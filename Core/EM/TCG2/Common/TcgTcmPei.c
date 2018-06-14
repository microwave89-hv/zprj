//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgTcmPei.c 1     4/21/14 2:16p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:16p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgTcmPei.c $
// 
// 1     4/21/14 2:16p Fredericko
// 
// 1     10/08/13 12:02p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 1:54p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 4     4/27/12 6:04p Fredericko
// remove unused functions
// 
// 3     4/01/11 9:33a Fredericko
// Updated function Header
// 
// 2     3/29/11 12:58p Fredericko
// 
// 1     3/28/11 2:14p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 51    11/30/10 11:31p Fredericko
// [TAG}         EIP45885
// [Category]   NEW FEATURE
// [Description]   Provide hook to override Ppi request confirmation
// [Files]    TCGMisc.h, xTcgDxe.c, TcgPei.c
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
#include <TcgPc.h>
#include "PPI\TcgService\TcgTcmService.h"
#include "PPI\TcgService\TcgService.h"
#include "PPI\TpmDevice\TpmDevice.h"
#include "PPI\CpuIo.h"
#include "PPI\LoadFile.h"
#include <FFS.h>


//*********************************************************************
//                      GLOBAL DEFINITIONS
//*********************************************************************

EFI_GUID gPeiTcmPpiGuid                    = PEI_TPM_PPI_GUID;
EFI_GUID gPeiTcgTcmPpiGuid                 = PEI_TCG_PPI_GUID;

#pragma pack(1)
typedef struct _TCG_PEI_CALLBACK_CONTEXT
{
    PEI_TPM_PPI      *TpmDevice;
    EFI_PEI_SERVICES **PeiServices;
} TCG_PEI_CALLBACK_CONTEXT;
#pragma pack()

EFI_GUID gEfiPeiAmiTcmTcgLogHobGuid        = EFI_TCG_LOG_HOB_GUID;

EFI_STATUS
EFIAPI TcmPeiLogEvent(
    IN PEI_TCM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN TCM_PCR_EVENT    *Event,
    OUT UINT32          *EventNum );

EFI_STATUS
EFIAPI TcgPeiHashLogExtendEventTcm(
    IN PEI_TCM_PPI       *This,
    IN EFI_PEI_SERVICES  **PeiServices,
    IN UINT8             *HashData,
    IN UINT32            HashDataLen,
    IN OUT TCM_PCR_EVENT *NewEvent,
    OUT UINT32           *EventNum );


static
EFI_STATUS
__stdcall FillCallbackContext(
    IN EFI_PEI_SERVICES          **PeiService,
    OUT TCG_PEI_CALLBACK_CONTEXT *CallbackContext )
{
    CallbackContext->PeiServices = PeiService;
    return (*PeiService)->LocatePpi(
               PeiService,
               &gPeiTcmPpiGuid,
               0,
               NULL,
               &CallbackContext->TpmDevice
               );
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcmPeiGetEventLog
//
// Description: Helper function for logging TCM events
//
// Input:        IN EFI_PEI_SERVICES **PeiServices,
//               OUT TCG_LOG_HOB     **EventLog
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
EFIAPI TcmPeiGetEventLog(
    IN EFI_PEI_SERVICES **PeiServices,
    OUT TCG_LOG_HOB     **EventLog )
{
    EFI_STATUS Status;
    VOID       *HobStart;
    EFI_GUID gEfiPeiAmiTcgLogHobGuid        = EFI_TCG_LOG_HOB_GUID;

    Status = (*PeiServices)->GetHobList( PeiServices, &HobStart );

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    return GetNextGuidHob( &HobStart, &gEfiPeiAmiTcgLogHobGuid, EventLog, NULL );
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
    IN PEI_TCM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN UINT32           TpmInputParameterBlockSize,
    IN UINT8            *TpmInputParameterBlock,
    IN UINT32           TpmOutputParameterBlockSize,
    IN UINT8            *TpmOutputParameterBlock );



static PEI_TCM_PPI            mTcmPpi = {
    TcgPeiHashLogExtendEventTcm,
    TcmPeiLogEvent,
    TcgPeiPassThroughToTpm
};

    
static EFI_PEI_PPI_DESCRIPTOR mTcgPpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiTcgTcmPpiGuid,
        &mTcmPpi
    }
};


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  IntTcmTcgPeiGetCapabilities
//
// Description: Executes TCM operation to read capabilities
//
//
// Input:       IN      EFI_PEI_SERVICES          **PeiServices,
//
// Output:      TCM_Capabilities_PermanentFlag
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
TCM_Capabilities_PermanentFlag IntTcmTcgPeiGetCapabilities(
    IN EFI_PEI_SERVICES **PeiServices )
{
    TCM_Capabilities_PermanentFlag * cap = NULL;
    EFI_STATUS                     Status;
    TPM_GetCapabilities_Input      cmdGetCap;
    UINT8                          result[0x100];

    TCG_PEI_CALLBACK_CONTEXT       Context;

    cmdGetCap.Tag         = TPM_H2NS( TPM_TAG_RQU_COMMAND );
    cmdGetCap.ParamSize   = TPM_H2NL( sizeof (cmdGetCap));
    cmdGetCap.CommandCode = TPM_H2NL( TCM_ORD_GetCapability );
    cmdGetCap.caparea     = TPM_H2NL( TPM_CAP_FLAG );
    cmdGetCap.subCapSize  = TPM_H2NL( 4 ); // subCap is always 32bit long
    cmdGetCap.subCap      = TPM_H2NL( TPM_CAP_FLAG_PERMANENT );

    Status =                FillCallbackContext( PeiServices, &Context );
    
    ASSERT_PEI_ERROR( PeiServices, Status );

    Status = Context.TpmDevice->Init( Context.TpmDevice, PeiServices );
    ASSERT_PEI_ERROR( PeiServices, Status );

    Status = TcgPeiPassThroughToTpm(
        &mTcmPpi,
        PeiServices,
        sizeof(cmdGetCap),
        (UINT8*)&cmdGetCap,
        0x100,
        result );

    cap = (TCM_Capabilities_PermanentFlag*)result;

    PEI_TRACE((-1, PeiServices,
               "GetCapability: %r; size: %x; retCode:%x; tag:%x; bytes %08x\n",
               Status,TPM_H2NL( cap->ParamSize ), TPM_H2NL(cap->RetCode ),
               (UINT32)TPM_H2NS(cap->tag ), TPM_H2NL( *(UINT32*)&cap->disabled )));

    Status = Context.TpmDevice->Close( Context.TpmDevice, PeiServices );
    ASSERT_PEI_ERROR( PeiServices, Status );

    return *cap;
}


//**********************************************************************
//<AMI_PHDR_START>
// Name:  TcmPeiLogEvent
//
// Description: TCM common function to log PEI events
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
EFIAPI TcmPeiLogEvent(
    IN PEI_TCM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN TCM_PCR_EVENT    *Event,
    OUT UINT32          *EventNum )
{
    EFI_STATUS                     Status = EFI_SUCCESS;
    TCG_LOG_HOB                    *TcgLog;
    TCG_PEI_CALLBACK_CONTEXT       Context;
    TCM_Capabilities_PermanentFlag Cap;

    //only log events if TPM is not deactivated
    Cap = IntTcmTcgPeiGetCapabilities( PeiServices );

    if ( !Cap.deactivated )
    {
        Status = FillCallbackContext( PeiServices, &Context );
        ASSERT_PEI_ERROR( PeiServices, Status );

        Status = TcmPeiGetEventLog(PeiServices, &TcgLog );

        if ( EFI_ERROR( Status ))
        {
            goto Exit;
        }

        Status = TcmCommonLogEvent(
            &Context,
            (TCM_PCR_EVENT*)(TcgLog + 1),
            &TcgLog->TableSize,
            TcgLog->TableMaxSize,
            (TCM_PCR_EVENT *)Event
            );

        if ( EFI_ERROR( Status ))
        {
            goto Exit;
        }

        *EventNum = TcgLog->EventNum;
        TcgLog->EventNum++;
    }
Exit:
    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
// Name:  TcgPeiHashLogExtendEventTcm
//
// Description: Tcm common function to Hash, Log and Extend data
//
// Input:       IN  *This
//              IN  **PeiServices
//              IN  *HashData
//              IN  HashDataLen
//              IN  *NewEvent,
//              IN  *EventNum
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
EFIAPI TcgPeiHashLogExtendEventTcm(
    IN PEI_TCM_PPI       *This,
    IN EFI_PEI_SERVICES  **PeiServices,
    IN UINT8             *HashData,
    IN UINT32            HashDataLen,
    IN OUT TCM_PCR_EVENT *NewEvent,
    OUT UINT32           *EventNum )
{
    EFI_STATUS               Status;
    UINT32                   Sha1MaxBytes;
    TCM_DIGEST               NewPCRValue;
    TCG_PEI_CALLBACK_CONTEXT Context;

    Status = FillCallbackContext( PeiServices, &Context );
    ASSERT_PEI_ERROR( PeiServices, Status );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    Status = TcgCommonSha1Start( &Context, TCG_ALG_SHA, &Sha1MaxBytes );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    Status = TcgCommonSha1Update(
        &Context,
        HashData,
        HashDataLen,
        Sha1MaxBytes
        );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    HashData    += (HashDataLen & ~63);
    HashDataLen &= 63;

    Status = TcmCommonSha1CompleteExtend(
        &Context,
        HashData,
        HashDataLen,
        NewEvent->PCRIndex,
        &NewEvent->Digest,
        &NewPCRValue
        );

    if ( EFI_ERROR( Status ))
    {
        goto Exit;
    }

    Status = TcmPeiLogEvent( This, PeiServices, NewEvent, EventNum );

Exit:
    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgTcmPeiEntry
//
// Description: Entry point for TCM device initialization
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
EFIAPI TcgTcmPeiEntry(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS Status;

    Status = (*PeiServices)->InstallPpi( PeiServices, mTcgPpiList );
    return Status;
}
