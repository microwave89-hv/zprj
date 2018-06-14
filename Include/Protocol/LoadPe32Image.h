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
// $Header: /Alaska/BIN/Core/Include/Protocol/LoadPe32Image.h 2     3/13/06 1:40a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/LoadPe32Image.h $
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     4/27/05 11:27a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	LoadPe32Image.h
//
// Description:	EFI_PE32_IMAGE_PROTOCOL protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LOAD_PE32_IMAGE_PROTOCOL_H__
#define __LOAD_PE32_IMAGE_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define PE32_IMAGE_PROTOCOL_GUID  \
  {0x5cb5c776,0x60d5,0x45ee,0x88,0x3c,0x45,0x27,0x8,0xcd,0x74,0x3f }

GUID_VARIABLE_DECLARATION(gEfiLoadPeImageGuid, PE32_IMAGE_PROTOCOL_GUID);

#define EFI_LOAD_PE_IMAGE_ATTRIBUTE_NONE                                 0x00
#define EFI_LOAD_PE_IMAGE_ATTRIBUTE_RUNTIME_REGISTRATION                 0x01
#define EFI_LOAD_PE_IMAGE_ATTRIBUTE_DEBUG_IMAGE_INFO_TABLE_REGISTRATION  0x02

typedef struct _EFI_PE32_IMAGE_PROTOCOL EFI_PE32_IMAGE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *LOAD_PE_IMAGE)(
	IN EFI_PE32_IMAGE_PROTOCOL *This,
	IN EFI_HANDLE ParentImageHandle,
	IN EFI_DEVICE_PATH_PROTOCOL	*FilePath,
	IN VOID *SourceBuffer OPTIONAL, IN UINTN SourceSize,
	IN EFI_PHYSICAL_ADDRESS DstBuffer OPTIONAL,
	IN OUT UINTN *NumberOfPages OPTIONAL,
	OUT EFI_HANDLE *ImageHandle,
	OUT EFI_PHYSICAL_ADDRESS *EntryPoint OPTIONAL,
	IN UINT32 Attribute
);

typedef EFI_STATUS (EFIAPI *UNLOAD_PE_IMAGE)(
	IN EFI_PE32_IMAGE_PROTOCOL *This, IN EFI_HANDLE ImageHandle
);

struct _EFI_PE32_IMAGE_PROTOCOL {
	LOAD_PE_IMAGE LoadPeImage;
	UNLOAD_PE_IMAGE UnLoadPeImage;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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