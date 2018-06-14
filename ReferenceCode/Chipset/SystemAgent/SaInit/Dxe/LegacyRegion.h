/** @file
  This code supports a private implementation of the Legacy Region protocol.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _LEGACY_REGION_H_
#define _LEGACY_REGION_H_

#include "EdkIIGlueDxe.h"
#include "Pci22.h"

#include EFI_PROTOCOL_PRODUCER (LegacyRegion)
#include EFI_PROTOCOL_DEFINITION (PciRootBridgeIo)
#define LEGACY_REGION_INSTANCE_SIGNATURE  EFI_SIGNATURE_32 ('R', 'E', 'G', 'N')

#include EFI_ARCH_PROTOCOL_CONSUMER (Cpu)
#define LEGACY_REGION_DECODE_ROM  3

#include "SaAccess.h"

///
/// PAM registers granularity is 16 KB
///
#define PAM_GRANULARITY 0x4000
#define UNLOCK          0x0000
#define LOCK            0x0001
#define BOOTLOCK        0x0002

typedef struct {
  UINT32                          Signature;
  EFI_HANDLE                      Handle;
  EFI_LEGACY_REGION_PROTOCOL      LegacyRegion;
  EFI_HANDLE                      ImageHandle;

  ///
  /// Protocol for PAM register access
  ///
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;
} LEGACY_REGION_INSTANCE;

#define LEGACY_REGION_INSTANCE_FROM_THIS  (this) CR (this, \
                                                     LEGACY_REGION_INSTANCE, \
                                                     LegacyRegion, \
                                                     LEGACY_REGION_INSTANCE_SIGNATURE \
        )

/**
  Install Driver to produce Legacy Region protocol.

  @param[in] ImageHandle             Handle for the image of this driver

  @retval EFI_SUCCESS - Legacy Region protocol installed
  @retval Other       - No protocol installed, unload driver.
**/
EFI_STATUS
LegacyRegionInstall (
  IN EFI_HANDLE           ImageHandle
  )
;

#endif
