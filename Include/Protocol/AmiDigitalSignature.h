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
// $Header: /Alaska/BIN/Modules/CryptoPkg/Protocol/AmiDigitalSignature.h 11    8/15/13 9:44a Alexp $
//
// $Revision: 11 $
//
// $Date: 8/15/13 9:44a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/CryptoPkg/Protocol/AmiDigitalSignature.h $
// 
// 11    8/15/13 9:44a Alexp
// Add UEFI TimeStamp certificate definitions; add new Pkcs7 operation
// code-Pkcs7TimeStampCertVerifyGet
// 
// 10    8/02/13 4:27p Alexp
// Add temporary defines for new Hash types with noPad 
// 
// 9     8/01/13 6:45p Alexp
// temp add  TIME STAMP type definitions per UEFI ECR#1009
// 
// 8     7/11/13 4:06p Alexp
// EIP#118850:Develop functionality per UEFI Mantis ticket (ECR)#1009
// add new Pkcs7 operator: Pkcs7TimeStampCertValidate
// 
// 7     8/22/12 4:38p Alexp
//   Added new Pkcs7Parse operations:
//     Pkcs7CertValidateGetSignerKey, 
//     Pkcs7CertGetMatchInCertChain,
//     Pkcs7CertValidateGetCAKey,
//     Pkcs7GetCAKey, Pkcs7GetSignerKey
// 
// 5     4/09/12 4:49p Alexp
// Add new Pkcs7Verify operand::Pkcs7CertValidateGetMatchInCertChain
// 
// 4     2/29/12 3:59p Alexp
// Add VerifyKey Protocol function to match to Crypto PEI API. 
// 
// 3     6/10/11 6:21p Alexp
// added new Pkcs7 parse  Operation: Pkcs7CertValidateGetSignerKeyHash
// 
// 2     5/10/11 6:57p Alexp
// include all Crypto related Guid Variable declarations
// 
// 1     5/06/11 6:11p Alexp
// initial module release
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  AmiDigitalSignature.h
//
// Description:	AMI Digital Signature Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __AMI_DIGITAL_SIGNATURE_DXE__H__
#define __AMI_DIGITAL_SIGNATURE_DXE__H__
#ifdef __cplusplus
extern "C" {
#endif

// All are EDKII defined headers
#include <Protocol/Hash.h>
#include <ImageAuthentication.h>

// Flags to define type of signature to process
#define EFI_CRYPT_RSASSA_PKCS1V15     1
#define EFI_CRYPT_RSASSA_PSS          2

///
/// SHA-1 digest size in bytes.
///
#define SHA1_DIGEST_SIZE    20
///
/// SHA-256 digest size in bytes
///
#define SHA256_DIGEST_SIZE  32

#define DEFAULT_RSA_KEY_MODULUS_LEN 256 // 2048 bits
#define DEFAULT_RSA_SIG_LEN DEFAULT_RSA_KEY_MODULUS_LEN // This is true as long as > data

#define AMI_DIGITAL_SIGNATURE_PROTOCOL_GUID  \
    { 0x5f87ba17, 0x957d, 0x433d, 0x9e, 0x15, 0xc0, 0xe7, 0xc8, 0x79, 0x88, 0x99 }

#define AMI_SMM_DIGITAL_SIGNATURE_PROTOCOL_GUID  \
    { 0x91ABC830, 0x16FC, 0x4D9E, 0xA1, 0x89, 0x5F, 0xC8, 0xBB, 0x41, 0x14, 0x02 }

GUID_VARIABLE_DECLARATION(gAmiDigitalSignatureProtocolGuid, AMI_DIGITAL_SIGNATURE_PROTOCOL_GUID);
GUID_VARIABLE_DECLARATION(gAmiSmmDigitalSignatureProtocolGuid, AMI_SMM_DIGITAL_SIGNATURE_PROTOCOL_GUID);

// Common Crypt construction type: ASN1 PubKey, Hash sha256, etc.
typedef struct{
    EFI_GUID AlgGuid;
    UINT32 BlobSize;
    UINT8 *Blob;
} CRYPT_HANDLE;

//**********************************************************************
//<AMI_THDR_START>
//
// Name:        PKCS7_OPERATIONS
//
// Description: Enumerated Pkcs7 Operations. 
//              List of different Pkcs7 verify tasks to perform:
//
// Fields:     Name                     Number  Description
//        ------------------------------------------------------------
//    Pkcs7Arg0                            0 Function presence check. Must return EFI_SUCCESS 
//    Pkcs7CertValidate                    1 Validate Certificate
//    Pkcs7GetSignerCert                   2 Return Signer Certificate in *Data. Performs cert chaining and time based validity tests
//    Pkcs7GetCACert                       3 Return Root CA certificate referenced by Signer. Used to compare with Trusted Cert in FW
//    Pkcs7ValidateRootCert                4 Validate Root Certificate
//    x509ValidateCertChain                5 Validate Signer Certificate Chain
//    Pkcs7GetDigestAlgorithm              6 Return Signature Digest Algorithm
//    Pkcs7CertValidateGetCACert           7 Validate Pkcs7 Cert, return Root CA Certificate
//    Pkcs7CertValidateGetSignerCert       8 Validate Pkcs7 Cert, return Signer Certificate
//    Pkcs7CertValidateGetSignerKeyHash    9 Validate Pkcs7 Cert, return Signer Key Hash (SHA256)
//    Pkcs7CertValidateGetMatchInCertChain 10 Validate Pkcs7 Cert and return Success if match is found between Trust and any leaf certificates in the Pkcs7 Signer chain
//    Pkcs7CertValidateGetSignerKey        11 Validate Pkcs7 Cert, return ptr in *Data to n-modulus of a Signer Key
//    Pkcs7CertGetMatchInCertChain         12 Return Success if match is found between Trust and any leaf certificates in the Signer chain
//    Pkcs7CertValidateGetCAKey            13 Validate Pkcs7 Cert, return ptr in *Data to n-modulus of a Root CA Key
//    Pkcs7GetCAKey                        14 Return ptr in *Data to n-modulus of a Root CA Key
//    Pkcs7GetSignerKey                    15 Return ptr in *Data to n-modulus of a Signer Key
//    Pkcs7TimeStampCertValidateGet        16 Validate TimeStamp certificate chain in Pkcs7 Certificate. Return TimeOfSigning
//<AMI_THDR_END>
//**********************************************************************
typedef enum {
    Pkcs7Arg0,
    Pkcs7CertValidate,
    Pkcs7GetSignerCert,
    Pkcs7GetCACert,
    Pkcs7ValidateRootCert,
    x509ValidateCertChain,
    Pkcs7GetDigestAlgorithm,
    Pkcs7CertValidateGetCACert,
    Pkcs7CertValidateGetSignerCert,
    Pkcs7CertValidateGetSignerKeyHash,
    Pkcs7CertValidateGetMatchInCertChain, // obsolete
    Pkcs7CertValidateGetSignerKey,
    Pkcs7CertGetMatchInCertChain,
    Pkcs7CertValidateGetCAKey,
    Pkcs7GetCAKey,
    Pkcs7GetSignerKey,
    Pkcs7TimeStampCertValidateGet
} PKCS7_OP;

typedef enum { SHA1, SHA256, SHA384, SHA512} HASH_ALG;

typedef struct _AMI_DIGITAL_SIGNATURE_PROTOCOL AMI_DIGITAL_SIGNATURE_PROTOCOL;

typedef 
EFI_STATUS
(EFIAPI *AMI_DIGITAL_SIGNATURE_PKCS1_VERIFY) (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN CRYPT_HANDLE *PublicKey,
  IN CRYPT_HANDLE *Hash,
  IN VOID *Signature,
  IN UINTN SignatureSize,
  IN UINT32 Flags
);

typedef 
EFI_STATUS
(EFIAPI *AMI_DIGITAL_SIGNATURE_PKCS7_VERIFY) (
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

typedef 
EFI_STATUS
(EFIAPI *AMI_DIGITAL_SIGNATURE_HASH) (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN CONST EFI_GUID *HashAlgorithm,
  IN UINTN Num_elem,
  IN CONST UINT8 *Addr[],
  IN CONST UINTN *Len,
  OUT UINT8 *Hash
);

typedef
EFI_STATUS
(EFIAPI *AMI_DIGITAL_SIGNATURE_GET_KEY) (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  OUT CRYPT_HANDLE *Key,
  IN EFI_GUID *AlgId,
  IN UINTN KeyLen,
  IN UINT32 Flags
  );

typedef
EFI_STATUS
(EFIAPI *AMI_DIGITAL_SIGNATURE_VERIFY_KEY) (
  IN CONST AMI_DIGITAL_SIGNATURE_PROTOCOL *This,
  IN EFI_GUID       *AlgId,
  IN CRYPT_HANDLE   *Key
  );
/*
Structure mutex
Mutual exclusion (mutex) semaphore locking mechanism used to serialise interthread intraprocess activities.

Usage example:
    mutex = identifier   

LOCK: 
    Lock the given mutex. Only one function owner can have the mutex locked at any time. 
    A caller that attempts to lock a mutex already locked by another caller will receive ACCESS_DENIED untill mutex owner unlocks the mutex.

UNLOCK:
    Unlock the given mutex. Other callers trying to lock the mutex/use the function will succeed.

RELEASE
    Releases Lock on exit from the function: 

CHECK:
    Does not change the state of Mutex Lock state
*/
typedef enum { RESET, LOCK, RELEASE, KEEP} RESET_MMGR;

typedef struct _AMI_DIGITAL_SIGNATURE_PROTOCOL  {
  AMI_DIGITAL_SIGNATURE_PKCS1_VERIFY Pkcs1Verify;
  AMI_DIGITAL_SIGNATURE_PKCS7_VERIFY Pkcs7Verify;
  AMI_DIGITAL_SIGNATURE_HASH Hash;
  AMI_DIGITAL_SIGNATURE_GET_KEY GetKey;
  AMI_DIGITAL_SIGNATURE_VERIFY_KEY VerifyKey;
};

//**********************************************************************
// NEW UEFI 2.3.1c hash types
//**********************************************************************
#ifndef EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID
#define EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID \
  { \
    0x24c5dc2f, 0x53e2,0x40ca,{0x9e, 0xd6, 0xa5, 0xd9,0xa4, 0x9f, 0x46, 0x3b} \
  }
#define EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID \
  { \
    0x8628752a, 0x6cb7, 0x4814, {0x96, 0xfc, 0x24, 0xa8,0x15, 0xac, 0x22, 0x26} \
  } 
GUID_VARIABLE_DECLARATION(gEfiHashAlgorithmSha1NoPadGuid,EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID); 
GUID_VARIABLE_DECLARATION(gEfiHashAlgorithmSha256NoPadGuid,EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID);
#endif
//**********************************************************************
// NEW TIME STAMP definitions ECR#1009
//**********************************************************************
#ifndef EFI_CERT_X509_SHA256_GUID
#define EFI_CERT_X509_SHA256_GUID \
  { 0x3bd2a492, 0x96c0, 0x4079, 0xb4, 0x20, 0xfc, 0xf9, 0x8e, 0xf1, 0x03, 0xed }
#define EFI_CERT_X509_SHA384_GUID \
  { 0x7076876e, 0x80c2, 0x4ee6, 0xaa, 0xd2, 0x28, 0xb3, 0x49, 0xa6, 0x86, 0x5b }
#define EFI_CERT_X509_SHA512_GUID \
  { 0x446dbf63, 0x2502, 0x4cda, 0xbc, 0xfa, 0x24, 0x65, 0xd2, 0xb0, 0xfe, 0x9d }

GUID_VARIABLE_DECLARATION(gEfiCertX509Sha256Guid, EFI_CERT_X509_SHA256_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertX509Sha384Guid, EFI_CERT_X509_SHA384_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertX509Sha512Guid, EFI_CERT_X509_SHA512_GUID);

typedef struct _EFI_CERT_X509_SHA256 {
    EFI_SHA256_HASH   ToBeSignedHash;
    EFI_TIME          TimeOfRevocation;
}  EFI_CERT_X509_SHA256;

typedef struct _EFI_CERT_X509_SHA384 {
    EFI_SHA384_HASH   ToBeSignedHash;
    EFI_TIME          TimeOfRevocation;
}  EFI_CERT_X509_SHA384;

typedef struct _EFI_CERT_X509_SHA512 {
    EFI_SHA512_HASH   ToBeSignedHash;
    EFI_TIME          TimeOfRevocation;
} EFI_CERT_X509_SHA512;

#endif
//**********************************************************************
// NEW TIME STAMP definitions ECR#1009
//**********************************************************************

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif // __AMI_DIGITAL_SIGNATURE_DXE__H__
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
//***********************************************************************
