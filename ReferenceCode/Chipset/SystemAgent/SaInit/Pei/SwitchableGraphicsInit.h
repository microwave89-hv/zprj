/** @file
  Header file for the SwitchableGraphics Pei driver.

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
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

#ifndef _SWITCHABLE_GRAPHICS_PEI_H_
#define _SWITCHABLE_GRAPHICS_PEI_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "EdkIIGlueIoLib.h"
#endif

#include "CpuRegs.h"
#include "CpuPlatformLib.h"

#include "PchAccess.h"
#include "SaAccess.h"

#include EFI_PPI_DEPENDENCY (SaPlatformPolicy)
#include EFI_PPI_DEPENDENCY (Stall)

#ifndef FALSE
#define FALSE 0
#endif

#ifndef HIGH
#define HIGH  1
#endif

#ifndef LOW
#define LOW 0
#endif

#define SG_DELAY_HOLD_RST    100 * STALL_ONE_MILLI_SECOND
#define SG_DELAY_PWR_ENABLE  300 * STALL_ONE_MILLI_SECOND

/**
  SG GPIO Write

  @param[in] PeiServices - General purpose services available to every PEIM
  @param[in] CpuFamilyId - Specifies the CPU family
  @param[in] GpioAddress - GPIO base address
  @param[in] Value       - PCH GPIO number
  @param[in] Level       - Write SG GPIO value (0/1)

  @retval none
**/
VOID
GpioWrite (
  EFI_PEI_SERVICES          **PeiServices,
  CPU_FAMILY                CpuFamilyId,
  IN UINT16                 GpioAddress,
  IN UINT8                  Value,
  IN BOOLEAN                Level
  )
;

/**
  SG GPIO Read

  @param[in] PeiServices - General purpose services available to every PEIM
  @param[in] CpuFamilyId - Specifies the CPU family
  @param[in] GpioAddress - GPIO base address
  @param[in] Value       - PCH GPIO number

  @retval GPIO read value (0/1)
**/
BOOLEAN
GpioRead (
  EFI_PEI_SERVICES          **PeiServices,
  CPU_FAMILY                CpuFamilyId,
  IN UINT16                 GpioAddress,
  IN UINT8                  Value
  )
;
#endif
