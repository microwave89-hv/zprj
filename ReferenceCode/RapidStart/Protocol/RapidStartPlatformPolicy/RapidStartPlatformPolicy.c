/** @file
  This file defines the RapidStart Policy Protocol.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
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
// Statements that include other files
//
//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "RapidStartPlatformPolicy.h"
#endif

///
/// Protocol GUID definition
///
EFI_GUID  gRapidStartPlatformPolicyProtocolGuid = RAPID_START_PLATFORM_POLICY_PROTOCOL_GUID;

///
/// Protocol description
///
EFI_GUID_STRING
  (
    &gRapidStartPlatformPolicyProtocolGuid, "RapidStartPlatformPolicy Protocol",
      "Intel(R) DXE Phase RapidStart Platform Policy Protocol"
  );
