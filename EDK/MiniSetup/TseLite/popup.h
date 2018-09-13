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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/popup.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/popup.h $
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
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		popup.h
//
// Description:	Header file for code to handle popup operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _POPUP_H_
#define	_POPUP_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"

// popup constants
#define POPUP_SINGLE_BORDER	1
#define POPUP_DOUBLE_BORDER	2

#define POPUP_STYLE_NORMAL	0
#define POPUP_STYLE_BBS		1

#define	POPUP_MEMBER_VARIABLES	\
	CHAR16	*Title;				\
	UINT16  PopupBorder;		\
	BOOLEAN	Border;				\
	BOOLEAN	Shadow;				\
	UINT16	Style;				\
	CHAR16	*Help1;				\
	CHAR16	*Help2;				\
	CHAR16	*Help3;				

typedef struct _POPUP_METHODS	POPUP_METHODS;

typedef struct _POPUP_DATA
{
	POPUP_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	POPUP_MEMBER_VARIABLES
    
}
POPUP_DATA;

#define	POPUP_METHOD_FUNCTIONS

struct _POPUP_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	POPUP_METHOD_FUNCTIONS
};

extern POPUP_METHODS gPopup;

// Object Methods
EFI_STATUS PopupCreate( VOID **object );
EFI_STATUS PopupDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS PopupInitialize( VOID *object, VOID *data );
EFI_STATUS PopupDraw( VOID *object );
EFI_STATUS PopupHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS PopupSetCallback(  VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS PopupSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS PopupSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS PopupSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS PopupSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS PopupGetControlHight( VOID *object,VOID *frame, UINT16 *height );

#endif /* _POPUP_H_ */


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
