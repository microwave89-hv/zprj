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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/MessageBox.c $
//
// $Author: Premkumara $
//
// $Revision: 31 $
//
// $Date: 8/28/14 8:02a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/MessageBox.c $
// 
// 31    8/28/14 8:02a Premkumara
// [TAG]		EIP107833, 125388
// [Category]	Improvement
// [Symptom:]	Setting best text and GOP mode while using TSEPostinterfaces
// before TSE or after TSE.
// [Files]		Protocol.c, AMITSE.sdl, CommonHelper.c, MiniSetup.sdl,
// PostMgmtc, PostmgmtExt.c, MessagBox.c
// 
// 30    5/03/14 3:13p Premkumara
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
// 29    5/02/14 3:51a Arunsb
// [TAG]	EIP155965
// [Category]	Improvement
// [Description]	MessageBox, ListBox cannot be canceled by Mouse
// Right-Click
// [Files]	MessageBox.c, ListBox.c and minisetupext.c
// 
// 28    2/11/14 8:35p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 27    12/05/13 1:29a Premkumara
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
// 26    5/22/13 10:59a Premkumara
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
// 25    1/22/13 12:20a Rajashakerg
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
// 24    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 22    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 23    5/24/12 9:02a Arunsb
// [TAG]  		EIP90379
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	UefiBootFailHook asserts when it is trying to call
// MsgBoxDestroy
// [RootCause]  	Tried to free the NULL pointer
// [Solution]  	Checked NULL before freeing
// [Files]  		TseAdvanced.c and MessageBox.c
// 
// 22    5/24/12 7:31a Rajashakerg
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
// 21    2/02/12 1:17p Premkumara
// [TAG]  		EIP75351,75352,75384
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		String.c, boot.c, TseAdvanced.c,Time.c, PopupEdit.c,
// MessageBox.c, Label.c, Edit.c, Date.c
// 
// 20    12/01/11 5:43a Rajashakerg
// [TAG]  		EIP74963 
// [Category]  	Improvement
// [Description]  	MAX_MSGBOX_WIDTH cannot be overridden
// [Files]  		AMITSE.sdl, CommonHelper.c, minisetup.h, legacy.c,
// MessageBox.c, MessageBox.h, FormBrowser.c
// 
// 19    12/01/11 1:42a Premkumara
// [TAG]  		EIP73236
// [Category]  	Improvement
// [Description]  	Large amounts of allocated memory are not freed
// [Files]  		Expression.c, PopupEdit.c, Popup.c, MessageBox.c, Menu.c,
// Memo.c, 
// 
// 18    11/30/11 12:42a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 17    11/20/11 7:50a Rajashakerg
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
// 16    11/10/11 8:30a Rajashakerg
// [TAG]  		EIP74965 
// [Category]  	Improvement
// [Description]  	Progress bar in MSGBOX_TYPE_PROGRESS never displays the
// full 100%
// [Files]  		MessageBox.c
// 
// 15    12/28/10 9:06a Mallikarjunanv
// Removing the changes of EIP:48381 which are not required. 
// 
// 14    12/24/10 12:50p Mallikarjunanv
// 
// 13    12/24/10 12:48p Mallikarjunanv
// [TAG]  		EIP 46143
// [Category]  	Bug Fix
// [Severity]- Medium
// [Symptom]- In Boot tab, "Add boot option" -> "Add boot option" option,
//  adding string displayed "invalid string" message , on clicking OK in
//  the message box using mouse not closing msg box. 
// [RootCause]  	In case of message box selection with mouse the
//  coordinates are improper.
// [Solution]  	Message box coordinates are updated with respect to
//  selection with mouse.
// [Files]  		MessageBox.c
// 
// 12    12/24/10 10:49a Mallikarjunanv
// [TAG]  		EIP48381  
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Mouse click operation not working properly in the warning
// [RootCause]  	In TSEMouseMsgBoxHandleAction function coordinates for
// mouse click are improper 
// [Solution]  	Fixed the issue by updating the coordinates for mouse
// click
// operation
// [Files]  		MessageBox.c
// 
// 11    10/20/10 1:42p Mallikarjunanv
// reverting back to v25
// 
// 9     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 16    7/07/10 7:37p Madhans
// To avoid Warning.
// 
// 15    5/19/10 4:13p Blaines
// Added length boundry check for legend string
// 
// 14    4/22/10 6:23p Blaines
// Adjust Messagebox width if required to display legend string. 
// 
// 13    4/20/10 7:02p Blaines
// Add mouse support for custom messagebox type 
// 
// 12    4/20/10 6:20p Blaines
// Support custom messagebox type in MsgBoxHandleAction 
// 
// 11    4/09/10 12:26p Madhans
// To freeup the strings
// 
// 10    3/26/10 6:53p Madhans
// Support to Map the do the Control Mapping from gTseControlMap Table. So
// no changes need in Frame.c, With this feature gTseControlMap Can be
// customized to add/customize the TSE controls.
// 
// 9     3/24/10 12:00p Blaines
// Message box color can be configured based on message box type
// (help, error, etc)
// 
// This change corrects the selected button FG/BG color.
// 
// 8     3/23/10 5:20p Blaines
// Extend Message Box support
//     Adds Custom Type
//     Adds Progress Bar Type
// 
// 7     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 6     2/15/10 10:13p Madhans
// To avoid warnings
// 
// 5     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 4     1/09/10 6:39a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
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
// Name:		MessageBox.c
//
// Description:	This file contains code to handle Message Box operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


MSGBOX_METHODS gMsgBox =
{
	MsgBoxCreate,
	MsgBoxDestroy,
	MsgBoxInitialize,
	MsgBoxDraw,
	MsgBoxHandleAction,
	MsgBoxSetCallback,
	MsgBoxSetFocus,
	MsgBoxSetPosition,
	MsgBoxSetDimensions,
	MsgBoxSetAttributes,
	MsgBoxGetControlHight,
	MsgBoxSetType
};

/////////////////////////////////////////////////
/////	Extern variables and functions
/////////////////////////////////////////////////
void ClearGrphxScreen (void);
BOOLEAN SingleClickActivation (VOID); //EIP-139608 

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxCreate
//
// Description:	Function to Create Message Box, which uses the Popup functions.
//
// Input:	MSGBOX_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxCreate( MSGBOX_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(MSGBOX_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gPopup.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gMsgBox;

	// create the memo 
	gMemo.Create(&((*object)->Memo));

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxDestroy
//
// Description:	Function to Destroy Message Box, which uses the Popup functions.
//
// Input:	MSGBOX_DATA *msgbox, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxDestroy( MSGBOX_DATA *msgbox, BOOLEAN freeMem )
{
	EFI_STATUS Status;

	if(NULL == msgbox)
	  return EFI_SUCCESS;
	
	Status = gPopup.Destroy( msgbox, FALSE );
	MemFreePointer( (VOID **)&(msgbox->Memo->ControlData.ControlPtr) );
	Status = gMemo.Destroy( msgbox->Memo, FALSE );

	if(msgbox->Title)
		MemFreePointer( (VOID **)&msgbox->Title );

	//Restore saved screen only inside TSE
	if (TSE_POST_STATUS_IN_TSE == gPostStatus)
	{
		if (msgbox->ScreenBuf) //Restore If it has valid data
			RestoreScreen( msgbox->ScreenBuf );
	}

	if (freeMem)
	{
		if (NULL != msgbox->Legend)			//EIP 90379
		{
			MemFreePointer ((VOID **)&msgbox->Legend);//EIP-73236
		}
		if (NULL != msgbox->PtrTokens)
		{	
			MemFreePointer ((VOID **)&msgbox->PtrTokens);
		}
	//        MemFreePointer( (VOID **)&msgbox->HotKeyList );
	//        MemFreePointer( (VOID **)&msgbox->OutKey );
		MemFreePointer( (VOID **)&msgbox );
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxInitialize
//
// Description:	Function to Initialize Message Box, which uses the Popup functions.
//
// Input:	MSGBOX_DATA *msgbox, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxInitialize( MSGBOX_DATA *msgbox, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 Length =0 ;
	VOID *buff;
	CONTROL_INFO MemoCtrlData;
	MEMO_DATA *memo;
	UINT8 Color ;

	UINT16 titleToken;
    VOID* TextHandle =((AMI_IFR_MSGBOX*)(((CONTROL_INFO*)data)->ControlPtr))->TextHandle;

	// initializes the heigth and width
	Status = gPopup.Initialize( msgbox, data );
	if (EFI_ERROR(Status))
		return Status;

	Status = StyleGetMessageboxColor(msgbox->MsgBoxCatagory, &Color) ; 
	
	if ( EFI_ERROR( Status ) == EFI_SUCCESS)
	{
		msgbox->FGColor = Color & 0x0f ; 
		msgbox->BGColor = Color & 0xf0 ; 
	}else
	// add extra initialization here...
	SetControlColorsHook( NULL, NULL, NULL , NULL, NULL , NULL, NULL ,
	                      NULL , NULL,  NULL,NULL ,
						  NULL,NULL ,&(msgbox->FGColor),&(msgbox->BGColor)  );


	msgbox->Container = NULL;
	
	msgbox->Border =TRUE;

	titleToken = (UINT16)(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Title);
	if ( titleToken != 0 ) {
		msgbox->Title = HiiGetString(msgbox->ControlData.ControlHandle, titleToken);
		//EIP-75351 Suppress the warnings from static code analyzer
		if(NULL == msgbox->Title){
			msgbox->Title = EfiLibAllocateZeroPool(2*sizeof(CHAR16));
			if(!msgbox->Title)
				return EFI_OUT_OF_RESOURCES;
			EfiStrCpy(msgbox->Title,L" ");
		}
	}

	Length = (UINT16)HiiMyGetMultiLineStringLength(msgbox->ControlData.ControlHandle, (UINT16)(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Text));

	if ( ( msgbox->Title != NULL) && ( Length < (TestPrintLength( msgbox->Title )/ (NG_SIZE)) ) )
		Length = (UINT16)(TestPrintLength( msgbox->Title ) / (NG_SIZE));

	msgbox->Width = (UINT16)(Length + 4);

	if(( msgbox->MsgBoxType == MSGBOX_TYPE_NULL ) && ( msgbox->Legend != NULL ))
	{ 
		if ( msgbox->Width < (UINT16)(TestPrintLength( msgbox->Legend )/ (NG_SIZE)) )
			msgbox->Width = (UINT16)(TestPrintLength( msgbox->Legend ) / (NG_SIZE)) + 8;
	}	
//EIP74963 : MAX_MSGBOX_WIDTH macro changed as token and handled from binary
	if ( msgbox->Width > GetMsgboxWidth())
		msgbox->Width = GetMsgboxWidth();

	//Save the screen only insied TSE not for PostInterfaces outside TSE
	if (TSE_POST_STATUS_IN_TSE == gPostStatus)
		msgbox->ScreenBuf = SaveScreen();

	//Clear screen before displaying msgbox when PROCEED_TO_BOOT not inside TSE
	if (TSE_POST_STATUS_PROCEED_TO_BOOT == gPostStatus)
	{
		ClearGrphxScreen(); //Clearing full screen when image is drawn in quietBoot mode
		ClearScreen(EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY);
	}

	// initialize memo control 
	memo = msgbox->Memo;

	buff = UefiCreateSubTitleTemplate(((AMI_IFR_MSGBOX*)(msgbox->ControlData.ControlPtr))->Text );

	
	MemSet( &MemoCtrlData, sizeof(MemoCtrlData), 0 );
	MemoCtrlData.ControlPtr = (VOID*)buff;
	MemoCtrlData.ControlHandle = TextHandle;
	MemoCtrlData.ControlFlags.ControlVisible = TRUE;
	gMemo.Initialize(memo,(VOID *)&(MemoCtrlData));
	memo->Width = msgbox->Width - 2;
	gMemo.GetControlHeight( memo, NULL, &msgbox->Height );
	msgbox->Height += 4;

	gMemo.SetAttributes(memo,msgbox->FGColor ,msgbox->BGColor);
	gMemo.SetDimensions( memo, msgbox->Width-2 , msgbox->Height-3 );
	gMemo.SetJustify( memo, JUSTIFY_CENTER );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_MsgBoxOptSize
//
// Description:	Function returns and fix the option string
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _MsgBoxOptSize(CHAR16 *txt)
{
	UINTN Size = (TestPrintLength( txt ) / (NG_SIZE));
	if( Size > 10)
	{
		txt[HiiFindStrPrintBoundary(txt,10)] = L'\0';
		Size = (TestPrintLength( txt ) / (NG_SIZE)); // Need to do this. instead of assigning 10;
	}
	return Size;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_MsgBoxDrawOpts
//
// Description:	Function to Draw Message box options
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _MsgBoxDrawOpts(MSGBOX_DATA *msgbox)
{
	UINT16 Index, W;
	CHAR16 Line[MAX_COLS] ,*txt;
	UINTN printLength, pos ;

	if ( msgbox->MsgBoxType != MSGBOX_TYPE_NULL )
	{ 
		for ( Index = 1; Index < msgbox->Width -1 ; Index++ )
			Line[Index] = BOXDRAW_HORIZONTAL;

		Line[0] = BOXDRAW_VERTICAL_RIGHT;
		Line[Index] = BOXDRAW_VERTICAL_LEFT;
		Line[Index+1] = 0x0;

		DrawString( msgbox->Left, msgbox->Top + msgbox->Height - 3, Line );

		// draw the buttons
		switch ( msgbox->MsgBoxType & MSGBOX_TYPE_MASK )
		{

			case MSGBOX_TYPE_YESNO:
				txt =  HiiGetString( msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_YES));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}

				msgbox->Button1Len = (UINT8)_MsgBoxOptSize(txt );
				DrawStringWithAttribute((UINTN) (msgbox->Left + msgbox->Width/3 -2) , (UINTN)(msgbox->Top + msgbox->Height -2), txt, (UINT8) (((msgbox->MsgboxSel==0)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
				MemFreePointer( (VOID **)&txt);

				txt =  HiiGetString( msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_NO));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}

				msgbox->Button2Len = (UINT8)_MsgBoxOptSize(txt );

				DrawStringWithAttribute((UINTN)( msgbox->Left + 2*(msgbox->Width/3) -2) ,(UINTN)(msgbox->Top + msgbox->Height -2), txt, (UINT8) (((msgbox->MsgboxSel==1)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
				MemFreePointer( (VOID **)&txt);

				break;
			case MSGBOX_TYPE_OKCANCEL:
				txt =  HiiGetString( msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_OK));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}
				msgbox->Button1Len = (UINT8)_MsgBoxOptSize(txt );
				DrawStringWithAttribute((UINTN) (msgbox->Left + msgbox->Width/3 -2) , (UINTN)(msgbox->Top + msgbox->Height -2), txt, (UINT8) (((msgbox->MsgboxSel==0)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
				MemFreePointer( (VOID **)&txt);

				txt =  HiiGetString( msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_CANCEL));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}
				msgbox->Button2Len = (UINT8)_MsgBoxOptSize(txt );
				DrawStringWithAttribute((UINTN)( msgbox->Left + 2*(msgbox->Width/3) -2) ,(UINTN)(msgbox->Top + msgbox->Height -2), txt, (UINT8) (((msgbox->MsgboxSel==1)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
				MemFreePointer( (VOID **)&txt);
				break;
			
			case MSGBOX_TYPE_CUSTOM:

				if ( (msgbox->OptionCount != 0) && (msgbox->PtrTokens != NULL ))
				{ 
					W = ( msgbox->Width)/(msgbox->OptionCount) ;


					for ( Index = 0; Index < msgbox->OptionCount ; Index++ )
					{
						txt =  HiiGetString( msgbox->ControlData.ControlHandle, msgbox->PtrTokens[Index]);
						//EIP-75351 Suppress the warnings from static code analyzer
						if (NULL == txt){
							break;
						}
						pos = (UINTN) (msgbox->Left + (Index * W) ) ;

						printLength = (TestPrintLength( txt ) / (NG_SIZE));
				
						if( printLength > W)
						{
							txt[HiiFindStrPrintBoundary(txt, W)] = L'\0';
							printLength = (TestPrintLength( txt ) / (NG_SIZE));
						}
								
						DrawStringWithAttribute(pos + (W-printLength)/2 , (UINTN)(msgbox->Top + msgbox->Height -2 ), txt, (UINT8) (((msgbox->MsgboxSel==Index)? EFI_BACKGROUND_BLACK|EFI_WHITE : msgbox->BGColor|msgbox->FGColor)));
						MemFreePointer( (VOID **)&txt);
					}
				}

				break;
						
			case MSGBOX_TYPE_PROGRESS:
				//Draw the progress bar based on percent complete, for example

				//----------------------- Title ------------------------//
				//							//									
				// 	Message Body will be printerd here		//
				//							//
				//------------------------------------------------------//
				// ##################### 10% ####			// <--- This section is where to use DrawStringWithAttribute 
				//--------------------- Legend -------------------------//

				{
					CHAR16 Box[2] = {0};
					CHAR16 PercentStr[5] = {0};
					UINT16 Index = 0;
					UINT16 ChrIdx=msgbox->Left;
					UINT16 ProgPos=0;
					
					//symbol character to show during progress update
					Box[0] = (CHAR16)BLOCKELEMENT_FULL_BLOCK ; //L'#';
					Box[1] = (CHAR16)L'\0';
				

					//max percentage should be 100
					if( msgbox->Percent > 100) {
						msgbox->Percent = 100;
					}

					//percentage to update on the progress bar
					if( msgbox->Percent / 100)
					{
						PercentStr[Index++] = (CHAR16)(msgbox->Percent / 100) + L'0';
						PercentStr[Index++] = (CHAR16)((msgbox->Percent % 100) / 10) + L'0';

					}
					if( (msgbox->Percent % 100) / 10)
						PercentStr[Index++] = (CHAR16)((msgbox->Percent % 100) / 10) + L'0';

					PercentStr[Index++] =  (CHAR16)((msgbox->Percent % 100) % 10) + L'0';
					PercentStr[Index] = L'%';

					/// some sample logic to fill the progress bar symbol character properly without hard coded values...
					ProgPos = msgbox->Width - 2;
					while ( ProgPos < 100 )
					{
						if ( 100  % ProgPos != 0){
							if ( 99  % ProgPos != 0){
								if ( 98  % ProgPos != 0) {
									ProgPos--;
								}
								else
								break;//EIP74965 : Progress bar now can show the 100% status 
							}
							else
								break;
						}
						else
							break;
					}

					ProgPos = 100/ProgPos;
			

					//Fill progress bar for the given percentage
					for( Index = 0; Index < msgbox->Percent; Index++ ) {
						//fill the symbol character based on the segment value for the given percentage
						if( ( msgbox->Percent != 0 ) && ( Index % ProgPos == 0 ) && (ChrIdx < msgbox->Left+msgbox->Width-2) )
							DrawStringWithAttribute((UINTN) ++ChrIdx, (UINTN)(msgbox->Top + msgbox->Height - 2), Box, (UINT8) msgbox->BGColor|EFI_CYAN/*| msgbox->FGColor*/);
					}

					if( msgbox->Percent == 100 ) {
						//to fill the progress bar completely for the box width in case of 100 percentage.
						for( ; (ChrIdx - msgbox->Left) < (msgbox->Width - 2); )
							DrawStringWithAttribute((UINTN) ++ChrIdx, (UINTN)(msgbox->Top + msgbox->Height - 2), Box, (UINT8) msgbox->BGColor|EFI_CYAN/*| msgbox->FGColor*/);
					}

					//draw percentage string on the progress bar
					DrawStringWithAttribute( msgbox->Left + msgbox->Width / 2 -	EfiStrLen(PercentStr)/2, msgbox->Top + msgbox->Height - 3,PercentStr, (UINT8) /*msgbox->BGColor|EFI_RED */msgbox->BGColor | msgbox->FGColor);

					//Draw the given legend
					DrawStringWithAttribute( msgbox->Left + msgbox->Width / 2 -	EfiStrLen(msgbox->Legend)/2, msgbox->Top + msgbox->Height - 1,msgbox->Legend, (UINT8) msgbox->BGColor | msgbox->FGColor);
				}

				break;

			case MSGBOX_TYPE_OK:

			default:
				txt =  HiiGetString(msgbox->ControlData.ControlHandle, STRING_TOKEN(STR_CTRL_OK));
				//EIP-75351 Suppress the warnings from static code analyzer
				if (NULL == txt){
					break;
				}

				msgbox->Button1Len = (UINT8)_MsgBoxOptSize(txt );
				msgbox->Button2Len = 0;
				DrawStringWithAttribute( msgbox->Left + msgbox->Width/2  , msgbox->Top + msgbox->Height -2, txt, EFI_BACKGROUND_BLACK|EFI_WHITE );
				MemFreePointer( (VOID **)&txt);
				break;
		} 

		FlushLines( msgbox->Top + msgbox->Height -3, msgbox->Top + msgbox->Height);
	} 

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxDraw
//
// Description:	Function to Draw Message box
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxDraw( MSGBOX_DATA *msgbox )
{
	EFI_STATUS Status;
	CHAR16 *PadTitle = NULL, *Str = NULL;
	Str = msgbox->Legend ;

	MouseFreeze();

	Status = gPopup.Draw( msgbox );
	if(EFI_ERROR(Status))
		return Status;

	_MsgBoxDrawOpts(msgbox);

	// draw memo
	gMemo.SetPosition( msgbox->Memo, msgbox->Left + 1, msgbox->Top + 2 );
	gMemo.SetJustify( msgbox->Memo, (msgbox->MsgBoxType & MSGBOX_STYLE_MASK) >> 4 );
	gMemo.Draw( msgbox->Memo );

	

	if ((Str != NULL) && ( msgbox->MsgBoxType == MSGBOX_TYPE_NULL ) )
	{
		PadTitle = EfiLibAllocateZeroPool( (msgbox->Width + 3) * sizeof(CHAR16) );

		if( (UINT16)(TestPrintLength( Str ) / (NG_SIZE)) > (UINT16)(msgbox->Width-2))
				EfiStrCpy( &Str[HiiFindStrPrintBoundary(Str,(msgbox->Width-5))],L"...");

		if ( PadTitle != NULL )
			SPrint( PadTitle,  msgbox->Width * sizeof(CHAR16), L" %s ",Str );
	}

	if ( PadTitle )
	{
		DrawStringJustified( 0, gMaxCols, msgbox->Top+msgbox->Height-1, JUSTIFY_CENTER, PadTitle );
		//DrawStringJustified( msgbox->Left+1, msgbox->Left+msgbox->Width-1, msgbox->Top+msgbox->Height, JUSTIFY_CENTER, PadTitle );
		MemFreePointer((VOID **)&PadTitle);
	}

	FlushLines( msgbox->Top, msgbox->Top + msgbox->Height );
	DoRealFlushLines();

	MouseRefresh();

	return  EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_MsgBoxCallCallback
//
// Description:	Internal Helper Function to Call the callback
//
// Input:		MENU_DATA *menu, UINT8 MenuEntry
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _MsgBoxCallCallback(MSGBOX_DATA *msgbox,UINT8 MsgboxSel)
{
    if ( ( msgbox->Callback != NULL ) && (msgbox->Cookie != NULL) )
    {
	    CALLBACK_MESSAGEBOX *callbackData = (CALLBACK_MESSAGEBOX *)msgbox->Cookie;
	    callbackData->Result = MsgboxSel;
        msgbox->Callback( msgbox->Container, msgbox, msgbox->Cookie );
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxHandleAction
//
// Description:	Function to Handle the Message Box Actions.
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxHandleAction( MSGBOX_DATA *msgbox, ACTION_DATA *Data)
{
	EFI_STATUS Status;
	BOOLEAN Redraw = FALSE; 
	//Always return success to consume the message, the messagebox is always modal.
	if ( Data->Input.Type == ACTION_TYPE_TIMER )
		return EFI_UNSUPPORTED;

    if ( Data->Input.Type == ACTION_TYPE_MOUSE )
    {
		Status = MouseMsgBoxHandleAction( msgbox, Data,&Redraw);
    }

	if(Data->Input.Type == ACTION_TYPE_KEY)
	{
        CONTROL_ACTION Action;

        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);

		if( TsePrintScreenEventSupport(Data->Input.Data.AmiKey.Key.ScanCode))
		{
			gApplication.HandleAction( gApp, Data );
			return EFI_UNSUPPORTED;//EIP-123432
		}

        switch(Action)
        {
            case ControlActionSelect:
				// EIP 34545 : If MSGBOX_TYPE_NULL, nothing to select Only Esc can control
                if (msgbox->MsgBoxType == MSGBOX_TYPE_NULL)
                    break;
				_MsgBoxCallCallback(msgbox,msgbox->MsgboxSel);
            break;

            case ControlActionNextLeft:
		if( ( (msgbox->MsgBoxType & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_OK )&&
				( (msgbox->MsgBoxType & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_CUSTOM ))
    		{
    				if ( msgbox->MsgboxSel == 1 )
    					msgbox->MsgboxSel = 0;
    				
    		}
		else if((msgbox->MsgBoxType & MSGBOX_TYPE_MASK) == MSGBOX_TYPE_CUSTOM )
		{
    				if ( msgbox->MsgboxSel > 0 )
    					msgbox->MsgboxSel--;
    				
    		}
    
    		Redraw = TRUE;
            	break;
            
	   case ControlActionNextRight:
    		if( ( (msgbox->MsgBoxType & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_OK )&&
				( (msgbox->MsgBoxType & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_CUSTOM ))
   		{
   			if ( msgbox->MsgboxSel == 0 )
   				msgbox->MsgboxSel = 1;
   			
   		}
		else if((msgbox->MsgBoxType & MSGBOX_TYPE_MASK) == MSGBOX_TYPE_CUSTOM )
		{
    				if ( msgbox->MsgboxSel < msgbox->OptionCount-1 )
    					msgbox->MsgboxSel++;
    		}
    
   		Redraw = TRUE;
                break;

            case ControlActionAbort:
    			msgbox->MsgboxSel = MSGBOX_CANCEL;
    			_MsgBoxCallCallback(msgbox,msgbox->MsgboxSel);
    			gAction.ClearAction( Data );
            break;
        }
    }

	if ( Redraw == TRUE )
		gMsgBox.Draw( msgbox );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetCallback
//
// Description:	Function to set callback.
//
// Input:		MSGBOX_DATA *msgbox, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetCallback( MSGBOX_DATA *msgbox, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( msgbox, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetType
//
// Description:	Function to set message box type.
//
// Input:		MSGBOX_DATA *msgbox, UINT8 Type
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetType( MSGBOX_DATA *msgbox, UINT8 Type )
{
	msgbox->MsgBoxType = Type;
	if ( (Type & MSGBOX_TYPE_MASK) != MSGBOX_TYPE_NULL )
		msgbox->Height += 2;

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetFocus
//
// Description:	Function to set focus.
//
// Input:		MSGBOX_DATA *msgbox, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetFocus(MSGBOX_DATA *msgbox, BOOLEAN focus)
{
	msgbox->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetPosition
//
// Description:	Function to set position.
//
// Input:		MSGBOX_DATA *msgbox, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetPosition(MSGBOX_DATA *msgbox, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( msgbox, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetDimensions
//
// Description:	Function to set dimensions.
//
// Input:		MSGBOX_DATA *msgbox, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetDimensions(MSGBOX_DATA *msgbox, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( msgbox, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxSetAttributes
//
// Description:	Function to set attrinutes.
//
// Input:		MSGBOX_DATA *msgbox, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxSetAttributes(MSGBOX_DATA *msgbox, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( msgbox, FGColor, BGColor );
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseMsgBoxHandleAction
//
// Description:	Function to hadnle Message Box using mouse
//
// Input:		MSGBOX_DATA *msgbox, 
//				ACTION_DATA *action,
//				BOOLEAN * pRedraw
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEMouseMsgBoxHandleAction( MSGBOX_DATA *msgbox, ACTION_DATA *Data,BOOLEAN * pRedraw)
{
    BOOLEAN ButtonClicked = FALSE;
	CONTROL_ACTION Action;

	UINT16 Index, W;
	CHAR16 *txt=NULL;
	UINTN printLength, pos ;

	//EIP 103449  : In Setup click\Touch from navigation window, option are not displayed properly
	Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);

    if((
        (Data->Input.Data.MouseInfo.Top < msgbox->Top) ||
        (Data->Input.Data.MouseInfo.Top > (UINT32)(msgbox->Top + msgbox->Height)) ||
        (Data->Input.Data.MouseInfo.Left < msgbox->Left) ||
        (Data->Input.Data.MouseInfo.Left > (UINT32)(msgbox->Left + msgbox->Width)) 
     	)&&( (SingleClickActivation() &&  (ControlActionSelect ==Action)) ||  //If singleClickActivation is enabled/Disable
	 		 (ControlActionAbort == Action) || (ControlActionChoose ==Action ) //EIP-139608 Closing listbox whn mouse action happens outside listbox
	 		)
	  )
    {
		msgbox->MsgboxSel = MSGBOX_CANCEL;
		_MsgBoxCallCallback(msgbox,msgbox->MsgboxSel);
		gAction.ClearAction( Data );
		return EFI_SUCCESS;
    }

	
	if( (Action == ControlActionChoose ) || (Action == ControlActionSelect) )
    {
        if(Data->Input.Data.MouseInfo.Top == (UINT32)(msgbox->Top + msgbox->Height -2))
        {
            switch(msgbox->MsgBoxType & MSGBOX_TYPE_MASK)
            {
				case MSGBOX_TYPE_CUSTOM:

					if ( (msgbox->OptionCount != 0) && (msgbox->PtrTokens != NULL ))
					{ 
						W = ( msgbox->Width)/(msgbox->OptionCount) ;

						for ( Index = 0; Index < msgbox->OptionCount ; Index++ )
						{
							txt =  HiiGetString( msgbox->ControlData.ControlHandle, msgbox->PtrTokens[Index]);
							pos = (UINTN) (msgbox->Left + (Index * W) ) ;

							printLength = (TestPrintLength( txt ) / (NG_SIZE));
				
							if( printLength > W)
							{
								txt[HiiFindStrPrintBoundary(txt, W)] = L'\0';
								printLength = (TestPrintLength( txt ) / (NG_SIZE));
							}

							MemFreePointer( (VOID **)&txt);

							if( (Data->Input.Data.MouseInfo.Left)>=(UINT32)(pos + (W-printLength)/2 -2)  &&
				        			(Data->Input.Data.MouseInfo.Left)<=(UINT32)((pos + (W-printLength)/2 -2)+printLength))	
				    			{
					        		msgbox->MsgboxSel = (UINT8)Index;
                            					ButtonClicked = TRUE;
								break;	
				    			}
						}
					}

					break;				

			    case MSGBOX_TYPE_YESNO:
    			case MSGBOX_TYPE_OKCANCEL:

				    if( (Data->Input.Data.MouseInfo.Left)>=(UINT32)(msgbox->Left + msgbox->Width/3 -2)   &&
				        (Data->Input.Data.MouseInfo.Left)<=(UINT32)((msgbox->Left + msgbox->Width/3 -2)+msgbox->Button1Len))
					    {
					        msgbox->MsgboxSel = 0;
                            ButtonClicked = TRUE;
					    }

    				if( (Data->Input.Data.MouseInfo.Left)>=(UINT32)( msgbox->Left + 2*(msgbox->Width/3) -2)   &&
				        (Data->Input.Data.MouseInfo.Left)<=(UINT32)(( msgbox->Left + 2*(msgbox->Width/3) -2)+msgbox->Button2Len) )	
					    {
					        msgbox->MsgboxSel = 1;
                            ButtonClicked = TRUE;
    					}
     		    break;              
    			case MSGBOX_TYPE_OK:
    			default:
    				// EIP 46143 - Updated the msg box position to slect with click properly
    				if( (Data->Input.Data.MouseInfo.Left)>=(UINT32)(msgbox->Left + msgbox->Width/2 -1)   &&
    				    (Data->Input.Data.MouseInfo.Left)<=(UINT32)((msgbox->Left + msgbox->Width/2 -1)+msgbox->Button1Len) )	
				    	{
        					msgbox->MsgboxSel = 0;
                            ButtonClicked = TRUE;
    					}
    			break;
			}

            if(ButtonClicked)
            {
				if(ControlActionChoose == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
                    *pRedraw = TRUE;
                else
					_MsgBoxCallCallback(msgbox,msgbox->MsgboxSel);
            }
        }
    }
	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MsgBoxGetControlHight
//
// Description:	Function unsupported.
//
// Input:		VOID *object,VOID *frame, UINT16 *height 
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MsgBoxGetControlHight( VOID *object,VOID *frame, UINT16 *height )
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

