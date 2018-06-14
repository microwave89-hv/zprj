/** @file
  Header file of CPU feature control module

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
#ifndef _FEATURES_H_
#define _FEATURES_H_

#include "CpuInitDxe.h"
#include "MpService.h"

#define OPTION_FEATURE_RESERVED_MASK        0xFFFF00F8  ///< bits 30:16,  7:3
#define OPTION_FEATURE_CONFIG_RESERVED_MASK 0xFFFFFFFC  ///< bits 2:31
/**
  Create feature control structure which will be used to program each feature on each core.

  @param[in] MPSystemData - MP_SYSTEM_DATA global variable that contains platform policy protocol settings of each features.
**/
VOID
InitializeFeaturePerSetup (
  IN MP_SYSTEM_DATA *MPSystemData
  );

/**
  Program all processor features basing on desired settings

  @param[in] MpServices  - EFI_MP_SERVICES_PROTOCOL
**/
VOID
ProgramProcessorFeature (
  IN EFI_MP_SERVICES_PROTOCOL *MpServices
  );

/**
  Program CPUID Limit before booting to OS

  @param[in] MpServices  - MP Services Protocol entry
**/
VOID
ProgramCpuidLimit (
  IN EFI_MP_SERVICES_PROTOCOL *MpServices
  );

/**
  Initialize prefetcher settings

  @param[in] MlcStreamerprefecterEnabled - Enable/Disable MLC streamer prefetcher
  @param[in] MlcSpatialPrefetcherEnabled - Enable/Disable MLC spatial prefetcher
**/
VOID
InitializeProcessorsPrefetcher (
  IN UINTN MlcStreamerprefecterEnabled,
  IN UINTN MlcSpatialPrefetcherEnabled
  );

/**
  Detect each processor feature and log all supported features

  @param[in] MpServices  - EFI_MP_SERVICES_PROTOCOL
**/
VOID
CollectProcessorFeature (
  IN EFI_MP_SERVICES_PROTOCOL *MpServices
  );

/**
  Lock VMX/TXT feature bits on the processor.
  Set "CFG Lock" (MSR 0E2h Bit[15]

  @param[in] LockFeatureEnable - TRUE to lock these feature bits and FALSE to not lock
**/
VOID
LockFeatureBit (
  IN BOOLEAN LockFeatureEnable
  );

/**
  Function to get desired core number by CSR register

  @retval Desired core number
**/
UINT32
GetCsrDesiredCores (
  VOID
  );

/**
  Function to set desired core numbers or SMT lock
**/
VOID
SetLockCsrDesiredCores (
  VOID
  );

/**
  Write 64bits MSR with script

  @param[in] Index - MSR index that will be written
  @param[in] Value - value written to MSR
**/
VOID
AsmWriteMsr64WithScript (
  IN UINT32 Index,
  IN UINT64 Value
  );

/**
  Write 64bits MSR to script

  @param[in] Index - MSR index that will be written
  @param[in] Value - value written to MSR
**/
VOID
WriteMsr64ToScript (
  IN UINT32 Index,
  IN UINT64 Value
  );

/**
  Provide access to the CPU misc enables MSR

  @param[in] Enable  - Enable or Disable Misc Features
  @param[in] BitMask - The register bit offset of MSR MSR_IA32_MISC_ENABLE
**/
VOID
CpuMiscEnable (
  BOOLEAN Enable,
  UINT64  BitMask
  );

#endif
