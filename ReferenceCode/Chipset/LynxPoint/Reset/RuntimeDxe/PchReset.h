/** @file
  Header file for PCH RESET Runtime Driver

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
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
#ifndef _PCH_RESET_H
#define _PCH_RESET_H

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include EFI_PROTOCOL_PRODUCER  (PchReset)
#include EFI_PROTOCOL_CONSUMER  (PchPlatformPolicy)
#include EFI_GUID_DEFINITION    (Capsule)
#include "PchResetCommon.h"
#include "DxeRuntimePciLibPciExpress.h"
#endif

/**
  Initialize the state information for the Timer Architectural Protocol

  @param[in] ImageHandle          Image handle of the loaded driver
  @param[in] SystemTable          Pointer to the System Table

  @retval EFI_SUCCESS             Thread can be successfully created
  @retval EFI_OUT_OF_RESOURCES    Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR        Cannot create the timer service
**/
EFI_STATUS
EFIAPI
InstallPchReset (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

/**
  Execute call back function for Pch Reset.

  @param[in] PchResetType         Pch Reset Types which includes PowerCycle, Globalreset.

  @retval EFI_SUCCESS             The callback function has been done successfully
  @retval EFI_NOT_FOUND           Failed to find Pch Reset Callback protocol. Or, none of
                                  callback protocol is installed.
  @retval Others                  Do not do any reset from PCH
**/
EFI_STATUS
EFIAPI
PchResetCallback (
  IN     PCH_RESET_TYPE           PchResetType
  );

/**
  Fixup internal data pointers so that the services can be called in virtual mode.

  @param[in] Event                The event registered.
  @param[in] Context              Event context. Not used in this event handler.

  @retval None
**/
VOID
PchResetVirtualAddressChangeEvent (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  );
#endif
