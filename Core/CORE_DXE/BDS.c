//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/BDS.c 3     7/15/14 9:54p Chienhsieh $
//
// $Revision: 3 $
//
// $Date: 7/15/14 9:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/BDS.c $
// 
// 3     7/15/14 9:54p Chienhsieh
// Update rev.125 for EIP172950, Core updates for UEFI Variable Technical
// Advisory implement.
// 
// 125   5/09/14 2:44p Artems
// [TAG]  		EIP166565
// [Category]  	Improvement
// [Description]  	Removed runtime-access attribute from the variables
// MemoryTypeInformation
// and PreviousMemoryTypeInformation
// [Files]  		BDS.c
// 
// 2     11/21/12 4:21a Wesleychen
// Update for SCT test (EIP104956).
// 
// 117   10/29/12 4:03p Artems
// [TAG]  		EIP104956
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	UEFI 2.3.1 SCT test failed in Generic\EfiCompliant case.
// The VariableAttribute of ErrOut is not correct.
// [RootCause]  	System variable ErrOut was saved without EFI_NON_VOLATILE
// attribute
// [Solution]  	Added missing attribute
// [Files]  		Bds.c
// 
// 116   10/08/12 6:56p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	build error with message invalid Code page
// [RootCause]  	Presence of special characters in debug comment
// [Solution]  	Removed special characters
// [Files]  		BDS.c
// 
// 115   7/20/12 10:33a Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Improved debug output for SaveMemoryInformation
// function
// [Files]  		BDS.c
// 
// 114   5/30/12 4:59p Felixp
// SaveMemoryTypeInformation is updated to never decrease the memory type
// usage values
// to workaround Windows 7 and Windows 8 bug.
// 
// 113   5/30/12 3:12p Felixp
// [TAG]  		EIP90941
// [Category]  	Bug Fix
// [Symptom]  	"System resume from S4 would have problem when iRST 
// setting changed and system did S4.
// [RootCause]  	SaveMemoryTypeInformation has been called twice.
// [Solution]  	The function is updated to perform processing only during
// the first call.
// 
// 112   5/23/12 11:42a Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Description]  	Replaced FirmwareVolume protocol with FirmwareVolume2
// protocol
// [Files]  		bootoptions.h BDS.c
// 
// 111   4/12/12 11:12a Felixp
// [TAG]  	      EIP85611
// [Category]      Improvement
// [Description]  Memory map is not consistent between 
//   second and third boots if system has been reset from the Setup 
//   during the very first boot.
// [Files]  	      Bds.c, CORE_DXE.sdl
// 
// 110   12/05/11 2:18p Felixp
// // 109   11/21/11 11:03a Felixp
// // [TAG]  		EIP69841
// // [Category]  	Improvement
// // [Description]  	Improvements in the Memory Type Information
// processing
// // to properly handle first boot.
// 
// 109   11/21/11 11:03a Felixp
// [TAG]  		EIP69841
// [Category]  	Improvement
// [Description]  	Improvements in the Memory Type Information processing
// to properly handle S4 resume during the fast boot.
// 
// 108   11/09/11 3:19p Oleksiyy
// [TAG]  		EIP64296 
// [Category]  	New Feature
// [Description]  	Creation and filling of Firmware Performance Data Table
// is added.
// [Files]  		AcpiCore.c, AmiDxeLib.h, BDS.c, DxeMain.c, EfiLib.c,
// Image.c, S3Resume.c and FirmPerfDataTab.h
// 
// 107   11/01/11 1:55p Felixp
// [TAG]  		EIP 69841 and 71719
// [Category]  	Improvement
// [Description]  	The AMI customizations are removed from the DXE memory
// manager. 
// They are replaced with the Memory Type Information HOB used in Tiano
// projects. 
// This is done to reduces number of descriptors in the memory map 
// and to workaround Windows bug (Windows can't handle memory allocations 
// that happen after the start of the OS loader).
// [Files] CORE_DXE.sdl, Page.c, BDS.c, DxeIpl.c
// 
// 106   11/01/11 1:42p Felixp
// Improvement: Support for logging of the performance information during
// legacy boot.
// 
// 105   10/20/11 6:59p Artems
// Function ConnectConsoles moved to FastBoot module
// 
// 104   3/16/11 11:41p Felixp
// Editorial: Several spelling errors in the comments are fixed
// 
// 103   2/25/11 12:51p Artems
// EIP 53767 - Velocity boot time above 5 seconds. Added provision to skip
// USB keyboard initialization
// 
// 102   2/15/11 6:52p Artems
// Add possibility to modify ConnectConsoles function list with SDL tokens
// 
// 101   12/03/10 10:26a Felixp
// 
// 100   12/03/10 10:23a Felixp
// 
// 99    12/03/10 10:23a Felixp
// Bug fix in InitConVars: console-related fields of the systems table
// were not initialized on headless systems.
// 
// 98    10/15/10 12:02p Felixp
// Bug fix in ConnectConsoles function
// 
// 97    10/01/10 8:02a Felixp
// ThisImageHandle variabled added (for compatibility with existing
// modules)
// Clean up
// 
// 96    9/29/10 9:21a Felixp
// Enhancement(EIP 39464) : Implementation of the BdsEntry function is
// changed. 
// The BdsEntry is now a dispatching function that calls a collection of
// functions 
// formed by the BDS_CONTROL_FLOW eLink.
// 
// 95    6/29/10 11:06p Felixp
// New Boot Options Maintenance Infrastructure.
// See AMI_Aptio_4.x_Boot_Options_Maintenance_Infrastructure_Porting_Guide
// _NDA.doc for details.
// 
// 94    5/07/10 6:00p Felixp
// Improvement in ConnectDevicePath (EIP 38132): Null pointer check of the
// input parameter is added
// 
// 93    3/22/10 10:20a Artems
// EIP 35562 Fixed boot variable name - hex digits should be in upper case
// 
// 92    2/03/10 4:34p Oleksiyy
// Minor bug fix (typecasting)
// 
// 91    2/02/10 5:45p Felixp
// Fast Boot related code is removed from BDS. It is now part of the stand
// alone FastBoot eModule.
// 
// 90    10/28/09 12:19p Felixp
// Minor bug fix: check for a NULL pointer is added to the
// CreateLegacyBootOption function(EIP 28577).
// 
// 89    10/09/09 6:06p Felixp
// UEFI 2.1 - related changes (suppot Framework and UEFI HII).
// 
// 88    10/09/09 11:58a Felixp
// Code that sets ConOutDev variable is removed. It is not needed. The
// variable is set by the ConSplitter driver.
// 
// 87    8/04/09 1:28p Felixp
// Bug fix: in BuildBootOptionName function.
// Symptoms: Systems with several boot devices where occasionally handing
// towards the end of the BDS phase.
// 
// 86    7/10/09 5:58p Felixp
// New Boot Option Maintenance Ifrastructure is added
// 
// 85    7/08/09 8:36a Felixp
// Bug fix (EIP 23027): Update NVRAM instance of LegacyDevOrder variable
// when it's modified by the AdjustLegacyDevOrder function.
// 
// 84    6/26/09 3:08p Felixp
// ConnectDefaultConOut updated:
//  1. AGP support is removed
//  2. Improved on-board device detection logic 
//    (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE attribut is used).
// 
// 83    5/22/09 9:52a Felixp
// Minor improvements in AdjustLegacyDevOrder function
// 
// 82    5/21/09 5:20p Felixp
// Bug fix in BuildBootOptionName function
// 
// 81    1/20/09 10:57p Felixp
// 
// 80    1/20/09 3:30p Felixp
// Bug fix. EIP 16566. Order of legacy devices within BBS group is reset
// when configuration changes.
// Symptoms: Order of legacy devices within BBS group is sometimes reset 
// when bootable devices are added (enabled) or removed (disabled).
// Here is one of the ways to reproduce the problem:
// 1. Make sure the following bootable devices are plugged into the
// system:
//  - Bootable network device (onboard or offboard) 
//  - USB flash drive emulated as hard drive 
//  - IDE or SATA hard drive 
// 2. Boot to setup. 
// 3. Enable PXE boot using "Lunch PXE OpRom" option on the "Advanced"
// page. 
// 4. Save the settings, reboot the system, and enter the setup. 
// 5. On the "Boot" page, update "Hard Driver BBS Priorities" to set USB
// drive as a first boot device. 
// 6. Disable PXE boot using "Lunch PXE OpRom" option on the "Advanced"
// page. 
// 7. Save the settings, reboot the system, and enter the setup. 
// 8. Enter "Hard Driver BBS Priorities" menu on the "Boot" page. 
// USB drive priority has been reset( it is no longer the first boot
// device). 
// Details: BDS used index within BBS table to match saved priorities with
// available boot devices. 
// However, when list of boot devices changes, BBS index may also change. 
// For example, when network boot is enabled, boot option for a network
// device 
// is inserted into the BBS table prior to the USB drive boot option. 
// As a result, index of the USB drive boot option increases by one 
// and matching against saved boor priority fails.
// BDS code is updated to save more information about legacy boot devices.
// For every legacy boot device BDS saves 
// checksum of the device name into the NVRAM (along with device index). 
// When index matching fails, BDS uses saved checksum to find updated BBS
// index 
// of the boot option. 
// 
// 79    1/14/09 3:52p Felixp
// BDS updated to signal beginning of the driver connection cycle by
// installing the protocol.
// 
// 78    1/05/09 3:02p Felixp
// Bug fix. EIP 17217
// Problems during video card switching.
// Symptoms: Some systems were hanging during after replacement 
// of the video card.
// 
// 77    11/03/08 5:21p Felixp
// Do no re-create boot option for the built-in Shell, if Shell is not
// included into the ROM
// 
// 76    10/29/08 12:52p Felixp
// RunDrivers updates: ignore non-active driver options; perform reconnect
// once
// 
// 74    10/22/08 4:24p Felixp
// 
// 73    10/22/08 11:35a Felixp
// 1. Code to recreate deleted boot option for the built-in Shell is
// added(EIP 15524). 
// 2. Processing of the DriverOrder list is added 
// 3. Clean up
// 
// 72    10/21/08 5:56p Felixp
// Multi-language support added to UEFI boot options implementation
// 
// 71    10/21/08 3:30p Felixp
// BuildBootOptionName function improvements and bug fixes
// 
// 70    10/17/08 3:46p Yakovlevs
// Support for UEFI boot options added
// 
// 69    10/10/08 4:25p Felixp
// - Improved handling of console devices
// - Clean up
// 
// 68    10/09/08 5:07p Felixp
// Bug fixes:
// - Support for systems with no console devices.
//   If no console input or output devices are available, 
//   system table is populated with the fake ConIn/ConOut handles 
//   and protocol interface pointers. 
//   This prevents potential failures caused by the NULL pointers in the
// system table. 
// - Early Console device initialization during the first boot(EIP 13459).
//   During the very first boot after the firmware update, 
//   console devices were initialized towards the end of the boot.
//   The logic has been updated to initialize default console devices 
//   at the beginning of the BDS connection cycle. 
// - Serial Redirection could not be enabled, if 
//   it was disabled by default(EIP 15565)
// 
// 67    9/30/08 11:07p Felixp
// Performance measurement support: callback to publish performance data
// for OS usage added (the callback is generated by TSE).
// 
// 66    6/06/08 11:00a Felixp
// 1. Performance measurement support is added
// 2. Support for boot with minimal configuration is added
// 3. Code is reformatted in accordance with the coding standards
// 
// 65    5/06/08 10:07a Felixp
// 
// 64    12/17/07 4:07p Felixp
// Signal protocol event before handing control over to TSE
// 
// 63    11/08/07 4:51p Felixp
// Code updated to compile and work without CSM.
// 
// 62    10/26/07 2:36p Felixp
// New FW based load file protocl is added.
// This protocol is used to load FW based EFI applications such as built
// in Shell.
// 
// 61    10/17/07 11:28a Felixp
// Update in InitBbs routine: Delete LegacyDevOrder when no legacy devices
// are found.
// This fixes hang in AMITSE when no bootable devices are present.
// 
// 60    8/31/07 1:55p Felixp
// Updated to support new location of AMIPostMgr.h. It is moved from
// Core/em/AMITSE into Include/Protocol
// 
// 59    8/07/07 2:36p Felixp
// Additionanal Status Codes added
// 
// 58    4/10/07 9:34a Felixp
// 
// 55    3/18/07 2:30p Felixp
// Initialization of Lang & LangCodes variables removed 
// (it is done in Setup now)
// 
// 54    2/28/07 7:32p Felixp
// 
// 52    2/26/07 6:12p Felixp
// Bug fix in SetBbsPriorities.
// 
// 51    2/13/07 9:18a Felixp
// MRE Handshake protocol renamed to AMI POST Manager protocol
// (MreHandshake.h removed from Core Protocols and added to AMITSE module
// as AMIPostMgr.h)
// 
// 50    2/12/07 1:45p Felixp
// 1. Correct handling of disabled legacy BBS options
// 2. Name of the legacy device removed from legacy boot option because it
// is not needed (AMITSE does not use it)
// 3. Clean up in ConnectDevicePath
// 
// 49    12/29/06 3:00p Felixp
// Console initialization logic changed
// 
// 48    10/30/06 6:03p Felixp
// Updated to be complient with HII Spec. 0.92 (used to be 0.91)
// 
// 47    10/13/06 4:43p Felixp
// Beep when ConIn available
// 
// 46    10/13/06 9:27a Felixp
// Patch for disconnected FDD moved to a proper place
// 
// 45    10/12/06 9:42a Felixp
// UEFI2.0 compliance: use CreateReadyToBootEvent instead of CreateEvent
// 
// 44    9/29/06 3:52p Pavell
// Added processing and dispatching capsule
// 
// 42    5/23/06 4:17a Felixp
// Patch for disconnection of the Floppy Controller added
// 
// 41    5/19/06 10:45p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
// 
// 40    3/13/06 10:07a Felixp
// 
// 39    12/22/05 11:25a Felixp
// 
// 38    11/08/05 4:07a Felixp
// Support for TSE notifications added
// 
// 37    11/07/05 10:34a Felixp
// Boot with minimum configuration suuport
// 
// 36    9/29/05 4:36p Robert
// 
// 35    8/25/05 11:47a Felixp
// Code added to start Standard ConIn devices (PS2, USB) early
// 
// 34    8/25/05 11:41a Felixp
// 
// 33    8/22/05 5:29p Felixp
// Invoke dispatcher before boot
// 
// 32    7/29/05 6:52p Felixp
// improvement in InitBbs: correct handling of LegacyDevOrder shorter then
// 6 bytes
// 
// 3     7/20/05 8:03p Felixp
// workaround for password support
// 
// 28    7/15/05 7:16p Felixp
// CONSOLE_DEVICES_STARTED_PROTOCOL_GUID added.
// BDS uses it to notify Splitter that Console Devices have been started.
// Once Splitter receives notification, it will install ConIn and ConOut
// in System Table
// 
// 27    7/14/05 12:10a Felixp
// BBS support
// 
// 25    5/24/05 2:55p Felixp
// Boot menu logic moved to SetupEngine.
// Now BDS just gives control to MREHandshake
// 
// 24    4/28/05 1:06p Felixp
// bug fix in InitConVars
// 
// 23    4/25/05 12:12p Felixp
// AddBootOption - loader options can now be passed
// 
// 21    4/08/05 3:02p Felixp
// SignalReadyToBoot added
// 
// 20    4/08/05 7:39a Felixp
// Boot Menu implemented
// 
// 19    4/02/05 3:24p Felixp
// 
// 18    3/28/05 7:03p Felixp
// DrawBmp function added
// 
// 15    3/17/05 7:51p Felixp
// pBootScript->CloseTable commented out
// 
// 14    3/15/05 2:55p Felixp
// 1. Code to initialize global EFI variables added
// 2. Code to Close boot script table and save the address to NVRAM added
// 
// 13    2/14/05 10:40a Felixp
// Off-board video started before on-board
// 
// 12    2/11/05 6:05p Felixp
// Code optimized by using DPAddNode instead of DPAdd
// Logic to set video card priorities added(from hi ti lo):  
// AGP->on board PCI ->off board PCI
// 
// 11    2/07/05 5:21p Felixp
// function GetEfiVariable moved to AmiDxeLib
// 
// 10    2/03/05 8:07p Felixp
// ConnectDevicePath change: now last node connected recursively
// 
// 9     2/03/05 7:58p Felixp
// 
// 8     2/03/05 7:45p Felixp
// Logic to initialize Console variables added
// 
// 7     2/01/05 4:24p Felixp
// 1 .ConnectDevicePath fixed (before it didn't connect last node in the
// device path)
// 2. REAY to BOOT event signaled
// 
// 6     1/25/05 3:27p Felixp
// if GSE absent restart shell if it returns
// 
// 5     1/19/05 7:01p Felixp
// 
// 3     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 2     1/10/05 5:10p Felixp
// Patches for Intel CSM and Intel Terminal driver disabled
// 
// 28    12/23/04 9:29a Felixp
// ArchProtocols moved to Include\Protocols
// 
// 27    12/21/04 4:53p Markw
// Modified device path defines for consistency.
// 
// 26    12/21/04 4:21p Markw
// Renamed hardware device path definition for consistency.
// 
// 21    12/01/04 3:24p Felixp
// GSE support added
// 
// 20    8/03/04 6:46p Felixp
// SetVariable for "Lang" and "LangCodes" moved to do it before all
// drivers are connected
// 
// 15    7/16/04 3:57p Felixp
// Changes to support both 7f and ff values for the device path end type
// 
// 1     3/30/04 3:26p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	BDS.c
//
// Description:	Implementation of the BDS architectural protocol
//
//<AMI_FHDR_END>
//**********************************************************************
#include "BootOptions.h"
#include <Protocol/BDS.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextOut.h >
#include <Protocol/LoadedImage.h>
#include <Protocol/ConsoleControl.h>
#include <Protocol/AMIPostMgr.h>
#include <Protocol/LoadFile.h>
#include <DXE.h>
#include <HOB.h>
#include <Guid/MemoryTypeInformation.h>

/**************************** TYPES ***********************************/

/***************** FUNCTION DECLARATIONS *****************************/
//this funciton is created from InitList.c template file during build process
VOID InitParts2(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);

//Local functions
VOID BdsEntry (IN EFI_BDS_ARCH_PROTOCOL *This);

EFI_STATUS FwLoadFile (
	IN EFI_LOAD_FILE_PROTOCOL *This, IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
	IN BOOLEAN BootPolicy, IN OUT UINTN *BufferSize,
	IN VOID *Buffer OPTIONAL
);

/**************************** CONSTANTS *******************************/
#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}
// {3AA83745-9454-4f7a-A7C0-90DBD02FAB8E}
#define BDS_CONNECT_DRIVERS_PROTOCOL_GUID \
    { 0x3aa83745, 0x9454, 0x4f7a, { 0xa7, 0xc0, 0x90, 0xdb, 0xd0, 0x2f, 0xab, 0x8e } }
// {8DB699CC-BC81-41e2-AAC6-D81D5300D759}
#define PARTITION_VARIABLE_GUID\
    { 0x8db699cc, 0xbc81, 0x41e2, { 0xaa, 0xc6, 0xd8, 0x1d, 0x53, 0x0, 0xd7, 0x59 } }
// {5023B95C-DB26-429b-A648-BD47664C8012}
#define AMI_MEDIA_DEVICE_PATH_GUID \
    { 0x5023b95c, 0xdb26, 0x429b, { 0xa6, 0x48, 0xbd, 0x47, 0x66, 0x4c, 0x80, 0x12 } }

extern EFI_GUID gEfiBdsArchProtocolGuid; // = EFI_BDS_ARCH_PROTOCOL_GUID;
extern EFI_GUID gEfiDevicePathProtocolGuid ;//= EFI_DEVICE_PATH_PROTOCOL_GUID;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid; // = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;
extern EFI_GUID gEfiLoadedImageProtocolGuid; //=EFI_LOADED_IMAGE_PROTOCOL_GUID;
extern EFI_GUID gEfiPciIoProtocolGuid; // = EFI_PCI_IO_PROTOCOL_GUID;
extern EFI_GUID gEfiBlockIoProtocolGuid;
extern EFI_GUID gEfiLoadFileProtocolGuid;
extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;
//defined in BdsBoard.c
extern EFI_GUID SetupEnterProtocolGuid;
extern EFI_GUID SecondBootOptionProtocolGuid;
extern EFI_GUID BeforeBootProtocolGuid;
extern EFI_GUID BeforeLegacyBootProtocolGuid;
extern EFI_GUID *DefaultAppFfsGuidPtr;

extern BDS_CONTROL_FLOW_FUNCTION *BdsControlFlowFunctions[];
extern CHAR8 *BdsControlFlowFunctionNames[];

EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
EFI_GUID AmiPostMgrProtocolGuid=AMI_POST_MANAGER_PROTOCOL_GUID;
EFI_GUID ConInStartedProtocolGuid = CONSOLE_IN_DEVICES_STARTED_PROTOCOL_GUID;
EFI_GUID ConOutStartedProtocolGuid = CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID;
EFI_GUID BdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
EFI_GUID BdsConnectDriversProtocolGuid = BDS_CONNECT_DRIVERS_PROTOCOL_GUID;
EFI_GUID PartitionVariableGuid = PARTITION_VARIABLE_GUID;

EFI_BDS_ARCH_PROTOCOL BDS = {&BdsEntry};

/**************************** VARIABLES *******************************/
//externals defined in BdsBoard.c
extern UINT16 DefaultTimeout;
extern BOOLEAN QuietBoot;
extern STRING_REF StrToken[];

// Global Variables
EFI_LOAD_FILE_PROTOCOL FwLoadFileInterface  = {FwLoadFile};

struct {
	VENDOR_DEVICE_PATH Media;
	EFI_DEVICE_PATH_PROTOCOL End;
} FwLoadFileDp = {
	{
        {
            MEDIA_DEVICE_PATH, MEDIA_VENDOR_DP,
            sizeof(VENDOR_DEVICE_PATH)
        },
        AMI_MEDIA_DEVICE_PATH_GUID
    },
	{
        END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
        sizeof(EFI_DEVICE_PATH_PROTOCOL)
    }
};

EFI_HANDLE LpcHandle = NULL;
EFI_DEVICE_PATH_PROTOCOL *LpcDevicePath = NULL;

VOID ConnectDevicePath(IN EFI_DEVICE_PATH_PROTOCOL *pPath)
{
    EFI_HANDLE Handle;
    EFI_STATUS Status;

    if (pPath == NULL) return;
	while (TRUE)
	{
		EFI_DEVICE_PATH_PROTOCOL *pLastPath=NULL, *pFirstNode = pPath;
		if (isEndNode(pPath))
		{
			if (pPath->SubType == END_ENTIRE_SUBTYPE) break;
			pPath++;
			continue;
		}
		while(TRUE){
            EFI_DEVICE_PATH_PROTOCOL *Dp;
            UINT8 SubType;

	        pPath = pFirstNode;

            //LocateDevicePath can not work with multi-instance device paths.
            //Prepare single instance device path and call LocateDevicePath
            Dp = DPGetEndNode(pPath);
	        SubType = Dp->SubType;
	        Dp->SubType=END_ENTIRE_SUBTYPE;
            Status = pBS->LocateDevicePath(&gEfiDevicePathProtocolGuid, &pPath, &Handle);
            Dp->SubType=SubType;
			if (EFI_ERROR(Status)) break;

			if (isEndNode(pPath))
			{
 				//Last time let's do it recursively	
				pBS->ConnectController(Handle,NULL,NULL,TRUE);	
				break;
			}
			if (pPath==pLastPath) break;
			pLastPath = pPath;
			if (EFI_ERROR(pBS->ConnectController(Handle,NULL,pPath,FALSE))) break;
		}
		while (!isEndNode(pPath))
			pPath = NEXT_NODE(pPath);
	}
}

EFI_DEVICE_PATH_PROTOCOL* AddDevicePath(EFI_DEVICE_PATH_PROTOCOL *pDp1, EFI_DEVICE_PATH_PROTOCOL *pDp2)
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

EFI_STATUS GetPciHandlesByClass(
    UINT8 Class, UINT8 SubClass, UINTN *NumberOfHandles, EFI_HANDLE **HandleBuffer
){
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;

    if (!NumberOfHandles || !HandleBuffer) return EFI_INVALID_PARAMETER;
	//Get a list of all PCI devices
	Status = pBS->LocateHandleBuffer(
        ByProtocol,&gEfiPciIoProtocolGuid, NULL, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return Status;
    *NumberOfHandles = 0;
	for(i=0; i<Number; i++)
	{
		EFI_PCI_IO_PROTOCOL *PciIo;
		UINT8 PciClass[4];
		Status=pBS->HandleProtocol(Handle[i],&gEfiPciIoProtocolGuid,&PciIo);
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

EFI_STATUS InitSystemVariable(
	IN CHAR16 *NameStr, IN UINTN DataSize, IN VOID *Data
)
{
	UINTN Size = 0;
	EFI_STATUS Status;
	Status = pRS->GetVariable(NameStr, &EfiVariableGuid, NULL, &Size, NULL);
	if (Status==EFI_NOT_FOUND)
	{
		return pRS->SetVariable(
			NameStr, &EfiVariableGuid,
			EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
			DataSize, Data);
	}
	return EFI_SUCCESS;
}

static EFI_HANDLE *RootHandles;
static UINTN NumberOfHandles;
VOID ConnectEverything()
{
	UINTN i;
	for(i=0; i<NumberOfHandles; i++) pBS->ConnectController(RootHandles[i],NULL,NULL,TRUE);
/////////////////////////////////////////
//TODO: Ugly patch for the Floppy Controller. Find the better place for it!
// It is necessary to Disconnect Floppy Device Handle when Floppy Drive is not connected.
// This is necessary to disable Floppy Device in the Super I/O
// and eliminate BBS Floppy boot option.
// It was previously done (In Core 4.0) by the Floppy Controller driver.
// However, EDK DXE Core (DxeMain) crashes during the 
// DisconnectController operation performed from within the Start function.
// Because of that, the Floppy Controller driver code is commented out
// and this patch is created.
// If you remove this code, you should also remove 
// LpcHandle & LpcDevicePath global variables.
// They are only used to implement this patch.
	if (LpcDevicePath)
	{
		EFI_HANDLE Handle;
		ACPI_HID_DEVICE_PATH FloppyCtrl = {
			{ACPI_DEVICE_PATH,ACPI_DP,sizeof(ACPI_HID_DEVICE_PATH)},
			EISA_PNP_ID(0x0604),0
		};
		EFI_DEVICE_PATH_PROTOCOL *ChildDp=DPAddNode(LpcDevicePath, &FloppyCtrl.Header);
		EFI_STATUS Status=pBS->LocateDevicePath(&gEfiDevicePathProtocolGuid, &ChildDp, &Handle);
		if (!EFI_ERROR(Status) && isEndNode(ChildDp))
		{
			VOID* pDummy;
			Status = pBS->HandleProtocol(Handle,&gEfiBlockIoProtocolGuid,&pDummy);
			if (EFI_ERROR(Status)) pBS->DisconnectController(LpcHandle,NULL,Handle);
		}
	}
}
VOID DisconnectEverything()
{
	UINTN i;
	for(i=0; i<NumberOfHandles; i++) pBS->DisconnectController(RootHandles[i],NULL,NULL);
}

VOID ReadyToBoot(UINT16 OptionNumber)
{
	//signal EFI_EVENT_SIGNAL_READY_TO_BOOT
	EFI_EVENT ReadToBootEvent;
	EFI_STATUS Status;
    if (OptionNumber!= (UINT16)-1)
    	pRS->SetVariable(
    		L"BootCurrent", &EfiVariableGuid,
    		EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
    		sizeof(OptionNumber), &OptionNumber
    	);
	Status = CreateReadyToBootEvent(
		TPL_CALLBACK, NULL, NULL, &ReadToBootEvent
	);
	if (!EFI_ERROR(Status)) {
		pBS->SignalEvent(ReadToBootEvent);
	   	pBS->CloseEvent(ReadToBootEvent);
	}
}

#if CSM_SUPPORT
EFI_STATUS BootLegacy(EFI_DEVICE_PATH_PROTOCOL *Dp, UINT16 Number)
{
	UINTN i, Old=-1, New, Priority=-1;
	BBS_BBS_DEVICE_PATH *BbsEntry = (BBS_BBS_DEVICE_PATH*)Dp;
    EFI_STATUS Status;
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;
    UINT16 HddCount;
    UINT16 BbsCount;
    HDD_INFO *HddInfo;
    BBS_TABLE *BbsTable;

	// Legacy Boot
    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
    if(EFI_ERROR(Status)) return Status;
	LegacyBios->GetBbsInfo(LegacyBios, &HddCount, &HddInfo, &BbsCount, &BbsTable);
	if (!BbsCount) return EFI_NOT_FOUND;	
	for(i=0; i<BbsCount; i++)
	{
		if ( //  !BbsTable[i].StatusFlags.Enabled
			/*||*/ BbsTable[i].BootPriority==BBS_IGNORE_ENTRY
			|| BbsTable[i].BootPriority==BBS_DO_NOT_BOOT_FROM
		) continue;
		if (!BbsTable[i].BootPriority && Old==-1) Old=i;
		if (	BbsTable[i].DeviceType==BbsEntry->DeviceType
			&&	BbsTable[i].BootPriority < Priority
		)
		{
			Priority = BbsTable[i].BootPriority;
			New = i;
		}
	}
	if (Old!=-1) BbsTable[Old].BootPriority=BbsTable[New].BootPriority;
	BbsTable[New].BootPriority=0;
	ReadyToBoot(Number);
	return LegacyBios->LegacyBoot(LegacyBios,(BBS_BBS_DEVICE_PATH*)Dp,0,0);
}
#endif

EFI_STATUS BootEfi(EFI_DEVICE_PATH_PROTOCOL *Dp, UINT16 Number, VOID *pOptions, UINT32 Size)
{
	EFI_STATUS Status;
	EFI_HANDLE Handle;
	EFI_LOADED_IMAGE_PROTOCOL *Image;
	Status=pBS->LoadImage(TRUE, TheImageHandle, Dp, NULL, 0, &Handle);
	if (EFI_ERROR(Status)) return Status;
	Status=pBS->HandleProtocol(Handle,&gEfiLoadedImageProtocolGuid,&Image);
	if (!EFI_ERROR(Status) && Size)
	{
		Image->LoadOptionsSize = Size;	
		Image->LoadOptions = pOptions;
	}
	ReadyToBoot(Number);
	return pBS->StartImage(Handle, NULL, NULL);
}

EFI_STATUS Boot(EFI_LOAD_OPTION *BootOption, UINT16 Number, UINTN Size)
{
	EFI_STATUS Status;
	EFI_DEVICE_PATH_PROTOCOL *Dp;
	Dp = (EFI_DEVICE_PATH_PROTOCOL*)
			(	//skip the header
				(UINT8*)(BootOption+1) 
				//skip the string
				+(Wcslen((CHAR16*)(BootOption+1))+1)*sizeof(CHAR16)
			);
	if (Dp->Type!=BBS_DEVICE_PATH)
	{
		UINT8 *pOptions = (UINT8*)Dp+BootOption->FilePathListLength;		
		Status=BootEfi(Dp,Number,pOptions, (UINT32)((UINT8*)BootOption+Size-pOptions));
	}
#if CSM_SUPPORT
	else
	{
		Status=BootLegacy(Dp,Number);
	}
#endif
	return Status;
}

VOID RunDrivers(){
	EFI_LOAD_OPTION *DriverOption = NULL; //buffer for DriverXXX variables
	UINT16 *DriverOrder = NULL; //old(saved) Driver Order
	UINTN DriverOrderSize = 0; //size of DriverOrder Variable
	EFI_STATUS Status;
	UINTN Size,i;
    BOOLEAN ReconnectAll = FALSE;

	//================== Init Driver Order buffers ========================//
	Status = GetEfiVariable(L"DriverOrder", &EfiVariableGuid, NULL, &DriverOrderSize, &DriverOrder);
    if (EFI_ERROR(Status)) return;
	//===================================================================//
	// Start drivers refered to by DriverXXXX                            //
	//===================================================================//
	for(i=0; i<DriverOrderSize/sizeof(UINT16); i++){	
		CHAR16 DriverStr[9];
		EFI_DEVICE_PATH_PROTOCOL *DevicePath;
	    EFI_HANDLE Handle;
	    EFI_LOADED_IMAGE_PROTOCOL *Image;
        UINT32 SizeOfOptions;
        UINT8 *Options;

		// Get Driver Option
		Swprintf(DriverStr,L"Driver%04X",DriverOrder[i]);
		Status=GetEfiVariable(DriverStr, &EfiVariableGuid, NULL, &Size, &DriverOption);
        if (   EFI_ERROR(Status) 
            || (DriverOption->Attributes & LOAD_OPTION_ACTIVE)==0
        ) continue; 

		DevicePath = (EFI_DEVICE_PATH_PROTOCOL*)
				(	//skip the header
					(UINT8*)(DriverOption+1) 
					//skip the string
					+(Wcslen((CHAR16*)(DriverOption+1))+1)*sizeof(CHAR16)
		);
	    Status=pBS->LoadImage(
            TRUE, TheImageHandle, DevicePath, NULL, 0, &Handle
        );
	    if (EFI_ERROR(Status)) continue;
	    Status=pBS->HandleProtocol(
            Handle,&gEfiLoadedImageProtocolGuid,&Image
        );
		Options = (UINT8*)DevicePath+DriverOption->FilePathListLength;
		SizeOfOptions=(UINT32)((UINT8*)DriverOption+Size-Options);
	    if (!EFI_ERROR(Status)&& SizeOfOptions!=0){
		    Image->LoadOptionsSize = SizeOfOptions;	
		    Image->LoadOptions = Options;
	    }
	    Status=pBS->StartImage(Handle, NULL, NULL);
        if (   !EFI_ERROR(Status) 
            && (DriverOption->Attributes & LOAD_OPTION_FORCE_RECONNECT)!=0
        ) ReconnectAll=TRUE;
	}
	pBS->FreePool(DriverOption);
    pBS->FreePool(DriverOrder);
    if (ReconnectAll){
        DisconnectEverything();
        ConnectEverything();
    }
}

EFI_DEVICE_PATH_PROTOCOL* DiscoverPartition(
    IN EFI_DEVICE_PATH_PROTOCOL *DevicePath
){
    UINTN Count,i;
    EFI_HANDLE *Handle;
    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL *PartDevicePath=NULL;	
    HARDDRIVE_DEVICE_PATH* BootParitionDevicePath  = (HARDDRIVE_DEVICE_PATH*)DevicePath;
    //get list of available Block I/O devices    
    Status=pBS->LocateHandleBuffer(ByProtocol,&gEfiBlockIoProtocolGuid,NULL,&Count,&Handle);    
    if (EFI_ERROR(Status)) return NULL;

    for(i=0;i<Count;i++){
        EFI_BLOCK_IO_PROTOCOL *BlockIo;
        EFI_DEVICE_PATH_PROTOCOL *PartitionDevicePath;
        HARDDRIVE_DEVICE_PATH* PartitionNode;
        Status = pBS->HandleProtocol(Handle[i],&gEfiBlockIoProtocolGuid,&BlockIo);
        if (EFI_ERROR(Status)) continue;
        // if this is not partition, continue
        if (!BlockIo->Media->LogicalPartition) continue;
        Status = pBS->HandleProtocol(Handle[i],&gEfiDevicePathProtocolGuid,&PartitionDevicePath);
        if (EFI_ERROR(Status)) continue;
        // Get last node of the device path. It should be partition node
        PartitionNode = (HARDDRIVE_DEVICE_PATH*)DPGetLastNode(PartitionDevicePath);
        //Check if our partition matches Boot partition
        if (   PartitionNode->Header.Type!=MEDIA_DEVICE_PATH 
            || PartitionNode->Header.SubType!=MEDIA_HARDDRIVE_DP
        ) continue;
        if (   PartitionNode->PartitionNumber==BootParitionDevicePath->PartitionNumber 
            && PartitionNode->SignatureType==BootParitionDevicePath->SignatureType 
            && !MemCmp(PartitionNode->Signature,BootParitionDevicePath->Signature,16) 
        ){
            //Match found
			PartDevicePath = PartitionDevicePath;
            break;
        }
    }
    pBS->FreePool(Handle);
    return PartDevicePath;
}

EFI_STATUS FwLoadFile (
	IN EFI_LOAD_FILE_PROTOCOL *This, IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
	IN BOOLEAN BootPolicy, IN OUT UINTN *BufferSize,
	IN VOID *Buffer OPTIONAL
){
    EFI_GUID *FileGuid;
	UINTN FvCount,i;
	EFI_HANDLE *FvHandle;
    EFI_STATUS Status;

    if (!BufferSize || *BufferSize && !Buffer)
        return EFI_INVALID_PARAMETER;
    if (!FilePath || isEndNode(FilePath)){
        if (BootPolicy){
            if (DefaultAppFfsGuidPtr==NULL) return EFI_UNSUPPORTED;
            else FileGuid = DefaultAppFfsGuidPtr;
        }else{
            return EFI_INVALID_PARAMETER;
        }
    }else{
        if (   FilePath->Type!=MEDIA_DEVICE_PATH 
            || FilePath->SubType!=MEDIA_FV_FILEPATH_DP
        ) return EFI_INVALID_PARAMETER;
        FileGuid = &((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)FilePath)->NameGuid;
    }
    //If Buffer is NULL, ReadSection will allocate the memory.
    //That's not what we need.
    //Initialize Buffer with some value.
    //We don't care what value is that because *BufferSize is 0 anyway,
    //so nothing will be copied into the buffer.
    //We know that *BufferSize is always 0 for NULL buffer because we checked that
    //at the beginning of the routine.
    if (!Buffer) Buffer = (VOID*)1;
	Status=pBS->LocateHandleBuffer(ByProtocol, &gEfiFirmwareVolume2ProtocolGuid, NULL, &FvCount, &FvHandle);
	if (EFI_ERROR(Status)) return Status;
	Status=EFI_NOT_FOUND;
	for(i=0; i<FvCount; i++)
	{
	    EFI_FIRMWARE_VOLUME_PROTOCOL *Fv;
	    UINT32 AuthStatus;
        Status = pBS->HandleProtocol(FvHandle[i], &gEfiFirmwareVolume2ProtocolGuid, &Fv);
		if (EFI_ERROR(Status)) continue;
	    Status = Fv->ReadSection(
            Fv, FileGuid, EFI_SECTION_PE32, 
			0, &Buffer, BufferSize, &AuthStatus
		);
        if (!EFI_ERROR(Status)){
            if (Status==EFI_WARN_BUFFER_TOO_SMALL) Status=EFI_BUFFER_TOO_SMALL;
            break;
        }
	}
	pBS->FreePool(FvHandle);
	return Status;
}

VOID InstallFwLoadFile(){
    EFI_HANDLE Handle=NULL;
    pBS->InstallMultipleProtocolInterfaces(
        &Handle, 
        &gEfiLoadFileProtocolGuid, &FwLoadFileInterface,
        &gEfiDevicePathProtocolGuid, &FwLoadFileDp,
        NULL
    );
}

//----------------------------------------------------------------------------
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SignalProtocolEvent
//
// Description:	Internal function that installs/uninstall protocol
//				with a specified GUID and NULL interface.
//              Such protocols can be used as event signaling mechanism.
//
// Input:		ProtocolGuid Pointer to the protocol GUID
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SignalProtocolEvent(IN EFI_GUID *ProtocolGuid){
    EFI_HANDLE  Handle = NULL;
    pBS->InstallProtocolInterface (
        &Handle, ProtocolGuid, EFI_NATIVE_INTERFACE,NULL
    );
    pBS->UninstallProtocolInterface (
        Handle, ProtocolGuid, NULL
    );
}

#ifdef EFI_DXE_PERFORMANCE
VOID SavePerformanceData(IN EFI_EVENT Event, IN VOID *Context){
    PERF_END (0, BDS_TOK, NULL, 0) ;
    WriteBootToOsPerformanceData();
}
#endif

VOID SaveFpdtDataOnLegacyBoot(IN EFI_EVENT Event, IN VOID *Context){
    AmiFillFpdt (FillOsLoaderStartImageStart); // Fill OsLoaderStartImageStart field in FPDT
}

VOID SignalConnectDriversEvent(){
    PROGRESS_CODE(DXE_BDS_CONNECT_DRIVERS);
    SignalProtocolEvent(&BdsConnectDriversProtocolGuid);
}

VOID ConnectRootBridgeHandles(){
	EFI_HANDLE *Handle;
	UINTN NumberOfHandles;
    EFI_STATUS Status;
	UINTN i;

	//Enumerate PCI Bus and Create handles for all PCI devices
	Status = pBS->LocateHandleBuffer(
        ByProtocol,&gEfiPciRootBridgeIoProtocolGuid, NULL, 
        &NumberOfHandles, &Handle
    );
	if (EFI_ERROR(Status)) return;
	for(i=0; i<NumberOfHandles; i++) 
        pBS->ConnectController(Handle[i],NULL,NULL,FALSE);
	pBS->FreePool(Handle);	
}

VOID ReportConnectConOutProgressCode(){
    PROGRESS_CODE(DXE_CON_OUT_CONNECT);
}

VOID ConnectVgaConOut(){
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;
	EFI_DEVICE_PATH_PROTOCOL *OnBoard=NULL, *OffBoard=NULL;
    UINT64 PciAttributes;

	//Get a list of all PCI devices
	Status = pBS->LocateHandleBuffer(
        ByProtocol,&gEfiPciIoProtocolGuid, NULL, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return;
	for(i=0; i<Number; i++)
	{
		EFI_PCI_IO_PROTOCOL *PciIo;
		EFI_DEVICE_PATH_PROTOCOL *Dp;
		UINT8 PciClass;
		Status=pBS->HandleProtocol(Handle[i],&gEfiPciIoProtocolGuid,&PciIo);
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
        )  OnBoard = AddDevicePath(OnBoard,Dp);
		else OffBoard = AddDevicePath(OffBoard,Dp);
	}
	pBS->FreePool(Handle);
    //Offboard has a higher priority
	OffBoard = AddDevicePath(OffBoard,OnBoard);
	if (OffBoard)
	{
		ConnectDevicePath(OffBoard);
		pBS->FreePool(OffBoard);
	}
}

VOID ConnecConsoleVariable(CHAR16* ConVar){
    EFI_DEVICE_PATH_PROTOCOL *ConPath=NULL;
    UINTN Size = 0;

    if (EFI_ERROR(
        GetEfiVariable(ConVar, &EfiVariableGuid, NULL, &Size, &ConPath)
    )) return;

    //Connect all active console devices
    ConnectDevicePath(ConPath);
    pBS->FreePool(ConPath);
}

VOID InstallConsoleStartedProtocol(
    CHAR16* ConDevVar, EFI_GUID* ProtocolGuid
){
    UINTN Size = 0;
    VOID *Interface;

    //Signal to Console Splitter that all console devices have been started
    //if at least one console device exists (ConDev variable exists)
    if (ConDevVar!=NULL && pRS->GetVariable(
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

VOID ConnectConOutVariable(){
    ConnecConsoleVariable(L"ConOut");
}

VOID InstallConOutStartedProtocol(){
    InstallConsoleStartedProtocol(L"ConOutDev", &ConOutStartedProtocolGuid);
}

VOID ReportConnectConInProgressCode(){
    PROGRESS_CODE(DXE_CON_IN_CONNECT);
}

VOID ConnectPs2ConIn(){
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;

	//Get a list of all PCI to ISA Bridges
	Status = GetPciHandlesByClass(
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
		LpcHandle = Handle[i];
		LpcDevicePath = Dp;
	}
	pBS->FreePool(Handle);

}

VOID ConnectUsbConIn(){
	EFI_STATUS Status;
	EFI_HANDLE *Handle;
	UINTN Number,i;
	//Get a list of all USB Controllers
	Status = GetPciHandlesByClass(
        PCI_CL_SER_BUS, PCI_CL_SER_BUS_SCL_USB, &Number, &Handle
    );
	if (EFI_ERROR(Status)) return;
	for(i=0; i<Number; i++)
	{
        pBS->ConnectController(Handle[i],NULL,NULL,TRUE);
	}
	pBS->FreePool(Handle);
}

VOID ConnectConInVariable(){
    ConnecConsoleVariable(L"ConIn");
}

VOID InstallConInStartedProtocol(){
    InstallConsoleStartedProtocol(L"ConInDev", &ConInStartedProtocolGuid);
}

VOID ConInAvailabilityBeep(){
    LibReportStatusCode(EFI_PROGRESS_CODE, AMI_STATUS_CODE_BEEP_CLASS|1, 0, NULL, NULL);
}

VOID InitConVars()
{
	UINTN i;
	UINTN Size = 0;
    EFI_STATUS Status;
	EFI_DEVICE_PATH_PROTOCOL *ConPath=NULL;

    static CHAR16* ConVar[] = {L"ConOut", L"ConIn"};
    static CHAR16* ConDev[] = {L"ConOutDev", L"ConInDev"};

    // Install Console Stared Protocols
    // ConSplitter will process notification by populating 
    // corresponding fields of the system table.
    // At this point the protocol need to be installed 
    // even if no actual console devices are available
    // to prevent problems on headless systems 
    // caused by NULL console pointers in the system table.
    // The functions will not install the protocol if it has already been installed
    InstallConsoleStartedProtocol(NULL, &ConOutStartedProtocolGuid);
    InstallConsoleStartedProtocol(NULL, &ConInStartedProtocolGuid);

	//Create non-existent ConVar variables for ConIn and ConOut
	//ErrOut will be treated differently 
	for( i=0; i<2; i++){
		if (EFI_ERROR(
				GetEfiVariable(ConDev[i], &EfiVariableGuid, NULL, &Size, &ConPath)
			)
		) continue;
        //Set ConVar[i] equal to the ConDev[i]
		pRS->SetVariable(
			ConVar[i], &EfiVariableGuid,
			EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS, 
			Size, ConPath
		);
	}
	//Let's take care about ErrOut
    Status = GetEfiVariable(
        L"ErrOutDev", &EfiVariableGuid, NULL, &Size, &ConPath
    );
	if ( Status == EFI_NOT_FOUND ){
        Status = GetEfiVariable(
            L"ConOutDev", &EfiVariableGuid, NULL, &Size, &ConPath
        );
	    if (!EFI_ERROR(Status))
           	//Set ConErrDev equal to the ConOutDev
			pRS->SetVariable(
				L"ErrOutDev", &EfiVariableGuid,
				EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS, 
				Size, ConPath
			);
    }
	if (!EFI_ERROR(Status)){
        //Set ErrOut
		pRS->SetVariable(
		    L"ErrOut", &EfiVariableGuid,
            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS, 
            Size, ConPath
        );
    }
	if (ConPath) pBS->FreePool(ConPath);
}

#define IsRuntimeMemoryType(MemoryType) \
  ((MemoryType) == EfiACPIReclaimMemory   || \
   (MemoryType) == EfiACPIMemoryNVS       || \
   (MemoryType) == EfiRuntimeServicesCode || \
   (MemoryType) == EfiRuntimeServicesData || \
   (MemoryType) == EfiReservedMemoryType )

VOID SaveMemoryTypeInformation (
    IN EFI_EVENT Event, IN VOID *Context
){
#ifdef EFI_DEBUG
    CONST CHAR8* EfiMemTypeStr[] = {
    	"Reserved   ",
    	"LoaderCode ",
    	"LoaderData ",
    	"BSCode     ",
    	"BSData     ",
    	"RSCode     ",
    	"RSData     ",
    	"Free       ",
    	"Unusable   ",
    	"ACPIReclaim",
    	"ACPINVS    ",
    	"MMIO       ",
    	"MMIOIOPort ",
    	"PalCode    "
    };
    struct{
        UINT32 Previous,Current,Next;
    } MemoryInfoHistory[EfiMaxMemoryType];
#endif
    static EFI_GUID HobListGuid = HOB_LIST_GUID;
    EFI_STATUS Status;
    EFI_HOB_GUID_TYPE *MemoryInformationHob;
    EFI_MEMORY_TYPE_INFORMATION *MemoryTypeInformation = NULL;
    UINTN MemoryTypeInformationSize = 0;
    BOOLEAN IsFirstBoot = FALSE;
    EFI_MEMORY_TYPE_INFORMATION *CurrentMemoryTypeInformation;
    UINTN i, j;
    BOOLEAN MemoryTypeInformationModified;
    BOOLEAN RtMemoryQuotasIncreased = FALSE;
    UINT32 Current, Next;

    static BOOLEAN MemoryTypeInformationIsSaved = FALSE;

    // Make sure the processing is performed only once.
    // (we are registering callback on multiple events in RegisterMemoryTypeInformationUpdateCallback)
    if (MemoryTypeInformationIsSaved){
        pBS->CloseEvent(Event);
        return;
    }

    // Get the Memory Type Information settings from Hob if they exist,
    // PEI is responsible for getting them from variable and building a Hob to save them.
    MemoryInformationHob = GetEfiConfigurationTable(pST, &HobListGuid);
    if (MemoryInformationHob == NULL) return;
    if (EFI_ERROR(
        FindNextHobByGuid(&gEfiMemoryTypeInformationGuid, &MemoryInformationHob)
    )) return;

	Status = pRS->GetVariable(
        L"PreviousMemoryTypeInformation", &gEfiMemoryTypeInformationGuid, NULL, 
        &MemoryTypeInformationSize, NULL
    );
	IsFirstBoot = Status==EFI_NOT_FOUND;

    MemoryTypeInformation = (EFI_MEMORY_TYPE_INFORMATION*)(MemoryInformationHob+1);
    MemoryTypeInformationSize =   MemoryInformationHob->Header.HobLength 
                                - sizeof (EFI_HOB_GUID_TYPE);
    // Save memory information for the current boot.
    // It will be used if next boot is S4 resume.
    Status = pRS->SetVariable (
        L"PreviousMemoryTypeInformation", &gEfiMemoryTypeInformationGuid,
        EFI_VARIABLE_NON_VOLATILE  | EFI_VARIABLE_BOOTSERVICE_ACCESS,
        MemoryTypeInformationSize, MemoryTypeInformation
    );
    ASSERT_EFI_ERROR(Status);

    // Retrieve the current memory usage statistics.  If they are not found, then
    // no adjustments can be made to the Memory Type Information variable.
    CurrentMemoryTypeInformation = GetEfiConfigurationTable(
        pST, &gEfiMemoryTypeInformationGuid
    );
    if (CurrentMemoryTypeInformation == NULL) return;
    MemoryTypeInformationModified = FALSE;
    TRACE((TRACE_DXE_CORE, "BDS.%s(%X)\n", 
        "SaveMemoryTypeInformation", SaveMemoryTypeInformation
    ));
    // Adjust the Memory Type Information for the next boot
    for (i = 0; MemoryTypeInformation[i].Type != EfiMaxMemoryType; i++) {
        Current = 0;
        for (j = 0; CurrentMemoryTypeInformation[j].Type != EfiMaxMemoryType; j++) {
            if (MemoryTypeInformation[i].Type == CurrentMemoryTypeInformation[j].Type) {
                Current = CurrentMemoryTypeInformation[j].NumberOfPages;
                break;
            }
        }

        // Set next value to 125% of the current
        Next = Current + (Current >> 2);
#ifdef EFI_DEBUG
        MemoryInfoHistory[i].Previous = MemoryTypeInformation[i].NumberOfPages;
        MemoryInfoHistory[i].Current = Current;
        MemoryInfoHistory[i].Next = (Next > MemoryTypeInformation[i].NumberOfPages) ? Next : MemoryTypeInformation[i].NumberOfPages;
#endif
        // We are never decreasing the memory type usage values.
        // It would've been more fair to check for inequality (!=) here to 
        // keep memory type information consistent with the actual memory usage.
        // We are not doing it to workaround UEFI Windows 7 and Windows 8 bug. 
        // Windows loader can't properly handle (it crashes)
        // memory map changes that happen after OS load has been launched
        // and before the ExitBootServices call. 
        // It's very difficult to predict how much memory will be used during 
        // the execution of the Windows loader because in certain cases Windows loader 
        // is pretty active. For example, it sometimes calls 
        // ConnectController for all the devices.
        // By never decreasing the memory type usage values, we are avoiding the problem 
        // by always assuming the worst case scenario (the heaviest memory usage).
        // The drawback is, we are stealing more memory than is actually used from the user.
        if (Next > MemoryTypeInformation[i].NumberOfPages){
            if ( IsRuntimeMemoryType(MemoryTypeInformation[i].Type) )
                RtMemoryQuotasIncreased = TRUE;
            MemoryTypeInformation[i].NumberOfPages = Next;
            MemoryTypeInformationModified = TRUE;
        }
    }

    // If any changes were made to the Memory Type Information settings,
    // set the new variable value;
    if ( MemoryTypeInformationModified ){
        TRACE((TRACE_DXE_CORE, "   Memory    Previous  Current    Next   \n"));
        TRACE((TRACE_DXE_CORE, "    Type      Pages     Pages     Pages  \n"));
        TRACE((TRACE_DXE_CORE, "===========  ========  ========  ========\n"));
        for (i = 0; MemoryTypeInformation[i].Type != EfiMaxMemoryType; i++) {
            TRACE((
                TRACE_DXE_CORE, "%s %8X  %8X  %8X\n", 
                EfiMemTypeStr[MemoryTypeInformation[i].Type], 
                MemoryInfoHistory[i].Previous,
                MemoryInfoHistory[i].Current,
                MemoryInfoHistory[i].Next
            ));
        }
        Status = pRS->SetVariable(
            EFI_MEMORY_TYPE_INFORMATION_VARIABLE_NAME, &gEfiMemoryTypeInformationGuid,
            EFI_VARIABLE_NON_VOLATILE  | EFI_VARIABLE_BOOTSERVICE_ACCESS,
            MemoryTypeInformationSize, MemoryTypeInformation
        );
        ASSERT_EFI_ERROR(Status);
        if (IsFirstBoot && RtMemoryQuotasIncreased){
            TRACE(( 
                TRACE_DXE_CORE, 
                "Default RT memory quotas have been increased. Resetting the system...\n"
            ));
            pRS->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
        }
    }
    pBS->CloseEvent(Event);
    MemoryTypeInformationIsSaved = TRUE;
}

VOID RegisterMemoryTypeInformationUpdateCallback(){
	EFI_EVENT Event;
    VOID *Registration;
    
    EFI_BOOT_MODE BootMode = GetBootMode();
    if (   BootMode == BOOT_ON_S4_RESUME 
        || BootMode == BOOT_ON_FLASH_UPDATE
        || BootMode == BOOT_IN_RECOVERY_MODE
    ) return;
    
    // We really want to get control.
    // That's why we are registering callbacks for multiple boot events hoping that
    // at least one of them will be triggered.
    // If multiple events are signaled, only the first one is handled
    RegisterProtocolCallback(
        &BeforeBootProtocolGuid,
        SaveMemoryTypeInformation,
        NULL, &Event, &Registration
    );
    RegisterProtocolCallback(
        &BeforeLegacyBootProtocolGuid,
        SaveMemoryTypeInformation,
        NULL, &Event, &Registration
    );
    CreateLegacyBootEvent(TPL_CALLBACK, &SaveMemoryTypeInformation, NULL, &Event);
	pBS->CreateEvent(
        EVT_SIGNAL_EXIT_BOOT_SERVICES,TPL_CALLBACK, 
        &SaveMemoryTypeInformation, NULL, &Event
    );
}

VOID CallTheDispatcher(){
	DXE_SERVICES *pDxe;
    
    if (EFI_ERROR(LibGetDxeSvcTbl(&pDxe)))
        return;
	if (pDxe) pDxe->Dispatch();
}

VOID SignalAllDriversConnectedEvent(){
    SignalProtocolEvent(&BdsAllDriversConnectedProtocolGuid);
}

VOID HandoffToTse(){
    AMI_POST_MANAGER_PROTOCOL *AmiPostMgr=NULL;

    if (!EFI_ERROR(pBS->LocateProtocol(
            &AmiPostMgrProtocolGuid, NULL, &AmiPostMgr
    ))) AmiPostMgr->Handshake();

}

VOID BdsEntry (IN EFI_BDS_ARCH_PROTOCOL *This)
{
	
	UINTN i;

    PERF_END(0, DXE_TOK, NULL, 0);
    PERF_START(0, BDS_TOK, NULL, 0);
	InitParts2(TheImageHandle, pST);
    //Lang & LangCodes are initialized by Setup driver
	InitSystemVariable(L"Timeout",	sizeof(UINT16), &DefaultTimeout);

{
    EFI_EVENT Event;
    VOID      *Registration;
#ifdef EFI_DXE_PERFORMANCE
    RegisterProtocolCallback(
        &BeforeBootProtocolGuid,
        SavePerformanceData,
        NULL, &Event, &Registration
    );
    RegisterProtocolCallback(
        &BeforeLegacyBootProtocolGuid,
        SavePerformanceData,
        NULL, &Event, &Registration
    );

#endif
    RegisterProtocolCallback(
        &BeforeLegacyBootProtocolGuid,
        SaveFpdtDataOnLegacyBoot,
        NULL, &Event, &Registration
    );

}
	pBS->LocateHandleBuffer(AllHandles, NULL, NULL, &NumberOfHandles, &RootHandles);

	for(i=0; BdsControlFlowFunctions[i]!=NULL; i++){
        TRACE((TRACE_DXE_CORE, "BDS.%s(%X)\n", 
            BdsControlFlowFunctionNames[i], BdsControlFlowFunctions[i]
        ));
        BdsControlFlowFunctions[i]();
    }
}

// Deprecated Variable.
// Use TheImageHandle instead.
EFI_HANDLE ThisImageHandle = NULL;

EFI_STATUS BdsInit (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_HANDLE Handle = NULL;
	InitAmiLib(ImageHandle, SystemTable);
    ThisImageHandle = ImageHandle;
	return pBS->InstallProtocolInterface(&Handle, &gEfiBdsArchProtocolGuid, EFI_NATIVE_INTERFACE, &BDS);
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
