/** @file
  PCH policy PPI produced by a platform driver specifying various
  expected PCH settings. This PPI is consumed by the PCH PEI modules.

@copyright
  Copyright (c) 2009 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/

//
// Statements that include other files
//
//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)

#include "EdkIIGluePeim.h"
#endif

#include "PchPlatformPolicy.h"

//
// PPI GUID definition
//
EFI_GUID  gPchPlatformPolicyPpiGuid = PCH_PLATFORM_POLICY_PPI_GUID;

//
// PPI description
//
EFI_GUID_STRING(&gPchPlatformPolicyPpiGuid, "PchPlatformPolicy PPI", "Intel(R) DXE Phase PCH Platform Policy PPI");