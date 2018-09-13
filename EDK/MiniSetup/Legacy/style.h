//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2011, American Megatrends, Inc.    **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Legacy/style.h $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 6:06a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Legacy/style.h $
// 
// 4     10/18/12 6:06a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:42p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 3     6/29/11 12:41p Rajashakerg
// [TAG]  		EIP47086
// [Category]  	New Feature
// [Description]  	Right clicking from the Main page is not exiting from
// BIOS setup.
// 
// [Files]  		minisetup.h, Ezport\style.h,Ezport\EzportBin.sdl,
// Ezport\EzportBin.mak, Ezport\ezport.c, Ezport\EzportBin.cif,
// EzportPlus\style.h, EzportPlus\EzportPlusBin.sdl, EzportPlusBin.mak,
// EzportPlus\EzportPlusBin.cif, EzportPlus\ezportplus.c, Legacy\style.h,
// Legacy\EzportPlusBin.sdl, Legacy\LegacyBin.mak, Legacy\LegacyBin.cif,
// Legacy\legacy.c, TseLiteBin.sdl, TseLite.cif, Memo.c, frame.c,
// application.h, application.c, commonoem.h, CommonHelper.c
// 
// 2     6/23/11 3:47p Rajashakerg
// [TAG]  		EIP55762, 58925, 59971	
// [Category]  	New Feature
// [Description]  	Support REF2,REF3 and REF4 in AMITSE
// Support direct form navigation path
// Improper layout of controls in the root page when Dynamic pages are
// added using the Legacy Setup Style	
// [Files]  		setupdata.h, CommonHelper.c, AMITSE.sdl, Legacy\Legacy.c,
// Legacy\style.h, Legacy\style.h, frame.c, minisetupext.c,
// minisetupext.h, numeric.c, page.c Popupstring.c, Hii.c,
// Uefi21Wrapper.c, Parse.c Hii.c
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
// 10    3/31/10 11:40a Blaines
// Remove the hook StyleFrameAddControl
// 
// 9     3/23/10 5:10p Blaines
// Add new style module hooks
// 
// 8     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 7     2/19/10 8:15a Mallikarjunanv
// updated year in copyright message
// 
// 6     2/05/10 6:04p Madhans
// Mouse action override from Style Module.
// 
// 5     8/19/09 11:13a Blaines
// Update OEM Override prototypes
// 
// 4     8/18/09 6:35p Blaines
// Support additional date styles
// 
// 3     8/17/09 12:23p Presannar
// Removed References to Tiano.h
// 
// 2     6/12/09 2:36p Blaines
// Update coding standard
// 
// 1     6/04/09 8:05p Madhans
// 
// 4     5/20/09 3:37p Blaines
// Add functions to access date format and Scroll behavior
// 
// 3     5/18/09 12:18p Blaines
// Fix Help Frame text scroll
// Add OEM Style override prototype declarations 
// 
// 2     5/07/09 10:35a Madhans
// Changes after Bin module
// 
// 1     4/28/09 11:15p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/24/09 9:35p Blaines
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		style.h
//
// Description:	Style override prototypes.
//
//<AMI_FHDR_END>
//**********************************************************************
//#define SETUP_STYLE_FULL_SCREEN 1
//#define SETUP_GO_TO_EXIT_PAGE_ON_EXIT_KEY 0 

#ifndef _STYLE_H_
#define _STYLE_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

//#define SETUP_STYLE_LEGACY 	1
#include "legacy.h"
#include "page.h"
#include "frame.h"

extern INT16 gTabIndex ;
EFI_STATUS LegacyFrameDrawScrollBar (FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32 modVal, UINT32	sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar);
EFI_STATUS StyleGetMessageboxColor( UINT8 MessageBoxType, UINT8 *Color);
EFI_STATUS StyleControlColor(FRAME_DATA *frame, STYLECOLORS *Colors);
EFI_STATUS OverRideControlColor(FRAME_DATA *frame, STYLECOLORS *Colors);
VOID	StyleInit( VOID );
VOID	StyleExit( VOID );
VOID	StyleDrawPageBorder( UINT32 page );
UINT32	StyleGetPageFrames( UINT32 page );
UINT32		StyleFrameIndexOf( UINT32 frameType );
VOID		StyleBeforeFrame( FRAME_DATA *frame ) ;
EFI_STATUS	StyleFrameDrawable( FRAME_DATA *frame );
VOID	StyleUpdateFrameStrings(PAGE_DATA *page);
VOID *	StyleGetFrameInitData( UINT32 page, UINT32 frame );

EFI_STATUS StyleFrameHandleMouse( FRAME_DATA *frame, MOUSE_INFO MouseInfo);
EFI_STATUS StyleFrameHandleTimer( FRAME_DATA *frame, ACTION_DATA *action );
EFI_STATUS StyleFrameHandleKey( FRAME_DATA *frame, EFI_INPUT_KEY Key );
EFI_STATUS StyleHandleControlOverflow( FRAME_DATA *frame, CONTROL_DATA *control, UINT16 count );
EFI_STATUS StyleInitializeFrame( FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data );
UINT16 StyleGetNavToken( UINT32 page );
EFI_STATUS StyleAddAdditionalControls( FRAME_DATA *frame, UINT32 controlNumber, BOOLEAN focus );

//EFI_STATUS StyleMenuCallback( FRAME_DATA *frame, MENU_DATA *menu, CALLBACK_MENU *data );
VOID StyleLabelCallback( FRAME_DATA *frame, LABEL_DATA *label, VOID *cookie );

EFI_STATUS _StyleAddControl( FRAME_DATA *frame, UINT16 type, VOID *data, UINT32 *number, BOOLEAN *focus );
UINT16 StyleLanguagePage( SUBMENU_DATA *submenu );
UINT16 StyleBootManagerPage( SUBMENU_DATA *submenu );
BOOLEAN StyleHelpAreaScrollable(VOID);
VOID StylePageItemFocus(PAGE_DATA *page, FRAME_DATA *frame );
VOID StyleSubPageItemFocus(PAGE_DATA *page, FRAME_DATA *frame );
BOOLEAN StyleGetShadowSupport(VOID);
VOID StyleDrawScrollBar(FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32 modVal, 
				UINT32 sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar);

VOID StyleDrawHelpScrollBar( MEMO_DATA *memo, UINT16 height);


VOID StyleSelectFirstDisplayPage( VOID );
VOID StyleAddExtraPagesData( VOID );
EFI_STATUS StyleGetSpecialColor( UINT16 ControlType, UINT8 *Color);
UINTN StyleGetDateFormat(VOID);
BOOLEAN StyleShowDay(VOID);
BOOLEAN StyleGetScrollBehavior(VOID) ;

VOID StyleFrameSetControlPositions(FRAME_DATA *frame,  UINT32 *pOtherEnd);
extern HOTKEY_TEMPLATE gHotKeyInfo[];
extern HOTCLICK_TEMPLATE gHotClickInfo[];//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
extern UINT32 gHotKeyCount;
extern UINT32 gHotClickCount;//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
//extern UINT8 gLabelLeftMargin ;
//extern UINT8 gControlLeftMargin ;
//extern FRAME_INFO _gStyleStandardSubFrames[] ;
extern UINT32 gSubFrameCount ;
extern EFI_STATUS FrameDrawScrollBar (FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32 modVal, UINT32 sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar);
EFI_STATUS StyleFrameAddTitle( FRAME_DATA *frame, UINT32 frameType,CONTROL_INFO * dummy );


//Common Overrides
VOID 		OverRideStyleLabelCallback(FRAME_DATA *frame, LABEL_DATA *label, VOID *cookie );
EFI_STATUS	OverRideStyleFrameHandleKey(FRAME_DATA *frame, EFI_INPUT_KEY Key);
EFI_STATUS 	OverRideStyleHandleControlOverflow( FRAME_DATA *frame, CONTROL_DATA *control, UINT16 count );
EFI_STATUS 	OverRideStyleInitializeFrame( FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data );
UINT16 		OverRideStyleGetNavToken( UINT32 page );
EFI_STATUS 	OverRideStyleAddAdditionalControls( FRAME_DATA *frame, UINT32 controlNumber, BOOLEAN focus );
VOID 		OverRideStyleSelectFirstDisplayPage( VOID );
VOID 		OverRideStyleUpdateVersionString( VOID );
EFI_STATUS 	OverRideStyleFrameDrawable( FRAME_DATA *frame );
VOID 		OverRideComponent(VOID);

//Oem Overrides
UINTN		OEMStyleGetDateFormat(VOID);
EFI_STATUS 	OEMGetSpecialColor(UINT16 ControlType, UINT8 *Color);
VOID 		OEMStyleBeforeFrame( FRAME_DATA *frame );
VOID 		OEMStyleUpdateFrameStrings( PAGE_DATA *page );
EFI_STATUS 	OEMStyleFrameDrawable( FRAME_DATA *frame );
VOID		OEMStyleInit( VOID );
VOID		OEMStyleExit( VOID );
VOID 		OEMStyleDrawPageBorder( UINT32 page );
VOID 		OEMDrawScrollBar(FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32 modVal, UINT32 sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar);
VOID 		OEMDrawHelpScrollBar( MEMO_DATA *memo, UINT16 height);
VOID 		*OEMStyleGetFrameInitData( UINT32 page, UINT32 frame );
EFI_STATUS 	OEMStyleFrameHandleKey( FRAME_DATA *frame, EFI_INPUT_KEY Key );
EFI_STATUS 	OEMStyleHandleControlOverflow( FRAME_DATA *frame, CONTROL_DATA *control, UINT16 count );
EFI_STATUS 	OEMStyleInitializeFrame( FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data );
UINT16 		OEMStyleGetNavToken( UINT32 page );
EFI_STATUS 	OEMStyleAddAdditionalControls( FRAME_DATA *frame, UINT32 controlNumber, BOOLEAN focus );
UINT16 		OEMStyleLanguagePage( SUBMENU_DATA *submenu );
UINT16 		OEMStyleBootManagerPage( SUBMENU_DATA *submenu );
VOID 		OEMStyleLabelCallback( FRAME_DATA *frame, LABEL_DATA *label, VOID *cookie );
VOID 		OEMStyleSelectFirstDisplayPage( VOID );
VOID 		OEMStyleAddExtraPagesData(VOID);
UINTN 		OEMStyleGetTextMode( UINTN Rows, UINTN Cols );
VOID 		OEMStyleUpdateVersionString( VOID );
VOID 		OEMStyleFrameSetControlPositions(FRAME_DATA *frame, UINT32 *pOtherEnd);
VOID 		OEMOverRideComponent(VOID);
VOID 		OEMStylePageItemFocus(PAGE_DATA *page, FRAME_DATA *frame );
VOID 		OEMStyleSubPageItemFocus(PAGE_DATA *page, FRAME_DATA *frame );

#endif /* _STYLE_H_ */
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2011, American Megatrends, Inc.    **//
//**                                                             **//
//**                       All Rights Reserved.                  **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                       Phone: (770)-246-8600                 **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
