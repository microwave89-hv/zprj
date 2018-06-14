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
// $Header: /Alaska/BIN/Core/Include/Protocol/UgaDraw.h 3     12/20/06 1:46p Felixp $
//
// $Revision: 3 $
//
// $Date: 12/20/06 1:46p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/UgaDraw.h $
// 
// 3     12/20/06 1:46p Felixp
// Updated to co-exist with Graphics Output Protocol header
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     11/08/04 1:41p Felixp
// 
// 3     11/05/04 6:02p Robert
// 
// 2     11/05/04 5:40p Robert
// 
// 1     11/05/04 5:34p Robert
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: UgaDraw_h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __UGA_DRAW_PROTOCOL_H__
#define __UGA_DRAW_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_UGA_DRAW_PROTOCOL_GUID \
		{ 0x982c298b, 0xf4fa, 0x41cb, 0xb8, 0x38, 0x77, 0xaa, 0x68, 0x8f, 0xb8, 0x39 }

GUID_VARIABLE_DECLARATION(gEfiUgaDrawProtocolGuid,EFI_UGA_DRAW_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/GraphicsOutput.h>

typedef struct _EFI_UGA_DRAW_PROTOCOL EFI_UGA_DRAW_PROTOCOL;


//=============================================================================
// Structure Definitions

typedef EFI_GRAPHICS_OUTPUT_BLT_PIXEL EFI_UGA_PIXEL;

typedef enum {
	EfiUgaVideoFill,
	EfiUgaVideoToBltBuffer,
	EfiUgaBltBufferToVideo,
	EfiUgaVideoToVideo,
	EfiUgaBltMax
	} EFI_UGA_BLT_OPERATION;

//=============================================================================
// Protocol typedefs

typedef EFI_STATUS (EFIAPI *EFI_UGA_DRAW_PROTOCOL_GET_MODE) (
			IN EFI_UGA_DRAW_PROTOCOL *This,
			OUT UINT32 *HorizontalResolution,
			OUT UINT32 *VerticalResolution,
			OUT UINT32 *ColorDepth,
			OUT UINT32 *RefreshRate
			);


typedef EFI_STATUS (EFIAPI *EFI_UGA_DRAW_PROTOCOL_SET_MODE) (
			IN EFI_UGA_DRAW_PROTOCOL *This,
			IN UINT32 HorizontalResolution,
			IN UINT32 VerticalResolution,
			IN UINT32 ColorDepth,
			IN UINT32 RefreshRate
			);


typedef EFI_STATUS (EFIAPI *EFI_UGA_DRAW_PROTOCOL_BLT) (
			IN EFI_UGA_DRAW_PROTOCOL *This,
			IN OUT EFI_UGA_PIXEL *BltBuffer, OPTIONAL
			IN EFI_UGA_BLT_OPERATION BltOperation,
			IN UINTN SourceX,
			IN UINTN SourceY,
			IN UINTN DestinationX,
			IN UINTN DestinationY,
			IN UINTN Width,
			IN UINTN Height,
			IN UINTN Delta OPTIONAL
			);

typedef struct _EFI_UGA_DRAW_PROTOCOL {
	EFI_UGA_DRAW_PROTOCOL_GET_MODE GetMode;
	EFI_UGA_DRAW_PROTOCOL_SET_MODE SetMode;
	EFI_UGA_DRAW_PROTOCOL_BLT Blt;
	} EFI_UGA_DRAW_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
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
