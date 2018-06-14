//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/DriverBinding.h 3     3/13/06 1:40a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DriverBinding.h $
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:34a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 3     12/02/04 10:32a Markw
// Added DevicePath include.
// 
// 2     3/13/04 5:13p Felixp
// 
// 1     3/13/04 4:36p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DriverBinging.h
//
// Description:	EFI_DRIVER_BINDING Protocol Definition.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __DRIVER_BINDING_PROTOCOL_H__
#define __DRIVER_BINDING_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_DRIVER_BINDING_PROTOCOL_GUID \
	{0x18A031AB,0xB443,0x4D1A,0xA5,0xC0,0x0C,0x09,0x26,0x1E,0x9F,0x71}

GUID_VARIABLE_DECLARATION(gEfiDriverBindingProtocolGuid, EFI_DRIVER_BINDING_PROTOCOL_GUID);

typedef struct _EFI_DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED) (
	IN EFI_DRIVER_BINDING_PROTOCOL *This, 
	IN EFI_HANDLE ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_START) (
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_STOP) (
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN UINTN NumberOfChildren,
	IN EFI_HANDLE *ChildHandleBuffer OPTIONAL
);

struct _EFI_DRIVER_BINDING_PROTOCOL {
	EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED Supported;
	EFI_DRIVER_BINDING_PROTOCOL_START Start;
	EFI_DRIVER_BINDING_PROTOCOL_STOP Stop;
	UINT32 Version;
	EFI_HANDLE ImageHandle;
	EFI_HANDLE DriverBindingHandle;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
