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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/StyleHook/StyleHook.h $
//
// $Author: Arunsb $
//
// $Revision: 3 $
//
// $Date: 10/18/12 6:20a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/StyleHook/StyleHook.h $
// 
// 3     10/18/12 6:20a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 3     10/10/12 12:40p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 2     11/09/11 10:07a Premkumara
// [TAG]  		EIP74375
// [Category]  	Improvement
// [Description]  	Control STYLE_HELP_AREA_SCROLLBAR from binary
// [Files]  		CommonHelper.c, AMITSE.sdl, StyleHook.h,
// Legacy\StyleCommon.c, Legacy.sdl, 
// EzportPlus\StyleCommon.c, EzportPlus.sdl, Ezport\StyleCommon.c,
// Ezport.sdl
// 
// 1     1/06/11 7:34p Madhans
// [TAG] - EIP 51678 
// [Category]- Enhancment
// [Severity]- Mordarate
// [Symptom]-  If OEMs override the style module parts, If new tse adds
// new style hook then 
// if the OEM has different style module, even if they don't need use the
// hook to avoid 
// compilation issue they need touch their style module to add the new
// hook.
// [RootCause] - The Original Style Hooks are part of Style module itself.
// [Solution]- To create Empty style Hook List in TSE core. This will
// allows the OEM not 
// to change their style module to update newer TSE.
// [Files] - StyleHook Module Part under TSE lite sources. StyleHook.lib
// StyleHookx64.lib tselitebin.sdl
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		StyleHook.h
//
// Description:	Style Hook List.
//
//<AMI_FHDR_END>
//**********************************************************************

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "page.h"
#include "frame.h"

EFI_STATUS StyleGetWindowColor(UINT8 *Color, INTN Level, UINT8 WindowType) ;
EFI_STATUS StyleGetMessageboxColor( UINT8 MessageBoxType, UINT8 *Color);
VOID NewStyleHook1(VOID);
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
BOOLEAN   IsHelpAreaScrollBarSupport (void);


VOID StyleSelectFirstDisplayPage( VOID );
VOID StyleAddExtraPagesData( VOID );
EFI_STATUS StyleGetSpecialColor( UINT16 ControlType, UINT8 *Color);
UINTN StyleGetDateFormat(VOID);
BOOLEAN StyleShowDay(VOID);
BOOLEAN StyleGetScrollBehavior(VOID) ;

VOID StyleFrameSetControlPositions(FRAME_DATA *frame,  UINT32 *pOtherEnd);
extern HOTKEY_TEMPLATE gHotKeyInfo[];
extern UINT32 gHotKeyCount;
EFI_STATUS StyleFrameAddTitle( FRAME_DATA *frame, UINT32 frameType,CONTROL_INFO * dummy );


//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.    **//
//**                                                             **//
//**                       All Rights Reserved.                  **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                       Phone: (770)-246-8600                 **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
