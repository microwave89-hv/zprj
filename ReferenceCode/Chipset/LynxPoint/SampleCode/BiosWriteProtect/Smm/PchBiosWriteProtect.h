/** @file
  Header file for the Pch Bios Write Protect Driver.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
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
#ifndef _PCH_BIOS_WRITE_PROTECT_H_
#define _PCH_BIOS_WRITE_PROTECT_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"

//
// Driver Dependency Protocols
//
#include EFI_PROTOCOL_CONSUMER (PchPlatformPolicy)
#include EFI_PROTOCOL_CONSUMER (SmmBase)
#include EFI_PROTOCOL_CONSUMER (SmmIchnDispatch)
#include EFI_PROTOCOL_CONSUMER (SmmIoTrapDispatch)
#endif

#endif
