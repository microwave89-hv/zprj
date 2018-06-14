//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Modules/CryptoPkg/Lib/Include/BaseCryptLib.h 1     6/13/11 5:19p Alexp $
//
// $Revision: 1 $
//
// $Date: 6/13/11 5:19p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/CryptoPkg/Lib/Include/BaseCryptLib.h $
// 
// 1     6/13/11 5:19p Alexp
// 
// 1     5/06/11 6:12p Alexp
// initial module release
// 
// 2     5/05/11 3:39p Alexp
// add Help hdrs
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		BaseCryptLib.h
//
// Description:	Defines base cryptographic library APIs compatible with EDK2 BaseCryptLib.
//  The Base Cryptographic Library provides implementations of basic cryptography
//  primitives (SHA-1, SHA-256, RSA, etc) for UEFI security functionality enabling.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __BASE_CRYPT_LIB_H__
#define __BASE_CRYPT_LIB_H__

#include <Efi.h>
//=====================================================================================
//    One-Way Cryptographic Hash Primitives
//=====================================================================================

///
/// SHA-1 digest size in bytes.
///
#define SHA1_DIGEST_SIZE    20
///
/// SHA-256 digest size in bytes
///
#define SHA256_DIGEST_SIZE  32

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Sha1GetContextSize
//
// Description: Retrieves the size, in bytes, of the context buffer required for SHA-1 hash operations.
//
// Input:none
//
// Output: The size, in bytes, of the context buffer required for SHA-1 hash operations.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN
Sha1GetContextSize (
  VOID
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Sha1Init
//
// Description: Initializes user-supplied memory pointed by Sha1Context as the SHA-1 hash context for
//  subsequent use. If Sha1Context is NULL, then ASSERT().
//
// Input:
//      param[in, out]  Sha1Context  Pointer to the SHA-1 Context being initialized.
//
// Output: 
//      retval TRUE  SHA-1 initialization succeeded.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Sha1Init (
  IN OUT  VOID  *Sha1Context
  );


/**
  Performs SHA-1 digest on a data buffer of the specified length. This function can
  be called multiple times to compute the digest of long or discontinuous data streams.

  If Sha1Context is NULL, then ASSERT().

  @param[in, out]  Sha1Context  Pointer to the SHA-1 context.
  @param[in]       Data         Pointer to the buffer containing the data to be hashed.
  @param[in]       DataLength   Length of Data buffer in bytes.

  @retval TRUE   SHA-1 data digest succeeded.
  @retval FALSE  Invalid SHA-1 context. After Sha1Final function has been called, the
                 SHA-1 context cannot be reused.

**/
BOOLEAN
Sha1Update (
  IN OUT  VOID        *Sha1Context,
  IN      CONST VOID  *Data,
  IN      UINTN       DataLength
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Sha1Final
//
// Description:   Completes SHA-1 hash computation and retrieves the digest value into the specified
//                memory. After this function has been called, the SHA-1 context cannot be used again.
//  If Sha1Context is NULL, then ASSERT().
//  If HashValue is NULL, then ASSERT().
//
// Input:
//  param[in, out]  Sha1Context  Pointer to the SHA-1 context
//  param[out]      HashValue    Pointer to a buffer that receives the SHA-1 digest
//                               value (20 bytes).
// Output: TRUE  SHA-1 digest computation succeeded.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Sha1Final (
  IN OUT  VOID   *Sha1Context,
  OUT     UINT8  *HashValue
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Sha256GetContextSize
//
// Description: Retrieves the size, in bytes, of the context buffer required for SHA256 hash operations.
//
// Input:none
// Output: The size, in bytes, of the context buffer required for SHA256 hash operations.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN
Sha256GetContextSize (
  VOID
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Sha256Init
//
// Description: Initializes user-supplied memory pointed by Sha256Context as SHA-256 hash context for
//  subsequent use. If Sha256Context is NULL, then ASSERT().
//
// Input:
//      param[in, out]  Sha256Context  Pointer to the SHA-1 Context being initialized.
//
// Output: 
//      retval TRUE  SHA-256 context initialization succeeded.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Sha256Init (
  IN OUT  VOID  *Sha256Context
  );


/**
  Performs SHA-256 digest on a data buffer of the specified length. This function can
  be called multiple times to compute the digest of long or discontinuous data streams.

  If Sha256Context is NULL, then ASSERT().

  @param[in, out]  Sha256Context  Pointer to the SHA-256 context.
  @param[in]       Data           Pointer to the buffer containing the data to be hashed.
  @param[in]       DataLength     Length of Data buffer in bytes.

  @retval TRUE   SHA-256 data digest succeeded.
  @retval FALSE  Invalid SHA-256 context. After Sha256Final function has been called, the
                 SHA-256 context cannot be reused.

**/
BOOLEAN
Sha256Update (
  IN OUT  VOID        *Sha256Context,
  IN      CONST VOID  *Data,
  IN      UINTN       DataLength
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Sha256Final
//
// Description:  Completes SHA-256 hash computation and retrieves the digest value into the specified
//               memory. After this function has been called, the SHA-256 context cannot be used again.
//  If Sha256Context is NULL, then ASSERT().
//  If HashValue is NULL, then ASSERT().
//
// Input:
//  param[in, out]  Sha256Context  Pointer to SHA-256 context
//  param[out]      HashValue      Pointer to a buffer that receives the SHA-256 digest
//                                 value (32 bytes).
// Output: TRUE  SHA-256 digest computation succeeded.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Sha256Final (
  IN OUT  VOID   *Sha256Context,
  OUT     UINT8  *HashValue
  );


//=====================================================================================
//    MAC (Message Authentication Code) Primitive
//=====================================================================================

///
/// No MAC supports for minimum scope required by UEFI
///


//=====================================================================================
//    Symmetric Cryptography Primitive
//=====================================================================================

///
/// No symmetric cryptographic supports for minimum scope required by UEFI
///


//=====================================================================================
//    Asymmetric Cryptography Primitive
//=====================================================================================
#define DEFAULT_RSA_KEY_MODULUS_LEN 256 // 2048 bits
#define DEFAULT_RSA_SIG_LEN DEFAULT_RSA_KEY_MODULUS_LEN // This is true as long as > data

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RsaNew
//
// Description:  Allocates and Initializes one RSA Context for subsequent use.
//
// Input:
//
// Output: Pointer to the RSA Context that has been initialized.
//         If the allocations fails, RsaNew() returns NULL.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *
RsaNew (
  VOID
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RsaFree
//
// Description:  Release the specified RSA Context.
//
// Input:
//         param[in]  RsaContext  Pointer to the RSA context to be released.
//
// Output: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
EFIAPI
RsaFree (
  IN  VOID  *RsaContext
  );


///
/// RSA Key Tags Definition used in RsaSetKey() function for key component identification.
///
typedef enum _RSA_KEY_TAG {
  RsaKeyN,      ///< RSA public Modulus (N)
  RsaKeyE,      ///< RSA Public exponent (e)
  RsaKeyD,      ///< RSA Private exponent (d)
  RsaKeyP,      ///< RSA secret prime factor of Modulus (p)
  RsaKeyQ,      ///< RSA secret prime factor of Modules (q)
  RsaKeyDp,     ///< p's CRT exponent (== d mod (p - 1))
  RsaKeyDq,     ///< q's CRT exponent (== d mod (q - 1))
  RsaKeyQInv    ///< The CRT coefficient (== 1/q mod p)
} RSA_KEY_TAG;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RsaSetKey
//
// Description:  Sets the tag-designated RSA key component into the established RSA context from
//  the user-specified nonnegative integer (octet string format represented in RSA
//  PKCS#1).   If RsaContext is NULL, then ASSERT().
//
// Input:
//  @param[in, out]  RsaContext  Pointer to RSA context being set.
//  @param[in]       KeyTag      Tag of RSA key component being set.
//  @param[in]       BigNumber   Pointer to octet integer buffer.
//  @param[in]       BnLength    Length of big number buffer in bytes.
//
// Output: 
//  @return  TRUE   RSA key component was set successfully.
//  @return  FALSE  Invalid RSA key component tag.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
RsaSetKey (
  IN OUT VOID         *RsaContext,
  IN     RSA_KEY_TAG  KeyTag,
  IN     CONST UINT8  *BigNumber,
  IN     UINTN        BnLength
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RsaPkcs1Verify
//
// Description:    Verifies the RSA-SSA signature with EMSA-PKCS1-v1_5 encoding scheme defined in
//  RSA PKCS#1.
//  If RsaContext is NULL, then ASSERT().
//  If MessageHash is NULL, then ASSERT().
//  If Signature is NULL, then ASSERT().
//  If HashLength is not equal to the size of SHA-1 or SHA-256 digest, then ASSERT().
//
// Input:
//  @param[in]  RsaContext   Pointer to RSA context for signature verification.
//  @param[in]  MessageHash  Pointer to octet message hash to be checked.
//  @param[in]  HashLength   Length of the message hash in bytes.
//  @param[in]  Signature    Pointer to RSA PKCS1-v1_5 signature to be verified.
//  @param[in]  SigLength    Length of signature in bytes.
//
// Output: 
//  @return  TRUE   Valid signature encoded in PKCS1-v1_5.
//  @return  FALSE  Invalid signature or invalid RSA context.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
RsaPkcs1Verify (
  IN  VOID         *RsaContext,
  IN  CONST UINT8  *MessageHash,
  IN  UINTN        HashLength,
  IN  UINT8        *Signature,
  IN  UINTN        SigLength
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Pkcs7Verify
//
// Description: Verifies the validility of a PKCS#7 signed data as described in 
//              "PKCS #7: Cryptographic Message Syntax Standard".
//  If P7Data is NULL, then ASSERT().
//
// Input:
//  @param[in]  P7Data       Pointer to the PKCS#7 message to verify.
//  @param[in]  P7Length     Length of the PKCS#7 message in bytes.
//  @param[in]  TrustedCert  Pointer to a trusted/root certificate encoded in DER, which
//                           is used for certificate chain verification.
//  @param[in]  CertLength   Length of the trusted certificate in bytes.
//  @param[in]  InData       Pointer to the content to be verified.
//  @param[in]  DataLength   Length of InData in bytes.
//
// Output: 
//  @return  TRUE  The specified PKCS#7 signed data is valid.
//  @return  FALSE Invalid PKCS#7 signed data.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Pkcs7Verify (
  IN  CONST UINT8  *P7Data,
  IN  UINTN        P7Length,
  IN  CONST UINT8  *TrustedCert,
  IN  UINTN        CertLength,
  IN  CONST UINT8  *InData,
  IN  UINTN        DataLength
  );


#endif // __BASE_CRYPT_LIB_H__
