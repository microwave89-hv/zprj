/*++
  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/*++

Copyright (c)  2006 - 2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  HeciHpet.h

Abstract:

  Definitions for HECI driver

--*/
#ifndef _HECI_HPET_H
#define _HECI_HPET_H

#include "EdkIIGlueDxe.h"
#include "MeAccess.h"
#include "HeciRegs.h"
#include "Pci22.h"

#define HECI_PRIVATE_DATA_SIGNATURE         EFI_SIGNATURE_32 ('H', 'e', 'c', 'i')
#define HECI_ROUND_UP_BUFFER_LENGTH(Length) ((UINT32) ((((Length) + 3) / 4) * 4))

//
// Driver Produced Protocol Prototypes
//
#include EFI_PROTOCOL_PRODUCER (HeciSmm)

VOID
SaveHpet (
  VOID
  )
/*++

Routine Description:

  Store the value of High Performance Timer

Arguments:

  None

Returns:

  None

--*/
;

VOID
RestoreHpet (
  VOID
  )
/*++

Routine Description:

  Restore the value of High Performance Timer

Arguments:

  None

Returns:

  None

--*/
;

VOID
StartTimer (
  OUT UINT32 *Start,
  OUT UINT32 *End,
  IN  UINT32 Time
  )
/*++

  Routine Description:

    Used for calculating timeouts

  Arguments:

    Start - Snapshot of the HPET timer
    End   - Calculated time when timeout period will be done
    Time  - Timeout period in microseconds

  Returns:

    VOID

--*/
;

EFI_STATUS
Timeout (
  IN  UINT32 Start,
  IN  UINT32 End
  )
/*++

  Routine Description:
    Used to determine if a timeout has occured.

  Arguments:
    Start - Snapshot of the HPET timer when the timeout period started.
    End   - Calculated time when timeout period will be done.

  Returns:
    EFI_STATUS

--*/
;

VOID
EnableHpet (
  VOID
  )
/*++

Routine Description:

  Enable Hpet function.

Arguments:

  None.

Returns:

  None.

--*/
;

VOID
IoDelay (
  UINT32 delayTime
  )
/*++

Routine Description:

  Delay for at least the request number of microseconds

Arguments:

  delayTime - Number of microseconds to delay.

Returns:

  None.

--*/
;

VOID
SmmStall (
  IN  UINTN   Microseconds
  )
/*++

Routine Description:

  Delay for at least the request number of microseconds.
  Timer used is DMA refresh timer, which has 15us granularity.
  You can call with any number of microseconds, but this 
  implementation cannot support 1us granularity.
    
Arguments:

  Microseconds - Number of microseconds to delay.

Returns:

  None

--*/
;
#endif // _HECI_HPET_H
