/** @file
  Txt specific PPI operation definition.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
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
#ifndef _TXT_PPI_OPERATION_H_
#define _TXT_PPI_OPERATION_H_

///
/// EDK and EDKII have different GUID formats
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#define TXT_ONE_TOUCH_OP_PROTOCOL_GUID \
  { \
    0xFA2338AD, 0x80DF, 0x49D0, 0x93, 0x96, 0xCF, 0x71, 0x45, 0xD0, 0x3A, 0x76 \
  }
#else
#define TXT_ONE_TOUCH_OP_PROTOCOL_GUID \
  { \
    0xFA2338AD, 0x80DF, 0x49D0, \
    { \
      0x93, 0x96, 0xCF, 0x71, 0x45, 0xD0, 0x3A, 0x76 \
    } \
  }
#endif
///
/// Extern the GUID for protocol users.
///
extern EFI_GUID gTxtOneTouchOpProtocolGuid;

///
/// Forward reference for ANSI C compatibility
///
typedef struct _TXT_ONE_TOUCH_OP_PROTOCOL TXT_ONE_TOUCH_OP_PROTOCOL;

///
/// Member functions
///
typedef
EFI_STATUS
(EFIAPI *TXT_PPI_EXEC_OPERATION)(
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command
  );

/*

@brief
  Extend PPI operation for TxT.

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT

*/
typedef
EFI_STATUS
(EFIAPI *TXT_CONFIRMATION_DIALOG)(
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command,
  IN OUT BOOLEAN               *Confirm
  );
/*

@brief
  Confirmation dialog for TxT PPI

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT
  @param[in] Confirm - User confirm

*/
typedef
EFI_STATUS
(EFIAPI *TXT_RESET_SYSTEM)(
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command
  );

/**
  Reset system.

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT

  @retval EFI_SUCCESS - Always return EFI_SUCCESS
**/
struct _TXT_ONE_TOUCH_OP_PROTOCOL {
  TXT_PPI_EXEC_OPERATION  ExecuteOperation;
  TXT_CONFIRMATION_DIALOG ConfirmationDialog;
  TXT_RESET_SYSTEM        ResetSystem;
};

#endif
