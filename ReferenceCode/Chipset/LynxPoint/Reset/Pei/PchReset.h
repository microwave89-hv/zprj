/** @file
  Header file for PCH RESET PEIM Driver.

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

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include EFI_PPI_PRODUCER (PchReset)
#include "PchResetCommon.h"
#include EFI_PPI_CONSUMER (MemoryDiscovered)
#include "PchAccess.h"
#endif

typedef struct {
  EFI_PEI_PPI_DESCRIPTOR  PpiDescriptor;
  PCH_RESET_INSTANCE      PchResetInstance;
} PEI_PCH_RESET_INSTANCE;

/**
  Installs PCH RESET PPI

  @param[in] FfsHeader            Not used.
  @param[in] PeiServices          General purpose services available to every PEIM.

  @retval EFI_SUCCESS             PCH SPI PPI is installed successfully
  @retval EFI_OUT_OF_RESOURCES    Can't allocate pool
**/
EFI_STATUS
InstallPchReset (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  );

/**
  Execute call back function for Pch Reset.

  @param[in] PchResetType         Pch Reset Types which includes PowerCycle, Globalreset.

  @retval EFI_SUCCESS             The callback function has been done successfully
  @exception EFI_UNSUPPORTED      Do not do any reset from PCH
**/
EFI_STATUS
EFIAPI
PchResetCallback (
  IN     PCH_RESET_TYPE           PchResetType
  );
#endif
