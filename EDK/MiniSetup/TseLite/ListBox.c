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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ListBox.c $
//
// $Author: Premkumara $
//
// $Revision: 32 $
//
// $Date: 5/03/14 3:11p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ListBox.c $
// 
// 32    5/03/14 3:11p Premkumara
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
// 31    5/02/14 3:54a Arunsb
// [TAG]	EIP155965
// [Category]	Improvement
// [Description]	MessageBox, ListBox cannot be canceled by Mouse
// Right-Click
// [Files]	MessageBox.c, ListBox.c and minisetupext.c
// 
// 30    2/11/14 9:03p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 29    12/05/13 1:25a Premkumara
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
// 28    12/03/13 2:11p Premkumara
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
// 27    1/22/13 12:21a Rajashakerg
// [TAG]  		EIP103449
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	In Setup click\Touch from navigation window, option are not
// displayed properly
// [RootCause]  	Latest mouse driver providing LEFT_DOWN when we hold the
// mouse left down button.
// [Solution]  	Provided fix resolves the issue.
// [Files]  		ezport.c, PopupEdit.c, ListBox.c, MessageBox.c
// 
// 26    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 26    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 24    9/21/12 8:40a Arunsb
// Build error corrected
// 
// 23    9/18/12 6:31a Arunsb
// [TAG]  		EIP93686
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When string too long will hang on bbs menu
// [RootCause]  	listbox->Width is not within the limit
// [Solution]  	listbox->Width handled properly
// [Files]  		ListBox.c
// 
// 22    5/28/12 12:32p Premkumara
// [TAG]  		EIP67049 & 90224
// [Category]  	New Feature
// [Description]  	Support mouse drag operation in frame and list box
// [Files]  		CommonHelper.c, Frame.c, ListBox.c, Minisetupext.h
// 
// 21    5/21/12 3:09a Arunsb
// [TAG]  		EIP87658
// [Category]  	Improvement
// [Description]  	Baudrate 9600 refresh sreen twice. Removed screen
// saving and restoring.
// [Files]  		Listbox.c
// 
// 20    1/20/12 4:11a Rajashakerg
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
// 19    11/01/11 5:47a Arunsb
// [Category]  	Improvement
// [Description]  	To change the single click behaviour as like double
// click
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c and listbox.c
// 
// 18    10/19/11 1:00p Madhans
// Fix to check for Listbox is NOT NULL before free the controls.
// 
// 17    1/24/11 1:38p Blaines
// [TAG] - EIP 48316
// [Category]- Defect
// [Severity]- Mordarate
// [Symptom]- The keys "Caps Lock", "Scroll Lock" and "Num Lock" have
// function and the function is the same as the key "Enter".
// [Solution] - Check for valid listbox hot-keys before calling listbox
// callback function.
// [Function] - ListBoxHandleAction
// [File] - listbox.c.
// 
// 16    12/24/10 3:46p Mallikarjunanv
// [TAG]  		EIP 45949
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BIOS Setup hang when the control string length is long
// [RootCause]  	List box title string is not truncated if it exceeds the
// limit.
// [Solution]  	Truncating the list box title string if it exceeds the
// limit
// 
// [Files]  		ListBox.c
// 
// 15    12/24/10 11:38a Mallikarjunanv
// [TAG]  		EIP48384
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Unable to select options in "Delete boot option", "Boot
// [RootCause]  	 In case of Listbox with scroll bar control is returned
// without updating the selected control 
// [Solution]  	Fixed the issue with respect to List box selection using
// mouse by commenting the return statement before selecting/highliting
// the clicked control.
// [Files]  		ListBox.c
// 
// 14    11/18/10 7:24p Blaines
// [TAG] - EIP 45374
// [Category]- Function Request
// [Synopsis]- Need method to configure Post Menu programmatically, Items
// requested 
// - Exit Keys
// - Font Colors
// - Background Colors.
// [Solution]
//  - Create hook to set window color, 
//  - Add AMI_POSTMENU_ATTRIB_EXIT_KEY  attribute to POSTMENU_TEMPLATE to
// configure exit keys.
// [Files] - stylecommon.c, style.h, listbox.c, minisetupext.c,
// AMIPostMgr.h
// 
// 
// [TAG] - EIP 48417
// [Category]- Defect
// [Symptom]- PostManagerDisplayMenu does not dynamically update Menu
// Title on language change.
// 
// [Solution]- Update listbox title string by calling HiiGetString
// whenever a selection is made. redraws.
// [Files] - listbox.c, minisetupext.c,
// 
// 
// 
// 13    10/20/10 1:40p Mallikarjunanv
// reverting back to v25
// 
// 11    9/07/10 12:25a Mallikarjunanv
// EIP-42124: Added Page up and Page down key in List box
// 
// 10    8/12/10 11:30a Blaines
// EIP-41614 : Change to allow DisplayPostMenu protocol to dynamically
// update menu items modified from the callback functions.
// 
// 9     6/15/10 10:47a Blaines
// Fix issue where Listbox->PtrItems[] is refered in places even if the
// style is not POPUP_STYLE_BBS.
// 
// 8     6/04/10 12:58p Blaines
// Add support for displaying menu list with (ALL) non-focusable items.
// 
// 7     5/24/10 6:06p Blaines
// Make sure selectable items are not hidden or non-focused in the
// function ListBoxHandleAction. 
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 9     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 8     2/15/10 10:13p Madhans
// To avoid warnings
// 
// 7     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 6     1/09/10 6:51a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     8/26/09 4:11p Blaines
// To fix issue with BBS popup when more then 20 bootoptions are present
// 
// 4     8/19/09 12:54p Madhans
// To return failure on invalid action.
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
// 3     3/31/09 4:08p Madhans
// UefiGetOption Interface change..
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
// Name:		ListBox.c
//
// Description:	This file contains code to handle Listbox controls
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//EIP-67049
static INT32 lButtonVaryingPosition = 0;
static INT32 lButtonInitialPosition = 0;
BOOLEAN lButtonOnListBoxScroll = FALSE;
BOOLEAN ScrollBarMoveAction = FALSE;
static UINT32 gListBoxScrollBarTop = 0, gListBoxScrollBarBottom = 0;
//EIP-67049 End
LISTBOX_METHODS gListBox =
{
	ListBoxCreate,
	ListBoxDestroy,
	ListBoxInitialize,
	ListBoxDraw,
	ListBoxHandleAction,
	ListBoxSetCallback,
	ListBoxSetFocus,
	ListBoxSetPosition,
	ListBoxSetDimensions,
	ListBoxSetAttributes,
	ListBoxGetControlHight,
	ListBoxInitializeBBSPopup
};
BOOLEAN SingleClickActivation (VOID); //EIP74141 providing select option for single click too

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxCreate
//
// Description:	Function to create a List Box, which uses the popup controls.
//
// Input:	LISTBOX_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxCreate( LISTBOX_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(LISTBOX_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gPopup.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gListBox;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxDestroy
//
// Description:	Function to Destroy a List Box, which uses the popup controls.
//
// Input:	LISTBOX_DATA *listbox, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxDestroy( LISTBOX_DATA *listbox, BOOLEAN freeMem )
{
    if(listbox == NULL)
        return EFI_SUCCESS;

	gPopup.Destroy( listbox, FALSE );

	RestoreScreen( listbox->ScreenBuf );

	if( freeMem )
	{
		MemFreePointer((VOID **)&listbox->Title);
		MemFreePointer((VOID **)&listbox->PtrTokens);
		MemFreePointer((VOID **)&listbox->PtrItems);
		MemFreePointer((VOID **)&listbox->Help1);
		MemFreePointer((VOID **)&listbox->Help2);
		MemFreePointer((VOID **)&listbox->Help3);
		MemFreePointer( (VOID **)&listbox );
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetListBoxString
//
// Description:	Function to set a string in List Box.
//
// Input:	LISTBOX_DATA *listbox, CHAR16 **pStr,UINT16 Toke
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetListBoxString(LISTBOX_DATA *listbox, CHAR16 **pStr,UINT16 Token)
{
	CHAR16 *TempStr=NULL;
	UINT16 TitleLength;

	TempStr = HiiGetString( listbox->ControlData.ControlHandle, Token );

	if ( TempStr != NULL )
	{
		TitleLength = (UINT16)((TestPrintLength( TempStr ) / (NG_SIZE)) + 3);

		//EIP_45949 - Truncate the list box title if it exceeds the limit
		if( TitleLength > gMaxCols-9 ){
			TempStr[gMaxCols-9] = L'\0';
			TitleLength = (UINT16)((TestPrintLength( TempStr ) / (NG_SIZE)) + 3);
		}

		if( listbox->Width < TitleLength + 4 )
			listbox->Width = TitleLength + 4;
	}
	*pStr = TempStr;
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
UINTN GetLineCount(CHAR16 *line, UINT8 *Width )
{
	CHAR16 * text;
	UINTN i=1;
	CHAR16 * String=line;
	UINT8 length;

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

		length = 0 ;
		length = (UINT8)((TestPrintLength(text) / (NG_SIZE))) ;
		if(length > *Width)
			*Width = length ;

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
// Procedure:	SetListBoxHelpString
//
// Description:	Function to set a string in List Box.
//
// Input:	LISTBOX_DATA *listbox, CHAR16 **pStr,UINT16 Toke
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetListBoxHelpString(LISTBOX_DATA *listbox, CHAR16 **pStr,UINT16 Token)
{
	CHAR16 *TempStr=NULL;
	UINT8 Width=0 ;

	TempStr = HiiGetString( listbox->ControlData.ControlHandle, Token );

	if ( TempStr != NULL )
	{
		GetLineCount(TempStr, &Width);	
				
		if( listbox->Width < Width + 4 )
			listbox->Width = Width + 4;
	}
	*pStr = TempStr;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetListBoxString
//
// Description:	Function to set the common fields in a List Box.
//
// Input:	LISTBOX_DATA *listbox
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetListBoxCommonFields(LISTBOX_DATA *listbox)
{
	
	listbox->Width += 4;
	listbox->Sel = 0;

	// check if we need to use do srollbar
	if(listbox->Height > MAX_VISIBLE_SELECTIONS )
	{
		listbox->Height = (UINT16)MAX_VISIBLE_SELECTIONS;
      		listbox->Width++;   // ad space for the scrollbar.
		listbox->FirstVisibleSel = 0;
		listbox->LastVisibleSel = listbox->Height-3; // 2 for borders and 1 more because is zero based.
         
	}
	else
	{
		listbox->FirstVisibleSel = 0;
		listbox->LastVisibleSel =  listbox->Height-3;
	}
	SetControlColorsHook(NULL, NULL, NULL, NULL ,NULL, NULL,
		              NULL , NULL,NULL, NULL,	NULL,NULL ,NULL,
			 	&(listbox->FGColor),&(listbox->BGColor));

	listbox->Border =TRUE;
	listbox->Shadow = TRUE;
	if(listbox->ScreenBuf == NULL)
	listbox->ScreenBuf = SaveScreen();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetListBoxString
//
// Description:	Function to initialize a List Box, which uses the Popup controls.
//
// Input:	LISTBOX_DATA *listbox, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxInitialize( LISTBOX_DATA *listbox, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 TempLength=0;
	UINT16 TitleToken;
	UINT16 Index= 0 ;

	Status = gPopup.Initialize( listbox, data );
	if (EFI_ERROR(Status))
		return Status;
	// add extra initialization here...
	listbox->ControlData.ControlHelp = UefiGetHelpField(listbox->ControlData.ControlPtr);

	listbox->ListHandle = listbox->ControlData.ControlHandle;
	listbox->HiddenItemCount = 0;
	Status = UefiGetOneOfOptions(&listbox->ControlData,&listbox->ListHandle,&listbox->PtrTokens, NULL, &listbox->ItemCount,NULL,NULL);

	if ( ! EFI_ERROR(Status) )
	{

		for ( Index = 0; Index < listbox->ItemCount; Index++ )
		{
			TempLength = (UINT16)HiiMyGetStringLength( listbox->ListHandle, listbox->PtrTokens[Index] );
	
			if ( TempLength > listbox->Width )
				listbox->Width = TempLength;
		}
		if (listbox->Width > (gMaxCols-6))
		    listbox->Width = (UINT16)(gMaxCols-6);

		listbox->ItemCount = Index;
		listbox->Height = Index + 2;

		//pad title 
		TitleToken = UefiGetPromptField(listbox->ControlData.ControlPtr);
		SetListBoxString(listbox,&listbox->Title ,TitleToken);
		SetListBoxCommonFields(listbox);
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetListBoxString
//
// Description:	Function to initialize the BBS Popup in a List Box.
//
// Input:	LISTBOX_DATA *listbox, LISTBOX_BSS_POPUP_DATA *listboxBBSPopupData
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxInitializeBBSPopup( LISTBOX_DATA *listbox, LISTBOX_BSS_POPUP_DATA *listboxBBSPopupData )
{
	UINT16 Index= 0 ;
	UINT16 TempLength=0;
	EFI_STATUS Status = EFI_SUCCESS;

	listbox->Style = POPUP_STYLE_BBS;
	
	if(listboxBBSPopupData->pControlData != NULL )
		MemCopy( &listbox->ControlData, listboxBBSPopupData->pControlData, sizeof(CONTROL_INFO) );

	listbox->ListHandle = listbox->ControlData.ControlHandle;
	listbox->ItemCount = listboxBBSPopupData->ItemCount;
	listbox->HiddenItemCount = listboxBBSPopupData->HiddenItemCount;
	listbox->Height = listbox->ItemCount - listbox->HiddenItemCount + 2;

	listbox->PtrItems = EfiLibAllocatePool( listbox->ItemCount * sizeof(POSTMENU_TEMPLATE) ); 
	if ( listbox->PtrItems == NULL )
		Status = EFI_OUT_OF_RESOURCES;
	else
	{
		for ( Index = 0; Index < listbox->ItemCount; Index++ )
		{
			listbox->PtrItems[Index] = listboxBBSPopupData->PtrItems[Index] ;

			if((listbox->PtrItems[Index].Attribute != AMI_POSTMENU_ATTRIB_HIDDEN)&&
				(listbox->PtrItems[Index].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY))
			{
				TempLength = (UINT16)HiiMyGetStringLength( listbox->ListHandle, listbox->PtrItems[Index].ItemToken );
	
				if ( TempLength > listbox->Width )
					listbox->Width = TempLength;
			}
		}
		if (listbox->Width > (gMaxCols-6))
		    listbox->Width = (UINT16)(gMaxCols-6);
		    
		if(listboxBBSPopupData->TitleToken)
			SetListBoxString(listbox,&listbox->Title ,listboxBBSPopupData->TitleToken);
		if(listboxBBSPopupData->Help1Token)
			SetListBoxHelpString(listbox,&listbox->Help1 ,listboxBBSPopupData->Help1Token);
		//SetListBoxString(listbox,&listbox->Help2 ,listboxBBSPopupData->Help2Token);
		//SetListBoxString(listbox,&listbox->Help3 ,listboxBBSPopupData->Help3Token);
		SetListBoxCommonFields(listbox);
	}

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure	:	ListBoxDrawSeperator
//
// Description	:	function to draw the border
//
// Input		:	UINTN Left, UINTN Top, UINTN Width, UINTN Height
//
// Output		:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ListBoxDrawSeperator( LISTBOX_DATA *listbox, UINTN Left, UINTN Top, UINTN Width, UINTN Height )
{
	UINTN  Index;
	CHAR16 *Line;

	UINTN Right, Bottom;

	Line = EfiLibAllocateZeroPool( (Width + 6) * sizeof(CHAR16) );

	if ( Line == NULL )
		return;

	Right = Left + Width - 1;
	Bottom = Top + Height - 1;

	for ( Index = 1; Index < Width - 1; Index++ )
		Line[Index] = BOXDRAW_HORIZONTAL;

	if(listbox->Border)
	{
		Line[0] = BOXDRAW_VERTICAL_RIGHT;

		if(!listbox->UseScrollbar)
			Line[Index] = BOXDRAW_VERTICAL_LEFT;

		DrawString( Left, Top, Line );
	}
	
	

	MemFreePointer( (VOID **)&Line );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxDraw
//
// Description:	Function to draw a List Box.
//
// Input:	LISTBOX_DATA *listbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxDraw( LISTBOX_DATA *listbox )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN Index;
	CHAR16 *text = NULL;
	UINT32  FirstLine = 0, LastLine = 0;
	CHAR16	ArrUp[2]={{GEOMETRICSHAPE_UP_TRIANGLE},{0x0000}},ArrDown[2]={{GEOMETRICSHAPE_DOWN_TRIANGLE},{0x0000}},ScrlSel[2]={{BLOCKELEMENT_FULL_BLOCK/*L'N'*/},{0x0000}},ScrlNSel[2]={{BLOCKELEMENT_LIGHT_SHADE/*L'S'*/},{0x0000}};
    UINT16 BorderWidth = 4;
	UINT8 FGColor = listbox->FGColor;
	UINT8 BGColor = listbox->BGColor;
	

	Status =  gPopup.Draw( listbox );
	if (Status != EFI_SUCCESS)
		return Status;

	listbox->UseScrollbar = FALSE;

	
	// check if we need to use do scrollbar
	if((listbox->ItemCount-listbox->HiddenItemCount) > (UINT16)(MAX_VISIBLE_SELECTIONS - 2))
	{
  		listbox->UseScrollbar = TRUE ;      	
		BorderWidth = 5;
		//EIP-67049
		if (!ScrollBarMoveAction)
		{
			if( listbox->Sel < listbox->FirstVisibleSel)
			{
				if((listbox->Sel != 0) && (listbox->Sel < listbox->LastVisibleSel -1))
				{
					listbox->FirstVisibleSel = listbox->Sel;
					listbox->LastVisibleSel = listbox->Sel + listbox->Height -3 ;
				}
				else
				{
					if( listbox->Sel !=0)
					{
						listbox->FirstVisibleSel = listbox->Sel /*--*/;
						listbox->LastVisibleSel = listbox->FirstVisibleSel + listbox->Height -3;
					}
					else
					{
						listbox->FirstVisibleSel = 0 ;
						listbox->LastVisibleSel = listbox->Height -3;
					}
				}
			}

			if(listbox->Sel > listbox->LastVisibleSel )
			{
				if( (( listbox->Sel +listbox->Height-3) <= (listbox->ItemCount-listbox->HiddenItemCount-1) ) && (listbox->Sel > listbox->LastVisibleSel +1))
				{
					listbox->FirstVisibleSel = listbox->Sel;
					listbox->LastVisibleSel = listbox->Sel + listbox->Height -3 ;
				}
				else
				{
					if( (listbox->Sel ) < (listbox->ItemCount-listbox->HiddenItemCount-1))
					{
						listbox->FirstVisibleSel = listbox->Sel - listbox->Height +3 /*--*/;
						listbox->LastVisibleSel = listbox->Sel;
					}
					else
					{
						listbox->FirstVisibleSel = listbox->ItemCount-listbox->HiddenItemCount-1  - listbox->Height +3 ;
						listbox->LastVisibleSel = listbox->ItemCount-listbox->HiddenItemCount-1;
					}
				}
			}
		}

		// draw the scrollbar
       		DrawStringWithAttribute( listbox->Left + listbox->Width -2 , listbox->Top+1, ArrUp, 
		                            listbox->FGColor | listbox->BGColor );
		
		DrawStringWithAttribute( listbox->Left+ listbox->Width -2, listbox->Top + listbox->Height-2, ArrDown, 
					                             listbox->FGColor | listbox->BGColor );

		FirstLine = ((listbox->Height-2)* listbox->FirstVisibleSel/(listbox->ItemCount-listbox->HiddenItemCount) )+ listbox->Top+2;
	    LastLine  = ((listbox->Height-2)* listbox->LastVisibleSel/(listbox->ItemCount-listbox->HiddenItemCount) )+ listbox->Top+2;
	
		gListBoxScrollBarTop = FirstLine; //EIP-67049 To store Scrollbar Top positon 
		gListBoxScrollBarBottom = LastLine; //EIP-67049 To store Scrollbar Bottom positon 

		for(Index = (listbox->Top + 2); Index < (UINTN)(listbox->Top + listbox->Height -2) ;Index++)
		{
                      if( (Index >= FirstLine) && (Index < LastLine))
						  DrawStringWithAttribute( listbox->Left+ listbox->Width-2, Index, ScrlSel, 
						                            listbox->FGColor | listbox->BGColor );
					  else
                        DrawStringWithAttribute( listbox->Left+ listbox->Width-2, Index, ScrlNSel, 
						                         listbox->FGColor | listbox->BGColor );
		}

	}


	// highlight selected item
	for ( Index = listbox->FirstVisibleSel/*0*/; Index <= listbox->LastVisibleSel/*listbox->ItemCount*/; Index++ )
	{
		if ( Index == listbox->Sel )
		{
			FGColor = EFI_WHITE ;
			BGColor = EFI_BACKGROUND_BLACK ;

			if(listbox->Style == POPUP_STYLE_BBS)
			{
				text = HiiGetString( listbox->ListHandle, listbox->PtrItems[Index].ItemToken );
				
				// Check condition if item is non-focusable
				// This may occur if all menu items are set non-focusable
				if( listbox->PtrItems[Index].Attribute == AMI_POSTMENU_ATTRIB_NON_FOCUS)
				{
				     FGColor = EFI_LIGHTGRAY;
				     BGColor = listbox->BGColor;
				}	
			}
			else
				text =  HiiGetString( listbox->ListHandle, listbox->PtrTokens[Index]);

			if(!text)
				text = EfiLibAllocateZeroPool(2);
			if((TestPrintLength( text) / (NG_SIZE)) >(UINTN) (listbox->Width - BorderWidth) )
				text[HiiFindStrPrintBoundary(text ,listbox->Width - BorderWidth)] = L'\0';
			DrawStringWithAttribute( listbox->Left + 2, listbox->Top + Index - listbox->FirstVisibleSel  + 1, 
					text, BGColor | FGColor);
		}	
		else
		{
			if(listbox->Style == POPUP_STYLE_BBS)
				text = HiiGetString( listbox->ListHandle, listbox->PtrItems[Index].ItemToken );
			else
				text = HiiGetString( listbox->ListHandle, listbox->PtrTokens[Index] );
			
			
			if(listbox->Style == POPUP_STYLE_BBS)
			{
				if (listbox->PtrItems[Index].ItemToken)
				{

					//if(!text)
					//	text = EfiLibAllocateZeroPool(2);
					if((TestPrintLength( text) / (NG_SIZE)) > (UINTN) (listbox->Width - BorderWidth) )
						text[HiiFindStrPrintBoundary(text ,listbox->Width - BorderWidth)] = L'\0';
				
					// check conditional ptr if necessary
					if( listbox->PtrItems[Index].Attribute == AMI_POSTMENU_ATTRIB_NON_FOCUS)
						FGColor = EFI_LIGHTGRAY;
					else
						FGColor = listbox->FGColor ;
				
					DrawStringWithAttribute( listbox->Left + 2, listbox->Top + Index - listbox->FirstVisibleSel + 1, 
						text, listbox->BGColor | FGColor /*popupmenu->FGColor*/ );
				}else
					ListBoxDrawSeperator( listbox, listbox->Left , listbox->Top + Index - listbox->FirstVisibleSel + 1, 
						listbox->UseScrollbar?(listbox->Width-2):listbox->Width, 1);

			}			
			else
			{

				if(!text)
					text = EfiLibAllocateZeroPool(2);
				if((TestPrintLength( text) / (NG_SIZE)) > (UINTN) (listbox->Width - BorderWidth) )
					text[HiiFindStrPrintBoundary(text ,listbox->Width - BorderWidth)] = L'\0';
				DrawStringWithAttribute( listbox->Left + 2, listbox->Top + Index - listbox->FirstVisibleSel + 1, 
					text, listbox->BGColor | listbox->FGColor );
			}
		}
		MemFreePointer( (VOID **)&text );
	}

	FlushLines( listbox->Top-2, listbox->Top+listbox->Height/*PtrTokens[0]*/ + 1+2);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxHandleAction
//
// Description:	Function to handle the List Box actions.
//
// Input:	LISTBOX_DATA *listbox, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxHandleAction( LISTBOX_DATA *listbox, ACTION_DATA *Data)
{
	EFI_STATUS Status=EFI_SUCCESS; 
	ACTION_DATA TempData;
	UINT16	i, start, end ;
	VOID	*ScreenBuf = NULL;				

	if(Data->Input.Type == ACTION_TYPE_TIMER)
		Status = EFI_UNSUPPORTED;

    if(Data->Input.Type == ACTION_TYPE_MOUSE)
    {
		Status = MouseListBoxHandleAction( listbox, Data);
    }

	if(Data->Input.Type == ACTION_TYPE_KEY)
	{
        CONTROL_ACTION Action;

		ScrollBarMoveAction = FALSE; //EIP-67049

        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);

        switch(Action)
        {
            //EIP-42124: Add Page up and Page down key in List box
            case ControlActionPageUp:
                if(listbox->Style == POPUP_STYLE_NORMAL)
                {
                    if (listbox->Sel < (listbox->Height-3))
                        listbox->Sel = 0;
                    else
                        listbox->Sel= listbox->Sel - (listbox->Height-3);
                }
                break;
            case ControlActionPageDown:
                if(listbox->Style == POPUP_STYLE_NORMAL)
                {
                    if ((listbox->Sel+(listbox->Height-3)) > (listbox->ItemCount-1))
                        listbox->Sel = (listbox->ItemCount-1);
                    else
                        listbox->Sel= listbox->Sel + (listbox->Height-3);
                }
                break;
            case ControlActionNextUp:
    		if ( listbox->Sel > 0 )
			{
				listbox->Sel--;
			
				if(listbox->Style == POPUP_STYLE_BBS)		
				{
				   					
				    if ( (listbox->PtrItems[listbox->Sel].ItemToken==0) || (listbox->PtrItems[listbox->Sel].Attribute == AMI_POSTMENU_ATTRIB_NON_FOCUS))
				    {	
						//Send Fake Action...
						MemCopy(&TempData,Data,sizeof(ACTION_DATA));
						TempData.Input.Data.AmiKey.Key.ScanCode = SCAN_UP;
						TempData.Input.Data.AmiKey.Key.UnicodeChar = CHAR_NULL ;
						gListBox.HandleAction(listbox, &TempData);
				    }
				}
			}
			else
			{
				if(listbox->Style == POPUP_STYLE_BBS)
				{
					//Rollover, find the first focusable item
					for ( i = listbox->ItemCount-1; i > -1 ; i-- )
					{
						if((listbox->PtrItems[i].Attribute != AMI_POSTMENU_ATTRIB_NON_FOCUS)&&
					(listbox->PtrItems[i].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY)&&
						   (listbox->PtrItems[i].Attribute != AMI_POSTMENU_ATTRIB_HIDDEN)) 
						{
						 	listbox->Sel=i;
							break;
						}
					}
				}
				else
					listbox->Sel = listbox->ItemCount - 1;
			}
            break;

            case ControlActionNextDown:
    		if ( (INTN)(listbox->Sel) < listbox->ItemCount-listbox->HiddenItemCount - 1 )
			{
		    	listbox->Sel++;
		    
   		    	if(listbox->Style == POPUP_STYLE_BBS)	 
  		    	{
								
					if ( (listbox->PtrItems[listbox->Sel].ItemToken==0) || (listbox->PtrItems[listbox->Sel].Attribute == AMI_POSTMENU_ATTRIB_NON_FOCUS))
					{
						//Send Fake Action...
						MemCopy(&TempData,Data,sizeof(ACTION_DATA));
						TempData.Input.Data.AmiKey.Key.ScanCode = SCAN_DOWN;
						TempData.Input.Data.AmiKey.Key.UnicodeChar = CHAR_NULL ;
						gListBox.HandleAction(listbox, &TempData);
					}
		    	}
		
			}
			else
			{	//Rollover, find the first focusable item
				listbox->Sel=0;
				if(listbox->Style == POPUP_STYLE_BBS)	
				{
					for ( i = 0; i < listbox->ItemCount; i++ )
					{
						if((listbox->PtrItems[i].Attribute != AMI_POSTMENU_ATTRIB_NON_FOCUS)&&
						(listbox->PtrItems[i].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY)&&
					   		(listbox->PtrItems[i].Attribute != AMI_POSTMENU_ATTRIB_HIDDEN)) 
						{
					 		listbox->Sel=i;
							break;
						}
					}
				}

			}
            break;

        	case ControlActionAbort:
//EIP:47962 - Start
//				ScreenBuf = SaveScreen();	
				listbox->Callback( listbox->Container, listbox, NULL );
//				RestoreScreen( ScreenBuf );	
//EIP:47962 - End 
			break;

	    	case ControlActionSelect:
//EIP:47962 - Start			
//				ScreenBuf = SaveScreen();
		  		listbox->Callback( listbox->Container, listbox, &(listbox->Sel) );
//				RestoreScreen( ScreenBuf );
//EIP:47962 - End
			break;

	    	default:
			if(listbox->Style == POPUP_STYLE_BBS)	 
	  		{		
				//Start from current selection
				start = listbox->Sel ;
				end = listbox->ItemCount ;
				
				Search:
				for ( i = start; i < end; i++ )
				{
					if(	(listbox->PtrItems[i].Attribute != AMI_POSTMENU_ATTRIB_NON_FOCUS)&&
						(listbox->PtrItems[i].Attribute != AMI_POSTMENU_ATTRIB_EXIT_KEY))
					{
						
						
//EIP:48316 - Start 
						if( (listbox->PtrItems[i].Key.Key.ScanCode != 0) 	||
							(listbox->PtrItems[i].Key.Key.UnicodeChar != 0) ||
							(listbox->PtrItems[i].Key.KeyShiftState != 0) )
						{						
//EIP:48316 - End
							if( (listbox->PtrItems[i].Key.Key.ScanCode == Data->Input.Data.AmiKey.Key.ScanCode) &&
								 (listbox->PtrItems[i].Key.Key.UnicodeChar == Data->Input.Data.AmiKey.Key.UnicodeChar) &&
								 TseCheckShiftState((Data->Input.Data.AmiKey), listbox->PtrItems[i].Key.KeyShiftState) )
							{
															
								if(listbox->PtrItems[i].Attribute == AMI_POSTMENU_ATTRIB_HIDDEN)
								{
									listbox->Callback( listbox->Container, listbox, &i );
								}
								else
								{
									listbox->Sel = i ;
									listbox->Callback( listbox->Container, listbox, &(listbox->Sel) );
								}	
								
								//Send Fake Action...
								/*
								MemCopy(&TempData,Data,sizeof(ACTION_DATA));
								TempData.Input.Data.AmiKey.Key.ScanCode = 0;
								TempData.Input.Data.AmiKey.Key.UnicodeChar = CHAR_CARRIAGE_RETURN;
								gListBox.HandleAction(listbox, &TempData);
								*/
	
								break;
							}
						}
					}
				}
				
				//Wrap and Search remaining items for match
				if(i==listbox->ItemCount && (start != 0))
				{
					start = 0 ;
					end = listbox->Sel ;
					goto Search ;	
				}
			}
        }
    }

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxSetCallback
//
// Description:	Function to set callback.
//
// Input:		LISTBOX_DATA *listbox, OBJECT_DATA *container,   OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxSetCallback( LISTBOX_DATA *listbox, OBJECT_DATA *container,   OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( listbox, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxSetFocus
//
// Description:	Function to set focus.
//
// Input:		LISTBOX_DATA *listbox, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxSetFocus(LISTBOX_DATA *listbox, BOOLEAN focus)
{
	listbox->ControlFocus =focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxSetPosition
//
// Description:	Function to set position.
//
// Input:		LISTBOX_DATA *listbox, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxSetPosition(LISTBOX_DATA *listbox, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( listbox, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		LISTBOX_DATA *listbox, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxSetDimensions(LISTBOX_DATA *listbox, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( listbox, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		LISTBOX_DATA *listbox, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxSetAttributes(LISTBOX_DATA *listbox, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( listbox, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseListBoxHandleAction
//
// Description:	Function to hadnle List Box using mouse
//
// Input:		LISTBOX_DATA *listbox, 
//				ACTION_DATA *action,
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEMouseListBoxHandleAction( LISTBOX_DATA *listbox, ACTION_DATA *Data)
{
	UINT16	i;	
	UINT32 Action;
	
	Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);
	//Exit listbox if clicked outside listbox
	//EIP 103449  : In Setup click\Touch from navigation window, option are not displayed properly
	if( (
        (Data->Input.Data.MouseInfo.Top < listbox->Top) ||
        (Data->Input.Data.MouseInfo.Top > (UINT32)(listbox->Top + listbox->Height)) ||
        (Data->Input.Data.MouseInfo.Left < listbox->Left) ||
        (Data->Input.Data.MouseInfo.Left > (UINT32)(listbox->Left + listbox->Width))
		 ) && (!lButtonOnListBoxScroll) // Check for lButtonDown on ScrollBar
		 && ( (SingleClickActivation() && (ControlActionSelect ==Action)) || //If singleClickActivation is enabled/Disable
		 	  (ControlActionAbort == Action) || (ControlActionChoose ==Action ) //EIP-139608 Closing listbox whn mouse action happens outside listbox.
		 	)
	    )
	{
        listbox->Callback( listbox->Container, listbox, NULL );
	}
	//Reset lbutton positions
	if (ControlMouseActionLeftUp == Action
		|| ControlActionChoose == Action
		|| ControlActionSelect == Action)
	{
		lButtonOnListBoxScroll = FALSE;
		lButtonInitialPosition = 0;
		lButtonVaryingPosition = 0;
	}
	//If scrollbar present
	if ( listbox->UseScrollbar )
	{
		//Check if clicked on scroll bar area
		if( ( Data->Input.Data.MouseInfo.Top > (UINT32)listbox->Top && (Data->Input.Data.MouseInfo.Top < (UINT32)(listbox->Top + listbox->Height)) ) //Clicked inside listbox area
			&& (Data->Input.Data.MouseInfo.Left == (UINT32)(listbox->Left + listbox->Width - 2)) //Clicked on scrollbar area
			)
		{
			//If clicked on UP_ARROW
			if(((Data->Input.Data.MouseInfo.Top == (UINT32)(listbox->Top + 1)) &&(Data->Input.Data.MouseInfo.Left == (UINT32) (listbox->Left + listbox->Width -2))) //Clicked on UP_ARROW
				 &&((TSEMOUSE_LEFT_CLICK == Data->Input.Data.MouseInfo.ButtonStatus)||(TSEMOUSE_LEFT_DCLICK == Data->Input.Data.MouseInfo.ButtonStatus))//EIP 78929  : Check for left click and left double click to scroll the frame if click on arrow buttons of scroll bar.
				)
			{
				ScrollBarMoveAction = TRUE;
				MouseListBoxScrollBarMove( listbox, TRUE, 1 );
				return EFI_SUCCESS;//EIP 78929  : Returning by consuming the click when the clicked on the arrow buttons of scroll bar 
			}
			//If clicked on DOWN_ARROW
			else if(((Data->Input.Data.MouseInfo.Top == (UINT32) (listbox->Top + listbox->Height-2)) &&(Data->Input.Data.MouseInfo.Left == (UINT32) (listbox->Left + listbox->Width-2))) //Clicked on DOWN_ARROW
						&&((TSEMOUSE_LEFT_CLICK == Data->Input.Data.MouseInfo.ButtonStatus)||(TSEMOUSE_LEFT_DCLICK == Data->Input.Data.MouseInfo.ButtonStatus))//EIP 78929  : Check for left click and left double click to scroll the frame if click on arrow buttons of scroll bar.
					)
			{
				ScrollBarMoveAction = TRUE;
				MouseListBoxScrollBarMove( listbox, FALSE, 1 );
				return EFI_SUCCESS;//EIP 78929  : Returning by consuming the click when the clicked on the arrow buttons of scroll bar 
			}
			//If clicked on scrollbar
			else if( ((Data->Input.Data.MouseInfo.Top < gListBoxScrollBarBottom) && (Data->Input.Data.MouseInfo.Top > gListBoxScrollBarTop)) //Scrollbar area
						&& (ControlMouseActionLeftDown == Action) //Mouse lbutton down
						&&	((ControlActionChoose != Action) || (ControlActionSelect != Action)) //Neglecting LEFT_DCLICK and LEFT_CLICK on scrollbar area
					)
			{
				lButtonOnListBoxScroll = TRUE;
				ScrollBarMoveAction = TRUE;
				if ( lButtonInitialPosition == 0 )//To get initial lButtonDown position
				{
					lButtonInitialPosition = Data->Input.Data.MouseInfo.Top;
				}
				if ( lButtonInitialPosition != Data->Input.Data.MouseInfo.Top )
				{
					lButtonVaryingPosition = Data->Input.Data.MouseInfo.Top;
					//Move scrollbar upwards
					if( lButtonInitialPosition > lButtonVaryingPosition )
						MouseListBoxScrollBarMove( listbox, TRUE, lButtonInitialPosition - lButtonVaryingPosition );

					//Move scrollbar downwards
					else
						MouseListBoxScrollBarMove( listbox, FALSE, lButtonVaryingPosition - lButtonInitialPosition );
					lButtonInitialPosition = lButtonVaryingPosition;
				}
				return EFI_SUCCESS;
			}
			//If mouse clicked above DOWN_ARROW and below ScrollBar
			else if( (Data->Input.Data.MouseInfo.Top < (UINT32) (listbox->Top + listbox->Height-3)) //Clicked above DOWN_ARROW
						&& (Data->Input.Data.MouseInfo.Top >= gListBoxScrollBarBottom)  //Clicked below ScrollBar							
						&& (ControlMouseActionLeftDown == Action) //Action is LEFT_DOWN
					)
			{
				ScrollBarMoveAction = TRUE;
				MouseListBoxScrollBarMove( listbox, FALSE, Data->Input.Data.MouseInfo.Top - gListBoxScrollBarBottom );
				return EFI_SUCCESS;
			}
			//If mouse clicked below UP_ARROW and above ScrollBar
			else if( (Data->Input.Data.MouseInfo.Top > (UINT32)(listbox->Top + 1)) //Clicked below UP_ARROW
						&& (Data->Input.Data.MouseInfo.Top <= gListBoxScrollBarTop) //Clicked above ScrollBar
						&& (ControlMouseActionLeftDown == Action) //Action is LEFT_DOWN
					)
			{
				ScrollBarMoveAction = TRUE;
				MouseListBoxScrollBarMove( listbox, TRUE, gListBoxScrollBarTop - Data->Input.Data.MouseInfo.Top);
				return EFI_SUCCESS;
			}
			return EFI_SUCCESS;
		}
		//If mouse button clicked on scrollbar and moved outside the scroll area
		else if( ControlMouseActionLeftDown == Action //Action is LEFT_DOWN
					&& (lButtonInitialPosition != 0)
					&& ((ControlActionChoose != Action) || (ControlActionSelect != Action)) //Neglecting LEFT_CLICK and LEFT_DCLICK
				)
		{
			lButtonVaryingPosition = Data->Input.Data.MouseInfo.Top;
			//Move scrollbar upwards
			if( lButtonInitialPosition > lButtonVaryingPosition )
				MouseListBoxScrollBarMove( listbox, TRUE, lButtonInitialPosition - lButtonVaryingPosition );

			//Move scrollbar downwards
			else
				MouseListBoxScrollBarMove( listbox, FALSE, lButtonVaryingPosition - lButtonInitialPosition );
			lButtonInitialPosition = lButtonVaryingPosition;
			
			//Reset lButtonDown position when lButton releases
			if (ControlMouseActionLeftUp == Action)
			{
				lButtonInitialPosition = lButtonVaryingPosition = 0;
			}
			return EFI_SUCCESS;
		}
	}
	//If clicked Inside listbox area other than scroll area to handle highlight or selection of the option
	if( ( Data->Input.Data.MouseInfo.Top > (UINT32)listbox->Top && (Data->Input.Data.MouseInfo.Top < (UINT32)(listbox->Top + listbox->Height)) ) //Clicked inside ListBox area
		&& ( (Data->Input.Data.MouseInfo.Left > listbox->Left)  && (Data->Input.Data.MouseInfo.Left < (listbox->Left + (UINT32)(listbox->Width - 2))) ) //Width calculation			
		&& (ControlActionChoose == Action || ControlActionSelect == Action) //check LEFT_DCLICK or LEFT_CLICK
		)
	{		
		for (i = listbox->FirstVisibleSel; i <= listbox->LastVisibleSel; i++ )
		{
			if(Data->Input.Data.MouseInfo.Top == (UINT32) (listbox->Top + i - listbox->FirstVisibleSel + 1))
			{
				switch( MapControlMouseActionHook(&Data->Input.Data.MouseInfo) )
				{
					case ControlActionChoose:
						listbox->Sel=i;
					break;

					case ControlActionSelect:
						if (SingleClickActivation ())		//EIP74141 providing select option for single click too
						{
							listbox->Sel=i;
						}
						listbox->Callback( listbox->Container, listbox, &(listbox->Sel) );
					break;
				}
			}
		}
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ListBoxGetControlHight
//
// Description:	Function unsupported.
//
// Input:		VOID *object,VOID *frame, UINT16 *height
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ListBoxGetControlHight( VOID *object,VOID *frame, UINT16 *height )
{
	return EFI_UNSUPPORTED;
}

//EIP-67049 Start
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    TSEMouseListBoxScrollBarMove
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

EFI_STATUS TSEMouseListBoxScrollBarMove(  LISTBOX_DATA *listbox, BOOLEAN bScrollUp, UINT16 Size )
{	
	if ( listbox->ItemCount == 0 )
		return EFI_UNSUPPORTED;

	switch ( bScrollUp )
	{
		case TRUE:

			if( Size >= listbox->FirstVisibleSel )
				Size = listbox->FirstVisibleSel;

			//If FirstVisibleCtrl is not equal to first control then move scrollbar till it reaches top
			if(listbox->FirstVisibleSel > 0)
			{
				listbox->FirstVisibleSel = listbox->FirstVisibleSel - Size;
				listbox->LastVisibleSel = listbox->LastVisibleSel - Size;
			}
			break;

		case FALSE:
			//If the size of scroll to move exceeds the remaining control count then change the size value based on the remaining control count
			if( Size >= (listbox->ItemCount - listbox->LastVisibleSel) )
				Size = listbox->ItemCount - listbox->LastVisibleSel - 1;

			//If LastVisibleCtrl is not equal to last control then move scrollbar till it reaches bottom
			if(listbox->LastVisibleSel < listbox->ItemCount - 1)
			{
				listbox->FirstVisibleSel = listbox->FirstVisibleSel + Size;
				listbox->LastVisibleSel = listbox->LastVisibleSel + Size;
			}
			break;
	}
	return EFI_SUCCESS;
}
//EIP-67049 End

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
