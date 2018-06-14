/** @file
  GUID definition for the SA SSDT ACPI table storage file name

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
#ifndef _SA_SSDT_TABLE_STORAGE_H_
#define _SA_SSDT_TABLE_STORAGE_H_

#define SA_SSDT_ACPI_TABLE_STORAGE_GUID \
  { \
    0xAAA99A23, 0x13B6, 0x4C31, 0xBB, 0x8B, 0x29, 0x9E, 0x8E, 0xC0, 0x4F, 0xA4 \
  }

extern EFI_GUID gSaSsdtAcpiTableStorageGuid;

#endif
