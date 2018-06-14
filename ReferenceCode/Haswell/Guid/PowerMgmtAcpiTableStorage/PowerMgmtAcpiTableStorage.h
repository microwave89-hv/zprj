/** @file
  GUID definition for the Power Management ACPI table storage file name

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
#ifndef _POWER_MGMT_ACPI_TABLE_STORAGE_H_
#define _POWER_MGMT_ACPI_TABLE_STORAGE_H_

///
/// Power Mgmt policy provided by platform for ACPI Table Storage
/// {299141BB-211A-48a5-92C0-6F9A0A3A006E}
///
#define POWER_MGMT_ACPI_TABLE_STORAGE_GUID \
  { \
    0x299141bb, 0x211a, 0x48a5, 0x92, 0xc0, 0x6f, 0x9a, 0xa, 0x3a, 0x0, 0x6e \
  }

extern EFI_GUID gPowerMgmtAcpiTableStorageGuid;

#endif
