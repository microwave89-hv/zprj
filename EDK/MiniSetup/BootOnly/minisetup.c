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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/minisetup.c $
//
// $Author: Arunsb $
//
// $Revision: 15 $
//
// $Date: 5/08/14 9:16p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/minisetup.c $
// 
// 15    5/08/14 9:16p Arunsb
// [TAG]  			EIP162981
// [Category]  	Improvement
// [Description]  	Configuring default Password through SDL token.
// Made dependency with RT_ACCESS_SUPPORT_IN_HPKTOOL.
// 
// 14    5/02/14 8:41a Premkumara
// [TAG]  		EIP162981
// [Category]  	Improvement
// [Description]  	Configuring default Password through SDL token
// [Files]  		AMITSE.sdl, CommonHelper.c, Minisetup.c, TseAdvanced.c
// 
// 13    5/01/14 4:05p Premkumara
// [TAG]  		EIP149734 
// [Category]  	Improvement
// [Description]  	Softkbd should not display in BBS menu
// [Files]  		Minisetup.c
// 
// 12    10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 13    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 10    6/25/12 5:39p Arunsb
// [TAG]  		EIP93524
// [Category]  	Improvement
// [Description]  	Invalidate the BGRT table when boot device launched
// from BBS popup or from shell or launched as second boot device
// [Files]  		boot.c and minisetup.c
// 
// 9     4/27/12 5:16a Rajashakerg
// [TAG]  		EIP82804
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hangs at password prompt when Administrator password
// set.
// [RootCause]  	When admin passwor set, in the absence of built in efi
// shell and no usb connected to SUT. IF we wont select any option at post
// we will try to launch setup but before launcing setup mouse is
// destroyed.
// [Solution]  	Fixed the issue by invoking the Mouseinit() for a specail
// case of admin password set and when no boot option to boot.
// [Files]  		minisetup.c
// 
// 8     4/27/12 2:09a Rajashakerg
// [TAG]  		EIP88454 
// [Category]  	Improvement
// [Description]  	 SoftKbd activate functionality in BBS Menu by AMITSE
// [Files]  		minisetup.c
// 
// 7     6/20/11 10:33a Arunsb
// [TAG]           EIP54861
// [Category]      Improvement
// [Description]   Updating string token value dynamically for Title Bar
// and Copyright messages.
// [Files]         minisetup.c and tselite\minisetupext.c
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 8     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 7     2/04/10 11:20p Madhans
// Post Status update for BBS popup.
// 
// 6     1/29/10 4:37p Madhans
// To not to depend on ConsoleControl and ConOut.
// 
// 5     1/09/10 5:16a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     6/24/09 6:09p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
// 
// 3     6/23/09 6:56p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:12p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 5     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     3/31/09 3:40p Madhans
// MinisetupLoopInit is moved to minisetup.c
// 
// 3     2/05/09 5:19p Madhans
// PostMgrStatus interface added.
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
// Name:		MINISETUP.C
//
// Description:	This file contains code for entrypoint and setup loop
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION
// from Resources.c
#if TSE_USE_EDK_LIBRARY
EFI_STATUS LoadStrings(
	EFI_HANDLE ImageHandle, /*EFI_HII_HANDLE*/VOID* *pHiiHandle
);
#endif
#endif

#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION || TSE_FOR_64BIT
EFI_STATUS ReadImageResource(
	EFI_HANDLE ImageHandle, EFI_GUID *pGuid, 
	VOID **ppData, UINTN *pDataSize
);
#endif

//Internal function definitions
#if APTIO_4_00 != 1 && SETUP_USE_GUIDED_SECTION !=1
EFI_STATUS InitMiniSetupStrings( VOID );
#endif

EFI_DRIVER_ENTRY_POINT (MiniSetupApplication)

/////////////////////////////////////////////////////////
//	FUNCTION DECLARATION
////////////////////////////////////////////////////////
VOID InitGlobalPointers( VOID );
VOID UpdategScreenParams (VOID);
VOID StopClickEvent(VOID);
AMI_SET_VERSION(TSE_MAJOR,TSE_MINOR,TSE_BUILD,TSE);
VOID        InvalidateStatusInBgrtWrapper (VOID);

//EIP 162981 Providing defaults through sdl tokens
BOOLEAN 	TseDefaultSetupPasswordSupported(VOID);
EFI_STATUS 	SetDefaultPassword (VOID);

#define	TSE_FIRST_BOOT_GUID	\
	{ 0xc5912ed9, 0x83c2, 0x4bff, 0x99, 0x36, 0x23, 0x1f, 0xeb, 0x85, 0xf3, 0xe8 }
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MiniSetupApplication
//
// Description:	This function is the entry point for TSE. It loads
//              resources like strings and setup-data. It registers
//              notification for console protocols. It Installs TSE
//              protocols.
//
// Input:		EFI_HANDLE ImageHandle
//              EFI_SYSTEM_TABLE *SystemTable
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MiniSetupApplication (
		EFI_HANDLE ImageHandle,
		EFI_SYSTEM_TABLE *SystemTable )
{
	EFI_STATUS	Status;
    UINTN 		OptionSize = 0;
    void 		*FirstBoot = NULL;
    EFI_GUID	TseFirstBootGuid = TSE_FIRST_BOOT_GUID;

	gImageHandle = ImageHandle;

	EfiInitializeDriverLib ( ImageHandle, SystemTable );

	RUNTIME_DEBUG( L"entry" );

#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION
#if TSE_USE_EDK_LIBRARY
	LoadStrings(ImageHandle,&gHiiHandle);
#else
	LoadStrings(ImageHandle,(EFI_HII_HANDLE*)&gHiiHandle);
#endif
#else
#ifdef USE_DEPRICATED_INTERFACE
	// Read in the strings from the GUIDed section
	Status = LoadStringsDriverLib( ImageHandle, &STRING_ARRAY_NAME );
	if ( EFI_ERROR( Status ) )
	{
		return Status;
	}
#endif

	Status = InitMiniSetupStrings();
	if ( EFI_ERROR( Status ) )
	{
		return Status;
	}
#endif

	Status = HiiInitializeProtocol();
	if ( EFI_ERROR ( Status ) )
		return Status;

	// initialize screen buffer
	RUNTIME_DEBUG( L"screen" );
	InitializeScreenBuffer( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );

	RUNTIME_DEBUG( L"guid" );

	Status = InitApplicationData(ImageHandle);
	if ( EFI_ERROR( Status ) )
	{
		return MiniSetupExit( Status );
	}

	RUNTIME_DEBUG( L"globals" );
	InitGlobalPointers();
    UpdategScreenParams ();

	Status = VarLoadVariables( (VOID **)&gVariableList, NULL );
	if ( EFI_ERROR( Status ) )
	{
		return Status;
	}

    MinisetupDriverEntryHookHook();

	gPostStatus = TSE_POST_STATUS_BEFORE_POST_SCREEN;

#ifndef STANDALONE_APPLICATION
	// Install our handshake protocol
	InstallProtocol();

	// Register any notification 'callbacks' that we need
	Status = RegisterNotification();
	if ( EFI_ERROR( Status ) )
		UninstallProtocol();
#else
	PostManagerHandshake();
#endif // STANDALONE_APPLICATION

    if (TseDefaultSetupPasswordSupported ())	//EIP 162981 Providing defaults through sdl tokens
    {
    	FirstBoot = (BOOT_OPTION *)VarGetNvramName (L"TseFirstBootFlag", &TseFirstBootGuid, NULL, &OptionSize);
    	if (NULL == FirstBoot)
    	{
    		SetDefaultPassword (); //Get default password, if any present in SDL, and set default pass to NVRAM EIP 162981
    		VarSetNvramName( L"TseFirstBootFlag", &TseFirstBootGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, &OptionSize, sizeof (OptionSize) );
    	}
    }
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MiniSetupExit
//
// Description:	This function is responsible for releasing the memory
//              allocated during MinisetuEntry(). It destroys the
//              application hierarchy; clears the memory used for
//              variables; clears the memory used for fixup of
//              setup-data.
//
// Input:		EFI_STATUS Status: Guideline status for MiniSetupExit
//              to return with.
//
// Output:		Return Status based on input status and errors that
//              occurred in library functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MiniSetupExit( EFI_STATUS Status )
{
	MiniSetupUIExit();

	if(gST->ConOut!=NULL)
	{
		gST->ConOut->Reset( gST->ConOut, FALSE );
		gST->ConOut->ClearScreen( gST->ConOut);
		gST->ConOut->EnableCursor( gST->ConOut, TRUE );
	}

	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoPopup
//
// Description:	This function runs the loop for Pop up boot menu.
//              This function is responsible for creating the list
//              box control. It also gathers actions and passes them
//              to list box control and initiates draw sequence.
//
// Input:		BOOT_FLOW *BootFlow: Ptr to BOOT_FLOW responsible for
//              the call.
//
// Output:		Return Status based on errors that occurred in
//              library functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DoPopup(BOOT_FLOW *BootFlow)
{
	EFI_STATUS Status = EFI_SUCCESS;

	gPostStatus = TSE_POST_STATUS_IN_BBS_POPUP;

	DoBbsPopupInit() ; 	//minisetupext.c

	if (gClickTimer) //EIP-149734 Stopping ClickEvent timer, if gClickTimer event is not stopped, before drawing BBS menu to avoid drawing softkbd if any mouse action happens during BBS menu
		StopClickEvent();

	//TSEStringReadLoopEntryHook();//EIP 88454 : Initializing the Softkbd for BBS popup menu 
	DrawPopupMenuHook() ;	//HookAnchor.c -> DrawBootOnlyBbsPopupMenu (minisetupext.c)
	BbsBootHook() ;		//HookAnchor.c -> BbsBoot (minisetupext.c)
	
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MainSetupLoopInit
//
// Description:	Main function that initializes the setup Loops.
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MainSetupLoopInit(VOID)
{
#ifndef STANDALONE_APPLICATION
    EFI_CONSOLE_CONTROL_SCREEN_MODE ScreenMode;
#endif
	EFI_GUID AmitseSetupEnterGuid = AMITSE_SETUP_ENTER_GUID;
	static int Initdone =0;

	if(Initdone)
	{
		EfiLibNamedEventSignal ( &AmitseSetupEnterGuid );
		return;
	}
	Initdone = 1;

#ifndef STANDALONE_APPLICATION
	if ( gConsoleControl != NULL )
	{
		gConsoleControl->GetMode(gConsoleControl, &ScreenMode, NULL, NULL);
		if(EfiConsoleControlScreenGraphics == ScreenMode)
		{
			gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenText );
			InvalidateStatusInBgrtWrapper ();					//EIP93524. Since mode changed invalidating status field in BGRT table. Usefull for boot from BBS Pop up.
		}
	}
#endif
	
	MouseInit();//EIP 82804 : Initiatializing the Mouse before prompting password
    ProcessEnterSetupHook();

     TSEUnlockHDD();			///Modified as a hook 

	EfiLibNamedEventSignal ( &AmitseSetupEnterGuid );
	// Report the Status code DXE_SETUP_START
	EfiLibReportStatusCode(EFI_PROGRESS_CODE, DXE_SETUP_START,0,NULL,NULL);
}

//EIP 162981 starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		GetDefaultPassword
//
// Description:		Getting default password from SDL token based on USER/ADMIN token
//
// Input:			UINT32, AMITSESETUP*
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetDefaultPasswordFromTokens (UINT32 PasswordType);
EFI_STATUS GetDefaultPassword (UINT32 PasswordInstalled, void **DefaultPassword)
{
	CHAR16 *adminPwd = NULL, *usrPwd = NULL;
	EFI_STATUS Status = EFI_NOT_FOUND;
	CHAR16 *tmpPasswd = NULL;
	
	if ((PasswordInstalled == AMI_PASSWORD_ADMIN) || (AMI_PASSWORD_NONE == PasswordInstalled))
	{
		usrPwd = GetDefaultPasswordFromTokens (AMI_PASSWORD_USER);
		if ((NULL != usrPwd) && (EfiStrCmp (usrPwd, L"\"\"")))
		{
			tmpPasswd =  (CHAR16 *)EfiLibAllocateZeroPool (sizeof (AMITSESETUP));
			if (NULL == tmpPasswd)
			{
				return EFI_OUT_OF_RESOURCES;
			}
			EfiStrCpy (tmpPasswd, usrPwd);
			PasswordEncodeHook (tmpPasswd, TsePasswordLength*sizeof(CHAR16));
			MemCopy (*DefaultPassword, tmpPasswd, TsePasswordLength*sizeof(CHAR16));
			MemFreePointer ((VOID **) &tmpPasswd);
			Status = EFI_SUCCESS;
		}
	}

	if ((PasswordInstalled == AMI_PASSWORD_USER) || (AMI_PASSWORD_NONE == PasswordInstalled))
	{
		adminPwd = GetDefaultPasswordFromTokens (AMI_PASSWORD_ADMIN);
		if ((NULL != adminPwd) && (EfiStrCmp (adminPwd, L"\"\"")))
		{
			tmpPasswd = (CHAR16 *) EfiLibAllocateZeroPool (sizeof (AMITSESETUP));
			if (NULL == tmpPasswd)
			{
				return EFI_OUT_OF_RESOURCES;
			}
			EfiStrCpy (tmpPasswd, adminPwd);
			PasswordEncodeHook (tmpPasswd, TsePasswordLength*sizeof(CHAR16));
			MemCopy ((CHAR16*)(*DefaultPassword) + TsePasswordLength, tmpPasswd, TsePasswordLength*sizeof(CHAR16));
			MemFreePointer ((VOID **) &tmpPasswd);			
			Status = EFI_SUCCESS;
		}
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		SetDefaultPassword
//
// Description:		Function to set defaults password in NVRAM, if any present in SDL
//
// Input:			void
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   TseRtAccessSupport (VOID);
EFI_STATUS SetDefaultPassword (VOID)
{
	UINTN 		size = 0;
	UINT32		Installed = AMI_PASSWORD_NONE;
	void 		*DefaultPassword = NULL;
	UINT32 		PasswordInstalled;
	EFI_STATUS  Status = EFI_SUCCESS;
	AMITSESETUP *pSetupVariable = (AMITSESETUP *)NULL;
    EFI_GUID 	amitsesetupGuid = AMITSESETUP_GUID;

	pSetupVariable = HelperGetVariable( VARIABLE_ID_AMITSESETUP, (CHAR16 *)NULL, (EFI_GUID *)NULL, NULL, &size );

	if(size < sizeof(AMITSESETUP))
	{
		pSetupVariable = (AMITSESETUP *) EfiLibAllocateZeroPool(sizeof(AMITSESETUP));
		if(gVariableList && (gVariableList[VARIABLE_ID_AMITSESETUP].Buffer))
			MemCopy( pSetupVariable, gVariableList[VARIABLE_ID_AMITSESETUP].Buffer, gVariableList[VARIABLE_ID_AMITSESETUP].Size );
      if (TseRtAccessSupport ())
      {
   		VarSetNvramName( L"AMITSESetup", &amitsesetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS, pSetupVariable, sizeof (AMITSESETUP));
      }
      else
      {
         VarSetNvramName( L"AMITSESetup", &amitsesetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, pSetupVariable, sizeof (AMITSESETUP));
      }  
//		VarSetNvram( VARIABLE_ID_AMITSESETUP, pSetupVariable, sizeof(AMITSESETUP));
	}
  	PasswordInstalled = PasswordCheckInstalled();
	
	if (AMI_PASSWORD_ANY == PasswordInstalled)
	{
		return EFI_ALREADY_STARTED;
	}
	
	Status = GetDefaultPassword (PasswordInstalled, &pSetupVariable);
	
	if (!EFI_ERROR (Status))
	{
      if (TseRtAccessSupport ())
      {
		   VarSetNvramName( L"AMITSESetup", &amitsesetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS, pSetupVariable, sizeof (AMITSESETUP));
      }
      else
      {
         VarSetNvramName( L"AMITSESetup", &amitsesetupGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, pSetupVariable, sizeof (AMITSESETUP));
      }
//		VarSetNvram( VARIABLE_ID_AMITSESETUP, pSetupVariable, sizeof(AMITSESETUP));
//		VarUpdateDefaults(VARIABLE_ID_AMITSESETUP);
	}
	return EFI_SUCCESS;
}
//EIP 162981 ends

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
