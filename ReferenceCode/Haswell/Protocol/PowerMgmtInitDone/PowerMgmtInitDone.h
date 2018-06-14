/** @file
  This file defines the PowerMgmtInitDone Protocol.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
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
#ifndef _POWER_MGMT_INIT_DONE_H_
#define _POWER_MGMT_INIT_DONE_H_

///
/// Define PPM INFO protocol GUID
///
/// EDK and EDKII have different GUID formats
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#define EFI_POWER_MGMT_INIT_DONE_PROTOCOL_GUID \
  { \
    0xd71db106, 0xe32d, 0x4225, 0xbf, 0xf4, 0xde, 0x6d, 0x77, 0x87, 0x17, 0x61 \
  }

#else
#define EFI_POWER_MGMT_INIT_DONE_PROTOCOL_GUID \
  { \
    0xd71db106, 0xe32d, 0x4225, \
    { \
      0xbf, 0xf4, 0xde, 0x6d, 0x77, 0x87, 0x17, 0x61 \
    } \
  }
#endif
///
/// Extern the GUID for protocol users.
///
extern EFI_GUID gEfiPowerMgmtInitDoneProtocolGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _EFI_POWER_MGMT_INIT_DONE_PROTOCOL EFI_POWER_MGMT_INIT_DONE_PROTOCOL;

#endif
