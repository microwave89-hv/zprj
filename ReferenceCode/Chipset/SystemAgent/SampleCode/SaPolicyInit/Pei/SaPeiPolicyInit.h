/** @file
  Header file for the SaPeiPolicyInit PEIM.

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
#ifndef _SA_PEI_PLATFORM_POLICY_H_
#define _SA_PEI_PLATFORM_POLICY_H_

///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "SaAccess.h"
#include "MrcApi.h"
#include "CpuRegs.h"
#include "CpuPlatformLib.h"

#include EFI_PPI_PRODUCER (SaPlatformPolicy)
#include EFI_GUID_DEFINITION (SaDataHob)
#endif

#include "SaPlatformPolicyUpdatePeiLib.h"

///
/// Functions
///
/**
  This PEIM performs SA PEI Platform Policy initialzation.

  @param[in] FfsHeader    - Pointer to Firmware File System file header.
  @param[in] PeiServices  - General purpose services available to every PEIM.

  @retval EFI_SUCCESS - The PPI is installed and initialized.
  @retval EFI ERRORS  - The PPI is not successfully installed.
**/
EFI_STATUS
SaPeiPolicyInitEntryPoint (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
;
#endif
