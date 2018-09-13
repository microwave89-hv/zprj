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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/frame.c $
//
// $Author: Premkumara $
//
// $Revision: 63 $
//
// $Date: 9/05/14 6:27a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/frame.c $
// 
// 63    9/05/14 6:27a Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 62    5/02/14 9:30p Arunsb
// EIP141986 changes reverted.
// 
// 61    5/02/14 11:01a Premkumara
// [TAG]  		EIP141986
// [Category]  	New Feature
// [Description]  	Made Grayed controls to focus-able when token
// TSE_SETUP_GRAYOUT_SELECTABLE
//  is enabled and can't edit the values
// [Files]  		AMITSE.sdl,CommonHelper.c,frame.c,Label.c,minisetupext.h,
// numeric.c,PopupPassword.c,PopupSel.c,PopupString.c,SubMenu.c
// 
// 60    5/02/14 2:55a Premkumara
// [TAG]  		EIP131547
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	In CPU Config page, controls are going beyond the page
// while clicking the down arrow in scroll bar in 80*25 mode [when
// terminal redirection module enabled].
// [RootCause]  	TSE was checking for LastVisibleCtrl with the total
// number of frame ctrl count
// and accordingly it was modifying FirstVisibleCtrl and LastVisibleCtrl 
// But there are some Suppressed controls at the end of the CPU Config
// page
// for which the above check was wrong.
// [Solution]  	Added an extra condition to check whether LastVisibleCtrl
// is equal to the LastNonSupressctrl in the Frame or not and
// accordingly modify FirstVisibleCtrl and LastVisibleCtrl.
// [Files]  		frame.c
// 
// 59    5/01/14 3:42p Premkumara
// [TAG]  		EIP123727
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Enabling Multiline and in Boot option priorities, Clicking
// on second or third line of the boot item is not selecting boot options
// menu
// [RootCause]  	Proper Condition was not there to check whether Mouse
// Click
// is within the Width and Height of Control or not.
// [Solution]  	Added Proper Condition to check whether Mouse Click
// is within the Width and Height of Control or not.
// [Files]  		Date.c, time.c, frame.c, SubMenu.c, numeric.c,
// PopupString.c, PopupSel.c, ordlistbox.c, PopupPassword.c, UefiAction.c,
// 
// 58    2/11/14 8:32p Arunsb
// [TAG]	EIP131365
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	TSE Help window flickers when Mouse\Touch device used under
// boot page in Setup
// [Root Cause]	gActiveBuffer->Chars get flushed with EmptyString in
// TSEMouseHelpFrameHandleAction() every time
// [Solution]	Handled gActiveBuffer properly
// [Files]	frame.c
// 
// 57    12/03/13 1:07p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 56    12/02/13 12:32p Premkumara
// [TAG]	                EIP131547
// [Category]	Bug Fix
// [Severity:]	                Important
// [Symptom:]	Frame is scrolling beyond visible controls when mouse is
// clicked on down arrow 
// [Root Cause]	Frame is scrolling for suppressed controls which are not
// visble in the frame
// [Solution]	Scrolling frame based on visible controls count.
// [Files]	frame.c
// 
// 54    3/25/13 8:39a Premkumara
// [TAG]  		EIP116315
// [Category]  	Improvement
// [Description]  	Display control prompt string for password control.
// (for String on CHAP secret popup)
// [Files]  		- AMITSE.sdl
// - CommonHelper.c
// - FakeToken.c
// - AmiTSEStr.uni
// - TseLite\PopupPassword.c
// - uefi2.1\UefiWapper21.c
// - uefi2.0\UefiWapper20.c
// - uefi2.0\HiiCallback.c
// - uefi2.0\hii.h
// - uefi2.0\hii.c 
// 
// 53    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 33    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 51    9/18/12 6:18a Arunsb
// [TAG]  		EIP92972
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hangs when submenu has no control in it
// [RootCause]  	visibleControlHeight is 0, dividing by this causes system
// hang
// [Solution]  	visibleControlHeight handled properly
// [Files]  		frame.c
// 
// 50    9/17/12 6:20a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 48    9/10/12 5:02a Rajashakerg
// [TAG]  		EIP93881 and 93873
// [Category]  	Improvement
// [Description]  	need keep system password after Load default and
// Password saved into NVRAM immediately(not buffer) while it is installed
// in TSE
// [Files]  		frame.c, callback.c, AMITSE.sdl, CommonHelper.c
// 
// 47    5/28/12 12:31p Premkumara
// [TAG]  		EIP67049 & 90224
// [Category]  	New Feature
// [Description]  	Support mouse drag operation in frame and list box
// [Files]  		CommonHelper.c, Frame.c, ListBox.c, Minisetupext.h
// 
// 46    4/05/12 9:15a Arunsb
// Unwanted code commented
// 
// 45    4/05/12 7:15a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 44    2/01/12 6:09p Blaines
// Rollback
// 
// 42    1/31/12 6:33p Blaines
// [TAG] - EIP 79963
// [Category]- Defect 
// [Synopsis]- Scrollbar functionality with mouse was not working properly
// and While Clicking the arrow buttons in scroll bar moves the entry up
// not the scroll bar.
// [Description]- 1. Build the BIOS project with GTSE and Mouse support,
// 2. Goto Chipset->South bridge, click on the arrow keys or Move the
// scrool bar and observe the behaviour.
// [Root Cause] - Incorrect scrollbar size computed when total
// lines/controls was 1 greater than a filled frame. 
// [Solution] - Check for special case and adjust visibleControlHeight
// when total lines is 1 greater than a filled frame (visible controls).
// [Files changed] - frame.c
// [Functions changed] - FrameDraw
// 
// 41    1/20/12 4:10a Rajashakerg
// [TAG]  		EIP78929 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Control selection using Mouse is not user friendly.
// [RootCause]  	Updating the buffer with mouse click information provided
// by mouse driver is improper. 
// [Solution]  	Updated the mouse click information properly to the buffer
// which is used by tse to do action.
// [Files]  		Action.c, frame.c ListBox.c
// 
// 40    12/07/11 3:32p Arunsb
// [TAG]  		EIP75588
// [Category]  	New Feature
// [Description]  	Support for queuing UpdatePack notifications
// [Files]  		frame.c, page.c, formbrowser2.c, hii.c, hiicallback.c,
// hiinotificationhandler.c, tseuefihii.h and uefi21wapper.c
// 
// 39    12/07/11 2:10p Rajashakerg
// [TAG]  		EIP76810 
// [Category]  	Improvement
// [Description]  	EFI_IFR_INCONSISTENT_IF to follow 28.2.5.9.2 as per efi
// spec 2.3.1
// [Files]  		frame.c
// 
// 38    11/21/11 12:07p Premkumara
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
// 37    11/20/11 7:49a Rajashakerg
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
// 36    11/18/11 11:40a Blaines
// [TAG] - EIP 72349 
// [Category]- Sighting
// [Synopsis]- In some SAS cards the scroll bar does not function
// correctly.
// 
// [Description] - The scroll bar is not accurate, doesn't properly handle
// multi-line controls. In some SAS cards with a large number of drives, 
// the scroll bar would move down the screen then disappear before
// reaching the end, giving the appearance that no more items are viewable
// or selectable.
// 
// [Files]
// Frame.c
// 
// 35    11/14/11 6:55p Blaines
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
// 34    7/21/11 1:07p Rajashakerg
// Updated the file to close the popup window when left clicked on help
// and navigation frame
// 
// 33    7/21/11 11:24a Rajashakerg
// Updated the file to restrict the control selection when cliked on help
// frame with mouse
// 
// 30    6/30/11 5:18a Rajashakerg
// Updated the help frame scroll restricted for left click alone.
// 
// 29    6/29/11 4:34p Rajashakerg
// Updated for Help frame scroll changes
// 
// 28    6/29/11 12:58p Rajashakerg
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
// 27    6/29/11 12:36p Rajashakerg
// [TAG]  		EIP59657 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	[TSE] When change password status, sometimes will miss
// first item.
// [RootCause]  	The frame first visible control is not handled properly
// [Solution]  	The first visible control is handled properly by making
// first visible control as 0 in framescroll
// [Files]  		Frame.c
// 
// 26    6/28/11 2:42p Arunsb
// Build error resolved by adding UpdateDestiantionQuestion function
// declaration.
// 
// 25    6/23/11 3:58p Rajashakerg
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
// 24    4/29/11 4:36p Arunsb
// For 2.13 public patch release IFR RefX feature is omitted
// 
// 22    3/29/11 12:15a Madhans
// [TAG]  		EIP54968
// [Category]  	Improvement
// [Description]  	To Support different style modules in TSE generically
// [Files]  		Ezport module updated. EzportPlus and Legacy Styles Modules
// added.
// 
// 21    12/28/10 9:37a Mallikarjunanv
// updaed changes regarding EIP:48382
// 
// 20    12/25/10 7:41a Mallikarjunanv
//  [TAG]  		EIP 49548 / 48377
//  [Category]  	Bug Fix
//  [Severity]  	Normal
//  [Symptom]  	BIOS gui scroll bar fails to indicate that there are more
// options available on the Advanced | CPU Configuration page
//  [RootCause]  	Scrollbar draw is not handled properly
//  [Solution]  	Updated the scrollbar draw depending on the controls of
//  the frame.
//  [Files]  		Frame.c
// 
// 19    12/25/10 4:16a Mallikarjunanv
// [TAG]  		EIP 48382
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Clicking somewhere in BIOS Setup selecting the control
// strings.
// [RootCause]  	Co-ordinates are not properly set for mouse click
// operation
// [Solution]  	Co-ordinates are updated properly for mouse click
// operation
// [Files]  		Frame.c
// 
// 18    12/25/10 3:40a Mallikarjunanv
// [TAG]  		EIP 47940
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Scrollbar disappeared while scrolling in the BOOT page
// [RootCause]  	Scrollbar support is not handled properly depending on
// the controls
// [Solution]  	Updated the scrollbar support handling depending on the
// controls.
// [Files]  		Frame.c
// 
// 17    12/02/10 2:44p Madhans
// [TAG] - EIP 47608  
// [Category]- Defect
// [Severity]- Mordarate
// [Symptom]- If the String length is different in different languages,
// Changing language causes
//            TSE multiline function to not work correctly.
// [Rootcause] control dimension are set only with initial language and it
// is not updated after that.
// [Solution]- The Control dimentions need to updated when language
// changes.
// [Files] - frame.c
// 
// 16    10/05/10 11:53a Blaines
// In the function _FrameAddTitle, set the property ParentFrameType before
// calling gMemo.Initialize. This is useful in case the function
// gMemo.Initialize is overriden. 
// 
// 15    9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 23    9/15/10 2:05p Madhans
// If the Dynamic update happens while drawing the control (via Evalutate
// Condition->VarGetValue->ExtractConfig). 
// The controls may be invalidated. In that case don't proceed with Frame
// Draw.
// 
// 22    8/12/10 1:06p Blaines
// EIP-41817: Fix to allow Help Frame scroll support
// 
// Use reference to gFrame.AddControl to allow option to customization
// outside of frame.c.
// 
// 21    6/17/10 2:46p Madhans
// Mouse issue fix,
// 
// 20    6/14/10 7:09p Madhans
// Dynamic parsing support
// 
// 19    3/30/10 4:50p Blaines
// Remove the call to StyleFrameAddControl.
// 
// 18    3/26/10 6:52p Madhans
// Support to Map the do the Control Mapping from gTseControlMap Table. So
// no changes need in Frame.c, With this feature gTseControlMap Can be
// customized to add/customize the TSE controls.
// 
// 17    3/23/10 5:13p Blaines
// Add new style module hook
// 
// 16    2/24/10 4:37p Madhans
// EIP 35522 Fix to make Text interactive control to work. Need to send
// the Timer action to all the controls.
// 
// 15    2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 14    2/15/10 10:13p Madhans
// To avoid warnings
// 
// 13    2/05/10 6:04p Madhans
// Mouse action override from Style Module.
// 
// 12    2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 11    2/01/10 7:38p Madhans
// EIP 32501 : Fix to handle the Conditional control Focusing , in the Sub
// form
// 
// 10    1/29/10 4:34p Madhans
// To avoid compiler warnings.
// 
// 9     1/09/10 6:34a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 8     12/04/09 8:49a Mallikarjunanv
// EIP:31606 - Fix for hanging issue in case of no active controls in a
// frame
// 
// 7     8/13/09 1:18p Blaines
// EIP #24980 Fix to properly display right area text;
// 
// Properly initialize the control width
// 
// 6     7/20/09 1:21p Mallikarjunanv
// error fixed in multiline controls
// 
// 5     7/09/09 12:28p Mallikarjunanv
// updated the password encoded fix
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
// 3     5/20/09 3:44p Blaines
// Update the way Scroll Behavior token is accessed
// 
// 2     5/07/09 10:36a Madhans
// Changes after Bin module
// 
// 1     4/28/09 11:04p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:08p Madhans
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		frame.c
//
// Description:	This file contains code to handle frame operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

EFI_STATUS _FrameHandleKey( FRAME_DATA *frame, AMI_EFI_KEY_DATA Key );
EFI_STATUS _FrameScroll( FRAME_DATA *frame, BOOLEAN bScrollUp );
BOOLEAN _FrameSetControlFocus( FRAME_DATA *frame, UINT32 index );
EFI_STATUS _PreviousFrame (FRAME_DATA *frame);
EFI_STATUS _NextFrame (FRAME_DATA *frame);
EFI_STATUS _FocusFirst (FRAME_DATA *frame);
EFI_STATUS _FocusLast (FRAME_DATA *frame);
EFI_STATUS FrameDrawScrollBar (FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32	modVal, UINT32	sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar);
EFI_STATUS UpdateDestiantionQuestion (UINT32, UINT32, UINT32 *);
EFI_STATUS TSEMouseHelpFrameHandleAction( FRAME_DATA *frame, ACTION_DATA *action,CONTROL_DATA **control);
VOID _HelpFrameScroll(MEMO_DATA *memo,BOOLEAN bScrollUp);
BOOLEAN IsMouseSupported(VOID);
//EIP-67049 Start
INT32 lButtonDownVaringPosition = 0;
INT32 lButtonDownInitialPosition = 0;
static UINT32 gFrameScrollBarTop = 0, gFrameScrollBarBottom = 0;
//EIP-67049 End
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
FRAME_METHODS gFrame =
{
	FrameCreate,
	FrameDestroy,
	FrameInitialize,
	FrameDraw,
	FrameHandleAction,
	FrameSetCallback,
	FrameAddControl
};
//--------------------------------------------------------------------------

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:		FrameCreate
//
// Description: Allocated memory size and creates frame 
//
// Input:		FRAME_DATA **object
//
// Output:		EFI_STATUS status - 
//				EFI_SUCCESS - 
//				EFI_OUT_OF_RESOURCES - if the object is NULL
//				EFI_ERROR - If there are any the error in the object
//							creating process
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FrameCreate( FRAME_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(FRAME_DATA) );

		if ( *object == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Status = gObject.Create( object );

	if (EFI_ERROR(Status))
	{
		MemFreePointer( (VOID **)object );
		return Status;
	}

	(*object)->Methods = &gFrame;

	return Status;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    FrameDestroy
//
// Description: Destroys an existing frame and frees memory
//
// Input:       FRAME_DATA *frame - Frame to be destroyed
//				BOOLEAN freeMem - Frees frame memory if TRUE, ignores
//									otherwise
//
// Output:		EFI_STATUS - EFI_SUCCESS
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FrameDestroy( FRAME_DATA *frame, BOOLEAN freeMem )
{
	CONTROL_DATA **control;
	UINT32	i;

	if(NULL == frame)
	  return EFI_SUCCESS;
	control = frame->ControlList;
	for ( i = 0; i < frame->ControlCount; i++, control++ )
	{
		if (*control)			//Destroy the controls if it is not NULL
			(*control)->Methods->Destroy( *control, TRUE );
	}

	frame->ControlCount = 0;

	MemFreePointer( (VOID **)&frame->ControlList );
	MemFreePointer( (VOID **)&frame->BlankLine );
	MemFreePointer( (VOID **)&frame->OrigPosition );
	MemFreePointer( (VOID **)&frame->CurrPosition );

	if ( freeMem )
		MemFreePointer( (VOID **)&frame );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:		 FrameInitialize
//
// Description:  Initializes the frame data
//
// Input:		 FRAME_DATA *frame - Frame to be intialized
//				 FRAME_INFO *data - Related frame data 
//
// Output:		 EFI_STATUS - EFI_SUCCESS
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FrameInitialize( FRAME_DATA *frame, FRAME_INFO *data )
{
	if ( data != NULL )
	{
		MemCopy( &frame->FrameData, data, sizeof(FRAME_INFO) );
		if ( frame->PageID != 0 )
		{
			frame->BlankLine = EfiLibAllocateZeroPool( sizeof(CHAR16) * (data->Width + 1) );
			if ( frame->BlankLine != NULL )
				MemFillUINT16Buffer( frame->BlankLine, data->Width, L' ' );
		}
	}

	frame->FirstVisibleCtrl = 0;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:		IsScrollSupportRequired
//
// Description: To know whether the scroll supprot required befor drawing the frame
//
// Input:       FRAME_DATA *frame - Frame information to get frame info
//
// Output:		BOOLEAN - TRUE/FALSE
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN	IsScrollSupportRequired(FRAME_DATA *frame )
{
	CONTROL_DATA **control;
	UINT16 i, Height, Top;
	UINT8 u8ChkResult;

	control = frame->ControlList;
	Height = frame->FrameData.Top;

	for ( i = 0; i < frame->ControlCount; i++, control++ )
	{
		Top = Height;

		u8ChkResult = CheckControlCondition( &((*control)->ControlData) ); //Check conditional

		if(u8ChkResult == COND_NONE || u8ChkResult == COND_GRAYOUT) {
	// EIP47608 +>>
		//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
		if(IsTSEMultilineControlSupported())
		{
			if(frame->FrameData.FrameType == MAIN_FRAME)
			{
				UINT16 height=0;
				(*control)->Methods->GetControlHeight( *control, (VOID*)frame,&height);
				height = height ? height:1;
				(*control)->Methods->SetDimensions( *control, 
										frame->FrameData.Width - (UINT8)gLabelLeftMargin - 2, 
										height );
			}
		}         
	// EIP47608 <<+ 
			Height = Height + (*control)->Height;
		}
	}
	
	//check whether scroll support required.
	if((frame->UseScrollbar) && ((frame->FrameData.Top + frame->FrameData.Height) >= Height+1))
	{
		return FALSE;
	}

	return TRUE;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:		FrameDraw
//
// Description: Draws the controls for the given frame 
//
// Input:       FRAME_DATA *frame - Frame information to draw controls
//
// Output:		EFI_STATUS - EFI_SUCCESS if successful, else EFI_ERROR
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FrameDraw( FRAME_DATA *frame )
{
	CONTROL_DATA **control;
	UINT32	i, j,FirstLine=0, LastLine=0, topPos=0, lastPos=0, count, visibleControlHeight=0, visibleControlCount = 0, modVal=0, sizeOfBar = 0, numOfBlocks = 0,CurrentvisibleControlCount = 0,CurrentFirstvisibleControlCount = 0,MltCnt=0,FrameLastVisibleControl=0;//EIP:48377/49548 Needed Local declarations for modification.
	UINT16 CurrHeight, ControlTop;
    UINT8 u8ChkResult;
    UINT8 u8ChkMask;

    BOOLEAN bCurrNotFocused = FALSE,bEraseScrollBar=FALSE;

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
		
		u8ChkResult = CheckControlCondition( &((*control)->ControlData) );
		
		//Setting focus to control if no control-condition is present and token TSE_SETUP_GRAYOUT_SELECTABLE is enable to make GrayoutIf control to focus and selectable
		if ( (COND_NONE == u8ChkResult) || (IsGrayoutSelectable() && (COND_GRAYOUT == u8ChkResult)) )
		{
          // Control might be dynamically updated. Get the actual control
          if(*control == NULL)
          {
            gApp->CompleteRedraw = TRUE;
            return EFI_UNSUPPORTED;
          }

			// Set the Focus to current control
			if((*control)->Methods->SetFocus(*control,TRUE) !=  EFI_SUCCESS)
			{
				
				//EIP-41817: Fix to allow Help Frame scroll support
				if(frame->FrameData.FrameType != HELP_FRAME)
				{ 
					frame->CurrentControl = FRAME_NONE_FOCUSED;
					bCurrNotFocused = TRUE; // Non is focused
				}
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
	
	//EIP:47940 - Check whether the scroll support required before proceeding.
	if(!IsScrollSupportRequired( frame )) {
		//If the scroll is not required, then reset the first visible control.
		frame->FirstVisibleCtrl = 0;
	}

    //Set position for all controls begining from FirstVisibleControl.
    //In the process calculate the correct LastVisibleControl.
    control = frame->ControlList;
    ControlTop = CurrHeight = 0;
    control = control + frame->FirstVisibleCtrl;
    CurrHeight = frame->FrameData.Top;
    frame->LastVisibleCtrl = frame->FirstVisibleCtrl;

	for ( i = frame->FirstVisibleCtrl; i < frame->ControlCount; i++, control++ )
	{
        ControlTop = CurrHeight;

        //Check conditional
        u8ChkResult = CheckControlCondition( &((*control)->ControlData) );

        if(*control == NULL)
        {
          gApp->CompleteRedraw = TRUE;
           return EFI_UNSUPPORTED;
        }

        if(u8ChkResult == COND_NONE || u8ChkResult == COND_GRAYOUT)
        {
// EIP47608 +>>
			//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
			if(IsTSEMultilineControlSupported())
			{
				if(frame->FrameData.FrameType == MAIN_FRAME)
				{
					UINT16 height=0;
					(*control)->Methods->GetControlHeight( *control, (VOID*)frame,&height);
					height = height ? height:1;
					(*control)->Methods->SetDimensions( *control, 
											frame->FrameData.Width - (UINT8)gLabelLeftMargin - 2, 
											height );
				}
			}
// EIP47608 <<+

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

		  //If token TSE_SETUP_GRAYOUT_SELECTABLE is enable to make GrayoutIf control to focus and selectable
        if (IsGrayoutSelectable())
            u8ChkMask = COND_NONE | COND_GRAYOUT;
        else
            u8ChkMask = COND_NONE;

        if ((u8ChkResult & ~u8ChkMask) != 0)
        {
            //Control grayed out or suppressed
            if(frame->CurrentControl == i)
            {
                //Current control cant be focused
                (*control)->Methods->SetFocus(*control,FALSE);
                bCurrNotFocused = TRUE;
            }
        }

        (*control)->Methods->SetPosition( *control, (*control)->Left, ControlTop);
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
    control = control + frame->FirstVisibleCtrl;
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

			if(count <= frame->LastVisibleCtrl)//EIP:48377/49548 Calculating the actual vlaue of CurrentvisibleControl when suppressed controls are present
   			         CurrentvisibleControlCount++;	
			if(count < frame->FirstVisibleCtrl)//EIP:48377/49548 Calculating the actual vlaue of FirstvisibleControl when suppressed controls are present
            			CurrentFirstvisibleControlCount++;
			FrameLastVisibleControl = count;
	  }
	}
    
    //EIP:72349
    if(frame->FrameData.FrameType == MAIN_FRAME)
    {
        // Total height of all drawable controls, takes care of multi-line issues
        visibleControlHeight = (UINT32)(CurrHeight - frame->FrameData.Top);
    
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
    
    	//Scroll bar coordinates are updated based on the controls in the frame
       	numOfBlocks = frame->FrameData.Height - 2;
        
        // Find the top position, considering multi-line controls may be present     
        for(count=0; count < frame->FirstVisibleCtrl; count++)
        {
            u8ChkResult = CheckControlCondition( &(frame->ControlList[count]->ControlData) );
            if((COND_NONE == u8ChkResult) || (COND_GRAYOUT == u8ChkResult))
            {
                topPos += frame->ControlList[count]->Height;
            }
        }
        
        // Find the last position, considering multi-line controls may be present
        for(count=0; count < frame->LastVisibleCtrl; count++)
        {
            u8ChkResult = CheckControlCondition( &(frame->ControlList[count]->ControlData) );
            if((COND_NONE == u8ChkResult) || (COND_GRAYOUT == u8ChkResult))
            {
                lastPos += frame->ControlList[count]->Height;
            }
        }

		// EIP_79963 Start             
        //Special case, check if total lines is 1 greater than a filled frame (visible controls)
        if( (visibleControlHeight > (UINT32)(frame->FrameData.Height-1)) && 
            ((visibleControlHeight - (UINT32)(frame->FrameData.Height-1)) < 2)  )
        {
            visibleControlHeight += 1 ;
            MltCnt = 1 ;
        }
		//EIP_79963 End 

		if (visibleControlHeight)
		{
			FirstLine = (((frame->FrameData.Height - 1) * topPos)/visibleControlHeight )+ frame->FrameData.Top;
			LastLine  = (((frame->FrameData.Height - 1) * lastPos)/visibleControlHeight )+ frame->FrameData.Top;
			sizeOfBar = ((frame->FrameData.Height - 1) * numOfBlocks) / visibleControlHeight;
			modVal = ((((frame->FrameData.Height - 1) * numOfBlocks) % visibleControlHeight)* numOfBlocks) > (numOfBlocks/2) ? 1 : 0;
		}
    
		//EIP_79963 Start
        if(((frame->LastVisibleCtrl < frame->ControlCount-1 )&&(FirstLine > (UINT32)(frame->FrameData.Height-2) )) || (frame->LastVisibleCtrl == FrameLastVisibleControl) || 
			((frame->FirstVisibleCtrl > 0) && (FirstLine == frame->FrameData.Top)) )
		{
		    if( (frame->FrameData.Top+topPos) < (UINT16)(frame->FrameData.Height-2))
			{
                if(MltCnt)
	            {
				    FirstLine = frame->FrameData.Top+topPos; //Providing the top postion value for immediate scroll after the (frame->FrameData.Height-2) reached
					LastLine = FirstLine + sizeOfBar+1;//Providing the appopriate lastline
                }
			}
		}
		//EIP_79963 End            

        // Minimum scrollbar size is 1
        if( ((LastLine - FirstLine)< 2) || (sizeOfBar == 0) )
        {
           sizeOfBar = 1 ;
        }
    
        // Scrollbar size must remain constant
        if((LastLine - FirstLine - 1) != sizeOfBar)
        {
            //Check the maximum scrollbar boundry
            if((FirstLine + sizeOfBar + 1) > (UINT32)(frame->FrameData.Top + frame->FrameData.Height - 2))
            {
                //Set the maximum scrollbar boundry
                FirstLine = frame->FrameData.Top + frame->FrameData.Height - 2 - sizeOfBar - 1 ;
            }
               
            LastLine = FirstLine + sizeOfBar + 1 ;  
        }
		
		if(MAIN_FRAME == frame->FrameData.FrameType)//EIP-67049 To store Scrollbar Top and Bottom positon 
		{
			gFrameScrollBarTop = FirstLine;
			gFrameScrollBarBottom = LastLine;
		}
    
       	// draw scrollbar if necessary
    	StyleDrawScrollBar(frame, FirstLine, LastLine, modVal, sizeOfBar, numOfBlocks, bEraseScrollBar);

    }//EIP:72349	
			
	FlushLines( frame->FrameData.Top, frame->FrameData.Top + frame->FrameData.Height );

//	if((!TSEMouseIgnoreMouseActionHook())&&((frame->ControlList[frame->CurrentControl]->ControlData.ControlType == CONTROL_TYPE_DATE)||(frame->ControlList[frame->CurrentControl]->ControlData.ControlType == CONTROL_TYPE_TIME)))
//	 if(MAIN_FRAME == frame->FrameData.FrameType)	
//		NumericSoftKbdInit();

	
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:		 FrameDrawScrollBar
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

EFI_STATUS FrameDrawScrollBar (FRAME_DATA *frame, UINT32 FirstLine, UINT32 LastLine, UINT32	modVal, UINT32	sizeOfBar, UINT32 numOfBlocks, BOOLEAN bEraseScrollBar)
{
	UINT32	i, j ; 
	CHAR16	ArrUp[2]={{GEOMETRICSHAPE_UP_TRIANGLE},{0x0000}} ;
    CHAR16	ArrDown[2]={{GEOMETRICSHAPE_DOWN_TRIANGLE},{0x0000}};
    CHAR16	ScrlSel[2]={{BLOCKELEMENT_FULL_BLOCK/*L'N'*/},{0x0000}};
    CHAR16	ScrlNSel[2]={{BLOCKELEMENT_LIGHT_SHADE/*L'S'*/},{0x0000}};


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
					DrawStringWithAttribute( frame->FrameData.Left + frame->FrameData.Width , j, ArrUp, 
				                            StyleGetScrollBarUpArrowColor() );
				else if(i==(UINT16)(frame->FrameData.Height - 1))
					DrawStringWithAttribute( frame->FrameData.Left+ frame->FrameData.Width, j, ArrDown, 
					                             StyleGetScrollBarDownArrowColor() );
				else
				{
					if( (j > FirstLine) && (j < LastLine) &&  ((sizeOfBar + modVal) != 0))////EIP:48377/49548 commented based on the draw of scrollbar.
					{	
						DrawStringWithAttribute( frame->FrameData.Left+ frame->FrameData.Width, j, ScrlSel, 
													StyleGetScrollBarColor() );
						sizeOfBar--;
					}
					else
					{
						DrawStringWithAttribute( frame->FrameData.Left+ frame->FrameData.Width, j, ScrlNSel, 
							                         StyleGetScrollBarColor() ); 
					}
				}
			}
			else if (bEraseScrollBar == TRUE)
				DrawStringWithAttribute( frame->FrameData.Left+ frame->FrameData.Width, j, L" ", 
					                         StyleGetScrollBarColor() ); 

		}
		bEraseScrollBar = FALSE;
	}
			

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    CheckKeyinHotKeysList
//
// Description: For Inconsistence condition checking for Hotkeys pressed to show the popup
//
// Input:		AMI_EFI_KEY_DATA Key
//
// Output:		BOOLEAN 
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckKeyinHotKeysList(AMI_EFI_KEY_DATA Key)
{
  UINT16 index=0;
	for(index=0; index <= gHotKeyCount; index++)
	{
		if( (!EfiCompareMem(&Key, &gHotKeyInfo[index], sizeof(EFI_INPUT_KEY)) ) &&
		( TseCheckShiftState( Key, gHotKeyInfo[index].KeySftSte ) )	)
			return TRUE;
	}
  return FALSE;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    FrameHandleAction
//
// Description: Action handler for specific frame 
//
// Input:		FRAME_DATA *frame - Pointer to the frame data
//				ACTION_DATA *action - Specific action for the frame
//
// Output:		EFI_STATUS Status - EFI_SUCCESS if successful, else
//										EFI_UNSUPPORTED
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FrameHandleAction( FRAME_DATA *frame, ACTION_DATA *action )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	CONTROL_DATA **control;

	if ( frame->ControlCount == 0 )
		return Status;

	if(frame->CurrentControl == FRAME_NONE_FOCUSED)
		control = NULL;
	else
		control = &frame->ControlList[frame->CurrentControl];

	switch ( action->Input.Type )
	{

        case ACTION_TYPE_MOUSE:
			Status = MouseFrameHandleAction(frame,action,control);
            break;

        case ACTION_TYPE_KEY:
            if ( control != NULL )
                Status = (*control)->Methods->HandleAction( *control, action );

            if (EFI_ERROR(Status))
                Status = StyleFrameHandleKey( frame, action->Input.Data.AmiKey.Key );

			//EIP76810 : Ckecking Inconsistence for the current control
			if (EFI_ERROR(Status))
			{
				if(( ControlActionUnknown != MapControlKeysHook(action->Input.Data.AmiKey))||(CheckKeyinHotKeysList(action->Input.Data.AmiKey)))
				{//If the control action is known and if its hot key only we are popuping up the ERROR popup
					if( CheckInconsistence((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[gApp->CurrentPage])) )
						if ( action->Input.Type != ACTION_TYPE_NULL )
							gAction.ClearAction( action );//Clearing the action if it is valid key pressed
				}
			}
		
            if (EFI_ERROR(Status))
                Status = _FrameHandleKey( frame, action->Input.Data.AmiKey );
            break;

		case ACTION_TYPE_TIMER:
			{
				UINT32 i;
				control = frame->ControlList;
				for ( i = 0; i < frame->ControlCount; i++, control++ )
				{
					EFI_STATUS TempStatus = (*control)->Methods->HandleAction( *control, action );
					if ( Status != EFI_SUCCESS )
						Status = TempStatus;
				}
				// To kill the timer action. Pass it to all the controls and frame.
				//	gAction.ClearAction( action );
			}

            if (EFI_ERROR(Status))
	           	Status = StyleFrameHandleTimer( frame, action);
			break;
		default:
			break;
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FrameSetCallback
//
// Description:	Function to set callback.
//
// Input:		FRAME_DATA *frame, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FrameSetCallback( FRAME_DATA *frame, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gObject.SetCallback( frame, container, callback, cookie );
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    FrameAddControl
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
EFI_STATUS FrameAddControl( FRAME_DATA *frame, CONTROL_INFO *controlData )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	CONTROL_DATA **control;
	POSITION_INFO *pos;
	UINT16 count = (UINT16)frame->ControlCount;
	UINT16 i;
	BOOLEAN		IsValidControl = FALSE;
	gActiveFrame = frame;
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
            
            //EIP-127577 Start, commented in order to remove the delay before entering Setup.
            // For Multi-line support, GetControlHeight is called again during the draw phase.
            /* 
			if(IsTSEMultilineControlSupported())
			{
				Status = (*control)->Methods->GetControlHeight( *control, (VOID*)frame,&height);
	   			height = height ? height:1;
			}
			*/
            //EIP-127577 End

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
// Name:		_FrameHandleKey
//
// Description: Controls Keyboard action for each frame 
//
// Input:		FRAME_DATA *frame - Pointer to the frame data
//				EFI_INPUT_KEY key - Key pressed in the keyboard
//
// Output:		EFI_STATUS Status - EFI_SUCCESS if successful, else
//										EFI_UNSUPPORTED
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS _FrameHandleKey( FRAME_DATA *frame, AMI_EFI_KEY_DATA key )
{
    EFI_STATUS Status = EFI_SUCCESS;
    CONTROL_ACTION Action;


    //Get mapping
    Action = MapControlKeysHook(key);

    switch (Action)
    {
        case ControlActionNextUp:
            Status = _FrameScroll( frame, TRUE);
            break;

        case ControlActionNextDown:
            Status = _FrameScroll( frame, FALSE);
            break;

		case ControlActionPageUp:
			Status = _PreviousFrame(frame);
			break;

		case ControlActionPageDown:
			Status = _NextFrame(frame);
			break;

		case ControlActionHome:
				Status = _FocusFirst(frame);
			break;

		case ControlActionEnd:
				Status = _FocusLast(frame);
			break;

		default:
			Status = EFI_UNSUPPORTED;
		break;
    }

//	if ( ! EFI_ERROR( Status ) )
//	{
//		if((TSEMouseIgnoreMouseActionHook())&&((frame->ControlList[frame->CurrentControl]->ControlData.ControlType != CONTROL_TYPE_DATE)&&(frame->ControlList[frame->CurrentControl]->ControlData.ControlType != CONTROL_TYPE_TIME)))
//			NumericSoftKbdExit();
//		if((!TSEMouseIgnoreMouseActionHook())&&((frame->ControlList[frame->CurrentControl]->ControlData.ControlType == CONTROL_TYPE_DATE)||(frame->ControlList[frame->CurrentControl]->ControlData.ControlType == CONTROL_TYPE_TIME)))
//			NumericSoftKbdInit();	
//	}
    return Status;
}



//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    _FrameScroll
//
// Description: Adds scroll bar functionality for frames with many controls
//
// Input:		FRAME_DATA *frame - Pointer to the frame data
//				BOOLEAN bScrollUp - Go up is TRUE, else to down one control
//
// Output:		EFI_STATUS Status - EFI_SUCCESS if successful, else
//										EFI_UNSUPPORTED
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS _FrameScroll( FRAME_DATA *frame, BOOLEAN bScrollUp )
{
	UINT32 thisControl = frame->CurrentControl;
	BOOLEAN bDone = FALSE;
	UINT32 *pOtherEnd = NULL;
    UINT8 u8ChkResult;

	if ( frame->ControlCount == 0 )
		return EFI_UNSUPPORTED;

    switch ( bScrollUp )
    {
        case TRUE:
            if (thisControl == FRAME_NONE_FOCUSED)
				thisControl = frame->FirstVisibleCtrl;

            if(thisControl < frame->FirstVisibleCtrl)
                thisControl = frame->FirstVisibleCtrl;

			//See if there are some controls that can be focused in the screen
			while (thisControl != frame->FirstVisibleCtrl)
			{
				thisControl--;
				if ( _FrameSetControlFocus( frame, thisControl ) )
				{
					bDone = TRUE;
					break;
				}
			}
			
			if (!bDone)
			{
				// No controls that can be focused is left move up til we find a unsuppressed control
                while(thisControl)
                {
                    thisControl--;

                    //EIP 75486 Support grayout condition for readonly controls
                    u8ChkResult = CheckControlCondition( &(frame->ControlList[thisControl]->ControlData) );
                    
                    if((COND_NONE == u8ChkResult) || (COND_GRAYOUT == u8ChkResult))
                    {
                        frame->FirstVisibleCtrl = thisControl;
  				    	pOtherEnd = &(frame->LastVisibleCtrl);
       					_FrameSetControlFocus( frame, thisControl);
                        bDone = TRUE;
                        break;
                    }
                }

                // If no control can be found roll to last visible page
				if (!bDone && StyleGetScrollBehavior())
                {
                    thisControl = frame->LastVisibleCtrl = frame->ControlCount;
    				do
                    {
                        thisControl--;

                        //EIP 75486 Support grayout condition for readonly controls
                        u8ChkResult = CheckControlCondition( &(frame->ControlList[thisControl]->ControlData) );
                        
                        if((COND_NONE == u8ChkResult) || (COND_GRAYOUT == u8ChkResult))
                        {
                            frame->LastVisibleCtrl = thisControl;
      				    	pOtherEnd = &(frame->FirstVisibleCtrl);
                            bDone = TRUE;
          					break;
                        }
    				}while(thisControl);
                }

                if(!bDone)
                {
                    //No control can be shown in this whole frame
					//Blaines EIP#13293
			if(StyleGetScrollBehavior())
                    		frame->FirstVisibleCtrl = frame->LastVisibleCtrl = 0;
                    return EFI_UNSUPPORTED;
                }
				
				// Calculate other end
				StyleFrameSetControlPositions(frame, pOtherEnd);

				if(pOtherEnd == &(frame->FirstVisibleCtrl))
				{
					//We rolled to last page; find if we can focus one
					while (thisControl >= frame->FirstVisibleCtrl)
					{
						if ( _FrameSetControlFocus( frame, thisControl ) )
						{
							break;
						}
                        if(thisControl == 0)
                            break;
						thisControl--;
					}
				}
					
				//De-focus if we have no control that can be focused in the screen
				if(frame->CurrentControl != FRAME_NONE_FOCUSED)
				{
					if((frame->CurrentControl < frame->FirstVisibleCtrl) || (frame->CurrentControl > frame->LastVisibleCtrl))
					{
						(frame->ControlList[frame->CurrentControl])->Methods->SetFocus(frame->ControlList[frame->CurrentControl],FALSE);
						frame->CurrentControl = FRAME_NONE_FOCUSED;
					}
				}				
			}
		break;

		case FALSE:
			if (thisControl == FRAME_NONE_FOCUSED)
				thisControl = frame->LastVisibleCtrl;

            if(thisControl > frame->LastVisibleCtrl)
                thisControl = frame->LastVisibleCtrl;

			//See if there are some controls that can be focused in the screen
			while (thisControl != frame->LastVisibleCtrl)
			{
				thisControl++;
				if ( _FrameSetControlFocus( frame, thisControl ) )
				{
					bDone = TRUE;
					break;
				}
			}
			
			if (!bDone)
			{
                // No controls that can be focused is left move down til we find an unsuppressed control
                while((frame->ControlCount - 1) != thisControl)
                {
                    thisControl++;

                    //EIP 75486 Support grayout condition for readonly controls
                    u8ChkResult = CheckControlCondition( &(frame->ControlList[thisControl]->ControlData) );
                    
                    if((COND_NONE == u8ChkResult) || (COND_GRAYOUT == u8ChkResult))
                    {
                        frame->LastVisibleCtrl = thisControl;
   				    	pOtherEnd = &(frame->FirstVisibleCtrl);
       					_FrameSetControlFocus( frame, thisControl);
                        bDone = TRUE;
                        break;
                    }
                }

                // If no control can be found roll to First visible page
				//EIP#13293
		        if (!bDone && StyleGetScrollBehavior())
       		    {
               		thisControl = frame->FirstVisibleCtrl = 0;
   			        while(thisControl < frame->ControlCount)
                    {
                        //EIP 75486 Support grayout condition for readonly controls
                        u8ChkResult = CheckControlCondition( &(frame->ControlList[thisControl]->ControlData) );

                        if((COND_NONE == u8ChkResult) || (COND_GRAYOUT == u8ChkResult))
                        {
                            //frame->FirstVisibleCtrl = thisControl;
      				    	pOtherEnd = &(frame->LastVisibleCtrl);
                            bDone = TRUE;
          					break;
                        }

                        if((thisControl + 1) == frame->ControlCount) //this while loop breaks here before while statement
                            break;
                        thisControl++;
    				}
                }

                if(!bDone)
                {
                    //No control can be shown in this whole frame
					//Blaines EIP#13293
					if(StyleGetScrollBehavior())
						frame->FirstVisibleCtrl = frame->LastVisibleCtrl = 0;
                    return EFI_UNSUPPORTED;
                }
					
				//Calculate other end
				StyleFrameSetControlPositions(frame, pOtherEnd);

				if(pOtherEnd == &(frame->LastVisibleCtrl))
				{
					//We rolled to First page; find if we can focus one
					while (thisControl <= frame->LastVisibleCtrl)
					{
						if ( _FrameSetControlFocus( frame, thisControl ) )
						{
							break;
						}
						thisControl++;
					}
				}
                    
				//De-focus if we have no control that can be focused in the screen
				if(frame->CurrentControl != FRAME_NONE_FOCUSED)
				{
					if((frame->CurrentControl < frame->FirstVisibleCtrl) || (frame->CurrentControl > frame->LastVisibleCtrl))
					{
						(frame->ControlList[frame->CurrentControl])->Methods->SetFocus(frame->ControlList[frame->CurrentControl],FALSE);
						frame->CurrentControl = FRAME_NONE_FOCUSED;
					}
				}
			}
		break;
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_FrameSubmenuCallback
//
// Description:	Function to set frame submenu callback.
//
// Input:		FRAME_DATA *frame, SUBMENU_DATA *submenu, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _FrameSubmenuCallback( FRAME_DATA *frame, SUBMENU_DATA *submenu, VOID *cookie )
{
	EFI_STATUS			Status = EFI_SUCCESS;
	CALLBACK_SUBMENU	*callbackData = (CALLBACK_SUBMENU *)cookie;

	if ( ( callbackData == NULL ) || ( callbackData->Header.Type != CALLBACK_TYPE_SUBMENU ) )
		return;

	if ( ! EFI_ERROR( Status ) )
	{
		gApp->CurrentPage = callbackData->DestPage;
//EIP: 55762 Start
		if(submenu->ControlData.DestQuestionID != 0){
			UINT32 FocusControlIndex = 0;
        
			Status = UpdateDestiantionQuestion(gApp->CurrentPage, submenu->ControlData.DestQuestionID, &FocusControlIndex);
			if(Status == EFI_SUCCESS){
				UINT32 MainFrameIndex = 0;		
				FRAME_DATA *MainFrame = NULL;
				PAGE_DATA *pageData = gApp->PageList[gApp->CurrentPage];
				MainFrameIndex = StyleFrameIndexOf(MAIN_FRAME); 
				MainFrame = pageData->FrameList[MainFrameIndex];
				_FrameSetControlFocus(MainFrame, FocusControlIndex);
			}
		}
	}
//EIP: 55762 End
	gApp->CompleteRedraw = TRUE;
	gApp->OnRedraw = SUBMENU_COMPLETE_REDRAW;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_FrameMenuCallback
//
// Description:	Function to set frame menu callback.
//
// Input:		FRAME_DATA *frame, MENU_DATA *menu, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _FrameMenuCallback( FRAME_DATA *frame, MENU_DATA *menu, VOID *cookie )
{
	EFI_STATUS			Status = EFI_SUCCESS;
	CALLBACK_MENU	*callbackData = (CALLBACK_MENU *)cookie;

	if ( ( callbackData == NULL ) || ( callbackData->Header.Type != CALLBACK_TYPE_MENU ) )
		return;

	if ( ! EFI_ERROR( Status ) )
		gApp->CurrentPage = callbackData->DestPage;
	gApp->CompleteRedraw = TRUE;
	gApp->OnRedraw = MENU_COMPLETE_REDRAW;
//EIP: 58925 Start
    if(IsLinkHistorySupport())
    {            
	    ResetNavStack();
    }
//EIP: 58925 End
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_FrameVariableCallback
//
// Description:	Function to set frame variable callback.
//
// Input:		FRAME_DATA *frame, CONTROL_DATA *control, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _FrameVariableCallback( FRAME_DATA *frame, CONTROL_DATA *control, VOID *cookie )
{
	CALLBACK_VARIABLE *callbackData = (CALLBACK_VARIABLE *)cookie;

	if ( ( callbackData == NULL ) || ( callbackData->Header.Type != CALLBACK_TYPE_VARIABLE ) )
		return;

	if ( callbackData->Variable >= gVariables->VariableCount )
		return;

	VarSetValue( callbackData->Variable, callbackData->Offset, callbackData->Length, callbackData->Data );

	if ( control->ControlData.ControlFlags.ControlReset )
		gResetRequired = TRUE;

}
BOOLEAN TSEPwdSavetoNvram(VOID);//EIP 93881 & 93873 : Save pwd to nvram and not loading empty pwd on loading defaults.
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_FramePasswordCallback
//
// Description:	Function to set frame password callback.
//
// Input:		FRAME_DATA *frame, CONTROL_DATA *control, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _FramePasswordCallback( FRAME_DATA *frame, CONTROL_DATA *control, VOID *cookie )
{
	CALLBACK_PASSWORD *callbackData = (CALLBACK_PASSWORD *)cookie;
	CHAR16 *saveData = NULL;

	if ( ( callbackData == NULL ) || ( callbackData->Header.Type != CALLBACK_TYPE_PASSWORD ) )
		return;

	if ( callbackData->Variable >= gVariables->VariableCount )
		return;

	saveData = (CHAR16 *)callbackData->Data;

	if(FramePwdCallbackIdePasswordUpdate ( control,saveData) != EFI_SUCCESS)
	{
//EIP 23354 : Start
        if( IsPasswordEncodeEnabled(&control->ControlData) )
    		saveData = PasswordUpdate( callbackData->Data, callbackData->Length);
//EIP 23354 : End
    
        if ( saveData )
        {
//EIP 93881 & 93873 : Save pwd to nvram and not loading empty pwd on loading defaults.
				if((TSEPwdSavetoNvram())&&( VARIABLE_ID_AMITSESETUP == callbackData->Variable ))
				{
				   AMITSESETUP *TempSaveData = (AMITSESETUP *)NULL;
					UINTN size=0;
					TempSaveData = (AMITSESETUP *) EfiLibAllocateZeroPool(sizeof(AMITSESETUP));
					size = sizeof(AMITSESETUP);
	
					TempSaveData = VarGetNvram(VARIABLE_ID_AMITSESETUP, &size);
					MemCopy( ((UINT8*)(TempSaveData))+(callbackData->Offset), saveData, callbackData->Length );
					VarSetNvram( VARIABLE_ID_AMITSESETUP, TempSaveData, sizeof(AMITSESETUP));
					MemFreePointer( (VOID **)&TempSaveData );	       	
				}
				else
        	 		VarSetValue( callbackData->Variable, callbackData->Offset, callbackData->Length, saveData );

			FramePasswordAdvancedCallback(callbackData,saveData);
        }

    	if ( saveData != callbackData->Data )
    		MemFreePointer( (VOID **)&saveData );
	}

	if ( control->ControlData.ControlFlags.ControlReset )
		gResetRequired = TRUE;

}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    _FrameSetControlFocus
//
// Description: Sets focus on a defined control in the frame 
//
// Input:		 FRAME_DATA *frame - Date for a specific frame
//				 UINT32 index - Index of the control
//
// Output:		 BOOLEAN focusSet - TRUE if focus is set, FALSE otherwise
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN _FrameSetControlFocus( FRAME_DATA *frame, UINT32 index )
{
	CONTROL_DATA *control;
	BOOLEAN focusSet = FALSE;

	if ( frame->ControlCount <= index )
		return focusSet;

	control = frame->ControlList[index];
	focusSet = (BOOLEAN)(control->Methods->SetFocus( control, TRUE ) == EFI_SUCCESS);

	// de-focus all other controls
	if ( focusSet )
	{
		UINT32 i;

		for ( i = 0; i < frame->ControlCount; i++ )
		{
			if ( i == index )
				continue;
			control = frame->ControlList[i];
			control->Methods->SetFocus( control, FALSE );
		}

		frame->CurrentControl = index;
	}

	return focusSet;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    _FrameAddControls
//
// Description:	Function to add controls in the frame 
//
// Input:		 FRAME_DATA *frame, PAGE_INFO *data
//				 
//
// Output:		 STATUS
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _FrameAddControls( FRAME_DATA *frame, PAGE_INFO *data )
{
	EFI_STATUS	Status = EFI_INVALID_PARAMETER;
	UINT32 i, controlNumber = 0;
	BOOLEAN focusSet = FALSE;

	for ( i = 0; i < data->PageControls.ControlCount; i++ )
	{
		Status = gFrame.AddControl( frame,  (CONTROL_INFO *) ((UINT8 *)gControlInfo + data->PageControls.ControlList[i]) );
		if ( EFI_ERROR(Status) )
			continue;

		if ( ! focusSet )
		{
			if ( _FrameSetControlFocus( frame, controlNumber ) )
			{
				frame->CurrentControl = controlNumber;
				focusSet = TRUE;
			}
		}
		controlNumber++;
	}

	Status = StyleAddAdditionalControls( frame, controlNumber, focusSet );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_FrameAddTitle
//
// Description:	Function to add tittle to a frame.
//
// Input:	FRAME_DATA *frame, UINT32 frameNumber, PAGE_INFO *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _FrameAddTitle( FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	CONTROL_DATA **control;
	CONTROL_INFO dummy;
	UINT8 BORDER = (frame->FrameData.Border==TRUE)?1:0 ;

	UINT8 SPACER = 0 ;


	control = EfiLibAllocateZeroPool( sizeof(CONTROL_INFO *) );
	if ( control == NULL )
		return EFI_OUT_OF_RESOURCES;

	frame->ControlList = control;
	Status = gMemo.Create( control );

	if ( EFI_ERROR( Status ) )
		return Status;

	MemSet( &dummy, sizeof(dummy), 0 );
	dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;
	dummy.ControlFlags.ControlVisible = TRUE;
    dummy.ControlType = CONTROL_TYPE_MEMO;

	switch ( frameType )
	{
		case TITLE_FRAME:
			dummy.ControlPtr = (VOID*)gTitle;
			break;
		case HELP_FRAME:
			dummy.ControlPtr = (VOID*)gHelp;
			SPACER = 1 ;
			break;
		case SUBTITLE_FRAME:
			dummy.ControlPtr = (VOID*)gSubTitle;
			break;
		case HELPTITLE_FRAME:
			dummy.ControlPtr = (VOID*)gHelpTitle;
			break;
		case NAV_FRAME:
			dummy.ControlPtr = (VOID*)gNavStrings;
			break;
		default:
			if(StyleFrameAddTitle(frame, frameType,&dummy) != EFI_SUCCESS)
			{
				gMemo.Destroy( *control, TRUE );
				return EFI_UNSUPPORTED;
			}
	}

	(*control)->ParentFrameType = frame->FrameData.FrameType ;
	gMemo.Initialize( *control, &dummy );
	gMemo.SetPosition( *control, frame->FrameData.Left+BORDER, frame->FrameData.Top+BORDER );
	gMemo.SetDimensions( *control, frame->FrameData.Width-SPACER-2*BORDER, frame->FrameData.Height-2*BORDER );
	gMemo.SetAttributes( *control, frame->FrameData.FGColor, frame->FrameData.BGColor );
	if((IsMouseSupported()) && (frameType == NAV_FRAME))
	{	
		(*control)->FGColor = FOCUS_COLOR;
	}
	frame->ControlCount++;
	

	return Status;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     _PreviousFrame
//
// Description:  Loads the controls from the previous frame into the screen.
//
// Input:    FRAME_DATA *frame = Pointer to the current frame
//
// Output: EFI_STATUS status - 
//					EFI_SUCCESS - If there exists a previous page and the 
//								   function successfully loads it				
//					EFI_OUT_PF_RESOURCES - If there are know previous page
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS _PreviousFrame (FRAME_DATA *frame)
{
	UINT32 thisControl;
	BOOLEAN bFocused;
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if(frame->FirstVisibleCtrl > 0)
	{
		//return EFI_UNSUPPORTED;

		frame->LastVisibleCtrl = frame->FirstVisibleCtrl-1;
		StyleFrameSetControlPositions(frame, &(frame->FirstVisibleCtrl));


		if(frame->FirstVisibleCtrl<=0)
		{
			StyleFrameSetControlPositions(frame, &(frame->LastVisibleCtrl));
		}
	}

	
	//Focus a control if possible
	thisControl = frame->FirstVisibleCtrl;
	bFocused = FALSE;
	while (thisControl <= frame->LastVisibleCtrl)
	{
		if ( _FrameSetControlFocus( frame, thisControl ) )
		{
			bFocused = TRUE;
			break;
		}
		thisControl++;
	}

	if (!bFocused)
		frame->CurrentControl = FRAME_NONE_FOCUSED;

	Status = EFI_SUCCESS ;

	return Status;
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:		 _NextFrame
//
// Description:  Loads the controls from the next frame into the screen.
//
// Input:    FRAME_DATA *frame = Pointer to the current frame
//
// Output: EFI_STATUS status - 
//					EFI_SUCCESS - If there exists a next page and the 
//								   function successfully loads it				
//					EFI_OUT_PF_RESOURCES - If there are know previous page
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _NextFrame (FRAME_DATA *frame)
{
	UINT32 thisControl;
	BOOLEAN bFocused;

    if(frame->LastVisibleCtrl < (frame->ControlCount-1))
	{
		//return EFI_UNSUPPORTED;
		frame->FirstVisibleCtrl = frame->LastVisibleCtrl + 1;

	StyleFrameSetControlPositions(frame, &(frame->LastVisibleCtrl));

		if(frame->LastVisibleCtrl>=(frame->ControlCount-1))
		{
			StyleFrameSetControlPositions(frame, &(frame->FirstVisibleCtrl));
		}
	}
	

	//Focus a control if possible
	/*
	thisControl = frame->FirstVisibleCtrl;
	bFocused = FALSE;
	while (thisControl <= frame->LastVisibleCtrl)
	{
		if ( _FrameSetControlFocus( frame, thisControl ) )
		{
			bFocused = TRUE;
			break;
		}
		thisControl++;
	}
	*/

	//EIP#13118 Set Focus to bottom of page on PageDown 
	thisControl = frame->LastVisibleCtrl;
	bFocused = FALSE;
	while (thisControl >= frame->FirstVisibleCtrl)
	{
		if ( _FrameSetControlFocus( frame, thisControl ) )
		{
			bFocused = TRUE;
			break;
		}
		//EIP:31606 - Fix for hanging issue in case of no active controls in a frame
		if (thisControl == 0)
			break;

		thisControl--;
	}

	if (!bFocused)
		frame->CurrentControl = FRAME_NONE_FOCUSED;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     _FocusFirst
//
// Description:  Set focus to the first control in the frame (in the first page). 
//
// Input:    FRAME_DATA *frame = Pointer to the current frame
//
// Output: EFI_STATUS status - 
//					EFI_SUCCESS - If there exists a previous page and the 
//								   function successfully loads it				
//					EFI_OUT_PF_RESOURCES - If there are know previous page
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS _FocusFirst (FRAME_DATA *frame)
{
	EFI_STATUS Status = EFI_SUCCESS;

	do
	{	//At least once in case there's less than a page
		Status = _PreviousFrame(frame);

	}while(frame->FirstVisibleCtrl > 0);
	
	
	return Status;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     _FocusLast
//
// Description:  Set focus to the last control in the frame. 
//
// Input:    FRAME_DATA *frame = Pointer to the current frame
//
// Output: EFI_STATUS status - 
//					EFI_SUCCESS - If there exists a previous page and the 
//								   function successfully loads it				
//					EFI_OUT_PF_RESOURCES - If there are know previous page
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS _FocusLast (FRAME_DATA *frame)
{
	
	EFI_STATUS Status = EFI_SUCCESS;

	do
	{   //At least once in case there's less than a page
		Status = _NextFrame(frame);

	}while(frame->LastVisibleCtrl < (frame->ControlCount-1));

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_FrameHandleMouse
//
// Description:	Function to hadnle frame using mouse
//
// Input:		FRAME_DATA *frame,
//				MOUSE_INFO MouseInfo 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _FrameHandleMouse( FRAME_DATA *frame,MOUSE_INFO MouseInfo)
{	
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT32 i, Action;
	
	Action = MapControlMouseActionHook(&MouseInfo);
	//if(TSEMOUSE_RIGHT_CLICK == MouseInfo.ButtonStatus)
	if(ControlActionAbort == Action)
		return Status;	

   if ( frame->ControlCount == 0 )
		return Status;
	
	//Reset lbutton positions
	if (ControlMouseActionLeftUp == Action || ControlActionChoose == Action || ControlActionSelect == Action)
	{
		lButtonDownInitialPosition = 0;
		lButtonDownVaringPosition = 0;
	}	

   //For Handling Frame Scroll Bar using Mouse
	if(frame->UseScrollbar)
	{
		//If clicked on scrollbar area
		if(MouseInfo.Left == (UINT32) frame->FrameData.Left + frame->FrameData.Width)
		{
			//If clicked on UP_ARROW
			if( (MouseInfo.Top == frame->FrameData.Top) /*Arrow Up*/ 
				  &&((TSEMOUSE_LEFT_CLICK == MouseInfo.ButtonStatus)||(TSEMOUSE_LEFT_DCLICK == MouseInfo.ButtonStatus))//EIP 78929  : Check for left click and left double click to scroll the frame if click on arrow buttons of scroll bar.   			
				)
				MouseScrollBarMove( frame, TRUE, 1 );

			//If clicked on DOWN_ARROW			
			else if( ( MouseInfo.Top == (UINT32) (frame->FrameData.Top + frame->FrameData.Height -2) || MouseInfo.Top == (UINT32) (frame->FrameData.Top + frame->FrameData.Height -3) ) //EIP:48377 Coordinates of Mouse click down arrow operation are updated to work for GTSE and AMITSE. 
						&&((TSEMOUSE_LEFT_CLICK == MouseInfo.ButtonStatus)||(TSEMOUSE_LEFT_DCLICK == MouseInfo.ButtonStatus))//EIP 78929  : Check for left click and left double click to scroll the frame if click on arrow buttons of scroll bar.
					)
				 MouseScrollBarMove( frame, FALSE, 1 );
				
			//If mouse clicked below UP_ARROW and above ScrollBar
			else if( (MouseInfo.Top <= gFrameScrollBarTop) //Clicked  above scrollbar
						&& (MouseInfo.Top > frame->FrameData.Top) //Clicked below UP_ARROW
						&& (ControlMouseActionLeftDown == Action)
					)
			{
				MouseScrollBarMove( frame, TRUE, gFrameScrollBarTop-MouseInfo.Top+1 );				
			}

			//If mouse clicked on scrollbar
			else if( (MouseInfo.Top < gFrameScrollBarBottom) && (MouseInfo.Top > gFrameScrollBarTop) //Clicked on ScrollBar area
						&& (ControlMouseActionLeftDown == Action) // Clicked lbutton down
						&&	((ControlActionChoose != Action) || (ControlActionSelect != Action)) //Neglecting LEFT_DCLICK and LEFT_CLICK on scrollbar area
					)
			{
				if ( lButtonDownInitialPosition == 0 )//To get initial lButtonDown position
				{
					lButtonDownInitialPosition = MouseInfo.Top;
				}
				if ( lButtonDownInitialPosition != MouseInfo.Top )
				{
					lButtonDownVaringPosition = MouseInfo.Top;
					//Move scrollbar upwards
					if( lButtonDownInitialPosition > lButtonDownVaringPosition )
						MouseScrollBarMove( frame, TRUE, lButtonDownInitialPosition - lButtonDownVaringPosition );

					//Move scrollbar downwards
					else
						MouseScrollBarMove( frame, FALSE, lButtonDownVaringPosition - lButtonDownInitialPosition );
					lButtonDownInitialPosition = lButtonDownVaringPosition;
				}
				return EFI_SUCCESS;
			}
			
			//If mouse clicked above DOWN_ARROW and below ScrollBar
			else if( (MouseInfo.Top >= gFrameScrollBarBottom)
						&& (MouseInfo.Top < (UINT32) (frame->FrameData.Top + frame->FrameData.Height -2))
						&& (ControlMouseActionLeftDown == Action)
					)
			{
				MouseScrollBarMove( frame, FALSE, MouseInfo.Top-gFrameScrollBarBottom + 1 );
			}
			return EFI_SUCCESS;
		}
		//If mouse button clicked on scrollbar and moved outside the scroll area
		else if( ControlMouseActionLeftDown == Action
					&& (lButtonDownInitialPosition != 0)
					&& ((ControlActionChoose != Action) || (ControlActionSelect != Action)) 
		)
		{
			lButtonDownVaringPosition = MouseInfo.Top;
			//Move scrollbar upwards
			if( lButtonDownInitialPosition > lButtonDownVaringPosition )
				MouseScrollBarMove( frame, TRUE, lButtonDownInitialPosition - lButtonDownVaringPosition );

			//Move scrollbar downwards
			else
				MouseScrollBarMove( frame, FALSE, lButtonDownVaringPosition - lButtonDownInitialPosition );
			lButtonDownInitialPosition = lButtonDownVaringPosition;
			
			//Reset lButtonDown position when lButton releases
			if (ControlMouseActionLeftUp == Action)
			{
				lButtonDownInitialPosition = lButtonDownVaringPosition = 0;
			}
			return EFI_SUCCESS;
		}
   }
		
	//If mouse clicked on frame without scrollbar support
   if(!((MouseInfo.Top >= (UINT32)frame->FrameData.Top) && (MouseInfo.Left > (UINT32)(frame->FrameData.Width+1) )) //Clicked other than scrollbar area
		&& (ControlMouseActionLeftUp != Action) //Neglecting LEFT_UP action
		)
   {
		//Find control that was clicked
	   for(i=frame->FirstVisibleCtrl; i<=frame->LastVisibleCtrl; i++)
	   {
			if( (MouseInfo.Top >= frame->ControlList[i]->Top) && (MouseInfo.Top < (UINT32)(frame->ControlList[i]->Top + frame->ControlList[i]->Height)) )
	      {
	         //This is the control; select it.
				if ( _FrameSetControlFocus( frame, i ) )
				{
				//	if((TSEMouseIgnoreMouseActionHook())&&((frame->ControlList[i]->ControlData.ControlType != CONTROL_TYPE_DATE)&&(frame->ControlList[i]->ControlData.ControlType != CONTROL_TYPE_TIME)))
				//		NumericSoftKbdExit();
				//	if((!TSEMouseIgnoreMouseActionHook())&&((frame->ControlList[i]->ControlData.ControlType == CONTROL_TYPE_DATE)||(frame->ControlList[i]->ControlData.ControlType == CONTROL_TYPE_TIME)))
				//		 NumericSoftKbdInit();				
						 Status = EFI_SUCCESS;
					break;
				}
	      }
	   }
   }
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseFrameHandleAction
//
// Description:	Function to hadnle frame using mouse
//
// Input:		FRAME_DATA *frame, 
//				ACTION_DATA *action,
//				CONTROL_DATA **control 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEMouseFrameHandleAction( FRAME_DATA *frame, ACTION_DATA *action,CONTROL_DATA **control )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if( (action->Input.Data.MouseInfo.Top >= (UINT32)frame->FrameData.Top) && (action->Input.Data.MouseInfo.Left > (UINT32)(frame->FrameData.Width+1) ) )
	{
		 TSEMouseHelpFrameHandleAction(frame, action, control);
	}
	 
		//EIP-123727 check whether Current Control is with in the Visible Area or not.
		if ( control != NULL  && (frame->CurrentControl >= frame->FirstVisibleCtrl && frame->CurrentControl <= frame->LastVisibleCtrl))
			Status = (*control)->Methods->HandleAction( *control, action );


    if (EFI_ERROR(Status))
    	Status = StyleFrameHandleMouse( frame, action->Input.Data.MouseInfo );

	//EIP76810 : Ckecking Inconsistence for the current control
	if (EFI_ERROR(Status))
	{
		if( CheckInconsistence((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[gApp->CurrentPage])) )
			if ( action->Input.Type != ACTION_TYPE_NULL )
				gAction.ClearAction( action );

	}

    if (EFI_ERROR(Status))
        Status = _FrameHandleMouse( frame, action->Input.Data.MouseInfo);

    return Status;
}

//EIP:62098 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseHelpFrameHandleAction
//
// Description:	Function to hadnle help frame using mouse
//
// Input:		FRAME_DATA *frame, 
//				ACTION_DATA *action,
//				CONTROL_DATA **control 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEMouseHelpFrameHandleAction( FRAME_DATA *frame, ACTION_DATA *action,CONTROL_DATA **control )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	MEMO_DATA *memo;
	BOOLEAN bScrollBar = FALSE;
	CHAR16 *text = NULL;
	UINT16 height = 0;
	
	control = frame->ControlList;
	control = control+ frame->FirstVisibleCtrl;
	memo = (MEMO_DATA *) *control;
	
	if( memo->ParentFrameType != HELP_FRAME )
	 return Status;
	else
	{	
		text = HiiGetString( memo->ControlData.ControlHandle,UefiGetTitleField( (VOID *)memo->ControlData.ControlPtr));

		if ( text == NULL )
		return Status;

		if ( EfiStrLen(text) == 0)
    		{
       			 // String is empty but memory is allocated.
			MemFreePointer( (VOID **)&text );
			return Status;
    		}

		// clear out old wrapped string
		//EIP-131365 Here gActiveBuffer will update with EmptyString and clear HelpFrame characters. This causes help area flickers when mouse action happens.
		//for ( pos = 0; pos < memo->Height; pos++ )		
		//DrawStringWithAttribute( memo->Left, memo->Top + pos, memo->EmptyString, memo->FGColor | memo->BGColor );
		
		// XXX: this wrapping code is probably not compatible with all languages
		StringWrapText( text, memo->Width, &height );
		if(height == 0)
			return Status;
		
		bScrollBar = ( (height > memo->Height) && (memo->ParentFrameType == HELP_FRAME /*memo->Top == MAIN_TOP*/)  ) ? 1 : 0;
		
		if(bScrollBar && (action->Input.Data.MouseInfo.ButtonStatus == TSEMOUSE_LEFT_CLICK))
		{
		
			if((action->Input.Data.MouseInfo.Top == (frame->FrameData.Top + frame->FrameData.Height -1))&&(action->Input.Data.MouseInfo.Left == frame->FrameData.Width + frame->FrameData.Left -1 ))
				 	_HelpFrameScroll( memo, FALSE);
			
			if(((action->Input.Data.MouseInfo.Top == frame->FrameData.Top) ||(action->Input.Data.MouseInfo.Top == frame->FrameData.Top -1))
			   && (action->Input.Data.MouseInfo.Left == frame->FrameData.Width + frame->FrameData.Left -1) )
					_HelpFrameScroll( memo, TRUE);
					

		}
		else
		return Status;
	}

	return Status;
	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_HelpFrameScroll
//
// Description:	Function to hadnle help frame scroll using mouse
//
// Input:		FRAME_DATA *frame, 
//				ACTION_DATA *action,
//				CONTROL_DATA **control 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _HelpFrameScroll(MEMO_DATA *memo,BOOLEAN bScrollUp)
{
	switch(bScrollUp)
	{
		
	case FALSE:
		if( memo->ParentFrameType == HELP_FRAME)
		{
			// Incrementing the ScrollBarPosition.
			memo->ScrollBarPosition++;
			// Based upon ScrollBarPosition drawing the Memo again.
			gMemo.Draw(memo);
		}
            break;

	case TRUE:
		if( memo->ParentFrameType == HELP_FRAME)
		{
			// Decrementing ScrollBarPosition
			if( memo->ScrollBarPosition != 0 )
				memo->ScrollBarPosition--;
			else
				memo->ScrollBarPosition = 0;
				gMemo.Draw(memo);
		}
            break;
	default:
		return ;			
	}

}
//EIP:62098 END

//EIP-67049 Start
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    TSEMouseScrollBarMove
//
// Description: Adds scroll bar functionality for frames with many controls
//
// Input:		FRAME_DATA *frame - Pointer to the frame data
//				BOOLEAN bScrollUp - Go up is TRUE, else to down one control
//
// Output:		EFI_STATUS Status - EFI_SUCCESS if successful, else
//										EFI_UNSUPPORTED
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS TSEMouseScrollBarMove( FRAME_DATA *frame, BOOLEAN bScrollUp, UINT32 Size )
{	
	CONTROL_DATA *control=NULL;
	UINTN  i=0,IndexOfLastNonSupressctrl=0;
	UINT8 u8ChkResult;
	 
	if ( frame->ControlCount == 0 )
		return EFI_UNSUPPORTED;

	switch ( bScrollUp )
	{
		case TRUE:

			if( Size >= frame->FirstVisibleCtrl )
				Size = frame->FirstVisibleCtrl;
			//If FirstVisibleCtrl is not equal to first control then move scrollbar till it reaches top
			if(frame->FirstVisibleCtrl > 0)
			{
				frame->FirstVisibleCtrl = frame->FirstVisibleCtrl - Size;
				frame->LastVisibleCtrl = frame->LastVisibleCtrl - Size;
			}
			break;

		case FALSE:
			//If the size of scroll to move exceeds the remaining control count then change the size value based on the remaining control count
			if( Size >= (frame->ControlCount - frame->LastVisibleCtrl) )
				Size = frame->ControlCount - frame->LastVisibleCtrl - 1;
			//get the Index of the Last Non Supress Ctrl in the Frame
			for ( i = 0; i < frame->ControlCount; i++ )
				{
					
					control = frame->ControlList[i];
					if(control != NULL)
						{
						//Check conditional
						u8ChkResult = CheckControlCondition(&(control->ControlData ));
						if(COND_SUPPRESS != u8ChkResult )
							IndexOfLastNonSupressctrl=i;
						else
							continue;
						}
				}
			//If LastVisibleCtrl is not equal to last control then move scrollbar till it reaches bottom
			if(frame->LastVisibleCtrl < frame->ControlCount-1 && IndexOfLastNonSupressctrl != frame->LastVisibleCtrl)
			{
				frame->FirstVisibleCtrl = frame->FirstVisibleCtrl + Size;
				frame->LastVisibleCtrl = frame->LastVisibleCtrl + Size;
			}
			break;
	}
	return EFI_SUCCESS;
}
//EIP-67049 End

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
