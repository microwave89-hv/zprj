//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2013, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/page.c $
//
// $Author: Arunsb $
//
// $Revision: 19 $
//
// $Date: 5/02/14 12:40a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/page.c $
// 
// 19    5/02/14 12:40a Arunsb
// [TAG]	EIP150526
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	TSE hangs on disconnecting and connecting the RAID driver
// [Root Cause]	Process pack updated on processing the existing pack
// update
// [Solution]	First we getting remove and new pack. On getting this TSE
// starts processing the pack(ProcessPackNotification) but on processing
// the pack itself we getting notification again for remove and add. So
// again process pack happens inside notification
// itself(IFRChangeNotifyFn), this processing should not happen inside
// notification so enabled flag gEnableProcessPack in PageHandleAction.
// [Files]	hii.c, minisetupext.c and page.c
// 
// 18    2/11/14 8:25p Arunsb
// [TAG]			EIP129750
// [Category]		Improvement
// [Description]	Dynamic pages support in ESA
// [Files]			page.c
// 
// 17    12/03/13 2:13p Premkumara
// [TAG]  		EIP130420
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	String is getting truncated
// [RootCause]  	The string for messagebox, Popup controls is getting
// truncated
// [Solution]  	Used temp variable to store original string and modify the
// string temp and used to avoid changing org string.
// [Files]  		String.c
// 
// 16    7/01/13 9:57a Premkumara
// [TAG]  		EIP126876 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Printscreen is not captured in H/W Monitor page
// [RootCause]  	TSE is trying to create new file with page title name
// after taking print screen. If page title has special character then
// file will not create with any of these character so returning
// FileHandle as NULL
// [Solution]  	If page title has any of these character then it will be
// replace wit hypen character
// [Files]  		Page.c
// 
// 15    5/15/13 4:44a Premkumara
// [TAG]  		EIP23310
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Memory leak
// [RootCause]  	Memory is not freed after taking printscreen buffer
// [Solution]  	Freed memory for BmpBuffer variable after taking
// printscreen buffer
// [Files]  		Page.c
// 
// 14    4/18/13 9:25a Arunsb
// Wrapper function introduce to avoid build error in 2.0
// 
// 13    3/29/13 12:24p Premkumara
// [TAG]  		EIP97611
// [Category]  	New Feature
// [Description]  	PrintScreen Support in TSE
// [Files]  		AMITSE.sdl, CommonHelper.c, HotKeyBin.h, AddBootOption.c,
// Page.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 12    3/14/13 11:46a Premkumara
// [TAG]  		EIP85745 & 109814 
// [Category]  	Improvement
// [Description]  	Support for Modal Form Support as per UEFI 2.3.1
// [Files]  		Parse.c, Page.c, Menu.c, Hotclick.c
// 
// 11    10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 10    12/07/11 3:34p Arunsb
// [TAG]  		EIP75588
// [Category]  	New Feature
// [Description]  	Support for queuing UpdatePack notifications
// [Files]  		frame.c, page.c, formbrowser2.c, hii.c, hiicallback.c,
// hiinotificationhandler.c, tseuefihii.h and uefi21wapper.c
// 
// 9     11/20/11 8:05a Rajashakerg
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
// 8     6/23/11 3:53p Rajashakerg
// [TAG]  		EIP55762, 58925, 59971
// [Category]  	New Feature
// [Description]  	
// Support REF2,REF3 and REF4 in AMITSE
// Support direct form navigation path
// Improper layout of controls in the root page when Dynamic pages are
// added using the Legacy Setup Style	
// 
// [Files]  		setupdata.h, CommonHelper.c, AMITSE.sdl, Legacy\Legacy.c,
// Legacy\style.h, Legacy\style.h, frame.c, minisetupext.c,
// minisetupext.h, numeric.c, page.c Popupstring.c, Hii.c,
// Uefi21Wrapper.c, Parse.c Hii.c
// 
// 7     3/01/11 1:56p Blaines
// Removes Engineer's name [Blaines] from commented code.
// 
// 6     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 8     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 7     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 6     2/01/10 7:38p Madhans
// EIP 32501 : Fix to handle the Conditional control Focusing , in the Sub
// form
// 
// 5     1/09/10 6:27a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     11/09/09 4:44a Mallikarjunanv
// Eip-30111 : fixed the issue to update the help if
// STYLE_PAGE_FIRSTITEM_FOCUS token enabled.
// 
// 3     6/23/09 6:52p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:05p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
// 25    9/17/08 7:44p Madhans
// For Boot only Driver file split changes.
// 
// 24    8/11/08 7:04p Madhans
// TSE_PRN_SCRN_EVENT_SUPPORT SDL token created.
// 
// 23    7/30/08 5:52p Madhans
// To handle the printscreen hotkey event.
// 
// 22    3/19/08 4:00p Madhans
// Shift Tab Support for Date and Time, MapControlKeys takes
// AMI_EFI_KEY_DATA.
// 
// 21    10/24/07 11:23a Arunkumars
// - Moved IDE security code to binary
// - Fixed build errors under UGA draw support
// - Added EFI key password support
// - Added modifier hot key support
// - Added popup support in From browser protocol
// 
// 20    7/09/07 1:27p Arunkumars
// - Added elink hooks for Logo, Password management and Control Keys
// customizations
// 
// 19    5/07/07 8:46a Arunkumars
// - Mouse input support
// - Message box protocol to display message boxes
// 
// 18    4/02/07 4:50p Arunkumars
// - When a control is active Issue draw only to the frame in which the
// control is present
// 
// 17    6/16/06 3:40p Madhans
// 64 Bit Support. Set SDL token TSE_FOR_64BIT for 64 bit support.
// 
// 16    5/02/06 7:38a Arunkumars
// Fix for alignment of the controls
// 
// 15    4/27/06 9:59a Arunkumars
// Fix to scroll to unfocusable views
// 
// 14    2/14/06 1:02p Arunkumars
// 1. Added Inconsistentif feature
// 2. We publish two events before and after asking for password (see
// postmgt.c and minisetup.h)
// 
// 13    9/02/05 1:23p Jerryp
// fix for incorrect help information being displayed
// 
// 12    5/25/05 1:38a Jerryp
// Moved handling of page 0 into the style specific code
// 
// 11    4/01/05 1:54p Franklynd
// 
// 10    2/17/05 12:47p Jerryp
// Reversed draw order to avoid help overwriting current.
// 
// 9     2/14/05 2:59p Jerryp
// Renamed some functions for consistency
// 
// 8     2/06/05 11:15a Jerryp
// Full hotkey support
// 
// 7     2/02/05 4:20p Jerryp
// **WORK IN PROGRESS **
// Latest changes for Label/Index.
// Not completely tested
// 
// 6     1/19/05 6:09p Jerryp
// Cleaned up header mess
// 
// 5     1/14/05 7:09p Jerryp
// First integration code with boot to shell.
// Still a bug in booting to shell from FV
// 
// 4     1/13/05 10:37a Jerryp
// Latest updated
// Added ifdef for fake HII info
// 
// 2     1/06/05 11:31a Jerryp
// Moved callback from Control to Object
// Better class heirarchy definitions through #define
// 
// 1     12/30/04 5:35p Jerryp
// Initial checkin
// ** Still some debugging code in place
// ** Not all object/controls work as expected
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		page.c
//
// Description:	This file contains code to handle page level operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//////////////////////////////////////////////////
//		Variable Declarations
//////////////////////////////////////////////////
PAGE_METHODS gPage =
{
	PageCreate,
	PageDestroy,
	PageInitialize,
	PageDraw,
	PageHandleAction,
	PageSetCallback
};
CHAR16 *gPageTitle = NULL;

//////////////////////////////////////////////////
//		Extern variables
//////////////////////////////////////////////////
extern EFI_GRAPHICS_OUTPUT_PROTOCOL	*gGOP;
extern BOOLEAN 		gPackUpdatePending;
extern UINT16 		gSelIdx;
extern UINT8 		gAddBgrtResolutions;

extern EFI_STATUS	FileBrowserLaunchFileSystem (UINT32 Variable);
//////////////////////////////////////////////////
//		Function Declarations
//////////////////////////////////////////////////
EFI_STATUS 	GetPageSubTitle(UINT32 PgIndex, UINT16 *TitleToken);
VOID 		SetGetBgrtCoordinates ( UINTN	*DestX, UINTN *DestY, UINTN *Width,	UINTN *Height, BOOLEAN Command );
VOID 		*ConvertBlt2Bmp ();
EFI_STATUS 	ProcessPackNotificationHook (VOID);
BOOLEAN 	IsPageModal(UINT32 PgIndex); //EIP-85745 Modal Support

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PageCreate
//
// Description:	function to create a page
//
// Input:	PAGE_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PageCreate( PAGE_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool(sizeof(PAGE_DATA));
		if ( *object == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Status = gObject.Create( object );

	if (EFI_ERROR(Status))
	{
		MemFreePointer( (VOID **)object );
		return Status;
	}

	(*object)->Methods = &gPage;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PageDestroy
//
// Description:	function to destroy a page, which uses the HotKey Fucntions
//
// Input:	PAGE_DATA *page, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PageDestroy( PAGE_DATA *page, BOOLEAN freeMem )
{
	UINT32	i;

	gObject.Destroy( page, FALSE );

	for ( i = 0; i < page->HotKeyCount; i++ )
	{
		gHotKey.Destroy( page->HotKeyList[i], TRUE );
	}

	MemFreePointer( (VOID **)&page->HotKeyList );

	for ( i = 0; i < page->FrameCount; i++ )
	{
		gFrame.Destroy( page->FrameList[i], TRUE );
	}
	page->FrameCount = 0;
	MemFreePointer( (VOID **)&page->FrameList );

	if ( freeMem )
		MemFreePointer( (VOID **)&page );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PageInitialize
//
// Description:	function to initialize a page, which uses the Frame Fucntions
//
// Input:	PAGE_DATA *page, PAGE_INFO *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PageInitialize( PAGE_DATA *page, PAGE_INFO *data )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32 i;

	page->CurrentFrame = 0;
	MemCopy( &page->PageData, data, sizeof(PAGE_INFO) );

	page->FrameCount = StyleGetPageFrames( data->PageID );

	page->FrameList = EfiLibAllocateZeroPool( sizeof(FRAME_DATA *) * page->FrameCount );
	if ( page->FrameList == NULL )
		return EFI_OUT_OF_RESOURCES;

	for ( i = 0; i < page->FrameCount; i++ )
	{
		if ( gFrame.Create( &page->FrameList[i] ) != EFI_SUCCESS )
			continue;

		page->FrameList[i]->PageID = data->PageID;
		gFrame.Initialize( page->FrameList[i], StyleGetFrameInitData( data->PageID, i ) );

		Status = StyleInitializeFrame( page->FrameList[i], page->FrameList[i]->FrameData.FrameType, data );
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PageDraw
//
// Description:	function to draw a page with attributes
//
// Input:	PAGE_DATA *page
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PageDraw( PAGE_DATA *page )
{
	UINT32	i, PageNum, MainFrameIndex=0, CurrentControl;
		
    FRAME_DATA *MainFrame = NULL;

    CONTROL_DATA **control;

	MainFrameIndex =StyleFrameIndexOf(MAIN_FRAME); 
	MainFrame = page->FrameList[MainFrameIndex];

	StyleBeforeFrame( MainFrame ) ;

	// update the help for the current selection
	_PageUpdateHelp( page );
	_PageUpdateTitle( page );
	_PageUpdateSubtitle( page );
	_PageUpdateNavStrings( page );
	_PageUpdateFrameStrings( page );

	PageNum = gApp->CurrentPage ;

	//Call Oem hooks to decide item focus on complete redraw
	
    if(gApp->CompleteRedraw && gApp->OnRedraw) {
		
		if(gApp->OnRedraw == MENU_COMPLETE_REDRAW)
			StylePageItemFocus(page, MainFrame);
		else if(gApp->OnRedraw == SUBMENU_COMPLETE_REDRAW) 
			StyleSubPageItemFocus(page, MainFrame);

		gApp->OnRedraw = 0 ;
			
	}
		


    //If there is an active control in Main frame only draw that frame
    if(MainFrame->CurrentControl == FRAME_NONE_FOCUSED)
		control = NULL;
	else
		control = &MainFrame->ControlList[MainFrame->CurrentControl];

	if ( control != NULL )
	{
        //If a control is active only draw that
		if( (*control)->ControlActive == TRUE )
		{
			StyleBeforeFrame( MainFrame ) ;
			gFrame.Draw( MainFrame );

            return EFI_SUCCESS;
		}
	}

	// Backup the MainFrame->CurrentControl
	CurrentControl = MainFrame->CurrentControl;
    for ( i = 0; i < page->FrameCount; i++ )
  	{
		StyleBeforeFrame( page->FrameList[i] ) ;
		gFrame.Draw( page->FrameList[i] );
		if(i == MainFrameIndex)
		{
			// After expression evalution if current control is affected
			if(MainFrame->CurrentControl != CurrentControl)
			{
				// Help might be updated
				_PageUpdateHelp( page );
				CurrentControl = MainFrame->CurrentControl;
				i = 0; // Redraw all the frames again
			}
		}
  	}


	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PageHandleAction
//
// Description:	function to handle the page actions
//
// Input:	PAGE_DATA *page, ACTION_DATA *action
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
extern BOOLEAN gEnableProcessPack;
EFI_STATUS PageHandleAction( PAGE_DATA *page, ACTION_DATA *action )
{
	UINT32	i;
    EFI_STATUS Status = EFI_UNSUPPORTED;
//EIP: 58925 Start
	UINT32 stackIndex = 0xFFFFFFFF, tmpcounter = 0;
	UINT16 parentPgID = 0, TitleToken = 0;

//EIP: 58925 End
	// On printScreen HotKey, Just return Unsupported and It will handed by Application Hotkey Handler.
	if( ( action->Input.Type == ACTION_TYPE_KEY ) &&
		(TsePrintScreenEventSupport(action->Input.Data.AmiKey.Key.ScanCode) ) ) 
	{
		GetPageSubTitle(page->PageData.PageID, &TitleToken);
		gPageTitle = HiiGetString( page->PageData.PageHandle, TitleToken);

		if (NULL != gPageTitle)
		{
			while(gPageTitle[tmpcounter]!= L'\0')
			{
				if (	('/' == gPageTitle[tmpcounter]) || 
						('\\' == gPageTitle[tmpcounter]) ||
						('<' == gPageTitle[tmpcounter]) ||
						('>' == gPageTitle[tmpcounter]) ||
						('?' == gPageTitle[tmpcounter]) ||
						('*' == gPageTitle[tmpcounter]) ||
						(':' == gPageTitle[tmpcounter]) ||
						('"' == gPageTitle[tmpcounter]) ||
						('|' == gPageTitle[tmpcounter])
					) //EIP-126876 to avoid create file with special characters. If any of these character found then replace it with '-' character
					gPageTitle[tmpcounter] = '-';
				tmpcounter++;
			}
		}
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

	//EIP-85745 Modal Support
	//If Page is Modal do not proceed further
	if(IsPageModal(page->PageData.PageID))
	{    	
		Status = EFI_UNSUPPORTED; //IF page is Modal
 
		if( action->Input.Type == ACTION_TYPE_KEY )
      	action->Input.Type = ACTION_TYPE_NULL ;
		goto DONE;
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
        if ( page->PageData.PageParentID == 0 )
        {
            Status = EFI_UNSUPPORTED;
//EIP: 58925 Start
            if(IsLinkHistorySupport())
            {    
			    Status = GetParentFormID((UINT16)gApp->CurrentPage, &parentPgID, &stackIndex); //Gets the parent page of the current page
			
                if(Status == EFI_SUCCESS)
                {
                    gApp->CurrentPage = parentPgID; //Else set the current page to the parent page
			    }
            }
//EIP: 58925 End
            
             goto DONE;
        }

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
//EIP: 58925 Start
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
//EIP: 58925 End
                gApp->CompleteRedraw = TRUE;
				gApp->OnRedraw = SUBMENU_COMPLETE_REDRAW;
            }

            Status = EFI_SUCCESS;
        }
    }
DONE:
	if (gPackUpdatePending)				//EIP75588 Update If any pack pending
	{
		if(!IsActiveControlPresent(page))
		{
			SETUP_DEBUG_UEFI_NOTIFICATION ("\n\n[TSE] PageHandleAction () calling ProcessPackNotificationHook() \n\n");
			gEnableProcessPack = TRUE;
			Status = ProcessPackNotificationHook ();
			gEnableProcessPack = FALSE;
		}
	}
//EIP: 58925 Start
    if(IsLinkHistorySupport())
    {
        if(Status == EFI_SUCCESS)
        {
   		    SetParentFormID(page->PageData.PageID, (UINT16)gApp->CurrentPage);
	    }
    }
//EIP: 58925 End
    return Status;
}

EFI_STATUS PageSetCallback( PAGE_DATA *page, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gObject.SetCallback( page, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PageUpdateMemo
//
// Description:	function to update the memo
//
// Input:	PAGE_DATA *page, UINT16 frameNumber, VOID* handle, UINT16 token
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _PageUpdateMemo( PAGE_DATA *page, UINT32 frameType, /*EFI_HII_HANDLE*/VOID* handle, UINT16 token )

{
	MEMO_DATA *memo;
	FRAME_DATA *memoFrame;
	UINT32 frameIndex;

	frameIndex = StyleFrameIndexOf(frameType);	
	if ( ( page->FrameCount <= frameIndex ) || ( token == 0 ) )
		return;

	memoFrame = page->FrameList[frameIndex];


	if ( memoFrame->ControlCount == 0 )
		return;

	memo = (MEMO_DATA *)memoFrame->ControlList[0];
	memo->ControlData.ControlHandle = handle;

	if(memo->ControlData.ControlType == CONTROL_TYPE_MEMO)
		UefiSetSubTitleField((VOID *)memo->ControlData.ControlPtr,token);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PageUpdateHelp
//
// Description:	function to update the page help
//
// Input:	PAGE_DATA *page
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _PageUpdateHelp( PAGE_DATA *page )
{
	CONTROL_DATA *control;
	FRAME_DATA *mainFrame;

	mainFrame = page->FrameList[StyleFrameIndexOf(MAIN_FRAME)];

	_PageUpdateMemo( page, HELP_FRAME, gHiiHandle, STRING_TOKEN(STR_EMPTY_STRING) );
	if ( mainFrame->ControlCount == 0 )
		return;

	if(mainFrame->CurrentControl == FRAME_NONE_FOCUSED)
		return;

	control = mainFrame->ControlList[mainFrame->CurrentControl];

	if ( control->ControlFocus )
		_PageUpdateMemo( page, HELP_FRAME, control->ControlData.ControlHandle, control->ControlData.ControlHelp );

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PageUpdateSubtitle
//
// Description:	function to update the subtitle of the page
//
// Input:	PAGE_DATA *page
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _PageUpdateSubtitle( PAGE_DATA *page )
{
	/*EFI_HII_HANDLE*/VOID * hiiHandle = page->PageData.PageHandle;
	UINT16 token = page->PageData.PageSubTitle;

	if ( token == 0 )
	{
		hiiHandle = gHiiHandle;
		token = gScreen->MainCopyright;
	}

	_PageUpdateMemo( page, SUBTITLE_FRAME, hiiHandle, token );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PageUpdateTitle
//
// Description:	function to update the title of the page
//
// Input:	PAGE_DATA *page
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _PageUpdateTitle( PAGE_DATA *page )
{
	/*EFI_HII_HANDLE*/VOID * hiiHandle = page->PageData.PageHandle;
	UINT16 token = page->PageData.PageTitle;

	if ( token == 0 )
	{
		hiiHandle = gHiiHandle;
		token = gScreen->MainTitle;
	}

	_PageUpdateMemo( page, TITLE_FRAME, hiiHandle, token );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PageUpdateNavStrings
//
// Description:	function to update the title of the page
//
// Input:	PAGE_DATA *page
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _PageUpdateNavStrings( PAGE_DATA *page )
{
	_PageUpdateMemo( page, NAV_FRAME, gHiiHandle, StyleGetNavToken( page->PageData.PageID ) );
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PageUpdateFrameStrings
//
// Description:	function to update the title of the page
//
// Input:	PAGE_DATA *page
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _PageUpdateFrameStrings( PAGE_DATA *page )
{
	StyleUpdateFrameStrings(page);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdatePageFocusedItemHelp
//
// Description:	function to update the Help in case of First Item focus set.
//
// Input:	PAGE_DATA *page
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdatePageFocusedItemHelp(PAGE_DATA *page)
{
	//call the internal function to update the page help
	_PageUpdateHelp(page);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HotclickESCaction
//
// Description:	function to handle the left click on ESC in Navigation frame.
//
// Input:	VOID 
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HotclickESCaction(VOID)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	PAGE_DATA *page;
	UINT32 stackIndex = 0xFFFFFFFF;
    UINT16 parentPgID = 0;
	  page = gApp->PageList[gApp->CurrentPage];

		if ( page->PageData.PageParentID == 0 )
		{
			gApp->Quit = ExitApplication();
			return;
		}
	
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

                if(IsLinkHistorySupport())
                {
                    // tell application that we need to change pages
                    Status = GetParentFormID((UINT16)gApp->CurrentPage, &parentPgID, &stackIndex); //Gets the parent page of the current page
    				if(Status != EFI_SUCCESS)
       					gApp->CurrentPage = page->PageData.PageParentID;
    					//gApp->CurrentPage = gNavStartPage; //If the parent page was not found or invalid, go to the first page
    				 else
                        gApp->CurrentPage = parentPgID; //Else set the current page to the parent page
                }
                else
                {
                    gApp->CurrentPage = page->PageData.PageParentID;
                }

                gApp->CompleteRedraw = TRUE;
				gApp->OnRedraw = SUBMENU_COMPLETE_REDRAW;
            }

            Status = EFI_SUCCESS;
        }
		
		
	    if(IsLinkHistorySupport())
	    {
	        if(Status == EFI_SUCCESS)
	        {
	   		    SetParentFormID(page->PageData.PageID, (UINT16)gApp->CurrentPage);
		    }
	    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		PrntScrnKeyHandleaction 
//
// Description:		Function to handle PrintScreenKeyto get screen image as BltBuffer and save as BMP file to a available filesystem
//
// Input:			VOID
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WriteDataToFileWrapper (CHAR16 *filename, VOID *Data, UINTN length, UINT32 index);
EFI_STATUS PrntScrnKeyHandleaction()
{
	BMP_IMAGE_HEADER  *BmpBuffer=NULL;
	EFI_STATUS 	Status = EFI_SUCCESS;
	EFI_TIME		time;

	CHAR16	*Title		= L"Snap of current page:";
	CHAR16	*Msg 			= NULL;
	CHAR16 	*Filename	= NULL;
	UINT8 	Sel = 0;
	UINTN 	StartX = 0, StartY = 0, Width = 0, Height = 0;
	UINT32 	variable = 0xffff;


	gAddBgrtResolutions = 1;
	Height = (UINTN)(gGOP->Mode->Info->VerticalResolution);
	Width = (UINTN)(gGOP->Mode->Info->HorizontalResolution);

	SetGetBgrtCoordinates (&StartX,&StartY,&Width,&Height,TRUE);

	//Converting blt buffer to BMP
	BmpBuffer =	ConvertBlt2Bmp ();

	if (BmpBuffer)
	{
		//List available FileSystem
		Status = FileBrowserLaunchFileSystem(variable);

		if (EFI_ERROR(Status))
		{
			PostManagerDisplayMsgBox (L"PrintScreen Error!!",L"Screen is not captured",MSGBOX_TYPE_OK,&Sel);
			goto DONE;
		}

		gRT->GetTime( &time, NULL );

		if (NULL == gPageTitle)
		{
			gPageTitle = EfiLibAllocateZeroPool ( (EfiStrLen(L"TSE_Snap")+1)*sizeof(CHAR16) );
			EfiStrCpy (gPageTitle, L"TSE_Snap");
		}
	
		Filename = EfiLibAllocateZeroPool ( (EfiStrLen(gPageTitle)+16)*sizeof(CHAR16));//length of title and time format (HH-MM-SS) and .BMP character
		if (NULL == Filename)
		{
			Status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		SPrint(Filename,((EfiStrLen(gPageTitle)+16)*sizeof(CHAR16)),L"%s_[%02d-%02d-%02d].BMP",gPageTitle,time.Hour,time.Minute,time.Second );
		Status = WriteDataToFileWrapper (Filename,BmpBuffer,BmpBuffer->Size,gSelIdx);

		if (!EFI_ERROR(Status))
		{
			Msg = EfiLibAllocateZeroPool( (EfiStrLen(L"Image is stored with name : ") + EfiStrLen (Filename) + 1) * sizeof(CHAR16) );	
		
			if (NULL == Msg)
			{
				Status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}

			SPrint(Msg,( (EfiStrLen(L"Image is stored with name : ") + EfiStrLen (Filename)+1) * sizeof(CHAR16) ),L"Image is stored with name : %s",Filename);
			PostManagerDisplayMsgBox (Title,Msg,MSGBOX_TYPE_OK,&Sel);
		}

		else
			PostManagerDisplayMsgBox (L"Error Message",L"Failed to save to a file",MSGBOX_TYPE_OK,&Sel);		
	}

DONE:
	if (BmpBuffer) //EIP-123310 memory leak
		MemFreePointer((VOID **)&BmpBuffer);
	if (Filename)
		MemFreePointer((VOID **)&Filename);
	if (Msg)
		MemFreePointer((VOID **)&Msg);
	if (gPageTitle)
		MemFreePointer ((VOID **)&gPageTitle);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		PrntScrnKeyNotification 
//
// Description:		PrntScrnKeyNotification Function handle PrntScrnKey action
//
// Input:			CHAR16 * 
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PrntScrnKeyNotification(APPLICATION_DATA *app, HOTKEY_DATA *hotkey, VOID *cookie )
{
	if ( TRUE == TsePrintScreenEventSupport ( ((HOTKEY_DATA*)hotkey)->HotKeyData.Key.ScanCode ) )
		PrntScrnKeyHandleaction();
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
