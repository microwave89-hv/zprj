/** @file
  This file defines the EFI SPI Protocol which implements the
  Intel(R) SPI Host Controller Compatibility Interface.

@copyright
  Copyright (c) 2004 - 2015 Intel Corporation. All rights reserved
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

//
// Statements that include other files
//
//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#endif
//
// Include the protocol header file
//
#include "Spi.h"

//
// Protocol GUID definition
//
EFI_GUID  gEfiSpiProtocolGuid     = EFI_SPI_PROTOCOL_GUID;
EFI_GUID  gEfiSmmSpiProtocolGuid  = EFI_SMM_SPI_PROTOCOL_GUID;
EFI_GUID  gEfiSpiDataProtocolGuid = EFI_SPI_DATA_PROTOCOL_GUID;

//
// Protocol description
//
EFI_GUID_STRING(&gEfiSpiProtocolGuid, "SPI Protocol", "Intel(R) Serial Peripheral Interface Protocol");
EFI_GUID_STRING(&gEfiSmmSpiProtocolGuid, "SMM SPI Protocol", "Intel(R) Serial Peripheral Interface Protocol");
EFI_GUID_STRING(&gEfiSpiDataProtocolGuid, "SPI Data Protocol", "Intel(R) Serial Peripheral Data Interface Protocol");
