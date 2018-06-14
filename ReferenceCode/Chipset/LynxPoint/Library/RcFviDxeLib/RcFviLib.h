/** @file
  Header file for Reference code Firmware Version Info Interface Lib implementation.

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
#ifndef _RC_FVI_LIBRARY_IMPLEMENTATION_H_
#define _RC_FVI_LIBRARY_IMPLEMENTATION_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueBase.h"
#include "EdkIIGlueDxe.h"
#include "Library/EdkIIGlueMemoryAllocationLib.h"

#include EFI_GUID_DEFINITION      (DataHubRecords)
#include EFI_PROTOCOL_CONSUMER    (DataHub)

#include "RcFviDxeLib.h"

#endif

/**
  Publish the Reference code version info as per Firmware Version Info (FVI) Interface Spec v0.7
  using MiscSubClass Data Hub.

  @param[in] Event                Event whose notification function is being invoked.
  @param[in] Context              Pointer to the notification functions context, which is implementation dependent.

  @retval None
**/
VOID
EFIAPI
DataHubCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  );
#endif
