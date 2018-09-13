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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Text.c $
//
// $Author: Arunsb $
//
// $Revision: 15 $
//
// $Date: 2/11/14 8:34p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Text.c $
// 
// 15    2/11/14 8:34p Arunsb
// [TAG]		EIP147142
// [Category]	Bug Fix
// [Severity]	Normal
// [Symptom]	text gets truncated
// [Root Cause]	The controls SetText function is called from the function
// TextDraw to update the properties [text->Label and text->text] using
// HiiGetString. However, FrameDraw will call each
// controls->getControlHeight before calling each controls->draw function.
// It is during this time when text->getControlHeight attempts to use the
// properties [text->Label and text->text] to compute the height [for
// multiline] which will be incorrect
// [Solution]	Call the controls SetText function from within the function
// getControlHeight 
// to ensure the text controls properties [text->Label and text->text]
// always has valid updated Hii text.
// [Files]	Text.c
// 
// 14    6/10/13 10:02a Arunsb
// String retrieval success check in TextInitialize is commented.
// 
// 13    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 12    2/01/12 5:54p Blaines
// Rollback to Revision 10
// 
// 10    11/21/11 10:59a Premkumara
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
// 9     11/21/11 8:59a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupString.c, SubMenu.c, Text.c.
// 
// 8     11/15/11 2:28a Rajashakerg
// [TAG]  		EIP73391 
// [Category]  	Improvement
// [Description]  	Information displayed in SETUP gets truncated.
// [Files]  		Text.c
// 
// 7     11/14/11 6:55p Blaines
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
// 6     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 7     8/18/10 7:17p Madhans
// [TAG]    	EIP42199
// [Category]	BUG FIX
// [Symptom]	Text Control does not disply the full string even with
// multiline TSE support.
// [RootCause]	Bug in TextGetControlHeight()
// [Solution]	Take the Frame width in account instead if Text->Width.
// [Files]		text.c
// 
// 6     3/26/10 6:53p Madhans
// Support to Map the do the Control Mapping from gTseControlMap Table. So
// no changes need in Frame.c, With this feature gTseControlMap Can be
// customized to add/customize the TSE controls.
// 
// 5     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 4     8/13/09 1:21p Blaines
// EIP #24980 Fix to properly display right area text
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
// Name:		text.c
//
// Description:	This file contains code to handle text operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

TEXT_METHODS gText =
{
	TextCreate,
	TextDestroy,
	TextInitialize,
	TextDraw,
	TextHandleAction,
	TextSetCallback,
	TextSetFocus,
	TextSetPosition,
	TextSetDimensions,
	TextSetAttributes,
    TextGetControlHeight,
	TextSetText
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextCreate
//
// Description:	this function uses the create function of control
//					and creates text
//
// Input:	TEXT_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextCreate( TEXT_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(TEXT_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gText;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys the text
//
// Input:	TEXT_DATA *text, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextDestroy( TEXT_DATA *text, BOOLEAN freeMem )
{
	if(NULL == text)
	  return EFI_SUCCESS;

	gControl.Destroy( text, FALSE );

	MemFreePointer( (VOID **)&text->LabelText );
	MemFreePointer( (VOID **)&text->Text );

	if ( freeMem )
		MemFreePointer( (VOID **)&text );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextDestroy
//
// Description:	this function uses the initialize function of control
//					and initializes the text
//
// Input:	TEXT_DATA *text, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextInitialize( TEXT_DATA *text, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( text, data );
	if (EFI_ERROR(Status))
		return Status;

	SetControlColorsHook(&(text->BGColor), &(text->FGColor), 
						NULL, NULL, 
						NULL, NULL,
	                    			NULL, NULL,
						NULL, NULL,
						NULL, 
						NULL, NULL,
						NULL,NULL);

	// add extra initialization here...
	text->ControlData.ControlHelp = UefiGetHelpField ((VOID*)text->ControlData.ControlPtr);
	//text->FGColor= EFI_DARKGRAY;
	StyleGetSpecialColor( CONTROL_TYPE_TEXT, &(text->FGColor)) ;

	text->LabelMargin = (UINT8)gControlLeftMargin;


	text->Interval = (UINT8)text->ControlData.ControlFlags.ControlRefresh;
	text->LabelText = HiiGetString( text->ControlData.ControlHandle, UefiGetTextField((VOID*)text->ControlData.ControlPtr));
//	if ( text->LabelText == NULL )						//EIP122907 In some case in init hiigetstring is failing but in draw its passing so commented this check.
//		return EFI_OUT_OF_RESOURCES;

	text->Text = HiiGetString( text->ControlData.ControlHandle, UefiGetTextTwoField((VOID *)text->ControlData.ControlPtr));
//	if ( text->Text == NULL )
//		return EFI_OUT_OF_RESOURCES;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextDraw
//
// Description:	function to draw the text with attributes.
//
// Input:	TEXT_DATA *text
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextDraw( TEXT_DATA *text )
{
	CHAR16 *txt =NULL, *txt2 = NULL;
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 ColorText = text->FGColor ;


	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( text->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &text->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorText = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	txt = HiiGetString( text->ControlData.ControlHandle, UefiGetTextField((VOID*)text->ControlData.ControlPtr));
	if ( txt == NULL )
		return EFI_OUT_OF_RESOURCES;

 	txt2 = HiiGetString( text->ControlData.ControlHandle, UefiGetTextTwoField((VOID*)text->ControlData.ControlPtr));
	if ( txt2 == NULL )
		return EFI_OUT_OF_RESOURCES;

	gText.SetText(text,txt,txt2);
	MemFreePointer ((VOID **)&txt);
	MemFreePointer ((VOID **)&txt2);

	if ( text->LabelText == NULL )
	{ 
		Status = EFI_UNSUPPORTED;
		return Status;
	}

		// labeltext boundary overflow  check	
	if(text->Height>1 && IsTSEMultilineControlSupported())//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	{
		DrawMultiLineStringWithAttribute( (UINTN)text->Left, (UINTN) text->Top, 
					(UINTN)(text->LabelMargin - text->Left),(UINTN)text->Height,
					text->LabelText, text->BGColor |ColorText );
	}
	else
	{
		if ( (TestPrintLength( text->LabelText ) / (NG_SIZE)) > (UINTN)(text->LabelMargin - text->Left  )/*21*/ )
				text->LabelText[HiiFindStrPrintBoundary(text->LabelText ,(UINTN)(text->LabelMargin - text->Left  ))] = L'\0';
	
		DrawStringWithAttribute( text->Left , text->Top, text->LabelText, text->BGColor |  ColorText /*text->FGColor*/  );
	}

	if ( text->Text != NULL )
	{
		//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
		if(text->Height>1 && IsTSEMultilineControlSupported())
		{
				DrawMultiLineStringWithAttribute( (UINTN)text->Left + text->LabelMargin, (UINTN) text->Top, 
						(UINTN)((text->Width + text->Left)  - text->LabelMargin -2),(UINTN)text->Height,
						text->Text, text->BGColor |ColorText );//EIP 73391 : Adjusted the cordinates to show maximum string in control left area

						
		}
		else
		{
			// text boundary overflow check
			//EIP 73391 : Adjusted the cordinates to show maximum string in control left area
	        if ( (TestPrintLength( text->Text ) / (NG_SIZE)) >= (UINTN)((text->Width + text->Left) - text->LabelMargin -2) )
	            text->Text[HiiFindStrPrintBoundary(text->Text ,(UINTN)((text->Width + text->Left) - text->LabelMargin -2))] = L'\0';
	        DrawStringWithAttribute( text->Left + text->LabelMargin , text->Top, text->Text, text->BGColor |ColorText );
		}
	}

	//EIP-72610 if TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		FlushLines(text->Top, text->Top + text->Height - 1);
	}
	else
	{
		FlushLines(text->Top, text->Top);
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextHandleAction
//
// Description:	function to handle the text actions
//
// Input:	TEXT_DATA *text, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextHandleAction( TEXT_DATA *text, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if ( (Data->Input.Type == ACTION_TYPE_TIMER) && ((UINT8)text->ControlData.ControlFlags.ControlRefresh != 0))
	{
		Status = CallTextCallBack(text, Data);
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetCallback
//
// Description:	Function to set callback.
//
// Input:		TEXT_DATA *text, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie 
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetCallback( TEXT_DATA *text, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( text, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetFocus
//
// Description:	Function to set focus.
//
// Input:		TEXT_DATA *text, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetFocus(TEXT_DATA *text, BOOLEAN focus)
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetPosition
//
// Description:	Function to set position.
//
// Input:		TEXT_DATA *text, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetPosition(TEXT_DATA *text, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( text, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetDimensions
//
// Description:	Function to set text dimension.
//
// Input:		TEXT_DATA *text, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetDimensions(TEXT_DATA *text, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( text, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetAttributes
//
// Description:	Function to set text attributes.
//
// Input:		TEXT_DATA *text, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetAttributes(TEXT_DATA *text, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( text, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextSetText
//
// Description:	function to set the text
//
// Input:	TEXT_DATA *text, CHAR16 *label, CHAR16 *value
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextSetText( TEXT_DATA *text, CHAR16 *label, CHAR16 *value )
{
	if ( label != NULL )
	{
		MemFreePointer( &text->LabelText );
		text->LabelText = StrDup( label );
	}

	if ( value != NULL )
	{
		MemFreePointer( &text->Text );
		text->Text = StrDup( value );
	}

	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TextGetControlHeight
//
// Description:	function to get the text height
//
// Input:	TEXT_DATA *text, Frame,  UINT16 *height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TextGetControlHeight( TEXT_DATA *text, VOID* frame,  UINT16 *height )
{
	//EIP-72610 if TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL;
		UINT16 tmpHeight=0;
		UINT16 Width;
	
		//EIP-147142  
		//Make sure text->Label and text->text are updated before computing the control height 		
		gText.SetText(text,
		        HiiGetString( text->ControlData.ControlHandle, UefiGetTextField((VOID*)text->ControlData.ControlPtr)),
		        HiiGetString( text->ControlData.ControlHandle, UefiGetTextTwoField((VOID*)text->ControlData.ControlPtr))
		        );
    
		Width = (UINT16)(text->LabelMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gLabelLeftMargin));
		newText = StringWrapText( text->Text, (UINT16)(((FRAME_DATA *)frame)->FrameData.Width - text->LabelMargin -2), &tmpHeight );
		*height = tmpHeight;
	    MemFreePointer( (VOID **)&newText );
	
		newText = StringWrapText( text->LabelText, Width, &tmpHeight );
	
		if(tmpHeight > *height)
			*height = tmpHeight;
	
		(*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
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
