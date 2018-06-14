/** @file
  Interface definition details for platform hook support to ME module.

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
#ifndef _PLATFORM_ME_HOOK_PPI_H_
#define _PLATFORM_ME_HOOK_PPI_H_

///
/// ME Hook provided by platform for PEI phase
/// This ppi provides an interface to hook reference code by OEM.
///
#define PLATFORM_ME_HOOK_PPI_GUID \
  { \
    0xe806424f, 0xd425, 0x4b1a, 0xbc, 0x26, 0x5f, 0x69, 0x03, 0x89, 0xa1, 0x5a \
  }

extern EFI_GUID gPlatformMeHookPpiGuid;

EFI_FORWARD_DECLARATION (PLATFORM_ME_HOOK_PPI);

//
// Revision
//
#define PLATFORM_ME_HOOK_PPI_REVISION 1

/**
  Platform hook before BIOS sends Global Reset Heci Message to ME

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] This                 Pointer to this PLATFORM_ME_HOOK_PPI

  @retval EFI Status Code
**/
typedef
EFI_STATUS
(EFIAPI *PLATFORM_ME_HOOK_PRE_GLOBAL_RESET) (
  IN      EFI_PEI_SERVICES             **PeiServices,
  IN      PLATFORM_ME_HOOK_PPI         *This
  );

///
/// ME Hook provided by platform for PEI phase
/// This ppi provides an interface to hook reference code by OEM.
///
struct _PLATFORM_ME_HOOK_PPI {
  ///
  /// Revision for the ppi structure
  ///
  UINT8                             Revision;
  ///
  /// Function pointer for the hook called before BIOS sends Global Reset Heci Message to ME
  //
  PLATFORM_ME_HOOK_PRE_GLOBAL_RESET PreGlobalReset;
};

#endif
