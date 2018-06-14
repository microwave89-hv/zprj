/** @file
  Platform Trust Technology (FTPM) HECI SkuMgr Library

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
#ifndef _PTT_HECI_LIB_H_
#define _PTT_HECI_LIB_H_

#ifdef PTT_FLAG

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueBase.h"
#endif

/**
  Checks whether ME FW has the Platform Trust Technology capability.

  @param[out] PttCapability      TRUE if PTT is supported, FALSE othewrwise.

  @retval EFI_SUCCESS            Command succeeded
  @retval EFI_DEVICE_ERROR       HECI Device error, command aborts abnormally
**/
EFI_STATUS
EFIAPI
PttHeciGetCapability(
  OUT BOOLEAN   *PttCapability
  );

/**
  Checks Platform Trust Technology enablement state.

  @param[out] IsPttEnabledState  TRUE if PTT is enabled, FALSE othewrwise.

  @retval EFI_SUCCESS            Command succeeded
  @retval EFI_DEVICE_ERROR       HECI Device error, command aborts abnormally
**/
EFI_STATUS
EFIAPI
PttHeciGetState(
  OUT BOOLEAN   *IsPttEnabledState
  );

/**
  Changes current Platform Trust Technology state.

  @param[in] PttEnabledState     TRUE to enable, FALSE to disable.

  @retval EFI_SUCCESS            Command succeeded
  @retval EFI_DEVICE_ERROR       HECI Device error, command aborts abnormally
**/
EFI_STATUS
EFIAPI
PttHeciSetState(
  IN  BOOLEAN   PttEnabledState
  );

#endif // PTT_FLAG
#endif
