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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupSel.h $
//
// $Author: Premkumara $
//
// $Revision: 11 $
//
// $Date: 8/28/14 6:08a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupSel.h $
// 
// 11    8/28/14 6:08a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 10    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 9     11/21/11 11:10a Premkumara
// [TAG]  		EIP72610
// [Category]  	Improvement
// [Description]  	Moving TSE_MULTILINE_CONTROLS to Binary
// [Files]  		AMITSE-CommonHelper.c, AMITSE.sdl, 
// TSELITE-UefiAction.c, TseLite.sdl, Time.h, Text.c,
// SubMenu.c, ResetButton.c, PopupString.c, PopupSel.h, PopupSel.c, 
// PopupPassword.c, OrderListBox.c, Numeric.c, Label.c, Frame.c, Edit.c, 
// Date.h, Date.c, 
// LEGACY-Legacy.c,
// BOOTONLY- Minisetup.h
// 
// 8     11/13/11 1:06p Arunsb
// [TAG]  		EIP70421
// [Category]  	New Feature
// [Description]  	Support for driver order in TSE
// [Files]  		AMITSE.SDL, CommonHelper.c, setup.ini, uefisetup.ini,
// boot.c,
// minisetup.h, bbs.c, special.c, special.h, tseadvanced.c,
// addbootoption.c,
// callback.c, minisetupext.c, minisetupext.h, popupsel.c, popupsel.h,
// TseLitehelper.c, variable.c, Uefi21Wapper.c, AMIVfr.h, boot.h,
// TseElink.h, variable.h, 
// setup.h, Boot.vfr and Setup.uni
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
// Name:		PopupSel.h
//
// Description:	Header file for Popup selections
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _POPUPSEL_H_
#define	_POPUPSEL_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"
#include "ListBox.h" 

#define POPUPSEL_VALUE_BASE		UINT64
#define	POPUPSEL_MAX_WIDTH	(gControlRightAreaWidth)
typedef struct _PTRTOKENS
{
	UINT16 Option;
	POPUPSEL_VALUE_BASE Value;
}PTRTOKENS;

#define	POPUPSEL_MEMBER_VARIABLES	\
	UINT16			Title;			\
	UINT8			LabelFGColor;	\
	UINT8	NSelLabelFGColor;		\
	UINT16 			LabelMargin;	\
	UINT8			SelFGColor;		\
	UINT8			SelBGColor;		\
	UINT8			NSelFGColor;	\
	LISTBOX_DATA	*ListBoxCtrl;	\
	BOOLEAN			ListBoxEnd;		\
	/*EFI_HII_HANDLE*/VOID *			PopupSelHandle;  \
	UINT16			Sel;            \
	UINT16			ItemCount;		\
    UINT16          bInteractive;   \
    UINT16          CallBackKey;    \
    PTRTOKENS		*PtrTokens;		\
	UINT8   Interval;


typedef struct _POPUPSEL_METHODS	POPUPSEL_METHODS;

typedef struct _POPUPSEL_DATA
{
	POPUPSEL_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	POPUPSEL_MEMBER_VARIABLES

}
POPUPSEL_DATA;


struct _POPUPSEL_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS	
};

extern POPUPSEL_METHODS gPopupSel;

// Object Methods
EFI_STATUS PopupSelCreate( VOID **object );
EFI_STATUS PopupSelDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS PopupSelInitialize( VOID *object, VOID *data );
EFI_STATUS PopupSelDraw( VOID *object );
EFI_STATUS PopupSelHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS PopupSelSetCallback(  VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS PopupSelSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS PopupSelSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS PopupSelSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS PopupSelSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS PopupSelGetControlHeight( VOID *object,VOID *frame, UINT16 *height );

VOID _PopupSelCallback( POPUPSEL_DATA *container, CONTROL_DATA *popupSel, VOID *cookie );
VOID RearrangeBootDriverOrderVariable (POPUPSEL_DATA *popupSel, UINT8 bIncrease);		//EIP70421 & 70422  Support for driver order

#endif /* _POPUPSEL_H_ */


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
