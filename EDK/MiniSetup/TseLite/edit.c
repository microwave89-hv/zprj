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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/edit.c $
//
// $Author: Arunsb $
//
// $Revision: 12 $
//
// $Date: 10/18/12 6:02a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/edit.c $
// 
// 12    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 11    4/05/12 7:14a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 10    11/30/11 12:46a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 9     11/21/11 12:09p Premkumara
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
// 8     11/21/11 8:50a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupSel.c, PopupString.c, SubMenu.c, Text.c.
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
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 6:50a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     8/13/09 1:17p Blaines
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
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
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
// Name:		Edit.c
//
// Description:	This file contains code to handle Edit control operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


EDIT_METHODS gEdit =
{
	EditCreate,
	EditDestroy,
	EditInitialize,
	EditDraw,
	EditHandleAction,
	EditSetCallback,
	EditSetFocus,
	EditSetPosition,
	EditSetDimensions,
	EditSetAttributes,
	EditGetControlHight

};

EFI_STATUS _EditHandleActionKey(EDIT_DATA *edit, AMI_EFI_KEY_DATA key);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditCreate
//
// Description:	Function to create Edit Controls, which uses the control functions.
//
// Input:	EDIT_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditCreate( EDIT_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(EDIT_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gEdit;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditDestroy
//
// Description:	Function to Destroy Edit Controls, which uses the control functions.
//
// Input:	EDIT_DATA *edit, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditDestroy( EDIT_DATA *edit, BOOLEAN freeMem )
{
	if(NULL == edit)
	  return EFI_SUCCESS;

	gControl.Destroy( edit, FALSE );

	MemFreePointer( (VOID **)&edit->Text );
	MemFreePointer( (VOID **)&edit->TempText );

	if( freeMem )
		MemFreePointer( (VOID **)&edit );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditInitialize
//
// Description:	Function to Initialize Edit Controls, which uses the control functions.
//
// Input:	EDIT_DATA *edit, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditInitialize( EDIT_DATA *edit, VOID *data )
{
	EFI_STATUS Status =  EFI_UNSUPPORTED;

	Status = gControl.Initialize( edit, data );
	if (EFI_ERROR(Status))
		return Status;

	SetControlColorsHook(NULL, NULL,
						 NULL,NULL, 
						 NULL /*&(edit->SelBGColor )*/, &(edit->SelFGColor),
	                     			&(edit->BGColor), &(edit->FGColor),
						 NULL /*UINT8 *LabelBGColor*/,&(edit->LabelFGColor) /*UINT8 *LabelFGColor*/,
						 &(edit->NSelLabelFGColor)/*UINT8 *NSelLabelFGColor*/,
						 &(edit->SelBGColor )/*EditBGColor*/,&(edit->EditFGColor),
						 NULL, NULL );


	// add extra initialization here...
	edit->TextMargin = (UINT8)gControlLeftMargin;
	if ( edit->TextWidth == 0 )
	{
	    edit->TextWidth = UefiGetWidth(((CONTROL_INFO *)data)->ControlPtr);
		edit->TextWidth = (edit->TextWidth>1)?(3 * (UINT16)edit->TextWidth):4;
	}

	edit->TextAreaWidth = (edit->TextWidth </*10*/(UINT16)(edit->Width - edit->TextMargin - 2)) ? edit->TextWidth:/*10*/(UINT16)(edit->Width - edit->TextMargin - 2);
	edit->Text = EfiLibAllocateZeroPool((edit->TextWidth +1)* sizeof(CHAR16));
	MemSet( edit->Text, (edit->TextWidth +1)* sizeof(CHAR16), 0 );

	if(  *((UINT8*)((CONTROL_INFO *)data)->ControlPtr) == IFR_PASSWORD_OP)
		edit->Chr = L'*';

	if ( edit->Text != NULL )
	{
        VarGetValue( edit->ControlData.ControlVariable, 
		         UefiGetQuestionOffset(((CONTROL_INFO *)data)->ControlPtr), 
				 UefiGetWidth(((CONTROL_INFO *)data)->ControlPtr), edit->Text );
	  
	}
	edit->TempText = EfiLibAllocateZeroPool((edit->TextWidth +1)* sizeof(CHAR16));
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditDraw
//
// Description:	Function to draw Edit Controls.
//
// Input:	EDIT_DATA *edit
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditDraw(EDIT_DATA *edit )
{
	CHAR16 *text,*text2;
	UINT16 i;
	UINT8 BGClr,FGClr;
    
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 ColorNSel = edit->FGColor;
	UINT8 ColorLabel = (edit->ControlFocus) ? edit->LabelFGColor : edit->NSelLabelFGColor ;
		
	
	if(edit->ControlFocus)
	{  
		BGClr = edit->SelBGColor;
		if(edit->ControlActive)
			FGClr =  edit->EditFGColor;  
		else
			FGClr =  edit->SelFGColor; 
	}
	else
	{ 
		BGClr =  edit->BGColor;
		FGClr = /*ColorLabel;*/ edit->FGColor;  
	}

	// check conditional ptr if necessary
        //EIP 75486 Support grayout condition for readonly controls
		//if( edit->ControlData.ControlConditionalPtr != 0x0)
		//{
			switch( CheckControlCondition( &edit->ControlData ) )
			{
				case COND_NONE:
					break;
				case COND_GRAYOUT:
					Status = EFI_WARN_WRITE_FAILURE;
					FGClr = ColorNSel =  ColorLabel = CONTROL_GRAYOUT_COLOR;
					break;
				default:
					return EFI_UNSUPPORTED;
					break;
			}
		//}
 
	
	text = HiiGetString( edit->ControlData.ControlHandle, UefiGetPromptField(edit->ControlData.ControlPtr));
	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == text){
		text = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
		if(!text)
			return EFI_NOT_FOUND;
		EfiStrCpy(text,L" ");
	}
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(edit->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( edit->Left , edit->Top, 
				(UINTN)(edit->TextMargin - edit->Left),(UINTN) edit->Height,
				text, edit->BGColor | ColorLabel );
	}
	else
	{
		// boundary overflow  check
		if ((TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(edit->TextMargin - edit->Left  )/*21*/ )
				text[HiiFindStrPrintBoundary(text,(UINTN)(edit->TextMargin - edit->Left  ))] = L'\0';
	
		DrawStringWithAttribute( edit->Left  , edit->Top, (CHAR16*)text, 
			edit->BGColor | ColorLabel/*((edit->ControlFocus)? edit->LabelFGColor : edit->NSelLabelFGColor )*/ );

	}

	for(i=0; i < edit->TextAreaWidth; i++)
		DrawStringWithAttribute( edit->Left + edit->TextMargin + i  , edit->Top, L" ", 
				BGClr | FGClr );

	if(edit->Chr != 0x0)
	{
		text2 = EfiLibAllocateZeroPool( ((TestPrintLength( edit->Text ) / (NG_SIZE))+1) * sizeof(CHAR16));
		for(i = 0; (i < (TestPrintLength( edit->Text ) / (NG_SIZE))) && (i < edit->TextAreaWidth); i++ )
			text2[i] = edit->Chr;

		DrawStringWithAttribute( edit->Left + edit->TextMargin, edit->Top, text2, 
				BGClr | FGClr );
		MemFreePointer((VOID **)&text2);
	}
	else
		DrawStringWithAttribute( edit->Left + edit->TextMargin  , edit->Top , edit->Text, 
				BGClr | FGClr );


    MemFreePointer((VOID **)&text);

    FlushLines( edit->Top, edit->Top );
    DoRealFlushLines();
		MouseRefresh();
    return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditSetCallback
//
// Description:	Function to set callback.
//
// Input:		EDIT_DATA *edit, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie 
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditSetCallback( EDIT_DATA *edit, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( edit, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditHandleAction
//
// Description:	Function to handle Edit actions.
//
// Input:	EDIT_DATA *edit, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditHandleAction( EDIT_DATA *edit, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;


    if ( Data->Input.Type == ACTION_TYPE_KEY )
        return _EditHandleActionKey(edit, Data->Input.Data.AmiKey);

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_EditHandleActionKey
//
// Description:	Function to handle Edit actions.
//
// Input:	EDIT_DATA *edit, AMI_EFI_KEY_DATA key
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _EditHandleActionKey(EDIT_DATA *edit, AMI_EFI_KEY_DATA key)
{
	UINT8 Redraw =0;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINTN i;
    CONTROL_ACTION Action;


    //Get mapping
    Action = MapControlKeysHook(key);

    switch(Action)
    {
        case ControlActionAbort:
            if(edit->ControlActive == TRUE)
                Status = EFI_SUCCESS;
        case ControlActionNextUp:
        case ControlActionNextDown:
            if(edit->ControlActive == TRUE)
            {
                MemCopy(edit->Text,edit->TempText,edit->TextWidth*sizeof(UINT16)); //UNICODE CHARS
                edit->ControlActive = FALSE;
                Redraw = 1;
            }
        break;

        case ControlActionNextLeft:
        case ControlActionNextRight:
            if(edit->ControlActive == TRUE)
			   Status = EFI_SUCCESS; // cosume the action if editing
		break;

        case ControlActionSelect:
    		if(edit->Callback != NULL)
			{
				if ( edit->Cookie != NULL )
				{
					CALLBACK_VARIABLE *callbackData = (CALLBACK_VARIABLE *)edit->Cookie;

					callbackData->Variable = edit->ControlData.ControlVariable;
					callbackData->Offset = UefiGetQuestionOffset(edit->ControlData.ControlPtr);
					callbackData->Length = UefiGetWidth(edit->ControlData.ControlPtr);
					callbackData->Data = (VOID *)edit->Text;
                
					edit->Callback( edit->Container,edit, edit->Cookie );	
				}
			}

			Redraw =1;
			edit->ControlActive = FALSE;
			Status = EFI_SUCCESS;
        break;

        case ControlActionBackSpace:
			if(EfiStrLen(edit->Text)>0)
			{
				if(edit->ControlActive == FALSE)
				{
					MemCopy(edit->TempText,edit->Text,edit->TextWidth * sizeof(UINT16)); //UNICODE CHARS
					edit->ControlActive = TRUE; 
				}
				edit->Text[EfiStrLen(edit->Text)-1] = 0x0;
				Redraw =1;
			}
        break;

        default:
            if(SCAN_NULL == key.Key.ScanCode)
            {
    			if((EfiStrLen(edit->Text) < edit->TextWidth) | 
    				( (edit->ControlActive == FALSE) ) && (edit->ControlData.ControlType == CONTROL_TYPE_NUMERIC) )
    			{
    				if(edit->ControlActive ==FALSE)
    				{
                        MemCopy(edit->TempText,edit->Text,edit->TextWidth* sizeof(UINT16));
    					if(edit->ControlData.ControlType == CONTROL_TYPE_NUMERIC)
    					{
                            i = edit->TextWidth;
    						do	{
    						   edit->Text[i] = 0x0;
    						}while(i-- > 0 );
    					}
    					edit->ControlActive = TRUE; 
    				}
    
    				i = EfiStrLen(edit->Text);
    				edit->Text[i] = key.Key.UnicodeChar ; 
                    edit->Text[i+1] = 0x0 ; 
    				Redraw =1;
    			}
            }
       break;
    }

	if(Redraw)
		Status = gEdit.Draw(edit);

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditSetFocus
//
// Description:	Function to set the edit focus.
//
// Input:		EDIT_DATA *edit, BOOLEAN focus
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditSetFocus(EDIT_DATA *edit, BOOLEAN focus)
{
	if(focus != FALSE)
	{
		if ( CheckControlCondition( &edit->ControlData ) )
			return EFI_UNSUPPORTED;
	}

	if( !(edit->ControlFocus && focus) )
		edit->ControlFocus = focus;

	if(!focus) 
		edit->ControlActive = 0;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditSetPosition
//
// Description:	Function to set the edit position.
//
// Input:		EDIT_DATA *edit, UINT16 Left, UINT16 Top
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditSetPosition(EDIT_DATA *edit, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( edit, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditSetDimensions
//
// Description:	Function to set the edit dimensions.
//
// Input:		EDIT_DATA *edit, UINT16 Width, UINT16 Height 
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditSetDimensions(EDIT_DATA *edit, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( edit, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditSetAttributes
//
// Description:	Function to set the edit attributes.
//
// Input:		EDIT_DATA *edit, UINT8 FGColor, UINT8 BGColor
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditSetAttributes(EDIT_DATA *edit, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( edit, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EditGetControlHight
//
// Description:	Function unsuppored.
//
// Input:		VOID *object,VOID *frame, UINT16 *height
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EditGetControlHight( VOID *object,VOID *frame, UINT16 *height )
{
	return EFI_UNSUPPORTED;
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
