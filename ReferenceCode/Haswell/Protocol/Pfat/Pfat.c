/** @file
  This file defines PFAT Abstraction Protocol

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

///
/// Statements that include other files
///
///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#endif
///
/// Include the PFAT SMM Protocol header file
///
#include "Pfat.h"

///
/// PFAT SMM Protocol GUID definition
///
EFI_GUID gSmmPfatProtocolGuid = SMM_PFAT_PROTOCOL_GUID;

///
/// PFAT SMM Protocol description
///
EFI_GUID_STRING(&gSmmPfatProtocolGuid, "SMM PFAT Protocol", "Intel(R) Platform Firmware Armoring Technology Protocol");
