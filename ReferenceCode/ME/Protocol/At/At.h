/** @file
  Defines and prototypes for the AT driver.
  This driver implements the AT protocol.

@copyright
  Copyright (c) 2004 - 2012 Intel Corporation. All rights reserved
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
#ifndef _DXE_AT_PROTOCOL_H_
#define _DXE_AT_PROTOCOL_H_
#include "MkhiMsgs.h"
///
/// Define the  protocol GUID
///
#define EFI_AT_PROTOCOL_GUID \
  { \
    0x2df8cdbe, 0x79ce, 0x48a0, 0x8c, 0x59, 0x50, 0xf7, 0x1d, 0xe1, 0xad, 0xd1 \
  }

///
/// Protocol revision number
/// Any backwards compatible changes to this protocol will result in an update in the revision number
/// Major changes will require publication of a new protocol
///
#define AT_PROTOCOL_REVISION  1

//
// Extern the GUID for protocol users.
//
extern EFI_GUID gEfiAtProtocolGuid;

//
// Forward reference for ANSI C compatibility
//
EFI_FORWARD_DECLARATION (EFI_AT_PROTOCOL);

//
// Protocol definitions
//

/**
  This function sends a request to ME AT Services to validate AT
  recovery credentials. The user input is captured in UTF-16
  format and then passed to this funtion. This function converts
  the User recovery password into a HASH by using Salt & Nonce
  and then send the password HASH to ME AT Services for
  validation. ME AT Service compares the Password HASH and
  returns either pass or fail.

  @param[in] This                 The address of protocol
  @param[in] PassPhrase           Passphrase that needs to be authenticated sent to ME
  @param[in] PassType             Password type user or server generated
  @param[in][out] IsAuthenticated The return of the password match 1 for success and 0 for fail

  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures
  @retval EFI_SUCCESS             The function completed successfully
**/
typedef
EFI_STATUS
(EFIAPI *EFI_AT_AUTHETICATE_CREDENTIAL) (
  IN     EFI_AT_PROTOCOL          *This,
  IN     UINT8                    *PassPhrase,
  IN     UINT32                   *PassType,
  IN OUT UINT8                    *IsAuthenticated
  );

/**
  This API compute the SHA1 hash of the user enterted password

  @param[in] This                 The address of protocol
  @param[in] PassPhrase           The passphrase for which SHA1 hash to be computed
  @param[in][out] Hash            The return value of the SHA1 hash

  @retval EFI_SUCCESS             The function completed successfully.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_AT_COMPUTE_HASH) (
  IN     EFI_AT_PROTOCOL          *This,
  IN     UINT8                    *PassPhrase,
  IN OUT UINT8                    *Hash
  );

/**
  This gets the ME nonce
  @param[in] This                 The address of protocol
  @param[in][out] Nonce           The return value of the 16 Byte nonce received from ME

  @retval EFI_SUCCESS             The function completed successfully.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_AT_GET_NONCE) (
  IN     EFI_AT_PROTOCOL          *This,
  IN OUT UINT8                    *Nonce
  );

/**
  This API get the AT Unlock Timer values

  @param[in] This                 The address of protocol
  @param[in] Interval             The return value of the Unlock Time Interval that was set by AT Server
  @param[in] TimeLeft             The Timeleft in the Unlock Timer

  @retval EFI_SUCCESS             The function completed successfully.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_AT_GET_TIMER_INFO) (
  IN     EFI_AT_PROTOCOL          *This,
  IN OUT UINT32                   *Interval,
  IN OUT UINT32                   *TimeLeft
  );

/**
  This retrives the ISV String stored by AT Server that BIOS will display during Platform lock state

  @param[in] This                 The address of protocol
  @param[in] StringId             The String buffer ID to retrive the ISV String
  @param[out] IsvString           256 Bytes of ISV string array, the
  @param[out] IsvStringLength     The String length

  @retval EFI_SUCCESS             The function completed successfully.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_AT_GET_RECOVERY_STRING) (
  IN     EFI_AT_PROTOCOL          *This,
  IN     UINT32                   *StringId,
  IN OUT UINT8                    *IsvString,
  IN OUT UINT32                   *IsvStringLength
  );

/**
  This receives the ISV ID from ME and display the ID, when the platform is in stolen state

  @param[in] This                 The address of protocol
  @param[out] IsvId               The pointer to 4 byte ISV ID

  @retval EFI_SUCCESS             The function completed successfully.
**/typedef
EFI_STATUS
(EFIAPI *EFI_AT_GET_ISV_ID) (
  IN     EFI_AT_PROTOCOL          *This,
  IN OUT UINT32                   *IsvId
  );

/**
  This instructs FW that a WWAN recovery is desired and thus the Radio needs to be initialized.

  This command in not supported.

  @param[in] This                 The address of protocol
**/typedef
EFI_STATUS
(EFIAPI *EFI_AT_SET_SUSPEND_STATE) (
  IN     EFI_AT_PROTOCOL          *This,
  IN     UINT32                   TransitionState,
  IN     UINT8                    *Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_AT_INIT_WWAN_RECOV) (
  IN     EFI_AT_PROTOCOL          *This
  );

/**
  This queries FW of the NIC Radio Status

  This command in not supported.

  @param[in] This                 The address of protocol
  @param[in] RadioStatus          Radio status
  @param[in] NetworkStatus        Network status
**/
typedef
EFI_STATUS
(EFIAPI *EFI_AT_GET_WWAN_NIC_STATUS) (
  IN     EFI_AT_PROTOCOL          *This,
  IN OUT UINT8                    *RadioStatus,
  IN OUT UINT8                    *NetworkStatus
  );

/**
  This send an AssertStolen Message to ME when OEM has set the AllowAssertStolen bit to be accepted by BIOS.

  @param[in] This                 The address of protocol
  @param[out] CompletionCode      The return ME Firmware return code for this request

  @retval EFI_SUCCESS             The function completed successfully.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_AT_SEND_ASSERT_STOLEN) (
  IN     EFI_AT_PROTOCOL          *This,
  IN OUT UINT8                    *CompletionCode
  );

/**
  This queries FW of the AT Status in Unsigned mode

  @param[in] This                 The address of protocol
  @param[out] StateUnsigned       Structure retrieved from ME describing current AT state

  @retval EFI_SUCCESS             The function completed successfully.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_AT_GET_STATE_UNSIGNED) (
  IN     EFI_AT_PROTOCOL          *This,
  IN OUT AT_STATE_INFO            *StateUnsigned
  );

///
/// Protocol definition
///
struct _EFI_AT_PROTOCOL {
  UINT8                           Revision;
  EFI_AT_AUTHETICATE_CREDENTIAL   AuthenticateCredential;
  EFI_AT_COMPUTE_HASH             ComputeHash;
  EFI_AT_GET_NONCE                GetNonce;
  EFI_AT_GET_TIMER_INFO           GetTimerInfo;
  EFI_AT_GET_RECOVERY_STRING      GetRecoveryString;
  EFI_AT_GET_ISV_ID               GetIsvId;
  EFI_AT_SEND_ASSERT_STOLEN       SendAssertStolen;
  EFI_AT_SET_SUSPEND_STATE        SetSuspendState;
  EFI_AT_INIT_WWAN_RECOV          InitWWAN;
  EFI_AT_GET_WWAN_NIC_STATUS      GetWWANNicStatus;
  EFI_AT_GET_STATE_UNSIGNED       GetStateUnsigned;
};

#endif
