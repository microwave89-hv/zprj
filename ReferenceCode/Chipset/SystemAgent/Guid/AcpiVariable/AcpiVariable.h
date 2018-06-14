/** @file
  GUIDs used for ACPI variables.

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
#ifndef _ACPI_VARIABLE_H_
#define _ACPI_VARIABLE_H_

///
/// RC Override: sync from R8HswClientPkg\Guid\AcpiVariable\AcpiVariable.h
///
#define EFI_ACPI_VARIABLE_GUID \
  { \
    0xc020489e, 0x6db2, 0x4ef2, 0x9a, 0xa5, 0xca, 0x6, 0xfc, 0x11, 0xd3, 0x6a \
  }

#define ACPI_GLOBAL_VARIABLE  L"AcpiGlobalVariable"

///
/// The following structure combine all ACPI related variables into one in order
/// to boost performance
///
#pragma pack(1)
typedef struct {
  UINT16  Limit;
  UINTN   Base;
} PSEUDO_DESCRIPTOR;
#pragma pack()

typedef struct {
  BOOLEAN               APState;
  BOOLEAN               S3BootPath;
  EFI_PHYSICAL_ADDRESS  WakeUpBuffer;
  EFI_PHYSICAL_ADDRESS  GdtrProfile;
  EFI_PHYSICAL_ADDRESS  IdtrProfile;
  EFI_PHYSICAL_ADDRESS  CpuPrivateData;
  EFI_PHYSICAL_ADDRESS  StackAddress;
  EFI_PHYSICAL_ADDRESS  MicrocodePointerBuffer;
  EFI_PHYSICAL_ADDRESS  SmramBase;
  EFI_PHYSICAL_ADDRESS  SmmStartImageBase;
  UINT32                SmmStartImageSize;
  UINT32                NumberOfCpus;
} ACPI_CPU_DATA;

///
/// Acpi Related variables
///
typedef struct {
  EFI_PHYSICAL_ADDRESS  AcpiReservedMemoryBase;
  UINT32                AcpiReservedMemorySize;
  EFI_PHYSICAL_ADDRESS  S3ReservedLowMemoryBase;
  EFI_PHYSICAL_ADDRESS  AcpiBootScriptTable;
  EFI_PHYSICAL_ADDRESS  RuntimeScriptTableBase;
  EFI_PHYSICAL_ADDRESS  AcpiFacsTable;
  UINT64                SystemMemoryLength;
  ACPI_CPU_DATA         AcpiCpuData;
  EFI_PHYSICAL_ADDRESS  VideoOpromAddress; ///< VGA OPROM to support Video Re-POST for Linux S3
  UINT32                VideoOpromSize;    ///< VGA OPROM to support Video Re-POST for Linux S3
  EFI_PHYSICAL_ADDRESS  S3DebugBufferAddress;   ///< S3 Debug extension
  EFI_PHYSICAL_ADDRESS  S3ResumeNvsEntryPoint;  ///< S3 Debug extension
} ACPI_VARIABLE_SET;

extern EFI_GUID gEfiAcpiVariableGuid;

#endif
