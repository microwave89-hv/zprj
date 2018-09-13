//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Legacy/legacy.h $
//
// $Author: Arunsb $
//
// $Revision: 2 $
//
// $Date: 10/18/12 6:06a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Legacy/legacy.h $
// 
// 2     10/18/12 6:06a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:42p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 1     3/28/11 11:52p Madhans
// [TAG]  		EIP54968
// [Category]  	Improvement
// [Description]  	To Support different style modules in TSE generically
// [Files]  		Ezport module updated. EzportPlus and Legacy Styles Modules
// added.
// 
// 1     9/16/10 6:37p Blaines
// 
// 1     9/16/10 6:32p Blaines
// 
// 6     2/19/10 8:15a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 6:12a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     8/24/09 5:15p Blaines
// Fix issue setting title and helptitle background color after clear
// screen
// 
// 3     8/18/09 6:34p Blaines
// Support additional date styles
// 
// 2     6/12/09 2:36p Blaines
// Update coding standard
// 
// 1     6/04/09 8:05p Madhans
// 
// 3     5/07/09 10:35a Madhans
// Changes after Bin module
// 
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 11:14p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     4/24/09 9:35p Blaines
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		alternate1.h
//
// Description:	Main header file for alternate1 style module.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _LEGACY_H_
#define _LEGACY_H_

#if SETUP_STYLE_LEGACY

VOID 		OverRideStyleInit( VOID );
VOID		OverRideStyleDrawPageBorder( UINT32 page );
VOID 		*OverRideStyleGetFrameInitData( UINT32 page, UINT32 frame );

#if SETUP_STYLE_FULL_SCREEN
	#define	STYLE_MAX_COLS	STYLE_FULL_MAX_COLS
	#define	STYLE_MAX_ROWS	STYLE_FULL_MAX_ROWS
#else
	#define	STYLE_MAX_COLS	STYLE_STD_MAX_COLS
	#define	STYLE_MAX_ROWS	STYLE_STD_MAX_ROWS
#endif

#define MAIN_FULL_Y     3
#define MAIN_Y          3
#define MAIN_FULL_W     98
#define MAIN_W          78


//#define	STYLE_CONTROL_LEFT_PAD	((UINT8)4)
//#define STYLE_CONTROL_RIGHT_AREA_WIDTH 28
//#define	STYLE_CONTROL_LEFT_MARGIN	((UINT8)28)
#define	STYLE_CLEAR_SCREEN_COLOR	(EFI_BACKGROUND_BLUE | EFI_WHITE)
//#define FULL_STYLE_CONTROL_LEFT_MARGIN	37
//#define FULL_STYLE_CONTROL_LEFT_PAD	2
#define FULL_STYLE_CONTROL_RIGHT_AREA_WIDTH	((UINT8)FULL_VERTICAL_MAIN_DIVIDER - FULL_STYLE_CONTROL_LEFT_MARGIN - FULL_STYLE_CONTROL_LEFT_PAD)
#define FULL_STYLE_LABEL_LEFT_MARGIN	2
#define STYLE_LABEL_LEFT_MARGIN	2
#define	EFI_BACKGROUND_WHITE  (EFI_WHITE << 4)
//#define	STYLE_CLEAR_SCREEN_COLOR	(HELPTITLE_BGCOLOR | EFI_WHITE)


// Style Overrides...
#define STYLE_OVERRIDE_INIT
#define STYLE_OVERRIDE_PAGE_BORDER
#define STYLE_OVERRIDE_FRAME_INIT_DATA
#define STYLE_OVERRIDE_CONTROL_OVERFLOW
#define STYLE_OVERRIDE_INITIALIZE_FRAME
#define STYLE_OVERRIDE_INITIALIZE_OEM_FRAME
#define STYLE_OVERRIDE_NAV_TOKEN
#define STYLE_OVERRIDE_ADD_CONTROLS
#define STYLE_OVERRIDE_FIRST_PAGE
#define	STYLE_OVERRIDE_VERSION_STRING
#define STYLE_OVERRIDE_FRAME_DRAWABLE
#define STYLE_COMPONENT_OVERRIDE
#define STYLE_OVERRIDE_HANDLE_KEY
#define STYLE_OVERRIDE_LABEL_CALLBACK
#define MENU_COMPLETE_REDRAW		1
#define SUBMENU_COMPLETE_REDRAW		2
#define STYLE_OVERRIDE_SCROLLBAR
#endif /* SETUP_STYLE_LEGACY */

#endif /* _LEGACY_H_ */
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                     Phone: (770)-246-8600                   **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
