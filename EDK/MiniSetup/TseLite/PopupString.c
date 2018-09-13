//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2014, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupString.c $
//
// $Author: Premkumara $
//
// $Revision: 42 $
//
// $Date: 8/28/14 3:04p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupString.c $
// 
// 42    8/28/14 3:04p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 41    8/28/14 12:44p Premkumara
// [TAG] EIP177886
// [Category] Bug Fix
// [Severity:] Normal
// [Symptom:] Mouse pointer flicker continuously when softkbd is launched
// for string control
// [Root Cause] MouseRefresh() function is been called continuously when
// popupedit is launched
// [Solution] Calling MouseRefresh() function only when mouse pointer is
// on Edit area or over cursor
// [Files] PopupString.c
// 
// 40    5/02/14 9:41p Arunsb
// EIP141986 changes reverted.
// 
// 39    5/02/14 10:52a Premkumara
// [TAG]  		EIP141986
// [Category]  	New Feature
// [Description]  	Made Grayed controls to focus-able when token
// TSE_SETUP_GRAYOUT_SELECTABLE
//  is enabled and can't edit the values
// [Files]  		AMITSE.sdl,CommonHelper.c,frame.c,Label.c,minisetupext.h,
// numeric.c,PopupPassword.c,PopupSel.c,PopupString.c,SubMenu.c
// 
// 38    5/01/14 3:45p Premkumara
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
// 37    2/11/14 8:39p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 36    12/03/13 2:15p Premkumara
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
// 35    12/03/13 1:13p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 34    7/01/13 9:41a Premkumara
// [TAG]  		EIP127021
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Clearing string in interactive String control causes setup
// crash
// [RootCause]  	Memory for PopupString->Text is allocated with length of
// typed string and trying to get current string using PopupString max
// value size in VarGetValue() function
// [Solution]  	Allocating PopupString->Text properly based on popupstring
// max value once string is cleared
// [Files]  		PopupString.c
// 
// 33    5/22/13 11:03a Premkumara
// [TAG]  		EIP123432 
// [Category]  	Bug Fix
// [Issue Faced]            Take print screen for save & Exit msg box. OK
// of msg box is consumed by Save & Exit msg box.
// 		- Cursor is missing after taking print screen of popupedit box in
// string control
// 		- Printscreen support is not given for Filebrowser feature
// [RootCause]  	- When msg box for Save&Exit is popped and printscreen
// event is called and displaying msg box over Save&Exit. Then msgbox
// handleaction for printscreen event will change the result value in
// _CallbackMsgbox() function so it will break the while loop in
// _CallbackGetValue() function so destroy the next msg box in
// CallbackShowMessageBox() function.
// 		- DrawCursor variable is not set to TRUE after printscreen event
// [Solution]  	- Returning EFI_UNSUPPORTED for printscreen event handling
// function for messgebox and change the result value to 0xff
// 		- Support given for file browser feature
// [Files]  		Callback.c, MessageBox.c, Minisetupext.c, PopupString.c,
// AddBootOption.c
// 		AmiTSEStr.uni, FakeToken.c 
// 
// 32    4/17/13 12:04p Arunsb
// EIP118949; Commented error messagebox in interactive callback failure
// case.
// 
// 31    2/22/13 12:46p Blaines
// [TAG] - EIP 115724 
// [Category]- Defect 
// [Symptom]- Multiline support for Hii String control does not wrap the
// string in some cases issues.
// 
// [Root cause]
// In the functions PopupStringGetControlHeight and PopupStringDraw,
// the computed width of the right column is incorrect, 
// causing the height to be 1, defaulting to string truncation.
// 
// [Files] 
//   -  PopupString.c
// 
// [Functions]
// - PopupStringDraw 
// - PopupStringGetControlHeight
// 
// 30    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 19    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 28    9/17/12 6:20a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 26    8/29/12 8:32a Premkumara
// [TAG]  		EIP 91364
// [Category]  	Improvement
// [Description]  	Token to disable the Cursor of TSE Password Dialog
// [Files]  		AMITSE.sdl, CommonHelper.c, Postmgmtext.c, PopupPassword.c,
// PopupString.c
// 
// 25    5/25/12 2:42a Premkumara
// [TAG]  		EIP90894
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Assert happening in Add/Del Boot/Driver option
// [RootCause]  	PopupString->Textwidth is not handled properly when empty
// string is entered
// [Solution]  	Handled PopupString->Textwidth properly
// [Files]  		PopupString.c
// 
// 24    4/27/12 2:42a Rajashakerg
// [TAG]  		EIP86346 
// [Category]  	Improvement
// [Description]  	Cursor visibility is not proper in multiline string
// controls
// [Files]  		PopupEdit.c, PopupString.c
// 
// 23    11/30/11 11:28a Premkumara
// [TAG]  		EIP67695
// [Category]  	Improvement
// [Description]  	No cursor visible in setup, while editing text input
// box
// [Files]  		Buffer.c, Postmgmtext.c, PopupString.c, PopupPassword.c
// 
// 22    11/21/11 11:08a Premkumara
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
// 21    11/21/11 8:58a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupString.c, SubMenu.c, Text.c.
// 
// 20    11/16/11 7:58a Premkumara
// [TAG]  		EIP75522 & 75517
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Accepts invalid String for string control, mismatch in
// string length
// [RootCause]  	Invalid strings are not validated using
// CallbackShowMessageBox() function.
// Improper in PopupString->textwidth before and after string entered.
// Previous string is not retained.
// [Solution]  	- Displaying Invalid error message for invalid string by
// calling CallbackShowMessageBox() function
// - PopupString->Textwidth is handled proper
// 
// [Files]  		PopupString.c
// 
// 19    11/14/11 6:55p Blaines
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
// 18    8/26/11 2:10p Blaines
// [TAG]  		EIP 67487
// [Category]  	Defect
// [Symptom]  	TSE_MULTILINE_CONTROLS does not work for all control types
// [RootCause]  	The controls (PopupSel,  PopupString) ONLY check for
// string wrapping in the label value (control prompt) when calling the
// methods GetControlHeight and Draw. 
// [Solution]	The controls (PopupSel,  PopupString) should check for
// string wrapping in the label (control prompt) and the control's value
// when calling the methods GetControlHeight and Draw. For Dynamic pages,
// adjust the width calculation for Submenu in the function
// GetControlHeight.
// [Files]  		PopupSel.c, PopupString.c, Submenu.c
// 
// 17    6/23/11 3:52p Rajashakerg
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
// 16    3/28/11 9:25p Madhans
// [TAG]  		EIP41744 
// [Category]  	Improvement
// [Description]  	SoftKeyBoard Support in TSE. and Support to Work with
// new mouse driver(Label 07).
// [Files]  		HookAnchor.h
// AMITSE.sdl
// CommonHelper.c
// commonoem.c
// commonoem.h
// HookList.c
// HookAnchor.c
// Mouse.c
// minisetupext.c
// postmgmtext.c
// minisetupext.h
// PopupPassword.c
// PopupString.c
// TseLiteCommon.c
// 
// 15    3/21/11 12:42a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 14    3/09/11 7:23p Madhans
// [TAG]  		EIP48615  
// [Category]  	Improvement
// [Description]  	To support UEFI 2.1 RefreshOp. Based in Refersh Rate
// Controls are refershed periodically.
// [Files]  		minisetupext.h
// SubMenu.h
// SubMenu.c
// Memo.c
// Memo.h
// numeric.c
// numeric.h
// time.c
// Date.c
// PopupSel.c
// PopupSel.h
// PopupString.c
// PopupString.h
// ordlistbox.c
// minisetupext.c
// UefiAction.c
// hii.h
// Uefi20wapper.c
// hiicallback.c
// Parse.c
// tseuefihii.h
// Uefi21wapper.c
// 
// 13    12/29/10 9:40a Mallikarjunanv
// [TAG]  		EIP51143
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	popup string value field is not grayed out even if the
// grayoutif condition satisfies.
// [RootCause]  	Not handled the color selection for grayout control in
// case of popupstring.
// [Solution]  	Fixed the issue by setting the color to grayout in case of
// a grayout popupsting control. 
// 
// [Files]  		PopupString.c
// 
// 11    12/26/10 4:16p Mallikarjunanv
// [TAG]  		EIP48387
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Displayed message as "Invalid input range" for the
// specified string as boot option name (for eg., "aaaa").
// [RootCause]  	In case of pressing ECS key the string length of Popup
// string is not considered.
// [Solution]  	Fixed the issue by handling Report message box display
// with
// respect to Popup string text.
// [Files]  		PopupString.c
// 
// 10    12/02/10 6:08p Madhans
// [TAG] - EIP49562    
// [Category]- Improvment.
// [Severity]- Mordarate
// [Symptom]- Need to support UEFI 2.2 requirements related to Calling
// Formcallback with 
// EFI_BROWSER_ACTION_CHANGING and EFI_BROWSER_ACTION_CHANGED action.
// [Solution]- Implemented the support.
// [Files] - submenu.c, numeric.c, popupsel.c, popupString.c,
// uefi20\hii.h, uefi20\uefi20wrapper.c
// uefi21\hiicalback.c, uefi21\tseuefihii.h
// 
// 9     12/02/10 2:34p Madhans
// [TAG] - EIP 48169  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Code Cleanup and Compiler Warning need to resolved.
// [Rootcause] Warnings reported when we build AMI higher Warning level.
// [Solution]- 1. Fix the warnings and do the code cleanup. 
//             2. Introduce proper checks.
//             3. change the popupSel.c to not change the Option/variable
// cache to default or first option
//                when the variable cache is not matching with any of
// option.
// [Files] - commonoem.c bbs.c boot.c hiistring.c resource.c
// popuppassword.c popupsel.c
//           expression.c hii.c parse.c
// 
// 8     10/04/10 4:24p Blaines
// In the function _DoPopupStringEdit, call gPopupEdit.SetType before
// calling gPopupEdit.Initialize. This is useful in case the function
// gPopupEdit.Initialize is overriden. 
// 
// 7     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 11    2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 10    2/17/10 7:03p Madhans
// To suppor readonly control
// 
// 9     2/15/10 10:15p Madhans
// To avoid warnings
// 
// 8     2/05/10 6:05p Madhans
// To fix the Screen corruption if mouse pointer is on the popup.
// 
// 7     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 6     1/09/10 6:58a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     1/04/10 10:40a Mallikarjunanv
// EIPs 27161/29095 - Added support for reserved boot option names and
// added support not to create empty boot option names
// 
// 4     8/13/09 1:20p Blaines
// EIP #24980 Fix to properly display right area text
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
// 2     5/07/09 10:36a Madhans
// Changes after Bin module
// 
// 1     4/28/09 11:06p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		PopupStirng.c
//
// Description:	This file contains code to handle Popup Stirngs
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

UINTN gCursorLeft,gCursorTop ; 
POPUP_STRING_METHODS gPopupString =
{
	PopupStringCreate,
	PopupStringDestroy,
	PopupStringInitialize,
	PopupStringDraw,
	PopupStringHandleAction,
	PopupStringSetCallback,
	PopupStringSetFocus, 
	PopupStringSetPosition,
	PopupStringSetDimensions,
	PopupStringSetAttributes,
    PopupStringGetControlHeight

};
extern UINTN gInvalidRangeFailMsgBox;
extern UINTN gAddBootOptionReserved;
extern CALLBACK_VARIABLE  gPopupEditCb ;
extern UINT8 res ;

VOID BbsStrnCpy ( CHAR16  *Dst, CHAR16  *Src, UINTN   Length );
BOOLEAN IsTSECursorSupport(); //EIP-91364
BOOLEAN IsMouseOnSoftkbd(VOID); //EIP-177886
VOID 	GetCoordinates(INT32 *x, INT32 *y, INT32 *z);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringCreate
//
// Description:	this function uses the create function of control
//					and creates popup strings
//
// Input:	TPOPUP_STRING_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringCreate( POPUP_STRING_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(POPUP_STRING_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gPopupString;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys popup strings
//
// Input:	POPUP_STRING_DATA *popupstring, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringDestroy( POPUP_STRING_DATA *popupstring, BOOLEAN freeMem )
{
	if(NULL == popupstring)
	  return EFI_SUCCESS;

	gControl.Destroy( popupstring, FALSE );

	MemFreePointer( (VOID **)&popupstring->Text );

	if( freeMem )
		MemFreePointer( (VOID **)&popupstring );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringDestroy
//
// Description:	this function uses the Initialize function of control
//					and initializes popup strings
//
// Input:	POPUP_STRING_DATA *popupstring, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringInitialize( POPUP_STRING_DATA *popupstring, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( popupstring, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	SetControlColorsHook(NULL, NULL,  
						 NULL, NULL,
						 &(popupstring->SelBGColor), &(popupstring->SelFGColor),
			             &(popupstring->BGColor), &(popupstring->FGColor),
						 NULL,&(popupstring->LabelFGColor),
					     &(popupstring->NSelLabelFGColor),
						 NULL,NULL,
						 NULL,NULL );

	popupstring->ControlData.ControlHelp = UefiGetHelpField(popupstring->ControlData.ControlPtr);
	popupstring->Interval = (UINT8)popupstring->ControlData.ControlFlags.ControlRefresh;

	popupstring->TextMargin = (UINT8)gControlLeftMargin;
	if ( popupstring->TextWidth == 0 )
	    popupstring->TextWidth = UefiGetWidth(((CONTROL_INFO *)data)->ControlPtr) /2;

    	popupstring->TextAreaWidth = (popupstring->TextWidth </*10*/(UINT16)(popupstring->Width - popupstring->TextMargin -2) ) ? popupstring->TextWidth:/*10*/(UINT16)(popupstring->Width - popupstring->TextMargin -2);

	popupstring->Text = EfiLibAllocateZeroPool((popupstring->TextWidth +1)* sizeof(CHAR16));
	MemSet( popupstring->Text, (popupstring->TextWidth +1)* sizeof(CHAR16), 0 );


	popupstring->TempText = EfiLibAllocateZeroPool((popupstring->TextWidth +1)* sizeof(CHAR16));
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringDraw
//
// Description:	this function is to draw the popup strings
//
// Input:	POPUP_STRING_DATA *popupstring
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringDraw(POPUP_STRING_DATA *popupstring )
{
	CHAR16 *text, *text1=NULL;
    UINT16 tmpHeight=0;
	UINTN Len = 0;
	UINT8 BGClr,FGClr;
	EFI_STATUS Status = EFI_SUCCESS;
	//UINT8 ColorNSel = popupstring->FGColor;
	UINT8 ColorLabel = (popupstring->ControlFocus) ? popupstring->LabelFGColor : popupstring->NSelLabelFGColor ;
	VOID *ifrData = popupstring->ControlData.ControlPtr;

	if(popupstring->ControlFocus)
	{  
		BGClr = popupstring->SelBGColor;
		FGClr =  popupstring->SelFGColor; 
	}
	else
	{ 
		BGClr =  popupstring->BGColor;
		FGClr = popupstring->FGColor;  
	}
	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( popupstring->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &popupstring->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				FGClr = ColorLabel = CONTROL_GRAYOUT_COLOR;		//EIP_51143 - to display the control value in grayout color
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	text = HiiGetString( popupstring->ControlData.ControlHandle, UefiGetPromptField(popupstring->ControlData.ControlPtr));
		
	if ( text != NULL )
	{
		CHAR16 *temptxt = NULL;

		temptxt = (CHAR16 *)EfiLibAllocateZeroPool( (UefiGetWidth(ifrData)+1) * sizeof(CHAR16) );

		//get the string value to check for string length
		VarGetValue( popupstring->ControlData.ControlVariable, UefiGetQuestionOffset(ifrData), UefiGetWidth(ifrData), (VOID *)temptxt );
		if (temptxt){
				Len = TestPrintLength( temptxt ) / (NG_SIZE);
				MemFreePointer( (VOID **)&temptxt );
		}

		//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
		if(popupstring->Height>1 && IsTSEMultilineControlSupported())
		{
			DrawMultiLineStringWithAttribute(	popupstring->Left , popupstring->Top,
															(UINTN)(popupstring->TextMargin - popupstring->Left),(UINTN) popupstring->Height, text,
															(UINT8)( (!Len && popupstring->ControlFocus) ? (popupstring->SelBGColor  | popupstring->SelFGColor) : (popupstring->BGColor | ColorLabel) ) //make it to focus when no string is given
														);
		}
		else
		{
	        // use frame width minus margins as available space
		    // boundary overflow  check
		    if (( TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(popupstring->TextMargin - popupstring->Left) )
				//EfiStrCpy(&text[HiiFindStrPrintBoundary(text,(UINTN)(popupstring->Width - 5))],L"...");
				text[HiiFindStrPrintBoundary(text,(UINTN)(popupstring->TextMargin - popupstring->Left  ))] = L'\0';

		    DrawStringWithAttribute(	popupstring->Left  ,
												popupstring->Top, text, 
												(UINT8)( (!Len && popupstring->ControlFocus) ? (popupstring->SelBGColor  | popupstring->SelFGColor) : (popupstring->BGColor | ColorLabel) ) //Make it to focus when no string is given
											);
		}
		//PopUpString has to display the string besides the title; need not fill with space here
		//for(i=(UINT16)(popupstring->Left + EfiStrLen( text )/*popupstring->TextWidth*/); i < popupstring->Width; i++)
		//	DrawStringWithAttribute( i, popupstring->Top, L" ", BGClr | FGClr );

	    MemFreePointer( (VOID **)&text );
	}

	if(ifrData)
	{
		//get the string value
		VarGetValue( popupstring->ControlData.ControlVariable, UefiGetQuestionOffset(ifrData), UefiGetWidth(ifrData), (VOID *)popupstring->Text );

		Len = TestPrintLength( popupstring->Text ) / (NG_SIZE);

		if(Len)
		{
			text = EfiLibAllocateZeroPool((Len+1)*2);
			EfiStrCpy(text, popupstring->Text);

			//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
            if(popupstring->Height>1 && IsTSEMultilineControlSupported())
	        {
                text1 = StringWrapText( (CHAR16*)text, (popupstring->Width - popupstring->TextMargin ), &tmpHeight );

                if(tmpHeight > 1)
		        {
                    DrawMultiLineStringWithAttribute( (UINTN)popupstring->Left + (UINTN)popupstring->TextMargin, 
																		(UINTN) popupstring->Top,
																		(UINTN)(popupstring->Width - popupstring->TextMargin ),
																		(UINTN)popupstring->Height, (CHAR16*)text,
																		(UINT8) (popupstring->ControlFocus ? (popupstring->SelBGColor  | popupstring->SelFGColor) : (popupstring->BGColor | ColorLabel) )
																	);
                }
                else
                {
                    DrawStringWithAttribute( popupstring->Left + popupstring->TextMargin,
															popupstring->Top, text, 
															(UINT8) (popupstring->ControlFocus ? (popupstring->SelBGColor  | popupstring->SelFGColor) : (popupstring->BGColor | ColorLabel) )
														);
                }
                
                MemFreePointer( (VOID **)&text1 );
                MemFreePointer( (VOID **)&text );
                
            }
            else
            {			
    			if ( Len  > (UINTN)(popupstring->Width - popupstring->TextMargin) )
    			{
    				Len = popupstring->Width - popupstring->TextMargin;
    				EfiStrCpy( &(text[Len-3 /*3 for "..."*/]), L"..." );
    			}
    
    			DrawStringWithAttribute	( popupstring->Left + popupstring->TextMargin  , popupstring->Top, text, 
    											(UINT8) (popupstring->ControlFocus ? (popupstring->SelBGColor  | popupstring->SelFGColor) : (popupstring->BGColor | ColorLabel) )
												);
    
    			MemFreePointer( (VOID **)&text );
            }

		}


		// erase extra spaces if neccessary
		//for(;(UINT16)(popupstring->Left + popupstring->TextMargin + Len) < (popupstring->Width);Len++)
		//	DrawStringWithAttribute( popupstring->Left + popupstring->TextMargin +Len , popupstring->Top, L" ", 
		//				 BGClr | FGClr);
	}

	FlushLines( popupstring->Top  , popupstring->Top );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringSetCallback
//
// Description:	function to handle the PopupString actions
//
// Input:		POPUP_STRING_DATA *popupstring, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringSetCallback( POPUP_STRING_DATA *popupstring, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( popupstring, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringHandleAction
//
// Description:	function to handle the Popup string actions.
//
// Input:	POPUP_STRING_DATA *popupstring, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringHandleAction( POPUP_STRING_DATA *popupstring, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
 	CONTROL_ACTION Action=ControlActionUnknown;
 	VOID * UnicodeInterface;
	CHAR16 *TmpStr = NULL;	
	CHAR16 *ResStr = NULL;
	CHAR16 *TmpPopupStringText = NULL;
	UINT16 TmpPopupStringTextWidth = 0;
    UINT8 u8ChkResult;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		if (popupstring->Interval == 0)
			return Status;

		if(IsActiveControlPresent(gApp->PageList[gApp->CurrentPage]))
			return Status;

		if ( --(popupstring->Interval) == 0 )
		{
			// initialize the interval
			popupstring->Interval = (UINT8)(popupstring->ControlData.ControlFlags.ControlRefresh);
			return UefiRefershQuestionValueNvRAM(&(popupstring->ControlData));
		}
		else
			return Status;
	}

    u8ChkResult = CheckControlCondition( &popupstring->ControlData );
	 
    //Not to perform action for grayoutif-control when token TSE_SETUP_GRAYOUT_SELECTABLE is enable to set focus for GrayoutIf control
    if ( IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT) ) {
        return EFI_UNSUPPORTED;
    }

    if(popupstring->ControlData.ControlFlags.ControlReadOnly)
		return EFI_UNSUPPORTED;

	if ( Data->Input.Type == ACTION_TYPE_MOUSE )
	{
		//Get mapping
	
		//EIP-123727 check whether MouseTop is within the Height and Width of popupstring or not
		if( (Data->Input.Data.MouseInfo.Top >= (UINT32)popupstring->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(popupstring->Top+popupstring->Height)) &&
			(Data->Input.Data.MouseInfo.Left >= (UINT32)popupstring->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(popupstring->Left+popupstring->Width))
		)
		{
			Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);
		}
	}

	if ( Data->Input.Type == ACTION_TYPE_KEY )
    {
        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);
	}

	if(ControlActionSelect == Action)
	{
		//Taking backup of original string.
		TmpPopupStringText = EfiLibAllocateZeroPool((popupstring->TextWidth + 1) * sizeof(CHAR16));			
		if(NULL == TmpPopupStringText){
			return EFI_OUT_OF_RESOURCES;
		}
		EfiStrCpy(TmpPopupStringText, popupstring->Text);

		//Taking backup of initial string length EIP-75522 
		TmpPopupStringTextWidth = popupstring->TextWidth; //EIP-90894

		// Reading string
		if(_DoPopupStringEdit( popupstring,UefiGetPromptField(popupstring->ControlData.ControlPtr), &(popupstring->Text)) == EFI_SUCCESS)
		{
			UINTN MinVal=0, MaxVal=0;
			MinVal = (UINTN)UefiGetMinValue(popupstring->ControlData.ControlPtr);
			MaxVal = (UINTN)UefiGetMaxValue(popupstring->ControlData.ControlPtr);

			//Find length of entered string EIP-75522 
			popupstring->TextWidth = (UINT16)EfiStrLen(popupstring->Text);

			// Check for Range. If its a valid string annd not between min and max report invalid error msg
			if((popupstring->Text) &&((popupstring->TextWidth < MinVal) || (popupstring->TextWidth > MaxVal)))
			{
				//Reset popupstring->Text with initial string EIP-75522 
				if(TmpPopupStringText) {
					MemFreePointer((VOID **)&popupstring->Text);					
					popupstring->Text = EfiLibAllocateZeroPool((MaxVal + 1) * sizeof(CHAR16)); //EIP-127021 Allocating PopupString->Text based on max size of control
					if(NULL == popupstring->Text){
						MemFreePointer((VOID **)&TmpPopupStringText);
						return EFI_OUT_OF_RESOURCES;
					}
					EfiStrCpy(popupstring->Text, TmpPopupStringText);
					MemFreePointer((VOID **)&TmpPopupStringText);
					popupstring->TextWidth = TmpPopupStringTextWidth; ////EIP-90894 Resetting width with old one
				}
				//Report Message box EIP-75522 
				CallbackShowMessageBox( (UINTN)gInvalidRangeFailMsgBox, MSGBOX_TYPE_OK );
				return EFI_ABORTED;
			}

			///Fix: Eip-27161 - not to allow Reserved boot options to delete 
			if( (popupstring->Text) && (IsReservedBootOptionNamesEnable()) ) 
			{
				ResStr = CONVERT_TO_WSTRING(RESERVED_ADD_DEL_BOOT_OPTION_NAME);
				TmpStr = EfiLibAllocateZeroPool( EfiStrLen(ResStr)+1); 
				BbsStrnCpy(TmpStr, popupstring->Text, (EfiStrLen(ResStr)+1));
				TmpStr[EfiStrLen(ResStr)]= L'\0';

				Status = InitUnicodeCollectionProtocol(&UnicodeInterface);
				if(!EFI_ERROR(Status)) 
				{
					if( StringColl( UnicodeInterface, TmpStr, ResStr) == 0 )
					{
						CallbackShowMessageBox( (UINTN)gAddBootOptionReserved, MSGBOX_TYPE_OK );
						return EFI_ABORTED;

					}
				}
			}

            if(popupstring->Callback != NULL)
            {
                if ( popupstring->Cookie != NULL )
                {
                    VOID *ifrData = popupstring->ControlData.ControlPtr;
                    CALLBACK_VARIABLE *callbackData = (CALLBACK_VARIABLE *)popupstring->Cookie;

                    callbackData->Variable = popupstring->ControlData.ControlVariable;
                    callbackData->Offset = UefiGetQuestionOffset(ifrData);
                    callbackData->Length = UefiGetWidth(ifrData);
                    callbackData->Data = (VOID *)popupstring->Text;

					// To support UEFI 2.1.C spec to Not to update the control when Callback fails.
					UefiPreControlUpdate(&(popupstring->ControlData));
                    popupstring->Callback( popupstring->Container,popupstring, popupstring->Cookie );	
                }
            }
            if ( UefiIsInteractive(&popupstring->ControlData) )
            {
    			VOID * Handle=popupstring->ControlData.ControlHandle;
    			UINT16 Key = UefiGetControlKey(&(popupstring->ControlData));
    			CONTROL_DATA *Control;
    
    			Status = CallFormCallBack(&(popupstring->ControlData),Key,0,AMI_CALLBACK_CONTROL_UPDATE);//EIP-53480: Updated the action to AMI_CALLBACK_CONTROL_UPDATE
    			Control = GetUpdatedControlData((CONTROL_DATA*)popupstring,CONTROL_TYPE_POPUP_STRING,Handle,Key);

    			if(Control == NULL) // Control deleted ?
    				return EFI_SUCCESS;
    			if(Control != (CONTROL_DATA*)popupstring)
    				popupstring = (POPUP_STRING_DATA*)Control; //control Updated

				//If error status returned by CallFormCallBack(), reset popupstring->Text with the old string.
				if(EFI_ERROR(Status))
				{
					if(popupstring->Text)
						MemFreePointer((VOID **)&popupstring->Text);
					popupstring->Text = EfiLibAllocateZeroPool((TmpPopupStringTextWidth + 1) * sizeof(CHAR16));
					if(popupstring->Text == NULL){
						return EFI_OUT_OF_RESOURCES;
					}
					if(TmpPopupStringText) {
						//Resetting old PopupstringText with TmpPopupStringText EIP-75522
						EfiStrCpy(popupstring->Text, TmpPopupStringText);
					}

					//Reset string length to initial string TmpPopupStringTextWidth length EIP-75522
					popupstring->TextWidth = TmpPopupStringTextWidth; 

					//Report Message box and return without proceeding further. EIP-75522
					//CallbackShowMessageBox( (UINTN)gInvalidRangeFailMsgBox, MSGBOX_TYPE_OK );   //All other callback not poping up msg box so commented
					MemFreePointer((VOID **)&TmpPopupStringText);
					return EFI_ABORTED;

				}

            }
        }
		Status = EFI_SUCCESS;
    }

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringSetFocus
//
// Description:	Function to handle the PopupString actions
//
// Input:		POPUP_STRING_DATA *popuppassword, BOOLEAN focus
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringSetFocus(POPUP_STRING_DATA *popuppassword, BOOLEAN focus)
{
	UINT8 u8ChkResult;
	
	if(focus != FALSE)
	{
        u8ChkResult = CheckControlCondition( &popuppassword->ControlData );
        
		//Setting focus to control which has no control-condtion and token TSE_SETUP_GRAYOUT_SELECTABLE is enable to make GrayoutIf control to focus and selectable
		if ( ((u8ChkResult != COND_NONE) && (u8ChkResult != COND_GRAYOUT)) ||
             (!IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT))
			){
			return EFI_UNSUPPORTED;
		}
	}

	if( !(popuppassword->ControlFocus && focus) )
		popuppassword->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringSetPosition
//
// Description:	Function to set position.
//
// Input:		POPUP_STRING_DATA *popuppassword, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringSetPosition(POPUP_STRING_DATA *popuppassword, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( popuppassword, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		POPUP_STRING_DATA *popuppassword, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringSetDimensions(POPUP_STRING_DATA *popuppassword, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( popuppassword, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		POPUP_STRING_DATA *popuppassword, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringSetAttributes(POPUP_STRING_DATA *popuppassword, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( popuppassword, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupStringGetControlHeight
//
// Description:	Function to get the lable height of the PopupString
//
// Input:		POPUP_STRING_DATA *popupstring, frame, UINT16 *height
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupStringGetControlHeight(POPUP_STRING_DATA *popupstring, VOID * frame, UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
	    UINT16 Width=0, tmpHeight=0;
		VOID *ifrData = popupstring->ControlData.ControlPtr;
		
	    if(ifrData)
		{
			//get the string value
			VarGetValue( popupstring->ControlData.ControlVariable, UefiGetQuestionOffset(ifrData), UefiGetWidth(ifrData), (VOID *)popupstring->Text );
	        newText = StringWrapText( popupstring->Text, 
	                    (UINT16)(((FRAME_DATA *)frame)->FrameData.Width - gLabelLeftMargin - popupstring->TextMargin - 2 ), &tmpHeight );
	                                
		    *height = tmpHeight;                        
		    MemFreePointer( (VOID **)&newText );
		}
			
		Width = (UINT16)(popupstring->TextMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gControlLeftPad));
		text = HiiGetString( popupstring->ControlData.ControlHandle, UefiGetPromptField(popupstring->ControlData.ControlPtr));
	
		newText = StringWrapText( text, Width, &tmpHeight );
	
	    if(tmpHeight > *height)
			*height = tmpHeight;
	
	    (*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
		MemFreePointer( (VOID **)&text );
	}
	else
	{
		*height = 1 ;
	}
	return EFI_SUCCESS;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_CBPopupStringEdit
//
// Description:	Function for PopupStringEdit callback.
//
// Input:		VOID *container, VOID *object, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _CBPopupStringEdit(VOID *container, VOID *object, VOID *cookie)
{
	EFI_STATUS Status = EFI_SUCCESS;
	if(cookie!=NULL)
	{

		res=0;
	}
	else
 	   res=1; // exit with no changes to string

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupStringEditGetValue
//
// Description:	function to get values for popup menu using edit functions.
//
// Input:	POPUP_STRING_DATA *popupedit
//
// Output:	UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _PopupStringEditGetValue( POPUPEDIT_DATA *popupedit )
{
	ACTION_DATA *action = gApp->Action;
	BOOLEAN		DrawCursor = TRUE;//EIP:67695
	EFI_STATUS  Status = EFI_SUCCESS;//EIP:67695 
	INT32  	MousePointerX = 0,MousePointerY = 0,MousePointerZ = 0;
		
	gPopupEdit.SetCallback( popupedit, NULL, _CBPopupStringEdit, &gPopupEditCb );
	gPopupEdit.SetDimensions( popupedit, popupedit->Width , popupedit->Height );
	res = (UINT8)-1;

    TSEStringReadLoopEntryHook();

    while ( res == (UINT8)-1 )
	{
		if ( action->Input.Type != ACTION_TYPE_NULL )
			gAction.ClearAction( action );

		GetCoordinates (&MousePointerX, &MousePointerY, &MousePointerZ); //EIP-177886
		if (gST->ConOut)
		{
			if ( 	
				( ((MousePointerX/HiiGetGlyphWidth ()) <= (UINT32)gST->ConOut->Mode->CursorColumn+1) && ((MousePointerX/HiiGetGlyphWidth ()) >= (UINT32)gST->ConOut->Mode->CursorColumn-1) ) && 
				( ((MousePointerY/HiiGetGlyphHeight ()) <= (UINT32)gST->ConOut->Mode->CursorRow+1) && ((MousePointerY/HiiGetGlyphHeight ()) >= (UINT32)gST->ConOut->Mode->CursorRow-1) )			//EIP79486 Stop the mouse if mouse poiner is over the text cursor useful for avoiding corruption
				)
				MouseStop ();
			else
			{
				if ( !IsMouseOnSoftkbd() )
					MouseFreeze ();
			}
		}
	
		gPopupEdit.Draw( popupedit );
		DoRealFlushLines();

		if (IsTSECursorSupport()) //EIP-91364
		{
			if (TRUE == DrawCursor)							//EIP:67695 Enabling at valid times
			{
				gST->ConOut->SetAttribute (gST->ConOut, popupedit->FGColor | popupedit->BGColor);
	        	gST->ConOut->SetCursorPosition (gST->ConOut, gCursorLeft, gCursorTop);//EIP 86346 : Providing the calculated Cursor position values.
				gST->ConOut->EnableCursor (gST->ConOut, TRUE);
				DrawCursor = FALSE;
			}
		}
		if ( !IsMouseOnSoftkbd() )
			MouseRefresh();
		
		if ( gAction.GetAction( action ) != EFI_SUCCESS )
			continue;

		if( ( action->Input.Type == ACTION_TYPE_KEY ) &&
			(TsePrintScreenEventSupport(action->Input.Data.AmiKey.Key.ScanCode) ) ) 
		{
			gApplication.HandleAction( gApp, action );
				DrawCursor = TRUE;     //EIP-123432  If print screen is taken then Drawcursor is made true.
				continue;
			}
			Status = gPopupEdit.HandleAction( popupedit, action );
			if (IsTSECursorSupport() && !((EFI_ERROR (Status))))//EIP:67695
			{
				DrawCursor = TRUE;			//EIP:67695 If any valid action performed then draw the cursor, useful for blinking
			}
		}
	    TSEStringReadLoopExitHook();

	return res;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DoPopupStringEdit
//
// Description:	Function to initiate PopupString editing
//
// Input:		POPUP_STRING_DATA PopupString, UINT16 Title, CHAR16 **Text
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _DoPopupStringEdit( POPUP_STRING_DATA *PopupString, UINT16 Title, CHAR16 **Text)
{
	static UINT8 gIFRPopupEdit[50];
	EFI_STATUS Status= EFI_SUCCESS;

	UINT8 retValue = (UINT8)-1;

	POPUPEDIT_DATA *popupedit = NULL;

	CONTROL_INFO dummy;
	BOOLEAN 		PreviousCursorState = gST->ConOut->Mode->CursorVisible;//EIP:67695 

	Status = gPopupEdit.Create( &popupedit );
	if ( EFI_ERROR( Status ) )
		return Status;

	MemSet( &dummy, sizeof(dummy), 0 );
	dummy.ControlHandle = PopupString->ControlData.ControlHandle;
	MemCopy( &gIFRPopupEdit, (VOID*)PopupString->ControlData.ControlPtr, UefiGetIfrLength(PopupString->ControlData.ControlPtr));

	//    gIFRPopupEdit.Prompt = Title;
	UefiSetPromptField ((VOID*)&gIFRPopupEdit,Title);

	dummy.ControlPtr = (VOID*)&gIFRPopupEdit;
	dummy.ControlFlags.ControlVisible = TRUE;

	//gPopupEdit.SetTitle(popupedit,Title);
	gPopupEdit.SetText(popupedit,*Text);
	gPopupEdit.SetType( popupedit, POPUPEDIT_TYPE_STRING );
	Status = gPopupEdit.Initialize( popupedit, &dummy );
	if ( EFI_ERROR( Status ) )
		goto Done;

	//gPopupEdit.SetType( popupedit, POPUPEDIT_TYPE_STRING );
	retValue = (UINT8)_PopupStringEditGetValue( popupedit );
	if (IsTSECursorSupport()) //EIP-91364
	{
		gST->ConOut->EnableCursor(gST->ConOut, PreviousCursorState);//EIP:67695 
	}
	if(retValue ==0)
	{
		// string changed, save to nvram or do whatever needs to be done
		MemFreePointer( (VOID **)Text );
		*Text = EfiLibAllocateZeroPool( (gPopupEditCb.Length+1) * sizeof(CHAR16) );
		if ( Text == NULL )
			return EFI_OUT_OF_RESOURCES;
		EfiStrCpy( *Text, gPopupEditCb.Data );
	}
Done:
	gPopupEdit.Destroy( popupedit, TRUE );
	return Status;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
