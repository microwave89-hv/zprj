/** @file
  This code abstracts the PEI core to provide SmmControl services.

@copyright
  Copyright (c) 2002 - 2012 Intel Corporation. All rights reserved
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

#include "Tiano.h"
#include "Pei.h"
#include EFI_PPI_DEFINITION (SmmControl)

EFI_GUID  gPeiSmmControlPpiGuid = PEI_SMM_CONTROL_PPI_GUID;

EFI_GUID_STRING(&gPeiSmmControlPpiGuid, "SmmControl", "SMM Control PPI");
