//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgCRBPei.c 3     4/21/14 3:45p Fredericko $
//
// $Revision: 3 $
//
// $Date: 4/21/14 3:45p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgCRBPei.c $
// 
// 3     4/21/14 3:45p Fredericko
// 
// 2     4/21/14 3:16p Fredericko
// 
// 1     4/21/14 2:16p Fredericko
// 
// 2     3/17/14 3:17p Fredericko
// 
// 1     10/08/13 12:02p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 1:55p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
//
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  
//
// Description: 
//  
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
#include "Tpm20CRBLib.h"
#include "PPI\CpuIo.h"
#include "PPI\LoadFile.h"
#include <FFS.h>
#include "TcgPlatformSetupPeiPolicy.h"


//*********************************************************************
//                      GLOBAL DEFINITIONS
//*********************************************************************
EFI_GUID gEfiCrbPeiAmiTcgLogHobGuid        = EFI_TCG_LOG_HOB_GUID;
EFI_GUID gPeiCrbTcgPpiGuid                 = PEI_TCG_PPI_GUID;


UINT8  GetHashPolicy(IN EFI_PEI_SERVICES    **PeiServices);



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InternalPeiBuildHobGuid
//
// Description: Internal abstracted function to create a Hob
//
// Input:       IN  EFI_PEI_SERVICES  **PeiServices,
//              IN  EFI_GUID          *Guid,
//              IN  UINTN             DataLength,
//              OUT VOID              **Hob
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
EFI_STATUS InternalPeiBuildHobGuid(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_GUID         *Guid,
    IN UINTN            DataLength,
    OUT VOID            **Hob )
{
    EFI_STATUS Status;

    Status = (*PeiServices)->CreateHob(
        PeiServices,
        EFI_HOB_TYPE_GUID_EXTENSION,
        (UINT16) ( sizeof (EFI_HOB_GUID_TYPE) + DataLength ),
        Hob
        );

    if ( EFI_ERROR( Status ))
    {
        return Status;
    }
    
    PEI_TRACE((-1, PeiServices, "Hob created \n")); 
    ((EFI_HOB_GUID_TYPE*)(*Hob))->Name = *Guid;

    return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI CrbGetEventLog(
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

    return GetNextGuidHob( &HobStart, &gEfiCrbPeiAmiTcgLogHobGuid, EventLog, NULL );
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
EFIAPI CrbTcgPeiLogEvent(
    IN PEI_TCG_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN TCG_PCR_EVENT    *Event,
    OUT UINT32          *EventNum )
{
    EFI_STATUS                     Status = EFI_SUCCESS;
    TCG_LOG_HOB                    *TcgLog;
    

#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(Event->EventType == EV_EFI_ACTION)
    {
        return EFI_SUCCESS;
    }
#endif

    Status = CrbGetEventLog( PeiServices, &TcgLog );
    if ( EFI_ERROR( Status ))goto Exit;

    Status = TcgCommonLogEvent(NULL,
                (TCG_PCR_EVENT*)(TcgLog + 1),
                &TcgLog->TableSize,
                TcgLog->TableMaxSize,
                Event, 0);

    if ( EFI_ERROR( Status ))goto Exit;

    *EventNum = TcgLog->EventNum;
    TcgLog->EventNum++;

Exit:
    return Status;
}






//**********************************************************************
//<AMI_PHDR_START>
// Name:  TcgPeiHashLogExtendEventTpm
//
// Description: TCGPEI common function to Hash, Log and Extend data using TPM
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
EFIAPI CrbTcgPeiHashLogExtendEventTpm(
    IN PEI_TCG_PPI       *This,
    IN EFI_PEI_SERVICES  **PeiServices,
    IN UINT8             *HashData,
    IN UINT32            HashDataLen,
    IN OUT TCG_PCR_EVENT *NewEvent,
    OUT UINT32           *EventNum )
{
    return EFI_UNSUPPORTED;
}


EFI_STATUS
CrbTpm20PeiExtend(
    IN EFI_PEI_SERVICES  **PeiServices,
    IN TPM_PCRINDEX PcrIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue )
{
    TPM2_PCRExtend_cmd_t  Cmd;
    TPM2_PCRExtend_res_t  Res;
    TPM2_PCRExtend_res_t  Tmpres;
    UINT32                CmdSize;
    UINT8                 *Buffer;
    UINT8                 *AuthSizeOffset;
    UINT8                 *ResultBuf = NULL;
    UINT32                ResultBufSize = 0;
    UINT32                DigestSize;
    EFI_STATUS            Status;

    Cmd.Tag          = (TPMI_ST_COMMAND_TAG)TPM_H2NS(TPM_ST_SESSIONS);
    Cmd.CommandSize  = TPM_H2NL(sizeof(Cmd));
    Cmd.CommandCode  = TPM_H2NL(TPM_CC_PCR_Extend);

    Buffer = (UINT8 *)&Cmd.inputParameters;
    *(UINT32 *)Buffer = TPM_H2NL(PcrIndex);
    Buffer += sizeof(UINT32);

    AuthSizeOffset = Buffer;
    *(UINT32 *)Buffer = 0;
    Buffer += sizeof(UINT32);

    //  pcr authHandle
    *(UINT32 *)Buffer = TPM_H2NL(TPM_RS_PW);
    Buffer += sizeof(UINT32);

    // nonce = nullNonce
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // sessionAttributes = 0
    *(UINT8 *)Buffer = 0;
    Buffer += sizeof(UINT8);

    // auth = nullAuth
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // authorizationSize
    *(UINT32 *)AuthSizeOffset = TPM_H2NL((UINT32)(Buffer - AuthSizeOffset - sizeof(UINT32)));

	//Digest count
	*(UINT32 *)Buffer = TPM_H2NL(1);
    Buffer += sizeof(UINT32);

	//Hash alg
	// Get the digest size based on Hash Alg
    if(GetHashPolicy(PeiServices)==0){
        //Hash alg
	    *(UINT16 *)Buffer = TPM_H2NS(TPM2_ALG_SHA1);
        Buffer += sizeof(UINT16);
        DigestSize = 0x14;
        TcgCommonCopyMem(NULL, Buffer, &Digest->digest, DigestSize);
    }else{
	    //Hash alg
	    /**(UINT16 *)Buffer = TPM_H2NS(TPM2_ALG_SHA256);
        Buffer += sizeof(UINT16);
        DigestSize = 0x20;
        TcgCommonCopyMem(NULL, Buffer, &Digest->digestSha2, DigestSize);*/
        return EFI_UNSUPPORTED;
    }

    Buffer += DigestSize;

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.CommandSize = TPM_H2NL(CmdSize);

    ResultBuf     = (UINT8 *) &Tmpres;
    ResultBufSize = sizeof(Res);
    
    
    PEI_TRACE((-1, PeiServices, "OutputSizeBefore = %x \n", ResultBufSize)); 
    
    Status = CrbSubmitCmd((UINT8 *)&Cmd, CmdSize, ResultBuf, &ResultBufSize);

    PEI_TRACE((-1, PeiServices, "Status = %r \n", Status)); 
    PEI_TRACE((-1, PeiServices, "OutputSizeAfter = %x \n", ResultBufSize)); 

    return Status;
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
EFI_STATUS CrbTcgPeiHashLogExtendEventSW(
    IN PEI_TCG_PPI       *This,
    IN EFI_PEI_SERVICES  **PeiServices,
    IN UINT8             *HashData,
    IN UINT32            HashDataLen,
    IN OUT TCG_PCR_EVENT *NewEvent,
    OUT UINT32           *EventNum )
{
    EFI_STATUS               Status;
    TCG_DIGEST               NewPCRValue;

#if defined LOG_EV_EFI_ACTION && LOG_EV_EFI_ACTION == 0
    if(NewEvent->EventType == EV_EFI_ACTION)
    {
        return EFI_SUCCESS;
    }
#endif

    if(GetHashPolicy(PeiServices)==0)
    {
        Status = SHA1HashAll( NULL, HashData, HashDataLen, &NewEvent->Digest );
        if ( EFI_ERROR( Status )){
            PEI_TRACE((-1, PeiServices, "SHA1HashAll fail %r \n", Status)); 
            return Status;
        }
    }else if(GetHashPolicy(PeiServices)==1){
       /* Status = SHA2HashAll( NULL, HashData, HashDataLen, &NewEvent->Digest);
        if ( EFI_ERROR( Status )){
            PEI_TRACE((-1, PeiServices, "SHA1HashAll fail %r \n", Status)); 
            return Status;
        }*/
    }

    Status = CrbTpm20PeiExtend(
                PeiServices,
                NewEvent->PCRIndex,
                &NewEvent->Digest,
                &NewPCRValue  );

    if ( EFI_ERROR( Status )){
        PEI_TRACE((-1, PeiServices, "CrbTpm20PeiExtend fail %r \n", Status)); 
        goto Exit;
    }

    Status = CrbTcgPeiLogEvent( This, PeiServices, NewEvent, EventNum );
    PEI_TRACE((-1, PeiServices, "CrbTcgPeiLogEvent fail %r \n", Status)); 

Exit:
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
EFIAPI CrbTcgPeiPassThroughToTpm(
    IN PEI_TCG_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices,
    IN UINT32           TpmInputParameterBlockSize,
    IN UINT8            *TpmInputParameterBlock,
    IN UINT32           TpmOutputParameterBlockSize,
    IN UINT8            *TpmOutputParameterBlock )
{
  UINT32 Size = 0;
  EFI_STATUS Status;
  Size = TpmOutputParameterBlockSize;

  PEI_TRACE((-1, PeiServices, "CrbTcgPeiPassThroughToTpm Execution \n")); 

  PEI_TRACE((-1, PeiServices, "OutputSizeBefore = %x \n", Size)); 

  Status = CrbSubmitCmd(TpmInputParameterBlock,
                       TpmInputParameterBlockSize,
                       TpmOutputParameterBlock,
                       &Size);

  PEI_TRACE((-1, PeiServices, "Status = %r \n", Status)); 
  PEI_TRACE((-1, PeiServices, "OutputSizeAfter = %x \n", Size)); 
  return Status;
}


static PEI_TCG_PPI            mTcgPpi = {
    CrbTcgPeiHashLogExtendEventSW,
    CrbTcgPeiLogEvent,
    CrbTcgPeiPassThroughToTpm
};

static EFI_PEI_PPI_DESCRIPTOR mTcgPpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiCrbTcgPpiGuid,
        &mTcgPpi
    }
};



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Tpm20CrbEntry
//
// Description: 
//
//
// Input:       
//
// Output:     
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI Tpm20CrbEntry(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS          Status;
    TCG_LOG_HOB         *TcgLog;
    EFI_HOB_GUID_TYPE   *Hob;

    if(!isTpm20CrbPresent())return EFI_NOT_FOUND;
    Status = InternalPeiBuildHobGuid(PeiServices, &gEfiCrbPeiAmiTcgLogHobGuid,
           (sizeof (*TcgLog) + 0x200),  & Hob);

    PEI_TRACE((-1, PeiServices, "CrbBuild Hob Status = %r \n", Status)); 

    TcgLog = (TCG_LOG_HOB*)(Hob + 1);
    (*PeiServices)->SetMem( TcgLog, sizeof (*TcgLog), 0 );
    TcgLog->TableMaxSize = 0x200;
    Status = (*PeiServices)->InstallPpi( PeiServices, mTcgPpiList );
    return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
