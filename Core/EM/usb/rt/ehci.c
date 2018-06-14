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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/ehci.c 152   10/16/16 10:12p Wilsonlee $
//
// $Revision: 152 $
//
// $Date: 10/16/16 10:12p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/ehci.c $
// 
// 152   10/16/16 10:12p Wilsonlee
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
// 151   7/22/16 3:50a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 150   7/07/16 2:08a Wilsonlee
// [TAG]  		EIP268836
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	The system will loop in USB runtime module during IPMI are
// resetting USB controller.
// [RootCause]  	Qh->dLinkPointer is invalid after device is disconnected.
// [Solution]  	Check if Qh is changed after we process it.
// [Files]  		ehci.c
// 
// 149   7/07/16 1:09a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 148   3/14/16 10:21p Wilsonlee
// [TAG]  		EIP257506
// [Category]  	Improvement
// [Description]  	Add USB_KEYREPEAT_INTERVAL token to change the key
// repeat interval.
// [Files]  		usb.sdl, xhci.h, usbkbd.h, uhci.c, ohci.c, ehci.c
// 
// 147   3/02/16 9:42p Wilsonlee
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
// 146   9/06/15 10:05p Wilsonlee
// 
// 145   7/24/15 4:41a Wilsonlee
// [TAG]  		EIP226493
// [Category]  	Improvement
// [Description]  	Block to process periodic list to prevent that we might
// send the wrong command sequences to the same device.
// [Files]  		usbmass.c, ehci.c, xhci.h, xhci.c, usbdef.h, uhcd.c
// 
// 144   5/26/15 10:48p Wilsonlee
// [TAG]  		EIP219177
// [Category]  	Improvement
// [Description]  	Fixed static code analysis issues in Usb module.
// [Files]  		UsbInt13.c, ehci.c, usbbus.c
// 
// 143   4/10/15 3:11a Wilsonlee
// [TAG]  		EIP207413
// [Category]  	Improvement
// [Description]  	Install UsbApiTable and UsbMassApitTable in
// AmiUsbSmmProtocol.
// [Files]  		amiusbhc.c, AmiUsbController.h, usbdef.h, usbCCID.c, uhci.c,
// ehci.c, amiusbrtCCID.h, amiusb.h, amiusb.c, uhcd.c
// 
// 142   4/07/15 4:36a Wilsonlee
// [TAG]  		EIP212211
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB transfer speed is slower than before in EHCI.
// [RootCause]  	If we parse through the all periodic list, the
// performance is low in AMD platforms.
// [Solution]  	Only parse the first entry through
// MAX_SPLIT_PERIODIC_NUMBER.
// [Files]  		ehci.c
// 
// 141   3/22/15 11:12p Wilsonlee
// [TAG]  		EIP206118
// [Category]  	Improvement
// [Description]  	Remove dead loop in EHCIStartAsyncSchedule and
// EHCIStopAsyncSchedule functions.
// [Files]  		ehci.c
// 
// 140   3/08/15 10:50p Wilsonlee
// [TAG]  		EIP207774
// [Category]  	Improvement
// [Description]  	Set USB_FLAG_DRIVER_STARTED flag when HC is running and
// clear it if we don't start any HC.
// [Files]  		uhci.c, usb.c, ehci.c, ohci.c, xhci.c, amiusb.h
// 
// 139   2/24/15 9:53p Wilsonlee
// [TAG]  		EIP205784
// [Category]  	Improvement
// [Description]  	Don't read Periodic Frame List Base Address Register if
// the controller doesn't support periodic schedule.
// [Files]  		ehci.c
// 
// 138   2/24/15 9:35p Wilsonlee
// [TAG]  		EIP206118
// [Category]  	Improvement
// [Description]  	Remove dead loop in EHCIStartAsyncSchedule and
// EHCIStopAsyncSchedule functions.
// [Files]  		ehci.c
// 
// 137   1/22/15 10:19p Wilsonlee
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
// 136   12/21/14 9:30p Wilsonlee
// [TAG]  		EIP194553
// [Category]  	Improvement
// [Description]  	Realtek 8111EP EHCI controller workaround, this
// controller doesn't work if the buffer address isn't DWORD alignment
// (current offset of qTD). Provide the workaround to locate DWORD
// alignment buffer.
// [Files]  		ehci.c
// 
// 135   11/24/14 12:50a Wilsonlee
// [TAG]  		EIP185972
// [Category]  	Improvement
// [Description]  	To acquire more bandwidth, a dynamically transfer queue
// allocation mechanism is required.
// [Files]  		ehci.c, usbdef.h
// 
// 134   5/01/14 3:56a Ryanchou
// [TAG]  		EIP162589
// [Category]  	Improvement
// [Description]  	Do not register external controller as key repeat
// controller.
// [Files]  		ehci.c, ohci.c, uhci.c
// 
// 133   4/30/14 6:12a Ryanchou
// [TAG]  		EIP151374
// [Category]  	Improvement
// [Description]  	Calculates maximum data length to be reported in the
// HID device.
// [Files]  		ehci.c, ohci.c, uhci.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, xhci.c
// 
// 132   4/30/14 5:25a Wilsonlee
// [TAG]  		EIP164842
// [Category]  	Improvement
// [Description]  	Check if the devices have put into to our queue before
// we put them.
// [Files]  		UsbInt13.c, amiusb.c, ehci.c, ohci.c, usb.c, usbdef.h,
// usbmass.c, xhci.c, amiusbhc.c, efiusbmass.c, uhcd.c, usbbus.c, usbsb.c
// 
// 131   2/26/14 1:56a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 130   11/26/13 4:15a Ryanchou
// [TAG]  		EIP142940
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB keyboard cannot work if token USB_RUNTIME_DRIVER_IN_SMM
// is disabled.
// [RootCause]  	The variable Qh in EhciAddPeriodicQh() does not have
// initialize value.
// [Solution]  	Check if the value of variable Qh is valid first.
// [Files]  		ehci.c
// 
// 129   9/05/13 12:14a Wilsonlee
// [TAG]  		EIP135237
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB can't work when turn on AMIDEBUG_RX_SUPPORT.
// [RootCause]  	EHCI_PORT_CHANGE_DETECT bit isn't set when turn on
// AMIDEBUG_RX_SUPPORT.
// [Solution]  	Ignore the EHCI_PORT_CHANGE_DETECT bit to check the root
// hub ports at first time.
// [Files]  		ehci.c
// 
// 128   7/26/13 2:33a Ryanchou
// [TAG]  		EIP122142
// [Category]  	Improvement
// [Description]  	Improve periodic schedule mechanism
// [Files]  		ehci.c, ehci.h, ohci.c, ohci.h, uhci.c, uhci.h, usbdef.h,
// amiusbhc.c
// 
// 127   7/22/13 10:31p Wilsonlee
// [TAG]  		EIP125357
// [Category]  	Improvement
// [Description]  	Check if the port releases to a select host controller.
// [Files]  		uhci.c, usb.c, usbhub.c, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 126   6/26/13 2:18a Roberthsu
// [TAG]           EIP122174
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Usb keyboard can not work.When special usb key insert
// [RootCause]     This keyboard detect connect status signal during this
// key initial. So port detect not service.
// [Solution]      Clear port detect status before check port change.
// [Files]         ehci.c
// 
// 125   6/02/13 11:41p Wilsonlee
// [TAG]  		EIP123235
// [Category]  	Improvement
// [Description]  	Stop the usb host controller at ExitBootService if it
// is an extend card or it doesn't support HW SMI.
// [Files]  		xhci.c, ehci.c, uhci.c, ohci.c, amiusb.c, usbdef.h, usbsb.c,
// uhcd.c
// 
// 124   5/12/13 11:52p Wilsonlee
// Set the data toggle to QH at EHCI_ActivatePolling and
// EHCI_InterruptTransfer.
// 
// 123   5/02/13 2:35a Wilsonlee
// [TAG]  		EIP121790
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	The usb keyboard doesn't work fine behind usb 2.0 hub.
// [RootCause]  	Teradici ehci controlle doesn't preserves DT bit in the
// qTD.
// [Solution]  	Don't set "Data toggle control" bit and check DT bit in
// the queue head.
// [Files]  		ehci.c
// 
// 122   5/01/13 9:54p Wilsonlee
// [TAG]  		EIP121643
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Cannot detect the usb floppy.
// [RootCause]  	This device doesn't return data when we sned
// get-config-descriptor command.
// [Solution]  	We retry to send get-config-descriptor command if there is
// no data.
// [Files]  		usb.c, ehci.c
// 
// 121   4/18/13 1:02p Ryanchou
// Add Teradici USB controller support.
// 
// 120   4/16/13 6:44a Ryanchou
// [TAG]  		EIP118912
// [Category]  	Improvement
// [Description]  	Add VIA VT6212 EHCI controller support.
// [Files]  		ehci.c, uhci.c, usbdef.h, uhcd.c
// 
// 119   3/19/13 3:59a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 118   3/18/13 4:47a Ryanchou
// [TAG]  		EIP98377
// [Category]  	Improvement
// [Description]  	Optimize USB controller timing.
// [Files]  		usb.sdl, usbport.c, ehci.c, elib.c, ohci.c, uhci.c,
// usbdef.h, usbhub.c, xhci.c, uhcd.c
// 
// 117   2/24/13 8:59p Wilsonlee
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
// 116   1/24/13 3:20a Roberthsu
// [TAG]           EIP111010 
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Touch panel button not work.
// [RootCause]     Device write wrong buffer.
// [Solution]      Clear bufferptr in pollingtdcallback.
// [Files]         ehci.c
// 
// 115   1/11/13 4:16a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 114   12/24/12 5:06a Ryanchou
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
// 113   12/06/12 12:38a Wilsonlee
// [TAG]  		EIP103186
// [Category]  	Improvement
// [Description]  	Handle the error case "MEMIO was disabled" in USB
// driver.
// [Files]  		uhci.c, ohci.c, ehci.c, xhci.c
// 
// 112   11/24/12 9:00p Wilsonlee
// [TAG]  		EIP107513
// [Category]  	Improvement
// [Description]  	Stop periodic schedule before removing QH.
// [Files]  		ehci.c
// 
// 111   11/13/12 7:11a Wilsonlee
// [TAG]  		EIP82553
// [Category]  	New Feature
// [Description]  	Support usb S5 wake up function for XHCI.
// [Files]  		usb.c, ehci.c, ohci.c, xhci.c, xhci.h
// 
// 110   11/10/12 6:40a Ryanchou
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
// 109   10/26/12 8:58a Roberthsu
// [TAG]           EIP102781
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       After update usb module, DebugRx hang at UHCD.Start().
// [RootCause]     dHCSParams vaule not vaild.
// [Solution]      Function EhciIsolateDebugPort move after variable
// dHCSParams fill.
// [Files]         ehci.c
// 
// 108   10/25/12 4:28a Wilsonlee
// [TAG]  		EIP103051
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	With USB3.0 flash on USB3.0 port and set to USB mode2,
// system will hang at post code 0x92 during the first cold boot after
// connecting AC power.
// [RootCause]  	This device connects to ehci first and it was
// disconnected after we reset the port.
// [Solution]  	We need to check the connect status after resetting the
// port.
// [Files]  		ehci.c
// 
// 107   10/25/12 4:15a Wilsonlee
// [TAG]  		EIP82354
// [Category]  	New Feature
// [Description]  	Support usb S5 wake up function for OHCI.
// [Files]  		usb.c, ehci.c, ohci.c
// 
// 106   9/28/12 2:37a Wilsonlee
// [TAG]  		EIP93154
// [Category]  	Improvement
// [Description]  	Change the unit of the FixedDelay from 15 us to 1 us.
// [Files]  		amiusb.h, xhci.c, ehci.c, ohci.c, uhci.c, usb.c, usbCCID.c,
// usbmass.c, usbhub.c, elib.c
// 
// 105   8/29/12 9:32a Ryanchou
// [TAG]  		EIP88307
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Key repeat cannot be stopped if the keyboard is connected
// to xHCI.
// [RootCause]  	Periodic timer SMI stop generating when USB SMI and
// periodic timer SMI is generated frequently.
// [Solution]  	Reduces the key repeat rate to avoid this issue.
// [Files]  		ehci.c, usb.c, usb.sdl
// 
// 104   8/29/12 8:16a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 103   5/04/12 6:38a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 102   5/03/12 5:59a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 101   5/03/12 5:17a Ryanchou
// [TAG]  		EIP88085
// [Category]  	Improvement
// [Description]  	Added 1 ms delay after port reset completed.
// [Files]  		ehci.c
// 
// 100   5/03/12 5:08a Ryanchou
// [TAG]  		EIP83361
// [Category]  	New Feature
// [Description]  	Added "USB 2.0 Controller Mode" setup item.
// [Files]  		ehci.c, usb.sd, usb.sdl, usb.uni, usbdef.h, UsbPolicy.h,
// usbport.c
// 
// 99    4/10/12 10:12p Wilsonlee
// [TAG]  		EIP84790
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB IO PROTOCOL under XHCI issue
// [RootCause]  	The DevMiscInfo is NULL.
// [Solution]  	Fill the DevMiscInfo for the xhci controller.
// [Files]  		ehci.c, xhci.c, amiusbhc.c
// 
// 98    4/05/12 7:42a Wilsonlee
// [TAG]  		EIP86001
// [Category]  	Improvement
// [Description]  	Free the chunk of memory allocated using the
// USBMem_Alloc call when we didn't use it. 
// [Files]  		usbhid.c, ehci.c
// 
// 97    3/20/12 10:34p Wilsonlee
// [TAG]  		EIP83295
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System will hang at B2 when do S3/S4 long run test or DOS
// reboot test.
// [RootCause]  	It causes the stack problem when we call
// IsUSBKeyboardBufferEmpty function.
// [Solution]  	Change to use pointer as parameter to
// IsUSBKeyboardBufferEmpty function.
// [Files]  		efiusbkb.c, efisubkb.h, usbmass.c, ehci.c
// 
// 96    2/16/12 9:04p Wilsonlee
// [TAG]  		EIP82307
// [Category]  	Improvement
// [Description]  	Port routing route to EHCI when EHCI initialization.
// [Files]  		ehci.c
// 
// 95    1/16/12 1:05a Wilsonlee
// [TAG]  		EIP81030
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	System hangs randomly at POST.
// [RootCause]  	This is EIP71067 side effect. It uses error memory
// address.
// [Solution]  	The change used the correct memory address.
// [Files]  		ehci.c
// 
// 94    12/23/11 8:39p Wilsonlee
// [TAG]  		EIP71067
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	SMI Timeout with USB FD and USB Flash Memory
// [RootCause]  	It uses the same area to bulk transfer on EHCI/
// [Solution]  	It uses local QH and QTD for each control and bulk
// transfer on EHCI
// [Files]  		ehci.c
// 
// 93    11/09/11 3:30a Ryanchou
// [TAG]  		EIP73692
// [Category]  	Improvement
// [Description]  	Implement the ownership change mechanism for PCH.
// [Files]  		ehci.c, usbdef.h, usbsrc.sdl
// 
// 92    11/08/11 1:57a Ryanchou
// [TAG]  		EIP63188
// [Category]  	Improvement
// [Description]  	External USB controller support.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, uhcd.c, uhcd.h, uhci.c,
// usbdef.h, usbmisc.c, usbsb.c, xhci.c
// 
// 91    9/09/11 5:06a Roberthsu
// [TAG]  		EIP68865
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	VIA plug in USB KB/MS cause system hang
// [RootCause]  	After release port.Ehci_line_status still exist.
// [Solution]  	Release port owner when connect status change.
// [Files]  		ehci.c
// 
// 90    8/08/11 6:58a Ryanchou
// [TAG]  		EIP54018
// [Category]  	New Feature
// [Description]  	Added USB S5 wake up support.
// [Files]  		amiusb.c, ehci.c, ohci.c, uhci.c, usb.c, usb.sdl, usbdef.h,
// usbsb.c xhci.c
// 
// 89    8/08/11 5:14a Ryanchou
// [TAG]  		EIP60561
// [Category]  	New Feature
// [Description]  	Add USB timing policy protocol for timing override.
// [Files]  		ehci.c, guids.c, ohci.c, uhcd.c, uhci.c usb.c, usbdef.h,
// usbhub.c, usbmass.c, UsbPolicy.h, usbport.c usbsrc.sdl
// 
// 88    7/19/11 5:16a Ryanchou
// [TAG]  		EIP64498
// [Category]  	New Feature
// [Description]  	Implement EHCI key repeat function.
// [Files]  		ehci.c, ehci.h, usb.c, usbdef.h
// 
// 87    7/15/11 6:11a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c, usb.c, usbdef.h,
// usbkbd.c, usbkbd.h, usbms.c, usbrt.cif, usbsb.c, usbsetup.c,
// usbsrc.sdl, xhci.c
// 
// 86    7/12/11 8:09a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
// 85    7/01/11 3:18a Ryanchou
// [TAG]  		EIP61385
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	USB devices can't detected.
// [RootCause]  	This is the side effect of EIP59663, the port status
// doesn't reflect connect status and connect status change.
// [Solution]  	Add 100 us delay.
// [Files]  		ehci.c, uhci.c
// 
// 84    6/21/11 10:26a Ryanchou
// [TAG]  		EIP60632
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Generic Usb Redirection caused system hung at checkpoint A2
// [RootCause]  	The timeout value is zero, and the bulk transfer never
// completed.
// [Solution]  	UEFI spec defines "If Timeout is 0, then the 
// caller must wait for the function to be completed until 
// EFI_SUCCESS or EFI_DEVICE_ERROR is returned".
// [Files]  		ehci.c
// 
// 83    6/21/11 10:00a Ryanchou
// [TAG]  		EIP62708
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Unexpected USB SMI after USB Owner Ship Change
// [RootCause]  	Unexpected USB SMI causes an expection after USB onwer
// ship change 
// executed.
// [Solution]  	Check if HC is still under BIOS control before service USB
// interrupts.
// [Files]  		ehci.c
// 
// 82    6/21/11 9:55a Ryanchou
// [TAG]  		EIP59663
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Plug USB WLAN device may causes OHCI malfunction.
// [RootCause]  	The devices have to connect to OHCI first, or it can't be
// configured.
// [Solution]  	Port routing route to EHCI after OHCI initialization.
// [Files]  		ehci.c, ohci.c
// 
// 81    5/30/11 8:41a Ryanchou
// [TAG]  		EIP61030
// [Category]  	Improvement
// [Description]  	PORTSC register should be read before write the
// register, and set the USB_PORT_STAT_DEV_CONNECT_CHANGED flag if
// bIgnoreConnectStsChng is set and connect status change bit is not set.
// [Files]  		ehci.c
// 
// 80    5/03/11 10:10a Ryanchou
// [TAG]  		EIP54283
// [Category]  	Improvement
// [Description]  	Follow XHCI spec ver 1.0 section 4.6.8 to recovery
// endpoint halt. 
// [Files]  		ehci.c, ohci.c, uhci.c, usbdef.h, usbmass.c, xhci.c
// 
// 79    5/03/11 8:54a Ryanchou
// [TAG]  		EIP58108
// [Category]  	Improvement
// [Description]  	Disable port only if this port is enabled and remove
// the delay after port disable. 
// [Files]  		ehci.c
// 
// 78    4/06/11 3:52a Ryanchou
// [TAG]  		EIP55960
// [Category]  	Improvement
// [Description]  	The Host Controller must halt within 16 micro-frames
// after software clears the Run bit.
// [Files]  		ehci.c, elib.c
// 
// 77    4/06/11 1:32a Ryanchou
// [TAG]  		EIP54782
// [Category]  	Improvement
// [Description]  	Change polling data size of HID devices to max packet
// size of interrupt endpoint.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, xhci.c
// 
// 76    3/29/11 10:47p Ryanchou
// [TAG]  		EIP55401
// [Category]  	Improvement
// [Description]  	Improve the USB 3.0 device compatibility.
// [Files]  		ehci.c, ehci.h, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c,
// xhci.c
// 
// 75    3/29/11 10:10a Ryanchou
// [TAG]  		EIP53518
// [Category]  	Improvement
// [Description]  	Added chipset xHCI chip support.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhcd.c, uhci.c, usb.c,
// usb.sdl, usbdef.h, usbport, usbsb.c, xhci.c
// 
// 74    2/17/11 8:03a Ryanchou
// [TAG]  		EIP48592
// [Category]  	Improvement
// [Description]  	Add timeout check in EHCIStartPeriodicSchedule and
// EHCIStopPeriodicSchedule to avoid the endless loop.
// [Files]  		ehci.c
// 
// 73    11/11/10 11:32p Ryanchou
// [TAG]  		EIP45578
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB 3.0 device can't be detected.
// [RootCause]  	Address Device Command fails.
// [Solution]  	Reset the device and attempt the Address Device Command
// again.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c, xhci.c
// 
// 72    10/20/10 1:02a Ryanchou
// EIP45689: Uncomment code in EHCI_GetRootHubStatus that wait 20ms for
// host controller could report accurate port status properly.
// 
// 71    9/24/10 5:38p Olegi
// EIP38221: Added the code that properly initializes
// DEV_INFO.bIntEndpoint field; interrupt endpoint polling is using this
// endpoint number.
// 
// 70    8/09/10 1:29a Ryanchou
// EIP41187: Set CERR field as 3 in a qTD, and service all interrupts
// after transfer complete.
// 
// 69    7/13/10 7:16a Ryanchou
// EIP38356: Implement shutdown USB legacy support in ACPI enable call.
// 
// 68    6/10/10 3:07a Ryanchou
// EIP38648: Enable USB Error SMI.
// 
// 67    3/11/10 9:42a Olegi
// 
// 66    3/02/10 4:51p Olegi
// Undone changes in EHCI_ControlTransfer for EIP32956.
// 
// 65    2/27/10 11:59a Olegi
// 
// 64    2/26/10 5:14p Olegi
// 
// 63    2/08/10 9:59a Olegi
// EIP33381: Implement multiple bulk endpoint in UsbIoProtocol.
// 
// 62    1/26/10 10:21a Olegi
// EIP32624: fix Change in InterruptTransfer.
// 
// 61    1/04/10 9:20a Olegi
// EIP32956: Polling rate for the keyboards has been changed from 8 ms to
// 32 ms.
// 
// 60    12/23/09 11:59a Olegi
// 
// 59    12/09/09 1:07p Davidd
// Corrected the USBkeyboard can't hotplug in DOS issue. (EIP 26477)
// 
// 58    12/09/09 12:33p Olegi
// Code cleanup.
// 
// 57    11/30/09 6:13p Olegi
// 
// 56    11/25/09 1:48p Olegi
// 
// 55    11/18/09 7:10p Olegi
// Restored EHCIResetHC call in Start function that was removed for
// EIP23479. This EIP is resolved differently.
// 
// 54    10/30/09 5:47p Olegi
// 
// 52    10/15/09 3:12p Olegi
// EIP24437: Change EHCI_ProcessInterrupt to handle the HC error bit in
// the periodic TDs.
// 
// 51    10/07/09 9:48a Olegi
// USB Hub error handling improvement. EIP#25601.
// 
// 50    9/17/09 11:13a Olegi
// Change in ProcessInterrupt:
// There may be a condition in which OS changes the base address before
// owning the semaphore and SMI may occur on USB complete or port change
// detect. This may cause SMI storm. Disabling SMI will not affect
// anything since we dont have any control over it.
// 
// 49    9/15/09 10:28a Olegi
// EIP26685: uncommented code in EHCI_Stop that disconnects all devices.
// 
// 48    9/15/09 10:21a Olegi
// Added USB_INCMPT_HID_DATA_OVERFLOW incompatibility type.
// 
// 47    8/28/09 11:49a Olegi
// EIP#25760: change the sequence of periodic schedule and async schedule
// execution.
// 
// 46    7/02/09 10:06a Olegi
// Fix for EIP#23479: while processing EHCI change ownership request, we
// will not reset the HC. This change will preserve the state of
// EHCI_CONFIGURE register (MMIO reg 60h, bit0) so the controller
// switching will not occur.
// 
// 45    6/24/09 2:35p Olegi
// Correction in EHCIInitializePeriodicSchedule(); fix for the EIP#23498.
// 
// 44    6/02/09 2:47p Olegi
// 
// 43    5/22/09 1:48p Olegi
// Bugfix in EHCI_GetRootHubStatus.
// 
// 42    5/15/09 6:16p Olegi
// Skip enabling PortPower for the ports that already have it enabled.
// Saves ~100ms per controller.
// 
// 41    3/19/09 4:56p Olegi
// 
// 40    3/09/09 8:49a Olegi
// Modified EHCIProgramLegacyRegisters, EIP#20084.
// 
// 39    2/20/09 2:30p Olegi
// Modifications in ProcessOwnerShipChangeSMI function, EIP#19525
// 
// 38    2/18/09 10:10a Olegi
// Fast unplug/insert fix,  EIP#19206.
// 
// 37    2/17/09 4:01p Olegi
// 
// 36    1/16/09 4:11p Olegi
// Added dependency on MAX_BULK_DATA in EHCI_BulkTransfer.
// 
// 35    11/06/08 1:59p Olegi
// Change in EHCI_EnumeratePorts that will avoid unnecessary delays during
// enabling the port power.
// 
// 34    10/06/08 3:33p Olegi
// EHCI change ownership testing in DOS fix (EIP#14855).
// 
// 33    9/02/08 10:28a Olegi
// EIP14855 bugfix: change ownership request is not processed properly in
// case of multiple controllers of the same type.
// 
// 32    8/08/08 2:37p Olegi
// Fix in EHCI_GetRootHubStatus that did not report connection properly in
// some cases.
// 
// 31    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 30    7/09/07 2:11p Olegi
// Changed the maximum data size of the BulkTransfer from 1kB to 64kB.
// 
// 29    4/17/07 8:24a Olegi
// Device detection algorythm update, in sync with Core8.
// 
// 28    3/20/07 12:21p Olegi
//
// 27    1/25/07 10:19a Olegi
//
// 26    12/28/06 5:27p Olegi
//
// 25    12/26/06 10:23a Olegi
//
// 24    12/22/06 4:05p Olegi
// Timeout implementation.
//
// 23    12/20/06 2:30p Olegi
//
// 22    11/21/06 5:35p Olegi
//
// 21    11/16/06 6:10p Olegi
// DebugPort support initial changes.
//
// 19    10/19/06 5:16p Andriyn
//
// 18    10/12/06 9:37p Andriyn
// Fix: unexpected plug-off hangs with endless TIMEOUTs
//
// 17    10/12/06 9:07p Andriyn
//
// 16    7/21/06 6:34p Olegi
//
// 15    7/19/06 3:53p Olegi
// Bugfix in EHCIRemoveQH routine.
//
// 14    6/09/06 10:29a Olegi
// USB_FLAG_ENABLE_BEEP_MESSAGE flag is reset while handling change of the
// controller ownership.
//
// 13    5/22/06 9:08a Olegi
// ASYNC_BELL_SUPPORT modifications
//
// 12    5/16/06 11:23a Olegi
//
// 11    5/16/06 11:19a Olegi
// Removed DisconnectDevice call from EHCI_Stop
//
// 10    4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 9     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 8     3/16/06 2:34p Olegi
//
// 7     3/06/06 6:25p Olegi
//
// 6     1/11/06 11:52a Olegi
//
// 5     11/29/05 12:33p Andriyn
//
// 4     6/03/05 6:09p Olegi
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
//  Name:           Ehci.h
//
//  Description:    AMI USB EHCI support
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

UINT8   EHCI_Start (HC_STRUC*);
UINT8   EHCI_Stop (HC_STRUC*);
UINT8   EHCI_EnumeratePorts (HC_STRUC*);
UINT8   EHCI_DisableInterrupts (HC_STRUC*);
UINT8   EHCI_EnableInterrupts (HC_STRUC*);
UINT8   EHCI_ProcessInterrupt(HC_STRUC*);
UINT8   EHCI_GetRootHubStatus (HC_STRUC*,UINT8, BOOLEAN);
UINT8   EHCI_DisableRootHub (HC_STRUC*,UINT8);
UINT8   EHCI_EnableRootHub (HC_STRUC*,UINT8);
UINT16  EHCI_ControlTransfer (HC_STRUC*,DEV_INFO*,UINT16,UINT16,UINT16,UINT8*,UINT16);
UINT32  EHCI_BulkTransfer (HC_STRUC*,DEV_INFO*,UINT8,UINT8*,UINT32);
UINT16  EHCI_InterruptTransfer (HC_STRUC*, DEV_INFO*, UINT8, UINT16, UINT8*, UINT16);
UINT8   EHCI_DeactivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   EHCI_ActivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   EHCI_DisableKeyRepeat (HC_STRUC*);
UINT8   EHCI_EnableKeyRepeat (HC_STRUC*);
UINT8   EHCI_ResetRootHub (HC_STRUC*,UINT8);
UINT8   EHCI_GlobalSuspend (HC_STRUC*);	//(EIP54018+)

UINT8   EHCIResetHC(HC_STRUC*);
UINT8   EHCIInitializePeriodicSchedule(HC_STRUC*, UINT32);
UINT8   EHCIProgramLegacyRegisters(HC_STRUC*, UINT8);
UINT8   EHCIStartAsyncSchedule(HC_STRUC*);
UINT8   EHCIStopAsyncSchedule(HC_STRUC*);
UINT8   EHCIStartPeriodicSchedule(HC_STRUC*);
UINT8   EHCIStopPeriodicSchedule(HC_STRUC*);
UINT8   EHCIProcessQH(HC_STRUC*, EHCI_QH*);
VOID    EHCIProcessPeriodicList(HC_STRUC*);
VOID    EHCIInitializeQueueHead (EHCI_QH*);
VOID    EHCISetQTDBufferPointers(EHCI_QTD*, UINT8*, UINT32);
UINT16  EHCIWaitForTransferComplete(HC_STRUC*, EHCI_QH*,DEV_INFO* );
UINT8   EhciAddPeriodicQh(HC_STRUC*,EHCI_QH*);
UINT8   EhciRemovePeriodicQh(HC_STRUC*,EHCI_QH*);
VOID    ProcessOwnerShipChangeSMI(HC_STRUC*);
VOID    ProcessSmiChangeToEHCD(HC_STRUC*);
VOID    ProcessSmiChangeToBIOS(HC_STRUC*);
UINT8   EHCIGetLegacySupportOffset(HC_STRUC*, UINT16);
VOID    EHCIRemoveQHFromAsyncList(HC_STRUC*, EHCI_QH*);
UINT8	EhciPollingTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8	EhciRepeatTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);

UINT32  ReadPCIConfig(UINT16, UINT8);
VOID    WordWritePCIConfig(UINT16, UINT8, UINT16);
VOID    DwordWritePCIConfig(UINT16, UINT8, UINT32);

UINT32  DwordReadMem(UINT32, UINT16);
VOID    DwordWriteMem(UINT32, UINT16, UINT32);
VOID    DwordResetMem(UINT32, UINT16, UINT32);
VOID    DwordSetMem(UINT32, UINT16, UINT32);

UINT32	EhciReadPciReg(HC_STRUC*, UINT32);
VOID	EhciWritePciReg(HC_STRUC*, UINT32, UINT32);
UINT32	EhciReadHcMem(HC_STRUC*, UINT32);
VOID	EhciWriteHcMem(HC_STRUC*, UINT32, UINT32);
UINT32	EhciReadOpReg(HC_STRUC*, UINT32);
VOID	EhciWriteOpReg(HC_STRUC*, UINT32, UINT32);
VOID	EhciClearOpReg(HC_STRUC*, UINT32, UINT32);
VOID	EhciSetOpReg(HC_STRUC*, UINT32, UINT32);
UINT32	EhciReadDebugReg(HC_STRUC*, UINT8, UINT32);
VOID*	EhciMemAlloc(HC_STRUC*, UINT16);
VOID	EhciMemFree(HC_STRUC*, VOID*, UINT16);
UINT8	EhciDmaMap(HC_STRUC*, UINT8, UINT8*, UINT32, UINT8**, VOID**);
UINT8	EhciDmaUnmap(HC_STRUC*, VOID*);
BOOLEAN EhciIsHalted(HC_STRUC*);
UINT16  EhciTranslateInterval(UINT8, UINT8);

UINT8   USBCheckPortChange (HC_STRUC*, UINT8, UINT8);
UINT8   USBLogError(UINT16);
UINT8	UsbGetDataToggle(DEV_INFO*,UINT8);
VOID	UsbUpdateDataToggle(DEV_INFO*, UINT8, UINT8);

VOID    USB_InitFrameList (HC_STRUC*, UINT32);
VOID    FixedDelay(UINTN);

VOID*   USB_MemAlloc (UINT16);
UINT8   USB_MemFree (VOID _FAR_ *, UINT16);
UINT8   USB_DisconnectDevice (HC_STRUC*, UINT8, UINT8);
DEV_INFO*   USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);
UINT8   USB_StopDevice (HC_STRUC*,  UINT8, UINT8);
UINT8	USB_InstallCallBackFunction (CALLBACK_FUNC);
VOID	USBKeyRepeat(HC_STRUC*, UINT8);

#if USB_DEV_KBD
VOID    USBKBDPeriodicInterruptHandler(HC_STRUC*);
#endif


extern  USB_GLOBAL_DATA     *gUsbData;
extern  BOOLEAN  gCheckUsbApiParameter;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   EHCI_FillHCDEntries (HCD_HEADER *fpHCDHeader)
//
// Description: This function fills the host controller driver
//              routine pointers
//
// Parameters:  fpHCDHeader     Ptr to the host controller header structure
//
// Output:      Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_FillHCDEntries (HCD_HEADER *fpHCDHeader)
{
    fpHCDHeader->pfnHCDStart                = EHCI_Start;
    fpHCDHeader->pfnHCDStop                 = EHCI_Stop;
    fpHCDHeader->pfnHCDEnumeratePorts       = EHCI_EnumeratePorts;
    fpHCDHeader->pfnHCDDisableInterrupts    = EHCI_DisableInterrupts;
    fpHCDHeader->pfnHCDEnableInterrupts     = EHCI_EnableInterrupts;
    fpHCDHeader->pfnHCDProcessInterrupt     = EHCI_ProcessInterrupt;
    fpHCDHeader->pfnHCDGetRootHubStatus     = EHCI_GetRootHubStatus;
    fpHCDHeader->pfnHCDDisableRootHub       = EHCI_DisableRootHub;
    fpHCDHeader->pfnHCDEnableRootHub        = EHCI_EnableRootHub;
    fpHCDHeader->pfnHCDControlTransfer      = EHCI_ControlTransfer;
    fpHCDHeader->pfnHCDBulkTransfer         = EHCI_BulkTransfer;
    fpHCDHeader->pfnHCDInterruptTransfer    = EHCI_InterruptTransfer;
    fpHCDHeader->pfnHCDDeactivatePolling    = EHCI_DeactivatePolling;
    fpHCDHeader->pfnHCDActivatePolling      = EHCI_ActivatePolling;
    fpHCDHeader->pfnHCDDisableKeyRepeat     = EHCI_DisableKeyRepeat;
    fpHCDHeader->pfnHCDEnableKeyRepeat      = EHCI_EnableKeyRepeat;
    fpHCDHeader->pfnHCDEnableEndpoints      = USB_EnableEndpointsDummy;
    fpHCDHeader->pfnHCDInitDeviceData       = USB_InitDeviceDataDummy;
    fpHCDHeader->pfnHCDDeinitDeviceData     = USB_DeinitDeviceDataDummy;
	fpHCDHeader->pfnHCDResetRootHub         = EHCI_ResetRootHub;
	fpHCDHeader->pfnHCDClearEndpointState	= 0;	//(EIP54283+)
	fpHCDHeader->pfnHCDGlobalSuspend        = EHCI_GlobalSuspend;	//(EIP54018+)

    USB_InstallCallBackFunction(EhciRepeatTDCallback);
    USB_InstallCallBackFunction(EhciPollingTDCallback);

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   EhciIsolateDebugPort
//
// Description: This routine locates EHCI debug port and determines whether
//              or not the debug port is initialized and being used by other
//              agents. If so, the global flag will be set to instruct the
//              EHCI runtime routines about debug port presence and prevent
//              any unwanted reset/reconfiguration of this port.
//
// Parameters:  fpHCStruc   Ptr to the host controller structure
//
// Output:      fpHCStruc->DebugPort is updated if Debug Port is active on
//              this controller; otherwise it will remain 0.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID EhciIsolateDebugPort(HC_STRUC *fpHCStruc)
{
    UINT32 HcSParams = fpHCStruc->dHCSParams;   // Host Controller Structural Parameters
    UINT8  DebugPortNo;
    UINT32 NextCap;
	UINT8  DebugPortBarIndex;
    UINT16 DebugPortOffset;

    //
    // Locate debug port by looking at the PCI capabilities
    //
    DebugPortNo = (UINT8)((HcSParams & (EHCI_DEBUG_N)) >> 20);

    //ASSERT(DebugPortNo); // No debug port implemented
    fpHCStruc->DebugPort = 0;
    if (DebugPortNo == 0) return;

    ASSERT(DebugPortNo <= (UINT8)(HcSParams & (EHCI_N_PORTS)));    // Invalid debug port number
    if (DebugPortNo > (UINT8)(HcSParams & (EHCI_N_PORTS))) return;

    //
    // Check whether device implements Capability list that starts at register 0x34
    //
    if (!(EhciReadPciReg(fpHCStruc, 4) & BIT20)) {
        //ASSERT(FALSE);  // Capabilities list is not implemented
        return;
    }

    //
    // Find the beginning of Debug Port registers block
    //
    for (NextCap = EhciReadPciReg(fpHCStruc, 0x34);
            (UINT8)NextCap > 0;
    )
    {
        NextCap = EhciReadPciReg(fpHCStruc, (UINT8)NextCap);
        if ((UINT8)NextCap == 0xA) break;   // Debug port capability found
        NextCap >>= 8;
    }
    if ((UINT8)NextCap == 0) {
        //ASSERT(FALSE);  // Debug capabilities not found
        return;
    }
	DebugPortBarIndex = (UINT8)((NextCap >> 29) - 1);
    DebugPortOffset = (UINT16)((NextCap >> 16) & 0x1FFF);
    ASSERT(DebugPortBarIndex >= 0 && DebugPortBarIndex <= 5); // Wrong BAR
    if (!(DebugPortBarIndex >= 0 && DebugPortBarIndex <= 5)) return;
    //
    // See whether Debug Port is acquired by other software
    //
	if (EhciReadDebugReg(fpHCStruc, DebugPortBarIndex, DebugPortOffset) & BIT28) {
        fpHCStruc->DebugPort = DebugPortNo;
        USB_DEBUG(DEBUG_LEVEL_3, "EHCI HC Debug Port #%d enabled.\n", DebugPortNo);
	}
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   EHCI_Start
//
// Description: This API function is called to start a EHCI host controller.
//              The input to the routine is the pointer to the HC structure
//              that defines this host controller
//
// Parameters:  fpHCStruc   Ptr to the host controller structure
//
// Output:      Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_Start (HC_STRUC* fpHCStruc)
{
    UINT32  dTemp;
//#if EHCI_ASYNC_BELL_SUPPORT
//    EHCI_QH *fpQHAsyncXfer;
//#endif
	EHCI_QH     *fpQHRepeat = NULL;
	EHCI_QTD    *fpqTDRepeat = NULL;
	UINT32	i;							//(EIP55960+)
	BOOLEAN	SetPortPower = FALSE;
    UINT16  PortReg;
    EHCI_DESC_PTRS      *DescPtr = NULL;
    EFI_STATUS  EfiStatus = EFI_SUCCESS;

/*
USB_DEBUG(DEBUG_LEVEL_3, "Enabling MEM/BM for EHCI HC %02X\n", fpHCStruc->wBusDevFuncNum);

    //
    // Enable IO access and Bus Mastering
    //
    WordWritePCIConfig((UINT16)fpHCStruc->wBusDevFuncNum, 4, BIT1 + BIT2);
*/
    //
    // Get memory base address of the HC and store it in the HCStruc
    //
    fpHCStruc->BaseAddress = EhciReadPciReg(fpHCStruc, USB_MEM_BASE_ADDRESS) & 0xFFFFFFF0;

    USB_DEBUG(DEBUG_LEVEL_3, "EHCI HC Mem Addr: %X\n", fpHCStruc->BaseAddress);
    
#if USB_RUNTIME_DRIVER_IN_SMM
    EfiStatus = AmiValidateMmioBuffer((VOID*)fpHCStruc->BaseAddress, fpHCStruc->BaseAddressSize);
    if (EFI_ERROR(EfiStatus)) {
        USB_DEBUG(3, "Usb Mmio address is invalid, it is in SMRAM\n");
        return USB_ERROR;
    }
#endif
    //
    // Get the number of ports supported by the host controller (Offset 4)
    // and store it in HCStruc
    //
    fpHCStruc->dHCSParams = EhciReadHcMem(fpHCStruc, EHCI_HCSPARAMS);
    fpHCStruc->bNumPorts = (UINT8)(fpHCStruc->dHCSParams & EHCI_N_PORTS);
    USB_DEBUG(DEBUG_LEVEL_3, "EHCI HC Number of ports: %d\n", fpHCStruc->bNumPorts);

    EhciIsolateDebugPort(fpHCStruc);	//(EIP102781)
 
    //
    // Read the Capability Registers Length to find the Offset address for the
    // beginning of the operational registers
    //
    fpHCStruc->bOpRegOffset = (UINT8)EhciReadHcMem(fpHCStruc, EHCI_VERCAPLENGTH);
    USB_DEBUG(DEBUG_LEVEL_3, "EHCI HC Operational Registers Offset: %d\n", fpHCStruc->bOpRegOffset);

    //
    // Read and store the HCCPARAMS value
    //
    fpHCStruc->dHCCParams = EhciReadHcMem(fpHCStruc, EHCI_HCCPARAMS);
    //USB_DEBUG(DEBUG_LEVEL_3, "EHCI HC HCPARAMS: %x\n", gUsbData->dHCCParams);

    //
    // Get PCI register offset for the legacy support in EHCI controller
    // and store it in HC_STRUC
    //
    fpHCStruc->bExtCapPtr = EHCIGetLegacySupportOffset(
                        fpHCStruc,
                        fpHCStruc->wBusDevFuncNum);

#if EHCI_64BIT_DATA_STRUCTURE == 0
    //
    // 64bit data structures are not enabled. So check whether this host controller
    // needs 64bit data structure or not.
    //
    if (fpHCStruc->dHCCParams & EHCI_64BIT_CAP)
    {
        //
        // Engineer has to enable the 64bit capability. Post an error message
        //
        USBLogError(ERRUSB_EHCI_64BIT_DATA_STRUC);
        ASSERT(FALSE);

        //
        // Connect all ports to the classic host controller
        //
        EhciClearOpReg(fpHCStruc, EHCI_CONFIGFLAG, BIT0);
        return  USB_ERROR;
    }
#endif

#if	HIDE_USB_HISPEED_SUPPORT_SETUP_QUESTION == 0
	if ((gUsbData->UsbHiSpeedSupport == 0) && ((fpHCStruc->dHCSParams & EHCI_N_CC) != 0)) {
		EhciClearOpReg(fpHCStruc, EHCI_CONFIGFLAG, BIT0);
		return  USB_ERROR;
	}
#endif

//----------------------------------------------------------------------------
// Note: after this point any access to the operational registers is through
// the macros EHCI_DWORD_READ_MEM and EHCI_DWORD_WRITE_MEM; access to the
// capability registers is through the macro USBPORT_DWORD_READ_MEM and
// there is no macro to write to the registers
//----------------------------------------------------------------------------
										//(EIP55960)>
	if ((EhciReadOpReg(fpHCStruc, EHCI_USBSTS) & EHCI_HCHALTED) == 0) {
	    // Turn HC off and wait for the Halted bit to get set
	    EhciClearOpReg(fpHCStruc, EHCI_USBCMD, EHCI_RUNSTOP);

		// The Host Controller must halt within 16 micro-frames after 
		// software clears the Run bit. 
		for (i = 0; i < 16; i++) {
			if (EhciReadOpReg(fpHCStruc, EHCI_USBSTS) & EHCI_HCHALTED) {
				break;
			}
            FixedDelay(125);	  // 125 us delay
		}
		//while ((DwordReadMem(dMemAddr, EHCI_USBSTS) & EHCI_HCHALTED) == 0) {};
	}
										//<(EIP55960)
// /* EIP#23479
    //
    // Reset the host controller (HC must be halted)
    //
    if (EHCIResetHC(fpHCStruc) == USB_ERROR)
    {
        return  USB_ERROR;  // HC reset error, error log is updated
    }
//*/
    //
    // Get the frame list size from the EHCI command register
    //
    dTemp = EhciReadOpReg(fpHCStruc, EHCI_USBCMD);
    dTemp = (dTemp & (BIT2 + BIT3)) >> 2;

    //
    // Calculate number of elements in the asynchronous list
    // and store the value in the HCStruc
    //
    switch (dTemp)
    {
        case 0: fpHCStruc->wAsyncListSize   = 1024;
                break;
        case 1: fpHCStruc->wAsyncListSize   = 512;
                break;
        case 2: fpHCStruc->wAsyncListSize   = 256;
                break;
        case 3: return  USB_ERROR;

    }

    USB_DEBUG(DEBUG_LEVEL_3, "EHCI AsyncListSize: %d\n", fpHCStruc->wAsyncListSize);

    //
    // Set the max bulk data size
    //
    fpHCStruc->dMaxBulkDataSize = MAX_EHCI_DATA_SIZE;

    //
    // Initialize the frame list pointers
    //
    USB_InitFrameList (fpHCStruc, EHCI_TERMINATE);

    //
    // Write the base address of the Periodic Frame List to the PERIODIC BASE
    // register
    //
    EhciWriteOpReg(fpHCStruc, EHCI_PERIODICLISTBASE, (UINT32)(UINTN)fpHCStruc->fpFrameList);

    //
    // Initialize the periodic schedule
    //
    EHCIInitializePeriodicSchedule(fpHCStruc, (UINT32)fpHCStruc->BaseAddress);
/*
#if EHCI_ASYNC_BELL_SUPPORT
    //
    // Allocate and initialize an queue head for Async transfer
    // Set the QHDummy as Async list head
    //
    fpQHAsyncXfer = EhciMemAlloc (fpHCStruc, GET_MEM_BLK_COUNT_STRUC(EHCI_QH));

    if (!fpQHAsyncXfer) {
        return  USB_ERROR;
    }

    gUsbData->fpQHAsyncXfer        = fpQHAsyncXfer;

    fpQHAsyncXfer->dEndPntCap       = QH_ONE_XFER;
    fpQHAsyncXfer->fpFirstqTD       = 0;
    fpQHAsyncXfer->dAltNextqTDPtr   = EHCI_TERMINATE;
    fpQHAsyncXfer->dNextqTDPtr      = EHCI_TERMINATE;

    //
    // Assume as a high speed device
    //
    dTemp = QH_HIGH_SPEED;  // 10b - High speed

    //
    // Use data toggle from qTD and this QH is the head of the queue
    //
    dTemp |= (QH_USE_QTD_DT | QH_HEAD_OF_LIST | DUMMY_DEVICE_ADDR); // Endpoint is 0

    //
    // dTemp[6:0] = Dev. Addr, dTemp[7] = I bit(0) & dTemp[11:8] = Endpoint (0)
    //
    fpQHAsyncXfer->dEndPntCharac    = dTemp;

    //
    // Set the ASYNCLISTADDR register to point to the QHDummy
    //
    EhciWriteOpReg(fpHCStruc, EHCI_ASYNCLISTADDR, (UINT32)(UINTN)fpQHAsyncXfer);

    //
    // Set next QH pointer to itself (circular link)
    //
    fpQHAsyncXfer->dLinkPointer = (UINT32)(UINTN)fpQHAsyncXfer | EHCI_QUEUE_HEAD;
    fpQHAsyncXfer->bActive = TRUE;
#endif  //  EHCI_ASYNC_BELL_SUPPORT
*/

#if USB_RUNTIME_DRIVER_IN_SMM
	// Check whether no companion host controllers
	if (!(fpHCStruc->dHCFlag & HC_STATE_EXTERNAL) &&
		(fpHCStruc->dHCSParams & EHCI_N_CC) == 0) {
		//
		// Allocate a QH/qTD for QHRepeat/qTDRepeat
		//
		fpQHRepeat = EhciMemAlloc(fpHCStruc,
						GET_MEM_BLK_COUNT(sizeof(EHCI_QH)+sizeof(EHCI_QTD)));

		if (!fpQHRepeat) {
			return	USB_ERROR;	// Memory allocation error
		}
        DescPtr = fpHCStruc->stDescPtrs.fpEHCIDescPtrs;
		DescPtr->fpQHRepeat = fpQHRepeat;
		fpqTDRepeat = (EHCI_QTD*)((UINT32)fpQHRepeat + sizeof(EHCI_QH));
		DescPtr->fpqTDRepeat = fpqTDRepeat;
//
// Setup QHRepeat and qTDRepeat.  It will run a interrupt transaction to a
// nonexistant dummy device.  This will have the effect of generating
// a periodic interrupt used to generate keyboard repeat.  This QH/qTD
// is normally inactive,  and is only activated when a key is pressed.
//
		//
		// Set the first qTD pointer
		//
		fpQHRepeat->fpFirstqTD = fpqTDRepeat;

		//fpQHRepeat->fpDevInfoPtr = (UINT8*)fpDevInfo;
		fpQHRepeat->dNextqTDPtr = (UINT32)fpqTDRepeat;

		//
		// Intialize the queue head
		//
		fpQHRepeat->dAltNextqTDPtr = EHCI_TERMINATE;
		fpQHRepeat->dLinkPointer = EHCI_TERMINATE;

		//
		// Set max packet size, address, endpoint and high speed
		// Update the AH's endpoint characteristcs field with the data formed
		//
		fpQHRepeat->dEndPntCharac |= ((0x40 << 16) | DUMMY_DEVICE_ADDR |
									QH_HIGH_SPEED);

		//
		// Set a bit in interrupt mask
		//
		fpQHRepeat->dEndPntCap	= (BIT0 | QH_ONE_XFER);
        fpQHRepeat->Interval = REPEAT_INTERVAL;

//
// Fill the repeat qTD with relevant information
// The token field will be set so
//	 Direction PID = QTD_IN_TOKEN,
//	 Size = size of the data,
//	 Data Toggle = QTD_DATA0_TOGGLE,
//	 Error Count = QTD_NO_ERRORS,
//	 Status code = QTD_ACTIVE
// The buffer pointers field will point to the fpBuffer buffer
//	 which was before initialized to contain a DeviceRequest struc.
// The dNextqTDPtr field will point to the qTDControlSetup
// The dAltNextqTDPtr field will be set to EHCI_TERMINATE
//
		fpQHRepeat->dTokenReload = ((UINT32)8 << 16) | QTD_IN_TOKEN | QTD_ONE_ERROR;
		fpqTDRepeat->dToken = ((UINT32)8 << 16) | QTD_IN_TOKEN | QTD_ONE_ERROR;

		EHCISetQTDBufferPointers(fpqTDRepeat,
			&fpQHRepeat->aDataBuffer[0], 8);

		//
		// Update next & alternate next qTD pointers
		//
		fpqTDRepeat->dNextqTDPtr = EHCI_TERMINATE;
		fpqTDRepeat->dAltNextqTDPtr = EHCI_TERMINATE;

		//
		// Schedule the QHRepeat to 8ms schedule
		//
        EhciAddPeriodicQh(fpHCStruc,fpQHRepeat);

		fpQHRepeat->bCallBackIndex = USB_InstallCallBackFunction(EhciRepeatTDCallback);
		fpQHRepeat->bActive = FALSE;

		USBKeyRepeat(fpHCStruc, 0);
	}
#endif

    //
    // Clear status register - all R/WC bits
    //
    EhciWriteOpReg(fpHCStruc, EHCI_USBSTS,
            EHCI_USB_INTERRUPT |        // Interrupt
            EHCI_USB_ERROR_INTERRUPT |  // Error interrupt
            EHCI_PORT_CHANGE_DETECT |   // Port Change Detect
            EHCI_FRAME_LIST_ROLLOVER |  // Frame List Rollover
            EHCI_HOST_SYSTEM_ERROR |    // Host System Error
            EHCI_INT_ASYNC_ADVANCE);    // Interrupt on Async Advance
    //
    // Program the HC BIOS owned bit and return the legacy support register offset
    //
    if (fpHCStruc->bExtCapPtr) {
		EHCIProgramLegacyRegisters(fpHCStruc, 1);  // Set HC BIOS owned semaphore

        //
        // Enable USB SMI, SMI on port change and SMI on ownership change
        //
        dTemp = EHCI_SMI + EHCI_PORT_CHANGE_SMI + EHCI_OWNERSHIP_CHANGE_SMI;

		EhciWritePciReg(fpHCStruc, fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG, dTemp);
    }

    //
    // Turn HC on
    //
    EhciSetOpReg(fpHCStruc, EHCI_USBCMD, \
        (EHCI_RUNSTOP | EHCI_PER_SCHED_ENABLE));

    // Wait for halt bit get cleared
    for (i = 0; i < 20; i++) {
        if (!(EhciReadOpReg(fpHCStruc, EHCI_USBSTS) & EHCI_HCHALTED)) {
            break;
        }
        FixedDelay(100);	  // 100 us delay
    }

    //
    // If the port has the power switch then enable the port. Otherwise 
    // Power for the port is already present. So don't need to enable the power.
    // ( Refer EHCI Spec 2.2.3 HCSPARAMS Structural Parameters Bit 4 (PPC) )
    if (fpHCStruc->dHCSParams & EHCI_PPC) {
        //
        // Enable port power
        //
        for (i = 1, PortReg = EHCI_PORTSC; i <= fpHCStruc->bNumPorts; i++, PortReg += 4) {
            //
            // Skip enabling DebugPort
            //
            if (fpHCStruc->DebugPort && fpHCStruc->DebugPort == i) continue;
    
            if (EhciReadOpReg(fpHCStruc, PortReg) & EHCI_PORTPOWER) {
                continue;
            }
            
            EhciSetOpReg(fpHCStruc, PortReg, EHCI_PORTPOWER);
            SetPortPower = TRUE;
        }
        //
        // Delay till the ports power is stabilised
        //
        if (SetPortPower) {
            FixedDelay(20 * 1000);        // 20 msec delay
        }
    }

    // Set HC flag as running
    fpHCStruc->dHCFlag |= HC_STATE_RUNNING;

    // Set USB_FLAG_DRIVER_STARTED flag when HC is running.
    if (!(gUsbData->dUSBStateFlag & USB_FLAG_DRIVER_STARTED)) {
        gUsbData->dUSBStateFlag |= USB_FLAG_DRIVER_STARTED;
    }

    //
    // Disconnect all ports from companion HC (if any) and route them to EHCI
    //
    EhciSetOpReg(fpHCStruc, EHCI_CONFIGFLAG, BIT0);		//(EIP59663-) //(EIP80307+)

    if (fpHCStruc->dHCFlag & HC_STATE_CONTROLLER_WITH_RMH) {
        // Wait for port change detect bit set
        for (i = 0; i < 50; i++) {
            if (EhciReadOpReg(fpHCStruc, EHCI_USBSTS) & EHCI_PORT_CHANGE_DETECT) {
                break;
            }
            FixedDelay(100);    // 100 us delay
        }
    } else {
        FixedDelay(100);    // 100 us delay
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
//----------------------------------------------------------------------------
//
// Procedure:   EHCIGetLegacySupportOffset
//
// Description: This function returns the PCI register offset for the legacy
//              support in EHCI controller
//
// Input:       fpHCStruc   - HCStruc pointer
//              wPciAddr    - PCI address of the EHCI host controller
//
// Output:      0   If the feature is not present
//              <>0 Legacy support capability offset
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIGetLegacySupportOffset(
    HC_STRUC* fpHCStruc,
    UINT16 wPciAddr)
{
    UINT8   bData = 0;
    UINT32  dData = 0;

#if USB_RUNTIME_DRIVER_IN_SMM

    if (fpHCStruc->dHCFlag & HC_STATE_EXTERNAL) {
        return 0;
    }

    //
    // Get EHCI Extended Capabilities Pointer
    //
    bData = (UINT8)((fpHCStruc->dHCCParams >> 8) & 0xFF);

    if (!bData)
    {
        return 0;   // No extended capabilities are implemented.
    }

    dData = EhciReadPciReg(fpHCStruc, bData);
    if (!((UINT8)dData & 1)) {
        return 0;
    }
#endif
    return bData;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIProgramLegacyRegisters
//
// Description: This function programs the EHCI legacy registers as per the
//              input. Also this routine returns the PCI register offset
//              for the legacy support in EHCI controller
//
// Input:   fpHCStruc   HCStruc pointer
//          bSetReset:
//              0   Reset HC BIOS owned bit
//              1   Set HC BIOS owned bit
//
// Output:  0   If the feature is not present
//          <>0 Legacy support capability offset
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIProgramLegacyRegisters(
    HC_STRUC* fpHCStruc,
    UINT8 bSetReset)
{
    UINT32  dTemp;

    //
    // Check whether EHCI extended capabilities  pointer is present
    //
    if (!fpHCStruc->bExtCapPtr)
    {
        return  0;  // No extended capabilities are implemented.
    }

    //
    // Program 'HC BIOS owned semaphore bit'
    //
    dTemp = EhciReadPciReg(fpHCStruc, fpHCStruc->bExtCapPtr);
    dTemp &= ~BIT16;

    if (bSetReset)
    {
        dTemp |= BIT16;
    }

                                        // (USB_S4_RESUME_ISSUE, EIP#20084)>
    if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI)
     dTemp &= ~BIT24;
                                        // <(USB_S4_RESUME_ISSUE, EIP#20084)

    EhciWritePciReg(fpHCStruc, fpHCStruc->bExtCapPtr, dTemp);

    //
    // Reset all enable bits and clear the status
    //
    dTemp = 0xE0000000 | EHCI_OWNERSHIP_CHANGE_SMI;

    EhciWritePciReg(fpHCStruc,
        fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG,
        dTemp);

    return  fpHCStruc->bExtCapPtr;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ClearEECPstatus
//
// Description: This procedure clear EHCI legacy support status.
//
// Input:   fpHCStruc   - HCStruc pointer
//          wSTatus     - Legacy status to clear
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ClearEECPstatus(
    HC_STRUC* fpHCStruc,
    UINT16 wStatus)
{
    UINT32  dTemp;

    if (!fpHCStruc->bExtCapPtr)
    {
        return; // No extended capabilities are implemented.
    }

    //
    // Read control and status register
    //
    dTemp = EhciReadPciReg(fpHCStruc,
                fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG);

    //
    // Keep enable bits and set clear status bit
    //
    dTemp = (dTemp & 0xFFFF) | ((UINT32)wStatus << 16);
    EhciWritePciReg(
        fpHCStruc,
        fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG,
        dTemp);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetEhciUSBLEGSUP
//
// Description: This routine return USBLEGSUP register content. It could be
//               used to check EHCI semaphore owened by BIOS or OS.
//
// Input:   fpHCStruc   HCStruc pointer
//
// Output:  UINT32  Legacy support extended capability register content.
//                  -1 if no extended capabilities are implemented.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
GetEhciUSBLEGSUP(HC_STRUC* fpHCStruc)
{
    UINT32  dTemp;

    //
    // Check whether EHCI extended capabilities  pointer is present
    //
    if (!fpHCStruc->bExtCapPtr)
    {
        return 0xFFFFFFFF;  // No extended capabilities are implemented.
    }

    //
    // Read Legacy support register
    //
    dTemp = EhciReadPciReg(
                fpHCStruc,
                fpHCStruc->bExtCapPtr);

    return dTemp;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCI_EnumeratePorts
//
// Description: This function enumerates the HC ports for devices
//
// Input:       fpHCStruc   Host controller's HCStruc structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_EnumeratePorts(HC_STRUC* fpHCStruc)
{
    UINT16  wPortCtl    = EHCI_PORTSC;  // Port Status and Control Register (44h)
    UINT8   bHCNumber;
    UINT8   bPortNum;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

	if (EhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}

    bHCNumber = (UINT8)(fpHCStruc->bHCNumber | BIT7);


    //
    // Enable port power so that new devices can be detected.
    //
    // Check whether enumeration flag is set by us or by somebody else by checking
    // local enum flag.
    //
    if (gUsbData->bEnumFlag == FALSE)
    {
        gUsbData->bIgnoreConnectStsChng    = TRUE;
        gUsbData->bEnumFlag                = TRUE;
                                        //(EIP122174+)>
        do {
            //
            // Clear the EHCI_PCD bit of the interrupt status register EHCI_USBSTS
            //
            EhciWriteOpReg(fpHCStruc, EHCI_USBSTS, EHCI_PORT_CHANGE_DETECT);

            //
            // Check the root hub ports to see if a device is connected.  If so, then
            // call USBCheckPortChange to handle the attachment of a new device.
            //
            for ( bPortNum = 1; bPortNum <= fpHCStruc->bNumPorts; bPortNum++) {
                //
                // Skip DebugPort enumeration
                //
                if (fpHCStruc->DebugPort && fpHCStruc->DebugPort==bPortNum) continue;

                //
                // Process device connect/disconnect
                //
                USBCheckPortChange(fpHCStruc, bHCNumber, bPortNum);
            }
        } while ((EhciReadOpReg(fpHCStruc, EHCI_USBSTS) & EHCI_PORT_CHANGE_DETECT));
                                        //<(EIP122174+)
        gUsbData->bIgnoreConnectStsChng = FALSE;

        //
        // Reset enumeration flag and enable hub enumeration
        //
        gUsbData->bEnumFlag = FALSE;
    }

    //
    // Enable appropriate interrupts
    //
    EhciWriteOpReg(fpHCStruc, EHCI_USBINTR, EHCI_USBINT_EN | EHCI_PCDINT_EN);
    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCICheckHCStatus
//
// Description: This function checks whether the host controller is still
//              under BIOS
//
// Input:       fpHCStruc   - Host controller's HCStruc structure
//
// Output:      USB_SUCCESS - If the control is with the BIOS
//              USB_ERROR   - If the control is not with the BIOS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCICheckHCStatus(
    HC_STRUC* HcStruc
)
{
    UINT32  Cmd;
    UINT32  Sts;

    Cmd = EhciReadOpReg(HcStruc, EHCI_USBCMD);
    Sts = EhciReadOpReg(HcStruc, EHCI_USBSTS);

    // Don't read Periodic Frame List Base Address Register if the controller 
    // doesn't support periodic schedule.
    if (Cmd & EHCI_PER_SCHED_ENABLE) {
        if (!(Sts & EHCI_PER_SCHED_STATUS)) {
            return USB_SUCCESS;
        }
    }
    //
    // Check whether the controller is still under BIOS control
    // Read the base address of the Periodic Frame List to the PERIODIC BASE
    // register and compare with stored value
    //
    if ((UINTN)HcStruc->fpFrameList == 
		(EhciReadOpReg(HcStruc, EHCI_PERIODICLISTBASE) & 0xFFFFF000))
    {
        return  USB_SUCCESS;    // Control is with BIOS
    }
    return  USB_ERROR;  // HC is controlled by someone else
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIStop
//
// Description: This function stops the EHCI controller.
//
// Input:       fpHCStruc   Host controller's HCStruc structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_Stop (HC_STRUC* fpHCStruc)
{
    UINT8   bPortNum;					//(EIP26685+)
    UINT8   Status;
	UINT8	i;							//(EIP55960+)
    EHCI_DESC_PTRS  *DescPtr;
    EFI_STATUS  EfiStatus;
    UINT8       *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }


    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    DescPtr = fpHCStruc->stDescPtrs.fpEHCIDescPtrs;
    
#if USB_RUNTIME_DRIVER_IN_SMM
    if (((UINT8*)DescPtr < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtr + sizeof(EHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }
#endif
    //
    // Check whether the control is with BIOS or not
    //
    if (EHCICheckHCStatus(fpHCStruc) == USB_SUCCESS)    // Controlled by BIOS
    {
#if PCH_EHCI_OWNERSHIP_CHANGE_MECHANISM
		if (fpHCStruc->dHCFlag & HC_STATE_OWNERSHIP_CHANGE_IN_PROGRESS) {
			UINT16  PortReg;
			UINT32	PortSts;
			UINT32	Data32;

			// Disconnect all the devices connected to its ports
			for (bPortNum = 1; bPortNum <= fpHCStruc->bNumPorts; bPortNum++) {
				USB_StopDevice(fpHCStruc, (UINT8)(fpHCStruc->bHCNumber | BIT7), bPortNum);
			}
	
			// Stop the asynchronous schedule
			EHCIStopAsyncSchedule(fpHCStruc);

			// Stop the periodic schedule
			EHCIStopPeriodicSchedule(fpHCStruc);
	
			for (bPortNum = 1; bPortNum <= fpHCStruc->bNumPorts; bPortNum++) {
				PortReg = (UINT16)((bPortNum-1)*4 + EHCI_PORTSC);
				PortSts = EhciReadOpReg(fpHCStruc, PortReg);
	
				if (!(PortSts & EHCI_PORTENABLE)) {
					continue;
				}
				EhciWriteOpReg(fpHCStruc, PortReg, PortSts | EHCI_SUSPEND);
			}
			FixedDelay(250);      // 250 us delay
	
			// Stop the host controller (Reset bit 0)
			EhciClearOpReg(fpHCStruc, EHCI_USBCMD, EHCI_RUNSTOP);
	
			// The Host Controller must halt within 16 micro-frames after 
			// software clears the Run bit. 
			for (i = 0; i < 16; i++) {
				if (EhciReadOpReg(fpHCStruc, EHCI_USBSTS) & EHCI_HCHALTED) {
					break;
				}
                FixedDelay(125);	  // 125 us delay
			}
	
			// Clear the SMI enable bits
			if (fpHCStruc->bExtCapPtr) {
				Data32 = EhciReadPciReg(fpHCStruc, 
							fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG);
	
				EhciWritePciReg(fpHCStruc,
					fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG, Data32 & ~(0x3F));
			}
	
			// Clear the USBSTS register bits
			EhciWriteOpReg(fpHCStruc, EHCI_USBSTS, EhciReadOpReg(fpHCStruc, EHCI_USBSTS));
	
			// Clear the Configure Flag bit
			EhciClearOpReg(fpHCStruc, EHCI_CONFIGFLAG, BIT0);
		} else 
#endif
		{
											//(EIP26685+)>
	        //
	        // Disconnect all the devices connected to its ports
	        //
	        for (bPortNum = 1; bPortNum <= fpHCStruc->bNumPorts; bPortNum++)
	        {
	            USB_DisconnectDevice(fpHCStruc,
	                    (UINT8)(fpHCStruc->bHCNumber | BIT7), bPortNum);
	        }
											//<(EIP26685+)

	        if (fpHCStruc->DebugPort == 0) {
	            //
	            // Stop the host controller (Reset bit 0)
	            //
	            EhciClearOpReg(fpHCStruc, EHCI_USBCMD, EHCI_RUNSTOP);
												//(EIP55960)>
				// The Host Controller must halt within 16 micro-frames after 
				// software clears the Run bit. 
				for (i = 0; i < 16; i++) {
	            	if (EhciReadOpReg(fpHCStruc, EHCI_USBSTS) & EHCI_HCHALTED) {
						break;
	            	}
                    FixedDelay(125);      // 125 us delay
				}
												//<(EIP55960)
	            //
	            // Reset the host controller
	            //
//  EIP#23479          EHCIResetHC(fpHCStruc); // ERROR CONDITION RETURNED IS NOT TAKEN CARE
	            Status = EHCIResetHC(fpHCStruc);
	            ASSERT(Status == USB_SUCCESS);
	        }
		}
        //
        // Program the HC BIOS owned bit and return the legacy
        // support register offset
        //
        EHCIProgramLegacyRegisters(fpHCStruc, 0);   // Reset HC BIOS owned semaphore
                                                    // ERROR CONDITION IS NOT HANDLED

        //
        // Clear the frame list pointers
        //
        USB_InitFrameList (fpHCStruc, EHCI_TERMINATE);

        //
        // Disable TD schedule and free the data structures
        //
		if (DescPtr->fpQHRepeat) {
			EhciMemFree(fpHCStruc, DescPtr->fpQHRepeat,
							GET_MEM_BLK_COUNT(sizeof(EHCI_QH) + sizeof(EHCI_QTD) ));
		}

        //
        // Free the scheduling QHs
        //
        EhciMemFree(fpHCStruc, DescPtr->PeriodicQh,        
                        GET_MEM_BLK_COUNT(1 * sizeof(EHCI_QH)));

        //
        // Free descriptor structure
        //
        EhciMemFree(fpHCStruc, DescPtr,
                        GET_MEM_BLK_COUNT_STRUC(EHCI_DESC_PTRS));

//#if EHCI_ASYNC_BELL_SUPPORT
        //
        // Free the Async transfer QH
        //
//        EhciMemFree(fpHCStruc, gUsbData->fpQHAsyncXfer, GET_MEM_BLK_COUNT_STRUC(EHCI_QH));
//#endif

		USBKeyRepeat(fpHCStruc, 3);
    }
    else    // not controlled by BIOS
    {
        //
        // Program the HC BIOS owned bit and return the legacy
        // support register offset
        //
        EHCIProgramLegacyRegisters(fpHCStruc, 0);   // Reset HC BIOS owned semaphore
    }

    //
    // Set the HC state to stopped
    //
    fpHCStruc->dHCFlag  &= ~(HC_STATE_RUNNING);

    CheckBiosOwnedHc();

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCI_DisableInterrupts
//
// Description: This function disables the HC interrupts
//
// Input:   fpHCStruc   Pointer to the HCStruc structure
//
// Output:  USB_ERROR   On error
//          USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_DisableInterrupts (HC_STRUC* fpHCStruc)
{
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    //
    // Disable interrupt generation
    //
    EhciClearOpReg(fpHCStruc, EHCI_USBINTR, EHCI_USBINT_EN | EHCI_PCDINT_EN);

    //
    // Stop periodic and asynchoronous schedule
    //
    EHCIStopAsyncSchedule(fpHCStruc);
    EHCIStopPeriodicSchedule(fpHCStruc);

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCI_EnableInterrupts
//
// Description: This function enables the HC interrupts
//
// Input:   fpHCStruc   Pointer to the HCStruc structure
//
// Output:  USB_ERROR   On error
//          USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_EnableInterrupts (HC_STRUC* fpHCStruc)
{
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    //
    // Start periodic and asynchoronous schedule
    //
    EHCIStartAsyncSchedule(fpHCStruc);
    EHCIStartPeriodicSchedule(fpHCStruc);

    //
    // Enable interrupt generation
    //
    EhciSetOpReg(fpHCStruc, EHCI_USBINTR, EHCI_USBINT_EN | EHCI_PCDINT_EN);

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   ProcessRootHubChanges
//
// Description: Root hub change processing code
//
// Parameters:  fpHCStruc   Pointer to the HCStruc structure
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
ProcessRootHubChanges(
    HC_STRUC* fpHCStruc
)
{
    UINT8   bPortNum;

    //
    // Check bEnumFlag before enumerating devices behind root hub
    //
    if ((gUsbData->bEnumFlag) == TRUE) {
        return USB_ERROR;
    }

    //
    // Clear the port change bit of the interrupt status register EHCI_USBSTS
    //
    EhciWriteOpReg(fpHCStruc, EHCI_USBSTS, EHCI_PORT_CHANGE_DETECT);

    //
    // Check all the ports on the root hub for any change in connect status.
    // If the connect status has been changed on either or both of these ports,
    // then call the  routine UsbHubPortChange for each changed port.
    //
    // Set enumeration flag and avoid hub port enumeration
    //
    gUsbData->bEnumFlag    = TRUE;

    for (bPortNum = 1; bPortNum <= fpHCStruc->bNumPorts; bPortNum++) {
        if (fpHCStruc->DebugPort && fpHCStruc->DebugPort==bPortNum) continue;
        //
        // Process device connect/disconnect
        // Note: port connect status is cleared while processing
        // connect/disconnect (EHCIGetRootHubStatus)
        //
        USBCheckPortChange(fpHCStruc, (UINT8)(fpHCStruc->bHCNumber | BIT7), bPortNum);
    }

    //
    // Reset enumeration flag and enable hub enumeration
    //
    gUsbData->bEnumFlag    = FALSE;
    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:    EHCI_ProcessInterrupt
//
// Description: This function is called when the USB interrupt bit is
//              set. This function will parse through the TDs and QHs to
//              find out completed TDs and call their respective call
//              back functions
//
// Parameters:  fpHCStruc   Pointer to the HCStruc structure
//
// Output:      USB_ERROR - Need more Interrupt processing
//              USB_SUCCESS - No interrupts pending
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_ProcessInterrupt(HC_STRUC* fpHCStruc)
{
    UINT32  dSts, dTmp;
    UINT16  wStatus;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
                                        //(EIP71067-)>
//#if (EHCI_ASYNC_BELL_SUPPORT==0)
//    EHCI_QH *fpQH;
//#endif
                                        //<(EIP71067-)
    //
    // If EHCI extended capabilities  pointer is present,
    // then service OwnerShipChange SMI
    //
    if (fpHCStruc->bExtCapPtr) {
        //
        // Read control and status register
        //
        dTmp = EhciReadPciReg(
                fpHCStruc,
                fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG);
        wStatus = (UINT16)dTmp;
        wStatus &= (UINT16)(dTmp >> 16);   // "And" enable and status bits
        if (wStatus & EHCI_OWNERSHIP_CHANGE_SMI_STS) {
            ClearEECPstatus(fpHCStruc, wStatus);
            ProcessOwnerShipChangeSMI(fpHCStruc);
            return USB_SUCCESS; // Break from Interrupt process loop
        }
    }

    //
    // Check whether the controller is still under BIOS control
    // Read the base address of the Periodic Frame List to the PERIODIC BASE
    // register and compare with stored value
    //
    if (EHCICheckHCStatus(fpHCStruc) == USB_ERROR) {
        //
        // Control is not with us anymore, we should disable SMI generation
        // and come out.
        //
        if (fpHCStruc->bExtCapPtr) {
            //
            // Read control and status register
            //
            dTmp = EhciReadPciReg(
                        fpHCStruc,
                        fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG);
        
            //
            // Leave only Ownership SMI active.
            //
            dTmp &= 0xE0002000; 
            EhciWritePciReg(
                fpHCStruc,
                fpHCStruc->bExtCapPtr + EHCI_LEGACY_CTRL_STS_REG,
                dTmp);
        }
        return  USB_SUCCESS;
    }

	if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
		return USB_SUCCESS;
	}

    while(TRUE){
        //
        // Get the interrupt status
        //
        dSts = EhciReadOpReg(fpHCStruc, EHCI_USBSTS);

        //USB_DEBUG(DEBUG_LEVEL_3, "-->> %x <<--\n", dSts);

		if (dSts & EHCI_HOST_SYSTEM_ERROR) {
			gUsbData->dUSBStateFlag  &= (~USB_FLAG_ENABLE_BEEP_MESSAGE);
			EHCI_Start(fpHCStruc);
			EHCI_EnumeratePorts(fpHCStruc);
			gUsbData->dUSBStateFlag |= USB_FLAG_ENABLE_BEEP_MESSAGE;
			continue;
		}

        if (dSts & EHCI_HCHALTED) {
			// Clear the USBSTS register bits
			EhciWriteOpReg(fpHCStruc, EHCI_USBSTS, EhciReadOpReg(fpHCStruc, EHCI_USBSTS));
            break;
        }
        
        //
        // Check for transaction complete
        //
        if ((gUsbData->ProcessingPeriodicList == TRUE) && (dSts & EHCI_USB_INTERRUPT)) {

            //
            // Clear the interrupt status
            //
            EhciWriteOpReg(fpHCStruc, EHCI_USBSTS, EHCI_USB_INTERRUPT);

            //Section 4.4 Schedule traversal rules.
            //if the periodic schedule is enabled (see Section 4.6) then the host controller must 
            //execute from the periodic schedule before executing from the asynchronous schedule. 
            //It will only execute from the asynchronous schedule after it encounters the end of
            //the periodic schedule.

            //
            // Check and process periodic schedule
            //
            if (dSts & EHCI_PER_SCHED_STATUS) {
                //
                // Check the command register for Async status
                //
                dTmp = EhciReadOpReg(fpHCStruc, EHCI_USBCMD);

                if (dTmp & EHCI_PER_SCHED_ENABLE) {
                    EHCIProcessPeriodicList(fpHCStruc);
                }
            }

            //
            // Check for Asynchronous schedule completion
            //
/*                                        //(EIP71067-)>
            if (dSts & EHCI_ASYNC_SCHED_STATUS) {
                dTmp = DwordReadMem(dMemAddr, EHCI_USBCMD);
                if (dTmp & EHCI_ASYNC_SCHED_ENABLE) {
                    //
                    // Check and process Async. QH
                    //
#if EHCI_ASYNC_BELL_SUPPORT
                    EHCIProcessQH(fpHCStruc, fpHCStruc->stDescPtrs.fpEHCIDescPtrs->fpQHControl);
                    EHCIProcessQH(fpHCStruc, fpHCStruc->stDescPtrs.fpEHCIDescPtrs->fpQHBulk);
#else
                    //
                    // Get the Async list address
                    //
                    fpQH = (EHCI_QH*)(UINTN)DwordReadMem(dMemAddr, EHCI_ASYNCLISTADDR);
                    if (EHCIProcessQH(fpHCStruc, fpQH) == USB_ERROR) {
                        //continue;
                        //return    USB_SUCCESS;
                    } else {
                        //
                        // Async list processed; stop the Async transfer
                        //
                        EHCIStopAsyncSchedule(fpHCStruc);
                    }
#endif
                }
            }
*/                                      //<(EIP71067-)
            continue;
        }

        //
        // Check PORT_CHANGE_DETECT bit
        //
        if ((dSts & EHCI_PORT_CHANGE_DETECT )) {
            if(ProcessRootHubChanges(fpHCStruc) == USB_SUCCESS) {
                continue;
            }
        }
        break;  // No more statuses to process
    }
    return  USB_SUCCESS;    // Set as interrupt processed
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProcessOwnerShipChangeSMI
//
// Description: This procedure process EHCI OwnerShipChange SMI.
//
// Input:   fpHCStruc   HCStruc pointer
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ProcessOwnerShipChangeSMI(HC_STRUC* fpHCStruc)
{
    UINT32 dTemp = GetEhciUSBLEGSUP(fpHCStruc);
	fpHCStruc->dHCFlag |= HC_STATE_OWNERSHIP_CHANGE_IN_PROGRESS;
    if (dTemp & EHCI_HC_OS) {
        gUsbData->dUSBStateFlag  &= (~USB_FLAG_ENABLE_BEEP_MESSAGE);
        ProcessSmiChangeToEHCD(fpHCStruc);
    }
    else {
        gUsbData->dUSBStateFlag |= USB_FLAG_ENABLE_BEEP_MESSAGE;
        ProcessSmiChangeToBIOS(fpHCStruc);
    }
	fpHCStruc->dHCFlag &= ~(HC_STATE_OWNERSHIP_CHANGE_IN_PROGRESS);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProcessSmiChangeToEHCD
//
// Description: This procedure process OwnerShipChange for BIOS -> EHCD.
//
// Input:   fpHCStruc   HCStruc pointer
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ProcessSmiChangeToEHCD (HC_STRUC* fpHCStruc)
{
    EHCI_Stop(fpHCStruc);    // Stop EHCI legacy
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProcessSmiChangeToBIOS
//
// Description: This procedure process OwnerShipChange for EHCD -> BIOS.
//
// Input:   SI  HCStruc pointer
//
// Output:  None
//
// Modified:    None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ProcessSmiChangeToBIOS (
    HC_STRUC    *fpHCStruc
)
{
    HC_STRUC    *Hc;
    UINT8       Count;
    DEV_INFO    *Device;

    // Stop UHCI devices connected to the companions
    // Core8 executes this under MKF_PCCHECK_PATCH==1 condition, EIP10272
    for (Count = 1; Count < MAX_DEVICES; Count++) {
        Device = &gUsbData->aDevInfoTable[Count];
        Hc = gUsbData->HcTable[Device->bHCNumber - 1];

        if (Hc->bHCType != USB_HC_UHCI) continue;   // Not UHCI

        if ((Device->Flag & DEV_INFO_VALID_STRUC)==0) continue;    // Not valid

        if ((Hc->wBusDevFuncNum & 0xfff8) !=
            (fpHCStruc->wBusDevFuncNum & 0xfff8)) continue; // Not a companion

        // Found a device connected to UHCI companion controller. Stop it.
        USB_StopDevice(Hc, Device->bHubDeviceNumber, Device->bHubPortNumber);
    }

    EHCI_Start(fpHCStruc);  // Reinitialize EHCI host controller
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCI_ReleasePortOwner
//
// Description: 
//
// Input:       HcStruc   - Pointer to HCStruc of the host controller
//              PortNum   - Port in the HC whose status is requested
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_ReleasePortOwner(
    HC_STRUC*	HcStruc,
    UINT8		PortNum
)
{
    UINT16  PortReg = (UINT16)((PortNum-1)*4 + EHCI_PORTSC);
    UINT16  i;

	if ((HcStruc->dHCSParams & EHCI_N_CC) == 0) {
		return USB_SUCCESS;
	}

    if (!(EhciReadOpReg(HcStruc, PortReg) & EHCI_CURRENTCONNECTSTATUS)) {
        return USB_ERROR;
    }

    USB_DEBUG(DEBUG_LEVEL_3, "Release EHCI port %d\n", PortNum);
    EhciSetOpReg(HcStruc, PortReg, EHCI_PORTOWNER);

    // Loop until Full speed device disconnect event process done.
    // This change is done in sync with Core8 except the extra 400mS delay
    for (i = 0; i < 200; i++) {
        if (EhciReadOpReg(HcStruc, PortReg) & EHCI_CONNECTSTATUSCHANGE) {
            break;
        }
        FixedDelay(100); 
    }

    EhciSetOpReg(HcStruc, PortReg, EHCI_CONNECTSTATUSCHANGE);

	return USB_SUCCESS;	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIGetRootHubStatus
//
// Description: This function returns the port connect status for the
//              root hub port
//
// Input:       fpHCStruc   - Pointer to HCStruc of the host controller
//              bPortNum    - Port in the HC whose status is requested
//
// Output:      Port status flags (see USB_PORT_STAT_XX equates)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_GetRootHubStatus(
    HC_STRUC*   fpHCStruc,
    UINT8       bPortNum,
    BOOLEAN     ClearChangeBits
)
{
    UINT32  dTmp;
    UINT8   bStatus     = USB_PORT_STAT_DEV_OWNER;
    UINT16  wPortReg    = (UINT16)((bPortNum-1)*4 + EHCI_PORTSC);
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (fpHCStruc->DebugPort && fpHCStruc->DebugPort==bPortNum) return 0;

    //
    // Read the status of the port
    //
    dTmp    = EhciReadOpReg(fpHCStruc, wPortReg);
	USB_DEBUG(3, "Ehci port[%d] status: %08x\n", bPortNum, dTmp);

	// Detect the high-speed device.
	// In case of low-speed or full-speed change the ownership to a
	// companion 1.1 controller (if any)
	if (dTmp & EHCI_CURRENTCONNECTSTATUS) {
    	// Analyze Line Status
    	if ((dTmp & EHCI_LINE_STATUS) == EHCI_DMINUSBIT) {	// Low speed device connected
    		EHCI_ReleasePortOwner(fpHCStruc, bPortNum);
			dTmp = EhciReadOpReg(fpHCStruc, wPortReg);
    	}
	}

    //
    // Check the connect status change bit
    //
    if (dTmp & EHCI_CONNECTSTATUSCHANGE) {
        //
        // Set connect status change flag
        //
        bStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED;

        //
        // Wait 20ms for host controller could report accurate port status properly.
        //
        //FixedDelay(gUsbData->UsbTimingPolicy.EhciPortConnect * 1000);   // 20ms delay

        //
        // Read the status of the port
        //
        //dTmp = EhciReadOpReg(fpHCStruc, wPortReg);

		// Clear connect status change
        if (ClearChangeBits == TRUE) {
		    EhciSetOpReg(fpHCStruc, wPortReg, EHCI_CONNECTSTATUSCHANGE);		//(EIP61030+)
        }
    }

    if (dTmp & EHCI_CURRENTCONNECTSTATUS) {
        bStatus |= USB_PORT_STAT_DEV_CONNECTED;

		if (dTmp & EHCI_PORTENABLE) {
            bStatus |= USB_PORT_STAT_DEV_HISPEED;

            // Patch for CloverTrail
            if (fpHCStruc->Vid == 0x8086 && 
                (fpHCStruc->Did == 0xE006 || fpHCStruc->Did == 0x08F2)) {                
                if ((dTmp & EHCI_LINE_STATUS) == EHCI_DMINUSBIT) {
                    bStatus &= ~USB_PORT_STAT_DEV_HISPEED;
                    bStatus |= USB_PORT_STAT_DEV_LOWSPEED;
                } else  if ((dTmp & EHCI_LINE_STATUS) == EHCI_DPLUSBIT) {
                    bStatus &= ~USB_PORT_STAT_DEV_HISPEED;
                    bStatus |= USB_PORT_STAT_DEV_FULLSPEED;
                }
            }
			bStatus |= USB_PORT_STAT_DEV_ENABLED;
										//(EIP61030+)>
		} else {
			if (gUsbData->bIgnoreConnectStsChng == TRUE) {
				if (!(dTmp & EHCI_CONNECTSTATUSCHANGE)) {
					bStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED;
				}
			}
										//<(EIP61030+)
		}
	}

    if (dTmp & EHCI_PORTOWNER) {
        bStatus &= ~USB_PORT_STAT_DEV_OWNER;
    }

	return bStatus;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIDisableRootHub
//
// Description: This function disables the EHCI HC Ruoot hub port.
//
// Input:       fpHCStruc   - Pointer to HCStruc of the host controller
//              bPortNum    - Port in the HC to disable
//
// Output:      USB_SUCCESS on success
//              USB_ERROR   on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_DisableRootHub(
    HC_STRUC* fpHCStruc,
    UINT8 bPortNum)
{
										//(EIP58108+)>
    UINT16  PortReg = (UINT16)((bPortNum-1)*4 + EHCI_PORTSC);
	UINT32	i;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (fpHCStruc->DebugPort && fpHCStruc->DebugPort==bPortNum) return USB_SUCCESS;

	if (!(EhciReadOpReg(fpHCStruc, PortReg) & EHCI_PORTENABLE)) {
		return USB_SUCCESS;
	}
    EhciClearOpReg(fpHCStruc, PortReg, EHCI_PORTENABLE);

	for (i = 0; i < 100; i++) {
		if ((EhciReadOpReg(fpHCStruc, PortReg) & EHCI_PORTENABLE) == 0) {
			break;
		}
		FixedDelay(100);
	}
										//<(EIP58108+)
    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIEnableRootHub
//
// Description: This function enables the EHCI HC Root hub port.
//
// Input:       fpHCStruc   - Pointer to HCStruc of the host controller
//              bPortNum    - Port in the HC to enable
//
// Output:      USB_SUCCESS on success
//              USB_ERROR   on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_EnableRootHub(
    HC_STRUC* fpHCStruc,
    UINT8 bPortNum)
{
//
// Software can only enable the EHCI root hub ports by port RESET.  HC will
// enable the port only if it is a high speed device
//
    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCI_ResetRootHub
//
// Description: This function resets the EHCI HC Root hub port.
//
// Input:       HcStruc   - Pointer to HCStruc of the host controller
//              PortNum    - Port in the HC to enable
//
// Output:      USB_SUCCESS on success
//              USB_ERROR   on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_ResetRootHub(
    HC_STRUC*	HcStruc,
    UINT8		PortNum
)
{
    UINT16  PortReg = (UINT16)((PortNum-1)*4 + EHCI_PORTSC);
	UINT32	i;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

	// Disable the port if it is enabled
	if (EhciReadOpReg(HcStruc, PortReg) & EHCI_PORTENABLE) {
		EhciClearOpReg(HcStruc, PortReg, EHCI_PORTENABLE);
	
		// There may be a delay in disabling or enabling a port due to other 
		// host controller and bus events.
		for (i = 0; i < 100; i++) {
			if ((EhciReadOpReg(HcStruc, PortReg) & EHCI_PORTENABLE) == 0) {
				break;
			}
			FixedDelay(100);    // 100 us delay
		}
	}

	// Reset the port
	EhciSetOpReg(HcStruc, PortReg, EHCI_PORTRESET);

    if ((HcStruc->dHCFlag & HC_STATE_CONTROLLER_WITH_RMH) && (PortNum == 1)) {
        FixedDelay(3 * 1000);	 // 3 ms delay
    } else {
    	// Wait til port disable is complete (Tdrstr=50ms Ref 7.1.7.5 of USB Spec 2.0)
    	FixedDelay(50 * 1000);	 // 50 ms delay        
    }

	EhciClearOpReg(HcStruc, PortReg, EHCI_PORTRESET);	// Terminate reset

    if (!(EhciReadOpReg(HcStruc, PortReg) & EHCI_CURRENTCONNECTSTATUS)) {
        return USB_ERROR;
    }

	// if the port detects that the attached device is high-speed during reset, 
	// then the host controller must have the port in the enabled state within 2ms 
	// of software writing this bit to a zero.
	for (i = 0; i < 20; i++) {
		if ((EhciReadOpReg(HcStruc, PortReg) & (EHCI_PORTRESET | 
			EHCI_PORTENABLE)) == EHCI_PORTENABLE) {
			break;
		}
        FixedDelay(100);	 // 100 us delay
	}

	if (EhciReadOpReg(HcStruc, PortReg) & EHCI_PORTRESET) {	 // Reset failed
		USBLogError(USB_ERR_PORT_RESET_FAILED);
		return USB_ERROR;
	}

	if (!(EhciReadOpReg(HcStruc, PortReg) & EHCI_PORTENABLE)) {
        if (!(EhciReadOpReg(HcStruc, PortReg) & EHCI_CURRENTCONNECTSTATUS)) {
            return USB_ERROR;
        } else {
		    EHCI_ReleasePortOwner(HcStruc, PortNum);
		    return USB_ERROR;
        }
	}

	FixedDelay(1 * 1000);	 // 1 ms delay

    return USB_SUCCESS;
}

                                        //(EIP54018+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        EHCI_GlobalSuspend
//
// Description: 
//  This function suspend the EHCI HC.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_GlobalSuspend(
    HC_STRUC*	HcStruc
)
{
    UINT16  PortReg;
	UINT32	PortSts;
    UINT8   PortNum;
    UINT8   i;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }
    
	if (EhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}

    for (PortNum = 1; PortNum <= HcStruc->bNumPorts; PortNum++) {
        PortReg = (UINT16)(EHCI_PORTSC + (PortNum - 1) * 4 );
        PortSts = EhciReadOpReg(HcStruc, PortReg );
        USB_DEBUG(DEBUG_LEVEL_3,"EHCI PortSts[%x] %x \n",
                        PortNum, PortSts); 
        // Check if port is disabled or suspended.
        if((PortSts & EHCI_PORTENABLE) && (!(PortSts & EHCI_SUSPEND))) {
            // Suspend if necessary.
            EhciClearOpReg(HcStruc, PortReg,
                            EHCI_WKOC_E | EHCI_WKDSCNNT_E | EHCI_WKCNNT_E);
            EhciSetOpReg(HcStruc, PortReg, EHCI_SUSPEND);
            // Read PortSc until port shows suspended. 
     	    for(i = 0; i < 100; i++) {
                if(EhciReadOpReg(HcStruc, PortReg) & EHCI_SUSPEND) {
                    break;
                }
                FixedDelay(100);      // 100 us delay
	        } 
        }
    }

    // Turn HC off and wait for the Halted bit to get set
    EhciClearOpReg(HcStruc, EHCI_USBCMD, EHCI_RUNSTOP);
    // The Host Controller must halt within 16 micro-frames after 
    // software clears the Run bit. 
	for (i = 0; i < 16; i++) {
        if(EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_HCHALTED) {
            break;
        }
        FixedDelay(125);      // 125 us delay
	}

    HcStruc->dHCFlag &= ~(HC_STATE_RUNNING);
    HcStruc->dHCFlag |= HC_STATE_SUSPEND;

    return USB_SUCCESS;
}
                                        //<(EIP54018+)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCI_GetHiSpeedHubPortNumber
//
// Description: This function gets the hi-speed hub's device and port number
//              to which this low speed device is connected.  It parses
//              through its parents until it finds the correct device. This
//              information is used for split transaction
//
// Input:   fpDevInfo   - Device info pointer of the device
//
// Output:  UINT16      - Device/port number of the hi-speed hub
//
// Notes:   This low/full speed device may be behind different hubs as
//          shown below. In any case this routine will get the device
//          address of the hub number HISP_A :
//      Notations used:
//          MBPortX     Motherboard USB port
//          HISP_X      Hi-speed hub number X
//          FUSP_X      Full-speed hub number X
//          Device      Low/Full speed device
//      Config 1:
//        MBPortX --> HISP_A --> Device
//      Config 2:
//        MBPortX --> HISP_A --> FUSP_1 --> Device
//      Config 3:
//        MBPortX --> HISP_B --> HISP_A --> Device
//      Config 4:
//        MBPortX --> HISP_A --> FUSP_1 --> HISP_B --> Device
//        In the above configuration the HISP_B will be operated in
//      full speed rather than hi-speed since it is connected to a
//      full speed hub
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
EHCI_GetHiSpeedHubPortNumber(DEV_INFO* fpDevInfo)
{
    DEV_INFO*   fpHubDev = fpDevInfo;
    DEV_INFO*   fpParentHubDev;
    UINT16      wRetCode;

    if( !VALID_DEVINFO( fpDevInfo) )
        return 0;

//
// Get the device info structure for the matching device address
//
    //
    // Get the device number of the immediate hub, then get the device
    // info structure for this device number
    //
    for(;;)
    {
        fpParentHubDev  = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR,
                                0, fpHubDev->bHubDeviceNumber, 0);
        if ( !fpParentHubDev )  // Error. Exit !
        {
            return  0;
        }
        if (((fpParentHubDev->bEndpointSpeed << USB_PORT_STAT_DEV_SPEED_MASK_SHIFT)
             & USB_PORT_STAT_DEV_SPEED_MASK) == 0) break;
        fpHubDev = fpParentHubDev;
    }
    //
    // The first USB 2.0 hub found as fpHubDev to which the low/full speed
    // device is connected
    //
    wRetCode = (UINT16)((fpHubDev->bHubPortNumber << 7) |
                                fpHubDev->bHubDeviceNumber);

    return wRetCode;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EhciExexuteAsyncSchedule
//
// Description: This function insert the requested QH to asynchronous schedule
//				and waits until the QH completes or the transaction time-out.
//
// Input:   HcStruc   - Pointer to HCStruc of the host controller
//          XferQh    - Pointer to the QH which has to be completed
//
// Output:  USB_ERROR   On error
//          USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
EhciExexuteAsyncSchedule(
	HC_STRUC	*HcStruc,
	EHCI_QH 	*XferQh
)
{
	UINT16	Status = USB_SUCCESS;
	UINT32	Count;
    UINT32  TimeOut = gUsbData->wTimeOutValue * 100; // in 10 macrosecond unit
//
//#if EHCI_ASYNC_BELL_SUPPORT
//	UINT32	Tmp;

//	XferQh->dLinkPointer = EHCI_TERMINATE;
//	XferQh->bActive = TRUE;

	//
	// Insert the Control/Bulk QH into the Async list
	//
//	Tmp = gUsbData->fpQHAsyncXfer->dLinkPointer;
//	gUsbData->fpQHAsyncXfer->dLinkPointer  = (UINT32)XferQh | EHCI_QUEUE_HEAD;
//	XferQh->dLinkPointer = Tmp;
//#else
	//
	// Set the ASYNCLISTADDR register to point to the Control/Bulk QH
	//
    EhciWriteOpReg(HcStruc, EHCI_ASYNCLISTADDR, (UINT32)(UINTN)XferQh);

	//
	// Set next QH pointer to itself (circular link)
	//
	XferQh->dLinkPointer = (UINT32)((UINTN)XferQh | EHCI_QUEUE_HEAD);
	XferQh->bActive = TRUE;
//#endif

	//
    // Now put the Control/Bulk QH into the HC's schedule by
    // setting the Async. schedule enabled field of USBCMD register
    // This will cause the HC to execute the transaction in the next active frame.
    //
    Status = EHCIStartAsyncSchedule(HcStruc);

    if (Status == USB_ERROR) {
        return Status;
    }

	// Wait for tansfer complete
	for(Count = 0; !TimeOut || Count < TimeOut; Count++) {
		EHCIProcessQH(HcStruc, XferQh);
		if(XferQh->bActive == FALSE) {
			break;
		}
		FixedDelay(10);  // 10 microsec
	}

//#if EHCI_ASYNC_BELL_SUPPORT
    //
    // Disconnect Control/Bulk QH from the Async list
    //
//    EHCIRemoveQHFromAsyncList(HcStruc, XferQh);
//#else
	//
	// Stop the Async transfer
	//
	EHCIStopAsyncSchedule(HcStruc);
//#endif

	if(XferQh->bActive == TRUE) {
		XferQh->bActive = FALSE;
		Status = USB_ERROR;
		USB_DEBUG (DEBUG_LEVEL_3, "EHCI Time-Out\n");
	}
	
	// Service all interrupts
	EHCI_ProcessInterrupt(HcStruc);

	return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:    EHCI_ControlTransfer
//
// Description: This function executes a device request command transaction
//              on the USB. One setup packet is generated containing the
//              device request parameters supplied by the caller.  The setup
//              packet may be followed by data in or data out packets
//              containing data sent from the host to the device
//              or vice-versa. This function will not return until the
//              request either completes successfully or completes in error
//              (due to time out, etc.)
//
// Parameters:  fpHCStruc   Pointer to HCStruc of the host controller
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
// Output:  Number of bytes actually transferred
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
EHCI_ControlTransfer (
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    UINT16      wRequest,
    UINT16      wIndex,
    UINT16      wValue,
    UINT8       *fpBuffer,
    UINT16      wLength)
{
    UINT32      dTmp, dTmp1;
    UINT16      wRetCode = 0;   // Initialize with error
    EHCI_QH     *fpQHCtl;
    EHCI_QTD    *fpQTDCtlSetup, *fpQTDCtlData, *fpQTDCtlStatus;
    DEV_REQ     *fpRequest = NULL;
    UINT8       bEndpointSpeed;
	UINT8		*BufPhyAddr = NULL;
	VOID		*BufferMapping = NULL;
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
                USB_DEBUG(3, "Ehci ControlTransfer Invalid Pointer, Buffer is in SMRAM.\n");
                return 0;
            }
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }

	if (EhciIsHalted(fpHCStruc)) {
		return 0;
	}

    if( !VALID_DEVINFO( fpDevInfo) )
        return 0;
    
    gUsbData->dLastCommandStatusExtended = 0;	//(EIP84790+)

//USB_DEBUG(DEBUG_LEVEL_3, "EHCI_ControlTransfer..\n");
    //
    // Build the device request in the data area of the control setup qTD
    //
    fpRequest = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT(sizeof(DEV_REQ)));
	ASSERT(fpRequest);
    if (fpRequest == NULL) {
        return 0;
    }

    fpRequest->wRequestType = wRequest;
    fpRequest->wIndex       = wIndex;
    fpRequest->wValue       = wValue;
    fpRequest->wDataLength  = wLength;

//
// The QH endpoint characteristic field will be set so
//   Function address & Endpoint number = From DeviceInfo structure,
//   Direction = From TD,
//   Speed = DeviceInfo.bEndpointSpeed,
//   Skip = 1, Format = 0,
//   Max packet size  = DeviceInfo.wEndp0MaxPacket
// The dNextqTDPtr field will be set to qTDControlSetup
// The dAltNextqTDPtr field will be set to EHCI_TERMINATE
// The dCurrentqTDPtr field will be set to 0
//
    //
    // Intialize the queue head with null pointers
    //
										//(EIP71067)>
    fpQHCtl = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT((1 * sizeof(EHCI_QH))+
                                             			(3 * sizeof(EHCI_QTD))));
                                        //(EIP83295+)>
    if(!fpQHCtl) {
        return 0;
    }
                                        //<(EIP83295+)
										//(EIP81030)>
    fpQTDCtlSetup = (EHCI_QTD*)((UINTN)fpQHCtl + sizeof(EHCI_QH));
    fpQTDCtlData = (EHCI_QTD*)((UINTN)fpQTDCtlSetup + sizeof(EHCI_QTD));
    fpQTDCtlStatus = (EHCI_QTD*)((UINTN)fpQTDCtlData + sizeof(EHCI_QTD));
										//<(EIP71067)
										//<EIP81030)
    EHCIInitializeQueueHead(fpQHCtl);

    bEndpointSpeed = fpDevInfo->bEndpointSpeed; // 00/01/10 for HI/LO/FULL

    //
    // Assume as a high speed device
    //
    dTmp = QH_HIGH_SPEED;   // 10b - High speed

    //
    // Check for high speed
    //
    if (bEndpointSpeed)         // Low/Full speed device
    {
        dTmp = ((UINT32)bEndpointSpeed & 1) << 12;  // Bit 12 = full/low speed flag
        dTmp |= QH_CONTROL_ENDPOINT;
        //
        // Set the hub address and port number
        // Get the Hispeed hub port number & device number
        //
        dTmp1 = (UINT32)EHCI_GetHiSpeedHubPortNumber(fpDevInfo);
        dTmp1 = (dTmp1 << 16);		// Split complete Xaction
        fpQHCtl->dEndPntCap |= dTmp1;
    }

//USB_DEBUG(DEBUG_LEVEL_3, "Tmp1..%x\n", dTmp);

    //
    // Use data toggle from qTD and this QH is the head of the queue
    //
//#if EHCI_ASYNC_BELL_SUPPORT
//    dTmp |= QH_USE_QTD_DT;
//#else
    dTmp |= QH_USE_QTD_DT;
    // Do not set QH_HEAD_OF_LIST bit on VIA controller
    if (fpHCStruc->Vid != 0x1106) {
        dTmp |= QH_HEAD_OF_LIST;
    }
//#endif
    dTmp |= (UINT32)fpDevInfo->bDeviceAddress;
    //
    // dTmp[Bits 6:0] = Dev. Addr
    // dTmp[Bit7] = I bit(0)
    // dTmp[Bits11:8] = Endpoint (0)
    //

    dTmp1 = (UINT32)fpDevInfo->wEndp0MaxPacket;
    dTmp |= (dTmp1 << 16);  // Tmp[Bits26:16] = device's packet size
    fpQHCtl->dEndPntCharac  = dTmp;

    //
    // Fill in various fields in the qTDControlSetup.
    //
    //fpQTDCtlSetup = fpHCStruc->stDescPtrs.fpEHCIDescPtrs->fpqTDControlSetup;	//(EIP71067-)

    //
    // The token field will be set so
    //   Direction PID = QTD_SETUP_TOKEN,
    //   Size = size of the data,
    //   Data Toggle = QTD_SETUP_TOGGLE,
    //   Error Count = QTD_THREE_ERRORS,
    //   Status code = QTD_DO_OUT + QTD_ACTIVE
    // The buffer pointers field will point to the aControlSetupData buffer
    //   which was before initialized to contain a DeviceRequest struc.
    // The dNextqTDPtr field will point to the qTDControlData if data will
    //   be sent/received or to the qTDControlStatus if no data is expected.
    // The dAltNextqTDPtr field will be set to EHCI_TERMINATE
    //
    fpQTDCtlSetup->dToken = QTD_SETUP_TOKEN |
                QTD_SETUP_TOGGLE | QTD_IOC_BIT |
                QTD_THREE_ERRORS | QTD_DO_OUT | QTD_ACTIVE |
                (8 << 16);  // Data size

    //
    // Update buffer pointers
    //
    EHCISetQTDBufferPointers(fpQTDCtlSetup, (UINT8*)fpRequest, 8);
    //fpQTDCtlData = fpHCStruc->stDescPtrs.fpEHCIDescPtrs->fpqTDControlData;	//(EIP71067-)

    if (wLength)    // br if no data to transfer
    {
        //
        // Fill in various fields in the qTDControlData
        //
        // The token field will be set so
        //   Direction PID = QTD_OUT_TOKEN/QTD_IN_TOKEN,
        //   Size = size of the data,
        //   Data Toggle = QTD_DATA1_TOGGLE,
        //   Error Count = QTD_THREE_ERRORS,
        //   Status code = QTD_DO_OUT(if it is out) + QTD_ACTIVE
        // The buffer pointers field will point to the fpBuffer buffer
        //   which was before initialized to contain a DeviceRequest struc.
        // The dNextqTDPtr field will point to the qTDControlSetup
        // The dAltNextqTDPtr field will be set to EHCI_TERMINATE
        //
        fpQTDCtlData->dToken = QTD_IN_TOKEN |
                QTD_DATA1_TOGGLE | QTD_IOC_BIT |
                QTD_THREE_ERRORS | QTD_ACTIVE;
        if (!(wRequest & BIT7)) // Br if host sending data to device (OUT)
        {
            fpQTDCtlData->dToken    = QTD_OUT_TOKEN |
                QTD_DATA1_TOGGLE | QTD_IOC_BIT |
                QTD_THREE_ERRORS | QTD_DO_OUT | QTD_ACTIVE;
        }

        //
        // Set length
        //
        fpQTDCtlData->dToken |= ((UINT32)wLength << 16);

		EhciDmaMap(fpHCStruc, (UINT8)(wRequest & BIT7), fpBuffer, wLength, 
			&BufPhyAddr, &BufferMapping);

        //
        // Update buffer pointers
        //
        EHCISetQTDBufferPointers(fpQTDCtlData,
                (UINT8*)BufPhyAddr,
                (UINT32)wLength);
    }

    //
    // Fill in various fields in the qTDControlStatus
    //
    //fpQTDCtlStatus = fpHCStruc->stDescPtrs.fpEHCIDescPtrs->fpqTDControlStatus;	//(EIP71067-)

    //
    // The token field will be set so
    //   Direction PID = QTD_OUT_TOKEN/QTD_IN_TOKEN,
    //   Size = 0,
    //   Data Toggle = QTD_DATA1_TOGGLE,
    //   Error Count = QTD_THREE_ERRORS,
    //   Status code = QTD_DO_OUT(if it is out) + QTD_ACTIVE
    // The buffer pointers field will be 0
    // The dNextqTDPtr field will set to EHCI_TERMINATE
    // The dAltNextqTDPtr field will be set to EHCI_TERMINATE
    //
    // For OUT control transfer status should be IN and
    // for IN cotrol transfer, status should be OUT
    //
    fpQTDCtlStatus->dToken = QTD_IN_TOKEN |
                QTD_DATA1_TOGGLE | QTD_IOC_BIT |
                QTD_THREE_ERRORS | QTD_ACTIVE;
    if(wRequest & BIT7)
    {
        fpQTDCtlStatus->dToken  = QTD_OUT_TOKEN |
                QTD_DATA1_TOGGLE | QTD_IOC_BIT |
                QTD_THREE_ERRORS | QTD_DO_OUT | QTD_ACTIVE;
    }

    EHCISetQTDBufferPointers(fpQTDCtlStatus, NULL, 0);

    //
    // Link the qTD formed now and connect them with the control queue head
    //
    fpQHCtl->fpFirstqTD     = fpQTDCtlSetup;
    fpQHCtl->dNextqTDPtr    = (UINT32)(UINTN)fpQTDCtlSetup;

    if(wLength)
    {
        fpQTDCtlSetup->dNextqTDPtr  = (UINT32)(UINTN)fpQTDCtlData;
        fpQTDCtlData->dNextqTDPtr   = (UINT32)(UINTN)fpQTDCtlStatus;
    }
    else
    {
        fpQTDCtlSetup->dNextqTDPtr  = (UINT32)(UINTN)fpQTDCtlStatus;
    }

    fpQTDCtlStatus->dNextqTDPtr = EHCI_TERMINATE;

	wRetCode = EhciExexuteAsyncSchedule(fpHCStruc, fpQHCtl);
    fpQHCtl->fpFirstqTD     = 0;
    fpQHCtl->dNextqTDPtr    = EHCI_TERMINATE;

	if (wLength) {
		EhciDmaUnmap(fpHCStruc, BufferMapping);
        wLength = wLength - (UINT16)((fpQTDCtlData->dToken & ~(QTD_DATA_TOGGLE)) >> 16);
	}

    //
    // Clear the stalled condition flag
    //
    gUsbData->bLastCommandStatus &= ~USB_CONTROL_STALLED;

    //
    // Check whether the QH stopped or timed out
    //
    if (wRetCode != USB_SUCCESS) {
        gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;	//(EIP84790+)
		wLength = 0;                    //(EIP71067)
	}

	if (fpQHCtl->bErrorStatus & QTD_HALTED) {
        //
        // Command stalled set the error bit appropriately
        //
        gUsbData->bLastCommandStatus   |= USB_CONTROL_STALLED;
		wLength = 0;                    //(EIP71067)
    }
                                        //(EIP71067+)>
    EhciMemFree(fpHCStruc, fpQHCtl, GET_MEM_BLK_COUNT((1 * sizeof(EHCI_QH))+
                                           (3 * sizeof(EHCI_QTD))));
                                        //<(EIP71067+)
	EhciMemFree(fpHCStruc, fpRequest, GET_MEM_BLK_COUNT(sizeof(DEV_REQ)));

	return wLength;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:    EHCI_BulkTransfer
//
// Description: This function executes a bulk transaction on the USB. The
//              transfer may be either DATA_IN or DATA_OUT packets containing
//              data sent from the host to the device or vice-versa. This
//              function wil not return until the request either completes
//              successfully or completes with error (due to time out, etc.)
//              NOTE: Make sure that amount of bytes to transfer should not
//              exceed MAX_EHCI_DATA_SIZE
//
// Parameters:  pHCStruc    Pointer to HCStruc of the host controller
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
// Output:      Amount of data transferred
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
EHCI_BulkTransfer(
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    UINT8       bXferDir,
    UINT8       *fpBuffer,
    UINT32      dwLength)
{
    UINT16      wMaxPkt;
    UINT8       bEndp, bDatToggle;
    EHCI_QH     *fpQHBulk;
    EHCI_QTD    *fpQTDBulkData;
    UINT32      dTmp, dTmp1;
    UINT16      Status;
    UINT32      dBytesToTransfer, dBytesRemaining;
    UINT32      dBytesTransferred;
	UINT8		*BufPhyAddr = NULL;
	VOID		*BufferMapping = NULL;
    UINT8       *TempBuffer = NULL;
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
            USB_DEBUG(3, "Ehci BulkTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }

	if (EhciIsHalted(fpHCStruc)) {
		return 0;
	}

    if (!VALID_DEVINFO(fpDevInfo)) {
        return 0;
    }

    // Realtek 8111EP EHCI controller workaround
    // The controller doesn't work if the buffer address isn't DWORD alignment 
    // (current offset of qTD). Provide the workaround to locate DWORD alignment buffer.
    
    if ((fpHCStruc->Vid == 0x10EC) && (fpHCStruc->Did == 0x816D)) {
        if ((UINTN)fpBuffer & (BIT0 | BIT1)) {
            if (dwLength < HIGHSPEED_MAX_BULK_DATA_SIZE) {
                TempBuffer = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT((UINT16)dwLength));
            } else {
                TempBuffer = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT(HIGHSPEED_MAX_BULK_DATA_SIZE));  
            }
        }
    }

    //clear HW source of error
    gUsbData->dLastCommandStatusExtended = 0;


    dBytesRemaining     = dwLength;
    dBytesTransferred   = 0;
		
	//
	// Get Bulk IN/OUT enpoint number, data sync value & max packet size
	//
	if (bXferDir & BIT7)
    {
        wMaxPkt = fpDevInfo->wBulkInMaxPkt;
        bEndp   = fpDevInfo->bBulkInEndpoint;
    }
    else
    {
        wMaxPkt = fpDevInfo->wBulkOutMaxPkt;
        bEndp   = fpDevInfo->bBulkOutEndpoint;
    }
    if( wMaxPkt == 0){
        return 0;
    }
                                        //(EIP71067+)>
    fpQHBulk = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT((1 * sizeof(EHCI_QH))+
                                              			 (1 * sizeof(EHCI_QTD))));
                                        //(EIP83295+)>
    if(!fpQHBulk) {
        return 0;
    }
                                        //<(EIP83295+)
    fpQTDBulkData = (EHCI_QTD*)((UINTN)fpQHBulk + sizeof(EHCI_QH));	//(EIP81030)
                                        //<(EIP71067+)
	EhciDmaMap(fpHCStruc, bXferDir, fpBuffer, dwLength, &BufPhyAddr, &BufferMapping);

    while (dBytesRemaining) {
        dBytesToTransfer = 
             (dBytesRemaining < HIGHSPEED_MAX_BULK_DATA_SIZE)?
                    dBytesRemaining : HIGHSPEED_MAX_BULK_DATA_SIZE;
		
		//
		// Get data toggle value
		//
    	bDatToggle = UsbGetDataToggle(fpDevInfo, bEndp | bXferDir);

        //
        // Set the QH's dNextqTDPtr field to bulk data qTD and dAltqTDPtr field to
        // EHCI_TERMINATE. Also set QH's link pointer to itself
        //
                                        //(EIP71067-)>
        //fpQHBulk        = fpHCStruc->stDescPtrs.fpEHCIDescPtrs->fpQHBulk;
        //fpQTDBulkData   = fpHCStruc->stDescPtrs.fpEHCIDescPtrs->fpqTDBulkData;
                                        //<(EIP71067-)
        //
        // Intialize the queue head
        //
        EHCIInitializeQueueHead(fpQHBulk);
    
        //
        // Set the first qTD pointer
        //
        fpQHBulk->fpFirstqTD    = fpQTDBulkData;
        fpQHBulk->dNextqTDPtr   = (UINT32)(UINTN)fpQTDBulkData;
        fpQHBulk->dLinkPointer  = (UINT32)((UINTN)fpQHBulk | EHCI_QUEUE_HEAD);
    
        //
        // Device address & Endpoint
        //
        dTmp    = (UINT32)(fpDevInfo->bDeviceAddress | (bEndp << 8));
    
        //
        // Set max packet size
        //
        dTmp    = dTmp | ((UINT32)wMaxPkt << 16);
    
        //
        // Set the data toggle control
        //
//    #if EHCI_ASYNC_BELL_SUPPORT
//        dTmp    |= QH_USE_QTD_DT;
//    #else
        dTmp |= QH_USE_QTD_DT;
        // Do not set QH_HEAD_OF_LIST bit on VIA controller
        if (fpHCStruc->Vid != 0x1106) {
            dTmp |= QH_HEAD_OF_LIST;
        }
//    #endif
    
        //
        // Set the device speed
        // Reset the device speed bits
        //
        dTmp1   = (UINT32)fpDevInfo->bEndpointSpeed;    // 00/01/10 for HI/LO/FULL
    
        //
        // Assume as a high speed device
        //
        dTmp    |= QH_HIGH_SPEED;   // 10b - High speed
    
        //
        // Check for high speed
        //
        if (dTmp1)
        {
            dTmp1   = (dTmp1 & 1) << 12;    // Bit 12 = full/low speed flag
            dTmp    &= ~(QH_ENDPOINT_SPEED);
            dTmp    |= dTmp1;
            //
            // Set the hub address and port number
            //
            dTmp1   = (UINT32)EHCI_GetHiSpeedHubPortNumber(fpDevInfo);
            dTmp1   = (dTmp1 << 16);    	// Hispeed hub port number & device number
            fpQHBulk->dEndPntCap    |= dTmp1;   // Split complete Xaction
        }
    
        //
        // Update the endpoint characteristcs field with the data formed
        //
        fpQHBulk->dEndPntCharac = dTmp;
    
        //
        // Fill the bulk data qTD with relevant information
        // The token field will be set so
        //   Direction PID = QTD_OUT_TOKEN/QTD_IN_TOKEN,
        //   Size = size of the data,
        //   Data Toggle = bDatToggle,
        //   Error Count = QTD_THREE_ERRORS,
        //   Status code = QTD_DO_OUT(if it is out) + QTD_ACTIVE
        // The buffer pointers field will point to the fpBuffer buffer
        //   which was before initialized to contain a DeviceRequest struc.
        // The dNextqTDPtr field will point to the qTDControlSetup
        // The dAltNextqTDPtr field will be set to EHCI_TERMINATE
        //
        if (bXferDir & BIT7) {
            fpQTDBulkData->dToken   = QTD_IN_TOKEN |
                    QTD_IOC_BIT |
                    QTD_THREE_ERRORS | QTD_ACTIVE;
        } else {
            fpQTDBulkData->dToken   = QTD_OUT_TOKEN |
                    QTD_IOC_BIT |
                    QTD_THREE_ERRORS | QTD_DO_OUT | QTD_ACTIVE;
            if (TempBuffer != NULL) {
                MemCpy(BufPhyAddr, TempBuffer, dBytesToTransfer);
            }            
        }
    
        //
        // Set the data toggle depending on the bDatToggle value
        //
        fpQTDBulkData->dToken   |= (UINT32)bDatToggle << 31;
    
        //
        // Set length
        //
        fpQTDBulkData->dToken   |= (dBytesToTransfer << 16);
    
        //
        // Update buffer pointers
        //
        if (TempBuffer != NULL) {
            EHCISetQTDBufferPointers(fpQTDBulkData, TempBuffer, dBytesToTransfer);
        } else {
            EHCISetQTDBufferPointers(fpQTDBulkData, BufPhyAddr, dBytesToTransfer);
        }
    
        //
        // Update next & alternate next qTD pointers
        //
        fpQTDBulkData->dNextqTDPtr      = EHCI_TERMINATE;
        fpQTDBulkData->dAltNextqTDPtr   = EHCI_TERMINATE;
    
        fpQHBulk->bActive   = TRUE;
    
    
        //
        // Set bulk condition as not stalled
        //
        gUsbData->bLastCommandStatus &= ~(USB_BULK_STALLED + USB_BULK_TIMEDOUT);
    
        //
        // Now wait for bulk transaction to be complete
        // the EHCIProcessInterrupt will set its active flag to FALSE.
        // Now wait for the bulk transfer to complete
        //
		Status = EhciExexuteAsyncSchedule(fpHCStruc, fpQHBulk);

		fpQHBulk->fpFirstqTD	= 0;
		fpQHBulk->dNextqTDPtr	= EHCI_TERMINATE;

		if (Status != USB_SUCCESS) {
			//
            // Set time out status
            //
            gUsbData->bLastCommandStatus |= USB_BULK_TIMEDOUT;
            gUsbData->dLastCommandStatusExtended  |= USB_TRNSFR_TIMEOUT;
			break;
		}

		if (fpQHBulk->bErrorStatus & QTD_HALTED) {
			//
			// Stall condition
			//
            gUsbData->bLastCommandStatus   &= ~(USB_BULK_TIMEDOUT);
            gUsbData->bLastCommandStatus   |= USB_BULK_STALLED;
            gUsbData->dLastCommandStatusExtended  |= USB_TRSFR_STALLED;
			break;
		}

        //
        // Update the data toggle value into the mass info structure
        //
        bDatToggle =
            (UINT8)(((fpQHBulk->dToken & QH_DATA_TOGGLE) >> 31) & 1);
		UsbUpdateDataToggle(fpDevInfo, bEndp | bXferDir, bDatToggle);

        //
        // Get the size of data transferred
        //
        dTmp = (fpQTDBulkData->dToken & ~(QTD_DATA_TOGGLE)) >> 16;
        dTmp = (dTmp)? dBytesToTransfer-dTmp : dBytesToTransfer;

        if (!dTmp) {
            break;
        }

        if (TempBuffer != NULL) {
            if (bXferDir & BIT7) {
                MemCpy(TempBuffer, BufPhyAddr, dTmp);
            }
        }

        //
        // Adjust loop variables
        //
        dBytesRemaining = dBytesRemaining - dTmp;
        dBytesTransferred += dTmp;

        if (dTmp < dBytesToTransfer) {
            break;
        }

        BufPhyAddr += dTmp;
    }

	EhciDmaUnmap(fpHCStruc, BufferMapping);
                                        //(EIP71067+)>
    EhciMemFree(fpHCStruc, fpQHBulk, GET_MEM_BLK_COUNT( (1 * sizeof(EHCI_QH)) +
                                             			(1 * sizeof(EHCI_QTD))));
                                        //<(EIP71067+)
    if (TempBuffer != NULL) {
        if (dwLength < HIGHSPEED_MAX_BULK_DATA_SIZE) {
            EhciMemFree(fpHCStruc, TempBuffer, GET_MEM_BLK_COUNT((UINT16)dwLength));     
        } else {
            EhciMemFree(fpHCStruc, TempBuffer, GET_MEM_BLK_COUNT(HIGHSPEED_MAX_BULK_DATA_SIZE));
        }
    }
    
    return  dBytesTransferred;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:    EHCI_InterruptTransfer
//
// Description: This function executes an interrupt transaction on the USB.
//              The data transfer direction is always DATA_IN. This
//              function wil not return until the request either completes
//              successfully or completes in error (due to time out, etc.)
//
// Parameters:  fpHCStruc   Pointer to HCStruc of the host controller
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
// Output:      Number of bytes transferred
//
//
// Notes:       DO NOT TOUCH THE LINK POINTER OF THE TDInterruptData. It is
//              statically allocated and linked with other items in the
//              1ms schedule
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
EHCI_InterruptTransfer (
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    UINT8       EndpointAddress,
    UINT16      MaxPktSize,
    UINT8       *fpBuffer,
    UINT16      wLength
)
{

    UINT8       bDatToggle;
    EHCI_QH     *fpQHInt;
    UINT32      dTmp, dTmp1;
    EHCI_QTD    *fpqTDIntData;
	UINT32		Count;
	UINT32		Timeout;
	UINT32		BytesTransferred;
	UINT8		*BufPhyAddr = NULL;
	VOID		*BufferMapping = NULL;
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
            USB_DEBUG(3, "Ehci InterruptTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    if (!(fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
        return 0;
    }

	if (EhciIsHalted(fpHCStruc)) {
		return 0;
	}

	gUsbData->dLastCommandStatusExtended = 0;

	bDatToggle = UsbGetDataToggle(fpDevInfo, EndpointAddress);

    //
    // Get the QHInterrupt pointer
    //
    fpQHInt = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT((1 * sizeof(EHCI_QH))+
                                             			(1 * sizeof(EHCI_QTD))));
	if (fpQHInt == NULL) {
		return 0;
	}

	fpqTDIntData = (EHCI_QTD*)((UINTN)fpQHInt + sizeof(EHCI_QH));

	//
	// Intialize the queue head
	//
	EHCIInitializeQueueHead(fpQHInt);

	//
	// Set the first qTD pointer
	//
	fpQHInt->fpFirstqTD	= fpqTDIntData;
	fpQHInt->dNextqTDPtr	= (UINT32)(UINTN)fpqTDIntData;
	fpQHInt->dLinkPointer	= EHCI_TERMINATE;

    //
    // Get Device address & Endpoint
    //
    dTmp = (UINT32)fpDevInfo->bDeviceAddress;
    dTmp |= (UINT32)(EndpointAddress & 0xF) << 8;

    //
    // Set max packet size
    //
    dTmp |= (UINT32)(MaxPktSize) << 16;

    //
    // Set the device speed, reset the device speed bits
    //
    dTmp1 = (UINT32)fpDevInfo->bEndpointSpeed;  // 00/01/10 for HI/LO/FULL

    //
    // Assume as a high speed device
    //
    dTmp |= QH_HIGH_SPEED;  // 10b - High speed

    //
    // Check for high speed
    //
    if (dTmp1)
    {
        dTmp1 = (dTmp1 & 1) << 12;  // Bit 12 = full/low speed flag
        dTmp &= ~(QH_ENDPOINT_SPEED);
        dTmp |= dTmp1;
        //
        // Set the hub address and port number
        //
        dTmp1 = (UINT32)EHCI_GetHiSpeedHubPortNumber(fpDevInfo);
        dTmp1 = (dTmp1 << 16) | BIT10 | BIT11 | BIT12;
        fpQHInt->dEndPntCap |= dTmp1;   // Split complete Xaction
    }
    //
    // Update the endpoint characteristcs field with the data formed
    //
    fpQHInt->dEndPntCharac = dTmp;
    fpQHInt->dEndPntCap |= (BIT0 | QH_ONE_XFER);    // Interrupt schedule mask
    fpQHInt->Interval = EhciTranslateInterval(fpDevInfo->bEndpointSpeed, 
                            fpDevInfo->bPollInterval);

    //
    // Set the data toggle depending on the bDatToggle value
    //
    fpQHInt->dToken |= (UINT32)bDatToggle << 31;

//
// Fill the interrupt data qTD with relevant information
// The token field will be set so
//   Direction PID = QTD_IN_TOKEN,
//   Size = size of the data,
//   Data Toggle = bDatToggle,
//   Error Count = QTD_THREE_ERRORS,
//   Status code = QTD_ACTIVE
// The buffer pointers field will point to the EDX
//   which was before initialized to contain a DeviceRequest struc.
// The dNextqTDPtr field will point to the qTDControlSetup
// The dAltNextqTDPtr field will be set to EHCI_TERMINATE
//
    fpqTDIntData->dToken = QTD_IOC_BIT | QTD_THREE_ERRORS | QTD_ACTIVE;
	if (EndpointAddress & BIT7) {
		fpqTDIntData->dToken |= QTD_IN_TOKEN;
	} else {
		fpqTDIntData->dToken |= QTD_OUT_TOKEN;
	}

    //
    // Set length
    //
    fpqTDIntData->dToken |= (UINT32)wLength << 16;
	
	EhciDmaMap(fpHCStruc, EndpointAddress & BIT7, fpBuffer, wLength, 
		&BufPhyAddr, &BufferMapping);
    //
    // Update buffer pointers
    //
    EHCISetQTDBufferPointers(fpqTDIntData, BufPhyAddr, (UINT32)wLength);

    //
    // Update next & alternate next qTD pointers
    //
    fpqTDIntData->dNextqTDPtr = EHCI_TERMINATE;
    fpqTDIntData->dAltNextqTDPtr = EHCI_TERMINATE;

    //
    // Schedule the QHInterrupt to 1msec schedule
    //
    EhciAddPeriodicQh(fpHCStruc,fpQHInt);

	// Set the QH as active
	fpQHInt->bActive = TRUE;

    //
    // Now wait for interrupt transaction to be complete;
    // the EHCIProcessInterrupt will set its active flag to FALSE.
    //
	Timeout = gUsbData->wTimeOutValue * 100; // makes it number of 10 macrosecond units

	for (Count = 0; Timeout == 0 || Count < Timeout; Count++) {
		if (!(fpqTDIntData->dToken & QTD_ACTIVE)) {
			break;
		}
		FixedDelay(10);  // 60 microsec
	}
    //Status = EHCIWaitForTransferComplete(fpHCStruc, fpQHInt, fpDevInfo);

	// Remove the QH from periodic schedule
    EhciRemovePeriodicQh(fpHCStruc,(EHCI_QH*)fpQHInt);

    //
    // Check whether the QH stopped or timed out
    //
    BytesTransferred = 0;
	if (fpqTDIntData->dToken & QTD_ACTIVE) {
		USB_DEBUG (DEBUG_LEVEL_3, "EHCI Time-Out\n");
		gUsbData->dLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
	} else if (fpqTDIntData->dToken & QTD_HALTED) {
		gUsbData->dLastCommandStatusExtended  |= USB_TRSFR_STALLED;
	} else {
		BytesTransferred = (UINT16)(wLength - ((fpqTDIntData->dToken &
								~(QTD_DATA_TOGGLE)) >> 16));
		//
		// Update the data toggle value into the mass info structure
		//
		bDatToggle = (UINT8)(((fpQHInt->dToken & QH_DATA_TOGGLE) >> 31) & 1);
		UsbUpdateDataToggle(fpDevInfo, EndpointAddress, bDatToggle);
	}

	EhciDmaUnmap(fpHCStruc, BufferMapping);

	// Free the allocated QH and qTD
    EhciMemFree(fpHCStruc, fpQHInt, GET_MEM_BLK_COUNT((1 * sizeof(EHCI_QH)) +
                                            		  (1 * sizeof(EHCI_QTD))));

	// Service all interrupts
	EHCI_ProcessInterrupt(fpHCStruc);

    return (UINT16)BytesTransferred;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCI_DeactivatePolling
//
// Description: This function de-activates the polling QH for the requested
//              device. The device may be a USB keyboard or USB hub
//
// Input:       fpHCStruc   - Pointer to the HC structure
//              fpDevInfo   - Pointer to the device information structure
//
// Output:      USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_DeactivatePolling(
    HC_STRUC* fpHCStruc,
    DEV_INFO* fpDevInfo)
{
    UINT8   *fpPollED;
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

	if (EhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}

    //
    // Get a pointer to the device's QH from the poll QH pointer and remove
    // the polling ED from the schedule
    //
    fpPollED    = fpDevInfo->fpPollEDPtr;
	if(!fpPollED) return USB_ERROR;

	((EHCI_QH*)fpPollED)->bActive = FALSE;

    EhciRemovePeriodicQh(fpHCStruc,(EHCI_QH*)fpPollED); 

	UsbUpdateDataToggle(fpDevInfo, fpDevInfo->IntInEndpoint, 
		(UINT8)((((EHCI_QH*)fpPollED)->dToken & QH_DATA_TOGGLE) >> 31));

    EhciMemFree(fpHCStruc, fpPollED, GET_MEM_BLK_COUNT(sizeof(EHCI_QH)+sizeof(EHCI_QTD)));
    fpDevInfo->fpPollEDPtr  = NULL;
	fpDevInfo->fpPollTDPtr	= NULL;

	if(fpDevInfo->fpPollDataBuffer) {
		EhciMemFree(fpHCStruc, fpDevInfo->fpPollDataBuffer, 
						GET_MEM_BLK_COUNT(fpDevInfo->PollingLength)); 
    	fpDevInfo->fpPollDataBuffer = 0;
	}

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCI_ActivatePolling
//
// Description: This function activates the polling QH for the requested
//              device. The device may be a USB keyboard or USB hub
//
// Input:       fpHCStruc   - Pointer to the HC structure
//              fpDevInfo   - Pointer to the device information structure
//
// Output:      USB_ERROR on error, USB_SUCCESS on success
//
// Notes:       For the keyboard device this routine allocates TDRepeat
//              also, if it is not already allocated. This routine allocate
//              a polling TD and schedule it to 8ms schedule for keyboards
//              and to 1024ms schedule for hubs.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_ActivatePolling(
    HC_STRUC* fpHCStruc,
    DEV_INFO* fpDevInfo)
{
    EHCI_QH     *fpPollED; 
    EHCI_QTD    *fpPollTD;
    UINT32      dTmp, dTmp1;
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

    USB_DEBUG (DEBUG_LEVEL_3, "EHCI_AP dev type %d\n", fpDevInfo->bDeviceType);

	if (EhciIsHalted(fpHCStruc)) {
		return USB_ERROR;
	}

    //
    // Allocate a QH/qTD for polling QH & qTD
    //
    fpPollED = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT(
                                    sizeof(EHCI_QH)+sizeof(EHCI_QTD)));
    if (!fpPollED)
    {
        return  USB_ERROR;  // Memory allocation error
    }

    //
    // Save the pointers in DeviceInfo structure
    //
    fpDevInfo->fpPollEDPtr  = (UINT8*)fpPollED;
    fpPollTD    = (EHCI_QTD*)((UINTN)fpPollED + sizeof(EHCI_QH));
    fpDevInfo->fpPollTDPtr  = (UINT8*)fpPollTD;

//
// Setup the polling QH
// Set the QH's dNextqTDPtr field to polling qTD and dAltqTDPtr field to
// EHCI_TERMINATE
//

    fpPollED->fpFirstqTD    = fpPollTD;
    fpPollED->dNextqTDPtr   = (UINT32)(UINTN)fpPollTD;

    //
    // Intialize the queue head
    //
    fpPollED->dAltNextqTDPtr    = EHCI_TERMINATE;
    fpPollED->dLinkPointer      = EHCI_TERMINATE;

    //
    // Set the device info pointer in the QH
    //
    fpPollED->fpDevInfoPtr  = (UINT8*)fpDevInfo;

    //
    // Get Device address & Endpoint
    //
    dTmp = ((UINT32)fpDevInfo->bDeviceAddress)  |
                    ((UINT32)(fpDevInfo->IntInEndpoint & 0xF) << 8);

    dTmp |= ((UINT32)fpDevInfo->IntInMaxPkt) << 16; // Set max packet size	//(EIP54782)

    dTmp1   = (UINT32)fpDevInfo->bEndpointSpeed;    // 00/01/10 for HI/LO/FULL

    //
    // Assume as a high speed device
    //
    dTmp |= QH_HIGH_SPEED;  // 10b - High speed

    //
    // Check for high speed
    //
    if (dTmp1)
    {
        dTmp1 = (dTmp1 & 1) << 12;  // Bit 12 = full/low speed flag
        dTmp &= ~(QH_ENDPOINT_SPEED);
        dTmp |= dTmp1;
        //
        // Set the hub address and port number
        //
        dTmp1 = (UINT32)EHCI_GetHiSpeedHubPortNumber(fpDevInfo);
        dTmp1 = (dTmp1 << 16) | (BIT10 + BIT11 + BIT12);    // Split complete Xaction
        fpPollED->dEndPntCap    |= dTmp1;
    }

    //
    // Update the endpoint characteristcs field with the data formed
    //
    fpPollED->dEndPntCharac = dTmp;

    //
    // Set a bit in interrupt mask
    //
    fpPollED->dEndPntCap    |= (BIT0 + QH_ONE_XFER);
    fpPollED->Interval = EhciTranslateInterval(fpDevInfo->bEndpointSpeed, 
                                fpDevInfo->bPollInterval);

    //
    // Set the data toggle
    //
	fpPollED->dToken |= (UINT32)(UsbGetDataToggle(fpDevInfo, fpDevInfo->IntInEndpoint) << 31);

//
// Fill the polling qTD with relevant information
// The token field will be set so
//   Direction PID = QTD_IN_TOKEN,
//   Size = size of the data,
//   Data Toggle = QTD_DATA0_TOGGLE,
//   Error Count = QTD_THREE_ERRORS,
//   Status code = QTD_ACTIVE
// The buffer pointers field will point to the fpBuffer buffer
//   which was before initialized to contain a DeviceRequest struc.
// The dNextqTDPtr field will point to the qTDControlSetup
// The dAltNextqTDPtr field will be set to EHCI_TERMINATE
//
    fpPollTD->dToken = QTD_IN_TOKEN |
                    QTD_IOC_BIT |
                    QTD_THREE_ERRORS |
                    QTD_ACTIVE;
    //
    // Set length
    //
    fpPollTD->dToken |= (UINT32)fpDevInfo->PollingLength << 16;
    fpDevInfo->fpPollDataBuffer = EhciMemAlloc(fpHCStruc, 
									GET_MEM_BLK_COUNT(fpDevInfo->PollingLength)); 
	ASSERT(fpDevInfo->fpPollDataBuffer);

    //
    // Update buffer pointers
    //
    EHCISetQTDBufferPointers(fpPollTD,
                fpDevInfo->fpPollDataBuffer, fpDevInfo->PollingLength);

    //
    // Update next & alternate next qTD pointers
    //
    fpPollTD->dNextqTDPtr = EHCI_TERMINATE;
    fpPollTD->dAltNextqTDPtr = EHCI_TERMINATE;

    EhciAddPeriodicQh(fpHCStruc,fpPollED); 

	fpPollED->bCallBackIndex = USB_InstallCallBackFunction(EhciPollingTDCallback);
	fpPollED->bActive = TRUE;

    return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIDisableKeyRepeat
//
// Description: This function disables the keyboard repeat rate logic by
//              enabling the repeat TD
//
// Input:       fpHCStruc   - Pointer to the HCStruc structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_DisableKeyRepeat (
	HC_STRUC	*HcStruc
)
{
    EHCI_DESC_PTRS  *DescPtr;
	EHCI_QH		    *RepeatQh;
    EFI_STATUS      EfiStatus;
    UINT8           *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }
    
	if (EhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}
    
    DescPtr = HcStruc->stDescPtrs.fpEHCIDescPtrs;

    if (DescPtr == NULL) {
        return USB_ERROR;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (((UINT8*)DescPtr < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtr + sizeof(EHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }
#endif
    
    RepeatQh = DescPtr->fpQHRepeat;

    if (RepeatQh == NULL) {
        return USB_ERROR;
    }
    
#if USB_RUNTIME_DRIVER_IN_SMM
    if (((UINT8*)RepeatQh < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(RepeatQh + sizeof(EHCI_QH)) > MemBlockEnd)) {
        return USB_ERROR;
    }
#endif

	if (RepeatQh) {
		RepeatQh->dTokenReload = ((UINT32)8 << 16) | QTD_IN_TOKEN | QTD_ONE_ERROR;
		RepeatQh->bActive = FALSE;
	}
    return  USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:    EHCI_EnableKeyRepeat
//
// Description: This function disables the keyboard repeat rate logic by
//              enabling the repeat TD
//
// Parameters:  fpHCStruc   Pointer to the HCStruc structure
//
// Output:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCI_EnableKeyRepeat (
	HC_STRUC* HcStruc
)
{
    EHCI_DESC_PTRS      *DescPtr;
	EHCI_QH		        *RepeatQh;
	EHCI_QTD            *RepeatQtd;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->dHCFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }
    
	if (EhciIsHalted(HcStruc)) {
		return USB_ERROR;
	}

    DescPtr = HcStruc->stDescPtrs.fpEHCIDescPtrs;

    if (DescPtr == NULL) {
        return USB_ERROR;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (((UINT8*)DescPtr < gUsbData->fpMemBlockStart) ||
        ((UINT8*)(DescPtr + sizeof(EHCI_DESC_PTRS)) > MemBlockEnd)) {
        return USB_ERROR;
    }
#endif

    RepeatQh = DescPtr->fpQHRepeat;

	if (RepeatQh == NULL) {
		return USB_ERROR;
	}
    
#if USB_RUNTIME_DRIVER_IN_SMM
    if (((UINT8*)RepeatQh < gUsbData->fpMemBlockStart) ||
        (((UINT8*)RepeatQh + sizeof(EHCI_QH)) > MemBlockEnd)) {
        return USB_ERROR;
    }
#endif

	if ((RepeatQh->dTokenReload & QTD_ACTIVE) == 0) {
		RepeatQtd = DescPtr->fpqTDRepeat;
        if (RepeatQtd == NULL) {
            return USB_ERROR;
        }
#if USB_RUNTIME_DRIVER_IN_SMM
        if (((UINT8*)RepeatQtd < gUsbData->fpMemBlockStart) ||
            (((UINT8*)RepeatQtd + sizeof(EHCI_QTD)) > MemBlockEnd)) {
            return USB_ERROR;
        }
#endif
		RepeatQh->dTokenReload = ((UINT32)8 << 16) | QTD_IN_TOKEN | 
								QTD_ONE_ERROR | QTD_IOC_BIT | QTD_ACTIVE;

		// Update buffer pointers
		EHCISetQTDBufferPointers(RepeatQtd,
						&RepeatQh->aDataBuffer[0], 8);
		
		// Re-init the QH pointers
		RepeatQh->dCurqTDPtr = 0;
		RepeatQh->dAltNextqTDPtr = EHCI_TERMINATE;
		RepeatQh->dNextqTDPtr = (UINT32)(UINTN)RepeatQtd;
		
		//
		// Restart the qTD
		//
		RepeatQh->dToken = 0;
		RepeatQtd->dToken = RepeatQh->dTokenReload;

		RepeatQh->bActive = TRUE;
	}
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIResetHC
//
// Description: This function resets the EHCI controller
//
// Input:   Pointer to the HCStruc structure
//
// Output:  USB_SUCCESS     HC successfully reset
//          USB_ERROR       Error, error log is updated
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIResetHC(HC_STRUC* fpHCStruc)
{
    UINT16   count;

    if (fpHCStruc->DebugPort) return USB_SUCCESS;
    //
    // Check HC is halted: attempting to reset an actively running HC will
    // result in undefined behavior.
    //
    if (EhciReadOpReg(fpHCStruc, EHCI_USBSTS) & EHCI_HCHALTED)
    {
        //
        // Issue reset
        //
        EhciSetOpReg(fpHCStruc, EHCI_USBCMD, EHCI_HCRESET);

        //
        // EHCI_HCRESET bit is set to zero by the Host Controller when the reset
        // process is complete.
        //
        for (count = 0; count < 500; count++) {
            if (!(EhciReadOpReg(fpHCStruc, EHCI_USBCMD) & EHCI_HCRESET)) {
                return  USB_SUCCESS;
            }
            FixedDelay(100);     // 100 us delay
        }
    }

    //
    // Error - HC reset failed
    //
    USBLogError(USB_ERR_HC_RESET_FAILED);

    return  USB_ERROR;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIInitializesPeriodicSchedule
//
// Description: This function initializes the periodic schedules for the
//              EHCI host controller
//
// Input:       fpHCStruc   - HCStruc for the controller
//              dMemAddr    - Membase address
//
// Output:      USB_ERROR   On error
//              USB_SUCCESS On success
//
// Notes:   This routine creates 8ms and 32ms schedules
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIInitializePeriodicSchedule(
    HC_STRUC* fpHCStruc,
    UINT32 dMemBase)
{
    UINT8           *fpPtr;
    EHCI_DESC_PTRS  *fpDescPtr;
    //
    // Allocate descriptor structure and fill it in HCStruc
    //
    fpDescPtr = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT_STRUC(EHCI_DESC_PTRS));
    if (fpDescPtr == NULL) {
        USB_DEBUG(DEBUG_LEVEL_4, "EHCI Descriptor struc alloc failed. %d \n",
                                    GET_MEM_BLK_COUNT_STRUC(EHCI_DESC_PTRS));
        return USB_ERROR;
    }

    //
    // Save the value in the HC struc
    //
    fpHCStruc->stDescPtrs.fpEHCIDescPtrs = fpDescPtr;

    // Allocate QH/qTD for PeriodicQh
    fpPtr = EhciMemAlloc(fpHCStruc, GET_MEM_BLK_COUNT((1 * sizeof(EHCI_QH))+
													  (0 * sizeof(EHCI_QTD))));
    if (fpPtr == NULL) {
        USB_DEBUG(DEBUG_LEVEL_4, "Schedule of EHCI QH alloc failed.\n");
        return USB_ERROR;
    }
	
    // Save the 1 QH in appropriate location
    fpDescPtr->PeriodicQh = (EHCI_QH*)fpPtr;

    EHCIInitializeQueueHead(fpDescPtr->PeriodicQh);
    fpDescPtr->PeriodicQh->dNextqTDPtr = EHCI_TERMINATE;
    fpDescPtr->PeriodicQh->dAltNextqTDPtr = EHCI_TERMINATE;
    fpDescPtr->PeriodicQh->dEndPntCharac = ((UINT32)0x40 << 16) + QH_HIGH_SPEED;
    fpDescPtr->PeriodicQh->dLinkPointer      = EHCI_TERMINATE;
    fpDescPtr->PeriodicQh->dToken = QTD_HALTED;
    fpDescPtr->PeriodicQh->Interval = 1;

    EhciAddPeriodicQh(fpHCStruc, fpDescPtr->PeriodicQh);

    return  USB_SUCCESS;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIInitializeQueueHead
//
// Description: This function initializes the queue head with default values
//
// Input:       fpQH    Pointer to queue head
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
EHCIInitializeQueueHead(EHCI_QH *fpQH)
{
    fpQH->dNextqTDPtr       = 1;
    fpQH->dAltNextqTDPtr    = 1;
    fpQH->dCurqTDPtr        = 0;

    fpQH->dEndPntCap        = QH_ONE_XFER;
    fpQH->dToken            = 0;
    fpQH->dEndPntCharac     = 0;
    fpQH->dBufferPtr0       = 0;
    fpQH->dBufferPtr1       = 0;
    fpQH->dBufferPtr2       = 0;
    fpQH->dBufferPtr3       = 0;
    fpQH->dBufferPtr4       = 0;
    fpQH->bErrorStatus      = 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIStartPeriodicSchedule
//
// Description: This function starts the periodic schedule for the
//              EHCI host controller
//
// Input:       Pointer to HcStruc
//
// Output:      USB_ERROR   On error
//              USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIStartPeriodicSchedule(
    HC_STRUC* HcStruc
)
{
    UINT16  i;
    //
    // Start periodic schedule
    //
    EhciSetOpReg(HcStruc, EHCI_USBCMD, EHCI_PER_SCHED_ENABLE);

    //
    // Make sure the HC started the schedules
    //
    for (i = 0; i < 1000; i++) {
        if (EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_PER_SCHED_STATUS) {
            break;
        }
        FixedDelay(10);
    }
    if (!(EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_PER_SCHED_STATUS)) {
        return USB_ERROR;
    }
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIStopPeriodicSchedule
//
// Description: This function stops the periodic schedule for the
//              EHCI USB host controller
//
// Input:       HcStruc for the controller
//
// Output:      USB_ERROR   On error
//              USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIStopPeriodicSchedule(
    HC_STRUC* HcStruc
)
{
    UINT16  i;
    //
    // Stop periodic schedule
    //
    EhciClearOpReg(HcStruc, EHCI_USBCMD, EHCI_PER_SCHED_ENABLE);

    //
    // Make sure the HC stopped the schedules
    //
    for (i = 0; i < 1000; i++) {
        if (!(EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_PER_SCHED_STATUS)) {
            break;
        }
        FixedDelay(10);
    }
    if (EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_PER_SCHED_STATUS) {
        return USB_ERROR;
    }
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIStartAsyncSchedule
//
// Description: This function starts the asynchronous schedule
//
// Input:       Pointer to HcStruc
//
// Output:      USB_ERROR   On error
//              USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIStartAsyncSchedule(
    HC_STRUC* HcStruc
)
{
    UINT16  i;
    //
    // Start the Async schedule
    //
    EhciSetOpReg(HcStruc, EHCI_USBCMD, EHCI_ASYNC_SCHED_ENABLE);

    //
    // Make sure the HC started the async. execution
    //
    for (i = 0; i < 1000; i++) {
        if (EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_ASYNC_SCHED_STATUS) {
            break;
        }
        FixedDelay(10);
    }
    if (!(EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_ASYNC_SCHED_STATUS)) {
        //
	    // Stop the host controller (Reset bit 0)
	    //
	    EhciClearOpReg(HcStruc, EHCI_USBCMD, EHCI_RUNSTOP);
        // The Host Controller must halt within 16 micro-frames after 
        // software clears the Run bit. 
        for (i = 0; i < 16; i++) {
            if (EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_HCHALTED) {
                break;
	        }
            FixedDelay(125);      // 125 us delay
		}
        return USB_ERROR;
    }
    
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIStopAsyncSchedule
//
// Description: This function stops the asynchronous transfer and sets the
//              asynchronous pointer to null
//
// Input:       Pointer to HcStruc
//
// Output:      USB_ERROR   On error
//              USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIStopAsyncSchedule(
    HC_STRUC* HcStruc
)
{
    UINT16  i;
    
	if (!(EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_ASYNC_SCHED_STATUS)) {
		return USB_SUCCESS;
	}

    //
    // Stop periodic schedule
    //
    EhciClearOpReg(HcStruc, EHCI_USBCMD, EHCI_ASYNC_SCHED_ENABLE);

    //
    // Make sure the HC stopped the async. execution
    //
    for (i = 0; i < 1000; i++) {
        if (!(EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_ASYNC_SCHED_STATUS)) {
            break;
        }
        FixedDelay(10);
    }
    if (EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_ASYNC_SCHED_STATUS) {
        //
	    // Stop the host controller (Reset bit 0)
	    //
	    EhciClearOpReg(HcStruc, EHCI_USBCMD, EHCI_RUNSTOP);
        // The Host Controller must halt within 16 micro-frames after 
        // software clears the Run bit. 
        for (i = 0; i < 16; i++) {
            if (EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_HCHALTED) {
                break;
	        }
            FixedDelay(125);      // 125 us delay
		}
        return USB_ERROR;
    }
    
    return USB_SUCCESS;
}

/*
#if EHCI_ASYNC_BELL_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIRemoveQHFromAsyncList
//
// Description: This function stops the asynchronous transfer and sets the
//      asynchronous pointer to null
//
// Input:   Pointer to HCStruc
//          Pointer to the Queue head that has to be removed
//          from the asynchronous schedule
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
EHCIRemoveQHFromAsyncList(
    HC_STRUC    *fpHCStruc,
    EHCI_QH     *fpQH
)
{
    //
    // Stop the Async transfer
    //
    EHCIStopAsyncSchedule(fpHCStruc);

    //
    // Remove the queue head from the Async list
    //
    gUsbData->fpQHAsyncXfer->dLinkPointer  = fpQH->dLinkPointer;

    //
    // Pointer is advanced. The queue head is totally removed from the list!
    //
}
#endif
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIAddPeriodicQH
//
// Description: This function adds a QH to the frame list
//
// Input:   Pointer to the QH to be added
//          Absolute pointer to the frame list
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EhciAddPeriodicQh(
    HC_STRUC    *HcStruc,
    EHCI_QH     *NewQh
)
{
    UINT16      Index;
    UINT32      *PrevPtr;
    UINT32      LinkPtr;
    EHCI_QH     *Qh;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (NewQh == NULL || NewQh->Interval == 0) {
        return USB_ERROR;
    }

    for (Index = HcStruc->SplitPeriodicIndex; Index < HcStruc->wAsyncListSize; Index += NewQh->Interval) {
        PrevPtr = &HcStruc->fpFrameList[Index];
        LinkPtr = *PrevPtr; 
        while (!(LinkPtr & EHCI_TERMINATE)){
            Qh = (EHCI_QH*)(LinkPtr & EHCI_POINTER_MASK);
#if USB_RUNTIME_DRIVER_IN_SMM
            Status = AmiValidateMemoryBuffer((VOID*)Qh, sizeof(EHCI_QH));
            if (EFI_ERROR(Status)) {
                return USB_ERROR;
            }
#endif
            if (Qh->Interval <= NewQh->Interval) {
                break;
            }
            PrevPtr = &Qh->dLinkPointer;
            LinkPtr = *PrevPtr; 
        }

        if (!(LinkPtr & EHCI_TERMINATE) && (Qh == NewQh)) {
            continue;
        }
#if USB_RUNTIME_DRIVER_IN_SMM
        Status = AmiValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
        if (EFI_ERROR(Status)) {
            return USB_ERROR;
        }
#endif
        NewQh->dLinkPointer = *PrevPtr;
        *PrevPtr = (UINT32)((UINTN)NewQh | EHCI_QUEUE_HEAD);

    }

    if (HcStruc->SplitPeriodicIndex == MAX_SPLIT_PERIODIC_NUMBER) {
        HcStruc->SplitPeriodicIndex = 0;
    } else {
        HcStruc->SplitPeriodicIndex++;
    }

    return USB_SUCCESS;
} 


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EhciRemovePeriodicQh
//
// Description: This function removes a QH from the frame list
//
// Input:   Pointer to the QH to be added
//          Absolute pointer to the frame list
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EhciRemovePeriodicQh (
    HC_STRUC    *HcStruc,
    EHCI_QH     *RetiredQh
)
{
    UINT16      Index;
    UINT32      *PrevPtr;
    UINT32      LinkPtr;
    EHCI_QH     *Qh;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (RetiredQh == NULL || RetiredQh->Interval == 0) {
        return USB_ERROR;
    }

    EHCIStopPeriodicSchedule(HcStruc);

    for (Index = 0; Index < HcStruc->wAsyncListSize; Index++) {
        PrevPtr = &HcStruc->fpFrameList[Index];
        LinkPtr = *PrevPtr; 
 
        while (!(LinkPtr & EHCI_TERMINATE)){
            Qh = (EHCI_QH*)(LinkPtr & EHCI_POINTER_MASK);
#if USB_RUNTIME_DRIVER_IN_SMM
            Status = AmiValidateMemoryBuffer((VOID*)Qh, sizeof(EHCI_QH));
            if (EFI_ERROR(Status)) {
                return USB_ERROR;
            }
#endif
            if (Qh == RetiredQh) {
                break;
            }
            PrevPtr = &Qh->dLinkPointer;
            LinkPtr = *PrevPtr; 
        }

        if (LinkPtr & EHCI_TERMINATE) {
            continue;
        }
#if USB_RUNTIME_DRIVER_IN_SMM
        Status = AmiValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
        if (EFI_ERROR(Status)) {
            return USB_ERROR;
        }
#endif
        *PrevPtr = RetiredQh->dLinkPointer;
    }

    RetiredQh->dLinkPointer = EHCI_TERMINATE;

    EHCIStartPeriodicSchedule(HcStruc);

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCISetQTDBufferPointers
//
// Description: This function will set the 5 buffer pointer in the qTD
//              appropriately depending upon the input size
//
// Input:   fpQtd   - Pointer to the qTD
//          fpBuf   - 32bit absolute buffer pointer
//          wSize   - Amount of data to be transferred
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
EHCISetQTDBufferPointers(
    EHCI_QTD    *fpQtd,
    UINT8       *fpBuf,
    UINT32      dSize
)
{
    UINT16      wBufSize;
    UINT8       *fpBuffer   = fpBuf;
    UINT32      *fpBufferPtr;
    UINT16      w4KRemainder;

    //
    // Fill the buffer pointers with 0s
    //
    fpQtd->dBufferPtr0      = 0;
    fpQtd->dBufferPtr1      = 0;
    fpQtd->dBufferPtr2      = 0;
    fpQtd->dBufferPtr3      = 0;
    fpQtd->dBufferPtr4      = 0;
    fpQtd->dAltNextqTDPtr   = 1;

    //
    // If size to transfer is 0 skip updating pointers
    //
    if (!dSize)
    {
        return;
    }

    //
    // Make sure the amount of data to be xferred is 16K or less
    //
    wBufSize = (UINT16)((dSize > MAX_EHCI_DATA_SIZE) ? MAX_EHCI_DATA_SIZE : dSize);

    fpBufferPtr = &fpQtd->dBufferPtr0;

    for (;;)
    {
        *fpBufferPtr = (UINT32)(UINTN)fpBuffer;
        //
        // Calculate the number of bytes that can be transferred using current
        // buffer pointer
        //
        w4KRemainder = (UINT16)((((UINT32)((UINTN)fpBuffer+0x1000)) & 0xFFFFF000) -
                                        (UINT32)(UINTN)fpBuffer);

        //
        // Check whether all the bytes can be accomadated in the current buffer
        //
        if (w4KRemainder >= wBufSize)
        {
            break;  // Yes. Current Buffer is sufficient for the rest of data
        }

        //
        // We have more data to transfer - adjust data and store it in the next pointer
        //
        wBufSize = (UINT16)(wBufSize - w4KRemainder);   // Amount of data remaining
        fpBuffer = fpBuffer + w4KRemainder;     // Adjust buffer (4K bound)
        fpBufferPtr++;                          // Next buffer pointer
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIWaitForTransferComplete
//
// Description: This function waits until the requested QH completes or
//              the transaction time-out
//
// Input:   fpHCStruc   - Pointer to HCStruc of the host controller
//          fpQH        - Pointer to the QH which has to be completed
//
// Output:  USB_ERROR   On error
//          USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
EHCIWaitForTransferComplete(
    HC_STRUC    *fpHCStruc,
    EHCI_QH     *fpQH,
    DEV_INFO*   fpDevInfo

)
{
    UINT32 dCount ;
    UINT32 countLimit = gUsbData->wTimeOutValue * 100; // makes it number of macrosecond units
	UINT16 Status = USB_ERROR;

    //
    // Check status change loop iteration
    //
    for(dCount = 0; !countLimit || dCount < countLimit; dCount++)
    {
        EHCIProcessQH(fpHCStruc, fpQH);
        if(fpQH->bActive == FALSE) {
            Status = USB_SUCCESS;
			break;
        }
        FixedDelay(10);  // 60 microsec
    }

	if(fpQH->bActive == TRUE) {
		// Set the QH as in-active
		fpQH->bActive = FALSE;
		Status = USB_ERROR;
    	USB_DEBUG (DEBUG_LEVEL_3, "EHCI Time-Out\n");
	}

	// Service all interrupts
	EHCI_ProcessInterrupt(fpHCStruc);
	
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIProcessQH
//
// Description: This function whether all the TD's in the QH is completed
//
// Input:       fpQH    - Pointer to the QH which has to be completed
//
// Output:      USB_ERROR   On error
//              USB_SUCCESS On success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EHCIProcessQH(
	HC_STRUC	*fpHCStruc,
	EHCI_QH		*fpQH
)
{
    EHCI_QTD *fpQTD = fpQH->fpFirstqTD;
    EFI_STATUS  Status = EFI_SUCCESS;

    for (;;) {
        if (fpQTD == NULL) {
            return USB_ERROR;
        }
#if USB_RUNTIME_DRIVER_IN_SMM
        Status = AmiValidateMemoryBuffer((VOID*)fpQTD, sizeof(EHCI_QTD));
        if (EFI_ERROR(Status)) {
            return USB_ERROR;
        }
#endif
        //
        // Check whether the qTD is active, if so. Exit!
        //
        if (fpQTD->dToken & QTD_ACTIVE) {
            return  USB_ERROR;
        }

        //
        // Check for halt condition, if halted - exit
        //
        if (fpQTD->dToken & QTD_HALTED) {
            //
            // Set the QH halted status
            //
            fpQH->bErrorStatus = QTD_HALTED;
            //
            // Set the QH as in-active
            //
            fpQH->bActive = FALSE;
			break;
        }
        //
        // qTD is not active and not halted. That is it is completed successfully
        // Check whether this qTD is the last one in the list
        //
        if (fpQTD->dNextqTDPtr & EHCI_TERMINATE) {
            //
            // Set the QH as in-active
            //
            fpQH->bActive = FALSE;
            break;
        }

        //
        // More qTDs are in the list. Process next qTD
        //
        fpQTD = (EHCI_QTD*)(UINTN)fpQTD->dNextqTDPtr;
    }

	if ((fpQH->bCallBackIndex) && (fpQH->bCallBackIndex <= MAX_CALLBACK_FUNCTION)) {
		if (gUsbData->aCallBackFunctionTable[fpQH->bCallBackIndex - 1]) {
            if ((gUsbData->aCallBackFunctionTable[fpQH->bCallBackIndex - 1])
                != EhciRepeatTDCallback) {
                Status = UsbDevInfoValidation((DEV_INFO*)fpQH->fpDevInfoPtr);

                if (EFI_ERROR(Status)) {
                    return USB_ERROR;
                }
            }
			(*gUsbData->aCallBackFunctionTable[fpQH->bCallBackIndex - 1])
							(fpHCStruc, (DEV_INFO*)fpQH->fpDevInfoPtr, 
							(UINT8*)fpQH, NULL, 0);
		}
	}

	return  USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIProcessPeriodicList
//
// Description: This function parses through the periodic list to find
//              completed qTD.  If a qTD is done it will call its associated
//              call back function (in device info structure) and restarts
//              the polling qTD
//
// Input:   fpHCStruc   - Pointer to HCStruc of the host controller
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
EHCIProcessPeriodicList(
	HC_STRUC	*HcStruc
)
{
    UINT16      Index;
    UINT32      *PrevPtr;
    UINT32      LinkPtr;
    EHCI_QH     *Qh;
    UINT32      OrgQhLinkPointer;
    EFI_STATUS  Status = EFI_SUCCESS;


    //
    // Get the first entry in the periodic list. This QH list will link to all
    // the periodic QH's
    //

    for (Index = 0; Index <= MAX_SPLIT_PERIODIC_NUMBER; Index ++) {
        PrevPtr = &HcStruc->fpFrameList[Index];
        LinkPtr = *PrevPtr; 

	    while (!(LinkPtr & EHCI_TERMINATE)) {
		    Qh = (EHCI_QH*)(LinkPtr & EHCI_POINTER_MASK);
#if USB_RUNTIME_DRIVER_IN_SMM
            Status = AmiValidateMemoryBuffer((VOID*)Qh, sizeof(EHCI_QH));
            if (EFI_ERROR(Status)) {
                return;
            }
#endif
	        // Process only QHeads, skip the other types
	        if ((Qh->dLinkPointer & 6) == EHCI_QUEUE_HEAD) {

    		    // Check whether this QH is actived
    		    if (Qh->bActive == TRUE) {
                    OrgQhLinkPointer = Qh->dLinkPointer;		
    			    EHCIProcessQH(HcStruc, Qh);
                    // Qh is changed, we re-parses through the list.
                    if (Qh->dLinkPointer != OrgQhLinkPointer) {
                        LinkPtr = *PrevPtr;
                        continue;
                    }
    		    }
            }

		    LinkPtr = Qh->dLinkPointer;
	    }

    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EhciPollingTDCallback
//
// Description: This function is called when a polling TD from the TD pool 
//				completes an interrupt transaction to its assigned device.
//  			This routine should process any data in the TD's data buffer, 
//				handle any errors, and then copy the TD's CSReloadValue field 
//				into its control status field to put the TD back into service.
//
// Input:       HcStruc   Pointer to the HCStruc structure
//				DevInfo   NULL (pDevInfo is not valid)
//              QueueHead Pointer to the QH that completed
//  			Buffer    Not used
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EhciPollingTDCallback(
    HC_STRUC	*HcStruc,
    DEV_INFO	*DevInfo,
    UINT8		*QueueHead,
    UINT8		*Buffer,
    UINT16      DataLength
)
{
	EHCI_QH*	PollQh = (EHCI_QH*)QueueHead;
	EHCI_QTD    *PollQtd = PollQh->fpFirstqTD;
    UINT16      BytesTransferred;
    EFI_STATUS  Status = EFI_SUCCESS;

#if USB_RUNTIME_DRIVER_IN_SMM
    Status = AmiValidateMemoryBuffer((VOID*)PollQtd, sizeof(EHCI_QTD));
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }
#endif

	// Update datat toggle value
	UsbUpdateDataToggle(DevInfo, DevInfo->IntInEndpoint, 
		(UINT8)((PollQh->dToken & QH_DATA_TOGGLE) >> 31));

	if (!(PollQh->dToken & QTD_STATUS_FIELD)) {
        if ((DevInfo->bCallBackIndex) && (DevInfo->bCallBackIndex <= MAX_CALLBACK_FUNCTION)) {
    		if (gUsbData->aCallBackFunctionTable[DevInfo->bCallBackIndex-1]) {
                //
                // Get the size of data transferred
                //
                BytesTransferred = DevInfo->PollingLength - (UINT16)((PollQtd->dToken & ~(QTD_DATA_TOGGLE)) >> 16);
    			(*gUsbData->aCallBackFunctionTable[DevInfo->bCallBackIndex-1])
    					(HcStruc, DevInfo, (UINT8*)PollQtd, DevInfo->fpPollDataBuffer, BytesTransferred);
    		}
        }
	}

    // Keep the PID code bit in the qTD
    PollQtd->dToken &= QTD_DIRECTION_PID;
    
    //
    // Set length
    //
	PollQtd->dToken |= (UINT32)DevInfo->PollingLength << 16;

    //
    // Update buffer pointers
    //
	EHCISetQTDBufferPointers(PollQtd,
					DevInfo->fpPollDataBuffer, DevInfo->PollingLength);

    //
    // Re-init the QH pointers
    //
    PollQh->dToken &= QH_DATA_TOGGLE; 
    PollQh->dCurqTDPtr = 0;
    PollQh->dAltNextqTDPtr = EHCI_TERMINATE;
    PollQh->dBufferPtr0 = 0;
    PollQh->dBufferPtr1 = 0;
    PollQh->dBufferPtr2 = 0;
    PollQh->dBufferPtr3 = 0;
    PollQh->dBufferPtr4 = 0;
    //
    // Update next & alternate next qTD pointers
    //
    PollQtd->dNextqTDPtr = EHCI_TERMINATE;
    PollQtd->dAltNextqTDPtr = EHCI_TERMINATE;
    PollQh->dNextqTDPtr = (UINT32)(UINTN)PollQtd;

    //
    // Restart the qTD
    //
    PollQtd->dToken |= (QTD_IOC_BIT | QTD_THREE_ERRORS | QTD_ACTIVE);
	PollQh->bActive = TRUE;
	
    return  USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EHCIRepeatTDCallback
//
// Description: This function is called when qTdRepeat completes
//              a transaction.  This qTD runs a dummy interrupt transaction
//              to a non-existant device address for the purpose of
//              generating a periodic timeout interrupt which in turn
//              is used to generate keyboard repeat or update LED status.
//
// Input:       HcStruc   Pointer to the HCStruc structure
//				DevInfo   NULL (pDevInfo is not valid)
//              QueueHead Pointer to the QH that completed
//  			Buffer    Not used
//
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
EhciRepeatTDCallback(
	HC_STRUC	*HcStruc,
	DEV_INFO	*DevInfo,
	UINT8		*QueueHead,
	UINT8		*Buffer,
	UINT16      DataLength
)
{
	EHCI_QH		*RepeatQh = (EHCI_QH*)QueueHead;
	EHCI_QTD	*RepeatQtd = RepeatQh->fpFirstqTD;
    EFI_STATUS  Status = EFI_SUCCESS;

#if USB_RUNTIME_DRIVER_IN_SMM
    Status = AmiValidateMemoryBuffer((VOID*)RepeatQtd, sizeof(EHCI_QTD));
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }
#endif

#if USB_DEV_KBD
	USBKBDPeriodicInterruptHandler(HcStruc);
#endif

	if (RepeatQh->dTokenReload & QTD_ACTIVE) {
		//
		// Update buffer pointers
		//
		EHCISetQTDBufferPointers(RepeatQtd,
						&RepeatQh->aDataBuffer[0], 8);

		//
		// Re-init the QH pointers
		//
        RepeatQh->dToken &= QH_DATA_TOGGLE;
        RepeatQh->dCurqTDPtr = 0;
        RepeatQh->dAltNextqTDPtr = EHCI_TERMINATE;
        RepeatQh->dBufferPtr0 = 0;
        RepeatQh->dBufferPtr1 = 0;
        RepeatQh->dBufferPtr2 = 0;
        RepeatQh->dBufferPtr3 = 0;
        RepeatQh->dBufferPtr4 = 0;
		RepeatQh->dNextqTDPtr = (UINT32)(UINTN)RepeatQtd;

	    //
	    // Restart the qTD
	    //
		RepeatQh->dToken = 0;
		RepeatQtd->dToken = RepeatQh->dTokenReload;
		
		RepeatQh->bActive = TRUE;
	}

    return  USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EhciIsHalted
//
// Description: This function check whether HC is halted.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
EhciIsHalted (
	HC_STRUC	*HcStruc
)
{
	return (EhciReadOpReg(HcStruc, EHCI_USBSTS) & EHCI_HCHALTED) == EHCI_HCHALTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EhciTranslateInterval
//
// Description: This function calculates the polling rate in frames unit.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
EhciTranslateInterval(
    UINT8   Speed,
    UINT8   Interval
)
{
    UINT8   BitCount = 0;
    UINT16  PollingRate = 0;

    if (Speed == USB_PORT_STAT_DEV_HISPEED) {
        // For high-speed interrupt endpoints, the Interval value must be 
        // from 1 to 16
        ASSERT(Interval >= 1 && Interval <= 16);
 
        PollingRate = (1 << (Interval - 1)) >> 3;
        return PollingRate != 0 ? PollingRate : 1;
    }

    // For full-/low-speed interrupt endpoints, the Interval value should 
    // be from 1 to 255
    ASSERT(Interval >= 1 && Interval <= 255);

    for (BitCount = 0; Interval != 0; BitCount++) {
        Interval >>= 1;
    }
    return (1 << (BitCount - 1));
}

//==========================================================================

UINT32
EhciReadPciReg(
	HC_STRUC	*HcStruc,
	UINT32		Offset
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
	return ReadPCIConfig(HcStruc->wBusDevFuncNum, Offset);
#else
	EFI_STATUS	Status;
	UINT32		Data = 0;
	EFI_PCI_IO_PROTOCOL	*PciIo = HcStruc->PciIo;

	Status = PciIo->Pci.Read (
			 PciIo,
			 EfiPciIoWidthUint32,
			 Offset,
			 1,
			 &Data);
	ASSERT_EFI_ERROR(Status);
	return Data;
#endif
}


VOID
EhciWritePciReg(
	HC_STRUC	*HcStruc,
	UINT32		Offset,
	UINT32		Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
	DwordWritePCIConfig(HcStruc->wBusDevFuncNum, Offset, Data);
	return;
#else
	EFI_STATUS	Status;
	EFI_PCI_IO_PROTOCOL	*PciIo = HcStruc->PciIo;

	Status = PciIo->Pci.Write (
			 PciIo,
			 EfiPciIoWidthUint32,
			 Offset,
			 1,
			 &Data);
	ASSERT_EFI_ERROR(Status);
	return;
#endif
}

UINT32
EhciReadHcMem(
	HC_STRUC	*HcStruc,
	UINT32		Offset
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    if (Offset > HcStruc->BaseAddressSize) {
        return 0;
    }
	return DwordReadMem((UINT32)HcStruc->BaseAddress, Offset);
#else
	EFI_STATUS	Status;
	UINT32		Data = 0;
	EFI_PCI_IO_PROTOCOL	*PciIo = HcStruc->PciIo;

	Status = PciIo->Mem.Read (
			 PciIo,
			 EfiPciIoWidthUint32,
			 0,
			 Offset,
			 1,
			 &Data);
	ASSERT_EFI_ERROR(Status);
	return Data;
#endif
}

VOID
EhciWriteHcMem(
	HC_STRUC	*HcStruc,
	UINT32		Offset,
	UINT32		Data
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    if (Offset > HcStruc->BaseAddressSize) {
        return;
    }
	DwordWriteMem((UINT32)HcStruc->BaseAddress, Offset, Data);
	return;
#else
	EFI_STATUS	Status;
	EFI_PCI_IO_PROTOCOL	*PciIo = HcStruc->PciIo;

	Status = PciIo->Mem.Write (
			 PciIo,
			 EfiPciIoWidthUint32,
			 0,
			 Offset,
			 1,
			 &Data);
	ASSERT_EFI_ERROR(Status);
	return;
#endif
}

UINT32
EhciReadOpReg(
	HC_STRUC	*HcStruc,
	UINT32		Offset
)
{
	return EhciReadHcMem(HcStruc, HcStruc->bOpRegOffset + Offset);
}

VOID
EhciWriteOpReg(
	HC_STRUC	*HcStruc,
	UINT32		Offset,
	UINT32		Data
)
{
	EhciWriteHcMem(HcStruc, HcStruc->bOpRegOffset + Offset, Data);
	return;
}

VOID
EhciSetOpReg(
	HC_STRUC	*HcStruc,
	UINT32		Offset,
	UINT32		Bit
)
{
	UINT32	Data;

	Data = EhciReadOpReg(HcStruc, Offset) | Bit;
	EhciWriteOpReg(HcStruc, Offset, Data);
	return;
}

VOID
EhciClearOpReg(
	HC_STRUC	*HcStruc,
	UINT32		Offset,
	UINT32		Bit
)
{
	UINT32	Data;

	Data = EhciReadOpReg(HcStruc, Offset) & ~Bit;
	EhciWriteOpReg(HcStruc, Offset, Data);
	return;
}

UINT32
EhciReadDebugReg(
	HC_STRUC	*HcStruc,
	UINT8		BarIndex,
	UINT32		Offset
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
	UINT8  BarOffset[6] = {0x10, 0x14, 0x18, 0x1C, 0x20, 0x24};
	UINT32 DebugPortsMem;

    DebugPortsMem = EhciReadPciReg(HcStruc, BarOffset[BarIndex]);
	return DwordReadMem(DebugPortsMem, Offset);
#else
	EFI_STATUS	Status;
	UINT32		Data = 0;
	EFI_PCI_IO_PROTOCOL	*PciIo = HcStruc->PciIo;

	Status = PciIo->Mem.Read (
			 PciIo,
			 EfiPciIoWidthUint32,
			 BarIndex,
			 Offset,
			 1,
			 &Data);
	ASSERT_EFI_ERROR(Status);
	return Data;
#endif
}

VOID*
EhciMemAlloc(
	HC_STRUC	*HcStruc,
	UINT16		NumBlks
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
	return USB_MemAlloc(NumBlks);
#else
	UINT32	SavedMemPages = gUsbData->MemPages;
	UINT8	*SavedMemPool = gUsbData->fpMemBlockStart;
	UINT32	SavedMemBlkStsBytes = gUsbData->MemBlkStsBytes;
	UINT32	*SavedMemBlsSts = gUsbData->aMemBlkSts;
	VOID*	MemPtr;

	gUsbData->MemPages = HcStruc->MemPoolPages;
	gUsbData->fpMemBlockStart = HcStruc->MemPool;
	gUsbData->MemBlkStsBytes = HcStruc->MemBlkStsBytes;
	gUsbData->aMemBlkSts = HcStruc->MemBlkSts;

	MemPtr = USB_MemAlloc(NumBlks);

	gUsbData->MemPages = SavedMemPages;
	gUsbData->fpMemBlockStart = SavedMemPool;
	gUsbData->MemBlkStsBytes = SavedMemBlkStsBytes;
	gUsbData->aMemBlkSts = SavedMemBlsSts;

	return MemPtr;
#endif
}

VOID
EhciMemFree(
	HC_STRUC	*HcStruc,
	VOID*		MemPtr,
	UINT16		NumBlks
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
	USB_MemFree(MemPtr, NumBlks);
#else
	UINT32	SavedMemPages = gUsbData->MemPages;
	UINT8	*SavedMemPool = gUsbData->fpMemBlockStart;
	UINT32	SavedMemBlkStsBytes = gUsbData->MemBlkStsBytes;
	UINT32	*SavedMemBlsSts = gUsbData->aMemBlkSts;

	gUsbData->MemPages = HcStruc->MemPoolPages;
	gUsbData->fpMemBlockStart = HcStruc->MemPool;
	gUsbData->MemBlkStsBytes = HcStruc->MemBlkStsBytes;
	gUsbData->aMemBlkSts = HcStruc->MemBlkSts;

	USB_MemFree(MemPtr, NumBlks);

	gUsbData->MemPages = SavedMemPages;
	gUsbData->fpMemBlockStart = SavedMemPool;
	gUsbData->MemBlkStsBytes = SavedMemBlkStsBytes;
	gUsbData->aMemBlkSts = SavedMemBlsSts;

	return;
#endif
}

UINT8
EhciDmaMap(
	HC_STRUC	*HcStruc,
	UINT8		Direction,
	UINT8		*BufferAddr,
	UINT32		BufferSize,
	UINT8		**PhyAddr,
	VOID		**Mapping
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
	*PhyAddr = BufferAddr;
#else
	EFI_PCI_IO_PROTOCOL_OPERATION	Operation;
	EFI_PHYSICAL_ADDRESS	Addr;
	EFI_STATUS	Status;
	UINTN		Bytes = BufferSize;
	EFI_PCI_IO_PROTOCOL	*PciIo = HcStruc->PciIo;

	if (Direction & BIT7) {
		Operation = EfiPciIoOperationBusMasterWrite;
	} else {
		Operation = EfiPciIoOperationBusMasterRead;
	}

	Status = PciIo->Map (
				PciIo,
				Operation,
				BufferAddr,
				&Bytes,
				&Addr,
				Mapping
				);
	ASSERT_EFI_ERROR(Status);
	if (EFI_ERROR(Status) || Bytes != BufferSize) {
		return USB_ERROR;
	}

	*PhyAddr = (UINT8*)Addr;
#endif
	return USB_SUCCESS;
}

UINT8
EhciDmaUnmap(
	HC_STRUC	*HcStruc,
	VOID		*Mapping
)
{
#if !USB_RUNTIME_DRIVER_IN_SMM

	EFI_STATUS	Status;
	EFI_PCI_IO_PROTOCOL	*PciIo = HcStruc->PciIo;

	Status = PciIo->Unmap(PciIo, Mapping);
	ASSERT_EFI_ERROR(Status);
	if (EFI_ERROR(Status)) {
		return USB_ERROR;
	}
#endif
	return USB_SUCCESS;
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
