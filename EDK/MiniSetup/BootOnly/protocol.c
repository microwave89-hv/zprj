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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/protocol.c $
//
// $Author: Premkumara $
//
// $Revision: 51 $
//
// $Date: 8/28/14 7:36a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/protocol.c $
// 
// 51    8/28/14 7:36a Premkumara
// [TAG]		EIP107833, 125388
// [Category]	Improvement
// [Symptom:]	Setting best text and GOP mode while using TSEPostinterfaces
// before TSE or after TSE.
// [Files]		Protocol.c, AMITSE.sdl, CommonHelper.c, MiniSetup.sdl,
// PostMgmtc, PostmgmtExt.c, MessagBox.c
// 
// 50    5/02/14 7:06a Premkumara
// [TAG]  		EIP137373
// [Category]  	Improvement
// [Description]  	Added signal event for BeforeTimeOut and AfterTimeOut
// with guids
// [Files]  		AMIVfr.h,protocol.c
// 
// 49    5/02/14 6:15a Arunsb
// [TAG]  		EIP128665
// [Category]  	Improvement
// [Description]  	Providing support to invalidate the BGRT status bit.
// Defined gTSEInvalidateBgrtStatusProtocolGuid
// [Files]  		protocol.c and amivfr.h
// 
// 48    5/02/14 6:12a Arunsb
// [TAG]  		EIP128665
// [Category]  	Improvement
// [Description]  	Providing support to invalidate the BGRT status bit
// [Files]  		protocol.c and amivfr.h
// 
// 47    2/11/14 8:09p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 46    11/07/13 1:55a Premkumara
// [TAG]	EIP-137373
// [Category]	Improvement
// [Description]	Added signal event for BeforeTimeOut and AfterTimeOut
// with GUID
// [Files]	Protocol.c, AMIVfr.h
// 
// 45    10/07/13 3:17a Premkumara
// Resolved build error in EIP-128665
// 
// 44    9/13/13 2:01p Premkumara
// Uploaded back for EIP-128665 after TSEBootOnly 1240 release
// Files - Protocol.c, Protocol.h, AMIPostMgr.h
// 
// 43    8/26/13 2:16a Premkumara
// Reverted back for BootOnly1240 release
// 
// 41    4/18/13 6:15a Arunsb
// [TAG]  		EIP113081 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Post message displays twice
// [RootCause]  	Buffer not cleared after displaying post message
// [Solution]  	Buffer cleared properly. Save and restored the post
// graphics screen properly.
// [Files]  		protocol.c, screen.c and string.c
// 
// 40    4/17/13 12:38p Arunsb
// [TAG]  		EIP107967 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Ami Post Management functionalities reliant on ConOut need
// checks added.
// [Files]  		protocol.c
// 
// 39    12/05/12 5:31a Rajashakerg
// [TAG]  		EIP103381 
// [Category]  	Improvement
// [Description]  	adopting SDL to control timeout spec
// [Files]  		AMITSE.sdl, CommonHelper.c, protocol.c
// 
// 38    12/05/12 4:50a Arunsb
// [TAG]  		EIP107967
// [Category]  	Improvement
// [Description]  	Ami Post Management functionalities reliant on ConOut
// need checks added
// [Files]  		protocol.c
// 
// 37    10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 31    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 35    9/24/12 9:14a Premkumara
// [TAG]  		EIP 93797
// [Category]  	Improvement
// [Description] 	Add support to check for enabled device in BBS priority
// order before launching legacy boot.
// [Files]  		bbs.c, Boot.c, Protocol.c
// 
// 34    9/17/12 6:10a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 32    8/27/12 6:21a Premkumara
// [TAG]  		EIP 94616
// [Category]  	Improvement
// [Description]  	TSE should not wait for key if fast boot is in progress
// [Files]  		AMITSE.sdl, CommonHelper.c, Notify.c, Protocol.c
// 
// 31    5/29/12 4:35a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 30    5/28/12 5:52a Premkumara
// [TAG]  		EIP75236
// [Category]  	Improvement
// [Description]  	Add the support to control the GOP dependency in TSE
// notification.
// [Files]  		AMITSE.sdl, CommonHelper.c, Notify.c, Minisetup.h,
// Minisetup.sdl, protocol.c, FormBrowser.c, FormBrowser2.c
// 
// 29    4/27/12 10:25a Premkumara
// [TAG]  		EIP87769
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Strings are not cleared after calling
// PostManagerSwitchToPostScreen() function
// [RootCause]  	DoRealFlushLines() is not done in
// PostManagerSwitchToPostScreen() function
// [Solution]  	Updateed the PostManagerSwitchToPostScreen() function to
// perform DoRealFlushLines().
// [Files]  		Protocol.c
// 
// 28    4/04/12 12:27a Rajashakerg
// [TAG]  		EIP86253 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Mouse and SoftKbd does not work after displaying "No option
// to boot to" in POST
// [RootCause]  	Mouse timer cleared once after displaying the "No option
// to boot to" in POST
// [Solution]  	Mouse timer cleared only when its going to boot.
// [Files]  		CommonHelper.c, commonoem.c, minisetupext.c, protocol.c
// 
// 27    4/03/12 9:54a Premkumara
// [TAG]  		EIP84150
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	All the timers for mouse drivers before exiting from setup
// is not  stopped
// [RootCause]  	MouseDestroy() is not called StopPointingDevice()
// function to stop Mouse device
// [Solution]  	StopPointingDevice() function is called in MouseDestroy()
// function
// [Files]  		Mouse.c, Protocol.c, Ezport/StyleCommon.c,
// EzportPlus/StyleCommon.c, Legacy/StyleCommon.c, Minisetupext.c
// 
// 26    4/03/12 3:01a Premkumara
// [TAG]  		EIP84150
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	All the timers for mouse drivers before exiting from setup
// is not  stopped
// [RootCause]  	MouseDestroy() is not called StopPointingDevice()
// function to stop Mouse device
// [Solution]  	StopPointingDevice() function is called in MouseDestroy()
// function
// [Files]  		Mouse.c, Protocol.c, Ezport/StyleCommon.c,
// EzportPlus/StyleCommon.c, Legacy/StyleCommon.c, Minisetupext.c
// 
// 25    1/25/12 5:12a Rajashakerg
// [TAG]  		EIP81549 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BOOT_FLOW_NORMAL_INFINITE_LOOP enabled and pressing F7
// while displaying "No option to boot to" is not working properly
// [RootCause]  	When F7 key is pressed we have gBootFlow =
// BOOT_FLOW_CONDITION_BBS_POPUP, and returning from checkforkey() and the
// F7 key is not getting consumed and keeps on looping. 
// [Solution]  	Checking gBootFlow and making to normal in the loop.
// [Files]  		protocol.c
// 
// 24    12/30/11 1:51a Arunsb
// [TAG]  		EIP76721
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BOOT_FLOW_NORMAL_INFINITE_LOOP option is not working
// properly
// [RootCause]  	Iterating variable reinitialized to 0 so in next loop it
// becoming 1 so its missing first boot option
// [Solution]  	Iterating vairable reinitialized to -1.
// [Files]  		Protocol.c
// 
// 23    11/21/11 5:48a Rajashakerg
// [TAG]  		EIP74591
// [Category]  	Improvement
// [Description]  	Make MainSetupLoop as board module hook
// [Files]  		AMITSE.sdl, CommonHelper.c, protocol.c, minisetup.h,
// FormBrowser.c, FormBrowser2.c
// 
// 22    11/20/11 7:19a Rajashakerg
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
// 21    10/31/11 2:14p Premkumara
// [TAG]  		EIP73751 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	L"BootFlow" variable uses inconsistent attributes
// [RootCause]  	L"BootFlow" variable uses inconsistent attributes in
// protocol.c
// [Solution]  	Made consistent use of L"Bootlow" variable with 
// EFI_VARIABLE_BOOTSERVICE_ACCESS attribute
// [Files]  		protocol.c
// 
// 20    9/29/11 7:02p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 19    6/23/11 7:38p Arunsb
// [TAG]           EIP57660 
// [Category]      New Feature
// [Description]   Non-removable media boot behavior as described in UEFI
//                 specification v 2.3.1, p. 3.4.1.
//                 Checks for the setup key if no boot options avail
//                 or not succedded to boot. If setup key pressed launches
// the setup.
//                 If no boot option avail then inserting thumb drive with
// image efi\boot\bootxxxx.efi TSE will launch that image.     
// [Files]         amitse.sdl, bootflow.c and protocol.c
// 
// 18    6/20/11 3:59p Arunsb
// [TAG]             EIP57660 
// [Category]       New Feature
// [Description]   Non-removable media boot behavior as described in UEFI
// specification v 2.3.1, p. 3.4.1.
//                       Checks for the setup key if no boot options avail
// or succedded to boot and launches the setup.
// [Files]             amitse.sdl, bootflow.c, bootflow.h, commonoem.c,
// boot.c and protocol.c
// 
// 17    1/06/11 1:58a Mallikarjunanv
// [TAG]  		EIP50479
// [Category]  	Bug Fix
// [Severity]  	Important
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
// 16    12/29/10 2:33a Mallikarjunanv
// [TAG]  		EIP50479
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Calls to PostManagerProtocol->SwitchToPostScreen() after
// legacy option ROM execution cause CPU exception.
// [RootCause]  	After the notification, if the graphics driver
// uninstalled and reinstalled from core module then gGOP getting
// corrupted.
// [Solution]  	Updated gGop/Ugadraw before using it in AMITSE. 
// [Files]  		logo.c,minisetup.h, notify.c, postmgmt.c ,protocol.c
// 
// 15    12/02/10 1:07p Madhans
// [TAG] - EIP 41838  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Update AMI Post Manager Protocol witht he following. 2.
// Updating the interface PostManagerDisplayPostMessageEx to handle the
// cursor position properly. 2. Need to add new interface to GetAttribute
// To keep the GetAttribute to end of protocol.
// [Rootcause] - 1. Display string is over written by the next string if
// the interface PostManagerDisplayPostMessageEx used simultaneously. 2.
// Need to get the attribute info to use PostManagerDisplayPostMessage
// interfaces effectively
// [Solution]- Fix in string.c to handle cursor and line positions. The
// files Protocol.c, Protocol.h and AmiPostMgr.h have the new interface
// implementaion to get the attribute.
// [Files] - Protocol.c, Protocol.h, AmiPostMgr.h and string.c
// 
// 14    11/16/10 8:56a Mallikarjunanv
// [TAG] - EIP 41838  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Update AMI Post Manager Protocol witht he following. 2.
// Updating the interface PostManagerDisplayPostMessageEx to handle the
// cursor position properly. 2. Need to add new interface to GetAttribute
// [Rootcause] - 1. Display string is over written by the next string if
// the interface PostManagerDisplayPostMessageEx used simultaneously. 2.
// Need to get the attribute info to use PostManagerDisplayPostMessage
// interfaces effectively
// [Solution]- Fix in string.c to handle cursor and line positions. The
// files Protocol.c, Protocol.h and AmiPostMgr.h have the new interface
// implementaion to get the attribute.
// [Files] - Protocol.c, Protocol.h, AmiPostMgr.h and string.c
// 
// 13    10/05/10 6:41p Madhans
// [TAG] - EIP 45301  
// [Category]- Bug Fix
// [Severity]- Minor
// [Symptom]- when TSE_PRESERVE_DISABLED_BBS_DEVICE_ORDER is set disabling
// first device cause system not to boot.
// [Rootcause] - protocol.c was assuming disabled opens are coming in the
// End.
// [Solution]- Fix in protocol.c to handle this case.
// [Files] - protocol.c
// 
// 12    9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 23    9/13/10 4:34p Madhans
// 1. To preserve FastBootflow condition before going to Boottimeout.
// 2. Preformance Calls optimized.
// 
// 22    9/13/10 12:11p Blaines
// Fix for the gPostMsgProtocolActive not being available past a certain
// point 
// 
// 21    9/08/10 6:53a Mallikarjunanv
// EIP-42080: TSE updates with respect to Fast Boot Support
// 
// 20    6/17/10 4:19p Madhans
// 
// 19    6/17/10 3:20p Blaines
// Added error checking to PostManagerDisplayQuietBootMessage()  for
// messages that are 0 in length. 
// 
// 18    6/14/10 7:06p Madhans
// 
// 17    4/02/10 4:34p Madhans
// 
// 16    3/30/10 4:45p Blaines
// Fix to prevent BBS Popup from being launched twice when selecting 
// ENTER_SETUP option
// 
// 15    3/23/10 5:09p Blaines
// Add PostManager Extentions
// 
// 14    2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 13    2/17/10 7:02p Madhans
// To support PrintQuiteBootmessage for UEFI 2.1
// 
// 12    2/15/10 10:12p Madhans
// To support Printquitebootmessage
// 
// 11    2/04/10 11:21p Madhans
// To remove Conout dependance
// 
// 10    2/04/10 12:10p Blaines
// Correct function header description for PostManagerSetAtribute.
// 
// 9     2/04/10 12:03p Blaines
// EIP-28005
// 
// Added PostManagerSetAttribute to support display of text in color.
// Added support for handling string characters --- \n, \r.
// 
// 8     1/09/10 5:35a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 7     12/14/09 12:21p Blaines
// Include EIP Comment
// 
// EIP 28007, FIX: If Post message printed in the Quiteboot by using Set
// cur position It is better to flash all the screen.
// 		
// 
// 6     10/28/09 5:37p Madhans
// 
// 5     9/17/09 9:04a Sudhirv
// Remove Load Driver Option from TSE 2.x as it will be handled from Core
// 
// 4     9/16/09 6:15p Madhans
// EIP 25416  : Support have 1/10 sec Timeout
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
// 2     5/13/09 2:22p Madhans
// To patch the version number in the Bootonly TSE. update the build
// number.
// 
// 1     4/28/09 11:12p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 6     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 5     3/31/09 4:00p Madhans
// UEFI2.1
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
// Name:		PROTOCOL.C
//
// Description:	This file contains code for TSE exported protocol
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

UINT32 gBootFlow = BOOT_FLOW_CONDITION_NORMAL;

BOOLEAN gDoNotBoot = FALSE;
VOID StopClickEvent(VOID);//EIP-84150 Stopping ClickEvents

static EFI_HANDLE gProtocolHandle = NULL;
EFI_GUID gAmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
EFI_GUID gTSEInvalidateBgrtStatusProtocolGuid = TSE_INVALIDATE_BGRT_STATUS_PROTOCOL_GUID;

BOOLEAN TseIgnoreKeyForFastBoot(); //EIP-94616 Don't wait for key when FastBoot is Enabled
BOOLEAN GetBBSOptionStatus(BOOT_DATA *pBootData); //EIP-93797

static AMI_POST_MANAGER_PROTOCOL	gPostManagerProtocol =
{
	PostManagerHandshake,
	PostManagerDisplayPostMessage,
    PostManagerDisplayPostMessageEx,
    PostManagerDisplayQuietBootMessage,
    PostManagerDisplayMsgBox,
    PostManagerSwitchToPostScreen,
	PostManagerSetCursorPosition,
	PostManagerGetCursorPosition,
	PostManagerInitProgressBar,
	PostManagerSetProgressBarPosition,
	PostManagerGetPostStatus,
	PostManagerDisplayInfoBox,
	PostManagerSetAttribute,
	PostManagerDisplayMenu,
	PostManagerDisplayMsgBoxEx,
	PostManagerDisplayProgress,
	PostManagerGetAttribute, 	//EIP-41838: New interface added to get the attribute
    PostManagerDisplayTextBox 	//EIP-64877: New interface added to get the text input
};

//EIP 128665 starts
EFI_STATUS InvalidateBgrtStatusByProtocol (VOID);
TSE_INVALIDATE_BGRT_STATUS_PROTOCOL gInvalidateBgrtStatus = {InvalidateBgrtStatusByProtocol};
EFI_STATUS InstallInvalBGRTStatusProtocol (EFI_HANDLE Handle);
//EIP 128665 ends

EFI_STATUS ShowPostMsgBox(IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8  MsgBoxType, UINT8 *pSelection);


EFI_STATUS ShowPostMsgBoxEx(
	IN CHAR16			*Title,
 	IN CHAR16			*Message,
 	IN CHAR16			*Legend,
 	IN MSGBOX_EX_CATAGORY	 	MsgBoxExCatagory,
 	IN UINT8	 		MsgBoxType,
    	IN UINT16			*OptionPtrTokens,	// Valid only with MSGBOX_TYPE_CUSTOM 
    	IN UINT16	 		OptionCount,		// Valid only with MSGBOX_TYPE_CUSTOM
    	IN AMI_POST_MGR_KEY		*HotKeyList, 		// NULL - AnyKeyPress closes
    	IN UINT16 			HotKeyListCount, 
    	OUT UINT8			*MsgBoxSel,
    	OUT AMI_POST_MGR_KEY		*OutKey
	);
EFI_STATUS ShowInfoBox(IN CHAR16  *InfoBoxTitle, IN CHAR16  *Message, IN UINTN   TimeLimit, EFI_EVENT  *RetEvent);

EFI_STATUS HiiString2BltBuffer(	CHAR16 *Message,
								EFI_UGA_PIXEL Foreground, 
								EFI_UGA_PIXEL Background, 
								OUT	UINTN *Width,
								OUT EFI_UGA_PIXEL **BltBuffer,
								OUT UINTN *BltGlyphWidth);
EFI_STATUS DrawHiiStringBltBuffer(CHAR16 *Message, INTN CoOrdX, INTN CoOrdY, CO_ORD_ATTRIBUTE Attribute, EFI_UGA_PIXEL Foreground, EFI_UGA_PIXEL Background);
EFI_STATUS ShowPostMenu (
    IN VOID	*HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN UINT16 	LegendToken,	  
    IN POSTMENU_TEMPLATE *MenuData,
    IN UINT16 	MenuCount,
    OUT UINT16  *pSelection
);

EFI_STATUS ShowPostTextBox(
    IN VOID	    *HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN TEXT_INPUT_TEMPLATE *InputData,
    IN UINT16 	ItemCount,
    IN DISPLAY_TEXT_KEY_VALIDATE DisplayTextKeyValidate
);

EFI_STATUS ShowPostProgress(
    IN UINT8			ProgressBoxState, 
    IN CHAR16			*Title,
    IN CHAR16			*Message,
    IN CHAR16			*Legend,	
    IN UINTN 			Percent,	
    IN OUT VOID			**Handle,	
    OUT AMI_POST_MGR_KEY	*OutKey
);
BOOLEAN   	IsTseBestTextGOPModeSupported (VOID);
EFI_STATUS	SaveCurrentTextGOP ( UINTN *currenttextModeCols, UINTN *currenttextModeRows, UINT32 *currentGOPMode ); //EIP-107833 Fixing proper mode and resolution for post interfaces
EFI_STATUS	RestoreTextGOPMode ( UINTN prevTextModeCols, UINTN prevTextModeRows, UINT32 prevGOPMode ); //EIP-107833 Fixing proper mode and resolution for post interfaces

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InstallProtocol
//
// Description:	This function installs different protocols exported.
//
// Input:		VOID
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InstallProtocol( VOID )
{
	EFI_STATUS Status;

	Status = gBS->InstallMultipleProtocolInterfaces(
			&gProtocolHandle,
			&gAmiPostManagerProtocolGuid, &gPostManagerProtocol,
#ifdef USE_COMPONENT_NAME
			&gEfiComponentNameProtocolGuid, &gComponentName,
#endif
			NULL
			);
	if ( !EFI_ERROR( Status ) )
	{
		Status = InstallFormBrowserProtocol(gProtocolHandle);
		Status = InstallInvalBGRTStatusProtocol (gProtocolHandle);
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UninstallProtocol
//
// Description:	This function uninstalls different protocols exported.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UninstallProtocol( VOID )
{
	gBS->UninstallMultipleProtocolInterfaces(
			&gProtocolHandle,
			&gAmiPostManagerProtocolGuid, &gPostManagerProtocol,
#ifdef USE_COMPONENT_NAME
			&gEfiComponentNameProtocolGuid, &gComponentName,
#endif
			NULL
			);

	UnInstallFormBrowserProtocol(gProtocolHandle);

}

VOID SetBootTimeout( EFI_EVENT Event, BOOLEAN *timeout )
{
	if ( timeout != NULL )
		*timeout = TRUE;
}

VOID AboartFastBootPath(VOID)
{
	gBootFlow = BOOT_FLOW_CONDITION_NORMAL;
	gPostManagerHandshakeCallIndex--;
    gRT->SetVariable(
    			L"BootFlow",
    			&_gBootFlowGuid,
    			EFI_VARIABLE_BOOTSERVICE_ACCESS,
    			sizeof(gBootFlow),
    			&gBootFlow
    			);
}
BOOLEAN IsBootTimeOutValueZero(VOID);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PostManagerHandshake
//
// Description:	This function is the handshake function to which BDS
//              hands-off.
//
// Input:		VOID
//
// Output:		This function never returns. It only boots different
//              options.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerHandshake( VOID )
{
	EFI_EVENT timer = NULL;
	EFI_STATUS Status = EFI_UNSUPPORTED;

	volatile BOOLEAN bootTimeout = FALSE;
	UINT16  Value = 1;
    UINT64  TimeoutValue;
	UINTN   size = 0;
	EFI_GUID    AmitseAfterFirstBootOptionGuid = AMITSE_AFTER_FIRST_BOOT_OPTION_GUID;
	EFI_GUID AmiTseBeforeTimeOutGuid = AMITSE_BEFORE_TIMEOUT_GUID;
	EFI_GUID AmiTseAfterTimeOutGuid = AMITSE_AFTER_TIMEOUT_GUID;
	BOOLEAN AfterFirstBootSignalled = FALSE;
	UINT16  *pBootOrder=NULL;
    UINT16  u16BootCount = 0,i;				//Dont change i data type, in infinite loop it is reinitialized to -1.
    UINT16  BootNext, *pBootNext = NULL;

	// Performance measurement starta
	PERF_START (0, AMITSE_TEXT("Boot"), NULL, 0);

	RUNTIME_DEBUG( L"mre" );

	gPostManagerHandshakeCallIndex++;

	if(gPostManagerHandshakeCallIndex!=1)
	{
		gEnterSetup = TRUE;
		goto _ShowMainMenu;
	}

    PostManagerHandShakeHookHook();

#ifndef STANDALONE_APPLICATION
	if ( ! gConsoleControl )
	{
		//All necessary protocols are not available yet.
		//We can still proceed if Uga Draw is the only protocol not available yet.
		ActivateApplication();
		//EIP-75236 
		if (!IsDelayLogoTillInputSupported())
			ActivateInput();
	}
#endif

    if(!gVariableList)
        VarLoadVariables( (VOID **)&gVariableList, NULL );

	TimerStopTimer( &gKeyTimer );

	// this *MUST* be run a EFI_TPL_APPLICATION
	gBS->RaiseTPL( EFI_TPL_HIGH_LEVEL );	// guarantees that RestoreTPL won't ASSERT
	gBS->RestoreTPL( EFI_TPL_APPLICATION );

	// Performance measurement Pause
//	PERF_END (0,L"Boot", NULL, 0);
	// Exclude IDEPasswordCheck IDEPasswordCheck that it may get the use input.
	// IDE password Module takes care of the Password check.
	//TSEIDEPasswordCheck(); 

	// Performance measurement continue
//	PERF_START (0, L"Boot", NULL, 0);    

    // get the current boot options and languages
	BootGetBootOptions();
	BootGetLanguages();

	StyleUpdateVersionString();

	gPostStatus = TSE_POST_STATUS_IN_BOOT_TIME_OUT;

	//EIP 103381 - Providing boot time out value depending on TSE_BOOT_TIME_OUT_AS_ZERO token
	if(!IsBootTimeOutValueZero())
		Value = GetBootTimeOut(Value);
	else
		Value = 0;

#ifdef STANDALONE_APPLICATION
    Value = 0;
    gEnterSetup = TRUE;
#endif

	if ( Value == 0 )
		bootTimeout = TRUE;

	if ( !TseIgnoreKeyForFastBoot() ) //EIP-94616
	{
		CheckForKeyHook( (EFI_EVENT)NULL, NULL );
	}

    if((BOOT_FLOW_CONDITION_NORMAL != gBootFlow) || (gEnterSetup==TRUE))
    {
        UINT32 condition = BOOT_FLOW_CONDITION_NORMAL;
        UINT32 *conditionPtr;

        size = 0;
        conditionPtr = VarGetNvramName( L"BootFlow", &_gBootFlowGuid, NULL, &size );
        if ( conditionPtr != NULL )
        	condition = *conditionPtr;
        
        MemFreePointer( (VOID **)&conditionPtr );

		if((condition == BOOT_FLOW_CONDITION_FAST_BOOT) && ((gBootFlow != condition)||(gEnterSetup==TRUE)))
		{
			// Take the Normal boot path as Fast boot path is altered by CheckForKeyHook().
			AboartFastBootPath();
			return EFI_UNSUPPORTED;
		}

        if(BOOT_FLOW_CONDITION_NORMAL == condition)
        {
            gRT->SetVariable(
    					L"BootFlow",
    					&_gBootFlowGuid,
    					EFI_VARIABLE_BOOTSERVICE_ACCESS,//EIP-73751 BootFlow wil use RS attribute to avoid inconsistent attributes
    					sizeof(UINT32),
    					&gBootFlow
    					);
        }
        else
            gBootFlow = BOOT_FLOW_CONDITION_NORMAL;
    }

	Status = BootFlowManageEntry();
	if (Status == EFI_UNSUPPORTED)
    {
        Value = 0xFFFF;
        gDoNotBoot = TRUE;
    }
	if(Status == EFI_NOT_STARTED)
		bootTimeout = TRUE;

	if(gBootFlow == BOOT_FLOW_CONDITION_FAST_BOOT)
	{
		UINT32 PasswordInstalled = PasswordCheckInstalled();
		
		if((gPasswordType == AMI_PASSWORD_NONE) && (PasswordInstalled != AMI_PASSWORD_NONE))
		{
			if(CheckSystemPasswordPolicy(PasswordInstalled))
			{
				// Take the Normal boot path as Password is installed and not validated by the user yet
				AboartFastBootPath();
				return EFI_UNSUPPORTED;
			}
		}
	}
    else
    {
	// Reinit Before Boottimeout So any action can set the boot flow again.
	gBootFlow = BOOT_FLOW_CONDITION_NORMAL;
    }

	if ( Value != 0xFFFF )
    {
        TimeoutValue = (UINT64) TIMER_TENTH_SECOND;
        TimeoutValue = MultU64x32( TimeoutValue, (UINT32) Value );

        TimerCreateTimer( &timer, SetBootTimeout, (VOID *)&bootTimeout, TimerRelative, TimeoutValue, EFI_TPL_CALLBACK );
    }

	// Performance measurement Pause
	PERF_END (0, AMITSE_TEXT("Boot"), NULL, 0);

	// While the boot timeout has not expired
	EfiLibNamedEventSignal (&AmiTseBeforeTimeOutGuid);
	while ( ! bootTimeout )
	{
		if ( gEnterSetup || gBootFlow )
		{
			bootTimeout = TRUE;
            continue;
		}
		if ( !TseIgnoreKeyForFastBoot() ) //EIP-94616
		{
			// check for 'hotkey' actions that would invoke something
			CheckForKeyHook( (EFI_EVENT)NULL, NULL );
		}

        TimeOutLoopHookHook();
	}
	EfiLibNamedEventSignal (&AmiTseAfterTimeOutGuid);

	// Performance measurement continue
	PERF_START (0, AMITSE_TEXT("Boot"), NULL, 0);

	TimerStopTimer( &timer );

    if ((!gDoNotBoot) && (gBootFlow))
    {
        gRT->SetVariable(
					L"BootFlow",
					&_gBootFlowGuid,
					EFI_VARIABLE_BOOTSERVICE_ACCESS,//EIP-73751 BootFlow wil use RS attribute to avoid inconsistent attributes
					sizeof(UINT32),
					&gBootFlow
					);
        BootFlowManageEntry();
    }

_ShowMainMenu:

	if ( gEnterSetup )
	{
    	// Performance measurement Pause
    	PERF_END (0, AMITSE_TEXT("Boot"), NULL, 0);
    	// Disable access to the post manager protocol display post message functions and to 
        //  the switch to post screen functions of post manager protocol
    	gPostMsgProtocolActive = FALSE;

		gPostStatus = TSE_POST_STATUS_ENTERING_TSE;
		gSetupContextActive = TRUE;

		Status = gST->ConIn->Reset( gST->ConIn, FALSE );
		Status = MainSetupLoopHook();//EIP74591 : Modified MainSetupLoop as board module hook
		gSetupContextActive = FALSE;
		

    	// Reenable access to the post manager protocol display post message functions and to 
        //  the switch to post screen functions of post manager protocol
    	gPostMsgProtocolActive = TRUE;
    	// Performance measurement continue
    	PERF_START (0, AMITSE_TEXT("Boot"), NULL, 0);
	}


	if(gPostManagerHandshakeCallIndex!=1)
	{
		// In case of not a first call
		// Don't do the Boot Manager Work just exit the to caller.
		gPostManagerHandshakeCallIndex--;
		return Status;
	}

	// Pass control to the boot process to handle the selected boot option
	// if the boot is allowed
    if (gDoNotBoot)
   {
		if(!ItkSupport())
		{
			gEnterSetup = TRUE;
			goto _ShowMainMenu;
		}
		else
			gEnterSetup = FALSE;
    }

	if(!NoVarStoreSupport())
	{
		size = 0;
		//VarGetNvram( VARIABLE_ID_AMITSESETUP, &size );
		HelperGetVariable( VARIABLE_ID_AMITSESETUP, (CHAR16 *)NULL, (EFI_GUID *)NULL, NULL, &size );
	
		if(size < sizeof(AMITSESETUP))
		{
			Status = MiniSetupEntry();
			MiniSetupExit( Status );
		}
	}

	gPostStatus = TSE_POST_STATUS_PROCEED_TO_BOOT;

	// LoadDriverOrder();	//EIP: 25799 - Remove Load Driver Option from TSE 2.x as it is handling from Core.

    ProcessProceedToBootHook();

    TSEUnlockHDD();

	if(ItkSupport())
	    BbsItkBoot();
	else
	{
	    //Try boot next first
	    size = 0;
	    pBootNext = (UINT16 *)VarGetNvramName(L"BootNext", &gEfiGlobalVariableGuid, NULL, &size);
	    if(pBootNext && (size == sizeof(UINT16)))
	    {
	        BootNext = *pBootNext;
	        //Clear Boot next
	        VarSetNvramName(L"BootNext",
	                        &gEfiGlobalVariableGuid,
	                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
	                        pBootNext,
	                        0);
	        if( gBootFlow == BOOT_FLOW_CONDITION_FAST_BOOT) { 
				// FastBoot module normally checks for Bootnext before taking the FastBoot path
				// If the Boot next is set in FastBoot case then do the full boot.
				    AboartFastBootPath();
					return Status;
				}
			else {
				BootLaunchBootOption(BootNext, NULL, 0);
			}
		}
	
	
	    if(pBootNext)
	        MemFreePointer((void **) &pBootNext);
	
	    size =0 ;
	    pBootOrder = (UINT16 *)VarGetNvramName( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
	
	#ifdef EFI_NT_EMULATOR
	    if(!pBootOrder || !gBootData)
	    {
	        VarSetNvramName(L"BootOrder",
	        &gEfiGlobalVariableGuid,
	        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
	        NULL,
	        0);
	
	        return Status;
	    }
	#endif
	
	    //Get enabled options count
	    for(u16BootCount=0; u16BootCount<(UINT16)(size/sizeof(UINT16)); u16BootCount++ )
	    {
            if(!IsPreservedDisabledBootOptionOrder())
            {
    	        BOOT_DATA *pBootData;

	            pBootData = BootGetBootData(pBootOrder[u16BootCount]);
	            if(!(pBootData->Active & LOAD_OPTION_ACTIVE))
	                break;
            }
	    }
	
		if(!u16BootCount)
	    {
	        //No valid/enabled boot option
			Status = BootFlowManageExit();
	            //infinite loop
	            while(EFI_NOT_STARTED == Status)
	            {
                    CHAR16 *text = NULL;
                    
                    text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_NO_BOOT_OPTIONS));
                    if ( ( text != NULL ) && (gST->ConOut != NULL))
                    gST->ConOut->OutputString(gST->ConOut, text);
                    
                    //Wait for key
                    gBS->WaitForEvent( 1, &gST->ConIn->WaitForKey, &size );
                    CheckForKeyHook( (EFI_EVENT)NULL, NULL );
                    if (TRUE == gEnterSetup)                          //If setup key detects then launch the setup
                    {
                        goto _ShowMainMenu;
                    }
                    Status = BootFlowManageExit ();                 //EIP: 57660 Condition: If user plugs the any thumb drive after boot then TSE will try to launch the image from that file system using the path efi\boot\bootxxxx.efi
					if( gBootFlow )//EIP 81549 : Checking for gBootFlow, making gBootFlow to normal such that the key will be consumed in chcekforkey
						gBootFlow = BOOT_FLOW_CONDITION_NORMAL;
	            }
	    }
	
		if ( !gEnterSetup )//EIP-86253  If no key is pressed to go to setup then stopping MousePointingDevice and stopping ClickEvents
		{
			StopClickEvent();
			MouseDestroy();
		}
	    for ( i = 0; i < u16BootCount; i++)
	    {
	        BOOT_DATA *pBootData;

	        pBootData = BootGetBootData(pBootOrder[i]);

  	        if(pBootData == NULL || !(pBootData->Active & LOAD_OPTION_ACTIVE))
                continue;

			if ( BBSValidDevicePath(pBootData->DevicePath) ) //EIP-93797
				if ( GetBBSOptionStatus (pBootData) )
					continue;

	        Status = BootLaunchBootOption(pBootOrder[i], pBootOrder+i, u16BootCount - i);
	
	        if ( !AfterFirstBootSignalled )
			{
				EfiLibNamedEventSignal ( &AmitseAfterFirstBootOptionGuid );

				if( gBootFlow == BOOT_FLOW_CONDITION_FAST_BOOT) {
				    AboartFastBootPath();
					return Status;
				}	

				AfterFirstBootSignalled = TRUE;
			}
	
	        if((i+1) >= u16BootCount)
	        {
	            Status = BootFlowManageExit();
	            if ( EFI_NOT_STARTED == Status )
				{
                    CheckForKeyHook( (EFI_EVENT)NULL, NULL );
                    if (TRUE == gEnterSetup)                          //If setup key detects then launch the setup
                    {
                        goto _ShowMainMenu;
                    }
					// Infinite loop is true so we start again
					i = -1;											//Changed 0 to -1. Then only in next iteration it will be zero otherwise it will be 1.
				}													//If it is i = 0 then it will miss first boot option
	        }
	    }

	}
#ifndef STANDALONE_APPLICATION
    gEnterSetup = TRUE;
    goto _ShowMainMenu;
#else
	return Status;
#endif

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PostManagerDisplayPostMessage
//
// Description:	This function is the protocol to display messages in
//              the post screen.
//
// Input:		CHAR16 *message: Unicode string to be displayed.
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerDisplayPostMessage( CHAR16 *message )
{
	if ( ! gPostMsgProtocolActive )
		return EFI_UNSUPPORTED;

	if (NULL == gST->ConOut)
		return EFI_NOT_READY;

	return PrintPostMessage(message, TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PostManagerDisplayPostMessageEx
//
// Description:	This function is the protocol to display messages with
//              attributes in the post screen.
//
// Input:		CHAR16 *message: Unicode string to be displayed.
//              UINTN Attribute: Attribute for the message
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerDisplayPostMessageEx( CHAR16 *message, UINTN Attribute )
{
	if ( ! gPostMsgProtocolActive )
		return EFI_UNSUPPORTED;

	if (NULL == gST->ConOut)
		return EFI_NOT_READY;

	switch(Attribute)
    {
        case PM_EX_DONT_ADVANCE_TO_NEXT_LINE:
            return PrintPostMessage(message, FALSE);
    }

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PostManagerSwitchToPostScreen
//
// Description:	This function is the protocol to switch to post screen
//
// Input:		VOID
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerSwitchToPostScreen( VOID )
{
#ifdef STANDALONE_APPLICATION
	return EFI_UNSUPPORTED;
#else
	if ( ! gPostMsgProtocolActive )
		return EFI_UNSUPPORTED;

    if ( gQuietBoot )
	{
		UpdateGoPUgaDraw();//EIP:50479 : Function to Update gGop before using it in AMITSE.
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
      if (!gGOP)
#else
      if (!gUgaDraw)
#endif
		 return EFI_UNSUPPORTED;//EIP:50479 : Returning unsupported if the GOP is NULL
	
		gQuietBoot = FALSE;
		CleanUpLogo();
		//EIP 28007, FIX: If Post message printed in the Quiteboot by using Set cur position
		// It is better to flash all the screen.
		FlushLines( 0, gMaxRows - 1 );
		DoRealFlushLines(); //EIP-87769
		InitPostScreen();
        return EFI_SUCCESS;
	}

    return EFI_UNSUPPORTED;
#endif
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     PostManagerInitProgressBar
//
// Description:  Initializes the PostManagerProgressBar
//
// Input:		 UINTN x - Column or Left screen position of ProgressBar in pixels
//				 UINTN y - Row or Top screen position of ProgressBar in pixels
//				 UINTN w - Width of ProgressBar in pixels
//				 UINTN h - Height of ProgressBar in pixels
//				 UINTN iterate - Total number of iterations or Calls
//								 to advanced the progressbar to 100% of the given width.
//								 The delta or changed value will be computed.								 
//
// Output:		 EFI_STATUS status - If the function runs correctly, returns
//				 EFI_SUCCESS, else other EFI defined error values.
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PostManagerInitProgressBar(
	UINTN x,
	UINTN y,
	UINTN w,
	UINTN h,
	UINTN iterate)
{
	EFI_STATUS Status = 0; 

	EFI_UGA_PIXEL	*BGColor;
	EFI_UGA_PIXEL	*BDRColor;
	EFI_UGA_PIXEL	*FillColor;
		
	BGColor = EfiLibAllocateZeroPool(sizeof (EFI_UGA_PIXEL));
	BDRColor = EfiLibAllocateZeroPool(sizeof (EFI_UGA_PIXEL));
	FillColor = EfiLibAllocateZeroPool(sizeof (EFI_UGA_PIXEL));
	
	GetProgressColor(BGColor,BDRColor,FillColor);

	gProgress->delta = w/iterate;
	gProgress->w = gProgress->delta*iterate;
	gProgress->h = h;
	gProgress->x = x;
	gProgress->y = y;
	gProgress->backgroundColor = BGColor;
	gProgress->borderColor = BDRColor;
	gProgress->fillColor = FillColor;
	gProgress->quiteBootActive = FALSE ;
	gProgress->active = TRUE ;         // progressbar has been initialized
	
	return Status;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     PostManagerSetProgressBarPosition
//
// Description:  Increments the PostManagerProgressBar
//
// Input:		 None
//				 
//
// Output:		 EFI_STATUS status - If the function runs correctly, returns
//				 EFI_SUCCESS, else other EFI defined error values.
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PostManagerSetProgressBarPosition()
{
	EFI_STATUS Status = EFI_SUCCESS;
	if(gProgress->active)
		DrawBltProgressBar();
	else
		Status = EFI_UNSUPPORTED;
			
	return Status;
}



	
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     PostManagerSetCursorPosition
//
// Description:  Wrapper function for SetCurPos
//
// Input:		 UINTN X - Value of the column 
//				 UINTN Y - Number of row below the last written line
//
// Output:		 EFI_STATUS status - If the function runs correctly, returns
//				 EFI_SUCCESS, else other EFI defined error values.
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PostManagerSetCursorPosition(UINTN X, UINTN Y)
{
	return SetCurPos(X,Y);
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     PostManagerGetCursorPosition
//
// Description:  Wrapper function for GetCurPos
//               Writes cursor position into given X and Y locations.
//
// Input:    UINTN *pX - Pointer to storage for current column value 
//			 UINTN *pY - Pointer to storage for current row value
//
// Output: EFI_STATUS status - EFI_SUCCESS if OK,
//                             EFI_INVALID_PARAMETER if NULL pointer
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PostManagerGetCursorPosition(UINTN *pX, UINTN *pY)
{
	return GetCurPos(pX, pY);
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     PostManagerDisplayMsgBox
//
// Description:  
// 
//
// Input:    IN CHAR16  *MsgBoxTitle,
//    		IN CHAR16  *Message,
//    		IN UINT8   MsgBoxType,
//
// Output: EFI_STATUS status and UINT8 MsgBoxSel
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveGraphicsScreen(VOID);
VOID RestoreGraphicsScreen(VOID);
EFI_STATUS
PostManagerDisplayMsgBox (
    IN CHAR16  *MsgBoxTitle,
    IN CHAR16  *Message,
    IN UINT8   MsgBoxType,
    OUT UINT8  *MsgBoxSel
	)
{
	UINTN currenttextModeCols = 0, currenttextModeRows = 0;
	UINT32 currentGOPMode = 0;
	
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if (NULL == gST->ConOut)
		return EFI_NOT_READY;

	if( gPostStatus == TSE_POST_STATUS_IN_POST_SCREEN )
		SaveGraphicsScreen();

	Status = SaveCurrentTextGOP (&currenttextModeCols, &currenttextModeRows, &currentGOPMode);
	if (EFI_ERROR(Status))
		return Status;

	Status = ShowPostMsgBox(MsgBoxTitle, Message, MsgBoxType,MsgBoxSel);

	RestoreTextGOPMode (currenttextModeCols, currenttextModeRows, currentGOPMode);

	if( gPostStatus == TSE_POST_STATUS_IN_POST_SCREEN )
		RestoreGraphicsScreen();

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PostManagerDisplayQuietBootMessage
//
// Description:	Function for the quit booting display.
//
// Input:	CHAR16 *Message, INTN CoOrdX, INTN CoOrdY,
//					CO_ORD_ATTRIBUTE Attribute, EFI_UGA_PIXEL Foreground,
//					EFI_UGA_PIXEL Background
//
// Output:	Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PostManagerDisplayQuietBootMessage(
    CHAR16 *Message,
    INTN CoOrdX,
    INTN CoOrdY,
    CO_ORD_ATTRIBUTE Attribute,
    EFI_UGA_PIXEL Foreground,
    EFI_UGA_PIXEL Background
    )
{
#ifdef STANDALONE_APPLICATION
	return EFI_UNSUPPORTED;
#elif defined TSE_FOR_APTIO_4_50
    UINTN BltGlyphWidth=0;
    EFI_UGA_PIXEL *BltBuffer=NULL;
    UINTN BltIndex;
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN SizeOfX, SizeOfY;

	if (NULL == gST->ConOut)
		return EFI_NOT_READY;

    UpdateGoPUgaDraw();//EIP:50479 : Function to Update gGop before using it in AMITSE.
    if(EFI_SUCCESS != HiiInitializeProtocol())
        return EFI_UNSUPPORTED;

    if(
        (EFI_SUCCESS != GetScreenResolution(&SizeOfX, &SizeOfY))||
        (!gQuietBoot)
        )
        return EFI_UNSUPPORTED;

    if ((Message != NULL) && (EfiStrLen(Message) == 0)) 
		return EFI_SUCCESS;
    BltIndex = 0;

	Status = HiiString2BltBuffer(Message,Foreground,Background,&BltIndex,&BltBuffer,&BltGlyphWidth);
	if(Status == EFI_SUCCESS)
	    DrawBltBuffer(BltBuffer, Attribute, BltIndex, HiiGetGlyphHeight(), CoOrdX, CoOrdY, BltGlyphWidth);

    //Free BltBuffer
    MemFreePointer((VOID **)&BltBuffer);

    return Status;
#else
// For EDK Nt32 support.
//    Status = DrawHiiStringBltBuffer(Message, CoOrdX, CoOrdY, Attribute, Foreground, Background);
	return EFI_UNSUPPORTED;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PostManagerGetPostStatus
//
// Description:	Function returns current Post status.
//
// Input:		none
//
// Output:		One of the TSE_POST_STATUS
// 					TSE_POST_STATUS_BEFORE_POST_SCREEN 	- TSE Loaded and yet goto post screen
// 					TSE_POST_STATUS_IN_POST_SCREEN		- In the post screen
// 					TSE_POST_STATUS_IN_QUITE_BOOT_SCREEN- In the quite boot screen
// 					TSE_POST_STATUS_IN_BOOT_TIME_OUT	- Witing for Boot timeout
// 					TSE_POST_STATUS_ENTERING_TSE		- Entering TSE
// 					TSE_POST_STATUS_IN_TSE				- Inside TSE
// 					TSE_POST_STATUS_IN_BBS_POPUP		- Inside BBS Poupup
// 					TSE_POST_STATUS_PROCEED_TO_BOOT		- Outside TSE and Booting or in Shell
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
TSE_POST_STATUS	PostManagerGetPostStatus(VOID)
{
	return gPostStatus;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PostManagerDisplayInfoBox
//
// Description:	Function to display the Information box
//
// Input:		none
//
// Output:		One of the TSE_POST_STATUS
// 					TSE_POST_STATUS_BEFORE_POST_SCREEN 	- TSE Loaded and yet goto post screen
// 					TSE_POST_STATUS_IN_POST_SCREEN		- In the post screen
// 					TSE_POST_STATUS_IN_QUITE_BOOT_SCREEN- In the quite boot screen
// 					TSE_POST_STATUS_IN_BOOT_TIME_OUT	- Witing for Boot timeout
// 					TSE_POST_STATUS_ENTERING_TSE		- Entering TSE
// 					TSE_POST_STATUS_IN_TSE				- Inside TSE
// 					TSE_POST_STATUS_IN_BBS_POPUP		- Inside BBS Poupup
// 					TSE_POST_STATUS_PROCEED_TO_BOOT		- Outside TSE and Booting or in Shell
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PostManagerDisplayInfoBox(	IN CHAR16		*InfoBoxTitle,
							IN CHAR16		*InfoString,
							IN UINTN		Timeout,
							OUT EFI_EVENT	*Event
						 )
{
	UINTN currenttextModeCols = 0, currenttextModeRows = 0;
	UINT32 currentGOPMode = 0;
	EFI_STATUS Status = EFI_SUCCESS;

	if (NULL == gST->ConOut)
		return EFI_NOT_READY;

	Status = SaveCurrentTextGOP (&currenttextModeCols, &currenttextModeRows, &currentGOPMode);

	if ( EFI_ERROR(Status) )
		return Status;

	Status = ShowInfoBox(InfoBoxTitle, InfoString, Timeout, Event);

	RestoreTextGOPMode (currenttextModeCols, currenttextModeRows, currentGOPMode);

	return Status;

}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     	PostManagerSetAtribute
//
// Description:  	Function to set color
//
// Input:		UINT8 Attrib - Text color 
//			 
//
// Output:		EFI_STATUS status - If the function runs correctly, returns
//			EFI_SUCCESS, else other EFI defined error values.
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerSetAttribute(UINT8 Attrib)
{
	gPostMgrAttribute = Attrib ;
	return EFI_SUCCESS ;
}
//EIP-41838: New interface to get the attribute using AMI Post Manager Protocol
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     	PostManagerGetAttribute
//
// Description:  	Function to Get color
//
// Input:		UINT8 *Attrib - Pointer to get Text color 
//			 
//
// Output:		EFI_STATUS status - If the function runs correctly, returns
//			EFI_SUCCESS, else other EFI defined error values.
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerGetAttribute(UINT8 *Attrib)
{
	*Attrib = gPostMgrAttribute ;
	return EFI_SUCCESS ;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     PostManagerDisplayMsgBoxEx
//
// Description:  Wrapper function for Display OEM Message box. 
//               
//
// Input:    IN CHAR16  *MsgBoxTitle - Caption of the Message Box
//			 IN CHAR16  *Message	 - String to be displayed by the Message Box
//			 IN CHAR16  *Legend		 - Legend String to be displayed by the Message Box
//			 IN UINT8   MsgBoxType   - Message Box type
//
// Output: EFI_STATUS status - EFI_SUCCESS if OK,
//                             EFI_INVALID_PARAMETER if NULL pointer
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerDisplayMsgBoxEx (
    IN CHAR16			*Title,
    IN CHAR16			*Message,
    IN CHAR16			*Legend,
    IN MSGBOX_EX_CATAGORY	MsgBoxExCatagory,
    IN UINT8	 		MsgBoxType,
    IN UINT16			*OptionPtrTokens,	// Valid only with MSGBOX_TYPE_CUSTOM 
    IN UINT16	 		OptionCount,		// Valid only with MSGBOX_TYPE_CUSTOM
    IN AMI_POST_MGR_KEY		*HotKeyList, 		// NULL - AnyKeyPress closes
    IN UINT16 			HotKeyListCount, 
    OUT UINT8			*MsgBoxSel,
    OUT AMI_POST_MGR_KEY	*OutKey
)
{
	UINTN currenttextModeCols = 0, currenttextModeRows = 0;
	UINT32 currentGOPMode = 0;
	EFI_STATUS Status = EFI_SUCCESS;
	
	if (NULL == gST->ConOut)
		return EFI_NOT_READY;

	Status = SaveCurrentTextGOP (&currenttextModeCols, &currenttextModeRows, &currentGOPMode);

	if ( EFI_ERROR(Status) )
		return Status;

	Status = ShowPostMsgBoxEx (Title, Message, Legend, MsgBoxExCatagory,
										MsgBoxType, OptionPtrTokens, OptionCount,
										HotKeyList, HotKeyListCount, MsgBoxSel, OutKey
										);

	RestoreTextGOPMode (currenttextModeCols, currenttextModeRows, currentGOPMode);

	return Status;
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     PostManagerDisplayProgress
//
// Description:  Wrapper function for Display OEM Message box. 
//               
//
// Input:    IIN UINTN Percent  - Percent Complete
//
// Output: EFI_STATUS status - EFI_SUCCESS if OK,
//                             EFI_INVALID_PARAMETER if NULL pointer
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerDisplayProgress (
    IN UINT8	ProgressBoxState, 
    IN CHAR16	*Title,
    IN CHAR16	*Message,
    IN CHAR16	*Legend,
    IN UINTN 	Percent,	// 0 - 100
    IN OUT VOID	**Handle,	//Out HANDLE. Valid Handle for update and close
    OUT AMI_POST_MGR_KEY	*OutKey	//Out Key 
)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	
	if (NULL == gST->ConOut)
		return EFI_NOT_READY;
		
	Status =  ShowPostProgress( ProgressBoxState, Title, Message, Legend, Percent, Handle, OutKey) ;
	return Status ;
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	PostManagerDisplayMenu
//
// Description:	Wrapper function for Display Menu. 
//               
//
// Input:    	IN VOID	*HiiHandle, 		- Handle that contains String
//    		IN UINT16 	TitleToken,     - Menu Title Token
//    		IN UINT16 	LegendToken,	- Menu Legend Token  
//    		IN POSTMENU_TEMPLATE *MenuData, - Menu Items to be displayed 
//    		IN UINT16 	MenuCount,	- Number of Menu items
//    		OUT UINT16  *pSelection		- Menu selection (DEFAULT)
//
// Output: 	EFI_STATUS status 		- EFI_SUCCESS if OK,
//                             			EFI_INVALID_PARAMETER if NULL pointer
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PostManagerDisplayMenu (
    IN VOID	*HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN UINT16 	LegendToken,	  
    IN POSTMENU_TEMPLATE *MenuData,
    IN UINT16 	MenuCount,
    OUT UINT16  *pSelection
)
{
	UINTN currenttextModeCols = 0, currenttextModeRows = 0;
	UINT32 currentGOPMode = 0;
	EFI_STATUS 	Status = EFI_SUCCESS;

	if (NULL == gST->ConOut)
		return EFI_NOT_READY;

	if(gPostStatus < TSE_POST_STATUS_IN_BOOT_TIME_OUT)
		return EFI_NOT_READY;
	
	Status = SaveCurrentTextGOP (&currenttextModeCols, &currenttextModeRows, &currentGOPMode);

	if ( EFI_ERROR(Status) )
		return Status;
		
	Status = ShowPostMenu(HiiHandle, TitleToken, LegendToken, MenuData, MenuCount, pSelection);

	RestoreTextGOPMode (currenttextModeCols, currenttextModeRows, currentGOPMode);

	return Status;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     PostManagerDisplayTextBox
//
// Description:  Function to display text entry interface
// 
//
// Input:   IN VOID    *HiiHandle,
//    		IN UINT16 	TitleToken,
//    		IN TEXT_INPUT_TEMPLATE *InputData,
//          IN UINT16 	ItemCount,
//          IN DISPLAY_TEXT_KEY_VALIDATE ValidateKeyFunc
//
// Output: EFI_STATUS
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PostManagerDisplayTextBox (
    IN VOID	    *HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN TEXT_INPUT_TEMPLATE *InputData,
    IN UINT16 	ItemCount,
    IN DISPLAY_TEXT_KEY_VALIDATE ValidateKeyFunc
	)
{
	UINTN currenttextModeCols = 0, currenttextModeRows = 0;
	UINT32 currentGOPMode = 0;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	
	if (NULL == gST->ConOut)
		return EFI_NOT_READY;

	Status = SaveCurrentTextGOP (&currenttextModeCols, &currenttextModeRows, &currentGOPMode);

	if ( EFI_ERROR(Status) )
		return Status;

	Status = ShowPostTextBox(HiiHandle, TitleToken, InputData, ItemCount, ValidateKeyFunc);

	RestoreTextGOPMode (currenttextModeCols, currenttextModeRows, currentGOPMode);

	return Status;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	StopClickEvent
//
// Description:	Function to Stop the Click Event
//               
// Input:    	VOID	
//
// Output: 	VOID 
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StopClickEvent(VOID)
{
	if(gClickTimer)
	{
		gBS->SetTimer ( gClickTimer,TimerCancel,0);
		TimerStopTimer( &gClickTimer );
	}
}

//EIP 128665 starts
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     	InvalidateBgrtStatusByProtocol
//
// Description: 	Protocol interface to invalidate BGRT status
// 
//
// Input:   		VOID
// 
//
// Output: 			EFI_STATUS
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InvalidateStatusInBgrtWrapper (VOID);
EFI_STATUS InvalidateBgrtStatusByProtocol (VOID)
{
	InvalidateStatusInBgrtWrapper();
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	InvalidateBGRTStatusProtocol
//
// Description:	Install Invalidate BGRT status protocol
//
// Parameter:	EFI_HANDLE Handle
//
// Return value:EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InstallInvalBGRTStatusProtocol (EFI_HANDLE Handle)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gTSEInvalidateBgrtStatusProtocolGuid,
                  &gInvalidateBgrtStatus,
                  NULL
                  );

  return Status;
}
//EIP 128665 ends

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name				:	SaveCurrentTextGOP
//
// Description		:	Function to Save current TextMode and GOP
//               
// Input				:  UINTN currentTextModCols, UINTN currentTextModRows, UINT32 currentGOPMode
//
// Output			:	EFI_STATUS
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SaveCurrentTextGOP ( UINTN *currenttextModeCols, UINTN *currenttextModeRows, UINT32 *currentGOPMode )
{

	EFI_STATUS 	Status = EFI_SUCCESS;
	
	if ( IsTseBestTextGOPModeSupported() && TSE_POST_STATUS_IN_TSE != gPostStatus )
	{
		if (gGOP)
		{
			*currentGOPMode = gGOP->Mode->Mode;
		}

		if (TSE_BEST_HORIZONTAL_RESOLUTION != gGOP->Mode->Info->HorizontalResolution || TSE_BEST_VERTICAL_RESOLUTION != gGOP->Mode->Info->VerticalResolution)
		{
			SetScreenResolution(TSE_BEST_HORIZONTAL_RESOLUTION,TSE_BEST_VERTICAL_RESOLUTION); //If any postinterface is invoked during QuietBoot
		}

		Status = gST->ConOut->QueryMode( gST->ConOut, gST->ConOut->Mode->Mode, currenttextModeCols, currenttextModeRows);
		if (EFI_ERROR(Status))
			return EFI_NOT_FOUND;

		if ((STYLE_FULL_MAX_COLS != *currenttextModeCols)  || (STYLE_FULL_MAX_ROWS != *currenttextModeRows))
		{
			gMaxRows = STYLE_FULL_MAX_ROWS;
			gMaxCols = STYLE_FULL_MAX_COLS;
			SetDesiredTextMode ();
		}
	}
	return Status;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name				:	RestoreTextGOPMode
//
// Description		:	Function to Save current TextMode and GOP
//               
// Input				:  UINTN currentTextModCols, UINTN currentTextModRows, UINT32 currentGOPMode
//
// Output			:	EFI_STATUS
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RestoreTextGOPMode ( UINTN prevTextModeCols, UINTN prevTextModeRows, UINT32 prevGOPMode )
{
	EFI_STATUS 	Status = EFI_SUCCESS;

	if ( IsTseBestTextGOPModeSupported() && TSE_POST_STATUS_IN_TSE != gPostStatus )
	{
		if ( (gMaxRows != prevTextModeRows) || (gMaxCols != prevTextModeCols) )
		{
			gMaxRows = prevTextModeRows; 
			gMaxCols = prevTextModeCols;
			SetDesiredTextMode (); //Restoring to previous textmode if any changed
		}

		if (gGOP && prevGOPMode != gGOP->Mode->Mode)
		{
			Status = gGOP->SetMode (gGOP, prevGOPMode);	//In some case changing text mode will change the graphcis mode, so reverting here.
		}
	}
	return Status;
}
//EIP-107833 END

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2014, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
