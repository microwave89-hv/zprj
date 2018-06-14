/** @file
  Header file for the SA Dmi Init library.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
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
#ifndef _SA_DMI_PEIM_H_
#define _SA_DMI_PEIM_H_

#include "EdkIIGluePeim.h"
#include "SaAccess.h"
#include "CpuRegs.h"
#include "CpuPlatformLib.h"

///
/// Driver Consumed PPI Prototypes
///
#include EFI_PPI_DEPENDENCY (SaPlatformPolicy)
#include EFI_PPI_DEPENDENCY (PchPlatformPolicy)
#include EFI_PPI_DEPENDENCY (PchInit)
#include EFI_PPI_DEPENDENCY (PchDmiTcVcMap)

/**
  Map SA DMI TCs to VC

  @param[in] PchDmiTcVcMapPpi     - Instance of PCH_DMI_TC_VC_PPI
  @param[in] DmiBar               - DMIBAR address

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaSetDmiTcVcMapping (
  IN    PCH_DMI_TC_VC_PPI  *PchDmiTcVcMapPpi,
  IN    UINT64             DmiBar
  )
;

/**
  Poll SA DMI negotiation completion

  @param[in] PchDmiTcVcMapPpi     - Instance of PCH_DMI_TC_VC_PPI
  @param[in] DmiBar               - DMIBAR address

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaPollDmiVcStatus (
  IN    PCH_DMI_TC_VC_PPI  *PchDmiTcVcMapPpi,
  IN    UINT64             DmiBar
  )
;

#ifdef DMI_FLAG
/**
  DMI link training

  @param[in] DmiBar - DMIBAR address
**/
VOID
DmiLinkTrain (
  IN  UINT64 DmiBar
  )
;

/**
  Additional DMI Programming Steps at PEI

  @param[in] SaPlatformPolicyPpi - pointer to SA_PLATFORM_POLICY_PPI
  @param[in] MchBar              - MCHBAR address
  @param[in] DmiBar              - DMIBAR address
**/
VOID
AdditionalDmiProgramSteps (
  IN SA_PLATFORM_POLICY_PPI    *SaPlatformPolicyPpi,
  IN UINT32                    MchBar,
  IN UINT32                    DmiBar
  )
;
#endif // DMI_FLAG
#endif
