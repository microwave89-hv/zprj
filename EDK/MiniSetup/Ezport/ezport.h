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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/ezport.h $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 10/18/12 6:05a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/ezport.h $
// 
// 6     10/18/12 6:05a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:42p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 5     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
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
// Name:		ezport.h
//
// Description:	Main header file for ezport style module.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _EZPORT_H_
#define _EZPORT_H_

#if SETUP_STYLE_EZPORT

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

#define	EFI_BACKGROUND_WHITE  (EFI_WHITE << 4)
#define	STYLE_CLEAR_SCREEN_COLOR	(HELPTITLE_BGCOLOR | EFI_WHITE)


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

#define MENU_COMPLETE_REDRAW		1
#define SUBMENU_COMPLETE_REDRAW		2
#endif /* SETUP_STYLE_EZPORT */

#endif /* _EZPORT_H_ */
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
