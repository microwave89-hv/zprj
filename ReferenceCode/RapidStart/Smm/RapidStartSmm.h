/** @file
  Header file for RapidStart SMM S3 Handler.

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
  identified as "Intel Mobile Silicon Support Module" and is
  licensed for Intel Mobile CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _RAPID_START_SMM_H_
#define _RAPID_START_SMM_H_

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
//
// Driver Consumed Protocol Prototypes
//
#include EFI_PROTOCOL_CONSUMER (LoadedImage)
#include EFI_PROTOCOL_DEPENDENCY (SmmBase)
#include EFI_PROTOCOL_DEPENDENCY (SmmSxDispatch)
#include EFI_PROTOCOL_DEPENDENCY (DevicePath)
#include EFI_ARCH_PROTOCOL_DEFINITION (Variable)

UINT64
ScanValueMem64 (
  VOID*   BaseAddress,
  UINT64  PageSize,
  UINT64  Index
);

#endif
#endif
