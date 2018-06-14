/** @file
  SEC Startup function invoked after SEC Ram is started.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/
#include "Tiano.h"
#include "PeiCore.h"
#include "FlashMap.h"
#include "EfiFirmwareFileSystem.h"
#include "EfiFirmwareVolumeHeader.h"

#include EFI_PPI_DEFINITION (SecPlatformInformation)

///
/// Define the Microcode FV base and size
/// So as to be used by Flat32.asm
/// Here the Microcode binary is embedded in a FFS within a FV
/// So the header should be taken into count to get the raw data
/// In FV header, the EFI_FV_BLOCK_MAP_ENTRY is an array with variable size
/// If the map is changed, it has to be adjusted as well.
///
UINT32 MicrocodeStart = FLASH_REGION_NVSTORAGE_SUBREGION_MICROCODE_BASE +
        sizeof (EFI_FFS_FILE_HEADER);
UINT32 MicrocodeEnd = FLASH_REGION_NVSTORAGE_SUBREGION_MICROCODE_BASE +
  FLASH_REGION_NVSTORAGE_SUBREGION_MICROCODE_SIZE;

extern UINT32 *TopOfCar;

EFI_STATUS
SecPlatformInformation (
  IN EFI_PEI_SERVICES                    **PeiServices,
  IN OUT UINT64                          *StructureSize,
  IN OUT SEC_PLATFORM_INFORMATION_RECORD *PlatformInformationRecord
  );

EFI_SEC_PLATFORM_INFORMATION_PPI mSecPlatformInformationPpi = { SecPlatformInformation };

EFI_PEI_PPI_DESCRIPTOR mPeiSecPlatformInformationPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiSecPlatformInformationPpiGuid,
  &mSecPlatformInformationPpi
};

/**
  Implementation of the PlatformInformation service in
  EFI_SEC_PLATFORM_INFORMATION_PPI.
  This function conveys state information out of the SEC phase into PEI.

  @param[in] PeiServices               - Pointer to the PEI Services Table.
  @param[in] StructureSize             - Pointer to the variable describing size of the input buffer.
  @param[in] PlatformInformationRecord - Pointer to the EFI_SEC_PLATFORM_INFORMATION_RECORD.

  @retval EFI_SUCCESS          - The data was successfully returned.
  @retval EFI_BUFFER_TOO_SMALL - The buffer was too small.
**/
EFI_STATUS
EFIAPI
SecPlatformInformation (
  IN EFI_PEI_SERVICES                    **PeiServices,
  IN OUT UINT64                          *StructureSize,
  IN OUT SEC_PLATFORM_INFORMATION_RECORD *PlatformInformationRecord
  )
{
  UINT32 *BIST;
  UINT32 Size;
  UINT32 Count;

  ///
  /// The entries of BIST information, together with the number of them,
  /// reside in the bottom of stack, left untouched by normal stack operation.
  /// This routine copies the BIST information to the buffer pointed by
  /// PlatformInformationRecord for output.
  ///
  Count = *(TopOfCar - 1);
  Size  = Count * sizeof (UINT64);

  if ((*StructureSize) < (UINT64) Size) {
    *StructureSize = Size;
    return EFI_BUFFER_TOO_SMALL;
  }

  *StructureSize  = Size;
  BIST            = (UINT32 *) ((UINT32) TopOfCar - sizeof (UINT32) - Size);

  EfiCommonLibCopyMem (PlatformInformationRecord, BIST, Size);

  return EFI_SUCCESS;
}

/**
  Entry point to the C language phase of SEC. After the SEC assembly
  code has initialized some temporary memory and set up the stack,
  the control is transferred to this function.

  @param[in] SizeOfRam          - Size of the temporary memory available for use.
  @param[in] BootFirmwareVolume - Base address of the Boot Firmware Volume.
  @param[in] PeiCoreEntryPoint  - Pointer to the entry point of the PEI core.

  @retval This function never returns
**/
VOID
SecStartup (
  IN UINT32               SizeOfRam,
  IN UINT32               BootFirmwareVolume,
  IN PEI_MAIN_ENTRY_POINT PeiCoreEntryPoint
  )
{
  EFI_PEI_STARTUP_DESCRIPTOR PeiStartup;

  PeiStartup.SizeOfCacheAsRam   = SizeOfRam;
  PeiStartup.BootFirmwareVolume = BootFirmwareVolume;
  PeiStartup.DispatchTable      = &mPeiSecPlatformInformationPpi;

  ///
  /// Transfer the control to the PEI core
  ///
  (*PeiCoreEntryPoint)(&PeiStartup);

  ///
  /// Should not come here.
  ///
  return;
}
