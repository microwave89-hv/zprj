/** @file
  Header file for the CpuPolicyInitDxe Driver.

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
#ifndef _CPU_PLATFORM_POLICY_DXE_H_
#define _CPU_PLATFORM_POLICY_DXE_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "CpuAccess.h"
#endif

#include "UefiIfrLibrary.h"
#include "PowermgmtDefinitions.h"
#include EFI_PROTOCOL_PRODUCER (CpuPlatformPolicy)
//AMI_REMOVE_FOR_COMPILE
//#include "CpuPlatformPolicyUpdateDxeLib.h"

/**
  Initilize Intel CPU DXE Policy

  @param[in] ImageHandle             Image handle of this driver.
  @param[in] SystemTable             Global system service table.

  @retval EFI_SUCCESS             Initialization complete.
  @exception EFI_UNSUPPORTED         The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
CpuPolicyInitDxeEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN OUT EFI_SYSTEM_TABLE *SystemTable
  );

#endif
