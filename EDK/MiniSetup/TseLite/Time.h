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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Time.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Time.h $
// 
// 9     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     11/21/11 10:56a Premkumara
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
// 7     11/10/10 7:02p Blaines
// EIP 47037:  Add range checks to properly edit and update date/time.
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
// 1     4/28/09 11:07p Madhans
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
// Name:		Time.h
//
// Description:	Header file for code to handle Time control operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _TIME_H_
#define	_TIME_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"

typedef struct _TIME
{
	UINT8 Hour;
	UINT8 Min;
	UINT8 Sec;

}
TIME;

#define	TIME_MEMBER_VARIABLES	\
	UINT8	LabelFGColor;		\
	UINT8	NSelLabelFGColor;		\
	UINT8   LabelMargin;		\
	UINT8   Sel;				\
	UINT8	SelFGColor;			\
	UINT8	SelBGColor;			\
	UINT8	NSelFGColor;		\
	UINT16  Min;				\
    UINT16  Max;				\
	UINT8   Interval;			\
	EFI_TIME *EditTime;

typedef struct _TIME_METHODS	TIME_METHODS;

typedef struct _TIME_DATA
{
	TIME_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	TIME_MEMBER_VARIABLES

}
TIME_DATA;



struct _TIME_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
};

extern TIME_METHODS gTime;

// Object Methods
EFI_STATUS TimeCreate( VOID **object );
EFI_STATUS TimeDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS TimeInitialize( VOID *object, VOID *data );
EFI_STATUS TimeDraw( VOID *object );
EFI_STATUS TimeHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS TimeSetCallback(  VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS TimeSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS TimeSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS TimeSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS TimeSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS TimeGetControlHeight(VOID *object, VOID *frame, UINT16 *height);
VOID _TimeUpdateHelp( TIME_DATA *time );
#endif /* _TIME_H_ */



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
