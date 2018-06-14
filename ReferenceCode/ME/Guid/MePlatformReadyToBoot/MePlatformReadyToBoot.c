/** @file
  EFI PlatformReadyToBoot Guid data declarations.

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
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

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include EFI_GUID_DEFINITION (MePlatformReadyToBoot)
#endif

EFI_GUID  gMePlatformReadyToBootGuid = EFI_EVENT_ME_PLATFORM_READY_TO_BOOT;

EFI_GUID_STRING(&gMePlatformReadyToBootGuid, "MePlatformReadyToBoot GUID", "MePlatformReadyToBoot GUID")
