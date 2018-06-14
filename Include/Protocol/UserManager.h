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
// $Header: /Alaska/BIN/Core/Include/Protocol/UserManager.h 1     5/13/11 4:36p Artems $
//
// $Revision: 1 $
//
// $Date: 5/13/11 4:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/UserManager.h $
// 
// 1     5/13/11 4:36p Artems
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<UserManager.h>
//
// Description:	User manager protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __USER_MANAGER__H__
#define __USER_MANAGER__H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_USER_MANAGER_PROTOCOL_GUID \
    { 0x6fd5b00c, 0xd426, 0x4283, 0x98, 0x87, 0x6c, 0xf5, 0xcf, 0x1c, 0xb1, 0xfe }

#define EFI_EVENT_GROUP_USER_PROFILE_CHANGED \
    { 0xbaf1e6de, 0x209e, 0x4adb, 0x8d, 0x96, 0xfd, 0x8b, 0x71, 0xf3, 0xf6, 0x83 }

#define EFI_USER_INFO_ACCESS_SETUP_ADMIN_GUID \
    { 0x85b75607, 0xf7ce, 0x471e, 0xb7, 0xe4, 0x2a, 0xea, 0x5f, 0x72, 0x32, 0xee }

#define EFI_USER_INFO_ACCESS_SETUP_NORMAL_GUID \
    { 0x1db29ae0, 0x9dcb, 0x43bc, 0x8d, 0x87, 0x5d, 0xa1, 0x49, 0x64, 0xdd, 0xe2 }

#define EFI_USER_INFO_ACCESS_SETUP_RESTRICTED_GUID \
    { 0xbdb38125, 0x4d63, 0x49f4, 0x82, 0x12, 0x61, 0xcf, 0x5a, 0x19, 0x0a, 0xf8 }

GUID_VARIABLE_DECLARATION(gEfiUserManagerProtocolGuid, EFI_USER_MANAGER_PROTOCOL_GUID);
GUID_VARIABLE_DECLARATION(gEfiEventUserProfileChangedGuid, EFI_EVENT_GROUP_USER_PROFILE_CHANGED);
GUID_VARIABLE_DECLARATION(gEfiUserInfoAccessSetupAdminGuid, EFI_USER_INFO_ACCESS_SETUP_ADMIN_GUID);
GUID_VARIABLE_DECLARATION(gEfiUserInfoAccessSetupNormalGuid, EFI_USER_INFO_ACCESS_SETUP_NORMAL_GUID);
GUID_VARIABLE_DECLARATION(gEfiUserInfoAccessSetupRestrictedGuid, EFI_USER_INFO_ACCESS_SETUP_RESTRICTED_GUID);

typedef struct _EFI_USER_MANAGER_PROTOCOL EFI_USER_MANAGER_PROTOCOL;

typedef VOID *EFI_USER_PROFILE_HANDLE;
typedef VOID *EFI_USER_INFO_HANDLE;
typedef UINT16 EFI_USER_INFO_ATTRIBS;

#define EFI_USER_INFO_STORAGE               0x000F
#define EFI_USER_INFO_STORAGE_VOLATILE      0x0000
#define EFI_USER_INFO_STORAGE_CREDENTIAL_NV 0x0001
#define EFI_USER_INFO_STORAGE_PLATFORM_NV   0x0002

#define EFI_USER_INFO_ACCESS                0x0070
#define EFI_USER_INFO_PUBLIC                0x0010
#define EFI_USER_INFO_PRIVATE               0x0020
#define EFI_USER_INFO_PROTECTED             0x0030
#define EFI_USER_INFO_EXCLUSIVE             0x0080

#define EFI_USER_INFO_ACCESS_POLICY_RECORD 0x0E
typedef struct {
    UINT32 Type;
    UINT32 Size;
} EFI_USER_INFO_ACCESS_CONTROL;
typedef EFI_USER_INFO_ACCESS_CONTROL EFI_USER_INFO_ACCESS_POLICY;

#define EFI_USER_INFO_ACCESS_FORBID_LOAD    0x00000001
#define EFI_USER_INFO_ACCESS_PERMIT_LOAD    0x00000002
#define EFI_USER_INFO_ACCESS_ENROLL_SELF    0x00000003
#define EFI_USER_INFO_ACCESS_ENROLL_OTHERS  0x00000004
#define EFI_USER_INFO_ACCESS_MANAGE         0x00000005
#define EFI_USER_INFO_ACCESS_SETUP          0x00000006
#define EFI_USER_INFO_ACCESS_FORBID_CONNECT 0x00000007
#define EFI_USER_INFO_ACCESS_PERMIT_CONNECT 0x00000008
#define EFI_USER_INFO_ACCESS_BOOT_ORDER     0x00000009
  typedef UINT32 EFI_USER_INFO_ACCESS_BOOT_ORDER_HDR;
  #define EFI_USER_INFO_ACCESS_BOOT_ORDER_MASK      0x000F
  #define EFI_USER_INFO_ACCESS_BOOT_ORDER_INSERT    0x0000
  #define EFI_USER_INFO_ACCESS_BOOT_ORDER_APPEND    0x0001
  #define EFI_USER_INFO_ACCESS_BOOT_ORDER_REPLACE   0x0002
  #define EFI_USER_INFO_ACCESS_BOOT_ORDER_NODEFAULT 0x0010

#define EFI_USER_INFO_CBEFF_RECORD 0x0B
typedef VOID *EFI_USER_INFO_CBEFF;

#define EFI_USER_INFO_CREATE_DATE_RECORD 0x02
typedef EFI_TIME EFI_USER_INFO_CREATE_DATE;

#define EFI_USER_INFO_CREDENTIAL_PROVIDER_RECORD 0x08
typedef EFI_GUID EFI_USER_INFO_CREDENTIAL_PROVIDER;

#define EFI_USER_INFO_CREDENTIAL_PROVIDER_NAME_RECORD 0x09
typedef CHAR16 *EFI_USER_INFO_CREDENTIAL_PROVIDER_NAME;

#define EFI_USER_INFO_CREDENTIAL_TYPE_RECORD 0x06
typedef EFI_GUID EFI_USER_INFO_CREDENTIAL_TYPE;

#define EFI_USER_INFO_CREDENTIAL_TYPE_NAME_RECORD 0x07
typedef CHAR16 *EFI_USER_INFO_CREDENTIAL_TYPE_NAME;

#define EFI_USER_INFO_GUID_RECORD 0xFF
typedef EFI_GUID EFI_USER_INFO_GUID;

#define EFI_USER_INFO_FAR_RECORD 0x0C
typedef UINT8 EFI_USER_INFO_FAR;

#define EFI_USER_INFO_IDENTIFIER_RECORD 0x05
typedef UINT8 EFI_USER_INFO_IDENTIFIER[16];

#define EFI_USER_INFO_IDENTITY_POLICY_RECORD 0x0F
typedef struct {
    UINT32 Type;
    UINT32 Length;
} EFI_USER_INFO_IDENTITY_POLICY;
#define EFI_USER_INFO_IDENTITY_FALSE                0x00
#define EFI_USER_INFO_IDENTITY_TRUE                 0x01
#define EFI_USER_INFO_IDENTITY_CREDENTIAL_TYPE      0x02
#define EFI_USER_INFO_IDENTITY_CREDENTIAL_PROVIDER  0x03
#define EFI_USER_INFO_IDENTITY_NOT                  0x10
#define EFI_USER_INFO_IDENTITY_AND                  0x11
#define EFI_USER_INFO_IDENTITY_OR                   0x12

#define EFI_USER_INFO_NAME_RECORD 0x01
typedef CHAR16 *EFI_USER_INFO_NAME;

#define EFI_USER_INFO_PKCS11_RECORD 0x0A
#define EFI_USER_INFO_RETRY_RECORD  0x0D
typedef UINT8 EFI_USER_INFO_RETRY;

#define EFI_USER_INFO_USAGE_DATE_RECORD 0x03
typedef EFI_TIME EFI_USER_INFO_USAGE_DATE;

#define EFI_USER_INFO_USAGE_COUNT_RECORD 0x04
typedef UINT64 EFI_USER_INFO_USAGE_COUNT;

#define EFI_USER_INFO_EMPTY_RECORD 0x00

typedef struct {
    UINT64 Size;
} EFI_USER_INFO_TABLE;

typedef struct {
    EFI_GUID              Credential;
    UINT8                 InfoType;
    UINT8                 Reserved1;
    EFI_USER_INFO_ATTRIBS InfoAttribs;
    UINT32                InfoSize;
} EFI_USER_INFO;

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_CREATE) (
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    OUT      EFI_USER_PROFILE_HANDLE   *User
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_DELETE) (
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    IN       EFI_USER_PROFILE_HANDLE   User
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_GET_NEXT)(
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    IN OUT   EFI_USER_PROFILE_HANDLE   *User
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_CURRENT)(
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    OUT      EFI_USER_PROFILE_HANDLE   *CurrentUser
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_IDENTIFY) (
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    OUT      EFI_USER_PROFILE_HANDLE   *User
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_FIND)(
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    IN OUT   EFI_USER_PROFILE_HANDLE   *User,
    IN OUT   EFI_USER_INFO_HANDLE      *UserInfo OPTIONAL,
    IN CONST EFI_USER_INFO             *Info,
    IN       UINTN                     InfoSize
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_NOTIFY)(
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    IN       EFI_HANDLE                Changed
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_GET_INFO)(
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    IN       EFI_USER_PROFILE_HANDLE   User,
    IN       EFI_USER_INFO_HANDLE      UserInfo,
    OUT      EFI_USER_INFO             *Info,
    IN OUT   UINTN                     *InfoSize
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_SET_INFO) (
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    IN       EFI_USER_PROFILE_HANDLE   User,
    IN OUT   EFI_USER_INFO_HANDLE      *UserInfo,
    IN CONST EFI_USER_INFO             *Info,
    IN UINTN                           InfoSize
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_DELETE_INFO) (
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    IN       EFI_USER_PROFILE_HANDLE   User,
    IN       EFI_USER_INFO_HANDLE      UserInfo
);

typedef EFI_STATUS
(EFIAPI *EFI_USER_PROFILE_GET_NEXT_INFO)(
    IN CONST EFI_USER_MANAGER_PROTOCOL *This,
    IN       EFI_USER_PROFILE_HANDLE   User,
    IN OUT   EFI_USER_INFO_HANDLE      *UserInfo
);

struct _EFI_USER_MANAGER_PROTOCOL {
    EFI_USER_PROFILE_CREATE         Create;
    EFI_USER_PROFILE_DELETE         Delete;
    EFI_USER_PROFILE_GET_NEXT       GetNext;
    EFI_USER_PROFILE_CURRENT        Current;
    EFI_USER_PROFILE_IDENTIFY       Identify;
    EFI_USER_PROFILE_FIND           Find;
    EFI_USER_PROFILE_NOTIFY         Notify;
    EFI_USER_PROFILE_GET_INFO       GetInfo;
    EFI_USER_PROFILE_SET_INFO       SetInfo;
    EFI_USER_PROFILE_DELETE_INFO    DeleteInfo;
    EFI_USER_PROFILE_GET_NEXT_INFO  GetNextInfo;
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