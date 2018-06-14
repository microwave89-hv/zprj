/** @file
  Header file for the PchPeiPolicy PEIM.

@copyright
  Copyright (c) 2009 - 2012 Intel Corporation. All rights reserved
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
#ifndef _PCH_POLICY_INIT_PEI_H_
#define _PCH_POLICY_INIT_PEI_H_

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include EFI_PPI_PRODUCER (PchPlatformPolicy)
#include "PchAccess.h"
#include "PchPlatformPolicyUpdatePeiLib.h"
#endif

#define PCH_LPC_RCBA_BASE_ADDRESS         0xFED1C000
#define PCH_LPC_ACPI_BASE_ADDRESS         0x1800
#define PCH_LPC_GPIO_BASE_ADDRESS         0x800

#define PCH_TEMP_MEM_BASE_ADDRESS         0xDFFF0000
#define PCH_HPET_BASE_ADDRESS             0xFED00000

//
// Functions
//

/**
  This PEIM performs PCH PEI Platform Policy initialzation.

  @param[in] FfsHeader            Pointer to Firmware File System file header.
  @param[in] PeiServices          General purpose services available to every PEIM.

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI ERRORS              The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
PchPolicyInitPeiEntryPoint (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  );
#endif
