/** @file
  Interface definition details for platform hook support to ME module during DXE phase.

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/
#ifndef _PLATFORM_ME_HOOK_H_
#define _PLATFORM_ME_HOOK_H_

///
/// ME Hook provided by platform for DXE phase
/// This protocol provides an interface to hook reference code by OEM.
///
#define PLATFORM_ME_HOOK_PROTOCOL_GUID \
  { \
    0xbc52476e, 0xf67e, 0x4301, 0xb2, 0x62, 0x36, 0x9c, 0x48, 0x78, 0xaa, 0xc2 \
  }

#define PLATFORM_ME_HOOK_PROTOCOL_REVISION  1

/**
  Platform hook before BIOS sends Global Reset Heci Message to ME

  @param[in] None

  @retval EFI Status Code
**/
typedef
EFI_STATUS
(EFIAPI *PLATFORM_ME_HOOK_PRE_GLOBAL_RESET) (
  VOID
  )
;

///
/// Platform Intel ME Hook Protocol
/// This protocol provides an interface to hook reference code by OEM.
///
typedef struct _PLATFORM_ME_HOOK_PROTOCOL {
  ///
  /// Revision for the protocol structure
  ///
  UINT8                             Revision;
  ///
  /// Function pointer for the hook called before BIOS sends Global Reset Heci Message to ME
  ///
  PLATFORM_ME_HOOK_PRE_GLOBAL_RESET PreGlobalReset;
} PLATFORM_ME_HOOK_PROTOCOL;

extern EFI_GUID gPlatformMeHookProtocolGuid;

#endif
