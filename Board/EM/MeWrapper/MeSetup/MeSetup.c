//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/MeSetup.c 3     11/02/14 9:48p Tristinchou $
//
// $Revision: 3 $
//
// $Date: 11/02/14 9:48p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/MeSetup.c $
// 
// 3     11/02/14 9:48p Tristinchou
// [TAG]  		EIP189985
// [Category]  	Improvement
// [Description]  	For ME 9.1.20.1035, add NFC related option in setup
// 
// 2     2/20/13 10:50p Klzhan
// [TAG]  		EIP114344
// [Category]  	Improvement
// [Description]  	Update PTT capability / State information in Setup.
// 
// 1     2/08/12 1:04a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:41a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:09a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            MeSetup.c
//
// Description:     Setup hooks for MeSetup module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++
Copyright (c)  2008-2009 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  
Module Name:

 MeSetup.c

Abstract:

  
--*/
#include <Setup.h>
#include <SetupStrTokens.h>
#include <AmiDxeLib.h>
#if EFI_SPECIFICATION_VERSION>0x20000
#include <Protocol\HiiDatabase.h>
#include <Protocol\HiiString.h>
#else
#include <Protocol/Hii.h>
#endif
#include "MeSetup.h"
#if NFC_SUPPORT_DXE_SUPPORT == 1
#include "NfcSupportDxe\NfcSupportDxe.h"
#endif

typedef struct{
  UINT8         MeFirmwareInfo;
  UINT32        MeMajor;
  UINT32        MeMinor;
  UINT32        MeHotFix;
  UINT32        MeBuildNo;
} ME_INFO_SETUP_DATA;

#define ME_INFO_SETUP_GUID \
  {0x78259433, 0x7B6D, 0x4DB3, 0x9A, 0xE8, 0x36, 0xC4, 0xC2, 0xC3, 0xA1, 0x7D}

typedef struct{
  BOOLEAN        PTTCapability;
  BOOLEAN        PTTState;
} PTT_INFO_VARIABLE_DATA;

#define PTT_INFO_VARIABLE_GUID \
  {0x9e6eae27, 0xc452, 0x49e6, 0x99, 0xd9, 0xb4, 0x5d, 0x1c, 0xf9, 0x1c, 0x5a}

EFI_GUID                      PttInfoVariableGuid = PTT_INFO_VARIABLE_GUID;
PTT_INFO_VARIABLE_DATA        gPttInfoVariable;

EFI_GUID gMeInfoSetupGuid = ME_INFO_SETUP_GUID;
EFI_GUID  gSetupGuid = SETUP_GUID;
ME_INFO_SETUP_DATA mMeInfoSetupData;
SETUP_DATA                gSetupData;

VOID InitMeInfo(EFI_HII_HANDLE HiiHandle)
{
  EFI_STATUS       Status;
  UINTN            VariableSize;
  UINT8            *MeFwSkuValue;
  CHAR16           String[0x100];
  UINTN            StringLength;
#if EFI_SPECIFICATION_VERSION>0x20000
static EFI_HII_STRING_PROTOCOL *HiiString=NULL;
static EFI_HII_DATABASE_PROTOCOL *HiiDatabase=NULL;
#else
  EFI_GUID         guidHII = EFI_HII_PROTOCOL_GUID;
  EFI_HII_PROTOCOL *Hii = NULL;
#endif
  STRING_REF MeMode[] = {
    STRING_TOKEN(STR_ME_NORMAL_MODE),
#ifdef Ibexpeak_SUPPORT
    STRING_TOKEN(STR_ME_IGNITION),
#else
    STRING_TOKEN(STR_ME_FAILED),
#endif
    STRING_TOKEN(STR_ME_ALT_DISABLED),
    STRING_TOKEN(STR_ME_TEMP_DISABLED),
    STRING_TOKEN(STR_ME_SECOVER),
    STRING_TOKEN(STR_ME_FAILED),

  };
  UINT8 *FwMeSku[] = {
     STR_ME_FW_SKU_1_5MB,
     STR_ME_FW_SKU_5MB,
     STR_ME_FW_SKU_UNIDENTIFIED
  };
#if NFC_SUPPORT_DXE_SUPPORT == 1
  EFI_GUID                    NfcSupportDataGuid = NFC_SUPPORT_DATA_GUID;
  NFC_SUPPORT_DATA            NfcSupportData;
#endif
  //
  // Set default string size assumption at no more than 256 bytes
  //
  StringLength = 0x100;
#if EFI_SPECIFICATION_VERSION<=0x20000
  pBS->LocateProtocol(&guidHII, NULL, &Hii);
#endif
  VariableSize = sizeof(ME_INFO_SETUP_DATA);
  Status = pRS->GetVariable(
        L"MeInfoSetup",
        &gMeInfoSetupGuid,
        NULL,
        &VariableSize,
        &mMeInfoSetupData
  );
  if (EFI_ERROR(Status)) return;

  InitString(
    HiiHandle,STRING_TOKEN(STR_ME_FW_VERSION_VALUE), 
    L"%d.%d.%d.%d", 
    mMeInfoSetupData.MeMajor,mMeInfoSetupData.MeMinor,
    mMeInfoSetupData.MeHotFix,mMeInfoSetupData.MeBuildNo
  );

  VariableSize = sizeof (PTT_INFO_VARIABLE_DATA);
  Status = pRS->GetVariable (
               L"PttInfoVariable",
               &PttInfoVariableGuid,
               NULL,
               &VariableSize,
               &gPttInfoVariable
           );

  if (!EFI_ERROR(Status))
  {
    InitString(
      HiiHandle,STRING_TOKEN(STR_PTT_CAPABILITY_STATE_VALUE),
      L"%d / %d",
      gPttInfoVariable.PTTCapability,gPttInfoVariable.PTTState
    );
  }
  
#if NFC_SUPPORT_DXE_SUPPORT == 1
  VariableSize = sizeof(NFC_SUPPORT_DATA);
  Status = pRS->GetVariable(
               L"NfcSupportData",
               &NfcSupportDataGuid,
               NULL,
               &VariableSize,
               &NfcSupportData );
  if( !EFI_ERROR(Status) )
  {
    if( NfcSupportData.NFCCapability == 1 )
        InitString( HiiHandle, STRING_TOKEN(STR_NFC_SUPPORT_VALUE), L"Enabled" );
    else
        InitString( HiiHandle, STRING_TOKEN(STR_NFC_SUPPORT_VALUE), L"Disabled" );
  }
#endif
  

#if EFI_SPECIFICATION_VERSION>0x20000
    Status = HiiLibGetString(
             HiiHandle, MeMode[(mMeInfoSetupData.MeFirmwareInfo & ME_MODE_MASK)],
             &StringLength, String);
#else
    Status = Hii->GetString(Hii, HiiHandle, MeMode[(mMeInfoSetupData.MeFirmwareInfo & ME_MODE_MASK)], FALSE, NULL, &StringLength, String);
#endif
  InitString(
    HiiHandle,STRING_TOKEN(STR_ME_FW_INFO_VALUE), 
    L"%s",
    String
  );

   VariableSize = sizeof(SETUP_DATA);
    Status = pRS->GetVariable(
          L"Setup", 
          &gSetupGuid,
          NULL,
          &VariableSize,
          &gSetupData
    );
    ASSERT_EFI_ERROR(Status);	

    if (gSetupData.MeImageType == ME_IMAGE_1_5MB_FW) {
        MeFwSkuValue = FwMeSku[0];
    } else if (gSetupData.MeImageType == ME_IMAGE_5MB_FW) { 
        MeFwSkuValue = FwMeSku[1];
    } else  { 
        MeFwSkuValue = FwMeSku[2];
    }
    InitString (
      HiiHandle,
      STRING_TOKEN (STR_ME_FW_SKU_VALUE),
      L"%S",
      MeFwSkuValue
      );

}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************