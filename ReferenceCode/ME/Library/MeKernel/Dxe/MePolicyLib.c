/** @file
  Implementation file for Me Policy functionality

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

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "MePolicyLib.h"
#include "MeAccess.h"
#include EFI_PROTOCOL_DEFINITION (HECI)
#endif

//
// Global variables
//
DXE_ME_POLICY_PROTOCOL            *mDxePlatformMePolicy = NULL;

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
{
  EFI_STATUS                      Status;

  if (mDxePlatformMePolicy != NULL) {
    return EFI_SUCCESS;
  }
  //
  // Get the desired platform setup policy.
  //
  Status = gBS->LocateProtocol (&gDxePlatformMePolicyGuid, NULL, (VOID **) &mDxePlatformMePolicy);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "No ME Platform Policy Protocol available"));
    ASSERT_EFI_ERROR (Status);
  } else if (mDxePlatformMePolicy == NULL) {
    DEBUG ((EFI_D_ERROR, "No ME Platform Policy Protocol available"));
    Status = EFI_UNSUPPORTED;
  }
  return Status;
}

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
{
  BOOLEAN                         Supported;
  EFI_STATUS                      Status;

  if (mDxePlatformMePolicy == NULL) {
    Status = MePolicyLibInit();
    if (EFI_ERROR(Status)) {
      return FALSE;
    }
  }
  if (mDxePlatformMePolicy->MeConfig.EndOfPostEnabled != 1) {
    Supported = FALSE;
  } else {
    Supported = TRUE;
  }

  return Supported;
}

/**
  Checks if EndOfPost event already happened

  @param[in] None

  @retval TRUE                    if end of post happened
  @retval FALSE                   if not yet
**/
BOOLEAN
IsAfterEndOfPost (
  VOID
  )
{
  EFI_STATUS                      Status;

  if (mDxePlatformMePolicy == NULL) {
    Status = MePolicyLibInit();
    if (EFI_ERROR(Status)) {
      return FALSE;
    }
  }

  if (mDxePlatformMePolicy->MeConfig.EndOfPostDone == TRUE) {
    return TRUE;
  }

  return FALSE;
}

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
{
  EFI_STATUS                      Status;

  if (mDxePlatformMePolicy == NULL) {
    Status = MePolicyLibInit();
    if (EFI_ERROR(Status)) {
      return;
    }
  }
  mDxePlatformMePolicy->MeReportError (MsgId);

  return ;
}

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
{
  EFI_STATUS                      Status;

  if (mDxePlatformMePolicy == NULL) {
    Status = MePolicyLibInit();
    if (EFI_ERROR(Status)) {
      return FALSE;
    }
  }
  if (mDxePlatformMePolicy->MeConfig.MeFwDownGrade == 1) {
    return TRUE;
  }

  return FALSE;
}
