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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/SubMenu.c $
//
// $Author: Premkumara $
//
// $Revision: 34 $
//
// $Date: 8/28/14 2:50p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/SubMenu.c $
// 
// 34    8/28/14 2:50p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 33    8/28/14 11:52a Premkumara
// [TAG] 			EIP174031
// [Category] 		Improvement
// [Description] 	Removed TODO comments and added proper comments in those
// places
// [Files] 			commonoem.c, commonhelper.c, special.c, submenu.c,
// minisetupext.c, uefi21wapper.c and legacy.c
// 
// 32    5/02/14 9:31p Arunsb
// EIP141986 changes reverted.
// 
// 31    5/02/14 10:50a Premkumara
// [TAG]  		EIP141986
// [Category]  	New Feature
// [Description]  	Made Grayed controls to focus-able when token
// TSE_SETUP_GRAYOUT_SELECTABLE
//  is enabled and can't edit the values
// [Files]  		AMITSE.sdl,CommonHelper.c,frame.c,Label.c,minisetupext.h,
// numeric.c,PopupPassword.c,PopupSel.c,PopupString.c,SubMenu.c
// 
// 30    5/01/14 3:46p Premkumara
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
// 29    2/11/14 8:33p Arunsb
// [TAG]	EIP146858
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	When both MINISETUP_MOUSE_SUPPORT and TSE_MULTILINE_CONTROLS
// are enabled, only the first line of wrapped controls are clickable
// [Root Cause]	The function SubMenuHandleAction doesn't consider the
// control’s height when checking mouse select actions.
// [Solution]	The function SubMenuHandleAction includes the controls
// height when checking mouse select actions
// [Files]	SubMenu.c
// 
// 28    12/03/13 1:14p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 27    3/12/13 12:28p Rajashakerg
// [TAG]  		EIP105167 
// [Category]  	Improvement
// [Description]  	Making the specify setup items departing from F2/F3
// effect.
// [Files]  		AMITSE.sdl, CommonHelper.c, callback.c, minisetupext.h,
// PopupPassword.c, SubMenu.c, HiiCallback.c
// 
// 26    3/08/13 1:35a Rajashakerg
// [TAG]  		EIP113085
// [Category]  	Improvement
// [Description]  	 Modify callback function behavior to match UEFI SPEC.
// [Files]  		HiiCallback.c, PopupPassword.c, SubMenu.c
// 
// 25    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 13    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 23    9/17/12 6:20a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 21    9/06/12 2:18a Rajashakerg
// [TAG]  		EIP97333 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Update TSE to V1227, there is a redundant blank line.
// [RootCause]  	Co-ordinates calculation was not proper for submenu
// control
// [Solution]  	Provided proper co-ordinates for sub menu control.
// [Files]  		SubMenu.c
// 
// 20    4/19/12 6:09p Blaines
// [TAG] - EIP 88031 
// [Category]- Defect
// [Synopsis]- Hii Callbacks may enter infinite loop on
// BROWSER_ACTION_RETRIEVE
// [Solution] - Only allow EFI_BROWSER_ACTION_RETRIEVE action for all
// Interactive controls from MiniSetupEntry.
// [Files] - Submenu.c, HiiCallback.c,
// 
// 19    2/01/12 8:05p Blaines
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
// 18    12/07/11 6:52p Blaines
// [TAG] - EIP 77046 
// [Category]- Sighting
// [Synopsis]- In some SAS cards, UEFI Driver submenu entry text are
// truncated, and do not properly wrap to the next line.
// [Solution] - In the function SubMenuDraw, truncate string when the
// length exceeds submenu->Width 
//  (when submenu->SubMenuType == 2, and submenu->Height == 1 ).
// 
// [Files]
// SubMenu.c
// 
// [Functions Changed]
// - SubMenuDraw
// 
// 
// 17    12/01/11 7:40a Rajashakerg
// [TAG]  		EIP75464 
// [Category]  	Improvement
// [Description]  	Improper handling of action controls
// [Files]  		SubMenu.c, UefiAction.c, HiiCallback.c, Uefi21Wapper.c
// 
// 16    11/28/11 4:58a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 15    11/21/11 11:04a Premkumara
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
// 14    11/21/11 8:58a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupString.c, SubMenu.c, Text.c.
// 
// 13    11/14/11 6:55p Blaines
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
// 12    11/08/11 5:10a Rajashakerg
// Moved the CallFormCallBack() function with retrive action to
// SubMenuInitialize() function as per the specification.
// 
// 11    8/26/11 2:10p Blaines
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
// 10    3/21/11 12:44a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 9     3/09/11 7:23p Madhans
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
// 8     12/02/10 6:08p Madhans
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
// 7     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 7     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 6     2/15/10 10:15p Madhans
// To avoid warnings
// 
// 5     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 4     11/04/09 11:54a Blaines
// EIP-28247
// 
// Fix for grayout color menu string not being grayed out.
// 
//  
// 
// 3     6/23/09 6:53p Blaines
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
// Name:		Submenu.c
//
// Description:	This file contains code to handle submenu operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

SUBMENU_METHODS gSubMenu =
{
	SubMenuCreate,
	SubMenuDestroy,
	SubMenuInitialize,
	SubMenuDraw,
	SubMenuHandleAction,
	SubMenuSetCallback,
	SubMenuSetFocus,
	SubMenuSetPosition,
	SubMenuSetDimensions,
	SubMenuSetAttributes,
    SubMenuGetControlHeight

};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuCreate
//
// Description:	this function uses the create function of control
//					and create submenu.
//
// Input:	SUBMENU_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuCreate( SUBMENU_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(SUBMENU_DATA) );

		if ( *object == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gSubMenu;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys submenu.
//
// Input:	SUBMENU_DATA *submenu, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuDestroy( SUBMENU_DATA *submenu, BOOLEAN freeMem )
{
	if(NULL == submenu)
	  return EFI_SUCCESS;

	gControl.Destroy( submenu, FALSE );

	if ( freeMem )
		MemFreePointer( (VOID **)&submenu );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuDestroy
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
EFI_STATUS SubMenuInitialize( SUBMENU_DATA *submenu, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( submenu, data );
	if (EFI_ERROR(Status))
		return Status;

    if(UefiIsInteractive(&submenu->ControlData))
	{
		// EIP88031 : Invoking CallFormCallBackon with AMI_CALLBACK_RETRIEVE 
        // caused infinite loop on FormCallBack when UIUpdateCallback is called during pack update.
        /*		
        UINT16 Key = UefiGetControlKey(&(submenu->ControlData));
		UefiPreControlUpdate(NULL);//EIP45464 : Updating the gPrevControlValue buffer to NULLL before invoking CallFormCallBack 	
		CallFormCallBack(&(submenu->ControlData),Key,0,AMI_CALLBACK_RETRIEVE);//EIP-53480: Updated the action to AMI_CALLBACK_RETRIEVE
        */
	}

	// add extra initialization here...
	submenu->ControlData.ControlHelp = UefiGetHelpField((VOID *)submenu->ControlData.ControlPtr); //refPtr->Help;
	submenu->ControlFocus = FALSE;
	submenu->Interval = (UINT8)submenu->ControlData.ControlFlags.ControlRefresh;
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
	
	

#if SETUP_STYLE_AWARD
	submenu->SubMenuType = (UINT8)(submenu->ControlData.ControlPageID != 0);
#endif

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuDraw
//
// Description:	function to draw a sub-menu.
//
// Input:	SUBMENU_DATA *submenu
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuDraw( SUBMENU_DATA *submenu )
{
	CHAR16 *text=NULL,*text1;
	UINTN length;
	EFI_STATUS Status = EFI_SUCCESS;
//	UINT8 ColorSubMenu = submenu->NSelFGColor;
	UINT8 ColorLabel = (submenu->ControlFocus) ? submenu->LabelFGColor : submenu->NSelLabelFGColor ;

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
            if (!submenu->ControlFocus)//setting grayoutif color for grayoutif control based on token TSE_SETUP_GRAYOUT_SELECTABLE
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

	SPrint( text, length, L"%c %s", (submenu->SubMenuType == 2)?L' ':GEOMETRICSHAPE_RIGHT_TRIANGLE, text1 );
	MemFreePointer( (VOID **)&text1 );

	if ( submenu->SubMenuType != 1 )
	{
		//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
		if(submenu->Height>1 && IsTSEMultilineControlSupported())
		{
			DrawMultiLineStringWithAttribute( submenu->Left , submenu->Top, 
					(UINTN)(submenu->Width),(UINTN) submenu->Height,
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
						
			
			if(((TestPrintLength( text ) / (NG_SIZE))-2) > (UINTN)(submenu->Width))//EIP 97333 : Check for width corrected since the text already include spaces in it.
				EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)(submenu->Width-2))],L"...");
	
			DrawStringWithAttribute( submenu->Left - 2, submenu->Top, (CHAR16*)text, 
					(UINT8)(  (submenu->ControlFocus) ? 
							  submenu->SelBGColor  | ColorLabel :
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
						(UINT8)(submenu->NSelBGColor | ColorLabel /*ColorSubMenu*/) );

				if ( submenu->ControlFocus )
					DrawStringWithAttribute( submenu->Left + submenu->LabelMargin + 1,
							submenu->Top, text1, (UINT8)(submenu->SelBGColor | submenu->SelFGColor) );
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
// Procedure:	SubMenuHandleAction
//
// Description:	function to handle the submenu actions
//
// Input:	SUBMENU_DATA *submenu, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuHandleAction( SUBMENU_DATA *submenu, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	BOOLEAN Selected = FALSE;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		if (submenu->Interval == 0)
			return Status;

		if ( --(submenu->Interval) == 0 )
		{
			// initialize the interval
			submenu->Interval = (UINT8)(submenu->ControlData.ControlFlags.ControlRefresh);
			return EFI_SUCCESS;
		}
		else
			return Status;
	}

	if ( ! submenu->ControlFocus )
		return Status;

	if (Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		//Status = MouseSubMenuHandleAction( submenu, Data);
		//if ( Data->Input.Data.MouseInfo.ButtonStatus==TSEMOUSE_LEFT_DCLICK )
	    
		if(ControlActionSelect == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
		//check whether MouseTop is within the Height and Width of submenu or not
			if( (Data->Input.Data.MouseInfo.Top >= (UINT32)submenu->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(submenu->Top+submenu->Height)) &&
				(Data->Input.Data.MouseInfo.Left >= (UINT32)submenu->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(submenu->Left+submenu->Width))
			)//EIP-123727
			{
				Selected = TRUE;
			}
	}

	if ( Data->Input.Type == ACTION_TYPE_KEY )
	{
		if ( ControlActionSelect == MapControlKeysHook(Data->Input.Data.AmiKey) )
			Selected = TRUE;
	}
	if(Selected)
	{
		UINT8 u8ChkResult;

		u8ChkResult = CheckControlCondition( &submenu->ControlData );
        
		//Not to perform action for grayoutif-control when token TSE_SETUP_GRAYOUT_SELECTABLE is enable to set focus for GrayoutIf control
		if ( IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT) ) {
		   return EFI_UNSUPPORTED;
		}

		MouseStop();
		
		if ( submenu->Callback )
		{
			if ( submenu->Cookie != NULL )
			{
				CALLBACK_SUBMENU *callbackData = (CALLBACK_SUBMENU *)submenu->Cookie;
				callbackData->DestPage = submenu->ControlData.ControlDestPageID;
			}
			UefiPreControlUpdate(NULL);
			submenu->Callback( submenu->Container, submenu, submenu->Cookie );
		}

		if(UefiIsInteractive(&submenu->ControlData))
		{
			VOID * Handle=submenu->ControlData.ControlHandle;
			UINT16 Key = UefiGetControlKey(&(submenu->ControlData));
			CONTROL_DATA *Control;
		  	
			Status = CallFormCallBack(&(submenu->ControlData),Key,0,AMI_CALLBACK_CONTROL_UPDATE);//EIP-53480: Updated the action to AMI_CALLBACK_CONTROL_UPDATE
			// To support UEFI 2.1.C spec to Not to change page when Callback fails.
			Status = UefiIsProceedWithPageChange(Status);
			if(Status != EFI_SUCCESS)
			{
				if ( submenu->Callback )
				{
					if ( submenu->Cookie != NULL )
					{
						CALLBACK_SUBMENU *callbackData = (CALLBACK_SUBMENU *)submenu->Cookie;
						callbackData->DestPage = submenu->ControlData.ControlPageID;
					}
					submenu->Callback( submenu->Container, submenu, submenu->Cookie );
				}
					// On Error Status Don't Change the Destination page. Skip the user action.
					return EFI_SUCCESS;			
				
			}

			Control = GetUpdatedControlData((CONTROL_DATA*)submenu,CONTROL_TYPE_SUBMENU,Handle,Key);
		
			if(Control == NULL) // Control deleted ?
				return EFI_SUCCESS;
			if(Control != (CONTROL_DATA*)submenu)
				submenu = (SUBMENU_DATA*)Control; //control Updated
		}

		_SubMenuHandleSpecialOp( submenu );

		MouseStart();

		

		Status = EFI_SUCCESS;
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetCallback
//
// Description:	function to handle the submenu actions
//
// Input:		SUBMENU_DATA *submenu, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetCallback( SUBMENU_DATA *submenu, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( submenu, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetFocus
//
// Description:	Function to handle the submenu actions
//
// Input:		SUBMENU_DATA *submenu, BOOLEAN focus
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetFocus(SUBMENU_DATA *submenu, BOOLEAN focus)
{
	UINT8 u8ChkResult;
	
	if(focus != FALSE)
	{
        u8ChkResult = CheckControlCondition( &submenu->ControlData );
        
		//Setting focus to control which has no control-condtion and token TSE_SETUP_GRAYOUT_SELECTABLE is enable to make GrayoutIf control to set focus and selectable
		if (	((u8ChkResult != COND_NONE) && (u8ChkResult != COND_GRAYOUT)) ||
         	(!IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT))
			){
			return EFI_UNSUPPORTED;
		}
	}

	if( !(submenu->ControlFocus && focus) )
		submenu->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetPosition
//
// Description:	Function to set position.
//
// Input:		SUBMENU_DATA *submenu, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetPosition(SUBMENU_DATA *submenu, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( submenu, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		SUBMENU_DATA *submenu, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetDimensions(SUBMENU_DATA *submenu, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( submenu, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		SUBMENU_DATA *submenu, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuSetAttributes(SUBMENU_DATA *submenu, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( submenu, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SubMenuGetControlHeight
//
// Description:	Function to get the label height of the submenu
//
// Input:		SUBMENU_DATA *submenu, Frame Data, UINT16 *height
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SubMenuGetControlHeight(SUBMENU_DATA *submenu, VOID *frame, UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
        UINTN length=0;
	
		Width = ((FRAME_DATA *)frame)->FrameData.Width - (UINT8)gLabelLeftMargin - 2 ;
		text = HiiGetString( submenu->ControlData.ControlHandle, UefiGetPromptField((VOID *)submenu->ControlData.ControlPtr) );
		if ( text == NULL )
			return EFI_OUT_OF_RESOURCES;

        length = (3 + (TestPrintLength( text ) / (NG_SIZE))) * sizeof(CHAR16);
	    newText = EfiLibAllocateZeroPool( length );
	    
        if ( newText == NULL )
		    return EFI_OUT_OF_RESOURCES;

	    SPrint( newText, length, L"%c %s", (submenu->SubMenuType == 2)?L' ':GEOMETRICSHAPE_RIGHT_TRIANGLE, text );
	    MemFreePointer( (VOID **)&text);
	
		text = StringWrapText( newText, Width+2, height );//EIP 97333 : Above we have appeneded the two spaces at begning of sub menu string, so providing proper widht for submenu 
	
	    (*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
		MemFreePointer( (VOID **)&text );
	}
	else
	{
		*height = 1;
	}
	return EFI_SUCCESS;

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
