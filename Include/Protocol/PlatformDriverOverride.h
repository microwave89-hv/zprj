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
// $Header: /Alaska/BIN/Core/Include/Protocol/PlatformDriverOverride.h 3     3/13/06 1:40a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/PlatformDriverOverride.h $
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:36a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     3/13/04 5:13p Felixp
// 
// 1     3/13/04 4:36p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	PlatformDriverOverride.h
//
// Description:	EFI_PLATFORM_DRIVER_OVERRIDE Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL__H__
#define __EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID \
	{ 0x6b30c738,0xa391,0x11d4,0x9a,0x3b,0x00,0x90,0x27,0x3f,0xc1,0x4d }

GUID_VARIABLE_DECLARATION(gEfiPlatformDriverOverrideProtocolGuid,EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID);

typedef struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER) (
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_HANDLE *DriverImageHandle
);

typedef EFI_STATUS (EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH) (
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN OUT EFI_DEVICE_PATH_PROTOCOL **DriverImagePath
);

typedef EFI_STATUS (EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED) (
	IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *DriverImagePath,
	IN EFI_HANDLE DriverImageHandle
);

struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL {
	EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER GetDriver;
	EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH GetDriverPath;
	EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED DriverLoaded;
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
