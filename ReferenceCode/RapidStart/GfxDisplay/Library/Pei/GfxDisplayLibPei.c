/** @file
  Implementation file for GfxDisplay Pei functionality

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

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "GfxDisplayLibPei.h"
#include EFI_PPI_DEFINITION (PeiGfxPpi)
#endif

/**
   This function allows the platform to restore the display to the Display Save State.

  @retval EFI_SUCCESS           - RapidStartGfxDisplayScreen succeeded
  @retval EFI_INVALID_PARAMETER - Invalid Parameter
  @retval EFI_NOT_FOUND         - Display Save State Header Signature failed
**/
EFI_STATUS
RapidStartGfxDisplayScreen (
  VOID
  )
{
  EFI_STATUS                      Status;
  PEI_GFX_PPI                     *PeiGfxPpi;

  DEBUG ((EFI_D_INFO, "RapidStartGfxDisplayScreen Start\n"));
  Status = PeiServicesLocatePpi (&gPeiGfxPpiGuid, 0, NULL, &PeiGfxPpi);
  ASSERT_EFI_ERROR (Status);

  Status = PeiGfxPpi->RestoreDisplay (GetPeiServicesTablePointer ());
  DEBUG ((EFI_D_INFO, "Call PeiGfxPpi->RestoreDisplay, Status = %r\n", Status));

  return Status;
}
