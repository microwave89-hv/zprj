/** @file
  Interface definition Me Platform Get Reset Type.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/
#ifndef _ME_PLATFORM_GET_RESET_TYPE_H_
#define _ME_PLATFORM_GET_RESET_TYPE_H_

#define ME_PLATFORM_GET_RESET_TYPE_GUID \
  { \
    0xb8cdced7, 0xbdc4, 0x4464, 0x9a, 0x1a, 0xff, 0x3f, 0xbd, 0xf7, 0x48, 0x69 \
  }

#define ME_PLATFORM_GET_RESET_TYPE_PROTOCOL_REVISION  1
extern EFI_GUID gMePlatformGetResetTypeGuid;

///
/// ME_SPEICAL_RESET_TYPES must be aligned with PCH_EXTENDED_RESET_TYPES
///
typedef enum {
  PowerCycleResetReq  = 3,
  GlobalResetReq,
  GlobalResetWithEcReq,
  MaxRestReq
} ME_SPEICAL_RESET_TYPES;

/**
  Get Platform requested reset type

  @param[in] Type                 UEFI defined reset type

  @retval ME_SPEICAL_RESET_TYPES  ME reset type aligned with PCH_EXTENDED_RESET_TYPES
**/
typedef
ME_SPEICAL_RESET_TYPES
(EFIAPI *GET_RESET_TYPE) (
  IN EFI_RESET_TYPE               Type
  );

typedef struct _ME_PLATFORM_GET_RESET_TYPE_PROTOCOL {
  GET_RESET_TYPE                  GetResetType;
} ME_PLATFORM_GET_RESET_TYPE_PROTOCOL;

#endif
