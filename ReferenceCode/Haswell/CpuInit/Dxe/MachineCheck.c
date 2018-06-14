/** @file
  Machine check register initialization

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
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "MachineCheck.h"
#include "Features.h"

#include EFI_GUID_DEFINITION (PowerOnHob)
#include EFI_PROTOCOL_DEFINITION (MpService)
#include EFI_PROTOCOL_DEFINITION (CpuPlatformPolicy)
#endif

extern DXE_CPU_PLATFORM_POLICY_PROTOCOL *mPlatformCpu;

/**
  Initialize all the Machine-Check registers.

  @param[in] Buffer      - Pointer to private data. Not Used.
  @param[in] MchkEnable  - Enable or disable Mchk.
**/
VOID
InitializeMachineCheckRegisters (
  IN VOID    *Buffer,
  IN BOOLEAN MchkEnable
  )
{
  EFI_CPUID_REGISTER            CpuidRegisters;
  CPU_FEATURE                   Feature;
  CPU_IA32_MCG_CAP_LOW_REGISTER *MCGCap;
  UINT64                        MCGCapValue;
  UINT8                         Count;
  UINT8                         Index;
  UINT8                         StartIndex;
  UINT64                        Value;

  if (!MchkEnable) {
    ///
    /// Do not enable MCHK
    ///
    return;
  }

  AsmCpuid (
          CPUID_VERSION_INFO,
          &CpuidRegisters.RegEax,
          &CpuidRegisters.RegEbx,
          &CpuidRegisters.RegEcx,
          &CpuidRegisters.RegEdx
          );
  *(UINT32 *) (&Feature) = CpuidRegisters.RegEdx;

  if (Feature.MCE && Feature.MCA) {

    MCGCapValue = AsmReadMsr64 (IA32_MCG_CAP);
    MCGCap      = (CPU_IA32_MCG_CAP_LOW_REGISTER *) &MCGCapValue;

    Count       = (UINT8) MCGCap->Count;

    StartIndex  = 0;
    for (Index = StartIndex; Index < Count; Index++) {
      Value = (UINT64) -1;
      AsmWriteMsr64WithScript (IA32_MC0_CTL + Index * 4, Value);
    }
    for (Index = StartIndex; Index < Count; Index++) {
      if (Index <= 4) {
        ///
        /// Clean MC0-MC4 Status when system is cold reset, but no boot script.  S3 is treated as warm reset.
        ///
        if (mPlatformCpu->CpuConfig->IsColdReset == CPU_FEATURE_ENABLE) {
          AsmWriteMsr64 (IA32_MC0_STATUS + Index * 4, 0);
        }
        continue;
      }
      AsmWriteMsr64WithScript (IA32_MC0_STATUS + Index * 4, 0);
    }
    EnableMce ();
  }

  return;
}

/**
  Enable MCE feature for current CPU.

  @param[in] MchkEnable  - Enable Mchk or not.
**/
VOID
InitializeMce (
  IN BOOLEAN MchkEnable
  )
{
  EFI_CPUID_REGISTER CpuidRegisters;
  CPU_FEATURE        Feature;

  if (!MchkEnable) {
    ///
    /// Do not enable MCHK
    ///
    return;
  }

  AsmCpuid (
          CPUID_VERSION_INFO,
          &CpuidRegisters.RegEax,
          &CpuidRegisters.RegEbx,
          &CpuidRegisters.RegEcx,
          &CpuidRegisters.RegEdx
          );
  *(UINT32 *) (&Feature) = CpuidRegisters.RegEdx;

  if (Feature.MCE && Feature.MCA) {
    EnableMce ();
  }

  return;
}
