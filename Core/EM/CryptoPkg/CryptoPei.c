//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Modules/CryptoPkg/CryptoPei.c 15    8/01/13 6:27p Alexp $
//
// $Revision: 15 $
//
// $Date: 8/01/13 6:27p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/CryptoPkg/CryptoPei.c $
// 
// 15    8/01/13 6:27p Alexp
// Comment out a check for FwKey location to be mapped to Flash FV_BB
// In some cases FindFFS for FwKey may return a location outside of Flash
// space. 
// Will have the logic fixed in the next label.
// 
// 14    7/01/13 5:24p Alexp
// CryptoPei_Init(): fix addr typecasting for pFwKeyHob->KeyAddress
// 
// 13    6/20/13 1:55p Alexp
// Impove FwKey handling. CryptoPEI pass FwKey location to Dxe via Hob
// Add mor parameter checking including 
//  check for FwKey location to be mapped to Flash FV_BB
// 
// 12    5/23/13 12:04p Alexp
// Add dependency on PKCS7_PEI_Support switch to turn off Pkcs7 support in
// CryptoPEI. Saves ~8kb of space
// 
// 11    12/28/12 3:05p Alexp
// CryptoGetRawImage(): calculate raw Key size inside FwKey ffs file
// 
// 10    12/19/12 10:31a Alexp
// code modify to meet "cppcheck" style & performance suggestions
// 
// 8     11/15/12 9:28a Alexp
// update Pkcs7Verify help header
// 
// 7     11/14/12 6:28p Alexp
// rename ppPS to gPeiServices in order to keep backward compatibility for
// older Secure Flash eModules
// 
// 6     11/13/12 11:50a Alexp
// EIP#105015: Add Pkcs#7 Cert Verification function in Crypto PPI
// Add handling of x509 formatted FW Key in FFS files
// 
// 5     7/25/12 10:00a Alexp
// cleaned comments in Hash Hdr
// 
// 4     3/12/12 4:11p Alexp
// do not install Crypto PPI on S3 resume.
// 
// 3     3/02/12 10:43a Alexp
// Remove dependency on SDL Token FWKEY_FORMAT to determine format of PR
// Key file
// Try different Ffs GUIDs to select proper Key format: SHA or RSA
// 
// 2     2/29/12 4:01p Alexp
// 1. Use SDL Token FWKEY_FORMAT to define format of PR Key file: Hash or
// RSA2048
// 2. Modify VerifyKey to account for PR Key in SHA256 format
// 
// 1     6/13/11 5:19p Alexp
// 
// 1     5/06/11 6:11p Alexp
// initial module release
// 
// 10    4/22/11 4:19p Alexp
// fix GetRaw file
// 
// 9     4/18/11 7:09p Alexp
// 
// 8     4/11/11 12:53p Alexp
// remove Verify Capsule from Crypto PPI. Function moved to SecRecovery.c
// 
// 7     4/08/11 1:33p Alexp
// This revision Supports single PK(FwSign) Ffs file with SigDb with
// multiple Keys
// 
// 6     4/05/11 6:31p Alexp
// 
// 5     3/21/11 6:58p Alexp
// 
// 4     3/15/11 12:48p Alexp
// 
// 3     3/14/11 3:26p Alexp
// add provision to handle multiple Platform Signing keys.
// rom may containg multiple Keys as FFS files with same Guid
// 
// 2     3/11/11 6:51p Alexp
// 
// 1     3/10/11 4:52p Alexp
// 
// 2     2/28/11 6:46p Alexp
// 
// 1     2/18/11 5:42p Alexp
// 
//**********************************************************************
#include <Token.h>
#include <AmiPeiLib.h>
#include "PPI\LoadFile.h"
#include <Protocol\Hash.h>
#include <PPI\CryptoPPI.h>
#include "AmiCertificate.h"

#include <cryptlib.h>

//
// Global variables
//

// Although ShaXXXGuid global variables are defined in EDK's EdkProtocol Lib, but linking it adds additional 20k in debug mode.
static EFI_GUID gEfiHashAlgorithmSha1Guid   = EFI_HASH_ALGORITHM_SHA1_GUID;
static EFI_GUID gEfiHashAlgorithmSha256Guid = EFI_HASH_ALGORITHM_SHA256_GUID;
static EFI_GUID gPKeyGuid                   = PR_KEY_GUID;

// Hardwired at Build time. Supported formats: RSA2048, HASH256 Key Certs
static EFI_GUID gPKeyFileRsa2048Guid = PR_KEY_FFS_FILE_RAW_GUID; 
static EFI_GUID gPKeyFileSha256Guid = PR_KEY_FFS_FILE_SHA256_GUID;
static EFI_GUID gPKeyFileX509Guid = PR_KEY_FFS_FILE_X509_GUID;

static EFI_GUID gEfiCertSha256Guid = EFI_CERT_SHA256_GUID;
static EFI_GUID gEfiCertRsa2048Guid = EFI_CERT_RSA2048_GUID;
static EFI_GUID gEfiCertX509Guid = EFI_CERT_X509;

static EFI_GUID *gKeyFileGuid [] = {
    &gPKeyFileX509Guid,
    &gPKeyFileRsa2048Guid,
    &gPKeyFileSha256Guid,
    NULL
};
static EFI_GUID *gKeyTypeGuid [] = {
    &gEfiCertX509Guid,
    &gEfiCertRsa2048Guid,
    &gEfiCertSha256Guid,
    NULL
};

EFI_PEI_SERVICES  **gPeiServices;
FW_KEY_HOB         *pFwKeyHob = NULL;
//
// SDL defined Public Exponent E of RSA Key.
//
const UINT8  KeyE[] = {E_CONST}; // 0x10001
const UINT32 LenE = sizeof(KeyE);
//    PKCS_1 PSS Signature constatnt. Size of the Salt (random data) field in PSS signature.
const INT32  saltlen = PSS_SIG_SALTLEN; // 8 
static UINT8 DecriptedSig[DEFAULT_RSA_SIG_LEN];
//----------------------------------------------------------------------------
// Crypto Function prototypes
//----------------------------------------------------------------------------
EFI_STATUS
PeiHash (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI      *This,
  IN CONST EFI_GUID               *HashAlgorithm,
  IN UINTN                        num_elem,
  IN CONST UINT8                  *addr[],
  IN CONST UINTN                  *len,
  OUT UINT8                       *Hash
  );

EFI_STATUS
PeiPkcs7Verify (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN CONST UINT8 *P7Data,
  IN UINTN        P7Size,
  IN CONST UINT8 *TrustedCert,
  IN UINTN        CertSize,
  IN OUT UINT8  **Data,
  IN OUT UINTN   *DataSize
  );

EFI_STATUS
PeiVerifySig 
(
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN PEI_CRYPT_HANDLE          *PublicKey,
  IN PEI_CRYPT_HANDLE          *Hash,
  IN VOID                      *Signature,
  IN UINTN                     SignatureSize,
  IN UINT32                    Flags
);

EFI_STATUS
PeiGetKey 
(
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN CONST EFI_GUID            *KeyAlgorithm, // reserved to PKPUB_KEY_GUID
  IN PEI_CRYPT_HANDLE          *PublicKey
  );

EFI_STATUS
PeiVerifyKey 
(
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN CONST EFI_GUID            *KeyAlgorithm, // reserved to PKPUB_KEY_GUID
  IN PEI_CRYPT_HANDLE          *PublicKey
  );

//----------------------------------------------------------------------------
// Crypto Protocol Identifiers
//----------------------------------------------------------------------------
static EFI_GUID gAmiDigitalSignaturePPIGuid = AMI_DIGITAL_SIGNATURE_PPI_GUID;

AMI_CRYPT_DIGITAL_SIGNATURE_PPI  mSigPeiInitPpi = {
  PeiHash,
  PeiVerifyKey,
  PeiVerifySig,
  PeiGetKey,
  PeiPkcs7Verify
};

//static 
EFI_PEI_PPI_DESCRIPTOR mPpiSigListVariable = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmiDigitalSignaturePPIGuid,
  &mSigPeiInitPpi
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  CryptoGetRawImage
//
// Description:    Loads binary from RAW section of X firwmare volume
//
//
// Output:          Buffer - returns a pointer to allocated memory. Caller
//                          must free it when done.
//                  Size  - returns the size of the binary loaded into the
//                          buffer.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
CryptoGetRawImage (IN EFI_GUID *FileGuid, IN OUT VOID **Buffer, IN OUT UINTN *Size)
{
  EFI_STATUS                    Status;
  EFI_FIRMWARE_VOLUME_HEADER    *pFV;
  UINTN                         FvNum=0;
  EFI_FFS_FILE_HEADER           *ppFile=NULL;
    
  if (!Buffer || !Size)
    return EFI_INVALID_PARAMETER;

  Status = (*gPeiServices)->FfsFindNextVolume (gPeiServices, FvNum, &pFV);
  
  while(TRUE)
    {
      Status = (*gPeiServices)->FfsFindNextFile(gPeiServices, EFI_FV_FILETYPE_ALL, pFV, &ppFile);
      if(Status == EFI_NOT_FOUND)
       {
//         FvNum++;
//         Status = (*gPeiServices)->FfsFindNextVolume (gPeiServices, FvNum, &pFV);
//         if(EFI_ERROR(Status)) return Status;
//         continue;
// !!! the PK Key may only be in FV_BB volume. FvNum=0!!!!
           return Status;
       }

      if(guidcmp(&ppFile->Name, FileGuid)==0) break;
    }

  // hopefully we found the file...now try to read raw data
  // !!! Keys are uncompressed. There is no much reason to run compression on prime numbers anyway
  Status = (*gPeiServices)->FfsFindSectionData(gPeiServices, EFI_SECTION_RAW, ppFile, Buffer);
  if(!EFI_ERROR(Status)) {
    // Size may need to subtract Section hdr size = 28 bytes sizeof(EFI_FFS_FILE_HEADER + EFI_COMMON_SECTION_HEADER)
    *Size = FVFILE_SIZE(ppFile)-sizeof(EFI_FFS_FILE_HEADER)-sizeof(EFI_COMMON_SECTION_HEADER);
  }
PEI_TRACE(((UINTN)TRACE_ALWAYS, gPeiServices, "Find Key Ffs %r addr=%X (%X,%X), size=%d\n", Status, (UINT32)*Buffer, ((UINT8*)*Buffer)[0], ((UINT8*)*Buffer)[1], *Size));

  return Status;  
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  PeiHash
//
// Description:    Allows creating a hash of an arbitrary message digest using one or more hash algorithms
//
// Input:
//      This          Pointer to the AMI_CRYPT_DIGITAL_SIGNATURE_PPI instance.
//      HashAlgorithm Points to the EFI_GUID which identifies the algorithm to use.
//      num_elem      Number of blocks to be passed via next argument:addr[]
//      addr[]        Pointer to array of UINT8* addresses of data blocks to be hashed
//      len           Pointer to array of integers containing length of each block listed by addr[]
//      Hash          Holds the resulting hash computed from the message.
//
// Output:    
//      EFI_SUCCESS           Hash returned successfully.
//      EFI_INVALID_PARAMETER Message or Hash is NULL
//      EFI_UNSUPPORTED       The algorithm specified by HashAlgorithm is not supported by this
//                            driver.
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
PeiHash (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI      *This,
  IN CONST EFI_GUID               *HashAlgorithm,
  IN UINTN                        num_elem,
  IN CONST UINT8                  *addr[],
  IN CONST UINTN                  *len,
  OUT UINT8                       *Hash
  )
{
    BOOLEAN     bSha1 = FALSE, bSha256 = FALSE;
    UINT32      HashLen=SHA256_DIGEST_SIZE;

// Support only SHA1 & SHA256 hashes
    if(!guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha1Guid))
    {
        bSha1 = TRUE;
        HashLen = SHA1_DIGEST_SIZE;
    }
    else 
        if(!guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha256Guid))
        {
            bSha256 = TRUE;
            HashLen = SHA256_DIGEST_SIZE;
        }
         else
            return EFI_UNSUPPORTED;

    MemSet(Hash, HashLen, 0);
    if(bSha1)
        sha1_vector(num_elem, addr, len, Hash);
    else
        sha256_vector(num_elem, addr, len, Hash);


    return  EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  PeiVerifySig
//
// Description:    Function verifies that the specified signature matches the specified hash. 
//    This function decrypts the signature with the provided key and then compares 
//    the decrypted value to the specified hash value
//
//  Input:
//    This          Pointer to the AMI_CRYPT_DIGITAL_SIGNATURE_PPI instance.
//    PublicKey     Handle to a key used for verifying signatures. This handle must be identifying a public key.
//    Hash          Handle of the hash object to verify.
//    Signature     Pointer to the signature data to be verified.
//    SignatureSize The size, in bytes, of the signature data.
//    Flags         Specifies additional flags to further customize the signing/verifying behavior.
//
// Output:    
//    EFI_SUCCESS               The signature is successfully verified.
//    EFI_SECURITY_VIOLATION    The signature does not match the given message.
//    EFI_ACCESS_DENIED         The key could not be used in signature operation.
//    EFI_INVALID_PARAMETER     The size of input message or signature does not meet the criteria 
//                              of the underlying signature algorithm.
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
PeiVerifySig 
(
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI      *This,
  IN PEI_CRYPT_HANDLE            *PublicKey,
  IN PEI_CRYPT_HANDLE            *Hash,
  IN VOID                        *Signature,
  IN UINTN                       SignatureSize,
  IN UINT32                      Flags
  )
{
    EFI_STATUS      Status;
    INTN            err;
    struct          crypto_rsa_key *key = NULL;
    UINT16          Size = (UINT16)(PublicKey->BlobSize);
    size_t         *sig_len=(size_t*)&SignatureSize;
    INT32           modulus_bitlen = DEFAULT_RSA_SIG_LEN << 3;
    UINT32          HashLen;

// Only supporting RSASSA_PKCS1V15 signature types
    if(!((Flags & EFI_CRYPT_RSASSA_PKCS1V15) || 
         (Flags & EFI_CRYPT_RSASSA_PSS)) )
            return EFI_INVALID_PARAMETER;

    ResetCRmm();

// check Key handle if requested PubKey is a Platform FW Key
// In this case use the FW key from ffs image
// validity of the Key must be verified prior to calling VerifySig
// Guid must match one of the valid keys we can use in PEI Sig verification.
// For now Public Key is supported in 2 formats: RAW 256 bytes and ASN.1 Integer
// shall be extended to gPBkey_x509_Guid
    if(!guidcmp(&PublicKey->AlgGuid, &gEfiCertRsa2048Guid))
        key = crypto_import_rsa2048_public_key(PublicKey->Blob, Size, (UINT8*)&KeyE, LenE);
    else
        return EFI_INVALID_PARAMETER;

    if(!guidcmp(&Hash->AlgGuid, &gEfiHashAlgorithmSha256Guid))
        HashLen = SHA256_DIGEST_SIZE;
    else if(!guidcmp(&Hash->AlgGuid, &gEfiHashAlgorithmSha1Guid))
            HashLen = SHA1_DIGEST_SIZE;
        else
            HashLen = SHA256_DIGEST_SIZE;

    if(key == NULL )
        err = -1;
    else
        err = crypto_rsa_exptmod((const UINT8*)Signature, (size_t)SignatureSize, (UINT8*)&DecriptedSig, sig_len, key, 0);
// locate Hash inside the decrypted signature body and compare it with given Hash;
// Should be extended to handle sha1, sha256 hashes. use Hash->AlgGuid to determine the Hash type
    if(!err) 
    {
        if(Flags & EFI_CRYPT_RSASSA_PKCS1V15)
        {
            // Validate PKCS#1v1.5 Padding
//            err = pkcs_1_v1_5_decode(Hash->Blob, HashLen, (const UINT8 *)&DecriptedSig, (unsigned long)*sig_len);
// just compare the hash at the end of the sig blob
            err = MemCmp(Hash->Blob, (void*)((UINT32)DecriptedSig + (UINT32)(*sig_len - HashLen)), HashLen);
        } else //(Flags & EFI_CRYPT_RSASSA_PSS))
            // Validate PKCS#1 PSS Signature: padding & hash
            err = pkcs_1_pss_decode(
                    Hash->Blob, HashLen, 
                    (const unsigned char *)&DecriptedSig, (unsigned long)*sig_len, 
                    saltlen,  modulus_bitlen);
    }

    Status = !err ? EFI_SUCCESS:EFI_SECURITY_VIOLATION;

// Security concern, memory heap is being cleared on exit 
    ResetCRmm();

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  PeiPkcs7Verify
//
// Description:    Verifies the validity of a PKCS#7 signed data as described in "PKCS #7: Cryptographic
//                 Message Syntax Standard".
//                 Function verifies validity of the signature contained inside the Certificate
//                 This function decrypts the signature with the Public key from the Signer certificate 
//                 and then compares the decrypted value to the input Data
//
//  Input:
//      This         Pointer to the AMI_CRYPT_DIGITAL_SIGNATURE_PPI instance.
//      P7Data       Pointer to the PKCS#7 DER encoded message to verify.
//      P7Size       Size of the PKCS#7 message in bytes.
//      TrustedCert  Pointer to a trusted/root X509 certificate encoded in DER, which
//                   is used for certificate chain verification.
//      CertSize     Size of the trusted certificate in bytes.
//      Data         Pointer to the content to be verified/returned at
//      DataSize     Size of Data in bytes
//
// Output:    
//    EFI_SUCCESS              The specified PKCS#7 signed data is valid
//    EFI_SECURITY_VIOLATION   Invalid PKCS#7 signed data.
//    EFI_ACCESS_DENIED        The Trusted certificate does not have a match in SignedData.certificate store.
//    EFI_INVALID_PARAMETER    The size of input message or signature does not meet the criteria 
//                             of the underlying signature algorithm.
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
PeiPkcs7Verify (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN CONST UINT8 *P7Data,
  IN UINTN        P7Size,
  IN CONST UINT8 *TrustedCert,
  IN UINTN        CertSize,
  IN OUT UINT8  **Data,
  IN OUT UINTN   *DataSize
  )
{
#if CONFIG_PEI_PKCS7 == 1

    EFI_STATUS  Status;
    INTN        err, reason;
    struct pkcs7_signed_data_st* PKCS7cert;
    struct x509_certificate *x509TrustCert;
    struct x509_certificate *x509SignCert;

    err     = -1;
    reason  = 0;
    x509SignCert = NULL;

    if((*Data == NULL || DataSize == NULL) ||
       (!P7Data || P7Size== 0) || 
       (!TrustedCert || CertSize== 0)
    ) 
        return EFI_INVALID_PARAMETER;

    ResetCRmm();

    PKCS7cert = Pkcs7_parse_Authenticode_certificate(P7Data, P7Size);
    if (PKCS7cert) {
        // verify Pkcs7 Signing Cert chain up to the TrustCert...
        x509TrustCert = x509_certificate_parse(TrustedCert, CertSize);
        if(x509TrustCert) {
            err = Pkcs7_x509_certificate_chain_validate(PKCS7cert, x509TrustCert, (int*)&reason);
            if(!err)
                err = Pkcs7_certificate_validate_digest(PKCS7cert, x509SignCert, *Data, *DataSize);
        }
    } 

    // Security concern, memory heap is being cleared on exit 
    ResetCRmm();

    // failed to process
    Status = !err ? EFI_SUCCESS:EFI_SECURITY_VIOLATION;

    return Status;
#else
    return EFI_UNSUPPORTED;
#endif
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  PeiGetKey
//
// Description:    Function returns Ptr to a Platform Signing Key (PK) Ffs 
//                 inside Recovery FV (FV_BB or similar)
//
//  Input:
//    This            Pointer to the AMI_CRYPT_DIGITAL_SIGNATURE_PPI instance.
//    KeyAlgorithm    Points to the EFI_GUID which identifies the PKpub algorithm to use.
//    PublicKey       Handle to a key used to return a ptr to a Key. This handle must be identifying a public key.
//
// Output:
//    EFI_SUCCESS               The Key is successfully returned.
//    EFI_NOT_FOUND             The Key not found
//    EFI_ACCESS_DENIED         The key could not be used in signature operation.
//    EFI_INVALID_PARAMETER     The size of input message or signature does not meet the criteria 
//                              of the underlying signature algorithm.
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
PeiGetKey (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI      *This,
  IN CONST EFI_GUID          *KeyAlgorithm, // reserved to PKPUB_KEY_GUID
  IN PEI_CRYPT_HANDLE        *PublicKey
  )
{
    if(!PublicKey || !KeyAlgorithm)
        return EFI_INVALID_PARAMETER;

    // now only supporting PKpub key comparison
    if(guidcmp((EFI_GUID*)KeyAlgorithm, &gPKeyGuid))
        return EFI_INVALID_PARAMETER;

    if(pFwKeyHob) {
        PublicKey->AlgGuid = pFwKeyHob->KeyGuid;
        PublicKey->Blob = (UINT8*)pFwKeyHob->KeyAddress;
        PublicKey->BlobSize = pFwKeyHob->KeySize;
        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  PeiVerifyKey
//
// Description:    Function compares the input PublicKey against 
//                 Platform Signing Key (PK) image in the flash.
//
//  Input:
//    This            Pointer to the AMI_CRYPT_DIGITAL_SIGNATURE_PPI instance.
//    KeyAlgorithm    Points to the EFI_GUID which identifies the PKpub algorithm to use.
//    PublicKey       Handle to a key used for verifying signatures.  This handle must be identifying a public key.
//
// Output:
//    EFI_SUCCESS               The Key is successfully verified.
//    EFI_SECURITY_VIOLATION    The Key does not match current FW key.
//    EFI_ACCESS_DENIED         The key could not be used in signature operation.
//    EFI_INVALID_PARAMETER     The size of input message or signature does not meet the criteria 
//                              of the underlying signature algorithm.
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
PeiVerifyKey 
(
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI      *This,
  IN CONST EFI_GUID          *KeyAlgorithm, // reserved to PKPUB_KEY_GUID
  IN PEI_CRYPT_HANDLE        *PublicKey
  )
{
    EFI_STATUS    Status;
    int           err;
    PEI_CRYPT_HANDLE KeyHndl;
    UINT8         Hash[SHA256_DIGEST_SIZE] = {0};
    UINT8         *KeyBuf, *PKpubBuffer=NULL;
    UINT32        KeyLen;

    if(!PublicKey || !KeyAlgorithm || !PublicKey->Blob)
        return EFI_INVALID_PARAMETER;
// check Key handle if requested PubKey is a Platform Key PKpub.
// In this case use PKpub key from ffs image
    if(guidcmp((EFI_GUID*)KeyAlgorithm, &gPKeyGuid))
        return EFI_INVALID_PARAMETER;

    Status = PeiGetKey(This, KeyAlgorithm, &KeyHndl);
    if(!EFI_ERROR(Status)) {
// only store Sha256 or n-modulus of RSA2048. For x509 cert - compare hash of an entire cert
// FFS - Sha256 Hash ->
//       Input =Sha258  -> cmp
//       Input =RSA2048 -> Hash n-modulus
//       Input =x509    -> Hash x509 cert
// FFS - RSA2048 ->
//       Input =RSA2048 -> cmp
//       Input =x509    -> extract n-modulus
// FFS - x5098 ->
//       Input =x509    -> cmp
/*
        PKpubBuffer = KeyHndl.Blob;
        KeyLen = KeyHndl.BlobSize; // always 256
        KeyBuf = PublicKey->Blob;

        if(!guidcmp(&KeyHndl.AlgGuid, &gEfiCertSha256Guid)) {
            KeyBuf = Hash;
            KeyLen = SHA256_DIGEST_SIZE;
            if(!guidcmp(&PublicKey->AlgGuid, &gEfiCertRsa2048Guid) ||
               !guidcmp(&PublicKey->AlgGuid, &gEfiCertX509Guid) ) {
            // SHA256 Hash of RSA Key/x509 cert
                sha256_vector(1, (const UINT8**)&PublicKey->Blob, (const UINTN*)&PublicKey->BlobSize, Hash);
            }
        } else 
            // if FwKey is x509 and Key->Algo - gEfiCertRsa2048Guid:
            // derive nModulus from x509 Key Cert for comparison
            if(!guidcmp(&KeyHndl.AlgGuid, &gEfiCertRsa2048Guid) &&
               !guidcmp(&PublicKey->AlgGuid, &gEfiCertX509Guid) ) {
                PKpubBuffer = &Hash[0];
                KeyLen = DEFAULT_RSA_KEY_MODULUS_LEN;
                ResetCRmm();
                err = Pkcs7_x509_return_Cert_pubKey((UINT8*)PublicKey->Blob, (UINTN)PublicKey->BlobSize, &PKpubBuffer, &KeyLen);
                ResetCRmm();
                if(err) return EFI_SECURITY_VIOLATION;
            }
*/
        PKpubBuffer = KeyHndl.Blob;
        KeyLen = KeyHndl.BlobSize; // always 256
        KeyBuf = PublicKey->Blob;
        if(!guidcmp(&KeyHndl.AlgGuid, &gEfiCertSha256Guid) &&
           !guidcmp(&PublicKey->AlgGuid, &gEfiCertRsa2048Guid)
        ) {
        // SHA256 Hash of RSA Key
            KeyLen = SHA256_DIGEST_SIZE;
            KeyBuf = Hash;
            sha256_vector(1, (const UINT8**)&PublicKey->Blob, (const UINTN*)&PublicKey->BlobSize, KeyBuf);
#if CONFIG_PEI_PKCS7 == 1
        } else {
            // if FwKey is x509 and Key->Algo - gEfiCertRsa2048Guid:
            // derive nModulus from x509 Key Cert for comparison
            if(!guidcmp(&KeyHndl.AlgGuid, &gEfiCertRsa2048Guid) &&
               !guidcmp(&PublicKey->AlgGuid, &gEfiCertX509Guid)
            ) {
                PKpubBuffer = &Hash[0];
                KeyLen = DEFAULT_RSA_KEY_MODULUS_LEN;
                ResetCRmm();
                err = Pkcs7_x509_return_Cert_pubKey((UINT8*)PublicKey->Blob, (UINTN)PublicKey->BlobSize, &PKpubBuffer, &KeyLen);
                ResetCRmm();
                if(err) return EFI_SECURITY_VIOLATION;
            }
#endif
        }

        err = MemCmp(PKpubBuffer, KeyBuf, KeyLen);
        Status = !err ? EFI_SUCCESS:EFI_SECURITY_VIOLATION;

    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CryptoPei_Init
//
// Description: This function is the entry point for this PEI.
//
//
// Input:       FfsHeader   Pointer to the FFS file header
//              PeiServices Pointer to the PEI services table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CryptoPei_Init (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS              Status;
    UINTN                   Size;
    UINTN                   Npages;
    EFI_PHYSICAL_ADDRESS    DstAddress;
    EFI_BOOT_MODE           BootMode;
    UINT8         Index;
    UINT8        *pBuf;

    gPeiServices = PeiServices; 

    Status = (*gPeiServices)->GetBootMode( PeiServices, &BootMode );
    if(EFI_ERROR(Status) || BootMode == BOOT_ON_S3_RESUME) {
        return Status; // skip Crypto PPI install on S3 resume
    }

////////////////////////////////////////////////////////////////////////////////////
//
// Create FwKey Hob
//
////////////////////////////////////////////////////////////////////////////////////
    Index = 0;
    while(gKeyFileGuid[Index] != NULL)
    {
// Available Key Cert GUIDs: RSA2048, SHA256 and x509
        Status = CryptoGetRawImage(gKeyFileGuid[Index], (VOID**)&pBuf, (UINTN*)&Size);
        if(!EFI_ERROR(Status)) {
        //  make sure the Key buffer is mapped to FV_BB address space 
/*
            if(!((UINT32)pBuf > FV_BB_BASE && 
                 (UINT64)((UINT32)pBuf+Size) < 
                 (UINT64)(FV_BB_BASE+(UINT64)FV_BB_BLOCKS*FLASH_BLOCK_SIZE)))
                break;
*/
            Status = (*PeiServices)->CreateHob(
                PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, 
               sizeof(FW_KEY_HOB), &pFwKeyHob);
            if (!EFI_ERROR(Status) && pFwKeyHob) {
                pFwKeyHob->Header.Name = gPKeyGuid;
                pFwKeyHob->KeyGuid =  *gKeyTypeGuid[Index];
                pFwKeyHob->KeyAddress = (EFI_PHYSICAL_ADDRESS)(UINT32)pBuf;
                pFwKeyHob->KeySize = Size;
            }    
            break;
        }
        Index++;
    }

////////////////////////////////////////////////////////////////////////////////////
//
// Init Aux Memory Manager
//
////////////////////////////////////////////////////////////////////////////////////
// convert the Heap Size in bytes to the number of pages and allocate appropriate number of pages

    Size = CR_PEI_MAX_HEAP_SIZE;
    Npages = EFI_SIZE_TO_PAGES(Size);
    Status = (*gPeiServices)->AllocatePages(gPeiServices, EfiBootServicesData, Npages, &DstAddress);
    PEI_TRACE(((UINTN)TRACE_ALWAYS, gPeiServices, "Heap alloc %r (addr=%X, size=%d)\n", Status, (UINT32)DstAddress, Size));
    if(EFI_ERROR(Status))
    {
        return Status;
    }
    InitCRmm((void*)DstAddress, Size);
    //  
    // Update Crypto debug traces level
    //
    wpa_set_trace_level(CRYPTO_trace_level); 

////////////////////////////////////////////////////////////////////////////////////
//
// Install VerifySig PPI
//
////////////////////////////////////////////////////////////////////////////////////
    return (**gPeiServices).InstallPpi (gPeiServices, &mPpiSigListVariable);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
