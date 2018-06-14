/** @file
  Header file for Me Policy functionality

@copyright
  Copyright (c) 2006 - 2012 Intel Corporation. All rights reserved
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
#ifndef _ME_POLICY_LIB_H_
#define _ME_POLICY_LIB_H_

#include EFI_PROTOCOL_DEFINITION (MePlatformPolicy)

/**
  Check if Me is enabled.

  @param[in] None.

  @retval EFI_SUCCESS             ME platform policy pointer is initialized.
  @retval All other error conditions encountered when no ME platform policy available.
**/
EFI_STATUS
MePolicyLibInit (
  VOID
  )
;

/**
  Check if End of Post Message is enabled in setup options.

  @param[in] None.

  @retval FALSE                   EndOfPost is disabled.
  @retval TRUE                    EndOfPost is enabled.
**/
BOOLEAN
MeEndOfPostEnabled (
  VOID
  )
;


/**
  Show Me Error message. This is used to support display error message on the screen for localization
  description

  @param[in] MsgId                Me error message ID for displaying on screen message

  @retval None
**/
VOID
MeReportError (
  IN ME_ERROR_MSG_ID              MsgId
  )
;

/**
  Check if MeFwDowngrade is enabled in setup options.

  @param[in] None.

  @retval FALSE                   MeFwDowngrade is disabled.
  @retval TRUE                    MeFwDowngrade is enabled.
**/
BOOLEAN
MeFwDowngradeSupported (
  VOID
  )
;

/**
  Dump DXE ME Platform Policy

  @param[in] None.

  @retval None
**/
VOID
DxeMePolicyDebugDump (
  VOID
  )
;
#endif
