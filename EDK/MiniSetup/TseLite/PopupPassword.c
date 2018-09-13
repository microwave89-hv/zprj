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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupPassword.c $
//
// $Author: Premkumara $
//
// $Revision: 43 $
//
// $Date: 8/28/14 3:08p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupPassword.c $
// 
// 43    8/28/14 3:08p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 42    5/03/14 4:03p Premkumara
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
// 41    5/02/14 9:35p Arunsb
// EIP141986 changes reverted.
// 
// 40    5/02/14 10:56a Premkumara
// [TAG]  		EIP141986
// [Category]  	New Feature
// [Description]  	Made Grayed controls to focus-able when token
// TSE_SETUP_GRAYOUT_SELECTABLE
//  is enabled and can't edit the values
// [Files]  		AMITSE.sdl,CommonHelper.c,frame.c,Label.c,minisetupext.h,
// numeric.c,PopupPassword.c,PopupSel.c,PopupString.c,SubMenu.c
// 
// 39    5/02/14 6:49a Premkumara
// [TAG]  		EIP164232
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When password keyboard is launched and mouse pointer is
// placed on softkbd mouse will flickers continously.
// [RootCause]  	MouseRefresh and MouseStop is calling contiously in loop
// so mouse pointer get flickers
// [Solution]  	When mouse pointer is on softkbd and is static then stop
// calling MouseRefresh and MouseFreeze
// [Files]  		PopupPassword.c, CommonHelper.c, Mouse.c
// 
// 38    5/01/14 3:44p Premkumara
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
// 37    2/11/14 8:37p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 32    7/01/13 6:15a Premkumara
// [TAG]  		EIP127023
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Empty password causes setup crashing
// [RootCause]  	After entering empty password in first attempt and no
// confirm password is given so the variable ConfirmNewPswd is NULL. Since
// ConfirmNewPswd is NULL TSE is trying to compare and find length for
// this NULL string and so it caused this issue.
// [Solution]  	Handled NULL check for ConfirmNewPswd variable before and
// after getting password
// [Files]  		PopupPassword.c
// 
// 31    3/25/13 8:38a Premkumara
// [TAG]  		EIP116315
// [Category]  	Improvement
// [Description]  	Display control prompt string for password control.
// (for String on CHAP secret popup)
// [Files]  		- AMITSE.sdl
// - CommonHelper.c
// - FakeToken.c
// - AmiTSEStr.uni
// - TseLite\PopupPassword.c
// - uefi2.1\UefiWapper21.c
// - uefi2.0\UefiWapper20.c
// - uefi2.0\HiiCallback.c
// - uefi2.0\hii.h
// - uefi2.0\hii.c 
// 
// 30    3/08/13 1:34a Rajashakerg
// [TAG]  		EIP113085
// [Category]  	Improvement
// [Description]  	 Modify callback function behavior to match UEFI SPEC.
// [Files]  		HiiCallback.c, PopupPassword.c, SubMenu.c
// 
// 29    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 17    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 27    9/17/12 6:20a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 25    8/29/12 8:31a Premkumara
// [TAG]  		EIP 91364
// [Category]  	Improvement
// [Description]  	Token to disable the Cursor of TSE Password Dialog
// [Files]  		AMITSE.sdl, CommonHelper.c, Postmgmtext.c, PopupPassword.c,
// PopupString.c
// 
// 24    5/28/12 11:35a Premkumara
// [TAG]  		EIP88912
// [Category]  	Improvement
// [Description]  	On password window display the softkbd with only with
// valid key's
// [Files]  		CommonHelper.c, Postmgmtext.c, Mouse.c, PopupPassword.c
// 
// 23    1/02/12 11:49a Arunsb
// EIP79486
// Build error resolved for 32 bit.
// 
// 22    12/27/11 12:41p Arunsb
// [TAG]  		EIP79486
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Cursor is not blinking when "Softkbd" support enabled
// [RootCause]  	Unknown action also consumed
// [Solution]  	Unknow action not consumed.
// Mouse stopped instead of freezing when the mouse pointer is over the
// cursor.
// [Files]  		popupedit.c and popuppassword.c
// 
// 21    12/14/11 12:43p Arunsb
// EIP63190 => Moving password support from TSELite to BootOnly
// 
// 20    12/01/11 5:13a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
//  hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c
// ,PopupPassword.c
// 
// 19    11/30/11 12:20p Premkumara
// Updated with review comments.
// 
// 18    11/30/11 11:57a Premkumara
// [TAG]  		EIP75521
// [Category]  	Improvement
// [Description]  	Need to support interactive password controls
// [Files]  		PopupPassword.c, PopupPassword.h, TsetAdvanced.c
// 
// 17    11/30/11 11:32a Premkumara
// [TAG]  		EIP67695
// [Category]  	Improvement
// [Description]  	No cursor visible in setup, while editing text input
// box
// [Files]  		Buffer.c, Postmgmtext.c, PopupString.c, PopupPassword.c
// 
// 16    11/21/11 11:15a Premkumara
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
// 15    11/20/11 8:12a Rajashakerg
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
// 14    11/20/11 7:40a Premkumara
// [TAG]  		EIP73226
// [Category]  	New Feature
// [Description]  	Extended support for password prompt
// [Files]  		FakeToken.c, Uefi21Wapper.c, AmiTSEStr.uni, PopupPassword.c,
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
// 12    11/10/11 12:48a Arunsb
// [TAG]  		EIP67735
// [Category]  	Improvement
// [Description]  	Zeroing password buffers before freeing
// [Files]  		mem.c, mem.h, popupedit.c, popuppassword.c and tseadvanced.c
// 
// 11    3/28/11 9:25p Madhans
// [TAG]  		EIP41744 
// [Category]  	Improvement
// [Description]  	SoftKeyBoard Support in TSE. and Support to Work with
// new mouse driver(Label 07).
// [Files]  		HookAnchor.h
// AMITSE.sdl
// CommonHelper.c
// commonoem.c
// commonoem.h
// HookList.c
// HookAnchor.c
// Mouse.c
// minisetupext.c
// postmgmtext.c
// minisetupext.h
// PopupPassword.c
// PopupString.c
// TseLiteCommon.c
// 
// 10    12/02/10 2:34p Madhans
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
// 9     10/04/10 4:26p Blaines
// In the function _DoPopupEdit, call gPopupEdit.SetType before calling
// gPopupEdit.Initialize. This is useful in case the function
// gPopupEdit.Initialize is overriden. 
// 
// 8     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 13    8/27/10 4:43a Mallikarjunanv
// EIP-39764: Setup password non-case sensitive support and password
// encode support updated
// 
// 12    4/09/10 12:26p Madhans
// 
// 11    3/26/10 6:53p Madhans
// Support to Map the do the Control Mapping from gTseControlMap Table. So
// no changes need in Frame.c, With this feature gTseControlMap Can be
// customized to add/customize the TSE controls.
// 
// 10    2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 9     2/05/10 6:05p Madhans
// To fix the Screen corruption if mouse pointer is on the popup.
// 
// 8     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 7     1/09/10 6:54a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 6     8/13/09 1:20p Blaines
// Fix color initialization 
// 
// 5     7/09/09 12:29p Mallikarjunanv
// updated the password encoding fix
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
// Name:		PopupPassword.c
//
// Description:	This file contains code to handle Popup Passwords
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
////////////////////////////////////////////////////////////////
////	Extern Variables
////////////////////////////////////////////////////////////////
extern UINTN gInvalidPasswordFailMsgBox;
//EIP-73226 Extended Password support
extern UINTN gClearPasswordMsgBox;
extern UINTN gInvalidRangeFailMsgBox;
extern UINTN gClearLabelPasswordMsgBox;

CALLBACK_VARIABLE  gPopupEditCb = { { CALLBACK_TYPE_VARIABLE, sizeof(CALLBACK_VARIABLE) }, 0,0,0,NULL };
UINT8 res = (UINT8)-1;

POPUP_PASSWORD_METHODS gPopupPassword =
{
	PopupPasswordCreate,
	PopupPasswordDestroy,
	PopupPasswordInitialize,
	PopupPasswordDraw,
	PopupPasswordHandleAction,
	PopupPasswordSetCallback,
	PopupPasswordSetFocus, 
	PopupPasswordSetPosition,
	PopupPasswordSetDimensions,
	PopupPasswordSetAttributes,
    PopupPasswordGetControlHeight

};
VOID 	GetCoordinates(INT32 *x, INT32 *y, INT32 *z);
VOID 	SetPwdKeyboardLayout(VOID);//EIP-88912
VOID 	ResetPwdKeyboardLayout(VOID);//EIP-88912
BOOLEAN IsTSECursorSupport(); //EIP-91364
VOID 	SavePswdString (CONTROL_INFO *ControlData, CHAR16 *String);
BOOLEAN	IsPasswordSupportNonCaseSensitive();
BOOLEAN	IsShowPromptStringAsTitle(VOID);//EIP-116315 password string
BOOLEAN IsMouseOnSoftkbd(VOID); //EIP-164232

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordCreate
//
// Description:	this function uses the create function of control
//					and creates the popup password
//
// Input:	POPUP_PASSWORD_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordCreate( POPUP_PASSWORD_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(POPUP_PASSWORD_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gPopupPassword;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordDestroy
//
// Description:	this function uses the destroy function of control
//					and destroys the popup password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordDestroy( POPUP_PASSWORD_DATA *popuppassword, BOOLEAN freeMem )
{
	if(NULL == popuppassword)
	  return EFI_SUCCESS;

	gControl.Destroy( popuppassword, FALSE );

	MemFreePointer( (VOID **)&popuppassword->Text );

	if( freeMem )
		MemFreePointer( (VOID **)&popuppassword );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordInitialize
//
// Description:	this function uses the initialize function of control
//					and initializes the popup password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordInitialize( POPUP_PASSWORD_DATA *popuppassword, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gControl.Initialize( popuppassword, data );
	if (EFI_ERROR(Status))
		return Status;

	// add extra initialization here...
	SetControlColorsHook(NULL, NULL,  
				NULL, NULL,
				&(popuppassword->SelBGColor), &(popuppassword->SelFGColor),
			        &(popuppassword->BGColor), &(popuppassword->FGColor),
				NULL, NULL,
				NULL,
				NULL ,NULL,
				NULL,NULL );

	popuppassword->ControlData.ControlHelp = UefiGetHelpField(popuppassword->ControlData.ControlPtr);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordDraw
//
// Description:	function to draw the popup password with attributes
//
// Input:	POPUP_PASSWORD_DATA *popuppassword
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordDraw(POPUP_PASSWORD_DATA *popuppassword )
{
	CHAR16 *text;
	EFI_STATUS Status = EFI_SUCCESS;

	UINT8 ColorLabel = popuppassword->FGColor;
	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( popuppassword->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &popuppassword->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorLabel = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	text = HiiGetString( popuppassword->ControlData.ControlHandle, UefiGetPromptField(popuppassword->ControlData.ControlPtr));
	if ( text == NULL )
		return EFI_OUT_OF_RESOURCES;

	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(popuppassword->Height>1 && IsTSEMultilineControlSupported())
	{
		DrawMultiLineStringWithAttribute( popuppassword->Left , popuppassword->Top, 
				(UINTN)(popuppassword->Width),(UINTN) popuppassword->Height,
				text,(UINT8)( (popuppassword->ControlFocus) ? 
						 popuppassword->SelBGColor  | popuppassword->SelFGColor : 
						 popuppassword->BGColor | ColorLabel));
	}
	else
	{
		// use frame width minus margins as available space
		// boundary overflow  check
		if ( (TestPrintLength( text ) / (NG_SIZE)) > (UINTN)(popuppassword->Width  ))
				text[HiiFindStrPrintBoundary(text,(UINTN)(popuppassword->Width  ))] = L'\0';
	
		DrawStringWithAttribute( popuppassword->Left  , popuppassword->Top, text, 
				(UINT8)( (popuppassword->ControlFocus) ? 
						 popuppassword->SelBGColor  | popuppassword->SelFGColor : 
						 popuppassword->BGColor | ColorLabel   ));
	}
	
	MemFreePointer( (VOID **)&text );
	FlushLines( popuppassword->Top  , popuppassword->Top );

	return Status;
}

EFI_STATUS PopupPasswordSetCallback( POPUP_PASSWORD_DATA *popuppassword, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( popuppassword, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordCheckInstalledLocal
//
// Description:	function to check the local installation of popup password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword
//
// Output:	True/False
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 PopupPasswordCheckInstalledLocal(POPUP_PASSWORD_DATA *popuppassword)
{
    VOID *data = popuppassword->ControlData.ControlPtr;
    CHAR16 *RealPassword=NULL;
	UINT32 Installed=0;
	// read real password from nvram
	RealPassword = EfiLibAllocateZeroPool( ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16) );
	if ( RealPassword == NULL )
        return Installed;
	MemSet( RealPassword, ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16), 0 );

	VarGetValue( popuppassword->ControlData.ControlVariable, 
		UefiGetQuestionOffset(data), 
		(UINT8)UefiGetMaxValue(data)*2, RealPassword );

	if ( RealPassword[0] != L'\0' )
		Installed = 1;
	MemFreePointer( (VOID **)&RealPassword );

	return Installed;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordAuthenticateLocal
//
// Description:	function to check authentication of the password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, CHAR16 *Password
//
// Output:	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN PopupPasswordAuthenticateLocal( POPUP_PASSWORD_DATA *popuppassword, CHAR16 *Password )
{
    VOID *data = popuppassword->ControlData.ControlPtr;
    CHAR16 *RealPassword=NULL,*TempEncoded=NULL;
	BOOLEAN AuthenticateStatus=FALSE;
	UINTN	ii;

	// read real password from nvram
	RealPassword = EfiLibAllocateZeroPool( ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16) );
	if ( RealPassword == NULL )
        return AuthenticateStatus;
	MemSet( RealPassword, ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16), 0 );

	VarGetValue( popuppassword->ControlData.ControlVariable, 
		UefiGetQuestionOffset(data), 
		(UINT8)UefiGetMaxValue(data)*2, RealPassword );

	TempEncoded = EfiLibAllocateZeroPool( ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16) );
	if ( TempEncoded == NULL )
        return AuthenticateStatus;

	MemSet( TempEncoded, ((UINT8)UefiGetMaxValue(data)+1) * sizeof(CHAR16), 0 );
	EfiStrCpy(TempEncoded,Password);

//EIP106950
	if (
      (IsPasswordSupportNonCaseSensitive ()) && 
      ( (VARIABLE_ID_AMITSESETUP == popuppassword->ControlData.ControlVariable) || (VARIABLE_ID_IDE_SECURITY == popuppassword->ControlData.ControlVariable) )
      )
	{
		for (ii = 0; ii < (UefiGetMaxValue(data)); ii++)
			TempEncoded [ii] = ((TempEncoded [ii]>=L'a')&&(TempEncoded [ii]<=L'z'))?(TempEncoded [ii]+L'A'-L'a'):TempEncoded [ii];
	}
//EIP106950
//EIP 23354 : Start
	//PasswordEncodeHook( TempEncoded, (UINT8)UefiGetMaxValue(data) * sizeof(CHAR16));
	if( IsPasswordEncodeEnabled( &popuppassword->ControlData )){
		PasswordEncodeHook( TempEncoded, (UINT8)UefiGetMaxValue(data) * sizeof(CHAR16));
	}
//EIP 23354 : END
    if( EfiCompareMem(TempEncoded,RealPassword,(UINT8)UefiGetMaxValue(data) * sizeof(CHAR16)))
		AuthenticateStatus = FALSE;
	else
		AuthenticateStatus = TRUE;

	MemFreePointer( (VOID **)&RealPassword );
	MemFreePointer( (VOID **)&TempEncoded );

	return AuthenticateStatus;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdatePasswordToNonCaseSensitive
//
// Description:	function to update the given password to non case sensitive
//
// Input:	CHAR16 *Password, UINTN PwdLength
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdatePasswordToNonCaseSensitive(CHAR16 *Password, UINTN PwdLength)
{
	UINTN Idx;
	for ( Idx = 0; Idx < PwdLength; Idx++ )
		Password[Idx] = ((Password[Idx]>=L'a')&&(Password[Idx]<=L'z'))?(Password[Idx]+L'A'-L'a'):Password[Idx];
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupPasswordActivate
//
// Description:	function to set and activate a password
//
// Input:	POPUP_PASSWORD_DATA *popuppassword
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _PopupPasswordActivate(POPUP_PASSWORD_DATA *popuppassword)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	BOOLEAN AbortUpdate = FALSE;
	CHAR16 *Text=NULL,*NewPswd=NULL,*ConfirmNewPswd=NULL;
	VOID *data = popuppassword->ControlData.ControlPtr;
	UINTN NewPwLen = 0;
	UINT16 orgtext = 0;
	UINT16 newtoken = 0;

	if( PopupPwdAuthenticateIDEPwd(popuppassword,&AbortUpdate,data) != EFI_SUCCESS)
	{
		AbortUpdate = FALSE;

		if(PopupPasswordCheckInstalled(popuppassword))
		{
            // ask for old password (popupedit)
			Status = _DoPopupEdit( popuppassword, (IsShowPromptStringAsTitle() ? STRING_TOKEN(STR_OLD_PSWD_LABEL): STRING_TOKEN(STR_OLD_PSWD)), &Text);
			if( Status )
				AbortUpdate = TRUE;
			else
			{
				if(!PopupPasswordAuthenticate( popuppassword, Text ))
                {   
					// optional message to user: "wrong password" and  exit                   
					CallbackShowMessageBox( (UINTN)gInvalidPasswordFailMsgBox, MSGBOX_TYPE_OK );
					AbortUpdate = TRUE;
				}
			}
		}
	}
	if(AbortUpdate == FALSE)
	{
Password:
		//ask for new password(1)
		Status = _DoPopupEdit( popuppassword, (IsShowPromptStringAsTitle() ? STRING_TOKEN(STR_NEW_PSWD_LABEL): STRING_TOKEN(STR_NEW_PSWD)), &NewPswd);

        if(!Status)
        {
			NewPwLen = EfiStrLen(NewPswd);
			//EIP-39764 : non case sensitive support during setting password
			//EIP106950
			if (
            (IsPasswordSupportNonCaseSensitive ()) && 
            (NewPwLen != 0) &&
            ( (VARIABLE_ID_AMITSESETUP == popuppassword->ControlData.ControlVariable) || (VARIABLE_ID_IDE_SECURITY == popuppassword->ControlData.ControlVariable) )
            )
         {
				UpdatePasswordToNonCaseSensitive (NewPswd, NewPwLen);
			}
			if (VARIABLE_ID_IDE_SECURITY != popuppassword->ControlData.ControlVariable)
			{
				if (PopupPasswordCheckInstalled (popuppassword))
				{
				 // Override the minmax validation for password clearing
					if(NewPwLen == 0) 
					{
						//EIP-116315 password string Starts
						if ( IsShowPromptStringAsTitle() )
						{
							CHAR16 *temptext = NULL, *tText = NULL;
							CHAR16 *tempTitle = NULL;
							UINTN strlen = 0;

							//Taking backup of original StringID
							orgtext = ((AMI_IFR_MSGBOX*)(gClearLabelPasswordMsgBox))->Text;

							//Get TSE string
							temptext = HiiGetString( (VOID*)(UINTN)INVALID_HANDLE, orgtext);
							strlen = EfiStrLen(temptext);

							tempTitle = EfiLibAllocateZeroPool((strlen+2)*sizeof(CHAR16));
							
							if (NULL == tempTitle)
								return EFI_OUT_OF_RESOURCES;

							EfiStrCpy (tempTitle,temptext);
							strlen = EfiStrLen(tempTitle);
							
							MemFreePointer( (VOID **)&temptext );

							//Get prompt string from controlptr
							temptext = HiiGetString( popuppassword->ControlData.ControlHandle, UefiGetPromptField(popuppassword->ControlData.ControlPtr));
							strlen = EfiStrLen(temptext+2);

							tempTitle = MemReallocateZeroPool (
														tempTitle,
														( (EfiStrLen (tempTitle) + 2) * sizeof (CHAR16) ),
														( ((EfiStrLen (tempTitle) + 2) * sizeof (CHAR16)) + ((EfiStrLen (temptext) + 2) * sizeof (CHAR16)) )    //2 for /n and NULL character
														);

							if (NULL == tempTitle)
								return EFI_OUT_OF_RESOURCES;

							//Eliminate white space character if any precedes
							tText = temptext;
							while(*temptext == L' ')
							{
								temptext++;
							}

							//Appending tse string with controlptr prompt string
							EfiStrCat (tempTitle,temptext);
							EfiStrCat (tempTitle,L"?");

							//Adding string to hiistring
							newtoken = HiiAddString( gHiiHandle, tempTitle );

							//Setting new stringID as current stringID
							((AMI_IFR_MSGBOX*)(gClearLabelPasswordMsgBox))->Text = newtoken;

							MemFreePointer( (VOID **)&tText );
							MemFreePointer( (VOID **)&tempTitle );
						}
						//EIP-116315 password string. Ends

						//Report Message box for Clearing Old password
						if(CallbackShowMessageBox( (IsShowPromptStringAsTitle() ? (UINTN)gClearLabelPasswordMsgBox : (UINTN)gClearPasswordMsgBox), MSGBOX_TYPE_YESNO )!= MSGBOX_YES)
						{
							if ( IsShowPromptStringAsTitle() )
							{
								//Resetting original token
								((AMI_IFR_MSGBOX*)(gClearLabelPasswordMsgBox))->Text = orgtext;
								//Delete created token
								HiiRemoveString(gHiiHandle, newtoken);
							}

							goto Password;
							//Status = EFI_UNSUPPORTED; //Do not clear the password
						} 
						else 
						{
							if ( IsShowPromptStringAsTitle() )
							{
								//Resetting original token
								((AMI_IFR_MSGBOX*)(gClearLabelPasswordMsgBox))->Text = orgtext;
								//Delete created token
								HiiRemoveString(gHiiHandle, newtoken);
							}

							ConfirmNewPswd = EfiLibAllocateZeroPool( sizeof(CHAR16) );
							
							if(ConfirmNewPswd) 
							{
								*ConfirmNewPswd = L'\0'; //Set confirmation password to null string
							} 
							else 
							{
								Status = EFI_OUT_OF_RESOURCES;
							}
						}
					}
				}
			}
			if( 
				NewPwLen && 
				( (NewPwLen < (UINT8)UefiGetMinValue (popuppassword->ControlData.ControlPtr)) ||
				  (NewPwLen > (UINT8)UefiGetMaxValue (popuppassword->ControlData.ControlPtr)) )
				)
            {
                //Report Message box
				CallbackShowMessageBox( (UINTN)gInvalidRangeFailMsgBox, MSGBOX_TYPE_OK );
                Status = EFI_UNSUPPORTED;
            }
        }
		// ask for new password(2)again
		if ( ((!Status) && (NewPwLen != 0)) || ((VARIABLE_ID_IDE_SECURITY == popuppassword->ControlData.ControlVariable) && (!Status)) )
		{
			Status = _DoPopupEdit(  popuppassword, (IsShowPromptStringAsTitle() ? STRING_TOKEN(STR_CONFIRM_NEW_PSWD_LABEL) : STRING_TOKEN(STR_CONFIRM_NEW_PSWD)), &ConfirmNewPswd);			
		}

		if ( !Status )
		{
			//EIP-39764 : non case sensitive support during setting password
			//EIP106950
			if (
					(IsPasswordSupportNonCaseSensitive ()) &&
					( NULL!=ConfirmNewPswd ) && (EfiStrLen (ConfirmNewPswd)) && //EIP-127023 Avoid crashing when give empty password
					( (VARIABLE_ID_AMITSESETUP == popuppassword->ControlData.ControlVariable) || (VARIABLE_ID_IDE_SECURITY == popuppassword->ControlData.ControlVariable) )
            )
         {
				NewPwLen = EfiStrLen (ConfirmNewPswd);
				UpdatePasswordToNonCaseSensitive (ConfirmNewPswd, NewPwLen);
			}
		    if ( ( NULL!=ConfirmNewPswd ) && EfiStrCmp(NewPswd, ConfirmNewPswd)==0 ) //EIP-127023  Avoid crashing when give empty password
		    {
				//EIP-75521 Support for Interactive Password control
				if(popuppassword->Text != NULL){
					MemFreePointer( (VOID **)&popuppassword->Text );
				}
				popuppassword->Text = (CHAR16 *) EfiLibAllocateZeroPool((NewPwLen + 1) * sizeof(CHAR16));
				EfiStrCpy(popuppassword->Text, NewPswd);

				//save new password
                if ( ( popuppassword->Callback != NULL ) && ( popuppassword->Cookie != NULL ) )
				{
                    VOID *ifrData = popuppassword->ControlData.ControlPtr;
					CALLBACK_PASSWORD *callbackData = (CALLBACK_PASSWORD *)popuppassword->Cookie;

					callbackData->Variable = popuppassword->ControlData.ControlVariable;
					callbackData->Offset = UefiGetQuestionOffset(ifrData);
					callbackData->Length = (UINT8)UefiGetMaxValue(ifrData) * sizeof(CHAR16);
					callbackData->Data = (VOID *)NewPswd;
					SavePswdString(&(popuppassword->ControlData),NewPswd);
					UefiPreControlUpdate(&(popuppassword->ControlData));
					popuppassword->Callback( popuppassword->Container,popuppassword, popuppassword->Cookie );

					PopupPwdUpdateIDEPwd ();
				}


				//For interactive control invoke the formcallback function.
				if(UefiIsInteractive(&popuppassword->ControlData))
				{
					VOID *Handle = popuppassword->ControlData.ControlHandle;
					UINT16 Key = UefiGetControlKey(&(popuppassword->ControlData));
					CONTROL_DATA *Control = (CONTROL_DATA *)NULL;

					//Call the callback passing the input value and value size.
					Status = CallFormCallBack( &(popuppassword->ControlData),Key,0,AMI_CALLBACK_CONTROL_UPDATE);

					Control = GetUpdatedControlData((CONTROL_DATA*)popuppassword, CONTROL_TYPE_PASSWORD, Handle, Key);
					if(Control == NULL){ //Control deleted.
						return EFI_SUCCESS;
					}
					if(Control != (CONTROL_DATA *)popuppassword){
						popuppassword = (POPUP_PASSWORD_DATA *)Control; //Control Updated.
					}
				}

				popuppassword->ControlActive = FALSE;
            }
			else
			{
			    CallbackShowMessageBox( (UINTN)gInvalidPasswordFailMsgBox, MSGBOX_TYPE_OK );
			}
	    }
	}
	StringZeroFreeMemory ((VOID **)&Text);		//EIP67735 zeroing the password prompt memories
	StringZeroFreeMemory ((VOID **)&NewPswd);
	StringZeroFreeMemory ((VOID **)&ConfirmNewPswd);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupPasswordHandleAction
//
// Description:	function to handle the password actions
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, , ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _PopupPasswordHandleAction( POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT8 u8ChkResult;

	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	   return Status;
	
    u8ChkResult = CheckControlCondition( &popuppassword->ControlData );
	 
	 //Not to perform action for control when token TSE_SETUP_GRAYOUT_SELECTABLE is enable to set focus for GrayoutIf control
    if ( IsGrayoutSelectable() && (COND_GRAYOUT == u8ChkResult) ) {
        return EFI_UNSUPPORTED;
    }

	if ( Data->Input.Type == ACTION_TYPE_KEY )
    {
        CONTROL_ACTION Action;

        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);

        if(ControlActionSelect == Action)
        {
			if(UefiIsInteractive(&popuppassword->ControlData))
				if(PopupPasswordFormCallback(&(popuppassword->ControlData),UefiGetControlKey(&(popuppassword->ControlData)),0) == EFI_SUCCESS)
					return EFI_SUCCESS;

            return _PopupPasswordActivate(popuppassword);
        }
    }

    if(Data->Input.Type == ACTION_TYPE_MOUSE)
	{
		if(ControlActionSelect == MapControlMouseActionHook(&Data->Input.Data.MouseInfo))
		{
			
			//EIP-123727 check whether MouseTop is within the Height and Width of Password Control or not
			if((Data->Input.Data.MouseInfo.Top >= (UINT32)popuppassword->Top) && (Data->Input.Data.MouseInfo.Top < (UINT32)(popuppassword->Top+popuppassword->Height)) &&
			   (Data->Input.Data.MouseInfo.Left >= (UINT32)popuppassword->Left) && (Data->Input.Data.MouseInfo.Left < (UINT32)(popuppassword->Left+popuppassword->Width))
			)
			{
				if(UefiIsInteractive(&popuppassword->ControlData))
					if(PopupPasswordFormCallback(&(popuppassword->ControlData),UefiGetControlKey(&(popuppassword->ControlData)),0) == EFI_SUCCESS)
						return EFI_SUCCESS;

	                return _PopupPasswordActivate(popuppassword);
	        }
		}
	}
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordHandleAction
//
// Description:	Function to handle the PopupPassword Actions
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordHandleAction( POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	
	Status = PopupPwdHandleActionOverRide(popuppassword, Data);

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordSetFocus
//
// Description:	Function to set focus
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, BOOLEAN focus
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordSetFocus(POPUP_PASSWORD_DATA *popuppassword, BOOLEAN focus)
{
    UINT8 u8ChkResult;

	if(focus != FALSE)
	{
        u8ChkResult = CheckControlCondition( &popuppassword->ControlData );
		if ( ((u8ChkResult != COND_NONE) && (u8ChkResult != COND_GRAYOUT)) ||
             (!IsGrayoutSelectable() && (u8ChkResult == COND_GRAYOUT)) )
			return EFI_UNSUPPORTED;
	}

	if( !(popuppassword->ControlFocus && focus) )
		popuppassword->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordSetPosition
//
// Description:	Function to set position.
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordSetPosition(POPUP_PASSWORD_DATA *popuppassword, UINT16 Left, UINT16 Top )
{
	return gControl.SetPosition( popuppassword, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordSetDimensions(POPUP_PASSWORD_DATA *popuppassword, UINT16 Width, UINT16 Height )
{
	return gControl.SetDimensions( popuppassword, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordSetAttributes(POPUP_PASSWORD_DATA *popuppassword, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( popuppassword, FGColor, BGColor );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupPasswordGetControlHeight
//
// Description:	function to get the height of the label
//
// Input:	POPUP_PASSWORD_DATA *popuppassword, frame, UINT16 *height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupPasswordGetControlHeight(POPUP_PASSWORD_DATA *popuppassword, VOID *frame, UINT16 *height)
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
	
		Width = ((FRAME_DATA*)frame)->FrameData.Width - 2;

		text = HiiGetString( popuppassword->ControlData.ControlHandle, UefiGetPromptField(popuppassword->ControlData.ControlPtr));
		if ( text == NULL )
			return EFI_OUT_OF_RESOURCES;
	
		newText = StringWrapText( text, Width, height );
	
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





//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_CBPopupEdit
//
// Description:	Function for PopupEdit callback.
//
// Input:		VOID *container, VOID *object, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _CBPopupEdit(VOID *container, VOID *object, VOID *cookie)
{
	EFI_STATUS Status = EFI_SUCCESS;
	if(cookie!=NULL)
	{

		res=0;
	}
	else
 	   res=1; // exit with no changes to string

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PopupEditGetValue
//
// Description:	Function to get edit value.
//
// Input:		POPUPEDIT_DATA *popupedit
//
// Output:		UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _PopupEditGetValue( POPUPEDIT_DATA *popupedit )
{
	ACTION_DATA *action = gApp->Action;
	EFI_STATUS 	Status = EFI_SUCCESS;//EIP:67695
	BOOLEAN 	DrawCursor = TRUE;//EIP:67695
	UINT32  	MousePointerX = 0,MousePointerY = 0,MousePointerZ = 0;
	
	gPopupEdit.SetCallback( popupedit, NULL, _CBPopupEdit, &gPopupEditCb );
	gPopupEdit.SetDimensions( popupedit, popupedit->Width , popupedit->Height );
	res = (UINT8)-1;

	SetPwdKeyboardLayout();//EIP-88912
	TSEStringReadLoopEntryHook();

	while ( res == (UINT8)-1 )
	{
		if ( action->Input.Type != ACTION_TYPE_NULL )
			gAction.ClearAction( action );

		GetCoordinates (&MousePointerX, &MousePointerY, &MousePointerZ);
		if (gST->ConOut)
		{
			if ( 	
				( ((MousePointerX/HiiGetGlyphWidth ()) <= (UINT32)gST->ConOut->Mode->CursorColumn+1) && ((MousePointerX/HiiGetGlyphWidth ()) >= (UINT32)gST->ConOut->Mode->CursorColumn-1) ) && 
				( ((MousePointerY/HiiGetGlyphHeight ()) <= (UINT32)gST->ConOut->Mode->CursorRow+1) && ((MousePointerY/HiiGetGlyphHeight ()) >= (UINT32)gST->ConOut->Mode->CursorRow-1) )			//EIP79486 Stop the mouse if mouse poiner is over the text cursor useful for avoiding corruption
				)
				MouseStop ();
			else
			{
				if ( !IsMouseOnSoftkbd() ) //EIP-164232 checking for mouse pointer position
					MouseFreeze ();
			}
		}

		gPopupEdit.Draw( popupedit );
		DoRealFlushLines();

		if (IsTSECursorSupport())//EIP-91364
		{
			if (TRUE == DrawCursor)	//EIP:67695 Enabling at valid times
			{
				gST->ConOut->SetAttribute (gST->ConOut, popupedit->FGColor | popupedit->BGColor);
				gST->ConOut->SetCursorPosition (gST->ConOut, popupedit->Left + EfiStrLen (popupedit->Text)+1, popupedit->Height- (2+ (popupedit->TextWidth/popupedit->Width +1))+popupedit->Top+1);
				gST->ConOut->EnableCursor (gST->ConOut, TRUE);
				DrawCursor = FALSE;
			}
		}
		if  ( !IsMouseOnSoftkbd() ) //EIP-164232 Avoid mouse flickers If mouse pointer is on softkbd area
			MouseRefresh();


		if ( gAction.GetAction( action ) != EFI_SUCCESS )
			continue;
		Status = gPopupEdit.HandleAction( popupedit, action );
		if (IsTSECursorSupport() && !(EFI_ERROR (Status)))//EIP:67695
		{
			DrawCursor = TRUE;			//EIP:67695 If any valid action performed then draw the cursor, usefull for blinking
		}
	}
	TSEStringReadLoopExitHook();
	ResetPwdKeyboardLayout();//EIP-88912

	return res;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DoPopupEdit
//
// Description:	function to perform the edit operations on popup
//
// Input:	POPUP_PASSWORD_DATA *PopupPassword, UINT16 Title, CHAR16 **Text
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _DoPopupEdit( POPUP_PASSWORD_DATA *PopupPassword, UINT16 Title, CHAR16 **Text)
{
	static UINT8 gIFRPopupEdit[50];
	EFI_STATUS Status= EFI_SUCCESS;
	UINT8 retValue = (UINT8)-1;
	UINT16 newtoken = 0;

	POPUPEDIT_DATA *popupedit = NULL;

	CONTROL_INFO dummy;
    BOOLEAN 		PreviousCursorState = gST->ConOut->Mode->CursorVisible;//EIP:67695

	Status = gPopupEdit.Create( &popupedit );
	if ( EFI_ERROR( Status ) )
		return Status;

	MemSet( &dummy, sizeof(dummy), 0 );

    MemCopy( &gIFRPopupEdit, (VOID*)PopupPassword->ControlData.ControlPtr, UefiGetIfrLength(PopupPassword->ControlData.ControlPtr) );

	//EIP-116315 password string. Starts
	//To show Control prompt string as PopupPassword String instead from AMITSEStr.uni file
	if (IsShowPromptStringAsTitle())
	{
		UINTN strlen = 0;
		CHAR16 *temptext, *tempTitle = NULL, *tText = NULL;		
		dummy.ControlHandle = PopupPassword->ControlData.ControlHandle;
		
		//Get TSE string
		temptext = HiiGetString( (VOID*)(UINTN)INVALID_HANDLE, Title);
		strlen = EfiStrLen(temptext);

		tempTitle = EfiLibAllocateZeroPool((strlen+2)*sizeof(CHAR16));
		
		if (NULL == tempTitle)
			return EFI_OUT_OF_RESOURCES;

		EfiStrCpy (tempTitle,temptext);
		strlen = EfiStrLen(tempTitle);

		MemFreePointer( (VOID **)&temptext );

		//Get Prompt String from ControlPtr
		temptext = HiiGetString( PopupPassword->ControlData.ControlHandle, UefiGetPromptField(PopupPassword->ControlData.ControlPtr));
		strlen = EfiStrLen(temptext+2);

		tempTitle = MemReallocateZeroPool (
									tempTitle,
									( (EfiStrLen (tempTitle) + 2) * sizeof (CHAR16) ),
									( ((EfiStrLen (tempTitle) + 2) * sizeof (CHAR16)) + ((EfiStrLen (temptext) + 2) * sizeof (CHAR16)) )    //2 for /n and NULL character
									);

		if (NULL == tempTitle)
			return EFI_OUT_OF_RESOURCES;

		//Eliminate white space character if any precedes
		tText = temptext;
		while(*temptext == L' ')
		{
			temptext++;
		}

		//Appending TSE string with controlptr string
		EfiStrCat (tempTitle,temptext);
		
		//Create new token for newly created string
		newtoken = HiiAddString( PopupPassword->ControlData.ControlHandle, tempTitle );

		//Set control prompt with newly created token
		UefiSetPromptField ((VOID*)&gIFRPopupEdit,newtoken);

		MemFreePointer( (VOID **)&tText );
		MemFreePointer( (VOID **)&tempTitle );
	}
	else
	{
		dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;
		UefiSetPromptField ((VOID*)&gIFRPopupEdit,Title);
	}
	//EIP-116315 password string. Ends

	dummy.ControlPtr = (VOID*)&gIFRPopupEdit;
	dummy.ControlFlags.ControlVisible = TRUE;
   
	//gPopupEdit.SetTitle(popupedit,Title);
    gPopupEdit.SetText(popupedit,*Text);
	gPopupEdit.SetType( popupedit, POPUPEDIT_TYPE_PASSWORD );
	Status = gPopupEdit.Initialize( popupedit, &dummy );
	if ( EFI_ERROR( Status ) )
		goto Done;

	//gPopupEdit.SetType( popupedit, POPUPEDIT_TYPE_PASSWORD );
	retValue = (UINT8)_PopupEditGetValue( popupedit );
	if (IsTSECursorSupport())//EIP-91364
	{
		gST->ConOut->EnableCursor (gST->ConOut, PreviousCursorState);//EIP:67695
	}
	if(retValue ==0)
	{
		// string changed, save to nvram or do whatever needs to be done
	    MemFreePointer( (VOID **)Text );
	    *Text = EfiLibAllocateZeroPool( (gPopupEditCb.Length+1) * sizeof(CHAR16) );
	     if ( Text == NULL )
		return EFI_OUT_OF_RESOURCES;

	    EfiStrCpy( *Text, gPopupEditCb.Data );			

	}
	else
		Status = EFI_UNSUPPORTED;
Done:
	gPopupEdit.Destroy( popupedit, TRUE );
	if ( IsShowPromptStringAsTitle() )
		HiiRemoveString(gHiiHandle, newtoken);//Delete created token
	return Status;
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
