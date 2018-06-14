/** @file
  CPU Firmware Version Info implementation.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
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
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "CpuInitDxe.h"
#endif

FVI_ELEMENT_AND_FUNCTION mCpuFviElementsData[] = {
  {
    DEFAULT_FVI_ELEMENT_DATA(CPU),
    NULL
  },
  {
    {
      1,
      0,
      UCODE_VERSION,
      UCODE_FVI_STRING,
      {
        0
      },
    },
    NULL
  },
  {
    {
      1,
      0,
      TXT_VERSION,
      TXT_FVI_STRING,
      {
        0
      },
    },
    NULL
  }
};

FVI_DATA_HUB_CALLBACK_CONTEXT mCpuFviVersionData = {
  MISC_SUBCLASS_FVI_HEADER_ENTRY(CPU),
  mCpuFviElementsData,
};

UINTN mCpuFviElements = sizeof (mCpuFviElementsData) / sizeof (FVI_ELEMENT_AND_FUNCTION);
