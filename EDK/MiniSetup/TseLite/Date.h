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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Date.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Date.h $
// 
// 9     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     11/21/11 12:10p Premkumara
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
// 7     6/04/10 12:53p Blaines
// Add support for UEFI 2.1 date and time controls
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
// 2     5/20/09 3:42p Blaines
// Update support for date format
// 
// 1     4/28/09 11:04p Madhans
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
// Name:		Date.h
//
// Description:	Header file for Date controls
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _DATE_H_
#define	_DATE_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"

#define	DATE_MEMBER_VARIABLES	\
	UINT8	LabelFGColor;		\
	UINT8	NSelLabelFGColor;	\
	UINT8   LabelMargin;		\
	UINT8   Sel;				\
	UINT8	SelFGColor;			\
	UINT8	SelBGColor;			\
	UINT8	NSelFGColor;		\
	UINT16  Min;				\
    UINT16  Max;				\
	UINT8   Interval;

typedef struct _DATE_METHODS	DATE_METHODS;

typedef struct _DATE_DATA
{
	DATE_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	DATE_MEMBER_VARIABLES

}
DATE_DATA;


struct _DATE_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
};

extern DATE_METHODS gDate;

extern EFI_STATUS UefiGetTime(CONTROL_INFO *control, EFI_TIME *Tm);
extern EFI_STATUS UefiSetTime(CONTROL_INFO *control, EFI_TIME *Tm);

// Object Methods
EFI_STATUS DateCreate( VOID **object );
EFI_STATUS DateDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS DateInitialize( VOID *object, VOID *data );
EFI_STATUS DateDraw( VOID *object );
EFI_STATUS DateHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS DateSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS DateSetFocus( VOID *object, BOOLEAN focus);
EFI_STATUS DateSetPosition( VOID *object, UINT16 Left, UINT16 Top );
EFI_STATUS DateSetDimensions( VOID *object, UINT16 Width, UINT16 Height );
EFI_STATUS DateSetAttributes( VOID *object, UINT8 FGColor, UINT8 BGColor );
EFI_STATUS DateGetControlHeight(VOID *object, VOID *frame, UINT16 *height);

UINTN _DateGetWeekDay( EFI_TIME *tm );
VOID _DateDecrease( DATE_DATA *date );
VOID _DateIncrease( DATE_DATA *date );
VOID _DateUpdateHelp( DATE_DATA *date );

#define DATE_STYLE_MMDDYYYY		0
#define DATE_STYLE_YYYYDDMM		1
#endif /* _DATE_H_ */


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
