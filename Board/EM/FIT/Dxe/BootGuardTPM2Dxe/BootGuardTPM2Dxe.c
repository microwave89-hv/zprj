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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardTPM2Dxe/BootGuardTPM2Dxe.c 2     10/29/13 5:15a Bensonlai $
//
// $Revision: 2 $
//
// $Date: 10/29/13 5:15a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardTPM2Dxe/BootGuardTPM2Dxe.c $
// 
// 2     10/29/13 5:15a Bensonlai
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Build error when enable the DEBUG mode.
// 
// 1     9/06/13 6:17a Bensonlai
// [TAG]  		EIP135513 
// [Category]  	New Feature
// [Description]  	Implementation of Boot Guard of PTT flow for WHCK test.
// [Files]  		BootGuardTPM2Dxe.cif
// BootGuardTPM2Dxe.c
// BootGuardTPM2Dxe.h
// BootGuardTPM2Dxe.sdl
// BootGuardTPM2Dxe.mak
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: BootGuardTPM2Dxe.c
//
// Description: TPM2 Initialization Flow for Boot Guard
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Efi.h>
#include <Pei.h>
#include "BootGuardTPM2Dxe.h"
#include <token.h>
#include "CpuRegs.h"
#include <AmiDxeLib.h>
#include "Include\Library\Tpm20.h"
#include <Protocol\TcgService\TcgService.h>

UINT32
EFIAPI
AsmReadMsr32 (
    IN      UINT32                    Index
);

#define DEBUG(arg)

VOID *
EFIAPI
GlueCopyMem (
    OUT VOID       *DestinationBuffer,
    IN CONST VOID  *SourceBuffer,
    IN UINTN       Length
);

VOID *
EFIAPI
GlueZeroMem (
    OUT VOID  *Buffer,
    IN UINTN  Length
);

VOID *
EFIAPI
GlueAllocatePool (
    IN UINTN  AllocationSize
);

#define CopyMem(_DESTINATIONBUFFER, _SOURCEBUFFER, _LENGTH)     GlueCopyMem(_DESTINATIONBUFFER, _SOURCEBUFFER, _LENGTH)
#define ZeroMem(_BUFFER, _LENGTH)                               GlueZeroMem(_BUFFER, _LENGTH)
#define AllocatePool(_SIZE)                         GlueAllocatePool(_SIZE)

#pragma pack(push, 1)

typedef union {
    UINT8 sha1[SHA1_DIGEST_SIZE];
    UINT8 sha256[SHA256_DIGEST_SIZE];
} TPM_COMM_DIGEST_UNION;

typedef struct {
    UINT16                  HashAlgId;
    TPM_COMM_DIGEST_UNION   Digest;
} TPM_COMM_DIGEST;

#pragma pack(pop)

EFI_STATUS
Tpm20Hash(
    IN  CONST UINT8                 *DataToHash,
    IN        UINTN                 DataSize,
    OUT       TPM_COMM_DIGEST       *Digest
);

EFI_STATUS
TpmDxeLogEventI(
    IN  VOID  *NewEventHdr,
    IN  UINT8              *NewEventData
);

#define ACM_STATUS (*(UINT32*)0xFED30328)

EFI_STATUS LogDetailPCREvent(
    VOID
)
{
    UINT8               FoundACM = 0, FoundKM = 0, FoundBPM = 0;
    UINT32              u32HashLen = 0;
    UINT8               byteEventBuf[0x200];
    TCG_PCR_EVENT       *TcgEvent = (TCG_PCR_EVENT*)&byteEventBuf[0];
    UINT32              EventNum = 0, FitEntryPointer = 0, FitEntryNumber = 0, i = 0;
    UINTN               Len;
    CHAR8               DetailPCRStr[] = "Boot Guard Measured S-CRTM";
    EFI_STATUS          Status = EFI_SUCCESS;
    BOOT_POLICY         *BP = NULL;
    FIT_ENTRY           *FitEntry = NULL;
    KEY_MANIFEST_STRAUCTURE   *KmStructure = NULL;
    BpmStruct                 *BpmStructure = NULL;

    ZeroMem(
        byteEventBuf,
        sizeof(byteEventBuf)
    );

    Len         = sizeof(DetailPCRStr)+1;

    TcgEvent->PCRIndex      = 0;
    TcgEvent->EventType     = EV_S_CRTM_VERSION;
    TcgEvent->EventSize     = (UINT32)Len;

    DEBUG((-1, "[BootGuardTPM2Dxe.c] : Enter LogDetailPCREvent(...)\n"));

    GlueCopyMem(
        TcgEvent->Event,
        DetailPCRStr,
        Len
    );

    // On page 44.
    // The pHashData must be the format .
    // SHA-1 {
    //          1) One byte containing the lower 8 bit of the BP.RSTR
    //          2) One byte contain the lower 8 bits of BP.TYPE
    //          ....
    //          7)  Digest of Hashed IBB Segments(s)

    BP = AllocatePool( sizeof (BOOT_POLICY));
    if ( NULL == BP ) {
        return EFI_OUT_OF_RESOURCES;
    }

    DEBUG(( -1, "MSR[0x%x]:[%08x]\n", MSR_BOOT_GUARD_SACM_INFO, AsmReadMsr32 (MSR_BOOT_GUARD_SACM_INFO) ));
    DEBUG(( -1, "ACM_STATUS:[%08x]\n", ACM_STATUS ));

    BP->RSTR0 = (AsmReadMsr32 (MSR_BOOT_GUARD_SACM_INFO) & BIT4) ? 1 : 0;
    BP->RSTR1 = (ACM_STATUS & BIT21) ? 1 : 0;
    BP->RSTR2 = (ACM_STATUS & BIT22) ? 1 : 0;
    BP->RSTR3 = (ACM_STATUS & BIT23) ? 1 : 0;
    BP->RSTR4 = (ACM_STATUS & BIT24) ? 1 : 0;
    BP->RSTR5 = 0;
    BP->RSTR6 = 0;
    BP->RSTR7 = 0;

    BP->TYPE0 = (AsmReadMsr32 (MSR_BOOT_GUARD_SACM_INFO) & BIT5) ? 1 : 0;
    BP->TYPE1 = (AsmReadMsr32 (MSR_BOOT_GUARD_SACM_INFO) & BIT6) ? 1 : 0;
    BP->TYPE2 = (ACM_STATUS & BIT20) ? 1 : 0;
    BP->TYPE3 = 0;
    BP->TYPE4 = 0;
    BP->TYPE5 = 0;
    BP->TYPE6 = 0;
    BP->TYPE7 = 0;

    BP->ACM_SVN = ACMSVN;
    {
        FitEntryPointer = MmioRead32(IBB_ENTRYPOINT_M);
        if ( FitEntryPointer == 0xFFFFFFFF ) {
            DEBUG((-1, "[BootGuardTPM2Dxe.c] : FitEntryPointer(%lx) is empty\n", FitEntryPointer));
        }

        FitEntry = (FIT_ENTRY*)FitEntryPointer;
        if ( FitEntry->TblAddress != EFI_SIGNATURE_64 ('_', 'F', 'I', 'T', '_', ' ', ' ', ' ') ) {
            DEBUG((-1, "[BootGuardTPM2Dxe.c] : [Type 0] FitEntry->TblAddress(%lx) is error\n", FitEntry->TblAddress));
        }

        FitEntryNumber = FitEntry->TblSIZE;

        FoundACM = 0;
        for(i=1; i<FitEntryNumber; i++) {
            FitEntry = (FIT_ENTRY*)(FitEntryPointer + i*16);
            if ( FitEntry->TblType == 0x02 ) { // FIT type 0x02 - Anc ACM location
                FoundACM =1;
                break;
            }
        }

        if ( FoundACM == 0 ) {
            DEBUG((-1, "[BootGuardTPM2Dxe.c] : Can't find the Boot Guard ACM"));
        }

        DEBUG((-1, "\n[BootGuardTPM2Dxe.c] : BP->ACM_Signature \n"));

        for ( i=0; i<256; i++ ) {
            if (i % 16 == 0) DEBUG((-1, "\n"));
            BP->ACM_Signature[i] = MmioRead8( FitEntry->TblAddress + 0x184 + i );
            DEBUG((-1, "%02x ", BP->ACM_Signature[i]));
        }

        DEBUG((-1, "\n"));

        FoundKM = 0;
        for(i=1; i<FitEntryNumber; i++) {
            FitEntry = (FIT_ENTRY*)(FitEntryPointer + i*16);
            if ( FitEntry->TblType == 0x0B ) { // FIT Type 0x0B - Key Manifest
                FoundKM =1;
                break;
            }
        }

        if ( FoundKM == 0 ) {
            DEBUG((-1, "[BootGuardTPM2Dxe.c] : Can't find the Boot Guard KM"));
        }

        KmStructure = (KEY_MANIFEST_STRAUCTURE*)FitEntry->TblAddress;
        DEBUG((-1, "\nKmStructure:\n"));

        for ( i=0; i<256; i++ ) {
            if (i % 16 == 0) DEBUG((-1, "\n"));
            BP->Key_Manifest_Signature[i] = KmStructure->KeyManifestSignature.Signature.Signature[i];
            DEBUG((-1, "%02x ", BP->Key_Manifest_Signature[i]));
        }

        DEBUG((-1, "\n"));

        FoundBPM = 0;
        for(i=1; i<FitEntryNumber; i++) {
            FitEntry = (FIT_ENTRY*)(FitEntryPointer + i*16);
            if ( FitEntry->TblType == 0x0C ) { // FIT type 0x0C - Boot Policy Manifest
                FoundBPM =1;
                break;
            }
        }

        if ( FoundBPM == 0 ) {
            DEBUG((-1, "[BootGuardTPM2Dxe.c] :Can't find the Boot Guard BPM"));
        }

        BpmStructure = (BpmStruct*)FitEntry->TblAddress;
        DEBUG((-1, "\nBpmStructure:\n"));

        for ( i=0; i<256; i++ ) {
            if (i % 16 == 0) DEBUG((-1, "\n"));
            BP->Boot_Policy_Manifest_Signature[i] = BpmStructure->Bpm_Signature_Element.KeySignature.Signature.Signature[i];
            DEBUG((-1, "%02x ", BP->Boot_Policy_Manifest_Signature[i]));
        }

        DEBUG((-1, "\n\nBpmStructure->Digest_of_Hashed_IBB_Segment:\n\n"));

        for ( i=0; i<32; i++ ) {
            if (i % 16 == 0) DEBUG((-1, "\n"));
            BP->Digest_of_Hashed_IBB_Segment[i] = BpmStructure->Ibb_Element.Digest.HashBuffer[i];
            DEBUG((-1, "%02x ", BP->Digest_of_Hashed_IBB_Segment[i]));
        }

        DEBUG((-1, "\n"));
    }

    {
        TPM_COMM_DIGEST                       Digest;

        u32HashLen = sizeof (BOOT_POLICY);
        Tpm20Hash( (UINT8*)BP, u32HashLen, &Digest );
        CopyMem(&TcgEvent->Digest, &Digest.Digest.sha1, SHA1_DIGEST_SIZE);
    }
    Status = TpmDxeLogEventI (
                 (VOID*)TcgEvent,
                 &TcgEvent->Event[0]);

    return Status;
}

EFI_STATUS ACM_PostSuccess(
    VOID
)
{
    UINT32  MsrValue;

    MsrValue = (UINT32) AsmReadMsr32 (MSR_BOOT_GUARD_SACM_INFO);
    if ( ((MsrValue & B_NEM_INIT) == B_NEM_INIT)  &&
         ((MsrValue & B_MEASURED) == B_MEASURED)  &&  
         ((MsrValue & V_TPM_PRESENT_PTT) == V_TPM_PRESENT_PTT) &&
         ((MsrValue & B_TPM_SUCCESS) == B_TPM_SUCCESS) ) {
        DEBUG((-1, "[BootGuardTPM2Dxe.c] : ACM_PostSuccess(...) : EFI_SUCCESS\n"));
        return EFI_SUCCESS;
    }

    DEBUG((-1, "[BootGuardTPM2Dxe.c] : ACM_PostSuccess(...) : EFI_UNSUPPORTED\n"));
    return EFI_UNSUPPORTED;
}

EFI_STATUS
BootGuardMeasureCRTMVersion(
    VOID )
{
    EFI_STATUS Status;
    DEBUG((-1, "[BootGuardTPM2Dxe.c] : Enter BootGuardMeasureCRTMVersion(...)\n"));

    Status = ACM_PostSuccess( );
    if( !EFI_ERROR(Status) )
    {
        Status = LogDetailPCREvent();
    }

    DEBUG((-1, "[BootGuardTPM2Dxe.c] : End of BootGuardMeasureCRTMVersion\n"));

    return EFI_SUCCESS;
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
