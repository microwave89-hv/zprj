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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbhid.c 17    5/28/15 5:01a Wilsonlee $
//
// $Revision: 17 $
//
// $Date: 5/28/15 5:01a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbhid.c $
// 
// 17    5/28/15 5:01a Wilsonlee
// [TAG]  		EIP218997
// [Category]  	Improvement
// [Description]  	Break the GetQueue loop if UninstallDevice is failed.
// [Files]  		usbbus.c, efiusbkb.c, efiusbmass.c, efiusbms.c,
// efiusbpoint.c, efiusbhid.c
// 
// 16    8/12/14 3:04a Wilsonlee
// [TAG]  		EIP180970
// [Category]  	Improvement
// [Description]  	Update X and Y data to usbmousedata and install
// SimplePointerProtocol interface if the mouses are using boot protocol
// interface.
// [Files]  		efiusbhid.c, usbms.c
// 
// 15    5/06/14 5:17a Ryanchou
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
// 14    10/19/13 7:08a Ryanchou
// [TAG]  		EIP138257
// [Category]  	Improvement
// [Description]  	Correct USB HID device type.
// [Files]  		amiusb.c, usbdef.h, usbhid.c, efiusbhid.c, uhcd.c
// 
// 13    7/24/13 2:31a Roberthsu
// [TAG]           EIP121333
// [Category]      Improvement
// [Description]   Multiple USB mouse support for UEFI USB mouse driver
// [Files]         efiusbhid.c,efiusbkb.h,efiusbms.c
// 
// 12    3/19/13 4:00a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 11    11/29/12 7:48a Ryanchou
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
// 10    11/10/12 6:41a Ryanchou
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
// 9     8/29/12 8:35a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 8     5/04/12 5:19a Roberthsu
// 
// 7     5/03/12 5:55a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 6     12/29/11 1:54a Deepthins
// [TAG]  		EIP77537
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Multiple USB keyboard are not synchronized properly
// [RootCause]  	In USB driver for the new Simpletextin ( USB keyboard)
// device, the memory allocated for the device is saved in gUsbKbd
// pointer. The same pointer is used when multiple simple text in device
// installed.
// [Solution]  	USB_KB_DEV structure is divided into 2 structure, one is
// common for all the Simpletextin and another structure is for specific
// to the SimpleTextin Device.Based on it, allocate the memory for
// structure and use it. When the stop function is called, we should free
// only the structure that is specific for device.
// 
// [Files]  		Efiusbkb.c, Efiusbhid.c, efiusbkb.c
// 
// 5     12/14/11 2:10a Ryanchou
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
// 4     10/24/11 8:31a Wilsonlee
// [TAG]  		EIP69250
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB driver doesn't pass SCT 2.3 ComponentName2 protocol.
// [RootCause]  	There is no checking if passed controller handle is NULL
// in AMIUSBComponentNameGetControllerName function.
// [Solution]  	Check controller handle is NULL in
// AMIUSBComponentNameGetControllerName function.
// [Files]  		componentname.c efiusbccid.c efiusbhid.c
// 
// 3     9/23/11 12:31a Rameshr
// [TAG]  		EIP63054
// [Category]  	New Feature
// [Description]  	0000790: Add warning to ReadKeyStrokeEx for partial key
// press
// [Files]  		KeyboardCommonDefinitions.h, In.c, Kbc.h, Ps2Kbd.c,
// Efiusbkb.c, efiusbkb.h, efiusbhid.c
// 
// 2     8/05/11 7:28a Ryanchou
// [TAG]  		EIP66231
// [Category]  	Improvement
// [Description]  	Remove token POINT_SUPPORT.Add token USB_DEV_POINT.Add
// check core version in point driver.Add check device descriptor to send
// get lang id command.Modify check button usage page.
// [Files]  		efiusbhid.c, efiusbpoint.c, usbbus.c, usbhid.c, usbpoint.c,
// usbsrc.sdl
// 
// 1     7/15/11 6:26a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, efiusbpoint.c, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c,
// usb.c, usbdef.h, usbhid.c, usbkbd.c, usbkbd.h, usbms.c, usbpoint.c,
// usbrt.cif, usbsb.c, usbsetup.c, usbsrc.sdl, xhci.c
// 
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           EfiUsbHid.C
//
//  Description:    EFI USB HID device Driver
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"
#include "efiusbkb.h"
#include "usbkbd.h"

#include "componentname.h"
#include "usbbus.h" 

extern  DLIST           mUsbKeyboardData;
extern  USB_GLOBAL_DATA *gUsbData; 
EFI_EVENT               UsbKeyEvent;
extern  USB_KEYBOARD_DATA*   gUsbKeyboardData;

#define AMI_HID_DEVICE_GUID \
	{0x1fede521, 0x31c, 0x4bc5, 0x80, 0x50, 0xf3, 0xd6, 0x16, 0x1e, 0x2e, 0x92}

EFI_GUID gAmiHidDeviceGuid = AMI_HID_DEVICE_GUID;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbHidGetControllerName
//
// Description: USB EFI keyboard driver driver protocol function that
//              returns the keyboard controller name.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16*
UsbHidGetControllerName(
    EFI_HANDLE Controller,
    EFI_HANDLE Child
)
{
    return NULL;
}
 

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbHidInit
//
// Description: HID EFI driver entry point
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbHidInit(
    EFI_HANDLE  ImageHandle,
    EFI_HANDLE  ServiceHandle
)
{
    EFI_STATUS        Status;
    static NAME_SERVICE_T Names;
    static EFI_DRIVER_BINDING_PROTOCOL Binding = {
        SupportedUSBHid,
        InstallUSBHid,
        UninstallUSBHid,
        USBKB_DRIVER_VERSION,
        NULL,
        NULL };

    Binding.DriverBindingHandle = ServiceHandle;
    Binding.ImageHandle = ImageHandle;

    DListInit(&mUsbKeyboardData);

    //
    // Create a event to Poll a key when there is RegisterKeyNotify
    //
    pBS->CreateEvent(
                    EVT_TIMER | EFI_EVENT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    StartPollingKey,
                    NULL,
                    &UsbKeyEvent
                    );
    
    InitUSBMouse(); 
    //
    // Allocate the memory for gUsbKeyboardData and calling InitUSBKeyboard
    // to initialize the USB keyboard.
    //
    Status = gBS->AllocatePool( EfiBootServicesData,sizeof(USB_KEYBOARD_DATA), &gUsbKeyboardData );
	ASSERT_EFI_ERROR(Status);
    EfiZeroMem(gUsbKeyboardData, sizeof(USB_KEYBOARD_DATA));
    Status = InitUSBKeyboard();

    return gBS->InstallMultipleProtocolInterfaces(
        &Binding.DriverBindingHandle,
        &gEfiDriverBindingProtocolGuid, &Binding,
        &gEfiComponentName2ProtocolGuid, InitNamesProtocol(&Names,	//(EIP69250)
              L"USB Hid driver", UsbHidGetControllerName),
        NULL);
}
 
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:      SupportedUSBHid
//
// Description: Verifies if usb hid support can be installed on a device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SupportedUSBHid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath)
{
    EFI_USB_INTERFACE_DESCRIPTOR    Desc;
    EFI_STATUS                      Status;
    EFI_USB_IO_PROTOCOL             *UsbIo;

    Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
        &UsbIo, This->DriverBindingHandle,
        Controller, EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    gBS->CloseProtocol ( Controller, &gEfiUsbIoProtocolGuid,
        This->DriverBindingHandle, Controller);

    Status = UsbIo->UsbGetInterfaceDescriptor(UsbIo, &Desc  );
    if(EFI_ERROR(Status))
        return EFI_UNSUPPORTED;

    if ( Desc.InterfaceClass == BASE_CLASS_HID)
    {
        return EFI_SUCCESS;
    } else {
        return EFI_UNSUPPORTED;
    }
} 

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InstallUSBHid
//
// Description: Installs SimpleTxtIn protocol on a given handle
//
// Input:       Controller - controller handle to install protocol on.
//
// Output:      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InstallUSBHid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
)
{
    EFI_STATUS              Status;
    EFI_USB_IO_PROTOCOL     *UsbIo;
	USBDEV_T* HidDev;
	HC_STRUC* HcData;
	UINT8 UsbStatus;
 
    USB_DEBUG(DEBUG_USBHC_LEVEL,
        "USB: InstallUSBHid: starting...\n");
    //
    // Open Protocols
    //
    Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
        &UsbIo, This->DriverBindingHandle,
        Controller, EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR(Status))
        return Status; 
	
	HidDev = UsbIo2Dev(UsbIo); 	
//Find DEV_INFO 
    ASSERT(HidDev);
    HcData = gUsbData->HcTable[HidDev->dev_info->bHCNumber - 1];
    UsbStatus = UsbSmiReConfigDevice(HcData, HidDev->dev_info); 
    if(UsbStatus != USB_SUCCESS) {
        USB_DEBUG(DEBUG_USBHC_LEVEL,
            "InstallUSBHid: failed to Reconfigure Hid: %d\n", UsbStatus );
		gBS->CloseProtocol (
			  Controller, &gEfiUsbIoProtocolGuid,
			  This->DriverBindingHandle, Controller);
        return EFI_DEVICE_ERROR;
    }

    Status = gBS->InstallMultipleProtocolInterfaces (&Controller,
                &gAmiHidDeviceGuid, NULL,
                NULL
                );
    
    if(HidDev->dev_info->HidDevType & HID_DEV_TYPE_KEYBOARD) {
	    InstallUSBKeyboard(This,Controller,DevicePath,HidDev->dev_info,UsbIo);
    }

    if (HidDev->dev_info->HidDevType & (HID_DEV_TYPE_MOUSE | HID_DEV_TYPE_POINT)) {
        if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
    		if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_RELATIVE_DATA) {
      			InstallUSBMouse(Controller, UsbIo, HidDev->dev_info);
    		}
#if USB_DEV_POINT 
    		if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_ABSOLUTE_DATA) {
    			InstallUSBAbsMouse(Controller, HidDev->dev_info);
    		}
#endif
        } else {
            InstallUSBMouse(Controller, UsbIo, HidDev->dev_info);
        }
    }
    return Status;

} 

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UninstallHid
//
// Description: Uninstalls protocol on a given handle
//
// Input:       Controller - controller handle.
//
// Output:      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UninstallUSBHid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
)
{
	EFI_STATUS				Status;
	EFI_USB_IO_PROTOCOL 	*UsbIo;
	VOID					*Ptr;
	UINT8		UsbSatus;
	USBDEV_T*	HidDev;
	HC_STRUC*	HcData;
 
	USB_DEBUG(DEBUG_USBHC_LEVEL,
		"\n USB: UnInstallUSBHid: stoping...\n");

	Status = gBS->OpenProtocol(Controller, &gAmiHidDeviceGuid,
		&Ptr, This->DriverBindingHandle, Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL );

	if (EFI_ERROR(Status)) {
		return Status; 
	}
	//
	// Open Protocols
	//
	Status = gBS->OpenProtocol(Controller, &gEfiUsbIoProtocolGuid,
		&UsbIo, This->DriverBindingHandle,
		Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL );
	if (EFI_ERROR(Status)) {
		return Status; 
	}

	HidDev = UsbIo2Dev(UsbIo);	
	HcData = gUsbData->HcTable[HidDev->dev_info->bHCNumber - 1];

	UsbSatus = UsbDevDriverDisconnect(HcData, HidDev->dev_info);
	ASSERT(UsbSatus == USB_SUCCESS);

	if (HidDev->dev_info->HidDevType & HID_DEV_TYPE_KEYBOARD) {
		Status = UninstallUSBKeyboard(This,Controller,NumberOfChildren,Children);
        if (EFI_ERROR(Status)) {
            return Status;
        }
	}

	if (HidDev->dev_info->HidDevType & (HID_DEV_TYPE_MOUSE | HID_DEV_TYPE_POINT)) {
        if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
    		if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_RELATIVE_DATA) {
    			Status = UninstallUSBMouse(This, Controller, NumberOfChildren, Children);
                if (EFI_ERROR(Status)) {
                    return Status;
                }
    		}
#if USB_DEV_POINT 
    		if (HidDev->dev_info->HidReport.Flag & HID_REPORT_FLAG_ABSOLUTE_DATA) {
    			Status = UninstallUSBAbsMouse(Controller);
                if (EFI_ERROR(Status)) {
                    return Status;
                }
    		}
#endif
        } else {
            Status = UninstallUSBMouse(This, Controller, NumberOfChildren, Children);
            if (EFI_ERROR(Status)) {
                return Status;
            }
        }
	}

	Status = gBS->UninstallMultipleProtocolInterfaces (Controller,
				&gAmiHidDeviceGuid, NULL, 
				NULL);

	if (EFI_ERROR(Status)) {
		return Status;
	}
	//Close usbio protocol
    Status = gBS->CloseProtocol(Controller, &gEfiUsbIoProtocolGuid,
    			This->DriverBindingHandle, Controller); 

 	return Status;
}

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
