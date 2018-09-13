//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2013, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                       Phone: (770)-246-8600                 **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/stylecommon.c $
//
// $Author: Rajashakerg $
//
// $Revision: 20 $
//
// $Date: 3/16/13 2:21a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/stylecommon.c $
// 
// 20    3/16/13 2:21a Rajashakerg
// [TAG]  		EIP111479 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BIOS dialog box is crashed with special
// monitor(160,53,1280*1024)
// [RootCause]  	DesiredTextMode was not set properly.
// [Solution]  	Provided proper mode number while setting text mode.
// [Files]  		postmgmtext.c, Ezport\stylecommon.c,
// EzportPlus\stylecommon.c, Legacy\stylecommon.c
// 
// 19    2/10/13 11:53p Rajashakerg
// [TAG]  		EIP104521
// [Category]  	Improvement
// [Description]  	Customer needs AMITSE modification to popup boxes so
// highlighted choices can be seen via VT100 console redirection
// [Files]  		AMITSE.sdl, CommonHelper.c, Ezport\stylecommon.c,
// EzportPlus\stylecommon.c, Legacy\stylecommon.c
// 
// 18    10/18/12 6:05a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 14    10/10/12 12:42p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 16    9/17/12 6:24a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 14    8/29/12 4:26p Arunsb
// [TAG]  			EIP94702
// [Description]  	Support for Native Resolution in POST/BOOT
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c, boot.c, logo.c,
// notify.c, postmgmt.c, tselite\minisetupext.c, ezport/stylecommon.c,
// ezportplus/stylecommon.c andlegacy/stylecommon.c
// 
// 13    4/03/12 3:02a Premkumara
// [TAG]  		EIP84150
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	All the timers for mouse drivers before exiting from setup
// is not  stopped
// [RootCause]  	MouseDestroy() is not called StopPointingDevice()
// function to stop Mouse device
// [Solution]  	StopPointingDevice() function is called in MouseDestroy()
// function
// [Files]  		Mouse.c, Protocol.c, Ezport/StyleCommon.c,
// EzportPlus/StyleCommon.c, Legacy/StyleCommon.c, Minisetupext.c
// 
// 12    11/28/11 1:23a Premkumara
// [TAG]  		EIP75384 
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		UefiWapper.c, Hii.c, Expression.c, CtrlCond.c, PopupSel.c,
// Minisetupext.c, Menu.c,
// Date.c, Ezport\Stylecommon.c, EzportPlus\StyleCommon.c,
// Legacy\StyleCommon.c
// 
// 11    11/20/11 7:28a Rajashakerg
// [TAG]  		EIP62763
// [Category]  	Improvement
// [Description]  	Utilize the Improvements done from mouse driver in
// AMITSE
// [Files]  		HookAnchor.h, TseCommon.h, AMITSE.sdl, CommonHelper.c,
// commonoem.c, commonoem.h, buffer.c, globals.c, HookAnchor.c,
// minisetup.h, notify.c, postmgmt.c, protocol.c, ezport.c, stylecommon.c,
// Mouse.c, Action.c, Date.c, frame.c, MessageBox.c, minisetupext.c,
// minisetupext.h, numeric.c, numeric.h, page.c, PopupEdit.c, PopupEdit.h,
// PopupPassword.c, postmgmtext.c, time.c.
// 
// 10    11/14/11 6:55p Blaines
// [TAG] - EIP 75486 
// [Category]- Function Request
// [Synopsis]- Support grayout condition for readonly controls.
// [Description] - Display readonly controls as grayout, non-selectable.
// [Files]
// AMITSE.sdl, CommonHelper.c, Minisetupext.h, stylecommon.c, Legacy.c,
// date.c, edit.c, label.c, memo.c, menu.c,, numeric.c, ordlistbox.c,
// PopupPassword.c, 
// PopupSel.c, PopupString.c, ResetButton.c, SubMenu.c, Text.c, Time.c,
// UefiAction.c, ctrlcond.c,   
// 
// 9     11/09/11 10:02a Premkumara
// [TAG]  		EIP74375
// [Category]  	Improvement
// [Description]  	Control STYLE_HELP_AREA_SCROLLBAR from binary
// [Files]  		CommonHelper.c, AMITSE.sdl, StyleHook.h,
// Legacy\StyleCommon.c, Legacy.sdl, 
// EzportPlus\StyleCommon.c, EzportPlus.sdl, Ezport\StyleCommon.c,
// Ezport.sdl
// 
// 8     1/06/11 7:54p Blaines
// [TAG] - EIP 51678 
// [Category]- Enhancment
// [Severity]- Mordarate
// [Symptom]- Style function should allow OEM to override default
// implementation.
// 
// [Rootcause] - Style function does not provide override macro. 
// [Solution] - Add Macro Overrides to the following functions:
// 
// StyleGetClearScreenColor,
// StyleGetPageLinkColor, 
// StyleGetScrollBarUpArrowColor ,
// StyleGetScrollBarDownArrowColor.
// 
// [Files] - stylecommon.c 
// 
// 7     11/18/10 6:38p Blaines
// [TAG] - EIP 45374
// [Category]- Function Request
// [Synopsis]- Need method to configure Post Menu programmatically, Items
// requested 
// - Exit Keys
// - Font Colors
// - Background Colors.
// [Solution]
//  - Create hook to set window color, 
//  - Add AMI_POSTMENU_ATTRIB_EXIT_KEY  attribute to POSTMENU_TEMPLATE to
// configure exit keys.
// [Files] - stylecommon.c, style.h, listbox.c, minisetupext.c,
// AMIPostMgr.h
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 8     2/19/10 8:15a Mallikarjunanv
// updated year in copyright message
// 
// 7     2/05/10 6:04p Madhans
// Mouse action override from Style Module.
// 
// 6     11/09/09 4:44a Mallikarjunanv
// Eip-30111 : fixed the issue to update the help if
// STYLE_PAGE_FIRSTITEM_FOCUS token enabled.
// 
// 5     8/18/09 6:35p Blaines
// Support additional date styles
// 
// 4     8/13/09 1:24p Blaines
// EIP #24980 Fix to properly display right area text;
// 
// 
// 3     6/23/09 6:54p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
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
// 4     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/24/09 9:35p Blaines
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		stylecommon.c
//
// Description:	Contains generic or default style functions.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "minisetup.h"

#if SETUP_STYLE_EZPORT


VOID _StyleControlSubmenu( CONTROL_INFO *control, UINT16 pageID, VOID *ref );
VOID UpdatePageFocusedItemHelp(PAGE_DATA *page);
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    StyleControlColor
//
// Description: 	Adds controls to the frame 
//
// Input:		FRAME_DATA *frame  - Pointer to the frame data
//			STYLECOLORS Colors - Color scheme 
//
// Output:		EFI_STATUS Status - EFI_SUCCESS if successful, else
//										EFI_UNSUPPORTED
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleControlColor(FRAME_DATA *frame, STYLECOLORS *Colors)
{
	//Note: Blaines 01/12/09
	//The goal here is to allow controls to match the BGColor of their frame.
	//Normally this is handled in StyleInitializeFrame(), before controls are added to the frame.
	//But this function is called dynamically during runtime (after pages/frames/controls are styled)
	//Since controls derive their colors from [STYLECOLORS Colors], 
	//we'll temporarly modify it before controls are added to this frame, then restore it.

	EFI_STATUS Status = EFI_SUCCESS;	

	#ifdef STYLE_OEM_CONTROL_COLOR				
		Status = OEMControlColor(frame, Colors);			
	#else
		#ifdef STYLE_CONTROL_COLOR	
			Status = OverRideControlColor(frame, Colors);	
		#else
			//Temporarly Match the BGColor of the frame
			Colors->BGColor		=	frame->FrameData.BGColor ;	
			Colors->SecBGColor	=	frame->FrameData.BGColor ;
			Colors->SelBGColor	=	frame->FrameData.BGColor ;
			Colors->NSelBGColor	=	frame->FrameData.BGColor ;
			Colors->LabelBGColor	=	frame->FrameData.BGColor ;
			Colors->PopupBGColor 	=	frame->FrameData.BGColor ;
			
		#endif	

	#endif	
	
	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetSpecialColor	
//
// Description:	Function to get control special color 
//
// Input:		UINT16 ControlType, UINT8 *Color
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleGetSpecialColor( UINT16 ControlType, UINT8 *Color)
{
	EFI_STATUS Status = EFI_SUCCESS;;	

	#ifdef STYLE_OEM_CONTROL_COLOR				
		Status = OEMGetSpecialColor(ControlType, Color);	
	#else
		
		
	switch ( ControlType )
	{
		case CONTROL_TYPE_MEMO:
			if (Color !=NULL) *Color = MEMO_COLOR ;	
			break;

		case CONTROL_TYPE_TEXT:
			if (Color !=NULL) *Color = TEXT_COLOR ;	
			break;
		
		default:
			Status = EFI_UNSUPPORTED;;
		break;
	}
	#endif		

	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetWindowLevel	
//
// Description:	Function to get window level 
//
// Input:		UINT16	PageID
//
// Output:		INTN Level
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN GetWindowLevel( UINT16	PageID)
{
	INTN zIndex = 0 ;
	UINT16 TempID = PageID ;
	
	while(gApp->PageList[TempID]->PageData.PageParentID)
	{
		TempID = gApp->PageList[TempID]->PageData.PageParentID ;
		zIndex += 1 ;
	} 
	
	return zIndex ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetWindowColor	
//
// Description:	Function to get window color 
//
// Input:		UINT8 *Color	- Window Color  
//				INTN Level 		- Window Level
//				UINT8 Type		- Window Type (0->Setup, 1->PostMenu)
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleGetWindowColor(UINT8 *Color, INTN Level, UINT8 WindowType)
{
	return EFI_SUCCESS ;

}

VOID GetMessageboxColorHook(UINT8 **Color);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetMessageboxColor	
//
// Description:	Function to get control Messagebox color 
//
// Input:		UINT16 ControlType, UINT8 *Color
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleGetMessageboxColor( UINT8 MessageBoxType, UINT8 *Color)
{
	EFI_STATUS Status = EFI_SUCCESS;;	

	if(Color == NULL)
		return Status ;
	
	
	switch ( MessageBoxType )
	{
		case MSGBOX_EX_CATAGORY_HELP:
			*Color = EFI_BACKGROUND_LIGHTGRAY | EFI_BLUE ;	
			break;

		case MSGBOX_EX_CATAGORY_QUERY:
			 *Color = EFI_BACKGROUND_BLUE | EFI_WHITE ;	
			 break;

		case MSGBOX_EX_CATAGORY_SUCCESS:
			 *Color = EFI_BACKGROUND_GREEN | EFI_WHITE ;	
			 break;

		case MSGBOX_EX_CATAGORY_WARNING:
			 *Color = EFI_BACKGROUND_RED | EFI_WHITE ;	
			 break;

		case MSGBOX_EX_CATAGORY_ERROR:
			 *Color = EFI_BACKGROUND_RED | EFI_WHITE ;	
			 break;

		case MSGBOX_EX_CATAGORY_PROGRESS:
			 *Color = EFI_BACKGROUND_LIGHTGRAY | EFI_WHITE ;	
			 break;

		case MSGBOX_EX_CATAGORY_HALT:
			 *Color = EFI_BACKGROUND_LIGHTGRAY | EFI_WHITE ;	
			 break;
		
		case MSGBOX_EX_CATAGORY_NORMAL:
		
		default:
			*Color = EFI_BACKGROUND_BLUE | EFI_WHITE ;
			
			break;
	}
	
	GetMessageboxColorHook(&Color);

	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleBeforeFrame	
//
// Description:	Function to alter frame styling before frame is drawn
//
// Input:		FRAME_DATA *frame
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleBeforeFrame( FRAME_DATA *frame )
{
	#ifdef STYLE_OEM_BEFORE_FRAME				
		OEMStyleBeforeFrame(frame);			
	#else
		#ifdef STYLE_OVERRIDE_BEFORE_FRAME		// from Ezport.h
			OverRideStyleBeforeFrame(frame );	// From ezport.c
		#endif
		
	#endif	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleUpdateFrameStrings	
//
// Description:	Function to update frame strings
//
// Input:		PAGE_DATA *page
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleUpdateFrameStrings( PAGE_DATA *page )
{
	#ifdef STYLE_OEM_FRAME_TOKEN				// SDL
		OEMStyleUpdateFrameStrings(page);		// OEM
	#else
		#ifdef STYLE_OVERRIDE_FRAME_TOKEN		// from Ezport.h
			OverRideStyleUpdateFrameStrings(page );	// From ezport.c
		#endif
	#endif		
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameDrawable	
//
// Description:	Function to determine if frame is drawable
//
// Input:		FRAME_DATA *frame
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleFrameDrawable( FRAME_DATA *frame )
{
	EFI_STATUS Status = EFI_SUCCESS;

	#ifdef STYLE_OEM_FRAME_DRAWABLE					// SDL
		Status = OEMStyleFrameDrawable(frame);			// OEM
	#else
		#ifdef STYLE_OVERRIDE_FRAME_DRAWABLE			// from Ezport.h
			Status = OverRideStyleFrameDrawable(frame );	// From ezport.c
		#endif
	#endif		

	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleInit	
//
// Description:	Function to initialize style  
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID	StyleInit( VOID )
{
	SetDesiredTextMode();
	OverRideStyleInit();		// From ezport.c	
	
#ifdef STYLE_OEM_INIT			// SDL
	OEMStyleInit();			// OEM
#endif	
    MouseInit();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleExit	
//
// Description:	Function to do style initialization on exit
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID	StyleExit( VOID )
{
	#ifdef STYLE_OEM_STYLE_EXIT			// SDL
		OEMStyleExit();				// OEM
	#else
		#ifdef STYLE_OVERRIDE_EXIT		// from Ezport.h
		OverRideStyleExit();			// From ezport.c
		#endif
	#endif
	MouseDestroy(); //EIP-84150 
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleDrawPageBorder	
//
// Description:	Function to draw the page border
//
// Input:		UINT32 page number
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleDrawPageBorder( UINT32 page )
{
	#ifdef STYLE_OEM_PAGE_BORDER				// SDL
		OEMStyleDrawPageBorder(page);			// OEM
	#else
		#ifdef STYLE_OVERRIDE_PAGE_BORDER		// from Ezport.h
			OverRideStyleDrawPageBorder(page);	// From ezport.c
		#else
			ClearScreen( EFI_BACKGROUND_BLUE | EFI_WHITE );
		#endif
	#endif	
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleDrawScrollBar	
//
// Description:	Function to draw the frame scrollbar
//
// Input:		FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32 modVal, UINT32 sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleDrawScrollBar(FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32 modVal, 
				UINT32 sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar)
{
	#ifdef STYLE_OEM_SCROLLBAR					
		OEMDrawScrollBar(frame, FirstLine, LastLine, modVal, sizeOfBar, numOfBlocks, bEraseScrollBar);			
	#else
		#ifdef STYLE_OVERRIDE_SCROLLBAR			
			OverRideDrawScrollBar(frame, FirstLine, LastLine, modVal, sizeOfBar, numOfBlocks, bEraseScrollBar);
		#else
			FrameDrawScrollBar(frame, FirstLine, LastLine, modVal, sizeOfBar, numOfBlocks, bEraseScrollBar);
		#endif
	#endif	
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleDrawHelpScrollBar	
//
// Description:	Function to draw the help frame scrollbar
//
// Input:		MEMO_DATA *memo, UINT16 height
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleDrawHelpScrollBar( MEMO_DATA *memo, UINT16 height)
{
	#ifdef STYLE_OEM_DRAW_HELP_SCROLLBAR					
		OEMDrawHelpScrollBar(memo, height);			
	#else
		#ifdef STYLE_OVERRIDE_HELP_SCROLLBAR			
			OverRideDrawHelpScrollBar(memo, height);
		#else
			if(IsHelpAreaScrollBarSupport())
				MemoDrawScrollBar(memo, height); 
		#endif
	#endif	
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetFrameInitData	
//
// Description:	Function to get frame initialization data
//
// Input:		UINT32 page number, UINT32 frame number
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *StyleGetFrameInitData( UINT32 page, UINT32 frame )
{
	#ifdef STYLE_OEM_FRAME_INIT_DATA					
		return OEMStyleGetFrameInitData(page, frame);		
	#else
		#ifdef STYLE_OVERRIDE_FRAME_INIT_DATA				// from Ezport.h
		 	return	OverRideStyleGetFrameInitData(page, frame);	// From ezport.c
		#else
			return NULL;
		#endif
	#endif	
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameHandleKey	
//
// Description:	Function to handle frame action keys
//
// Input:		FRAME_DATA *frame, EFI_INPUT_KEY Key
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleFrameHandleKey( FRAME_DATA *frame, EFI_INPUT_KEY Key )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;;

	#ifdef STYLE_OEM_HANDLE_KEY				// SDL
		Status = OEMStyleFrameHandleKey(frame, Key);			// OEM
	#else
		#ifdef STYLE_OVERRIDE_HANDLE_KEY		// from Ezport.h
		 	Status = OverRideStyleFrameHandleKey(frame, Key);	// From ezport.c
		#endif
	#endif		
	
	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameHandleMouse
//
// Description:	Function to handle frame using mouse
//
// Input:		FRAME_DATA *frame,
//				MOUSE_INFO MouseInfo 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleFrameHandleMouse( FRAME_DATA *frame, MOUSE_INFO MouseInfo)
{
    EFI_STATUS Status = EFI_UNSUPPORTED;;

	#ifdef STYLE_OEM_HANDLE_MOUSE				
		Status = OEMStyleFrameHandleMouse(frame, MouseInfo);			
	#else
		#ifdef STYLE_OVERRIDE_HANDLE_MOUSE		
		 	Status = OverRideStyleFrameHandleMouse(frame, MouseInfo);	
		#endif
	#endif		
	
	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameHandleTimer	
//
// Description:	Function to handle frame timer action
//
// Input:		FRAME_DATA *frame, ACTION_DATA *action
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleFrameHandleTimer( FRAME_DATA *frame, ACTION_DATA *action )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;;

	#ifdef STYLE_OEM_HANDLE_TIMER				
		Status = OEMStyleFrameHandleTimer(frame, action);			
	#else
		#ifdef STYLE_OVERRIDE_HANDLE_TIMER		
		 	Status = OverRideStyleFrameHandleTimer(frame, action);	
		#endif
	#endif		
	
	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleHandleControlOverflow	
//
// Description:	Function to handle control overflow
//
// Input:		FRAME_DATA *frame, CONTROL_DATA *control, UINT16 count 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleHandleControlOverflow( FRAME_DATA *frame, CONTROL_DATA *control, UINT16 count )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	#ifdef STYLE_OEM_CONTROL_OVERFLOW						
		Status = OEMStyleHandleControlOverflow(frame, control, count );
	#else
		#ifdef STYLE_OVERRIDE_CONTROL_OVERFLOW
		 	Status = OverRideStyleHandleControlOverflow(frame, control, count );
		#endif
	#endif		
	
	return Status ;	

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleInitializeFrame	
//
// Description:	Function to Initialize frame
//
// Input:		FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleInitializeFrame( FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data )
{
	EFI_STATUS Status = EFI_SUCCESS;;

	#ifdef STYLE_OEM_INITIALIZE_FRAME						
		Status = OEMStyleInitializeFrame(frame, frameType, data );
	#else
		#ifdef STYLE_OVERRIDE_INITIALIZE_FRAME
		 	Status = OverRideStyleInitializeFrame(frame, frameType, data);	//style.c
		#endif
	#endif		
	
	return Status ;	
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetNavToken	
//
// Description:	Function to get navigation token 
//
// Input:		UINT32 page
//
// Output:		UINT16 token number
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 StyleGetNavToken( UINT32 page )
{
	UINT16 i=0 ;	

	#ifdef STYLE_OEM_NAV_TOKEN						
		i = OEMStyleGetNavToken(page );
	#else
		#ifdef STYLE_OVERRIDE_NAV_TOKEN
		 	i = OverRideStyleGetNavToken(page);
		#endif
	#endif		
	
	return i ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleAddAdditionalControls	
//
// Description:	Function to add additinal controls
//
// Input:		FRAME_DATA *frame, UINT32 controlNumber, BOOLEAN focus
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleAddAdditionalControls( FRAME_DATA *frame, UINT32 controlNumber, BOOLEAN focus )
{
	EFI_STATUS Status = EFI_SUCCESS;
	
	#ifdef STYLE_OEM_ADD_CONTROLS
		Status = OEMStyleAddAdditionalControls(frame, controlNumber, focus );
	#else
		#ifdef STYLE_OVERRIDE_ADD_CONTROLS
		 	Status = OverRideStyleAddAdditionalControls(frame, controlNumber, focus);
		#endif
	#endif		
	
	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleLanguagePage	
//
// Description:	Function to set Language page
//
// Input:		SUBMENU_DATA *submenu
//
// Output:		UINT16 page number
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 StyleLanguagePage( SUBMENU_DATA *submenu )
{
	UINT16 i = 0 ;
	
	#ifdef STYLE_OEM_LANGUAGE_PAGE						
		i = OEMStyleLanguagePage(submenu );
	#else
		#ifdef STYLE_OVERRIDE_LANGUAGE_PAGE
		 	i = OverRideStyleLanguagePage(submenu);
		#endif
	#endif			

	return i ;
}



static UINT16 _gBootManagerPageID = 0;
/*static*/ UINT16 _gHDOrderPageID = 0;
/*static*/ UINT16 _gCDOrderPageID = 0;
/*static*/ UINT16 _gFDOrderPageID = 0;
/*static*/ UINT16 _gNetOrderPageID = 0;
/*static*/ UINT16 _gBevOrderPageID = 0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleBootManagerPage	
//
// Description:	Function to set boot manager page
//
// Input:		SUBMENU_DATA *submenu
//
// Output:		UINT16 page number
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 StyleBootManagerPage( SUBMENU_DATA *submenu )
{
	UINT16 i = 0 ;
	
	#ifdef STYLE_OEM_BM_PAGE						
		i = OEMStyleBootManagerPage(submenu );
	#else
		#ifdef STYLE_OVERRIDE_BM_PAGE
		 	i = OverRideStyleBootManagerPage(submenu);
		#endif
	#endif			
	
	return i ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleLabelCallback	
//
// Description:	Function to set label callback
//
// Input:		FRAME_DATA *frame, LABEL_DATA *label, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleLabelCallback( FRAME_DATA *frame, LABEL_DATA *label, VOID *cookie )
{
	#ifdef STYLE_OEM_LABEL_CALLBACK						
		OEMStyleLabelCallback(frame, label, cookie );
	#else
		#ifdef STYLE_OVERRIDE_LABEL_CALLBACK
		 	OverRideStyleLabelCallback(frame, label, cookie );
		#endif
	#endif		
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleSelectFirstDisplayPage	
//
// Description:	Function to set the first display page
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleSelectFirstDisplayPage( VOID )
{
	#ifdef STYLE_OEM_FIRST_PAGE						
		OEMStyleSelectFirstDisplayPage();
	#else
		#ifdef STYLE_OVERRIDE_FIRST_PAGE
		 	OverRideStyleSelectFirstDisplayPage();
		#endif
	#endif	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleAddExtraPagesData	
//
// Description:	Function to add extra pages
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleAddExtraPagesData(VOID)
{
	#ifdef STYLE_OEM_ADD_EXTRA_PAGES
		OEMStyleAddExtraPagesData();
	#else
		#ifdef STYLE_OVERRIDE_ADD_EXTRA_PAGES
			OverRideStyleAddExtraPagesData();
		#endif
	#endif	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetTextMode	
//
// Description:	Function to get text mode
//
// Input:		UINTN Rows, UINTN Cols 
//
// Output:		UNNTN mode
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN StyleGetTextMode( UINTN Rows, UINTN Cols )
{
	EFI_STATUS Status;
	INT32 i;
	UINTN ModeRows, ModeCols;

	#ifdef STYLE_OEM_GET_TEXT_MODE
		i = OEMStyleGetTextMode( Rows, Cols );
	#else
		#ifdef STYLE_OVERRIDE_GET_TEXT_MODE
		    i =	OverRideStyleGetTextMode( Rows, Cols);
		#else
		// Default Implementation
		for ( i = 0; i < gST->ConOut->Mode->MaxMode; i++ )
		{
			Status = gST->ConOut->QueryMode( gST->ConOut, i, &ModeCols, &ModeRows );
			if ( EFI_ERROR( Status ) )
				continue;

			if ( ( Cols == ModeCols ) && ( Rows == ModeRows ) )
				return i;
		}

		// return MaxMode if the mode wasn't found
		#endif
	#endif	
	
	return i;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleUpdateVersionString	
//
// Description:	Function to set the version string 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleUpdateVersionString( VOID )
{
	#ifdef STYLE_OEM_VERSION_STRING
		OEMStyleUpdateVersionString();
	#else
		#ifdef STYLE_OVERRIDE_VERSION_STRING
		 	OverRideStyleUpdateVersionString();
		#endif
	#endif	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameSetControlPositions	
//
// Description:	Function to set control positioning in a frame
//
// Input:		FRAME_DATA *frame, UINT32 *pOtherEnd
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleFrameSetControlPositions(FRAME_DATA *frame, UINT32 *pOtherEnd)
{
	UINT32 u32Height = 0;
	UINT32 i;
	CONTROL_DATA *control;
  	UINT8 u8ChkResult;
	
	#ifdef STYLE_OEM_FRAME_CONTROL_POSITION
		OEMStyleFrameSetControlPositions(frame, pOtherEnd);
	#else
		#ifdef STYLE_OVERRIDE_FRAME_CONTROL_POSITION
		 	OverRideStyleFrameSetControlPositions(frame, pOtherEnd);
		#else
			//Move reference end variable based on action
			if(pOtherEnd == &(frame->LastVisibleCtrl))
			{
				i = frame->FirstVisibleCtrl;
			}
			else
			{
				i = frame->LastVisibleCtrl;
			}
			
			//Calculate other end variable
			while( (pOtherEnd == &(frame->LastVisibleCtrl)) ? (i < frame->ControlCount) : TRUE )
			{
				control = frame->ControlList[i];
				        
                //EIP 75486 Support grayout condition for readonly controls
                u8ChkResult = CheckControlCondition( &(control->ControlData) );
                		        
		        if((COND_NONE == u8ChkResult) || (COND_GRAYOUT == u8ChkResult))
		        {
		        	if( (u32Height + control->Height) < frame->FrameData.Height )
		        	{
		        		*pOtherEnd = i;
		        		u32Height += control->Height;
		        	}
		        	else
		        		break; //We cant accommodate
		        }
		        else
		            *pOtherEnd = i; //we can accomodate a suppressed control
				
				if(pOtherEnd == &(frame->LastVisibleCtrl))
					i++;
				else
				{
					// i>=0 in while loop will result in infinite loop
					// break statement should be introduced inside
					if (i == 0)
						break;
					i--;
				}
			}		
			
		#endif
	#endif	

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleOverRideComponent	
//
// Description:	Function to override component or control functionality
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleOverRideComponent(VOID)
{
	#ifdef STYLE_OEM_COMPONENT_OVERRIDE				// SDL
		OEMOverRideComponent();					// OEM
	#else
		#ifdef STYLE_COMPONENT_OVERRIDE				// from Ezport.h
			OverRideComponent();				// From ezport.c
		#endif
	#endif	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_StyleControlSubmenu	
//
// Description:	Function to initialize submenu control
//
// Input:		CONTROL_INFO control, UINT16 pageID, VOID *ref 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _StyleControlSubmenu( CONTROL_INFO *control, UINT16 pageID, VOID *ref )
{
	control->ControlHandle = gHiiHandle;
	control->ControlType = CONTROL_TYPE_SUBMENU;
	control->ControlFlags.ControlVisible = TRUE;
	control->ControlPtr = (VOID*)ref;
	control->ControlPageID = pageID;
	control->ControlDestPageID = 0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleHelpAreaScrollable	
//
// Description:	Function to get Help area scroll support
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN StyleHelpAreaScrollable(VOID)
{
	if(IsHelpAreaScrollBarSupport())		
		return TRUE ;
	else
		return FALSE;
}	
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetShadowSupport	
//
// Description:	Function to get shadow support
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN StyleGetShadowSupport(VOID)
{
	if(STYLE_SHADOW_SUPPORT)		
		return TRUE ;
	else
		return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetScrollBehavior	
//
// Description:	Function to get scroll behavior 
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN StyleGetScrollBehavior(VOID)
{
	return STYLE_SCROLLBAR_ROLLOVER ; // 0 - Item Limit, 1 - Rollover		

}		
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetDateFormat	
//
// Description:	Function to get date format
//
// Input:		VOID
//
// Output:		BOOLEAN 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN StyleGetDateFormat(VOID)
{
	#ifdef STYLE_OEM_DATE_FOMAT
   		return OEMStyleGetDateFormat();
	#else
   		return STYLE_DATE_FORMAT;
	#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleShowDay	
//
// Description:	Function to show day in date format
//
// Input:		VOID
//
// Output:		BOOLEAN 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN StyleShowDay(VOID)
{
	return STYLE_SHOW_DAY ;		

}			
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetStdMaxRows	
//
// Description:	Function to max number of columns
//
// Input:		VOID
//
// Output:		STYLE_STD_MAX_ROWS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN StyleGetStdMaxRows(VOID)
{
	return STYLE_STD_MAX_ROWS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetStdMaxCols	
//
// Description:	Function to get max number of rows
//
// Input:		VOID
//
// Output:		STYLE_STD_MAX_COLS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN StyleGetStdMaxCols(VOID)
{
	return STYLE_STD_MAX_COLS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetClearScreenColor	
//
// Description:	Function to Get Clear Screen Color
//
// Input:		VOID
//
// Output:		STYLE_CLEAR_SCREEN_COLOR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN StyleGetClearScreenColor(VOID)
{
	#ifdef STYLE_OVERRIDE_CLEAR_SCREEN_COLOR
   		return OverRideStyleGetClearScreenColor();
	#else	
		return STYLE_CLEAR_SCREEN_COLOR;
	#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: 	StyleGetPageLinkColor	
//
// Description:	Function to PageLink (Submenu) color
//
// Input:		VOID
//
// Output:		PAGE_LINK_FGCOLOR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 StyleGetPageLinkColor(VOID)
{
	#ifdef STYLE_OVERRIDE_PAGELINK_COLOR
   		return OverRideStyleGetPageLinkColor();
	#else	
		return PAGE_LINK_COLOR;
	#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetScrollBarColor	
//
// Description:	Function to get scrollbar color
//
// Input:		VOID
//
// Output:		FGCOLOR|BGCOLOR 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 StyleGetScrollBarColor(VOID)
{
	#ifdef STYLE_OVERRIDE_SCROLLBAR_COLOR
   		return OverRideStyleGetScrollBarColor();
	#else	
		return  (SCROLLBAR_FGCOLOR | SCROLLBAR_BGCOLOR) ;
	#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetScrollBarUpArrowColor	
//
// Description:	Function to get scrollbar UpArrow Color
//
// Input:		VOID
//
// Output:		FGCOLOR|BGCOLOR 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 StyleGetScrollBarUpArrowColor(VOID)
{
	#ifdef STYLE_OVERRIDE_SCROLLBAR_UP_ARROW_COLOR
   		return OverRideStyleGetScrollBarUpArrowColor();
	#else
		return  (SCROLLBAR_UPARROW_FGCOLOR | SCROLLBAR_UPARROW_BGCOLOR) ;
	#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetScrollBarDownArrowColor
//
// Description:	Function to get scrollbar downarrow color
//
// Input:		VOID
//
// Output:		FGCOLOR|BGCOLOR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 StyleGetScrollBarDownArrowColor(VOID)
{
	#ifdef STYLE_OVERRIDE_SCROLLBAR_DOWN_ARROW_COLOR
   		return OverRideStyleGetScrollBarDownArrowColor();
	#else
   		return  (SCROLLBAR_DOWNARROW_FGCOLOR | SCROLLBAR_DOWNARROW_BGCOLOR) ;
	#endif	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StylePageItemFocus
//
// Description:	This function is called whenever a user navigates to a new page. 
//				OEMs may use this hook to set item focus. 
//				The default behavior sets focus to the previously focused page item. 
//
// Input:		PAGE_DATA *page, FRAME_DATA *frame
//				
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StylePageItemFocus(PAGE_DATA *page, FRAME_DATA *frame )
{
	
	#ifdef STYLE_OEM_PAGE_ITEM_FOCUS				
		OEMStylePageItemFocus(page, frame);
	#else
		#ifdef STYLE_OVERRIDE_PAGE_ITEM_FOCUS		
			OverRideStylePageItemFocus(page, frame);
		#else
		if(STYLE_PAGE_FIRSTITEM_FOCUS)
		{
			UINT32 i;
			for ( i = 0; i < frame->ControlCount; i++ )
			{
				
				if ( _FrameSetControlFocus( frame, i ) )
				{
					frame->FirstVisibleCtrl = 0;
					break;
				}
			}
			///Eip:30111 fix - Update the Help based on the Focussed Item
			UpdatePageFocusedItemHelp(page);			
		}
		#endif
	#endif	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleSubPageItemFocus
//
// Description:	This function is called whenever a user returns (or navigates back) 
//				from a submenu page causing a complete page redraw. OEMs may use this hook to set item focus. 
//				The default behavior sets focus to the previously focused page item. 
//
// Input:		PAGE_DATA *page, FRAME_DATA *frame 
//				
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StyleSubPageItemFocus(PAGE_DATA *page, FRAME_DATA *frame )
{
	#ifdef STYLE_OEM_SUBPAGE_ITEM_FOCUS				// SDL
		OEMStyleSubPageItemFocus(page, frame);		// OEM
	#else
		#ifdef STYLE_OVERRIDE_SUBPAGE_ITEM_FOCUS		// from Ezport.h
			OverRideStyleSubPageItemFocus(page, frame);	// From ezport.c
		#else
		if(STYLE_SUBPAGE_FIRSTITEM_FOCUS)
		{
			UINT32 i;

			for ( i = 0; i < frame->ControlCount; i++ )
			{
				if ( _FrameSetControlFocus( frame, i ) )
				{
					frame->FirstVisibleCtrl = 0;
					break;
				}
			}
		}
		#endif
	#endif	 	
}
#endif
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2013, American Megatrends, Inc.    **//
//**                                                             **//
//**                       All Rights Reserved.                  **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                       Phone: (770)-246-8600                 **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
