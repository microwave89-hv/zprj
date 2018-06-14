//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/HiiConfig.c 10    6/16/11 12:52p Artems $
//
// $Revision: 10 $
//
// $Date: 6/16/11 12:52p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/HiiConfig.c $
// 
// 10    6/16/11 12:52p Artems
// Bugfix: Handle situation when string passed to BlockToConfig function
// doesn't have standard header
// 
// 9     5/13/11 5:17p Artems
// Function CompareGuid (native EdkII) renamed to HiiCompareGuid to avoid
// collusion
// 
// 8     5/09/11 6:40p Artems
// Bugfix: Handle situation when config string passed to ConfigToBlock
// function doesn't have standard header
// 
// 7     1/25/11 3:26p Artems
// EIP 47960 : Added functionality for ExportConfig function
// 
// 6     11/05/10 5:17p Artems
// EIP 46880: Fixed bug, where two functions referred to the same global
// pointer
// 
// 4     10/01/10 4:36p Artems
// Added service function StripValuePattern
// 
// 2     12/03/09 6:02p Artems
// SCT test bug fix
// 
// 1     10/09/09 6:12p Felixp
// 
// 1     2/27/09 3:55p Artems
// Initial check-in
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	HiiConfig.c
//
// Description:	Hii Config Routing protocol implementation
//
//<AMI_FHDR_END>
//**********************************************************************

#pragma warning (disable : 4090)

#include <AmiDxeLib.h>
#include "HiiPrivate.h"


extern HII_DATABASE_PRIVATE_DATA PrivateData;

const NAME_PATTERN GuidPattern   = { 10, L"GUID=" };
const NAME_PATTERN NamePattern   = { 10, L"NAME=" };
const NAME_PATTERN PathPattern   = { 10, L"PATH=" };
const NAME_PATTERN AltCfgPattern = { 14, L"ALTCFG=" };
const NAME_PATTERN OffsetPattern = { 14, L"OFFSET=" };
const NAME_PATTERN WidthPattern  = { 12, L"WIDTH=" };
const NAME_PATTERN ValuePattern  = { 12, L"VALUE=" };

const CHAR16 HexDigit[] = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7',
                            L'8', L'9', L'a', L'b', L'c', L'd', L'e', L'f' };

EFI_GUID HiiConfigAccessProtocolGuid = EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID;

#define INITIAL_RESULT_STRING_SIZE 0x1000



//**************************** Protocol functions implementation ***************************

EFI_STATUS HiiExtractConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING Request1,
    OUT EFI_STRING      *Progress,
    OUT EFI_STRING      *Results
)
{
    EFI_STRING ConfigString;
    EFI_STRING ErrorPointer;
    EFI_STRING ResultPointer;
    BOOLEAN LastString = FALSE;
    EFI_STATUS Status;
    UINTN Index;
    EFI_HANDLE Handle;
    UINTN ProgressMarker = 0;
    UINTN Gap;
    EFI_HII_CONFIG_ACCESS_PROTOCOL *ConfigAccess;
    EFI_STRING Request = Request1;
    RESULT_BLOCK Result;

    if(Progress == NULL || Results == NULL)
        return EFI_INVALID_PARAMETER;

    if(Request == NULL)
    {
        *Progress = NULL;
        return EFI_INVALID_PARAMETER;
    }

    if(!CheckPattern(Request, &GuidPattern))
    {
        *Progress = Request;
        return EFI_INVALID_PARAMETER;
    }

    Status = InitResultBlock(&Result);
    if (EFI_ERROR(Status))
	    return Status;

    do
    {
        Status = ExtractConfigString(Request, &Index, &ConfigString);
        if(EFI_ERROR(Status))
            return Status;

        if(ConfigString != NULL)
        {
            Status = FindDeviceHandle(ConfigString, &Handle);
            if(EFI_ERROR(Status))       //we failed to find corresponding driver handle
            {
                pBS->FreePool(ConfigString);
                *Progress = &Request[ProgressMarker];
                *Results = Result.ResultString;
                return Status;
            }

            Status = pBS->HandleProtocol(Handle, &HiiConfigAccessProtocolGuid, &ConfigAccess);
            if(EFI_ERROR(Status))       //we failed to find corresponding protocol
            {
                pBS->FreePool(ConfigString);
                *Progress = &Request[ProgressMarker];
                *Results = Result.ResultString;
                return Status;
            }

            Status = ConfigAccess->ExtractConfig(ConfigAccess, ConfigString, 
                                                 &ErrorPointer, &ResultPointer);
            if(EFI_ERROR(Status))
            {
                Gap = (UINTN)(ErrorPointer - ConfigString); //determine offset of error
                pBS->FreePool(ConfigString);
                *Progress = &Request[ProgressMarker + Gap];
                *Results = Result.ResultString;
                return Status;
            }

            ProgressMarker += Index;     //shift to next config string
            Request += Index;
            pBS->FreePool(ConfigString);
            Status = CollectResults(ResultPointer, 0, &Result);
	        if (EFI_ERROR(Status))
		        return Status;
            pBS->FreePool(ResultPointer);
        }
        else                            //now we process last request
        {
            LastString = TRUE;
            Status = FindDeviceHandle(Request, &Handle);
            if(EFI_ERROR(Status))       //we failed to find corresponding driver handle
            {
                *Progress = Request;
                *Results = Result.ResultString;
                return Status;
            }

            Status = pBS->HandleProtocol(Handle, &HiiConfigAccessProtocolGuid, &ConfigAccess);
            if(EFI_ERROR(Status))       //we failed to find corresponding protocol
            {
                *Progress = Request;
                *Results = Result.ResultString;
                return Status;
            }

            Status = ConfigAccess->ExtractConfig(ConfigAccess, Request, 
                                                 &ErrorPointer, &ResultPointer);
            if(EFI_ERROR(Status))
            {
                *Progress = ErrorPointer;
                *Results = Result.ResultString;
                return Status;
            }
            Status = CollectResults(ResultPointer, 0, &Result);
	        if (EFI_ERROR(Status))
		        return Status; 
            pBS->FreePool(ResultPointer);
        }
    } while(!LastString);

    *Results = Result.ResultString;

//set Progress to null-terminator
    Index = StrSize16(Request) / 2;
    *Progress = &Request[Index - 1];
    
    return EFI_SUCCESS;
}

EFI_STATUS Hii21ExportConfigHelper (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    OUT EFI_STRING *Results
);

EFI_STATUS HiiExportConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    OUT EFI_STRING *Results
)
{
    if(Results == NULL)
        return EFI_INVALID_PARAMETER;

    return Hii21ExportConfigHelper (This, Results);
}

EFI_STATUS HiiRouteConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING Configuration1,
    OUT EFI_STRING      *Progress
)
{
    EFI_STRING ConfigString;
    EFI_STRING ErrorPointer;
    BOOLEAN LastString = FALSE;
    EFI_STATUS Status;
    UINTN Index;
    EFI_HANDLE Handle;
    UINTN ProgressMarker = 0;
    UINTN Gap;
    EFI_HII_CONFIG_ACCESS_PROTOCOL *ConfigAccess;
    EFI_STRING Configuration = Configuration1;

    if(Progress == NULL)
        return EFI_INVALID_PARAMETER;

    if(Configuration == NULL)
    {
        *Progress = NULL;
        return EFI_INVALID_PARAMETER;
    }

    if(!CheckPattern(Configuration, &GuidPattern))
    {
        *Progress = Configuration;
        return EFI_INVALID_PARAMETER;
    }

    do
    {
        Status = ExtractConfigString(Configuration, &Index, &ConfigString);
        if(EFI_ERROR(Status))
            return Status;

        if(ConfigString != NULL)
        {
            Status = FindDeviceHandle(ConfigString, &Handle);
            if(EFI_ERROR(Status))       //we failed to find corresponding driver handle
            {
                pBS->FreePool(ConfigString);
                *Progress = &Configuration[ProgressMarker];
                return Status;
            }

            Status = pBS->HandleProtocol(Handle, &HiiConfigAccessProtocolGuid, &ConfigAccess);
            if(EFI_ERROR(Status))       //we failed to find corresponding protocol
            {
                pBS->FreePool(ConfigString);
                *Progress = &Configuration[ProgressMarker];
                return Status;
            }

            Status = ConfigAccess->RouteConfig(ConfigAccess, ConfigString, &ErrorPointer);
            if(EFI_ERROR(Status))
            {
                Gap = (UINTN)(ErrorPointer - ConfigString); //determine offset of error
                pBS->FreePool(ConfigString);
                *Progress = &Configuration[ProgressMarker + Gap];
                return Status;
            }

            ProgressMarker += Index;     //shift to next config string
            Configuration += Index;
            pBS->FreePool(ConfigString);
        }
        else                            //now we process last cofiguration
        {
            LastString = TRUE;
            Status = FindDeviceHandle(Configuration, &Handle);
            if(EFI_ERROR(Status))       //we failed to find corresponding driver handle
            {
                *Progress = Configuration;
                return Status;
            }

            Status = pBS->HandleProtocol(Handle, &HiiConfigAccessProtocolGuid, &ConfigAccess);
            if(EFI_ERROR(Status))       //we failed to find corresponding protocol
            {
                *Progress = Configuration;
                return Status;
            }

            Status = ConfigAccess->RouteConfig(ConfigAccess, Configuration, &ErrorPointer);
            if(EFI_ERROR(Status))
            {
                *Progress = ErrorPointer;
                return Status;
            }
        }
    } while(!LastString);

//set Progress to null-terminator
    Index = StrSize16(Configuration) / 2;
    *Progress = &Configuration[Index - 1];
    
    return EFI_SUCCESS;
}

EFI_STATUS HiiBlockToConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigRequest,
    IN CONST UINT8      *Block,
    IN CONST UINTN      BlockSize,
    OUT EFI_STRING      *Config,
    OUT EFI_STRING      *Progress
)
{
    UINTN ProgressMarker;
    UINTN i = 0;
    UINTN Start;
    UINT32 Offset;
    UINT32 Width;
    UINT32 ConfigStringSize;
    EFI_STATUS Status;
    RESULT_BLOCK Result;

    if(Progress == NULL)
        return EFI_INVALID_PARAMETER;

    if(ConfigRequest == NULL || Block == NULL || Config == NULL )
    {
        *Progress = ConfigRequest;
        return EFI_INVALID_PARAMETER;
    }

    ConfigStringSize = StrSize16(ConfigRequest) / 2;

//Prepare result buffer for output
    Status = InitResultBlock(&Result);
    if (EFI_ERROR(Status))
	    return Status;

//find start of OFFSET/WIDTH/VALUE block
    if(!CheckPattern(ConfigRequest, &OffsetPattern)) { //for BlockToConfig function ConfigResp is allowed not to have standard header GUID=...NAME=.
        do
        {
            while((ConfigRequest[i] != L'&') && (ConfigRequest[i] != 0))
                i++;

            if(ConfigRequest[i] == 0)
            {
                *Progress = ConfigRequest;
                pBS->FreePool(Result.ResultString);
                return EFI_NOT_FOUND;
            }

            i++;            //shift pointer to next symbol
            if(CheckPattern(&ConfigRequest[i], &OffsetPattern))
                break;
        } while(1);
    }
 
    Status = CollectResults(ConfigRequest, i, &Result);   //copy header
	if (EFI_ERROR(Status))
    {
        pBS->FreePool(Result.ResultString);
	    return Status;
    }

    do
    {
        ProgressMarker = i - 1;     //set ProgressMarker to '&'

        Start = i;
        Status = GetPatternValue(ConfigRequest, &i, &OffsetPattern, &Offset);
        if(EFI_ERROR(Status))
        {
            *Progress = &ConfigRequest[ProgressMarker];
            pBS->FreePool(Result.ResultString);
            return Status;
        }
        else    
        {
            Status = CollectResults(&ConfigRequest[Start], i - Start, &Result);   //copy header
	        if (EFI_ERROR(Status))
            {
                pBS->FreePool(Result.ResultString);
	            return Status;
            }
        }            

        Start = i;
        Status = GetPatternValue(ConfigRequest, &i, &WidthPattern, &Width);
        if(EFI_ERROR(Status))
        {
            *Progress = &ConfigRequest[ProgressMarker];
            pBS->FreePool(Result.ResultString);
            return Status;
        }
        else    
        {
            Status = CollectResults(&ConfigRequest[Start], i - Start, &Result);   //copy header
	        if (EFI_ERROR(Status))
            {
                pBS->FreePool(Result.ResultString);
	            return Status;
            }
        }            

        if(BlockSize < (Offset + Width))
        {
            pBS->FreePool(Result.ResultString);
            return EFI_DEVICE_ERROR;
        }

        Status = CollectValueResults(&Block[Offset], Width, &Result);
	    if (EFI_ERROR(Status))
        {
            pBS->FreePool(Result.ResultString);
	        return Status;
        }

    } while(i < ConfigStringSize);

    *Progress = &ConfigRequest[ConfigStringSize - 1];         //set Progress to null-terminator
    *Config = Result.ResultString;

    return EFI_SUCCESS;
}

EFI_STATUS HiiConfigToBlock (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigResp,
    IN OUT CONST UINT8 *Block,
    IN OUT UINTN *BlockSize,
    OUT EFI_STRING *Progress
)
{
    UINTN ProgressMarker;
    UINTN i = 0;
    UINT32 Offset;
    UINT32 Width;
    UINT32 ConfigStringSize;
    EFI_STATUS Status;

    if(Progress == NULL)
        return EFI_INVALID_PARAMETER;

    if(ConfigResp == NULL || BlockSize == NULL )
    {
        *Progress = ConfigResp;
        return EFI_INVALID_PARAMETER;
    }

    if(Block == NULL && *BlockSize != NULL )
    {
        *Progress = ConfigResp;
        return EFI_INVALID_PARAMETER;
    }

    ConfigStringSize = StrSize16(ConfigResp) / 2;

//find start of OFFSET/WIDTH/VALUE block
    if(!CheckPattern(ConfigResp, &OffsetPattern)) { //for ConfigToBlock function ConfigResp is allowed not to have standard header GUID=...NAME=.
        do {
            while((ConfigResp[i] != L'&') && (ConfigResp[i] != 0))
                i++;

            if(ConfigResp[i] == 0) {
//TODO: should it be like this???
//Intel's style - if there is no OFFSET/WIDTH/VALUE blocks - return EFI_SUCCESS
/*
            *Progress = ConfigResp;
            return EFI_NOT_FOUND;
*/
                *Progress = &ConfigResp[i];
                return EFI_SUCCESS;
            }

            i++;            //shift pointer to next symbol
            if(CheckPattern(&ConfigResp[i], &OffsetPattern))
                break;
        } while(1);
    }

    do
    {
        ProgressMarker = i - 1;     //set ProgressMarker to '&'

        Status = GetPatternValue(ConfigResp, &i, &OffsetPattern, &Offset);
        if(EFI_ERROR(Status))
        {
            *Progress = &ConfigResp[ProgressMarker];
            return Status;
        }

        Status = GetPatternValue(ConfigResp, &i, &WidthPattern, &Width);
        if(EFI_ERROR(Status))
        {
            *Progress = &ConfigResp[ProgressMarker];
            return Status;
        }

//provided block is too small to accumulate value
        if(*BlockSize < (Offset + Width))
        {
            *BlockSize = Offset + Width;
            return EFI_DEVICE_ERROR;
        }

        Status = GetStringValue(ConfigResp, &i, &Block[Offset], Width);
        if(EFI_ERROR(Status))
        {
            *Progress = &ConfigResp[ProgressMarker];
            return Status;
        }

    } while(i < ConfigStringSize);

    *BlockSize = Offset + Width - 1;    //set index of last updated byte
    *Progress = &ConfigResp[ConfigStringSize - 1];         //set Progress to null-terminator

    return EFI_SUCCESS;
}

EFI_STATUS HiiGetAltConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigResp,
    IN CONST EFI_GUID   *Guid,
    IN CONST EFI_STRING Name,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN CONST EFI_STRING AltCfgId,
    OUT EFI_STRING      *AltCfgResp
)
{
    BOOLEAN LastString = FALSE;
    EFI_STATUS Status;
    UINTN Index;
    UINTN StrSize;
    EFI_STRING ConfigString = ConfigResp;


    if(ConfigResp == NULL || AltCfgResp == NULL)
        return EFI_INVALID_PARAMETER;

    if(!CheckPattern(ConfigString, &GuidPattern))
        return EFI_INVALID_PARAMETER;

    do {
        Status = ExtractConfigString(ConfigString, &Index, AltCfgResp);
        if(EFI_ERROR(Status))
            return Status;

        if(*AltCfgResp != NULL) {
            Status = CheckAltCfg(*AltCfgResp, Guid, Name, DevicePath, AltCfgId);
            if(!EFI_ERROR(Status))
                return Status;

            ConfigString += Index;
            pBS->FreePool(*AltCfgResp);
        } else {
            LastString = TRUE;
            StrSize = StrSize16(ConfigString);
            Status = pBS->AllocatePool(EfiBootServicesData, StrSize, AltCfgResp);
            if(EFI_ERROR(Status))
                return Status;

            MemCpy(*AltCfgResp, ConfigString, StrSize);
            Status = CheckAltCfg(*AltCfgResp, Guid, Name, DevicePath, AltCfgId);
            if(EFI_ERROR(Status))
                pBS->FreePool(*AltCfgResp);

            return Status;
            
        }
    } while(!LastString);

    return EFI_NOT_FOUND;
}

// *************************** Service functions (not for public use) **********************

VOID StringToBlock(
    IN CHAR16 *String,
    IN UINTN StringSize,
    OUT UINT8 *Block)
{
    UINT8 LowNibble, HiNibble;
    UINTN i, j;

    j = 0;

    for(i = 0; i < StringSize; i += 2)
    {
        if(i == StringSize - 1) {   //odd number need to fill with zeroes
            HiNibble = 0;
            LowNibble = HexValue((UINT8)String[i]);
        } else {
            HiNibble = HexValue((UINT8)String[i]);
            LowNibble = HexValue((UINT8)String[i + 1]);
        }
        Block[j] = (HiNibble << 4) | LowNibble;
        j++;
    }
}

BOOLEAN CheckIfHexDigit(CHAR16 Char)
{
    if(Char < 0x30 || Char > 0x66)
        return FALSE;

    if(Char > 0x39 && Char < 0x41)
        return FALSE;

    if(Char > 0x46 && Char < 0x61)
        return FALSE;

    return TRUE;
}

UINT8 HexValue(CHAR8 Char)
{
    if(Char >= 0x30 && Char <= 0x39)        //symbols 0...9
        return Char - 0x30;

    if(Char >= 0x41 && Char <= 0x46)        //symbols A...F
        return Char - 0x37;

    return Char - 0x57;                     //symbols a...f
}


UINT32 GetValue(CHAR16 *String, UINTN Start, UINTN End)
{
    UINT32 Result = 0;
    UINTN i;
    UINT8 Nibble;
    UINT8 NibbleCount = 0;

    for(i = Start; i < End; i++)
    {
        Nibble = HexValue((UINT8) String[i]);
        if(Nibble == 0 && NibbleCount == 0)             //skip leading zeros
            continue;

        if(NibbleCount >= 8)        //provided value exceed 4 bytes
            return 0xffffffff;

        Result <<= 4;
        Result |= Nibble;
        NibbleCount++;
    }
    return Result;
}

EFI_STATUS GetStringValue(
    CHAR16 *String,
    UINTN  *Index,
    UINT8  *Output,
    UINT32 Width)
{
    EFI_STATUS Status;
    UINTN Start;
    UINTN i;
    UINT8 *Result;
    UINTN HexSymbolsCount;
    UINT8 SmallBuffer[20];
    UINTN ResultBufferSize = 20;

    Start = *Index;

    if(!CheckPattern(&String[Start], &ValuePattern))
        return EFI_INVALID_PARAMETER;

    Start += ValuePattern.Length / 2;
    i = Start;

    while((String[i] != L'&') && (String[i] != 0)) {
        if(!CheckIfHexDigit(String[i]))
            return EFI_INVALID_PARAMETER;
        i++;
    }

    HexSymbolsCount = i - Start;

    if(Width > 20) {
        Status = pBS->AllocatePool(EfiBootServicesData, Width, &Result);
        if(EFI_ERROR(Status))
            return Status;
        ResultBufferSize = Width;
    } else {
        Result = SmallBuffer;
    }

    MemSet(Result, ResultBufferSize, 0);
    StringToBlock(&String[Start], HexSymbolsCount, Result);
    
//now write the result swapped(INTEL's style)
    if(Width > 1)
        WriteSwappedBuffer(Output, Result, Width);
    else
        *Output = *Result;

    if(Width > 20)
        pBS->FreePool(Result);

    i++;                //skip delimiter

    *Index = i;

    return EFI_SUCCESS;
}

EFI_STATUS GetPatternValue(
    CHAR16 *String, 
    UINTN *Index, 
    NAME_PATTERN *Pattern, 
    UINT32 *Value)
{
    UINT32 Result;
    UINTN Start;
    UINTN i;
    BOOLEAN EndPattern = FALSE;

    if(Pattern->Tag[0] == L'V' || Pattern->Tag[0] == L'W')
        EndPattern = TRUE;

    Start = *Index;

    if(!CheckPattern(&String[Start], Pattern))
        return EFI_INVALID_PARAMETER;

    Start += Pattern->Length / 2;
    i = Start;

    while((String[i] != L'&') && (String[i] != 0))
    {
        if(!CheckIfHexDigit(String[i]))
            return EFI_INVALID_PARAMETER;
        i++;
    }

    if(String[i] == 0 && !EndPattern)  //unexpected end of string
        return EFI_INVALID_PARAMETER;

    Result = GetValue(String, Start, i);
    i++;        //skip delimiter

    *Value = Result;
    *Index = i;

    return EFI_SUCCESS;
}

EFI_STATUS FindDeviceHandle(
    IN CHAR16 *ConfigString,
    OUT EFI_HANDLE *Handle)
{
    UINTN i = 0;
    UINTN DpLength;
    UINT8 *DevicePath;
    EFI_STATUS Status;

//scan config string to find PATH pattern
    do
    {
        while((ConfigString[i] != L'&') && (ConfigString[i] != 0))
            i++;

        if(ConfigString[i] == 0)
            return EFI_NOT_FOUND;

        i++;            //shift pointer to next symbol
        if(CheckPattern(&ConfigString[i], &PathPattern))
            break;
    } while(1);

//if we get here, we have pointer set on PATH pattern
    Status = ExtractDevicePath(&ConfigString[i], &DevicePath, &DpLength);
    if(EFI_ERROR(Status))
        return Status;

    Status = SearchDevicePath(DevicePath, DpLength, Handle);
    pBS->FreePool(DevicePath);

    return Status;
}

EFI_STATUS ExtractDevicePath(CHAR16 *ConfigString, UINT8 **DevicePath, UINTN *DpLength)
{
    EFI_STATUS Status;
    UINTN Length = 0;
    UINTN i = 5;        //set pointer to skip first four symbols "PATH="

    while(CheckIfHexDigit(ConfigString[i]))      //determine device path length in characters
    {
        Length++;
        i++;
    }

    Status = pBS->AllocatePool(
                            EfiBootServicesData, 
        					(Length / 2), 
					        DevicePath);
	if (EFI_ERROR(Status))
		return Status;

    StringToBlock(&ConfigString[5], Length, *DevicePath);
    *DpLength = Length / 2;

    return EFI_SUCCESS;
}

EFI_STATUS SearchDevicePath(UINT8 *DevicePath, UINTN DpLength, EFI_HANDLE *Handle)
{
    PACKAGE_LIST_RECORD *Record = (PACKAGE_LIST_RECORD *) PrivateData.PackList.pHead;
	PACKAGE_LINK *PackageLink;

    while(Record != NULL)
    {
        PackageLink = (PACKAGE_LINK *) Record->PackageList.pHead;
        while(PackageLink != NULL)
        {
            if(PackageLink->Package.Type == EFI_HII_PACKAGE_DEVICE_PATH)
            {
                if(CheckDevicePath(DevicePath, DpLength, &PackageLink->Package))
                {
                    *Handle = Record->DriverHandle;
                    return EFI_SUCCESS;
                }
            }
            PackageLink = (PACKAGE_LINK *)PackageLink->Link.pNext;
        }
        Record = (PACKAGE_LIST_RECORD *)Record->Link.pNext;
    }
    return EFI_NOT_FOUND;
}

static BOOLEAN CheckDevicePath(
    IN UINT8 *DevicePath, 
    IN UINTN DpLength, 
    IN EFI_HII_PACKAGE_HEADER *Package)
{
    UINTN Length;
    UINT8 *Dp = (UINT8 *)Package;

    Dp += sizeof(EFI_HII_PACKAGE_HEADER);

    Length = Package->Length - sizeof(EFI_HII_PACKAGE_HEADER);
    if(Length != DpLength)
        return FALSE;
    if(MemCmp(DevicePath, Dp, Length))
        return FALSE;

    return TRUE;
}


EFI_STATUS ExtractConfigString(CHAR16 *String, UINTN *NextIndex, CHAR16 **NewString)
{
    EFI_STATUS Status;
    UINTN i = 0;
    CHAR16 *Eos;

//scan config string to find next GUID pattern
    do
    {
        while((String[i] != L'&') && (String[i] != 0))
            i++;

        if(String[i] == 0)
        {
            *NewString = NULL;      //config string contains only one string
            return EFI_SUCCESS;
        }

        i++;            //shift pointer to next symbol
        if(CheckPattern(&String[i], &GuidPattern))
            break;
    } while(1);

//as we are here i points to next config string
    Status = pBS->AllocatePool(
                            EfiBootServicesData, 
        					sizeof(CHAR16) * i, 
					        NewString);
	if (EFI_ERROR(Status))
		return Status;

    MemCpy(*NewString, String, (i - 1) * 2);
    Eos = *NewString;
    Eos[i - 1] = 0;         //put null terminator

    *NextIndex = i;
    return EFI_SUCCESS;
}

BOOLEAN CheckPattern(CHAR16 *String, NAME_PATTERN *Pattern)
{
    if(MemCmp(String, Pattern->Tag, Pattern->Length))
        return FALSE;
    else
        return TRUE;
}

EFI_STATUS CollectResults(CHAR16 *Result, UINTN Symbols, RESULT_BLOCK *ResultBlock)
{
    EFI_STATUS Status;
    UINTN StrSize;
    CHAR16 *Helper;

    StrSize = (Symbols != 0) ? Symbols : StrSize16(Result) / 2;    //we need size in CHAR16, not bytes

    if(ResultBlock->MaxResultStringSize < (StrSize + ResultBlock->CurrentSize))
    {
        Status = ReallocResultString((StrSize + ResultBlock->CurrentSize) * 2, ResultBlock);
	    if (EFI_ERROR(Status))
		    return Status;             
    }

    Helper = ResultBlock->ResultString;
    if(ResultBlock->CurrentSize != 0)        //we have to change null-terminator to '&' symbol
        Helper[ResultBlock->CurrentSize - 1] = L'&';

    MemCpy(&Helper[ResultBlock->CurrentSize], Result, StrSize * sizeof(CHAR16));
    ResultBlock->CurrentSize += StrSize;

    return EFI_SUCCESS;
}

EFI_STATUS ReallocResultString(UINTN NewSize, RESULT_BLOCK *ResultBlock)
{
    CHAR16 *Pointer;
    EFI_STATUS Status;
    
    ResultBlock->MaxResultStringSize = NewSize;
    Status = pBS->AllocatePool(
                            EfiBootServicesData, 
        					sizeof(CHAR16) * ResultBlock->MaxResultStringSize, 
					        &Pointer);
    if (EFI_ERROR(Status))
	    return Status;             

    MemCpy(Pointer, ResultBlock->ResultString, ResultBlock->CurrentSize * sizeof(CHAR16));
    pBS->FreePool(ResultBlock->ResultString);
    ResultBlock->ResultString = Pointer;

    return EFI_SUCCESS;
}

EFI_STATUS CollectValueResults(UINT8* Value, UINT32 Width, RESULT_BLOCK *ResultBlock)
{
    CHAR16 ValueHeader[] = L"VALUE=";
    UINT32 i;
    UINT8 Nibble;
    EFI_STATUS Status;
    CHAR16 *ValueString;
    CHAR16 *Ptr;
    UINTN  StringSize;

//first determine necessary string size, including null-terminator in CHAR16 symbols
    StringSize = Width * 2 + 6 + 1; //each byte requires two symbols plus &VALUE= size plus null terminator

    Status = pBS->AllocatePool(EfiBootServicesData, StringSize * 2, &ValueString);
    if(EFI_ERROR(Status))
        return Status;

//copy header
    MemCpy(ValueString, ValueHeader, 12);
    Ptr = ValueString + 6;

//write value in reversed order
    for(i = 0; i < Width; i++)
    {
        Nibble = Value[Width - i - 1] >> 4;
        *Ptr++ = HexDigit[Nibble];
        Nibble = Value[Width - i - 1] & 0xf;
        *Ptr++ = HexDigit[Nibble];
    }

//set null-terminator
    *Ptr = 0;
    Status = CollectResults(ValueString, 0, ResultBlock);
    pBS->FreePool(ValueString);
    return Status;
}

VOID WriteSwappedBuffer(
    OUT UINT8 *Output,
    IN  UINT8 *Input,
    IN  UINTN Size)
{
    UINTN i;

    for(i = 0; i < Size; i++)
        Output[i] = Input[Size - i - 1];
}

EFI_STATUS CheckAltCfg (
    IN EFI_STRING ConfigString,
    IN CONST EFI_GUID   *Guid,
    IN CONST EFI_STRING Name,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN CONST EFI_STRING AltCfgId
)
{
    EFI_STATUS Status;
    UINTN i = 0;
    UINTN j;
    UINT32 Size;
    UINT32 CfgId;

//scan config string to find ALTCFG pattern
    do {
        while((ConfigString[i] != L'&') && (ConfigString[i] != 0))
            i++;

        if(ConfigString[i] == 0)        //ALTCFG pattern not found
            break;

        i++;            //shift pointer to next symbol
        if(CheckPattern(&ConfigString[i], &AltCfgPattern))
            break;
    } while(1);

    if(ConfigString[i] == 0 && AltCfgId != NULL) //we have current config but needed alt one
        return EFI_NOT_FOUND;

    if(ConfigString[i] != 0 && AltCfgId == NULL) //we have alt config but needed current one
        return EFI_NOT_FOUND;

    if(ConfigString[i] != 0 && AltCfgId != NULL) {
        j = i;
        Status = GetPatternValue(ConfigString, &j, &AltCfgPattern, &CfgId);
        if(EFI_ERROR(Status) || *AltCfgId != (UINT16)CfgId)
            return EFI_NOT_FOUND;                   //we have alt config, but it's not matched

//if we're here alt config is matched
//we need to remove "ALTCFG=XXXX" from string as per spec but SCT expects "ALTCFG=" pattern in output string

        //j already points to the next pattern
        Size = StrSize16(&ConfigString[j]);
        MemCpy(&ConfigString[i], &ConfigString[j], Size);

    }

    if(Guid != NULL && !HiiCompareGuid(ConfigString, Guid))
        return EFI_NOT_FOUND;       //guid not matched

    if(Name != NULL && !CompareName(ConfigString, Name))
        return EFI_NOT_FOUND;       //name not matched

    if(DevicePath != NULL && !CompareDevicePath(ConfigString, DevicePath))
        return EFI_NOT_FOUND;       //DevicePath not matched

    return EFI_SUCCESS;
}

BOOLEAN HiiCompareGuid(
    IN EFI_STRING ConfigString,
    IN CONST EFI_GUID   *Guid
)
{
    CHAR16 *Pointer = ConfigString;
    UINTN       Length;
    EFI_GUID    AltGuid;
    EFI_GUID *VarGuid = Guid;

    if(!CheckPattern(ConfigString, &GuidPattern))
        return FALSE;

    Pointer += 5;       //skip "GUID=" pattern
    Length = 32;        //length of guid in symbols
    StringToBlock(Pointer, Length, (UINT8 *)&AltGuid);

    return !guidcmp(VarGuid, &AltGuid);
}

BOOLEAN CompareName(
    IN EFI_STRING ConfigString,
    IN CONST EFI_STRING  Name
)
{
    CHAR16 *Pointer = ConfigString;
    UINTN       Length;
    CHAR16      AltName[80];
    EFI_STRING VarName = Name;
    UINTN i = 0;

    do {
        while((ConfigString[i] != L'&') && (ConfigString[i] != 0))
            i++;

        if(ConfigString[i] == 0)        //NAME pattern not found
            return FALSE;

        i++;            //shift pointer to next symbol
        if(CheckPattern(&ConfigString[i], &NamePattern))
            break;
    } while(1);

    Pointer = &ConfigString[i];
    Pointer += 5;       //skip "NAME=" pattern
    Length = 80;        //length of name buffer
    StringToChar16(Pointer, &Length, AltName);

    return !StrCmp16(VarName, AltName);
}

BOOLEAN CompareDevicePath(
    IN EFI_STRING ConfigString,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath
)
{
    UINTN       Length;
    EFI_DEVICE_PATH_PROTOCOL *AltDevicePath;
    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL *VarDp = DevicePath;
    BOOLEAN Result;
    UINTN i = 0;

    do {
        while((ConfigString[i] != L'&') && (ConfigString[i] != 0))
            i++;

        if(ConfigString[i] == 0)        //PATH pattern not found
            return FALSE;

        i++;            //shift pointer to next symbol
        if(CheckPattern(&ConfigString[i], &PathPattern))
            break;
    } while(1);

    Status = ExtractDevicePath(&ConfigString[i], (UINT8 **)&AltDevicePath, &Length);
    if(EFI_ERROR(Status))
        return FALSE;

    Result = !DPCmp(VarDp, AltDevicePath);
    pBS->FreePool(AltDevicePath);
    return Result;
}

VOID StringToChar16(
    IN CHAR16 *String,
    IN OUT UINTN  *Size,
    OUT CHAR16 *Block
)
{
    UINTN i, j;

    i = 0;
    j = 0;

    while( CheckIfHexDigit(String[i]) && CheckIfHexDigit(String[i + 1]) && 
           CheckIfHexDigit(String[i + 2]) && CheckIfHexDigit(String[i + 3]) &&
           j < *Size - 1 )
    {
        Block[j]  = HexValue((UINT8)String[i]) & 0x000f;
        Block[j] <<= 4;
        Block[j] |= HexValue((UINT8)String[i + 1]);
        Block[j] <<= 4;
        Block[j] |= HexValue((UINT8)String[i + 2]);
        Block[j] <<= 4;
        Block[j] |= HexValue((UINT8)String[i + 3]);

        i += 4;
        j++;
    }
    *Size = j;      //number of words processed
    Block[j] = 0;   //put null-terminator
}

VOID StripValuePattern(
    IN OUT EFI_STRING String,
    IN UINTN          Size
)
{
    EFI_STATUS Status;
    EFI_STRING NewString;
    UINTN i = 0;
    UINTN j = 0;

    Status = pBS->AllocatePool(EfiBootServicesData, Size, &NewString);

    while(String[i] != 0) {
        if(String[i] == L'&') {
            if(CheckPattern(&String[i + 1], &ValuePattern)) {
                i++;
                while((String[i] != L'&') && (String[i] != 0))
                    i++;
                if(String[i] == 0)
                    break;
            }
        }

        NewString[j++] = String[i++];
    }

    NewString[j] = 0;
    MemCpy(String, NewString, (j + 1) * 2);
    pBS->FreePool(NewString);
}

EFI_STATUS InitResultBlock(
    IN OUT RESULT_BLOCK *ResultBlock
)
{
    EFI_STATUS Status;
    ResultBlock->MaxResultStringSize = INITIAL_RESULT_STRING_SIZE;
    ResultBlock->CurrentSize = 0;
    Status = pBS->AllocatePool(
                            EfiBootServicesData, 
        					sizeof(CHAR16) * ResultBlock->MaxResultStringSize, 
					        &(ResultBlock->ResultString));
    return Status;
}

#pragma warning (default : 4090)

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************