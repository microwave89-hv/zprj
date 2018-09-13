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
//**                     Phone: (770)-246-8600                   **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/ezport.c $
//
// $Author: Premkumara $
//
// $Revision: 16 $
//
// $Date: 11/26/13 12:07a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/ezport.c $
// 
// 16    11/26/13 12:07a Premkumara
// [TAG]  		EIP123006
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When switch language between English to Japanese will have
// display japanese character in exit page
// [RootCause]  	While drawing the frame gFlushBuffer is not flushed
// properly
// [Solution]  	Before drawing frames gFlushBuffer is reset with empty
// characters to clear the screen properly
// [Files]  		Ezport.c
// 
// 15    2/11/13 5:57a Premkumara
// [TAG]  		EIP112628
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	(JP000E)SETUP_GO_TO_EXIT_PAGE_ON_EXIT_KEY does not work on
// 4.6.2_TSE_2_15_1234
// [RootCause]  	The Exit FormID value will change if any form is
// generated before Exit page
// [Solution]  	Handled Exit FormID from Binary and handling Exit FormID
// from binary
// [Files]  		Ezport.c, Ezport.sdl, Legacy.c, Legacy.sdl, EzportPlus.c,
// EzportPlus.sdl
// 
// 14    1/22/13 12:15a Rajashakerg
// [TAG]  		EIP103449
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	In Setup click\Touch from navigation window, option are not
// displayed properly
// [RootCause]  	Latest mouse driver providing LEFT_DOWN when we hold the
// mouse left down button.
// [Solution]  	Provided fix resolves the issue.
// [Files]  		ezport.c, PopupEdit.c, ListBox.c, MessageBox.c
// 
// 13    10/18/12 6:05a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 14    10/10/12 12:42p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 12    5/24/12 7:29a Rajashakerg
// [TAG]  		EIP88811
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When pop-up window is invoked in setup and Click on ESC
// icon or ESC/Right Click, it will respond as two times ESC is clicked
// [RootCause]  	ESC functionality provided for left click on the ESC
// sting navigation frame .
// [Solution]  	Now providing the ESC sequence for left down and double
// click
// [Files]  		ezport.c, numeric.c, MessageBox.c
// 
// 11    11/20/11 7:26a Rajashakerg
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
// 10    6/29/11 12:26p Rajashakerg
// [TAG]  		EIP47086, 62098 
// [Category]  	New Feature
// [Description]  	Right clicking from the Main page is not exiting from
// BIOS setup and the Mouse hotclicks.
// [Files]  		minisetup.h, Ezport\style.h,Ezport\EzportBin.sdl,
// Ezport\EzportBin.mak, Ezport\ezport.c, Ezport\EzportBin.cif,
// EzportPlus\style.h, EzportPlus\EzportPlusBin.sdl, EzportPlusBin.mak,
// EzportPlus\EzportPlusBin.cif, EzportPlus\ezportplus.c, Legacy\style.h,
// Legacy\EzportPlusBin.sdl, Legacy\LegacyBin.mak, Legacy\LegacyBin.cif,
// Legacy\legacy.c, TseLiteBin.sdl, TseLite.cif, Memo.c, frame.c,
// application.h, application.c, commonoem.h, CommonHelper.c
// 
// 9     3/28/11 5:13p Rajashakerg
// [TAG]  		EIP56413 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_RESET_BUTTON opcode
// [Files]  		ezport.c, minisetupext.h, ResetButton.c, ResetButton.h,
// Hii.c, TseUefiHii.h, Uefi21Wapper.c, hii.h, Uefi20Wapper.c 
// 
// 8     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 7     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 6     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 10    2/19/10 8:15a Mallikarjunanv
// updated year in copyright message
// 
// 9     2/15/10 10:12p Madhans
// To avoid warnings
// 
// 8     1/09/10 6:11a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 7     8/24/09 5:15p Blaines
// Fix issue setting title and helptitle background color after clear
// screen
// 
// 6     8/13/09 1:22p Blaines
// Support BgColor for MAIN_FRAME, NAV_FRAME, and HELP_FRAME
// 
// 5     8/04/09 6:57p Blaines
// Add Support for Exit Page SDL tokens
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
// 3     5/07/09 10:35a Madhans
// Changes after Bin module
// 
// 9     5/05/09 3:20p Blaines
// 
// 8     5/04/09 6:52p Blaines
// Support customizable Help and Nav frame text Foreground color
// 
// 7     5/01/09 9:25p Blaines
// 
// 6     4/30/09 9:54p Blaines
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
// Name:		ezport.c
//
// Description:	Main file for ezport style module.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "minisetup.h"
#include "ezport.h"

extern	STYLECOLORS  Colors ;
extern 	AMI_IFR_MENU gMenuData ;

extern UINTN gLabelLeftMargin ;
extern UINTN gControlLeftMargin ;
extern UINTN gControlLeftPad ;
extern UINTN gControlRightAreaWidth ;
static CALLBACK_SUBMENU gMenuCallbackData = { { CALLBACK_TYPE_MENU, sizeof(CALLBACK_MENU) }, 0 };
static CALLBACK_SUBMENU gSubmenuCallbackData = { { CALLBACK_TYPE_SUBMENU, sizeof(CALLBACK_SUBMENU) }, 0 };
static CALLBACK_VARIABLE gVariableCallbackData = { { CALLBACK_TYPE_VARIABLE, sizeof(CALLBACK_VARIABLE) }, 0, 0, 0, NULL };
static CALLBACK_PASSWORD gPasswordCallbackData = { { CALLBACK_TYPE_PASSWORD, sizeof(CALLBACK_PASSWORD) }, 0, 0, 0, NULL, TRUE };

VOID _FrameSubmenuCallback( FRAME_DATA *frame, SUBMENU_DATA *submenu, VOID *cookie );
VOID _FrameMenuCallback( FRAME_DATA *frame, MENU_DATA *menu, VOID *cookie );
VOID HotclickESCaction(VOID);
BOOLEAN   gotoExitOnEscKey(EFI_GUID *exitFormGuid, UINT16 *pageClass, UINT16 *pageSubclass, UINT16 *pageFormID); //EIP-112628

#if SETUP_STYLE_EZPORT

#if SETUP_STYLE_FULL_SCREEN
static FRAME_INFO _gStyleFullSubFrames[] =
{
//	{ FrameType		Drawable	Border,		BorderType,	Width,			Height,			Top,			Left,			FGColor,		BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE,		0,		TITLE_FULL_W,		TITLE_FULL_H,		TITLE_FULL_Y,		TITLE_FULL_X,		TITLE_FGCOLOR,		TITLE_BGCOLOR		},// TITLE
	{ SUBTITLE_FRAME,	TRUE,		FALSE,		0,		MENU_FULL_W,		MENU_FULL_H,		MENU_FULL_Y,		MENU_FULL_X,		MENU_FGCOLOR,		MENU_BGCOLOR		},// SUBTITLE (MENU)
	{ MAIN_FRAME,		TRUE,		FALSE,		0,		MAIN_FULL_W,		MAIN_FULL_H,		MAIN_FULL_Y,		MAIN_FULL_X,		PAGE_FGCOLOR,		MAIN_BGCOLOR		},// Main
	{ HELP_FRAME,		TRUE,		FALSE,		0,		HELP_FULL_W,		HELP_FULL_H,		HELP_FULL_Y,		HELP_FULL_X,		HELP_FGCOLOR,		HELP_BGCOLOR		},// HELP
	{ NAV_FRAME,		TRUE,		FALSE,		0,		NAV_FULL_W,		NAV_FULL_H,		NAV_FULL_Y,		NAV_FULL_X,		NAV_FGCOLOR,		NAV_BGCOLOR		},// NAVIGATION
	{ HELPTITLE_FRAME,	TRUE,		FALSE,		0,		HELPTITLE_FULL_W,	HELPTITLE_FULL_H,	HELPTITLE_FULL_Y,	HELPTITLE_FULL_X,	HELPTITLE_FGCOLOR,	HELPTITLE_BGCOLOR	} // HELP TITLE (Copyright)
};
#endif

static FRAME_INFO _gStyleStandardSubFrames[] =
{
//	{ FrameType		Drawable	Border,		BorderType,	Width,		Height,		Top,		Left,		FGColor,		BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE,		0,		TITLE_W,	TITLE_H,	TITLE_Y,	TITLE_X,	TITLE_FGCOLOR,		TITLE_BGCOLOR		},// TITLE
	{ SUBTITLE_FRAME,	TRUE,		FALSE,		0,		MENU_W,		MENU_H,		MENU_Y,		MENU_X,		MENU_FGCOLOR,		MENU_BGCOLOR		},// SUBTITLE (MENU)
	{ MAIN_FRAME,		TRUE,		FALSE,		0,		MAIN_W,		MAIN_H,		MAIN_Y,		MAIN_X,		PAGE_FGCOLOR,		MAIN_BGCOLOR		},// Main
	{ HELP_FRAME,		TRUE,		FALSE,		0,		HELP_W,		HELP_H,		HELP_Y,		HELP_X,		HELP_FGCOLOR,		HELP_BGCOLOR		},// HELP
	{ NAV_FRAME,		TRUE,		FALSE,		0,		NAV_W,		NAV_H,		NAV_Y,		NAV_X,		NAV_FGCOLOR,		NAV_BGCOLOR		},// NAVIGATION
	{ HELPTITLE_FRAME,	TRUE,		FALSE,		0,		HELPTITLE_W,	HELPTITLE_H,	HELPTITLE_Y,	HELPTITLE_X,	HELPTITLE_FGCOLOR,	HELPTITLE_BGCOLOR	} // HELP TITLE (Copyright)
};

AMITSE_CONTROL_MAP gTseControlMap[] =
{
//	ControlType			 ControlMethods		 	CallbackSuppored 	CallbackFunction		CallbackContext		
 { CONTROL_TYPE_MENU, 	 (CONTROL_METHODS*)&gMenu, 	TRUE, (VOID*)(UINTN)&_FrameMenuCallback, (VOID*)(UINTN)&gMenuCallbackData},
 { CONTROL_TYPE_SUBMENU, (CONTROL_METHODS*)&gSubMenu,TRUE, (VOID*)(UINTN)&_FrameSubmenuCallback, (VOID*) &gSubmenuCallbackData},
 { CONTROL_TYPE_LABEL, 	 (CONTROL_METHODS*)&gLabel, 	TRUE, (VOID*)(UINTN)&StyleLabelCallback, (VOID*) NULL},
 { CONTROL_TYPE_TEXT, 	 (CONTROL_METHODS*)&gText, 	FALSE,(VOID*)NULL, (VOID*) NULL},
 { CONTROL_TYPE_POPUP_STRING, (CONTROL_METHODS*)&gPopupString, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
 { CONTROL_TYPE_DATE, (CONTROL_METHODS*)&gDate, FALSE, (VOID*)NULL, (VOID*) NULL},
 { CONTROL_TYPE_TIME, (CONTROL_METHODS*)&gTime, FALSE, (VOID*)NULL, (VOID*) NULL},
 { CONTROL_TYPE_POPUPSEL, (CONTROL_METHODS*)&gPopupSel, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
	// Checkbox is just popup sel
 { CONTROL_TYPE_CHECKBOX, (CONTROL_METHODS*)&gPopupSel, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
 { CONTROL_TYPE_MEMO, (CONTROL_METHODS*)&gMemo, FALSE, (VOID*)NULL, (VOID*)NULL},
 { CONTROL_TYPE_NUMERIC, (CONTROL_METHODS*)&gNumeric, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
 { CONTROL_TYPE_ORDERED_LIST, (CONTROL_METHODS*)&gOrdListBox, TRUE, (VOID*)(UINTN)&_FrameVariableCallback, (VOID*) &gVariableCallbackData},
 { CONTROL_TYPE_PASSWORD, (CONTROL_METHODS*)&gPopupPassword, TRUE, (VOID*)(UINTN)&_FramePasswordCallback, (VOID*)&gPasswordCallbackData},
 { CONTROL_TYPE_ACTION, (CONTROL_METHODS*)&gUefiAction, TRUE, (VOID*)(UINTN) &StyleLabelCallback, (VOID*) NULL},
 { CONTROL_TYPE_RESET, (CONTROL_METHODS*)&gResetButton, TRUE, (VOID*)(UINTN) &StyleLabelCallback, (VOID*) NULL},//EIP:56413 Updated the Reset Button Control information
	// CONTROL_TYPE_NULL need to be last member 
 { CONTROL_TYPE_NULL, (CONTROL_METHODS*)NULL, FALSE, (VOID*)NULL, (VOID*) NULL}
};

static FRAME_INFO *_gStyleSubFrames = _gStyleStandardSubFrames ;

UINT8 gVerticalMainDivider = VERTICAL_MAIN_DIVIDER ;
UINT8 gHorizontalHelpDivider = HORIZONTAL_HELP_DIVIDER ;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleInit	
//
// Description:	Function to initialize style
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID	OverRideStyleInit( VOID )
{

	gLabelLeftMargin = STYLE_LABEL_LEFT_MARGIN ;
	gControlLeftMargin = STYLE_CONTROL_LEFT_MARGIN ;
	gControlLeftPad = STYLE_CONTROL_LEFT_PAD ;
	gControlRightAreaWidth 	= STYLE_CONTROL_RIGHT_AREA_WIDTH ;
		

#if SETUP_STYLE_FULL_SCREEN
	if ( gMaxCols == STYLE_FULL_MAX_COLS )
	{
		_gStyleSubFrames 	= _gStyleFullSubFrames;

		gVerticalMainDivider 	= FULL_VERTICAL_MAIN_DIVIDER ;
		gHorizontalHelpDivider 	= FULL_HORIZONTAL_HELP_DIVIDER ;

		gLabelLeftMargin 	= FULL_STYLE_LABEL_LEFT_MARGIN ;
		gControlLeftMargin 	= FULL_STYLE_CONTROL_LEFT_MARGIN ;
		gControlLeftPad 	= FULL_STYLE_CONTROL_LEFT_PAD ;
		gControlRightAreaWidth 	= FULL_STYLE_CONTROL_RIGHT_AREA_WIDTH ;
	}
#endif

	if(gLabelLeftMargin < 2)
		gLabelLeftMargin = 2 ;
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameIndexOf	
//
// Description:	Function to get frame index
//
// Input:		UINT32 frameType
//
// Output:		UINT32 index
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32	StyleFrameIndexOf( UINT32 frameType )
{
	UINT32 FrameCount ;
	UINT32 i;
	
	FrameCount = sizeof(_gStyleStandardSubFrames) / sizeof(FRAME_INFO);
	

	for ( i = 0; i < FrameCount; i++ )
	{
		if( _gStyleSubFrames[i].FrameType == frameType ){
			return i ;
			break ;
		}
	}
	
	return i ;
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetPageFrames	
//
// Description:	Function to number of frames
//
// Input:		UINT32 page
//
// Output:		UINT32 number of frames
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32	StyleGetPageFrames( UINT32 page )
{
	return sizeof(_gStyleStandardSubFrames) / sizeof(FRAME_INFO);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleDrawPageBorder	
//
// Description:	Function to draw page border
//
// Input:		UINT32 page
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OverRideStyleDrawPageBorder( UINT32 page )
{
	PAGE_DATA *Page ;
	FRAME_DATA *fTitle, *fMenu, *fHelptitle, *fMain;

	CHAR16 *line;
	UINT8 lineNumber;
	UINT8 start, end, col;
	UINT8 pbx,pby,pbw,pbh;
	UINT8 vertDivider = VERTICAL_MAIN_DIVIDER ;
	UINT8 horzDivider = HORIZONTAL_HELP_DIVIDER;

	Page = gApp->PageList[page];
	
	fTitle = Page->FrameList[StyleFrameIndexOf(TITLE_FRAME)];
	fHelptitle = Page->FrameList[StyleFrameIndexOf(HELPTITLE_FRAME)];
	fMenu = Page->FrameList[StyleFrameIndexOf(SUBTITLE_FRAME)];
	fMain = Page->FrameList[StyleFrameIndexOf(MAIN_FRAME)];//EIP-123006

	pbx = PAGEBORDER_X;
	pby = PAGEBORDER_Y;
	pbw = PAGEBORDER_W;
	pbh = PAGEBORDER_H;

	if ( gMaxCols == STYLE_FULL_MAX_COLS )
	{
		vertDivider = FULL_VERTICAL_MAIN_DIVIDER ;
		horzDivider = FULL_HORIZONTAL_HELP_DIVIDER;
		pbx = PAGEBORDER_FULL_X;
		pby = PAGEBORDER_FULL_Y;
		pbw = PAGEBORDER_FULL_W;
		pbh = PAGEBORDER_FULL_H;
	}
		

	line = EfiLibAllocateZeroPool( (gMaxCols + 1) * sizeof(CHAR16) );
	if ( line == NULL )
		return;

	ClearLinesWithoutFlush( fTitle->FrameData.Top, fTitle->FrameData.Height, fTitle->FrameData.BGColor | fTitle->FrameData.FGColor );
	ClearLinesWithoutFlush( fHelptitle->FrameData.Top, fHelptitle->FrameData.Height, fHelptitle->FrameData.BGColor | fHelptitle->FrameData.FGColor );
	ClearLinesWithoutFlush( fMenu->FrameData.Top, fMenu->FrameData.Height, fMenu->FrameData.BGColor | fMenu->FrameData.FGColor );

	//EIP-123006 Clearing gFlushBuffer with attribute(0) and chars(' ')
	MemSet( &(gFlushBuffer->Attribs[fMain->FrameData.Top*gMaxCols]), fMain->FrameData.Height*gMaxCols, 0 );
	MemFillUINT16Buffer( &(gFlushBuffer->Chars[fMain->FrameData.Top*gMaxCols]), fMain->FrameData.Height*gMaxCols, (UINT16)L' ' );

	ClearLinesWithoutFlush( pby, pbh, PAGE_BGCOLOR | PAGE_FGCOLOR );
	
	
	DrawWindow( pbx, pby, pbw, pbh, PAGE_BGCOLOR| PAGE_FGCOLOR, TRUE, FALSE );



	MemFillUINT16Buffer( &line[1], gMaxCols - 1, BOXDRAW_HORIZONTAL );

	line[0] = BOXDRAW_DOWN_HORIZONTAL;
	line[1] = L'\0';
	DrawString( vertDivider, pby, line );

	line[0] = BOXDRAW_UP_HORIZONTAL;
	DrawString( vertDivider, pby+pbh-1, line );
		
	// center divider
	line[0] = BOXDRAW_VERTICAL;

	col = vertDivider ;
	start = pby+1; 
	end = pby+pbh-1 ;

	for ( lineNumber = start; lineNumber < end ; lineNumber++ )
		DrawString( col, lineNumber, line );

	// Horizontal Help divider 
	MemFillUINT16Buffer( &line[1], gMaxCols - 1, BOXDRAW_HORIZONTAL );
	line[0] = BOXDRAW_VERTICAL;
	//line[1] = BOXDRAW_HORIZONTAL;
	line[gMaxCols - vertDivider-1] = L'\0';
	DrawString(col, horzDivider, line );

	FlushLines( 0, end-1 );

	gBS->FreePool( line );
	
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OverRideStyleGetFrameInitData	
//
// Description:	Function to get frame initialization data
//
// Input:		UINT32 page, UINT32 frame
//
// Output:		VOID* 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *OverRideStyleGetFrameInitData( UINT32 page, UINT32 frame )
{
	return &_gStyleSubFrames[frame];
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleFrameAddTitle	
//
// Description:	Function to add frame title 
//
// Input:		FRAME_DATA *frame, UINT32 frameType, CONTROL_INFO * dummy
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StyleFrameAddTitle( FRAME_DATA *frame, UINT32 frameType,CONTROL_INFO * dummy )
{
	return EFI_UNSUPPORTED;
}

#endif /* SETUP_STYLE_EZPORT */

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleEscKey	
//
// Description:	Function to handle ESC Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HandleEscKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	UINT16 pageClass = 0, pageSubclass = 0, pageFormID = 0;
	EFI_GUID ExitPageGuid;


	if(FormBrowserHandleValid())
		app->Quit = TRUE;

	else if ( gotoExitOnEscKey (&ExitPageGuid, &pageClass, &pageSubclass, &pageFormID) )//EIP-112628
	{
    	UINT32 i=0;
    	PAGE_INFO *pageInfo;

		for ( i = 0; i < gPages->PageCount; i++ )
		{
			pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[i]);
			if (
	         	( EfiCompareGuid(&ExitPageGuid,&(gPageIdInfo[pageInfo->PageIdIndex].PageGuid)) ) &&
					( pageClass == gPageIdInfo[pageInfo->PageIdIndex].PageClass ) 							&&
					( pageSubclass == gPageIdInfo[pageInfo->PageIdIndex].PageSubClass ) 					&&
					( pageFormID == pageInfo->PageFormID ) 
			   )
			{
				gApp->CurrentPage = i; // Page found go to exit page
	            gApp->CompleteRedraw = TRUE;
	            gApp->Fixed = FALSE;
				break;
			}
		}
		if(i >= gPages->PageCount) //Page not found exit application
			app->Quit = ExitApplication();
	}

	else
		app->Quit = ExitApplication();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleSaveExitKey	
//
// Description:	Function to handle Save and Exit Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HandleSaveExitKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	app->Quit = SaveAndExit();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandlePrevValuesKey	
//
// Description:	Function to handle Load Previous value Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HandlePrevValuesKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( app->CurrentPage != 0 )
		LoadPreviousValues( TRUE );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleFailsafeKey	
//
// Description:	Function to handle Load Failsafe values Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HandleFailsafeKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( app->CurrentPage != 0 )
		LoadFailsafeDefaults();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleOptimalKey	
//
// Description:	Function to handle Load Optimal values Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HandleOptimalKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( app->CurrentPage != 0 )
		LoadOptimalDefaults();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandleHelpKey	
//
// Description:	Function to handle Help Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HandleHelpKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( app->CurrentPage != 0 )
		ShowHelpMessageBox();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HandlePrnScrnKey	
//
// Description:	Function to handle print screen Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HandlePrnScrnKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	TseHotkeyPrintScreenSupport();
}
//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
//EIP:47086 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MainFrameHandlewithMouse	
//
// Description:	Function to handle Main Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MainFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{
	NumericSoftKbdExit();
	if(app->Action->Input.Data.MouseInfo.ButtonStatus == TSEMOUSE_RIGHT_CLICK)
		app->Quit = ExitApplication();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HelpFrameHandlewithMouse	
//
// Description:	Function to handle Help Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HelpFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{
	NumericSoftKbdExit();
	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NavFrameHandlewithMouse	
//
// Description:	Function to handle Navigation Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NavFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{

	UINT32 Action;
// EIP :62098 -Handling mouse hot click operations
	NumericSoftKbdExit();
	Action = MapControlMouseActionHook(&app->Action->Input.Data.MouseInfo);
//EIP 88811 : When pop-up window is invoked in setup and Click on ESC icon or ESC/Right Click, it will respond as two times ESC is clicked
	if(( ControlActionChoose == Action )||( ControlActionSelect == Action ))//EIP 103449  : In Setup click\Touch from navigation window, option are not displayed properly
	{
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 4)
			if ( app->CurrentPage != 0 )
			{
				ShowHelpMessageBox();
				return;
			}
		
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 5)
			if ( app->CurrentPage != 0 )
			{	
				LoadPreviousValues( TRUE );
				return;
			}
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 6)
			if ( app->CurrentPage != 0 )
			{	
				LoadOptimalDefaults();
				return;
			}
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 7)
			{
				app->Quit = SaveAndExit();
				return;
			}
		
		if(app->Action->Input.Data.MouseInfo.Top == hotclick->HotClickData.Yo + 8)		
			HotclickESCaction();	
		//app->Quit = ExitApplication();	
	
	}	
}
//EIP:47086 END

//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2011, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                     Phone: (770)-246-8600                   **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
