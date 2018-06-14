/** @file
  MP Support functions

@copyright
  Copyright (c) 2007 - 2012 Intel Corporation. All rights reserved
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
#include "MpService.h"
#include EFI_PROTOCOL_DEFINITION (MpService)
#endif

extern EFI_CPU_MICROCODE_HEADER **mMicrocodePointerBuffer;

ACPI_CPU_DATA  *mAcpiCpuData;
MP_SYSTEM_DATA *mMPSystemData;

///
/// Function declarations
///
/**
  Initializes MP support in the system.

  @retval EFI_SUCCESS          - Multiple processors are initialized successfully.
  @retval EFI_OUT_OF_RESOURCES - No enough resoruces (such as out of memory).
**/
EFI_STATUS
InitializeMpSupport (
  VOID
  )
{
  EFI_STATUS           Status;
  MP_CPU_RESERVED_DATA *MpCpuReservedData;

  ///
  /// Allocate memory for MP CPU related data below 4G
  ///
  Status = AllocateReservedMemoryBelow4G (
            sizeof (MP_CPU_RESERVED_DATA),
            (VOID **) &MpCpuReservedData
            );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (MpCpuReservedData, sizeof (MP_CPU_RESERVED_DATA));

  mMPSystemData = &(MpCpuReservedData->MPSystemData);
  mAcpiCpuData  = &(MpCpuReservedData->AcpiCpuData);

  ///
  /// Copy microcode to allocated memory
  ///
  CopyMem (
    MpCpuReservedData->MicrocodePointerBuffer,
    mMicrocodePointerBuffer,
    sizeof (EFI_CPU_MICROCODE_HEADER *) * (NUMBER_OF_MICROCODE_UPDATE + 1)
    );

  ///
  /// Initialize ACPI_CPU_DATA data
  ///
  mAcpiCpuData->CpuPrivateData          = (EFI_PHYSICAL_ADDRESS) (UINTN) (&(mMPSystemData->S3DataPointer));
  mAcpiCpuData->S3BootPath              = FALSE;
  mAcpiCpuData->MicrocodePointerBuffer  = (EFI_PHYSICAL_ADDRESS) MpCpuReservedData->MicrocodePointerBuffer;
  mAcpiCpuData->GdtrProfile             = (EFI_PHYSICAL_ADDRESS) & (MpCpuReservedData->GdtrProfile);
  mAcpiCpuData->IdtrProfile             = (EFI_PHYSICAL_ADDRESS) & (MpCpuReservedData->IdtrProfile);

  ///
  /// Initialize MP services
  ///
  InitializeMpServices ();

  return EFI_SUCCESS;
}
