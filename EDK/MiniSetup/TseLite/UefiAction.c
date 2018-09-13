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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/UefiAction.c $
//
// $Author: Premkumara $
//
// $Revision: 17 $
//
// $Date: 5/01/14 3:46p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/UefiAction.c $
// 
// 17    5/01/14 3:46p Premkumara
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
// 16    4/23/14 2:55a Premkumara
// [TAG]  		EIP153045 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	After selecting UEFI action control either by mouse/key and
// try to exit application, TSE is not prompting "Save and Reset" message
// to reset the system
// [RootCause]  	When RESET_REQUIRED flag is set for text control TSE is
// not setting gResetRequired flag for Interactive Text control(Action
// type control).
// [Solution]  	Setting gResetRequired flag for action type controls when
// action type controls is selected or modified either using mouse/Key.
// [Files]  		UefiAction.c
// 
// 15    2/11/14 8:48p Arunsb
// [TAG]	EIP147140
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	UefiActionHandleAction() doesnt handle mouse clicks
// [Root Cause]	The function UefiActionHandleAction doesnt handle mouse
// actions
// [Solution]	Added mouse action handling support to the function
// UefiActionHandleAction
// [Files]	UefiAction.c
// 
// 14    10/18/12 6:03a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 13    12/01/11 7:42a Rajashakerg
// [TAG]  		EIP75464 
// [Category]  	Improvement
// [Description]  	Improper handling of action controls
// [Files]  		SubMenu.c, UefiAction.c, HiiCallback.c, Uefi21Wapper.c
// 
// 12    11/30/11 12:29a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 11    11/28/11 5:01a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 10    11/21/11 10:47a Premkumara
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
// 9     11/14/11 6:55p Blaines
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
// 8     3/21/11 12:48a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 7     3/09/11 7:23p Madhans
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
// 6     2/01/11 7:34p Madhans
// [TAG] - EIP 50737 
// [Category]- Defect
// [Severity]- Mordarate
// [Symptom] - Suppressing the Interactive control does not work
// correctly.
// [RootCause] - The control conditional pointer if not set correctly.
// [Solution]- To fix the Control condition pointer. And identify the
// suppress if related to UEFI action control
// [Files] - UefiAction.c TseLiteHelper.c hii.h uefi20wapper.c
// uefi21wapper.c
// 
// 5     12/02/10 5:21p Madhans
// [TAG] - EIP 49557  
// [Category]- defect
// [Severity]- Mordarate
// [Symptom]- UEFIAction controls does not work correctly.
// [Rootcause] - Action controls does not Process the QuestionResp
// correctly. 
// [Solution]- Fix done UEFIAction to check for QuestionResp and call the
// callback 
// [Files] - uefiaction.c and uefi21wapper.c
// 
// 4     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:19a Mallikarjunanv
// updated year in copyright message
// 
// 3     6/23/09 6:53p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		UefiAction.c
//
// Description:	This file contains code to handle the uefi actions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "Minisetup.h"

UEFI_ACTION_METHODS gUefiAction =
{
	UefiActionCreate,
	LabelDestroy,
	UefiActionInitialize,
	UefiActionDraw,
	UefiActionHandleAction,
	LabelSetCallback,
	LabelSetFocus,
	LabelSetPosition,
	LabelSetDimensions,
	LabelSetAttributes,
    LabelGetControlHeight
};

EFI_STATUS _ProcessActionCallback(CONTROL_INFO * ControlData, BOOLEAN InteractiveText);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiActionCreate
//
// Description:	Function to create an Action Control.
//
// Input:	VOID **object
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiActionCreate( VOID **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(UEFI_ACTION_DATA) );

		if ( *object == NULL )
    {
			Status = EFI_OUT_OF_RESOURCES;
      goto DONE;
    }
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		((UEFI_ACTION_DATA*)(*object))->Methods = &gUefiAction;

DONE:
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiActionInitialize
//
// Description:	Function to Initialize an Action Control.
//
// Input:	VOID *object, VOID *data
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiActionInitialize( VOID *object, VOID *data )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UEFI_ACTION_DATA *Action = (UEFI_ACTION_DATA*) object;

	Status = gControl.Initialize( Action, data );
	if (EFI_ERROR(Status))
  {
    goto DONE;
  }

	// add extra initialization here...
  Action->Interval = (UINT8)Action->ControlData.ControlFlags.ControlRefresh;
  Action->ControlData.ControlHelp = Action->ControlData.ControlHelp? Action->ControlData.ControlHelp :
                                      UefiGetHelpField(Action->ControlData.ControlPtr);

	SetControlColorsHook(NULL, NULL, NULL, NULL, &(Action->SelBGColor), &(Action->SelFGColor),
			               &(Action->BGColor), &(Action->FGColor), NULL, NULL, NULL, NULL, NULL, NULL, NULL );

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiActionDraw
//
// Description:	Function to draw an Action Control.
//
// Input:	VOID *object
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiActionDraw( VOID *object )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UEFI_ACTION_DATA *Action = (UEFI_ACTION_DATA*) object;

	CHAR16 *text;
  UINT16 token = 0;
	UINT8 ColorLabel = Action->FGColor;

  // check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( Action->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &Action->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorLabel = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				Status = EFI_UNSUPPORTED;
        goto DONE;
				break;
		}
	//}

  token = UefiGetPromptField(Action->ControlData.ControlPtr);
	text = HiiGetString( Action->ControlData.ControlHandle, token);
	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == text){
		text = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
		if(!text)
			return EFI_NOT_FOUND;
		EfiStrCpy(text,L" ");
	}

	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(Action->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( Action->Left , Action->Top, 
				(UINTN)(Action->Width),(UINTN) Action->Height,
				text,(UINT8)( (Action->ControlFocus) ? 
					 Action->SelBGColor  | Action->SelFGColor : 
					 Action->BGColor | ColorLabel ));
	}
	else
	{
		// use frame width minus margins as available space
		// boundary overflow  check
		if ( (TestPrintLength( text) / (NG_SIZE)) > (UINTN)(Action->Width))
				text[HiiFindStrPrintBoundary(text,(UINTN)(Action->Width))] = L'\0';
	
		DrawStringWithAttribute( Action->Left  , Action->Top, text, 
				(UINT8)( (Action->ControlFocus) ? 
						 Action->SelBGColor  | Action->SelFGColor : 
						 Action->BGColor | ColorLabel /*Action->FGColor*/  ));
	}

	MemFreePointer( (VOID **)&text );
	FlushLines( Action->Top  , Action->Top );

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiActionHandleAction
//
// Description:	Function to handle the Label actions.
//
// Input:	VOID *object, ACTION_DATA *data
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiActionHandleAction(VOID *object, ACTION_DATA *data)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;
  UEFI_ACTION_DATA *Action = (UEFI_ACTION_DATA*) object;
  UINT16 Value = 0;
  BOOLEAN Selected = FALSE;
  
  if (data->Input.Type == ACTION_TYPE_MOUSE) //EIP-147140
  {
	if(ControlActionSelect == MapControlMouseActionHook(&data->Input.Data.MouseInfo))
	//EIP-123727 check whether MouseTop is within the Height and Width of Interactive Text Control or not
		if((data->Input.Data.MouseInfo.Top >= (UINT32)Action->Top) && (data->Input.Data.MouseInfo.Top < (UINT32)(Action->Top+Action->Height)) &&
		   (data->Input.Data.MouseInfo.Left >= (UINT32)Action->Left) && (data->Input.Data.MouseInfo.Left < (UINT32)(Action->Left+Action->Width))
		)
		{
			Selected = TRUE;
		}
  }
  
  if ( data->Input.Type == ACTION_TYPE_KEY )
  {
      if ( ControlActionSelect == MapControlKeysHook(data->Input.Data.AmiKey) )
          Selected = TRUE;
  }
	
	if (Selected )
	{
		MouseStop();

		if (Action->ControlData.ControlFlags.ControlReset) //EIP-153045 Showing Save & Reset when Interactive text control is selected and try to exit TSE
			gResetRequired = TRUE;

		//Process UefiAction QuestionConfig
		Status = ProcessActionQuestionConfiguration(&Action->ControlData);

		if(EFI_ERROR(Status))
		{
			//goto DONE;
		}
		//Process UefiAction Callback if any
		Status = _ProcessActionCallback(&Action->ControlData, FALSE);
		return EFI_SUCCESS; //EIP75464 :Status from previous functions are already been handled. So return EFI_SUCCESS
	}
  
  if ( data->Input.Type == ACTION_TYPE_TIMER )
  {
    if(--Action->Interval == 0)
    {
      Action->Interval = (UINT8)Action->ControlData.ControlFlags.ControlRefresh;
      Value = UefiTseLiteGetAmiCallbackIndex(Action->ControlData.ControlConditionalPtr,Action->ControlData.ControlPtr );
      if(Value == INTERACTIVE_TEXT_VALUE)
      {
        //Process UefiAction Callback if any
        Status = _ProcessActionCallback(&Action->ControlData, TRUE);
      }
	  else
		return EFI_SUCCESS; // If it is not Interactive Test just do the Redraw
    }
  }

//DONE:
  return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ProcessActionCallback
//
// Description:	Function process action callbacks
//
// Input:		CONTROL_INFO * ControlData, BOOLEAN InteractiveText
//					
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _ProcessActionCallback(CONTROL_INFO * ControlData, BOOLEAN InteractiveText)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(UefiIsInteractive(ControlData))
  {
    if(InteractiveText)
    {
      Status = SpecialActionCallBack(ControlData, UefiGetControlKey(ControlData));
    }else
    {
	  UefiPreControlUpdate(NULL);	  
      Status = CallFormCallBack(ControlData, UefiGetControlKey(ControlData), FALSE, AMI_CALLBACK_CONTROL_UPDATE);////EIP-53480: Implementation of FormBrowser with actions support 
    }
  }

  return Status;
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
