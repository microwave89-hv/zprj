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

  TcgLogHob.c

Abstract:

  GUIDs used for TCG event log table

--*/

#include "Efi.h"
#include EFI_GUID_DEFINITION (TcgLogHob)


EFI_GUID gEfiTcgLogHobGuid  = EFI_TCG_LOG_HOB_GUID;

EFI_GUID_STRING (&gEfiTcgLogHobGuid, "TCG Event Log HOB", "TCG Event Log HOB");
