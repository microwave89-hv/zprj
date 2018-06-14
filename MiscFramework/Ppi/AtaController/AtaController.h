//
// This file contains 'Framework Code' and is licensed as such 
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.                 
//
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

  AtaController.h

Abstract:

  ATA Controller PPI as defined in EFI 2.0

  This code abstracts the PEI core to provide ATA services.

--*/

#ifndef _PEI_ATA_CONTROLLER_PPI_H_
#define _PEI_ATA_CONTROLLER_PPI_H_

#define PEI_ATA_CONTROLLER_PPI_GUID \
  { \
    0xa1e2176f, 0xcbda, 0x4f32, 0x87, 0x56, 0x7d, 0x7a, 0xe5, 0x22, 0xd6, 0x93 \
  }

#define PEI_ICH_IDE_NONE        0x00
#define PEI_ICH_IDE_PRIMARY     0x01
#define PEI_ICH_IDE_SECONDARY   0x02
#define PEI_ICH_SATA_NONE       0x04
#define PEI_ICH_SATA_PRIMARY    0x08
#define PEI_ICH_SATA_SECONDARY  0x010

EFI_FORWARD_DECLARATION (PEI_ATA_CONTROLLER_PPI);

typedef
EFI_STATUS
(EFIAPI *PEI_ENABLE_ATA) (
  IN EFI_PEI_SERVICES               **PeiServices,
  IN PEI_ATA_CONTROLLER_PPI         * This,
  IN UINT8                          ChannelMask
  );

typedef struct _PEI_ATA_CONTROLLER_PPI {
  PEI_ENABLE_ATA  EnableAtaChannel;
} PEI_ATA_CONTROLLER_PPI;

extern EFI_GUID gPeiAtaControllerPpiGuid;

#endif
