/** @file
  Definition of the MEFW global NVS area protocol.  This protocol
  publishes the address and format of a global ACPI NVS buffer used as a communications
  buffer between SMM/DXE/PEI code and ASL code.
  @todo The format is derived from the ACPI reference code, version 0.95.

  Note:  Data structures defined in this protocol are not naturally aligned.

@copyright
  Copyright (c) 2012 - 2013 Intel Corporation. All rights reserved
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
#ifndef _ME_GLOBAL_NVS_AREA_H_
#define _ME_GLOBAL_NVS_AREA_H_

///
/// Includes
///
///
/// Forward reference for pure ANSI compatability
///
EFI_FORWARD_DECLARATION (ME_GLOBAL_NVS_AREA_PROTOCOL);

///
/// ME Global NVS Area Protocol GUID
///
#define ME_GLOBAL_NVS_AREA_PROTOCOL_GUID \
  { \
    0x3bffecfd, 0xd75f, 0x4975, 0xb8, 0x88, 0x39, 0x02, 0xbd, 0x69, 0x00, 0x2b \
  }

///
/// Extern the GUID for protocol users.
///
extern EFI_GUID gMeGlobalNvsAreaProtocolGuid;

///
/// Global NVS Area definition
///
#pragma pack(1)
typedef struct {
  UINT32      MeNvsRevision;                                ///< 000 Me NVS Protocol Revision
  ///
  /// PTT Solution
  ///
  UINT8       FTpmSwitch;                                  /// (004) fTPM Solution Method Selection
  ///
  /// PTT Allocated Buffer Address
  ///
  UINT64      PTTAddress;                                  /// (005) PTT Allocated Buffer Address

} ME_GLOBAL_NVS_AREA;
#pragma pack()
///
/// ME Global NVS Area Protocol
///
typedef struct _ME_GLOBAL_NVS_AREA_PROTOCOL {
  ME_GLOBAL_NVS_AREA *Area;
} ME_GLOBAL_NVS_AREA_PROTOCOL;

#endif
