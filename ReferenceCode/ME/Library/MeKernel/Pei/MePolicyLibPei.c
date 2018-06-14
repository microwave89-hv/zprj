/** @file
  Implementation file for Me Policy functionality for PEIM

@copyright
  Copyright (c) 2006 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "MePolicyLibPei.h"
#endif

/**
  Check if Me is enabled.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] PeiMePlatformPolicy  The Me Platform Policy protocol instance

  @retval EFI_SUCCESS             ME platform policy Ppi loacted
  @retval All other error conditions encountered when no ME platform policy Ppi
**/
EFI_STATUS
PeiMePolicyLibInit (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  PEI_ME_PLATFORM_POLICY_PPI  **PeiMePlatformPolicy
  )
{
  EFI_STATUS  Status;

  //
  // Locate system configuration variable
  //
  Status = PeiServicesLocatePpi (
            &gPeiMePlatformPolicyPpiGuid, // GUID
            0,                            // INSTANCE
            NULL,                         // EFI_PEI_PPI_DESCRIPTOR
            (VOID **) PeiMePlatformPolicy // PPI
            );
  ASSERT_EFI_ERROR (Status);
  return Status;
}
