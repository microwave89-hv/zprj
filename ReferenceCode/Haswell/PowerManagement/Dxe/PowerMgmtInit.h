/** @file
  This header file contains power management definitions specific to
  Haswell processors.

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
#ifndef _POWER_MANAGEMENT_H_
#define _POWER_MANAGEMENT_H_

#include "PowerMgmtCommon.h"

//
// Function prototypes
//
/**
  Initialize the power management support.
  This function will do boot time configuration:
    Install into SMRAM/SMM
    Detect HW capabilities and SW configuration
    Initialize HW and software state (primarily MSR and ACPI tables)
    Install SMI handlers for runtime interfacess

  @param[in] ImageHandle  Pointer to the loaded image protocol for this driver
  @param[in] SystemTable  Pointer to the EFI System Table

  @retval EFI_SUCCESS   The driver installed/initialized correctly.
  @retval Driver will ASSERT in debug builds on error. PPM functionality is considered critical for mobile systems.
**/
EFI_STATUS
InitializePowerManagement (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  );

/**
  Initializes the CPU power management global variable.
  This must be called prior to any of the functions being used.

  @retval EFI_SUCCESS       Library was initialized successfully
  @retval EFI_DEVICE_ERROR  If CPU is not supported by this library
**/
VOID
InitializePowerManagementGlobalVariables (
  VOID
  );

/**
  Create a custom FVID table based on setup options.
  Caller is responsible for providing a large enough table.

  @param[in] FvidPointer   Table to update, must be initialized.
**/
VOID
CreateCustomFvidTable (
  IN OUT FVID_TABLE *FvidPointer
  );

/**
  Sets up the PPM flags based upon capabilities

  @param[in] This  - None

  @retval EFI_STATUS
**/
VOID
SetPpmFlags (
  VOID
  );

/**
  Set the PPM flags based on current user configuration obtained from PPM platform policy protocol

  @param[in] PpmFlagsMask  Mask of feature options to be enabled as specified by the policy
**/
VOID
SetUserConfigurationPpmFlags (
  );

/**
  Initialize the platform power management based on hardware capabilities
  and user configuration settings.

  This includes creating FVID table, updating ACPI tables,
  and updating processor and chipset hardware configuration.

  This should be called prior to any Px, Cx, Tx activity.

  @retval EFI_SUCCESS - on success
  @retval Appropiate failure code on error
**/
EFI_STATUS
InitializePpm (
  VOID
  );

/**
  This is a debug function to print PPM Policy
**/
VOID
DumpCpuPmConfig (
  VOID
  );

/**
  This is a debug function to print PPM Global NVS area
**/
VOID
DumpPPMGlobalNvs (
  VOID
  );

#endif
