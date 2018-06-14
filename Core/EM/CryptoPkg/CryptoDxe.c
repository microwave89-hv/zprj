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
// $Header: /Alaska/BIN/Modules/CryptoPkg/CryptoDxe.c 31    8/15/13 9:43a Alexp $
//
// $Revision: 31 $
//
// $Date: 8/15/13 9:43a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/CryptoPkg/CryptoDxe.c $
// 
// 31    8/15/13 9:43a Alexp
// Pkcs7Verify() - add TimeStamp signature processing(UEFI ECR1009)
// Pkcs7Verify() - enable code branch for PKCS7_MUTEX_LOCK
// 
// 30    8/02/13 4:26p Alexp
// Moved EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID under AmiDigSig 
// Protocol defining header file
// 
// 29    8/02/13 4:00p Alexp
// 1. Fix logic to get FwKey from a Hob. 
//  Key is copied into pre-allocated buffer by driver entry point
// 2. Optimized Pkcs7Verify. 
// 
// 27    6/20/13 1:55p Alexp
// Impove FwKey handling. CryptoPEI pass FwKey location to Dxe via Hob
// Add mor parameter checking including 
//  check for FwKey location to be mapped to Flash FV_BB
// 
// 26    1/11/13 10:07a Alexp
// GetKey(): fix MemCpy() 2nd argument. Was not copying a key buffer.
// 
// 25    12/28/12 2:50p Alexp
// EIP#110823:The system cannot boot to UEFI(WIN8) OS if the Secure Flash
// Pkg module is not supported
//  Update GetKey(); InSmmFunction() and NotInSmmFunction() routines 
//   to handle cases when Fw Key FFS file not present
// 
// 23    12/10/12 6:09p Alexp
// Bug fix: InSmmFunction() the Key pointer gKeyBuf was to updated to Key
// in SMM region
// 
// 21    12/07/12 4:08p Alexp
// disable debug crypto traces in SMM
// 
// 20    11/29/12 3:10p Alexp
// Pkcs7Verify()- 
// Fix error checking for input **Data parameter : Data == NULL
// 
// 18    11/16/12 5:10p Alexp
// EIP#105015: Add handling of x509 format for Platform FW Key in FFS
// files
// 
// 16    8/28/12 12:33p Alexp
// UEFI 2.3.1. ErrataC. 
// Added support for new Hash types 
// defined by a GUID with 'NOPAD' keyword:
// EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID
// EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID
// 
// 15    8/22/12 4:28p Alexp
//  Added support in Pkcs7Parse() for new operations:
//      Pkcs7CertValidateGetSignerKey -  n-modulus of Signer key
//      Pkcs7CertGetMatchInCertChain  - true if found leaf cert matching
// to
//         trust cert
//      Pkcs7CertValidateGetCAKey,     - n-modulus of CA key if detected
// in
//          x509 chain
//      Pkcs7GetCAKey, Pkcs7GetSignerKey
// 
// 12    7/23/12 4:12p Alexp
// Pkcs7Verify:
// Bug Fix. For condition:Pkcs7CertValidateGetMatchInCertChain return
// success if leaf cert is found. Before code fell down testing
// certificate and could return error potentially misleading Caller of this
// function.
// 
// 11    7/18/12 8:57p Alexp
// Pkcs7Verify
// fix bug - "reason" var was used uninitialized
// 
// 10    5/04/12 9:49a Alexp
// [TAG]          EIP89280
// [Category]      Improvement
// [Description]      When secure boot enable with secure flash disable, in
// Security page of setup menu same items will exist twice
// Fix: Install Crypto Protocols even if Root FW Key not found (brought in
// by Sec Flash module)
// [Files]          cryptoDxe.c
// 
// 9     4/11/12 5:27p Alexp
// Add new operand within Pkcs7Validate:
// Pkcs7CertValidateGetMatchInCertChain
// 
// 7     3/02/12 10:43a Alexp
// Remove dependency on SDL Token FWKEY_FORMAT to determine format of PR
// Key file
// Try different Ffs GUIDs to select proper Key format: SHA or RSA
// 
// 6     2/29/12 4:04p Alexp
// 1. Add VerifyKey
// 2. Fix GetKey (API call will be deprecated as not needed) to move PR
// Key from file to local storage
// 3. Use FWKEY_FORMAT to process VerifyKey according to file format. Hash
// input RSA2048 key for comparison if PR Key stored as Hash
// 
// 5     11/14/11 12:01p Alexp
// InSmmFunction()->InstallMultipleProtocols() Change the HAndle argument
// from ImageHandle to a DummyHandle=NULL
// 
// 4     6/30/11 5:45p Alexp
// GetRawImage: added freepool(HandleBuffer)
// 
// 3     6/27/11 5:30p Alexp
// removed commented out lines
// 
// 2     6/22/11 5:46p Alexp
// update deafult Crypto trace level
// 
// 1     6/13/11 5:19p Alexp
// 
// 7     6/10/11 6:21p Alexp
// added new Pkcs7 parse  Operation: Pkcs7CertValidateGetSignerKeyHash
// 
// 6     6/09/11 9:57a Alexp
// always parse PKCS7 cert
// 
// 5     5/18/11 1:18p Alexp
// edited text in func headers
// 
// 4     5/17/11 12:53p Alexp
// fix WDK Level4 compiler warnings
// 
// 3     5/11/11 7:38p Alexp
// remove set trace level call. If needed, modify Sdl token in Crypto Src
// 
// 2     5/10/11 6:55p Alexp
// use external Guid variable declarations
// 
// 1     5/06/11 6:11p Alexp
// initial module release
// 
// 10    4/22/11 4:20p Alexp
// cleaned up CryptoGetRawImage 
// 
// 9     4/18/11 7:09p Alexp
// 
// 8     4/11/11 12:52p Alexp
// remove ASN1 as possible Key buf format. 
// 
// 7     4/05/11 6:31p Alexp
// remove content from GetKey.  We may add get FwSig key in later
// revisions
// 
// 6     3/31/11 6:14p Alexp
// hashing of SpcIndirect data is done inside Pkcs Validate
// 
// 
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include "Setup.h"
#include "AmiCertificate.h"
#include <Protocol\AmiDigitalSignature.h>
#include <Protocol\Hash.h>

#include <cryptlib.h>

#include <Protocol\SmmBase.h> // used for SMM Malloc

//
// Global variables
//
extern EFI_BOOT_SERVICES    *pBS;
extern EFI_RUNTIME_SERVICES *pRS;

static EFI_GUID gPRKeyGuid = PR_KEY_GUID;

// The ptr to a buffer containing the Fw Platform Key
// Key Image is copied from .ffs to a local buffer. 
// It is a safe location in case of AmiSig running in SMM
static CRYPT_HANDLE gKey = {{0},0,NULL};

// Second part of the Public key, public exponent (e), 
// must be hardwired in the FW elsewhere(recommended value of e=65537).
//
// SDL Hardwired value of publicExponent--e
const UINT8  KeyE[] = {E_CONST}; // 0x10001
const UINT32 LenE = sizeof(KeyE);
const INT32  saltlen = PSS_SIG_SALTLEN; // 8
static UINT8 Rsa2048Sig[DEFAULT_RSA_SIG_LEN];

// Pkcs7 Certificate private var
//struct pkcs7_signed_data_st* PKCS7cert = NULL;
// Mutex to control Memory reset during atomic Pkcs7 operations
static UINT8  MutexLock = RESET;

//----------------------------------------------------------------------------
// Crypto Function prototypes
//----------------------------------------------------------------------------
EFI_STATUS
Pkcs1Verify (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN CRYPT_HANDLE *PublicKey,
  IN CRYPT_HANDLE *Hash,
  IN VOID         *Signature,
  IN UINTN        SignatureSize,
  IN UINT32       Flags
  );

EFI_STATUS
Pkcs7Verify (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN CONST UINT8 *P7Data,
  IN UINTN        P7Size,
  IN CONST UINT8 *TrustedCert,
  IN UINTN        CertSize,
  IN OUT UINT8  **Data,
  IN OUT UINTN   *DataSize,
  IN UINT8        Operation,
  IN UINT32       Flags
  );

EFI_STATUS
Hash(
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL  *This,
  IN CONST EFI_GUID   *HashAlgorithm,
  IN UINTN            Num_elem,
  IN CONST UINT8      *Addr[],
  IN CONST UINTN      *Len,
  OUT UINT8           *Hash
  );

EFI_STATUS
GetKey (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL  *This,
  OUT CRYPT_HANDLE  *Key,
  IN  EFI_GUID      *AlgId,
  IN  UINTN          KeyLen,
  IN  UINT32         Flags
  );

EFI_STATUS
VerifyKey (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN EFI_GUID       *AlgId,
  IN CRYPT_HANDLE   *Key
  );
//----------------------------------------------------------------------------
// Crypto Protocol Identifiers
//----------------------------------------------------------------------------
AMI_DIGITAL_SIGNATURE_PROTOCOL  mAmiSig = {
  Pkcs1Verify,
  Pkcs7Verify,
  Hash,
  GetKey,
  VerifyKey
};

//----------------------------------------------------------------------------
// Crypto Function Implementation
//----------------------------------------------------------------------------

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  Hash
//
// Description:    Allows creating a hash of an arbitrary message digest using one or more hash algorithms
//
// Input:
//      This          Pointer to the AMI_DIGITAL_SIGNATURE_PROTOCOL instance.
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
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
Hash(
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL  *This,
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
    if(!guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha1Guid) ||
       !guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha1NoPadGuid)) 
    {
        bSha1 = TRUE;
        HashLen = SHA1_DIGEST_SIZE;
    }
    else 
        if(!guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha256Guid) ||
           !guidcmp((EFI_GUID*)HashAlgorithm, &gEfiHashAlgorithmSha256NoPadGuid))
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
// Procedure:  Pkcs7Verify
//
// Description:    Verifies the validity of a PKCS#7 signed data as described in "PKCS #7: Cryptographic
//                 Message Syntax Standard".
//                 Function perfors several operations on input Pkcs7 certificate 
//                 based on the input Operation argument
//                 1. Verifies validity of the signature contained inside the Certificate
//                    This function decrypts the signature with the Public key from the Signer certificate 
//                    and then compares the decrypted value to the input Data
//                 2. Extracts the Signer certificate in format of x509
//                 3. Extracts Root CA certificate that used to sign the Signer certificate.
//
//  Input:
//      This         Pointer to the AMI_DIGITAL_SIGNATURE_PROTOCOL instance.
//      P7Data       Pointer to the PKCS#7 DER encoded message to verify.
//      P7Size       Size of the PKCS#7 message in bytes.
//      TrustedCert  Pointer to a trusted/root X509 certificate encoded in DER, which
//                   is used for certificate chain verification.
//      CertSize     Size of the trusted certificate in bytes.
//      Data         Pointer to the content to be verified/returned at
//      DataSize     Size of Data in bytes
//      Operation    Specifies different tasks to perform:
//                   0-Function presence check. Must return EFI_SUCCESS 
//                   1-Validate Certificate
//                   2-Return Signer Certificate in *Data. Performs cert chaining and time based validity tests
//                   3-Return Root CA certificate referenced by Signer. Used to compare with Trusted Cert in FW
//                   4-Validate Root Certificate
//                   5-Validate Signer Certificate Chain
//                   6-Return Signature Digest Algorithm
//                   7-Validate Certificate, return Root CA Certificate
//                   8-Validate Certificate, return Signer Certificate
//                   9-Validate Certificate, return Signer Key Hash (SHA256)
//                   10-Validate Certificate and return Success if match is found between Trust and any leaf certificates in the Signer chain
//                   11-Validate Certificate, return ptr in *Data to n-modulus of a Signer Key
//                   12-Return Success if match is found between Trust and any leaf certificates in the Signer chain
//                   13-Validate Certificate, return ptr in *Data to n-modulus of a Root CA Key
//                   14-Return ptr in *Data to n-modulus of a Root CA Key
//                   15-Return ptr in *Data to n-modulus of a Signer Key
//                   16-Validate TimeStamp certificate chain in Pkcs7 Certificate
//                   17-255 reserved values
//      Flags        Specifies additional flags to further customize the signing/verifying behavior.
//
// Output:    
//    EFI_SUCCESS              The specified PKCS#7 signed data is valid
//    EFI_SECURITY_VIOLATION   Invalid PKCS#7 signed data.
//    EFI_ACCESS_DENIED        The Trusted certificate does not have a match in SignedData.certificate store.
//    EFI_INVALID_PARAMETER    The size of input message or signature does not meet the criteria 
//                             of the underlying signature algorithm.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
Pkcs7Verify (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN CONST UINT8 *P7Data,
  IN UINTN        P7Size,
  IN CONST UINT8 *TrustedCert,
  IN UINTN        CertSize,
  IN OUT UINT8   **Data,
  IN OUT UINTN   *DataSize,
  IN UINT8        Operation,
  IN UINT32       Flags
  )
{
    EFI_STATUS  Status;
    INTN        err, reason;
    static struct pkcs7_signed_data_st* PKCS7cert;
    struct x509_certificate *x509SignCert;
    struct x509_certificate *x509TrustCert;
    UINT8  *x509SignCertPtr, *x509RootCertPtr;
    UINTN  SignCert_len, CARootCert_len;
    struct pkcs7_cert_revoke_info   revokeInfo;
    EFI_CERT_X509_SHA256     *revokeCert;

// Mutex functionality:
/*
Structure mutex
Mutual exclusion (mutex) semaphore locking mechanism used to serialise interthread intraprocess activities.
*/
#if PKCS7_MUTEX_LOCK == 1
    switch(Flags & 0x3) {
        case RESET:
            ResetCRmm();    // first time needs mem clean
            MutexLock = RESET;
            PKCS7cert = NULL;
          break;

        case LOCK:
            ResetCRmm();    // first time needs mem clean
            MutexLock = LOCK;
            PKCS7cert = NULL;
          break;

        case RELEASE:       // clear memory after execute routines
            if(MutexLock == RESET)
                ResetCRmm();
            MutexLock = RESET;
          break;

        case KEEP:      
            if(MutexLock == RESET)
                ResetCRmm();
          break;

        default: 
            ResetCRmm();
    }
#else
    PKCS7cert = NULL;
    ResetCRmm();
#endif
/*
    Notes of implementation:
    
    IN order to allocate the Pool for returned Cert (Signer or CA) 
    -run getCert with Size 0 -> it will return real cert size
    -allocate buffer of Size and re-run with new size
    OR caller is responsible for freeng the Data buffer
    OR caller always allocates sufficient size == Trusted Cert + 1k 

    GetSignerCert
        parse Pkcs7 to *Pkcs7cert
        get SignerName from SignerInfo.serialName
        find x509 cert matching Signer name
    GetCACert
        run GetSignerCert
        run cert chain valid for that cert

    ValidateSignCert - internal Cert validation, returns Root CA Cert ptr
    ValidateTrustCert - external Trust Cert validation, returns Sign Cert ptr
        
*/
    err = -1;
    reason=0;

    switch(Operation){
        case Pkcs7Arg0: 
            Status = EFI_SUCCESS; 
            err = 0;
            break;    
// Validate Digest and returns Root CA cert or Signer Cert
        case Pkcs7CertGetMatchInCertChain:
        case Pkcs7CertValidateGetMatchInCertChain: // obsolete
            reason = -1; // non-0 reason argument forces Pkcs7_Chain_Validate to scan for matching Cert in the Chain if other checks failed
        case Pkcs7CertValidate: 
        case Pkcs7CertValidateGetCAKey:
        case Pkcs7CertValidateGetCACert:
        case Pkcs7CertValidateGetSignerKey:
        case Pkcs7CertValidateGetSignerCert:
        case Pkcs7CertValidateGetSignerKeyHash:
        case Pkcs7TimeStampCertValidateGet:
        	if(Data == NULL || DataSize == NULL)
                break;
        case Pkcs7ValidateRootCert:
              if (!PKCS7cert) PKCS7cert = Pkcs7_parse_Authenticode_certificate(P7Data, P7Size);
            if (!PKCS7cert) 
                break;
            // verify Pkcs7 Signing Cert chain up to the TrustCert...if provided
            if(TrustedCert && CertSize) {
                x509TrustCert = x509_certificate_parse(TrustedCert, CertSize);
                if(x509TrustCert) {
                    err = Pkcs7_x509_certificate_chain_validate_with_timestamp(PKCS7cert, (Operation == Pkcs7TimeStampCertValidateGet), x509TrustCert, NULL, (int*)&reason);
                } else {
                // potentially a TimeStamped revocation cert 
                    revokeCert = (EFI_CERT_X509_SHA256*)TrustedCert;
                    if(CertSize == sizeof(EFI_CERT_X509_SHA256))
                        revokeInfo.ToBeSignedHashLen = 32;
                    else 
                        if(CertSize == sizeof(EFI_CERT_X509_SHA384))
                            revokeInfo.ToBeSignedHashLen = 48;
                        else 
                            if(CertSize == sizeof(EFI_CERT_X509_SHA512))
                                revokeInfo.ToBeSignedHashLen = 64;
                            else { // unsupported Hash struct
                                err = -1;
                                break;
                            }
                    revokeInfo.ToBeSignedHash = (UINT8*)&revokeCert->ToBeSignedHash;
                   	err = Pkcs7_x509_certificate_chain_validate_with_timestamp(PKCS7cert, FALSE, NULL, &revokeInfo, (int*)DataSize);
                }

                if(err == -1 || 
                    Operation==Pkcs7CertGetMatchInCertChain || 
                    Operation == Pkcs7ValidateRootCert
                )
                    break;     // break(err=0) if leaf found to match trust cert
            }
            // x509SignCert== NULL -> extract SignCert from Pkcs7 crt
            err = Pkcs7_certificate_validate_digest(PKCS7cert, NULL, (UINT8*)*Data, (UINTN)*DataSize);
            if(!err) {
                switch(Operation){
           //Returns CA Root cert after successfully validating Cert chain and signature digest
                    case Pkcs7CertValidateGetCACert:
                        err = Pkcs7_return_cerificate_ptr(PKCS7cert, Data, DataSize, &x509SignCertPtr, (size_t*)&SignCert_len);
                        break;
           //Returns Signing Key from Cert after successfully validating Cert chain and signature digest
                    case Pkcs7CertValidateGetSignerCert:
                        err = Pkcs7_return_cerificate_ptr(PKCS7cert, &x509RootCertPtr, (size_t*)&CARootCert_len, Data, DataSize);
                        break;
                    case Pkcs7CertValidateGetSignerKeyHash:
                        err = Pkcs7_x509_return_signing_Key(PKCS7cert, &x509SignCertPtr, &SignCert_len);
                        if(!err) {
                            Hash(This, &gEfiHashAlgorithmSha256Guid, 1, &x509SignCertPtr, (const UINTN*)&SignCert_len, *Data); 
                            *DataSize=SHA256_DIGEST_SIZE;
                        }
                        break;
                    case Pkcs7CertValidateGetSignerKey:
                        err = Pkcs7_x509_return_signing_Key(PKCS7cert, Data, DataSize);
                        break;
                    case Pkcs7CertValidateGetCAKey:
                        err = Pkcs7_return_cerificate_ptr(PKCS7cert, Data, DataSize, &x509SignCertPtr, (size_t*)&SignCert_len);
                        if(!err)
                            err = Pkcs7_x509_return_Cert_pubKey(*Data, *DataSize, Data, DataSize);
                        break;
                    case Pkcs7TimeStampCertValidateGet:
                        err = Pkcs7_certificate_validate_timestamp_digest(PKCS7cert, (long*)DataSize);
                        break;
                 } 
            }
            break;

// returns Ptr within input P7Data DER buffer to RootCA cert or Signing Cert
        case Pkcs7GetSignerCert: 
        case Pkcs7GetCACert: 
        case Pkcs7GetSignerKey:
        case Pkcs7GetCAKey:
            if(Data == NULL || DataSize == NULL) {
                break;    
            }
              if (!PKCS7cert) PKCS7cert = Pkcs7_parse_Authenticode_certificate(P7Data, P7Size);
            if (PKCS7cert) {
                err = Pkcs7_return_cerificate_ptr(PKCS7cert, &x509RootCertPtr, (size_t*)&CARootCert_len, &x509SignCertPtr, (size_t*)&SignCert_len);
                if(!err) {
                    switch(Operation){
                        case Pkcs7GetSignerCert: 
                            *DataSize = SignCert_len;
                            *Data   = x509SignCertPtr;
                            break;
                        case Pkcs7GetCACert: 
                            *DataSize = CARootCert_len;
                            *Data = x509RootCertPtr;
                            break;
                        case Pkcs7GetCAKey:
                            err = Pkcs7_x509_return_Cert_pubKey(x509RootCertPtr, CARootCert_len, Data, DataSize);
                            break;
                        case Pkcs7GetSignerKey:
                            err = Pkcs7_x509_return_Cert_pubKey(x509SignCertPtr, SignCert_len, Data, DataSize);
                            break;
                    }
                }
            }
            break; 

        case x509ValidateCertChain:
        //Validates Signer certificate's key against Trusted Cert
            x509SignCert = x509_certificate_parse(P7Data, P7Size);
            if(TrustedCert && CertSize)
                x509TrustCert = x509_certificate_parse(TrustedCert, CertSize);
            if (x509TrustCert && x509SignCert)
               err = x509_certificate_chain_validate(x509TrustCert, x509SignCert, (int*)&reason);
            break;

        case Pkcs7GetDigestAlgorithm: 
        // validate input params.
            if(Data == NULL || DataSize == NULL) {
                break;
            }
              if (!PKCS7cert) PKCS7cert = Pkcs7_parse_Authenticode_certificate(P7Data, P7Size);
            if (PKCS7cert) {
                err = Pkcs7_return_digestAlgorithm(PKCS7cert, (UINT8*)*Data);
                if(!err)
                    *DataSize = sizeof(UINT8);
             }
            break;

        default: 
            Status = EFI_INVALID_PARAMETER;
            err = -1;
    }

// Security concern, memory heap is being cleared on exit 
    if(err)  
        MutexLock = RESET;

#if PKCS7_MUTEX_LOCK == 1
    if(MutexLock == RESET) 
#endif
    {
        ResetCRmm();
        PKCS7cert = NULL;
    }

// failed to process
    Status = !err ? EFI_SUCCESS:EFI_SECURITY_VIOLATION;

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  Pkcs1Verify
//
// Description:    Function verifies that the specified signature matches the specified hash. 
//                 Verifies the RSA-SSA signature with EMSA-PKCS1-v1_5 encoding scheme defined in
//                 RSA PKCS#1.
//                 This function decrypts the signature with the provided key and then compares 
//                 the decrypted value to the specified hash value
//
//  Input:
//    This          Pointer to the AMI_DIGITAL_SIGNATURE_PROTOCOL instance.
//    PublicKey     Handle to a key used for verifying signatures. This handle must be identifying a public key.
//    Hash          Handle of the hash object to verify.
//    Signature     Pointer to the signature data to be verified.
//    SignatureSize The size, in bytes, of the signature data.
//    Flags         Specifies additional flags to further customize the signing/verifying behavior.
//
// Output:    
//    EFI_SUCCESS              The signature is successfully verified.
//    EFI_SECURITY_VIOLATION   The signature does not match the given message.
//    EFI_ACCESS_DENIED        The key could not be used in signature operation.
//    EFI_INVALID_PARAMETER    The size of input message or signature does not meet the criteria 
//                             of the underlying signature algorithm.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
Pkcs1Verify (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN CRYPT_HANDLE   *PublicKey,
  IN CRYPT_HANDLE   *Hash,
  IN VOID           *Signature,
  IN UINTN           SignatureSize,
  IN UINT32          Flags
  )
{
    EFI_STATUS  Status;
    INTN        err;
    struct      crypto_rsa_key *key = NULL;
    UINT16      Size = (UINT16)(PublicKey->BlobSize);
    size_t     *sig_len=(size_t*)&SignatureSize;
    INT32       modulus_bitlen = DEFAULT_RSA_SIG_LEN << 3;
    UINT32      HashLen;

// Only supporting RSASSA_PKCS1V15 & PSS signature types
    if(!((Flags & EFI_CRYPT_RSASSA_PKCS1V15) || 
         (Flags & EFI_CRYPT_RSASSA_PSS)) )
            return EFI_INVALID_PARAMETER;

    if(!PublicKey || !Hash || !Signature)
        return EFI_INVALID_PARAMETER;

    ResetCRmm();
    MutexLock = RESET;

// For now Public Key is supported in 2 formats: RAW 256 bytes and ASN.1 Integer
    if(!guidcmp(&PublicKey->AlgGuid, &gEfiCertRsa2048Guid))
        key = crypto_import_rsa2048_public_key(PublicKey->Blob, Size, (UINT8*)&KeyE, LenE);
    else 
        return EFI_INVALID_PARAMETER;

// 2 hash types supporte: SHA1 & SHA256
    if(!guidcmp(&Hash->AlgGuid, &gEfiHashAlgorithmSha256Guid))
        HashLen = SHA256_DIGEST_SIZE;
    else if(!guidcmp(&Hash->AlgGuid, &gEfiHashAlgorithmSha1Guid))
            HashLen = SHA1_DIGEST_SIZE;
        else
            HashLen = SHA256_DIGEST_SIZE;

    if(key == NULL )
        err = -1;
    else
        err = crypto_rsa_exptmod((const UINT8*)Signature, (size_t)SignatureSize, (UINT8*)&Rsa2048Sig, sig_len, key, 0);

// locate Hash inside the decrypted signature body and compare it with given Hash;
    if(!err) {
        if(Flags & EFI_CRYPT_RSASSA_PKCS1V15)
        {
            // Validate PKCS#1 Padding
//            err = pkcs_1_v1_5_decode((const UINT8 *)&Hash->Blob, HashLen, (const UINT8 *)&Rsa2048Sig, (unsigned long)*sig_len);
            err = MemCmp((void*)(UINTN)Hash->Blob, (void*)(UINTN)((UINT32)(UINTN)Rsa2048Sig + (UINT32)(*sig_len - HashLen)), HashLen);
        }
        else //(Flags & EFI_CRYPT_RSASSA_PSS))
            // Validate PKCS_1 PSS Signature: padding & hash
            err = pkcs_1_pss_decode((UINT8*)Hash->Blob, HashLen,(const unsigned char *)&Rsa2048Sig, (unsigned long)*sig_len, 
                    saltlen,  modulus_bitlen);
    }

    Status = !err ? EFI_SUCCESS:EFI_SECURITY_VIOLATION;

// Security concern, memory heap is being cleared on exit 
    ResetCRmm();

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CryptoGetFwKey
//
// Description:    Passes FwKey info from a Hob to an external Key handler structure
//
//  Input:       Key       - ptr to the buffer to hold the target key parameters
//
// Output:       Status
//
//               EFI_NOT_FOUND  - Can't find the Key Hob
//               EFI_INVALID_PARAMETER - Wrong KeyID
//               EFI_LOAD_ERROR - Load fail.
//               EFI_SUCCESS    - Load success.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CryptoGetFwKey (
  IN EFI_SYSTEM_TABLE *SystemTable,
  IN CRYPT_HANDLE   *Key
)
{
    EFI_STATUS    Status=EFI_NOT_FOUND;
    FW_KEY_HOB     *pFwKeyHob;
    static EFI_GUID HobListGuid = HOB_LIST_GUID;

    if(!Key) return EFI_INVALID_PARAMETER;

    pFwKeyHob = GetEfiConfigurationTable(SystemTable, &HobListGuid);
    if (pFwKeyHob!=NULL) {
        Status = FindNextHobByGuid(&gPRKeyGuid, &pFwKeyHob);
        if(!EFI_ERROR(Status)) {
// make sure the Key buffer is mapped to FV_BB address space 
/*
            if(!((UINT32)pFwKeyHob->KeyAddress > FV_BB_BASE && 
                 (UINT64)((UINT32)pFwKeyHob->KeyAddress+pFwKeyHob->KeySize) < 
                    (UINT64)(FV_BB_BASE+(UINT64)FV_BB_BLOCKS*FLASH_BLOCK_SIZE))) {
                return EFI_NOT_FOUND;
*/
            Key->Blob = (UINT8*)(UINT32)pFwKeyHob->KeyAddress;
            Key->BlobSize = pFwKeyHob->KeySize;
            Key->AlgGuid  = pFwKeyHob->KeyGuid;
        }
    }

    TRACE(((UINTN) -1,"Get Key File %g: %r\n(%lx, %dbytes)=%X,%X\n", Key->AlgGuid, Status, Key->Blob, Key->BlobSize, Key->Blob[0], Key->Blob[1]));

    return Status;
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  GetKey
//
// Description:    Return Firmware Signing Key from a local storage
//
//  Input:
//    This         Pointer to the AMI_DIGITAL_SIGNATURE_PROTOCOL instance.
//    Key          ptr to the buffer to hold the target key
//    AlgId        Key GUID
//    KeyLen       Length of the target Key buffer
//    Flags        Specifies additional flags to further customize the GetKey behavior.
// Output:    
//    EFI_SUCCESS            
//    EFI_ACCESS_DENIED        The key could not be located
//    EFI_INVALID_PARAMETER    Wrong KeyID
//    BUFFER_TOO_SMALL         The Key->BlobSize will contain the size of the buffer to be prepared
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
GetKey (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  OUT     CRYPT_HANDLE               *Key,
  IN      EFI_GUID                   *AlgId,
  IN      UINTN                      KeyLen,
  IN      UINT32                     Flags
  )
{
    if(!AlgId || !Key)
        return EFI_INVALID_PARAMETER;

// Guid must match one of the valid keys we can use in Sig verification.
    if(guidcmp(AlgId, &gPRKeyGuid))
        return EFI_UNSUPPORTED;

    if(gKey.Blob && gKey.BlobSize){

// make sure the Key buffer is mapped to FV_BB address space 
/*        if(!((UINT32)gKey.Blob > FV_BB_BASE && 
             (UINT64)((UINT32)gKey.Blob+gKey.BlobSize) < 
                (UINT64)(FV_BB_BASE+(UINT64)FV_BB_BLOCKS*FLASH_BLOCK_SIZE)))
            return EFI_NOT_FOUND;
*/
        Key->BlobSize = gKey.BlobSize;
        Key->AlgGuid = gKey.AlgGuid;
        if(Key->Blob) {
            if(KeyLen < gKey.BlobSize)
                return EFI_BUFFER_TOO_SMALL;
            else
                MemCpy(Key->Blob, gKey.Blob, gKey.BlobSize);
        } else
            Key->Blob = gKey.Blob;// upd address to int buffer

        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  VerifyKey
//
// Description:    Function compares the input PublicKey against 
//                 Platform Signing Key (PK) image in the flash.
//
//  Input:
//    This            Pointer to the AMI_DIGITAL_SIGNATURE protocol instance.
//    KeyAlgorithm    Points to the EFI_GUID which identifies the PKpub algorithm to use.
//    PublicKey       Handle to a key used for verifying signatures.  This handle must be identifying a public key.
//
// Output:
//    EFI_SUCCESS               The Key is successfully verified.
//    EFI_SECURITY_VIOLATION    The Key does not match current FW key.
//    EFI_ACCESS_DENIED         The key could not be used in signature operation.
//    EFI_INVALID_PARAMETER     The size of input message or signature does not meet the criteria 
//                              of the underlying signature algorithm.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
VerifyKey (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN EFI_GUID       *AlgId,
  IN CRYPT_HANDLE   *Key
  )
{
    EFI_STATUS          Status;
    CRYPT_HANDLE        PubKeyHndl;
    UINT8               Hash[SHA256_DIGEST_SIZE]={0};
    UINT8               *KeyFfs, *KeyCmp;
    UINTN               KeyLen;
    UINT32              Flags=0;
    INTN                err;

    if(!AlgId || !Key || !Key->Blob)
        return EFI_INVALID_PARAMETER;

// Guid must match one of the valid keys we can use in Sig verification.
    if(guidcmp(AlgId, &gPRKeyGuid))
        return EFI_UNSUPPORTED;

// Get PRKey
    PubKeyHndl.Blob = NULL;
    PubKeyHndl.BlobSize = 0;
    Status = GetKey(NULL, &PubKeyHndl, AlgId, 0, Flags);
    if(!EFI_ERROR(Status))
    {
        KeyFfs = PubKeyHndl.Blob;
        KeyLen = PubKeyHndl.BlobSize;
        KeyCmp = Key->Blob;

        // If FwKey is Hash of Rsa2048 Key and Key->Algo is Rsa2048 - 
        // prepare Key for SHA256 Hash compare
        if(!guidcmp(&Key->AlgGuid, &gEfiCertRsa2048Guid)) 
        {
            if(!guidcmp(&PubKeyHndl.AlgGuid, &gEfiCertSha256Guid)) 
            {
                KeyCmp = Hash;
                KeyLen = SHA256_DIGEST_SIZE;
                sha256_vector(1, (const UINT8**)&Key->Blob, (const UINTN*)&Key->BlobSize, Hash);
            } else 
                // if FwKey is x509 and Key->Algo - gEfiCertRsa2048Guid:
                // derive nModulus from x509 Key Cert for comparison
                if(!guidcmp(&PubKeyHndl.AlgGuid, &gEfiCertX509Guid)) 
                {
                    KeyFfs = &Rsa2048Sig[0];
                    KeyLen = DEFAULT_RSA_KEY_MODULUS_LEN;
                    ResetCRmm();
                    err = Pkcs7_x509_return_Cert_pubKey((UINT8*)PubKeyHndl.Blob, (UINTN)PubKeyHndl.BlobSize, &KeyFfs,&KeyLen);
                    ResetCRmm();
                    if(err) return EFI_SECURITY_VIOLATION;
                }
        }
        err = MemCmp(KeyFfs, KeyCmp, KeyLen);

        Status = !err ? EFI_SUCCESS:EFI_SECURITY_VIOLATION;
    }
    return Status;
}
//----------------------------------------------------------------------------
// END of Crypto DXE Function definitions
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   InSmmFunction
//
// Description: 
//
// Input:   
//
// Output: 
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS  Status;
    EFI_HANDLE  DummyHandle = NULL;
    UINT8       *pKey;

    TRACE(((UINTN) -1,"Init Crypto API in SMM\n"));
    //
    // Init Crypto lib internal state
    //
    RuntimeCryptLibConstructorInSmm(ImageHandle, SystemTable);
    //  
    // Update Crypto debug traces level
    //
#ifdef EFI_DEBUG
//    wpa_set_trace_level(CRYPTO_trace_level); 
#endif
    //
    // Get location of PRKey from .ffs
    // ReadFfs/FindHob are preboot services whereas Key needs to be available during EFI runtime
    //
    gKey.Blob = NULL;
    Status = CryptoGetFwKey(SystemTable, &gKey);
    if(!EFI_ERROR(Status) && gKey.Blob) {
    // re-allocate buffer in runtime mem 
        pKey = gKey.Blob; // preserve the pointer
        Status = pSmmBase->SmmAllocatePool(pSmmBase, EfiRuntimeServicesData, gKey.BlobSize, (void**)&pKey);
        ASSERT_EFI_ERROR (Status);
        if(!EFI_ERROR(Status)) {
            MemCpy(pKey, gKey.Blob, gKey.BlobSize);
            gKey.Blob = pKey;
        }
    }
    if(EFI_ERROR(Status)) 
        gKey.Blob = NULL;

    TRACE((TRACE_ALWAYS,"Init: GetKey %r (addr %x(%X, %X), %d bytes)\n", Status, gKey.Blob, gKey.Blob[0], gKey.Blob[1], gKey.BlobSize));    

///////////////////////////////////////////////////////////////////////////////////
// Install the SMM clone of Crypto protocols
///////////////////////////////////////////////////////////////////////////////////
    return pBS->InstallMultipleProtocolInterfaces (
            &DummyHandle,
            &gAmiSmmDigitalSignatureProtocolGuid, &mAmiSig,
            NULL
            );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NotInSmmFunction
//
// Description: This function is called from outside of SMM during SMM registration.
//
// Input:
//  IN EFI_HANDLE       ImageHandle
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NotInSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS  Status;
    UINT8       *pKey;

    TRACE(((UINTN) -1,"Init Crypto API NOT in SMM\n"));
    //
    // Init Crypto lib internal state
    //
    RuntimeCryptLibConstructor(ImageHandle, SystemTable);
    //  
    // Update Crypto debug traces level
    //
#ifdef EFI_DEBUG
    wpa_set_trace_level(CRYPTO_trace_level); 
#else
    wpa_set_trace_level(0); 
#endif
    //
    // Get location of PRKey from .ffs
    // ReadFfs/FindHob are preboot services whereas Key needs to be available during EFI runtime
    //
    gKey.Blob = NULL;
    Status = CryptoGetFwKey(SystemTable, &gKey);
    if(!EFI_ERROR(Status) && gKey.Blob) {
    // re-allocate buffer in runtime mem 
        pKey = gKey.Blob; // preserve the pointer
        Status = pBS->AllocatePool(EfiRuntimeServicesData, gKey.BlobSize, (void**)&pKey);
        ASSERT_EFI_ERROR (Status);
        if(!EFI_ERROR(Status)) {
            MemCpy(pKey, gKey.Blob, gKey.BlobSize);
            gKey.Blob = pKey;
        }
    }
    if(EFI_ERROR(Status)) 
        gKey.Blob = NULL;

    TRACE((TRACE_ALWAYS,"Init: GetKey %r (addr %x(%X, %X), %d bytes)\n", Status, gKey.Blob, gKey.Blob[0], gKey.Blob[1], gKey.BlobSize));    


///////////////////////////////////////////////////////////////////////////////
//
// Install the DXE Crypto protocols
//
///////////////////////////////////////////////////////////////////////////////
    return pBS->InstallMultipleProtocolInterfaces (
            &ImageHandle,
            &gAmiDigitalSignatureProtocolGuid, &mAmiSig,
            NULL
            );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CryptoDxe_Init
//
// Description: Entry point of Crypto DXE driver
//
// Input:       EFI_HANDLE           ImageHandle,
//              EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CryptoDxe_Init (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);
    //
    // Install DXE & SMM Crypto Services
    //

    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NotInSmmFunction);
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
