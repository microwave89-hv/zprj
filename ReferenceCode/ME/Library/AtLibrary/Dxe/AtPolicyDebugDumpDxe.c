/** @file
  Dump whole DXE_AT_POLICY_PROTOCOL and serial out.

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
#include "AtPolicyLib.h"
#endif

extern DXE_AT_POLICY_PROTOCOL  *mDxePlatformAtPolicy;

/**
  Dump DXE AT Platform Policy

  @param[in] None.

  @retval None
**/
VOID
DxeAtPolicyDebugDump (
  VOID
  )
{
  if (mDxePlatformAtPolicy == NULL) {
    return;
  }
  DEBUG ((EFI_D_INFO, "\n------------------------ AtPlatformPolicy Dump Begin ------------------\n"));
  DEBUG ((EFI_D_INFO, " Revision : 0x%x\n", mDxePlatformAtPolicy->Revision));
  DEBUG ((EFI_D_INFO, "At ---\n"));
  DEBUG ((EFI_D_INFO, " AtConfig : 0x%x\n", mDxePlatformAtPolicy->At.AtAmBypass));
  DEBUG ((EFI_D_INFO, " AtEnterSuspendState : 0x%x\n", mDxePlatformAtPolicy->At.AtEnterSuspendState));
  DEBUG ((EFI_D_INFO, "\n------------------------ AtPlatformPolicy Dump End --------------------\n"));
}

