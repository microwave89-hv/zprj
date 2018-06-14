/** @file
  This code makes the BIOS Data structure available via standard ACPI mechanisms.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved.
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

#ifndef _BDAT_ACCESS_HANDLER_H_
#define _BDAT_ACCESS_HANDLER_H_
///
/// External include files do NOT need to be explicitly specified in real EDKII environment.
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "Acpi3_0.h"
#include "Acpi.h"
#include "BdatRmtHandler.h"
#include EFI_GUID_DEFINITION (Hob)

///
/// Consumed protocols
///
#include EFI_PROTOCOL_CONSUMER (AcpiTable)
#include EFI_PROTOCOL_PRODUCER (BdatAccess)
#include EFI_PROTOCOL_DEFINITION (SaPlatformPolicy)
#endif
///
/// Ensure proper structure formats
///
#pragma pack(push, 1)
///
/// BIOS Data ACPI structure
///
typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER             Header;
  EFI_ACPI_3_0_GENERIC_ADDRESS_STRUCTURE  BdatGas;
} EFI_BDAT_ACPI_DESCRIPTION_TABLE;


/**
  Entry point of the Bdat RMT Access Handler.

  @param[in] DxePlatformSaPolicy   : A pointer to Dxe platform policy
  @param[in] HobList               : A pointer to the HOB list
  @param[in] AcpiTable             : A pointer to ACPI table

  @retval EFI_SUCCESS:              Driver initialized successfully
  @exception EFI_UNSUPPORTED:       A needed driver was not located
  @retval EFI_OUT_OF_RESOURCES:     Could not allocate needed resources
**/
EFI_STATUS
BdatRmtHandler (
  IN DXE_PLATFORM_SA_POLICY_PROTOCOL *DxePlatformSaPolicy,
  IN VOID                            *HobList,
  IN EFI_ACPI_TABLE_PROTOCOL         *AcpiTable
  )
;
///
/// This is copied from Include\Acpi.h
///
#define CREATOR_ID_INTEL  0x4C544E49  /// "LTNI""INTL"(Intel)
#define CREATOR_REV_INTEL 0x20090903

#pragma pack(pop)

#endif /// _BDAT_ACCESS_HANDLER_H_
