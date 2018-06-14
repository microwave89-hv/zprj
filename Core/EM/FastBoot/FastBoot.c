//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/PTT/FastBoot.c 58    8/06/13 10:42p Simonchen $
//
// $Revision: 58 $
//
// $Date: 8/06/13 10:42p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBoot.c $
// 
// 58    8/06/13 10:42p Simonchen
// [TAG]  		EIP130731
// [Category]  	Improvement
// [Description]  	Use file system protocol to check boot loader.
// [Files]  		FastBoot.c
// 
// 57    7/17/13 2:59a Simonchen
// [TAG]  		EIP125309
// [Category]  	New Feature
// [Description]  	Add function to make sure before boot to OS, BIOS is in
// fastboot path.
// [Files]  		FastBoot.sdl
// FastBootTseHook.c
// FastBoot.c
// FastBoot.h
// 
// 56    7/14/13 10:10p Simonchen
// [TAG]  		EIP118901
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	The Rumtime Memory Allocation in SmiVariable Module may
// cause S4 Resume Failure
// [RootCause]  	Memory mapping changed between Normal Boot Path and
// FastBoot Path if SmiVariable is enabled
// [Solution]  	Publish  HII data in fastboot path.
// [Files]  		FastBoot.c
// 
// 55    7/11/13 10:10p Simonchen
// [TAG]  		EIP126196
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	If set two HDD password and use Raid mode, fastboot will
// fail.
// [RootCause]  	Because when AHCI driver unlock first HDD, Raid driver
// will try to read all HDD, but second HDD is still lock, so access will
// fail.
// [Solution]  	Make sure all HDD unlock then Raid can access HDD. 
// And add "Support Raid Driver" token to control fastboot support Raid
// feature or not.
// [Files]  		FastBoot.c
// FastBoot.sd
// FastBoot.sdl
// FastBootRuntime.c
// FastBoot.h
// 
// 54    4/18/13 5:39a Simonchen
// [TAG]  		EIP113454
// [Category]  	New Feature
// [Description]  	This eip is created for implement or experiment for
// Intel raid mode on fastboot.
// [Files]  		FastBoot.sdl
// FastBootRuntime.c
// FastBoot.c
// FastBoot.sd
// FastBoot.uni
// 
// 53    1/15/13 1:50a Bibbyyeh
// Boot variables is in upper case from version 4.6.4.1.
// 
// 52    1/07/13 2:04a Bibbyyeh
// [TAG]           EIP111095
// [Category]      Improvement
// [Description]   Win8 will create "WINDOWS BOOT MANAGER" and change this
// boot option as the highest boot priority when first time boot into
// Win8. It may cause fast boot fail because boot order is changed by OS.
// To avoid this problem, we check devcie path again if boot option number
// is check failure.
// [Files]         FastBoot.c
// 
// 51    12/21/12 2:38a Bibbyyeh
// [TAG]           EIP110027
// [Category]      Improvement
// [Description]  	The parameter BootPolicy should NOT set as TRUE when
// load image if this loading is not for boot.
// [Files]         FastBoot.c
// 
// 50    12/12/12 2:59a Bibbyyeh
// [TAG]           EIP107729
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       When fastboot enable, the floppy disk driver can・t
// detect by OS(already test on Win7 32 and 64(not UEFI))
// [RootCause]     BIOS didn't install INT13 service for floppy.
// [Solution]      Don't set bbs priority of floppy as BBS_IGNORE_ENTRY,
// set as BBS_DO_NOT_BOOT_FROM.
// [Files]         FastBoot.c
// 
// 49    11/29/12 9:30p Bibbyyeh
// [Description]  	Fix build error because AMI_AMT_BOOT_OPTION_GUID is not
// found on non-Intel platforms.
// [Files]         FastBoot.c
// 
// 48    10/30/12 3:13a Bibbyyeh
// [TAG]           EIP105175
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       USB controller does not skip in Fast Boot path when set
// USB support as disabled.
// [RootCause]     The Runtime flag is set too early, and it make USB
// controller connect again when TSE call ReadKeyStroke.
// [Solution]      Set Runtime flag just before boot into image or legacy
// environment to make sure the ReadKeyStroke is called by OS, not BIOS.
// [Files]         FastBoot.c
// 
// 47    10/11/12 2:34a Bibbyyeh
// [TAG]  		EIP103422
// [Category]  	Improvement
// [Description]  	FastBoot behavior is conflict with  Fixed boot order.
// System cannot Enter windows 7 most of the time and will just show the
// message no bootable device found.
// [Files]  		FastBoot.c
// 
// 46    10/04/12 11:52p Bibbyyeh
// [TAG]           EIP102931
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       When issue the Local HDD Boot from WebUI, sometimes the
// BIOS can't boot from Local Hard Disk drive and enter BIOS setup.
// [RootCause]     It's possible AMT boot device is skipped in fast boot
// path, and enter setup.
// [Solution]      If AMT boot is request, boot with normal boot path and
// set Setup boot flow as BOOT_FLOW_CONDITION_NORMAL.
// [Files]         FastBoot.c FastBoot.sdl
// 
// 45    9/06/12 8:01a Bibbyyeh
// The definition in USB_SKIP_LIST is changed from bNotUsed to bFlag.
// 
// 44    9/06/12 6:20a Bibbyyeh
// [TAG]           EIP100342
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       System hangs if remove monitor cable (D-SUB\DVI\HDMI)
// when FastBoot enabled.
// [RootCause]     When monitor cable is removed ,there is no simple text
// out protocol installed for ConOut service in fastboot mode.
// [Solution]      Signal CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID and
// install simple text out protocol even if there is no ConOut devcie. 
// [Files]         FastBoot.c
// 
// 43    9/06/12 3:41a Bibbyyeh
// [TAG]           EIP96292
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       Bitlock test failure when fast boot enabled and USB
// support is as "partial initial".
// [RootCause]     Usb key can NOT be connected by Windows successfully.
// [Solution]      Usb module provides the policy control for USB mass
// storage driver enabled/disabled dynamically.
// 
// 42    8/28/12 11:58p Bibbyyeh
// Consider fast boot failed case, chagne boot flow back to
// BOOT_FLOW_CONDITION_NORMAL.
// 
// 41    8/27/12 6:08a Bibbyyeh
// Fixed the logic of IsFastBoot elink. System only enter FastBoot path
// when all the IsFastBoot elinks return TRUE.
// 
// 40    8/24/12 1:09a Bibbyyeh
// Fixed the logic of IsFastBoot elink. System only enter FastBoot path
// when all the IsFastBoot elinks return TRUE.
// 
// 39    8/23/12 6:07a Bibbyyeh
// Modify Dp macro and add a flag "InFastBootPath".
// 
// 38    8/22/12 5:42a Bibbyyeh
// [TAG]           EIP95568
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       SATA HDD device is not found under UEFI Shell when SATA
// mode is RAID
// [RootCause]     RAID controller is not connected in fast boot path.
// [Solution]      Connect RAID controller in ConnectAllSATADevices
// procedure.
// [Files]         FastBoot.c
// 
// 37    8/16/12 1:27a Bibbyyeh
// Refine the code base and add Dp macro.
// 
// 36    8/10/12 6:00a Bibbyyeh
// [TAG]           EIP97474
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Some ConIn devices are not workable in fastboot path.
// [RootCause]     Some handles are not connectted in FbConnectEverything.
// [Solution]      Connect all handles and only skip the devices we
// expected.
// [Files]         FastBoot.c FastBoot.sdl
// 
// 35    8/10/12 3:23a Bibbyyeh
// [TAG]           EIP96276
// [Category]      New Feature
// [Description]   Function request for PTT_12
// EIP96276.2 Fixed USB skip table issue. 
// EIP96276.3 Add token ．CONNECT_ALL_SATA_DEVICE_IN_FASTBOOT・ to
// gFastBootPolicy.
// EIP96276.4 Add IsValidFBBootOptionPtr support by driver type. Exp : usb
// type skip or other type
// EIP96276.5 Add token ．Test mode； to gFastBootPolicy Setup menu.
// EIP96276.6 Disable Tse Hotkey support in fastboot path.
// EIP96276.7 Modify TRACE message.
// [Files]         FastBoot.c FastBoot.sd FastBoot.sdl FastBoot.uni
// FastBootRuntime.c FastBootProtocol.c
// 
// 34    8/07/12 4:40a Bibbyyeh
// [TAG]           EIP97545
// [Category]      Improvement
// [Description]   Updated PTT Module to Implement Support for
// Initializing the Keyboard in First Call of Readkeystroke on Fastboot.
// [Files]         FastBoot.c FastBoot.h FastBootProtocol.h
// 
// 33    6/27/12 4:21a Bibbyyeh
// [TAG]           EIP93038
// [Category]      New Feature
// [Description]   Ability to customize fast boot boot option selection
// [Files]         FastBoot.c FastBoot.h FastBoot.sdl
// 
// 32    6/22/12 2:49a Bibbyyeh
// [TAG]           EIP91458
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       System hangs if USB LAN is first boot priority
// [RootCause]     USB LAN is identified as USB Hdd, and it cause fast
// boot behavior wrong.
// [Solution]      Add checking rule for USB LAN, this kind of device
// would not be the fast boot device.
// [Files]         FastBoot.c
// 
// 31    6/13/12 8:49a Bibbyyeh
// Add checking Built in Shell device path when building Fast Efi Boot
// Option.
// 
// 30    6/12/12 10:15p Bibbyyeh
// Add a item "Auto" for fastboot "VGA Support". Only install Legacy OpRom
// only when previous boot is Legacy OS.
// 
// 29    6/07/12 7:42a Bibbyyeh
// [TAG]           EIP91800
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       The USB_SKIP_LIST which in the SBDXE.c in the routing
// ：sbUsbProtocolCallback； is not working.
// [RootCause]     UsbSkipTable is updated by PTT module
// [Solution]      Backup SkipTable pointer before set new skip table in
// Fastboot path. If return to normal boot mode, restore the skip table
// pointer to backup one.
// [Files]         FastBoot.c
// 
// 28    6/04/12 4:34a Bibbyyeh
// Compliant with Core 4.6.4.0
// 
// 27    6/01/12 7:04a Bibbyyeh
// [TAG]           EIP90455
// [Category]      New Feature
// [Description]   PTT improvement - fastboot policy protocol for dynamic
// control fast boot behavior.
// [Files]         FastBoot.c FastBoot.sdl FastBoot.sd FastBoot.uni
// FastBootRuntime.c FastBootTseHook.c FastBootProtocol.h FastBoot.h
// 
// 26    5/29/12 3:19a Bibbyyeh
// [TAG]           EIP87390
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       TCG Bitlocker Driver Encryption error if set the Fast
// boot enable
// [RootCause]     USB INT13 service is not installed and Pci OpRom is not
// measured by TPM in fastboot path.
// [Solution]      Set USB device priority as BBS_DO_NOT_BOOT_FROM for
// install int13 service. Raise TPL as TPL_HIGH_LEVEL for invoking TPM
// callback function "OnPciIOInstalled".
// [Files]         FastBoot.h
// 
// 25    4/13/12 4:17a Bibbyyeh
// [TAG]           EIP86159
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       SUT can't be unlock by network when FastBoot enabled,
// it always needs to input PIN code and recovery key even connected to
// WDS Server.
// [RootCause]     Network stack protocol didn't install in fastboot path.
// [Solution]      Connect Network device and install network stack
// protocol.
// [Files]         FastBoot.c
// 
// 24    4/11/12 6:12a Bibbyyeh
// [TAG]           EIP87526
// [Category]      New Feature
// [Description]   Fastboot from specific device without recording device
// infomration from previous boot
// [Files]         FastBoot.c
// 
// 23    4/10/12 9:08a Bibbyyeh
// Fix a typo for pervious check in.
// 
// 22    4/10/12 8:47a Bibbyyeh
// [TAG]           EIP87452
// [Category]      Improvement
// [Description]   1. Create an elink "ReturnNormalMode", OEM/ODM can link
// their procedure to handle the fastboot failure case. 2. Disconnect USB
// controller when return to normal mode.
// [Files]         FastBoot.c FastBoot.h FastBoot.mak FastBoot.sdl
// 
// 21    4/09/12 9:09a Bibbyyeh
// [Category]      Improvement
// [Description]   Replace procedure "FbAllDriverConnect" by elink
// "CallTheDispatcher" and "SignalAllDriversConnectedEvent".
// [Files]         FastBoot.c FastBoot.sdl
// 
// 20    3/22/12 6:42a Bibbyyeh
// [TAG]           EIP86042
// [Category]      Improvement
// [Description]   For Win8 seamless boot, BIOS should not clear screen
// when boot into OS.
// [Files]         FastBoot.c
// 
// 19    3/22/12 3:19a Bibbyyeh
// [TAG]           EIP85135
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       When enabled XHCI support difficult into setup menu
// [RootCause]     Usb addon is not connected successfully when connect
// Console In devices.
// [Solution]      Create FbConnectEverything procedure to connect usb
// controller.
// [Files]         FastBoot.c FastBoot.sdl
// 
// 18    1/29/12 11:34p Bibbyyeh
// [TAG]           EIP75969
// [Category]      Improvement
// [Description]   Moved signaling of ReadyToBoot event on EFI boot path
// before call to LoadImage as per UEFI spec.
// [Files]         FastBoot.c
// 
// 17    11/21/11 5:41a Bibbyyeh
// [TAG]           EIP75718
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       After reboot 2 times, system will show error message
// and hang up if enabled Fast boot with skip VGA 
// [RootCause]     In SG mode, fastboot need to consider mutli VGA case.
// [Solution]      Disable PCI VGA device when check or install VGA rom
// failure.
// [Files]         FastBoot.c
// 
// 16    10/25/11 2:16a Bibbyyeh
// [TAG]           EIP73019
// [Category]      Improvement
// [Description]   Code logic improvment, 'Index' used on line 1489,
// conditionally not set
// [Files]         FastBoot.c
// 
// 15    10/25/11 2:12a Bibbyyeh
// [TAG]           EIP71257
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       SugarBay got build errors if TSE is disabled.
// [RootCause]     TSE_MAJOR and TSE_MINOR are not defined when TSE is
// disabled.
// [Solution]      Add define for TSE_MINOR and TSE_MAJOR if they are not
// defined.
// [Files]         FastBoot.c
// 
// 14    9/08/11 5:26a Bibbyyeh
// [TAG]           EIP68329
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       OS can't back to desktop correctly after resumed from
// S3. 
// [RootCause]     TSEIDEPasswordFreezeDevices is skipped in fastboot path
// if SKIP_TSE_HANDSHAKE is enabled. 
// [Solution]      Call TSEIDEPasswordFreezeDevices after ReadyToBoot
// Event in fastboot path.
// [Files]         FastBoot.c FastBootProtocol.h FastBootTseHook.c
// 
// 13    8/04/11 8:10a Bibbyyeh
// [TAG]         EIP62845
// [Category]    New Feature
// [Description] Connect all Sata devices in fastboot path.
// [Files]       FastBoot.c FastBoot.mak FastBoot.sdl
// 
// 12    7/07/11 10:07a Bibbyyeh
// [TAG]           EIP63924
// [Category]      Improvement
// [Description]   
// 1. Add elink for FastBoot mode change, default checking rule is check
// post hotkey.
// 2. Timer call back for check hotkey is not necessary. Create a protocol
// for calling checkforkey in TSE.
// 3. Since EIP68383 improve the performance of ps2 keyboard, we don't
// need to exchange the initial order of ConIn/ConOut for getting more
// time to detect hotkey.
// [Files]         FastBoot.sdl FastBoot.mak FastBoot.c FastBootTseHook.c
// FastBoot.h FastBootProtocol.h
// 
// 11    6/22/11 11:45p Bibbyyeh
// [TAG]           EIP62683
// [Category]      New Feature
// [Description]   Add an Elink after AllDriverConnect in fastboot path
// [Files]         FastBoot.c FastBoot.sdl FastBoot.mak
// 
// 10    5/30/11 4:34a Bibbyyeh
// [TAG]           EIP60794
// [Category]      Improvement
// [Description]   Post Time Tuning eModule improvement for CSP.
//                 1. Clear screen before boot into shell and enable
// cursor.
//                 2. Move Fastboot.h to include folder.
// [Files]         FastBoot.c
//                 FastBoot.cif
//                 FastBootIncludes.cif
// 
// 9     3/17/11 7:18a Bibbyyeh
// [TAG]  		EIP56151
// [Category]  	Improvement
// [Description]  	 PTT eModule has several compiled errors if CSM eModule
// is removed, that must be solved.
// [Files]  		FastBoot.c FastBoot.sd
// 
// 8     3/11/11 10:01p Bibbyyeh
// [TAG]		EIP54993
// [Category]	Improvement
// [Description]
// 1.Sync with Fastboot_10
// 2.Remove token "SAVE_LAST_BOOT_DEVICE_CHECKSUM"
// 3.Add token "CALL_DISPATCHER_AGAIN_IN_FASTBOOT"
// 4.Use SimpleText protocol to detect mode change hotkey instead of
// pBS->ConIn.
// 5.Simplify the code about "AMILEGACY16_FASTBOOT_SOLUTION".
// 6.Fixed a bug that SATA device can't be found if keep TSE execution on
// fastboot path.
// [Files]		PPT.cif FastBoot.sdl FastBootRuntime.c FastBootTseHook.c
// FastBoot.c FastBoot.h FastBoot.sd FastBootProtocol.cif
// FastBootProtocol.h FastBootSMI.cif FastBootSMI.sdl FastBootSMI.c
// FastBootSMI.dxs FastBootSMI.mak
// 
// 7     2/22/11 4:06a Bibbyyeh
// [TAG]  		EIP54286
// [Category]  	Improvement
// [Description]  	Add elink for IsFastBoot Function to overwirte it, it
// can help OEM/ODM to implement their "FAST BOOT" feature easily.
// [Files]  		FastBoot.sdl FastBoot.mak FastBoot.c
// 
// 6     11/26/10 12:10a Bibbyyeh
// [TAG]  		EIP48698 
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	CPU exception when all ConIn are skipped.
// [RootCause]  	It's side effect of "EIP48698". "FBTimerCallback" is
// called when pBS-> ConIn is Null.
// [Solution]  	Move "FBTimerCallback" to after
// "InstallDummySimpleTextProtocol" to make sure pBS->Con is not Null.
// [Files]  		FastBoot.c
// 
// 5     11/22/10 7:49a Bibbyyeh
// [TAG]  		EIP48698
// [Category]  	Improvement
// [Description]  	For improving success ratio of mode change by hotkey.
// Move some work into PTT module, it can make BIOS have more time to
// detect hotkey. 1.Install and execute VGA OpRom in PTT module. 2.Replace
// the order of connect ConIn/ConOut.
// [Files]  		FastBoot.c
// 
// 4     11/17/10 9:43a Bibbyyeh
// [TAG]  		EIP47397
// [Category]  	Improvement
// [Description]  	1. Move all console related functions into PTT module
// to avoid uncompatible with different core version.
// 2. Install dumy SimpleTextCoin protocol when pBS->ConIn & pBS-ConOut is
// Null.
// 3. Raise timer call back as TPL_HIGH_LEVEL level, it will give BIOS
// more chance to mode change successfully.
// 4. Remove FASTBOOT_CONSOLE_SETTING token.Add setup option for fastboot
// setting, "Skip VGA", "Skip USB", Skip "PS2".
// [Files]  		FastBoot.c
// FastBoot.h
// FastBoot.sd
// FastBoot.sdl
// FastBoot.uni
// 
// 3     10/22/10 8:26a Bibbyyeh
// [TAG]  		EIP46688
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	After dd PTT moduel and enable fast boot, the system will
// have a CPU exception 0xOD error during POST
// [RootCause]  	The root cause is EFI_COMPONENT_NAME_PROTOCOL_GUID and
// EFI_COMPONENT_NAME2_PROTOCOL_GUID is used in different UEFI version.
// [Solution]  	Add UEFU versrion checking rule to avoid this problem.
// [Files]  		fastboot.c
// 
// 2     10/13/10 5:08a Bibbyyeh
// Replace BeforeFastBoot to BeforeFastBootHook to solve build error
// 
// 1     10/12/10 9:04a Bibbyyeh
// Initial check in
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FastBoot.c
//
//  Description:
//  Implementation of fast boot functionality
//
//<AMI_FHDR_END>
//*************************************************************************

//============================================================================
// Includes
//============================================================================

#include <Token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Protocol/BlockIo.h>
#include <Protocol/LoadedImage.h>

#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>
#include <Protocol/ConsoleControl.h>
#include <Pci.h>
#include <Protocol/AMIPostMgr.h>
#include <Protocol/FastBootProtocol.h>
#include <Protocol/AmiUsbController.h>	//(EIP85135+)
#include <Protocol/UsbPolicy.h>

//#include <PPI\SBPPI.h>
#include <Protocol\PIDEController.h>
#include <Protocol\PDiskInfo.h>

#if CSM_SUPPORT
#include <Protocol/LegacyBios.h>
#endif

#ifdef CMOS_MANAGER_SUPPORT
  #if CMOS_MANAGER_SUPPORT
#include <CmosAccess.h>
  #endif
#endif

#include <Protocol\PIDEBus.h> 
#include <Protocol\PAhciBus.h>

#include "FastBoot.h"
#include "Core\EM\USB\rt\usbdef.h"

#include <Protocol\SimpleFileSystem.h>
//============================================================================
// Define
//============================================================================
                                        //(EIP71257+)>
#if !defined(AMITSE_SUPPORT) || (!AMITSE_SUPPORT)
    #ifndef TSE_MAJOR
        #define TSE_MAJOR 0
    #endif
    #ifndef TSE_MINOR
        #define TSE_MINOR 0
    #endif     
#endif
                                        //<(EIP71257+)
#define AMI_MEDIA_DEVICE_PATH_GUID \
    { 0x5023b95c, 0xdb26, 0x429b, 0xa6, 0x48, 0xbd, 0x47, 0x66, 0x4c, 0x80, 0x12 }

#define BOOT_IA32  44     //size in bytes of string L"EFI\\BOOT\\BOOTIA32.EFI"
#define BOOT_X64   42     //size in bytes of string L"EFI\\BOOT\\BOOTx64.EFI"

struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    CHAR16 FileName[22];
} FilePathNode = {
    {
        MEDIA_DEVICE_PATH,
        MEDIA_FILEPATH_DP,
#ifdef EFIx64
        BOOT_X64 + 4
#else
        BOOT_IA32 + 4
#endif
    },
#ifdef EFIx64
    { L"EFI\\BOOT\\BOOTx64.EFI"}
#else
    { L"EFI\\BOOT\\BOOTIA32.EFI" }
#endif
};

struct {
    EFI_DEVICE_PATH_PROTOCOL Header;
    CHAR16 FileName[20];
} TestFilePathNode = {
    {
        MEDIA_DEVICE_PATH,
        MEDIA_FILEPATH_DP,
#ifdef EFIx64
        38 + 4
#else
        40 + 4
#endif
    },
#ifdef EFIx64
    { L"EFI\\DP\\BOOTx64.EFI"}
#else
    { L"EFI\\DP\\BOOTIA32.EFI" }
#endif
};

#define	BOOT_FLOW_CONDITION_FAST_BOOT 7
#define BOOT_FLOW_CONDITION_NORMAL  0

#define EFI_SHELL_PROTOCOL_GUID \
  {0x47C7B223, 0xC42A, 0x11D2, 0x8E, 0x57, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}

#if CORE_COMBINED_VERSION > 0x40281
#define gBootName L"Boot%04X"		
#else
#define gBootName L"Boot%04x"
#endif
//============================================================================
// Globel Variable
//============================================================================
static EFI_GUID AmiMediaDevicePathGuid = AMI_MEDIA_DEVICE_PATH_GUID;
static EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
static EFI_GUID FastBootVariableGuid = FAST_BOOT_VARIABLE_GUID;
static EFI_GUID gSimpleTextOutProtocolGuid = EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID; 
static EFI_GUID gSimpleTextInProtocolGuid = EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID; 
static EFI_GUID guidBootFlow = BOOT_FLOW_VARIABLE_GUID;
#if FASTBOOT_NEED_RESTART
static EFI_GUID FastbootRestartGuid = FAST_BOOT_RESTART_GUID;
static EFI_GUID FastbootRestartCountGuid = FAST_BOOT_RESTART_COUNT_GUID;
#endif
extern EFI_GUID AmiPostMgrProtocolGuid;
extern EFI_HANDLE ThisImageHandle;

EFI_GUID gUsbPolicyGuid = EFI_USB_POLICY_PROTOCOL_GUID;
EFI_GUID gEfiPciIoProtocolGuid2 = EFI_PCI_IO_PROTOCOL_GUID; 
EFI_GUID FbConInStartedProtocolGuid = CONSOLE_IN_DEVICES_STARTED_PROTOCOL_GUID;
EFI_GUID FbConOutStartedProtocolGuid = CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID;
EFI_GUID FbBdsAllDriversConnectedProtocolGuid = \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93};

FAST_BOOT_TSE_PROTOCOL *gFastBootTseProtocol=NULL;  //(EIP63924+)

EFI_HANDLE      gDummyConInHdl = NULL;
EFI_HANDLE      gDummyConOutHdl = NULL;
EFI_HANDLE      EFIBootImageHanlde = NULL;
EFI_HANDLE      LegacyBootDeviceHandle = NULL;
EFI_HANDLE      *RootHandles;
UINTN           NumberOfHandles;
SETUP_DATA      FbSetupData;
static BOOLEAN  Runtime = FALSE;
BOOLEAN	StopBlkIo = FALSE;
EFI_HANDLE gHandle = NULL;
#ifdef CMOS_MANAGER_SUPPORT
  #if CMOS_MANAGER_SUPPORT
EFI_CMOS_ACCESS_INTERFACE *CmosInterface = NULL;
  #endif
#endif

static AMI_FAST_BOOT_PROTOCOL FastBootProtocol = { 
    NULL, 
    FbConnectInputDevices,
    IsRuntime
};

EFI_SIMPLE_TEXT_INPUT_PROTOCOL DummySimpleInProtocol = {
	DummyInReset,
	DummyReadKeyStroke,
	NULL
	} ;

SIMPLE_TEXT_OUTPUT_MODE	DummyMasterMode =
	{
	1, 		// MaxMode
	0, 		// Current Mode
	0x0F,	// Attribute
	0, 		// Column
	0, 		// Row
	1  		// CursorVisible
	};

EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	DummySimpleOutProtocol = {
	DummyReset,
	DummyOutputString,
	DummyTestString,
	DummyQueryMode,
	DummySetMode,
	DummySetAttribute,
	DummyClearScreen,
	DummySetCursorPosition,
	DummyEnableCursor,
	&DummyMasterMode
	};

typedef BOOLEAN (IsFastBootElink)(
    IN SETUP_DATA *Setupdata
);

extern IsFastBootElink IS_FAST_BOOT_LIST EndOfIsFastBootList;
IsFastBootElink* IsFastBootList[] = {IS_FAST_BOOT_LIST NULL};
										//(EIP62683+)>
typedef VOID (AfterAllDrirverConnectElink)();
extern AfterAllDrirverConnectElink AFTER_ALL_DRIVER_CONNECT_HOOK EndOfList;
AfterAllDrirverConnectElink* AfterAllDriverConnectList[] = {AFTER_ALL_DRIVER_CONNECT_HOOK NULL};
										//<(EIP62683+)
										//(EIP63924+)>
typedef BOOLEAN (FastBootCheckModeChangeElink)();
extern FastBootCheckModeChangeElink FAST_BOOT_CHECK_MODE_CHANGE_HOOK EndOfFastBootModeChangeList;
FastBootCheckModeChangeElink* FastBootModeChange[] = {FAST_BOOT_CHECK_MODE_CHANGE_HOOK NULL};
										//<(EIP63924+)
										//<(EIP62845+)
typedef VOID (BeforeConnectFastBootDeviceElink)();	//(EIP85135+)
extern BeforeConnectFastBootDeviceElink BEFORE_CONNECT_FAST_BOOT_DEVICE_HOOK EndOfBeforeConnectFastBootDeviceElink;
BeforeConnectFastBootDeviceElink* BeforeConnectFastBootDeviceHook[] = {BEFORE_CONNECT_FAST_BOOT_DEVICE_HOOK NULL};
										//<(EIP62845+)
typedef VOID (ReturnNormalModeElink)();
extern ReturnNormalModeElink RETURN_NORMAL_MODE_HOOK EndOfReturnNormalModeElink;
ReturnNormalModeElink* ReturnNormalModeHook[] = {RETURN_NORMAL_MODE_HOOK NULL};
FAST_BOOT_POLICY    *gFastBootPolicy;
BOOLEAN FBUsbSkipTableIsSet = FALSE;
UINT8   *BackupSkipTable = NULL;

EFI_USB_POLICY_PROTOCOL *gUsbPolicyProtocol = NULL;
BOOLEAN BackupUsbMassDriverSupport;

extern IS_VALID_FASTBOOT_BOOT_OPTION_FUNC_PTR  IS_VALID_FASTBOOT_BOOT_OPTION_FUNC;
IS_VALID_FASTBOOT_BOOT_OPTION_FUNC_PTR *IsValidFBBootOptionPtr = IS_VALID_FASTBOOT_BOOT_OPTION_FUNC;

#if FASTBOOT_NEED_RESTART
#define AMITSE_EVENT_BEFORE_BOOT_GUID \
  { 0x3677770f, 0xefb2, 0x43b2, 0xb8, 0xae, 0xb3, 0x2, 0xe9, 0x60, 0x48, 0x82 }

#define EFI_AMI_LEGACYBOOT_PROTOCOL_GUID            \
  {0x120d28aa, 0x6630, 0x46f0, 0x81, 0x57, 0xc0, 0xad, 0xc2, 0x38, 0x3b, 0xf5};

EFI_GUID    FBBeforeBootProtocolGuid = AMITSE_EVENT_BEFORE_BOOT_GUID;
EFI_GUID    FBBeforeLegacyBootProtocolGuid = EFI_AMI_LEGACYBOOT_PROTOCOL_GUID;
#endif

//============================================================================
// Function Definitions
//============================================================================

BOOLEAN CapsulePresent(VOID);
VOID ReadyToBoot(UINT16 OptionNumber);

VOID ConnectDevicePath(IN EFI_DEVICE_PATH_PROTOCOL *pPath);
VOID InstallFwLoadFile(VOID);
EFI_DEVICE_PATH_PROTOCOL* DiscoverPartition(
    IN EFI_DEVICE_PATH_PROTOCOL *DevicePath
);

#ifdef EFI_DXE_PERFORMANCE
VOID SavePerformanceData(IN EFI_EVENT Event, IN VOID *Context);
#endif

#if CORE_COMBINED_VERSION <= 0x40280   //Core 4.6.4.0
#if SINGAL_ALL_DRIVERS_CONNECTED_EVENT
extern VOID SignalProtocolEvent(IN EFI_GUID *ProtocolGuid);
#endif
#endif

EFI_STATUS ConnectFastEfiBootDevice();
EFI_STATUS ConnectFastLegacyBootDevice();

EFI_STATUS ConnectAllSataDevices();
EFI_STATUS ConnectHddDevices();
EFI_STATUS ConnectLastHddDevice();

//============================================================================
// Procedures
//============================================================================

//<EIP118901+> 2013/06/21 >>>
VOID BdsLoadStrings()
{
    EFI_STATUS      Status;
    EFI_HII_HANDLE  HiiHandle = NULL;
    Status = LoadStrings(TheImageHandle, &HiiHandle);
}
//<EIP118901+> 2013/06/21 >>>

#ifdef CMOS_MANAGER_SUPPORT
  #if CMOS_MANAGER_SUPPORT
  #else
UINT8 ReadCMOS(
    IN  UINT8   Address
)
{
    IoWrite8( (UINTN)CMOS_ADDR_PORT, Address );
    return IoRead8( (UINTN)CMOS_DATA_PORT );
}

VOID WriteCMOS(
    IN  UINT8   Address,
    IN  UINT8   Data
)
{
    IoWrite8( (UINTN)CMOS_ADDR_PORT, Address );
    IoWrite8( (UINTN)CMOS_DATA_PORT, Data );
}
  #endif
#endif 


VOID EnableLegacy16Fastboot()
{
#if AMILEGACY16_FASTBOOT_SOLUTION

    UINT8 LastBootedIPLIndex=0;

//clear the 7th bit of cmos index when fast boot is succeded.
//so that int 19 would not update the cmos index on fast boot path
//do this only if cmos index has a valid data (non 0xff value)
#ifdef CMOS_MANAGER_SUPPORT
  #if CMOS_MANAGER_SUPPORT
    CmosInterface->Read(
        CmosInterface,
        0x38,//CMOS_FASTBOOT_INDEX_REG,
        &LastBootedIPLIndex
    );
  #else
    LastBootedIPLIndex = ReadCMOS( 0x38 );
  #endif
#endif
                    
    if (LastBootedIPLIndex != 0xff) {
#ifdef CMOS_MANAGER_SUPPORT
  #if CMOS_MANAGER_SUPPORT
        CmosInterface->Write(
            CmosInterface,
            0x38,//CMOS_FASTBOOT_INDEX_REG,
            LastBootedIPLIndex & 0x7f
        );
  #else
        WriteCMOS( 0x38, LastBootedIPLIndex & 0x7F );
  #endif
#endif
    }
    
#endif //AMILEGACY16_FASTBOOT_SOLUTION
}

VOID DisableLegacy16Fastboot()
{
#if AMILEGACY16_FASTBOOT_SOLUTION

    UINT8 LastBootedIPLIndex=0;

#ifdef CMOS_MANAGER_SUPPORT
  #if CMOS_MANAGER_SUPPORT
    CmosInterface->Read(
        CmosInterface,
        0x38,//CMOS_FASTBOOT_INDEX_REG,
        &LastBootedIPLIndex
    );
  #else
    LastBootedIPLIndex = ReadCMOS( 0x38 );
  #endif
#endif

#ifdef CMOS_MANAGER_SUPPORT
  #if CMOS_MANAGER_SUPPORT
    CmosInterface->Write(
        CmosInterface,
        0x38,
        LastBootedIPLIndex|0x80
    );
  #else
    WriteCMOS( 0x38, LastBootedIPLIndex | 0x80 );
  #endif
#endif  

#endif //AMILEGACY16_FASTBOOT_SOLUTION
}

#if CORE_COMBINED_VERSION <= 0x40280   //Core 4.6.4.0
VOID CallDispatcherAgain()
{
    static EFI_GUID guidDXE = DXE_SERVICES_TABLE_GUID;
	DXE_SERVICES *pDxe;
	//before boot call dispatcher again.
	pDxe = GetEfiConfigurationTable(pST,&guidDXE);
	if (pDxe) pDxe->Dispatch();
}
#endif
//
// Connect Console realted Procedures ================>
//
EFI_DEVICE_PATH_PROTOCOL* FbAddDevicePath(
    EFI_DEVICE_PATH_PROTOCOL *pDp1, 
    EFI_DEVICE_PATH_PROTOCOL *pDp2
)
{
	if (!pDp2) return pDp1;
	if (!pDp1)
	{
		return DPCopy(pDp2);
	}
	else
	{
		pDp2 = DPAddInstance(pDp1,pDp2);
		pBS->FreePool(pDp1);
		return pDp2;
	}
} 

EFI_STATUS FbGetPciHandlesByClass(
    UINT8 Class, 
    UINT8 SubClass, 
    UINTN *NumberOfHandles, 
    EFI_HANDLE **HandleBuffer
)
{
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;

    if (!NumberOfHandles || !HandleBuffer) return EFI_INVALID_PARAMETER;
	//Get a list of all PCI devices
	Status = pBS->LocateHandleBuffer(
        ByProtocol,&gEfiPciIoProtocolGuid2, NULL, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return Status;
    *NumberOfHandles = 0;
	for(i=0; i<Number; i++)
	{
		EFI_PCI_IO_PROTOCOL *PciIo;
		UINT8 PciClass[4];
		Status=pBS->HandleProtocol(Handle[i],&gEfiPciIoProtocolGuid2,&PciIo);
		if (EFI_ERROR(Status)) continue;
		Status=PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, PCI_REV_ID_OFFSET, 1, &PciClass);
		if( PciClass[3]==Class && PciClass[2]==SubClass)
            Handle[(*NumberOfHandles)++] = Handle[i];
	}
	if (*NumberOfHandles == 0){
        pBS->FreePool(Handle);
        return EFI_NOT_FOUND;
    }
    *HandleBuffer = Handle;
    return EFI_SUCCESS;
}


VOID FbReportConnectConOutProgressCode()
{
    PROGRESS_CODE(DXE_CON_OUT_CONNECT);
}

VOID FbReportConnectConInProgressCode()
{
    PROGRESS_CODE(DXE_CON_IN_CONNECT);
}


VOID FbConnectVgaConOut()
{
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;
	EFI_DEVICE_PATH_PROTOCOL *OnBoard=NULL, *OffBoard=NULL;
    UINT64 PciAttributes;

	//Get a list of all PCI devices
	Status = pBS->LocateHandleBuffer(
        ByProtocol,&gEfiPciIoProtocolGuid2, NULL, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return;
	for(i=0; i<Number; i++)
	{
		EFI_PCI_IO_PROTOCOL *PciIo;
		EFI_DEVICE_PATH_PROTOCOL *Dp;
		UINT8 PciClass;
		Status=pBS->HandleProtocol(Handle[i],&gEfiPciIoProtocolGuid2,&PciIo);
		if (EFI_ERROR(Status)) continue;
		Status=PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClass);
		if (EFI_ERROR(Status)) continue;
		if (PciClass!=PCI_CL_DISPLAY) continue;
		Status=pBS->HandleProtocol(Handle[i],&gEfiDevicePathProtocolGuid,&Dp); 
		if (EFI_ERROR(Status)) continue;
		//We found Display adapter
		// Check if this is on-board device 
        //(EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE is set).
        Status = PciIo->Attributes(
            PciIo, EfiPciIoAttributeOperationGet, 0, &PciAttributes
        );
        if (   !EFI_ERROR(Status) 
            && (PciAttributes & EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE)
        )  OnBoard = FbAddDevicePath(OnBoard,Dp);
		else OffBoard = FbAddDevicePath(OffBoard,Dp);
	}
	pBS->FreePool(Handle);
    //Offboard has a higher priority
	OffBoard = FbAddDevicePath(OffBoard,OnBoard);
	if (OffBoard)
	{
		ConnectDevicePath(OffBoard);
		pBS->FreePool(OffBoard);
	}
}

#if CSM_SUPPORT
BOOLEAN FbInstallOnBoardVgaOpRom(
    UINTN HdlNum,
    EFI_HANDLE *pHandle,
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios, 
    BOOLEAN OnBoard
)
{
    UINTN   i;
    EFI_STATUS  Status;
    UINT64 PciAttributes;    
    UINTN   Flags;
    UINT64  Capabilities;	
    
	for(i=0; i<HdlNum; i++)	{
    	EFI_PCI_IO_PROTOCOL *PciIo;
    	EFI_DEVICE_PATH_PROTOCOL *Dp;
    	UINT8 PciClass;
    	Status=pBS->HandleProtocol(pHandle[i],&gEfiPciIoProtocolGuid2,&PciIo);
    	if (EFI_ERROR(Status)) continue;
        
		Status=PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClass);
		if (EFI_ERROR(Status)) continue;        
		if (PciClass!=PCI_CL_DISPLAY) continue;
        
		Status=pBS->HandleProtocol(pHandle[i],&gEfiDevicePathProtocolGuid,&Dp); 
		if (EFI_ERROR(Status)) continue;
        
        Status = PciIo->Attributes(
            PciIo, EfiPciIoAttributeOperationGet, 0, &PciAttributes
        );

        if ( !EFI_ERROR(Status) && (PciAttributes & EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE) && OnBoard)        
            continue;

										//(EIP75718)>
        Status = PciIo->Attributes (PciIo,
                                    EfiPciIoAttributeOperationSupported, 0,
                                    &Capabilities);     // Get device capabilities
        if (EFI_ERROR(Status)) continue;

        Status = PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationEnable,
                        //Capabilities & EFI_PCI_DEVICE_ENABLE,
                        Capabilities & (EFI_PCI_DEVICE_ENABLE | EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO),
                        NULL);              // Enable device
        if (EFI_ERROR(Status)) goto done; 
              

        Status = LegacyBios->CheckPciRom ( LegacyBios,
                                           pHandle[i],
                                           NULL,
                                           NULL,
                                           &Flags);
        if (EFI_ERROR(Status) || (Flags != 2)) goto done;
               
        Status = LegacyBios->InstallPciRom (
                              LegacyBios,
                              pHandle[i],
                              NULL,
                              &Flags,
                              NULL,
                              NULL,
                              NULL,
                              NULL
                              );

done:        
        if (!EFI_ERROR(Status)) return TRUE;
        else {
            
            if (PciIo != NULL) {     
            //
            // Turn off the PCI device and disable forwarding of VGA cycles to this device
            //
            PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationDisable,
                    Capabilities & EFI_PCI_DEVICE_ENABLE | EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO,
                    NULL);
            }
        }
										//<(EIP75718)
    }
    return FALSE;
}
#endif
VOID FbInstallVgaOpRom()
{
#if CSM_SUPPORT
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number;
    BOOLEAN VgaInstalled = FALSE;
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;

    //Locate LegacyBios Protocol
    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);    
    if (EFI_ERROR(Status)) return ;

	//Get a list of all PCI devices
	Status = pBS->LocateHandleBuffer(
        ByProtocol,&gEfiPciIoProtocolGuid2, NULL, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return;


    VgaInstalled = FbInstallOnBoardVgaOpRom(Number,Handle,LegacyBios,FALSE);
    if (VgaInstalled == FALSE)    
        VgaInstalled = FbInstallOnBoardVgaOpRom(Number,Handle,LegacyBios,TRUE);        

	pBS->FreePool(Handle);

    //If Legacy Vga OpRom is not installed successfully, then try to connect EFI VGA driver
    if (VgaInstalled == FALSE)    
         FbConnectVgaConOut();    
#endif    
}


VOID FbConnectPs2ConIn()
{
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;

	//Get a list of all PCI to ISA Bridges
	Status = FbGetPciHandlesByClass(
        PCI_CL_BRIDGE, PCI_CL_BRIDGE_SCL_ISA, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return;
	for(i=0; i<Number; i++)
	{
		EFI_DEVICE_PATH_PROTOCOL *Dp, *ChildDp;
		ACPI_HID_DEVICE_PATH Ps2Kbd = {
			{ACPI_DEVICE_PATH,ACPI_DP,sizeof(ACPI_HID_DEVICE_PATH)},
			EISA_PNP_ID(0x303),0
		};
		ACPI_HID_DEVICE_PATH Ps2Mouse = {
			{ACPI_DEVICE_PATH,ACPI_DP,sizeof(ACPI_HID_DEVICE_PATH)},
			EISA_PNP_ID(0xF03),0
		};
		Status=pBS->HandleProtocol(Handle[i],&gEfiDevicePathProtocolGuid,&Dp);
		if (EFI_ERROR(Status)) continue;
		pBS->ConnectController(Handle[i],NULL,NULL,FALSE);
		ChildDp=DPAddNode(Dp, &Ps2Kbd.Header);
		ConnectDevicePath(ChildDp);
		pBS->FreePool(ChildDp);
		ChildDp=DPAddNode(Dp, &Ps2Mouse.Header);
		ConnectDevicePath(ChildDp);
		pBS->FreePool(ChildDp);
	}
	pBS->FreePool(Handle);

}

VOID FbConnectUsbConIn()
{
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;
	//Get a list of all USB Controllers
	Status = FbGetPciHandlesByClass(
        PCI_CL_SER_BUS, PCI_CL_SER_BUS_SCL_USB, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return;
	for(i=0; i<Number; i++)
	{
        pBS->ConnectController(Handle[i],NULL,NULL,TRUE);
	}
	pBS->FreePool(Handle);
}


VOID FbConnecConsoleVariable(
    CHAR16* ConVar
)
{
    EFI_DEVICE_PATH_PROTOCOL *ConPath=NULL;
    UINTN Size = 0;

    if (EFI_ERROR(
        GetEfiVariable(ConVar, &EfiVariableGuid, NULL, &Size, &ConPath)
    )) return;

    //Connect all active console devices
    ConnectDevicePath(ConPath);
    pBS->FreePool(ConPath);
}

VOID FbConnectConOutVariable()
{
    FbConnecConsoleVariable(L"ConOut");
}

VOID FbConnectConInVariable()
{
    FbConnecConsoleVariable(L"ConIn");
}    

VOID FbInstallConsoleStartedProtocol(
    CHAR16* ConDevVar, 
    EFI_GUID* ProtocolGuid
)
{
    UINTN Size = 0;
    VOID *Interface;

    //Signal to Console Splitter that all console devices have been started
    //if at least one console device exists (ConDev variable exists)
    if (pRS->GetVariable(
            ConDevVar, &EfiVariableGuid, NULL, &Size, NULL
        ) == EFI_NOT_FOUND
    ) return;
    //if the protocol is already installed, return
    if (!EFI_ERROR(pBS->LocateProtocol(ProtocolGuid, NULL, &Interface)))
        return;
    pBS->InstallProtocolInterface(
        &TheImageHandle, ProtocolGuid, EFI_NATIVE_INTERFACE, NULL
    );
}


VOID FbInstallConOutStartedProtocol()
{
    FbInstallConsoleStartedProtocol(L"ConOutDev", &FbConOutStartedProtocolGuid);
}



VOID FbInstallConInStartedProtocol()
{
    FbInstallConsoleStartedProtocol(L"ConInDev", &FbConInStartedProtocolGuid);
}

VOID InstallDummySimpleTextProtocol()
{
    EFI_STATUS Status;

    if (pST->ConOut== NULL) 
    {      
        TRACE((-1,"FB:Install Dummy ConOut\n"));    
        
        Status = pBS->InstallProtocolInterface(&gDummyConOutHdl,
                                              &gSimpleTextOutProtocolGuid,
                                              EFI_NATIVE_INTERFACE,
                                              &DummySimpleOutProtocol);
        if (!EFI_ERROR(Status))
            pST->ConOut= &DummySimpleOutProtocol;    
    }  

    
    if (pST->ConIn == NULL) 
    {      
        TRACE((-1,"FB:Install Dummy ConIn\n"));            
        
        Status = pBS->InstallProtocolInterface(&gDummyConInHdl,
                                              &gSimpleTextInProtocolGuid,
                                              EFI_NATIVE_INTERFACE,
                                              &DummySimpleInProtocol);
        if (!EFI_ERROR(Status))
            pST->ConIn = &DummySimpleInProtocol;     
    }    
}

VOID UnInstallDummySimpleTextProtocol()
{
    if (gDummyConOutHdl!=NULL)
    {
        pBS->UninstallProtocolInterface(gDummyConOutHdl,
                                        &gSimpleTextOutProtocolGuid,
                                        &DummySimpleOutProtocol);
        pST->ConOut = 0;

    }

    if (gDummyConInHdl!=NULL)
    {
        pBS->UninstallProtocolInterface(gDummyConInHdl,
                                        &gSimpleTextInProtocolGuid,
                                        &DummySimpleInProtocol);        
        pST->ConIn = 0;
    }
}
										//(EIP85135+)>
BOOLEAN     IsRootBridgeHandle(EFI_HANDLE Handle)
{
    EFI_STATUS  Status;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *PciRootBridgeIo;
    EFI_GUID PciRootBridgeIoProtocolGuid           = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;

    Status = pBS->HandleProtocol (
                    Handle,
                    &gEfiDevicePathProtocolGuid,
                    &DevicePath
                    );
    if(EFI_ERROR(Status)) return FALSE;

    Status = pBS->HandleProtocol (
                    Handle,
                    &PciRootBridgeIoProtocolGuid,
                    &PciRootBridgeIo
                    );
    if(EFI_ERROR(Status)) return FALSE;

    return TRUE;

}


VOID ConnectEveryPciHandles()
{
    EFI_STATUS  Status;
	UINTN Number;
	EFI_HANDLE *Handle;    
    UINTN i,j;  
    SKIP_PCI_LIST *SkipPciList = gFastBootPolicy->SkipPciList;

	Status = pBS->LocateHandleBuffer(
        ByProtocol,&gEfiPciIoProtocolGuid2, NULL, &Number, &Handle
    );
    if (EFI_ERROR(Status)) return;

 	for(i=0; i<Number; i++)
	{
		EFI_PCI_IO_PROTOCOL *PciIo;
		UINT8 PciClass[4];
		Status=pBS->HandleProtocol(Handle[i],&gEfiPciIoProtocolGuid2,&PciIo);
		if (EFI_ERROR(Status)) continue;
		Status=PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, PCI_REV_ID_OFFSET, 1, &PciClass);

        //check skip table
        for (j=0;j<(gFastBootPolicy->SkipPciListSize/(sizeof(SKIP_PCI_LIST)));j++) {

            if (SkipPciList[j].SubClass == 0xFF && PciClass[3] == SkipPciList[j].Class) 
                break;
                
            if (PciClass[3] == SkipPciList[j].Class && PciClass[2] == SkipPciList[j].SubClass)
                break;
        }
        if (j<(gFastBootPolicy->SkipPciListSize/(sizeof(SKIP_PCI_LIST))))
            continue;
                
        //check fastboot policy
        if (gFastBootPolicy->UsbSupport == 0 && PciClass[3] == PCI_CL_SER_BUS && PciClass[2] == PCI_CL_SER_BUS_SCL_USB)
            continue;    

        if(PciClass[3] == PCI_CL_NETWORK && gFastBootPolicy->NetWorkStackSupport == 0) {
            pBS->ConnectController(Handle[i],NULL,NULL,FALSE);
            continue;
        }
        

        //all pass, then we connect this controller
        pBS->ConnectController(Handle[i],NULL,NULL,TRUE);        
            	
	}

    pBS->FreePool(Handle);      
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FbConnectEverything
//
//  Description:
//  This function connects all PCI handles excpet PCI devices in 
//  FAST_BOOT_PCI_SKIP_LIST
//
//  Input:
// 	None
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FbConnectEverything()
{
    UINTN i;
       
    for(i=0; i<NumberOfHandles; i++) {
        if(IsRootBridgeHandle(RootHandles[i]))
            ConnectEveryPciHandles();
        else     
            pBS->ConnectController(RootHandles[i],NULL,NULL,TRUE);        
    }

    pBS->FreePool(RootHandles);

// Signal it anyway for Consplitter to take care the ConIn/ConOut 
// after everything is connected
    FbInstallConsoleStartedProtocol(NULL, &FbConOutStartedProtocolGuid); 
    FbInstallConsoleStartedProtocol(NULL, &FbConInStartedProtocolGuid); 
}

VOID BeforeBDSFlow()
{
	pBS->LocateHandleBuffer(AllHandles, NULL, NULL, &NumberOfHandles, &RootHandles);
}

										//<(EIP85135+)
#if CORE_COMBINED_VERSION <= 0x40280   //Core 4.6.4.0
VOID FbAllDriverConnect()
{
#if CALL_DISPATCHER_AGAIN_IN_FASTBOOT         
    TRACE((-1,"FB: Call dispatcher again\n"));
    CallDispatcherAgain();
#endif
       
#if SINGAL_ALL_DRIVERS_CONNECTED_EVENT
    SignalProtocolEvent(&FbBdsAllDriversConnectedProtocolGuid);
#endif

}
#endif

										//(EIP85135+)>
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 920)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   SetUsbSkipTable
//
//  Description:
//  Skip all usb port in fastboot path by setting skip table in usb protocol. 
//
//  Input:
// 	None
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>  
VOID  SetUsbSkipTable()
{
    EFI_STATUS    Status = EFI_SUCCESS;
    EFI_GUID gEfiUsbProtocolGuid               = EFI_USB_PROTOCOL_GUID;    
    EFI_USB_PROTOCOL *UsbProtocol = NULL;    
    USB_GLOBAL_DATA   *UsbData = NULL;

    Status = pBS->LocateProtocol( &gEfiUsbProtocolGuid, \
                                      NULL, \
                                      &UsbProtocol );
    if (EFI_ERROR(Status)) return;

//backup skip table pointer
    UsbData = (USB_GLOBAL_DATA*)UsbProtocol->USBDataPtr;

    BackupSkipTable = UsbData->gUsbSkipListTable;

//Set new skip table    
    UsbProtocol->UsbCopySkipTable( \
            (USB_SKIP_LIST*)gFastBootPolicy->UsbSkipTable, \
                     (UINT8)gFastBootPolicy->UsbSkipTableSize);  

}   
#endif
										//<(EIP85135+)
										//(EIP63924)>
VOID FastConnectConsoles()
{    
    TRACE((-1,"FB:Connect Console...\n"));

    // Connect Console Out
    FbReportConnectConOutProgressCode();              

    PERF_START(0, L"ConnectVgaConOut", L"FB", 0);  
    if (gFastBootPolicy->VGASupport || gFastBootPolicy->UEfiBoot == TRUE){  
        TRACE((-1,"FB:Connect Vga\n"));    
        FbConnectVgaConOut();          
    } else {
        TRACE((-1,"FB:Install Vga OpRom Only\n"));            
        FbInstallVgaOpRom();        
    }
        
    PERF_END(0,L"ConnectVgaConOut",L"FB",0);  
    PERF_START(0,L"InstallConOutStartedProtocol",L"FB",0);          
    FbInstallConOutStartedProtocol();               
    PERF_END(0,L"InstallConOutStartedProtocol",L"FB",0);  

    // Connect Console In
    FbReportConnectConInProgressCode();
    
    PERF_START(0, L"ConnectUsbConIn", L"FB" , 0);       
										//(EIP85135)>
    if (gFastBootPolicy->UsbSupport >= 1){
                       
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 920)
        if (gFastBootPolicy->UsbSupport == 2){  

            //Disable Usb storage driver support
            pBS->LocateProtocol(&gUsbPolicyGuid, NULL, &gUsbPolicyProtocol);
            if (gUsbPolicyProtocol != NULL) {
                BackupUsbMassDriverSupport = gUsbPolicyProtocol->UsbDevPlcy->UsbMassDriverSupport;
                gUsbPolicyProtocol->UsbDevPlcy->UsbMassDriverSupport = FALSE;
            }

            
            TRACE((-1,"FB:Set Usb Skip Table\n"));           
            FBUsbSkipTableIsSet = TRUE;
            SetUsbSkipTable();
        }
#endif
        TRACE((-1,"FB:Connect Usb\n")); 
        FbConnectUsbConIn();
    } 
    PERF_END(0, L"ConnectUsbConIn", L"FB", 0);           
										//<(EIP85135)
    PERF_START(0, L"ConnectPs2ConIn", L"FB", 0); 										
    if (gFastBootPolicy->Ps2Support){
        TRACE((-1,"FB:Connect Ps2\n"));                        
        FbConnectPs2ConIn();            
    }    
    PERF_END(0, L"ConnectPs2ConIn", L"FB", 0); 

    PERF_START(0, L"InstallConInStartedProtocol",L"FB", 0);    
    FbInstallConInStartedProtocol();
    PERF_END(0, L"InstallConInStartedProtocol", L"FB", 0);        
    // Install Dumy protocol, if ConIn/ConOut is Null
    TRACE((-1,"FB:Connect Console...End\n"));
}
										//<(EIP63924)
//
// <============= Connect Console realted Procedures 
//
#if FASTBOOT_NEED_RESTART
VOID ResetForFastboot (
	IN EFI_EVENT Event,
	IN VOID *Context
)
{
	pRS->ResetSystem(EfiResetCold,0,0,NULL);
}
										
FastBootEnableRestart(
    UINTN Flag,
    UINTN Count )
{
	EFI_STATUS Status;
	EFI_EVENT Event;
	VOID *Registration;
										
	TRACE((-1,"FB:Normal boot need to restart.\n"));
	RegisterProtocolCallback(
				&FBBeforeBootProtocolGuid,
				ResetForFastboot,
				NULL, &Event, &Registration
				);
	RegisterProtocolCallback(
				&FBBeforeLegacyBootProtocolGuid,
				ResetForFastboot,
				NULL, &Event, &Registration
				);
										
	Status = pRS->SetVariable(FAST_BOOT_RESTART, 
				&FastbootRestartGuid, 
				EFI_VARIABLE_NON_VOLATILE |
				EFI_VARIABLE_BOOTSERVICE_ACCESS |
				EFI_VARIABLE_RUNTIME_ACCESS,
				sizeof(Flag),
				&Flag);
	Status = pRS->SetVariable(FAST_BOOT_RESTART_COUNT, 
				&FastbootRestartCountGuid, 
				EFI_VARIABLE_NON_VOLATILE |
				EFI_VARIABLE_BOOTSERVICE_ACCESS |
				EFI_VARIABLE_RUNTIME_ACCESS,
				sizeof(Count),
				&Count);		
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBoot
//
// Description: FastBoot entry point
//
// Input:       None	
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FastBoot(VOID)
{
										//(EIP63924+)>
    EFI_STATUS Status;
    EFI_GUID    FastBootTseGuid = FAST_BOOT_TSE_PROTOCOL_GUID;    
    
    Status = pBS->LocateProtocol(&FastBootTseGuid, NULL, &gFastBootTseProtocol);
    if (EFI_ERROR(Status)) return;
										//<(EIP63924+)
    gFastBootPolicy->InFastBootPath = TRUE;										
    FastBootWorker();

//if we're here - fast boot failed
    ReturnToNormalBoot();
    gFastBootPolicy->InFastBootPath = FALSE;										
    TRACE((-1,"FB: FastBoot Failure, return to BDS\n"));
}

VOID RemoveFilePathNode(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp)
{
    EFI_DEVICE_PATH_PROTOCOL *FileDpNode = NULL;
    UINTN   FileDpNodeSize;
    EFI_DEVICE_PATH_PROTOCOL *TempDp = Dp;    
    UINTN DpSize = DPLength(Dp);
    UINTN RemainingDpLength=0;
    UINT8 ReaminingDpBuffer[100];
    
    for( ; !(isEndNode(TempDp)); TempDp = NEXT_NODE(TempDp)) {
        if(TempDp->Type == MEDIA_DEVICE_PATH && 
            TempDp->SubType == MEDIA_FILEPATH_DP) {
            FileDpNode = TempDp;
            break;
        }
    }

    if (FileDpNode == NULL) return;
    
    RemainingDpLength = DPLength(FileDpNode);
    FileDpNodeSize = NODE_LENGTH(FileDpNode);

    pBS->SetMem(ReaminingDpBuffer,100,0);

    pBS->CopyMem(ReaminingDpBuffer,FileDpNode,RemainingDpLength);

    pBS->SetMem(FileDpNode,RemainingDpLength,0);

    pBS->CopyMem(FileDpNode,
        (VOID*)((UINTN)ReaminingDpBuffer+FileDpNodeSize),
        RemainingDpLength - FileDpNodeSize);
}

#ifdef EFI_DXE_PERFORMANCE
VOID UpdatePolicyForTestMode()
{
    BOOLEAN UsbMassStorage = FALSE;
    BOOLEAN HddFilePath = FALSE;
    EFI_DEVICE_PATH_PROTOCOL *Dp = gFastBootPolicy->FastBootOption;
    EFI_DEVICE_PATH_PROTOCOL *NewDp=NULL;
    EFI_DEVICE_PATH_PROTOCOL *TempDp=NULL;    
    UINTN   NewDpSize;
	UINT32  LoadOptionsSize = 0;
	VOID    *LoadOptions;
    EFI_STATUS  Status;    

    if(gFastBootPolicy->TestMode == FALSE || gFastBootPolicy->UEfiBoot == FALSE) return;

    if(!IsSupportedDevice(gFastBootPolicy->FastBootOption, &UsbMassStorage,&HddFilePath))
        return;

    LoadOptions = (UINT8*)Dp + DPLength(Dp);
    LoadOptionsSize = *(UINT32*)LoadOptions;   

	NewDpSize = DPLength(Dp)+ LoadOptionsSize+ sizeof(UINT32)+ \
        NODE_LENGTH(&TestFilePathNode.Header);
   
    Status = pBS->AllocatePool(EfiBootServicesData,NewDpSize,&NewDp);
    if(EFI_ERROR(Status)) return;
   
    pBS->SetMem(NewDp,NewDpSize,0);
    pBS->CopyMem(NewDp,Dp,DPLength(Dp));

    //Replace file path from "efi\boot\" to "efi\dp\"
    RemoveFilePathNode(NewDp);      
    TempDp = DPAddNode(NewDp, &TestFilePathNode.Header);

    pBS->CopyMem(NewDp,TempDp,DPLength(TempDp));

    //Copy optional data
    pBS->CopyMem( (VOID*)((UINTN)NewDp+DPLength(NewDp)),
                   LoadOptions, 
                   LoadOptionsSize+sizeof(UINT32));


    gFastBootPolicy->FastBootOption = NewDp;
    pBS->FreePool(TempDp);

    gFastBootPolicy->CheckBootOptionNumber = FALSE;

}
#endif

VOID ShowFastBootPolicy()
{
    EFI_DEVICE_PATH_PROTOCOL *Dp = gFastBootPolicy->FastBootOption;    
    UINTN   FastBootOptionSize=0;
	VOID    *LoadOptions;
	UINT32  LoadOptionsSize = 0;
    UINT8   *ptr8=NULL;  
    SKIP_PCI_LIST *PciSkipList=NULL;
#if SUPPORT_RAID_DRIVER	
    SATA_DEVICE_DATA *SataDevice=NULL;
#endif
    UINTN   i,j;
    USB_SKIP_LIST  *usbskip = NULL; //(EIP96276.7)+

    TRACE((-1,"FB: ==================================================\n"));
    TRACE((-1,"FB: FastBootPolicy->FastBootEnable = %x\n",gFastBootPolicy->FastBootEnable));
    TRACE((-1,"FB: FastBootPolicy->TestMode = %x\n",gFastBootPolicy->TestMode));

    TRACE((-1,"FB: FastBootPolicy->UEfiBoot = %x\n",gFastBootPolicy->UEfiBoot));
    TRACE((-1,"FB: FastBootPolicy->BootOptionNumber = %x\n",gFastBootPolicy->BootOptionNumber));
    TRACE((-1,"FB: FastBootPolicy->DevStrCheckSum = %x\n",gFastBootPolicy->DevStrCheckSum));

    FastBootOptionSize = DPLength(Dp);
    if (gFastBootPolicy->UEfiBoot) {
        LoadOptions = (UINT8*)Dp + DPLength(Dp);
        LoadOptionsSize = *(UINT32*)LoadOptions;  
        FastBootOptionSize += LoadOptionsSize+sizeof(UINT32);
    }

    TRACE((-1,"FB: FastBootPolicy->FastBootOption\n"));         
    ptr8=(UINT8*)Dp;
    for (i=0;i<FastBootOptionSize;)
    {
        for(j=0;j<0x10 && i<FastBootOptionSize;j++)
        {
            TRACE((-1,"%02X ",ptr8[i]));
            i++;
        }
        TRACE((-1," \n"));
    }
           
    TRACE((-1,"FB: FastBootPolicy->LastBootFailure = %x\n",gFastBootPolicy->LastBootFailure));
    TRACE((-1,"FB: FastBootPolicy->LastBootVarPresence = %x\n",gFastBootPolicy->LastBootVarPresence));
    TRACE((-1,"FB: FastBootPolicy->BootCount = %x\n",gFastBootPolicy->BootCount));

#if SUPPORT_RAID_DRIVER
    SataDevice = gFastBootPolicy->SataDevice;
    for(i=0;i<MAX_SATA_DEVICE_COUNT && SataDevice[i].BDF!=0;i++)
    {
     
        TRACE((-1,"FB: FastBootPolicy->SataDevice[%d],n",i));
	
        TRACE((-1,"BDF:%x, CalssCode:%x, DveType:%x, PortNum:%x\n",\
            SataDevice[i].BDF,\
            SataDevice[i].ClassCode,\
            SataDevice[i].DevType,\
            SataDevice[i].PortNum));  
        
        TRACE((-1,"Serial Number: "));
	
        for(j=0;j<20;j++)
        {
            TRACE((-1,"%02X ",SataDevice[i].SerialNum[j]));
        }
        TRACE((-1," \n"));
    }
#endif

    TRACE((-1,"FB: FastBootPolicy->CheckBootOptionNumber = %x\n",gFastBootPolicy->CheckBootOptionNumber));
    TRACE((-1,"FB: FastBootPolicy->CheckDevStrCheckSum = %x\n",gFastBootPolicy->CheckDevStrCheckSum));
    TRACE((-1,"FB: FastBootPolicy->SataSupport = %x\n",gFastBootPolicy->SataSupport));
    TRACE((-1,"FB: FastBootPolicy->VGASupport = %x\n",gFastBootPolicy->VGASupport));
    TRACE((-1,"FB: FastBootPolicy->UsbSupport = %x\n",gFastBootPolicy->UsbSupport));

                                        //(EIP96276.7)>
    usbskip = gFastBootPolicy->UsbSkipTable;
    for (i = 0; i < gFastBootPolicy->UsbSkipTableSize; i++)
    {
        TRACE((-1,"FB: FastBootPolicy->UsbSkipTable[%d] = {%02X,%02X,%04X,%02X,%08X,%02X}\n",i,usbskip->bSkipType,usbskip->bFlag,usbskip->wBDF,usbskip->bRootPort,usbskip->dRoutePath,usbskip->bBaseClass));
        usbskip++;
    }
                                        //<(EIP96276.7)

    TRACE((-1,"FB: FastBootPolicy->Ps2Support = %x\n",gFastBootPolicy->Ps2Support));
    TRACE((-1,"FB: FastBootPolicy->NetWorkStackSupport = %x\n",gFastBootPolicy->NetWorkStackSupport));

    for (i=0,PciSkipList = gFastBootPolicy->SkipPciList;i<gFastBootPolicy->SkipPciListSize/sizeof(SKIP_PCI_LIST);i++)
        TRACE((-1,"FB: FastBootPolicy->SkipPciList[%d] = Class:%x,SubClass:%x\n",i,PciSkipList[i].Class,PciSkipList[i].SubClass));

    TRACE((-1,"FB: FastBootPolicy->CheckPassword = %x\n",gFastBootPolicy->CheckPassword));

    TRACE((-1,"FB: FastBootPolicy->SkipTSEHandshake = %x\n",gFastBootPolicy->SkipTSEHandshake));

    TRACE((-1,"FB: ==================================================\n"));

}
                                        //(EIP96276.4)>>
BOOLEAN IsValidFastBootOption(
    IN  UINTN BootOrderIndex, 
    IN  EFI_LOAD_OPTION *BootOption)
{    
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    CHAR16                   *Description;
    CHAR16      *gWindowsBootManagerStr = L"Windows Boot Manager";    
    BOOLEAN LegacyType = FALSE;
    BOOLEAN UsbDevice = FALSE;
    BOOLEAN HardDrive = FALSE;
    BOOLEAN CDROM = FALSE;
    BOOLEAN NetWork = FALSE;
    BOOLEAN WindowsBootManager = FALSE;
    
//check attribute

    if (!(BootOption->Attributes & LOAD_OPTION_ACTIVE)) return FALSE;

//check windows boot manager
	
    Description = (CHAR16 *)(BootOption + 1);
    if(!MemCmp(gWindowsBootManagerStr,Description,Strlen((char*)gWindowsBootManagerStr)))
        WindowsBootManager = TRUE;
    
//check device type
	
    Dp = (EFI_DEVICE_PATH_PROTOCOL *)((UINT8*)Description + (Wcslen(Description) + 1) * sizeof(CHAR16));
    
    for( ; !(isEndNode(Dp)); Dp = NEXT_NODE(Dp)) {
        if(Dp->Type == BBS_DEVICE_PATH) LegacyType = TRUE; 
	
        if(Dp->Type == MESSAGING_DEVICE_PATH && Dp->SubType == MSG_USB_DP)
            UsbDevice = TRUE;
	
        if(Dp->Type == MESSAGING_DEVICE_PATH && Dp->SubType == MSG_MAC_ADDR_DP)
            NetWork = TRUE;        
	
        if(Dp->Type == MEDIA_DEVICE_PATH && Dp->SubType == MEDIA_HARDDRIVE_DP) 
            HardDrive = TRUE;
        
        if(Dp->Type == MEDIA_DEVICE_PATH && Dp->SubType == MEDIA_CDROM_DP) 
            CDROM = TRUE;
    }
	
    TRACE((-1,"FB: BootOrder Index %x\n",BootOrderIndex));
    TRACE((-1,"FB: Windows Boot Manager: %x\n",WindowsBootManager));
    TRACE((-1,"FB: Legacy %x,Usb %x, HardDrive %x, CDROM %x, NetWork %x\n", \
        LegacyType,UsbDevice,HardDrive,CDROM,NetWork));    
    
// there is some samples for selecting a boot option as fast boot device.
/*
//Case 1. Fast boot with windows boot manager and it's the highest priority in boot order.
    if(BootOrderIndex == 0 && WindowsBootManager == 1) return TRUE;

//Case 2. don't support Legacy device
    if(LegacyType == TRUE) return FALSE;

//Case3. don't support usb type
    if(UsbDevice == TRUE) return FALSE;
*/

    return TRUE;   
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsOneOfDP
//
// Description: Determines whether a device path, pAll, contains another 
//              device path, pOne.  
//
// Input:       
//  IN EFI_DEVICE_PATH_PROTOCOL *pAll - The device path to be scanned.
//  IN EFI_DEVICE_PATH_PROTOCOL *pOne - The device path to locate within pAll.
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN 
IsOneOfDP(
  IN EFI_DEVICE_PATH_PROTOCOL *pAll, 
  IN EFI_DEVICE_PATH_PROTOCOL *pOne
)
{
    EFI_DEVICE_PATH_PROTOCOL *pPath;
    
    pPath = pOne;

    do{
        if (isEndNode(pAll)) return FALSE;        
        
        if (DPLength(pAll) < DPLength(pOne)) return FALSE;
    
        if(!(pAll->Type == pPath->Type && pAll->SubType == pPath->SubType))
        {
            pAll = NEXT_NODE(pAll);
            continue;
        }

        if (!MemCmp(pAll,pOne,DPLength(pOne)))
            return TRUE;
        else
            pAll = NEXT_NODE(pAll);
        
    }while(TRUE);
    
}
                                        //<<(EIP96276.4)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindDevicePath
//
// Description: Search DevicePath and find out indicated device path node.
//
// Input:       
//	IN OUT   EFI_DEVICE_PATH_PROTOCOL *DevicePath - Searched device path
//	IN       UINT8                    Type - Indicated device path type
//	IN       UINT8                    SubType - Indicated device path sub type
//
// Output:      EFI_DEVICE_PATH_PROTOCOL - return indicated device path 
//                                         pointer otherwise NULL.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_DEVICE_PATH_PROTOCOL* 
FindDevicePath (
  IN OUT   EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  IN       UINT8                    Type,
  IN       UINT8                    SubType
)
{
    if (DevicePath == NULL) {
        return NULL;
    }
	
    while (!isEndNode (DevicePath)) {
        if (DevicePath->Type == Type && DevicePath->SubType== SubType)
            return DevicePath;
        
        DevicePath = NEXT_NODE (DevicePath);
    }
	
    return NULL;
}                                       

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastConnectSata
//
// Description: Connect Sata controller in fast boot path.
//
// Input:       
//  None
//
// Output:    
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
FastConnectSata()
{
    
    TRACE((-1,"FB:Connect Sata\n"));    

    switch(gFastBootPolicy->SataSupport)
    {
        case 0: // only connect previous boot HDD?
            return ConnectLastHddDevice();        
        case 1: // connect all sata device
            ConnectAllSataDevices();        
            break;
#if SUPPORT_RAID_DRIVER			
        case 2: // only connect HDDs, ODD & Port Multiplier will be skipped.
            return ConnectHddDevices();        
#endif			
    }
    
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootWorker
//
// Description: FastBoot main function
//
// Input:       None	
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FastBootWorker(VOID)
{
    EFI_EVENT  FastBootReadyToBootEvent;
    CHAR16     BootOptionName[9];
	EFI_LOAD_OPTION *BootOption = NULL;    
    UINTN      Size;
    EFI_STATUS Status;
    UINT16     *BootOrder = NULL;
    UINT32     BootFlow;
    UINT8       i;                      //(EIP62683+)
    BOOLEAN     VaildBootOption = FALSE;
    UINTN       BootOptionSize; 		//(EIP96276.4+)
#if FASTBOOT_NEED_RESTART	
	UINTN    Flag = 1;
	UINTN    Count = 0;
#endif	
	
    TRACE((-1, "FB: FastBoot started\n"));
	Size = sizeof(BootFlow);
	Status = pRS->GetVariable(L"BootFlow", &guidBootFlow, NULL, &Size, (VOID *)&BootFlow);
	if(!EFI_ERROR(Status) && (BootFlow != BOOT_FLOW_CONDITION_NORMAL)) {
		// Some other driver wants different bootflow - abandon fast boot.
#if FASTBOOT_NEED_RESTART		
		TRACE((-1,"FB : Normal boot need to notify.\n"));
		//Initial Reboot Flag
		Status = pRS->SetVariable(FAST_BOOT_RESTART, 
				&FastbootRestartGuid, 
				EFI_VARIABLE_NON_VOLATILE |
				EFI_VARIABLE_BOOTSERVICE_ACCESS |
				EFI_VARIABLE_RUNTIME_ACCESS,
				sizeof(Flag),
				&Flag);
		Status = pRS->SetVariable(FAST_BOOT_RESTART_COUNT, 
				&FastbootRestartCountGuid, 
				EFI_VARIABLE_NON_VOLATILE |
				EFI_VARIABLE_BOOTSERVICE_ACCESS |
				EFI_VARIABLE_RUNTIME_ACCESS,
				sizeof(Count),
				&Count);

        Status = CreateReadyToBootEvent(TPL_CALLBACK,
                                        FastBootReadyToBootNotify,
                                        NULL,
                                        &FastBootReadyToBootEvent);
#endif										
            return;		
	}
    PERF_START(0, L"FastBoot", L"FB", 0);  

#if CAPSULE_SUPPORT
    if(CapsulePresent())
        return; 
#endif

    if(OemConfigurationChanged())
        return;   

        Status = CreateReadyToBootEvent(TPL_CALLBACK,
                                        FastBootReadyToBootNotify,
                                        NULL,
                                        &FastBootReadyToBootEvent);
    	if (EFI_ERROR(Status)) 
            return;

        if (!gFastBootPolicy->LastBootVarPresence) return;
        
#ifdef EFI_DXE_PERFORMANCE
        UpdatePolicyForTestMode();
#endif

        ShowFastBootPolicy();        
        
        if (gFastBootPolicy->CheckBootOptionNumber) {
        
            Size = 0;
            Status = GetEfiVariable(L"BootOrder", &EfiVariableGuid, NULL, &Size, &BootOrder);

            for (i=0;i<Size/sizeof(UINT16);i++,BootOption = NULL) {	//(EIP96276.4)

                Swprintf(BootOptionName, gBootName, BootOrder[i]);
                Status = GetEfiVariable(BootOptionName, &EfiVariableGuid, NULL, &BootOptionSize, &BootOption);//(EIP96276.4)
                if(EFI_ERROR(Status))
                    return;         
                
                VaildBootOption = IsValidFBBootOptionPtr(i,BootOption);
                if (VaildBootOption) break;

                pBS->FreePool(BootOption);

                if (VaildBootOption == FALSE && i == (Size/sizeof(UINT16) -1 )) {
                    TRACE((-1, "FB: There is no valid boot option\n"));
                    pBS->FreePool(BootOrder);
                    return;

                }
            }
            
            TRACE((-1, "FB: LastBootOption=%x, BootOrder[%d]=%x\n",gFastBootPolicy->BootOptionNumber,i,BootOrder[i]));
            
            if(gFastBootPolicy->BootOptionNumber != BootOrder[i]) 
            {
            //
            // BootOption Number check fail, then check device path.
            // If device path is also wrong, abort the fast boot.
            //                
                EFI_DEVICE_PATH_PROTOCOL *Dp;
                CHAR16                   *Description;   
                Description = (CHAR16 *)(BootOption + 1);                
                Dp = (EFI_DEVICE_PATH_PROTOCOL *)((UINT8*)Description + (Wcslen(Description) + 1) * sizeof(CHAR16));

                if(!IsOneOfDP(gFastBootPolicy->FastBootOption,Dp)) {
                    pBS->FreePool(BootOrder);
                    pBS->FreePool(BootOption);
                    return;
                }
                
                TRACE((-1,"FB: Update new boot option number\n")); 
                gFastBootPolicy->BootOptionNumber = BootOrder[i];               
            }

            pBS->FreePool(BootOrder);
            pBS->FreePool(BootOption);
        }

    
    PERF_START(0,L"FastBootConnectConsole",L"FB" ,0);
    FastConnectConsoles();
    PERF_END(0,L"FastBootConnectConsole",L"FB",0);

//<EIP118901+> 2013/06/21 >>>
    BdsLoadStrings();
//<EIP118901+> 2013/06/21 <<<

    PERF_START(0,L"BeforeConnectFbDevElink",L"FB",0);
										//(EIP62683+)>
    // before all driver connect elink 
    for (i=0;BeforeConnectFastBootDeviceHook[i]; i++)
        BeforeConnectFastBootDeviceHook[i](); //(EIP85135)

										//<(EIP62683+)
    PERF_END(0,L"BeforeConnectFbDevElink",L"FB",0);	
    Status = FastConnectSata();
    if (EFI_ERROR(Status)) return;
    
    PERF_START(0,L"ConnectFbDev",L"FB",0);
    if(gFastBootPolicy->UEfiBoot == TRUE)
        Status = ConnectFastEfiBootDevice();
    else
        Status = ConnectFastLegacyBootDevice();
    PERF_END(0,L"FB",L"ConnectFbDev",0);

    if(EFI_ERROR(Status)) return;


										//(EIP62683+)>
    PERF_START(0,L"AfterConnectFbDevElink",L"FB",0);										
    // after all driver connect elink 
    for (i=0;AfterAllDriverConnectList[i]; i++)
        AfterAllDriverConnectList[i]();
    PERF_END(0,L"AfterConnectFbDevElink",L"FB",0);    
										//<(EIP62683+)
    

#if CORE_COMBINED_VERSION <= 0x40280   //Core 4.6.4.0
    FbAllDriverConnect();
#endif

    if((gFastBootPolicy->SkipTSEHandshake == 0) && (TSE_MAJOR >= 0x02) && (TSE_MINOR >= 0x10)) {
        PERF_START(0,L"TSE",L"FB",0);        
        Status = TseHandShake();
        if(Status == EFI_ABORTED)   //fast boot failed, proceed to full boot
            return;
    }

                                        //(EIP63924+)>
//Stop CheckForKey callback timer in TSE
        gFastBootTseProtocol->FastBootStopCheckForKeyTimer();
                                        //<(EIP63924+)
//if we are here, somehow we failed launch fast boot through TSE - do it on our own
    
    if(gFastBootPolicy->UEfiBoot == TRUE)
        FastEfiBoot();
    else
        FastLegacyBoot();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsBootToShell
//
// Description: Function to determine if the boot path is to UEFI Shell
//
// Input:
//  IN EFI_DEVICE_PATH_PROTOCOL *Dp - pointer to device path of bootable device
//
// Output:      TRUE - if it's UEFI Shell boot path, FALSE otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsBootToShell(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp
)
{
    if(Dp->Type == MEDIA_DEVICE_PATH &&
       Dp->SubType == MEDIA_VENDOR_DP &&
       !guidcmp(&(((VENDOR_DEVICE_PATH *)Dp)->Guid), &AmiMediaDevicePathGuid))
       return TRUE;
    
    return FALSE;
}
                                        //(EIP63924+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckPostManagerKey
//
// Description: Check TSE Post key is pressed or not.
//
// Input:		None
//
// Output:      TRUE - Post key is pressed
//              FALSE - Post key is not pressed
//----------------------------------------------------------------------------
//<AMI_PHDR_END>										
BOOLEAN CheckPostManagerKey()
{
    EFI_STATUS CheckForKeyStatus;
    BOOLEAN EnterSetup;
    UINT32  BootFlow;

    CheckForKeyStatus = gFastBootTseProtocol->FastBootCheckForKey(&EnterSetup,&BootFlow);
    if(CheckForKeyStatus == EFI_SUCCESS) return TRUE;
    return FALSE;  
}
                                        //<(EIP63924+)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckConnectedHdd
//
// Description: Check connected Hdds are as same as previous boot's.
//
// Input:       
//	IN UINT16 BDF - BDF of previous boot's Hdd 
//	IN UINT16 ClassCode - Class of previous boot's Hdd 
//	IN UINT8  PortNum - Port Number of previous boot's Hdd 
//
// Output:    
//  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#if SUPPORT_RAID_DRIVER
EFI_STATUS 
CheckConnectedHdd(
  IN UINT16 BDF,
  IN UINT16 ClassCode,
  IN UINT8  PortNum 
)
{
    EFI_STATUS  Status;       
    EFI_GUID    DiskInfoGuid = EFI_DISK_INFO_PROTOCOL_GUID;
    EFI_GUID    DiskInfoIdeGuid = EFI_DISK_INFO_IDE_INTERFACE_GUID;
    EFI_GUID    DiskInfoAhciGuid = EFI_DISK_INFO_AHCI_INTERFACE_GUID;    
    EFI_DISK_INFO_PROTOCOL  *DiskInfoProtocol;
    EFI_HANDLE  *Handle;
    UINTN   Count;
    UINTN   PciSeg,PciBus,PciDev,PciFun;    
    UINT16  DetectedHddBDF;
    UINT16  DetectedHddClassCode;
    UINT8   DetectedHddPortNum;
    UINT8   *DetectedHddSerialNum = NULL;
    BOOLEAN StrucFound = FALSE;
    UINT8   i;
    SATA_DEVICE_DATA *SataDevice = (SATA_DEVICE_DATA*)gFastBootPolicy->SataDevice;    
   
//
// Find out sata device structure the from last boot stat devcie list
//
    for (i=0;i<MAX_SATA_DEVICE_COUNT && SataDevice->BDF!=0;SataDevice++) {
        if (BDF == SataDevice->BDF &&\
            ClassCode == SataDevice->ClassCode &&\
            PortNum == SataDevice->PortNum)
        {
            StrucFound = TRUE;
            break;
        }        
    }    
    if (StrucFound == FALSE) return EFI_NOT_FOUND;

//
// Find out serial number of detected Hdd.
//    

    Status=pBS->LocateHandleBuffer(ByProtocol,&DiskInfoGuid,NULL,&Count,&Handle);
    if (EFI_ERROR(Status)) return Status;

    for(i=0;i<Count;i++)
    {
        Status=pBS->HandleProtocol(Handle[i],&DiskInfoGuid,(VOID**)&DiskInfoProtocol);
        if(EFI_ERROR(Status)) continue;

        if(!guidcmp(&DiskInfoProtocol->Interface,&DiskInfoIdeGuid)) {
        //            
        // Ide diskInfo
        //
            IDE_BUS_PROTOCOL    *IdeInterface = ((IDE_DISK_INFO*)DiskInfoProtocol)->IdeBusInterface;
            EFI_PCI_IO_PROTOCOL *PciIo = IdeInterface->PciIO;
            
            Status = PciIo->GetLocation(PciIo, &PciSeg, &PciBus, &PciDev, &PciFun);
            ASSERT_EFI_ERROR(Status);

            DetectedHddBDF = (UINT16)((PciBus << 8) | (PciDev << 3) | PciFun );
                
            Status = PciIo->Pci.Read (PciIo,\
                EfiPciIoWidthUint16,\
                0x0A,\
                1,\
                &DetectedHddClassCode);            
            ASSERT_EFI_ERROR(Status);

            DetectedHddPortNum = IdeInterface->IdeDevice.Channel | IdeInterface->IdeDevice.Device<<1;

            if (DetectedHddBDF != BDF ||\
                DetectedHddClassCode != ClassCode ||\
                DetectedHddPortNum != PortNum)
                continue;                

            DetectedHddSerialNum = IdeInterface->IdeDevice.IdentifyData.Serial_Number_10;
            break;
        
        }else if (!guidcmp(&DiskInfoProtocol->Interface,&DiskInfoAhciGuid)) {
        //
        //Devie is detected in Ahci mode
        //  
            SATA_DEVICE_INTERFACE *SataInterface = ((SATA_DISK_INFO*)DiskInfoProtocol)->SataDevInterface;
            EFI_PCI_IO_PROTOCOL *PciIo = SataInterface->AhciBusInterface->PciIO;
                    
            Status = PciIo->GetLocation(PciIo, &PciSeg, &PciBus, &PciDev, &PciFun);
            ASSERT_EFI_ERROR(Status);
  
            DetectedHddBDF = (UINT16)((PciBus << 8) | (PciDev << 3) | PciFun );
            
            Status = PciIo->Pci.Read (PciIo,\
                EfiPciIoWidthUint16,\
                0x0A,\
                1,\
                &DetectedHddClassCode);            
            ASSERT_EFI_ERROR(Status);

            DetectedHddPortNum = SataInterface->PortNumber;

            if (DetectedHddBDF != BDF ||\
                DetectedHddClassCode != ClassCode ||\
                DetectedHddPortNum != PortNum)
                continue;      

            DetectedHddSerialNum = SataInterface->IdentifyData.Serial_Number_10;
            break;           
            
        }    
    }

    pBS->FreePool(Handle);

    if (DetectedHddSerialNum == NULL) return EFI_NOT_FOUND;

//
// Compare Serial number is as same as last boot.
//

    if(!MemCmp(DetectedHddSerialNum,SataDevice->SerialNum,20))
        return EFI_SUCCESS;


    TRACE((-1,"FB: ConnectedHdd is match with previous boot\n"));

    TRACE((-1,"Detected BDS %x, ClassCode %x, PortNum %x\n",DetectedHddBDF,DetectedHddClassCode,DetectedHddPortNum));

    TRACE((-1,"Detected Serial Number: "));
    
    for(i=0;i<20;i++)
    {
        TRACE((-1,"%02x ",DetectedHddSerialNum[i]));
    }
    TRACE((-1," \n"));


    TRACE((-1,"Last BDS %x, ClassCode %x, PortNum %x\n",SataDevice->BDF,SataDevice->ClassCode,SataDevice->PortNum));
    
    TRACE((-1,"Last Serial Number: "));
    
    for(i=0;i<20;i++)
    {
        TRACE((-1,"%02x ",SataDevice->SerialNum[i]));
    }
    TRACE((-1," \n"));

    return EFI_DEVICE_ERROR;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsSataDevicePath
//
// Description: Check device path is for sata devcie or not
//
// Input:       
//	IN EFI_DEVICE_PATH_PROTOCOL *Dp - Device path need to be checked.
//
// Output:    
//  BOOLEAN TRUE,the devcie path is for sata devcie, otherwise False.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsSataDevicePath(
  IN EFI_DEVICE_PATH_PROTOCOL *Dp
)
{
    EFI_DEVICE_PATH_PROTOCOL *TempDp = NULL;
    
    TempDp = FindDevicePath(Dp,MESSAGING_DEVICE_PATH,MSG_SATA_DP);
    if (TempDp != NULL) return TRUE;

    TempDp = FindDevicePath(Dp,MESSAGING_DEVICE_PATH,MSG_ATAPI_DP);
    if (TempDp != NULL) return TRUE;

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsLegacyRaidDevicePath
//
// Description: Check device path is legacy raid device path or not.
//
// Input:       
//	IN EFI_DEVICE_PATH_PROTOCOL *Dp - Device path need to be checked.
//
// Output:    
//  BOOLEAN TRUE,the devcie path is for legacy raid devcie, otherwise False.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsLegacyRaidDevicePath(
  IN EFI_DEVICE_PATH_PROTOCOL *Dp
)
{
    EFI_DEVICE_PATH_PROTOCOL *TempDp = NULL;
    PCI_DEVICE_PATH *PciDp = NULL;
#if SUPPORT_RAID_DRIVER	
    SATA_DEVICE_DATA *SataDevice = (SATA_DEVICE_DATA*)gFastBootPolicy->SataDevice;   
    UINT8	i;
#endif
    UINT16  BDF;
    
    if (gFastBootPolicy->UEfiBoot == TRUE)  return FALSE;

    TempDp = FindDevicePath(Dp,HARDWARE_DEVICE_PATH,HW_VENDOR_DP);
    if(TempDp == NULL) return FALSE;
    
    TempDp = FindDevicePath(Dp,HARDWARE_DEVICE_PATH,HW_PCI_DP);
    if(TempDp == NULL) return FALSE;
   
    PciDp = (PCI_DEVICE_PATH*)TempDp;
    BDF = (UINT16)((0 << 8) | (PciDp->Device << 3) | PciDp->Function );
#if SUPPORT_RAID_DRIVER
    for (i=0;i<MAX_SATA_DEVICE_COUNT && SataDevice[i].BDF!=0;i++) {
        if (BDF == SataDevice[i].BDF)
            return TRUE;
    }
#endif
    return FALSE;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConnectDevicePath_Recursive
//
// Description: Connect controller by device path recursively.
//
// Input:       
//	IN EFI_DEVICE_PATH_PROTOCOL *pPath - Device path want to be connected.
//
// Output:    
//  None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ConnectDevicePath_Recursive (
    IN EFI_DEVICE_PATH_PROTOCOL *pPath)
{
    EFI_HANDLE Handle;
    EFI_STATUS Status;
	EFI_DEVICE_PATH_PROTOCOL    *DevicePath;

    while (TRUE)
    {
        EFI_DEVICE_PATH_PROTOCOL *pLastPath = NULL;
        EFI_DEVICE_PATH_PROTOCOL *pFirstNode = pPath;

        if (isEndNode(pPath))
        {
            if (pPath->SubType == END_ENTIRE_SUBTYPE) break;
            pPath++;
            continue;
        }

        while (TRUE) {
            EFI_DEVICE_PATH_PROTOCOL *Dp;
            UINT8 SubType;

            pPath = pFirstNode;

            // LocateDevicePath can not work with multi-instance device paths.
            // Prepare single instance device path and call LocateDevicePath.

            Dp = DPGetEndNode(pPath);
            SubType = Dp->SubType;
            Dp->SubType = END_ENTIRE_SUBTYPE;
            Status = pBS->LocateDevicePath(&gEfiDevicePathProtocolGuid, \
                                                            &pPath, &Handle);
            Dp->SubType = SubType;
            if (EFI_ERROR(Status)) break;

            if (isEndNode(pPath))
            {
                // Last time let's do it recursively.

                pBS->ConnectController(Handle, NULL, NULL, TRUE);  
                break;
            }
            if (pPath == pLastPath) break;
            pLastPath = pPath;

			if (StopBlkIo == TRUE) {
				gHandle = Handle;
    			Status = pBS->OpenProtocol( Handle,
                    		&gEfiDevicePathProtocolGuid,
                    		(VOID **)&DevicePath,
                    		ThisImageHandle,     
                    		Handle,   
                    		EFI_OPEN_PROTOCOL_BY_DRIVER);
			} else {
            	Status = pBS->CloseProtocol ( Handle,
                                &gEfiDevicePathProtocolGuid,
                                ThisImageHandle,
                                Handle);
			}

            if (EFI_ERROR(pBS->ConnectController(Handle, NULL, pPath, TRUE)))
                break;
        }

        while (!isEndNode(pPath))
            pPath = NEXT_NODE(pPath);
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConnectAllAmdRaidController
//
// Description: Connect All Amd Raid Controller
//
// Input:       
//	None
//
// Output:    
//  None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ConnectAllAmdRaidController(){
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;

    TRACE((-1,"FB: ConnectAllAmdRaidController\n"));

    
	//Get a list of all USB Controllers
	Status = FbGetPciHandlesByClass(
        PCI_CL_MASS_STOR, PCI_CL_MASS_STOR_SCL_RAID, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return;
	for(i=0; i<Number; i++)
	{
        EFI_PCI_IO_PROTOCOL *PciIo;
        UINT16 VID;
        Status=pBS->HandleProtocol(Handle[i],&gEfiPciIoProtocolGuid2,&PciIo);
        if (EFI_ERROR(Status)) continue;
        Status=PciIo->Pci.Read(PciIo, EfiPciIoWidthUint16, 0x00, 1, &VID);
        if(VID == 0x1022) {
            TRACE((-1,"FB: Connect AMD Raid Controller\n"));
            pBS->ConnectController(Handle[i],NULL,NULL,TRUE);
        }       

	}
	pBS->FreePool(Handle);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConnectLastHddDevice
//
// Description: Connect previous boot Hdd
//
// Input:       
//	None
//
// Output:    
//  None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ConnectLastHddDevice()
{
    EFI_DEVICE_PATH_PROTOCOL *Dp = gFastBootPolicy->FastBootOption;
    EFI_DEVICE_PATH_PROTOCOL *TempDp = Dp;
    EFI_GUID    PciIoProtocolGuid = EFI_PCI_IO_PROTOCOL_GUID;
    EFI_PCI_IO_PROTOCOL *PciIo; 
    EFI_STATUS  Status;
    EFI_HANDLE  PciHandle;
    UINT16  RaidDevCnt=0; 
#if SUPPORT_RAID_DRIVER	
    SATA_DEVICE_PATH    *SataDp;
    UINT16  RaidPortNumber;
    UINT16  i,j;
#endif	
    UINT16  ClassCode;
    UINT16  VID;

    if (IsLegacyRaidDevicePath(Dp))
    {
        // there is no port information in Legacy Raid device, so decide to 
        // connect all HDDs.        
        TRACE((-1, "FB: ConnectLastHddDevice - Find Legacy raid!\n"));
        TRACE((-1, "FB: Attempt to connect all Sata Device\n"));        
		ConnectAllSataDevices();
        return EFI_SUCCESS;
    }

    TRACE((-1, "FB: ConnectLastHddDevice\n"));

    TempDp = Dp;
	
    Status = pBS->LocateDevicePath(&PciIoProtocolGuid, &TempDp, &PciHandle);
    if (EFI_ERROR(Status)) return Status;
   
    Status = pBS->HandleProtocol(PciHandle,&PciIoProtocolGuid,&PciIo);
    if (EFI_ERROR(Status)) return Status;

    Status = PciIo->Pci.Read (PciIo,\
        EfiPciIoWidthUint16,\
        0x0A,\
        1,\
        &ClassCode);            
    ASSERT_EFI_ERROR(Status);

    Status = PciIo->Pci.Read (PciIo,\
        EfiPciIoWidthUint16,\
        0x00,\
        1,\
        &VID);            
    ASSERT_EFI_ERROR(Status);
	
    if (ClassCode != 0x0104 && ClassCode != 0x0106 && ClassCode != 0x0101)
        return EFI_SUCCESS; //is not sata device, do Not try to connect it.

#if SUPPORT_RAID_DRIVER
    if(VID == 0x8086 && ClassCode == 0x0104) 
    {   //Intel Raid
        TempDp = Dp;
        TempDp = FindDevicePath(TempDp,MESSAGING_DEVICE_PATH,MSG_SATA_DP);
        SataDp = (SATA_DEVICE_PATH*)TempDp;
		StopBlkIo = TRUE;
        //check how many raid dev by checking bitmap
        for (i=0;i<16;i++) {
            if(SataDp->PortNumber & 1<<i) RaidDevCnt++;
        }
        RaidPortNumber = SataDp->PortNumber;        

        Status = pBS->AllocatePool(EfiBootServicesData,DPLength(Dp),&TempDp);
        ASSERT_EFI_ERROR(Status);

        MemCpy(TempDp,Dp,DPLength(Dp));

        //connect each port
        SataDp = (SATA_DEVICE_PATH*)FindDevicePath(TempDp,MESSAGING_DEVICE_PATH,MSG_SATA_DP);
        for(j=0;j<16 && RaidDevCnt>0;j++) {
            if(RaidPortNumber & 1<<j) 
            {
                SataDp->PortNumber = j;
                SataDp->MultiplierPortNumber = 0xFF;
                RaidDevCnt--;               
				if (RaidDevCnt == 0) {
					StopBlkIo = FALSE;
				}
                ConnectDevicePath_Recursive(TempDp);
            }                
        }

        pBS->FreePool(TempDp);

        
    } else {
        ConnectDevicePath_Recursive(Dp);        
    }
#else
	if(ClassCode == 0x0104)	// RAID Mode
		ConnectAllSataDevices();
	else
		ConnectDevicePath_Recursive(Dp);
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConnectHddDevices
//
// Description: Connect all previous boot Hdds.
//
// Input:       
//	None
//
// Output:    
//  None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if SUPPORT_RAID_DRIVER
EFI_STATUS ConnectHddDevices()
{    
    UINT8 SataPort_DevPath[]= {
    // ACPI Device Path
    0x02,0x01,0x0c,0x00,0xd0,0x41,0x03,0x0a,0x00,0x00,0x00,0x00,
    //PCI Device Path
    0x01,0x01,0x06,0x00,0x02,0x1f,
    //SATA Device Path
    0x03,0x12,0x0a,0x00,0x00,0x00,0xff,0xff,0x00,0x00,
    //Terminal
    0x7f,0xff,0x04,0x00
    };
	
    UINT8 IdePort_DevPath[]= {
    // ACPI Device Path
    0x02,0x01,0x0c,0x00,0xd0,0x41,0x03,0x0a,0x00,0x00,0x00,0x00,
    //PCI Device Path
    0x01,0x01,0x06,0x00,0x02,0x1f,
    //SATA Device Path
    0x03,0x01,0x08,0x00,0x00,0x00,0x00,0x00,
    //Terminal
    0x7f,0xff,0x04,0x00
    };

    EFI_STATUS  Status;   
    UINT8 i;
    EFI_DEVICE_PATH_PROTOCOL *TempDp;
    UINT8   Device,Function;
    SATA_DEVICE_DATA *SataDevice = (SATA_DEVICE_DATA*)gFastBootPolicy->SataDevice;
	EFI_DEVICE_PATH_PROTOCOL *Dp = gFastBootPolicy->FastBootOption;

    if (IsLegacyRaidDevicePath(Dp) && SataDevice[0].ClassCode == 0x0104)
    {
        TRACE((-1, "FB: Attempt to connect all Sata Device\n"));        
		ConnectAllSataDevices();
        return EFI_SUCCESS;
    }
    TRACE((-1, "FB: ConnectHddDevices\n"));
    
    for(i=0;i<MAX_SATA_DEVICE_COUNT && SataDevice[i].BDF!=0;i++)
    {
        if (SataDevice[i].DevType == ATAPI || SataDevice[i].DevType == PMPORT)
            continue;
        
        if(SataDevice[i].ClassCode == 0x0106 || SataDevice[i].ClassCode == 0x0104) 
        { // AHCI or RAID
			if(SataDevice[i].ClassCode == 0x0104) {

				StopBlkIo = TRUE;
			}
            Function = SataDevice[i].BDF & 0x03;
            Device = (SataDevice[i].BDF >> 3) & 0x1F;            
            TempDp = FindDevicePath((EFI_DEVICE_PATH_PROTOCOL*)SataPort_DevPath,HARDWARE_DEVICE_PATH,HW_PCI_DP);
            if (TempDp == NULL) { 
				StopBlkIo = FALSE;
				continue;                 
			}
            ((PCI_DEVICE_PATH*)TempDp)->Device = Device;
            ((PCI_DEVICE_PATH*)TempDp)->Function = Function;            
	
            TempDp = FindDevicePath((EFI_DEVICE_PATH_PROTOCOL*)SataPort_DevPath,MESSAGING_DEVICE_PATH,MSG_SATA_DP);
            ((SATA_DEVICE_PATH*)TempDp)->PortNumber = (UINT16)SataDevice[i].PortNum;

            ConnectDevicePath_Recursive((EFI_DEVICE_PATH_PROTOCOL*)SataPort_DevPath);
			if (SataDevice[i + 1].BDF == 0) {
				StopBlkIo = FALSE;
            	pBS->CloseProtocol ( gHandle,
                                &gEfiDevicePathProtocolGuid,
                                ThisImageHandle,
                                gHandle);
				pBS->ConnectController(gHandle, NULL, NULL, TRUE); 
			}
            Status = CheckConnectedHdd(SataDevice[i].BDF,SataDevice[i].ClassCode,SataDevice[i].PortNum);
            if(EFI_ERROR(Status)) {
				if (StopBlkIo == TRUE) {
					StopBlkIo = FALSE;
            		pBS->CloseProtocol ( gHandle,
                                &gEfiDevicePathProtocolGuid,
                                ThisImageHandle,
                                gHandle);
				}
				return Status;            
			}             
        }
        else if (SataDevice[i].ClassCode == 0x0101)
        { //IDE

            Function = SataDevice[i].BDF & 0x03;
            Device = (SataDevice[i].BDF >> 3) & 0x1F;            
            TempDp = FindDevicePath((EFI_DEVICE_PATH_PROTOCOL*)IdePort_DevPath,HARDWARE_DEVICE_PATH,HW_PCI_DP);
                if (TempDp == NULL) continue;                 
            ((PCI_DEVICE_PATH*)TempDp)->Device = Device;
            ((PCI_DEVICE_PATH*)TempDp)->Function = Function;   
            
            TempDp = FindDevicePath((EFI_DEVICE_PATH_PROTOCOL*)IdePort_DevPath,MESSAGING_DEVICE_PATH,MSG_ATAPI_DP);
            ((ATAPI_DEVICE_PATH*)TempDp)->PrimarySecondary = SataDevice[i].PortNum & BIT0;
            ((ATAPI_DEVICE_PATH*)TempDp)->SlaveMaster = SataDevice[i].PortNum & BIT1;

            ConnectDevicePath_Recursive((EFI_DEVICE_PATH_PROTOCOL*)IdePort_DevPath);

            Status = CheckConnectedHdd(SataDevice[i].BDF,SataDevice[i].ClassCode,SataDevice[i].PortNum);
            if(EFI_ERROR(Status)) return Status;
        }
    }

    // Up to here, all recorded sata devcies are connected.
    //
    // But AHCIBUS would NOT be run in AMD Raid mode, so we don't know whether all Hdd is connect on Raid controller or not.
    // Find out all AMD Raid controller and connect it.

    ConnectAllAmdRaidController();

    return EFI_SUCCESS;
}
#endif

                                        //(EIP62845+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConnectAllSataDevices
//
// Description: Connect All Stat Devcies
//
// Input:		None
//
// Output:      EFI_STATUS 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>										
EFI_STATUS ConnectAllSataDevices()			//(EIP85135)
{
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;
//	    if (gFastBootPolicy->ConnectAllSata == FALSE) return;    //(EIP96276.3)+

    TRACE((-1, "FB: ConnectAllSataDevices\n"));

	//Connect all SATA IDE Controllers
	Status = FbGetPciHandlesByClass(
        PCI_CL_MASS_STOR, PCI_CL_MASS_STOR_SCL_IDE, &Number, &Handle
    );

    if(!EFI_ERROR(Status)){
        for(i=0; i<Number; i++){
            pBS->ConnectController(Handle[i],NULL,NULL,TRUE);
        }        
        pBS->FreePool(Handle);
    }
    
	//Connect all SATA AHCI Controllers
	Status = FbGetPciHandlesByClass(
        PCI_CL_MASS_STOR, 0x06, &Number, &Handle
    );

    if(!EFI_ERROR(Status)){
        for(i=0; i<Number; i++){
            pBS->ConnectController(Handle[i],NULL,NULL,TRUE);
        }        
        pBS->FreePool(Handle);
    }

										//(EIP95568+)>
	//Connect all SATA RAID Controllers
	Status = FbGetPciHandlesByClass(
        PCI_CL_MASS_STOR, PCI_CL_MASS_STOR_SCL_RAID, &Number, &Handle
    );

    if(!EFI_ERROR(Status)){
        for(i=0; i<Number; i++){
            pBS->ConnectController(Handle[i],NULL,NULL,TRUE);
        }        
        pBS->FreePool(Handle);
    }
										//<(EIP95568+)
    return EFI_SUCCESS;	    			//(EIP85135)

}
                                        
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetSataPortPresentHOB
//
// Description: Get Sata port present HOB
//
// Input:       
//	IN OUT SATA_PRESENT_HOB **SataPresentHob    
//
// Output:    
//  None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>                        
#if SUPPORT_RAID_DRIVER
EFI_STATUS GetSataPortPresentHOB (
    IN SATA_PRESENT_HOB **SataPresentHob    
    )
{
    EFI_STATUS  Status;
    VOID        *pHobList = NULL;
    EFI_GUID    guidHob = HOB_LIST_GUID;    
    EFI_GUID    SataPresentHobGuid = AMI_SATA_PRESENT_HOB_GUID;
//	    SATA_PRESENT_HOB *pSataPresentHob;

    
    pHobList = GetEfiConfigurationTable(pST, &guidHob);
    if (!pHobList) return EFI_NOT_READY;

    *SataPresentHob = (SATA_PRESENT_HOB*)pHobList;

    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, SataPresentHob)))
    {
        if (guidcmp(&(*SataPresentHob)->EfiHobGuidType.Name, &SataPresentHobGuid) == 0)
            break;
    }


    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    return  EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CollectSataDeviceInfo
//
// Description: Collect the Sata device information created by Ahci and Ide 
//              bus driver
//
// Input:       
//  IN FAST_BOOT *Var - FastBoot variable
//
// Output:    
//  None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>  
#if SUPPORT_RAID_DRIVER	
VOID CollectSataDeviceInfo(
  IN FAST_BOOT *Var
)
{
    EFI_GUID    DiskInfoGuid = EFI_DISK_INFO_PROTOCOL_GUID;
    EFI_GUID    DiskInfoIdeGuid = EFI_DISK_INFO_IDE_INTERFACE_GUID;
    EFI_GUID    DiskInfoAhciGuid = EFI_DISK_INFO_AHCI_INTERFACE_GUID;
    EFI_DISK_INFO_PROTOCOL  *DiskInfoProtocol;
    UINTN Count,i,j;
    EFI_HANDLE *Handle;
    EFI_STATUS  Status;
    static BOOLEAN Executed = FALSE;
    UINTN Seg, Bus, Dev, Fun;    
    UINT8   SataDevCount = 0;
    SATA_PRESENT_HOB *pSataPresentHob = NULL;

    if (Executed == TRUE) return;
//
// Collect the port present information reported by chipset
//

    Status = GetSataPortPresentHOB(&pSataPresentHob);
    if (EFI_ERROR(Status)) {
        TRACE((-1,"FB: Sata port present HOB is not found, need CSP porting for it\n"));
        return;
    }

    MemCpy(&Var->ControllerCount,&pSataPresentHob->ControllerCount,sizeof(SATA_PRESENT_HOB)-sizeof(EFI_HOB_GUID_TYPE));
    
//
// Collect the Sata device information created by Ahci and Ide bus driver
//
    Status=pBS->LocateHandleBuffer(ByProtocol,&DiskInfoGuid,NULL,&Count,&Handle);
    if (EFI_ERROR(Status)) return;

    for(i=0;i<Count;i++)
    {
        Status=pBS->HandleProtocol(Handle[i],&DiskInfoGuid,(VOID**)&DiskInfoProtocol);
        if(EFI_ERROR(Status)) continue;

        if(!guidcmp(&DiskInfoProtocol->Interface,&DiskInfoIdeGuid)) {
        //            
        //Devie is detected in Ide mode
        //
            IDE_BUS_PROTOCOL    *IdeInterface = ((IDE_DISK_INFO*)DiskInfoProtocol)->IdeBusInterface;
            EFI_PCI_IO_PROTOCOL *PciIo = IdeInterface->PciIO;
            
            Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Fun);
            ASSERT_EFI_ERROR(Status);

            Var->SataDevice[SataDevCount].BDF = (UINT16)((Bus << 8) | (Dev << 3) | Fun );
            
            Status = PciIo->Pci.Read (PciIo,\
                EfiPciIoWidthUint16,\
                0x0A,\
                1,\
                &Var->SataDevice[SataDevCount].ClassCode);            
            ASSERT_EFI_ERROR(Status);


            Var->SataDevice[SataDevCount].DevType = IdeInterface->IdeDevice.DeviceType;
            Var->SataDevice[SataDevCount].PortNum = IdeInterface->IdeDevice.Channel | IdeInterface->IdeDevice.Device<<1;
                
            MemCpy( &Var->SataDevice[SataDevCount].SerialNum,
                    &IdeInterface->IdeDevice.IdentifyData.Serial_Number_10,20);
            
            SataDevCount++;
        
            ASSERT(SataDevCount<MAX_SATA_DEVICE_COUNT);
        
        }else if (!guidcmp(&DiskInfoProtocol->Interface,&DiskInfoAhciGuid)) {
        //
        //Devie is detected in Ahci mode
        //  
            SATA_DEVICE_INTERFACE *SataInterface = ((SATA_DISK_INFO*)DiskInfoProtocol)->SataDevInterface;
            EFI_PCI_IO_PROTOCOL *PciIo = SataInterface->AhciBusInterface->PciIO;
                    
            Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Fun);
            ASSERT_EFI_ERROR(Status);
  
            Var->SataDevice[SataDevCount].BDF = (UINT16)((Bus << 8) | (Dev << 3) | Fun );
            
            Status = PciIo->Pci.Read (PciIo,\
                EfiPciIoWidthUint16,\
                0x0A,\
                1,\
                &Var->SataDevice[SataDevCount].ClassCode);            
            ASSERT_EFI_ERROR(Status);

            Var->SataDevice[SataDevCount].DevType = SataInterface->DeviceType;
            Var->SataDevice[SataDevCount].PortNum = SataInterface->PortNumber;
            
            MemCpy( &Var->SataDevice[SataDevCount].SerialNum,
                    &SataInterface->IdentifyData.Serial_Number_10,20);

            SataDevCount++;
            
            ASSERT(SataDevCount<MAX_SATA_DEVICE_COUNT);
            
        } else {
            continue;
        }
    
    }

//
//  Print out message for Sata Port&Device information.
//

    for(i=0;i<MAX_SATA_DEVICE_COUNT && Var->SataDevice[i].BDF!=0;i++)
    {
        TRACE((-1,"FB: SataDevice[%d] -- BDF:%x, CalssCode:%x, DveType:%x, PortNum:%x\n",\
            i,Var->SataDevice[i].BDF,Var->SataDevice[i].ClassCode,\
            Var->SataDevice[i].DevType,Var->SataDevice[i].PortNum));            
        
        TRACE((-1,"Serial Number: "));
        
        for(j=0;j<20;j++)
        {
            TRACE((-1,"%02x ",Var->SataDevice[i].SerialNum[j]));
        }
        TRACE((-1," \n"));
    }

    pBS->FreePool(Handle);

    return;       
}
#endif
                                        //<(EIP62845+)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootReadyToBootNotify
//
// Description: FastBoot ReadyToBoot callback
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FastBootReadyToBootNotify(
	IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS               Status;
    UINTN                    i,Size;
    FAST_BOOT                Var;
    UINT16                   *BootOrder = NULL;
    CHAR16                   BootOptionName[9];
	EFI_LOAD_OPTION          *BootOption = NULL;
    UINTN                    BootOptionSize;	//(EIP96276.4+)
    CHAR16                   *Description;
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    UINT32                   BbsPopup;
    BOOLEAN     VaildBootOption = FALSE;
#if FASTBOOT_NEED_RESTART	
	UINTN    ReBootFlag;
	UINTN    ReBootFlagSize = sizeof(ReBootFlag);
	UINTN    ReBootCount;
	UINTN    ReBootCountSize = sizeof(ReBootCount);
	UINTN    ResetFlag = 1;
	UINTN    ClearCount = 0;
#endif

//check if we are on bbs-popup boot path
    Size = sizeof(BbsPopup);
    Status = pRS->GetVariable(L"BbsPopupCalled", &FastBootVariableGuid, NULL, &Size, (VOID *)&BbsPopup);
    if(!EFI_ERROR(Status) && (BbsPopup == 0x55aa55aa))  {   //we are on bbs-popup boot path
        ResetFastBootVariable();    //clear variable if it was created on previous boots
        return;
    }

    Size = sizeof(Var);
    pBS->SetMem(&Var,Size,0);

    Status = pRS->GetVariable(L"LastBoot", &FastBootVariableGuid, NULL, &Size, (VOID *)&Var);
    if(EFI_ERROR(Status)) {       

#if FASTBOOT_NEED_RESTART	
		Status = pRS->GetVariable(FAST_BOOT_RESTART,
							&FastbootRestartGuid,
							NULL,
							&ReBootFlagSize,
							(VOID *)&ReBootFlag
							);
	
		Status = pRS->GetVariable(FAST_BOOT_RESTART_COUNT,
							&FastbootRestartCountGuid,
							NULL,
							&ReBootCountSize,
							(VOID *)&ReBootCount
							);
		if(!EFI_ERROR(Status))
		{
			TRACE((-1,"FB: ReBootFlag:%d\n",ReBootFlag));
			TRACE((-1,"FB: ReBootCount:%d\n",ReBootCount));

			if(ReBootFlag == 1 && ReBootCount <1 )
				FastBootEnableRestart(ReBootFlag,ReBootCount+1);
		}
		else
			FastBootEnableRestart(ResetFlag,ClearCount+1);
#endif				       

        //variable not found - create a new one
        
//
// Collect Boot Option information for next boot
//
        Status = GetEfiVariable(L"BootOrder", &EfiVariableGuid, NULL, &Size, &BootOrder);
        if(EFI_ERROR(Status)) return;        

        for (i=0;i<Size/sizeof(UINT16);i++,BootOption=NULL) {	//(EIP96276.4)

            Swprintf(BootOptionName, gBootName, BootOrder[i]);
           
            Status = GetEfiVariable(BootOptionName, &EfiVariableGuid, NULL, &BootOptionSize, &BootOption);	//(EIP96276.4)
            if(EFI_ERROR(Status)) return;


            VaildBootOption = IsValidFBBootOptionPtr(i,BootOption);
            if (VaildBootOption) break;
            
            pBS->FreePool(BootOption);
            
            if (VaildBootOption == FALSE && i == (Size/sizeof(UINT16) -1 )) {
                TRACE((-1, "FB: There is no valid boot option\n"));
                pBS->FreePool(BootOrder);
                return;

            }

        }

        Var.BootOptionNumber = BootOrder[i];
        Var.BootCount = 0;

        //retrieve device path
        Description = (CHAR16 *)(BootOption + 1);
	    Dp = (EFI_DEVICE_PATH_PROTOCOL *)((UINT8*)Description + (Wcslen(Description) + 1) * sizeof(CHAR16));

        if(Dp->Type == BBS_DEVICE_PATH) {
            Var.BootType =  FAST_BOOT_TYPE_LEGACY;
            Status = CreateLegacyFastBootOption(&Var);
            TRACE((-1,"FB: Create FastBoot Legacy Boot Option %r\n",Status));                                
        } else {
            Var.BootType = FAST_BOOT_TYPE_EFI;  
            Status = CreateEfiFastBootOption(BootOption, BootOptionSize, BootOrder[i]);	//(EIP96276.4)
            TRACE((-1,"FB: Create FastBoot EFI Boot Option %r\n",Status));                        
        }

        pBS->FreePool(BootOrder);
        pBS->FreePool(BootOption);

        if(EFI_ERROR(Status)) return;

//
// Collect SATA Port&Device information
//
#if SUPPORT_RAID_DRIVER
        CollectSataDeviceInfo(&Var);
#endif
        
    } else {
        Var.BootCount++;
        Var.BootOptionNumber = gFastBootPolicy->BootOptionNumber;
    }
   
    TRACE((-1,"FB: Create LastBoot Variable\n"));  
    pRS->SetVariable(L"LastBoot",
                     &FastBootVariableGuid,
                     EFI_VARIABLE_NON_VOLATILE | 
                     EFI_VARIABLE_BOOTSERVICE_ACCESS | 
                     EFI_VARIABLE_RUNTIME_ACCESS,
                     sizeof(Var),
                     (VOID *)&Var);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConnectFastLegacyBoot
//
// Description: Connect Legacy FastBoot Device
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ConnectFastLegacyBootDevice()
{
#if CSM_SUPPORT 
    EFI_STATUS Status;
    UINTN Size = 0;
    UINT8 *BootOption = NULL;
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    BOOLEAN UsbMassStorage = FALSE;
    BOOLEAN HddFilePath = FALSE;
    EFI_BLOCK_IO_PROTOCOL *BlockIo;
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;
    UINT16 HddCount;
    UINT16 BbsCount;
    HDD_INFO *HddInfo;
    BBS_TABLE *BbsTable;
    EFI_HANDLE  Handle;
    UINT8 i;  							//(EIP63924+)
    TRACE((-1, "FB: Connect Fast LegacyBoot Device\n"));     
     
    Dp = gFastBootPolicy->FastBootOption;
    if(!IsSupportedDevice(Dp, &UsbMassStorage, &HddFilePath))         //CD-ROM legacy boot not supported
        return EFI_NOT_FOUND;

    if ( UsbMassStorage && gFastBootPolicy->UsbSupport == 0)
        return EFI_NOT_FOUND;  //If skip usb enable, don't boot into usb mass storage     
        
    if(!IsSataDevicePath(Dp) && !IsLegacyRaidDevicePath(Dp))
    {
        TRACE((-1, "FB: Dp connecting\n"));
        ConnectDevicePath(Dp);
    }
            
    Status = pBS->LocateDevicePath(&gEfiBlockIoProtocolGuid, &Dp, &Handle);
    if(EFI_ERROR(Status))
        return Status;
    TRACE((-1, "FB: Dp connected Handle %x\n",Handle));
        
    LegacyBootDeviceHandle = Handle;
        
    Status = pBS->HandleProtocol(Handle, &gEfiBlockIoProtocolGuid, &BlockIo);
    if(EFI_ERROR(Status))
        return Status;
    TRACE((-1, "FB: BlockIo found\n"));

    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
    if (EFI_ERROR(Status)) 
        return Status;
    TRACE((-1, "FB: Legacybios discovered\n"));

										//(EIP63924)>
    // check FastBootModeChange
    for (i=0;FastBootModeChange[i]; i++) 
        if(FastBootModeChange[i]())return EFI_NOT_FOUND;
										//<(EIP63924)
        
    Status = LegacyBios->GetBbsInfo(LegacyBios, &HddCount, &HddInfo, &BbsCount, &BbsTable);  //install int 13
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

#endif 
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastLegacyBoot
//
// Description: Legacy FastBoot path
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FastLegacyBoot(VOID)
{
#if CSM_SUPPORT 
    UINTN Size = 0;
    EFI_STATUS Status;
    UINT8 *BootOption = NULL;
    UINT8 Index;	
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;
    UINT16 HddCount;
    UINT16 BbsCount;
    HDD_INFO *HddInfo;
    BBS_TABLE *BbsTable;
    EFI_EVENT  FastBootLegacyBootEvent;
    UINT8   *pDeviceString;
    UINT8   i;
    UINT16   StringCheckSum;

    TRACE((-1, "FB: Fast legacy boot started\n"));

										//(EIP87390+)>
	pBS->RaiseTPL( TPL_HIGH_LEVEL );	// guarantees that RestoreTPL won't ASSERT
	pBS->RestoreTPL( TPL_APPLICATION );
										//<(EIP87390+)
	Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
	if (EFI_ERROR(Status)) 
        return Status;
    TRACE((-1, "FB: Legacybios discovered\n"));
        
    LegacyBios->GetBbsInfo(LegacyBios, &HddCount, &HddInfo, &BbsCount, &BbsTable);  //install int 13

										//(EIP87390+)>
    //Set USB device BootPriority as BBS_DO_NOT_BOOT_FROM, Install USB INT13 service for TCG Bitlocker Driver
    for (Index=0;Index<BbsCount;Index++){       

                                        //(EIP103422+)>
        // if BBS table priority have been arranged already 
        // increase one priority to all prioritized BBS table entry
        if (BbsTable[Index].BootPriority < BBS_DO_NOT_BOOT_FROM) { 
            BbsTable[Index].BootPriority = BbsTable[Index].BootPriority + 1;
            continue;
        }
                                        //<(EIP103422+)         

        // If BBS table priority have not been arranged yet, set device 
        // priority as BBS_DO_NOT_BOOT_FROM.
        // It means don't boot from this devcie but BIOS still need to install
        // INT13 service for it.

        if (BbsTable[Index].BootPriority != BBS_IGNORE_ENTRY)
            BbsTable[Index].BootPriority = BBS_DO_NOT_BOOT_FROM;                    
            
    }
										//<(EIP87390+)

    for (Index=0;Index<BbsCount;Index++){
    
        if (BbsTable[Index].IBV1 == (UINT32)LegacyBootDeviceHandle) break;
    
        if (Index == (BbsCount-1)) return Status; //can't find fast device in bbstable 
    }
    
    if(gFastBootPolicy->CheckDevStrCheckSum) {
        
        pDeviceString = (UINT8*)((UINTN)((UINTN)BbsTable[Index].DescStringSegment<<4) + BbsTable[Index].DescStringOffset);
        StringCheckSum =0;    
        for (i=0;i<50;i++) {        
            if (pDeviceString[i] == 0) break;
            StringCheckSum+=pDeviceString[i];
        }        
         
        if (StringCheckSum != gFastBootPolicy->DevStrCheckSum) return EFI_DEVICE_ERROR;
  
    }

    BbsTable[Index].BootPriority = 0;

    Status = CreateLegacyBootEvent(TPL_CALLBACK,
                                    FastBootClearBootFailFlag,
                                    NULL,
                                    &FastBootLegacyBootEvent);
	if (EFI_ERROR(Status)) 
        return Status; 

    TRACE((-1,"FB: LEGACY BOOT Singal Ready to Boot\n"));

    ReadyToBoot(0xffff);

                                        //(EIP68329)>
    if((SKIP_TSE_HANDSHAKE == 0) && (TSE_MAJOR >= 0x02) && (TSE_MINOR >= 0x10)) {            
    } else {
        gFastBootTseProtocol->FastBootPasswordFreezeDevices();
    }
                                        //<(EIP68329)

//Set Runtime as TRUE before pass control to OS.
    Runtime = TRUE;

    LegacyBios->LegacyBoot(LegacyBios, 0, 0, 0);
    
    return Status;
#else
    return EFI_SUCCESS;
#endif    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckLoaderEx
//
// Description: This function use file system protocol to 
//				checks if OS loader present on given device
//
// Input:
//	IN EFI_HANDLE  Handle - Block io handle, used to get file system protocol
//  IN EFI_DEVICE_PATH_PROTOCOL *Dp - pointer to device path of bootable device
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckLoaderEx( 
		IN EFI_HANDLE  Handle,
		IN EFI_DEVICE_PATH_PROTOCOL *Dp)
{
	EFI_STATUS  Status;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem = NULL;
	EFI_FILE_PROTOCOL *FileProtocol = NULL;
	EFI_FILE_PROTOCOL* NewFileProtocol = NULL;
	FILEPATH_DEVICE_PATH   *BootOptionFilePath=NULL;

	for( ; !(isEndNode(Dp)); Dp = NEXT_NODE(Dp)) {
    	if(Dp->Type == MEDIA_DEVICE_PATH && Dp->SubType == MEDIA_FILEPATH_DP) { 
			BootOptionFilePath = (FILEPATH_DEVICE_PATH*) (Dp);
			break;
		}
	}
	if (BootOptionFilePath == NULL) {
		return EFI_DEVICE_ERROR;
	}

	Status = pBS->HandleProtocol (
            Handle,
            &gEfiSimpleFileSystemProtocolGuid,
            &SimpleFileSystem
        );
    if(EFI_ERROR(Status)) {          
        return Status;
    }

    Status = SimpleFileSystem->OpenVolume (
            SimpleFileSystem,
            &FileProtocol
        );
    if(EFI_ERROR(Status)) {          
        return Status;
    }

	Status = FileProtocol->Open (
                FileProtocol,
                &NewFileProtocol,
				BootOptionFilePath->PathName,
                EFI_FILE_MODE_READ,
                NULL
            );
    if(EFI_ERROR(Status)) {          
        return Status;
    }

	NewFileProtocol->Close(NewFileProtocol);
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConnectFastEfiBootDevice
//
// Description: Connect UEFI FastBoot Device
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConnectFastEfiBootDevice()
{
    EFI_STATUS  Status;
    EFI_DEVICE_PATH_PROTOCOL *Dp = gFastBootPolicy->FastBootOption;
    UINT8 *BootOption = NULL;
    UINTN Size = 0;
    EFI_HANDLE  Handle;    
    UINT8   i;                          //(EIP63924+)
    TRACE((-1, "FB: Connect Fast EFIBoot Device\n"));
    
    if(IsBootToShell(Dp))
        InstallFwLoadFile();
    else {
        if(!IsSataDevicePath(Dp))
        {  
            TRACE((-1, "FB: Dp connecting\n"));
            ConnectDevicePath(Dp);	
        }   

        Status = pBS->LocateDevicePath(&gEfiBlockIoProtocolGuid, &Dp, &Handle);
        if(EFI_ERROR(Status)) return Status;
        TRACE((-1, "FB: Dp connected Handle %x\n",Handle));
        Status = CheckLoaderEx(Handle, gFastBootPolicy->FastBootOption);		
        if(EFI_ERROR(Status)) {
            TRACE((-1, "FB: Check loader %r\n",Status));            
            return Status;
        }

    }
   										//(EIP63924)>
    for (i=0;FastBootModeChange[i]; i++) 
        if(FastBootModeChange[i]())return EFI_NOT_FOUND;
										//<(EIP63924)

    return EFI_SUCCESS;
}

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
VOID _ShellClearScreen (EFI_EVENT Event, VOID *Context)
{
    pST->ConOut->ClearScreen (pST->ConOut);
	pBS->CloseEvent (Event);
	pST->ConOut->EnableCursor (pST->ConOut, TRUE);
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
    EFI_EVENT   ShellLaunchEvent;
	Status = pBS->CreateEvent (
				EFI_EVENT_NOTIFY_SIGNAL, 
				TPL_CALLBACK,
				_ShellClearScreen,
				NULL,
				&ShellLaunchEvent);
	if (!EFI_ERROR (Status))
	{
		Status = pBS->RegisterProtocolNotify(
				&EfiShellInterfaceGuid,
				ShellLaunchEvent,
				&Registration
				);
	}
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastEfiBoot
//
// Description: UEFI FastBoot path
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FastEfiBoot(VOID) 
{
    EFI_STATUS Status;
    UINT8 *BootOption = NULL;
    UINTN Size = 0;
    UINT16 OptionNumber = 0xFFFF;
    EFI_DEVICE_PATH_PROTOCOL *Dp = NULL;
    UINTN DpSize;
	UINT32 LoadOptionsSize;
	VOID *LoadOptions;
	EFI_LOADED_IMAGE_PROTOCOL *Image;

    TRACE((-1, "FB: Fast EFI boot started\n"));

    DpSize = DPLength(gFastBootPolicy->FastBootOption);
    LoadOptionsSize = *(UINT32 *)((UINT8 *)gFastBootPolicy->FastBootOption + DpSize);
    LoadOptions = (VOID *)((UINT8 *)gFastBootPolicy->FastBootOption + DpSize + sizeof(UINT32));                         

	// this *MUST* be run a EFI_TPL_APPLICATION
	pBS->RaiseTPL( TPL_HIGH_LEVEL );	// guarantees that RestoreTPL won't ASSERT (EIP87390)+
	pBS->RestoreTPL( TPL_APPLICATION );

    TRACE((-1,"FB: EFI BOOT Signal Ready to Boot\n"));

//
//  ReadyToBoot have signaled already in TSE path.
//
    if (gFastBootPolicy->SkipTSEHandshake)
        ReadyToBoot(gFastBootPolicy->BootOptionNumber);

    
    Status = pBS->LoadImage(TRUE, ThisImageHandle, gFastBootPolicy->FastBootOption, NULL, 0, &EFIBootImageHanlde);

    TRACE((-1,"FB: load image %r\n",Status));
    
    if (EFI_ERROR(Status)) return Status;        
    if(LoadOptionsSize != 0) {
        Status = pBS->HandleProtocol(EFIBootImageHanlde, &gEfiLoadedImageProtocolGuid, &Image);
        if (EFI_ERROR(Status)) 
            return Status;

        Image->LoadOptionsSize = LoadOptionsSize;   
        Image->LoadOptions = LoadOptions;
    }    
                                        //(EIP68329)>
    if((gFastBootPolicy->SkipTSEHandshake == 0) && (TSE_MAJOR >= 0x02) && (TSE_MINOR >= 0x10)) {            
    } else {
        gFastBootTseProtocol->FastBootPasswordFreezeDevices();
    }
    PERF_END(0,L"FastBoot",L"FB",0);  
    PERF_END(0,L"TSE",L"FB",0);            
                                        //<(EIP68329)
#ifdef EFI_DXE_PERFORMANCE
    SavePerformanceData(NULL, NULL);
#endif

    FastBootClearBootFailFlag(NULL, NULL);

                                        //(EIP60794+)>
    if (pST->ConOut != NULL) {
        pST->ConOut->EnableCursor(pST->ConOut,FALSE);
    }

    _RegisterShellGuid();    
                                        //<(EIP60794+)
                                        
    TRACE((-1,"FB: EFI BOOT start image\n"));

//enabld usb mass driver, so that OS have chance to connect usb mass storage.
    if (gUsbPolicyProtocol != NULL) 
        gUsbPolicyProtocol->UsbDevPlcy->UsbMassDriverSupport = TRUE;

//Set Runtime as TRUE before pass control to OS.
    Runtime = TRUE;
                                        
    IoWrite8(0x80,0xFB);    //output 80port to show system boot with fast boot path.
    Status = pBS->StartImage(EFIBootImageHanlde, NULL, NULL);
     
    return Status;     
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateLegacyFastBootOption
//
// Description: This function creates Legacy fast boot option and save it to NVRAM
//
// Input:       None
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateLegacyFastBootOption( 
    FAST_BOOT *Var
)
{
#if CSM_SUPPORT
    EFI_STATUS Status;
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;
    UINT16 HddCount;
    UINT16 BbsCount;
    HDD_INFO *HddInfo;
    BBS_TABLE *BbsTable;
    EFI_HANDLE Handle;
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    UINT8 BootOption[200];
    UINTN DpSize;
    UINT8 i;
    UINT8 Index = 0;                    //(EIP73019+)
    UINT16 Priority = 0xfffc;
    UINT8   *pDeviceString;
    UINT16   StringCheckSum=0;

    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
    if(EFI_ERROR(Status))
        return Status;

	LegacyBios->GetBbsInfo(LegacyBios, &HddCount, &HddInfo, &BbsCount, &BbsTable);

//find record with highest priority
    for(i = 0; i < BbsCount; i++) {
        if(BbsTable[i].BootPriority < Priority) {
            Priority = BbsTable[i].BootPriority;
            Index = i;
        }
    }

    if(BbsTable[Index].DeviceType != BBS_HARDDISK)
        return EFI_UNSUPPORTED;

    Handle = (EFI_HANDLE) *(UINTN*)(&(BbsTable[Index].IBV1));
    Status = pBS->HandleProtocol(Handle, &gEfiDevicePathProtocolGuid, &Dp);
    if(EFI_ERROR(Status))
        return Status;

    //save device string check sum    
    pDeviceString = (UINT8*)((UINTN)((UINTN)BbsTable[Index].DescStringSegment<<4) + BbsTable[Index].DescStringOffset);
    
    for (i=0;i<50;i++) {        
        if (pDeviceString[i] == 0) break;
        StringCheckSum+=pDeviceString[i];
    }

    Var->DevStrCheckSum = StringCheckSum;

    DpSize = DPLength(Dp);
    MemCpy(BootOption, Dp, DpSize);

    Status = pRS->SetVariable(L"FastBootOption",
                              &FastBootVariableGuid,
                              EFI_VARIABLE_NON_VOLATILE | 
                              EFI_VARIABLE_BOOTSERVICE_ACCESS | 
                              EFI_VARIABLE_RUNTIME_ACCESS,
                              DpSize,
                              BootOption);
    
    return Status;
#else
    return EFI_SUCCESS;    
#endif 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsSupportedDevice
//
// Description: This function detects if FastBoot is supported for given device
//
// Input:
//  IN EFI_DEVICE_PATH_PROTOCOL *Dp - pointer to device path of bootable device
//  OUT BOOLEAN *UsbMassStorage - TRUE if device is USB device, FALSE otherwise
//
// Output:      TRUE if FastBoot is supported for given device, FALSE otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsSupportedDevice(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp,
    OUT BOOLEAN *UsbMassStorage,
    OUT BOOLEAN *HddFilePath
    
)
{
    BOOLEAN USBDev = FALSE;

    
    for( ; !(isEndNode(Dp)); Dp = NEXT_NODE(Dp)) {
        if(Dp->Type == BBS_DEVICE_PATH)
            return FALSE;

        if(Dp->Type == MESSAGING_DEVICE_PATH) {
            if(Dp->SubType == MSG_USB_DP) 
                USBDev = TRUE;
    
            if(Dp->SubType == MSG_MAC_ADDR_DP)
                return FALSE;        

            continue;
        }

        if(Dp->Type == MEDIA_DEVICE_PATH) {
            
            if(Dp->SubType == MEDIA_HARDDRIVE_DP) {

                if(USBDev == TRUE) 
                    *UsbMassStorage = TRUE;
                
                Dp = NEXT_NODE(Dp);
                //check whether there is a file path behind hard drive path.
                if(Dp->SubType == MEDIA_FILEPATH_DP)
                    *HddFilePath = TRUE;  

                return TRUE;
            }

            if(Dp->SubType == MEDIA_CDROM_DP)
                return FALSE;              
        }
    }
    
    return TRUE;    
}
/*
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckLoader
//
// Description: This function checks if OS loader present on given device
//
// Input:
//  IN EFI_DEVICE_PATH_PROTOCOL *Dp - pointer to device path of bootable device
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckLoader(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handle;

    Status = pBS->LoadImage(FALSE, ThisImageHandle, Dp, NULL, 0, &Handle);
	if (EFI_ERROR(Status)) 
        return Status;

    Status = pBS->UnloadImage(Handle);
    return Status;
}
*/
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CreateEfiFastBootOption
//
// Description: This function creates UEFI fast boot option and save it to NVRAM
//
// Input:
//  IN EFI_LOAD_OPTION *BootOption - pointer to regular boot option to boot to
//  IN UINTN OptionSize - size of option additional parameters
//  IN UINT16 OptionNumber - number of boot option in BootOrder variable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreateEfiFastBootOption(
    IN EFI_LOAD_OPTION *BootOption,
    IN UINTN           OptionSize,
    IN UINT16          OptionNumber
)
{
    EFI_STATUS Status;
    UINTN Size;
    UINTN DpSize;
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    EFI_DEVICE_PATH_PROTOCOL *PartitionDp;
    CHAR16 *Description;
	UINT32 LoadOptionsSize;
	VOID *LoadOptions;
    UINT8 *FastBootOption;
    VOID *SavePtr;
    BOOLEAN UpdatedDp = FALSE;
    BOOLEAN UsbMassStorage = FALSE;
    BOOLEAN HddFilePath = FALSE;
    EFI_HANDLE  Handle;  

//retrieve device path
    Description = (CHAR16 *)(BootOption + 1);
	Dp = (EFI_DEVICE_PATH_PROTOCOL *)((UINT8*)Description + (Wcslen(Description) + 1) * sizeof(CHAR16));
    
    if(!IsSupportedDevice(Dp, &UsbMassStorage,&HddFilePath))
        return EFI_UNSUPPORTED;

    //only hard drive or USB can come here

    LoadOptions = (UINT8*)Dp + BootOption->FilePathListLength;
    LoadOptionsSize = (UINT32)((UINT8*)BootOption + OptionSize - (UINT8 *)LoadOptions);

    if(Dp->Type == MEDIA_DEVICE_PATH && Dp->SubType == MEDIA_HARDDRIVE_DP) {    //Windowns boot manager?
        PartitionDp = DiscoverPartition(Dp);
        if(PartitionDp == NULL)
            return EFI_UNSUPPORTED;

        Dp = DPAdd(PartitionDp, NEXT_NODE(Dp));
        UpdatedDp = TRUE;
    } else if (Dp->Type == MEDIA_DEVICE_PATH && Dp->SubType == MEDIA_VENDOR_DP) { // bulit in shell?

    } else if (HddFilePath == FALSE) { //add file path for SATA Hdd or USB Hdd without file path
        Dp = DPAddNode(Dp, &FilePathNode.Header);
        Status = pBS->LocateDevicePath(&gEfiBlockIoProtocolGuid, &Dp, &Handle);
        if(EFI_ERROR(Status)) {
            pBS->FreePool(Dp);
			return Status;
		}
		Status = CheckLoaderEx(Handle, Dp);
        if(EFI_ERROR(Status)) {
//            pBS->FreePool(Dp);
            return EFI_UNSUPPORTED;
        }
//        UpdatedDp = TRUE;

    } 

    DpSize = DPLength(Dp);

//prepare data
    Size = DpSize + sizeof(UINT32) + LoadOptionsSize;
    Status = pBS->AllocatePool(EfiBootServicesData, Size, &FastBootOption);
    SavePtr = FastBootOption;
    MemCpy(FastBootOption, Dp, DpSize);
    FastBootOption += DpSize;
    *(UINT32 *)FastBootOption = LoadOptionsSize;
    FastBootOption += sizeof(UINT32);
    MemCpy(FastBootOption, LoadOptions, LoadOptionsSize);

    Status = pRS->SetVariable(L"FastBootOption", 
                              &FastBootVariableGuid,
                              EFI_VARIABLE_NON_VOLATILE | 
                              EFI_VARIABLE_BOOTSERVICE_ACCESS | 
                              EFI_VARIABLE_RUNTIME_ACCESS,
                              Size,
                              SavePtr);

    pBS->FreePool(SavePtr);
    if(UpdatedDp)
        pBS->FreePool(Dp);
    return Status;
}

VOID ReturnToNormalBoot(VOID)
{
    UINT8   i;
    for (i=0;ReturnNormalModeHook[i]; i++)
        ReturnNormalModeHook[i]();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ResetFastBootVariable
//
// Description: This function resets FastBoot variable if FastBoot path failed
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ResetFastBootVariable(VOID)
{
    UINTN Size = sizeof(FAST_BOOT);
    FAST_BOOT Var;

    Runtime = FALSE;

//clear LastBootFailed variable if present
    FastBootClearBootFailFlag(NULL, NULL);

    if (!gFastBootPolicy->LastBootVarPresence) return;

    pRS->SetVariable(L"LastBoot", 
                     &FastBootVariableGuid,
                     EFI_VARIABLE_NON_VOLATILE,
                     0,
                     &Var);

// Disable legacy16 fastboot support
    DisableLegacy16Fastboot();  
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisconnectUsbController
//
// Description: This function resets skip table for Usb driver and disconnect 
//				all usb controllers
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DisconnectUsbController(VOID)
{

    EFI_STATUS    Status = EFI_SUCCESS;
    EFI_HANDLE *Handle;    
    UINTN Number,i;    

    if (gFastBootPolicy->UsbSupport != 2) return;
    
    //Restore Usb storage driver support
    if (gUsbPolicyProtocol != NULL) 
        gUsbPolicyProtocol->UsbDevPlcy->UsbMassDriverSupport = BackupUsbMassDriverSupport;
    
    if (FBUsbSkipTableIsSet == FALSE) return;
    
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 920)    
{
    EFI_GUID gEfiUsbProtocolGuid = EFI_USB_PROTOCOL_GUID;
    EFI_USB_PROTOCOL *UsbProtocol = NULL;
    USB_GLOBAL_DATA   *UsbData = NULL;
        
    Status = pBS->LocateProtocol( &gEfiUsbProtocolGuid, \
                                      NULL, \
                                      &UsbProtocol );
    if (EFI_ERROR(Status)) return;

    //restore backup skip table pointer
    UsbData = (USB_GLOBAL_DATA*)UsbProtocol->USBDataPtr;    
    UsbData->gUsbSkipListTable = BackupSkipTable;
}    
#endif

    //Get a list of all USB Controllers
    Status = FbGetPciHandlesByClass(
        PCI_CL_SER_BUS, PCI_CL_SER_BUS_SCL_USB, &Number, &Handle
    );
    if (EFI_ERROR(Status)) return;
    
    for(i=0; i<Number; i++)
    {
        pBS->DisconnectController(Handle[i],NULL,NULL);
    }
    pBS->FreePool(Handle); 

    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OemConfigurationChanged
//
// Description: This function checks if configuration was changed since last boot
//
// Input:       None
//
// Output:      TRUE if configuration was changed, FALSE otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN OemConfigurationChanged(VOID)
{
    EFI_STATUS Status;
    UINT32 BootFlow;
    UINTN Size = sizeof(UINT32);

    Status = pRS->GetVariable(L"BootFlow", &guidBootFlow, NULL, &Size, &BootFlow);

    return (!EFI_ERROR(Status) && BootFlow == BOOT_FLOW_CONDITION_FIRST_BOOT) ? TRUE : FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FastBootClearBootFailFlag
//
// Description: FastBoot clear boot fail flag callback
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FastBootClearBootFailFlag(
	IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS Status;
    UINT32 LastBootFailed;
    UINTN Size = sizeof(UINT32);

    Status = pRS->GetVariable(L"LastBootFailed", &FastBootVariableGuid, NULL, &Size, &LastBootFailed);
    if(!EFI_ERROR(Status)) {
        Status = pRS->SetVariable(L"LastBootFailed", 
                                  &FastBootVariableGuid, 
                                  EFI_VARIABLE_NON_VOLATILE,
                                  0,
                                  &LastBootFailed);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsFastBoot
//
// Description: This function FastBoot is enabled or disabled by checking 
//              elink "IsFastBootList"
//
// Input:       None
//
// Output:      TRUE if fast boot is enabled, FALSE otherwise
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsFastBoot(VOID)
{
    static EFI_GUID SetupVariableGuid = SETUP_GUID;    
    EFI_STATUS  Status;
	UINTN         Size;
    BOOLEAN Result = TRUE;
    UINTN   i;
    EFI_GUID FastBootPolicyGuid = FAST_BOOT_POLICY_PROTOCOL_GUID;

    // init globe variable 
#ifdef CMOS_MANAGER_SUPPORT
  #if CMOS_MANAGER_SUPPORT
            LOCATE_CMOS_ACCESS_PROTOCOL(Status, CmosInterface);
            ASSERT_EFI_ERROR (Status);
  #endif
#endif

    Status = pBS->LocateProtocol(&FastBootPolicyGuid,NULL,&gFastBootPolicy);
    if (EFI_ERROR(Status) || gFastBootPolicy->FastBootEnable == FALSE)
        return FALSE;

    Size = sizeof(FbSetupData);
    Status = pRS->GetVariable(L"Setup", &SetupVariableGuid, NULL, &Size, &FbSetupData);
    if (EFI_ERROR(Status)) return FALSE;


    // check IsFastBootList
    for (i=0;IsFastBootList[i] && Result; i++)
        Result = IsFastBootList[i](&FbSetupData);


    if (!Result)
        ReturnToNormalBoot();    //return to normal boot
    else
        EnableLegacy16Fastboot();
 
    return Result;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsFastBootDeafult
//
// Description: This function returns the status of Fast boot setup option
//
// Input:       
//  IN  SETUP_DATA  *FbSetupData - ptr of SetupData
//
// Output:      TRUE if fast boot is enabled, FALSE otherwise
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsFastBootDefault (
    IN SETUP_DATA *FbSetupData
)
{
    static EFI_GUID SetupVariableGuid = SETUP_GUID;

    UINT16        BootNext;
	UINTN         Size;
    EFI_STATUS    Status;
    EFI_BOOT_MODE BootMode;
    BOOLEAN       FastBoot;

    if (!gFastBootPolicy->FastBootEnable) return FALSE;

	BootMode = GetBootMode();
    
    if (BootMode == BOOT_WITH_MINIMAL_CONFIGURATION) 
    return TRUE;        

    if (!gFastBootPolicy->FirstFastBootInS4 && BootMode == BOOT_ON_S4_RESUME) {
        if (gFastBootPolicy->LastBootVarPresence)
            return (gFastBootPolicy->BootCount > 0) ? TRUE : FALSE;        
    }

//Check for "BootNext" variable
    Size = sizeof(BootNext);
    Status = pRS->GetVariable(L"BootNext", &EfiVariableGuid, NULL, &Size, &BootNext);
    if(!EFI_ERROR(Status)) {
        FastBoot = FALSE;
    } else {
        FastBoot = gFastBootPolicy->FastBootEnable;
    }

	return FastBoot;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ChangeSetupBootFlow
//
// Description: Changea Setup Boot Flow
//
// Input:       UINT32 BootFlow       
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ChangeSetupBootFlow(UINT32 BootFlow)
{
    EFI_STATUS  Status;
    EFI_GUID guidBootFlow = BOOT_FLOW_VARIABLE_GUID;    

    Status = pRS->SetVariable(L"BootFlow", 
                               &guidBootFlow, 
                               EFI_VARIABLE_BOOTSERVICE_ACCESS,
                               sizeof(BootFlow),
                               &BootFlow);
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IsAmtBoot
//
// Description: Do NOT perform FastBoot if AMT boot is request.
//
// Input:       
//  IN  SETUP_DATA  *FbSetupData - ptr of SetupData
//
// Output:      TRUE if fast boot is enabled, FALSE otherwise
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if iME_SUPPORT
#include "ReferenceCode\ME\Protocol\AlertStandardFormat\AlertStandardFormat.h"
#include "Board\EM\MeWrapper\AmtWrapper\Protocol\AmtWrapper\AmtWrapper.h"
BOOLEAN IsAmtBoot(IN SETUP_DATA *FbSetupData)
{
    EFI_GUID gEfiAmtWrapperProtocolGuidTse = EFI_AMT_WRAPPER_PROTOCOL_GUID;
    EFI_GUID gEfiAlertStandardFormatProtocolGuid = EFI_ALERT_STANDARD_FORMAT_PROTOCOL_GUID;
    AMT_WRAPPER_PROTOCOL *pAmtWrapper = NULL;
    EFI_STATUS            Status;
    EFI_ALERT_STANDARD_FORMAT_PROTOCOL  *AsfCheck;
    EFI_ASF_BOOT_OPTIONS  *mInternalAsfBootOptions;

    if (pAmtWrapper == NULL) {
        Status = pBS->LocateProtocol(&gEfiAmtWrapperProtocolGuidTse, NULL, &pAmtWrapper);
    }

    //case IDER
    if (pAmtWrapper != NULL) {
        if (pAmtWrapper->ActiveManagementEnableIdeR()||pAmtWrapper->ActiveManagementEnableSol()){
            ChangeSetupBootFlow(BOOT_FLOW_CONDITION_NORMAL);
            return FALSE;   //Is AMT boot, return FALSE for fast boot disabled.
        }
    }

    //case ASF
    //Get the ASF options
    //if set then we have to do and Asfboot
    Status = pBS->LocateProtocol (
                    &gEfiAlertStandardFormatProtocolGuid,
                    NULL,
                    &AsfCheck
                    );
	
    if (EFI_ERROR (Status)) {
        //Is not AMT boot, return TRUE for fast boot enabled.
        return TRUE;
    }

    Status = AsfCheck->GetBootOptions (AsfCheck, &mInternalAsfBootOptions);
	  
    if (mInternalAsfBootOptions->SubCommand != ASF_BOOT_OPTIONS_PRESENT)
        return TRUE;   //Is not AMT boot, return TRUE for fast boot enabled.
    else {
        ChangeSetupBootFlow(BOOT_FLOW_CONDITION_NORMAL);
        return FALSE;    //Is AMT boot, return FALSE for fast boot disabled.
    }

}
#else // for order ME version

#define AMI_AMT_BOOT_OPTION_GUID \
{0x9ba25957, 0x21bf, 0x41d0, 0x81, 0xe7, 0xe7, 0xb6, 0xd8, 0x88, 0x2a, 0x49}

BOOLEAN IsAmtBoot(IN SETUP_DATA *FbSetupData)
{
    EFI_GUID gAmtBootOptionGuid = AMI_AMT_BOOT_OPTION_GUID;
    EFI_STATUS Status;
    UINT16  AmtBootOption = NULL;
    UINTN   VariableSize = 0;

    // Get Device Type Variable of AMT Boot Option.
    VariableSize = sizeof(UINT16);

    Status = pRS->GetVariable ( L"AmtBootOption",
                                  &gAmtBootOptionGuid,
                                  NULL,
                                  &VariableSize,
                                  &AmtBootOption  );

    if (EFI_ERROR(Status))  
//Is not AMT boot, return TRUE for fastboot enabled.
	    return TRUE;
    else {
//Is AMT boot, return FALSE for fastboot disabled.
        ChangeSetupBootFlow(BOOT_FLOW_CONDITION_NORMAL);
        return FALSE;
    }   
}								
#endif	

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   TseHandShake
//
// Description: This function executes FastBoot path via AMI TSE boot manager
//
// Input:       FAST_BOOT LastBoot - last successful fast boot information
//
// Output:      EFI_ERROR - if fast boot via AMI TSE cannot be executed
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS TseHandShake()
{
    EFI_STATUS Status;
	AMI_POST_MANAGER_PROTOCOL *AmiPostMgr;
    UINT32 BootFlow;
    EFI_HANDLE Handle = NULL;

    Status = pBS->LocateProtocol(&AmiPostMgrProtocolGuid, NULL, &AmiPostMgr);
    if(EFI_ERROR(Status))
        return Status;

	if( gFastBootPolicy->UEfiBoot == TRUE)
        FastBootProtocol.Launch =  FastEfiBoot;
    else
		FastBootProtocol.Launch =  FastLegacyBoot;

	Status = pBS->InstallMultipleProtocolInterfaces(
		                        &Handle,
		                        &AmiFastBootProtocolGuid, 
                                &FastBootProtocol,
		                        NULL);

    if(EFI_ERROR(Status))
        return Status;

	BootFlow = BOOT_FLOW_CONDITION_FAST_BOOT;
    Status = pRS->SetVariable(L"BootFlow", 
	                          &guidBootFlow, 
	                          EFI_VARIABLE_BOOTSERVICE_ACCESS,
	                          sizeof(BootFlow),
	                          &BootFlow);

    if(EFI_ERROR(Status))
        return Status;
    
    TRACE((-1,"FB: TseHandShake\n"));
        
	Status = AmiPostMgr->Handshake();

//if we're here fast boot failed, change Boot flow back to BOOT_FLOW_CONDITION_NORMAL

	BootFlow = BOOT_FLOW_CONDITION_NORMAL;
    Status = pRS->SetVariable(L"BootFlow", 
	                          &guidBootFlow, 
	                          EFI_VARIABLE_BOOTSERVICE_ACCESS,
	                          sizeof(BootFlow),
	                          &BootFlow);
    return EFI_ABORTED;
}

//
//  Dummy console protocol
//
EFI_STATUS DummyInReset( 
	IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,	
	IN BOOLEAN                        EV 
)
{
	return EFI_SUCCESS;
}
            
EFI_STATUS DummyReadKeyStroke(
	IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	OUT	EFI_INPUT_KEY                  *Key 
)
{
	return EFI_SUCCESS;
}

EFI_STATUS  DummyReset(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN                         EV
)
{
	return EFI_SUCCESS;
}


EFI_STATUS DummyOutputString(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16                          *String
)
{
	return EFI_SUCCESS;
}

EFI_STATUS  DummyTestString(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This,
	IN CHAR16 *String)
{
	return EFI_SUCCESS;
}

EFI_STATUS DummyQueryMode(
	IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This,
	IN  UINTN                           ModeNum,
	OUT UINTN                           *Col,
	OUT UINTN                           *Row
)
{
	return EFI_SUCCESS;
}

EFI_STATUS DummySetMode(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           ModeNum
)
{
	return EFI_SUCCESS;
}


EFI_STATUS  DummySetAttribute(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           Attribute
)
{
	return EFI_SUCCESS;
}

EFI_STATUS  DummyClearScreen(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This
)
{
    return EFI_SUCCESS;
}

EFI_STATUS DummySetCursorPosition(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           Column,
	IN UINTN                           Row
)
{
	return EFI_SUCCESS;
}

EFI_STATUS  DummyEnableCursor(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN Visible	)
{
	return EFI_SUCCESS;
}

BOOLEAN IsRuntime(
    VOID
)
{
    return Runtime;
}

VOID FbConnectInputDevices(
    VOID
)
{
    FbConnectConInVariable();
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
