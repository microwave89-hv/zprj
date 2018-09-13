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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Menu.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Menu.h $
// 
// 7     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
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
// 5     1/09/10 6:39a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
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
// Name:		Menu.h
//
// Description:	Header file for Menu controls
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _MENU_H_
#define	_MENU_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"

typedef struct _IFR_MENU
{ // this structure is, in some way, following EFI_IFR structures
	UINT8	Opcode, Length;
}AMI_IFR_MENU;

typedef struct _MENU_ENTRY
{
	/*EFI_HII_HANDLE*/VOID* PageHandle;
	UINT16 PageID;
	UINT16 StringToken; // page title to use in menu
}AMI_MENU_ENTRY;


#define	MENU_MEMBER_VARIABLES   \
    UINT8   SelFGColor;         \
    UINT8   SelBGColor;         \
    UINT16   NumEntries;         \
    UINT16   CurrEntry;          \
    UINT8   IsSubMenu;          \
    UINT8   MenuWidth;          \
    UINT16   StartItem;          \
    UINT16   ActualPage;         \
    UINT16   PageNum;            \
    UINT16   ItemsInPage;        \
    AMI_MENU_ENTRY	*Entries;


typedef struct _MENU_METHODS	MENU_METHODS;

typedef struct _MENU_DATA
{
	MENU_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	MENU_MEMBER_VARIABLES

}
MENU_DATA;

typedef	EFI_STATUS	(*MENU_METHOD_SET_WIDTH)		( VOID *object, UINT8 Width );

#define	MENU_METHOD_FUNCTIONS \
	MENU_METHOD_SET_WIDTH		SetWidth;	

struct _MENU_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	MENU_METHOD_FUNCTIONS
};

extern MENU_METHODS gMenu;

// Object Methods
EFI_STATUS MenuCreate( VOID **object );
EFI_STATUS MenuDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS MenuInitialize( VOID *object, VOID *data );
EFI_STATUS MenuDraw( VOID *object );
EFI_STATUS MenuHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS MenuSetCallback(  VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS MenuSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS MenuSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS MenuSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS MenuSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS MenuGetControlHight( VOID *object,VOID *frame, UINT16 *height );
//menu methods
EFI_STATUS MenuSetWidth(VOID *menu,UINT8 Width);

#endif /* _MENU_H_ */


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
