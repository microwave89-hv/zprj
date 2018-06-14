/** @file
  Header file for PCH SMM Handler

@copyright
  Copyright (c) 2015 Intel Corporation. All rights reserved
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

#ifndef _PCHLATEINITSMM_H_
#define _PCHLATEINITSMM_H_

///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"

///
/// Driver Consumed Protocol Prototypes
///
#include EFI_PROTOCOL_DEPENDENCY (PchS3Support)
#include EFI_PROTOCOL_DEPENDENCY (SmmBase)
#include EFI_PROTOCOL_DEPENDENCY (SmmIoTrapDispatch)
#include EFI_PROTOCOL_DEPENDENCY (SmmSxDispatch)
#include EFI_PROTOCOL_CONSUMER   (ExitPmAuth)


#endif

/**
  An IO Trap SMI callback to copy the DispatchArray data to SMRAM and unregister the IO Trap.

  @param[in] DispatchHandle  - The handle of this callback, obtained when registering
  @param[in] DispatchContext - Pointer to the EFI_SMM_IO_TRAP_DISPATCH_CALLBACK_CONTEXT

  @retval None
**/
VOID
S3SupportSmmExitPmAuthCallback (
  EFI_EVENT           Event,
  VOID                *ParentImageHandle
);

#endif
