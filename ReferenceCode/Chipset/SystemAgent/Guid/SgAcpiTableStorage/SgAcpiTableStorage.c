/** @file
  The GUID definition for SG ACPI table storage file name

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
#include "EdkIIGlueDxe.h"
#include "SgAcpiTableStorage.h"

///
/// Protocol GUID definition for PEG Switchable Graphics
///
EFI_GUID  gSgAcpiTableStorageGuid = SG_ACPI_TABLE_STORAGE_GUID;

///
/// Protocol description for PEG Switchable Graphics
///
EFI_GUID_STRING
  (&gIntelSgAcpiTableStorageGuid, "SG ACPI Table Storage File Name", "SG ACPI Table Storage file name GUID");


///
/// Protocol GUID definition for PCH Switchable Graphics
///
EFI_GUID  gSgAcpiTablePchStorageGuid = SG_ACPI_TABLE_PCH_STORAGE_GUID;

///
/// Protocol description for PCH Switchable Graphics
///
EFI_GUID_STRING
  (&gSgAcpiTablePchStorageGuid, "SG ACPI Table Pch Storage File Name", "SG ACPI Table Pch Storage file name GUID");
