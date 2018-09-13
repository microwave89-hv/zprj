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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Text.h $
//
// $Author: Arunsb $
//
// $Revision: 7 $
//
// $Date: 10/18/12 6:02a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Text.h $
// 
// 7     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 6     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 5     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 4     8/17/09 12:27p Presannar
// Removed References to Tiano.h and replaced it with Efi.h
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:06p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		text.h
//
// Description:	Header file for code to handle text operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _TEXT_H_
#define	_TEXT_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"

#define	TEXT_MEMBER_VARIABLES	\
	CHAR16	*LabelText;			\
	UINT16	LabelMargin;		\
	CHAR16	*Text;				\
	UINT8	Interval;

typedef struct _TEXT_METHODS	TEXT_METHODS;

typedef struct _TEXT_DATA
{
	TEXT_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	TEXT_MEMBER_VARIABLES

}
TEXT_DATA;

typedef EFI_STATUS	(*TEXT_METHOD_SET_TEXT) ( VOID *object, CHAR16 *label, CHAR16 *value );
#define	TEXT_METHOD_FUNCTIONS                   \
	TEXT_METHOD_SET_TEXT        SetText;

struct _TEXT_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	TEXT_METHOD_FUNCTIONS
};

extern TEXT_METHODS gText;

// Object Methods
EFI_STATUS TextCreate( VOID **object );
EFI_STATUS TextDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS TextInitialize( VOID *object, VOID *data );
EFI_STATUS TextDraw( VOID *object );
EFI_STATUS TextHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS TextSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS TextSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS TextSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS TextSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS TextSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);

// Text Methods
EFI_STATUS TextSetText( VOID *object, CHAR16 *label, CHAR16 *value );
EFI_STATUS TextGetControlHeight( VOID *text,VOID *frame, UINT16 *height );

#endif /* _TEXT_H_ */


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
