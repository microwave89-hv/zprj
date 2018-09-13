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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/SubMenu.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/SubMenu.h $
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
// Name:		submenu.h
//
// Description:	Header file for submenu related functionalities
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _SUBMENU_H_
#define	_SUBMENU_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"

#define	SUBMENU_MEMBER_VARIABLES	\
	UINT8	LabelFGColor;			\
	UINT8	NSelLabelFGColor;		\
	UINT8  	LabelMargin;			\
    UINT8	SubMenuType;			\
	UINT8	SelFGColor;				\
	UINT8	SelBGColor;				\
	UINT8	NSelFGColor;			\
    UINT8	NSelBGColor;			\
	UINT8   Interval;

typedef struct _SUBMENU_METHODS	SUBMENU_METHODS;

typedef struct _SUBMENU_DATA
{
	SUBMENU_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	SUBMENU_MEMBER_VARIABLES

}
SUBMENU_DATA;

#define	SUBMENU_METHOD_FUNCTIONS

struct _SUBMENU_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	SUBMENU_METHOD_FUNCTIONS
};

extern SUBMENU_METHODS gSubMenu;

// Object Methods
EFI_STATUS SubMenuCreate( VOID **object );
EFI_STATUS SubMenuDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS SubMenuInitialize( VOID *object, VOID *data );
EFI_STATUS SubMenuDraw( VOID *object );
EFI_STATUS SubMenuHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS SubMenuSetCallback(  VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS SubMenuSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS SubMenuSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS SubMenuSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS SubMenuSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS SubMenuGetControlHeight(SUBMENU_DATA *submenu, VOID *frame, UINT16 *height);

UINT16 _SubMenuGetSpecialValue( SUBMENU_DATA *submenu );
BOOLEAN _SubMenuHandleSpecialOp( SUBMENU_DATA *submenu );
BOOLEAN _SubMenuAmiCallback( UINT16 value );

// find a better place for these
#define	SAVE_AND_EXIT_VALUE		1
#define	DISCARD_AND_EXIT_VALUE		2
#define	SAVE_VALUE				3
#define	DISCARD_VALUE			4
#define	RESTORE_DEFAULTS_VALUE		5
#define	SAVE_USER_DEFAULTS_VALUE	6
#define	RESTORE_USER_DEFAULTS_VALUE	7


#endif /* _SUBMENU_H_ */


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
