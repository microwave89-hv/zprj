//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2015, American Megatrends, Inc.          **
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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/usbbus.c 101   11/04/15 9:52p Wilsonlee $
//
// $Revision: 101 $
//
// $Date: 11/04/15 9:52p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/usbbus.c $
// 
// 101   11/04/15 9:52p Wilsonlee
// TAG]  		EIP241067
// [Category]  	Improvement
// [Description]  	Add the device descriptor to the DEV_INFO structure.
// [Files]  		usb.c, usbdef.h, xhci.c, usbbus.c, AmiUsbController.h
// 
// 100   5/28/15 5:01a Wilsonlee
// [TAG]  		EIP218997
// [Category]  	Improvement
// [Description]  	Break the GetQueue loop if UninstallDevice is failed.
// [Files]  		usbbus.c, efiusbkb.c, efiusbmass.c, efiusbms.c,
// efiusbpoint.c, efiusbhid.c
// 
// 99    5/26/15 10:49p Wilsonlee
// [TAG]  		EIP219177
// [Category]  	Improvement
// [Description]  	Fixed static code analysis issues in Usb module.
// [Files]  		UsbInt13.c, ehci.c, usbbus.c
// 
// 98    4/29/15 11:29p Wilsonlee
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
// 97    3/20/15 7:19a Wilsonlee
// [TAG]  		EIP209904
// [Category]  	Improvement
// [Description]  	Remove "ASSERT(HubNode != NULL);" because it will be to
// see a DEV_INFO from not-yet-installed hub in the some cases.
// [Files]  		usbbus.c
// 
// 96    11/23/14 9:11p Wilsonlee
// [TAG]  		EIP188119
// [Category]  	Improvement
// [Description]  	Disconnect devices and uninstall usb device related
// protocols if we call stop api for the host controllers.
// [Files]  		usbkbd.c, usbbus.c, uhcd.h, uhcd.c
// 
// 95    10/23/14 10:07p Wilsonlee
// [TAG]  		EIP183572
// [Category]  	Improvement
// [Description]  	Change tpl of UsbHcOnTimer to EFI_TPL_CALLBACK
// [Files]  		efiusbmass.c, usbbus.c
// 
// 94    9/30/14 2:07a Wilsonlee
// [TAG]  		EIP183572
// [Category]  	Improvement
// [Description]  	Change tpl of UsbHcOnTimer to EFI_TPL_CALLBACK
// [Files]  		efiusbmass.c, usbbus.c
// 
// 93    9/29/14 11:37p Wilsonlee
// [TAG]  		EIP181169
// [Category]  	Improvement
// [Description]  	Support XHCI 1.1/USB 3.1.
// [Files]  		xhci.c, xhci.h, usb.c, usbbus.c, usbdef.h, UsbHc.h
// 
// 92    9/04/14 7:27a Wilsonlee
// [TAG]  		EIP179794
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Unplug RTKUSB LAN on BSU cause system hang up.
// [RootCause]  	We return the wrong status for UsbIoTransfers if the
// device is not present.
// [Solution]  	Return EFI_DEVICE_ERROR if the device is not present.
// [Files]  		usbbus.c
// 
// 91    8/20/14 10:03p Wilsonlee
// [TAG]  		EIP180089
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	After updated to AMI_USB_07, we get EHCI TIMEOUT for
// specific mouse.
// [RootCause]  	This device may not respond getting string descriptors
// which describing manufacturer, product and the device's serial number.
// [Solution]  	Set the timeout value to 100 ms, the original is 20 secs.
// [Files]  		usbbus.c, usbdef.h
// 
// 90    7/30/14 5:16a Wilsonlee
// [TAG]  		EIP176293
// [Category]  	Improvement
// [Description]  	The changes are for DisplayLink USB Network driver.
// [Files]  		usbbus.c, usb.c
// 
// 89    7/06/14 11:02p Wilsonlee
// [TAG]  		EIP176289
// [Category]  	Improvement
// [Description]  	The device path for multiple LUN devices is created
// using MSG_DEVICE_LOGICAL_UNIT_DP node.
// [Files]  		usbbus.c
// 
// 88    6/26/14 1:18a Wilsonlee
// [TAG]  		EIP173387
// [Category]  	Improvement
// [Description]  	Remove TODO comments.
// [Files]  		usbsetup.c, xhci.c, usbmass.c, usbCCID.c, usb.c, uhci.c,
// syskbc.c, usbport.c, usbbus.c, uhcd.c, UsbBotPeim.c, PeiXhci.c,
// PeiEhci.c
// 
// 87    4/30/14 5:27a Wilsonlee
// [TAG]  		EIP164842
// [Category]  	Improvement
// [Description]  	Check if the devices have put into to our queue before
// we put them.
// [Files]  		UsbInt13.c, amiusb.c, ehci.c, ohci.c, usb.c, usbdef.h,
// usbmass.c, xhci.c, amiusbhc.c, efiusbmass.c, uhcd.c, usbbus.c, usbsb.c
// 
// 86    4/29/14 8:37p Wilsonlee
// [TAG]  		EIP165318
// [Category]  	Improvement
// [Description]  	Retry the DisconnectController() from a timer event
// until it succeeds if it fails.
// [Files]  		usbbus.c
// 
// 85    4/03/14 4:40a Wilsonlee
// [TAG]  		EIP158119
// [Category]  	Improvement
// [Description]  	Change parent port number of USB device paths to
// 0-based.
// [Files]  		usbbus.c
// 
// 84    12/20/13 3:42a Wilsonlee
// [TAG]  		EIP147402
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System hang at 0xA2 if plugging Seagate USB device.
// [RootCause]  	This device doesn't respond get descriptor command after
// we install mass storage driver.
// [Solution]  	We store the string descriptor when we load the langid
// table.
// [Files]  		usbbus.c, usbbus.h
// 
// 83    11/04/13 2:58a Wilsonlee
// [TAG]  		EIP135009
// [Category]  	Improvement
// [Description]  	Retry 3 times when devices stall the get descriptor
// command.
// [Files]  		usbbus.c
// 
// 82    9/04/13 5:47a Wilsonlee
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
// 81    8/16/13 4:19a Ryanchou
// 
// 80    7/30/13 2:31a Roberthsu
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
// [Files]         usb.c,usbmass.c,efiusbmass.c,uhcd.c,usbbus.c
// 
// 79    4/14/13 11:01p Wilsonlee
// [TAG]  		EIP120345
// [Category]  	Improvement
// [Description]  	EFI_USB_IO_PROTOCOL.UsbGetStringDescriptor() returns
// EFI_SUCCESS if String is NULL.
// [Files]  		usbbus.c
// 
// 78    1/23/13 4:38a Wilsonlee
// [TAG]  		EIP109538
// [Category]  	Improvement
// [Description]  	Fix the code check error result.
// [Files]  		usbkbd.c, usbCCID.c, usbbus.c, efiusbccid.c
// 
// 77    1/22/13 2:39a Wilsonlee
// [TAG]  		EIP110305
// [Category]  	Improvement
// [Description]  	Set the device address after we send the first
// get-device-descriptor command.
// [Files]  		usbmass.c, usb.c, usbdef.h, usbbus.c, efiusbmass.c, uhcd.c,
// usbport.c
// 
// 76    1/11/13 4:19a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 75    1/07/13 12:57a Wilsonlee
// [TAG]  		EIP111305
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	It is failed at reloading the usb keyboard driver.
// [RootCause]  	The DEV_INFO_VALID_STRUC and DEV_INFO_DEV_PRESENT flag
// were cleared when the usb driver is disconnecting.
// [Solution]  	We should not clear the DEV_INFO_VALID_STRUC and
// DEV_INFO_DEV_PRESENT flag at USBKBDDisconnectDevice.
// [Files]  		usbkbd.c, usbbus.c
// 
// 74    11/10/12 6:41a Ryanchou
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
// 73    11/09/12 12:25a Wilsonlee
// [TAG]  		EIP104910
// [Category]  	Improvement
// [Description]  	Raise the tpl to TPL_CALLBACK when we connect or
// disconnect controller for the usb device.
// [Files]  		usbbus.c
// 
// 72    9/12/12 3:49a Wilsonlee
// [TAG]  		EIP100371
// [Category]  	Improvement
// [Description]  	Set the tpl to TPL_APPLICATION when we connect or
// disconnect controller for the usb device.
// [Files]  		usbbus.c
// 
// 71    9/04/12 6:15a Ryanchou
// [TAG]  		EIP99123
// [Category]  	Improvement
// [Description]  	Roll back EIP79221 changes that has device
// compatibility issue.
// [Files]  		usbbus.c, usbbus.h
// 
// 70    8/29/12 10:03p Wilsonlee
// [TAG]  		EIP97609
// [Category]  	Improvement
// [Description]  	Handle the set interface request in the
// UsbIoControlTransfer.
// [Files]  		usbbus.c
// 
// 69    6/01/12 5:44a Ryanchou
// [TAG]  		EIP90535
// [Category]  	Improvement
// [Description]  	Increase the buffer size in the function
// GetUsbDescriptor.
// [Files]  		usbbus.c
// 
// 68    5/04/12 6:43a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 67    5/04/12 5:33a Wilsonlee
// [TAG]  		EIP89307
// [Category]  	Improvement
// [Description]  	Modify incorrect #pragma pack directive.
// [Files]  		amidef.h, amiusb.c, ehci.h, ohci.c, ohci.h, uhci.h, usb.c,
// usbdef.h, xhci.h, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h,
// UsbIo.h
// 
// 66    4/05/12 7:34a Wilsonlee
// [TAG]  		EIP84215
// [Category]  	Improvement
// [Description]  	Update the DataSync in LUN0 DevInfo if it is a
// multi-lun device. 
// [Files]  		usbbus.c
// 
// 65    2/16/12 8:54p Wilsonlee
// [TAG]  		EIP81612
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Add EFI_USB_SPEED_SUPER in EFI_USB2_HC_PROTOCOL
// according to UEFI 2.3.1 spec
// [Files]  		usb.c, usbbus.c, amiusbhc.c
// 
// 64    1/31/12 12:34a Roberthsu
// [TAG]           EIP79221
// [Category]      Improvement
// [Description]   Add get serial number and product string descriptor.
// [Files]         usbbus.c,usbbus.h
// 
// 63    1/13/12 4:26a Ryanchou
// [TAG]  		EIP47348
// [Category]  	New Feature
// [Description]  	Support for USB Port Reset function.
// [Files]  		amiusb.c, amiusb.h, amiusbhc.c, uhci.c, usb.c, usbbus.c,
// usbbus.h, usbmass.c
// 
// 62    1/06/12 1:02a Rajeshms
// [TAG]  		EIP62737
// [Category]  	Improvement
// [Description]  	Added USB Device number into USB mass device name
// string based on SDL Token.
// [Files]  		Usb.sdl, usbport.c, usbmass.c, UsbInt13.h, UsbInt13.c,
// usbbus.c, Bfiusb.equ
// 
// 61    12/14/11 2:09a Ryanchou
// [TAG]  		EIP76397
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	ASSERT occurred when executing "reconnect -r" under shell
// [RootCause]  	The EIP63188 changes locate all USB controllers at one
// time, the "reconnect -r" will connect ConIn and ConOut first, so USB
// driver only locate a controller.
// [Solution]  	Rollback the EIP63188 changes to avoid this issue.
// [Files]  		amiusbhc.c, efiusbhid.c, efiusbkb.c, uhcd.c, uhcd.h,
// usbbus.c usbhid.c
// 
// 60    8/05/11 7:31a Ryanchou
// [TAG]  		EIP66231
// [Category]  	Improvement
// [Description]  	Remove token POINT_SUPPORT.Add token USB_DEV_POINT.Add
// check core version in point driver.Add check device descriptor to send
// get lang id command.Modify check button usage page.
// [Files]  		efiusbhid.c, efiusbpoint.c, usbbus.c, usbhid.c, usbpoint.c,
// usbsrc.sdl
// 
// 59    7/13/11 4:10a Ryanchou
// [TAG]  		EIP59332
// [Category]  	Improvement
// [Description]  	Modified the Stop function for UHCD and USBBUS to
// properly stop devices and uninstall the protocols.
// [Files]  		uhcd.c, uhcd.h, uhci.c, usbbus.c, UsbInt13.c, usbmisc.c
// 
// 58    6/23/11 6:49a Ryanchou
// [TAG]  		EIP61644
// [Category]  	Improvement
// [Description]  	Uninstall USB bus driver only DEV_INFO_DEV_BUS is set.
// [Files]  		usbbus.c
// 
// 57    6/22/11 9:38a Ryanchou
// [TAG]  		EIP60640
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Logitec USB keyboard has no function in DOS.
// [RootCause]  	The USB keybaord may stall get configuration descriptor
// request or set address request.
// [Solution]  	Retry five times when the device stalls these request.
// [Files]  		usb.c, usbbus.c
// 
// 56    6/21/11 11:57p Ryanchou
// [TAG]  		EIP60745
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB driver doesn't pass SCT 2.3 ComponentName2 protocol
// test
// [RootCause]  	USB driver fails to pass SCT 2.3 ComponentName2 protocol
// test - function GetControllerName conformance test, because there is no
// checking if passed handle is valid or not, or even NULL
// [Solution]  	Check the handle is valid in GetControllerName function.
// [Files]  		uhcd.c, usbbus.c
// 
// 55    5/03/11 10:45a Ryanchou
// [TAG]  		EIP59272
// [Category]  	Improvement
// [Description]  	According Uefi 2.1 Aptio porting document, changes made
// to install the component name protocol.
// [Files]  		componentname.c, componentname.h, efiusbkb.c, efiusbmass.c,
// efiusbms.c, uhcd.c, uhcd.h, usbbus.c
// 
// 54    3/30/11 8:25a Ryanchou
// [TAG]  		EIP54126
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Sometimes system hangs at checkpoint 0xB4.
// [RootCause]  	The bLength field of configuration descriptor is zero.
// [Solution]  	Check wether bLength field is zero before paring next
// descriptor.
// [Files]  		usb.c, usbbus.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c
// 
// 53    3/16/11 5:34p Anandakrishnanl
// [TAG]  		EIP56121
// [Category]  	Defect
// [Description]  	GetSupportedLanguages() returns invalid return status
// [Files]  	usbbus.c
// 
// 52    3/04/11 1:29p Olegi
// 
// 51    3/04/11 1:25p Olegi
// [TAG]  		EIP55172
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Install EFI_COMPONENT_NAME_PROTOCOL if BIOS is in UEFI
// 2.0 mode and EFI_COMPONENT_NAME2_PROTOCOL if BIOS is in UEFI 2.1 mode.
// [Files]  		uhcd.c
// usbbus.c
// efiusbkb.c
// efiusbmass.c
// efiusbms.c
// componentname.c
// componentname.h
// 
// 50    1/06/11 11:28a Olegi
// [TAG]  		EIP51191
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	USB mass storage device name is different for UEFI and
// Legacy device
// [RootCause]  	The change in InstallDevice done for 47749; it uninstalls
// UsbIo for a current device if ConnectController is unsuccessful.
// ConnectController could be unsecsessful for a number of legitemate
// reasons, one of them is the driver for this device is not present in
// the project (which is the case for a USB hub).
// [Solution]  	Removed UsbIo uninstallation in case of ConnectController
// failure.
// [Files]  		USBBUS.C
// 
// 49    11/08/10 10:03a Olegi
// [TAG]  		EIP47749
// [Category]  	Improvement
// [Description]  	Intermittently with Certain USB devices at PC B4h
// [Files]  		usbbus.c
// 
// 48    10/19/10 4:22p Krishnakumarg
// 
// [TAG]           EIP45589
// [Category]     DEFECT
// [Severity]	     MAJOR
// [Symptom]     USB3.0 controller did not show boot option when only one
// USB device connected.
// [RootCause]  USB Bus polling time was high(one second).
// [Solution]	      Reduce the usb bus polling time(100ms)
// [Files]	usbbus.c
// 
// 47    8/18/10 4:21p Olegi
// Klockwork related fixes; EIP37978
// 
// 46    6/17/10 10:35a Olegi
// EIP39326: Runtime data moved to runtime memory region.
// 
// 45    3/15/10 12:14p Olegi
// UsbBusStart:  Raise the tpl level more then EFI_TPL_CALLBACK to make it
// can be called in other callback function.EIP35956
// 
// 44    2/27/10 12:00p Olegi
// 
// 43    2/08/10 10:06a Olegi
// EIP33381: Implement multiple bulk endpoint in UsbIoProtocol.
// 
// 42    10/30/09 5:48p Olegi
// 
// 41    9/24/09 1:32p Olegi
// EIP27593: Fix in UsbIoGetStringDescriptor.
// 
// 40    8/18/09 11:53a Olegi
// 
// 39    12/16/08 10:51a Olegi
// Correction in the return values: 0 changed to NULL. EIP#17767.
// 
// 38    10/22/08 4:25p Olegi
// QueueData1 declaration and initialization is moved to UHCD.C
// 
// 37    9/05/08 4:17p Olegi
// gQueueCnnctDisc is made a part of global data structure.
// 
// 36    9/02/08 10:35a Olegi
// Bugfix in UsbIoBulkTransfer.
// 
// 35    6/27/08 5:57p Olegi
// - Coding standard related modifications
// - LoadName function modified to return USB mass storage device name
// from the INQUIRY command
// 
// 34    6/19/08 5:01p Olegi
// 
// 33    5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
// 
// 21    10/26/06 3:58p Olegi
// EFI_USB2_HC_PROTOCOL implementatin.
//
// 17    5/31/06 6:56p Mirk
// Core 4.5 compliant - DP Length manipulation changes.
//
// 15    3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 12    11/03/05 6:32p Andriyn
// LUN support
//
// 9     6/15/05 1:59p Andriyn
// Comments were changed
//****************************************************************************
//<AMI_FHDR_START>
//
//  Name:           UsbBus.c
//
//  Description:    USB Bus driver implementation
//
//<AMI_FHDR_END>
//****************************************************************************

//#include "Efi.h"
#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"

#include "usbdef.h"
#include "usbbus.h"
#include "componentname.h"

//#pragma warning(disable: 4244)

extern EFI_GUID  gEfiUsb2HcProtocolGuid;

EFI_DRIVER_BINDING_PROTOCOL gUSBBusDriverBinding = {
    UsbBusSupported,
    UsbBusStart,
    UsbBusStop,
    USB_DRIVER_VERSION,
    NULL,
    NULL
};

extern USB_GLOBAL_DATA*     gUsbData;

TREENODE_T  UsbRootRoot = {0,};
TREENODE_T* gUsbRootRoot = &UsbRootRoot;
EFI_EVENT   gEvUsbEnumTimer=0;
int         gCounterUsbEnumTimer=0;
int         gBustreeLock = 0;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbIo2Dev
//
// Description: This function returns a pointer to USB device from UsbIo.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

USBDEV_T* UsbIo2Dev(EFI_USB_IO_PROTOCOL* UsbIo)
{
    return (USBDEV_T*)((char*)UsbIo - (UINTN)&((USBDEV_T*)0)->io );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        HcByIndex
//
// Description: Predicate for searching host controller node in the tree
//              by bHcNumber
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

int HcByIndex(VOID* n, VOID* d)
{
    USBBUS_HC_T* HcNode = (USBBUS_HC_T*)n;

    return n && (HcNode->type == NodeHC)
         && (HcNode->hc_data->bHCNumber == *(UINT8*)d );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        HcByHandle
//
// Description: Predicate for searching host controller node in the tree
//              by EFI controller handle
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

int HcByHandle(VOID* n, VOID* d)
{
    USBBUS_HC_T* HcNode = (USBBUS_HC_T*)n;
    return (HcNode->type == NodeHC) && (HcNode->hc_data->Controller == *(EFI_HANDLE*)d );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        DevByIndex
//
// Description: Predicate for searching device node in the tree
//              by index of the DEV_INFO structure in the aDevInfoTable
//              array of USB data
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

int DevByIndex(VOID* n, VOID* d)
{
    USBDEV_T* Dev = (USBDEV_T*)n;
    return (Dev->type == NodeDevice) && (Dev->dev_info ==
        gUsbData->aDevInfoTable  + *(UINT8*)d );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        DevGrpByAddr
//
// Description: Predicate for searching device node in the tree
//              by USB address of the device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

int DevGrpByAddr(VOID* n, VOID* d)
{
    USBDEV_T* Dev = (USBDEV_T*)n;
    return (Dev->type == NodeDevice || Dev->type ==  NodeGroup) &&
        (Dev->dev_info->bDeviceAddress == *(UINT8*)d );
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    DevGrpByPortIf
//
// Description: Predicate for searching device node in the tree
//              by parent hub port of the device, interface and LUN
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

int DevGrpByPortIf(VOID* n, VOID* d)
{
    USBDEV_T* Dev = (USBDEV_T*)n;
    return (Dev->type == NodeDevice || Dev->type ==  NodeGroup) &&
        (Dev->dev_info->bHubPortNumber == ((DEV_INFO*)d)->bHubPortNumber ) &&
        (Dev->dev_info->bInterfaceNum == ((DEV_INFO*)d)->bInterfaceNum ) &&
        (Dev->dev_info->bLUN == ((DEV_INFO*)d)->bLUN );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    DevByInfo
//
// Description: Predicate for searching device node in the tree
//              by comparing pointers to the DEV_INFO structure
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

int DevByInfo(VOID* n, VOID* d )
{
    USBDEV_T* Dev = (USBDEV_T*)n;
    return (Dev->type == NodeDevice) && (Dev->dev_info == (DEV_INFO*)d );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    DevByAdrIf
//
// Description: Predicate for searching device node in the tree
//              by USB address and interface number of the device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

int DevByAdrIf(VOID* n, VOID* d)
{
    USBDEV_T* Dev = (USBDEV_T*)n;

    return ((Dev->type == NodeDevice) &&
        (Dev->dev_info->bDeviceAddress == ((DEV_INFO*)d)->bDeviceAddress ) &&
        (Dev->dev_info->bInterfaceNum == ((DEV_INFO*)d)->bInterfaceNum )&&
        (Dev->dev_info->bLUN == ((DEV_INFO*)d)->bLUN));
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:         UsbDevGetGroup
//
// Description:  Retrieve DEVGROUP_T that is parent of
//               the specified USB device in the USB Bus tree
//
// Input:        Device for which the parent is requested
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

DEVGROUP_T* UsbDevGetGroup(USBDEV_T* Dev)
{
    return (DEVGROUP_T*)Dev->node.parent->data;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        DpAddUsbSegment
//
// Description: Builds a new path appending a USB segment
//
// Output:      Pointer to a callee allocated memory buffer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_DEVICE_PATH_PROTOCOL*
DpAddUsbSegment(
    EFI_DEVICE_PATH_PROTOCOL*   Dp,
    UINT8                       bHubPortNumber,
    UINT8                       bInterfaceNum
)
{
    USB_DEVICE_PATH DpNewSegment = {0,};
    DpNewSegment.Header.Type = MESSAGING_DEVICE_PATH;
    DpNewSegment.Header.SubType = MSG_USB_DP;
    SET_NODE_LENGTH(&DpNewSegment.Header, sizeof(DpNewSegment));

    DpNewSegment.InterfaceNumber = bInterfaceNum;
    DpNewSegment.ParentPortNumber = bHubPortNumber;
    return  EfiAppendDevicePathNode(Dp,(EFI_DEVICE_PATH_PROTOCOL*)&DpNewSegment);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        DpAddLun
//
// Description: Builds a new path appending a LUN node
//
//
// Output:      Pointer to a callee allocated memory buffer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_DEVICE_PATH_PROTOCOL*
DpAddLun(
    EFI_DEVICE_PATH_PROTOCOL* Dp,
    UINT8   Lun
)
{
    LOGICAL_UNIT_DEVICE_PATH DpNewSegment = {0,};

    DpNewSegment.Header.Type = MESSAGING_DEVICE_PATH;
    DpNewSegment.Header.SubType = MSG_USB_LOGICAL_UNIT_CLASS_DP;
    SET_NODE_LENGTH(&DpNewSegment.Header, sizeof(DpNewSegment));
    DpNewSegment.Lun = Lun;
    return  EfiAppendDevicePathNode(Dp,(EFI_DEVICE_PATH_PROTOCOL*)&DpNewSegment);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    ReadUsbDescriptor
//
// Description: This function executes a get descriptor command to the
//              given USB device and endpoint
//
// Input:       dev         a pointer to USBDEV_T corresponding to the device
//              fpBuffer    Buffer to be used for the transfer
//              wLength     Size of the requested descriptor
//              bDescType   Requested descriptor type
//              bDescIndex  Descriptor index
//              wLangIndex  LangIndex
//
// Output:      Pointer to memory buffer containing the descriptor
//              NULL on error
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8*
ReadUsbDescriptor( USBDEV_T* Dev,
    UINT8*  Buffer,
    UINT16  Length,
    UINT8   DescType,
    UINT8   DescIndex,
    UINT16  LangIndex )
{
    HC_STRUC*   HcStruc = Dev->hc_info;
    DEV_INFO*   DevInfo = Dev->dev_info;
    UINT8       GetDescIteration;
    UINT16      Reg;
    UINT16      Status;

    for (GetDescIteration = 0; GetDescIteration < 3; GetDescIteration++) {
        Reg = (UINT16)((DescType << 8) + DescIndex);
        Status = UsbSmiControlTransfer(
                        HcStruc,
                        DevInfo,
                        (UINT16)USB_RQ_GET_DESCRIPTOR,
                        (UINT16)LangIndex,
                        Reg,
                        Buffer,
                        Length);
        if (Status) {
            return Buffer;
        }
        if (gUsbData->dLastCommandStatusExtended & USB_TRNSFR_TIMEOUT) {
            break;
        }
        pBS->Stall(10 * 1000);
    }

    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        GetUsbDescriptor
//
// Description: Allocates memory necessary to hold complete descriptor
//              and returns the descriptor there
//
// Input:       dev         a pointer to USBDEV_T corresponding to the device
//              type        Requested descriptor type
//              index       Descriptor index
//              langindex   LangIndex
//
// Output:      Pointer to memory buffer containing the descriptor
//              NULL on error
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

USB_DESCRIPTOR_T*
GetUsbDescriptor(
    USBDEV_T*   Dev,
    UINT8       Type,
    UINT8       Index,
    UINT16      LangIndex)
{
    UINT8               Buffer[0xFF] = {0};
    USB_DESCRIPTOR_T    *Desc;
    UINT8*              DescBuffer;

    DescBuffer= ReadUsbDescriptor(Dev, Buffer, sizeof(Buffer), Type, Index, LangIndex);

    if ((DescBuffer == NULL) || 
        (((USB_DESCRIPTOR_T*)Buffer)->DescriptorType != Type) ||
        (((USB_DESCRIPTOR_T*)Buffer)->Length == 0)) {
        return NULL;
    }
    gBS->AllocatePool(EfiBootServicesData, ((USB_DESCRIPTOR_T*)Buffer)->Length, &Desc);

    EfiCopyMem(Desc, Buffer, ((USB_DESCRIPTOR_T*)Buffer)->Length);

    return Desc;

/*
	EfiZeroMem(Desc, ((USB_DESCRIPTOR_T*)Buffer)->Length);
    DescBuffer = ReadUsbDescriptor(Dev, (UINT8*)Desc,
        ((USB_DESCRIPTOR_T*)Buffer)->Length, Type, Index, LangIndex);
    //ASSERT(Desc->DescriptorType == Type);     //(EIP60640-)
    if (DescBuffer == NULL){
        gBS->FreePool(Desc);
        return NULL;
    }
    //
    //Decriptor Type cannot be 0, this case means that Get Descriptor cmd timed out
    //
    if (Desc->DescriptorType == 0) {
        gBS->FreePool(Desc);
        return NULL;
    } else {
      return Desc;
    }
*/
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    FreeConfigDesc
//
// Description: Delocates memory that was used by the descriptor
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID FreeConfigDesc( VOID* Desc )
{
    if (Desc != 0) gBS->FreePool(Desc);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    NextDescriptor
//
// Description: Returns pointer to the next descriptor for the pack of
//              USB descriptors located in continues memory segment
//              - result of reading CONFIG_DESCRIPTOR
// Notes:
//              Uses TotalLength of the CONFIG_DESCRIPTOR and Length
//              field of each USB descriptor found inside the pack
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

int
NextDescriptor(
    EFI_USB_CONFIG_DESCRIPTOR* Desc,
    UINTN* Offset
)
{
    if( Desc == NULL || *Offset >= Desc->TotalLength ) return FALSE;
    if( ((EFI_USB_CONFIG_DESCRIPTOR*)((char*)Desc+*Offset))->Length == 0) return FALSE;
    *Offset += ((EFI_USB_CONFIG_DESCRIPTOR*)((char*)Desc+*Offset))->Length;
    if( *Offset >= Desc->TotalLength ) return FALSE;

    return TRUE;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UsbDevConfigDesc
//
// Description: Returns a pointer to the memory containing CONFIG_DESCRIPTOR
//              reported by the USB device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_USB_CONFIG_DESCRIPTOR*
DevGroupConfigDesc( DEVGROUP_T* Grp ){
    return Grp->f_DevDesc && (Grp->active_config != -1)? 
        Grp->configs[Grp->active_config]:NULL;
}

EFI_USB_CONFIG_DESCRIPTOR*
UsbDevConfigDesc( USBDEV_T* Dev ){
    return DevGroupConfigDesc( UsbDevGetGroup(Dev));
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbDevLoadAllDescritors
//
// Description: Reads DEVICE and CONFIG descriptors for each
//              configuration available in the device. Marks
//              the index of the buffer containing CONFIG descriptor
//              for active configurations currently selected in
//              USB device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbDevLoadAllDescritors(
    DEVGROUP_T* Dev
)
{
    UINT8 i;
	EFI_STATUS Status;

    //ASSERT( Dev->f_DevDesc == 0 );
    Dev->configs = NULL;
    //
    // Device descriptor
    //
    gBS->CopyMem((UINT8*)&Dev->dev_desc, (UINT8*)&Dev->dev_info->DevDesc, sizeof(Dev->dev_desc));
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USB Bus: dev descr: ");
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "cls:%x;subcls:%x;proto:%x;vndr:%x;id:%x\n",
                Dev->dev_desc.DeviceClass,
                Dev->dev_desc.DeviceSubClass,
                Dev->dev_desc.DeviceProtocol,
                Dev->dev_desc.IdVendor,
                Dev->dev_desc.IdProduct);
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "\t\tstr1:%x,str2:%x,str3:%x\n",
                Dev->dev_desc.StrManufacturer,
                Dev->dev_desc.StrProduct,
                Dev->dev_desc.StrSerialNumber );

    Dev->f_DevDesc = TRUE;

    //
    // Config descriptor
    //
    Dev->config_count = Dev->dev_desc.NumConfigurations;
//  dev->configs = (EFI_USB_CONFIG_DESCRIPTOR**)MallocZ(dev->config_count*sizeof(EFI_USB_CONFIG_DESCRIPTOR*));
    Status = gBS->AllocatePool (EfiBootServicesData,
        Dev->config_count*sizeof(EFI_USB_CONFIG_DESCRIPTOR*), (VOID *)&Dev->configs);
	ASSERT_EFI_ERROR(Status);
    EfiZeroMem(Dev->configs, Dev->config_count*sizeof(EFI_USB_CONFIG_DESCRIPTOR*));

    Dev->active_config = -1;
    for(i=0; i<Dev->config_count; ++i){
        //read each configuration
        //first failed read will terminate loop

        //Optimization: allloc&read MAX size first
        //      and read second time only if total length is greater
        //Read 1 : get total length
        EFI_USB_CONFIG_DESCRIPTOR tmp = {0,0,};
        UINT8* p = ReadUsbDescriptor((USBDEV_T*)Dev,(UINT8*)&tmp,
            sizeof(tmp),DESC_TYPE_CONFIG,i, 0 );
        //ASSERT(tmp.DescriptorType == DESC_TYPE_CONFIG);
        //ASSERT(tmp.TotalLength >= sizeof(tmp));
        //
        //Addressing timeouts caused by device errors - empty DESC structure will be returned
        //
        if( (p == NULL) || (tmp.DescriptorType == 0) ) {
          break;
        }

        //Read 2: Actual content
//      dev->configs[i] = MallocZ(tmp.TotalLength);
        Status = gBS->AllocatePool (EfiBootServicesData, tmp.TotalLength, &Dev->configs[i]);
		ASSERT_EFI_ERROR(Status);
        EfiZeroMem(Dev->configs[i], tmp.TotalLength);

        p = ReadUsbDescriptor((USBDEV_T*)Dev, (UINT8*)Dev->configs[i],
            tmp.TotalLength, DESC_TYPE_CONFIG, i, 0);
        //ASSERT(Dev->configs[i]->DescriptorType == DESC_TYPE_CONFIG);  //(EIP60640-)
        //
        //Addressing timeouts caused by device errors - empty DESC structure will be returned
        //
        if( (p == NULL) || (Dev->configs[i]->DescriptorType == 0) ){
            gBS->FreePool(Dev->configs[i]);
            Dev->configs[i] = 0;
            break;
        }
        //config Desc is here

        //Active Config
        if( Dev->configs[i]->ConfigurationValue == Dev->dev_info->bConfigNum ){
            Dev->active_config = i;
        }
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbDevLoadEndpoints
//
// Description: Locates information about each endpoint inside the
//              descriptors pack loaded with CONFIG descriptor
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbDevLoadEndpoints(
    USBDEV_T* Dev
)
{
    EFI_USB_INTERFACE_DESCRIPTOR  *TmpDesc;
    EFI_USB_ENDPOINT_DESCRIPTOR  *EpDesc;
    EFI_USB_CONFIG_DESCRIPTOR  *CfgDesc;
    int j;
    UINTN   Offset;
    DEVGROUP_T *Grp = UsbDevGetGroup(Dev);

    Dev->first_endpoint = Grp->endpoint_count;
    Dev->end_endpoint = Grp->endpoint_count;

    CfgDesc = UsbDevConfigDesc(Dev);
    USB_DEBUG(DEBUG_LEVEL_USBBUS,
        "\tScanning config desc: ");
    USB_DEBUG(DEBUG_LEVEL_USBBUS,
        "%x(type:%x;len:%x;val:%x;total:%x)\n",
        CfgDesc,CfgDesc->DescriptorType,CfgDesc->Length,
        CfgDesc->ConfigurationValue,CfgDesc->TotalLength );

    //
    // Search interface descriptor
    //
    for(Offset = 0; NextDescriptor(CfgDesc,&Offset);)
    {
        TmpDesc = (EFI_USB_INTERFACE_DESCRIPTOR *)((char*)CfgDesc+Offset);
        USB_DEBUG(DEBUG_LEVEL_USBBUS,
            "\t\tdesc: %x(type:%x;len:%x;if:%x;aif:%x)\n",
            TmpDesc,TmpDesc->DescriptorType,TmpDesc->Length,
            TmpDesc->InterfaceNumber, TmpDesc->AlternateSetting );
        if( TmpDesc->DescriptorType == DESC_TYPE_INTERFACE &&
            TmpDesc->InterfaceNumber== Dev->dev_info->bInterfaceNum &&
            TmpDesc->AlternateSetting == Dev->dev_info->bAltSettingNum)
        {
            //found
            USB_DEBUG(DEBUG_LEVEL_USBBUS,
                "\t...IF found.\n" );

            Dev->descIF= TmpDesc;

            ASSERT(TmpDesc->NumEndpoints < COUNTOF(Grp->endpoints));
            for(j=0;j<TmpDesc->NumEndpoints && NextDescriptor(CfgDesc,&Offset);){
                EpDesc = (EFI_USB_ENDPOINT_DESCRIPTOR*)((char*)CfgDesc+Offset);
                if( EpDesc->DescriptorType == DESC_TYPE_ENDPOINT ){
                    USB_DEBUG(DEBUG_LEVEL_USBBUS,
                        "\t\tend-point desc: %x", EpDesc);
                    USB_DEBUG(DEBUG_LEVEL_USBBUS,
                        "(index:%x;type:%x;len:%x;addr:%x;pcksz:%x;attr:%x,t:%x)\n",
                        Grp->endpoint_count,
                        EpDesc->DescriptorType,EpDesc->Length,
                        EpDesc->EndpointAddress, EpDesc->MaxPacketSize,
                        EpDesc->Attributes, EpDesc->Interval);
                    Grp->endpoints[Grp->endpoint_count].address = EpDesc->EndpointAddress;
                    Grp->endpoints[Grp->endpoint_count++].desc = EpDesc;
                    Grp->a2endpoint[COMPRESS_EP_ADR(EpDesc->EndpointAddress)] = EpDesc;
                    j++;
                }
                if( EpDesc->DescriptorType == DESC_TYPE_INTERFACE ){
                    //Oops, We stepped into another interface
                    break;
                }
            }
            Dev->end_endpoint = Grp->endpoint_count;
            USB_DEBUG(DEBUG_LEVEL_USBBUS,
                    "\t\tinterface end-points: ");
            USB_DEBUG(DEBUG_LEVEL_USBBUS,
                    "first:%x; end:%x, grp.endpoint_count:%x\n",
                        Dev->first_endpoint, Dev->end_endpoint, Grp->endpoint_count);
            return;
        }
    }
    USB_DEBUG(DEBUG_LEVEL_USBBUS,
        "\t...IF not found.\n" );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        GetMaxPacket
//
// Description: Retrieves information about a max packet size
//              for the specified endpoint of the device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
GetMaxPacket(
    UINT8       Endpoint,
    USBDEV_T*   Dev
)
{
    DEVGROUP_T *Grp = UsbDevGetGroup(Dev);
    EFI_USB_ENDPOINT_DESCRIPTOR* Desc = Grp->a2endpoint[COMPRESS_EP_ADR(Endpoint)];
    if (Desc == 0) return 0;
    return Desc->MaxPacketSize;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        GetEndpointDesc
//
// Description: Retrieves information about a max packet size
//              for the specified endpoint of the device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_USB_ENDPOINT_DESCRIPTOR*
GetEndpointDesc(
    UINT8       Endpoint,
    USBDEV_T*   Dev
)
{
    DEVGROUP_T *Grp = UsbDevGetGroup(Dev);
    EFI_USB_ENDPOINT_DESCRIPTOR* Desc;

    if (((Endpoint & 0x7F)==0) || ((Endpoint & 0x7F) > 0xF))
        return NULL;
    Desc = Grp->a2endpoint[COMPRESS_EP_ADR(Endpoint)];

    return Desc;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
//  Name:  UsbIoControlTransfer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoControlTransfer(
    IN EFI_USB_IO_PROTOCOL      *UsbIo,
    IN EFI_USB_DEVICE_REQUEST   *Request,
    IN EFI_USB_DATA_DIRECTION   Direction,
    IN UINT32                   Timeout,
    IN OUT VOID                 *Data,
    IN UINTN                    DataLength,
    OUT UINT32                  *UsbStatus
)
{
    USBDEV_T*   Dev = UsbIo2Dev(UsbIo);
    EFI_STATUS  Status;

    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );

    if( Request == NULL || UsbStatus == NULL ) return EFI_INVALID_PARAMETER;
    if (Direction > EfiUsbNoData) return EFI_INVALID_PARAMETER;

    if (!(Dev->dev_info->Flag & DEV_INFO_DEV_PRESENT)) {
        return EFI_DEVICE_ERROR;
    }

    Status = Dev->hc->ControlTransfer(
        Dev->hc, Dev->dev_info->bDeviceAddress, GetSpeed(Dev),
        (UINTN)Dev->dev_info->wEndp0MaxPacket,				//(EIP81612)
        Request, Direction, Data, &DataLength, Timeout, NULL, UsbStatus);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    if ((Request->Request == (USB_RQ_SET_INTERFACE >> 8)) &&
         (Request->RequestType == (USB_RQ_SET_INTERFACE & 0x0F) ) &&
         (Request->Index == Dev->dev_info->bInterfaceNum)) {
        Dev->dev_info->bAltSettingNum = (UINT8)Request->Value;
        UsbDevLoadEndpoints(Dev);
    }
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    UsbIoBulkTransfer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoBulkTransfer(
  IN EFI_USB_IO_PROTOCOL    *UsbIo,
  IN UINT8                  Endpoint,
  IN OUT VOID               *Data,
  IN OUT UINTN              *DataLength,
  IN UINTN                  Timeout,
  OUT UINT32                *UsbStatus
)
{
    USBDEV_T* Dev = UsbIo2Dev(UsbIo);
    UINT16 MaxPacket;
	UINT8		ToggleBit = (Endpoint & 0xF) - 1;
										//(EIP84215)>
	UINT16		*wDataSync;
    UINT8       Toggle;
    EFI_STATUS  Status;
    EFI_USB_ENDPOINT_DESCRIPTOR* EpDesc = GetEndpointDesc(Endpoint, Dev);
    DEV_INFO *DevInfoToDataSync;
										//<(EIP84215)
    if (((Endpoint & 0x7F)==0) || ((Endpoint & 0x7F) > 0xF))
        return EFI_INVALID_PARAMETER;

//	    if ( Dev->dev_info->bBulkInEndpoint &&
//	        ((Endpoint & 0x80) && ((Endpoint & 0x7F) != Dev->dev_info->bBulkInEndpoint)) ) {
//	        return EFI_INVALID_PARAMETER;
//	    }

//	    if ( Dev->dev_info->bBulkOutEndpoint &&
//	        (!(Endpoint & 0x80) && (Endpoint != Dev->dev_info->bBulkOutEndpoint)) ) {
//	        return EFI_INVALID_PARAMETER;
//	    }

    if ( Data == NULL || DataLength == NULL || UsbStatus == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if( EpDesc == NULL ) {
        return EFI_INVALID_PARAMETER;
    }
    MaxPacket = EpDesc->MaxPacketSize;
    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );

    if( UsbStatus == NULL || MaxPacket == 0) {
        return EFI_INVALID_PARAMETER;
    }

    if ( (EpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS) != EP_DESC_FLAG_TYPE_BULK ) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(Dev->dev_info->Flag & DEV_INFO_DEV_PRESENT)) {
        return EFI_DEVICE_ERROR;
    }
										//(EIP84215+)>
    if (Dev->dev_info->fpLUN0DevInfoPtr) {
        DevInfoToDataSync = Dev->dev_info->fpLUN0DevInfoPtr;
    }else {
        DevInfoToDataSync = Dev->dev_info;
    }

    if (Endpoint & 0x80) {
        wDataSync = &DevInfoToDataSync->wDataInSync;
    }else {
        wDataSync = &DevInfoToDataSync->wDataOutSync;
    }
										//<(EIP84215+)
    GETBIT( *wDataSync, Toggle, ToggleBit );

    Status = Dev->hc->BulkTransfer(
        Dev->hc, Dev->dev_info->bDeviceAddress, Endpoint, GetSpeed(Dev),
        MaxPacket, 1, &Data, DataLength, &Toggle, Timeout, NULL, UsbStatus);

    SETBIT( *wDataSync, Toggle, ToggleBit );

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoIsochronousTransfer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoAsyncInterruptTransfer(
    IN EFI_USB_IO_PROTOCOL  *UsbIo,
    IN UINT8                Endpoint,
    IN BOOLEAN              IsNewTransfer,
    IN UINTN                PollingInterval,
    IN UINTN                DataLength,
    IN EFI_ASYNC_USB_TRANSFER_CALLBACK InterruptCallback,
    IN VOID                 *Context
)
{
    USBDEV_T*   Dev = UsbIo2Dev(UsbIo);
    UINT8       Toggle;
	UINT8		ToggleBit = (Endpoint & 0xF) - 1;
										//(EIP84215)>
	UINT16		*wDataSync;
    EFI_STATUS  Status;
    EFI_USB_ENDPOINT_DESCRIPTOR* EpDesc = GetEndpointDesc(Endpoint, Dev);
    DEV_INFO *DevInfoToDataSync;
										//<(EIP84215)
	ASSERT( Dev->dev_info );
	ASSERT( Dev->hc );

	// Check whether Endpoint is valid
    if(EpDesc == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if ((EpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS) != EP_DESC_FLAG_TYPE_INT ) {
        return EFI_INVALID_PARAMETER;
    }

	if (IsNewTransfer && (PollingInterval < 1 || PollingInterval > 255)) {
		return EFI_INVALID_PARAMETER;
	}

    if (IsNewTransfer) {
        if (!(Dev->dev_info->Flag & DEV_INFO_DEV_PRESENT)) {
            return EFI_DEVICE_ERROR;
        }
    }
										//(EIP84215+)>
    if (Dev->dev_info->fpLUN0DevInfoPtr) {
        DevInfoToDataSync = Dev->dev_info->fpLUN0DevInfoPtr;
    }else {
        DevInfoToDataSync = Dev->dev_info;
    }

    if (Endpoint & 0x80) {
        wDataSync = &DevInfoToDataSync->wDataInSync;
    }else {
        wDataSync = &DevInfoToDataSync->wDataOutSync;
    }
										//<(EIP84215+)
    GETBIT( *wDataSync, Toggle, ToggleBit );

    Status = Dev->hc->AsyncInterruptTransfer(
        Dev->hc, Dev->dev_info->bDeviceAddress, Endpoint,
        GetSpeed(Dev), EpDesc->MaxPacketSize, IsNewTransfer,
        &Toggle, PollingInterval, DataLength, NULL,
        InterruptCallback, Context );

    SETBIT( *wDataSync, Toggle, ToggleBit );

	if (!EFI_ERROR(Status)) {
		Dev->async_endpoint = IsNewTransfer ? Endpoint : 0;
	}
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoSyncInterruptTransfer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoSyncInterruptTransfer(
    IN     EFI_USB_IO_PROTOCOL  *UsbIo,
    IN     UINT8                Endpoint,
    IN OUT VOID                 *Data,
    IN OUT UINTN                *DataLength,
    IN     UINTN                Timeout,
    OUT    UINT32               *UsbStatus
)
{
    USBDEV_T*   Dev = UsbIo2Dev(UsbIo);
    UINT8       Toggle;
	UINT8		ToggleBit = (Endpoint & 0xF) - 1;
										//(EIP84215)>
	UINT16		*wDataSync;
    EFI_STATUS  Status;
    EFI_USB_ENDPOINT_DESCRIPTOR* EpDesc = GetEndpointDesc(Endpoint, Dev);
    DEV_INFO *DevInfoToDataSync;
										//<(EIP84215)
	ASSERT( Dev->dev_info );
	ASSERT( Dev->hc );

	// Check whether Endpoint is valid
	if( EpDesc == NULL ) {
		return EFI_INVALID_PARAMETER;
	}

	if ( (EpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS) != EP_DESC_FLAG_TYPE_INT ) {
		 return EFI_INVALID_PARAMETER;
	}

    if ( Data == NULL || DataLength == NULL || UsbStatus == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(Dev->dev_info->Flag & DEV_INFO_DEV_PRESENT)) {
        return EFI_DEVICE_ERROR;
    }
										//(EIP84215+)>
    if (Dev->dev_info->fpLUN0DevInfoPtr) {
        DevInfoToDataSync = Dev->dev_info->fpLUN0DevInfoPtr;
    }else {
        DevInfoToDataSync = Dev->dev_info;
    }

    if (Endpoint & 0x80) {
        wDataSync = &DevInfoToDataSync->wDataInSync;
    }else {
        wDataSync = &DevInfoToDataSync->wDataOutSync;
    }
										//<(EIP84215+)
    GETBIT( *wDataSync, Toggle, ToggleBit );
    Status = Dev->hc->SyncInterruptTransfer(
        Dev->hc, Dev->dev_info->bDeviceAddress, Endpoint,
        GetSpeed(Dev), EpDesc->MaxPacketSize,
        Data, DataLength, &Toggle, Timeout, NULL, UsbStatus);
    SETBIT( *wDataSync, Toggle, ToggleBit );

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
//  Name:   UsbIoIsochronousTransfer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoIsochronousTransfer(
    IN EFI_USB_IO_PROTOCOL  *UsbIo,
    IN     UINT8            Endpoint,
    IN OUT VOID             *Data,
    IN     UINTN            DataLength,
    OUT    UINT32           *Status
)
{
    USBDEV_T*   Dev = UsbIo2Dev(UsbIo);
    UINT16      MaxPacket;// = GetMaxPacket(Endpoint,dev);
    EFI_USB_ENDPOINT_DESCRIPTOR* EpDesc = GetEndpointDesc(Endpoint, Dev);

    if (EpDesc == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    MaxPacket = EpDesc->MaxPacketSize;
    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );

    if (Status == NULL || MaxPacket == 0) {
        return EFI_INVALID_PARAMETER;
    }

    if ((EpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS) != EP_DESC_FLAG_TYPE_ISOC) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(Dev->dev_info->Flag & DEV_INFO_DEV_PRESENT)) {
        return EFI_DEVICE_ERROR;
    }

    return Dev->hc->IsochronousTransfer(
        Dev->hc, Dev->dev_info->bDeviceAddress, Endpoint, GetSpeed(Dev),
        MaxPacket, 1, &Data, DataLength, NULL, Status);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoAsyncIsochronousTransfer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoAsyncIsochronousTransfer(
    IN EFI_USB_IO_PROTOCOL  *UsbIo,
    IN UINT8                Endpoint,
    IN OUT VOID             *Data,
    IN     UINTN            DataLength,
    IN EFI_ASYNC_USB_TRANSFER_CALLBACK  IsochronousCallback,
    IN VOID                 *Context
)
{
    USBDEV_T* Dev = UsbIo2Dev(UsbIo);
    UINT16 MaxPacket;// = GetMaxPacket(Endpoint, Dev);
    EFI_USB_ENDPOINT_DESCRIPTOR* EpDesc = GetEndpointDesc(Endpoint, Dev);
    
    if (EpDesc == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    MaxPacket = EpDesc->MaxPacketSize;
    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );
    if ((EpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS) != EP_DESC_FLAG_TYPE_ISOC) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(Dev->dev_info->Flag & DEV_INFO_DEV_PRESENT)) {
        return EFI_DEVICE_ERROR;
    }

    return Dev->hc->AsyncIsochronousTransfer(
        Dev->hc, Dev->dev_info->bDeviceAddress, Endpoint, GetSpeed(Dev),
        MaxPacket, 1, &Data, DataLength, NULL, IsochronousCallback, Context );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoPortReset
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoPortReset(
    IN EFI_USB_IO_PROTOCOL  *UsbIo
)
{
    USBDEV_T* Dev = UsbIo2Dev(UsbIo);
	DEVGROUP_T* Grp = UsbDevGetGroup(Dev);
	UINT8	Status;
	UINT8	i;

    if (Dev->dev_info->bDeviceType == BIOS_DEV_TYPE_HUB)
        return EFI_INVALID_PARAMETER;

	Status = UsbResetAndReconfigDev(Dev->hc_info, Dev->dev_info);
	if (Status != USB_SUCCESS) {
		return EFI_DEVICE_ERROR;
	}

	if( UsbSmiGetDescriptor(Dev->hc_info, Dev->dev_info, (UINT8*)&Grp->dev_desc,
        sizeof(Grp->dev_desc), DESC_TYPE_DEVICE, 0) == 0 ){
        return EFI_DEVICE_ERROR;
    }

	for(i = 0; i < Grp->dev_desc.NumConfigurations; i++) {
		if (ReadUsbDescriptor(Dev, (UINT8*)Grp->configs[i], 
			Grp->configs[i]->TotalLength, DESC_TYPE_CONFIG, i, 0) == 0) {
			return EFI_DEVICE_ERROR;
		}
	}

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbIoGetDeviceDescriptor
//
// Description: Retrieves the USB Device Descriptor.
//
// Input:
//      UsbIo       A pointer to the EFI_USB_IO_PROTOCOL instance. Type
//                  EFI_USB_IO_PROTOCOL is defined in Section 14.2.5.
//      Desc        A pointer to the caller allocated USB Device Descriptor.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoGetDeviceDescriptor(
    IN EFI_USB_IO_PROTOCOL          *UsbIo,
    OUT EFI_USB_DEVICE_DESCRIPTOR   *Desc
)
{
    USBDEV_T* Dev = UsbIo2Dev(UsbIo);
    DEVGROUP_T* Grp = UsbDevGetGroup(Dev);
    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );
    if( Desc == NULL ) return EFI_INVALID_PARAMETER;

    if( Grp->f_DevDesc ){
        *Desc = Grp->dev_desc;
        return EFI_SUCCESS;
    } else
        return EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoGetConfigDescriptor
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoGetConfigDescriptor(
    IN EFI_USB_IO_PROTOCOL          *UsbIo,
    OUT EFI_USB_CONFIG_DESCRIPTOR   *Desc
)
{
    USBDEV_T*   Dev = UsbIo2Dev(UsbIo);
    DEVGROUP_T* Grp = UsbDevGetGroup(Dev);
    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );
    if( Desc == NULL ) return EFI_INVALID_PARAMETER;

    if( Grp->configs && Grp->active_config != -1 &&
        Grp->configs[Grp->active_config] ){
        *Desc = *Grp->configs[Grp->active_config];
        return EFI_SUCCESS;
    } else
        return EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoGetInterfaceDescriptor
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoGetInterfaceDescriptor(
    IN EFI_USB_IO_PROTOCOL              *UsbIo,
    OUT EFI_USB_INTERFACE_DESCRIPTOR    *Desc
)
{
    USBDEV_T* Dev = UsbIo2Dev(UsbIo);

    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );
    if (Desc == NULL) return EFI_INVALID_PARAMETER;

    if (Dev->descIF == NULL) return EFI_NOT_FOUND;

    *Desc = *Dev->descIF;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoGetEndpointDescriptor
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoGetEndpointDescriptor(
    IN EFI_USB_IO_PROTOCOL  *UsbIo,
    IN  UINT8               EndpointIndex,
    OUT EFI_USB_ENDPOINT_DESCRIPTOR *Desc
)
{
    USBDEV_T* Dev = UsbIo2Dev(UsbIo);
    DEVGROUP_T *Grp;
    EFI_USB_ENDPOINT_DESCRIPTOR* DescCopy;

    if( Desc == NULL || EndpointIndex >= 0x10) return EFI_INVALID_PARAMETER;

    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );

    USB_DEBUG( 3, "Get Endpoint desc: devaddr: 0x%x; Endpoint: 0x%x\n",
            Dev->dev_info->bDeviceAddress, EndpointIndex );
    USB_DEBUG( 3, "\tfirst Endpoint: 0x%x; last Endpoint: 0x%x\n",
            Dev->first_endpoint, Dev->end_endpoint-1 );

    if( Dev->first_endpoint + EndpointIndex >= Dev->end_endpoint )
        return EFI_NOT_FOUND;

    ASSERT( Dev->first_endpoint + EndpointIndex < 0x20 );

    Grp = UsbDevGetGroup(Dev);
    DescCopy = Grp->endpoints[Dev->first_endpoint + EndpointIndex].desc;

    ASSERT( DescCopy );

    if (DescCopy==NULL) return EFI_NOT_FOUND;

    USB_DEBUG( 3, "\tendp addr: 0x%x; attr: 0x%x; MaxPacket: 0x%x\n",
            DescCopy->EndpointAddress,
            DescCopy->Attributes, DescCopy->MaxPacketSize );

    *Desc = *DescCopy;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoGetStringDescriptor
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UsbIoGetStringDescriptor(
    IN EFI_USB_IO_PROTOCOL  *UsbIo,
    IN  UINT16              LangId,
    IN  UINT8               StringId,
    OUT CHAR16              **String
)
{
    USBDEV_T*                       Dev = UsbIo2Dev(UsbIo);
    EFI_USB_STRING_DESCRIPTOR*      StrDesc = NULL;
    UINT16                          Index;
    UINT16                          *LangIdTable;
    DEVGROUP_T*                     Grp;
    EFI_STATUS                      Status = EFI_NOT_FOUND;

    ASSERT(Dev->dev_info);
    ASSERT(Dev->hc);

    Grp = UsbDevGetGroup(Dev);

    if (StringId == 0 || Grp->lang_table == NULL) {
        //reserved ids: stringid==0 => langid table descripto;
        return Status;
    }
    // search langid_table
    LangIdTable = Grp->lang_table->langID;
    for (Index = 0; Index < Grp->lang_table->len ; Index++) {
        if (LangId == LangIdTable[Index]) {
            break;
        }
    }
    
    if (Index == Grp->lang_table->len) {
        return Status;
    }
    
    if (LangId == USB_US_LAND_ID) {
        if (StringId == Grp->dev_desc.StrSerialNumber) {
            StrDesc = Grp->SerialNumberStrDesc;
        } else if (StringId == Grp->dev_desc.StrProduct) {
            StrDesc = Grp->ProductStrDesc;
        } else if (StringId == Grp->dev_desc.StrManufacturer) {
            StrDesc = Grp->ManufacturerStrDesc;
        }
    }
    //
    // Get string descriptor: variable size
    //
    if (StrDesc == NULL) {
        StrDesc = (EFI_USB_STRING_DESCRIPTOR*)GetUsbDescriptor(Dev, DESC_TYPE_STRING,
			        StringId, LangId);
    }
    
    if (StrDesc == NULL) {
        return Status;
    }

    if (StrDesc->Length > 2 && StrDesc->DescriptorType == DESC_TYPE_STRING) {
        //
        // Allocate memory for string & copy
        //
        if (String != NULL) {
            gBS->AllocatePool(EfiBootServicesData, StrDesc->Length, String);
            EfiZeroMem(*String, StrDesc->Length);
            EfiCopyMem(*String, StrDesc->String, StrDesc->Length -2);
        }
        Status = EFI_SUCCESS;
    }
    if ((StrDesc != Grp->SerialNumberStrDesc) && (StrDesc != Grp->ProductStrDesc) &&
        (StrDesc != Grp->ManufacturerStrDesc)) {
        gBS->FreePool(StrDesc);
    }
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  UsbIoGetSupportedLanguages
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbIoGetSupportedLanguages(
    IN EFI_USB_IO_PROTOCOL  *UsbIo,
    OUT UINT16              **LangIdTable,
    OUT UINT16              *TableSize )
{
    USBDEV_T*   Dev = UsbIo2Dev(UsbIo);
    DEVGROUP_T* Grp;

    ASSERT( Dev->dev_info );
    ASSERT( Dev->hc );
    Grp = UsbDevGetGroup(Dev);
    if (LangIdTable == NULL || TableSize == NULL) {
        return EFI_SUCCESS;
    }
    if (Grp->lang_table == NULL) {
        *LangIdTable  = 0;
        *TableSize = 0;
    } else {
        *LangIdTable = Grp->lang_table->langID;
        *TableSize = Grp->lang_table->len*2;
    }
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        LoadName
//
// Description: loads STRING descriptor that corresponds to
//              the name of the USB device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16*
LoadName(
    USBDEV_T* Dev
)
{
    EFI_USB_INTERFACE_DESCRIPTOR DescIf = {0,};
    EFI_USB_DEVICE_DESCRIPTOR DescDev = {0,};
    DEVGROUP_T* Grp = UsbDevGetGroup(Dev);
    CHAR16* StrIf = 0;
    CHAR16* StrProduct = 0;
//  CHAR16* StrManufact=0;
    CHAR16 Lang;
    CHAR16  *MassStorageName;
    UINT8   *p;
    UINT8   i;

    for (i = 0; i < 64; i++) {
        if (Dev->dev_info->DevNameString[i] != 0) {
            break;
        }
    }

    if (i != 64) {
        gBS->AllocatePool (EfiBootServicesData, 128, &MassStorageName);
        EfiZeroMem(MassStorageName, 128);
        for (p = (UINT8*)&Dev->dev_info->DevNameString, i=0; i<64; i++) {
            if (p[i] == 0) break;
            MassStorageName[i] = (CHAR16)p[i];
        }
        return MassStorageName;
    }

    if( Grp->lang_table == 0 || Grp->lang_table->len == 0 ) return 0;

    Lang = Grp->lang_table->langID[0];

    UsbIoGetInterfaceDescriptor(&Dev->io,&DescIf);
    if( DescIf.Interface && !EFI_ERROR(
        UsbIoGetStringDescriptor(&Dev->io, Lang,
        DescIf.Interface, &StrIf )))
        return StrIf;

    UsbIoGetDeviceDescriptor(&Dev->io, &DescDev);
    if( DescDev.StrProduct && !EFI_ERROR(
        UsbIoGetStringDescriptor(&Dev->io, Lang,
        DescDev.StrProduct, &StrProduct )))
        return StrProduct;

    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InstallDevice
//
// Description: Adds a device to the tree; creates an EFI handle for the
//              usb device; installs USB_IO and DEVICEPATH protocols
//              on a new device handle; connects a new device to
//              EFI device drivers
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

TREENODE_T*
UsbDevHubNode(
    TREENODE_T  *HcNode,
    DEV_INFO    *DevInfo
)
{
//    int i;
    TREENODE_T *HubNode=0;
    TREENODE_T *HubGrpNode;

    HubGrpNode = TreeSearchDeep(HcNode->child, DevGrpByAddr, &DevInfo->bHubDeviceNumber );
    if (HubGrpNode != NULL){
        HubNode = HubGrpNode->child;
        ASSERT(HubNode);
        USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: parent Hub found: %x\n", HubNode );
        return HubNode;
    }
/*
    for( i=0;i<COUNTOF(gUsbData->aDevInfoTable) && (HubNode==0);i++){
        if((gUsbData->aDevInfoTable[i].Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT))
            != (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT))
            continue;
        if( gUsbData->aDevInfoTable[i].bHCNumber == DevInfo->bHCNumber &&
            gUsbData->aDevInfoTable[i].bDeviceAddress == DevInfo->bHubDeviceNumber )
        {
            USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: UsbDevHubNode:  valid hub info [%d]: %x\n",i, gUsbData->aDevInfoTable +i );
            InstallDevice( gUsbData->aDevInfoTable +i );
            HubNode = TreeSearchDeep(HcNode->child, DevByInfo, gUsbData->aDevInfoTable +i );
            ASSERT(HubNode);
        }
    }
*/
    return HubNode;
}

VOID InstallDevice(DEV_INFO* DevInfo)
{
    TREENODE_T* HcNode;
    TREENODE_T* HubNode;
    TREENODE_T* ParentNode;
    USBDEV_T* Dev;
    DEVGROUP_T* Grp;
    EFI_STATUS Status;
	EFI_TPL OldTpl;
    UINT16  Index;
    UINT16  *LangId;
    UINT16  OrgTimeOutValue;

    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: InstallDevice ");
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "(hc:%x,hub:%x,port:%x,addr:%x,if:%x,aif:%x,lun:%x)\n",
        DevInfo->bHCNumber, DevInfo->bHubDeviceNumber, DevInfo->bHubPortNumber, DevInfo->bDeviceAddress,
        DevInfo->bInterfaceNum, DevInfo->bAltSettingNum, DevInfo->bLUN );

    // Find HC node in tree
    HcNode = TreeSearchSibling(gUsbRootRoot->child, HcByIndex, &DevInfo->bHCNumber );

    // Do not assert here: it's fine to see a DEV_INFO from not-yet-installed HC
    if( HcNode == NULL ) return;
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: HC node found: %x\n", HcNode );

    // Find a hub node in tree
    if( DevInfo->bHubDeviceNumber & BIT7){ // hub is a root HC
        USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: Connecting to root Hub\n", DevInfo->bHCNumber );
        ASSERT( (DevInfo->bHubDeviceNumber & ~BIT7 )== DevInfo->bHCNumber );
        HubNode = HcNode;
    } else { // hub is usb hub device
        HubNode = UsbDevHubNode(HcNode, DevInfo);
        // Do not assert here: it may be to see a DEV_INFO from not-yet-installed hub.
        //ASSERT(HubNode != NULL);
        if (HubNode == NULL) return;
    }

    ParentNode = NULL;
    ParentNode = TreeSearchSibling(HubNode->child, 
        DevGrpByAddr, &DevInfo->bDeviceAddress );

    if( ParentNode == NULL ){
        // Create group
        USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: group created\n" );
        Status = gBS->AllocatePool (EfiBootServicesData, sizeof(DEVGROUP_T), &Grp);
		ASSERT_EFI_ERROR(Status);
        EfiZeroMem(Grp, sizeof(DEVGROUP_T));

        Grp->dev_info = DevInfo;
        Grp->hc = ((USBBUS_HC_T*)HcNode->data)->hc;
        Grp->hc_info  = ((USBBUS_HC_T*)HcNode->data)->hc_data;
        Grp->f_DevDesc = FALSE;
        Grp->configs = NULL;
        Grp->config_count = 0;
        Grp->ManufacturerStrDesc = NULL;
        Grp->ProductStrDesc = NULL;
        Grp->SerialNumberStrDesc = NULL;
        Grp->type = NodeGroup;
        Grp->active_config = 0;
        UsbDevLoadAllDescritors(Grp);
        //
        // Check at least for Device Descriptor present before proceeding
        //
        if(Grp->f_DevDesc == FALSE) {
          //
          //When  no Device Descriptor present quit installing the device
          //
          USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: dev install aborted - no device descriptor\n");
          return;
        }
        USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: descriptors loaded\n" );
 
                                        //(EIP66231+)>
        if ((Grp->dev_desc.StrManufacturer != 0) || (Grp->dev_desc.StrProduct != 0) || 
            (Grp->dev_desc.StrSerialNumber != 0)) {
            // Load langid table
            Grp->lang_table = (lang_table_t*)GetUsbDescriptor((USBDEV_T*)Grp, DESC_TYPE_STRING, 0, 0);
            if (Grp->lang_table && Grp->lang_table->len != 0) {
                Grp->lang_table->len = (Grp->lang_table->len -2) / sizeof(UINT16);
                USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: LangID table loaded\n" );
                
                LangId = Grp->lang_table->langID;
                
                for (Index = 0; Index < Grp->lang_table->len; Index++) {
                    if (LangId[Index] == USB_US_LAND_ID) {
                        break;
                    }
                }
             
                if (Index != Grp->lang_table->len) {
                    // Some devices may not respond getting string descriptors 
                    // whcih describing manufacturer, product set the timeout value to 100 ms.
                    OrgTimeOutValue = gUsbData->wTimeOutValue;
                    gUsbData->wTimeOutValue = USB_GET_STRING_DESC_TIMEOUT_MS;
                    if (Grp->dev_desc.StrManufacturer != 0) {
                        Grp->ManufacturerStrDesc = 
                            (EFI_USB_STRING_DESCRIPTOR*)GetUsbDescriptor(
                            (USBDEV_T*)Grp, DESC_TYPE_STRING, 
                            Grp->dev_desc.StrManufacturer, USB_US_LAND_ID);
                    }
                    if (Grp->dev_desc.StrProduct != 0) {
                        Grp->ProductStrDesc = 
                            (EFI_USB_STRING_DESCRIPTOR*)GetUsbDescriptor(
                            (USBDEV_T*)Grp, DESC_TYPE_STRING, 
                            Grp->dev_desc.StrProduct, USB_US_LAND_ID);
                    }
                    if (Grp->dev_desc.StrSerialNumber != 0) {
                        // Set timeout value to 3000 ms for the serial number string descriptor.
                        gUsbData->wTimeOutValue = USB_GET_SERIAL_NUMBER_DESC_TIMEOUT_MS;
                        Grp->SerialNumberStrDesc = 
                            (EFI_USB_STRING_DESCRIPTOR*)GetUsbDescriptor(
                            (USBDEV_T*)Grp, DESC_TYPE_STRING, 
                            Grp->dev_desc.StrSerialNumber, USB_US_LAND_ID);
                    }
                    gUsbData->wTimeOutValue = OrgTimeOutValue;
                }
            }
        }
                                        //<(EIP66231+)
        TreeAddChild(HubNode,(ParentNode = TreeCreate(&Grp->node, Grp)));
    } else {
        // Old group was found in tree
        TREENODE_T *tmp = TreeSearchSibling(ParentNode->child, DevByAdrIf, DevInfo );
        if(tmp){
            USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: IF is already in tree: %x\n", tmp );
            return;
        }

        USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: multi-function; group node found: %x\n", ParentNode );
        Grp = (DEVGROUP_T*)ParentNode->data;
    }

    // Create new device node as a child of HubNode
    gBS->AllocatePool (EfiBootServicesData, sizeof(USBDEV_T), &Dev);
    ASSERT(Dev);
    if (Dev == NULL) return;
    EfiZeroMem(Dev, sizeof(USBDEV_T));

    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: device node created: %x\n",
        &Dev->node );
    Dev->type = NodeDevice;
    TreeAddChild(ParentNode, TreeCreate(&Dev->node, Dev));
    Dev->dev_info = DevInfo;
    Dev->hc = ((USBBUS_HC_T*)HcNode->data)->hc;
    Dev->hc_info  = ((USBBUS_HC_T*)HcNode->data)->hc_data;
    Dev->f_connected = FALSE;

    UsbDevLoadEndpoints(Dev);

    // Speed 00/10/01 - High/Full/Low
                                        //(EIP81612)>
    switch (Dev->dev_info->bEndpointSpeed) {
        case USB_DEV_SPEED_SUPER_PLUS:
            Dev->speed = EFI_USB_SPEED_SUPER_PLUS; 
            break;
        case USB_DEV_SPEED_SUPER:
            Dev->speed = EFI_USB_SPEED_SUPER; 
            break;
        case USB_DEV_SPEED_FULL:
            Dev->speed = EFI_USB_SPEED_FULL;
            break;
        case USB_DEV_SPEED_LOW:
            Dev->speed = EFI_USB_SPEED_LOW;
            break;
        case USB_DEV_SPEED_HIGH:
            Dev->speed = EFI_USB_SPEED_HIGH;
    }
                                        //<(EIP81612)
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: endpoints loaded\n" );

    // Create Device Path
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: preparing DP...\n" );

    ASSERT(((USBDEV_T*)HubNode->data)->dp);
    Dev->dp = DpAddUsbSegment(((USBDEV_T*)HubNode->data)->dp,
        DevInfo->bHubPortNumber - 1, DevInfo->bInterfaceNum);
    if (DevInfo->bLUN) {
        Dev->dp = DpAddLun(Dev->dp, DevInfo->bLUN);
    }
    ASSERT(Dev->dp);

    // Install USB_IO protocol
    Dev->io.UsbControlTransfer          = UsbIoControlTransfer;
    Dev->io.UsbBulkTransfer             = UsbIoBulkTransfer;
    Dev->io.UsbAsyncInterruptTransfer   = UsbIoAsyncInterruptTransfer;
    Dev->io.UsbSyncInterruptTransfer    = UsbIoSyncInterruptTransfer;
    Dev->io.UsbIsochronousTransfer      = UsbIoIsochronousTransfer;
    Dev->io.UsbAsyncIsochronousTransfer = UsbIoAsyncIsochronousTransfer;

    Dev->io.UsbGetDeviceDescriptor      = UsbIoGetDeviceDescriptor;
    Dev->io.UsbGetConfigDescriptor      = UsbIoGetConfigDescriptor;
    Dev->io.UsbGetInterfaceDescriptor   = UsbIoGetInterfaceDescriptor;
    Dev->io.UsbGetEndpointDescriptor    = UsbIoGetEndpointDescriptor;
    Dev->io.UsbGetStringDescriptor      = UsbIoGetStringDescriptor;
    Dev->io.UsbGetSupportedLanguages    = UsbIoGetSupportedLanguages;

    Dev->io.UsbPortReset                = UsbIoPortReset;

//    DEBUG_DELAY();
    //Install DP_ protocol
	Status = gBS->InstallMultipleProtocolInterfaces (
        &Dev->handle,
        &gEfiUsbIoProtocolGuid, &Dev->io,
        &gEfiDevicePathProtocolGuid, Dev->dp,
        NULL);
	ASSERT_EFI_ERROR(Status);
	
    *(UINTN*)Dev->dev_info->Handle = (UINTN)Dev->handle;
	Dev->dev_info->Flag |= DEV_INFO_DEV_BUS;
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: USB_IO %x installed on Dev %x\n", &Dev->io, Dev );

    {
        VOID* tmp;
        VERIFY_EFI_ERROR(
            gBS->OpenProtocol (
            Dev->hc_info->Controller,
            &gEfiUsb2HcProtocolGuid,
            &tmp,
            gUSBBusDriverBinding.DriverBindingHandle,
            Dev->handle,
            EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER ));
    }

    PROGRESS_CODE(DXE_USB_HOTPLUG);

    OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);
    pBS->RestoreTPL(TPL_CALLBACK);

    // Connect controller to start device drvirs
    Status = gBS->ConnectController(Dev->handle,NULL,NULL,TRUE);

    pBS->RaiseTPL(TPL_HIGH_LEVEL);
    pBS->RestoreTPL(OldTpl);
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: instdev: connect controller: %r\n", Status );

    if( !EFI_ERROR(Status)){
        Dev->f_connected = TRUE;
    }
    return;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UninstallDevice
//
// Description: Disconnects device; uninstalls USB_IO and DEVICEPATH protocols
//              delocates all memory used USB Bus driver to support the device
//              removes device node from the tree; if device has children, all
//              UninstallDevice procedure is repeated for each child.
//
//              In case if disconnect or protocol uninstall fails, it reports
//              error stauts returned from Boot service procedure.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UninstallDevice(USBDEV_T* Dev)
{
    EFI_STATUS Status;
	EFI_TPL OldTpl;

    //
    // Uninstall connected devices if it's a hub
    //
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: UninstallDevice: node %x; ", &Dev->node);
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "info:%x [adr:%d;if:%d] uninstalling children...\n",
        Dev->dev_info,Dev->dev_info->bDeviceAddress, Dev->dev_info->bInterfaceNum);
    if( TreeSearchSibling( Dev->node.child, eUninstallDevice, &Status ))
        return Status;

    OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);
    pBS->RestoreTPL(TPL_CALLBACK);

	Status = gBS->DisconnectController(Dev->handle, NULL, NULL);

    pBS->RaiseTPL(TPL_HIGH_LEVEL);
    pBS->RestoreTPL(OldTpl);

    if (EFI_ERROR(Status)) {
        QueuePut(&gUsbData->QueueCnnctDisc, Dev->dev_info);
        Dev->dev_info->Flag |= DEV_INFO_IN_QUEUE;
        return Status;
    }

	if (Dev->async_endpoint != 0) {
		Status = Dev->io.UsbAsyncInterruptTransfer(&Dev->io, Dev->async_endpoint, FALSE, 
			0, 0, NULL, NULL);
		Dev->async_endpoint = 0;
	}

    Status = gBS->CloseProtocol (
        Dev->hc_info->Controller,
        &gEfiUsb2HcProtocolGuid,
        gUSBBusDriverBinding.DriverBindingHandle,
        Dev->handle
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    //
    // Try to uninstall protocols
    //
    // they can be denied to uninstall, which result in
    // keeping this device and all bus alive
    //
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: uninstdev: [%d:%d] uninstalling protocols...",
        Dev->dev_info->bDeviceAddress, Dev->dev_info->bInterfaceNum);
    Status = gBS->UninstallMultipleProtocolInterfaces (
        Dev->handle,
        &gEfiUsbIoProtocolGuid, &Dev->io,
        &gEfiDevicePathProtocolGuid, Dev->dp,
        NULL);
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "%r\n", Status );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

	Dev->dev_info->Flag &= ~DEV_INFO_DEV_BUS;
	if (!(Dev->dev_info->Flag & (DEV_INFO_MASS_DEV_REGD | DEV_INFO_DEV_PRESENT))) {
		Dev->dev_info->Flag &= ~DEV_INFO_VALID_STRUC;
	}

    //
    // Unistall succeeded, free usbdev
    //
    TreeRemove(&Dev->node);
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: uninstdev: [%d:%d] done.\n",
        Dev->dev_info->bDeviceAddress, Dev->dev_info->bInterfaceNum);

    if(Dev->name)
        gBS->FreePool(Dev->name);
    gBS->FreePool(Dev);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        eUninstallDevice
//
// Description: Enumeration call-back function that is usded
//              uninstall all enumerated device nodes
//              Stops enumeration as soon as error was recieved
// Input:
//              Node - tree node of the USB device or group
//              Contex - pointer to the EFI_STATUS variable that
//                      recieves status information if error
//                      was recieved
// Output:      TRUE  on error found; this will stop enumeration
//              FALSE on succesfull uninstall operation
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
int
eUninstallDevice(
    VOID* Node,
    VOID* Context
)
{
    EFI_STATUS *Status = (EFI_STATUS*)Context;
    DEVGROUP_T* Grp = (DEVGROUP_T*)Node;
    ASSERT(Status);

    if (Grp->type == NodeGroup) {
        //
        // Uninstall all CONNECTED devices within group
        //
        TreeSearchSibling( Grp->node.child, eUninstallDevice, Status );
        if (EFI_ERROR(*Status)) {
            USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: devgroup uninstall failed: devaddr:0x%x\n",
                Grp->dev_info->bDeviceAddress );
            return TRUE; //stop enumeration
        }
        // Free devgroup
        TreeRemove(&Grp->node);
        if (Grp->configs) {
            int i;
            for (i = 0; i < Grp->config_count; ++i) {
                if (Grp->configs[i]) {
                    gBS->FreePool(Grp->configs[i]);
                }
            }
            gBS->FreePool(Grp->configs);
        }
        if (Grp->ManufacturerStrDesc) {
            gBS->FreePool(Grp->ManufacturerStrDesc);
        }
        if (Grp->ProductStrDesc) {
            gBS->FreePool(Grp->ProductStrDesc);
        }
        if (Grp->SerialNumberStrDesc) {
            gBS->FreePool(Grp->SerialNumberStrDesc);
        }
        gBS->FreePool(Grp);
    } else if (Grp->type == NodeDevice ) {
        //
        //Uninstall Device
        //
        *Status = UninstallDevice((USBDEV_T*)Node);
        if (EFI_ERROR(*Status)) {
            USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: usbdev uninstall failed: if:%d\n",
                ((USBDEV_T*)Node)->dev_info->bInterfaceNum );
            return TRUE; //stop enumeration
        }
    }
    return FALSE;// continue enumeration
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        RemoveHubEcho
//
// Description: Finds the USB hub node that sits on the same
//              path (seq. of (hub ports,if) ) but have different
//              USB address or DEV_INFO node. This could be the result
//              of lost disconnect event or previous error to uninstall
//              USB_IO
// Input:
//              pDevInfo - DEV_INFO structure that is checked for
//                      echoes in the bus
// Output:      EFI_SUCCESS - echo wasn't found or was succesfully removed
//              otherwise return status resulted from attemp to remove the node
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveHubEcho(
    TREENODE_T  *HcNode,
    UINT8       Addr
)
{
    while(!( Addr  & BIT7 )){
        //
        // Find hub DEV_INFO
        //
        int i;
        TREENODE_T *HubNode;
        TREENODE_T* DevNode;
        DEV_INFO* DevInfo=NULL;

        for ( i= 1; i < MAX_DEVICES; i++)   {
            if( ((gUsbData->aDevInfoTable[i].Flag &
            (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT | DEV_INFO_DEV_DUMMY))
            != (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT)) &&
             gUsbData->aDevInfoTable[i].bDeviceAddress == Addr )
        {
                DevInfo = gUsbData->aDevInfoTable+i;
                break;
            }
        }
        if ( DevInfo == NULL )
            return EFI_NOT_FOUND;

        //
        // Search for parent hub
        //
        if( DevInfo->bHubDeviceNumber  & BIT7 ){
            //Root hub
            HubNode = HcNode;
        } else {
            //USB hub device
            TREENODE_T* HubGrpNode = TreeSearchDeep(HcNode->child,
                DevGrpByAddr, &DevInfo->bHubDeviceNumber );
            if( HubGrpNode != NULL ){
                USBDEV_T* Dev;

                HubNode = HubGrpNode->child;
                ASSERT(HubNode);
                DevNode = TreeSearchSibling(HubNode->child,
                            DevGrpByPortIf, DevInfo);
                if(DevNode==NULL) return EFI_SUCCESS;
                Dev = (USBDEV_T*)DevNode->data;
                if( Dev && (DevInfo->bDeviceAddress !=
                    Dev->dev_info->bDeviceAddress ||
                    DevInfo != Dev->dev_info ))
                {
                    //
                    // The disconnect event must have been droped
                    // disconnect old info now
                    //

                    USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: echo found [%x]:\n" );
                    USB_DEBUG(DEBUG_LEVEL_USBBUS,
                        "\t(hc:0x%x,hub:0x%x,port:%d,addr:0x%x,if:%d)\n",
                        Dev->dev_info->bHCNumber,
                        Dev->dev_info->bHubDeviceNumber,
                        Dev->dev_info->bHubPortNumber,
                        Dev->dev_info->bDeviceAddress,
                        Dev->dev_info->bInterfaceNum);
                    return RemoveDevInfo(Dev->dev_info);
                }
                return EFI_SUCCESS;
            } else {
                //
                // Either hub wasn't added to bus yet; or there is echo for the
                // brunch. The the later case succesfull removal of the burnch
                // removes an echo for this device info
                //
                Addr = DevInfo->bHubDeviceNumber;

            }
        }
    }
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        RemoveDevInfoEcho
//
// Description: Finds the USB device node that sits on the same
//              path (seq. of (hub ports,if) ) but have different
//              USB address or DEV_INFO node. This could be the result
//              of lost disconnect event or previous error to uninstall
//              USB_IO
// Input:
//              DevInfo - DEV_INFO structure that is checked for
//                      echoes in the bus
// Output:      EFI_SUCCESS - echo wasn't found or was succesfully removed
//              otherwise return status resulted from attemp to remove the node
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveDevInfoEcho(
    DEV_INFO    *DevInfo
)
{
    USBDEV_T    *Dev;
    TREENODE_T  *DevNode;
    TREENODE_T  *HcNode, *HubNode;

    HcNode = TreeSearchSibling(gUsbRootRoot->child,HcByIndex,
        &DevInfo->bHCNumber);
    if(HcNode==NULL) return EFI_SUCCESS;

    if( DevInfo->bHubDeviceNumber  & BIT7 ){
        //Root hub
        HubNode = HcNode;
    } else {
        //USB hub device
        TREENODE_T* HubGrpNode = TreeSearchDeep(HcNode->child,
            DevGrpByAddr, &DevInfo->bHubDeviceNumber );
        if( HubGrpNode != NULL ){
            HubNode = HubGrpNode->child;
            ASSERT(HubNode);
        } else {
            //
            // Either hub wasn't added to bus yet; or there is echo for the
            // brunch. The the later case succesfull removal of the burnch
            // removes an echo for this device info
            //
            //return RemoveHubEcho(HcNode, DevInfo->bHubDeviceNumber);
            return EFI_SUCCESS;
        }
    }
    DevNode = TreeSearchSibling(HubNode->child, DevGrpByPortIf, DevInfo);
    if(DevNode==NULL) return EFI_SUCCESS;
    Dev = (USBDEV_T*)DevNode->data;
    if (Dev != NULL) {
        //
        // The disconnect event must have been droped
        // disconnect old info now
        //

        USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: echo found [%x]:\n" );
        USB_DEBUG(DEBUG_LEVEL_USBBUS,
            "\t(hc:0x%x,hub:0x%x,port:%d,addr:0x%x,if:%d)\n",
            Dev->dev_info->bHCNumber,
            Dev->dev_info->bHubDeviceNumber,
            Dev->dev_info->bHubPortNumber,
            Dev->dev_info->bDeviceAddress,
            Dev->dev_info->bInterfaceNum);
        return RemoveDevInfo(Dev->dev_info);
    }
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        RemoveDevInfo
//
// Description: Removes device node from the USB bus tree. Device node
//              corresponds to the DEV_INFO. Device gets removed in response to
//              the pending removal event sheduled from SMM when disconnect
//              was detected on USB
// Input:
//              DevInfo - DEV_INFO structure that was disconnect
//
// Output:      EFI_SUCCESS - echo wasn't found or was succesfully removed
//              otherwise return status resulted from attemp to remove the node
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RemoveDevInfo(DEV_INFO* DevInfo)
{
    TREENODE_T  *DevNode;
    TREENODE_T  *HcNode;
    EFI_STATUS  Status;

    HcNode = TreeSearchSibling(gUsbRootRoot->child, HcByIndex,
        &DevInfo->bHCNumber);
    if(HcNode==NULL) return EFI_NOT_FOUND;

    //Check for echoes

    DevNode = TreeSearchDeep(HcNode->child,DevGrpByAddr,
        &DevInfo->bDeviceAddress);
    if (DevNode==NULL){
        USB_DEBUG(DEBUG_LEVEL_USBBUS, "\tdevice is not found in the tree...\n" );
        return EFI_NOT_FOUND;
    }
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "\tdevice found in the tree...\n" );

    Status = EFI_SUCCESS;
    eUninstallDevice(DevNode->data, &Status);
    USB_DEBUG(DEBUG_LEVEL_USBBUS, "\tDisconnect complete: %r.\n", Status );

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbHcOnTimer
//
// Description: Timer call-back routine that is
//              is used to monitor changes on USB Bus
//              It monitors the state of queueCnnct and queueDiscnct queues
//              which get populated by UsbSmiNotify call-back routine
//
//              When this routine finds a new device connected to usb it
//              will install a device node for that device by calling
//              InstallDevice
//
//              When this routine finds a disconneced device it uninstalls the
//              device node by calling UninstallDevice
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbHcOnTimer(
    EFI_EVENT   Event,
    VOID        *Context
)
{
    DEV_INFO* EventCnnct = 0;
    static int i = 0;
    int Lock;
    EFI_STATUS  Status;

    UsbSmiPeriodicEvent();

	if (Event) {
		gBS->SetTimer(Event, TimerCancel, ONESECOND / 10);
	}

    ATOMIC({Lock = gBustreeLock; gBustreeLock = 1;});

    if (Lock) {
        USB_DEBUG(DEBUG_LEVEL_USBBUS, "UsbHcOnTimer::  is locked; return\n");
        return;
    }

    do {
        ATOMIC({EventCnnct = QueueGet(&gUsbData->QueueCnnctDisc);});

        if (EventCnnct == NULL) {
            break;
        }
        EventCnnct->Flag &= ~DEV_INFO_IN_QUEUE;
        //
        // There is no need to raise tpl here: this is callback of Event with
        // TPL_CALLBACK, so this code doesn't reenter; the Install and Uninstall
        // are also called from driver stop and start. Stop and start protect
        // the code at TPL_CALLBACK level
        //
        if( (EventCnnct->Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT |
            DEV_INFO_DEV_DUMMY)) == (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT) ){
            USB_DEBUG(DEBUG_LEVEL_USBBUS, "UsbHcOnTimer:: event connect [%d]: %x\n", i++, EventCnnct);

            RemoveDevInfoEcho(EventCnnct);
            InstallDevice(EventCnnct);
        } else if ((EventCnnct->Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT |
            DEV_INFO_DEV_DUMMY)) == DEV_INFO_VALID_STRUC) {
            USB_DEBUG(DEBUG_LEVEL_USBBUS,
                "UsbHcOnTimer:: event disconnect [%d]: %x\n", i++, EventCnnct);
            USB_DEBUG(DEBUG_LEVEL_USBBUS,
                "\t(hc:0x%x,hub:0x%x,port:%d,addr:0x%x,if:%d)\n",
                EventCnnct->bHCNumber, EventCnnct->bHubDeviceNumber,
                EventCnnct->bHubPortNumber, EventCnnct->bDeviceAddress,
                EventCnnct->bInterfaceNum);
            //RemoveDevInfoEcho(EventCnnct);
            Status = RemoveDevInfo(EventCnnct);
            if (EFI_ERROR(Status)) {
        		break;
            }
        }
    } while ( EventCnnct != NULL );

    gBustreeLock = 0;

	if (Event) {
		gBS->SetTimer(Event, TimerPeriodic, ONESECOND / 10);
	}
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  PopulateTree
//
// Description: Enumerate all DEV_INFO structures in the aDevInfoTable array
//              and install all currently connected device
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
PopulateTree(
    HC_STRUC    *HcStruc
)
{
    UINT16  i;

    PROGRESS_CODE(DXE_USB_DETECT);

	UsbHcOnTimer(NULL, NULL);

    for (i = 1; i < COUNTOF(gUsbData->aDevInfoTable); i++) {
        if ((gUsbData->aDevInfoTable[i].Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT | 
            DEV_INFO_DEV_DUMMY | DEV_INFO_DEV_BUS)) == (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_PRESENT)) {
            if (HcStruc != gUsbData->HcTable[gUsbData->aDevInfoTable[i].bHCNumber - 1]) {
                continue;
            }
			//
			// Valid and present device behind specified HC, so insert it in the tree
			//
			USB_DEBUG(DEBUG_LEVEL_3, "USBBUS: PopulateTree: found valid dev info[%d]: %x\n",i, gUsbData->aDevInfoTable +i );
			
			//RemoveDevInfoEcho(&gUsbData->aDevInfoTable[i]);
			//InstallDevice( gUsbData->aDevInfoTable + i );
            if (!(gUsbData->aDevInfoTable[i].Flag & DEV_INFO_IN_QUEUE)) {
                QueuePut(&gUsbData->QueueCnnctDisc, &gUsbData->aDevInfoTable[i]);
                gUsbData->aDevInfoTable[i].Flag |= DEV_INFO_IN_QUEUE;
            }
        }
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbBusGetControllerName
//
// Description: This function is a part of binding protocol, it returns
//              the string with the controller name.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16*
UsbBusGetControllerName(
    EFI_HANDLE  Controller,
    EFI_HANDLE  Child
)
{
                                        //(EIP60745+)>
    EFI_STATUS Status;

    Status = gBS->OpenProtocol ( Controller,
                            &gEfiUsb2HcProtocolGuid,
                            NULL,
                            gUSBBusDriverBinding.DriverBindingHandle,
                            Controller,
                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

    if (Status != EFI_SUCCESS && Status != EFI_ALREADY_STARTED) {
        return NULL;
    }
                                        //<(EIP60745+)
    if(Child) {
        //Get name for USB device
        EFI_USB_IO_PROTOCOL *UsbIo;
        USBDEV_T            *Dev ;
        if( EFI_ERROR(gBS->HandleProtocol(Child,& gEfiUsbIoProtocolGuid, &UsbIo)))
        {
            return NULL;
        }
        Dev = UsbIo2Dev(UsbIo);
        if( Dev->name == 0)
            Dev->name = LoadName(Dev);
        return Dev->name;
    } else {
        //Get name for USB HC
        return L"USB Host Controller (USBBUS)";
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbBusInit
//
// Description: Install driver binding and controller name protocols
//              for the USB bus driver.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbBusInit(
    EFI_HANDLE  ImageHandle,
    EFI_HANDLE  ServiceHandle
)
{
                                        //(EIP59272)>
    static NAME_SERVICE_T usbbus_names;
    gUSBBusDriverBinding.DriverBindingHandle = ServiceHandle;
    gUSBBusDriverBinding.ImageHandle = ImageHandle;

    return gBS->InstallMultipleProtocolInterfaces(
                &gUSBBusDriverBinding.DriverBindingHandle,
                &gEfiDriverBindingProtocolGuid, &gUSBBusDriverBinding,
                &gEfiComponentName2ProtocolGuid, InitNamesProtocol(&usbbus_names,
                L"USB bus", UsbBusGetControllerName),
                NULL);
                                        //<(EIP59272)
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbBusSupported
//
// Description: This is a binding protocol function that returns EFI_SUCCESS
//              for USB controller and EFI_UNSUPPORTED for any other kind of
//              controller.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbBusSupported(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE Controller,
    EFI_DEVICE_PATH_PROTOCOL *DevicePath
)
{
    EFI_STATUS  Status;
    VOID*       Ptr = 0;

    Status = gBS->OpenProtocol ( Controller, &gEfiUsb2HcProtocolGuid,
        &Ptr, This->DriverBindingHandle, Controller, EFI_OPEN_PROTOCOL_BY_DRIVER );

    if (Status != EFI_SUCCESS && Status != EFI_ALREADY_STARTED) {
        return EFI_UNSUPPORTED;
    } else if (Status == EFI_ALREADY_STARTED) {
        return Status;
    }

    gBS->CloseProtocol ( Controller, &gEfiUsb2HcProtocolGuid,
        This->DriverBindingHandle, Controller);

    Status = gBS->OpenProtocol ( Controller, &gEfiDevicePathProtocolGuid,
        NULL, This->DriverBindingHandle, Controller, EFI_OPEN_PROTOCOL_TEST_PROTOCOL );

    if (Status != EFI_SUCCESS && Status != EFI_ALREADY_STARTED) {
        return EFI_UNSUPPORTED;
    }

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbBusStop
//
// Description: This function is part of binding protocol installed on USB
//              controller. It stops the controller and removes all the
//              children.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbBusStop (
   EFI_DRIVER_BINDING_PROTOCOL     *This,
   EFI_HANDLE                      Controller,
   UINTN                           NumberOfChildren,
   EFI_HANDLE                      *Children  )
{
    EFI_STATUS	Status = EFI_SUCCESS;
    TREENODE_T	*HcNode;
    USBBUS_HC_T	*HcDev;

    //EFI_TPL SaveTpl = gBS->RaiseTPL (EFI_TPL_NOTIFY);
    //ASSERT(SaveTpl <= EFI_TPL_NOTIFY );

	HcNode = TreeSearchSibling(gUsbRootRoot->child, HcByHandle, &Controller );
	ASSERT(HcNode);
	if( HcNode == NULL ) {
		//gBS->RestoreTPL(SaveTpl);
		return EFI_DEVICE_ERROR;
	}
	HcDev = (USBBUS_HC_T*)HcNode->data;
    
	VERIFY_EFI_ERROR(
		gBS->SetTimer( gEvUsbEnumTimer, TimerCancel, ONESECOND/10));

    UsbHcOnTimer(NULL, NULL);
    
	if (TreeSearchSibling(HcNode->child, eUninstallDevice, &Status) != NULL)
	{
		USB_DEBUG(DEBUG_LEVEL_USBBUS, 
			"USBBUS: Stop HC: [%d] failed to uninstall children\n",
			((USBBUS_HC_T*)HcNode->data)->hc_data->bHCNumber);
		//gBS->RestoreTPL(SaveTpl);
	    VERIFY_EFI_ERROR(
			gBS->SetTimer ( gEvUsbEnumTimer, TimerPeriodic, ONESECOND/10));
		return Status;
	}

	if (NumberOfChildren == 0) {
		TreeRemove(HcNode);

		//
		// Close Protocols opened by driver
		//
		gBS->CloseProtocol (
			Controller, &gEfiUsb2HcProtocolGuid,
			This->DriverBindingHandle, Controller);
		
		gBS->FreePool(HcDev);
		
		if(--gCounterUsbEnumTimer==0){
			VERIFY_EFI_ERROR(
				gBS->SetTimer ( gEvUsbEnumTimer, TimerCancel, ONESECOND/10));
			VERIFY_EFI_ERROR(
				gBS->CloseEvent (gEvUsbEnumTimer));
			gEvUsbEnumTimer=0;
		}
	}

    if (gCounterUsbEnumTimer != 0) {
	    VERIFY_EFI_ERROR(
			gBS->SetTimer ( gEvUsbEnumTimer, TimerPeriodic, ONESECOND/10));
    }
    //gBS->RestoreTPL(SaveTpl);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbBusStart
//
// Description: This function is part of binding protocol installed on USB
//              controller. It starts the USB bus for a given controller.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbBusStart(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePathProtocol
)
{
    USBBUS_HC_T* HcDev = 0;
	EFI_STATUS	Status = EFI_UNSUPPORTED;

    VERIFY_EFI_ERROR (
        gBS->AllocatePool (
            EfiBootServicesData,
            sizeof(USBBUS_HC_T),
            &HcDev ));
    HcDev->type = NodeHC;
    HcDev->hc_data = FindHcStruc(Controller);

//    ASSERT(HcDev->hc_data);
    if (HcDev->hc_data == NULL) {
        gBS->FreePool(HcDev);
        return EFI_DEVICE_ERROR;
    }

    //
    // Open Protocols
    //
	Status = gBS->OpenProtocol ( Controller,
		&gEfiUsb2HcProtocolGuid,	&HcDev->hc,
		This->DriverBindingHandle, Controller,
		EFI_OPEN_PROTOCOL_BY_DRIVER );
	ASSERT_EFI_ERROR(Status);
	if (EFI_ERROR(Status)) {
		return Status;
	}

    Status = gBS->OpenProtocol ( Controller,
        &gEfiDevicePathProtocolGuid,
        &HcDev->dp, This->DriverBindingHandle,
        Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL );
	ASSERT_EFI_ERROR(Status);
	if (EFI_ERROR(Status)) {
		return Status;
	}

    //
    // Install Polling timer
    //
    {
        //EFI_TPL SaveTpl = gBS->RaiseTPL (EFI_TPL_NOTIFY);
        //ASSERT( SaveTpl <= EFI_TPL_NOTIFY);
        if(gEvUsbEnumTimer != 0) {
            VERIFY_EFI_ERROR(
                gBS->SetTimer ( gEvUsbEnumTimer, TimerCancel, ONESECOND/10));
        }
        //
        // Critical section

//        HookSmiNotify(1);

        USB_DEBUG(DEBUG_LEVEL_USBBUS,"**** \tnew hc_struc: %x(type:%x,number:%x)\n",
                HcDev->hc_data, HcDev->hc_data->bHCType, HcDev->hc_data->bHCNumber);

        //
        // Create HC branch in the USB root
        //
        TreeAddChild(gUsbRootRoot, TreeCreate(&HcDev->node,HcDev));

        gCounterUsbEnumTimer++;
        PopulateTree(HcDev->hc_data);

		UsbHcOnTimer(NULL, NULL);

        // Setting up global: gUsbDeviceToDisconnect, gUsbDeviceToConnect
        if (gEvUsbEnumTimer == 0) {
            USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: Start: setup timer callback %x\n", &UsbHcOnTimer );
            VERIFY_EFI_ERROR(
                gBS->CreateEvent ( EFI_EVENT_TIMER | EFI_EVENT_NOTIFY_SIGNAL,
                EFI_TPL_CALLBACK, UsbHcOnTimer,0,&gEvUsbEnumTimer));  
        }
        VERIFY_EFI_ERROR(
            gBS->SetTimer ( gEvUsbEnumTimer, TimerPeriodic, ONESECOND/10));
        //gBS->RestoreTPL(SaveTpl);
    }

    return EFI_SUCCESS;
}

#if defined(DEBUG_SWITCH) && (DEBUG_SWITCH == 1)
VOID DEBUG_DELAY()
{
    int i;
     PrintDebugMsg(3,"\nDELAY: ");
    for(i=0;i<10;i++){
        PrintDebugMsg(3,"%d..",i);
        pBS->Stall(200*1000);
    }
    PrintDebugMsg(3,"\n");
}
#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2015, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
