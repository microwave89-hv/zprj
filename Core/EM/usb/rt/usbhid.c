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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbhid.c 39    10/16/16 10:12p Wilsonlee $
//
// $Revision: 39 $
//
// $Date: 10/16/16 10:12p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
//
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbhid.c $
// 
// 39    10/16/16 10:12p Wilsonlee
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
// 38    3/02/16 9:41p Wilsonlee
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
// 37    4/29/15 5:29a Wilsonlee
// [TAG]  		EIP215830
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	CYBORG R.A.T3 Gaming Mouse left/right button has no
// function, instead DPI UP/DOWN config button has left/right click
// function.
// [RootCause]  	We get mouuse button data from constant data offset.
// [Solution]  	Mouse Data should be defining report fields that contain
// modifiable device data.
// [Files]  		usbms.c, usbhid.c, usbpoint.c
// 
// 36    2/05/15 5:54a Wilsonlee
// [TAG]  		EIP203944
// [Category]  	Improvement
// [Description]  	If InputReportDataLength is less than IntMaxPkt, we
// need to use IntMaxPkt polling interrupt data.
// [Files]  		usbhid.c
// 
// 35    12/24/14 9:33p Wilsonlee
// [TAG]  		EIP194683
// [Category]  	Improvement
// [Description]  	Add the flag "USB_INCMPT_HID_BOOT_PROTOCOL_ONLY" of usb
// bad device table to keep devices use boot protocol.
// [Files]  		usbkbd.c, usbms.c, usbhid.c, usbdef.h
// 
// 34    10/05/14 10:06p Wilsonlee
// [TAG]  		EIP186639
// [Category]  	Improvement
// [Description]  	Medigenic-Esterline USB keboard (Advanced Input Devices
// chip) workaround.
// [Files]  		usbhid.c
// 
// 33    9/30/14 2:42a Wilsonlee
// [TAG]  		EIP183901
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System will hang up when attach special docking.
// [RootCause]  	It hangs at HidParserLocal function because it caused
// dead loop if Field->UsageMax is 0xFFFF.
// [Solution]  	Change Data to UINT32.
// [Files]  		usbhid.c
// 
// 32    9/02/14 3:53a Wilsonlee
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
// 31    8/07/14 2:19a Wilsonlee
// [TAG]  		EIP176549
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Microstep USB Keyboard issue.
// [RootCause]  	The report descriptor of Microstep USB Keyboard (Sonix
// Technology Co chip) has an error, Modifier keys is bitmap data, but it
// reports as array data.
// [Solution]  	We need to force variable flag for Modifier keys input
// item.
// [Files]  		usbhid.c, usbkbd.c, usbdef.h
// 
// 30    5/06/14 5:15a Ryanchou
// [TAG]  		EIP166835
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Arrow keys cannot work with specific USB keyboard
// [RootCause]  	HID driver cannot parse a input report that includes both
// usage minimum/maximum and single usage.
// [Solution]  	Store the usage in the same array to determine the input
// data format.
// [Files]  		syskbc.c, sysnokbc.c, usbdef.h, usbhid.c, usbkbd.c,
// usbkbd.h, usbms.c, usbpoint, efiusbhid.c, efiusbpoint.c
// 
// 29    4/30/14 6:14a Ryanchou
// [TAG]  		EIP151374
// [Category]  	Improvement
// [Description]  	Calculates maximum data length to be reported in the
// HID device.
// [Files]  		ehci.c, ohci.c, uhci.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, xhci.c
// 
// 28    4/29/14 7:54p Wilsonlee
// [TAG]  		EIP163828
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	The mouses stop more than 4 seconds during TP 0xB4 when
// power on several times.
// [RootCause]  	The device sometime doesn't respond the set report
// command.
// [Solution]  	Change the timeout of set report command to 100 ms.
// [Files]  		syskbc.c, sysnokbc.c, usbhid.c, amiusb.h
// 
// 27    4/23/14 10:59p Wilsonlee
// [TAG]  		EIP158723
// [Category]  	Improvement
// [Description]  	It sends set idle command before getting report
// descriptor command.
// [Files]  		usbhid.c
// 
// 26    2/26/14 1:56a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 25    11/05/13 5:38a Ryanchou
// [TAG]  		EIP139807
// [Category]  	Improvement
// [Description]  	Handle the 4 bytes of item size.
// [Files]  		usbhid.c
// 
// 24    10/19/13 7:07a Ryanchou
// [TAG]  		EIP138257
// [Category]  	Improvement
// [Description]  	Correct USB HID device type.
// [Files]  		amiusb.c, usbdef.h, usbhid.c, efiusbhid.c, uhcd.c
// 
// 23    9/04/13 11:56p Ryanchou
// [TAG]  		N/A
// [Category]  	Improvement
// [Description]  	Add usage page check for HID set feature request.
// [Files]  		usbhid.c
// 
// 22    7/04/13 5:48a Roberthsu
// [TAG]           EIP127014 
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Mouse drifting not smooth
// [RootCause]     Bbecause Efi simple point protocol RelativeMovementX
// type is INT32.
// [Solution]      Transfer data type to INT32.
// [Files]         usbdef.h,usbhid.c,usbms.c,usbkbd.h
// 
// 21    3/19/13 3:59a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 20    3/07/13 8:52a Ryanchou
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
// 19    1/11/13 4:15a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 18    11/29/12 7:47a Ryanchou
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
// 17    11/10/12 6:39a Ryanchou
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
// 16    10/26/12 8:50a Roberthsu
// [TAG]           EIP101990 
// [Category]      Improvement
// [Description]   Add check inpurt mode.
// [Files]         usbhid.c,usbpoint.c
// 
// 15    8/27/12 5:07a Roberthsu
// [TAG]           EIP98251
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       RF KB NumLock/ScrollLock/CapsLock indicator is not
// available during post or BIOS setup menu
// [RootCause]  	Set led command lost report id.
// [Solution]      Check report id exist.
// [Files]         syskbc.c,usbhid.c
// 
// 14    8/13/12 3:24a Roberthsu
// [TAG]           EIP96010
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       The KB can not work under bios.
// [RootCause]     Usage count overflow.
// [Solution]      Add usage count check.
// [Files]         usbdef.h,usbhid.c
// 
// 13    5/04/12 2:37a Roberthsu
// [TAG]           EIP89279
// [Category]      Improvement
// [Description]   Add check totalcount condition.
// [Files]         usbhid.c
// 
// 12    5/03/12 6:25a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 11    4/24/12 3:52a Roberthsu
// [TAG]           EIP84336
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       When insert the touch board, it will block the function
// of rear USB ports.
// [RootCause]     Report buffer size not enough.
// [Solution]      Create Report buffer by report item count.
// [Files]         usbhid.c
// 
// 10    4/05/12 7:42a Wilsonlee
// [TAG]  		EIP86001
// [Category]  	Improvement
// [Description]  	Free the chunk of memory allocated using the
// USBMem_Alloc call when we didn't use it. 
// [Files]  		usbhid.c, ehci.c
// 
// 9     4/03/12 5:52a Roberthsu
// [TAG]           EIP80948
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       When insert the touch board, it will block the function
// of rear USB ports.
// [RootCause]     Report item not enough.
// [Solution]      Create buffer use report length.
// [Files]         usbhid.c,usbdef.h
// 
// 8     3/23/12 4:28a Roberthsu
// [TAG]           EIP84264
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       After updating usb module, system will hang at BIOS
// LOGO display.
// [RootCause]     Allocate memory not enough.
// [Solution]      Allocate memory by report length
// [Files]         usbhid.c
// 
// 7     12/14/11 2:12a Ryanchou
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
// 6     10/21/11 2:35a Roberthsu
// [TAG]           EIP71068
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Thermaltake mouse is not work
// [RootCause]     Because some undefine usage page report.
// [Solution]      Get all input report.
// [Files]         usbhid.c
// 
// 5     9/27/11 1:41a Roberthsu
// [TAG]     EIP67400
// [Category]    Bug Fix
// [Severity]    Normal
// [Symptom]     Microsoft wireless Media Desktop 1000 can¡¦t work normal.
// [RootCause]   Wireless ms report data contains usage page keyboard.And
// output data not contains vaild report id.
// [Solution]    Check usage page led to decide kb or ms.Check correct
// report id with report data.
// [Files]       usbkbd.c,usbhid.c,usbms.c
// 
// 4     9/27/11 12:05a Roberthsu
// [TAG]  		EIP65344
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Razer mouse will hang in post
// [RootCause]  	Razer has report keyboard interface.But not report led
// usage.
// [Solution]  	Check if not report led usage page.Do not send led
// command.
// [Files]  		syskbc.c,usbhid.c,usbdef.h
// 
// 3     9/26/11 11:45p Roberthsu
// [TAG]  		EIP67230
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Ntrig touch panel can not use on CedarTrail
// [RootCause]  	Because ntrig report data over than 512 byte.Control
// transfer check if over 512 than set length is 512.
// [Solution]  	Remove check transfer length.
// [Files]  		ohci.c,uhci.c,usbhid.c
// 
// 2     8/05/11 7:32a Ryanchou
// [TAG]  		EIP66231
// [Category]  	Improvement
// [Description]  	Remove token POINT_SUPPORT.Add token USB_DEV_POINT.Add
// check core version in point driver.Add check device descriptor to send
// get lang id command.Modify check button usage page.
// [Files]  		efiusbhid.c, efiusbpoint.c, usbbus.c, usbhid.c, usbpoint.c,
// usbsrc.sdl
// 
// 1     7/15/11 6:16a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, efiusbpoint.c, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c,
// usb.c, usbdef.h, usbhid.c, usbkbd.c, usbkbd.h, usbms.c, usbpoint.c,
// usbrt.cif, usbsb.c, usbsetup.c, usbsrc.sdl, xhci.c
// 
//
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           usbhid.c
//
//  Description:    USB HID class device driver
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "amiusb.h"
#include "usbkbd.h"

extern USB_GLOBAL_DATA *gUsbData; 

UINT8	UsbControlTransfer(HC_STRUC*, DEV_INFO*, DEV_REQ, UINT16, VOID*);

VOID        USBHIDInitialize (VOID);
UINT8       USBHIDCheckForDevice (DEV_INFO*, UINT8, UINT8, UINT8);
DEV_INFO*   USBHIDConfigureDevice (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT16);
UINT8   	USBHIDProcessData ( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8       USBHIDDisconnectDevice (DEV_INFO*);

UINT8		HidGetReportDescriptor(HC_STRUC*, DEV_INFO*, HID_DESC*);  

VOID        USBMSInitialize (VOID);
DEV_INFO*   USBMSConfigureDevice (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT16); 
DEV_INFO*   USBKBDConfigureDevice (DEV_INFO*);  //(EIP84455)
DEV_INFO*   USBAbsConfigureDevice (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT16);  
VOID        CheckInputMode(DEV_INFO *DevInfo, HID_REPORT_FIELD * Field);    //(EIP101990)

VOID
USBHIDFillDriverEntries (DEV_DRIVER *fpDevDriver)
{
    fpDevDriver->bDevType               = BIOS_DEV_TYPE_HID;
    fpDevDriver->bBaseClass             = BASE_CLASS_HID;
    fpDevDriver->bSubClass              = 0;
    fpDevDriver->bProtocol              = 0;
    fpDevDriver->pfnDeviceInit          = USBHIDInitialize;
    fpDevDriver->pfnCheckDeviceType     = USBHIDCheckForDevice;
    fpDevDriver->pfnConfigureDevice     = USBHIDConfigureDevice;
    fpDevDriver->pfnDisconnectDevice    = USBHIDDisconnectDevice;

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBHIDInitialize (VOID)
//
// Description: This function returns fills the host controller driver
//              routine pointers in the structure provided
//
// Input:       Nothing
//
// Output:      Nothing
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBHIDInitialize (VOID)
{
	USBKBDInitialize();
	USBMSInitialize();
    USB_InstallCallBackFunction(USBHIDProcessData);

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMSCheckForMouse
//
// Description: This routine checks for mouse type device from the
//              interface data provided
//
// Input:   bBaseClass  USB base class code
//          bSubClass   USB sub-class code
//          bProtocol   USB protocol code
//
// Output:  BIOS_DEV_TYPE_MOUSE type on success or 0FFH on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHIDCheckForDevice (
    DEV_INFO* fpDevInfo,
    UINT8 bBaseClass,
    UINT8 bSubClass,
    UINT8 bProtocol
)
{
	//
	// Check the BaseClass, SubClass and Protocol for a HID/Boot/Mouse device.
	//
	if (bBaseClass != BASE_CLASS_HID) {
		return USB_ERROR;
	}

    if ((BOOT_PROTOCOL_SUPPORT != 0) || 
        (fpDevInfo->wIncompatFlags & USB_INCMPT_HID_BOOT_PROTOCOL_ONLY)) {
        if (bSubClass != SUB_CLASS_BOOT_DEVICE) {
            return USB_ERROR;
        }
    
        if (bProtocol != PROTOCOL_KEYBOARD &&
            bProtocol != PROTOCOL_MOUSE) {
            return USB_ERROR;
        }
    }

	return	BIOS_DEV_TYPE_HID;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHIDConfigureKeyboard
//
// Description: This routine checks an interface descriptor of the USB device
//      detected to see if it describes a HID/Boot/Keyboard device.
//      If the device matches the above criteria, then the device is
//      configured and initialized
//
// Input:       fpHCStruc   HCStruc pointer
//              fpDevInfo   Device information structure pointer
//              fpDesc      Pointer to the descriptor structure
//              wStart      Offset within interface descriptor
//                      supported by the device
//              wEnd        End offset of the device descriptor
//
// Output:      FPDEV_INFO  New device info structure, 0 on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
                                        //(EIP84455+)>
DEV_INFO*
USBHIDConfigureDevice (
    HC_STRUC*   fpHCStruc,
    DEV_INFO*   fpDevInfo,
    UINT8*      fpDesc,
    UINT16      wStart,
    UINT16      wEnd)
{
    ENDP_DESC       *fpEndpDesc;
    INTRF_DESC      *fpIntrfDesc;
	UINT8			*DescEnd;
	HID_DESC		*HidDesc = NULL;
	DEV_REQ			Request = {0};
    
	fpDevInfo->bDeviceType = (UINT8)BIOS_DEV_TYPE_HID;
	fpDevInfo->HidDevType = 0;
    fpDevInfo->IntInEndpoint = 0;
    fpDevInfo->IntOutEndpoint = 0;

	MemSet(&fpDevInfo->HidReport, sizeof(fpDevInfo->HidReport), 0);

	USB_DEBUG(3, "USBHIDConfigureDevice...  \n");

    fpDevInfo->bCallBackIndex = USB_InstallCallBackFunction(USBHIDProcessData);

    fpIntrfDesc = (INTRF_DESC*)(fpDesc + wStart);
    DescEnd = fpDesc + ((CNFG_DESC*)fpDesc)->wTotalLength; // Calculate the end of descriptor block
    fpEndpDesc = (ENDP_DESC*)((char*)fpIntrfDesc + fpIntrfDesc->bDescLength);

    //Select correct endpoint
    for (;(fpEndpDesc->bDescType != DESC_TYPE_INTERFACE) && ((UINT8*)fpEndpDesc < DescEnd);
        fpEndpDesc = (ENDP_DESC*)((UINT8 *)fpEndpDesc + fpEndpDesc->bDescLength)){
        if(!(fpEndpDesc->bDescLength)) {
            break;  // Br if 0 length desc (should never happen, but...)
        }

		if (fpEndpDesc->bDescType == DESC_TYPE_HID ) {
			HidDesc = (HID_DESC*)fpEndpDesc;
			continue;
		}

        if (fpEndpDesc->bDescType != DESC_TYPE_ENDPOINT ) {
            continue;
        }

        //
        // Check for and configure Interrupt endpoint if present
        //
        if ((fpEndpDesc->bEndpointFlags & EP_DESC_FLAG_TYPE_BITS) !=
                EP_DESC_FLAG_TYPE_INT) {    // Bit 1-0: 10 = Endpoint does interrupt transfers
			continue;
        }
		if (fpEndpDesc->bEndpointAddr & EP_DESC_ADDR_DIR_BIT) {
            if (fpDevInfo->IntInEndpoint == 0) {
                fpDevInfo->IntInEndpoint = fpEndpDesc->bEndpointAddr;
                fpDevInfo->IntInMaxPkt = fpEndpDesc->wMaxPacketSize;
                fpDevInfo->bPollInterval = fpEndpDesc->bPollInterval;
            }
        } else {
            if (fpDevInfo->IntOutEndpoint == 0) {
                fpDevInfo->IntOutEndpoint = fpEndpDesc->bEndpointAddr;
                fpDevInfo->IntOutMaxPkt = fpEndpDesc->wMaxPacketSize;
            }
        }
    }

    if (fpDevInfo->IntInEndpoint == 0) {
        return 0;
    }

	//Set protocol (Option)
	if ((BOOT_PROTOCOL_SUPPORT != 0) &&
		!(fpDevInfo->wIncompatFlags & USB_INCMPT_SET_BOOT_PROTOCOL_NOT_SUPPORTED) ||
		(fpDevInfo->wIncompatFlags & USB_INCMPT_HID_BOOT_PROTOCOL_ONLY)) {
		//
		// Send the set protocol command, wValue = 0 (Boot protocol)
		//
		Request.wRequestType = HID_RQ_SET_PROTOCOL;
		Request.wValue = 0;		// 0: Boot Protocol
		Request.wIndex = fpDevInfo->bInterfaceNum;
		Request.wDataLength = 0;
		
		UsbControlTransfer(fpHCStruc, fpDevInfo, Request, 100, NULL);
	} 

	//Send Set_Idle command 
	Request.wRequestType = HID_RQ_SET_IDLE;
	Request.wValue = 0;
	Request.wIndex = fpDevInfo->bInterfaceNum;
	Request.wDataLength = 0;
	
	UsbControlTransfer(fpHCStruc, fpDevInfo, Request, 100, NULL);

	if ((BOOT_PROTOCOL_SUPPORT == 0) && 
        !(fpDevInfo->wIncompatFlags & USB_INCMPT_HID_BOOT_PROTOCOL_ONLY)) {
		HidGetReportDescriptor(fpHCStruc, fpDevInfo, HidDesc);
		fpDevInfo->HidReport.Flag |= HID_REPORT_FLAG_REPORT_PROTOCOL;
        if (fpDevInfo->PollingLength < fpDevInfo->IntInMaxPkt) {
            fpDevInfo->PollingLength = fpDevInfo->IntInMaxPkt;
        }
	} else {
		fpDevInfo->PollingLength = fpDevInfo->IntInMaxPkt;
		switch (fpDevInfo->bProtocol) {
			case PROTOCOL_KEYBOARD:
				fpDevInfo->HidDevType = HID_DEV_TYPE_KEYBOARD;
				break;

			case PROTOCOL_MOUSE:
				fpDevInfo->HidDevType = HID_DEV_TYPE_MOUSE;
				break;

			default:
				break;
		}
	}

    if (fpDevInfo->HidDevType & HID_DEV_TYPE_KEYBOARD) { 
        if (!(USBKBDConfigureDevice(fpDevInfo))) {
            return 0;
        }
    }

//Active polling
    if ((fpDevInfo->PollingLength != 0) && (fpDevInfo->bPollInterval != 0)) {
		if (!((fpDevInfo->HidDevType & HID_DEV_TYPE_MOUSE) && (gUsbData->dUSBStateFlag & USB_FLAG_EFIMS_DIRECT_ACCESS))) {
            (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDActivatePolling)(fpHCStruc,fpDevInfo);
        }
    }


    return fpDevInfo;
} 
                                        //<(EIP84455+)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBHIDDisconnectDevice
//
// Description: This routine disconnects the keyboard by freeing
//              the USB keyboard device table entry
//
// Input:       fpDevInfo   Pointer to DeviceInfo structure
//
// Output:      USB_SUCCESS/USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHIDDisconnectDevice (
	DEV_INFO	*DevInfo
)
{
	HC_STRUC	*HcStruc = gUsbData->HcTable[DevInfo->bHCNumber - 1];
	UINT16		Index;

	// Stop polling the endpoint
	(*gUsbData->aHCDriverTable[GET_HCD_INDEX(HcStruc->bHCType)].pfnHCDDeactivatePolling)(HcStruc, DevInfo);
	DevInfo->IntInEndpoint = 0;

    if (DevInfo->HidDevType & HID_DEV_TYPE_KEYBOARD) {
        USBKBDDisconnectDevice(DevInfo);
    }

    if (DevInfo->HidReport.Fields != NULL) {
		for (Index = 0; Index < DevInfo->HidReport.FieldCount; Index++) {
			if (DevInfo->HidReport.Fields[Index]->Usages != NULL) {
				USB_MemFree(DevInfo->HidReport.Fields[Index]->Usages, 
					GET_MEM_BLK_COUNT(DevInfo->HidReport.Fields[Index]->UsageCount * sizeof(UINT16)));
				DevInfo->HidReport.Fields[Index]->Usages = NULL;
			}
			USB_MemFree(DevInfo->HidReport.Fields[Index], GET_MEM_BLK_COUNT(sizeof(HID_REPORT_FIELD)));
			DevInfo->HidReport.Fields[Index] = NULL;
		}

		USB_MemFree(DevInfo->HidReport.Fields, GET_MEM_BLK_COUNT(DevInfo->HidReport.FieldCount * sizeof(HID_REPORT_FIELD*)));
        DevInfo->HidReport.Fields = NULL;
        DevInfo->HidReport.ReportDescLen = 0;
    }

	return USB_SUCCESS; 	
} 

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       ExtractInputReportData
//
// Description: 
//
// intput:      
//
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
ExtractInputReportData (
	UINT8	*Report,
	UINT16	Offset,
	UINT16	Size
)
{
	UINT32	*Start;
	UINT8	BitOffset;
	UINT32	Data = 0;

	ASSERT(Data <= 32);
	Start = (UINT32*)((UINTN)Report + (Offset >> 3));
	BitOffset = Offset & 0x7;
	Data = (*Start >> BitOffset) & ((0x1 << Size) - 1);
	return Data;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       GetItemData
//
// Description: This funtion copy data of the item to buffer.
//
// intput:      
//
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
GetItemData (
	HID_ITEM	*Item,
	VOID		*Buffer,
	UINT32		BufferSize
)
{
	UINT32	Size = Item->bSize > BufferSize ? BufferSize : Item->bSize;
	MemSet(Buffer, BufferSize, 0);
	MemCpy(Buffer, &Item->data, Size);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       AddUsage
//
// Description: This funtion adds usage into usage table.
//
// intput:      
//
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
AddUsage (
	HID_REPORT_FIELD	*Field,
	UINT16				Usage
)
{
	if (Field->UsageCount >= Field->MaxUsages) {
		return;
	}

	Field->Usages[Field->UsageCount++] = Usage;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       Add_Hid_Field
//
// Description: Add input or output item.
//
// intput:      
//
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
                                        //(EIP84455+)>
VOID
AddField (
	HID_REPORT			*Report,
	HID_REPORT_FIELD	*Field
)
{
	HID_REPORT_FIELD	*NewField;
	HID_REPORT_FIELD	**Fields;
	UINT16				Index;

	NewField = USB_MemAlloc(GET_MEM_BLK_COUNT(sizeof(HID_REPORT_FIELD)));
	ASSERT(NewField != NULL);
	if (NewField == NULL) {
		return;
	}

	if (Field->ReportId != 0) {
		Report->Flag |= HID_REPORT_FLAG_REPORT_ID;
	}

	MemCpy(NewField, Field, sizeof(HID_REPORT_FIELD));
	NewField->Usages = NULL;

	USB_DEBUG(4, "============================================== \n");
	USB_DEBUG(4, "Field index = %02x, \t", Report->FieldCount);
	USB_DEBUG(4, "Flag = %02x\n", NewField->Flag);
	USB_DEBUG(4, "UsagePage = %4x, \t", NewField->UsagePage);
	USB_DEBUG(4, "ReportId = %02x\n", NewField->ReportId);
	USB_DEBUG(4, "ReportCount = %02x, \t", NewField->ReportCount);
	USB_DEBUG(4, "bReportSize = %02x\n", NewField->ReportSize);
	USB_DEBUG(4, "LogicalMin = %4x, \t", NewField->LogicalMin);
	USB_DEBUG(4, "LogicalMax = %4x\n", NewField->LogicalMax);
	USB_DEBUG(4, "PhysicalMax = %4x, \t", NewField->PhysicalMax);
	USB_DEBUG(4, "PhysicalMin = %4x\n", NewField->PhysicalMin);
	USB_DEBUG(4, "UnitExponent = %2x, \t", NewField->UnitExponent);
	USB_DEBUG(4, "UsageCount = %4x\n", NewField->UsageCount);

	if (NewField->UsageCount != 0) {
		NewField->Usages = USB_MemAlloc (GET_MEM_BLK_COUNT(NewField->UsageCount * sizeof(UINT16)));
		ASSERT(NewField->Usages != NULL);
		if (NewField->Usages == NULL) {
			return;
		}

		MemCpy(NewField->Usages, Field->Usages, NewField->UsageCount * sizeof(UINT16));

		USB_DEBUG(4, "Usages:\n");
		for (Index = 0; Index < NewField->UsageCount; Index++) {
			if ((NewField->UsagePage == 0x01) && (NewField->Usages[Index] == 0x30)) {
				if (NewField->Flag & HID_REPORT_FIELD_FLAG_RELATIVE) {
					Report->Flag |= HID_REPORT_FLAG_RELATIVE_DATA;
				} else {
					Report->Flag |= HID_REPORT_FLAG_ABSOLUTE_DATA;
				}
				Report->AbsMaxX = NewField->LogicalMax;
			}
			if (NewField->Usages[Index] == 0x31) {
				Report->AbsMaxY= NewField->LogicalMax;
			}
			USB_DEBUG(4, "%02X ", NewField->Usages[Index]); 	
			if ((Index & 0xF) == 0xF) {
				USB_DEBUG(4, "\n"); 
			}
		}
	}
	USB_DEBUG(4, "\n============================================== \n");

	Fields = USB_MemAlloc(GET_MEM_BLK_COUNT((Report->FieldCount + 1) * sizeof(HID_REPORT_FIELD*)));
	ASSERT(Fields != NULL);
	if (Fields == NULL) {
		return;
	}

	if (Report->Fields != NULL) {
		MemCpy(Fields, Report->Fields, Report->FieldCount * sizeof(HID_REPORT_FIELD*));
		USB_MemFree(Report->Fields, GET_MEM_BLK_COUNT(Report->FieldCount * sizeof(HID_REPORT_FIELD*)));
	}

	Report->Fields = Fields;
	Report->Fields[Report->FieldCount++] = NewField;

	return;
}
                                        //<(EIP84455+)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       HidParserMain
//
// Description: 
//
// intput:      
//
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
HidParserMain (
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field,
	HID_ITEM 			*Item
)
{
    UINT8	Data = 0;
                                        //(EIP71068)>
	switch (Item->bTag) {
		case HID_MAIN_ITEM_TAG_BEGIN_COLLECTION:
			GetItemData(Item, &Data, sizeof(Data));

			// Check if it is application collection
			if (Data == 0x01) {
				if (Field->UsagePage == 0x01) { 	// Generic Desktop
					switch (Field->Usages[Field->UsageCount - 1]) {
						case 0x01:		// Pointer
						case 0x02:		// Mouse
							DevInfo->HidDevType |= HID_DEV_TYPE_MOUSE;
							break;
						case 0x06:		// Keyboard
						case 0x07:		// KeyPad
							DevInfo->HidDevType |= HID_DEV_TYPE_KEYBOARD;
							break;
						default:
							break;
					}
				} else if (Field->UsagePage == 0x0D) {	// Digitizer
					if (Field->Usages[Field->UsageCount - 1] == 0x04) {
						DevInfo->HidDevType |= HID_DEV_TYPE_POINT;
					}
				}
			}
			break;

		case HID_MAIN_ITEM_TAG_END_COLLECTION:
			break;

		case HID_MAIN_ITEM_TAG_INPUT:
			GetItemData(Item, &Field->Flag, sizeof(Field->Flag));
			Field->Flag = (Field->Flag & 7) | HID_REPORT_FIELD_FLAG_INPUT;
            
            // Microstep USB Keyboard (Sonix Technology Co chip) workaround
            // The report descriptor has an error, Modifier keys is bitmap data, but 
            // it reports as array data. We force variable flag for Modifier keys input item.
            if ((DevInfo->wVendorId == 0x0C45) && 
                ((DevInfo->wDeviceId == 0x7603) || (DevInfo->wDeviceId == 0x7624))) {
                if ((Field->UsagePage == HID_UP_KEYBOARD) && 
                    (Field->UsageMin == HID_UP_KEYBOARD_LEFT_CTRL) &&
                    (Field->UsageMax == HID_UP_KEYBOARD_RIGHT_GUI)) {
                    Field->Flag |= HID_REPORT_FIELD_FLAG_VARIABLE;
                }
            }
            
    		AddField(&DevInfo->HidReport, Field);
			break;

		case HID_MAIN_ITEM_TAG_OUTPUT:
			GetItemData(Item, &Field->Flag, sizeof(Field->Flag));
			Field->Flag &= 7;
                                        //(EIP98251+)>
            if (Field->UsagePage == 0x8) {
				AddField(&DevInfo->HidReport, Field);
            }                                        //<(EIP98251+)
			break;

		case HID_MAIN_ITEM_TAG_FEATURE:
            CheckInputMode(DevInfo, Field);  //(EIP101990)
			break;

		default:
			break;
	}
                                        //<(EIP71068)
                                        //(EIP84455+)>
//Clear Local Item
	MemSet(Field->Usages, Field->UsageCount * sizeof(UINT16), 0);
	Field->UsageCount = 0;
	Field->UsageMin = 0;
	Field->UsageMax = 0;

                                        //<(EIP84455+)
	return 0;
}  

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       HidParserGlobal
//
// Description:	Parsing Global item 
//
// intput:      
//
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
HidParserGlobal (
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field,
	HID_ITEM 			*Item
)
{
	switch (Item->bTag) {
		case HID_GLOBAL_ITEM_TAG_USAGE_PAGE:
			GetItemData(Item, &Field->UsagePage, sizeof(Field->UsagePage));
										//(EIP65344+)>
            //Get Led usage page
			if (Field->UsagePage == 0x8) {
                DevInfo->HidReport.Flag |= HID_REPORT_FLAG_LED_FLAG;
			}
										//<(EIP65344+) 
			break;

		case HID_GLOBAL_ITEM_TAG_LOGICAL_MINIMUM:
			GetItemData(Item, &Field->LogicalMin, sizeof(Field->LogicalMin));
			break;
		
		case HID_GLOBAL_ITEM_TAG_LOGICAL_MAXIMUM:
			GetItemData(Item, &Field->LogicalMax, sizeof(Field->LogicalMax));
			break;
                                        //(EIP127014+)>
		case HID_GLOBAL_ITEM_TAG_PHYSICAL_MINIMUM:
			GetItemData(Item, &Field->PhysicalMin, sizeof(Field->PhysicalMin));
			break;
		
		case HID_GLOBAL_ITEM_TAG_PHYSICAL_MAXIMUM:
			GetItemData(Item, &Field->PhysicalMax, sizeof(Field->PhysicalMax));
			break;

		case HID_GLOBAL_ITEM_TAG_UNIT_EXPONENT:
			GetItemData(Item, &Field->UnitExponent, sizeof(Field->UnitExponent));
			break;
                                        //<(EIP127014+)
		case HID_GLOBAL_ITEM_TAG_REPORT_SIZE:
			GetItemData(Item, &Field->ReportSize, sizeof(Field->ReportSize));
			break;
		
		case HID_GLOBAL_ITEM_TAG_REPORT_COUNT:
			GetItemData(Item, &Field->ReportCount, sizeof(Field->ReportCount));
			break;
		
		case HID_GLOBAL_ITEM_TAG_REPORT_ID:
			GetItemData(Item, &Field->ReportId, sizeof(Field->ReportId));
			break;
		
		default:
			break;
	} 

	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       HidParserLocal
//
// Description: Parsing Local item
//
// intput:      
//
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
HidParserLocal (
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field,
	HID_ITEM			*Item
)
{
	UINT32	Data;

	GetItemData(Item, &Data, sizeof(Data));

	switch (Item->bTag) {
		case HID_LOCAL_ITEM_TAG_USAGE:
			AddUsage(Field, Data);
			break;
		
		case HID_LOCAL_ITEM_TAG_USAGE_MINIMUM:
			Field->UsageMin = Data;
			break;
		
		case HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM:
			Field->UsageMax = Data;
            
            // Medigenic-Esterline USB keboard (Advanced Input Devices chip) 
            // workaround. This device reports the wrong local minimum for 
            // keyboard data in its report descriptor, local minimum should be 0x00.
            
            if ((DevInfo->wVendorId == 0x059d) && (DevInfo->wDeviceId == 0x0708)) {
                if ((Field->UsageMin == 0x01) && (Field->UsageMax == 0x65)) {
                    Field->UsageMin = 0x00;
                }
            }

			for (Data = Field->UsageMin; Data <= Field->UsageMax; Data++) {
				AddUsage(Field, Data);
			}
			break;
		
		default:	
			break;
	}

	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       HidParserReserved
//
// Description: Parsing Reserved item
//
// intput:      
//
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
HidParserReserved(
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field,
	HID_ITEM			*Item
)
{
	return USB_SUCCESS;
} 

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       HidParseReportDescriptor
//
// Description: 
//              
// intput:      
//              
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
HidParseReportDescriptor (
    DEV_INFO	*DevInfo,
    UINT8		*ReportDesc
)
{
	HID_REPORT			*Report = &DevInfo->HidReport;
	UINT8				*Start = ReportDesc;
	UINT8				*End = Start + Report->ReportDescLen;
	UINT16				Usages[0x300] = {0};
	HID_REPORT_FIELD	Field = {0};
	HID_ITEM  			Item = {0};
	UINT8 				Data;
	UINT8				DataSize[] = {0, 1, 2, 4};

	static	UINT8 (*DispatchType[]) (DEV_INFO *DevInfo, 
					HID_REPORT_FIELD *Field, HID_ITEM *Item) = {
		HidParserMain,
		HidParserGlobal,
		HidParserLocal,
		HidParserReserved
	};

	Field.Usages = Usages;
	Field.MaxUsages = COUNTOF(Usages);
	
	while (Start < End) {
		Data = *Start++;

		Item.bType = (Data >> 2) & 0x3;
		Item.bTag  = (Data >> 4) & 0xF;
		Item.bSize = DataSize[Data & 0x3];

		if ((Start + Item.bSize) > End) {
			break;
		}
	
		MemCpy(&Item.data.u32, Start, Item.bSize);
		Start += Item.bSize;
		DispatchType[Item.bType](DevInfo, &Field, &Item);
	}

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       CalculateInputReportDataLength
//
// Description: This function calculates max data length to be reported 
//				in the HID device.
//
// intput:      
//              
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
CalculateInputReportDataLength (
	DEV_INFO	*DevInfo
)
{
	UINT8				Index = 0;
	HID_REPORT_FIELD	*Field = NULL;
	UINT16				ReportLen[256] = {0};
	UINT16				Length = 0;
	UINT16				MaxLength = 0;
	UINT16				ReportId = 0;

	for (Index = 0; Index < DevInfo->HidReport.FieldCount; Index++) {
		Field = DevInfo->HidReport.Fields[Index];
		if (!(Field->Flag & HID_REPORT_FIELD_FLAG_INPUT)) {
			continue;
		}

		ReportId = Field->ReportId;
		ReportLen[ReportId] += Field->ReportCount * Field->ReportSize;
	}

	for (ReportId = 0; ReportId < COUNTOF(ReportLen); ReportId++) {
		if (ReportLen[ReportId] == 0) {
			continue;
		}

		Length = (ReportLen[ReportId] + 7) >> 3;
		if (ReportId != 0) {
			Length++;
		}

		MaxLength = MaxLength < Length ? Length : MaxLength;
	}

	return MaxLength;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       HidGetReportDescriptor
//
// Description: 
//
// intput:      
//              
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
HidGetReportDescriptor(
    HC_STRUC	*HcStruc,
    DEV_INFO	*DevInfo,
    HID_DESC	*HidDesc
)
{
	UINT8		*ReportDesc = NULL;
	UINT8		Index = 0;
	UINT8		Status = USB_ERROR;
	DEV_REQ		Request = {0};

	if (HidDesc == NULL) {
		return USB_ERROR;
	}

	if (HidDesc->bDescriptorLength == 0) {
		return USB_SUCCESS;
	}

    ReportDesc = USB_MemAlloc(GET_MEM_BLK_COUNT(HidDesc->bDescriptorLength));
	if (ReportDesc == NULL) {
		return USB_ERROR;
	}

	Request.wRequestType = HID_RQ_GET_DESCRIPTOR;
	Request.wValue = DESC_TYPE_REPORT << 8;
	Request.wIndex = DevInfo->bInterfaceNum;
	Request.wDataLength = HidDesc->bDescriptorLength;

	for (Index = 0; Index < 3; Index++) {
		Status = UsbControlTransfer(HcStruc, DevInfo, Request, USB_GET_REPORT_DESC_TIMEOUT_MS, ReportDesc);
		if (Status == USB_SUCCESS) {
			break;
		}
	}

    DevInfo->HidReport.ReportDescLen = HidDesc->bDescriptorLength ;		
	HidParseReportDescriptor(DevInfo, ReportDesc);
	DevInfo->PollingLength = CalculateInputReportDataLength(DevInfo);

    USB_MemFree(ReportDesc, GET_MEM_BLK_COUNT(HidDesc->bDescriptorLength));
	return USB_SUCCESS;
}
                                        //(EIP84455+)>

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       USBHIDProcessData
//
// Description: 
//
// intput:      
//              
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END> 

UINT8
USBHIDProcessData(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Td,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UINT8               DataType = 0;
    UINT8               i;
    UINT16              j;
	HID_REPORT_FIELD 	*Field = NULL;

    DataType = DevInfo->bProtocol;

	if (DevInfo->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
		for (i = 0; i < DevInfo->HidReport.FieldCount; i++) {
			Field = DevInfo->HidReport.Fields[i];

			//Check is input?
			if (!(Field->Flag & HID_REPORT_FIELD_FLAG_INPUT)) {
				continue;
			}
			//if report id exist, check first byte
			if (Field->ReportId != 0 && Field->ReportId != Buffer[0]) {
				continue;
			}

            if (Field->UsagePage == 7) {
                DataType = HID_BTYPE_KEYBOARD;
            }
            //Check X,Y
            if ((Field->UsagePage == 1) && (Field->UsageCount != 0)) {
                for (j = 0; j < Field->UsageCount; j++) {
                //find X
                    if (Field->Usages[j] == 0x30) {
                        if (Field->Flag & HID_REPORT_FIELD_FLAG_RELATIVE) {
                            DataType = HID_BTYPE_MOUSE;
                        } else {
                            DataType = HID_BTYPE_POINT;
                        }
                    }

				}    
            }
		}
	}

    switch(DataType) {
        case HID_BTYPE_KEYBOARD:
            USBKBDProcessKeyboardData(HcStruc, DevInfo, Td, Buffer, DataLength);
            break;
        case HID_BTYPE_MOUSE:
            USBMSProcessMouseData(HcStruc, DevInfo, Td, Buffer, DataLength);
            break;
        case HID_BTYPE_POINT:
            USBAbsProcessMouseData(HcStruc, DevInfo, Td, Buffer, DataLength);
            break;          
        default:
            break;
    }
    return USB_SUCCESS; 
}
                                        //<(EIP84455+)

                                        //(EIP101990+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Input:       CheckInputMode
//
// Description: 
//
// intput:      
//              
// Output:     
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END> 
VOID
CheckInputMode(
	DEV_INFO			*DevInfo,
	HID_REPORT_FIELD	*Field
)
{
	HC_STRUC	*HcStruc = gUsbData->HcTable[DevInfo->bHCNumber - 1];
	DEV_REQ		Request = {0};
    UINT8		*Buffer;
	UINT16		Index;
    
    for (Index = 0; Index < Field->UsageCount; Index++) {
		if (Field->UsagePage == 0xd) {
        	if (Field->Usages[Index] == 0x52 && Field->Usages[Index + 1] == 0x53) {
				Request.wRequestType = HID_RQ_SET_REPORT;
				Request.wValue = (0x03 << 8) | Field->ReportId;
				Request.wIndex = DevInfo->bInterfaceNum;
				Request.wDataLength = 3;

				Buffer = USB_MemAlloc (1); 
				Buffer[0] = Field->ReportId;
				Buffer[1] = 2;
				Buffer[2] = 0;

				UsbControlTransfer(HcStruc, DevInfo, Request, 100, Buffer);

				USB_MemFree(Buffer, 1);
            	break;
        	}
        }
    }
}
                                        //<(EIP101990+)
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

