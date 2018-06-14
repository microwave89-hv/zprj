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
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgTisPei.c 1     4/21/14 2:16p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:16p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgTisPei.c $
// 
// 1     4/21/14 2:16p Fredericko
// 
// 3     3/17/14 3:05p Fredericko
// 
// 2     3/11/14 6:32p Fredericko
// [TAG]  		EIP151925
// [Category]  	New Feature
// [Description]  	Changes for TcgGeneric Regression Testing
// 
// 1     10/08/13 12:02p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 1:52p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 57    1/12/12 12:10p Fredericko
// Remove unused functions.
// 
// 56    8/26/11 1:01p Fredericko
// 
// 55    8/09/11 6:15p Fredericko
// [TAG]  		EIP66465
// [Category]  	New Feature
// [Description]  	1. Added support to remove EFI_EV_ACTION from the TCG
// logs if customer wants. 
// [Files]  		1. Tcgdxe.c
// 2. Tcgpei.c
// 3. Tcg.sdl
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
#include <ppi\AmiTcgPlatformPpi.h>
#include "TcgPlatformSetupPeiPolicy.h"


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

static BOOLEAN           SupportType = 0xff;


EFI_STATUS
__stdcall Tcg20CommonExtend(
    IN VOID         *CallbackContext,
    IN TPM_PCRINDEX PcrIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue,
    IN  UINT8        DigestSize);

UINTN FindNextLogLocation(TCG_PCR_EVENT_HDR   *TcgLog, UINTN EventNum);



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


UINT8  GetHashPolicy(IN EFI_PEI_SERVICES    **PeiServices)
{
    TCG_PLATFORM_SETUP_INTERFACE   *TcgPeiPolicy = NULL;
    EFI_STATUS Status;
    EFI_GUID  gTcgPeiPolicyGuid = TCG_PLATFORM_SETUP_PEI_POLICY_GUID;
    TCG_CONFIGURATION  Configuration;

    Status = (*PeiServices)->LocatePpi(
                PeiServices,
                &gTcgPeiPolicyGuid,
                0, NULL,
                &TcgPeiPolicy);

    if(EFI_ERROR(Status) || TcgPeiPolicy == NULL )return 0;

    TcgPeiPolicy->getTcgPeiPolicy(PeiServices, &Configuration);
    return(Configuration.Reserved1);
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
    UINT8                          HashAlgo = GetHashPolicy(PeiServices);
    UINTN                           NextLocation;
    

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

    //prepare next location
    NextLocation = FindNextLogLocation((TCG_PCR_EVENT_HDR*)(TcgLog + 1), TcgLog->EventNum);

    Status = TcgCommonLogEvent(
            &Context,
            (TCG_PCR_EVENT*)(NextLocation),
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
    
    if(SupportType==1){
        if(GetHashPolicy(((TCG_PEI_CALLBACK_CONTEXT *)CallbackContext)->PeiServices) ==0 ){
            return(Tcg20CommonExtend(CallbackContext, PCRIndex, Digest, NewPCRValue, 20));
        }else{
            return(Tcg20CommonExtend(CallbackContext, PCRIndex, Digest, NewPCRValue, 32));
        }
    }

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
    EFI_GUID                 Tpm20Hobguid = TPM20_HOB_GUID;
    AMI_TPM20SUPPORTTYPE_PPI *Tpm20PeiSupportPpi = NULL;   

    Status = FillCallbackContext( PeiServices, &Context );
    ASSERT_PEI_ERROR( PeiServices, Status );

#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(NewEvent->EventType == EV_EFI_ACTION)
    {
        return EFI_SUCCESS;
    }
#endif

    if(GetHashPolicy( PeiServices)==0)
    {
        Status = SHA1HashAll( &Context, HashData, HashDataLen, &NewEvent->Digest );
    }else{
        //Status = SHA2HashAll(&Context, HashData, HashDataLen, &NewEvent->Digest);
    }

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    Status = Context.TpmDevice->Init( Context.TpmDevice, PeiServices );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }
    
    if(SupportType == 0xff)
    {
        Status = (*PeiServices)->LocatePpi(
                    PeiServices,
                    &Tpm20Hobguid,
                    0, NULL,
                    &Tpm20PeiSupportPpi);

        if(!EFI_ERROR(Status) && Tpm20PeiSupportPpi!= NULL){
            SupportType = 1;
        }else{
            SupportType = 0;
        }
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
EFIAPI TcgPeiEntry(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS Status;
    EFI_PHYSICAL_ADDRESS TPM_Base = (EFI_PHYSICAL_ADDRESS)PORT_TPM_IOMEMBASE;
#if TCG_LEGACY == 0
    Status = IsTpmPresent((TPM_1_2_REGISTERS_PTR)( UINTN ) TPM_Base );
    if(EFI_ERROR(Status))return Status;
#endif    
    Status = (*PeiServices)->InstallPpi( PeiServices, mTcgPpiList );
    return Status;
}
