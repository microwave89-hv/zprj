/** @file
  Dump whole ME_BIOS_EXTENSION_SETUP and serial out.

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
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

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "AmtPolicyLib.h"
#endif

/**
  Dump ME_BIOS_EXTENSION_SETUP variable

  @param[in] MeBiosExtensionSetup   Pointer to ME_BIOS_EXTENSION_SETUP variable

  @retval None
**/
VOID
DxeMebxSetupVariableDebugDump (
  IN ME_BIOS_EXTENSION_SETUP      *MeBiosExtensionSetup OPTIONAL
  )
{
  EFI_STATUS                Status;
  UINTN                     VariableSize;
  ME_BIOS_EXTENSION_SETUP   MeBxSetup;
  ME_BIOS_EXTENSION_SETUP   *MeBxSetupPtr;

  if (MeBiosExtensionSetup == NULL) {
    Status = gRT->GetVariable (
              gEfiMeBiosExtensionSetupName,
              &gEfiMeBiosExtensionSetupGuid,
              NULL,
              &VariableSize,
              &MeBxSetup
              );
    if (EFI_ERROR(Status)) {
      return;
    }
    MeBxSetupPtr = &MeBxSetup;
  } else {
    MeBxSetupPtr = MeBiosExtensionSetup;
  }

  DEBUG ((EFI_D_INFO, "\n------------------------ MeBiosExtensionSetup Dump Begin -----------------\n"));
  DEBUG ((EFI_D_INFO, " InterfaceVersion : 0x%x\n", MeBxSetupPtr->InterfaceVersion));
  DEBUG ((EFI_D_INFO, " Flags : 0x%x\n", MeBxSetupPtr->Flags));
  DEBUG ((EFI_D_INFO, " PlatformMngSel : 0x%x\n", MeBxSetupPtr->PlatformMngSel));
  DEBUG ((EFI_D_INFO, " AmtSolIder : 0x%x\n", MeBxSetupPtr->AmtSolIder));
  DEBUG (
    (EFI_D_INFO,
    " RemoteAssistanceTriggerAvailablilty : 0x%x\n",
    MeBxSetupPtr->RemoteAssistanceTriggerAvailablilty)
    );
  DEBUG ((EFI_D_INFO, " KvmEnable : 0x%x\n", MeBxSetupPtr->KvmEnable));
  DEBUG ((EFI_D_INFO, " MebxDefaultSolIder : 0x%x\n", MeBxSetupPtr->MebxDefaultSolIder));

  DEBUG ((EFI_D_INFO, "\n------------------------ MeBiosExtensionSetup Dump End -------------------\n"));

}
