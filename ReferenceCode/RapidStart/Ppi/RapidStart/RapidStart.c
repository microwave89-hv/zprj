/** @file
  This file defines RapidStart PPI

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

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "RapidStart.h"
#endif

///
/// Protocol GUID definition
///
EFI_GUID  gRapidStartPpiGuid = RAPID_START_PPI_GUID;

///
/// Protocol description
///
EFI_GUID_STRING(&gRapidStartPpiGuid, "RapidStartPpi", "Rapid Start PPI");
