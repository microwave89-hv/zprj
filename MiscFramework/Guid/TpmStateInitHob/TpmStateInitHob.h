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

  TpmStateInitHob.h

Abstract:

  GUID of the HOB data for TPM state initialization.

--*/

#ifndef _EFI_TPM_STATE_INIT_HUB_GUID_H_
#define _EFI_TPM_STATE_INIT_HUB_GUID_H_

#define EFI_TPM_STATE_INIT_HUB_GUID \
  { 0xA0C6D918, 0x8DEE, 0x41BB, 0x9D, 0x92, 0x67, 0x53, 0xA5, 0x72, 0xB6, 0x52 };

typedef struct {
  BOOLEAN           TpmEnabledStateFlag;
  BOOLEAN           TpmActivatedStateFlag;
  BOOLEAN           TpmOwnedStateFlag;
  UINT8             Reserved[5];
} EFI_TPM_STATE_FLAGS;


extern EFI_GUID gEfiTpmStateInitHobGuid;

#endif // _EFI_TPM_STATE_INIT_HUB_GUID_H_
