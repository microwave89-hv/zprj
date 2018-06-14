/** @file
  Header file to define some function for getting the Intel ME policy PEI phase.

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
#ifndef _PEI_ME_POLICY_LIB_H_
#define _PEI_ME_POLICY_LIB_H_

#include EFI_PPI_DEFINITION (MePlatformPolicyPei)

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
;

#endif
