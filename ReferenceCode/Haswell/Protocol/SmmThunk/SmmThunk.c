/** @file
  This file defines SMM thunk abstraction protocol

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
#include EFI_PROTOCOL_DEFINITION (SmmThunk)

EFI_GUID gEfiSmmThunkProtocolGuid = EFI_SMM_THUNK_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiSmmThunkProtocolGuid, "SMM Thunk Protocol", "SMM Thunk protocol");
