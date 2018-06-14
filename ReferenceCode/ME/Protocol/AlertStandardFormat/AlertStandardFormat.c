/** @file
  Definition of Alert Standard Format (ASF) 2.0

@copyright
  Copyright (c) 2005 - 2012 Intel Corporation. All rights reserved
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
#include EFI_PROTOCOL_DEFINITION (AlertStandardFormat)
#endif

EFI_GUID  gEfiAlertStandardFormatProtocolGuid = EFI_ALERT_STANDARD_FORMAT_PROTOCOL_GUID;

EFI_GUID_STRING
  (&gEfiAlertStandardFormatProtocolGuid, "Alert Standard Format Protocol", "Alert Standard Format Protocol");
