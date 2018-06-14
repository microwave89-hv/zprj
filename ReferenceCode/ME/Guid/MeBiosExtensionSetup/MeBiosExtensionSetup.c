/** @file
  ME BIOS Extension 16 Setup Options Guid data declarations.

@copyright
  Copyright (c) 2005 - 2012 Intel Corporation. All rights reserved
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
#include EFI_GUID_DEFINITION (MeBiosExtensionSetup)
#endif

EFI_GUID  gEfiMeBiosExtensionSetupGuid = EFI_ME_BIOS_EXTENSION_SETUP_GUID;

EFI_GUID_STRING(&gEfiMeBiosExtensionSetupGuid, "EFI", "Efi Me Bios Extension 16 Setup Options GUID")

CHAR16  gEfiMeBiosExtensionSetupName[] = EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME;
