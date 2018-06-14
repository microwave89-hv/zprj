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
// $Header: /Alaska/SOURCE/Core/Modules/FirmwareManagement/FirmwareManagement.c 2     4/11/12 5:03p Artems $
//
// $Revision: 2 $
//
// $Date: 4/11/12 5:03p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/FirmwareManagement/FirmwareManagement.c $
// 
// 2     4/11/12 5:03p Artems
// [TAG]  		EIP87144
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Aptio4.6.5.3...SCT Execution test failed.(Firmware
// Management Test\Firmware Management Protocol)
// [RootCause]  	Firmware management protocol is not supported
// [Solution]  	Added fix to pass conformance SCT test
// [Files]  		FirmwareManagement.c
// 
// 1     5/02/11 5:49p Artems
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: FirmwareManagement.c
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol\FirmwareManagement.h>

EFI_STATUS FmGetImageInfo (
    IN     EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    IN OUT UINTN                            *ImageInfoSize,
    IN OUT EFI_FIRMWARE_IMAGE_DESCRIPTOR    *ImageInfo,
    OUT    UINT32                           *DescriptorVersion,
    OUT    UINT8                            *DescriptorCount,
    OUT    UINTN                            *DescriptorSize,
    OUT    UINT32                           *PackageVersion,
    OUT    CHAR16                           **PackageVersionName
)
{
    if(ImageInfoSize == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if(*ImageInfoSize < sizeof(EFI_FIRMWARE_IMAGE_DESCRIPTOR)) {
        *ImageInfoSize = sizeof(EFI_FIRMWARE_IMAGE_DESCRIPTOR);
        return EFI_BUFFER_TOO_SMALL;
    }

    return EFI_UNSUPPORTED;
}

EFI_STATUS FmGetImage (
    IN     EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    IN     UINT8                            ImageIndex,
    IN OUT VOID                             *Image,
    IN OUT UINTN                            *ImageSize
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS FmSetImage (
    IN       EFI_FIRMWARE_MANAGEMENT_PROTOCOL              *This,
    IN       UINT8                                         ImageIndex,
    IN CONST VOID                                          *Image,
    IN       UINTN                                         ImageSize,
    IN CONST VOID                                          *VendorCode,
    IN       EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress,
    OUT      CHAR16                                        **AbortReason
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS FmCheckImage (
    IN       EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    IN       UINT8                            ImageIndex,
    IN CONST VOID                             *Image,
    IN       UINTN                            ImageSize,
    OUT      UINT32                           *ImageUpdatable
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS FmGetPackageInfo (
    IN  EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    OUT UINT32                           *PackageVersion,
    OUT CHAR16                           **PackageVersionName,
    OUT UINT32                           *PackageVersionNameMaxLen,
    OUT UINT64                           *AttributesSupported,
    OUT UINT64                           *AttributesSetting
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS FmSetPackageInfo (
    IN       EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    IN CONST VOID                             *Image,
    IN       UINTN                            ImageSize,
    IN CONST VOID                             *VendorCode,
    IN       UINT32                           PackageVersion,
    IN CONST CHAR16                           *PackageVersionName
)
{
    return EFI_UNSUPPORTED;
}


EFI_FIRMWARE_MANAGEMENT_PROTOCOL EfiFirmwareManagementProtocol = {
    FmGetImageInfo,
    FmGetImage,
    FmSetImage,
    FmCheckImage,
    FmGetPackageInfo,
    FmSetPackageInfo
};

EFI_STATUS FirmwareManagementEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_HANDLE  Handle = NULL;

    InitAmiLib(ImageHandle,SystemTable);

    Status = pBS->InstallMultipleProtocolInterfaces(
                                &Handle,
                                &gEfiFirmwareManagementProtocolGuid, 
                                &EfiFirmwareManagementProtocol,
                                NULL);


    return Status;
}





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