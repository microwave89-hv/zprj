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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbccid.c 9     10/16/16 10:18p Wilsonlee $
//
// $Revision: 9 $
//
// $Date: 10/16/16 10:18p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbccid.c $
// 
// 9     10/16/16 10:18p Wilsonlee
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
// 8     7/07/16 1:12a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 7     3/19/13 4:00a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 6     1/23/13 4:39a Wilsonlee
// [TAG]  		EIP109538
// [Category]  	Improvement
// [Description]  	Fix the code check error result.
// [Files]  		usbkbd.c, usbCCID.c, usbbus.c, efiusbccid.c
// 
// 5     8/29/12 8:35a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 4     5/02/12 2:01a Rajeshms
// [TAG]  		EIP83117
// [Category]  	Improvement
// [Description]  	Extend the Support to different smart card Readers and
// smart Cards.
// [Files]  		usbCCID.c, amiusbrtCCID.h, usbdef.h, efiusbccid.c,
// AmiusbCCID.h
// 
// 3     10/24/11 8:30a Wilsonlee
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
// 2     10/14/11 4:56a Rajeshms
// [TAG]  		EIP70315
// [Category]  	Improvement
// [Description]  	Removed Slot number in the USB CCID API's
// [Files]  		efiusbccid.c, AmiUsbCCID.h
// 
// 1     7/12/11 8:14a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
//****************************************************************************

//****************************************************************************
//<AMI_FHDR_START>
//
//  Name:           EfiUsbccid.c
//
//  Description:    USB CCID EFI driver implementation
//
//<AMI_FHDR_END>
//****************************************************************************

#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"
#include "componentname.h"
#include "usbbus.h"
#include "amidxelib.h"

extern  USB_GLOBAL_DATA *gUsbData;

EFI_STATUS
SupportedUSBCCID(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
);

EFI_STATUS
StartUSBCCID(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
);

EFI_STATUS
StopUSBCCID(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
);

EFI_STATUS
GetReturnValue(
    UINT8    bRetValue
);

ICC_DEVICE*
GetICCDevice(
    DEV_INFO        *fpDevInfo, 
    UINT8            Slot
);

EFI_STATUS
USBCCIDAPISmartClassDescriptor (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *ResponseBuffer
);

EFI_STATUS
USBCCIDAPIGetAtr (
    IN AMI_CCID_IO_PROTOCOL *This,
    UINT8 Slot,
    UINT8 *ATRData
);

EFI_STATUS
USBCCIDAPIPowerupSlot (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *bStatus,
    OUT UINT8                           *bError,
    OUT UINT8                           *ATRData
);

EFI_STATUS
USBCCIDAPIPowerDownSlot (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *bStatus,
    OUT UINT8                           *bError
);

EFI_STATUS
USBCCIDAPIGetSlotStatus (
    IN AMI_CCID_IO_PROTOCOL              *This,
    OUT UINT8                            *bStatus,
    OUT UINT8                            *bError,
    OUT UINT8                            *bClockStatus

);

EFI_STATUS
USBCCIDAPIXfrBlock (
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINTN                            CmdLength,
    IN UINT8                            *CmdBuffer,
    IN UINT8                            ISBlock,
    OUT UINT8                           *bStatus,
    OUT UINT8                           *bError,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                           *ResponseBuffer
);

EFI_STATUS
USBCCIDAPIGetParameters (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *bStatus,
    OUT UINT8                           *bError,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                           *ResponseBuffer
);

EFI_GUID gAmiCCIDIoProtocolGuid = AMI_CCID_IO_PROTOCOL_GUID;
EFI_GUID gAmiCCIDPresenceGuid = AMI_CCID_PRESENCE_GUID;

EFI_EVENT       gEvICCEnumTimer = 0;
UINTN           gCounterCCIDEnumTimer = 0;
UINTN           gICCLock = 0;

#define    USBCCID_DRIVER_VERSION        1

NAME_SERVICE_T Names;

EFI_DRIVER_BINDING_PROTOCOL CcidBindingProtocol = {
        SupportedUSBCCID,
        StartUSBCCID,
        StopUSBCCID,
        USBCCID_DRIVER_VERSION,
        NULL,
        NULL 
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InstallUSBCCID
//
// Description: Install AMI_CCID_IO_PROTOCOL_GUID for each slot
//
// Input:
//              EFI_HANDLE      CCIDHandle
//              DEV_INFO        *fpCCIDDevice
//              ICC_DEVICE      *fpICCDevice
//
// Output:
//              EFI_STATUS
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InstallUSBCCID(
    EFI_HANDLE      CCIDHandle,
    DEV_INFO        *fpCCIDDevice, 
    ICC_DEVICE      *fpICCDevice
)
{

    EFI_STATUS                  Status = EFI_INVALID_PARAMETER;
    USB_ICC_DEV                 *ICCDev;
    EFI_USB_IO_PROTOCOL         *UsbIo;

    USB_DEBUG(DEBUG_LEVEL_USBBUS, "InstallUSBCCID ....\n" );

    //
    // Install Protocol irrespective of device found or not. 
    // By checking ChildHandle here, avoid repeated protocol installation.
    //

    if (fpICCDevice && !fpICCDevice->ChildHandle) {
    
        gBS->AllocatePool(EfiBootServicesData, sizeof(USB_ICC_DEV), &ICCDev);
        ICCDev->ChildHandle = 0;
        ICCDev->ControllerHandle = 0;
        ICCDev->DevInfo    = fpCCIDDevice;
        ICCDev->Slot       = fpICCDevice->Slot;


        ICCDev->CCIDIoProtocol.USBCCIDAPISmartClassDescriptor = USBCCIDAPISmartClassDescriptor;
        ICCDev->CCIDIoProtocol.USBCCIDAPIGetAtr = USBCCIDAPIGetAtr;
        ICCDev->CCIDIoProtocol.USBCCIDAPIPowerupSlot = USBCCIDAPIPowerupSlot;
        ICCDev->CCIDIoProtocol.USBCCIDAPIPowerDownSlot = USBCCIDAPIPowerDownSlot;
        ICCDev->CCIDIoProtocol.USBCCIDAPIGetSlotStatus = USBCCIDAPIGetSlotStatus;
        ICCDev->CCIDIoProtocol.USBCCIDAPIXfrBlock = USBCCIDAPIXfrBlock;
        ICCDev->CCIDIoProtocol.USBCCIDAPIGetParameters = USBCCIDAPIGetParameters;
    
        Status = gBS->InstallProtocolInterface(
                        &ICCDev->ChildHandle,
                        &gAmiCCIDIoProtocolGuid,
                        EFI_NATIVE_INTERFACE,
                        &ICCDev->CCIDIoProtocol
                        );

        ASSERT_EFI_ERROR(Status);

        fpICCDevice->ChildHandle = ICCDev->ChildHandle;

        USB_DEBUG(DEBUG_LEVEL_3, "ICCDev->ChildHandle = %x\n", ICCDev->ChildHandle);

        Status = gBS->OpenProtocol (
                        CCIDHandle,
                        &gEfiUsbIoProtocolGuid,
                        &UsbIo,
                        CcidBindingProtocol.DriverBindingHandle,
                        ICCDev->ChildHandle,
                        EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );
    
        USB_DEBUG(DEBUG_LEVEL_3, "Install CCID on %x status = %r\n", CCIDHandle, Status);
        ASSERT_EFI_ERROR(Status);

    }

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UnInstallUSBCCID
//
// Description: Uninstall AMI_CCID_IO_PROTOCOL_GUID for each slot
//
// Input:
//    EFI_HANDLE    CCIDHandle - SmartCard Reader Handle
//    EFI_HANDLE    ChildHandle - Smart Card Handle
//
// output:
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UnInstallUSBCCID (
    EFI_HANDLE    CCIDHandle,
    EFI_HANDLE    ChildHandle
)
{

    EFI_STATUS                Status;
    AMI_CCID_IO_PROTOCOL      *CCIDIoProtocol;

    USB_DEBUG(DEBUG_LEVEL_USBBUS, "UnInstallUSBCCID ....\n" );

    Status = gBS->OpenProtocol ( ChildHandle, 
                                &gAmiCCIDIoProtocolGuid, 
                                &CCIDIoProtocol, 
                                CcidBindingProtocol.DriverBindingHandle, 
                                ChildHandle, 
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    //
    // CCID protocol not found on ChildHandle. return with error.
    //
    if(EFI_ERROR(Status)) {
        return Status;
    }

    //
    // If CCID protocol Found, close the protocol and uninstall the protocol interface.
    //
    Status = gBS->CloseProtocol (CCIDHandle, 
                                &gEfiUsbIoProtocolGuid, 
                                CcidBindingProtocol.DriverBindingHandle, 
                                ChildHandle);

    Status = pBS->UninstallProtocolInterface (  ChildHandle, 
                                                &gAmiCCIDIoProtocolGuid, 
                                                CCIDIoProtocol);
    
    if(!EFI_ERROR(Status)){
        gBS->FreePool(CCIDIoProtocol);
    }

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBCCIDAPISmartClassDescriptor
//
// Description: Generates a SW SMI to get the SMART Class Descriptor for the CCID device
//
// Input:
//              IN AMI_CCID_IO_PROTOCOL *This
//              OUT UINT8                *ResponseBuffer
//
// Output:
//              EFI_STATUS and returns SMART Class Descriptor in ResponseBuffer
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
USBCCIDAPISmartClassDescriptor(
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *ResponseBuffer
)
{

    EFI_STATUS              Status;
    URP_STRUC               Parameters = { 0 };

    Parameters.bFuncNumber = USB_API_CCID_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_CCID_SMARTCLASSDESCRIPTOR;

    Parameters.ApiData.CCIDSmartClassDescriptor.fpDevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    Parameters.ApiData.CCIDSmartClassDescriptor.Slot = ((USB_ICC_DEV *)This)->Slot;
    Parameters.ApiData.CCIDSmartClassDescriptor.fpResponseBuffer = (UINTN)ResponseBuffer;

    InvokeUsbApi(&Parameters);

    Status = GetReturnValue(Parameters.bRetValue);

    return Status;

}

//---------------------------------------------------------------------------
//
// Name:        USBCCIDAPIGetAtr
//
// Description: Generates a SW SMI to get the ATR data
//
// Input:
//              IN AMI_CCID_IO_PROTOCOL *This
//              IN UINT8                Slot,
//              OUT UINT8               *ATRData
//
// Output:
//  EFI_STATUS and returns  ATR data if available
//
// Notes:
//      ATRData buffer length should be 32 bytes long. Caller should allocate 
//      memory for *ATRData. 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
USBCCIDAPIGetAtr (
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINT8                            Slot,
    OUT UINT8                           *ATRData
)
{

    EFI_STATUS  Status;
    URP_STRUC   Parameters = { 0 };

    Parameters.bFuncNumber = USB_API_CCID_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_CCID_ATR;

    Parameters.ApiData.CCIDAtr.fpDevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    Parameters.ApiData.CCIDAtr.Slot = ((USB_ICC_DEV *)This)->Slot;
    Parameters.ApiData.CCIDAtr.ATRData = (UINTN)ATRData;

    InvokeUsbApi(&Parameters);

    Status = GetReturnValue(Parameters.bRetValue);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBCCIDAPIPowerupSlot
//
// Description: Generates a SW SMI to power up the slot in CCID
//
// Input:
//              IN AMI_CCID_IO_PROTOCOL               *This,
//              IN UINT8                              Slot,    
//              OUT UINT8                             *bStatus,
//              OUT UINT8                             *bError,
//              OUT UINT8                             *ATRData
//
// Output:
//              EFI_STATUS and returns  ATR data if Card powered up successfully.
//
// Notes:
//              ATRData buffer length should be 32 bytes long. Caller should allocate memory for *ATRData. 
//              Presence/Absence of card can be determined from *bStatus/*bError.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
USBCCIDAPIPowerupSlot (
    IN AMI_CCID_IO_PROTOCOL                 *This,
    OUT UINT8                               *bStatus,
    OUT UINT8                               *bError,
    OUT UINT8                               *ATRData
)
{

    EFI_STATUS              Status;
    URP_STRUC               Parameters = { 0 };

    Parameters.bFuncNumber = USB_API_CCID_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_CCID_POWERUP_SLOT;

    Parameters.ApiData.CCIDPowerupSlot.fpDevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    Parameters.ApiData.CCIDPowerupSlot.Slot = ((USB_ICC_DEV *)This)->Slot;
    Parameters.ApiData.CCIDPowerupSlot.ATRData = (UINTN)ATRData;

	InvokeUsbApi(&Parameters);

    *bStatus = Parameters.ApiData.CCIDPowerupSlot.bStatus; 
    *bError = Parameters.ApiData.CCIDPowerupSlot.bError;

    Status = GetReturnValue(Parameters.bRetValue);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBCCIDAPIPowerDownSlot
//
// Description: Generates a SW SMI to power down the slot in CCID.
//
// Input:
//              IN AMI_CCID_IO_PROTOCOL             *This,
//              IN UINT8                            Slot,
//              OUT UINT8                           *bStatus,
//              OUT UINT8                           *bError,
//
// Output:
//              EFI_STATUS 
//
// Notes:
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
USBCCIDAPIPowerDownSlot (
    IN AMI_CCID_IO_PROTOCOL                 *This,
    OUT UINT8                               *bStatus,
    OUT UINT8                               *bError
)
{

    EFI_STATUS              Status;
    URP_STRUC               Parameters = { 0 };

    Parameters.bFuncNumber = USB_API_CCID_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_CCID_POWERDOWN_SLOT;

    Parameters.ApiData.CCIDPowerdownSlot.fpDevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    Parameters.ApiData.CCIDPowerdownSlot.Slot = ((USB_ICC_DEV *)This)->Slot;

	InvokeUsbApi(&Parameters);

    *bStatus = Parameters.ApiData.CCIDPowerdownSlot.bStatus; 
    *bError = Parameters.ApiData.CCIDPowerdownSlot.bError;

    Status = GetReturnValue(Parameters.bRetValue);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBCCIDAPIGetSlotStatus
//
// Description: This API returns data from RDR_to_PC_SlotStatus
//
// Input:
//              IN AMI_CCID_IO_PROTOCOL             *This
//              OUT UINT8                           *bStatus
//              OUT UINT8                           *bError
//              OUT UINT8                           *bClockStatus
//
// Output:
//              OUT UINT8                            *bStatus - Sec 6.2.6 if CCID spec ver 1.2
//              OUT UINT8                            *bError - Sec 6.2.6 if CCID spec ver 1.2
//              OUT UINT8                            *bClockStatus
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
USBCCIDAPIGetSlotStatus (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *bStatus,
    OUT UINT8                           *bError,
    OUT UINT8                           *bClockStatus

)
{

    EFI_STATUS              Status;
    URP_STRUC               Parameters = { 0 };

    Parameters.bFuncNumber = USB_API_CCID_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_CCID_GET_SLOT_STATUS;

    Parameters.ApiData.CCIDGetSlotStatus.fpDevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    Parameters.ApiData.CCIDGetSlotStatus.Slot = ((USB_ICC_DEV *)This)->Slot;

	InvokeUsbApi(&Parameters);

    *bStatus = Parameters.ApiData.CCIDGetSlotStatus.bStatus; 
    *bError = Parameters.ApiData.CCIDGetSlotStatus.bError;
    *bClockStatus = Parameters.ApiData.CCIDGetSlotStatus.bClockStatus;

    Status = GetReturnValue(Parameters.bRetValue);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBCCIDAPIXfrBlock
//
// Description: This API generates a SWSMI to execute the USB_CCID_XFRBLOCK API.
//
// Input:
//              IN AMI_CCID_IO_PROTOCOL     *This
//              IN UINTN                    CmdLength - Length of CmdBuffer
//              IN UINT8                    *CmdBuffer - Buffer prepared to be sent to ICC through PC_TO_RDR_XFRBLOCK cmd
//              IN UINT8                    ISBlock  - Valid only in T1 TDPU        
//              OUT UINT8                   *bStatus
//              OUT UINT8                   *bError
//              IN OUT UINTN                *ResponseLength - Lenght of the Responsebuffer
//              OUT UINT8                   *ResponseBuffer
// 
// Output: 
//              EFI_STATUS
//              OUT UINT8                   *bStatus - Sec 6.2.6 if CCID spec ver 1.2 
//              OUT UINT8                   *bError - Sec 6.2.6 if CCID spec ver 1.2
//              IN OUT UINTN                *ResponseLength - Actual number of Bytes returned in ResponseBuffer
//              OUT UINT8                   *ResponseBuffer - Response bytes
//
// Notes:
//       ISBlock is valid only for T1. For updating IFS use S_IFS_REQUEST(0xC1).
//       For WTX request use S_WTX_REQUEST (0xC3). For all others use I_BLOCK(0x0)
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
USBCCIDAPIXfrBlock (
    IN AMI_CCID_IO_PROTOCOL                *This,
    IN UINTN                            CmdLength,
    IN UINT8                            *CmdBuffer,
    IN UINT8                             ISBlock,
    OUT UINT8                            *bStatus,
    OUT UINT8                            *bError,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                            *ResponseBuffer
)
{

    EFI_STATUS              Status;
    URP_STRUC               Parameters = { 0 };

    Parameters.bFuncNumber = USB_API_CCID_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_CCID_XFRBLOCK;
    Parameters.ApiData.CCIDXfrBlock.CmdLength = CmdLength;
    Parameters.ApiData.CCIDXfrBlock.fpCmdBuffer = (UINT32)(UINTN)CmdBuffer;
    Parameters.ApiData.CCIDXfrBlock.ISBlock = I_BLOCK;
    Parameters.ApiData.CCIDXfrBlock.ResponseLength = *ResponseLength;
    Parameters.ApiData.CCIDXfrBlock.fpResponseBuffer = (UINTN)ResponseBuffer;

    Parameters.ApiData.CCIDXfrBlock.fpDevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    Parameters.ApiData.CCIDXfrBlock.Slot = ((USB_ICC_DEV *)This)->Slot;

 	InvokeUsbApi(&Parameters);

    *bStatus = Parameters.ApiData.CCIDXfrBlock.bStatus ;
    *bError = Parameters.ApiData.CCIDXfrBlock.bError;
    *ResponseLength = Parameters.ApiData.CCIDXfrBlock.ResponseLength;

    Status = GetReturnValue(Parameters.bRetValue);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBCCIDAPIGetParameters
//
// Description: Returns data from PC_TO_RDR_GETPARAMETERS/RDR_to_PCParameters cmd
//
// Input:
//              IN AMI_CCID_IO_PROTOCOL         *This,
//              OUT UINT8                       *bStatus,
//              OUT UINT8                       *bError,
//              IN OUT UINTN                    *ResponseLength,
//              OUT UINT8                       *ResponseBuffer
//
// Output:
//              IN AMI_CCID_IO_PROTOCOL         *This,
//              OUT UINT8                       *bStatus,
//              OUT UINT8                       *bError,
//              IN OUT UINTN                    *ResponseLength,
//              OUT UINT8                       *ResponseBuffer
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
USBCCIDAPIGetParameters (
    IN AMI_CCID_IO_PROTOCOL                *This,
    OUT UINT8                            *bStatus,
    OUT UINT8                            *bError,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                            *ResponseBuffer
)
{

    EFI_STATUS              Status;
    URP_STRUC               Parameters = { 0 };

    Parameters.bFuncNumber = USB_API_CCID_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_CCID_GET_PARAMETERS;
    Parameters.ApiData.CCIDGetParameters.ResponseLength = *ResponseLength;
    Parameters.ApiData.CCIDGetParameters.fpResponseBuffer = (UINT32)(UINTN)ResponseBuffer;

    Parameters.ApiData.CCIDGetParameters.fpDevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    Parameters.ApiData.CCIDGetParameters.Slot = ((USB_ICC_DEV *)This)->Slot;

	InvokeUsbApi(&Parameters);

    *bStatus = Parameters.ApiData.CCIDGetParameters.bStatus ;
    *bError = Parameters.ApiData.CCIDGetParameters.bError;
    *ResponseLength = Parameters.ApiData.CCIDGetParameters.ResponseLength;

    Status = GetReturnValue(Parameters.bRetValue);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        GetICCDevice
//
// Description: Search the linked list to find the ICC_DEVICE for the given slot #.
//
// Input:
//              DEV_INFO        *fpDevInfo, 
//              UINT8            Slot
//
// Output:
//              ICC_DEVICE Pointer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
ICC_DEVICE*
GetICCDevice(
    DEV_INFO        *fpDevInfo, 
    UINT8            Slot
)
{

    ICC_DEVICE        *fpICCDevice;
    DLINK           *dlink;

    dlink = fpDevInfo->ICCDeviceList.pHead;

    for ( ; dlink; dlink = dlink->pNext) {

        fpICCDevice = OUTTER(dlink, ICCDeviceLink, ICC_DEVICE);

        //
        // Slot # matches
        //
        if (fpICCDevice->Slot == Slot) {
            return fpICCDevice;
        }      
          
    }

    //
    // No Device Found. Return with NULL pointer
    //
    return NULL;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        GetCCIDDevice
//
// Description: Search the linked list to find the CCID Device for the given ICC
//
// Input:
//              ICC_DEVICE  *fpICCDevice
//
// Output:
//              DEV_INFO Pointer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
DEV_INFO*
GetCCIDDevice(
    ICC_DEVICE        *fpICCDevice
)
{


    DEV_INFO        *fpCCIDDevice;
    ICC_DEVICE      *fpTempICCDevice;
    DLINK           *dlink;
    UINTN           i;

    for (i = 0; i < MAX_DEVICES; i++ ){

        fpCCIDDevice = &(gUsbData->aDevInfoTable[i]);
        
        //
        // If not a CCID device continue the loop
        //
        if (!(fpCCIDDevice->bDeviceType == BIOS_DEV_TYPE_CCID)) continue;

        dlink = fpCCIDDevice->ICCDeviceList.pHead;

        for ( ; dlink; dlink = dlink->pNext) {
    
            fpTempICCDevice = OUTTER(dlink, ICCDeviceLink, ICC_DEVICE);

            //    
            // Match found?
            //
            if (fpICCDevice == fpTempICCDevice) {
                return fpCCIDDevice;
            }      
          
        }

    }

    //
    // Device Not Found, Return with NULL
    //
    return NULL;
}


//---------------------------------------------------------------------------
//
// Name:        GetReturnValue
//
// Description: Convert CCID return Value to EFI_STATUS
//
// Input:
//              UINT8    bRetValue
//
// Output:
//              EFI_STATUS - Return the EFI Status
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetReturnValue(
    UINT8    bRetValue
)
{
    EFI_STATUS    Status;

    switch (bRetValue) {

            case USB_SUCCESS:
                Status = EFI_SUCCESS;
                break;

            default:
                Status = EFI_DEVICE_ERROR;
    }

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        ICCOnTimer
//
// Description: Timer call-back routine that is used to monitor insertion/removal 
//              of ICC(Smart card) in the smart card reader.
//
// Input:
//              EFI_EVENT   Event,
//              VOID        *Context
//
// Output:
//              None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ICCOnTimer(
    EFI_EVENT   Event,
    VOID        *Context
)
{
    ICC_DEVICE        *fpICCDevice = NULL;
    DEV_INFO        *fpCCIDDevice; 
    UINTN              Lock;
    EFI_HANDLE        CCIDHandle;

    ATOMIC({Lock = gICCLock; gICCLock=1;});

    if( Lock ){
        USB_DEBUG(DEBUG_LEVEL_USBBUS, "ICCOnTimer::  is locked; return\n" );
        return;
    }

    do {

        ATOMIC({fpICCDevice = (ICC_DEVICE *)QueueGet(&gUsbData->ICCQueueCnnctDisc);});

        if (fpICCDevice == NULL) { 
            break;
        }

        fpCCIDDevice = GetCCIDDevice(fpICCDevice);

        if (!fpCCIDDevice) {
            continue;
        }

        CCIDHandle = (EFI_HANDLE) *(UINTN*)fpCCIDDevice->Handle;

        USB_DEBUG(DEBUG_LEVEL_3, "Controller %x\n", CCIDHandle);
        USB_DEBUG(DEBUG_LEVEL_3, "Insert/Removal: fpDevInfo %x fpICCDevice %x\n", fpCCIDDevice, fpICCDevice);

#if CCID_USE_INTERRUPT_INSERTION_REMOVAL
        if (fpICCDevice->ConfiguredStatus & ICCPRESENT) {
            //
            // Install EFI interface to communicate with Smart Card/CCID
            //
            InstallUSBCCID(CCIDHandle, fpCCIDDevice, fpICCDevice);
        }
        else{
            //
            // Device Removed. Uninstall the existing Device
            //
             UnInstallUSBCCID (CCIDHandle, fpICCDevice->ChildHandle);
        }
#else
        InstallUSBCCID(CCIDHandle, fpCCIDDevice, fpICCDevice);     
#endif

    } while ( 1 );

    gICCLock = 0;

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        SupportedUSBCCID
//
// Description: Verifies if usb CCID support can be installed on a device
//
// Input:
//              IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to driver binding protocol
//              IN EFI_HANDLE ControllerHandle - controller handle to install driver on
//              IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath - pointer to device path
//
// Output:
//      EFI_STATUS
//              EFI_SUCCESS - driver supports given controller
//              EFI_UNSUPPORTED - driver doesn't support given controller
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SupportedUSBCCID(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
)
{
    EFI_USB_INTERFACE_DESCRIPTOR    Desc;
    EFI_STATUS                      Status;
    EFI_USB_IO_PROTOCOL             *UsbIo;

    Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
                                &UsbIo, This->DriverBindingHandle,
                                Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL 
                                );

    if( EFI_ERROR(Status)) {
        return Status;
    }

    Status = UsbIo->UsbGetInterfaceDescriptor(UsbIo, &Desc);

    if(EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

    if ( Desc.InterfaceClass == BASE_CLASS_CCID_STORAGE &&
        Desc.InterfaceSubClass == SUB_CLASS_CCID &&
        Desc.InterfaceProtocol == PROTOCOL_CCID) {
        return EFI_SUCCESS;
    } else {
        return EFI_UNSUPPORTED;
    }

    return EFI_UNSUPPORTED;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        StartUSBCCID
//
// Description: Installs CCID protocol on a given handle
//
// Input:   
//              IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to driver binding protocol
//              IN EFI_HANDLE ControllerHandle - controller handle to install driver on
//              IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath - pointer to device path
//
// Output:
//              EFI_STATUS
//                      EFI_SUCCESS - driver started successfully
//                      EFI_UNSUPPORTED - driver didn't start
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
StartUSBCCID(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
)
{
    EFI_STATUS              Status;
    EFI_USB_IO_PROTOCOL     *UsbIo;

    USB_DEBUG(DEBUG_USBHC_LEVEL,
        "USB: installUSBCCID: starting...\n");

    //
    // Open Protocols
    //
    //ALREADY_STARTED is a normal condition
    Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
                                &UsbIo, This->DriverBindingHandle,
                                Controller, EFI_OPEN_PROTOCOL_BY_DRIVER );
    if( EFI_ERROR(Status)) {
        return Status;
    }

    {
        USBDEV_T* CCIDDev = UsbIo2Dev(UsbIo);
        HC_STRUC* HcData;
        UINT8 UsbStatus;

        ASSERT(CCIDDev);
        HcData = gUsbData->HcTable[CCIDDev->dev_info->bHCNumber - 1];
        UsbStatus = UsbSmiReConfigDevice(HcData, CCIDDev->dev_info);

        if(UsbStatus != USB_SUCCESS) {
            USB_DEBUG(DEBUG_USBHC_LEVEL,
                "installUSBCCID: failed to Reconfigure KBD: %d\n", UsbStatus );

            return EFI_DEVICE_ERROR;
        }

        //
        // Install AMI CCID Presence protocol to identify SMART Card reader is detected
        //
        Status = gBS->InstallProtocolInterface(
                            &Controller,
                            &gAmiCCIDPresenceGuid,
                            EFI_NATIVE_INTERFACE,
                            NULL
                            );

        ASSERT_EFI_ERROR(Status);

        //
        // Setting up Timer to to detect ICC card insertion removal 
        //
        gCounterCCIDEnumTimer++;
        if (gEvICCEnumTimer == 0) {
            USB_DEBUG(DEBUG_LEVEL_USBBUS, "USBBUS: Start: setup timer callback %x\n", &ICCOnTimer );
            VERIFY_EFI_ERROR(
                gBS->CreateEvent ( EFI_EVENT_TIMER | EFI_EVENT_NOTIFY_SIGNAL,
                                    EFI_TPL_CALLBACK, ICCOnTimer,0,&gEvICCEnumTimer));
                VERIFY_EFI_ERROR(
                    gBS->SetTimer ( gEvICCEnumTimer, TimerPeriodic, MILLISECOND));
        }

    }

    USB_DEBUG(DEBUG_USBHC_LEVEL,
        "USB: installCCID: done (%x).\n", Status);


    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        StopSBCCID
//
// Description: Uninstalls CCID protocol on a given handle
//
// Input:   
//              IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to driver binding protocol
//              IN EFI_HANDLE ControllerHandle - controller handle to install driver on
//              IN UINTN NumberOfChildren - number of childs on this handle
//              IN OPTIONAL EFI_HANDLE *ChildHandleBuffer - pointer to child handles array
//
// Output:
//              EFI_STATUS
//                  EFI_SUCCESS - driver stopped successfully
//                  EFI_INVALID_PARAMETER - invalid values passed for NumberOfChildren or
//                                  ChildHandleBuffer
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
StopUSBCCID(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
)
{

    EFI_STATUS Status;

    if (!NumberOfChildren) {

        // Closer the timer event when all CCID devices have been stopped
        if(--gCounterCCIDEnumTimer==0){

            VERIFY_EFI_ERROR(gBS->SetTimer ( gEvICCEnumTimer, TimerCancel, ONESECOND));
            VERIFY_EFI_ERROR(gBS->CloseEvent (gEvICCEnumTimer));
            gEvICCEnumTimer=0;

        }

        //
        // uninstall gAmiCCIDPresenceGuid 
        //
        Status = pBS->UninstallProtocolInterface ( Controller, 
                                                &gAmiCCIDPresenceGuid, 
                                                NULL);

        Status = gBS->CloseProtocol (Controller, 
                                    &gEfiUsbIoProtocolGuid, 
                                    This->DriverBindingHandle, 
                                    Controller);
        ASSERT_EFI_ERROR(Status);

    }

    while (NumberOfChildren){

        //
        // Uninstall AMI_CCID_IO_PROTOCOL for each slot
        //
        Status = UnInstallUSBCCID (Controller, Children[NumberOfChildren -  1]);
        ASSERT_EFI_ERROR(Status);
        NumberOfChildren--;

    }

    return Status;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbCCIDGetControllerName
//
// Description: Returns the Controller Name 
//
// Input:
//              EFI_HANDLE Controller,
//              EFI_HANDLE Child
//
// Output:
//              CHAR16* - Pointer to the buffer
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16*
UsbCCIDGetControllerName(
    EFI_HANDLE Controller,
    EFI_HANDLE Child
)
{
    return NULL;
}
 

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbCCIDInit
//
// Description: CCID driver entry point
//
// Input:
//              EFI_HANDLE  ImageHandle,
//              EFI_HANDLE  ServiceHandle
//
// Output:
//              EFI_STATUS - Efi Status.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbCCIDInit(
    EFI_HANDLE  ImageHandle,
    EFI_HANDLE  ServiceHandle
)
{

    CcidBindingProtocol.DriverBindingHandle = ServiceHandle;
    CcidBindingProtocol.ImageHandle = ImageHandle;

    USB_DEBUG(DEBUG_LEVEL_3, "USB CCID binding:\n\t");
    USB_DEBUG(DEBUG_LEVEL_3, "SupportedUSBCCID:%x\n", &SupportedUSBCCID );
    USB_DEBUG(DEBUG_LEVEL_3, "\tInstallUSBCCID:%x\n", &StartUSBCCID);
    USB_DEBUG(DEBUG_LEVEL_3, "\tUninstallUSBCCID:%x\n", &StopUSBCCID );

    return gBS->InstallMultipleProtocolInterfaces(
        &CcidBindingProtocol.DriverBindingHandle,
        &gEfiDriverBindingProtocolGuid, &CcidBindingProtocol,
        &gEfiComponentName2ProtocolGuid, InitNamesProtocol(&Names,	//(EIP69250)
              L"AMI USB CCID driver", UsbCCIDGetControllerName),
        NULL);
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
