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
// $Header: /Alaska/BIN/Core/Include/WinCertificate.h 3     5/22/12 10:23a Artems $
//
// $Revision: 3 $
//
// $Date: 5/22/12 10:23a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/WinCertificate.h $
// 
// 3     5/22/12 10:23a Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	PKCS7 guid definition is moved to ImageAuthentication.h
// in sync with EDKII
// [Files]  		WinCertificate.h ImageAuthentication.h
// 
// 2     5/13/11 4:28p Artems
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<WinCertificate.h>
//
// Description:	Win certificate definition header file
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __EFI_WIN_CERTIFICATE_H__
#define __EFI_WIN_CERTIFICATE_H__
#ifdef __cplusplus
extern "C" {
#endif

#define WIN_CERT_TYPE_PKCS_SIGNED_DATA 0x0002
#define WIN_CERT_TYPE_EFI_PKCS115      0x0EF0
#define WIN_CERT_TYPE_EFI_GUID         0x0EF1


typedef struct {
    UINT32  dwLength;
    UINT16  wRevision;
    UINT16  wCertificateType;
//  UINT8   bCertificate[ANYSIZE_ARRAY];
} WIN_CERTIFICATE;

#define EFI_CERT_TYPE_RSA2048_SHA256_GUID \
  {0xa7717414, 0xc616, 0x4977, 0x94, 0x20, 0x84, 0x47, 0x12, 0xa7, 0x35, 0xbf }

typedef struct {
    EFI_GUID  HashType;
    UINT8     PublicKey[256];
    UINT8     Signature[256];
} EFI_CERT_BLOCK_RSA_2048_SHA256;

typedef struct {
    WIN_CERTIFICATE                 Hdr;
    EFI_GUID                        CertType;
    UINT8                           CertData[1];
//  EFI_CERT_BLOCK_RSA_2048_SHA256  CertData;
} WIN_CERTIFICATE_UEFI_GUID;

typedef struct {     
    WIN_CERTIFICATE Hdr;
    EFI_GUID        HashAlgorithm;
//  UINT8           Signature[];
} WIN_CERTIFICATE_EFI_PKCS1_15;

GUID_VARIABLE_DECLARATION(gEfiCertTypeRsa2048Sha256Guid, EFI_CERT_TYPE_RSA2048_SHA256_GUID);


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