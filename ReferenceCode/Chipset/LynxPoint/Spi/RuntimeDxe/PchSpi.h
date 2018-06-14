/** @file
  Header file for the PCH SPI Runtime Driver.

@copyright
  Copyright (c) 2004 - 2015 Intel Corporation. All rights reserved
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
#ifndef _PCH_SPI_H_
#define _PCH_SPI_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include EFI_PROTOCOL_PRODUCER (Spi)
#include "SpiCommon.h"
#include "DxeRuntimePciLibPciExpress.h"
#include "EfiScriptLib.h"
#include EFI_PROTOCOL_CONSUMER (BootScriptSave)
#endif

#define  SIZE_4GB    0x0000000100000000ULL

//
// Function prototypes used by the SPI protocol.
//

/**
  Fixup internal data pointers so that the services can be called in virtual mode.

  @param[in] Event                The event registered.
  @param[in] Context              Event context. Not used in this event handler.

  @retval None.
**/
VOID
PchSpiVirtualAddressChangeEvent (
  IN EFI_EVENT              Event,
  IN VOID                   *Context
  );

/**
  This function is a hook for Spi Dxe phase specific initialization

  @param[in] None

  @retval None
**/
VOID
EFIAPI
SpiPhaseInit (
  VOID
  );

/**
  This function is a hook for Spi to disable BIOS Write Protect

  @param[in] None

  @retval None
**/
VOID
EFIAPI
DisableBiosWriteProtect (
  VOID
  );

/**
  This function is a hook for Spi to enable BIOS Write Protect

  @param[in] None

  @retval None
**/
VOID
EFIAPI
EnableBiosWriteProtect (
  VOID
  );

#endif
