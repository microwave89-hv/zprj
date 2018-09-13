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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/popup.c $
//
// $Author: Premkumara $
//
// $Revision: 14 $
//
// $Date: 5/03/14 6:22p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/popup.c $
// 
// 14    5/03/14 6:22p Premkumara
// [TAG]	EIP135665
// [Category]	Bug Fix
// Corrected condtion to display multi-line string
// 
// 13    5/03/14 4:01p Premkumara
// [TAG]	                EIP135665
// [Category]	Bug Fix
// [Severity:]	                Important
// [Symptom:]	TSE get hangs, when long string is given as title for
// password
// [Root Cause]	TSE is not handling properl when PasswordTitle length
// exceeds screen width 
// [Solution]	Handled password title length based on screen width and
// given support to display title in multiple lines.
// [Files]	postmgmtext.c, Popup.c, PopupEdit.c, PopupPassword.c 
// 
// 12    5/02/14 1:03p Premkumara
// [TAG]  		EIP154407
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	NVMe Driver - AddBootOption Hang
// [RootCause]  	System hangs When popup->width(NvMe driver path) is more
// than 
// gmaxcol.
// [Solution]  	Added condition to initialize the popup->width =
// gmaxcol-10 when
// it exceeds gmaxcol.
// [Files]  		popup.c
// 
// 11    2/11/14 9:01p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 10    12/06/13 4:49a Premkumara
// [TAG]	EIP135665
// [Category]	Bug Fix
// [Comments]             Corrected condtion properly for password and
// string type control
// 
// 9     12/03/13 9:02a Premkumara
// [TAG]	EIP135665
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	TSE get hangs, when long string is given as title for
// password
// [Root Cause]	TSE is not handling properl when PasswordTitle length
// exceeds screen width 
// [Solution]	Handled password title length based on screen width and
// given support to display title in multiple lines.
// [Files]	postmgmtext.c, Popup.c, PopupEdit.c, PopupPassword.c 
// 
// 8     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     12/01/11 1:39a Premkumara
// [TAG]  		EIP73236
// [Category]  	Improvement
// [Description]  	Large amounts of allocated memory are not freed
// [Files]  		Expression.c, PopupEdit.c, Popup.c, MessageBox.c, Menu.c,
// Memo.c,
// 
// 6     11/21/11 8:55a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupSel.c, PopupString.c, SubMenu.c, Text.c.
// 
// 5     6/28/11 10:14a Madhans
// To remove ";" in unwanted case.
// 
// 4     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
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
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		popup.c
//
// Description:	This file contains code to handle popup operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

POPUP_METHODS gPopup =
{
	PopupCreate,
	PopupDestroy,
	PopupInitialize,
	PopupDraw,
	PopupHandleAction,
	PopupSetCallback,
	PopupSetFocus,
	PopupSetPosition,
	PopupSetDimensions,
	PopupSetAttributes,
	PopupGetControlHight
};

extern BOOLEAN	IsShowPromptStringAsTitle(VOID);//EIP-116315 password string
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupCreate
//
// Description:	this function uses the create function of control
//					and creates the Popup menu
//
// Input:	POPUP_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupCreate( POPUP_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(POPUP_DATA) );

		if ( *object == NULL )
		return Status;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gPopup;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys the Popup menu
//
// Input:	POPUP_DATA *popup, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupDestroy( POPUP_DATA *popup, BOOLEAN freeMem )
{
	if(NULL == popup)
	  return EFI_SUCCESS;

	gControl.Destroy( popup, FALSE );

    if( freeMem ){
        MemFreePointer( (VOID **)&popup->Title );//EIP-73236
        MemFreePointer( (VOID **)&popup->Help1 );
        MemFreePointer( (VOID **)&popup->Help2 );
        MemFreePointer( (VOID **)&popup->Help3 );
		MemFreePointer( (VOID **)&popup );
    }

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupInitialize
//
// Description:	this function uses the initialize function of control
//					and initializes the Popup menu
//
// Input:	POPUP_DATA *popup, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupInitialize( POPUP_DATA *popup, VOID *data )
{
	EFI_STATUS Status = EFI_SUCCESS;

	Status = gControl.Initialize( (CONTROL_DATA *)popup, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	popup->PopupBorder = POPUP_SINGLE_BORDER; //Default border

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetLineCount
//
// Description:	function to get line count and max width.
//
// Input:	CHAR16 *line, UINT8 *Width 
//					
//
// Output:	UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN PopupGetLineCount(CHAR16 *line)
{
	CHAR16 * text;
	UINTN i=1;
	CHAR16 * String=line;
	

	while(1)
	{
		CHAR16 save;

		text = String;
		if ( *String == L'\0' )
			break;

		while ( ( *String != L'\n' ) &&( *String != L'\r' ) && ( *String != L'\0' ) )
			String++;

		save = *String;
		*String = L'\0';

		
		if ( ( *String = save ) != L'\0' )
		{
			if ( *String == L'\r' )
			{	String++;
				i--;
			}
			if ( *String == L'\n' )
			{
				String++;

				if ( *(String - sizeof(CHAR16)) == L'\r' )
					i++;
			}
		}
		else
			break;
		i++;
	}
	return i;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupDrawString
//
// Description:	function to draw string in a popup menu with attributes
//
// Input:	POPUP_DATA *popup, CHAR16 *Str,UINT16 Top
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PopupDrawString(POPUP_DATA *popup, CHAR16 *Str,UINT16 Top)
{
	CHAR16 *PadTitle = NULL;
	UINTN Height = 0;
	UINT16 OpCode = 0xFF;


	if ((EFI_IFR_OP_HEADER*)popup->ControlData.ControlPtr) //If it has valid control pointer
	{
		//Skipping ESC code color not to print title in color for Popup controls like OneOf,CheckBox,String,Password(based on token IsShowPromptStringAsTitle)
		if( (popup->ControlData.ControlType == CONTROL_TYPE_POPUPSEL) || 
			 (((EFI_IFR_OP_HEADER *)popup->ControlData.ControlPtr)->OpCode == EFI_IFR_STRING_OP) ||
			 (((EFI_IFR_OP_HEADER *)popup->ControlData.ControlPtr)->OpCode == CONTROL_TYPE_ORDERED_LIST) ||
			 ( IsShowPromptStringAsTitle() && ((EFI_IFR_OP_HEADER *)popup->ControlData.ControlPtr)->OpCode == EFI_IFR_PASSWORD_OP )
			)
		{
			Str = TseSkipEscCode(Str);
		}
	}

	if ((EFI_IFR_OP_HEADER*)popup->ControlData.ControlPtr) //If it has valid control pointer
		OpCode = ((EFI_IFR_OP_HEADER*)popup->ControlData.ControlPtr)->OpCode;

	//If control is of Password OR String type, and Multiline is supported
	if ( ( (OpCode == EFI_IFR_PASSWORD_OP ) || (EFI_IFR_STRING_OP == OpCode) ) && IsTSEMultilineControlSupported() )
	{
		if (Str)
		{
			Height=(EfiStrLen(Str) / popup->Width)+(((EfiStrLen(Str) % popup->Width) > 0)?1:0);
			DrawMultiLineStringWithAttribute (popup->Left+2, Top, popup->Width-3, Height, Str, 0);
		}
	}

	else
	{
		if ( Str != NULL )
		{
			PadTitle = EfiLibAllocateZeroPool( (popup->Width + 3) * sizeof(CHAR16) );

			//If no multiline support truncating the long string and showing ... at last
			if((TestPrintLength( Str) / (NG_SIZE)) > popup->Width)
			{
				UINTN  Index=HiiFindStrPrintBoundary(Str ,popup->Width);
				Str[Index-4] = L'\0';
				Str[Index-5] = L'.';
				Str[Index-6] = L'.';
				Str[Index-7] = L'.';
			}

			if ( PadTitle != NULL )
				SPrint( PadTitle, (EfiStrLen(Str)) * sizeof(CHAR16), L" %s ",Str );
		}
	
		if ( PadTitle )
		{
			DrawStringJustified( 0, gMaxCols, Top, JUSTIFY_CENTER, PadTitle );
			MemFreePointer((VOID **)&PadTitle);
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupDraw
//
// Description:	function to draw popup menu with attributes
//
// Input:	POPUP_DATA *popup
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupDraw( POPUP_DATA *popup )
{
	UINTN NumOfHelpLines = 0, NumOfTitleLines = 0;
	CHAR16 *String = NULL, *text = NULL;
	UINTN i=0;
	

	BOOLEAN bShadow = StyleGetShadowSupport() ;
	popup->Top = (UINT16)(gMaxRows - popup->Height) / 2;
	popup->Left = (UINT16)(gMaxCols - popup->Width) / 2;

   //EIP154407 System hangs if popup->Width is more than gMaxCols  
   if( popup->Width > gMaxCols)
   {
    popup->Width = (UINT16)(gMaxCols - 10);
   }

	
	if(popup->Style == POPUP_STYLE_NORMAL)
	{
		DrawWindow( popup->Left, popup->Top, popup->Width, popup->Height, 
				(UINT8)(popup->BGColor | popup->FGColor) , popup->Border, bShadow );
	
		if ( popup->Title != NULL )
			PopupDrawString(popup,popup->Title,popup->Top);
	}
	else
	{
#define TITLE_LINES	1
#define HELP_LINES	3
	
			
		if ( popup->Title != NULL )
			NumOfTitleLines = 2 ;

		if ( popup->Help1 != NULL )
			NumOfHelpLines = PopupGetLineCount(popup->Help1)+1 ;


		DrawWindow( popup->Left, popup->Top-NumOfTitleLines, popup->Width, popup->Height+NumOfHelpLines+NumOfTitleLines, 
				(UINT8)(popup->BGColor | popup->FGColor), FALSE, FALSE );

		if(NumOfTitleLines)
			DrawBorder( popup->Left, popup->Top-NumOfTitleLines, popup->Width, NumOfTitleLines+1 );
		if(NumOfHelpLines)
			DrawBorder( popup->Left, popup->Top+popup->Height-1, popup->Width, NumOfHelpLines+1);
		DrawBorder( popup->Left, popup->Top-NumOfTitleLines, popup->Width, popup->Height+NumOfHelpLines+NumOfTitleLines );

		if ( popup->Title != NULL )
			PopupDrawString(popup,popup->Title,popup->Top-1);

		//if ( popup->Help1 != NULL )
		//	PopupDrawString(popup,popup->Help1,popup->Top+popup->Height);

		String = popup->Help1 ;

		for(i=0;i<NumOfHelpLines;i++)
		{
			CHAR16 save;

			text = String;
			if ( *String == L'\0' )
				break;

			while ( ( *String != L'\n' ) &&( *String != L'\r' ) && ( *String != L'\0' ) )
				String++;

			save = *String;
			*String = L'\0';

			if((TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(popup->Width-2))
					EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(UINTN)(popup->Width-5))],L"...");
	
			PopupDrawString(popup, text, (UINT16)(popup->Top+popup->Height+i));
			

			if ( ( *String = save ) != L'\0' )
			{
				String++;
				if ( ( *String == L'\r' ) || ( *String == L'\n' ) )
					String++;
			}
		}
	}

	return gControl.Draw( popup );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSetCallback
//
// Description:	Function to set the Popup callback
//
// Input:		POPUP_DATA *popup, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSetCallback( POPUP_DATA *popup, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( popup, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupHandleAction
//
// Description:	Function to handle the Popup Edit actions
//
// Input:	POPUP_DATA *popup, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupHandleAction( POPUP_DATA *popup, ACTION_DATA *Data)
{
	//do nothing here, the action is handled on the child class either listbox or messagebox
	return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSetFocus
//
// Description:	Function to set focus
//
// Input:		POPUP_DATA *popup, BOOLEAN focus
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSetFocus( POPUP_DATA *popup, BOOLEAN focus)
{
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSetPosition
//
// Description:	Function to set focus
//
// Input:		POPUP_DATA *popup, UINT16 Left, UINT16 Top 
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSetPosition( POPUP_DATA *popup, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( popup, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSetDimensions
//
// Description:	Function to set the dimentions of the editable popup menu
//
// Input:		POPUP_DATA *popup, UINT16 Width, UINT16 Height
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSetDimensions( POPUP_DATA *popup, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( popup, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupSetAttributes
//
// Description:	Function to set the dimentions of the editable popup menu
//
// Input:		POPUP_DATA *popup, UINT8 FGColor, UINT8 BGColor
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupSetAttributes( POPUP_DATA *popup, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( popup, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupGetControlHight
//
// Description:	Function unsuppored.
//
// Input:		VOID *object,VOID *frame, UINT16 *height
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupGetControlHight( VOID *object,VOID *frame, UINT16 *height )
{
	return EFI_UNSUPPORTED;
}


//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**       (C)Copyright 1985-2014, American Megatrends, Inc.     **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**    5555 Oakbrook Pkwy, Norcross, Suite 200, Georgia 30093   **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

