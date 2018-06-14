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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/TdtWrapper/TDTWrapper.c 12    6/18/14 3:04a Larryliu $
//
// $Revision: 12 $
//
// $Date: 6/18/14 3:04a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/TdtWrapper/TDTWrapper.c $
// 
// 12    6/18/14 3:04a Larryliu
// [TAG]  		EIP173999
// [Category]  	Improvement
// [Description]  	[HWR]Remove useless comments from Intel ME
// component.(except RC)
// [Files]  		TDTWrapper.c
// 
// 10    5/14/14 10:04p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 9     12/17/13 9:50p Tristinchou
// [TAG]  		EIP146961
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	After Initiated Resume, "Enter Intel AT Suspend Mode"
// option is still enable in Bios setup menu
// [RootCause]  	The conditional expression is never true to clean steup
// item.
// [Solution]  	Use MBP data to check AT status.
// 
// 8     6/21/13 3:08a Klzhan
// [TAG]  		EIP127189
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 1.60
// 
// 7     6/02/13 9:13a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Report PBA not support when AT is disabled.
// 
// 6     4/02/13 1:51a Klzhan
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Setup Variable crash
// [RootCause]  	Variable not been initialized.
// 
// 5     9/27/12 4:56a Klzhan
// [TAG]  		EIP102254
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 0.7
// [Files]  		TDTWrapper.dxs
// TDTWrapper.c
// TDTWrapper.mak
// TDTWrapper.sdl
// TDTSetup.sd
// TDTSetup.uni
// TdtCallback.h
// TDTWrapper.cif
// 
// 4     8/30/12 2:57a Klzhan
// 
// 3     4/24/12 3:33a Klzhan
// 
// 2     4/24/12 12:33a Klzhan
// Update modulepart to latest
// 
// 1     2/08/12 1:07a Klzhan
// Initial Check in 
// 
// 3     9/20/11 9:40a Klzhan
// Check TdtConfig by Wrapper not SetupData.
// 
// 2     4/21/11 2:58a Klzhan
// 
// 1     2/25/11 1:40a Klzhan
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
// Name:            TdtSetup.c
//
// Description:     Setup Hooks for Tdt.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

Copyright (c) 2004-2006 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  TDTPlatformPolicy.c
  
Abstract:

  TDTPlatformPolicy to check and set TDT Platform Policy.
  
--*/
/*++
 This file contains an 'Intel Peripheral Driver' and is        
 licensed for Intel CPUs and chipsets under the terms of your  
 license agreement with Intel or your vendor.  This file may   
 be modified by the user, subject to additional terms of the   
 license agreement                                             
--*/


//This needs to be merged with AMT Platform Policy. 

//
// Statements that include other files
//
//#include "Efi.h"


#include <EFI.h>
#include <AmiDxeLib.h>
#include <Protocol\SMBios.h>
#include <Include\Protocol\SmbiosGetFlashDataProtocol.h>
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
#include <Include\Protocol\LegacyRegion.h>
#endif
#include "Setup.h"
#include "ReferenceCode\ME\Protocol\AtPlatformPolicy\AtPlatformPolicy.h"
#include "MkhiMsgs.h"
#include "Protocol\MeBiosPayloadData\MeBiosPayloadData.h"
#include "TdtCallback.h"
#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
 { 0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93 }

#define ME_ALERT_AT_HANDLER_GUID {0xb441df87, 0x8d94, 0x4811, 0x85, 0xf7, 0xf, 0x9a, 0x7b, 0xf8, 0x9d, 0x2a}

#define SMB131_IDENTIFIER_OFFSET    0x38       
#define SMB131_ME_CAPS_OFFSET       0x18       
#define SMB131_AT_ENROLL_OFFSET     0x24
#define SMB131_BIOS_SEC_CAPS_OFFSET 0x34

EFI_GUID gSetupGuid                 = SETUP_GUID;
EFI_GUID gDxePlatformTdtPolicyGuid = DXE_PLATFORM_AT_POLICY_GUID;
EFI_GUID gEfiSmbiosProtocolGuid = EFI_SMBIOS_PROTOCOL_GUID;
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
EFI_GUID gEfiLegacyRegionProtocol = EFI_LEGACY_REGION_PROTOCOL_GUID;
#endif
EFI_GUID gBdsAllDriversConnectedProtocolGuid = \
                                    BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
EFI_GUID gMEAlertATHandlerGuid = ME_ALERT_AT_HANDLER_GUID;
EFI_EVENT                           mReady2BootEvent;
EFI_RUNTIME_SERVICES                *gRT;
EFI_BOOT_SERVICES                   *gBS;

DXE_AT_POLICY_PROTOCOL *TDTPlatformPolicyInstance;

#define EFI_TPL_DRIVER              6
#define EFI_TPL_APPLICATION         4
#define EFI_TPL_CALLBACK            8
#define EFI_TPL_NOTIFY              16
#define EFI_TPL_HIGH_LEVEL          31

VOID
EFIAPI
TDTEventModSmbiosType131 (
  IN    EFI_EVENT           Event,
  IN    VOID                *Context
);

DXE_MBP_DATA_PROTOCOL     *mBIOSPayLoad;
VOID NullFunction( 
  EFI_EVENT   Event, 
  VOID        *ParentImageHandle 
)
{
    return;
}

//
// Function implementations
//
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TxtExitSetupEvent
//
// Description: This routine for reset the TPM Establishment flag.
//
// Input:       EFI_EVENT   - Efi event.
//              VOID*       - Image handle.
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
TdtAllDriverConnectEvent  (
    IN EFI_EVENT            Event,
    IN VOID                 *ParentImageHandle
)
{
    EFI_STATUS          Status;
    EFI_EVENT           MEAlertAT;
    UINT32              SetupVarAttr;
    EFI_GUID            TdtSetupDataGuid = TDT_VOLATILE_SETUP_DATA_GUID;
    TDT_VOLATILE_SETUP_DATA  TdtSetupData;
    SETUP_DATA          SetupData;
    UINTN               VariableSize = sizeof(SETUP_DATA);

    // Get current Setup Data.
    Status = gRT->GetVariable( L"Setup",
                               &gSetupGuid,
                               &SetupVarAttr,
                               &VariableSize,
                               &SetupData );
    if( !EFI_ERROR(Status) )
    {
        if( (mBIOSPayLoad->MeBiosPayload.AtState.State == AT_STATE_INACTIVE) &&
            (SetupData.TdtEnterSuspendState != 0) )
        {
            SetupData.TdtEnterSuspendState = 0;
            Status = gRT->SetVariable ( L"Setup",
                                        &gSetupGuid,
                                        SetupVarAttr,
                                        VariableSize,
                                        &SetupData );
        }
    }

    TdtSetupData.TdtEnroll = 0;
    if (mBIOSPayLoad->MeBiosPayload.AtState.State != 0) TdtSetupData.TdtEnroll = 1;
    Status = gRT->SetVariable ( TDT_VOLATILE_SETUP_DATA_C_NAME, \
                                &TdtSetupDataGuid, \
                                EFI_VARIABLE_NON_VOLATILE | \
                                EFI_VARIABLE_BOOTSERVICE_ACCESS, \
                                sizeof(TDT_VOLATILE_SETUP_DATA), \
                                &TdtSetupData    );
    // Signal Event To support New AT AM module.
    Status = gBS->CreateEventEx(
          EFI_EVENT_NOTIFY_SIGNAL,
          EFI_TPL_NOTIFY,
          NullFunction,
          NULL,
          &gMEAlertATHandlerGuid,
          &MEAlertAT); 
    gBS->SignalEvent(MEAlertAT);
    gBS->CloseEvent(MEAlertAT);
    return EFI_SUCCESS;
}
VOID LocateMBP(IN EFI_EVENT Event, IN VOID *Context)
{
    pBS->LocateProtocol (&gMeBiosPayloadDataProtocolGuid, NULL, &mBIOSPayLoad);
}
EFI_STATUS
EFIAPI
TdtWrapperEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
/*++
 
Routine Description:
 
  Entry point for the TDTPlatformPolicy Driver.
  
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
  EFI_STATUS                    Status;
  EFI_GUID                      gSetupGuid = SETUP_GUID;
  UINT32                        SetupVarAttr;
  UINTN                         VariableSize = 0;
  SETUP_DATA                    SetupDataBuffer;
  SETUP_DATA*                   SetupData = &SetupDataBuffer;
  EFI_EVENT                     AllDriverConnectEvent;
  VOID                          *Registration;
  EFI_GUID            TdtSetupDataGuid = TDT_VOLATILE_SETUP_DATA_GUID;
  TDT_VOLATILE_SETUP_DATA  TdtSetupData;
  //
  // Initialize the EFI Driver Library
  //
 
  VariableSize = sizeof (SETUP_DATA);
  InitAmiLib(ImageHandle, SystemTable);
  gBS = SystemTable->BootServices;
  gRT = SystemTable->RuntimeServices;

    Status = gBS->LocateProtocol(&gMeBiosPayloadDataProtocolGuid, NULL, &mBIOSPayLoad);
    if (EFI_ERROR (Status))
    {
        EFI_EVENT   AmiCpuInfoEvt;
        VOID        *CpuNotifyReg;

        Status = RegisterProtocolCallback(
            &gMeBiosPayloadDataProtocolGuid,
            LocateMBP,
            NULL,
            &AmiCpuInfoEvt,
            &CpuNotifyReg
        );
    }
  //
  // Allocate Ide private data structure
  //
  Status = gBS->AllocatePool (
                EfiBootServicesData,
                sizeof (DXE_AT_POLICY_PROTOCOL),
                (VOID**)&TDTPlatformPolicyInstance
                );
  if (EFI_ERROR(Status))
    return EFI_OUT_OF_RESOURCES;

  //
  // Get TDT BIOS Setup 
  //	
  Status = gRT->GetVariable (
    L"Setup",
    &gSetupGuid,
    &SetupVarAttr,
    &VariableSize,
    &SetupDataBuffer
    );
  VariableSize = sizeof(TDT_VOLATILE_SETUP_DATA);
  Status = gRT->GetVariable ( TDT_VOLATILE_SETUP_DATA_C_NAME, \
                              &TdtSetupDataGuid, \
                              NULL, \
                              &VariableSize, \
                              &TdtSetupData    );
  // If Tdt is in Enroll state, Set Tdt config to Enable.
  if((!EFI_ERROR(Status)) && (TdtSetupData.TdtEnroll == 1))
  {
    SetupData->TdtConfig = 1;
    Status = gRT->SetVariable ( L"Setup", \
                                &gSetupGuid, \
                                SetupVarAttr, \
                                sizeof(SETUP_DATA), \
                                &SetupDataBuffer    );
  }
  if (EFI_ERROR(Status)){
    TDTPlatformPolicyInstance->At.AtAmBypass             = 1;
    TDTPlatformPolicyInstance->At.AtEnterSuspendState    = 0;
    TDTPlatformPolicyInstance->At.AtSupported            = 1;
    TDTPlatformPolicyInstance->At.AtPba                  = 1;
  } else {
    TDTPlatformPolicyInstance->At.AtAmBypass             = SetupData->TdtConfig == 1 ? 0 : 1;
    TDTPlatformPolicyInstance->At.AtEnterSuspendState    = SetupData->TdtEnterSuspendState;
    TDTPlatformPolicyInstance->At.AtSupported            = 1;
    TDTPlatformPolicyInstance->At.AtPba                  = 1;
  }
    TDTPlatformPolicyInstance->Revision                   = DXE_PLATFORM_AT_POLICY_PROTOCOL_REVISION_2;

  //
  // Install the TDT Platform Policy PROTOCOL interface
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
               &ImageHandle,
               &gDxePlatformTdtPolicyGuid,	TDTPlatformPolicyInstance,
               NULL
             );
  // If TDT support is disabled in BIOS SETUP, clear the AT support flag of 
  // SMBIOS TYPE131 to avoid that system can be enrolled.
  Status = RegisterProtocolCallback ( &gBdsAllDriversConnectedProtocolGuid, \
                                      TdtAllDriverConnectEvent, \
                                      NULL, \
                                      &AllDriverConnectEvent, \
                                      &Registration   );
                                    
  // If TDT support is disabled in BIOS SETUP, clear the AT support flag of 
  // SMBIOS TYPE131 to avoid that system can be enrolled.
  Status = CreateReadyToBootEvent ( TPL_CALLBACK - 1, \
                                    TDTEventModSmbiosType131, \
                                    NULL, \
                                    &mReady2BootEvent   );

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	TDTEventModSmbiosType131
//
// Description:	This routine clear the AT support flag of Type 131.
//
// Input:
//  IN EFI_EVENT Event - signalled event
//  IN VOID *Context - event context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>                   
VOID
EFIAPI
TDTEventModSmbiosType131 (
  IN    EFI_EVENT           Event,
  IN    VOID                *Context
)
{
    EFI_STATUS                  Status;
    EFI_SMBIOS_PROTOCOL         *mSmbiosProtocol;
    SMBIOS_TABLE_ENTRY_POINT    *SmbTblEntry;
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
    EFI_LEGACY_REGION_PROTOCOL* iRegion;			
#endif
    UINT16                      i, MeCaps, AtEnroll, BiosSecurityCaps; 
    UINT8*                      pStrucPtr; 
    UINTN                       VariableSize = sizeof(TDT_VOLATILE_SETUP_DATA);
    EFI_GUID            TdtSetupDataGuid = TDT_VOLATILE_SETUP_DATA_GUID;
    TDT_VOLATILE_SETUP_DATA  TdtSetupData;

    Status = gBS->LocateProtocol (  &gEfiSmbiosProtocolGuid, \
                                    NULL, \
                                    &mSmbiosProtocol    );
    if (EFI_ERROR(Status)) return ;

    Status = gRT->GetVariable ( TDT_VOLATILE_SETUP_DATA_C_NAME, \
                                &TdtSetupDataGuid, \
                                NULL, \
                                &VariableSize, \
                                &TdtSetupData );
    if (EFI_ERROR(Status)) return ;

    // Get SMBIOS Table Entry Point.
    SmbTblEntry = mSmbiosProtocol->SmbiosGetTableEntryPoint ();

    // Search SMBIOS Type 131.
    for ( pStrucPtr = (UINT8*)SmbTblEntry->TableAddress, i = 0; \
          i < SmbTblEntry->TableLength; i++ ) {
        // search SMBIOS Type 131 structure identifier - vPro    
        if ( *(UINT32*)(pStrucPtr + i) != 0x6f725076 ) continue;
        // Pointer to ME Capabilities field.
        MeCaps = i - (SMB131_IDENTIFIER_OFFSET - SMB131_ME_CAPS_OFFSET);
        AtEnroll = i - (SMB131_IDENTIFIER_OFFSET - SMB131_AT_ENROLL_OFFSET);
        BiosSecurityCaps = i - (SMB131_IDENTIFIER_OFFSET - SMB131_BIOS_SEC_CAPS_OFFSET);
        if (*(UINT32*)(pStrucPtr + MeCaps) & BIT13) {
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
            Status = pBS->LocateProtocol (  &gEfiLegacyRegionProtocol, \
                                            NULL, \
                                            &iRegion );
            if (EFI_ERROR(Status)) return ;
            // Unlock Shadow ram.
            iRegion->UnLock ( iRegion, 0xE0000, 0x20000, NULL );
#endif
            // AT-P is disabled in SETUP, clear the AT-p support flag to avoid 
            // that system can be enrolled.
            if (TDTPlatformPolicyInstance->At.AtAmBypass == 1) 
            {
                *(UINT32*)(pStrucPtr + MeCaps) &= ~BIT13; 
                *(UINT32*)(pStrucPtr + BiosSecurityCaps) &= ~BIT6; 
            }
            // Set AT is configured if AT is enrolled.
            if (TdtSetupData.TdtEnroll != 0) 
                *(UINT8*)(pStrucPtr + AtEnroll) |= BIT5; 
            // Lock Shadow ram.
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
            iRegion->Lock ( iRegion, 0xE0000, 0x20000, NULL );
#endif
        }
        break;
    }        
    return ;
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
