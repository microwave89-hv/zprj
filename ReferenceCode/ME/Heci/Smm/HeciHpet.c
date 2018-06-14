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

  HeciHpet.c

Abstract:

  Definitions for HECI driver

--*/
#include "HeciHpet.h"
#include "HeciRegs.h"
#include "HeciCore.h"

//
// Extern for shared HECI data and protocols
//
extern HECI_INSTANCE_SMM  *mHeciContext;
VOLATILE UINT32           mSaveHpetConfigReg;

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
{
  mSaveHpetConfigReg = MmioRead32 (PCH_RCRB_BASE + R_PCH_RCRB_HPTC);
}

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
{
  MmioWrite32 (PCH_RCRB_BASE + R_PCH_RCRB_HPTC, mSaveHpetConfigReg);
}

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
{
  UINT32  Ticks;

  //
  // Make sure that HPET is enabled and running
  //
  EnableHpet ();

  //
  // Read current timer value into start time from HPET
  //
  *Start = mHeciContext->HpetTimer[HPET_MAIN_COUNTER_LOW];

  //
  // Convert microseconds into 70ns timer ticks
  //
  Ticks = Time * HPET_TICKS_PER_MICRO;

  //
  // Compute end time
  //
  *End = *Start + Ticks;

  return ;
}

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
{
  UINT32  Current;

  //
  // Read HPET and assign the value as the current time.
  //
  Current = mHeciContext->HpetTimer[HPET_MAIN_COUNTER_LOW];

  //
  // Test basic case (no overflow)
  //
  if ((Start < End) && (End <= Current)) {
    return EFI_TIMEOUT;
  }
  //
  // Test basic start/end conditions with overflowed timer
  //
  if ((Start < End) && (Current < Start)) {
    return EFI_TIMEOUT;
  }
  //
  // Test for overflowed start/end condition
  //
  if ((Start > End) && ((Current < Start) && (Current > End))) {
    return EFI_TIMEOUT;
  }
  //
  // Catch corner case of broken arguments
  //
  if (Start == End) {
    return EFI_TIMEOUT;
  }
  //
  // Else, we have not yet timed out
  //
  return EFI_SUCCESS;
}

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
{
  SmmStall (delayTime);
}

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
{
  UINT8 Data;
  UINT8 InitialState;
  UINTN CycleIterations;

  CycleIterations = 0;
  Data            = 0;
  InitialState    = 0;

  //
  // The time-source is 15 us granular, so calibrate the timing loop
  // based on this baseline
  // Error is possible 15us.
  //
  CycleIterations = (Microseconds / 15) + 1;

  //
  // Use the DMA Refresh timer in port 0x61.  Cheap but effective.
  // The only issue is that the granularity is 15us, and we want to
  // guarantee "at least" one full transition to avoid races.
  //
  //
  //   _____________/----------\__________/--------
  //
  //                |<--15us-->|
  //
  // --------------------------------------------------> Time (us)
  //
  while (CycleIterations--) {
    Data          = IoRead8 (0x61);
    InitialState  = Data;

    //
    // Capture first transition (strictly less than one period)
    //
    while (InitialState == Data) {
      Data = IoRead8 (0x61);
    }

    InitialState = Data;
    //
    // Capture next transition (guarantee at least one full pulse)
    //
    while (InitialState == Data) {
      Data = IoRead8 (0x61);
    }
  }
}
