/** @file
  AmtReadyToBoot Protocol definitions

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
#ifndef _AMT_READY_TO_BOOT_PROTOCOL_H_
#define _AMT_READY_TO_BOOT_PROTOCOL_H_

///
/// AMT Readt to Boot Protocol
/// This protocol performs all Management Engine task
///
#define AMT_READY_TO_BOOT_PROTOCOL_GUID \
  { \
    0x40b09b5a, 0xf0ef, 0x4627, 0x93, 0xd5, 0x27, 0xf0, 0x4b, 0x75, 0x4d, 0x5 \
  }

EFI_FORWARD_DECLARATION (AMT_READY_TO_BOOT_PROTOCOL);

/**
  Signal an event for Amt ready to boot.

  @param[in] None

  @retval EFI_SUCCESS             Mebx launched or no controller
**/
typedef
EFI_STATUS
(EFIAPI *AMT_READY_TO_BOOT_PROTOCOL_SIGNAL) (
  VOID
  );

///
/// AMT Readt to Boot Protocol
/// The interface functions are for Performing all Management Engine task
///
struct _AMT_READY_TO_BOOT_PROTOCOL {
  AMT_READY_TO_BOOT_PROTOCOL_SIGNAL Signal; ///< Performs all Management Engine task
};

extern EFI_GUID gAmtReadyToBootProtocolGuid;

#endif
