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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePlatformPolicy/MePlatformPolicy.c 14    5/14/14 10:33p Tristinchou $
//
// $Revision: 14 $
//
// $Date: 5/14/14 10:33p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePlatformPolicy/MePlatformPolicy.c $
// 
// 14    5/14/14 10:33p Tristinchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Load ICC library while using ME 9.1
// 
// 13    5/14/14 9:59p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 12    5/13/14 4:02a Tristinchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix BPF version check error while using MEBX 9.1
// 
// 11    7/11/13 5:50a Klzhan
// [TAG]  		EIP128534
// [Category]  	Improvement
// [Description]  	Restore Logo after information shows
// 
// 10    6/21/13 3:07a Klzhan
// [TAG]  		EIP127189
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 1.60
// 
// 9     5/13/13 2:39a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix build error when ICC_OVERCLOCKING_SUPPORT disabled.
// 
// 8     12/07/12 5:12a Klzhan
// [TAG]  		EIP107613
// [Category]  	Improvement
// [Description]  	Skip Send HECI protocol when Boot on Flash Update
// 
// 7     12/04/12 5:56a Klzhan
// [TAG]  		EIP107309
// [Category]  	New Feature
// [Description]  	Support ICC library for ME 9.5
// [Files]  		MePlatformPolicy.c
// MePlatformPolicy.h
// MePlatformPolicy.sdl
// MePlatformPolicy.mak
// MePlatformPolicy.cif
// 
// 6     9/27/12 4:49a Klzhan
// [TAG]  		EIP102254
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 0.7
// 
// 5     7/02/12 11:34p Klzhan
// [TAG]  		EIP94113
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 0.6
// 
// 4     5/14/12 4:40a Klzhan
// [TAG]  		EIP89952
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 0.56
// [Files]  		MePlatformPolicy.c
// MePlatformPolicy.h
// MePlatformPolicy.sdl
// MePlatformPolicy.mak
// MePlatformPolicy.cif
// 
// 3     4/23/12 11:13p Klzhan
// 
// 2     4/03/12 8:11a Klzhan
// [TAG]  		EIP86914
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC.
// 
// 1     2/08/12 1:04a Klzhan
// Initial Check in 
// 
// 10    9/26/11 5:46a Klzhan
// [TAG]  		EIP70516
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME 8.0 RC 0.8
// 
// 9     9/15/11 6:36a Klzhan
// [TAG]  		EIP65738
// [Category]  	Improvement
// [Description]  	Disable SOL and IDER when AMT is disabled.
// 
// 8     9/07/11 4:49a Klzhan
// Get thermal reporting data from HOB.
// 
// 7     7/26/11 8:25a Klzhan
// [TAG]  		EIP64542
// [Category]  	Improvement
// [Description]  	Replace Getvariable by GetSBSetupData
// 
// 6     7/26/11 6:33a Klzhan
// Always_MeFwDowngrade
// 
// 5     7/11/11 4:41a Klzhan
// Fix system can't boot on ME FW 1076.
// 
// 4     7/08/11 9:14a Klzhan
// Restore to older ME Platform Policy module part.
// To fix system hangs with other modules.
// 
// 3     7/08/11 4:20a Klzhan
// [TAG]  		EIP64189
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC to 0.7
// [Files]  		MePlatformPolicy.c
// MePlatformPolicy.h
// MePlatformPolicy.sdl
// MePlatformPolicy.mak
// MePlatformPolicy.cif
// 
// 2     4/18/11 9:47a Klzhan
// Improvement : Move ME FW downgrade related code to ME platform policy.
// Improvement : Update ME platform policy revision to 7.
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
// Name:            MePlatformPolicy.c
//
// Description:     
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

This file contains a 'Sample Driver' and is licensed as such
under the terms of your license agreement with Intel or your
vendor.  This file may be modified by the user, subject to  
the additional terms of the license agreement               

--*/

/*++
Copyright (c)  2008 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  
Module Name:

 MePlatformPolicy.c

Abstract:

  
--*/
#include "EdkIIGlueDxe.h"
#include "MePlatformPolicy.h"
#include "MeSetup.h"
#include <SetupDataDefinition.h>
#include "MeChipsetLib.h"
#include <token.h>
#if IccOverClocking_SUPPORT
#include "IccProtocol.h"
#endif
DXE_ME_POLICY_PROTOCOL  mDxePlatformMePolicy = { 0 };
SETUP_DATA              *gSetupData = NULL;
EFI_MEBX_API_ENTRY_POINT HookedMebxEntryPoint;

#define ME_INFO_SETUP_GUID \
  {0x78259433, 0x7B6D, 0x4DB3, 0x9A, 0xE8, 0x36, 0xC4, 0xC2, 0xC3, 0xA1, 0x7D}

EFI_GUID gSetupGuid                     = SETUP_GUID;
EFI_GUID gEfiFirmwareVolumeProtocolGuid = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;
EFI_GUID gMeSetupInfoGuid               = ME_INFO_SETUP_GUID;
EFI_GUID gEfiMebxProtocolGuid           = INTEL_MEBX_PROTOCOL_GUID;

//
// Driver entry point
//
EFI_DRIVER_ENTRY_POINT (MePlatformPolicyEntryPoint)

//
// Module Global Variable
//
//TR_CONFIG mTrConfig = { 0 };

//
// TS DIMM thermal polling Smbus Address. 
// This is platform specific.
//
EFI_STATUS
HookMebxEntry (
  IN  UINT32  BiosParams,
  OUT UINT32  *MebxReturnValue
)
{
  MEBX_BPF                  *MebxBpf = NULL;
  ME_BIOS_EXTENSION_SETUP   *MebxSetup = NULL;
  
  MebxBpf = (MEBX_BPF*)BiosParams;
  MebxSetup = (ME_BIOS_EXTENSION_SETUP*)MebxBpf->MeBiosSyncDataPtr;

  //Modify the BPF version before MEBX entry
  MebxBpf->BpfVersion = 0xA000;
  MebxSetup->InterfaceVersion = 0xA000;
  
  return HookedMebxEntryPoint( BiosParams, MebxReturnValue);
}

VOID
MebxProtocolCallBack (
  IN EFI_EVENT Event,
  IN VOID *Context
)
{
  EFI_STATUS        Status;
  EFI_MEBX_PROTOCOL *MebxProtocol = NULL;
  
  Status = gBS->LocateProtocol(
                &gEfiMebxProtocolGuid,
                NULL,
                &MebxProtocol );
  if( EFI_ERROR(Status) )
    return;

  //If MEBX version is 10, hook the entry to modify the BPF version
  if( (MebxProtocol->MebxVersion.Major == 10) )
  {
    HookedMebxEntryPoint = MebxProtocol->CoreMebxEntry;
    MebxProtocol->CoreMebxEntry = HookMebxEntry;
  }
  
  gBS->CloseEvent( Event );
}

UINT8                   mTsDimmSmbusAddress[] = { 0x30, 0x34 };
EFI_STATUS
DummyHeciSendACK(
  IN OUT  UINT32                  *Message,
  IN OUT  UINT32                  Length,
  IN OUT  UINT32                  *RecLength,
  IN      UINT8                   HostAddress,
  IN      UINT8                   MEAddress
  )
{
    return EFI_SUCCESS;
}
//
// Function implementations
//
EFI_STATUS
EFIAPI
MePlatformPolicyEntryPoint (
    IN EFI_HANDLE               ImageHandle,
    IN EFI_SYSTEM_TABLE         *SystemTable
)
/*++
 
Routine Description:
 
  Entry point for the Management Engine Driver.
  
Arguments:
 
  ImageHandle       Image handle of this driver.
  SystemTable       Global system service table.
 
Returns:
 
  EFI_SUCCESS           Initialization complete.
  EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  EFI_DEVICE_ERROR      Device error, driver exits abnormally.
 
--*/
{
  EFI_STATUS                      Status;
  SETUP_DATA                      SetupData;
  UINT32                          SetupVarAttr;
  UINTN                           SetupVariableSize;
  EFI_HECI_PROTOCOL               *Heci;
  UINT32                          MeMode = ME_MODE_FAILED;
  ME_INFO_SETUP_DATA              MeInfoSetupData;
  UINT8                           Index = 0;
  DXE_MBP_DATA_PROTOCOL           *mBIOSPayLoad;
  EFI_GUID                        gEfiHeciProtocolGuid = HECI_PROTOCOL_GUID;
  EFI_GUID                        gDimmTsInfoGuid = DIMM_TS_INFO_GUID;
  EFI_BOOT_MODE                   BootMode;
  EFI_PEI_HOB_POINTERS            HobList;
  EFI_EVENT                       MebxProtocolEvent;
  VOID                            *MebxProtocolReg = NULL;

  EfiInitializeDriverLib (ImageHandle, SystemTable);
  Status = gBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  &Heci
                  );

  if (EFI_ERROR(Status)) return EFI_SUCCESS; 

  EfiGetSystemConfigurationTable (&gEfiHobListGuid, &HobList.Raw);
  if (HobList.Header->HobType != EFI_HOB_TYPE_HANDOFF) {
    DEBUG ((EFI_D_ERROR, "(Wdt) Handoff Hob missing!\n"));
    return EFI_NOT_FOUND;
  }

  BootMode = HobList.HandoffInformationTable->BootMode;

  if((BootMode == BOOT_ON_FLASH_UPDATE) ||
     (BootMode == BOOT_ASSUMING_NO_CONFIGURATION_CHANGES))
  {
    // Install Dummy HECI protocol.
    Heci->SendwACK = DummyHeciSendACK;
  }


  Status = Heci->GetMeMode (&MeMode);
  //
  // Default ME information for SETUP
  // 
  MeInfoSetupData.MeFirmwareInfo = MeMode;
  MeInfoSetupData.MeMajor = 0;
  MeInfoSetupData.MeMinor = 0;
  MeInfoSetupData.MeHotFix = 0;
  MeInfoSetupData.MeBuildNo = 0;
  //
  // ME DXE Policy Init
  //
  mDxePlatformMePolicy.Revision = DXE_PLATFORM_ME_POLICY_PROTOCOL_REVISION_2;

  SetupVarAttr = 0;
  SetupVariableSize = sizeof(SETUP_DATA);
  Status = gRT->GetVariable (
                             L"Setup",
                             &gSetupGuid,
                             &SetupVarAttr,
                             &SetupVariableSize,
                             &SetupData
                             );
  if(EFI_ERROR(Status))
  {
      mDxePlatformMePolicy.MeConfig.MeFwDownGrade = 0;
      SetupVarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE;
  }

  if(!EFI_ERROR(Status))
  {
    //
    // Initialzie the Me Configuration
    //
    mDxePlatformMePolicy.MeConfig.EndOfPostEnabled        = 1;
    mDxePlatformMePolicy.MeConfig.MeLocalFwUpdEnabled     = 0;
    mDxePlatformMePolicy.MeConfig.MdesForBiosState        = SetupData.MDESForBiosState;

    //
    // Please don't change the default value of EndOfPostDone,
    // the value will be update to 1 after the moment EOP message should be sent
    //
    mDxePlatformMePolicy.MeConfig.EndOfPostDone           = 0;


  }else
  {
    // Default
    mDxePlatformMePolicy.MeConfig.EndOfPostEnabled        = 1;
    mDxePlatformMePolicy.MeConfig.MeLocalFwUpdEnabled     = 0;
  }

  //
  // Thermal reporting policy is based on strap settings
  //
  MmioAndThenOr32 (
    PCH_RCRB_BASE + R_PCH_SPI_FDOC,
    (UINT32) (~(B_PCH_SPI_FDOC_FDSS_MASK | B_PCH_SPI_FDOC_FDSI_MASK)),
    (UINT32) (V_PCH_SPI_FDOC_FDSS_PCHS | R_PCH_SPI_STRP15)
    );
  mDxePlatformMePolicy.MeReportError = ShowMeReportError;
 
// Debug  UpdateDxeMePlatformPolicy (&mMeDxePlatformPolicy);
  mDxePlatformMePolicy.MeConfig.MeFwDownGrade = SetupData.MeFwDowngrade;
  //
  // If Me Fw is in ME_MODE_SECOVER, we will clear "Simple Firmware Downgrade" BIOS setup options 
  //
  if (MeMode == ME_MODE_SECOVER) {
        SetupData.MeFwDowngrade = 0;   
  }
  Status = gBS->LocateProtocol (
               &gMeBiosPayloadDataProtocolGuid,
               NULL,
               &mBIOSPayLoad
               );
  if(!EFI_ERROR(Status))
  {
    SetupData.MeImageType = (UINT8)mBIOSPayLoad->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType;
    SetupData.MeFirmwareInfo = MeMode;

    MeInfoSetupData.MeMajor = mBIOSPayLoad->MeBiosPayload.FwVersionName.MajorVersion;
    MeInfoSetupData.MeMinor = mBIOSPayLoad->MeBiosPayload.FwVersionName.MinorVersion;
    MeInfoSetupData.MeHotFix = mBIOSPayLoad->MeBiosPayload.FwVersionName.HotfixVersion;
    MeInfoSetupData.MeBuildNo = mBIOSPayLoad->MeBiosPayload.FwVersionName.BuildVersion;
  }
#if IccOverClocking_SUPPORT
  if((MeInfoSetupData.MeMajor == 9) && (MeInfoSetupData.MeMinor == 5))
  {
    EFI_GUID  gIcc95Guid = ICC_9_5_GUID;
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &ImageHandle,
                    &gIcc95Guid,
                    NULL,
                    NULL
                    );
  }

  if( (MeInfoSetupData.MeMajor == 9) &&
      ((MeInfoSetupData.MeMinor == 0) || (MeInfoSetupData.MeMinor == 1)) )
  {
    EFI_GUID  gIcc90Guid = ICC_9_0_GUID;
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &ImageHandle,
                    &gIcc90Guid,
                    NULL,
                    NULL
                    );
  }
#endif
  Status = gRT->SetVariable (
                    L"MeInfoSetup",
                    &gMeSetupInfoGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    sizeof(MeInfoSetupData),
                    &MeInfoSetupData
                    );

  Status = gRT->SetVariable (
                    L"Setup",
                    &gSetupGuid,
                    SetupVarAttr,
                    sizeof(SETUP_DATA),
                    &SetupData
                    );

  //Create the event for MEBX_PROTOCOL
  Status = gBS->CreateEvent(
                    EFI_EVENT_NOTIFY_SIGNAL,
                    EFI_TPL_NOTIFY,
                    MebxProtocolCallBack,
                    NULL,
                    &MebxProtocolEvent );

  Status = gBS->RegisterProtocolNotify(
                    &gEfiMebxProtocolGuid,
                    MebxProtocolEvent,
                    &MebxProtocolReg );            

  //
  // Install protocol to to allow access to this Policy.
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gDxePlatformMePolicyGuid,
                  &mDxePlatformMePolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
#include EFI_PROTOCOL_CONSUMER (ConsoleControl)
#include EFI_PROTOCOL_CONSUMER (GraphicsOutput)
EFI_CONSOLE_CONTROL_PROTOCOL    *ConsoleControl;
EFI_GRAPHICS_OUTPUT_PROTOCOL    *GraphicsOutput;
EFI_CONSOLE_CONTROL_SCREEN_MODE ScreenMode;
UINTN                           UgaBltSize = 0;
EFI_UGA_PIXEL                   *UgaBlt = NULL;
VOID
GraphicsSave
(
    VOID
)
{
  EFI_STATUS
  Status = gBS->LocateProtocol( &gEfiConsoleControlProtocolGuid, NULL, &ConsoleControl);

  if(EFI_ERROR(Status))
  {
    ConsoleControl = NULL;
    return;
  }

  Status = ConsoleControl->GetMode(ConsoleControl, &ScreenMode, NULL, NULL);
  if(ScreenMode == EfiConsoleControlScreenText)
  {
    ConsoleControl = NULL;
    return;    
  }

  Status = gBS->LocateProtocol( &gEfiGraphicsOutputProtocolGuid, NULL, &GraphicsOutput);
  if(EFI_ERROR(Status))
  {
    GraphicsOutput = NULL;
    return;
  }
  UgaBltSize = GraphicsOutput->Mode->Info[GraphicsOutput->Mode->Mode].HorizontalResolution * 
               GraphicsOutput->Mode->Info[GraphicsOutput->Mode->Mode].VerticalResolution * 
               sizeof(EFI_UGA_PIXEL);

  UgaBlt = AllocateZeroPool (UgaBltSize);

  Status = GraphicsOutput->Blt(
           GraphicsOutput,
           UgaBlt,
           EfiBltVideoToBltBuffer,
           0, 0,
           0, 0,
           GraphicsOutput->Mode->Info->HorizontalResolution, 
           GraphicsOutput->Mode->Info->VerticalResolution,
           0);

  Status = ConsoleControl->SetMode( ConsoleControl, EfiConsoleControlScreenText );
}

VOID
GraphicsRestore
(
    VOID
)
{
  if(!ConsoleControl)
    return;

  ConsoleControl->SetMode( ConsoleControl, EfiConsoleControlScreenGraphics ); 

  if(!GraphicsOutput)
    return;

  GraphicsOutput->Blt(
           GraphicsOutput,
           UgaBlt,
           EfiBltBufferToVideo,
           0, 0,
           0, 0,
           GraphicsOutput->Mode->Info->HorizontalResolution, 
           GraphicsOutput->Mode->Info->VerticalResolution,
           0);

}
VOID
ShowMeReportError (
  IN ME_ERROR_MSG_ID            MsgId
  )
/*++

Routine Description:

  Show Me Error message.
  
Arguments:

  MsgId   Me error message ID.

Returns:

  None.
  
--*/
{
  UINTN MsgDelay;

  MsgDelay = HECI_MSG_DELAY;
  GraphicsSave();
  gST->ConOut->ClearScreen (gST->ConOut);

  switch (MsgId) {
  case MSG_EOP_ERROR:
    gST->ConOut->OutputString (gST->ConOut, L"Error sending End Of Post message to ME, System HALT!\n");
    break;

  case MSG_ME_FW_UPDATE_FAILED:
    gST->ConOut->OutputString (gST->ConOut, L"ME FW Update Failed, please try again!\n");
    break;

  case MSG_ASF_BOOT_DISK_MISSING:
    gST->ConOut->OutputString (gST->ConOut, L"Boot disk missing, please insert boot disk and press ENTER\r\n");
    break;

  case MSG_KVM_TIMES_UP:
    gST->ConOut->OutputString (gST->ConOut, L"Error!! Times up and the KVM session was cancelled!!");
    break;

  case MSG_KVM_REJECTED:
    gST->ConOut->OutputString (gST->ConOut, L"Error!! The request has rejected and the KVM session was cancelled!!");
    break;

  case MSG_HMRFPO_LOCK_FAILURE:
    gST->ConOut->OutputString (gST->ConOut, L"(A7) Me FW Downgrade - Request MeSpiLock Failed\n");
    break;

  case MSG_HMRFPO_UNLOCK_FAILURE:
    gST->ConOut->OutputString (gST->ConOut, L"(A7) Me FW Downgrade - Request MeSpiEnable Failed\n");
    break;

  case MSG_ME_FW_UPDATE_WAIT:
    gST->ConOut->OutputString (
                  gST->ConOut,
                  L"Intel(R) Firmware Update is in progress. It may take up to 90 seconds. Please wait.\n"
                  );
    break;

  case MSG_ILLEGAL_CPU_PLUGGED_IN:
    gST->ConOut->OutputString (
                  gST->ConOut,
                  L"\n\n\rAn unsupported CPU/PCH configuration has been identified.\n"
                  );
    gST->ConOut->OutputString (
                  gST->ConOut,
                  L"\rPlease refer to the Haswell Platform Validation Matrix\n\rfor supported CPU/PCH combinations."
                  );
    break;

  case MSG_KVM_WAIT:
    gST->ConOut->OutputString (gST->ConOut, L"Waiting Up to 8 Minutes For KVM FW.....");
    break;

  case MSG_PLAT_DISABLE_WAIT:
    gST->ConOut->OutputString (gST->ConOut, L"WARNING! Firmware encountered errors and will reboot the platform in 30 minutes.");
    MsgDelay = 5 * HECI_MSG_DELAY;
    break;

  default:
    DEBUG ((EFI_D_ERROR, "This Message Id hasn't been defined yet, MsgId = %x\n", MsgId));
    break;
  }

  gBS->Stall (MsgDelay);
  GraphicsRestore();
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
