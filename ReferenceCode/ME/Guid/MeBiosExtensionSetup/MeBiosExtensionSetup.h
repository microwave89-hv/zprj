/** @file
  Me Bios Extension 16 Setup Options Guid definitions

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
#ifndef _EFI_ME_BIOS_EXTENSION_SETUP_GUID_H_
#define _EFI_ME_BIOS_EXTENSION_SETUP_GUID_H_

///
/// A NV-RAM variable for storing Intel MEBX setup option settings is created if this variable is not
/// present.  Those settings are used by BIOS during POST to bypass portions of the code if the
/// Intel ME features are not available
///
#define EFI_ME_BIOS_EXTENSION_SETUP_GUID \
  { \
    0x1bad711c, 0xd451, 0x4241, 0xb1, 0xf3, 0x85, 0x37, 0x81, 0x2e, 0xc, 0x70 \
  }

#define EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME         (L"MeBiosExtensionSetup")
#define EFI_ME_BIOS_EXTENSION_SETUP_FORMAT_VARIABLE_NAME  ("MeBiosExtensionSetup")

extern CHAR16   gEfiMeBiosExtensionSetupName[];

extern EFI_GUID gEfiMeBiosExtensionSetupGuid;

#pragma pack(1)

///
/// A NV-RAM variable for storing Intel MEBX setup option settings is created if this variable is not
/// present.  Those settings are used by BIOS during POST to bypass portions of the code if the
/// Intel ME features are not available. The information is obtained from Intel MEBx BIOS sync data
/// structure
///
typedef struct {
  ///
  /// Sync Data Structure Version, a non-zero version indicates the variable is being initialized or valid
  ///
  UINT16  InterfaceVersion;
  UINT16  Reserved;
  ///
  /// Bit 0 - UPDATED - this structure has been updated by MEBX
  ///
  UINT32  Flags;
  ///
  /// Platform Manageability Selection
  ///   00h - Off
  ///   01h - On
  ///
  UINT8   PlatformMngSel;
  UINT8   Reserved4;
  UINT8   AmtSolIder;
  UINT8   Reserved1[2];
  ///
  /// CIRA Feature
  ///   00h - DISABLED
  ///   01h - ENABLED
  ///
  UINT8   RemoteAssistanceTriggerAvailablilty;
  ///
  /// KVM state (0 - DISABLED, 1 - ENABLED)
  ///
  UINT8   KvmEnable;
  ///
  /// 0 - On every later boot after BIOS 1st boot
  /// 1 - Mebx will not require a reboot for synchronizing SOL/IDER state, used when BIOS 1st boot only.
  ///
  UINT8   MebxDefaultSolIder;
  UINT8   Reserved2[10];
} ME_BIOS_EXTENSION_SETUP;

#define MNT_OFF     0x00
#define MNT_ON      0x01
#define LAN_ENABLE  0x01
#define SOL_ENABLE  0x01
#define IDER_ENABLE 0x02
#define KVM_ENABLE  0x01

#pragma pack()

#endif
