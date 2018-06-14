/** @file
  GUID Definition for the MP Services Protocol defined in the PI 1.1 spec.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
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
#include EFI_PROTOCOL_DEFINITION (PiMpService)

EFI_GUID gEfiPiMpServiceProtocolGuid = EFI_PI_MP_SERVICES_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiPiMpServiceProtocolGuid, "PI MP SERVICE", "PI MP Service Protocol");
