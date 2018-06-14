/** @file

This file defines the Low Power Idle Table definition, defined by
Intel IA-PC LPIT (Low Power Idle Table) Specification draft.

@copyright 
Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
This file contains an 'Intel Peripheral Driver' and is
licensed for Intel CPUs and chipsets under the terms of your
license agreement with Intel or your vendor. This file may
be modified by the user, subject to additional terms of the
license agreement

**/

#ifndef _LOW_POWER_IDLE_TABLE_H_
#define _LOW_POWER_IDLE_TABLE_H_

//
// Include files
//
#include "Acpi2_0.h"

//
// LPIT Definitions
//

#define EFI_ACPI_LOW_POWER_IDLE_TABLE_REVISION 0x1

//
// Ensure proper structure formats
//
#pragma pack(1)

typedef union _EFI_ACPI_LPI_STATE_FLAGS {
  struct {
    UINT32 Disabled           :1;
    UINT32 CounterUnavailable :1;
    UINT32 Reserved           :30;
  };
  UINT32 AsUlong;
} EFI_ACPI_LPI_STATE_FLAGS, *PEFI_ACPI_LPI_STATE_FLAGS;

// Only Mwait LPI here:

typedef struct _EFI_ACPI_MWAIT_LPI_STATE_DESCRIPTOR {
  UINT32 Type;        // offset: 0
  UINT32 Length;      // offset: 4
  UINT16 UniqueId;    // offset: 8
  UINT8 Reserved[2]; // offset: 10
  EFI_ACPI_LPI_STATE_FLAGS Flags; // offset: 12
  EFI_ACPI_2_0_GENERIC_ADDRESS_STRUCTURE EntryTrigger; // offset: 16
  UINT32 Residency;  // offset: 28
  UINT32 Latency; // offset: 32
  EFI_ACPI_2_0_GENERIC_ADDRESS_STRUCTURE ResidencyCounter; // offset: 36
  UINT64 ResidencyCounterFrequency; //offset: 48
} EFI_ACPI_MWAIT_LPI_STATE_DESCRIPTOR;

#pragma pack()

#endif //_LOW_POWER_IDLE_TABLE_H_
