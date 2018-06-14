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
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_PPI/TcgService/TcgTcmService.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_PPI/TcgService/TcgTcmService.h $
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
// 3     9/29/11 6:08p Davidd
// [TAG]           EIP71378
// [Category]      Improvement
// [Description]   Customer names in source files
// [Files]         TcgTcmService.h
// 
// 2     3/29/11 3:00p Fredericko
// 
// 1     3/28/11 3:15p Fredericko
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
/*

   Copyright (c)  2005 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Abstract:

   TCM Service PPI

   Only minimum subset of features is contained in this PPI definition

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_PPI/TcgService/TcgTcmService.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_PPI/TcgService/TcgTcmService.h $
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
// 3     9/29/11 6:08p Davidd
// [TAG]           EIP71378
// [Category]      Improvement
// [Description]   Customer names in source files
// [Files]         TcgTcmService.h
// 
// 2     3/29/11 3:00p Fredericko
// 
// 1     3/28/11 3:15p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG file override
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
// Name:  TCMService.h
//
// Description: 
//  Header file for TCMService.c
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _TCG_TCM_SERVICE_H_
#define _TCG_TCM_SERVICE_H_

#include <TcgEfiTpm.h>
#include <TcgMisc.h>
#include <token.h>

struct _PEI_TCM_PPI;
typedef struct _PEI_TCM_PPI PEI_TCM_PPI;

typedef
EFI_STATUS
(EFIAPI * PEI_TCM_LOG_EVENT)(
    IN PEI_TCM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN TCM_PCR_EVENT    *Event,
    OUT UINT32          *EventNum );

typedef
EFI_STATUS
(EFIAPI * PEI_TCM_HASH_LOG_EXTEND_EVENT)(
    IN PEI_TCM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN UINT8            *HashData,
    IN UINT32           HashDataLen,
    IN TCM_PCR_EVENT    *NewEvent,
    OUT UINT32          *EventNum
    );

typedef
EFI_STATUS
(EFIAPI * PEI_TCM_PASS_THROUGH_TO_TCM)(
    IN PEI_TCM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiSerivces,
    IN UINT32           TcmInputParameterBlockSize,
    IN UINT8            *TcmInputParameterBlock,
    IN UINT32           TcmOutputParameterBlockSize,
    IN UINT8            *TcmOutputParameterBlock
    );

typedef struct _PEI_TCM_PPI
{
    PEI_TCM_HASH_LOG_EXTEND_EVENT TCMHashLogExtendEvent;
    PEI_TCM_LOG_EVENT             TCMLogEvent;
    PEI_TCM_PASS_THROUGH_TO_TCM   TCMPassThroughToTcm;
} PEI_TCM_PPI;

extern EFI_GUID gPeiTCMPpiGuid;

#endif