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

  MePeiPolicyInit.c
  
Abstract: 
  
  This file is SampleCode for Intel ME PEI Platform Policy initialzation.

--*/
#include <Token.h>
#include "MePeiPolicyInit.h"
#include <Ppi\PchPlatformPolicy\PchPlatformPolicy.h>
#include <SetupDataDefinition.h>

#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }
static EFI_GUID	   gSetupGuid = SETUP_GUID;


//
// Function implementations
//
VOID
PrepareThermalHob (
  IN EFI_PEI_SERVICES          **PeiServices
)
{
  EFI_STATUS                 Status;
  EFI_HOB_GUID_TYPE          *Hob;
  UINT8                      TsOnDimm[4];
  EFI_GUID                   gPchPolicyPpiGuid = PCH_PLATFORM_POLICY_PPI_GUID;
  PCH_PLATFORM_POLICY_PPI    *PchPlatformPolicy;
  EFI_GUID                   gDimmTsInfoGuid = DIMM_TS_INFO_GUID;

  Status = (**PeiServices).LocatePpi (PeiServices, &gPchPolicyPpiGuid, 0,
                      NULL, (VOID **)&PchPlatformPolicy);

  if(EFI_ERROR(Status))
  {
    return;
  }
  // Build the GUID'd HOB for DXE
  Status = (*PeiServices)->CreateHob (
                             PeiServices,
                             EFI_HOB_TYPE_GUID_EXTENSION,
                             (UINT16) (sizeof (EFI_HOB_GUID_TYPE) + 4),
                             &Hob
                             );

  if (EFI_ERROR (Status))return;

  ((EFI_HOB_GUID_TYPE *)(Hob))->Name = gDimmTsInfoGuid;

  Hob++;

//-   TsOnDimm[0] = PchPlatformPolicy->ThermalReportConfig->ThermalReportControl->Dimm1TempReadEnable;
//-   TsOnDimm[1] = PchPlatformPolicy->ThermalReportConfig->ThermalReportControl->Dimm2TempReadEnable;
//-   TsOnDimm[2] = PchPlatformPolicy->ThermalReportConfig->ThermalReportControl->Dimm3TempReadEnable;
//-   TsOnDimm[3] = PchPlatformPolicy->ThermalReportConfig->ThermalReportControl->Dimm4TempReadEnable;

  GlueCopyMem (Hob, TsOnDimm, sizeof(TsOnDimm));

}

EFI_STATUS
MePeiPolicyInitEntryPoint (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
/*++

Routine Description:

  Initilize Intel ME PEI Platform Policy
  
Arguments:

  FfsHeader               Pointer to Firmware File System file header.
  PeiServices             General purpose services available to every PEIM.

Returns:

  EFI_STATUS
  
--*/
{
  EFI_STATUS                  Status;
  PEI_ME_PLATFORM_POLICY_PPI  *MePlatformPolicyPpi;
  EFI_PEI_PPI_DESCRIPTOR      *MePlatformPolicyPpiDesc;
  EFI_PEI_READ_ONLY_VARIABLE_PPI       *VariableServices;
  UINTN                                 VariableSize;
  SETUP_DATA                            SetupData;

  //
  // Allocate descriptor and PPI structures
  //
  MePlatformPolicyPpi = (PEI_ME_PLATFORM_POLICY_PPI *) AllocateZeroPool (sizeof (PEI_ME_PLATFORM_POLICY_PPI));
  ASSERT (MePlatformPolicyPpi != NULL);
  if (MePlatformPolicyPpi == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  MePlatformPolicyPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  ASSERT (MePlatformPolicyPpiDesc != NULL);
  if (MePlatformPolicyPpiDesc == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Locate Variable Ppi
  //
  Status = (*PeiServices)->LocatePpi(PeiServices,
                                     &gPeiReadOnlyVariablePpiGuid,
                                     0,
                                     NULL,
                                     &VariableServices);

  //
  // Make sure we have a PPI, if not, just return.
  //
  if (!VariableServices) {
   	return EFI_UNSUPPORTED;
  }
  VariableSize = sizeof(SETUP_DATA);
  //
  // Get Setup Variable
  //
  Status = VariableServices->PeiGetVariable (
                    PeiServices,
                    L"Setup",
                    &gSetupGuid,
                    NULL,
                    &VariableSize,
                    &SetupData);

  //
  // Update Itnel PPT 
  // 
  if ( !EFI_ERROR(Status) ) {
#if IntelPTT_SUPPORT
    MePlatformPolicyPpi->FTpmSwitch = SetupData.FTpmSwitch;
#else
    MePlatformPolicyPpi->FTpmSwitch = 0;
#endif
  } else {
    MePlatformPolicyPpi->FTpmSwitch = 0;
  }

  //
  // Initialize the PPI
  //
  MePlatformPolicyPpiDesc->Flags  = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  MePlatformPolicyPpiDesc->Guid   = &gPeiMePlatformPolicyPpiGuid;

  //
  // Update the REVISION number
  //
  MePlatformPolicyPpi->Revision = PEI_ME_PLATFORM_POLICY_PPI_REVISION_2;


  //
  // Initialize the Platform Configuration
  //
// Debug  UpdatePeiMePlatformPolicy (PeiServices, MePlatformPolicyPpi);

  MePlatformPolicyPpiDesc->Ppi = MePlatformPolicyPpi;

  ///
  /// TBD put initialize codes in here if needs
  ///
  ///
  /// Install the ME PEI Platform Policy PPI
  ///
  Status = (**PeiServices).InstallPpi (PeiServices, MePlatformPolicyPpiDesc);
  ASSERT_PEI_ERROR (PeiServices, Status);
  DEBUG ((EFI_D_INFO, "ME PEI Platform Policy PPI Installed\n"));

  return Status;
}
