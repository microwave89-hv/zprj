//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/bootflowLib.c $
//
// $Author: Premkumara $
//
// $Revision: 8 $
//
// $Date: 8/28/14 8:42a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/bootflowLib.c $
// 
// 8     8/28/14 8:42a Premkumara
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
// 7     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     3/26/10 5:06p Madhans
// EIP 36704 : Fix for Making sure to make the Variable to NULL after it
// is Freed up.
// 
// 5     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:12a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/29/10 4:37p Madhans
// To not to depend on ConsoleControl and ConOut.
// 
// 4     10/12/09 4:11p Madhans
// //EIP 28577 : Fix to avoid "Checker: SIGN_EXTENSION"
// 
// 3     7/08/09 3:35p Madhans
// In Aptio use the Text mode as is it in post screen
// 
// 2     6/12/09 7:43p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:16p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:27p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/07/08 10:34a Arunkumars
// Stand alone application support for x64 and nt32
// 
// 1     7/09/07 1:29p Arunkumars
// - Added elink hooks for Logo, Password management and Control Keys
// customizations
//
//*****************************************************************//
//*****************************************************************//

#include "minisetup.h"
BOOLEAN 	IsMouseSupported(VOID);
BOOLEAN 	IsSoftKbdSupported(VOID);
static MSGBOX_DATA *_gBootFlowMsg = NULL;

VOID _BootFlowCancelTimer( EFI_EVENT Event, VOID *Context )
{
	if ( _gBootFlowMsg != NULL )
		gMsgBox.Destroy( _gBootFlowMsg, TRUE );

	_gBootFlowMsg = NULL;

	TimerStopTimer( &Event );
}

VOID _BootFlowShowMessageBox( BOOT_FLOW *bootFlowPtr )
{
	AMI_IFR_MSGBOX msgBox;
	CONTROL_INFO dummy;

#ifndef STANDALONE_APPLICATION
	if ( gConsoleControl != NULL )
		gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenText );
#endif

	if (gST->ConOut == NULL) // Headless system/NoVideo in BIOS
		return;

	gST->ConOut->Reset( gST->ConOut, FALSE );
#if !APTIO_4_00
    SetDesiredTextMode();
#else
	//  In Aptio use the Text mode as is it in post screen
	if(EFI_ERROR(gST->ConOut->QueryMode( gST->ConOut, gST->ConOut->Mode->Mode, &gMaxCols, &gMaxRows )))
	{ 
		gMaxRows = StyleGetStdMaxRows(); 
		gMaxCols = StyleGetStdMaxCols(); 
	}
#endif

	if(IsMouseSupported()&& IsSoftKbdSupported())//Initializing the mouse at post when mouse and softkbd present
		MouseInit();

	ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );

	MemSet( &msgBox, sizeof(msgBox), 0 );
	msgBox.Text = bootFlowPtr->MessageBoxToken;

	MemSet( &dummy, sizeof(dummy), 0 );
	dummy.ControlHandle = INVALID_HANDLE;
	dummy.ControlPtr = (VOID*)(UINTN)&msgBox;
	dummy.ControlFlags.ControlVisible = TRUE;

	gMsgBox.Create( &_gBootFlowMsg );
	if ( _gBootFlowMsg == NULL )
		return;

	gMsgBox.Initialize( _gBootFlowMsg, &dummy );
	gMsgBox.SetType( _gBootFlowMsg, MSGBOX_TYPE_NULL );
	gMsgBox.Draw( _gBootFlowMsg );

	if ( bootFlowPtr->MessageBoxTimeout != 0 )
	{
		EFI_EVENT Event;

		//EIP 28577 : Fix to avoid "Checker: SIGN_EXTENSION"
		TimerCreateTimer( &Event, _BootFlowCancelTimer, NULL,
			TimerRelative, MultU64x32( (UINT64)TIMER_ONE_SECOND, (UINT32) bootFlowPtr->MessageBoxTimeout ), EFI_TPL_CALLBACK );
	}
}

VOID _BootFlowSetActivePage( BOOT_FLOW *bootFlowPtr )
{
	PAGE_INFO *pageInfo;
	UINT32	i;

	for ( i = 0; i < gPages->PageCount; i++ )
	{
		pageInfo = (PAGE_INFO *)((UINTN)gSetupPkg + gPages->PageList[i]);
		if (
			( bootFlowPtr->PageClass == gPageIdInfo[pageInfo->PageIdIndex].PageClass ) &&
			( bootFlowPtr->PageSubClass == gPageIdInfo[pageInfo->PageIdIndex].PageSubClass ) &&
			( bootFlowPtr->PageFormID == pageInfo->PageFormID ) 
		   )
		{
			gEnterSetup = TRUE;
			gStartPage = i;
			break;
		}
	}

}

VOID _BootFlowSetActiveControl( BOOT_FLOW *bootFlowPtr )
{
	// select the control from the currently active page
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
