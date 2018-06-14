/** @file
  Definitions for HECI driver

@copyright
  Copyright (c) 2006 - 2012 Intel Corporation. All rights reserved
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
#ifndef _HECI_DRV_H
#define _HECI_DRV_H

#include "EdkIIGlueDxe.h"
#include "MeAccess.h"
#include "HeciRegs.h"
#include "Pci22.h"
#include "RcFviDxeLib.h"

#include EFI_PROTOCOL_CONSUMER (PciRootBridgeIo)

#define HECI_PRIVATE_DATA_SIGNATURE         EFI_SIGNATURE_32 ('H', 'e', 'c', 'i')
#define HECI_ROUND_UP_BUFFER_LENGTH(Length) ((UINT32) ((((Length) + 3) / 4) * 4))

//
// Driver Produced Protocol Prototypes
//
#include EFI_PROTOCOL_PRODUCER (Heci)
#include EFI_PROTOCOL_PRODUCER (MeRcInfo)

//
// Driver Consumed Protocol Prototypes
//
#include EFI_PROTOCOL_CONSUMER (MebxProtocol)

extern FVI_ELEMENT_AND_FUNCTION       mMeFviElementsData[];
extern FVI_DATA_HUB_CALLBACK_CONTEXT  mMeFviVersionData;
extern UINTN                          mMeFviElements;

typedef union {
  UINT32  Data32;
  UINT16  Data16[2];
  UINT8   Data8[4];
} DATA32_UNION;

///
/// HECI private data structure
///
typedef struct {
  UINTN                   Signature;
  EFI_HANDLE              Handle;
  UINT64                  HeciMBAR;
  UINT16                  DeviceInfo;
  UINT32                  RevisionInfo;
  EFI_HECI_PROTOCOL       HeciCtlr;
  VOLATILE UINT32         *HpetTimer;
  EFI_ME_RC_INFO_PROTOCOL MeRcInfo;
  UINT8                   MeFwImageType;
} HECI_INSTANCE;
#endif
