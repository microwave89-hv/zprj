/*++

   Copyright (c)  2005 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Abstract:

   TCG Service PPI

   Only minimum subset of features is contained in this PPI definition

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_PPI/TcgService/TcgService.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_PPI/TcgService/TcgService.h $
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
// 6     3/29/11 2:59p Fredericko
// 
// 5     3/28/11 3:14p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 4     5/19/10 6:49p Fredericko
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
//  Header file for TcgService.c
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _TCG_SERVICE_H_
#define _TCG_SERVICE_H_

#include <TcgEfiTpm.h>
#include <TCGMisc.h>
#include <token.h>

struct _PEI_TCG_PPI;

typedef struct _PEI_TCG_PPI PEI_TCG_PPI;


#define PEI_TCG_PPI_GUID  \
    {0x177d39d2, 0x43b8, 0x40c8, 0x9a, 0xe1, 0x3c, 0x51, 0x98, 0xd6, 0x94, 0x1e}

typedef
EFI_STATUS
(EFIAPI * PEI_TCG_LOG_EVENT)(
    IN PEI_TCG_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN TCG_PCR_EVENT    *Event,
    OUT UINT32          *EventNum
    );

typedef
EFI_STATUS
(EFIAPI * PEI_TCG_HASH_LOG_EXTEND_EVENT)(
    IN PEI_TCG_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN UINT8            *HashData,
    IN UINT32           HashDataLen,
    IN TCG_PCR_EVENT    *NewEvent,
    OUT UINT32          *EventNum
    );

typedef
EFI_STATUS
(EFIAPI * PEI_TCG_PASS_THROUGH_TO_TPM)(
    IN PEI_TCG_PPI      *This,
    IN EFI_PEI_SERVICES **PeiSerivces,
    IN UINT32           TpmInputParameterBlockSize,
    IN UINT8            *TpmInputParameterBlock,
    IN UINT32           TpmOutputParameterBlockSize,
    IN UINT8            *TpmOutputParameterBlock
    );

typedef struct _PEI_TCG_PPI
{
    PEI_TCG_HASH_LOG_EXTEND_EVENT TCGHashLogExtendEvent;
    PEI_TCG_LOG_EVENT             TCGLogEvent;
    PEI_TCG_PASS_THROUGH_TO_TPM   TCGPassThroughToTpm;
} PEI_TCG_PPI;

extern EFI_GUID gPeiTcgPpiGuid;

#endif
