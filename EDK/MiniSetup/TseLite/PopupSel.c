//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupSel.c $
//
// $Author: Premkumara $
//
// $Revision: 40 $
//
// $Date: 8/28/14 3:09p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupSel.c $
// 
// 40    8/28/14 3:09p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 39    5/02/14 9:36p Arunsb
// EIP141986 changes reverted.
// 
// 38    5/02/14 10:54a Premkumara
// [TAG]  		EIP141986
// [Category]  	New Feature
// [Description]  	Made Grayed controls to focus-able when token
// TSE_SETUP_GRAYOUT_SELECTABLE
//  is enabled and can't edit the values
// [Files]  		AMITSE.sdl,CommonHelper.c,frame.c,Label.c,minisetupext.h,
// numeric.c,PopupPassword.c,PopupSel.c,PopupString.c,SubMenu.c
// 
// 37    5/01/14 3:45p Premkumara
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
// 36    2/11/14 8:37p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 35    12/03/13 1:12p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 34    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 17    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 32    9/25/12 11:44a Blaines
// [TAG] - EIP 101903
// [Category] - Defect
// [Synopsis] -  Enabling Multiline in TSE cause a crash when entering in
// TSE
// [Root cause] If SPrint is called with a string that exceeds the
// buffersize, overflow occurs and exception happens. 
// [Solution] Call Sprint using only the printable length copy of the
// original string.
// [Files] - Popupsel.c
// [Function] - PopupSelGetControlHeight 
// 
// 31    9/18/12 5:08a Arunsb
// [TAG]  		EIP95139
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	BootOrder and DriverOrder cases are not handled preoperly
// in _PopupSelGetSelection() function
// [Files]  		PopupSel.c
// 
// 30    9/17/12 6:20a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 28    9/06/12 1:02a Rajashakerg
// [TAG]  		EIP91410 
// [Category]  	Improvement
// [Description]  	TSE_MULTILINE_CONTROLS=1 makes one of option with max
// string looks not good.
// [Files]  		PopupSel.c, COmmonHelper.c, AMITSE.sdl
// 
// 27    2/01/12 8:05p Blaines
// [TAG] - EIP 81631 
// [Category]- Sighting
// [Synopsis]- In some SAS cards,  HII Adapter Settings screen is not
// wrapping the text correctly
// [Solution] - Use the proper control width calculation to determine
// control height in PopupSelGetControlHeight.
// The string length calculation used to determine control height in
// SubMenuGetControlHeight needs to be consistent with the same in
// SubMenuDraw.  
// 	
// [Files]
// Submenu.c, PopupSel.c,
// 
// 26    2/01/12 3:33a Arunsb
// [TAG]  		EIP81603 
// [Category]  	Improvement
// [Description]  	If any option is not obtained then default option is
// used
// [Files]  		PopupSel.c
// 
// 25    1/31/12 7:04p Blaines
// [TAG] - EIP 81631 
// [Category]- Sighting
// [Synopsis]- In some SAS cards,  HII Adapter Settings screen is not
// wrapping the text correctly
// [Solution] - Allow max space when creating controls in the functions
// FrameAddControl, FrameDraw.
// Allow max space for computing height in PopupSelGetControlHeight,
// TextGetControlHeight PopupSelDraw, TextDraw.  
// 	
// [Files]
// Text.c, PopupSel.c, frame.c
// 
// 24    1/18/12 6:37a Rajashakerg
// [TAG]  		EIP79949 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Text srting is not wrapped in "Advanced -> Super IO config.
// -> Floppy disk controller config. -> Change settings" option when
// TSE_MULTILINE_CONTROLS token enabled.
// [RootCause]  	The calculation was not proper to show maximum string in
// the left control area for popupsel control.
// [Solution]  	Adjusted the cordinates to show maximum string in control
// left area
// [Files]  		PopupSel.c
// 
// 23    1/05/12 12:27a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupString.c, SubMenu.c, Text.c,PopupSel.c.
// 
// 22    12/07/11 8:18a Rajashakerg
// [TAG]  		EIP75118 
// [Category]  	Improvement
// [Description]  	xtractConfig() fail since BrowserCallback() cannot find
// the variable to process
// [Files]  		FormBrowser2.c, FormBrowser2.h, HiiCallback.c,
// Uefi21Wapper.c, PopupSel.c
// 
// 21    12/05/11 7:05p Blaines
// [TAG] - EIP 77040 
// [Category]- Sighting
// [Synopsis]- Setup: Boot Option Priority list items truncated, until you
// move within the tab.
// [Solution] - In the function PopupSelGetControlHeight, call the
// function _PopupSelGetSelection to get the current selection before
// computing the control height. 
// 	
// [Files]
// PopupSel.c
// 
// 20    11/30/11 1:33p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 19    11/21/11 11:12a Premkumara
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
// 18    11/14/11 6:55p Blaines
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
// 17    11/13/11 1:05p Arunsb
// [TAG]  		EIP70421
// [Category]  	New Feature
// [Description]  	Support for driver order in TSE
// [Files]  		AMITSE.SDL, CommonHelper.c, setup.ini, uefisetup.ini,
// boot.c,
// minisetup.h, bbs.c, special.c, special.h, tseadvanced.c,
// addbootoption.c,
// callback.c, minisetupext.c, minisetupext.h, popupsel.c, popupsel.h,
// TseLitehelper.c, variable.c, Uefi21Wapper.c, AMIVfr.h, boot.h,
// TseElink.h, variable.h, 
// setup.h, Boot.vfr and Setup.uni
// 
// 16    10/20/11 12:03p Madhans
// Check in comment corrected.
// 
// 15    9/19/11 11:50a Blaines
// [TAG]  		EIP 68920
// [Category]  	Defect
// [Symptom]  	SOME SAS controller card HII menus hang when selecting "Clear
// Configuration" when DEBUG_MODE=0
// [RootCause]  	Menu is not re-initialize from SetupData after dynamic
// page update. 
// PopupSelGetControlHeight() causes an assert if popupSel has an item
// with an invalid string token.  
// 		
// [Solution]	Due to dynamic updates, SetupData (most current data) is
// given priority when re-initializing menu. 
// Check for invalid string token in PopupSelGetControlHeight.		
// 
// [Files Changed]
// - Menu.c, Popupsel.c
// 
// 14    8/26/11 2:10p Blaines
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
// 13    3/28/11 11:40p Madhans
// [TAG]  		EIP50878
// [Category]  	Improvement
// [Description]  	Support to move the Control With Boot Order Change.
// [Files]  		AMITSE.sdl
// commonoem.c
// minisetup.h
// popupsel.c
// 
// 12    3/21/11 12:40a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 11    3/09/11 7:23p Madhans
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
// 8     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 7     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 6     3/26/10 5:06p Madhans
// EIP 36704 : Fix for Making sure to make the Variable to NULL after it
// is Freed up.
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
// 8     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 7     1/09/10 6:57a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 6     9/15/09 9:48a Sudhirv
// updated the Add Del Boot Option support
// 
// 5     8/13/09 1:20p Blaines
// EIP #24980 Fix to properly display right area text
// 
// 4     8/13/09 7:40a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
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
// 1     4/28/09 11:06p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:12p Madhans
// TSE Lite Special control support
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
// Name:		PopupSel.c
//
// Description:	This file contains code to handle Popup selections
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

BOOLEAN OneofMultilineDisable(POPUPSEL_DATA *popupSel);
VOID _PopupSelGetSelection( POPUPSEL_DATA *popupSel );
static BOOLEAN bSelectionChanged = FALSE;

extern EFI_STATUS _FrameScroll( FRAME_DATA *frame, BOOLEAN bScrollUp );
extern UINT16 _gHDOrderPageID;
extern UINT16 _gCDOrderPageID;
extern UINT16 _gFDOrderPageID;
extern UINT16 _gNetOrderPageID;
extern UINT16 _gBevOrderPageID;

POPUPSEL_METHODS gPopupSel =
{
	PopupSelCreate,
	PopupSelDestroy,
	PopupSelInitialize,
	PopupSelDraw,
	PopupSelHandleAction,
	PopupSelSetCallback,
	PopupSelSetFocus,
	PopupSelSetPosition,
	PopupSelSetDimensions,
	PopupSelSetAttributes,
    PopupSelGetControlHeight
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelCreate
//
// Description:	this function uses the create function of control
//					and creates the Popup Selected
//
// Input:	POPUPSEL_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelCreate( POPUPSEL_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(POPUPSEL_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gPopupSel;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys the Popup Selected
//
// Input:	POPUPSEL_DATA *popupSel, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelDestroy( POPUPSEL_DATA *popupSel, BOOLEAN freeMem )
{
	if(NULL == popupSel)
	  return EFI_SUCCESS;

	gControl.Destroy( popupSel, FALSE );

	if ( popupSel->ListBoxCtrl )
		gListBox.Destroy( popupSel->ListBoxCtrl, TRUE );

	popupSel->ListBoxCtrl = NULL;

	if( freeMem )
	{
		MemFreePointer( (VOID **)&(popupSel->PtrTokens) );
		MemFreePointer( (VOID **)&popupSel );

	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelInitialize
//
// Description:	this function uses the initialize function of control
//					and initializes the Popup Selected
//
// Input:	POPUPSEL_DATA *popupSel, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelInitialize( POPUPSEL_DATA *popupSel, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 Index = 0;
	UINT16 *OptionList=NULL;
	UINT64 *ValueList=NULL;


	Status = gControl.Initialize( popupSel, data );
	if (EFI_ERROR(Status))
		return Status;

	popupSel->PopupSelHandle = popupSel->ControlData.ControlHandle;
	popupSel->Title = UefiGetPromptField(popupSel->ControlData.ControlPtr);

	// add extra initialization here...
	Status = UefiGetOneOfOptions(&popupSel->ControlData,&popupSel->PopupSelHandle,
			&OptionList, &ValueList, &popupSel->ItemCount,&popupSel->bInteractive,&popupSel->CallBackKey);

	if (EFI_ERROR(Status))
		return Status;

	popupSel->Interval = (UINT8)(popupSel->ControlData.ControlFlags.ControlRefresh);

	if( popupSel->PtrTokens != NULL )
      MemFreePointer( (VOID **)&(popupSel->PtrTokens));
	popupSel->PtrTokens = EfiLibAllocatePool( popupSel->ItemCount * sizeof(PTRTOKENS) );
	if ( popupSel->PtrTokens == NULL )
		Status = EFI_OUT_OF_RESOURCES;
	else
	{
		for( Index = 0; Index < popupSel->ItemCount; Index++ )
		{
			popupSel->PtrTokens[Index].Option = OptionList[Index];
			popupSel->PtrTokens[Index].Value = ValueList[Index];
		}

	    MemFreePointer( (VOID **)&(OptionList));
	    MemFreePointer( (VOID **)&(ValueList));

		if(popupSel->ControlData.ControlFlags.ControlInteractive)
	    {
			popupSel->bInteractive = TRUE;
			popupSel->CallBackKey = popupSel->ControlData.ControlKey;
		}

	    // boundary overflow  check

		popupSel->ListBoxCtrl = NULL;
		popupSel->ListBoxEnd = FALSE;
		popupSel->LabelMargin = (UINT8)gControlLeftMargin;

		// We dont have to do Get selection here it is done before we draw a page
		//_PopupSelGetSelection( popupSel );

		SetControlColorsHook(&(popupSel->BGColor), &(popupSel->FGColor), NULL, NULL ,&(popupSel->SelBGColor), &(popupSel->SelFGColor),
			                    NULL , &(popupSel->NSelFGColor),NULL,&(popupSel->LabelFGColor) ,
								&(popupSel->NSelLabelFGColor),NULL ,NULL,NULL, NULL );
	
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelDraw
//
// Description:	function to draw the specific popup window
//
// Input:	POPUPSEL_DATA *popupSel
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelDraw( POPUPSEL_DATA *popupSel )
{
	CHAR16 *text=NULL,*text1=NULL;
	UINTN i=0,Len=0;
	EFI_STATUS Status = EFI_SUCCESS;
	UINT16 Index = 0, TempHeight=0;
	UINT16 *OptionList=NULL;
	UINT64 *ValueList=NULL;
	
	UINT16 tmpHeight=0;

	UINT8 ColorNSel = popupSel->NSelFGColor;
	UINT8 ColorLabel = (popupSel->ControlFocus) ? popupSel->LabelFGColor : popupSel->NSelLabelFGColor ;

	if(  popupSel->ListBoxCtrl != NULL)
	{
		gListBox.Draw( popupSel->ListBoxCtrl );
	}
	else
	{
		// check conditional ptr if necessary
        //EIP 75486 Support grayout condition for readonly controls
		//if( popupSel->ControlData.ControlConditionalPtr != 0x0)
		//{
			switch( CheckControlCondition( &popupSel->ControlData ) )
			{
				case COND_NONE:
					break;
				case COND_GRAYOUT:
					Status = EFI_WARN_WRITE_FAILURE;
					ColorNSel =  ColorLabel = CONTROL_GRAYOUT_COLOR;
					break;
				default:
					return EFI_UNSUPPORTED;
					break;
			}
		//}
		// If not Special
		if(TseLiteIsSpecialOptionList((CONTROL_DATA *)popupSel) != TRUE)
		{
			Status = UefiGetOneOfOptions(&popupSel->ControlData,&popupSel->PopupSelHandle,
					&OptionList, &ValueList, &popupSel->ItemCount,NULL,NULL);
			if (EFI_ERROR(Status))
				return Status;
			for( Index = 0; Index < popupSel->ItemCount; Index++ )
			{
				popupSel->PtrTokens[Index].Option = OptionList[Index];
				popupSel->PtrTokens[Index].Value = ValueList[Index];
			}
			MemFreePointer( (VOID **)&(OptionList));
			MemFreePointer( (VOID **)&(ValueList));
		}

		_PopupSelGetSelection( popupSel );
		text1 = HiiGetString( popupSel->ControlData.ControlHandle, popupSel->Title );
		if ( text1 != NULL )
		{
			//Eip TSE_MULTILINE_CONTROLS moved to binary
			if(popupSel->Height>1 && IsTSEMultilineControlSupported())
			{	
				DrawMultiLineStringWithAttribute( (UINTN)popupSel->Left, (UINTN) popupSel->Top, 
						(UINTN)(popupSel->LabelMargin - popupSel->Left),(UINTN) popupSel->Height,
						text1, popupSel->BGColor |  ColorLabel );
			}
			else
			{
	            // boundary overflow  check
				if((TestPrintLength( text1) / (NG_SIZE))> (UINTN)(popupSel->LabelMargin - popupSel->Left  ))
					text1[HiiFindStrPrintBoundary(text1 ,(UINTN)(popupSel->LabelMargin - popupSel->Left  ))] = L'\0';
	
				DrawStringWithAttribute( popupSel->Left , popupSel->Top, (CHAR16*)text1, 
						popupSel->BGColor |  ColorLabel  );

			}
			MemFreePointer( (VOID **)&text1 );
		}

		/*EfiStrCpy(text, L"[");
		DrawStringWithAttribute( popupSel->Left + popupSel->LabelMargin , popupSel->Top, (CHAR16*)text, 
				(UINT8)( (popupSel->ControlFocus) ? 
						 popupSel->SelBGColor  | popupSel->SelFGColor : 
						  popupSel->BGColor  | ColorNSel ));
*/
	
        text1 = HiiGetString( popupSel->PopupSelHandle, popupSel->PtrTokens[popupSel->Sel].Option);
		//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
		if(popupSel->Height>1 && OneofMultilineDisable(popupSel))
		{
			TempHeight = popupSel->Height;
			popupSel->Height = 1;
		}
		
		if(popupSel->Height>1 && IsTSEMultilineControlSupported())
		{
			Len = TestPrintLength( text1 ) / (NG_SIZE);
			text = EfiLibAllocateZeroPool( (Len+3)*2 ); 
			SPrint( text,(UINTN)( (Len+3)*2 )/*(popupSel->Width - popupSel->Left - popupSel->LabelMargin +2)*/, L"[%s]", text1 );
			MemFreePointer( (VOID **)&text1 );	

			text1 = StringWrapText( (CHAR16*)text, (popupSel->Width - popupSel->LabelMargin ), &tmpHeight );

			if(tmpHeight == 1)
				DrawStringWithAttribute( popupSel->Left + popupSel->LabelMargin  , popupSel->Top, (CHAR16*)text, 
				(UINT8)( (popupSel->ControlFocus) ? popupSel->SelBGColor  | popupSel->SelFGColor : popupSel->BGColor  | ColorNSel   ));
			else
				DrawMultiLineStringWithAttribute( (UINTN)popupSel->Left + (UINTN)popupSel->LabelMargin, (UINTN) popupSel->Top,
												(UINTN)(popupSel->Width - popupSel->LabelMargin ),(UINTN)&tmpHeight/*popupSel->Height*/, (CHAR16*)text,
												(UINT8)( (popupSel->ControlFocus)? popupSel->SelBGColor  | popupSel->SelFGColor : 
												popupSel->BGColor  | ColorNSel   ));
			
			MemFreePointer( (VOID **)&text1 );

        }
		else
		{

    		if(!text1)
    			text1 = EfiLibAllocateZeroPool(2);
    
    		//MemSet( text, sizeof(text), 0 );
    		Len = TestPrintLength( text1 ) / (NG_SIZE);
    		// XXX: may be broken for wide character languages !!!
    		if ( Len /*StringDisplayLen( text1 )*/ > /*19*/(UINTN)(popupSel->Width + popupSel->Left - popupSel->LabelMargin -4)/*gControlRightAreaWidth*/ ) //EIP 79949 : Adjusted the cordinates to show maximum string in control left area
    		EfiStrCpy(&text1[HiiFindStrPrintBoundary(text1 ,(UINTN)(popupSel->Width + popupSel->Left - popupSel->LabelMargin /*gControlRightAreaWidth*/-7/*16*/))],L"..." );        
    
    
            text = EfiLibAllocateZeroPool( (Len+3)*2 ); 
    		SPrint( text,(UINTN)( (Len+3)*2 )/*(popupSel->Width - popupSel->Left - popupSel->LabelMargin +2)*/, L"[%s]", text1 );
    		MemFreePointer( (VOID **)&text1 );
    		DrawStringWithAttribute( popupSel->Left + popupSel->LabelMargin  , popupSel->Top, (CHAR16*)text, 
    				(UINT8)( (popupSel->ControlFocus) ? 
    						 popupSel->SelBGColor  | popupSel->SelFGColor : 
    						  popupSel->BGColor  | ColorNSel   ));

        }
		
		if((TempHeight > 0) && OneofMultilineDisable(popupSel))
		{
			 popupSel->Height = TempHeight;
		}
  		i=TestPrintLength(text) / (NG_SIZE);
        MemFreePointer( (VOID **)&text );
		/*EfiStrCpy(text, L"]");
		DrawStringWithAttribute( popupSel->Left + popupSel->LabelMargin +i +1, popupSel->Top, (CHAR16*)text, 
				(UINT8)( (popupSel->ControlFocus) ? 
						 popupSel->SelBGColor  | popupSel->SelFGColor : 
						  popupSel->BGColor  | ColorNSel ));
*/
        // erase extra spaces if neccessary
		for(;(UINT16)(popupSel->Left + popupSel->LabelMargin + i) <= (popupSel->Width-1);i++)
			DrawStringWithAttribute( popupSel->Left + popupSel->LabelMargin +i, popupSel->Top, L" ", 
						 popupSel->BGColor  |  ColorNSel );

		FlushLines( popupSel->Top, popupSel->Top+popupSel->Height );
	}

	return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelSetCallback
//
// Description:	Function to handle the PopupString actions
//
// Input:		POPUPSEL_DATA *popupSel, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie 
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelSetCallback( POPUPSEL_DATA *popupSel, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( popupSel, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoBootDelBootOption
//
// Description:	Function to delete the boot option
//
// Input:		POPUPSEL_DATA *
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DoBootDelBootOption (POPUPSEL_DATA *popupSel)
{
    if( popupSel->ControlData.ControlVariable == VARIABLE_ID_DEL_BOOT_OPTION )
    {
        //delete selected option
        BootDelBootOption( (UINT16) popupSel->PtrTokens[popupSel->Sel].Value );

        //Complete redraw
        gApp->CompleteRedraw = TRUE;

        //Variable should not be set so return
        return 1;
    }
	return 0;
}

//EIP70421 & 70422  Support for driver order
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoDriverDelDriverOption
//
// Description:	Function to delete the driver option
//
// Input:		POPUPSEL_DATA *
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DoDriverDelDriverOption(POPUPSEL_DATA * popupSel)
{
    if (VARIABLE_ID_DEL_DRIVER_OPTION == popupSel->ControlData.ControlVariable)
    {
        //delete selected option
       	DriverDelDriverOption ((UINT16) popupSel->PtrTokens[popupSel->Sel].Value);

        //Complete redraw
        gApp->CompleteRedraw = TRUE;

        //Variable should not be set so return
        return 1;
    }
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoPopupSelCallBack
//
// Description:	Callback function of the PopupSel
//
// Input:	POPUPSEL_DATA *popupSel
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DoPopupSelCallBack(POPUPSEL_DATA **popupSel)
{
//#if SETUP_SUPPORT_ADD_BOOT_OPTION
	if( TseDoBootDelBootOption(*popupSel) )
		return;
//#endif

	if( TseDoDriverDelDriverOption(*popupSel) )			//EIP70421 & 70422  Support for driver order
		return;

    if ( (*popupSel)->Cookie != NULL )
	{
        VOID *ifrData = (VOID *)(*popupSel)->ControlData.ControlPtr;
		CALLBACK_VARIABLE *callbackData = (CALLBACK_VARIABLE *)(*popupSel)->Cookie;

		callbackData->Variable = (*popupSel)->ControlData.ControlVariable;
		callbackData->Offset = UefiGetQuestionOffset(ifrData);
		callbackData->Length = UefiGetWidth(ifrData);
		callbackData->Data = (VOID*)&((*popupSel)->PtrTokens[(*popupSel)->Sel].Value);
	}
	// To support UEFI 2.1.C spec to Not to update the control when Callback fails.
	UefiPreControlUpdate(&((*popupSel)->ControlData));
	(*popupSel)->Callback( (*popupSel)->Container, (*popupSel), (*popupSel)->Cookie );

    if((*popupSel)->bInteractive)
    {   
        EFI_STATUS Status;
		VOID * Handle=(*popupSel)->ControlData.ControlHandle;
		UINT16 Key = (*popupSel)->CallBackKey;
		CONTROL_DATA *Control;

		Status = CallFormCallBack(&((*popupSel)->ControlData),(*popupSel)->CallBackKey,0, AMI_CALLBACK_CONTROL_UPDATE);//EIP-53480: Updated the action to AMI_CALLBACK_CONTROL_UPDATE
		Control = GetUpdatedControlData((CONTROL_DATA*)(*popupSel),(*popupSel)->ControlData.ControlType,Handle,Key);

	
		if(Control == NULL){ // Control deleted ?
			*popupSel = NULL;
             return;
        }
		if(Control != (CONTROL_DATA*)(*popupSel))
			*popupSel = (POPUPSEL_DATA*)Control; //control Updated
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupSelHandleActionKey
//
// Description:	function to handle the PopupSel Action keys
//
// Input:	POPUPSEL_DATA *popupSel, AMI_EFI_KEY_DATA key
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _PopupSelHandleActionKeyMouse(POPUPSEL_DATA *popupSel, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
    CONTROL_ACTION Action=ControlActionUnknown;
	AMI_EFI_KEY_DATA key=Data->Input.Data.AmiKey;

	if(Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		//EIP-123727 check whether MouseTop is within the Height and Width of PopupSel or not
		if((Data->Input.Data.MouseInfo.Top >= (UINT32)popupSel->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(popupSel->Top+popupSel->Height)) &&
		   (Data->Input.Data.MouseInfo.Left >= (UINT32)popupSel->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(popupSel->Left+popupSel->Width))
		)
		{
			Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);
		}
			
	}

	if(Data->Input.Type == ACTION_TYPE_KEY)
 	   Action = MapControlKeysHook(key);

    switch(Action)
    {
        case ControlActionDecreament:
			//Handle special case for boot order & Legacy dev order
			if (
				(VARIABLE_ID_BOOT_ORDER == popupSel->ControlData.ControlVariable) ||
				(VARIABLE_ID_BBS_ORDER == popupSel->ControlData.ControlVariable) ||
				(VARIABLE_ID_DRIVER_ORDER == popupSel->ControlData.ControlVariable)			//EIP70421 & 70422  Support for driver order
				)
			{
				RearrangeBootDriverOrderVariable (popupSel, FALSE);
			}
            else if( ( CheckForAddDelBootOption() ) && 
					 (popupSel->ControlData.ControlVariable == VARIABLE_ID_DEL_BOOT_OPTION ) )
            {
            }
			else
			{
				if ( popupSel->Sel > 0 )
					popupSel->Sel--;
				else
					popupSel->Sel = popupSel->ItemCount - 1;
				DoPopupSelCallBack(&popupSel);
                if(popupSel == NULL)
                    return EFI_SUCCESS;
			}
			Status = EFI_SUCCESS;
        break;

        case ControlActionIncreament:
			//Handle special case for boot order & Legacy dev order
			if (
				(VARIABLE_ID_BOOT_ORDER == popupSel->ControlData.ControlVariable) ||
				(VARIABLE_ID_BBS_ORDER == popupSel->ControlData.ControlVariable) ||
				(VARIABLE_ID_DRIVER_ORDER == popupSel->ControlData.ControlVariable)			//EIP70421 & 70422  Support for driver order
				)
			{
				RearrangeBootDriverOrderVariable (popupSel, TRUE);
			}
            else if( ( CheckForAddDelBootOption() ) && 
					 (popupSel->ControlData.ControlVariable == VARIABLE_ID_DEL_BOOT_OPTION ) )
            {
            }
			else
			{
				if ( popupSel->Sel < (UINTN)(popupSel->ItemCount - 1) )
					popupSel->Sel++;
				else
					popupSel->Sel = 0;
				DoPopupSelCallBack(&popupSel);
                if(popupSel == NULL)
                    return EFI_SUCCESS;
			}
			Status = EFI_SUCCESS;
        break;

        case ControlActionSelect:
			if ( gListBox.Create( &(popupSel->ListBoxCtrl) ) == EFI_SUCCESS )
			{
				popupSel->ControlActive = TRUE;
				gListBox.Initialize( popupSel->ListBoxCtrl, &(popupSel->ControlData) );
				if(TseLiteIsSpecialOptionList((CONTROL_DATA *)popupSel) == TRUE)
				{
					UINT16 TempLength=0, i;
					//Need fix the ListBox options
					for( i = 0 ; i < popupSel->ItemCount; i++ )
					{
						popupSel->ListBoxCtrl->PtrTokens[i] = popupSel->PtrTokens[i].Option;
						TempLength = (UINT16)HiiMyGetStringLength( popupSel->ListBoxCtrl->ListHandle, popupSel->ListBoxCtrl->PtrTokens[i] );
						TempLength+=5; // to included barders
						if ( TempLength > popupSel->ListBoxCtrl->Width )
							popupSel->ListBoxCtrl->Width = TempLength;
					}

				}
		
				if(popupSel->ListBoxCtrl->Width > (UINT16)(gMaxCols-5))
					popupSel->ListBoxCtrl->Width = (UINT16)(gMaxCols-5);
				popupSel->ListBoxCtrl->Sel = popupSel->Sel;
				gListBox.SetCallback(popupSel->ListBoxCtrl, popupSel,  _PopupSelCallback, NULL);
				
				MouseStop();

				gListBox.Draw( popupSel->ListBoxCtrl );

				MouseRefresh();
			} 
			Status = EFI_SUCCESS; 
        break;

        default:
        break;
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelHandleAction
//
// Description:	function to handle the PopupSel Actions
//
// Input:	POPUPSEL_DATA *popupSel, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelHandleAction( POPUPSEL_DATA *popupSel, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT8 u8ChkResult;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		// List box is active don't refresh
		if ( popupSel->ListBoxCtrl != NULL )
			return Status;

		if (popupSel->Interval == 0)
			return Status;

		if(IsActiveControlPresent(gApp->PageList[gApp->CurrentPage]))
			return Status;
		
		if ( --(popupSel->Interval) == 0 )
		{
			// initialize the interval
			popupSel->Interval = (UINT8)(popupSel->ControlData.ControlFlags.ControlRefresh);
			return UefiRefershQuestionValueNvRAM(&(popupSel->ControlData));
		}
		else
			return Status;
	}

    u8ChkResult = CheckControlCondition( &popupSel->ControlData );
	 
    //Not to perform action for control when token TSE_SETUP_GRAYOUT_SELECTABLE is enable to set focus for GrayoutIf control
    if ( IsGrayoutSelectable() && (COND_GRAYOUT == u8ChkResult) ) {
        return EFI_UNSUPPORTED;
    }

    if(popupSel->ControlData.ControlFlags.ControlReadOnly)
		return EFI_UNSUPPORTED;

	if(!popupSel->ControlFocus)
		return Status;

    if ( popupSel->ListBoxCtrl != NULL )
    {
    	Status = gListBox.HandleAction(popupSel->ListBoxCtrl,Data);
    	if ( popupSel->ListBoxEnd )
    	{
            if(bSelectionChanged)
            {
                if(popupSel->Sel != popupSel->ListBoxCtrl->Sel)
                {
                    popupSel->Sel = popupSel->ListBoxCtrl->Sel;
           			DoPopupSelCallBack(&popupSel);
                    if(popupSel == NULL)
                        return EFI_SUCCESS;

                }
                bSelectionChanged = FALSE;
            }
    
    		gListBox.Destroy(popupSel->ListBoxCtrl,TRUE);
    		popupSel->ListBoxCtrl = NULL;
    		popupSel->ListBoxEnd = FALSE;
    		popupSel->ControlActive = FALSE;
    	}
    }
    else
    {
        if((Data->Input.Type == ACTION_TYPE_KEY) || (Data->Input.Type == ACTION_TYPE_MOUSE))
        {
            return _PopupSelHandleActionKeyMouse(popupSel, Data);
		}
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelSetFocus
//
// Description:	Function to set focus
//
// Input:		POPUPSEL_DATA *popupSel, BOOLEAN focus
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelSetFocus(POPUPSEL_DATA *popupSel, BOOLEAN focus)
{
	UINT8 u8ChkResult;
	
	if(focus != FALSE)
	{
		u8ChkResult = CheckControlCondition( &popupSel->ControlData );
        
		//Setting focus to control which has no condtion and token TSE_SETUP_GRAYOUT_SELECTABLE is enable to make GrayoutIf control to focus and selectable
		if (	((u8ChkResult != COND_NONE) && (u8ChkResult != COND_GRAYOUT)) ||
				(!IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT))
			){
			return EFI_UNSUPPORTED;
		}
	}

	if( !(popupSel->ControlFocus && focus) )
		popupSel->ControlFocus = focus;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelSetPosition
//
// Description:	Function to set position.
//
// Input:		POPUPSEL_DATA *popupSel, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelSetPosition(POPUPSEL_DATA *popupSel, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( popupSel, Left, Top );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		POPUPSEL_DATA *popupSel, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelSetDimensions(POPUPSEL_DATA *popupSel, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( popupSel, Width, Height );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		POPUPSEL_DATA *popupSel, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelSetAttributes(POPUPSEL_DATA *popupSel, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( popupSel, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupSelCallback
//
// Description:	PopupSel callback function.
//
// Input:		POPUPSEL_DATA *container, CONTROL_DATA *popupSel, VOID *cookie
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _PopupSelCallback( POPUPSEL_DATA *container, CONTROL_DATA *popupSel, VOID *cookie )
{
	container->ListBoxEnd = TRUE;
	if ( cookie != NULL )
    {
        bSelectionChanged = TRUE;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelHandleAction
//
// Description:	function to handle the PopupSel set and get operations
//
// Input:	POPUPSEL_DATA *popupSel
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _PopupSelGetSelection( POPUPSEL_DATA *popupSel )
{
	VOID *temp;
	VOID *ifrData = popupSel->ControlData.ControlPtr;
	int i=0;
	EFI_STATUS Status = EFI_SUCCESS;
	
	popupSel->Sel = 0;
	temp = EfiLibAllocateZeroPool( 8 * 2 );
	if ( temp == NULL )
		return;

	if ( VarGetValue( popupSel->ControlData.ControlVariable, UefiGetQuestionOffset(ifrData), UefiGetWidth(ifrData), temp ) == EFI_SUCCESS )
	{
		while( i< popupSel->ItemCount)
		{
			if(popupSel->PtrTokens[i].Value == *(UINT64 *)temp)
			{
				popupSel->Sel = (UINT16)i;
		        break;
			}
			i++;
		}
		if( i == popupSel->ItemCount)
		{
			//EIP92783 Boot order and driver order are special controls, so TSE is forming the one of with the current boot/driver options.
			//So no need of checking error case.
			if ( (VARIABLE_ID_BOOT_ORDER == popupSel->ControlData.ControlVariable) || (VARIABLE_ID_DRIVER_ORDER == popupSel->ControlData.ControlVariable) )
			{												
				popupSel->Sel = 0;
			}
			else
			{
			// The data does not correspond to the available selections
				if(popupSel->ControlData.ControlDataWidth != 0)					//Uncommented for EIP81603 One-of forced to new value but new value not passed to RouteConfig
				{
					//Try to set selection to the default option
					 VarGetDefaults( popupSel->ControlData.ControlVariable, 
											   UefiGetQuestionOffset(popupSel->ControlData.ControlPtr),
											   popupSel->ControlData.ControlDataWidth, temp );
	
					 i=0;
	     			while( i< popupSel->ItemCount)
					{
	               if(popupSel->PtrTokens[i].Value == *(UINT16 *)temp)
						{
	                  popupSel->Sel = (UINT16)i;
							Status = VarSetValue( popupSel->ControlData.ControlVariable, 
										UefiGetQuestionOffset(popupSel->ControlData.ControlPtr),
							     		(UefiGetWidth(popupSel->ControlData.ControlPtr) > sizeof(UINT16) )?sizeof(UINT16):UefiGetWidth(popupSel->ControlData.ControlPtr),
										temp );
							break;
						}
						i++;
					}
				}
				if( (i == popupSel->ItemCount) || (EFI_ERROR(Status)) )
				{
					//Try to set selection to the option with smallest value
					UINT16 TempoptIndex = 0; //holds index of option with smalleset value
					i = 0;
					while (i< popupSel->ItemCount)			//Trying for least option
					{
						if (popupSel->PtrTokens [i].Value < popupSel->PtrTokens [TempoptIndex].Value)
						{
							TempoptIndex = (UINT16)i;
						}
						i++;
					}
					popupSel->Sel = (UINT16)TempoptIndex; // if nothing else works, revert to the option with smallest value
					Status = VarSetValue (popupSel->ControlData.ControlVariable, 
						UefiGetQuestionOffset (popupSel->ControlData.ControlPtr),
						(UefiGetWidth (popupSel->ControlData.ControlPtr) > sizeof (UINT16)) ? sizeof (UINT16) : UefiGetWidth (popupSel->ControlData.ControlPtr),
						&(popupSel->PtrTokens[TempoptIndex].Value) );
				}
				// either case (found default, reverted to first value)we have changed the variable so notify application
			}
		}
	}
	MemFreePointer( (VOID **)&temp );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RearrangeBootDriverOrderVariable
//
// Description:	Function to rearrange the boot/driver order variables
//
// Input:	POPUPSEL_DATA *popupSel, UINT8 bIncrease
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RearrangeBootDriverOrderVariable (POPUPSEL_DATA *popupSel, UINT8 bIncrease)
{
    UINTN optionNumber,size;
    UINT16 newOption, *optionList = NULL;
    VOID *ifrData = popupSel->ControlData.ControlPtr;
    FRAME_DATA *MainFrame = NULL ;
	UINTN OptionCount = 0;

    MainFrame = gApp->PageList[gApp->CurrentPage]->FrameList[StyleFrameIndexOf(MAIN_FRAME)];
    //Find newOption
    if (
		(VARIABLE_ID_BOOT_ORDER == popupSel->ControlData.ControlVariable) ||
		(VARIABLE_ID_DRIVER_ORDER == popupSel->ControlData.ControlVariable)		//EIP70421 & 70422  Support for driver order
		 )
    {
		(VARIABLE_ID_BOOT_ORDER == popupSel->ControlData.ControlVariable) ? (OptionCount = gBootOptionCount) : (OptionCount = gDriverOptionCount);
        optionNumber = UefiGetQuestionOffset (ifrData) / sizeof(UINT16);
        size = 0;
        optionList = (UINT16 *)VarGetVariable (popupSel->ControlData.ControlVariable, &size);
		//EIP-75352 Suppress the warnings from static code analyzer
        if (NULL == optionList){
            return;
        }

        if(optionList[optionNumber] == DISABLED_BOOT_OPTION)
            newOption = DISABLED_BOOT_OPTION;
        else
        {
            if(bIncrease)
            {
                if(0 == optionNumber)
                {
                    //MAY CHANGE: cant increase priority further
                    newOption = optionList [optionNumber];
                }
                else
                {
                    newOption = optionList [optionNumber - 1];
                    //EIP:50878
                    if (IsUpdateBootOrderCursor ())
                        _FrameScroll (MainFrame, TRUE);
                }
            }
            else
            {
                if ( (optionNumber+1) >= OptionCount )
                {
                    //MAY CHANGE: cant decrease priority further
                    newOption = optionList [optionNumber];
                }
                else if ( DISABLED_BOOT_OPTION == optionList[optionNumber+1] )
                {
                    //MAY CHANGE: cant decrease priority further
                    newOption = optionList [optionNumber];
                }
                else
                {
                    newOption = optionList [optionNumber + 1];
                    //EIP:50878
                    if (IsUpdateBootOrderCursor ())
                        _FrameScroll ( MainFrame, FALSE);
                }
            }
        }

        //Free Optionlist
        MemFreePointer((VOID **) &optionList);
    }
//#if TSE_CSM_SUPPORT
    else if(popupSel->ControlData.ControlVariable == VARIABLE_ID_BBS_ORDER)
    {
		CsmRearrangeBBSOrderVariable(popupSel, bIncrease, &newOption);
    }
//#endif //TSE_CSM_SUPPORT

    //Call callback to the container to record this change in gVariableList(cached copy)
	if ( popupSel->Cookie != NULL )
	{
		CALLBACK_VARIABLE *callbackData = (CALLBACK_VARIABLE *)popupSel->Cookie;

		callbackData->Variable = popupSel->ControlData.ControlVariable;
		callbackData->Offset = UefiGetQuestionOffset(ifrData);
		callbackData->Length = UefiGetWidth(ifrData);
		callbackData->Data = (VOID *)&newOption;
		
		popupSel->Callback( popupSel->Container, popupSel, popupSel->Cookie );
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RearrangeBBSOrderVariable
//
// Description:	Function to reorder the BBS order variable
//
// Input:	POPUPSEL_DATA *popupSel, UINT8 bIncrease,UINT16 *newOption
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RearrangeBBSOrderVariable(POPUPSEL_DATA *popupSel, UINT8 bIncrease,UINT16 *newOption)
{
    UINTN optionNumber,size;
    UINT16 *optionList = NULL;
    VOID *ifrData = popupSel->ControlData.ControlPtr;
    UINT8 *pDevOrder;
    UINT16 count = 0;
    UINTN offset = UefiGetQuestionOffset(ifrData);
    FRAME_DATA *MainFrame = NULL ;
    MainFrame = gApp->PageList[gApp->CurrentPage]->FrameList[StyleFrameIndexOf(MAIN_FRAME)];

    size = 0;
    pDevOrder = VarGetVariable( VARIABLE_ID_BBS_ORDER, &size );

    offset -= (sizeof(UINT32) + sizeof(UINT16));

    count = gCurrLegacyBootData->LegacyDevCount;
    offset -= gCurrLegacyBootData->LegacyEntryOffset;
    optionList = (UINT16 *)(pDevOrder + gCurrLegacyBootData->LegacyEntryOffset + sizeof(UINT32) + sizeof(UINT16));

    optionNumber = offset / sizeof(UINT16);

    if(optionList[optionNumber] == DISABLED_BOOT_OPTION)
        *newOption = DISABLED_BOOT_OPTION;
    else
    {
        if(bIncrease)
        {
            if(0 == optionNumber)
            {
                //MAY CHANGE: cant increase priority further
                *newOption = optionList[optionNumber];
            }
            else
            {
                *newOption = optionList[optionNumber - 1];
                //EIP:50878
                if(IsUpdateBootOrderCursor())
                    _FrameScroll( MainFrame, TRUE);
            }
            
        }
        else
        {
            if( (optionNumber+1) >= count )
            {
                //MAY CHANGE: cant decrease priority further
                *newOption = optionList[optionNumber];
            }
            else if( DISABLED_BOOT_OPTION == optionList[optionNumber+1] )
            {
                //MAY CHANGE: cant decrease priority further
                *newOption = optionList[optionNumber];
            }
            else
            {
                *newOption = optionList[optionNumber + 1];
                //EIP:50878
                if(IsUpdateBootOrderCursor())
                    _FrameScroll( MainFrame, FALSE);
            }
        }
    }
    //Free Order
    MemFreePointer((VOID **) &pDevOrder);
}

//EIP81603 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------------------------------------------------
// Procedure:		_GetPopUpSelectionFromVariable
//
// Description:	Fucntion to return the current selection based on the variable. If not matched with variable value
//						Selection will be 0	
//
// Input:			POPUPSEL_DATA *
//
// Output:			VOID
//
//-----------------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _GetPopUpSelectionFromVariable (POPUPSEL_DATA *popupSel)
{
	VOID *temp;
	VOID *ifrData = popupSel->ControlData.ControlPtr;
	int i = 0;
	
	popupSel->Sel = 0;
	temp = EfiLibAllocateZeroPool (8 * 2);
   if (NULL == temp)
		return;
	
	if (VarGetValue (popupSel->ControlData.ControlVariable, UefiGetQuestionOffset (ifrData), UefiGetWidth (ifrData), temp) == EFI_SUCCESS)
	{
		while (i< popupSel->ItemCount)
		{
			if (popupSel->PtrTokens [i].Value == *(UINT64 *)temp)
			{
				popupSel->Sel = (UINT16)i;
				break;
			}
			i++;
		}
	}
}
//EIP81603 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSelGetControlHeight
//
// Description:	function to get the height of the label
//
// Input:	POPUPSEL_DATA *popupSel,Frame, UINT16 *height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSelGetControlHeight(POPUPSEL_DATA *popupSel,VOID * frame, UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *text=NULL, *text1=NULL, *newtext=NULL ;
		UINT16 Width ;
		UINT16 tmpHeight=0;
		UINTN Len=0;
	
		UINT16 Index = 0;
		UINT16 *OptionList=NULL;
		UINT64 *ValueList=NULL;
		EFI_STATUS Status = EFI_UNSUPPORTED;
	
		
	    if(TseLiteIsSpecialOptionList((CONTROL_DATA *)popupSel) != TRUE)
		{
			Status = UefiGetOneOfOptions(&popupSel->ControlData,&popupSel->PopupSelHandle,
					&OptionList, &ValueList, &popupSel->ItemCount,NULL,NULL);
			if (EFI_ERROR(Status))
				return Status;
			for( Index = 0; Index < popupSel->ItemCount; Index++ )
			{
				popupSel->PtrTokens[Index].Option = OptionList[Index];
				popupSel->PtrTokens[Index].Value = ValueList[Index];
			}
			MemFreePointer( (VOID **)&(OptionList));
			MemFreePointer( (VOID **)&(ValueList));
		}

		Width = (UINT16)(popupSel->LabelMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gLabelLeftMargin));
	
		*height = 1 ;

//        _PopupSelGetSelection( popupSel );					//EIP81603 One-of forced to new value but new value not passed to RouteConfig
		_GetPopUpSelectionFromVariable (popupSel);			//In _PopupSelGetSelection fnc, boot manager variable behaving wrongly so introduced _GetPopUpSelectionFromVariable fnc 
																			//to read simply value from variable and set the option and not setting any value to variable
	
		text1 = HiiGetString( popupSel->PopupSelHandle, popupSel->PtrTokens[popupSel->Sel].Option);
	
		//EIP 68920: Check for invalid string token    
	    if (text1 != NULL)
	    {
	        //Len = TestPrintLength( text1 ) / (NG_SIZE);
			Len = (3 + (TestPrintLength( text1 ) / (NG_SIZE))) * sizeof(CHAR16);
			
		    text = EfiLibAllocateZeroPool(Len); 
			newtext = EfiLibAllocateZeroPool(Len);

			if ( text == NULL || newtext == NULL)
		    	return EFI_OUT_OF_RESOURCES;

			MemCpy(newtext, text1, Len);	
			
			SPrint( text,(UINTN)( Len ), L"[%s]", newtext );
		    
			MemFreePointer( (VOID **)&text1 );
			MemFreePointer( (VOID **)&newtext );		
	
		    text1 = StringWrapText( (CHAR16*)text, (UINT16)(((FRAME_DATA *)frame)->FrameData.Width - gLabelLeftMargin - 2 - popupSel->LabelMargin), &tmpHeight );
		    MemFreePointer( (VOID **)&text1 );	
				
		    *height = tmpHeight;
	
		    MemFreePointer( (VOID **)&text );
	    }
	    
	    text = HiiGetString( popupSel->ControlData.ControlHandle, popupSel->Title ) ;
	
	    if(text == NULL)
	        return EFI_OUT_OF_RESOURCES;
	    
		text1 = StringWrapText(text, Width, &tmpHeight );
		
		if ((tmpHeight >= 1) && ( OneofMultilineDisable(popupSel)))
		{
			*height = tmpHeight;
		}
		else if(tmpHeight > *height)
			*height = tmpHeight;
	
		(*height) = (*height) ? (*height):1;
		    
		MemFreePointer( (VOID **)&text );
	    MemFreePointer( (VOID **)&text1 );
	}
	
	else
	{
		*height = 1;
	}
	return EFI_SUCCESS;
}
BOOLEAN TseSuppressOneofMultilineSupport(VOID);
BOOLEAN OneofMultilineDisable(POPUPSEL_DATA *popupSel)
{
	if((UefiIsOneOfControl(popupSel->ControlData.ControlPtr))&&(TseSuppressOneofMultilineSupport()))
	{
		return TRUE;
	}	
	
	return FALSE;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
