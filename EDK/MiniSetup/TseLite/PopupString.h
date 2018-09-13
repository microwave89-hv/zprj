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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupString.h $
//
// $Author: Premkumara $
//
// $Revision: 9 $
//
// $Date: 8/28/14 6:08a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupString.h $
// 
// 9     8/28/14 6:08a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 8     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     3/09/11 7:23p Madhans
// [TAG]  		EIP48615  
// [Category]  	Improvement
// [Description]  	To support UEFI 2.1 RefreshOp. Based in Refersh Rate
// Controls are refershed periodically.
// [Files]  		minisetupext.h
// SubMenu.h
// SubMenu.c
// Memo.c
// Memo.h
// numeric.c
// numeric.h
// time.c
// Date.c
// PopupSel.c
// PopupSel.h
// PopupString.c
// PopupString.h
// ordlistbox.c
// minisetupext.c
// UefiAction.c
// hii.h
// Uefi20wapper.c
// hiicallback.c
// Parse.c
// tseuefihii.h
// Uefi21wapper.c
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 7     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     2/15/10 10:15p Madhans
// To avoid warnings
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
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		popupstring.h
//
// Description:	Header file for popupstring control
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _POPUP_STRING_H_
#define	_POPUP_STRING_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"
#include "action.h"
#include "Label.h"
#include "PopupEdit.h" 

#define	POPUP_STRING_MEMBER_VARIABLES	\
	CHAR16	*TempText;		\
	UINT16	TextMargin;		\
    UINT16	MinSize;		\
	UINT16	MaxSize;		\
	UINT16	TextWidth;		\
	UINT16  TextAreaWidth;	\
    UINT8	LabelFGColor;	\
	UINT8	NSelLabelFGColor;		\
	UINT8   LabelMargin;	\
	UINT8   Interval;

typedef struct _POPUP_STRING_METHODS	POPUP_STRING_METHODS;

typedef struct _POPUP_STRING_DATA
{
	POPUP_STRING_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	LABEL_MEMBER_VARIABLES
	POPUP_STRING_MEMBER_VARIABLES

}
POPUP_STRING_DATA;

#define	POPUP_STRING_METHOD_FUNCTIONS


struct _POPUP_STRING_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	POPUP_STRING_METHOD_FUNCTIONS

};

extern POPUP_STRING_METHODS gPopupString;

// Object Methods
EFI_STATUS PopupStringCreate( VOID **object );
EFI_STATUS PopupStringDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS PopupStringInitialize( VOID *object, VOID *data );
EFI_STATUS PopupStringDraw( VOID *object );
EFI_STATUS PopupStringHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS PopupStringSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS PopupStringSetFocus( VOID *object, BOOLEAN focus);
EFI_STATUS PopupStringSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS PopupStringSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS PopupStringSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS PopupStringGetControlHeight(VOID *object, VOID *frame, UINT16 *height);

EFI_STATUS _DoPopupStringEdit( POPUP_STRING_DATA *PopupString, UINT16 Title, CHAR16 **Text);

#endif /* _POPUP_STRING_H_ */



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
