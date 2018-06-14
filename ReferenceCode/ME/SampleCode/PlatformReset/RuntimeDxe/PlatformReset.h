/** @file
  Definitions for PlatformReset driver

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
#ifndef _PLATFORM_RESET_H_
#define _PLATFORM_RESET_H_

#include "EdkIIGlueDxe.h"
#include EFI_PROTOCOL_CONSUMER (PchReset)
#include EFI_PROTOCOL_CONSUMER (MePlatformGetResetType)
#include EFI_ARCH_PROTOCOL_DEFINITION (Reset)

#endif // _PLATFORM_RESET_H_
