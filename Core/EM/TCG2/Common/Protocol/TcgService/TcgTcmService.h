/*++

   Copyright (c) 2006, Intel Corporation
   All rights reserved. This program and the accompanying materials
   are licensed and made available under the terms and conditions of the BSD License
   which accompanies this distribution.  The full text of the license may be found at
   http://opensource.org/licenses/bsd-license.php

   THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
   WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

   Abstract:

   TCG Service Protocol as defined in TCG_EFI_Protocol_1_20_Final

   See http://trustedcomputinggroup.org for the latest specification

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_Protocol/TcgService/TcgTcmService.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_Protocol/TcgService/TcgTcmService.h $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 12:00p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:58p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 2     3/29/11 3:02p Fredericko
// 
// 1     3/28/11 3:20p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 4     5/20/10 8:44a Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgService.h
//
// Description: 
//  Header file for TcgService.c [Protocol] 
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _TCG_TCM_SERVICE_PROTOCOL_H_
#define _TCG_TCM_SERVICE_PROTOCOL_H_

#include "TcgEfiTpm.h"

#define EFI_TCG_PROTOCOL_GUID  \
    {0xf541796d, 0xa62e, 0x4954, 0xa7, 0x75, 0x95, 0x84, 0xf6, 0x1b, 0x9c, 0xdd}

#define TSS_EVENT_DATA_MAX_SIZE   256

EFI_FORWARD_DECLARATION( EFI_TCM_PROTOCOL );
// Set structure alignment to 1-byte
//
#pragma pack (push, 1)

typedef struct
{
    UINT8 Major;
    UINT8 Minor;
    UINT8 RevMajor;
    UINT8 RevMinor;
} TCM_VERSION;

typedef struct _TCM_EFI_BOOT_SERVICE_CAPABILITY
{
    UINT8       Size;               // Size of this structure
    TCM_VERSION StructureVersion;
    TCM_VERSION ProtocolSpecVersion;
    UINT8       HashAlgorithmBitmap; // Hash algorithms
                                     // this protocol is capable of : 01=SHA-1
    BOOLEAN TPMPresentFlag;     // 00h = TPM not present
    BOOLEAN TPMDeactivatedFlag; // 01h = TPM currently deactivated
} TCM_EFI_BOOT_SERVICE_CAPABILITY;

typedef UINT32 TCG_ALGORITHM_ID;

#pragma pack (pop)

typedef
EFI_STATUS
(EFIAPI * EFI_TCM_STATUS_CHECK)(
    IN EFI_TCM_PROTOCOL      *This,
    OUT TCM_EFI_BOOT_SERVICE_CAPABILITY
                             *ProtocolCapability,
    OUT UINT32               *TCGFeatureFlags,
    OUT EFI_PHYSICAL_ADDRESS *EventLogLocation,
    OUT EFI_PHYSICAL_ADDRESS *EventLogLastEntry
    );

typedef
EFI_STATUS
(EFIAPI * EFI_TCM_HASH_ALL)(
    IN EFI_TCM_PROTOCOL *This,
    IN UINT8            *HashData,
    IN UINT64           HashDataLen,
    IN TCG_ALGORITHM_ID AlgorithmId,
    IN OUT UINT64       *HashedDataLen,
    IN OUT UINT8        **HashedDataResult
    );

typedef
EFI_STATUS
(EFIAPI * EFI_TCM_LOG_EVENT)(
    IN EFI_TCM_PROTOCOL *This,
    IN TCM_PCR_EVENT    *TCGLogData,
    IN OUT UINT32       *EventNumber,
    IN UINT32           Flags
    );

typedef
EFI_STATUS
(EFIAPI * EFI_TCM_PASS_THROUGH_TO_TPM)(
    IN EFI_TCM_PROTOCOL *This,
    IN UINT32           TpmInputParamterBlockSize,
    IN UINT8            *TpmInputParamterBlock,
    IN UINT32           TpmOutputParameterBlockSize,
    IN UINT8            *TpmOutputParameterBlock
    );

typedef
EFI_STATUS
(EFIAPI * EFI_TCM_HASH_LOG_EXTEND_EVENT)(
    IN EFI_TCM_PROTOCOL      *This,
    IN EFI_PHYSICAL_ADDRESS  HashData,
    IN UINT64                HashDataLen,
    IN TCG_ALGORITHM_ID      AlgorithmId,
    IN OUT TCM_PCR_EVENT     *TCGLogData,
    IN OUT UINT32            *EventNumber,
    OUT EFI_PHYSICAL_ADDRESS *EventLogLastEntry
    );

typedef struct _EFI_TCM_PROTOCOL
{
    EFI_TCM_STATUS_CHECK          StatusCheck;
    EFI_TCM_HASH_ALL              HashAll;
    EFI_TCM_LOG_EVENT             LogEvent;
    EFI_TCM_PASS_THROUGH_TO_TPM   PassThroughToTpm;
    EFI_TCM_HASH_LOG_EXTEND_EVENT HashLogExtendEvent;
} EFI_TCM_PROTOCOL;

extern EFI_GUID gEfiTcgProtocolGuid;

#endif
