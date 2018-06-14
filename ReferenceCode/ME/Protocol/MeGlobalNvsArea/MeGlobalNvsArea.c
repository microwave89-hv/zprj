/** @file
  ME FW Global NVS Area description protocol implementation.

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
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
#include "EdkIIGlueDxe.h"

#include "MeGlobalNvsArea.h"

EFI_GUID  gMeGlobalNvsAreaProtocolGuid = ME_GLOBAL_NVS_AREA_PROTOCOL_GUID;

EFI_GUID_STRING
  (
    &gMeGlobalNvsAreaProtocolGuid, "ME Global NVS Area Protocol",
      "Protocol describing MEFW ACPI NVS memory region used by ACPI subsystem."
  );
