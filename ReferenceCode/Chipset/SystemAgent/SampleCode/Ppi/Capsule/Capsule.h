/** @file
  Capsule PPI definitions.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
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

#ifndef _PEI_CAPSULE_PPI_H_
#define _PEI_CAPSULE_PPI_H_

#define PEI_CAPSULE_PPI_GUID \
  { \
    0x3acf33ee, 0xd892, 0x40f4, 0xa2, 0xfc, 0x38, 0x54, 0xd2, 0xe1, 0x32, 0x3d \
  }

EFI_FORWARD_DECLARATION (PEI_CAPSULE_PPI);

typedef
EFI_STATUS
(EFIAPI *PEI_CAPSULE_COALESCE) (
  IN EFI_PEI_SERVICES                **PeiServices,
  IN OUT VOID                        **MemoryBase,
  IN OUT UINTN                       *MemSize
  );

typedef
EFI_STATUS
(EFIAPI *PEI_CAPSULE_CREATE_STATE) (
  IN EFI_PEI_SERVICES                                 **PeiServices,
  IN VOID                                             *CapsuleBase, /// returned from coalesce
  IN UINTN                              CapsuleSize                 /// returned from coalesce
  );

typedef
EFI_STATUS
(EFIAPI *PEI_CAPSULE_CHECK_CAPSULE_UPDATE) (
  IN EFI_PEI_SERVICES           **PeiServices
  );

struct _PEI_CAPSULE_PPI {
  PEI_CAPSULE_COALESCE              Coalesce;
  PEI_CAPSULE_CHECK_CAPSULE_UPDATE  CheckCapsuleUpdate;
  PEI_CAPSULE_CREATE_STATE          CreateState;
};

extern EFI_GUID gPeiCapsulePpiGuid;

#endif /// #ifndef _PEI_CAPSULE_PPI_H_
