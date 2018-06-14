/** @file
  Defines and prototypes for the ActiveBios driver.
  This driver implements the ActiveBios protocol for the PCH.
  It provides a simple implementation that allows for basic control
  of the PCH flash mapping state.

@copyright
  Copyright (c) 2005 - 2012 Intel Corporation. All rights reserved
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
#ifndef _ACTIVE_BIOS_H_
#define _ACTIVE_BIOS_H_

//
// Include files
//
//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)

#include "EdkIIGlueDxe.h"

#include EFI_PROTOCOL_PRODUCER (ActiveBios)
#include "PchAccess.h"
#include "PchPlatformLib.h"
#endif
//
// Active BIOS private data
//
#define ACTIVE_BIOS_SIGNATURE EFI_SIGNATURE_32 ('D', 'P', 'B', 'A')

typedef struct {
  UINT32                    Signature;
  EFI_HANDLE                Handle;
  EFI_ACTIVE_BIOS_PROTOCOL  ActiveBiosProtocol;
  UINTN                     CurrentKey;
  BOOLEAN                   Locked;
} ACTIVE_BIOS_INSTANCE;

#define ACTIVE_BIOS_INSTANCE_FROM_ACTIVE_BIOS_THIS(a) \
  CR ( \
  a, \
  ACTIVE_BIOS_INSTANCE, \
  ActiveBiosProtocol, \
  ACTIVE_BIOS_SIGNATURE \
  )

//
// Driver global data
//
extern ACTIVE_BIOS_INSTANCE mPrivateData;
extern UINT32               mPchRootComplexBar;

//
// Protocol constructor
//

/**
  Initialization function for the ActiveBios protocol implementation.

  @param[in] This                 Pointer to the protocol

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
ActiveBiosProtocolConstructor (
  IN  EFI_ACTIVE_BIOS_PROTOCOL      *This
  );

//
// Driver entry point
//

/**
  ActiveBios driver entry point function.

  @param[in] ImageHandle          Image handle for this driver image
  @param[in] SystemTable          Pointer to the EFI System Table

  @retval EFI_SUCCESS             Application completed successfully
  @exception EFI_UNSUPPORTED      Unsupported chipset detected
**/
EFI_STATUS
InstallActiveBios (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

#endif
