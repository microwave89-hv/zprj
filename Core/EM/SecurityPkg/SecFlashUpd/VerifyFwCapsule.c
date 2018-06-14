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
// $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/VerifyFwCapsule.c 41    9/30/14 3:34p Alexp $
//
// $Revision: 41 $
//
// $Date: 9/30/14 3:34p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/VerifyFwCapsule.c $
// 
// 41    9/30/14 3:34p Alexp
// EIP185686:Build error with Recovery_SUPPORT = 0
// 
// 40    7/03/14 10:15a Alexp
// EIP176297: Fix bug in condition expresison inside For loops. 
// 
// [Files] VerifyFwCapsule.c
// 
// 39    6/13/14 10:08a Alexp
// VerifyFwCapsule(): With dummy FwKey function returns no error but with
// set Key flag. 
// The Recovery page must display the warning and user prompt.
// 
// 38    4/24/14 3:17p Alexp
// Fix build error when REFLASH_INTERACTIVE is 0
// 
// 37    3/20/14 11:34a Alexp
// 1. EIP149817: don't override a default Recovery file name defined by 
//     RECOVERY_ROM
// 2. Add logic to ignore Capsule Verify error if dummy FwKey is detected.
// The feature is activated only when REFLASH_INTERACTIVE mode is ON
// 3. VerifyFwCapsule: FwCap RomImageOffset checked against max size 
//     (FWCAPSULE_IMAGE_SIZE-FLASH_SIZE)
// 
// 36    12/12/13 10:11a Alexp
// 
// 34    8/22/13 11:36a Alexp
// VerifyFwCertRsa2048Sha256() - Break a loop after RootCert Verify 
//  if key match is found. Old code would cycle through all root certs.
// 
// 33    8/12/13 4:35p Alexp
// 1. Add check for an end of Certificate block
// 2. Chnage Ignore_rollback behavior. Won't skip Project Tag check 
// 
// 32    7/11/13 3:39p Alexp
// Removed check for FWCAPSULE_MAX_HDR_SIZE. Replaced it with fixed 0x8000
// value
// 
// 31    6/28/13 12:01p Alexp
// restore logic to return FwCapsule file name as expected Recovery file
// name
// 
// 30    6/21/13 11:02a Alexp
// HashFwRomMapImage() - add check for 32bit address overflow
// 
// 29    6/12/13 3:48p Alexp
// VerifyFwCertRsa2048Sha256() - parse multiple chained RootKey 
//    certificate structures  in FwCert header
// 
// 28    5/01/13 6:16p Alexp
// VerifyFwImage() - ignore verification if no FwKey file is detected in
// FV_BB
// 
// 26    2/21/13 4:00p Alexp
// update IGNORE_IMAGE_ROLLBACK logic. 
// 
// 25    1/24/13 4:05p Alexp
// Made IGNORE_IMAGE_ROLLBACK depend on REFLASH_INTERACTIVE
// Disable revision rollback check if interactive flag is set
// 
// 24    12/17/12 2:45p Alexp
// fix cppcheck style check finds
// 
// 23    11/21/12 10:38a Alexp
// EIP#105015: Add support for Pkcs7# Certificates in Aptio Fw Capsule
// update packages
// 
// 22    11/20/12 3:32p Alexp
// EIP[104046]: Findings from Security review on Aptio4 Image verification
//  Includes the fix for item #10: hardening of RomMap parsing oin
// FwCapsule update
// 
// 21    11/13/12 3:29p Alexp
// 1. Calculate offset to RomLayout table within FwCapsHdr instead of
//  using hardwired location. Pkcs#7 cert may overlap fixed RomMap field
// 2. Remove dependency on FWSIG_SIGNHDR flag. Use Capsule flags instead.
// 
// 20    10/18/12 10:43a Alexp
// VerifyFwImage:
//  sanity check for buffer overruns. 
//  Applied for FwCapsules with Hdr on top of the Payload
// 
// 19    9/18/12 6:59p Alexp
// Bug: Recovery update was broken for FwCapsule with embedded signature
// and FwSig_hdr token 0.
// Fix: FindCapHdrFFS() change Ffs Hdr size testing
// 
// 18    7/26/12 3:26p Alexp
// replaced #if FWSIG_PADDING == 0  with #if FWSIG_SIGNHDR == 1. 
// Flag in the FwCap Hdr to switch between PKCS1_5 and PSS padding is
// available only if #if FWSIG_SIGNHDR == 1
// 
// 17    5/18/12 4:35p Alexp
// 1. Add support for Embedded FwSignature file
// 2. EIP:89687 Replace Hash PPI calls with calls to Crypto lib functions.
// Allows to support RomMap tables in FwCaps Hdr with unlimited number of
// entries
// 3. VerifyFwVersion. a)Moved the call after Rom image signature is
// verified.; b) search FID struct only in signed FVs with PEI or DXE
// attributes
// 
// 16    4/25/12 2:12p Alexp
// New logic extends search for matching Platform FW Key inside Signing
// and then RootKey
// certificates in the Cap Hdr
// 
// 14    3/09/12 11:16a Alexp
// VerifyFwImage-> fixed logic to process RomMap entries. 
// Number of signed elements in RomMap may not exceed max_num_elem
// constant. 
// Overall number of elements in th RomMap may not exceed max_num_elem x 2
// 
// 13    2/29/12 4:11p Alexp
// Update format of Capsule signiing:
// 1. Entire Cap Hdr and FW_Cert Hdr are included in SigCert Signature
// calculation. Improves Cap image security
// 2. RootKey signs only SignKey buffer and not entire Sign Certificate.
// No nee dfor resigning of RootCert each time SignCert is being created
// 
// 12    2/13/12 2:07p Alexp
// GetFidData: Use 1 byte alligned pointer in searching "Section Guid".
// Fixes the issue with RomMap entries that are not 4 byte alligned
// 
// 11    12/29/11 3:59p Alexp
// VerifyProjectId(). 
// Calculate size of ProjectId string based on SDL Token PROJECT_TAG
// 
// 10    11/30/11 8:02p Alexp
// FW Revision searched inside FID structure.
// Simplified the search throughout FW block by 4byte aligned $FID
// signature only
// 
// 9     11/08/11 3:08p Alexp
// match the name "FW"CAPSULE_FILE_NAME to one defined in SDL token
// 
// 8     11/03/11 6:39p Alexp
// restored FwCapsuleInfo()
// 
// 7     10/17/11 11:33a Alexp
// Replace old method to detect FlashUpd with single IsFlashUpdate() hook
// to be called from SbPei.c ->GetBootMode
// 
// 6     10/11/11 12:24p Alexp
// VerifyFwRevision(): removed unused input parameter: **PeiServices
// 
// 5     9/29/11 3:25p Alexp
// Bug fix. EIP#71244: No Rollback support
// 
// 4     9/20/11 2:25p Alexp
// change BootMode from Recovery to BOOT_ON_FLASH_UPDATE if FlUpdate is
// pending.
// 
// 3     8/05/11 3:19p Alexp
// add condition to skip Revision check. Ignore rollback protection
// 
// 2     7/20/11 7:16p Alexp
// remove dependency on Capsule module
// 
// 1     7/01/11 4:39p Alexp
// 
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: VerifyFwCapsule.c - PEI secured recovery services
//
// Description:   File contains VerifyFwCapsule hook to evaluate Fw Capsule
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include "Efi.h"
#include "Pei.h"
#include "token.h"
#include <AmiPeiLib.h>
#include <Hob.h>
#include <RomLayout.h>
#include <Ffs.h>
#include <Ppi\ReadOnlyVariable.h>
#include <FlashUpd.h>
#include <PPI\CryptoPPI.h>
#include <PPI\FwVersion.h>
#include <Protocol\Hash.h>
#include "AmiCertificate.h"
#include <BaseCryptLib.h>

//----------------------------------------------------------------------------
// Function Externs 

//----------------------------------------------------------------------------
// Local prototypes
EFI_STATUS
FwCapsuleInfo (
  IN EFI_PEI_SERVICES  **PeiServices,
  IN OUT VOID          **pCapsuleName,
  IN OUT UINTN         *pCapsuleSize,
  OUT   BOOLEAN        *ExtendedVerification
);

//----------------------------------------------------------------------------
typedef struct {
    EFI_FFS_FILE_HEADER FfsHdr;
    EFI_COMMON_SECTION_HEADER SecHdr;
    EFI_GUID            SectionGuid;
    UINT8               FwCapHdr[0];
} AMI_FFS_COMMON_SECTION_HEADER;

typedef struct _FID_SECTION {
    EFI_GUID   Guid;
    FW_VERSION FwVersion;
} FID_SECTION;

//----------------------------------------------------------------------------
// Local Variables
static EFI_GUID FwCapFfsGuid = AMI_FW_CAPSULE_FFS_GUID;
static EFI_GUID FwCapSectionGuid = AMI_FW_CAPSULE_SECTION_GUID;
static EFI_GUID FidSectionGuid = \
    { 0x2EBE0275, 0x6458, 0x4AF9, 0x91, 0xed, 0xD3, 0xF4, 0xED, 0xB1, 0x00, 0xAA };

const UINT8 *FidSignature = "$FID";

EFI_PEI_SERVICES  **gPeiServices;
static AMI_CRYPT_DIGITAL_SIGNATURE_PPI *gpAmiSigPPI=NULL;

//static EFI_GUID gAmiDigitalSignaturePPIGuid = AMI_DIGITAL_SIGNATURE_PPI_GUID;
static EFI_GUID gFWCapsuleGuid              = APTIO_FW_CAPSULE_GUID;
static EFI_GUID gEfiCertRsa2048Guid         = EFI_CERT_RSA2048_GUID;
static EFI_GUID gFWkeyGuid                  = PR_KEY_GUID;
static EFI_GUID gEfiHashAlgorithmSha256Guid = EFI_HASH_ALGORITHM_SHA256_GUID;
static EFI_GUID gEfiCertX509Guid            = EFI_CERT_X509;
static EFI_GUID gEfiCertTypePkcs7Guid       = EFI_CERT_TYPE_PKCS7_GUID;

static EFI_GUID gPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
static AMI_FLASH_UPDATE_BLOCK  gFlashUpdDesc;

//const char *RecoveryCapFileName = CONVERT_TO_STRING(FWCAPSULE_FILE_NAME);
const UINTN RecoveryCapImageSize = FWCAPSULE_IMAGE_SIZE;

static UINT8 gHashDB[SHA256_DIGEST_SIZE];
// Allocate Hash Descr table
static UINTN *gAddrList=NULL;
static UINTN *gLenList=NULL;
static UINTN gHashNumElem=0;

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
    IN FW_VERSION      *FwVersionData,
    IN OUT UINT32      *FailedVTask
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
    *FailedVTask = Ver;
// Project ID, Major, Minor rev
PEI_TRACE((-1, gPeiServices, "\nOrgBiosTag=%s,NewBiosTag=%s\nPrjMajVer=%02d, NewMajVer=%s\nPrjMinorVer=%02d, NewMinorVer=%s\n",
FwVersionData->BiosTag, strProjectId,
PROJECT_MAJOR_VERSION, FwVersionData->ProjectMajorVersion,
PROJECT_MINOR_VERSION, FwVersionData->ProjectMinorVersion
));
    if (Size==0 || MemCmp (FwVersionData->BiosTag, strProjectId, Size-1)) return FALSE;
#if IGNORE_IMAGE_ROLLBACK == 0
// Physically present user may override roll back protection from Setup screen
    if(Atoi(FwVersionData->ProjectMajorVersion) < PROJECT_MAJOR_VERSION ||
       Atoi(FwVersionData->ProjectMinorVersion) < PROJECT_MINOR_VERSION)
#if (defined(REFLASH_INTERACTIVE) && REFLASH_INTERACTIVE==1)
        return TRUE;
#else    
        return FALSE;
#endif   
#endif 

    *FailedVTask = 0;

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
    UINT8* SearchPointer;
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
    IN UINT8           *RomData,
    IN OUT UINT32      *FailedVTask
)    
{
    ROM_AREA                *Area;
    EFI_PHYSICAL_ADDRESS    FvAddress;
    FW_VERSION             *FwVersionData;

    *FailedVTask = Ver;

    Area = (ROM_AREA *)(UINTN)((UINT32)FWCapsuleHdr+FWCapsuleHdr->RomLayoutOffset);
    for (Area; Area->Size != 0; Area++) {
        if (!(Area->Attributes & ROM_AREA_FV_SIGNED)) 
            continue;
        //  $FID can be in FV with either PEI or DXE
        if (!(Area->Attributes & (ROM_AREA_FV_PEI+ROM_AREA_FV_DXE))) 
            continue;

        FvAddress = (EFI_PHYSICAL_ADDRESS)RomData + (Area->Offset);
        if (GetFidData((UINT8*)FvAddress, Area->Size, &FwVersionData)){
            if(VerifyProjectId(FwVersionData, FailedVTask))
                return EFI_SUCCESS;
            break;
        }
    } 
// At least one FW block must be signed OR no $FID structure found in the new FW image
    return EFI_SECURITY_VIOLATION;
}

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
    Signature = FwCapFfsGuid.Data1;

    do {
        if(*SearchPointer == Signature) {
            FileSection = (AMI_FFS_COMMON_SECTION_HEADER *)SearchPointer;
            if(!guidcmp(&FwCapFfsGuid, &(FileSection->FfsHdr.Name)) &&
               !guidcmp(&FwCapSectionGuid, &(FileSection->SectionGuid))
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

    UINTN    i, RomMap_size, max_num_elem, num_elem;

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
    max_num_elem=i;
    num_elem+=2; // add 2 extra entries

    if(!gAddrList || !gHashNumElem || gHashNumElem<num_elem) {
        gHashNumElem = num_elem;
        i = num_elem*sizeof(UINTN);
        Status = (*gPeiServices)->AllocatePool(gPeiServices, i*2, &gAddrList);
        ASSERT_PEI_ERROR (gPeiServices, Status);
        if(EFI_ERROR(Status)) return Status;
        gLenList = (UINTN*)((UINT8*)gAddrList + i);
    }
    num_elem = 0;
    for(i=0; i < max_num_elem && num_elem < gHashNumElem && RomAreaTbl[i].Size != 0; i++)
    {
        if (!(RomAreaTbl[i].Attributes & ROM_AREA_FV_SIGNED)) 
            continue;
    // sanity check for buffer overruns
        if(RomAreaTbl[i].Offset > RomSize ||
           (UINT64)RomAreaTbl[i].Offset + RomAreaTbl[i].Size > RomSize)
            return EFI_SECURITY_VIOLATION;
    // RomArea only holds offsets within a payload
        gAddrList[num_elem] = (UINTN)((UINTN)Payload + RomAreaTbl[i].Offset);
        gLenList[num_elem] = RomAreaTbl[i].Size;

        num_elem++;

    }
    if(num_elem >= gHashNumElem) return EFI_SECURITY_VIOLATION;
//
//  Hash of Capsule Hdr + FW Certificate Hdr
//
    if(FWCapsuleHdr->CapHdr.Flags & CAPSULE_FLAGS_CAPHDR_IN_SIGNCERT) {
        gAddrList[num_elem] = (UINTN) FWCapsuleHdr;
        gLenList[num_elem] = (UINTN)&FWCapsuleHdr->FWCert.SignCert.CertData - (UINTN)FWCapsuleHdr;
        num_elem++;
        if(num_elem >= gHashNumElem) return EFI_SECURITY_VIOLATION;
    }
//
//  Hash of the ROM_MAP table
//
    gAddrList[num_elem] = (UINTN)RomAreaTbl;
    gLenList[num_elem] = (i+1)*sizeof(ROM_AREA);
    num_elem++;

    Status = gpAmiSigPPI->Hash(gpAmiSigPPI, &gEfiHashAlgorithmSha256Guid, 
                num_elem, (const UINT8**)gAddrList,  (const UINTN*)gLenList, gHashDB );

//    PEI_TRACE((-1, gPeiServices, "Hash the FW Image %r\n", Status));

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
    IN UINTN                     RomSize,
    IN PEI_CRYPT_HANDLE         *PubKeyHndl,
    IN OUT UINT32               *FailedVTask
){
    EFI_STATUS              Status;
    UINT8                  *Pkcs7Cert, *pDigest;
    UINTN                   Pkcs7Cert_len, DigestLen;

//
// 1. Validate Root Key
//
    *FailedVTask = Key;

    if( PubKeyHndl->Blob==NULL)
        return EFI_SECURITY_VIOLATION; 

    if(guidcmp(&PubKeyHndl->AlgGuid, &gEfiCertX509Guid))
        return EFI_UNSUPPORTED;

// 2. Verify Signing Cert Signature
//
// 2.1 The Rom image hash is calculated based on info from the Rom Area map
//
    *FailedVTask = Sig;

    Status = HashFwRomMapImage(FWCapsuleHdr, Payload, RomSize, gHashDB);
    if (EFI_ERROR(Status)) return Status;

// 2.2 Verify Fw Certificate
    pDigest = &gHashDB[0];
    DigestLen = SHA256_DIGEST_SIZE;
    Pkcs7Cert = (UINT8*)&FWCapsuleHdr->FWCert.SignCert.CertData; 
    Pkcs7Cert_len = FWCapsuleHdr->FWCert.SignCert.Hdr.Hdr.dwLength-sizeof(WIN_CERTIFICATE_UEFI_GUID_1);

    return gpAmiSigPPI->VerifyPkcs7Sig( gpAmiSigPPI,
                     Pkcs7Cert, Pkcs7Cert_len,           // Pkcs7Cert
                     PubKeyHndl->Blob, PubKeyHndl->BlobSize, // TrustCert
                     &pDigest, &DigestLen               // In/OutData
                     );
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
    IN UINTN                     RomSize,
    IN OUT UINT32               *FailedVTask
){
    EFI_STATUS              Status;
    PEI_CRYPT_HANDLE        HashHndl;
    PEI_CRYPT_HANDLE        PubKeyHndl;
    UINT8                   *pSig;
    UINT32                  Flags=0;
    UINT8                   *Addr;
    UINTN                   Size;
    EFI_CERT_BLOCK_RSA_2048_SHA256* pRootCert;

// Versions 010 and later support extended flags
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

    HashHndl.AlgGuid  = gEfiHashAlgorithmSha256Guid;
    HashHndl.BlobSize = SHA256_DIGEST_SIZE;
    HashHndl.Blob = (UINT8*)&gHashDB;
//
// 1. Compare Capsule's Sign Cert key with Platform Root Key
//
    *FailedVTask = Key;

    PubKeyHndl.BlobSize =  DEFAULT_RSA_KEY_MODULUS_LEN;
    PubKeyHndl.AlgGuid = gEfiCertRsa2048Guid;
    PubKeyHndl.Blob = (UINT8*)FWCapsuleHdr->FWCert.SignCert.CertData.PublicKey;
    Status = gpAmiSigPPI->VerifyKey(gpAmiSigPPI, &gFWkeyGuid, &PubKeyHndl); 
    PEI_TRACE((-1, gPeiServices, "Compare Platform and SignCert Keys : %r\n", Status));
//  Skip the RootCert key checking if SignCert Key and PR Key are matching
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
            PubKeyHndl.Blob = (UINT8*)pRootCert->PublicKey;
            Status = gpAmiSigPPI->VerifyKey(gpAmiSigPPI, &gFWkeyGuid, &PubKeyHndl); 
            PEI_TRACE((-1, gPeiServices, "Compare Platform and RootCert Keys : %r\n", Status));
            if (EFI_ERROR(Status)) continue;        
    
    // 2. Verify RootCert.Signature
    //
    // 2.1  Compute FWCert.SignCert.PublicKey Hash
    // 
            if(FWCapsuleHdr->CapHdr.Flags & CAPSULE_FLAGS_SIGNKEY_IN_ROOTCERT)
            {
                Addr = (UINT8*)FWCapsuleHdr->FWCert.SignCert.CertData.PublicKey;
                Size = DEFAULT_RSA_KEY_MODULUS_LEN;
            } else
    // 2.2  Compute FWCert.SignCert Hash
            {
                Addr = (UINT8*)&FWCapsuleHdr->FWCert.SignCert;
                Size = sizeof(AMI_CERTIFICATE_RSA2048_SHA256);
            }
    
            Status = gpAmiSigPPI->Hash(gpAmiSigPPI,&gEfiHashAlgorithmSha256Guid, 1,&Addr,(const UINTN*)&Size, gHashDB); 
            if (EFI_ERROR(Status)) break;
        
            pSig = (void*)pRootCert->Signature; 
            Status = gpAmiSigPPI->VerifySig(gpAmiSigPPI, &PubKeyHndl, &HashHndl, pSig, DEFAULT_RSA_SIG_LEN, Flags ); 
            PEI_TRACE((-1, gPeiServices, "Verify Root Cert : %r\n", Status));
            break;      
        }
    }
    if (EFI_ERROR(Status)) return EFI_SECURITY_VIOLATION;
//
// 3. Verify Signing Cert
//
    *FailedVTask = Sig;
//
// 3.1 The Rom image hash is calculated based on info from the Rom Area map
//
    Status = HashFwRomMapImage(FWCapsuleHdr, Payload, RomSize, gHashDB);
    if (EFI_ERROR(Status)) return Status;

    pSig = (void*)FWCapsuleHdr->FWCert.SignCert.CertData.Signature; 
    PubKeyHndl.Blob = (UINT8*)FWCapsuleHdr->FWCert.SignCert.CertData.PublicKey;

    return gpAmiSigPPI->VerifySig(gpAmiSigPPI, &PubKeyHndl, &HashHndl, pSig, DEFAULT_RSA_SIG_LEN, Flags); 
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  VerifyFwImage
//
// Description:    Function verifies various sections of the FW Capsule 
//
// 0. Locate protocol AMI_CRYPT_DIGITAL_SIGNATURE_PPI
// 1. Check if FV GUID matches Aptio FW Capsule. 
//         - Yes - 
//          update Payload ptr to beginning of BIOS ROM data
//            continue with Image Varify
//         - Not found at offs 0 - assume Cap Hdr is in FFS
//          locate FFS by Hole GUID, Sec GUID
//          update FWCapsuleHdr ptr,
//            continue with Image Varify
// 2. Validate  Root Certificate 
//    -Compare PubKey in Root Certificate Hdr with local FW Platform Key
//    -Hash SignCert.PubKey 
//    -VerifySig for RootCert.Signature and compare with SignCert.Key hash
// 3. Validate  Sign Certificate 
//    -Hash the ROM image inside the FW Capsule
//    -VerifySig for SignCert.Signature and compare with ROM hash
// 4. Update pCapsuleSize = FwPayload and set pCapsule to point to FW Payload
//
//  Input:
//    PeiServices   Pointer to PeiServices instance.
//    pCapsule      Points to the start of the Aptio FW Capsule.
//    pCapsuleSize  The size of buffer, in bytes.
//    FailedVTask   Specifies additional flags to further customize the signing/verifying behavior.
//
// Output:
//    pCapsule      ptr is set to start of Capsule's Payload - ROM image
//    pCapsuleSize  return ROM image size
//    EFI_SUCCESS               The signature is successfully verified.
//    EFI_SECURITY_VIOLATION    The signature does not match the given message.
//    EFI_ACCESS_DENIED         The key could not be used in signature operation.
//    EFI_INVALID_PARAMETER     The size of input message or signature does not meet the criteria 
//                              of the underlying signature algorithm.
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
VerifyFwImage(
  IN EFI_PEI_SERVICES  **PeiServices,
  IN OUT VOID          **pCapsule,
  IN OUT UINT32         *pCapsuleSize,
  IN OUT UINT32         *FailedVTask
){
    EFI_STATUS              Status;
    APTIO_FW_CAPSULE_HEADER  *FWCapsuleHdr;
    UINT8                   *Payload;
    UINTN                   RomSize;
    PEI_CRYPT_HANDLE        PubKeyHndl;
    UINT8                   Byte;
    UINTN                   Size;

    gPeiServices = PeiServices; 

    PEI_TRACE((-1, PeiServices, "\nValidate FW Capsule ...\n"));

// Predefined bit mask of checks to perform on Aptio FW Capsule
    *FailedVTask = Cap;

    Status = (*PeiServices)->LocatePpi(PeiServices, &gAmiDigitalSignaturePPIGuid, 0, NULL, &gpAmiSigPPI);
    if(EFI_ERROR(Status)) return Status;

    // ignore Verification if FwKey is not detected in the FW.
    // Works with unsigned Aptio.ROM image or Signed ROM with embedded sig.
    PubKeyHndl.BlobSize =  0;
    PubKeyHndl.Blob = NULL;
    Status = gpAmiSigPPI->GetKey(gpAmiSigPPI, &gFWkeyGuid, &PubKeyHndl);
    PEI_TRACE((-1, PeiServices, "Get Root Cert Key (%r),0x%8X (%d bytes)\n", Status, (*(UINT32*)PubKeyHndl.Blob), PubKeyHndl.BlobSize));
    if(EFI_ERROR(Status)) 
    {
#if (defined(REFLASH_INTERACTIVE) && REFLASH_INTERACTIVE==1)
        if(Status == EFI_NOT_FOUND)
            return EFI_SUCCESS;
#endif            
        *FailedVTask = Key;
        return Status;
    }

    FWCapsuleHdr = *pCapsule;
    Payload = (UINT8*)*pCapsule;
    RomSize = (UINTN)*pCapsuleSize;

// verify Capsule Mailbox points to FW_CAPSULE hdr
    if(guidcmp((EFI_GUID*)&FWCapsuleHdr->CapHdr.CapsuleGuid, &gFWCapsuleGuid))
    {
// looking FwCap hdr inside BIOS.ROM
        if(EFI_ERROR(FindCapHdrFFS(Payload, (UINT8**)&FWCapsuleHdr)))
            return EFI_SECURITY_VIOLATION;
    }
    PEI_TRACE((-1, PeiServices, "FW Capsule Hdr Detected...\n"));

// Aptio FW Capsule only supporting WIN_CERT_TYPE_EFI_GUID 
    if(FWCapsuleHdr->FWCert.SignCert.Hdr.Hdr.wCertificateType != WIN_CERT_TYPE_EFI_GUID)
            return EFI_SECURITY_VIOLATION;

// Applied for FwCapsules with Hdr on top of the Payload
    if( (UINT8*)*pCapsule ==(UINT8*) FWCapsuleHdr) {
        if(FWCapsuleHdr->CapHdr.CapsuleImageSize > *pCapsuleSize)
            return EFI_SECURITY_VIOLATION;
        // Update pFwCapsule to point to beginning of Bios ROM
        Payload = (UINT8*)((UINT32)FWCapsuleHdr + FWCapsuleHdr->RomImageOffset);
        RomSize = (FWCapsuleHdr->CapHdr.CapsuleImageSize - FWCapsuleHdr->RomImageOffset);
    }

// Capsule Hdr sanity checks
    if((RomSize > *pCapsuleSize) ||
       (FWCapsuleHdr->RomImageOffset > (FWCAPSULE_IMAGE_SIZE-FLASH_SIZE)) || // 16k is a MAX possible FwCap Hdr size
       (FWCapsuleHdr->CapHdr.HeaderSize > FWCapsuleHdr->RomImageOffset) ||
       (FWCapsuleHdr->RomLayoutOffset > FWCapsuleHdr->RomImageOffset) ||
       (FWCapsuleHdr->FWCert.SignCert.Hdr.Hdr.dwLength + offsetof(APTIO_FW_CAPSULE_HEADER, FWCert) > 
        FWCapsuleHdr->RomLayoutOffset )
    )
        return EFI_SECURITY_VIOLATION;

    // If dummy FWkey - skip integrity check - only test the Capsule's structure 
    Byte = PubKeyHndl.Blob[0];
    for(Size = 1; Size < PubKeyHndl.BlobSize && (Byte == PubKeyHndl.Blob[Size]); Size++);
    if(Size == PubKeyHndl.BlobSize) {
        *FailedVTask = Key;
        PEI_TRACE((-1, PeiServices, "Dummy FW Key detected. Skip image verification...\n"));
    } else 
    {
// Begin Authentication
        if(!guidcmp((EFI_GUID*)&FWCapsuleHdr->FWCert.SignCert.Hdr.CertType, &gEfiCertTypePkcs7Guid))
            Status = VerifyFwCertPkcs7(FWCapsuleHdr, Payload, RomSize, &PubKeyHndl, FailedVTask);
        else
            Status = VerifyFwCertRsa2048Sha256(FWCapsuleHdr, Payload, RomSize, FailedVTask);

        PEI_TRACE((-1, gPeiServices, "Verify Sign Certificate Sig : %r\n", Status));
        if (EFI_ERROR(Status)) return Status;

        *FailedVTask = 0;

// Local PEI $FID is linked with CspLib. extern FW_VERSION   FwVersionData;
// Find $FID in new Fw FVs. Any instance found should do for us. Use RomMap from Capsule's Hdr
// compare local BB and Main $Fid BIOS Major/Minor revs with New one.
        Status = VerifyFwRevision(FWCapsuleHdr, Payload, FailedVTask);
        PEI_TRACE((-1, PeiServices, "FW Revision test %r (FailedVTask = %x)\n", Status, *FailedVTask));
    }

    *pCapsule = (UINT32*)Payload;
    *pCapsuleSize = RomSize;

    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    FwCapsuleInfo
//
// Description:  Updates the Recovery File name and size if defaults are 
//               overriden in FlashUpd EFI Var.
//               Called from Recovery LoadRecoveryCapsule.
//
//    pCapsuleName  Pointer to the variable containing a Recovery File name
//    pCapsuleSize  Pointer to the size of recovery image capsule, in bytes.
//    ExtendedVerification Indicates to Recovery module whether Fw Capsule 
//                  Recovery path will perform image size check.
//
// Output:
//    EFI_SUCCESS 
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS
FwCapsuleInfo (
  IN EFI_PEI_SERVICES  **PeiServices,
  IN OUT VOID          **pCapsuleName,
  IN OUT UINTN         *pCapsuleSize,
  OUT   BOOLEAN        *ExtendedVerification
){
    EFI_STATUS          Status;
    UINTN               Size;
    EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable = NULL;
    EFI_GUID            FlashUpdGuid = FLASH_UPDATE_GUID;

    if(!pCapsuleName && !pCapsuleSize && !ExtendedVerification )
        return EFI_UNSUPPORTED;

    if(ExtendedVerification != NULL)
        *ExtendedVerification = TRUE;

    if(pCapsuleSize != NULL) 
    {
        *pCapsuleSize = RecoveryCapImageSize;

        if(pCapsuleName != NULL) 
        {
// EIP149817: don't override a default recovery file name
//          *pCapsuleName = (VOID*)RecoveryCapFileName;

        // Detect if we are in Flash Update mode and set some recovery global variables
        // Read "FlashOp" Variable to update global RecoveryFileName, Size
            Status = (*PeiServices)->LocatePpi( PeiServices,
                                        &gPeiReadOnlyVariablePpiGuid,
                                        0,
                                        NULL,
                                        &ReadOnlyVariable );
        //    ASSERT_PEI_ERROR (PeiServices, Status);
           if(EFI_ERROR(Status))
               return Status;
        
            Size = sizeof(AMI_FLASH_UPDATE_BLOCK);
            Status = ReadOnlyVariable->GetVariable( PeiServices,
                                        FLASH_UPDATE_VAR,
                                        &FlashUpdGuid,
                                        NULL,
                                        &Size,
                                        &gFlashUpdDesc );
            if(!EFI_ERROR(Status))
            {
                if(gFlashUpdDesc.FlashOpType == FlRecovery && gFlashUpdDesc.FwImage.AmiRomFileName[0] != 0)
                    *pCapsuleName = (VOID*)gFlashUpdDesc.FwImage.AmiRomFileName;

                *pCapsuleSize = gFlashUpdDesc.ImageSize;
                Status = (*PeiServices)->SetBootMode(PeiServices, BOOT_ON_FLASH_UPDATE);
            }
            PEI_TRACE((-1, PeiServices, "FW Capsule update %r\nImage Name %s, Size %x\n", Status, *pCapsuleName, *pCapsuleSize));
        }
    } 
    return EFI_SUCCESS;
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
