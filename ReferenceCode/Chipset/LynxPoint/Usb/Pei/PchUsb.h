/** @file
  Header file for the PCH USB PEIM

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
#ifndef _PCH_USB_H_
#define _PCH_USB_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "PchAccess.h"
#include EFI_PPI_CONSUMER (PchUsbPolicy)
#endif

/**
  Initialize PCH EHCI PEIM

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] UsbPolicyPpi         PCH Usb Policy PPI

  @retval EFI_SUCCESS             The PCH EHCI PEIM is initialized successfully
  @retval EFI_INVALID_PARAMETER   UsbControllerId is out of range
  @retval EFI_OUT_OF_RESOURCES    Insufficient resources to create database
  @retval Others                  All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
InitForEHCI (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN PCH_USB_POLICY_PPI         *UsbPolicyPpi
  );

#endif
