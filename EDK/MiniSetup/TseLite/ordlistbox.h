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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ordlistbox.h $
//
// $Author: Premkumara $
//
// $Revision: 9 $
//
// $Date: 8/28/14 6:06a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ordlistbox.h $
// 
// 9     8/28/14 6:06a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 8     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     11/03/11 4:33a Premkumara
// [TAG]  		EIP70966
// [Category]  	Improvement
// [Description]  	Hii orderlist item can't update priority from value in
// Setup menu for both enable and disable TSE_MULTILINE_CONTROLS token
// [Files]  		Ordlistbox.c, ordlistbox.h, TseUefiHii.h, Uefi21Wrapper.c
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
// 1     4/28/09 11:05p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
// 8     7/09/07 10:45a Arunkumars
// - Added multi line support for ordered list
// 
// 7     6/11/07 9:02p Arunkumars
// Changed ordered list control to correct invalid value in variables only
// on refresh of a page and not during initialization.
// 
// 6     7/06/06 6:37p Arunkumars
// Include tiano.h instead of efi.h
// 
// 5     6/22/05 11:17a Franklynd
// 1- Adding knowledge of dimension to the controls
// 2- Adding check for boundaries in controls.
// 
// 4     6/17/05 5:20p Jerryp
// Code rollback to incorporate bug fixes BEFORE feature enhancements
// 
// 2     5/25/05 11:56p Franklynd
// Finalized coding on ordered list control. 
// 
// 1     5/25/05 12:26a Franklynd
// orderedlistbox controls files
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		orderlistbox.h
//
// Description:	Header file for code to handle ordered list box controls
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _ORD_LISTBOX_H_
#define	_ORD_LISTBOX_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "PopupSel.h"

//TBD// May be removed if not needed.
#ifndef TRUE
	#define TRUE 1
	#define FALSE 0
#endif

#define SCAN_PLUS  '+'
#define SCAN_MINUS '-'

#define	ORD_LISTBOX_MEMBER_VARIABLES	\
    VOID	*ScreenBuf;				\
	/*EFI_HII_HANDLE*/VOID*  ListHandle;				

/*  These variables are defined in PopupSel control
	UINT16	Sel;                    \
	UINT16	ItemCount;				\
    UINT16  *PtrTokens;*/

typedef struct _ORD_LISTBOX_METHODS	ORD_LISTBOX_METHODS;

typedef struct _ORD_LISTBOX_DATA
{
	ORD_LISTBOX_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	POPUPSEL_MEMBER_VARIABLES
    ORD_LISTBOX_MEMBER_VARIABLES

}
ORD_LISTBOX_DATA;


#define	ORD_LISTBOX_METHOD_FUNCTIONS


struct _ORD_LISTBOX_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	ORD_LISTBOX_METHOD_FUNCTIONS
};

extern ORD_LISTBOX_METHODS gOrdListBox;

// Object Methods
EFI_STATUS OrdListBoxCreate( VOID **object );
EFI_STATUS OrdListBoxDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS OrdListBoxInitialize( VOID *object, VOID *data );
EFI_STATUS OrdListBoxDraw( VOID *object );
EFI_STATUS OrdListBoxHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS OrdListBoxSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS OrdListBoxSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS OrdListBoxSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS OrdListBoxSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS OrdListBoxSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS OrdListGetControlHeight( VOID *OrdList,VOID* frame, UINT16 *height );
EFI_STATUS _OrdListBoxShift(ORD_LISTBOX_DATA *listbox, UINT8 bShiftUp);

VOID	_OrdListBoxCallback( ORD_LISTBOX_DATA *container, CONTROL_DATA *listbox, VOID *cookie );
VOID _OrdListGetSelection( ORD_LISTBOX_DATA *ordlist );//EIP-70966

#endif /* _ORD_LISTBOX_H_ */


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
