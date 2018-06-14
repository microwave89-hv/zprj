//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardTPMPei/BootGuardTPMPei.c 3     9/06/13 6:10a Bensonlai $
//
// $Revision: 3 $
//
// $Date: 9/06/13 6:10a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardTPMPei/BootGuardTPMPei.c $
// 
// 3     9/06/13 6:10a Bensonlai
// [TAG]  		EIP135513
// [Category]  	Improvement
// [Description]  	Support the TPM1.2 for WHCK test
// 
// 2     7/25/13 11:02p Bensonlai
// [TAG]  		EIP130647
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Detail PCR is incorrect for Boot Guard.
// [RootCause]  	Coding error.
//
// 1     6/04/13 5:15a Bensonlai
// [TAG]  		EIP125148
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	[SBY ULT] Boot Guard for 4th Gen Intel Core Processor
// based on Mobile U-Processor Line - BIOS Writer's Guide - Rev 1.0
// [Files]  		BootGuardTPMPei.cif
// BootGuardTPMPei.c
// BootGuardTPMPei.h
// BootGuardTPMPei.sdl
// BootGuardTPMPei.mak
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: BootGuardTPMPei.c
//
// Description: TPM Initialization Flow for Boot Guard
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Efi.h>
#include <Pei.h>
#include <TcgCommon.h>
#include <AmiPeiLib.h>
#include <TcgMisc.h>
#include "PPI\TcgService\TcgTcmService.h"
#include "PPI\TcgService\TcgService.h"
#include "PPI\TpmDevice\TpmDevice.h"
#include "PPI\CpuIo.h"
#include "PPI\LoadFile.h"
#include <Ppi\ReadOnlyVariable.h>
#include "AmiTcgPlatformPei.h"
#include "TcgPlatformSetupPeiPolicy.h"
#include <Token.h>
#include "CpuRegs.h"
#include <AmiCspLibInc.h>
#include "BootGuardTPMPei.h"

static
EFI_STATUS
__stdcall __FillCallbackContext(
    IN EFI_PEI_SERVICES          **PeiService,
    OUT TCG_PEI_CALLBACK_CONTEXT *CallbackContext )
{
    EFI_GUID _gPeiTpmPpiGuid = PEI_TPM_PPI_GUID;
    CallbackContext->PeiServices = PeiService;
    return (*PeiService)->LocatePpi(
               PeiService,
               &_gPeiTpmPpiGuid,
               0,
               NULL,
               &CallbackContext->TpmDevice
           );
}

#define TCGPASSTHROUGH( cb, in, out ) \
    TcgCommonPassThrough(  \
        cb, \
        sizeof (in) / sizeof (*(in)), \
        (in), \
        sizeof (out) / sizeof (*(out)), \
        (out) \
        )

EFI_STATUS TcgCommonSha1Complete(
    IN VOID         *CallbackContext,
    IN VOID         *Data,
    IN UINT32       DataLen,
    OUT TCG_DIGEST  *Digest )
{
    TPM_1_2_CMD_SHA1COMPLETE       cmdSHA1Complete;
    TPM_1_2_RET_HEADER             retSHA1Complete;
    TPM_TRANSMIT_BUFFER            InBuffer[2], OutBuffer[2];

    if ( DataLen >= 64 )
    {
        return EFI_INVALID_PARAMETER;
    }

    cmdSHA1Complete.Header.Tag       = TPM_H2NS( TPM_TAG_RQU_COMMAND );
    cmdSHA1Complete.Header.ParamSize = TPM_H2NL(sizeof(cmdSHA1Complete) + DataLen);
    cmdSHA1Complete.Header.Ordinal = TPM_H2NL( TPM_ORD_SHA1Complete );

//    if(AutoSupportType()){
//         cmdSHA1Complete.Header.Ordinal = TPM_H2NL(TCM_ORD_SHA1Complete);
//    }

    cmdSHA1Complete.NumBytes       = TPM_H2NL( DataLen );

    InBuffer[0].Buffer = &cmdSHA1Complete;
    InBuffer[0].Size   = sizeof (cmdSHA1Complete);
    InBuffer[1].Buffer = Data;
    InBuffer[1].Size   = DataLen;

    OutBuffer[0].Buffer = &retSHA1Complete;
    OutBuffer[0].Size   = sizeof (retSHA1Complete);
    OutBuffer[1].Buffer = Digest;
    OutBuffer[1].Size   = sizeof (*Digest);

    return TCGPASSTHROUGH( CallbackContext, InBuffer, OutBuffer );
}

EFI_STATUS
SHA1HashFunc (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN UINT8                *HashData,
    IN UINT32               HashDataLen,
    OUT TCG_DIGEST          *Digest
)
{
    EFI_STATUS                  Status;
    UINT32                      Sha1MaxBytes;
    TCG_PEI_CALLBACK_CONTEXT    Context;

    Status = __FillCallbackContext( PeiServices, &Context );
    ASSERT_PEI_ERROR( PeiServices, Status );

    Status = Context.TpmDevice->Init( Context.TpmDevice, PeiServices );

    if ( EFI_ERROR( Status )) {
        goto Exit;
    }

    Status = TcgCommonSha1Start( &Context, TCG_ALG_SHA, &Sha1MaxBytes );

    if ( EFI_ERROR( Status )) {
        goto Exit;
    }

    Status = TcgCommonSha1Update(
                 &Context,
                 HashData,
                 HashDataLen,
                 Sha1MaxBytes
             );

    if ( EFI_ERROR( Status )) {
        goto Exit;
    }

    HashData    += (HashDataLen & ~63);
    HashDataLen &= 63;

    Status = TcgCommonSha1Complete(
                 &Context,
                 (UINT8 *)HashData,
                 (UINT32)HashDataLen,
                 Digest
             );

    if ( EFI_ERROR( Status )) {
        goto Exit;
    }

Exit:
    Context.TpmDevice->Close( Context.TpmDevice, PeiServices );
    return Status;
}

EFI_STATUS ACM_PostSuccess(
    IN EFI_PEI_SERVICES **PeiServices
)
{
    UINT32  MsrValue;

    MsrValue = (UINT32) ReadMsr (MSR_BOOT_GUARD_SACM_INFO);
    if ( ((MsrValue & B_NEM_INIT) == B_NEM_INIT)  &&
         ((MsrValue & B_MEASURED) == B_MEASURED)  &&         
         (((MsrValue & V_TPM_PRESENT_DTPM_12) == V_TPM_PRESENT_DTPM_12) || ((MsrValue & V_TPM_PRESENT_DTPM_20) == V_TPM_PRESENT_DTPM_20)) &&
         ((MsrValue & B_TPM_SUCCESS) == B_TPM_SUCCESS) ) {
        PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : ACM_PostSuccess : EFI_SUCCESS\n"));
        return EFI_SUCCESS;
    }

    PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : ACM_PostSuccess : EFI_UNSUPPORTED\n"));
    return EFI_UNSUPPORTED;
}

EFI_STATUS LogDetailPCREvent(
    IN EFI_PEI_SERVICES **PeiServices
)
{
    UINT8                     FoundACM, FoundKM, FoundBPM;
    UINT32                    u32HashLen = 0;
    EFI_TCG_PCR_EVENT         TcgEvent;
    UINT32                    EventNum, FitEntryPointer, FitEntryNumber, i;
    UINTN                     Len;
    CHAR8                     DetailPCRStr[] = "Boot Guard Measured S-CRTM";
    PEI_TPM_PPI               *TpmPpi = NULL;
    PEI_TCG_PPI               *TcgPpi = NULL;
    EFI_STATUS                Status;
    BOOT_POLICY               *BP;
    FIT_ENTRY                 *FitEntry;
    KEY_MANIFEST_STRAUCTURE   *KmStructure;
    BpmStruct                 *BpmStructure;

    Len         = sizeof(DetailPCRStr) < sizeof(EFI_GUID) ? sizeof(DetailPCRStr) : sizeof(EFI_GUID);

    TcgEvent.Header.PCRIndex      = 0;
    TcgEvent.Header.EventType     = EV_S_CRTM_VERSION;
    TcgEvent.Header.EventDataSize = Len;

    PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] Starting 1"));

    MemCpy(
        &TcgEvent.Event.SCrtmVersion,
        DetailPCRStr,
        Len
    );

    Status = LocateTcgPpi(PeiServices,&TpmPpi, &TcgPpi);
    if(EFI_ERROR(Status))return EFI_NOT_FOUND;

    // On page 44.
    // The pHashData must be the format .
    // SHA-1 {
    //          1) One byte containing the lower 8 bit of the BP.RSTR
    //          2) One byte contain the lower 8 bits of BP.TYPE
    //          ....
    //          7)  Digest of Hashed IBB Segments(s)

    Status = (*PeiServices)->AllocatePool(PeiServices, sizeof (BOOT_POLICY),&BP);
    if ( EFI_ERROR( Status ) ) {
        return EFI_OUT_OF_RESOURCES;
    }

    BP->RSTR0 = (ReadMsr (MSR_BOOT_GUARD_SACM_INFO) & BIT4) ? 1 : 0;
    BP->RSTR1 = (MmioRead32 (ACM_STATUS) & BIT21) ? 1 : 0;
    BP->RSTR2 = (MmioRead32 (ACM_STATUS) & BIT22) ? 1 : 0;
    BP->RSTR3 = (MmioRead32 (ACM_STATUS) & BIT23) ? 1 : 0;
    BP->RSTR4 = (MmioRead32 (ACM_STATUS) & BIT24) ? 1 : 0;
    BP->RSTR5 = 0;
    BP->RSTR6 = 0;
    BP->RSTR7 = 0;

    BP->TYPE0 = (ReadMsr (MSR_BOOT_GUARD_SACM_INFO) & BIT5) ? 1 : 0;
    BP->TYPE1 = (ReadMsr (MSR_BOOT_GUARD_SACM_INFO) & BIT6) ? 1 : 0;
    BP->TYPE2 = (MmioRead32 (ACM_STATUS) & BIT20) ? 1 : 0;
    BP->TYPE3 = 0;
    BP->TYPE4 = 0;
    BP->TYPE5 = 0;
    BP->TYPE6 = 0;
    BP->TYPE7 = 0;

    BP->ACM_SVN = ACMSVN;
    {
        FitEntryPointer = MmioRead32(IBB_ENTRYPOINT_M);
        if ( FitEntryPointer == 0xFFFFFFFF ) {
            PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : FitEntryPointer(%lx) is empty\n", FitEntryPointer));
            ASSERT_PEI_ERROR( PeiServices, EFI_NOT_READY );
        }

        FitEntry = (FIT_ENTRY*)FitEntryPointer;
        if ( FitEntry->TblAddress != EFI_SIGNATURE_64 ('_', 'F', 'I', 'T', '_', ' ', ' ', ' ') ) {
            PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : [Type 0] FitEntry->TblAddress(%lx) is error\n", FitEntry->TblAddress));
            ASSERT_PEI_ERROR( PeiServices, EFI_NOT_READY );
        }

        FitEntryNumber = FitEntry->TblSIZE;

        FoundACM = 0;
        for(i=1; i<FitEntryNumber; i++) {
            FitEntry = (FIT_ENTRY*)(FitEntryPointer + i*16);
            PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : FitEntry->TblType = %x\n", FitEntry->TblType));
            if ( FitEntry->TblType == 0x02 ) { // FIT type 0x02 - Anc ACM location
                FoundACM =1;
                break;
            }
        }

        if ( FoundACM == 0 ) {
            PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : Can't find the Boot Guard ACM"));
            ASSERT_PEI_ERROR( PeiServices, EFI_NOT_READY );
        }

        PEI_TRACE((-1, PeiServices, "BP->ACM_Signature \n"));

        for ( i=0; i<256; i++ ) {
            if (i % 16 == 0) PEI_TRACE((-1, PeiServices, "\n"));
            BP->ACM_Signature[i] = MmioRead8( FitEntry->TblAddress + 0x184 + i );
            PEI_TRACE((-1, PeiServices, "%02x ", BP->ACM_Signature[i]));
        }

        FoundKM = 0;
        for(i=1; i<FitEntryNumber; i++) {
            FitEntry = (FIT_ENTRY*)(FitEntryPointer + i*16);
            PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : FitEntry->TblType = %x\n", FitEntry->TblType));
            if ( FitEntry->TblType == 0x0B ) { // FIT Type 0x0B - Key Manifest
                FoundKM =1;
                break;
            }
        }

        if ( FoundKM == 0 ) {
            PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : Can't find the Boot Guard KM"));
            ASSERT_PEI_ERROR( PeiServices, EFI_NOT_READY );
        }

        KmStructure = (KEY_MANIFEST_STRAUCTURE*)FitEntry->TblAddress;
        PEI_TRACE((-1, PeiServices, "\nKmStructure:\n"));

        for ( i=0; i<256; i++ ) {
            if (i % 16 == 0) PEI_TRACE((-1, PeiServices, "\n"));
            BP->Key_Manifest_Signature[i] = KmStructure->KeyManifestSignature.Signature.Signature[i];
            PEI_TRACE((-1, PeiServices, "%02x ", BP->Key_Manifest_Signature[i]));
        }

        FoundBPM = 0;
        for(i=1; i<FitEntryNumber; i++) {
            FitEntry = (FIT_ENTRY*)(FitEntryPointer + i*16);
            PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : FitEntry->TblType = %x\n", FitEntry->TblType));
            if ( FitEntry->TblType == 0x0C ) { // FIT type 0x0C - Boot Policy Manifest
                FoundBPM =1;
                break;
            }
        }

        if ( FoundBPM == 0 ) {
            PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] : Can't find the Boot Guard BPM"));
            ASSERT_PEI_ERROR( PeiServices, EFI_NOT_READY );
        }

        BpmStructure = (BpmStruct*)FitEntry->TblAddress;
        PEI_TRACE((-1, PeiServices, "\nBpmStructure:\n"));

        for ( i=0; i<256; i++ ) {
            if (i % 16 == 0) PEI_TRACE((-1, PeiServices, "\n"));
            BP->Boot_Policy_Manifest_Signature[i] = BpmStructure->Bpm_Signature_Element.KeySignature.Signature.Signature[i];
            PEI_TRACE((-1, PeiServices, "%02x ", BP->Boot_Policy_Manifest_Signature[i]));
        }

        PEI_TRACE((-1, PeiServices, "\n\nBpmStructure->Digest_of_Hashed_IBB_Segment:\n\n"));

        for ( i=0; i<32; i++ ) {
            if (i % 16 == 0) PEI_TRACE((-1, PeiServices, "\n"));
            BP->Digest_of_Hashed_IBB_Segment[i] = BpmStructure->Ibb_Element.Digest.HashBuffer[i];
            PEI_TRACE((-1, PeiServices, "%02x ", BP->Digest_of_Hashed_IBB_Segment[i]));
        }

        PEI_TRACE((-1, PeiServices, "\n"));
    }

    SHA1HashFunc( PeiServices, (UINT8*)BP, u32HashLen, &TcgEvent.Header.Digest );

    Status = TcgPpi->TCGLogEvent(TcgPpi, PeiServices, (TCG_PCR_EVENT*)&TcgEvent, &EventNum);

    return Status;
}

/*
EFI_STATUS LogAuthorityPCREvent(
    IN EFI_PEI_SERVICES **PeiServices
)
{
    UINT8*  pHashData = NULL;
    UINT32  u32HashLen = 0;

    EFI_TCG_PCR_EVENT TcgEvent;
    UINT32            EventNum;
    UINTN             Len;
    CHAR16            AuthorityPCRStr[] = L"Boot Guard Measured S-CRTM";
    PEI_TPM_PPI       *TpmPpi = NULL;
    PEI_TCG_PPI       *TcgPpi = NULL;
    EFI_STATUS        Status;

    Len         = sizeof(AuthorityPCRStr) < sizeof(EFI_GUID) ? sizeof(AuthorityPCRStr) : sizeof(EFI_GUID);

    TcgEvent.Header.PCRIndex      = 6;
    TcgEvent.Header.EventType     = EV_EFI_VARIABLE_DRIVER_CONFIG;
    TcgEvent.Header.EventDataSize = Len;

    MemCpy(
        &TcgEvent.Event.SCrtmVersion,
        AuthorityPCRStr,
        Len
    );

    Status = LocateTcgPpi(PeiServices,&TpmPpi, &TcgPpi);
    if(EFI_ERROR(Status))return EFI_NOT_FOUND;

    // On page 45~46.
    // The pHashData must be the format .
    // SHA-1 {
    //          1) One byte containing the lower 8 bit of the BP.RSTR
    //          2) One byte contain the lower 8 bits of BP.TYPE
    //          ....
    //          7)  One byte indicating status of verified boot.

//    SHA1HashFunc( PeiServices, pHashData, u32HashLen, &TcgEvent.Header.Digest );

    Status = TcgPpi->TCGLogEvent(TcgPpi, PeiServices, (TCG_PCR_EVENT*)&TcgEvent, &EventNum);
    return Status;
}
*/

EFI_STATUS
BootGuardMeasureCRTMVersion(
    IN EFI_PEI_SERVICES **PeiServices )
{
    EFI_STATUS Status;
    PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] Start of BootGuardMeasureCRTMVersion\n"));

    Status = ACM_PostSuccess( PeiServices );
    if( !EFI_ERROR(Status) )
    {
        PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] Start the LogDetailPCREvent\n"));
        Status = LogDetailPCREvent( PeiServices );
        ASSERT_PEI_ERROR( PeiServices, Status );
//        Status = LogAuthorityPCREvent( PeiServices );
//        ASSERT_PEI_ERROR( PeiServices, Status );
    }

    PEI_TRACE((-1, PeiServices, "[BootGuardTPMPei.c] End of BootGuardMeasureCRTMVersion\n"));

    return MeasureCRTMVersion( PeiServices );
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
