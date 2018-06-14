/** @file
  Protocol used for specifying platform related CPU information and policy setting.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#include "Tiano.h"
#include EFI_PROTOCOL_DEFINITION (CpuPlatformPolicy)

EFI_GUID gDxeCpuPlatformPolicyProtocolGuid = DXE_CPU_PLATFORM_POLICY_PROTOCOL_GUID;

EFI_GUID_STRING
        (&gDxeCpuPlatformPolicyProtocolGuid, "CPU Platform Policy", "Platform related CPU information and policy settings");
