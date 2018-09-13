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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Legacy/legacy.c $
//
// $Author: Premkumara $
//
// $Revision: 10 $
//
// $Date: 8/28/14 11:19a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Legacy/legacy.c $
// 
// 10    8/28/14 11:19a Premkumara
// [TAG] 			EIP174031
// [Category] 		Improvement
// [Description] 	Removed TODO comments and added proper comments in those
// places
// [Files] 			commonoem.c, commonhelper.c, special.c, submenu.c,
// minisetupext.c, uefi21wapper.c and legacy.c
// 
// 9     2/11/13 6:01a Premkumara
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
// 8     10/18/12 6:06a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:42p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     12/01/11 5:40a Rajashakerg
// [TAG]  		EIP74963 
// [Category]  	Improvement
// [Description]  	MAX_MSGBOX_WIDTH cannot be overridden
// [Files]  		AMITSE.sdl, CommonHelper.c, minisetup.h, legacy.c,
// MessageBox.c, MessageBox.h, FormBrowser.c
// 
// 6     11/21/11 10:39a Premkumara
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
// 5     11/14/11 6:55p Blaines
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
// 4     6/29/11 12:43p Rajashakerg
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
// 3     6/23/11 3:49p Rajashakerg
// [TAG]  		EIP55762, 58925, 59971
// [Category]  	New Feature
// [Description]  	Support REF2,REF3 and REF4 in AMITSE
// Support direct form navigation path
// Improper layout of controls in the root page when Dynamic pages are
// added using the Legacy Setup Style	
// 
// [Files]  		setupdata.h, CommonHelper.c, AMITSE.sdl, Legacy\Legacy.c,
// Legacy\style.h, Legacy\style.h, frame.c, minisetupext.c,
// minisetupext.h, numeric.c, page.c Popupstring.c, Hii.c,
// Uefi21Wrapper.c, Parse.c Hii.c
// 
// 2     3/29/11 12:13a Madhans
// [TAG]  		EIP54968
// [Category]  	Improvement
// [Description]  	To Support different style modules in TSE generically
// [Files]  		Ezport module updated. EzportPlus and Legacy Styles Modules
// added.
// 
// 1     3/28/11 11:51p Madhans
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
// 12    6/14/10 7:07p Madhans
// to avoid warnings
// 
// 11    3/26/10 6:52p Madhans
// Support to Map the do the Control Mapping from gTseControlMap Table. So
// no changes need in Frame.c, With this feature gTseControlMap Can be
// customized to add/customize the TSE controls.
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
// Name:		alternate1.c
//
// Description:	Main file for alternate1 style module.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "minisetup.h"
#include "Legacy.h"

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

BOOLEAN   gotoExitOnEscKey(EFI_GUID *exitFormGuid, UINT16 *pageClass, UINT16 *pageSubclass, UINT16 *pageFormID);//EIP-112628 GotoExitPageOnEscKey

#if SETUP_STYLE_LEGACY

static FRAME_INFO _gStyleLegacyMainFrames[] =
{
//	{FrameType		Drawable	Border, BorderType, Width, Height, Top, Left, FGColor, BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE, 0, 80, 1, 0, 0, TITLE_FGCOLOR, TITLE_BGCOLOR },			// Title
	{ MAIN_FRAME,		TRUE,		FALSE, 0, 78, 15, 2, 1, PAGE_FGCOLOR, PAGE_BGCOLOR },			// Main
	{ HELP_FRAME,		TRUE,		FALSE, 0, 76, 1, 21, 1, HELP_FGCOLOR, PAGE_BGCOLOR },			// Help text
	{ NAV_FRAME,		TRUE,		FALSE, 0, 76, 2, 18, 2, NAV_FGCOLOR, PAGE_BGCOLOR }			// Navigation
};

static FRAME_INFO _gStyleLegacySubFrames[] =
{
//	{ FrameType		Drawable	Border, BorderType, Width, Height, Top, Left, FGColor, BGColor }	
	
	{ TITLE_FRAME,		TRUE,		FALSE, 0, 80,  1,  0, 0,  TITLE_FGCOLOR, TITLE_BGCOLOR},		// Title
    	{ SUBTITLE_FRAME,	TRUE,		FALSE, 0, 80,  1,  1, 0,  MENU_FGCOLOR, MENU_BGCOLOR },		// Subtitle
	{ MAIN_FRAME,		TRUE,		FALSE, 0, 50, 19,  3, 1,  PAGE_FGCOLOR, PAGE_BGCOLOR },		// Main
	{ HELPTITLE_FRAME,	TRUE,		FALSE, 0, 23,  1,  3, 56, HELPTITLE_FGCOLOR, PAGE_BGCOLOR },	// Help title
	{ HELP_FRAME,		TRUE,		FALSE, 0, 23, 16,  5, 56, HELP_FGCOLOR, PAGE_BGCOLOR },		// Help text
	{ NAV_FRAME,		TRUE,		FALSE, 0, 80,  2, 22, 0,  NAV_FGCOLOR, PAGE_BGCOLOR },		// Navigation
};

#if SETUP_STYLE_FULL_SCREEN
static FRAME_INFO _gStyleLegacyFullMainFrames[] =
{
//	{FrameType			Drawable		Border, BorderType, Width, Height, Top, Left, FGColor, BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE, 0, 100, 1, 0, 0, TITLE_FGCOLOR, TITLE_BGCOLOR },			// Title
	{ MAIN_FRAME,		TRUE,		FALSE, 0, 98, 19, 2, 1, PAGE_FGCOLOR, PAGE_BGCOLOR },			// Main
	{ HELP_FRAME,		TRUE,		FALSE, 0, 95, 1, 28, 1, HELP_FGCOLOR, PAGE_BGCOLOR },			// Help text
	{ NAV_FRAME,		TRUE,		FALSE, 0, 95, 2, 25, 2, NAV_FGCOLOR, PAGE_BGCOLOR }			// Navigation
};

static FRAME_INFO _gStyleLegacyFullSubFrames[] =
{
//	{ FrameType		Drawable	Border, BorderType, Width, Height, Top, Left, FGColor, BGColor }	
	{ TITLE_FRAME,		TRUE,		FALSE, 0, 100,  1,  0,  0,  TITLE_FGCOLOR, TITLE_BGCOLOR},		// Title
    { SUBTITLE_FRAME,	TRUE,		FALSE, 0, 100,  1,  1,  0,  MENU_FGCOLOR, MENU_BGCOLOR },		// Subtitle
	{ MAIN_FRAME,		TRUE,		FALSE, 0,  63, 25,  3,  1,  PAGE_FGCOLOR, PAGE_BGCOLOR },		// Main
	{ HELPTITLE_FRAME,	TRUE,		FALSE, 0,  29,  1,  3, 70,  HELPTITLE_FGCOLOR, PAGE_BGCOLOR },	// Help title
	{ HELP_FRAME,		TRUE,		FALSE, 0,  29, 21,  5, 70,  HELP_FGCOLOR, PAGE_BGCOLOR },		// Help text
	{ NAV_FRAME,		TRUE,		FALSE, 0, 100,  2, 29,  0,  NAV_FGCOLOR, PAGE_BGCOLOR },		// Navigation
};
#endif

FRAME_INFO *_gStyleMainFrames = _gStyleLegacyMainFrames ;
FRAME_INFO *_gStyleSubFrames = _gStyleLegacySubFrames ;

INT16 gTabIndex = 0 ;

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



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacyPageHandleAction
//
// Description:	function to handle the page actions
//
// Input:	PAGE_DATA *page, ACTION_DATA *action
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LegacyPageHandleAction( PAGE_DATA *page, ACTION_DATA *action )
{
	UINT32	i;
    EFI_STATUS Status = EFI_UNSUPPORTED;

//EIP# 58925
    UINT32 stackIndex = 0xFFFFFFFF;
    UINT16 parentPgID = 0;
//EIP# 58925
	// On printScreen HotKey, Just return Unsupported and It will handed by Application Hotkey Handler.
	if( ( action->Input.Type == ACTION_TYPE_KEY ) &&
		(TsePrintScreenEventSupport(action->Input.Data.AmiKey.Key.ScanCode) ) ) 
	{
		Status = EFI_UNSUPPORTED;
		goto DONE;
        
	}
/*
#if TSE_PRN_SCRN_EVENT_SUPPORT
	if (( action->Input.Type == ACTION_TYPE_KEY ) && ( action->Input.Data.AmiKey.Key.ScanCode == TSE_PRN_SCRN_KEY_SCAN ))
            return EFI_UNSUPPORTED;
#endif
*/
	for ( i = 0; i < page->FrameCount; i++ )
	{
		if ( gFrame.HandleAction( page->FrameList[StyleFrameIndexOf(i)], action ) == EFI_SUCCESS )
		{	
            Status = EFI_SUCCESS;
		    goto DONE;
        }
	}

	for ( i = 0; i < page->HotKeyCount; i++ )
	{
		if ( gHotKey.HandleAction( page->HotKeyList[i], action ) == EFI_SUCCESS )
        {
			Status = EFI_SUCCESS;
		    goto DONE;
        }
	}

	if(
        (( action->Input.Type == ACTION_TYPE_KEY ) && (ControlActionAbort == MapControlKeysHook(action->Input.Data.AmiKey)))
        || ((action->Input.Type == ACTION_TYPE_MOUSE) && (ControlActionAbort == MapControlMouseActionHook(&(action->Input.Data.MouseInfo))) /*(TSEMOUSE_RIGHT_CLICK == action->Input.Data.MouseInfo.ButtonStatus)*/)
      )
	{
	
	//Commented for Legacy Style 07/07/10
	//if ( page->PageData.PageParentID == 0 )
        //    return EFI_UNSUPPORTED;

        
        if ( page->PageData.PageID != page->PageData.PageParentID )
        {
            // check for inconsistency here too.
            if (CheckInconsistence((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[page->PageData.PageID]))!= TRUE )
            {
                // reset focus to first control
                FRAME_DATA *frame = page->FrameList[StyleFrameIndexOf(MAIN_FRAME)];
                UINT32 i;

                for ( i = 0; i < frame->ControlCount; i++ )
                {
                    if ( _FrameSetControlFocus( frame, i ) )
                    {
                        frame->FirstVisibleCtrl = 0;
                        break;
                    }
                }
//EIP# 58925
                if(IsLinkHistorySupport())
                {
                    // tell application that we need to change pages
                    Status = GetParentFormID((UINT16)gApp->CurrentPage, &parentPgID, &stackIndex); //Gets the parent page of the current page
    				if(Status != EFI_SUCCESS)
    					gApp->CurrentPage = page->PageData.PageParentID;
    				 else
                        gApp->CurrentPage = parentPgID; //Else set the current page to the parent page
                }
                else
                {
                    gApp->CurrentPage = page->PageData.PageParentID;
                }
//EIP# 58925
                gApp->CompleteRedraw = TRUE;
				gApp->OnRedraw = SUBMENU_COMPLETE_REDRAW;
            }

            Status = EFI_SUCCESS;
        }
    }
DONE:
//EIP# 58925   
    if(IsLinkHistorySupport())
    {
        if(Status == EFI_SUCCESS){
       		SetParentFormID(page->PageData.PageID, (UINT16)gApp->CurrentPage);
    	}
    }
//EIP# 58925
    return Status ;
    
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    LegacyFrameAddControl
//
// Description: Adds controls to the frame 
//
// Input:		FRAME_DATA *frame - Pointer to the frame data
//				CONTROL_INFO *controlData - Control date to be added
//
// Output:		EFI_STATUS Status - EFI_SUCCESS if successful, else
//										EFI_UNSUPPORTED
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LegacyFrameAddControl( FRAME_DATA *frame, CONTROL_INFO *controlData )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	CONTROL_DATA **control;
	POSITION_INFO *pos;
	UINT16 count = (UINT16)frame->ControlCount;
	UINT16 i;
	BOOLEAN		IsValidControl = FALSE;
	PAGE_INFO *pageInfo=NULL;

	gActiveFrame = frame;


	if(controlData->ControlType == CONTROL_TYPE_SUBMENU)
	{
		pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[controlData->ControlDestPageID]);
		
		if(pageInfo->PageHandle == NULL)
		{
			frame->NullCount--;
			return EFI_OUT_OF_RESOURCES;
		}
	}
		
	control = MemReallocateZeroPool( frame->ControlList, count * sizeof(CONTROL_INFO *), (count + 1) * sizeof(CONTROL_INFO *) );

	if ( control == NULL )
		return EFI_OUT_OF_RESOURCES;

	frame->ControlList = control;
	control = &frame->ControlList[ count ];

	for(i=0;gTseControlMap[i].ControlType != CONTROL_TYPE_NULL;i++)
	{
		if(gTseControlMap[i].ControlType == controlData->ControlType)
		{
			Status = gTseControlMap[i].ControlMethods->Create(control);
			if ( ! EFI_ERROR(Status) )
			{
				if(gTseControlMap[i].CallbackSuppored )
					gTseControlMap[i].ControlMethods->SetCallback(*control, frame, 
							(OBJECT_CALLBACK)(UINTN)gTseControlMap[i].CallbackFunction, 
							(VOID*)gTseControlMap[i].CallbackContext);
			}
			IsValidControl = TRUE;
		}
	}

	if(!IsValidControl)
	{
		if(controlData->ControlType == CONTROL_TYPE_NULL )
			frame->NullCount++;
		return Status;
	}
	
	if ( ! EFI_ERROR( Status ) )
	{
		Status = (*control)->Methods->Initialize( *control, controlData );

		if ( ! EFI_ERROR( Status ) )
		{
            UINT16 height = 1;
			//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
			if(IsTSEMultilineControlSupported())
			{
				Status = (*control)->Methods->GetControlHeight( *control, (VOID*)frame,&height);
	   			height = height ? height:1;
			}

			if(frame->FrameData.FrameType == SUBTITLE_FRAME)
				(*control)->Methods->SetDimensions( *control, frame->FrameData.Width , height );
			else
				(*control)->Methods->SetDimensions( *control, frame->FrameData.Width - (UINT8)gLabelLeftMargin - 2 , height );

			(*control)->ParentFrameType = frame->FrameData.FrameType ;

			frame->ControlCount++;
			count++;

			(*control)->Methods->SetPosition( *control, frame->FrameData.Left + (UINT8)gLabelLeftMargin, frame->FrameData.Top + count -1 );

		 	
		 	if( EFI_ERROR( StyleHandleControlOverflow( frame, frame->ControlList[ count -1 ], (UINT16)frame->ControlCount )) )
			{
				frame->LastVisibleCtrl = frame->ControlCount-1;
			}

			// set position information
			pos = MemReallocateZeroPool( frame->OrigPosition, (count-1) * sizeof(POSITION_INFO), (count ) * sizeof(POSITION_INFO) );
			if ( pos != NULL )
			{
				pos[count-1].Left = (*control)->Left;
				pos[count-1].Top = (*control)->Top;
				frame->OrigPosition = pos;
			}

			MemFreePointer( (VOID **)&frame->CurrPosition );
			frame->CurrPosition = EfiLibAllocateZeroPool( count * sizeof(POSITION_INFO) );
			
		}

	}
	return Status;
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:		 LegacyFrameDrawScrollBar
//
// Description:  Draws the scrollbar controls for the frame..
//
// Input:		FRAME_DATA *frame	- Pointer to the current frame
//				UINT32	FirstLine	- FirstLine of the scrollbar
//				UINT32 LastLine		- LastLine	 
//				UINT32	modVal		- modVal 
//				UINT32	sizeOfBar	- Size of the Scrollbar
//				UINT32 numOfBlocks	- Number of blocks 
//				BOOLEAN bEraseScrollBar	- flag to erase the scrollbar
//
// Output: EFI_STATUS status - 
//					EFI_SUCCESS - If there exists a next page and the 
//								   function successfully loads it				
//					EFI_OUT_PF_RESOURCES - If there are know previous page
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LegacyFrameDrawScrollBar (FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32 modVal, UINT32	sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar)
{
	UINT32	i, j ; //,FirstLine=0,LastLine=0, count,visibleControlCount = 0, modVal=0, sizeOfBar, numOfBlocks = 0;
	CHAR16	ArrUp[2]={{GEOMETRICSHAPE_UP_TRIANGLE},{0x0000}},ArrDown[2]={{GEOMETRICSHAPE_DOWN_TRIANGLE},{0x0000}},ScrlSel[2]={{BLOCKELEMENT_FULL_BLOCK/*L'N'*/},{0x0000}},ScrlNSel[2]={{BLOCKELEMENT_LIGHT_SHADE/*L'S'*/},{0x0000}};


	// draw scrollbar if necessary
	if ( frame->BlankLine != NULL )
	{
		j = frame->FrameData.Top;
		for ( i = 1; i < frame->FrameData.Height; i++, j++ )
		{
            // use this loop to draw the scrollbar
		    if(frame->UseScrollbar)
		    {
				if(i==1)
					DrawStringWithAttribute( frame->FrameData.Left + frame->FrameData.Width+2 , j, ArrUp, 
				                            StyleGetScrollBarUpArrowColor() );
				else if(i==(UINT16)(frame->FrameData.Height - 1))
					DrawStringWithAttribute( frame->FrameData.Left+ frame->FrameData.Width+2, j, ArrDown, 
					                             StyleGetScrollBarDownArrowColor() );
				else
				{
					if( (j > FirstLine) && (j < LastLine) &&  ((sizeOfBar + modVal) != 0))
					{	
						DrawStringWithAttribute( frame->FrameData.Left+ frame->FrameData.Width+2, j, ScrlSel, 
													StyleGetScrollBarColor() );
						sizeOfBar--;
					}
					else
					{
						DrawStringWithAttribute( frame->FrameData.Left+ frame->FrameData.Width+2, j, ScrlNSel, 
							                         StyleGetScrollBarColor() ); 
					}
				}
			}
			else if (bEraseScrollBar == TRUE)
				DrawStringWithAttribute( frame->FrameData.Left+ frame->FrameData.Width+2, j, L" ", 
					                         StyleGetScrollBarColor() ); 

		}
		bEraseScrollBar = FALSE;
	}
			

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:		LegacyFrameDraw
//
// Description: Draws the controls for the given frame 
//
// Input:       FRAME_DATA *frame - Frame information to draw controls
//
// Output:		EFI_STATUS - EFI_SUCCESS if successful, else EFI_ERROR
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LegacyFrameDraw( FRAME_DATA *frame )
{
	CONTROL_DATA **control;
	UINT32	i, j,FirstLine=0,LastLine=0, count,visibleControlCount = 0, modVal=0, sizeOfBar, numOfBlocks = 0;
	UINT16 CurrHeight, ControlTop;
    	UINT8 u8ChkResult;
	EFI_STATUS Status = EFI_UNSUPPORTED;

    	BOOLEAN bCurrNotFocused = FALSE,bEraseScrollBar=FALSE;

	if((frame->FrameData.FrameType != MAIN_FRAME) || ( frame->PageID != 0 ))
    	{
        Status = FrameDraw(frame );
        return Status;
    	}


	if(StyleFrameDrawable(frame)) 
		return EFI_UNSUPPORTED;
	
	if ( frame->ControlCount == 0 )
		return EFI_UNSUPPORTED;

    //If there is an active control send draw only for that
   	if(frame->CurrentControl == FRAME_NONE_FOCUSED)
	{
		control = NULL;
		bCurrNotFocused = TRUE; // Non is focused
	}
	else
		control = &frame->ControlList[frame->CurrentControl];

	if ( control != NULL )
	{
        //If a control is active only draw that
		if( (*control)->ControlActive == TRUE )
		{
			(*control)->Methods->Draw( *control );
			return EFI_SUCCESS;
		}
		
		if(COND_NONE == CheckControlCondition( &((*control)->ControlData) ))
		{
			// Set the Focus to current control
			if((*control)->Methods->SetFocus(*control,TRUE) !=  EFI_SUCCESS)
			{
				frame->CurrentControl = FRAME_NONE_FOCUSED;
				bCurrNotFocused = TRUE; // Non is focused
			}
		}
	}

    //There is no active control we have to draw all in the view.

   	// First, clear the frame.
	if ( frame->BlankLine != NULL )
	{
		j = frame->FrameData.Top;
		for ( i = 1; i < frame->FrameData.Height; i++, j++ )
		{
			DrawStringWithAttribute( frame->FrameData.Left, j, frame->BlankLine, frame->FrameData.FGColor | frame->FrameData.BGColor );
		}
	}

	//Set position for all controls begining from FirstVisibleControl.
    //In the process calculate the correct LastVisibleControl.
    control = frame->ControlList;

    control = control+ frame->FirstVisibleCtrl;
    CurrHeight = frame->FrameData.Top;
    frame->LastVisibleCtrl = frame->FirstVisibleCtrl;

	for ( i = frame->FirstVisibleCtrl; i < frame->ControlCount; i++, control++ )
	{
        ControlTop = CurrHeight;

        //Check conditional
        u8ChkResult = CheckControlCondition( &((*control)->ControlData) );

        if(u8ChkResult == COND_NONE || u8ChkResult == COND_GRAYOUT)
        {
            //Control is drawn increament height
            CurrHeight = CurrHeight + (*control)->Height;
            if((frame->ControlCount > 1) && ((frame->FrameData.Top +frame->FrameData.Height) < CurrHeight+1 ))
            {
                break;
            }
            else
            {
                frame->LastVisibleCtrl = i;
            }
        }

        if(u8ChkResult != COND_NONE)
        {
            //Control grayed out or suppressed
            if(frame->CurrentControl == i)
            {
                //Current control cant be focused
                (*control)->Methods->SetFocus(*control,FALSE);
                bCurrNotFocused = TRUE;
            }
        }

        //(*control)->Methods->SetPosition( *control, (*control)->Left, ControlTop);
    }

    //Current control can not be focused? Find another one to focus.
    if(bCurrNotFocused)
    {
        control = frame->ControlList;
        control = control+ frame->FirstVisibleCtrl;

        for ( i = frame->FirstVisibleCtrl; i <= frame->LastVisibleCtrl; i++, control++ )
        {
            if ( (*control)->Methods->SetFocus( *control, TRUE ) == EFI_SUCCESS )
            {
                frame->CurrentControl = i;
                break;
            }
        }

        if(i > frame->LastVisibleCtrl)
            frame->CurrentControl = FRAME_NONE_FOCUSED;
    }

	//Draw controls in the set positions
    control = frame->ControlList;
    control = control+ frame->FirstVisibleCtrl;
    for ( i = frame->FirstVisibleCtrl; i <= frame->LastVisibleCtrl; i++, control++ )
    {
        (*control)->Methods->Draw( *control );
    }

    CurrHeight = frame->FrameData.Top;
	for (count = 0; count < frame->ControlCount; count++)
	{
		u8ChkResult = COND_NONE;

		//EIP 75486 Support grayout condition for readonly controls
        u8ChkResult = CheckControlCondition( &(frame->ControlList[count]->ControlData) );
        
        if((COND_NONE == u8ChkResult) || (COND_GRAYOUT == u8ChkResult))
        {
			visibleControlCount++ ; 
            CurrHeight = CurrHeight + frame->ControlList[count]->Height;
	    }
	}

	// if already have a Scroll bar and due some changes (some controls may bedisabled) we don't need a scroll bar in this frame.
	if((frame->UseScrollbar) && ((frame->FrameData.Top + frame->FrameData.Height) >= CurrHeight+1))
	{
		bEraseScrollBar = TRUE;
		frame->UseScrollbar = FALSE;
	}

	// if we don't have a Scroll bar and due some changes (some controls may be enabled) we  need a scroll bar in this frame.
	if((frame->ControlCount > 1) && (!frame->UseScrollbar) && ((frame->FrameData.Top + frame->FrameData.Height) < CurrHeight+1))
	{
		frame->UseScrollbar = TRUE;
	}

	if(visibleControlCount==0)visibleControlCount=1;
    	FirstLine = (frame->FrameData.Height* frame->FirstVisibleCtrl/visibleControlCount )+ frame->FrameData.Top;
	LastLine  = (frame->FrameData.Height* frame->LastVisibleCtrl/visibleControlCount )+ frame->FrameData.Top;

	numOfBlocks = frame->FrameData.Height - 2;
	sizeOfBar = ((frame->FrameData.Height -1) * numOfBlocks) / visibleControlCount;
	modVal = ((((frame->FrameData.Height -1) * numOfBlocks) % visibleControlCount)* numOfBlocks) > (numOfBlocks/2) ? 1 : 0;

	// draw scrollbar if necessary
	StyleDrawScrollBar(frame, FirstLine, LastLine, modVal, sizeOfBar, numOfBlocks, bEraseScrollBar);	
			
	FlushLines( frame->FrameData.Top, frame->FrameData.Top + frame->FrameData.Height );

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacyMsgBoxInitialize
//
// Description:	Function to Initialize Message Box, which uses the Popup functions.
//
// Input:	MSGBOX_DATA *msgbox, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LegacyMsgBoxInitialize( MSGBOX_DATA *msgbox, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 Length =0 ;
	VOID *buff;
	CONTROL_INFO MemoCtrlData;
	MEMO_DATA *memo;
	UINT8 Color ;

	UINT16 titleToken;
    	VOID* TextHandle =((AMI_IFR_MSGBOX*)(((CONTROL_INFO*)data)->ControlPtr))->TextHandle;

	// initializes the heigth and width
	Status = gPopup.Initialize( msgbox, data );
	if (EFI_ERROR(Status))
		return Status;

	Status = StyleGetMessageboxColor(msgbox->MsgBoxCatagory, &Color) ; 
	
	if ( EFI_ERROR( Status ) == EFI_SUCCESS)
	{
		msgbox->FGColor = Color & 0x0f ; 
		msgbox->BGColor = Color & 0xf0 ; 
	}else
	// add extra initialization here...
	SetControlColorsHook( NULL, NULL, NULL , NULL, NULL , NULL, NULL ,
	                      NULL , NULL,  NULL,NULL ,
						  NULL,NULL ,&(msgbox->FGColor),&(msgbox->BGColor)  );
	
	msgbox->FGColor = Colors.PopupFGColor ;
	msgbox->BGColor = Colors.PopupBGColor ;

	msgbox->Container = NULL;
	
	msgbox->Border =TRUE;

	titleToken = (UINT16)(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Title);
	if ( titleToken != 0 ) {
		msgbox->Title = HiiGetString(msgbox->ControlData.ControlHandle, titleToken);
		if ( msgbox->Title == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Length = (UINT16)HiiMyGetMultiLineStringLength(msgbox->ControlData.ControlHandle, (UINT16)(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Text));

	if ( ( msgbox->Title != NULL) && ( Length < (TestPrintLength( msgbox->Title )/ (NG_SIZE)) ) )
		Length = (UINT16)(TestPrintLength( msgbox->Title ) / (NG_SIZE));

	msgbox->Width = (UINT16)(Length + 4);

	if(( msgbox->MsgBoxType == MSGBOX_TYPE_NULL ) && ( msgbox->Legend != NULL ))
	{ 
		if ( msgbox->Width < (UINT16)(TestPrintLength( msgbox->Legend )/ (NG_SIZE)) )
			msgbox->Width = (UINT16)(TestPrintLength( msgbox->Legend ) / (NG_SIZE)) + 8;
	}	
//EIP74963 : MAX_MSGBOX_WIDTH macro changed as token and handled from binary
	if ( msgbox->Width > GetMsgboxWidth())
		msgbox->Width = GetMsgboxWidth();

	msgbox->ScreenBuf = SaveScreen();

	// initialize memo control 
	memo = msgbox->Memo;

	buff = UefiCreateSubTitleTemplate(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Text );

	
	MemSet( &MemoCtrlData, sizeof(MemoCtrlData), 0 );
	MemoCtrlData.ControlPtr = (VOID*)buff;
	MemoCtrlData.ControlHandle = TextHandle;
	MemoCtrlData.ControlFlags.ControlVisible = TRUE;
	gMemo.Initialize(memo,(VOID *)&(MemoCtrlData));
	memo->Width = msgbox->Width - 2;
	gMemo.GetControlHeight( memo, NULL, &msgbox->Height );
	msgbox->Height += 4;

	gMemo.SetAttributes(memo,msgbox->FGColor ,msgbox->BGColor);
	gMemo.SetDimensions( memo, msgbox->Width-2 , msgbox->Height-3 );
	gMemo.SetJustify( memo, JUSTIFY_CENTER );

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacySubMenuInitialize
//
// Description:	this function uses the initialize function of control
//					and initializes the submenu.
//
// Input:	SUBMENU_DATA *submenu, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LegacySubMenuInitialize( SUBMENU_DATA *submenu, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	//PAGE_INFO *pageInfo=NULL;
	//PAGE_DATA *Page ;
	
	Status = gControl.Initialize( submenu, data );
	if (EFI_ERROR(Status))
		return Status;

	

	// add extra initialization here...
	submenu->ControlData.ControlHelp = UefiGetHelpField((VOID *)submenu->ControlData.ControlPtr); //refPtr->Help;
	submenu->ControlFocus = FALSE;
	submenu->LabelMargin = (UINT8)gControlLeftMargin;

	// initialize default colors
	SetControlColorsHook(&(submenu->BGColor), &(submenu->FGColor),  
						NULL, NULL,
						&(submenu->SelBGColor), &(submenu->SelFGColor),
			            		&(submenu->NSelBGColor), &(submenu->NSelFGColor),  
						NULL,&(submenu->LabelFGColor) ,
					    	&(submenu->NSelLabelFGColor),
						NULL,NULL,
						NULL,NULL );


	//if((submenu->SubMenuType==0) && (submenu->ControlData.ControlPageID!=0))
	//	submenu->SelFGColor = FOCUS_COLOR ;

	

/*        

	if(submenu->SubMenuType==0)
	{
		Page = gApp->PageList[gApp->CurrentPage];
		
		if(Page->PageData.PageTitle == STRING_TOKEN(STR_EXIT))
		{
			submenu->SelFGColor = FOCUS_COLOR ;

		}
	}
*/        

/*						
	if((submenu->SubMenuType==0) && (submenu->ControlData.ControlPageID!=0))
	{
		pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[submenu->ControlData.ControlPageID]);
		
		if(pageInfo->PageTitle == STRING_TOKEN(STR_EXIT))
		{
			submenu->SelFGColor = FOCUS_COLOR ;

		}
	}	
*/			
	
	

#if SETUP_STYLE_LEGACY
	submenu->SubMenuType = (UINT8)(submenu->ControlData.ControlPageID != 0);
#endif

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacySubMenuDraw
//
// Description:	function to draw a sub-menu.
//
// Input:	SUBMENU_DATA *submenu
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LegacySubMenuDraw( SUBMENU_DATA *submenu )
{
	CHAR16 *text=NULL,*text1;
	UINTN length;
	EFI_STATUS Status = EFI_SUCCESS;
//	UINT8 ColorSubMenu = submenu->NSelFGColor;
	UINT8 ColorLabel = (submenu->ControlFocus) ? submenu->LabelFGColor : submenu->NSelLabelFGColor ;
	UINT32 PageNum ;

	PageNum = gApp->CurrentPage ;

	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( submenu->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &submenu->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorLabel = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	text1 = HiiGetString( submenu->ControlData.ControlHandle,  UefiGetPromptField((VOID *)(submenu->ControlData.ControlPtr)));
	if ( text1 == NULL )
		return EFI_OUT_OF_RESOURCES;
	// XXX check to see if text1 is not NULL
	length = (3 + (TestPrintLength( text1 ) / (NG_SIZE))) * sizeof(CHAR16);
	text = EfiLibAllocateZeroPool( length );
	if ( text == NULL )
		return EFI_OUT_OF_RESOURCES;

	if((submenu->SubMenuType == 0)&&( PageNum == 0 ))
		SPrint( text, length,  L"%s", text1 );
	else if(submenu->SubMenuType == 2)
		SPrint( text, length, L"%s", text1 );
	else
		SPrint( text, length, L"%c %s", GEOMETRICSHAPE_RIGHT_TRIANGLE, text1 );		


	//SPrint( text, length, L"%c %s", (submenu->SubMenuType == 2)?L' ':GEOMETRICSHAPE_RIGHT_TRIANGLE, text1 );

	//SPrint( text, length,  ((submenu->SubMenuType == 0)&&( PageNum == 0 ))?L"%c%s":L"%c %s", ((submenu->SubMenuType == 2)||( PageNum == 0 ))?L' ':GEOMETRICSHAPE_RIGHT_TRIANGLE, text1 );

	//SPrint( text, length,  ((submenu->SubMenuType == 0)&&( PageNum == 0 ))?L"%c%s":L"%c %s", ((submenu->SubMenuType == 2)||( PageNum == 0 ))?L' ':GEOMETRICSHAPE_RIGHT_TRIANGLE, text1 );
	MemFreePointer( (VOID **)&text1 );

	if ( submenu->SubMenuType != 1 )
	{
		//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
		if(submenu->Height>1 && IsTSEMultilineControlSupported())
		{
			DrawMultiLineStringWithAttribute( submenu->Left , submenu->Top, 
					(UINTN)(submenu->Width-2),(UINTN) submenu->Height,
					&text[2], (UINT8)(  (submenu->ControlFocus) ? 
							  submenu->SelBGColor  | ColorLabel /*submenu->SelFGColor*/ :
							  submenu->NSelBGColor | ColorLabel /*ColorSubMenu*/ )  );
			if(submenu->SubMenuType != 2)
			{
				text[2]=0;
				DrawStringWithAttribute( submenu->Left - 2, submenu->Top, (CHAR16*)text, 
						(UINT8)(  (submenu->ControlFocus) ? 
								  submenu->SelBGColor  | ColorLabel /*submenu->SelFGColor*/ :
								  submenu->NSelBGColor | ColorLabel /*ColorSubMenu*/ ) );
			}
		}
		else	
		{
			
			if(submenu->SubMenuType==0 && !submenu->ControlFocus && ColorLabel != CONTROL_GRAYOUT_COLOR)
				ColorLabel = StyleGetPageLinkColor();


            if( PageNum == 0 )
            {
                if((TestPrintLength( text ) / (NG_SIZE)) > (UINTN)((submenu->Width/2)-2))
				    EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)((submenu->Width/2)-5))],L"...");
                
            }else{
						
			
			if((TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(submenu->Width-2))
				EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)(submenu->Width-5))],L"...");

            }
	
			DrawStringWithAttribute( submenu->Left, submenu->Top, (CHAR16*)text, 
					(UINT8)(  (submenu->ControlFocus) ? 
							  submenu->SelBGColor  | submenu->SelFGColor :
							  submenu->NSelBGColor | ColorLabel ) );
		}
	}
	else
	{
		if((TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(submenu->Width-2))
			EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)(submenu->Width-5))],L"...");

		text1 = HiiGetString( gHiiHandle, STRING_TOKEN(STR_SUBMENU_OPTION) );
		if ( text1 != NULL )
		{
			DrawStringWithAttribute( submenu->Left - 2, submenu->Top, (CHAR16*)text, 
					EFI_BACKGROUND_BLUE | EFI_WHITE );
			MemFreePointer( (VOID **)&text );

			length = (3 + (TestPrintLength( text1 ) / (NG_SIZE))) * sizeof(CHAR16);
			text = EfiLibAllocatePool( length );
			if ( text != NULL )
			{
				SPrint( text, length, L"[%s]", text1 );
		
			 	if ((TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(submenu->Width-2))
					EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)(submenu->Width-5))],L"...");

				DrawStringWithAttribute( submenu->Left  + submenu->LabelMargin , submenu->Top, text,
					(UINT8)(  (submenu->ControlFocus) ? 
						  	submenu->SelBGColor  | submenu->SelFGColor :
							submenu->NSelBGColor | submenu->NSelFGColor ) );

				//if ( submenu->ControlFocus )
				//	DrawStringWithAttribute( submenu->Left + submenu->LabelMargin + 1,
				//			submenu->Top, text1, (UINT8)(submenu->SelBGColor | submenu->SelFGColor) );
			}
		}
	}

	MemFreePointer( (VOID **)&text );
	MemFreePointer( (VOID **)&text1 );

	FlushLines( submenu->Top, submenu->Top );

	return Status;
}

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
	VOID *data = NULL ;
	data = (UINT8 *)gApplicationData + gPages->PageList[0] ;

	if( ((PAGE_INFO*)data)->PageHandle == 0)
	       	((PAGE_INFO*)data)->PageHandle = gHiiHandle ;

	
	gLabelLeftMargin = STYLE_LABEL_LEFT_MARGIN ;
	gControlLeftMargin = STYLE_CONTROL_LEFT_MARGIN ;
	gControlLeftPad = STYLE_CONTROL_LEFT_PAD ;
	

	#if SETUP_STYLE_FULL_SCREEN
	if ( gMaxCols == STYLE_FULL_MAX_COLS )
	{
		_gStyleMainFrames = _gStyleLegacyFullMainFrames ;
		_gStyleSubFrames = _gStyleLegacyFullSubFrames ;

		gLabelLeftMargin = FULL_STYLE_LABEL_LEFT_MARGIN ;
		gControlLeftMargin = FULL_STYLE_CONTROL_LEFT_MARGIN ;
		gControlLeftPad = FULL_STYLE_CONTROL_LEFT_PAD ;
	
	}
	#endif


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
	UINT32 i, PageNum ;

	PageNum = gApp->CurrentPage ;


	if ( PageNum == 0 )
		FrameCount = sizeof(_gStyleLegacyMainFrames) / sizeof(FRAME_INFO);
	else
		FrameCount = sizeof(_gStyleLegacySubFrames) / sizeof(FRAME_INFO);


	for ( i = 0; i < FrameCount; i++ )
	{
		if ( PageNum == 0 )
		{
			if( _gStyleMainFrames[i].FrameType == frameType )
			{
				return i ;
				break ;
			}
		}else{

			if( _gStyleSubFrames[i].FrameType == frameType )
			{
				return i ;
				break ;
			}

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
	if ( page == 0 )
		return sizeof(_gStyleLegacyMainFrames) / sizeof(FRAME_INFO);

	return sizeof(_gStyleLegacySubFrames) / sizeof(FRAME_INFO);
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
	CHAR16 *line;
	UINT8 lineNumber;

	UINT8 start, end, col;

	PAGE_DATA *Page=NULL ;
	FRAME_DATA *fHelptitle=NULL, *fHelp=NULL ;

	Page = gApp->PageList[page];
	
	fHelptitle = Page->FrameList[StyleFrameIndexOf(HELPTITLE_FRAME)];
	fHelp = Page->FrameList[StyleFrameIndexOf(HELP_FRAME)];
	




	line = EfiLibAllocateZeroPool( (gMaxCols + 1) * sizeof(CHAR16) );
	if ( line == NULL )
		return;

	ClearScreenWithoutFlush( EFI_BACKGROUND_BLUE | EFI_WHITE );

	MemFillUINT16Buffer( &line[1], gMaxCols - 2, L' ' );
	line[0] = line[gMaxCols - 1] = BOXDRAW_DOUBLE_VERTICAL;

	if ( page == 0 )
	{
		start = 2;
		end = (UINT8)(gMaxRows - 2);
	}
	else
	{
		start = 3;
		end = (UINT8)(gMaxRows - 3);
	}

	for ( lineNumber = start; lineNumber < end; lineNumber++ )
		DrawString( 0, lineNumber, line );

	MemFillUINT16Buffer( &line[1], gMaxCols - 2, BOXDRAW_DOUBLE_HORIZONTAL );
	// top line
	line[0] = BOXDRAW_DOUBLE_DOWN_RIGHT;
	line[gMaxCols - 1] = BOXDRAW_DOUBLE_DOWN_LEFT;
	DrawString( 0, start - 1, line );

	// bottom line
	line[0] = BOXDRAW_DOUBLE_UP_RIGHT;
	line[gMaxCols - 1] = BOXDRAW_DOUBLE_UP_LEFT;
	DrawString( 0, end, line );

	MemFillUINT16Buffer( &line[1], gMaxCols - 2, BOXDRAW_HORIZONTAL );

	if ( page == 0 )
	{
		line[0] = BOXDRAW_VERTICAL_DOUBLE_RIGHT;
		line[gMaxCols - 1] = BOXDRAW_VERTICAL_DOUBLE_LEFT;
		DrawString( 0, gMaxRows - 4, line );
		line[gMaxCols / 2] = BOXDRAW_UP_HORIZONTAL;
		DrawString( 0, gMaxRows - 7, line );

		line[0] = BOXDRAW_DOWN_HORIZONTAL_DOUBLE;
		line[1] = L'\0';
		DrawString( gMaxCols / 2, 1, line );
	}
	else
	{
		// dividing line
		line[0] = BOXDRAW_VERTICAL_RIGHT;
		line[fHelp->FrameData.Width + 2] = BOXDRAW_VERTICAL_DOUBLE_LEFT;
		line[fHelp->FrameData.Width + 3] = L'\0';
		DrawString( fHelp->FrameData.Left - 2, 4, line );
		line[0] = BOXDRAW_DOWN_HORIZONTAL_DOUBLE;
		line[1] = L'\0';
		DrawString( fHelp->FrameData.Left - 2, 2, line );
		line[0] = BOXDRAW_UP_HORIZONTAL_DOUBLE;
		DrawString( fHelp->FrameData.Left - 2, gMaxRows - 3, line );

	}

	// center divider
	line[0] = BOXDRAW_VERTICAL;

	if ( page == 0 )
	{
		start = 2;
		end = (UINT8)(gMaxRows - 7);
		col = (UINT8)(gMaxCols / 2);
	}
	else
	{
		start = 5;
		end = (UINT8)(gMaxRows - 3);
		col = fHelp->FrameData.Left - 2;
	}
	for ( lineNumber = start; lineNumber < end; lineNumber++ )
		DrawString( col, lineNumber, line );

	if ( page != 0 )
		DrawString( fHelp->FrameData.Left - 2, 3, line );

	FlushLines( 0, gMaxRows - 1 );

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
	if ( page == 0 )
				return &_gStyleMainFrames[frame];

	return &_gStyleSubFrames[frame];

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OverRideComponent
//
// Description: Function to override component or control functionality
//
// Input:   VOID
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OverRideComponent(VOID)
{
    gMsgBox.Initialize = LegacyMsgBoxInitialize ;
    gSubMenu.Initialize = LegacySubMenuInitialize ;
    gSubMenu.Draw = LegacySubMenuDraw ;
    gFrame.Draw = LegacyFrameDraw ;    		        // Override framedraw
	gFrame.AddControl = LegacyFrameAddControl ;     // Override FrameAddControl
    gPage.HandleAction = LegacyPageHandleAction ;   // Override FrameAddControl
    
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

#endif /* SETUP_STYLE_LEGACY */

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
VOID LegacyHandleEscKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	UINT16 pageClass = 0, pageSubclass = 0, pageFormID = 0;
	EFI_GUID ExitPageGuid;


	if(FormBrowserHandleValid())
		app->Quit = TRUE;

	else if ( gotoExitOnEscKey (&ExitPageGuid, &pageClass, &pageSubclass, &pageFormID) )//EIP-112628 GotoExitPageOnEscKey
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
VOID LegacyHandleSaveExitKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
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
VOID LegacyHandlePrevValuesKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	//if ( app->CurrentPage != 0 )
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
VOID LegacyHandleFailsafeKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	//if ( app->CurrentPage != 0 )
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
VOID LegacyHandleOptimalKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	//if ( app->CurrentPage != 0 )
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
VOID LegacyHandleHelpKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	//if ( app->CurrentPage != 0 )
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
VOID LegacyHandlePrnScrnKey( APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	TseHotkeyPrintScreenSupport();
}

//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
//EIP:47086 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacyMainFrameHandlewithMouse	
//
// Description:	Function to handle Main Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LegacyMainFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{
	if(app->Action->Input.Data.MouseInfo.ButtonStatus == TSEMOUSE_RIGHT_CLICK)
		app->Quit = ExitApplication();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacyHelpFrameHandlewithMouse	
//
// Description:	Function to handle Help Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LegacyHelpFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{
	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacyNavFrameHandlewithMouse	
//
// Description:	Function to handle Navigation Frame with Mouse
//
// Input:		APPLICATION_DATA *app, HOTCLICK_DATA *hotkey, VOID *cookie 
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LegacyNavFrameHandlewithMouse( APPLICATION_DATA *app, HOTCLICK_DATA *hotclick, VOID *cookie )
{

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
