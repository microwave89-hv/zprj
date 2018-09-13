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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Memo.h $
//
// $Author: Arunsb $
//
// $Revision: 8 $
//
// $Date: 10/18/12 6:02a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Memo.h $
// 
// 8     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
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
// 2     5/18/09 12:21p Blaines
// Fix Help Frame (memo) text scroll
// 
// 1     4/28/09 11:05p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/28/09 9:40p Madhans
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
// Name:		Memo.h
//
// Description:	Header file for Memo controls.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _MEMO_H_
#define	_MEMO_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"

#define	MEMO_MEMBER_VARIABLES	\
	UINT8	Justify;			\
	UINT16	DisplayLines;		\
	CHAR16	*EmptyString;		\
	UINT16 	ScrollBarPosition;	\
	UINT8   Interval;


typedef struct _MEMO_METHODS	MEMO_METHODS;

typedef struct _MEMO_DATA
{
	MEMO_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	MEMO_MEMBER_VARIABLES

}
MEMO_DATA;

typedef	EFI_STATUS	(*MEMO_METHOD_SET_JUSTIFY)		( VOID *object, UINT8 justify );
typedef EFI_STATUS	(*MEMO_METHOD_GET_TEXT_HEIGHT)	( MEMO_DATA *memo, UINT16 *height );

#define	MEMO_METHOD_FUNCTIONS					\
	MEMO_METHOD_SET_JUSTIFY		SetJustify;		


struct _MEMO_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	MEMO_METHOD_FUNCTIONS
};

extern MEMO_METHODS gMemo;

// Object Methods
EFI_STATUS MemoCreate( VOID **object );
EFI_STATUS MemoDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS MemoInitialize( VOID *object, VOID *data );
EFI_STATUS MemoDraw( VOID *object );
EFI_STATUS MemoHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS MemoSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS MemoSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS MemoSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS MemoSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS MemoGetControlHeight( VOID *object,VOID *frame, UINT16 *height );

// Memo Methods
EFI_STATUS MemoSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS MemoSetJustify( VOID *object, UINT8 justify );
VOID MemoDrawScrollBar( MEMO_DATA *memo, UINT16 height);
VOID MemoEraseScrollBar( MEMO_DATA *memo);
#endif /* _MEMO_H_ */


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
