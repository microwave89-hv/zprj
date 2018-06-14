/** @file
  This file defines SMM Thunk abstraction protocol.

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
#ifndef _SMM_THUNK_H_
#define _SMM_THUNK_H_

EFI_FORWARD_DECLARATION (EFI_SMM_THUNK_PROTOCOL);

///
/// include LegacyBios Protocol for IA32_REGISTER_SET
///
#include EFI_PROTOCOL_DEFINITION (LegacyBios)

#define EFI_SMM_THUNK_PROTOCOL_GUID \
  { \
    0x2a82fce6, 0x8bb6, 0x413e, 0xb9, 0xeb, 0x45, 0xdf, 0xc0, 0x52, 0x2d, 0xf3 \
  }

typedef
BOOLEAN
(EFIAPI *EFI_SMM_FARCALL86)(
  IN EFI_SMM_THUNK_PROTOCOL          *This,
  IN UINT16                          Segment,
  IN UINT16                          Offset,
  IN OUT EFI_IA32_REGISTER_SET *Regs OPTIONAL,
  IN VOID *Stack                     OPTIONAL,
  IN UINTN                           StackSize
  );

typedef
BOOLEAN
(EFIAPI *EFI_SMM_INTCALL86)(
  IN EFI_SMM_THUNK_PROTOCOL          *This,
  IN UINT16                          Segment,
  IN UINT16                          Offset,
  IN OUT EFI_IA32_REGISTER_SET *Regs OPTIONAL,
  IN VOID *Stack                     OPTIONAL,
  IN UINTN                           StackSize
  );

struct _EFI_SMM_THUNK_PROTOCOL {
  EFI_SMM_FARCALL86 FarCall86;
  EFI_SMM_INTCALL86 IntCall86;
};

extern EFI_GUID gEfiSmmThunkProtocolGuid;

#endif
