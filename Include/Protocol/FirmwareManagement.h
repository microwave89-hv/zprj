//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/FirmwareManagement.h 1     5/02/11 5:39p Artems $
//
// $Revision: 1 $
//
// $Date: 5/02/11 5:39p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/FirmwareManagement.h $
// 
// 1     5/02/11 5:39p Artems
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FirmwareManagement.h
//
//  Description:
//  EFI_FIRMWARE_MANAGEMENT_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __FIRMWARE_MANAGEMENT_PROTOCOL__H__
#define __FIRMWARE_MANAGEMENT_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>
#include <WinCertificate.h>

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GUID \
    { 0x86c77a67, 0xb97, 0x4633, 0xa1, 0x87, 0x49, 0x10, 0x4d, 0x6, 0x85, 0xc7 }

#define IMAGE_ATTRIBUTE_IMAGE_UPDATABLE         0x0000000000000001
#define IMAGE_ATTRIBUTE_RESET_REQUIRED          0x0000000000000002
#define IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED 0x0000000000000004
#define IMAGE_ATTRIBUTE_IN_USE                  0x0000000000000008

#define IMAGE_COMPATIBILITY_CHECK_SUPPORTED     0x0000000000000001

#define EFI_FIRMWARE_IMAGE_DESCRIPTOR_VERSION 1

#define IMAGE_UPDATABLE_VALID        0x0000000000000001
#define IMAGE_UPDATABLE_INVALID      0x0000000000000002
#define IMAGE_UPDATABLE_INVALID_TYPE 0x0000000000000004
#define IMAGE_UPDATABLE_INVALID_OLD  0x0000000000000008

#define PACKAGE_ATTRIBUTE_VERSION_UPDATABLE       0x0000000000000001
#define PACKAGE_ATTRIBUTE_RESET_REQUIRED          0x0000000000000002
#define PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED 0x0000000000000004

GUID_VARIABLE_DECLARATION(gEfiFirmwareManagementProtocolGuid, EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GUID);


typedef struct _EFI_FIRMWARE_MANAGEMENT_PROTOCOL EFI_FIRMWARE_MANAGEMENT_PROTOCOL;

typedef struct {
    UINT64                    MonotonicCount;
    WIN_CERTIFICATE_UEFI_GUID AuthInfo;
} EFI_FIRMWARE_IMAGE_AUTHENTICATION;

typedef struct {
    UINT8    ImageIndex;
    EFI_GUID ImageTypeId;
    UINT64   ImageId;
    CHAR16   *ImageIdName;
    UINT32   Version;
    CHAR16   *VersionName;
    UINTN    Size;
    UINT64   AttributesSupported;
    UINT64   AttributesSetting;
    UINT64   Compatibilities;
} EFI_FIRMWARE_IMAGE_DESCRIPTOR;

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS) (
    IN UINTN Completion
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE_INFO) (
    IN     EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    IN OUT UINTN                            *ImageInfoSize,
    IN OUT EFI_FIRMWARE_IMAGE_DESCRIPTOR    *ImageInfo,
    OUT    UINT32                           *DescriptorVersion,
    OUT    UINT8                            *DescriptorCount,
    OUT    UINTN                            *DescriptorSize,
    OUT    UINT32                           *PackageVersion,
    OUT    CHAR16                           **PackageVersionName
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE) (
    IN     EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    IN     UINT8                            ImageIndex,
    IN OUT VOID                             *Image,
    IN OUT UINTN                            *ImageSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_IMAGE) (
    IN       EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *This,
    IN       UINT8                                         ImageIndex,
    IN CONST VOID                                          *Image,
    IN       UINTN                                         ImageSize,
    IN CONST VOID                                          *VendorCode,
    IN       EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress,
    OUT      CHAR16                                        **AbortReason
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_CHECK_IMAGE) (
    IN       EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    IN       UINT8                            ImageIndex,
    IN CONST VOID                             *Image,
    IN       UINTN                            ImageSize,
    OUT      UINT32                           *ImageUpdatable
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_PACKAGE_INFO) (
    IN  EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    OUT UINT32                           *PackageVersion,
    OUT CHAR16                           **PackageVersionName,
    OUT UINT32                           *PackageVersionNameMaxLen,
    OUT UINT64                           *AttributesSupported,
    OUT UINT64                           *AttributesSetting
);

typedef
EFI_STATUS
(EFIAPI *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_PACKAGE_INFO) (
    IN       EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    IN CONST VOID                             *Image,
    IN       UINTN                            ImageSize,
    IN CONST VOID                             *VendorCode,
    IN       UINT32                           PackageVersion,
    IN CONST CHAR16                           *PackageVersionName
);

struct _EFI_FIRMWARE_MANAGEMENT_PROTOCOL {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE_INFO   GetImageInfo;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE        GetImage;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_IMAGE        SetImage;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_CHECK_IMAGE      CheckImage;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_PACKAGE_INFO GetPackageInfo;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_PACKAGE_INFO SetPackageInfo;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
