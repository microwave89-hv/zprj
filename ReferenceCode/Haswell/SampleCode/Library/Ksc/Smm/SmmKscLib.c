/** @file
  SMM KSC library implementation.

  These functions need to be SMM safe.

  These functions require the SMM IO library (SmmIoLib) to be present.
  Caller must link those libraries and have the proper include path.

@copyright
  Copyright (c) 1999 - 2013 Intel Corporation. All rights reserved
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
#include "KscLib.h"
#include "SmmIoLib.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"

BOOLEAN mSmmKscLibInitialized = FALSE;

///
/// Function implemenations
///
/**
  Initialize the library.
  The SMM library only requires SMM IO library and has no initialization.
  However, this must be called prior to use of any other KSC library functions
  for future compatibility.

  @param[in] None.

  @retval EFI_SUCCESS       - KscLib is successfully initialized.
**/
EFI_STATUS
InitializeKscLib (
  VOID
  )
{
  EFI_STATUS Status;

  ///
  /// Fail if EC doesn't exist.
  ///
  if (SmmIoRead8 (KSC_C_PORT) == 0xff) {
    mSmmKscLibInitialized = FALSE;
    Status                = EFI_DEVICE_ERROR;
  } else {
    mSmmKscLibInitialized = TRUE;
    Status                = EFI_SUCCESS;
  }

  return Status;
}

/**
  Sends command to Keyboard System Controller.

  @param[in] Command  - Command byte to send

  @retval EFI_SUCCESS       - Command success
  @retval EFI_DEVICE_ERROR  - Command error
**/
EFI_STATUS
SendKscCommand (
  UINT8 Command
  )
{
  UINTN Index;
  UINT8 KscStatus;

  KscStatus = 0;
  ///
  /// Verify if KscLib has been initialized, NOT if EC dose not exist.
  ///
  if (mSmmKscLibInitialized == FALSE) {
    return EFI_DEVICE_ERROR;
  }

  Index = 0;

  ///
  /// Wait for KSC to be ready (with a timeout)
  ///
  ReceiveKscStatus (&KscStatus);
  while (((KscStatus & KSC_S_IBF) != 0) && (Index < KSC_TIME_OUT)) {
    PchPmTimerStall(15);
    ReceiveKscStatus (&KscStatus);
    Index++;
  }

  if (Index >= KSC_TIME_OUT) {
    return EFI_DEVICE_ERROR;
  }
  ///
  /// Send the KSC command
  ///
  SmmIoWrite8 (KSC_C_PORT, Command);

  return EFI_SUCCESS;
}

/**
  Receives status from Keyboard System Controller.

  @param[in] KscStatus  - Status byte to receive

  @retval EFI_DEVICE_ERROR  - Ksc library has not initialized yet or KSC not present
  @retval EFI_SUCCESS       - Get KSC status successfully
**/
EFI_STATUS
ReceiveKscStatus (
  UINT8 *KscStatus
  )
{
  ///
  /// Verify if KscLib has been initialized, NOT if EC dose not exist.
  ///
  if (mSmmKscLibInitialized == FALSE) {
    return EFI_DEVICE_ERROR;
  }
  ///
  /// Read and return the status
  ///
  *KscStatus = SmmIoRead8 (KSC_C_PORT);

  return EFI_SUCCESS;
}

/**
  Sends data to Keyboard System Controller.

  @param[in] Data  - Data byte to send

  @retval EFI_SUCCESS       - Success
  @retval EFI_DEVICE_ERROR  - Error
**/
EFI_STATUS
SendKscData (
  UINT8 Data
  )
{
  UINTN Index;
  UINT8 KscStatus;

  ///
  /// Verify if KscLib has been initialized, NOT if EC dose not exist.
  ///
  if (mSmmKscLibInitialized == FALSE) {
    return EFI_DEVICE_ERROR;
  }

  Index = 0;

  ///
  /// Wait for KSC to be ready (with a timeout)
  ///
  ReceiveKscStatus (&KscStatus);
  while (((KscStatus & KSC_S_IBF) != 0) && (Index < KSC_TIME_OUT)) {
    PchPmTimerStall(15);
    ReceiveKscStatus (&KscStatus);
    Index++;
  }

  if (Index >= KSC_TIME_OUT) {
    return EFI_DEVICE_ERROR;
  }
  ///
  /// Send the data and return
  ///
  SmmIoWrite8 (KSC_D_PORT, Data);

  return EFI_SUCCESS;
}

/**
  Receives data from Keyboard System Controller.

  @param[in] Data  - Data byte received

  @retval EFI_SUCCESS       - Read success
  @retval EFI_DEVICE_ERROR  - Read error
**/
EFI_STATUS
ReceiveKscData (
  UINT8 *Data
  )
{
  UINTN Index;
  UINT8 KscStatus;

  ///
  /// Verify if KscLib has been initialized, NOT if EC dose not exist.
  ///
  if (mSmmKscLibInitialized == FALSE) {
    return EFI_DEVICE_ERROR;
  }

  Index = 0;

  ///
  /// Wait for KSC to be ready (with a timeout)
  ///
  ReceiveKscStatus (&KscStatus);
  while (((KscStatus & KSC_S_OBF) == 0) && (Index < KSC_TIME_OUT)) {
    PchPmTimerStall(15);
    ReceiveKscStatus (&KscStatus);
    Index++;
  }

  if (Index >= KSC_TIME_OUT) {
    return EFI_DEVICE_ERROR;
  }
  ///
  /// Read KSC data and return
  ///
  *Data = SmmIoRead8 (KSC_D_PORT);

  return EFI_SUCCESS;
}
