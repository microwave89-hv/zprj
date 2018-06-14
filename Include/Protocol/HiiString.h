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
// $Header: /Alaska/BIN/Core/Include/Protocol/HiiString.h 3     5/23/12 3:51p Artems $
//
// $Revision: 3 $
//
// $Date: 5/23/12 3:51p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/HiiString.h $
// 
// 3     5/23/12 3:51p Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Change in input parameter of protocol function
// [Files]  		HiiString.h
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
// Name:	<HiiString.h>
//
// Description:	Hii String protocol header file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_STRING__H__
#define __HII_STRING__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <UefiHii.h>

#define EFI_HII_STRING_PROTOCOL_GUID \
    { 0xfd96974, 0x23aa, 0x4cdc, 0xb9, 0xcb, 0x98, 0xd1, 0x77, 0x50, 0x32, 0x2a }

GUID_VARIABLE_DECLARATION(gEfiHiiStringProtocolGuid, EFI_HII_STRING_PROTOCOL_GUID);

typedef struct _EFI_HII_STRING_PROTOCOL EFI_HII_STRING_PROTOCOL;

typedef EFI_STATUS
(EFIAPI *EFI_HII_NEW_STRING) (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	OUT EFI_STRING_ID				 *StringId,
	IN CONST CHAR8					 *Language,
	IN CONST CHAR16					 *LanguageName OPTIONAL,
	IN CONST EFI_STRING				 String,
	IN CONST EFI_FONT_INFO			 *StringFontInfo
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_GET_STRING) (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN CONST CHAR8					 *Language,
	IN EFI_HII_HANDLE				 PackageList,
	IN EFI_STRING_ID				 StringId,
	OUT EFI_STRING					 String,
	IN OUT UINTN					 *StringSize,
	OUT EFI_FONT_INFO				 **StringFontInfo OPTIONAL
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_SET_STRING) (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN EFI_STRING_ID				 StringId,
	IN CONST CHAR8					 *Language,
	IN CONST EFI_STRING				 String,
	IN CONST EFI_FONT_INFO			 *StringFontInfo OPTIONAL
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_GET_LANGUAGES) (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN OUT CHAR8					 *Languages,
	IN OUT UINTN					 *LanguagesSize
);

typedef EFI_STATUS
(EFIAPI *EFI_HII_GET_2ND_LANGUAGES) (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN CONST CHAR8*					 FirstLanguage,
	IN OUT CHAR8					 *SecondLanguages,
	IN OUT UINTN					 *SecondLanguagesSize
);

struct _EFI_HII_STRING_PROTOCOL {
	EFI_HII_NEW_STRING NewString;
	EFI_HII_GET_STRING GetString;
	EFI_HII_SET_STRING SetString;
	EFI_HII_GET_LANGUAGES GetLanguages;
	EFI_HII_GET_2ND_LANGUAGES GetSecondaryLanguages;
};

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