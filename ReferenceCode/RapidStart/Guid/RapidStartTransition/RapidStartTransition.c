/** @file
  GUIDs used for RapidStart Transition.

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
#include "EdkIIGluePeim.h"
#include "RapidStartConfig.h"
#include "RapidStartTransition.h"
#include EFI_PPI_DEFINITION (PeiGfxPpi)

///
/// The purpose of this PPI GUID is to trigger the RapidStartTransition
/// for IBVs can decide the best point to trigger our Rapid Start module.
///
#ifdef RAPID_START_ON_START_PPI_INSTALLED
EFI_GUID  gRapidStartTransitionPpiGuid = PEI_RAPID_START_TRANSITION_PPI_GUID;
#else
EFI_GUID  gRapidStartTransitionPpiGuid = PEI_GFX_PPI_GUID;
#endif

EFI_GUID_STRING(&gRapidStartTransitionPpiGuid, "RapidStart Transition", "RapidStart Transition GUID");
