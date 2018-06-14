/** @file
  The header file for Ftpm SMM driver.

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
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

#ifndef __FTPM_SMM_H__
#define __FTPM_SMM_H__

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"

#include EFI_PROTOCOL_DEPENDENCY (SmmBase)
#include EFI_PROTOCOL_DEPENDENCY (SmmSwDispatch)
#include EFI_PROTOCOL_DEPENDENCY (AcpiTable)
#include EFI_PROTOCOL_DEPENDENCY (FirmwareVolume)
#include EFI_PROTOCOL_DEPENDENCY (MeGlobalNvsArea)
#include EFI_GUID_DEFINITION     (MeSsdtTableStorage)

#include "Acpi.h"

//
// Below definition is generic, but NOT in GreenH
//
#include EFI_PROTOCOL_DEPENDENCY (SmmVariable)

#include "IndustryStandard\AcpiAml.h"
#ifndef EFI_ACPI_5_0_TRUSTED_COMPUTING_PLATFORM_2_TABLE_SIGNATURE
#define EFI_ACPI_5_0_TRUSTED_COMPUTING_PLATFORM_2_TABLE_SIGNATURE  EFI_SIGNATURE_32('T', 'P', 'M', '2')
#endif

#include "IndustryStandard\Tpm2Acpi.h"
#include EFI_GUID_DEFINITION (TrEEPhysicalPresenceData)
#include EFI_GUID_DEFINITION (MemoryOverwriteControl)

//
// Below definition is chipset specific
//
#include EFI_GUID_DEFINITION (MeDataHob)
#include "CpuRegs.h"
#include "CpuPlatformLib.h"
#include "PttHciRegs.h"
#endif

//
// Below definition is driver specific
//
#include "Tpm2AcpiTableStorage.h"

#pragma pack(1)
typedef struct {
  UINT8                  SoftwareSmi;
  UINT32                 Parameter;
  UINT32                 Response;
  UINT32                 Request;
  UINT32                 LastRequest;
  UINT32                 ReturnCode;
} PHYSICAL_PRESENCE_NVS;

typedef struct {
  UINT8                  SoftwareSmi;
  UINT32                 Parameter;
  UINT32                 Request;
  UINT32                 ReturnCode;
} MEMORY_CLEAR_NVS;

typedef struct {
  UINT8                  SoftwareSmi;
  UINT32                 ReturnCode;
} START_METHOD_NVS;

typedef struct {
  PHYSICAL_PRESENCE_NVS  PhysicalPresence;
  MEMORY_CLEAR_NVS       MemoryClear;
  START_METHOD_NVS       StartMethod;
} TCG_NVS;

typedef struct {
  UINT8                  OpRegionOp;
  UINT32                 NameString;
  UINT8                  RegionSpace;
  UINT8                  DWordPrefix;
  UINT32                 RegionOffset;
  UINT8                  BytePrefix;
  UINT8                  RegionLen;
} AML_OP_REGION_32_8;
#pragma pack()

//
// The definition for TCG physical presence ACPI function
//
#define ACPI_FUNCTION_GET_PHYSICAL_PRESENCE_INTERFACE_VERSION      1
#define ACPI_FUNCTION_SUBMIT_REQUEST_TO_BIOS                       2
#define ACPI_FUNCTION_GET_PENDING_REQUEST_BY_OS                    3
#define ACPI_FUNCTION_GET_PLATFORM_ACTION_TO_TRANSITION_TO_BIOS    4
#define ACPI_FUNCTION_RETURN_REQUEST_RESPONSE_TO_OS                5
#define ACPI_FUNCTION_SUBMIT_PREFERRED_USER_LANGUAGE               6
#define ACPI_FUNCTION_SUBMIT_REQUEST_TO_BIOS_2                     7
#define ACPI_FUNCTION_GET_USER_CONFIRMATION_STATUS_FOR_REQUEST     8

//
// The return code for Get User Confirmation Status for Operation
//
#define PP_REQUEST_NOT_IMPLEMENTED                                 0
#define PP_REQUEST_BIOS_ONLY                                       1
#define PP_REQUEST_BLOCKED                                         2
#define PP_REQUEST_ALLOWED_AND_PPUSER_REQUIRED                     3
#define PP_REQUEST_ALLOWED_AND_PPUSER_NOT_REQUIRED                 4

//
// The return code for Sumbit TPM Request to Pre-OS Environment
// and Sumbit TPM Request to Pre-OS Environment 2
//
#define PP_SUBMIT_REQUEST_SUCCESS                                  0
#define PP_SUBMIT_REQUEST_NOT_IMPLEMENTED                          1
#define PP_SUBMIT_REQUEST_GENERAL_FAILURE                          2
#define PP_SUBMIT_REQUEST_BLOCKED_BY_BIOS_SETTINGS                 3

//
// The definition for TCG MOR
//
#define ACPI_FUNCTION_DSM_MEMORY_CLEAR_INTERFACE                   1
#define ACPI_FUNCTION_PTS_CLEAR_MOR_BIT                            2

//
// The return code for Memory Clear Interface Functions
//
#define MOR_REQUEST_SUCCESS                                        0
#define MOR_REQUEST_GENERAL_FAILURE                                1

//
// Below definition should be in platorm scope
//
// TBD: Use policy to input these data...
#ifndef EFI_TPM2_PP_SW_SMI
#define EFI_TPM2_PP_SW_SMI     0x9E
#endif
#ifndef EFI_TPM2_MOR_SW_SMI
#define EFI_TPM2_MOR_SW_SMI    0x9F
#endif

#endif  // __FTPM_SMM_H__
