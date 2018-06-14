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
// $Header: /Alaska/BIN/Core/Include/Protocol/HiiUtilities.h 3     5/23/12 3:54p Artems $
//
// $Revision: 3 $
//
// $Date: 5/23/12 3:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/HiiUtilities.h $
// 
// 3     5/23/12 3:54p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Rewrite GraphicsConsole driver to draw strings as a
// whole,
// not symbol-by-symbol for performance reasons
// [Files]  		HiiUtilities.h, AmiDxeLib.h, EfiLib.h, GC.c, UefiHiiUtils.c
// 
// 2     2/23/10 10:14p Felixp
// SetBrowserData function is added
// 
// 1     10/09/09 3:15p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	HiiUtilities.h
//
// Description:	HII Utilities Protocol
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_UTILITIES_PROTOCOL__H__
#define __HII_UTILITIES_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

// {67B5787C-0E6A-4796-943E-A093B73A0267}
#define HII_UTILITIES_PROTOCOL_GUID \
    { 0x67b5787c, 0xe6a, 0x4796, 0x94, 0x3e, 0xa0, 0x93, 0xb7, 0x3a, 0x2, 0x67 }

GUID_VARIABLE_DECLARATION(gHiiUtilitiesProtocolGuid,HII_UTILITIES_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#if EFI_SPECIFICATION_VERSION>0x20000
#include <Protocol/HiiConfigAccess.h>
#else
#include <Protocol/FormCallBack.h >
#endif

typedef struct _CALLBACK_INFO CALLBACK_INFO;

typedef VOID(*INIT_HII_PACK)(
	EFI_HII_HANDLE HiiHandle,
	CALLBACK_INFO *pCallBackFound
);

struct _CALLBACK_INFO{
	EFI_GUID *pGuid;
#if EFI_SPECIFICATION_VERSION>0x20000
	EFI_HII_CONFIG_ACCESS_PROTOCOL *pFormCallback;
#else
	EFI_FORM_CALLBACK_PROTOCOL *pFormCallback;
#endif
	UINT16 Class, SubClass;
	EFI_HII_HANDLE HiiHandle;
};

typedef EFI_STATUS (EFIAPI *HII_UTILS_LOAD_RESOURCES)(
	IN EFI_HANDLE ImageHandle, IN UINTN NumberOfCallbacks,
	IN CALLBACK_INFO *CallbackInfo, IN INIT_HII_PACK InitFunction OPTIONAL
);

typedef EFI_STATUS (EFIAPI *HII_UTILS_LOAD_STRINGS)(
	EFI_HANDLE ImageHandle, OUT EFI_HII_HANDLE *HiiHandle
);

typedef EFI_STATUS (EFIAPI *HII_UTILS_GET_STRING)(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, 
	IN OUT UINTN *StringSize, OUT EFI_STRING String
);

typedef EFI_STATUS (EFIAPI *HII_UTILS_SET_STRING)(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, IN EFI_STRING String
);

typedef EFI_STATUS (EFIAPI *HII_UTILS_PUBLISH_PACKAGES)(
    IN VOID *PackagePointers, IN UINTN NumberOfPackages, 
    IN EFI_GUID *PackageGuid, IN EFI_HANDLE DriverHandle OPTIONAL,
    OUT EFI_HII_HANDLE *HiiHandle
);

typedef EFI_STATUS (EFIAPI *HII_UTILS_GET_BROWSER_DATA)(
    IN UINTN *BufferSize, OUT VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid OPTIONAL,
    IN CONST CHAR16 *VarStoreName  OPTIONAL
);

typedef EFI_STATUS (EFIAPI *HII_UTILS_SET_BROWSER_DATA)(
    IN UINTN BufferSize, IN VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid, OPTIONAL 
    IN CONST CHAR16 *VarStoreName  OPTIONAL
);

typedef EFI_STATUS (EFIAPI *HII_UTILS_GET_GLYPH_WIDTH)(
    IN CHAR16 Char, OUT UINT16 *Width
);

typedef struct{
    HII_UTILS_LOAD_RESOURCES LoadResources;
    HII_UTILS_LOAD_STRINGS LoadStrings;
    HII_UTILS_PUBLISH_PACKAGES PublishPackages;
    HII_UTILS_GET_BROWSER_DATA GetBrowserData;
    HII_UTILS_SET_BROWSER_DATA SetBrowserData;
    HII_UTILS_GET_STRING GetString;
    HII_UTILS_SET_STRING SetString;
    HII_UTILS_GET_GLYPH_WIDTH GetGlyphWidth;
}HII_UTILITIES_PROTOCOL;

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
