//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Modules/CryptoPkg/PPI/CryptoPPI.h 2     11/13/12 11:47a Alexp $
//
// $Revision: 2 $
//
// $Date: 11/13/12 11:47a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/CryptoPkg/PPI/CryptoPPI.h $
// 
// 2     11/13/12 11:47a Alexp
// EIP#105015
// Add GUID defines for x509 Public Key file type and 
// Pkcs#7 Cert verification function in Crypto PPI
// 
// 1     6/13/11 5:19p Alexp
// 
// 1     5/06/11 6:11p Alexp
// initial module release
// 
// 3     4/11/11 12:53p Alexp
// remove Verify Capsule from Crypto PPI.
// 
// 2     3/10/11 4:53p Alexp
// 
// 1     2/28/11 6:46p Alexp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  CryptoPPI.h
//
// Description:	AMI Digital Signature Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef ___AMI_DIGITAL_SIGNATURE_PEI__H__
#define ___AMI_DIGITAL_SIGNATURE_PEI__H__

#ifdef __cplusplus
extern "C" {
#endif

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

#define AMI_DIGITAL_SIGNATURE_PPI_GUID \
    { 0x86c29aa5, 0xdb0, 0x4343, 0xbd, 0x52, 0x7a, 0x72, 0x9f, 0x37, 0xc9, 0x6d }

GUID_VARIABLE_DECLARATION(gAmiDigitalSignaturePPIGuid, AMI_DIGITAL_SIGNATURE_PPI_GUID);

typedef struct _AMI_CRYPT_DIGITAL_SIGNATURE_PPI AMI_CRYPT_DIGITAL_SIGNATURE_PPI;

typedef struct{
    EFI_GUID   AlgGuid;
    UINT32     BlobSize;
    UINT8      *Blob;
} PEI_CRYPT_HANDLE;

typedef 
EFI_STATUS
(EFIAPI *PEI_CRYPT_DS_VERIFY_SIG) (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN PEI_CRYPT_HANDLE        *PublicKey,
  IN PEI_CRYPT_HANDLE        *Hash,
  IN VOID                    *Signature,
  IN UINTN                    SignatureSize,
  IN UINT32                   Flags
  );

typedef 
EFI_STATUS
(EFIAPI *PEI_CRYPT_DS_VERIFY_PKCS7SIG) (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN CONST UINT8 *P7Data,
  IN UINTN        P7Size,
  IN CONST UINT8 *TrustedCert,
  IN UINTN        CertSize,
  IN OUT UINT8  **Data,
  IN OUT UINTN   *DataSize
  );

typedef 
EFI_STATUS
(EFIAPI *PEI_CRYPT_DS_GET_KEY) (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN CONST EFI_GUID          *KeyAlgorithm, // supported PKPUB_KEY_GUID only
  IN PEI_CRYPT_HANDLE        *PublicKey
  );

typedef 
EFI_STATUS
(EFIAPI *PEI_CRYPT_DS_VERIFY_KEY) (
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN CONST EFI_GUID          *KeyAlgorithm, // supported PKPUB_KEY_GUID only
  IN PEI_CRYPT_HANDLE        *PublicKey
  );

typedef
EFI_STATUS
(EFIAPI *PEI_CRYPT_DS_HASH)(
  IN CONST AMI_CRYPT_DIGITAL_SIGNATURE_PPI *This,
  IN CONST EFI_GUID          *HashAlgorithm,
  IN UINTN                    num_elem,
  IN CONST UINT8             *addr[],
  IN CONST UINTN             *len,
  OUT UINT8                  *Hash
  );    

typedef struct _AMI_CRYPT_DIGITAL_SIGNATURE_PPI  {
  PEI_CRYPT_DS_HASH           Hash;
  PEI_CRYPT_DS_VERIFY_KEY     VerifyKey; // compares Key with Platform Signing key(PKpub)
  PEI_CRYPT_DS_VERIFY_SIG     VerifySig; // Rsa2048_sha256 Pkcs1v1.5
  PEI_CRYPT_DS_GET_KEY        GetKey;  
  PEI_CRYPT_DS_VERIFY_PKCS7SIG   VerifyPkcs7Sig;
};
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif // ___AMI_DIGITAL_SIGNATURE_PEI__H__
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
