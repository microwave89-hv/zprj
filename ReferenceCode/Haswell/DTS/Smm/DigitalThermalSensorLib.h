/** @file
  Defines and prototypes for the DigitalThermalSensor SMM driver

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

#ifndef _DIGITAL_THERMAL_SENSOR_LIB_H_
#define _DIGITAL_THERMAL_SENSOR_LIB_H_

/**
  Prepare data and protocol for Dts Hooe Lib

  @retval EFI_SUCCESS - Initialize complete
**/
EFI_STATUS
InitializeDtsHookLib (
  VOID
  );

/**
  Platform may need to register some data to private data structure before generate
  software SMI or SCI.
**/
VOID
PlatformHookBeforeGenerateSCI (
  VOID
  );

/**
  Read CPU temperature from platform diode

  @retval TemperatureOfDiode   -  Return the CPU temperature of platform diode
**/
UINT8
ReadPlatformThermalDiode (
  VOID
  );

/**
  When system temperature out of specification, do platform specific programming to prevent
  system damage.
**/
VOID
PlatformEventOutOfSpec (
  VOID
  );

#endif
