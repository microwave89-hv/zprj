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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ListBox.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ListBox.h $
// 
// 8     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 12    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 6     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 8     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 7     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 6     10/28/09 5:38p Madhans
// 
// 5     8/26/09 4:11p Blaines
// To fix issue with BBS popup when more then 20 bootoptions are present
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
// 1     4/28/09 11:05p Madhans
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
// Name:		ListBox.h
//
// Description:	Header file for Listbox controls.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _LISTBOX_H_
#define	_LISTBOX_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "popup.h"

#define MAX_VISIBLE_SELECTIONS     (gMaxRows -10)

#define	LISTBOX_MEMBER_VARIABLES	\
    VOID	*ScreenBuf;				\
	/*EFI_HII_HANDLE*/VOID	*ListHandle;				\
	UINT16	Sel;                    \
	UINT16  FirstVisibleSel;		\
	UINT16  LastVisibleSel ;		\
	UINT16	ItemCount;				\
    	UINT16  *PtrTokens;		\
	POSTMENU_TEMPLATE  *PtrItems;	\
	BOOLEAN	 UseScrollbar;  \
	UINT16  QuitPopupLoop ;		\
	UINT16	HiddenItemCount;			

typedef struct _LISTBOX_METHODS	LISTBOX_METHODS;

typedef struct _LISTBOX_DATA
{
	LISTBOX_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	POPUP_MEMBER_VARIABLES
    LISTBOX_MEMBER_VARIABLES

}
LISTBOX_DATA;


typedef struct _LISTBOX_BSS_POPUP_DATA
{
	UINT16 TitleToken;
	UINT16	ItemCount;
	POSTMENU_TEMPLATE  *PtrItems;
	UINT16 	Help1Token;
	UINT16 	Help2Token;
	UINT16 	Help3Token;
	CONTROL_INFO *pControlData;
	UINT16	HiddenItemCount;
}
LISTBOX_BSS_POPUP_DATA;

typedef EFI_STATUS	(*LISTBOX_METHOD_INITIALIZE_BBS_POPUP)	( VOID *object, VOID *data );

// Don't Call Initialize if you call InitializeBBSPopup...
#define	LISTBOX_METHOD_FUNCTIONS 	\
	LISTBOX_METHOD_INITIALIZE_BBS_POPUP 	InitializeBBSPopup;

struct _LISTBOX_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	LISTBOX_METHOD_FUNCTIONS
};

extern LISTBOX_METHODS gListBox;

// Object Methods
EFI_STATUS ListBoxCreate( VOID **object );
EFI_STATUS ListBoxDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS ListBoxInitialize( VOID *object, VOID *data );
EFI_STATUS ListBoxDraw( VOID *object );
EFI_STATUS ListBoxHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS ListBoxSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS ListBoxSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS ListBoxSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS ListBoxSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS ListBoxSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS ListBoxGetControlHight( VOID *object,VOID *frame, UINT16 *height );

//Listbox Methods
EFI_STATUS ListBoxInitializeBBSPopup( LISTBOX_DATA *listbox, LISTBOX_BSS_POPUP_DATA *listboxBBSPopupData );

#endif /* _LISTBOX_H_ */


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
