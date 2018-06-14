/** @file
  The GUID definition for ChipsetInitHob

@copyright
  Copyright (c) 2015 Intel Corporation. All rights reserved
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

#include <Tiano.h>
#include "S3SupportHob.h"

EFI_GUID  gS3SupportHobGuid = S3_SUPPORT_HOB_GUID;
EFI_GUID  gS3DataHobGuid = S3_DATA_HOB_GUID;

EFI_GUID_STRING(&gS3SupportHobGuid, "S3 Support HOB", "GUID for S3 Support HOB");
EFI_GUID_STRING(&gS3DataHobGuid, "S3 Data HOB", "GUID for S3 Data HOB")

