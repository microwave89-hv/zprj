/** @file
  This code makes the BIOS Data structure available via standard ACPI mechanisms.

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

#include "BdatAccessHandler.h"

STATIC EFI_ACPI_TABLE_PROTOCOL  *AcpiTable;

/**
  Entry point of the Bdat Access Handler.

  @param[in] ImageHandle   EFI_HANDLE: A handle for the image that is initializing this driver
  @param[in] SystemTable   EFI_SYSTEM_TABLE: A pointer to the EFI system table

  @retval EFI_SUCCESS:              Driver initialized successfully
  @exception EFI_UNSUPPORTED:          A needed driver was not located
  @retval EFI_OUT_OF_RESOURCES:     Could not allocate needed resources
**/
EFI_STATUS
BdatAccessHandler (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                      Status;
  VOID                            *HobList;
  DXE_PLATFORM_SA_POLICY_PROTOCOL *DxePlatformSaPolicy;

  ///
  /// Check if the BDAT ACPI table support is enabled in Setup, if not then exit.
  /// Get the platform setup policy.
  ///
  Status = gBS->LocateProtocol (&gDxePlatformSaPolicyGuid, NULL, (VOID **) &DxePlatformSaPolicy);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Get the start of the HOBs.
  ///
  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &HobList);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }
  ///
  /// Locate ACPI table protocol
  ///
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
  ASSERT_EFI_ERROR (Status);
  ASSERT (AcpiTable != NULL);
  if (EFI_ERROR (Status)) {
    return EFI_OUT_OF_RESOURCES;
  }
  BdatRmtHandler (DxePlatformSaPolicy, HobList, AcpiTable);
  ///
  /// ASSERT_EFI_ERROR (Status);
  ///
  return Status;
}
