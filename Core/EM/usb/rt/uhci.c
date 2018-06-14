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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/uhci.c 114   10/16/16 10:12p Wilsonlee $
//
// $Revision: 114 $
//
// $Date: 10/16/16 10:12p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/uhci.c $
// 
// 114   10/16/16 10:12p Wilsonlee
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
// 113   7/22/16 3:50a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 112   7/07/16 1:09a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 111   3/14/16 10:21p Wilsonlee
// [TAG]  		EIP257506
// [Category]  	Improvement
// [Description]  	Add USB_KEYREPEAT_INTERVAL token to change the key
// repeat interval.
// [Files]  		usb.sdl, xhci.h, usbkbd.h, uhci.c, ohci.c, ehci.c
// 
// 110   3/02/16 9:41p Wilsonlee
// [TAG]  		EIP254309
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	GK-FORCE K83 USB KB function abnormal.
// [RootCause]  	This device has an interrupt out endpoint and doesn't
// support "Set Report" request.
// [Solution]  	Use the interrupt out endpoint instead of sending "Set
// Report" request.
// [Files]  		AmiUsbController.h, xhci.c, usbmass.c, usbkbd.h, usbkbd.c,
// usbhub.c, usbhid.c, usbdef.h, usbCCID.c, usb.c, uhci.c, ohci.c, ehci.c,
// amiusb.h, efiusbms,c, amiusbhc.c
// 
// 109   12/03/15 1:48a Wilsonlee
// [TAG]  		EIP247625
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB hot-plug function is failed in external uhci
// controllers.
// [RootCause]  	We don't install UhciRootHubQhCallBack for external uhci
// controllers.
// [Solution]  	Handle the hot-plug function in the periodic timer smi
// handler if the uhci controller is external.
// [Files]  		uhci.c
// 
// 108   4/10/15 3:11a Wilsonlee
// [TAG]  		EIP207413
// [Category]  	Improvement
// [Description]  	Install UsbApiTable and UsbMassApitTable in
// AmiUsbSmmProtocol.
// [Files]  		amiusbhc.c, AmiUsbController.h, usbdef.h, usbCCID.c, uhci.c,
// ehci.c, amiusbrtCCID.h, amiusb.h, amiusb.c, uhcd.c
// 
// 107   3/08/15 10:49p Wilsonlee
// [TAG]  		EIP207774
// [Category]  	Improvement
// [Description]  	Set USB_FLAG_DRIVER_STARTED flag when HC is running and
// clear it if we don't start any HC.
// [Files]  		uhci.c, usb.c, ehci.c, ohci.c, xhci.c, amiusb.h
// 
// 106   1/22/15 10:19p Wilsonlee
// [TAG]  		EIP201434
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Number of connected devices isn't correct if we plug out
// keyboards or mice behind hub in xhci.
// [RootCause]  	The PortConnectChange bit is cleared when we check port
// status for interrupt endpoint transaction error.
// [Solution]  	Don't clear change bits if we check port status for
// interrupt endpoint transaction error.
// [Files]  		xhci.c, usbhub.c, usbdef.h, usb.c, uhci.c, ohci.c, ehci.c,
// amiusbhc.c
// 
// 105   6/26/14 1:15a Wilsonlee
// [TAG]  		EIP173387
// [Category]  	Improvement
// [Description]  	Remove TODO comments.
// [Files]  		usbsetup.c, xhci.c, usbmass.c, usbCCID.c, usb.c, uhci.c,
// syskbc.c, usbport.c, usbbus.c, uhcd.c, UsbBotPeim.c, PeiXhci.c,
// PeiEhci.c
// 
// 104   5/01/14 3:57a Ryanchou
// [TAG]  		EIP162589
// [Category]  	Improvement
// [Description]  	Do not register external controller as key repeat
// controller.
// [Files]  		ehci.c, ohci.c, uhci.c
// 
// 103   4/30/14 8:56a Ryanchou
// [TAG]  		EIP160289
// [Category]  	Improvement
// [Description]  	Handle zero length of short packet.
// [Files]  		uhci.c
// 
// 102   4/30/14 6:13a Ryanchou
// [TAG]  		EIP151374
// [Category]  	Improvement
// [Description]  	Calculates maximum data length to be reported in the
// HID device.
// [Files]  		ehci.c, ohci.c, uhci.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, xhci.c
// 
// 101   2/26/14 1:55a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 100   9/24/13 5:39a Ryanchou
// [TAG]  		EIP132985 
// [Category]  	Improvement
// [Description]  	Clear the SMI enable bit if UHCI is not controlled by
// BIOS.
// [Files]  		uhci.c
// 
// 99    8/16/13 2:15a Ryanchou
// 
// 98    7/26/13 2:40a Ryanchou
// [TAG]  		EIP122142
// [Category]  	Improvement
// [Description]  	Improve periodic schedule mechanism
// [Files]  		ehci.c, ehci.h, ohci.c, ohci.h, uhci.c, uhci.h, usbdef.h,
// amiusbhc.c
// 
// 97    7/22/13 10:31p Wilsonlee
// [TAG]  		EIP125357
// [Category]  	Improvement
// [Description]  	Check if the port releases to a select host controller.
// [Files]  		uhci.c, usb.c, usbhub.c, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 96    6/02/13 11:42p Wilsonlee
// [TAG]  		EIP123235
// [Category]  	Improvement
// [Description]  	Stop the usb host controller at ExitBootService if it
// is an extend card or it doesn't support HW SMI.
// [Files]  		xhci.c, ehci.c, uhci.c, ohci.c, amiusb.c, usbdef.h, usbsb.c,
// uhcd.c
// 
// 95    4/16/13 6:45a Ryanchou
// [TAG]  		EIP118912
// [Category]  	Improvement
// [Description]  	Add VIA VT6212 EHCI controller support.
// [Files]  		ehci.c, uhci.c, usbdef.h, uhcd.c
// 
// 94    3/19/13 3:58a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 93    3/18/13 4:49a Ryanchou
// [TAG]  		EIP98377
// [Category]  	Improvement
// [Description]  	Optimize USB controller timing.
// [Files]  		usb.sdl, usbport.c, ehci.c, elib.c, ohci.c, uhci.c,
// usbdef.h, usbhub.c, xhci.c, uhcd.c
// 
// 92    2/24/13 9:00p Wilsonlee
// [TAG]  		EIP113541
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	System hangs at checkpoint 0xA2 when Win8 resume from S4.
// [RootCause]  	The "HCHalted" bit and "Port Change Detect" bit are set
// when the system S4 resume to Win8 OS.
// [Solution]  	We need to clear the interrupt status even if the
// "HCHalted" bit is set.
// [Files]  		ehci.c, ohci.c, uhci.c
// 
// 91    12/06/12 12:39a Wilsonlee
// [TAG]  		EIP103186
// [Category]  	Improvement
// [Description]  	Handle the error case "MEMIO was disabled" in USB
// driver.
// [Files]  		uhci.c, ohci.c, ehci.c, xhci.c
// 
// 90    11/22/12 9:21p Wilsonlee
// [TAG]  		EIP106887
// [Category]  	New Feature
// [Description]  	Support usb S5 wake up function for UHCI.
// [Files]  		usb.c, uhci.c, uhci.h
// 
// 89    11/10/12 6:48a Ryanchou
// 
// 88    11/10/12 6:39a Ryanchou
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
// 87    9/28/12 2:37a Wilsonlee
// [TAG]  		EIP93154
// [Category]  	Improvement
// [Description]  	Change the unit of the FixedDelay from 15 us to 1 us.
// [Files]  		amiusb.h, xhci.c, ehci.c, ohci.c, uhci.c, usb.c, usbCCID.c,
// usbmass.c, usbhub.c, elib.c
// 
// 86    8/29/12 8:17a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 85    5/04/12 6:39a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 84    5/03/12 6:23a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 83    11/08/11 1:56a Ryanchou
// [TAG]  		EIP63188
// [Category]  	Improvement
// [Description]  	External USB controller support.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, uhcd.c, uhcd.h, uhci.c,
// usbdef.h, usbmisc.c, usbsb.c, xhci.c
// 
// 82    9/26/11 11:43p Roberthsu
// [TAG]  		EIP67230
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Ntrig touch panel can not use on CedarTrail
// [RootCause]  	Because ntrig report data over than 512 byte.Control
// transfer check if over 512 than set length is 512.
// [Solution]  	Remove check transfer length.
// [Files]  		ohci.c,uhci.c,usbhid.c
// 
// 81    8/08/11 6:59a Ryanchou
// [TAG]  		EIP54018
// [Category]  	New Feature
// [Description]  	Added USB S5 wake up support.
// [Files]  		amiusb.c, ehci.c, ohci.c, uhci.c, usb.c, usb.sdl, usbdef.h,
// usbsb.c xhci.c
// 
// 80    8/08/11 5:15a Ryanchou
// [TAG]  		EIP60561
// [Category]  	New Feature
// [Description]  	Add USB timing policy protocol for timing override.
// [Files]  		ehci.c, guids.c, ohci.c, uhcd.c, uhci.c usb.c, usbdef.h,
// usbhub.c, usbmass.c, UsbPolicy.h, usbport.c usbsrc.sdl
// 
// 79    7/15/11 6:11a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c, usb.c, usbdef.h,
// usbkbd.c, usbkbd.h, usbms.c, usbrt.cif, usbsb.c, usbsetup.c,
// usbsrc.sdl, xhci.c
// 
// 78    7/13/11 4:09a Ryanchou
// [TAG]  		EIP59332
// [Category]  	Improvement
// [Description]  	Modified the Stop function for UHCD and USBBUS to
// properly stop devices and uninstall the protocols.
// [Files]  		uhcd.c, uhcd.h, uhci.c, usbbus.c, UsbInt13.c, usbmisc.c
// 
// 77    7/12/11 8:09a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
// 76    7/01/11 3:19a Ryanchou
// [TAG]  		EIP61385
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	USB devices can't detected.
// [RootCause]  	This is the side effect of EIP59663, the port status
// doesn't reflect connect status and connect status change.
// [Solution]  	Add 100 us delay.
// [Files]  		ehci.c, uhci.c
// 
// 75    6/22/11 1:44a Ryanchou
// [TAG]  		EIP59738
// [Category]  	Improvement
// [Description]  	Support Block size other than 512 bytes USB HDD in UEFI
// mode.
// [Files]  		efiusbmass.c, uhci.c, usb.c, usbdef.h, usbmass.c
// 
// 74    5/03/11 10:09a Ryanchou
// [TAG]  		EIP54283
// [Category]  	Improvement
// [Description]  	Follow XHCI spec ver 1.0 section 4.6.8 to recovery
// endpoint halt. 
// [Files]  		ehci.c, ohci.c, uhci.c, usbdef.h, usbmass.c, xhci.c
// 
// 73    4/06/11 1:33a Ryanchou
// [TAG]  		EIP54782
// [Category]  	Improvement
// [Description]  	Change polling data size of HID devices to max packet
// size of interrupt endpoint.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, xhci.c
// 
// 72    3/29/11 10:51p Ryanchou
// [TAG]  		EIP55401
// [Category]  	Improvement
// [Description]  	Improve the USB 3.0 device compatibility.
// [Files]  		ehci.c, ehci.h, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c,
// xhci.c
// 
// 71    3/29/11 10:08a Ryanchou
// [TAG]  		EIP53518
// [Category]  	Improvement
// [Description]  	Added chipset xHCI chip support.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhcd.c, uhci.c, usb.c,
// usb.sdl, usbdef.h, usbport, usbsb.c, xhci.c
// 
// 70    11/11/10 11:35p Ryanchou
// [TAG]  		EIP45578
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB 3.0 device can't be detected.
// [RootCause]  	Address Device Command fails.
// [Solution]  	Reset the device and attempt the Address Device Command
// again.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c, xhci.c
// 
// 69    9/24/10 5:38p Olegi
// EIP38221: Added the code that properly initializes
// DEV_INFO.bIntEndpoint field; interrupt endpoint polling is using this
// endpoint number.
// 
// 68    9/07/10 4:11a Tonylo
// Remove user tags for coding standard.
// 
// 67    8/18/10 4:22p Olegi
// Klockwork related fixes; EIP37978
// 
// 66    4/30/10 3:36p Fredericko
// Fixed EIP : 38028: USB AutoKeyRepeat is not working properly
// 
// 65    3/10/10 6:35p Olegi
// 
// 64    3/10/10 10:51a Olegi
// Function headers corrected.
// 
// 63    3/06/10 1:11p Olegi
// 
// 62    2/26/10 4:23p Olegi
// 
// 61    2/08/10 10:11a Olegi
// EIP33381: Implement multiple bulk endpoint in UsbIoProtocol.
// 
// 60    2/08/10 9:40a Olegi
// EIP34448: Changes in UHCIWaitForTransferComplete and transfer routines.
// 
// 59    1/26/10 4:35p Olegi
// 
// 55    12/23/09 11:59a Olegi
// 
// 54    12/22/09 8:57a Olegi
// 
// 53    12/10/09 10:06a Olegi
// Added timeout in UHCI_WaitForBulkTransferComplete, EIP32048.
// 
// 52    11/13/09 12:37p Olegi
// 
// 51    10/30/09 5:47p Olegi
// 
// 50    10/07/09 9:48a Olegi
// USB Hub error handling improvement. EIP#25601.
// 
// 49    9/15/09 10:21a Olegi
// Added USB_INCMPT_HID_DATA_OVERFLOW incompatibility type.
// 
// 48    8/26/09 11:41a Olegi
// Changes that prevent collision of keyboard activity and mass storage
// access. EIP#22808
// 
// 47    2/23/09 12:56p Olegi
// 
// 46    2/20/09 4:43p Olegi
// 
// 45    2/17/09 4:01p Olegi
// 
// 44    2/17/09 8:58a Olegi
// 
// 43    2/06/09 4:06p Olegi
// 
// 42    1/16/09 3:50p Olegi
// Optimization in BulkTransfer scheduling.
// 
// 41    10/06/08 3:33p Olegi
// EHCI change ownership testing in DOS fix (EIP#14855).
// 
// 40    9/02/08 10:29a Olegi
// EIP14855 bugfix: change ownership request is not processed properly in
// case of multiple controllers of the same type.
// 
// 39    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 38    2/05/08 3:13p Olegi
// Bugfix in BulkTdCallback that showed when data TD returns with stall
// condition.
// 
// 37    12/17/07 4:04p Olegi
// KBC emulation support added.
// 
// 36    10/15/07 5:13p Olegi
// ControlTransfer cleanup.
// 
// 35    9/26/07 9:15a Olegi
// Added USB_FORCE_64BIT_ALIGNMENT flag as well as a call ty sync the LEDs
// between keyboards in DOS.
// 
// 34    9/21/07 5:10p Davidd
// Allocation TDs is forced to be 64-bytes aligned.
// 
// 33    9/06/07 6:12p Olegi
// 
// 32    9/06/07 5:52p Olegi
// Tracker 27603 fix added.
// 
// 31    8/14/07 11:56a Olegi
// Reverted buggy BulkTransfer changes to make floppy work.
// 
// 30    8/14/07 10:59a Olegi
// 
// 29    7/09/07 2:11p Olegi
// Changed the maximum data size of the BulkTransfer from 1kB to 64kB.
// 
// 28    4/17/07 6:13p Fredericko
// Modified UHCI_EnableRootHub to preserve the Connect Status Change bit.
// 
// 27    4/17/07 8:24a Olegi
// Device detection algorythm update, in sync with Core8.
// 
// 26    3/20/07 12:18p Olegi
//
// 25    1/26/07 2:52p Olegi
// Bugfix in UHCI_BulkTDCallback.
//
// 24    1/25/07 4:25p Olegi
//
// 23    1/25/07 10:19a Olegi
//
// 22    1/02/07 2:08p Olegi
//
// 21    12/28/06 5:27p Olegi
//
// 20    12/26/06 10:52a Olegi
//
// 19    12/20/06 2:30p Olegi
//
// 17    10/19/06 5:24p Andriyn
//
// 15    10/12/06 9:37p Andriyn
// Fix: unexpected plug-off hangs with endless TIMEOUTs
//
// 14    7/10/06 2:57p Andriyn
// Fix: double delocation of descriptors used for control transfer
//
// 13    6/29/06 11:54a Andriyn
// Removed commented code
//
// 12    4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 11    3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 10    3/06/06 6:23p Olegi
//
// 9     11/29/05 12:33p Andriyn
//
// 8     9/23/05 12:01p Olegi
//
// 7     9/23/05 11:58a Olegi
//
// 6     8/27/05 3:43p Andriyn
// Fix: lost mouse click when mouse is not moving
//
// 5     8/11/05 9:53a Olegi
// 60/64 port emulation related fixes for EMU6064 driver.
//
// 4     6/03/05 6:08p Olegi
// HW SMI registration change.
//
// 3     5/19/05 8:07p Olegi
// Aptio changes in driver 8.1 implementation.
//
// 2     5/17/05 7:51p Andriyn
// USB BUS pre-release
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           Uhci.c
//
//  Description:    AMI USB UHCI driver
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "amiusb.h"
#include "usbkbd.h"
#if USB_RUNTIME_DRIVER_IN_SMM
#include <AmiBufferValidationLib.h>
#endif

extern  VOID*       USB_MemAlloc (UINT16);
extern  UINT8       USB_MemFree  (VOID _FAR_ *,  UINT16);
extern  UINT8       USBCheckPortChange (HC_STRUC*, UINT8, UINT8);
extern  UINT8       USB_InstallCallBackFunction (CALLBACK_FUNC);

extern  UINT32      ReadPCIConfig(UINT16, UINT8);
extern  VOID        WordWritePCIConfig(UINT16, UINT8, UINT16);
extern  UINT8       ByteReadIO(UINT16);
extern  VOID        ByteWriteIO(UINT16, UINT8);
extern  UINT16      WordReadIO(UINT16);
extern  VOID        WordWriteIO(UINT16, UINT16);
extern  UINT32      DwordReadIO(UINT16);
extern  VOID        DwordWriteIO(UINT16, UINT32);
extern  VOID        FixedDelay(UINTN);
extern  DEV_INFO*   USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);
extern  UINT8       USBLogError(UINT16);
extern  VOID        USB_InitFrameList (HC_STRUC*, UINT32);
#if USB_DEV_KBD
extern  VOID        USBKBDPeriodicInterruptHandler(HC_STRUC*);
extern  VOID        USBKeyRepeat(HC_STRUC*, UINT8);
#endif

UINT8   USB_DisconnectDevice (HC_STRUC*, UINT8, UINT8);
UINT8	UsbGetDataToggle(DEV_INFO*,UINT8);
VOID	UsbUpdateDataToggle(DEV_INFO*, UINT8, UINT8);

//---------------------------------------------------------------------------

// Public function declaration
UINT8   UHCI_Start (HC_STRUC*);
UINT8   UHCI_Stop (HC_STRUC*);
UINT8   UHCI_EnumeratePorts (HC_STRUC*);
UINT8   UHCI_DisableInterrupts (HC_STRUC*);
UINT8   UHCI_EnableInterrupts (HC_STRUC*);
UINT8   UHCI_ProcessInterrupt(HC_STRUC*);
UINT8   UHCI_GetRootHubStatus (HC_STRUC*,UINT8, BOOLEAN);
UINT8   UHCI_DisableRootHub (HC_STRUC*,UINT8);
UINT8   UHCI_EnableRootHub (HC_STRUC*,UINT8);
UINT8   UHCI_ResetRootHub (HC_STRUC*,UINT8);
UINT16  UHCI_ControlTransfer (HC_STRUC*,DEV_INFO*,UINT16,UINT16,UINT16,UINT8*,UINT16);
UINT32  UHCI_BulkTransfer (HC_STRUC*,DEV_INFO*,UINT8,UINT8*,UINT32);
UINT16  UHCI_InterruptTransfer (HC_STRUC*, DEV_INFO*, UINT8, UINT16, UINT8*, UINT16);
UINT8   UHCI_DeactivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   UHCI_ActivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   UHCI_DisableKeyRepeat (HC_STRUC*);
UINT8   UHCI_EnableKeyRepeat (HC_STRUC*);
UINT8   UHCI_GlobalSuspend (HC_STRUC*);	//(EIP54018+)

UINT8   UhciProcessQh (HC_STRUC*, UHCI_QH*);
UINT8   UhciProcessTd (HC_STRUC*, UHCI_TD*);
UINT8   UhciProcessFrameList (HC_STRUC*);

UINT8   UHCI_DisableHCPorts (HC_STRUC*);
UINT8   UHCI_StartTDSchedule (HC_STRUC*);
UINT8   UHCI_StopTDSchedule (HC_STRUC*);
UINT8   UHCI_InterruptTDCallback (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*);
UINT8   UhciAddQhToFrameList (HC_STRUC*, UHCI_QH*);
UINT8   UhciRemoveQhFromFrameList (HC_STRUC*, UHCI_QH*);
VOID    UhciInitQh (UHCI_QH*);
BOOLEAN UhciIsHalted(HC_STRUC*);
UINT8   UhciTranslateInterval(UINT8);

UHCI_TD*
UhciAllocGeneralTds (
	IN UINT8		DeviceAddr,
	IN BOOLEAN		LowSpeed,
	IN UINT8		PacketId,
	IN UINT8        EndpointAddr,
	IN UINT16		MaxPacket,
	IN BOOLEAN		ShortPacket,
    IN OUT UINTN    *BufferAddr,
    IN OUT UINT32   *Length,
    IN OUT UINT8    *DataToggle
);

VOID
UhciFreeTds (
	IN UHCI_TD	*FirstTd
);

VOID
UhciActivateTds (
	IN UHCI_TD	*FirstTd,
	IN UINT8	DataToggle
);

extern  USB_GLOBAL_DATA *gUsbData;
extern  BOOLEAN gCheckUsbApiParameter;

UINT8   UhciRootHubQhCallBack(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   UhciRepeatQhCallback (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   UhciPollingQhCallback (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_FillHCDEntries
//
// Description:
//  This function fills the host controller driver routine pointers
//
// Input:
//  fpHCDHeader     Ptr to the host controller header structure
//
// Output:
//  USB_SUCCESS = Success, USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_FillHCDEntries(HCD_HEADER *fpHCDHeader)
{
    //
    // Fill the routines here
    //
    fpHCDHeader->pfnHCDStart                = UHCI_Start;
    fpHCDHeader->pfnHCDStop                 = UHCI_Stop;
    fpHCDHeader->pfnHCDEnumeratePorts       = UHCI_EnumeratePorts;
    fpHCDHeader->pfnHCDDisableInterrupts    = UHCI_DisableInterrupts;
    fpHCDHeader->pfnHCDEnableInterrupts     = UHCI_EnableInterrupts;
    fpHCDHeader->pfnHCDProcessInterrupt     = UHCI_ProcessInterrupt;
    fpHCDHeader->pfnHCDGetRootHubStatus     = UHCI_GetRootHubStatus;
    fpHCDHeader->pfnHCDDisableRootHub       = UHCI_DisableRootHub;
    fpHCDHeader->pfnHCDEnableRootHub        = UHCI_EnableRootHub;
    fpHCDHeader->pfnHCDControlTransfer      = UHCI_ControlTransfer;
    fpHCDHeader->pfnHCDBulkTransfer         = UHCI_BulkTransfer;
    fpHCDHeader->pfnHCDInterruptTransfer    = UHCI_InterruptTransfer;
    fpHCDHeader->pfnHCDDeactivatePolling    = UHCI_DeactivatePolling;
    fpHCDHeader->pfnHCDActivatePolling      = UHCI_ActivatePolling;
    fpHCDHeader->pfnHCDDisableKeyRepeat     = UHCI_DisableKeyRepeat;
    fpHCDHeader->pfnHCDEnableKeyRepeat      = UHCI_EnableKeyRepeat;
    fpHCDHeader->pfnHCDEnableEndpoints      = USB_EnableEndpointsDummy;
    fpHCDHeader->pfnHCDInitDeviceData       = USB_InitDeviceDataDummy;
    fpHCDHeader->pfnHCDDeinitDeviceData     = USB_DeinitDeviceDataDummy;
	fpHCDHeader->pfnHCDResetRootHub         = UHCI_ResetRootHub;
	fpHCDHeader->pfnHCDClearEndpointState	= 0;	//(EIP54283+)
	fpHCDHeader->pfnHCDGlobalSuspend        = UHCI_GlobalSuspend;	//(EIP54018+)

    USB_InstallCallBackFunction(UhciPollingQhCallback);
    USB_InstallCallBackFunction(UhciRepeatQhCallback);
    USB_InstallCallBackFunction(UhciRootHubQhCallBack);

    return  USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:     UHCI_Start
//
// Description:
//  This API function is called to start a UHCI host controller. The input to the
//  routine is the pointer to the HC structure that defines this host controller
//
// Input:
//  fpHCStruc   Ptr to the host controller structure
//
// Output:
//  Status: USB_SUCCESS = Success, USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_Start (HC_STRUC*   fpHCStruc)
{
    UINT16  wIOAddr;
    UINT16  LegSupReg;
    UINT16  Index;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    
#if USB_RUNTIME_DRIVER_IN_SMM
    EfiStatus = AmiValidateMmioBuffer((VOID*)fpHCStruc->fpFrameList, 0x1000);
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
#endif

/*
USB_DEBUG(DEBUG_LEVEL_3, "Enabling IO/BM for UHCI HC %02X\n", fpHCStruc->wBusDevFuncNum);
    //
    // Enable IO access and Bus Mastering
    //
    WordWritePCIConfig((UINT16)fpHCStruc->wBusDevFuncNum, 4, BIT0 + BIT2);
*/
    //
    // Set number of root hub ports present
    //
    fpHCStruc->bNumPorts = 2;

    //
    // Get the I/O base address for the host controller
    //
    wIOAddr = (UINT16)ReadPCIConfig((UINT16)fpHCStruc->wBusDevFuncNum, USB_IO_BASE_ADDRESS);

    //
    // Mask the low order two bits and store the value in HCStruc
    //
    wIOAddr = (UINT16)(wIOAddr & (~(BIT0+BIT1)));
    USB_DEBUG(DEBUG_LEVEL_4, "HC I/O Address : %X\n", wIOAddr);
    fpHCStruc->BaseAddress = wIOAddr;

    fpHCStruc->wAsyncListSize   = UHCI_FRAME_LIST_SIZE;

    //
    // Disable hardware interrupt generation by programming legacy registers
    //
    LegSupReg = (UINT16)ReadPCIConfig((UINT16)fpHCStruc->wBusDevFuncNum, USB_UHCI_REG_LEGSUP);

    //
    // Disable generation of SMI/IRQ and clear status bits
    //
    LegSupReg = (UINT16)(LegSupReg & (~BIT4));
    WordWritePCIConfig((UINT16)fpHCStruc->wBusDevFuncNum, USB_UHCI_REG_LEGSUP, LegSupReg);

    //
    // Disable the interrupts (to aVOID spurious interrupts)
    //
    UHCI_DisableInterrupts(fpHCStruc);

    //
    // Disable the host controller root hub ports
    //
    UHCI_DisableHCPorts(fpHCStruc);

    //
    // Check whether HC is already stopped
    //
    if (!UhciIsHalted(fpHCStruc)) {
        //
        // HC is still running. Stop it by programming HC run bit
        //
        ByteWriteIO ((UINT16)(wIOAddr + UHCI_COMMAND_REG),
            ByteReadIO((UINT16)(wIOAddr + UHCI_COMMAND_REG)) & ~UHC_HOST_CONTROLLER_RUN);

        //
        // Check whether the host controller is halted (check for 50 ms)
        //
        for (Index = 0; Index < 500; Index++) {
            if ((ByteReadIO((UINT16)(wIOAddr + UHCI_STATUS_REG))) & UHC_HC_HALTED) {
                break;
            }
            FixedDelay(100);      // 100 us delay
        }
    }
    ASSERT((ByteReadIO((UINT16)(wIOAddr + UHCI_STATUS_REG))) & UHC_HC_HALTED);
    if (!((ByteReadIO((UINT16)(wIOAddr + UHCI_STATUS_REG))) & UHC_HC_HALTED)) {
        return USB_ERROR;
    }

    //
    // Reset the host controller
    //
    ByteWriteIO((UINT16)(wIOAddr + UHCI_COMMAND_REG), UHC_GLOBAL_RESET);
	
    FixedDelay(10 * 1000);    // Recommended 10msec delay, UHCI Spec, p.12, GRESET description
	
    ByteWriteIO((UINT16)(wIOAddr + UHCI_COMMAND_REG), 0);

    //
    // Memory has been allocated in AMIUHCD
    //
    if (!fpHCStruc->fpFrameList) {
        return USB_ERROR;
    }

    USB_InitFrameList (fpHCStruc, UHCI_TERMINATE);

    //
    // Program frame list pointer to the HC
    //
    USB_DEBUG(DEBUG_LEVEL_4, "Frame list pointer : %x\n", fpHCStruc->fpFrameList);
    DwordWriteIO((UINT16)(wIOAddr + UHCI_FRAME_LIST_BASE), (UINT32)(UINTN)fpHCStruc->fpFrameList);

    USB_DEBUG(DEBUG_LEVEL_6, "UHCI_StartTDSchedule\n");

    //
    // Start the TD schedule
    //
    if (UHCI_StartTDSchedule(fpHCStruc) != USB_SUCCESS)
        return USB_ERROR;

#if USB_RUNTIME_DRIVER_IN_SMM
    //
    // Enable hardware interrupt generation by programming legacy registers
    //
    if (!(fpHCStruc->dHCFlag & HC_STATE_EXTERNAL)) {
        LegSupReg = (UINT16)ReadPCIConfig(fpHCStruc->wBusDevFuncNum, USB_UHCI_REG_LEGSUP);
        // Enable generation of SMI/IRQ
        LegSupReg = (UINT16)(LegSupReg | BIT4) & ~BIT13;
        WordWritePCIConfig((UINT16)fpHCStruc->wBusDevFuncNum, USB_UHCI_REG_LEGSUP, LegSupReg);
    }
#endif
    //
    // Start the host controller by setting the run and configure bit
    //
    WordWriteIO((UINT16)(wIOAddr + UHCI_COMMAND_REG),
        UHC_HOST_CONTROLLER_RUN |
        UHC_CONFIGURE_FLAG |
        UHC_MAX_PACKET_64_BYTE);

    //
    // Enable interrupt generation
    //
//  WordWriteIO((UINT16)(wIOAddr + UHCI_INTERRUPT_ENABLE), (UHC_IOC_ENABLE | UHC_TIMEOUT_CRC_ENABLE));
    WordWriteIO((UINT16)(wIOAddr + UHCI_INTERRUPT_ENABLE), UHC_IOC_ENABLE);

    fpHCStruc->dHCFlag |= HC_STATE_RUNNING;

    // Set USB_FLAG_DRIVER_STARTED flag when HC is running.
    if (!(gUsbData->dUSBStateFlag & USB_FLAG_DRIVER_STARTED)) {
        gUsbData->dUSBStateFlag |= USB_FLAG_DRIVER_STARTED;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    //
    // Register the USB HW SMI handler
    //
    if (!(fpHCStruc->dHCFlag & HC_STATE_EXTERNAL)) {
        UsbInstallHwSmiHandler(fpHCStruc);
    } else {
        USBSB_InstallUsbIntTimerHandler();
	}
#endif

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_Stop
//
// Description:
//  This API function is called to stop the UHCI controller. The input to the
//  routine is the pointer to the HC structure that defines this host controller.
//
// Input:
//  fpHCStruc   Ptr to the host controller structure
//
// Output:
//  Status: USB_SUCCESS = Success, USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_Stop (HC_STRUC* fpHCStruc)
{
	UINT16	wIOAddr = (UINT16)fpHCStruc->BaseAddress;
    UINT16  LegSupReg;
    UINT16  Index;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }
    //
    // Disable hardware interrupt generation by programming legacy registers
    //
    if (!(fpHCStruc->dHCFlag & HC_STATE_EXTERNAL)) {
        LegSupReg = (UINT16)ReadPCIConfig((UINT16)fpHCStruc->wBusDevFuncNum, USB_UHCI_REG_LEGSUP);

        //
        // Disable generation of SMI/IRQ and clear status bits
        //
        LegSupReg = (UINT16)(LegSupReg & ~(BIT4));
        WordWritePCIConfig((UINT16)fpHCStruc->wBusDevFuncNum, USB_UHCI_REG_LEGSUP, LegSupReg);
    }

    //
    // Disable the host controller interrupt generation
    //
    UHCI_DisableInterrupts (fpHCStruc);

	// Disconnect all devices	
	USB_DisconnectDevice(fpHCStruc, fpHCStruc->bHCNumber | BIT7, 1);
	USB_DisconnectDevice(fpHCStruc, fpHCStruc->bHCNumber | BIT7, 2);

    //
    // Stop the host controller
    //
    if (!UhciIsHalted(fpHCStruc)) {
        //
        // Clear HC run bit
        //
        ByteWriteIO ((UINT16)(wIOAddr + UHCI_COMMAND_REG),
            ByteReadIO((UINT16)(wIOAddr + UHCI_COMMAND_REG)) & ~(UHC_HOST_CONTROLLER_RUN));

        //
        // Check whether the host controller is halted (check for 50 ms)
        //
        for (Index = 0; Index < 500; Index++) {
            if ((ByteReadIO((UINT16)(wIOAddr + UHCI_STATUS_REG))) & UHC_HC_HALTED) {
                break;
            }
            FixedDelay(100);      // 100 us delay
        }
    }
    ASSERT((ByteReadIO((UINT16)(wIOAddr + UHCI_STATUS_REG))) & UHC_HC_HALTED);

    // Reset the host controller
    ByteWriteIO((UINT16)(wIOAddr + UHCI_COMMAND_REG), UHC_GLOBAL_RESET);
	// Recommended 10msec delay, UHCI Spec, p.12, GRESET description
    FixedDelay(10 * 1000);
    ByteWriteIO((UINT16)(wIOAddr + UHCI_COMMAND_REG), 0);

    //
    // Clear the frame list pointers
    //
    USB_InitFrameList (fpHCStruc, UHCI_TERMINATE);

    //
    // Disable and free the TD schedule data structures
    //
    UHCI_StopTDSchedule (fpHCStruc);

    //
    // Set the HC state to stopped
    //
    fpHCStruc->dHCFlag  &= ~(HC_STATE_RUNNING);

    CheckBiosOwnedHc();

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_EnumeratePorts
//
// Description:
//  This API function is called to enumerate the root hub ports in the UHCI
//  controller. The input to the routine is the pointer to the HC structure
//  that defines this host controller
//
// Input:
//  fpHCStruc   Ptr to the host controller structure
//
// Output:
//  Status: USB_SUCCESS = Success, USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_EnumeratePorts(HC_STRUC* fpHCStruc)
{
    UINT8       bHCNumber;
    UINT16      wIOAddr, wPortAddr;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (UhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}

    wIOAddr = (UINT16)fpHCStruc->BaseAddress;

//(USB0061+)>
    //
    // Check whether USB host controllers are accessible to aVOID system 
    // hang in ports enumeration.
    //
    if (ByteReadIO(wIOAddr) == 0xFF) return USB_ERROR;
//<(USB0061+)
    //
    // Check whether enumeration is already began
    //
    if(gUsbData->bEnumFlag == TRUE) return USB_SUCCESS;

    gUsbData->bEnumFlag = TRUE;
    bHCNumber = (UINT8)(fpHCStruc->bHCNumber | BIT7);
										//(EIP61385)>
    //
    // Process Port#1 and clear Port#1 status bit
    //
    wPortAddr = wIOAddr + UHCI_PORT1_CONTROL;
	if ((WordReadIO(wPortAddr) & (UHC_CONNECT_STATUS_CHANGE | 
		UHC_CONNECT_STATUS)) == UHC_CONNECT_STATUS_CHANGE) {
		 WordWriteIO(wPortAddr, UHC_CONNECT_STATUS_CHANGE);
	}
    USBCheckPortChange(fpHCStruc, bHCNumber, 1);
    WordWriteIO(wPortAddr, WordReadIO(wPortAddr));

    //
    // Process Port#2 and clear Port#2 status bit
    //
    wPortAddr = wIOAddr + UHCI_PORT2_CONTROL;
	if ((WordReadIO(wPortAddr) & (UHC_CONNECT_STATUS_CHANGE | 
		UHC_CONNECT_STATUS)) == UHC_CONNECT_STATUS_CHANGE) {
		 WordWriteIO(wPortAddr, UHC_CONNECT_STATUS_CHANGE);
	}
    USBCheckPortChange(fpHCStruc, bHCNumber, 2);
    WordWriteIO(wPortAddr, WordReadIO(wPortAddr));
										//<(EIP61385)
    gUsbData->bEnumFlag = FALSE;

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_DisableInterrupts
//
// Description:
//  This API function is called to disable the interrupts generated by the UHCI
//  host controller. The input to the routine is the pointer to the HC structure
//  that defines this host controller.
//
// Input:
//  fpHCStruc   Ptr to the host controller structure
//
// Output:
//  Status: USB_SUCCESS = Success, USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_DisableInterrupts (HC_STRUC* fpHCStruc)
{
    UINT8   IntEnReg;    
    UINT16  IoAddr = (UINT16)fpHCStruc->BaseAddress;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    IntEnReg = ByteReadIO((UINT16)(IoAddr + UHCI_INTERRUPT_ENABLE));
    IntEnReg &= ~(UHC_IOC_ENABLE);
    ByteWriteIO((UINT16)(IoAddr + UHCI_INTERRUPT_ENABLE), IntEnReg);

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_EnableInterrupts
//
// Description:
//  This function enables the HC interrupts
//
// Input:
//  fpHCStruc   Pointer to the HCStruc structure
//
// Output:
//  USB_SUCCESS of USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_EnableInterrupts (HC_STRUC* fpHCStruc)
{
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_ProcessInterrupt
//
// Description:
//  This function is called when the USB interrupt bit is set. This function
//  will parse through the TDs and QHs to find out completed TDs and call
//  their respective callback functions.
//
// Input:
//  fpHCStruc   Pointer to the HCStruc structure
//
// Output:
//  USB_ERROR - Need more Interrupt processing
//  USB_SUCCESS - No interrupts pending
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_ProcessInterrupt(
    HC_STRUC    *HcStruc
)
{
    UINT16  IoPort = (UINT16)HcStruc->BaseAddress;
	UINT16  LegSupReg = 0;
    UINT16  UsbSts = 0;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

	if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
		return USB_ERROR;
	}

#if USB_RUNTIME_DRIVER_IN_SMM
	if (!(HcStruc->dHCFlag & HC_STATE_EXTERNAL)) {
		LegSupReg = (UINT16)ReadPCIConfig(HcStruc->wBusDevFuncNum, USB_UHCI_REG_LEGSUP);
		if (!(LegSupReg & BIT4)) {
			return USB_ERROR;
		}
	}
#endif

    //
    // Check whether the controller is still under BIOS control
    // Read the frame list base address and compare with stored value
    //
    if (((UINTN)DwordReadIO(IoPort + UHCI_FRAME_LIST_BASE) & 0xFFFFF000) != 
        (UINTN)HcStruc->fpFrameList) {
#if USB_RUNTIME_DRIVER_IN_SMM
        if (!(HcStruc->dHCFlag & HC_STATE_EXTERNAL)) {
			// Disable the SMI on IRQ enable bit
			WordWritePCIConfig(HcStruc->wBusDevFuncNum, USB_UHCI_REG_LEGSUP, LegSupReg & ~BIT4);
		}
#endif
        return USB_ERROR; // Control is not with us anymore
    }

    UsbSts = WordReadIO(IoPort + UHCI_STATUS_REG);

	if (UsbSts & UHC_HC_HALTED) {
		return USB_ERROR;
	}

    if (UsbSts & UHC_USB_INTERRUPT) {
		WordWriteIO(IoPort + UHCI_STATUS_REG, UsbSts);
        UhciProcessFrameList(HcStruc);
    }

    if (HcStruc->dHCFlag & HC_STATE_EXTERNAL) {
        UhciRootHubQhCallBack(HcStruc, NULL, NULL, NULL, 0);
    }

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_GetRootHubStatus
//
// Description:
//  This function returns the port connect status for the root hub port
//
// Input:
//  pHCStruc    Pointer to HCStruc of the host controller
//  bPortNum    Port in the HC whose status is requested
//
// Output:
//  NewPortNum  Port in the HC that can possibly replace bPortNum
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_GetRootHubStatus(
    HC_STRUC*   fpHCStruc,
    UINT8       bPortNum,
    BOOLEAN     ClearChangeBits
)
{
    UINT16  wPortAddr, wPortStatus, wPortTemp;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    wPortStatus = USB_PORT_STAT_DEV_OWNER;
    wPortAddr = (UINT16)((bPortNum<<1)+UHCI_PORT1_CONTROL-2+fpHCStruc->BaseAddress);

    //
    // Read the port status
    //
    wPortTemp = WordReadIO(wPortAddr);
	USB_DEBUG(3, "UHCI port[%d] status: %04x\n", bPortNum, wPortTemp);

    //
    // Check for port connect status
    //
    if (wPortTemp & UHC_CONNECT_STATUS) {
        wPortStatus |= USB_PORT_STAT_DEV_CONNECTED;

        //
        // Identify the speed of the device (full or low speed)
        //
        if (wPortTemp & UHC_LOW_SPEED_ATTACHED) {
            wPortStatus |= USB_PORT_STAT_DEV_LOWSPEED;
        }
        else {
            wPortStatus |= USB_PORT_STAT_DEV_FULLSPEED;
        }

		if (wPortTemp & UHC_PORT_ENABLE) {
			wPortStatus |= USB_PORT_STAT_DEV_ENABLED;
		}
    }

    //
    // Check for connect status change
    //
    if (wPortTemp & UHC_CONNECT_STATUS_CHANGE) {
        wPortStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED;
        if (ClearChangeBits == TRUE) {
		    WordWriteIO(wPortAddr, UHC_CONNECT_STATUS_CHANGE);		//(EIP61385+)
        }
    }

    return  (UINT8)wPortStatus;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_DisableRootHub
//
// Description:
//  This function disables the root hub of the UHCI controller.
//
// Input:
//  fpHCStruc   Pointer to HCStruc of the host controller
//  bPortNum    Root port to be disabled
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_DisableRootHub (HC_STRUC* fpHCStruc,UINT8 bPortNum)
{
    UINT16 wPortAddr =
        (UINT16)(fpHCStruc->BaseAddress + (bPortNum << 1) + UHCI_PORT1_CONTROL - 2);
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    //
    // Reset the enable bit
    //
    WordWriteIO(
        wPortAddr,
        (UINT16)(WordReadIO(wPortAddr) & (~UHC_PORT_ENABLE)));

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_EnableRootHub
//
// Description:
//  This function enables the root hub port specified
//
// Input:
//  fpHCStruc   Pointer to HCStruc of the host controller
//  bPortNum    Root port to be enabled
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_EnableRootHub (
    HC_STRUC    *HcStruc,
    UINT8       PortNum)
{
	UINT16 PortStatus;
    UINT16 PortAddr =
        (UINT16)(HcStruc->BaseAddress + (PortNum << 1) + UHCI_PORT1_CONTROL - 2);
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

	PortStatus = WordReadIO(PortAddr);

    //
    // Set the enable & reset bit, preserve Connect Status Change bit
    //
	PortStatus &= ~(UHC_CONNECT_STATUS_CHANGE | UHC_PORT_ENABLE_CHANGE);
    WordWriteIO(PortAddr, PortStatus | UHC_PORT_RESET);

    //
    // Wait for 10ms
    //
    FixedDelay(10 * 1000);  // 10msec delay

    //
    // Clear the reset bit and set the enable, preserve Connect Status Change bit
    //
	PortStatus = WordReadIO(PortAddr);
	PortStatus &= ~(UHC_CONNECT_STATUS_CHANGE | UHC_PORT_ENABLE_CHANGE);
    WordWriteIO(PortAddr, PortStatus & (~UHC_PORT_RESET));

    // Wait 1 ms for stabilize the port status
    FixedDelay(1 * 1000);        // 1 ms delay

    // Clear Connect Status Change bit and Port Enable Change bit
    WordWriteIO(PortAddr, WordReadIO(PortAddr));

    //
    // Set the enable bit
    //
    PortStatus = WordReadIO(PortAddr);
    PortStatus &= ~(UHC_CONNECT_STATUS_CHANGE | UHC_PORT_ENABLE_CHANGE);
    WordWriteIO(PortAddr, PortStatus | UHC_PORT_ENABLE);

    //
    // Wait for 100ms
    //
    //FixedDelay(gUsbData->UsbTimingPolicy.UhciPortEnable * 1000);        // 100msec delay

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_ResetRootHub
//
// Description:
//  This function resets the UHCI HC root hub port
//
// Input:
//  HcStruc   Pointer to HCStruc of the host controller
//  PortNum    Root port to be enabled
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_ResetRootHub (
    HC_STRUC*	HcStruc,
    UINT8		PortNum)
{
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UHCI_GlobalSuspend
//
// Description: 
//  This function suspend the UHCI HC.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_GlobalSuspend(
    HC_STRUC*	HcStruc
)
{

    UINT16	IoAddr = (UINT16)HcStruc->BaseAddress;
    UINT16  UhciCommand;
    UINT16  UhciStatus;
    UINT32  i;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (UhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}

    UhciCommand = WordReadIO(IoAddr + UHCI_COMMAND_REG);
    UhciCommand &= ~UHC_HOST_CONTROLLER_RUN;
    WordWriteIO(IoAddr + UHCI_COMMAND_REG, UhciCommand);
    for (i = 0; i < 1024; i++) {
        UhciStatus = WordReadIO(IoAddr + UHCI_STATUS_REG);
        if (UhciStatus & UHC_HC_HALTED) {
            break;
        }
        FixedDelay(1 * 1000);
    }
    
    WordWriteIO((UINT16)(IoAddr + UHCI_INTERRUPT_ENABLE), UHC_RESUME_ENABLE);
    
    UhciStatus = WordReadIO(IoAddr + UHCI_STATUS_REG);
    UhciStatus |= 0x1F;
    WordWriteIO(IoAddr + UHCI_STATUS_REG, UhciStatus);
  
    UhciCommand = WordReadIO(IoAddr + UHCI_COMMAND_REG);
    UhciCommand |= UHC_ENTER_SUSPEND;
    WordWriteIO(IoAddr + UHCI_COMMAND_REG, UhciCommand);
    FixedDelay(50 * 1000);
    
    HcStruc->dHCFlag &= ~(HC_STATE_RUNNING);
    HcStruc->dHCFlag |= HC_STATE_SUSPEND;
    
    return  USB_SUCCESS;
}
                                        
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UhciExecuteTransfer
//
// Description:
//  This function execites a transfer and waits for the completion of 
//  the transfer, and returns the transfer results.
//
// Input:
//  Pointers to the first data TD and last data TD in the TD list
//
// Output:
//  Return value is the size of transferred data, Bytes
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
UhciExecuteTransfer (
    HC_STRUC    *HcStruc,
    UHCI_QH     *TransferQh
)
{
	UINT32	Timeout = gUsbData->wTimeOutValue * 100; // *100, makes it number of 10 usec units
	BOOLEAN InfiniteLoop = (Timeout == 0);

    TransferQh->ActiveFlag = TRUE;
    UhciAddQhToFrameList(HcStruc, TransferQh);

    while (InfiniteLoop || Timeout--) {
        UhciProcessQh(HcStruc, TransferQh);
        if (TransferQh->ActiveFlag == FALSE) {
            break;
        }

        FixedDelay(10);  // 10 microseconds
    }

    UhciRemoveQhFromFrameList(HcStruc, TransferQh);
    UhciProcessQh(HcStruc, TransferQh);
    
    if (TransferQh->ActiveFlag) {
        USB_DEBUG (DEBUG_LEVEL_3, "UHCI Time-Out\n");
    }

    return TransferQh->BytesTransferred;
}
 
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_ControlTransfer
//
// Description:
//  This function executes a device request command transaction on the USB. One
//  setup packet is generated containing the device request parameters supplied
//  by the caller.  The setup packet may be followed by data in or data out packets
//  containing data sent from the host to the device or vice-versa. This function
//  will not return until the request either completes successfully or completes in
//  error (due to time out, etc.)
//
// Input:
//      fpHCStruc   Pointer to HCStruc of the host controller
//      pDevInfo    DeviceInfo structure (if available else 0)
//      wRequest    Request type (low byte)
//              Bit 7   : Data direction
//                  0 = Host sending data to device
//                  1 = Device sending data to host
//              Bit 6-5 : Type
//                  00 = Standard USB request
//                  01 = Class specific
//                  10 = Vendor specific
//                  11 = Reserved
//              Bit 4-0 : Recipient
//                  00000 = Device
//                  00001 = Interface
//                  00010 = Endpoint
//                  00100 - 11111 = Reserved
//              Request code, a one byte code describing
//              the actual device request to be executed
//              (ex: Get Configuration, Set Address etc)
//      wIndex      wIndex request parameter (meaning varies)
//      wValue      wValue request parameter (meaning varies)
//      fpBuffer    Buffer containing data to be sent to the
//              device or buffer to be used to receive data
//      wLength     wLength request parameter, number of bytes
//              of data to be transferred in or out
//              of the host controller
//
//
// Output:
//  Number of bytes transferred: 0 - Failure, <>0 - Success
//
//
// Notes:
//  Do not use USB_SUCCESS or USB_ERROR as returned values
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
UHCI_ControlTransfer (
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    UINT16      wRequest,
    UINT16      wIndex,
    UINT16      wValue,
    UINT8       *fpBuffer,
    UINT16      wLength)
{
    UINT16      wTemp;
    UINT32      dTemp;
    UINT32      dValue;

    DEV_REQ     *fpDevReq;
    UHCI_TD     *SetupTd = NULL;
    UHCI_TD     *DataTDs = NULL;
    UHCI_TD     *StatusTd = NULL;
    UHCI_TD     *LastTd = NULL;
    UHCI_TD     *CurrentTd = NULL;
    UHCI_QH     *CtrlQh;
    UINT16      NumDataTDs = 0;
    UINT16      BytesRemaining;
    UINT16      BytesTransferred;
    UINT8       DataToggle;
    EFI_STATUS  EfiStatus = EFI_SUCCESS;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return 0;
    }

    EfiStatus = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return 0;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        if (wLength != 0) {
            EfiStatus = AmiValidateMemoryBuffer((VOID*)fpBuffer, wLength);
            if (EFI_ERROR(EfiStatus)) {
                USB_DEBUG(3, "Uhci ControlTransfer Invalid Pointer, Buffer is in SMRAM.\n");
                return 0;
            }
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }

	if (UhciIsHalted(fpHCStruc)) {
		return 0;
	}
    
    if (!VALID_DEVINFO(fpDevInfo)) return 0;

    gUsbData->bLastCommandStatus &= ~( USB_CONTROL_STALLED );
    gUsbData->dLastCommandStatusExtended = 0;

    //
    // Allocate TDs for control setup and control status packets
    //
    SetupTd = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    if(SetupTd == NULL) {
        return 0;
    }

    //
    // Build the device request in the data area of the control setup TD
    //
    fpDevReq = (DEV_REQ*)SetupTd->aDataArea;
    fpDevReq->wRequestType  = wRequest;
    fpDevReq->wValue        = wValue;
    fpDevReq->wIndex        = wIndex;
    fpDevReq->wDataLength   = wLength;

    //
    // dTemp will contain the device address and endpoint shifted and ready to go
    // into the TDs' token field.
    // 10:0] = Dev. Addr & Endpoint
    // [18:8] = Dev. Addr & Endpoint
    //
    dTemp = ((UINT32)(fpDevInfo->bDeviceAddress)) << 8;

    //
    // Fill in various fields in the control setup TD.
    // The LinkPointer field will point to the control data TD if data will
    // be sent/received or to the control status TD if no data is expected.
    // The ControlStatus field will be set to active and interrupt on complete.
    // The Token field will contain the packet size (size of DeviceRequest
    // struc), the device address, endpoint, and a setup PID.
    // The BufferPointer field will point to the TD's DataArea buffer which
    // was just initialized to contain a DeviceRequest struc.
    // The CSReloadValue field will contain 0 because this is a "one shot" packet.
    // The pCallback will be set to point to the UHCI_ControlTDCallback routine.
    // The ActiveFlag field will be set to TRUE.
    //

    //
    // 11/01/10 for HI/LO/FULL
    //
    dValue = (((UINT32)fpDevInfo->bEndpointSpeed) & 1) << 26;
										//(EIP34448)>
	dValue |= (UINT32)(UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE);
										//<(EIP34448)

    SetupTd->dControlStatus = dValue;

    dValue = dTemp |
        ((UINT32)UHCI_TD_SETUP_PACKET |
        ((UINT32)(sizeof(DEV_REQ) - 1) << 21));

    //
    // Set PID=Setup, and MaxLen
    //
    SetupTd->dToken         = dValue;
    SetupTd->pBufferPtr     = (UINT32)(UINTN)SetupTd->aDataArea;
    SetupTd->dCSReload      = 0;
    SetupTd->bActiveFlag   = 1;

    LastTd = SetupTd;
    //
    // Fill in various fields in the control data TD.
    // Enough control data TDs must be initialized to handle the amount of
    // data expected.  The length of the data transfer is currently in wLength.
    // LinkPointer field will be set to the next data TD or the status TD.
    // ControlStatus field will be se to active and interrupt on complete.
    // Token field will contain the data transfer size (still in wLength), device
    // address (in pDevInfo), endpoint (in dTemp), and an in or out PID
    // (in wReqType).
    // BufferPointer field will point to the data buffer passed in by the
    // caller (currently in fpBuffer).
    // CSReloadValue field will contain 0 because this is a "one shot" packet.
    // pCallback will be set to point to the UHCI_ControlTDCallback routine.
    // ActiveFlag field will be set to TRUE.
    //
    if(wLength) {
        NumDataTDs = wLength / fpDevInfo->wEndp0MaxPacket;
        if (wLength % fpDevInfo->wEndp0MaxPacket) {
            NumDataTDs++;
        }

        DataTDs = USB_MemAlloc(GET_MEM_BLK_COUNT(NumDataTDs * sizeof(UHCI_TD)));
        if (DataTDs == NULL) {
            USB_MemFree(SetupTd, GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
            return 0;
        }

        CurrentTd = DataTDs;

        DataToggle  = 1;
        BytesRemaining = wLength;
 
        //
        // Allocate one more TD to be used either for more data or for TD Status
        //
        do {
            //
            // 11/01/10 for HI/LO/FULL
            //
            dValue = (((UINT32)(fpDevInfo->bEndpointSpeed) & 1) << 26);
            dValue = dValue |
                (UINT32)(UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE);
            if(wRequest & BIT7) {
                dValue |= UHCI_TD_SHORT_PACKET_DETECT;
            }
            CurrentTd->dControlStatus = dValue;
            CurrentTd->pBufferPtr = (UINT32)(UINTN)fpBuffer;
            wTemp = (UINT16)((BytesRemaining > (fpDevInfo->wEndp0MaxPacket)) ?
                                fpDevInfo->wEndp0MaxPacket : BytesRemaining);
            //
            // Packet size is valid
            //
            BytesRemaining = (UINT16)(BytesRemaining - wTemp);
            fpBuffer = fpBuffer + wTemp;
            --wTemp;

            //
            // [18:8]=Dev. addr & endp
            //
            dValue = dTemp | (((UINT32)wTemp) << 21);
            dValue = (dValue & 0xFFFFFF00) | UHCI_TD_OUT_PACKET;

            if(wRequest & BIT7)
            {
                dValue = (dValue & 0xFFFFFF00) | UHCI_TD_IN_PACKET;
            }
            if(DataToggle & 1)
            {
                dValue = dValue | UHCI_TD_DATA_TOGGLE;  // Make packet into a data 1
            }
            CurrentTd->dToken = dValue;
            CurrentTd->dCSReload = 0;
            CurrentTd->bActiveFlag = 1;

            LastTd->pLinkPtr = (UINT32)((UINTN)CurrentTd | UHCI_VERTICAL_FLAG);
            LastTd = CurrentTd;
            CurrentTd++;
            
            DataToggle  ^=  1;
        } while (BytesRemaining);  // End the data TD list
    }
    //
    // Fill in various fields in the TD control status.
    // LinkPointer field will point to TERMINATE.
    // ControlStatus field will be set to active and interrupt on complete.
    // Token field will contain the packet size (0), the device address,
    // endpoint, and a setup PID with opposite data direction as that defined
    // in the request type (wReqType).
    // BufferPointer field will point to the TD's DataArea buffer even though
    // we are not expecting any data transfer.
    // CSReloadValue field will contain 0 because this is a "one shot" packet.
    // pCallback will be set to point to the UHCI_ControlTDCallback routine.
    // ActiveFlag field will be set to TRUE.
    //
    StatusTd = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    if (StatusTd == NULL) {
        return 0;
    }

    LastTd->pLinkPtr = (UINT32)((UINTN)StatusTd | UHCI_VERTICAL_FLAG);
    LastTd = StatusTd;
    StatusTd->pLinkPtr  = UHCI_TERMINATE;
    dValue = (((UINT32)(fpDevInfo->bEndpointSpeed) & 1) << 26);
										//(EIP34448)>
    dValue = dValue | (UINT32)(UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE);
										//<(EIP34448)
    StatusTd->dControlStatus = dValue;
    dValue = dTemp;
    dValue = (dValue & 0xFFFFFF00) | (UINT32)UHCI_TD_OUT_PACKET;
    if((wRequest & BIT7) == 0)
    {
        dValue = (dValue & 0xFFFFFF00) | (UINT32)UHCI_TD_IN_PACKET;
    }
    dValue |= (UHCI_TD_DATA_TOGGLE | ((UINT32)UHCI_TD_ACTUAL_LENGTH << 21));
    StatusTd->dToken = dValue;
    dValue = (UINT32)(UINTN)StatusTd->aDataArea;
    StatusTd->pBufferPtr = dValue;
    StatusTd->dCSReload = 0;
    StatusTd->bActiveFlag = 1;
    //
    // Now put the control setup, data and status into the HC's schedule by
    // pointing QhControl's link pointer to control setup TD.
    // This will cause the HC to execute the transaction in the next active frame.

    CtrlQh = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    if (CtrlQh == NULL) {
        return 0;
    }

    UhciInitQh(CtrlQh);
    CtrlQh->pElementPtr = (UINT32)(UINTN)SetupTd;
    CtrlQh->CurrentTd = SetupTd;
    CtrlQh->Type = Control;
    CtrlQh->FirstTd = SetupTd;

    // Wait till transfer complete
    BytesTransferred = UhciExecuteTransfer(fpHCStruc, CtrlQh);

    // Calculate the transferred length
    BytesTransferred -= (((SetupTd->dControlStatus & UHCI_TD_ACTUAL_LENGTH) + 1) & 0x7FF);
 
    // Save error information in global variable
    gUsbData->dLastCommandStatusExtended = 
        (CtrlQh->CurrentTd->dControlStatus & UHCI_TD_STATUS_FIELD) >> 17;

    if (CtrlQh->CurrentTd->dControlStatus & UHCI_TD_STALLED ){
        gUsbData->bLastCommandStatus |= USB_CONTROL_STALLED;
        BytesTransferred = 0;
    }

    USB_MemFree(SetupTd, GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    if (DataTDs) {
        USB_MemFree(DataTDs, GET_MEM_BLK_COUNT(NumDataTDs * sizeof(UHCI_TD)));
    }
    USB_MemFree(StatusTd, GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    USB_MemFree(CtrlQh, GET_MEM_BLK_COUNT_STRUC(UHCI_QH));

    return BytesTransferred;
}   // UHCI_ControlTransfer


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UHCI_InitBulkTdCommon
//
// Description:
//  This function creates a chain of two TDs for bulk data transfer. It fills
//  in the following fields in TD:
//                  pLinkPtr - NextTd address
//                  dToken   - All bits except length and data toggle
//
// Input:
//  BulkDataTd0     1st TD in the chain
//  BulkDataTd1     2nd TD in the chain
//  TokenData       Data for dToken
//  NumBulkTds      # of bulk TDs
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UHCI_InitBulkTdCommon (
    UHCI_TD *BulkDataTd0,
    UINT32  TokenData,
    UINT16  NumBulkTds
)
{
    UINT16  i;
    UHCI_TD *Td0 = BulkDataTd0;
    UHCI_TD *Td1 = Td0;
    UINT16  NumTd = NumBulkTds*2;

    for (i=0; i<NumTd; i++)
    {
        Td0 = Td1;
        Td0->dToken = TokenData;
        Td1 = (UHCI_TD*)((UINTN)Td0 + sizeof(UHCI_TD));
        Td0->pLinkPtr = (UINT32)(UINTN)Td1 | UHCI_VERTICAL_FLAG;
    }
    // Terminated later in UHCI_InitBulkDataTds
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UHCI_InitBulkDataTds
//
// Description:
//  This function initializes the fields in bulk data TD list that remain after
//  UHCI_InitBulkTdCommon:
//                  - Data buffer pointer
//                  - Data length
//                  - Data toggle (DAT0/DAT1)
//
// Output:
//  Pointer to the last TD in the chain
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UHCI_TD*
UHCI_InitBulkDataTds(
    IN UHCI_TD      *BulkDataTd,
    IN UINT16       MaxPkt,
    IN UINT32       EndpointSpeed,
    IN OUT UINT32   *Address,
    IN OUT UINT8    *DatToggle,
    IN OUT UINT32   *BytesRemaining,
    IN UINT16       NumBulkTds
)
{
    UINT16  i;
    UINT32  Length = *BytesRemaining;
    UHCI_TD *Td = BulkDataTd;
    UINT32  Addr = *Address;
    UINT8   Toggle = *DatToggle;
    BOOLEAN TheLastTd = FALSE;

    for (i = 0; i < NumBulkTds; i++)
    {
        Length = *BytesRemaining;

        if (Length > (UINT32)MaxPkt)
        {
            Length = (UINT32)MaxPkt;
        }
        else
        {
            TheLastTd = TRUE;
        }
        Td->dToken &= 0x1FFFFF;
        Td->dToken |= (Length - 1) << 21;
    
        Td->dToken &= ~UHCI_TD_DATA_TOGGLE;      // Make packet go into DAT0
        if (Toggle == 1)
        {
            Td->dToken |= UHCI_TD_DATA_TOGGLE;   // Make packet go into DAT1
        }
    
        Td->dControlStatus = EndpointSpeed |
                    (UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE);
        if ((Td->dToken & UHCI_TD_PACKET_ID) == UHCI_TD_IN_PACKET) {
            Td->dControlStatus |= UHCI_TD_SHORT_PACKET_DETECT;
        }

        Td->pBufferPtr = Addr;
        Addr += MaxPkt;
        Toggle ^= 1;
        Td = (UHCI_TD*)((UINTN)Td + sizeof(UHCI_TD));
        *BytesRemaining -= Length;

        if (TheLastTd) break;
    }

    Td = (UHCI_TD*)((UINTN)Td - sizeof(UHCI_TD));
    Td->pLinkPtr = UHCI_TERMINATE;

    *Address = Addr;
    *DatToggle = Toggle;

    return Td;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UHCI_BulkTransfer
//
// Description:
//  This function executes a bulk transaction on the USB. The transfer may be
//  either DATA_IN or DATA_OUT packets containing data sent from the host to
//  the device or vice-versa. This function wil not return until the request
//  either completes successfully or completes with error (due to time out, etc.)
//
// Input:
//  HcStruc     Pointer to HCStruc of the host controller
//  DevInfo     DeviceInfo structure (if available else 0)
//  XferDir     Transfer direction
//                  Bit 7: Data direction
//                          0 Host sending data to device
//                          1 Device sending data to host
//                  Bit 6-0 : Reserved
//  Buffer      Buffer containing data to be sent to the device or buffer to be
//              used to receive data value in Segment:Offset format
//  Length      Length request parameter, number of bytes of data to be transferred
//              in or out of the host controller
//
// Output:
//  Amount of data transferred
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
UHCI_BulkTransfer (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       XferDir,
    UINT8       *Buffer,
    UINT32      Length
)
{
    UINT16      MaxPkt;
    UINT8       Endp;
    UINT32      Data;
    UINT8       DatToggle;
    UINT32      TransferError;
    UHCI_QH     *BulkQh;
    UHCI_TD     *BulkDataTd;
    UHCI_TD     *NextBulkDataTd;
    UHCI_TD     *BulkDataTd0;
    UHCI_TD     *BulkDataTd1;
    UHCI_TD     *LastTd;
    UHCI_TD     *NextLastTd;
    UINT16      NumAllocTDs;
    UINT16      NumBulkTDs;
    UINT32      BytesRemaining;
    UINT32      BytesTransferred;
    UINT32      BytesTransferredNow;
    UINT32      Address;
    UINT32      Eps;
    EFI_STATUS  EfiStatus = EFI_SUCCESS;
    
    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return 0;
    }

    EfiStatus = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return 0;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        EfiStatus = AmiValidateMemoryBuffer((VOID*)Buffer, Length);
        if (EFI_ERROR(EfiStatus)) {
            USB_DEBUG(3, "Uhci BulkTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }

	if (UhciIsHalted(HcStruc)) {
		return 0;
	}
    
    if ( !VALID_DEVINFO( DevInfo) ) return 0;

    if (Length == 0) return 0;

    // Clear HW source of error
    gUsbData->bLastCommandStatus &= ~(USB_BULK_STALLED | USB_BULK_TIMEDOUT );
    gUsbData->dLastCommandStatusExtended = 0;
    //
    // Get Bulk IN/OUT enpoint number, data sync value & max packet size
    // Store the appropriate max packet size and endpoint number
    // in the local variables
    //
    MaxPkt = (XferDir & BIT7)? DevInfo->wBulkInMaxPkt : DevInfo->wBulkOutMaxPkt;

    if (MaxPkt == 0) return 0;

    Endp = (XferDir & BIT7)? DevInfo->bBulkInEndpoint : DevInfo->bBulkOutEndpoint;

    //
    // For multiple LUN devices toggle is maintained by LUN0
    //
    DatToggle = UsbGetDataToggle(DevInfo, Endp | XferDir);

    //
    // Form TD token data, less the transfer length and toggle information
    //
    Data = (UINT32)Endp << 7;
    Data = (Data | DevInfo->bDeviceAddress) << 8;
    Data = (XferDir & BIT7)? Data | UHCI_TD_IN_PACKET : Data | UHCI_TD_OUT_PACKET;

    BulkQh = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    if (BulkQh == NULL) return 0;

    BulkQh->Type = Bulk;

    // Allocate data TDs.
    NumBulkTDs = FULLSPEED_MAX_BULK_DATA_SIZE_PER_FRAME/MaxPkt;
    ASSERT(NumBulkTDs != 0);

    NumAllocTDs = NumBulkTDs*2;

    BulkDataTd0 = (UHCI_TD*)USB_MemAlloc(GET_MEM_BLK_COUNT(NumAllocTDs * sizeof(UHCI_TD)));
    ASSERT(BulkDataTd0 != NULL);

    UHCI_InitBulkTdCommon (BulkDataTd0, Data, NumBulkTDs);

    BulkDataTd1 = (UHCI_TD*)((UINTN)BulkDataTd0 + (NumBulkTDs * sizeof(UHCI_TD)));

    BulkDataTd = BulkDataTd0;
    NextBulkDataTd = BulkDataTd1;
    BytesRemaining = Length;
    BytesTransferred = 0;
    BytesTransferredNow = 0;
    Address = (UINT32)(UINTN)Buffer;
    TransferError = 0;
    Eps = ((UINT32)(DevInfo->bEndpointSpeed) & 1) << 26;

    LastTd = UHCI_InitBulkDataTds(
        BulkDataTd, MaxPkt, Eps, &Address, &DatToggle, &BytesRemaining, NumBulkTDs);
    NextLastTd = LastTd;

    do {
        // Start the transfer by adding TD in the bulk queue head
        UhciInitQh(BulkQh);
        BulkQh->pElementPtr = (UINT32)(UINTN)BulkDataTd;
        BulkQh->CurrentTd = BulkDataTd;
        BulkQh->FirstTd = BulkDataTd;

        // Initialize the next TD block and wait for the current one to complete.
        // In case MaxPkt is 64 Bytes, we have approx. NumBulkTDs*50mcs for this.
        if (BytesRemaining != 0) {
            NextLastTd = UHCI_InitBulkDataTds(
                NextBulkDataTd, MaxPkt, Eps, &Address, &DatToggle, &BytesRemaining, NumBulkTDs);
        }

        // Wait til BulkDataTd is complete, check for errors
        BytesTransferredNow = UhciExecuteTransfer(HcStruc, BulkQh);

		DatToggle = BulkQh->DataToggle;
        TransferError = (BulkQh->CurrentTd->dControlStatus & UHCI_TD_STATUS_FIELD) >> 17;
        if (TransferError) {
            break;
        }
        BytesTransferred += BytesTransferredNow;

        NextBulkDataTd = BulkDataTd;
        LastTd = NextLastTd;
        BulkDataTd = (BulkDataTd == BulkDataTd0)? BulkDataTd1 : BulkDataTd0;

    } while ((BytesTransferred < Length) && !BulkQh->ShortPacketDetected);

    UsbUpdateDataToggle(DevInfo, Endp | XferDir, DatToggle);
    gUsbData->dLastCommandStatusExtended = TransferError;
    if (BulkQh->CurrentTd->dControlStatus & UHCI_TD_STALLED){
        gUsbData->bLastCommandStatus |= USB_BULK_STALLED;
    }
    if (BulkQh->CurrentTd->dControlStatus & UHCI_TD_ACTIVE) {
        gUsbData->bLastCommandStatus |= USB_BULK_TIMEDOUT;
    }
    //
    // Deallocate memory and return the transferred data size
    //
    USB_MemFree(BulkDataTd0, GET_MEM_BLK_COUNT(NumAllocTDs * sizeof(UHCI_TD)));
    USB_MemFree(BulkQh, GET_MEM_BLK_COUNT_STRUC(UHCI_QH));

    return BytesTransferred;
}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_InterruptTransfer
//
// Description:
//  This function executes an interrupt transaction on the USB. The data transfer
//  direction is always DATA_IN. This function wil not return until the request
//  either completes successfully or completes in error (due to time out, etc.)
//
// Input:
//  fpHCStruc   Pointer to HCStruc of the host controller
//  fpDevInfo   DeviceInfo structure (if available else 0)
//  EndpointAddress The destination USB device endpoint to which the device request 
//              is being sent.
//  MaxPktSize  Indicates the maximum packet size the target endpoint is capable 
//              of sending or receiving.
//  fpBuffer    Buffer containing data to be sent to the device or buffer to be
//              used to receive data
//  wLength     wLength request parameter, number of bytes of data to be transferred
//
// Output:
//  Number of bytes transferred
//
//
// Notes:
//  DO NOT TOUCH THE LINK POINTER OF THE TDInterruptData. It is statically allocated
//  and linked with other items in the 1ms schedule
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
UHCI_InterruptTransfer(
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    UINT8       EndpointAddress,
    UINT16      MaxPktSize,
    UINT8       *fpBuffer,
    UINT16      wLength)
{
    UINT8		bEndp;
    UINT8       DataToggle;
    UINT32		dTemp, dValue;
    UHCI_QH     *IntQh;
	UHCI_TD		*IntTd;
	UINT32		BytesTransferred;
    EFI_STATUS  EfiStatus = EFI_SUCCESS;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return 0;
    }

    EfiStatus = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return 0;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        EfiStatus = AmiValidateMemoryBuffer((VOID*)fpBuffer, wLength);
        if (EFI_ERROR(EfiStatus)) {
            USB_DEBUG(3, "Uhci InterruptTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }

	if (UhciIsHalted(fpHCStruc)) {
		return 0;
	}
    
    if( !VALID_DEVINFO( fpDevInfo) )
        return 0;

    gUsbData->dLastCommandStatusExtended = 0;

    //
    // Check for 0 length transfer (if so, exit)
    //
    if(wLength == 0) {
        return 0;
    }

    //
    // Store the descriptor pointer in a local variable
    //
    IntTd = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
	if (IntTd == NULL) {
		return 0;
	}

	IntTd->pLinkPtr  = UHCI_TERMINATE;

    //
    // It is an interrupt IN transaction get appropriate size
    //
    bEndp = EndpointAddress & 0xF;
	DataToggle = UsbGetDataToggle(fpDevInfo, EndpointAddress);

    //
    // Form device address and endpoint in proper order and bit position
    //
    dTemp = (UINT32)bEndp << 7;
    dTemp = (dTemp | (fpDevInfo->bDeviceAddress)) << 8; //[10:0] = Dev. Addr & Endpoint
                                                        //[18:8] = Dev. Addr & Endpoint
    //
    // Fill in various fields in the interrupt data TD
    //
    IntTd->dControlStatus = (((UINT32)(fpDevInfo->bEndpointSpeed) & 1) << 26) | 
    							UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE;
    //
    // Set the buffer pointer. Note that currently UHCI Interrupt Transfer
    // implementation assumes IN packet; the direction is not passed here as
    // parameter. Should this change in future, make a branch to use 
    // UHCI_TD_OUT_PACKET while constructing dToken.
    //
	IntTd->pBufferPtr = (UINT32)(UINTN)fpBuffer;
    dValue = (UINT32)(wLength - 1);
    dValue = ((dValue << 21) | dTemp) & 0xffffff00;
	dValue |= EndpointAddress & BIT7 ? UHCI_TD_IN_PACKET : 
		UHCI_TD_OUT_PACKET;

    if(DataToggle & 1) {
        dValue |= UHCI_TD_DATA_TOGGLE;  // Make packet into a data 1
    }

    IntTd->dToken = dValue;
    IntTd->dCSReload = 0;
    IntTd->bActiveFlag = 1;

    IntQh = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    if (IntQh == NULL) {
        return 0;
    }

    UhciInitQh(IntQh);
    IntQh->pElementPtr = (UINT32)(UINTN)IntTd;
    IntQh->CurrentTd = IntTd;
    IntQh->Type = Interrupt;
    IntQh->FirstTd = IntTd;
    IntQh->Interval = UhciTranslateInterval(fpDevInfo->bPollInterval);

    BytesTransferred = UhciExecuteTransfer(fpHCStruc, IntQh);

    gUsbData->dLastCommandStatusExtended =
        (IntQh->CurrentTd->dControlStatus & UHCI_TD_STATUS_FIELD) >> 17;

    UsbUpdateDataToggle(fpDevInfo, EndpointAddress, IntQh->DataToggle);

    USB_MemFree(IntTd, GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    USB_MemFree(IntQh, GET_MEM_BLK_COUNT_STRUC(UHCI_QH));

    return (UINT16)BytesTransferred;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_DeactivatePolling
//
// Description:
//  This function de-activates the polling TD for the requested device. The
//  device may be a USB keyboard or USB hub
//
// Input:
//  fpHCStruc   Pointer to the HC structure
//  fpDevInfo   Pointer to the device information structure
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_DeactivatePolling (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo
)
{
    UHCI_QH     *PollQh;
    UINT8       DataToggle;

    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (UhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}

    if (DevInfo->fpPollTDPtr == NULL) {
        return USB_ERROR;
    }

    PollQh = (UHCI_QH*)DevInfo->fpPollTDPtr;

    UhciRemoveQhFromFrameList(HcStruc, PollQh);

    DataToggle = (PollQh->FirstTd->dToken & UHCI_TD_DATA_TOGGLE)? 1 : 0;
    if (!(PollQh->FirstTd->dControlStatus & UHCI_TD_STATUS_FIELD)) {
        UsbUpdateDataToggle(DevInfo, DevInfo->IntInEndpoint, DataToggle ^ 1);
    }

    UhciFreeTds(PollQh->FirstTd);
    USB_MemFree(PollQh, GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    DevInfo->fpPollTDPtr = NULL;

	if (DevInfo->fpPollDataBuffer) {
		USB_MemFree(DevInfo->fpPollDataBuffer, GET_MEM_BLK_COUNT(DevInfo->PollingLength)); 
    	DevInfo->fpPollDataBuffer = NULL;
	}

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_ActivatePolling
//
// Description:
//  This function activates the polling TD for the requested device. The device
//  may be a USB keyboard or USB hub
//
// Input:
//  fpHCStruc   Pointer to the HC structure
//  fpDevInfo   Pointer to the device information structure
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
// Notes:
//  For the keyboard device this routine allocates TDRepeat also, if it is not
//  already allocated. This routine allocate a polling TD and schedule it to 8ms
//  schedule for keyboards and to 1024ms schedule for hubs.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_ActivatePolling (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo)
{
    UHCI_TD     *PollTd;
    UHCI_QH     *PollQh;
	BOOLEAN		LowSpeed;
	UINT8		PacketId;
	UINTN		BufferAddr;
	UINT32		DataLen;
	UINT8		DataToggle;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (UhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}
    
    if( !VALID_DEVINFO(DevInfo) )
        return USB_ERROR;

	DevInfo->fpPollDataBuffer = USB_MemAlloc(GET_MEM_BLK_COUNT(DevInfo->PollingLength));
    if (DevInfo->fpPollDataBuffer == NULL) {
        return USB_ERROR;
    }

	LowSpeed = (DevInfo->bEndpointSpeed & 1) != 0;
	PacketId = DevInfo->IntInEndpoint & BIT7 ? UHCI_TD_IN_PACKET : UHCI_TD_OUT_PACKET;
	BufferAddr = (UINTN)DevInfo->fpPollDataBuffer;
	DataLen = DevInfo->PollingLength;
	DataToggle = UsbGetDataToggle(DevInfo, DevInfo->IntInEndpoint);

	PollTd = UhciAllocGeneralTds(DevInfo->bDeviceAddress, LowSpeed, PacketId, 
					DevInfo->IntInEndpoint & 0xF, DevInfo->IntInMaxPkt, TRUE, 
					&BufferAddr, &DataLen, &DataToggle);
	if (PollTd == NULL) {
		USB_MemFree(DevInfo->fpPollDataBuffer, GET_MEM_BLK_COUNT(DevInfo->PollingLength));
		return USB_ERROR;
	}

    PollQh = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    if (PollQh == NULL) {
		USB_MemFree(DevInfo->fpPollDataBuffer, GET_MEM_BLK_COUNT(DevInfo->PollingLength));
        UhciFreeTds(PollTd);
        return USB_ERROR;
    }

    DevInfo->fpPollTDPtr = (UINT8*)PollQh;

    UhciInitQh(PollQh);
    PollQh->pElementPtr = (UINT32)(UINTN)PollTd;
    PollQh->CurrentTd = PollTd;
    PollQh->Type = Interrupt;
    PollQh->FirstTd = PollTd;
    PollQh->Interval = UhciTranslateInterval(DevInfo->bPollInterval);
    PollQh->CallBackIndex = USB_InstallCallBackFunction(UhciPollingQhCallback);
    PollQh->DevInfoPtr = DevInfo;
    PollQh->ActiveFlag = TRUE;

    UhciAddQhToFrameList(HcStruc, PollQh);

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_DisableKeyRepeat
//
// Description:
//  This function disables the keyboard repeat rate logic
//
// Input:
//  fpHCStruc   Pointer to the HCStruc structure
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_DisableKeyRepeat (
    HC_STRUC    *HcStruc
)
{
    UHCI_DESC_PTRS      *UhicDescPtrs;
    UHCI_QH             *Qh;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (UhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}

    UhicDescPtrs = HcStruc->stDescPtrs.fpUHCIDescPtrs;

    if (UhicDescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINT8*)UhicDescPtrs < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(UhicDescPtrs + sizeof(UHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    Qh = UhicDescPtrs->RepeatQh;

    if (Qh == NULL) {
        return USB_ERROR;
    }

    if (((UINT8*)Qh < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(Qh + sizeof(UHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINT8*)Qh->FirstTd < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(Qh->FirstTd + sizeof(UHCI_TD)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    Qh->FirstTd->dCSReload = UHCI_TD_ONE_ERROR;
    Qh->FirstTd->dControlStatus= UHCI_TD_ONE_ERROR;
    Qh->FirstTd->bActiveFlag = 0;
    Qh->ActiveFlag = FALSE;
    Qh->pElementPtr = UHCI_TERMINATE;

    return USB_SUCCESS;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_EnableKeyRepeat
//
// Description:
//  This function enables the keyboard repeat rate logic
//
// Input:
//  fpHCStruc   Pointer to the HCStruc structure
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_EnableKeyRepeat (
    HC_STRUC    *HcStruc
)
{
    UHCI_DESC_PTRS      *UhicDescPtrs;
    UHCI_QH             *Qh;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (UhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}

    UhicDescPtrs = HcStruc->stDescPtrs.fpUHCIDescPtrs;

    if (UhicDescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINT8*)UhicDescPtrs < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(UhicDescPtrs + sizeof(UHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    Qh = UhicDescPtrs->RepeatQh;

    if (((UINT8*)Qh < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(Qh + sizeof(UHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINT8*)Qh->FirstTd < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(Qh->FirstTd + sizeof(UHCI_TD)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    Qh->FirstTd->dCSReload = (UHCI_TD_INTERRUPT_ON_COMPLETE |
                            UHCI_TD_ONE_ERROR | UHCI_TD_ACTIVE);
    Qh->FirstTd->dControlStatus = Qh->FirstTd->dCSReload;
    Qh->FirstTd->bActiveFlag = 1;
    Qh->pElementPtr = (UINT32)(UINTN)Qh->FirstTd;
    Qh->CurrentTd = Qh->FirstTd;
    Qh->ActiveFlag = TRUE;

    return USB_SUCCESS;
}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_DisableHCPorts (fpHCStruc)
//
// Description:
//  This routine disables the UHCI HC root hub ports
//
// Input:
//  fpHCStruc   Ptr to the host controller structure
//
// Output:
//  Status: USB_SUCCESS = Success, USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_DisableHCPorts (HC_STRUC* fpHCStruc)
{
    UINT16 wIOAddr = (UINT16)fpHCStruc->BaseAddress;

    //
    // Disable the root hub port 1
    //
    ByteWriteIO((UINT16)(wIOAddr+UHCI_PORT1_CONTROL),
                (UINT8)(ByteReadIO(
                    (UINT16)(wIOAddr+UHCI_PORT1_CONTROL)) & (~UHC_PORT_ENABLE)));
    //
    // Disable the root hub port 2
    //
    ByteWriteIO((UINT16)(wIOAddr+UHCI_PORT2_CONTROL),
                (UINT8)(ByteReadIO(
                    (UINT16)(wIOAddr+UHCI_PORT2_CONTROL)) & (~UHC_PORT_ENABLE)));

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UhciAddQhToFrameList
//
// Description:
//  This routine will add the particular QH into the frame list
//
// Input:
//  HcStruc     Pointerr to the host controller structure
//  NewQh       Address of the QH to be linked
//
// Output:
//  USB_SUCCESS/USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciAddQhToFrameList (
    HC_STRUC    *HcStruc,
    UHCI_QH     *NewQh
)
{
    UINT16      Index;
    UINT32      *PrevPtr;
    UINT32      LinkPtr;
    UHCI_QH     *Qh;
    BOOLEAN     ByInterval = FALSE;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (NewQh == NULL) {
        return USB_ERROR;
    }

    switch (NewQh->Type) {
        case Control:
        case Bulk:
            ByInterval = FALSE;
            break;
        case Interrupt:
            ByInterval = TRUE;
            break;
        case Isochronous:
            ASSERT(FALSE);
        default:
            return USB_ERROR;
    }

    if (ByInterval && NewQh->Interval == 0) {
        return USB_ERROR;
    }

    for (Index = 0; Index < HcStruc->wAsyncListSize; 
        ByInterval ? Index += NewQh->Interval : Index++) {
        PrevPtr = &HcStruc->fpFrameList[Index];
        LinkPtr = *PrevPtr;

        while (!(LinkPtr & UHCI_TERMINATE)) {
            Qh = (UHCI_QH*)(LinkPtr & UHCI_POINTER_MASK);
#if USB_RUNTIME_DRIVER_IN_SMM
             Status = AmiValidateMemoryBuffer((VOID*)Qh, sizeof(UHCI_QH));
             if (EFI_ERROR(Status)) {
                return USB_ERROR;
             }
#endif
            if (Qh->Type <= NewQh->Type) {
                if (ByInterval == FALSE ||
                    Qh->Interval <= NewQh->Interval) {
                    break;
                }
            }
            PrevPtr = &Qh->pLinkPtr;
            LinkPtr = *PrevPtr; 
        }
        if (Qh == NewQh) {
            continue;
        }
#if USB_RUNTIME_DRIVER_IN_SMM
        Status = AmiValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
        if (EFI_ERROR(Status)) {
            return USB_ERROR;
        }
#endif
        NewQh->pLinkPtr = *PrevPtr;
        *PrevPtr = (UINT32)((UINTN)NewQh | UHCI_QUEUE_HEAD);
    }

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UhciRemoveQhFromFrameList
//
// Description:
//  This routine will remove a QH from the the frame list
//
// Input:
//  HcStruc     Pointerr to the host controller structure
//  RetiredQh   Address of the QH to be removed
//
// Output:
//  USB_SUCCESS/USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciRemoveQhFromFrameList (
    HC_STRUC    *HcStruc,
    UHCI_QH     *RetiredQh
)
{
    UINT16      Index;
    UINT32      *PrevPtr;
    UINT32      LinkPtr;
    UHCI_QH     *Qh;
    BOOLEAN     ByInterval = FALSE;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (RetiredQh == NULL) {
        return USB_ERROR;
    }

    switch (RetiredQh->Type) {
        case Control:
        case Bulk:
            ByInterval = FALSE;
            break;
        case Interrupt:
            ByInterval = TRUE;
            break;
        case Isochronous:
            ASSERT(FALSE);
        default:
            return USB_ERROR;
    }

    if (ByInterval && RetiredQh->Interval == 0) {
        return USB_ERROR;
    }

    RetiredQh->pElementPtr = UHCI_TERMINATE;

    for (Index = 0; Index < HcStruc->wAsyncListSize;
        ByInterval ? Index += RetiredQh->Interval : Index++) {
        PrevPtr = &HcStruc->fpFrameList[Index];
        LinkPtr = *PrevPtr; 
 
        while (!(LinkPtr & UHCI_TERMINATE)) {
            Qh = (UHCI_QH*)(LinkPtr & UHCI_POINTER_MASK);
#if USB_RUNTIME_DRIVER_IN_SMM
            Status = AmiValidateMemoryBuffer((VOID*)Qh, sizeof(UHCI_QH));
            if (EFI_ERROR(Status)) {
                return USB_ERROR;
            }
#endif
            if (Qh == RetiredQh) {
                break;
            }
            PrevPtr = &Qh->pLinkPtr;
            LinkPtr = *PrevPtr;
        }

        if (LinkPtr & UHCI_TERMINATE) {
            continue;
        }
#if USB_RUNTIME_DRIVER_IN_SMM
        Status = AmiValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
        if (EFI_ERROR(Status)) {
            return USB_ERROR;
        }
#endif
        *PrevPtr = RetiredQh->pLinkPtr;
    }

    RetiredQh->pLinkPtr = UHCI_TERMINATE;
    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_StartTDSchedule (fpHCStruc)
//
// Description:
//  This routine will start the TD schedule for the UHCI controller. After this
//  routine TD's can be scheduled for execution.
//
// Input:
//  fpHCStruc   Pointer to the HC information structure
//
// Output:
//  USB_SUCCESS/USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_StartTDSchedule (
    HC_STRUC  *HcStruc
)
{
    UHCI_DESC_PTRS  *DescPtr;
    UHCI_TD         *Td;

    //
    // Allocate the UHCI descriptor pointer structure
    //
    DescPtr = (UHCI_DESC_PTRS*) USB_MemAlloc (GET_MEM_BLK_COUNT_STRUC(UHCI_DESC_PTRS));
    if (DescPtr == NULL) {
        USB_DEBUG(DEBUG_LEVEL_4, "UHCI Descriptor struc alloc failed.\n");
        return USB_ERROR;
    }

    //
    // Save the value in the HC struc
    //
    HcStruc->stDescPtrs.fpUHCIDescPtrs = DescPtr;

    DescPtr->StaticQh = USB_MemAlloc(GET_MEM_BLK_COUNT(1 * sizeof(UHCI_QH)));
    if (DescPtr->StaticQh == NULL) {
        return USB_ERROR;
    }

    UhciInitQh(DescPtr->StaticQh);
    DescPtr->StaticQh->Type = Interrupt;
    DescPtr->StaticQh->Interval = 1;
    UhciAddQhToFrameList(HcStruc, DescPtr->StaticQh);

	if (HcStruc->dHCFlag & HC_STATE_EXTERNAL) {
		return USB_SUCCESS;
	}

    DescPtr->RepeatQh = USB_MemAlloc(GET_MEM_BLK_COUNT(1 * sizeof(UHCI_QH) + 
                                         1 * sizeof(UHCI_TD)));
    if(DescPtr->RepeatQh == NULL) {
        return USB_ERROR;
    }

    Td = (UHCI_TD*)((UINTN)DescPtr->RepeatQh + sizeof (UHCI_QH));

    //
    // Initialize the body of TdRepeat. It will run a interrupt transaction
    // to a non-existant dummy device.  This will have the effect of generating
    // a periodic interrupt used to generate keyboard repeat.  This TD is normally
    // inactive, and is only activated when a key is pressed.  TdRepeat will be
    // set to timeout after two attempts.  Since the TD is in the schedule
    // at 16ms intervals, this will generate an interrupt at intervals of 32ms
    // (when the TD is active).  This 32ms periodic interrupt may then
    // approximate the fastest keyboard repeat rate of 30 characters per second.
    //
    Td->pLinkPtr = UHCI_TERMINATE;
    Td->dControlStatus = UHCI_TD_ONE_ERROR;
    Td->dToken = (UHCI_TD_IN_PACKET |
                ((UINT32)DUMMY_DEVICE_ADDR << 8) |
                ((UINT32)(DEFAULT_PACKET_LENGTH - 1) << 21));
    Td->pBufferPtr = (UINT32)(UINTN)Td->aDataArea;
    Td->dCSReload = UHCI_TD_ONE_ERROR;
    Td->bActiveFlag = 0;

    UhciInitQh(DescPtr->RepeatQh);
    DescPtr->RepeatQh->Type = Interrupt;
    DescPtr->RepeatQh->FirstTd = Td;
    DescPtr->RepeatQh->Interval = REPEAT_INTERVAL;
    DescPtr->RepeatQh->CallBackIndex = USB_InstallCallBackFunction(UhciRepeatQhCallback);
    DescPtr->RepeatQh->ActiveFlag = FALSE;

    //
    // Schedule the TDRepeat to 8ms schedule
    //
    UhciAddQhToFrameList(HcStruc, DescPtr->RepeatQh);

    //
    // Inform the common code that key repeat is implemented
    //
    USBKeyRepeat(HcStruc, 0);

    //
    // Initialize the body of root hub TD.  It will run a interrupt
    // transaction to a nonexistent dummy device.  This will have the effect
    // of generating a periodic interrupt for the purpose of checking for
    // attach/detach on the root hub's ports
    // This initialization is done only once for the first HC
    //
    DescPtr->RootHubQh = USB_MemAlloc(GET_MEM_BLK_COUNT(1 * sizeof(UHCI_QH) + 
                                         1 * sizeof(UHCI_TD)));
    ASSERT(DescPtr->RootHubQh != NULL);
    if (DescPtr->RootHubQh == NULL) {
        return USB_ERROR;
    }

    Td = (UHCI_TD*)((UINTN)DescPtr->RootHubQh + sizeof (UHCI_QH));

    Td->pLinkPtr = UHCI_TERMINATE;
    Td->dControlStatus  = 0;
    Td->dToken =
        (UHCI_TD_IN_PACKET | ((UINT32)DUMMY_DEVICE_ADDR << 8) |
        ((UINT32)(DEFAULT_PACKET_LENGTH - 1) << 21));
    Td->pBufferPtr = (UINT32)(UINTN)Td->aDataArea;
    Td->dCSReload = 0;
    Td->bActiveFlag = 0;

    UhciInitQh(DescPtr->RootHubQh);
    DescPtr->RootHubQh->Type = Interrupt;
    DescPtr->RootHubQh->FirstTd = Td;
    DescPtr->RootHubQh->Interval = 128;
    DescPtr->RootHubQh->CallBackIndex = USB_InstallCallBackFunction(UhciRootHubQhCallBack);
    DescPtr->RootHubQh->ActiveFlag = FALSE;

    //
    // Schedule the root hub TD to 256ms schedule
    //
    UhciAddQhToFrameList(HcStruc, DescPtr->RootHubQh);

	if (gUsbData->RootHubHcStruc == NULL) {
	    Td->dCSReload =
	            UHCI_TD_INTERRUPT_ON_COMPLETE |
	            UHCI_TD_ONE_ERROR |
	            UHCI_TD_ACTIVE;
	    Td->bActiveFlag = 1;
	    Td->dControlStatus = Td->dCSReload;
        DescPtr->RootHubQh->pElementPtr = (UINT32)(UINTN)Td;
        DescPtr->RootHubQh->CurrentTd = Td;
        DescPtr->RootHubQh->ActiveFlag = TRUE;;
		gUsbData->RootHubHcStruc = HcStruc;
	}

    USB_DEBUG(DEBUG_LEVEL_4, "TD's are scheduled\n");

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_StopTDSchedule (fpHCStruc)
//
// Description:
//  This routine will stop the TD schedules and frees the data structures
//
// Input:
//  fpHCStruc   Pointer to the HC information structure
//
// Output:
//  USB_SUCCESS/USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UHCI_StopTDSchedule (
    HC_STRUC    *HcStruc
)
{
	UINT8			i;
	UHCI_DESC_PTRS	*DescPtrs = HcStruc->stDescPtrs.fpUHCIDescPtrs;
    UINT8            *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);
    //
    // Free all the TD/QH data structures
    //
    if (DescPtrs == NULL) {
        return USB_ERROR;
    }
    
    if (((UINT8*)DescPtrs < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs + sizeof(UHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINT8*)DescPtrs->StaticQh < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs->StaticQh + sizeof(UHCI_QH)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINT8*)DescPtrs->RootHubQh < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs->RootHubQh + sizeof(UHCI_QH)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINT8*)DescPtrs->RepeatQh < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs->RepeatQh + sizeof(UHCI_QH)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    USB_MemFree (DescPtrs->StaticQh, GET_MEM_BLK_COUNT(sizeof(UHCI_QH)));
	if (DescPtrs->RootHubQh) {
    	USB_MemFree (DescPtrs->RootHubQh, 
        	GET_MEM_BLK_COUNT(sizeof(UHCI_QH) + sizeof(UHCI_TD)));
	}
	if (DescPtrs->RepeatQh) {
		USB_MemFree (DescPtrs->RepeatQh, 
        	GET_MEM_BLK_COUNT(sizeof(UHCI_QH) + sizeof(UHCI_TD)));
	}
 
    //
    // Finally free the descriptor pointer
    //
    USB_MemFree (DescPtrs, GET_MEM_BLK_COUNT_STRUC(UHCI_DESC_PTRS));

	USBKeyRepeat(HcStruc, 3);

	if (gUsbData->RootHubHcStruc == HcStruc) {
		gUsbData->RootHubHcStruc  = NULL;
		for (i = 0; i < gUsbData->HcTableCount; i++) {
            if (gUsbData->HcTable[i] == NULL) {
                continue;
            }
			if ((gUsbData->HcTable[i]->bHCNumber) && 
				(gUsbData->HcTable[i]->bHCType == USB_HC_UHCI) &&
				(gUsbData->HcTable[i]->dHCFlag & HC_STATE_RUNNING) &&
				(HcStruc != gUsbData->HcTable[i])) {

				DescPtrs = gUsbData->HcTable[i]->stDescPtrs.fpUHCIDescPtrs;
                
                if (((UINT8*)DescPtrs < gUsbData->fpMemBlockStart) ||
                    ((UINT8*)(DescPtrs + sizeof(UHCI_DESC_PTRS)) > MemBlockEnd)) {
                    return USB_ERROR;
                }
                if (((UINT8*)DescPtrs->RootHubQh < gUsbData->fpMemBlockStart) ||
                    ((UINT8*)(DescPtrs->RootHubQh + sizeof(UHCI_QH)) > MemBlockEnd)) {
                    return USB_ERROR;
                }

                if (((UINT8*)DescPtrs->RootHubQh->FirstTd < gUsbData->fpMemBlockStart) ||
                    ((UINT8*)(DescPtrs->RootHubQh->FirstTd + sizeof(UHCI_TD)) > MemBlockEnd)) {
                    return USB_ERROR;
                }

                if (((UINT8*)DescPtrs->RootHubQh->CurrentTd < gUsbData->fpMemBlockStart) ||
                    ((UINT8*)(DescPtrs->RootHubQh->CurrentTd + sizeof(UHCI_TD)) > MemBlockEnd)) {
                    return USB_ERROR;
                }
                
				DescPtrs->RootHubQh->FirstTd->dCSReload =
						UHCI_TD_INTERRUPT_ON_COMPLETE |
						UHCI_TD_ONE_ERROR |
						UHCI_TD_ACTIVE;
				DescPtrs->RootHubQh->FirstTd->bActiveFlag = 1;
				DescPtrs->RootHubQh->FirstTd->dControlStatus =
						DescPtrs->RootHubQh->FirstTd->dCSReload;
                DescPtrs->RootHubQh->pElementPtr = 
                        (UINT32)(UINTN)DescPtrs->RootHubQh->FirstTd;
                DescPtrs->RootHubQh->CurrentTd = 
                        DescPtrs->RootHubQh->FirstTd;
                DescPtrs->RootHubQh->ActiveFlag = TRUE;;
				gUsbData->RootHubHcStruc = gUsbData->HcTable[i];
			}
		}
	}

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UhciProcessQh
//
// Description:
//  This function will check whether the QH is completed if so, it will call
//  the call back routine associated with the TDs present in the QH
//
// Input:
//  HcStruc     HCStruc structure
//  Qh          Pointer to the QH
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciProcessQh(
    HC_STRUC    *HcStruc,
    UHCI_QH     *Qh
)
{
    UHCI_TD     *Td;
    UINT16      Length;
    EFI_STATUS	Status;
 
    if (Qh == NULL) {
        return USB_ERROR;
    }

    if (Qh->ActiveFlag == FALSE) {
        return USB_SUCCESS;
    }

    if (Qh->FirstTd == NULL) {
        return USB_SUCCESS;
    }

    if (Qh->CurrentTd == NULL) {
        Qh->CurrentTd = Qh->FirstTd;
    }

    Td = Qh->CurrentTd;
    while (Td) {
        Qh->CurrentTd = Td;
        Qh->DataToggle = Td->dToken & UHCI_TD_DATA_TOGGLE ? 1 : 0;

        if (Td->dControlStatus & UHCI_TD_ACTIVE) {
            return USB_ERROR;
        }

        Length = (UINT16)((Td->dControlStatus + 1) & UHCI_TD_ACTUAL_LENGTH);
        Qh->BytesTransferred += Length;

        if (Td->dControlStatus & UHCI_TD_STATUS_FIELD) {
            break;
        }

        Qh->DataToggle ^= 1;
        Qh->ShortPacketDetected = (Length < (((Td->dToken >> 21) + 1) & 0x7FF));

        if (Qh->ShortPacketDetected) {
            if (Qh->Type == Control) {
                while (!(Td->pLinkPtr & UHCI_TERMINATE)) {
                    Td = (UHCI_TD*)((UINTN)Td->pLinkPtr & UHCI_POINTER_MASK);
                }
                Qh->pElementPtr = (UINT32)(UINTN)Td;
                continue;
            }
            break;
        }
 
        Td = Td->pLinkPtr & UHCI_TERMINATE ?
                NULL : (UHCI_TD*)(Td->pLinkPtr & UHCI_POINTER_MASK);
    }

    Qh->ActiveFlag = FALSE;
    if (Qh->CallBackIndex == 0) {
        return USB_SUCCESS;
    }

    if ((Qh->CallBackIndex) && (Qh->CallBackIndex <= MAX_CALLBACK_FUNCTION)) {
        if (gUsbData->aCallBackFunctionTable[Qh->CallBackIndex - 1]) {
            if ((gUsbData->aCallBackFunctionTable[Qh->CallBackIndex - 1] != UhciRepeatQhCallback) && 
                (gUsbData->aCallBackFunctionTable[Qh->CallBackIndex - 1] != UhciRootHubQhCallBack)) {
                Status = UsbDevInfoValidation(Qh->DevInfoPtr);
                if (EFI_ERROR(Status)) {
                    return USB_ERROR;
                }
            }
            (*gUsbData->aCallBackFunctionTable[Qh->CallBackIndex - 1])(
                    HcStruc,
                    (DEV_INFO*)Qh->DevInfoPtr,
                    (UINT8*)Qh,
                    0,
                    0);
        }
    }

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UhciProcessTd
//
// Description:
//  This function will check whether the TD is completed if so, it will call
//  the call back routine associated with this TD
//
// Input:
//  HcStruc     HCStruc structure
//  Td          Pointer to the TD
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
// Notes:
//  For any TD whose ActiveFlag is TRUE and its ControlStatus bit 23 is clear
//  (completed), process the TD by calling its callback routine, if one is present.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciProcessTd(
    HC_STRUC    *HcStruc,
    UHCI_TD     *Td
)
{
    UINT8       DevAddr;
	DEV_INFO    *DevInfo;

    if (Td == NULL) {   // Check for NULL
        return USB_ERROR;
    }

    if (Td->bActiveFlag == 0) {
        return USB_SUCCESS;
    }

    if (Td->dControlStatus & UHCI_TD_ACTIVE) {
        return USB_ERROR;
    }

    Td->bActiveFlag = 0;
    if ((Td->bCallBackIndex) && (Td->bCallBackIndex <= MAX_CALLBACK_FUNCTION)) {
        //
        // Get the device address from the completed TD
        //
        DevAddr = (UINT8)(((Td->dToken) >> 8) & 0x7F);
        DevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR, 0,
                        DevAddr, HcStruc);

        if (gUsbData->aCallBackFunctionTable[Td->bCallBackIndex - 1]) {
            (*gUsbData->aCallBackFunctionTable[Td->bCallBackIndex - 1])(
                    HcStruc,
                    DevInfo,
                    (UINT8*)Td,
                    0,
                    0);
        }
    }

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UhciProcessFrameList
//
// Description:
//  This function will parse through frame list to find completed QH/TD
//  and invoke corresponding call back routine
//
// Input:
//  HcStruc     HCStruc structure
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
// Notes:
//  For any TD whose ActiveFlag is TRUE and its ControlStatus bit 23 is clear
//  (completed), process the TD by calling its call back routine, if one is present.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciProcessFrameList (
    HC_STRUC    *HcStruc
)
{
    UINT32  ListPtr;
    EFI_STATUS  Status = EFI_SUCCESS;

    ListPtr = HcStruc->fpFrameList[0];

    while (!(ListPtr & UHCI_TERMINATE)) {
        if (ListPtr & UHCI_QUEUE_HEAD) {
#if USB_RUNTIME_DRIVER_IN_SMM
            Status = AmiValidateMemoryBuffer((VOID*)ListPtr, sizeof(UHCI_QH));
            if (EFI_ERROR(Status)) {
               return USB_ERROR;
            }
#endif
            UhciProcessQh(HcStruc, (UHCI_QH*)(ListPtr & UHCI_POINTER_MASK));
            ListPtr = ((UHCI_QH*)(ListPtr & UHCI_POINTER_MASK))->pLinkPtr;
        } else {
#if USB_RUNTIME_DRIVER_IN_SMM
            Status = AmiValidateMemoryBuffer((VOID*)ListPtr, sizeof(UHCI_TD));
            if (EFI_ERROR(Status)) {
               return USB_ERROR;
            }
#endif
            UhciProcessTd(HcStruc, (UHCI_TD*)(ListPtr & UHCI_POINTER_MASK));
            ListPtr = ((UHCI_TD*)(ListPtr & UHCI_POINTER_MASK))->pLinkPtr;
        }
    }
	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_RootHubTDCallBack
//
// Description:
//  This function is called when TD256ms completes a transaction. This TD runs
//  a dummy interrupt transaction to a non-existant device address for the
//  purpose of generating a periodic timeout interrupt.  This periodic interrupt
//  may be used to check for new devices on the root hub etc.
//
// Input:
//  fpHCStruc   Pointer to the HCStruc structure
//  fpDevInfo   NULL (pDevInfo is not valid)
//  fpTD        Pointer to the TD that completed
//  fpBuffer    Not used
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciRootHubQhCallBack(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Qh,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UINT8       Index;
    HC_STRUC    *Hc;
    UINT16      IoPort;
	UINT16		PortAddr;
    UHCI_QH     *RootHubQh;

	//
	// First deactivate the TDRootHub so this callback function will not get
	// reentered.
	//
    if (Qh != NULL) {
        RootHubQh = (UHCI_QH*)Qh;
        RootHubQh->FirstTd->bActiveFlag = 0;
    }

    for (Index = 0; Index < gUsbData->HcTableCount; Index++) {
        Hc = gUsbData->HcTable[Index];
        if (Hc == NULL) {
            continue;
        }

        if (Hc->bHCType != USB_HC_UHCI) {	// Process for UHCI only
			continue;
        }

		if (!(Hc->dHCFlag & HC_STATE_RUNNING)) {
			continue;
		}

		//
		// Check whether the controller is still under BIOS control
		// Read the frame list base address and compare with stored value
		//
		IoPort = (UINT16)Hc->BaseAddress;
		if ((DwordReadIO(IoPort + UHCI_FRAME_LIST_BASE) & 0xFFFFF000) 
			!= (UINT32)Hc->fpFrameList) {
			continue;
		}

		//
		// Check whether USB host controllers are accessible to aVOID system 
		// hang in ports enumeration.
		//
		if (ByteReadIO(IoPort) == 0xFF) {
			continue;
		}

		//
		// Check whether enumeration is already began
		//
		if(gUsbData->bEnumFlag == FALSE) {
			gUsbData->bEnumFlag = TRUE;

			//
			// Mask the Host Controller interrupt so the ISR does not get re-entered due
			// to an IOC interrupt from any TDs that complete in frames while we are
			// configuring a new device that has just been plugged in.
			//
			// Disable IOC, timeout & CRC interrupt
			//
			WordWriteIO((UINT16)(IoPort + UHCI_INTERRUPT_ENABLE), 0);
		
			//
			// Process Port#1 and clear Port#1 status bit
			//
			PortAddr = IoPort + UHCI_PORT1_CONTROL;
			if (WordReadIO(PortAddr) & UHC_CONNECT_STATUS_CHANGE) {
				USBCheckPortChange(Hc, Hc->bHCNumber | BIT7, 1);
				WordWriteIO(PortAddr, WordReadIO(PortAddr));
			}
		
			//
			// Process Port#2 and clear Port#2 status bit
			//
			PortAddr = IoPort + UHCI_PORT2_CONTROL;
			if (WordReadIO(PortAddr) & UHC_CONNECT_STATUS_CHANGE) {
				USBCheckPortChange(Hc, Hc->bHCNumber | BIT7, 2);
				WordWriteIO(PortAddr, WordReadIO(PortAddr));
			}

			//
			// Renable interrupts from the host controller
			// Enable IOC, timeout & CRC interrupt
			//
			WordWriteIO((UINT16)(IoPort + UHCI_INTERRUPT_ENABLE), (UINT16)(UHC_IOC_ENABLE));

			gUsbData->bEnumFlag = FALSE;
		}
    }

	//
	// Reactivate the TdRootHub
	//
    if (Qh != NULL) {
        RootHubQh->FirstTd->dControlStatus	= RootHubQh->FirstTd->dCSReload;
        RootHubQh->FirstTd->bActiveFlag = 1;
        RootHubQh->pElementPtr = (UINT32)(UINTN)RootHubQh->FirstTd;
        RootHubQh->CurrentTd = RootHubQh->FirstTd;
        RootHubQh->ActiveFlag = TRUE;
    }

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_RepeatTDCallback
//
// Description:
//  This function is called when TdRepeat completes a transaction.  This TD
//  runs a dummy interrupt transaction to a non-existant device address for
//  the purpose of generating a periodic timeout interrupt which in turn is
//  used to generate keyboard repeat.
//
// Input:
//  fpHCStruc   Pointer to the HCStruc structure
//  fpDevInfo   NULL (pDevInfo is not valid)
//  fpTD        Pointer to the TD that completed
//  fpBuffer    Not used
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciRepeatQhCallback(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Qh,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UHCI_QH *RepeatQh = (UHCI_QH*)Qh;

    USB_DEBUG(DEBUG_LEVEL_8, "Processing Repeat TD ...\n");
    //
    // First deactivate the TdRepeat so this callback function will not get
    // re-entered.
    //
    RepeatQh->FirstTd->bActiveFlag = 0;

#if USB_DEV_KBD
    USBKBDPeriodicInterruptHandler(HcStruc);
#endif
    //
    // Reactivate the TdRepeat
    //
    if (RepeatQh->FirstTd->dCSReload & UHCI_TD_ACTIVE) {
        RepeatQh->FirstTd->dControlStatus = RepeatQh->FirstTd->dCSReload;
        RepeatQh->FirstTd->bActiveFlag = 1;
        RepeatQh->pElementPtr = (UINT32)(UINTN)RepeatQh->FirstTd;
        RepeatQh->CurrentTd = RepeatQh->FirstTd;
        RepeatQh->ActiveFlag = TRUE;
	}

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UHCI_PollingTDCallback
//
// Description:
//  This function is called when a polling TD from the TD pool completes an
//  interrupt transaction to its assigned device.
//  This routine should process any data in the TD's data buffer, handle any
//  errors, and then copy the TD's CSReloadValue field into its control status
//  field to put the TD back into service.
//
// Input:
//  fpHCStruc   Pointer to the HCStruc structure
//  fpDevInfo   NULL (pDevInfo is not valid)
//  fpTD        Pointer to the TD that completed
//
// Output:
//  USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciPollingQhCallback(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Qh,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UHCI_QH     *PollQh = (UHCI_QH*)Qh;   

    USB_DEBUG(DEBUG_LEVEL_8, "Processing polling TD ...\n");

	UsbUpdateDataToggle(DevInfo, DevInfo->IntInEndpoint, 
			PollQh->DataToggle);

    if ((PollQh->CurrentTd->dControlStatus & UHCI_TD_STATUS_FIELD) == 0) {
        if ((DevInfo->bCallBackIndex) && (DevInfo->bCallBackIndex <= MAX_CALLBACK_FUNCTION)) {
            if (gUsbData->aCallBackFunctionTable[DevInfo->bCallBackIndex - 1]) {
                (*gUsbData->aCallBackFunctionTable[DevInfo->bCallBackIndex-1])(
                        HcStruc,
                        DevInfo,
                        Qh,
                        DevInfo->fpPollDataBuffer,
                        PollQh->BytesTransferred);
            }
        }
    }

	UhciActivateTds(PollQh->FirstTd, PollQh->DataToggle);

    PollQh->pElementPtr = (UINT32)(UINTN)PollQh->FirstTd;
    PollQh->CurrentTd = PollQh->FirstTd;
    PollQh->BytesTransferred = 0;
    PollQh->ActiveFlag = TRUE;

    return  USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UhciInitQh
//
// Description: This function check whether HC is halted.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UhciInitQh (
    UHCI_QH *Qh
)
{
    Qh->pLinkPtr = UHCI_TERMINATE;
    Qh->pElementPtr = UHCI_TERMINATE;
    Qh->CurrentTd = NULL;
    Qh->DataToggle = 0;
    Qh->BytesTransferred = 0;
    Qh->ShortPacketDetected = FALSE;
    Qh->FirstTd = NULL;
    Qh->Interval = 0;
    Qh->CallBackIndex = 0;
    Qh->ActiveFlag = FALSE;
    Qh->DevInfoPtr = NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UhciIsHalted
//
// Description: This function check whether HC is halted.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
UhciIsHalted (
	HC_STRUC	*HcStruc
)
{
	return (ByteReadIO((UINT16)(HcStruc->BaseAddress + UHCI_STATUS_REG)) & UHC_HC_HALTED) == UHC_HC_HALTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UhciTranslateInterval
//
// Description: This function calculates the polling rate.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UhciTranslateInterval(
    UINT8   Interval
)
{
    UINT8  BitCount = 0;

    // The Interval value should be from 1 to 255
    ASSERT(Interval >= 1 && Interval <= 255);

    for (BitCount = 0; Interval != 0; BitCount++) {
        Interval >>= 1;
    }
    return (1 << (BitCount - 1));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UhciAllocGeneralTds
//
// Description: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UHCI_TD*
UhciAllocGeneralTds (
	IN UINT8		DeviceAddr,
	IN BOOLEAN		LowSpeed,
	IN UINT8		PacketId,
	IN UINT8        EndpointAddr,
	IN UINT16		MaxPacket,
	IN BOOLEAN		ShortPacket,
    IN OUT UINTN    *BufferAddr,
    IN OUT UINT32   *Length,
    IN OUT UINT8    *DataToggle
)
{
	UINT16		NumTds = 0;
	UHCI_TD		*FirstTd = NULL;
	UHCI_TD		*Td = NULL;
	UINTN		Address = *BufferAddr;
	UINT32		BytesRemaining = *Length;
	UINT8		Toggle = *DataToggle;
	UINT16		MaxLen = 0;

	if (BytesRemaining == 0) {
		return NULL;
	}

	NumTds = BytesRemaining / MaxPacket;
	if (BytesRemaining % MaxPacket) {
		NumTds++;
	}

	FirstTd = USB_MemAlloc(GET_MEM_BLK_COUNT(NumTds * sizeof(UHCI_TD)));
	if (FirstTd == NULL) {
		return NULL;
	}
	
	for (Td = FirstTd;;) {
		MaxLen = BytesRemaining > MaxPacket ? MaxPacket : BytesRemaining;

		Td->pLinkPtr = UHCI_TERMINATE;
		Td->dToken = (UINT32)PacketId | ((UINT32)DeviceAddr << 8) | 
						((UINT32)EndpointAddr << 15) | ((MaxLen - 1) << 21);
		if (Toggle) {
			Td->dToken |= UHCI_TD_DATA_TOGGLE;
		}

		Td->pBufferPtr = (UINT32)Address;
		Td->dCSReload = UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE;
		if (LowSpeed) {
			Td->dCSReload |= UHCI_TD_LOW_SPEED_DEVICE;
		}
		if (ShortPacket) {
			Td->dCSReload |= UHCI_TD_SHORT_PACKET_DETECT;
		}
		Td->dControlStatus = Td->dCSReload;
		Td->bActiveFlag = 1;

		BytesRemaining -= MaxLen;
		Address += MaxLen;
		Toggle ^= 1;

		if (BytesRemaining == 0) {
			break;
		}

		Td->pLinkPtr = (UINT32)(((UINTN)Td + sizeof(UHCI_TD)) | UHCI_VERTICAL_FLAG);
		Td = (UHCI_TD*)((UINTN)Td->pLinkPtr & UHCI_POINTER_MASK);
	}

	Td->dCSReload |= UHCI_TD_INTERRUPT_ON_COMPLETE;
	Td->dControlStatus = Td->dCSReload;

	*Length = BytesRemaining;
	*BufferAddr = Address;
	*DataToggle = Toggle;
	
	return FirstTd;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UhciFreeTds
//
// Description: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UhciFreeTds (
	IN UHCI_TD	*FirstTd
)
{
	UHCI_TD	*Td = FirstTd;
	UINT16	NumTds = 0;

	if (FirstTd == NULL) {
		return;
	}

	while (Td) {
		NumTds++;
        Td = Td->pLinkPtr & UHCI_TERMINATE ?
                NULL : (UHCI_TD*)((UINTN)Td->pLinkPtr & UHCI_POINTER_MASK);
	}

	USB_MemFree(FirstTd, GET_MEM_BLK_COUNT(NumTds * sizeof(UHCI_TD)));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UhciActivateTds
//
// Description: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UhciActivateTds (
	IN UHCI_TD	*FirstTd,
	IN UINT8	DataToggle
)
{
	UHCI_TD	*Td = FirstTd;
	UINT8	Toogle = DataToggle;

	if (FirstTd == NULL) {
		return;
	}

	while (Td) {
		Td->dToken &= ~UHCI_TD_DATA_TOGGLE;
		if (Toogle) {
			Td->dToken |= UHCI_TD_DATA_TOGGLE;
		}
    	Td->dControlStatus = Td->dCSReload;
		Td->bActiveFlag = 1;

		Toogle ^= 1;
        Td = Td->pLinkPtr & UHCI_TERMINATE ?
                NULL : (UHCI_TD*)((UINTN)Td->pLinkPtr & UHCI_POINTER_MASK);
	}
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
