/** @file
  The GUID definition for Dptf ACPI table storage file name

@copyright
  Copyright (c) 1999 - 2013 Intel Corporation. All rights reserved
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
#include "DptfAcpiTableStorage.h"

///
/// Protocol GUID definition
///
EFI_GUID gDptfAcpiTableStorageGuid = DPTF_ACPI_TABLE_STORAGE_GUID;
EFI_GUID gDptfAcpiTableStorageGuidFfrd = DPTF_ACPI_TABLE_STORAGE_GUID_FFRD;

///
/// Protocol description string
///
EFI_GUID_STRING (&gDptfAcpiTableStorageGuid, "Dynamic Platform Thermal Framework ACPI Table Storage File Name", "Dynamic Platform Thermal Framework ACPI Table Storage file name GUID");
