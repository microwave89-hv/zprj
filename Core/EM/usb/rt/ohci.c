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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/ohci.c 98    10/16/16 10:12p Wilsonlee $
//
// $Revision: 98 $
//
// $Date: 10/16/16 10:12p $
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/ohci.c $
// 
// 98    10/16/16 10:12p Wilsonlee
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
// 97    7/28/16 4:56a Wilsonlee
// [TAG]  		EIP264662
// [Category]  	Improvement
// [Description]  	Don't install usb hw smi after reconnecting usb
// controllers.
// [Files]  		uhcd.c, usb.c, ohci.c, amiusb.c, amiusbhc.c
// 
// 96    7/22/16 3:50a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 95    7/07/16 1:09a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 94    3/14/16 10:21p Wilsonlee
// [TAG]  		EIP257506
// [Category]  	Improvement
// [Description]  	Add USB_KEYREPEAT_INTERVAL token to change the key
// repeat interval.
// [Files]  		usb.sdl, xhci.h, usbkbd.h, uhci.c, ohci.c, ehci.c
// 
// 93    3/02/16 9:42p Wilsonlee
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
// 92    9/01/15 10:46p Wilsonlee
// [TAG]  		EIP235977
// [Category]  	Improvement
// [Description]  	Break the loop which we check list processing TD if
// NextTd is the same as Td.
// [Files]  		ohci.c
// 
// 91    3/08/15 10:50p Wilsonlee
// [TAG]  		EIP207774
// [Category]  	Improvement
// [Description]  	Set USB_FLAG_DRIVER_STARTED flag when HC is running and
// clear it if we don't start any HC.
// [Files]  		uhci.c, usb.c, ehci.c, ohci.c, xhci.c, amiusb.h
// 
// 90    1/22/15 10:19p Wilsonlee
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
// 89    5/01/14 3:56a Ryanchou
// [TAG]  		EIP162589
// [Category]  	Improvement
// [Description]  	Do not register external controller as key repeat
// controller.
// [Files]  		ehci.c, ohci.c, uhci.c
// 
// 88    4/30/14 6:13a Ryanchou
// [TAG]  		EIP151374
// [Category]  	Improvement
// [Description]  	Calculates maximum data length to be reported in the
// HID device.
// [Files]  		ehci.c, ohci.c, uhci.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, xhci.c
// 
// 87    4/30/14 5:25a Wilsonlee
// [TAG]  		EIP164842
// [Category]  	Improvement
// [Description]  	Check if the devices have put into to our queue before
// we put them.
// [Files]  		UsbInt13.c, amiusb.c, ehci.c, ohci.c, usb.c, usbdef.h,
// usbmass.c, xhci.c, amiusbhc.c, efiusbmass.c, uhcd.c, usbbus.c, usbsb.c
// 
// 86    2/26/14 1:56a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 85    7/26/13 2:36a Ryanchou
// [TAG]  		EIP122142
// [Category]  	Improvement
// [Description]  	Improve periodic schedule mechanism
// [Files]  		ehci.c, ehci.h, ohci.c, ohci.h, uhci.c, uhci.h, usbdef.h,
// amiusbhc.c
// 
// 84    7/22/13 10:31p Wilsonlee
// [TAG]  		EIP125357
// [Category]  	Improvement
// [Description]  	Check if the port releases to a select host controller.
// [Files]  		uhci.c, usb.c, usbhub.c, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 83    6/28/13 2:29a Roberthsu
// [TAG]           EIP124581 
// [Category]      Improvement
// [Description]   Controller driver always return the length passed in
// parameter, devices may return zero length data, it should be corrected.
// [Files]         ohci.c
// 
// 82    6/02/13 11:42p Wilsonlee
// [TAG]  		EIP123235
// [Category]  	Improvement
// [Description]  	Stop the usb host controller at ExitBootService if it
// is an extend card or it doesn't support HW SMI.
// [Files]  		xhci.c, ehci.c, uhci.c, ohci.c, amiusb.c, usbdef.h, usbsb.c,
// uhcd.c
// 
// 81    4/18/13 1:02p Ryanchou
// Add Teradici USB controller support.
// 
// 80    4/10/13 11:23p Ryanchou
// [TAG]  		EIP111483
// [Category]  	Improvement
// [Description]  	Increase the delay when OHCI port reset complete.
// [Files]  		ohci.c
// 
// 79    3/19/13 3:59a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 78    3/18/13 4:48a Ryanchou
// [TAG]  		EIP98377
// [Category]  	Improvement
// [Description]  	Optimize USB controller timing.
// [Files]  		usb.sdl, usbport.c, ehci.c, elib.c, ohci.c, uhci.c,
// usbdef.h, usbhub.c, xhci.c, uhcd.c
// 
// 77    2/24/13 9:00p Wilsonlee
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
// 76    1/11/13 4:16a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 75    12/24/12 5:06a Ryanchou
// [TAG]  		EIP103031
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hans when loading QNX 6.5.0
// [RootCause]  	The EHCI port detect change SMI is generated after
// ownership change to OS.
// [Solution]  	Clear the SMI enable bits and status bits even the
// controller is OS owned.
// [Files]  		ehci.c, ohci.c
// 
// 74    12/06/12 12:39a Wilsonlee
// [TAG]  		EIP103186
// [Category]  	Improvement
// [Description]  	Handle the error case "MEMIO was disabled" in USB
// driver.
// [Files]  		uhci.c, ohci.c, ehci.c, xhci.c
// 
// 73    11/13/12 7:12a Wilsonlee
// [TAG]  		EIP82553
// [Category]  	New Feature
// [Description]  	Support usb S5 wake up function for XHCI.
// [Files]  		usb.c, ehci.c, ohci.c, xhci.c, xhci.h
// 
// 72    11/10/12 6:40a Ryanchou
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
// 71    10/25/12 4:16a Wilsonlee
// [TAG]  		EIP82354
// [Category]  	New Feature
// [Description]  	Support usb S5 wake up function for OHCI.
// [Files]  		usb.c, ehci.c, ohci.c
// 
// 70    9/28/12 2:37a Wilsonlee
// [TAG]  		EIP93154
// [Category]  	Improvement
// [Description]  	Change the unit of the FixedDelay from 15 us to 1 us.
// [Files]  		amiusb.h, xhci.c, ehci.c, ohci.c, uhci.c, usb.c, usbCCID.c,
// usbmass.c, usbhub.c, elib.c
// 
// 69    8/29/12 8:17a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 68    8/28/12 5:19a Ryanchou
// [TAG]  		EIP98857
// [Category]  	Improvement
// [Description]  	WriteBackDoneHead status bit shall be cleared even
// HccaDoneHead is zero.
// [Files]  		ohci.c
// 
// 67    7/25/12 4:44a Wilsonlee
// [TAG]  		EIP95959
// [Category]  	Improvement
// [Description]  	Don't set INTERRUPT_ROUTING if the ohci is external usb
// pci controller card.
// [Files]  		ohci.c
// 
// 66    5/04/12 6:38a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 65    5/04/12 5:25a Wilsonlee
// [TAG]  		EIP89307
// [Category]  	Improvement
// [Description]  	Modify incorrect #pragma pack directive.
// [Files]  		amidef.h, amiusb.c, ehci.h, ohci.c, ohci.h, uhci.h, usb.c,
// usbdef.h, xhci.h, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h,
// UsbIo.h
// 
// 64    5/03/12 6:01a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 63    11/08/11 1:57a Ryanchou
// [TAG]  		EIP63188
// [Category]  	Improvement
// [Description]  	External USB controller support.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, uhcd.c, uhcd.h, uhci.c,
// usbdef.h, usbmisc.c, usbsb.c, xhci.c
// 
// 62    9/26/11 11:40p Roberthsu
// [TAG]  		EIP67230
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Ntrig touch panel can not use on CedarTrail
// [RootCause]  	Because ntrig report data over than 512 byte.Control
// transfer check if over 512 than set length is 512.
// [Solution]  	Remove check transfer length.
// [Files]  		ohci.c,uhci.c,usbhid.c
// 
// 61    8/24/11 2:14a Ryanchou
// [TAG]  		EIP66448
// [Category]  	New Feature
// [Description]  	Clear connect status change and port enable status
// change.
// [Files]  		ohci.c
// 
// 60    8/08/11 6:58a Ryanchou
// [TAG]  		EIP54018
// [Category]  	New Feature
// [Description]  	Added USB S5 wake up support.
// [Files]  		amiusb.c, ehci.c, ohci.c, uhci.c, usb.c, usb.sdl, usbdef.h,
// usbsb.c xhci.c
// 
// 59    8/08/11 5:15a Ryanchou
// [TAG]  		EIP60561
// [Category]  	New Feature
// [Description]  	Add USB timing policy protocol for timing override.
// [Files]  		ehci.c, guids.c, ohci.c, uhcd.c, uhci.c usb.c, usbdef.h,
// usbhub.c, usbmass.c, UsbPolicy.h, usbport.c usbsrc.sdl
// 
// 58    7/15/11 6:11a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c, usb.c, usbdef.h,
// usbkbd.c, usbkbd.h, usbms.c, usbrt.cif, usbsb.c, usbsetup.c,
// usbsrc.sdl, xhci.c
// 
// 57    7/12/11 8:10a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
// 56    7/12/11 6:17a Ryanchou
// [TAG]  		EIP59707
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	The wireless USB keyboard does not work after boot into
// windows loader.
// [RootCause]  	The amount of data returned by the device exceeded the
// size of the maximum data packet allowed, that causes babble error, and
// BIOS does not re-init the polling TD.
// [Solution]  	Re-init polling TD even the last transaction get error.
// [Files]  		ohci.c
// 
// 55    6/21/11 9:56a Ryanchou
// [TAG]  		EIP59663
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Plug USB WLAN device may causes OHCI malfunction.
// [RootCause]  	The devices have to connect to OHCI first, or it can't be
// configured.
// [Solution]  	Port routing route to EHCI after OHCI initialization.
// [Files]  		ehci.c, ohci.c
// 
// 54    5/03/11 10:10a Ryanchou
// [TAG]  		EIP54283
// [Category]  	Improvement
// [Description]  	Follow XHCI spec ver 1.0 section 4.6.8 to recovery
// endpoint halt. 
// [Files]  		ehci.c, ohci.c, uhci.c, usbdef.h, usbmass.c, xhci.c
// 
// 53    4/06/11 1:33a Ryanchou
// [TAG]  		EIP54782
// [Category]  	Improvement
// [Description]  	Change polling data size of HID devices to max packet
// size of interrupt endpoint.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, xhci.c
// 
// 52    3/30/11 9:04a Ryanchou
// 
// 51    3/29/11 10:50p Ryanchou
// [TAG]  		EIP55401
// [Category]  	Improvement
// [Description]  	Improve the USB 3.0 device compatibility.
// [Files]  		ehci.c, ehci.h, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c,
// xhci.c
// 
// 50    3/29/11 10:11a Ryanchou
// [TAG]  		EIP53518
// [Category]  	Improvement
// [Description]  	Added chipset xHCI chip support.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhcd.c, uhci.c, usb.c,
// usb.sdl, usbdef.h, usbport, usbsb.c, xhci.c
// 
// 49    3/16/11 8:51a Ryanchou
// [TAG]  		EIP55025
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Finger Print function fail
// [RootCause]  	Wrong tranferred data size on short packet condition.
// [Files]  		ohci.c
// 
// 48    11/11/10 11:34p Ryanchou
// [TAG]  		EIP45578
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB 3.0 device can't be detected.
// [RootCause]  	Address Device Command fails.
// [Solution]  	Reset the device and attempt the Address Device Command
// again.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c, xhci.c
// 
// 47    9/24/10 5:38p Olegi
// EIP38221: Added the code that properly initializes
// DEV_INFO.bIntEndpoint field; interrupt endpoint polling is using this
// endpoint number.
// 
// 46    6/07/10 8:55a Ryanchou
// EIP38547: Fixed system halt when installing FreeBSD.
// 
// 45    3/10/10 6:35p Olegi
// 
// 44    3/06/10 1:11p Olegi
// 
// 43    2/26/10 4:23p Olegi
// 
// 42    2/23/10 1:21p Olegi
// Work around Klockwork issues. EIP34370
// 
// 41    2/08/10 10:00a Olegi
// EIP33381: Implement multiple bulk endpoint in UsbIoProtocol.
// 
// 40    1/04/10 9:20a Olegi
// EIP32956: Polling rate for the keyboards has been changed from 8 ms to
// 32 ms.
// 
// 39    12/23/09 11:59a Olegi
// 
// 38    12/08/09 3:33p Olegi
// EIP32387: Bugfix in OHCI_FreeAllStruc; memory was not released properly
// when USB_FORCE_64BIT_ALIGNMENT is set.
// 
// 37    11/24/09 12:43p Olegi
// EIP#26693: fixed OHCI_DISABLE_32MS_POLLING implementation.
// 
// 36    10/30/09 5:47p Olegi
// 
// 35    10/13/09 9:11a Olegi
// EIP28707: OHCI ownership change modifications.
// 
// 34    10/07/09 9:48a Olegi
// USB Hub error handling improvement. EIP#25601.
// 
// 33    9/15/09 10:21a Olegi
// Added USB_INCMPT_HID_DATA_OVERFLOW incompatibility type.
// 
// 32    2/17/09 4:01p Olegi
// 
// 31    2/17/09 8:59a Olegi
// Additional modifications in BulkTransfer routine to maximize the
// bandwidth.
// 
// 30    1/30/09 10:08a Olegi
// MAX_BULK_DATA_SIZE limitation moved to individual HC drivers.
// 
// 29    10/06/08 3:33p Olegi
// EHCI change ownership testing in DOS fix (EIP#14855).
// 
// 28    9/24/08 3:58p Olegi
// Bugfix in the memory allocation in OHCI_ActivatePolling.
// 
// 27    6/16/08 10:07a Olegi
// Bugfix in OHCI_Start.
// 
// 26    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 25    7/09/07 2:11p Olegi
// Changed the maximum data size of the BulkTransfer from 1kB to 64kB.
// 
// 24    4/17/07 8:24a Olegi
// Device detection algorythm update, in sync with Core8.
// 
// 23    3/20/07 12:22p Olegi
//
// 22    1/16/07 3:24p Olegi
// Change in OHCI_ControlTransfer: return 0 if transfer stalled.
//
// 21    1/02/07 12:17p Olegi
//
// 20    1/02/07 11:13a Olegi
//
// 19    12/28/06 4:32p Olegi
// OHCI_ProcessRootHubStatusChange is modified to properly clear the
// connect change status bit
//
// 18    12/22/06 4:05p Olegi
// Timeout implementation.
//
// 17    12/20/06 2:30p Olegi
//
// 16    12/13/06 5:40p Olegi
// X64 build update
//
// 14    11/09/06 10:16a Olegi
//
// 13    10/18/06 9:43a Andriyn
// Fix: race condition on hot-plug in / plug-off
//
// 12    10/12/06 9:37p Andriyn
// Fix: unexpected plug-off hangs with endless TIMEOUTs
//
// 11    6/09/06 10:29a Olegi
// USB_FLAG_ENABLE_BEEP_MESSAGE flag is reset while handling change of the
// controller ownership.
//
// 10    5/16/06 11:22a Olegi
//
// 9     4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 8     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 7     3/06/06 6:26p Olegi
//
// 6     1/11/06 11:53a Olegi
//
// 5     12/01/05 5:48p Olegi
//
// 4     11/29/05 12:33p Andriyn
//
// 3     6/20/05 8:55a Olegi
// .NET compiler with highest warning level and warning-as-error
// modification.
//
// 2     6/03/05 6:09p Olegi
// HW SMI registration change.
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
//  Name:           Ohci.c
//
//  Description:    AMI USB OHCI driver source file
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

#pragma warning (disable :4213)
#pragma warning (disable :4706)

UINT8   OHCI_FillHCDEntries(HCD_HEADER*);
UINT8   OHCI_Start (HC_STRUC*);
UINT8   OHCI_Stop (HC_STRUC*);
UINT8   OHCI_DisableInterrupts (HC_STRUC*);
UINT8   OHCI_EnableInterrupts (HC_STRUC*);
UINT8   OHCI_ProcessInterrupt(HC_STRUC*);
UINT8   OHCI_GetRootHubStatus (HC_STRUC*,UINT8, BOOLEAN);
UINT8   OHCI_DisableRootHub (HC_STRUC*,UINT8);
UINT8   OHCI_EnableRootHub (HC_STRUC*,UINT8);
UINT16  OHCI_ControlTransfer (HC_STRUC*,DEV_INFO*,UINT16,UINT16,UINT16,UINT8*,UINT16);
UINT32  OHCI_BulkTransfer (HC_STRUC*,DEV_INFO*,UINT8,UINT8*,UINT32);
UINT16  OHCI_InterruptTransfer (HC_STRUC*, DEV_INFO*, UINT8, UINT16, UINT8*, UINT16);
UINT8   OHCI_DeactivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   OHCI_ActivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   OHCI_DisableKeyRepeat (HC_STRUC*);
UINT8   OHCI_EnableKeyRepeat (HC_STRUC*);
UINT8   OHCI_ResetRootHub (HC_STRUC*,UINT8);
UINT8   OHCI_GlobalSuspend (HC_STRUC*);	//(EIP54018+)

UINT8   OHCI_EnumeratePorts(HC_STRUC*);
UINT8   OHCI_StartEDSchedule(HC_STRUC*);
UINT8   OhciAddPeriodicEd (HC_STRUC*, OHCI_ED*);
UINT8   OhciRemovePeriodicEd (HC_STRUC*, OHCI_ED*);
UINT8   OHCI_RepeatTDCallBack(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   OHCI_ResetHC(HC_STRUC*);
UINT8   OHCI_StopUnsupportedHC(HC_STRUC*);
UINT32  OHCI_ProcessRootHubStatusChange(HC_STRUC*);
UINT8   OHCIWaitForTransferComplete(HC_STRUC*, OHCI_ED*, OHCI_TD*,DEV_INFO*);
UINT8   OHCI_ControlTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID    OHCI_ProcessTD(HC_STRUC*, OHCI_TD*);
UINT8   OHCI_GeneralTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   OHCI_PollingTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID    StopControllerType(UINT8);
UINT8   USBCheckPortChange (HC_STRUC*, UINT8, UINT8);
VOID	OHCI_FreeAllStruc(HC_STRUC* fpHCStruc);			//(EIP28707+)
BOOLEAN OhciIsHalted(HC_STRUC*);
UINT8   OhciTranslateInterval(UINT8);

UINT8	UsbGetDataToggle(DEV_INFO*,UINT8);
VOID	UsbUpdateDataToggle(DEV_INFO*, UINT8, UINT8);

extern  USB_GLOBAL_DATA     *gUsbData;
extern  BOOLEAN  gCheckUsbApiParameter;

extern  void        USB_InitFrameList (HC_STRUC*, UINT32);
extern  UINT32      ReadPCIConfig(UINT16, UINT8);
extern  void        WordWritePCIConfig(UINT16, UINT8, UINT16);
extern  void        DwordWritePCIConfig(UINT16, UINT8, UINT32);
extern  UINT32      DwordReadMem(UINT32, UINT16);
extern  void        DwordWriteMem(UINT32, UINT16, UINT32);
extern  void        DwordSetMem(UINT32, UINT16, UINT32);
extern  void        DwordResetMem(UINT32, UINT16, UINT32);
extern  void        FixedDelay(UINTN);
extern  void*       USB_MemAlloc (UINT16);
extern  UINT8       USB_InstallCallBackFunction (CALLBACK_FUNC);
extern  DEV_INFO*   USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);
extern  UINT8       USB_MemFree(void _FAR_*, UINT16);
extern	UINT8		USB_DisconnectDevice(HC_STRUC*, UINT8, UINT8);	//(EIP28707+)
#if USB_DEV_KBD
extern  void        USBKBDPeriodicInterruptHandler(HC_STRUC*);
extern  void        USBKeyRepeat(HC_STRUC*, UINT8);
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_FillHCDEntries
//
// DESCRIPTION: This function fills the host controller driver
//              routine pointers
//
// PARAMETERS:  fpHCDHeader     Ptr to the host controller header structure
//
// RETURN:      Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_FillHCDEntries(HCD_HEADER *fpHCDHeader)
{
    //
    // Fill the routines here
    //
    fpHCDHeader->pfnHCDStart                = OHCI_Start;
    fpHCDHeader->pfnHCDStop                 = OHCI_Stop;
    fpHCDHeader->pfnHCDEnumeratePorts       = OHCI_EnumeratePorts;
    fpHCDHeader->pfnHCDDisableInterrupts    = OHCI_DisableInterrupts;
    fpHCDHeader->pfnHCDEnableInterrupts     = OHCI_EnableInterrupts;
    fpHCDHeader->pfnHCDProcessInterrupt     = OHCI_ProcessInterrupt;
    fpHCDHeader->pfnHCDGetRootHubStatus     = OHCI_GetRootHubStatus;
    fpHCDHeader->pfnHCDDisableRootHub       = OHCI_DisableRootHub;
    fpHCDHeader->pfnHCDEnableRootHub        = OHCI_EnableRootHub;
    fpHCDHeader->pfnHCDControlTransfer      = OHCI_ControlTransfer;
    fpHCDHeader->pfnHCDBulkTransfer         = OHCI_BulkTransfer;
    fpHCDHeader->pfnHCDInterruptTransfer    = OHCI_InterruptTransfer;
    fpHCDHeader->pfnHCDDeactivatePolling    = OHCI_DeactivatePolling;
    fpHCDHeader->pfnHCDActivatePolling      = OHCI_ActivatePolling;
    fpHCDHeader->pfnHCDDisableKeyRepeat     = OHCI_DisableKeyRepeat;
    fpHCDHeader->pfnHCDEnableKeyRepeat      = OHCI_EnableKeyRepeat;
    fpHCDHeader->pfnHCDEnableEndpoints      = USB_EnableEndpointsDummy;
    fpHCDHeader->pfnHCDInitDeviceData       = USB_InitDeviceDataDummy;
    fpHCDHeader->pfnHCDDeinitDeviceData     = USB_DeinitDeviceDataDummy;
	fpHCDHeader->pfnHCDResetRootHub         = OHCI_ResetRootHub;
	fpHCDHeader->pfnHCDClearEndpointState	= 0;	//(EIP54283+)
	fpHCDHeader->pfnHCDGlobalSuspend        = OHCI_GlobalSuspend;	//(EIP54018+)

    USB_InstallCallBackFunction(OHCI_ControlTDCallback);
    USB_InstallCallBackFunction(OHCI_GeneralTDCallback);
    USB_InstallCallBackFunction(OHCI_PollingTDCallback);
    USB_InstallCallBackFunction(OHCI_RepeatTDCallBack);

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:     OHCI_Start
//
// DESCRIPTION: This API function is called to start a OHCI host controller.
//              The input to the routine is the pointer to the HC structure
//              that defines this host controller
//
// PARAMETERS:  fpHCStruc   Ptr to the host controller structure
//
// RETURN:      Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_Start (HC_STRUC*   fpHCStruc)
{
    UINT32          OhciControlReg = 0;
	UINT32			BaseAddr;
	UINT32			HcFmInterval;
    EFI_STATUS      EfiStatus = EFI_SUCCESS;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    fpHCStruc->wAsyncListSize = OHCI_FRAME_LIST_SIZE;
    fpHCStruc->dMaxBulkDataSize = MAX_OHCI_BULK_DATA_SIZE;

    //
    // Get memory base address of the HC and store it in the HCStruc
    //
    BaseAddr = ReadPCIConfig(fpHCStruc->wBusDevFuncNum, USB_MEM_BASE_ADDRESS);
    BaseAddr &= 0xFFFFFFF0;    // Mask lower bits

#if USB_RUNTIME_DRIVER_IN_SMM
    EfiStatus = AmiValidateMmioBuffer((VOID*)BaseAddr, fpHCStruc->BaseAddressSize);
    if (EFI_ERROR(EfiStatus)) {
        USB_DEBUG(3, "Usb Mmio address is invalid, it is in SMRAM\n");
        return USB_ERROR;
    }
    EfiStatus = AmiValidateMmioBuffer((VOID*)fpHCStruc->fpFrameList, 0x100);
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
#endif

    fpHCStruc->BaseAddress = BaseAddr;

    //
    // Get the number of ports supported by the host controller (Offset 48h)
    //
    fpHCStruc->bNumPorts = (UINT8)DwordReadMem(BaseAddr, OHCI_RH_DESCRIPTOR_A);

	USB_InitFrameList (fpHCStruc, 0);

    //
    // Enable the ED schedules
    //
    if (OHCI_StartEDSchedule(fpHCStruc) == USB_ERROR) return USB_ERROR;

    //
    // First stop the host controller if it is at all active
    //
    if (OHCI_DisableInterrupts(fpHCStruc) == USB_ERROR) return USB_ERROR;

	// Save the contents of the HcFmInterval register
	HcFmInterval = DwordReadMem(BaseAddr, OHCI_FRAME_INTERVAL);
	HcFmInterval &= 0x3FFF;
	if (HcFmInterval != 0x2EDF) {
		USB_DEBUG(3, "OHCI: HcFmInterval %x\n", HcFmInterval);
	}
	HcFmInterval |= (((6 * (HcFmInterval - 210)) / 7) & 0x7FFF) << 16;

	// Issue a controller reset
	if (OHCI_ResetHC(fpHCStruc) != USB_SUCCESS) {
		return USB_ERROR;
	}
	
	// Restore the value of the HcFmInterval register
	DwordWriteMem(BaseAddr, OHCI_FRAME_INTERVAL, HcFmInterval);

    //
    // Program the frame list base address register
    //
    DwordWriteMem(BaseAddr, OHCI_HCCA_REG, (UINT32)(UINTN)fpHCStruc->fpFrameList);

    //
    // Set the periodic start time = 2A27h (10% off from HcFmInterval-2EDFh)
    //
    DwordWriteMem(BaseAddr, OHCI_PERIODIC_START, (((HcFmInterval & 0x3FFF) * 9) / 10) & 0x3FFF);

	//
	// Start the host controller for periodic list and control list.
	//
    OhciControlReg = (PERIODIC_LIST_ENABLE | CONTROL_LIST_ENABLE |
        BULK_LIST_ENABLE | USBOPERATIONAL);
#if USB_RUNTIME_DRIVER_IN_SMM
    if (!(fpHCStruc->dHCFlag & HC_STATE_EXTERNAL)) {
        OhciControlReg |= INTERRUPT_ROUTING;
    }
#endif
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_CONTROL_REG,
        OhciControlReg);

    //
    // Enable interrupts from the host controller, enable SOF, WDH, RHSC interrupts
    //
    DwordWriteMem(BaseAddr, OHCI_INTERRUPT_ENABLE,
        MASTER_INTERRUPT_ENABLE | WRITEBACK_DONEHEAD_ENABLE |
        RH_STATUS_CHANGE_ENABLE | OWNERSHIP_CHANGE_ENABLE);

	//
    // Set the HC state to running
    //
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

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_Stop
//
// DESCRIPTION: This API function is called to stop the OHCI controller.
//              The input to the routine is the pointer to the HC structure
//              that defines this host controller.
//
// PARAMETERS:  fpHCStruc   Ptr to the host controller structure
//
// RETURN:      Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_Stop (HC_STRUC* fpHCStruc)
{
    UINT8 Port;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }


    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    for (Port = 1; Port <= fpHCStruc->bNumPorts; Port++) {
        USB_DisconnectDevice(fpHCStruc, (UINT8)(fpHCStruc->bHCNumber | BIT7), Port); 
    }

    //
    // Reset Host Controller
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_CONTROL_REG, USBRESET);
    FixedDelay(gUsbData->UsbTimingPolicy.OhciHcResetDelay * 1000);   // Wait 10ms for assertion of reset

    //
    // Disable interrupts
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_DISABLE, 0xffffffff);

    //
    // Disable OHCI KBC Emulation
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_HCE_CONTROL, 0);

    USB_InitFrameList (fpHCStruc, 0);
	OHCI_FreeAllStruc(fpHCStruc);		//(EIP28707+)

	USBKeyRepeat(fpHCStruc, 3);

    fpHCStruc->dHCFlag &= ~HC_STATE_RUNNING;

    CheckBiosOwnedHc();

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_RepeatTDCallBack
//
// DESCRIPTION: This function is called when TdRepeat/TD32ms completes
//              a transaction.  This TD runs a dummy interrupt transaction
//              to a non-existant device address for the purpose of
//              generating a periodic timeout interrupt which in turn
//              is used to generate keyboard repeat or update LED status.
//
// PARAMETERS:  fpHCStruc   Pointer to the HCStruc structure
//              fpDevInfo   NULL (pDevInfo is not valid)
//              fpTD        Pointer to the TD that completed
//              fpBuffer    Not used
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_RepeatTDCallBack(
    HC_STRUC	*HcStruc,
    DEV_INFO	*DevInfo,
    UINT8		*Td,
    UINT8		*Buffer,
    UINT16      DataLength
)
{
    OHCI_DESC_PTRS  *DescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;
    UINT8           *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)DescPtrs < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs + sizeof(OHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINT8*)DescPtrs->fpTDRepeat < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs->fpTDRepeat + sizeof(OHCI_TD)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    DescPtrs->fpTDRepeat->bActiveFlag = FALSE;

#if USB_DEV_KBD
    USBKBDPeriodicInterruptHandler(HcStruc);
#endif

    if (((UINT8*)DescPtrs->fpEDRepeat < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs->fpEDRepeat + sizeof(OHCI_ED)) > MemBlockEnd)) {
        return USB_ERROR;
    }

	if (!(DescPtrs->fpEDRepeat->dControl & ED_SKIP_TDQ)) {
	    //
	    // Rebind the TD to its parent ED
	    //
	    DescPtrs->fpEDRepeat->fpHeadPointer = (UINT32)(UINTN)DescPtrs->fpTDRepeat;

	    //
	    // Clear the link pointer. It may point to some other TD
	    //
	    DescPtrs->fpTDRepeat->fpLinkPointer = OHCI_TERMINATE;

	    //
	    // Reactivate the TD
	    //
	    DescPtrs->fpTDRepeat->dControlStatus = DescPtrs->fpTDRepeat->dCSReloadValue;
	    DescPtrs->fpTDRepeat->bActiveFlag = TRUE;
	}

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_DisableInterrupts
//
// DESCRIPTION: This API function is called to disable the interrupts
//              generated by the OHCI host controller. The input to the
//              routine is the pointer to the HC structure that defines this
//              host controller.  This routine will stop the HC to avoid
//              further interrupts.
//
// PARAMETERS:  fpHCStruc   Ptr to the host controller structure
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_DisableInterrupts (HC_STRUC* fpHCStruc)
{
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    //
    // Disable interrupt generation (global) bit (Set bit31)
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_DISABLE, MASTER_INTERRUPT_ENABLE);
    //
    // Disable periodic, isochronous, control and bulk list processing, reset bits 2 to 5
    //
    DwordResetMem((UINT32)fpHCStruc->BaseAddress, OHCI_CONTROL_REG, BIT2 + BIT3 + BIT4 + BIT5);

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_EnableInterrupts
//
// DESCRIPTION: This function enables the HC interrupts
//
// PARAMETERS:  fpHCStruc   Pointer to the HCStruc structure
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_EnableInterrupts (HC_STRUC* fpHCStruc)
{
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    //
    // Enable periodic, control and bulk list processing
    // Set bit 2, 4 & 5
    //
    DwordSetMem((UINT32)fpHCStruc->BaseAddress, OHCI_CONTROL_REG, BIT2 + BIT4 + BIT5);
    //
    // Enable interrupt generation (global) bit
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_ENABLE, MASTER_INTERRUPT_ENABLE);

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_ProcessInterrupt
//
// DESCRIPTION: This function is called when the USB interrupt bit is
//              set. This function will parse through the TDs and QHs to
//              find out completed TDs and call their respective call
//              back functions
//
// PARAMETERS:  fpHCStruc   Pointer to the HCStruc structure
//
// RETURN:      USB_ERROR - Interrupt not processed
//              USB_SUCCESS - Interrupt processed
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_ProcessInterrupt(HC_STRUC* fpHCStruc)
{
    OHCI_TD *fpTD, *fpTD1;
    UINT8 bIntProcessFlag = USB_ERROR;  // Set as interrupt not processed
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    // Make sure MEMIO & Bus mastering are enabled
    if (((UINT8)ReadPCIConfig(fpHCStruc->wBusDevFuncNum, USB_REG_COMMAND) & 0x6) != 0x6) {
        return bIntProcessFlag;
    }

    if ((ReadPCIConfig(fpHCStruc->wBusDevFuncNum, USB_MEM_BASE_ADDRESS) & ~(0x7F)) != 
        (UINT32)fpHCStruc->BaseAddress) {
        return bIntProcessFlag;
    }
    //
    // Check the interrupt status register for an ownership change.  If this bit
    // is set, it means that the O/S USB device driver is attempting to takeover
    // control of the host controller. In this case the host controller is
    // shut down and the interrupt routing bit in the control register is cleared
    // (this disables SMI generation and enebles standard IRQ generation from
    // the USB host controller.
    //
    if (DwordReadMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_STATUS) & OWNERSHIP_CHANGE) {
        DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_STATUS, OWNERSHIP_CHANGE);
        if (DwordReadMem((UINT32)fpHCStruc->BaseAddress, OHCI_HCCA_REG) == (UINT32)(UINTN)fpHCStruc->fpFrameList) {
            //
            // OS tries to take the control over HC
            //
            gUsbData->dUSBStateFlag  &= (~USB_FLAG_ENABLE_BEEP_MESSAGE);

			OHCI_StopUnsupportedHC(fpHCStruc);

            OHCI_Stop(fpHCStruc);
            return USB_SUCCESS; // Set interrupt as processed
        } else {    // Ownership comes back to the driver - reinit
            gUsbData->bHandOverInProgress = FALSE;
            gUsbData->dUSBStateFlag  |= (USB_FLAG_ENABLE_BEEP_MESSAGE);
            OHCI_Start(fpHCStruc);
            return USB_SUCCESS; // Set interrupt as processed
        }
    }   // ownership change

	if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) return USB_ERROR;

	if (OhciIsHalted(fpHCStruc)) {
        // Clear All bits of the interrupt status
        DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_STATUS, 
            DwordReadMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_STATUS));
		return bIntProcessFlag;
	}
    //
    // Check whether the controller is still under BIOS control
    // Read the base address of the Periodic Frame List to the OHCI HCCA
    // register and compare with stored value
    //
    if ((DwordReadMem((UINT32)fpHCStruc->BaseAddress, OHCI_HCCA_REG) & 0xFFFFFF00) !=
            (UINT32)(UINTN)fpHCStruc->fpFrameList) {
        return bIntProcessFlag;
    }
    //
    // Check the interrupt status register for a root hub status change.  If
    // this bit is set, then a device has been attached or removed from one of
    // the ports on the root hub.
    //
    if (DwordReadMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_STATUS) & RH_STATUS_CHANGE) {
        //
        // Stop the periodic list processing to avoid more interrupts from HC
        //
        DwordResetMem((UINT32)fpHCStruc->BaseAddress, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);
//        USB_DEBUG(3, "before OHCI_ProcessRootHubStatusChange\n");
        // Handle root hub change
        bIntProcessFlag = (UINT8)OHCI_ProcessRootHubStatusChange(fpHCStruc);
//        USB_DEBUG(3, "after OHCI_ProcessRootHubStatusChange\n");
        //
        // Re-enable the periodic list processing
        //
        DwordSetMem((UINT32)fpHCStruc->BaseAddress, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);
    }

    //
    // Check the interrupt status register for a one or more TDs completing.
    //
    if (!(DwordReadMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_STATUS) & WRITEBACK_DONEHEAD)) {
        return USB_SUCCESS;
    }
    bIntProcessFlag = USB_SUCCESS;  // Set interrupt as processed

    //
    // The memory dword at HCCADONEHEAD has been updated to contain the head
    // pointer of the linked list of TDs that have completed.  Walk through
    // this list processing TDs as we go.
    //
    for (;;) {
        fpTD = (OHCI_TD*)(UINTN)(((OHCI_HCCA_PTRS*)fpHCStruc->fpFrameList)->dHccaDoneHead);
#if USB_RUNTIME_DRIVER_IN_SMM
        EfiStatus = AmiValidateMemoryBuffer((VOID*)fpTD, sizeof(OHCI_TD));
        if (EFI_ERROR(EfiStatus)) {
            return USB_ERROR;
        }
#endif
        ((OHCI_HCCA_PTRS*)fpHCStruc->fpFrameList)->dHccaDoneHead = 0;

        //
        // Clear the WRITEBACK_DONEHEAD bit of the interrupt status register
        // in the host controller
        //
        DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_STATUS, WRITEBACK_DONEHEAD);

        if (!fpTD) break;   // no TDs in the list

        do {
            fpTD = (OHCI_TD*)((UINTN)fpTD & 0xfffffff0);
#if USB_RUNTIME_DRIVER_IN_SMM
            EfiStatus = AmiValidateMemoryBuffer((VOID*)fpTD, sizeof(OHCI_TD));
            if (EFI_ERROR(EfiStatus)) {
                return USB_ERROR;
            }
#endif
            fpTD1 = (OHCI_TD*)fpTD->fpLinkPointer;
            OHCI_ProcessTD(fpHCStruc, fpTD);
            // Host controllers might change NextTD pointer to Td, then it causes
            // infinite loop in this routing. Break this loop if NextTd is the same as Td.
            if (fpTD == fpTD1) {
                break;
            }
            fpTD = fpTD1;
        } while (fpTD);
    }   // Check if any TDs completed while processing

    return  bIntProcessFlag;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_GetRootHubStatus
//
// DESCRIPTION: This function returns the port connect status for the
//              root hub port
//
// PARAMETERS:  pHCStruc    Pointer to HCStruc of the host controller
//              bPortNum    Port in the HC whose status is requested
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_GetRootHubStatus(
    HC_STRUC*   fpHCStruc,
    UINT8       bPortNum,
    BOOLEAN     ClearChangeBits
)
{
    UINT8 bRHStatus = USB_PORT_STAT_DEV_OWNER;
    UINT32 dPortStatus;
    UINT16 wPortReg = ((UINT16)bPortNum << 2) + (OHCI_RH_PORT1_STATUS - 4); 
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    dPortStatus = DwordReadMem((UINT32)fpHCStruc->BaseAddress, wPortReg);
	USB_DEBUG(3, "Ohci port[%d] status: %08x\n", bPortNum, dPortStatus);

    if (dPortStatus & CURRENT_CONNECT_STATUS) {
        bRHStatus |= USB_PORT_STAT_DEV_CONNECTED;
		if (dPortStatus & PORT_ENABLE_STATUS) {
			bRHStatus |= USB_PORT_STAT_DEV_ENABLED;
		}
    }

    bRHStatus |= USB_PORT_STAT_DEV_FULLSPEED;   // Assume full speed and set the flag
    if (dPortStatus & LOW_SPEED_DEVICE_ATTACHED) {
        bRHStatus &= ~USB_PORT_STAT_DEV_FULLSPEED;  // Reset full speed
        bRHStatus |= USB_PORT_STAT_DEV_LOWSPEED;    // Set low speed flag
    }

    if (dPortStatus & CONNECT_STATUS_CHANGE) {
        if (ClearChangeBits == TRUE)
		DwordWriteMem((UINT32)fpHCStruc->BaseAddress, wPortReg, CONNECT_STATUS_CHANGE);	//(EIP66448+)
        bRHStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED; // Set connect status change flag
    }
										//(EIP66448+)>
	if (dPortStatus & PORT_ENABLE_STATUS_CHANGE) {
        if (ClearChangeBits == TRUE) {
		    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, wPortReg, PORT_ENABLE_STATUS_CHANGE);
        }
	}
										//<(EIP66448+)
    return  bRHStatus;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_DisableRootHub
//
// DESCRIPTION: This function disables the specified root hub port.
//
// PARAMETERS:  fpHCStruc   Pointer to HCStruc of the host controller
//              bPortNum    Port in the HC to be disabled.
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_DisableRootHub (HC_STRUC* fpHCStruc, UINT8 bPortNum)
{
    UINT32 dPortReg = ((UINT32)bPortNum << 2) + (OHCI_RH_PORT1_STATUS - 4);
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, (UINT16)dPortReg, CLEAR_PORT_ENABLE);
    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_EnableRootHub
//
// DESCRIPTION: This function enables the specified root hub port.
//
// PARAMETERS:  fpHCStruc   Pointer to HCStruc of the host controller
//              bPortNum    Port in the HC to be enabled.
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_EnableRootHub (HC_STRUC* fpHCStruc,UINT8 bPortNum)
{
    return  USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_ResetRootHub
//
// DESCRIPTION: This function resets the specified root hub port.
//
// PARAMETERS:  HcStruc   Pointer to HCStruc of the host controller
//              PortNum    Port in the HC to be disabled.
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_ResetRootHub (HC_STRUC* HcStruc, UINT8 PortNum)
{
	UINT32	BaseAddr = (UINT32)HcStruc->BaseAddress;
	UINT16	PortReg = ((UINT16)PortNum << 2) + (OHCI_RH_PORT1_STATUS - 4);
	UINT32	i;
    EFI_STATUS EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
	
    DwordWriteMem(BaseAddr, PortReg, SET_PORT_RESET);    // Reset the port

    // The reset signaling must be driven for a minimum of 10ms
    FixedDelay(10 * 1000);

    //
    // Wait for reset to complete
    //
    for (i = 0; i < 500; i++) {
		if (DwordReadMem(BaseAddr, PortReg) & PORT_RESET_STATUS_CHANGE) {
			break;
		}
        FixedDelay(100);       // 100 us delay
    }

	if (!(DwordReadMem(BaseAddr, PortReg) & PORT_RESET_STATUS_CHANGE)) {
		USB_DEBUG(3, "OHCI: port reset timeout, status: %08x\n", 
			DwordReadMem(BaseAddr, PortReg));
		return USB_ERROR;
	}

    //
    // Clear the reset status change status
    //
    DwordWriteMem(BaseAddr, PortReg, PORT_RESET_STATUS_CHANGE);

    // Some devices need a delay here
	FixedDelay(3 * 1000);  // 3 ms delay

    return  USB_SUCCESS;
}

										//(EIP54018+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        OHCI_GlobalSuspend
//
// Description: 
//  This function suspend the OHCI HC.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_GlobalSuspend(
    HC_STRUC*	HcStruc
)
{
    EFI_STATUS EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (OhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}

    DwordWriteMem((UINT32)HcStruc->BaseAddress, OHCI_INTERRUPT_ENABLE,
                    RESUME_DETECTED_ENABLE);
    FixedDelay(40 * 1000);
    DwordWriteMem((UINT32)HcStruc->BaseAddress, OHCI_CONTROL_REG,
                    USBSUSPEND | REMOTE_WAKEUP_ENABLE);
    FixedDelay(20 * 1000);

    HcStruc->dHCFlag &= ~(HC_STATE_RUNNING);
    HcStruc->dHCFlag |= HC_STATE_SUSPEND;

    return  USB_SUCCESS;
}
										//<(EIP54018+)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_ControlTransfer
//
// DESCRIPTION: This function executes a device request command transaction
//              on the USB. One setup packet is generated containing the
//              device request parameters supplied by the caller.  The setup
//              packet may be followed by data in or data out packets
//              containing data sent from the host to the device
//              or vice-versa. This function will not return until the
//              request either completes successfully or completes in error
//              (due to time out, etc.)
//
// PARAMETERS:  fpHCStruc   Pointer to HCStruc of the host controller
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
// RETURN:  Number of bytes transferred
//
//
// NOTES:   Do not use USB_SUCCESS or USB_ERROR as returned values
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
OHCI_ControlTransfer (
    HC_STRUC*   fpHCStruc,
    DEV_INFO*   fpDevInfo,
    UINT16      wRequest,
    UINT16      wIndex,
    UINT16      wValue,
    UINT8       *fpBuffer,
    UINT16      wLength)
{
    UINT16  *fpData;
    OHCI_DESC_PTRS *fpDescPtrs = fpHCStruc->stDescPtrs.fpOHCIDescPtrs;
    OHCI_ED *fpED;
    OHCI_TD *fpTD;
    UINT32 dData;
    UINT16 wData;
	UINT8 CompletionCode;
    UINT32 TransferLength;
    UINT8   *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);
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
                USB_DEBUG(3, "Ohci ControlTransfer Invalid Pointer, Buffer is in SMRAM.\n");
                return 0;
            }
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }

	if (OhciIsHalted(fpHCStruc)) {
		return 0;
	}
    //FixedDelay(5 * 1000);    // 5 ms delay is necessary for OHCI host controllers

    if( !VALID_DEVINFO( fpDevInfo) )
        return 0;
    if (((UINT8*)fpDescPtrs < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(fpDescPtrs + sizeof(OHCI_DESC_PTRS)) > MemBlockEnd)) {
        return 0;
    }
    if (((UINT8*)fpDescPtrs->fpEDControl < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(fpDescPtrs->fpEDControl + sizeof(OHCI_ED)) > MemBlockEnd)) {
        return 0;
    }
    if (((UINT8*)fpDescPtrs->fpTDControlSetup < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(fpDescPtrs->fpTDControlSetup + sizeof(OHCI_TD)) > MemBlockEnd)) {
        return 0;
    }
    if (((UINT8*)fpDescPtrs->fpTDControlData < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(fpDescPtrs->fpTDControlData + sizeof(OHCI_TD)) > MemBlockEnd)) {
        return 0;
    }
    if (((UINT8*)fpDescPtrs->fpTDControlStatus < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(fpDescPtrs->fpTDControlStatus + sizeof(OHCI_TD)) > MemBlockEnd)) {
        return 0;
    }
	gUsbData->dLastCommandStatusExtended = 0;

    //
    // Build the device request in the data area of the control setup qTD
    //
    fpData = (UINT16*)fpDescPtrs->fpTDControlSetup->aSetupData;
    *fpData++ = wRequest;
    *fpData++ = wValue;
    *fpData++ = wIndex;
    *fpData++ = wLength;
    *(UINTN*)fpData = (UINTN)fpBuffer;
    //
    // Prepare some registers that will be used in building the TDs below.
    // wLength  contains the data length.
    // fpBuffer contains the absolute address of the data buffer.
    // wRequest contains the request type (bit 7 = 0/1 for Out/In).
    // fpDevInfo will contain a pointer to the DeviceInfo structure for the given device.
    //
    // Ready the EDControl for the control transfer.
    //
    fpED = fpDescPtrs->fpEDControl;
    //
    // The ED control field will be set so
    //   Function address & Endpoint number = ESI,
    //   Direction = From TD,
    //   Speed = DeviceInfo.bEndpointSpeed,
    //   Skip = 1, Format = 0,
    //   Max packet size  = DeviceInfo.wEndp0MaxPacket
    // The HeadPointer field will be set to TDControlSetup
    // The TailPointer field will be set to OHCI_TERMINATE
    // The LinkPointer field will be set to OHCI_TERMINATE
    //
    dData = (UINT32)fpDevInfo->wEndp0MaxPacket;
    if (dData > 0x40) dData = 0x40; // Force the max packet size to 64 bytes
    dData <<= 16;                   // dData[26:16] = device's packet size
    wData = (UINT16)fpDevInfo->bEndpointSpeed;  // 00/01/10 for HI/LO/FULL
    wData = (wData & 1) << 13;      // wData[13] = full/low speed flag
    wData |= fpDevInfo->bDeviceAddress | ED_SKIP_TDQ;
    fpED->dControl = dData | wData;
    fpED->fpTailPointer = 0;
    fpED->fpEDLinkPointer = 0;

    fpTD = fpDescPtrs->fpTDControlSetup;
    //
    // The ControlStatus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_SETUP_PACKET,
    //   Delay Interrupt = GTD_IntD,
    //   Data Toggle = GTD_SETUP_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to the TD's SetupData buffer
    //   which was before initialized to contain a DeviceRequest struc.
    // The BufferEnd field will point to the last byte of the TD's SetupData
    //   buffer.
    // The LinkPointer field will point to the TDControlData if data will
    //   be sent/received or to the TDControlStatus if no data is expected.
    // The CSReloadValue field will contain 0 because this is a "one shot" packet.
    // The pCallback will be set to point to the OHCI_ControlTDCallback routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control TDs do
    //   not need rebinding to the EDControl.
    //
    fpTD->dControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_SETUP_PACKET | GTD_SETUP_TOGGLE |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));

    fpTD->fpCurrentBufferPointer = (UINT32)(UINTN)fpTD->aSetupData;
    fpTD->fpBufferEnd = (UINT32)(UINTN)fpTD->aSetupData + 7; // size of aSetupData - 1

    wData = wLength ;                   //(EIP67230)

    if (wLength) {  // some data to transfer
        fpTD = fpDescPtrs->fpTDControlData;     // Fill in various fields in the TDControlData.
        //
        // The ControlStatus field will be set so
        //   Buffer Rounding = 1,
        //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
        //   Delay Interrupt = GTD_IntD,
        //   Data Toggle = GTD_DATA1_TOGGLE,
        //   Error Count = GTD_NO_ERRORS,
        //   Condition Code = GTD_NOT_ACCESSED
        // The CurrentBufferPointer field will point to the caller's buffer
        //   which is now in EBP.
        // The BufferEnd field will point to the last byte of the caller's buffer.
        // The LinkPointer field will point to the TDControlStatus.
        // The CSReloadValue field will contain 0 because this is a "one shot" packet.
        // The pCallback will be set to point to the OHCI_ControlTDCallback routine.
        // The ActiveFlag field will be set to TRUE.
        // The DeviceAddress field does not need to be set since the Control TDs do
        //   not need rebinding to the EDControl.
        // The CSReloadValue field will contain 0 because this is a "one shot" packet.
        // The pCallback will be set to point to the OHCI_ControlTDCallback routine.
        // The ActiveFlag field will be set to TRUE.    return  USB_SUCCESS;
        // The DeviceAddress field does not need to be set since the Control TDs do}
        //   not need rebinding to the EDControl.
        //
        dData = (UINT32)(GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
        dData = (wRequest & BIT7)? (dData | GTD_IN_PACKET | GTD_IntD) : (dData | GTD_OUT_PACKET);
        fpTD->dControlStatus = dData;
        fpTD->fpCurrentBufferPointer = (UINT32)(UINTN)fpBuffer;
        fpTD->fpBufferEnd = (UINT32)((UINTN)fpBuffer + wData - 1);
    }
    fpTD = fpDescPtrs->fpTDControlStatus;   // Fill in various fields in the TDControlStatus.
    //
    // The ControlStaus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
    //   Delay Interrupt = GTD_IntD,
    //   Data Toggle = GTD_DATA1_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to NULL
    // The BufferEnd field will point to NULL.
    // The LinkPointer field will point to OHCI_TERMINATE.
    // The CSReloadValue field will contain 0 because this is a "one shot" packet.
    // The pCallback will be set to point to the OHCI_ControlTdCallback routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control TDs do
    //   not need rebinding to the EdControl.
    //
    // Note: For OUT control transfer status should be IN and
    //       for IN cotrol transfer, status should be OUT.
    //
    dData = (UINT32)(GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
    dData = (wRequest & BIT7)? (dData | GTD_OUT_PACKET) : (dData | GTD_IN_PACKET | GTD_IntD);
    fpTD->dControlStatus = dData;
    fpTD->fpCurrentBufferPointer = 0;
    fpTD->fpBufferEnd = 0;
    fpTD->fpLinkPointer = 0;
    //
    // Link all the pointers together
    //
    fpTD = fpDescPtrs->fpTDControlSetup;
    fpED->fpHeadPointer = (UINT32)(UINTN)fpTD;
    if (wLength) {  // chain in data TD
        fpTD->fpLinkPointer = (UINT32)(UINTN)fpDescPtrs->fpTDControlData;
        fpTD = fpDescPtrs->fpTDControlData;
    }
    fpTD->fpLinkPointer = (UINT32)(UINTN)fpDescPtrs->fpTDControlStatus;

    fpDescPtrs->fpTDControlStatus->fpLinkPointer = 0;

    fpTD = fpDescPtrs->fpTDControlSetup;
    do {
        fpTD->dCSReloadValue = 0;
        fpTD->bCallBackIndex = USB_InstallCallBackFunction(OHCI_ControlTDCallback);
        fpTD->bActiveFlag = TRUE;
        fpTD = (OHCI_TD*)fpTD->fpLinkPointer;
    } while (fpTD);
    //
    // Now control queue is complete, so set ED_SKIP_TDQ=0
    //
    fpED->dControl &= ~ED_SKIP_TDQ;
    //
    // Set the HcControlHeadED register to point to the EDControl.
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_CONTROL_HEAD_ED, (UINT32)(UINTN)fpED);
    //
    // Now put the control setup, data and status into the HC's schedule by
    // setting the ControllListFilled field of HcCommandStatus reg.
    // This will cause the HC to execute the transaction in the next active frame.
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_COMMAND_STATUS, CONTROL_LIST_FILLED);
    //
    // Now wait for the control status TD to complete.  When it has completed,
    // the OHCI_ControlTDCallback will set its active flag to FALSE.
    //
    OHCIWaitForTransferComplete(fpHCStruc, fpED, fpDescPtrs->fpTDControlStatus,fpDevInfo);
    //
    // Stop the HC from processing the EDControl by setting its Skip bit.
    //
    fpED->dControl |= ED_SKIP_TDQ;

    //
    // Finally check for any error bits set in both the TDControlStatus.
    // If the TD did not complete successfully, return STC.
    //
    CompletionCode = (UINT8)(fpDescPtrs->fpTDControlStatus->dControlStatus >> 28);    // dData[3:0] = Completion status
    gUsbData->bLastCommandStatus &= ~USB_CONTROL_STALLED;

    fpTD = fpDescPtrs->fpTDControlData;
    TransferLength = wLength ; 
    if(fpTD->fpCurrentBufferPointer != 0){
        TransferLength = fpTD->fpCurrentBufferPointer - (UINT32)(UINTN)fpBuffer;
    }


	wData = 0;
	switch (CompletionCode) {
        case GTD_NO_ERROR:
            wData = TransferLength;
			break;
		case GTD_STALL:
			gUsbData->bLastCommandStatus |= USB_CONTROL_STALLED;
			gUsbData->dLastCommandStatusExtended |= USB_TRSFR_STALLED;
			break;
		case GTD_NOT_ACCESSED:
			gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
			break;
		default:
			break;
	}

    return wData;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_BulkTransfer
//
// DESCRIPTION: This function executes a bulk transaction on the USB. The
//              transfer may be either DATA_IN or DATA_OUT packets containing
//              data sent from the host to the device or vice-versa. This
//              function wil not return until the request either completes
//              successfully or completes with error (due to time out, etc.)
//              Size of data can be upto 64K
//
// PARAMETERS:  pHCStruc    Pointer to HCStruc of the host controller
//              pDevInfo    DeviceInfo structure (if available else 0)
//              bXferDir    Transfer direction
//                  Bit 7: Data direction
//                          0 Host sending data to device
//                          1 Device sending data to host
//                  Bit 6-0 : Reserved
//              fpBuffer    Buffer containing data to be sent to the
//                          device or buffer to be used to receive data
//                          value in Segment:Offset format
//              dwLength    dwLength request parameter, number of bytes
//                          of data to be transferred in or out
//                          of the host controller
//
// RETURN:      Amount of data transferred
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
OHCI_BulkTransfer (
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    UINT8       bXferDir,
    UINT8       *fpBuffer,
    UINT32      dwLength)
{
    UINT32      dData;
    UINT8   bData;
    OHCI_DESC_PTRS *fpDescPtrs;
    UINT16      wMaxPkt;
    UINT8       bEndp;
    UINT8       bDatToggle;
    UINT32      dBytesToTransfer, dBytesRemaining;
    UINT32      dBytesTransferred;
    UINT32      Buffer;
    UINT8       *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);
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
        EfiStatus = AmiValidateMemoryBuffer((VOID*)fpBuffer, dwLength);
        if (EFI_ERROR(EfiStatus)) {
            USB_DEBUG(3, "Ohci BulkTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }

	if (OhciIsHalted(fpHCStruc)) {
		return 0;
	}
    
    if( !VALID_DEVINFO( fpDevInfo) )
        return 0;

	gUsbData->dLastCommandStatusExtended = 0;

    fpDescPtrs = fpHCStruc->stDescPtrs.fpOHCIDescPtrs;

    if (((UINT8*)fpDescPtrs < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(fpDescPtrs + sizeof(OHCI_DESC_PTRS)) > MemBlockEnd)) {
        return 0;
    }

    if (((UINT8*)fpDescPtrs->fpEDBulk < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(fpDescPtrs->fpEDBulk + sizeof(OHCI_ED)) > MemBlockEnd)) {
        return 0;
    } 

    if (((UINT8*)fpDescPtrs->fpTDBulkData < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(fpDescPtrs->fpTDBulkData + sizeof(OHCI_TD)) > MemBlockEnd)) {
        return 0;
    } 
    
    wMaxPkt = (bXferDir & 0x80)? fpDevInfo->wBulkInMaxPkt : fpDevInfo->wBulkOutMaxPkt;
    bEndp = (bXferDir & 0x80)? fpDevInfo->bBulkInEndpoint : fpDevInfo->bBulkOutEndpoint;
	bDatToggle = UsbGetDataToggle(fpDevInfo, bEndp | bXferDir);

    if( wMaxPkt == 0){
        return 0;
    }

    dBytesRemaining = dwLength;
    dBytesTransferred = 0;
    dBytesToTransfer = 0;

    for (;dBytesRemaining != 0; dBytesRemaining -= dBytesToTransfer) {
        dBytesToTransfer = 
             (dBytesRemaining < FULLSPEED_MAX_BULK_DATA_SIZE_PER_FRAME)?
                    dBytesRemaining : FULLSPEED_MAX_BULK_DATA_SIZE_PER_FRAME;

        Buffer = (UINT32)(UINTN)fpBuffer + dBytesTransferred;

        //
        //  Set the SKIP bit in the EdBulk to avoid accidental scheduling
        //
        fpDescPtrs->fpEDBulk->dControl = ED_SKIP_TDQ;
        //
        // Set the ED's head pointer field to bulk data TD and tail pointer field to
        // OHCI_TERMINATE. Also set ED's link pointer to OHCI_TERMINATE.
        //
        fpDescPtrs->fpEDBulk->fpHeadPointer = (UINT32)(UINTN)fpDescPtrs->fpTDBulkData;
        fpDescPtrs->fpEDBulk->fpTailPointer = OHCI_TERMINATE;
        fpDescPtrs->fpEDBulk->fpEDLinkPointer = OHCI_TERMINATE;
        //
        // Form the data needed for ED's control field with the available information
        //
        dData = (bXferDir & 0x80)? ED_IN_PACKET : ED_OUT_PACKET;
        dData |= fpDevInfo->bDeviceAddress;
        dData |= (UINT16)bEndp << 7;
        dData |= (UINT32)wMaxPkt << 16;
        //
        // Update the ED's control field with the data formed
        // ASSUME ALL MASS DEVICES ARE FULL SPEED DEVICES.
        //
        fpDescPtrs->fpEDBulk->dControl = dData;
        //
        // Fill the general bulk data TD with relevant information.  Set the
        //  TD's control field with buffer rounding set to 1, direction PID to
        //  don't care, delay interrupt to INTD, data toggle to the latest data
        //  toggle value, error count to no errors and condition code to not accessed.
        //
        // Set the data toggle to DATA0 (SETUP_TOGGLE)
        fpDescPtrs->fpTDBulkData->dControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET |
            GTD_IntD | GTD_SETUP_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
        fpDescPtrs->fpTDBulkData->dControlStatus |= (UINT32)bDatToggle << 24;
        //
        // GTD current buffer pointer field will point to the caller's buffer which
        // now in the variable fpBuffer
        //
        fpDescPtrs->fpTDBulkData->fpCurrentBufferPointer = Buffer;
        fpDescPtrs->fpTDBulkData->fpBufferEnd = Buffer + dBytesToTransfer - 1;
        fpDescPtrs->fpTDBulkData->fpLinkPointer = OHCI_TERMINATE;
        //
        // GTD's CSReloadValue field will contain 0 because this is a "one shot" packet
        //
        fpDescPtrs->fpTDBulkData->dCSReloadValue = 0;
        fpDescPtrs->fpTDBulkData->bCallBackIndex = USB_InstallCallBackFunction(OHCI_GeneralTDCallback);
        fpDescPtrs->fpTDBulkData->bActiveFlag = TRUE;
    
        fpDescPtrs->fpEDBulk->dControl &= ~ED_SKIP_TDQ;
        //
        // Set the HCBulkHeadED register to point to the bulk ED
        //
        DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_BULK_HEAD_ED, (UINT32)(UINTN)fpDescPtrs->fpEDBulk);
        //
        // Clear bulk stall/time out condition flag
        //
        gUsbData->bLastCommandStatus &= ~(USB_BULK_STALLED + USB_BULK_TIMEDOUT);
        //
        // Enable the bulk list processing
        //
        DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_COMMAND_STATUS, BULK_LIST_FILLED);
    
        OHCIWaitForTransferComplete(fpHCStruc, fpDescPtrs->fpEDBulk, fpDescPtrs->fpTDBulkData,fpDevInfo);
        //
        // Stop the HC from processing the EDBulk by setting its Skip bit.
        //
        fpDescPtrs->fpEDBulk->dControl |= ED_SKIP_TDQ;
        //
        // Update the data toggle value into the mass info structure
        //
		UsbUpdateDataToggle(fpDevInfo, bEndp | bXferDir, 
			(UINT8)(((fpDescPtrs->fpTDBulkData->dControlStatus & GTD_DATA_TOGGLE) >> 24) & 1));
        //
        // Check for the error conditions - if possible recover from them
        //
        bData = (UINT8)(fpDescPtrs->fpTDBulkData->dControlStatus >> 28);
		switch (bData) {
			case GTD_STALL:
				gUsbData->bLastCommandStatus |= USB_BULK_STALLED;
				gUsbData->dLastCommandStatusExtended |= USB_TRSFR_STALLED;
				break;
			case GTD_NOT_ACCESSED:
				gUsbData->bLastCommandStatus |= USB_BULK_TIMEDOUT;
				gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
				break;
			default:
				break;
		}

		if (bData != GTD_NO_ERROR) {
			break;
		}

        //
        // Get the size of data transferred
        //
        dData = fpDescPtrs->fpTDBulkData->fpCurrentBufferPointer;
        if (dData != 0)
        {
            //
            // Device sent less data than requested, calculate the
            // transferred size and exit
            //
            //dBytesTransferred += (UINT32)(UINTN)fpDescPtrs->fpTDBulkData->fpBufferEnd - dData; //(EIP55025-)
     	    dBytesTransferred += dData - Buffer;   //Short Packet (OHCI Spec 4.3.1.3.5  Transfer Completion, Pg.23) //<(EIP55025)+    
            break;
        }

        //
        // CurrentBufferPointer equals 0. This indicates the successfull TD completion,
        // all data is transferred. Adjust the total amount and continue.
        //
        dBytesTransferred += dBytesToTransfer;
    }

    return  dBytesTransferred;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_InterruptTransfer
//
// DESCRIPTION: This function executes an interrupt transaction on the USB.
//              The data transfer direction is always DATA_IN. This
//              function wil not return until the request either completes
//              successfully or completes in error (due to time out, etc.)
//
// PARAMETERS:  fpHCStruc   Pointer to HCStruc of the host controller
//              fpDevInfo   DeviceInfo structure (if available else 0)
//              EndpointAddress The destination USB device endpoint to which the device request 
//                          is being sent.
//              MaxPktSize  Indicates the maximum packet size the target endpoint is capable 
//                          of sending or receiving.
//              fpBuffer    Buffer containing data to be sent to the
//                          device or buffer to be used to receive data
//              wLength     wLength request parameter, number of bytes
//                          of data to be transferred in
//
// RETURN:      Number of bytes transferred
//
//
// NOTES:       DO NOT TOUCH THE LINK POINTER OF THE TDInterruptData. It is
//              statically allocated and linked with other items in the
//              1ms schedule
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
OHCI_InterruptTransfer (
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    UINT8       EndpointAddress,
    UINT16      MaxPktSize,
    UINT8       *fpBuffer,
    UINT16      wLength)
{
    UINT8 bEndp, bDatToggle;
    UINT32 dData;
    OHCI_ED	*IntEd;
	OHCI_TD	*IntTd;
	UINT8	CompletionCode;
	UINT32	BytesTransferred;
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
            USB_DEBUG(3, "Ohci InterruptTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }
	
	if (OhciIsHalted(fpHCStruc)) {
		return 0;
	}

    if(!VALID_DEVINFO( fpDevInfo)) {
        return 0;
    }

	gUsbData->dLastCommandStatusExtended = 0;

	IntEd = USB_MemAlloc(GET_MEM_BLK_COUNT(sizeof(OHCI_ED) + sizeof(OHCI_TD)));

	if (IntEd == NULL) {
		return 0;
	}

	IntTd = (OHCI_TD*)((UINTN)IntEd + sizeof(OHCI_ED));

    //
    // Set the SKIP bit to avoid accidental scheduling
    //
    IntEd->dControl = ED_SKIP_TDQ;
    //
    // Set the ED's head pointer field to interrupt data TD and tail pointer
    // field to OHCI_TERMINATE. Also set ED's link pointer to OHCI_TERMINATE.
    //
    IntEd->fpHeadPointer = (UINT32)(UINTN)IntTd;
    IntEd->fpTailPointer = OHCI_TERMINATE;
    IntEd->fpEDLinkPointer = OHCI_TERMINATE;
    IntEd->Interval = OhciTranslateInterval(fpDevInfo->bPollInterval);

    //
    // Get maximum packet size from device info structure
    //
    bEndp = EndpointAddress & 0xF;
	bDatToggle = UsbGetDataToggle(fpDevInfo, EndpointAddress);
	
    //
    // Form the data needed for ED's control field with the available information
    //
    dData = (EndpointAddress & BIT7)? ED_IN_PACKET : ED_OUT_PACKET;
    dData |= fpDevInfo->bDeviceAddress | ((UINT16)bEndp << 7);
    dData |= ((UINT32)MaxPktSize << 16);
	dData |= (UINT32)(fpDevInfo->bEndpointSpeed & 1) << 13;
    //
    // Update the ED's control field with the data formed
    // ASSUME ALL MASS DEVICES ARE FULL SPEED DEVICES.
    //
    IntEd->dControl = dData;
    //
    // Fill the general interrupt data TD with relevant information.  Set the
    //  TD's control field with buffer rounding set to 1, direction PID to
    //  don't care, delay interrupt to INTD, data toggle to the latest data
    //  toggle value, error count to no errors and condition code to not accessed.
    //
    // Set the data toggle to DATA0 (SETUP_TOGGLE)
    //
    dData = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET  | GTD_IntD | GTD_SETUP_TOGGLE |
        GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
    IntTd->dControlStatus = dData;
    //
    // Set the data toggle depending on the bDatToggle value
    //
    IntTd->dControlStatus |= ((UINT32)bDatToggle << 24);
    //
    // GTD current buffer pointer field will point to the caller's buffer
    //
    IntTd->fpCurrentBufferPointer = (UINT32)(UINTN)fpBuffer;
    //
    // GTD's buffer end field will point to the last byte of the caller's buffer
    //
    IntTd->fpBufferEnd = (UINT32)(UINTN)(fpBuffer + wLength - 1);
    //
    // GTD's link pointer field will be set to OHCI_TERMINATE
    //
    IntTd->fpLinkPointer = OHCI_TERMINATE;
    //
    // GTD's CSReloadValue field will contain 0 because this is a "one shot" packet
    //
    IntTd->dCSReloadValue = 0;
    //
    // GTD's pCallback will point to the OHCI_GeneralTDCallback routine
    //
    IntTd->bCallBackIndex = USB_InstallCallBackFunction(OHCI_GeneralTDCallback);
    //
    // GTD's ActiveFlag field will be set to TRUE.
    //
	OhciAddPeriodicEd(fpHCStruc, IntEd);

	IntTd->bActiveFlag = TRUE;
    IntEd->dControl &= ~ED_SKIP_TDQ;

    //
    // Now wait for the interrupt data TD to complete.
    //
    OHCIWaitForTransferComplete(fpHCStruc, IntEd, IntTd, fpDevInfo);
    //
    // Stop the HC from processing the EDInterrupt by setting its Skip bit.
    //
    OhciRemovePeriodicEd(fpHCStruc, IntEd);
    //
    // Get appropriate data sync shift value
    //
    bDatToggle = (UINT8)((IntTd->dControlStatus & GTD_DATA_TOGGLE) >> 24) & 1;
	UsbUpdateDataToggle(fpDevInfo, EndpointAddress, bDatToggle);
	
    //
    // Check for the error conditions - if possible recover from them
    //
	CompletionCode = (UINT8)(IntTd->dControlStatus >> 28);
	switch (CompletionCode) {
		case GTD_STALL:
			gUsbData->dLastCommandStatusExtended |= USB_TRSFR_STALLED;
			break;
		case GTD_NOT_ACCESSED:
			gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
			break;
		default:
			break;
	}

	BytesTransferred = IntTd->fpCurrentBufferPointer == 0 ? wLength :
		IntTd->fpCurrentBufferPointer - (UINT32)fpBuffer;

	USB_MemFree(IntEd, GET_MEM_BLK_COUNT(sizeof(OHCI_ED) + sizeof(OHCI_TD)));

    return (UINT16)BytesTransferred;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_ActivatePolling
//
// DESCRIPTION: This function activates the polling TD for the requested
//              device. The device may be a USB keyboard or USB hub
//
// PARAMETERS:  fpHCStruc   Pointer to the HC structure
//              fpDevInfo   Pointer to the device information structure
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
// NOTES:       For the keyboard device this routine allocates TDRepeat
//              also, if it is not already allocated. This routine allocate
//              a polling TD and schedule it to 8ms schedule for keyboards
//              and to 1024ms schedule for hubs.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_ActivatePolling (
    HC_STRUC* fpHCStruc,
    DEV_INFO* fpDevInfo)
{
    UINT32 dData;
    UINT8   *fpPtr;
	UINT8	bDatToggle;

    EFI_STATUS EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (OhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}
    
    if (!VALID_DEVINFO(fpDevInfo)) {
        return USB_ERROR;
    }

	bDatToggle = UsbGetDataToggle(fpDevInfo, fpDevInfo->IntInEndpoint);

    fpPtr = USB_MemAlloc(1);
    ASSERT(fpPtr);
    fpDevInfo->fpPollEDPtr  = fpPtr;
    fpPtr = USB_MemAlloc(1);
    ASSERT(fpPtr);
    fpDevInfo->fpPollTDPtr  = fpPtr;

    dData = (fpDevInfo->IntInEndpoint & BIT7)? ED_IN_PACKET : ED_OUT_PACKET;
    dData |= (UINT32)fpDevInfo->bDeviceAddress | ((fpDevInfo->IntInEndpoint & 0xF) << 7);
    dData |= ((UINT32)fpDevInfo->IntInMaxPkt << 16);
	dData |= (UINT32)(fpDevInfo->bEndpointSpeed & 1) << 13;
	dData |= ED_SKIP_TDQ;

    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->dControl = dData;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->fpHeadPointer = (UINT32)(UINTN)fpDevInfo->fpPollTDPtr;
	((OHCI_ED*)fpDevInfo->fpPollEDPtr)->fpHeadPointer |= bDatToggle << 1;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->fpEDLinkPointer = OHCI_TERMINATE;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->fpTailPointer = OHCI_TERMINATE;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->Interval = OhciTranslateInterval(fpDevInfo->bPollInterval);

	fpDevInfo->fpPollDataBuffer = USB_MemAlloc(GET_MEM_BLK_COUNT(fpDevInfo->PollingLength));  
	ASSERT(fpDevInfo->fpPollDataBuffer);

    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->dControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->dCSReloadValue = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED << 28));
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->fpCurrentBufferPointer =
    			(UINT32)(fpDevInfo->fpPollDataBuffer); 					//(EIP54782)
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->fpBufferEnd =
    			(UINT32)(fpDevInfo->fpPollDataBuffer + fpDevInfo->PollingLength - 1);
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->fpLinkPointer = OHCI_TERMINATE;
    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->bCallBackIndex = USB_InstallCallBackFunction(OHCI_PollingTDCallback);

    OhciAddPeriodicEd(fpHCStruc, (OHCI_ED*)fpDevInfo->fpPollEDPtr);

    ((OHCI_TD*)fpDevInfo->fpPollTDPtr)->bActiveFlag = TRUE;
    ((OHCI_ED*)fpDevInfo->fpPollEDPtr)->dControl &= ~ED_SKIP_TDQ;
    return  USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_DeactivatePolling
//
// DESCRIPTION: This function de-activates the polling TD for the requested
//              device. The device may be a USB keyboard or USB hub
//
// PARAMETERS:  fpHCStruc   Pointer to the HC structure
//              fpDevInfo   Pointer to the device information structure
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_DeactivatePolling (
    HC_STRUC* fpHCStruc,
    DEV_INFO* fpDevInfo)
{
    OHCI_ED *fpOHCIED = (OHCI_ED*)fpDevInfo->fpPollEDPtr;
    OHCI_TD *fpOHCITD = (OHCI_TD*)fpDevInfo->fpPollTDPtr;

    EFI_STATUS  EfiStatus;
    
    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (OhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}
	
    if(!fpOHCIED) {
        return USB_SUCCESS;
    }

    fpOHCITD->dControlStatus = 0;
    fpOHCITD->dCSReloadValue = 0;
    fpOHCITD->bActiveFlag    = FALSE;

    OhciRemovePeriodicEd(fpHCStruc, fpOHCIED);

	UsbUpdateDataToggle(fpDevInfo, fpDevInfo->IntInEndpoint, 
			(UINT8)((fpOHCIED->fpHeadPointer & ED_TOGGLE_CARRY) >> 1));

    USB_MemFree(fpOHCITD, GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
    fpDevInfo->fpPollTDPtr = NULL;

    USB_MemFree(fpOHCIED, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    fpDevInfo->fpPollEDPtr = NULL;

	if(fpDevInfo->fpPollDataBuffer) {
		USB_MemFree(fpDevInfo->fpPollDataBuffer, 
			GET_MEM_BLK_COUNT(fpDevInfo->PollingLength)); 
    	fpDevInfo->fpPollDataBuffer = 0;
	} 

    return  USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_PollingTDCallback
//
// DESCRIPTION: This function is called when a polling TD from the TD pool
//      completes an interrupt transaction to its assigned device.
//      This routine should process any data in the TD's data buffer,
//      handle any errors, and then copy the TD's CSReloadValue
//      field into its control status field to put the TD back
//      into service.
//
//
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_PollingTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
)
{
    UINT8   i;
    UINT16  BytesTransferred;

    if (((OHCI_TD*)Td)->bActiveFlag == FALSE) {
        return USB_SUCCESS;
    }

	((OHCI_TD*)Td)->bActiveFlag = FALSE;
	DwordResetMem((UINT32)HcStruc->BaseAddress, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);

    for (i = 1; i < MAX_DEVICES; i++) {
        DevInfo = &gUsbData->aDevInfoTable[i];
        if (DevInfo->Flag & DEV_INFO_DEV_PRESENT) {
            if (DevInfo->fpPollTDPtr == Td) {
                break;
            }
        }
    }

    if (i == MAX_DEVICES) {
        return USB_ERROR;
    }

	UsbUpdateDataToggle(DevInfo, DevInfo->IntInEndpoint, 
			(UINT8)((((OHCI_ED*)DevInfo->fpPollEDPtr)->fpHeadPointer & ED_TOGGLE_CARRY) >> 1));

										//(EIP59707)>
	if ((((OHCI_TD*)Td)->dControlStatus & GTD_STATUS_FIELD) == GTD_NO_ERROR) {
        //
        // Get the size of data transferred
        //
        if (((OHCI_TD*)Td)->fpCurrentBufferPointer != 0) {
            BytesTransferred = ((OHCI_TD*)Td)->fpCurrentBufferPointer -
                (UINT32)(UINTN)(DevInfo->fpPollDataBuffer);
        } else {
            BytesTransferred = DevInfo->PollingLength;
        }
        if ((DevInfo->bCallBackIndex) && (DevInfo->bCallBackIndex <= MAX_CALLBACK_FUNCTION)) {
    	    (*gUsbData->aCallBackFunctionTable[DevInfo->bCallBackIndex-1])(
    	                HcStruc,
    	                DevInfo,
    	                (UINT8*)Td,
    	                DevInfo->fpPollDataBuffer,
    	                BytesTransferred);
        }
	}
										//<(EIP59707)
    DwordSetMem((UINT32)HcStruc->BaseAddress, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);

    // Clear the link pointer. It may point to some other TD
    ((OHCI_TD*)Td)->fpLinkPointer = OHCI_TERMINATE;
    ((OHCI_TD*)Td)->dControlStatus = ((OHCI_TD*)Td)->dCSReloadValue;
    ((OHCI_TD*)Td)->fpCurrentBufferPointer = (UINT32)(UINTN)(DevInfo->fpPollDataBuffer);		//(EIP54782)
    ((OHCI_ED*)DevInfo->fpPollEDPtr)->fpHeadPointer &= ED_TOGGLE_CARRY;
    ((OHCI_ED*)DevInfo->fpPollEDPtr)->fpHeadPointer |= (UINTN)((OHCI_TD*)Td);
    ((OHCI_TD*)Td)->bActiveFlag = TRUE;
    // Reset the TD's control and buffer pointer fields to their original values.
    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_DisableKeyRepeat
//
// DESCRIPTION: This function disables the keyboard repeat rate logic by
//              enabling the repeat TD
//
// PARAMETERS:  fpHCStruc   Pointer to the HCStruc structure
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_DisableKeyRepeat (
	HC_STRUC	*HcStruc
)
{
    OHCI_DESC_PTRS      *DescPtrs;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (OhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}
    
    DescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;

    if (DescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINT8*)DescPtrs < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs + sizeof(OHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }
    
    if (DescPtrs->fpEDRepeat == NULL) {
		return USB_ERROR;
    }

    if (((UINT8*)DescPtrs->fpEDRepeat < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs->fpEDRepeat + sizeof(OHCI_ED)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    DescPtrs->fpEDRepeat->dControl |= ED_SKIP_TDQ;    // Inactive
	DescPtrs->fpTDRepeat->bActiveFlag = FALSE;

    return  USB_SUCCESS;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_EnableKeyRepeat
//
// DESCRIPTION: This function enables the keyboard repeat rate logic by
//              enabling the repeat TD
//
// PARAMETERS:  fpHCStruc   Pointer to the HCStruc structure
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_EnableKeyRepeat (
	HC_STRUC	*HcStruc
)
{
    OHCI_DESC_PTRS      *DescPtrs;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (OhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}

    DescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;

    if (DescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINT8*)DescPtrs < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs + sizeof(OHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }

    if (DescPtrs->fpEDRepeat == NULL) {
		return USB_ERROR;
    }

    if (((UINT8*)DescPtrs->fpEDRepeat < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtrs->fpEDRepeat + sizeof(OHCI_ED)) > MemBlockEnd)) {
        return USB_ERROR;
    }

	DescPtrs->fpTDRepeat->fpLinkPointer = OHCI_TERMINATE;
	DescPtrs->fpEDRepeat->fpHeadPointer = (UINT32)(UINTN)DescPtrs->fpTDRepeat;
	DescPtrs->fpTDRepeat->dControlStatus = 
						DescPtrs->fpTDRepeat->dCSReloadValue;
	DescPtrs->fpTDRepeat->bActiveFlag = TRUE;
	DescPtrs->fpEDRepeat->dControl &= (~ED_SKIP_TDQ); // Active

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_EnumeratePorts
//
// DESCRIPTION: This API function is called to enumerate the root hub ports
//              in the OHCI controller. The input to the routine is the
//              pointer to the HC structure  that defines this host controller
//
// PARAMETERS:  fpHCStruc   Ptr to the host controller structure
//
// RETURN:      Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_EnumeratePorts(HC_STRUC* fpHCStruc)
{
	UINT32	BaseAddr = (UINT32)fpHCStruc->BaseAddress;
	UINT32  RhDescriptorA = 0;
	UINT8	PowerOnDelay = 0;
	UINT8	Index = 0;
	UINT16	PortReg = OHCI_RH_PORT1_STATUS;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (OhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}

	RhDescriptorA = DwordReadMem(BaseAddr, OHCI_RH_DESCRIPTOR_A);
	if (!(RhDescriptorA & NO_POWER_SWITCH)) {
		if (!(RhDescriptorA & POWER_SWITCH_MODE)) {
			// All ports are powered at the same time, enable global port power
	    	DwordWriteMem(BaseAddr, OHCI_RH_STATUS, SET_GLOBAL_POWER);
		} else {
			// Each port is powered individually, enable individual port's power
			for (Index = 0; Index < fpHCStruc->bNumPorts; PortReg+=4, Index++) {
                // Set PortPowerControlMask bit 
                DwordSetMem(BaseAddr, OHCI_RH_DESCRIPTOR_B, ((1 << (Index + 1)) << 16));
                // Set PortPower bit
				DwordWriteMem(BaseAddr, PortReg, SET_PORT_POWER);
			}
		}
		PowerOnDelay = ((RhDescriptorA & POWERON2POWERGOOD_TIME) >> 24) << 1;
		FixedDelay(PowerOnDelay * 1000);
	}

    OHCI_ProcessRootHubStatusChange(fpHCStruc);

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OhciAddPeriodicEd
//
// DESCRIPTION: This function adds a ED to the frame list
//
// PARAMETERS:  HcStruc - Ptr to the host controller structure
//              Ed - ED will be added in periodic schedule
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OhciAddPeriodicEd (
    HC_STRUC    *HcStruc,
    OHCI_ED     *Ed
)
{
    UINT16  Index;
    UINT32  *PrevPtr;
    OHCI_ED *Current;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (Ed == NULL || Ed->Interval == 0) {
        return USB_ERROR;
    }

    for (Index = 0; Index < HcStruc->wAsyncListSize; Index += Ed->Interval) {
        PrevPtr = &HcStruc->fpFrameList[Index]; 
        Current = (OHCI_ED*)(*PrevPtr);

        while (Current != NULL) {
#if USB_RUNTIME_DRIVER_IN_SMM
            Status = AmiValidateMemoryBuffer((VOID*)Current, sizeof(OHCI_ED));
            if (EFI_ERROR(Status)) {
                return USB_ERROR;
            }
#endif
            if (Current->Interval <= Ed->Interval) {
                break;
            }

            PrevPtr = &Current->fpEDLinkPointer; 
            Current = (OHCI_ED*)Current->fpEDLinkPointer;
        }

        if (Current == Ed) {
            continue;
        }
        Ed->fpEDLinkPointer = (UINT32)(UINTN)Current;
#if USB_RUNTIME_DRIVER_IN_SMM
         Status = AmiValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
         if (EFI_ERROR(Status)) {
            return USB_ERROR;
         }
#endif
        *PrevPtr = (UINT32)(UINTN)Ed;
    }

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OhciRemovePeriodicEd
//
// DESCRIPTION: This function removes a ED from the frame list
//
// PARAMETERS:  HcStruc - Ptr to the host controller structure
//              Ed - ED will be removed from periodic schedule
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OhciRemovePeriodicEd (
    HC_STRUC    *HcStruc,
    OHCI_ED     *Ed
)
{
    UINT16  Index;
    UINT32  *PrevPtr;
    OHCI_ED *Current;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (Ed == NULL || Ed->Interval == 0) {
        return USB_ERROR;
    }

    Ed->dControl |= ED_SKIP_TDQ;

    for (Index = 0; Index < HcStruc->wAsyncListSize; Index += Ed->Interval) {
        PrevPtr = &HcStruc->fpFrameList[Index]; 
        Current = (OHCI_ED*)(*PrevPtr);

        while (Current != NULL) {
#if USB_RUNTIME_DRIVER_IN_SMM
            Status = AmiValidateMemoryBuffer((VOID*)Current, sizeof(OHCI_ED));
            if (EFI_ERROR(Status)) {
                return USB_ERROR;
            }
#endif
            if (Current == Ed) {
                break;
            }

            PrevPtr = &Current->fpEDLinkPointer; 
            Current = (OHCI_ED*)Current->fpEDLinkPointer;
        }

        if (Current == NULL) {
            continue;
        }
#if USB_RUNTIME_DRIVER_IN_SMM
         Status = AmiValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
         if (EFI_ERROR(Status)) {
            return USB_ERROR;
         }
#endif
        *PrevPtr = Ed->fpEDLinkPointer;
    }

    DwordWriteMem((UINT32)HcStruc->BaseAddress, OHCI_INTERRUPT_STATUS, START_OF_FRAME);
    DwordWriteMem((UINT32)HcStruc->BaseAddress, OHCI_INTERRUPT_ENABLE, START_OF_FRAME_ENABLE);

    for (Index = 0; Index < 100; Index++) {
        if (DwordReadMem((UINT32)HcStruc->BaseAddress, 
                OHCI_INTERRUPT_STATUS) & START_OF_FRAME) {
            break;
        }
        FixedDelay(10);   // 10 us delay
    }
    ASSERT(Index < 100);
    ASSERT(DwordReadMem((UINT32)HcStruc->BaseAddress, OHCI_INTERRUPT_STATUS) & START_OF_FRAME);
    DwordWriteMem((UINT32)HcStruc->BaseAddress, OHCI_INTERRUPT_DISABLE, START_OF_FRAME_DISABLE);

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OHCI_StartEDSchedule
//
// DESCRIPTION: This function starts the standard TD schedules for the
//              USB host controller
//
// PARAMETERS:  HCStruc for the controller
//
// RETURN:      USB_ERROR on error, USB_SUCCESS on success
//
// NOTES:   This routine creates 1, 2, 8, 32 and 1024ms schedules
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_StartEDSchedule(
    HC_STRUC    *HcStruc
)
{
    OHCI_DESC_PTRS  *DescPtrs;
    UINT8           *Ptr;

    //
    // Allocate descriptor structure and fill it in HCStruc
    //
    DescPtrs = (OHCI_DESC_PTRS*)USB_MemAlloc (GET_MEM_BLK_COUNT_STRUC(OHCI_DESC_PTRS));
    ASSERT(DescPtrs);
    if (!DescPtrs) return USB_ERROR;

    //
    // Save the value in the HC struc
    //
    HcStruc->stDescPtrs.fpOHCIDescPtrs = DescPtrs;

    //
    // Allocate 4 EDs + 1 TDs and put them in Descriptor list
    //
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    ASSERT(Ptr);
    if (!Ptr) return USB_ERROR;

    DescPtrs->PeriodicEd = (OHCI_ED*)Ptr;
    DescPtrs->PeriodicEd->dControl = ED_SKIP_TDQ;
    DescPtrs->PeriodicEd->fpEDLinkPointer = 0;
    DescPtrs->PeriodicEd->Interval = 1;

    // Initialize each entry of Interrupt Table as statically disable ED
    OhciAddPeriodicEd(HcStruc, DescPtrs->PeriodicEd);

    //
    // Allocate ED/TD for EDControl, TDControlSetup, TDControlData,
    // TDControlStatus, EDBulk, TDBulkData, EDInterrupt and TDInterruptData
    //
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT(2 * sizeof(OHCI_ED) + 4 * sizeof(OHCI_TD)));
    ASSERT(Ptr);
    if (!Ptr) return USB_ERROR;

    //
    // Save the 8 ED/TD in their proper position. Note: fpHCStruc->stDescPtrs.fpEHCIDescPtrs
    // is initialized earlier in OHCI_StartEDSchedule.
    //
    DescPtrs->fpEDControl = (OHCI_ED*)Ptr;
    Ptr += sizeof (OHCI_ED);

    DescPtrs->fpTDControlSetup = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->fpTDControlData = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->fpTDControlStatus = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->fpEDBulk = (OHCI_ED*)Ptr;
    Ptr += sizeof (OHCI_ED);

    DescPtrs->fpTDBulkData = (OHCI_TD*)Ptr;

	if (HcStruc->dHCFlag & HC_STATE_EXTERNAL) {
		return USB_SUCCESS;
	}

    // Allocate a ED/TD for EDRepeat/TDRepeat
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    ASSERT(Ptr);
    DescPtrs->fpEDRepeat  = (OHCI_ED*)Ptr;
 
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
    ASSERT(Ptr);
    DescPtrs->fpTDRepeat  = (OHCI_TD*)Ptr;

    DescPtrs->fpEDRepeat->dControl = (DUMMY_DEVICE_ADDR |
            ED_IN_PACKET | ED_SKIP_TDQ | (DEFAULT_PACKET_LENGTH << 16));
    DescPtrs->fpEDRepeat->fpHeadPointer = (UINT32)(UINTN)DescPtrs->fpTDRepeat;
    DescPtrs->fpEDRepeat->fpEDLinkPointer = OHCI_TERMINATE;
    DescPtrs->fpEDRepeat->fpTailPointer = OHCI_TERMINATE;
    DescPtrs->fpEDRepeat->Interval = REPEAT_INTERVAL;

    DescPtrs->fpTDRepeat->dControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
        GTD_TWO_ERRORS | (GTD_NOT_ACCESSED << 28));
    DescPtrs->fpTDRepeat->dCSReloadValue = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
        GTD_TWO_ERRORS | (GTD_NOT_ACCESSED << 28));

    DescPtrs->fpTDRepeat->fpCurrentBufferPointer =
                (UINT32)(UINTN)DescPtrs->fpTDRepeat->aSetupData;
    DescPtrs->fpTDRepeat->fpBufferEnd =
                (UINT32)(UINTN)DescPtrs->fpTDRepeat->aSetupData;
    DescPtrs->fpTDRepeat->fpLinkPointer = OHCI_TERMINATE;
    DescPtrs->fpTDRepeat->bCallBackIndex = USB_InstallCallBackFunction(OHCI_RepeatTDCallBack);
    DescPtrs->fpTDRepeat->bActiveFlag = FALSE;

    OhciAddPeriodicEd(HcStruc, DescPtrs->fpEDRepeat);
	
	USBKeyRepeat(HcStruc, 0);

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OHCI_ResetHC
//
// DESCRIPTION: This function resets the OHCI controller
//
// PARAMETERS:  Pointer to the HCStruc structure
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 OHCI_ResetHC(HC_STRUC* fpHCStruc)
{
	UINT32	BaseAddr = (UINT32)fpHCStruc->BaseAddress;
	UINT8	i;
    //
    // Issue a software reset and HC go to UsbSuspend state
    //
    DwordWriteMem(BaseAddr, OHCI_COMMAND_STATUS, HC_RESET);

    // The reset operation must be completed within 10 us
	for (i = 0; i < 100; i++) {
		FixedDelay(1);   // 1 us delay
		if (!(DwordReadMem(BaseAddr, OHCI_COMMAND_STATUS) & HC_RESET)) {
			return USB_SUCCESS;
		}
	}

	return USB_ERROR;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OHCI_ProcessRootHubStatusChange
//
// DESCRIPTION: This function is called when TD1024ms completes
//      a transaction. This TD runs a dummy interrupt transaction
//      to a non-existant device address for the purpose of
//      generating a periodic timeout interrupt.  This periodic
//      interrupt may be used to check for new devices on the
//      root hub etc.
//
// PARAMETERS:  Pointer to HC Struc
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 OHCI_ProcessRootHubStatusChange(HC_STRUC* fpHCStruc)
{
    UINT8   bHCNumber, bPort;//, bPortStatus;	//(EIP59663)

    //
    // Check bEnumFlag before enumerating devices behind root hub
    //
    if (gUsbData->bEnumFlag == TRUE) return USB_ERROR;
    gUsbData->bEnumFlag = TRUE;    // Set enumeration flag and avoid hub port enumeration
    //
    // Mask the Host Controller interrupt so the ISR does not get re-entered due
    // to an IOC interrupt from any TDs that complete in frames while we are
    // configuring a new device that has just been plugged in.
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_DISABLE, 0x80000000);
    //
    // Check all the ports on the root hub for any change in connect status.
    // If the connect status has been changed on either or both of these ports,
    // then call the  routine UsbHubPortChange for each changed port.
    //
    bHCNumber = fpHCStruc->bHCNumber | BIT7;

    for (bPort = 1; bPort <= fpHCStruc->bNumPorts; bPort++) {
										//(EIP59663)>
        //bPortStatus = OHCI_GetRootHubStatus (fpHCStruc, bPort+1);
      	//DwordResetMem((UINT32)fpHCStruc->BaseAddress, OHCI_RH_PORT1_STATUS+bPort*4, 0xFFFF);
        //if (bPortStatus & USB_PORT_STAT_DEV_CONNECT_CHANGED) {
		USBCheckPortChange(fpHCStruc, bHCNumber, bPort);
        //}
        //DwordResetMem((UINT32)fpHCStruc->BaseAddress, OHCI_RH_PORT1_STATUS+bPort*4, 0xFFFF);
										//<(EIP59663)
    }
    //
    // Clear the RH_STATUS_CHANGE bit of the interrupt status register
    // in the host controller: write 1 to bit to clear it
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_STATUS, RH_STATUS_CHANGE);

    //
    // Renable interrupts from the host controller
    //
    DwordWriteMem((UINT32)fpHCStruc->BaseAddress, OHCI_INTERRUPT_ENABLE, MASTER_INTERRUPT_ENABLE);

    gUsbData->bEnumFlag    = FALSE;
    return USB_SUCCESS;
}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCIWaitForTransferComplete
//
// DESCRIPTION: This function executes a device request command transaction
//
// PARAMETERS:  fpHCStruc   Pointer to HCStruc of the host controller
//              fpTD        Pointer to the TD which has to be completed
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCIWaitForTransferComplete(
	HC_STRUC	*fpHCStruc, 
	OHCI_ED		*XferED,
	OHCI_TD		*LastTD,
    DEV_INFO*	fpDevInfo
)
{
    UINT32 Count ;
    UINT32 Timeout = gUsbData->wTimeOutValue << 4; // *16, makes it number of 60mcs units

    //
    // Check status change loop iteration
    //
    for(Count = 0; !Timeout || Count < Timeout; Count++) {
        OHCI_ProcessInterrupt(fpHCStruc);
        if(!LastTD->bActiveFlag )
           return   USB_SUCCESS;
        else if(!VALID_DEVINFO(fpDevInfo)){
            USB_DEBUG (DEBUG_LEVEL_3, "OHCI Abort: devinfo: %x\n",fpDevInfo );
            return USB_ERROR;
        }
        FixedDelay(60);  // 60 microseconds
    }

	XferED->dControl |= ED_SKIP_TDQ;
	OHCI_ProcessInterrupt(fpHCStruc);

	if(!LastTD->bActiveFlag) {
		return USB_SUCCESS;
	}

    USB_DEBUG (DEBUG_LEVEL_3, "OHCI Time-Out\n");

    return USB_ERROR;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OHCI__StopUnsupportedHC
//
// DESCRIPTION: This routine is called, from host controllers that supports
//      OS handover functionality (currently from OHCI driver only), when OS
//      wants the BIOS to hand-over the host controllers to the OS.  This routine
//      will stop HC that does not support this functionality.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_StopUnsupportedHC(
	HC_STRUC*	HcStruc
)
{
    UINT8	i;

	if (!gUsbData->UsbEhciHandoff) {
		return USB_SUCCESS;
	}

//
// Currently this host controller stops only the EHCI host controllers
// Find the EHCI host controller HCStruc
//
    for (i = 0; i < gUsbData->HcTableCount; i++ ) {
        if (gUsbData->HcTable[i] == NULL) {
            continue;
        }
        if (!(gUsbData->HcTable[i]->dHCFlag & HC_STATE_USED)) {
        	continue;
        }
		if (!(gUsbData->HcTable[i]->dHCFlag & HC_STATE_RUNNING) ||
			(gUsbData->HcTable[i]->bHCType != USB_HC_EHCI) ||
			((gUsbData->HcTable[i]->wBusDevFuncNum & ~0x7) != 
			(HcStruc->wBusDevFuncNum & ~0x7))) {
			continue;
		}

		gUsbData->bHandOverInProgress = TRUE;
		(*gUsbData->aHCDriverTable[GET_HCD_INDEX(
			gUsbData->HcTable[i]->bHCType)].pfnHCDStop)(gUsbData->HcTable[i]);
    }

	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OHCI_GeneralTDCallback
//
// DESCRIPTION: This function is called when bulk data or interrupt data TD
//              is completed. This routine just deactivates the TD.
//
// PARAMETERS:  Pointer to the HCStruc structure
//              Pointer to the TD that completed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_GeneralTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
 )
{
    ((OHCI_TD*)Td)->bActiveFlag = FALSE;
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:    OHCI_ControlTDCallback
//
// DESCRIPTION: This function is called when the control transfer scheduled
//              is completed.
//
// PARAMETERS:  fpHCStruc   Pointer to the HCStruc structure
//              fpDevInfo   NULL (pDevInfo is not valid)
//              fpTD        Pointer to the TD that completed
//              fpBuffer    Not used
//
// RETURN:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OHCI_ControlTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
)
{
    OHCI_DESC_PTRS *DescPtrs;
    UINT8           *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);
    
    //
    // Check to see if the TD that just completed has any error bits set.  If
    // any of the control TDs (Setup, Data, or Status) complete with an error, set
    // ActiveFlag of the control status TD and copy the error information from the
    // TD that just completed into the control status TD.
    //
    if ((UINT8)(((OHCI_TD*)Td)->dControlStatus >> 28)) {
        DescPtrs = HcStruc->stDescPtrs.fpOHCIDescPtrs;
        if (((UINT8*)DescPtrs < gUsbData->fpMemBlockStart) ||
            ((UINT8*)(DescPtrs + sizeof(OHCI_DESC_PTRS)) > MemBlockEnd)) {
            return USB_ERROR;
        }
        if (((UINT8*)DescPtrs->fpTDControlStatus < gUsbData->fpMemBlockStart) ||
            ((UINT8*)(DescPtrs->fpTDControlStatus + sizeof(OHCI_TD)) > MemBlockEnd)) {
            return USB_ERROR;
        }
        if (DescPtrs->fpTDControlStatus != (OHCI_TD*)Td) {
            DescPtrs->fpTDControlStatus->dControlStatus = ((OHCI_TD*)Td)->dControlStatus;
            DescPtrs->fpTDControlStatus->bActiveFlag = FALSE;
        }
    }
    //
    // Make the TD that just completed inactive.  It may be the control setup TD,
    // one of the control data TDs, or the control status TD.
    //
    ((OHCI_TD*)Td)->bActiveFlag = FALSE;

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OHCI_ProcessTD
//
// DESCRIPTION: This function will check whether the TD is completed
//              if so, it will call the call back routine associated with
//              this TD.
//
// PARAMETERS:  HCStruc structure, Pointer to the TD
//
// NOTES:   For any TD whose ActiveFlag is TRUE and its ControlStatus
//      bit 23 is clear (completed), process the TD by calling
//      its call back routine, if one is present.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void OHCI_ProcessTD(
    HC_STRUC    *HcStruc,
    OHCI_TD     *Td
)
{
    if (!Td) {
        return;  // Check for NULL
    }
    if (Td->bActiveFlag != TRUE) {
        return;  // TD is not active
    }
    if ((Td->bCallBackIndex) && (Td->bCallBackIndex <= MAX_CALLBACK_FUNCTION)) {
        if (gUsbData->aCallBackFunctionTable[Td->bCallBackIndex-1]) {
            (*gUsbData->aCallBackFunctionTable[Td->bCallBackIndex-1])(
                HcStruc,
                0,
                (UINT8*)Td,
                0,
                0);
        }
    }
}

										//(EIP28707+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// FUNCTION:    OHCI_FreeAllStruc
//
// DESCRIPTION: This function is used to free the all the allocated TDs,
//				QH and DescriptorPtr structure. This function only frees
//				the entries in the DescriptorPtr and the descriptor pointer
//				only.
//                                                                              ;
// PARAMETERS:  fpHCStruc   Pointer to the HCStruc structure
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID OHCI_FreeAllStruc(HC_STRUC* fpHCStruc)
{
	OHCI_DESC_PTRS  *fpDescPtrs;

	fpDescPtrs = fpHCStruc->stDescPtrs.fpOHCIDescPtrs;

// Free the EDs & TDs
	USB_MemFree(fpDescPtrs->PeriodicEd, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
	if (fpDescPtrs->fpEDRepeat) {
		USB_MemFree(fpDescPtrs->fpEDRepeat, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
	}
	if (fpDescPtrs->fpTDRepeat) {
		USB_MemFree(fpDescPtrs->fpTDRepeat, GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
	}

	USB_MemFree(fpDescPtrs->fpEDControl, 
        GET_MEM_BLK_COUNT(2 * sizeof(OHCI_ED) + 4 * sizeof(OHCI_TD)));
	
// Free descriptor structure (in BX)
	USB_MemFree(fpDescPtrs, GET_MEM_BLK_COUNT_STRUC(OHCI_DESC_PTRS));
}
										//<(EIP28707+)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   OhciIsHalted
//
// Description: This function check whether HC is halted.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
OhciIsHalted (
	HC_STRUC	*HcStruc
)
{
	return (DwordReadMem((UINT32)HcStruc->BaseAddress, OHCI_CONTROL_REG) & HC_FUNCTION_STATE) != USBOPERATIONAL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   OhciTranslateInterval
//
// Description: This function calculates the polling rate.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
OhciTranslateInterval(
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
