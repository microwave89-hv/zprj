/** @file
  This file defines the Pch Info Protocol.

@copyright
  Copyright (c) 2008 - 2012 Intel Corporation. All rights reserved
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

#include "PchInfo.h"

//
// Protocol GUID definition
//
EFI_GUID  gEfiPchInfoProtocolGuid = EFI_PCH_INFO_PROTOCOL_GUID;

//
// Protocol description
//
EFI_GUID_STRING(&gEfiPchInfoProtocolGuid, "PCH Info Protocol", "PCH Information Protocol");
