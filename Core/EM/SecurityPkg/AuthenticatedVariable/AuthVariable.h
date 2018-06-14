//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SecureBoot_WIN8/AuthenticatedVariable_efi/AuthVariable.h 17    3/09/15 4:27p Alexp $
//
// $Revision: 17 $
//
// $Date: 3/09/15 4:27p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureBoot_WIN8/AuthenticatedVariable_efi/AuthVariable.h $
// 
// 17    3/09/15 4:27p Alexp
// Update year 2015 in the file header
// 
// 16    2/08/13 5:15p Alexp
// Optimized the code flow fro Auth2 Variables.
// 
// 15    12/07/12 3:45p Alexp
// define AVAR_TRACE macro
// 
// 14    11/19/12 4:41p Alexp
// Fix for Win8 SecureBoot logo requirement: restore Secure Boot state
// across flash updates.
// Move all secure boot Setup settings to a separate varstore variable. 
// Preserve var across re-flash
// 
// 13    10/16/12 3:45p Alexp
// Implemented  R/O Variables support via fixed and OEM defined (eLink)
// lists
// 
// 12    8/27/12 10:42a Alexp
// GetmSecureBootSupport(): 
// Add input parameter SetupMode to control state of 
// Setup Flag:SecureBootSupport
// 
// 11    2/27/12 6:52p Alexp
// removed AuthenticatedVariableServiceInitialize() 
// 
// 10    2/03/12 9:56a Alexp
// EIP#82122. WHCK "Secure Boot Manual Logo Test" fails
// Fixed Append logic to process multiple sig data instances in a single
// Signature List block
// New logic will remove dupplicated certs and update new SigList header.
// 
// 9     8/18/11 5:59p Alexp
// renamed func SecureBootSupport()
// 
// 8     8/18/11 4:53p Alexp
// removed AuthVar mailbox
// 
// 7     8/16/11 7:18p Alexp
// added Mailbox variable AuthVarMAilbox to syncronize local state between
// DXE and SMM AuthVariable services
// 
// 6     8/05/11 3:12p Alexp
// add mkime prototyte define
// 
// 5     8/04/11 7:12p Alexp
// 
// 4     6/30/11 4:02p Alexp
// added Callback event on Setup Mode change request form Security Setup
// Page.
// 
// 3     6/24/11 7:04p Alexp
// fixed ValidateSignatureList () logic. Added Certificate RSA2048 to
// supported Signatures
// 
// 2     6/23/11 6:19p Alexp
// Added ValidateSigList() function
// 
// 5     6/09/11 5:49p Alexp
// add new parameter to ValidateSelfSigned  - Operation.
// 
// 4     6/02/11 5:52p Alexp
// add ValidateSelfSigned certificates func definition
// 
// 2     5/19/11 4:59p Alexp
// Major code revamp to be able to handle of handling Secure vars in Setup
// Mode
// TBD: TimeBased certificates from Msft fail to process. Not compiled as
// Authenticode format 
// 
// 4     3/31/11 6:28p Alexp
// Add SHA256 to supported SignatureList
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  AuthVariable.h Implement authentication services for the authenticated variable
//                       service in UEFI2.2+
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _AUTHVARIABLE_H_
#define _AUTHVARIABLE_H_

#include <Efi.h>
// All are EDKII defined headers
#include "WinCertificate.h"
#include "ImageAuthentication.h"
#include <Protocol/Hash.h>

#define HASH_SHA256_LEN                   sizeof(EFI_SHA256_HASH)     // 32
#define HASH_SHA1_LEN                     sizeof(EFI_SHA1_HASH)
#define RSA2048_PUB_KEY_LEN               DEFAULT_RSA_KEY_MODULUS_LEN // 256
#define EFI_CERT_TYPE_RSA2048_SHA256_SIZE RSA2048_PUB_KEY_LEN
#define EFI_CERT_TYPE_RSA2048_SIZE        RSA2048_PUB_KEY_LEN

//
// EFI_VARIABLE_AUTHENTICATION descriptor
//
// A authentication authentication method descriptor template
//  AuthInfo is a WIN_CERTIFICATE using the wCertificateType
//  WIN_CERTIFICATE_UEFI_GUID and the CertType
//  EFI_CERT_TYPE_RSA2048_SHA256.
//
#ifndef EFI_VARIABLE_AUTHENTICATION
typedef struct {
    UINT64 MonotonicCount;
    WIN_CERTIFICATE_UEFI_GUID            AuthInfo;
} EFI_VARIABLE_AUTHENTICATION;
#endif

//
// EFI_VARIABLE_AUTHENTICATION_2 descriptor
//
// A time-based authentication method descriptor template
//
#ifndef EFI_VARIABLE_AUTHENTICATION_2
typedef struct {
    EFI_TIME                            TimeStamp;
    WIN_CERTIFICATE_UEFI_GUID           AuthInfo;
} EFI_VARIABLE_AUTHENTICATION_2;
#endif

///
/// Size of AuthInfo prior to the data payload
///
#define AUTHINFO_SIZE(Cert) (((UINTN)(((EFI_VARIABLE_AUTHENTICATION *) Cert)->AuthInfo.Hdr.dwLength)) + sizeof(UINT64))
#define AUTHINFO_2_SIZE(Cert) (((UINTN)(((EFI_VARIABLE_AUTHENTICATION_2 *) Cert)->AuthInfo.Hdr.dwLength)) + sizeof(EFI_TIME))

#ifdef EFI_DEBUG
#define AVAR_TRACE(Arguments) { if (!AVarRuntime) TRACE(Arguments); }
#else
#define AVAR_TRACE(Arguments)
#endif


typedef enum {
    IsPkVarType = 0,
    IsKekVarType,
    IsDbVarType,
    IsPrivateVarType
} AUTHVAR_TYPE;

VOID AuthVariableServiceInitSMM (VOID );
VOID AuthVariableServiceInit ( VOID );

EFI_STATUS VerifyVariable (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32   *Attributes,
    IN VOID    **Data,
    IN UINTN    *DataSize, 
    IN VOID     *OldData,   
    IN UINTN     OldDataSize,
    IN OUT EXT_SEC_FLAGS *ExtFlags
    );

EFI_STATUS FindInSignatureDb (
    IN EFI_GUID *VendorGuid,
    IN UINT32    Attributes,
    IN VOID     *Data,
    IN UINTN    *DataSize,
    IN VOID     *SigDB,
    IN UINTN     SigDBSize
    );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Variable Auth Hdr EFI_VARIABLE_AUTHENTICATION
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
EFI_STATUS VerifyVariable1 (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32    Attributes,
    IN VOID    **Data,
    IN UINTN    *DataSize, 
    IN VOID     *OldData,
    IN UINTN     OldDataSize,
    IN OUT EXT_SEC_FLAGS *ExtFlags
    );

EFI_STATUS VerifyDataPayload (
    IN VOID     *Data,
    IN UINTN    DataSize, 
    IN UINT8    *PubKey
    );

EFI_STATUS ProcessVarWithPk (
    IN  VOID        *Data,
    IN  UINTN        DataSize,
    IN  UINT32       Attributes,
    IN  BOOLEAN      IsPk
    );

EFI_STATUS ProcessVarWithKek (
    IN  VOID        *Data,
    IN  UINTN        DataSize,
    IN  UINT32       Attributes
    );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Variable Auth Hdr EFI_VARIABLE_AUTHENTICATION_2
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
EFI_STATUS VerifyVariable2 (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32    Attributes,
    IN VOID    **Data,
    IN UINTN    *DataSize, 
    IN VOID     *OldData,
    IN UINTN     OldDataSize,
    IN OUT EXT_SEC_FLAGS *ExtFlags
    );

EFI_STATUS ValidateSelfSigned (
    IN UINT8     *Pkcs7Cert,
    IN UINTN      Pkcs7Cert_len,
    IN OUT UINT8 **pDigest,
    IN OUT UINTN  *Digest_len,
    IN UINT8       Operation
    );

EFI_STATUS ConstructDataParameter (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32    Attributes,
    IN VOID     *Data,
    IN UINTN     DataSize, 
    OUT UINT8   *pDigest,
    OUT UINTN   *Digest_len,
    IN  UINT8    Mutex    
    );

EFI_STATUS ProcessVarWithPk2 (
    IN  UINT8     *Pkcs7Cert,
    IN  UINTN      Pkcs7Cert_len,
    IN  UINT8     *pDigest,
    IN  UINTN      Digest_len
    );

EFI_STATUS ProcessVarWithKek2 (
    IN  UINT8     *Pkcs7Cert,
    IN  UINTN      Pkcs7Cert_len,
    IN  UINT8     *pDigest,
    IN  UINTN      Digest_len
    );

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Misc auxilary functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

INTN StrCmp16(CHAR16 *Dest, CHAR16 *Src);
UINT32 StrSize16(CHAR16 *String);

BOOLEAN IsPkVar(
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid
    );

BOOLEAN IsKekVar(
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid
    );

BOOLEAN IsDbVar(
    IN EFI_GUID *VendorGuid
    );

EFI_STATUS GetPlatformMode (
    VOID
    );

EFI_STATUS GetmSecureBootSupport (
    UINT8
    );

VOID  UpdatePlatformMode (
    IN  UINT8 Mode
    );

EFI_STATUS ValidateSignatureList (
    IN VOID     *Data,
    IN UINTN     DataSize
);

UINT64 mkLongTime ( 
    EFI_TIME *TimeStamp 
);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NVRAM module defined auxilary functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

EFI_STATUS FindVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID **Data
    );

EFI_STATUS DxeSetVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
);
EFI_STATUS DxeGetVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID *Data
);

#endif  // _AUTHVARIABLE_H_
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
