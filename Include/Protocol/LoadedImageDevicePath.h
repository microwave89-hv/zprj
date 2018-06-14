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
// $Header: /Alaska/BIN/Core/Include/Protocol/LoadedImageDevicePath.h 1     11/19/09 12:53p Felixp $
//
// $Revision: 1 $
//
// $Date: 11/19/09 12:53p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/LoadedImageDevicePath.h $
// 
// 1     11/19/09 12:53p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  LoadedImageDevicePath.h
//
// Description:	Loaded Image Device Path Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LOADED_IMAGE_DEVICE_PATH_PROTOCOL__H__
#define __LOADED_IMAGE_DEVICE_PATH_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/DevicePath.h>
#else
#include <EFI.h>
#endif

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID \
    { 0xbc62157e, 0x3e33, 0x4fec, 0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf }

GUID_VARIABLE_DECLARATION(gEfiLoadedImageDevicePathProtocolGuid, EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID);

typedef EFI_DEVICE_PATH_PROTOCOL EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL;
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
