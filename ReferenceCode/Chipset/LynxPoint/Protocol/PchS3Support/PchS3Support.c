/** @file
  This file defines the PCH S3 Support Protocol.

@copyright
  Copyright (c) 2008 - 2015 Intel Corporation. All rights reserved
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

#include "PchS3Support.h"

//
// Protocol GUID definition
//
EFI_GUID  gEfiPchS3SupportProtocolGuid = EFI_PCH_S3_SUPPORT_PROTOCOL_GUID;
EFI_GUID  gEfiPchS3SupportSmmProtocolGuid = EFI_PCH_S3_SUPPORT_SMM_PROTOCOL_GUID;

//
// Protocol description
//
EFI_GUID_STRING(&gEfiPchS3SupportProtocolGuid, "PCH S3 Support Protocol", "PCH S3 Support Protocol");
EFI_GUID_STRING(&gEfiPchS3SupportSmmProtocolGuid, "PCH S3 SMM Support Protocol", "PCH S3 SMM Support Protocol");
