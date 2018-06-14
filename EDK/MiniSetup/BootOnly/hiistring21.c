//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/BootOnly/hiistring21.c $
//
// $Author: Premkumara $
//
// $Revision: 30 $
//
// $Date: 9/08/14 12:50p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/BootOnly/hiistring21.c $
// 
// 30    9/08/14 12:50p Premkumara
// [TAG]  		EIP182798
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Build error when token TSE_USE_GETGYLPH_PRINTLENGH = 1
// [RootCause]  	 Variable "Status" is not declared in
// UefiHiiTestPrintLength() function when token is enabled.
// [Solution]  	Handled Status variable properly in both the case
// [Files]  		HiiString21.c
// 
// 29    9/05/14 2:29p Premkumara
// Moved below functions from HiiString21.c to CommonHelper.c
//   - IsSupportDefaultForStringControl()
//   - IsTseBestTextGOPModeSupported()
// 
// 28    9/05/14 6:56a Premkumara
// added IsTseBestTextGOPModeSupported() defination to resolve build error
// 
// 27    8/28/14 6:46a Premkumara
// [TAG]	EIP93340
// [Category]	Improvement
// [Description]	- Defaults can be given to string type controls using tag
// "Default = STRING_TOKEN(STR_DEFAULT_STRING)".
// - New token TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL is introduced for
// this support.
// - Enabling this TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL token will
// display default string mention in setup.
// - On loading optimal defaults also string will load default mentioned
// in default value tag.
// [Files] AMITSE.sdl, HiiString21.c, TseAdvanced.c, MiniSetupExt.c, Hii.c
// 
// 26    8/28/14 5:41a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 25    5/08/14 9:12p Arunsb
// [TAG]  			EIP162981
// [Category]  	Improvement
// [Description]  	Configuring default Password through SDL token
// TSE_ADMIN_PASSWORD, TSE_USER_PASSWORD handled from binary.
// 
// 24    10/18/12 11:42a Rajashakerg
// [TAG]  		EIP 97951
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Creation of TSE which does not access NVRAM during recovery
// [RootCause]  	TSE get Platform lang every time using VarGetNvramName 
// [Solution]  	Moved the code accessing PlatformLang to uefi2.1.
// [Files]  		hiistring21.c, minisetupext.c, hiistring20.c
// 
// 21    9/25/12 6:19a Rajashakerg
// [TAG]  		EIP85564
// [Category]  	Improvement
// [Description]  	UefiHiiTestPrintLength function needs optimization
// [Files]  		TseLiteCommon.c, hiistring21.c
// 
// 20    9/21/12 9:32a Premkumara
// [TAG]  		EIP97951
// [Solution ]                 Resolved build issue because of adding
// space in #define EfiCopyMem and #define EfiZeroMem
// 
// 19    9/21/12 3:42a Premkumara
// [TAG]  		EIP 97951
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Creation of TSE which does not access NVRAM during recovery
// [RootCause]  	TSE get Platform lang every time using VarGetNvramName 
// [Solution]  	Created cache to store Platform lang intially and using
// cached value instead of
// reading from NVRAM (VarGetNvramName ).
// [Files]  		hiistring21.c, minisetupext.c
// 
// 18    5/29/12 3:27a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 17    5/28/12 7:27a Rajashakerg
// [TAG]  		EIP85564
// [Category]  	Improvement
// [Description]  	UefiHiiTestPrintLength function needs optimization
// [Files]  		TseLiteCommon.c, hiistring21.c
// 
// 16    1/25/12 8:01a Rajashakerg
// [TAG]  		EIP81617 
// [Category]  	Improvement
// [Description]  	Avoiding memory leaks in TSE
// [Files]  		hiistring21.c, CommonHelper.c, notify.c
// 
// 15    1/20/12 5:04a Rajashakerg
// [TAG]  		EIP77875 
// [Category]  	Improvement
// [Description]  	Minisetup: Memory leaks in text browser
// [Files]  		Uefi21Wapper.c, hiistring21.c, variable.c
// 
// 14    12/08/11 7:49a Premkumara
// [TAG]  		EIP72588
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System execption error if print string +"*" in Japanese &
// French 
// [RootCause]  	can't get correct length size, because this data have
// include height data
// [Solution]  	Fixed the length
// [Files]  		hiistring21.c
// 
// 13    12/01/11 12:55p Premkumara
// [TAG]  		EIP75536
// [Category]  	Improvement
// [Description]  	1.String handling inside the callbacks in
// Minisetup.Adding Null termination for String and Password control type.
// 2.Iterate to check the available language and add/change the string
// only for the passed language.
// [Files]  		HiiCallback.c, hiistring21.c
// 
// 12    11/30/11 12:23a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 11    7/01/11 5:14a Arunsb
// FormBrowser2.h included for resolving build error.
// 
// 10    6/30/11 4:08a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Boot device repair operation related functions added.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 9     6/29/11 6:24a Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Hot key boot option support in TSE as per UEFI spec.
// section 3.1.6.
// [Files]         AMITSE.sdl, bootflow.c, bootflow.h, CommonHelper.c,
// commonoem.c, commonoem.h, boot.c,
//                 hiistring20.c, hiistring21.c and notify.c.
// 
// 8     6/22/11 2:45p Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Support for Hot key boot option in TSE as per UEFI
// spec. section 3.1.6.
// [Files]         AMITSE.sdl, CommonHelper.c, commonoem.c, commonoem.h,
// boot.c, hiistring20.c and hiistring21.c.
// 
// 7     11/15/10 11:05a Madhans
// [TAG]    	EIP47355
// [Category]	Defect
// [Symptom]	HiiAddString was overwrtting the exiting strings when the
// projects support multiple language.
// [RootCause]  -
// [Solution]	Fixed the Uefi21HiiChangeStringLanguage() function to
// add/update the string only to specified lang.
// [Files]		hiistring21.c
// 
// 6     10/27/10 3:16p Madhans
// [TAG]    	EIP45875
// [Category]	Defect
// [Symptom]	Memory Leaks in Language reading functions.
// [RootCause] -
// [Solution]	Freed the memory after use.
// [Files]		hiistring21.c
// 
// 5     6/17/10 2:17p Madhans
// Refer Changelog.log.
// 
// 4     2/26/10 8:46p Madhans
// For Tse 2.01.1204. Refer Changelog.log file change history
// 
// 10    2/26/10 7:04p Madhans
// To void build issue when build with EDK
// 
// 9     2/19/10 8:07a Mallikarjunanv
// updated year in copyright message
// 
// 8     2/17/10 7:01p Madhans
// HiiString2BltBuffer() function updated to return the StringGlyphwidth
// If String not found in current lang Search in Default Lang. If not
// search in english.
// 
// 7     2/15/10 9:42p Madhans
// Wide Char Support
// 
// 6     1/09/10 3:04a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     10/28/09 5:36p Madhans
// 
// 3     7/31/09 4:55p Presannar
// HiiString21.c moved to Boot Only binary module
// Modifications done to build without EDK dependencies
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     3/31/09 3:34p Madhans
// Hii string support for UEFI 2.0 and UEFI 2.1
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		hiistring21.c
//
// Description:	This file contains code to handle UEFI2.1 supported hii strings.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifdef TSE_FOR_APTIO_4_50
#include "Token.h"  
#include "Efi.h"
#include "Protocol/DevicePath.h"
#else
#include "tokens.h"
#include "efi.h"
#endif

#ifdef TSE_FOR_APTIO_4_50
#ifndef EFI_PROTOCOL_DEFINITION
#define TSE_STRINGIZE(a) #a
#define EFI_PROTOCOL_DEFINITION(a) TSE_STRINGIZE(Protocol/a.h)
#endif
#endif

#include EFI_PROTOCOL_DEFINITION (HiiString)
#include EFI_PROTOCOL_DEFINITION (HiiDatabase)
#include EFI_PROTOCOL_DEFINITION (HiiFont)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (SimpleTextIn)
#include EFI_PROTOCOL_DEFINITION (SimpleTextInEx)
#include EFI_PROTOCOL_DEFINITION (AmiKeycode)
#include EFI_PROTOCOL_DEFINITION (FormBrowser2)

#include "Mem.h"
#include "HiiLib.h"
#include "Variable.h"
#include "TseDrvHealth.h"       //Has TSE related driver health structures
#include "PwdLib.h"
#include "AmiLib.h"

#pragma pack(push,1)
typedef struct{
    EFI_GUID SubtypeGuid;
	UINT32 NumberOfPackages;
} RESOURCE_SECTION_HEADER;
#pragma pack(pop)

typedef struct HOT_KEYS
{
    EFI_KEY_DATA    KeyData;
    UINT16          BootOption;
    UINT32          BootOptionCrc;
}HOT_KEYS;
UINT32      CheckBootOptionMatch (UINT16 BootOption);
HOT_KEYS    *gHotKeysDetails = NULL;
UINTN       gHotKeysCount = 0;
UINTN       gAllocateKeysCount = 0;
#define HOTKEY_ALLOC_UNIT   10
#define HOT_KEY_SHIFT           0x00000100          
#define HOT_KEY_CTRL            0x00000200
#define HOT_KEY_ALT             0x00000400
#define HOT_KEY_LOGO            0x00000800
#define HOT_KEY_MENU            0x00001000
#define HOT_KEY_SYSREQ          0x00002000
#define MODIFIER_DUAL_KEYS 			0x000000FF          //For handling any of the two dual(ctrl, alt, shift and logo) keys pressed
#define RIGHT_LEFT_SHIFT_PRESSED	0x00000003
#define RIGHT_LEFT_CONTROL_PRESSED	0x0000000C
#define RIGHT_LEFT_ALT_PRESSED		0x00000030
#define RIGHT_LEFT_LOGO_PRESSED		0x000000C0
BOOLEAN CheckAdvShiftState (UINT32 AmiKeyShiftState, UINT32 CondShiftState);
extern INTN  gHotKeyBootOption;
VOID    SetBootOptionSupportVariable (UINT32);
BOOLEAN MetaiMatch (VOID *,IN CHAR16 *, IN CHAR16 *);
EFI_STATUS InitUnicodeCollectionProtocol (VOID **);

#define RFC_3066_ENTRY_SIZE (42 + 1)
#define GLYPH_WIDTH 8
#define GLYPH_HEIGHT 19
#define NG_SIZE 	19
#define WG_SIZE		38

#define MINI_SETUP_RESOURCE_SECTION_GUID \
	{0x97e409e6, 0x4cc1, 0x11d9, 0x81, 0xf6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
typedef EFI_GRAPHICS_OUTPUT_BLT_PIXEL EFI_UGA_PIXEL;

extern EFI_BOOT_SERVICES *gBS;
extern EFI_RUNTIME_SERVICES	*gRT;
extern /*EFI_HII_HANDLE*/VOID* gHiiHandle;

#if !TSE_APTIO_5_SUPPORT
EFI_GUID gEfiHiiFontProtocolGuid = EFI_HII_FONT_PROTOCOL_GUID;
#endif
EFI_GUID gEfiHiiDatabaseProtocolGuid = EFI_HII_DATABASE_PROTOCOL_GUID;
EFI_GUID gEfiHiiStringProtocolGuid = EFI_HII_STRING_PROTOCOL_GUID;

EFI_HII_STRING_PROTOCOL *gHiiString;
EFI_HII_DATABASE_PROTOCOL *gHiiDatabase;
EFI_HII_FONT_PROTOCOL *gHiiFont;

extern EFI_GUID gEfiGlobalVariableGuid;
CHAR8 *GlyphWidthCache = NULL;//EIP 85564 : UefiHiiTestPrintLength function needs optimization

CHAR8 *_GetSupportedLanguages(EFI_HII_HANDLE HiiHandle);
VOID _GetNextLanguage(CHAR8 **LangCode, CHAR8 *Lang);
EFI_STATUS UefiHiiWrapperGetString( EFI_HII_HANDLE handle, CHAR8 *Language, EFI_STRING_ID StringId, CHAR16 *buffer,UINTN *bufferSize );

extern VOID *EfiLibAllocatePool(IN UINTN AllocationSize);
extern EFI_STATUS HiiExtendedInitializeProtocol();
extern CHAR8* StrDup16to8(CHAR16 *String);
extern VOID *VarGetNvram( UINT32 variable, UINTN *size );
extern INTN EfiAsciiStrCmp(IN CHAR8 *String, IN CHAR8 *String2);
extern CHAR8 *StrDup8( CHAR8 *string );
extern EFI_STATUS ReadImageResource(EFI_HANDLE ImageHandle, EFI_GUID *pGuid,
					VOID **ppData, UINTN *pDataSize);
BOOLEAN AdvancedRepairSupported (VOID);
VOID DriverHealthSystemReset (VOID);
// Typecast EFI_KEY_OPTION to make it compatible Aptio 4 and 5
typedef struct {
  ///
  /// Specifies options about how the key will be processed.
  ///
  HOT_KEY_EFI_KEY_DATA  KeyData;
  ///
  /// The CRC-32 which should match the CRC-32 of the entire EFI_LOAD_OPTION to
  /// which BootOption refers. If the CRC-32s do not match this value, then this key
  /// option is ignored.
  ///
  UINT32             BootOptionCrc;
  ///
  /// The Boot#### option which will be invoked if this key is pressed and the boot option
  /// is active (LOAD_OPTION_ACTIVE is set).
  ///
  UINT16             BootOption;
  ///
  /// The key codes to compare against those returned by the
  /// EFI_SIMPLE_TEXT_INPUT and EFI_SIMPLE_TEXT_INPUT_EX protocols.
  /// The number of key codes (0-3) is specified by the EFI_KEY_CODE_COUNT field in KeyOptions.
  ///
  //EFI_INPUT_KEY      Keys[];
} AMI_EFI_KEY_OPTION;

CHAR16  gPlatformLang [20];			//EIP97951
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetSupportedLanguages
//
// Description:
//
// Parameter:
//
// Return value:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8 *_GetSupportedLanguages (EFI_HII_HANDLE HiiHandle)
{
  EFI_STATUS  status;
  UINTN       BufferSize;
  CHAR8       *LanguageString;

  status = HiiInitializeProtocol ();

  //
  // Collect current supported Languages for given HII handle
  //
  BufferSize = 0x1000;
  LanguageString = (CHAR8*)EfiLibAllocatePool (BufferSize);
  status = gHiiString->GetLanguages (gHiiString, HiiHandle, LanguageString, &BufferSize);
  if(status == EFI_BUFFER_TOO_SMALL)
  {
    MemFreePointer((VOID**)&LanguageString);
    LanguageString = (CHAR8*)EfiLibAllocatePool (BufferSize);
    status = gHiiString->GetLanguages (gHiiString, HiiHandle, LanguageString, &BufferSize);
  }

  if(EFI_ERROR(status))
  {
    LanguageString = NULL;
  }

  return LanguageString;
}

VOID _GetNextLanguage(CHAR8 **LangCode, CHAR8 *Lang)
{
  UINTN  Index;
  CHAR8  *StringPtr;

  if (LangCode == NULL || *LangCode == NULL)
  {
    *Lang = 0;
    return;
  }

  Index = 0;
  StringPtr = *LangCode;
  while (StringPtr[Index] != 0 && StringPtr[Index] != ';')
  {
    Index++;
  }

  MemCopy(Lang, StringPtr, Index);
  Lang[Index] = 0;

  if (StringPtr[Index] == ';')
  {
    Index++;
  }
  *LangCode = StringPtr + Index;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    HiiInitializeProtocol
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS
//					EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Uefi21HiiInitializeProtocol(VOID)
{
	EFI_STATUS Status = EFI_SUCCESS;

	Status = gBS->LocateProtocol(&gEfiHiiFontProtocolGuid, NULL, &gHiiFont);
	if(EFI_ERROR(Status))
	{
		goto DONE;
	}
	Status = gBS->LocateProtocol(&gEfiHiiDatabaseProtocolGuid, NULL, &gHiiDatabase);
	if(EFI_ERROR(Status))
	{
		goto DONE;
	}
	Status = gBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, &gHiiString);
	if(EFI_ERROR(Status))
	{
		goto DONE;
	}
	Status = HiiExtendedInitializeProtocol();

DONE:
	return Status;
}

UINT16 Uefi21HiiChangeStringLanguage(VOID* handle, UINT16 token, CHAR16 *lang, CHAR16 *string)
{
	EFI_STATUS		status = EFI_SUCCESS;
	UINT16			newToken = INVALID_TOKEN;
	CHAR8			*passedLang = (CHAR8 *)NULL;
	CHAR8			*Languages = (CHAR8 *)NULL;
	CHAR8			*LangStrings = (CHAR8 *)NULL;
	CHAR8			Lang[RFC_3066_ENTRY_SIZE];

	status = HiiInitializeProtocol();

	if((EFI_ERROR(status)) || (string == NULL))	
	{
		return (UINT16)INVALID_TOKEN;
	}

	passedLang = StrDup16to8(lang);

	Languages = _GetSupportedLanguages(handle);
	if(Languages == NULL)
		return INVALID_TOKEN;

	//
	//EIP-75536 Iterate through the languages supported by package list to see whether passed language is supported. If yes, add/change the string. 
	//
	LangStrings = Languages;
	while (*LangStrings != 0)
	{
		_GetNextLanguage (&LangStrings, Lang);

		if(EfiAsciiStrCmp(passedLang, Lang) == 0) 
		{
			if(token) 
			{
				status = gHiiString->SetString(gHiiString, handle, token, Lang, string, NULL);
				newToken = token;
			}
			else 
			{
				status = gHiiString->NewString(gHiiString, handle, &newToken, Lang, NULL, string, NULL);
			}

			if(EFI_ERROR(status)) 
			{
				newToken = INVALID_TOKEN;
			}
			break;
		}
	}

	MemFreePointer ((VOID **)&passedLang);//EIP 77875 : Freeing the allocated memory before returning
    MemFreePointer ((VOID **)&Languages);
	return newToken;
}


#define TSE_TO_STRING(a) #a
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	Uefi21HiiGetStringLanguage
//
// Description:	Returns the string for incoming token.
//						If lang is valid then return string for this lang
//						else return string for PlatformLang variable
//						else return english string - default
//
// Input:		Handle, string token and lang code
//
// Output:		Sting buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID * EfiLibAllocateZeroPool (IN  UINTN   AllocationSize);
VOID EfiStrCpy (IN CHAR16   *Destination, IN CHAR16   *Source);
#define EfiCopyMem(_Destination, _Source, _Length)  gBS->CopyMem((_Destination), (_Source), (_Length))
#define EfiZeroMem(_Destination, _Length)  gBS->SetMem((_Destination), (_Length), 0)
CHAR16 *Uefi21HiiGetStringLanguage(EFI_HII_HANDLE handle, UINT16 token, CHAR16 *lang)
{
	EFI_STATUS status;
	CHAR16 *buffer 	= 	NULL;
	UINTN bufferSize 	= 	0,Size=0;
	UINT8 *language 	= 	NULL;

	status = HiiInitializeProtocol();
	if ( EFI_ERROR(status) )
	{
		return buffer;
	}
	
	/* This is a Quick Fix. We need to get the Default Languag here. */
	if (lang)
		language = StrDup16to8 (lang);
	else
	{
		//EIP97951-Start
		//language = VarGetNvramName( L"PlatformLang", &gEfiGlobalVariableGuid, NULL, &Size );
		if (*gPlatformLang)		//gPlatformLang will filled in mainsetuploop only if any call comes before it get from NVRAM
		{
			language = EfiLibAllocateZeroPool (20 * sizeof (CHAR16));
			if (NULL != language)
			{
				EfiStrCpy ((CHAR16 *)language, gPlatformLang);
			}
		}
		else
		{
			language = VarGetNvramName( L"PlatformLang", &gEfiGlobalVariableGuid, NULL, &Size );
			if (NULL != language)
			{
 	      	EfiZeroMem (gPlatformLang, sizeof (gPlatformLang));
		   	EfiCopyMem (gPlatformLang, language, Size);
			}
		}
		//EIP97951-End		
	}
	if (NULL == language)//EIP-75351 Suppress the warnings from static code analyzer
		return NULL;	
	
	status = UefiHiiWrapperGetString(handle, language,token ,buffer, &bufferSize );
	
	if(status == EFI_INVALID_PARAMETER)
	{
		buffer = (CHAR16*)EfiLibAllocateZeroPool(sizeof(CHAR16));
		if(buffer == NULL)
		{
			return buffer;
		}
		status = UefiHiiWrapperGetString(handle, language,token ,buffer, &bufferSize );
	}
// String not found with currnet Lang
	if (( EFI_ERROR(status) ) && (bufferSize==0))
	{
		MemFreePointer( (VOID **)&language );
		language = StrDup8(TSE_TO_STRING(DEFAULT_LANGUAGE_CODE));
		status = UefiHiiWrapperGetString(handle, language,token ,buffer, &bufferSize );
// String not found in Default Lang
		if (( EFI_ERROR(status) )&&(bufferSize==0))
		{
			if(EfiAsciiStrCmp(language, "en-US")!=0)
			{
				MemFreePointer( (VOID **)&language );
				language = StrDup8("en-US");
				status = UefiHiiWrapperGetString(handle, language,token ,buffer, &bufferSize );
// string not found in english
				if (( EFI_ERROR(status) )&&(bufferSize==0))
				{
//81617 : Avoiding memory leaks in TSE
					MemFreePointer( (VOID **)&language );
					return buffer;
				}
			}
			else
			{
//81617 : Avoiding memory leaks in TSE
				MemFreePointer( (VOID **)&language );
				return buffer;
			}
		}
	}
	buffer = (CHAR16*)EfiLibAllocatePool( bufferSize );
	if ( buffer == NULL )
		return buffer;
	
	status = UefiHiiWrapperGetString(handle, language,token ,buffer, &bufferSize );
	
	if ( EFI_ERROR(status) )
		MemFreePointer( (VOID **)&buffer );
	MemFreePointer( (VOID **)&language );

	return buffer;
}

EFI_STATUS UefiHiiWrapperGetString( EFI_HII_HANDLE handle, CHAR8 *Language, EFI_STRING_ID StringId, CHAR16 *buffer,UINTN *bufferSize )
{
	if ( handle == INVALID_HANDLE )
		handle = gHiiHandle;

	return gHiiString->GetString(gHiiString, Language, handle, StringId, buffer, bufferSize, NULL);
}

#if TSE_USE_EDK_LIBRARY

#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION

EFI_STATUS LoadStrings(
	EFI_HANDLE ImageHandle, VOID * *pHiiHandle
)
{
	static EFI_GUID guidResourceSection= MINI_SETUP_RESOURCE_SECTION_GUID;
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_LOADED_IMAGE_PROTOCOL *pImage;
	RESOURCE_SECTION_HEADER *pSection;
	UINTN SectionSize;
	EFI_HII_PACKAGE_LIST_HEADER *pPackages = NULL;
	EFI_HII_PACKAGE_HEADER *pPack;

	Status = HiiInitializeProtocol();
	if (EFI_ERROR(Status))
		goto DONE;

	Status = gBS->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, &pImage);
	if (EFI_ERROR(Status))
		goto DONE;

	Status = ReadImageResource(ImageHandle,&guidResourceSection,&pSection,&SectionSize);
	if (EFI_ERROR(Status))
		goto DONE;

	pPack = (EFI_HII_PACKAGE_HEADER*)(pSection+1);
	if (pPack->Type==EFI_HII_PACKAGE_STRINGS)
	{
		pPackages = EfiLibAllocateZeroPool(sizeof(EFI_HII_PACKAGE_LIST_HEADER) +
			pPack->Length);
		pPackages->PackageListGuid = ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(pImage->FilePath))->NameGuid;
		pPackages->PackageLength = sizeof(EFI_HII_PACKAGE_LIST_HEADER) + pPack->Length;
		MemCopy(pPackages + 1, pPack, pPack->Length);
		Status = gHiiDatabase->NewPackageList(gHiiDatabase, pPackages, ImageHandle, (EFI_HII_HANDLE*)pHiiHandle);
	}
	else
	{
		Status = EFI_INVALID_PARAMETER;
	}
	MemFreePointer((VOID **)&pPackages);
	gBS->FreePool(pSection);

DONE:
	return Status;
}
#endif

#endif //#if TSE_USE_EDK_LIBRARY

UINTN Uefi21HiiGetGlyphWidth(VOID)
{
	return GLYPH_WIDTH;
}

UINTN Uefi21HiiGetGlyphHeight(VOID)
{
	return GLYPH_HEIGHT;
}

//----------------------------------------------------------------------------
// Patch to use UnicodeCollation until
// Aptio supports UnicodeCollation2 protocol
//----------------------------------------------------------------------------
#include EFI_PROTOCOL_DEFINITION(UnicodeCollation)
#if UEFI_2_1_SUPPORT 
#ifndef TSE_FOR_APTIO_4_50
#include EFI_PROTOCOL_DEFINITION(UnicodeCollation2)
#endif
#endif

EFI_STATUS GetUnicodeCollection2Protocol(VOID **Protocol)
{
	EFI_STATUS Status = EFI_SUCCESS;

	Status = gBS->LocateProtocol(
                &gEfiUnicodeCollation2ProtocolGuid,
                NULL,
                Protocol);
//----------------------------------------------------------------------------
// Patch to use UnicodeCollation until
// Aptio supports UnicodeCollation2 protocol
//----------------------------------------------------------------------------
	if(EFI_ERROR(Status))
	{
		Status = gBS->LocateProtocol(
                &gEfiUnicodeCollationProtocolGuid,
                NULL,
                Protocol);
	}

	return Status;
}
//EIP : 85564 STARTS
CHAR16 *TseSkipEscCode(CHAR16 *String);
UINTN EfiStrLen(IN CHAR16 *String);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EfiTestPrintLength
//
// Description:	function to get the printable lenght of the string
//
// Input:		CHAR16 *string
//
// Output:		Size of string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN UefiHiiTestPrintLength ( IN CHAR16   *String )
{

	UINTN Size = 0;

	if(String == NULL)
	{
		goto DONE;
	}

#if !TSE_USE_GETGYLPH_PRINTLENGH
	{
		EFI_STATUS Status = EFI_SUCCESS;
		EFI_IMAGE_OUTPUT *Blt = NULL;
		UINTN BltX = 0;
		UINTN BltY = 0;
		UINT32 Flag = EFI_HII_OUT_FLAG_WRAP;

		// Skip Esc Characters from String
		String = (UINT16* )TseSkipEscCode(String);
	
		Status = gHiiFont->StringToImage(gHiiFont, Flag, String, NULL, &Blt, BltX, BltY, NULL, NULL, NULL);
		if(EFI_ERROR(Status))
		{
			if(String != NULL)
				gBS->FreePool( String );
			goto DONE;
		}
		if(Blt)
		{
			Size = Blt->Width * Blt->Height;
			Size = Size/GLYPH_WIDTH;
            Size = Size/(Blt->Height/EFI_GLYPH_HEIGHT); // EIP72588
			MemFreePointer(&Blt->Image.Bitmap);
			MemFreePointer(&Blt);
		}

		if(String != NULL)
			gBS->FreePool( String );
	}
#else // Non Aptio case with EDK Nt32 emulation
	{
		EFI_STATUS Status = EFI_SUCCESS;
		UINTN StringLen = 0;
		UINT32 Index = 0;

  	    if (GlyphWidthCache == NULL) {
  		    // Allocate a 64k buffer to store the widths of each possible CHAR16 glyph
  		    GlyphWidthCache = EfiLibAllocateZeroPool(65536); 
  		    if (GlyphWidthCache == NULL)
  			    return 0;
  	    }
      		
  	    StringLen = EfiStrLen(String);
  	    while(Index < StringLen) //Get the glyph of each character
  	    {
  		    UINTN Baseline = 0;
  		    CHAR16 Character = String[Index];
      		
  		    if (*(GlyphWidthCache+Character) == 0) {
  			    EFI_IMAGE_OUTPUT *Blt = NULL;
      
				Status = gHiiFont->GetGlyph(gHiiFont, Character, NULL, &Blt, &Baseline);
				if(EFI_ERROR(Status) && Status != EFI_WARN_UNKNOWN_GLYPH)
				{
					goto DONE;
				}
  			    if(Blt == NULL)
  			    {
  				    Character = L' ';
  				    gHiiFont->GetGlyph(gHiiFont, Character, NULL, &Blt, &Baseline);
  			    }
  			    *(GlyphWidthCache+Character) = (CHAR8) Blt->Width;
  			    if(Blt)
  			    {
  				    MemFreePointer(&Blt->Image.Bitmap);
  				    MemFreePointer(&Blt);
  			    }			
  		    }
      
  		    Size += *(GlyphWidthCache+Character);
  		    Index++;
  	    }
  	    Size = ((Size/GLYPH_WIDTH)*NG_SIZE);
	}
#endif

DONE:

	return Size;
}
//EIP : 85564 ENDS

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiString2BltBuffer
//
// Description:	function to get the Blt for the message with the given attributes
//
// Input:		CHAR16 *Message, EFI_UGA_PIXEL Foreground, EFI_UGA_PIXEL Background, 
//				OUT	UINTN *Width, OUT EFI_UGA_PIXEL **BltBuffer
//
// Output:		Size of string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiString2BltBuffer(	CHAR16 *Message,
								EFI_UGA_PIXEL Foreground, 
								EFI_UGA_PIXEL Background, 
								OUT	UINTN *Width,
								OUT EFI_UGA_PIXEL **BltBuffer,
								OUT UINTN *BltGlyphWidth)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_IMAGE_OUTPUT *Blt = NULL;
  EFI_FONT_DISPLAY_INFO FontDisplayInfo={0};
  UINTN BltX = 0;
  UINTN BltY = 0;
  UINT32 Flag = EFI_HII_OUT_FLAG_WRAP;

  // Get the Font Display Info for use in StringToImage
  FontDisplayInfo.ForegroundColor = Foreground;
  FontDisplayInfo.BackgroundColor = Background;

  // Get the String To Image Blt Buffer
  Status = gHiiFont->StringToImage(gHiiFont, Flag, Message, &FontDisplayInfo, &Blt, BltX, BltY, NULL, NULL, NULL);
  if(EFI_ERROR(Status))
  {
    goto DONE;
  }
  *BltBuffer = Blt->Image.Bitmap;
  *BltGlyphWidth = *Width = Blt->Width;

  // Free Blt. Only Blt is freed. The Bitmap memory is not freed.
  if(Blt)
    MemFreePointer(&Blt);

DONE:
  return Status;
}

//EIP: 62631 Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RefreshBootKeysDetails
//
// Description:	Clears the boot key gloabl details
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RefreshBootKeysDetails (VOID)
{
    gHotKeysCount = 0;
    gAllocateKeysCount = 0;
    MemFreePointer ((VOID **)&gHotKeysDetails);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FormHotBootKeys
//
// Description:	Function to form the boot option hot keys
//
// Input:		CHAR16 * = Hot key name to retrieve the hot key details
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FormHotBootKeys (CHAR16 *VarName)
{
    UINT8           Keycount = 0;
    EFI_INPUT_KEY   *InputKey;
    HOT_KEYS        *ParseKey = NULL;
    UINTN		    size=0;
    UINT32          CRC32 = 0;
    AMI_EFI_KEY_OPTION  *HotKeyBuff = NULL;

    
    if (gHotKeysCount >= gAllocateKeysCount)
    {
        gHotKeysDetails = MemReallocateZeroPool (gHotKeysDetails, gHotKeysCount * sizeof (HOT_KEYS), ((gAllocateKeysCount + HOTKEY_ALLOC_UNIT) * sizeof (HOT_KEYS)) );
        if (NULL == gHotKeysDetails)
        {
            return;
        }
        gAllocateKeysCount = gAllocateKeysCount + HOTKEY_ALLOC_UNIT;
    }
    HotKeyBuff = VarGetNvramName (VarName, &gEfiGlobalVariableGuid, NULL, &size);
    if (NULL == HotKeyBuff)
    {
        return;
    }
    Keycount = HotKeyBuff->KeyData.Options.InputKeyCount;
    CRC32 = CheckBootOptionMatch (HotKeyBuff->BootOption);
    if ((!CRC32) || (CRC32 != HotKeyBuff->BootOptionCrc))             //For failure case CRC32 will return 0
    {
        return;
    }
    gHotKeysDetails [gHotKeysCount].KeyData.KeyState.KeyShiftState = SHIFT_STATE_VALID;         //Making valid shift state
    if (HotKeyBuff->KeyData.PackedValue & HOT_KEY_SHIFT)              //Checking for shift(special) keys, if anything found in data then we have to give the value for both the shifts/ctrls etc.,
    {
        gHotKeysDetails [gHotKeysCount].KeyData.KeyState.KeyShiftState |= RIGHT_LEFT_SHIFT_PRESSED;
    }
    if (HotKeyBuff->KeyData.PackedValue & HOT_KEY_CTRL)
    {
        gHotKeysDetails [gHotKeysCount].KeyData.KeyState.KeyShiftState |= RIGHT_LEFT_CONTROL_PRESSED;
    }
    if (HotKeyBuff->KeyData.PackedValue & HOT_KEY_ALT)
    {
        gHotKeysDetails [gHotKeysCount].KeyData.KeyState.KeyShiftState |= RIGHT_LEFT_ALT_PRESSED;
    }
    if (HotKeyBuff->KeyData.PackedValue & HOT_KEY_LOGO)
    {
        gHotKeysDetails [gHotKeysCount].KeyData.KeyState.KeyShiftState |= RIGHT_LEFT_LOGO_PRESSED;
    }
    if (HotKeyBuff->KeyData.PackedValue & HOT_KEY_MENU)
    {
        gHotKeysDetails [gHotKeysCount].KeyData.KeyState.KeyShiftState |= MENU_KEY_PRESSED;
    }
    if (HotKeyBuff->KeyData.PackedValue & HOT_KEY_SYSREQ)
    {
        gHotKeysDetails [gHotKeysCount].KeyData.KeyState.KeyShiftState |= SYS_REQ_PRESSED;
    }
    gHotKeysDetails [gHotKeysCount].BootOption = HotKeyBuff->BootOption;
    gHotKeysDetails [gHotKeysCount].BootOptionCrc = HotKeyBuff->BootOptionCrc;

    while (Keycount)
    {                                                       //Since the values are ORED the values may read at reverse also
        InputKey = (EFI_INPUT_KEY *)((UINT8 *)HotKeyBuff + (sizeof (EFI_KEY_OPTION) + ((Keycount-1) * sizeof (EFI_INPUT_KEY))));
        gHotKeysDetails [gHotKeysCount].KeyData.Key.ScanCode |= InputKey->ScanCode;
        gHotKeysDetails [gHotKeysCount].KeyData.Key.UnicodeChar |= InputKey->UnicodeChar;
        Keycount --;
    }
    gHotKeysCount ++;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FreeExtraKeyMemories
//
// Description:	Function to free the extra memories allocated
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FreeExtraKeyMemories (VOID)
{
    if (gHotKeysCount < gAllocateKeysCount)
    {
        gHotKeysDetails = MemReallocateZeroPool (gHotKeysDetails, gAllocateKeysCount * sizeof (HOT_KEYS), gHotKeysCount * sizeof (HOT_KEYS));
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FindandSetHotKeys
//
// Description:	Function to form the hot keys from NVRAM
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FindandSetHotKeys (VOID)
{
#ifndef STANDALONE_APPLICATION
    CHAR16		KeyPattern [] = L"Key[0-9a-f][0-9a-f][0-9a-f][0-9a-f]";
    UINTN		VarNameSize = 80;
    CHAR16		*VarName = NULL;
    EFI_GUID	VarGuid;
    UINTN		OldVarNameSize = 0;
    EFI_STATUS  Status = EFI_SUCCESS;
    VOID *		UnicodeInterface;
    
    OldVarNameSize = VarNameSize;
    VarName = EfiLibAllocateZeroPool(VarNameSize);
    if (NULL == VarName)
    {
        return;
    }
    RefreshBootKeysDetails ();
    SetBootOptionSupportVariable (EFI_BOOT_OPTION_SUPPORT_KEY);            //Indicates boot manager supports hot key boot
    Status = InitUnicodeCollectionProtocol (&UnicodeInterface);
    do
    { 
        Status = gRT->GetNextVariableName (&VarNameSize,
                    VarName,
                    &VarGuid);
        if (EFI_BUFFER_TOO_SMALL == Status)
        {
            //Allocate correct size
            VarName = MemReallocateZeroPool (
                        VarName,
                        OldVarNameSize,
                        VarNameSize);
            OldVarNameSize = VarNameSize;
            continue;
        }
        if (VarNameSize == ((EfiStrLen(L"keyXXXX")+1)*2))
        {
            if (MetaiMatch (UnicodeInterface, VarName, KeyPattern))
            {
                FormHotBootKeys (VarName);
            }
        }
        VarNameSize = OldVarNameSize;
    }while (EFI_NOT_FOUND != Status);
    FreeExtraKeyMemories ();
    MemFreePointer ((VOID **)&VarName);
#endif
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------------------
// Procedure:	CheckforHotKey
//
// Description:	Checks for the key pressed by user matches the boot key options
//
// Input:		AMI_EFI_KEY_DATA = Input key details pressed by user
//              UINT16 * = Boot index to return; Memory should be allocated by user              
//
// Output:		BOOLEAN TRUE = If boot option found for user pressed key
//                      FALSE = If boot index not found for user pressed key
//
//--------------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckforHotKey (AMI_EFI_KEY_DATA InputKey)
{
    UINTN		Count = 0;
    UINT32      CRC32 = 0;

    while (Count < gHotKeysCount)
    {
        if ( (gHotKeysDetails [Count].KeyData.Key.UnicodeChar == InputKey.Key.UnicodeChar)
				&&  (gHotKeysDetails [Count].KeyData.Key.ScanCode == InputKey.Key.ScanCode)
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
				&& (CheckAdvShiftState (InputKey.KeyState.KeyShiftState, gHotKeysDetails [Count].KeyData.KeyState.KeyShiftState))
#endif
        )
        {
            gHotKeyBootOption = (INTN)gHotKeysDetails->BootOption;
            return TRUE;
        }
        Count ++;
    }
    return FALSE;
}
//EIP: 62631 End

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------------
// Procedure:	FindtheMatchUptoEndNode
//
// Description:	Finds all agent handle which opens the input handle upto the last agent for the controller
//
//	Input:		EFI_HANDLE = Handle to be examined
//              EFI_HANDLE = Handle to be matched
//
// Output:		BOOLEAN => If handle matches return TRUE else FALSE
//
//------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN FindtheMatchUptoEndNode (EFI_HANDLE Handle, EFI_HANDLE DPHandle)
{
    EFI_GUID    **ppGuid = NULL;
    UINTN		Count = 0;
    UINTN		iIndex = 0;
    UINTN		jIndex = 0;
    VOID        *Interface = NULL;
    UINTN       EntryCount = 0;
    EFI_STATUS  Status = EFI_SUCCESS;
    BOOLEAN     RetStatus = FALSE;    
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer = NULL;
    
    Status = gBS->ProtocolsPerHandle (Handle, &ppGuid, &Count);
    if (EFI_ERROR (Status) )
    {
        return FALSE;
    }
    for (iIndex = 0; (iIndex < Count && !RetStatus); iIndex ++)
    {
        Status = gBS->OpenProtocolInformation (Handle, ppGuid [iIndex], &EntryBuffer, &EntryCount);
        if (EFI_ERROR (Status) )
        {
            continue;
        }
        for (jIndex = 0; (jIndex < EntryCount && !RetStatus); jIndex ++)
        {
            if (!(EntryBuffer [jIndex].Attributes & (EFI_OPEN_PROTOCOL_BY_DRIVER|EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)))
            {
                continue;
            }
            if ((EntryBuffer [jIndex].AgentHandle == DPHandle) || (EntryBuffer [jIndex].ControllerHandle == DPHandle) )
            {
                RetStatus = TRUE;
                break;
            }
            RetStatus = FindtheMatchUptoEndNode (EntryBuffer [jIndex].AgentHandle, DPHandle);
        }
        MemFreePointer ((VOID **)&EntryBuffer);
    }
    MemFreePointer ((VOID **)&ppGuid);
    return RetStatus;
}           

//<AMI_PHDR_START>
//--------------------------------------------------------------------------------------------
// Procedure:	MatchDPHandleWithDrvHlthHndls
//
// Description:	Checks whether the input handle has the driver health support
//
//	Input:		EFI_HANDLE = Handle to be examined
//
// Output:		BOOLEAN => TRUE if input handle has the driver health support else FALSE
//
//--------------------------------------------------------------------------------------------
//<AMI_PHDR_END> 
BOOLEAN MatchDPHandleWithDrvHlthHndls (EFI_HANDLE DPHandle)
{
	EFI_STATUS  Status;
	UINTN       NumHandles = 0;
	UINTN		Count = 0;
    UINTN       EntryCount = 0;
	EFI_HANDLE  *DriverHealthHandles = NULL;
	UINTN       iIndex = 0, jIndex = 0, kIndex = 0;
    EFI_GUID    **ppGuid = NULL;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *EntryBuffer = NULL;
    EFI_GUID EfiDriverHealthProtocolGuid = EFI_DRIVER_HEALTH_PROTOCOL_GUID;

	Status = gBS->LocateHandleBuffer (
				ByProtocol,
				&EfiDriverHealthProtocolGuid,
				NULL,
				&NumHandles,
				&DriverHealthHandles
				);
	if (EFI_ERROR (Status))
	{
		return FALSE;
	}
	for (iIndex = 0; iIndex < NumHandles; iIndex ++)
	{
        Status = gBS->ProtocolsPerHandle (DriverHealthHandles [iIndex], &ppGuid, &Count);
        if (EFI_ERROR (Status) )
        {
            return FALSE;
        }
        for (jIndex = 0; jIndex < Count; jIndex++)
    	{
            Status = gBS->OpenProtocolInformation (DriverHealthHandles [iIndex], ppGuid [jIndex], &EntryBuffer, &EntryCount);
            if (EFI_ERROR (Status) )
            {
                continue;
            }
            for (kIndex = 0; kIndex < EntryCount; kIndex ++)
            {
                if (!(EntryBuffer [kIndex].Attributes & (EFI_OPEN_PROTOCOL_BY_DRIVER|EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)) )
                {
                    continue;
                }
                if ((EntryBuffer [kIndex].AgentHandle == DPHandle) || (EntryBuffer [kIndex].ControllerHandle == DPHandle))
                {
                    MemFreePointer ((VOID **)&DriverHealthHandles);
                    return TRUE;
                }
                if (TRUE == FindtheMatchUptoEndNode (EntryBuffer [kIndex].AgentHandle, DPHandle) ) //ControllerHandle is NULL here
                {
                    MemFreePointer ((VOID **)&DriverHealthHandles);   
                    return TRUE;
                }
            }
            MemFreePointer ((VOID **)&EntryBuffer);
        }
        MemFreePointer ((VOID **)&ppGuid);
    }
    MemFreePointer ((VOID **)&DriverHealthHandles);
    return FALSE;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------------
// Procedure:	CheckForDeviceNeedRepair
//
// Description:	Repairs the driver for the input device path protocol
//
// Input:		EFI_DEVICE_PATH_PROTOCOL * = Device path for the handle to which repair operation to be done
//
// Output:		VOID
//
//------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckForDeviceNeedRepair (EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    UINTN       EntryCount = 0;
    UINTN       iIndex = 0;
    EFI_STATUS  Status = EFI_SUCCESS;
    EFI_HANDLE  DevHandle = NULL;
    EFI_HANDLE  FormHiiHandle = NULL;            
    EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath = DevicePath;
	EFI_DRIVER_HEALTH_PROTOCOL	*DrvHealthInstance = NULL;
	EFI_DRIVER_HEALTH_STATUS	HealthStatus = EfiDriverHealthStatusHealthy;
    EFI_FORM_BROWSER2_PROTOCOL  *FormBrowserInterface = NULL;
    EFI_GUID    FormBrowserGuid = EFI_FORM_BROWSER2_PROTOCOL_GUID;
    EFI_GUID    DrvHealthFormsetGuid = EFI_HII_DRIVER_HEALTH_FORMSET_GUID;
    EFI_GUID    EfiDriverHealthProtocolGuid = EFI_DRIVER_HEALTH_PROTOCOL_GUID;

    Status = gBS->LocateDevicePath (
                &gEfiDevicePathProtocolGuid,
                &TempDevicePath,
                &DevHandle
                );
	if (EFI_ERROR (Status))
	{
        return Status;
    }
    if (FALSE == MatchDPHandleWithDrvHlthHndls (DevHandle))
    {
        return EFI_UNSUPPORTED;
    }
    Status = gBS->HandleProtocol (DevHandle, &EfiDriverHealthProtocolGuid, &DrvHealthInstance);
	if (EFI_ERROR (Status))
	{
		return Status;
	}
	Status = DrvHealthInstance->GetHealthStatus (DrvHealthInstance, DevHandle, NULL, &HealthStatus, NULL, &FormHiiHandle);
    if (EFI_ERROR (Status))
    {
        return Status;
    }
    Status = gBS->LocateProtocol (&FormBrowserGuid, NULL, &FormBrowserInterface);
    if (EFI_ERROR (Status))
    {
        return Status;
    }
DriverRepair:    
    if (EfiDriverHealthStatusRepairRequired == HealthStatus)
    {
        Status = DrvHealthInstance->Repair (
            DrvHealthInstance,
            DevHandle,
            NULL,
            NULL
            );
        if (EFI_ERROR (Status))
        {
            return EFI_UNSUPPORTED;
        }
    }
    if (AdvancedRepairSupported ())
    {
        Status = DrvHealthInstance->GetHealthStatus (DrvHealthInstance, DevHandle, NULL, &HealthStatus, NULL, &FormHiiHandle);
        if (!EFI_ERROR (Status))
        {
            if (EfiDriverHealthStatusConfigurationRequired == HealthStatus)
            {
                Status = FormBrowserInterface->SendForm (
                            FormBrowserInterface,
                            &FormHiiHandle,
                            1,
                            &DrvHealthFormsetGuid,
                            0,
                            NULL,
                            NULL
                            );
                if (EFI_ERROR (Status))
                {
                    return Status;
                }
                Status = DrvHealthInstance->GetHealthStatus (DrvHealthInstance, DevHandle, NULL, &HealthStatus, NULL, &FormHiiHandle);
                if (EFI_ERROR (Status))
                {
                    return Status;
                }
            }
            if ((EfiDriverHealthStatusRepairRequired == HealthStatus) || (EfiDriverHealthStatusConfigurationRequired == HealthStatus))
            {
                goto DriverRepair;
            }
            else if (EfiDriverHealthStatusRebootRequired == HealthStatus)
            {
                DriverHealthSystemReset ();
            }
            else if (EfiDriverHealthStatusReconnectRequired == HealthStatus)
            {
                Status = gBS->DisconnectController (DevHandle, NULL, NULL);
                gBS->ConnectController (DevHandle, NULL, NULL, TRUE);
            }
        }
    }
    Status = DrvHealthInstance->GetHealthStatus (DrvHealthInstance, DevHandle, NULL, &HealthStatus, NULL, &FormHiiHandle);
    if ((!(EFI_ERROR (Status))) && (EfiDriverHealthStatusHealthy == HealthStatus) )
    {
        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------------
// Procedure:	ReadPlatformLang
//
// Description:	Function to return the PlatformLang
//
// Input:	UINTN *Size 	
//
// Output:		PlatformLang String
//
//------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *ReadPlatformLang( UINTN *Size )
{
	return VarGetNvramName (L"PlatformLang", &gEfiGlobalVariableGuid, NULL, Size);
}

//<AMI_PHDR_START>
//------------------------------------------------------------------------------------------------------------------------------
//
// Name:	GetDefaultPasswordFromTokens
//
// Description:	Gets default password throug sdl tokens
//               
// Input:    	UINT32 PasswordType	
//
// Output: 	CHAR16 * Password 
//
//-------------------------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#define EMPTY_DATA ""
CHAR16 *GetDefaultPasswordFromTokens (UINT32 PasswordType)
{
#if TSE_DEFAULT_SETUP_PASSWORD_SUPPORT
	if (AMI_PASSWORD_ADMIN == PasswordType)
	{
		return CONVERT_TO_WSTRING (TSE_ADMIN_PASSWORD);
	}
	if (AMI_PASSWORD_USER == PasswordType)
	{
		return CONVERT_TO_WSTRING (TSE_USER_PASSWORD);
	}
#endif
	return NULL;
}

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
