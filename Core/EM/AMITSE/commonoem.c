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
// $Archive: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/em/AMITSE/commonoem.c $
//
// $Author: Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 7/08/15 4:29a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/em/AMITSE/commonoem.c $
// 
// 1     7/08/15 4:29a Chienhsieh
// Update rev66
// 
// 66    4/22/15 8:22a Omkark
// [TAG]  EIP201836
// [Category]  Bug Fix
// [Severity:]  Normal
// [Symptom:] ARM systems generate exception after 3 invalid password
// tries in the POST
// [Root Cause] Parameters are not used properly for WaitForEvent function
// during POST password.
// [Solution]  Handled parameters for WaitForEvent() function.
// [Files]  commonoem.c
// 
// 62    8/28/14 12:02p Premkumara
// [TAG] 		EIP174154
// [Category] 	Bug Fix
// [Severity:] Normal
// [Symptom:] 	TMM Settings page is moved to wrong position
// [Solution] 	If root page ordering is not present for some of the boot
// flows then menu ordering will not present.
// So for the boot flows which doesn't has ordering now
// BOOT_FLOW_CONDITION_NORMAL ordering will be applied.
// [Files] 		commonoem.c
// 
// 61    8/28/14 10:09a Premkumara
// [TAG] 			EIP174031
// [Category] 		Improvement
// [Description] 	Removed TODO comments and added proper comments in those
// places
// [Files] 			commonoem.c, commonhelper.c, special.c, submenu.c,
// minisetupext.c, uefi21wapper.c and legacy.c
// 
// 60    5/21/14 6:23p Arunsb
// [TAG]	EIPEIP169096,168632
// [Description]	Changed global variable guid usage for tse debug messages
// [Files]	commonoem.c, setupdbg.h and print.c
// 
// 59    5/08/14 4:25p Arunsb
// [TAG]  		EIP162197
// [Category]  	Improvement
// [Description]  	Password encode feature modify to encode using Hashing
// based on token.
// PasswordEncode function moved to PasswordEncode module.
// 
// 58    5/02/14 2:10p Premkumara
// [TAG]  		EIP140123 
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	While showing secureboot error msg mouse is not move and
// get hang. Softkbd is displaying
// [RootCause]  	MouseClickEvent is not stopped while boot to any option.
// So clicking outside msg box causes displaying
// softkbd and mouse is not init at this phase.
// [Solution]  	Initialized mouse and deactivating any softkbd activated
// before showing secureboot error msg box.
// [Files]  		CommonHelper.c, CommonOem.c, MessageBox.c
// 
// 57    5/02/14 5:44a Arunsb
// [TAG]  		EIP156258
// [Category]  	Improvement
// [Description]  	Providing ELINK option to suppress the handle
// comparison on dynamic parsing
// [Files]  		AMITSE.mak, AMITSE.sdl, commonoem.c, commonoem.h and Parse.c
// 
// 56    5/02/14 4:41a Premkumara
// [TAG]  		EIP95647
// [Category]  	Improvement
// [Description]  	Dynamic Forms need to hide.
// [Files]  		AMITSE.mak, AMITSE.sdl, CommonOem.c, Parse.c
// 
// 55    2/11/14 10:52p Arunsb
// Build error rectified for EFI_STRING_ID
// 
// 54    12/04/13 5:17a Premkumara
// [TAG]	EIP123535
// [Category]	Improvement
// [Description]	Moved saving quietboot resolution to DrawQuietBootLogo()
// to avoid setting resolution of initPostScreenthis while booting.
// [Files]	commonoem.c, Boot.c, Logo.c, MinisetupExt.c
// 
// 53    12/04/13 2:58a Premkumara
// [TAG]	EIP139099
// [Category]	New Feature
// [Description]	Supress formset other than
// EFI_HII_PLATFORM_SETUP_FORMSET_GUID and
// EFI_HII_DRIVER_HEALTH_FORMSET_GUID through elink based on token
// [Files]	AMITSE.sdl, AMITSE.mak, CommonOem.c, Hii.c, Parse.c,
// TseUefiHii.h
// 
// 52    5/22/13 10:13a Arunsb
// Moving password encoding to source
// 
// 51    4/18/13 1:47a Arunsb
// [TAG]  		EIP81490
// [Category]  	New Feature
// [Description]  	Post message support for BBS popup menu
// [Files]  		AMITSE.sdl, AmiTSEStr.uni, commonoem.c, FakeTokens.c and
// globals.c
// 
// 50    3/18/13 2:04p Blaines
// [TAG] - EIP 118410 
// [Category] - Defect 
// [Symptom] - Hidden tabs when dynamic pages are present in setup.
// [Description] - Setup is missing tabs (i.e. Security, Boot, Exit), when
// pages are dynamically added to Advanced menu. 
// This has been seen with both SAS and Network UEFI drivers that
// dynamically publish setup pages.
// 
// [Root cause]
// The functions FixSubPageAsRootPageList and FixHiddenPageList will
// typecast gPages->PageCount to UINT8 in the for-loop to search the page
// data.
// The masking of this count value will affect the parsing of
// AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST, and AMITSE_ROOT_PAGE_ORDER.
// 
// [Solution]- Use UINTN to typecast gPages->PageCount in the for-loop
// used to search the page data.
// 
// [Files] 
//   -  commonoem.c
// 
// [Functions]
// - FixSubPageAsRootPageList
// - FixHiddenPageList
// 
// 49    3/06/13 12:23a Premkumara
// [TAG]  		EIP111415
// [Category]  	Improvement
// [Description]  	Elink function for SETUP_TOGGLE_KEY_UNICODE function
// [Files]  		HookAnchor.h, AMITSE.sdl, commonoem.c, Commonoem.h,
// HookList.c, HookAnchor.c
// 
// 48    10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 30    10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 46    9/25/12 12:26p Rajashakerg
// [TAG]  		EIP92053 
// [Category]  	Improvement
// [Description]  	Need support define Root page order using elinks
// [Files]  		AMITSE.sdl, Menu.c, AMIVfr.h, AMITSE.mak, commonoem.c
// 
// 45    9/25/12 9:27a Rajashakerg
// [TAG]  		EIP92053 
// [Category]  	Improvement
// [Description]  	Need support define Root page order using elinks
// [Files]  		AMITSE.sdl, Menu.c, AMIVfr.h, AMITSE.mak, commonoem.c
// 
// 44    9/21/12 7:27a Premkumara
// [TAG]  		EIP 90647 
// [Category]  	Improvement
// [Description]  	Implement new token to launch Boot Menu using shift
// state key such as CTRL+F7
// [Files]  		AMITSE.sdl, Commonoem.c
// 
// 43    9/17/12 5:59a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 41    8/29/12 4:11p Arunsb
// [TAG]  			EIP94702
// [Description]  	Support for Native Resolution in POST/BOOT
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c, boot.c, logo.c,
// notify.c, postmgmt.c, tselite\minisetupext.c, ezport/stylecommon.c,
// ezportplus/stylecommon.c andlegacy/stylecommon.c
// 
// 40    5/29/12 3:18a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 39    5/09/12 5:25p Arunsb
// [TAG]  		EIP85768
// [Category]  	Improvement
// [Description]  	Combination key does not work properly for checkoemkey
// functionality
// [Files]  		commonoem.c
// 
// 38    4/27/12 2:05p Arunsb
// Build error rectified
// 
// 37    4/27/12 11:18a Arunsb
// [TAG]  		EIP85904
// [Category]  	New Feature
// [Description]  	OS indication support
// [Files]  		Amitse.sdl and commonoem.c
// 
// 36    4/27/12 9:44a Arunsb
// [TAG]  		EIP84199
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	ProcessConInAvailability displays "Press <F2> or <DEL> to
// enter Setup." message on the POST screen as many times as it is hooked.
// [RootCause]  	ProcessConInAvailability called twice
// [Solution]  	Messages displayed only once regardless of number of times
// ProcessConInAvailability hook get called
// [Files]  		commonoem.c
// 
// 35    4/04/12 12:24a Rajashakerg
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
// 34    2/03/12 9:29p Madhans
// [TAG]     EIP82552 
// [Category]  Bug Fix
// [Severity]  Normal
// [Symptom]   Soft Keyboard is On after booted to BIOS setup from POST
// [RootCause] Soft Keyboard is not deactivated for time out in post
// [Solution]  Soft keyboard deactivated for time out too
// [Files]     commonoem.c
// 
// 33    2/02/12 1:21a Arunsb
// [TAG]  		EIP81959
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Stop at LOGO if continue to press one of Shift / Alt / Ctrl
// keys
// [RootCause]  	Partial keys not handled
// [Solution]  	Partial keys handled properly
// [Files]  		commonoem.c
// 
// 32    2/01/12 1:55a Arunsb
// [TAG]  		EIP74968
// [Category]  	Improvement
// [Description]  	Support for mouse drag and drop to rearrange the items
// in the Orderlist.
// [Files]  		Ordlistbox.c, commonoem.c and commonoem.h
// 
// 31    1/25/12 8:31a Rajashakerg
// [TAG]  		EIP62763 
// [Category]  	Improvement
// [Description]  	Utilize the Improvements done from mouse driver in
// AMITSE
// [Files]  		commonoem.c
// 
// 30    12/28/11 4:10a Arunsb
// [TAG]  		EIP75021 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	[TSE] In Date and Time item Press Shift+Tab key can't move
// previous field.
// [RootCause]  	Shift states not checked properly
// [Solution]  	Shift state bits are cleared for every combinations and
// compared at last
// [Files]  		commonoem.c and commonhelper.c
// 
// 29    11/20/11 6:54a Rajashakerg
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
// 28    11/14/11 2:40p Blaines
// [TAG] - EIP 75481
// [Category]- Function Request
// [Synopsis]- TSE debug print infrastructure.
// [Description]- Add TSE debug print info for basic functions such as
// Hiiparsing, HiiNotifications, HiiCallbacks. Variables, and Ifrforms
// data. 
// [Files]
// AMITSE.sdl, AmiTSEStr.uni,  CommonHelper.c, commonoem.c, FakeTokens.c
// Globals.c, Minisetup.cif, Minisetup.h, print.c, FormBrowser2.c, Hii.c,
// HiiCallback.c, HiiNotificationHandler.c, Parse.c, TseUefiHii.h,
// Uefi21Wrapper.c, setupdbg.h
// 
// 27    11/01/11 4:21a Arunsb
// [Category]  	Improvement
// [Description]  	To change the single click behaviour as like double
// click
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c and listbox.c
// 
// 26    9/22/11 2:45a Arunsb
// [TAG]  		EIP64402
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	If logo.ffs not present in TSE then BGRT table not
// formed for badging images.
// This one is fixed.
// [Files]  		commonoem.c
// 
// 25    9/21/11 1:56p Arunsb
// [TAG]  		EIP66443
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Build fails when SETUP_BBS_POPUP_ENABLE is enabled and
// SETUP_ALT_ENTRY_ENABLE is disabled.
// [RootCause]  	By default, SETUP_BBS_POPUP_ENABLE is set to disabled and
// SETUP_ALT_ENTRY_ENABLE is enabled.
// If the customer sets SETUP_BBS_POPUP_ENABLE to enabled, and
// SETUP_ALT_ENTRY_ENABLE to disabled, then the
// SETUP_ALT_ENTRY_SHIFT_STATE SDL token is not defined and thus the build
// error arose.
// [Solution]  	SETUP_ALT_ENTRY_SHIFT_STATE SDL token is validated before
// its usage.
// [Files]  		commonoem.c
// 
// 24    6/30/11 3:55a Arunsb
// Unused BootOption variable removed.
// 
// 23    6/29/11 2:06p Arunsb
// EIP 62631 gHotKeyBootOption declaration moved to commonhelper.c
// 
// 22    6/29/11 6:03a Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Hot key boot option support in TSE as per UEFI spec.
// section 3.1.6.
//                 CheckAdvShiftState function moved from commonoem.c to
// here.
//                 BootLaunchBootOption removed in checkforkey function to
// avoid TPL problem.    
// [Files]         AMITSE.sdl, bootflow.c, bootflow.h, CommonHelper.c,
// commonoem.c, commonoem.h, boot.c,
//                 hiistring20.c, hiistring21.c and notify.c.
// 
// 21    6/23/11 8:29p Arunsb
// [TAG]  		EIP62466
// [Category]  	Improvement
// [Description]  	Trace message support in commonoem.c.
// Included amidxelib.h file.
// [Files]  		commonoem.c
// 
// 20    6/22/11 7:10a Arunsb
// [TAG]           EIP 62631, 60128 
// [Category]      New Feature
// [Description]   Hot key boot option in TSE as per UEFI spec. section
// 3.1.6.
//                 Hot key checked.
//                 CheckAdvShiftState function added to handle special
// case like Ctrl+Alt+F6.
//                 TSE_CHECK_SHIFTSTATE added for checking special key to
// launch setup.    
// [Files]         AMITSE.sdl, CommonHelper.c, commonoem.c, commonoem.h,
// boot.c, hiistring20.c and hiistring21.c.
// 
// 19    6/20/11 3:50p Arunsb
// [TAG]            EIP57660 
// [Category]     New Feature
// [Description]  Non-removable media boot behavior as described in UEFI
// specification v 2.3.1, p. 3.4.1.
//                       Added CheckForSetupKey function to check setup
// key pressed.
// [Files]            amitse.sdl, bootflow.c, bootflow.h, commonoem.c,
// boot.c and protocol.c
// 
// 18    5/29/11 12:01p Arunsb
// [TAG]           EIP58954
// [Category]      New Feature
// [Description]   Quiet boot logo's only added for BGRT. BGRT status
// field cleared if any changes happened in screen other than displaying
// the image.
// [Files]         Postmgmt.c, boot.c, logo.c commonoem.c and
// commonhelper.c
// 
// 17    5/03/11 9:55p Arunsb
// [TAG]  		EIP58954
// [Category]  	New Feature
// [Description]  	Contributing BGRT table to ACPI table.
// CONTRIB_BGRT_TABLE_TO_ACPI token added. EDK Build support added. Code
// moved to drawimage function.
// [Files]  		Postmgmt.c, commonoem.c and commonhelper.c
// 
// 16    4/23/11 3:10p Arunsb
// [TAG]  		EIP58954
// [Category]  	New Feature
// [Description]  	Contributing BGRT table to ACPI table.
// CONTRIB_BGRT_TABLE_TO_ACPI token added.
// [Files]  		Postmgmt.c and commonoem.c
// 
// 15    3/28/11 9:06p Madhans
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
// 14    12/28/10 4:15p Mallikarjunanv
// [TAG]  		EIP 47837
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Shift key combinations are not working properly.
// [RootCause]  	Issues with handling shiftstate in case of AMI Keycode
// protocol
// [Solution]  	udpated the sources to verify the key with and without
// shiftstate value in case of TSE_USE_AMI_KEYCODE_PROTOCOL enabled.
// 
// [Files]  		Commonoem.c
// 
// 13    12/27/10 3:07a Mallikarjunanv
// 
// 12    12/26/10 5:15p Mallikarjunanv
// [TAG]  		EIP47387
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Shift key combinations are not working properly.
// [RootCause]  	Issues with handling shiftstate in case of AMI Keycode
// protocol
// [Solution]  	udpated the sources to verify the key with and without
// shiftstate value in case of TSE_USE_AMI_KEYCODE_PROTOCOL enabled.
// [Files]  		commonoem.c
// 
// 11    12/02/10 2:31p Madhans
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
// 10    9/16/10 8:39p Madhans
// Updated for TSE 2.10. Refer changelog.log for more deatils.
// 
// 25    8/18/10 6:15p Mallikarjunanv
// EIP-38089: Hook after pressing F2 key and before showing setup menu.
// 
// 24    8/13/10 10:21a Mallikarjunanv
// EIP-40772: Created a token to control enter setup string in POST during
// 
// 23    7/07/10 7:36p Madhans
// To fix the issue of Not booting from BBS if SetupEntry and BBS Keys
// pressed togather multiple time.
// 
// 22    6/14/10 7:03p Madhans
// To avoid warning
// 
// 21    6/08/10 5:06p Blaines
// Created new AMITSE hook (hook33), called when TSE determines that
// console out is available.
// 
// 20    5/14/10 4:08p Madhans
// EIp 38626 : to include the OEM header files in commonoem.h
// 
// 19    4/21/10 11:09a Mallikarjunanv
// EIP-36596: Logo ImageData buffer freeing issue fixed
// 
// 18    4/13/10 6:01p Madhans
// Eip: 33100 To create new hook for BootNowLaunching. (From bbsPopoup and
// Boot override menu).
// 
// 17    4/13/10 5:12p Madhans
// EIP: 37439 To support extended OEM Key support.
// 
// 16    4/07/10 6:23p Madhans
// Post Screen Scroll Area Support.TSE_POSTSCREEN_SCROLL_AREA Sdl token
// Controls it.
// 
// 15    2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 14    2/15/10 10:02p Madhans
// 
// 13    2/04/10 11:06p Madhans
// MapControlActionMouse hook added.
// 
// 12    1/18/10 2:05a Mallikarjunanv
// EIP-28501: Updated for Keyboard scancode as password. Added a new Token
// SETUP_STORE_KEYCODE_PASSWORD to support the EFI key or Scan code as
// password
// 
// 11    1/09/10 2:26a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 10    12/04/09 7:13a Mallikarjunanv
// Fix for EIP:30263 - Gif Logo Issue
// 
// 9     11/05/09 12:38p Mallikarjunanv
// deleted the function HiiGetEfiKey, which is moved to uefi module
// 
// 8     10/30/09 9:46a Mallikarjunanv
// EIP-28551 : Fixed TSE 2.0 Build error releated to
// SETUP_STORE_EFI_KEY_PASSWORD and TSE_USE_AMI_EFI_KEYCODE_PROTOCOL 
// 
// 7     10/28/09 5:34p Madhans
// 1. Support to Add the String from other modules to TSE.
// 2. Clean of GIF and Image code Control them with minimal code from TSE
// binary.
// 
// 
// 6     9/15/09 9:16a Sudhirv
// added new hooks for LoadSetupDefaults and PreSystemReset
// 
// 5     8/13/09 7:31a Mallikarjunanv
// eips: 25075, 24971 and hii functions miving from binary to uefi module
// 
// 4     7/31/09 11:45a Blaines
// Add support for non-case sensitive password. 
// 
// 3     7/30/09 7:51a Mallikarjunanv
// updated the code to move the exit page option elinks to Tse Binary
// 
// 2     7/20/09 1:07p Mallikarjunanv
// fixed syntax errors
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 2     4/29/09 9:01p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 10:49p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Commonoem.c
//
// Description:	contains default implementation of TSE hooks
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifdef TSE_FOR_APTIO_4_50

#include "Token.h"
#include <Efi.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/EfiOemBadging.h>
#include <Protocol/AMIPostMgr.h>
#include "AMITSEStrTokens.h"
#include "AMITSEElinks.h"
#include <AmiDxeLib.h>

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
#include "Protocol/AmiKeyCode.h"
#else
#ifndef _AMI_EFI_KEY_DATA_
#define _AMI_EFI_KEY_DATA_
typedef struct {
  EFI_INPUT_KEY  Key;
} AMI_EFI_KEY_DATA;
#endif
#endif

#pragma pack (1)
#ifndef _TSE_EFI_IFR_FORM_SET
#define _TSE_EFI_IFR_FORM_SET
typedef UINT16 EFI_STRING_ID;    //For avoiding build error in EFI 2.0
typedef struct _TSE_EFI_IFR_FORM_SET {
  EFI_IFR_OP_HEADER        Header;
  EFI_GUID                 Guid;
  EFI_STRING_ID            FormSetTitle;
  EFI_STRING_ID            Help;
  UINT8                    Flags;
  EFI_GUID                 ClassGuid[1];
} TSE_EFI_IFR_FORM_SET;
#endif
#pragma pack ()

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
EFI_GUID gAmiEfiKeycodeProtocolGuid = AMI_EFIKEYCODE_PROTOCOL_GUID;
#endif

VOID *
EfiLibAllocateZeroPool (
  IN  UINTN   AllocationSize
  );

#else //#ifdef TSE_FOR_APTIO_4_50

#include "minisetup.h"
#include "AMITSEElinks.h"
#endif //#ifdef TSE_FOR_APTIO_4_50

#ifdef TSE_FOR_APTIO_4_50
// Definitions of keys are different in Alaska and Tiano. So for
// Alaska define Tiano key definitions.

#define CharIsUpper(c) ((c >= L'A') && (c <= L'Z'))
#define CharIsLower(c) ((c >= L'a') && (c <= L'z'))
#define CharIsAlpha(c) (CharIsUpper(c) || CharIsLower(c)) 
#define CharIsNumeric(c) ((c >= L'0') && (c <= L'9'))

#define CHAR_NULL             0x0000
#define CHAR_BACKSPACE        0x0008
#define CHAR_TAB              0x0009
#define CHAR_LINEFEED         0x000A
#define CHAR_CARRIAGE_RETURN  0x000D

#ifndef SCAN_NULL
#define SCAN_NULL       EFI_SCAN_NULL
#endif

#ifndef SCAN_UP
#define SCAN_UP         EFI_SCAN_UP
#endif

#ifndef SCAN_DOWN
#define SCAN_DOWN       EFI_SCAN_DN
#endif

#ifndef SCAN_RIGHT
#define SCAN_RIGHT      EFI_SCAN_RIGHT
#endif

#ifndef SCAN_LEFT
#define SCAN_LEFT       EFI_SCAN_LEFT
#endif

#ifndef SCAN_HOME
#define SCAN_HOME       EFI_SCAN_HOME
#endif

#ifndef SCAN_END
#define SCAN_END        EFI_SCAN_END
#endif

#ifndef SCAN_INSERT
#define SCAN_INSERT     EFI_SCAN_INS
#endif

#ifndef SCAN_DELETE
#define SCAN_DELETE     EFI_SCAN_DEL
#endif

#ifndef SCAN_PAGE_UP
#define SCAN_PAGE_UP    EFI_SCAN_PGUP
#endif

#ifndef SCAN_PAGE_DOWN
#define SCAN_PAGE_DOWN  EFI_SCAN_PGDN
#endif

#ifndef SCAN_F1
#define SCAN_F1         EFI_SCAN_F1
#endif

#ifndef SCAN_F2
#define SCAN_F2         EFI_SCAN_F2
#endif

#ifndef SCAN_F3
#define SCAN_F3         EFI_SCAN_F3
#endif

#ifndef SCAN_F4
#define SCAN_F4         EFI_SCAN_F4
#endif

#ifndef SCAN_F5
#define SCAN_F5         EFI_SCAN_F5
#endif

#ifndef SCAN_F6
#define SCAN_F6         EFI_SCAN_F6
#endif

#ifndef SCAN_F7
#define SCAN_F7         EFI_SCAN_F7
#endif

#ifndef SCAN_F8
#define SCAN_F8         EFI_SCAN_F8
#endif

#ifndef SCAN_F9
#define SCAN_F9         EFI_SCAN_F9
#endif

#ifndef SCAN_F10
#define SCAN_F10        EFI_SCAN_F10
#endif

#ifndef SCAN_F11
#define SCAN_F11        EFI_SCAN_F11
#endif

#ifndef SCAN_F12
#define SCAN_F12        EFI_SCAN_F12
#endif

#ifndef SCAN_ESC
#define SCAN_ESC        EFI_SCAN_ESC
#endif


#endif //#ifdef TSE_FOR_APTIO_4_50
#include "commonoem.h"
#include "LogoLib.h"
#include "Mem.h"
#include "HiiLib.h"
#include "PwdLib.h"
#include "KeyMon.h"
#include "bootflow.h"
#include "variable.h"
#include "TseElinks.h"
#include "AmiVfr.h"
#if MINISETUP_MOUSE_SUPPORT
#include "Include\Protocol\MouseProtocol.h"
extern DXE_MOUSE_PROTOCOL *TSEMouse;
#endif
#include <setupdata.h>
#include <AutoId.h> // for MAIN_MAIN

// Build time file generated from AMITSE_OEM_HEADER_LIST elink.
#include "AmiTseOem.h"		

#ifndef EFI_DEFAULT_BMP_LOGO_GUID
#define EFI_DEFAULT_BMP_LOGO_GUID \
  {0x7BB28B99,0x61BB,0x11d5,0x9A,0x5D,0x00,0x90,0x27,0x3F,0xC1,0x4D}
#endif

typedef struct {
	UINT8 CtrlAction;
	CHAR16 UnicodeChar;
	UINT16 ScanCode;
	UINT32 KeyShiftState;
}	USER_CONTROL_KEY_DATA;

extern PAGE_LIST           *gPages;
extern UINT8         *gApplicationData;
extern PAGE_ID_LIST  *gPageIdList;

typedef struct _HII_FORM_ADDRESS
{
	EFI_GUID formsetGuid; // Required
	UINT16		formId;	// Required
	VOID *		Handle;	// Optional
}HII_FORM_ADDRESS;
#define NULL_GUID \
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
HII_FORM_ADDRESS RootPageList[] = {	AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, NULL}, };
HII_FORM_ADDRESS HiddenPageList[] = { AMITSE_HIDDEN_PAGE_LIST { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, NULL}, };
HII_FORM_ADDRESS RootPageOrder[] = { AMITSE_ROOT_PAGE_ORDER  { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, NULL}, };

EFI_GUID gFormSetClassGuidList[] = {AMITSE_FILTER_CLASSGUID_FORMSETS, NULL_GUID};
EFI_GUID gSuppressDynamicFormsetList[] = { AMITSE_SUPPRESS_DYNAMIC_FORMSET_LIST NULL_GUID };
VAR_DYNAMICPARSING_HANDLESUPPRESS gHandleSuppressVarList [] = {AMITSE_DYNAMICPARSING_HANDLE_SUPPRESS_LIST {NULL_GUID, ""}};

extern BOOLEAN
EfiCompareGuid (
  IN EFI_GUID *Guid1,
  IN EFI_GUID *Guid2
  );


extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE *gST;
extern EFI_RUNTIME_SERVICES *gRT;
extern BOOLEAN gEnterSetup;
extern BOOLEAN gEnterBoot;
extern BOOLEAN gQuietBoot;
extern STYLECOLORS  Colors;
extern VOID StyleOverRideComponent(VOID);
VOID ConfigPostScrollArea(VOID);
extern UINT32 gBootFlow;
extern EFI_GUID _gBootFlowGuid;
extern UINT16 gDbgPrint ;
///Assign the Exit Page options info. from Elink...
EXIT_PAGE_OPTIONS gExitPageOptions[] = {
	EXIT_PAGE_OPTIONS_LIST
};
extern BOOLEAN GifImageFlag;	//flag to denote the gif animation
VOID ContribBGRTTableToAcpi (BOOLEAN);
extern UINT8 gAddBgrtResolutions;
BOOLEAN     CheckforHotKey (AMI_EFI_KEY_DATA);
VOID TSEStringReadLoopEntryHook(VOID);
BOOLEAN TSEMouseIgnoreMouseActionHook(VOID);
VOID StopClickEvent(VOID);
VOID TSEStringReadLoopExitHook(VOID);
VOID MouseStop(VOID);
VOID MouseRefresh(VOID);
VOID SwitchToPostScreenHook(VOID);//EIP-111415 SwitchToPostScreenHook

//EIP81959
#ifndef KEY_STATE_EXPOSED
#define KEY_STATE_EXPOSED   0x40
#endif
static BOOLEAN gPostScreenMsg = FALSE;				//EIP 84199 ProcessConInAvailability needs protection against getting called twice

BOOLEAN gIsRootPageOrderPresent = FALSE;
//UINT16 *gRootPageOrder;
HII_FORM_ADDRESS *gRootPageOrder;
UINT16 gRootPageOrderIndex = 0;
UINTN	CurrentScreenresolutionX, CurrentScreenresolutionY;
extern UINTN gPostStatus; //EIP-140123

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawQuietBootLogo
//
// Description:	This function is the generic implementation of
//              drawing quiet boot logo. This function is available
//              as an ELINK.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetNativeResFromEdid (VOID);
VOID DrawQuietBootLogo(VOID)
{
    EFI_STATUS 	Status;
    BOOLEAN 	LogoToDo = TRUE;
    EFI_OEM_BADGING_PROTOCOL *Badging = NULL;
    UINT32 		Instance = 0;
    EFI_BADGING_FORMAT Format;
    UINT8 		*ImageData = NULL;
    UINTN 		ImageSize = 0;
    EFI_BADGING_DISPLAY_ATTRIBUTE Attribute;
    INTN 		CoordinateX = 0;
    INTN 		CoordinateY = 0;
    EFI_GUID 	LogoFile = EFI_DEFAULT_BMP_LOGO_GUID;
    UINTN 		Width, Height;
    BOOLEAN 	AdjustSize = TRUE;
	UINTN		NoOfHandles = 0;
	EFI_HANDLE 	*Handles;
	UINTN		HandleIndex = 0;
	BOOLEAN		AddBgrtToAcpi = TRUE;

	// Draw the Logo
#if TSE_SUPPORT_NATIVE_RESOLUTION
	SetNativeResFromEdid ();		//EIP94702
#endif
	Status = GetGraphicsBitMapFromFV( &LogoFile, &ImageData, &ImageSize );
	MouseStop ();//EIP 62763 : Stopping the mouse before drawing the Quiet boot logo.
  	if (!EFI_ERROR (Status))
	{
        //No need for initializing CoordinateX and CoordinateY
        //because image will be cenetered and they will be ignored
        //anyways
        Attribute = EfiBadgingDisplayAttributeCenter;
		gAddBgrtResolutions = 1;
        Status = DrawImage( 
                        ImageData,
                        ImageSize,
                        (CO_ORD_ATTRIBUTE)Attribute,
                        CoordinateX,
                        CoordinateY,
                        AdjustSize,
                        &Width,
                        &Height
                        );
        AdjustSize = FALSE;
		if (EFI_SUCCESS != Status)
		{
			AddBgrtToAcpi = FALSE;			//EIP 58954 Not Adding BGRT table to ACPI
		}
        //In case of gif animation not to clear the image data
        if (!GifImageFlag)
	        MemFreePointer((VOID **)&ImageData);
	}

    //Locate Badging protocol Handles
	Status = gBS->LocateHandleBuffer(ByProtocol,&gEfiOEMBadgingProtocolGuid,NULL,&NoOfHandles,&Handles);

	if (!EFI_ERROR (Status))
	{
		if (!gAddBgrtResolutions)		//EIP64402 to support oem logo module. If logo.ffs not present from TSE then this wiil set the gAddBgrtResolutions.
		{
			gAddBgrtResolutions = 1;
		}

		// for each badging protocol
		for(HandleIndex=0; HandleIndex<NoOfHandles;HandleIndex++)
		{
			Badging = NULL;
			Instance = 0;
			gBS->HandleProtocol(Handles[HandleIndex],&gEfiOEMBadgingProtocolGuid,&Badging);
			if(Badging != NULL)
				LogoToDo = TRUE;

		    //Draw all Logo obtained from Badging protocol or FV
			while ( LogoToDo )
		    {
	            Status = Badging->GetImage (
	                            Badging,
	                            &Instance,
	                            &Format,
	                            &ImageData,
	                            &ImageSize,
	                            &Attribute,
	                            &CoordinateX,
	                            &CoordinateY
	                            );
	            if(EFI_ERROR (Status))
	            {
	                LogoToDo = FALSE;
	                break;
	            }
		        Status = DrawImage( 
		                        ImageData,
		                        ImageSize,
		                        (CO_ORD_ATTRIBUTE)Attribute,
		                        CoordinateX,
		                        CoordinateY,
		                        AdjustSize,
		                        &Width,
		                        &Height
		                        );
				if (EFI_SUCCESS != Status)			//EIP 58954 Not Adding BGRT table to ACPI
				{
					AddBgrtToAcpi = FALSE;
				}
		        AdjustSize = FALSE;
		
	        //In case of gif animation not to clear the image data
	        if(!GifImageFlag)
		        MemFreePointer((VOID **)&ImageData);
			}
	  	}
		if(NoOfHandles)
			gBS->FreePool(Handles);
	}
	gAddBgrtResolutions = 0;
	if (TRUE == AddBgrtToAcpi)
	{
		ContribBGRTTableToAcpi (GifImageFlag);
	}
	MouseRefresh();//EIP 62763 : Refreshing the mouse after drawing the Quiet boot logo.
	GetScreenResolution(&CurrentScreenresolutionX, &CurrentScreenresolutionY); //EIP-123535 Getting QuietBoot resolution
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ProcessConInAvailability
//
// Description:	This function is a hook called when TSE determines
//              that console is available. This function is available
//              as ELINK. In the generic implementation boot password
//              is prompted in this function.
//
// Input:		VOID
//
// Output:		BOOLEAN. Should return TRUE if the screen was used to
//              ask password; FALSE if the screen was not used to ask
//              password.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ProcessConInAvailability(VOID)
{
	UINTN NoOfRetries;
	UINT32 PasswordInstalled = AMI_PASSWORD_NONE;
	UINTN Index;
	EFI_INPUT_KEY Key;
	BOOLEAN bScreenUsed = FALSE;
#if SETUP_PRINT_EVAL_MSG || SETUP_PRINT_ENTER_SETUP_MSG
	CHAR16 *text = NULL;
#endif
	if (!gPostScreenMsg)							//EIP 84199 ProcessConInAvailability needs protection against getting called twice
	{
#if SETUP_PRINT_EVAL_MSG
    //Print evaluation message here
    	text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_EVAL_MSG));
    	if ( text != NULL )
			PostManagerDisplayPostMessage(text);
		MemFreePointer( (VOID **)&text );
#endif
#if SETUP_PRINT_ENTER_SETUP_MSG //EIP:40772 - new token to control Setup enter message display
		text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_DEL_ENTER_SETUP) );
		if ( text != NULL )
			PostManagerDisplayPostMessage(text);
		MemFreePointer( (VOID **)&text );
#endif
		gPostScreenMsg = TRUE;
	}
	// if gPasswordType is not AMI_PASSWORD_NONE, Already got the Password.
	// Don't Ask for Password if it is already entered. 
	if ( gPasswordType == AMI_PASSWORD_NONE )
	{	
		PasswordInstalled = PasswordCheckInstalled();
		NoOfRetries = 3;
	
		if(CheckSystemPasswordPolicy(PasswordInstalled))
		{
	        bScreenUsed = TRUE;
	        if(AMI_PASSWORD_NONE == CheckSystemPassword( AMI_PASSWORD_NONE, &NoOfRetries, NULL))
	        {
	            while(1)
	            {
	                //Patch
	                //Ctl-Alt-Del is not recognized by core unless a
	                //ReadKeyStroke is issued
	                gBS->WaitForEvent( 1, &(gST->ConIn->WaitForKey), &Index );
	                gST->ConIn->ReadKeyStroke( gST->ConIn, &Key );
	            }
            }
        }
    }
    return bScreenUsed;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ProcessEnterSetup
//
// Description:	This function is a hook called when TSE determines
//              that SETUP utility has to be displayed. This function
//              is available as ELINK. In the generic implementation
//              setup password is prompted in this function.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProcessEnterSetup(VOID)
{
    UINTN NoOfRetries;
    UINT32 PasswordInstalled = AMI_PASSWORD_NONE;
    UINTN Index;
    EFI_INPUT_KEY Key;

    if ( gPasswordType == AMI_PASSWORD_NONE )
    {

      	PasswordInstalled = PasswordCheckInstalled();

        if ( !( PasswordInstalled & AMI_PASSWORD_ADMIN ) )
        {
            SetPasswordType( AMI_PASSWORD_ADMIN );
        }
        else
        {
            NoOfRetries = 3;

            if(AMI_PASSWORD_NONE == CheckSystemPassword( AMI_PASSWORD_USER, &NoOfRetries, NULL))
            {
                while(1)
                {
                    //Patch
                    //Ctl-Alt-Del is not recognized by core unless a
                    //ReadKeyStroke is issued
                    gBS->WaitForEvent( 1, &(gST->ConIn->WaitForKey), &Index );
                    gST->ConIn->ReadKeyStroke( gST->ConIn, &Key );
                }
            }
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ProcessEnterSetup
//
// Description:	This function is a hook called when TSE determines
//              that it has to load the boot options in the boot
//              order. This function is available as ELINK. In the
//              generic implementation this function is empty. OEM
//              may decide to prompt for boot password in this
//              function.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProcessProceedToBoot(VOID)
{
}

///Control key handling using Elinks...

USER_CONTROL_KEY_DATA	gUserCtrlKeyData[]= { CONTROL_KEY_MAP_LIST };

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetKeySelection
//
// Description: Function to validate the selected key based the key data.
//
// Input:		UserCtrlKeyData: User initialized data for the key 
//					Key: Key provided by SimpleTextIn protocol
//					KeyCodeProtocolSupport: flag to verify KeyShiftState.
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN GetKeySelection(USER_CONTROL_KEY_DATA UserCtrlKeyData, AMI_EFI_KEY_DATA AmiKey, BOOLEAN KeyCodeProtocolSupport)
{
	///EIP-47387: Start
	if (KeyCodeProtocolSupport)
	{ 
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
		/// validate the key including KeyShiftState.
		if ((TSE_CHECK_SHIFTSTATE(AmiKey.KeyState.KeyShiftState, UserCtrlKeyData.KeyShiftState) )&&
			(AmiKey.Key.UnicodeChar == UserCtrlKeyData.UnicodeChar ) && 
			(AmiKey.Key.ScanCode == UserCtrlKeyData.ScanCode ) )
		{
			return 1;
		}
#endif
	}
	/// validate the key without KeyShiftState
	else if( (AmiKey.Key.UnicodeChar == UserCtrlKeyData.UnicodeChar ) && 
		 		(AmiKey.Key.ScanCode == UserCtrlKeyData.ScanCode ) )
	{
		return 1;		
	}
	return 0;	
	///EIP-47387: End
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MapControlKeys
//
// Description:	This function is a hook called inside setup utility
//              to determine the action to be taken for a particular
//              key press. This function is available as ELINK. OEMs
//              may choose to have a different action or a different
//              key. With this function OEMs can change key mappings
//              for the controls in the setup utility. Post hot keys
//              and Setup utility hot keys are out of this functions
//              scope.
//
// Input:		Key: Key provided by SimpleTextIn protocol
//
// Output:		CONTROL_ACTION: enumeration defined in commonoem.h.
//              Input EFI_INPUT_KEY has to mapped to one of the
//              enumerations in CONTROL_ACTION.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CONTROL_ACTION MapControlKeys(AMI_EFI_KEY_DATA key)
{
	UINT8 CtrlCnt=0;
	UINT32 UserCtrlKeyCount=0;
	UserCtrlKeyCount = ( sizeof(gUserCtrlKeyData) / sizeof(USER_CONTROL_KEY_DATA));

///EIP-47387: Start
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
	///To get the selected key data with shiftstate using Keycode protocol. 
	for( CtrlCnt=0; CtrlCnt<UserCtrlKeyCount; CtrlCnt++ )
	{
		if( GetKeySelection (gUserCtrlKeyData[CtrlCnt], key, 1) )		
		{
	        return gUserCtrlKeyData[CtrlCnt].CtrlAction;
		}
	}
#else
    ///To get the selected key data without shiftstate 
	for( CtrlCnt=0; CtrlCnt<UserCtrlKeyCount; CtrlCnt++ )
	{
		if( GetKeySelection (gUserCtrlKeyData[CtrlCnt], key, 0) )		
		{
	        return gUserCtrlKeyData[CtrlCnt].CtrlAction;
		}
	}
#endif    
///EIP-47387: End
	
 	if( CharIsAlpha(key.Key.UnicodeChar) ) 
        return ControlActionAlpha;
	if( CharIsNumeric(key.Key.UnicodeChar) )
        return ControlActionNumeric;

    return ControlActionUnknown;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SupportOSIndication
//
// Description:	Adds OSIndication support
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI	0x0000000000000001
VOID SupportOSIndication (VOID)
{
	EFI_STATUS 	Status = EFI_SUCCESS;
	EFI_GUID 	EfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
	UINT64 		OsIndicationsSupported = EFI_OS_INDICATIONS_BOOT_TO_FW_UI;
	UINT64 		OsIndications = 0;
	UINTN 		DataSize = sizeof (UINT64);
	UINT32 		Attributes = 0;
	UINT32 		BootFlow = BOOT_FLOW_CONDITION_FIRST_BOOT;
	EFI_GUID 	BootFlowGuid = BOOT_FLOW_VARIABLE_GUID;

	Status = pRS->SetVariable (L"OsIndicationsSupported", &EfiGlobalVariableGuid, (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS), DataSize, (VOID *)&OsIndicationsSupported);
	if (!EFI_ERROR (Status))
	{
		DataSize = sizeof (UINT64);
		Status = pRS->GetVariable (L"OsIndications", &EfiGlobalVariableGuid, &Attributes, &DataSize, (VOID *)&OsIndications);
		if (!EFI_ERROR (Status))
		{
			if (OsIndications & EFI_OS_INDICATIONS_BOOT_TO_FW_UI)
			{
				Status = pRS->SetVariable (L"BootFlow", 
								&BootFlowGuid, 
								EFI_VARIABLE_BOOTSERVICE_ACCESS,
								sizeof (BootFlow),
								&BootFlow);
				OsIndications = OsIndications & (~EFI_OS_INDICATIONS_BOOT_TO_FW_UI);
				Status = pRS->SetVariable (L"OsIndications", &EfiGlobalVariableGuid, Attributes, DataSize, (VOID *)&OsIndications);
			}
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MinisetupDriverEntryHook
//
// Description:	This function is a hook called at the end of TSE
//              driver entry. This function is available as ELINK.
//              In the generic implementation TSE installs Key
//              monitoring protocol. OEMs may choose to do additional
//              logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MinisetupDriverEntryHook(VOID)
{
#if TSE_DEBUG_MESSAGES
    EFI_STATUS 	Status;
    EFI_GUID    guidDbgPrint = TSE_DEBUG_MESSAGES_GUID; 
    UINTN dbgVarSize = sizeof(gDbgPrint); 
    UINT16 FeatureBit ;
    
#endif

#if SETUP_SUPPORT_KEY_MONITORING
    InstallKeyMonProtocol();
#endif
	StyleOverRideComponent();
	ConfigPostScrollArea();

#if TSE_DEBUG_MESSAGES
           
    Status = pRS->GetVariable(
		L"TseDebugPrint",
		&guidDbgPrint,
		NULL,
		&dbgVarSize,
		&FeatureBit) ;

    if(!EFI_ERROR( Status ) )
		gDbgPrint = FeatureBit ;
#endif
#if OSIndication_SUPPORT
	SupportOSIndication ();
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PostManagerHandShakeHook
//
// Description:	This function is a hook called at the begining of the
//              PostManagerHandShake protocol function. This function
//              is available as ELINK. In the generic implementation
//              TSE gets keys from key monitor filter. OEMs may choose
//              to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PostManagerHandShakeHook(VOID)
{
#if SETUP_SUPPORT_KEY_MONITORING
    GetKeysFromKeyMonFilter();
#endif
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PrintEnterBBSPopupMessage
//
// Description: Displays STR_ACK_BBS_POPUP message in screen	
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PrintEnterBBSPopupMessage ()
{
    if(gEnterBoot != TRUE) // Print the "Entering Boot" message only once
    {
#if SETUP_PRINT_ENTER_BBSPOPUP_MSG
        CHAR16 *text = NULL;

        //Print Entering Boot Menu here
        text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_ACK_BBS_POPUP) );
        if ( text != NULL )
            PostManagerDisplayPostMessage(text);
        MemFreePointer( (VOID **)&text );
#endif
        gEnterBoot = TRUE;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PrintEnterSetupMessage
//
// Description: Displays STR_ACK_ENTER_SETUP message in screen	
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void PrintEnterSetupMessage()
{
   	if(gEnterSetup != TRUE) // To print the "Entering setup" message only once
	{
#if SETUP_PRINT_ENTER_SETUP_MSG	//EIP:40772 - new token to control Setup enter message display
		CHAR16 *text = NULL;

	        //Print Entering setup here
		text = HiiGetString( gHiiHandle, STRING_TOKEN(STR_ACK_ENTER_SETUP) );
		if ( text != NULL )
				PostManagerDisplayPostMessage(text);
	    		MemFreePointer( (VOID **)&text );
#endif
		gEnterSetup = TRUE;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckandDeactivateSoftkbd
//
// Description:	This function is  called to check and Deactivate the Softkbd
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void CheckandDeactivateSoftkbd()
{
	 if(TSEMouseIgnoreMouseActionHook() == TRUE)
		TSEStringReadLoopExitHook();
}

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
BOOLEAN CheckOEMKey(AMI_EFI_KEY_DATA* AmiKey, UINT16 UnicodeCharSDL, UINT16 ScanCodeSDL,
                EFI_KEY EfiKeySDL, UINT32 ShiftStateSDL, EFI_KEY_TOGGLE_STATE ToggleStateSDL)
{
    BOOLEAN bRet = FALSE;
    BOOLEAN bKeyMatch = FALSE;
    BOOLEAN bShiftStateMatch = FALSE;
    BOOLEAN bToggleStateMatch = FALSE;
    
     if ( ( ((AmiKey->Key.UnicodeChar == UnicodeCharSDL)&&(UnicodeCharSDL != 0))
		|| ((AmiKey->Key.ScanCode == ScanCodeSDL)&&(ScanCodeSDL!=0)) )
        ^((AmiKey->EfiKey == EfiKeySDL)&&(EfiKeySDL != 0)) )    
        bKeyMatch = TRUE;

    //find if the shift key is valid and matching
    /*if (!(ShiftStateSDL & SHIFT_STATE_VALID))//we don't have to check
        bShiftStateMatch = TRUE;*/
    if (AmiKey->KeyState.KeyShiftState & SHIFT_STATE_VALID)
    {
        bShiftStateMatch = CheckAdvShiftState(AmiKey->KeyState.KeyShiftState, ShiftStateSDL);   // EIP85768
       /* if( ((AmiKey->KeyState.KeyShiftState &(~SHIFT_STATE_VALID)) & ShiftStateSDL)
            || ((AmiKey->KeyState.KeyShiftState == SHIFT_STATE_VALID) 
                  && (ShiftStateSDL == SHIFT_STATE_VALID)) )
            bShiftStateMatch = TRUE;*/
    }
    //find if the toggle key is valid and matching
    if (!(ToggleStateSDL & TOGGLE_STATE_VALID))//we don't have to check
        bToggleStateMatch = TRUE; 
    else if (AmiKey->KeyState.KeyToggleState & TOGGLE_STATE_VALID)
    {
        if( ((AmiKey->KeyState.KeyToggleState &(~TOGGLE_STATE_VALID)) & ToggleStateSDL)
            || ((AmiKey->KeyState.KeyToggleState == TOGGLE_STATE_VALID) 
                  && (ToggleStateSDL == TOGGLE_STATE_VALID)) )
            bToggleStateMatch = TRUE;
    }
    
    bRet = (bKeyMatch && bShiftStateMatch && bToggleStateMatch) ? TRUE : FALSE;

    return bRet;   
}
#else
BOOLEAN CheckOEMKey(AMI_EFI_KEY_DATA* AmiKey, UINT16 UnicodeCharSDL, UINT16 ScanCodeSDL)
{
    if ( ( AmiKey->Key.UnicodeChar == UnicodeCharSDL ) 
        && ( AmiKey->Key.ScanCode == ScanCodeSDL ) )
        return TRUE;
    else 
        return FALSE;
}
#endif
typedef BOOLEAN (OEM_KEY_CALLBACK_CHECK_FN) (  CHAR16 UnicodeChar, UINT16 ScanCode, UINT32 ShiftState, OUT VOID **OemKeyCallbackFn );

extern OEM_KEY_CALLBACK_CHECK_FN OEM_KEY_CALLBACK_FN EndOfOemCallbackList;
OEM_KEY_CALLBACK_CHECK_FN * OemKeyCheckFnList[] = {  OEM_KEY_CALLBACK_FN NULL };
extern BOOT_FLOW	*gBootFlowTable;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckOEMKeyCallback
//
// Description:	This function to check OEMKey is consumed by any of the modules that
//				has child elink to OEM_KEY_CALLBACK_LIST. If it wants to handle the key
//				It can return success and callback funciton. The callback function will be 
//				called in Bootflowentry.
//
// Input:		AMI_EFI_KEY_DATA
//
// Output:		BOOLEAN 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckOEMKeyCallback(AMI_EFI_KEY_DATA* AmiKey)
{
	UINT32 ShiftState = 0;
	VOID *CallbackFunction=NULL;
	UINTN i;
	BOOT_FLOW *bootFlowPtr;

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
	ShiftState = AmiKey->KeyState.KeyShiftState;
#endif
	for( i=0;OemKeyCheckFnList[i];i++)
	{
		if(OemKeyCheckFnList[i](AmiKey->Key.UnicodeChar, AmiKey->Key.ScanCode, ShiftState, &CallbackFunction))
		{
			// OEMKey Claimed 
			if(CallbackFunction != NULL)
			{
				bootFlowPtr = gBootFlowTable;
				for ( bootFlowPtr = gBootFlowTable;
					bootFlowPtr->Condition != BOOT_FLOW_CONDITION_NULL; bootFlowPtr++ )
				{
					if(bootFlowPtr->Condition == BOOT_FLOW_CONDITION_OEM_KEY_CALLBACK)
					{
						// Update the OEM Key Callback function.
						bootFlowPtr->CallbackFunction = (BOOT_FLOW_CALLBACK)(UINTN)CallbackFunction;
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckForKey
//
// Description:	This function is a hook called to perform specific
//              action for a POST hot key. This function is called
//              periodically. This function is available as ELINK.
//
// Input:		Event: Timer event.
//              Context: Event context; always NULL
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CheckForKey (EFI_EVENT Event, VOID *Context)
{
	EFI_STATUS Status;
    AMI_EFI_KEY_DATA AmiKey;

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
	AMI_EFI_KEY_DATA KeyFlush;
	EFI_STATUS StatusFlush;
    AMI_EFIKEYCODE_PROTOCOL *pKeyCodeProtocol;

    Status = gBS->HandleProtocol(gST->ConsoleInHandle, &gAmiEfiKeycodeProtocolGuid, (void*)&pKeyCodeProtocol);
        if (EFI_ERROR(Status)) return;
#endif  

	if ( gST->ConIn == NULL )
		return;

    if ( gEnterSetup || gBootFlow )
        return;
	do
	{
#if SETUP_SUPPORT_KEY_MONITORING
        if(gLegacyKeys)
        {
            if(gLegacyKeys & SETUP_ENTRY_KEY_BIT)
                PrintEnterSetupMessage();
#if SETUP_BBS_POPUP_ENABLE
            else if (gLegacyKeys & POPUP_ENTRY_KEY_BIT) {
                PrintEnterBBSPopupMessage ();
                gBootFlow = BOOT_FLOW_CONDITION_BBS_POPUP;
            }
#endif
#if SETUP_OEM_KEY1_ENABLE
            else if (gLegacyKeys & OEM_KEY1_BIT)
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY1;
#endif
#if SETUP_OEM_KEY2_ENABLE
            else if (gLegacyKeys & OEM_KEY2_BIT)
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY2;
#endif
#if SETUP_OEM_KEY3_ENABLE
            else if (gLegacyKeys & OEM_KEY3_BIT)
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY3;
#endif
#if SETUP_OEM_KEY4_ENABLE
            else if (gLegacyKeys & OEM_KEY4_BIT)
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY4;
#endif
         }
#endif
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
		Status = pKeyCodeProtocol->ReadEfikey( pKeyCodeProtocol, &AmiKey );

        // If it Partial Key make the Status as Error to ignore 
        // the Partial Key.
		if((AmiKey.KeyState.KeyToggleState & KEY_STATE_EXPOSED) ==  KEY_STATE_EXPOSED)			//EIP81959 - Ignoring Partial keys
			if( (!EFI_ERROR( Status )) && (AmiKey.Key.ScanCode==0) && (AmiKey.Key.UnicodeChar==0))
				Status = EFI_NOT_READY;

		if ( ! EFI_ERROR( Status ) )
		{
			do
			{
				StatusFlush = pKeyCodeProtocol->ReadEfikey( pKeyCodeProtocol, &KeyFlush );
                // If it Partial Key make the Status as Error to ignore 
                // the Partial Key.
				if((KeyFlush.KeyState.KeyToggleState & KEY_STATE_EXPOSED) ==  KEY_STATE_EXPOSED)			//EIP81959 - Ignoring Partial keys
					if( (!EFI_ERROR( Status )) && (KeyFlush.Key.ScanCode==0) && (KeyFlush.Key.UnicodeChar==0))
						break;
			} while ( ! EFI_ERROR( StatusFlush ) );
	}

#else
         Status = gST->ConIn->ReadKeyStroke( gST->ConIn, &AmiKey.Key );
#endif

		if ( ! EFI_ERROR( Status ))
		{
			if(
				( (SETUP_ENTRY_UNICODE	== AmiKey.Key.UnicodeChar)
				&&(SETUP_ENTRY_SCAN	== AmiKey.Key.ScanCode)
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
				&& (TSE_CHECK_SHIFTSTATE(AmiKey.KeyState.KeyShiftState, SETUP_ENTRY_SHIFT_STATE))
#endif
				)
#if SETUP_ALT_ENTRY_ENABLE 
				|| ( (SETUP_ALT_ENTRY_UNICODE == AmiKey.Key.UnicodeChar)
				&&  (SETUP_ALT_ENTRY_SCAN == AmiKey.Key.ScanCode)
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL				
				&& (TSE_CHECK_SHIFTSTATE(AmiKey.KeyState.KeyShiftState, SETUP_ALT_ENTRY_SHIFT_STATE))
#endif	    
				)
#endif   
	           )

			{
				CheckandDeactivateSoftkbd();// EIP62763 : Check and Deactivate if softkbd present
                PrintEnterSetupMessage();
			}
#if SETUP_BBS_POPUP_ENABLE
	        else if ( (AmiKey.Key.UnicodeChar == POPUP_MENU_ENTRY_UNICODE) 
             && (AmiKey.Key.ScanCode == POPUP_MENU_ENTRY_SCAN)
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
#ifdef POPUP_MENU_ENTRY_SHIFT_STATE
			 && (TSE_CHECK_SHIFTSTATE (AmiKey.KeyState.KeyShiftState, POPUP_MENU_ENTRY_SHIFT_STATE))
#endif
#endif
			)
			{
				CheckandDeactivateSoftkbd();// EIP62763 : Check and Deactivate if softkbd present
				PrintEnterBBSPopupMessage ();
				gBootFlow = BOOT_FLOW_CONDITION_BBS_POPUP;
			}
#endif
#if EFI_SPECIFICATION_VERSION>0x20000
	        else if (CheckforHotKey (AmiKey))       //EIP: 62631 checking for hot boot keys
            {
                gBootFlow = BOOT_FLOW_HOTKEY_BOOT;
            } 
#endif

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
#if SETUP_OEM_KEY1_ENABLE
			else if (CheckOEMKey(&AmiKey, SETUP_OEM_KEY1_UNICODE, SETUP_OEM_KEY1_SCAN,
                     SETUP_OEM_KEY1_EFIKEY, SETUP_OEM_KEY1_SHIFT, SETUP_OEM_KEY1_TOGGLE))
   				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY1;
#endif

#if SETUP_OEM_KEY2_ENABLE
			else if (CheckOEMKey(&AmiKey, SETUP_OEM_KEY2_UNICODE, SETUP_OEM_KEY2_SCAN,
                     SETUP_OEM_KEY2_EFIKEY, SETUP_OEM_KEY2_SHIFT, SETUP_OEM_KEY2_TOGGLE))
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY2;
#endif

#if SETUP_OEM_KEY3_ENABLE
			else if (CheckOEMKey(&AmiKey, SETUP_OEM_KEY3_UNICODE, SETUP_OEM_KEY3_SCAN,
                     SETUP_OEM_KEY3_EFIKEY, SETUP_OEM_KEY3_SHIFT, SETUP_OEM_KEY3_TOGGLE))
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY3;
#endif

#if SETUP_OEM_KEY4_ENABLE
			else if (CheckOEMKey(&AmiKey, SETUP_OEM_KEY4_UNICODE, SETUP_OEM_KEY4_SCAN,
                     SETUP_OEM_KEY4_EFIKEY, SETUP_OEM_KEY4_SHIFT, SETUP_OEM_KEY4_TOGGLE))
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY4;
#endif

#else // if no TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
#if SETUP_OEM_KEY1_ENABLE
			else if (CheckOEMKey(&AmiKey, SETUP_OEM_KEY1_UNICODE, SETUP_OEM_KEY1_SCAN))
    				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY1;
#endif

#if SETUP_OEM_KEY2_ENABLE
			else if (CheckOEMKey(&AmiKey, SETUP_OEM_KEY2_UNICODE, SETUP_OEM_KEY2_SCAN))
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY2;
#endif

#if SETUP_OEM_KEY3_ENABLE 
			else if (CheckOEMKey(&AmiKey, SETUP_OEM_KEY3_UNICODE, SETUP_OEM_KEY3_SCAN))
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY3;
#endif

#if SETUP_OEM_KEY4_ENABLE
			else if (CheckOEMKey(&AmiKey, SETUP_OEM_KEY4_UNICODE, SETUP_OEM_KEY4_SCAN))
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY4;
#endif
#endif
			else if (CheckOEMKeyCallback(&AmiKey) )
				gBootFlow = BOOT_FLOW_CONDITION_OEM_KEY_CALLBACK;
#ifndef STANDALONE_APPLICATION
			else if ( ( AmiKey.Key.UnicodeChar == SETUP_TOGGLE_KEY_UNICODE ) 
                && ( AmiKey.Key.ScanCode == SETUP_TOGGLE_KEY_SCANCODE) )
			{
				if ( gQuietBoot )
				{
					gQuietBoot = FALSE;
					MouseStop();//EIP 62763 : Stopping the mouse before cleanuplogo when TAB key pressed
					CleanUpLogo();
					SwitchToPostScreenHook();//EIP-111415 SwitchToPostScreenHook
					InitPostScreen();
				}
			}
#endif
		}
	} while ( ! EFI_ERROR( Status ) );


}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckForClick
//
// Description:	This function is a hook called to perform specific
//              action for a POST hot key. This function is called
//              periodically. This function is available as ELINK.
//
// Input:		Event: Timer event.
//              Context: Event context; always NULL
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CheckForClick (EFI_EVENT Event, VOID *Context)
{
#if MINISETUP_MOUSE_SUPPORT
	INT32 Button_Status=0;
	
	if(TSEMouseIgnoreMouseActionHook())
	{
		return;// EIP62763 : Check for softkbd, if present return
	}
     if(TSEMouse!=NULL)
     {
	    TSEMouse->MousePoll(TSEMouse);
	  	TSEMouse->GetButtonStatus(TSEMouse,&Button_Status);

		if (TSE_POST_STATUS_PROCEED_TO_BOOT == gPostStatus) ////EIP-140123 To StopclickEvent andd avoid displaying softkbd when Proceed_To_Boot
			StopClickEvent();

		if(((Button_Status == TSEMOUSE_RIGHT_CLICK)||(Button_Status == TSEMOUSE_LEFT_DCLICK)||(Button_Status == TSEMOUSE_LEFT_CLICK))&&(!TSEMouseIgnoreMouseActionHook()))
		{
			TSEStringReadLoopEntryHook();
			StopClickEvent();
		}

     }
#endif

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BeforeLegacyBootLaunch
//
// Description:	This function is a hook called before launching
//              legacy boot option. This function is available as
//              ELINK. In the generic implementation this function is
//              empty. OEMs may choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BeforeLegacyBootLaunch(VOID)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AfterLegacyBootLaunch
//
// Description:	This function is a hook called after launching
//              legacy boot option. This function is available as
//              ELINK. In the generic implementation this function is
//              empty. OEMs may choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AfterLegacyBootLaunch(VOID)
{
}
VOID MouseDestroy(VOID);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BeforeEfiBootLaunch
//
// Description:	This function is a hook called before launching EFI
//              boot option. This function is available as ELINK. In
//              the generic implementation this function is empty.
//              OEMs may choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID BeforeEfiBootLaunch(VOID)
{
	StopClickEvent();//EIP 86253 : Mouse and SoftKbd does not work after displaying "No option to boot to" in POST
	MouseDestroy();

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AfterEfiBootLaunch
//
// Description:	This function is a hook called after launching EFI
//              boot option. This function is available as ELINK. In
//              the generic implementation this function is empty.
//              OEMs may choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AfterEfiBootLaunch(VOID)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SavedConfigChanges
//
// Description:	This function is a hook called after setup utility
//              saves changes based on user input. This function is
//              available as ELINK. In the generic implementation
//              this function is empty. OEMs may choose to do
//              additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SavedConfigChanges(VOID)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadedConfigDefaults
//
// Description:	This function is a hook called after setup utility
//              loaded config defaults based on user input. This
//              function is available as ELINK. In the generic
//              implementation this function is empty. OEMs may
//              choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadedConfigDefaults(VOID)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TimeOutLoopHook
//
// Description:	This function is a hook called in every iteration
//              (not every second) while TSE is waiting for POST time
//              out. This function is available as ELINK. In the generic
//              implementation this function is empty. OEMs may
//              choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TimeOutLoopHook(VOID)
{
}

VOID HiiGetEfiKey(CHAR16 *PwKey);
///////////////////////////////////////////////////////////////////
////////PasswordEncode moved to PasswordEncode module//////////////
///////////////////////////////////////////////////////////////////

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetControlColors
//
// Description:	This function is a hook called when colour of a
//              control has to be decided. This function is available
//              as ELINK. OEMs may choose to use different colour
//              combination.
//
// Input:		BGColor: Back ground colour
//              FGColor: Fore ground colour
//              SecBGColor: Secondary back ground colour used for
//              time, date and menu
//              SecFGColor: Secondary fore ground colour used for
//              time, date and menu
//              SelBGColor: Selected back ground colour
//              SelFGColor: Selected fore ground colour
//              NSelBGColor: Not selected back ground colour
//              NSelFGColor: Not selected fore ground colour
//              LabelBGColor: Label back ground colour
//              LabelFGColor: Label fore ground colour
//              NSelLabelFGColor: Not selected label fore ground
//              EditBGColor: Edit box back ground
//              EditFGColor: Edit box fore ground
//              PopupFGColor: Popup fore ground
//              PopupBGColor: Popup back ground
//
// Output:		EFI_STATUS: always EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetControlColors(UINT8 *BGColor, UINT8 *FGColor, UINT8 *SecBGColor, UINT8 *SecFGColor, 
								 UINT8 *SelBGColor, UINT8 *SelFGColor, UINT8 *NSelBGColor, UINT8 *NSelFGColor,
								 UINT8 *LabelBGColor, UINT8 *LabelFGColor,UINT8 *NSelLabelFGColor, UINT8 *EditBGColor, UINT8 *EditFGColor,
								 UINT8 *PopupFGColor, UINT8 *PopupBGColor)
{
	if(FGColor !=NULL)	*FGColor = Colors.FGColor ;
	if(BGColor !=NULL)	*BGColor = Colors.BGColor ;	

	if(SecFGColor !=NULL)	*SecFGColor = Colors.SecFGColor ;
	if(SecBGColor !=NULL)	*SecBGColor = Colors.SecBGColor ;	

	if(SelFGColor !=NULL)	*SelFGColor = Colors.SelFGColor ;
	if(SelBGColor !=NULL) 	*SelBGColor = Colors.SelBGColor ;

	if(NSelFGColor !=NULL)	*NSelFGColor = Colors.NSelFGColor ;
	if(NSelBGColor !=NULL) 	*NSelBGColor = Colors.NSelBGColor ;

	if(LabelFGColor !=NULL)	*LabelFGColor = Colors.LabelFGColor ;
	if(LabelBGColor !=NULL)	*LabelBGColor = Colors.LabelBGColor ;
	
	if(NSelLabelFGColor !=NULL)	*NSelLabelFGColor = Colors.NSelLabelFGColor ;

	if(EditFGColor !=NULL)	*EditFGColor = Colors.EditFGColor ;
	if(EditBGColor !=NULL)	*EditBGColor = Colors.EditBGColor ;

	if(PopupFGColor !=NULL)	*PopupFGColor = Colors.PopupFGColor ;
	if(PopupBGColor !=NULL)	*PopupBGColor = Colors.PopupBGColor ;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InvalidActionHook
//
// Description:	This function is the hook call the appropriate InvalidActions function.
//				OEMs may choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InvalidActionHook(VOID)
{
	/// Call the Invalid action function (Ex: Beep )
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadedUserDefaults
//
// Description:	This function is a hook called after setup utility
//              loaded user defaults based on user input. This
//              function is available as ELINK. In the generic
//              implementation this function is empty. OEMs may
//              choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadedUserDefaults(VOID)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadedBuildDefaults
//
// Description:	This function is a hook called after setup utility
//              loaded Oem defaults based on user input. This
//              function is available as ELINK. In the generic
//              implementation this function is empty. OEMs may
//              choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadedBuildDefaults(VOID)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadedPreviousValues
//
// Description:	This function is a hook called after setup utility
//              loaded previously saved values based on user input. This
//              function is available as ELINK. In the generic
//              implementation this function is empty. OEMs may
//              choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LoadedPreviousValues(VOID)
{
	//UpdateControlStatus(TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetupConfigModified
//
// Description:	This function is a hook called after some control 
//				modified in the setup utility by user. This
//              function is available as ELINK. In the generic
//              implementation this function is empty. OEMs may
//              choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetupConfigModified(VOID)
{
	//UpdateControlStatus(TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadSetupDefaults
//
// Description:	This function is a hook called when user loads the manufacturing
//              or optimal defaults. This function is
//              available as ELINK. OEMs may override the function and  
//              decide the policy.
//
// Input:		defaults : (NVRAM_VARIABLE *)optimal or manufacturing
//              data : Messagebox
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _LoadDefaults( NVRAM_VARIABLE *defaults, UINTN data );
VOID LoadSetupDefaults (VOID *defaults, UINTN data )
{

	_LoadDefaults((NVRAM_VARIABLE *)defaults, data );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetupConfigModified
//
// Description:	This function is a hook called after some control 
//				modified in the setup utility by user. This
//              function is available as ELINK. In the generic
//              implementation this function is empty. OEMs may
//              choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PreSystemResetHook(VOID)
{
	///to have the oem customizations just before resetting
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OemKey1Hook
//
// Description:	This function is a hook called when user activates
//              configurable post hot key 1. This function is
//              available as ELINK. Generic implementation is empty.
//              OEMs may choose to use different logic here.
//
// Input:		bootFlowPtr: Boot flow entry that triggered this call
//
// Output:		always EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS	OemKey1Hook ( BOOT_FLOW *bootFlowPtr )
{
	EFI_STATUS Status = EFI_SUCCESS;
	//
	// Add code here on enabling SETUP_OEM_KEY1_ENABLE for callback

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OemKey2Hook
//
// Description:	This function is a hook called when user activates
//              configurable post hot key 2. This function is
//              available as ELINK. Generic implementation is empty.
//              OEMs may choose to use different logic here.
//
// Input:		bootFlowPtr: Boot flow entry that triggered this call
//
// Output:		always EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS	OemKey2Hook ( BOOT_FLOW *bootFlowPtr )
{
	EFI_STATUS Status = EFI_SUCCESS;
	//
	// Add code here on enabling SETUP_OEM_KEY2_ENABLE for callback

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OemKey3Hook
//
// Description:	This function is a hook called when user activates
//              configurable post hot key 3. This function is
//              available as ELINK. Generic implementation is empty.
//              OEMs may choose to use different logic here.
//
// Input:		bootFlowPtr: Boot flow entry that triggered this call
//
// Output:		always EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS	OemKey3Hook ( BOOT_FLOW *bootFlowPtr )
{
	EFI_STATUS Status = EFI_SUCCESS;
	//
	// Add code here on enabling SETUP_OEM_KEY3_ENABLE for callback

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OemKey4Hook
//
// Description:	This function is a hook called when user activates
//              configurable post hot key 4. This function is
//              available as ELINK. Generic implementation is empty.
//              OEMs may choose to use different logic here.
//
// Input:		bootFlowPtr: Boot flow entry that triggered this call
//
// Output:		always EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS	OemKey4Hook ( BOOT_FLOW *bootFlowPtr )
{
	EFI_STATUS Status = EFI_SUCCESS;
	//
	// Add code here on enabling SETUP_OEM_KEY4_ENABLE for callback

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MapControlMouseAction
//
// Description:	This function is a hook called inside setup utility
//              to determine the action to be taken for a particular
//              Mouse Click. This function is available as ELINK. OEMs
//              may choose to have a different action or a different
//              mouse click. 
//
// Input:		MOUSE_INFO *pMouseInfo
//
// Output:		CONTROL_ACTION: enumeration defined in commonoem.h.
//              Input EFI_INPUT_KEY has to mapped to one of the
//              enumerations in CONTROL_ACTION.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CONTROL_ACTION MapControlMouseAction(MOUSE_INFO *pMouseInfo)
{
	if(pMouseInfo!=NULL)
	{
	    if(TSEMOUSE_RIGHT_CLICK == pMouseInfo->ButtonStatus)
			return ControlActionAbort;
#if SINGLE_CLICK_ACTIVATION			//EIP74141 providing select option for single click too
		if(TSEMOUSE_LEFT_DCLICK == pMouseInfo->ButtonStatus || TSEMOUSE_LEFT_CLICK == pMouseInfo->ButtonStatus)
			return ControlActionSelect;
#else
		if(TSEMOUSE_LEFT_CLICK == pMouseInfo->ButtonStatus)
			return ControlActionChoose;

		if(TSEMOUSE_LEFT_DCLICK == pMouseInfo->ButtonStatus)
			return ControlActionSelect;
#endif
		if(TSEMOUSE_LEFT_DOWN == pMouseInfo->ButtonStatus)		//EIP74968
			return ControlMouseActionLeftDown;

		if(TSEMOUSE_LEFT_UP == pMouseInfo->ButtonStatus)		//EIP74968
			return ControlMouseActionLeftUp;

	}
    return ControlActionUnknown;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ProcessProceedToBootNow
//
// Description:	This function is a hook called when Boots from 
//				BBS popup or Bootoverride page. 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProcessProceedToBootNow(VOID)
{
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ProcessConOutAvailable
//
// Description:	This function is a hook called when TSE determines
//              that console out is available. This function is available
//              as ELINK. 
//
// Input:		VOID
//
// Output:		VOID	
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProcessConOutAvailable(VOID)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FixSubPageAsRootPageList
//
// Description:	This function Fixes the SubPage as root pages from
//				AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FixSubPageAsRootPageList()
{
	UINTN RootPageListCount = sizeof(RootPageList) / sizeof (HII_FORM_ADDRESS);
	UINTN i,j;
	PAGE_INFO *info;
	PAGE_ID_INFO *pageIdInfo;
	// Support to Handle some child pages as root pages.
	for(j=0; j<RootPageListCount;j++)
	{
	    for ( i = 0; i < (UINTN)gPages->PageCount; i++ ) // EIP118410
		{
			info = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[i]);

			// To Make Page as root
			if( info->PageFormID == RootPageList[j].formId)
			{
				// If Handle is not null compare. If it null Ignore
				if(RootPageList[j].Handle != NULL)
				{
					if(info->PageHandle != RootPageList[j].Handle)
						continue;
				}
				pageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[info->PageIdIndex]);

				if( EfiCompareGuid(&pageIdInfo->PageGuid,&RootPageList[j].formsetGuid) )//Compare Guid
					info->PageParentID =0;
			}
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FixSubPageAsRootPageList
//
// Description:	This function Fixes the Hides pages from
//				AMITSE_HIDDEN_PAGE_LIST
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FixHiddenPageList(VOID)
{
	UINTN HiddenPageListCount = sizeof(HiddenPageList) / sizeof (HII_FORM_ADDRESS);
	UINTN i,j;
	PAGE_INFO *info;
	PAGE_ID_INFO *pageIdInfo;
	// To Hide Pages
	for(j=0; j<HiddenPageListCount;j++)
	{
		for ( i = 0; i < (UINTN)gPages->PageCount; i++ ) // EIP118410
		{
			info = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[i]);

			if( info->PageFormID == HiddenPageList[j].formId)
			{
				// If Handle is not null compare. If it null Ignore
				if(RootPageList[j].Handle != NULL)
				{
					if(info->PageHandle != HiddenPageList[j].Handle)
						continue;
				}
				pageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[info->PageIdIndex]);

				if( EfiCompareGuid(&pageIdInfo->PageGuid,&HiddenPageList[j].formsetGuid) )//Compare Guid
				{
                   info->PageFlags.PageVisible = TRUE;
                   /* This is needed as the PageDynamic is true if the IFR page  is added dynamically. Then it will be shown under Dynamic pages. By making PageDynamic as FALSE we can make sure it is not shown anywere. */
                   info->PageFlags.PageDynamic = FALSE;
				}
			}
		}
	}
}

VOID TseUpdateRootPageOrder(VOID);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ProcessUIInitHook
//
// Description:	This function is a hook called just before creating
//						the setup application for oem customizations. This function is
// 					available as ELINK. OEMs may choose to do additional logic here. 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProcessUIInitHook(VOID)
{
	CheckandDeactivateSoftkbd ();		//EIP82552 Deactivating softkbd when time out occurs in post and enters into setup
#if AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST_SUPPORT
	FixSubPageAsRootPageList ();
#endif
#if AMITSE_HIDE_ROOT_PAGE
	FixHiddenPageList ();
#endif
	TseUpdateRootPageOrder();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	AfterInitPostScreen
//
// Description:	This function is a hook called After post screen is initilzed.
//      This function is available as ELINK. In the generic implementation this function
//		is empty. OEMs may choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AfterInitPostScreen(VOID)
{

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TseUpdateRootPageOrder
//
// Description:	This function is to update the Root page order from the specified elink.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TseUpdateRootPageOrder(VOID)
{

#if AMITSE_ROOT_PAGE_ORDER_SUPPORT

	UINTN RootPageOrderCount = sizeof(RootPageOrder) / sizeof (HII_FORM_ADDRESS);
	UINTN j,k;
	EFI_GUID gSetupPageOrderGuid = SETUP_ROOT_PAGE_ORDER_GUID, NullGuid = NULL_GUID;
	UINT32 *currentBootFlow;
	UINTN size = 0;
	UINT32 BootFlow = BOOT_FLOW_CONDITION_NORMAL;

	//EIP166682 gBootFlow is changing constantly so better get it from NVRAM and proceed
	currentBootFlow = VarGetNvramName( L"BootFlow", &_gBootFlowGuid, NULL, &size );
	if (NULL != currentBootFlow)
	{
		BootFlow = *currentBootFlow;
		MemFreePointer ((VOID **)&currentBootFlow);
	}

	if((1 == RootPageOrderCount)&&(EfiCompareGuid(&NullGuid,&RootPageOrder[0].formsetGuid)))
		return;

	if(gRootPageOrder!=NULL)
		return;

	gRootPageOrder = EfiLibAllocateZeroPool (RootPageOrderCount * sizeof (HII_FORM_ADDRESS));
	if (NULL == gRootPageOrder)
		return;
	// To Hide Pages
	for(j=0; j<RootPageOrderCount;j++)
	{
		if((EfiCompareGuid(&gSetupPageOrderGuid,&RootPageOrder[j].formsetGuid))&&(RootPageOrder[j].formId == BootFlow))
		{
			k = j + 1;
			while(!((EfiCompareGuid(&gSetupPageOrderGuid,&RootPageOrder[k].formsetGuid)) || (EfiCompareGuid(&NullGuid,&RootPageOrder[k].formsetGuid))))
			{
				gBS->CopyMem (&gRootPageOrder[gRootPageOrderIndex], &RootPageOrder[k], sizeof (HII_FORM_ADDRESS));
				gRootPageOrderIndex ++;
				gIsRootPageOrderPresent = TRUE;
				k ++;
			}
			break;
		}
	}

	//EIP166682 If root page ordering is not found for any bootflow then trying for BOOT_FLOW_CONDITION_NORMAL bootflow. Helpful for BOOT_FLOW_CONDITION_OEM_KEY1 etc.,,
	if ( (FALSE == gIsRootPageOrderPresent) && (BOOT_FLOW_CONDITION_NORMAL != BootFlow) )
	{
		for(j=0; j<RootPageOrderCount;j++)
		{
			if ( (EfiCompareGuid (&gSetupPageOrderGuid,&RootPageOrder[j].formsetGuid)) && (RootPageOrder[j].formId == BOOT_FLOW_CONDITION_NORMAL) )
			{
				k=++j;
				while (!( (EfiCompareGuid (&gSetupPageOrderGuid,&RootPageOrder[k].formsetGuid)) || (EfiCompareGuid(&NullGuid,&RootPageOrder[k].formsetGuid)) ) )
				{
					gBS->CopyMem (&gRootPageOrder[gRootPageOrderIndex], &RootPageOrder[k], sizeof (HII_FORM_ADDRESS));
					gRootPageOrderIndex ++;
					gIsRootPageOrderPresent = TRUE;
					k ++;
				}
				break;
			}
		}
	}
#endif
}
//EIP-111415 SwitchToPostScreenHook Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SwitchToPostScreen
//
// Description:	This function is a hook called during SwitchToPostScreen post.
//      				This function is available as ELINK. In the generic implementation this function
//						is empty. OEMs may choose to do additional logic here.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SwitchToPostScreen(VOID)
{

}
//EIP-111415 SwitchToPostScreenHook Ends

//EIP-139099 Start
//<AMI_PHDR_START>
//---------------------------------------------------------------------------------------------
// Procedure:		IsHideFormsetsWithClassGuid
//
// Description:	This function filter formset and display formset based on ClassGUID mentioned in elink AMITSE_FILTER_CLASSGUID_FORMSETS 
//
// Input:			EFI_IFR_FORMSET. Formset to compare with elink classGuid.
//
// Output:			BOOLEAN. Return TRUE formset matches with elink ClassGuid else FALSE
//
//---------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ShowClassGuidFormsets (TSE_EFI_IFR_FORM_SET *FormSet )
{
#if SHOW_FORMSETS_WITH_CLASSGUID
	UINT16 FilterListcount = sizeof(gFormSetClassGuidList) / sizeof (EFI_GUID);
	UINT16 index = 0;

	if (FormSet->ClassGuid)
	{
		for (index = 0; index < (FilterListcount-1); index++)//(FilterListcount-1) To avoid check with NULL guid
		{
			if ( EfiCompareGuid ( FormSet->ClassGuid, &gFormSetClassGuidList[index])  )
				return TRUE;
		}
		return FALSE;
	}
#endif
	return TRUE;//if token is disable
}
//EIP-139099 End

//EIP-95647 Start
//<AMI_PHDR_START>
//---------------------------------------------------------------------------------------------
// Procedure:		HideDynamicFormsets
//
// Description:		This function suppress dynamic formset mentioned in the elink AMITSE_SUPPRESS_DYNAMIC_FORMSET_LIST
//
// Input:			GUID. Formset guid to compare with gSuppressDynamicFormsetList elink guids.
//
// Output:			BOOLEAN. Return TRUE if any guid matches with gSuppressDynamicFormsetList elink else FALSE
//
//---------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN HideDynamicFormsets (EFI_GUID *FormSetGuid )
{
#if AMITSE_SUPPRESS_DYNAMIC_FORMSET
	UINTN suppressDynamicFormsetListCount = sizeof(gSuppressDynamicFormsetList) / sizeof (EFI_GUID);
	UINT16 index = 0;

	if (FormSetGuid)
	{
		for (index = 0; index < (suppressDynamicFormsetListCount-1); index++)
		{
			if ( EfiCompareGuid ( FormSetGuid, &gSuppressDynamicFormsetList[index])  )
				return TRUE;
		}
	}
#endif
	return FALSE;
}
//EIP-95647 End

//<AMI_PHDR_START>
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Procedure:		VariableHandleSuppressed
//
// Description:	This function informs to match the handle or not for creating new variable using VAR_DYNAMICPARSING_HANDLESUPPRESS_LIST ELink
//
// Input:			EFI_GUID *, CHAR16	*
//
// Output:			BOOLEAN. Return TRUE handle matches with elink else FALSE
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* StrDup16to8(CHAR16 *String);
INTN EfiStrCmp (IN CHAR16   *String, IN CHAR16   *String2);
BOOLEAN VariableHandleSuppressed (EFI_GUID *VariableGuid, CHAR16	*VariableName)
{
#if SUPPRESS_HANDLE_FOR_VAR_CREATION	
	UINTN HandleSuppressListCount = sizeof (gHandleSuppressVarList)/sizeof (VAR_DYNAMICPARSING_HANDLESUPPRESS);
	UINTN i = 0;
	CHAR8 *VariableNameStr8 = (CHAR8 *)NULL;
	
	VariableNameStr8 = StrDup16to8 (VariableName);
	if (NULL == VariableNameStr8)
	{
		return FALSE;
	}
	for(i=0; i < HandleSuppressListCount; i++)
	{
		if ( (EfiCompareGuid(VariableGuid, &(gHandleSuppressVarList [i].VariableGuid))) && (Strcmp (VariableNameStr8, gHandleSuppressVarList [i].VariableName) ==0) )
		{
			return TRUE;
		}
	}
#endif	
	return FALSE;
}

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
