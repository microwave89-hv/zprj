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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/boot.c $
//
// $Author: Arunsb $
//
// $Revision: 70 $
//
// $Date: 5/02/14 9:26p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/boot.c $
// 
// 70    5/02/14 9:26p Arunsb
// semicolon added to PERF_END
// 
// 69    5/02/14 5:13p Premkumara
// [TAG]  	                EIP162197
// [Category]  	Improvement
// [Description]  	Password encode feature modify to encode using Hashing
// based on token.
// [[Files]  		Password.c, PasswordEncodeBin.cif, AMITSE.cif,
// TSESource.cif, PasswordEncode.c, PasswordEncode.h, AMITSE.sdl,
// PasswordEncodeBin.mak, PasswordEncodeBin.sdl
// AMIVfr.h, Boot.c
// 
// 68    5/02/14 2:24a Arunsb
// [TAG]  		EIP158989
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BGRT status bit not cleared with Shell v2.0
// [RootCause]  	Shell v2.0 protocol not registered
// [Solution]  	Shell v2.0 protocol registered and cleared the BGRT status
// bit
// [Files]  		AMIVfr.h and boot.c
// 
// 67    2/11/14 7:52p Arunsb
// [TAG]	EIP125719
// [Category]	Improvement
// [Description]	The EfiCreateEventReadyToBoot is conflicted under
// UefiLib.h and EDKhelper.h.
// [Files]	boot.c
// 
// 66    12/04/13 5:20a Premkumara
// [TAG]	EIP123535
// [Category]	Improvement
// [Description]	Moved saving quietboot resolution to DrawQuietBootLogo()
// to avoid setting resolution of initPostScreenthis while booting.
// [Files]	commonoem.c, Boot.c, Logo.c, MinisetupExt.c
// 
// 65    11/06/13 12:16p Arunsb
// [TAG]	EIP136592, 141863
// [Category]	Improvement
// [Description]	Resolution restored before signalling
// AMITSE_EVENT_BEFORE_BOOT_GUID
// [Files]	boot.c
// 
// 64    9/13/13 1:55p Premkumara
// Uploaded back EIP-126807 after TSEBootOnly1240 release.
// 
// 63    9/13/13 8:33a Premkumara
// Reverted EIP-126807 for TSEBootOnly1240 release.
// 
// 61    7/02/13 10:06a Premkumara
// [TAG]  		EIP120011
// [Category]  	Improvement
// [Description]  	Variable BootOrder and LegacyDevOrder need
// fool-proofing function when TSE load variabled
// [Files]  		Bbs.c, Boot.c, Callback.c, TseLiteHelper.c, Variable.c
// 
// 60    6/10/13 1:17p Arunsb
// BS->CalculateCrc32 used to calculate CRC
// 
// 59    5/21/13 5:52a Rajashakerg
// [TAG]  		EIP121881 
// [Category]  	Improvement
// [Description]  	Change resolution before boot in FastBoot path
// [Files]  		boot.c
// 
// 58    4/18/13 2:18a Arunsb
// [TAG]  		EIP113266
// [Category]  	Improvement
// [Description]  	gBrowserCallbackEnabled variable moved to boot only
// module
// [Files]  		boot.c and FormBrowser2.c
// 
// 57    3/18/13 12:23a Arunsb
// [TAG]  		EIP117338
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	TSE BootGetBBSOptionStatus asserts
// [RootCause]  	Pointer incremented from allocated initial memory and
// freed so asserts
// [Solution]  	Freed the initial allocated memory
// [Files]  		boot.c
// 
// 56    3/14/13 10:50a Premkumara
// [TAG]  		EIP112796
// [Category]  	New Feature
// [Description]  	AMITSE not signalling AMITSE_EVENT_BEFORE_BOOT_GUID in
// fast boot path and legacy boot path.
// [Files]  		Boot.c
// 
// 55    2/19/13 4:18a Premkumara
// [TAG]  		EIP103540 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	 Currently _BootBuildFVDevicePath function using FV
// protocol alone not FV2 protocol. So applications loading from ffs are
// not loading properly.
// [RootCause]  	_BootBuildFVDevicePath() function used
// gEfiFirmwareVolumeProtocolGuid only not gEfiFirmwareVolume2ProtocolGuid
// [Solution]  	Used gEfiFirmwareVolume2ProtocolGuid based on
// PISpecVersion
// [Files]  		CommonHelper.c, Boot.c
// 
// 54    12/05/12 5:30a Arunsb
// [TAG]  		EIP105864
// [Category]  	Improvement
// [Description]  	Screen not cleared properly for successive boots
// [Files]  		boot.c
// 
// 53    10/18/12 11:20a Arunsb
// [TAG]  		EIP102710
// [Category]  	Improvement
// [Description]  	Include function "_RegisterShellGuid()" in fast boot
// path
// [Files]  		boot.c
// 
// 52    10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 19    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 50    9/24/12 9:13a Premkumara
// [TAG]  		EIP 93797
// [Category]  	Improvement
// [Description]  	 	Add support to check for enabled device in BBS
// priority order before launching legacy boot.
// [Files]  		bbs.c, Boot.c, Protocol.c
// 
// 49    9/21/12 9:38a Premkumara
//  [TAG]  		EIP 97704
//  [Category]  	Improvement
//  [Description]  	Support BootFFFF variable
//  [Files]  		Boot.h, Boot.c, Special.c
// 
// 48    9/18/12 12:50a Rajashakerg
// [TAG]  		EIP95518
// [Category]  	Improvement
// [Description]  	Validate the Gop before usage in all the possible cases
// and also get instance of Gop through notification
// [Files]  		boot.c, notify.c, logo.c
// 
// 47    9/17/12 6:10a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 45    9/12/12 5:23a Rajashakerg
// [TAG]  		EIP94205
// [Category]  	Improvement
// [Description]  	OEM needs Token to assign the display mode of SHELL
// [Files]  		AMITSE.sdl, boot.c, CommonHelper.c
// 
// 44    8/29/12 4:19p Arunsb
// [TAG]  			EIP94702
// [Description]  	Support for Native Resolution in POST/BOOT
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c, boot.c, logo.c,
// notify.c, postmgmt.c, tselite\minisetupext.c, ezport/stylecommon.c,
// ezportplus/stylecommon.c andlegacy/stylecommon.c
// 
// 43    6/25/12 5:37p Arunsb
// [TAG]  		EIP93524
// [Category]  	Improvement
// [Description]  	Invalidate the BGRT table when boot device launched
// from BBS popup or from shell or launched as second boot device
// [Files]  		boot.c and minisetup.c
// 
// 42    5/29/12 3:53a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 41    5/28/12 6:09a Rajashakerg
// [TAG]  		EIP89377
// [Category]  	Improvement
// [Description]  	Support to LegacyBootFailHook() in TSE.
// [Files]  		AMITSE.sdl, CommonHelper.c, boot.c
// 
// 40    5/25/12 1:38a Premkumara
// [TAG]  		EIP88430
// [Category]  	Improvement
// [Description]  	Resolution set after logo displayed should retain when
// boot to device.
// [Files]  		boot.c, logo.c
// 
// 39    5/08/12 2:31a Rajashakerg
// [TAG]  		EIP89483
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Handle hidden boot options properly in BBS Pop up menu
// [RootCause]  	Check for LOAD_OPTION_HIDDEN is not present when
// TSE_BOOT_NOW_IN_BOOT_ORDER and POPUP_MENU_SHOW_ALL_BBS_DEVICES are
// Disabled
// [Solution]  	Provided the check for the loda option hidden.
// [Files]  		boot.c
// 
// 38    2/02/12 1:05p Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		boot.c
// 
// 37    1/31/12 6:42a Arunsb
// [TAG]  		EIP81830
// [Category]  	Improvement
// [Description]  	Support to uninstall the BGRT on legacy boot.
// [Files]  		Commonhelper.c, postmgmt.c and boot.c
// 
// 36    1/13/12 1:40a Arunsb
// For shell the cursor is enabled. Default the cursor is disabled to
// avoid cursor visibility in win8 seamless boot
// 
// 35    1/10/12 2:36a Arunsb
// [TAG]  		EIP77400
// [Category]  	Improvement
// [Description]  	Need to do "Clear Screen" whenever boot to EFI Shell
// [Files]  		Boot.c and minisetup.h
// 
// 34    12/29/11 12:00p Arunsb
// [TAG]  		EIP74871
// [Category]  	Improvement
// [Description]  	When UEFI booting to windows, a cursor is displayed on
// the lower right hand corner of the screen
// [Files]  		Screen attribute changed to EFI_BACKGROUND_BLACK | EFI_WHITE
// 
// 33    12/14/11 12:14p Premkumara
// [TAG]  		EIP77400
// [Category]  	Improvement
// [Description]  	Need to do "Clear Screen" whenever boot to EFI Shell
// [Files]  		Boot.c
// 
// 32    12/10/11 4:43a Arunsb
// Corrected the header
// 
// 31    12/08/11 12:29p Arunsb
// UpdateDriverVariables function used properly
// 
// 30    11/30/11 1:20p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 29    11/24/11 5:26a Arunsb
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		boot.c
// 
// 28    11/16/11 11:17a Madhans
// [TAG]  		EIP75736
// [Category]  	Improvement
// [Description]  	To avoid flicks when booting UEFI OS for seamless boot.
// [Files]  		Boot.c 
// Tseadvanced.c
// 
// 27    11/13/11 12:30p Arunsb
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
// 26    11/02/11 10:43a Arunsb
// [TAG]  		EIP69884
// [Category]  	New Feature
// [Description]  	Support for UEFI Load Options - USB WWID
// [Files]  		boot.c
// 
// 25    11/01/11 3:53p Rajashakerg
// [TAG]  		EIP71223
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	TSE label 4.6.2_TSE_2_14_1219 has issues in Sandybridge
// platform
// [Solution]  	Fixed the issue by handling the return status when there
// is no valid boot option to boot.
// [Files]  		BootOnly\boot.c
// 
// 24    10/31/11 9:47a Rajashakerg
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
// 23    9/24/11 4:41a Arunsb
// [TAG]  		EIP70096
// [Category]  	Improvement
// [Description]  	Exposing the Handle of the image that's being launched
// for boot.
// This will help other elinks to do the processing. Needed for CsmOptOut
// Feature.
// [Files]  		BootOnly\boot.c
// 
// 22    7/19/11 11:53a Arunsb
// [TAG]  		EIP65320
// [Category]  	Improvement
// [Description]  	Board module hook for LoadImage failure
// [Files]  		boot.c and commonhelper.c
// 
// 21    7/11/11 4:50p Arunsb
// [TAG]  		EIP64295 
// [Category]  	New Feature
// [Description]  	Support for software created boot entry for USB.
// CheckDevSupShortFormPath function added to check whether the boot
// option supports short-form device path for USB class(Table 60) device
// path.
// Goto statement removed in CheckDevSupShortFormPath function.
// [Files]  		boot.c
// 
// 20    7/11/11 3:24p Arunsb
// [TAG]  		EIP64295 
// [Category]  	New Feature
// [Description]  	Support for software created boot entry for USB.
// CheckDevSupShortFormPath function added to check whether the boot
// option supports short-form device path for USB class(Table 60) device
// path.
// [Files]  		boot.c
//
// 19    6/30/11 4:13a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Boot device repair operation performed.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
//
// 18    6/29/11 6:12a Arunsb
// [TAG]           EIP 62631, 60128
// [Category]      New Feature
// [Description]   Hot key boot option in TSE as per UEFI spec. section
// 3.1.6.
// [Files]         AMITSE.sdl, CommonHelper.c, commonoem.c, commonoem.h,
// boot.c, hiistring20.c and hiistring21.c.
//
// 17    6/22/11 2:40p Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Support for Hot key boot option in TSE as per UEFI
// spec. section 3.1.6.
// [Files]         AMITSE.sdl, CommonHelper.c, commonoem.c, commonoem.h,
// boot.c, hiistring20.c and hiistring21.c.
//
// 16    6/20/11 3:55p Arunsb
// [TAG]           EIP57660
// [Category]    New Feature
// [Description] Non-removable media boot behavior as described in UEFI
// specification v 2.3.1, p. 3.4.1.
// [Files]           amitse.sdl, bootflow.c, bootflow.h, commonoem.c,
// boot.c and protocol.c
//
// 15    6/20/11 11:45a Rajashakerg
// [TAG]  		EIP59417
// [Category]  	New Feature
// [Description]  	Spport LOAD_OPTION_HIDDEN option in TSE
// [Files]  		boot.h, AMITSE.sdl, CommonHelper.c, bbs.c, boot.c,
// minisetup.h, special.c, callback.c
//
// 14    6/10/11 2:35p Arunsb
// [TAG]  		EIP57660
// [Category]  	New Feature
// [Description]  	Non-removable media boot behavior as described in UEFI
// specification v 2.3.1, p. 3.4.1.2
// [Files]  		boot.c, bootflow.c and bootflow.h
//
// 13    6/04/11 1:49p Arunsb
// [TAG]             EIP58954
// [Category]      New Feature
// [Description]  Wrapper function added for InvalidateStatusInBgrt
// function.
// [Files]            Postmgmt.c, boot.c, logo.c commonoem.c and
// commonhelper.c
//
// 12    5/29/11 12:04p Arunsb
// [TAG]           EIP58954
// [Category]      New Feature
// [Description]   Quiet boot logo's only added for BGRT. BGRT status
// field cleared if any changes happened in screen other than displaying
// the image.
// [Files]         Postmgmt.c, boot.c, logo.c commonoem.c and
// commonhelper.c
//
// 11    3/15/11 5:15a Rajashakerg
// [TAG]  		EIP51671
// [Category]  	New Feature
// [Description]  	 Boot overide menu devices are not disable
// [Files]  		boot.c, minisetup.h, special.c, minisetupext.c, AMITSE.sdl,
// boot.h, CommonHelper.c
//
// 10    2/04/11 4:36p Mallikarjunanv
// UpdateBootVariables() function added to update boot and BBS Order
// varaibles.
//
// 9     1/14/11 6:05p Madhans
// [TAG]  		EIP52153
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	If new device added once we boot after reboot, Booting
// using BBS popup might Crash
// [RootCause]  	The BootOrder Varaible is read when TSE entry and And it
// is not synced with Cache value.
// [Solution]  	Update the BootOrder,BBSOrder variable cache, when we
// handle boot Variables in TSE
// [Files]  		boot.c
//
// 8     12/02/10 2:33p Madhans
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
// 7     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
//
// 13    9/13/10 3:10p Madhans
// [TAG]    	EIP41137
// [Category]	Improvement
// [Symptom]	Boot errors status reported for TSE loaded also
// [RootCause]	Fix done in Boot.c. To report the error status only for
// boot options.
//
// 12    9/08/10 6:53a Mallikarjunanv
// EIP-42080: TSE updates with respect to Fast Boot Support
//
// 11    8/23/10 4:00p Blaines
// In the function _BootSetBootManagerVariables, the assert that was
// ensuring that all disabled boot options were forced to the end of the
// list, was left outside of the code block (it was causing a hang  after
// inserting a new boot device, then re-booting).
//
// Only process the assert if the preserve disabled boot option order is
// disabled.
//
// 10    7/28/10 4:46a Mallikarjunanv
// EIP-29951: TSE Device Path Name support updated
//
// 9     4/13/10 6:01p Madhans
// Eip: 33100 To create new hook for BootNowLaunching. (From bbsPopoup and
// Boot override menu).
//
// 8     3/23/10 5:08p Blaines
// Preseve the order of disabled BBS boot devices.
//
// 7     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
//
// 6     2/15/10 10:10p Madhans
// To avoid Compilation issues
//
// 5     1/29/10 4:37p Madhans
// To not to depend on ConsoleControl and ConOut.
//
// 4     1/29/10 4:34p Madhans
// To avoid compiler warnings.
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
// 2     5/19/09 6:36p Madhans
// updated the code getting language codes
//
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
//
// 6     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
//
// 5     3/31/09 3:33p Madhans
// UnicodeCollection2 protocol support.
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
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		BOOT.C
//
// Description:	This file contains code for Boot management
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include EFI_PROTOCOL_DEFINITION (BlockIo)
#include EFI_PROTOCOL_DEFINITION (UsbIo)
#include EFI_PROTOCOL_DEFINITION (DiskIo)
#define BOOT_OPTION_ALLOC_UNIT  10
//////////////////////////////////////
//Extern Variables
//////////////////////////////////////
extern UINTN        	gDelOptionCount;
extern BOOT_DATA    	*gDelBootData;
extern UINT32       	gBootFlow;
extern UINTN 			CurrentScreenresolutionX, CurrentScreenresolutionY; //EIP-88430
//////////////////////////////////////
//Internal Variable Declarations
//////////////////////////////////////
UINTN		        		gBootOptionCount;
EFI_GUID	        		gBootNowCountGuid 	= 	BOOT_NOW_COUNT_GUID;
UINT16		        *gBBSDisabled 			= 	L"Disabled in BBS Order";
UINTN		        		gLangCount;
BOOT_DATA		    	*gBootData;
LANGUAGE_DATA	    	*gLanguages;
EFI_HANDLE          	gCurrentBootHandle 	= 	NULL;
EFI_EVENT				gShellLaunchEvent 	= NULL;		//EIP 77400 Clearing the screen for shell boot
EFI_EVENT				gShell20LaunchEvent 	= NULL;	//EIP158989 For shell2.0
UINT16 					DISABLED_BOOT_OPTION; //EIP-97704
UINT16 					DISABLED_DRIVER_OPTION; //EIP-97704
UINTN						gDriverOptionCount;//EIP70421 & 70422 Support for driver order
BOOT_DATA				*gDriverData;//EIP70421 & 70422 Support for driver order
BOOLEAN              gBrowserCallbackEnabled = FALSE; //EIP113266 Allow external drivers to change ASL cache only if it's TRUE; ignore browser callback otherwise
//////////////////////////////////////
//Internal Functions Declarations
//////////////////////////////////////
EFI_DEVICE_PATH_PROTOCOL *_BootBuildFVDevicePath( UINT32 *index, EFI_GUID *guidPtr );
EFI_DEVICE_PATH_PROTOCOL *_BootBuildFileDevicePath( UINT32 *index, CHAR16 *fileName );
EFI_DEVICE_PATH_PROTOCOL* _DiscoverPartition(EFI_DEVICE_PATH_PROTOCOL *DevicePath);
VOID        _BootSetBootManagerVariables(VOID);
VOID        _BootInstallLoadOptions( EFI_HANDLE handle, VOID *Options, UINTN OptionSize );
EFI_STATUS  _BootLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath, VOID *Options, UINTN OptionSize, BOOLEAN ValidBootOption );
UINT16      _BootSetBootNowCount(VOID);
CHAR16      *TseGetUefiDevPathString(EFI_DEVICE_PATH_PROTOCOL *DevPath);
VOID        InvalidateStatusInBgrtWrapper (VOID);
VOID        UninstallBgrtWrapper(VOID);//EIP81830 Support to uninstall the BGRT on legacy boot
VOID        FormHotBootKeys (CHAR16 *VarName);
VOID        RefreshBootKeysDetails (VOID);
VOID        FreeExtraKeyMemories (VOID);
EFI_STATUS	CheckForDeviceNeedRepair (EFI_DEVICE_PATH_PROTOCOL *);
EFI_HANDLE	CheckDevSupShortFormPath (EFI_DEVICE_PATH_PROTOCOL *);
VOID 			LegacyBootFailHook(EFI_STATUS);
VOID			UefiBootFailHook (EFI_STATUS);
VOID			UpdateBootVariables ();
VOID			FixHiddenOptions (BOOLEAN, UINT16 **, UINTN);
VOID 			_SetDriverManagerVariables (VOID);//EIP70421 & 70422 Support for driver order
VOID 			UpdateDriverVariables ();//EIP70421 & 70422 Support for driver order
UINT32  		ShellTextMode (VOID);//EIP 94205 : OEM needs Token to assign the display mode of SHELL.
UINTN   		PISpecVersion(VOID);//EIP-103540

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootGetBootOptions
//
// Description:	This function collects all the boot options, both efi
//              and legacy boot options, that are present in the
//              system and sets various boot manager variables that
//              are used to expand boot manager questions.
//
// Input:		VOID
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BootGetBootOptions( VOID )
{
    EFI_STATUS	Status;
    UINTN		AllocatedCount;

#ifndef STANDALONE_APPLICATION
    CHAR16		Pattern[]=L"boot[0-9a-f][0-9a-f][0-9a-f][0-9a-f]";
    CHAR16		KeyPattern[]=L"Key[0-9a-f][0-9a-f][0-9a-f][0-9a-f]";
    UINTN		OldVarNameSize;
    UINTN		VarNameSize;
    CHAR16		*VarName;
    EFI_GUID	VarGuid;
	VOID *		UnicodeInterface;
    UINTN		size=0, Length = 2;
    UINT8		*bufPtr;
    BOOT_OPTION *buffer;
    BOOT_DATA   *dataPtr;
	UINT32      *conditionPtr;
	UINT16      *BootOrder;
    CHAR16      *String=NULL;
//    UINTN       KeyVarNameSize = 0;
#endif //STANDALONE_APPLICATION
	BOOLEAN IsFastBoot=FALSE;
//EIP70421 & 70422 Support for driver order starts
	UINTN		DriverAllocatedCount;
    CHAR16		DriverPattern[] = L"Driver[0-9a-f][0-9a-f][0-9a-f][0-9a-f]";
	BOOLEAN 	BootOption = FALSE;
	BOOLEAN 	DriverOption = FALSE;
//EIP-97704 Starts
	UINT16 		jIndex 		= 	0;
	DISABLED_BOOT_OPTION 	= 	0xFFFF;
	DISABLED_DRIVER_OPTION 	= 	0xFFFF;
//EIP-97704 Ends
	DriverAllocatedCount = gDriverOptionCount = 0;
//EIP70421 & 70422 Support for driver order ends
    AllocatedCount = gBootOptionCount = 0;
#ifndef STANDALONE_APPLICATION
	Status = InitUnicodeCollectionProtocol(&UnicodeInterface);
    if(EFI_ERROR(Status))
        return Status;

    RefreshBootKeysDetails ();
    //start with a size of 80 bytes
    VarNameSize = 80;
    OldVarNameSize = VarNameSize;
    VarName = EfiLibAllocateZeroPool(VarNameSize);
    conditionPtr = VarGetNvramName( L"BootFlow", &_gBootFlowGuid, NULL, &size );
    if ( (conditionPtr != NULL) && (BOOT_FLOW_CONDITION_FAST_BOOT == *conditionPtr) )
	{
		IsFastBoot = TRUE;
		BootOrder = HelperGetVariable(VARIABLE_ID_BOOT_ORDER, L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
		VarNameSize = ((EfiStrLen(L"BOOTXXXX")+1)*2);
		VarName = EfiLibAllocateZeroPool(VarNameSize);
		SPrint (VarName, VarNameSize, L"Boot%04X",BootOrder[0] );
	    MemFreePointer((VOID **) &BootOrder);
	    MemFreePointer((VOID **) &conditionPtr);
	}
    do
    {
		if (!IsFastBoot)
		{
			Status = gRT->GetNextVariableName (&VarNameSize,
											VarName,
											&VarGuid);
			if (Status == EFI_BUFFER_TOO_SMALL)
			{
				//Allocate correct size
				VarName = MemReallocateZeroPool (VarName,
												OldVarNameSize,
												VarNameSize);
				OldVarNameSize = VarNameSize;
				continue;
			}
		}
//        KeyVarNameSize = VarNameSize;                   													//EIP: 62631 For hot key boot
        if ( (VarNameSize == ((EfiStrLen (L"BOOTXXXX")+1)*2)) || (VarNameSize == ((EfiStrLen (L"DRIVERXXXX")+1)*2)) )	        //Find if this variable is one of L"BOOTXXXX" or L"DRIVERXXXX"
        {
			if (MetaiMatch (UnicodeInterface, VarName, Pattern))											//The buffer is definatly a boot#### option
			{
                size = 0;
                buffer = VarGetNvramName (VarName, &gEfiGlobalVariableGuid, NULL, &size);
                if (buffer)																					//Variable exists. Store details in global array.
                {
                    if (gBootOptionCount >= AllocatedCount)													//Check if enough size has been already allocated
                    {
                        gBootData = MemReallocateZeroPool (gBootData, AllocatedCount * sizeof(BOOT_DATA), (AllocatedCount + BOOT_OPTION_ALLOC_UNIT) * sizeof(BOOT_DATA));
                        if (NULL == gBootData)
						{
                            return EFI_UNSUPPORTED;
						}
                        AllocatedCount += BOOT_OPTION_ALLOC_UNIT;
                    }
					dataPtr = &(gBootData [gBootOptionCount]);
					HexStringToBuf(
						(UINT8 *)(&(dataPtr->Option)),
						&Length,
						&(VarName[4]),
						NULL);
					BootOption = TRUE;
					gBootOptionCount ++;
				}
			}
			else if (MetaiMatch (UnicodeInterface, VarName, DriverPattern))	//EIP70421 Support for Driver Order
			{
                size = 0;
                buffer = VarGetNvramName (VarName, &gEfiGlobalVariableGuid, NULL, &size);
                if (buffer)		//Variable exists. Store details in global array.
                {
                    if (gDriverOptionCount >= DriverAllocatedCount)		//Check if enough size has been already allocated
                    {
                        gDriverData = MemReallocateZeroPool (gDriverData, DriverAllocatedCount * sizeof (BOOT_DATA), (DriverAllocatedCount + BOOT_OPTION_ALLOC_UNIT) * sizeof(BOOT_DATA));
                        if (NULL == gDriverData)
						{
                            return EFI_UNSUPPORTED;
						}	
                        DriverAllocatedCount += BOOT_OPTION_ALLOC_UNIT;
                    }
					dataPtr = &(gDriverData [gDriverOptionCount]);
					HexStringToBuf(
						(UINT8 *)(&(dataPtr->Option)),
						&Length,
						&(VarName[6]),
						NULL);
					DriverOption = TRUE;
					gDriverOptionCount ++;
				}
			}
			else
			{
				goto _NextVariable;					//Jumping for next variable iteration
			}
			if (DriverOption || BootOption)			//Common code for both driver and boot options
			{
				dataPtr->Active = buffer->Active;
				dataPtr->Name = StrDup (buffer->Name);
				bufPtr = (UINT8 *)((CHAR16 *)buffer->Name + EfiStrLen( buffer->Name ) + 1);
				dataPtr->DevicePath = EfiLibAllocateZeroPool( buffer->PathLength );
				if (NULL != dataPtr->DevicePath)
				{
					MemCopy (dataPtr->DevicePath, bufPtr, buffer->PathLength);
				}
				bufPtr += buffer->PathLength;
				size -= (UINTN)bufPtr - (UINTN)buffer;
				if (size != 0)
				{
					dataPtr->LoadOptions = EfiLibAllocatePool( size );
					if ( dataPtr->LoadOptions != NULL )
					{
						dataPtr->LoadOptionSize = size;
						MemCopy( dataPtr->LoadOptions, bufPtr, size );
					}
				}
				if (BootOption)
				{
	                //In case of DEVIE PATH support, to reset the name using device path
	                String = TseGetUefiDevPathString(dataPtr->DevicePath);
	                if (NULL != String)
					{
	                    // For UEFI boot options, Prefix the string with "UEFI: "
	                    MemFreePointer( (VOID **)&(dataPtr->Name) );
	                    dataPtr->Name = EfiLibAllocateZeroPool( EfiStrLen( String ) + EfiStrLen(L"UEFI: ")+ 1 );
	                    EfiStrCpy(dataPtr->Name, L"UEFI: ");
	                    EfiStrCat(dataPtr->Name, String);
	                }
	            }
				MemFreePointer( (VOID **)&buffer );
			}
_NextVariable:
			BootOption = DriverOption = FALSE;		//Getting ready for next iteration
        }
        else if (VarNameSize == ((EfiStrLen(L"keyXXXX")+1)*2))		//Boot, Driver and Key are different length so handling in else if cases
        {
            if (MetaiMatch (UnicodeInterface, VarName, KeyPattern))
            {
                FormHotBootKeys (VarName);
            }
        }
		// Only one Boot options is valid in FastBoot case
		if(IsFastBoot)
			break;
        //reset the size of this buffer to what has been allocated for it
        VarNameSize = OldVarNameSize;

    }while(Status != EFI_NOT_FOUND);

#endif //STANDALONE_APPLICATION

//EIP-97704 Starts
	//For Boot#### variable
	for ( jIndex = 0; jIndex < gBootOptionCount; jIndex++ )
	{
		if ( gBootData[jIndex].Option == DISABLED_BOOT_OPTION )
		{
			DISABLED_BOOT_OPTION--;//Changing the value based on the available of BOOT#### variable
			jIndex	=	-1;
			continue;
		}
	}
	//For Driver#### variable
	for ( jIndex = 0; jIndex < gDriverOptionCount; jIndex++ )
	{
		if ( gDriverData[jIndex].Option == DISABLED_DRIVER_OPTION )	
		{
			DISABLED_DRIVER_OPTION--;//Changing the value based on the available of DRIVER#### variable
			jIndex	=	-1;
			continue;
		}
	}
//EIP-97704 Ends
    //Free unused memory
    if (gBootOptionCount < AllocatedCount)
        gBootData = MemReallocateZeroPool(gBootData, AllocatedCount * sizeof (BOOT_DATA), gBootOptionCount * sizeof (BOOT_DATA));

    if (gDriverOptionCount < DriverAllocatedCount)
        gDriverData = MemReallocateZeroPool(gDriverData, DriverAllocatedCount * sizeof (BOOT_DATA), gDriverOptionCount * sizeof (BOOT_DATA));

    FreeExtraKeyMemories ();
    //Set boot manager variables
	if(!IsFastBoot)
	{
	    _BootSetBootManagerVariables ();
		_SetDriverManagerVariables ();
	}
    Status = EFI_SUCCESS;
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootLaunchBootOption
//
// Description:	This function launches the boot option supplied
//
// Input:		u16Option: BootOption to be launched
//              pOrder: The order in which to set BBS priorities
//              u16OrderCount: No of options in pOrder
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BootLaunchBootOption(UINT16 u16Option, UINT16 *pOrder, UINTN u16OrderCount)
{
    EFI_STATUS	status = EFI_NOT_FOUND;
    UINT16		u16BootCurrent;

    BOOT_DATA	*pBootData = NULL;

    pBootData = BootGetBootData(u16Option);
    if (pBootData)
    {
        //Set BootCurrent
        u16BootCurrent = pBootData->Option;
        VarSetNvramName(L"BootCurrent",
                &gEfiGlobalVariableGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                &(u16BootCurrent),
                sizeof(u16BootCurrent));
        if( gBootFlow != BOOT_FLOW_CONDITION_FAST_BOOT) {
        	CsmBBSSetBootPriorities(pBootData, pOrder, u16OrderCount);
        }
        status = _BootLaunchDevicePath(pBootData->DevicePath, pBootData->LoadOptions, pBootData->LoadOptionSize,TRUE);

        //clear BootCurrent
        VarSetNvramName(L"BootCurrent",
                &gEfiGlobalVariableGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                &(u16BootCurrent),
                0);
    }

    return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootGetBootData
//
// Description:	Finds and returns internal data structure BOOT_DATA
//              for a given boot option number.
//
// Input:		Option: Option number for which BOOT_DATA is needed
//
// Output:		Returns pointer to BOOT_DATA if found. Returns NULL
//              if BOOT_DATA not found.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOT_DATA *BootGetBootData( UINT16 Option )
{
    UINTN i;

    for ( i = 0; i < gBootOptionCount; i++ )
    {
        if ( gBootData[i].Option == Option )
            return &gBootData[i];
    }

    return NULL;
}

//EIP70421 & 70422  Support for driver order
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DriverGetDriverData
//
// Description:	Finds and returns internal data structure BOOT_DATA
//              for a given Driver option number.
//
// Input:		Option: Option number for which BOOT_DATA is needed
//
// Output:		Returns pointer to BOOT_DATA if found. Returns NULL
//              if BOOT_DATA not found.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOT_DATA *DriverGetDriverData (UINT16 Option)
{
    UINTN i;

    for ( i = 0; i < gDriverOptionCount; i++ )
    {
        if ( gDriverData[i].Option == Option )
            return &gDriverData[i];
    }
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootGetOptionName
//
// Description:	Provides the unicode name for the given boot option
//              in the form of internal data structure BOOT_DATA.
//
// Input:		bootData: BOOT_DATA struct for which unicode name is
//              needed.
//
// Output:		Returns unicode string corresponding to the provided
//              BOOT_DATA. If the BOOT_DATA provided is for legacy
//              option then the name for the first legacy option in
//              that category is returned.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *BootGetOptionName( BOOT_DATA *bootData)
{
    if ( BBSValidDevicePath(bootData->DevicePath) ) {
		return CsmBBSBootOptionName(bootData);
    }
    return bootData->Name;
}

//EIP70421 & 70422  Support for driver order
//<AMI_PHDR_START>
//------------------------------------------------------------------------------------
// Procedure:	DriverGetOptionName
//
// Description:	Provides the unicode name for the given driver option
//              in the form of internal data structure BOOT_DATA.
//
// Input:		DriverData: BOOT_DATA struct for which unicode name is
//              needed.
//
// Output:		Returns unicode string corresponding to the provided BOOT_DATA
//
//------------------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *DriverGetOptionName (BOOT_DATA *DriverData)
{
    return DriverData->Name;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootGetBootNowName
//
// Description:	Provides the unicode name for the given boot option.
//
// Input:		value: boot option for which unicode name is needed
//
// Output:		Returns unicode string corresponding to the provided
//              boot option.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *BootGetBootNowName( UINT16 value, BOOLEAN ShowAllBBSDev, BOOLEAN TseBootNowInBootOrde)
{
    UINT16	*BootOrder=NULL;
    UINTN	size = 0;
    UINTN	i,j,k;
    UINTN	count;

    BOOT_DATA *bootData;

	if((!ShowAllBBSDev) && (!TseBootNowInBootOrde))
		if(gBootData == NULL)
			return NULL;
		else
		{
			if(gLoadOptionHidden && (gBootData[value].Active & LOAD_OPTION_HIDDEN))
				return NULL;//EIP 89483 : Cheking for the load option hidden presence in the Boot option

			return BootGetOptionName(&(gBootData[value]));
		}
	if(TseBootNowInBootOrde)
	{
		BootOrder = HelperGetVariable(VARIABLE_ID_BOOT_ORDER, L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
  		//EIP-75352 Suppress the warnings from static code analyzer
		if(NULL == BootOrder){
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
	}

	if(ShowAllBBSDev)
	{
	    count = 0;
	    for(i=0;i<gBootOptionCount;i++)
	    {
			if(TseBootNowInBootOrde) {
		        bootData = BootGetBootData(BootOrder[i]);
				//EIP-75352 Suppress the warnings from static code analyzer
				if(NULL == bootData){
					return NULL;
				}
			}
			else {
	     		bootData = gBootData + i;
			}

	        if ( BBSValidDevicePath(bootData->DevicePath) )
	        {
	            if((value >= count) && (value < (count+bootData->LegacyDevCount)))
	            {
					if(TseBootNowInBootOrde)
		                MemFreePointer((VOID **) &BootOrder);
				if (gLoadOptionHidden && ((bootData->Active & LOAD_OPTION_HIDDEN)!= 0))
 					return NULL;
				
	                return bootData->OrderList[value-count].Name;
	            }

	            count+=bootData->LegacyDevCount;
	        }
	        else {
	            if(value == count)
	            {
					if(TseBootNowInBootOrde)
		                MemFreePointer((VOID **) &BootOrder);
					if (gLoadOptionHidden && ((bootData->Active & LOAD_OPTION_HIDDEN)!= 0))
 					 return NULL;
	                return bootData->Name;
	            }
	            count++;
	        }
	    }
 		return NULL;
	}
	else {
	    bootData = BootGetBootData(BootOrder[value]);
	    MemFreePointer((VOID **) &BootOrder);
		if (gLoadOptionHidden && ((bootData->Active & LOAD_OPTION_HIDDEN)!= 0))
				return NULL;//EIP 89483 : Cheking for the load option hidden presence in the Boot option

	    return BootGetOptionName(bootData);
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootGetLanguages
//
// Description:	Finds the languages that the firmware supports.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetBootLanguages( VOID )
{
    CHAR16	*langString;
    CHAR8	*langCodes, *langPtr;
    UINTN	i, count, size = 0;

    langCodes = VarGetNvramName( L"LangCodes", &gEfiGlobalVariableGuid, NULL, &size );
    count = size /3;

    if ( size == 0 )
    {
	    langCodes = VarGetNvramName( L"Lang", &gEfiGlobalVariableGuid, NULL, &size );
		if ( size != 0) {
		    count = 1;
		}
		else {
	        gLanguages = EfiLibAllocateZeroPool( sizeof(LANGUAGE_DATA) );
	        if ( gLanguages == NULL )
	            return;

			gLanguages[0].LangCode = StrDup8("eng");
			gLanguages[0].Unicode = StrDup(L"eng");
	        gLangCount = 1;
	        langString = HiiGetStringLanguage( (VOID*)(UINTN)INVALID_HANDLE, 1, gLanguages[0].Unicode );
	        gLanguages[0].Token = HiiAddString( gHiiHandle, langString );
	        gLanguages[0].LangString = langString;
	        return;
		}
    }

    gLanguages = EfiLibAllocateZeroPool( count * sizeof(LANGUAGE_DATA) );
    if ( gLanguages == NULL )
        return;

    for ( langPtr = langCodes, i = 0; i < count; i++, langPtr += 3 )
    {
		gLanguages[i].LangCode = EfiLibAllocateZeroPool( 4 * sizeof(CHAR8));
        MemCopy( gLanguages[i].LangCode, langPtr, 3 * sizeof(CHAR8) );
		gLanguages[i].Unicode = StrDup8to16(gLanguages[i].LangCode);
    }

    gLangCount = count;

    for ( langPtr = langCodes, i = 0; i < count; i++, langPtr += 3 )
    {
        langString = HiiGetStringLanguage( (VOID*)(UINTN)INVALID_HANDLE, 1, gLanguages[i].Unicode );
        gLanguages[i].Token = HiiAddString( gHiiHandle, langString );
        gLanguages[i].LangString = langString;
    }

    MemFreePointer( (VOID **)&langCodes );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootGetLanguages
//
// Description:	Finds the languages that the firmware supports.
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetPlatformBootLanguages( VOID )
{
    CHAR16	*langString;
    CHAR8	*langCodes, *langPtr;
    UINTN	i = 0, count=0, size = 0, pos = 0;

    langCodes = VarGetNvramName( L"PlatformLangCodes", &gEfiGlobalVariableGuid, NULL, &size );
    if(langCodes != NULL)
		count = GetTokenCount(langCodes);

    if ((0 == size) || (NULL == langCodes))
    {
	    langCodes = VarGetNvramName( L"PlatformLang", &gEfiGlobalVariableGuid, NULL, &size );
	    if ( size  != 0 ) {
			count=1;
		}
		else {
		        gLanguages = (LANGUAGE_DATA *)EfiLibAllocateZeroPool( sizeof(LANGUAGE_DATA) );
	        if ( gLanguages == NULL )
	            return;

	        gLanguages[0].LangCode = StrDup8("en-US");
	        gLanguages[0].Unicode = StrDup(L"en-US");

	        gLangCount = 1;
	        langString = HiiGetStringLanguage( (VOID*)(UINTN)INVALID_HANDLE, 1, gLanguages[0].Unicode );
	        gLanguages[0].Token = HiiAddString( gHiiHandle, langString );
	        gLanguages[0].LangString = langString;
	        return;
	    }
	}

    gLanguages = EfiLibAllocateZeroPool( count * sizeof(LANGUAGE_DATA) );
    if ( gLanguages == NULL )
        return;

    for ( langPtr = langCodes, i = 0; i < count; i++ )
    {
        gLanguages[i].LangCode = GetTokenString(langPtr, &pos);
        gLanguages[i].Unicode  = StrDup8to16(gLanguages[i].LangCode);
        langString = HiiGetStringLanguage( INVALID_HANDLE, 1, gLanguages[i].Unicode );
        gLanguages[i].Token = HiiAddString( gHiiHandle, langString );
        gLanguages[i].LangString = langString;

        langPtr += pos + 1;
    }

    gLangCount = count;
    MemFreePointer( (VOID **)&langCodes );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootLaunchBootNow
//
// Description:	Launches the boot option provided.
//
// Input:		index: The nth option in the boot now menu.
//				ShowAllBbsDev - SETUP_SHOW_ALL_BBS_DEVICES
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BootLaunchBootNow( UINT16 index, BOOLEAN ShowAllBbsDev )
{

    EFI_STATUS	Status = EFI_OUT_OF_RESOURCES;
    BOOLEAN		bLegacyBoot = FALSE;
    UINT16		count = 0, BootCurrent;
    UINT16		*BootOrder;
    UINTN		i = 0;

    BOOT_DATA *bootData=NULL;

	ProcessProceedToBootNowHook();

    BootOrder = BootNowinBootOrderInit();

	if(ShowAllBbsDev)
	{
	    for(i=0;i<gBootOptionCount;i++)
	    {
			bootData = BootGetBootNowBootData(gBootData,BootOrder,i);
			//EIP-75352 Suppress the warnings from static code analyzer
			if(NULL == bootData){
				continue;
			}
	        if ( BBSValidDevicePath(bootData->DevicePath) )
	        {
	            if((index >= count) && (index < (count+bootData->LegacyDevCount)))
	            {
	                bLegacyBoot = TRUE;
	                break;
	            }
	            else
	                count=count+(UINT16)(bootData->LegacyDevCount);
	        }
	        else
	        {
	            if(index == count)
	                break;
	            count++;
	        }
	    }
	}
	else
	{
		if(0 == gBootOptionCount)//EIP 71223: If there is no valid boot option present, returning EFI_NOT_FOUND. 
	        return EFI_NOT_FOUND;
		bootData = BootGetBootNowBootData(gBootData,BootOrder,index);
	}

	if(BootOrder!=NULL)
		MemFreePointer((VOID **) &BootOrder);

	//EIP-75352 Suppress the warnings from static code analyzer
	if(NULL == bootData){
		return EFI_NOT_FOUND;
	}

	if(ShowAllBbsDev)
	{
	    if(i == gBootOptionCount)
	        return Status;

	    //Boot bootData and device index-count
	    //set bbs priorities
	    if(bLegacyBoot)
		{
			Status = CsmBBSSetBootNowPriority(bootData,index-count,ShowAllBbsDev);
			if(EFI_ERROR( Status )) //EIP-93797
				return EFI_UNSUPPORTED;
		}
	}

    //Set BootCurrent
    BootCurrent = bootData->Option;
    VarSetNvramName(L"BootCurrent",
            &gEfiGlobalVariableGuid,
            EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
            &(BootCurrent),
            sizeof(BootCurrent));
	if(!ShowAllBbsDev)
	{
	    if(BBSValidDevicePath(bootData->DevicePath))
		{
	        Status = CsmBBSSetBootNowPriority(bootData,0,ShowAllBbsDev);
			if(EFI_ERROR( Status )) //EIP-93797
				return EFI_UNSUPPORTED;
		}	
	}
    Status = _BootLaunchDevicePath( bootData->DevicePath, bootData->LoadOptions, bootData->LoadOptionSize,TRUE );
    //clear BootCurrent
    VarSetNvramName(L"BootCurrent",
            &gEfiGlobalVariableGuid,
            EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
            &(BootCurrent),
            0);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootLaunchGuid
//
// Description:	Launches the guided file from FV.
//
// Input:		guid: Guid of the file to be launched.
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BootLaunchGuid( EFI_GUID *guid )
{
    EFI_STATUS	Status = EFI_UNSUPPORTED;
    UINT32		index = 0;

    EFI_DEVICE_PATH_PROTOCOL *devicePath;

    do
    {
        devicePath = _BootBuildFVDevicePath( &index, guid );
        if ( index != (UINT32)-1 )
            Status = _BootLaunchDevicePath( devicePath, NULL, 0,FALSE );

        MemFreePointer( (VOID **)&devicePath );
    }
    while ( ( EFI_ERROR( Status ) ) && ( index != (UINT32)-1 ) );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootLaunchFilename
//
// Description:	Launches the file mentioned in file path from the
//              available FS.
//
// Input:		fileName: Path of the file to be launched.
//
// Output:		Return Status based on errors that occurred in library
//              functions.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS BootLaunchFilename( CHAR16 *fileName )
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT32     index = 0;

    EFI_DEVICE_PATH_PROTOCOL *devicePath;

    do
    {
        devicePath = _BootBuildFileDevicePath( &index, fileName );
        if ( index != (UINT32)-1 )
            Status = _BootLaunchDevicePath( devicePath, NULL, 0,FALSE );

        MemFreePointer( (VOID **)&devicePath );
    }
    while ( ( EFI_ERROR( Status ) ) && ( index != (UINT32)-1 ) );

    return Status;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------
// Procedure:	FixHiddenOptions
//
// Description:	Function to move the hidden option at last of the boot order
//
// Input:		UINT16 ** => Boot order to be reformed
//
// Output:		VOID
//
//--------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FixHiddenOptions (BOOLEAN Option, UINT16 **Order, UINTN OptionCount)
{
	UINTN iIndex = 0;
	UINTN jIndex = 0;
	UINT16 TempBootOption = 0;
	BOOT_DATA   *pBootData;

	if (0 == OptionCount)
	{
		return;
	}
	for (iIndex = 0; iIndex < OptionCount-1; iIndex ++)
	{
		if (BOOT_ORDER_OPTION == Option)
		{
			pBootData = BootGetBootData ((*Order) [iIndex]);
		}
		else
		{
			pBootData = DriverGetDriverData ((*Order) [iIndex]);
		}
		if (pBootData)
		{
			if (pBootData->Active & LOAD_OPTION_HIDDEN)
			{
				for (jIndex = iIndex+1; jIndex < OptionCount; jIndex ++)
				{
					if (BOOT_ORDER_OPTION == Option)
					{
						pBootData = BootGetBootData ((*Order) [jIndex]);
					}
					else
					{
						pBootData = DriverGetDriverData ((*Order) [jIndex]);
					}
					if (!(pBootData->Active & LOAD_OPTION_HIDDEN))
					{
						TempBootOption = (*Order) [iIndex];
						(*Order) [iIndex] = (*Order) [jIndex];
						(*Order) [jIndex] = TempBootOption;
						break;
					}
				}
			}
		}
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BootSetBootManagerVariables
//
// Description:	function to set the variables for the boot manager
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _BootSetBootManagerVariables(VOID)
{
    UINT16	*NewBootOrder, *BootOrder, count;
    UINTN	size=0, i=0, j=0, k=0, BootOrderCount;

    EFI_GUID 	BootManGuid = BOOT_MANAGER_GUID;
    BOOT_DATA   *pBootData;

    //Correct BootOrder variable if necessary
    NewBootOrder = NULL;
    if(gBootOptionCount)
        NewBootOrder = (UINT16 *)EfiLibAllocateZeroPool(gBootOptionCount * sizeof(UINT16));

    BootOrder = (UINT16 *)VarGetNvramName( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
    BootOrderCount = size/sizeof(UINT16);

    //Get all the enabled boot options in the boot order
    for(i = 0; i < BootOrderCount; i++)
    {
        pBootData = BootGetBootData(BootOrder[i]);
        if(pBootData)
        {
	  	    if(IsPreservedDisabledBootOptionOrder())
		    {	 //EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
				/*if(gLoadOptionHidden && (pBootData->Active & LOAD_OPTION_HIDDEN))
				{
					j++;
					continue;
				}*/
				NewBootOrder[j] = BootOrder[i];
	   			j++;
		    }
		    else if(pBootData->Active & LOAD_OPTION_ACTIVE)
	        {	 //EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
				/*if(gLoadOptionHidden && (pBootData->Active & LOAD_OPTION_HIDDEN))
				{
					j++;
					continue;
				}*/
	            NewBootOrder[j] = BootOrder[i];
	            j++;
	        }
        }
    }

    //Append all options that are enabled but not included in
    //BootOrder. FCFS used.
    for(i=0; i < gBootOptionCount; i++)
    {
        if(gBootData[i].Active & LOAD_OPTION_ACTIVE)
        {
            //Check presence in boot order
            for(k=0;k<BootOrderCount;k++)
            {
                if(BootOrder[k] == gBootData[i].Option)
                    break;
            }
            if(k >= BootOrderCount)
            {
                //Not present in boot order! Add option
                NewBootOrder[j] = gBootData[i].Option;
                j++;
            }
        }
    }

    //Free Boot order
    MemFreePointer((VOID **)&BootOrder);

    if(!IsPreservedDisabledBootOptionOrder())
    {
        //Put disabled options at the end of NewBootOrder
        for(i=0; i < gBootOptionCount; i++)
        {
            if(!(gBootData[i].Active & LOAD_OPTION_ACTIVE))
            {	 //EIP:59417 - Checking the  LOAD_OPTION_HIDDEN for the boot option
/*				if(gLoadOptionHidden && (gBootData[i].Active & LOAD_OPTION_HIDDEN))
				{
					j++;
					continue;
				}*/
    			NewBootOrder[j] = gBootData[i].Option;
    			j++;
	        }
        }
        ASSERT(j==gBootOptionCount);
    }

    //Set BootOrder Variable with corrected order
	if (gLoadOptionHidden)
	{
		FixHiddenOptions (BOOT_ORDER_OPTION, &NewBootOrder, gBootOptionCount);
	}
    VarSetNvramName(L"BootOrder",
        &gEfiGlobalVariableGuid,
        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
        NewBootOrder,
        gBootOptionCount * sizeof(UINT16));

    //Free NewBootOrder
    MemFreePointer((VOID **)&NewBootOrder);

    //Get BBS devices
    CsmBBSGetDeviceList();

    // Update the BootOrder,BBSOrder Cache From the NVRAM.
    UpdateBootVariables();

    //Set Boot manager variable
    count = (UINT16)gBootOptionCount;
    VarSetNvramName( L"BootManager", &BootManGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &count, sizeof(count) );

    //Set Boot now count
	if(gShowAllBbsDev)
  		count = _BootSetBootNowCount();

    VarSetNvramName( L"BootNowCount", &gBootNowCountGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &count, sizeof(count) );
	UpdateAddDeleteBootVar ();
}

//EIP70421 & 70422  Support for driver order Starts
//<AMI_PHDR_START>
//--------------------------------------------------------------------------------------
// Procedure:	_SetDriverManagerVariables
//
// Description:  Sets DriverManager variable for drivers count and sets DriverOrder
//
// Input:   void
//
// Output:  void
//
//--------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _SetDriverManagerVariables (VOID)
{
	UINT16	*DriverOrder = NULL;
	UINT16	*NewDriverOrder = NULL;
	UINT16	DriverOrderCount = 0;
    UINTN	DriverOrderSize = 0;
	UINTN 	iIndex = 0;
	UINTN 	jIndex = 0;
	UINT16 	Count = 0;
    BOOT_DATA   *pDrvData;			//BOOT_DATA using same structure for driver options too
    EFI_GUID 	DrvMgrGuid = DRIVER_MANAGER_GUID;

	if (gDriverOptionCount)
	{	
	    NewDriverOrder = (UINT16 *)EfiLibAllocateZeroPool (gDriverOptionCount * sizeof(UINT16));
		if (NULL == NewDriverOrder)
		{
			return;
		}
	}
	DriverOrder = (UINT16 *)VarGetNvramName (L"DriverOrder", &gEfiGlobalVariableGuid, NULL, &DriverOrderSize);
	DriverOrderCount = (UINT16)(DriverOrderSize/sizeof(UINT16));
	if ((NULL == DriverOrder) || (0 == DriverOrderSize))
	{
		for (iIndex = 0; iIndex < gDriverOptionCount; iIndex++)			//Forming DriverOrder variable freshly
        {
			if (gDriverData [iIndex].Active & LOAD_OPTION_ACTIVE)
			{
				NewDriverOrder [Count] = gDriverData [iIndex].Option;
				Count ++;
			}
		}
		goto _FormDisableDevices;
	}
	else											//Forming DriverOrder variable with first active and non hidden drivers
	{
	    for (iIndex = 0; iIndex < DriverOrderCount; iIndex ++)
	    {
	        pDrvData = DriverGetDriverData (DriverOrder [iIndex]);
	        if (pDrvData)
	        {													
		    	if ( (pDrvData->Active & LOAD_OPTION_ACTIVE) )				
				{													//Checking for active drivers
	                NewDriverOrder [Count] = DriverOrder [iIndex];
	                Count ++;
	            }
	        }
	    }
	}
	//Append all options that are enabled but not included in
    //DriverOrder. Having same logic as of boot order.
    for(iIndex = 0; iIndex < gDriverOptionCount; iIndex ++)
    {
		if ( (gDriverData [iIndex].Active & LOAD_OPTION_ACTIVE) )
        {
            //Check presence in DriverOrder
            for (jIndex = 0; jIndex < DriverOrderCount; jIndex ++)
            {
                if (DriverOrder [jIndex] == gDriverData [iIndex].Option)
                    break;
            }
            if (jIndex >= DriverOrderCount)
            {
                //Not present in Driver order! Add option
                NewDriverOrder [Count] = gBootData[iIndex].Option;
                Count ++;
            }
        }
    }
_FormDisableDevices:			//Forming disabled drivers last in the newly formed DriverOrder variable.
	for (iIndex = 0; iIndex < gDriverOptionCount; iIndex ++)
	{
		if (!(gDriverData [iIndex].Active & LOAD_OPTION_ACTIVE))
		{	 
			NewDriverOrder [Count] = gDriverData [iIndex].Option;
			Count ++;
		}
	}
	if (gLoadOptionHidden)
	{
		FixHiddenOptions (DRIVER_ORDER_OPTION, &NewDriverOrder, gDriverOptionCount);
	}
	VarSetNvramName (
		L"DriverOrder",
		&gEfiGlobalVariableGuid,
		EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
		NewDriverOrder,
		gDriverOptionCount * sizeof(UINT16)
		);
    //Set Driver manager variable
    Count = (UINT16)gDriverOptionCount;
    VarSetNvramName (L"DriverManager", &DrvMgrGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &Count, sizeof(Count));
    UpdateDriverVariables ();
	if (DriverOrder)
	{
		MemFreePointer ((VOID **)&DriverOrder);
	}
	if (DriverOrder)
	{
		MemFreePointer ((VOID **)&NewDriverOrder);
	}
	UpdateAddDeleteDriverVar ();
}
//EIP70421 & 70422  Support for driver order Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BootSetBootNowCount
//
// Description:	function to set boot new devices count
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _BootSetBootNowCount(VOID)
{
    UINT16 count = 0;
    UINTN i;

    BOOT_DATA *bootData;

    for( i=0; i<gBootOptionCount; i++)
    {
        bootData = &(gBootData[i]);

		if(BBSValidDevicePath(bootData->DevicePath))
        {
            count = count + bootData->LegacyDevCount;
        }
        else
            count++;
    }

    return count;
}

//EIP 77400 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_ShellClearScreen
//
// Description:	Clears the screen for shell boot
//
// Input:		EFI_EVENT , VOID *
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void ClearGrphxScreen (void);
VOID _ShellClearScreen (EFI_EVENT Event, VOID *Context)
{
	UINT32 shelltextmodetype;
	InvalidateStatusInBgrtWrapper();				//EIP93524 : When booting to shell clearing the BGRT status bit.
	ClearGrphxScreen ();
	gST->ConOut->ClearScreen (gST->ConOut);
	gBS->CloseEvent (Event);
	gST->ConOut->EnableCursor (gST->ConOut, TRUE);
	if (Event != gShellLaunchEvent)				//One event will be closed in incoming fnc argument other we have to close it
	{
		gBS->CloseEvent (gShellLaunchEvent);
	}
	if (Event != gShell20LaunchEvent)				//EIP158989 For shell2.0
	{
		gBS->CloseEvent (gShell20LaunchEvent);
	}
	gShellLaunchEvent = NULL;					//Make NULL otherwise we will try to close it after startimage
	gShell20LaunchEvent = NULL;

	shelltextmodetype = ShellTextMode();//EIP 94205 : OEM needs Token to assign the display mode of SHELL.
	
	if ( 0xFF != shelltextmodetype )
		gST->ConOut->SetMode( gST->ConOut, shelltextmodetype );	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_RegisterShellGuid
//
// Description:	Registers the shell guid
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _RegisterShellGuid (VOID)
{
	EFI_STATUS 	Status = EFI_UNSUPPORTED;
	VOID 		*Registration = NULL;
	EFI_GUID 	EfiShellInterfaceGuid = EFI_SHELL_PROTOCOL_GUID;
	EFI_GUID 	EfiShell20InterfaceGuid = EFI_SHELL2_0_FILE_GUID;

	Status = gBS->CreateEvent (
				EFI_EVENT_NOTIFY_SIGNAL, 
				EFI_TPL_CALLBACK,
				_ShellClearScreen,
				NULL,
				&gShellLaunchEvent);
	if (!EFI_ERROR (Status))
	{
		Status = gBS->RegisterProtocolNotify(
				&EfiShellInterfaceGuid,
				gShellLaunchEvent,
				&Registration
				);
	}
	Status = gBS->CreateEvent (
				EFI_EVENT_NOTIFY_SIGNAL, 
				EFI_TPL_CALLBACK,
				_ShellClearScreen,
				NULL,
				&gShell20LaunchEvent);
	if (!EFI_ERROR (Status))
	{
		Status = gBS->RegisterProtocolNotify(
				&EfiShell20InterfaceGuid,
				gShell20LaunchEvent,
				&Registration
				);
	}
}
//EIP 77400 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BootLaunchDevicePath
//
// Description:	function to launch the boot operation
//
// Input:		EFI_DEVICE_PATH_PROTOCOL *DevicePath, VOID *Options, UINTN OptionSize, BOOLEAN ValidBootOption
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _BootLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath, VOID *Options, UINTN OptionSize, BOOLEAN ValidBootOption )
{
    EFI_STATUS	Status;
    EFI_HANDLE	handle;
    BOOLEAN		FreeDevicePath = FALSE;
    EFI_EVENT	ReadyToBootEvent;
	EFI_GUID	Bootguid = AMITSE_EVENT_BEFORE_BOOT_GUID;
	EFI_GUID	AfterBootGuid = AMITSE_EVENT_AFTER_BOOT_GUID; //EIP-162197

    EFI_TPL CurrentTpl;
	TSE_POST_STATUS	BackupPostStatus;
#ifndef STANDALONE_APPLICATION
    EFI_CONSOLE_CONTROL_SCREEN_MODE ScreenMode = EfiConsoleControlScreenText;
#endif //STANDALONE_APPLICATION

	BackupPostStatus = gPostStatus; // Back it up and of boot fail restore it back
	gPostStatus = TSE_POST_STATUS_PROCEED_TO_BOOT;

#if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT) && EFI_SPECIFICATION_VERSION<0x20000
    Status = gBS->CreateEvent(
                EFI_EVENT_SIGNAL_READY_TO_BOOT | EFI_EVENT_NOTIFY_SIGNAL_ALL,
                EFI_TPL_CALLBACK,
                NULL,
                NULL,
                &ReadyToBootEvent
                );
#else
    Status = TseEfiCreateEventReadyToBoot(
                EFI_TPL_CALLBACK,
                NULL,
                NULL,
                &ReadyToBootEvent
                );
#endif //EFI_EVENT_SIGNAL_READY_TO_BOOT

    if (EFI_ERROR(Status))
        return Status;

    gBS->SignalEvent( ReadyToBootEvent );
    gBS->CloseEvent( ReadyToBootEvent );
	EfiLibReportStatusCode(EFI_PROGRESS_CODE, DXE_READY_TO_BOOT,0,NULL,NULL);

    TSEIDEPasswordFreezeDevices();

    if( gBootFlow == BOOT_FLOW_CONDITION_FAST_BOOT)
    {
		// Call the Hook and do the FastBoot
		if ( BBSValidDevicePath( DevicePath ) )
		{
			BeforeLegacyBootLaunchHook();
			UninstallBgrtWrapper(); 							//EIP81830 Support to uninstall the BGRT on legacy boot
		}
		else
		{
			BeforeEfiBootLaunchHook();							//Clearing the logo for shell in fast boot also EIP102710
			if (NULL != gShellLaunchEvent)				
			{
				gBS->CloseEvent (gShellLaunchEvent);
				gShellLaunchEvent = NULL;
			}
			if (NULL != gShell20LaunchEvent)		//EIP158989			
			{
				gBS->CloseEvent (gShell20LaunchEvent);
				gShell20LaunchEvent = NULL;
			}
			//EIP 95518 : Validate the Gop before usage in all the possible cases and also get instance of Gop through notification
			//EIP136592, 141863, 123535 
			if ( ( NULL != gGOP ) && (CurrentScreenresolutionX && CurrentScreenresolutionY) && //If it has valid gGOP and resolution
				 ((CurrentScreenresolutionX != gGOP->Mode->Info->HorizontalResolution) || (CurrentScreenresolutionY != gGOP->Mode->Info->VerticalResolution)) //If current and quietboot resolution is different
				)//EIP-88430 
			{
				GOPSetScreenResolution(&CurrentScreenresolutionX, &CurrentScreenresolutionY);
				//gGOP->SetMode (gGOP, CurrentResolutionIndex); // To maintain graphics resolution 
			}
			EfiLibNamedEventSignal (&Bootguid);//EIP-112796 Signal  AMITSE_EVENT_BEFORE_BOOT_GUID for EfiBoot during Fastboot
			_RegisterShellGuid ();
		}
		// Performance measurement Pause
		PERF_END (0, AMITSE_TEXT("Boot"), NULL, 0);
		Status = FastBootLaunch();
		
		EfiLibNamedEventSignal (&AfterBootGuid);
		return Status;
    }
#if APTIO_4_00						//EIP94702 Useful for secure boot violation message box
	gMaxRows = MAX_ROWS;
	gMaxCols = MAX_COLS;
#endif
    if ( BBSValidDevicePath( DevicePath ) )			//EIP58954 Changing the mode only for csm
    {
#ifndef STANDALONE_APPLICATION
	// Fast Boot May want to boot without Console Control
		if (gConsoleControl != NULL)
		{
		    gConsoleControl->GetMode (gConsoleControl, &ScreenMode, NULL, NULL);
		    if (ScreenMode != EfiConsoleControlScreenText)
			{
		        gConsoleControl->SetMode (gConsoleControl, EfiConsoleControlScreenText);
				InvalidateStatusInBgrtWrapper ();					//Since mode changed invalidating status field in BGRT table. EIP 58954
			}
		}
#endif //STANDALONE_APPLICATION
        BeforeLegacyBootLaunchHook();
        UninstallBgrtWrapper(); 										//EIP81830 Support to uninstall the BGRT on legacy boot
        Status = CsmBBSLaunchDevicePath( DevicePath );
		if (EFI_ERROR (Status))
			LegacyBootFailHook(Status);//EIP 89377 : Support to LegacyBootFailHook() in TSE.
        AfterLegacyBootLaunchHook();
		gPostStatus = BackupPostStatus;
		
		EfiLibNamedEventSignal (&AfterBootGuid);
        return Status;
    }

    CurrentTpl = gBS->RaiseTPL( EFI_TPL_HIGH_LEVEL );
    gBS->RestoreTPL( EFI_TPL_APPLICATION );
    if (DevicePath->Type==MEDIA_DEVICE_PATH && DevicePath->SubType==MEDIA_HARDDRIVE_DP)
    {
        DevicePath = _DiscoverPartition(DevicePath);
        FreeDevicePath = TRUE;
    }
    Status = gBS->LoadImage (TRUE, gImageHandle, DevicePath, NULL, 0, &handle);
    if (EFI_ERROR (Status))
    {
        EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath = DevicePath;
        EFI_STATUS RepairStatus = FALSE;
		UefiBootFailHook (Status);
        RepairStatus = CheckForDeviceNeedRepair (TempDevicePath);           //EIP 57661 support for UEFI specification v 2.3.1, p. 10.10.1 Driver health protocol
        if (!(EFI_ERROR (RepairStatus)))
        {
            Status = gBS->LoadImage (TRUE, gImageHandle, DevicePath, NULL, 0, &handle);
			if (EFI_ERROR (Status))
			{
				UefiBootFailHook (Status);
			}
        }
    }
    if (EFI_ERROR (Status))
    {
        //Try default behaviour
        EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath = NULL;
        EFI_HANDLE                  DevHandle;
        EFI_HANDLE                  UsbDevHandle = NULL;
        EFI_BLOCK_IO_PROTOCOL       *BlkIo = NULL;
        VOID                        *Buffer = NULL;
        EFI_DEVICE_PATH_PROTOCOL    *FilePath = NULL;

        // Find a Simple File System protocol on the device path.
        TempDevicePath = DevicePath;

        UsbDevHandle = CheckDevSupShortFormPath (DevicePath);       ////EIP 64295 Support for section 3.1.2. booting from a short-form device path
        if (NULL != UsbDevHandle)
        {
            DevHandle = UsbDevHandle;
        }
        else
        {
            Status = gBS->LocateDevicePath (
                        &gEfiSimpleFileSystemProtocolGuid,
                        &TempDevicePath,
                        &DevHandle
                        );
        }
        if ((!EFI_ERROR (Status) && IsDevicePathEnd (TempDevicePath)) || (NULL != UsbDevHandle))
        {
            // Files are specified in the device path so try to
            // load the default removable media file name.

            FilePath = EfiFileDevicePath (DevHandle, gBootFileName);

			if (FilePath)
			{
                // Issue a dummy read to the device to check for media
                // change. When the removable media is changed, any Block
                // IO read/write will cause the BlockIo protocol be
                // reinstalled and EFI_MEDIA_CHANGED is returned. After
                // the Block IO protocol is reinstalled, subsequent Block
                // IO read/write will success.
                Status = gBS->HandleProtocol (
                                    DevHandle,
                                    &gEfiBlockIoProtocolGuid,
                                    (VOID **) &BlkIo
                                    );
                if (!EFI_ERROR (Status))
                {
                    Buffer = EfiLibAllocatePool (BlkIo->Media->BlockSize);
                    if (Buffer != NULL)
                    {
                        BlkIo->ReadBlocks (
                            BlkIo,
                            BlkIo->Media->MediaId,
                            0,
                            BlkIo->Media->BlockSize,
                            Buffer
                            );
                        MemFreePointer((VOID **)&Buffer);
                    }
                }

                Status = gBS->LoadImage (
                    TRUE,
                    gImageHandle,
                    FilePath,
                    NULL,
                    0,
                    &handle
                    );
				if (EFI_ERROR (Status))
				{
					UefiBootFailHook (Status);
				}
                MemFreePointer((VOID **) &FilePath);
            }
            else
            {
                Status = EFI_NOT_FOUND;
            }
        }
        else
        {
            Status = EFI_NOT_FOUND;
        }
    }


    if(ValidBootOption==TRUE)
        if (EFI_ERROR (Status)) // Report only if it Boot Option launch - Boot of loading Error!!!
    		EfiLibReportStatusCode(EFI_ERROR_CODE| EFI_ERROR_MAJOR, DXE_BOOT_OPTION_LOAD_ERROR,0,NULL,NULL);

    if (FreeDevicePath) gBS->FreePool(DevicePath);

    if ( ! EFI_ERROR( Status ) )
    {
		if (gST->ConOut != NULL)
        {
            gST->ConOut->EnableCursor (gST->ConOut, FALSE);         //Disabling bcoz Cursor appears on the WIN8 boot
        }
        _BootInstallLoadOptions( handle, Options, OptionSize );

        BeforeEfiBootLaunchHook();

		// Performance measurement Pause
		PERF_END (0, AMITSE_TEXT("Boot"), NULL, 0);

		//EIP 95518 : Validate the Gop before usage in all the possible cases and also get instance of Gop through notification
		//EIP136592, 141863
		if ( ( NULL != gGOP ) && (CurrentScreenresolutionX && CurrentScreenresolutionY) && //If it has valid gGOP and resolution
			 ((CurrentScreenresolutionX != gGOP->Mode->Info->HorizontalResolution) || (CurrentScreenresolutionY != gGOP->Mode->Info->VerticalResolution)) //If current and quietboot resolution is different
			)//EIP-88430 
		{
			GOPSetScreenResolution(&CurrentScreenresolutionX, &CurrentScreenresolutionY);
			//gGOP->SetMode (gGOP, CurrentResolutionIndex); // To maintain graphics resolution 
		}
		
		// Signal AMITSE_EVENT_BEFORE_BOOT_GUID Event;
		EfiLibNamedEventSignal (&Bootguid);
		_RegisterShellGuid ();						//EIP 77400 clearing the screen if its shell boot

		Status = gBS->StartImage( handle, NULL, NULL );
		if (NULL != gShellLaunchEvent)				//EIP 77400 Close the event if it is not the shell boot
		{
			gBS->CloseEvent (gShellLaunchEvent);
			gShellLaunchEvent = NULL;
		}
		if (NULL != gShell20LaunchEvent)			//EIP158989	
		{
			gBS->CloseEvent (gShell20LaunchEvent);
			gShell20LaunchEvent = NULL;
		}
		// Performance measurement continue
		PERF_START (0, AMITSE_TEXT("Boot"), NULL, 0);

        AfterEfiBootLaunchHook();
		EfiLibNamedEventSignal (&AfterBootGuid);
/*#if APTIO_4_00
		gMaxRows = MAX_ROWS;
		gMaxCols = MAX_COLS;
#endif //APTIO_4_00

		SetDesiredTextMode();			//EIP94702 - StyleInit will set the desired text mode*/
      ClearGrphxScreen ();
        if(EFI_ERROR( Status ))
        {
            // Report only if it is Boot Option launch - Starting the Boot option failed.!!!!
            if(ValidBootOption==TRUE)
    			EfiLibReportStatusCode(EFI_ERROR_CODE| EFI_ERROR_MAJOR, DXE_BOOT_OPTION_FAILED,0,NULL,NULL);

    		//Clear the flush buffer so that flush lines will actually
            //draw the complete screen again
        	MemSet(gFlushBuffer, sizeof(SCREEN_BUFFER), 0);

			if (gST->ConOut != NULL)
			{
	            //Disable cursor, set desired attributes and clear screen
	            gST->ConOut->EnableCursor( gST->ConOut, FALSE );
	            gST->ConOut->SetAttribute( gST->ConOut, EFI_BACKGROUND_BLACK | EFI_WHITE);
	            gST->ConOut->ClearScreen( gST->ConOut);
			}

            //Call flush lines to draw the whole screen again
            FlushLines( 0, gMaxRows - 1 );
//			DoRealFlushLines();			//EIP94702
        }
		else
		{
			InvalidateStatusInBgrtWrapper ();			//EIP93524 When win8 launched after successfull boot then BGRT table should be invalidated
		}
    }
	 gPostStatus = BackupPostStatus; /// restore the pre. Post status.

    if ( CurrentTpl > EFI_TPL_APPLICATION )
        gBS->RaiseTPL( CurrentTpl );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_DiscoverPartition
//
// Description:	function to launch the boot operation
//
// Input:		EFI_DEVICE_PATH_PROTOCOL *DevicePath
//
// Output:		device path
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_DEVICE_PATH_PROTOCOL* _DiscoverPartition(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    EFI_STATUS	Status;
    EFI_HANDLE	*Handle;
    UINTN		Count, i;

    EFI_DEVICE_PATH_PROTOCOL *FullDevicePath=NULL;
    HARDDRIVE_DEVICE_PATH* BootParitionDevicePath  = (HARDDRIVE_DEVICE_PATH*)DevicePath;

    //get list of available Block I/O devices
    Status = gBS->LocateHandleBuffer(ByProtocol,&gEfiBlockIoProtocolGuid,NULL,&Count,&Handle);
    if (EFI_ERROR(Status)) return NULL;

    for( i=0; i<Count; i++ )
    {
        EFI_BLOCK_IO_PROTOCOL		*BlockIo;
        EFI_DEVICE_PATH_PROTOCOL	*PartitionDevicePath, *TmpDevicePath;
        HARDDRIVE_DEVICE_PATH*		PartitionNode;

        Status = gBS->HandleProtocol(Handle[i],&gEfiBlockIoProtocolGuid,&BlockIo);
        if (EFI_ERROR(Status))
			continue;

        // if this is not partition, continue
        if (!BlockIo->Media->LogicalPartition)
			continue;

		Status = gBS->HandleProtocol(Handle[i],&gEfiDevicePathProtocolGuid,&PartitionDevicePath);
        if (EFI_ERROR(Status))
			continue;

        // Get last node of the device path. It should be partition node
        PartitionNode = (HARDDRIVE_DEVICE_PATH*)PartitionDevicePath;

        for( TmpDevicePath = PartitionDevicePath;
             !IsDevicePathEndType(TmpDevicePath);
             TmpDevicePath=NextDevicePathNode(TmpDevicePath) )
		{
			PartitionNode = (HARDDRIVE_DEVICE_PATH*)TmpDevicePath;
		}

        //Check if our partition matches Boot partition
        if (PartitionNode->Header.Type!=MEDIA_DEVICE_PATH || PartitionNode->Header.SubType!=MEDIA_HARDDRIVE_DP)
			continue;

        if ( PartitionNode->PartitionNumber==BootParitionDevicePath->PartitionNumber &&
             PartitionNode->SignatureType==BootParitionDevicePath->SignatureType &&
             !MemCmp(PartitionNode->Signature,BootParitionDevicePath->Signature,16) )
        {
            //Match found
            FullDevicePath = EfiAppendDevicePath(PartitionDevicePath,NextDevicePathNode(DevicePath));
            break;
        }
    }

    gBS->FreePool(Handle);
    return FullDevicePath;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BootInstallLoadOptions
//
// Description:	function to install the load options
//
// Input:		EFI_HANDLE handle, VOID *Options, UINTN OptionSize
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _BootInstallLoadOptions( EFI_HANDLE handle, VOID *Options, UINTN OptionSize )
{
    EFI_STATUS Status;
    EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;

    Status = gBS->HandleProtocol( handle, &gEfiLoadedImageProtocolGuid, &LoadedImage );
    if ( EFI_ERROR( Status ) )
        return;

    LoadedImage->LoadOptions = Options;
    LoadedImage->LoadOptionsSize = (UINT32)OptionSize;

    gCurrentBootHandle = handle;		//EIP70096 Exposing the Handle of the image that's being launched for boot, This will help other elinks to do the processing.

}

#if EFI_SPECIFICATION_VERSION<0x20000
static MEDIA_FW_VOL_FILEPATH_DEVICE_PATH  gFvFile =
{
  { MEDIA_DEVICE_PATH, MEDIA_FV_FILEPATH_DP, { sizeof(MEDIA_FW_VOL_FILEPATH_DEVICE_PATH), 0 } },
  MINI_SETUP_DATA_GUID
};
#endif //EFI_SPECIFICATION_VERSION

static EFI_DEVICE_PATH_PROTOCOL gEndDevicePath =
{
    END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, { sizeof(EFI_DEVICE_PATH_PROTOCOL), 0 }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BootBuildFVDevicePath
//
// Description:	function to build firmware volume device path protocol.
//
// Input:		UINT32 *index, EFI_GUID *guidPtr
//
// Output:		device path
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_DEVICE_PATH_PROTOCOL *_BootBuildFVDevicePath( UINT32 *index, EFI_GUID *guidPtr )
{
	EFI_STATUS  Status;
	EFI_HANDLE  *HandleBuffer;
	UINTN       Count;
	UINT32      i;
	EFI_GUID tempEfiFirmwareVolumeProtocolGuid;

    EFI_DEVICE_PATH_PROTOCOL *DevicePath, *FilePath = NULL;
#if EFI_SPECIFICATION_VERSION>=0x20000
    MEDIA_FW_VOL_FILEPATH_DEVICE_PATH gFvFile;
#endif //EFI_SPECIFICATION_VERSION

	if ( PISpecVersion() < 0x00010000 )//EIP-103540
		tempEfiFirmwareVolumeProtocolGuid = gEfiFirmwareVolumeProtocolGuid;
	else
		tempEfiFirmwareVolumeProtocolGuid = gEfiFirmwareVolume2ProtocolGuid;

    Status = gBS->LocateHandleBuffer(
            ByProtocol,
            &tempEfiFirmwareVolumeProtocolGuid,
            NULL,
            &Count,
            &HandleBuffer
            );

    if ( EFI_ERROR( Status ) )
    {
        *index = (UINT32)-1;
        return FilePath;
    }

#if EFI_SPECIFICATION_VERSION<0x20000
    MemCopy( (UINT8 *)&gFvFile + sizeof(EFI_DEVICE_PATH_PROTOCOL), guidPtr, sizeof(EFI_GUID) );
#endif //EFI_SPECIFICATION_VERSION

    for ( i = *index; i < (UINT32)Count; i++ )
    {
        Status = gBS->HandleProtocol( HandleBuffer[i], &gEfiDevicePathProtocolGuid, &DevicePath );
        if ( EFI_ERROR( Status ) )
            continue;

#if EFI_SPECIFICATION_VERSION>=0x20000
        EfiInitializeFwVolDevicepathNode (&gFvFile, guidPtr);
#endif //EFI_SPECIFICATION_VERSION

        FilePath = EfiAppendDevicePathNode( DevicePath, (EFI_DEVICE_PATH_PROTOCOL *)&gFvFile );
        if ( FilePath != NULL )
        {
            *index = i + 1;
            break;
        }
    }

    if ( i == (UINT32)Count )
        *index = (UINT32)-1;

    MemFreePointer( (VOID **)&HandleBuffer );

    return FilePath;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_BootBuildFileDevicePath
//
// Description:	function to build File device path protocol.
//
// Input:		UINT32 *index, CHAR16 *fileName
//
// Output:		device path
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_DEVICE_PATH_PROTOCOL *_BootBuildFileDevicePath( UINT32 *index, CHAR16 *fileName )
{
    EFI_STATUS  Status;
    EFI_HANDLE  *HandleBuffer;
    UINTN       Count;
    UINT32      i;

    EFI_DEVICE_PATH_PROTOCOL *FilePath = NULL;

    Status = gBS->LocateHandleBuffer(
            ByProtocol,
            &gEfiSimpleFileSystemProtocolGuid,
            NULL,
            &Count,
            &HandleBuffer
            );

    if ( EFI_ERROR( Status ) )
    {
        *index = (UINT32)-1;
        return FilePath;
    }

    for ( i = *index; i < (UINT32)Count; i++ )
    {
        FilePath = EfiFileDevicePath( HandleBuffer[i], fileName );
        if ( FilePath != NULL )
        {
            *index = i + 1;
            break;
        }
    }

    if ( i == (UINT32)Count )
        *index = (UINT32)-1;

    MemFreePointer( (VOID **)&HandleBuffer );
    return FilePath;
}

//EIP: 51671 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsBootDeviceEnabled
//
// Description:	Function to check the boot option status
//
// Input:		UINT16 value, BOOLEAN ShowAllBBSDev, BOOLEAN TseBootNowInBootOrde, BOOLEAN FromSetup
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsBootDeviceEnabled( UINT16 value, BOOLEAN ShowAllBBSDev, BOOLEAN TseBootNowInBootOrde, BOOLEAN FromSetup)
{

	UINT16	*BootOrder=NULL;
    UINTN	size = 0;
    UINTN	i,j,k;
    UINT16	count;

    BOOT_DATA *bootData;

	if((!ShowAllBBSDev) && (!TseBootNowInBootOrde))
		if(gBootData == NULL)
			return FALSE;
		else
			{
				bootData = &gBootData[value];
				if(BBSValidDevicePath(bootData->DevicePath) )
					return BootGetBBSOptionStatus(bootData, 0, FromSetup,ShowAllBBSDev);
				else
	      		return BootGetOptionStatus(bootData, FromSetup);//EIP: 51671 Getting the Boot option status when TSE_BOOT_NOW_IN_BOOT_ORDER and SETUP_SHOW_ALL_BBS_DEVICES is OFF.
			}
	if(TseBootNowInBootOrde)
	{
		BootOrder = HelperGetVariable(VARIABLE_ID_BOOT_ORDER, L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
		if (NULL == BootOrder)		//Check for boot order else the system will hang
		{
			return TRUE;
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
	}

	if(ShowAllBBSDev)
	{
	    count = 0;
	    for(i=0;i<gBootOptionCount;i++)
	    {
			if(TseBootNowInBootOrde) {
		        bootData = BootGetBootData(BootOrder[i]);
			}
			else {
	     		bootData = gBootData + i;
			}

	        if ( BBSValidDevicePath(bootData->DevicePath) )
	        {
	            if((value >= count) && (value < (count+bootData->LegacyDevCount)))
	            {
					if(TseBootNowInBootOrde)
		                MemFreePointer((VOID **) &BootOrder);
	                return BootGetBBSOptionStatus(bootData, value-count, FromSetup, ShowAllBBSDev);//EIP: 51671 Getting the Legacy Boot option status when SETUP_SHOW_ALL_BBS_DEVICES is ON.
	            }

	            count+=bootData->LegacyDevCount;
	        }
	        else {
	            if(value == count)
	            {
					if(TseBootNowInBootOrde)
		                MemFreePointer((VOID **) &BootOrder);
	                return BootGetOptionStatus(bootData, FromSetup);//EIP: 51671 Getting the Boot option status when SETUP_SHOW_ALL_BBS_DEVICES is ON.
	            }
	            count++;
	        }
	    }
 		return FALSE;
	}
	else {
	    bootData = BootGetBootData(BootOrder[value]);
	    MemFreePointer((VOID **) &BootOrder);
		if(BBSValidDevicePath(bootData->DevicePath) )
			return BootGetBBSOptionStatus(bootData, 0, FromSetup,ShowAllBBSDev);
		else
	      return BootGetOptionStatus(bootData, FromSetup);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootGetOptionStatus
//
// Description:	Function to check the boot option status in Boot Order
//
// Input:		BOOT_DATA *bootData, BOOLEAN FromSetup
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BootGetOptionStatus(BOOT_DATA *bootData, BOOLEAN FromSetup)
{
	UINTN size = 0;
	UINTN i=0;
	UINT16 *buffer = NULL;

			if(0 == FromSetup)
			{
					if(bootData->Active & LOAD_OPTION_ACTIVE)
						return FALSE;
					else
						return TRUE;

			}

			buffer = EfiLibAllocateZeroPool(  gBootOptionCount * sizeof(UINT16));
			buffer = HelperGetVariable(VARIABLE_ID_BOOT_ORDER, L"BootOrder", &gEfiGlobalVariableGuid, NULL, &size );
         if (NULL == buffer)
         {
            return TRUE;
         }

			for(i=0 ; i<gBootOptionCount ; i++)
			{
				if(buffer[i] == bootData->Option)
				   break;
			}
			if(i == gBootOptionCount )
			{
				MemFreePointer((VOID **) &buffer);
					return TRUE;
			}
			else
			{
				MemFreePointer((VOID **) &buffer);
					return FALSE;
			}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BootGetBBSOptionStatus
//
// Description:	Function to check the Legacy boot option status
//
// Input:		BOOT_DATA *bootData, BOOLEAN FromSetup, BOOLEAN ShowAllBBSDev
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BootGetBBSOptionStatus(BOOT_DATA *bootData, UINT16 value, BOOLEAN FromSetup, BOOLEAN ShowAllBBSDev)
{
	   UINT32 offset=0;
		UINT32 i;
		UINT8 *pDevOrder;
		BBS_ORDER_TABLE	*pDev;
		UINTN size = 0;
		UINT16 *buf = NULL, *Tempbuf = NULL;

		if(0 == FromSetup)
		{
		   if(!BootGetOptionStatus(bootData, FromSetup))
		   {
	            offset = (UINT16)bootData->LegacyEntryOffset;

			  		pDevOrder = HelperGetVariable(VARIABLE_ID_BBS_ORDER,L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size);

	         	pDev = (BBS_ORDER_TABLE *)(pDevOrder + offset);

					if ( (pDev->Length >= size) || (0 == pDev->Length) ) //EIP-120011
						return TRUE;

              if(DISABLED_BOOT_OPTION == pDev->Data[value])
					{
						 MemFreePointer((VOID **) &pDevOrder);
  					    return  TRUE;
					}
    		  		else
					{
						 MemFreePointer((VOID **) &pDevOrder);
                   return  FALSE;
					}
		   }
		   else
		       return TRUE;
        }
		if(!BootGetOptionStatus(bootData, FromSetup))
		{

			size=0;
		 	offset = (UINT16)bootData->LegacyEntryOffset;
			pDevOrder = HelperGetVariable(VARIABLE_ID_BBS_ORDER,L"LegacyDevOrder", &gLegacyDevGuid, NULL, &size);
            if (NULL == pDevOrder)
            {
              return TRUE;
            }

			pDev = (BBS_ORDER_TABLE *)(pDevOrder + offset);

			if ( (pDev->Length >= size) || (0 == pDev->Length) ) //EIP-120011
				return TRUE;

			if(!ShowAllBBSDev)
			{
					if(DISABLED_BOOT_OPTION == pDev->Data[value])
					{
						MemFreePointer((VOID **) &pDevOrder);
  					   	return  TRUE;
    				}
					else
					{
						MemFreePointer((VOID **) &pDevOrder);
                  	return  FALSE;
					}
			}
			
	      buf = EfiLibAllocateZeroPool(  pDev->Length - sizeof(UINT16));
			
         if (NULL == buf)		//EIP117338
         {
            return FALSE;
         }
			
         Tempbuf = buf;
			MemCopy( buf, &pDev->Data, pDev->Length - sizeof(UINT16) );
			
			for(i=0; i < bootData->LegacyDevCount ;i++)
			{
            if(*buf == bootData->OrderList[value].Index)
               break;
            buf++;
			}
			
         MemFreePointer((VOID **) &pDevOrder);		//EIP117338
         MemFreePointer((VOID **) &Tempbuf);
			
			if(i ==  bootData->LegacyDevCount)
			{
            return  TRUE;
			}
			else
			{
            return  FALSE;
			}
		}
		else
			return TRUE;
}
//EIP: 51671 END
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LoadOptionhidden
//
// Description:	Function to check the Boot option status if gLoadOptionhidden token is Enabled
//
// Input:		UINT16 value
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN LoadOptionhidden (UINT16 value, BOOLEAN Option)
{
	if (BOOT_ORDER_OPTION == Option)
	{
    	if (gBootData [value].Active & LOAD_OPTION_HIDDEN)
			return TRUE;
	}
	else if (DRIVER_ORDER_OPTION == Option)				//EIP70421 & 70422
	{
		if (gDriverData [value].Active & LOAD_OPTION_HIDDEN)
			return TRUE;
	}	
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckHiddenforBootDriverOption
//
// Description:	Check whether the Boot/Driver option has hidden property
//
// Input:		UINT16, BOOLEAN
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckHiddenforBootDriverOption (UINT16 Option, BOOLEAN HiddenOption)
{
	UINTN i = 0;
	if (gLoadOptionHidden)
	{	
		if (BOOT_ORDER_OPTION == HiddenOption)
		{
			for (i = 0 ;i < gBootOptionCount ;i++)
			{
				if (gBootData [i].Option == Option)
				{
					if (gBootData [i].Active & LOAD_OPTION_HIDDEN)
					{
						return TRUE;
					}
					break;
				}
			}
		}
		else if (DRIVER_ORDER_OPTION == HiddenOption)
		{
			for (i = 0 ;i < gDriverOptionCount ;i++)
			{
				if (gDriverData [i].Option == Option)
				{
					if (gDriverData [i].Active & LOAD_OPTION_HIDDEN)
					{
						return TRUE;
					}
					break;
				}
			}
		}
	}
	return FALSE;
}

//EIP: 62631 Start
//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------
// Procedure:	CheckBootOptionMatch
//
// Description:	Checks the input boot option matches with any of the boot option in the system
//
// Input:		UINT16 = Boot option to which match to be find
//
// Output:		UINT32 = Returns 0 if no match found
//                     = 32 bit CRC value of boot option if match found
//
//------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 CheckBootOptionMatch (UINT16 BootOption)
{
    UINTN	iIndex = 0;
    CHAR16  BootOptionName [9];             //Bootxxxx + 1 NULL char
    UINT32	*LoadOptions = NULL;        //Using 32 bit ptr bcoz to find CRC32
    UINTN	LoadOptionSize = 0;
    UINT32  CRC32 = 0;

    SPrint (BootOptionName, sizeof (BootOptionName), L"Boot%04X", BootOption);
    LoadOptions = VarGetNvramName (BootOptionName, &gEfiGlobalVariableGuid, NULL, &LoadOptionSize);     //Getting boot options
    if ((NULL == LoadOptions) || (0 == LoadOptionSize))
    {
        return CRC32;           //returning 0
    }
   gBS->CalculateCrc32 ((UINT8 *)LoadOptions, LoadOptionSize, &CRC32);
   return CRC32;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------------------
// Procedure:	SetBootOptionSupportVariable
//
// Description:	Function to set the BootOptionSupport variable
//
// Input:		UINT32 = Capabilities for the BootOptionSupport variable
//
// Output:		VOID
//
//--------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetBootOptionSupportVariable (UINT32 BootManCapabilities)
{
    CHAR16 VariableName [] = L"BootOptionSupport";
    UINT32 Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
    UINTN DataSize = 0;
    VOID *Data;
    UINT32 SetData = 0;

    Data = VarGetNvramName (VariableName, &gEfiGlobalVariableGuid, &Attributes, &DataSize);     //If the variable exists use its attribute to set it
    if (NULL != Data)
    {
        SetData = *((UINT32 *)Data);
    }
    SetData |= BootManCapabilities;
    DataSize = sizeof (UINT32);         //Sizeof BootOptionSupport variable is UINT32
    VarSetNvramName (VariableName, &gEfiGlobalVariableGuid, Attributes, (VOID *)&SetData, DataSize);
}
//EIP: 62631 End

//EIP 64295 Start
//<AMI_PHDR_START>
//--------------------------------------------------------------------------------------
// Procedure:	CheckDevSupShortFormPath
//
// Description:  Matches the device path with USB class device path (Table 60) and returns
//                  the corresponding USB's file system handle
//
// Input:   EFI_DEVICE_PATH_PROTOCOL * -> Device path for the boot option
//
// Output:  EFI_HANDLE -> Handle for the file system
//
//--------------------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_HANDLE CheckDevSupShortFormPath (EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
	UINTN       NumHandles = 0;
	UINTN       iIndex = 0;
	CHAR16		*USBString = NULL;
	CHAR16		*USBDevPathString = NULL;
	UINT16     	*LangIDTable;
	UINT16		TableSize = 0;
	EFI_STATUS  Status;
	EFI_HANDLE  *UsbIoHandles = NULL;
    EFI_USB_IO_PROTOCOL         *UsbIoProtocolInstance = NULL;
    EFI_USB_DEVICE_DESCRIPTOR   DeviceDescriptor;
    USB_CLASS_DEVICE_PATH       *UsbClassDevPath = NULL;
	USB_WWID_DEVICE_PATH		*UsbWwidDevPath = NULL;
    EFI_DEVICE_PATH_PROTOCOL    *TempDevPath = DevicePath;
	
    if ((MESSAGING_DEVICE_PATH == TempDevPath->Type) && (MSG_USB_CLASS_DP == TempDevPath->SubType))     //Check for USB Device Path Class. type = 3 and subtype = 0xf
    {
		UsbClassDevPath = (USB_CLASS_DEVICE_PATH *)TempDevPath;
    }
    else if ((MESSAGING_DEVICE_PATH == TempDevPath->Type) && (MSG_USB_WWID_CLASS_DP == TempDevPath->SubType))
    {
		UsbWwidDevPath = (USB_WWID_DEVICE_PATH *)TempDevPath;
		USBDevPathString = (CHAR16 *)((UINT8 *)UsbWwidDevPath + sizeof (USB_WWID_DEVICE_PATH));		//String will be present at the end of the WWID device path
    }
	else
	{
		return NULL;
	}
	Status = gBS->LocateHandleBuffer (                  //To match with USB Device Path Class
				ByProtocol,
				&gEfiUsbIoProtocolGuid,
				NULL,
				&NumHandles,
				&UsbIoHandles
				);
	if (EFI_ERROR (Status))
	{
        return NULL;
	}
	for (iIndex = 0; iIndex < NumHandles; iIndex ++)
	{
		Status = gBS->HandleProtocol (UsbIoHandles [iIndex], &gEfiUsbIoProtocolGuid, &UsbIoProtocolInstance);
		if (EFI_ERROR (Status))
    	{
            continue;
        }
        Status = UsbIoProtocolInstance->UsbGetDeviceDescriptor (UsbIoProtocolInstance, &DeviceDescriptor);
        if (EFI_ERROR (Status))
    	{
            continue;
        }
		if (UsbWwidDevPath)
		{
			Status = UsbIoProtocolInstance->UsbGetSupportedLanguages (UsbIoProtocolInstance, &LangIDTable, &TableSize);
			if (!EFI_ERROR (Status) && TableSize)
			{
				Status = UsbIoProtocolInstance->UsbGetStringDescriptor (UsbIoProtocolInstance, LangIDTable [0], DeviceDescriptor.StrSerialNumber, &USBString);		//LangIDTable [0], getting default as English
				if (EFI_ERROR (Status))
				{
					USBString = NULL;  		//Explicitly making as NULL
				}
			}
			if ((NULL != USBString) ^ (0 != EfiStrLen (USBDevPathString)))		//If serial number string present in device path and not in descriptor then try for other device and vice versa too
			{																			//If device path and descriptor not has the string then proceed
				continue;
			}
		}
		if (UsbClassDevPath?
		(			//Check for USB Class device path
        ((UsbClassDevPath->VendorId == DeviceDescriptor.IdVendor) || (0xFFFF == UsbClassDevPath->VendorId)) &&      //If values are 0xF's then dont consider that option
        ((UsbClassDevPath->ProductId == DeviceDescriptor.IdProduct) || (0xFFFF == UsbClassDevPath->ProductId)) &&
        ((UsbClassDevPath->DeviceClass == DeviceDescriptor.DeviceClass) || (0xFF == UsbClassDevPath->DeviceClass)) &&
        ((UsbClassDevPath->DeviceSubClass == DeviceDescriptor.DeviceSubClass) || (0xFF == UsbClassDevPath->DeviceSubClass)) &&
        ((UsbClassDevPath->DeviceProtocol == DeviceDescriptor.DeviceProtocol) || (0xFF == UsbClassDevPath->DeviceProtocol))
        ):
		(			//Check for USB WWID device path
		(UsbWwidDevPath->VendorId == DeviceDescriptor.IdVendor) &&
		(UsbWwidDevPath->ProductId == DeviceDescriptor.IdProduct) &&
		(USBString ? (!(EfiStrCmp (USBDevPathString, USBString))):1)			//String number of USB might not be filled in some case in such conditions will take it as TRUE
		)
		)
        {
            UINTN       Count;
        	EFI_GUID    **ppGuid;
            UINTN       jIndex = 0;
            UINTN       kIndex = 0;

            Status = gBS->ProtocolsPerHandle (UsbIoHandles [iIndex], &ppGuid, &Count);
            if (EFI_ERROR (Status))
            {
                continue;
            }
            for (jIndex = 0; jIndex < Count; jIndex ++)
	        {
                if (!guidcmp (ppGuid [jIndex], &gEfiDiskIoProtocolGuid))
                {
                    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *pInfo;
                    UINTN InfoCount = 0;
                    VOID  *FilsSystemInstance = NULL;
                    EFI_HANDLE handle = NULL;
                    EFI_DEVICE_PATH_PROTOCOL    *FilePath = NULL;

                    Status = gBS->OpenProtocolInformation (UsbIoHandles [iIndex], ppGuid [jIndex], &pInfo, &InfoCount);
                    if (EFI_ERROR (Status))
                    {
                        continue;
                    }
                    for (kIndex = 0; kIndex < InfoCount; kIndex ++)
                    {
                        Status = gBS->HandleProtocol (pInfo [kIndex].ControllerHandle, &gEfiSimpleFileSystemProtocolGuid, &FilsSystemInstance);
                        if (EFI_ERROR (Status))
                        {
                            continue;
                        }
                        FilePath = EfiFileDevicePath (pInfo [kIndex].ControllerHandle, gBootFileName);
                        if (FilePath)
                        {
                            Status = gBS->LoadImage (                       //Ensuring the image can load
                                                       TRUE,
                                                        gImageHandle,
                                                        FilePath,
                                                        NULL,
                                                        0,
                                                        &handle
                                                    );
                            MemFreePointer((VOID **) &FilePath);
                            if (!EFI_ERROR (Status))
                            {
								if (USBString)
								{
									MemFreePointer ((VOID **)&USBString);
								}
                                MemFreePointer ((VOID **)&UsbIoHandles);
                                return pInfo [kIndex].ControllerHandle;
                            }

                        }
                    }
                    if (InfoCount)
					{
						MemFreePointer ((VOID **)&pInfo);
                	}
                }
            }
        }
		if (USBString)
		{
			MemFreePointer ((VOID **)&USBString);
		}
	}
	MemFreePointer ((VOID **)&UsbIoHandles);
    return NULL;
}
//EIP 64295 End

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
