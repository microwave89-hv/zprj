//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2013, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/notify.c $
//
// $Author: Premkumara $
//
// $Revision: 46 $
//
// $Date: 8/28/14 8:35a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/notify.c $
// 
// 46    8/28/14 8:35a Premkumara
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
// 45    7/12/14 5:46p Arunsb
// [TAG]			EIP160126
// [Category]		Bug Fix
// [Severity:]		Normal
// [Symptom:]		When Softkbd Enabled, Post display gets delayed
// [Root Cause]	If softkbd enabled then TSE waits up to mouse
// notification.
// 				Mouse notification will happen next to installing conin so delayed.
// [Solution]		Mouse initialized only when softkbd present and password
// installed.
// 				Removed NOTIFY_MASK_MOUSE_DRIVER in SETUP_DELAY_LOGO_TILL_INPUT
// [Files]			CommonHelper.c and BootOnly\notify.c
// 
// 44    5/02/14 3:59a Premkumara
// [TAG]  		EIP151966
// [Category]  	Improvement
// [Description]  	Added the implementation for getting the BIOS build
// year dynamically 
// from TimeStamp.h file and updated the Build year in copyright message
// in both Setup and POST.
// [Files]  		style.c,style.c,style.c,notify.c,minisetupext.c,CommonHelper
// .c,
// AmiTSEStr.uni,AMITSE.mak
// 
// 43    5/02/14 12:05a Arunsb
// [TAG]  		EIP141066,141084,144118
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Keys in USB and PS2 are not working to enter into setup.
// [Solution]  	Hanlded ConsoleInHandle proplerly with ConsoleOutHandle
// when ConIn is available.
// [Files]  		Notify.c
// 
// 42    2/11/14 8:06p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 41    11/26/13 7:57a Premkumara
// [TAG]  		EIP141066,141084,144118
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Keys in USB and PS2 are not working to enter into setup.
// [Solution]  	Hanlded ConsoleInHandle proplerly with ConsoleOutHandle
// when ConIn is available.
// [Files]  		Notify.c
// 
// 40    5/23/13 12:56a Arunsb
// [TAG]  		EIP103962
// [Description]  	Reverting the notify TPL from EFI_TPL_NOTIFY to
// EFI_TPL_CALLBACK
// [Files]  		notify.c
// 
// 39    4/17/13 1:11a Arunsb
// [TAG]  		EIP121116 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	AMI small logo has damage on POST and boot
// [RootCause]  	When system starts with higher text resolution more than
// 100*31 then TSE not setting proper text mode
// [Solution]  	Mode set properly
// [Files]  		notify.c and postmgmt.c
// 
// 38    3/16/13 4:00a Rajashakerg
// [TAG]  		EIP107221 
// [Category]  	Improvement
// [Description]  	Logo disappear after HDD password verified
// [Files]  		CommonHelper.c, notify.c, minisetupext.c
// 
// 37    3/08/13 2:57a Premkumara
// [TAG]  		EIP116451
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When User password alone is set, Setup gets hang in post
// while validating User Password. 
// [RootCause]  	ConsoleInHandle is  NULL while validating password.
// [Solution]  	Setting gST->ConsoleInHandle with "gST->ConsoleInHandle"
// to locate the Keycode protocol
// [Files]  		nofify.c
// 
// 36    1/27/13 11:36p Rajashakerg
// [TAG]  		EIP103962 
// [Category]  	Improvement
// [Description]  	AMITSE Simpletextin, Simpletextout etc event should
// have high priority.
// [Files]  		notify.c
// 
// 35    12/05/12 4:57a Premkumara
// [TAG]  		EIP105717
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Splash logo is not displaying when Admin/User password is
// set in  setup
// [RootCause]  	The resolution is not handled properly while drawing
// QuietBoot logo
// [Solution]  	Restoring the QuietBoot logo resolution after drawing
// password window.
// [Files]  		Notify.c
// 
// 34    10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 20    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 32    9/26/12 7:21a Arunsb
// Avoided calling ActivateInput twice
// 
// 31    9/26/12 4:08a Premkumara
// [TAG]  		EIP98112
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When the SETUP_DELAY_LOGO_TILL_INPUT set to 1,
// ActivateInput() function called very late.
// [RootCause]  	ActivateInput and ProcessconInavailability are not
// handled properly
// [Solution]  	Handled ActivateInput(), ActivateAppilcation() and
// ProcessConInAvailability() properly when all device are available
// [Files]  		Notify.c
// 
// 30    9/25/12 7:20a Premkumara
// Updated missed changes for EIP98112
// 
// 29    9/24/12 10:28a Premkumara
// [TAG]  		EIP98112
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When the SETUP_DELAY_LOGO_TILL_INPUT set to 1,
// ActivateInput() function called very late.
// [RootCause]  	ActivateInput and ProcessconInavailability are not
// handled properly
// [Solution]  	Handled ActivateInput(), ActivateAppilcation() and
// ProcessConInAvailability() properly when all device are available
// [Files]  		Notify.c
// 
// 28    9/21/12 6:14a Arunsb
// GopEvent corrected
// 
// 27    9/20/12 11:52a Arunsb
// [TAG]  		EIP92497
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	ActivateApplication is delayed when softkeyboard is added
// [RootCause]  	Notification functions not handled properly
// [Solution]  	Notification functions changed from switch to if condition
// [Files]  		notify.c
// 
// 26    9/18/12 12:50a Rajashakerg
// [TAG]  		EIP95518
// [Category]  	Improvement
// [Description]  	Validate the Gop before usage in all the possible cases
// and also get instance of Gop through notification
// [Files]  		boot.c, notify.c, logo.c
// 
// 25    9/17/12 6:10a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 23    8/29/12 4:22p Arunsb
// [TAG]  			EIP94702
// [Description]  	Support for Native Resolution in POST/BOOT
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c, boot.c, logo.c,
// notify.c, postmgmt.c, tselite\minisetupext.c, ezport/stylecommon.c,
// ezportplus/stylecommon.c andlegacy/stylecommon.c
// 
// 22    8/27/12 6:20a Premkumara
// [TAG]  		EIP 94616
// [Category]  	Improvement
// [Description]  	TSE should not wait for key if fast boot is in progress
// [Files]  		AMITSE.sdl, CommonHelper.c, Notify.c, Protocol.c
// 
// 21    5/28/12 5:47a Premkumara
// [TAG]  		EIP75236
// [Category]  	Improvement
// [Description]  	Add the support to control the GOP dependency in TSE
// notification.
// [Files]  		AMITSE.sdl, CommonHelper.c, Notify.c, Minisetup.h,
// Minisetup.sdl, protocol.c, FormBrowser.c, FormBrowser2.c
// 
// 20    4/27/12 5:29a Rajashakerg
// [TAG]  		EIP88435
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Touch does not have functionality at POST
// [RootCause]  	Mouse is initialized after getting notification from
// mousedriver. So mouse avaliable at post and if we click at post, then
// the button status is not consumed by any other application and mouse
// pointer stuck at post
// [Solution]  	Provided the changes to init the mouse at setup in the
// absence of softkbd.
// [Files]  		notify.c, minisetupext.c
// 
// 19    1/25/12 8:02a Rajashakerg
// [TAG]  		EIP81617 
// [Category]  	Improvement
// [Description]  	Avoiding memory leaks in TSE
// [Files]  		hiistring21.c, CommonHelper.c, notify.c
// 
// 18    1/17/12 8:55a Arunsb
// Break statement added in NOTIFY_MASK_MOUSE_DRIVER. Without break
// statement postmessage displayed twice.
// 
// 17    11/20/11 7:14a Rajashakerg
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
// 16    7/19/11 3:00p Arunsb
// [TAG]  		EIP57661
// [Category]  	New Feature
// [Description]  	Driver health related variables are updated via
// notification function.
// [Files]  		notify.c, Uefi21Wapper.c and variable.h
// 
// 15    6/29/11 6:29a Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Hot key boot option support in TSE as per UEFI spec.
// section 3.1.6.
//                 Hot boot keys formed in AtivateInput function.
// [Files]         AMITSE.sdl, bootflow.c, bootflow.h, CommonHelper.c,
// commonoem.c, commonoem.h, boot.c,
//                 hiistring20.c, hiistring21.c and notify.c.
// 
// 14    6/23/11 5:36a Rajashakerg
// [TAG]  		EIP63073  
// [Category]  	New Feature
// [Description]  	Source modules in TSE should get the version details
// from binary in run time not at build time  
// [Files]  		CommonHelper.c, minisetupext.c, notify.c, Ezport\style.c,
// EzportPlus\style.c, Legacy\style.c
// 
// 13    6/19/11 4:04p Arunsb
// [TAG]           EIP58712
// [Category]      New Feature
// [Description]   To disable the BIOS Signon Message and TSE copyright
// version in post screen.
// [Files]         amitse.sdl, amitse.mak, commonhelper.c and notify.c
// 
// 12    4/29/11 4:33p Arunsb
// For 2.13 public patch release signon message hiding feature is omitted
// 
// 10    1/06/11 1:53a Mallikarjunanv
// [TAG]  		EIP50479
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Calls to PostManagerProtocol->SwitchToPostScreen() after
// legacy option ROM execution cause CPU exception.
// [RootCause]  	After the notification, if the graphics driver
// uninstalled and reinstalled from core module then gGOP is getting
// corrupted.
// [Solution]  	Updated the files, by making gGOP/gUgaDraw to NULL in the
// update function and in switch to posty screen returining status as
// aborted if the gGOP/gUgaDraw is NULL
// [Files]  		protocol.c,notify.c,postmgmt.c
// 
// 9     12/29/10 2:30a Mallikarjunanv
// [TAG]  		EIP50479
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Calls to PostManagerProtocol->SwitchToPostScreen() after
// legacy option ROM execution cause CPU exception.
// [RootCause]  	After the notification, if the graphics driver
// uninstalled and reinstalled from core module then gGOP getting
// corrupted.
// [Solution]  	Updated gGop/UgaDraw before using it in AMITSE. 
// [Files]  		logo.c,minisetup.h, notify.c, postmgmt.c ,protocol.c
// 
// 7     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 14    9/16/10 3:01p Madhans
// To avoid compiler warning
// 
// 13    7/12/10 4:49p Madhans
// EIP 39113: Sign ON Message Support.
// 
// 12    6/08/10 5:09p Blaines
// Added new AMITSE hook (hook33), called when TSE determines that console
// out is available.
// 
// 11    2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 10    2/15/10 10:10p Madhans
// 
// 9     2/04/10 11:20p Madhans
// To avoid calling notification function when entring setup.(in Fastboot
// case)
// 
// 8     1/29/10 4:37p Madhans
// To not to depend on ConsoleControl and ConOut.
// 
// 7     1/09/10 5:30a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 6     10/28/09 5:36p Madhans
// 
// 5     9/25/09 6:37a Sudhirv
// EIP-26893 : when the DisplayPostMessage() function of the AMI Post
// Manager protocol is called multiple times, strings are truncated when
// displayed.
// 
// 4     9/15/09 9:32a Sudhirv
// //Fix for EIP 21807 - Version number at the Setup/POST Screen corrupted
// if other language is chosen
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
// 5     3/31/09 3:59p Madhans
// EIP19632
// 
// 4     2/05/09 5:19p Madhans
// PostMgrStatus interface added.
// 
// 3     2/05/09 10:15a Madhans
// Style Module created.
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
// Name:		notify.c
//
// Description:	file contains code to support the notification functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

EFI_GUID        gEfiDXEMouseDriverProtocolGuid  = 
                            EFI_MOUSE_DRIVER_PROTOCOL_GUID;
#include "TseDrvHealth.h"       //Has TSE related driver health structures

#define	NOTIFY_MASK_UGA					(0x00000001)
#define	NOTIFY_MASK_CONSOLE_CONTROL	(0x00000002)
#define	NOTIFY_MASK_CONSOLE_IN			(0x00000004)
#define	NOTIFY_MASK_CONSOLE_OUT			(0x00000008)
#define	NOTIFY_MASK_MOUSE_DRIVER		(0x00000010)
BOOLEAN  IsDriverHealthSupported (VOID);
////////////////////////////////////////////////////////////
/// VARIABLE DECLARATIONS
///////////////////////////////////////////////////////////
typedef struct _NOTIFICATION_INFO
{
	EFI_HANDLE	NotifyHandle;
	EFI_EVENT	NotifyEvent;
	UINT32		NotifyMask;
	EFI_GUID	*NotifyGuid;
	BOOLEAN		NotifyDevicePath;
	VOID		*NotifyRegistration;
	VOID		*NotifyProtocol;
	VOID		**pgProtocol;
}
NOTIFICATION_INFO;

#ifndef STANDALONE_APPLICATION
static UINT32	gGlobalNotify = 0;
BOOLEAN	gQuietBoot = FALSE;
VOID ActivateInput(VOID);

static NOTIFICATION_INFO _gUgaNotify = 
{
	NULL,                             //EFI_HANDLE  NotifyHandle;
	NULL,                             //EFI_EVENT   NotifyEvent;
	NOTIFY_MASK_UGA,                  //UINT32      NotifyMask;
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
	&gEfiGraphicsOutputProtocolGuid,  //EFI_GUID    *NotifyGuid;
#else
	&gEfiUgaDrawProtocolGuid,         //EFI_GUID    *NotifyGuid;
#endif
	TRUE,                             //BOOLEAN     NotifyDevicePath;
	NULL,                             //VOID        *NotifyRegistration;
	NULL,                             //VOID        *NotifyProtocol;
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
	(VOID**)&gGOP                     //VOID        **pgProtocol;
#else
	(VOID**)&gUgaDraw                 //VOID        **pgProtocol;
#endif
};

static NOTIFICATION_INFO _gConsoleControlNotify = 
{
	NULL,                             //EFI_HANDLE  NotifyHandle;
	NULL,                             //EFI_EVENT   NotifyEvent;
	NOTIFY_MASK_CONSOLE_CONTROL,      //UINT32      NotifyMask;
	&gEfiConsoleControlProtocolGuid,  //EFI_GUID    *NotifyGuid;
	FALSE,                            //BOOLEAN     NotifyDevicePath;
	NULL,                             //VOID        *NotifyRegistration;
	NULL,                             //VOID        *NotifyProtocol;
	NULL //(VOID**)&gConsoleControl   //VOID        **pgProtocol;
			//gConsoleControl is used by PostManagerHAndshake to know if ActivateApplication has been called
			//if we allow Notification function to set it, when PostManager handshake need to call ActivateApplication as in case of
			//headless system, the call may be missed.
};

static NOTIFICATION_INFO _gConInNotify =
{
	NULL,                           //EFI_HANDLE  NotifyHandle;
	NULL,                           //EFI_EVENT   NotifyEvent;
	NOTIFY_MASK_CONSOLE_IN,         //UINT32      NotifyMask;
	&gEfiSimpleTextInProtocolGuid,  //EFI_GUID    *NotifyGuid;
	FALSE,                          //BOOLEAN     NotifyDevicePath;
	NULL,                           //VOID        *NotifyRegistration;
	NULL,                           //VOID        *NotifyProtocol;
	NULL //(VOID**)&gConIn          //VOID        **pgProtocol;
};

static NOTIFICATION_INFO _gConOutNotify =
{
	NULL,                            //EFI_HANDLE  NotifyHandle;
	NULL,                            //EFI_EVENT   NotifyEvent;
	NOTIFY_MASK_CONSOLE_OUT,         //UINT32      NotifyMask;
	&gEfiSimpleTextOutProtocolGuid,  //EFI_GUID    *NotifyGuid;
	FALSE,                           //BOOLEAN     NotifyDevicePath;
	NULL,                            //VOID        *NotifyRegistration;
	NULL,                            //VOID        *NotifyProtocol;
	NULL //(VOID**)&gConOut          //VOID        **pgProtocol;
};

static NOTIFICATION_INFO _gMousedriverNotify =
{
	NULL,                            //EFI_HANDLE  NotifyHandle;
	NULL,                            //EFI_EVENT   NotifyEvent;
	NOTIFY_MASK_MOUSE_DRIVER,         //UINT32      NotifyMask;
	&gEfiDXEMouseDriverProtocolGuid,  //EFI_GUID    *NotifyGuid;
	FALSE,                           //BOOLEAN     NotifyDevicePath;
	NULL,                            //VOID        *NotifyRegistration;
	NULL,                            //VOID        *NotifyProtocol;
	NULL 				          //VOID        **pgProtocol;
};


static NOTIFICATION_INFO *_gNotifyList[] =
{
	&_gUgaNotify,
	&_gConsoleControlNotify,
	&_gConInNotify,
	&_gConOutNotify,
	&_gMousedriverNotify,
	NULL
};

#if APTIO_4_00 
EFI_STATUS FvReadResources (
  IN EFI_GUID                       *NameGuid,
  IN EFI_GUID                       *pGuid, 
  IN OUT VOID                       **Buffer,
  IN OUT UINTN                      *BufferSize
  );

// Signon Section Guide
// {2EBE0275-6458-4af9-91ED-D3F4EDB100AA}
#define SGN_ON_SECTION_GUID    {0x2ebe0275, 0x6458, 0x4af9, 0x91, 0xed, 0xd3, 0xf4, 0xed, 0xb1, 0x0, 0xaa}

// Signon file guid
// {A59A0056-3341-44b5-9C9C-6D76F7673817}
// {0xa59a0056, 0x3341, 0x44b5, 0x9c, 0x9c, 0x6d, 0x76, 0xf7, 0x67, 0x38, 0x17};
#define SGN_ON_FILE_GUID    {0xa59a0056, 0x3341, 0x44b5, 0x9c, 0x9c, 0x6d, 0x76, 0xf7, 0x67, 0x38, 0x17}

typedef struct _SIGNON
{
    UINT8 Sig[5];
    UINT8 Ver;
    UINT16 Reserved;
    CHAR8  SgnMsg1[]; 
}AMI_SIGN_ON;

#endif
////////////////////////////////////////////////////////////
/// EXTERN VARIABLES
///////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// FUNCTIONS DECLARATIONS
///////////////////////////////////////////////////////////
VOID 		FindandSetHotKeys (VOID);
UINT8   	IsSetupHideBiosSignOnMsg (void);
VOID 		GetTseBuildVersion(UINTN *TseMajor, UINTN *TseMinor, UINTN *TseBuild);//EIP 63073 : Source modules in TSE should get the version details from binary in run time not at build time
VOID 		GetTseBuildYear(UINT16 *TseBuildYear);//EIP 151966 : Use BIOS build year for copyright message
VOID 		SetDriverHealthCount (VOID);
BOOLEAN 	IsMouseSupported(VOID);
BOOLEAN 	IsSoftKbdSupported(VOID);
BOOLEAN	TseIgnoreKeyForFastBoot(); //EIP-94616

VOID *SavePostScreen( UINTN *SizeOfX, UINTN *SizeOfY );
VOID RestorePostScreen( VOID *UgaBlt, UINTN SizeOfX, UINTN SizeOfY );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DrvHealthNotifyFunction
//
// Description:	Notification function for driver health protocol instal.
//
// Input:		EFI_EVENT , VOID *
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DrvHealthNotifyFunction (EFI_EVENT Event, VOID *Context)
{
	SetDriverHealthCount ();
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_UpdateGoPNotifyFunction
//
// Description:	Notification function for driver health protocol instal.
//
// Input:		EFI_EVENT , VOID *
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _UpdateGoPNotifyFunction (EFI_EVENT Event, VOID *Context)
{
	UpdateGoPUgaDraw();//EIP 95518 : Validate the Gop before usage in all the possible cases and also get instance of Gop through notification
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RegisterNotification
//
// Description:	It will create a notify event and register a notification.
//
// Input:		VOID
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RegisterNotification( VOID )
{
	EFI_STATUS 	Status = EFI_UNSUPPORTED;
	UINTN 		i;
	EFI_EVENT 	Event, GopEvent;
	EFI_GUID 	EfiDriverHealthProtocolGuid = EFI_DRIVER_HEALTH_PROTOCOL_GUID;
	VOID 		*Registration = NULL, *GopRegistration = NULL;

	NOTIFICATION_INFO **notify = _gNotifyList;

	for ( i = 0; *notify != NULL; i++, notify++ )
	{
		Status = gBS->CreateEvent(
				EFI_EVENT_NOTIFY_SIGNAL,
				EFI_TPL_CALLBACK,
				NotificationFunction,
				*notify,
				&((*notify)->NotifyEvent)
				);

		if ( EFI_ERROR(Status) )
			continue;	

		Status = gBS->RegisterProtocolNotify(
				(*notify)->NotifyGuid,
				(*notify)->NotifyEvent,
				&((*notify)->NotifyRegistration)
				);

		// get any of these events that have occured in the past
		gBS->SignalEvent( (*notify)->NotifyEvent );
	}
	if (IsDriverHealthSupported ())			//EIP 57661 Notifying the driver health protocol installation to update the drv health variable in cache
	{
		Status = gBS->CreateEvent(
				EFI_EVENT_NOTIFY_SIGNAL,
				EFI_TPL_CALLBACK,
				_DrvHealthNotifyFunction,
				NULL,
				&Event
				);
		if (!EFI_ERROR (Status))
		{
			Status = gBS->RegisterProtocolNotify(
				&EfiDriverHealthProtocolGuid,
				Event,
				&Registration
				);
			if (!EFI_ERROR(Status))
			{
				gBS->SignalEvent (Event);
			}
		}
	}

//EIP 95518 : Validate the Gop before usage in all the possible cases and also get instance of Gop through notification
	Status = gBS->CreateEvent(
				EFI_EVENT_NOTIFY_SIGNAL,
				EFI_TPL_CALLBACK,
				_UpdateGoPNotifyFunction,
				NULL,
				&GopEvent
				);
		if (!EFI_ERROR (Status))
		{
			Status = gBS->RegisterProtocolNotify(
				&gEfiGraphicsOutputProtocolGuid,
				GopEvent,
				&GopRegistration
				);
			if (!EFI_ERROR(Status))
			{
				gBS->SignalEvent (GopEvent);
			}
		}

	return Status;
}

#if 0
static _gConOutCount = 0;
#endif

#if !APTIO_4_00
extern EFI_GUID  gEfiConsoleOutDeviceGuid;

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NotificationFunction
//
// Description:	function to perform the notification operations.
//
// Input:		EFI_EVENT Event, NOTIFICATION_INFO *Context
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NotificationFunction( EFI_EVENT Event, NOTIFICATION_INFO *Context )
{
	EFI_STATUS Status;
	UINTN Count = 0;
	EFI_HANDLE *HandleBuffer = NULL;
	BOOLEAN found = FALSE;
	UINT32 ModSomething = 0;
//	NOTIFICATION_INFO *Context  =  NotificationContext;
	void *MouseDriverProtocol = NULL;
	UINT32 PasswordInstalled = AMI_PASSWORD_NONE;
	static BOOLEAN ActivateInputDone = FALSE;
	
	if ( Context == NULL )
		return;

	// Do nothing on Notification when Enters to setup/BBSPopup/Booting.
	if(gPostStatus >= TSE_POST_STATUS_ENTERING_TSE)
		return;

    //According to UEFI spec 2.0.: When LocateHandleBuffer() is called
    //with ByRegisterNotify it returns the next handle that is new
    //for the registration. Only one handle is returned at a time and
    //the caller must loop until no more handles.
    do
    {
        Status = gBS->LocateHandleBuffer(
                        ByRegisterNotify,
                        NULL,
                        Context->NotifyRegistration,
                        &Count,
                        &HandleBuffer
                        );

        if (EFI_ERROR( Status ))
            break;

        if(0 != Count)
        {
            EFI_DEVICE_PATH_PROTOCOL *DevicePath;

            Status = gBS->HandleProtocol( HandleBuffer[0], &gEfiDevicePathProtocolGuid, &DevicePath );

#if !APTIO_4_00
            if(Context == &_gConOutNotify) //Special handling for ConOut
            {
                if(
                    (_gUgaNotify.NotifyHandle) && //Wait until local console is initiated
                    (EFI_ERROR(Status)) //This is the notification for the virtual ConOut device
                    )
                {
                    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfoBuffer = NULL;
                    UINTN       EntryCount = 0, Index;

                    Status = gBS->OpenProtocolInformation(
                                    _gUgaNotify.NotifyHandle,
                                    &gEfiConsoleOutDeviceGuid,
                                    &OpenInfoBuffer,
                                    &EntryCount
                                    );
                    if(EFI_SUCCESS == Status)
                    {
                        for (Index = 0; Index < EntryCount; Index++)
                        {
                            if (OpenInfoBuffer[Index].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)
                            {
                                found = TRUE;
                            }
                        }

                        MemFreePointer((VOID **) &OpenInfoBuffer);

                        if(found)
                            break;
                    }
                }
            }
            else
            {
#endif
                //Check if notification for this protocol has to have a
                //device path
				if(Context->NotifyDevicePath)
				{
                	if ( !EFI_ERROR( Status ))
	        		{
	       			    found = TRUE;
	                    break;
	                }
				}
				else
        		{
       			    found = TRUE;
                    break;
                }
				
#if !APTIO_4_00
            }
#endif

            MemFreePointer( (VOID **)&HandleBuffer );
        }

    }while(Count);

#if 0
	if ( Context == &_gConOutNotify )
	{
		if ( _gConOutCount == 0 )
        {
            if(found)
            {
                MemFreePointer( (VOID **)&HandleBuffer );
    			found = FALSE;
            }
        }

		_gConOutCount++;
	}
#endif

	if ( ! found )
		return;

    Context->NotifyHandle = HandleBuffer[0];

	MemFreePointer( (VOID **)&HandleBuffer );

	RUNTIME_DEBUG( L"notify" );

	Status = gBS->HandleProtocol( Context->NotifyHandle, Context->NotifyGuid, (VOID **)&Context->NotifyProtocol );
    if( Context->pgProtocol )
        *(Context->pgProtocol) = Context->NotifyProtocol;

	if ( gGlobalNotify & Context->NotifyMask )
        return;

	if(Context->NotifyMask != NOTIFY_MASK_CONSOLE_IN)
		gGlobalNotify |= Context->NotifyMask;
	else
	{ 	//EIP19632: ConIn Notification is only valid with gST->ConIn != NULL. Otherwise not all the ConIn Connected.
		if(gST->ConIn != NULL )
		{
			gGlobalNotify |= Context->NotifyMask;
			gST->ConsoleInHandle = gST->ConsoleOutHandle;//EIP-141066 Context->NotifyHandle; //EIP:116451, To assign the "gST->ConsoleInHandle" to locate the Keycode protocol.
		}
	}
	
	ModSomething = GetNotifyMaskValue();	//EIP-75236
	/*if(IsSoftKbdSupported())
	{//Checking for the presence of Softkbd
		ModSomething = SOMETHING;
	}
	else
	{//If softkbd is not present the unmasking the mousedriver notify from something
		ModSomething = SOMETHING & (~NOTIFY_MASK_MOUSE_DRIVER);
	}*/
 //EIP-98112 & 92497 Starts
//Commented because ActivateInput getting called twice
	/*if (NOTIFY_MASK_CONSOLE_IN == Context->NotifyMask)					//EIP92497 if softkbd presented then ActivateApplication invoked in postmanager only
	{																					//So changed the logic from switch to if
		//Check if Input has been activated and if yes Activate input
		//EIP19632: ConIn Notification is only valid with gST->ConIn != NULL
		if ( !IsDelayLogoTillInputSupported() ) //EIP-75236
		{
			if( (( gGlobalNotify & ModSomething ) == ModSomething) && ( gST->ConIn != NULL ) )
			{
				ActivateInput();
			}
		}
	}*/
	if (NOTIFY_MASK_MOUSE_DRIVER == Context->NotifyMask)
	{
		if(IsMouseSupported()&& IsSoftKbdSupported())//EIP 88435 : Initializing the mouse at post when mouse and softkbd present
		{
			MouseInit();					//If mouse is notified then Initializing the mouse
			InstallClickHandlers (); 	//EIP160126 install click handlers in notification itself. In other places installing click handler is removed.
		}
	}
	if (((gGlobalNotify & ModSomething) == ModSomething))			//EIP92497 if gConsoleControl is not validated then ActivateApplication will be invoked twice
	{
		/*//All necessary protocols available activate output
		if (NULL == gConsoleControl)	//If kept outside then activateinput wont get call succesully
		{
			ActivateApplication();
		}*/
	
		//If Simple Text Input already available but input has not been activated yet activate now
		//EIP19632: ConIn Notification is only valid with gST->ConIn != NULL
		if (IsDelayLogoTillInputSupported ()) //EIP-75236
		{
			if( (( gGlobalNotify & ModSomething ) == ModSomething) && ( gST->ConIn != NULL ) && (FALSE == ActivateInputDone))
			{
				if (IsMouseSupported()&& IsSoftKbdSupported())		//EIP160126 if softkbd & password presents wait until mouse notify
				{
					PasswordInstalled = PasswordCheckInstalled();
					if(CheckSystemPasswordPolicy(PasswordInstalled))
					{	
						Status = gBS->LocateProtocol(&gEfiDXEMouseDriverProtocolGuid, NULL, &MouseDriverProtocol);
						if (EFI_ERROR (Status))
						{
							return;
						}
					}
				}
				ActivateApplication();
				ActivateInput();
				ActivateInputDone = TRUE;
			}
		}
		else
		{
			if (NULL == gConsoleControl)
			{
				ActivateApplication ();
			}
			if( (( gGlobalNotify & ModSomething ) == ModSomething) && ( gST->ConIn != NULL ) && (FALSE == ActivateInputDone)) //EIP-98112
			{
				if (IsMouseSupported()&& IsSoftKbdSupported())		//EIP160126 if softkbd & password presents wait until mouse notify	
				{
					PasswordInstalled = PasswordCheckInstalled();
					if(CheckSystemPasswordPolicy(PasswordInstalled))
					{	
						Status = gBS->LocateProtocol(&gEfiDXEMouseDriverProtocolGuid, NULL, &MouseDriverProtocol);
						if (EFI_ERROR (Status))
						{
							return;
						}
					}
				}
				ActivateInput();
				ActivateInputDone = TRUE;
			}
		}
   }
 //EIP-98112 & 92497 Ends	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActivateApplication
//
// Description:	function for the Active application operations.
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ActivateApplication( VOID )
{
	CHAR16 *text=NULL,*newString=NULL, *text2=NULL;
	UINTN length, TseMajor,TseMinor, TseBuild;
	UINT16 TseBuildYear=0;
#if APTIO_4_00
	UINTN ConCols,ConRows;
#endif
	gConsoleControl = (EFI_CONSOLE_CONTROL_PROTOCOL *)_gConsoleControlNotify.NotifyProtocol;

	BootGetLanguages();
	CheckEnableQuietBoot ();
	if(gST->ConOut != NULL)
	{
#if !APTIO_4_00
	SetDesiredTextMode();
#else
//eip:26893-Start
	if(EFI_ERROR(gST->ConOut->QueryMode( gST->ConOut, gST->ConOut->Mode->Mode, &ConCols, &ConRows )))
	{
		gMaxRows = StyleGetStdMaxRows();
		gMaxCols = StyleGetStdMaxCols();
	}
	else
	{
	  if((gMaxRows > ConRows) && (gMaxCols > ConCols))
	  {
	 	//  In Aptio 4.x use the Text mode as is it in post screen (Set by the Core)
		// Old Post messages already provided may be affected.
		// Preserve Post messages
		PreservePostMessages(ConCols, gMaxCols);
		gMaxRows = ConRows;
		gMaxCols = ConCols;
	  }
	  else if ((gMaxRows < ConRows) && (gMaxCols < ConCols) && (!gQuietBoot))		//EIP94702 Desired Text mode will be set at InitPostScreen, if quiet boot dont set mode for seamless boot
	  {
		// Current screen mode is bigger then the TSE supports.
		// TSE sets DesiredTextMode
      SetDesiredTextMode();
	  }
	}
//eip:26893-end
#endif
	}
#if APTIO_4_00 
    {
        EFI_GUID SgnFile = SGN_ON_FILE_GUID;
        EFI_GUID SgnSection = SGN_ON_SECTION_GUID;
        AMI_SIGN_ON *SignOn;        
    	VOID  *pSection;
	    UINTN SectionSize;
        EFI_STATUS Status;
        CHAR8 *SgnMsg2;

        Status = FvReadResources (&SgnFile, &SgnSection,(VOID**)&pSection,&SectionSize);
    	if (! EFI_ERROR( Status ) ) {
            SignOn = (AMI_SIGN_ON*)((UINT8 *)pSection + sizeof(EFI_GUID));
            if( (MemCmp( (UINT8*)&SignOn->Sig, (UINT8*)"$SGN$",5) == 0) && (SignOn->Ver >= 2))
            {
                text = StrDup8to16( SignOn->SgnMsg1 );
				if (!IsSetupHideBiosSignOnMsg ())
				{
					SgnMsg2 = ((UINT8 *)&SignOn->SgnMsg1 + StrLen8(SignOn->SgnMsg1)+1);
					text2 = StrDup8to16( SgnMsg2 );
				}
            }
        }
        else
			text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_MAIN_COPYRIGHT) );
    }
#else
	//EIP 21807 - Version number at the Setup/POST Screen corrupted if other language is chosen
	text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_MAIN_COPYRIGHT) );
#endif

	if ( text != NULL )
	{
		length = EfiStrLen(text) + 10;
		newString = EfiLibAllocateZeroPool( length * sizeof(CHAR16) );
		if ( newString != NULL )
		{
		//EIP 63073 : Source modules in TSE should get the version details from binary in run time not at build time
			GetTseBuildVersion(&TseMajor,&TseMinor,&TseBuild);
			//EIP 151966 : Use BIOS build year for copyright message
			GetTseBuildYear(&TseBuildYear);
			SPrint( newString, length * sizeof(CHAR16), text, TseMajor, TseMinor, TseBuild,TseBuildYear );
			PostManagerDisplayPostMessage(newString);
			MemFreePointer( (VOID **)&newString );
		}
		else
			PostManagerDisplayPostMessage(text);
		MemFreePointer( (VOID **)&text );
	}
    // Sign on OEM String
	if(text2 != NULL)
	{
		PostManagerDisplayPostMessage(text2);
		MemFreePointer( (VOID **)&text2 );
	}

	if (IsDelayLogoTillInputSupported())	//EIP-75236 
		ProcessConInAvailabilityHook();

#ifdef EFI_NT_EMULATOR
    gGlobalNotify = gGlobalNotify | NOTIFY_MASK_CONSOLE_OUT;
#endif

	if ( gGlobalNotify & NOTIFY_MASK_UGA )
	{
		if ( gQuietBoot )
		{
			gPostStatus = TSE_POST_STATUS_IN_QUITE_BOOT_SCREEN;
			if(gConsoleControl != NULL)
				gConsoleControl->SetMode( gConsoleControl, EfiConsoleControlScreenGraphics );
			DrawQuietBootLogoHook();
			if(IsMouseSupported()&& IsSoftKbdSupported())//Initializing the mouse at post when mouse and softkbd present
				MouseInit();
			gProgress->quiteBootActive = TRUE ;
			if(gProgress->active)
				PostManagerSetProgressBarPosition() ;
			
		}
	}

//	if ( gGlobalNotify & NOTIFY_MASK_CONSOLE_OUT )
	if ( gST->ConOut != NULL ) // If ConOut is available in System Table the display the post messages.
	{
		//Show post screen if it is not quiet boot or if it is a headless system
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
		if ( ! gQuietBoot || !gGOP)
#else
		if ( ! gQuietBoot || !gUgaDraw)
#endif
		{
			CleanUpLogo();
			InitPostScreen();
		}
	
	ProcessConOutAvailableHook();
	}

	if (IsDelayLogoTillInputSupported())	//EIP-75236 
	{
		if ( !TseIgnoreKeyForFastBoot() ) //EIP-94616
			InstallKeyHandlers();
/*		
  		//Lets install mouse click event in NotificationFunction itself
		if( IsMouseSupported() && IsSoftKbdSupported())//EIP62763 : Checking for mouse and softkbd presence
			InstallClickHandlers();
*/			
	}
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActivateInput
//
// Description:	function for the active Input.
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ActivateInput( VOID )
{
//    EFI_STATUS Status; Set not used 
    VOID *UgaBlt = NULL;
    UINTN SizeOfX=0, SizeOfY=0;
    BOOLEAN bRedraw = FALSE;		//If not initialized then on delay till logo input case we always restoring post due to garabage initialization

    FindandSetHotKeys ();
    // if it is quiet boot copy the screen for later restoration
	if ( gGlobalNotify & NOTIFY_MASK_UGA )
	{
		UgaBlt = SavePostScreen(&SizeOfX, &SizeOfY);
	}

	if (!IsDelayLogoTillInputSupported()) //EIP-98112
	{
		bRedraw = ProcessConInAvailabilityHook();
	}

	//Restore
	if(bRedraw)
   {
		RestorePostScreen (UgaBlt, SizeOfX, SizeOfY);
   }
	else
	{
		MemFreePointer((VOID **) &UgaBlt);		//if redraw required this buffer will be freed in RestorePostScreen
	}

	if (!IsDelayLogoTillInputSupported()) //EIP-98112
	{
		if ( !TseIgnoreKeyForFastBoot() ) //EIP-94616
			InstallKeyHandlers();
/*		
 	 	//Lets install mouse click event in NotificationFunction itself 
		if( IsMouseSupported() && IsSoftKbdSupported())//EIP62763 : Checking for mouse and softkbd presence
			InstallClickHandlers();
*/			
	}
}

//EIP:50479 : Start
//Function to update gGop 
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateGoPUgaDraw
//
// Description:	function to update the Gop when controls comes to TSE.
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UpdateGoPUgaDraw( VOID )
{
    EFI_STATUS Status;
	UINTN Count = 0;
	UINTN Index=0;
	EFI_HANDLE *HandleBuffer = NULL;	
    EFI_DEVICE_PATH_PROTOCOL *DevicePath;
	BOOLEAN found = FALSE;
	
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL//EIP:50479 Initializing gGOP/gUgaDraw to NULL before locating
gGOP = NULL;
#else
gUgaDraw = NULL;
#endif

    Status = gBS->LocateHandleBuffer(
                    ByProtocol,
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
                    &gEfiGraphicsOutputProtocolGuid,
#else
                    &gEfiUgaDrawProtocolGuid,
#endif
                  	NULL,
                    &Count,
                    &HandleBuffer
                    );

	 for(Index=0;Index < Count;Index++)
     {
        Status = gBS->HandleProtocol( HandleBuffer[Index], &gEfiDevicePathProtocolGuid, &DevicePath );
		if (EFI_ERROR( Status ))
            	continue;
#if !APTIO_4_00
        {
            EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfoBuffer = NULL;
            UINTN       EntryCount = 0, i;
    
            Status = gBS->OpenProtocolInformation(
                            HandleBuffer[Index],
                            &gEfiConsoleOutDeviceGuid,
                            &OpenInfoBuffer,
                            &EntryCount
                            );
            if(EFI_SUCCESS == Status)
            {
                for (i = 0; i < EntryCount; i++)
                {
                    if (OpenInfoBuffer[i].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)
                    {
                        found = TRUE;
                    }
                }
                MemFreePointer((VOID **) &OpenInfoBuffer);
            }
        }
#else
        found = TRUE;
#endif
        if(!found)
            continue;

#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
        Status = gBS->LocateProtocol(
                &gEfiGraphicsOutputProtocolGuid,
                NULL, // Registration key
	            &gGOP                     //VOID        **pgProtocol;
                );
			if(EFI_ERROR(Status))
			    gGOP = NULL;
#else
        Status = gBS->LocateProtocol(
                &gEfiUgaDrawProtocolGuid,
                NULL, // Registration key
	            &gUgaDraw                 //VOID        **pgProtocol;
                );
			if(EFI_ERROR(Status))
			    gUgaDraw = NULL;
#endif
	}		

	//81617 : Avoiding memory leaks in TSE
	MemFreePointer( (VOID **)&HandleBuffer );	

}
//EIP:50479 : End
#endif // STANDALONE_APPLICATION

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
