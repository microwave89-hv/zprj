/** @file
  Copies the memory related timing and configuration information into the
  Compatible BIOS data (BDAT) table.

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved.
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
  license agreement.
**/
#ifndef _BdatRmtHandler_h_
#define _BdatRmtHandler_h_
#ifndef BDAT_SUPPORT
#define BDAT_SUPPORT
#endif
#include "MemInfoHob.h"

#define EFI_BDAT_TABLE_SIGNATURE  EFI_SIGNATURE_32 ('B', 'D', 'A', 'T')
#define ACPI_BDAT_OEM_REV         0x00001000
#define EFI_BDAT_ACPI_POINTER     0x0

#endif /// _BdatRmtHandler_h_
