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
// $Header: /Alaska/BIN/Modules/CryptoPkg/Lib/Include/CryptLib.h 6     1/16/14 5:14p Alexp $
//
// $Revision: 6 $
//
// $Date: 1/16/14 5:14p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/CryptoPkg/Lib/Include/CryptLib.h $
// 
// 6     1/16/14 5:14p Alexp
// fix parameter inside pkcs_1_v1_5_decode()
// 
// 5     8/15/13 9:45a Alexp
// Expose TimeStamp validation functions: 
// Pkcs7_certificate_validate_timestamp_digest, 
// os_mktime, 
// Pkcs7_x509_certificate_chain_validate_with_timestamp
// 
// 4     5/22/13 10:36a Alexp
// expose MD5 hash librray function: md5_vector()
// 
// 3     11/20/12 2:31p Alexp
// New function to update default EfiTime for Pkcs7 operations
// set_crypt_efitime(EFI_TIME*)
// 
// 2     8/15/12 4:22p Alexp
// Added new lib function:Pkcs7_x509_return_Cert_pubKey()
// Used to extract n-Modulus of a pub key withinn given x509 Key
// certificate
// 
// 1     6/13/11 5:19p Alexp
// 
// 2     6/10/11 6:22p Alexp
// added new Pkcs7 parse  Operation: Pkcs7CertValidateGetSignerKeyHash
// 
// 1     5/06/11 6:12p Alexp
// initial module release

// 
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		CryptLib.h
//
// Description:	Defines Aptio cryptographic library APIs.
//  This Cryptographic Library provides implementations of basic and extended cryptography
//  primitives (SHA-1, SHA-256, RSA, x509, PKCS7, ASN1.1) for UEFI security functionality enabling.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef CRYPTOLIB_H
#define CRYPTOLIB_H

#if defined(_WIN64)
//typedef unsigned __int64        size_t;
#else
typedef unsigned int            size_t;
#endif

// Common Crypto Lib API
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RuntimeCryptLibConstructorInSMM
//
// Description: Init Crypto lib internal state. 
//              This function is called from outside of SMM during SMM registration.
//
// Input:
//  IN EFI_HANDLE       ImageHandle
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RuntimeCryptLibConstructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);
EFI_STATUS RuntimeCryptLibConstructorInSmm(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   wpa_set_trace_level
//
// Description: sets the debug message print mode
//
// Input:
//  level: print level: 0 - no messages, 1 - minimal, 2 - full
//
// Output: none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID wpa_set_trace_level(int level);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   set_crypt_efitime
//
// Description: updates the local value of crypto EfiTime 
//
// Input:
//  *EFI_TIME
//
// Output: none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID set_crypt_efitime(EFI_TIME *EfiTime);

// 0. auxilary Memory Manager 
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    InitCRmm
//
// Description:    Initializes Crypo Memory Manager 
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
void InitCRmm(void* pHeap, UINTN HeapSize);
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    ResetCRmm
//
// Description:    Resets Crypto Memory Manager. Clears mem heap and descriptors
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
void ResetCRmm();

// 1. Rsa Public Key import
//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:  crypto_import_rsa2048_public_key
//
// Description:	Imports RSA2048 public key binary from RAW format into internal crypto_rsa_key data structure
//
// Input:
//  KeyN      - Pointer to N public modulus buffer
//  KeyE      - Pointer to E public exponent buffer
//  LenN      - Size of KeyN buffer (must be 256)
//  LenE      - Size of KeyE buffer
//
// Output:	  Pointer to Key data structure crypto_rsa_key 
//            NULL if failed to import Key
//
//**********************************************************************
//<AMI_PHDR_END>
struct crypto_rsa_key *crypto_import_rsa2048_public_key(const UINT8 *KeyN, size_t lenN,
                        const UINT8 *KeyE, size_t lenE);
//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:  crypto_import_asn1_public_key
//
// Description:	Imports RSA2048 public key from ASN.1 DER format into 
//              internal crypto_rsa_key data structure
//
// Input:
//  key       - Pointer to public key buffer
//  len       - Size of key buffer
//
// Output:	  Pointer to Key data structure crypto_rsa_key 
//            NULL if failed to import Key
//
//**********************************************************************
//<AMI_PHDR_END>
struct crypto_rsa_key *crypto_import_asn1_public_key(const UINT8 *key, size_t len);

//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:  base64_decode
//
// Description:	Do in-place decoding of base-64 data of LENGTH in BUFFER.
//
// Input:
//  buffer       - Data to be decoded
//  length       - Length of the data to be decoded
//
// Output:	  New length of the buffer bytes of decoded data,
//            or -1 n failure
//
//**********************************************************************
//<AMI_PHDR_END>
size_t	base64_decode (char *buffer, size_t length);

// 2. RSA Exponentiation
//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:  crypto_rsa_exptmod
//
// Description:	RSA modular exponentiation
//
// Input:
//  in: Input data
//  inlen: Input data length
//  out: Buffer for output data
//  outlen: Maximum size of the output buffer and used size on success
//  key: RSA key
//  use_private: 1 = Use RSA private key, 0 = Use RSA public key
//
// Output:	  0 on success, -1 on failure
//
//**********************************************************************
//<AMI_PHDR_END>
int crypto_rsa_exptmod(const UINT8 *in, size_t inlen, UINT8 *out, size_t *outlen,
                       struct crypto_rsa_key *key, int use_private);

// 3. PKCS#1 Signatures
//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:  pkcs_1_pss_decode
//
// Description:	PKCS #1 v2.00 PSS sig decode
//
// Input:
//   msghash         The hash to verify
//   msghashlen      The length of the hash (octets)
//   sig             The signature data (encoded data)
//   siglen          The length of the signature data (octets)
//   saltlen         The length of the salt used (octets)
//   modulus_bitlen  The bit length of the RSA modulus
//
// Output:	  CRYPT_OK if successful (even if the comparison failed)
//
//**********************************************************************
//<AMI_PHDR_END>
int pkcs_1_pss_decode(const unsigned char *msghash, unsigned long msghashlen,
                      const unsigned char *sig,     unsigned long siglen,
                      unsigned long saltlen,  unsigned long modulus_bitlen);
//<AMI_PHDR_START>
//**********************************************************************
//
// Procedure:  pkcs_1_v1_5_decode
//
// Description:	 Strip PKCS #1 header 
//
// Input:   Sig              The encoded data to decode
//          siglen          The length of the encoded data (octets)
//
// Output:	  CRYPT_OK if successful
//
//**********************************************************************
//<AMI_PHDR_END>
int pkcs_1_v1_5_decode(const UINT8 *hash, size_t hashlen, const UINT8 *sig, unsigned long siglen);

// 4. SHA hashing
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    md5_vector
//
// Description:    MD5 hash for data vector
//
// Input:
//  num_elem: Number of elements in the data vector
//  addr: Pointers to the data areas
//  len: Lengths of the data blocks
//  mac: Buffer for the hash
//
// Output:	  none
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
void md5_vector(size_t num_elem, const UINT8 *addr[], const size_t *len, UINT8 *mac);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    sha1_vector
//
// Description:    SHA-1 hash for data vector
//
// Input:
//  num_elem: Number of elements in the data vector
//  addr: Pointers to the data areas
//  len: Lengths of the data blocks
//  mac: Buffer for the hash
//
// Output:	  none
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
void sha1_vector(size_t num_elem, const UINT8 *addr[], const size_t *len, UINT8 *mac);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    sha256_vector
//
// Description:    SHA256 hash for data vector
//
// Input:
//  num_elem: Number of elements in the data vector
//  addr: Pointers to the data areas
//  len: Lengths of the data blocks
//  mac: Buffer for the hash
//
// Output:	  none
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
void sha256_vector(size_t num_elem, const UINT8 *addr[], const size_t *len, UINT8 *mac);

// 5. Pkcs7/x509 certificates
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    x509_certificate_parse
//
// Description:    Parse a X.509 certificate in DER format
// Caller is responsible for freeing the returned certificate by calling
// x509_certificate_free().
//
// Input:
// buf: Pointer to the X.509 certificate in DER format
// len: Buffer length
//
// Output:	  Pointer to the parsed certificate or %NULL on failure
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
struct x509_certificate *x509_certificate_parse(const UINT8 *buf, size_t len);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    x509_certificate_chain_validate
//
// Description:    Validate X.509 certificate chain
//
// Input:
// trusted: List of trusted certificates
// chain: Certificate chain to be validated (first chain must be issued by
// igned by the second certificate in the chain and so on)
// reason: Buffer for returning failure reason (X509_VALIDATE_*)
//
// Output:	  0 if chain is valid, -1 if not
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
int x509_certificate_chain_validate(struct x509_certificate *trusted, struct x509_certificate *chain, int *reason);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_parse_Authenticode_certificate
//
// Description:    Parse a Pkcs7 Authenticode certificate in DER format
// Caller is responsible for freeing the returned certificate by calling
// Pkcs7_certificate_free().
//
// Input:
// buf: Pointer to the Pkcs7 Authenticode SignedData in DER format
// len: Buffer length
//
// Output:	  Pointer to the parsed certificate or %NULL on failure
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
struct pkcs7_signed_data_st * Pkcs7_parse_Authenticode_certificate(const UINT8 *buf, size_t len);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_certificate_validate_digest
//
// Description:    Verify certificate signature
//
// Input:
//  SignedData: Complete PKCS certificate
//  SignCert: Signing certificate containing the public key
//
// Output:	  0 if cert has a valid signature that was signed by the issuer, -1 if not
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
int Pkcs7_certificate_validate_digest(struct pkcs7_signed_data_st *SignedData, struct x509_certificate *SignCert,
                            UINT8 *fileHash, size_t hashLen);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    PKCS7_return_signing_cerificate
//
// Description:    Return certificate with signer's public key
//
// Input:
//  SignedData: List of trusted certificates
//
// Output:	  cert if chain is valid, NULL if not found
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
struct x509_certificate 
    * Pkcs7_return_signing_cerificate(struct pkcs7_signed_data_st *SignedData);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_return_timestamp_signing_cerificate
//
// Description:    Return timestamps root signing certificate
//
// Input:
//  SignedData: List of trusted certificates
//
// Output:	  cert if chain is valid, NULL if not found
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
struct x509_certificate 
    * Pkcs7_return_timestamp_signing_cerificate(struct pkcs7_signed_data_st *SignedData);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_x509_certificate_chain_validate
//
// Description:    Validate Pkcs7 certificate chain
//
// Input:
// trusted: List of trusted certificates
// chain: Certificate chain to be validated (first chain must be issued by
// igned by the second certificate in the chain and so on)
// reason: Buffer for returning failure reason (X509_VALIDATE_*)
//
// Output:	  0 if chain is valid, -1 if not
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
int Pkcs7_x509_certificate_chain_validate(struct pkcs7_signed_data_st *SignedData, 
        struct x509_certificate *trusted, int *reason);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_return_cerificate_ptr
//
// Description:    Return pointer within DER buffer to:
//  1. Signing certificate 
//  2. Root CA certificate that is used to sign Signing certificate
//
// Input:
// SignedData: List of trusted certificates
//
// Output:	  cert if chain is valid, -1 if not found
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
int Pkcs7_return_cerificate_ptr(struct pkcs7_signed_data_st *SignedData, 
        UINT8** CAcert, size_t* CAcert_len, 
        UINT8** SignCert, size_t* SignCert_len);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_x509_return_signing_Key
//
// Description:    Extract n-Modulus of a Signing Key from x509 certificate
//
// Input:
// SignedData: Pkcs7 certificate structure
//
// Output:	  0-key present, -1 if not found
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
int Pkcs7_x509_return_signing_Key(struct pkcs7_signed_data_st *SignedData,
	UINT8 **public_key, size_t *public_key_len);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_x509_return_Cert_pubKey
//
// Description:    Extract n-Modulus from an x509 Key certificate
//
// Input:
// pCert: DER encoded x509 certificate
//
// Output:	  0-key present, -1 if not found
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
int Pkcs7_x509_return_Cert_pubKey(UINT8 *pCert, size_t cert_len,
    UINT8 **public_key, size_t *public_key_len);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_return_digestAlgorithm
//
// Description:    Return digestAlgorithm type
//
// Input:
// PKCS7cert: Pkcs7 certificate structure
//
// Output:	  cert if chain is valid, -1 if not found
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
int Pkcs7_return_digestAlgorithm(struct pkcs7_signed_data_st *PKCS7cert, UINT8* HashType);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure: Pkcs7_x509_certificate_chain_validate_with_timestamp
//
// Description:	Common routine to validate Pkcs7 certificate chain and revoked time stamped certs
//				Supported RFC6131 TimeStampToken format
// Input:
// SignedData: Pkcs7 certificate chain to be validated (first chain must be issued by
// signed by the second certificate in the chain and so on)
// trusted   : List of trusted x509 certificates
// revokeInfo: Hash certificate
// action: Buffer for returning either result of operation or intermediate data, e.g TimeOfSigning
//
// Output:	  0 if chain is valid, -1 if not
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
typedef struct pkcs7_cert_revoke_info {
    UINT8   *ToBeSignedHash;
    size_t   ToBeSignedHashLen;
};
int Pkcs7_x509_certificate_chain_validate_with_timestamp(
                    struct pkcs7_signed_data_st *SignedData,
                    BOOLEAN bTimeStampCert,
                    struct x509_certificate *trusted,
                    struct pkcs7_cert_revoke_info *revokeInfo,
                    int *action);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:     os_mktime - Convert broken-down time into seconds since 1970-01-01
//
//  Input:
//  year: Four digit year
//  month: Month (1 .. 12)
//  day: Day of month (1 .. 31)
//  hour: Hour (0 .. 23)
//  min: Minute (0 .. 59)
//  sec: Second (0 .. 60)
//  @t: Buffer for returning calendar time representation 
//      (seconds since 1970-01-01 00:00:00)
//
// Output: int 
//      0 on success, -1 on failure
//
// Note: The result is in seconds from Epoch, i.e., in UTC, not in local time
//       which is used by POSIX mktime().

//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
typedef long os_time_t;
int os_mktime(int year, int month, int day, int hour, int min, int sec,
              os_time_t *t);

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    Pkcs7_certificate_validate_timestamp_digest
//
// Description: Validate RFC6131 TimeStampToken digest
//
// Input: PKCS7 Certificate
//
// Output:    0 if chain is valid, -1 if not
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
int Pkcs7_certificate_validate_timestamp_digest(struct pkcs7_signed_data_st *SignedData, os_time_t *TimeOfSign);

#endif /* CRYPTOLIB_H */
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
