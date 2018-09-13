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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/TseAdvanced.c $
//
// $Author: Premkumara $
//
// $Revision: 69 $
//
// $Date: 9/05/14 2:39p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/TseAdvanced.c $
// 
// 69    9/05/14 2:39p Premkumara
// Moved GetSetDefaultsFromControlPtr() function from Uefi2.1\Hii.c to
// TseAdvanced.c
// 
// 68    8/28/14 9:39a Premkumara
// [TAG] 		EIP172956
// [Category]	Bug Fix
// [Severity:]                Critical
// [Symptom:]	Build error is displayed when TSE_CLEAR_USERPW_WITH_ADMINPW
// token is ON
// [Root Cause]	When we do clear password then with Admin password its
// only clearing user password from cache not from NVRAM. But in ESA it
// working fine
// [Solution]  	In ClearUserPasswordPolicy in TseAdvanced.c, we just
// clearing password from Cache not from NVRAM if save paswd to nvram
// token ios ON, so added that feature.
// [Files] 		TseAdvanced.c
// 
// 67    8/28/14 9:28a Premkumara
// [TAG] 		EIP170151
// [Category] 	Bug Fix
// [Severity:] 	Normal
// [Symptom:] 	DisplayTextBox does not close before it returns.
// [Root Cause] 	Text box was not clearing before showing message box or
// info box.
// [Solution] 		modified the code to clear the Text box before showing
// message box or info box
// [Files] 		TseAdvanced.c
// 
// 66    8/28/14 6:48a Premkumara
// [TAG]	EIP93340
// [Category]	Improvement
// [Description]	- Defaults can be given to string type controls using tag
// "Default = STRING_TOKEN(STR_DEFAULT_STRING)".
// - New token TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL is introduced for
// this support.
// - Enabling this TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL token will
// display default string mention in setup.
// - On loading optimal defaults also string will load default mentioned
// in default value tag.
// [Files] AMITSE.sdl, HiiString21.c, TseAdvanced.c, MiniSetupExt.c, Hii.c
// 
// 65    5/02/14 8:44a Premkumara
// [TAG]  		EIP162981
// [Category]  	Improvement
// [Description]  	Configuring default Password through SDL token
// [Files]  		AMITSE.sdl, CommonHelper.c, Minisetup.c, TseAdvanced.c
// 
// 64    5/02/14 2:20a Premkumara
// [TAG]  		EIP131553
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	SoftKbd clearance issue on selecting UEFI shell from Save
// and Exit tab [when SoftKbd icon is selected]
// [RootCause]  	TSE was deactivating the softkbd after clearing the 
// screen when we are selecting UEFI shell from Save and Exit tab
//  [when SoftKbd icon is selected].
// [Solution]  	Modified the code to deactivate the softkbd before
// clearing
//  the TSE screen when we are selecting UEFI shell from Save and Exit tab
//  [when SoftKbd icon is selected].
// [Files]  		TseAdvanced.c
// 
// 63    5/01/14 11:27p Arunsb
// [TAG]  		EIP128948
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	TSE security code check failure for using uninitialized
// variable "Action"
// [RootCause]  	Action variable in TimeHanldeActionKeyMouse and
// _PostPopupEditGetValues is not initialized
// [Solution]  	Initialized Action variable.
// [Files]  		Time.c, TseAdvanced.c
// 
// 62    2/11/14 7:49p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 61    11/26/13 9:48a Premkumara
// [TAG]  		EIP118342
// [Category]  	Improvement
// [Description]  	Show meaningful error message when HDD is locked after
// reached maximum unlocking attempt.
// [Files]  		TseAdvanced.c, CommonHelper.c, FakeToken.c, AmiTseStr.uni
// 
// 60    11/26/13 1:31a Premkumara
// [TAG]  		EIP118342
// [Category]  	Improvement
// [Description]  	Show meaningful error message when HDD is locked after
// reached maximum unlocking attempt.
// [Files]  		TseAdvanced.c, CommonHelper.c
// 
// 59    11/06/13 1:26a Premkumara
// [TAG]  		EIP128948
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	TSE security code check failure for using uninitialized
// variable "Action"
// [RootCause]  	Action variable in TimeHanldeActionKeyMouse and
// _PostPopupEditGetValues is not initialized
// [Solution]  	Initialized Action variable.
// [Files]  		Time.c, TseAdvanced.c
// 
// 58    10/07/13 3:06a Premkumara
// Intergrated missed EIP130529 changes (sysAccessGuid variable in
// LoadUserDefaultsSilently) to avoid build error
// 
// 57    9/19/13 7:58a Arunsb
// [TAG]	EIP127375
// [Category]	Bug Fix
// [Severity:]	Critical
// [Symptom:]	Legacy boot doesn't work after UEFI Shell is launched from
// LaunchAppHotkey menu. The system hangs
// [Root Cause]	If ShowPostMsgBoxEx is invoked through postmgr protcol
// then gMsgBoxAction will be NULL initially,
// so this time action is assigned and used. 
// ACTION_DATA *action = gMsgBoxAction; so accessing NULL pointer leads to
// hang.
// [Solution]	gMsgBoxAction is created again inside ShowPostMsgBoxEx, 
// reassign gMsgBoxAction to action.
// [Files]	TseAdvanced.c
// 
// 56    8/06/13 4:02a Premkumara
// [TAG]  		EIP130529 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When entered into setup with User mode and On pressing
// "Restore User Defaults" SystemAccess variable is loading and the user
// mode is changes to Admin mode so the controls are editable
// [RootCause]  	LoadUserDefaultsSilently() function is loading defaults
// for all types of variable
// [Solution]  	Skipping loading SystemAccess variable while loading
// defaults for user default variable.
// [Files]  		TseAdvanced.c, AMITSE.sdl, CommonHelper.c 
// 
// 55    5/23/13 3:44a Premkumara
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
// - TseAdvanced.c
// 
// 54    5/22/13 10:22a Arunsb
// [TAG]  		EIP122907
// [Category]  	Improvement
// [Description]  	For getting name value offset preserving page number
// then it will be easy to find handle of the hii which published name
// value
// 
// 53    12/05/12 5:20a Arunsb
// [TAG]  		EIP106749
// [Category]  	New Feature
// [Description]  	Message box can lock the computer if ConIn not present
// [Files]  		TseAdvanced.c
// 
// 52    10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 40    10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 50    10/10/12 11:22a Arunsb
// 
// 49    10/10/12 11:21a Arunsb
// Properly checked in the EIP98918
// 
// 48    9/24/12 1:17a Premkumara
// [TAG]  		EIP98918
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Restore User Defaults causes system hang
// [Files]  		TseAdvanced.c
// 
// 47    9/21/12 12:33p Premkumara
// [TAG]  		EIP99092
// [Category]  	Improvement
// [Description]  	Tokenize the feature of flushing keyboard after every
// key read
// [Files]  		AMITSE.sdl, CommonHelper.c, TseAdvanced.c, Action.c
// 
// 46    9/17/12 6:08a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 44    9/03/12 3:12a Premkumara
// [TAG]  		EIP 96246
// [Category]  	Improvement
// [Description]  	Improvement of a boots override when firmware has a
// BootNext variable
// [Files]  		AMITSE.sdl, CommonHelper.c, FakeToken.c, AmiTSEStr.uni,
// TseAdvanced.c
// 
// 43    5/28/12 6:23a Rajashakerg
// [TAG]  		EIP80873
// [Category]  	Improvement
// [Description]  	TSE Load/Save defaults without Messaaagebox.
// [Files]  		TseElinks.h, Tseadvanced.c
// 
// 42    5/24/12 9:00a Arunsb
// [TAG]  		EIP90379
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	UefiBootFailHook asserts when it is trying to call
// MsgBoxDestroy
// [RootCause]  	Tried to free the NULL pointer
// [Solution]  	Checked NULL before freeing
// [Files]  		TseAdvanced.c and MessageBox.c
// 
// 41    5/09/12 4:56p Premkumara
// [TAG]  		EIP87117 
// [Category]  	Improvement
// [Description]  	AMITSE should handle partial key support
// [Files]  		TseAdvanced.c
// 
// 40    2/02/12 1:15p Premkumara
// [TAG]  		EIP75351,75352,75384
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		String.c, boot.c, TseAdvanced.c,Time.c, PopupEdit.c,
// MessageBox.c, Label.c, Edit.c, Date.c
// 
// 39    1/13/12 1:22a Arunsb
// [TAG]  		EIP80360
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	HDDSecurity module - Issue in login with TSE, Master
// password disabled
// [RootCause]  	Cache not updated
// [Solution]  	Cache updated properly
// [Files]  		Tseadvanced.c, special.c and uefi21wapper.c
// 
// 38    12/08/11 12:30p Rajashakerg
// Updated the file to overcome build errors when build for x32 mode.
// 
// 37    12/01/11 7:16p Blaines
// Fix build errors in Uefi2.0
// 
// 36    11/30/11 1:28p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 35    11/30/11 12:00p Premkumara
// [TAG]  		EIP75521
// [Category]  	Improvement
// [Description]  	Need to support interactive password controls
// [Files]  		PopupPassword.c, PopupPassword.h, TsetAdvanced.c
// 
// 34    11/30/11 12:25a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 33    11/16/11 11:21a Madhans
// [TAG]  		EIP75736
// [Category]  	Improvement
// [Description]  	To avoid flicks when booting UEFI OS for seamless boot.
// [Files]  		Boot.c 
// Tseadvanced.c
// 
// 32    11/14/11 2:01p Blaines
// Add function headers for the changes made in TSEAdvanced.c for EIP
// 66860
// 
// 31    11/13/11 12:50p Arunsb
// [TAG]  		EIP70421
// [Category]  	New Feature
// [Description]  	Support for driver order in TSE
// [Files]  		AMITSE.SDL, CommonHelper.c, setup.ini, uefisetup.ini,
// boot.c,
// minisetup.h, bbs.c, special.c, special.h, tseadvanced.c,
// addbootoption.c,
// callback.c, minisetupext.c, minisetupext.h, popupsel.c, popupsel.h,
// TseLitehelper.c, variable.c, Uefi21Wapper.c, AMIVfr.h, boot.h,
// TseElink.h, variable.h, 
// setup.h, Boot.vfr and Setup.uni
// 
// 30    11/10/11 7:25p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// Added new parameter to the function prototype DISPLAY_TEXT_KEY_VALIDATE
// 
// Initialize textbox witih default value
// 
// 29    11/10/11 12:51a Arunsb
// [TAG]  		EIP67735
// [Category]  	Improvement
// [Description]  	Zeroing password buffers before freeing
// [Files]  		mem.c, mem.h, popupedit.c, popuppassword.c and tseadvanced.c
// 
// 28    10/31/11 9:41a Rajashakerg
// [TAG]  		EIP71120,71512 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BIOS gets stuck in infinite loop On enabling
// TSE_LOAD_OPTION_HIDDEN token,In first boot incorrect devices is
// disabled in Setup & BBS table but in second boot the correct device is
// disabled in both places.
// [Solution]  	Hidden option handled properly.
// [Files]  		TseLite\variable.c, TseLite\minisetupext.c, TseAdvanced.c,
// special.c, BootOnly\minisetup.h,BootOnly\boot.c, BootOnly\bbs.c
// 
// 27    10/19/11 3:52p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry. Add cursor
// support.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c,
// uefi20Wapper.c, PopupEdit.c
// 
// 26    9/29/11 7:02p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 25    7/19/11 12:30p Arunsb
// [TAG]  		EIP63895
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Same message "Save & reset" displayed twice
// [RootCause]  	guidInfo->GuidFlags.GuidLaunchFilename condition also
// executed after executing guidInfo->GuidFlags.GuidLaunchGuid condition.
// [Solution]  	Made as any one condition will execute
// [Files]  		Tseadvanced.c
// 
// 24    6/30/11 4:12a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Driver health special controls handled.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 23    12/29/10 6:51a Mallikarjunanv
// [TAG]  		EIP 49745 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Hangs on CP06 when Core is update to 4.6.4.1
// [RootCause]  	It hangs on CP06 when go to SETUP if updated core to
// 4.6.4.1 and added TSE source and X64 = 0.
// [Solution]  	Fixed the Stack Frame corruption by passing NULL for Var
// or Flags.
// [Files]  		TseAdvanced.c
// 
// 22    12/28/10 6:09p Mallikarjunanv
// [TAG]  		EIP41615
// [Category]  	New Feature
// [Description]  	Added the file browser support for the Add boot option
// reated controls
// [Files]  		AmiVfr.h, AmiTse.sdl, AmiTseStr.uni, CommonHelper.c,
// Faketokens.c, TseElinks.h, EdkHelper.h, minisetup.h, TseAdvanced.c,
// AddBootOption.c
// 
// 21    12/28/10 12:54p Mallikarjunanv
// [TAG]  		EIP 47260
// [Category]  	Improvement
// [Description]  	Updated with TSE_NVRAM_DEFAULTS_SUPPORT token name
// [Files]  		TseAdvanced.sdl, TseAdvanced.c
// 
// 20    12/24/10 1:15p Mallikarjunanv
// [TAG]  		EIP 47932
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Screen changing to Normal TSE from GTSE if the boot fails
// rom the selected boot option
// [RootCause]  	Style Initilization is not done before BootLaunchFailed .
// [Solution]  	Fixed by updating style Initilization BootLaunchFailed.
// 
// [Files]  		TseAdvanced.c
// 
// 19    12/22/10 5:28a Mallikarjunanv
// [TAG]  		EIP47260
// [Category]  	Improvement
// [Description]  	To Build TSE sources without NVRAM module support. 
// [Files]  		TseAdvanced.c, TseAdvanced.mak, TseAdvanced.sdl
// 
// 18    11/18/10 7:13p Blaines
//  [TAG] - EIP 47962
//  [Category]- Defect
//  [Symptom]- Post Manager's DisplayMsgBox displays a corrupted screen
//  When the French or Japanese langues are selected and a call is made to
// DisplayMsgBox, the screen that is displayed is corrupted
// 
//  [Rootcause]  
//  The bounding box area of the message box is drawn, which may not span
// previous screen redraws. 
// Therefore, artifacts from previous screen displays may appear.
//  [Solution]- Clear the screen before drawing message box to clear
// artifacts from previous screen redraws.
// [Files] - TseAdvanced.c,  AMIPostMgr.h, 
// 
// 17    9/29/10 1:36p Blaines
// Function ShowPostMsgBoxEx was updated to allow a buttonless messages
// box to be displayed without a legend.
// 
// 16    9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 33    8/31/10 11:32a Blaines
// Fix for ShowPostProgress function not calling gAction.Destroy,  casuing
// system to appear to hang and to not be responsive to input.
// 
// 32    8/10/10 7:13p Madhans
// EIP 40555 : To avoid Compilation issues with Fareast Windows.
// 
// 31    6/22/10 5:31a Mallikarjunanv
// EIP:39102 - Handling Scrren corruption if Launching shell from file
// system fails
// 
// 30    6/14/10 7:08p Madhans
// To keep the NVRAM defaults only for Aptio 4.x
// 
// 29    6/08/10 5:13p Blaines
// Fix for EIP #39416 - PostManagerDisplayProgress does not update
// message.
// 
// 28    5/19/10 4:11p Blaines
// Added parameter error checking to the function ShowPostMsgBoxEx
// 
// 27    4/22/10 6:21p Blaines
// Fix build error when TSE_USE_AMI_EFI_KEYCODE_PROTOCOL token
// enabled
// 
// In function ShowPostMsgBoxEx, set property msgbox->Legend before
// calling gMsgBox.Initialize. 
// 
// 26    4/20/10 6:15p Blaines
// Add MessageBox Hotkey support
// 
// 25    4/15/10 4:49p Blaines
// In function ShowPostMsgBox, 
// check if pSelection is null before it attempts to use it.
// 
// 24    4/07/10 6:24p Madhans
// To Fix the build issue.
// 
// 23    3/30/10 4:46p Blaines
// EIP 36704 : Fix for Making sure to make the Variable to NULL after it
// is Freed up.
// 
// 22    3/26/10 6:12p Madhans
// EIP 36704 : Fix for Making sure to make the Variable to NULL after it
// is Freed up.
// 
// 21    3/26/10 6:01p Madhans
// Fix in Load Defaults from NVRAM Defaults, To make work for Runtime
// pages. Before this fix it only work for Offline parsing Data and For
// Runtime pages the defaults are broken.
// 
// 20    3/23/10 5:11p Blaines
// Add support for new PostManager Extentions
// 
// 19    3/19/10 2:39p Madhans
// Support to Load Defaults from NVRAM Defaults.
// 
// 18    2/26/10 11:09a Madhans
// to resove build errors;.
// 
// 17    2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
// 
// 16    2/15/10 10:13p Madhans
// For EDK Nt32 version
// 
// 15    2/04/10 11:19p Madhans
// Fix for Password with AMIKeyCode ON without EfiKey or Scancode support.
// 
// 14    1/18/10 2:09a Mallikarjunanv
// EIP-28501: Updated for Keyboard scancode as password. Added a new Token
// SETUP_STORE_KEYCODE_PASSWORD to support the EFI key or Scan code as
// password
// 
// 13    1/09/10 4:51a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 12    10/30/09 9:47a Mallikarjunanv
// EIP-28551 : Fixed TSE 2.0 Build error releated to
// SETUP_STORE_EFI_KEY_PASSWORD and TSE_USE_AMI_EFI_KEYCODE_PROTOCOL 
// 
// 11    9/17/09 9:05a Sudhirv
// EIP:25799 - Remove Load Driver Option from TSE 2.x as it will be
// handled from Core
// 
// 10    9/15/09 9:41a Sudhirv
// updated with support for SETUP_OEM_SPECIAL_CONTROL_SUPPORT and the
// support for Add Del boot option support
// 
// 9     8/19/09 6:33p Madhans
// IsToggleStateKey Function added
// 
// 8     8/19/09 10:42a Mallikarjunanv
// Fixed the issue regarding loading defaults by desabling the chipset
// menu.
// 
// 7     8/13/09 7:37a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
// 
// 6     7/30/09 7:48a Mallikarjunanv
// updated the code to move the exit page option elinks to Tse Binary
// 
// 5     7/20/09 1:17p Mallikarjunanv
// updated the return values 
// 
// 4     6/23/09 7:09p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 3     6/12/09 7:43p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 2     6/05/09 11:55a Blaines
// Fix screen corruption for GTSE
// 
// 1     6/04/09 8:05p Madhans
// 
// 3     5/07/09 10:36a Madhans
// Changes after Bin module
// 
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 11:16p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:27p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		TseAdvanced.c
//
// Description:	This file contains code to handle the Advanced TSE Operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include "Special.h"
#include "TseElinks.h"

//////////////////////////////////////////////////
/////// INTERNAL VARIABLE DECLARATION
//////////////////////////////////////////////////
///Exit Page options info. from Elink...
extern EXIT_PAGE_OPTIONS gExitPageOptions[END_OF_EXIT_PAGE_OPTION_LIST];
extern APPLICATION_DATA *gApp;
extern UINTN gSaveUserMsgBox;
extern UINTN gLoadUserMsgBox;
extern UINTN gBootLaunchFailedMsgBox;
extern UINTN gInvalidPasswordFailMsgBox;


#define AMITSE_PRINT_SCREEN_PRESS_GUID \
{ 0x71030b81, 0xf72, 0x4b48, 0xb5, 0xe8, 0xbc, 0xcd, 0x51, 0x78, 0x60, 0x9e }


#define	CONSTRUCT_DEFAULTS_FIRST_BOOT_GUID	\
{ 0xc5912ed9, 0x83c2, 0x4bff, 0x99, 0x36, 0x23, 0x1f, 0xeb, 0x85, 0xf3, 0xe8 }

MSGBOX_DATA *gInfoBox = NULL;
UINT32			gtempCurrentPage;
//////////////////////////////////////////////////
/////// INTERNAL FUNCTIONS DECLARATION
//////////////////////////////////////////////////
///Exit page options handling using Elinks...
VOID HandleSaveAndExit(VOID);
VOID HandleExitApplication(VOID);
VOID HandleSaveAndReset(VOID);
VOID HandleResetSys(VOID);
VOID HandleSaveWithoutExit(VOID);
VOID HandleLoadPreviousValues(VOID);
VOID HandleLoadOptimalDefaults(VOID);
VOID HandleSaveUserDefaults(VOID);
VOID HandleRestoreUserDefaults(VOID);
VOID HandleBootAddBootOption(VOID);
VOID HandleDriverAddDriverOption(VOID);

//EIP-41615: Start 
VOID HandleLaunchFileSystem(VOID);
VOID HandleLaunchFileSystemDriver(VOID);
//EIP-41615: End

VOID SaveUserDefaults( VOID );
VOID LoadUserDefaults( VOID );
BOOLEAN CheckIsAllowedPasswordChar(CHAR16 Char);
BOOLEAN CheckIsAllowedChar(CHAR16 Char);

//////////////////////////////////////////////////
/////// EXTERN FUNCTIONS DECLARATION
//////////////////////////////////////////////////
extern VOID 			*UefiCreateStringTemplate(UINT16 Token);
extern EFI_STATUS 	ReadImageResource(EFI_HANDLE ImageHandle, EFI_GUID *pGuid, VOID **ppData, UINTN *pDataSize);
extern BOOLEAN   		IsLoadSysteAccessOnUserDefault(VOID);
extern BOOLEAN   		IsSupportDefaultForStringControl (VOID);
EFI_STATUS 	GetSetDefaultsFromControlPtr(NVRAM_VARIABLE *optimalDefaultlist, NVRAM_VARIABLE *failSafeDefaultlist);
UINTN 	GetANSIEscapeCode(CHAR16 *String,UINT8 *Bold,UINT8 *Foreground, UINT8 *Background);
VOID 		OEMSpecialGotoSelect(UINT16 value);
BOOLEAN 	IsShowPromptStringAsTitle(VOID);//EIP-116315 password window title string
extern BOOLEAN TSEPwdSavetoNvram(VOID);

typedef UINT16 VAR_SIZE_TYPE;
#pragma pack(push)
#pragma pack(1)
typedef struct{
	UINT32 signature;
	VAR_SIZE_TYPE size;
	UINT32 next:24;
	UINT32 flags:8;
//  guid and name are there only if NVRAM_FLAG_DATA_ONLY is not set
//	UINT8 guid; 
//	CHAR8 or CHAR16 name[...];
//  UINT8 data[...];
//  if NVRAM_FLAG_EXT_HEDER is set
//  UINT8 extflags;
//  UINT8 extdata[...];
//  VAR_SIZE_TYPE extsize;
}NVAR;
#pragma pack(pop)

typedef struct {
    UINT8 *NvramAddress;
    UINTN NvramSize;
    EFI_GUID* NvramGuidsAddress;
    UINT8 *pEndOfVars, *pFirstVar;
    INT16 NextGuid;
    VAR_SIZE_TYPE LastVarSize;
    NVAR *pLastReturned;
    UINT8 Flags;
} NVRAM_STORE_INFO;


VOID NvInitInfoBuffer(IN NVRAM_STORE_INFO *pInfo, UINTN HeaderSize, UINT8 Flags);
EFI_STATUS NvGetVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID *Data,
    IN NVRAM_STORE_INFO *pInfo, OUT UINT8 *Flags
);
BOOLEAN IsTseLoadPasswordOnDefaults();

#define NVRAM_STORE_FLAG_NON_VALATILE 1

#define DEFAULTS_GUID {0x4599d26f, 0x1a11, 0x49b8, 0xb9, 0x1f, 0x85, 0x87, 0x45, 0xcf, 0xf8, 0x24}

EFI_GUID DefaultsGuid = DEFAULTS_GUID;
VOID SetDrvHealthHandleAndCtrlCount (UINT16);
VOID DoDriverHealthOperation (CONTROL_INFO *, UINT16);
BOOLEAN   FlushKeysAfterRead(void);
//EIP-96246 starts
EFI_STATUS 	ShowBootOverrideSelectOption (VOID);
BOOLEAN  	IsBootOverrideBootNextSupport (VOID);
#define BOOT_OVERRIDE_OPTION_MENU_COUNT 3
//EIP-96246 Ends

#ifndef KEY_STATE_EXPOSED
#define KEY_STATE_EXPOSED   0x40 //EIP-87117 
#endif

//EIP 162981 Providing defaults through sdl tokens
BOOLEAN DefaultSetupPwdAtFirstBootOnly (void);
BOOLEAN TseDefaultSetupPasswordSupported(VOID);
EFI_STATUS GetDefaultPassword (UINT32 PasswordInstalled, void **DefaultPassword);


BOOLEAN TseLiteIsSpecialOptionList(CONTROL_DATA *ControlData)
{
	// For TSE Advanced we papulate and add the control dynamically.
	// So it is not TSE lite Special control
	// TSE Lite special controls are patched instad of removing and adding.
	return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootUpdateOrder
//
// Description:	Function to update the boot/driver order
//
// Input:		UINT16 *buffer
//				UINT32 *offset
//				UINTN *size
//				VOID **realBuffer
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BootUpdateOrder(UINT16 *buffer,UINT32 *offset,UINTN *size, VOID **realBuffer)
{
	UINTN i, j, optionNumber = *offset / sizeof(UINT16);
	UINT16 index = *(UINT16 *)buffer;
	UINT16 newOption = index;
	UINT16 oldOption, *optionList;

#if TSE_SEPERATE_EFI_LEGACY_OPTIONS
	UINT16 *OrgOptionList;
	OrgOptionList = EfiLibAllocateZeroPool( *size );
	MemCopy( OrgOptionList, gVariableList[VARIABLE_ID_BOOT_ORDER].Buffer, *size );
#endif

	*realBuffer = EfiLibAllocateZeroPool( *size );
	if (NULL == *realBuffer)
	{
		return;
	}
	*offset = 0;
	MemCopy( *realBuffer, gVariableList[VARIABLE_ID_BOOT_ORDER].Buffer, *size );

	optionList = (UINT16 *)*realBuffer;
	oldOption = optionList[ optionNumber ];

	if ( newOption == oldOption )
		return;

    if(DISABLED_BOOT_OPTION == newOption)
    {
        for (i = optionNumber, j = 0; i < gBootOptionCount; i++)
        {
            if ((i+1) < gBootOptionCount)
			{
				if ( (CheckHiddenforBootDriverOption (optionList [i + 1], BOOT_ORDER_OPTION))  && gLoadOptionHidden )
				{
					j ++;
					continue;
				}
                optionList [i] = optionList [i + 1];
			}
            else
                optionList [i-j] = newOption; 	// or DISABLED_BOOT_OPTION; boot order will be like active boot option
        }										//then hidden options, so hidden option will always maintain at same place(last positions).
    }
    else if (DISABLED_BOOT_OPTION == oldOption)
    {
        //Find newOption's position
        for(i=0;i<gBootOptionCount;i++)
        {
            if(newOption == optionList[i])
                break;
        }

        if(i < gBootOptionCount)//New option found
        {
            //Move new option to the last of enabled devices
            for(j=i; j<gBootOptionCount; j++)
            {
                if( DISABLED_BOOT_OPTION != optionList[j+1])
                    optionList[j] = optionList[j+1];
                else
                {
                    optionList[j] = newOption;
                    break;
                }
            }
        }
        else//New option not enabled
        {
            //Replace first disabled with new one
            for(i=0;i<gBootOptionCount;i++)
            {
                if(DISABLED_BOOT_OPTION == optionList[i])
                    break;
            }
            optionList[i] = newOption;
        }
#if TSE_SEPERATE_EFI_LEGACY_OPTIONS
        ReGroupOptions(optionList,NULL);
#endif
    }
    else
    {
        optionList[optionNumber] = newOption;
        for(i=0;i<gBootOptionCount;i++)
        {
            if(i == optionNumber)
                continue;
            if(newOption == optionList[i])
            {
                optionList[i] = oldOption;
                break;
            }
        }
#if TSE_SEPERATE_EFI_LEGACY_OPTIONS
        ReGroupOptions(optionList,OrgOptionList);
#endif
    }
#if TSE_SEPERATE_EFI_LEGACY_OPTIONS
	MemFreePointer( (VOID **)&OrgOptionList );
#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DriverUpdateOrder
//
// Description:	Function to update the driver order
//
// Input:		UINT16 *buffer
//				UINT32 *offset
//				UINTN *size
//				VOID **realBuffer
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DriverUpdateOrder (UINT16 *buffer,UINT32 *offset,UINTN *size, VOID **realBuffer)
{
	UINTN i, j, optionNumber = *offset / sizeof(UINT16);
	UINT16 index = *(UINT16 *)buffer;
	UINT16 newOption = index;
	UINT16 oldOption, *optionList;

	*realBuffer = EfiLibAllocateZeroPool (*size);
	if (NULL == *realBuffer)
	{
		return;
	}
	*offset = 0;

	MemCopy (*realBuffer, gVariableList [VARIABLE_ID_DRIVER_ORDER].Buffer, *size);
	optionList = (UINT16 *)*realBuffer;
	oldOption = optionList [optionNumber];

	if (newOption == oldOption)
		return;

    if (DISABLED_BOOT_OPTION == newOption)
    {
        for (i = optionNumber, j = 0; i < gDriverOptionCount; i++)
        {
            if ((i+1) < gDriverOptionCount)
			{
				if ( (CheckHiddenforBootDriverOption (optionList [i + 1], DRIVER_ORDER_OPTION))  && gLoadOptionHidden )
				{
					j ++;
					continue;
				}
                optionList [i] = optionList [i + 1];
			}
            else
                optionList [i-j] = newOption; 	// or DISABLED_BOOT_OPTION; boot order will be like active boot option
        }										//then hidden options, so hidden option will always maintain at same place(last positions).
    }
    else if (DISABLED_BOOT_OPTION == oldOption)
    {
        //Find newOption's position
        for (i = 0; i < gDriverOptionCount; i ++)
        {
            if (newOption == optionList [i])
                break;
        }
        if (i < gDriverOptionCount)//New option found
        {
            //Move new option to the last of enabled devices
            for (j = i; j < gDriverOptionCount; j ++)
            {
                if (DISABLED_BOOT_OPTION != optionList [j+1])
                    optionList [j] = optionList [j+1];
                else
                {
                    optionList [j] = newOption;
                    break;
                }
            }
        }
        else//New option not enabled
        {
            //Replace first disabled with new one
            for (i = 0; i < gDriverOptionCount; i ++)
            {
                if (DISABLED_BOOT_OPTION == optionList [i])
                    break;
            }
            optionList [i] = newOption;
        }
    }
    else
    {
        optionList[optionNumber] = newOption;
        for (i = 0; i < gDriverOptionCount; i ++)
        {
            if(i == optionNumber)
                continue;
            if(newOption == optionList[i])
            {
                optionList[i] = oldOption;
                break;
            }
        }
    }
}

/// functions to handle the exit page options
VOID HandleSaveAndExit()
{
	gApp->Quit = SaveAndExit();
}

VOID HandleExitApplication()
{
	gApp->Quit = ExitApplication();
}

VOID HandleSaveAndReset()
{
	gApp->Quit = SaveAndReset();
}

VOID HandleResetSys()
{
	gApp->Quit = ResetSys();
}

VOID HandleSaveWithoutExit()
{
	SaveWithoutExit();
}

VOID HandleLoadPreviousValues()
{
	LoadPreviousValues( TRUE );
}

VOID HandleLoadOptimalDefaults()
{
	LoadOptimalDefaults();
}

VOID HandleSaveUserDefaults()
{
	SaveUserDefaults();
}

VOID HandleRestoreUserDefaults(VOID)
{
	LoadUserDefaults();
}

VOID HandleBootAddBootOption(VOID)
{
	TseBootAddBootOption();
}

//EIP70421 & 70422
VOID HandleDriverAddDriverOption(VOID)
{
	TseDriverAddDriverOption();
}

// EIP-41615: Function to handle selection of the file system
VOID HandleLaunchFileSystem(VOID)
{
	TseLaunchFileSystem(VARIABLE_ID_ADD_BOOT_OPTION);
}

//EIP70421 & 70422
VOID HandleLaunchFileSystemDriver(VOID)
{
	TseLaunchFileSystem(VARIABLE_ID_ADD_DRIVER_OPTION);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SubMenuAmiCallback
//
// Description:	Function implemented to handle the Exit page 
//				options using Elinks.
//
// Input:		UINT16 value - index of the exit page option
//
// Output:		TRUE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _SubMenuAmiCallback( UINT16 value )
{
	UINT8 idx=0;

	for(idx=0;idx<(sizeof(gExitPageOptions)/sizeof(EXIT_PAGE_OPTIONS));idx++)
	{
		if( gExitPageOptions[idx].OptIdx == END_OF_EXIT_PAGE_OPTION_LIST ) {
			break;
		}
		else if(value == gExitPageOptions[idx].OptIdx) {
			gExitPageOptions[idx].ExitPageCallBack();
			break;
		}
	}

	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_SubMenuHandleSpecialOp
//
// Description:	Sub menu handle for Special operations.
//
// Input:		Submenu data
//
// Output:		Bool - Interpreted by the Caller.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _SubMenuHandleSpecialOp( SUBMENU_DATA *submenu )
{
	BOOLEAN status = FALSE;
	BOOLEAN BootLaunchFailed = FALSE;
	BOOLEAN StyleExitDone = FALSE;
	UINT16 value;
	GUID_INFO *guidInfo;
	EFI_STATUS Status;

// EIP:39412 - START
	VOID *ScreenBuf;	

	//Save the screen buffer to restore later if required
	ScreenBuf = SaveScreen();
// EIP:39412 - END

	value = SpecialGetValue( (CONTROL_DATA *)submenu, &guidInfo );
	if ( value != (UINT16)-2 )
	{
		if ( guidInfo->GuidFlags.GuidLaunchCallback )
		{
			switch ( guidInfo->GuidKey )
			{
				case GUID_KEY_BOOT_NOW:
					//EIP-96246 Starts
					if ( !gResetRequired && IsBootOverrideBootNextSupport () )
					{
						UINT16 *pBootNext = NULL;
						UINTN size = 0;
						pBootNext = (UINT16 *)VarGetNvramName(L"BootNext", &gEfiGlobalVariableGuid, NULL, &size);
						if ( pBootNext && (size == sizeof(UINT16)))//If BootNext Variable is present
						{					
							Status = ShowBootOverrideSelectOption ();//EIP-96246 To show Override menu option for BootNext variable
							if ( Status != EFI_SUCCESS )//Exit menu and retain in override menu
							{
								status = TRUE;
								break;
							}
						}
						if(pBootNext)
	        				MemFreePointer((void **) &pBootNext);
					}
					//EIP-96246 Ends
					if(!gResetRequired)
					{
						if(!gDoNotBoot)
      				{
    						gApp->ClearScreen = TRUE;
                            //EIP 75736
    						StyleExit();
    						if (gST->ConOut != NULL)
                			{
                	            //Disable cursor, set desired attributes and clear screen
                	            gST->ConOut->EnableCursor( gST->ConOut, FALSE );
                	            gST->ConOut->SetAttribute( gST->ConOut, (EFI_BACKGROUND_BLACK | EFI_WHITE));
                	            gST->ConOut->ClearScreen( gST->ConOut);
                			}
						
    						BootLaunchBootNow( value, gShowAllBbsDev/*SETUP_SHOW_ALL_BBS_DEVICES*/ );
							StyleInit();
                	}
					}
					else
					{
						gApp->Quit = SaveAndReset();
					}
					status = TRUE;
					break;

				case GUID_KEY_AMI_CALLBACK:
					status = _SubMenuAmiCallback( value );
					break;

				case GUID_KEY_ERROR_MANAGER:
					{
					UefiSpecialGuidCallback(submenu->ControlData.ControlHandle, value, &guidInfo->GuidValue);
					}
					break;
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
		        case GUID_KEY_OEM_CONTROL:
					{
						OEMSpecialGotoSelect(value);
						break;
					}
#endif
                case GUID_KEY_IDE_SECURITY:
                    {
                        UINTN size;
                        IDE_SECURITY_CONFIG *ideSecConfig;


                        //Update mem copy of the IDE sec variable
                        size = 0;
                        ideSecConfig = VarGetVariable( VARIABLE_ID_IDE_SECURITY, &size );
						//EIP-75352 Suppress the warnings from static code analyzer
                        if (NULL == ideSecConfig) {
                            break;
                        }

                        TSEIDEUpdateConfig(ideSecConfig, value);

                        VarSetValue( VARIABLE_ID_IDE_SECURITY, 0, size, ideSecConfig );
                        MemFreePointer((VOID **)&ideSecConfig);
                    }
                break;
                case GUID_KEY_BBS_ORDER:
                {
                    BBSUpdateBootData(value);
                    VarSetValue(VARIABLE_ID_LEGACY_GROUP_INFO, 0, sizeof(UINT16), &(gCurrLegacyBootData->LegacyDevCount));
                }
                break;
                //EIP 57661 Start
				case GUID_KEY_DRIVER_HEALTH:
				{
					SetDrvHealthHandleAndCtrlCount (value);
					break;
				}
				case GUID_KEY_DRV_HEALTH_CTRL_COUNT:
				{
					DoDriverHealthOperation ((VOID *)&((CONTROL_DATA *)submenu)->ControlData, value);
					break;	
				}
                //EIP 57661 End
				default:
					break;
			}
		}
		else
		{
			EFI_STATUS Status = EFI_UNSUPPORTED;
			
			if ( guidInfo->GuidFlags.GuidLaunchGuid )
			{
				if(!gResetRequired)
				{
					if(!gDoNotBoot)
					{
   						gApp->ClearScreen = TRUE;
                        //EIP 75736
   						StyleExit();
   						if (gST->ConOut != NULL)
               			{
               	            //Disable cursor, set desired attributes and clear screen
               	            gST->ConOut->EnableCursor( gST->ConOut, FALSE );
               	            gST->ConOut->SetAttribute( gST->ConOut, (EFI_BACKGROUND_BLACK | EFI_WHITE));
               	            gST->ConOut->ClearScreen( gST->ConOut);
               			}
						StyleExitDone = TRUE;				
						Status = BootLaunchGuid( &guidInfo->GuidValue );
    					if ( ! EFI_ERROR( Status ) )
    					{
    						gApp->ClearScreen = TRUE;
							status = TRUE;
    					}
    					else
    						BootLaunchFailed = TRUE;
					}
				}
				else
				{
					gApp->Quit = SaveAndReset();
					status = TRUE;
				}
			}

			if (( guidInfo->GuidFlags.GuidLaunchFilename ) && (FALSE == status))
			{
				if(!gResetRequired)
				{
					if(!gDoNotBoot)
     				{
         				CHAR16 FileName[VARIABLE_NAME_LENGTH];
             			UINTN i = 0, j;
    					while(guidInfo->GuidName[i])
         				{
							j=0;
       						for(;guidInfo->GuidName[i];i++)
             				{
                 				if(L'|' == guidInfo->GuidName[i])
                     			{
                        			i++;
                           			break;
								}
        						FileName[j] = guidInfo->GuidName[i];
              					j++;
                   			}
  	                    	FileName[j] = 0;
							if(!StyleExitDone){		
       						gApp->ClearScreen = TRUE;
                            //EIP 75736
       						StyleExit();
       						if (gST->ConOut != NULL)
                   			{
                   	            //Disable cursor, set desired attributes and clear screen
               	                gST->ConOut->EnableCursor( gST->ConOut, FALSE );
               	                gST->ConOut->SetAttribute( gST->ConOut, (EFI_BACKGROUND_BLACK | EFI_WHITE));
               	                gST->ConOut->ClearScreen( gST->ConOut);
                   			}
		
							StyleExitDone = TRUE;
						}  					
						Status = BootLaunchFilename( FileName );
 	    				if ( ! EFI_ERROR( Status ) )
	        			{
	        				gApp->ClearScreen = TRUE;
							status = TRUE;
							BootLaunchFailed = FALSE;
							break;
      					}else
							BootLaunchFailed = TRUE;
     	 			}
    	     		//BootLaunchFailed = TRUE;
				}
			}
			else {
				gApp->Quit = SaveAndReset();
				status = TRUE;
			}
		}

		// EIP:47932 - Start 
		if(StyleExitDone)
		StyleInit();
		// EIP:47932 - End

// EIP:39412 - START
		if ( BootLaunchFailed ){
			
			//Restore the Original screen before boot launch 
			RestoreScreen( ScreenBuf );
			CallbackShowMessageBox( (UINTN)gBootLaunchFailedMsgBox, MSGBOX_TYPE_OK );
		}
		else {
			//In case Boot Launch not failed, free the saved screen buffer
			MemFreePointer((VOID **) &ScreenBuf);
		}
// EIP:39412 - END
		}
	}


	


	return status;

}

#ifdef TSE_FOR_APTIO_4_50
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitApplicationData
//
// Description:	 function to initialize the application data
//
// Input:		EFI_HANDLE ImageHandle
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS	InitApplicationData(EFI_HANDLE ImageHandle)
{
	EFI_STATUS	Status = EFI_SUCCESS;
#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION || TSE_FOR_64BIT
	VOID *pSection;
	UINTN SectionSize;
	EFI_GUID dataGuid = MINI_SETUP_DATA_GUID;

	Status=ReadImageResource(ImageHandle,&dataGuid,&pSection,&SectionSize);
	if ( EFI_ERROR( Status ) ) {
		return Status;
	}
	gApplicationData = (UINT8 *)pSection + sizeof(EFI_GUID);
#else
#ifdef USE_DEPRICATED_INTERFACE

	// Read in the data files from the GUIDed section
	Status = LoadGuidedDataDriverLib( gImageHandle, dataGuid, &gApplicationData );
	if ( EFI_ERROR( Status ) )
	{
		return Status;
	}
#else
#ifndef STANDALONE_APPLICATION
	gApplicationData = (UINT8 *)&_SetupPackage;
#else
	gApplicationData = (UINT8 *)&DummySetupData;
#endif	//#ifndef STANDALONE_APPLICATION
#endif	//#ifdef USE_DEPRICATED_INTERFACE
#endif	//#if APTIO_4_00 || SETUP_USE_GUIDED_SECTION || TSE_FOR_64BIT

	return Status;
}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadUserDefaultsSilently
//
// Description:	Function to load the user set defaults Silently
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadUserDefaultsSilently(VOID)
{
	NVRAM_VARIABLE *nvramVar, *tmpPtr;
	UINTN 			i = 0;
	UINT8 			*buffer;
	UINT16 			size;
	UINT32 			count;
//EIP-98918 Starts
   VARIABLE_INFO *varInfo = NULL;
	EFI_GUID sysAccessGuid = SYSTEM_ACCESS_GUID;
	
	VARIABLE_INFO *InnerLoopvarInfo = NULL;
	UINT32 			InnerLoop;
	BOOLEAN 			MatchFound = FALSE;
//EIP-98918 Ends
	nvramVar = &gVariableList [VARIABLE_ID_USER_DEFAULTS];
	if ( ( nvramVar->Size == 0 ) || ( nvramVar->Buffer == NULL ) )
		return;

	buffer = nvramVar->Buffer;
	count = *(UINT32 *)buffer;
	buffer += sizeof(UINT32);

	for ( i = 0; i < count; i++ )
	{
		varInfo = VarGetVariableInfoIndex (*(UINT32 *)buffer);//EIP-98918
		tmpPtr = &gVariableList[ *(UINT32 *)buffer ];

		if ( IsLoadSysteAccessOnUserDefault() ) //EIP-130529 Skip loading SYSTEM_ACCESS variable for user defaults	
		{
			if ( !EfiStrCmp(varInfo->VariableName, L"SystemAccess") &&  EfiCompareGuid(&sysAccessGuid, &(varInfo->VariableGuid)) )//EIP-UserDefault - Skip to load SystemAccess variable on pressing Restore User Defaults
			{
				buffer += sizeof(UINT32);
				size = *(UINT16 *)buffer;
				buffer += sizeof(UINT16);
				buffer += (sizeof (EFI_GUID) + sizeof (CHAR16) * VARIABLE_NAME_LENGTH); //Move to next variable
				buffer += size;
				continue;
			}
		}

		buffer += sizeof(UINT32);
		size = *(UINT16 *)buffer;
		buffer += sizeof(UINT16);

//EIP-98918 Starts
		if (
				(size == tmpPtr->Size) &&
				(!MemCmp (&varInfo->VariableGuid, buffer, sizeof (EFI_GUID) )) &&
				(!EfiStrCmp (varInfo->VariableName, (CHAR16 *)(buffer + sizeof (EFI_GUID)) ))
			)
		{
			buffer += (sizeof (EFI_GUID) + sizeof (CHAR16) * VARIABLE_NAME_LENGTH);
			MemCopy (tmpPtr->Buffer, buffer, size);
		}
		else					//If any variable deleted then order wont be same, so trying in all possible variable and loading the user defaults
		{
			MatchFound = FALSE;	
			for (InnerLoop = 0; InnerLoop < gVariables->VariableCount; InnerLoop ++)
			{
				InnerLoopvarInfo = VarGetVariableInfoIndex (InnerLoop);
				if ( NULL != InnerLoopvarInfo)
				{
					if (
						(size == InnerLoopvarInfo->VariableSize) && 
						(!MemCmp (&InnerLoopvarInfo->VariableGuid, buffer, sizeof(EFI_GUID))) && 
						(!EfiStrCmp (InnerLoopvarInfo->VariableName, (CHAR16 *)(buffer + sizeof (EFI_GUID)) ))
						)
					{
						buffer += (sizeof(EFI_GUID)+ sizeof(CHAR16) * VARIABLE_NAME_LENGTH);
						tmpPtr = &gVariableList [InnerLoop];
						MemCopy (tmpPtr->Buffer, buffer, size);
						MatchFound = TRUE;
						break;
					}
				}
			}
			if (FALSE == MatchFound)
			{
				SETUP_DEBUG_TSE ("\nERROR : Variable %s has been modified so skipping the USER default loading for this variable alone.", varInfo->VariableName );
				buffer += (sizeof(EFI_GUID)+ sizeof(CHAR16) * VARIABLE_NAME_LENGTH);
			}
		}
//EIP-98918 Ends
		buffer += size;
	}
	LoadedUserDefaultsHook();
	gResetRequired = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadUserDefaults
//
// Description:	Function to load the user set defaults
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadUserDefaults( VOID )
{

	if ( CallbackShowMessageBox( (UINTN)gLoadUserMsgBox, MSGBOX_TYPE_YESNO ) != MSGBOX_YES )
		return;

	LoadUserDefaultsSilently();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveUserDefaultsSilently
//
// Description:	Function to save the user set defaults Silently
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveUserDefaultsSilently(VOID)
{
	NVRAM_VARIABLE *nvramVar, *tmpPtr;
	UINT32 i,count;
	UINT8 *buffer;
   VARIABLE_INFO *varInfo = NULL;
	
	nvramVar = &gVariableList[ VARIABLE_ID_USER_DEFAULTS ];
	if ( ( nvramVar->Size != 0 ) || ( nvramVar->Buffer != NULL ) )
		MemFreePointer( (VOID **)&(nvramVar->Buffer) );

	nvramVar->Size = sizeof(UINT32);
    count = 0;
	for ( i = 0; i < gVariables->VariableCount; i++ ) {
            if ( (i == VARIABLE_ID_USER_DEFAULTS) ||
             (i == VARIABLE_ID_ERROR_MANAGER) ||
             (i == VARIABLE_ID_BOOT_ORDER) ||
			 (i == VARIABLE_ID_BBS_ORDER) ||
             (i == VARIABLE_ID_BOOT_MANAGER) ||
             (i == VARIABLE_ID_BOOT_NOW))
            continue;
		nvramVar->Size += sizeof(UINT32) + sizeof(UINT16) + sizeof (EFI_GUID) + (sizeof (CHAR16) * VARIABLE_NAME_LENGTH) + gVariableList[ i ].Size;
        count++;
    }

	buffer = EfiLibAllocateZeroPool( nvramVar->Size );
	if ( buffer == NULL )
		return;

	nvramVar->Buffer = buffer;

	*(UINT32 *)buffer = count;
	buffer += sizeof(UINT32);

	for ( i = 0, tmpPtr = gVariableList; i < gVariables->VariableCount; i++, tmpPtr++ )
    {
        if ( (i == VARIABLE_ID_USER_DEFAULTS) ||
             (i == VARIABLE_ID_ERROR_MANAGER) ||
             (i == VARIABLE_ID_BOOT_ORDER) ||
			 (i == VARIABLE_ID_BBS_ORDER) ||
             (i == VARIABLE_ID_BOOT_MANAGER) ||
             (i == VARIABLE_ID_BOOT_NOW))
            continue;
		*(UINT32 *)buffer = i;
		buffer += sizeof(UINT32);
		*(UINT16 *)buffer = (UINT16)tmpPtr->Size;
		buffer += sizeof(UINT16);

		varInfo = VarGetVariableInfoIndex (i);
		MemCopy (buffer, &varInfo->VariableGuid, sizeof (EFI_GUID));
		buffer += sizeof (EFI_GUID);
	
		EfiStrCpy ((CHAR16 *)buffer, varInfo->VariableName);
//		MemCopy( buffer, varInfo->VariableName, sizeof(CHAR16) * VARIABLE_NAME_LENGTH );
		buffer +=  sizeof(CHAR16) * VARIABLE_NAME_LENGTH;

		MemCopy( buffer, tmpPtr->Buffer, tmpPtr->Size );
		buffer += tmpPtr->Size;
	}

	VarSetNvram( VARIABLE_ID_USER_DEFAULTS, nvramVar->Buffer, nvramVar->Size );

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveUserDefaults
//
// Description:	Function to save the user specified defaults
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveUserDefaults( VOID )
{

	if ( CallbackShowMessageBox( (UINTN)gSaveUserMsgBox, MSGBOX_TYPE_YESNO ) != MSGBOX_YES )
		return;
		
	SaveUserDefaultsSilently();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetANSIEscapeCode
//
// Description:	 Return Size of Escape Code and gets the FG,BGColor.
//
// Input:		CHAR16 *String,
//				UINT8 *Bold,
//				UINT8 *Foreground, 
//				UINT8 *Background
//
// Output:		UINTN	- Escape code length (in CHAR16), 0 if not an escape code
//					Bold, Forground, Background - Filled with -1 if value not found in Escape Code
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN GetANSIEscapeCode(CHAR16 *String,UINT8 *Bold,UINT8 *Foreground, UINT8 *Background)
{
	CHAR16 *TempStr;
	UINTN i;
	BOOLEAN Bld=FALSE,Fg=FALSE;
	UINT8 Num=0xff;

	//Is ESC Code
	if((String[0]==L'\x1b')&&(String[1]==L'['))
	{	
		TempStr = &String[2];

		//  ESC [ x ; x x ; x x  m 	= Color esc code format
		//	  0 1 2 3 4 5 6 7 8  9 
		//	Check till Code m or Upto 10 char

		for(i=2;(*TempStr!=L'm')&&(i<10);i++,TempStr++)
		{
			if(*TempStr == L';')
			{
				if(!Bld)
				{	
					*Bold = Num; 
					Num = 0xFF; 
					Bld = TRUE;
				}
				else if(!Fg)
				{
					*Foreground = Num; 
					Num = 0xFF; 
					Fg = TRUE;
				}
			}	
			else
			{
				if(Num==0xFF)
					Num =(UINT8)(*TempStr-L'0');
				else
					Num = (Num*10)+(UINT8)(*TempStr-L'0');
			}
			if(TempStr[1]==L'm')
				*Background=Num;
		}
		if(*TempStr==L'm')
			return (TempStr-String);
	}

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SkipEscCode
//
// Description:	function to perform the esc key operation
//
// Input:	CHAR16 *string
//
// Output:	string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *SkipEscCode(CHAR16 *String)
{
	CHAR16 	  *TempString;
	UINTN	  i=0,j=0;

	//EIP-75351 Suppress the warnings from static code analyzer
	if (NULL == String) {
		return NULL;	
	}
	// Check For escape Code and remove that from the string
	TempString = StrDup(String);
	while(String[i])
	{
		if((String[i] == 0x001b) && (String[i+1] == L'[')) // ESC Code
		{	
			while(String[i] != L'm')i++;
			i++;
		}
		TempString[j] = String[i];
		i++; j++;
	}
	TempString[j]=0;	

	return TempString;
}
static UINT8 result = (UINT8)-1;
static CALLBACK_MESSAGEBOX  gCbMsgBox = { { CALLBACK_TYPE_MESSAGEBOX, sizeof(CALLBACK_MESSAGEBOX) }, 0 }; 

VOID _CallbackMsgboxEx( VOID *container, VOID *object, VOID *cookie )
{
	if ( (cookie != NULL) && ( ((CALLBACK_MESSAGEBOX*)cookie)->Header.Type == CALLBACK_TYPE_MESSAGEBOX) )
		result = (UINT8)(((CALLBACK_MESSAGEBOX*)cookie)->Result);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_CallbackGetValueEx
//
// Description:	Callback function to get the message box return value
//
// Input:	MSGBOX_DATA *msgbox
//
// Output:	Message box return value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _CallbackGetValueEx( MSGBOX_DATA *msgbox )
{
	ACTION_DATA *action = gMsgBoxAction;

	result = (UINT8)-1;
	gMsgBox.SetCallback( msgbox, NULL, _CallbackMsgboxEx, &gCbMsgBox );

	while ( result == (UINT8)-1 )
	{
		if ( action->Input.Type != ACTION_TYPE_NULL )
			gAction.ClearAction( action );

		gMsgBox.Draw( msgbox );

		if ( gAction.GetAction( action ) != EFI_SUCCESS )
			continue;

		gMsgBox.HandleAction( msgbox, action );
		DoRealFlushLines();
	}

	return result;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowPostMsgBoxEx
//
// Description:	Function to display the message box 
//
// Input:	CHAR16  *MsgBoxTitle,
//					CHAR16  *Message,
//					UINT8  MsgBoxType, 
//					UINT8 *pSelection
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowPostMsgBoxEx(
    IN CHAR16			*Title,
    IN CHAR16			*Message,
    IN CHAR16			*Legend,
    IN MSGBOX_EX_CATAGORY	MsgBoxExCatagory,
    IN UINT8	 		MsgBoxType,
    IN UINT16			*OptionPtrTokens,	
    IN UINT16	 		OptionCount,		
    IN AMI_POST_MGR_KEY		*HotKeyList, 		
    IN UINT16 			HotKeyListCount, 
    OUT UINT8			*MsgBoxSel,
    OUT AMI_POST_MGR_KEY	*OutKey
)
{
    static AMI_IFR_MSGBOX MsgBox = { 0, 0, 0, INVALID_HANDLE, 0 };
    EFI_STATUS Status = EFI_SUCCESS;
    UINT8 retValue = (UINT8)-1;
    MSGBOX_DATA *msgbox = NULL;
    CONTROL_INFO dummy;
    ACTION_DATA *action = gMsgBoxAction;	
    UINT16 i = 0;	

    if (NULL == gST->ConIn)
        return EFI_NOT_READY;

    if(Title == NULL || Message == NULL || 
	//Note: Messagebox should not require a legend 
	/*((Legend == NULL ) && (MsgBoxType == MSGBOX_TYPE_NULL)) ||*/
	    ((MsgBoxType == MSGBOX_TYPE_CUSTOM) && (OptionPtrTokens == NULL)) ||
        ((OptionCount > 0) && (OptionPtrTokens == NULL)) ||
        ((HotKeyListCount > 0) && (HotKeyList == NULL)))
        return EFI_INVALID_PARAMETER;
    
    if((MsgBoxType == MSGBOX_TYPE_CUSTOM) && (OptionCount > MSGBOX_MAX_OPTIONS))
    	return EFI_UNSUPPORTED ;	

    MsgBox.Title = HiiChangeString(gHiiHandle, MsgBox.Title, Title);
    MsgBox.Text = HiiChangeString(gHiiHandle, MsgBox.Text, Message);

    if(!gApp)
    {
        Status = gAction.Create( &gMsgBoxAction );
    	if ( EFI_ERROR( Status ) )
			return Status;
    	action = gMsgBoxAction;					//EIP127375, If NULL while initialization then this assignment will be helpful
    }


	Status = gMsgBox.Create( (void**)&msgbox ); 
	if ( EFI_ERROR( Status ) )
		return retValue;

	MemSet( &dummy, sizeof(dummy), 0 );
	dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;
	dummy.ControlPtr = (VOID*)&MsgBox ; //data;
	dummy.ControlFlags.ControlVisible = TRUE;

	msgbox->MsgBoxCatagory = (MsgBoxExCatagory & (~MSGBOX_EX_ATTRIB_CLEARSCREEN)) ;
	
	msgbox->Legend = StrDup (Legend);				//EIP-88918
	if (OptionCount)										//EIP 90379
	{
		msgbox->PtrTokens = EfiLibAllocateZeroPool (sizeof (UINT16) * OptionCount);
		if (NULL == msgbox->PtrTokens)
		{
			return EFI_OUT_OF_RESOURCES;
		}
		MemCopy (msgbox->PtrTokens, OptionPtrTokens, sizeof (UINT16) * OptionCount);
	}
	else
	{
		msgbox->PtrTokens = NULL;
	}
//	msgbox->PtrTokens = OptionPtrTokens;
	msgbox->OptionCount = OptionCount ;

	Status = gMsgBox.Initialize( msgbox, &dummy );
	if ( EFI_ERROR( Status ) )
		goto Done;

	gMsgBox.SetType( msgbox, MsgBoxType );
	
	//*MsgBoxSel = (UINT8)_CallbackGetValueEx( msgbox );

	result = (UINT8)-1;
	gMsgBox.SetCallback( msgbox, NULL, _CallbackMsgboxEx, &gCbMsgBox );

//EIP:47962 Start
	if((MsgBoxExCatagory & MSGBOX_EX_ATTRIB_CLEARSCREEN) == MSGBOX_EX_ATTRIB_CLEARSCREEN)
			ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );
//EIP:47962 End

	while ( result == (UINT8)-1 )
	{
		if ( action->Input.Type != ACTION_TYPE_NULL )
			gAction.ClearAction( action );

		gMsgBox.Draw( msgbox );

		if ( gAction.GetAction( action ) != EFI_SUCCESS )
			continue;

		gMsgBox.HandleAction( msgbox, action );
		DoRealFlushLines();
		
		if(HotKeyList!=NULL && HotKeyListCount>0)
		{
			for(i=0 ; i<HotKeyListCount; i++)
			{
				if( (HotKeyList[i].Key.ScanCode == action->Input.Data.AmiKey.Key.ScanCode ) &&
				    (HotKeyList[i].Key.UnicodeChar == action->Input.Data.AmiKey.Key.UnicodeChar) &&
				    (TseCheckShiftState( action->Input.Data.AmiKey, HotKeyList[i].KeyShiftState)  ) )
				{
					// Verify passed argument is not NULL before attempting to assign to it
					if(OutKey != NULL)
					{
						OutKey->Key.ScanCode = action->Input.Data.AmiKey.Key.ScanCode ; 
						OutKey->Key.UnicodeChar = action->Input.Data.AmiKey.Key.UnicodeChar; 
					
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
						OutKey->KeyShiftState = (UINT32)action->Input.Data.AmiKey.KeyState.KeyShiftState ;
#else
						OutKey->KeyShiftState = 0 ;
#endif
					}
					goto Done;
					
				}
		
			}
			
		}
		else
		{
			if((msgbox->MsgBoxType == MSGBOX_TYPE_NULL) && (action ->Input.Type == ACTION_TYPE_KEY))
				goto Done;

		}

	}

    if((result != -1) && (MsgBoxSel != NULL))
	*MsgBoxSel = (UINT8) result;


Done:
	gMsgBox.Destroy( msgbox, TRUE );


    if(!gApp)
    {
        gAction.Destroy( gMsgBoxAction, TRUE );
	gMsgBoxAction = NULL ;
    }
   

    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowPostProgress
//
// Description:	Function to display the progress bar 
//
// Input:	IN UINT8	ProgressBoxState - Progress bar state 
//    		IN CHAR16	*Title		 - Progress bar title 	
//    		IN CHAR16	*Message,	 - Progress bar message string
//    		IN CHAR16	*Legend,	 - Progress bar legend string
//    		IN UINTN 	Percent,	 - Percent Complete (0 - 100)
//    		IN OUT VOID	**Handle,	 - HANDLE. Valid Handle for update and close
//    		OUT AMI_POST_MGR_KEY	*OutKey  - Out Key
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowPostProgress(
    IN UINT8			ProgressBoxState, 
    IN CHAR16			*Title,
    IN CHAR16			*Message,
    IN CHAR16			*Legend,	
    IN UINTN 			Percent,	
    IN OUT VOID			**Handle,	
    OUT AMI_POST_MGR_KEY	*OutKey
)
{
    	static AMI_IFR_MSGBOX MsgBox = { 0, 0, 0, INVALID_HANDLE, 0 };
    	EFI_STATUS Status = EFI_SUCCESS;
    	MSGBOX_DATA *msgbox = NULL;
    	CONTROL_INFO dummy;
	ACTION_DATA *action=NULL;
	UINT16 MessageToken = 0 ;
	MEMO_DATA *memo = NULL;

	switch(ProgressBoxState)
        {
            case AMI_PROGRESS_BOX_INIT:

		Status = gMsgBox.Create( &msgbox );
		if ( EFI_ERROR( Status ) )
			return EFI_UNSUPPORTED;

	    	MsgBox.Title = HiiChangeString(gHiiHandle, STRING_TOKEN(STR_MSGBOX_PROGRESS_TITLE), Title);
    		MsgBox.Text = HiiChangeString(gHiiHandle, STRING_TOKEN(STR_MSGBOX_PROGRESS_TEXT), Message);

		MemSet( &dummy, sizeof(dummy), 0 );
		dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;
		dummy.ControlPtr = (VOID*)&MsgBox ; //data;
		dummy.ControlFlags.ControlVisible = TRUE;

		msgbox->MsgBoxCatagory = MSGBOX_EX_CATAGORY_NORMAL ;

		Status = gMsgBox.Initialize( msgbox, &dummy );

		if ( EFI_ERROR( Status ) )
		{
			gMsgBox.Destroy( msgbox, TRUE );
			return Status;
		}

		*Handle = msgbox ;
		msgbox->Legend = Legend ;
		msgbox->Percent = 0 ;
		gMsgBox.SetType( msgbox, MSGBOX_TYPE_PROGRESS );
		
		gMsgBox.Draw( msgbox );
		DoRealFlushLines();
		
            	break;

            case AMI_PROGRESS_BOX_UPDATE:

		if(Handle == NULL)
			return EFI_UNSUPPORTED;
		
		msgbox = *Handle ;
	        msgbox->Percent = Percent ;

//EIP:39416	START 
		if(Message != NULL)
		{
		     memo = msgbox->Memo;
		     MessageToken = HiiChangeString(gHiiHandle, MessageToken, Message);
		     UefiSetSubTitleField((VOID *)memo->ControlData.ControlPtr, MessageToken);
		}
//EIP:39416	END

		gMsgBox.Draw( msgbox );	
		DoRealFlushLines();
		
		//Output the key
		if (! EFI_ERROR( gAction.Create( &action ) ) )
		{
                if(!EFI_ERROR(gAction.GetAction( action )))
                {
                    OutKey->Key.ScanCode = action->Input.Data.AmiKey.Key.ScanCode ;
                    OutKey->Key.UnicodeChar = action->Input.Data.AmiKey.Key.UnicodeChar;

                #if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
                    OutKey->KeyShiftState = action->Input.Data.AmiKey.KeyState.KeyShiftState ;
                #else
                    OutKey->KeyShiftState = 0 ;
                #endif
                }
                Status = gAction.Destroy(action, TRUE);
            }
              	break;

            case AMI_PROGRESS_BOX_CLOSE:
            	msgbox = *Handle ;
		gMsgBox.Destroy( msgbox, TRUE );
		//restore the screen
    	       	break;
        }

    	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowPostMsgBox
//
// Description:	Function to display the message box 
//
// Input:	CHAR16  *MsgBoxTitle,
//					CHAR16  *Message,
//					UINT8  MsgBoxType, 
//					UINT8 *pSelection
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowPostMsgBox(IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8  MsgBoxType, UINT8 *pSelection)
{
    static AMI_IFR_MSGBOX MsgBox = { 0, 0, 0, INVALID_HANDLE, 0 };
    EFI_STATUS Status = EFI_SUCCESS;
	UINT8 Selection;

    MsgBox.Title = HiiChangeString(gHiiHandle, MsgBox.Title, MsgBoxTitle);
    MsgBox.Text = HiiChangeString(gHiiHandle, MsgBox.Text, Message);

  	if(!gApp)
    {
        Status = gAction.Create( &gMsgBoxAction );
    	if ( EFI_ERROR( Status ) )
			return Status;
    }

    Selection = CallbackShowMessageBox((UINTN)&MsgBox, MsgBoxType);

  	if(!gApp)
    {
        gAction.Destroy( gMsgBoxAction, TRUE );
		gMsgBoxAction = NULL;
    }
    
    if(pSelection!=NULL)
	    *pSelection = Selection;

	return Status;
}

#define     PADDING     8
#define     GUTTER      2
#define     BRACKET     1
UINT16 gPostLabelMargin = 0 ;
extern EFI_STATUS _CBPopupStringEdit(VOID *container, VOID *object, VOID *cookie);
extern UINT8 res ;
extern CALLBACK_VARIABLE  gPopupEditCb ;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PostEditCallback
//
// Description:	Callback function for text entry popup
//
// Input:	VOID *container, VOID *object, VOID *cookie
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _PostEditCallback(VOID *container, VOID *object, VOID *cookie)
{
	EFI_STATUS Status = EFI_SUCCESS;
  
/*  
	if(cookie!=NULL)
	{
       res=0;
	}
	else
 	   res=1;
*/    
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PostEditDraw
//
// Description:	Function to draw text entry edit box
//
// Input:	POPUPEDIT_DATA *popup
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _PostEditDraw( POPUPEDIT_DATA *popup )
{
	UINT16 Length = 0 ;
    BOOLEAN bShadow = StyleGetShadowSupport() ;
     
	//DrawWindow( popup->Left, popup->Top, popup->Width, popup->Height, (UINT8)(popup->BGColor | popup->FGColor) , FALSE, FALSE );

	if ( popup->Title != NULL )
    {
        Length = (UINT16)TestPrintLength( popup->Title ) / (NG_SIZE);
        DrawStringWithAttribute( popup->Left - Length - GUTTER, popup->Top, popup->Title, (popup->ControlActive?EFI_WHITE:popup->FGColor) | popup->BGColor );
    }
		
    Length = (UINT16)UefiGetMaxValue(popup->ControlData.ControlPtr);
    DrawStringWithAttribute( popup->Left, popup->Top, L"[", (popup->ControlActive?EFI_WHITE:popup->FGColor) | popup->BGColor );
    DrawStringWithAttribute( popup->Left+Length+1   , popup->Top, L"]", (popup->ControlActive?EFI_WHITE:popup->FGColor) | popup->BGColor );
    if(popup->ControlActive)
        DrawWindow( popup->Left+1, popup->Top, Length, popup->Height, (UINT8)(EFI_BLACK | popup->FGColor) , FALSE, FALSE );

	return gControl.Draw( popup );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PostPopupEditDraw
//
// Description:	Function to draw text entry popup window
//
// Input:	POPUPEDIT_DATA *PopupEdit
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _PostPopupEditDraw( POPUPEDIT_DATA *PopupEdit )
{
	EFI_STATUS Status;
	CHAR16 *text = NULL, *newText = NULL;
	CHAR16 *line;
	UINT16 pos, height,i,ii=0;;

	
	text = StrDup(PopupEdit->Text);

	Status = _PostEditDraw( PopupEdit );
	if(EFI_ERROR(Status))
		return Status;

	// clear out old wrapped string
	for ( pos = ii; pos < PopupEdit->Height-2; pos++ )
		DrawStringWithAttribute( PopupEdit->Left+1, PopupEdit->Top + pos, PopupEdit->EmptyString, PopupEdit->FGColor | PopupEdit->BGColor );

	newText = StringWrapText( text, PopupEdit->Width-1, &height );
	if ( newText != text )
		MemFreePointer( (VOID **)&text );

	line = newText;

	for ( pos = ii; pos < PopupEdit->Height; pos++ )
	{
		CHAR16 save;

		text = line;
		if ( *line == L'\0' )
			break;

		while ( ( *line != L'\n' ) &&( *line != L'\r' ) && ( *line != L'\0' ) )
			line++;

		save = *line;
		*line = L'\0';
		i=0;
		while( (text[i] != L'\0') && (PopupEdit->Chr !=0x0 ) )
		{		
//			if(text[i] != L' ') //all chars should be treated the same
				text[i] = PopupEdit->Chr;
			i++;
		}

		if(PopupEdit->ControlActive)
			DrawStringWithAttribute( PopupEdit->Left+1, PopupEdit->Top + pos, text, EFI_WHITE | EFI_BLACK );
		else
			DrawStringWithAttribute( PopupEdit->Left+1, PopupEdit->Top + pos, text, PopupEdit->FGColor | PopupEdit->BGColor );

		if ( ( *line = save ) != L'\0' )
		{
			line++;
			if ( ( *line == L'\r' ) || ( *line == L'\n' ) )
				line++;
		}
	}
	MemFreePointer( (VOID **)&newText );

	if ( pos < height )
		height = pos;

	PopupEdit->DisplayLines = height;
	FlushLines( 0, 24  );
	//FlushLines( PopupEdit->Top, PopupEdit->Top + PopupEdit->Height  );
	return  EFI_SUCCESS;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_PostPopupEditGetValues
//
// Description:	Function to draw text entry popup window
//
// Input:	POPUP_DATA          *popup, 
//          POPUPEDIT_DATA      *editList, 
//          TEXT_INPUT_TEMPLATE *InputData,
//          UINT16              ItemCount, 
//          DISPLAY_TEXT_KEY_VALIDATE ValidateKeyFunc
//
// Output:	UINTN  - 0/1 (success/abort)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _PostPopupEditGetValues(
    POPUP_DATA          *popup, 
    POPUPEDIT_DATA      *editList, 
    TEXT_INPUT_TEMPLATE *InputData,
    UINT16              ItemCount, 
    DISPLAY_TEXT_KEY_VALIDATE ValidateKeyFunc
)
{
	EFI_STATUS Status;
    POPUPEDIT_DATA *ptrEdit=NULL; 
    CONTROL_ACTION Action = ControlActionUnknown;
    ACTION_DATA *action=NULL ;
    UINT16 i=0, Length=0, CurPos=0;
    UINT16 count = 0;
    res = (UINT8)-1;
    

    if(!gApp)
    {
        Status = gAction.Create( &action );
    	if ( EFI_ERROR( Status ) )
        {
		    res=0;
            goto Done;
        }
    } else {
        action = gApp->Action;
    }

          
    gPopup.Draw( popup );

    //1. Position Child items
    for ( i = 0; i < ItemCount; i++)
	{
        Length = (UINT16)TestPrintLength( editList[i].Title ) / (NG_SIZE);  
        editList[i].Top = popup->Top+1+i ;
        editList[i].Left = popup->Left + gPostLabelMargin ;
        editList[i].Height = 1 ;  
    }		
    
    

    res = (UINT8)-1;

    while ( res == (UINT8)-1 )
	{
		//2. Clear the action
        if ( action->Input.Type != ACTION_TYPE_NULL ) { 
			gAction.ClearAction( action );
        }
		
        //3. Draw the controls
        gPopup.Draw( popup );

        ptrEdit = editList;

        for ( i = 0; i < ItemCount; i++, ptrEdit++)
	    {
            _PostPopupEditDraw( ptrEdit );
        }	

        FlushLines( popup->Top-2, popup->Top + popup->Height  );
        DoRealFlushLines();

        //4. Get the action
        Status = gAction.GetAction( action );
        if( Status != EFI_SUCCESS ) {
			continue;
        }

        //5. Set the count to control the active item
        if (action->Input.Type == ACTION_TYPE_KEY)
        {
            Action = MapControlKeysHook(action->Input.Data.AmiKey) ;
       
            switch(Action)
            {
                case ControlActionHome:
                    count = 0;
                    break;
                
                case ControlActionEnd:
                    count = ItemCount-1;
                    break;

                case ControlActionNextUp:
                    if (count > 0 ) 
                        count--;
                    break;

	            case ControlActionNextSelection:    
                case ControlActionNextDown:
                    if (count < ItemCount-1 ) 
                        count++;
                    break;
              /*       
                case ControlActionSelect:
                    count++;
                    if(count >= ItemCount)
                        res=0;
                    break;
              */          
                case ControlActionAbort:
                    res=1;
                    break;
            }
        }

        ptrEdit = editList;

        //6. Scan Items, Set Active Status and handle the action
        for ( i = 0; i < ItemCount; i++, ptrEdit++)
	    {
            if(count == i)
		    {		
                //Handle the action ONLY for the active item 
                ptrEdit->ControlActive = TRUE ;
              
                //Check filter key, skip the character/Action if required
                if( (action->Input.Data.AmiKey.Key.UnicodeChar) && 
                    (Action != ControlActionBackSpace)          &&
                    (Action != ControlActionAbort)              &&
                    //(Action != ControlActionSelect)           &&
                    (Action != ControlActionNextSelection)      &&  
                    (Action != ControlActionUnknown)            
                   /* (action->Input.Data.AmiKey.Key.UnicodeChar  != 0x20 )*/   )
	            {
                    
                    if(InputData[i].FilterKey == TSE_FILTER_KEY_NUMERIC)
                    { 
                        if(!CharIsNumeric(action->Input.Data.AmiKey.Key.UnicodeChar))
                            continue ;
                    }
                    else if(InputData[i].FilterKey == TSE_FILTER_KEY_ALPHA)
                    {
                         if(!CharIsAlpha(action->Input.Data.AmiKey.Key.UnicodeChar))
                            continue ;
                    }
                    else if(InputData[i].FilterKey == TSE_FILTER_KEY_ALPHANUMERIC)
                    {
                         if(!CharIsAlphaNumeric(action->Input.Data.AmiKey.Key.UnicodeChar))
                            continue ;
                    }
                    else if((InputData[i].FilterKey == TSE_FILTER_KEY_CUSTOM) && (ValidateKeyFunc!=NULL))
                    {
                         if(!(ValidateKeyFunc(i, action->Input.Data.AmiKey.Key.UnicodeChar, ptrEdit->Text)))
                            continue ;
                    }
                }
                
                gPopupEdit.HandleAction( ptrEdit, action );
                CurPos = (UINT16)EfiStrLen(ptrEdit->Text)+1 ;
                gST->ConOut->SetAttribute ( gST->ConOut, ptrEdit->FGColor | ptrEdit->BGColor );
                gST->ConOut->SetCursorPosition( gST->ConOut,
                    ptrEdit->Left + CurPos, ptrEdit->Top );
                
                if(CurPos <= ptrEdit->TextWidth)
                {
                    gST->ConOut->EnableCursor(gST->ConOut, TRUE);
                }
                else
                {
                    gST->ConOut->EnableCursor(gST->ConOut, FALSE);
                }
                
                                
		    }
            else
            {
                ptrEdit->ControlActive = FALSE ;
            }

        }

        if(Action == ControlActionSelect)
        {
            count++;
            
            if(count >= ItemCount)
            {
                res=0;
            }
        }

        Action = ControlActionUnknown ;
        
    }

Done:
    if(!gApp)
    {
        gAction.Destroy( action, TRUE );
	    action = NULL ;
    }
    
 
	return res;
}
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     ShowPostTextBox
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
EFI_STATUS ShowPostTextBox(
    IN VOID	    *HiiHandle, 	
    IN UINT16 	TitleToken, 
    IN TEXT_INPUT_TEMPLATE *InputData,
    IN UINT16 	ItemCount,
    IN DISPLAY_TEXT_KEY_VALIDATE FilterKeyFunc)
{
    
    EFI_STATUS Status = EFI_SUCCESS;
    UINT16 Token=0, i=0, Length=0, MaxLabelWidth=0, MaxControlWidth=0; 
    UINT8 retValue = (UINT8)-1;
    VOID *OriginalPopupEditDraw = NULL ;
    CHAR16 *Text=NULL;
    VOID *IFRString ;
    CONTROL_INFO dummy;
   
    POPUP_DATA *popup = NULL ;
    POPUPEDIT_DATA *PopupEditList=NULL, *ptrEdit=NULL; 
    CALLBACK_VARIABLE *PopupEditCb=NULL, *ptrCb=NULL ;
    CONTROL_INFO *dummys=NULL, *ptrDummy=NULL;
    EFI_TPL OrgTPL;
    BOOLEAN PreviousCursorState = gST->ConOut->Mode->CursorVisible;

    if(HiiHandle == NULL)
    {
        return EFI_UNSUPPORTED ;
    } 

    Status = gPopup.Create( &popup );
	if ( EFI_ERROR( Status ) )
    {
		return Status;
    }

    // this *MUST* be run a EFI_TPL_APPLICATION
    OrgTPL = gBS->RaiseTPL( EFI_TPL_HIGH_LEVEL );               // guarantees that RestoreTPL won't ASSERT
    gBS->RestoreTPL( EFI_TPL_APPLICATION );

    PopupEditList = EfiLibAllocateZeroPool( sizeof(POPUPEDIT_DATA) * ItemCount);
    PopupEditCb = EfiLibAllocateZeroPool( sizeof(CALLBACK_VARIABLE) * ItemCount);
    dummys = EfiLibAllocateZeroPool( sizeof(CONTROL_INFO) * ItemCount);

    ptrEdit = PopupEditList;
    ptrDummy = dummys ;
    ptrCb = PopupEditCb ;  

    IFRString = UefiCreateSubTitleTemplate(TitleToken);
    //((EFI_IFR_STRING*)IFRString)->MaxSize = 10 ;
    
    MemSet( &dummy, sizeof(dummy), 0 );
    dummy.ControlPtr = (VOID*)IFRString;
	dummy.ControlHandle = HiiHandle;
	dummy.ControlType = CONTROL_TYPE_POPUP_STRING;
    dummy.ControlFlags.ControlVisible = TRUE;
    

    Status = gPopup.Initialize( popup, &dummy );
	if ( EFI_ERROR( Status ) )
		goto Done;

    SetControlColorsHook( NULL, NULL , NULL, NULL , NULL, NULL ,
	                      NULL , NULL,  NULL,NULL ,
						  NULL,NULL ,NULL,&(popup->FGColor),&(popup->BGColor)  );

    popup->Border  = TRUE ;
    popup->Title = HiiGetString(HiiHandle, TitleToken); 
    popup->Style  = POPUP_STYLE_BBS ;

    if ( popup->Title == NULL )
    {
		Status = EFI_UNSUPPORTED ;
        goto Done;
    }
    

    for ( i = 0; i < ItemCount; i++, ptrEdit++, ptrDummy++, ptrCb++)
	{
	    
        if((InputData[i].Value == NULL) || (InputData[i].MaxSize < 1 )) 
        {
            Status = EFI_INVALID_PARAMETER;
            goto Done;
        }

        // Create PopupEdit Control
        Status = gPopupEdit.Create( &((POPUPEDIT_DATA *)ptrEdit) );
	    if ( EFI_ERROR( Status ) )
		    goto Done;

        MemSet( ptrDummy, sizeof(CONTROL_INFO), 0 );
        ptrDummy->ControlPtr = (VOID*)UefiCreateStringTemplate(InputData[i].ItemToken);
	    ptrDummy->ControlHandle = HiiHandle;
	    ptrDummy->ControlType = CONTROL_TYPE_POPUP_STRING;
        ptrDummy->ControlFlags.ControlVisible = TRUE;
        ((EFI_IFR_STRING*)ptrDummy->ControlPtr)->MaxSize = InputData[i].MaxSize ;

		//Set the text, caller may want to display default value 
		gPopupEdit.SetText(ptrEdit, InputData[i].Value);
        gPopupEdit.SetType( ptrEdit, InputData[i].Hidden?POPUPEDIT_TYPE_PASSWORD:POPUPEDIT_TYPE_STRING );

        // Initialize PopupEdit Control
        Status = gPopupEdit.Initialize( ptrEdit, ptrDummy ) ;
        
	    if ( EFI_ERROR( Status ) )
		    goto Done;		

        ptrEdit->Border  = FALSE ;
	    ptrEdit->Style  = POPUP_STYLE_NORMAL ;    
        
        gPopupEdit.SetCallback( ptrEdit, NULL, _PostEditCallback, ptrCb );
        
        // Item width = PromptStringLength + "[" + ControlWidth +"]"

        //Get maximum label width
        Length = (UINT16)TestPrintLength( ptrEdit->Title ) / (NG_SIZE);
        if(Length > MaxLabelWidth)
            MaxLabelWidth = Length ; 

        
        //Get maximum control width
        Length = (UINT16)UefiGetMaxValue(ptrEdit->ControlData.ControlPtr); 
        if(Length > MaxControlWidth)
            MaxControlWidth = Length ; 
	}
    
    //popup->width = MaxLabelWidth + GUTTER + "["   + MaxControlWidth + "]"
    popup->Width = MaxLabelWidth + GUTTER + BRACKET + MaxControlWidth + BRACKET ;
    popup->Width += PADDING ;    

    Length = (UINT16)TestPrintLength( popup->Title ) / (NG_SIZE);  
    
    //Check if the title exceeds the popup window width
    if(Length > popup->Width)
    {
        //Adjust the popup window width
        popup->Width = Length + PADDING ; 
        //Set the label margin 
        gPostLabelMargin = (popup->Width - (MaxLabelWidth + GUTTER + MaxControlWidth))/2 + MaxLabelWidth  ;
    }
    else
    {
        //Set the label margin 
        gPostLabelMargin = MaxLabelWidth + GUTTER + PADDING/2; 
    }
  
    //Set the popup window height
    popup->Height = ItemCount + 2	;

    //Check screen overflow
    if( (popup->Width > gMaxCols - 2)   ||
        (popup->Height > gMaxRows - 2)   )
    {
        Status = EFI_UNSUPPORTED;
        goto Done;	   
    }

   	// Save gPopupEdit.Draw (It may be an override function)
    OriginalPopupEditDraw = gPopupEdit.Draw ;

    // Override gPopupEdit.Draw with our functiion (It will be called by the PopupEdit control)
  	gPopupEdit.Draw	= _PostPopupEditDraw ;

    gST->ConOut->EnableCursor(gST->ConOut, TRUE);
    gST->ConOut->SetAttribute ( gST->ConOut, popup->FGColor | popup->BGColor );

    // Launch the textbox and get the values. 
    retValue = (UINT8)_PostPopupEditGetValues( popup, PopupEditList, InputData, ItemCount, FilterKeyFunc );

    gST->ConOut->EnableCursor(gST->ConOut, PreviousCursorState);

    // Restore gPopupEdit.Draw to the original
   	gPopupEdit.Draw	= OriginalPopupEditDraw ;


    if(retValue == 0)
	{
		for ( i = 0; i < ItemCount; i++)
	    {
            if(InputData[i].Value == NULL)
            {
                // Allocate space for the user entered value
                //EntryData[i].Value = EfiLibAllocateZeroPool( (PopupEditCb[i].Length+1) * sizeof(CHAR16) );
                
                //if(EntryData[i].Value == NULL)
                Status = EFI_INVALID_PARAMETER;
                goto Done;	
		    }
            // Get the user entered value
            EfiStrCpy( InputData[i].Value, PopupEditList[i].Text );
            //EfiStrCpy( InputData[i].Value, PopupEditCb[i].Data );	
        }		
	}

Done:
    
   gPopupEdit.Destroy( PopupEditList, TRUE );//EIP-170151 Destroy text box before message box
     
    // Free allocated init data
  	
  	MemFreePointer((VOID**)&PopupEditCb);
   MemFreePointer((VOID**)&dummys);
	gPopup.Destroy( popup, TRUE );

    if (gApp != NULL) {
        gApp->CompleteRedraw = TRUE ; //CompleteRedraw;
        gApp->OnRedraw = SUBMENU_COMPLETE_REDRAW;
    }

    gBS->RaiseTPL( EFI_TPL_HIGH_LEVEL ); // guarantees that RestoreTPL won't ASSERT
    gBS->RestoreTPL( OrgTPL );

    if (res == 1) {
        Status = EFI_ABORTED;
    }

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DisplayInfoCancelTimer
//
// Description:	Timer notify fucntion
//
// Input:		EFI_EVENT Event
//				VOID *Context
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _DisplayInfoCancelTimer( EFI_EVENT Event, VOID *Context )
{
	if ( gInfoBox != NULL )
		gMsgBox.Destroy( gInfoBox, TRUE );
	
	gInfoBox = NULL;

	TimerStopTimer( &Event );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowInfoBox
//
// Description:	fucntiont to display the information box
//
// Input:		CHAR16  *InfoBoxTitle, 
//				CHAR16  *Message, 
//				UINTN   TimeLimit, 
//				EFI_EVENT  *RetEvent)
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowInfoBox(IN CHAR16  *InfoBoxTitle, IN CHAR16  *Message, IN UINTN   TimeLimit, EFI_EVENT  *RetEvent)
{
    EFI_STATUS Status;
	static AMI_IFR_MSGBOX msgbox = { 0, 0, 0, INVALID_HANDLE, 0 };
	CONTROL_INFO dummy;

    msgbox.Title = HiiChangeString(gHiiHandle, msgbox.Title, InfoBoxTitle);
    msgbox.Text = HiiChangeString(gHiiHandle, msgbox.Text, Message);

	Status = gMsgBox.Create( &gInfoBox );
	if ( EFI_ERROR( Status ) )
		return 1;

	MemSet( &dummy, sizeof(dummy), 0 );

	dummy.ControlHandle = INVALID_HANDLE;
	dummy.ControlPtr = (VOID*)(UINTN) &msgbox;
	dummy.ControlFlags.ControlVisible = TRUE;

	gMsgBox.Initialize( gInfoBox, &dummy );

	gMsgBox.SetType( gInfoBox, MSGBOX_TYPE_NULL );
	gMsgBox.Draw( gInfoBox );

	if ( TimeLimit != 0 )
	{
		UINT32 EventType = EFI_EVENT_TIMER | EFI_EVENT_NOTIFY_SIGNAL;		//|EFI_EVENT_NOTIFY_WAIT, EFI_EVENT_NOTIFY_SIGNAL|

		Status = gBS->CreateEvent(
									EventType,
									EFI_TPL_CALLBACK,
									_DisplayInfoCancelTimer,
									NULL,
									RetEvent
					 			 );	

		if ( EFI_ERROR( Status ) )
			return Status;

		Status = gBS->SetTimer( *RetEvent, TimerRelative, MultU64x32((UINT64)TIMER_ONE_SECOND, TimeLimit) );
	
		if ( EFI_ERROR( Status ) )
			TimerStopTimer( RetEvent );
	}

	return Status;
}

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActionReadKeyWithAMIKeyCode
//
// Description:	fucntion to read the a key using AMI Key Code Protocol
//
// Input:		AMI_EFI_KEY_DATA *pAmiKey, 
//				UINT64 Timeout
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActionReadKeyWithAMIKeyCode( AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout )
{
	EFI_STATUS Status;
	EFI_STATUS StatusFlush;
	EFI_EVENT EventList[2] = { NULL, NULL };
	UINTN Count = 1, Index = 1;
    AMI_EFI_KEY_DATA    KeyFlush;

    AMI_EFIKEYCODE_PROTOCOL *pKeyCodeProtocol;
    Status = gBS->HandleProtocol(gST->ConsoleInHandle, &gAmiEfiKeycodeProtocolGuid, (void*)&pKeyCodeProtocol);
        if (EFI_ERROR(Status)) return Status;

	if ( Timeout )
	{
		EventList[0] = pKeyCodeProtocol->WaitForKeyEx;

		Status = TimerCreateTimer( &EventList[1], NULL, NULL, TimerRelative, Timeout, EFI_TPL_CALLBACK );
		if ( EFI_ERROR( Status ) )
			return Status;

		Count++;

		gBS->WaitForEvent( Count, EventList, &Index );
	
		TimerStopTimer( &EventList[1] );

		if ( Index == 1 )
			return EFI_NOT_READY;
	}

    Status = pKeyCodeProtocol->ReadEfikey( pKeyCodeProtocol, pAmiKey );
    ////EIP-87117  If it Partial Key make the Status as Error to ignore 
    // the Partial Key.
    if((pAmiKey->KeyState.KeyToggleState & KEY_STATE_EXPOSED) ==  KEY_STATE_EXPOSED) {
        if( (!EFI_ERROR( Status )) && (pAmiKey->Key.ScanCode==0) && (pAmiKey->Key.UnicodeChar==0)) {
            Status = EFI_NOT_READY;
        }
    }

	if ( ! EFI_ERROR( Status ) && FlushKeysAfterRead())//EIP 99022 :check for the FLUSH_KEYS_AFTER_READ token before flushing the keys
	{
		do
		{
        	StatusFlush = pKeyCodeProtocol->ReadEfikey( pKeyCodeProtocol, &KeyFlush );
            ////EIP-87117  If it Partial Key make the Status as Error to ignore 
            // the Partial Key.
            if((KeyFlush.KeyState.KeyToggleState & KEY_STATE_EXPOSED) ==  KEY_STATE_EXPOSED) {
                if( (!EFI_ERROR( Status )) && (KeyFlush.Key.ScanCode==0) && (KeyFlush.Key.UnicodeChar==0)) {
                    StatusFlush = EFI_NOT_READY;
                }
            }
		} while ( ! EFI_ERROR( StatusFlush ) );

	}

	return Status;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ActionReadKey
//
// Description:	fucntion to handle the read key action
//
// Input:		AMI_EFI_KEY_DATA *pAmiKey, 
//				UINT64 Timeout
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ActionReadKey( AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout )
{
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
	return ActionReadKeyWithAMIKeyCode( pAmiKey, Timeout );
#else
	return _ActionReadKey( pAmiKey, Timeout );
#endif

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AMIReadKeyStroke
//
// Description:	function to read a key stroke
//
// Input:		EFI_INPUT_KEY *Key,
//				AMI_EFI_KEY_DATA *KeyData
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AMIReadKeyStroke(EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData)
{
	EFI_STATUS Status;
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
    AMI_EFIKEYCODE_PROTOCOL *pKeyCodeProtocol;

  	Status = gBS->HandleProtocol(gST->ConsoleInHandle, &gAmiEfiKeycodeProtocolGuid, (void*)&pKeyCodeProtocol);
   	if (EFI_ERROR(Status)) return Status;

	Status = pKeyCodeProtocol->ReadEfikey( pKeyCodeProtocol, KeyData );

    ////EIP-87117  If it Partial Key make the Status as Error to ignore 
    // the Partial Key.
    if((KeyData->KeyState.KeyToggleState & KEY_STATE_EXPOSED) ==  KEY_STATE_EXPOSED) {
        if( (!EFI_ERROR( Status )) && (KeyData->Key.ScanCode==0) && (KeyData->Key.UnicodeChar==0)) {
            Status = EFI_NOT_READY;
        } 
    }
    *Key = KeyData->Key;
#else
    Status = gST->ConIn->ReadKeyStroke( gST->ConIn, Key );
#endif
	return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HelperIsPasswordCharValid
//
// Description:	function to check whether the password char is valid
//
// Input:		EFI_INPUT_KEY *Key,
//				AMI_EFI_KEY_DATA *KeyData,
//				UINTN StrIndex,
//				UINTN PasswordLength, 
//				CHAR16 *OutChar
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HelperIsPasswordCharValid(EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData,UINTN StrIndex,UINTN PasswordLength, CHAR16 *OutChar)
{
#if (TSE_USE_AMI_EFI_KEYCODE_PROTOCOL )
	switch( SETUP_STORE_KEYCODE_PASSWORD )
	{
		case PW_EFI_KEY:
			if ( (StrIndex < PasswordLength) && (KeyData->EfiKeyIsValid) ) {
				/// EIP:28551 - Get EFI Key with the help of AMI key code protocol
				*OutChar = (0x8000)^(CHAR16)(KeyData->EfiKey);
				return EFI_SUCCESS;
			}
		break;
		case PW_SCAN_CODE:
			if ( (StrIndex < PasswordLength) && (KeyData->PS2ScanCodeIsValid) ) {
				*OutChar = (CHAR16)(KeyData->PS2ScanCode);
				return EFI_SUCCESS;
			}
		break;
		default:
			break;
	}

#endif
	// if tokens not enabled then, check whether the character is alphanumeric and return the key
	if ( CheckIsAllowedPasswordChar(Key->UnicodeChar) && ( StrIndex < PasswordLength ) )
	{
		*OutChar = Key->UnicodeChar;
		return EFI_SUCCESS;
	}

	// If AMI key code support TOKEN not enabled and the character is not alphanumeric then return as Unsupported.
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PopupEditHandlePassword
//
// Description:	function to handle the popup password edit
//
// Input:		VOID *pPopupEdit, 
//				VOID *pData
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PopupEditHandlePassword( VOID *pPopupEdit, VOID *pData)
{
#if (TSE_USE_AMI_EFI_KEYCODE_PROTOCOL && SETUP_STORE_KEYCODE_PASSWORD)
	POPUPEDIT_DATA *PopupEdit = pPopupEdit;
	ACTION_DATA *Data = pData;

	// Check whether the popup edit type is Password, 
    if(( PopupEdit->PopupEditType == POPUPEDIT_TYPE_PASSWORD )&&( EfiStrLen(PopupEdit->Text) < PopupEdit->TextWidth ))
    {
        if(PopupEdit->ControlActive ==FALSE)
		{
			// copy the password text into temp and make the control active.
            MemCopy(PopupEdit->TempText,PopupEdit->Text,PopupEdit->TextWidth* sizeof(UINT16));
			PopupEdit->ControlActive = TRUE; 
		}
		switch( SETUP_STORE_KEYCODE_PASSWORD )
		{
			case PW_EFI_KEY:
				if(Data->Input.Data.AmiKey.EfiKeyIsValid)
					PopupEdit->Text[EfiStrLen(PopupEdit->Text)] = 0x8000 ^(CHAR16)(Data->Input.Data.AmiKey.EfiKey); 			
				else
					return EFI_UNSUPPORTED;
			break;
	
			case PW_SCAN_CODE:
				if(Data->Input.Data.AmiKey.PS2ScanCodeIsValid)
					PopupEdit->Text[EfiStrLen(PopupEdit->Text)] = (CHAR16)(Data->Input.Data.AmiKey.PS2ScanCode);
				else
					return EFI_UNSUPPORTED;
			break;
		}
		// set end of string and return success
        PopupEdit->Text[EfiStrLen(PopupEdit->Text)] = 0x0 ; 

		return EFI_SUCCESS;
    }
#endif
    	return EFI_UNSUPPORTED;
}

//TSE_CLEAR_USERPW_WITH_ADMINPW
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ClearUserPasswordPolicy
//
// Description:	fucntion to clear the user password if admin password is empty,
// 				Only Valid with Password Local
//
// Input:		CALLBACK_PASSWORD *callbackData,
//				CHAR16 *saveData
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearUserPasswordPolicy(CALLBACK_PASSWORD *callbackData,CHAR16 *saveData)
{
    if(
        (VARIABLE_ID_AMITSESETUP == callbackData->Variable)&&
        (STRUCT_OFFSET(AMITSESETUP,AdminPassword) == callbackData->Offset)&&
        (0 == ((CHAR16 *)callbackData->Data)[0])
    )
    {
        //Admin password is being cleared
		//Clear user pw; write the same thing for user
		//EIP-172956 To update password values properly
    	if((TSEPwdSavetoNvram())&&( VARIABLE_ID_AMITSESETUP == callbackData->Variable ))
		{
		    AMITSESETUP *TempSaveData = (AMITSESETUP *)NULL;
			UINTN size=0;
			TempSaveData = (AMITSESETUP *) EfiLibAllocateZeroPool(sizeof(AMITSESETUP));
			size = sizeof(AMITSESETUP);

			TempSaveData = VarGetNvram(VARIABLE_ID_AMITSESETUP, &size);
			MemCopy( ((UINT8*)(TempSaveData))+(STRUCT_OFFSET(AMITSESETUP,UserPassword)), saveData, callbackData->Length );
			VarSetNvram( VARIABLE_ID_AMITSESETUP, TempSaveData, sizeof(AMITSESETUP));
			MemFreePointer( (VOID **)&TempSaveData );	       	
		}
    	 else{
    		 VarSetValue(VARIABLE_ID_AMITSESETUP, STRUCT_OFFSET(AMITSESETUP,UserPassword), callbackData->Length, saveData);
    	 }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TseFramePwdCallbackIdePasswordUpdate
//
// Description:	function to update the ide password
//
// Input:		CONTROL_DATA *control,
//				CHAR16 *saveData
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TseFramePwdCallbackIdePasswordUpdate ( CONTROL_DATA *control,CHAR16 *saveData)
{
    BOOLEAN bCheckUser = FALSE;
	VOID * data =control->ControlData.ControlPtr;

	if (control->ControlData.ControlVariable == VARIABLE_ID_IDE_SECURITY )  // IDE Password
	{
        if(/*data->QuestionId*/UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword))
            bCheckUser = TRUE;
		TSEIDEPasswordUpdate( (UINT32)gCurrIDESecPage, saveData, bCheckUser );
		return EFI_SUCCESS;
	}
	else
    	return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TsePopupPwdAuthenticateIDEPwd
//
// Description:	Function to authenticate the IDE password
//
// Input:		POPUP_PASSWORD_DATA *popuppassword, 
//				BOOLEAN *AbortUpdate,
//				VOID *data
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TsePopupPwdAuthenticateIDEPwd(POPUP_PASSWORD_DATA *popuppassword, BOOLEAN *AbortUpdate,VOID *data)
{
   	EFI_STATUS Status = EFI_UNSUPPORTED;
    CHAR16 *Text=NULL;
	if(popuppassword->ControlData.ControlVariable == VARIABLE_ID_IDE_SECURITY ) 
	{
		//if drive is locked ask for the old password to unlock the drive
		VOID* DataPtr = TSEIDEPasswordGetDataPtr(gCurrIDESecPage);
        BOOLEAN bCheckUser = FALSE;
        BOOLEAN EnabledBit = FALSE;
        UINTN size = 0;
        IDE_SECURITY_CONFIG *ideSecConfig;

        ideSecConfig = VarGetVariable( VARIABLE_ID_IDE_SECURITY, &size );
		//EIP-75352 Suppress the warnings from static code analyzer
        if (NULL == ideSecConfig) {
            return EFI_NOT_FOUND;
        }
        if(ideSecConfig->Enabled) EnabledBit = TRUE;

        if(EnabledBit)
        {
            if(UefiGetQuestionOffset(data) /*data->QuestionId*/ == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword))
                bCheckUser = TRUE;

            if(bCheckUser || ideSecConfig->MasterPasswordStatus)
            {
    			Status = _DoPopupEdit( popuppassword, (IsShowPromptStringAsTitle() ? STRING_TOKEN(STR_OLD_PSWD_LABEL): STRING_TOKEN(STR_OLD_PSWD)), &Text);//EIP-116315 password window title string
                if(EFI_SUCCESS != Status )
                {
                    *AbortUpdate = TRUE;
                }
    			else
    			{
                    Status = TSEIDEPasswordAuthenticate( Text, DataPtr, bCheckUser );
                    if(EFI_ERROR( Status ))
        			{
        				CallbackShowMessageBox( (UINTN)gInvalidPasswordFailMsgBox, MSGBOX_TYPE_OK );
        				*AbortUpdate = TRUE;
        			}
					StringZeroFreeMemory ((VOID **)&Text);
    			}
            }
		}

        MemFreePointer((VOID **) &ideSecConfig);
		return EFI_SUCCESS;
	}
	return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TsePopupPwdUpdateIDEPwd
//
// Description:	function to update the IDE password
//
// Input:		None
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TsePopupPwdUpdateIDEPwd (VOID)
{
    UINTN size = 0;
    IDE_SECURITY_CONFIG *ideSecConfig;

    ideSecConfig = VarGetVariable( VARIABLE_ID_IDE_SECURITY, &size );
	//EIP-75352 Suppress the warnings from static code analyzer
    if (NULL == ideSecConfig) {
        return;
    }
    TSEIDEUpdateConfig((VOID*)ideSecConfig, gCurrIDESecPage);
    VarSetValue (VARIABLE_ID_IDE_SECURITY, 0, size, ideSecConfig);		//Updating the cache
	if (gApp != NULL)
		gApp->CompleteRedraw = TRUE;											//EIP 80360 Complete redraw bcoz if User password set it should grayout the Master password.
    MemFreePointer((VOID **)&ideSecConfig);		
}


#if TSE_SEPERATE_EFI_LEGACY_OPTIONS
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsLegacyOption
//
// Description:	function to check for legacy option
//
// Input:		UINT16 Option
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsLegacyOption(UINT16 Option)
{
    BOOT_DATA *pBootData;

    pBootData = BootGetBootData(Option);

    if(pBootData)
    {
        if(BBSValidDevicePath( pBootData->DevicePath ))
            return TRUE;
    }
	
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ReGroupOptions
//
// Description:	function to regroup the boot options
//
// Input:		UINT16 *optionList,
//				UINT16 *OrgOptionList
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ReGroupOptions(UINT16 *optionList,UINT16 *OrgOptionList)
{
    UINTN src, dest, i;
    UINT16 *TempList;
	UINTN LegDevStartIndex=0xFFFF,LegDevStopIndex=0xFFFF;

    TempList = EfiLibAllocatePool(gBootOptionCount * sizeof(UINT16));
    MemCopy(TempList, optionList, gBootOptionCount * sizeof(UINT16));

    dest = 0;
    //Copy all first EFI option
    for(src=0; (src<gBootOptionCount)&&(DISABLED_BOOT_OPTION!=TempList[src]); src++)
    {
        if(IsLegacyOption(TempList[src]))
            break;

        optionList[dest] = TempList[src];
        dest++;
    }

    //Gather all Legacy option
    for(i = src; (i<gBootOptionCount)&&(DISABLED_BOOT_OPTION!=TempList[i]); i++)
    {
        if(IsLegacyOption(TempList[i]))
        {
            optionList[dest] = TempList[i];
            dest++;
			if(LegDevStartIndex == 0xFFFF)
				LegDevStartIndex = i;		// Start Index
			LegDevStopIndex = i;			// End Index Updated for Each Legacy Entry
        }
    }

    //Gather all EFI option
    for(i = src; (i<gBootOptionCount)&&(DISABLED_BOOT_OPTION!=TempList[i]); i++)
    {
        if(!IsLegacyOption(TempList[i]))
        {
			if(OrgOptionList != NULL)
			// Don't Allow Mixing of Legacy and UEFI Boot Options
				if( (i > LegDevStartIndex) && (i < LegDevStopIndex))
				{
					// Restore the Orginal Boot Options
					MemCopy( optionList, OrgOptionList, gBootOptionCount*sizeof(UINT16));
					break;
				}

            optionList[dest] = TempList[i];
            dest++;
        }
    }

    MemFreePointer((VOID **) &TempList);
}
#endif


#ifdef TSE_FOR_APTIO_4_50
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEGetNVVariable
//
// Description:	reads the NV Varaiable from Nram buffer using NVLib.
//
// Input:		UINT32 variable, NVRAM_STORE_INFO *pInfo , UINTN *size
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *TSEGetNVVariable( UINT32 variable, NVRAM_STORE_INFO *pInfo , UINTN *size )
{
	VOID *buffer = NULL;
#if TSE_NVRAM_DEFAULTS_SUPPORT	//EIP-47260: To build TSE without NVRAM module support.
	EFI_STATUS Status = EFI_UNSUPPORTED;
	VARIABLE_INFO *varInfo;
 //UINT8 Flags; EIP: 49745 To fix the CPU hangs when Core is update  to 4.6.4.1 

	varInfo = VarGetVariableInfoIndex( variable );
	if ( varInfo == NULL )
		return buffer;

	*size=0;
	Status = NvGetVariable(
		varInfo->VariableName,
		&varInfo->VariableGuid,
		NULL,
		size,
		buffer,
		pInfo, /*&Flags*/ NULL 			//EIP: 49745 To fix the CPU hangs when Core is update  to 4.6.4.1 
		 
		);

	if ( Status != EFI_BUFFER_TOO_SMALL )
		return buffer;

	buffer = EfiLibAllocatePool( *size );
	if ( buffer == NULL )
		return buffer;

	Status = NvGetVariable(
		varInfo->VariableName,
		&varInfo->VariableGuid,
		NULL,
		size,
		buffer,
		pInfo,/*&Flags*/ NULL 			//EIP: 49745 To fix the CPU hangs when Core is update  to 4.6.4.1 
		);
	    
	if ( EFI_ERROR( Status ) )
	    MemFreePointer( (VOID *)&buffer );

#endif //TSE_NVRAM_DEFAULTS_SUPPORT
	return buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UpdateNVDefautls
//
// Description:	Updated the Variable buffer with NVRam Defaults buffer.
//
// Input:		UINT32 index, NVRAM_STORE_INFO *NvInfo, NVRAM_VARIABLE * VarPtr
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateNVDefautls(UINT32 index, NVRAM_STORE_INFO *NvInfo, NVRAM_VARIABLE * VarPtr)
{
	UINTN Nvsize;
	UINT8 * NvVarBuffer;

	Nvsize = 0;
	NvVarBuffer = TSEGetNVVariable( index, NvInfo , &Nvsize );
	if(NvVarBuffer && Nvsize)
	{
		if(index == VARIABLE_ID_AMITSESETUP)
		{
			if(!IsTseLoadPasswordOnDefaults())
			{
				// To preserve password
				if(Nvsize>=sizeof(AMITSESETUP))
				{
					if(VarPtr->Buffer && (VarPtr->Size>=sizeof(AMITSESETUP)))
					{
						MemCopy(((AMITSESETUP*)NvVarBuffer)->UserPassword, ((AMITSESETUP*)VarPtr->Buffer)->UserPassword,TsePasswordLength*sizeof(CHAR16));
						MemCopy(((AMITSESETUP*)NvVarBuffer)->AdminPassword, ((AMITSESETUP*)VarPtr->Buffer)->AdminPassword,TsePasswordLength*sizeof(CHAR16));
					}
				}
			}
		}

		if(VarPtr->Size >= Nvsize)
		{
			MemCopy(VarPtr->Buffer,NvVarBuffer,Nvsize);
			MemFreePointer( (VOID **)&NvVarBuffer );
		}
		else
		{
			MemFreePointer( (VOID **)&VarPtr->Buffer);
			VarPtr->Buffer = NvVarBuffer;
			VarPtr->Size = Nvsize;
		}
	}

}
#endif


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TseVarBuildAMIDefaults
//
// Description:	function build the AMI defaults
//
// Input:		None
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TseVarBuildAMIDefaults(VOID)
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32	page, control;
	VOID *defaults4FirstBootVar = NULL;
#if TSE_NVRAM_DEFAULTS_SUPPORT	//EIP-47260: To build TSE without NVRAM module support.
	NVRAM_VARIABLE *OptvarPtr;
	NVRAM_VARIABLE *FailsafevarPtr;
	UINT32 index;

#ifdef TSE_FOR_APTIO_4_50
	NVRAM_STORE_INFO NvInfo={0};
	UINTN Nvsize;
	UINT8 * NvVarBuffer=NULL;
	UINT32 attribute=7;
#endif
#endif
	//EIP-93340 Setting "ConstructDefaults4FirstBoot" variable in NVRAM for first boot only
	if ( IsSupportDefaultForStringControl() )
	{
		EFI_GUID ConstructDefaults4FirstBootGuid = CONSTRUCT_DEFAULTS_FIRST_BOOT_GUID;
		UINTN varSize = 0;
		
		defaults4FirstBootVar = (VOID *)VarGetNvramName (L"ConstructDefaults4FirstBoot", &ConstructDefaults4FirstBootGuid, NULL, &varSize);
 		if (NULL == defaults4FirstBootVar)
 		{
 			VarSetNvramName( L"ConstructDefaults4FirstBoot", &ConstructDefaults4FirstBootGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, &varSize, sizeof (varSize) );
		}
 	}//EIP-93340 End
	
	gFailsafeDefaults = EfiLibAllocateZeroPool( sizeof(NVRAM_VARIABLE) * gVariables->VariableCount );
	if ( gFailsafeDefaults == NULL )
	{
		Status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
	gOptimalDefaults = EfiLibAllocateZeroPool( sizeof(NVRAM_VARIABLE) * gVariables->VariableCount );
	if (gOptimalDefaults == NULL )
	{
		Status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
#if TSE_NVRAM_DEFAULTS_SUPPORT	//EIP-47260: To build TSE without NVRAM module support.
	// Load the Current NVRAM variable then update the defaults.
	OptvarPtr = gOptimalDefaults;
	FailsafevarPtr = gFailsafeDefaults;
	for ( index = 0; index < gVariables->VariableCount; index++, OptvarPtr++, FailsafevarPtr++)
	{
		if ((VARIABLE_ID_AMITSESETUP == index) && (TseDefaultSetupPasswordSupported ()))
		{
			OptvarPtr->Buffer = VarGetNvram( index, &OptvarPtr->Size );
			if (OptvarPtr->Buffer)
			{
				MemSet(OptvarPtr->Buffer, ((TsePasswordLength * 2) * sizeof(CHAR16)), 0 );		//Preserving quietboot details
				if ((!DefaultSetupPwdAtFirstBootOnly ()))
				{
					GetDefaultPassword (AMI_PASSWORD_NONE, &OptvarPtr->Buffer);
				}
			}
		}
		else
		{
			OptvarPtr->Buffer = VarGetNvram( index, &OptvarPtr->Size );
		}
		if(OptvarPtr->Size)
		{
			// init mfg defautls from Std Defaults 
			FailsafevarPtr->Buffer = EfiLibAllocateZeroPool (OptvarPtr->Size);
			if (NULL == FailsafevarPtr->Buffer)
				continue;
			if (NULL == OptvarPtr->Buffer)			//Add the fix for: If name value string is not able to retrieve then system hang
			{
				OptvarPtr->Buffer = EfiLibAllocateZeroPool (OptvarPtr->Size);
				if (NULL == OptvarPtr->Buffer)
					continue;
			}
			MemCopy(FailsafevarPtr->Buffer, OptvarPtr->Buffer,OptvarPtr->Size);
		}
		else
			FailsafevarPtr->Buffer = NULL;
		FailsafevarPtr->Size = OptvarPtr->Size;
	}
#endif	//TSE_NVRAM_DEFAULTS_SUPPORT

	// this is the AMIBCP compatible user defaults
	for ( page = 0; page < gPages->PageCount; page++ )
	{
		PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[page]);

		if(pageInfo->PageHandle ==0)
			continue;
		if (NULL == gApp)
		{
			gtempCurrentPage = page;					//Will be used in UefiGetQuestionOffset. Since gApp will not be filled but we need handle to find name value variable so
		}												//saving current page
		else
		{
			gApp->CurrentPage = page;
		}
			
		for ( control= 0; control < pageInfo->PageControls.ControlCount; control++ )
		{
			CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

			if ( ( controlInfo->ControlVariable == VARIABLE_ID_LANGUAGE ) || ( controlInfo->ControlVariable == VARIABLE_ID_BOOT_ORDER ) || (controlInfo->ControlVariable == VARIABLE_ID_BBS_ORDER) )
				continue;

			if ( controlInfo->ControlDataWidth > 0 )
			{
				VOID *ifrData = controlInfo->ControlPtr;
				UINT8 *failValue = NULL, *optValue = NULL;
				UINT32 ControlVarOffset = 0;

				if ( ifrData == NULL )
					continue;

				failValue = (UINT8 *)controlInfo + sizeof(CONTROL_INFO);
				optValue = failValue + controlInfo->ControlDataWidth;

				ControlVarOffset = UefiGetQuestionOffset(ifrData);
				//EIP-93340 Updating gOptimalDefaults and gFailSafeDefaults for stringType controls based on controlPtr
				if (IsSupportDefaultForStringControl () && controlInfo->ControlType == CONTROL_TYPE_POPUP_STRING)
				{
					CHAR16 *failDefStr = NULL, *optimalDefStr = NULL;
					
					if (*(UINT16*)(failValue))
					{
						failDefStr = (VOID*)HiiGetString( controlInfo->ControlHandle, *(UINT16*)(failValue));
						if (NULL == failDefStr)
							continue;
						_VarGetSetValue( VAR_COMMAND_SET_VALUE, gFailsafeDefaults, controlInfo->ControlVariable, ControlVarOffset, EfiStrLen(failDefStr)*sizeof(CHAR16), (VOID*)failDefStr );
					}
					
					if (*(UINT16*)(optValue))
					{
						optimalDefStr = (VOID*)HiiGetString( controlInfo->ControlHandle, *(UINT16*)(optValue));
						if (NULL == optimalDefStr)
							continue;
						_VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, controlInfo->ControlVariable, ControlVarOffset, EfiStrLen(optimalDefStr)*sizeof(CHAR16), (VOID*)optimalDefStr );
					}
					
					if (NULL == defaults4FirstBootVar && optimalDefStr) //Modify NVRAM for first time for string type controls based on defaults from controlPtr
					{
						VOID *optiBuffer = NULL, *failBuffer = NULL;
						VARIABLE_INFO 	*varInfo = (VARIABLE_INFO *)NULL;
						UINTN size = 0;
						EFI_STATUS status = EFI_SUCCESS;
						
						varInfo = VarGetVariableInfoIndex (controlInfo->ControlVariable);
						
						optiBuffer = VarGetNvram( controlInfo->ControlVariable, &size );						
						if (NULL == optiBuffer)
						{
							continue;
						}

						MemCopy ( ((UINT8*)optiBuffer)+ControlVarOffset, (UINT8*)optimalDefStr, EfiStrLen(optimalDefStr)*sizeof(CHAR16) );
						
						status = VarSetNvramName( varInfo->VariableName, &varInfo->VariableGuid, varInfo->VariableAttributes, optiBuffer, size );
						if (optiBuffer)
							MemFreePointer( (VOID **)&optiBuffer );
					}
					if (failDefStr)
						MemFreePointer( (VOID **)&failDefStr );
					
					if (optimalDefStr)
						MemFreePointer( (VOID **)&optimalDefStr );
					
				}
				//EIP-93340 End
				else
				{				
					_VarGetSetValue( VAR_COMMAND_SET_VALUE, gFailsafeDefaults, controlInfo->ControlVariable, ControlVarOffset, controlInfo->ControlDataWidth, failValue );
					_VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, controlInfo->ControlVariable, ControlVarOffset, controlInfo->ControlDataWidth, optValue );
				}
			}
		}
	}

#ifdef TSE_FOR_APTIO_4_50
#if TSE_NVRAM_DEFAULTS_SUPPORT	//EIP-47260: To build TSE without NVRAM module support.
	// StdDefaults
	Nvsize = 0;
	NvVarBuffer = VarGetNvramName( L"StdDefaults", &DefaultsGuid, &attribute, &Nvsize );
	if(NvVarBuffer && Nvsize)
	{
		NvInfo.NvramAddress = NvVarBuffer;
		NvInfo.NvramSize = Nvsize;
		NvInitInfoBuffer(&NvInfo, 0, NVRAM_STORE_FLAG_NON_VALATILE );

		// Update the defaults.
		OptvarPtr = gOptimalDefaults;
		for ( index = 0; index < gVariables->VariableCount; index++, OptvarPtr++)
		{
			UpdateNVDefautls(index, &NvInfo, OptvarPtr);
		}
		MemFreePointer( (VOID **)&NvVarBuffer );
	}

	// MfgDefaults
	Nvsize = 0;
	NvVarBuffer = VarGetNvramName( L"MfgDefaults", &DefaultsGuid, &attribute, &Nvsize );
	if(NvVarBuffer && Nvsize)
	{
		NvInfo.NvramAddress = NvVarBuffer;
		NvInfo.NvramSize = Nvsize;
		NvInitInfoBuffer(&NvInfo, 0, NVRAM_STORE_FLAG_NON_VALATILE );

		FailsafevarPtr = gFailsafeDefaults;
		for ( index = 0; index < gVariables->VariableCount; index++, FailsafevarPtr++ )
		{
			UpdateNVDefautls(index, &NvInfo, FailsafevarPtr);
		}
		MemFreePointer( (VOID **)&NvVarBuffer );
	}
	//EIP-93340 Updating optimalDefaults and gFailsafeDefaults for STRING_TYPE controls 
	//based on defalut stringID present in controlPtr
	GetSetDefaultsFromControlPtr(gOptimalDefaults, gFailsafeDefaults);
#endif	//TSE_NVRAM_DEFAULTS_SUPPORT
#endif
DONE:
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TseBootNowinBootOrderInit
//
// Description:	function build the AMI defaults
//
// Input:		None
//
// Output:		boot order string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 * TseBootNowinBootOrderInit(VOID)
{
    UINT16 *BootOrder=NULL;
    UINTN size = 0;
    UINTN j,k,i;

	BootOrder = HelperGetVariable(VARIABLE_ID_BOOT_ORDER, L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
	//EIP-75352 Suppress the warnings from static code analyzer
	if (NULL == BootOrder) {
		ASSERT (0);
		return NULL;
	}
    //Find the first disabled option
    for ( i = 0; i < gBootOptionCount; i++ )
    {
        if ( DISABLED_BOOT_OPTION == BootOrder[i] )
            break;
    }

    if(i<gBootOptionCount)
    {
        //There are disabled options replace them with valid options
        for(j=0;j<gBootOptionCount;j++)
        {
            for(k=0;k<gBootOptionCount;k++)
            {
                if(BootOrder[k] == gBootData[j].Option)
                    break;
            }

            if(k >= gBootOptionCount)
            {
                //gBootData[j].Option is not present in BootOrder; fill it
                BootOrder[i] = gBootData[j].Option;
                i++;
            }
        }
    }
	return BootOrder;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckShiftState
//
// Description:	function to check the shift state value
//
// Input:		None
//
// Output:		1 - valid shift state
//				0 - invalid shift state
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckShiftState(UINT32 KeyShiftState, UINT32 HotkeyState)
{
	if( KeyShiftState == HotkeyState)
		return 1;
	else
		return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SupportPrintScreen
//
// Description:	function to support the print screen.
//
// Input:		None
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SupportPrintScreen()
{
	EFI_GUID guid = AMITSE_PRINT_SCREEN_PRESS_GUID;
	// Install the PrintScreen Notification. 
    EfiLibNamedEventSignal (&guid);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SupportPrintScreenEvent
//
// Description:	function to check the print screen supprot event.
//
// Input:		UINT16 ScanCode
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SupportPrintScreenEvent(UINT16 ScanCode)
{
	if( ScanCode == TSE_PRN_SCRN_KEY_SCAN )
		return 1;
	else 
		return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsToggleStateKey
//
// Description:	function to check Is any of ToggleStateKey (CapsLock,Numlock ScrollLock) Keys pressed.
//
// Input:		ACTION_DATA *Data
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsToggleStateKey(ACTION_DATA *Data)
{
	if(Data->Input.Type == ACTION_TYPE_KEY)
	{
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
		if(Data->Input.Data.AmiKey.EfiKey == EfiKeyCapsLock || Data->Input.Data.AmiKey.EfiKey ==  EfiKeySLck || Data->Input.Data.AmiKey.EfiKey ==  EfiKeyNLck)
			return TRUE;
		else
#endif
		{
			// Normal EFI_KEY will return ScanCode and Unicode as 0 for this toggleStateKeys.
			if(Data->Input.Data.AmiKey.Key.ScanCode || Data->Input.Data.AmiKey.Key.UnicodeChar)
				return FALSE;
			else
				return TRUE;
		}
	}
	else
		return FALSE;
}

//EIP-96246 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ShowBootOverrideSelectOption
//
// Description:	function to Show menu with below option on selecting options under Boot Override 
//						1) Override now and clear the BootNext data
//						2) Override now but keep the BootNext data
//						3) Boot to BootNext and clear BootNext data
// Input:		VOID
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ShowBootOverrideSelectOption (VOID)
{

	UINT16 ItemCount = 3,itemSelected = 0;
	UINT16	Title, Legend;
	UINT8 i;
	EFI_STATUS Status;
	POSTMENU_TEMPLATE *BootNextOverrideOptionsMenu = NULL; 

	UINT16 BootNextOverrideOptionString[3] = {STRING_TOKEN (STR_OVERRIDE_BOOTNEXT_OPTION_1), STRING_TOKEN (STR_OVERRIDE_BOOTNEXT_OPTION_2), STRING_TOKEN (STR_OVERRIDE_BOOTNEXT_OPTION_3)};

	BootNextOverrideOptionsMenu = EfiLibAllocateZeroPool ( sizeof( POSTMENU_TEMPLATE ) * BOOT_OVERRIDE_OPTION_MENU_COUNT);

	for ( i = 0; i < BOOT_OVERRIDE_OPTION_MENU_COUNT; i++ )
	{
		BootNextOverrideOptionsMenu[i].ItemToken = BootNextOverrideOptionString[i];
		BootNextOverrideOptionsMenu[i].Callback = (VOID*)NULL ;
		BootNextOverrideOptionsMenu[i].CallbackContext = (VOID*)NULL ;
		BootNextOverrideOptionsMenu[i].Attribute = AMI_POSTMENU_ATTRIB_FOCUS;
		BootNextOverrideOptionsMenu[i].Key.Key.ScanCode = 0 ;
		BootNextOverrideOptionsMenu[i].Key.Key.UnicodeChar = 0 ;
		BootNextOverrideOptionsMenu[i].Key.KeyShiftState = 0 ;
	}


	Title = STRING_TOKEN (STR_OVERRIDE_OPTION_MENU_TITLE) ;
	Legend = STRING_TOKEN (STR_OVERRIDE_OPTION_MENU_LEGEND) ;

	//To show menu with options
	Status = PostManagerDisplayMenu (gHiiHandle, Title, Legend, BootNextOverrideOptionsMenu, BOOT_OVERRIDE_OPTION_MENU_COUNT, &itemSelected);
	
	if( Status == EFI_SUCCESS )
	{
		UINTN size = 0;
		UINT16  *pBootNext = NULL;
		pBootNext = (UINT16 *)VarGetNvramName (L"BootNext", &gEfiGlobalVariableGuid, NULL, &size);

		//Override now and clear the BootNext data
		if ( BootNextOverrideOptionsMenu[itemSelected].ItemToken == BootNextOverrideOptionString[0] )
		{
		   if( pBootNext && (size == sizeof(UINT16)))
		   {	       
		   	//Clear Boot next variable
		    	VarSetNvramName (L"BootNext",
		     							&gEfiGlobalVariableGuid,
		                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
		                        NULL,
		                        0);
			}
			if(pBootNext)
				MemFreePointer((void **) &pBootNext);
			Status = EFI_SUCCESS;		
		}
		//Override now but keep the BootNext data
		else if(BootNextOverrideOptionsMenu[itemSelected].ItemToken == BootNextOverrideOptionString[1])
		{
			Status = EFI_SUCCESS;
			return Status;
		}
		//Boot to BootNext and clear BootNext data
		else if(BootNextOverrideOptionsMenu[itemSelected].ItemToken == BootNextOverrideOptionString[2])
		{
			if( pBootNext && (size == sizeof(UINT16)))
			{
				//Clear Boot next variable
		    	VarSetNvramName (L"BootNext",
		     							&gEfiGlobalVariableGuid,
		                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
		                        NULL,
		                        0);
				if(!gResetRequired)
				{
					if(!gDoNotBoot)
     				{
	 					gApp->ClearScreen = TRUE;
	 					StyleExit();
	 					if (gST->ConOut != NULL)
	 					{             	 		
             	 		gST->ConOut->EnableCursor( gST->ConOut, FALSE );
             	 		gST->ConOut->SetAttribute( gST->ConOut, (EFI_BACKGROUND_BLACK | EFI_WHITE));
             	 		gST->ConOut->ClearScreen( gST->ConOut);
	 					}
 						BootLaunchBootOption(*pBootNext, NULL, 0); //Boot to BootNext option
						StyleInit();
             	}
				}				
			}
			if(pBootNext)
				MemFreePointer((void **) &pBootNext);

			Status = EFI_UNSUPPORTED;
		}
	}
	return Status;
}
//EIP-96246 Ends

//EIP-93340 Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		GetSetDefaultsFromControlPtr
//
// Description:	Function to get default stringID for String Type control from controlPtr and
//						fetch respective string from Hii database and set as default to NVRAM, gOptimalDefaults, gFailSafeDefaults buffer
// Input:			NVRAM_VARIABLE *OptimalDefs, NVRAM_VARIABLE *FailSafeDefs
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetSetDefaultsFromControlPtr(NVRAM_VARIABLE *optimalDefaultlist, NVRAM_VARIABLE *failSafeDefaultlist)
{
	EFI_STATUS status = EFI_UNSUPPORTED;

	if ( IsSupportDefaultForStringControl () )
	{
		UINT32	page = 0, control = 0;
		
		for ( page = 0; page < gPages->PageCount; page++ )
		{
			PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[page]);

			if(pageInfo->PageHandle ==0)
				continue;

			for ( control= 0; control < pageInfo->PageControls.ControlCount; control++ )
			{
				CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

				if ( ( controlInfo->ControlVariable == VARIABLE_ID_LANGUAGE ) || ( controlInfo->ControlVariable == VARIABLE_ID_BOOT_ORDER ) || (controlInfo->ControlVariable == VARIABLE_ID_BBS_ORDER) )
					continue;

				//To update Optimal and FailSafe defaults with STRING default based on StringID from controlPtr
				if ( (controlInfo->ControlType == CONTROL_TYPE_POPUP_STRING) && (controlInfo->ControlDataWidth > 0) )
				{
					if ( (optimalDefaultlist) || (failSafeDefaultlist))
					{
						CHAR16 *failDefStr = NULL, *optimalDefStr = NULL;
						UINT8 *failValue, *optValue;
						UINT32 ControlVarOffset, size = 0;

						//Getting stringID if any present in controlPtr for failsafe default
						failValue = (UINT8 *)controlInfo + sizeof(CONTROL_INFO);
					
						//Getting stringID if any present in controlPtr for optimal default
						optValue = failValue + controlInfo->ControlDataWidth;
						//size = controlInfo->ControlDataWidth;

						size = UefiGetWidth (controlInfo->ControlPtr) * sizeof(CHAR16); 	
						ControlVarOffset = UefiGetQuestionOffset(controlInfo->ControlPtr);
					
						//Getting string based on StrigID from controlPtr and updating failsafeDefaults
						if (NULL != failSafeDefaultlist)
						{
							if (*(UINT16*)(failValue))
							{
								failDefStr = (VOID*)HiiGetString( controlInfo->ControlHandle, *(UINT16*)(failValue));
								if (NULL == failDefStr)
									continue;
								_VarGetSetValue( VAR_COMMAND_SET_VALUE, gFailsafeDefaults, controlInfo->ControlVariable, ControlVarOffset, EfiStrLen(failDefStr)*sizeof(CHAR16), failDefStr );
							}
						}

						//Getting string based on StrigID from controlPtr and updating optimalDefaults
						if (NULL != optimalDefaultlist)
						{
							if (*(UINT16*)(optValue))
							{
								optimalDefStr = (VOID*)HiiGetString( controlInfo->ControlHandle, *(UINT16*)(optValue));
								if (NULL == optimalDefStr)
									continue;
								status = _VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, controlInfo->ControlVariable, ControlVarOffset, EfiStrLen(optimalDefStr)*sizeof(CHAR16), optimalDefStr );
							}
						}
				
						if (failDefStr)
							MemFreePointer( (VOID **)&failDefStr );
					
						if (optimalDefStr)
							MemFreePointer( (VOID **)&optimalDefStr );
					}//End of optimal/Failsafe condition check
				}//End of ControlType condition check
			}//End of control iteration
		}//End of Page iteration
	}//End of Default support condition check
	return status;
}
//EIP-93340 End
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
