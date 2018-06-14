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
// $Header: /Alaska/BIN/Core/Include/Protocol/DevicePathToText.h 2     6/13/11 6:18p Artems $
//
// $Revision: 2 $
//
// $Date: 6/13/11 6:18p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DevicePathToText.h $
// 
// 2     6/13/11 6:18p Artems
// Fixed bug in file header
// 
// 1     5/05/11 12:05p Artems
// 
// 
//*************************************************************************
//<AMI_FHDR_START>
//
//  Name: DevicePathToText.h
//
//  Description:
//  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __DEVICE_PATH_TO_TEXT_PROTOCOL__H__
#define __DEVICE_PATH_TO_TEXT_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>
#include <Protocol/DevicePath.h>

#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID \
    { 0x8b843e20, 0x8132, 0x4852, 0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c }

GUID_VARIABLE_DECLARATION(gEfiDevicePathToTextProtocolGuid, EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID);


typedef struct _EFI_DEVICE_PATH_TO_TEXT_PROTOCOL EFI_DEVICE_PATH_TO_TEXT_PROTOCOL;

typedef
CHAR16*
(EFIAPI *EFI_DEVICE_PATH_TO_TEXT_NODE) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DeviceNode,
    IN       BOOLEAN                  DisplayOnly,
    IN       BOOLEAN                  AllowShortcuts
);

typedef
CHAR16*
(EFIAPI *EFI_DEVICE_PATH_TO_TEXT_PATH) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN       BOOLEAN                  DisplayOnly,
    IN       BOOLEAN                  AllowShortcuts
);

struct _EFI_DEVICE_PATH_TO_TEXT_PROTOCOL {
    EFI_DEVICE_PATH_TO_TEXT_NODE ConvertDeviceNodeToText;
    EFI_DEVICE_PATH_TO_TEXT_PATH ConvertDevicePathToText;
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
