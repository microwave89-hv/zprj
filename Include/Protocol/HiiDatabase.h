//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/HiiDatabase.h 2     10/13/09 6:06p Felixp $
//
// $Revision: 2 $
//
// $Date: 10/13/09 6:06p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/HiiDatabase.h $
// 
// 2     10/13/09 6:06p Felixp
// Hii.h renamed to UefiHii.h
// 
// 1     10/09/09 3:52p Felixp
// 
// 1     2/27/09 3:55p Artems
// Initial check-in
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<HiiDatabase.h>
//
// Description:	Hii Database protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_DATABASE__H__
#define __HII_DATABASE__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <UefiHii.h>

#define EFI_HII_DATABASE_PROTOCOL_GUID \
    { 0xef9fc172, 0xa1b2, 0x4693, 0xb3, 0x27, 0x6d, 0x32, 0xfc, 0x41, 0x60, 0x42 }

GUID_VARIABLE_DECLARATION(gEfiHiiDatabaseProtocolGuid, EFI_HII_DATABASE_PROTOCOL_GUID);

typedef struct _EFI_HII_DATABASE_PROTOCOL EFI_HII_DATABASE_PROTOCOL;

typedef EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_NEW_PACK) (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN CONST EFI_HII_PACKAGE_LIST_HEADER    *PackageList,
    IN CONST EFI_HANDLE                     DriverHandle,
    OUT EFI_HII_HANDLE                      *Handle
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_REMOVE_PACK) (
    IN CONST EFI_HII_DATABASE_PROTOCOL  *This,
    IN EFI_HII_HANDLE                   Handle
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_UPDATE_PACK) (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HII_HANDLE                       Handle,
    IN CONST EFI_HII_PACKAGE_LIST_HEADER    *PackageList
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_LIST_PACKS) (
    IN CONST EFI_HII_DATABASE_PROTOCOL  *This,
    IN UINT8                            PackageType,
    IN CONST EFI_GUID                   *PackageGuid,
    IN OUT UINTN                        *HandleBufferLength,
    OUT EFI_HII_HANDLE                  *Handle
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_EXPORT_PACKS) (
    IN CONST EFI_HII_DATABASE_PROTOCOL  *This,
    IN EFI_HII_HANDLE                   Handle,
    IN OUT UINTN                        *BufferSize,
    OUT EFI_HII_PACKAGE_LIST_HEADER     *Buffer
);

typedef UINTN EFI_HII_DATABASE_NOTIFY_TYPE;

#define EFI_HII_DATABASE_NOTIFY_NEW_PACK    0x00000001
#define EFI_HII_DATABASE_NOTIFY_REMOVE_PACK 0x00000002
#define EFI_HII_DATABASE_NOTIFY_EXPORT_PACK 0x00000004
#define EFI_HII_DATABASE_NOTIFY_ADD_PACK    0x00000008

typedef EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_NOTIFY) (
    IN UINT8                        PackageType,
    IN CONST EFI_GUID               *PackageGuid,
    IN CONST EFI_HII_PACKAGE_HEADER *Package,
    IN EFI_HII_HANDLE               Handle,
    IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_REGISTER_NOTIFY) (
    IN CONST EFI_HII_DATABASE_PROTOCOL  *This,
    IN UINT8                            PackageType,
    IN CONST EFI_GUID                   *PackageGuid,
    IN CONST EFI_HII_DATABASE_NOTIFY    PackageNotifyFn,
    IN EFI_HII_DATABASE_NOTIFY_TYPE     NotifyType,
    OUT EFI_HANDLE                      *NotifyHandle
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_DATABASE_UNREGISTER_NOTIFY) (
    IN CONST EFI_HII_DATABASE_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_FIND_KEYBOARD_LAYOUTS) (
    IN EFI_HII_DATABASE_PROTOCOL    *This,
    IN OUT UINT16                   *KeyGuidBufferLength,
    OUT EFI_GUID                    *KeyGuidBuffer
);

typedef
EFI_STATUS (EFIAPI *EFI_HII_GET_KEYBOARD_LAYOUT) (
    IN EFI_HII_DATABASE_PROTOCOL    *This,
    IN EFI_GUID                     *KeyGuid,
    IN OUT UINT16                   *KeyGuidBufferLength,
    OUT EFI_HII_KEYBOARD_LAYOUT     *KeyboardLayout
);

typedef
EFI_STATUS (EFIAPI *EFI_HII_SET_KEYBOARD_LAYOUT) (
    IN EFI_HII_DATABASE_PROTOCOL *This,
    IN EFI_GUID                  *KeyGuid
);

typedef
EFI_STATUS (EFIAPI *EFI_HII_DATABASE_GET_PACK_HANDLE) (
    IN EFI_HII_DATABASE_PROTOCOL *This,
    IN EFI_HII_HANDLE            PackageListHandle,
    OUT EFI_HANDLE               *DriverHandle
);

struct _EFI_HII_DATABASE_PROTOCOL {
    EFI_HII_DATABASE_NEW_PACK           NewPackageList;
    EFI_HII_DATABASE_REMOVE_PACK        RemovePackageList;
    EFI_HII_DATABASE_UPDATE_PACK        UpdatePackageList;
    EFI_HII_DATABASE_LIST_PACKS         ListPackageLists;
    EFI_HII_DATABASE_EXPORT_PACKS       ExportPackageLists;
    EFI_HII_DATABASE_REGISTER_NOTIFY    RegisterPackageNotify;
    EFI_HII_DATABASE_UNREGISTER_NOTIFY  UnregisterPackageNotify;
    EFI_HII_FIND_KEYBOARD_LAYOUTS       FindKeyboardLayouts;
    EFI_HII_GET_KEYBOARD_LAYOUT         GetKeyboardLayout;
    EFI_HII_SET_KEYBOARD_LAYOUT         SetKeyboardLayout;
    EFI_HII_DATABASE_GET_PACK_HANDLE    GetPackageListHandle;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************