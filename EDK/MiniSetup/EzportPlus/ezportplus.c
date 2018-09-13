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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/EzportPlus/ezportplus.c $
//
// $Author: Premkumara $
//
// $Revision: 12 $
//
// $Date: 2/11/13 6:06a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/EzportPlus/ezportplus.c $
// 
// 12    2/11/13 6:06a Premkumara
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
// 11    10/18/12 6:07a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:43p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 10    1/18/12 7:37a Premkumara
// [TAG]  		EIP79958
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Softkeyboard is not launched for Password control in
// EzportPlus style module
// [RootCause]  	Soft keyboard was not launched for Password field in
// EzportPlus module
// [Solution]  	Launched Softkeyboard properly in EzportPlus style module
// [Files]  		EzportPlus.c
// 
// 9     1/06/12 5:05p Blaines
// [TAG] - EIP 77887 
// [Category]- Function Request
// [Synopsis]- Change input system password box in same window
// [Description] - Display and get System password prompts for old, new,
// and confirm text in the same window, 
// 
// [Files]
// StyleTokens.c, StyleStr.uni, EzportPlus.sdl, ezportplus.c
// 
// 8     12/14/11 6:24p Blaines
// Added code to suppress the warnings from static code analyzer
// 
// 7     12/14/11 3:50p Blaines
// EIP:74899 Fixed issue with message not getting disaplayed when password
// is cleared.
// 
// 6     12/14/11 2:00p Blaines
// EIP:74899 Add missing interactive support
// 
// 5     12/14/11 1:37p Blaines
// Fix in _PopupPasswordActivate function for IDE password applied to
// _EzportPlusPopupPasswordActivate. 
// 
// 4     12/13/11 6:15p Blaines
// Remove error message when ESC key pressed.
// Display message when password is cleared.
// 
// 3     11/23/11 1:26p Blaines
// [TAG] - EIP 74899 
// [Category]- Function Request
// [Synopsis]- Change input password box in same window
// [Description] - Display Hdd and System password prompts for old, new,
// and confirm text in the same window, 
// 
// [Files]
// StyleTokens.c, StyleStr.uni, EzportPlus.sdl, ezportplus.c
// 
// 2     6/29/11 12:36p Rajashakerg
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
// 1     3/28/11 11:51p Madhans
// [TAG]  		EIP54968
// [Category]  	Improvement
// [Description]  	To Support different style modules in TSE generically
// [Files]  		Ezport module updated. EzportPlus and Legacy Styles Modules
// added.
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
// Name:		ezportplus.c
//
// Description:	Main file for ezportplus style module.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "minisetup.h"
#include "ezportplus.h"

extern	STYLECOLORS  Colors ;
extern 	AMI_IFR_MENU gMenuData ;
extern UINTN gInvalidPasswordFailMsgBox;

extern UINTN gLabelLeftMargin ;
extern UINTN gControlLeftMargin ;
extern UINTN gControlLeftPad ;
extern UINTN gControlRightAreaWidth ;
extern BOOLEAN IsPasswordSupportNonCaseSensitive();

static CALLBACK_SUBMENU gMenuCallbackData = { { CALLBACK_TYPE_MENU, sizeof(CALLBACK_MENU) }, 0 };
static CALLBACK_SUBMENU gSubmenuCallbackData = { { CALLBACK_TYPE_SUBMENU, sizeof(CALLBACK_SUBMENU) }, 0 };
static CALLBACK_VARIABLE gVariableCallbackData = { { CALLBACK_TYPE_VARIABLE, sizeof(CALLBACK_VARIABLE) }, 0, 0, 0, NULL };
static CALLBACK_PASSWORD gPasswordCallbackData = { { CALLBACK_TYPE_PASSWORD, sizeof(CALLBACK_PASSWORD) }, 0, 0, 0, NULL, TRUE };

VOID _FrameSubmenuCallback( FRAME_DATA *frame, SUBMENU_DATA *submenu, VOID *cookie );
VOID _FrameMenuCallback( FRAME_DATA *frame, MENU_DATA *menu, VOID *cookie );

BOOLEAN   gotoExitOnEscKey(EFI_GUID *exitFormGuid, UINT16 *pageClass, UINT16 *pageSubclass, UINT16 *pageFormID);//EIP-112628

#if SETUP_STYLE_EZPORTPLUS

#if SETUP_STYLE_FULL_SCREEN
static FRAME_INFO _gStyleFullSubFrames[] =
{
//	{ FrameType		Drawable	Border,		BorderType,	Width,			Height,			Top,			Left,			FGColor,		BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE,		0,		TITLE_FULL_W,		TITLE_FULL_H,		TITLE_FULL_Y,		TITLE_FULL_X,		TITLE_FGCOLOR,		TITLE_BGCOLOR		},// TITLE
	{ SUBTITLE_FRAME,	TRUE,		FALSE,		0,		MENU_FULL_W,		MENU_FULL_H,		MENU_FULL_Y,		MENU_FULL_X,		MENU_FGCOLOR,		MENU_BGCOLOR		},// SUBTITLE (MENU)
    { HELPTITLE_FRAME,	TRUE,		FALSE,		0,		HELPTITLE_FULL_W,	HELPTITLE_FULL_H,	HELPTITLE_FULL_Y,	HELPTITLE_FULL_X,	HELPTITLE_FGCOLOR,	HELPTITLE_BGCOLOR	},// HELP TITLE (Copyright)	
    { HELP_FRAME,		TRUE,		FALSE,		0,		HELP_FULL_W,		HELP_FULL_H,		HELP_FULL_Y,		HELP_FULL_X,		HELP_FGCOLOR,		HELP_BGCOLOR		},// HELP    
    { MAIN_FRAME,		TRUE,		FALSE,		0,		MAIN_FULL_W,		MAIN_FULL_H,		MAIN_FULL_Y,		MAIN_FULL_X,		PAGE_FGCOLOR,		MAIN_BGCOLOR		},// Main
    { NAV_FRAME,		TRUE,		FALSE,		0,		NAV_FULL_W,		    NAV_FULL_H,		    NAV_FULL_Y,		    NAV_FULL_X,		    NAV_FGCOLOR,	    NAV_BGCOLOR		    }// NAVIGATION
	
};
#endif

static FRAME_INFO _gStyleStandardSubFrames[] =
{
//	{ FrameType		Drawable	Border,		BorderType,	Width,		Height,		Top,		Left,		FGColor,		BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE,		0,		TITLE_W,	TITLE_H,	TITLE_Y,	TITLE_X,	TITLE_FGCOLOR,		TITLE_BGCOLOR		},// TITLE
	{ SUBTITLE_FRAME,	TRUE,		FALSE,		0,		MENU_W,		MENU_H,		MENU_Y,		MENU_X,		MENU_FGCOLOR,		MENU_BGCOLOR		},// SUBTITLE (MENU)
    { HELPTITLE_FRAME,	TRUE,		FALSE,		0,		HELPTITLE_W,HELPTITLE_H,HELPTITLE_Y,HELPTITLE_X,HELPTITLE_FGCOLOR,	HELPTITLE_BGCOLOR	},// HELP TITLE (Copyright)	
    { HELP_FRAME,		TRUE,		FALSE,		0,		HELP_W,		HELP_H,		HELP_Y,		HELP_X,		HELP_FGCOLOR,		HELP_BGCOLOR		},// HELP
    { MAIN_FRAME,		TRUE,		FALSE,		0,		MAIN_W,		MAIN_H,		MAIN_Y,		MAIN_X,		PAGE_FGCOLOR,		MAIN_BGCOLOR		},// Main
	{ NAV_FRAME,		TRUE,		FALSE,		0,		NAV_W,		NAV_H,		NAV_Y,		NAV_X,		NAV_FGCOLOR,		NAV_BGCOLOR		    }// NAVIGATION
	
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
	FRAME_DATA *fTitle, *fMenu, *fHelptitle ;

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
	ClearLinesWithoutFlush( pby, pbh, PAGE_BGCOLOR | PAGE_FGCOLOR );
	
	
	DrawWindow( pbx, pby, pbw, pbh, PAGE_BGCOLOR| PAGE_FGCOLOR, TRUE, FALSE );

    // Hidden line in first page
    if (Page->PageData.PageIdIndex == FIRST_PAGE_ID_INDEX)
    {
        gBS->FreePool( line );
        return;
    }

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

#endif /* SETUP_STYLE_EZPORTPLUS */

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusHandleEscKey	
//
// Description:	Function to handle ESC Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusHandleEscKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
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
// Procedure:	EzportPlusHandleSaveExitKey	
//
// Description:	Function to handle Save and Exit Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusHandleSaveExitKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	app->Quit = SaveAndExit();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusHandlePrevValuesKey	
//
// Description:	Function to handle Load Previous value Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusHandlePrevValuesKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( app->CurrentPage != 0 )
		LoadPreviousValues( TRUE );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusHandleFailsafeKey	
//
// Description:	Function to handle Load Failsafe values Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusHandleFailsafeKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( app->CurrentPage != 0 )
		LoadFailsafeDefaults();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusHandleOptimalKey	
//
// Description:	Function to handle Load Optimal values Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusHandleOptimalKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( app->CurrentPage != 0 )
		LoadOptimalDefaults();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusHandleHelpKey	
//
// Description:	Function to handle Help Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusHandleHelpKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( app->CurrentPage != 0 )
		ShowHelpMessageBox();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusHandlePrnScrnKey	
//
// Description:	Function to handle print screen Hotkey action
//
// Input:		APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusHandlePrnScrnKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	TseHotkeyPrintScreenSupport();
}

//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
//EIP:47086 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusMainFrameHandlewithMouse	
//
// Description:	Function to handle Main Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusMainFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{
	if(app->Action->Input.Data.MouseInfo.ButtonStatus == TSEMOUSE_RIGHT_CLICK)
		app->Quit = ExitApplication();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusHelpFrameHandlewithMouse	
//
// Description:	Function to handle Help Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusHelpFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{

	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusNavFrameHandlewithMouse	
//
// Description:	Function to handle Navigation Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusNavFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{
}
//EIP:47086 END




//EIP:74899 START
#if OVERRIDE_PopupPwdHandleActionOverRide
extern VOID UpdatePasswordToNonCaseSensitive(CHAR16 *Password, UINTN PwdLength);
extern UINT8 CallbackShowMessageBox( UINTN data, UINT8 type );
extern UINTN gClearPasswordMsgBox ;

EFI_STATUS _EzportPlusPopupPasswordHandleAction( VOID *popuppassword, VOID *Data);
EFI_STATUS 	PopupPwdHandleActionOverRide(POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data)
{
	return _EzportPlusPopupPasswordHandleAction(popuppassword, Data);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusShowPasswordErrorMessageBox
//
// Description:	Function to Display the password failed message box
//
// Input:	None
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusShowPasswordErrorMessageBox( VOID )
{
	UINT8 sel = 0 ;
	AMI_POST_MGR_KEY OutKey ;

    PostManagerDisplayMsgBoxEx(
    	HiiGetString( gHiiHandle, STRING_TOKEN(STR_ERROR)), 
    	HiiGetString( gHiiHandle, STRING_TOKEN(STR_ERROR_PSWD)), 
    	NULL, MSGBOX_EX_CATAGORY_WARNING, MSGBOX_TYPE_OK,
    	NULL, 0, NULL, 0, &sel, &OutKey
	) ;
	TSEStringReadLoopExitHook();//EIP-79958 Exit softkeyboard after display Error Msg Box
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusShowPasswordSuccessMessageBox
//
// Description:	Function to Display the password success message box
//
// Input:	None
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusShowPasswordSuccessMessageBox( VOID )
{
	UINT8 sel = 0 ;
	AMI_POST_MGR_KEY OutKey ;

    PostManagerDisplayMsgBoxEx(
    	HiiGetString( gHiiHandle, STRING_TOKEN(STR_SUCCESS)), 
    	HiiGetString( gHiiHandle, STRING_TOKEN(STR_PASSWORD_SUCCESS_MSG)), 
    	NULL, MSGBOX_EX_CATAGORY_SUCCESS, MSGBOX_TYPE_OK,
    	NULL, 0, NULL, 0, &sel, &OutKey
	) ;
	TSEStringReadLoopExitHook();//EIP-79958 Exit SoftKeyboard after displayed Successful Msg Box
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusShowPasswordClearedMessageBox
//
// Description:	Function to Display the password success message box
//
// Input:	None
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EzportPlusShowPasswordClearedMessageBox( VOID )
{
	UINT8 sel = 0 ;
	AMI_POST_MGR_KEY OutKey ;

    PostManagerDisplayMsgBoxEx(
    	HiiGetString( gHiiHandle, STRING_TOKEN(STR_INFO)), 
    	HiiGetString( gHiiHandle, STRING_TOKEN(STR_PASSWORD_CLEARED_MSG)), 
    	NULL, MSGBOX_EX_CATAGORY_QUERY, MSGBOX_TYPE_OK,
    	NULL, 0, NULL, 0, &sel, &OutKey
	) ;
	TSEStringReadLoopExitHook(); //EIP-79958 Exit Softkeyboard after displayed Clear Old Password Msg Box
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusPopupPasswordSetPrompt
//
// Description:	Function to display password prompts for new, and confirm in the same window.
//
// Input:	POPUP_PASSWORD_DATA *PopupPassword,
//          UINT16 NewPrompt, 
//          CHAR16 **NewPwd,
//          UINT16 ConfirmPrompt, 
//          CHAR16 **ConfirmPwd,
//
// Output:	Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EzportPlusPopupPasswordSetPrompt(POPUP_PASSWORD_DATA *PopupPassword, UINT16 NewPrompt, CHAR16 **NewPwd, UINT16 ConfirmPrompt, CHAR16 **ConfirmPwd)
{
    EFI_STATUS Status = EFI_SUCCESS ;

    UINT8 Length = (UINT8)UefiGetMaxValue(PopupPassword->ControlData.ControlPtr);

    TEXT_INPUT_TEMPLATE SetPasswordPrompt[2] = 
    {
        {NewPrompt, Length, TSE_FILTER_KEY_NULL, TRUE, NULL},
        {ConfirmPrompt, Length, TSE_FILTER_KEY_NULL, TRUE, NULL}
    };

    UINT16 Title = STRING_TOKEN(STR_SET_PASSWORD_PROMPT) ;

    *NewPwd = EfiLibAllocateZeroPool((Length+1) * sizeof(CHAR16) );
    *ConfirmPwd = EfiLibAllocateZeroPool((Length+1) * sizeof(CHAR16) );

    SetPasswordPrompt[0].Value = *NewPwd ;
    SetPasswordPrompt[1].Value = *ConfirmPwd ;
    
    
    if ( *NewPwd == NULL || *ConfirmPwd == NULL)
        return EFI_OUT_OF_RESOURCES ;
	
	TSEStringReadLoopEntryHook(); //EIP-79958 Launch Softkeyboard on selecting Password control for setting password

    Status = PostManagerDisplayTextBox(
			gHiiHandle,
            Title,
            SetPasswordPrompt, 
            2,
            NULL
			) ;	
	
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EzportPlusPopupPasswordChangePrompt
//
// Description:	Function to display password prompts for old, new, and confirm in the same window.
//
// Input:	POPUP_PASSWORD_DATA *PopupPassword,
//          UINT16 OldPrompt, 
//          CHAR16 **OldPwd, 
//          UINT16 NewPrompt, 
//          CHAR16 **NewPwd,
//          UINT16 ConfirmPrompt, 
//          CHAR16 **ConfirmPwd,
//
// Output:	Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EzportPlusPopupPasswordChangePrompt(POPUP_PASSWORD_DATA *PopupPassword, UINT16 OldPrompt, CHAR16 **OldPwd, UINT16 NewPrompt, CHAR16 **NewPwd, UINT16 ConfirmPrompt, CHAR16 **ConfirmPwd)
{

    EFI_STATUS Status = EFI_SUCCESS ;

    UINT8 Length = (UINT8)UefiGetMaxValue(PopupPassword->ControlData.ControlPtr);

    TEXT_INPUT_TEMPLATE ChangePasswordPrompt[3] = 
    {
        {OldPrompt, Length, TSE_FILTER_KEY_NULL, TRUE, NULL},
        {NewPrompt, Length, TSE_FILTER_KEY_NULL, TRUE, NULL},
        {ConfirmPrompt, Length, TSE_FILTER_KEY_NULL, TRUE, NULL}
    };

    UINT16 Title = STRING_TOKEN(STR_CHANGE_PASSWORD_PROMPT) ;

    *OldPwd = EfiLibAllocateZeroPool((Length+1) * sizeof(CHAR16) );
    *NewPwd = EfiLibAllocateZeroPool((Length+1) * sizeof(CHAR16) );
    *ConfirmPwd = EfiLibAllocateZeroPool((Length+1) * sizeof(CHAR16) );

    ChangePasswordPrompt[0].Value = *OldPwd ;
    ChangePasswordPrompt[1].Value = *NewPwd ;
    ChangePasswordPrompt[2].Value = *ConfirmPwd ;
    
    
    if ( *OldPwd == NULL || NewPwd == NULL || *ConfirmPwd == NULL)
        return EFI_OUT_OF_RESOURCES ;
	
	TSEStringReadLoopEntryHook(); //EIP-79958 Launch Softkeyboard on selecting Password control for changing password

    Status = PostManagerDisplayTextBox(
			gHiiHandle,
            Title,
            ChangePasswordPrompt, 
            3,
            NULL
			) ;	
	
	return Status;
}

BOOLEAN IsPasswordSupportNonCaseSensitive();
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_EzportPlusPopupPasswordActivate
//
// Description:	function to set and activate a password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _EzportPlusPopupPasswordActivate(POPUP_PASSWORD_DATA *popuppassword)
{
   	EFI_STATUS Status = EFI_UNSUPPORTED;
	BOOLEAN AbortUpdate = FALSE, ChangePwd = FALSE, ClearPwd = FALSE ;
    CHAR16 /* *TempText=NULL,*/ *Text=NULL,*NewPswd=NULL,*ConfirmNewPswd=NULL;
    VOID *data = popuppassword->ControlData.ControlPtr;
	UINTN NewPwLen = 0, ConfirmPwLen = 0;

    if( PopupPwdAuthenticateIDEPwd(popuppassword,&AbortUpdate,data) != EFI_SUCCESS)
	{

		AbortUpdate = FALSE;

		if(PopupPasswordCheckInstalled(popuppassword))
		{

            ChangePwd = TRUE ;
            Status = EzportPlusPopupPasswordChangePrompt(popuppassword, STRING_TOKEN(STR_OLD_PSWD), &Text, STRING_TOKEN(STR_NEW_PSWD), &NewPswd,  STRING_TOKEN(STR_CONFIRM_NEW_PSWD), &ConfirmNewPswd) ;   

			if( Status )
				AbortUpdate = TRUE;
			else
			{
				if(!PopupPasswordAuthenticate( popuppassword, Text ))
                {   
					// optional message to user: "wrong password" and  exit                   
					//CallbackShowMessageBox( (UINTN)gInvalidPasswordFailMsgBox, MSGBOX_TYPE_OK );
                    EzportPlusShowPasswordErrorMessageBox();
					AbortUpdate = TRUE;
				}
			}
		}
	}
#if OVERRIDE_PopupPwdAuthenticateIDEPwd && SETUP_IDE_SECURITY_SUPPORT     
    else
    {
        BOOLEAN bCheckUser = FALSE;
        BOOLEAN EnabledBit = FALSE;
        UINTN size = 0;
        IDE_SECURITY_CONFIG *ideSecConfig;
        VOID* DataPtr = TSEIDEPasswordGetDataPtr(gCurrIDESecPage);
        ideSecConfig = VarGetVariable( VARIABLE_ID_IDE_SECURITY, &size );
        
        //EIP-75352 Suppress the warnings from static code analyzer
        if (NULL != ideSecConfig) {
                
            if(ideSecConfig->Enabled) EnabledBit = TRUE;
    
            if(EnabledBit)
            {        
                if(UefiGetQuestionOffset(data) /*data->QuestionId*/ == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword))
                    bCheckUser = TRUE;
        
                if(bCheckUser || ideSecConfig->MasterPasswordStatus)
                {
                   //Status = _DoPopupEdit( *popuppassword, STRING_TOKEN(STR_OLD_PSWD), &Text);
                    ChangePwd = TRUE ;
                    Status = EzportPlusPopupPasswordChangePrompt(popuppassword, STRING_TOKEN(STR_OLD_PSWD), &Text, STRING_TOKEN(STR_NEW_PSWD), &NewPswd,  STRING_TOKEN(STR_CONFIRM_NEW_PSWD), &ConfirmNewPswd) ;
                
                    if(Status )
                    {
                        AbortUpdate = TRUE;
                    }
        			else
        			{
                        Status = TSEIDEPasswordAuthenticate( Text, DataPtr, bCheckUser );
                        if(EFI_ERROR( Status ))
            			{
            				//CallbackShowMessageBox( (UINTN)gInvalidPasswordFailMsgBox, MSGBOX_TYPE_OK );
                            EzportPlusShowPasswordErrorMessageBox();
            				AbortUpdate = TRUE;
            			}
                        else
                        {
                            NewPwLen = EfiStrLen(NewPswd);
                            ConfirmPwLen = EfiStrLen(ConfirmNewPswd);
                           
    				        if(NewPwLen == 0 && ConfirmPwLen == 0) 
    			        	{
    					        ClearPwd = TRUE ; 
    					    }
                        }
        			}
                }
            }
            
            MemFreePointer((VOID **) &ideSecConfig);
        }
    }
#endif

    if(AbortUpdate == FALSE)
	{
Password:

        if(ChangePwd == FALSE)
        {
            Status = EzportPlusPopupPasswordSetPrompt(popuppassword, STRING_TOKEN(STR_NEW_PSWD), &NewPswd,  STRING_TOKEN(STR_CONFIRM_NEW_PSWD), &ConfirmNewPswd) ; 
            
            if(!Status &&  EfiStrLen(NewPswd) == 0)
            {             
                //Report Message box 
                EzportPlusShowPasswordErrorMessageBox(); 
                Status = EFI_UNSUPPORTED;    
            }
        }
		
        if(!Status)
        {
			NewPwLen = EfiStrLen(NewPswd);
            ConfirmPwLen = EfiStrLen(ConfirmNewPswd);    
			//EIP-39764 : non case sensitive support during setting password
			if( IsPasswordSupportNonCaseSensitive() && (NewPwLen != 0)) {
				UpdatePasswordToNonCaseSensitive(NewPswd, NewPwLen);
			}

   			if (VARIABLE_ID_IDE_SECURITY != popuppassword->ControlData.ControlVariable)
			{
    			if(PopupPasswordCheckInstalled(popuppassword))
    			{
    				 // Override the minmax validation for password clearing
    				if(NewPwLen == 0 && ConfirmPwLen == 0) 
    				{
    					//Report Message box for Clearing Old password
    					if(CallbackShowMessageBox( (UINTN)gClearPasswordMsgBox, MSGBOX_TYPE_YESNO )!= MSGBOX_YES)
    					{
    						ChangePwd = FALSE ;
                            ClearPwd = FALSE ; 
                            goto Password;
    						//Status = EFI_UNSUPPORTED; //Do not clear the password
    					} 
    					else 
    					{
    						ClearPwd = TRUE ; 
    					}
    				}
    			}
            }else if( (NewPwLen < (UINT8)UefiGetMinValue(popuppassword->ControlData.ControlPtr)) ||
				(NewPwLen > (UINT8)UefiGetMaxValue(popuppassword->ControlData.ControlPtr))
				)
            {
                //Report Message box
                EzportPlusShowPasswordErrorMessageBox();

                Status = EFI_UNSUPPORTED;
            }
            
            if( ClearPwd == TRUE)
            {
                if(ConfirmNewPswd)
                    StringZeroFreeMemory ((VOID **)&ConfirmNewPswd);

                ConfirmNewPswd = EfiLibAllocateZeroPool( sizeof(CHAR16) );
                    						
    			if(ConfirmNewPswd) 
    			{
    				*ConfirmNewPswd = '\0'; //Set confirmation password to null string
    			} 
    			else 
    			{
    				Status = EFI_OUT_OF_RESOURCES;
    			}

            }
        }

		if ( !Status )
		{
			//EIP-39764 : non case sensitive support during setting password
			if( IsPasswordSupportNonCaseSensitive() && EfiStrLen(ConfirmNewPswd)) {
				NewPwLen = EfiStrLen(ConfirmNewPswd);
				UpdatePasswordToNonCaseSensitive( ConfirmNewPswd, NewPwLen );
			}
		    if ( EfiStrCmp(NewPswd, ConfirmNewPswd)==0 ) 
		    {
				//EIP-75521 Support for Interactive Password control
				if(popuppassword->Text != NULL){
					MemFreePointer( (VOID **)&popuppassword->Text );
				}
				popuppassword->Text = (CHAR16 *) EfiLibAllocateZeroPool((NewPwLen + 1) * sizeof(CHAR16));
				EfiStrCpy(popuppassword->Text, NewPswd);

				//save new password
                if ( ( popuppassword->Callback != NULL ) && ( popuppassword->Cookie != NULL ) )
				{
                    VOID *ifrData = popuppassword->ControlData.ControlPtr;
					CALLBACK_PASSWORD *callbackData = (CALLBACK_PASSWORD *)popuppassword->Cookie;

					callbackData->Variable = popuppassword->ControlData.ControlVariable;
					callbackData->Offset = UefiGetQuestionOffset(ifrData);
					callbackData->Length = (UINT8)UefiGetMaxValue(ifrData) * sizeof(CHAR16);
					callbackData->Data = (VOID *)NewPswd;
					UefiPreControlUpdate(&(popuppassword->ControlData));
					popuppassword->Callback( popuppassword->Container,popuppassword, popuppassword->Cookie );

					PopupPwdUpdateIDEPwd ();
				}


				//For interactive control invoke the formcallback function.
				if(UefiIsInteractive(&popuppassword->ControlData))
				{
					VOID *Handle = popuppassword->ControlData.ControlHandle;
					UINT16 Key = UefiGetControlKey(&(popuppassword->ControlData));
					CONTROL_DATA *Control = (CONTROL_DATA *)NULL;

					//Call the callback passing the input value and value size.
					Status = CallFormCallBack( &(popuppassword->ControlData),Key,0,AMI_CALLBACK_CONTROL_UPDATE);

					Control = GetUpdatedControlData((CONTROL_DATA*)popuppassword, CONTROL_TYPE_PASSWORD, Handle, Key);
					if(Control == NULL){ //Control deleted.
						return EFI_SUCCESS;
					}
					if(Control != (CONTROL_DATA *)popuppassword){
						popuppassword = (POPUP_PASSWORD_DATA *)Control; //Control Updated.
					}
				}

				popuppassword->ControlActive = FALSE;
                
                if(ClearPwd)
                {
                    EzportPlusShowPasswordClearedMessageBox();
                }
                else if(NewPwLen != 0)
                {
                    EzportPlusShowPasswordSuccessMessageBox();
                }
            }
			else
            {
			    EzportPlusShowPasswordErrorMessageBox();
            }
	    }
	}

	StringZeroFreeMemory ((VOID **)&Text);		//EIP67735 zeroing the password prompt memories
	StringZeroFreeMemory ((VOID **)&NewPswd);
	StringZeroFreeMemory ((VOID **)&ConfirmNewPswd);

	TSEStringReadLoopExitHook();//EIP-79958 Exit softkeyboard on pressing ESC
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_EzportPlusPopupPasswordHandleAction
//
// Description:	function to handle the password actions
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, , ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _EzportPlusPopupPasswordHandleAction( POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	   return Status;
	

	if ( Data->Input.Type == ACTION_TYPE_KEY )
    {
        CONTROL_ACTION Action;

        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);

        if(ControlActionSelect == Action)
        {
			if(UefiIsInteractive(&popuppassword->ControlData))
				if(PopupPasswordFormCallback(&(popuppassword->ControlData),UefiGetControlKey(&(popuppassword->ControlData)),0) == EFI_SUCCESS)
					return EFI_SUCCESS;

            return _EzportPlusPopupPasswordActivate(popuppassword);
        }
    }

    if(Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		if(ControlActionSelect == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
		{
			if( popuppassword->Top == (Data->Input.Data.MouseInfo.Top) )
	        {
				if(UefiIsInteractive(&popuppassword->ControlData))
					if(PopupPasswordFormCallback(&(popuppassword->ControlData),UefiGetControlKey(&(popuppassword->ControlData)),0) == EFI_SUCCESS)
						return EFI_SUCCESS;

	                return _EzportPlusPopupPasswordActivate(popuppassword);
	        }
		}
	}
	return Status;
}
#endif


#if OVERRIDE_PopupPwdAuthenticateIDEPwd

EFI_STATUS PopupPwdAuthenticateIDEPwd(POPUP_PASSWORD_DATA *popuppassword, BOOLEAN *AbortUpdate,VOID *data)
{
#if SETUP_IDE_SECURITY_SUPPORT
	EFI_STATUS Status = EFI_UNSUPPORTED;
    CHAR16 *Text=NULL;
	if(popuppassword->ControlData.ControlVariable == VARIABLE_ID_IDE_SECURITY ) 
	{
		//if drive is locked ask for the old password to unlock the drive
		VOID* DataPtr = TSEIDEPasswordGetDataPtr(gCurrIDESecPage);
        BOOLEAN bCheckUser = FALSE;
        BOOLEAN EnabledBit = FALSE;
        UINTN size = 0;
        IDE_SECURITY_CONFIG *ideSecConfig;

        ideSecConfig = VarGetVariable( VARIABLE_ID_IDE_SECURITY, &size );
        
        //EIP-75352 Suppress the warnings from static code analyzer
        if (NULL == ideSecConfig) 
            return EFI_NOT_FOUND;
        
        if(ideSecConfig->Enabled) EnabledBit = TRUE;

        if(EnabledBit)
        {
             return EFI_SUCCESS;
 		}

        MemFreePointer((VOID **) &ideSecConfig);
		return EFI_SUCCESS;
	}
	return EFI_UNSUPPORTED;
#else
    return EFI_UNSUPPORTED;
#endif
}
#endif
//EIP:74899 END
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
