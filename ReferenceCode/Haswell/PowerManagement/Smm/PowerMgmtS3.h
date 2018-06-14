/** @file
  Header file for PpmS3 Smm Driver.

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
#ifndef _POWER_MGMT_S3_SMM_H_
#define _POWER_MGMT_S3_SMM_H_

#include "EdkIIGlueDxe.h"
#include "EfiScriptLib.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"

#define PPM_WAIT_PERIOD 15

typedef struct _EFI_MSR_VALUES {
  UINT16  Index;
  UINT64  Value;
  UINT64  BitMask;
  BOOLEAN RestoreFlag;
} EFI_MSR_VALUES;

/**
  Runs the specified procedure on all logical processors, passing in the
  parameter buffer to the procedure.

  @param[in] Procedure     The function to be run.
  @param[in] Buffer        Pointer to a parameter buffer.

  @retval EFI_SUCCESS
**/
STATIC
EFI_STATUS
RunOnAllLogicalProcessors (
  IN OUT EFI_AP_PROCEDURE Procedure,
  IN OUT VOID             *Buffer
  );
/**
  This function will restore MSR settings.

  This function must be MP safe.

  @param[in] Buffer        Unused

  @retval EFI_SUCCESS   MSR restored
**/
VOID
EFIAPI
ApSafeRestoreMsr (
  IN OUT VOID *Buffer
  );

#endif
