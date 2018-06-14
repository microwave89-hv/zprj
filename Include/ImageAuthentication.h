//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/ImageAuthentication.h 3     5/22/12 10:21a Artems $
//
// $Revision: 3 $
//
// $Date: 5/22/12 10:21a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/ImageAuthentication.h $
// 
// 3     5/22/12 10:21a Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Keep guid definitions in sync with UEFI 2.3.1 spec and
// EDK II implementation
// [Files]  		ImageAuthentication.h
// 
// 2     5/13/11 3:56p Artems
// AMI coding standard compliance added
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<ImageAuthentication.h>
//
// Description:	Image Authentication definitions header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __IMAGE_AUTHTICATION_H__
#define __IMAGE_AUTHTICATION_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <WinCertificate.h>

#define EFI_IMAGE_SECURITY_DATABASE_GUID \
  { 0xd719b2cb, 0x3d3a, 0x4596, 0xa3, 0xbc, 0xda, 0xd0, 0xe, 0x67, 0x65, 0x6f }


#define EFI_IMAGE_SECURITY_DATABASE       L"db"
#define EFI_IMAGE_SECURITY_DATABASE1      L"dbx"

#define SETUP_MODE                        1
#define USER_MODE                         0

#define EFI_SETUP_MODE_NAME               L"SetupMode"
#define EFI_PLATFORM_KEY_NAME             L"PK"
#define EFI_KEY_EXCHANGE_KEY_NAME         L"KEK"
#define EFI_SIGNATURE_SUPPORT_NAME        L"SignatureSupport"
#define EFI_SECURE_BOOT_NAME              L"SecureBoot"

#define SECURE_BOOT                       1
#define NONSECURE_BOOT                    0

//***********************************************************************
// Signature Database
//***********************************************************************

#pragma pack(1)

typedef struct {
    EFI_GUID          SignatureOwner;
    UINT8             SignatureData[1];
} EFI_SIGNATURE_DATA;

typedef struct {
    EFI_GUID           SignatureType;
    UINT32             SignatureListSize;
    UINT32             SignatureHeaderSize;
    UINT32             SignatureSize; 
//  UINT8              SignatureHeader[SignatureHeaderSize];
//  EFI_SIGNATURE_DATA Signatures[][SignatureSize];
} EFI_SIGNATURE_LIST;

#pragma pack()

#define EFI_CERT_SHA256_GUID \
  { 0xc1c41626, 0x504c, 0x4092, 0xac, 0xa9, 0x41, 0xf9, 0x36, 0x93, 0x43, 0x28 }

#define EFI_CERT_RSA2048_GUID \
  { 0x3c5766e8, 0x269c, 0x4e34, 0xaa, 0x14, 0xed, 0x77, 0x6e, 0x85, 0xb3, 0xb6 }

#define EFI_CERT_RSA2048_SHA256_GUID \
  { 0xe2b36190, 0x879b, 0x4a3d, 0xad, 0x8d, 0xf2, 0xe7, 0xbb, 0xa3, 0x27, 0x84 }

#define EFI_CERT_SHA1_GUID \
  { 0x826ca512, 0xcf10, 0x4ac9, 0xb1, 0x87, 0xbe, 0x01, 0x49, 0x66, 0x31, 0xbd }

#define EFI_CERT_RSA2048_SHA1_GUID \
  { 0x67f8444f, 0x8743, 0x48f1, 0xa3, 0x28, 0x1e, 0xaa, 0xb8, 0x73, 0x60, 0x80 }

#define EFI_CERT_X509 \
  { 0xa5c059a1, 0x94e4, 0x4aa7, 0x87, 0xb5, 0xab, 0x15, 0x5c, 0x2b, 0xf0, 0x72 }

#define EFI_CERT_SHA224_GUID \
  { 0x0b6e5233, 0xa65c, 0x44c9, 0x94, 0x07, 0xd9, 0xab, 0x83, 0xbf, 0xc8, 0xbd }

#define EFI_CERT_SHA384_GUID \
  { 0xff3e5307, 0x9fd0, 0x48c9, 0x85, 0xf1, 0x8a, 0xd5, 0x6c, 0x70, 0x1e, 0x01 }

#define EFI_CERT_SHA512_GUID \
  { 0x093e0fae, 0xa6c4, 0x4f50, 0x9f, 0x1b, 0xd4, 0x1e, 0x2b, 0x89, 0xc1, 0x9a }

#define EFI_CERT_TYPE_PKCS7_GUID \
  { 0x4aafd29d, 0x68df, 0x49ee, 0x8a, 0xa9, 0x34, 0x7d, 0x37, 0x56, 0x65, 0xa7 }

//***********************************************************************
// Image Execution Information Table Definition
//***********************************************************************
typedef UINT32 EFI_IMAGE_EXECUTION_ACTION;

#define EFI_IMAGE_EXECUTION_AUTHENTICATION      0x00000007 
#define EFI_IMAGE_EXECUTION_AUTH_UNTESTED       0x00000000
#define EFI_IMAGE_EXECUTION_AUTH_SIG_FAILED     0x00000001
#define EFI_IMAGE_EXECUTION_AUTH_SIG_PASSED     0x00000002
#define EFI_IMAGE_EXECUTION_AUTH_SIG_NOT_FOUND  0x00000003
#define EFI_IMAGE_EXECUTION_AUTH_SIG_FOUND      0x00000004
#define EFI_IMAGE_EXECUTION_POLICY_FAILED       0x00000005
#define EFI_IMAGE_EXECUTION_INITIALIZED         0x00000008

typedef struct {
    EFI_IMAGE_EXECUTION_ACTION Action;
    UINT32                     InfoSize;
//  CHAR16                     Name[];
//  EFI_DEVICE_PATH_PROTOCOL   DevicePath;
    EFI_SIGNATURE_LIST            Signature;
} EFI_IMAGE_EXECUTION_INFO;

typedef struct {
    UINTN                    NumberOfImages; 
//  EFI_IMAGE_EXECUTION_INFO InformationInfo[] 
} EFI_IMAGE_EXECUTION_INFO_TABLE;


GUID_VARIABLE_DECLARATION(gEfiImageSecurityDatabaseGuid, EFI_IMAGE_SECURITY_DATABASE_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertSha256Guid, EFI_CERT_SHA256_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertRsa2048Guid, EFI_CERT_RSA2048_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertRsa2048Sha256Guid, EFI_CERT_RSA2048_SHA256_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertSha1Guid, EFI_CERT_SHA1_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertRsa2048Sha1Guid, EFI_CERT_RSA2048_SHA1_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertX509Guid, EFI_CERT_X509);
GUID_VARIABLE_DECLARATION(gEfiCertSha224Guid, EFI_CERT_SHA224_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertSha384Guid, EFI_CERT_SHA384_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertSha512Guid, EFI_CERT_SHA512_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertPkcs7Guid, EFI_CERT_TYPE_PKCS7_GUID);
GUID_VARIABLE_DECLARATION(gEfiCertTypePkcs7Guid, EFI_CERT_TYPE_PKCS7_GUID);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************