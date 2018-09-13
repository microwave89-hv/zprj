//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/minisetup.h $
//
// $Author: Premkumara $
//
// $Revision: 49 $
//
// $Date: 8/28/14 5:43a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/minisetup.h $
// 
// 49    8/28/14 5:43a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 48    2/11/14 7:56p Arunsb
// [TAG]	EIP125719
// [Category]	Improvement
// [Description]	The EfiCreateEventReadyToBoot is conflicted under
// UefiLib.h and EDKhelper.h.
// [Files]	boot.c
// 
// 47    10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 37    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 45    5/29/12 4:31a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 44    5/28/12 5:39a Premkumara
// [TAG]  		EIP75236
// [Category]  	Improvement
// [Description]  	Add the support to control the GOP dependency in TSE
// notification.
// [Files]  		AMITSE.sdl, CommonHelper.c, Notify.c, Minisetup.h,
// Minisetup.sdl, protocol.c, FormBrowser.c, FormBrowser2.c
// 
// 43    1/10/12 2:36a Arunsb
// [TAG]  		EIP77400
// [Category]  	Improvement
// [Description]  	Need to do "Clear Screen" whenever boot to EFI Shell
// [Files]  		Boot.c and minisetup.h
// 
// 42    12/08/11 12:34p Arunsb
// [TAG]  		EIP63190
// [Category]  	New Feature
// [Description]  	Security operations in BootOnly module instead of
// TSELite
// 
// 41    12/05/11 5:48a Rajashakerg
// [TAG]  		EIP76381 
// [Category]  	Improvement
// [Description]  	Performance: Improving variable data load and usage
// [Files]  		callback.c, minisetupext.c, variable.c, variable.h,
// minisetup.h, Hii.c, FormBrowser2.c
// 
// 40    12/01/11 5:36a Rajashakerg
// [TAG]  		EIP74963 
// [Category]  	Improvement
// [Description]  	MAX_MSGBOX_WIDTH cannot be overridden
// [Files]  		AMITSE.sdl, CommonHelper.c, minisetup.h, legacy.c,
// MessageBox.c, MessageBox.h, FormBrowser.c
// 
// 39    12/01/11 4:58a Arunsb
// // [TAG]  		EIP70175
// // [Category]  	Improvement
// // [Description]  	Removed unwanted declarations
// // [Files]  	                CommonHelper.c, postmgmtext.c
// 
// 38    11/21/11 10:44a Premkumara
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
// 37    11/21/11 5:47a Rajashakerg
// [TAG]  		EIP74591 
// [Category]  	Improvement
// [Description]  	Make MainSetupLoop as board module hook
// [Files]  		AMITSE.sdl, CommonHelper.c, protocol.c, minisetup.h,
// FormBrowser.c, FormBrowser2.c
// 
// 36    11/20/11 8:10a Premkumara
// [TAG]  		EIP70175
// [Category]  	Improvement
// [Description]  	Color of PopupPassword Window to validate password in
// GTSE style
// [Files]  	CommonHelper.c, postmgmtext.c, minisetup.h
// 
// 35    11/20/11 7:09a Rajashakerg
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
// 34    11/14/11 2:43p Blaines
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
// 33    11/13/11 12:32p Arunsb
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
// 32    10/31/11 9:45a Rajashakerg
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
// 31    7/19/11 10:50a Blaines
// [TAG] - EIP 63262
// [Category]- Defect
// [Symptom]- Setup page display problem on rose city.
// When SETUP_GROUP_DYNAMIC_PAGES is enabled and Network Stack is enabled,
// the "iSCSI" menu is listed as a dynamic page in advanced menu but only
// 3 of 4 "Port Configuration" pages shows up. The TSE dynamic page count
// is incorrect.
// 
// [Solution]- In the functions (RTIfrProcessRunTimeForms,
// HandleNewIFRPack, HandleRemoveIFRPack, HandleAddIFRPack), make sure the
// nvram cache is updated by calling
// VarUpdateVariable(VARIABLE_ID_DYNAMIC_PAGE_COUNT) when updating
// "DynamicPageCount" variable name. 
// .
// [Files] -  Hii.c, Minisetup.h, Variable.h
// 
// 30    7/01/11 5:19a Arunsb
// Driver health related declaration moved to tsedrvhealth.h.
// 
// 29    6/30/11 5:05a Premkumara
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Resolve Build error with Driver Health protocol
// 
// 28    6/30/11 4:14a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 2.0 & 2.1 compatibility added
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 27    6/29/11 12:19p Rajashakerg
// [TAG]  		EIP47086, 62098 
// [Category]  	New Feature
// [Description]  	Right clicking from the Main page is not exiting from
// BIOS setup and the Mouse hotclicks.
// [Files]  		minisetup.h, Ezport\style.h,Ezport\EzportBin.sdl,
// Ezport\EzportBin.mak, Ezport\ezport.c, Ezport\EzportBin.cif,
// EzportPlus\style.h, EzportPlus\EzportPlusBin.sdl, EzportPlusBin.mak,
// EzportPlus\EzportPlusBin.cif, EzportPlus\ezportplus.c, Legacy\style.h,
// Legacy\EzportPlusBin.sdl, Legacy\LegacyBin.mak, Legacy\LegacyBin.cif,
// Legacy\legacy.c, TseLiteBin.sdl, TseLite.cif, Memo.c, frame.c,
// application.h, application.c, commonoem.h, CommonHelper.c
// 
// 26    6/23/11 4:06p Rajashakerg
// [TAG]  		EIP55762, 58925, 59971
// [Category]  	New Feature
// [Description]  	Support REF2,REF3 and REF4 in AMITSE
// Support direct form navigation path
// Improper layout of controls in the root page when Dynamic pages are
// added using the Legacy Setup Style	
// 
// [Files]  		setupdata.h, CommonHelper.c, AMITSE.sdl, Legacy\Legacy.c,
// Legacy\style.h, Legacy\style.h, frame.c, minisetupext.c,
// minisetupext.h, numeric.c, page.c Popupstring.c, Hii.c,
// Uefi21Wrapper.c, Parse.c Hii.c
// 
// 25    6/20/11 11:46a Rajashakerg
// [TAG]  		EIP59417
// [Category]  	New Feature
// [Description]  	Spport LOAD_OPTION_HIDDEN option in TSE 
// [Files]  		boot.h, AMITSE.sdl, CommonHelper.c, bbs.c, boot.c,
// minisetup.h, special.c, callback.c 
// 
// 24    3/28/11 11:40p Madhans
// [TAG]  		EIP50878
// [Category]  	Improvement
// [Description]  	Support to move the Control With Boot Order Change.
// [Files]  		AMITSE.sdl
// commonoem.c
// minisetup.h
// popupsel.c
// 
// 23    3/23/11 8:38p Blaines
// [TAG] - EIP 23601
// [Category]- Enhancement
// [Symptom]- Add support for OEM special controls.
// [Files] - AmiTse.sdl, CommonHelper.c, Setup.ini, UefiSetup.ini,
// AmiVfr.h, minisetup.h, minisetup.sdl, variable.c, special.c
// 
// 22    3/21/11 1:23a Rajashakerg
// [TAG]  		EIP53740
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Animation does not continue after the last frame of the
// logo.
// [RootCause]  	
// Animation is continued upto the last frame of the animated image
// [Solution]  	Fixed the issue by handling Gif image data to redraw image
// if all the frames are completed and if boottimeout is present. 	
// [Files]  		minisetup.h, dogif.c, dogifmgr.c
// 
// 21    3/15/11 5:14a Rajashakerg
// [TAG]  		EIP51671
// [Category]  	New Feature
// [Description]  	Boot overide menu devices are not disable  
// [Files]  		boot.c, minisetup.h, special.c, minisetupext.c, AMITSE.sdl,
// boot.h, CommonHelper.c 
// 
// 20    1/10/11 3:55p Mallikarjunanv
// Updated to work with respect to EDK Libraries
// 
// 19    12/29/10 2:27a Mallikarjunanv
// Updated the funcation name of the EIP:50479
// 
// 18    12/28/10 6:14p Mallikarjunanv
// [TAG]  		EIP41615
// [Category]  	New Feature
// [Description]  	Added the file browser support for the Add boot option
// reated controls
// [Files]  		AmiVfr.h, AmiTse.sdl, AmiTseStr.uni, CommonHelper.c,
// Faketokens.c, TseElinks.h, EdkHelper.h, minisetup.h, TseAdvanced.c,
// AddBootOption.c
// 
// 17    12/26/10 10:27a Mallikarjunanv
// [TAG]  		EIP50479
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Calls to PostManagerProtocol->SwitchToPostScreen() after
// legacy option ROM execution cause CPU exception. 
// [RootCause]  	fter the notification, if the graphics driver uninstalled
// and reinstalled from core module then gGOP getting corrupted.
// [Solution]  	Updated gGop before using it in AMITSE.
// [Files]  		logo.c,minisetup.h, notify.c, postmgmt.c
// 
// 16    10/06/10 5:59p Madhans
// [TAG] - EIP 45620 
// [Category]- Enhancment
// [Severity]- Mordarate
// [Symptom]- TSE with TSE_CONTINUE_BOOT_NOW_ON_FAIL ON Not allows to boot
// to USB group of devices with customized BDS.
// [RootCause] - BBSTable does not contain the DeviceType called USB. Only
// in EFI Logical group is created in EFI variables.
// TSE was checking the DeviceType to set the priorities.
// [Solution]- TSE is changed to not check for DeviceType in BBSTable. But
// set the priorities based on LegacyDevOrder.
// [Files] - bbs.c commonhelper.c minisetup.h 
// 
// 15    10/05/10 5:38p Madhans
// [TAG] - EIP 45299 
// [Category]- Enhancment
// [Severity]- Minor
// [Symptom]- TSE by default saves the Disbaled BBS devices device path in
// NVRAM Varaiable "DisabledDevs" Variable. In Next boots it depend on
// this variable to consider the device as disabled inaddtion to
// LegacyDevOrder.
// Some BDS customized projects don't want this.
// [Solution]- TSE_SAVE_DISABLED_BBS_DEVICEPATH SDL token created to
// control this option. Bydefault It is Enabled.
// [Files] - callback.c bbs.c commonhelper.c minisetup.h AMITSE.sdl
// 
// 14    9/20/10 6:47p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 13    9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 28    9/08/10 6:53a Mallikarjunanv
// EIP-42080: TSE updates with respect to Fast Boot Support
// 
// 27    8/27/10 5:00a Mallikarjunanv
// EIP-39334: support to build TSE without the CSM module support
// 
// 26    4/07/10 6:24p Madhans
// post screen Sroll area support. TSE_POSTSCREEN_SCROLL_AREA SDL
// configures the area.
// 
// 25    4/02/10 4:37p Madhans
// To get ride of TSEOEM.H referance in TSE. Oem hearder files can be
// refered only in Tse Binary.
// 
// 24    3/23/10 5:08p Blaines
// Preseve the order of disabled BBS boot devices.
// 
// 23    2/26/10 7:06p Madhans
// Cleanup on formbrowrser.h
// 
// 3     2/26/10 3:36p Madhans
// Formbrowser.h need to be in Hii modules.
// 
// 21    2/17/10 1:02p Madhans
// minisetupstr.uni removed and Strings token are refered from
// AMITSEStrTokens.h
// 
// 20    2/15/10 10:10p Madhans
// To avoid Compilation issues
// 
// 19    2/11/10 7:14a Mallikarjunanv
// added Tse Advanced module dependency to include TseElinks.h
// 
// 18    2/04/10 12:03p Blaines
// EIP-28005
// 
// Added PostManagerSetAttribute to support display of text in color.
// Added support for handling string characters --- \n, \r.
// 
// 17    1/18/10 2:07a Mallikarjunanv
// EIP-28501: Updated for Keyboard scancode as password. Added a new Token
// SETUP_STORE_KEYCODE_PASSWORD to support the EFI key or Scan code as
// password
// 
// 16    1/09/10 5:26a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 15    1/04/10 10:40a Mallikarjunanv
// EIPs 27161/29095 - Added support for reserved boot option names and
// added support not to create empty boot option names
// 
// 14    10/28/09 5:37p Madhans
// 
// 13    9/24/09 9:41a Sudhirv
// EIP-24971: moved the dependency for TSE_CONTINUE_BOOT_NOW_ON_FAIL to
// Tse Binary
// 
// 12    9/17/09 9:04a Sudhirv
// Remove Load Driver Option from TSE 2.x as it will be handled from Core
// 
// 11    9/16/09 6:15p Madhans
// EIP 25416  : Support have 1/10 sec Timeout
// 
// 10    9/15/09 9:31a Sudhirv
// removed Version macros and added function declarations for Add Del boot
// option handling
// 
// 9     8/18/09 6:34p Blaines
// Support additional date styles
// 
// 8     8/17/09 12:21p Presannar
// Removed References to Tiano.h
// 
// 7     8/17/09 10:52a Presannar
// Added code to include EDKHelper.h
// Removed redefinition of structure LOGO_TYPE
// Added fn prototype for CleanUpExtendedLogoWrapper and
// DoLogoAnimateWrapper
// 
// 6     8/13/09 7:35a Mallikarjunanv
// eip:24971 - supporting tse features without tse sources
// 
// 5     7/30/09 7:49a Mallikarjunanv
// updated the code to move the exit page option elinks to Tse Binary - 
// included the new header file TseElinks.h to access all tse modules
// 
// 4     6/24/09 6:09p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 3     5/13/09 2:22p Madhans
// To patch the version number in the Bootonly TSE. update the build
// number.
// 
// 2     5/07/09 10:35a Madhans
// Changes after Bin module
// 
// 9     5/06/09 12:31p Mallikarjunanv
// updated the version info
// 
// 8     5/05/09 3:11p Madhans
// Std Col default.
// 
// 7     5/01/09 9:45p Blaines
// Control and Label margin support changes
// 
// 6     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 5     3/31/09 3:58p Madhans
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
// Name:		MINISETUP.h
//
// Description:	Main header file takes care of TSE includes.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _MINISETUP_H_
#define	_MINISETUP_H_

#ifdef TSE_FOR_APTIO_4_50
#include <Token.h>
#else
#include "tokens.h"
#endif


#ifndef SETUP_USE_GUIDED_SECTION
#define SETUP_USE_GUIDED_SECTION 0
#endif

#ifndef SETUP_JPEG_LOGO_SUPPORT
#define SETUP_JPEG_LOGO_SUPPORT 0
#endif

#ifndef SETUP_PCX_LOGO_SUPPORT
#define SETUP_PCX_LOGO_SUPPORT 0
#endif

#ifndef SETUP_GIF_LOGO_SUPPORT
#define SETUP_GIF_LOGO_SUPPORT 0
#endif

#ifndef TSE_BOOT_NOW_IN_BOOT_ORDER
#define TSE_BOOT_NOW_IN_BOOT_ORDER 0
#endif

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 

#include "EfiDriverLib.h"
#include "EfiPrintLib.h"

#include EFI_PROTOCOL_DEFINITION(FirmwareVolume)
#include EFI_PROTOCOL_DEFINITION(SimpleFileSystem)
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
#include EFI_PROTOCOL_DEFINITION(GraphicsOutput)
// Between GOP and UGA draw protocols blt buffer structure remains
// the same. The difference is only in the name so we can safely
// typedef the new structure to old structure's name.
typedef EFI_GRAPHICS_OUTPUT_BLT_PIXEL EFI_UGA_PIXEL;
#else
#include EFI_PROTOCOL_DEFINITION(UgaDraw)
#endif
#include EFI_PROTOCOL_DEFINITION(ConsoleControl)
#include EFI_PROTOCOL_DEFINITION(DevicePath)
#include EFI_PROTOCOL_DEFINITION(ComponentName)
#include EFI_PROTOCOL_DEFINITION(LegacyBios)
#include EFI_PROTOCOL_DEFINITION(LoadedImage)
#include EFI_PROTOCOL_DEFINITION(FileInfo)
#if EFI_SPECIFICATION_VERSION<=0x20000
#include EFI_PROTOCOL_DEFINITION(Hii)
#endif

#if SETUP_ITK_COMPATIBILITY
#include "..\ITK\OemBadgingSupport\EfiOEMBadging.h"
#else
#include EFI_PROTOCOL_DEFINITION(EfiOEMBadging)
#endif
#include EFI_GUID_DEFINITION(Bmp)
INTN MemCmp( UINT8 *dest, UINT8 *src, UINTN size );

#define MSG_USB_WWID_CLASS_DP           MSG_USB_WWID_DP
#define MSG_USB_LOGICAL_UNIT_CLASS_DP   MSG_DEVICE_LOGICAL_UNIT_DP
#define MSG_USB_SATA_DP			        MSG_SATA_DP
#define MSG_USB_ISCSI_DP		        MSG_ISCSI_DP

#else //TSE_USE_EDK_LIBRARY

#include "Efi.h"

#include "Protocol/FirmwareVolume.h"
#include "Protocol/SimpleFileSystem.h"
#include "Protocol/SimpleTextOut.h"
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
#include "Protocol/GraphicsOutput.h"
	// Between GOP and UGA draw protocols blt buffer structure remains
	// the same. The difference is only in the name so we can safely
	// typedef the new structure to old structure's name.
typedef EFI_GRAPHICS_OUTPUT_BLT_PIXEL EFI_UGA_PIXEL;
#else
#include "UgaDraw.h"
#endif

#include "Protocol/ConsoleControl.h"
#include "Protocol/DevicePath.h"
#include "Protocol/ComponentName.h"
//#include "LegacyBios.h"
#include "Protocol/LoadedImage.h"


#if SETUP_ITK_COMPATIBILITY
#include "..\ITK\OemBadgingSupport\EfiOEMBadging.h"
#else
#include "Protocol/EfiOemBadging.h" 
#endif

#include "Protocol/SimpleTextInEx.h"
//#include "LegacyBios.h"
#include "AmiDxeLib.h"  
#define EFI_DRIVER_ENTRY_POINT(a)

#include "EDKhelper.h"  

// EfiDriverlib
VOID *
EfiLibAllocateZeroPool (
  IN  UINTN   AllocationSize
  );

VOID
EfiStrCpy (
  IN CHAR16   *Destination,
  IN CHAR16   *Source
  );
UINTN
EfiDevicePathSize (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  );
VOID *
EfiLibAllocatePool (
  IN  UINTN   AllocationSize
  );
EFI_STATUS
EFIAPI
TseEfiCreateEventReadyToBoot (
  IN EFI_TPL                      NotifyTpl,
  IN EFI_EVENT_NOTIFY             NotifyFunction,
  IN VOID                         *NotifyContext,
  OUT EFI_EVENT                   *ReadyToBootEvent
  );
EFI_STATUS
EfiLibReportStatusCode (
  IN EFI_STATUS_CODE_TYPE     Type,
  IN EFI_STATUS_CODE_VALUE    Value,
  IN UINT32                   Instance,
  IN EFI_GUID                 *CallerId OPTIONAL,
  IN EFI_STATUS_CODE_DATA     *Data     OPTIONAL
  );
EFI_DEVICE_PATH_PROTOCOL *
EfiFileDevicePath (
  IN EFI_HANDLE               Device  OPTIONAL,
  IN CHAR16                   *FileName
  );
EFI_STATUS
EfiLibNamedEventSignal (
  IN EFI_GUID            *Name
  );
EFI_DEVICE_PATH_PROTOCOL *
EfiAppendDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL  *Src2
  );

EFI_DEVICE_PATH_PROTOCOL        *
EfiAppendDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
  IN EFI_DEVICE_PATH_PROTOCOL  *Src2
  );

VOID
EFIAPI
EfiInitializeFwVolDevicepathNode (
  IN  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH     *FvDevicePathNode,
  IN EFI_GUID                               *NameGuid
  );

UINTN
SPrint (
  OUT CHAR16        *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR16  *Format,
  ...
  );
EFI_STATUS
EfiInitializeDriverLib (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

VOID SetupDebugPrint(IN CONST CHAR8  *Format, ...) ;

extern EFI_SYSTEM_TABLE 	*gST;
extern EFI_BOOT_SERVICES 	*gBS;
extern EFI_RUNTIME_SERVICES 	*gRT;

#define EFI_TPL_APPLICATION 	TPL_APPLICATION
#define EFI_TPL_CALLBACK    	TPL_CALLBACK
#define EFI_TPL_NOTIFY      	TPL_NOTIFY
#define EFI_TPL_HIGH_LEVEL  	TPL_HIGH_LEVEL

#ifndef BBS_TYPE_FLOPPY
#define BBS_TYPE_FLOPPY           	BBS_FLOPPY
#endif
#ifndef BBS_TYPE_HARDDRIVE
#define BBS_TYPE_HARDDRIVE        	BBS_HARDDISK
#endif
#ifndef BBS_TYPE_CDROM
#define BBS_TYPE_CDROM            	BBS_CDROM
#endif
#ifndef BBS_TYPE_PCMCIA
#define BBS_TYPE_PCMCIA           	BBS_PCMCIA
#endif
#ifndef BBS_TYPE_USB
#define BBS_TYPE_USB              	BBS_USB
#endif
#ifndef BBS_TYPE_EMBEDDED_NETWORK
#define BBS_TYPE_EMBEDDED_NETWORK 	BBS_EMBED_NETWORK
#endif
#ifndef BBS_TYPE_BEV
#define BBS_TYPE_BEV              	BBS_BEV_DEVICE
#endif
#ifndef BBS_TYPE_UNKNOWN
#define BBS_TYPE_UNKNOWN          	BBS_UNKNOWN
#endif

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

#define CHAR_NULL             0x0000
#define CHAR_BACKSPACE        0x0008
#define CHAR_TAB              0x0009
#define CHAR_LINEFEED         0x000A
#define CHAR_CARRIAGE_RETURN  0x000D
#define GLYPH_WIDTH         8
#define GLYPH_HEIGHT        19
#define NARROW_CHAR         0xFFF0
#define WIDE_CHAR           0xFFF1
#define NON_BREAKING_CHAR   0xFFF2

// BMP
//
// Definitions for BMP files
//
#pragma pack(1)

typedef struct {
  UINT8   Blue;
  UINT8   Green;
  UINT8   Red;
  UINT8   Reserved;
} BMP_COLOR_MAP;

typedef struct {
  CHAR8         CharB;
  CHAR8         CharM;
  UINT32        Size;
  UINT16        Reserved[2];
  UINT32        ImageOffset;
  UINT32        HeaderSize;
  UINT32        PixelWidth;
  UINT32        PixelHeight;
  UINT16        Planes;       // Must be 1
  UINT16        BitPerPixel;  // 1, 4, 8, or 24
  UINT32        CompressionType;
  UINT32        ImageSize;    // Compressed image size in bytes
  UINT32        XPixelsPerMeter;
  UINT32        YPixelsPerMeter;
  UINT32        NumberOfColors;
  UINT32        ImportantColors;
} BMP_IMAGE_HEADER;

#pragma pack()

#define EFI_DEFAULT_BMP_LOGO_GUID \
  {0x7BB28B99,0x61BB,0x11d5,0x9A,0x5D,0x00,0x90,0x27,0x3F,0xC1,0x4D}

extern EFI_GUID gEfiDefaultBmpLogoGuid;

///DEVICE PATH Definitions
#ifndef MSG_USB_WWID_CLASS_DP
#define MSG_USB_WWID_CLASS_DP		0x10
#endif
#ifndef MSG_USB_LOGICAL_UNIT_CLASS_DP
#define MSG_USB_LOGICAL_UNIT_CLASS_DP	0x11
#endif
#ifndef MSG_USB_SATA_DP
#define MSG_USB_SATA_DP			0x12
#endif
#ifndef MSG_USB_ISCSI_DP
#define MSG_USB_ISCSI_DP		0x13
#endif
#endif //TSE_USE_EDK_LIBRARY

//USB Class devices - Device path..
#define USB_PHY_DEV_CLASS 		0x05
#define USB_MASS_DEV_CLASS 		0x08

extern EFI_GUID  gEfiGlobalVariableGuid;

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
#if TSE_USE_EDK_LIBRARY
#if EFI_SPECIFICATION_VERSION>=0x2000A
#define __UEFI_HII__H__
#include<EfiHii.h>
#else
#define __HII_PROTOCOL_H__
#endif
#endif //TSE_USE_EDK_LIBRARY
#include "Protocol/AmiKeyCode.h"
#else
#ifndef _AMI_EFI_KEY_DATA_
#define _AMI_EFI_KEY_DATA_
typedef struct {
  EFI_INPUT_KEY  Key;
} AMI_EFI_KEY_DATA;
#endif
#endif

#ifdef TSE_FOR_APTIO_4_50
#include "Include/Protocol/AMIPostMgr.h"
#else
#include "AMIPostMgr.h"
#endif

#include "amiver.h"

//handling version macros as tokens
//#define	TSE_MAJOR	0x02
//#define	TSE_MINOR	0x00
//#define	TSE_BUILD	0x1201

#define	MINI_SETUP_DATA_GUID		\
	{ 0xFE612B72, 0x203C, 0x47B1, 0x85, 0x60, 0xA6, 0x6D, 0x94, 0x6E, 0xB3, 0x71 }

#include "hiistring.h"
#include "string.h"
#include "protocol.h"
#include "variable.h"
#include "boot.h"
#include "AMILogo.h"
#include "bootflow.h"
#include "Timer.h"  

#ifdef TSE_FOR_APTIO_4_50
#include "AMITSEStrTokens.h"
#else
#include STRING_DEFINES_FILE
#endif

#ifdef TSE_FOR_APTIO_4_50
#include "Include/AMIVfr.h" 
#else
#include "AMIVFR.h"
#endif

#if TSE_APTIO_5_SUPPORT
#define AMITSE_TEXT(a) 	a
#else
#define AMITSE_TEXT(a) 	L##a
#endif

#include "bbs.h"

///for Hotkey customizations - 6/1/09
#if TSE_STYLE_SOURCES_SUPPORT
#include "HotkeyBin.h"
#include "HotclickBin.h" //EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
#endif

#if TSE_LITE_SOURCES_SUPPORT
#include "frame.h"
#include "Label.h"  
#include "hotkey.h"
#include "hotclick.h"//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
#include "minisetupext.h"
#endif 

#ifndef STRING_TOKEN
#define STRING_TOKEN(t) t
#endif

UINTN StyleGetTextMode( UINTN Rows, UINTN Cols );
VOID StyleUpdateVersionString( VOID );
UINTN StyleGetClearScreenColor(VOID);
UINT8 StyleGetPageLinkColor(VOID);
UINT8 StyleGetScrollBarColor(VOID);
UINT8 StyleGetScrollBarUpArrowColor(VOID);
UINT8 StyleGetScrollBarDownArrowColor(VOID);

UINTN StyleGetStdMaxRows(VOID);
UINTN StyleGetStdMaxCols(VOID);
VOID GetProgressColor(EFI_UGA_PIXEL * BGColor, EFI_UGA_PIXEL * BDRColor, EFI_UGA_PIXEL * FillColor);

#ifndef STYLE_FULL_MAX_ROWS
#define	STYLE_FULL_MAX_ROWS	31
#endif

#ifndef STYLE_FULL_MAX_COLS
#define	STYLE_FULL_MAX_COLS	100
#endif

#ifndef STYLE_STD_MAX_ROWS
#define	STYLE_STD_MAX_ROWS	24
#endif

#ifndef STYLE_STD_MAX_COLS
#define	STYLE_STD_MAX_COLS	80
#endif

#ifndef STYLE_MAX_COLS
#define	STYLE_MAX_COLS	STYLE_FULL_MAX_COLS
#endif

#ifndef STYLE_MAX_ROWS
#define	STYLE_MAX_ROWS	STYLE_FULL_MAX_ROWS
#endif

#define	MAX_ROWS		STYLE_MAX_ROWS
#define	MAX_COLS		STYLE_MAX_COLS
#define	MAX_DIMENSIONS	(STYLE_FULL_MAX_ROWS * STYLE_FULL_MAX_COLS)

#include "screen.h"

#include "commonoem.h"
#include "LogoLib.h"
#include "PwdLib.h"
#include "HiiLib.h"
#include "mem.h"
#include "HookAnchor.h"
#if TSE_ADVANCED_SUPPORT
#include "TseElinks.h"
#endif 
#ifdef TSE_FOR_APTIO_4_50
#include "AmiStatusCodes.h"
#else
#include "EfiStatusCode.h"
#endif

#ifndef BBS_TYPE_DEV
#ifdef BBS_TYPE_BEV
#define BBS_TYPE_DEV BBS_TYPE_BEV
#else
#define BBS_TYPE_DEV 0x80
#endif
#endif
/* B1DA0ADF-4F77-4070-A88E-BFFE1C60529A */
#define	MINI_SETUP_GUID	\
	{ 0xB1DA0ADF, 0x4F77, 0x4070, { 0xA8, 0x8E, 0xBF, 0xFE, 0x1C, 0x60, 0x52, 0x9A } }

#define	SETUP_VARIABLE_GUID	\
	{ 0xEC87D643, 0xEBA4, 0x4BB5, { 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 } }

/* 47C7B224-C42A-11D2-8E57-00A0C969723B */
#define ENVIRONMENT_VARIABLE_ID  \
  { 0x47c7b224, 0xc42a, 0x11d2, 0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

// End Notifications


// Status code reporting - Defines >> Start
// Defined in AmiStatusCodes.h
// Redefining for Aptio 3.x 
#ifndef AMI_STATUS_CODE_CLASS
#define AMI_STATUS_CODE_CLASS 	EFI_OEM_SPECIFIC //0x8000
#endif

#ifndef AMI_DXE_BS_EC_INVALID_PASSWORD
#define AMI_DXE_BS_EC_INVALID_PASSWORD (AMI_STATUS_CODE_CLASS | 0x00000002)
#endif

#ifndef AMI_DXE_BS_EC_BOOT_OPTION_LOAD_ERROR
#define AMI_DXE_BS_EC_BOOT_OPTION_LOAD_ERROR (AMI_STATUS_CODE_CLASS | 0x00000003)
#endif

#ifndef AMI_DXE_BS_EC_BOOT_OPTION_FAILED
#define AMI_DXE_BS_EC_BOOT_OPTION_FAILED (AMI_STATUS_CODE_CLASS | 0x00000004)
#endif


#ifndef DXE_SETUP_VERIFYING_PASSWORD
#define DXE_SETUP_VERIFYING_PASSWORD (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_DXE_BS_PC_VERIFYING_PASSWORD)
#endif

#ifndef DXE_SETUP_START
#define DXE_SETUP_START (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_USER_SETUP)
#endif

#ifndef DXE_SETUP_INPUT_WAIT
#define DXE_SETUP_INPUT_WAIT (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_INPUT_WAIT)
#endif

#ifndef DXE_READY_TO_BOOT
#define DXE_READY_TO_BOOT (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_DXE_BS_PC_READY_TO_BOOT_EVENT)
#endif

#ifndef DXE_INVALID_PASSWORD
#define DXE_INVALID_PASSWORD (EFI_SOFTWARE_DXE_BS_DRIVER | AMI_DXE_BS_EC_INVALID_PASSWORD)
#endif

#ifndef DXE_BOOT_OPTION_LOAD_ERROR
#define DXE_BOOT_OPTION_LOAD_ERROR (EFI_SOFTWARE_DXE_BS_DRIVER | AMI_DXE_BS_EC_BOOT_OPTION_LOAD_ERROR)
#endif

#ifndef DXE_BOOT_OPTION_FAILED
#define DXE_BOOT_OPTION_FAILED (EFI_SOFTWARE_DXE_BS_DRIVER | AMI_DXE_BS_EC_BOOT_OPTION_FAILED)
#endif
// Status code reporting -Define >> End

#define NG_SIZE 	19
#define WG_SIZE		38

#ifdef EFI_NT_EMULATOR
#define	RUNTIME_DEBUG_SUPPORT
#define	RUNTIME_DEBUG(str)	{ if ( __RuntimeCheckDebugMode( str ) ) _asm int 3 }
#else
#undef RUNTIME_DEBUG_SUPPORT
#define	RUNTIME_DEBUG(str)
#endif

#ifndef STANDALONE_APPLICATION
#if APTIO_4_00 != 1 && SETUP_USE_GUIDED_SECTION !=1
extern SETUP_PKG					_SetupPackage;
#endif
#else
extern UINT8 DummySetupData[];
#endif


extern SCREEN_BUFFER				*gActiveBuffer;
extern SCREEN_BUFFER				*gFlushBuffer;
#ifdef USE_DEPRICATED_INTERFACE
extern UINT8						*STRING_ARRAY_NAME;
#else
#if APTIO_4_00
#else
extern UINT8						STRING_ARRAY_NAME[];
#endif
#endif
extern UINT8						*gApplicationData;
extern EFI_HANDLE					gImageHandle;
extern EFI_COMPONENT_NAME_PROTOCOL	gComponentName;
extern UINT16						gCheckboxTokens[];

extern BOOLEAN						gVariableChanged;
extern BOOLEAN						gResetRequired;

#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
extern EFI_GRAPHICS_OUTPUT_PROTOCOL	*gGOP;
#else
extern EFI_UGA_DRAW_PROTOCOL		*gUgaDraw;
#endif

#ifndef STANDALONE_APPLICATION
extern EFI_CONSOLE_CONTROL_PROTOCOL	*gConsoleControl;
#endif

//EIP75481  Support TSE debug print infrastructure

#define PRINT_UEFI		        1
#define PRINT_UEFI_CALLBACK	    2
#define PRINT_UEFI_NOTIFICATION 4
#define PRINT_UEFI_PARSE	    8

#if SUPPRESS_PRINT
    #define SETUP_DEBUG_TSE(format,...)
    #define SETUP_DEBUG_UEFI(format,...)
    #define SETUP_DEBUG_UEFI_PARSE(format,...)
    #define SETUP_DEBUG_UEFI_NOTIFICATION(format,...)
    #define SETUP_DEBUG_UEFI_CALLBACK(format,...)
    #define SETUP_DEBUG_VAR(format,...)
#else //Else of SUPPRESS_PRINT
    #define SETUP_DEBUG_TSE(format,...) SetupDebugPrint(format, __VA_ARGS__)
    #define SETUP_DEBUG_UEFI(format,...) if((gDbgPrint & PRINT_UEFI)== PRINT_UEFI)SetupDebugPrint(format, __VA_ARGS__)
    #define SETUP_DEBUG_UEFI_PARSE(format,...) if((gDbgPrint & PRINT_UEFI_PARSE)== PRINT_UEFI_PARSE)SetupDebugPrint(format, __VA_ARGS__)
    #define SETUP_DEBUG_UEFI_NOTIFICATION(format,...) if((gDbgPrint & PRINT_UEFI_NOTIFICATION)== PRINT_UEFI_NOTIFICATION)SetupDebugPrint(format, __VA_ARGS__)
    #define SETUP_DEBUG_UEFI_CALLBACK(format,...) if((gDbgPrint & PRINT_UEFI_CALLBACK)== PRINT_UEFI_CALLBACK)SetupDebugPrint(format, __VA_ARGS__)
    #define SETUP_DEBUG_VAR(format,...) SetupDebugPrint(format, __VA_ARGS__)
#endif //End of SUPPRESS_PRINT
//EIP75481  


extern BOOLEAN						gQuietBoot;
extern BOOLEAN						gEnterSetup;
extern EFI_EVENT					gKeyTimer;
extern EFI_EVENT					gClickTimer;
extern UINT32						gPasswordType;

extern UINTN 						gPostStatus;

extern BOOT_DATA					*gBootData;

extern BOOT_DATA                    *gCurrLegacyBootData;

extern UINTN						gLangCount;
extern LANGUAGE_DATA				*gLanguages;

extern BOOLEAN						gSetupContextActive;
extern BOOLEAN						gPostMsgProtocolActive;
extern UINT8						gPostMgrAttribute;
extern AMI_VERSION					gVersion_TSE;
extern UINT32						gStartPage;

extern UINTN 						gLabelLeftMargin ;
extern UINTN 						gControlLeftPad ;
extern UINTN						gControlLeftMargin;
extern UINTN						gControlRightAreaWidth;

extern UINTN						gMaxRows;
extern UINTN						gMaxCols;
extern UINTN 						gPostManagerHandshakeCallIndex;
extern UINT16                       gDbgPrint ;

extern EFI_GUID _gBootFlowGuid;
extern BOOLEAN gDoNotBoot;

extern UINTN   gCurrIDESecPage;


#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
extern EFI_GUID gAmiEfiKeycodeProtocolGuid;
#endif

//EIP-28501: To support SETUP_STORE_KEYCODE_PASSWORD options
#define PW_EFI_KEY		1
#define PW_SCAN_CODE	2

#define DATE_STYLE_MMDDYYYY		0
#define DATE_STYLE_YYYYDDMM		1
#define DATE_STYLE_DDMMYYYY		2
#define DATE_STYLE_YYYYMMDD		3

#define	TIMER_ONE_SECOND	(10 * 1000 * 1000)
#define	TIMER_HALF_SECOND	(TIMER_ONE_SECOND / 2)
#define TIMER_TENTH_SECOND  (TIMER_ONE_SECOND / 10)

#define	STRUCT_OFFSET(type, field)	(UINTN)&(((type *)0)->field)

typedef struct _PROGRESSBAR_INFO		//Structure containing global information used by progressbar handler
{
	UINTN			x;					//	ProgressBar Left Position
	UINTN			y;					//	ProgressBar Top Position
	UINTN			w;					//	ProgressBar width
	UINTN			h;					//	ProgressBar Height
	EFI_UGA_PIXEL	*backgroundColor;	//	ProgressBar Background Color
	EFI_UGA_PIXEL	*borderColor;		//	ProgressBar Border Color
	EFI_UGA_PIXEL	*fillColor;			//	ProgressBar Fill Color
	UINTN			delta;				//	Varies	increment
	UINTN			completed;			//	Varies	increment
	BOOLEAN			quiteBootActive;	//  True if quiteBoot is active	
	BOOLEAN			active;				//  True if progressbar has been initialized
}PROGRESSBAR_INFO;

extern PROGRESSBAR_INFO	*gProgress;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Function Number (0 = First Function).
  ///
  UINT8                           FunctionNumber;
} AMITSE_PCCARD_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Firmware file name
  ///
  EFI_GUID                        FvFileName;
} AMITSE_MEDIA_FW_VOL_FILEPATH_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  UINT32                          Tid;
} AMITSE_I2O_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// The MAC address for a network interface padded with 0s.
  ///
  EFI_MAC_ADDRESS                 MacAddress;
  ///
  /// Network interface type(i.e. 802.3, FDDI).
  ///
  UINT8                           IfType;
} AMITSE_MAC_ADDR_DEVICE_PATH;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// The HBA port number that facilitates the connection to the
  /// device or a port multiplier. The value 0xFFFF is reserved.
  ///
  UINT16                          HBAPortNumber;
  ///
  /// The Port multiplier port number that facilitates the connection
  /// to the device. Bit 15 should be set if the device is directly
  /// connected to the HBA.
  ///
  UINT16                          PortMultiplierPortNumber;
  ///
  /// Logical Unit Number.
  ///
  UINT16                          Lun;
} AMITSE_SATA_DEVICE_PATH;
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// Network Protocol (0 = TCP, 1+ = reserved).
  ///
  UINT16                          NetworkProtocol;
  ///
  /// iSCSI Login Options.
  ///
  UINT16                          LoginOption;
  ///
  /// iSCSI Logical Unit Number.
  ///
  UINT64                          Lun;
  ///
  /// iSCSI Target Portal group tag the initiator intends
  /// to establish a session with.
  ///
  UINT16                          TargetPortalGroupTag;
  ///
  /// iSCSI NodeTarget Name. The length of the name
  /// is determined by subtracting the offset of this field from Length.
  ///
  /// CHAR8                        iSCSI Target Name.
} AMITSE_ISCSI_DEVICE_PATH;

// box.c 
VOID DrawLineWithAttribute( UINTN Col, UINTN Row, UINTN Length, CHAR16 Type, UINT8 Attrib );
VOID DrawLine( UINTN Col, UINTN Row, UINTN Length, CHAR16 Type );
VOID DrawBorder( UINTN Left, UINTN Top, UINTN Width, UINTN Height );
VOID DrawWindow( UINTN Left, UINTN Top, UINTN Width, UINTN Height, UINT8 Attrib, BOOLEAN Border, BOOLEAN Shadow );
VOID DrawBox( UINTN Left, UINTN Top, UINTN Width, UINTN Height, UINT8 Attrib );

// buffer.c
EFI_STATUS InitializeScreenBuffer( UINT8 attrib );
VOID SlowFlushLines( UINTN Top, UINTN Bottom );
VOID FlushLines( UINTN Top, UINTN Bottom );
VOID DoRealFlushLines();
void SetDesiredTextMode();


// logo.c
VOID CleanUpExtendedLogoWrapper();
VOID DoLogoAnimateWrapper(CO_ORD_ATTRIBUTE Attribute,INTN CoordinateX,INTN CoordinateY);
VOID DrawBltProgressBar(/*UINTN completed*/ );

VOID DrawProgressBarBorder(
    UINTN	x,
    UINTN	y,
	UINTN	w,
    UINTN	h,
	EFI_UGA_PIXEL *BltBuffer,
	UINTN	bw
    );

VOID DrawBlock(
    UINTN	x,
    UINTN	y,
	UINTN	w,
    UINTN	h,
	EFI_UGA_PIXEL *BltBuffer
    );


VOID DrawBltBuffer(
    EFI_UGA_PIXEL *UgaBlt,
    CO_ORD_ATTRIBUTE Attribute,
    UINTN Width,
    UINTN Height,
    INTN DestX,
    INTN DestY,
    UINTN BufferWidth
    );
EFI_STATUS GetScreenResolution(UINTN *ResX, UINTN *ResY);

typedef struct RefreshIdInfo{
    UINT8 *pEvent;
    UINT8 *pNotifyContext;
} REFRESH_ID_INFO;

// dobmpmgr.c
#if SETUP_BMP_LOGO_SUPPORT
EFI_STATUS ConvertBmpToUgaBlt (IN VOID *BmpImage, IN UINTN BmpImageSize, IN OUT VOID **UgaBlt,
		IN OUT UINTN  *UgaBltSize, OUT UINTN *PixelHeight, OUT UINTN *PixelWidth );
#endif

EFI_STATUS
ConvertAdvancedImageToUgaBlt (
  IN  VOID      *BmpImage,
  IN  UINTN     BmpImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *PixelHeight,
  OUT UINTN     *PixelWidth,
  OUT BOOLEAN *Animate
);

VOID DoLogoAnimate(CO_ORD_ATTRIBUTE Attribute,INTN CoordinateX,INTN CoordinateY);
VOID CleanUpExtendedLogo(VOID);


// minisetup.c
BOOLEAN __RuntimeCheckDebugMode( CHAR16 *string );
VOID UIUpdateCallbackHook( VOID * Handle, UINT32 OldVariableCount  );//EIP 129750: UIUpdateCallback as board module hook
EFI_STATUS MainSetupLoopHook( VOID );//EIP74591: MainSetupLoop as board module hook
EFI_STATUS Handshake( VOID );
EFI_STATUS MiniSetupExit( EFI_STATUS Status );
EFI_STATUS MiniSetupEntry( VOID );

//EIP# 58925
extern UINT32 gNavStartPage ;
extern EFI_STATUS GetParentFormID(UINT16 ChildID, UINT16 *ParentID, UINT32 *StackIndex);
extern EFI_STATUS SetParentFormID(UINT16 ParentID, UINT16 TargetID);
extern VOID ResetNavStack();
//EIP# 58925

// notify.c
EFI_STATUS RegisterNotification( VOID );
VOID NotificationFunction( EFI_EVENT Event, VOID *Context );
VOID ActivateApplication( VOID );

//EIP-75236 Starts
VOID ActivateInput( VOID );
BOOLEAN  GetNotifyMaskValue (VOID);
BOOLEAN  IsDelayLogoTillInputSupported (VOID);
//EIP-75236 Ends

// postmgmt.c
VOID EncodePassword( CHAR16 *Password, UINTN MaxSize );
VOID CheckEnableQuietBoot( VOID );
//UINTN DrawAMILogo( VOID );
VOID InstallKeyHandlers( VOID );
VOID InstallClickHandlers( VOID );
VOID _DrawPasswordWindow(UINT16 PromptToken, UINTN PasswordLength, UINTN *CurrXPos, UINTN *CurrYPos);
VOID _ReportInBox(UINTN PasswordLength, UINT16 BoxToken, UINTN CurrXPos, UINTN CurrYPos, BOOLEAN bWaitForReturn);
EFI_STATUS _GetPassword(CHAR16 *PasswordEntered, UINTN PasswordLength, UINTN CurrXPos, UINTN CurrYPos, UINTN *TimeOut);

// helper functions
VOID * HelperGetVariable( UINT32 variable, CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size );
EFI_STATUS	InitApplicationData(EFI_HANDLE ImageHandle);
VOID MiniSetupUIExit(VOID);
VOID TSEIDEPasswordCheck();
VOID TSEIDEPasswordFreezeDevices();
VOID TSEUnlockHDD(VOID);
extern NVRAM_VARIABLE				*gVariableList;

// EIP 76381 : Performance Improving of variable data load and usage
extern NVRAM_VARIABLE *gCurrNvramVarList;
extern UINTN gCurrNvramVarCount;

#define	VARIABLE_ID_SETUP			0
#define	VARIABLE_ID_LANGUAGE		1
#define	VARIABLE_ID_BOOT_TIMEOUT	2
#define	VARIABLE_ID_USER_DEFAULTS	3
#define	VARIABLE_ID_ERROR_MANAGER	4
#define	VARIABLE_ID_AMITSESETUP     5
#define	VARIABLE_ID_IDE_SECURITY    6
#define VARIABLE_ID_BOOT_ORDER      7
#define VARIABLE_ID_BBS_ORDER       8
#define VARIABLE_ID_DEL_BOOT_OPTION 9
#define VARIABLE_ID_ADD_BOOT_OPTION 10
#define VARIABLE_ID_BOOT_MANAGER    11
#define VARIABLE_ID_BOOT_NOW        12
#define	VARIABLE_ID_LEGACY_DEV_INFO 13
#define	VARIABLE_ID_AMI_CALLBACK    14
#define	VARIABLE_ID_LEGACY_GROUP_INFO 15
#define	VARIABLE_ID_OEM_TSE_VAR		17
#define	VARIABLE_ID_DYNAMIC_PAGE_COUNT	18

UINT16 GetBootTimeOut(UINT16 DefaultValue);
EFI_STATUS UefiFormCallbackNVRead(CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size, VOID **buffer);
EFI_STATUS UefiFormCallbackNVWrite(CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size);
void UpdateAddDeleteBootVar(void);
UINT16 * BootNowinBootOrderInit(VOID);
BOOT_DATA * BootGetBootNowBootData(BOOT_DATA *bootData, UINT16 *BootOrder, UINTN i );
BOOLEAN NoVarStoreSupport(VOID);
BOOLEAN ItkSupport(VOID);
VOID UpdateLegacyDevVariable(UINT16 NoOfLegacyGroups);
VOID CsmBBSSetBootPriorities( BOOT_DATA *pBootData, UINT16 *pOrder, UINTN u16OrderCount);
CHAR16 *CsmBBSBootOptionName( BOOT_DATA *bootData);
EFI_STATUS CsmBBSSetBootNowPriority( BOOT_DATA *BootData,UINTN uiPrefferedDevice,BOOLEAN ShowAllBbsDev);
VOID CsmBBSGetDeviceList( VOID );
EFI_STATUS CsmBBSLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath );
EFI_STATUS 	InstallFormBrowserProtocol(EFI_HANDLE Handle);
VOID UnInstallFormBrowserProtocol(EFI_HANDLE Handle);
EFI_STATUS DoBbsPopupInit(VOID);
VOID MainSetupLoopInit(VOID);
UINTN TseGetANSIEscapeCode(CHAR16 *String,UINT8 *Bold,UINT8 *Foreground, UINT8 *Background);
CHAR16 *TseSkipEscCode(CHAR16 *String);
VOID DrawBootOnlyBbsPopupMenu( VOID );
VOID BbsBoot(VOID);
VOID BootGetLanguages();

extern BOOLEAN PlatformLangVerSupport();
extern BOOLEAN BootNowInBootOrderSupport();

VOID TseBootAddBootOption();
BOOLEAN CheckForAddDelBootOption();
VOID TSESpecialFixupDelBootOption(VOID *ControlInfo);
VOID TseDoAddBootOptionFixup(VOID *ControlInfo );
BOOLEAN TseDoBootDelBootOption(VOID *popupSel);
VOID TseDiscardAddDelBootOptions();
VOID TseSaveAddDelBootOptions();

// EIP-41615: Functions for the file browser support in add boot option
VOID TseLaunchFileSystem();

VOID TseBBSSetBootPriorities_BootOrder(UINT16 Priority); //EIP-24971: moved TSE_CONTINUE_BOOT_NOW_ON_FAIL support to Binary.

#define ___INTERNAL_CONVERT_TO_WSTRING___(a) L#a
#define CONVERT_TO_WSTRING(a) ___INTERNAL_CONVERT_TO_WSTRING___(a)

///Extended checks for Add/Delete Boot Option support
BOOLEAN IsUpdateBootOrderCursor();
BOOLEAN IsReservedBootOptionNamesEnable();
BOOLEAN IsPreservedDisabledBootOptionOrder();
EFI_STATUS FastBootLaunch(VOID);
extern BOOLEAN gIsSaveDisabledBBSDevicePath;
VOID UpdateGoPUgaDraw( VOID );//EIP:50479 : Function to Update gGop before using it in AMITSE.
//EIP:51671 Start
//Function declarations 
BOOLEAN IsBootDeviceEnabled( UINT16 value, BOOLEAN ShowAllBBSDev, BOOLEAN TseBootNowInBootOrde, BOOLEAN FromSetup);
BOOLEAN BootGetOptionStatus(BOOT_DATA *bootData, BOOLEAN FromSetup );
BOOLEAN BootGetBBSOptionStatus(BOOT_DATA *bootData, UINT16 value, BOOLEAN FromSetup,  BOOLEAN ShowAllBBSDev);
//EIP:51671 End
VOID RedrawGif(VOID);//EIP:53740 : Function to Redraw the Gif animated image.
BOOLEAN LoadOptionhidden(UINT16, BOOLEAN);	    //EIP:59417 - Fucntion Decleration to check the LOAD_OPTION_HIDDEN attribute for a boot option
EFI_STATUS TSEGetCoordinates(INT32 *x, INT32 *y, INT32 *z);
BOOLEAN CheckHiddenforBootDriverOption (UINT16, BOOLEAN);

//EIP70421 & 70422  Support for driver order starts
extern BOOT_DATA					*gDriverData;
void UpdateAddDeleteDriverVar (void);
VOID TseDriverAddDriverOption();
VOID TSESpecialFixupDelDriverOption (VOID *);
BOOLEAN TseDoDriverDelDriverOption(VOID *popupSel);
VOID TseDiscardAddDelDriverOptions();
VOID TseSaveAddDelDriverOptions();
//EIP70421 & 70422  Support for driver order ends
BOOLEAN  IsTSEMultilineControlSupported (VOID); //EIP-72610 Moved TSE_MULTILINE_CONTROLS to binary
UINT32 GetMsgboxWidth(VOID);//EIP74963 : MAX_MSGBOX_WIDTH macro changed as token and handled from binary
extern const UINTN TsePasswordLength;
VOID GetAMITSEVariable(AMITSESETUP **mSysConf,UINT8 **setup,UINTN *VarSize);
VOID NoVarStoreUpdateSystemAccess(UINT8 sysAccessValue);
VOID SetSystemAccessValueItk(UINT8 sysAccessValue);
VOID TSEStringReadLoopEntryHook(VOID);
VOID TSEStringReadLoopExitHook(VOID);
UINT32 PasswordAuthenticate( CHAR16 *Password );
EFI_STATUS AMIReadKeyStroke(EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData);
EFI_STATUS HelperIsPasswordCharValid(EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData,UINTN StrIndex,UINTN PasswordLength, CHAR16 *OutChar);
VOID TSEIDEUpdateConfig(VOID *ideSecConfig, UINTN value);
//EIP 77400
#define EFI_SHELL_PROTOCOL_GUID \
  { \
    0x47C7B223, 0xC42A, 0x11D2, 0x8E, 0x57, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B \
  }
#endif /* _MINISETUP_H_ */

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2012, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
