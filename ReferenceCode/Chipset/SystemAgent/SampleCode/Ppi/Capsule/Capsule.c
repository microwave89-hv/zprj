/** @file
  Capsule PPI GUID declaration.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains 'Framework Code' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may not be modified, except as allowed by
  additional terms of your license agreement.
**/

#include "Tiano.h"
#include "PeiBind.h"
#include "PeiApi.h"
#include EFI_PPI_DEFINITION (Capsule)

EFI_GUID  gPeiCapsulePpiGuid = PEI_CAPSULE_PPI_GUID;

EFI_GUID_STRING(&gPeiCapsulePpiGuid, "Capsule", "Capsule Update PPI");
