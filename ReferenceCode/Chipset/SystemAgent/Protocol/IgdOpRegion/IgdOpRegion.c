/** @file
  This file is part of the IGD OpRegion Implementation.  The IGD OpRegion is
  an interface between system BIOS, ASL code, and Graphics drivers.  The code
  in this file will implement a protocol allowing access to the
  OpRegion from ASL code.

  Supporting Specifiction: IGD OpRegion/Software SCI BIOS SPEC

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
#include "Tiano.h"
#include "IgdOpRegion.h"

EFI_GUID  gIgdOpRegionProtocolGuid = IGD_OPREGION_PROTOCOL_GUID;

EFI_GUID_STRING
  (
    &gIgdOpRegionProtocolGuid, "IGD OpRegion/Software SCI",
      "Communication interface between Graphics drivers, ASL code, and system BIOS"
  );
