/** @file
  GUID definition for the ME SSDT ACPI table storage file name

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
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
#ifndef _ME_SSDT_TABLE_STORAGE_H_
#define _ME_SSDT_TABLE_STORAGE_H_

#define ME_SSDT_ACPI_TABLE_STORAGE_GUID \
  { \
    0x9A8F82D5, 0x39B1, 0x48DA, 0x92, 0xDC, 0xA2, 0x2D, 0xA8, 0x83, 0x4D, 0xF6 \
  }

extern EFI_GUID gMeSsdtAcpiTableStorageGuid;

#endif
