/*++
  This file contains a 'Sample Driver' and is licensed as such  
  under the terms of your license agreement with Intel or your  
  vendor.  This file may be modified by the user, subject to    
  the additional terms of the license agreement                 
--*/

/*++

Copyright (c)  1999 - 2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  AmtPeiPolicyInit.c
  
Abstract: 
  
  This file is SampleCode for Intel AMT PEI Platform Policy initialzation.

--*/
#include "AmtPeiPolicyInit.h"

#if EFI_SPECIFICATION_VERSION>0x20000
#define __UEFI_HII__H__
#define __HII_CONFIG_ACCESS__H__
#include EFI_PROTOCOL_DEFINITION (HiiConfigAccess)
#else
#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif
#define __UEFI_HII__H__
#define __HII_PROTOCOL_H__
#define _HII_H_
#endif

#include <Setup.h>

#include EFI_PPI_DEFINITION     (Variable)
#include EFI_GUID_DEFINITION    (MeBiosExtensionSetup)
#include <ActiveManagement\AlertStandardFormat\Heci\Common\AlertStandardFormatCommon.h>
#include <Guid\AmtForcePushPetPolicy\AmtForcePushPetPolicy.h>

EFI_GUID gSetupGuid = SETUP_GUID;
EFI_GUID gEfiMeBiosExtensionSetupGuid = EFI_ME_BIOS_EXTENSION_SETUP_GUID;
CHAR16   gEfiMeBiosExtensionSetupName[] = EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME;
EFI_GUID gPeiReadOnlyVariablePpiGuid = PEI_READ_ONLY_VARIABLE_ACCESS_PPI_GUID;
EFI_GUID gAmtForcePushPetPolicyGuid = AMT_FORCE_PUSH_PET_POLICY_GUID;

EFI_STATUS
CreateAmtForcePushPetPolicyHob(
    IN EFI_PEI_SERVICES         **PeiServices
);

//
// Function implementations
//
EFI_STATUS
AmtPeiPolicyInitEntryPoint (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
/*++

Routine Description:

  Initilize Intel AMT PEI Platform Policy

Arguments:

  FfsHeader               Pointer to Firmware File System file header.
  PeiServices             General purpose services available to every PEIM.

Returns:

  EFI_STATUS
  
--*/
{
  EFI_STATUS                  Status;
  PEI_AMT_PLATFORM_POLICY_PPI *AmtPlatformPolicyPpi;
  EFI_PEI_PPI_DESCRIPTOR      *AmtPlatformPolicyPpiDesc;
  EFI_PEI_READ_ONLY_VARIABLE_PPI        *VariableServices;
  UINTN                                 VariableSize;
  SETUP_DATA                            SetupData;
  ME_BIOS_EXTENSION_SETUP               MeBiosExtensionSetupData;
  //
  // Allocate descriptor and PPI structures
  //
  AmtPlatformPolicyPpi = (PEI_AMT_PLATFORM_POLICY_PPI *) AllocateZeroPool (sizeof (PEI_AMT_PLATFORM_POLICY_PPI));
  ASSERT (AmtPlatformPolicyPpi != NULL);
  if (AmtPlatformPolicyPpi == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  AmtPlatformPolicyPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  ASSERT (AmtPlatformPolicyPpiDesc != NULL);
  if (AmtPlatformPolicyPpiDesc == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Initialize the PPI
  //
  AmtPlatformPolicyPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  AmtPlatformPolicyPpiDesc->Guid  = &gPeiAmtPlatformPolicyPpiGuid;

  // Locate Variable Ppi
  Status = (*PeiServices)->LocatePpi (PeiServices, &gPeiReadOnlyVariablePpiGuid, 0, NULL, &VariableServices);

  //
  // Make sure we have a PPI, if not, just return.
  //
  if (!VariableServices) {
    return EFI_SUCCESS;
  }
  //
  // Get Setup Variable
  //

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->PeiGetVariable (
                              PeiServices,
                              L"Setup",
                              &gSetupGuid,
                              NULL,
                              &VariableSize,
                              &SetupData
                              );
  //
  // Update the REVISION number
  //
  AmtPlatformPolicyPpi->Revision = PEI_AMT_PLATFORM_POLICY_PPI_REVISION_5;

  //
  // Initialize the Platform Configuration
  //
  if (Status != EFI_SUCCESS) {
    AmtPlatformPolicyPpi->iAmtEnabled        = 0;
    AmtPlatformPolicyPpi->WatchDog           = 0;
    AmtPlatformPolicyPpi->WatchDogTimerBios  = 0;
    AmtPlatformPolicyPpi->WatchDogTimerOs    = 0;
    AmtPlatformPolicyPpi->AsfEnabled         = 1;
    AmtPlatformPolicyPpi->FWProgress = 1;
  } else {
    AmtPlatformPolicyPpi->iAmtEnabled        = SetupData.Amt;
    AmtPlatformPolicyPpi->WatchDog           = SetupData.WatchDog;
    AmtPlatformPolicyPpi->WatchDogTimerBios  = SetupData.WatchDogTimerBios;
    AmtPlatformPolicyPpi->WatchDogTimerOs    = SetupData.WatchDogTimerOs;
    AmtPlatformPolicyPpi->AsfEnabled         = SetupData.Asf;
    AmtPlatformPolicyPpi->FWProgress         = SetupData.FWProgress;
  }

    //
    // Get BIOS Sync-up data from MEBx to AMT platform policy
    //    
    VariableSize = sizeof (MeBiosExtensionSetupData);
    Status = VariableServices->PeiGetVariable(
                                   PeiServices,
                                   gEfiMeBiosExtensionSetupName,
                                   &gEfiMeBiosExtensionSetupGuid,
                                   NULL,
                                   &VariableSize,
                                   &MeBiosExtensionSetupData
                                 );
    if (Status != EFI_SUCCESS) {
        AmtPlatformPolicyPpi->ManageabilityMode = 0;
    } else {
        AmtPlatformPolicyPpi->ManageabilityMode = MeBiosExtensionSetupData.PlatformMngSel;
    }

// Debug  UpdatePeiAmtPlatformPolicy (PeiServices, AmtPlatformPolicyPpi);

  AmtPlatformPolicyPpiDesc->Ppi = AmtPlatformPolicyPpi;
  //
  // Install the ME PEI Platform Policy PPI
  //
  Status = (**PeiServices).InstallPpi (PeiServices, AmtPlatformPolicyPpiDesc);
  ASSERT_PEI_ERROR (PeiServices, Status);

  CreateAmtForcePushPetPolicyHob(PeiServices);

  return Status;
}
EFI_FRAMEWORK_MESSAGE_TYPE mAmtForcePushPetPolicy[] = {
  EfiAsfMessageChassisIntrusion,
  EfiAsfMessageUserAuthenticationInvalid,
  EfiAsfMessageHddAuthenticationInvalid,
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CreateAmtForcePushPetPolicyHob
//
// Description: Create AMT force push pet policy HOB.
//
// Input:       IN EFI_PEI_SERVICES                   **PeiServices,
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CreateAmtForcePushPetPolicyHob(
IN    EFI_PEI_SERVICES    **PeiServices
)
{
  EFI_STATUS                 Status;
  EFI_HOB_GUID_TYPE          *Hob;

  // Build the GUID'd HOB for DXE
  Status = (*PeiServices)->CreateHob (
                             PeiServices,
                             EFI_HOB_TYPE_GUID_EXTENSION,
                             (UINT16) (sizeof (EFI_HOB_GUID_TYPE) + sizeof(mAmtForcePushPetPolicy)),
                             &Hob
                             );
  if (EFI_ERROR (Status))return Status;

  ((EFI_HOB_GUID_TYPE *)(Hob))->Name = gAmtForcePushPetPolicyGuid;

  Hob++;

  GlueCopyMem (Hob, mAmtForcePushPetPolicy, sizeof(mAmtForcePushPetPolicy));

  return EFI_SUCCESS;
}
