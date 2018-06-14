/** @file
  Header file for the PCH SPI SMM Driver.

@copyright
  Copyright (c) 2004 - 2012 Intel Corporation. All rights reserved
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
#include "EfiScriptLib.h"

//
// Driver Dependency Protocols
//
#include EFI_PROTOCOL_DEPENDENCY (SmmBase)
#include EFI_PROTOCOL_CONSUMER (BootScriptSave)
#endif

/**
  This function is a a hook for Spi Smm phase specific initialization

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
