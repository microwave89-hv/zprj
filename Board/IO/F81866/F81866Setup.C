//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//
//*************************************************************************
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866Setup.C 2     12/14/11 9:45p Kasalinyi $
//
// $Revision: 2 $
//
// $Date: 12/14/11 9:45p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866Setup.C $
// 
// 2     12/14/11 9:45p Kasalinyi
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix setup screen display "??" char
// [Files]  		F81865Setup.C
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting 
// [Files]  		F81866.CIF
// IO_F81866.SDL
// F81866.ASL
// F81866.MAK
// F81866.SD
// F81866.UNI
// F81866DXE.C
// F81866PEI.C
// F81866PeiDebugger.C
// F81866Setup.C
// F81866Setup.H
// History.txt
// F81866.chm
// 
// 4     3/21/11 9:41p Mikes
// seperate the core and oem job
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81866Setup.C>
//
// Description: Setup related Routines.
//
//<AMI_FHDR_END>
//*************************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Efi.h>
#include <AmiDxeLib.h>
#include <GenericSio.h>
#include "F81866Setup.H"
#include "SetupStringList.h"

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------
typedef void (HWM_EXTERNAL_FUN)(
    IN OUT HWM_DATA * Data
); 

typedef struct{
    UINT8   Type;
    UINT8   UID;
    UINT16  StrTokenV;
}STR_UID;

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------
static VOID SetSioStrings(
    IN    SPIO_DEV        *Dev,
    IN    EFI_HII_HANDLE  HiiHandle
);

STR_UID SetupStringsList[] = { STR_TABLE_LIST {0xff,0xff,0xffff}};

//----------------------------------
extern HWM_EXTERNAL_FUN  HWM_External_Fun_LIST EndOfFunList;
static HWM_EXTERNAL_FUN* OemHwmExternalFunList[] = {HWM_External_Fun_LIST NULL};

void AdjustString(
    IN OUT  CHAR16  * Buffer,
    IN      CHAR16  * StringToChged,
    IN      UINT8   STCLen,
    IN      CHAR16  * HeadBuf,
    IN      UINT8   HeadLen,
    IN      BOOLEAN Flag,
    IN      UINT8   MidPos,
    IN      CHAR16  * TailBuf,
    IN      UINT8   TailLen
);

UINTN
HHMEfiValueToString (
    IN  OUT CHAR16  *Buffer, 
    IN  INT64       Value, 
    IN  UINTN       Flags,
    IN  UINTN       Width
);

void HHMCommon(
    IN      UINTN   RegData,
    IN      UINT8   Func,
    IN      UINT16  StrToken,
    IN      UINT8   RefValue,
    EFI_HII_HANDLE    hiiHandle
);

/////////////////////////////////////////////////////////////////////////////
//Below function will update HII database's SIO strings, before enter setup
/////////////////////////////////////////////////////////////////////////////

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    InitSioSetupStrings
//
// Description:
//  This function provide SIO Setup screen display string.
//
// Input:
//  IN  IN UINT16       Class
//  IN  EFI_HII_HANDLE  *HiiHandle 
//
// Output:    VOID
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
VOID InitSioSetupStrings(
    IN    EFI_HII_HANDLE HiiHandle,
    IN    UINT16         Class)
{
    static EFI_GUID siopg=EFI_AMI_SIO_PROTOCOL_GUID;
    SPIO_DEV        *dev;
    UINTN           i,hcnt;
    EFI_HANDLE      *hbuff;
    EFI_STATUS      Status=0;

    if(Class == ADVANCED_FORM_SET_CLASS) {
        Status=pBS->LocateHandleBuffer(ByProtocol,&siopg, NULL, &hcnt,&hbuff);
        if (EFI_ERROR(Status)) hcnt = 0;
        for (i=0; i<hcnt; i++) {
            Status = pBS->HandleProtocol ( hbuff[i],&siopg,(VOID*)&dev);
            ASSERT_EFI_ERROR(Status);
            if(dev->DeviceInfo->HasSetup) SetSioStrings(dev, HiiHandle);
        }
    }
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: SetSioStrings
//
// Description:
//    This function provide SIO's each logic device Setup screen display string.
//
// Input:
//    IN  SPIO_DEV        *Dev - SPIO Device Private Data section
//    IN  EFI_HII_HANDLE  *HiiHandle 
//
// Output:    None
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//------------------------------------------------------------------------- 
// <AMI_PHDR_END> 
static VOID SetSioStrings(
    IN    SPIO_DEV        *Dev,
    IN    EFI_HII_HANDLE  HiiHandle)
{
    UINT8   i;
    CHAR8   pString8[80];
    CHAR16  pString16[80];

    if((!Dev->NvData.DevEnable) || (!Dev->VlData.DevImplemented)) return;

    if(Dev->VlData.DevDma1) {
        if(Dev->VlData.DevIrq1)
            Sprintf(pString8, "IO=%Xh; IRQ=%d; DMA=%d;", Dev->VlData.DevBase1,Dev->VlData.DevIrq1,Dev->VlData.DevDma1);
        else 
            Sprintf(pString8, "IO=%Xh; DMA=%d;",Dev->VlData.DevBase1, Dev->VlData.DevDma1);
    }
    else {
        if(Dev->VlData.DevIrq1)
            Sprintf(pString8, "IO=%Xh; IRQ=%d;",Dev->VlData.DevBase1,Dev->VlData.DevIrq1);
        else
            Sprintf(pString8, "IO=%Xh;",Dev->VlData.DevBase1);
    }
    
    for(i=0;(i < 0x80) && (pString8[i] != 0);i++)
        pString16[i] = (CHAR16)pString8[i];
        pString16[i++] = 0;

    for(i=0;;i++) {
        if(SetupStringsList[i].Type == 0xFF) break;
        if((SetupStringsList[i].UID == Dev->DeviceInfo->UID) && \
           (SetupStringsList[i].Type == Dev->DeviceInfo->Type)) {
            InitString(HiiHandle,SetupStringsList[i].StrTokenV,pString16);
            return;
        }

    }
    return;
}

/////////////////////////////////////////////////////////////////////////////
//Below function will update hardware monitor value dynamically
//No porting needed
/////////////////////////////////////////////////////////////////////////////

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:    F81866_HWM_CallBack
//
// Description:  
//  Form Callback Function.Will be called every 100m Polling for data Updates.
//
// Input:
//  IN EFI_HII_HANDLE HiiHandle
//  IN UINT16 Class
//  IN UINT16 SubClass
//  IN UINT16 Key
//
// Output:    VOID
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//------------------------------------------------------------------------- 
//<AMI_PHDR_END>
void F81866_HWM_CallBack(
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16 Class, 
    IN UINT16 SubClass, 
    IN UINT16 Key
)
{
    //EFI_STATUS  Status;
    HWM_DATA    Data;
    UINT8       i;

//-------------------------------------------------------------------------
//AMI_TO:  AMI need to porting the register where they goto read.
//-------------------------------------------------------------------------
    for(i=0; OemHwmExternalFunList[i]; i++)
    {
        OemHwmExternalFunList[i](&Data);
        HHMCommon(Data.Value, Data.Type, Data.Token, Data.OddPos, HiiHandle);
    }

  return ;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:  HHMEfiValueToString
//
// Description: 
//  This function Adjust the String shows in setup screen
//
// Input:     
//  INT64       Value   ->Value need change to string
//  UINTN       Flags   ->Comma type
//  UINTN       Width   ->Character number for value
//  CHAR16      *Buffer ->Temp string for this change
// Output:     
//
// OPTIONAL:  
//  None
//
// Returns:   
//  Index
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN
HHMEfiValueToString (
    IN  OUT CHAR16  *Buffer, 
    IN  INT64       Value, 
    IN  UINTN       Flags,
    IN  UINTN       Width
) {
    CHAR16      TempBuffer[CHARACTER_NUMBER_FOR_VALUE];
    CHAR16      *TempStr;
    CHAR16      *BufferPtr;
    UINTN       Count;
    UINTN       ValueCharNum;
    UINTN       Remainder;
    CHAR16      Prefix;
    UINTN       Index;
    BOOLEAN     ValueIsNegative;

    TempStr           = TempBuffer;
    BufferPtr         = Buffer;
    Count             = 0;
    ValueCharNum      = 0;
    ValueIsNegative   = FALSE;

    if (Width > CHARACTER_NUMBER_FOR_VALUE - 1) {
        Width = CHARACTER_NUMBER_FOR_VALUE - 1;
    }

    if (Value < 0) {
        *(TempStr++) = '-';
        Value        = -Value;
        ValueCharNum++;
        Count++;
        ValueIsNegative = TRUE;
    }
    do {
        if ((Width != 0) && (Count >= Width)) break;

        Value = (UINT64)Div64 ((UINT64)Value, 10, &Remainder);
        *(TempStr++) = (CHAR16)(Remainder + '0');
        ValueCharNum++;
        Count++;

        if ((Flags & COMMA_TYPE) == COMMA_TYPE) {
            if (Value != 0) {
                if ((ValueIsNegative && (ValueCharNum % 3 == 1)) || \
                    ((!ValueIsNegative) && (ValueCharNum % 3 == 0))) {
                    *(TempStr++) = ',';
                    Count++;
                }
            }
        }
    } while (Value != 0);

    if (Flags & PREFIX_ZERO) Prefix = '0';
    else Prefix = ' ';

    Index = Count;

    if (!(Flags & LEFT_JUSTIFY)) {
        for (; Index < Width; Index++) 
            *(TempStr++) = Prefix;
    }
    //
    // Reverse temp string into Buffer.
    //
    if (Width == 0) {
        while (TempStr != TempBuffer) 
            *(BufferPtr++) = *(--TempStr);
    } 
    else {
        Index = 0;
        while ((TempStr != TempBuffer) && (Index++ < Width))
        *(BufferPtr++) = *(--TempStr);
    } 
    *BufferPtr = 0;

    return Index;
}


//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:    AdjustString
//
// Description:  
//  Adjust string with float point
//
// Input:        
//  Buffer  -> defautl string.  ": N/A    ". Buffer length should more than 0x10
//  StringToChged -> Raw data
//  STCLen  -> String total length
//  HeadBuf -> Header of string
//  HeadLen -> Header length
//  Flag    -> TRUE indicate is a float data, False indicate it's a integet data.
//  MidPos  -> Float point position. eg: 0.076 is 0x3
//  TailBuf -> unit of string data 
//  TailLen -> Length of unit
//
// Output:       Return string in Buffer
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AdjustString(
    IN OUT  CHAR16  * Buffer,
    IN      CHAR16  * StringToChged,
    IN      UINT8   STCLen,
    IN      CHAR16  * HeadBuf,
    IN      UINT8   HeadLen,
    IN      BOOLEAN Flag,
    IN      UINT8   MidPos,
    IN      CHAR16  * TailBuf,
    IN      UINT8   TailLen
) {
    CHAR16     *temp        = Buffer;
    CHAR16     *TempSrc     = StringToChged;
    CHAR16     dod[]        ={L"."};
    CHAR16     Zero[]       ={L"0"};

    pBS->SetMem(temp, STR_BUFFER_LENGTH * sizeof(CHAR16), 0);

    if(HeadLen) {
        //Add the leading string
        pBS->CopyMem(temp, HeadBuf, (HeadLen * sizeof(CHAR16)));
        temp +=  HeadLen;
    }
    if (!Flag) {
        //Add the float point->L"."
        pBS->CopyMem(temp, TempSrc, (STCLen * sizeof(CHAR16))); //Add the string before float point
        temp += STCLen; TempSrc += STCLen;
        goto not_float_data;
    }

    if(STCLen <= MidPos) {
        //make up with a zero
        pBS->CopyMem(temp, Zero, (0x01 * sizeof(CHAR16)));      //Copy a 0
        temp++;
    } else {
        pBS->CopyMem(temp, TempSrc, ((STCLen - MidPos) * sizeof(CHAR16))); //Add the string before float point
        temp += (STCLen - MidPos); TempSrc += (STCLen - MidPos);
    }
    pBS->CopyMem(temp, dod, 0x01 * sizeof(CHAR16));             //Add the float point->L"."
    temp++;
    if(STCLen < MidPos) {
        //make up with a zero
        pBS->CopyMem(temp, Zero, ((MidPos - STCLen) * sizeof(CHAR16)));//Copy a 0
        pBS->CopyMem(temp, TempSrc, ((STCLen) * sizeof(CHAR16)));    //Add the string after float point
        temp += MidPos; TempSrc += MidPos;
    } else {
        pBS->CopyMem(temp, TempSrc, ((MidPos) * sizeof(CHAR16)));    //Add the string after float point
        temp += MidPos; TempSrc += MidPos;
    }
    not_float_data:
    if (TailLen) {
        //Add the unit
        pBS->CopyMem(temp, TailBuf, (TailLen * sizeof(CHAR16)));        
    }
    return;
}


//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:    HHMCommon
//
// Description:  
//  Update option with the data read from register
//
// Input:        
//  RegData     -> data from SIO registers
//  Func        -> Fan Speed,Voltage and Temperature
//  StrToken    -> String token
//  OddPos      -> Odd position
//  hiiHandle   
//  gblHii
//
// Output:       
//  Return string in Buffer
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HHMCommon(
    IN      UINTN     RegData,
    IN      UINT8     Func,
    IN      UINT16    StrToken,
    IN      UINT8     OddPos,
    IN      EFI_HII_HANDLE    hiiHandle
) {
    CHAR16          TailRound[]     = L" RPM";          //Fan uint
    CHAR16          TailVoltg[]     = L" V";            //Voltage uint
    CHAR16          TailTempt[]     = L" C";            //Temperature uint
    CHAR16          LeadingMini[]   = L": -";           //Fix 
    CHAR16          LeadingPlus[]   = L": +";           //Fix 
    CHAR16          LeadingSpac[]   = L": ";            //Fix
    CHAR16          AllSpace[]      = L": N/A       ";  //Fix
    CHAR16          *TempStr        = AllSpace;
    UINT8           StrLen;
    UINT64          NData;
    CHAR16          StrUp[STR_BUFFER_LENGTH] = L": N/A     "; //Don't change this line    
    CHAR16          *StrUpdated = StrUp;
    TailTempt[1]=0x2103;
    NData = (UINT64)(RegData);
    //The following may be ported by each SIO
    //As now, it support max length is five
    if(NData>9999)      StrLen = 0x5;
    else if(NData>999)  StrLen = 0x4;
    else if(NData>99)   StrLen = 0x3;
    else if(NData>9)    StrLen = 0x2;
    else                StrLen = 0x1;    

    //When device not present, update to 'N/A'
    if(NData == 0x00) StrUpdated = StrUp;
    else {
        HHMEfiValueToString(TempStr, NData, 0, StrLen);
        switch(Func) {
            case    VOLTAGE:                       //Indicate it's voltage
                AdjustString(StrUpdated, TempStr, StrLen, LeadingPlus, 0x03,\
                            OddPos?TRUE:FALSE, OddPos, TailVoltg, 0x02);
                break;
            case    TEMPERATURE:                   //Indicate it's Temperature
                AdjustString(StrUpdated, TempStr, StrLen, LeadingPlus, 0x03,\
                            OddPos?TRUE:FALSE, OddPos, TailTempt, 0x02);
                break;
            case    FAN_SPEED:                     //Indicate it's fan
                AdjustString(StrUpdated, TempStr, StrLen, LeadingSpac, 0x02,\
                            OddPos?TRUE:FALSE, OddPos, TailRound, 0x04);
                break;
            default :                              //Default to " N/A "
                break;
        }
    }
    InitString(hiiHandle, StrToken, StrUpdated);

    return;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

