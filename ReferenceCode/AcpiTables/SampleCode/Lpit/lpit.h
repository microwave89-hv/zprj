/*++
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
  --*/
/*++

Copyright (c)  2013 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

Lpit.h

Abstract:

This file describes the contents of the ACPI Low Power Idle Table (LPIT).
All changes to the LPIT contents should be done in this file.



--*/

#ifndef _LPIT_H_
#define _LPIT_H_

//
// Statements that include other files
//

#include "LowPowerIdleTable.h"

//
// Defines for LPIT table, some are HSW ULT specific
//


// signature "LPIT"
#define EFI_ACPI_LOW_POWER_IDLE_TABLE_SIGNATURE  0x5449504c

#define EFI_ACPI_OEM_LPIT_REVISION                      0x00000000
#define EFI_ACPI_CREATER_ID          0x2e494d41 //"AMI."
#define EFI_ACPI_CREATER_REVISION    0x5
#define EFI_ACPI_LOW_POWER_IDLE_MWAIT_TYPE    0x0
#define EFI_ACPI_LOW_POWER_IDLE_DEFAULT_FLAG  0x0
#define EFI_ACPI_LOW_POWER_IDLE_NO_RES_COUNTER_FLAG  0x2
#define EFI_ACPI_LOW_POWER_IDLE_RES_FREQ_TSC  0x0

//
// LPI state count (only 1 on HSW ULT)
//

#define EFI_ACPI_HSW_LPI_STATE_COUNT            2

//
// LPI TRIGGER (HW C10 on HSW ULT) 
//
#define EFI_ACPI_HSW_LPI_TRIGGER {0x7F,0x1,0x2,0x0,0x60}

//
// LPI residency counter (HW C10 on HSW ULT)
//
#define  EFI_ACPI_HSW_LPI_RES_COUNTER   {0x7F,64,0x0,0x0,0x632}

//
// LPI DUMMY COUNTER
//
#define  EFI_ACPI_HSW_DUMMY_RES_COUNTER   {0x0,0,0x0,0x0,0x0}


//
// LPI break-even residency in us (HW C10 on HSW ULT)
//
#define  EFI_ACPI_HSW_LPI_MIN_RES   30000

//
// LPI latency in us (HW C10 on HSW ULT) 
//  
#define  EFI_ACPI_HSW_LPI_LATENCY   3000

//
// LPI ID (HW C10 on HSW ULT) 
//  
#define  EFI_ACPI_HSW_LPI_AUDIO_ID   0

//
// LPI ID (HW C10 on HSW ULT) 
//  
#define  EFI_ACPI_HSW_LPI_CS_ID   1

//
//  LPI ACPI table header
//

#pragma pack(1)

typedef struct _EFI_ACPI_LOW_POWER_IDLE_TABLE {
  EFI_ACPI_DESCRIPTION_HEADER             Header;
  EFI_ACPI_MWAIT_LPI_STATE_DESCRIPTOR     LpiStates[EFI_ACPI_HSW_LPI_STATE_COUNT];
} EFI_ACPI_LOW_POWER_IDLE_TABLE;

#pragma pack()


#endif //_LPIT_H_
