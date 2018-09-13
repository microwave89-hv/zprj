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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ResetButton.c $
//
// $Author: Arunsb $
//
// $Revision: 5 $
//
// $Date: 10/18/12 6:03a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ResetButton.c $
// 
// 5     10/18/12 6:03a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     11/21/11 11:06a Premkumara
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
// 3     11/14/11 6:55p Blaines
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
// 2     5/18/11 11:58a Madhans
// To Avoid Build issue when Multiline support is enabled.
// 
// 1     3/28/11 4:02p Rajashakerg
// Added to support reset opcode.
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		ResetButton.c
//
// Description:	This file contains code to handle the uefi actions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "Minisetup.h"

RESET_BUTTON_METHODS gResetButton =
{
	ResetButtonCreate,
	LabelDestroy,
	ResetButtonInitialize,
	ResetButtonDraw,
	ResetButtonHandleAction,
	LabelSetCallback,
	LabelSetFocus,
	LabelSetPosition,
	LabelSetDimensions,
	LabelSetAttributes,
   LabelGetControlHeight
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ResetButtonCreate
//
// Description:	Function to create an ResetButton Control.
//
// Input:	VOID **object
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ResetButtonCreate( VOID **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(RESET_BUTTON_DATA) );

		if ( *object == NULL )
    {
			Status = EFI_OUT_OF_RESOURCES;
      goto DONE;
    }
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		((RESET_BUTTON_DATA*)(*object))->Methods = &gResetButton;

DONE:
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ResetButtonInitialize
//
// Description:	Function to Initialize an Action Control.
//
// Input:	VOID *object, VOID *data
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ResetButtonInitialize( VOID *object, VOID *data )
{
  EFI_STATUS Status = EFI_SUCCESS;
  RESET_BUTTON_DATA *ResetButton = (RESET_BUTTON_DATA*) object;

	Status = gControl.Initialize( ResetButton, data );
	if (EFI_ERROR(Status))
  {
    goto DONE;
  }

	// add extra initialization here...
  ResetButton->ControlData.ControlHelp = ResetButton->ControlData.ControlHelp? ResetButton->ControlData.ControlHelp :
                                      UefiGetHelpField(ResetButton->ControlData.ControlPtr);

	SetControlColorsHook(NULL, NULL, NULL, NULL, &(ResetButton->SelBGColor), &(ResetButton->SelFGColor),
			               &(ResetButton->BGColor), &(ResetButton->FGColor), NULL, NULL, NULL, NULL, NULL, NULL, NULL );

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ResetButtonDraw
//
// Description:	Function to draw ResetButton.
//
// Input:	VOID *object
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ResetButtonDraw( VOID *object )
{
  EFI_STATUS Status = EFI_SUCCESS;
  RESET_BUTTON_DATA *ResetButton = (RESET_BUTTON_DATA*) object;

	CHAR16 *text;
  UINT16 token = 0;
	UINT8 ColorLabel = ResetButton->FGColor;

  // check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( ResetButton->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &ResetButton->ControlData ) )
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

  token = UefiGetPromptField(ResetButton->ControlData.ControlPtr);
	text = HiiGetString( ResetButton->ControlData.ControlHandle, token);

	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(ResetButton->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( ResetButton->Left , ResetButton->Top,
				(UINTN)(ResetButton->Width),(UINTN) ResetButton->Height,
				text,(UINT8)( (ResetButton->ControlFocus) ?
					 ResetButton->SelBGColor  | ResetButton->SelFGColor :
					 ResetButton->BGColor | ColorLabel ));


	}
	else
	{
		// use frame width minus margins as available space
		// boundary overflow  check
		if ( (TestPrintLength( text) / (NG_SIZE)) > (UINTN)(ResetButton->Width))
				text[HiiFindStrPrintBoundary(text,(UINTN)(ResetButton->Width))] = L'\0';

		DrawStringWithAttribute( ResetButton->Left  , ResetButton->Top, text,
				(UINT8)( (ResetButton->ControlFocus) ?
						 ResetButton->SelBGColor  | ResetButton->SelFGColor :
						 ResetButton->BGColor | ColorLabel /*Action->FGColor*/  ));
	}

	MemFreePointer( (VOID **)&text );
	FlushLines( ResetButton->Top  , ResetButton->Top );

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ResetButtonHandleAction
//
// Description:	Function to handle the ResetButton.
//
// Input:	VOID *object, ACTION_DATA *data
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ResetButtonHandleAction(VOID *object, ACTION_DATA *data)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;
  RESET_BUTTON_DATA *ResetButton = (RESET_BUTTON_DATA*) object;
  CONTROL_ACTION CtrlAction;
  UINT16 DefaultId = 0;

  if (( data->Input.Type == ACTION_TYPE_KEY )|| (data->Input.Type == ACTION_TYPE_MOUSE))
  {
	if( data->Input.Type == ACTION_TYPE_KEY )
    CtrlAction = MapControlKeysHook(data->Input.Data.AmiKey);
	else
	{
		 CtrlAction = MapControlMouseActionHook(&data->Input.Data.MouseInfo);
  	}
	    switch(CtrlAction)
	    {
	    case ControlActionSelect:
	      //call a wapper function to update the Default vaule
			DefaultId = UefiGetResetButtonDefaultid( ResetButton->ControlData.ControlPtr );

			if(0xFFFF == DefaultId)
			    return EFI_UNSUPPORTED;

	      Status = UefiupdateResetButtonDefault(ResetButton->ControlData,DefaultId);
	       break;

	    default:
	      break;
	    }
  }
  return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 2011, American Megatrends, Inc.         	  **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
