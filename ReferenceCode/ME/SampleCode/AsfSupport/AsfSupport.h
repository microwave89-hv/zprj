/** @file
  ASF BDS Support include file

@copyright
  Copyright (c) 2005-2012 Intel Corporation. All rights reserved
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
#ifndef _ASF_SUPPORT_H_
#define _ASF_SUPPORT_H_

#include "EdkIIGlueDxe.h"
#include "BdsLib.h"
#include "Pci22.h"
#include "Amt.h"
#include "AmtLib.h"
#include "MeAccess.h"

#include EFI_PROTOCOL_DEFINITION (LegacyBios)
#include EFI_PROTOCOL_DEFINITION (SimpleNetwork)
#include EFI_PROTOCOL_DEFINITION (FirmwareVolume)
#include EFI_PROTOCOL_DEFINITION (PciRootBridgeIo)

#include EFI_PROTOCOL_CONSUMER (AlertStandardformat)
#include EFI_PROTOCOL_CONSUMER (DiskInfo)

#include EFI_PROTOCOL_DEFINITION (IderControllerDriver)

#define IDER_PRIMARY_SECONDARY_MASK   0x02
#define IDER_MASTER_SLAVE_MASK        0x01
#define IDER_PRIMARY_SECONDARY_SHIFT  1

#define IS_IDER(BUS, DEVICE,FUNCTION) \
  (BUS == ME_BUS && DEVICE == ME_DEVICE_NUMBER && FUNCTION == IDER_FUNCTION_NUMBER)
#define IS_PXE(TYPE, CLASS) \
  (TYPE == BBS_TYPE_BEV && CLASS == PCI_CLASS_NETWORK)
#define IS_CDROM(TYPE, CLASS) \
  (TYPE == BBS_TYPE_BEV && CLASS == PCI_CLASS_MASS_STORAGE)

#define SECURE_BOOT_ENABLED               1
#define SECURE_BOOT_DISABLED              0

#define RESTORE_SECURE_BOOT_NONE          0
#define RESTORE_SECURE_BOOT_ENABLED       1

#define RESTORE_SECURE_BOOT_GUID \
  { \
    0x118b3c6f, 0x98d6, 0x4d05, 0x96, 0xb2, 0x90, 0xe4, 0xcb, 0xb7, 0x40, 0x34 \
  }

typedef union {
  UINT32  Data32;
  UINT16  Data16[2];
} DATA32_UNION;

/**
  Retrieve the ASF boot options previously recorded by the ASF driver.

  @param[in] None.

  @retval EFI_SUCCESS        Initialized Boot Options global variable and AMT protocol
**/
EFI_STATUS
BdsAsfInitialization (
  IN  VOID
  )
;

/**
  This routine makes necessary Secure Boot & CSM state changes for IDEr boot

  @param[in] None.

  @retval EFI_SUCCESS      Changes applied succesfully
**/
EFI_STATUS
ManageSecureBootState(
  IN VOID
  )
;

/**
  This function will create a BootOption from the give device path and
  description string.

  @param[in]  DevicePath     The device path which the option represent
  @param[in]  Description     The description of the boot option

  @retval BDS_COMMON_OPTION - Pointer to created boot option
**/
BDS_COMMON_OPTION *
BdsCreateBootOption (
  IN  EFI_DEVICE_PATH_PROTOCOL       *DevicePath,
  IN  CHAR16                         *Description
  )
;

/**
  Dump all devices of BBS.

  @param[in] LocalBbsTable      BBS table entry.
**/
VOID
PrintBbsTable (
  IN BBS_TABLE                      *LocalBbsTable
  )
;

/**
  This will return if Media in IDE-R is present.

  @param[in] None.

  @retval TRUE    Media is present.
  @retval FALSE   Media is not present.
**/
BOOLEAN
BdsCheckIderMedia (
  IN  VOID
  )
;

/**
  This function will create a SHELL BootOption to boot.

  @param[in]  None.

  @retval EFI_DEVICE_PATH_PROTOCOL Shell Device path for booting.
**/
EFI_DEVICE_PATH_PROTOCOL *
BdsCreateShellDevicePath (
  VOID
  )
;

/**
  This function will create a BootOption from the give device path and
  description string.

  @param[in]  DevicePath     The device path which the option represent
  @param[in]  Description     The description of the boot option

  @retval BDS_COMMON_OPTION - Pointer to created boot option
**/
BDS_COMMON_OPTION *
BdsCreateBootOption (
  IN  EFI_DEVICE_PATH_PROTOCOL       *DevicePath,
  IN  CHAR16                         *Description
  )
;

#endif
