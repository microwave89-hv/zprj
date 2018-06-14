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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSetup/AmtSetup.c 5     5/14/14 9:48p Tristinchou $
//
// $Revision: 5 $
//
// $Date: 5/14/14 9:48p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSetup/AmtSetup.c $
// 
// 5     5/14/14 9:48p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 4     9/19/12 6:37a Klzhan
// Fix entry point return type.
// 
// 3     6/05/12 2:05a Klzhan
// [TAG]  		EIP91581
// [Category]  	Improvement
// [Description]  	Avoid system crash when HECI reset
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 2     7/14/11 7:45a Klzhan
// Add "Disable ME" setup item.
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:11a Klzhan
// Initial Check-in.
//
//**********************************************************************
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		AMTSetup.c
//
// Description:	AMT TSE Functions.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "Token.h"
#include "Efi.h"
#include "EfiDriverLib.h"
#include "EfiCommonLib.h"
#include "Amt.h"
#include "EfiScriptLib.h"
#include "AmtLib.h"
#include "Include\Protocol\LegacySredir.h"
#include "AmtSetup.h"
#include <SetupDataDefinition.h>
#include "MELib.h"
#include EFI_PROTOCOL_CONSUMER   (AmtPlatformPolicy)
#include EFI_PROTOCOL_CONSUMER   (AmtWrapper)
#include EFI_PROTOCOL_DEFINITION (MeBiosPayloadData)
#include "Protocol\AmtWrapper\AmtWrapper.h"

EFI_GUID gEfiAmtWrapperProtocolGuid = EFI_AMT_WRAPPER_PROTOCOL_GUID;

#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }
EFI_GUID gEfiSetupGuid = SETUP_GUID;

VOID 
SetMEDisable (
    IN UINT8  Grayout 
)
{
#if defined(iAMT_SUPPORT) && (iAMT_SUPPORT == 1)
  SETUP_DATA               gSetupData;
  UINTN                    SetupDataSize;
  EFI_STATUS               Status;
  EFI_HECI_PROTOCOL        *Heci;
  UINT32                   MeMode;
  DXE_MBP_DATA_PROTOCOL    *mBIOSPayLoad;

  Status = gBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  &Heci
                  );

  if (EFI_ERROR (Status)) {
    return;
  }

  Status = Heci->GetMeMode (&MeMode);

  if (EFI_ERROR (Status)) {
    return;
  }

  SetupDataSize = sizeof(SETUP_DATA);
  Status = gRT->GetVariable ( L"Setup", \
                              &gEfiSetupGuid, \
                              NULL, \
                              &SetupDataSize, \
                              &gSetupData );

  if (EFI_ERROR (Status)) {
    return;
  }

  Status = gBS->LocateProtocol(&gMeBiosPayloadDataProtocolGuid, 
                               NULL, &mBIOSPayLoad);

  if (EFI_ERROR (Status)) {
    return;
  }

  if(gSetupData.MEDisabled)
  {
      // AT in Inactive mode, and no SOL or IDER or KVM session
      // can't set ME to disabled
      if((MeMode == ME_MODE_NORMAL) && 
         (mBIOSPayLoad->MeBiosPayload.AtState.State == 0) &&
         (Grayout == 0))
      {
          Status = HeciSetMeDisableMsg();
          if(!EFI_ERROR(Status))
          {
              Status = HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
              if(!EFI_ERROR(Status))
                  EFI_DEADLOOP();
          }
      }
  }else
  {
      if(MeMode == ME_MODE_TEMP_DISABLED)
      {
          Status = HeciSetMeEnableMsg();
          if(!EFI_ERROR(Status))
          {
              Status = HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
              if(!EFI_ERROR(Status))
                  EFI_DEADLOOP();
          }
      }
  }
#endif
}


EFI_STATUS 
InitializeAmtSetup (
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
  SETUP_AMT_FEATURES    SetupAmtFeatures;
  EFI_STATUS            Status;
  UINT32                VarAttr;
  UINTN                 VariableSize;
  UINTN                 Update = 0;
  UINT8                 GrayOut;
  AMT_WRAPPER_PROTOCOL  *pAmtWrapper = NULL;


  EfiInitializeDriverLib (ImageHandle, SystemTable);
	
  Status = gBS->LocateProtocol(
                              &gEfiAmtWrapperProtocolGuid, 
                              NULL, 
                              &pAmtWrapper);

  ASSERT_EFI_ERROR(Status);
		
  VariableSize = sizeof(SETUP_AMT_FEATURES);
  Status = gRT->GetVariable(
                L"SetupAmtFeatures",
                &gEfiSetupGuid,
                &VarAttr,
                &VariableSize,
                &SetupAmtFeatures);
	
  if ( pAmtWrapper->ActiveManagementEnableIdeR() || 
       pAmtWrapper->ActiveManagementEnableSol() || 
       pAmtWrapper->ActiveManagementEnableKvm()) {
    GrayOut = 1;
  } else {
    GrayOut = 0;
  }
  	
  if (SetupAmtFeatures.GrayOut != GrayOut) {
      SetupAmtFeatures.GrayOut = GrayOut;
      Update = 1;
  }
  	
  if (Update || EFI_ERROR(Status)) {
      if( Status == EFI_NOT_FOUND )
        VarAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
      Status = gRT->SetVariable(
                    L"SetupAmtFeatures",
                    &gEfiSetupGuid,
                    VarAttr,
                    sizeof(SETUP_AMT_FEATURES),
                    &SetupAmtFeatures);
      ASSERT_EFI_ERROR(Status);
  }
  SetMEDisable(GrayOut);


  return EFI_SUCCESS;
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