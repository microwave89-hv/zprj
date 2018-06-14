//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/DevicePathUtilities.h 1     10/12/06 6:43p Felixp $
//
// $Revision: 1 $
//
// $Date: 10/12/06 6:43p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DevicePathUtilities.h $
// 
// 1     10/12/06 6:43p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DevicePathUtilities.h
//
// Description:	EFI_DEVICE_PATH_UTILITIES_PROTOCOL protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_DEVICE_PATH_UTILITIES_PROTOCOL__H__
#define __EFI_DEVICE_PATH_UTILITIES_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID \
	{0x379be4e,0xd706,0x437d,0xb0,0x37,0xed,0xb8,0x2f,0xb7,0x72,0xa4}

GUID_VARIABLE_DECLARATION(gEfiDevicePathUtilitiesProtocolGuid, EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID);

typedef UINTN (EFIAPI *EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE)(
    IN CONST EFI_DEVICE_PATH_PROTOCOL* DevicePath
);

typedef EFI_DEVICE_PATH_PROTOCOL* (EFIAPI *EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH)(
    IN CONST EFI_DEVICE_PATH_PROTOCOL* DevicePath
);

typedef EFI_DEVICE_PATH_PROTOCOL* (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_PATH)(
	IN CONST EFI_DEVICE_PATH_PROTOCOL* Src1,
	IN CONST EFI_DEVICE_PATH_PROTOCOL* Src2
);

typedef EFI_DEVICE_PATH_PROTOCOL* (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_NODE)(
    IN CONST EFI_DEVICE_PATH_PROTOCOL* DevicePath,
    IN CONST EFI_DEVICE_PATH_PROTOCOL* DeviceNode
);

typedef EFI_DEVICE_PATH_PROTOCOL* (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE)(
    IN CONST EFI_DEVICE_PATH_PROTOCOL* DevicePath,
    IN CONST EFI_DEVICE_PATH_PROTOCOL* DevicePathInstance
);

typedef EFI_DEVICE_PATH_PROTOCOL* (EFIAPI *EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE)(
    IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePathInstance,
    OUT UINTN *DevicePathInstanceSize
);

typedef EFI_DEVICE_PATH_PROTOCOL* (EFIAPI *EFI_DEVICE_PATH_UTILS_CREATE_NODE)(
    IN UINT8 NodeType, IN UINT8 NodeSubType,
    IN UINT16 NodeLength
);

typedef BOOLEAN (EFIAPI *EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE)(
    IN CONST EFI_DEVICE_PATH_PROTOCOL* DevicePath
);

typedef struct _EFI_DEVICE_PATH_UTILITIES_PROTOCOL{
    EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE GetDevicePathSize;
    EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH DuplicateDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_PATH AppendDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_NODE AppendDeviceNode;
    EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE AppendDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE GetNextDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE IsDevicePathMultiInstance;
    EFI_DEVICE_PATH_UTILS_CREATE_NODE CreateDeviceNode;
} EFI_DEVICE_PATH_UTILITIES_PROTOCOL;
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************