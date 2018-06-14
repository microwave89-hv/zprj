//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/usbport.c 80    10/28/16 3:57a Wilsonlee $
//
// $Revision: 80 $
//
// $Date: 10/28/16 3:57a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/usbport.c $
// 
// 80    10/28/16 3:57a Wilsonlee
// [TAG]  		EIP300142
// [Category]  	Improvement
// [Description]  	Remove USB Int1C module part because we use the other
// method to service xhci.
// [Files]  		usbport.c, amidef.h, amiusbhc.c, UsbLegacy.cif
// 
// 79    10/28/16 1:28a Wilsonlee
// [TAG]  		EIP300142
// [Category]  	Improvement
// [Description]  	Get vector value from memory 0x1c directly and check
// it's not zero.
// [Files]  		usbport.c, amidef.h
// 
// 78    2/18/16 10:05p Wilsonlee
// [TAG]  		EIP256089
// [Category]  	Improvement
// [Description]  	Add {0, 0, 0, 0, 0, 0} for the end of USB_SKIP_LIST
// structure in UsbGetSkipList function.
// [Files]  		usbport.c
// 
// 77    2/16/15 2:43a Wilsonlee
// [TAG]  		EIP205373
// [Category]  	Improvement
// [Description]  	Cppcheck errors in Usb module.
// [Files]  		usb.c, usbport.c, uhcd.c, usbCCID.c
// 
// 76    12/24/14 10:41p Wilsonlee
// [TAG]  		EIP196287
// [Category]  	Improvement
// [Description]  	Display info of connected usb controllers and remove or
// grayed-out some item according the connected usb controller number.
// [Files]  		uhcd.c, usbport.c, usb.uni, usb.sd, usbsetup.c,
// AmiUsbController.h, UsbPolicy.h
// 
// 75    11/24/14 12:13a Wilsonlee
// [TAG]  		EIP188680
// [Category]  	Improvement
// [Description]  	Add Genovation USB Mini-Terminal Model #904-RJ to
// UsbBadDeviceTable.
// [Files]  		usbport.c
// 
// 74    9/23/14 11:52p Wilsonlee
// [TAG]  		EIP185391
// [Category]  	Improvement
// [Description]  	Use 0xF to mask the port number for
// SKIP_FLAG_SKIP_MULTI_LEVEL function.
// [Files]  		usbport.c
// 
// 73    8/06/14 10:06p Wilsonlee
// [TAG]  		EIP180650
// [Category]  	Improvement
// [Description]  	Hide mass storage devices if "Usb Support" is disable.
// [Files]  		usbport.c, uhcd.c
// 
// 72    6/26/14 1:12a Wilsonlee
// [TAG]  		EIP173387
// [Category]  	Improvement
// [Description]  	Remove TODO comments.
// [Files]  		usbsetup.c, xhci.c, usbmass.c, usbCCID.c, usb.c, uhci.c,
// syskbc.c, usbport.c, usbbus.c, uhcd.c, UsbBotPeim.c, PeiXhci.c,
// PeiEhci.c
// 
// 71    6/11/14 8:22p Wilsonlee
// [TAG]  		EIP172625
// [Category]  	Improvement
// [Description]  	Usb skip table function adds the flag
// "SKIP_FLAG_SKIP_MULTI_LEVEL" that skips usb ports include down stream
// ports.
// [Files]  		usbport.c, AmiUsbController.h
// 
// 70    5/07/14 10:38a Wilsonlee
// [TAG]  		EIP166594
// [Category]  	Improvement
// [Description]  	Add the token "USB_SETUP_VARIABLE_RUNTIME_ACCESS" to
// control if we set runtime attribute for the setup variables used by USB
// module.
// [Files]  		usb.sdl, usbport.c, usbsetup.c
// 
// 69    7/03/13 4:06a Roberthsu
// [TAG]           EIP127455
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Skip table can not skip device
// [RootCause]     Because xhci root port over than 0xf.
// [Solution]      Check root port use another variable.
// [Files]         usbport.c
// 
// 68    6/26/13 3:37a Roberthsu
// [TAG]           EIP125792
// [Category]      Bug Fix
// [Severity:]     Normal
// [Symptom:]      Keep function not work
// [Root Cause]    When check port change. We can not get baseclass.
// [Solution]      Add Vaild base class flag.
// [Files]         UsbPort.c,Usb.c
// 
// 67    3/19/13 3:54a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 66    3/18/13 4:46a Ryanchou
// [TAG]  		EIP98377
// [Category]  	Improvement
// [Description]  	Optimize USB controller timing.
// [Files]  		usb.sdl, usbport.c, ehci.c, elib.c, ohci.c, uhci.c,
// usbdef.h, usbhub.c, xhci.c, uhcd.c
// 
// 65    1/22/13 2:40a Wilsonlee
// [TAG]  		EIP110305
// [Category]  	Improvement
// [Description]  	Set the device address after we send the first
// get-device-descriptor command.
// [Files]  		usbmass.c, usb.c, usbdef.h, usbbus.c, efiusbmass.c, uhcd.c,
// usbport.c
// 
// 64    1/11/13 4:13a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 63    12/21/12 5:01a Ryanchou
// [TAG]  		EIP71730
// [Category]  	New Feature
// [Description]  	Added OHCI handoff support.
// [Files]  		usb.sdl, usbport.c, amiusb.c, usbdef.h, UsbPolicy.h, usb.sd,
// usb.uni
// 
// 62    12/19/12 2:51a Roberthsu
// Correct comment.
// 
// 61    12/19/12 2:35a Roberthsu
// [TAG]           EIP107664
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Usb skip table no function
// [RootCause]     HubDeviceNumber and PortNumber fail.
// [Solution]      Restore bHubDeviceNumber and bHubPortNumber.
// [Files]         usbport.c
// 
// 60    9/13/12 1:41a Ryanchou
// Fix compile error with x64_BUILD = 0.
// 
// 59    9/04/12 8:06a Wilsonlee
// [TAG]  		EIP99882
// [Category]  	New Feature
// [Description]  	Add the usb setup item and usbpolicyprotocol to enable
// or disable the usb mass storage driver.
// [Files]  		UsbPolicy.h, usb.uni, usb.sd, usbmass.c, usbdef.h,
// efiusbmass.c, usbport.c, uhcd.c
// 
// 58    9/03/12 5:25a Roberthsu
// [TAG]           EIP88776
// [Category]      Improvement
// [Description]   Implement keep port function.
// [Files]         usbport.c,AmiUsbController.h
// 
// 57    8/29/12 8:06a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 56    5/04/12 6:36a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 55    5/03/12 5:06a Ryanchou
// [TAG]  		EIP83361
// [Category]  	New Feature
// [Description]  	Added "USB 2.0 Controller Mode" setup item.
// [Files]  		ehci.c, usb.sd, usb.sdl, usb.uni, usbdef.h, UsbPolicy.h,
// usbport.c
// 
// 54    5/02/12 8:11a Wilsonlee
// [TAG]  		EIP86793
// [Category]  	New Feature
// [Description]  	Add the SDL token "USB_MASS_EMULATION_FOR_NO_MEDIA" for
// determine the USB mass storage device emulation type without media.
// [Files]  		usbmass.c, usbport.c, uhcd.c, usbdef.h, usbsrc.sdl
// 
// 53    4/05/12 10:54a Ryanchou
// [TAG]  		EIP74685
// [Category]  	New Feature
// [Description]  	Add a token "USB_BAD_DEVICES" that is used to list the
// bad devices for OEM.
// [Files]  		usb.sdl, usbport.c
// 
// 52    1/14/12 6:40a Wilsonlee
// [TAG]  		EIP80382
// [Category]  	New Feature
// [Description]  	Add the SDL token "USB_MASS_EMULATION_BY_SIZE" for
// determine the USB mass storage device emulation type by size only.
// [Files]  		usbmass.c, usbport.c, uhcd.c, usbdef.h,  usbsrc.sdl
// 
// 51    1/06/12 1:03a Rajeshms
// [TAG]  		EIP62737
// [Category]  	Improvement
// [Description]  	Added USB Device number into USB mass device name
// string based on SDL Token.
// [Files]  		Usb.sdl, usbport.c, usbmass.c, UsbInt13.h, UsbInt13.c,
// usbbus.c, Bfiusb.equ
// 
// 50    12/26/11 2:32a Roberthsu
// Correct checkin comment.
// 
// 49    12/26/11 2:21a Roberthsu
// [TAG]           EIP74609
// [Category]      Improvement
// [Description]   Add check oemskiplist at check port change.
// [Files]         usbport.c,usb.c,AmiUsbController.h
// 
// 48    12/08/11 1:44a Ryanchou
// [TAG]  		EIP75441
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hangs at 0xB4 after restart from Win7
// [RootCause]  	The device does not use standard BOT protocol under
// Windows.
// [Solution]  	Add the device into bad device table.
// [Files]  		usb.c usbport.c
// 
// 47    11/16/11 3:18a Ryanchou
// [TAG] EIP70094
// [Category] Improvement
// [Description] Microsoft CSM Opt-Out feature implementation.
// [Files] amiusb.c, uhcd.c, usbport.c
// 
// 46    11/05/11 7:34a Wilsonlee
// [TAG]  		EIP64781
// [Category]  	New Feature
// [Description]  	Added SDL token
// SKIP_CARD_READER_CONNECT_BEEP_IF_NO_MEDIA that skip the connect beep if
// no media present in USB card reader.
// [Files]  		usbport.c, usbmass.c, usb.c, usbdef.h, uhcd.c usbsrc.sdl
// 
// 45    10/17/11 2:23a Ryanchou
// [TAG]  		EIP69136
// [Category]  	Improvement
// [Description]  	Remove the dependency of EBDA in USB module for CSM
// disabling.
// [Files]  		amiusb.c, uhcd.c, usbport.c, usbsb.c
// 
// 44    9/28/11 10:46a Ryanchou
// [TAG]  		EIP66064
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System hangs when waiting for finger swipe
// [RootCause]  	USB driver save the URP pointer to EBDA in function
// UsbSmiCore and UsbSmiHc, the pointer will be destroyed if someone also
// invoke the two functions.
// [Solution]  	Save the URP pointer before generate SW SMI and restore it
// after return from SMI.
// [Files]  		amiusb.c, amiusbhc.c, usbport.c
// 
// 43    8/08/11 5:14a Ryanchou
// [TAG]  		EIP60561
// [Category]  	New Feature
// [Description]  	Add USB timing policy protocol for timing override.
// [Files]  		ehci.c, guids.c, ohci.c, uhcd.c, uhci.c usb.c, usbdef.h,
// usbhub.c, usbmass.c, UsbPolicy.h, usbport.c usbsrc.sdl
// 
// 42    8/05/11 6:17a Ryanchou
// [TAG]  		EIP60706
// [Category]  	Improvement
// [Description]  	Move gUsbBadDeviceTable into SMRAM.
// [Files]  		usbport.c, amiusb.c, usb.c, uhcd.c, AmiUsbController.h
// 
// 41    6/22/11 2:14a Ryanchou
// [TAG] EIP62695
// [Improvement] Add new oemskiplist function
// [Description] Add skip function by controller or port.Skip by device
// type or port number.
// 
// 40    4/13/11 12:47a Ryanchou
// [TAG]  		EIP58029 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hangs when insert USB devices
// [RootCause]  	The function OEMSkipList uses LocateProtocol to get USB
// global data pointer, uses Boot Services in runtime may cause system
// hang.
// [Solution]  	Extern usb global data pointer.
// [Files]  		usbport.c
// 
// 39    4/06/11 12:52a Ryanchou
// [TAG]  		EIP51653
// [Category]  	New Feature
// [Description]  	Added an interface that skips specific port
// enumeration.
// [Files]  		AmiUsbController.h, uhcd.c, uhcd.h, usb.c, usbdef.h,
// usbport.c
// 
// 38    3/29/11 10:05a Ryanchou
// [TAG]  		EIP53518
// [Category]  	Improvement
// [Description]  	Added chipset xHCI chip support.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhcd.c, uhci.c, usb.c,
// usb.sdl, usbdef.h, usbport, usbsb.c, xhci.c
// 
// 37    10/29/10 5:33a Ryanchou
// EIP46992: USB module build failed with WDK after apply EIP44570.
// 
// 36    10/22/10 8:56a Ryanchou
// EIP46693: Clear xHCI BIOS owned semaphore bit and SMI enable bit in
// PreInitXhci.
// 
// 35    10/21/10 8:56a Ryanchou
// EIP44570: Added multiple xHCI SMI pin support. 
// 
// 34    10/12/10 4:52a Rameshr
// [TAG]- EIP 44585
// [Category]-IMPROVEMENT
// [Description]- Number of maximum supported USB Mass Storage device
// increased from 8 to 16. 
// [Files]- Uin13.bin, UsbPort.c, UsbInt13.h, Usb.c, Usbdef.h, Uasbmass.c,
// Usb.sd, usb.uni, UsbSetup.c, UsbSrc.sdl, UsbPolicy.h
// 
// 33    10/12/10 2:05a Rameshr
// [TAG]- EIP 44585
// [Category]-IMPROVEMENT
// [Description]- Number of maximum supported USB Mass Storage device
// increased from 8 to 16. 
// [Files]- Uin13.bin, UsbPort.c, UsbInt13.h, Usb.c, Usbdef.h, Uasbmass.c,
// Usb.sd, usb.uni, UsbSetup.c, UsbSrc.sdl, UsbPolicy.h
// 
// 32    9/16/10 1:09p Olegi
// 
// 31    8/31/10 8:52a Tonylo
// EIP41544 - Add EntronTech XHCI support.
// 
// 30    7/13/10 7:03a Ryanchou
// EIP38356: Implement shutdown USB legacy support in ACPI enable call.
// 
// 29    6/23/10 10:18a Olegi
// 
// 28    6/22/10 9:15p Olegi
// EIP39708: added incompatible mouse "SANWA Supply MA-LS11DS USB Mouse"
// 
// 27    6/15/10 1:25a Ryanchou
// Implement xHCI USB Legacy Capability.
// 
// 26    6/10/10 10:45p Ryanchou
// Remove SMSC USB Floppy in gUsbBadDeviceTable.
// 
// 25    5/20/10 11:56a Olegi
// 
// 24    5/19/10 4:01p Olegi
// 
// 23    4/19/10 1:54p Olegi
// 
// 22    4/12/10 12:20p Olegi
// Moving structure definitions to the .H file. EIP36942
// 
// 21    4/02/10 10:09a Olegi
// 
// 20    4/02/10 8:57a Olegi
// 
// 19    12/10/09 10:10a Olegi
// Added UsbControlTimeout setup selection. EIP30079.
// 
// 18    11/23/09 3:28p Olegi
// Fix for EIP30023: access gSetupData only when GetVariable returns
// EFI_SUCCESS.
// 
// 17    11/13/09 9:11a Olegi
// EIP31023: key repeat rates are defined by SDL tokens.
// 
// 16    10/30/09 5:48p Olegi
// 
// 15    10/09/09 5:56p Olegi
// 
// 14    10/06/09 6:19p Olegi
// 
// 13    5/21/09 5:10p Olegi
// Added HDD hotplug support.
// 
// 12    3/26/09 2:17p Olegi
// All setup related code is moved to OEMPORT.C to maximize the porting
// capabilities.
// 
// 11    2/27/09 10:27a Olegi
// 
// 10    2/18/09 3:45p Olegi
// Added a feature that allows to skip mass storage device installation
// depending on physical media presence. EIP#19260.
// 
// 9     11/25/08 6:03p Olegi
// Support for OEM USB Boot Override feature. EIP#17052.
// 
// 8     7/04/08 1:06p Olegi
// NATIVE emulation option EIP 14317
// 
// 7     5/16/08 12:00p Olegi
// Compliance with AMI coding standard.
//
// 6     2/06/08 11:44a Olegi
// Added UpdateHCPCIInfo function.
//
// 5     12/17/07 4:03p Olegi
// Removed kbc_support variable.
//
// 4     5/22/07 1:20p Yakovlevs
// Added code to initialize kbc_support variable if KBC_SUPPORT token is
// undefined
//
// 3     11/10/05 11:10a Olegi
//
// 2     8/04/05 5:57p Andriyn
// Legacy over LegacyFree
//
// 1     3/29/05 10:16a Olegi
//
//****************************************************************************
//
//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:   USBPORT.C
//
//  Description:    AMI USB Porting file
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

//****************************************************************************

#include "Efi.h"
#include "token.h"
#include "Setup.h"
#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"

#if defined(CSM_SUPPORT) && CSM_SUPPORT		//(EIP69136+)
#include <Protocol\LegacyBiosExt.h>
#endif										//(EIP69136+)

#if USB_DIFFERENTIATE_IDENTICAL_DEVICE_NAME
static UINT8   DeviceNumber=1;
#endif

#if  USB_RT_DRIVER
//-----------------------------------------------------------------------------
// This part is linked with USBRT and located in SMI

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:        USBBadDeviceTable
//
// Description: This table contains list of vendor & device IDs of USB
//              devices that are non-compliant. This is currently used
//              only for USB mass storage devices but can be extended to
//              other type of non-compliant devices also.
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>

USB_BADDEV_STRUC    gUsbBadDeviceTable[] = {
// Intel, Lacie hard disk
    {0x059f, 0xa601,
        0, 0, PROTOCOL_CBI_NO_INT,
        0},

// In-systems ATA bridge
    {0x05ab, 0x0060,
        0, 0, 0,
        USB_INCMPT_START_UNIT_NOT_SUPPORTED},

// Data Store Technologies, USB 2 ATA bridge
    {0x04e6, 0x0001,
        BASE_CLASS_MASS_STORAGE, 0, PROTOCOL_CBI_NO_INT,
        USB_INCMPT_BOT_STATUS_FAILED},

// NEC, Floppy drive
    {0x0409, 0x0040,
        0, 0, PROTOCOL_CBI_NO_INT,
        0},

// Hana flash drive
    {0x090a, 0x1001,
        0, 0, 0, \
        USB_INCMPT_SINGLE_LUN_DEVICE +
        USB_INCMPT_MODE_SENSE_NOT_SUPPORTED},

// Compact Flash reader
    {0x04e6, 0x000a,
        0, 0, 0,
        USB_INCMPT_MODE_SENSE_NOT_SUPPORTED},

// ScanLogic SL11R-IDE and Ennyah RW4420U
    {0x04ce, 0x0002,
        0, SUB_CLASS_SL11R, PROTOCOL_BOT,
        0},

// BAFO Slim CDR-W BF-2100
    {0x09cc, 0x0404,
        0, 0, PROTOCOL_CBI,
        0},

//Panasonic USB CD/RW Model:KXL-RW21AN
    {0x04da, 0x0d06,
        BASE_CLASS_MASS_STORAGE, 0, PROTOCOL_CBI,
        0},

    {0x04da, 0x0d07,
        BASE_CLASS_MASS_STORAGE, 0, PROTOCOL_CBI,
        0},

//TaiDen Technology:CoolFlash
    {0x0ea0, 0x6803,
        0, 0, 0,
        USB_INCMPT_MODE_SENSE_NOT_SUPPORTED},

// A-Bit USB Mouse(Model:97M32U)
    {0x0605, 0x0001,
        0, 0, 0,
        USB_INCMPT_SET_BOOT_PROTOCOL_NOT_SUPPORTED},

// The problem with this card reader is fixed elsewhere
// HP 4-in-1 Card reader (does not support Read Format Capacity command)
//  {0x6050, 0x0034,
//      0, 0, 0,
//      USB_INCMPT_FORMAT_CAPACITY_NOT_SUPPORTED},

// Silicon Motion Inc., Taiwan: USB Flash Disk
    {0x090c, 0x1000,
        0, 0, 0,
        USB_INCMPT_GETMAXLUN_NOT_SUPPORTED},

//Intel KVM HID
    {0x8086, 0x2b,
        0, 0, 0,
        USB_INCMPT_HID_DATA_OVERFLOW},

// SANWA Supply MA-LS11DS USB Mouse
    {0x04fc, 0x0801,
        0, 0, 0,
        USB_INCMPT_BOOT_PROTOCOL_IGNORED},
										//(EIP75441+)>
// SanDisk 2GB Sansa Clip+ MP3 Player
	{0x0781, 0x74D0,
		0xFF, 0xFF, 0xFF,
		0},

// SanDisk Sansa Fuze 4GB Flash Portable Media Player
	{0x0781, 0x74C2,
		0xFF, 0xFF, 0xFF,
		0},
										//<(EIP75441+)
// Genovation USB Mini-Terminal Model #904-RJ
    {0x16C0, 0x0604,
        0, 0, 0,
        USB_INCMPT_DISABLE_DEVICE},
#ifdef USB_BAD_DEVICES
	USB_BAD_DEVICES
#endif
// End of incompatible device list
    {0, 0, 0, 0, 0, 0}
};

UINT16 gKbcSetTypeRate11CharsSec=KEY_REPEAT_DELAY;
UINT16 gKbcSetTypeDelay500MSec=KEY_REPEAT_INITIAL_DELAY;
extern  USB_GLOBAL_DATA  *gUsbData;  //EIP58029

DEV_INFO*   USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        OEMSkipList
//
// Description:	This function intends to skip port.
//  
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END> 

BOOLEAN 
OEMSkipList (
    UINT8       HubAddr,
    UINT8       PortNum, 	
	UINT16      Bdf,
	UINT8       BaseClass,
    UINT8       VaildBaseClass
)
{
                                        //(EIP88776+)>
    USB_SKIP_LIST   *UsbSkipListTable;
    DEV_INFO        *TmpDevInfo;
    UINT8           TablePortNumber; 
    UINT8           ConnectDeviceNumber;
	UINT8           ConnectPortNumber;	
    UINT16          i; 
    UINT16          TableLevel; 
    UINT16          ConnectLevel;
    UINT32          TablePath; 
    UINT32          ConnectPath;
    UINT32          ConnectPathMask;
 
    UsbSkipListTable = (USB_SKIP_LIST*) gUsbData->gUsbSkipListTable;

    if (UsbSkipListTable == NULL) {
        return FALSE;
    }
	
    for ( ; (UsbSkipListTable->wBDF != 0); UsbSkipListTable++) {
        TablePortNumber = UsbSkipListTable->bRootPort;
        TablePath = UsbSkipListTable->dRoutePath;
        for (i = 1; i < 5; i++, TablePath >>= 4) {
            if (TablePath == 0) {
                break;
            }
		}

        TablePath = UsbSkipListTable->dRoutePath;
        TableLevel = i;
        USB_DEBUG(4, "TableLevel = %x TablePath = %x TablePortNumber = %x BDF = %x\n",
                TableLevel,TablePath,TablePortNumber, UsbSkipListTable->wBDF);

        //get connect path and level
        ConnectDeviceNumber = HubAddr; 
        ConnectPortNumber = PortNum;		
        for (i = 1, ConnectPath = 0; i < 5; i++) {	
            if (ConnectDeviceNumber & BIT7) {
                break;
            }
            ConnectPath = ConnectPath << 4; 
            ConnectPath |= ConnectPortNumber;

            // Get the device info structure for the matching device address
            TmpDevInfo = USB_GetDeviceInfoStruc(
                                        USB_SRCH_DEV_ADDR, 
                                        0, 
                                        ConnectDeviceNumber, 
                                        0);
            if (TmpDevInfo == NULL) {
                break;
            }
            ConnectDeviceNumber = TmpDevInfo->bHubDeviceNumber;
            ConnectPortNumber   = TmpDevInfo->bHubPortNumber;             
        }
        ConnectLevel = i; 
        USB_DEBUG(4, "ConnectLevel = %x ConnectPath = %x ConnectPortNumber = %x BDF = %x\n",
                    ConnectLevel, ConnectPath, ConnectPortNumber, Bdf);

        //Skip by all 
        if (UsbSkipListTable->bSkipType == SKIP_FOR_ALLCONTROLLER) {
            if (UsbSkipListTable->bFlag == SKIP_FLAG_SKIP_LEVEL) {
                if (TableLevel != ConnectLevel) {
                    continue;
                }
            }
			
            if (UsbSkipListTable->bBaseClass == 0) {
                return TRUE;
            }
			
            if (UsbSkipListTable->bBaseClass == BaseClass) {
                return TRUE;
            }
			
			continue;
		}

        if (UsbSkipListTable->wBDF != Bdf) {
            continue;
        }

        //Skip by controller
        if (UsbSkipListTable->bRootPort == 0) {
            if (UsbSkipListTable->bBaseClass != 0) {         
                if (UsbSkipListTable->bBaseClass != BaseClass) {
                    continue;
                } else {
                    return TRUE;                    
                }
            }
            return TRUE;                                
        }
        //Skip usb ports which include down stream ports.
        if (UsbSkipListTable->bFlag == SKIP_FLAG_SKIP_MULTI_LEVEL) {
            ConnectPathMask = 0xFFFFFFFF >> (4 * (8 - (TableLevel)));
            ConnectPathMask = ConnectPathMask >> 4;
            if (((ConnectPath & ConnectPathMask) == TablePath) && (ConnectPortNumber == TablePortNumber)){
                if (UsbSkipListTable->bBaseClass != 0) {
                    if (UsbSkipListTable->bBaseClass == BaseClass) {
                        return TRUE;
                    }
                    continue;
                }
                return TRUE;
            }
            continue;
        }
        
        if (TableLevel != ConnectLevel) {
            continue;
        }
		//Skip usb ports on the same level.
        if (UsbSkipListTable->bFlag == SKIP_FLAG_SKIP_LEVEL) {
            if (UsbSkipListTable->bBaseClass == 0) {
                return TRUE;
            }
			
            if (UsbSkipListTable->bBaseClass == BaseClass) {
                return TRUE;
            }
        }
        for (i = 0; i < TableLevel; i++, ConnectPath >>= 4, TablePath >>= 4) {
            if (i == (TableLevel - 1)) { 
                switch (UsbSkipListTable->bFlag) {
                    case SKIP_FLAG_SKIP_PORT:
                        if ((ConnectPath == TablePath) && (ConnectPortNumber == TablePortNumber)){
                            if (UsbSkipListTable->bBaseClass != 0) {
                                if (UsbSkipListTable->bBaseClass == BaseClass) {
                                    return TRUE;
                                }
                                break;
                            }
                            return TRUE;
                        }
                        break;						
                    case SKIP_FLAG_KEEP_PORT:
                        if (ConnectPortNumber == TablePortNumber) {
                            if (ConnectPath == TablePath) {
                                if (UsbSkipListTable->bBaseClass != 0) {
                                    if (VaildBaseClass == 1) {
                                        if (UsbSkipListTable->bBaseClass != BaseClass) {
                                            return TRUE;
                                        }
                                    }
                                }
                                break;                                
                            }
                            return TRUE;
                        }
                        break;
                    default:
                        break;
                }                
            } else {
                if ((ConnectPath & 0xf) != (TablePath & 0xf)) {
                    break;
                }
            }
        }
    }
	
    return FALSE;
                                        //<(EIP88776+)
}
 
// End of SMI part of USBPORT.C
//-----------------------------------------------------------------------------
#else
//-----------------------------------------------------------------------------
// This part is linked with UHCD and located outside SMI
extern  USB_GLOBAL_DATA  *gUsbData;  //EIP58029
extern  EFI_GUID gEfiSetupGuid;

UINT8 gFddHotplugSupport = USB_HOTPLUG_FDD;
UINT8 gHddHotplugSupport = USB_HOTPLUG_HDD;
UINT8 gCdromHotplugSupport = USB_HOTPLUG_CDROM;
UINT8 gUsbMassNativeEmulation = USB_MASS_EMULATION_NATIVE;
UINT8 UsbMassEmulationForNoMedia = USB_MASS_EMULATION_FOR_NO_MEDIA;	//(EIP86793+)
                                        //(EIP80382+)>
#ifndef USB_MASS_EMULATION_BY_SIZE
#define USB_MASS_EMULATION_BY_SIZE 0
#endif
UINT8 UsbMassSizeEmulation = USB_MASS_EMULATION_BY_SIZE;
                                        //<(EIP80382+)
#ifndef REMOVE_CHECK_FOR_USB_FLOPPY_DRIVE
#define REMOVE_CHECK_FOR_USB_FLOPPY_DRIVE 0
#endif
UINT8 gUsbMassMediaCheck = REMOVE_USB_STORAGE_FROM_BBS_IF_NO_MEDIA;
UINT8 gUsbMassSkipFddMediaCheck = REMOVE_CHECK_FOR_USB_FLOPPY_DRIVE;
UINT8 gUsbEfiMsDirectAccess = USB_EFIMS_DIRECT_ACCESS;
UINT8 SkipCardReaderConnectBeep = SKIP_CARD_READER_CONNECT_BEEP_IF_NO_MEDIA;    //(EIP64781+)

//USB_SUPPORT_SETUP           gSetupData;					//(EIP99882-)

//(EIP51653+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbGetSkipList
//
// Description: This function returns a name string of connected mass storage
//              device.
//
// Input:       SkipStruc - Pointer to a skip list to be filled
//              TotalStruc - Size of the data to copy to a buffer
// Output:      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbGetSkipList(
    USB_SKIP_LIST	*SkipStruc,
    UINT8			TotalStruc
)
{
	EFI_STATUS  Status;

	Status = pBS->AllocatePool(
			EfiRuntimeServicesData,
			(TotalStruc + 1) * sizeof(USB_SKIP_LIST),
			&(gUsbData->gUsbSkipListTable));

    if (EFI_ERROR(Status)) {
        return;
    }

    pBS->SetMem(gUsbData->gUsbSkipListTable, (TotalStruc + 1) * sizeof(USB_SKIP_LIST), 0);
	pBS->CopyMem(gUsbData->gUsbSkipListTable,SkipStruc, TotalStruc*sizeof(USB_SKIP_LIST));

	return;
}
//<(EIP51653+) 

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UpdateHcPciInfo
//
// Description: This function is called from the UHCD entry point, HcPciInfo
//              can be updated here depending on the platform and/or chipset
//              requirements.
//
// Input:       None
//
// Output:      EFI_STATUS - Updating succeeded / failed
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateHcPciInfo()
{
    return EFI_UNSUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    OemGetAssignedUsbBootPort
//
// Description: This procedure return specific USB host controller index and
//              port number for BIOS to give specific mass storage device
//              have highest boot priority.
//
// Input: 	None
//
// Output:
//          EFI_SUCCESS         USB boot device assigned
//              UsbHcIndx       USB host index (1-based)
//              UsbHubPortIndx  USB hub port index (1-based)
//          EFI_UNSUPPORTED     No USB boot device assigned
//          EFI_INVALID_PARAMETER   UsbHcIndx or UsbHubPortIndx are NULL
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
OemGetAssignUsbBootPort (
    UINT8   *UsbHcIndx,
    UINT8   *UsbHubPortIndx
)
{
    if (UsbHcIndx == NULL || UsbHubPortIndx == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }
/*
    // The code below is the sample implementation that reports Port#3 of HC#7
    // to be a port of boot priority device
    *UsbHcIndx = 7;
    *UsbHubPortIndx = 3;

    return EFI_SUCCESS;
*/
    return EFI_UNSUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    InitUsbSetupVars
//
// Description: This is porting function that fills in USB related fields in
//              gSetupData variable according to the setup settings and OEM
//              policy.
//
// Input: 	    Pointers to USB data, Boot Services and Runtime Services
//
// Output:      The status of gSetupData initialization
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitUsbSetupVars (
    USB_GLOBAL_DATA         *UsbData,
    EFI_BOOT_SERVICES       *pBS,
    EFI_RUNTIME_SERVICES    *pRS
)
{

    UINTN               VariableSize;
    USB_MASS_DEV_NUM    MassDevNum;
    EFI_STATUS          Status;
    UINT8               Index;
    USB_MASS_DEV_VALID  MassDevValid= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    UINT32              VariableAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    USB_CONTROLLER_NUM  UsbControllerNum;

#if USB_SETUP_VARIABLE_RUNTIME_ACCESS
    VariableAttributes |= EFI_VARIABLE_RUNTIME_ACCESS;
#endif

    UsbControllerNum.UhciNum = 0;
    UsbControllerNum.OhciNum = 0;
    UsbControllerNum.EhciNum = 0;
    UsbControllerNum.XhciNum = 0;
    VariableSize = sizeof(UsbControllerNum);
    
    Status = pRS->SetVariable(L"UsbControllerNum",
        &gEfiSetupGuid,
        VariableAttributes,
        VariableSize,
        &UsbControllerNum);

    MassDevNum.UsbMassDevNum = 0;
    MassDevNum.IsInteractionAllowed = 1;
    VariableSize = sizeof(MassDevNum);

    Status = pRS->SetVariable(L"UsbMassDevNum",
        &gEfiSetupGuid,
        VariableAttributes,
        VariableSize,
        &MassDevNum);

    //
    // Initilize the Variable to 0
    //        
    VariableSize = sizeof(MassDevValid);
    Status = pRS->SetVariable( L"UsbMassDevValid",
        &gEfiSetupGuid,
        VariableAttributes,
        VariableSize,
        &MassDevValid );

    if (UsbData == NULL) {
        return EFI_SUCCESS;
    }

    VariableSize = sizeof(USB_SUPPORT_SETUP);
    Status = pRS->GetVariable( L"UsbSupport", &gEfiSetupGuid, NULL,
                        &VariableSize, &UsbData->UsbSetupData);
    if (EFI_ERROR(Status)) {
        // Set default values and save "UsbSupport" variable.
        pBS->SetMem(&UsbData->UsbSetupData, sizeof(UsbData->UsbSetupData), 0);

		UsbData->UsbSetupData.UsbMainSupport = 1;

        if (gFddHotplugSupport) {
            UsbData->UsbSetupData.UsbHotplugFddSupport = SETUP_DATA_HOTPLUG_AUTO;
        }
        if (gHddHotplugSupport) {
            UsbData->UsbSetupData.UsbHotplugHddSupport = SETUP_DATA_HOTPLUG_AUTO;
        }
        if (gCdromHotplugSupport) {
            UsbData->UsbSetupData.UsbHotplugCdromSupport = SETUP_DATA_HOTPLUG_AUTO;
        }

        UsbData->UsbSetupData.UsbMassResetDelay = SETUP_DATA_RESETDELAY_20S;
        UsbData->UsbSetupData.UsbControlTimeOut = 20;      //(EIP30079+)
		UsbData->UsbSetupData.UsbXhciSupport = 1;
		UsbData->UsbSetupData.UsbHiSpeedSupport = 1;
        UsbData->UsbSetupData.UsbMassDriverSupport = 1;

        VariableAttributes |= EFI_VARIABLE_NON_VOLATILE;

        Status = pRS->SetVariable(
                    L"UsbSupport",
                    &gEfiSetupGuid,
                    VariableAttributes,
                    sizeof(UsbData->UsbSetupData),
                    &UsbData->UsbSetupData );
    }

    if (gFddHotplugSupport) {
        UsbData->fdd_hotplug_support = UsbData->UsbSetupData.UsbHotplugFddSupport;
    }
    if (gHddHotplugSupport) {
        UsbData->hdd_hotplug_support = UsbData->UsbSetupData.UsbHotplugHddSupport;
    }
    if (gCdromHotplugSupport) {
        UsbData->cdrom_hotplug_support = UsbData->UsbSetupData.UsbHotplugCdromSupport;
    }
	UsbData->UsbXhciHandoff = UsbData->UsbSetupData.UsbXhciHandoff;
    UsbData->UsbEhciHandoff = UsbData->UsbSetupData.UsbEhciHandoff;
    UsbData->UsbOhciHandoff = UsbData->UsbSetupData.UsbOhciHandoff;
    UsbData->UsbEmul6064 = UsbData->UsbSetupData.UsbEmul6064;
    UsbData->UsbMassResetDelay = UsbData->UsbSetupData.UsbMassResetDelay;
    for (Index=0; Index<16; Index++) {
        UsbData->USBMassEmulationOptionTable[Index] =
                        *((UINT8*)&UsbData->UsbSetupData.UsbEmu1+Index);
    }
    if (UsbData->UsbSetupData.UsbLegacySupport == 1) {
        UsbData->dUSBStateFlag |= USB_FLAG_DISABLE_LEGACY_SUPPORT;
    }
    UsbData->wTimeOutValue = UsbData->UsbSetupData.UsbControlTimeOut*1000 ;   //(EIP30079+)
	UsbData->UsbXhciSupport = UsbData->UsbSetupData.UsbXhciSupport;
	UsbData->UsbHiSpeedSupport = UsbData->UsbSetupData.UsbHiSpeedSupport;

    UsbData->PowerGoodDeviceDelay =
        (UsbData->UsbSetupData.PowerGoodDeviceDelay == 0)? 0 : UsbData->UsbSetupData.PowerGoodDeviceNumDelay;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UsbSetupGetLegacySupport
//
// Description: Returns the status of "USB legacy support" question from Setup.
//
// Input:       None
//
// Output:      0 - Enable, 1 - Disable, 2 - Auto
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 UsbSetupGetLegacySupport()
{
    return gUsbData->UsbSetupData.UsbLegacySupport;			//(EIP99882)
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UpdateMassDevicesForSetup
//
// Description: Updates "UsbMassDevNum" setup variable according to the number
//              of installed mass storage devices.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateMassDevicesForSetup()
{
    EFI_STATUS  Status;
    UINTN       VariableSize;
    CONNECTED_USB_DEVICES_NUM   devs;
    USB_MASS_DEV_NUM    SetupData;
    UINT8       MassDevValid[16]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    UINT8       i;
    UINT32      VariableAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;

#if USB_SETUP_VARIABLE_RUNTIME_ACCESS
    VariableAttributes |= EFI_VARIABLE_RUNTIME_ACCESS;
#endif

    VariableSize = sizeof(SetupData);
    Status = pRS->GetVariable( L"UsbMassDevNum",
        &gEfiSetupGuid,
        NULL,
        &VariableSize,
        &SetupData );

    if (Status == EFI_SUCCESS) {
        if (!SetupData.IsInteractionAllowed) return EFI_SUCCESS;
    }

    ReportDevices(&devs);

    SetupData.UsbMassDevNum = devs.NumUsbMass;

    Status = pRS->SetVariable( L"UsbMassDevNum",
        &gEfiSetupGuid,
        VariableAttributes,
        VariableSize,
        &SetupData );

    //
    // Based on avilable USB mass storage device, set the device avilable flag
    //
    for(i=0;i<devs.NumUsbMass;i++) {
        MassDevValid[i]=1;
    }

    VariableSize = sizeof(USB_MASS_DEV_VALID);

    Status = pRS->SetVariable( L"UsbMassDevValid",
        &gEfiSetupGuid,
        VariableAttributes,
        VariableSize,
        &MassDevValid );

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        Usb3OemGetMaxDeviceSlots
//
// Description: Returns maximum device slots to be enabled and programmed
//              in MaxSlotsEn field of XHCI CONFIG register. Valid range
//              is 1...HCPARAMS1.MaxSlots (see xhci.h for details)
//
// Output:      EFI_SUCCESS         - Valid value is reported in MaxSlots
//              EFI_UNSUPPORTED     - Function is not ported; MaxSlots will
//                                    be used from HCPARAMS1 field.
// Notes:       Porting is optional
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
Usb3OemGetMaxDeviceSlots(
    OUT UINT8   *MaxSlots
)
{
    return EFI_UNSUPPORTED;
}


/*
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        XHCI_InterruptHandler
//
// Description:
//  Hardware interrupt handler
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
XHCI_InterruptHandler (
  IN EFI_EXCEPTION_TYPE   InterruptType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
    EFI_TPL OriginalTPL;
    
    OriginalTPL = pBS->RaiseTPL (TPL_HIGH_LEVEL);
    
    gPic->EndOfInterrupt (gPic, gVector);
    
    pBS->RestoreTPL (OriginalTPL);
    USB_DEBUG(3, "xhci interrupt..\n");
}
*/

VOID
XhciTimerCallback(
    EFI_EVENT   Event,
    VOID        *Context
)
{
	EFI_TPL OriginalTPL;
    
    OriginalTPL = pBS->RaiseTPL (TPL_HIGH_LEVEL);

    // Execute XHCI_ProcessInterrupt using SW SMI, Context points to HC_STRUC
    UsbSmiHc(opHC_ProcessInterrupt, USB_HC_XHCI, Context);

	pBS->RestoreTPL (OriginalTPL);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBPort_InstallEventHandler
//
// Description:
//  Purpose of this function is to install event handlers for different
//  USB host controllers.
//
// Input:
//  Pointer to a host controller data structure
//
// Output:
//  EFI_SUCCESS on a successful handler installation, otherwise EFI_NOT_READY
//  
// Notes:
//  1. Currently implemented for XHCI only. UHCI, OHCI and EHCI currently have the
//  HW SMI registration routines in their HC Start functions.
//
//  2. This function is a part of UHCD, not a part of USBRT (SMI). It may only have
//  a code that installs a non-SMI event handler, e.h. timer callback function for
//  HC event polling, or HW interrupt handler. SMI handlers are installed in the
//  USBRT entry point (amiusb.c).
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBPort_InstallEventHandler(
    HC_STRUC *HcStruc
)
{
#if XHCI_SUPPORT
    EFI_STATUS  Status = EFI_SUCCESS;

	if (HcStruc->bHCType != USB_HC_XHCI) return EFI_UNSUPPORTED;
/*
#if XHCI_EVENT_SERVICE_MODE == 0
{
    EFI_EVENT   XhciTimerEvent;

    // Current HW does not support INTx method of interrupt, hold on to the handler
    // installation until HW matures. In the meantime, use timer interrupt callback.
    Status = pBS->CreateEvent(
            EFI_EVENT_TIMER | EFI_EVENT_NOTIFY_SIGNAL,
            EFI_TPL_CALLBACK,
            XhciTimerCallback, HcStruc, &XhciTimerEvent
    );
    ASSERT_EFI_ERROR(Status);

    pBS->SetTimer (XhciTimerEvent, TimerPeriodic, MILLISECOND*100 );
}
#endif
*/
/*
#if USBInt1C_SUPPORT
#if defined(CSM_SUPPORT) && CSM_SUPPORT		//(EIP69136+)

    // Update INT1C timer interrupt handler with the HcStruc data
    {
        UINT32  *ivt = (UINT32*)0;
        UINT32  Int1cVector;
        UINT32  Addr;
        UINT32  HcStrucAddr;
        UINT8   Count;
        EFI_LEGACY_BIOS_EXT_PROTOCOL    *BiosExtensions = NULL;

        // Find the vector hooked up by "USB Int1C". At this time only AMI OEM interrupts
        // might have trapped the original INT1C. So the trapped vector is located at EP-4
        // (EP is the Entry Point).
        //
        // For the details refer the INT1C data area in usbint1c.asm
		Status = pBS->LocateProtocol(
			&gEfiLegacyBiosExtProtocolGuid, NULL, &BiosExtensions);

		if (!EFI_ERROR(Status)) {
	        for (Count = 0, Int1cVector = ivt[0x1c];
	            ((Int1cVector >> 16) != 0xf000) && Count < 5;
	            Count++)
	        {
	            Addr = ((Int1cVector >> 12) & 0xffff0) + (Int1cVector & 0xffff);
	            // Check "$AMIUSB$" signature
	            if ((*(UINT32*)(UINTN)(Addr+2) == 0x494d4124) &&
	                (*(UINT32*)(UINTN)(Addr+6) == 0x24425355)) break;
	    
	            Int1cVector = *(UINT32*)(UINTN)(Addr - 4); // Trapped address
	        }
	        ASSERT(Count < 5);
	        if ((Count < 5) && ((Int1cVector >> 16) != 0xf000)) {
	            // Update HcStruc information
	            HcStrucAddr = Addr + 12;
	            Addr = (UINT32)(*(UINT16*)(UINTN)(Addr + 10));  // offset of the Params in URP
	            Addr += ((Int1cVector >> 12) & 0xffff0);        // added segment to create 32-bit address

	            BiosExtensions->UnlockShadow(0, 0, 0, 0);

	            *(UINTN*)(UINTN)HcStrucAddr = (UINTN)HcStruc;
	            *(UINTN*)(UINTN)Addr = (UINTN)HcStrucAddr;

	            BiosExtensions->LockShadow(0, 0);
	        }
		}
    }

#endif										//(EIP69136+)
#endif
*/
/*
    // Install HW interrupt handler on HcStruc->Irq IRQ level

    // Find the Legacy8259 protocol.  ASSERT if not found.
    Status = pBS->LocateProtocol (&gEfiLegacy8259ProtocolGuid, NULL, (VOID **) &gPic);
    if (!EFI_ERROR(Status)) {
        EFI_CPU_ARCH_PROTOCOL   *Cpu;

        // Get the interrupt vector number corresponding to IRQ0 from the 8259 driver
        Status = gPic->GetVector (gPic, HcStruc->Irq, (UINT8*)&gVector);
        ASSERT_EFI_ERROR (Status);
    
        // Find the CPU architectural protocol.  ASSERT if not found.
        Status = pBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &Cpu);
        ASSERT_EFI_ERROR (Status);

        // Install interrupt handler for XHCI controller
        Status = Cpu->RegisterInterruptHandler (Cpu, gVector, XHCI_InterruptHandler);
        ASSERT_EFI_ERROR (Status);
        gPic->EnableIrq (gPic, HcStruc->Irq, TRUE);

    }
*/

#endif
    return EFI_SUCCESS;
}

#endif

#if USB_DIFFERENTIATE_IDENTICAL_DEVICE_NAME
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AddPortNumbertoDeviceString
//
// Description:
//  This function will insert the USB device number into the devicename string.
//    Format----> "U(DeviceNumber)-DevNameString"
//
// Input:
//  Pointer to a device data structure
//
// Output:
//  VOID
//  
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
AddPortNumbertoDeviceString(
    DEV_INFO        *Device
)
{
    UINT8   i;
    UINT8   j;
    UINT8   TempArray[50];
    UINT8   Appendarray1[5] = {'U',NULL,'-',NULL};
    UINT8   Appendarray2[6] = {'U',NULL,NULL,'-',NULL};

    for (i = 0 ; Device->DevNameString[i]; i++) {
        TempArray[i] = Device->DevNameString[i];
    }
    TempArray[i] = 0;

    //
    // Check for device number, if <= 9 then convert to ASCII and insert in array,
    // else split the number and convert to ASCII and then insert in array.  
    //
    if (DeviceNumber <= 9) {
        Appendarray1[1] = DeviceNumber + 0x30;
        
        for (i = 0; Appendarray1[i]; i++) {
            Device->DevNameString[i] = Appendarray1[i];
        }
    } else {
        i = (DeviceNumber / 10) + 0x30;
        j = (DeviceNumber % 10) + 0x30;

        Appendarray2[1] = i;
        Appendarray2[2] = j;

        for (i = 0; Appendarray2[i] ; i++) {
            Device->DevNameString[i] = Appendarray2[i];
        }
    }

    for (j=0; TempArray[j]; j++, i++) {
         Device->DevNameString[i] = TempArray[j];
    }

    Device->DevNameString[i] = 0;

    DeviceNumber++;
}
#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
