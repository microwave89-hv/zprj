/** @file
  Header file for CPU Data File

Revision History

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _PROCESSOR_DATA_H_
#define _PROCESSOR_DATA_H_

#include "CpuInitDxe.h"

#define EFI_PROCESSOR_TYPE_SIZE 6

typedef struct {
  UINT8      Index;
  UINT8      ProcessorFamily;
  STRING_REF ProcessorVersionToken;
} EFI_PROCESSOR_VERSION;

typedef struct {
  UINT32 Dword1;
  UINT32 Dword2;
  UINT32 Dword3;
  UINT32 Dword4;
} EFI_QDWORD;

///
/// Platform-specific definitions
///
#define EFI_CPU_DATA_MAXIMUM_LENGTH 0x100

/**
  This function gets called with the processor number and will log all data to data hub
  pertaining to this processor.

  @param[in] CpuNumber         - Processor Number
  @param[in] CpuDataForDatahub - Contains CPU data which is collected for data hub

  @retval EFI_OUT_OF_RESOURCES - failed to allocate pool for CPU data
  @retval EFI_SUCCESS          - CPU data Hub has been created successfully
**/
EFI_STATUS
InitializeProcessorData (
  IN UINTN                CpuNumber,
  IN CPU_DATA_FOR_DATAHUB *CpuDataForDatahub
  );

/**
  Returns the processor voltage of the processor installed in the system.

  @retval Processor Voltage
**/
INT16
GetProcessorVoltage (
  VOID
  );

/**
  Returns the processor microcode revision of the processor installed in the system.

  @retval Processor Microcode Revision
**/
UINT32
GetCpuUcodeRevision (
  VOID
  );

/**
  Get processor status by specific CPU number

  @param[in] CpuNumber - indicate which CPU status are requested

  @retval EFI_PROCESSOR_STATUS_DATA  for specific CPU number
**/
EFI_PROCESSOR_STATUS_DATA
GetProcessorStatus (
  UINTN CpuNumber
  );

/**
  Returns the procesor version string token installed in the system.

  @retval Processor Version string token
**/
VOID
GetProcessorVersion (
  OUT PROCESSOR_VERSION_INFORMATION *Version
  );

/**
  Returns the processor family of the processor installed in the system.

  @retval Processor Family
**/
EFI_PROCESSOR_FAMILY_DATA
GetProcessorFamily (
  VOID
  );

/**
  Returns the procesor manufaturer string token installed in the system.

  @retval Processor Manufacturer string token
**/
EFI_PROCESSOR_MANUFACTURER_DATA
GetProcessorManufacturer (
  VOID
  );

/**
  Returns if processor is Intel or not.

  @retval TRUE - Intel Processor.
  @retval FALSE - Not Intel Processor.
**/
BOOLEAN
IsIntelProcessor (
  VOID
  );

#endif
