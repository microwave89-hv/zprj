/** @file
  Definitions for ACPI RC FVI DXE driver

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
#ifndef _ACPI_RC_FVI_H_
#define _ACPI_RC_FVI_H_
#include "EdkIIGlueDxe.h"
#include "RcFviDxeLib.h"
#include EFI_PROTOCOL_PRODUCER  (AcpiInfo)

#define ACPI_FVI_STRING          "Reference Code - ACPI"
#define ACPI_FVI_SMBIOS_TYPE     0xDD  ///< Default value
#define ACPI_FVI_SMBIOS_INSTANCE 0x01
#endif
