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
// $Header: /Alaska/BIN/Core/Include/Protocol/HiiFont.h 6     5/23/12 3:41p Artems $
//
// $Revision: 6 $
//
// $Date: 5/23/12 3:41p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/HiiFont.h $
// 
// 6     5/23/12 3:41p Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Minor change in protocol function input parameter
// [Files]  		HiiFont.h
// 
// 5     10/25/11 6:55p Artems
// Renamed CLIP flags according to UEFI 2.3.1 spec
// 
// 4     12/04/09 12:14p Felixp
// 
// 3     12/03/09 6:02p Artems
// moved font related structures outside pack pragma
// 
// 2     10/13/09 6:06p Felixp
// Hii.h renamed to UefiHii.h
// 
// 1     10/09/09 3:52p Felixp
// 
// 1     2/27/09 3:55p Artems
// Initial check-in
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<HiiFont.h>
//
// Description:	Hii Font protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_FONT__H__
#define __HII_FONT__H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_HII_FONT_PROTOCOL_GUID \
    { 0xe9ca4775, 0x8657, 0x47fc, 0x97, 0xe7, 0x7e, 0xd6, 0x5a, 0x8, 0x43, 0x24 }

GUID_VARIABLE_DECLARATION(gEfiHiiFontProtocolGuid, EFI_HII_FONT_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <UefiHii.h>
#include <Protocol/GraphicsOutput.h>

typedef UINT32 EFI_HII_OUT_FLAGS;

#define EFI_HII_OUT_FLAG_CLIP         0x00000001
#define EFI_HII_OUT_FLAG_WRAP         0x00000002
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_Y 0x00000004
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_X 0x00000008
#define EFI_HII_OUT_FLAG_TRANSPARENT  0x00000010
#define EFI_HII_IGNORE_IF_NO_GLYPH    0x00000020
#define EFI_HII_IGNORE_LINE_BREAK     0x00000040
#define EFI_HII_DIRECT_TO_SCREEN      0x00000080

typedef UINT32 EFI_FONT_INFO_MASK;

#define EFI_FONT_INFO_SYS_FONT		 0x00000001
#define EFI_FONT_INFO_SYS_SIZE		 0x00000002
#define EFI_FONT_INFO_SYS_STYLE		 0x00000004
#define EFI_FONT_INFO_SYS_FORE_COLOR 0x00000010
#define EFI_FONT_INFO_SYS_BACK_COLOR 0x00000020
#define EFI_FONT_INFO_RESIZE		 0x00001000
#define EFI_FONT_INFO_RESTYLE		 0x00002000
#define EFI_FONT_INFO_ANY_FONT		 0x00010000
#define EFI_FONT_INFO_ANY_SIZE		 0x00020000
#define EFI_FONT_INFO_ANY_STYLE		 0x00040000

typedef struct _EFI_HII_ROW_INFO {
	UINTN StartIndex;
	UINTN EndIndex;
	UINTN LineHeight;
	UINTN LineWidth;
	UINTN BaselineOffset;
} EFI_HII_ROW_INFO;

typedef struct _EFI_FONT_DISPLAY_INFO {
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL	ForegroundColor;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL	BackgroundColor;
	EFI_FONT_INFO_MASK				FontInfoMask;
	EFI_FONT_INFO					FontInfo;
} EFI_FONT_DISPLAY_INFO;

typedef struct _EFI_IMAGE_OUTPUT {
	UINT16 Width;
	UINT16 Height;
	union {
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Bitmap;
		EFI_GRAPHICS_OUTPUT_PROTOCOL  *Screen;
	} Image;
} EFI_IMAGE_OUTPUT;

//Protocol functions prototypes

typedef struct _EFI_HII_FONT_PROTOCOL EFI_HII_FONT_PROTOCOL;

typedef EFI_STATUS
(EFIAPI *EFI_HII_STRING_TO_IMAGE) (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN EFI_HII_OUT_FLAGS			Flags,
	IN CONST EFI_STRING				String,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo OPTIONAL,
	IN OUT EFI_IMAGE_OUTPUT			**Blt,
	IN UINTN						BltX,
	IN UINTN						BltY,
	OUT EFI_HII_ROW_INFO			**RowInfoArray OPTIONAL,
	OUT UINTN						*RowInfoArraySize OPTIONAL,
	OUT UINTN						*ColumnInfoArray OPTIONAL
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_STRING_ID_TO_IMAGE) (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN EFI_HII_OUT_FLAGS			Flags,
	IN EFI_HII_HANDLE				PackageList,
	IN EFI_STRING_ID				StringId,
	IN CONST CHAR8*					Language,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo OPTIONAL,
	IN OUT EFI_IMAGE_OUTPUT			**Blt,
	IN UINTN						BltX,
	IN UINTN						BltY,
	OUT EFI_HII_ROW_INFO			**RowInfoArray OPTIONAL,
	OUT UINTN						*RowInfoArraySize OPTIONAL,
	OUT UINTN						*ColumnInfoArray OPTIONAL
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_GET_GLYPH) (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN CHAR16						Char,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo,
	OUT EFI_IMAGE_OUTPUT			**Blt,
	OUT UINTN						*Baseline OPTIONAL
);

typedef VOID *EFI_FONT_HANDLE;

typedef EFI_STATUS
(EFIAPI *EFI_HII_GET_FONT_INFO) (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN OUT EFI_FONT_HANDLE			*FontHandle,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfoIn, OPTIONAL
	OUT EFI_FONT_DISPLAY_INFO		**StringInfoOut,
	IN CONST EFI_STRING				String OPTIONAL
);

struct _EFI_HII_FONT_PROTOCOL {
	EFI_HII_STRING_TO_IMAGE		StringToImage;
	EFI_HII_STRING_ID_TO_IMAGE	StringIdToImage;
	EFI_HII_GET_GLYPH			GetGlyph;
	EFI_HII_GET_FONT_INFO		GetFontInfo;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
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