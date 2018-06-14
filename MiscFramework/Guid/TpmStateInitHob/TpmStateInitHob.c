/*++

Copyright (c)  1999 - 2002 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  TpmStateInitHob.c

Abstract:

  GUID of the HOB data for TPM state initialization.

--*/

#include "Efi.h"
#include EFI_GUID_DEFINITION (TpmStateInitHob)


EFI_GUID gEfiTpmStateInitHobGuid  = EFI_TPM_STATE_INIT_HUB_GUID;

EFI_GUID_STRING (&gEfiTpmStateInitHobGuid, "TPM State Initialization HOB", "TPM State Initialization HOB");
