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
// $Header: /Alaska/BIN/Core/Include/Protocol/UserCredential.h 1     5/13/11 4:37p Artems $
//
// $Revision: 1 $
//
// $Date: 5/13/11 4:37p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/UserCredential.h $
// 
// 1     5/13/11 4:37p Artems
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<UserCredential.h>
//
// Description:	User credential protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __USER_CREDENTIAL__H__
#define __USER_CREDENTIAL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <UefiHii.h>
#include <Protocol/UserManager.h>

#define EFI_USER_CREDENTIAL_PROTOCOL_GUID \
    { 0x71ee5e94, 0x65b9, 0x45d5, 0x82, 0x1a, 0x3a, 0x4d, 0x86, 0xcf, 0xe6, 0xbe }

#define EFI_USER_CREDENTIAL_CLASS_UNKNOWN \
    { 0x5cf32e68, 0x7660, 0x449b, 0x80, 0xe6, 0x7e, 0xa3, 0x6e, 0x03, 0xf6, 0xa8 }

#define EFI_USER_CREDENTIAL_CLASS_PASSWORD \
    { 0xf8e5058c, 0xccb6, 0x4714, 0xb2, 0x20, 0x3f, 0x7e, 0x3a, 0x64, 0x0b, 0xd1 }

#define EFI_USER_CREDENTIAL_CLASS_SMART_CARD \
    { 0x5f03ba33, 0x8c6b, 0x4c24, 0xaa, 0x2e, 0x14, 0xa2, 0x65, 0x7b, 0xd4, 0x54 }

#define EFI_USER_CREDENTIAL_CLASS_FINGERPRINT \
    { 0x32cba21f, 0xf308, 0x4cbc, 0x9a, 0xb5, 0xf5, 0xa3, 0x69, 0x9f, 0x04, 0x4a }

#define EFI_USER_CREDENTIAL_CLASS_HANDPRINT \
    { 0x5917ef16, 0xf723, 0x4bb9, 0xa6, 0x4b, 0xd8, 0xc5, 0x32, 0xf4, 0xd8, 0xb5 }

#define EFI_USER_CREDENTIAL_CLASS_SECURE_CARD \
    { 0x8a6b4a83, 0x42fe, 0x45d2, 0xa2, 0xef, 0x46, 0xf0, 0x6c, 0x7d, 0x98, 0x52 }


#define EFI_CREDENTIAL_CAPABILITIES_ENROLL  0x0000000000000001

#define EFI_CREDENTIAL_LOGON_FLAG_AUTO      0x00000001
#define EFI_CREDENTIAL_LOGON_FLAG_DEFAULT   0x00000002

GUID_VARIABLE_DECLARATION(gEfiUserCredentialProtocolGuid, EFI_USER_CREDENTIAL_PROTOCOL_GUID);
GUID_VARIABLE_DECLARATION(gEfiUserCredentialClassPasswordGuid, EFI_USER_CREDENTIAL_CLASS_PASSWORD);

typedef struct _EFI_USER_CREDENTIAL_PROTOCOL EFI_USER_CREDENTIAL_PROTOCOL;

typedef UINT64 EFI_CREDENTIAL_CAPABILITIES;
typedef UINT32 EFI_CREDENTIAL_LOGON_FLAGS;

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_ENROLL)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    IN       EFI_USER_PROFILE_HANDLE      User
);

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_FORM)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    OUT      EFI_HII_HANDLE               *Hii,
    OUT      EFI_GUID                     *FormSetId,
    OUT      EFI_FORM_ID                  *FormId
);

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_TILE)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    IN OUT   UINTN                        *Width,
    IN OUT   UINTN                        *Height,
    OUT      EFI_HII_HANDLE               *Hii,
    OUT      EFI_IMAGE_ID                 *Image
);

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_TITLE)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    OUT      EFI_HII_HANDLE               *Hii,
    OUT      EFI_STRING_ID                *String
);

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_USER)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    IN       EFI_USER_PROFILE_HANDLE      User,
    OUT      EFI_USER_INFO_IDENTIFIER     *Identifier
);

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_SELECT)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    OUT      EFI_CREDENTIAL_LOGON_FLAGS   *AutoLogon
);

typedef
EFI_STATUS (EFIAPI *EFI_CREDENTIAL_DESELECT)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This
);

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_DEFAULT)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    OUT      EFI_CREDENTIAL_LOGON_FLAGS   *AutoLogon
);

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_GET_INFO)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    IN       EFI_USER_INFO_HANDLE         UserInfo,
    OUT      EFI_USER_INFO                *Info,
    IN OUT   UINTN                        *InfoSize
);

typedef EFI_STATUS
(EFIAPI *EFI_CREDENTIAL_GET_NEXT_INFO)(
    IN CONST EFI_USER_CREDENTIAL_PROTOCOL *This,
    IN OUT   EFI_USER_INFO_HANDLE         *UserInfo
);

struct _EFI_USER_CREDENTIAL_PROTOCOL {
    EFI_GUID                     Identifier;
    EFI_GUID                     Type;
    EFI_CREDENTIAL_ENROLL        Enroll;
    EFI_CREDENTIAL_FORM          Form;
    EFI_CREDENTIAL_TILE          Tile;
    EFI_CREDENTIAL_TITLE         Title;
    EFI_CREDENTIAL_USER          User;
    EFI_CREDENTIAL_SELECT        Select;
    EFI_CREDENTIAL_DESELECT      Deselect;
    EFI_CREDENTIAL_DEFAULT       Default;
    EFI_CREDENTIAL_GET_INFO      GetInfo;
    EFI_CREDENTIAL_GET_NEXT_INFO GetNextInfo;
    EFI_CREDENTIAL_CAPABILITIES  Capabilities;
};

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