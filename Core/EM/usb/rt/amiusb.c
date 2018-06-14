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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/amiusb.c 121   10/16/16 10:11p Wilsonlee $
//
// $Revision: 121 $
//
// $Date: 10/16/16 10:11p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/amiusb.c $
// 
// 121   10/16/16 10:11p Wilsonlee
// [TAG]  		EIP288158
// [Category]  	Improvement
// [Description]  	Check if gUsbData is integrity.
// [Files]  		amiusb.cif, usbsb.c, AmiUsbLib.cif, AmiUsbLib.sdl,
// AmiUsbSmmGlobalDataValidationLib.c,
// AmiUsbSmmGlobalDataValidationLib.cif,
// AmiUsbSmmGlobalDataValidationLib.mak, Crc32.c, amiusb.c, amiusb.h,
// ehci.c, elib.c, ohci.c, syskbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h,
// usbhid.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c, usbrt.mak, xhci.c,
// amiusbhc.c, efiusbccid.c, efiusbmass.c, uhcd.c, usbmisc.c,
// AmiUsbController.h, AmiUsbLibInclude.cif,
// AmiUsbSmmGlobalDataValidationLib.h
// 
// 120   7/29/16 3:13a Wilsonlee
// [TAG]  		EIP264662
// [Category]  	Improvement
// [Description]  	Don't install usb hw smi after reconnecting usb
// controllers.
// [Files]  		uhcd.c, usb.c, ohci.c, amiusb.c, amiusbhc.c
// 
// 119   7/29/16 3:09a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 117   7/07/16 1:09a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 116   10/16/15 3:34a Wilsonlee
// [TAG]  		EIP241977
// [Category]  	Improvement
// [Description]  	Improve UsbKbcAccessControl api function.
// [Files]  		amiusb.c
// 
// 115   4/10/15 3:12a Wilsonlee
// [TAG]  		EIP207413
// [Category]  	Improvement
// [Description]  	Install UsbApiTable and UsbMassApitTable in
// AmiUsbSmmProtocol.
// [Files]  		amiusbhc.c, AmiUsbController.h, usbdef.h, usbCCID.c, uhci.c,
// ehci.c, amiusbrtCCID.h, amiusb.h, amiusb.c, uhcd.c
// 
// 114   2/10/15 12:20a Wilsonlee
// Fixed build error in non-smm projects.
// 
// 113   12/03/14 9:36p Wilsonlee
// [TAG]  		EIP193805
// [Category]  	Improvement
// [Description]  	Security Enhancement for SMIHandler in USB module.
// [Files]  		amiusb.c, uhcd.c, usbrt.mak, usbdef.h, usbsb.c
// 
// 112   11/23/14 10:10p Wilsonlee
// [TAG]  		EIP189293
// [Category]  	Improvement
// [Description]  	Implement XHCI key repeat function.
// [Files]  		usb.c, xhci.c , xhci.h, amiusb.c
// 
// 111   6/05/14 9:15p Wilsonlee
// [TAG]  		EIP171837
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	When use afuwin update BIOS or read ROMID under pure Win8.1
// OS, sometimes the system will blue screen.
// [RootCause]  	UsbData->EfiKeyboardBuffer is EfiBootServicesData. This
// memory isn't reserved in OS. We can't write data to this memory in OS.
// [Solution]  	We clear the buffer at USBKBDProcessKeyboardData function
// if the system is under EFI.
// [Files]  		amiusb.c
// 
// 110   4/30/14 5:25a Wilsonlee
// [TAG]  		EIP164842
// [Category]  	Improvement
// [Description]  	Check if the devices have put into to our queue before
// we put them.
// [Files]  		UsbInt13.c, amiusb.c, ehci.c, ohci.c, usb.c, usbdef.h,
// usbmass.c, xhci.c, amiusbhc.c, efiusbmass.c, uhcd.c, usbbus.c, usbsb.c
// 
// 109   4/07/14 1:28a Wilsonlee
// [TAG]  		EIP157193
// [Category]  	Improvement
// [Description]  	Stop the usb host controllers at AcpiModeEnable if they
// art extend cards or don't support HW SMI.
// [Files]  		amiusb.c
// 
// 108   2/10/14 1:19a Ryanchou
// [TAG]  		EIP149929
// [Category]  	Improvement
// [Description]  	Stop all external EHCI HCs in ACPI enable call.
// [Files]  		amiusb.c
// 
// 107   12/15/13 10:16p Wilsonlee
// [TAG]  		EIP136594
// [Category]  	New Feature
// [Description]  	Support 64 bits LBA of usb mass storages.
// [Files]  		Bfiusb.asm, Bfiusb.equ, UsbInt13.c, UsbInt13.h, amiusb.c,
// usbdef.h, usbmass.c, UsbMass.h, efiusbmass.c, UI13.bin
// 
// 106   11/05/13 4:46a Ryanchou
// [TAG]  		EIP135636
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	NumLock LED cannot be on/off properly.
// [RootCause]  	It is the side effect of EIP #107429 changes, the
// keyboard does not generate break code when pressing NumLock.
// [Solution]  	Remove the EIP #107429 changes.
// [Files]  		amiusb.c, usbkbd.c, efiusbkb.c
// 
// 105   10/19/13 7:06a Ryanchou
// [TAG]  		EIP138257
// [Category]  	Improvement
// [Description]  	Correct USB HID device type.
// [Files]  		amiusb.c, usbdef.h, usbhid.c, efiusbhid.c, uhcd.c
// 
// 104   8/06/13 4:21a Wilsonlee
// [TAG]  		EIP128970
// [Category]  	Improvement
// [Description]  	UsbInstallHwSmiHandler returns EFI_UNSUPPORTED if
// HCType is invalid.
// [Files]  		amiusb.c
// 
// 103   6/02/13 11:43p Wilsonlee
// [TAG]  		EIP123235
// [Category]  	Improvement
// [Description]  	Stop the usb host controller at ExitBootService if it
// is an extend card or it doesn't support HW SMI.
// [Files]  		xhci.c, ehci.c, uhci.c, ohci.c, amiusb.c, usbdef.h, usbsb.c,
// uhcd.c
// 
// 102   4/10/13 9:29p Wilsonlee
// [TAG]  		EIP120573
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Afuwinx64/Safuwinx64 hang up issue.
// [RootCause]  	EfiZeroMem is a boot service function, we can't use it
// during runtime.
// [Solution]  	Use MemFill function to clear the KBC buffers.
// [Files]  		amiusb.c
// 
// 101   3/19/13 3:58a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 100   1/23/13 4:15a Ryanchou
// [TAG]  		EIP111280
// [Category]  	Improvement
// [Description]  	Add USB APIs for external driver.
// [Files]  		amiusb.c, amiusb.h, usbdef.h
// 
// 99    1/22/13 3:09a Wilsonlee
// [TAG]  		EIP112938
// [Category]  	Improvement
// [Description]  	Create a header file for usb mass storage driver.
// [Files]  		UsbMass.h, usbmass.c, usbdef.h, amiusb.c, efiusbmass.c
// 
// 98    12/21/12 5:02a Ryanchou
// [TAG]  		EIP71730
// [Category]  	New Feature
// [Description]  	Added OHCI handoff support.
// [Files]  		usb.sdl, usbport.c, amiusb.c, usbdef.h, UsbPolicy.h, usb.sd,
// usb.uni
// 
// 97    12/09/12 12:12a Wilsonlee
// [TAG]  		EIP107429
// [Category]  	Improvement
// [Description]  	Process the make code even if there is no break code.
// [Files]  		efiusbkb.c, amiusb.c
// 
// 96    12/02/12 10:23p Roberthsu
// [TAG]           EIP102150
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Push key and unplug KB , character  repeat can not.
// stop
// [RootCause]     Because repeat key does not clear when usb keyboard
// unplug.
// [Solution]      When keyboard disconnrct, clear keyboard device id with
// device id buffer and scancode buffer.
// [Files]         amiusb.c,syskbc.c,uhcd.c,usbkbd.c
// 
// 95    11/10/12 6:39a Ryanchou
// [TAG]  		EIP99431
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Cannot use the UsbIo's UsbAsyncInterruptTransfer for
// keyboard input
// [RootCause]  	Stopping EFI USB keyboard driver does not stop the
// endpoint polling, then application calls UsbAsyncInterruptTransfer,
// error will be returned.
// [Solution]  	Stops endpoint polling and release resource when
// disconnecting the device driver. And improve the
// UsbSyncInterruptTransfer.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhci.c, usb.c,
// usbCCID.c, usbdef.h, usbhub.c, usbkbd.c, usbmass.c, usbms.c,
// usbpoint.c, amiusbhc.c, efiusbhid.c, usbbus.c, usbbus.h
// 
// 94    8/29/12 8:10a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 93    8/07/12 9:39p Wilsonlee
// [TAG]  		EIP96366
// [Category]  	New Feature
// [Description]  	Add the token "DEFAULT_USB_EMUL6064_OPTION" that
// control the default value of the I/O port 60h/64h emulation support
// option.
// [Files]  		usb.sd, usb.sdl, amiusb.c, amiusb.h
// 
// 92    6/13/12 7:31a Lavanyap
// [TAG]  		EIP89825
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System get's hangs inside the SMI handler while flashing
// the Bios.
// [RootCause]  	Port 60/64 access SMI will not be generated immediately
// if accessed inside an SMI handler when KbcEmulation is enabled.
// [Solution]  	Emulation is disabled while accessing the Port 60/64.
// [Files]  		amiusb.c
// 
// 91    5/22/12 10:03a Ryanchou
// [TAG]  		EIP90154
// [Category]  	Improvement
// [Description]  	Remove the USBSB_EnableSmmPeriodicSmi and
// USBSB_DisableSmmPeriodicSmi hooks.
// [Files]  		amidef.h, amiusb.c, usb.c, usbsb.c
// 
// 90    5/04/12 6:37a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 89    5/04/12 5:21a Wilsonlee
// [TAG]  		EIP89307
// [Category]  	Improvement
// [Description]  	Modify incorrect #pragma pack directive.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, ohci.h, uhci.h, usb.c,
// usbdef.h, xhci.h, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h,
// UsbIo.h
// 
// 88    5/03/12 5:50a Roberthsu
// [TAG]           EIP84455
// [Category]  	Improvement
// [Description]  	Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 87    1/16/12 6:01a Ryanchou
// [TAG]  		EIP81132
// [Description]  	Add core version check for EIP80609 solution.
// [Files]  		amiusb.c, usbrt.mak, usbsb.c
// 
// 86    1/14/12 4:09a Ryanchou
// [TAG]  		EIP80609
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	If to enable debug mode and set launch CSM is "Never" in
// setup, system will hang at 0xB1
// [RootCause]  	The pointer AmiUsb is invalid if CSM is not launched,
// that may cause CPU exception.
// [Solution]  	Added USB smm protocol, and use SmmLocateProtocol to get
// the pointer.
// [Files]  		amiusb.c, AmiUsbController.h, usbrt.mak, usbsb.c
// 
// 85    1/13/12 4:23a Ryanchou
// [TAG]  		EIP47348
// [Category]  	New Feature
// [Description]  	Support for USB Port Reset function.
// [Files]  		amiusb.c, amiusb.h, amiusbhc.c, uhci.c, usb.c, usbbus.c,
// usbbus.h, usbmass.c
// 
// 84    12/09/11 3:09p Ryanchou
// [TAG]  		EIP7768
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	USB mass storage can't work after unplug and plug under DOS
// [RootCause]  	The SW SMI handler checks USB_FLAG_RUNNING_UNDER_EFI flag
// to get the URP from USB global data area or EBDA. Legacy boot event
// clears the flag, and UsbPrepareForLegacyOS will not be invoked.
// [Solution]  	Check the URP in USB global data area, if it is not empty,
// get it in USB global data area, or get it in EBDA.
// [Files]  		amiusb.c
// 
// 83    11/08/11 8:22a Wilsonlee
// [TAG]  		EIP74876
// [Category]  	New Feature
// [Description]  	Add USB API for shutdown single USB controller.
// [Files]  		amiusb.c, amiusb.h, usb.c, usbdef.h, uhcd.c, uhcd.h,
// AmiUsbController.h
// 
// 82    11/08/11 1:41a Ryanchou
// [TAG]  		EIP63188
// [Category]  	Improvement
// [Description]  	External USB controller support.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, uhcd.c, uhcd.h, uhci.c,
// usbdef.h, usbmisc.c, usbsb.c, xhci.c
// 
// 81    11/05/11 3:26a Ryanchou
// [TAG]  		EIP70094
// [Category]  	Improvement
// [Description]  	Microsoft CSM Opt-Out feature implementation.
// [Files]  		amiusb.c, uhcd.c
// 
// 80    10/17/11 2:24a Ryanchou
// [TAG]  		EIP69136
// [Category]  	Improvement
// [Description]  	Remove the dependency of EBDA in USB module for CSM
// disabling.
// [Files]  		amiusb.c, uhcd.c, usbport.c, usbsb.c
// 
// 79    9/28/11 10:45a Ryanchou
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
// 78    8/08/11 6:57a Ryanchou
// [TAG]  		EIP54018
// [Category]  	New Feature
// [Description]  	Added USB S5 wake up support.
// [Files]  		amiusb.c, ehci.c, ohci.c, uhci.c, usb.c, usb.sdl, usbdef.h,
// usbsb.c xhci.c
// 
// 77    8/05/11 6:18a Ryanchou
// [TAG]  		EIP60706
// [Category]  	Improvement
// [Description]  	Move gUsbBadDeviceTable into SMRAM.
// [Files]  		usbport.c, amiusb.c, usb.c, uhcd.c, AmiUsbController.h
// 
// 76    7/15/11 6:11a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c, usb.c, usbdef.h,
// usbkbd.c, usbkbd.h, usbms.c, usbrt.cif, usbsb.c, usbsetup.c,
// usbsrc.sdl, xhci.c
// 
// 75    7/12/11 8:09a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
// 74    5/03/11 8:44a Ryanchou
// [TAG]  		EIP57521
// [Category]  	Improvement
// [Description]  	Enumerate root hub ports after start host controllers
// in USB_StartLegacy.
// [Files]  		amiusb.c
// 
// 73    3/30/11 9:02a Ryanchou
// [TAG]  		EIP41483
// [Category]  	Improvement
// [Description]  	Stop timer SMI after legacy shutdown.
// [Files]  		amiusb.c, AmiUsbController.h, ohci.c
// 
// 72    3/29/11 10:07a Ryanchou
// [TAG]  		EIP53518
// [Category]  	Improvement
// [Description]  	Added chipset xHCI chip support.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhcd.c, uhci.c, usb.c,
// usb.sdl, usbdef.h, usbport, usbsb.c, xhci.c
// 
// 71    12/24/10 5:02a Tonylo
// [TAG]  		EIP48323
// [Category]  	Improvement
// [Description]  	Reflush USB keyboard data buffer to avoid junk data
// sent after enable USB keyboard data throughput.
// [Files]  		AMIUSB.C
// 
// 70    11/22/10 8:42a Ryanchou
// [TAG]  		EIP48064
// [Category]  	Improvement
// [Description]  	The SB template implemented elink
// AcpiEnableCallbackList, the XHCI/EHCI hand off function should be
// invoked via the elink AcpiEnableCallbackList.
// [Files]  		amidef.h, amiusb.c, amiusb.dxs, amiusb.h,
// AmiUsbController.h, usb.sdl, usbrt.mak, usbsb.c
// 
// 69    10/07/10 9:32a Ryanchou
// EIP42986: Remove the retry loop in UsbHwSmiHandler.
// 
// 68    8/31/10 8:57a Tonylo
// Remove user tags for coding standard.
// 
// Description:  Remove user tags for coding standard.
// 
// 67    8/18/10 4:22p Olegi
// Klockwork related fixes; EIP37978
// 
// 66    7/27/10 9:11a Ryanchou
// EIP41216: Return correct error code when device isn't present.
// 
// 65    7/15/10 4:33a Tonylo
// EIP21649 - USB mass storage device still appear in BBS menu when USB
// legacy support is disabled.
// 
// 64    6/07/10 8:56a Ryanchou
// EIP38547: Fixed system halt when installing FreeBSD.
// 
// 63    3/31/10 6:26p Olegi
// 
// 62    3/25/10 9:45a Olegi
// 
// 61    3/19/10 10:05a Olegi
// 
// 60    1/27/10 5:19p Olegi
// Added chipset porting hook to initialize timers.
// 
// 59    12/01/09 10:06a Olegi
// EIP31535: RWV error code corrected.
// 
// 58    11/25/09 8:05a Olegi
// EIPEIP29733: Added KBC access control API
// 
// 57    10/30/09 5:47p Olegi
// 
// 56    10/02/09 10:49a Olegi
// Code cleanup.
// 
// 54    9/15/09 10:21a Olegi
// Added USB_INCMPT_HID_DATA_OVERFLOW incompatibility type.
// 
// 53    8/26/09 11:41a Olegi
// Changes that prevent collision of keyboard activity and mass storage
// access. EIP#22808
// 
// 52    5/22/09 1:46p Olegi
// Added the special treatment for in-built hubs.
// 
// 51    5/21/09 5:11p Olegi
// Added checking for hotplug fake drives in Read/Write/Verify functions.
// 
// 50    1/29/09 2:31p Olegi
// USB API CheckDevicePresence is extended with USB_SRCH_DEVBASECLASS_NUM
// search key.
// 
// 49    1/23/09 4:28p Olegi
// Added EXTRA_CHECK_DEVICE_READY condition for the fix to EIP#15037.
// 
// 48    1/05/09 9:40a Olegi
// Changes for EIP#15037. Extra CheckDeviceReady call added to read/write
// functions.
// 
// 46    10/06/08 3:33p Olegi
// EHCI change ownership testing in DOS fix (EIP#14855).
// 
// 44    9/24/08 4:01p Olegi
// Modified USBAPI_ChangeOwner so that it allows multiple calls to
// acquiring the ownership without releasing it.
// 
// 43    7/04/08 1:07p Olegi
// Device "Ultra-X, Inc.: Ultra-X QTP USB HD 1.01" is removed from
// incompatible device list.
// 
// 42    6/27/08 5:52p Olegi
// Added incompatible devices.
// 
// 41    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 40    12/17/07 4:04p Olegi
// KBC emulation support added.
// 
// 39    12/05/07 4:36p Olegi
// Modification in USBSWSMIHandler() related to the 64/32-bit pointers.
// 
// 36    7/09/07 2:11p Olegi
// Changed the maximum data size of the BulkTransfer from 1kB to 64kB.
// 
// 34    6/11/07 2:53p Olegi
// Bugfix in device read/write routine: do not issue RWV command if there
// is no media present.
// 
// 32    3/20/07 12:16p Olegi
// SMITHUNK removed.
//
// 28    10/18/06 9:40a Andriyn
// Fix: race condition on hot-plug in / plug-off
//
// 27    10/12/06 4:41p Olegi
// Modified the method of passing arguments into USBSWSMIHandler: it is
// done through memory location, not using CPU register. This change is
// only valid for CSM16 versions 31 and later.
//
// 26    4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 24    3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 23    3/06/06 6:22p Olegi
// Lun devices support modifications: supported using the index in
// DEV_INFO table, not through dedicated massLun table.
//
// 21    1/11/06 11:51a Olegi
// LegacyUsbSupport setup question functionality added.
//
// 18    10/20/05 3:08p Olegi
// ReadDevice correction (EST change).
//
// 14    8/25/05 7:19p Andriyn
// USB Keyboard and mouse to use EMUL 60/64 for passing data to KBC.
// Fall-back when EMUL 60/64 is not present
//
// 13    8/23/05 5:50p Olegi
// USBMassGetDeviceParameters function added.
//
// 12    8/11/05 9:53a Olegi
// 60/64 port emulation related fixes for EMU6064 driver.
//
// 11    8/04/05 5:58p Andriyn
// Legacy over LegacyFree
//
// 10    6/20/05 8:55a Olegi
// .NET compiler with highest warning level and warning-as-error
// modification.
//
// 9     6/15/05 1:59p Andriyn
// Comments were changed
//
// 6     6/03/05 6:06p Olegi
// UsbHwSmiHandler modified to be called individually from UHCI, OHCI and
// EHCI drivers.
//
// 5     6/03/05 9:28a Olegi
// ATA Error reporting is corrected in USBWrapGetATAErrorCode.
//
// 4     6/01/05 5:21p Olegi
// Debug message shortened.
//
// 3     5/17/05 7:51p Andriyn
// USB BUS pre-release
//
// 2     5/10/05 4:11p Andriyn
// USBBUS implementation
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:   AMIUSB.C
//
//  Description:    AMI USB API implementation. The following code will be
//                  copied to SMM; only RT functions can be used. gUsbData
//                  is obtained from AMIUHCD in the entry point and can be
//                  used afterwards.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiDxeLib.h>
#include "amiusb.h"
#include "amidef.h"
#include <UsbDevDriverElinks.h>			//(EIP71750+)
#if USB_RUNTIME_DRIVER_IN_SMM
#include <AmiBufferValidationLib.h>
#include <AmiUsbSmmGlobalDataValidationLib.h>
#endif

#if USB_DEV_KBD
#include "usbkbd.h"
#endif
#include "UsbMass.h"

										//(EIP54018+)>
#if USB_S5_WAKEUP_SUPPORT
#include <Protocol\SmmSxDispatch.h>
#include <Protocol\SmmPowerButtonDispatch.h>
#endif
										//<(EIP54018+)
//#pragma warning (disable: 4152)

extern UINT8 IsKbcAccessBlocked;            //(EIP29733+)
EFI_EMUL6064MSINPUT_PROTOCOL* gMsInput = 0;
EFI_EMUL6064KBDINPUT_PROTOCOL* gKbdInput = 0;
EFI_EMUL6064TRAP_PROTOCOL* gEmulationTrap = 0;

USB_GLOBAL_DATA     *gUsbData;
//USB_BADDEV_STRUC    *gUsbBadDeviceTable;			//(EIP60706-)

AMI_USB_SMM_PROTOCOL	gUsbSmmProtocol = {0};

BOOLEAN gLockSmiHandler = FALSE;
BOOLEAN gLockHwSmiHandler = FALSE;
BOOLEAN gCheckUsbApiParameter = FALSE;

VOID    StopControllerType(UINT8);
VOID    StartControllerType(UINT8);
UINT8   USB_StopDevice (HC_STRUC*,  UINT8, UINT8);
UINT8   USB_EnumerateRootHubPorts(UINT8);   //(EIP57521+)              
VOID    StopControllerBdf(UINT16);			//(EIP74876+)

VOID	FillHcdEntries();
										//(EIP71750+)>
typedef VOID USB_DEV_DELAYED_DRIVER_CHECK (DEV_DRIVER*);
extern USB_DEV_DELAYED_DRIVER_CHECK USB_DEV_DELAYED_DRIVER EndOfUsbDevDelayedDriverList;
USB_DEV_DELAYED_DRIVER_CHECK* UsbDevDelayedDrivers[]= {USB_DEV_DELAYED_DRIVER NULL};

typedef VOID USB_DEV_DRIVER_CHECK (DEV_DRIVER*);
extern USB_DEV_DRIVER_CHECK USB_DEV_DRIVER EndOfUsbDevDriverList;
USB_DEV_DRIVER_CHECK* UsbDevDrivers[]= {USB_DEV_DRIVER NULL};
										//<(EIP71750+)
										//(EIP54018+)>
#if USB_S5_WAKEUP_SUPPORT
VOID    UsbSuspend(VOID);
#endif

#if USB_S5_WAKEUP_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbS5SmiCallback
//
// Description: 
//  This function enter usb s5 callback.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UsbS5SmiCallback(
    IN EFI_HANDLE DispatchHandle,
    IN EFI_SMM_SX_DISPATCH_CONTEXT *DispatchContext
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)    
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) {
        return;
    }
#endif
    UsbSuspend();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbPowerButtonSmiCallback
//
// Description: 
//  This function enter s5 callback if press power button.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UsbPowerButtonSmiCallback(
    IN EFI_HANDLE DispatchHandle,
	IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT *DispatchContext
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)    
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) {
        return;
    }
#endif
    UsbSuspend();
}
#endif
										//<(EIP54018+)

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:        aUsbApiTable - USB API Function Dispatch Table
//
// Type:        Function Dispatch Table
//
// Description: This is the table of functions used by USB API
//
// Notes:       This functions are invoked via software SMI
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>

API_FUNC aUsbApiTable[] = {
    USBAPI_CheckPresence,
    USBAPI_Start,
    USBAPI_Stop,
    USBAPI_DisableInterrupts,
    USBAPI_EnableInterrupts,
    USBAPI_MoveDataArea,
    USBAPI_GetDeviceInfo,
    USBAPI_CheckDevicePresence,
    USBAPI_MassDeviceRequest,
    USBAPI_PowerManageUSB,
    USBAPI_PrepareForOS,
    USBAPI_SecureInterface,
    USBAPI_LightenKeyboardLEDs,
    USBAPI_ChangeOwner,
    USBAPI_HC_Proc,
    USBAPI_Core_Proc,
    USBAPI_LightenKeyboardLEDs_Compatible,
    USBAPI_KbcAccessControl,
    USBAPI_LegacyControl,
    USBAPI_GetDeviceAddress,
    USBAPI_ExtDriverRequest,
    USBAPI_CCIDRequest,
    USBAPI_UsbStopController,				//(EIP74876+)
    USBAPI_HcStartStop
};

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:        USBMassAPITable - USB Mass Storage API Function Dispatch Table
//
// Type:        Function Dispatch Table
//
// Description: This is the table of functions used by USB Mass Storage API
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>

API_FUNC aUsbMassApiTable[] = {
    USBMassAPIGetDeviceInformation, // USB Mass API Sub-Func 00h
    USBMassAPIGetDeviceGeometry,    // USB Mass API Sub-Func 01h
    USBMassAPIResetDevice,          // USB Mass API Sub-Func 02h
    USBMassAPIReadDevice,           // USB Mass API Sub-Func 03h
    USBMassAPIWriteDevice,          // USB Mass API Sub-Func 04h
    USBMassAPIVerifyDevice,         // USB Mass API Sub-Func 05h
    USBMassAPIFormatDevice,         // USB Mass API Sub-Func 06h
    USBMassAPICommandPassThru,      // USB Mass API Sub-Func 07h
    USBMassAPIAssignDriveNumber,    // USB BIOS API function 08h
    USBMassAPICheckDevStatus,       // USB BIOS API function 09h
    USBMassAPIGetDevStatus,         // USB BIOS API function 0Ah
    USBMassAPIGetDeviceParameters   // USB BIOS API function 0Bh
};

EFI_DRIVER_ENTRY_POINT(USBDriverEntryPoint)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   USBDriverEntryPoint
//
// Description: USB Driver entry point
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBDriverEntryPoint(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS Status;

    InitAmiLib(ImageHandle, SystemTable);

#if USB_RUNTIME_DRIVER_IN_SMM
    Status = InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
#else
	Status = InstallUsbProtocols(); 
	InitializeUsbGlobalData();
#endif
    ASSERT_EFI_ERROR(Status);

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:       InitializeUsbGlobalData
//
// Description: This function initializes the USB global data.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitializeUsbGlobalData(
	VOID
)
{
	EFI_STATUS	Status;
    UINT8   	bDriverIndex;
    UINT8   	bDelayedIndex;

    //
    // Initialize host controller drivers
    //
    FillHcdEntries();   // This routine is implemented in $(BUILD_DIR)\dummyusbrt.c

    //
    // Initialize the device driver pointers
    //
    bDriverIndex = 0;
    bDelayedIndex = 0;
										//(EIP71750)>
    while(UsbDevDelayedDrivers[bDelayedIndex]) {
        UsbDevDelayedDrivers[bDelayedIndex](&gUsbData->aDelayedDrivers[bDelayedIndex]);
		if (gUsbData->aDelayedDrivers[bDelayedIndex].pfnDeviceInit) {
            (*gUsbData->aDelayedDrivers[bDelayedIndex].pfnDeviceInit)();
        }
        if (gUsbData->aDelayedDrivers[bDelayedIndex].bDevType) {
            bDelayedIndex++;
        }
    }

    while(UsbDevDrivers[bDriverIndex]) {
        UsbDevDrivers[bDriverIndex](&gUsbData->aDevDriverTable[bDriverIndex]);
		if (gUsbData->aDevDriverTable[bDriverIndex].pfnDeviceInit) {
            (*gUsbData->aDevDriverTable[bDriverIndex].pfnDeviceInit)();
        }
        if (gUsbData->aDevDriverTable[bDriverIndex].bDevType) {
            bDriverIndex++;
        }
    }

	//
	// Allocate a block of memory to be used as a temporary
	// buffer for  USB mass transfer
	//
	Status = pBS->AllocatePool (EfiRuntimeServicesData, MAX_CONSUME_BUFFER_SIZE, 
				&gUsbData->fpUSBMassConsumeBuffer);
	ASSERT_EFI_ERROR(Status);
	pBS->SetMem(gUsbData->fpUSBMassConsumeBuffer, MAX_CONSUME_BUFFER_SIZE, 0);

	//
	// Allocate a block of memory for the temporary buffer
	//
	Status = gBS->AllocatePool (EfiRuntimeServicesData, MAX_TEMP_BUFFER_SIZE, 
				&gUsbData->fpUSBTempBuffer);
	ASSERT_EFI_ERROR(Status);
	pBS->SetMem(gUsbData->fpUSBTempBuffer, MAX_TEMP_BUFFER_SIZE, 0);

    //
    // Allow to enumerate ports
    //
    gUsbData->bEnumFlag = FALSE;

	return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:       UsbApiHandler
//
// Description: 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbApiHandler(VOID* Param)
{
    URP_STRUC   *fpURP = (URP_STRUC*)Param;
    UINT8       bFuncIndex;
    UINT8       bNumberOfFunctions;

	if (fpURP == NULL) {
		return;
	}

    bFuncIndex = fpURP->bFuncNumber;
    bNumberOfFunctions = sizeof aUsbApiTable / sizeof (API_FUNC *);

    //
    // Make sure function number is valid; if function number is not zero
    // check for valid extended USB API function
    //
    if (bFuncIndex && ((bFuncIndex < USB_NEW_API_START_FUNC ) ||
            bFuncIndex > (bNumberOfFunctions + USB_NEW_API_START_FUNC))) {
        //fpURP->bRetValue = USBAPI_INVALID_FUNCTION;
        USB_DEBUG(3, "UsbApiHandler Invalid function#%x\n", bFuncIndex);
        return;
    }

    if (bFuncIndex) {
        bFuncIndex = (UINT8)(bFuncIndex - USB_NEW_API_START_FUNC + 1);
    }

    aUsbApiTable[bFuncIndex](fpURP);    // Call the appropriate function

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:       InstallUsbProtocols
//
// Description: This function initializes the USB global data.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InstallUsbProtocols(
	VOID
)
{
	EFI_STATUS	Status;
	EFI_USB_PROTOCOL	*UsbProtocol;

    Status = pBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, &UsbProtocol);
	if (EFI_ERROR(Status)) {
		return Status;
	}
    gUsbData = UsbProtocol->USBDataPtr;

	UsbProtocol->UsbRtKbcAccessControl = UsbKbcAccessControl;

	//Hook USB legacy control function for shutdown/init USB legacy support
	UsbProtocol->UsbLegacyControl = USBRT_LegacyControl;
	UsbProtocol->UsbStopUnsupportedHc = USB_StopUnsupportedHc;
#if !USB_RUNTIME_DRIVER_IN_SMM
	UsbProtocol->UsbInvokeApi = UsbApiHandler;
#endif

	return Status;
}

#if USB_RUNTIME_DRIVER_IN_SMM
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: SMM entry point of AMIUSB driver
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InSmmFunction(
    EFI_HANDLE ImageHandle,
    EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS                      Status;

    EFI_SMM_SW_DISPATCH_CONTEXT     SwSmiContext;
    EFI_HANDLE                      SwSmiHandle = NULL;
    EFI_SMM_SW_DISPATCH_PROTOCOL    *SwSmiDispatch;

    UINT32                          KbcEmulFeature = 0;
    VOID	                        *ProtocolNotifyRegistration;
    EFI_EVENT                       Emul6064Event = NULL;

									//(EIP54018+)>
#if USB_S5_WAKEUP_SUPPORT
    EFI_SMM_SX_DISPATCH_CONTEXT     S5DispatchContext;
    EFI_SMM_SX_DISPATCH_PROTOCOL    *SxDispatchProtocol;
    EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT   PbDispatchContext;
    EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL  *PbDispatchProtocol;
    EFI_HANDLE  S5DispatchHandle;
    EFI_HANDLE  PbDispatchHandle;
#endif
									//<(EIP54018+)
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
	EFI_HANDLE	UsbSmmProtocolHandle = NULL;

    Status = InitAmiSmmLib(ImageHandle, SystemTable);
    if (EFI_ERROR(Status)) return Status;
#endif

    InitAmiBufferValidationLib(ImageHandle, SystemTable);

	InstallUsbProtocols();
	InitializeUsbGlobalData();


    Status = pBS->LocateProtocol (&gEmul6064TrapProtocolGuid, NULL, &gEmulationTrap);
    if (EFI_ERROR(Status)) {
        Status = RegisterProtocolCallback(&gEmul6064TrapProtocolGuid,
        							    Emul6064TrapCallback,
                                        NULL,
                                        &Emul6064Event,
                                        &ProtocolNotifyRegistration);
    }

    if(!gUsbData->kbc_support) {
        Status = gBS->LocateProtocol (&gEmul6064MsInputProtocolGuid, NULL, &gMsInput);
        pBS->LocateProtocol (&gEmul6064KbdInputProtocolGuid, NULL, &gKbdInput);

        if (Status == EFI_SUCCESS) {
            gUsbData->dUSBStateFlag |= USB_FLAG_6064EMULATION_ON;
            if(gEmulationTrap) 
                KbcEmulFeature = gEmulationTrap->FeatureSupported(gEmulationTrap);
                if(KbcEmulFeature & IRQ_SUPPORTED) {
                    gUsbData->dUSBStateFlag |= USB_FLAG_6064EMULATION_IRQ_SUPPORT;
                }
        } else {
           InitSysKbc( &gKbdInput, &gMsInput );
        }
    } else {
        //
        //Init Fake Emulation interface
        //
        InitSysKbc( &gKbdInput, &gMsInput );
    }

    Status = USBSB_InstallSmiEventHandlers();

    USB_DEBUG(DEBUG_LEVEL_3,"AMIUSB global data at 0x%x\n", gUsbData);

    //
    // Register the USB SW SMI handler
    //
    Status = pBS->LocateProtocol (&gEfiSmmSwDispatchProtocolGuid, NULL, &SwSmiDispatch);

    if (EFI_ERROR (Status)) {
        USB_DEBUG(DEBUG_LEVEL_0, "SmmSwDispatch protocol: %r\n", Status);
        return Status;
    }

    SwSmiContext.SwSmiInputValue = USB_SWSMI;
    Status = SwSmiDispatch->Register (SwSmiDispatch, USBSWSMIHandler, &SwSmiContext, &SwSmiHandle);

    USB_DEBUG(DEBUG_LEVEL_3, "AMIUSB SW SMI registration:: %r\n", Status);

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    gUsbSmmProtocol.UsbStopUnsupportedHc = USB_StopUnsupportedHc;
    gUsbSmmProtocol.UsbApiTable = aUsbApiTable;
    gUsbSmmProtocol.UsbMassApiTable = aUsbMassApiTable;
    gUsbSmmProtocol.GlobalDataValidation.ConstantDataCrc32 = 0;
    gUsbSmmProtocol.GlobalDataValidation.Crc32Hash = (UINT32)GetCpuTimer();

    Status = pSmst->SmmInstallProtocolInterface(
                    &UsbSmmProtocolHandle,
                    &gAmiUsbSmmProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gUsbSmmProtocol
                    );
	
	USB_DEBUG(DEBUG_LEVEL_3, "AMIUSB SMM protocol: %r\n", Status);
#endif

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    InitAmiUsbSmmGlobalDataValidationLib(ImageHandle, SystemTable);
    UpdateAmiUsbSmmGlobalDataCrc32(gUsbData);
#endif

										//(EIP54018+)>
#if USB_S5_WAKEUP_SUPPORT
    Status = pBS->LocateProtocol(
        &gEfiSmmSxDispatchProtocolGuid,
        NULL,
        &SxDispatchProtocol
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    S5DispatchContext.Type  = SxS5;
    S5DispatchContext.Phase = SxEntry;
    Status = SxDispatchProtocol->Register(
        SxDispatchProtocol,
        UsbS5SmiCallback,
        &S5DispatchContext,
        &S5DispatchHandle
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    // Locate Power Button Dispatch Protocol
    Status = pBS->LocateProtocol(
        &gEfiSmmPowerButtonDispatchProtocolGuid,
        NULL,
        &PbDispatchProtocol
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    // Register the handler for power button presses
    PbDispatchContext.Phase = PowerButtonEntry;
    Status = PbDispatchProtocol->Register(
        PbDispatchProtocol,
        UsbPowerButtonSmiCallback,
        &PbDispatchContext,
        &PbDispatchHandle
    );
#endif
										//<(EIP54018+)

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBSWSMIHandler
//
// Description: Invoked on reads from SW SMI port with value USB_SWSMI. This
//              function dispatches the USB Request Packets (URP) to the
//              appropriate functions.
//
// Input:       EBDA:USB_DATA_EBDA_OFFSET - Pointer to the URP (USB Request
//              Packet structure)
//              DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
//
// Output:      bRetValue   Zero on successfull completion
//              Non-zero on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBSWSMIHandler (
    EFI_HANDLE                  DispatchHandle,
    EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext
)
{
    URP_STRUC   *UsbUrp;
    UINT16      EbdaSeg;
    EFI_STATUS  Status;

    if (gLockSmiHandler == TRUE) {
        return;
    }
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) {
        gLockHwSmiHandler = TRUE;
        gLockSmiHandler = TRUE;
        return;
    }
#endif

	if (gUsbData->fpURP) {			// Call from AMIUSB C area
        Status = AmiValidateMemoryBuffer((VOID*)gUsbData->fpURP, sizeof(URP_STRUC));
        if (EFI_ERROR(Status)) {
            USB_DEBUG(3, "UsbApiHandler Invalid Pointer, the address is in SMRAM.\n");
            return;
        }
		UsbUrp = gUsbData->fpURP;
		gUsbData->fpURP = 0;   		// Clear the switch
	} else {
	    if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_OS) {
            return;
        }
        //
        // Get the fpURP pointer from EBDA
        //
        EbdaSeg = *((UINT16*)0x40E);
        UsbUrp = *(URP_STRUC**)(UINTN)(((UINT32)EbdaSeg << 4) + USB_DATA_EBDA_OFFSET);
        UsbUrp = (URP_STRUC*)((UINTN)UsbUrp & 0xFFFFFFFF);
        Status = AmiValidateMemoryBuffer((VOID*)UsbUrp, sizeof(URP_STRUC));
        if (EFI_ERROR(Status)) {
            USB_DEBUG(3, "UsbApiHandler Invalid Pointer, the address is in SMRAM.\n");
            return;
        }
	}

	if (UsbUrp == NULL) {
		return;
	}

    gCheckUsbApiParameter = TRUE;

	UsbApiHandler(UsbUrp);

    gCheckUsbApiParameter = FALSE;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHwSmiHandler
//
// Description: USB Hardware SMI handler.
//
// Input:       Host controller type.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbHwSmiHandler (UINT8 HcType)
{
    UINT8       Index;
    HC_STRUC    *HcStruc;
    EFI_STATUS  Status;

    if (gLockHwSmiHandler == TRUE) {
        return;
    }

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) {
        gLockHwSmiHandler = TRUE;
        gLockSmiHandler = TRUE;
        return;
    }
#endif

    for (Index = 0; Index < gUsbData->HcTableCount; Index++) {
        HcStruc = gUsbData->HcTable[Index];
        if (HcStruc == NULL) {
            continue;
        }
        if (!(HcStruc->dHCFlag & HC_STATE_USED)) {
        	continue;
        }
        if (HcStruc->bHCType == HcType) { // Process appropriate interrupt
            (*gUsbData->aHCDriverTable
				[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDProcessInterrupt)(HcStruc);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   xhciHWSMIHandler
//
// Description: USB Hardware SMI handler.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
//
// Output:      Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UhciHWSMIHandler (
    EFI_HANDLE                      DispatchHandle,
    EFI_SMM_USB_DISPATCH_CONTEXT    *DispatchContext
    )
{
    UsbHwSmiHandler(USB_HC_UHCI);
}
VOID
OhciHWSMIHandler (
    EFI_HANDLE                      DispatchHandle,
    EFI_SMM_USB_DISPATCH_CONTEXT    *DispatchContext
    )
{
    UsbHwSmiHandler(USB_HC_OHCI);
}
VOID
EhciHWSMIHandler (
    EFI_HANDLE                      DispatchHandle,
    EFI_SMM_USB_DISPATCH_CONTEXT    *DispatchContext
    )
{
    UsbHwSmiHandler(USB_HC_EHCI);
}

VOID
XhciHwSmiHandler (
    EFI_HANDLE	DispatchHandle,
    VOID	    *DispatchContext
    )
{
    UsbHwSmiHandler(USB_HC_XHCI);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBInstallHwSmiHandler
//
// Description:
//  This function registers USB hardware SMI callback function.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbInstallHwSmiHandler(
	HC_STRUC    *HcStruc
)
{
	EFI_STATUS                      Status;
	EFI_SMM_USB_DISPATCH_CONTEXT    UsbContext;
    EFI_SMM_USB_DISPATCH_PROTOCOL   *UsbDispatch;
	EFI_SMM_USB_DISPATCH			UsbCallback;
    EFI_HANDLE                      Handle = NULL;

    if (HcStruc->HwSmiHandle != NULL) {
        return EFI_SUCCESS;
    }
	
    Status = gBS->LocateProtocol(
            &gEfiSmmUsbDispatchProtocolGuid,
            NULL,
            &UsbDispatch);
    ASSERT_EFI_ERROR(Status);
	if (EFI_ERROR(Status)) {
		return Status;
	}

	switch (HcStruc->bHCType) {
		case USB_HC_UHCI:
			UsbCallback = UhciHWSMIHandler;
			break;

		case USB_HC_OHCI:
			UsbCallback = OhciHWSMIHandler;
			break;

		case USB_HC_EHCI:
			UsbCallback = EhciHWSMIHandler;
			break;

		case USB_HC_XHCI:
			UsbCallback = XhciHwSmiHandler;
			break;

        default:
            return EFI_UNSUPPORTED;
	}

    UsbContext.Type = UsbLegacy;
    UsbContext.Device = HcStruc->pHCdp;

    Status = UsbDispatch->Register(
                UsbDispatch,
                UsbCallback,
                &UsbContext,
                &Handle);

    USB_DEBUG(DEBUG_LEVEL_3, "AMIUSB HC type %x HW SMI registation status:: %r\n", HcStruc->bHCType, Status);

	if (!EFI_ERROR(Status)) {
		HcStruc->HwSmiHandle = Handle;
	}

	return Status;
}
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        Emul6064TrapCallback
//
// Description:
//  Update the KbcEmul feature when the Emul6064Trap Protocol becomes available.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
Emul6064TrapCallback (
    EFI_EVENT       Event,
    VOID            *Context
)
{
    EFI_STATUS                      Status;
    UINT32                          KbcEmulFeature = 0;
    
	Status = gBS->LocateProtocol(
				&gEmul6064TrapProtocolGuid,
				NULL,
				&gEmulationTrap);

    if(!gUsbData->kbc_support) {
        	Status = gBS->LocateProtocol(
        			&gEmul6064MsInputProtocolGuid,
        			NULL,
        			&gMsInput);

        	gBS->LocateProtocol(
        			&gEmul6064KbdInputProtocolGuid,
        			NULL,
        			&gKbdInput);

        if (Status == EFI_SUCCESS) {
            gUsbData->dUSBStateFlag |= USB_FLAG_6064EMULATION_ON;
            if(gEmulationTrap) 
                KbcEmulFeature = gEmulationTrap->FeatureSupported(gEmulationTrap);
                if(KbcEmulFeature & IRQ_SUPPORTED) {
                    gUsbData->dUSBStateFlag |= USB_FLAG_6064EMULATION_IRQ_SUPPORT;
                }
        } else {
           InitSysKbc( &gKbdInput, &gMsInput );
        }
    } else {
        //
        //Init Fake Emulation interface
        //
        InitSysKbc( &gKbdInput, &gMsInput );
    }
}

//////////////////////////////////////////////////////////////////////////////
//
// USB API Functions
//
//////////////////////////////////////////////////////////////////////////////

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_MassDeviceRequest
//
// Description: This routine services the USB API function number 27h.  It
//      handles all the mass storage related calls from the higher
//      layer. Different sub-functions are invoked depending on
//      the sub-function number
//
// Input:   fpURPPointer    Pointer to the URP structure
//      fpURPPointer.bSubFunc   Subfunction number
//          00  Get Device Information
//          01  Get Device Parameter
//          02  Reset Device
//          03  Read Device
//          04  Write Device
//          05  Verify Device
//          06  Format Device
//          07  Request Sense
//          08  Test Unit Ready
//          09  Start Stop Unit
//          0A  Read Capacity
//          0B  Mode Sense
//          0C  Device Inquiry
//          0D  Send Command
//          0E  Assign drive number
//
// Output:  URP structure is updated with the relevant information
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBAPI_MassDeviceRequest (URP_STRUC *fpURP)
{
    UINT8 bMassFuncIndex = fpURP->bSubFunc;
    UINT8 bNumberOfMassFunctions = sizeof aUsbMassApiTable / sizeof (API_FUNC *);

    //
    // Make sure function number is valid
    //
    if (bMassFuncIndex >= bNumberOfMassFunctions) {
        //fpURP->bRetValue = USBAPI_INVALID_FUNCTION;
        USB_DEBUG(3, "UsbApi MassDeviceRequet Invalid function#%x\n", bMassFuncIndex);
        return;
    }
    gUsbData->bUSBKBC_MassStorage = 01;
    //
    // Function number is valid - call it
    //
    aUsbMassApiTable[bMassFuncIndex](fpURP);
    gUsbData->bUSBKBC_MassStorage = 00;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_CheckPresence
//
// Description: This routine services the USB API function number 0.  It
//              reports the USB BIOS presence, its version number and
//              its current status information
//
// Input: fpURPPointer - Pointer to the URP structure
//
// Output: URP structure is updated with the following information
//            CkPresence.wBiosRev       USB BIOS revision (0210h means r2.10)
//            CkPresence.bBiosActive    0 - if USB BIOS is not running
//            CkPresence.bNumBootDev    Number of USB boot devices found
//            CkPresence.bNumHC         Number of host controller present
//            CkPresence.bNumPorts      Number of root hub ports
//            CkPresence.dUsbDataArea   Current USB data area
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBAPI_CheckPresence (URP_STRUC *fpURP)
{
    fpURP->bRetValue                        = USB_SUCCESS;
    fpURP->ApiData.CkPresence.bBiosActive   = 0;

    fpURP->ApiData.CkPresence.bNumBootDev   = 0;    // Number of USB boot devices found
    fpURP->ApiData.CkPresence.bNumKeyboards = 0;    // Number of USB keyboards present
    fpURP->ApiData.CkPresence.bNumMice      = 0;    // Number of USB mice present
    fpURP->ApiData.CkPresence.bNumPoint		= 0;    // Number of USB Point present    //(EIP38434+)
    fpURP->ApiData.CkPresence.bNumHubs      = 0;    // Number of USB hubs present
    fpURP->ApiData.CkPresence.bNumStorage   = 0;    // Number of USB storage devices present

    fpURP->ApiData.CkPresence.wBiosRev = (USB_DRIVER_MAJOR_VER << 4) + USB_DRIVER_MINOR_VER;
    fpURP->ApiData.CkPresence.bBiosActive = USB_ACTIVE; // Set USB BIOS as active
    if (!(gUsbData->dUSBStateFlag & USB_FLAG_DISABLE_LEGACY_SUPPORT)) {
        fpURP->ApiData.CkPresence.bBiosActive |= USB_LEGACY_ENABLE;
    }
    if (gUsbData->dUSBStateFlag & USB_FLAG_6064EMULATION_ON) {
        fpURP->ApiData.CkPresence.bBiosActive |= USB_6064_ENABLE;
    }
    USBWrap_GetDeviceCount(fpURP);  // Get active USB devices
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_Start
//
// Description: This API routine configures the USB host controllers and
//      enumerate the devices
//
// Input: fpURPPointer  URP structure with input parameters
//        StartHc.wDataAreaFlag Indicates which data area to use
//
// Output: StartHc.wDataAreaFlag Returns current data area pointer
//         bRetValue - USB_SUCCESS on success, USB_ERROR on error.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_Start (URP_STRUC *fpURP)
{
    USB_DEBUG(DEBUG_LEVEL_3, "USBSMI: Start\n");
    USB_DEBUG(DEBUG_LEVEL_3, "\tUSBAPI_HC_Proc:%x\n", &USBAPI_HC_Proc);
    USB_DEBUG(DEBUG_LEVEL_3, "\tUSBAPI_Core_Proc:%x\n", &USBAPI_Core_Proc);
    USB_DEBUG(DEBUG_LEVEL_3, "\tUSB_ReConfigDevice:%x\n", &USB_ReConfigDevice);
    fpURP->bRetValue = USB_StartHostControllers (gUsbData);
    USB_DEBUG(DEBUG_LEVEL_3, "USB_StartHostControllers returns %d\n", fpURP->bRetValue);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_Stop
//
// Description: This routine stops the USB host controllers
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  bRetValue   USB_SUCCESS on success
//              USB_ERROR on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_Stop (URP_STRUC *fpURP)
{
    gCheckUsbApiParameter = FALSE;
    fpURP->bRetValue = USB_StopHostControllers (gUsbData);
    USB_DEBUG(DEBUG_LEVEL_3, "USB_StopHostControllers returns %d\n", fpURP->bRetValue);
    gUsbData->dUSBStateFlag &= ~(USB_FLAG_DRIVER_STARTED);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_PowerManageUSB
//
// Description: This routine suspends the USB host controllers
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_PowerManageUSB (URP_STRUC *fpURP)
{
    fpURP->bRetValue = USB_NOT_SUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_PrepareForOS
//
// Description: This routine updates data structures to reflect that
//      POST is completed
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_PrepareForOS (URP_STRUC *fpURP)
{
    fpURP->bRetValue = USB_NOT_SUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_SecureInterface
//
// Description: This routine handles the calls related to security device
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_SecureInterface (URP_STRUC *fpURP)
{
    fpURP->bRetValue = USB_NOT_SUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_DisableInterrupts
//
// Description: This routine stops the USB host controllers interrupts
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  bRetValue   USB_SUCCESS on success
//              USB_ERROR on error (Like data area not found)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_DisableInterrupts (URP_STRUC *fpURP)
{
    fpURP->bRetValue = USB_NOT_SUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_EnableInterrupts
//
// Description: This routine re-enable the USB host controller interrupts
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  bRetValue   USB_SUCCESS on success
//              USB_ERROR on error (Like data area not found)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_EnableInterrupts (URP_STRUC *fpURP)
{
    fpURP->bRetValue = USB_NOT_SUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_MoveDataArea
//
// Description: This routine stops the USB host controllers and moves
//      the data area used by host controllers to a new area.
//      The host controller is started from the new place.
//
// Input:   fpURPPointer    URP structure with input parameters
//      StartHc.wDataAreaFlag   Indicates which data area to use
//
// Output:  bRetValue   USB_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_MoveDataArea(URP_STRUC *fpURP)
{
    fpURP->bRetValue = USB_NOT_SUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_GetDeviceInfo
//
// Description: This routine returns the information regarding
//      a USB device like keyboard, mouse, floppy drive etc
//
// Input:   fpURPPointer            URP structure with input parameters
//          GetDevInfo.bDevNumber   Device number (1-based) whose
//                  information is requested
//
// Output:  URP structure is updated with the following information
//      GetDevInfo.bHCNumber - HC number in which the device is found
//      GetDevInfo.bDevType  - Type of the device
//      bRetValue will be one of the following value
//      USB_SUCCESS         on successfull completion
//      USB_PARAMETER_ERROR if bDevNumber is invalid
//      USB_ERROR           on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID USBAPI_GetDeviceInfo (URP_STRUC *fpURP)
{
    DEV_INFO* fpDevInfo;

    //
    // Initialize the return values
    //
    fpURP->ApiData.GetDevInfo.bHCNumber = 0;
    fpURP->ApiData.GetDevInfo.bDevType  = 0;
    fpURP->bRetValue                    = USB_ERROR;

    //
    // Check for parameter validity
    //
    if ( !fpURP->ApiData.GetDevInfo.bDevNumber ) return;

    fpURP->bRetValue = USB_PARAMETER_ERROR;

    //
    // Get the device information structure for the 'n'th device
    //
    fpDevInfo = USBWrap_GetnthDeviceInfoStructure(fpURP->ApiData.GetDevInfo.bDevNumber);
//  if (!wRetCode) return;  // USB_PARAMETER_ERROR

    //
    // Return value
    //
    fpURP->ApiData.GetDevInfo.bDevType  = fpDevInfo->bDeviceType;
    fpURP->ApiData.GetDevInfo.bHCNumber = fpDevInfo->bHCNumber;
    fpURP->bRetValue                    = USB_SUCCESS;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_CheckDevicePresence
//
// Description: This routine checks whether a particular type of USB device
//      is installed in the system or not.
//
// Input:   fpURPPointer            URP structure with input parameters
//          ChkDevPrsnc.bDevType    Device type to find
//          ChkDevPrsnc.fpHCStruc   Pointer to HC being checked for device
//            connection; if NULL then the total number of devices
//            connected to ANY controller is returned.
//          ChkDevPrsnc.bNumber     Number of devices connected
//
// Output:  bRetValue will be one of the following value
//          USB_SUCCESS     if device type present, ChkDevPrsnc.bNumber <> 0
//          USB_ERROR       if device type absent, ChkDevPrsnc.bNumber returns 0
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBAPI_CheckDevicePresence (URP_STRUC *fpURP)
{
    UINT8 bSearchFlag;
    UINTN dData;

    bSearchFlag = USB_SRCH_DEV_NUM;
    if (fpURP->bSubFunc == 1)
    {
        bSearchFlag = USB_SRCH_DEVBASECLASS_NUM;
    }
    //
    // The total number of devices connected to ANY controller has been requested
    //
    dData = (UINTN) USB_GetDeviceInfoStruc( bSearchFlag,
            0, fpURP->ApiData.ChkDevPrsnc.bDevType, fpURP->ApiData.ChkDevPrsnc.fpHCStruc);

    fpURP->ApiData.ChkDevPrsnc.bNumber = (UINT8)dData;
    fpURP->bRetValue = (UINT8)((fpURP->ApiData.ChkDevPrsnc.bNumber)?
                                            USB_SUCCESS : USB_ERROR);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMassAPIGetDeviceInformation
//
// Description: This function is part of the USB BIOS MASS API. This function
//      returns the device information of the mass storage device
//
// Input:   fpURPPointer    Pointer to the URP structure
//          bDevAddr    USB device address of the device
//
// Output:  bRetValue   Return value
//      fpURPPointer    Pointer to the URP structure
//          dSenseData  Sense data of the last command
//          bDevType    Device type byte (HDD, CD, Removable)
//          bEmuType    Emulation type used
//          fpDevId     Far pointer to the device ID
//          dInt13Entry INT 13h entry point
//
// Notes:   Initially the bDevAddr should be set to 0 as input. This
//      function returns the information regarding the first mass
//      storage device (if no device found it returns bDevAddr as
//      0FFh) and also updates bDevAddr to the device address of
//      the current mass storage device. If no other mass storage
//      device is found then the routine sets the bit7 to 1
//      indicating current information is valid but no more mass
//      device found in the system. The caller can get the next
//      device info if bDevAddr is not 0FFh and bit7 is not set
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMassAPIGetDeviceInformation (URP_STRUC *fpURP)
{
    fpURP->bRetValue = USBMassGetDeviceInfo (&fpURP->ApiData.MassGetDevInfo);
}

VOID
USBMassAPIGetDeviceParameters (URP_STRUC *fpURP)
{
    DEV_INFO    *DevInfo;
    EFI_STATUS  Status;

    DevInfo = fpURP->ApiData.MassGetDevParms.fpDevInfo;

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        return;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        Status = AmiValidateMemoryBuffer((VOID*)fpURP->ApiData.MassGetDevParms.fpInqData, sizeof(MASS_INQUIRY));
        if (EFI_ERROR(Status)) {
            return;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif
    
    fpURP->ApiData.MassGetDevParms.fpInqData = USBMassGetDeviceParameters(DevInfo);
    fpURP->bRetValue = (fpURP->ApiData.MassGetDevParms.fpInqData == NULL)? USB_ERROR : USB_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBMassAPIGetDevStatus
//
// Description: This function returns the drive status and media presence
//      status
//
// Input:       fpURPPointer    Pointer to the URP structure
//              fpURP->ApiData.fpDevInfo - pointer to USB device that is
//              requested to be checked
//
// Output:  Return code USB_ERROR - Failure, USB_SUCCESS - Success
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>

VOID
USBMassAPIGetDevStatus(URP_STRUC *fpURP)
{
#if USB_DEV_MASS
    fpURP->bRetValue    = USBMassGetDeviceStatus (&fpURP->ApiData.MassGetDevSts);
//    USB_DEBUG(DEBUG_LEVEL_3, "USBMassAPIGetDevStatus ... check function call correct?\n");
#endif
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMassAPIGetDeviceGeometry
//
// Description: This function is part of the USB BIOS MASS API.
//
// Input:   fpURPPointer    Pointer to the URP structure
//          bDevAddr    USB device address of the device
//
// Output:  bRetValue   Return value
//      fpURPPointer    Pointer to the URP structure
//          dSenseData  Sense data of the last command
//          bNumHeads   Number of heads
//          wNumCylinders   Number of cylinders
//          bNumSectors Number of sectors
//          wBytesPerSector Number of bytes per sector
//          bMediaType  Media type
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMassAPIGetDeviceGeometry(URP_STRUC *fpURP)
{
    fpURP->bRetValue = USBMassGetDeviceGeometry (&fpURP->ApiData.MassGetDevGeo);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMassAPIResetDevice
//
// Description: This function is part of the USB BIOS MASS API.
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  bRetValue   Return value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMassAPIResetDevice (URP_STRUC *fpURP)
{
    UINT8       bDevAddr;
    DEV_INFO    *fpDevInfo;
    UINT16      wResult;

    bDevAddr = fpURP->ApiData.MassReset.bDevAddr;

    //
    // Get the device info structure for the matching device address
    //
    fpDevInfo   = USB_GetDeviceInfoStruc(USB_SRCH_DEV_INDX, 0, bDevAddr, 0);
    if((fpDevInfo == NULL)|| (!(fpDevInfo->Flag & DEV_INFO_DEV_PRESENT))) {
		fpURP->bRetValue = USB_ATA_TIME_OUT_ERR;
        return;
    }
    //
    // Send Start/Stop Unit command to UFI class device only
    //
    fpURP->bRetValue    = USB_SUCCESS;
    if(fpDevInfo->bSubClass ==  SUB_CLASS_UFI) {
        wResult = USBMassStartUnitCommand (fpDevInfo);
        if (wResult) {
            fpURP->bRetValue  = USBWrapGetATAErrorCode(fpURP->ApiData.MassReset.dSenseData);
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMassAPIReadDevice
//
// Description: This function is part of the USB BIOS MASS API.
//
// Input:   fpURPPointer    Pointer to the URP structure, it contains the following:
//                  bDevAddr      USB device address of the device
//                  dStartLBA     Starting LBA address
//                  wNumBlks      Number of blocks to read
//                  wPreSkipSize  Number of bytes to skip before
//                  wPostSkipSize Number of bytes to skip after
//                  fpBufferPtr   Far buffer pointer
//
// Output: fpURPPointer Pointer to the URP structure
//                  bRetValue    Return value
//                  dSenseData   Sense data of the last command
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMassAPIReadDevice (
    URP_STRUC *Urp
)
{
    DEV_INFO    *DevInfo;
    UINT8       DevAddr;
    UINT16      Result;
    UINT32		Data = 0;
    UINT8       OpCode;

    DevAddr = Urp->ApiData.MassRead.DevAddr;

    if (((DevAddr == USB_HOTPLUG_FDD_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_FDD_ENABLED) == FALSE)) ||
        ((DevAddr == USB_HOTPLUG_HDD_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_HDD_ENABLED) == FALSE)) ||
        ((DevAddr == USB_HOTPLUG_CDROM_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_CDROM_ENABLED) == FALSE))) {
        Urp->bRetValue = USB_ATA_DRIVE_NOT_READY_ERR;
        return;
    }

    //
    // Get the device info structure for the matching device address
    //
    DevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_INDX, 0, DevAddr, 0);
    if ((DevInfo == NULL)|| (!(DevInfo->Flag & DEV_INFO_DEV_PRESENT))) {
		Urp->bRetValue = USB_ATA_TIME_OUT_ERR;
        return;
    }

											//(EIP15037+)>
#if EXTRA_CHECK_DEVICE_READY
    //
    // Check device ready
    //
    Data = USBMassCheckDeviceReady(DevInfo);
	if (Data) {
        Urp->ApiData.MassRead.dSenseData = Data;
        Urp->bRetValue = USBWrapGetATAErrorCode(Urp->ApiData.MassRead.dSenseData);	//(EIP31535)
		return;
	}
#endif
											//<(EIP15037+)

    //
    // Issue read command
    //
    if (Shr64(DevInfo->MaxLba, 32)) {
        OpCode = COMMON_READ_16_OPCODE;
    } else {
        OpCode = COMMON_READ_10_OPCODE;
    }
    Result = USBMassRWVCommand(DevInfo, OpCode, &Urp->ApiData.MassRead);
    //USB_DEBUG(DEBUG_LEVEL_3, " wr(%x):%x %x", DevAddr, Result, Urp->ApiData.MassRead.dSenseData);
    if (Result) {
        Urp->bRetValue = USB_SUCCESS;
        return;
    }
    Urp->bRetValue = USBWrapGetATAErrorCode(Urp->ApiData.MassRead.SenseData);
    //USB_DEBUG(DEBUG_LEVEL_3, " er(%x):%x", DevAddr, Urp->bRetValue);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMassAPIWriteDevice
//
// Description: This function is part of the USB BIOS MASS API.
//
// Input:   fpURPPointer    Pointer to the URP structure
//          bDevAddr    USB device address of the device
//          dStartLBA   Starting LBA address
//          wNumBlks    Number of blocks to write
//          wPreSkipSize    Number of bytes to skip before
//          wPostSkipSize   Number of bytes to skip after
//          fpBufferPtr Far buffer pointer
//
// Output:  fpURPPointer    Pointer to the URP structure
//          bRetValue   Return value
//          dSenseData  Sense data of the last command
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMassAPIWriteDevice(
    URP_STRUC *Urp
)
{
    DEV_INFO    *DevInfo;
    UINT8       DevAddr;
    UINT16      Result;
    UINT32		Data = 0;
    UINT8       OpCode;

    DevAddr = Urp->ApiData.MassWrite.DevAddr;

    if (((DevAddr == USB_HOTPLUG_FDD_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_FDD_ENABLED) == FALSE)) ||
        ((DevAddr == USB_HOTPLUG_HDD_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_HDD_ENABLED) == FALSE)) ||
        ((DevAddr == USB_HOTPLUG_CDROM_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_CDROM_ENABLED) == FALSE))) {
        Urp->bRetValue = USB_ATA_DRIVE_NOT_READY_ERR;
        return;
    }

    //
    // Get the device info structure for the matching device address
    //
    DevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_INDX, 0, DevAddr, 0);
    if((DevInfo == NULL)|| (!(DevInfo->Flag & DEV_INFO_DEV_PRESENT))) {
		Urp->bRetValue = USB_ATA_TIME_OUT_ERR;
        return;
    }
/*
    if (!(DevInfo->bLastStatus & USB_MASS_MEDIA_PRESENT)) {
        Urp->bRetValue = USB_ATA_NO_MEDIA_ERR;
        return;
    }
*/
											//(EIP15037+)>
#if EXTRA_CHECK_DEVICE_READY
    //
    // Check device ready
    //
    Data = USBMassCheckDeviceReady(DevInfo);
	if (Data) {
        Urp->ApiData.MassRead.dSenseData = Data;
        Urp->bRetValue = USBWrapGetATAErrorCode(Urp->ApiData.MassWrite.dSenseData);	//(EIP31535)
		return;
	}
#endif
											//<(EIP15037+)

    //
    // Issue write command
    //
    if (Shr64(DevInfo->MaxLba, 32)) {
        OpCode = COMMON_WRITE_16_OPCODE;
    } else {
        OpCode = COMMON_WRITE_10_OPCODE;
    }
    Result = USBMassRWVCommand(DevInfo, OpCode, &Urp->ApiData.MassWrite);
    if (Result) {
        Urp->bRetValue = USB_SUCCESS;
        return;
    }

    Urp->bRetValue = USBWrapGetATAErrorCode(Urp->ApiData.MassWrite.SenseData);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMassAPIVerifyDevice
//
// Description: This function is part of the USB BIOS MASS API.
//
// Input:   fpURPPointer    Pointer to the URP structure
//          bDevAddr    USB device address of the device
//          dStartLBA   Starting LBA address
//          wNumBlks    Number of blocks to write
//          wPreSkipSize    Number of bytes to skip before
//          wPostSkipSize   Number of bytes to skip after
//          fpBufferPtr Far buffer pointer
//
// Output:  fpURPPointer    Pointer to the URP structure
//          bRetValue   Return value
//          dSenseData  Sense data of the last command
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMassAPIVerifyDevice(
    URP_STRUC *Urp
)
{
    DEV_INFO    *DevInfo;
    UINT8       DevAddr;
    UINT16      Result;
    UINT32		Data = 0;
    UINT8       OpCode;

    DevAddr = Urp->ApiData.MassVerify.DevAddr;

    if (((DevAddr == USB_HOTPLUG_FDD_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_FDD_ENABLED) == FALSE)) ||
        ((DevAddr == USB_HOTPLUG_HDD_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_HDD_ENABLED) == FALSE)) ||
        ((DevAddr == USB_HOTPLUG_CDROM_ADDRESS) &&
            ((gUsbData->dUSBStateFlag & USB_HOTPLUG_CDROM_ENABLED) == FALSE))) {
        Urp->bRetValue = USB_ATA_DRIVE_NOT_READY_ERR;
        return;
    }

    //
    // Get the device info structure for the matching device address
    //
    DevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_INDX, 0, DevAddr, 0);
    if ((DevInfo == NULL)|| (!(DevInfo->Flag & DEV_INFO_DEV_PRESENT))) {
		Urp->bRetValue = USB_ATA_TIME_OUT_ERR;
        return;
    }
											//(EIP15037+)>
#if EXTRA_CHECK_DEVICE_READY
    //
    // Check device ready
    //
    Data = USBMassCheckDeviceReady(DevInfo);
	if (Data) {
        Urp->ApiData.MassRead.dSenseData = Data;
        Urp->bRetValue = USBWrapGetATAErrorCode(Urp->ApiData.MassVerify.dSenseData);	//(EIP31535)
		return;
	}
#endif
											//<(EIP15037+)

    //
    // Issue write command
    //
    if (Shr64(DevInfo->MaxLba, 32)) {
        OpCode = COMMON_VERIFY_16_OPCODE;
    } else {
        OpCode = COMMON_VERIFY_10_OPCODE;
    }
    Result = USBMassRWVCommand(DevInfo, OpCode, &Urp->ApiData.MassVerify);
    if (Result) {
        Urp->bRetValue = USB_SUCCESS;
        return;
    }

    Urp->bRetValue = USBWrapGetATAErrorCode(Urp->ApiData.MassVerify.SenseData);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMassAPIFormatDevice
//
// Description: This function is part of the USB BIOS MASS API.
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  bRetValue   Return value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMassAPIFormatDevice(URP_STRUC *fpURP)
{
    fpURP->bRetValue = USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMassAPICommandPassThru
//
// Description: This function is part of the USB BIOS MASS API. This
//      function can be used to pass raw command/data sequence to
//      the USB mass storage device
//
// Input:   fpURPPointer    Pointer to the URP structure
//
// Output:  bRetValue   Return value
//
// Modified:    Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMassAPICommandPassThru (URP_STRUC *fpURP)
{
    UINT8                   Result;
    MASS_CMD_PASS_THRU      *MassCmdPassThru;
    EFI_STATUS              Status = EFI_SUCCESS;

    MassCmdPassThru = &fpURP->ApiData.MassCmdPassThru;

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        Status = AmiValidateMemoryBuffer((VOID*)MassCmdPassThru->fpCmdBuffer, MassCmdPassThru->wCmdLength);
        if (EFI_ERROR(Status)) {
            return;
        }
        Status = AmiValidateMemoryBuffer((VOID*)MassCmdPassThru->fpDataBuffer, MassCmdPassThru->wDataLength);
        if (EFI_ERROR(Status)) {
            return;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    Result = USBMassCmdPassThru(MassCmdPassThru);
    
    fpURP->bRetValue = Result;
}


//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBMassAPIAssignDriveNumber
//
// Description: This function is part of the USB BIOS MASS API. This function
//      assigns the logical drive device according to the information of the
//      mass storage device
//
// Input:   fpURPPointer    Pointer to the URP structure
//      bDevAddr    USB device address of the device
//      bLogDevNum  Logical Drive Number to assign to the device
//
// Output:  Return code USB_ERROR - Failure, USB_SUCCESS - Success
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>

VOID
USBMassAPIAssignDriveNumber (URP_STRUC *fpURP)
{
    fpURP->bRetValue = USB_SUCCESS; // No errors expected after this point
}


//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBMassAPICheckDevStatus
//
// Description: This function is part of the USB BIOS MASS API. This function
//              invokes USB Mass Storage API handler to check whether device
//              is ready. If called for the first time, this function retrieves
//              the mass storage device geometry and fills the corresponding
//              fpDevInfo fields.
//
// Input:       fpURPPointer    Pointer to the URP structure
//              fpURP->ApiData.fpDevInfo - pointer to USB device that is
//              requested to be checked
//
// Output:  Return code USB_ERROR - Failure, USB_SUCCESS - Success
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>

VOID
USBMassAPICheckDevStatus(URP_STRUC *fpURP)
{
#if USB_DEV_MASS
    UINT32      Result;
    DEV_INFO    *DevInfo;
    EFI_STATUS  Status;

    DevInfo = fpURP->ApiData.MassChkDevReady.fpDevInfo;

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        return;
    }
	
	gCheckUsbApiParameter = FALSE;

    Result = USBMassCheckDeviceReady(fpURP->ApiData.MassChkDevReady.fpDevInfo);
    fpURP->bRetValue = (UINT8)Result;
#endif
}


//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_LightenKeyboardLEDs
//
// Description: This function is part of the USB BIOS API. This function
//              controls LED state on the connected USB keyboards
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:  Return code USB_ERROR - Failure, USB_SUCCESS - Success
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>

VOID
USBAPI_LightenKeyboardLEDs(URP_STRUC *fpURP)
{
#if USB_DEV_KBD

    gCheckUsbApiParameter = FALSE;

    if(fpURP->ApiData.KbLedsData.fpLedMap) {
        gUsbData->bUSBKBShiftKeyStatus = 0;
        if(((LED_MAP*)fpURP->ApiData.KbLedsData.fpLedMap)->NumLock) {
            gUsbData->bUSBKBShiftKeyStatus |= KB_NUM_LOCK_BIT_MASK;
        }
        if(((LED_MAP*)fpURP->ApiData.KbLedsData.fpLedMap)->CapsLock) {
            gUsbData->bUSBKBShiftKeyStatus |= KB_CAPS_LOCK_BIT_MASK;
        }
        if(((LED_MAP*)fpURP->ApiData.KbLedsData.fpLedMap)->ScrLock) {
            gUsbData->bUSBKBShiftKeyStatus |= KB_SCROLL_LOCK_BIT_MASK;
        }
    }
    //USB_DEBUG(DEBUG_LEVEL_3," LEDs: %d\n", gUsbData->bUSBKBShiftKeyStatus);
    USBKB_LEDOn();

    fpURP->bRetValue    = USB_SUCCESS;
    return;
#else
    fpURP->bRetValue    = USB_NOT_SUPPORTED;
#endif

}

VOID
USBAPI_LightenKeyboardLEDs_Compatible(URP_STRUC *fpURP)
{
    USBAPI_LightenKeyboardLEDs(fpURP);
}

					                        //(EIP29733+)>
//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_KbcAccessControl
//
// Description: This function is part of the USB BIOS API. This function
//              is used to control whether KBC access in USB module 
//              should be blocked or not.
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:      Return code USB_ERROR - Failure, USB_SUCCESS - Success
//
// Notes:
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>


VOID
UsbKbcAccessControl(
    UINT8 ControlSwitch
)
{
    UINT8       Index;
    HC_STRUC    *HcStruc;
#if USB_RUNTIME_DRIVER_IN_SMM
    EFI_STATUS Status = EFI_SUCCESS;
    
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);
    
    if (EFI_ERROR(Status)) {
        gLockHwSmiHandler = TRUE;
        gLockSmiHandler = TRUE;
        return;
    }
#endif

    gCheckUsbApiParameter = FALSE;

    IsKbcAccessBlocked = (ControlSwitch != 0)? TRUE : FALSE;

    for (Index = 0; Index < gUsbData->HcTableCount; Index++) {
        HcStruc = gUsbData->HcTable[Index];
        if (HcStruc == NULL) {
            continue;
        }
        if (HcStruc->dHCFlag & HC_STATE_RUNNING) {
            break;
        }
    }

    if (Index == gUsbData->HcTableCount) {
        return;
    }
/*
    //
    // Check if the USB access in Legacy mode. If it's legacy mode enable/disable
    // the Kbcemulation based on the ControlSwitch  
    //
    if(!(gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI)) {

        if(IsKbcAccessBlocked) {
            if(gEmulationTrap) { 
                //
                // Keyboard access blocked. Disable the Emulation
                //
                gEmulationTrap->TrapDisable(gEmulationTrap);
            }
        } else {
            if(gEmulationTrap) { 
                //
                // Keyboard access enabled. Enable the KbcEmulation
                //
                gEmulationTrap->TrapEnable(gEmulationTrap);
            }
        }
    }
*/
					//(EIP48323+)>
    //Reflush USB data buffer if intend to disable usb keyboard data throughput.
    if (IsKbcAccessBlocked) {
        USBKeyRepeat(NULL, 1);  // Disable Key repeat
        gUsbData->RepeatKey = 0;

		// Clear Legacy USB keyboard buffer
		MemFill(gUsbData->aKBCCharacterBufferStart, sizeof(gUsbData->aKBCCharacterBufferStart), 0);
		gUsbData->fpKBCCharacterBufferHead = gUsbData->aKBCCharacterBufferStart;
		gUsbData->fpKBCCharacterBufferTail = gUsbData->aKBCCharacterBufferStart;
		
		MemFill(gUsbData->aKBCScanCodeBufferStart, sizeof(gUsbData->aKBCScanCodeBufferStart), 0);
		gUsbData->fpKBCScanCodeBufferPtr = gUsbData->aKBCScanCodeBufferStart;
											
		MemFill(gUsbData->aKBCDeviceIDBufferStart, sizeof(gUsbData->aKBCDeviceIDBufferStart), 0);
		MemFill(gUsbData->aKBCShiftKeyStatusBufferStart, sizeof(gUsbData->aKBCShiftKeyStatusBufferStart), 0);
		
		MemFill(gUsbData->aKBInputBuffer, sizeof(gUsbData->aKBInputBuffer), 0);
    }
					//<(EIP48323+)
}


VOID
USBAPI_KbcAccessControl(URP_STRUC *fpURP)
{
    UsbKbcAccessControl(fpURP->ApiData.KbcControlCode);
}
					                        //<(EIP29733+)
//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USB_StopLegacy
//
// Description: This function is part of the USB BIOS API. This function init USB 
//             legacy support.
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:      None
//
// Notes:
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>
VOID
USB_StopLegacy(URP_STRUC *fpURP)
{
    //shutdown device first
    UINT8       bIndex;
    DEV_INFO    *fpDevInfo;
    HC_STRUC    *fpHCStruc;
    
    for (bIndex = 1; bIndex < MAX_DEVICES; bIndex ++){
        fpDevInfo = gUsbData->aDevInfoTable +bIndex;
        if ((fpDevInfo->Flag & 
            (DEV_INFO_VALID_STRUC |DEV_INFO_DEV_PRESENT)    ) ==   
            (DEV_INFO_VALID_STRUC |DEV_INFO_DEV_PRESENT)    ){
            //
            fpHCStruc = gUsbData->HcTable[fpDevInfo->bHCNumber - 1];
            //
            USB_StopDevice (fpHCStruc, fpDevInfo->bHubDeviceNumber, fpDevInfo->bHubPortNumber);
        }
    }

    StopControllerType(USB_HC_XHCI);    //(EIP57521+)
    StopControllerType(USB_HC_EHCI);
    StopControllerType(USB_HC_UHCI);
    StopControllerType(USB_HC_OHCI);
    
    //return as success
    fpURP->bRetValue    = USB_SUCCESS;
    
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USB_StartLegacy
//
// Description: This function is part of the USB BIOS API. This function init USB 
//             legacy support.
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:      None
//
// Notes:
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>
VOID
USB_StartLegacy(URP_STRUC *fpURP)
{
                                        //(EIP57521)>
    gUsbData->bHandOverInProgress = FALSE;
    //Start XHCI
    StartControllerType(USB_HC_XHCI);
    USB_EnumerateRootHubPorts(USB_HC_XHCI);
    //Start EHCI
    StartControllerType(USB_HC_EHCI);
    USB_EnumerateRootHubPorts(USB_HC_EHCI);
    //Start UHCI
    StartControllerType(USB_HC_UHCI);
    USB_EnumerateRootHubPorts(USB_HC_UHCI);
    //Start OHCI
    StartControllerType(USB_HC_OHCI);
    USB_EnumerateRootHubPorts(USB_HC_OHCI);
                                        //<(EIP57521)
    //return as success
  fpURP->bRetValue    = USB_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_LegacyControl
//
// Description: This function is part of the USB BIOS API. This function
//              is used to shutdown/init USB legacy support.
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:      None
//
// Notes:
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>
VOID USBAPI_LegacyControl (URP_STRUC *fpURP)
{
    UINT8 bSubLegacyFunc = fpURP->bSubFunc,i;       //(EIP102150+)
    UINT8 Count = (UINT8)(gUsbData->fpKBCScanCodeBufferPtr - 
                  (UINT8*)gUsbData->aKBCScanCodeBufferStart);   //(EIP102150+) 
                  
    gCheckUsbApiParameter = FALSE;

    USB_DEBUG(DEBUG_LEVEL_3, "USBAPI_LegacyControl %d\n", fpURP->bSubFunc);
    if(bSubLegacyFunc==STOP_USB_CONTROLLER){ 		//(EIP43475+)>  	
        USB_StopLegacy (fpURP);
                                        //(EIP102150+)>
    for(i = Count; i > 0; i--)
        USBKB_DiscardCharacter(&gUsbData->aKBCShiftKeyStatusBufferStart[i-1]); 
                                        //<(EIP102150+)
        if(gEmulationTrap) 
            gEmulationTrap->TrapDisable(gEmulationTrap);
    }

    if(bSubLegacyFunc==START_USB_CONTROLLER){
        USB_StartLegacy (fpURP);
        if(gEmulationTrap)
            gEmulationTrap->TrapEnable(gEmulationTrap);
    }												//<(EIP43475+)
    USB_DEBUG(DEBUG_LEVEL_3, "Result %d\n", fpURP->bRetValue);
}
										//(EIP74876+)>
//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_UsbStopController
//
// Description: This function is part of the USB BIOS API. This function stops 
//              the USB host controller.
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:      None
//
// Notes:
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>
VOID USBAPI_UsbStopController (URP_STRUC *fpURP)
{
    gCheckUsbApiParameter = FALSE;
	StopControllerBdf(fpURP->ApiData.HcBusDevFuncNum);
}
										//<(EIP74876+)
//-----------------------------------------------------
//
//-----------------------------------------------------
EFI_STATUS USBRT_LegacyControl (VOID *fpURP)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    EFI_STATUS Status = EFI_SUCCESS;
    
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);
    
    if (EFI_ERROR(Status)) {
        gLockHwSmiHandler = TRUE;
        gLockSmiHandler = TRUE;
        return EFI_SUCCESS;
    }
#endif
  //
  USBAPI_LegacyControl ((URP_STRUC *)fpURP);
  //
  return((EFI_STATUS)(((URP_STRUC *)fpURP)->bRetValue));
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_GetDeviceAddress
//
// Description: 
//
// Input:  
//
// Output: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBAPI_GetDeviceAddress(
    URP_STRUC *Urp
)
{
	UINT8		i;
	DEV_INFO	*DevInfo = NULL;

	for (i = 1; i < MAX_DEVICES; i++) {
		if (!(gUsbData->aDevInfoTable[i].Flag & DEV_INFO_VALID_STRUC)) {
			continue;
		}
		if ((gUsbData->aDevInfoTable[i].wVendorId == Urp->ApiData.GetDevAddr.Vid) && 
				(gUsbData->aDevInfoTable[i].wDeviceId == Urp->ApiData.GetDevAddr.Did)) {
			DevInfo = &gUsbData->aDevInfoTable[i];
		}
	}
	if (DevInfo == NULL) {
		Urp->bRetValue = USB_ERROR;
		return;
	}

	Urp->ApiData.GetDevAddr.DevAddr = DevInfo->bDeviceAddress;
	Urp->bRetValue = USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_ExtDriverRequest
//
// Description: 
//
// Input:  
//
// Output: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBAPI_ExtDriverRequest (
    URP_STRUC *Urp
)
{
    DEV_INFO	*DevInfo = NULL;
    DEV_DRIVER	*DevDriver;

	DevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR, 0, Urp->ApiData.DevAddr, 0);
	if (DevInfo == NULL) {
		Urp->bRetValue = USB_ERROR;
		return;
	}

    DevDriver = UsbFindDeviceDriverEntry(DevInfo->fpDeviceDriver);

	if (DevDriver != NULL) {
		DevDriver->pfnDriverRequest(DevInfo, Urp);
	}
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USB_StopUnsupportedHc
//
// Description: This routine is called, from host controllers that supports
//				OS handover functionality, when OS wants the BIOS to hand-over 
//				the host controllers to the OS.  This routine will stop HC that 
//				does not support this functionality.
//
// Input:       None
//
// Output:      None
//
// Notes:
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>

VOID
USB_StopUnsupportedHc()
{

#if USB_RUNTIME_DRIVER_IN_SMM
    UINT8       Index;
    HC_STRUC*   HcStruc;
    EFI_STATUS  Status;
    
    Status = AmiUsbSmmGlobalDataValidation(gUsbData);

    ASSERT_EFI_ERROR(Status);
    
    if (EFI_ERROR(Status)) {
        gLockHwSmiHandler = TRUE;
        gLockSmiHandler = TRUE;
        return;
    }
    
	USBSB_UninstallTimerHandlers();

    USB_DEBUG(DEBUG_LEVEL_3, "Stopping all external HCs");
    for (Index = 0; Index < gUsbData->HcTableCount; Index++) {
        HcStruc = gUsbData->HcTable[Index];
        if (HcStruc == NULL) {
            continue;
        }
        if (HcStruc->HwSmiHandle != NULL) {
            continue;
        }
        if (HcStruc->dHCFlag & HC_STATE_RUNNING) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDStop)(HcStruc);
            USB_DEBUG(DEBUG_LEVEL_3, ".");
        }
    }
    
    USB_DEBUG(DEBUG_LEVEL_3, "\n");

#endif

	if(gUsbData->UsbXhciHandoff) {
		StopControllerType(USB_HC_XHCI);
	}
	if(gUsbData->UsbEhciHandoff) {
		gUsbData->bHandOverInProgress = TRUE;
		StopControllerType(USB_HC_EHCI);
	}
	if(gUsbData->UsbOhciHandoff) {
		StopControllerType(USB_HC_OHCI);
	}
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_ChangeOwner
//
// Description: This function is part of the USB BIOS API. This function
//              updates the global variables according to the new owner
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:      Return code USB_ERROR - Failure, USB_SUCCESS - Success
//
// Notes:       It is a caller responsibility to release the keyboard only if it
//              was previously acquired.
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>

VOID
USBAPI_ChangeOwner(URP_STRUC *fpURP)
{
//USB_DEBUG(DEBUG_LEVEL_3, "USBAPI_ChangeOwner..");

    if(fpURP->ApiData.Owner) {  // Changing to Efi driver
//USB_DEBUG(DEBUG_LEVEL_3, "fpURP->ApiData.Owner=%d\n", fpURP->ApiData.Owner);
        if(gEmulationTrap) {
            gEmulationTrap->TrapDisable(gEmulationTrap);
        }
        gUsbData->dUSBStateFlag |= USB_FLAG_RUNNING_UNDER_EFI;
    } else {    // Acquiring - check the current condition first
//USB_DEBUG(DEBUG_LEVEL_3, "fpURP->ApiData.Owner=%d...", fpURP->ApiData.Owner);
        if(gEmulationTrap) {
            gEmulationTrap->TrapEnable(gEmulationTrap);
        }

        if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {
//USB_DEBUG(DEBUG_LEVEL_3, "USB_FLAG_RUNNING_UNDER_EFI\n");
            gUsbData->dUSBStateFlag &= ~USB_FLAG_RUNNING_UNDER_EFI;
        } else {
//USB_DEBUG(DEBUG_LEVEL_3, "not USB_FLAG_RUNNING_UNDER_EFI\n");
        }
    }
    fpURP->bRetValue = USB_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_HcStartStop
//
// Description: This function is part of the USB BIOS API. This function 
//              starts/stops the USB host controller.
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:      None
//
// Notes:
//
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>

VOID
USBAPI_HcStartStop(URP_STRUC *Urp)
{
    HC_STRUC*   HcStruc;
    EFI_STATUS  Status;

    HcStruc = Urp->ApiData.HcStartStop.HcStruc;

    Status = UsbHcStrucValidation(HcStruc);

    if (EFI_ERROR(Status)) {
        return;
    }

    if ((HcStruc->bHCType != USB_HC_UHCI) && (HcStruc->bHCType != USB_HC_OHCI) &&
        (HcStruc->bHCType != USB_HC_EHCI) && (HcStruc->bHCType != USB_HC_XHCI)) {
        return;
    }

    gCheckUsbApiParameter = FALSE;

    if (Urp->ApiData.HcStartStop.Start) {
        Urp->bRetValue = UsbHcStart(HcStruc);
    } else {
        Urp->bRetValue = UsbHcStop(HcStruc);
    }
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_invoke_in_frame
//
// Description: Invokes procedure passing parameters supplied in the buffer
//      It replicates the stack frame so that target procedure can
//      see the parameters passed to the stub.
//
// Output:  Returns result of invoked proc
//
//------------------------------------------------------------------------------
//<AMI_PHDR_END>

//
// The following typedef corresponds to the min width type that can be passed
// into function call as a parameter without padding
//
typedef UINTN STACKWORD;

UINTN 
USBAPI_invoke_in_frame(
    VOID* pProc,
    VOID* buffer,
    UINT32 paramSize )
{
    STACKWORD* params = (STACKWORD*)buffer;

    switch(paramSize/sizeof(STACKWORD)){
    case 0: return ((STACKWORD (*)())pProc)();
    case 1: return ((STACKWORD (*)(STACKWORD))pProc)(params[0]);
    case 2: return ((STACKWORD (*)(STACKWORD,STACKWORD))pProc)(params[0],
                params[1]);
    case 3: return ((STACKWORD (*)(STACKWORD,STACKWORD,STACKWORD))pProc)(
                params[0],params[1],params[2]);
    case 4: return ((STACKWORD (*)(STACKWORD,STACKWORD,STACKWORD,
                STACKWORD))pProc)(
                params[0],params[1],params[2],params[3]);
    case 5: return ((STACKWORD (*)(STACKWORD,STACKWORD,STACKWORD,STACKWORD,
                STACKWORD))pProc)(
                params[0],params[1],params[2],params[3],params[4]);
    case 6: return ((STACKWORD (*)(STACKWORD,STACKWORD,STACKWORD,STACKWORD,
                STACKWORD,STACKWORD))pProc)(
                params[0],params[1],params[2],params[3],params[4],params[5]);
    case 7: return ((STACKWORD (*)(STACKWORD,STACKWORD,STACKWORD,STACKWORD,
                STACKWORD,STACKWORD,STACKWORD))pProc)(
                params[0],params[1],params[2],params[3],params[4],params[5],
                params[6]);
    default:
        ASSERT(paramSize/sizeof(STACKWORD) < 4);
        return 0;
    }
/*  kept for reference
    __asm {
        push    ecx
        push    esi
        pushf
                        //Copy stak frame
        std
        mov     esi, buffer
        mov     ecx, paramSize
        add     esi, ecx
        sub     esi, 4
        shr     ecx, 2
loop1:
        lodsd   //DWORD PTR ds:edi
        push    eax
        loop    loop1
                        //Call proc
        mov     eax, pProc
        cld
        call    eax
                        //Read return value
        mov     retVal, eax

                        //Restore stack and registers
        add     esp, paramSize
        popf
        pop     esi
        pop     ecx
    }
    return retVal;*/
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_HC_Proc
//
// Description: Bridge to a number of procedures supplied by HC driver
//
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:  Return code USB_ERROR - Failure, USB_SUCCESS - Success)
//
// Notes:
//      Assumes that buffer has a correct image of the stack that
//      corresponding function reads argument from
//      Size of the buffer can be biger than actually used.
//
//      Following code copies the buffer (some stack frame) into new
//      stack frame such that invoked dirver proc can read parametes
//      supplied by buffer
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>

VOID USBAPI_HC_Proc(URP_STRUC *fpURP)
{
    VOID* buffer = fpURP->ApiData.HcProc.paramBuffer;
    UINT32 paramSize = // align size on DWORD
        (fpURP->ApiData.HcProc.paramSize + 3) & ~0x3;
    UN_HCD_HEADER* pHdr;

    ASSERT( GET_HCD_INDEX(fpURP->ApiData.HcProc.bHCType) <
        sizeof(gUsbData->aHCDriverTable)/sizeof(HCD_HEADER));
    ASSERT( fpURP->bSubFunc < sizeof(pHdr->asArray.proc)/sizeof(VOID*));

    pHdr = (UN_HCD_HEADER*)(gUsbData->aHCDriverTable +
                GET_HCD_INDEX(fpURP->ApiData.HcProc.bHCType));
    fpURP->ApiData.HcProc.retVal = USBAPI_invoke_in_frame(
        pHdr->asArray.proc[fpURP->bSubFunc],buffer,paramSize);
    fpURP->bRetValue = USB_SUCCESS;
}


//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Procedure:   USBAPI_Core_Proc
//
// Description: Bridge to a number of procedures supplied by Core proc table
//
// Input:       fpURP   Pointer to the URP structure
//
// Output:  Return code USB_ERROR - Failure, USB_SUCCESS - Success
//
// Notes:
//      Assumes that buffer has a correct image of the stack that
//      corresponding function reads argument from
//      Size of the buffer can be biger than actually used.
//
//      Following code copies the buffer (some stack frame) into new
//      stack frame such that invoked proc can read parametes
//      supplied by buffer
//------------------------------------------------------------------------------;
//<AMI_PHDR_END>


VOID* core_proc_table[] = {
        USB_GetDescriptor,
        USB_ReConfigDevice,
        USB_ReConfigDevice2,
        UsbAllocDevInfo,
        prepareForLegacyOS,
        USB_ResetAndReconfigDev,
        USB_DevDriverDisconnect,
//        USB_GetDataPtr,
//        MemCopy,
    };

VOID USBAPI_Core_Proc(URP_STRUC *fpURP)
{
    VOID* buffer = fpURP->ApiData.CoreProc.paramBuffer;
    UINT32 paramSize = // align size on DWORD
        (fpURP->ApiData.CoreProc.paramSize + 3) & ~0x3;

    ASSERT( fpURP->bSubFunc < COUNTOF(core_proc_table));

    fpURP->ApiData.CoreProc.retVal = USBAPI_invoke_in_frame(
        core_proc_table[fpURP->bSubFunc],buffer,paramSize);

    fpURP->bRetValue = USB_SUCCESS;
}


//----------------------------------------------------------------------------
//          USB API Procedures Ends
//----------------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBWrapGetATAError
//
// Description: This routine converts the sense data information into
//      ATAPI error code
//
// Input:   dSenseData  Sense data obtained from the device
//
// Output:  BYTE - ATAPI error code
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 USBWrapGetATAErrorCode (UINT32 dSenseData)
{
    UINT8   sc = (UINT8)dSenseData;             // Sense code
    UINT8   asc = (UINT8)(dSenseData >> 16);    // Additional Sense Code (ASC)
    UINT8   ascq = (UINT8)(dSenseData >> 8);    // Additional Sense Code Qualifier (ASCQ)

    if (ascq == 0x28) return USB_ATA_DRIVE_NOT_READY_ERR;
    if (sc == 7) return USB_ATA_WRITE_PROTECT_ERR;
    if ((asc == 0x80) && (ascq == 0x80)) return USB_ATA_TIME_OUT_ERR;
    if (ascq == 0x18) return USB_ATA_DATA_CORRECTED_ERR;
    if ((ascq==6) && (asc == 0)) return USB_ATA_MARK_NOT_FOUND_ERR;
    if ((ascq==0x3a) && (asc == 0)) return USB_ATA_NO_MEDIA_ERR;
    if ((ascq==0x11) && (asc == 0)) return USB_ATA_READ_ERR;
    if ((ascq==0x11) && (asc == 6)) return USB_ATA_UNCORRECTABLE_ERR;
    if (ascq==0x30) return USB_ATA_BAD_SECTOR_ERR;
    if ((ascq<0x20) || (ascq>0x26)) return USB_ATA_GENERAL_FAILURE;

    return USB_ATA_PARAMETER_FAILED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBWrap_GetnthDeviceInfoStructure
//
// Description: This routine finds the 'n'th device's DeviceInfo entry.
//
// Input:   bDevNumber  Device number (1-based)
//
// Output:  DeviceInfo structure
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USBWrap_GetnthDeviceInfoStructure(UINT8 bDevNumber)
{
    return &gUsbData->aDevInfoTable[bDevNumber];
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBWrap_GetDeviceCount
//
// Description: This routine searches through the device entry table
//      and returns number of active USB devices configured
//      by the BIOS.
//
// Input:   fpURPPointer    Pointer to the URP
//
// Output:  Following fields in the URP are modified
//      CkPresence.bNumBootDev      Number of USB boot devices found
//      CkPresence.bNumKeyboards    Number of USB keyboards present
//      CkPresence.bNumMice         Number of USB mice present
//      CkPresence.bNumHubs         Number of USB hubs present
//      CkPresence.bNumStorage      Number of USB storage devices present
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBWrap_GetDeviceCount(URP_STRUC *fpURP)
{
    DEV_INFO    *fpDevInfo;
    UINT8       i;

    for (i=1; i<MAX_DEVICES; i++) {
        fpDevInfo   = &gUsbData->aDevInfoTable[i];

        if ( (fpDevInfo->Flag & DEV_INFO_VALID_STRUC) &&
            (fpDevInfo->Flag & DEV_INFO_DEV_PRESENT)) {
            fpURP->ApiData.CkPresence.bNumBootDev++;

            switch (fpDevInfo->bDeviceType) {
				case BIOS_DEV_TYPE_HID:
                    if (fpDevInfo->HidDevType & HID_DEV_TYPE_KEYBOARD) {
                        fpURP->ApiData.CkPresence.bNumKeyboards++;
                    }
                    if (fpDevInfo->HidDevType & HID_DEV_TYPE_MOUSE) {
                        fpURP->ApiData.CkPresence.bNumMice++;
                    }
                    if (fpDevInfo->HidDevType & HID_DEV_TYPE_POINT) {
                        fpURP->ApiData.CkPresence.bNumPoint++;
                    }
					break;
										//<(EIP84455+)
                case  BIOS_DEV_TYPE_HUB:
                            fpURP->ApiData.CkPresence.bNumHubs++;
                            break;
                case  BIOS_DEV_TYPE_STORAGE:
                            fpURP->ApiData.CkPresence.bNumStorage++;
                            break;
                case  BIOS_DEV_TYPE_SECURITY:
                            break;
            }
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MemFill
//
// Description: This routine fills the given memory range with the given value.
//
// Input:
//    fpPtr    - Pointer to the memory region to fill.
//    wSize    - Size in bytes of the area to be filled.
//    Value    - Byte value to fill the given range with.
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
MemFill (
    UINT8*  fpPtr,
    UINT32  dSize,
    UINT8   Value)
{
    UINT32      dCount;

    if (fpPtr) {    // Check for pointer validity
        for(dCount = 0; dCount < dSize; dCount++) {
            fpPtr[dCount] = Value;
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MemCopy
//
// Description: This routine copies data from source to destination.
//
// Input:
//    fpSrc    - Pointer to the source.
//    fpDest   - Pointer to the destination.
//    wSize    - Number of bytes to copy.
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
MemCopy (
    UINT8*  fpSrc,
    UINT8*  fpDest,
    UINT32  dSize)
{
    UINT32  dCount;

    //
    // Check for pointer validity
    //
    if ((fpSrc) && (fpDest)) {
        for(dCount = 0; dCount < dSize; dCount++) {
            fpDest[dCount] = fpSrc[dCount];
        }
    }
}


UINTN DevicePathSize (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
    EFI_DEVICE_PATH_PROTOCOL     *Start;

    if (DevicePath == NULL) {
        return 0;
    }

    //
    // Search for the end of the device path structure
    //
    Start = DevicePath;
    while (!EfiIsDevicePathEnd (DevicePath)) {
        DevicePath = EfiNextDevicePathNode (DevicePath);
    }

    //
    // Compute the size and add back in the size of the end device path structure
    //
    return ((UINTN)DevicePath - (UINTN)Start) + sizeof(EFI_DEVICE_PATH_PROTOCOL);
}


EFI_DEVICE_PATH_PROTOCOL *
AppendDevicePath (
    IN EFI_DEVICE_PATH_PROTOCOL  *Src1,
    IN EFI_DEVICE_PATH_PROTOCOL  *Src2
    )
{
    EFI_STATUS                  Status;
    UINTN                       Size;
    UINTN                       Size1;
    UINTN                       Size2;
    EFI_DEVICE_PATH_PROTOCOL    *NewDevicePath;
    EFI_DEVICE_PATH_PROTOCOL    *SecondDevicePath;

    //
    // Allocate space for the combined device path. It only has one end node of
    // length EFI_DEVICE_PATH_PROTOCOL
    //
    Size1 = DevicePathSize (Src1);
    Size2 = DevicePathSize (Src2);
    Size = Size1 + Size2;

    if (Size1 != 0 && Size2 != 0) {
        Size -= sizeof(EFI_DEVICE_PATH_PROTOCOL);
    }

    Status = gBS->AllocatePool (EfiBootServicesData, Size, (VOID **)&NewDevicePath);

    if (EFI_ERROR(Status)) {
        return NULL;
    }

    gBS->CopyMem (NewDevicePath, Src1, Size1);

    //
    // Over write Src1 EndNode and do the copy
    //
    if (Size1 != 0) {
        SecondDevicePath = (EFI_DEVICE_PATH_PROTOCOL *)((CHAR8 *)NewDevicePath + (Size1 - sizeof(EFI_DEVICE_PATH_PROTOCOL)));
    }
    else {
        SecondDevicePath = NewDevicePath;
    }
    gBS->CopyMem (SecondDevicePath, Src2, Size2);
    return NewDevicePath;
}

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
