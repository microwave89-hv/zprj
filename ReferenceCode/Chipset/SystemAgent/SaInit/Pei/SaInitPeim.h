/** @file
  Header file for the SA Init PEIM

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
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
#ifndef _SA_INIT_PEIM_H_
#define _SA_INIT_PEIM_H_

///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "SaAccess.h"
#include "MemInfoHob.h"
#include "CpuRegs.h"
#include "CpuPlatformLib.h"
#include "SaOcInit.h"

#include EFI_PPI_DEPENDENCY  (SaPlatformPolicy)
#include EFI_PPI_DEPENDENCY  (CpuPlatformPolicy)
#include EFI_PPI_PRODUCER    (SaPeiInit)
#include EFI_GUID_DEFINITION (SaDataHob)
#endif
///
/// Data definitions & structures
///

EFI_GUID  gMemoryInitHobGuid = EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI_GUID;

///
/// Functions
///
EFI_STATUS
EFIAPI
SaInitPeiEntryPoint (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
/**
  SA PEI Initialization.

  @param[in] FfsHeader    - Pointer to Firmware File System file header.
  @param[in] PeiServices  - General purpose services available to every PEIM.

  @retval EFI_SUCCESS
**/
;

VOID
ProgramSaBars (
  IN    SA_PLATFORM_POLICY_PPI    *SaPlatformPolicyPpi
  )
/**
  Programs Sa Bars

  @param[in] SaPlatformPolicyPpi  - Instance of SA_PLATFORM_POLICY_PPI
**/
;

VOID
SwitchableGraphicsInit (
  IN EFI_PEI_SERVICES             **PeiServices,
  IN SA_PLATFORM_POLICY_PPI       *SaPlatformPolicyPpi
  )
/**
  SwitchableGraphicsInit: Initialize the Switchable Graphics if enabled

  @param[in] PeiServices          - Pointer to the PEI services table
  @param[in] SaPlatformPolicyPpi  - SaPlatformPolicyPpi to access the SgConfig related information
**/
;

VOID
EarlyBiosPostProgramming (
  IN    SA_PLATFORM_POLICY_PPI   *SaPlatformPolicyPpi
  )
/**
  Do Early BIOS POST Programming

  @param[in] SaPlatformPolicyPpi - Instance of SA_PLATFORM_POLICY_PPI
**/
;

VOID
GraphicsInit (
  IN EFI_PEI_SERVICES             **PeiServices,
  IN SA_PLATFORM_POLICY_PPI       *SaPlatformPolicyPpi
  )
/**
  GraphicsInit: Initialize the IGD if no other external graphics is present

  @param[in] PeiServices          - Pointer to the PEI services table
  @param[in] SaPlatformPolicyPpi  - SaPlatformPolicyPpi to access the GtConfig related information
**/
;

EFI_STATUS
SaDmiTcVcInit (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN SA_PLATFORM_POLICY_PPI    *SaPlatformPolicyPpi
  )
/**
  Initialize DMI Tc/Vc mapping through SA-PCH.

  @param[in] PeiServices          - General purpose services available to every PEIM.
  @param[in] SaPlatformPolicyPpi  - SaPlatformPolicyPpi to access the GtConfig related information

  @retval EFI_SUCCESS
**/
;

#ifdef DMI_FLAG
EFI_STATUS
DmiInit (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN SA_PLATFORM_POLICY_PPI    *SaPlatformPolicyPpi
  )
/**
  Initialize DMI.

  @param[in] PeiServices          - General purpose services available to every PEIM.
  @param[in] SaPlatformPolicyPpi  - SaPlatformPolicyPpi to access the GtConfig related information

  @retval EFI_SUCCESS
**/
;
#endif // DMI_FLAG

#ifdef PEG_FLAG
VOID
PciExpressInit (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN SA_PLATFORM_POLICY_PPI    *SaPlatformPolicyPpi
  )
/**
  GraphicsInit: Initialize the IGD if no other external graphics is present

  @param[in] PeiServices          - Pointer to the PEI services table
  @param[in] SaPlatformPolicyPpi  - SaPlatformPolicyPpi to access the GtConfig related information
**/
;
#endif // PEG_FLAG

EFI_STATUS
InstallSaHob (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN SA_PLATFORM_POLICY_PPI    *SaPlatformPolicyPpi
  )
/**
  Init and Install SA Hob

  @param[in] PeiServices  - General purpose services available to every PEIM.
  @param[in] SaPlatformPolicyPpi  - SaPlatformPolicyPpi to access the GtConfig related information

  @retval EFI_SUCCESS
**/
;

EFI_STATUS
ReportPcieVersion (
  IN    SA_PLATFORM_POLICY_PPI   *SaPlatformPolicyPpi
  )
/**
  Report the SA PCIe initialization code version.

  @param[in] SaPlatformPolicyPpi - Instance of SA_PLATFORM_POLICY_PPI

  @retval EFI_SUCCESS
**/
;

STATIC
EFI_STATUS
SaResetComplete (
  IN      EFI_PEI_SERVICES          **PeiServices,
  IN      EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
  IN      VOID                      *Ppi
  )
/**
  BIOS_CPL_BIT is set for processor to activate the power and thermal management
  features on the platform.

  @param[in] PeiServices   - Pointer to PEI Services Table.
  @param[in] NotifyDesc    - Pointer to the descriptor for the Notification event that
                  caused this function to execute.
  @param[in] Ppi           - Pointer to the PPI data associated with this function.

  @retval EFI_SUCCESS
**/
;

VOID
SaPeiPolicyDump (
  IN    SA_PLATFORM_POLICY_PPI   *SaPlatformPolicyPpi
  )
/**
  This function prints the PEI phase platform policy.

  @param[in] SaPlatformPolicyPpi - Instance of SA_PLATFORM_POLICY_PPI
**/
;

static
EFI_STATUS
SaS3ResumeAtEndOfPei (
  IN      EFI_PEI_SERVICES          **PeiServices,
  IN      EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
  IN      VOID                      *Ppi
  )
/**
  This function handles SA S3 resume task

  @param[in] PeiServices   - Pointer to PEI Services Table.
  @param[in] NotifyDesc    - Pointer to the descriptor for the Notification event that
                             caused this function to execute.
  @param[in] Ppi           - Pointer to the PPI data associated with this function.

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
;

#ifdef RAPID_START_FLAG
static
EFI_STATUS
SaCheckRapidStartMode (
  IN      EFI_PEI_SERVICES          **PeiServices,
  IN      EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
  IN      VOID                      *Ppi
  )
/**
  This function will check Rapid Start mode and install SaS3Resume callback notify if it was Rapid Start Resume

  @param[in] PeiServices   - Pointer to PEI Services Table.
  @param[in] NotifyDesc    - Pointer to the descriptor for the Notification event that
                             caused this function to execute.
  @param[in] Ppi           - Pointer to the PPI data associated with this function.

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
;
#endif // RAPID_START_FLAG

#endif
