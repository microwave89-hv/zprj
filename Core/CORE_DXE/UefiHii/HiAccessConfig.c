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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/HiAccessConfig.c 7     5/04/11 12:08p Artems $
//
// $Revision: 7 $
//
// $Date: 5/04/11 12:08p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/UefiHii/HiAccessConfig.c $
// 
// 7     5/04/11 12:08p Artems
// Bug fix: when variable is absent attribute state was undefined
// 
// 6     1/25/11 4:03p Artems
// EIP 51298: Fixed corruption in buffer size after passing it to
// ConfigToBlock function
// Added check for correct syntax of request string in ExtractConfig
// function
// 
// 5     9/30/10 6:12p Artems
// Removed unnecessary service functions
// 
// 3     2/19/10 4:01p Felixp
// Debug messages are removed.
// 
// 2     11/25/09 11:25a Felixp
// Action parameter of the Callback function is updated  based on UEFI
// errata
// 
// 1     10/09/09 6:12p Felixp
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	HiiAccessConfig.c
//
// Description:	Hii Config Access protocol implementation
//
//<AMI_FHDR_END>
//**********************************************************************

#pragma warning (disable : 4090)

#include <AmiDxeLib.h>
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/HiiConfigRouting.h>

#include "HiiPrivate.h"

extern const NAME_PATTERN GuidPattern;
extern const NAME_PATTERN NamePattern;
extern const NAME_PATTERN PathPattern;
extern const NAME_PATTERN AltCfgPattern;
extern const NAME_PATTERN OffsetPattern;
extern const NAME_PATTERN WidthPattern;
extern const NAME_PATTERN ValuePattern;
extern const CHAR16 HexDigit[];

UINTN EfiStrLen  (IN CHAR16 *String);
UINTN EfiStrSize (IN CHAR16 *String);
VOID  EfiStrCat  (IN CHAR16 *Destination, IN CHAR16 *Source);

//**************************** Protocol functions implementation ***************************


EFI_STATUS HiiAccessExtractConfig(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN CONST EFI_STRING Request,
    OUT EFI_STRING *Progress,
    OUT EFI_STRING *Results
)
{
    EFI_STATUS  Status;
    UINTN       Length;
    EFI_GUID    Guid;
    CHAR16      Name[80];
    CHAR16      *Pointer = Request;
    UINT8       *Var = NULL;
    EFI_HII_CONFIG_ROUTING_PROTOCOL *ConfigRouting;
    CHAR16      *ErrorMarker;

    if(Request == NULL) {
        *Progress = NULL;
        return EFI_INVALID_PARAMETER;
    }

    Status = pBS->LocateProtocol(&gEfiHiiConfigRoutingProtocolGuid, NULL, &ConfigRouting);
    if(EFI_ERROR(Status))
        return Status;

//check syntax for guid
    if(!CheckPattern(Request, &GuidPattern)) {
        *Progress = Request;
        return EFI_INVALID_PARAMETER;
    }
//extract guid
    ErrorMarker = Pointer;
    Pointer += 5;       //skip "GUID=" pattern
    Length = 32;        //length of guid in symbols
    StringToBlock(Pointer, Length, (UINT8 *)&Guid);
    Pointer += Length;
    if(*Pointer != L'&') {
        TRACE((TRACE_DXE_CORE, "HII Extract Config: Guid extraction failed\n"));
        *Progress = ErrorMarker;
        return EFI_INVALID_PARAMETER;
    }

//check syntax for name
    if(!CheckPattern(Pointer + 1, &NamePattern)) {
        *Progress = Pointer;
        return EFI_INVALID_PARAMETER;
    }
//extract name
    ErrorMarker = Pointer;
    Pointer += 6;       //skip '&NAME=' pattern
    Length = 80;
    StringToChar16(Pointer, &Length, Name);
    Pointer += (Length * 4);
    if(*Pointer != L'&') {
        TRACE((TRACE_DXE_CORE, "HII Extract Config: Name extraction failed\n"));
        *Progress = ErrorMarker;
        return EFI_INVALID_PARAMETER;
    }

//get variable by name and guid from nvram

    Length = 0;
    Status = GetEfiVariable(Name, &Guid, NULL, &Length, &Var);
    if(EFI_ERROR(Status)) {
        *Progress = Request;
        return Status;
    }

//find start of OFFSET/WIDTH/VALUE block
    Pointer++;      //skip '&'
    while((*Pointer != L'&') && (*Pointer != 0))    //skip PATH
            Pointer++;

    if(*Pointer == 0) {                     //OFFSET/WIDTH blocks are missed
        UINTN TempSize; 
        CHAR16 *TempString;
        CHAR16 *TempString2;

        TempSize = (EfiStrLen(L"&OFFSET=0&WIDTH=") + sizeof(Length) + 1) * sizeof(CHAR16);
        TempString = MallocZ(TempSize);
        if(TempString == NULL)
            return EFI_OUT_OF_RESOURCES;

        Swprintf_s(TempString, TempSize, L"&OFFSET=0&WIDTH=%x", Length);

        TempSize += EfiStrSize(Request);
        TempString2 = MallocZ(TempSize);
        if(TempString2 == NULL)
            return EFI_OUT_OF_RESOURCES;

        EfiStrCat(TempString2, Request);
        EfiStrCat(TempString2, TempString);

        Status = ConfigRouting->BlockToConfig(ConfigRouting, TempString2, Var, Length, Results, Progress);
        *Progress = Request + EfiStrLen(Request); //set Progress to end of ConfigHdr
        pBS->FreePool(TempString);
        pBS->FreePool(TempString2);
    } else {                                        //OFFSET/WIDTH block found, let's check if it's correct
        if(!CheckPattern(Pointer + 1, &OffsetPattern)) {
            *Progress = Pointer;
            return EFI_INVALID_PARAMETER;
        }
        Status = ConfigRouting->BlockToConfig(ConfigRouting, Request, Var, Length, Results, Progress);
    }
        
    pBS->FreePool(Var);

    return Status;
}

EFI_STATUS HiiAccessRouteConfig(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN CONST EFI_STRING Configuration,
    OUT EFI_STRING *Progress
)
{
    EFI_STATUS  Status;
    UINTN       Length;
    UINTN       VarSize;
    EFI_GUID    Guid;
    CHAR16      Name[80];
    CHAR16      *Pointer = Configuration;
    UINT8       *Var = NULL;
    EFI_HII_CONFIG_ROUTING_PROTOCOL *ConfigRouting;
    EFI_HANDLE  Handle;
    UINT32      Attributes;

    if(Configuration == NULL)
    {
        *Progress = NULL;
        return EFI_INVALID_PARAMETER;
    }

    Status = pBS->LocateProtocol(&gEfiHiiConfigRoutingProtocolGuid, NULL, &ConfigRouting);
    if(EFI_ERROR(Status))
        return Status;

//check syntax for guid
    if(!CheckPattern(Configuration, &GuidPattern))
    {
        *Progress = Configuration;
        return EFI_INVALID_PARAMETER;
    }

//check proper device path
        Status = FindDeviceHandle(Configuration, &Handle);
        if(EFI_ERROR(Status))
            return EFI_NOT_FOUND;

//extract guid
    Pointer += 5;       //skip "GUID=" pattern
    Length = 32;        //length of guid in bytes
    StringToBlock(Pointer, Length, (UINT8 *)&Guid);
    Pointer += Length;
    if(*Pointer != L'&')
    {
        TRACE((TRACE_DXE_CORE, "HII Route Config: Guid extraction failed\n"));
        *Progress = Pointer;
        return EFI_INVALID_PARAMETER;
    }

//check syntax for name
    if(!CheckPattern(Pointer + 1, &NamePattern))
    {
        *Progress = Pointer;
        return EFI_INVALID_PARAMETER;
    }
//extract name
    Pointer += 6;       //skip '&NAME=' pattern
    Length = 80;
    StringToChar16(Pointer, &Length, Name);
    Pointer += (Length * 4);
    if(*Pointer != L'&')
    {
        TRACE((TRACE_DXE_CORE, "HII Route Config: Name extraction failed\n"));
        *Progress = Pointer;
        return EFI_INVALID_PARAMETER;
    }

//get variable by name and guid from nvram

    Length = 0;
    Status = GetEfiVariable(Name, &Guid, &Attributes, &Length, &Var);
    if(EFI_ERROR(Status))   //requested variable not found
    {
        Var = NULL;
        Length = 0;
        Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
    }
    VarSize = Length;

    Status = ConfigRouting->ConfigToBlock(ConfigRouting, Configuration, Var, &Length, Progress);
    while(Status == EFI_DEVICE_ERROR) //block not large enough
    {
        if(Var != NULL)
            pBS->FreePool(Var);

        Status = pBS->AllocatePool(EfiBootServicesData, Length, &Var);
        if(EFI_ERROR(Status))
            return Status;

        VarSize = Length;
        Status = ConfigRouting->ConfigToBlock(ConfigRouting, Configuration, Var, &Length, Progress);
    }

    if(EFI_ERROR(Status))
        return Status;

    pRS->SetVariable(Name, &Guid, Attributes, VarSize, Var);

    pBS->FreePool(Var);

    return EFI_SUCCESS;
}

EFI_STATUS HiiAccessFormCallback(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID QuestionId,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
)
{
    return EFI_UNSUPPORTED;
}

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
