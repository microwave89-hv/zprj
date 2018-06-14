#pragma warning(disable: 4001)
#pragma warning(disable: 4127)
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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usb.c 183   10/21/16 1:48a Wilsonlee $
//
// $Revision: 183 $
//
// $Date: 10/21/16 1:48a $
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usb.c $
// 
// 183   10/21/16 1:48a Wilsonlee
// Fixed Cppcheck error.
// 
// 182   10/16/16 10:12p Wilsonlee
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
// 181   7/28/16 4:56a Wilsonlee
// [TAG]  		EIP264662
// [Category]  	Improvement
// [Description]  	Don't install usb hw smi after reconnecting usb
// controllers.
// [Files]  		uhcd.c, usb.c, ohci.c, amiusb.c, amiusbhc.c
// 
// 180   3/02/16 9:41p Wilsonlee
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
// 179   11/04/15 9:51p Wilsonlee
// [TAG]  		EIP241067
// [Category]  	Improvement
// [Description]  	Add the device descriptor to the DEV_INFO structure.
// [Files]  		usb.c, usbdef.h, xhci.c, usbbus.c, AmiUsbController.h
// 
// 178   9/01/15 10:17p Wilsonlee
// [TAG]  		EIP235482
// [Category]  	Improvement
// [Description]  	Select this alternate setting for multiple TTs hubs.
// [Files]  		usbhub.c, usb.c, amiusb.h, usbdef.h
// 
// 177   7/24/15 3:30a Wilsonlee
// [TAG]  		EIP229294
// [Category]  	Improvement
// [Description]  	If the device descriptor returns with a value in its
// length field that is greater 18, it is valid and we should ignore the
// extra bytes.
// [Files]  		usb.c
// 
// 176   5/28/15 4:29a Wilsonlee
// [TAG]  		EIP219785
// [Category]  	Improvement
// [Description]  	Suspend usb devices which are connected to Hubs.
// [Files]  		usb.c, usbdef.h
// 
// 175   4/29/15 11:26p Wilsonlee
// [TAG]  		EIP215031
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Transcend USB 3.0 HDD is disappeared in the setup menu by
// cold boot.
// [RootCause]  	We only can get SerialNumber string descriptor before
// setting configuration for this device, otherwise it is failed at
// getting this descriptor and inquiry command is also failed.
// [Solution]  	Retry inquiry command.
// [Files]  		usb.c, usbmass.c, efiusbmass.c, usbbus.c, usbdef.h
// 
// 174   4/27/15 2:25a Wilsonlee
// [TAG]  		EIP211855
// [Category]  	Improvement
// [Description]  	Set the default interface if the device has alternate
// setting for the interface.
// [Files]  		usb.c, usbdef.h
// 
// 173   4/07/15 4:03a Wilsonlee
// [TAG]  		EIP211598
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Keyboard/Mouse sometimes cannot work when connected to USB
// 3.0 HUB.
// [RootCause]  	It's failed at setting device address.
// [Solution]  	Wait 10 ms for stable before we set device address.
// [Files]  		usb.c
// 
// 172   3/08/15 10:49p Wilsonlee
// [TAG]  		EIP207774
// [Category]  	Improvement
// [Description]  	Set USB_FLAG_DRIVER_STARTED flag when HC is running and
// clear it if we don't start any HC.
// [Files]  		uhci.c, usb.c, ehci.c, ohci.c, xhci.c, amiusb.h
// 
// 171   2/16/15 2:44a Wilsonlee
// [TAG]  		EIP205373
// [Category]  	Improvement
// [Description]  	Cppcheck errors in Usb module.
// [Files]  		usb.c, usbport.c, uhcd.c, usbCCID.c
// 
// 170   1/22/15 10:19p Wilsonlee
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
// 169   12/15/14 2:16a Wilsonlee
// [TAG]  		EIP194720
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System shutdown delay when connect with cardreader.
// [RootCause]  	When we reenumerate devices, we still reserve the
// original device info, then we will use the wrong info to send command
// and the device may not respond.
// [Solution]  	Remove the present flag of devices before we reenumerate.
// [Files]  		usb.c
// 
// 168   11/23/14 10:09p Wilsonlee
// [TAG]  		EIP189293
// [Category]  	Improvement
// [Description]  	Implement XHCI key repeat function.
// [Files]  		usb.c, xhci.c , xhci.h, amiusb.c
// 
// 167   9/29/14 11:35p Wilsonlee
// [TAG]  		EIP181169
// [Category]  	Improvement
// [Description]  	Support XHCI 1.1/USB 3.1.
// [Files]  		xhci.c, xhci.h, usb.c, usbbus.c, usbdef.h, UsbHc.h
// 
// 166   9/02/14 3:53a Wilsonlee
// [TAG]  		EIP182567
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	POST B4h sometimes stays about 30 sec if using special
// KB/Ms.
// [RootCause]  	t's timeout in getting config or report descriptor
// commands.
// [Solution]  	Set the timeout to 500 ms.
// [Files]  		usb.c, usbhid.c, usbdef.h
// 
// 165   7/30/14 5:17a Wilsonlee
// [TAG]  		EIP176293
// [Category]  	Improvement
// [Description]  	The changes are for DisplayLink USB Network driver.
// [Files]  		usbbus.c, usb.c
// 
// 164   7/28/14 7:39a Wilsonlee
// [TAG]  		EIP176070
// [Category]  	Improvement
// [Description]  	Add 100 microseconds before we send get configuration
// descriptor command if the device is full speed.
// [Files]  		usb.c
// 
// 163   6/26/14 1:16a Wilsonlee
// [TAG]  		EIP173387
// [Category]  	Improvement
// [Description]  	Remove TODO comments.
// [Files]  		usbsetup.c, xhci.c, usbmass.c, usbCCID.c, usb.c, uhci.c,
// syskbc.c, usbport.c, usbbus.c, uhcd.c, UsbBotPeim.c, PeiXhci.c,
// PeiEhci.c
// 
// 162   6/20/14 2:11a Wilsonlee
// [TAG]  		EIP174589
// [Category]  	Improvement
// [Description]  	Fix build error if USB_HID_KEYREPEAT_USE_SETIDLE is 1.
// [Files]  		usb.c
// 
// 161   5/12/14 4:29a Wilsonlee
// [TAG]  		EIP168515
// [Category]  	New Feature
// [Description]  	Add the token "USB_CONTROLLERS_INITIAL_DELAY_LIST" if
// usb controllers need to delay for stabilization.
// [Files]  		usb.sdl, usb.c
// 
// 160   4/30/14 5:25a Wilsonlee
// [TAG]  		EIP164842
// [Category]  	Improvement
// [Description]  	Check if the devices have put into to our queue before
// we put them.
// [Files]  		UsbInt13.c, amiusb.c, ehci.c, ohci.c, usb.c, usbdef.h,
// usbmass.c, xhci.c, amiusbhc.c, efiusbmass.c, uhcd.c, usbbus.c, usbsb.c
// 
// 159   4/29/14 8:30p Wilsonlee
// [TAG]  		EIP164772
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System would auto wake up if USB hot-plug in S5 state via
// USB hub.
// [RootCause]  	The usb hubs have connnect / disconnect wakeup function
// if we send remote wakeup command
// [Solution]  	Don't send remote wakeup command to the usb hubs.
// [Files]  		usb.c
// 
// 158   2/26/14 1:55a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 157   11/26/13 1:23a Wilsonlee
// [TAG]  		EIP143251
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	The usb mouse lost if it behinds TI TUSB8040A1 hub under
// BIOS.
// [RootCause]  	The device may connect later, then we clear connect
// change without setting the device is connected.
// [Solution]  	Don't get port status again before we clear the changes.
// [Files]  		usb.c, usbhub.c
// 
// 156   11/04/13 3:26a Wilsonlee
// [TAG]  		EIP139714
// [Category]  	Improvement
// [Description]  	Improve the UsbIoPortReset function to support the xhci
// controller.
// [Files]  		usb.c
// 
// 155   9/04/13 5:46a Wilsonlee
// [TAG]  		EIP134478
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	The devices which behind the hub don't install successfully
// in shell.
// [RootCause]  	Find the wrong root hub port.
// [Solution]  	Check DEV_INFO_VALID_STRUC and DEV_INFO_DEV_PRESENT flag
// to find the root hub port.
// [Files]  		usb.c, xhci.c, usbbus.c
// 
// 154   8/16/13 4:17a Ryanchou
// 
// 153   8/02/13 6:16a Ryanchou
// 
// 152   7/29/13 5:19a Roberthsu
// [TAG]           EIP126741
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Cannot boot to uefi usb device with Sophos software.
// [RootCause]     When boot into tool. Ownership to os event occur.Usb
// will disconnect device.And record this disconnect event. Then ownership
// to bios,bios will connect all device.Run legacy to efi function. Bios
// run disconnect event first.Then reconnect device.Because usb key behind
// hub. So usb key disconnect also.
// [Solution]      Check device when device reconnect.If device and port
// number the same.Use the same device info.
// [Files]         usb.c,usbmass.c,efiusbmass.c,uhcd.c
// 
// 151   7/22/13 10:31p Wilsonlee
// [TAG]  		EIP125357
// [Category]  	Improvement
// [Description]  	Check if the port releases to a select host controller.
// [Files]  		uhci.c, usb.c, usbhub.c, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 150   7/17/13 4:14a Roberthsu
// [TAG]           EIP126319
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       TEAC floppy can not detect when cold boot.
// [RootCause]     Device need more delay after get config descriptor.
// [Solution]      Add delay to 1ms.
// [Files]         usb.c
// 
// 149   6/26/13 3:36a Roberthsu
// [TAG]           EIP125792
// [Category]      Bug Fix
// [Severity:]     Normal
// [Symptom:]      Keep function not work
// [Root Cause]    When check port change. We can not get baseclass.
// [Solution]      Add Vaild base class flag.
// [Files]         UsbPort.c,Usb.c
// 
// 148   5/01/13 9:54p Wilsonlee
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
// 147   4/19/13 12:44a Wilsonlee
// Fix build error if token USB_S5_WAKEUP_SUPPORT is enabled.
// 
// 146   4/18/13 11:22a Ryanchou
// Fix build error if token x64_BUILD is 0.
// 
// 145   3/19/13 3:58a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 144   3/15/13 5:57a Ryanchou
// 
// 143   3/15/13 4:59a Ryanchou
// [TAG]  		EIP117211
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB Memory Allocation Failure for Sizes Above 4k
// [RootCause]  	The variable count will be reset when across a page
// boundary.
// [Solution]  	Only reset the variable Count if the allocated blocks less
// than a page.
// [Files]  		usb.c
// 
// 142   3/07/13 9:25p Wilsonlee
// [TAG]  		EIP116044
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	TEAC FDD is not recognized after hot plugging under DOS.
// [RootCause]  	Setting the device configuration is failed.
// [Solution]  	This device configure successfully by that we set the
// device address after sending the first get-device-descriptor command.
// [Files]  		usb.c
// 
// 141   3/07/13 8:52a Ryanchou
// [TAG]  		EIP113218
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB keyboard cannot work after ownership change back to
// BIOS
// [RootCause]  	The key repeat SMI does not generated because the HC is
// stopped.
// [Solution]  	Use the other HC to generate key repeat SMI
// [Files]  		usb.c, usbhid.c, usbkbd.c
// 
// 140   1/23/13 8:33p Wilsonlee
// [TAG]  		EIP108891
// [Category]  	Improvement
// [Description]  	For usb wakp up function, we need to add some delay to
// wait the usb devces connect.
// [Files]  		usb.c
// 
// 139   1/22/13 2:38a Wilsonlee
// [TAG]  		EIP110305
// [Category]  	Improvement
// [Description]  	Set the device address after we send the first
// get-device-descriptor command.
// [Files]  		usbmass.c, usb.c, usbdef.h, usbbus.c, efiusbmass.c, uhcd.c,
// usbport.c
// 
// 138   1/11/13 4:15a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 137   12/05/12 4:23a Roberthsu
// [TAG]           EIP96616
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       When Legacy to EFI, USB KB can't be used.
// [RootCause]     Usb device driver content incorrect driver entry.Legacy
// insert a devicet,when legacy to efi,device does not install efi driver.
// [Solution]      When legacy to efi, scan device info table and put it
// to smiqueue.
// [Files]         usb.sdl,uhcd.c,usb.c
// 
// 136   11/29/12 7:47a Ryanchou
// [TAG]  		EIP107586 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Unplug USB keyboard does not uninstall EFI USB keyboard
// driver properly
// [RootCause]  	The EIP99431 changes clear DEV_INFO.bSubDeviceType in
// runtime keyboard driver, that cause EFI keyboard driver does not know
// what type of the device is.
// [Solution]  	Do not clear DEV_INFO.bSubDeviceType  in runtime keyboard
// driver.
// [Files]  		usb.c, usbhid.c, efiusbhid.c
// 
// 135   11/22/12 9:20p Wilsonlee
// [TAG]  		EIP106887
// [Category]  	New Feature
// [Description]  	Support usb S5 wake up function for UHCI.
// [Files]  		usb.c, uhci.c, uhci.h
// 
// 134   11/13/12 7:11a Wilsonlee
// [TAG]  		EIP82553
// [Category]  	New Feature
// [Description]  	Support usb S5 wake up function for XHCI.
// [Files]  		usb.c, ehci.c, ohci.c, xhci.c, xhci.h
// 
// 133   11/10/12 6:39a Ryanchou
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
// 132   10/25/12 4:14a Wilsonlee
// [TAG]  		EIP82354
// [Category]  	New Feature
// [Description]  	Support usb S5 wake up function for OHCI.
// [Files]  		usb.c, ehci.c, ohci.c
// 
// 131   9/28/12 2:38a Wilsonlee
// [TAG]  		EIP93154
// [Category]  	Improvement
// [Description]  	Change the unit of the FixedDelay from 15 us to 1 us.
// [Files]  		amiusb.h, xhci.c, ehci.c, ohci.c, uhci.c, usb.c, usbCCID.c,
// usbmass.c, usbhub.c, elib.c
// 
// 130   9/03/12 4:55a Roberthsu
// [TAG]           EIP98145
// [Category]      Improvement
// [Description]   Add skip function message.
// [Files]         usb.c,usbsrc.sdl
// 
// 129   8/29/12 9:32a Ryanchou
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
// 128   8/29/12 8:18a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 127   8/22/12 4:59a Wilsonlee
// [TAG]  		EIP98230
// [Category]  	Improvement
// [Description]  	Set the default of the MaxPacket for endpoint 0 by the
// device speed.
// [Files]  		usb.c
// 
// 126   6/13/12 2:39a Roberthsu
// [TAG]       EIP90124
// [Category]  Bug Fix
// [Severity]  Normal
// [Symptom]   Insert barcode when pxe option rom running.Barcode will not
// work under dos.
// [RootCause] Because pxe option under legacy mode.Back to efi mode
// barcode after reinit will fail under dos.
// [Solution]  In function USB_ReConfigDevice check device initial done.
// [Files]     usb.c
// 
// 125   5/22/12 10:04a Ryanchou
// [TAG]  		EIP90154
// [Category]  	Improvement
// [Description]  	Remove the USBSB_EnableSmmPeriodicSmi and
// USBSB_DisableSmmPeriodicSmi hooks.
// [Files]  		amidef.h, amiusb.c, usb.c, usbsb.c
// 
// 124   5/22/12 4:48a Wilsonlee
// [TAG]  		EIP89641
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB Keyboard driver overwrites INT0 vector (address 0:0)
// [RootCause]  	The Queue Head cross the page boundary.
// [Solution]  	Added page alignment restriction into memory allocation
// routine.
// [Files]  		usb.c
// 
// 123   5/04/12 6:40a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 122   5/04/12 5:27a Wilsonlee
// [TAG]  		EIP89307
// [Category]  	Improvement
// [Description]  	Modify incorrect #pragma pack directive.
// [Files]  		amidef.h, amiusb.c, ehci.h, ohci.c, ohci.h, uhci.h, usb.c,
// usbdef.h, xhci.h, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h,
// UsbIo.h
// 
// 121   4/24/12 3:36a Wilsonlee
// [TAG]  		EIP81761
// [Category]  	Improvement
// [Description]  	Determine the limit of devices after checking whether
// this device is reconnected.
// [Files]  		usb.c
// 
// 120   2/16/12 8:53p Wilsonlee
// [TAG]  		EIP81612
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Add EFI_USB_SPEED_SUPER in EFI_USB2_HC_PROTOCOL
// according to UEFI 2.3.1 spec
// [Files]  		usb.c, usbbus.c, amiusbhc.c
// 
// 119   1/13/12 4:24a Ryanchou
// [TAG]  		EIP47348
// [Category]  	New Feature
// [Description]  	Support for USB Port Reset function.
// [Files]  		amiusb.c, amiusb.h, amiusbhc.c, uhci.c, usb.c, usbbus.c,
// usbbus.h, usbmass.c
// 
// 118   1/04/12 6:23a Ryanchou
// 
// 117   1/04/12 6:22a Ryanchou
// [TAG]  		EIP78861
// [Category]  	Improvement
// [Description]  	Some device will be disconnected after port
// reset, and reconnected for a while, added 100 ms delay in this case.
// [Files]  		usb.c
// 
// 116   12/26/11 2:24a Roberthsu
// [TAG]           EIP74609
// [Category]      Improvement
// [Description]   Add check oemskiplist at check port change.
// [Files]         usbport.c,usb.c,AmiUsbController.h
// 
// 115   12/08/11 1:46a Ryanchou
// [TAG]  		EIP75441
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hangs at 0xB4 after restart from Win7
// [RootCause]  	The device does not use standard BOT protocol under
// Windows.
// [Solution]  	Add the device into bad device table.
// [Files]  		usb.c usbport.c
// 
// 114   11/28/11 8:36p Wilsonlee
// [TAG]  		EIP73803
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	The mouse can't work under setup after hot-plug.
// [RootCause]  	The device may fail at the get device descriptor or set
// device configuration.
// [Solution]  	Add 10 msec delay before getting device descriptor if the
// device is low or full speed and add 2 msec delay after setting the
// device's address.
// [Files]  		usb.c
// 
// 113   11/08/11 8:21a Wilsonlee
// [TAG]  		EIP74876
// [Category]  	New Feature
// [Description]  	Add USB API for shutdown single USB controller.
// [Files]  		amiusb.c, amiusb.h, usb.c, usbdef.h, uhcd.c, uhcd.h,
// AmiUsbController.h
// 
// 112   11/05/11 7:36a Wilsonlee
// [TAG]  		EIP64781
// [Category]  	New Feature
// [Description]  	Added SDL token
// SKIP_CARD_READER_CONNECT_BEEP_IF_NO_MEDIA that skip the connect beep if
// no media present in USB card reader.
// [Files]  		usbport.c, usbmass.c, usb.c, usbdef.h, uhcd.c, usbsrc.sdl
// 
// 111   10/25/11 8:23a Wilsonlee
// [TAG]  		EIP71750
// [Category]  	New Feature
// [Description]  	Support extraUSB device driver hook by elink.
// 
// 110   10/25/11 3:51a Ryanchou
// [TAG]  		EIP70933
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System hangs at checkpoint 0x98 when webcam plugged
// [RootCause]  	The webcam return invalid data in configuration
// descriptor.
// [Solution]  	Get the configuration descriptor twice, the first time is
// to receive the returned configure descriptor to get the total length
// and the second time is to feed the length to the function again.
// [Files]  		usb.c, usbdef.h
// 
// 109   8/08/11 6:59a Ryanchou
// [TAG]  		EIP54018
// [Category]  	New Feature
// [Description]  	Added USB S5 wake up support.
// [Files]  		amiusb.c, ehci.c, ohci.c, uhci.c, usb.c, usb.sdl, usbdef.h,
// usbsb.c xhci.c
// 
// 108   8/08/11 5:17a Ryanchou
// [TAG]  		EIP60561
// [Category]  	New Feature
// [Description]  	Add USB timing policy protocol for timing override.
// [Files]  		ehci.c, guids.c, ohci.c, uhcd.c, uhci.c usb.c, usbdef.h,
// usbhub.c, usbmass.c, UsbPolicy.h, usbport.c usbsrc.sdl
// 
// 107   8/05/11 6:18a Ryanchou
// [TAG]  		EIP60706
// [Category]  	Improvement
// [Description]  	Move gUsbBadDeviceTable into SMRAM.
// [Files]  		usbport.c, amiusb.c, usb.c, uhcd.c, AmiUsbController.h
// 
// 106   7/22/11 5:37a Ryanchou
// [TAG]  		EIP65385
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB mouse can not be detected.
// [RootCause]  	The device is connected in disconnect progress, port
// reset is not issued.
// [Solution]  	Remove the code that check device connection in disconnect
// progress.
// [Files]  		usb.c
// 
// 105   7/19/11 5:17a Ryanchou
// [TAG]  		EIP64498
// [Category]  	New Feature
// [Description]  	Implement EHCI key repeat function.
// [Files]  		ehci.c, ehci.h, usb.c, usbdef.h
// 
// 104   7/15/11 6:11a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c, usb.c, usbdef.h,
// usbkbd.c, usbkbd.h, usbms.c, usbrt.cif, usbsb.c, usbsetup.c,
// usbsrc.sdl, xhci.c
// 
// 103   7/13/11 2:47a Ryanchou
// [TAG]  		EIP60460
// [Category]  	Improvement
// [Description]  	Adds a flag when device disconnected during data
// transfer, BIOS will not issue a transfer to the devicce if this flag is
// set. This change is for Fresco USB 3.0 controller.
// [Files]  		usb.c, usbdef.h, xhci.c, xhci.h
// 
// 102   7/12/11 8:09a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
// 101   6/22/11 9:36a Ryanchou
// [TAG]  		EIP60640
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Logitec USB keyboard has no function in DOS.
// [RootCause]  	The USB keybaord may stall get configuration descriptor
// request or set address request.
// [Solution]  	Retry five times when the device stalls these request.
// [Files]  		usb.c, usbbus.c
// 
// 100   6/22/11 1:44a Ryanchou
// [TAG]  		EIP59738
// [Category]  	Improvement
// [Description]  	Support Block size other than 512 bytes USB HDD in UEFI
// mode.
// [Files]  		efiusbmass.c, uhci.c, usb.c, usbdef.h, usbmass.c
// 
// 99    6/21/11 9:33a Ryanchou
// [TAG]  		EIP59601
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB devices can't be detected if webcam is connected. 
// [RootCause]  	The configuration descriptor length is greater than
// buffer length, the causes the last descriptor is invalid.
// [Solution]  	If the next descriptor cross the buffer boundary, skip the
// descriptor.
// [Files]  		usb.c
// 
// 98    4/06/11 5:27a Tonylo
// [TAG]  		EIP52339
// [Category]  	New Feature
// [Description]  	USB changes of USB host safe disabling solution.
// 
// 97    4/06/11 1:33a Ryanchou
// [TAG]  		EIP54782
// [Category]  	Improvement
// [Description]  	Change polling data size of HID devices to max packet
// size of interrupt endpoint.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, xhci.c
// 
// 96    4/06/11 12:49a Ryanchou
// [TAG]  		EIP51653
// [Category]  	New Feature
// [Description]  	Added an interface that skips specific port
// enumeration.
// [Files]  		AmiUsbController.h, uhcd.c, uhcd.h, usb.c, usbdef.h,
// usbport.c
// 
// 95    3/30/11 8:13a Ryanchou
// [TAG]  		EIP54126
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Sometimes system hangs at checkpoint 0xB4.
// [RootCause]  	The bLength field of configuration descriptor is zero.
// [Solution]  	Check wether bLength field is zero before paring next
// descriptor.
// [Files]  		usb.c, usbbus.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c
// 
// 94    3/29/11 10:52p Ryanchou
// [TAG]  		EIP55401
// [Category]  	Improvement
// [Description]  	Improve the USB 3.0 device compatibility.
// [Files]  		ehci.c, ehci.h, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c,
// xhci.c
// 
// 93    3/29/11 10:08a Ryanchou
// [TAG]  		EIP53518
// [Category]  	Improvement
// [Description]  	Added chipset xHCI chip support.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhcd.c, uhci.c, usb.c,
// usb.sdl, usbdef.h, usbport, usbsb.c, xhci.c
// 
// 92    1/17/11 3:51a Ryanchou
// [TAG]  		EIP50361
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Hot plug USB 3.0 flash drive in setup will cause system
// hang.
// [RootCause]  	The memory may be destroyed if the Address Device command
// fails.
// [Solution]  	Check the memory has been allocated when free the memory.
// [Files]  		usb.c xhci.c xhci.h
// 
// 91    11/11/10 11:36p Ryanchou
// [TAG]  		EIP45578
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB 3.0 device can't be detected.
// [RootCause]  	Address Device Command fails.
// [Solution]  	Reset the device and attempt the Address Device Command
// again.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c, xhci.c
// 
// 90    10/28/10 12:34a Ryanchou
// EIP46865: Comment out unnecessary ASSERT macro.
// 
// 89    10/28/10 12:24a Ryanchou
// EIP45643: Fixed system hangs when hot plug USB mass storage quickly on
// USB 3.0 port.
// 
// 88    10/21/10 10:12a Ryanchou
// EIP45121: Added xHCI Supported Protocol Capability and fix the problem
// that USB 3.0 device can't be detected.
// 
// 87    10/20/10 10:24a Ryanchou
// EIP44702: Added USB 3.0 hub support.
// 
// 86    10/20/10 12:55a Ryanchou
// EIP45828: If the flag DEV_INFO_MASS_DEV_REGD is set, check if the
// controller type is difference between old DevInfo and new one.
// 
// 85    9/16/10 9:22a Ryanchou
// EIP44149: Disable slot if the Address Device command was unsuccessful. 
// 
// 84    9/07/10 4:12a Tonylo
// Remove user tags for coding standard.
// 
// 83    8/18/10 4:23p Olegi
// Klockwork related fixes; EIP37978
// 
// 82    8/13/10 4:10p Olegi
// Bugfix in CheckDeviceLimit function. EIP41442
// 
// 81    7/15/10 4:39a Tonylo
// EIP15489 - Add USB HandOff function for shurdown/init USB legacy
// through USB API function.
// 
// 80    7/13/10 5:09a Ryanchou
// EIP39838: Fixed configure USB hub fail.
// 
// 79    7/02/10 1:59a Ryanchou
// Update DevMiscInfo field when hot plug USB mass storage.
// 
// 78    6/22/10 9:29a Ryanchou
// EIP39374: Fixed USB mass storage hot plug issue.
// 
// 77    6/11/10 1:43a Ryanchou
// EIP36720: Fixed USB keyboard hot plug in setup issue.
// 
// 76    5/11/10 11:02a Olegi
// Bugfix in USB_InitDeviceDataDummy; EIP37974
// 
// 75    3/19/10 10:05a Olegi
// 
// 74    3/11/10 9:42a Olegi
// 
// 73    3/10/10 6:36p Olegi
// 
// 72    3/10/10 6:35p Olegi
// 
// 71    3/06/10 1:11p Olegi
// 
// 70    2/27/10 11:58a Olegi
// Change in the arguments of pfnHCDInitDeviceData function.
// 
// 69    2/26/10 4:23p Olegi
// 
// 68    2/23/10 1:20p Olegi
// Work around Klockwork issues. EIP34370
// 
// 67    2/08/10 9:38a Olegi
// EIP34448: Bugfix in prepareForLegacyOS.
// 
// 66    1/13/10 3:20p Olegi
// Correction in CheckDeviceLimit routine, EIP32804.
// 
// 65    12/31/09 9:53a Olegi
// 
// 64    12/10/09 10:12a Olegi
// Added UsbControlTimeout setup selection. EIP30079.
// 
// 63    11/12/09 6:09p Olegi
// 
// 62    11/09/09 5:40p Olegi
// 
// 61    10/30/09 5:47p Olegi
// 
// 60    10/13/09 8:55a Olegi
// EIP28323: Change in USBGetProperDeviceInfoStructure:
// - Undo the checking for DEV_INFO_DEV_BUS so that in device structure
// re-used.
// 
// 59    10/09/09 5:57p Olegi
// 
// 58    10/08/09 10:18a Olegi
// EIP28031: USB_SmiQueuePut must not be called after OS booted as it
// modifies the BS memory.
// 
// 57    10/07/09 9:48a Olegi
// USB Hub error handling improvement. EIP#25601.
// 
// 56    10/02/09 10:49a Olegi
// Code cleanup.
// 
// 55    9/15/09 12:21p Olegi
// Added KEY_REPEAT_LOGIC functionality. EIP#25841
// 
// 54    8/26/09 11:41a Olegi
// Changes that prevent collision of keyboard activity and mass storage
// access. EIP#22808
// 
// 53    8/18/09 2:36p Rameshr
// Symptom: When the system is inside the Option rom, connect uSb keyboard
// and it doesn't work.
// Rootcause: In post only EFI driver configure the USB keyboard. So Once
// comes out from option rom Usbkeyboard works.
// Solution: When you are inside the option rom configure the newly
// connected USB keyboard and notify EFI driver.
// 
// 52    8/06/09 4:15p Olegi
// Changes related to EIP#23335: connect status change is not maintained
// properly when device is disconnected while connection is in progress.
// 
// 51    6/11/09 5:29p Olegi
// Increased the default timeout value to 20 sec. Thermlake external HDD
// is not responding to the first READ_10 command for 14 seconds.
// 
// 50    6/04/09 3:42p Olegi
// USB_ConfigureDevice: for the existing devices copy the information
// about the parent controller/hub/port# into the new device structure.
// 
// 49    6/01/09 2:48p Olegi
// EIP#22046: while detecting the new device we get the configuration
// descriptor, assuming it is followed by the interface descriptor; if it
// is not an interface descriptor, we used to think it is not the first
// one, so we never send set address and configuration request.
// 
// 47    5/08/09 8:56a Olegi
// Increased the timeout value from 5 sec to 10 sec. Several types of
// external USB HDDs require this change to be properly enumerated.
// 
// 46    1/29/09 2:32p Olegi
// Added the check for device limit before device is configured.
// 
// 44    9/05/08 4:21p Olegi
// fpCallbackNotify4 is replaced with the local function.
// 
// 42    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 39    10/30/07 12:07p Olegi
// Set configuration one more time: it was found that for some devices
// SET_CONFIGURATION must be the executed right before issuing device
// specific commands. Example is USB Netac Key (VID 0x0644 DID 0x0000).
// 
// 38    10/15/07 5:20p Olegi
// Modified USB_on_identifyDev() routine.
// 
// 37    9/26/07 9:15a Olegi
// Added USB_FORCE_64BIT_ALIGNMENT flag.
// 
// 36    9/06/07 5:59p Olegi
// Added support for 64-byte pool allocation byte alignment.
// 
// 35    7/09/07 2:11p Olegi
// Changed the maximum data size of the BulkTransfer from 1kB to 64kB.
// 
// 32    5/05/07 1:54p Olegi
// Persistent DOS drives.
// 
// 31    4/17/07 8:43a Michaela
// Bugfix in USB_DetectNewDevice function.
// 
// 30    4/17/07 8:24a Olegi
// Device detection algorythm update, in sync with Core8.
// 
// 24    12/22/06 4:05p Olegi
// Timeout implementation.
//
// 17    4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 16    3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 14    3/06/06 6:24p Olegi
// Lun devices support modifications: supported using the index in
// DEV_INFO table, not through dedicated massLun table.
//
// 13    3/01/06 3:50p Olegi
// USB_FLAG_RUNNING_UNDER_OS flag added.
//
// 11    1/11/06 11:51a Olegi
// Multi-functional devices handling changed.
//
// 10    12/19/05 10:17a Olegi
// USB_StopHostControllers modified to control the sequence of stopping
// (EHCI first, others follow).
//
// 9     11/03/05 6:31p Andriyn
// LUN Support changes
//
// 7     6/20/05 8:55a Olegi
// .NET compiler with highest warning level and warning-as-error
// modification.
//
// 6     6/16/05 12:19p Andriyn
// Fix usb device lost after boot to legacy OS: don't disable port even if
// device is not
// supported by USBRT: there could be another device at the same address
//
// 5     6/15/05 1:59p Andriyn
// Comments were changed
//
// 4     6/01/05 5:34p Olegi
// Bugfix in USB_DetectNewDevice.
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
//-----------------------------------------------------------------------------
//
//  Name:           Usb.c
//
//  Description:    AMI USB main wrapper
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Token.h>
#include "amidef.h"
#include "usbdef.h"

#if USB_RUNTIME_DRIVER_IN_SMM
#include <AmiBufferValidationLib.h>
#include <AmiUsbSmmGlobalDataValidationLib.h>
#endif

#include <PCI.h>						//(EIP54018+)

BOOLEAN     gKeyRepeatStatus = FALSE;
extern BOOLEAN  gCheckUsbApiParameter;

BOOLEAN	OEMSkipList(UINT8,UINT8,UINT16,UINT8,UINT8);		//(EIP74609+)

#if USB_DEV_HUB
UINT8   USBHub_EnablePort(HC_STRUC*, UINT8, UINT8);
UINT8   USBHub_DisablePort(HC_STRUC*, UINT8, UINT8);
UINT8   USBHub_ResetPort(HC_STRUC*, UINT8, UINT8);
//VOID    USBHubFillDriverEntries (DEV_DRIVER*);    //(EIP71750-)
UINT8   USBHub_GetPortStatus (HC_STRUC*, UINT8, UINT8, BOOLEAN);
#endif

VOID    SpeakerBeep (UINT8, UINT16, HC_STRUC*);
VOID    FixedDelay(UINTN);
//VOID    BusFillDriverEntries(DEV_DRIVER*);    //(EIP71750-)
										//(EIP38434+)>
//#if USB_DEV_KBD
//VOID    USBKBDFillDriverEntries (DEV_DRIVER*);
//#endif
//#if USB_DEV_MOUSE
//VOID    USBMSFillDriverEntries (DEV_DRIVER*);
//#endif
                                        //(EIP71750-)>                                       
//VOID    USBHIDFillDriverEntries (DEV_DRIVER*);
										//<(EIP38434+)
//#if USB_DEV_MASS
//VOID    USBMassFillDriverEntries (DEV_DRIVER*);
//#endif
//#if USB_DEV_CCID
//VOID    USBCCIDFillDriverEntries (DEV_DRIVER*);
//#endif
                                        //<(EIP71750-)
VOID    MemFill (UINT8*, UINT32, UINT8);
VOID    MemCopy (UINT8*, UINT8*, UINT32);

VOID USBAPI_CheckDevicePresence (URP_STRUC*);

extern  USB_BADDEV_STRUC gUsbBadDeviceTable[];				//(EIP60706)

DEV_INFO*    USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);    //(EIP98145)
VOID*       USB_MemAlloc(UINT16);
UINT8       USB_MemFree (VOID*, UINT16);
UINT8*      USB_GetDescriptor (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT8 , UINT8);
UINT8       USB_SetAddress(HC_STRUC*,DEV_INFO*, UINT8);
DEV_INFO*   USBIdentifyAndConfigureDevice (HC_STRUC* , DEV_INFO* , UINT8* , UINT16 ,UINT16 );
UINT8       USB_DisconnectDevice (HC_STRUC*, UINT8, UINT8 );
VOID        USB_InitFrameList (HC_STRUC*, UINT32);
DEV_DRIVER* UsbFindDeviceDriverEntry(DEV_DRIVER*);

UINT8   USB_MemInit (VOID);
UINT8   USBInitHostController(UINT16 *, UINT8);
UINT8   USB_EnumerateRootHubPorts(UINT8);
UINT8   USBLogError(UINT16);
BOOLEAN CheckDeviceLimit(UINT8);
VOID	USB_SmiQueuePutMsg(QUEUE_T*, VOID*, int);

										//(EIP54018+)>
UINT32  ReadPCIConfig(UINT16, UINT8);
#if USB_S5_WAKEUP_SUPPORT
VOID    DwordWritePCIConfig(UINT16, UINT8, UINT32);
VOID    WordWritePCIConfig(UINT16, UINT8, UINT16);
VOID    ByteWritePCIConfig(UINT16, UINT8, UINT8);
VOID    UsbSbEnablePme(VOID);
#endif
										//<(EIP54018+)

extern  USB_GLOBAL_DATA  *gUsbData;  // Defined in AMIUHCD

#ifdef USB_CONTROLLERS_INITIAL_DELAY_LIST
typedef struct {
    UINT16  Vid;
    UINT16  Did;
    UINT16  DelayTime;
} CONTROLLERS_INITIAL_DELAY_LIST;

CONTROLLERS_INITIAL_DELAY_LIST gControllersInitialDelayList[] = {USB_CONTROLLERS_INITIAL_DELAY_LIST};
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_StartHostControllers
//
// Description: This function initializes the USB host controllers and
//              enumerate the root hub ports for possible USB devices.
//
// Output:      fpGlobalDataArea    Far pointer to the global data area
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_StartHostControllers(UINT8* fpGlobalDataArea)
{
    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       StopControllerType
//
// Description: This function stops all USB host controllers of a given type
//
// Output:      HC type
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
StopControllerType(
    UINT8 hc_type
)
{
    UINT8 i;
    HC_STRUC*   fpHCStruc;

    USB_DEBUG(DEBUG_LEVEL_3, "stopping all HC type %x:", hc_type);
    for (i = 0; i < gUsbData->HcTableCount; i++) {
        fpHCStruc = gUsbData->HcTable[i];
        if (fpHCStruc == NULL) {
            continue;
        }
        if ((fpHCStruc->bHCType == hc_type) &&
            (fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDStop)(fpHCStruc);
            USB_DEBUG(DEBUG_LEVEL_3, ".");
        }
    }
    USB_DEBUG(DEBUG_LEVEL_3, "\n");
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       StartControllerType
//
// Description: This function start all USB host controllers of a given type
//
// Output:      HC type
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
StartControllerType(
    UINT8 hc_type
)
{
    UINT8 i;
    HC_STRUC*   fpHCStruc;

    USB_DEBUG(DEBUG_LEVEL_3, "starting all HC type %x:", hc_type);
    for (i=0; i<gUsbData->HcTableCount; i++) {
        fpHCStruc = gUsbData->HcTable[i];
        if (fpHCStruc == NULL) {
            continue;
        }
        if (!(fpHCStruc->dHCFlag & HC_STATE_USED)) {
        	continue;
        }
        if ((fpHCStruc->bHCType == hc_type) ) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDStart)(fpHCStruc);
            USB_DEBUG(DEBUG_LEVEL_3, ".");
        }
    }
    USB_DEBUG(DEBUG_LEVEL_3, "\n");
}

										//(EIP74876+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:       StopControllerBdf
//
// Description: This function stops the USB host controllers of a given Bus Dev Function
//
// Input:       BusDevFuncNum
//
// Output:      None
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
StopControllerBdf(
    UINT16 BusDevFuncNum
)
{
    UINT8 i;
    HC_STRUC*   HcStruc;

    for (i = 0; i < gUsbData->HcTableCount; i++) {
        HcStruc = gUsbData->HcTable[i];
        if (HcStruc == NULL) {
            continue;
        }
        if ((HcStruc->wBusDevFuncNum == BusDevFuncNum) &&
            (HcStruc->dHCFlag & HC_STATE_RUNNING)) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDStop)(HcStruc);
            break;
        }
    }
}
										//<(EIP74876+)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_StopHostControllers
//
// Description: This function stops the USB host controllers and
//              frees the data structures associated with the host controllers
//              In case of USB2.0 first stop USB1.1 controllers, then USB2.0.
//
// Output:      None
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_StopHostControllers (VOID)
{
    // Suppress disconnect beeps as they might be confusing
    gUsbData->dUSBStateFlag  &= (~USB_FLAG_ENABLE_BEEP_MESSAGE);

    StopControllerType(USB_HC_XHCI);    				//(EIP52339+)
    StopControllerType(USB_HC_UHCI);
    StopControllerType(USB_HC_OHCI);
    StopControllerType(USB_HC_EHCI);

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       UsbHcStart
//
// Description: This function initializes the USB host controller and
//              enumerate the root hub ports for possible USB devices.
//
// Input:		HcStruc		HC struc pointer
//
// Output:		Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHcStart(HC_STRUC* HcStruc)
{
    UINT8   Index = 0;
    
	USB_DEBUG(DEBUG_LEVEL_3, "Starting HC %X, HCNum %d, type %x\n",
                    HcStruc->wBusDevFuncNum, HcStruc->bHCNumber, HcStruc->bHCType);
	
	// Execute start routine of the host controller driver
	(*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDStart)(HcStruc);

	// Check if the HC is running
	if ((HcStruc->dHCFlag & HC_STATE_RUNNING) == 0) {
		return USB_ERROR;
	}

    for (Index = 0; Index < gUsbData->HcTableCount; Index++) {
        if (gUsbData->HcTable[Index] == NULL) {
            continue;
        }
        if (HcStruc == gUsbData->HcTable[Index]) {
            continue;
        }
        if (HcStruc->BaseAddress == gUsbData->HcTable[Index]->BaseAddress) {
            break;
        }
        if (HcStruc->fpFrameList != NULL) {
            if (HcStruc->fpFrameList == gUsbData->HcTable[Index]->fpFrameList) {
                break;
            }
        }
        if (HcStruc->usbbus_data != NULL) {
            if (HcStruc->usbbus_data == gUsbData->HcTable[Index]->usbbus_data) {
                break;
            }
        }
#if USB_RUNTIME_DRIVER_IN_SMM
        if (HcStruc->wBusDevFuncNum == gUsbData->HcTable[Index]->wBusDevFuncNum) {
            break;
        }
#endif
    }

    if (Index != gUsbData->HcTableCount) {
        HcStruc->dHCFlag &= ~HC_STATE_RUNNING;
        return USB_ERROR;
    }
    
	HcStruc->dHCFlag |= HC_STATE_INITIALIZED;

#if USB_RUNTIME_DRIVER_IN_SMM
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    UpdateAmiUsbSmmGlobalDataCrc32(gUsbData);
#endif
#endif

#ifdef USB_CONTROLLERS_INITIAL_DELAY_LIST
    for (Index = 0; Index < COUNTOF(gControllersInitialDelayList); Index++) {
        if ((gControllersInitialDelayList[Index].Vid == HcStruc->Vid) &&
            (gControllersInitialDelayList[Index].Did == HcStruc->Did)) {
        	if (gControllersInitialDelayList[Index].DelayTime) {
        		FixedDelay(gControllersInitialDelayList[Index].DelayTime * 1000);
        	}
            break;
        }
    }
#endif

	USB_DEBUG(DEBUG_LEVEL_3, "Enumerating HC#%d, type 0x%x\n", HcStruc->bHCNumber, HcStruc->bHCType);
	// Issue enumerate call for this HC
	(*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDEnumeratePorts)(HcStruc);

	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       UsbHcStop
//
// Description: This function stops the USB host controller.
//
// Input:		HcStruc		HC struc pointer
//
// Output:		Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHcStop(HC_STRUC* HcStruc)
{
	if ((HcStruc->dHCFlag & HC_STATE_RUNNING) == 0) {
		return USB_ERROR;
	}

	USB_DEBUG(DEBUG_LEVEL_3, "Stopping HC %X, HCNum %d, type %x\n", 
		 		HcStruc->wBusDevFuncNum, HcStruc->bHCNumber, HcStruc->bHCType);
	(*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDStop)(HcStruc);

	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       CheckBiosOwnedHc
//
// Description: This function checks bios owned hc. 
//              Clear USB_FLAG_DRIVER_STARTED if we don't start 
//              any host controller.              
//
// Input:		None
//
// Output:		None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
CheckBiosOwnedHc(
    VOID
)
{
    UINT8       Index;
    HC_STRUC    *HcStruc;

    for (Index = 0; Index < gUsbData->HcTableCount; Index++) {
        HcStruc = gUsbData->HcTable[Index];
        if (HcStruc == NULL) {
            continue;
        }
        if (HcStruc->dHCFlag & HC_STATE_RUNNING) {
            return;
        }
    }
    
    gUsbData->dUSBStateFlag &= ~(USB_FLAG_DRIVER_STARTED);

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_EnmumerateRootHubPorts
//
// Description: This function enumerates the root hub ports of the all
//              selected type HCs
//
//
// Output:      bType   - HC type
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_EnumerateRootHubPorts (UINT8 bType)
{
    UINT8		Index;
    HC_STRUC*   fpHCStruc;

    USB_DEBUG(DEBUG_LEVEL_4, "Enumerating HC Ports.\n");
    for (Index = 0; Index < gUsbData->HcTableCount; Index++) {
        //
        // Get the HCStruc pointer associated with this controller
        //
        fpHCStruc = gUsbData->HcTable[Index];
        if (fpHCStruc == NULL) {
              continue;
        }

        if((fpHCStruc->bHCType) == bType && (fpHCStruc->dHCFlag & HC_STATE_RUNNING)) {
            USB_DEBUG(DEBUG_LEVEL_3, "Enumerating HC#%d, type 0x%x\n", fpHCStruc->bHCNumber, bType);
            //
            // Issue enumerate call for this HC
            //
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(bType)].pfnHCDEnumeratePorts)(fpHCStruc);
        }
    }
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_InitHostControllers
//
// Description: This function initializes the specified type of the HC
//              from the provided list of host controller PCI addresses
//
// Output:      pHCPCIAddrList  Pointer to table of HC PCI addresses in the system
//              bHCType         Type of HC to be initialized (EHCI, OHCI etc)
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBInitHostController(
    UINT16  * pHCPCIAddrList,
    UINT8   bHCType)
{
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_GetHubPortStatus
//
// Description: This function returns the hub port status
//
// Input:       HcStruc   HC struc pointer
//              HubAddr   USB device address of the hub or HC number
//                        BIT7 = 1/0  Roothub/Hub
//              PortNum   Port number
//
// Output:      Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_GetHubPortStatus (
    HC_STRUC*	HcStruc,
    UINT8       HubAddr,
    UINT8		PortNum,
    BOOLEAN     ClearChangeBits
)
{
    //
    // Check whether the request is for root hub or generic hub
    //
    if (HubAddr & BIT7) {
		// Root hub
        return (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDGetRootHubStatus)(
                                HcStruc, PortNum, ClearChangeBits);
    } else {
    #if USB_DEV_HUB
        return USBHub_GetPortStatus (HcStruc, HubAddr, PortNum, ClearChangeBits);
    #else
        return 0;
    #endif
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_DisableHubPort
//
// Description: This function disables the hub port
//
// Output:      fpHCStruc   HC struc pointer
//              bHubAddr    USB device address of the hub or HC number
//                          BIT7 = 1/0  Roothub/Hub
//              bPortNum    Port number
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_DisableHubPort(
    HC_STRUC*   fpHCStruc,
    UINT8       bHubAddr,
    UINT8       bPortNum)
{
    //
    // Check whether the request is for root hub or generic hub
    //
    if (bHubAddr & BIT7) {
        //
        // Issue the disable root hub call to disable the hub port
        //
        (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDDisableRootHub)(
                        fpHCStruc,
                        bPortNum);
#if USB_DEV_HUB
    }
    else {
        USBHub_DisablePort (fpHCStruc, bHubAddr, bPortNum);
#endif
    }
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_EnableHubPort
//
// Description: This function enables the hub port
//
// Output:      fpHCStruc   HC struc pointer
//              bHubAddr    USB device address of the hub or HC number
//                          BIT7 = 1/0  Roothub/Hub
//              bPortNum    Port number
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_EnableHubPort (
    HC_STRUC*   fpHCStruc,
    UINT8       bHubAddr,
    UINT8       bPortNum)
{
    //
    // Check whether the request is for root hub or generic hub
    //
    if (bHubAddr & BIT7) {
        //
        // Root hub
        // Issue the disable root hub call to disable the hub port
        //
        return (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDEnableRootHub)(fpHCStruc, bPortNum);
    } else {
    #if USB_DEV_HUB
        return USBHub_EnablePort (fpHCStruc, bHubAddr, bPortNum);
    #else
        return USB_ERROR;   // Only root hub could be successfully enabled
    #endif
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_ResetHubPort
//
// Description: This function resets the hub port
//
// Input:       HcStruc   HC struc pointer
//              HubAddr   USB device address of the hub or HC number
//                        BIT7 = 1/0  Roothub/Hub
//              PortNum   Port number
//
// Output:      Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_ResetHubPort (
    HC_STRUC*	HcStruc,
    UINT8       HubAddr,
    UINT8		PortNum)
{
    //
    // Check whether the request is for root hub or generic hub
    //
    if (HubAddr & BIT7) {
        //
        // Root hub
        // Issue the reset root hub call to reset the hub port
        //
        return (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDResetRootHub)(HcStruc, PortNum);
    } else {
    #if USB_DEV_HUB
        return USBHub_ResetPort (HcStruc, HubAddr, PortNum);
    #else
        return USB_ERROR;   // Only root hub could be successfully reset
    #endif
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_DetectNewDevice
//
// Description: This function checks the port status provided and depending
//              on the status it invokes device connect/disconnect routine
//
// Output:      fpHCStruc   Pointer to HCStruc
//              bHubAddr    For root port this is the host controller index
//                          in gUsbData->aHCStrucTable combined with BIT7;
//                          For devices connected to a hub this is parent
//                          hub USB address
//              bHubPort    Parent hub port number
//              bPortStatus Port status read
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USB_DetectNewDevice(
    HC_STRUC*   fpHCStruc,
    UINT8   bHubAddr,
    UINT8   bHubPort,
    UINT8   bPortStatus
)
{
    UINT8           bErrorFlag  = 0;
    UINT16          wDescLength;
    UINT8           bDevConfigured;
    UINTN           ConfigLevel = 0;
    UINT16          wTotalLength;
    UINT8           *fpBuffer = NULL;
    DEV_INFO        *fpDevInfo,
                    *fPointer;
    DEV_DESC        *fpDevDesc;
    CNFG_DESC       *fpCnfgDesc;
    INTRF_DESC      *fpIntrfDesc;
    UINT8           *DevMiscInfo;
	UINT8			Status;
    BOOLEAN         SkipConnectBeep = FALSE;   //(EIP64781+)
    UINT16			OrgTimeOutValue;			//(EIP75441+)
    UINT8           DeviceAddress;

    //
    // Get the temporary device info structure pointer (index 0)
    //
    fpDevInfo = gUsbData->aDevInfoTable;

    //
    // Fill the necessary entries in the device info
    //
    fpDevInfo->Flag             = DEV_INFO_VALID_STRUC;
    fpDevInfo->bDeviceAddress   = 0;
    //fpDevInfo->wEndp0MaxPacket  = 0x40;   //(EIP98230-)
    fpDevInfo->bDeviceType      = 0;
    fpDevInfo->wIncompatFlags   = 0;
	fpDevInfo->DevMiscInfo		= NULL;

    //
    // Fill the hub/host controller information
    //
    fpDevInfo->bHubDeviceNumber = bHubAddr;
    fpDevInfo->bHubPortNumber   = bHubPort;

    //
    // Fill the device speed
    //
USB_DEBUG(DEBUG_LEVEL_3, "USB_DetectNewDevice: wPS = %x\n", bPortStatus);
    fpDevInfo->bEndpointSpeed = (bPortStatus & USB_PORT_STAT_DEV_SPEED_MASK) >>
                        USB_PORT_STAT_DEV_SPEED_MASK_SHIFT;

                                        //(EIP98145+)>
#if SHOW_SKIP_PORT_INFORMATION
{
    UINT8   i;
    DEV_INFO   						*tmpDevInfo; 
    tmpDevInfo = fpDevInfo; 	
    USB_DEBUG(3, "==== SHOW_SKIP_PORT_INFORMATION ==== \n"); 				  
    USB_DEBUG(DEBUG_LEVEL_3, "BDF %x \nRoutePath = ",fpHCStruc->wBusDevFuncNum);  
    for(i=0;i<5;i++)
    {
        if(tmpDevInfo->bHubDeviceNumber & BIT7)
        {
            USB_DEBUG(3, "\nRootPort %x \n",tmpDevInfo->bHubPortNumber); 					  
            break;
        }
        USB_DEBUG(3, "%x ",tmpDevInfo->bHubPortNumber); 				  
        tmpDevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR, 0, tmpDevInfo->bHubDeviceNumber, 0);     
        if(tmpDevInfo == NULL) break;         
    }
    USB_DEBUG(3, "==== SHOW_SKIP_PORT_INFORMATION ==== \n"); 				  
}
#endif
                                        //<(EIP98145+)
                                        //(EIP98230+)>    
    switch (fpDevInfo->bEndpointSpeed) {
        case USB_DEV_SPEED_SUPER_PLUS:
        case USB_DEV_SPEED_SUPER:
            fpDevInfo->wEndp0MaxPacket = 0x200;
            break;
        case USB_DEV_SPEED_HIGH:
            fpDevInfo->wEndp0MaxPacket = 0x40;
            break;
        case USB_DEV_SPEED_FULL:
        case USB_DEV_SPEED_LOW:
            fpDevInfo->wEndp0MaxPacket = 0x08;
            break;
    }
                                        //<(EIP98230+)
    
    //
    // Fill the HC struc index value
    //
    fpDevInfo->bHCNumber = fpHCStruc->bHCNumber;

    bErrorFlag = TRUE;      // Assume as error
    bDevConfigured = FALSE;     // No device configured

    //
    // Allocate memory for device requests
    //
    ConfigLevel = USB_ERR_DEV_INIT_MEM_ALLOC;   // For proper error handling
    fpBuffer = USB_MemAlloc (GET_MEM_BLK_COUNT(MAX_CONTROL_DATA_SIZE));
    if (fpBuffer == NULL) {
		SpeakerBeep(8, 0x2000, fpHCStruc);
		return (DEV_INFO*)ConfigLevel;
    }
    ConfigLevel = USB_ERR_DEV_INIT_GET_DESC_8;

    // Initialize HC specific data before device configuration
    Status = (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDInitDeviceData)(
                        fpHCStruc, fpDevInfo, bPortStatus, &DevMiscInfo);
	if(Status != USB_SUCCESS) {
		USB_MemFree(fpBuffer, (UINT8)(MAX_CONTROL_DATA_SIZE / sizeof(MEM_BLK)));
		SpeakerBeep(8, 0x2000, fpHCStruc);
		return (DEV_INFO*)ConfigLevel;
	}
    fpDevInfo->DevMiscInfo = (VOID*)DevMiscInfo;

//
// Next send a GetDescriptor command to the device to get its Device
// Descriptor. Assume a MaxPacket size of 64 bytes (the device will use 8,
// 16, 32, or 64). Regardless of the packet size used by te device we can
// always get the real MaxPacket size that the device is using, because
// this piece of information is at offset 7 in the device descriptor.
//
	OrgTimeOutValue = gUsbData->wTimeOutValue;	//(EIP75441+)
	gUsbData->wTimeOutValue = 1000;				//(EIP75441+)

    fpDevDesc = (DEV_DESC*)USB_GetDescriptor(
                            fpHCStruc,
                            fpDevInfo,
                            fpBuffer,
                            8,
                            DESC_TYPE_DEVICE,
                            0);

	gUsbData->wTimeOutValue = OrgTimeOutValue;	//(EIP75441+)
    if(fpDevDesc == NULL) {
        goto detection_complete;
    }

    //
    // Get and store the endpoint 0 max packet size
    //
    ConfigLevel = USB_ERR_DEV_INIT_SET_ADDR;
    //
    // Endpoint 0 max packet size check.
    // CyQ've USB modem(Model:MQ4UFM560) return invalid device descriptor after 
    // warm reset.
    //
                                        //(EIP81612)>
    if (fpDevDesc->BcdUsb >= 0x0300) {
        fpDevInfo->wEndp0MaxPacket = (UINT16)1 << fpDevDesc->MaxPacketSize0;
    } else {
        fpDevInfo->wEndp0MaxPacket = (fpDevDesc->MaxPacketSize0)?
                (UINT16)fpDevDesc->MaxPacketSize0 : 0x40;
    }
                                        //<(EIP81612)
                                        //(EIP73803)>
    if((fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_LOW) ||
        (fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_FULL) ||
        (fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_HIGH)){
        FixedDelay(10 * 1000);     // 10msec delay
    }
                                        //<(EIP73803)

    //To assign an address to a USB device, the USB device transitions the state 
    //from the Default to the Address state.
    for (DeviceAddress = 1; DeviceAddress < 64; DeviceAddress++) {
        if (gUsbData->DeviceAddressMap & Shl64(1, DeviceAddress)) {
            break;
        }
    }

    if (DeviceAddress == 64) {
        goto detection_complete;
    }
    Status = USB_SetAddress(fpHCStruc, fpDevInfo, DeviceAddress);
    if (Status == USB_ERROR) {
		goto detection_complete;
    }
    gUsbData->DeviceAddressMap &= ~(Shl64(1, DeviceAddress));
    fpDevInfo->bDeviceAddress = DeviceAddress;
    FixedDelay(2 * 1000);
    
    //
    // Now send a GetDescriptor command to the device to get its device descriptor.
    //
    fpDevDesc = (DEV_DESC*)USB_GetDescriptor(
                            fpHCStruc,
                            fpDevInfo,
                            fpBuffer,
                            18,
                            DESC_TYPE_DEVICE,
                            0);

    //ASSERT(fpDevDesc != NULL);
    if (fpDevDesc == NULL) {
		goto detection_complete;
    }
    // If a descriptor returns with a value in its length field that is 
    // less than defined by USB specification, the descriptor is invalid.
    if (fpDevDesc->DescLength < 18) {
        goto detection_complete;
    }
    if (fpDevDesc->NumConfigs == 0) {
        fpDevDesc->NumConfigs = 1;
    }

    MemCopy((UINT8*)fpDevDesc, (UINT8*)&fpDevInfo->DevDesc, sizeof(DEV_DESC));

    ConfigLevel = USB_ERR_DEV_INIT_GET_DESC_200;
    //
    // Get the relevant information from the descriptor and store it in
    // device information struture
    //
    fpDevInfo->wVendorId    = fpDevDesc->VendorId;
    fpDevInfo->wDeviceId    = fpDevDesc->DeviceId;
//
// Look at each of the device's ConfigDescriptors and InterfaceDescriptors
// until an InterfaceDescriptor is found with BaseClass, SubClass, and
// Protocol fields indicating boot keyboard, mouse, hub or storage support.
//
    fpDevInfo->bConfigNum   = 0;

    if (fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_FULL) {
        FixedDelay(100);
    }

    do {    // For processing multiple configurations
								//(EIP70933+)>
        fpCnfgDesc = (CNFG_DESC*)USB_GetDescriptor(
                        fpHCStruc,
                        fpDevInfo,
                        fpBuffer,
                        0xFF,
                        DESC_TYPE_CONFIG,
                        fpDevInfo->bConfigNum);
		if(fpCnfgDesc == NULL) {
			break;
		}
		wTotalLength = fpCnfgDesc->wTotalLength;
        if (wTotalLength > 0xFF) {
            if(wTotalLength > (MAX_CONTROL_DATA_SIZE - 1)) {
                wTotalLength = MAX_CONTROL_DATA_SIZE - 1;
            }
            fpCnfgDesc = (CNFG_DESC*)USB_GetDescriptor(
                        fpHCStruc,
                        fpDevInfo,
                        fpBuffer,
                        wTotalLength,
                        DESC_TYPE_CONFIG,
                        fpDevInfo->bConfigNum);
								//<(EIP70933+)
            if(fpCnfgDesc == NULL) {
                break;
            }
        }
        if (fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_FULL) {
            FixedDelay(100);
        }
//
// fpCnfgDesc should now point to a ConfigDescriptor.  Verify this and
// then get some fields out of it.  Then point to the next descriptor.
//
        if(fpCnfgDesc->bDescType == DESC_TYPE_CONFIG) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDEnableEndpoints)(
                        fpHCStruc, fpDevInfo, (UINT8*)fpCnfgDesc);

            //wTotalLength = fpCnfgDesc->wTotalLength; //(EIP70933-)
            wDescLength = (UINT8)fpCnfgDesc->bDescLength;
            fpDevInfo->bConfigNum = fpCnfgDesc->bConfigValue;

										//(EIP70933-)>
/*
            if(wTotalLength > (MAX_CONTROL_DATA_SIZE - 1)) {
                wTotalLength = MAX_CONTROL_DATA_SIZE - 1;
            }
*/
										//<(EIP70933-)

            // Check if the device has alternate setting for the interface.
            for (;wDescLength < wTotalLength;) {
                //
                // fpIntrfDesc should now point to an InterfaceDescriptor.  Verify this
                // and then check its BaseClass, SubClass, and Protocol fields for
                // usable devices.
                //
                fpIntrfDesc = (INTRF_DESC*)((UINT8*)fpCnfgDesc + wDescLength);
										//(EIP59601+)>
				if ((fpIntrfDesc->bDescLength == 0) || 
					((fpIntrfDesc->bDescLength + wDescLength) > wTotalLength)) {
					break;
				}
                if ((fpIntrfDesc->bDescType == DESC_TYPE_INTERFACE) && (fpIntrfDesc->bAltSettingNum != 0)) {
                    fpDevInfo->Flag |= DEV_INFO_ALT_SETTING_IF;
                    break;
                }
                if (fpIntrfDesc->bDescLength) {
                    wDescLength += (UINT16)fpIntrfDesc->bDescLength;
                } else {
                    break;
                }
            }

            wDescLength = (UINT8)fpCnfgDesc->bDescLength;

            for (;wDescLength < wTotalLength;) {
                //
                // fpIntrfDesc should now point to an InterfaceDescriptor.  Verify this
                // and then check its BaseClass, SubClass, and Protocol fields for
                // usable devices.
                //
                fpIntrfDesc = (INTRF_DESC*)((UINT8*)fpCnfgDesc + wDescLength);
										//(EIP59601+)>
				if ((fpIntrfDesc->bDescLength == 0) || 
					((fpIntrfDesc->bDescLength + wDescLength) > wTotalLength)) {
					break;
				}
										//<(EIP59601+)
                if ((fpIntrfDesc->bDescType == DESC_TYPE_INTERFACE) && (fpIntrfDesc->bAltSettingNum == 0)) {
                    fpDevInfo->bInterfaceNum    = fpIntrfDesc->bInterfaceNum;
                    fpDevInfo->bAltSettingNum   = 0;
                    //USB_DEBUG(DEBUG_LEVEL_6, "USBIdentifyAndConfigureDevice::fpIntrfDesc %lx\n",fpIntrfDesc);
                    USB_DEBUG(DEBUG_LEVEL_3, "USBIdentifyAndConfigureDevice:: %04x/%04x Intrf %d, AltSetting %d\n",
                            fpDevInfo->wVendorId, fpDevInfo->wDeviceId, fpIntrfDesc->bInterfaceNum, fpIntrfDesc->bAltSettingNum);
                    USB_DEBUG(3, "fpCnfgDesc %x, wDescLength 0x%x, wTotalLength 0x%x\n", fpCnfgDesc, wDescLength, wTotalLength);
                    fPointer = USBIdentifyAndConfigureDevice(
                                    fpHCStruc,
                                    fpDevInfo,
                                    (UINT8*)fpCnfgDesc,
                                    wDescLength,
                                    wTotalLength);
                    if(fPointer != NULL) {
                        fpDevInfo = fPointer;
                        bDevConfigured = TRUE;  // At-least one device is configured
                                        //(EIP64781+)>
                        if(gUsbData->dUSBStateFlag & USB_FLAG_SKIP_CARD_READER_CONNECT_BEEP) {
                            if(fpDevInfo->bBaseClass == BASE_CLASS_MASS_STORAGE) {
                                SkipConnectBeep = TRUE;
                            }
                        }
                                        //<(EIP64781+)
                    }
															//(EIP22046+)>
					//
                    // There is one more config. Set device info structure entry 0 for it
                    //
                    if ((fpCnfgDesc->bNumInterfaces > 1) && bDevConfigured) {
						gUsbData->aDevInfoTable[0].Flag   |= DEV_INFO_MULTI_IF;
                    }
															//<(EIP22046+)
                }
                if (fpIntrfDesc->bDescLength && 
                    !(fpIntrfDesc->bDescType == DESC_TYPE_INTERFACE &&
                            fpIntrfDesc->bBaseClass == BASE_CLASS_HUB)) {
                    wDescLength += (UINT16)fpIntrfDesc->bDescLength;
                    if (wDescLength < wTotalLength) {
															//(EIP22046-)>
                        //
                        // There is one more config. Set device info structure entry 0 for it
                        //
                        /*
                        if (fpDevInfo->bInterfaceNum > 0) {
                            fpDevInfo->Flag |= DEV_INFO_MULTI_IF;
                        }
                        gUsbData->aDevInfoTable[0].Flag   |= DEV_INFO_MULTI_IF;
                        */
															//<(EIP22046-)
                        fpDevInfo = gUsbData->aDevInfoTable;
                    }
                } else {
                    break;   // fpIntrfDesc->bDescLength == 0
                }
            }   // while ()
        }   // if
        //
        // Check if we have at least one usable device
        //
        if (bDevConfigured) {
            bErrorFlag = FALSE; // Device successfully configured
            ConfigLevel = (UINTN)gUsbData->aDevInfoTable;
            goto detection_complete;
        }
        else {
            fpDevInfo->bConfigNum++;
        }
    } while (fpDevInfo->bConfigNum < fpDevInfo->DevDesc.NumConfigs);  // while

detection_complete:
    //
    // At this point, if bErrorFlag is FALSE then we successfully configured
    // atleast a device.
    // If bErrorFlag is TRUE then there is error in configuring the device
    //
    if (bErrorFlag) {
        USBLogError((UINT16)ConfigLevel); // Log configuration level

        SpeakerBeep(8, 0x2000, fpHCStruc);

		(*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDDeinitDeviceData)
 						(fpHCStruc, fpDevInfo);
        if(ConfigLevel != USB_ERR_DEV_INIT_GET_DESC_8) {
            //
            // Disable the hub port
            //
            USB_DisableHubPort(
                fpHCStruc,
                fpDevInfo->bHubDeviceNumber,
                fpDevInfo->bHubPortNumber);
            ConfigLevel = 0;
        }
        if (fpDevInfo->bDeviceAddress) {
            gUsbData->DeviceAddressMap |= Shl64(1, fpDevInfo->bDeviceAddress);
        }
    }
    else {
                                        //(EIP64781+)>
        if(!SkipConnectBeep) {
            SpeakerBeep(4, 0x1000, fpHCStruc);
        }
                                        //<(EIP64781+)
    }
    USB_MemFree(fpBuffer, (UINT8)(MAX_CONTROL_DATA_SIZE / sizeof(MEM_BLK)));

    return (DEV_INFO*)ConfigLevel;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_StopDevice
//
// Description: This function stops the device:
//              - calls its disconnect function if available
//              - stops polling the device's interrupt endpoint
//              - updates device address memory map
//
//
// Output:      fpHCStruc   Pointer to HCStruc
//              bHCNubAddr  Hub address
//              bHCPort     Port number
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_StopDevice(
    HC_STRUC*   fpHCStruc,
    UINT8       bHubAddr,
    UINT8       bHCPort)
{
    UINT8           bCount;
    DEV_DRIVER* fpDevDriver;
    DEV_INFO*       fpDevice;
    UINT8           Status;

    Status = USB_ERROR;
    //
    // Find the device entry that would match the input.
    //
    for (bCount = 1; bCount < MAX_DEVICES; bCount++)
    {
        fpDevice = &gUsbData->aDevInfoTable[bCount];
        if((fpDevice->Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_DUMMY)) ==
			DEV_INFO_VALID_STRUC) {
            if((fpDevice->bHubDeviceNumber == bHubAddr) &&
                                    (fpDevice->bHubPortNumber == bHCPort))
            {
                //
                // Device found - issue disconnect call for the device
                //
                if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {
                    if (!(fpDevice->Flag & DEV_INFO_IN_QUEUE)) {
                        USB_SmiQueuePut(fpDevice);
                        fpDevice->Flag |= DEV_INFO_IN_QUEUE;
                    }
                }

                fpDevDriver = UsbFindDeviceDriverEntry(fpDevice->fpDeviceDriver);
                //
                // Check disconnect function is valid, if yes - execute it
                //
                if (fpDevDriver && fpDevDriver->pfnDisconnectDevice)
                {
                    fpDevDriver->pfnDisconnectDevice(fpDevice);
					fpDevice->fpDeviceDriver = NULL;
                } else {
					//
					// Stop polling the device's interrupt endpoint
					//
					if (fpDevice->IntInEndpoint) {
						Status = (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDDeactivatePolling)
										(fpHCStruc, fpDevice);
						fpDevice->IntInEndpoint = 0;
					}
                }

                // HC device removal call
                Status = (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDDeinitDeviceData)
                                (fpHCStruc, fpDevice);

				// Reset the disconnecting flag
				fpDevice->Flag &= ~DEV_INFO_DEV_DISCONNECTING;

                //
                // Update Device Address Map, preserving the address for registered devices
                //
                gUsbData->DeviceAddressMap |= Shl64(1, fpDevice->bDeviceAddress);
                fpDevice->Flag &= ~DEV_INFO_DEV_PRESENT;
                if (!(fpDevice->Flag & (DEV_INFO_DEV_BUS | DEV_INFO_MASS_DEV_REGD))) {
					// Reset the device info structure validity ~flag
					fpDevice->Flag &= ~DEV_INFO_VALID_STRUC;
                }
                USB_DEBUG(3, "Release Dev[%d]: %x, flag %x\n", bCount, fpDevice, fpDevice->Flag);
            }
        }
    }
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_DisconnectDevice
//
// Description: This function is called when a device disconnect is
//              detected. This routine disables the hub port and stops the
//              device and its children by calling another routine.
//
// Output:      fpHCStruc   Far pointer to HCStruc of the host controller
//              bHubAddr    USB device address of the hub whose status
//                          has changed
//                  bit 7   : 1 - Root hub, 0 for other hubs
//                  bit 6-0 : Device address of the hub
//              bPortNum    Port number
//
// Output:     Status: USB_SUCCESS = Success
//                      USB_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_DisconnectDevice(
    HC_STRUC*   fpHCStruc,
    UINT8       bHubAddr,
    UINT8       bHCPort)
{
    //
    // A device has been disconnected from the USB.  First disable the hub port
    // that the device was plugged into.  Then free up the device's entry in the
    // DeviceTable.  If there an error occurs while disabling the port, assume
    // that the device is still present an leave its DeviceTable entry in place.
    //
    USB_DisableHubPort(fpHCStruc, bHubAddr, bHCPort);

    USB_StopDevice(fpHCStruc, bHubAddr, bHCPort);

    return USB_SUCCESS;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   USBCheckPortChange
//
// Description: This routine processes the port status change (like connect,
//              disconnect, etc.) for the root hub and external hubs.
//
// Output:      HcStruc   Pointer to Host Controller structure
//              HubAddr     Device address of the hub whose status
//                          has changed:
//                                bit 7	: 1 - Root hub, 0 for other hubs
//                                bit 6-0	: Device address of the hub
//              PortNum     Hub port number
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBCheckPortChange (
    HC_STRUC    *HcStruc,
    UINT8       HubAddr,
    UINT8       PortNum
)
{
    UINT8       PortStatus;
    DEV_INFO    *Dev;
    UINT8       Count;

    for (Count = 0; Count < 5; Count++) {
		PortStatus = USB_GetHubPortStatus(HcStruc, HubAddr, PortNum, TRUE);

        //
        // Check the obtained port status
        //
        if (PortStatus == USB_ERROR) {
			return USB_ERROR;
        }
        if (!(PortStatus & USB_PORT_STAT_DEV_OWNER)) {
            return USB_SUCCESS;
        }
        if (OEMSkipList(HubAddr,PortNum,HcStruc->wBusDevFuncNum,0,0)) {
            USB_DEBUG(3, "Match the skip table ; skipping this device.\n");   //(EIP98145)
            return USB_SUCCESS;
        }
        if (!Count && !(PortStatus & USB_PORT_STAT_DEV_CONNECT_CHANGED)) {
			return USB_SUCCESS;
        }
    
        if (PortStatus & USB_PORT_STAT_DEV_CONNECTED) {
            if (gUsbData->bHandOverInProgress) {
                USB_DisableHubPort(HcStruc, HubAddr, PortNum);
                return USB_SUCCESS;
            }
			if ((Count != 0) || !(PortStatus & USB_PORT_STAT_DEV_ENABLED)) {
				// Reset and enable the port
				USB_ResetHubPort(HcStruc, HubAddr, PortNum);
				USB_EnableHubPort(HcStruc, HubAddr, PortNum);
				PortStatus = USB_GetHubPortStatus(HcStruc, HubAddr, PortNum, TRUE);

                if (PortStatus == USB_ERROR) {
			        return USB_ERROR;
                }
                if (!(PortStatus & USB_PORT_STAT_DEV_OWNER)) {
                    return USB_SUCCESS;
                }
				if (!(PortStatus & USB_PORT_STAT_DEV_CONNECTED)) {
					// Some device will be disconnected after 
					// port reset, and reconnected for a while.
					FixedDelay(100 * 1000);
					continue;
				}
				// Check whether port is enabled
				if (!(PortStatus & USB_PORT_STAT_DEV_ENABLED)) {
					FixedDelay(100 * 1000);	 // 100msec delay
					continue;
				}
			}
            Dev = USB_DetectNewDevice(HcStruc, HubAddr, PortNum, PortStatus);
            if ((UINTN)Dev == USB_ERR_DEV_INIT_GET_DESC_8) {
                FixedDelay(100 * 1000);     // 100msec delay
                continue;
            }
			if ((UINTN)Dev == 0) {
				return USB_ERROR;
			}
            if ((UINTN)Dev > USB_ERR_DEV_INIT_GET_DESC_200) {
                return USB_SUCCESS;
            }
            SpeakerBeep(16, 0x4000, HcStruc);  // Issue error beep
            return USB_ERROR;
        } else {  // Disconnect
            USB_DisconnectDevice(HcStruc, HubAddr, PortNum);
            SpeakerBeep(8, 0x1000, HcStruc);
			return USB_SUCCESS;
        }
    }
    if (Count == 5) {
        USB_DisableHubPort(HcStruc, HubAddr, PortNum);
        return USB_ERROR;
    }

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_MemAlloc
//
// Description: This routine allocates blocks of memory from the global
//              memory pool
//
// Output:      bNumBlocks  Number of 32 byte blocks needed
//
// Output:     Start offset to the allocated block (NULL on error)
//
// NOTES:       This routine allocates continuous 32 byte memory blocks.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID _FAR_ *
USB_MemAlloc(UINT16  wNumBlk)
{
    UINT8       bMemIsFound     = FALSE,
                bBitCount       = 0,
                bStart          = 0;
    UINT16      wCount;
    UINT16      Count           = 0;    // Contiguous blocks counter

    UINT16      BlkOffset       = 0,
                wMapDwordPtr;
										//(EIP89641)>
	UINT16		PageCount = 0;
	UINT16		MapDwordCount = 0;
	UINT32		BlksStsDwordsPerPage = 0;

    UINT32      dMask,
                dTemp;

    if (wNumBlk == 0) return NULL;
    
#if USB_FORCE_64BIT_ALIGNMENT
    if (wNumBlk % 2) wNumBlk++;
#endif
	wCount = wNumBlk;

	BlksStsDwordsPerPage = (gUsbData->MemBlkStsBytes >> 2) / gUsbData->MemPages;

    //
    // Locate wNumBlk contiguous blocks from each memory page
    //
    for(PageCount = 0; (PageCount < gUsbData->MemPages) && !bMemIsFound; PageCount++) {

        // Do not reset the counter if the allocated blocks greater than a page.
        if (wNumBlk <= (0x1000 / sizeof(MEM_BLK))) {
		    Count = 0;  // Reset contiguous blocks counter
        }

	    for (MapDwordCount = 0; MapDwordCount < BlksStsDwordsPerPage; MapDwordCount++) {
	        //
	        // Read the next DWORD memory map data
	        //
	        wMapDwordPtr = (PageCount * BlksStsDwordsPerPage) + MapDwordCount;
        	dTemp = gUsbData->aMemBlkSts[wMapDwordPtr];

	        for (bBitCount = 0; bBitCount < 32; bBitCount++)  {
	            BlkOffset++;
	            if (dTemp & (UINT32)(1 << bBitCount))  {
	                Count++;    // Found another free block
	                if(Count == wCount) {
	                    BlkOffset = (UINT16)(BlkOffset-Count);
	                    bMemIsFound = TRUE;
	                    break;  // Found the requested number of free blocks
	                }
	            }
	            else
	            {
	                Count = 0;  // Reset contiguous blocks counter
	            }
	        }
	        if (bMemIsFound) break;
	    }
    }
										//<(EIP89641)
    if (!bMemIsFound) {
        ASSERT(FALSE);
        return NULL;
    }

//
// Change the appropriate bits in the memory map to indicate that some memory
// is being allocated
//
// At this point,
//  bBitCount points to the end of the block within DWORD
//  wMapDwordPtr points to the status dword in question

// We have to reset bCount number of bits starting from
// wMapDwordPtr[bBitCount] to wStsX[BitPosY]
// where wStsX is the status double word of the starting block,
// BitPosY is the bit position of the starting block.
//
    USB_DEBUG(DEBUG_LEVEL_4, "wMapDwordPtr = %d\n", wMapDwordPtr);
//
// Let us have a do loop to do the trick
//
    do {
        //
        // Find out how many bits we can reset in current (pointed by wMapDwordPtr)
        // double word
        //
        Count = (UINT16)((bBitCount >= (wCount-1)) ? wCount : bBitCount+1);
        //
        // Find out the starting bit offset
        //
        bStart = (UINT8)(bBitCount + 1 - Count);
        //
        // Form the 32bit mask for the AND operation
        // First prepare the bits left on the left
        //
        // Note: FFFFFFFF << 32 treated differently by different compilers; it
        // results as 0 for 16 bit compiler and FFFFFFFF for 32 bit. That's why
        // we use caution while preparing the AND mask for the memory map update.
        //
        dMask = ((Count + bStart) < 32) ? (0xFFFFFFFF << (Count + bStart)) : 0;

        //
        // Second, prepare the bits on the right
        //
        if (bStart)
        {
            dMask = dMask | ~(0xFFFFFFFF << bStart);
        }

        //
        // Reset the specified number of bits
        //
        gUsbData->aMemBlkSts[wMapDwordPtr] &= dMask;

        //
        // Update the bCount, StsWordCount & BitCount
        //
        bBitCount = 31;     // End of previous double word where we have to start
        wMapDwordPtr--;     // Previous double word
        wCount = wCount - Count;
    } while ( wCount );

    USB_DEBUG(DEBUG_LEVEL_4, "MemAlloc: %d block(s) at %x %x %x\n",
            wNumBlk,
            gUsbData->fpMemBlockStart + BlkOffset * sizeof(MEM_BLK),
            gUsbData->aMemBlkSts[0],
            gUsbData->aMemBlkSts[1]);

    return  ((VOID _FAR_ *)
        (gUsbData->fpMemBlockStart + (UINT32)BlkOffset * sizeof(MEM_BLK)));
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_MemFree
//
// Description: This routine frees the chunk of memory allocated using
//              the USBMem_Alloc call
//
// Output:      fpPtr       Pointer to the memory block to be freed
//              bNumBlocks  Number of 32 byte blocks to be freed
//
// Output:     Start offset to the allocated block (NULL on error)
//
// NOTES:       This routine frees continuous memory blocks starting
//              from the fpPtr.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_MemFree (
    VOID _FAR_ * fpPtr,
    UINT16    wNumBlk)
{
    UINT8   bOffset, bCount;
    UINT16  wBlkCount, wBlkOffset, wStsWord;

#if USB_FORCE_64BIT_ALIGNMENT
    if (wNumBlk % 2) wNumBlk++;
#endif
    wBlkCount = wNumBlk;
    wBlkOffset = 0;

    //
    // Check for pointer validity
    //
    if (fpPtr == NULL) return USB_ERROR;

    if ((fpPtr < (VOID *)gUsbData->fpMemBlockStart) ||
            (fpPtr > (VOID *)(gUsbData->fpMemBlockStart +
                            (MEM_BLK_COUNT+1)*sizeof(MEM_BLK)))) {
        return  USB_ERROR;
    }

    wBlkOffset = (UINT16)((UINTN)fpPtr - (UINTN)gUsbData->fpMemBlockStart) / sizeof (MEM_BLK);

    if (wBlkOffset >= MEM_BLK_COUNT) {
        return USB_ERROR;
    }

    wStsWord = (UINT16)(wBlkOffset >> 5);   // Divide by 32
    bOffset = (UINT8)(wBlkOffset & 0x1F);   // Mod 32
    bCount = 0;

    do {
        gUsbData->aMemBlkSts[wStsWord] |= ((UINT32)1 << (bCount + bOffset));
        wBlkCount--;
        bCount++;

        if ((bCount + bOffset) && (!((bCount + bOffset) & 0x1F))) {
            wStsWord ++;
            bCount = bOffset = 0;
        }
    } while (wBlkCount);

    USB_DEBUG(DEBUG_LEVEL_4, "MemFree: %d block(s) at %x %x %x\n",
                wNumBlk, fpPtr,
                gUsbData->aMemBlkSts[0], gUsbData->aMemBlkSts[1]);
    //
    // Pointer is valid. Fill the memory with 0's
    //
    MemFill (fpPtr, (UINT32)(wNumBlk * sizeof (MEM_BLK)), 0);

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_InstallCallBackFunction
//
// Description: This function adds a new callback function to the globall
//              callback function list and returns the index of it.
//
// Output:      pfnCallBackFunction     Callback function address
//
// Output:     Callback function index
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_InstallCallBackFunction (
    CALLBACK_FUNC      CallBackFunction
)
{
    UINT8   Index;
    //
    // Check whether this function is already installed or none found
    //
    for (Index = 0; Index < MAX_CALLBACK_FUNCTION; Index++) {
        //
        // Check for null entry
        //
        if (gUsbData->aCallBackFunctionTable[Index] == 0) {
            break;  // No entry found
        }

        if (gUsbData->aCallBackFunctionTable[Index] == CallBackFunction) {
            return (UINT8)(Index+1);
        }
    }

    ASSERT(Index != MAX_CALLBACK_FUNCTION);
    if (Index == MAX_CALLBACK_FUNCTION) {
        EFI_DEADLOOP(); // Exceeding max # of callback function is illegal
    } else {
        //
        // Store the call back function
        //
        gUsbData->aCallBackFunctionTable[Index] = CallBackFunction;
    }

    return (UINT8)(Index + 1);
}

DEV_DRIVER*
UsbFindDeviceDriverEntry(
    DEV_DRIVER* DevDriver
)
{
    UINTN   Index;

    if (DevDriver == NULL) {
        return DevDriver;
    }

    for (Index = 0; Index < MAX_DEVICE_TYPES; Index++) {
        if (DevDriver == &gUsbData->aDevDriverTable[Index]) {
            return &gUsbData->aDevDriverTable[Index];
        }
        if (DevDriver == &gUsbData->aDelayedDrivers[Index]) {
            return &gUsbData->aDelayedDrivers[Index];
        }
    }

    return NULL;
    
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_GetDescriptor
//
// Description: This function executes a get descriptor command to the
//              given USB device and endpoint
//
// Output:      fpHCStruc   HCStruc pointer
//              fpDevInfo   Device info pointer
//              fpBuffer    Buffer to be used for the transfer
//              wLength     Size of the requested descriptor
//              bDescType   Requested descriptor type
//              bDescIndex  Descriptor index
//
// Output:     Pointer to memory buffer containing the descriptor
//              NULL on error
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8*
USB_GetDescriptor(
    HC_STRUC*   fpHCStruc,
    DEV_INFO*   fpDevInfo,
    UINT8*  fpBuffer,
    UINT16  wLength,
    UINT8   bDescType,
    UINT8   bDescIndex)
{
    UINT8           bGetDescIteration;
    UINT16          wReg,
                    wStatus;
    EFI_STATUS      EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);

    if (EFI_ERROR(EfiStatus)) {
        return NULL;
    }

    EfiStatus = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return NULL;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        EfiStatus = AmiValidateMemoryBuffer((VOID*)fpBuffer, wLength);
        if (EFI_ERROR(EfiStatus)) {
            return NULL;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif
                                        //(EIP60640)>
    for (bGetDescIteration = 0; bGetDescIteration < 5; bGetDescIteration++) {
        wReg = (UINT16)((bDescType << 8) + bDescIndex);
        wStatus = (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDControlTransfer)(
                        fpHCStruc,
                        fpDevInfo,
                        (UINT16)USB_RQ_GET_DESCRIPTOR,
                        (UINT16)0,
                        wReg,
                        fpBuffer,
                        wLength);
        if (wStatus) {
            return fpBuffer;
        }
        if (gUsbData->dLastCommandStatusExtended & USB_TRNSFR_TIMEOUT) {
            break;
        }
        FixedDelay(10 * 1000);
    }
                                        //<(EIP60640)
    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_SetAddress
//
// Description: This function sets the USB device address of device 0 to
//              the given value. After this call the USB device will respond
//              at its new address.
//
// Output:      fpHCStruc   Pointer to HCStruc structure
//              fpDevInfo   Pointer to device info structure
//              bNewDevAddr New device address to set
//
// Output:      USB_SUCCESS or USB_ERROR
//
// Notes:       Skip SET_ADDRESS request for XHCI controllers
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_SetAddress(
    HC_STRUC*   fpHCStruc,
    DEV_INFO*   fpDevInfo,
    UINT8       bNewDevAddr)
{
                                        //(EIP60640)>
    UINT8           SetAddressIteration;

    for (SetAddressIteration = 0; SetAddressIteration < 5; SetAddressIteration++) {
        (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDControlTransfer)(
                            fpHCStruc,
                            fpDevInfo,
                            (UINT16)USB_RQ_SET_ADDRESS,
                            0,
                            (UINT16)bNewDevAddr,
                            0,
                            0);
        if (!(gUsbData->bLastCommandStatus & USB_CONTROL_STALLED )) {
            USB_DEBUG(DEBUG_LEVEL_5, "USB_SetAddress#%d\n",bNewDevAddr);
            return USB_SUCCESS;
        }
    }
    return USB_ERROR;
                                        //<(EIP60640)
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_SetConfig
//
// Description: This function sets the device configuration.
//
// Input:       HcStruc   Pointer to HCStruc structure
//              DevInfo   Pointer to device info structure
//              ConfigNum Configuration Value
//
// Output:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_SetConfig(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8       ConfigNum)
{
     (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDControlTransfer)(
                    HcStruc,
                    DevInfo,
                    USB_RQ_SET_CONFIGURATION,
                    0,
                    (UINT16)ConfigNum,
                    0,
                    0);

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       UsbSetInterface
//
// Description: This function sets the device interface.
//
// Input:       HcStruc   Pointer to HCStruc structure
//              DevInfo   Pointer to device info structure
//              InterfaceNum Interface Value
//
// Output:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbSetInterface(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8       InterfaceNum
)
{
    USB_DEBUG(3, "UsbSetInterface %d\n", InterfaceNum);
    (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDControlTransfer)(
                    HcStruc,
                    DevInfo,
                    USB_RQ_SET_INTERFACE,
                    0,
                    (UINT16)InterfaceNum,
                    0,
                    0);

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USBLogError
//
// Description: This routine logs the USB error in the data area. This
//              logged errors will be displayed during the POST.
//
// Output:      wErrorCode  Error code to log
//
// Output:     USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBLogError(UINT16  wErrorCode)
{
    //
    // First check for end of the buffer
    //
    if(gUsbData->bErrorLogIndex < MAX_USB_ERRORS_NUM)
    {
        //
        // Still have space to log errors
        //
        gUsbData->aErrorLogBuffer[gUsbData->bErrorLogIndex] = wErrorCode;
        gUsbData->bErrorLogIndex++;
    }
    return USB_ERROR;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_GetDeviceInfoStruc
//
// Description: This function is used to retrieve the device info structure
//              for the particular device address & HCStruc
//
// Output:     bSearchFlag  Flag indicating search type
//                  = USB_SRCH_DEV_ADDR to search by device address and
//                      HCStruc pointer
//                  = USB_SRCH_DEV_TYPE to search by device type
//                  = USB_SRCH_HC_STRUC to search by HC struc pointer
//                  = USB_SRCH_DEV_NUM to count the number of devices connected:
//                      if fpHCStruc is not NULL - count only devices connected to
//                      certain controller, otherwise - all devices of requested
//                      type.
//                  = USB_SERCH_DEV_INDX to search by device location in the DEV_INFO:
//                     a) if fpDevInfo <> 0 return index or the fpDevInfo
//                     b) if bDevAddr <> 0 return the corresponding fpDevInfo
//                     c) if both bDevAddr <> 0 and fpDevInfo <> 0, consider a)
//
//              fpDevInfoPtr    Pointer to the device info structure from where the
//                              search begins (if 0 start from first entry)
//              bDev    Device address/drive number/device type
//              pHCStruc    Pointer to the HCStruc structure
//
// Output:     Depending on bSearchFlag this function returns:
//              - pointer to DEV_INFO structure
//              - table index
//              - number of devices
//              Function returns NULL if device is not found.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USB_GetDeviceInfoStruc(
    UINT8       bSearchFlag,
    DEV_INFO*   fpDev_Info,
    UINT8       bDev,
    HC_STRUC*   fpHcStruc
)
{
    UINT8       Index;
    BOOLEAN     TerminateSearch = FALSE;
    UINT32      dDeviceCounter  = 0;

    if (bSearchFlag == USB_SRCH_DEV_INDX) {
        if (fpDev_Info) {
            for (Index=1; Index < MAX_DEVICES; Index++) {
                if (&gUsbData->aDevInfoTable[Index] == fpDev_Info) {
                    return (DEV_INFO*)(UINTN)Index;
                }
            }
            return NULL;    // Device address not found in the table
        }
        if (bDev == USB_HOTPLUG_FDD_ADDRESS) return &gUsbData->FddHotplugDev;
        if (bDev == USB_HOTPLUG_HDD_ADDRESS) return &gUsbData->HddHotplugDev;
        if (bDev == USB_HOTPLUG_CDROM_ADDRESS) return &gUsbData->CdromHotplugDev;

        if (bDev) return &gUsbData->aDevInfoTable[bDev];
        return NULL;        // Invalid input - both bDev and fpDevInfo are zeroes.
    }

    for (Index = 1; Index < MAX_DEVICES; Index ++) {
        //
        // if fpDev_Info is not null then position the search at the correct
        // index that matches the fpDev_Info
        //
        if (fpDev_Info) {
            if (&gUsbData->aDevInfoTable[Index] != fpDev_Info)
                continue;
            else {
                fpDev_Info = 0;
                continue;
            }
        }
        //
        // For USB_SRCH_DEVBASECLASS_NUM devices are counted regardless of their
        // DEV_INFO_VALID_STRUC flag
        //
        if (bSearchFlag == USB_SRCH_DEVBASECLASS_NUM)
        {
            if(gUsbData->aDevInfoTable[Index].bBaseClass == bDev) {
                if (fpHcStruc) {
                    //
                    // Check if device belongs to the specified HC
                    //
                    if (gUsbData->aDevInfoTable[Index].bHCNumber != fpHcStruc->bHCNumber)
                    {
                        continue;
                    }
                }
                if (gUsbData->aDevInfoTable[Index].Flag & DEV_INFO_DEV_PRESENT)
                {
                    dDeviceCounter++;
                }
            }
            continue;
        }

        if ((gUsbData->aDevInfoTable[Index].Flag & DEV_INFO_VALIDPRESENT) ==
            DEV_INFO_VALIDPRESENT){
            switch(bSearchFlag) {
                case  USB_SRCH_HC_STRUC:
                    if (fpHcStruc == NULL) return NULL;
                    if (gUsbData->HcTable
                        [gUsbData->aDevInfoTable[Index].bHCNumber-1] == fpHcStruc) {
                        TerminateSearch = TRUE;
                    }
                    break;

                case  USB_SRCH_DEV_TYPE:
                    if (gUsbData->aDevInfoTable[Index].bDeviceType == bDev) {
                        TerminateSearch = TRUE;
                    }
                    break;
                case  USB_SRCH_DEV_NUM:
                    if (gUsbData->aDevInfoTable[Index].bDeviceType == bDev) {
                        if (fpHcStruc) {
                            //
                            // Check if device belongs to the specified HC
                            //
                            if (gUsbData->aDevInfoTable[Index].bHCNumber != fpHcStruc->bHCNumber)
                            {
                                break;
                            }
                        }
                        dDeviceCounter++;
                    }
                    break;  // Do not change TerminateSearch so loop continues
                case  USB_SRCH_DEV_ADDR:
                    if (gUsbData->aDevInfoTable[Index].bDeviceAddress == bDev) {
                        if ((fpHcStruc == NULL) ||
                            (gUsbData->HcTable
                                [gUsbData->aDevInfoTable[Index].bHCNumber-1] == fpHcStruc)) {
                            TerminateSearch = TRUE;
                        }
                    }
                    break;

                default:
                    return NULL;
            }
        }
        if (TerminateSearch) return ((DEV_INFO*)&gUsbData->aDevInfoTable[Index]);
    }
    if ( (bSearchFlag == USB_SRCH_DEV_NUM) || (bSearchFlag == USB_SRCH_DEVBASECLASS_NUM) )
         return (DEV_INFO*)(UINTN)dDeviceCounter;

    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// PROCEDURE:   UsbAllocDevInfo
//
// Description: Finds a non-used DEV_INFO record in aDevInfoTable and marks it
//              reserved. To free the user need to clear DEV_INFO_VALID_STRUC
//              bit in bFlag of DEV_INFO
//
// Output:     Pointer to new device info. struc. 0 on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
DEV_INFO* UsbAllocDevInfo()
{
    UINT8       bIndex;
    DEV_INFO    *fpNewDevInfo;

    for (bIndex = 1; bIndex < MAX_DEVICES; bIndex ++){
        fpNewDevInfo = gUsbData->aDevInfoTable +bIndex;
        if ((fpNewDevInfo->Flag &
        ( DEV_INFO_VALID_STRUC | DEV_INFO_DEV_BUS)) == 0 ){
            //
            // Free device info structure. Save it if not.
            //
            fpNewDevInfo->Flag |= DEV_INFO_VALID_STRUC |  DEV_INFO_DEV_PRESENT;
            return  fpNewDevInfo;
        }
    }
    return NULL;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBGetProperDeviceInfoStructure
//
// Description: This routine searches for a device info structure that
//              matches the vendor and device id, and LUN of the device
//              found. If such a device info structure not found, then it
//              will return a free device info structure
//
// Input:       Vendor, Device ID, Current LUN
//
// Output:     Pointer to new device info. struc. NULL on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USBGetProperDeviceInfoStructure(
    DEV_INFO*	Dev,
    UINT8   	Lun)
{
    UINT8       bCount;
    DEV_INFO    *fpDevInfo, *fpFreeDevInfo;

    fpFreeDevInfo = NULL;

//
// Scan through the device info table for a free entry. Also if the device
// connected is a mass storage device look for a device info structure whose
// device is disconnected and its vendor & device id matches the one of
// current device. If such a structure found that means this device may be
// reconnected - use the same structure
//
    for (bCount = 1; bCount < MAX_DEVICES; bCount++)
    {
        fpDevInfo   = (DEV_INFO*) &gUsbData->aDevInfoTable[bCount];

        if (fpDevInfo->Flag & DEV_INFO_DEV_DUMMY) {
            continue;
        }

        // Check whether the structure is valid
        if (!(fpDevInfo->Flag & DEV_INFO_VALID_STRUC)) {    
            if (fpFreeDevInfo == NULL) {
                fpFreeDevInfo = fpDevInfo;    // Store the value of the free device info
            }
        } else {
            //
            // Yes, structure is valid. Check for device presence
            //
			if (fpDevInfo->Flag & DEV_INFO_DEV_PRESENT) {
				if ((fpDevInfo->bHubDeviceNumber != Dev->bHubDeviceNumber) ||
					(fpDevInfo->bHubPortNumber != Dev->bHubPortNumber)) {
					continue;
				}
			}
            //
            // Device is not present. Match the vendor, device id  and LUN with
            // current device info
            //
            if ((fpDevInfo->wVendorId == Dev->wVendorId) &&
                (fpDevInfo->wDeviceId == Dev->wDeviceId) &&
                (fpDevInfo->bInterfaceNum == Dev->bInterfaceNum) &&
                (fpDevInfo->bEndpointSpeed == Dev->bEndpointSpeed) &&
                (fpDevInfo->bLUN == Lun)) {
                return fpDevInfo;   // "Abandoned" device entry found
            }
        }
    }
    return fpFreeDevInfo;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// PROCEDURE:   USB_ConfigureDevice
//
// Description: This routine completes the USB device configuration for
//              the devices supported by USB BIOS. This routine
//              handles the generic configuration for the devices.
//
// Output:      pHCStruc    HCStruc pointer
//              pDevInfo    Device information structure pointer
//              pDesc       Pointer to the descriptor structure
//              wStart      Offset within interface descriptor
//                          supported by the device
//              wEnd        End offset of the device descriptor
//
// Output:     Pointer to new device info. struc. 0 on error
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USB_ConfigureDevice (
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Desc,
    UINT16      Start,
    UINT16      End
)
{
    DEV_INFO    *NewDevInfo;

    NewDevInfo = USBGetProperDeviceInfoStructure(DevInfo, 0);

    if (NewDevInfo == NULL) {
        return NULL;
    }
    //
    // Check whether this device is reconnected by checking the valid
    // structure flag
    //
    if (NewDevInfo->Flag & DEV_INFO_VALID_STRUC) {
        USB_DEBUG(DEBUG_LEVEL_3, "USB_ConfigureDevice: Existing device.\n");
        //
        // This device is reconnected. Reuse the old device address so that
        // INT13h can identify this drive properly
        //
        DevInfo->Flag |= NewDevInfo->Flag;
		NewDevInfo->wDataInSync = 0;
		NewDevInfo->wDataOutSync = 0;
    }
    else {
        //
        // Check whether we reached the limit of devices of this type
        //
        if (CheckDeviceLimit(DevInfo->bBaseClass) == TRUE) {
            return NULL;
        }
    }

    //
    // For registered devices skip updating bFlag
    //
    if (!(NewDevInfo->Flag & DEV_INFO_MASS_DEV_REGD)) {
        //
        // Since DeviceInfo[0] already has many fields filled in, the new entry
        // should be initialized with a copy of DeviceInfo[0].  But, the new
        // DeviceInfo should not be  marked as "present" until the device
        // is successfully initialized.
        //
        // Copy old DeviceInfo struc to new DeviceInfo struc and zero device[0]
        //
        MemCopy ((UINT8*)DevInfo, (UINT8*)NewDevInfo, sizeof (DEV_INFO));
		NewDevInfo->Flag &= DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT |
								DEV_INFO_MASS_DEV_REGD | DEV_INFO_DEV_BUS |
								DEV_INFO_IN_QUEUE | DEV_INFO_ALT_SETTING_IF;
    } else {
        // Change the parent HC number and port number in the existing DEV_INFO
        NewDevInfo->bHCNumber = DevInfo->bHCNumber;
    	NewDevInfo->bHubDeviceNumber = DevInfo->bHubDeviceNumber;
		NewDevInfo->bHubPortNumber = DevInfo->bHubPortNumber;
		NewDevInfo->bEndpointSpeed = DevInfo->bEndpointSpeed;
		NewDevInfo->wEndp0MaxPacket = DevInfo->wEndp0MaxPacket;
    	NewDevInfo->DevMiscInfo = DevInfo->DevMiscInfo;
        NewDevInfo->bDeviceAddress = DevInfo->bDeviceAddress;
    }

    //
    // Do a SetConfiguration command to the device to set it to its
    // HID/Boot configuration.
    //
    NewDevInfo->Flag |= DEV_INFO_VALIDPRESENT;
    if (!(DevInfo->Flag & DEV_INFO_MULTI_IF)) {
	    USB_SetConfig(HcStruc, NewDevInfo, NewDevInfo->bConfigNum);
        if (DevInfo->Flag & DEV_INFO_ALT_SETTING_IF) {
            UsbSetInterface(HcStruc, NewDevInfo, NewDevInfo->bAltSettingNum);
        }
    }

    USB_DEBUG(3, "new dev: %x, flag: %x, addr %d\n",
                NewDevInfo, NewDevInfo->Flag, NewDevInfo->bDeviceAddress);

    return NewDevInfo;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCheckNonCompliantDevice
//
// Description: This function checks for non-compliant USB devices by
//              by comparing the device's vendor and device id with
//              the non-compliant device table list and updates the
//              data structures appropriately to support the device.
//
// Input:       fpHCStruc - HCStruc pointer
//              fpDevInfo - Device information structure pointer
//              fpDesc    - Pointer to the descriptor structure
//              wDescLength - End offset of the device descriptor
//
// Output:     Updated fpDevInfo->wIncompatFlags field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
USBCheckNonCompliantDevice(
    HC_STRUC*   fpHCStruc,
    DEV_INFO*   fpDevInfo,
    UINT8*      fpDesc,
    UINT16      wLength,
    UINT16      wDescLength
)
{
    USB_BADDEV_STRUC    *fpBadDevice;
    INTRF_DESC          *fpIntrfDesc;

    fpIntrfDesc = (INTRF_DESC*)((UINT8*)fpDesc + wLength);

    //
    // Search the bad device table to get the structure for this device
    //
    for (fpBadDevice = gUsbBadDeviceTable;
         fpBadDevice->wDID | fpBadDevice->wVID; fpBadDevice++) {

        if ((fpBadDevice->wDID != fpDevInfo->wDeviceId) ||
                (fpBadDevice->wVID != fpDevInfo->wVendorId)) {
            continue;
        }
USB_DEBUG(DEBUG_LEVEL_3, "Found non-compatible device: DID=%x, VID=%x\n", fpBadDevice->wDID, fpBadDevice->wVID);
        //
        // Save the incompatibility flag into device info structure
        //
        fpDevInfo->wIncompatFlags = fpBadDevice->wFlags;

        //
        // Check which fields to update in the interface descriptor
        //
        // Check for base class field
        //
        if (fpBadDevice->bBaseClass) {
            //
            // Update base class field in the interface descriptor
            //
            fpIntrfDesc->bBaseClass = fpBadDevice->bBaseClass;
        }
        //
        // Check for base sub class field
        //
        if (fpBadDevice->bSubClass) {
            //
            // Update sub class field in the interface descriptor
            //
            fpIntrfDesc->bSubClass = fpBadDevice->bSubClass;
        }
        //
        // Check for protocol field
        //
        if (fpBadDevice->bProtocol) {
            //
            // Update protocol field in the interface descriptor
            //
            fpIntrfDesc->bProtocol = fpBadDevice->bProtocol;
        }
        break;
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// PROCEDURE:   USBIdentifyAndConfigureDevice
//
// Description: This routine invokes the device drivers 'check device type'
//              routine and identifies the device type.
//
// Output:      pHCStruc    HCStruc pointer
//              pDevInfo    Device information structure pointer
//              pDesc       Pointer to the descriptor structure
//              wStart      Offset within interface descriptor
//                          supported by the device
//              wEnd        End offset of the device descriptor
//
// Output:     Pointer to new device info. struc, NULL on error
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USBIdentifyAndConfigureDevice (
    HC_STRUC*   fpHCStruc,
    DEV_INFO*   fpDevInfo,
    UINT8*      fpDesc,
    UINT16      wLength,
    UINT16      wDescLength)
{
    UINT8           bBaseClass, bSubClass, bProtocol,
                    bIndex, bRetValue;
    DEV_INFO*       fpDevInfoLocal;
    DEV_DRIVER*     fpDevDriver;
    INTRF_DESC*     fpIntrfDesc;

    //
    // Check for non-compliant device. If non-compliant device found then
    // the descriptor values will get updated depending on the need.
    //
    USBCheckNonCompliantDevice (
            fpHCStruc,
            fpDevInfo,
            fpDesc,
            wLength,
            wDescLength);

    USB_DEBUG(DEBUG_LEVEL_3, "USBIdentifyAndConfigureDevice...");

    //
    // Check whether device needs to be disable
    //
    if (fpDevInfo->wIncompatFlags & USB_INCMPT_DISABLE_DEVICE) {
        USB_DEBUG(DEBUG_LEVEL_3, "not compatible device.\n");
        return NULL;
    }

    fpIntrfDesc = (INTRF_DESC*)(fpDesc + wLength);

//(EIP74609+)>
	if(OEMSkipList(fpDevInfo->bHubDeviceNumber,fpDevInfo->bHubPortNumber,fpHCStruc->wBusDevFuncNum,fpIntrfDesc->bBaseClass,1)) {
        USB_DEBUG(3, "Match the skip table ; skipping this device.\n");   //(EIP98145) 
		return NULL;
	}	
//<(EIP74609+) 
    //
    // Get the base, sub class & protocol values
    //
    bBaseClass  = fpIntrfDesc->bBaseClass;
    bSubClass   = fpIntrfDesc->bSubClass;
    bProtocol   = fpIntrfDesc->bProtocol;

    //
    // Check for matching device driver
    //
    fpDevInfoLocal = NULL;
    bRetValue = USB_ERROR;
                                        
                                        //(EIP96616+)>
    for (bIndex = 0; bIndex < MAX_DEVICE_TYPES; bIndex ++) {
        fpDevDriver = &gUsbData->aDevDriverTable[bIndex];
        //
        // Check structure validity
        //
        if (!fpDevDriver->bDevType) {
            continue;       // Driver table not valid
        }
        //
        // Verify presence of Check Device routine
        //
        if (fpDevDriver->pfnCheckDeviceType) {
            //
            // Check device type is implemented. Execute it!
            //
            bRetValue = (*fpDevDriver->pfnCheckDeviceType)(
                           fpDevInfo,bBaseClass,
                           bSubClass,bProtocol);
                if (bRetValue != USB_ERROR)
                    break;
            }  else {
            //
            // Check device type is not implemented. Compare the class codes
            //
            if((fpDevDriver->bBaseClass == bBaseClass) ||
                (fpDevDriver->bSubClass == bSubClass) ||
                (fpDevDriver->bProtocol == bProtocol)) {
                //
                // If the class codes match set bRetValue with the bDevType from the Device Driver
                //
                bRetValue = fpDevDriver->bDevType;
                break;
            }
        }
    }
    if(bRetValue != USB_ERROR){
        //
        // Check whether we reached the limit of devices of this type
        //
        //if (CheckDeviceLimit(bBaseClass) == TRUE) continue;   //(EIP81761-)

        //
        // Set the device type in the Device Info structure
        //
        fpDevInfo->bDeviceType  = bRetValue;

        //
        // Set Base Class, Subclass and Protocol information
        //
        fpDevInfo->bBaseClass = bBaseClass;
        fpDevInfo->bProtocol = bProtocol;
        fpDevInfo->bSubClass = bSubClass;

        //
        // Device identified. Issue common configure call
        // Call a common routine to handle the remaining initialization that is done
        // for all devices.
        //
        fpDevInfoLocal = USB_ConfigureDevice(
                            fpHCStruc,
                            fpDevInfo,
                            fpDesc,
                            wLength,
                            wDescLength);

        if (fpDevInfoLocal == NULL) {
            USB_DEBUG(DEBUG_LEVEL_3, "USB: Common configure failed.\n");
            return fpDevInfoLocal;
        }

        if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {
            if (!(fpDevInfoLocal->Flag & DEV_INFO_IN_QUEUE)) {
                USB_SmiQueuePut(fpDevInfoLocal);
                fpDevInfoLocal->Flag |= DEV_INFO_IN_QUEUE;
            }
        }

        fpDevInfoLocal->fpDeviceDriver = fpDevDriver;
        fpDevInfoLocal = (*fpDevDriver->pfnConfigureDevice)(
                                fpHCStruc,
                                fpDevInfoLocal,
                                fpDesc,
                                wLength,
                                wDescLength);
        if (!fpDevInfoLocal ||
        !(fpDevInfoLocal->Flag & DEV_INFO_VALID_STRUC) )
        {
            fpDevInfoLocal = 0;
            USB_DEBUG(DEBUG_LEVEL_3, "USB: Device specific configure failed.\n");
            return fpDevInfoLocal;
        }

                                        //<(EIP96616+)
    }

    USB_DEBUG(DEBUG_LEVEL_3, "%x\n", fpDevInfoLocal);

    return fpDevInfoLocal;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USB_InitFrameList
//
// Description: This routine initializes the frame list pointed by fpPtr
//              with the dValue provided
//
// Output:      fpHCStruc   Pointer to the Host Controller structure
//              dValue  Value to be initialized with
//
// Output:     Nothing
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>


VOID
USB_InitFrameList(
    HC_STRUC*   fpHCStruc,
    UINT32      dValue)
{
    UINT16  wIndex;
    UINT32  *fpPtr = (UINT32*)fpHCStruc->fpFrameList;

    for (wIndex = 0; wIndex < fpHCStruc->wAsyncListSize; wIndex ++) {
        fpPtr[wIndex] = dValue;
    }
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBKeyRepeat
//
// Description: This function handles different key repeat related functions
//              depending on the input
//
// Input:   fpHCStruc - pointer for the HC that implements the key repeat function
//          bAction   - sub-function index:
//              0  Install key repeat HCStruc
//              1  Disable key repeat
//              2  Enable key repeat
//				3  Uninstall key repeat HCStruc
//
// Output:  None
//
// Note:    fpHCStruc is only relevant for sub-function 0.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBKeyRepeat(
    HC_STRUC*   HcStruc,
    UINT8       Action
)
{

//USB_DEBUG(DEBUG_LEVEL_3, "KR%d\n", bAction);
	UINT8		i;

    switch (Action) {
        case 0:     // Sub-function 0: Save the HCStruc value for later use
            if (gKeyRepeatStatus == FALSE) {
                gUsbData->fpKeyRepeatHCStruc = HcStruc;
        	}
            break;
        case 1:     // Sub-function 0: Disable key repeat
			if (gKeyRepeatStatus) {
#if USB_HID_KEYREPEAT_USE_SETIDLE == 1 
	            if (gUsbData->fpKeyRepeatDevInfo != NULL) {
	            //
	            // Set the HID SET_IDLE request to 0
	            //
	            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(gUsbData->HcTable[gUsbData->fpKeyRepeatDevInfo->bHCNumber - 1]->bHCType)].pfnHCDControlTransfer)
	                    (gUsbData->HcTable[gUsbData->fpKeyRepeatDevInfo->bHCNumber - 1],
	                    gUsbData->fpKeyRepeatDevInfo,(UINT16)HID_RQ_SET_IDLE, gUsbData->fpKeyRepeatDevInfo->bInterfaceNum, 0, 0, 0);	//(EIP54782)
	            }
#else
	            if (gUsbData->fpKeyRepeatHCStruc) {
	                (*gUsbData->aHCDriverTable[GET_HCD_INDEX(
	                    gUsbData->fpKeyRepeatHCStruc->bHCType)].pfnHCDDisableKeyRepeat)(
	                        gUsbData->fpKeyRepeatHCStruc);
	            }
#endif
				gKeyRepeatStatus = FALSE;
			}
            break;
        case 2:     // Sub-function 0: Enable key repeat
        	if (!gKeyRepeatStatus) {
#if USB_HID_KEYREPEAT_USE_SETIDLE == 1 
	            if(gUsbData->fpKeyRepeatDevInfo != NULL) {
	                //
	                // Set the HID SET_IDLE request to 0x200 (8ms)
	                //
	                (*gUsbData->aHCDriverTable[GET_HCD_INDEX(gUsbData->HcTable[gUsbData->fpKeyRepeatDevInfo->bHCNumber - 1]->bHCType)].pfnHCDControlTransfer)
	                        (gUsbData->HcTable[gUsbData->fpKeyRepeatDevInfo->bHCNumber - 1],
	                        gUsbData->fpKeyRepeatDevInfo,(UINT16)HID_RQ_SET_IDLE, gUsbData->fpKeyRepeatDevInfo->bInterfaceNum, 0x400, 0, 0);	//(EIP54782)
	            }
#else 
	            if (gUsbData->fpKeyRepeatHCStruc) {
	                (*gUsbData->aHCDriverTable[GET_HCD_INDEX(
	                    gUsbData->fpKeyRepeatHCStruc->bHCType)].pfnHCDEnableKeyRepeat)(
	                        gUsbData->fpKeyRepeatHCStruc);
	            }
#endif
				gKeyRepeatStatus=TRUE;
        	}
            break;
		case 3:
        	if (gUsbData->fpKeyRepeatHCStruc == HcStruc) {
            	gUsbData->fpKeyRepeatHCStruc = NULL;
				for (i = 0; i < gUsbData->HcTableCount; i++) {
                    if (gUsbData->HcTable[i] == NULL) {
                        continue;
                    }
                    if (gUsbData->HcTable[i] == HcStruc) {
                        continue;
                    }
					if (gUsbData->HcTable[i]->dHCFlag & HC_STATE_RUNNING) {
						gUsbData->fpKeyRepeatHCStruc = gUsbData->HcTable[i];
                        if (gKeyRepeatStatus) {
                            gKeyRepeatStatus = FALSE;
                            USBKeyRepeat(NULL, 2);
                        }
                        break;
					}
				}
        	}
			break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BusFillDriverEntries
//
// Description: Install drivers that redirects ...????
//
// Input:   fpDevDriver - record that the routine can use to install the drive
// Output:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_bus_interrupt_handler (
    HC_STRUC	*HcStruc,
    DEV_INFO	*DevInfo,
    UINT8		*Td,
    UINT8		*Buffer,
    UINT16      DataLength
)
{
	USBHC_INTERRUPT_DEVNINFO_T *Idi = (USBHC_INTERRUPT_DEVNINFO_T *)DevInfo->pExtra;
    EFI_STATUS  Status = EFI_SUCCESS;
    
	ASSERT(Idi);
	if (Idi == NULL) {
		return USB_SUCCESS;
	}

#if USB_RUNTIME_DRIVER_IN_SMM	
	Status = AmiValidateMemoryBuffer((VOID*)Idi, sizeof(USBHC_INTERRUPT_DEVNINFO_T));
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }
#endif

	USB_SmiQueuePutMsg(&Idi->QCompleted, Buffer, (int)Idi->DataLength);
    return USB_SUCCESS;
}

VOID
UsbBusDeviceInit(
    VOID
)
{
    USB_InstallCallBackFunction(USB_bus_interrupt_handler);
    return;
}

DEV_INFO*
USB_on_configDev(
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    UINT8       *fpDesc,
    UINT16      wStart,
    UINT16      wEnd
)
{
    fpDevInfo->bDeviceType      = (UINT8)BIOS_DEV_TYPE_USBBUS;
    fpDevInfo->bCallBackIndex   = USB_InstallCallBackFunction(USB_bus_interrupt_handler);
    return(fpDevInfo);
}

UINT8
USB_on_identifyDev(
    DEV_INFO*   fpDevInfo,
    UINT8       bBaseClass,
    UINT8       bSubClass,
    UINT8       bProtocol
)
{
                                        //(EIP96616+)>
    if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI)
        return  BIOS_DEV_TYPE_USBBUS;
    else
        return  USB_ERROR;
                                        //<(EIP96616+)
}

UINT8
USB_on_disconnectDev(
    DEV_INFO* fpDevInfo
)
{
    return  USB_SUCCESS;
}

VOID
BusFillDriverEntries(
    DEV_DRIVER  *fpDevDriver
)
{
    fpDevDriver->bDevType               = BIOS_DEV_TYPE_USBBUS;
    fpDevDriver->bBaseClass             = 0;
    fpDevDriver->bSubClass              = 0;
    fpDevDriver->bProtocol              = 0;
    fpDevDriver->pfnDeviceInit          = UsbBusDeviceInit;
    fpDevDriver->pfnCheckDeviceType     = USB_on_identifyDev;
    fpDevDriver->pfnConfigureDevice     = USB_on_configDev;
    fpDevDriver->pfnDisconnectDevice    = USB_on_disconnectDev;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USB_ReConfigDevice, USB_ReConfigDevice2
//
// Description: EFI code will call this function to give a chance for
//              SMI dev driver to complete the configuration of device
//
//              Before call, USB device is connected, address is assigned
//              and configuration is set. DEV_INFO structure is initalized
//              from information parsed from descriptors and linked
//              to USBBUS dev driver. Device driver specific to the type
//              of USB device wasn't called on this device
//
//              After the call returns, a specific device driver
//              initialization was  performed by calling pfnCheckDeviceType
//              and pfnConfigureDevice functions of device driver. Parameters
//              to those functions are taken from descriptors downloaded from
//              the device. Device preserve old address and active configuration
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
int USB_ReConfigDevice2( HC_STRUC* fpHCStruc, DEV_INFO* fpDevInfo,
                        CNFG_DESC   *fpCnfgDesc,
                        INTRF_DESC * fpIntrfDesc );

int USB_ReConfigDevice( HC_STRUC* fpHCStruc, DEV_INFO* fpDevInfo )
{
    INTRF_DESC      *fpIntrfDesc=NULL;

    UINT8           iConfig;
    int             status = USB_SUCCESS;   //(EIP90124)
    UINT8*          fpBuffer;
    CNFG_DESC       *fpCnfgDesc=NULL;
    UINT16			OrgTimeOutValue;

    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(fpHCStruc);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    gCheckUsbApiParameter = FALSE;

	if (fpDevInfo->bDeviceType != 0 && 
		fpDevInfo->bDeviceType != BIOS_DEV_TYPE_USBBUS) {
		return USB_SUCCESS;
	}

    fpBuffer = USB_MemAlloc (GET_MEM_BLK_COUNT(MAX_CONTROL_DATA_SIZE));
    if (fpBuffer == NULL) {
        return USB_ERROR;
    }
    //
    // Find configuration desc
    //
    for (iConfig = 0; iConfig < fpDevInfo->DevDesc.NumConfigs;++iConfig){
        
        OrgTimeOutValue = gUsbData->wTimeOutValue;
        gUsbData->wTimeOutValue = USB_GET_CONFIG_DESC_TIMEOUT_MS;
        
        fpCnfgDesc = (CNFG_DESC*)USB_GetDescriptor(
            fpHCStruc,
            fpDevInfo,
            fpBuffer,
            (MAX_CONTROL_DATA_SIZE - 1),
            DESC_TYPE_CONFIG,
            iConfig);
        
        gUsbData->wTimeOutValue = OrgTimeOutValue;
        
        if (fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_FULL) {
            FixedDelay(1000);           
        }
        if(fpCnfgDesc != NULL && fpCnfgDesc->bDescType == DESC_TYPE_CONFIG &&
            fpDevInfo->bConfigNum == fpCnfgDesc->bConfigValue ){
            break;
        }

        fpCnfgDesc = NULL;
    }

    if( fpCnfgDesc ){
        UINT16 offset;
        UINT16 wDescLength;
        INTRF_DESC      *pIntrf;

        if(fpCnfgDesc->wTotalLength > MAX_CONTROL_DATA_SIZE - 1)
            fpCnfgDesc->wTotalLength = MAX_CONTROL_DATA_SIZE - 1;
        wDescLength = fpCnfgDesc->wTotalLength;
        for(offset=(UINT16)fpCnfgDesc->bDescLength;offset <wDescLength ;offset = offset + (UINT16)pIntrf->bDescLength){
            pIntrf  = (INTRF_DESC*)((UINT8*)fpCnfgDesc + offset);
            if(pIntrf->bDescLength == 0) {
                break;
            }
            if (pIntrf->bDescType == DESC_TYPE_INTERFACE &&
                fpDevInfo->bInterfaceNum == pIntrf->bInterfaceNum &&
                fpDevInfo->bAltSettingNum == pIntrf->bAltSettingNum ) {
                fpIntrfDesc =pIntrf;
                break;
            }
        }
    }

    USB_DEBUG(DEBUG_LEVEL_3,
        "USB_reConfigDev:: CfgDsc=%x; IntrfDsc=%x\n",
        fpCnfgDesc, fpIntrfDesc);

    if (fpIntrfDesc && fpCnfgDesc) {
        status = USB_ReConfigDevice2(fpHCStruc, fpDevInfo,
                                    fpCnfgDesc, fpIntrfDesc);
    } else {
        status = USB_ERROR;
    }

    USB_MemFree(fpBuffer, (UINT8)(MAX_CONTROL_DATA_SIZE / sizeof(MEM_BLK)));

    return status;
}

//----------------------------------------------------------------------------
//  USB_ReConfigDevice2
//----------------------------------------------------------------------------
int
USB_ReConfigDevice2(
    HC_STRUC    *fpHCStruc,
    DEV_INFO    *fpDevInfo,
    CNFG_DESC   *fpCnfgDesc,
    INTRF_DESC  *fpIntrfDesc
)
{
//  int             abort=0;
    int             bIndex;
    UINT8               bRetValue = USB_ERROR;
    DEV_DRIVER          *fpDevDriver = NULL;
    DEV_INFO            *fpDevInfoLocal;
    UINT8               bBaseClass, bSubClass, bProtocol;
    EFI_STATUS      EfiStatus;

    USB_DEBUG(DEBUG_LEVEL_3, "USB_ReConfigDevice2.\n");


    EfiStatus = UsbHcStrucValidation(fpHCStruc);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    
#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        EfiStatus = AmiValidateMemoryBuffer((VOID*)fpCnfgDesc, sizeof(CNFG_DESC));
        if (EFI_ERROR(EfiStatus)) {
            return USB_ERROR;
        }
        EfiStatus = AmiValidateMemoryBuffer((VOID*)fpCnfgDesc, fpCnfgDesc->wTotalLength);
        if (EFI_ERROR(EfiStatus)) {
            return USB_ERROR;
        }
        EfiStatus = AmiValidateMemoryBuffer((VOID*)fpIntrfDesc, sizeof(INTRF_DESC));
        if (EFI_ERROR(EfiStatus)) {
            return USB_ERROR;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    //
    // Check for non-compliant device. If non-compliant device found then
    // the descriptor values will get updated depending on the need.
    //
    USBCheckNonCompliantDevice (
        fpHCStruc,
        fpDevInfo,
        (UINT8*)fpCnfgDesc,
        fpCnfgDesc->bDescLength,
        fpCnfgDesc->wTotalLength);

    //
    // Check whether device needs to be disable
    //
    if (fpDevInfo->wIncompatFlags & USB_INCMPT_DISABLE_DEVICE)
    {
        return USB_ERROR;
    }

    //
    // Get the base, sub class & protocol values
    //
    bBaseClass  = fpIntrfDesc->bBaseClass;
    bSubClass   = fpIntrfDesc->bSubClass;
    bProtocol   = fpIntrfDesc->bProtocol;

    //
    // Check for matching device driver
    //
    fpDevInfoLocal = NULL;
    for (bIndex = 0, bRetValue = USB_ERROR;
        bIndex < MAX_DEVICE_TYPES && bRetValue == USB_ERROR; bIndex ++) {
        fpDevDriver = &gUsbData->aDelayedDrivers[bIndex];
        if (!fpDevDriver->bDevType)
            continue;
        if (fpDevDriver->pfnCheckDeviceType){
            bRetValue = (*fpDevDriver->pfnCheckDeviceType)(
                fpDevInfo,bBaseClass,bSubClass,bProtocol);
        }else if((fpDevDriver->bBaseClass == bBaseClass) &&
                (fpDevDriver->bSubClass == bSubClass) &&
                (fpDevDriver->bProtocol == bProtocol)){
            bRetValue = fpDevDriver->bDevType;
        }
    }
    if(bRetValue == USB_ERROR)
        return bRetValue;

    //driver was found

    fpDevInfo->bDeviceType = bRetValue;
    fpDevInfo->fpDeviceDriver = fpDevDriver;
    fpDevInfoLocal = (*fpDevDriver->pfnConfigureDevice)(
        fpHCStruc,fpDevInfo,(UINT8*)fpCnfgDesc,
        (UINT16)(UINTN)((char*)fpIntrfDesc - (char*)fpCnfgDesc),fpCnfgDesc->wTotalLength);
    if (!fpDevInfoLocal)
    {
        USB_DEBUG(DEBUG_LEVEL_0, "USB_ReConfigDevice2: Device specific configure failed.\n");
        return USB_ERROR;
    }
    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   hcnum2hcstruc
//
// Description: Search for the HC_STRUC with specified bHCNumber
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

HC_STRUC*
hcnum2hcstruc(
    UINT8 bHCNumber
)
{
    return gUsbData->HcTable[bHCNumber - 1];
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   prepareForLegacyOS
//
// Description: Changes global state of USBSMI module to function properly
//              in non-EFI OS - without support from EFI drivers
//
//              Before call USB BUS is a driver that handles all devices (
//              except hub) and rest of the drivers are delayed. Number of
//              devices are supported by SUBBUS driver and custom EFI driver
//
//              After call returns, USBBUS driver is removed and all drivers
//              that where
//              delayed became active. All USBBUS devices are reconfigured.
//              Devices that are not supported by now active drivers are decon-
//              figured.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
prepareForLegacyOS()
{
                                        //(EIP96616)>
    DEV_INFO* di;
    HC_STRUC* fpHCStruc;
    DEV_INFO* e = gUsbData->aDevInfoTable + COUNTOF(gUsbData->aDevInfoTable);
    int status;

    gCheckUsbApiParameter = FALSE;


    //
    //First Reconfigure all USBBUS device (while drivers are in delayed array)
    //
    for( di = &gUsbData->aDevInfoTable[1]; di != e; ++di ){		//(EIP34448)
        if((di->Flag & DEV_INFO_VALIDPRESENT) == DEV_INFO_VALIDPRESENT &&
            di->bDeviceType == BIOS_DEV_TYPE_USBBUS )
        {
            fpHCStruc = hcnum2hcstruc(di->bHCNumber);
            status = USB_ReConfigDevice(fpHCStruc, di );
            if(status == USB_ERROR){
                //
                // Release DEV_INFO
                //
                di->Flag &= ~DEV_INFO_VALIDPRESENT;
            }
        }
		//di->Flag &= ~DEV_INFO_DEV_BUS;
    }
                                        //<(EIP96616)


    USBKeyRepeat(NULL, 1);  // Disable key repeat
    //gUsbData->dUSBStateFlag |= USB_FLAG_RUNNING_UNDER_OS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USB_ResetAndReconfigDev
//
// Description: This routine resets and reconfigures the device.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
USB_ResetAndReconfigDev(
	HC_STRUC    *HcStruc,
	DEV_INFO    *DevInfo
)
{
	DEV_INFO	*Dev;
	UINT32		Status;
	UINT8		DevAddr;
	UINT8		*Buffer;
    DEV_DESC	*DevDesc;
    CNFG_DESC	*CnfgDesc;
    INTRF_DESC	*IntrfDesc;
	UINT8		ConfigIndx;
	UINT8		IntrfIndx;
	DEV_DRIVER	*DevDriver;
	UINT8		i;
    UINT8       PortStatus;
    UINT8       *DevMiscInfo;
    UINT16      TotalLength;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    gCheckUsbApiParameter = FALSE;

	for (i = 1; i < MAX_DEVICES; i++) {
		Dev = &gUsbData->aDevInfoTable[i];
		if ((Dev->Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT | 
			DEV_INFO_DEV_DUMMY)) != (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT)) {
			continue;
		}
		if ((Dev->bHubDeviceNumber == DevInfo->bHubDeviceNumber) && 
			(Dev->bHubPortNumber == DevInfo->bHubPortNumber) &&
			(Dev->bDeviceType != BIOS_DEV_TYPE_USBBUS)) {
			(*gUsbData->aHCDriverTable[GET_HCD_INDEX(
					HcStruc->bHCType)].pfnHCDDeactivatePolling)(HcStruc, Dev);
		}
	}

    Status = (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDDeinitDeviceData)
                                (HcStruc, DevInfo);
	if (Status != USB_SUCCESS) {
		return Status;
	}
	
	Status = USB_ResetHubPort(HcStruc, DevInfo->bHubDeviceNumber, DevInfo->bHubPortNumber);
	if (Status != USB_SUCCESS) {
		return Status;
	}

	Status = USB_EnableHubPort(HcStruc, DevInfo->bHubDeviceNumber, DevInfo->bHubPortNumber);
	if (Status != USB_SUCCESS) {
		return Status;
	}
    
    PortStatus = USB_GetHubPortStatus(HcStruc, DevInfo->bHubDeviceNumber, DevInfo->bHubPortNumber, TRUE);

    if (PortStatus == USB_ERROR) {
        return USB_ERROR;
    }

    if (!(PortStatus & USB_PORT_STAT_DEV_ENABLED)) {
        return USB_ERROR;
    }

    // Initialize HC specific data before device configuration
    Status = (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDInitDeviceData)(
                        HcStruc, DevInfo, PortStatus, &DevMiscInfo);
    if (Status != USB_SUCCESS) {
        return Status;
    }

    DevInfo->DevMiscInfo = (VOID*)DevMiscInfo;

    Buffer = USB_MemAlloc(GET_MEM_BLK_COUNT(sizeof(DEV_DESC)));
    if (Buffer == NULL) {
        return USB_ERROR;
    }

	DevAddr = DevInfo->bDeviceAddress;
	DevInfo->bDeviceAddress = 0;

	DevDesc = (DEV_DESC*)USB_GetDescriptor(HcStruc, DevInfo, Buffer, sizeof(DEV_DESC), 
				DESC_TYPE_DEVICE, 0);
	if(DevDesc == NULL) {
		USB_MemFree(Buffer, GET_MEM_BLK_COUNT(sizeof(DEV_DESC)));
		return USB_ERROR;
	}

	Status = USB_SetAddress(HcStruc, DevInfo, DevAddr);	
	if (Status != USB_SUCCESS) {
		USB_MemFree(DevDesc, GET_MEM_BLK_COUNT(sizeof(DEV_DESC)));
		return Status;
	}	

	DevInfo->bDeviceAddress = DevAddr;

    Buffer = USB_MemAlloc(GET_MEM_BLK_COUNT(MAX_CONTROL_DATA_SIZE));
    if (Buffer == NULL) {
		USB_MemFree(DevDesc, GET_MEM_BLK_COUNT(sizeof(DEV_DESC)));
        return USB_ERROR;
    }

    for (ConfigIndx = 0; ConfigIndx < DevDesc->NumConfigs; ConfigIndx++) {
        CnfgDesc = (CNFG_DESC*)USB_GetDescriptor(HcStruc, DevInfo, Buffer, 
						0xFF, DESC_TYPE_CONFIG, ConfigIndx);
		if (CnfgDesc == NULL) {
			continue;
		}
		TotalLength = CnfgDesc->wTotalLength;
        if (TotalLength > 0xFF) {
            if (TotalLength > (MAX_CONTROL_DATA_SIZE - 1)) {
                TotalLength = MAX_CONTROL_DATA_SIZE - 1;
            }
            CnfgDesc = (CNFG_DESC*)USB_GetDescriptor(HcStruc, DevInfo, Buffer, 
						TotalLength, DESC_TYPE_CONFIG, ConfigIndx);
            if (CnfgDesc == NULL) {
                continue;
            }
        }

        if (CnfgDesc->bDescType == DESC_TYPE_CONFIG) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDEnableEndpoints)(
                        HcStruc, DevInfo, (UINT8*)CnfgDesc);
        }

		USB_SetConfig(HcStruc, DevInfo, CnfgDesc->bConfigValue);
	
		IntrfDesc = (INTRF_DESC*)CnfgDesc;
		for (IntrfIndx = 0; IntrfIndx < CnfgDesc->bNumInterfaces; IntrfIndx++) {
			do {
				IntrfDesc = (INTRF_DESC*)((UINTN)IntrfDesc + IntrfDesc->bDescLength);
				if ((UINTN)IntrfDesc > ((UINTN)CnfgDesc + CnfgDesc->wTotalLength) ||
					(UINTN)IntrfDesc > ((UINTN)CnfgDesc + MAX_CONTROL_DATA_SIZE)) {
					break;
				}
			} while (IntrfDesc->bDescType != DESC_TYPE_INTERFACE);

			if (IntrfDesc->bDescType != DESC_TYPE_INTERFACE) {
				break;
			}

			for (i = 1; i < MAX_DEVICES; i++) {
				Dev = &gUsbData->aDevInfoTable[i];
				if ((Dev->Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT | 
					DEV_INFO_DEV_DUMMY)) != (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT)) {
					continue;
				}
				if ((Dev->bHubDeviceNumber == DevInfo->bHubDeviceNumber) && 
					(Dev->bHubPortNumber == DevInfo->bHubPortNumber) &&
					(Dev->bConfigNum == CnfgDesc->bConfigValue) &&
					(Dev->bInterfaceNum == IntrfDesc->bInterfaceNum) &&
					(Dev->bAltSettingNum == IntrfDesc->bAltSettingNum)) {
					break;
				}
			}
			if (i == MAX_DEVICES) {
				continue;
			}

			Dev->wVendorId = DevDesc->VendorId;
			Dev->wDeviceId = DevDesc->DeviceId;

			if (Dev->bDeviceType != BIOS_DEV_TYPE_USBBUS) {
				DevDriver = UsbFindDeviceDriverEntry(Dev->fpDeviceDriver);
                if (DevDriver != NULL) {
    				(*DevDriver->pfnConfigureDevice)(HcStruc, Dev, (UINT8*)CnfgDesc,
    	        		(UINT16)((UINTN)IntrfDesc - (UINTN)CnfgDesc), CnfgDesc->wTotalLength);
                }
			}
		}
	}

	USB_MemFree(DevDesc, GET_MEM_BLK_COUNT(sizeof(DEV_DESC)));
	USB_MemFree(Buffer, GET_MEM_BLK_COUNT(MAX_CONTROL_DATA_SIZE));

	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USB_DevDriverDisconnect
//
// Description:  
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
USB_DevDriverDisconnect(
	HC_STRUC    *HcStruc,
	DEV_INFO    *DevInfo
)
{
	DEV_DRIVER* DevDriver;
	UINT8		Index;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    gCheckUsbApiParameter = FALSE;

	DevDriver = UsbFindDeviceDriverEntry(DevInfo->fpDeviceDriver);

	if (DevDriver && DevDriver->pfnDisconnectDevice) {
		DevDriver->pfnDisconnectDevice(DevInfo);

		DevInfo->bDeviceType = 0;
		DevInfo->fpDeviceDriver = NULL;

		for (Index = 0; Index < MAX_DEVICE_TYPES; Index++) {
			DevDriver = &gUsbData->aDevDriverTable[Index];

			if (DevDriver->bDevType == BIOS_DEV_TYPE_USBBUS) {
				DevInfo->bDeviceType = DevDriver->bDevType;
				DevDriver->pfnConfigureDevice(HcStruc, DevInfo, NULL, 0, 0);
				break;
			}
		}
	} else {
		if (DevInfo->IntInEndpoint) {
			// Stop polling the device's interrupt endpoint
			(*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDDeactivatePolling)
							(HcStruc, DevInfo);
			DevInfo->IntInEndpoint = 0;
		}
	}

	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   VALID_DEVINFO
//
// Description:  Checks if DEV_INFO is a valid connected device info
//               Due to hot-plug a DEV_INFO can become invalid in the
//               midle of configuration
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
int VALID_DEVINFO(DEV_INFO* pDevInfo)
{
    return (pDevInfo->Flag & DEV_INFO_VALIDPRESENT)!=0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   USB_AbortConnectHubChildren
//
// Description: Mark DEV_INFO not valid for all the devices connected to a
//              given hub.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USB_AbortConnectHubChildren(
    UINT8 HubAddr
)
{
    UINT8       i;
    DEV_INFO    *Dev = &gUsbData->aDevInfoTable[1];

    for (i=1;  i<MAX_DEVICES; i++, Dev++) {
        if ((Dev->bHubDeviceNumber == HubAddr) && (Dev->Flag & DEV_INFO_VALIDPRESENT)) {
			Dev->Flag &= ~DEV_INFO_DEV_PRESENT;
			if (!(Dev->Flag & DEV_INFO_MASS_DEV_REGD)) {
            	Dev->Flag &= ~DEV_INFO_VALID_STRUC;
			}

            USB_DEBUG(DEBUG_LEVEL_3, "USB: abort device [%x] connected to hub[%x]\n",
                Dev->bDeviceAddress, HubAddr);

            if (Dev->bDeviceType == BIOS_DEV_TYPE_HUB) {
                USB_AbortConnectHubChildren(Dev->bDeviceAddress);
            }
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   USB_FreeDeviceAddress
//
// Description: This routine releases the given device's address by
//              updating gUsbData->dDeviceAddressMap.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USB_FreeDeviceAddress(
    DEV_INFO    *DevInfo
)
{
    UINT8   i;
    UINT8   Found = 0;

    if (DevInfo->bDeviceAddress)
    {
        for (i=1;  i<MAX_DEVICES; i++) {
            if (gUsbData->aDevInfoTable+i != DevInfo &&
                gUsbData->aDevInfoTable[i].bDeviceAddress == DevInfo->bDeviceAddress)
            {
                Found++;
            }
        }
        if (Found == 0){
            //The DevInfo was the only function with allocated address -
            // return the address to the pool
            gUsbData->DeviceAddressMap |= Shl64(1, DevInfo->bDeviceAddress);
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USB_AbortConnectDev
//
// Description: Mark DEV_INFO not valid and release its device address
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USB_AbortConnectDev(
    DEV_INFO* pDevInfo
)
{
    USB_DEBUG(DEBUG_LEVEL_3, "USB: abort connect [%x].flag = %x\n",
          pDevInfo, pDevInfo->Flag);

	pDevInfo->Flag &= ~DEV_INFO_DEV_PRESENT;

	if (!(pDevInfo->Flag & DEV_INFO_MASS_DEV_REGD)) {
	    pDevInfo->Flag &= ~DEV_INFO_VALID_STRUC;
	    if (pDevInfo->bDeviceAddress == 0) return;

	    USB_FreeDeviceAddress(pDevInfo);
	}

    // Remove children (if any) from aborted parent hub device.
    // Assume the child device has not been connected since
    // the hub has to be connected first.
    if (pDevInfo->bDeviceType == BIOS_DEV_TYPE_HUB) {
        USB_AbortConnectHubChildren(pDevInfo->bDeviceAddress);
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   USB_SmiQueuePut
//
// Description: Puts the pointer pointer into the queue for processing,
//              updates queue head and tail.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USB_SmiQueuePut(VOID * d)
{
    QUEUE_T* q = &gUsbData->QueueCnnctDisc;

    while (q->head >= q->maxsize) {
        q->head -= q->maxsize;
    }

    q->data[q->head++] = d;
    if (q->head == q->maxsize) {
        q->head -= q->maxsize;
    }
    if (q->head == q->tail) {
        //Drop data from queue
        q->tail++;
        while (q->tail >= q->maxsize) {
            q->tail -= q->maxsize;
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:        QueuePutMsg
//
// Description: Add a variable size item to the queue
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USB_SmiQueuePutMsg( QUEUE_T* q, VOID * d, int sz )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    if (q->head + sz > q->maxsize) {
        q->head = 0;
    }
#if USB_RUNTIME_DRIVER_IN_SMM
    Status = AmiValidateMemoryBuffer((VOID*)((UINTN)q->data + q->head), sz);
    if (EFI_ERROR(Status)) {
        return;
    }
#endif
    MemCopy((UINT8*)d, (UINT8*)((UINTN)q->data + q->head), sz);
    q->head += sz;
    if(q->head==q->maxsize) q->head = 0;
    if(q->head==q->tail){
        //Drop data from queue
        q->tail+=sz;
        if( q->tail >= q->maxsize ) q->tail = 0;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CheckDeviceLimit
//
// Description: Verifies whether the number of initialized devices of a given
//              class has reached the limit.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
CheckDeviceLimit(
    UINT8   BaseClass
)
{
    URP_STRUC Urp;
    UINT8 DevNumber;

    Urp.bFuncNumber = USB_API_CHECK_DEVICE_PRESENCE;
    Urp.bSubFunc = 1;
    Urp.ApiData.ChkDevPrsnc.fpHCStruc = NULL;
    Urp.ApiData.ChkDevPrsnc.bDevType = BaseClass;

    USBAPI_CheckDevicePresence(&Urp);

    if (Urp.bRetValue == USB_SUCCESS)
    {
        DevNumber = Urp.ApiData.ChkDevPrsnc.bNumber;
        if ((BaseClass == BASE_CLASS_HID)
              && ((USB_DEV_HID_COUNT == 0) || (DevNumber == USB_DEV_HID_COUNT)))
        {
            USB_DEBUG(3, "Reached the limit of supported HIDs (%d); skipping this device.\n", USB_DEV_HID_COUNT);
            return TRUE;
        }

        if ((BaseClass == BASE_CLASS_HUB)
              && ((USB_DEV_HUB_COUNT == 0) || (DevNumber == USB_DEV_HUB_COUNT)))
        {
            USB_DEBUG(3, "Reached the limit of supported HUBs (%d); skipping this device.\n", USB_DEV_HUB_COUNT);
            return TRUE;
        }

        if ((BaseClass == BASE_CLASS_MASS_STORAGE)
              && ((USB_DEV_MASS_COUNT == 0) || (DevNumber == USB_DEV_MASS_COUNT)))
        {
            USB_DEBUG(3, "Reached the limit of supported Mass Storage Devices (%d); skipping this device.\n", USB_DEV_MASS_COUNT);
            return TRUE;
        }
        if ((BaseClass == BASE_CLASS_CCID_STORAGE)
              && ((USB_DEV_CCID_COUNT == 0) || (DevNumber == USB_DEV_CCID_COUNT+1)))
        {
            USB_DEBUG(3, "Reached the limit of supported CCID Devices (%d); skipping this device.\n", USB_DEV_CCID_COUNT);
            return TRUE;
        }
    }
    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbControlTransfer
//
// Description: 
//
// Input:  
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbControlTransfer(
	HC_STRUC*   HcStruc,
    DEV_INFO*	DevInfo,
	DEV_REQ		DevReq,
	UINT16		Timeout,
	VOID*		Buffer)
{
	UINT16	Status;
	UINT16  SavedTimeout;

	SavedTimeout = gUsbData->wTimeOutValue;
	gUsbData->wTimeOutValue = Timeout;

    Status = (*gUsbData->aHCDriverTable[
				GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDControlTransfer)(
                HcStruc,
                DevInfo,
                DevReq.wRequestType,
                DevReq.wIndex,
                DevReq.wValue,
                Buffer,
                DevReq.wDataLength);

	gUsbData->wTimeOutValue = SavedTimeout;

	return DevReq.wDataLength && (Status == 0)? USB_ERROR : USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbInterruptTransfer
//
// Description: This function executes an interrupt transaction on the USB.
//
// Input:  
//  HcStruc     Pointer to HCStruc of the host controller.
//  DevInfo     DeviceInfo structure (if available else 0).
//  EndpointAddress The destination USB device endpoint to which the device request 
//                    is being sent.
//  MaxPktSize  Indicates the maximum packet size the target endpoint is capable 
//              of sending or receiving.
//  Buffer      Buffer containing data to be sent to the device or buffer to be
//              used to receive data.
//  Length      Length request parameter, number of bytes of data to be transferred.
//  Timeout     Indicates the maximum time, in milliseconds, which the transfer 
//              is allowed to complete.
//
// Output: USB_SUCCESS or USB_ERROR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbInterruptTransfer (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       EndpointAddress,
    UINT16      MaxPktSize,
    VOID        *Buffer,
    UINT16      Length,
    UINT16		Timeout
)
{
    UINT16  SavedTimeout;
    UINT16  BytesTransferred;

    SavedTimeout = gUsbData->wTimeOutValue;
    gUsbData->wTimeOutValue = Timeout;

    BytesTransferred = (*gUsbData->aHCDriverTable[
                GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDInterruptTransfer)(
                HcStruc,
                DevInfo,
                EndpointAddress,
                MaxPktSize,
                Buffer,
                Length);

    gUsbData->wTimeOutValue = SavedTimeout;

    if (BytesTransferred == 0) {
        return USB_ERROR;
    } else {
        return USB_SUCCESS;
    }
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   USB_EnableEndpointsDummy
//
// Description: Dummy HC API function used by the HC drivers that do not need
//              to implement enable endpoint function.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USB_EnableEndpointsDummy (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Desc
)
{
    return USB_SUCCESS;
}

UINT8
USB_InitDeviceDataDummy (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       PortStatus,
    UINT8       **DeviceData
)
{
    *DeviceData = NULL;
    return USB_SUCCESS;
}

UINT8
USB_DeinitDeviceDataDummy (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo
)
{
    return USB_SUCCESS;
}

										//(EIP54018+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        LocatePwrCapOffset
//
// Description: 
//  This function locate power management capability offset
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
LocatePwrCapOffset (
    IN UINT16 BusDevFunc
)
{
#if USB_RUNTIME_DRIVER_IN_SMM
    UINT16  StatusReg;
    UINT8   CapOffset;
    EFI_PCI_CAPABILITY_HDR CapHeader;

    // Check if device supports extended capabilities
    StatusReg = (UINT16)ReadPCIConfig(BusDevFunc, PCI_STATUS_REGISTER_OFFSET);
    if((StatusReg & PCI_STS_CAPABILITY) == 0) {
        return 0;
    }    
    // Get offset of first capability structure
    CapOffset = (UINT8)ReadPCIConfig(BusDevFunc, EFI_PCI_CAPABILITY_PTR);
    // Check capabilities until PMI is found or no more capabilities
    while (CapOffset) {
        CapHeader.CAP_HDR = (UINT16)ReadPCIConfig(BusDevFunc, CapOffset);
        // If PMI block, return offset 
        if(CapHeader.CapabilityID == PCI_CAP_ID_PMI) {
            return CapOffset;
        }        
        // If not, check for next offset
        CapOffset = CapHeader.NextItemPtr;
    }
#endif
    return 0;
}

#if USB_S5_WAKEUP_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        ResumePciBridge
//
// Description: 
//  This function resumed PciBridge
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ResumePciBridge(
    UINT16      BusDevFun
)
{
    UINT32      PmStaCtlReg;
    UINT32      PmCapReg;
    UINT8       PwrCapPtr;
    UINT8       PciCommand;

    PwrCapPtr = LocatePwrCapOffset(BusDevFun);
    
    if (PwrCapPtr) {
        PmCapReg = ReadPCIConfig(BusDevFun, PwrCapPtr);
        PmStaCtlReg = ReadPCIConfig(BusDevFun, PwrCapPtr + 0x04);
        if (PmCapReg & (BIT31 | BIT30)) {
            PmStaCtlReg |= BIT8;
        }
        if (PmStaCtlReg & (BIT0 | BIT1)) {
            PmStaCtlReg &= ~(BIT0 | BIT1);
        }
        DwordWritePCIConfig(BusDevFun, PwrCapPtr + 0x04, PmStaCtlReg);
    }
    
    PciCommand = (UINT8)ReadPCIConfig(BusDevFun, PCI_COMMAND_REGISTER_OFFSET);
    PciCommand |= (PCI_CMD_MEMORY_SPACE + PCI_CMD_BUS_MASTER);
    ByteWritePCIConfig(BusDevFun, PCI_COMMAND_REGISTER_OFFSET, PciCommand);
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        StopPciBridge
//
// Description: 
//  This function stopped PciBridge
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
StopPciBridge(
    UINT16      BusDevFun
)
{
    UINT32      PmStaCtlReg;
    UINT8       PwrCapPtr;
    UINT8       PciCommand;
    
    PwrCapPtr = LocatePwrCapOffset(BusDevFun);
    
    if (PwrCapPtr) {
        PmStaCtlReg = ReadPCIConfig(BusDevFun, PwrCapPtr + 0x04);
        PmStaCtlReg |= (BIT0 + BIT1);
        DwordWritePCIConfig(BusDevFun, PwrCapPtr + 0x04, PmStaCtlReg);
    }
    
    PciCommand = (UINT8)ReadPCIConfig(BusDevFun, PCI_COMMAND_REGISTER_OFFSET);
    PciCommand &= (~PCI_CMD_BUS_MASTER);
    ByteWritePCIConfig(BusDevFun, PCI_COMMAND_REGISTER_OFFSET, PciCommand);
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        EnablePciBridge
//
// Description: 
//  This function scaned PciBridge
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ScanPciBridge(
    UINT16      *BridgePciAddr
)
{
    HC_STRUC    *HcStruc;
    UINT8       HcBus[256];
    UINT16      HcBusIndex = 0;
    UINT16      MaxHcBus = 0;
    UINT16      i;
	UINT16	    PciAddr;
    UINT16      PciBus;
    UINT16      PciDev;
    UINT16      PciFun;
    UINT16      BridgeIndex = 255;
    UINT16      DownstreamBus;
    
    for (i = 0; i < gUsbData->HcTableCount; i++) {
        HcStruc = gUsbData->HcTable[i];
        if (HcStruc == NULL) {
            continue;
        }

        if (!(HcStruc->dHCFlag & HC_STATE_USED)) {
        	continue;
        }

        if (HcStruc->dHCFlag & HC_STATE_EXTERNAL) {
            HcBus[HcBusIndex] = (UINT8)(HcStruc->wBusDevFuncNum >> 8);
            if(MaxHcBus < HcBus[HcBusIndex]) {
                MaxHcBus = HcBus[HcBusIndex];
            }
            HcBusIndex++;
        }
    }
    
    for (PciBus = 0; PciBus  < MaxHcBus; PciBus++) {
        for (PciDev = 0; PciDev < 0x20 ; PciDev++) {
            PciAddr = (UINT16)((PciBus << 8) | (PciDev << 3) | 0);  
            if (ReadPCIConfig(PciAddr, PCI_VID) != 0xffffffff) {
                PciFun = ((UINT8)ReadPCIConfig(PciAddr, PCI_HDR) & 0x80) ? 8 : 1;
                do {
                    PciFun--;
                    PciAddr = (UINT16)((PciBus << 8) | (PciDev << 3) | PciFun);
                    if (PciFun != 0) {
                        if (ReadPCIConfig(PciAddr, PCI_VID) == 0xffffffff) {
                            continue;
                        }
                    }
                    if (ReadPCIConfig(PciAddr, PCI_SCC) == 0x0604) {
                        DownstreamBus = (UINT16)ReadPCIConfig(PciAddr, PCI_SBUS);
                        for (i = 0; i < HcBusIndex; i++) {
                            if ((HcBus[i] >= (UINT8)(DownstreamBus)) &&
                                (HcBus[i] <= (UINT8)(DownstreamBus >> 8))) {
                                ResumePciBridge(PciAddr);
                                BridgePciAddr[BridgeIndex] = PciAddr;
                                BridgeIndex--;
                                break;
                            }
                        }
                    }
                } while (PciFun);
            }
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       UsbSuspendHubPort
//
// Description: This function suspends the hub port
//
// Input:     DevInfo   Device info pointer
//
// Output:     Status: EFI_SUCCESS = Success
//                     EFI_DEVICE_ERROR = Failure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbSuspendHubPort (
    DEV_INFO    *DevInfo
)
{
    UINT32      Index;
    DEV_INFO    *HubDevInfo;
    HC_STRUC    *HcStruc;
	UINT16      OrgTimeOutValue;

    if (DevInfo->bHubDeviceNumber & BIT7) {
        return EFI_SUCCESS;
    }

    for (Index = 1; Index < MAX_DEVICES; Index++) {
        HubDevInfo = &gUsbData->aDevInfoTable[Index];
        if ((HubDevInfo->Flag & DEV_INFO_VALIDPRESENT) != DEV_INFO_VALIDPRESENT) {
			continue;
		}
        if (DevInfo->bHubDeviceNumber == HubDevInfo->bDeviceAddress) {
            HcStruc = gUsbData->HcTable[HubDevInfo->bHCNumber - 1];
            
        	OrgTimeOutValue = gUsbData->wTimeOutValue;
        	gUsbData->wTimeOutValue = USB_SUSPEND_HUB_PORT_TIMEOUT_MS;
            
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(
                    HcStruc->bHCType)].pfnHCDControlTransfer)(
                    HcStruc,
                    HubDevInfo,
                    (UINT16)HUB_RQ_SET_PORT_FEATURE,
                    DevInfo->bHubPortNumber,
                    (UINT16)PortSuspend,
                    0, 0); 
            
            gUsbData->wTimeOutValue = OrgTimeOutValue;
            return EFI_SUCCESS;
        }
    }
    return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbSuspendDevices
//
// Description: 
//  This function suspends usb devices.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbSuspendDevices (
    VOID
)
{
    UINT32      Index;
    DEV_INFO    *DevInfo;
    
    for (Index = MAX_DEVICES; Index > 0; Index--) {

        DevInfo = &gUsbData->aDevInfoTable[Index];
	
        if ((DevInfo->Flag & DEV_INFO_VALIDPRESENT) != DEV_INFO_VALIDPRESENT) {
			continue;
		}
        UsbSuspendHubPort(DevInfo);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbSuspend
//
// Description: 
//  This function suspend USB
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbSuspend(
    VOID
)
{
    HC_STRUC    *HcStruc;
    DEV_INFO    *DevInfo;
    CNFG_DESC   *CnfgDesc;
    UINT8       *Buffer;
    UINT16      i;
    UINT32      PmStaCtlReg;
    UINT32      PmCapReg;
    UINT16      BridgePciAddr[256];
    UINT32      HcLowBaseAddress;
    UINT32      HcHighBaseAddress;
    UINT16      HcIoAddress;
    UINT16	    OrgTimeOutValue;

    for (i = 0; i < 256; i++) {
        BridgePciAddr[i] = 0;
    }

    ScanPciBridge(BridgePciAddr);

    for (i = 0; i < gUsbData->HcTableCount; i++) {
        HcStruc = gUsbData->HcTable[i];
        if (HcStruc == NULL) {
            continue;
        }

        if (!(HcStruc->dHCFlag & HC_STATE_USED)) {
        	continue;
        }

        HcStruc->PwrCapPtr = LocatePwrCapOffset(HcStruc->wBusDevFuncNum);	
        if (HcStruc->PwrCapPtr) {
            PmCapReg = ReadPCIConfig(HcStruc->wBusDevFuncNum,
                                HcStruc->PwrCapPtr);
            PmStaCtlReg = ReadPCIConfig(HcStruc->wBusDevFuncNum,
                                        HcStruc->PwrCapPtr + 0x04);
            if (PmCapReg & (BIT31 | BIT30)) {
                PmStaCtlReg |= BIT8;
            }
            if (PmStaCtlReg & (BIT0 | BIT1)) {
                PmStaCtlReg &= ~(BIT0 | BIT1);
            }
            DwordWritePCIConfig(HcStruc->wBusDevFuncNum,
                            HcStruc->PwrCapPtr + 0x04, PmStaCtlReg);
		}
        if (HcStruc->bHCType == USB_HC_UHCI) {
            HcIoAddress = (UINT16)ReadPCIConfig(HcStruc->wBusDevFuncNum, USB_IO_BASE_ADDRESS);
            if (HcStruc->BaseAddress != HcIoAddress) {
                WordWritePCIConfig(HcStruc->wBusDevFuncNum,
                        USB_IO_BASE_ADDRESS, (UINT32)HcStruc->BaseAddress);
            }
            ByteWritePCIConfig(HcStruc->wBusDevFuncNum,
	                PCI_CMD, PCI_CMD_IO_SPACE | PCI_CMD_BUS_MASTER);
        } else {       
            HcLowBaseAddress = ReadPCIConfig(HcStruc->wBusDevFuncNum, PCI_BAR0);
            if ((((UINT8)HcLowBaseAddress & (BIT1 |BIT2)) == BIT2) && ((sizeof(VOID*) / sizeof(UINT32)) == 2)) {
                HcHighBaseAddress = ReadPCIConfig(HcStruc->wBusDevFuncNum, PCI_BAR1);
                if(HcStruc->BaseAddress != ((UINTN)(HcLowBaseAddress & 0xFFFFFFF0)) +
                    (Shl64((UINTN)HcHighBaseAddress, 32))) {
                    DwordWritePCIConfig(HcStruc->wBusDevFuncNum,
                        PCI_BAR0, (UINT32)HcStruc->BaseAddress);
                    DwordWritePCIConfig(HcStruc->wBusDevFuncNum,
                        PCI_BAR1, (UINT32)(Shr64(HcStruc->BaseAddress, 32)));
                }
            } else {
                if (HcStruc->BaseAddress != (HcLowBaseAddress & 0xFFFFFFF0)) {
                    DwordWritePCIConfig(HcStruc->wBusDevFuncNum,
                        PCI_BAR0, (UINT32)HcStruc->BaseAddress);
                }
            }
		    ByteWritePCIConfig(HcStruc->wBusDevFuncNum,
	                PCI_CMD, PCI_CMD_MEMORY_SPACE | PCI_CMD_BUS_MASTER);
        }
    }

    // Remove the prsent flag of devices before we reenumerate.
    for (i = 1; i < MAX_DEVICES; i++) {
        DevInfo = &gUsbData->aDevInfoTable[i];
        DevInfo->Flag &= ~DEV_INFO_DEV_PRESENT;
    }

    gUsbData->UsbSetupData.UsbMassDriverSupport = FALSE;
    gUsbData->bHandOverInProgress = FALSE;

    //Start XHCI
    StartControllerType(USB_HC_XHCI);
    //Start EHCI
    StartControllerType(USB_HC_EHCI);
    //Start UHCI
    StartControllerType(USB_HC_UHCI);
    //Start OHCI
    StartControllerType(USB_HC_OHCI);

    //Wait for the usb devices connect.
    FixedDelay(50 * 1000);
    
    USB_EnumerateRootHubPorts(USB_HC_XHCI);
    USB_EnumerateRootHubPorts(USB_HC_EHCI);
    USB_EnumerateRootHubPorts(USB_HC_UHCI);
    USB_EnumerateRootHubPorts(USB_HC_OHCI);
 
    Buffer = USB_MemAlloc(sizeof(CNFG_DESC));

    OrgTimeOutValue = gUsbData->wTimeOutValue;
    gUsbData->wTimeOutValue = 500;
    
    for (i = 1; i < MAX_DEVICES; i++) {

        DevInfo = &gUsbData->aDevInfoTable[i];
        
        if ((DevInfo->Flag & DEV_INFO_VALIDPRESENT) != DEV_INFO_VALIDPRESENT) {
			continue;
		}
        
        if (DevInfo->bDeviceType == BIOS_DEV_TYPE_HUB) {
            continue;
        }
        
        HcStruc = gUsbData->HcTable[DevInfo->bHCNumber - 1];

        CnfgDesc = (CNFG_DESC*)USB_GetDescriptor(
                            HcStruc,
                            DevInfo,
                            Buffer,
                            sizeof(CNFG_DESC),
                            DESC_TYPE_CONFIG,
                            0);

        if (CnfgDesc == NULL) {
            continue;
        }
        
        //Check the device have the capable of remote wakeup
        if (CnfgDesc ->bConfigFlags & BIT5) {
            //Send device wakeup command to the device
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(
                    HcStruc->bHCType)].pfnHCDControlTransfer)(
                    HcStruc,
                    DevInfo,
                    (UINT16)USB_RQ_SET_FEATURE,
                    0,
                    (UINT16)USB_FSEL_DEV_REMOTE_WAKEUP,
                    0, 0); 
        
        }

    }

    gUsbData->wTimeOutValue = OrgTimeOutValue;

    USB_MemFree(Buffer, sizeof(CNFG_DESC));

    UsbSuspendDevices();

    for (i = 0; i < gUsbData->HcTableCount; i++) {
        HcStruc = gUsbData->HcTable[i];
        if (HcStruc == NULL) {
            continue;
        }

        //Global suspend host
        if (HcStruc->dHCFlag & HC_STATE_RUNNING) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(
                HcStruc->bHCType)].pfnHCDGlobalSuspend)(HcStruc);
            if (HcStruc->PwrCapPtr) {
                PmStaCtlReg = ReadPCIConfig(HcStruc->wBusDevFuncNum,
                                        HcStruc->PwrCapPtr + 0x04);
                PmStaCtlReg |= (BIT0 + BIT1);
                DwordWritePCIConfig(HcStruc->wBusDevFuncNum,
                            HcStruc->PwrCapPtr + 0x04, PmStaCtlReg);
            }
        }    
    }

    for (i = 0; i < 256; i++) {
        if (BridgePciAddr[i] != 0) {
            StopPciBridge(BridgePciAddr[i]);
        }
    }

    UsbSbEnablePme();

}

#endif
										//<(EIP54018+)
UINT8
UsbGetDataToggle(
	DEV_INFO	*DevInfo,
	UINT8		EndpointAddr
)
{
    DEV_INFO    *DevInfoToToggle;
    UINT8       ToggleBit = (EndpointAddr & 0xF) - 1;
    UINT16      *DataSync;
    EFI_STATUS  Status;

    if (DevInfo->fpLUN0DevInfoPtr) {
        Status = UsbDevInfoValidation(DevInfo->fpLUN0DevInfoPtr);
        if (EFI_ERROR(Status)) {
            return 0;
        }  
        DevInfoToToggle = DevInfo->fpLUN0DevInfoPtr;
    } else {
        DevInfoToToggle = DevInfo;
    }

    if (EndpointAddr & BIT7) {
        DataSync = &DevInfoToToggle->wDataInSync;
    } else {
        DataSync = &DevInfoToToggle->wDataOutSync;
    }

    return (UINT8)((*DataSync) >> ToggleBit) & 0x1;
}

VOID
UsbUpdateDataToggle(
	DEV_INFO	*DevInfo,
	UINT8		EndpointAddr,
	UINT8		DataToggle
)
{
    DEV_INFO    *DevInfoToToggle;
    UINT8       ToggleBit = (EndpointAddr & 0xF) - 1;
    UINT16      *DataSync;
    EFI_STATUS  Status;

    if (DevInfo->fpLUN0DevInfoPtr) {
        Status = UsbDevInfoValidation(DevInfo->fpLUN0DevInfoPtr);
        if (EFI_ERROR(Status)) {
            return;
        }  
        DevInfoToToggle = DevInfo->fpLUN0DevInfoPtr;
    } else {
        DevInfoToToggle = DevInfo;
    }

    if (EndpointAddr & BIT7) {
        DataSync = &DevInfoToToggle->wDataInSync;
    } else {
        DataSync = &DevInfoToToggle->wDataOutSync;
    }
    
    *DataSync &= (UINT16)~(1 << ToggleBit);
    *DataSync |= (UINT16)(DataToggle << ToggleBit);
    return;
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
