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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/postmgmtext.c $
//
// $Author: Premkumara $
//
// $Revision: 19 $
//
// $Date: 8/28/14 8:39a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/postmgmtext.c $
// 
// 19    8/28/14 8:39a Premkumara
// [TAG]       	EIP142551
// [Category]  	Bug Fix
// [Severity]		Minor
// [Symptom]		Mouse Movement is not initialized to Full Screen Resolution
// in case of quiet boot mode with high resolution OEM Logo.
// [Root Cause]	Mouse Initialization was not across the full screen incase
// of High Resolution Quiet Boot Logo.
// [Solution]		Initialised the Mouse with the Resolution Set in case of
// Quiet Boot logo so that Mouse will move acroos the Whole screen
// [Files]        Mouse.c, BootFlowLib.c, PostMgmt.c, PostMgmtExt.c,
// Notify.c, MinisetupExt.c
// 
// 18    8/28/14 7:30a Premkumara
// [TAG]		EIP107833, 125388
// [Category]	Improvement
// [Symptom:]	Setting best text and GOP mode while using TSEPostinterfaces
// before TSE or after TSE.
// [Files]		Protocol.c, AMITSE.sdl, CommonHelper.c, MiniSetup.sdl,
// PostMgmtc, PostmgmtExt.c, MessagBox.c
// 
// 17    7/15/14 5:50p Arunsb
// [TAG]	EIP174261
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	Location issue of Password Popup
// [Root Cause]	Text Mode was not setting properly when gMaxRows != Rows
// or gMaxCols != Cols
// [Solution]	Modified the code to set the Text Mode properly when
// gMaxRows != Rows
// or gMaxCols != Cols
// [Files]	postmgmtext.c
// 
// 16    6/25/14 12:33a Premkumara
// [TAG]	EIP173965
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	HDD password prompt is not proper in post.
// [Root Cause]	Since the password length for HDD password is
// IDE_PASSWORD_LENGTH = 32 and Setup password is SETUP_PASSWORD_LENGTH =
// 20(TsePasswordLength) . So using TsePasswordLength to find coordinate
// of X for displaying either HDD/Setup password prompt in post will cause
// distortion for HDD.
// [Solution]	Using respective password (HDD/Setup) length to find the
// coordinates of X for drawing post HDD/Setup password prompt in proper
// place.
// [Files]	PostMgmtExt.c
// 
// 15    5/03/14 6:24p Premkumara
// [TAG]	EIP135665
// [Category]	Bug Fix
// Solved crashing issue in post password when password window title is
// more than 80
// [Files] PostMgmtExt.c
// 
// 14    5/03/14 4:04p Premkumara
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
// 13    2/11/14 8:21p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 12    12/05/13 10:57a Premkumara
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
// 11    9/18/13 7:09a Arunsb
// [TAG]	EIP135029, 136209
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	Password popup window displayed with post messages
// [Root Cause]	Since ClearScreen is commented, dorealflushlines displays
// the previous saved post messages also
// [Solution]	ClearScreen uncommented
// [Files]	postmgmtext.c
// 
// 10    3/16/13 2:16a Rajashakerg
// [TAG]  		EIP111479 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BIOS dialog box is crashed with special
// monitor(160,53,1280*1024)
// [RootCause]  	DesiredTextMode was not set properly.
// [Solution]  	Provided proper mode number while setting text mode.
// [Files]  		postmgmtext.c, Ezport\stylecommon.c,
// EzportPlus\stylecommon.c, Legacy\stylecommon.c
// 
// 9     10/19/12 6:28a Arunsb
// [Issue] - Screen is not cleared fully while displaying logo at (0,0)
// position in post screen.
// [Solution] - Clearing whole graphics screen while drawing logo at (0,0)
// co-ordinates
// 
// 3     10/19/12 5:28a Premkumara
// [Issue] - Screen is not cleared fully while displaying log at (0,0)
// position in post screen
// [Solution] - Clearing complete screen while drawing logo at (0,0)
// co-ordinates
// 
// 2     10/10/12 12:37p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     9/17/12 6:10a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 4     8/29/12 8:30a Premkumara
// [TAG]  		EIP 91364
// [Category]  	Improvement
// [Description]  	Token to disable the Cursor of TSE Password Dialog
// [Files]  		AMITSE.sdl, CommonHelper.c, Postmgmtext.c, PopupPassword.c,
// PopupString.c
// 
// 3     5/28/12 11:27a Premkumara
// [TAG]  		EIP88912
// [Category]  	Improvement
// [Description]  	On password window display the softkbd with only with
// valid key's
// [Files]  		CommonHelper.c, Postmgmtext.c, Mouse.c, PopupPassword.c
// 
// 2     12/08/11 1:06p Rajashakerg
// [TAG]  		EIP75379 
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Postmgmtext.c, Uefi21Wapper.c
// 
// 1     12/08/11 4:54a Arunsb
// EIP63190 => Moving password support from TSELite to BootOnly
// 
// 18    11/30/11 11:26a Premkumara
// [TAG]  		EIP67695
// [Category]  	Improvement
// [Description]  	No cursor visible in setup, while editing text input
// box
// [Files]  		Buffer.c, Postmgmtext.c, PopupString.c, PopupPassword.c
// 
// 17    11/22/11 5:33a Rajashakerg
// [TAG]  		EIP62763
// [Description]  	Removed wanted mouseinit before drawing password window
// at post.
// 
// 16    11/22/11 12:13a Premkumara
// [TAG]  		EIP70175
// [Category]  	Improvement
// [Description]  	Color of Password Validation for TSE and  GTSE
// [Files]  		CommonHelper.c, postmgmtext.c
// 
// 15    11/20/11 8:16a Rajashakerg
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
// 14    11/20/11 8:08a Premkumara
// [TAG]  		EIP70175
// [Category]  	Improvement
// [Description]  	Color of PopupPassword Window to validate password in
// GTSE style
// [Files]  	                CommonHelper.c, postmgmtext.c, minisetup.h
// 
// 13    8/26/11 6:46a Arunsb
// [TAG]  		EIP66211
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Password window hangs while pressing ESC
// [RootCause]  	If status is not equals success then TSE hangs the
// system.
// [Solution]  	If password window is time out then TSE will hang.
// If ESC pressed for password window then that try wont taken
// into account.
// [Files]  		postmgmtext.c
// 
// 12    6/24/11 9:35a Arunsb
// [TAG]  		EIP62754
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Time out not occurring in password popup window
// [RootCause]  	Timer event was set only for the first try in consecutive
// tries
//                                 event not created
// [Solution]  	If time out occurs in first try then TSE wont try for next
// iteration to get password.
//                                 TSE will report error and waits upto
// restarting the system.
// 
// [Files]  		postmgmtext.c
// 
// 11    6/08/11 11:26p Arunsb
// [TAG]  		EIP59138
// [Category]  	Improvement
// [Description]  	TSE expects extra key on the last wrong password retry
// [Files]  		postmgmtext.c
// 
// 10    3/28/11 9:25p Madhans
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
// 9     1/10/11 3:59p Mallikarjunanv
// [TAG]  		EIP51621
// [Description]  	Updated with respect to pressing ESC in password dialog
// box while entring to setup
// 
// 8     1/07/11 12:42a Mallikarjunanv
// [TAG]  		EIP51621
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	pressing ESC in password dialog makes system hang
// [RootCause]  	While entering password to boot to setup ESC key is not
// handled properly
// [Solution]  	Fixed the issue by handling the ESC key properly. 
// [Files]  		postmgmtext.c
// 
// 7     10/27/10 3:14p Madhans
// [TAG]    	EIP44886
// [Category]	Defect
// [Symptom]	If the SETUP_PASSWORD_LENGTH Changed to smaller then while
// entering Invalid Password in POST causes
// Error message printed outside of the box.
// [RootCause] The Boxsize is depending on Max Password length
// [Solution]	Boxsize is desided on Maximum of ErrorString or
// PasswordLength
// [Files]		postmgmtext.c
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/26/10 8:56p Madhans
// EIP-28501: fix for the issue for validating password using scan code 
// 
// 4     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 7     2/25/10 12:27p Madhans
// EIP 35391 To resolve the Get Password Window if it is called second
// time.
// 
// 5     2/19/10 8:19a Mallikarjunanv
// updated year in copyright message
// 
// 4     2/04/10 11:17p Madhans
// Mouse support related code optimized
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
// 2     5/19/09 6:32p Madhans
// DoRealFlushLines added to avoid the image overriding during post if
// password set
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
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		PostMgmtExt.c
//
// Description:	This file contains code extended post management operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

////////////////////////////////////////////////////////////////////
//		Function Declarations
////////////////////////////////////////////////////////////////////
//EIP-70175 Set Password Popup Window and PopupTextBox color
UINT8			GetPasswordPopupTextBoxColor (VOID);
UINT8 		GetPasswordPopupWindowColor (VOID);
UINT8 		GetPasswordReportInboxcolor (VOID);
BOOLEAN		IsMouseSupported (VOID);
BOOLEAN 		IsSoftKbdSupported (VOID);
VOID 			SetPwdKeyboardLayout (VOID);//EIP-88912
VOID 			ResetPwdKeyboardLayout (VOID);//EIP-88912
BOOLEAN 		IsTSECursorSupport (); //EIP-91364
void 			ClearGrphxScreen (void);
BOOLEAN  IsTSEMultilineControlSupported (VOID); //EIP-135665 Multiline support for Password and String control
EFI_STATUS SaveCurrentTextGOP ( UINTN *currenttextModeCols, UINTN *currenttextModeRows, UINT32 *currentGOPMode );
EFI_STATUS RestoreTextGOPMode ( UINTN prevTextModeCols, UINTN prevTextModeRows, UINT32 prevGOPMode );
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetSystemAccessValue
//
// Description:	function to set the system access  Value
//
// Input:	UINT8 sysAccessValue
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetSystemAccessValue(UINT8 sysAccessValue)
{
	EFI_GUID sysAccessGuid = SYSTEM_ACCESS_GUID;
	if(NoVarStoreSupport())
	{
		NoVarStoreUpdateSystemAccess(sysAccessValue);
	}
	else
		VarSetNvramName( L"SystemAccess", &sysAccessGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &sysAccessValue, sizeof(sysAccessValue) );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetPasswordType
//
// Description:	function to set the type of password
//
// Input:	UINT32 PasswordType
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetPasswordType( UINT32 PasswordType )
{
	UINT8 sysAccessValue = SYSTEM_PASSWORD_ADMIN;

	gPasswordType = PasswordType;

	if ( gPasswordType == AMI_PASSWORD_USER )
		sysAccessValue = SYSTEM_PASSWORD_USER;

	if ( gPasswordType != AMI_PASSWORD_NONE )
	{
		if(ItkSupport())
		{
			SetSystemAccessValueItk(sysAccessValue);
		}
		else
		{	
			SetSystemAccessValue(sysAccessValue);
		}
	}

	return;
}
/*Removed from BootOnly
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckEnableQuietBoot
//
// Description:	Function to check the quick boot enable option
//
// Input:	void
//
// Output:	void
//
// Notes		:	if NVRAM variable field AMISilentBoot = 0, then disable silent
//					mode else enable In case of error reading the Setup variable,
//					then return as silent boot disable
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CheckEnableQuietBoot( VOID )
{
#ifndef STANDALONE_APPLICATION
	if(ItkSupport())
	    gQuietBoot = TRUE;
	else
	{
		UINT8 *setupvar=NULL;
		UINT8 *setup=NULL;
		UINTN size = 0;
		UINTN offset;
	
		GetAMITSEVariable((AMITSESETUP**)&setup,&setupvar,&size);
	
		offset = STRUCT_OFFSET( AMITSESETUP, AMISilentBoot );
		if ( ( setup == NULL ) || ( size < offset ) )
			gQuietBoot = FALSE;
		else
			gQuietBoot = (BOOLEAN)setup[offset];
	
		if(setupvar)
			MemFreePointer( (VOID **)&setupvar );
		else
			MemFreePointer( (VOID **)&setup );
	}
#endif //#ifndef STANDALONE_APPLICATION
}
*/
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckSystemPassword
//
// Description:	Function to check the system password
//
// Input:	UINT32 EmptyPasswordType, UINTN *NoOfRetries, UINTN *TimeOut
//
// Output:	PasswordCheck
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 CheckSystemPassword(UINT32 EmptyPasswordType, UINTN *NoOfRetries, UINTN *TimeOut)
{
	UINTN PasswordCheck = AMI_PASSWORD_NONE;
	UINTN CurrXPos, CurrYPos;
	CHAR16 *PasswordEntered;
	UINT32 PasswordInstalled;
	SCREEN_BUFFER *TempScreenBuffer = NULL;
	CHAR16 *BoxStr=NULL;
	UINTN BoxLength = TsePasswordLength;

	UINTN currenttextModeCols = 0, currenttextModeRows = 0;
	UINT32 currentGOPMode = 0;

	EFI_STATUS Status = EFI_SUCCESS;
	
	EFI_GUID AmitsePasswordPromptEnterGuid = AMITSE_PASSWORD_PROMPT_ENTER_GUID;
	EFI_GUID AmitsePasswordPromptExitGuid = AMITSE_PASSWORD_PROMPT_EXIT_GUID;
	EFI_GUID AmitseUserPasswordValidGuid = AMITSE_USER_PASSWORD_VALID_GUID;
	EFI_GUID AmitseAdminPasswordValidGuid = AMITSE_ADMIN_PASSWORD_VALID_GUID;
	EFI_GUID AmitseInvalidPasswordGuid = AMITSE_INVALID_PASSWORD_GUID;

    EfiLibNamedEventSignal (&AmitsePasswordPromptEnterGuid);
	// Report the Status code DXE_SETUP_VERIFYING_PASSWORD
	EfiLibReportStatusCode(EFI_PROGRESS_CODE, DXE_SETUP_VERIFYING_PASSWORD,0,NULL,NULL);

    CheckForKeyHook( (EFI_EVENT)NULL, NULL );
	if( IsMouseSupported() && IsSoftKbdSupported())
    	CheckForClickHook( (EFI_EVENT)NULL, NULL );//EIP 62763 : Checking for mouse and softkbd.

	gST->ConIn->Reset( gST->ConIn, FALSE );

    // Copy the contents of Active buffer so password code can use it
	TempScreenBuffer = EfiLibAllocateZeroPool( sizeof(SCREEN_BUFFER) );
	if(TempScreenBuffer != NULL)
		MemCopy(TempScreenBuffer, gActiveBuffer, sizeof(SCREEN_BUFFER));

    BoxStr = HiiGetString( gHiiHandle, STRING_TOKEN(STR_ERROR_PSWD));
    if ( BoxStr ){
        if ((TestPrintLength( BoxStr ) / NG_SIZE) > BoxLength ){
            BoxLength = TestPrintLength( BoxStr ) / NG_SIZE;
        }
    }
    MemFreePointer((VOID**) &BoxStr );

	SaveCurrentTextGOP (&currenttextModeCols, &currenttextModeRows, &currentGOPMode);

    //Draw password window
    _DrawPasswordWindow(STRING_TOKEN(STR_PASSWORD_PROMPT), BoxLength, &CurrXPos, &CurrYPos);

    PasswordEntered = EfiLibAllocatePool((TsePasswordLength + 1)*sizeof(CHAR16));
    PasswordInstalled = PasswordCheckInstalled();
    PasswordCheck = AMI_PASSWORD_NONE;

    //Give retries based on NoOfRetries
    while(*NoOfRetries)
    {
	//EIP:51621 Handling ESC key for the the input password
		Status = _GetPassword (PasswordEntered, TsePasswordLength, CurrXPos, CurrYPos, TimeOut);
		if (EFI_ABORTED == Status)		//Status should be aborted, success or timeout. If time out we should not go for another iteration
		{								//If user presses ESC TSE handle that as invalid case so let it for another iteration.	
			continue;					
		}
		else if (EFI_TIMEOUT == Status)
		{
			break;						//EIP 62754; Breaking if time out occurs
		}
        PasswordCheck = PasswordAuthenticate( PasswordEntered );
        PasswordCheck &= PasswordInstalled;

        if((PasswordEntered[0] == L'\0') && (AMI_PASSWORD_NONE == PasswordCheck))
        {
            //Honour EmptyPasswordType
            if(
                (!(PasswordInstalled & AMI_PASSWORD_USER ))&&
                (EmptyPasswordType & AMI_PASSWORD_USER)
                )
                //PasswordCheck = AMI_PASSWORD_USER;
                PasswordCheck = AMI_PASSWORD_NONE;
            if(
                (!(PasswordInstalled & AMI_PASSWORD_ADMIN ))&&
                (EmptyPasswordType & AMI_PASSWORD_ADMIN)
                )
                PasswordCheck = AMI_PASSWORD_ADMIN;
        }

        if(AMI_PASSWORD_NONE != PasswordCheck)
            break;
        else
        {
            if (1 == *NoOfRetries) // Do not wait for key if it is the lastest try
                _ReportInBox( TsePasswordLength, STRING_TOKEN(STR_ERROR_PSWD), CurrXPos, CurrYPos, FALSE);
            else
                _ReportInBox( TsePasswordLength, STRING_TOKEN(STR_ERROR_PSWD), CurrXPos, CurrYPos, TRUE);
        }

        (*NoOfRetries)--;
    }

    MemFreePointer((VOID **)&PasswordEntered);

    if(AMI_PASSWORD_NONE == PasswordCheck)
    {
        EfiLibNamedEventSignal (&AmitseInvalidPasswordGuid);
		EfiLibReportStatusCode(EFI_ERROR_CODE| EFI_ERROR_MAJOR, DXE_INVALID_PASSWORD,0,NULL,NULL);

        //Report Invalid password
        _ReportInBox( TsePasswordLength, STRING_TOKEN(STR_ERROR_PSWD), CurrXPos, CurrYPos, FALSE);
    }
    else
    {
        MouseStop();
    	ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );
		DoRealFlushLines();
        MouseRefresh();

		if(IsMouseSupported()&& IsSoftKbdSupported())//Initializing the mouse at post when mouse and softkbd present
			MouseInit();

        if (!( PasswordInstalled & AMI_PASSWORD_ADMIN ))
		    PasswordCheck = AMI_PASSWORD_ADMIN;
	    SetPasswordType( (UINT32)PasswordCheck );

      	if(AMI_PASSWORD_ADMIN == PasswordCheck)
    		EfiLibNamedEventSignal (&AmitseAdminPasswordValidGuid);

    	if(AMI_PASSWORD_USER == PasswordCheck)
		    EfiLibNamedEventSignal (&AmitseUserPasswordValidGuid);
    }

	RestoreTextGOPMode (currenttextModeCols, currenttextModeRows, currentGOPMode);
    EfiLibNamedEventSignal (&AmitsePasswordPromptExitGuid);

   	//Copy the original active buffer contents
	if(TempScreenBuffer != NULL)
	{
		MemCopy(gActiveBuffer, TempScreenBuffer, sizeof(SCREEN_BUFFER));
		MemFreePointer((VOID **) &TempScreenBuffer);
	}
	return ((UINT32)PasswordCheck);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DrawPasswordWindow
//
// Description:	Function to draw password window with attributes
//
// Input:	UINT16 PromptToken, UINTN PasswordLength, UINTN *CurrXPos, UINTN *CurrYPos
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DrawPasswordWindow(UINT16 PromptToken, UINTN PasswordLength, UINTN *CurrXPos, UINTN *CurrYPos)
{
	UINTN	DlogWidth = PasswordLength + 4;
	UINTN Height=1;
	CHAR16 *PasswordPrompt;

#ifndef STANDALONE_APPLICATION
    if ( gConsoleControl != NULL )
		gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenText );
#endif

    //Set desired Mode.
#if !APTIO_4_00
    SetDesiredTextMode();
#else
	//  In Aptio use the Text mode as is it in post screen 
	if(gST->ConOut!=NULL)
	{
		UINTN Rows, Cols;
		if(EFI_ERROR(gST->ConOut->QueryMode( gST->ConOut, gST->ConOut->Mode->Mode, &Cols, &Rows )))
		{ 
			gMaxRows = STYLE_STD_MAX_ROWS; 
			gMaxCols = STYLE_STD_MAX_COLS; 
		}
		else if ((gMaxRows != Rows) || (gMaxCols != Cols))
 		{
			//Setting the Desired text mode as is it in post screen 
		  	SetDesiredTextMode ();
 		}

	}
	else
	{ 
		gMaxRows = STYLE_STD_MAX_ROWS; 
		gMaxCols = STYLE_STD_MAX_COLS; 
	}
#endif

	if(IsMouseSupported()&& IsSoftKbdSupported())//Initializing the mouse at post when mouse and softkbd present
		MouseInit();

    MouseStop();
	// Clear the Screen
	ClearGrphxScreen ();//To clear screen while drawing logo at (0,0) co-ordinates
//	ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );
	DoRealFlushLines();
    MouseRefresh();

	PasswordPrompt = HiiGetString( gHiiHandle, PromptToken);
	if ( PasswordPrompt != NULL )
    {
        if ( (TestPrintLength(PasswordPrompt) / NG_SIZE +6) > DlogWidth )
            DlogWidth = TestPrintLength(PasswordPrompt) / NG_SIZE +6;
    }

	if (DlogWidth >= (gMaxCols-2)) //EIP-135665 If string is more than gMaxCols 80/100
	{
		if ( IsTSEMultilineControlSupported() ) //If multiline supported
			{
				Height=(DlogWidth / (gMaxCols-2))+(((DlogWidth % (gMaxCols-2)) > 0)?1:0);
				DlogWidth = gMaxCols-2;
			}
		else
			{
				DlogWidth = gMaxCols-2;
				PasswordPrompt[DlogWidth-4]=L'\0';
				PasswordPrompt[DlogWidth-5]=L'.';
				PasswordPrompt[DlogWidth-6]=L'.';
				PasswordPrompt[DlogWidth-7]=L'.';
			}
	}

	*CurrYPos = (gMaxRows - 5) / 2;
	*CurrXPos = (gMaxCols-2 - DlogWidth) / 2;
	
	//EIP-70175 Set Password Window color
	//DrawWindow( *CurrXPos, *CurrYPos, DlogWidth, 5, EFI_BACKGROUND_BLUE | EFI_WHITE, TRUE, FALSE );
	DrawWindow( *CurrXPos, *CurrYPos, DlogWidth, 4+Height, GetPasswordPopupWindowColor(), TRUE, FALSE );	
	
	if ( PasswordPrompt != NULL )
	{
		if ( IsTSEMultilineControlSupported() ) //If multiline supported
			DrawMultiLineStringWithAttribute ((*CurrXPos)+2, *CurrYPos, DlogWidth-3, Height, PasswordPrompt, 0);
		else
			DrawStringJustified( 0, gMaxCols-2, *CurrYPos, JUSTIFY_CENTER, PasswordPrompt );
	}
	MemFreePointer( (VOID **)&PasswordPrompt );

    //Record position of the Box
   *CurrXPos = ((gMaxCols - DlogWidth) / 2)+1; //EIP-173320 HDD password prompt issue
	*CurrYPos += Height+1;

	FlushLines( *CurrYPos - Height-1, *CurrYPos + 2);
    MouseStop();
	DoRealFlushLines();
    MouseRefresh();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ReportInBox
//
// Description:	Function to report using Box
//
// Input:	UINTN PasswordLength, UINT16 BoxToken, UINTN CurrXPos,
//					UINTN CurrYPos, BOOLEAN bWaitForReturn
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _ReportInBox(
        UINTN PasswordLength,
        UINT16 BoxToken,
        UINTN CurrXPos,
        UINTN CurrYPos,
        BOOLEAN bWaitForReturn
        )
{
    CHAR16 *BoxStr=NULL;
   	EFI_INPUT_KEY Key;

	//Draw Box
	//EIP-70175 Set Password ReportInbox color
    //DrawBox( CurrXPos, CurrYPos,  PasswordLength, 1, EFI_BACKGROUND_BLUE | EFI_WHITE );
	DrawBox( CurrXPos, CurrYPos,  PasswordLength, 1, GetPasswordReportInboxcolor());
	
    //Draw Box string
    if(BoxToken != INVALID_TOKEN)
    {
        BoxStr = HiiGetString( gHiiHandle, BoxToken );
        DrawString( CurrXPos, CurrYPos, BoxStr);
    }
	 
	 SetPwdKeyboardLayout();//EIP-88912
    TSEStringReadLoopEntryHook();

    FlushLines( CurrYPos - 2, CurrYPos + 2 );
    MouseStop();
	DoRealFlushLines();
    MouseRefresh();

    if(bWaitForReturn)
    {
        MemFillUINT16Buffer(BoxStr, (TestPrintLength(BoxStr)/ NG_SIZE), L' ');

        Key.UnicodeChar = 0;
        do
	    {
     		gST->ConIn->ReadKeyStroke( gST->ConIn, &Key );
       	} while( Key.UnicodeChar != CHAR_CARRIAGE_RETURN );

        DrawString( CurrXPos, CurrYPos, BoxStr);
        MemFreePointer((VOID **) &BoxStr);
    }

   TSEStringReadLoopExitHook();
	ResetPwdKeyboardLayout();//EIP-88912

    MemFreePointer((VOID **)&BoxStr);
}

VOID SetPwdTimeOut( EFI_EVENT Event, BOOLEAN *timeout )
{
	if ( timeout != NULL )
		*timeout = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_GetPassword
//
// Description:	Function to get password from the user
//
// Input:	CHAR16 *PasswordEntered, UINTN PasswordLength, UINTN CurrXPos,
//					UINTN CurrYPos, UINTN *pTimeOut
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetPassword(
        CHAR16 *PasswordEntered,
        UINTN PasswordLength,
        UINTN CurrXPos,
        UINTN CurrYPos,
        UINTN *pTimeOut
        )
{
   	EFI_INPUT_KEY Key = {0,0};
	UINTN StrIndex;
    CHAR16 *StrStar;
    UINTN i;
    volatile BOOLEAN bTimeOut = FALSE;
    UINTN TimeOutValue;
    EFI_EVENT timer;
    EFI_STATUS Status;
    AMI_EFI_KEY_DATA    KeyData;

    MemSet( PasswordEntered, (PasswordLength + 1)*sizeof(CHAR16), 0 );
    StrStar = EfiLibAllocatePool((PasswordLength + 1)*sizeof(CHAR16));
    StrIndex = 0;
	
	//EIP-70175 Set Password PopupTextBox color
    //DrawBox( CurrXPos, CurrYPos,  PasswordLength, 1, EFI_BACKGROUND_LIGHTGRAY | EFI_BLUE );
	DrawBox( CurrXPos, CurrYPos,  PasswordLength, 1, GetPasswordPopupTextBoxColor() );	
	
    FlushLines( CurrYPos, CurrYPos );
    MouseStop();
	DoRealFlushLines();
    MouseRefresh();

	SetPwdKeyboardLayout();//EIP-88912
   TSEStringReadLoopEntryHook();

	if (IsTSECursorSupport()) //EIP-91364
	{
		gST->ConOut->SetCursorPosition( gST->ConOut, CurrXPos, CurrYPos);	//EIP:67695 Cursor support for msg boxes
		gST->ConOut->EnableCursor(gST->ConOut, TRUE);//EIP:67695 Enable Cursor support for msg boxes
	}
	do
	{
        TimeOutValue = pTimeOut ? *pTimeOut : 0;

        if(TimeOutValue)
        {
            timer = NULL;
            Status = TimerCreateTimer( &timer, SetPwdTimeOut, (VOID *)&bTimeOut, TimerRelative, TimeOutValue * TIMER_ONE_SECOND, EFI_TPL_NOTIFY );
        }

        // While the timeout has not expired
        while ( ! bTimeOut )
	    {
			Status = AMIReadKeyStroke(&Key,&KeyData);
            if ( !(EFI_ERROR(Status)) )
                break;
        }

        if(TimeOutValue)
            TimerStopTimer( &timer );

        if(bTimeOut)
        {
            Status = gST->ConIn->Reset( gST->ConIn, FALSE );
            MemFreePointer((VOID **)&StrStar);
            PasswordEntered[0] = L'\0';
            break;
        }

		switch (Key.UnicodeChar)
		{
			case CHAR_NULL:
				if (Key.ScanCode == SCAN_ESC) 
            {
      			Status = gST->ConIn->Reset( gST->ConIn, FALSE );
					MemFreePointer((VOID **)&StrStar);
					PasswordEntered[0] = L'\0';
					TSEStringReadLoopExitHook();
					ResetPwdKeyboardLayout();//EIP-88912
				   return EFI_ABORTED;
            }
				if (Key.ScanCode != SCAN_NULL) {
					if(HelperIsPasswordCharValid(&Key,&KeyData,StrIndex,PasswordLength,&PasswordEntered[StrIndex]) == EFI_SUCCESS)
						StrIndex++;
				}
				else {
					InvalidActionHookHook();
				}
                break;

			case CHAR_CARRIAGE_RETURN:
				Status = gST->ConIn->Reset( gST->ConIn, FALSE );
            MemFreePointer((VOID **)&StrStar);
            TSEStringReadLoopExitHook();
				ResetPwdKeyboardLayout();//EIP-88912
            return EFI_SUCCESS;

			case CHAR_BACKSPACE:
				if ( StrIndex != 0 )
					PasswordEntered[--StrIndex] = L'\0';	
				break;
			
			default:
				if(HelperIsPasswordCharValid(&Key,&KeyData,StrIndex,PasswordLength,&PasswordEntered[StrIndex]) == EFI_SUCCESS)
					StrIndex++;
				break; 
		}
		if ( StrIndex > PasswordLength  ) {
			InvalidActionHookHook();
		}
		//Draw stars for entered characters
		for ( i = 0; i < PasswordLength; i++ )
			StrStar[i] = (i<StrIndex) ? L'*': L' ';
		StrStar[PasswordLength] = L'\0';

		DrawString( CurrXPos, CurrYPos, StrStar );
		FlushLines( CurrYPos, CurrYPos );
		MouseStop();
		DoRealFlushLines();

		if (IsTSECursorSupport()) //EIP-91364
		{
			gST->ConOut->SetCursorPosition( gST->ConOut, ((PasswordLength!=StrIndex)?(CurrXPos + StrIndex):(CurrXPos + StrIndex-1)), CurrYPos);	//EIP:67695 For restricting the cursor within the limit
			gST->ConOut->EnableCursor(gST->ConOut, TRUE);		//EIP:67695 Enable Cursor support for msg boxes
		}
		MouseRefresh();
	}
	while( 1 );

	TSEStringReadLoopExitHook();
	ResetPwdKeyboardLayout();//EIP-88912

	//EIP-75379 Suppress the warnings from static code analyzer
	if (pTimeOut)
    	*pTimeOut = 0;
    return EFI_TIMEOUT;
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
