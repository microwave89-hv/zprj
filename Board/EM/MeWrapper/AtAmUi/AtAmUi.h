/** @file
  Header file.

@copyright
  Copyright (c) 2013 Intel Corporation. All rights reserved
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
#ifndef _ATAMUI_H_
#define _ATAMUI_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "AtAmUiString.h"
#include "AtAm.h"
#include "AtHi.h"
#include "AtAmHelper.h"
#endif

#include EFI_PROTOCOL_CONSUMER (AtAm)
#include EFI_PROTOCOL_CONSUMER (AtPlatformPolicy)

///
/// Intel ME Alert AT Handler Event GUID
/// The event is used to execute AtAmUiCallback () when the system is ready to launch ATAM UI
/// The event is signaled after consoles are ready in BDS phase.
///
#define ME_ALERT_AT_HANDLER_GUID \
  { \
    0xb441df87, 0x8d94, 0x4811, 0x85, 0xf7, 0xf, 0x9a, 0x7b, 0xf8, 0x9d, 0x2a \
  }

#define ATAMUI_SUSPEND_ATTEMPTS 3

/**
  ATAM UI callback.

  @param[in] Event                The event registered
  @param[in] Context              Event context. Not used in this event handler.

  @retval None
**/
VOID
EFIAPI
AtAmUiCallback (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context
  )
;

/**
  Function handling entering suspend mode.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiTheftNotification (
  VOID
  )
;

/**
  Function handling displaing theft notification.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiEnterSuspendState (
  VOID
  )
;

/**
  Function handling exiting suspend mode.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiExitSuspendState (
  VOID
  )
;

/**
  Function handling recovery proccess.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiRecovery (
  VOID
  )
;

/**
  Function displaing Ivs strings.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES    Unable to allocate necessary data structures.
**/
EFI_STATUS
AtAmUiDisplayIsvStrings (
  VOID
  )
;

/**
  This GetRecoveryPassword() process the AT recovery password user input.

  @param[out] PasswordASCII       Pointer to an array of ASCII user input
  @param[in] MaxPasswordLength    Integer value for max password length
  @param[out] PasswordUNICODE     Pointer to an array of UNICODE user input
  @param[in] ShowPassword         TRUE - password is shown, FALSE - pasword is hidden by *

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES Do not have enough resources to allocate memory or password too long.
**/
EFI_STATUS
AtAmUiGetPassword (
  OUT UINT8                       *PasswordASCII,
  IN INTN                         MaxPasswordLength,
  OUT CHAR16                      *PasswordUNICODE,
  IN UINT8                        ShowPassword
  )
;
#endif
