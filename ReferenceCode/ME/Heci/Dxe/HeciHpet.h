/** @file
  Definitions for HECI driver

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
#ifndef _HECI_HPET_H
#define _HECI_HPET_H

#include "EdkIIGlueDxe.h"
#include "MeAccess.h"
#include "HeciRegs.h"
#include "Pci22.h"

/**
  Store the value of High Performance Timer

  @param[in] None

  @retval None
**/
VOID
SaveHpet (
  VOID
  )
;

/**
  Restore the value of High Performance Timer

  @param[in] None

  @retval None
**/

VOID
RestoreHpet (
  VOID
  )
;

/**
  Used for calculating timeouts

  @param[out] Start               Snapshot of the HPET timer
  @param[out] End                 Calculated time when timeout period will be done
  @param[in] Time                 Timeout period in microseconds

  @retval None
**/
VOID
StartTimer (
  OUT UINT32                      *Start,
  OUT UINT32                      *End,
  IN  UINT32                      Time
  )
;

/**
  Used to determine if a timeout has occured.

  @param[in] Start                Snapshot of the HPET timer when the timeout period started.
  @param[in] End                  Calculated time when timeout period will be done.

  @retval EFI_TIMEOUT             Timeout occured.
  @retval EFI_SUCCESS             Not yet timed out
**/
EFI_STATUS
Timeout (
  IN  UINT32                      Start,
  IN  UINT32                      End
  )
;

/**
  Enable Hpet function.

  @param[in] None.

  @retval None
**/
VOID
EnableHpet (
  VOID
  )
;

/**
  Delay for at least the request number of microseconds

  @param[in] delayTime            Number of microseconds to delay.

  @retval None
**/
VOID
IoDelay (
  IN UINT32                       delayTime
  )
;

#endif // _HECI_HPET_H
