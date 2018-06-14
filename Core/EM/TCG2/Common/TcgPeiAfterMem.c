/*++

   Copyright (c) 2005 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Module Name:

   TcgPei.c

   Abstract:

   PEIM that provides TCG services

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgPeiAfterMem/TcgPeiAfterMem.c 1     4/21/14 2:16p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:16p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgPeiAfterMem/TcgPeiAfterMem.c $
// 
// 1     4/21/14 2:16p Fredericko
// 
// 1     10/08/13 12:02p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 1:57p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 3     1/12/12 12:11p Fredericko
// Remove unused function.
// 
// 2     8/29/11 6:49p Fredericko
// [TAG]  		EIP0000
// [Category]  	Improvement
// [Description]  	Include Open and Close of locality 0 for TPM Ppi
// functions
// [Files]  		TcgPeiAfterMem.c
// 
// 1     8/22/11 1:45p Fredericko
// [TAG]  		EIP61168
// [Category]  	Improvement
// [Description]  	Reload TCG PPI from memory when Memory is Installed
// [Files]  		TcgPeiAfterMem.cif
// TcgPeiAfterMem.c
// xTcgPeiAfterMem.c
// TcgPeiAfterMem.mak
// 
// 54    3/31/11 4:49p Fredericko
// Changes for TCG_LEGACY support
// 
// 53    3/29/11 12:57p Fredericko
// 
// 52    3/28/11 2:12p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 50    8/04/10 5:16p Fredericko
// Changes to flow of Lock Physical Presence for support Smi PPI changes
// 
// 49    5/21/10 4:31p Fredericko
// Changes for some build errors that happened with MOR support
// 
// 48    5/19/10 5:51p Fredericko
// Updated AMI Function Headers
// Code Beautification
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgPei.c
//
// Description: 
//  Functions for early initialization of TPM are executed here
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include "TcgCommon.h"
#include <AmiPeiLib.h>
#include <Sha.h>
#include <TcgMisc.h>
#include <token.h>
#include <TpmLib.h>
#include <TcgPc.h>
#include "PPI\TcgService\TcgService.h"
#include "PPI\TpmDevice\TpmDevice.h"
#include "PPI\CpuIo.h"
#include "PPI\LoadFile.h"
#include <FFS.h>


//*********************************************************************
//                      GLOBAL DEFINITIONS
//*********************************************************************


#pragma pack(1)
typedef struct _TCG_PEI_CALLBACK_CONTEXT
{
    PEI_TPM_PPI      *TpmDevice;
    EFI_PEI_SERVICES **PeiServices;
} TCG_PEI_CALLBACK_CONTEXT;
#pragma pack()


EFI_GUID gEfiPeiAmiTcgLogHobGuid        = EFI_TCG_LOG_HOB_GUID;
EFI_GUID gPeiTpmPpiGuid                 = PEI_TPM_PPI_GUID;
EFI_GUID gPeiTcgPpiGuid                 = PEI_TCG_PPI_GUID;

static
EFI_STATUS
__stdcall FillCallbackContext(
    IN EFI_PEI_SERVICES          **PeiService,
    OUT TCG_PEI_CALLBACK_CONTEXT *CallbackContext )
{
    CallbackContext->PeiServices = PeiService;
    return (*PeiService)->LocatePpi(
               PeiService,
               &gPeiTpmPpiGuid,
               0,
               NULL,
               &CallbackContext->TpmDevice
               );
}

EFI_STATUS
EFIAPI TcgPeiGetEventLog(
    IN EFI_PEI_SERVICES **PeiServices,
    OUT TCG_LOG_HOB     **EventLog )
{
    EFI_STATUS Status;
    VOID       *HobStart;

    Status = (*PeiServices)->GetHobList( PeiServices, &HobStart );

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    return GetNextGuidHob( &HobStart, &gEfiPeiAmiTcgLogHobGuid, EventLog, NULL );
}




//**********************************************************************
//<AMI_PHDR_START>
// Name:  TcgPeiLogEvent
//
// Description: TCGPEI common function to Hash, Log and Extend data
//              using software SHA-1
//
// Input:       IN   *This
//              IN   **PeiServices
//              IN   *Event,
//              IN   *EventNum
//
// Output:     EFI STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//*********************************************************************
EFI_STATUS
EFIAPI TcgPeiLogEvent(
    IN PEI_TCG_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN TCG_PCR_EVENT    *Event,
    OUT UINT32          *EventNum )
{
    EFI_STATUS                     Status = EFI_SUCCESS;
    TCG_LOG_HOB                    *TcgLog;
    TCG_PEI_CALLBACK_CONTEXT       Context;
    UINT8                          HashAlgo = 0;
    

    //only log events if TPM is not deactivated
#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(Event->EventType == EV_EFI_ACTION)
    {
        return EFI_SUCCESS;
    }
#endif

    Status = FillCallbackContext( PeiServices, &Context );
    ASSERT_PEI_ERROR( PeiServices, Status );

    Status = TcgPeiGetEventLog( PeiServices, &TcgLog );
    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    Status = TcgCommonLogEvent(
            &Context,
            (TCG_PCR_EVENT*)(TcgLog + 1),
            &TcgLog->TableSize,
            TcgLog->TableMaxSize,
            Event, HashAlgo);

    if ( EFI_ERROR( Status )){
            goto Exit;
    }

    *EventNum = TcgLog->EventNum;
    TcgLog->EventNum++;

Exit:
    return Status;
}





EFI_STATUS
__stdcall TcgPeiCommonExtend(
    IN VOID         *CallbackContext,
    IN TPM_PCRINDEX PCRIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue )
{
    TPM_1_2_CMD_HEADER  cmdHeader;
    TPM_1_2_RET_HEADER  retHeader;
    TPM_TRANSMIT_BUFFER InBuffer[3], OutBuffer[2];
    static BOOLEAN      SupportType = 0xff;

    InBuffer[0].Buffer = &cmdHeader;
    InBuffer[0].Size   = sizeof (cmdHeader);
    InBuffer[1].Buffer = &PCRIndex;
    InBuffer[1].Size   = sizeof (PCRIndex);
    InBuffer[2].Buffer = Digest->digest;
    InBuffer[2].Size   = sizeof (Digest->digest);

    OutBuffer[0].Buffer = &retHeader;
    OutBuffer[0].Size   = sizeof (retHeader);
    OutBuffer[1].Buffer = NewPCRValue->digest;
    OutBuffer[1].Size   = sizeof (NewPCRValue->digest);

    cmdHeader.Tag       = TPM_H2NS( TPM_TAG_RQU_COMMAND );
    cmdHeader.ParamSize = TPM_H2NL(sizeof (cmdHeader) 
                          + sizeof (PCRIndex) + sizeof (Digest->digest));

    cmdHeader.Ordinal = TPM_H2NL( TPM_ORD_Extend );
    PCRIndex          = TcgCommonH2NL( PCRIndex );

    return TCGPASSTHROUGH( CallbackContext, InBuffer, OutBuffer );
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Name:  TcgPeiHashLogExtendEventSW
// Description: TCGPEI Software function to Hash, Log and Extend data
//              using software SHA-1
//
// Input:     IN        *This
//            IN        **PeiServices
//            IN        *HashData
//            IN        HashDataLen
//            IN OUT    *NewEvent,
//            OUT       *EventNum
//
// Output:    EFI STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//*********************************************************************
EFI_STATUS TcgPeiHashLogExtendEventSW(
    IN PEI_TCG_PPI       *This,
    IN EFI_PEI_SERVICES  **PeiServices,
    IN UINT8             *HashData,
    IN UINT32            HashDataLen,
    IN OUT TCG_PCR_EVENT *NewEvent,
    OUT UINT32           *EventNum )
{
    EFI_STATUS               Status;
    TCG_DIGEST               NewPCRValue;
    TCG_PEI_CALLBACK_CONTEXT Context;

    Status = FillCallbackContext( PeiServices, &Context );
    ASSERT_PEI_ERROR( PeiServices, Status );

#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(NewEvent->EventType == EV_EFI_ACTION)
    {
        return EFI_SUCCESS;
    }
#endif

    Status = SHA1HashAll( &Context, HashData, HashDataLen, &NewEvent->Digest );

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    Status = Context.TpmDevice->Init( Context.TpmDevice, PeiServices );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    Status = TcgPeiCommonExtend(
        &Context,
        NewEvent->PCRIndex,
        &NewEvent->Digest,
        &NewPCRValue
        );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    Status = TcgPeiLogEvent( This, PeiServices, NewEvent, EventNum );

Exit:
    Context.TpmDevice->Close( Context.TpmDevice, PeiServices );
    return Status;
}







//**********************************************************************
//<AMI_PHDR_START>
//
// Name:  TcgPeiPassThroughToTpm
//
// Description: TCGPEI common function to abstract passing commands to the TPM
//                FIFO
//
// Input:       IN   *This
//              IN   **PeiServices
//              IN   TpmInputParameterBlockSize
//              IN   *TpmInputParameterBlock
//              IN   TpmOutputParameterBlockSize
//              IN   *TpmOutputParameterBlock
//
// Output:      EFI STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TcgPeiPassThroughToTpm(
    IN PEI_TCG_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN UINT32           TpmInputParameterBlockSize,
    IN UINT8            *TpmInputParameterBlock,
    IN UINT32           TpmOutputParameterBlockSize,
    IN UINT8            *TpmOutputParameterBlock )
{
    EFI_STATUS               Status;
    TPM_TRANSMIT_BUFFER      InBuffer[1], OutBuffer[1];
    TCG_PEI_CALLBACK_CONTEXT Context;

    Status = FillCallbackContext( PeiServices, &Context );
    ASSERT_PEI_ERROR( PeiServices, Status );

    InBuffer[0].Buffer  = TpmInputParameterBlock;
    InBuffer[0].Size    = TpmInputParameterBlockSize;
    OutBuffer[0].Buffer = TpmOutputParameterBlock;
    OutBuffer[0].Size   = TpmOutputParameterBlockSize;

    return TcgCommonPassThrough(
               &Context,
               sizeof (InBuffer) / sizeof (*InBuffer),
               InBuffer,
               sizeof (OutBuffer) / sizeof (*OutBuffer),
               OutBuffer
               );
}


static PEI_TCG_PPI            mTcgPpi = {
    TcgPeiHashLogExtendEventSW,
    TcgPeiLogEvent,
    TcgPeiPassThroughToTpm
};

static EFI_PEI_PPI_DESCRIPTOR mTcgPpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiTcgPpiGuid,
        &mTcgPpi
    }
};




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgPeiEntry
//
// Description: Entry point to Memory Absent and Memory Present Initialization
//              for TPM
//
//
// Input:       IN      EFI_FFS_FILE_HEADER       *FfsHeader
//              IN      EFI_PEI_SERVICES          **PeiServices,
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TcgPeiMemoryCallbackEntry(
    IN EFI_PEI_SERVICES    **PeiServices 
)
{
    EFI_PEI_PPI_DESCRIPTOR         *PpiDesc;
    PEI_TCG_PPI                    *TcgPpi;
    EFI_STATUS                     Status;

    Status = (*PeiServices)->LocatePpi(
                            PeiServices,
                            &gPeiTcgPpiGuid,
                            0,
                            &PpiDesc,
                            &TcgPpi);

    
   Status = (*PeiServices)->ReInstallPpi(
                            PeiServices,
                            PpiDesc,
                            &mTcgPpiList[0] );
   
    ASSERT_PEI_ERROR( PeiServices, Status );

    Status = (*PeiServices)->LocatePpi(
                            PeiServices,
                            &gPeiTcgPpiGuid,
                            0,
                            &PpiDesc,
                            &TcgPpi );

    ASSERT_PEI_ERROR( PeiServices, Status );

    return Status;
}


