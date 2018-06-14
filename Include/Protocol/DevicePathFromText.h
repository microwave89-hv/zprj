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
// $Header: /Alaska/BIN/Core/Include/Protocol/DevicePathFromText.h 1     5/05/11 12:05p Artems $
//
// $Revision: 1 $
//
// $Date: 5/05/11 12:05p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DevicePathFromText.h $
// 
// 1     5/05/11 12:05p Artems
// 
// 
//*************************************************************************
//<AMI_FHDR_START>
//
//  Name: DevicePathFromText.h
//
//  Description:
//  EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __DEVICE_PATH_FROM_TEXT_PROTOCOL__H__
#define __DEVICE_PATH_FROM_TEXT_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>
#include <Protocol/DevicePath.h>


#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID \
    { 0x5c99a21, 0xc70f, 0x4ad2, 0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e }

GUID_VARIABLE_DECLARATION(gEfiDevicePathFromTextProtocolGuid, EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID);


typedef struct _EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL;

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_NODE) (
    IN CONST CHAR16* TextDeviceNode
);

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_PATH) (
    IN CONST CHAR16* TextDevicePath
);

struct _EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL {
    EFI_DEVICE_PATH_FROM_TEXT_NODE ConvertTextToDeviceNode;
    EFI_DEVICE_PATH_FROM_TEXT_PATH ConvertTextToDevicePath;
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
