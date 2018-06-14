//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/BootOnly/hiistring20.c $
//
// $Author: Arunsb $
//
// $Revision: 12 $
//
// $Date: 5/08/14 9:37p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/BootOnly/hiistring20.c $
// 
// 12    5/08/14 9:37p Arunsb
// GetDefaultPasswordFromTokens function added
// 
// 11    10/18/12 11:44a Rajashakerg
// [TAG]  		EIP 97951
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Creation of TSE which does not access NVRAM during recovery
// [RootCause]  	TSE get Platform lang every time using VarGetNvramName 
// [Solution]  	Moved the code accessing PlatformLang to uefi2.1.
// [Files]  		hiistring21.c, minisetupext.c, hiistring20.c
// 
// 10    10/18/12 5:46a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 15    10/10/12 12:29p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     9/25/12 1:48p Premkumara
// [TAG]  		EIP97951
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Creation of TSE which does not access NVRAM during recovery
// [Comments]              Updated for UEFI2.0
// 
// 7     5/28/12 2:32p Premkumara
// [TAG]  		EIP85564
// [Category]  	Improvement
// [Description]  	UefiHiiTestPrintLength function needs optimization
// [Files]  		HiiString20.c
// 
// 6     6/30/11 4:09a Arunsb
// 
// 5     6/29/11 6:17a Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Hot key boot option support in TSE as per UEFI spec.
// section 3.1.6.
//                 Dummy functions added.
// [Files]         AMITSE.sdl, bootflow.c, bootflow.h, CommonHelper.c,
// commonoem.c, commonoem.h, boot.c,
//                 hiistring20.c, hiistring21.c and notify.c.
// 
// 4     6/22/11 2:21p Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Hot key boot option in TSE as per UEFI spec. section
// 3.1.6.
//                 Dummy FormHotBootKeys function added
// [Files]         AMITSE.sdl, CommonHelper.c, commonoem.c, commonoem.h,
// boot.c, hiistring20.c and hiistring21.c.
// 
// 3     2/26/10 8:46p Madhans
// For Tse 2.01.1204. Refer Changelog.log file change history
// 
// 10    2/26/10 1:29p Madhans
// Bootonly source module need AMITSEStrTokens.h
// 
// 9     2/19/10 8:07a Mallikarjunanv
// updated year in copyright message
// 
// 8     2/17/10 7:00p Madhans
// HiiString2BltBuffer() function updated to return the StringGlyphwidth
// 
// 7     2/15/10 10:04p Madhans
// 
// 6     10/28/09 5:36p Madhans
// 
// 4     8/17/09 10:49a Presannar
// Removed dependance on Minisetup.h
// Added additional includes to resolve undefined definitions and expose
// fn prototypes 
// 
// 3     6/23/09 6:56p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
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
// Intial version of TSE Lite sourc
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		hiistring20.c
//
// Description:	This file contains code to handle UEFI2.0 supported hii strings.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//#include "minisetup.h"

#ifdef TSE_FOR_APTIO_4_50
#include "token.h"
#include "efi.h"
#include "devicepath.h"
#else
#include "tokens.h"
#include "efi.h"
#endif

#ifndef EFI_PROTOCOL_DEFINITION
#define TSE_STRINGIZE(a) #a
#define EFI_PROTOCOL_DEFINITION(a) TSE_STRINGIZE(Protocol/a.h)
#endif

#include EFI_PROTOCOL_DEFINITION (FirmwareVolume)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION(Hii)

#include "HiiLib.h"
#include "Mem.h"

#define GLYPH_WIDTH 8
#define GLYPH_HEIGHT 19

/////////////////////////////////////////////////
//  VARIABLE DECLARATIONS
/////////////////////////////////////////////////

EFI_HII_PROTOCOL *gHiiProtocol = NULL;
CHAR16 	*TseSkipEscCode(CHAR16 *String);
extern 	EFI_BOOT_SERVICES *gBS;
CHAR16  	gPlatformLang [20];			//EIP97951
CHAR8 	*GlyphWidthCache = NULL;//EIP 85564 : UefiHiiTestPrintLength function needs optimization

/////////////////////////////////////////////////
//  FUNCTION DECLARATIONS
/////////////////////////////////////////////////
#if HII_VERSION <= 1
EFI_STATUS _HiiWrapperGetString( VOID* handle, UINT16 token, CHAR16 *lang, UINT16 *bufferSize, CHAR16 *buffer );
#else
EFI_STATUS _HiiWrapperGetString( VOID* handle, UINT16 token, CHAR16 *lang, UINTN *bufferSize, CHAR16 *buffer );
#endif //HII_VERSION

VOID 		*EfiLibAllocatePool(IN UINTN AllocationSize);
UINTN 	EfiStrLen(IN CHAR16 *String);
VOID 		*EfiLibAllocateZeroPool(IN UINTN AllocationSize);
UINTN 	HiiGetGlyphWidth(VOID);
UINTN 	HiiGetGlyphHeight(VOID);
/////////////////////////////////////////////////

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	Uefi20HiiInitializeProtocol
//
// Description:	function to initialize the Hii protocol
//
// Input:	void
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Uefi20HiiInitializeProtocol( VOID )
{
	EFI_STATUS Status ;

#ifdef STANDALONE_APPLICATION
#define APTIO_HII_PROTOCOL_GUID  \
	{ 0xea816d2c, 0xcee5, 0x4f02, 0x99, 0xb5, 0xd3, 0x90, 0x5c, 0xbb, 0xd0, 0x77 }
	EFI_GUID NewHii=APTIO_HII_PROTOCOL_GUID;
#endif //STANDALONE_APPLICATION

	if ( gHiiProtocol != NULL )
		return EFI_SUCCESS;

	Status = gBS->LocateProtocol( &gEfiHiiProtocolGuid, NULL, (VOID **)&gHiiProtocol );

#ifdef STANDALONE_APPLICATION
// As the standalone application build in EDK the gEfiHiiProtocolGuid different between aptio and EDK.
// Look for Hiiprotocol from Aptio also.
	if ( EFI_ERROR(Status) )
		Status = gBS->LocateProtocol( &NewHii, NULL, (VOID **)&gHiiProtocol );
#endif //STANDALONE_APPLICATION

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	Uefi20HiiGetStringLanguage
//
// Description:	function to get the language string
//
// Input:	VOID* handle, UINT16 token, CHAR16 *lang
//
// Output:	sting
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *Uefi20HiiGetStringLanguage( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token, CHAR16 *lang )
{
	EFI_STATUS Status;
	CHAR16 *buffer = NULL;
#if HII_VERSION <= 1
	UINT16 bufferSize = 0;
#else
	UINTN bufferSize = 0;
#endif //HII_VERSION
	Status = HiiInitializeProtocol();

	if ( EFI_ERROR(Status) )
		return buffer;

	Status = _HiiWrapperGetString( handle, token, lang, &bufferSize, buffer );
	if ( Status != EFI_BUFFER_TOO_SMALL )
		return buffer;

	buffer = EfiLibAllocatePool( bufferSize );
	if ( buffer == NULL )
		return buffer;

	Status = _HiiWrapperGetString( handle, token, lang, &bufferSize, buffer );
	if ( EFI_ERROR(Status) )
		MemFreePointer( (VOID **)&buffer );

	return buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	Uefi20HiiChangeStringLanguage
//
// Description:	function to change the language string
//
// Input:	VOID* handle, UINT16 token, CHAR16 *lang, CHAR16 *string
//
// Output:	token
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 Uefi20HiiChangeStringLanguage( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token, CHAR16 *lang, CHAR16 *string )
{
	EFI_STATUS Status;
	UINT16 newToken = token;

	Status = HiiInitializeProtocol();

	if ( ( EFI_ERROR(Status) ) || ( string == NULL ) )
		return INVALID_TOKEN;

	Status = gHiiProtocol->NewString( gHiiProtocol, lang, (EFI_HII_HANDLE)(UINTN)handle, &newToken, string );
	if ( EFI_ERROR(Status) )
		newToken = INVALID_TOKEN;

	return newToken;
}


#if HII_VERSION <= 1
EFI_STATUS _HiiWrapperGetString( /*EFI_HII_HANDLE*/ VOID * handle, UINT16 token, CHAR16 *lang,UINT16 *bufferSize, CHAR16 *buffer )
#else
EFI_STATUS _HiiWrapperGetString( /*EFI_HII_HANDLE*/VOID * handle, UINT16 token, CHAR16 *lang,UINTN *bufferSize, CHAR16 *buffer )
#endif //HII_VERSION
{
	if ( /*(EFI_HII_HANDLE)(UINTN)*/handle == INVALID_HANDLE )
		handle = gHiiHandle;

	return gHiiProtocol->GetString( gHiiProtocol, (EFI_HII_HANDLE)(UINTN)handle, token, TRUE, lang, bufferSize, buffer );
}


UINTN HiiTestPrintLength ( IN CHAR16   *String )
{
    EFI_STATUS    Status;
    UINT32    FirstMissing = 0;
    UINT32    GlyphBufferSize = 0;
    UINT32    BufferSize;
    if(EFI_SUCCESS != HiiInitializeProtocol())
        return GlyphBufferSize;

	if(String == NULL)
		return 0;

	String = TseSkipEscCode(String);

    while(String[FirstMissing])
    {
        BufferSize = 0;
        Status = gHiiProtocol->TestString (
                    gHiiProtocol,
                    String,
                    &FirstMissing,
                    &BufferSize);

        GlyphBufferSize += BufferSize;

        if(String[FirstMissing])
        {
            //Glyph for this character is missing calculate the
            //print length for remaining string
            FirstMissing++;
        }
    }
	gBS->FreePool( String );
    return GlyphBufferSize;
}

EFI_STATUS HiiString2BltBuffer(	CHAR16 *Message,
								EFI_UGA_PIXEL Foreground, 
								EFI_UGA_PIXEL Background, 
								OUT	UINTN *Width,
								OUT EFI_UGA_PIXEL **BltBuffer,
								OUT UINTN *BltGlyphWidth)
{
	UINT8  GlyphBuf[sizeof(EFI_WIDE_GLYPH)];
    UINT8 *GlyphArray = (UINT8 *)&GlyphBuf;
    UINT16 GlyphWidth, index;
    UINT32 GlyphStatus;
    CHAR16 *ptr;
    UINTN Length;
    EFI_STATUS Status = EFI_SUCCESS;

    GlyphStatus = 0;
    ptr = Message;
    Length = EfiStrLen(Message);
    *Width = 0;

    //Allocate enuf memory for all wide chars
    *BltBuffer = EfiLibAllocateZeroPool(sizeof (EFI_UGA_PIXEL) * Length * ((2*HiiGetGlyphWidth()) * HiiGetGlyphHeight()));
	*BltGlyphWidth = Length * 2 * HiiGetGlyphWidth();

    while(*ptr)
    {

        index=0;
        Status = gHiiProtocol->GetGlyph(
                                gHiiProtocol,
                                ptr,
                                &index,
                                &GlyphArray,
                                &GlyphWidth,
                                &GlyphStatus
                                );

        if(EFI_SUCCESS == Status)
        {
            Status = gHiiProtocol->GlyphToBlt(
                                gHiiProtocol,
                                GlyphArray,
                                Foreground,
                                Background,
                                Length*2,
                                HiiGetGlyphWidth() * ((GlyphWidth > 8) ? 2 : 1),
                                HiiGetGlyphHeight(),
                                *BltBuffer + *Width);

            *Width += ( HiiGetGlyphWidth() * ((GlyphWidth > 8) ? 2 : 1) );
        }

        ptr++;
    }

	return Status;
}

UINTN Uefi20HiiGetGlyphWidth(VOID)
{
	return GLYPH_WIDTH;
}

UINTN Uefi20HiiGetGlyphHeight(VOID)
{
	return GLYPH_HEIGHT;
}

#include EFI_PROTOCOL_DEFINITION(UnicodeCollation)

EFI_STATUS GetUnicodeCollectionProtocol(VOID **Protocol)
{
	return gBS->LocateProtocol(
                &gEfiUnicodeCollationProtocolGuid,
                NULL,
                Protocol);
}


#if TSE_USE_EDK_LIBRARY

#if APTIO_4_00
#pragma pack(push,1)
typedef struct{
    EFI_GUID SubtypeGuid;
	UINT32 NumberOfPackages;
} RESOURCE_SECTION_HEADER;
#pragma pack(pop)
#endif
EFI_STATUS ReadImageResource(
	EFI_HANDLE ImageHandle, EFI_GUID *pGuid, 
	VOID **ppData, UINTN *pDataSize
);

#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadStrings
//
// Description:	Function to load the strings from Hii.
//
// Input:	EFI_HANDLE ImageHandle, VOID * *pHiiHandle
//
// Output:	Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LoadStrings(
	EFI_HANDLE ImageHandle, VOID * *pHiiHandle
)
{
	//TODO: create a macros for GUID
	static EFI_GUID guidResourceSection= {0x97e409e6, 0x4cc1, 0x11d9, 0x81, 0xf6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	static EFI_HII_PROTOCOL *pHii = NULL;
	EFI_STATUS Status;
	EFI_LOADED_IMAGE_PROTOCOL *pImage;
	RESOURCE_SECTION_HEADER *pSection;
	UINTN SectionSize;
	EFI_HII_PACKAGES *pPackages = NULL;
	EFI_HII_PACK_HEADER *pPack;
	if (!pHii && EFI_ERROR(Status=gBS->LocateProtocol(&gEfiHiiProtocolGuid, NULL, &pHii))) return Status;
	if (EFI_ERROR(Status=gBS->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, &pImage))) return Status;
	Status=ReadImageResource(ImageHandle,&guidResourceSection,&pSection,&SectionSize);
	if (EFI_ERROR(Status)) return Status;
	pPack = (EFI_HII_PACK_HEADER*)(pSection+1);
	if (pPack->Type==EFI_HII_STRING)
	{
		pPackages = EfiLibAllocatePool(sizeof(EFI_HII_PACKAGES)+sizeof(EFI_HII_PACK_HEADER*));
		pPackages->NumberOfPackages=1;
		pPackages->GuidId = &((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(pImage->FilePath))->NameGuid;
		*(EFI_HII_PACK_HEADER**)(pPackages+1)=pPack;
		Status=pHii->NewPack(pHii, pPackages, (EFI_HII_HANDLE*)pHiiHandle);
	}
	else
	{
		Status = EFI_INVALID_PARAMETER;
	}
	MemFreePointer((VOID **)&pPackages);
	gBS->FreePool(pSection);
	return Status;	
}

#endif

#endif //#if TSE_USE_EDK_LIBRARY

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------
// Procedure:	FormHotBootKeys
//
// Description:	Dummy function for FormHotBootKeys function
//
// Input:		VOID
//
// Output:		VOID
//
//-------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FormHotBootKeys (CHAR16 *VarName)
{
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------
// Procedure:	FreeExtraKeyMemories
//
// Description:	Dummy function for FreeExtraKeyMemories function
//
// Input:		VOID
//
// Output:		VOID
//
//-------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FreeExtraKeyMemories (VOID)
{
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------
// Procedure:	RefreshBootKeysDetails
//
// Description:	Dummy function for RefreshBootKeysDetails function
//
// Input:		VOID
//
// Output:		VOID
//
//-------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RefreshBootKeysDetails (VOID)
{
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------
// Procedure:	FindandSetHotKeys
//
// Description:	Dummy function for FindandSetHotKeys function
//
// Input:		VOID
//
// Output:		VOID
//
//-------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FindandSetHotKeys (VOID)
{
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
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------------
// Procedure:	ReadPlatformLang
//
// Description:	Dummy function for PlatformLang function
//
// Input:	UINTN *Size 	
//
// Output:	NULL
//
//------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *ReadPlatformLang( UINTN 	*Size )
{
	return NULL;
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

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2011, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

