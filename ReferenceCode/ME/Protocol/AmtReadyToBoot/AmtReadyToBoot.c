/** @file
  AmtReadyToBoot Protocol definitions

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
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
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include EFI_PROTOCOL_DEFINITION (AmtReadyToBoot)
#endif

EFI_GUID  gAmtReadyToBootProtocolGuid = AMT_READY_TO_BOOT_PROTOCOL_GUID;

EFI_GUID_STRING(&gAmtReadyToBootProtocolGuid, "AMT ReadyToBoot Protocol", "AMT ReadyToBoot Protocol")
