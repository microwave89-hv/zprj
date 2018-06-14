/** @file
  ME Firmware Version Info implementation.

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
#include "Hecidrv.h"

FVI_ELEMENT_AND_FUNCTION      mMeFviElementsData[] = {
  {
    DEFAULT_FVI_ELEMENT_DATA(ME),
    NULL
  },
  {
    DEFAULT_FVI_ELEMENT_DATA(MEBX),
    NULL
  },
  {
    {
      1,
      3,
      MEFW_VERSION,
      MEFW_FVI_STRING,
      MEFW_1_5M_STRING,
    },
    NULL
  }
};

FVI_DATA_HUB_CALLBACK_CONTEXT mMeFviVersionData = {
  MISC_SUBCLASS_FVI_HEADER_ENTRY(ME),
  mMeFviElementsData,
};

UINTN                         mMeFviElements = sizeof (mMeFviElementsData) / sizeof (FVI_ELEMENT_AND_FUNCTION);
