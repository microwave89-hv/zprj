/** @file
  Interface definition between MRC and SaInitPeim driver.

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

///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#endif

#include "SaPeiInit.h"

///
/// PPI GUID definition
///
EFI_GUID  gSaPeiInitPpiGuid = SA_PEI_INIT_PPI_GUID;

///
/// PPI description
///
EFI_GUID_STRING(&gSaPeiInitPpiGuid, "SA PEI Init PPI", "SA PEI Initialization PPI");
