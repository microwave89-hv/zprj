/** @file
  Describes the functions visible to the rest of the PfatInit.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
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
#ifndef _PFAT_INIT_H_
#define _PFAT_INIT_H_

#include "PfatDefinitions.h"
#include EFI_PPI_DEFINITION (CpuPlatformPolicy)

///
/// Function Prototypes
///
/**
  Execute Early-Post initialization of PFAT specific MSRs

  @param[in] PeiServices          - Indirect reference to the PEI Services Table.
  @param[in] CpuPlatformPolicyPpi - Platform Policy PPI
**/
VOID
PfatInit (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN PEI_CPU_PLATFORM_POLICY_PPI *CpuPlatformPolicyPpi
  );

#endif
