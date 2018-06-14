//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureSmiFlash/VerifyFwCapsule.c 30    7/03/14 10:15a Alexp $
//
// $Revision: 30 $
//
// $Date: 7/03/14 10:15a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureSmiFlash/VerifyFwCapsule.c $
// 
// 30    7/03/14 10:15a Alexp
// EIP176297: Fix bug in condition expresison inside For loops. 
// 
// 29    5/20/14 5:22p Alexp
// Replace a var name gRomFileSize to a more appropriate gFwCapMaxSize
// 
// 27    3/20/14 12:31p Alexp
// 1. Don't re-read FwKey. Use gpPubKeyHndl
// 2. CapsuleValidate: sanity check: FwCapHdr RomImageOffset checked
// against max size 
//  (FWCAPSULE_IMAGE_SIZE-FLASH_SIZE)
// 3. CapsuleValidate: add parameter check pFWCapsuleHdr != NULL
// 
// 26    8/22/13 11:34a Alexp
// VerifyFwCertRsa2048Sha256() - Break a loop after RootCert Verify if key
// match is found. Old code would cycle through all certs.
// 
// 25    8/12/13 4:31p Alexp
// add check for end of Certificate block marker
// 
// 24    7/11/13 3:41p Alexp
// Removed check for FWCAPSULE_MAX_HDR_SIZE. Replaced it with fixed 0x8000
// value
// 
// 23    6/27/13 9:43a Alexp
// fixed range check in ROM_MAP table processing.
// 
// 22    6/21/13 11:00a Alexp
// HashFwRomMapImage(): add check for address overflow in UIN32 build mode
// 
// 21    6/12/13 3:51p Alexp
// 1. CapsuleValidate() made external function in SecSmiFlash API
//  EIP#125800 : Privilege escalation into SMM via Secure SMI Flash SMM
//  driver via GetFlUpdPolicy and SetFlUpdMethod - BugID 305294 
//  add IsAddressInSmram() checks inside exposed API functions 
// 2. VerifyFwCertRsa2048Sha256() - parse multiple chained RootKey 
//  certificate structures  in FwCert header
// 
// 20    12/17/12 2:51p Alexp
// fix cppcheck style check finds
// 
// 19    11/21/12 10:44a Alexp
// EIP#105015: Implemented handling of Pkcs7# Certificate in Aptio Fw
// Capsule update packages
// Replace direct calls to Hash() infrom CryptoLib with calls to Crypto
// API. Saves ROM space
// 
// 
// 18    11/20/12 3:30p Alexp
// EIP[104046]: Findings from Security review on Aptio4 Image verification
//  Includes the fix for item #10: hardening of RomMap parsing oin
// FwCapsule update
// 
// 17    11/13/12 3:23p Alexp
// 1. EIP#106359 : Secure Flash Cross function fail. 
//    Move FwCapSectionGuid define outside of #if branch
// 2. Calculate offset to RomLayout table within FwCapsHdr instead of
// using hardwired location. Pkcs#7 
//     cert will differ in size and offset may change 
// 3. Remove dependency on FWSIG_SIGNHDR flag. Use Capsule flags instead.
// 
// 16    9/18/12 6:59p Alexp
// Bug: Recovery update was broken for FwCapsule with embedded signature
// and FwSig_hdr token 0.
// Fix: FindCapHdrFFS() change Ffs Hdr size testing
// 
// 15    9/06/12 7:28p Alexp
// Add new IGNORE_RUNTIME_UPDATE_IMAGE_REVISION_CHECK flag
// When set, FW Capsule Validate logic will skip image Revision check only
// for Runtime updates
// 
// 14    7/26/12 3:26p Alexp
// replaced #if FWSIG_PADDING == 0  with #if FWSIG_SIGNHDR == 1. 
// Flag in the FwCap Hdr to switch between PKCS1_5 and PSS padding is
// available only if #if FWSIG_SIGNHDR == 1
// 
// 13    5/21/12 4:55p Alexp
// keep a pointer to FwCaps Hdr withing Capsule image. Streamlines
// creation of Capsule Mailbox. 
// 
// 12    5/18/12 5:14p Alexp
//  1. Add support for Embedded FwSignature file
//  2. EIP:89687 Replace Hash PPI calls with calls to Crypto lib
// functions.
//      Allows to support RomMap tables in FwCaps Hdr with unlimited
// number of
//      entries
//  3. VerifyFwVersion. 
//      a) Moved the call after Rom image signature is verified.;
//      b) search $FID struct only in signed FVs with PEI or DXE
//     attributes
// 
// 11    4/25/12 2:11p Alexp
// Platform FW Key is compared with either Signing or if no match - with
// RootKey certificates
// 
// 9     3/09/12 11:16a Alexp
// VerifyFwImage-> fixed logic to process RomMap entries. 
// Number of signed elements in RomMap may not exceed max_num_elem
// constant. 
// Overall number of elements in th RomMap may not exceed max_num_elem x 2
// 
// 8     2/29/12 4:13p Alexp
// Update format of Capsule signing:
// 1. Entire Cap Hdr and FW_Cert Hdr are included in SigCert Signature
// calculation. Improves Cap image security
// 2. RootKey signs only SignKey buffer and not entire Sign Certificate.
//  No need for resigning of RootCert each time SignCert is being created
// 
// 7     2/13/12 1:57p Alexp
// GetFidData: Use 1 byte alligned pointer in searching "Section Guid".
// Fixes the issue with RomMap entries that are not 4 byte alligned
// 
// 6     12/29/11 4:00p Alexp
// VerifyProjectId(). 
// Calculate size of ProjectId string based on SDL Token PROJECT_TAG
// 
// 5     11/30/11 8:04p Alexp
// FW Revision searched inside FID structure. Simplified the search
// throughout FW block by 4byte aligned $FID signature only
// 
// 4     10/17/11 11:26a Alexp
// Fix misspelled FidSignature name
// 
// 3     9/29/11 3:27p Alexp
// Bug fix. EIP#71244: No Rollback support
// 
// 2     8/05/11 3:29p Alexp
// add SDL condition to IGNORE_IMAGE_ROLLBACK. Disabled by default
// 
// 4     5/16/11 5:54p Alexp
// Use 5 characters for Project Tag comparison (old was 4)
// 
// 3     5/10/11 5:09p Alexp
// Hash guids are defined globally
// 
// 2     4/13/11 7:15p Alexp
// included first draft of VersionControl code
// 
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        VerifyFwCapsule.c
//
// Description:    Verify Aptio FW capsule integrity and performs other security checks
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiDxeLib.h>
#include <Protocol\SmiFlash.h>
#include <Protocol\SecSmiFlash.h>
#include <Ppi\FwVersion.h>
#include <RomLayout.h>
#include <Ffs.h>
#include "AmiCertificate.h"

//----------------------------------------------------------------------------
// Function Externs
extern AMI_DIGITAL_SIGNATURE_PROTOCOL *gAmiSig;
extern UINTN     gFwCapMaxSize; // add 4k for capsule's header
extern EFI_GUID  gFWCapsuleGuid;
extern EFI_GUID  gPRKeyGuid;
extern EFI_GUID  gFwCapFfsGuid;
extern EFI_SHA256_HASH  *gHashTbl;
extern CRYPT_HANDLE  gpPubKeyHndl;
extern UINT8     gHashDB[SHA256_DIGEST_SIZE];

BOOLEAN IsAddressInSmram (
    IN EFI_PHYSICAL_ADDRESS  Buffer,
    IN UINT64                Length
);
//----------------------------------------------------------------------------
// Local prototypes
EFI_STATUS CapsuleValidate (
    IN OUT UINT8     **pFwCapsule,
    IN OUT APTIO_FW_CAPSULE_HEADER     **pFWCapsuleHdr
);

typedef struct {
    EFI_FFS_FILE_HEADER FfsHdr;
    EFI_COMMON_SECTION_HEADER SecHdr;
    EFI_GUID            SectionGuid;
    UINT8                FwCapHdr[0];
} AMI_FFS_COMMON_SECTION_HEADER;

//----------------------------------------------------------------------------
// Local Variables

static EFI_GUID FwCapSectionGuid = AMI_FW_CAPSULE_SECTION_GUID;

//----------------------------------------------------------------------------
#if IGNORE_RUNTIME_UPDATE_IMAGE_REVISION_CHECK == 0
//----------------------------------------------------------------------------
typedef struct _FID_SECTION {
    EFI_GUID   Guid;
    FW_VERSION FwVersion;
} FID_SECTION;

static EFI_GUID FidSectionGuid = \
    { 0x2EBE0275, 0x6458, 0x4AF9, 0x91, 0xed, 0xD3, 0xF4, 0xED, 0xB1, 0x00, 0xAA };

const UINT8 *FidSignature = "$FID";
//----------------------------------------------------------------------------
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   VerifyProjectId
//
// Description: 
//
// Input:       
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
VerifyProjectId (
    IN FW_VERSION      *FwVersionData
)
{
    char  *strProjectId = CONVERT_TO_STRING(PROJECT_TAG);
    UINTN  Size = sizeof(CONVERT_TO_STRING(PROJECT_TAG));
/*
CHAR8       BiosTag[9];     //BIOS Tag
EFI_GUID    FirmwareGuid;       //Firmware GUID
CHAR8       CoreMajorVersion[3];    
CHAR8       CoreMinorVersion[3];
CHAR8       ProjectMajorVersion[3];
CHAR8       ProjectMinorVersion[3];
*/
// Project ID, Major, Minor rev    
    TRACE((-1, "OrgBiosTag=%s,NewBiosTag=%s\nPrjMajVer=%02X, NewMajVer=%s\nPrjMinorVer=%02X, NewMinorVer=%s\n",
    FwVersionData->BiosTag, strProjectId,
    PROJECT_MAJOR_VERSION, FwVersionData->ProjectMajorVersion,
    PROJECT_MINOR_VERSION, FwVersionData->ProjectMinorVersion
    ));
    
    if (Size==0 || MemCmp (FwVersionData->BiosTag, strProjectId, Size-1)) return FALSE;
#if IGNORE_IMAGE_ROLLBACK == 0
    if(Atoi(FwVersionData->ProjectMajorVersion) < PROJECT_MAJOR_VERSION) return FALSE;
    if(Atoi(FwVersionData->ProjectMinorVersion) < PROJECT_MINOR_VERSION) return FALSE;
#endif

    return TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetFidData
//
// Description: Function to read FFS FID data structure from the given data buffer
//
// Input:       OUT FW_VERSION **Fid - pointer to output buffer
//              IN  VOID *pFV - pointer to data buffer to read from

//
// Output:      EFI_SUCCESS if FID data is retrieved
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN GetFidData(
    IN  VOID           *pFV,
    IN  UINT32          Size,
    OUT FW_VERSION    **FwVersionData
)
{
//    UINT32 Signature;
    UINT8 *SearchPointer;
    FID_SECTION *Section;

// Simplified search by $FID signature only.
//    SearchPointer = (UINT32 *)((UINT8 *)pFV + sizeof(EFI_GUID));
//    Signature = FidSectionGuid.Data1;
    SearchPointer = (UINT8 *)pFV;

    do {
//        if(*SearchPointer == Signature) {
            Section = (FID_SECTION *)SearchPointer;
            if(!guidcmp(&FidSectionGuid, &(Section->Guid)) && 
               (*((UINT32*)(&Section->FwVersion.FirmwareID[0])) == *(UINT32*)FidSignature)){ 
                *FwVersionData = &Section->FwVersion;
                return TRUE;
            }
//        }
    } while( SearchPointer++ < (UINT8*)((UINT32)pFV+Size));

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   VerifyFwRevision
//
// Description: Verify Fw revision compatibility
//              NewVer > OldVer, newProjectTAGid = oldProjectTAGid
//
// Input:
//      IN OUT UINT8 *pCapsule
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
VerifyFwRevision (
    IN APTIO_FW_CAPSULE_HEADER  *FWCapsuleHdr,
    IN UINT8 *RomData    
)    
{
    ROM_AREA                *Area;
    EFI_PHYSICAL_ADDRESS    FvAddress;
    FW_VERSION             *FwVersionData;

    Area = (ROM_AREA *)(UINTN)((UINT32)FWCapsuleHdr+FWCapsuleHdr->RomLayoutOffset);

    for (Area; Area->Size != 0; Area++) {
        if (!(Area->Attributes & ROM_AREA_FV_SIGNED)) 
            continue;
        //  $FID can be in FV with either PEI or DXE
        if (!(Area->Attributes & (ROM_AREA_FV_PEI+ROM_AREA_FV_DXE))) 
            continue;

        FvAddress = (EFI_PHYSICAL_ADDRESS)RomData + (Area->Offset);
        if (GetFidData((UINT8*)FvAddress, Area->Size, &FwVersionData)) {
            if(VerifyProjectId(FwVersionData))
                return EFI_SUCCESS;
            break;
        }
    } 
// At least one FW block must be signed OR no $FID structure found in the new FW image
    return EFI_SECURITY_VIOLATION;
}

#endif // #if IGNORE_RUNTIME_UPDATE_IMAGE_REVISION_CHECK == 0

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindCapHdrFFS
//
// Description: Function to read FW Cap Sig data from Ffs
//
// Input:       OUT UINT8 **pFwCapHdr - pointer to output buffer
//              IN  VOID *pCapsule - pointer to data buffer to read from
//
// Output:      EFI_SUCCESS if Capsule Hdr with Signature is retrieved
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindCapHdrFFS(
    IN  VOID    *pCapsule,
    OUT UINT8 **pFfsData
)
{
    UINT32 Signature;
    UINT32 *SearchPointer;
    AMI_FFS_COMMON_SECTION_HEADER *FileSection;
    APTIO_FW_CAPSULE_HEADER *pFwCapHdr;

    SearchPointer = (UINT32 *)((UINT8 *)pCapsule - sizeof(AMI_FFS_COMMON_SECTION_HEADER) + FLASH_SIZE);
    Signature = gFwCapFfsGuid.Data1;
    do {
        if(*SearchPointer == Signature) {
            FileSection = (AMI_FFS_COMMON_SECTION_HEADER *)SearchPointer;
            if(!guidcmp(&gFwCapFfsGuid, &(FileSection->FfsHdr.Name))
               && !guidcmp(&FwCapSectionGuid, &(FileSection->SectionGuid))
            ){
                pFwCapHdr = (APTIO_FW_CAPSULE_HEADER*)(FileSection->FwCapHdr);
                // just a sanity check - Cap Size must match the Section size
                if(((*(UINT32 *)FileSection->FfsHdr.Size) & 0xffffff) >=
                        pFwCapHdr->CapHdr.HeaderSize + sizeof(AMI_FFS_COMMON_SECTION_HEADER) &&
                    !guidcmp((EFI_GUID*)&pFwCapHdr->CapHdr.CapsuleGuid, &gFWCapsuleGuid)
                ){
                    *pFfsData = (UINT8*)pFwCapHdr;
                        return EFI_SUCCESS;
                }    
            }
        }
    } while(SearchPointer-- != pCapsule);

    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    HashFwRomMapImage
//
// Description:    The Rom image hash is calculated based on info from the Rom Area map
//
// Input:        
//          Payload - pointer to a FW Image
//          FwCapsuleHdr - pointer to a FW Capsule Hdr
//          RomSize - Size of Rom Image
//
// Output:      EFI_SUCCESS - capsule processed successfully
//              EFI_DEVICE_ERROR - capsule processing failed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HashFwRomMapImage (
    IN APTIO_FW_CAPSULE_HEADER  *FWCapsuleHdr,
    IN UINT8                    *Payload,
    IN UINTN                     RomSize,
    OUT UINT8                   *gHashDB
){
    EFI_STATUS              Status = EFI_SUCCESS;
    ROM_AREA                *RomAreaTbl;
    UINTN                   *Addr;
    UINTN                   *Len;
    UINTN    i, RomMap_size, max_num_elem, num_elem, max_hash_elem;

    RomAreaTbl = (ROM_AREA *)(UINTN)((UINT32)FWCapsuleHdr+FWCapsuleHdr->RomLayoutOffset);

    RomMap_size = FWCapsuleHdr->RomImageOffset-FWCapsuleHdr->RomLayoutOffset;
    max_num_elem = RomMap_size/sizeof(ROM_AREA);
// assume max size of RomMap array = RomMap_size/sizeof(ROM_AREA);
// or better yet ...calculate exact number
    num_elem = 0;
    for (i=0; i < max_num_elem && RomAreaTbl[i].Size != 0; i++ )
    {
        if (RomAreaTbl[i].Attributes & ROM_AREA_FV_SIGNED)
            num_elem++;
    }
    max_num_elem  = i;
    max_hash_elem = num_elem+2; // add 2 extra entries
    Addr = (UINTN*)gHashTbl;
    Len = (UINTN*)((UINT8*)gHashTbl + max_hash_elem*sizeof(UINTN));

    num_elem = 0;
    for (i=0; i < max_num_elem && num_elem < max_hash_elem && RomAreaTbl[i].Size != 0; i++)
    {
        if (!(RomAreaTbl[i].Attributes & ROM_AREA_FV_SIGNED)) 
            continue;
    // sanity check for buffer overruns
        if(RomAreaTbl[i].Offset > RomSize ||
           (UINT64)RomAreaTbl[i].Offset + RomAreaTbl[i].Size > RomSize)
            return EFI_SECURITY_VIOLATION;
    // RomArea only holds offsets within a payload
        Addr[num_elem] = (UINTN)((UINTN)Payload + RomAreaTbl[i].Offset);
        Len[num_elem] = RomAreaTbl[i].Size;
//TRACE((-1, "\n Num %d: Offs = %X (%X), len %X\n", num_elem, /*Addr[num_elem]*/RomAreaTbl[i].Offset, (UINT32)*(UINT32*)Addr[num_elem], Len[num_elem]));

        num_elem++;

    }
    if(num_elem >= max_hash_elem) return EFI_SECURITY_VIOLATION;
//
//  Hash of Capsule Hdr + FW Certificate Hdr
//
    if(FWCapsuleHdr->CapHdr.Flags & CAPSULE_FLAGS_CAPHDR_IN_SIGNCERT) {
        Addr[num_elem] = (UINTN) FWCapsuleHdr;
        Len[num_elem] = (UINTN)&FWCapsuleHdr->FWCert.SignCert.CertData - (UINTN)FWCapsuleHdr;
//TRACE((-1, "\n Num %d: Offs = %X (%X), len %X\n", num_elem, Addr[num_elem], (UINT32)*(UINT32*)Addr[num_elem], Len[num_elem]));
        num_elem++;
        if(num_elem >= max_hash_elem) return EFI_SECURITY_VIOLATION;
    }
//
//  Hash of the ROM_MAP table
//
    Addr[num_elem] = (UINTN)RomAreaTbl;
    Len[num_elem] = (i+1)*sizeof(ROM_AREA);
//TRACE((-1, "\n Num %d: Offs = %X (%X), len %X\n", num_elem, Addr[num_elem], (UINT32)*(UINT32*)Addr[num_elem], Len[num_elem]));
    num_elem++;

    Status = gAmiSig->Hash(gAmiSig, &gEfiHashAlgorithmSha256Guid, 
                num_elem, (const UINT8**)Addr,  (const UINTN*)Len, gHashDB );

//TRACE((-1, "\nHash the FW Image %r\nNumElems = %d\n", Status, num_elem));

//for (i=0; i<16; i++) 
//    TRACE((-1,"%02X ", (gHashDB[i]) ));

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    VerifyFwCertPkcs7
//
// Description:    This code verifies FW Capsule is genuine, 
//                 and performs following checks on the image:
//                  1. Signing certificate is signed with trusted Root Platform key
//                  2. Integrity check. Image Signature verification
//
// Input:        
//          Payload - pointer to a FW Image
//          FwCapsuleHdr - pointer to a FW Capsule Hdr
//          RomSize - Size of Rom Image
//
// Output:      EFI_SUCCESS - capsule processed successfully
//              EFI_DEVICE_ERROR - capsule processing failed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VerifyFwCertPkcs7 (
    IN APTIO_FW_CAPSULE_HEADER  *FWCapsuleHdr,
    IN UINT8                    *Payload,
    IN UINTN                     RomSize
){
    EFI_STATUS              Status;
    UINT8                  *Pkcs7Cert, *pDigest;
    UINTN                   Pkcs7Cert_len, DigestLen;
    UINT32                  Flags=0;

//    TRACE((-1, "Verify Fw Pkcs7 Cert\n"));
//
// 1. Verify Platform Key algo matches x509 cert
//
    if(guidcmp(&gpPubKeyHndl.AlgGuid, &gEfiCertX509Guid))
        return EFI_UNSUPPORTED;

// 2. Verify Signing Cert Signature
//
// 2.1 The Rom image hash is calculated based on info from the Rom Area map
//
    Status = HashFwRomMapImage(FWCapsuleHdr, Payload, RomSize, gHashDB);
    if (EFI_ERROR(Status)) return Status;

// 2.2 Verify Fw Certificate
    pDigest = &gHashDB[0];
    DigestLen = SHA256_DIGEST_SIZE;
    Pkcs7Cert = (UINT8*)&FWCapsuleHdr->FWCert.SignCert.CertData; 
    Pkcs7Cert_len = FWCapsuleHdr->FWCert.SignCert.Hdr.Hdr.dwLength-sizeof(WIN_CERTIFICATE_UEFI_GUID_1);
    Status = gAmiSig->Pkcs7Verify( gAmiSig,
                     Pkcs7Cert, Pkcs7Cert_len,           // Pkcs7Cert
                     gpPubKeyHndl.Blob, gpPubKeyHndl.BlobSize, // TrustCert
                     &pDigest, &DigestLen,               // In/OutData
                     Pkcs7CertValidate,
                     RELEASE                             // Flags, mutex
                     );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    VerifyFwCertRsa2048Sha256
//
// Description:    This code verifies FW Capsule is genuine, 
//                 and performs following checks on the image:
//                  1. Signing certificate is signed with trusted Root Platform key
//                  2. Integrity check. Image Signature verification
//
// Input:        
//          Payload - pointer to a FW Image
//          FwCapsuleHdr - pointer to a FW Capsule Hdr
//          RomSize - Size of Rom Image
//
// Output:      EFI_SUCCESS - capsule processed successfully
//              EFI_DEVICE_ERROR - capsule processing failed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VerifyFwCertRsa2048Sha256 (
    IN APTIO_FW_CAPSULE_HEADER  *FWCapsuleHdr,
    IN UINT8                    *Payload,
    IN UINTN                     RomSize
){
    EFI_STATUS              Status;
    CRYPT_HANDLE            HashHndl;
    CRYPT_HANDLE            PubKeyHndl;
    UINT8                   *pSig;
    UINT32                  Flags;
    UINT8                   *Addr;
    UINTN                   Size;
    EFI_CERT_BLOCK_RSA_2048_SHA256* pRootCert;

// Version 010 and later supporting extended flags
//    if(FWCapsuleHdr->CapHdr.Flags & CAPSULE_FLAGS_CAPHDR_IN_SIGNCERT)
    if(FWCapsuleHdr->CapHdr.HeaderSize == FWCapsuleHdr->RomImageOffset)
    {
        if(FWCapsuleHdr->CapHdr.Flags & CAPSULE_FLAGS_RSA_PSS_PADDING_SCHEME)
            Flags = EFI_CRYPT_RSASSA_PSS;
        else
            Flags = EFI_CRYPT_RSASSA_PKCS1V15;
    }
    else
        Flags = EFI_CRYPT_RSASSA_PSS;

    HashHndl.AlgGuid = gEfiHashAlgorithmSha256Guid;
    HashHndl.BlobSize =  SHA256_DIGEST_SIZE;
    HashHndl.Blob = gHashDB;

    PubKeyHndl.AlgGuid = gEfiCertRsa2048Guid;
    PubKeyHndl.BlobSize =  DEFAULT_RSA_KEY_MODULUS_LEN;
//
// 1. Compare Capsule's Sign Cert key with Platform Root Key
//
    PubKeyHndl.Blob = (UINT8*)FWCapsuleHdr->FWCert.SignCert.CertData.PublicKey;
    Status = gAmiSig->VerifyKey(gAmiSig, &gPRKeyGuid, &PubKeyHndl);
    //  Skip the RootCert key checking if SignCert Key and PR Key are matching
//TRACE((-1, "Compare SignCert Key == FW Key(%X) : %r\n", (UINT32)*PubKeyHndl.Blob, Status));
    if(EFI_ERROR(Status)) {
//
// 1.1 Compare Platform Root with Capsule's Key from a Root Key store
//
        for (pRootCert = &FWCapsuleHdr->FWCert.RootCert; 
            (UINT8*)pRootCert < 
                (UINT8*)&FWCapsuleHdr->FWCert+FWCapsuleHdr->FWCert.SignCert.Hdr.Hdr.dwLength && 
                pRootCert->PublicKey[0]!=0;
            pRootCert++) 
        {
            PubKeyHndl.Blob = pRootCert->PublicKey;
            Status = gAmiSig->VerifyKey(gAmiSig, &gPRKeyGuid, &PubKeyHndl);
//TRACE((-1, "Compare RootCert Key == FW Key(%X) : %r\n", (UINT32)*PubKeyHndl.Blob, Status));
            if (EFI_ERROR(Status)) continue;
//
// 2. Verify RootCert.Signature
//
// 2.1  Compute FWCert.SignCert.PublicKey Hash
            if(FWCapsuleHdr->CapHdr.Flags & CAPSULE_FLAGS_SIGNKEY_IN_ROOTCERT)
            {
                Addr = (UINT8*)&FWCapsuleHdr->FWCert.SignCert.CertData.PublicKey;
                Size = DEFAULT_RSA_KEY_MODULUS_LEN;
            } else
// 2.2  Compute FWCert.SignCert Hash
            {
                Addr = (UINT8*)&FWCapsuleHdr->FWCert.SignCert;
                Size = sizeof(AMI_CERTIFICATE_RSA2048_SHA256);
            }

            Status = gAmiSig->Hash(gAmiSig, &gEfiHashAlgorithmSha256Guid, 1,&Addr,(const UINTN*)&Size, gHashDB); 
            if (EFI_ERROR(Status)) break;
        
            pSig = (void*)pRootCert->Signature; 
            Status = gAmiSig->Pkcs1Verify(gAmiSig, &PubKeyHndl, &HashHndl, pSig, DEFAULT_RSA_SIG_LEN, Flags); 
//TRACE((-1, "Verify Root Cert : %r\n", Status));
            break;
        }
    }
    if (EFI_ERROR(Status)) return EFI_SECURITY_VIOLATION;
// 3. Verify Signing Cert Signature
//
// 3.1 The Rom image hash is calculated based on info from the Rom Area map
//
    Status = HashFwRomMapImage(FWCapsuleHdr, Payload, RomSize, gHashDB);
    if (EFI_ERROR(Status)) return Status;

    pSig = (void*)FWCapsuleHdr->FWCert.SignCert.CertData.Signature; 
    PubKeyHndl.Blob = (UINT8*)FWCapsuleHdr->FWCert.SignCert.CertData.PublicKey;
    Status = gAmiSig->Pkcs1Verify(gAmiSig, &PubKeyHndl, &HashHndl, pSig, DEFAULT_RSA_SIG_LEN, Flags); 

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    CapsuleValidate
//
// Description:    This code verifies FW Capsule is genuine, 
//                 and performs following checks on the image:
//                  1. Re-Play protection. Verifies that new FW image version is newer then the current one
//                  2. Signing certificate is signed with trusted Root Platform key
//                  3. Integrity check. Image Signature verification
//
// Input:        
//  IN VOID *pFwCapsule - pointer to a FW Image
//  OUT UINT8 *pFwCapsuleHdr - return a pointer to a FW Capsule Hdr(optional if parameter is not NULL)
//
// Output:      EFI_SUCCESS - capsule processed successfully
//              EFI_SECURITY_VIOLATION - capsule processing failed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CapsuleValidate (
    IN OUT UINT8     **pFwCapsule,
    IN OUT APTIO_FW_CAPSULE_HEADER     **pFWCapsuleHdr
){
    EFI_STATUS              Status = EFI_DEVICE_ERROR;
    APTIO_FW_CAPSULE_HEADER *FWCapsuleHdr;
    UINTN                   RomSize;
    UINT8                   *Payload;

    FWCapsuleHdr = (APTIO_FW_CAPSULE_HEADER*)*pFwCapsule;
    Payload = (UINT8*)*pFwCapsule;
    RomSize = FLASH_SIZE;

/*
 - CapsuleValidate 
     - Look up Capsule GUID
         - Found - 
            update pFwCapsule ptr to beginning of BIOS ROM data
            continue with Image Verify
         - Not found at offs 0 - assume Cap Hdr in FFS
            Call GetSigFFS
            locate FFS by Hole GUID, Sec GUID
             if found, update FWCapsuleHdr,
            continue with Image Verify
*/
// proper FW Capsule presence check

// verify Capsule Mailbox points to FW_CAPSULE hdr
    if(!guidcmp((EFI_GUID*)&FWCapsuleHdr->CapHdr.CapsuleGuid, &gFWCapsuleGuid))
    {
// Update pFwCapsule to point to beginning of Bios ROM
        Payload = (UINT8*)((UINT32)FWCapsuleHdr + FWCapsuleHdr->RomImageOffset);
        RomSize = (FWCapsuleHdr->CapHdr.CapsuleImageSize - FWCapsuleHdr->RomImageOffset);
        *pFwCapsule = Payload;
    }
    else
    {
//TRACE((-1, "Looking for embedded Signature...\n"));
        if(EFI_ERROR(FindCapHdrFFS(Payload, (UINT8**)&FWCapsuleHdr)))
            return EFI_SECURITY_VIOLATION;
    }
TRACE((-1, "Found Fw Capsule GUID %g\n\r", &(FWCapsuleHdr->CapHdr.CapsuleGuid)));

// update return argument with a ptr to FwCapHdr
    if(pFWCapsuleHdr)
        *pFWCapsuleHdr = FWCapsuleHdr;

// Aptio FW Capsule only supporting WIN_CERT_TYPE_EFI_GUID 
    if(FWCapsuleHdr->FWCert.SignCert.Hdr.Hdr.wCertificateType != WIN_CERT_TYPE_EFI_GUID)
        return EFI_SECURITY_VIOLATION;

// sanity check for buffer overruns
    if((FWCapsuleHdr->CapHdr.CapsuleImageSize > gFwCapMaxSize) ||
       (FWCapsuleHdr->RomImageOffset > (FWCAPSULE_IMAGE_SIZE-FLASH_SIZE)) || // 16k is a MAX possible FwCap Hdr size
       (FWCapsuleHdr->CapHdr.HeaderSize > FWCapsuleHdr->RomImageOffset) ||
       (FWCapsuleHdr->RomLayoutOffset > FWCapsuleHdr->RomImageOffset) ||
       (FWCapsuleHdr->FWCert.SignCert.Hdr.Hdr.dwLength + offsetof(APTIO_FW_CAPSULE_HEADER, FWCert) >
        FWCapsuleHdr->RomLayoutOffset )
    )
        return EFI_SECURITY_VIOLATION;

    if(!IsAddressInSmram((EFI_PHYSICAL_ADDRESS)gpPubKeyHndl.Blob, gpPubKeyHndl.BlobSize) )
        return EFI_SECURITY_VIOLATION; 
    TRACE((TRACE_ALWAYS,"gpKey (%x, %x bytes)\n",gpPubKeyHndl.Blob,gpPubKeyHndl.BlobSize));
// Begin Authentication
    if(!guidcmp((EFI_GUID*)&FWCapsuleHdr->FWCert.SignCert.Hdr.CertType, &gEfiCertTypePkcs7Guid))
        Status = VerifyFwCertPkcs7(FWCapsuleHdr, Payload, RomSize);
    else
        Status = VerifyFwCertRsa2048Sha256(FWCapsuleHdr, Payload, RomSize);
    TRACE((-1, "Signature validate %r\n", Status));
    if (EFI_ERROR(Status)) return Status;
// 
// Local PEI $FID is linked with CspLib. extern FW_VERSION FwVersionData;
// Find $FID in new Fw FVs. Any found should do for us. Use RomMap from Capsule's Hdr
// compare local BB and Main $Fid BIOS Major/Minor revs with New one.
#if IGNORE_RUNTIME_UPDATE_IMAGE_REVISION_CHECK == 0
    Status = VerifyFwRevision(FWCapsuleHdr, Payload);
//TRACE((-1, "FW Revision test %r\n", Status));
#endif
    
//TRACE((-1, "Capsule Verify %r\n", Status));

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
