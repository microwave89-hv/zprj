/** @file
  Describes the functions visible to the rest of the CpuPeim.

@copyright
  Copyright (c) 2010 - 2013 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Pre-EFI Module' and is licensed
  for Intel CPUs and Chipsets under the terms of your license
  agreement with Intel or your vendor.  This file may be
  modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _CPU_INIT_PEIM_H_
#define _CPU_INIT_PEIM_H_

#include EFI_PPI_PRODUCER (Cache)
#include EFI_PPI_DEFINITION (CpuPlatformPolicy)
#include "CpuRegs.h"

typedef struct {
  UINT32 HtDisabled          : 1;
  UINT32 NumberOfActiveCores : 2;
  UINT32 Reserved0           : 2;
  UINT32 Bist                : 1;
  UINT32 FlexRatio           : 6;
  UINT32 Reserved1           : 4;
  UINT32 Reserved2           : 16;
} CPU_STRAP_SET;

typedef UINT32 CPU_RESET_TYPE;

typedef struct {
  UINT64  MsrValue;
  BOOLEAN Changed;
} MTRR_VALUE;

typedef struct {
  PEI_CACHE_PPI          Ppi;
  EFI_PEI_PPI_DESCRIPTOR PpiDesc;
  MTRR_VALUE             FixedMtrrValue[V_FIXED_MTRR_NUMBER];
  MTRR_VALUE             VariableMtrrValue[V_MAXIMUM_VARIABLE_MTRR_NUMBER * 2];
  BOOLEAN                FixedMtrrChanged;
  BOOLEAN                VariableMtrrChanged;
  BOOLEAN                NemDisabledDone;
} CACHE_PPI_INSTANCE;

#define PEI_CACHE_PPI_INSTANCE_FROM_THIS(a) _CR (a, CACHE_PPI_INSTANCE, Ppi)

///
/// Breaking UINT64 MSR into DWORDs/BYTEs
///
#pragma pack(1)
typedef union _MSR_REGISTER {
  UINT64 Qword;

  struct _DWORDS {
    UINT32 Low;
    UINT32 High;
  } Dwords;

  struct _BYTES {
    UINT8 FirstByte;
    UINT8 SecondByte;
    UINT8 ThirdByte;
    UINT8 FouthByte;
    UINT8 FifthByte;
    UINT8 SixthByte;
    UINT8 SeventhByte;
    UINT8 EighthByte;
  } Bytes;

} MSR_REGISTER;
#pragma pack()
#define NO_RESET              0
#define CPU_ONLY_RESET        1
#define WARM_RESET            2
#define COLDRESET             3

#define RESET_PPI_WARM_RESET  0
#define RESET_PPI_COLD_RESET  3

#define RESET_PORT            0x0CF9
#define CLEAR_RESET_BITS      0x0F1
#define PSIX_THRESHOLD_MASK   0x3FFFFFFF  ///< Bits 61:32 - Mask value respect to Dword.High
#define PSI1_THRESHOLD_VALUE  0x14
#define PSI2_THRESHOLD_VALUE  0x05
#define PSI3_THRESHOLD_VALUE  0x01

#define MAX_OVERCLOCKING_BINS 0x7

/**
  Set up flags in CR4 for XMM instruction enabling
**/
VOID
XmmInit (
  VOID
  );

/**
  Loads the Processor Microcode & Install the Cache PPI

  @param[in] FfsHeader   - Pointer to an alleged FFS file.
  @param[in] PeiServices - General purpose services available to every PEIM.

  @retval EFI_STATUS - the status code returned from any sub-routine
**/
EFI_STATUS
PeimInitializeCpu (
  IN EFI_FFS_FILE_HEADER *FfsHeader,
  IN EFI_PEI_SERVICES    **PeiServices
  );

/**
  Install CacheInitPpi

  @retval EFI_OUT_OF_RESOURCES - failed to allocate required pool
**/
EFI_STATUS
CacheInitPpiInit (
  VOID
  );

/**
  Set CPU strap setting for feature change

  @param[in] PeiServices       - Indirect reference to the PEI Services Table.
  @param[in] NotifyDescriptor  - Address of the notification descriptor data structure. Type
                      EFI_PEI_NOTIFY_DESCRIPTOR is defined above.
  @param[in] Ppi               - Address of the PPI that was installed.

  @retval EFI_SUCCESS - Function completed successfully
**/
EFI_STATUS
EFIAPI
SetCpuStrap (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  );

/**
  Based on ResetType, perform warm or cold reset using PCH Reset PPI

  @param[in] PeiServices       - Indirect reference to the PEI Services Table.
  @param[in] ResetType         - CPU_RESET_TYPE to indicate which reset shoudl be performed.

  @exception EFI_UNSUPPORTED - Reset type unsupported
  @retval EFI_SUCCESS     - function successfully (system should already reset)
**/
EFI_STATUS
PerformWarmORColdReset (
  IN EFI_PEI_SERVICES **PeiServices,
  IN CPU_RESET_TYPE   ResetType
  );

/**
  Based on ResetType, perform warm or cold reset using PCH Reset PPI

  @param[in] PeiServices
  @param[in] CPU_RESET_TYPE

  @retval EFI_STATUS

  Build BIST HOB

  @param[in] PeiServices       - Indirect reference to the PEI Services Table.
  @param[in] NotifyDescriptor  - Address of the notification descriptor data structure. Type
                      EFI_PEI_NOTIFY_DESCRIPTOR is defined above.
  @param[in] Ppi               - Address of the PPI that was installed.

  @retval EFI_SUCCESS - Hob built or not necessary
**/
EFI_STATUS
EFIAPI
BuildBistHob (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  );

/**
  Dump RC CPU and PPM platform policies

  @param[in] CpuPlatformPolicyPpi  - Address of the cpu platform policy ppi.
**/
VOID
CpuPeiPolicyDump(
  IN PEI_CPU_PLATFORM_POLICY_PPI *CpuPlatformPolicyPpi
  );

/**

  Perform the platform spefific initializations.

  @param[in] PeiServices          - Indirect reference to the PEI Services Table.
  @param[in] CpuPlatformPolicyPpi - Platform Policy PPI

**/ 
VOID
BootGuardInit (
  IN EFI_PEI_SERVICES             **PeiServices,
  IN PEI_CPU_PLATFORM_POLICY_PPI  *CpuPlatformPolicyPpi
  );

#endif
