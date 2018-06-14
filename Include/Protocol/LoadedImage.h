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
// $Header: /Alaska/BIN/Core/Include/Protocol/LoadedImage.h 5     11/08/10 6:15p Felixp $
//
// $Revision: 5 $
//
// $Date: 11/08/10 6:15p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/LoadedImage.h $
// 
// 5     11/08/10 6:15p Felixp
// The Core source files are updated to remove upper ASCII characters
// (above 128) 
// from the comment blocks. The characters caused build errors 
// with Japanese version of Microsoft compiler.
// 
// 4     5/22/09 1:18p Felixp
// Clean  up
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:35a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     2/19/04 4:31p Felixp
// 
// 1     2/16/04 5:11p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	LoadedImage.h
//
// Description:	EFI_LOADED_IMAGE_PROTOCOL Protocol Definition.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LOADED_IMAGE_PROTOCOL_H__
#define __LOADED_IMAGE_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
	{0x5B1B31A1,0x9562,0x11d2,0x8E,0x3F,0x00,0xA0,0xC9,0x69,0x72,0x3B}

GUID_VARIABLE_DECLARATION(gEfiLoadedImageProtocolGuid, EFI_LOADED_IMAGE_PROTOCOL_GUID);

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION 0x1000

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	EFI_UNLOAD
//
// Description:	Unloads an image from memory.
//
// Input:
//	IN EFI_HANDLE ImageHandle - The handle to the image to unload.
//
// Output: EFI_STATUS
//	Status Codes Returned
//		EFI_SUCCESS - The image was unloaded.
//		EFI_INVALID_PARAMETER - The ImageHandle was not valid.
//
//<AMI_PHDR_END>
//**********************************************************************
typedef EFI_STATUS (EFIAPI *EFI_UNLOAD) (
	IN EFI_HANDLE ImageHandle
);

//**********************************************************************
//<AMI_THDR_START>
//
// Name: EFI_LOADED_IMAGE_PROTOCOL
//
// Fields: Name	Type	Description
//	Revision		UINT32				Defines the revision of the EFI_LOADED_IMAGE_PROTOCOL structure.
//	ParentHandle	EFI_HANDLE			Parent image's image handle. NULL if the image is loaded directly from the firmware's boot manager.
//	SystemTable		EFI_SYSTEM_TABLE*	The image's EFI system table pointer.
//	DeviceHandle	EFI_HANDLE			The device handle that the EFI Image was loaded from. 
//	FilePath		EFI_DEVICE_PATH_PROTOCOL*	A pointer to the file path portion specific to DeviceHandle that the EFI Image was loaded from.
//	Reserved		VOID*				Reserved. DO NOT USE.
//	LoadOptionsSize	UINT32				The size in bytes of LoadOptions.
//	LoadOptions		VOID*				A pointer to the image's binary load options.
//	ImageBase		VOID*				The base address at which the image was loaded.
//	ImageSize		UINT64				The size in bytes of the loaded image.
//	ImageCodeType	EFI_MEMORY_TYPE	The Memory type that the code sections were loaded as.
//	ImageDataType	EFI_MEMORY_TYPE	The Memory type that the data sections were loaded as.
//	Unload			EFI_IMAGE_UNLOAD	Function that unloads the image.
//
// Description:	EFI_LOADED_IMAGE_PROTOCOL protocol interface structure
//
//<AMI_THDR_END>
//**********************************************************************
typedef struct {
	UINT32 Revision;
	EFI_HANDLE ParentHandle;
	EFI_SYSTEM_TABLE *SystemTable;
	// Source location of the image
	EFI_HANDLE DeviceHandle;
	EFI_DEVICE_PATH_PROTOCOL *FilePath;
	VOID *Reserved;
	// Image's load options
	UINT32 LoadOptionsSize;
	VOID *LoadOptions;
	// Location where image was loaded
	VOID *ImageBase;
	UINT64 ImageSize;
	EFI_MEMORY_TYPE ImageCodeType;
	EFI_MEMORY_TYPE ImageDataType;
	EFI_UNLOAD Unload;
} EFI_LOADED_IMAGE_PROTOCOL;

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
