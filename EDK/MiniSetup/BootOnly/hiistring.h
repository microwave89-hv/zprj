//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/hiistring.h $
//
// $Author: Premkumara $
//
// $Revision: 8 $
//
// $Date: 8/28/14 5:30a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/hiistring.h $
// 
// 8     8/28/14 5:30a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 7     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 12    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 5     2/26/10 8:53p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 8     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 7     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 6     1/09/10 5:13a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     1/04/10 10:40a Mallikarjunanv
// EIPs 27161/29095 - Added support for reserved boot option names and
// added support not to create empty boot option names
// 
// 4     8/17/09 12:19p Presannar
// Removed References to Tiano.h
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 3:34p Madhans
// Hii string support for UEFI 2.0 or UEFI 2.1
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
// 1     9/17/08 7:57p Madhans
// Boot Only driver after file split.
// 
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		hiistring.h
//
// Description:	Header file for code to handle the hii sting operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMIHIISTRING_H_	// DO NOT CHANGE THIS TO _HII_H_ !!  That is used by the HII Protocol header
#define	_AMIHIISTRING_H_

#ifdef TSE_FOR_APTIO_4_50
#include "Token.h" 
#else
#include "tokens.h"
#endif

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif


#define	INVALID_HANDLE	((VOID*)(UINTN)-1)
#define	INVALID_TOKEN	((UINT16)-1)


UINT16 HiiAddString( /*EFI_HII_HANDLE*/VOID* handle, CHAR16 *string );
UINT16 HiiChangeStringLanguage( /*EFI_HII_HANDLE*/VOID * handle, UINT16 token, CHAR16 *lang, CHAR16 *string );
CHAR16 *HiiGetStringLanguage( /*EFI_HII_HANDLE*/VOID * handle, UINT16 token, CHAR16 *lang );
CHAR16 *GetVariableNameByID( UINT32 VariableID );
CHAR16 *GetGUIDNameByID( UINT32 VariableID );

UINTN HiiFindStrPrintBoundary ( IN CHAR16   *String, IN UINTN PrintWidth );
UINTN IsCharWide( CHAR16 strWide);

CHAR16 *SkipEscCode(CHAR16 *String);
CHAR16 *GetLanguageVariableName();
UINTN HiiGetGlyphWidth(VOID);
UINTN HiiGetGlyphHeight(VOID);
EFI_STATUS GetUnicodeCollection2Protocol(VOID **Protocol);
EFI_STATUS GetUnicodeCollectionProtocol(VOID **Protocol);
EFI_STATUS InitUnicodeCollectionProtocol(VOID **Protocol);
BOOLEAN MetaiMatch(VOID *Protocol,IN CHAR16 *String,IN CHAR16 *Pattern);
INTN StringColl(VOID *Protocol,IN CHAR16 *String1,IN CHAR16 *String2);

#endif /* _AMIHIISTRING_H_ */

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
