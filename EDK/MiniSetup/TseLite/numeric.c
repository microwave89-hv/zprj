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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/numeric.c $
//
// $Author: Premkumara $
//
// $Revision: 38 $
//
// $Date: 8/28/14 3:06p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/numeric.c $
// 
// 38    8/28/14 3:06p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 37    5/03/14 8:04p Premkumara
// [TAG]	                EIP139608
// [Category]	Bug Fix
// [Severity:]	                Important
// [Symptom:]	Not able to navigate to other page using Mouse/Clicks when
// Numeric control is focused. Msgbox, Menu, Listbox is not closing using
// touch/mouse.
// [Root Cause]	When token SINGLE_CLICK_ACTIVATION is enabled
// numerichandle action is not returning unsupported. TSE isn't handled
// ControlActionSelect to close msgbox, menu, listbox when token is
// enable.
// [Solution]	Handled mouse action properly for numeric control. Handled
// action properly to close msgbox, listbox, menu.
// [Files]	ListBox.c, Numeic.c, MessageBox.c, MinisetupExt.c
// 
// 36    5/03/14 3:17p Premkumara
// [TAG]	                EIP139608
// [Category]	Bug Fix
// [Severity:] 	Important
// [Symptom:]	Not able to navigate to other page using Mouse/Clicks when
// Numeric control is focused. Msgbox, Menu, Listbox is not closing using
// touch/mouse.
// [Root Cause]	When token SINGLE_CLICK_ACTIVATION is enabled
// numerichandle action is not returning unsupported. TSE isn't handled
// ControlActionSelect to close msgbox, menu, listbox when token is
// enable.
// [Solution]	Handled mouse action properly for numeric control. Handled
// action properly to close msgbox, listbox, menu.
// [Files]	ListBox.c, Numeic.c, MessageBox.c, MinisetupExt.c
// 
// 35    5/02/14 9:33p Arunsb
// EIP141986 changes reverted.
// 
// 34    5/02/14 10:58a Premkumara
// [TAG]  		EIP141986
// [Category]  	New Feature
// [Description]  	Made Grayed controls to focus-able when token
// TSE_SETUP_GRAYOUT_SELECTABLE
//  is enabled and can't edit the values
// [Files]  		AMITSE.sdl,CommonHelper.c,frame.c,Label.c,minisetupext.h,
// numeric.c,PopupPassword.c,PopupSel.c,PopupString.c,SubMenu.c
// 
// 33    5/01/14 3:43p Premkumara
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
// 32    2/11/14 9:02p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 31    12/05/13 1:37a Premkumara
// [TAG]	EIP139608
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	Not able to navigate to other page using Mouse/Clicks when
// Numeric control is focused. Msgbox, Menu, Listbox is not closing using
// touch/mouse.
// [Root Cause]	When token SINGLE_CLICK_ACTIVATION is enabled
// numerichandle action is not returning unsupported. TSE isn't handled
// ControlActionSelect to close msgbox, menu, listbox when token is
// enable.
// [Solution]	Handled mouse action properly for numeric control. Handled
// action properly to close msgbox, listbox, menu.
// [Files]	ListBox.c, Numeic.c, MessageBox.c, MinisetupExt.c
// 
// 30    12/03/13 1:10p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 29    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 13    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 28    6/28/12 8:23p Arunsb
// [TAG]  		EIP92407
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Shift + "+" key wont respond
// [RootCause]  	Shift state not cleared
// [Solution]  	Shift state cleared
// [Files]  		numeric.c
// 
// 27    5/29/12 2:41a Premkumara
// Added missed EIP-88811 changes (TSEMouseIgnoreMouseActionHook()) in
// numeric.c
// 
// 26    5/28/12 11:52a Premkumara
// [TAG]  		EIP89272
// [Category]  	Improvement
// [Description]  	Change softkbd layout for numeric control
// [Files]  		CommonHelper.c, Mouse.c, Minisetup.h, C, Numeric.c
// 
// 25    5/28/12 8:27a Arunsb
// CallbackShowMessageBox commented in NumericDraw
// 
// 24    5/24/12 7:30a Rajashakerg
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
// 23    5/09/12 6:23p Premkumara
// [TAG]  		EIP83703
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	TSE hangs while clicking on the "link training time out"
// value [this is happening while trying the specified steps immediate
// after bios flash
// [RootCause]  	When invalid range input is provided for numeric control
// ESC sequence is not provided if it is handled by the mouse.
// [Solution]  	Provided the proper ESC sequence to the control such that
// it close the Invalid Range Fail MsgBox when handled with the mouse and
// key.
// [Files]  		Numeric.c, CommonHelper.c
// 
// $/Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/
// - numeric.c (ver 22)
// 
// $/Alaska/BIN/Modules/AMITSE2_0/AMITSE/
// - CommonHelper.c (ver 88)
// 
// 22    5/09/12 5:04p Premkumara
// [TAG]  		EIP83703
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	TSE hangs while clicking on the "link training time out"
// value [this is happening while trying the specified steps immediate
// after bios flash
// [RootCause]  	When invalid range input is provided for numeric control
// ESC sequence is not provided if it is handled by the mouse.
// [Solution]  	Provided the proper ESC sequence to the control such that
// it close the Invalid Range Fail MsgBox when handled with the mouse and
// key.
// [Files]  		Numeric.c, CommonHelper.c
// 
// 21    4/05/12 7:17a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 20    4/03/12 11:57p Rajashakerg
// [TAG]  		EIP83703 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	TSE hangs while clicking on the "link training time out"
// value [this is happening while trying the specified steps immediate
// after bios flash]
// [RootCause]  	Invalid message box handling with in the numeric is not
// proper which is cauing the hang.
// [Solution]  	Invalid message box is handled propely with mouse
// selection.
// [Files]  		numeric.c
// 
// 19    12/08/11 12:28p Rajashakerg
// Updated the file to overcome build errors when build for x32 mode.
// 
// 18    11/21/11 11:23a Premkumara
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
// 17    11/21/11 12:23a Rajashakerg
// [TAG]  		EIP62763
// [Category]  	Improvement
// [Description]  	Utilize the Improvements done from mouse driver in
// AMITSE.
// [Files]  		HookAnchor.h, TseCommon.h, AMITSE.sdl, CommonHelper.c,
// commonoem.c, commonoem.h, buffer.c, globals.c, HookAnchor.c,
// minisetup.h, notify.c, postmgmt.c, protocol.c, ezport.c, stylecommon.c,
// Mouse.c, Action.c, Date.c, frame.c, MessageBox.c, minisetupext.c,
// minisetupext.h, numeric.c, numeric.h, page.c, PopupEdit.c, PopupEdit.h,
// PopupPassword.c, postmgmtext.c, time.c.
// 
// 16    11/20/11 8:01a Rajashakerg
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
// 15    11/14/11 6:55p Blaines
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
// 14    10/21/11 2:54a Rajashakerg
// [TAG]  		EIP60563 
// [Category]  	New Feature
// [Description]  	Updating the file with fix for issue : maximum 8 byte
// value shows negative number
// [Files]  		numeric.c, numeric.h, string.c, string.h
// 
// 13    10/10/11 1:32a Arunsb
// [TAG]  		EIP66976
// [Category]  	Improvement
// [Description]  	Provision to change the Numeric string format
// [Files]  		commonhelper.c, amitse.sdl and numeric.c
// 
// 12    6/23/11 3:54p Rajashakerg
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
// 11    6/20/11 12:22p Rajashakerg
// [TAG]  		EIP60563 
// [Category]  	New Feature
// [Description]  	Support for signed decimal value for
// EFI_IFR_NUMERIC_OP.  
// [Files]  		numeric.c, numeric.h, string.c, string.h, Uefi21Wapper.c
// 
// 10    6/07/11 2:44p Madhans
// [TAG]  		EIP61897 
// [Category]  	Improvement
// [Description]  	To ignore the limit checking for the Suppressed
// Controls in TSE
// [Files]  		numeric.c
// 
// 9     3/21/11 12:39a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 8     3/09/11 7:23p Madhans
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
// 7     12/02/10 6:08p Madhans
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
// 6     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 5     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 6:45a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     9/15/09 3:54p Madhans
// // EIP: 26473 Fix  To support uppercase Hex numbers
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
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
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
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		numeric.c
//
// Description:	This file contains code to handle Label operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

NUMERIC_METHODS gNumeric =
{
	NumericCreate,
	NumericDestroy,
	NumericInitialize,
	NumericDraw,
	NumericHandleAction,
	NumericSetCallback,
	NumericSetFocus,
	NumericSetPosition,
	NumericSetDimensions,
	NumericSetAttributes,
    NumericGetControlHeight
};
BOOLEAN SingleClickActivation (VOID); //EIP-139608 
extern UINTN gInvalidRangeFailMsgBox;
static BOOLEAN NumericIncDec = TRUE;
BOOLEAN CheckKeyinHotKeysList(AMI_EFI_KEY_DATA Key);
EFI_STATUS NumericHandleActionKeyMouse(NUMERIC_DATA *numeric, ACTION_DATA *Data);
VOID NumSPrint(NUMERIC_DATA *numeric,NUMERIC_MIN_MAX_BASE Num);
VOID UpdateNumericDisplayString (CHAR16 **, INT64, UINT8, UINT16, UINT16);
VOID ClearNumericShiftState (AMI_EFI_KEY_DATA *);//EIP-83703 

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericCreate
//
// Description:	function used for Numeric control Create, which uses the Edit functions.
//
// Input:	 NUMERIC_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericCreate( NUMERIC_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(NUMERIC_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gEdit.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gNumeric;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericDestroy
//
// Description:	function used to destroy Numeric controls, which uses the Edit functions.
//
// Input:	 NUMERIC_DATA **object, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericDestroy( NUMERIC_DATA *numeric, BOOLEAN freeMem )
{
	if(NULL == numeric	)
	  return EFI_SUCCESS;
	
	gEdit.Destroy( numeric, FALSE );

	MemFreePointer( (VOID **)&numeric->Text );

	if( freeMem )
		MemFreePointer( (VOID **)&numeric );

	return EFI_SUCCESS;
}

//EIP:60563 to support signed integers for NUMERIC opcode
//EIP:60563 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckForRange
//
// Description:	function used to check the range for the negative numbers and positive nubmers.
//
// Input:	 NUMERIC_DATA *numeric, NUMERIC_VALUE_BASE *Num
//
// Output:	BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckForRange(NUMERIC_DATA *numeric, NUMERIC_VALUE_BASE *Num)
{
	if(numeric->Base == 32)
	{
		if(numeric->ControlData.ControlDataWidth == 1)
		{
			if(((INT8)*Num < (INT8)numeric->MinValue) ||((INT8)*Num > (INT8)numeric->MaxValue))
				return TRUE;
		}
		else if(numeric->ControlData.ControlDataWidth == 2)
		{
			if(((INT16)*Num < (INT16)numeric->MinValue) ||((INT16)*Num > (INT16)numeric->MaxValue))
				return TRUE;
		}
		else if(numeric->ControlData.ControlDataWidth == 4)
		{
			if(((INT32)*Num < (INT32)numeric->MinValue) ||((INT32)*Num > (INT32)numeric->MaxValue))
				return TRUE;
		}
		else if(numeric->ControlData.ControlDataWidth == 8)
		{
			if(((INT64)*Num < (INT64)numeric->MinValue) ||((INT64)*Num > (INT64)numeric->MaxValue))
				return TRUE;
		}
		else 
			return FALSE;
	}
	else
	{
		if(((*Num) < numeric->MinValue) ||(*Num > numeric->MaxValue))
			return TRUE;
		else
			return FALSE;
	}
return FALSE;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckForRangefromsetup
//
// Description:	function used to check the range for the negative numbers and positive nubmers from setup.
//
// Input:	 NUMERIC_DATA *numeric, NUMERIC_VALUE_BASE *Num
//
// Output:	BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckForRangefromsetup(NUMERIC_DATA *numeric, NUMERIC_VALUE_BASE *Num)
{
	if(numeric->Base == 32)
	{
		if(numeric->ControlData.ControlDataWidth == 1)
		{
			if(((INT8)*Num >= (INT8)numeric->MinValue) &&((INT8)*Num <= (INT8)numeric->MaxValue))
				return TRUE;
		}
		else if(numeric->ControlData.ControlDataWidth == 2)
		{
			if(((INT16)*Num >= (INT16)numeric->MinValue) &&((INT16)*Num <= (INT16)numeric->MaxValue))
				return TRUE;
		}
		else if(numeric->ControlData.ControlDataWidth == 4)
		{
			if(((INT32)*Num >= (INT32)numeric->MinValue) &&((INT32)*Num <= (INT32)numeric->MaxValue))
				return TRUE;
		}
		else if(numeric->ControlData.ControlDataWidth == 8)
		{
			if(((INT64)*Num >= (INT64)numeric->MinValue) &&((INT64)*Num <= (INT64)numeric->MaxValue))
				return TRUE;
		}
		else 
			return FALSE;
	}
	else
	{
		if(((*Num) >= numeric->MinValue) &&(*Num <= numeric->MaxValue))
			return TRUE;
		else
			return FALSE;
	}
	
	return FALSE;
}
//EIP:60563 END
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericInitialize
//
// Description:	function used to Initialize the Numeric controls, which uses the Edit functions.
//
// Input:	 NUMERIC_DATA **object, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericInitialize( NUMERIC_DATA *numeric, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	NUMERIC_VALUE_BASE *Num;
	VOID * ControlPtr = ((CONTROL_INFO *)data)->ControlPtr;
	UINT16 Size = UefiGetWidth(ControlPtr);

	// If the size 1 (it can hold upto 3 Decimal data +1 for null, is more then one the size * 3 is ok
	numeric->TextWidth = (Size>1)?(3 * (UINT16)Size):4;

	Status = gEdit.Initialize( numeric, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	//numeric->FGColor = EFI_YELLOW;
	//numeric->BGColor = EFI_BACKGROUND_BLUE;
	//numeric->TextWidth = numeric->TextAreaWidth;
	numeric->Chr = 0x0;
	numeric->MinValue = UefiGetMinValue(ControlPtr);//EIP:60563 to support signed integers for NUMERIC opcode
	numeric->MaxValue = UefiGetMaxValue(ControlPtr);
	numeric->Step = UefiGetStepValue(ControlPtr);
    numeric->ControlData.ControlDataWidth = Size;
	numeric->Base = UefiGetBaseValue(ControlPtr); // default base decimal number
	numeric->Interval = (UINT8)(numeric->ControlData.ControlFlags.ControlRefresh);

	Num = EfiLibAllocateZeroPool( (Size <sizeof(NUMERIC_MIN_MAX_BASE))? sizeof(NUMERIC_MIN_MAX_BASE):Size );

	if ( Num != NULL )
	{
		VarGetValue( numeric->ControlData.ControlVariable, 
				UefiGetQuestionOffset(ControlPtr), Size, Num );

		// check that value is in range
		//EIP:60563 to support signed integers for NUMERIC opcode
		if(CheckForRange( numeric, Num))
		{
			// try to use the default
			if(numeric->ControlData.ControlDataWidth != 0)
			{
			    VarGetDefaults( numeric->ControlData.ControlVariable, 
								UefiGetQuestionOffset(ControlPtr),
								Size, Num );
			}
		}

        if(*Num < numeric->MinValue)
			*Num = numeric->MinValue;//revert to minimum value 

        if(*Num > numeric->MaxValue)
			*Num =numeric->MaxValue;//revert to maximum value 

		numeric->Value = *Num;

		MemFreePointer( (VOID **)&Num );
	}

	NumSPrint(numeric,numeric->Value);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericDraw
//
// Description:	function used to draw the numeric controls
//
// Input:	 NUMERIC_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericDraw(NUMERIC_DATA *numeric )
{
	NUMERIC_MIN_MAX_BASE *Num;
	VOID * ControlPtr = numeric->ControlData.ControlPtr;

	if(numeric->ControlActive == TRUE)
		return gEdit.Draw( numeric );

	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( numeric->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &numeric->ControlData ) )
		{
			case COND_NONE:
			case COND_GRAYOUT:
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	Num = EfiLibAllocateZeroPool((numeric->ControlData.ControlDataWidth<sizeof(NUMERIC_MIN_MAX_BASE))?sizeof(NUMERIC_MIN_MAX_BASE):numeric->ControlData.ControlDataWidth);

	if ( Num != NULL )
	{
		VarGetValue( numeric->ControlData.ControlVariable, 
				UefiGetQuestionOffset(ControlPtr),
				numeric->ControlData.ControlDataWidth, Num );

		// check that value is in range
		//EIP:60563 to support signed integers for NUMERIC opcode
		if(CheckForRange(numeric, Num))
		{
			//Report Message box
//	  		CallbackShowMessageBox( (UINTN)gInvalidRangeFailMsgBox, MSGBOX_TYPE_OK );

			// try to use the default
			if(numeric->ControlData.ControlDataWidth != 0)
			{
			    VarGetDefaults( numeric->ControlData.ControlVariable, 
								UefiGetQuestionOffset(ControlPtr),
								numeric->ControlData.ControlDataWidth, Num );
			}
		 if(*Num < numeric->MinValue)
			*Num = numeric->MinValue;//revert to minimum value 

        if(*Num > numeric->MaxValue)
			*Num =numeric->MaxValue;//revert to maximum value 
		}

		numeric->Value = *Num;

		MemFreePointer( (VOID **)&Num );
	}

	NumSPrint(numeric,numeric->Value);
#if 0
	/*To eliminate leading zeroes*/
	Num = atoi( numeric->Text, numeric->Base );
	SPrint( numeric->Text, numeric->TextAreaWidth, L"%d", Num);
#endif
	return gEdit.Draw( numeric );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericSetCallback
//
// Description:	function used for setting Numeric control callback.
//
// Input:	  NUMERIC_DATA *numeric, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericSetCallback( NUMERIC_DATA *numeric, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gEdit.SetCallback( numeric, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericHandleAction
//
// Description:	function used handle the Numeric controls
//
// Input:	NUMERIC_DATA *numeric, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericHandleAction( NUMERIC_DATA *numeric, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;


	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		if(numeric->ControlActive)
			return Status;

		if (numeric->Interval == 0)
			return Status;

		if(IsActiveControlPresent(gApp->PageList[gApp->CurrentPage]))
			return Status;

		if ( --(numeric->Interval) == 0 )
		{
			// initialize the interval
			numeric->Interval = (UINT8)(numeric->ControlData.ControlFlags.ControlRefresh);
			return UefiRefershQuestionValueNvRAM(&(numeric->ControlData));
		}
		else
			return Status;
	}

     if (( Data->Input.Type == ACTION_TYPE_KEY )||(Data->Input.Type == ACTION_TYPE_MOUSE))
		return NumericHandleActionKeyMouse(numeric, Data);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckforIncrementandDecreament
//
// Description:	function used handle the Numeric controls Increment and Decreament operation
//
// Input:	NUMERIC_MIN_MAX_BASE *Num, NUMERIC_DATA *numeric,  CONTROL_ACTION Action,UINT8 *bValueChanged 
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CheckforIncrementandDecreament(NUMERIC_MIN_MAX_BASE *Num, NUMERIC_DATA *numeric,  CONTROL_ACTION Action,UINT8 *bValueChanged )
{
	if(ControlActionIncreament == Action)
	{
		if(AMI_BASE_INT_DEC == numeric->Base)
		{
				if(numeric->ControlData.ControlDataWidth == 1)
				{
					if ( ((INT8)*Num + (INT8)numeric->Step) <= (INT8)numeric->MaxValue )
					{
						*Num = *Num + (NUMERIC_MIN_MAX_BASE)numeric->Step;
						*bValueChanged = 1;	
					}
				}
				else if(numeric->ControlData.ControlDataWidth == 2)
				{
					if ( ((INT16)*Num + (INT16)numeric->Step) <= (INT16)numeric->MaxValue )
					{
						*Num = *Num + (NUMERIC_MIN_MAX_BASE)numeric->Step;
						*bValueChanged = 1;
						
					}
				}
				else if(numeric->ControlData.ControlDataWidth == 4)
				{
					if ( ((INT32)*Num + (INT32)numeric->Step) <= (INT32)numeric->MaxValue )
					{
						*Num = *Num + (NUMERIC_MIN_MAX_BASE)numeric->Step;
						*bValueChanged = 1;
						
					}
				}
				else
				{
					if ( ((INT64)*Num + (INT64)numeric->Step) <= (INT64)numeric->MaxValue )
					{
						*Num = *Num + (NUMERIC_MIN_MAX_BASE)numeric->Step;
						*bValueChanged = 1;
						
					}
				}
			
		}
		else
		{
			if ( *Num + numeric->Step <= numeric->MaxValue )
			{
							*Num = *Num + (NUMERIC_MIN_MAX_BASE)numeric->Step;
							*bValueChanged = 1;
			}
		}
	}
	else
	{
		if(AMI_BASE_INT_DEC == numeric->Base)
		{
				if(numeric->ControlData.ControlDataWidth == 1)
				{		
					if ( ((INT8)*Num - (INT8)numeric->Step) >= (INT8)numeric->MinValue)
					{
						*Num = *Num - (NUMERIC_MIN_MAX_BASE)numeric->Step;
						*bValueChanged = 1;
						
					}
				}
				else if(numeric->ControlData.ControlDataWidth == 2)
				{
					if ( ((INT16)*Num - (INT16)numeric->Step) >= (INT16)numeric->MinValue )
					{
						*Num = *Num - (NUMERIC_MIN_MAX_BASE)numeric->Step;
						*bValueChanged = 1;
						
					}
				}
				else if(numeric->ControlData.ControlDataWidth == 4)
				{
					if ( ((INT32)*Num - (INT32)numeric->Step) >= (INT32)numeric->MinValue)
					{
						*Num = *Num - (NUMERIC_MIN_MAX_BASE)numeric->Step;
						*bValueChanged = 1;
						
					}
				}
				else
				{
					if ( ((INT64)*Num - (INT64)numeric->Step) >= (INT64)numeric->MinValue )
					{
						*Num = *Num - (NUMERIC_MIN_MAX_BASE)numeric->Step;
						*bValueChanged = 1;
						
					}
				}

			
		}
		else
		{
			if( *Num - numeric->Step >= numeric->MinValue )
			 {
				*Num = *Num - (NUMERIC_MIN_MAX_BASE)numeric->Step;
				*bValueChanged = 1;
			 }
		}
			
	}


}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericHandleActionKey
//
// Description:	function used handle the Numeric control keys
//
// Input:	 NUMERIC_DATA *numeric, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericHandleActionKeyMouse(NUMERIC_DATA *numeric, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	CHAR16 Chr;
	BOOLEAN DataOk = FALSE;
	NUMERIC_MIN_MAX_BASE Num;
	ACTION_DATA TempData;
    CONTROL_ACTION Action;
    AMI_EFI_KEY_DATA key;
	VOID * ControlPtr = numeric->ControlData.ControlPtr;
    UINT8 u8ChkResult;

    u8ChkResult = CheckControlCondition( &numeric->ControlData );
	 
	 //Not to perform action for control when token TSE_SETUP_GRAYOUT_SELECTABLE is enable to set focus for GrayoutIf control
    if ( IsGrayoutSelectable() && (COND_GRAYOUT == u8ChkResult) ) {
        return EFI_UNSUPPORTED;
    }

    if(numeric->ControlData.ControlFlags.ControlReadOnly)
		return EFI_UNSUPPORTED;

    key  = Data->Input.Data.AmiKey;
    //Get mapping
	if(Data->Input.Type == ACTION_TYPE_KEY)
	{	
      Action = MapControlKeysHook(key);
	}
	else if(Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);
		//EIP-123727 check whether MouseTop is within the Height and Width of Neumeric Control or not
		if	(	(ControlActionSelect == Action) &&
			 	(	(Data->Input.Data.MouseInfo.Top >= (UINT32)numeric->Top) && 
					(Data->Input.Data.MouseInfo.Top < (UINT32)(numeric->Top+numeric->Height)) &&
					(Data->Input.Data.MouseInfo.Left >= (UINT32)numeric->Left) && 
					(Data->Input.Data.MouseInfo.Left < (UINT32)(numeric->Left+numeric->Width))
				)//EIP-139608 when mouse is clicked on numeric control and action is ControlActionSelect
		)
		{
			Action = ControlActionSelect;		
			if(!TSEMouseIgnoreMouseActionHook())
			{
				if (numeric->Base == AMI_BASE_INT_DEC || numeric->Base == AMI_BASE_DEC)
					NumericSoftKbdInit();
				else if (numeric->Base == AMI_BASE_HEX || numeric->Base == AMI_BASE_OCT)
				{
					PrintableKeysSoftKbdInit();
				}
			}
		}
		//EIP-123727 Close softkbd if activatd when clicked/touch outside numeric
		else if ( ((!((Data->Input.Data.MouseInfo.Top >= (UINT32)numeric->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(numeric->Top+numeric->Height))&& (Data->Input.Data.MouseInfo.Left >= (UINT32)numeric->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(numeric->Left+numeric->Width)))))
					&&(TSEMouseIgnoreMouseActionHook())&&(( ControlMouseActionLeftDown== Action)||(ControlMouseActionLeftUp == Action))
		)
		{
			if (numeric->Base == AMI_BASE_INT_DEC || numeric->Base == AMI_BASE_DEC)
				NumericSoftKbdExit();
			else if (numeric->Base == AMI_BASE_HEX || numeric->Base == AMI_BASE_OCT)
			{
				PrintableKeysSoftKbdExit();
			}

			gAction.ClearAction( Data );
			return EFI_UNSUPPORTED;
		}

		//If mouse clicked outside numeric control area
		else if	( ((Data->Input.Data.MouseInfo.Top < (UINT32)numeric->Top) ||
						(Data->Input.Data.MouseInfo.Top > (UINT32)(numeric->Top+numeric->Height)) ||
						(Data->Input.Data.MouseInfo.Left < (UINT32)numeric->Left) ||
						(Data->Input.Data.MouseInfo.Left > (UINT32)(numeric->Left+numeric->Width))
						)&& ( (ControlActionSelect == Action) && SingleClickActivation() ) //EIP-139608 
		)
		{
			return EFI_UNSUPPORTED;	
		}

		//If mouse clicked in numeric control area including multi-line string also don't consume mouse action in numeric side.
		else if ((Data->Input.Data.MouseInfo.Top >= (UINT32)numeric->Top) && 
					(Data->Input.Data.MouseInfo.Top < (UINT32)(numeric->Top+numeric->Height)) && 
					(Data->Input.Data.MouseInfo.Left >= (UINT32)numeric->Left) && 
					(Data->Input.Data.MouseInfo.Left < (UINT32)(numeric->Left+numeric->Width))&& 
					(numeric->ControlActive)
		)
		{
			return EFI_UNSUPPORTED;	
		}

	}
	
    switch(Action)
    {
        case ControlActionSelect:      		
			// check that the data is proper.
			if((numeric->Text[0] ==0x0)||((numeric->Base == AMI_BASE_INT_DEC)&&(L'-' == numeric->Text[0])&&( EfiStrStr(numeric->Text+1, L"-"))))
					 NumSPrint(numeric,numeric->MinValue);
			
			Num = (NUMERIC_MIN_MAX_BASE)atoi( numeric->Text, numeric->Base );

			//EIP:60563 to support signed integers for NUMERIC opcode
			if ( CheckForRangefromsetup( numeric, &Num) )
			{
				if ( ( numeric->Callback != NULL ) && ( numeric->Cookie != NULL ) )
				{
					CALLBACK_VARIABLE *callbackData = (CALLBACK_VARIABLE *)numeric->Cookie;

					callbackData->Variable = numeric->ControlData.ControlVariable;
					callbackData->Offset = UefiGetQuestionOffset(ControlPtr);
					callbackData->Length = UefiGetWidth(ControlPtr);
					callbackData->Data = (VOID *)&Num;
					// To support UEFI 2.1.C spec to Not to update the control when Callback fails.
					UefiPreControlUpdate(&(numeric->ControlData));
					numeric->Callback( numeric->Container,numeric, numeric->Cookie );
				}

                {
					if(UefiIsInteractive(&numeric->ControlData))
                    {
            			VOID * Handle=numeric->ControlData.ControlHandle;
            			UINT16 Key = UefiGetControlKey(&(numeric->ControlData));
            			CONTROL_DATA *Control;
            
            			Status = CallFormCallBack(&(numeric->ControlData), Key, 0, AMI_CALLBACK_CONTROL_UPDATE);//EIP-53480: Updated the action to AMI_CALLBACK_CONTROL_UPDATE
            			Control = GetUpdatedControlData((CONTROL_DATA*)numeric,CONTROL_TYPE_NUMERIC,Handle,Key);

            			if(Control == NULL) // Control deleted ?
            				return EFI_SUCCESS;
            			if(Control != (CONTROL_DATA*)numeric)
            				numeric = (NUMERIC_DATA*)Control; //control Updated

                    }
                }

				Status = EFI_SUCCESS;				
				numeric->ControlActive = FALSE;
				if(((Data->Input.Type == ACTION_TYPE_KEY))&&(TSEMouseIgnoreMouseActionHook() == TRUE)&& (TRUE == NumericIncDec))
				{
					if (numeric->Base == AMI_BASE_INT_DEC || numeric->Base == AMI_BASE_DEC)
						NumericSoftKbdExit();
					else if (numeric->Base == AMI_BASE_HEX || numeric->Base == AMI_BASE_OCT)
					{
						PrintableKeysSoftKbdExit();
					}
				}
				else if(!NumericIncDec)
				{
					NumericIncDec = TRUE;	
				}
			}
			else
			{
				//Report Message box
		  		CallbackShowMessageBox( (UINTN)gInvalidRangeFailMsgBox, MSGBOX_TYPE_OK );
				Data->Input.Type = ACTION_TYPE_KEY;//EIP 83703 : Providing the input type as key such that it can be consumed in edithandleaction 
				Data->Input.Data.AmiKey.Key.ScanCode = SCAN_ESC;
				Data->Input.Data.AmiKey.Key.UnicodeChar = L'\0';
				ClearNumericShiftState(&(Data->Input.Data.AmiKey));//EIP-83703 
				//Data->Input.Data.AmiKey.KeyState.KeyShiftState = 0;//EIP 83703 : providing the key shiftstate
				DataOk = TRUE;
			}
        break;

        case ControlActionBackSpace:
    		DataOk = TRUE;
        break;

        case ControlActionIncreament:
        case ControlActionDecreament:
			if ( ( numeric->Step != 0 ) && ( ! numeric->ControlActive ))
			{
				UINT8 bValueChanged = 0;

				Num = (NUMERIC_MIN_MAX_BASE)atoi( numeric->Text, numeric->Base );
				if ( ControlActionIncreament == Action )
				{
					if(Num == numeric->MaxValue);
					else
					 CheckforIncrementandDecreament(&Num,numeric,Action,&bValueChanged);
                   /*     if ( Num + numeric->Step <= numeric->MaxValue )
						{
							Num = Num + (NUMERIC_MIN_MAX_BASE)numeric->Step;
							bValueChanged = 1;
						}*/
				}
				else if ( ControlActionDecreament == Action )
				{
					if(Num == numeric->MinValue);
				    else
					CheckforIncrementandDecreament(&Num,numeric,Action,&bValueChanged);
                   /* if( Num - numeric->Step >= numeric->MinValue )
					{
						Num = Num - (NUMERIC_MIN_MAX_BASE)numeric->Step;
						bValueChanged = 1;
					}*/
				}

                NumSPrint(numeric,Num);
				NumericIncDec = FALSE;
				if((bValueChanged)&& CheckForRangefromsetup( numeric, &Num))
				{
					MemCopy(&TempData,Data,sizeof(ACTION_DATA));
					TempData.Input.Data.AmiKey.Key.ScanCode = 0;
					TempData.Input.Data.AmiKey.Key.UnicodeChar = CHAR_CARRIAGE_RETURN;
					ClearNumericShiftState(&(TempData.Input.Data.AmiKey));//EIP-92407 Clearing the Shiftstate before invoking numerichandleaction with CHAR_CARRIAGE_RETURN
					gNumeric.HandleAction(numeric,&TempData);
				}
				// Data updated to variables Now draw it in the screen.
				Status = gNumeric.Draw( numeric );
			}
			else if( ( numeric->ControlActive )&&(numeric->Base == AMI_BASE_INT_DEC))
			{
				DataOk = TRUE;
			}
			
        break;

        case ControlActionAlpha:
        case ControlActionNumeric:
            Chr = key.Key.UnicodeChar;
            switch ( numeric->Base )
			{
					case AMI_BASE_BIN:
						if ( ( Chr == L'0' ) || ( Chr == L'1' ) )
							DataOk = TRUE;
						break;

					case AMI_BASE_OCT:
						if ( ( Chr <= L'7' ) && ( Chr >= L'0' ) )
							DataOk = TRUE;
						break;

					case AMI_BASE_DEC:
                    case AMI_BASE_INT_DEC:
						if ( ( Chr <= L'9' ) && ( Chr >= L'0' ) )
							DataOk = TRUE;
						break;

					case AMI_BASE_HEX:
						// EIP: 26473  To support uppercase Hex numbers
						if ( ( ( Chr <= L'9' ) && ( Chr >= L'0' ) ) || ( ( Chr >= L'a' ) && ( Chr <= L'f' ) ) || ( ( Chr >= L'A' ) && ( Chr <= L'F' ) ))

							DataOk = TRUE;
						break;
			}
        break;

        case ControlActionNextUp:
        case ControlActionNextDown:
        case ControlActionNextLeft:
        case ControlActionNextRight:
			if ( numeric->ControlActive )
			{
				MemCopy(&TempData,Data,sizeof(ACTION_DATA));
				TempData.Input.Data.AmiKey.Key.ScanCode = 0;
			    TempData.Input.Data.AmiKey.Key.UnicodeChar = CHAR_CARRIAGE_RETURN;
				ClearNumericShiftState(&(TempData.Input.Data.AmiKey));//EIP-92407 Clearing the Shiftstate before invoking numerichandleaction with CHAR_CARRIAGE_RETURN
				gNumeric.HandleAction(numeric,&TempData);
			} 
        break;

        default:
			if ( numeric->ControlActive )
			{
				MemCopy(&TempData,Data,sizeof(ACTION_DATA));
				TempData.Input.Type = ACTION_TYPE_KEY;
				TempData.Input.Data.AmiKey.Key.ScanCode = 0;
			    TempData.Input.Data.AmiKey.Key.UnicodeChar = CHAR_CARRIAGE_RETURN;
				ClearNumericShiftState(&(TempData.Input.Data.AmiKey));//EIP-83703 
				//TempData.Input.Data.AmiKey.KeyState.KeyShiftState = 0;
				gNumeric.HandleAction(numeric,&TempData);
			} 
			// Only Alpha Numeric chars are allowed. Other Special printable chars not allowed.
			if(Data->Input.Data.AmiKey.Key.ScanCode)
	            DataOk = TRUE;
        break;
    }

	if ( DataOk )	
		Status = gEdit.HandleAction( numeric, Data );

	if((((!numeric->ControlActive)||(!IsMouseClickedonSoftkbd())) && (TSEMouseIgnoreMouseActionHook() == TRUE) )
		&&	(((Data->Input.Type == ACTION_TYPE_KEY) && ((Action == ControlActionNextLeft) ||(Action == ControlActionNextRight) ||(Action == ControlActionNextUp) ||(Action == ControlActionNextDown) ||(Action == ControlActionPageUp) ||(Action == ControlActionPageDown) ||(Action == ControlActionAbort) ||(Action == ControlActionHome) ||(Action == ControlActionEnd) ||(CheckKeyinHotKeysList(key))) ) 
				|| ((Data->Input.Type == ACTION_TYPE_MOUSE)&&((!((Data->Input.Data.MouseInfo.Top >= (UINT32)numeric->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(numeric->Top+numeric->Height))&& (Data->Input.Data.MouseInfo.Left >= (UINT32)numeric->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(numeric->Left+numeric->Width))))||(Action == ControlActionAbort))))
			)
	{
		if (numeric->Base == AMI_BASE_INT_DEC || numeric->Base == AMI_BASE_DEC)
				NumericSoftKbdExit();
		else if (numeric->Base == AMI_BASE_HEX || numeric->Base == AMI_BASE_OCT)
		{
			PrintableKeysSoftKbdExit();
		}
	}
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericSetFocus
//
// Description:	Function to set focus.
//
// Input:	  NUMERIC_DATA *numeric, BOOLEAN focus
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericSetFocus( NUMERIC_DATA *numeric, BOOLEAN focus )
{
	 UINT8 u8ChkResult;
	 
	if(focus != FALSE)
	{
		u8ChkResult = CheckControlCondition( &numeric->ControlData );
		
		//Setting focus to control which has no control-condtion and token TSE_SETUP_GRAYOUT_SELECTABLE is enable to set focus for GrayoutIf control
		if ( ((u8ChkResult != COND_NONE) && (u8ChkResult != COND_GRAYOUT)) ||
		     (!IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT))
		   ){
			return EFI_UNSUPPORTED;
		}
	}

	
	if( !(numeric->ControlFocus && focus) )
		numeric->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericSetPosition
//
// Description:	Function to set position.
//
// Input:		NUMERIC_DATA *numeric, UINT16 Left, UINT16 Top 
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericSetPosition(NUMERIC_DATA *numeric, UINT16 Left, UINT16 Top )
{
	return gEdit.SetPosition( numeric, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericSetDimensions
//
// Description:	Function to set dimensions.
//
// Input:		NUMERIC_DATA *numeric, UINT16 Width, UINT16 Height
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericSetDimensions(NUMERIC_DATA *numeric, UINT16 Width, UINT16 Height )
{
	return gEdit.SetDimensions( numeric, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		NUMERIC_DATA *numeric, UINT8 FGColor, UINT8 BGColor
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericSetAttributes(NUMERIC_DATA *numeric, UINT8 FGColor, UINT8 BGColor )
{
	return gEdit.SetAttributes( numeric, FGColor, BGColor );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumericGetControlHeight
//
// Description:	Function to get label height.
//
// Input:		NUMERIC_DATA *numeric, UINT16 Width, UINT16 *height
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NumericGetControlHeight(NUMERIC_DATA *numeric, VOID* frame , UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
	
		Width = (UINT16)(((EDIT_DATA *)numeric)->TextMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gControlLeftPad));
		text = HiiGetString( numeric->ControlData.ControlHandle, UefiGetPromptField((VOID *)numeric->ControlData.ControlPtr));
		if ( text == NULL )
			return EFI_OUT_OF_RESOURCES;
	
		newText = StringWrapText( text, Width, height );
	
	    (*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
		MemFreePointer( (VOID **)&text );
	}
	else
	{
		*height =1;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NumSPrint
//
// Description:	Function to print nums.
//
// Input:		NUMERIC_DATA *numeric,NUMERIC_MIN_MAX_BASE Num
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NumSPrint(NUMERIC_DATA *numeric,NUMERIC_MIN_MAX_BASE Num)
{
	switch(numeric->Base)
	{
		case AMI_BASE_HEX:
			SPrint( numeric->Text, numeric->TextWidth*sizeof(CHAR16), L"%lx", Num );
			break;
        case AMI_BASE_INT_DEC:
			if(numeric->ControlData.ControlDataWidth == 1)
			{
				if((INT8)Num < 0)
				{
					SPrint( numeric->Text, numeric->TextWidth*sizeof(CHAR16), L"%d", (INT8)Num );
					break;
				}
			}
			else if(numeric->ControlData.ControlDataWidth == 2)
			{
				if((INT16)Num < 0)
				{
					SPrint( numeric->Text, numeric->TextWidth*sizeof(CHAR16), L"%d", (INT16)Num );	
					break;
				}
			}
			else if(numeric->ControlData.ControlDataWidth == 4)
			{
				if((INT32)Num < 0)
				{
					SPrint( numeric->Text, numeric->TextWidth*sizeof(CHAR16), L"%d", (INT32)Num );	
					break;
				}
			}
			else if(numeric->ControlData.ControlDataWidth == 8)
			{
				if((INT64)Num < 0)
				{
					SPrint( numeric->Text, numeric->TextWidth*sizeof(CHAR16), L"%ld", (INT64)Num );	
					break;
				}
			}
			SPrint( numeric->Text, numeric->TextWidth*sizeof(CHAR16), L"%d", Num );
            break;
		case AMI_BASE_DEC:
		default:
			SPrint( numeric->Text, numeric->TextWidth*sizeof(CHAR16), L"%ld", Num );
			break;
	}
	UpdateNumericDisplayString (&(numeric->Text), Num, numeric->Base, numeric->ControlData.ControlDataWidth, numeric->TextWidth*sizeof(CHAR16)); //EIP66976 Provision to change the Numeric string format
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
