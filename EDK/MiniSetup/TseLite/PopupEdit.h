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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupEdit.h $
//
// $Author: Arunsb $
//
// $Revision: 9 $
//
// $Date: 10/18/12 6:02a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupEdit.h $
// 
// 9     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     4/05/12 7:25a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 7     11/20/11 8:10a Rajashakerg
// [TAG]  		EIP62763
// [Category]  	Improvement
// [Description]  	Utilize the Improvements done from mouse driver in
// AMITSE
// [Files]  		HookAnchor.h, TseCommon.h, AMITSE.sdl, CommonHelper.c,
// commonoem.c, commonoem.h, buffer.c, globals.c, HookAnchor.c,
// minisetup.h, notify.c, postmgmt.c, protocol.c, ezport.c, stylecommon.c,
// Mouse.c, Action.c, Date.c, frame.c, MessageBox.c, minisetupext.c,
// minisetupext.h, numeric.c, numeric.h, page.c, PopupEdit.c, PopupEdit.h,
// PopupPassword.c, postmgmtext.c, time.c.
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 5     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 4     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 3     8/17/09 12:27p Presannar
// Removed References to Tiano.h and replaced it with Efi.h
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
// Name:		PopupEdit.h
//
// Description:	This file contains definitions to handle Popup Edit operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _POPUPEDIT_H_
#define	_POPUPEDIT_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "popup.h"
//#include "memo.h"

#define PASSWORD_CHAR   L'*'
// popupedit constants
#define MAX_POPUPEDIT_WIDTH		(gMaxCols - 10)
#define POPUPEDIT_TYPE_STRING	0
#define POPUPEDIT_TYPE_PASSWORD	1
#define POPUPEDIT_CANCEL		1

#define	POPUPEDIT_MEMBER_VARIABLES	\
    VOID	*ScreenBuf;			\
    UINT8	PopupEditType; \
	UINT8	Justify;			\
	UINT16	DisplayLines;		\
    CHAR16  *EmptyString; \
    UINT16	MinSize;		\
	UINT16	MaxSize;		\
	UINT16	TextWidth;		\
    CHAR16  *Text;			\
	CHAR16	*TempText;		\
	CHAR16	Chr;		      /* character used to display instead of real chars */
								 /* mainly used for password entry.*/

typedef struct _POPUPEDIT_METHODS	POPUPEDIT_METHODS;

typedef struct _POPUPEDIT_DATA
{
	POPUPEDIT_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	POPUP_MEMBER_VARIABLES
	POPUPEDIT_MEMBER_VARIABLES
}
POPUPEDIT_DATA;

typedef	EFI_STATUS	(*POPUPEDIT_METHOD_SET_TEXT)		( VOID *object, CHAR16 *String);
typedef	EFI_STATUS	(*POPUPEDIT_METHOD_SET_TYPE)		( VOID *object, UINT8 Type);

#define	POPUPEDIT_METHOD_FUNCTIONS \
	POPUPEDIT_METHOD_SET_TYPE		SetType; \
	POPUPEDIT_METHOD_SET_TEXT		SetText;		

struct _POPUPEDIT_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
    POPUPEDIT_METHOD_FUNCTIONS
};

extern POPUPEDIT_METHODS gPopupEdit;


// Object Methods
EFI_STATUS PopupEditCreate( VOID **object );
EFI_STATUS PopupEditDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS PopupEditInitialize( VOID *object, VOID *data );
EFI_STATUS PopupEditDraw( VOID *object );
EFI_STATUS PopupEditHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS PopupEditSetCallback(  VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );
EFI_STATUS PopupEditSetType(VOID *object, UINT8 Type );
//EFI_STATUS PopupEditSetTitle(VOID *object, CHAR16 *String );
EFI_STATUS PopupEditSetText(VOID *object, CHAR16 *String );

// Control Methods
EFI_STATUS PopupEditSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS PopupEditSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS PopupEditSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS PopupEditSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS PopupEditGetControlHight( VOID *object,VOID *frame, UINT16 *height );

#endif /* _POPUPEDIT_H_ */


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
