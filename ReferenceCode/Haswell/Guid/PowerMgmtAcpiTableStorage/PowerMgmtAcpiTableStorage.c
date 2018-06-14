/** @file
  The GUID definition for power management ACPI table storage file name

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

///
/// Statements that include other files
///
#include "EdkIIGlueDxe.h"
#include "PowerMgmtAcpiTableStorage.h"

///
/// Protocol GUID definition
///
EFI_GUID gPowerMgmtAcpiTableStorageGuid = POWER_MGMT_ACPI_TABLE_STORAGE_GUID;

///
/// Protocol description
///
EFI_GUID_STRING
(
        &gPowerMgmtAcpiTableStorageGuid, "Power Management ACPI Table Storage File Name",
        "Power Management ACPI Table Storage file name GUID"
);
