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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbCCID.c 19    10/16/16 10:12p Wilsonlee $
//
// $Revision: 19 $
//
// $Date: 10/16/16 10:12p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
//
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbCCID.c $
// 
// 19    10/16/16 10:12p Wilsonlee
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
// 18    7/07/16 1:09a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 17    3/02/16 9:41p Wilsonlee
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
// 16    4/10/15 3:10a Wilsonlee
// [TAG]  		EIP207413
// [Category]  	Improvement
// [Description]  	Install UsbApiTable and UsbMassApitTable in
// AmiUsbSmmProtocol.
// [Files]  		amiusbhc.c, AmiUsbController.h, usbdef.h, usbCCID.c, uhci.c,
// ehci.c, amiusbrtCCID.h, amiusb.h, amiusb.c, uhcd.c
// 
// 15    3/05/15 3:54a Wilsonlee
// [TAG]  		EIP203888
// [Category]  	Improvement
// [Description]  	RateAndProtocolManagement() default return changed from
// EFI_DEVICE_ERROR to EFI_SUCCESS.
// [Files]  		usbCCID.c
// 
// 14    2/16/15 2:45a Wilsonlee
// [TAG]  		EIP205373
// [Category]  	Improvement
// [Description]  	Cppcheck errors in Usb module.
// [Files]  		usb.c, usbport.c, uhcd.c, usbCCID.c
// 
// 13    6/26/14 1:16a Wilsonlee
// [TAG]  		EIP173387
// [Category]  	Improvement
// [Description]  	Remove TODO comments.
// [Files]  		usbsetup.c, xhci.c, usbmass.c, usbCCID.c, usb.c, uhci.c,
// syskbc.c, usbport.c, usbbus.c, uhcd.c, UsbBotPeim.c, PeiXhci.c,
// PeiEhci.c
// 
// 12    4/30/14 6:14a Ryanchou
// [TAG]  		EIP151374
// [Category]  	Improvement
// [Description]  	Calculates maximum data length to be reported in the
// HID device.
// [Files]  		ehci.c, ohci.c, uhci.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, xhci.c
// 
// 11    2/26/14 1:55a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 10    2/11/14 11:47p Rameshr
// [TAG]  		EIP152203
// [Category]  	Improvement
// [Description]  	Hardcoded value for bProtocolNum removed.
// [Files]  		usbCCID.c
// 
// 9     6/20/13 10:22p Wilsonlee
// [TAG]  		EIP126814
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Security code check fail in the function
// USBAPI_CCIDRequest() in usbCCID.c.
// [RootCause]  	The function USBAPI_CCIDRequest() in usbCCID.c reads data
// from just outside the bounds of aUsbCCIDApiTable.
// [Solution]  	Condition is fixed from ">" to ">=".
// [Files]  		usbCCID.c
// 
// 8     4/02/13 7:54a Rameshr
// [TAG]  		EIP119028
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Insert smart card incorrectly (backwards), system will hang
// 0xA0 . 
// [RootCause]  	Invalid Status returned
// [Solution]  	Add a check whether ATR data is successfully read and
// processed, If not return error
// 
// 7     3/19/13 3:59a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 6     1/23/13 4:36a Wilsonlee
// [TAG]  		EIP109538
// [Category]  	Improvement
// [Description]  	Fix the code check error result.
// [Files]  		usbkbd.c, usbCCID.c, usbbus.c, efiusbccid.c
// 
// 5     11/10/12 6:39a Ryanchou
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
// 4     9/28/12 2:38a Wilsonlee
// [TAG]  		EIP93154
// [Category]  	Improvement
// [Description]  	Change the unit of the FixedDelay from 15 us to 1 us.
// [Files]  		amiusb.h, xhci.c, ehci.c, ohci.c, uhci.c, usb.c, usbCCID.c,
// usbmass.c, usbhub.c, elib.c
// 
// 3     5/02/12 1:55a Rajeshms
// [TAG]  		EIP83117 
// [Category]  	Improvement
// [Description]  	Extend the Support to different smart card Readers and
// smart Cards.
// [Files]  		usbCCID.c, amiusbrtCCID.h, usbdef.h, efiusbccid.c,
// AmiusbCCID.h
// 
// 2     9/22/11 1:24a Rajeshms
// [TAG]  		EIP67832
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When ICC(Smart Card) is unplugged and inserted again , it
// is not detected.
// [RootCause]  	The ChildHandle for the smart card where protocol is
// installed is not made to zero when it was unplugged.
// [Solution]  	The ChilHandle is changed to zero when smart card is
// unplugged.
// [Files]  		usbCCID.c
// 
// 1     7/12/11 8:04a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
//
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           UsbCCID.c
//
//  Description:    AMI USB CCID Device class support driver
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "amiusb.h"
#include "amidxelib.h"
#if USB_RUNTIME_DRIVER_IN_SMM
#include <AmiBufferValidationLib.h>
#endif

extern      USB_GLOBAL_DATA *gUsbData;
extern      BOOLEAN gCheckUsbApiParameter;

UINT8       gSequence = 0;

VOID _FAR_ *
USB_MemAlloc(
    UINT16  wNumBlk
);

UINT8
USB_MemFree (
    VOID _FAR_ * fpPtr,
    UINT16    wNumBlk
);

void    FixedDelay(
    IN UINTN
);

typedef VOID (*API_FUNC)(URP_STRUC*);

extern  UINT8   USB_InstallCallBackFunction (CALLBACK_FUNC  pfnCallBackFunction);

//                      Fi   Max  Di
UINT16 FiFmaxDi[] = {   372,   4, 0, 
                        372,   5, 1, 
                        558,   6, 2,
                        744,   8, 4,
                        1116, 12, 8,
                        1488, 16, 16,
                        1860, 20, 32,
                        0,     0, 64, 
                        0,     0, 12,
                        512,   5, 20,
                        768,   7,  0,
                        1024, 10,  0,
                        1536, 15,  0,
                        2048, 20,  0,
                        0,     0,  0,
                        0,     0,  0
                        };

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:        USBCCIDAPITable - USB CCID API Function Dispatch Table
//
// Type:        Function Dispatch Table
//
// Description: This is the table of functions used by USB CCID API
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>

API_FUNC aUsbCCIDApiTable[] = {

    USBCCIDAPISmartClassDescriptorSMM,  // USB Mass API Sub-Func 00h
    USBCCIDAPIAtrSMM,                   // USB Mass API Sub-Func 01h
    USBCCIDAPIPowerupSlotSMM,           // USB Mass API Sub-Func 02h
    USBCCIDAPIPowerDownSlotSMM,         // USB Mass API Sub-Func 03h
    USBCCIDAPIGetSlotStatusSMM,         // USB Mass API Sub-Func 04h
    USBCCIDAPIXfrBlockSMM,              // USB Mass API Sub-Func 05h
    USBCCIDAPIGetParametersSMM,         // USB Mass API Sub-Func 06h

};
 
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDFillDriverEntries
//
// Description: This function fills DEV_DRIVER structure
//
// Input:   
//              fpDevDriver    Pointer to the DEV driver 
//
// Output: 
//              None
//
// 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
USBCCIDFillDriverEntries (
    IN OUT DEV_DRIVER    *fpDevDriver
)
{

    fpDevDriver->bDevType               = BIOS_DEV_TYPE_STORAGE;
    fpDevDriver->bBaseClass             = BASE_CLASS_CCID_STORAGE;
    fpDevDriver->bSubClass              = SUB_CLASS_CCID;
    fpDevDriver->bProtocol              = PROTOCOL_CCID;
    fpDevDriver->bProtocol              = 0;
    fpDevDriver->pfnDeviceInit          = USBCCIDInitialize;
    fpDevDriver->pfnCheckDeviceType     = USBCCIDCheckForDevice;
    fpDevDriver->pfnConfigureDevice     = USBCCIDConfigureDevice;
    fpDevDriver->pfnDisconnectDevice    = USBCCIDDisconnectDevice;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDAPISmartClassDescriptorSMM
//
// Description: This function is part of the USB BIOS MASS API inside SMM
//
// Input:   
//              fpURPPointer    Pointer to the URP structure
//
// Output: 
//              fpURPPointer    Pointer to the URP structure
//              fpURP->bRetValue USB_SUCESS if data is returned
//
// Notes:       This API returns 36h bytes of SMART Class Descriptor to the caller. 
//              Input Buffer of 36h bytes long is provided by the caller. Caller is 
//              USBCCIDAPISmartClassDescriptor in EfiUsbCCID.C
// 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBCCIDAPISmartClassDescriptorSMM(
    IN OUT URP_STRUC *Urp
)
{
   
    DEV_INFO        *DevInfo;
    EFI_STATUS      EfiStatus = EFI_SUCCESS;
    UINT8           *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        EfiStatus = AmiValidateMemoryBuffer((VOID*)(Urp->ApiData.CCIDSmartClassDescriptor.fpResponseBuffer), 
                        (UINT32)sizeof(SMARTCLASS_DESC));
        if (EFI_ERROR(EfiStatus)) {
            USB_DEBUG(3, "UsbCcid Invalid Pointer, Buffer is in SMRAM.\n");
            Urp->bRetValue = USB_ERROR;
            return;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    DevInfo = (DEV_INFO *)(Urp->ApiData.CCIDSmartClassDescriptor.fpDevInfo);

    // Check whether it is a valid CCID Device
    if (!DevInfo || !DevInfo->pCCIDDescriptor) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    EfiStatus = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(EfiStatus)) {
        Urp->bRetValue = USB_PARAMETER_ERROR;
        return;
    }

    if (((UINT8*)DevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)DevInfo->pCCIDDescriptor > MemBlockEnd)) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    MemCopy((UINT8 *)DevInfo->pCCIDDescriptor, 
            (UINT8 *)(Urp->ApiData.CCIDSmartClassDescriptor.fpResponseBuffer), 
            (UINT32)sizeof(SMARTCLASS_DESC)
            );

    Urp->bRetValue = USB_SUCCESS;

    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDAPIAtrSMM
//
// Description: This function is part of the USB BIOS MASS API inside SMM
//
// Input:   fpURPPointer    Pointer to the URP structure, it contains the following:
//
// Output: fpURPPointer Pointer to the URP structure
//         fpURP->bRetValue : USB_SUCESS if data is returned
//
// Notes:   This API returns ATR data if present
// 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
USBCCIDAPIAtrSMM (
    IN OUT URP_STRUC *Urp

)
{

    DEV_INFO            *DevInfo;
    ICC_DEVICE          *IccDevice;
    EFI_STATUS          EfiStatus = EFI_SUCCESS;
    UINT8               *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        EfiStatus = AmiValidateMemoryBuffer((VOID*)(Urp->ApiData.CCIDAtr.ATRData), 
                        MAX_ATR_LENGTH);
        if (EFI_ERROR(EfiStatus)) {
            USB_DEBUG(3, "UsbCcid Invalid Pointer, Buffer is in SMRAM.\n");
            Urp->bRetValue = USB_ERROR;
            return;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    DevInfo = (DEV_INFO *)(Urp->ApiData.CCIDAtr.fpDevInfo);
    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo || !DevInfo->pCCIDDescriptor) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    EfiStatus = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(EfiStatus)) {
        Urp->bRetValue = USB_PARAMETER_ERROR;
        return;
    }

    if (((UINT8*)DevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)DevInfo->pCCIDDescriptor > MemBlockEnd)) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    Urp->bRetValue = USB_ERROR;

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetICCDevice(DevInfo, Urp->ApiData.CCIDAtr.Slot);

    if (IccDevice) {
        if (IccDevice->ConfiguredStatus & ATRDATAPRESENT) {
            MemCopy((UINT8 *)IccDevice->RawATRData, (UINT8 *)(Urp->ApiData.CCIDAtr.ATRData), MAX_ATR_LENGTH);
            Urp->bRetValue = USB_SUCCESS;
        }
    }

    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDAPIPowerupSlotSMM
//
// Description: This function is part of the USB BIOS MASS API inside SMM
//
// Input:       
//              fpURPPointer    Pointer to the URP structure
//
// Output:      
//              fpURPPointer Pointer to the URP structure
//              fpURP->bRetValue : USB_SUCESS if data is returned
//
// Notes:       This API powers up the particular slot in CCID and returns ATR data if successful
// 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
USBCCIDAPIPowerupSlotSMM (
    IN OUT URP_STRUC *Urp

)
{

    EFI_STATUS          Status;    
    DEV_INFO            *DevInfo;
    ICC_DEVICE          *IccDevice;
    UINT8               *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        Status = AmiValidateMemoryBuffer((VOID*)(Urp->ApiData.CCIDPowerupSlot.ATRData),
                    MAX_ATR_LENGTH);
        if (EFI_ERROR(Status)) {
            USB_DEBUG(3, "UsbCcid Invalid Pointer, Buffer is in SMRAM.\n");
            Urp->bRetValue = USB_ERROR;
            return;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    DevInfo = (DEV_INFO *)(Urp->ApiData.CCIDPowerupSlot.fpDevInfo);

    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo || !DevInfo->pCCIDDescriptor) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        Urp->bRetValue = USB_PARAMETER_ERROR;
        return;
    }

    if (((UINT8*)DevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)DevInfo->pCCIDDescriptor > MemBlockEnd)) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetICCDevice(DevInfo, Urp->ApiData.CCIDPowerupSlot.Slot);

    if (IccDevice) {
        //
        // The slot has been already discovered. Check the status.
        //
        if (IccDevice->ConfiguredStatus & VOLTAGEAPPLIED) {
            //
            // Power down the device
            //
            PCtoRDRIccPowerOff (DevInfo, IccDevice);
            RDRToPCSlotStatus(DevInfo, IccDevice);
        }
    }

    Status = ICCInsertEvent(DevInfo, Urp->ApiData.CCIDPowerupSlot.Slot);

    //
    // If the card has been successfully poweredup copy ATR data
    //
    if (!IccDevice) {
        IccDevice = GetICCDevice(DevInfo, Urp->ApiData.CCIDPowerupSlot.Slot);
        if (!IccDevice) {
            Urp->bRetValue = USB_ERROR;
            return;
        }
    }
    Urp->ApiData.CCIDPowerupSlot.bStatus = IccDevice->bStatus;
    Urp->ApiData.CCIDPowerupSlot.bError = IccDevice->bError;

    if (IccDevice->ConfiguredStatus & ATRDATAPRESENT) {
        MemCopy((UINT8 *)IccDevice->RawATRData, (UINT8 *)(Urp->ApiData.CCIDPowerupSlot.ATRData), MAX_ATR_LENGTH);        
    }

    Urp->bRetValue = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR) {
        Urp->bRetValue = USB_ERROR;
    }

    return;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDAPIPowerDownSlotSMM
//
// Description: This function is part of the USB BIOS MASS API inside SMM
//
// Input:   
//              fpURPPointer    Pointer to the URP structure, it contains the following:
//
// Output: 
//              fpURPPointer Pointer to the URP structure
//              fpURP->bRetValue : USB_SUCESS if data is returned
//
// Notes:       This API powers down the particular slot.
// 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
USBCCIDAPIPowerDownSlotSMM (
    IN OUT URP_STRUC *fpURP

)
{
    
    EFI_STATUS          Status = EFI_SUCCESS;
    DEV_INFO               *fpDevInfo;
    ICC_DEVICE            *fpICCDevice;
    UINT8       *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    fpDevInfo = (DEV_INFO *) (fpURP->ApiData.CCIDPowerdownSlot.fpDevInfo);

    fpURP->bRetValue    = USB_ERROR;

    //
    // Check whether it is a valid CCID Device
    //
    if (!fpDevInfo || !fpDevInfo->pCCIDDescriptor) {

        return;

    }

    Status = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(Status)) {
        fpURP->bRetValue = USB_PARAMETER_ERROR;
        return;
    }

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        fpURP->bRetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    fpICCDevice = GetICCDevice(fpDevInfo, fpURP->ApiData.CCIDPowerdownSlot.Slot);

    if (fpICCDevice) {
        //
        // The slot has been already discovered. Check the status.
        //
        if (fpICCDevice->ConfiguredStatus & ICCPRESENT) {
        
            //
            // Power down the device
            //
            Status = PCtoRDRIccPowerOff (fpDevInfo,  fpICCDevice);
            RDRToPCSlotStatus(fpDevInfo, fpICCDevice);

            fpICCDevice->ConfiguredStatus &= (~VOLTAGEAPPLIED);

            fpURP->ApiData.CCIDPowerdownSlot.bStatus = fpICCDevice->bStatus;
            fpURP->ApiData.CCIDPowerdownSlot.bError = fpICCDevice->bError;

        }
    }

    fpURP->bRetValue    = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR){
        fpURP->bRetValue    = USB_ERROR;
    }

    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDAPIGetSlotStatusSMM
//
// Description: This function is part of the USB BIOS MASS API inside SMM
//
// Input:   
//              fpURPPointer    Pointer to the URP structure, it contains the following:
//              UINT8           *bStatus;
//              UINT8           *bError;
//
// Output: 
//              fpURPPointer    Pointer to the URP structure
//              bRetValue       Return value
//              bClockStatus    Return Value
//
// Notes:       This API returns information from RDR_to_PC_SlotStatus. 
//              Caller is USBCCIDAPIGetSlotStatus in EfiUsbCCID.C
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBCCIDAPIGetSlotStatusSMM (
    IN OUT URP_STRUC *fpURP
)
{
    
    EFI_STATUS              Status;
    DEV_INFO                *fpDevInfo;
    ICC_DEVICE              *fpICCDevice;
    UINT8       *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    fpDevInfo = (DEV_INFO *) (fpURP->ApiData.CCIDGetSlotStatus.fpDevInfo);

    //
    // Check whether it is a valid CCID Device
    //
    if (!fpDevInfo || !fpDevInfo->pCCIDDescriptor) {

        fpURP->bRetValue    = USB_ERROR;
        return;

    }

    Status = UsbDevInfoValidation(fpDevInfo);

    if (EFI_ERROR(Status)) {
        fpURP->bRetValue = USB_PARAMETER_ERROR;
        return;
    }

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        fpURP->bRetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    fpICCDevice = GetICCDevice(fpDevInfo, fpURP->ApiData.CCIDGetSlotStatus.Slot);
    if (!fpICCDevice ||  !(fpICCDevice->ConfiguredStatus & ICCPRESENT)) {

        fpURP->ApiData.CCIDGetSlotStatus.bStatus = 0x42; 
        fpURP->ApiData.CCIDGetSlotStatus.bError = 0xFE;
        fpURP->bRetValue    = USB_ERROR;
        return;

    }
    
    //
    // Issue the cmd
    //
    Status = PCToRDRGetSlotStatus(fpDevInfo, fpICCDevice);

    if (EFI_ERROR(Status)){
        fpURP->bRetValue    = USB_ERROR;
        return;        
    }

    //
    // Get the response
    //
    Status = RDRToPCSlotStatus(fpDevInfo, fpICCDevice);

    fpURP->ApiData.CCIDGetSlotStatus.bStatus = fpICCDevice->bStatus;
    fpURP->ApiData.CCIDGetSlotStatus.bError = fpICCDevice->bError;
    fpURP->ApiData.CCIDGetSlotStatus.bClockStatus = fpICCDevice->bClockStatus;

    fpURP->bRetValue    = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR){
        fpURP->bRetValue    = USB_ERROR;
    }

    return;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDAPIXfrBlockSMM
//
// Description: This function is part of the USB BIOS MASS API.
//
// Input:   
//              fpURPPointer    Pointer to the URP structure, it contains the following:
//              IN UINTN        CmdLength
//              IN UINTN        fpCmdBuffer
//              OUT UINT8       bStatus
//              OUT UINT8       bError
//              IN OUT UINTN    ResponseLength - Points to the buffer length of fpResponseBuffer
//              OUT UINTN       fpResponseBuffer
//
// Output: 
//              fpURPPointer    Pointer to the URP structure
//              OUT UINT8       bStatus
//              OUT UINT8       bError
//              IN OUT UINTN    ResponseLength - Points to the actual response bytes in fpResponseBuffer on return
//              OUT UINTN       fpResponseBuffer
//
// Note:        This API excutes PC_to_RDR_XfrBlock cmd and returns the response from 
//              RDR_to_PC_DataBlock to the caller.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBCCIDAPIXfrBlockSMM (
    IN OUT URP_STRUC *Urp
)
{

    EFI_STATUS          Status;
    DEV_INFO            *DevInfo;
    ICC_DEVICE          *IccDevice;
    UINT32              CmdLength = (UINT32)Urp->ApiData.CCIDXfrBlock.CmdLength;
    UINT8               *CmdBuffer = (UINT8 *)Urp->ApiData.CCIDXfrBlock.fpCmdBuffer;
    UINT8               IsBlock = (BOOLEAN)Urp->ApiData.CCIDXfrBlock.ISBlock;
    UINT32              *ResponseLength = (UINT32 *)&(Urp->ApiData.CCIDXfrBlock.ResponseLength);
    UINT8               *ResponseBuffer = (UINT8 *)(Urp->ApiData.CCIDXfrBlock.fpResponseBuffer);
    UINT8       *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        Status = AmiValidateMemoryBuffer((VOID*)(Urp->ApiData.CCIDXfrBlock.fpCmdBuffer),
                    Urp->ApiData.CCIDXfrBlock.CmdLength);
        if (EFI_ERROR(Status)) {
            USB_DEBUG(3, "UsbCcid Invalid Pointer, Buffer is in SMRAM.\n");
            Urp->bRetValue = USB_ERROR;
            return;
        }
        Status = AmiValidateMemoryBuffer((VOID*)(Urp->ApiData.CCIDXfrBlock.fpResponseBuffer),
                    Urp->ApiData.CCIDXfrBlock.ResponseLength);
        if (EFI_ERROR(Status)) {
            USB_DEBUG(3, "UsbCcid Invalid Pointer, Buffer is in SMRAM.\n");
            Urp->bRetValue = USB_ERROR;
            return;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    DevInfo = (DEV_INFO *)(Urp->ApiData.CCIDXfrBlock.fpDevInfo);

    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo || !DevInfo->pCCIDDescriptor) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        Urp->bRetValue = USB_PARAMETER_ERROR;
        return;
    }

    if (((UINT8*)DevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)DevInfo->pCCIDDescriptor > MemBlockEnd)) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetICCDevice(DevInfo, Urp->ApiData.CCIDXfrBlock.Slot);

    if (!IccDevice || !(IccDevice->ConfiguredStatus & ICCPRESENT)) {

        Urp->ApiData.CCIDXfrBlock.bStatus = 0x42; 
        Urp->ApiData.CCIDXfrBlock.bError = 0xFE;
        Urp->bRetValue = USB_ERROR;
        return;
    }


    //
    // Only T0/T1 are recognized
    //
    if (IccDevice->bProtocolNum > 1) {
        Urp->bRetValue = USB_ERROR;        
        return;
    } 

    //
    // Check for T0/T1
    //
    if (IccDevice->bProtocolNum){    
        switch (((SMARTCLASS_DESC*)DevInfo->pCCIDDescriptor)->dwFeatures & 0x70000) {

            case TDPU_LEVEL_EXCHANGE:

                Status = TxRxT1TDPUChar(DevInfo, IccDevice, CmdLength, CmdBuffer, IsBlock, ResponseLength, ResponseBuffer);
                break;

            case CHARACTER_LEVEL_EXCHANGE:

                Status = TxRxT1TDPUChar(DevInfo, IccDevice, CmdLength, CmdBuffer, IsBlock, ResponseLength, ResponseBuffer);
                break;

            case SHORT_ADPU_LEVEL_EXCHANGE:
            case EXT_ADPU_LEVEL_EXCHANGE:
                Status = TxRxT1Adpu(DevInfo, IccDevice, CmdLength, CmdBuffer, ResponseLength, ResponseBuffer);
                break;
        }
    } else {
        // T0 not supported yet
        Urp->bRetValue = USB_ERROR;        
        return;
    }

    Urp->ApiData.CCIDXfrBlock.bStatus = IccDevice->bStatus;
    Urp->ApiData.CCIDXfrBlock.bError = IccDevice->bError;

    Urp->bRetValue = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR) {
        Urp->bRetValue = USB_ERROR;
    }

    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDAPIGetParametersSMM
//
// Description: This function is part of the USB BIOS MASS API.
//
// Input:   
//              fpURPPointer    Pointer to the URP structure, it contains the following:
//              OUT UINT8       bStatus;
//              OUT UINT8       bError;
//              IN OUT UINTN    ResponseLength;
//              OUT UINTN       fpResponseBuffer;
//              IN  UINT8       Slot;
//              OUT UINTN       fpDevInfo;
//
// Output: 
//              fpURPPointer    Pointer to the URP structure
//              bRetValue       Return value
//
// Notes:       This API returns the response to RDR_to_PCParameters cmd
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBCCIDAPIGetParametersSMM (
    IN OUT URP_STRUC *Urp

)
{
    
    EFI_STATUS              Status;
    DEV_INFO                *DevInfo;
    ICC_DEVICE              *IccDevice;
    UINT8       *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

#if USB_RUNTIME_DRIVER_IN_SMM
    if (gCheckUsbApiParameter) {
        Status = AmiValidateMemoryBuffer((VOID*)(Urp->ApiData.CCIDGetParameters.fpResponseBuffer),
                    Urp->ApiData.CCIDGetParameters.ResponseLength);
        if (EFI_ERROR(Status)) {
            USB_DEBUG(3, "UsbCcid Invalid Pointer, Buffer is in SMRAM.\n");
            Urp->bRetValue = USB_ERROR;
            return;
        }
        gCheckUsbApiParameter = FALSE;
    }
#endif

    DevInfo = (DEV_INFO *)(Urp->ApiData.CCIDGetParameters.fpDevInfo);

    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo || !DevInfo->pCCIDDescriptor) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        Urp->bRetValue = USB_PARAMETER_ERROR;
        return;
    }

    if (((UINT8*)DevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)DevInfo->pCCIDDescriptor > MemBlockEnd)) {
        Urp->bRetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetICCDevice(DevInfo, Urp->ApiData.CCIDGetParameters.Slot);
    if (!IccDevice || !(IccDevice->ConfiguredStatus & ICCPRESENT)) {
        Urp->ApiData.CCIDGetParameters.bStatus = 0x42; 
        Urp->ApiData.CCIDGetParameters.bError = 0xFE;
        Urp->bRetValue = USB_ERROR;
        return;
    }

    // Should we check for device presence in data area. The call will find that out anyways.

    //    
    // Issue the cmd
    //
    Status = PCToRDRGetParameters(DevInfo, IccDevice);

    if (EFI_ERROR(Status)){
        Urp->bRetValue = USB_ERROR;
        return;        
    }

    //
    // Get the response
    //
    Status = RDRToPCParameters(DevInfo, IccDevice);
    if (!EFI_ERROR(Status)) {
        Urp->ApiData.CCIDGetParameters.ResponseLength = 6;
        if (IccDevice->bProtocolNum){
            Urp->ApiData.CCIDGetParameters.ResponseLength = 8;
        }
        //
        // Update the Data
        //
        MemCopy((UINT8 *)&(IccDevice->bProtocolNum), 
                (UINT8 *)(Urp->ApiData.CCIDGetParameters.fpResponseBuffer), 
                (UINT32)(Urp->ApiData.CCIDGetParameters.ResponseLength)
                );
    }

    Urp->ApiData.CCIDGetParameters.bStatus = IccDevice->bStatus;
    Urp->ApiData.CCIDGetParameters.bError = IccDevice->bError;

    Urp->bRetValue = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR) {
        Urp->bRetValue = USB_ERROR;
    }

    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAPI_CCIDRequest
//
// Description: This routine services the USB API function number 30h.  It
//              handles all the CCID related calls from the higher
//              layer. Different sub-functions are invoked depending on
//              the sub-function number
//
// Input:   
//              fpURPPointer    Pointer to the URP structure
//              fpURPPointer.bSubFunc   Subfunction number
//
// Output:  
//              URP structure is updated with the relevant information
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBAPI_CCIDRequest (
    URP_STRUC *fpURP
)
{
    UINT8 bCCIDFuncIndex = fpURP->bSubFunc;
    UINT8 bNumberOfCCIDFunctions = sizeof aUsbCCIDApiTable / sizeof (API_FUNC *);

    //
    // Make sure function number is valid
    //
    if (bCCIDFuncIndex >= bNumberOfCCIDFunctions) {
        //fpURP->bRetValue = USBAPI_INVALID_FUNCTION;
        USB_DEBUG(3, "UsbApi CCIDRequest Invalid function#%x\n", bCCIDFuncIndex);
        return;
    }
    //
    // Function number is valid - call it
    //
    aUsbCCIDApiTable[bCCIDFuncIndex](fpURP);

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:    PCtoRDRIccPowerOn
//
// Description:  PC_TO_RDR_XFRBLOCK cmd is issued to the device
//
// Input  
//              IN DEV_INFO             *fpDevInfo,
//              IN ICC_DEVICE           *fpICCDevice,
//              IN UINT32               CmdLength,
//              IN UINT8                *CmdBuffer,
//              IN UINT8                BlockWaitingTime,
//              IN UINT16               LevelParameter
//
// Output :     
//              EFI_STATUS
//
// Notes:       This function sends PC_TO_RDR_XFRBLOCK to the device. 
//              See section 6.1.4 of CCID spec 1.1 for the details.
//              CmdBuffer points to abData.
//          
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PCToRDRXfrBlock (
    IN DEV_INFO             *fpDevInfo,
    IN ICC_DEVICE           *fpICCDevice,
    IN UINT32               CmdLength,
    IN UINT8                *CmdBuffer,
    IN UINT8                BlockWaitingTime,
    IN UINT16               LevelParameter    

)
{

    EFI_STATUS                      Status = EFI_SUCCESS;
    PC_TO_RDR_XFRBLOCK_STRUC        *fpCmdBuffer;
    UINT32                          dwData;
    UINT32                          i;  

    USB_DEBUG (DEBUG_LEVEL_3, "PCToRDRXfrBlock ....");

    fpCmdBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength));
    ASSERT(fpCmdBuffer);
    if (!fpCmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpCmdBuffer, sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength, 0);

    //
    // Prepare  the cmd buffer
    //
    fpCmdBuffer->bMessageType = PC_TO_RDR_XFRBLOCK;
    fpCmdBuffer->dwLength = CmdLength;
    fpCmdBuffer->bSlot = fpICCDevice->Slot;
    fpCmdBuffer->bSeq = gSequence;
    fpCmdBuffer->bBWI = BlockWaitingTime;
    fpCmdBuffer->wLevelParameter = LevelParameter;

    //
    // Copy the cmd
    //
    if (CmdLength) {
        MemCopy(CmdBuffer, (UINT8 *)fpCmdBuffer + sizeof(PC_TO_RDR_XFRBLOCK_STRUC), CmdLength);
    }


    USB_DEBUG (DEBUG_LEVEL_3, "\n");
    for (i=0; i< sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength; i++) {
        USB_DEBUG (DEBUG_LEVEL_3, "%02X ", ((UINT8 *)fpCmdBuffer)[i]);
    }
    USB_DEBUG (DEBUG_LEVEL_3, "\n");

    dwData = USBCCIDIssueBulkTransfer(fpDevInfo, 0, 
                                    (UINT8 *)fpCmdBuffer, 
                                    sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!dwData) {
        Status = EFI_DEVICE_ERROR;
    }

    USB_MemFree(fpCmdBuffer, (UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength));

    USB_DEBUG (DEBUG_LEVEL_3, "%r ....", Status);

    return Status;
    
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PCtoRDRIccPowerOn
//
// Description: PC_TO_RDR_ICCPOWERON cmd is issued to the CCID
//
// Input:
//              IN DEV_INFO     *fpDevInfo,
//              IN ICC_DEVICE   *fpICCDevice,
//              IN UINT8        PowerLevel - 00:Automatic  Voltage selection, 01:5.0v, 02:3.0v, 03:1.8v
//
// Output: 
//              EFI_STATUS
//
// Notes:       See section 6.1.1 of CCID spec Rev 1.1 for more details
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PCtoRDRIccPowerOn(
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice,
    IN UINT8            PowerLevel
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_ICCPOWERON_STRUC     *fpCmdBuffer;
    UINT32                        dwData;

    USB_DEBUG (DEBUG_LEVEL_3, "PCtoRDRIccPowerOn ....");

    fpCmdBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_ICCPOWERON_STRUC)));
    ASSERT(fpCmdBuffer);
    if (!fpCmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpCmdBuffer, sizeof(PC_TO_RDR_ICCPOWERON_STRUC), 0);

    //
    // Prepare  the cmd buffer
    //
    fpCmdBuffer->bMessageType = PC_TO_RDR_ICCPOWERON;
    fpCmdBuffer->dwLength = 0;
    fpCmdBuffer->bSlot = fpICCDevice->Slot;
    fpCmdBuffer->bSeq = gSequence;
    fpCmdBuffer->bPowerSlot = PowerLevel;
    fpCmdBuffer->abRFU = 0;

    dwData = USBCCIDIssueBulkTransfer(fpDevInfo, 0, 
                                    (UINT8 *)fpCmdBuffer, 
                                    sizeof(PC_TO_RDR_ICCPOWERON_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!dwData) {
        Status = EFI_DEVICE_ERROR;
    }

    USB_MemFree(fpCmdBuffer, (UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_ICCPOWERON_STRUC)));

    USB_DEBUG (DEBUG_LEVEL_3, "%r ....", Status);

    return Status;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PCtoRDRIccPowerOff
//
// Description: PC_TO_RDR_ICCPOWEROFF cmd is issued to the CCID
//
// Input :
//              IN DEV_INFO           *fpDevInfo,
//              IN ICC_DEVICE        *fpICCDevice
//
// Output : 
//              EFI_STATUS
//
// Notes:       See section 6.1.2 of CCID spec Rev 1.1 for more details
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PCtoRDRIccPowerOff(
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice
)
{

    EFI_STATUS                  Status = EFI_SUCCESS;
    PC_TO_RDR_ICCPOWEROFF_STRUC *fpCmdBuffer;
    UINT32                      dwData;

    USB_DEBUG (DEBUG_LEVEL_3, "PCtoRDRIccPowerOff ....");

    fpCmdBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_ICCPOWEROFF_STRUC)));
    ASSERT(fpCmdBuffer);
    if (!fpCmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpCmdBuffer, sizeof(PC_TO_RDR_ICCPOWEROFF_STRUC), 0);

    //
    // Prepare the buffer
    //
    fpCmdBuffer->bMessageType = PC_TO_RDR_ICCPOWEROFF;
    fpCmdBuffer->dwLength = 0;
    fpCmdBuffer->bSlot = fpICCDevice->Slot;
    fpCmdBuffer->bSeq = gSequence;

    dwData = USBCCIDIssueBulkTransfer(fpDevInfo, 0, 
                                    (UINT8 *)fpCmdBuffer, 
                                    sizeof(PC_TO_RDR_ICCPOWEROFF_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!dwData) {
        Status = EFI_DEVICE_ERROR;
    }
    else {
        fpICCDevice->ConfiguredStatus = 0;
    }

    USB_MemFree(fpCmdBuffer, (UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_ICCPOWEROFF_STRUC)));

    USB_DEBUG (DEBUG_LEVEL_3, "%r ....", Status);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PCToRDRGetSlotStatus
//
// Description: PC_TO_RDR_GETSLOTSTATUS cmd is issued to CCID
//
// Input: 
//              IN DEV_INFO           *fpDevInfo,
//              IN ICC_DEVICE        *fpICCDevice
//
// Output:
//              EFI_STATUS
//
//Notes:        See section 6.1.3 of CCID spec Rev 1.1 for more details
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PCToRDRGetSlotStatus(
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_GETSLOT_STATUS_STRUC *fpCmdBuffer;
    UINT32                        dwData;

    USB_DEBUG (DEBUG_LEVEL_3, "PCToRDRGetSlotStatus ....");

    fpCmdBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_GETSLOT_STATUS_STRUC)));
    ASSERT(fpCmdBuffer);
    if (!fpCmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpCmdBuffer, sizeof(PC_TO_RDR_GETPARAMETERS_STRUC), 0);
    
    //
    // Prepare cmd buffer
    //
    fpCmdBuffer->bMessageType = PC_TO_RDR_GETSLOTSTATUS;
    fpCmdBuffer->bSlot = fpICCDevice->Slot;
    fpCmdBuffer->bSeq = gSequence;

    dwData = USBCCIDIssueBulkTransfer(fpDevInfo, 0, 
                                    (UINT8 *)fpCmdBuffer, 
                                    sizeof(PC_TO_RDR_GETSLOT_STATUS_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!dwData) {
        Status = EFI_DEVICE_ERROR;
    }

    USB_MemFree(fpCmdBuffer, (UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_GETSLOT_STATUS_STRUC)));

    USB_DEBUG (DEBUG_LEVEL_3, "%r ....", Status);

    return Status;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PCToRDRGetParameters
//
// Description: PC_TO_RDR_GETPARAMETERS cmd is issued to CCID
//
// Input:
//              IN DEV_INFO           *fpDevInfo,
//              IN ICC_DEVICE        *fpICCDevice
//
// Output:
//              EFI_STATUS
//
// Notes:       See section 6.1.5 of CCID spec Rev 1.1 for more details
//             
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PCToRDRGetParameters(
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_GETPARAMETERS_STRUC *fpCmdBuffer;
    UINT32                        dwData;

    USB_DEBUG (DEBUG_LEVEL_3, "PCToRDRGetParameters ....");

    fpCmdBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_GETPARAMETERS_STRUC)));
    ASSERT(fpCmdBuffer);
    if (!fpCmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpCmdBuffer, sizeof(PC_TO_RDR_GETPARAMETERS_STRUC), 0);

    //
    // Prepare cmd buffer
    //
    fpCmdBuffer->bMessageType = PC_TO_RDR_GETPARAMETERS;
    fpCmdBuffer->bSlot = fpICCDevice->Slot;
    fpCmdBuffer->bSeq = gSequence;

    dwData = USBCCIDIssueBulkTransfer(fpDevInfo, 0, 
                                    (UINT8 *)fpCmdBuffer, 
                                    sizeof(PC_TO_RDR_GETPARAMETERS_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!dwData) {
        Status = EFI_DEVICE_ERROR;
    }

    USB_MemFree(fpCmdBuffer, (UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_GETPARAMETERS_STRUC)));

    USB_DEBUG (DEBUG_LEVEL_3, "%r ....", Status);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PCToRDRSetParameters
//
// Description: PC_TO_RDR_SETPARAMETERS cmd is issued to CCID
//
// Input :
//              IN DEV_INFO     *fpDevInfo
//              IN ICC_DEVICE   *fpICCDevice
//              IN UINT8        ProtocolNum -  0 : T=0, 1 : T=1
//              IN VOID         *Data - Points to data from abProtocolDataStructure 
//                                      in PC_TO_RDR_SETPARAMETERS
//
// Output:
//              EFI_STATUS
//
// Notes:       See section 6.1.7 of CCID spec Rev 1.1 for more details
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PCToRDRSetParameters(
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice,
    IN UINT8            ProtocolNum,
    IN VOID             *Data
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_SETPARAMETERS_T0_STRUC *fpCmdBuffer;
    UINT32                        dwData;
    UINT8                        Length = ProtocolNum == 0 ? sizeof(PROTOCOL_DATA_T0) : sizeof(PROTOCOL_DATA_T1);

    USB_DEBUG (DEBUG_LEVEL_3, "PCToRDRSetParameters ....");

    fpCmdBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(Length + sizeof(RDR_HEADER)));
    ASSERT(fpCmdBuffer);
    if (!fpCmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpCmdBuffer, Length + sizeof(RDR_HEADER), 0);

    //
    // Prepare 
    //
    fpCmdBuffer->bMessageType = PC_TO_RDR_SETPARAMETERS;
    fpCmdBuffer->dwLength = Length;
    fpCmdBuffer->bSlot = fpICCDevice->Slot;
    fpCmdBuffer->bSeq = gSequence;
    fpCmdBuffer->bProtocolNum = ProtocolNum;

    MemCopy ((UINT8 *)Data,  (UINT8 *)fpCmdBuffer +sizeof(RDR_HEADER), Length); 

    dwData = USBCCIDIssueBulkTransfer(fpDevInfo, 0, 
                                    (UINT8 *)fpCmdBuffer, 
                                    Length + sizeof(RDR_HEADER)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!dwData) {
        Status = EFI_DEVICE_ERROR;
    }

    USB_MemFree(fpCmdBuffer, (UINT8)GET_MEM_BLK_COUNT(Length + sizeof(RDR_HEADER)));

    USB_DEBUG (DEBUG_LEVEL_3, "%r ....", Status);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PCToRDRSetDataRateAndClockFrequency
//
// Description: PC_TO_RDR_SETDATARATEANDCLOCK cmd is issued. 
//              Response for this cmd is from RDR_TO_PC_DATARATEANDCLOCK
//
// Input: 
//              IN DEV_INFO         *fpDevInfo
//              IN ICC_DEVICE       *fpICCDevice
//              IN UINT32           ClockFrequency  - ICC Clock Frequency in KHz
//              IN UINT32           DataRate - ICC data rate in bpd
//
// Output:
//              EFI_STATUS
//
// Notes:       See section 6.1.14 of CCID spec Rev 1.1 for more details     
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PCToRDRSetDataRateAndClockFrequency(
    IN DEV_INFO          *fpDevInfo,
    IN ICC_DEVICE        *fpICCDevice,
    IN UINT32            ClockFrequency, 
    IN UINT32            DataRate
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC *fpCmdBuffer;
    UINT32                        dwData;

    USB_DEBUG (DEBUG_LEVEL_3, "PCToRDRGetParameters ....");

    fpCmdBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC)));
    ASSERT(fpCmdBuffer);
    if (!fpCmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpCmdBuffer, sizeof(PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC), 0);

    //
    // Prepare cmd buffer
    //
    fpCmdBuffer->bMessageType = PC_TO_RDR_SETDATARATEANDCLOCK;
    fpCmdBuffer->dwLength = 8;
    fpCmdBuffer->bSlot = fpICCDevice->Slot;
    fpCmdBuffer->bSeq = gSequence;
    fpCmdBuffer->dwCloclFrequency = ClockFrequency;
    fpCmdBuffer->dwDataRate = DataRate;

    dwData = USBCCIDIssueBulkTransfer(fpDevInfo, 0, 
                                    (UINT8 *)fpCmdBuffer, 
                                    sizeof(PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!dwData) {
        Status = EFI_DEVICE_ERROR;
    }

    USB_MemFree(fpCmdBuffer, (UINT8)GET_MEM_BLK_COUNT(sizeof(PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC)));

    USB_DEBUG (DEBUG_LEVEL_3, "%r ....", Status);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   RDRToPCDataBlock
//
// Description: RDR_TO_PC_DATABLOCK cmd is issued to the CCID. 
//              This is on response to PCI_to_RDR_XfrBlock
//
// Input: 
//              IN DEV_INFO        *fpDevInfo
//              IN ICC_DEVICE      *fpICCDevice
//              IN OUT UINT32      *dwLength - # of bytes in Buffer
//              OUT UINT8          *Buffer - Points to abData in RDR_TO_PC_DATABLOCK
//
// Output:
//              EFI_STATUS
//
// Notes:       See section 6.2.1 of CCID spec Rev 1.1 for more details     
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
RDRToPCDataBlock(
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice,
    IN OUT UINT32       *dwLength,
    OUT UINT8           *Buffer

)
{    

    EFI_STATUS      Status = EFI_SUCCESS;
    RDR_TO_PC_DATABLOCK_STRUC*  fpReceiveBuffer;
    UINT32          dwData;
    UINT8           Iterations = 3;
    UINT32          InputLength = *dwLength;
    UINT32           i;   

    //
    // Allocate memory for receiving data
    //
    fpReceiveBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(RDR_TO_PC_DATABLOCK_STRUC) + *dwLength));
    ASSERT(fpReceiveBuffer);
    if (!fpReceiveBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpReceiveBuffer, sizeof(RDR_TO_PC_DATABLOCK_STRUC) + *dwLength, 0);

    do {
        //
        // Get the response 
        //
        fpReceiveBuffer->bMessageType = RDR_TO_PC_DATABLOCK;
        fpReceiveBuffer->dwLength = *dwLength;
        fpReceiveBuffer->bSlot = fpICCDevice->Slot;
        fpReceiveBuffer->bSeq = gSequence;
        fpReceiveBuffer->bStatus = 0;
        fpReceiveBuffer->bError = 0;
        fpReceiveBuffer->bChainParameter = 0;

        dwData = USBCCIDIssueBulkTransfer(fpDevInfo, BIT7, 
                                        (UINT8 *)fpReceiveBuffer, 
                                        sizeof(RDR_TO_PC_DATABLOCK_STRUC) + *dwLength
                                        );

        USB_DEBUG (DEBUG_LEVEL_3, "\n");

        for (i=0; i< sizeof(RDR_TO_PC_DATABLOCK_STRUC) + fpReceiveBuffer->dwLength; i++) {
            USB_DEBUG (DEBUG_LEVEL_3, "%02X ", ((UINT8 *)fpReceiveBuffer)[i]);
        }

        USB_DEBUG (DEBUG_LEVEL_3, "\n");

        //    
        // Handle Error if any. This error is due to blk transfer
        //
        if (!dwData) {
            Status = EFI_DEVICE_ERROR;
            goto exit_RDRToPCDataBlock;
        }    

        //
        // Check for time extension 
        //
        if ((fpReceiveBuffer->bStatus & 0xC0) == 0x80) {
            FixedDelay(fpReceiveBuffer->bError * fpICCDevice->WaitTime * 1000);  
        } else {
            break;
        }

        Iterations--;
    } while (Iterations);    

    // Should the cmd be aborted if the response isn't received???

    //
    // Processed without error if Zero
    //
    if (fpReceiveBuffer->bStatus & 0xC0) {
        Status = EFI_DEVICE_ERROR;

        if ((fpReceiveBuffer->bStatus & 0x3) == 0x2) {        
            Status = EFI_NOT_FOUND;
        }
    }

    if (Iterations && !EFI_ERROR(Status)) {
    
        fpICCDevice->bChainParameter = fpReceiveBuffer->bChainParameter;

        //
        // If response is successful get the data
        //
        if (fpReceiveBuffer->dwLength && fpReceiveBuffer->dwLength <= *dwLength) {
    
            // Copy data 
            MemCopy ((UINT8 *)fpReceiveBuffer + sizeof(RDR_TO_PC_DATABLOCK_STRUC),  
                    Buffer, 
                    fpReceiveBuffer->dwLength
                    ); 

        }

        if  (fpReceiveBuffer->dwLength > *dwLength) {
            Status = EFI_BUFFER_TOO_SMALL;
        }

        //
        // Update the o/p buffer length
        //
        *dwLength = fpReceiveBuffer->dwLength;

    } else {

        Status = EFI_DEVICE_ERROR;
        *dwLength = 0;
    }

    //
    // Save the last cmd status 
    //
    fpICCDevice->bStatus = fpReceiveBuffer->bStatus;
    fpICCDevice->bError = fpReceiveBuffer->bError;


    //    
    // if success exit
    //
    if (!EFI_ERROR(Status) && !fpICCDevice->bStatus) {
        Status =  EFI_SUCCESS;
        goto exit_RDRToPCDataBlock;
    }

    // Card not present?
    Status = EFI_NOT_FOUND;
    if ((fpReceiveBuffer->bStatus & 7) == 2) goto exit_RDRToPCDataBlock;

    //
    // Other errors
    //
    Status = EFI_DEVICE_ERROR;

exit_RDRToPCDataBlock:

    gSequence++;

    USB_MemFree(fpReceiveBuffer, 
                (UINT8)GET_MEM_BLK_COUNT(sizeof(RDR_TO_PC_DATABLOCK_STRUC) + InputLength)
                );

    USB_DEBUG (DEBUG_LEVEL_3, " Status : %r bStatus : %02X bError : %02X\n", Status, fpICCDevice->bStatus, fpICCDevice->bError);
    
    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   RDRToPCSlotStatus
//
// Description: RDR_TO_PC_SLOTSTATUS cmd is issued to CCID.
//
// Input:
//              IN DEV_INFO         *fpDevInfo,
//              IN ICC_DEVICE       *fpICCDevice
//
// Output:
//              EFI_STATUS
//
// Notes:       bStatus, BError and bClockStatus is updated.  
//              See section 6.2.2 of CCID spec Rev 1.1 for more details.
//    
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
RDRToPCSlotStatus(
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice
)
{

    EFI_STATUS                  Status = EFI_SUCCESS;
    RDR_TO_PC_SLOTSTATUS_STRUC  *fpReceiveBuffer;
    UINT32                      dwData;
    UINT8                       Iterations = 3;    

    fpReceiveBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(RDR_TO_PC_SLOTSTATUS_STRUC)));
    ASSERT(fpReceiveBuffer);
    if (!fpReceiveBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpReceiveBuffer, sizeof(RDR_TO_PC_SLOTSTATUS_STRUC), 0);
    do {
        //
        // Read the PCSlot Status
        //
        fpReceiveBuffer->bMessageType = RDR_TO_PC_SLOTSTATUS;
        fpReceiveBuffer->dwLength = 0;
        fpReceiveBuffer->bSlot = fpICCDevice->Slot;
        fpReceiveBuffer->bSeq = gSequence;

        dwData = USBCCIDIssueBulkTransfer(fpDevInfo, BIT7, 
                                        (UINT8 *)fpReceiveBuffer, 
                                        sizeof(RDR_TO_PC_SLOTSTATUS_STRUC)
                                        );

        //
        // Handle Error if any. This error is due to blk transfer
        //
        if (!dwData) {
            Status = EFI_DEVICE_ERROR;
            goto exit_RDRToPCSlotStatus;
        }

        //
        // Check for time extension 
        //
        if ((fpReceiveBuffer->bStatus & 0xC0) == 0x80) {
            FixedDelay(fpReceiveBuffer->bError * fpICCDevice->WaitTime * 1000);  
        } else {
            break;
        }

        Iterations--;
    } while (Iterations);


    //
    // Save the last cmd status 
    //
    fpICCDevice->bStatus = fpReceiveBuffer->bStatus;
    fpICCDevice->bError = fpReceiveBuffer->bError;

    // Processed without error if Zero
    if (fpReceiveBuffer->bStatus & 0xC0) {
        Status = EFI_DEVICE_ERROR;

        if ((fpReceiveBuffer->bStatus & 0x3) == 0x2) {        
            Status = EFI_NOT_FOUND;
        }

    }

    if (Iterations && !EFI_ERROR(Status)) {
        //
        // Update the last ClockStatus
        //
        fpICCDevice->bClockStatus = fpReceiveBuffer->bClockStatus; 
    } else {
        Status = EFI_DEVICE_ERROR;
    }

exit_RDRToPCSlotStatus:

    gSequence++;

    USB_MemFree(fpReceiveBuffer, 
                (UINT8)GET_MEM_BLK_COUNT(sizeof(RDR_TO_PC_SLOTSTATUS_STRUC))
                );

    USB_DEBUG (DEBUG_LEVEL_3, " Status :  %r bStatus : %02X bError : %02X\n", Status, fpICCDevice->bStatus, fpICCDevice->bError);

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   RDRToPCParameters
//
// Description: RDR_TO_PC_SLOTSTATUS cmd is issued
//
// Input: 
//              IN DEV_INFO         *fpDevInfo,
//              IN ICC_DEVICE       *fpICCDevice
//
// Output:
//              EFI_STATUS
//              abProtocolDataStructure is copied
//        
//
// Notes:       bStatus, BErroris updated.  See section 6.2.3 of CCID spec 
//              Rev 1.1 for more details. 
//              bProtocolNum and abProtocolDatStructure is captured.
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
RDRToPCParameters(
    IN DEV_INFO           *fpDevInfo,
    IN ICC_DEVICE        *fpICCDevice
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    RDR_TO_PC_PARAMETERS_T1_STRUC *fpReceiveBuffer;
    UINT32                        dwData;
    UINT8                         Iterations = 3;    

    fpReceiveBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(RDR_TO_PC_PARAMETERS_T1_STRUC)));
    ASSERT(fpReceiveBuffer);
    if (!fpReceiveBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpReceiveBuffer, sizeof(RDR_TO_PC_PARAMETERS_T1_STRUC), 0);

    do {

        //
        // Read the PCSlot Status
        //
        fpReceiveBuffer->Header.bMessageType = RDR_TO_PC_PARAMETERS;
        fpReceiveBuffer->Header.dwLength = 0;
        fpReceiveBuffer->Header.bSlot = fpICCDevice->Slot;
        fpReceiveBuffer->Header.bSeq = gSequence;

        dwData = USBCCIDIssueBulkTransfer(fpDevInfo, BIT7, 
                                        (UINT8 *)fpReceiveBuffer, 
                                        sizeof(RDR_TO_PC_PARAMETERS_T1_STRUC)
                                        );

        //
        // Handle Error if any. This error is due to blk transfer
        //
        if (!dwData) {
            Status = EFI_DEVICE_ERROR;
            goto exit_RDRToPCParameters;
        }

        //
        // Check for time extension 
        //
        if ((fpReceiveBuffer->Header.bStatus & 0xC0) == 0x80) {
            FixedDelay(fpReceiveBuffer->Header.bError * fpICCDevice->WaitTime * fpICCDevice->etu);  
        } else {
            break;
        }

        Iterations--;

    } while (Iterations);

    //
    // Save the last cmd status 
    //
    fpICCDevice->bStatus = fpReceiveBuffer->Header.bStatus;
    fpICCDevice->bError = fpReceiveBuffer->Header.bError;

    //
    // Processed without error if Zero
    //
    if (fpReceiveBuffer->Header.bStatus & 0xC0) {
        Status = EFI_DEVICE_ERROR;

        if ((fpReceiveBuffer->Header.bStatus & 0x3) == 0x2) {        
            Status = EFI_NOT_FOUND;
        }

    }

    if (Iterations && !EFI_ERROR(Status)) {

        //
        // Update the Data
        //
        MemCopy((UINT8 *)&(fpReceiveBuffer->Header.Data), 
                (UINT8 *)&(fpICCDevice->bProtocolNum), 
                sizeof(RDR_TO_PC_PARAMETERS_T1_STRUC) - 9);

    } else {

        Status = EFI_DEVICE_ERROR;
    }

exit_RDRToPCParameters:

    gSequence++;

    USB_MemFree(fpReceiveBuffer, 
                (UINT8)GET_MEM_BLK_COUNT(sizeof(RDR_TO_PC_PARAMETERS_T1_STRUC))
                );

    USB_DEBUG (DEBUG_LEVEL_3, " Status :  %r bStatus : %02X bError : %02X\n", Status, fpICCDevice->bStatus, fpICCDevice->bError);

    PrintPCParameters((UINT8 *)&(fpICCDevice->bProtocolNum));

    return Status;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   RDRToPCDataRateAndClockFrequency
//
// Description: RDR_TO_PC_DATARATEANDCLOCK cmd is issued. 
//
// Input:
//              IN DEV_INFO          *fpDevInfo,
//              IN ICC_DEVICE        *fpICCDevice
//
// Output:
//              EFI_STATUS
//         
// Notes:       Returns dwClockFrequency and dwDataRate. 
//              See section 6.2.5 of CCID spec Rev 1.1 for more details.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
RDRToPCDataRateAndClockFrequency(
    IN DEV_INFO          *fpDevInfo,
    IN ICC_DEVICE        *fpICCDevice
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC  *fpReceiveBuffer;
    UINT32                        dwData;
    UINT8                        Iterations = 3;    

    fpReceiveBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC)));
    ASSERT(fpReceiveBuffer);
    if (!fpReceiveBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)fpReceiveBuffer, sizeof(RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC), 0);

    do {

        //
        // Read the PCSlot Status
        //
        fpReceiveBuffer->bMessageType = RDR_TO_PC_DATARATEANDCLOCK;
        fpReceiveBuffer->dwLength = 8;
        fpReceiveBuffer->bSlot = fpICCDevice->Slot;
        fpReceiveBuffer->bSeq = gSequence;

        dwData = USBCCIDIssueBulkTransfer(fpDevInfo, BIT7, 
                                        (UINT8 *)fpReceiveBuffer, 
                                        sizeof(RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC));

        //
        // Handle Error if any. This error is due to blk transfer
        //
        if (!dwData) {
            Status = EFI_DEVICE_ERROR;
            goto exit_RDRToPCDataRateAndClockFrequency;
        }

        //
        // Check for time extension 
        //
        if ((fpReceiveBuffer->bStatus & 0xC0) == 0x80) {
            FixedDelay(fpReceiveBuffer->bError * fpICCDevice->WaitTime * 1000);  
        } else {
            break;
        }

        Iterations--;

    } while (Iterations);


    //
    // Processed without error if Zero
    //
    if (fpReceiveBuffer->bStatus & 0xC0) {
        Status = EFI_DEVICE_ERROR;

        if ((fpReceiveBuffer->bStatus & 0x3) == 0x2) {        
            Status = EFI_NOT_FOUND;
        }
    }

    if (Iterations && !EFI_ERROR(Status)) {

         fpICCDevice->dwClockFrequency = fpReceiveBuffer->dwClockFrequency; 
         fpICCDevice->dwDataRate = fpReceiveBuffer->dwDataRate;

    } else {

        Status = EFI_DEVICE_ERROR;

    }

    //
    // Save the last cmd status 
    //
    fpICCDevice->bStatus = fpReceiveBuffer->bStatus;
    fpICCDevice->bError = fpReceiveBuffer->bError;

exit_RDRToPCDataRateAndClockFrequency:

    gSequence++;

    USB_MemFree(fpReceiveBuffer, 
                (UINT8)GET_MEM_BLK_COUNT(sizeof(RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC))
                );

    USB_DEBUG (DEBUG_LEVEL_3, " Status :  %r bStatus : %02X bError : %02X\n", 
                Status, fpICCDevice->bStatus, fpICCDevice->bError);

    USB_DEBUG (DEBUG_LEVEL_3, " dwClockFrequency :  %4x dwDataRate : %4x\n", 
                fpICCDevice->dwClockFrequency, fpICCDevice->dwDataRate);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   TxRxT1Adpu
//
// Description: Transmit/Receive T1 ADPU
//
// Input:
//              IN DEV_INFO         *fpDevInfo,
//              IN ICC_DEVICE       *fpICCDevice,
//              IN UINT32           CmdLength,
//              IN UINT8            *CmdBuffer,
//              IN UINT8            BlockWaitingTime,
//              IN UINT16           LevelParameter    
//
// Output: 
//
//
// Notes: 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
TxRxT1Adpu (
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice,
    IN UINT32           CmdLength,
    IN UINT8            *CmdBuffer,
    OUT UINT32          *ResponseLength,
    OUT UINT8           *ResponseBuffer
)
{

    EFI_STATUS  Status;

    //
    // Issue the cmd
    //
    Status = PCToRDRXfrBlock(fpDevInfo, fpICCDevice, CmdLength, CmdBuffer, 0, 0);
    
    if (EFI_ERROR(Status)){
        return Status;        
    }

    //
    // Get the response
    //
    Status = RDRToPCDataBlock(fpDevInfo, fpICCDevice, ResponseLength, ResponseBuffer);

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:       TxRxT1TDPUChar
//
// Description:     Transmit/Receive T1 TDPU/Character 
//
// Input:
//    IN DEV_INFO         *fpDevInfo,
//    IN ICC_DEVICE       *fpICCDevice,
//    IN UINT32           CmdLength,
//    IN UINT8            *CmdBuffer,
//    IN UINT8            ISBlock,
//    OUT UINT32          *ResponseLength,
//    OUT UINT8           *ResponseBuffer   
//
// Output: 
//
//
// Notes: 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
TxRxT1TDPUChar (
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice,
    IN UINT32           CmdLength,
    IN UINT8            *CmdBuffer,
    IN UINT8            ISBlock,
    IN OUT UINT32       *ResponseLength,
    OUT UINT8           *ResponseBuffer
)
{

    EFI_STATUS  Status;
    UINT8       Pcb = ISBlock;
    UINT32      InfLength = CmdLength;
    UINT8       *InfBuffer = CmdBuffer;

    UINT32      IBlockFrameLength = 0;      // Used for I-Block
    UINT8       *IBlockFrame = NULL;

    UINT32      SendBlockFrameLength = 0;   // Place holder for the block currently sent
    UINT8       *SendBlockFrame = NULL;

    UINT32      RBlockFrameLength = 0;      // Used for R-Block
    UINT8       *RBlockFrame = NULL;

    UINT32      SBlockFrameLength = 0;      // Used for S-Block
    UINT8       *SBlockFrame = NULL;

    UINT32      lResponseLength = 0;        // Response buffer for all the blocks I/S/R
    UINT32      OrglResponseLength = 0;     
    UINT8       *lResponseBuffer;

    UINT8       wLevelParameter = 0;

    UINT8       ReceiveStatus;
    UINT8       bBWIByte = 0;    

    UINT32      UserBufferLength = *ResponseLength;
    UINT32      lResponseBufferAddDataPtr = 0;

    BOOLEAN T1Char = ((SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor)->dwFeatures & TDPU_LEVEL_EXCHANGE ? FALSE : TRUE;    
    UINT8     *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return EFI_DEVICE_ERROR;
    }
    // Initialize Chaining is off
    fpICCDevice->Chaining = FALSE;
    *ResponseLength  = 0;

    // Update Pcb with Nas only for IBlocks
    if (!ISBlock) {
        Pcb = ((fpICCDevice->NaSInterface & 1) << 6);
    }

    Status = ConstructBlockFrame(fpDevInfo, fpICCDevice, 
                                fpICCDevice->NAD, Pcb, 
                                CmdLength, CmdBuffer, 
                                &wLevelParameter, &IBlockFrameLength, 
                                &IBlockFrame
                                );        


    if (EFI_ERROR(Status)) { 
        return Status;
    }

    SendBlockFrameLength = IBlockFrameLength;
    SendBlockFrame = IBlockFrame;

    if (UserBufferLength < 2)  lResponseLength = 2;

    lResponseLength += (UserBufferLength + 3 + (fpICCDevice->EpilogueFields == 0 ? 1 :  2));

    lResponseBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(lResponseLength));
    ASSERT(lResponseBuffer);
    if (!lResponseBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill(lResponseBuffer, lResponseLength, 0);    

    OrglResponseLength = lResponseLength;

    fpICCDevice->T1CharCmdDataPhase = TRUE; // Always Cmd Phase first

    do {

        Status = PCToRDRXfrBlock(fpDevInfo, fpICCDevice, 
                                SendBlockFrameLength, SendBlockFrame, 
                                bBWIByte, wLevelParameter
                                );

        if (EFI_ERROR(Status)){
            break;        
        }

        //
        // Get the response
        //
        lResponseLength = OrglResponseLength - lResponseBufferAddDataPtr;
        Status = RDRToPCDataBlock(fpDevInfo, fpICCDevice, &lResponseLength, lResponseBuffer + lResponseBufferAddDataPtr);

        if (EFI_ERROR(Status)){
            break;        
        }

        // Check for errors
        ReceiveStatus = HandleReceivedBlock(fpDevInfo, fpICCDevice, 
                                            IBlockFrameLength, IBlockFrame, 
                                            SendBlockFrameLength, SendBlockFrame, 
                                            lResponseBuffer
                                            );        

        bBWIByte = 0;

        switch (ReceiveStatus) {

            case BLOCK_TRANSMISION_SUCCESS:
                break;
    
            case RESEND_BLOCK:
                break;

            case SEND_R_BLOCK_1:
            case SEND_R_BLOCK_0:

                // Check if Chaining is in progress
                if (fpICCDevice->Chaining) {

                    // Copy the data from lResponseBuffer to the user buffer
                    //
                    // If success copy the data to Response buffer
                    //
                    if (lResponseBuffer[2] && ((UserBufferLength - *ResponseLength) < lResponseBuffer[2])) {
                        Status = EFI_BUFFER_TOO_SMALL;        
                    }

                    MemCopy(lResponseBuffer+3, ResponseBuffer + *ResponseLength, lResponseBuffer[2]);
                    *ResponseLength +=  lResponseBuffer[2];
                    lResponseBufferAddDataPtr = 0;          // Reset to use the lResponseBuffer from the beginning
                    
                    // Clear out the PCB/length feild so that by mistake the buffer is interpreted as valid data
                    lResponseBuffer[1] = 0;
                    lResponseBuffer[2] = 0;
                    lResponseLength = OrglResponseLength;
                    
                }
                Status = ConstructBlockFrame(fpDevInfo, fpICCDevice,    
                                            fpICCDevice->NAD, ReceiveStatus == SEND_R_BLOCK_1 ? 0x80 | 0x10 : 0x80, 
                                            0, NULL, &wLevelParameter, 
                                            &RBlockFrameLength, &RBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }
                SendBlockFrameLength = RBlockFrameLength;
                SendBlockFrame = RBlockFrame;
                fpICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            case I_BLOCK_RESEND:

                Status = ConstructBlockFrame(fpDevInfo, fpICCDevice, 
                                            fpICCDevice->NAD, Pcb, CmdLength, 
                                            CmdBuffer, &wLevelParameter, 
                                            &IBlockFrameLength, &IBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }
                SendBlockFrameLength = IBlockFrameLength;
                SendBlockFrame = IBlockFrame;
                fpICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            case WTX_RESPONSE:

                bBWIByte = lResponseBuffer[3];

                Status = ConstructBlockFrame(fpDevInfo, fpICCDevice, 
                                            fpICCDevice->NAD, WTX_RESPONSE, 
                                            lResponseBuffer[2], lResponseBuffer + 3, 
                                            &wLevelParameter, &SBlockFrameLength, 
                                            &SBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }

                SendBlockFrameLength = SBlockFrameLength;
                SendBlockFrame = SBlockFrame;
                fpICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            case GET_DATA_T1_CHAR:
                
                //
                // Issue a PCToRDRXfrBlock with dwLength to zero. 
                // Check Page 68 of CCID spec Rev 1.1, Apr 22, 2005
                //

                SendBlockFrameLength = 0;
                // Assumption : only LRC is supported
                wLevelParameter = lResponseBuffer[2] + 1; 

                //
                // Since the prologue is received in the first three bytes increment 
                // the address so that data is recived after that  
                //
                lResponseBufferAddDataPtr += 3;   

                //
                // Indicate it is data phase now                  
                //
                fpICCDevice->T1CharCmdDataPhase = FALSE;  
                break;

            case IFS_RESPONSE:
                Status = ConstructBlockFrame(fpDevInfo, fpICCDevice, 
                                            fpICCDevice->NAD, IFS_RESPONSE, 
                                            lResponseBuffer[2], lResponseBuffer + 3, 
                                            &wLevelParameter, &SBlockFrameLength, 
                                            &SBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }

                SendBlockFrameLength = SBlockFrameLength;
                SendBlockFrame = SBlockFrame;
                fpICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            case ABORT_RESPONSE:
                 Status = ConstructBlockFrame(fpDevInfo, fpICCDevice, 
                                            fpICCDevice->NAD, ABORT_RESPONSE, 
                                            lResponseBuffer[2], lResponseBuffer + 3, 
                                            &wLevelParameter, &SBlockFrameLength, 
                                            &SBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }

                SendBlockFrameLength = SBlockFrameLength;
                SendBlockFrame = SBlockFrame;
                fpICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            default:
                break;
                        
        }

        if (ReceiveStatus == BLOCK_TRANSMISION_SUCCESS) {
            break;
        }       
    }while (1);

    //
    // If success copy the data to Response buffer for the last I-Block that was received.
    //
    if (lResponseBuffer[2] && ((UserBufferLength - *ResponseLength) < lResponseBuffer[2])) {
        Status = EFI_BUFFER_TOO_SMALL;        
    }

    if (lResponseBuffer[2] && ((UserBufferLength - *ResponseLength) >= lResponseBuffer[2])) {
        MemCopy(lResponseBuffer+3, ResponseBuffer + *ResponseLength, lResponseBuffer[2]);
        *ResponseLength +=  lResponseBuffer[2];
    }

    //
    // Free up memory I-Block allocated here
    //
    if (IBlockFrame && IBlockFrameLength) {
        USB_MemFree(IBlockFrame, (UINT8)GET_MEM_BLK_COUNT(IBlockFrameLength));
    }

    //
    // Free up S-Block memory allocated here
    //
    if (SBlockFrame && SBlockFrameLength) {
        USB_MemFree(SBlockFrame, (UINT8)GET_MEM_BLK_COUNT(SBlockFrameLength));
    }

    if (lResponseBuffer && OrglResponseLength) {
        USB_MemFree(lResponseBuffer, (UINT8)GET_MEM_BLK_COUNT(OrglResponseLength));
    }



    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   ConstructBlockFrame
//
// Description: Construct the Block Frame for the CCID
//
// Input:
//              IN DEV_INFO         *fpDevInfo,
//              IN ICC_DEVICE       *fpICCDevice,
//              IN UINT8            Nad,
//              IN UINT8            PCB,
//              IN UINT32           InfLength,
//              IN UINT8            *InfBuffer,
//              OUT UINT8           *wLevelParameter,
//              OUT UINT32          *BlockFrameLength,
//              OUT UINT8           **BlockFrame
//
// Output: 
//              EFI_STATUS      EFI Status
//
// Notes: 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ConstructBlockFrame(
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice,
    IN UINT8            Nad,
    IN UINT8            PCB,
    IN UINT32           InfLength,
    IN UINT8            *InfBuffer,
    OUT UINT8           *wLevelParameter,
    OUT UINT32          *BlockFrameLength,
    OUT UINT8           **BlockFrame
)
{

    UINT32  BufLengthRequired = InfLength + 3 + 
                                (fpICCDevice->EpilogueFields == 0 ? 1 :  2);
    UINT8   *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return EFI_DEVICE_ERROR;
    }

    //
    // Check if the input buffer if already allocated is enough for the current case. 
    // If not free it up and allocate again.
    //
    
    if (BufLengthRequired > *BlockFrameLength) {
        if (*BlockFrame) {
            USB_MemFree(*BlockFrame, (UINT8)GET_MEM_BLK_COUNT(*BlockFrameLength));
            *BlockFrame = NULL;

        }
    }

    *BlockFrameLength = InfLength + 3 + (fpICCDevice->EpilogueFields == 0 ? 1 :  2);

    //
    // if BlockFrame is NULL only then allocate memory. Assumption is if Memory 
    // has been allocated before then it is sufficent enough for the length needed.
    //
    if (!*BlockFrame) {
        //
        // Allocate length needed to contruct the Block Frame
        //
        *BlockFrame = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(*BlockFrameLength));

        if (!*BlockFrame) {
            return EFI_OUT_OF_RESOURCES;
        }
    }

    MemFill(*BlockFrame, *BlockFrameLength, 0);    

    (*BlockFrame)[0] = Nad;
    (*BlockFrame)[1] = PCB;
    (*BlockFrame)[2] = InfLength;

    if (InfLength) {
        MemCopy((UINT8 *)InfBuffer, (UINT8 *)(*BlockFrame + 3), InfLength);
    }

    //
    // Update Checksum
    //
    (*BlockFrame)[*BlockFrameLength - 1] = 0;

    if (fpICCDevice->EpilogueFields == 0) {
        CalculateLRCChecksum(*BlockFrame, *BlockFrameLength);
    } else {
        return EFI_UNSUPPORTED;
    }

    //
    // For Character transfer update wLevelParameter also
    //
    if (!(((SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor)->dwFeatures & 0x70000)) {
        *wLevelParameter = 3;
    }

    return EFI_SUCCESS;    

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   HandleReceivedBlock
//
// Description: Process the Recevied data from CCID device
//
// Input:
//              IN DEV_INFO         *fpDevInfo,
//              IN ICC_DEVICE       *fpICCDevice,
//              IN UINT32           OriginalBlockFrameLength,
//              IN UINT8            *OriginalBlockFrame,
//              IN UINT32           SentBlockFrameLength,
//              IN UINT8            *SentBlockFrame,
//              IN UINT8            *ReceivedBlockFrame
//
// Output: 
//
//
// Notes: 
//      For Character exchange control will come twice for S(Response), I-Block with M bit set. So while counting
//      number of exchnages this needs to be taken care of.
//      Refer to ISO/IEC 7816-1 First edition 1998-10-15 for different scenarios mentioned in this function.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8   
HandleReceivedBlock (
    IN DEV_INFO         *fpDevInfo,
    IN ICC_DEVICE       *fpICCDevice,
    IN UINT32           OriginalBlockFrameLength,
    IN UINT8            *OriginalBlockFrame,
    IN UINT32           SentBlockFrameLength,
    IN UINT8            *SentBlockFrame,
    IN UINT8            *ReceivedBlockFrame
)
{

    UINT8   ReturnParameter = BLOCK_TRANSMISION_SUCCESS;
    BOOLEAN T1Char = ((SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor)->dwFeatures & 0x70000 ? FALSE : TRUE;
    UINT8     *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return BLOCK_TRANSMISSION_TERMINATE;
    }

    // It is easy to support T1 TDPU & CHAR as they are almost same except that 
    // prologue and data are received separatly in T1 Char.
    // The trick here will be that when data is received we can combine the 
    // previously received prologue and the INF/Epilogue received 
    // later so that it will be similar to T1 TDPU. Then all the processing will be same.

    if (!ReceivedBlockFrame){    // if no response

        if (fpICCDevice->RBlockCounter == 2) {
            return BLOCK_TRANSMISSION_TERMINATE;
        }


        
        // If I-Block sent before and no response, send R-Block with the expected I Block(N(R). Rule 7.1/Rule 7.6
        if (!(SentBlockFrame[1] & 0x80)) { 
            
            fpICCDevice->RBlockCounter++;

            if (fpICCDevice->NaSCard) {
             return SEND_R_BLOCK_0;
            } else {
                return SEND_R_BLOCK_1;
            }
        }
        
    }

    // Reset the RBlock Counter if the response we received isn't a R-Block.
    if ((ReceivedBlockFrame[1] & 0xC0) !=  RBLOCK) {
            fpICCDevice->RBlockCounter = 0;
    }

    //
    // Is the block received an I-Block?
    //
    if (!(ReceivedBlockFrame[1] & 0x80)) {

        //
        // It is T1 Char and also if in cmd phase handle it.
        //
        if (T1Char && fpICCDevice->T1CharCmdDataPhase)  { 

            // Save the N(s) from the card for later use.
            fpICCDevice->NaSCard = (ReceivedBlockFrame[1] & NSBIT) >> 6;

            // If data needs to be received
            if (ReceivedBlockFrame[2]){
                return GET_DATA_T1_CHAR;
            }  else {
                return BLOCK_TRANSMISION_SUCCESS;
            }            

        }

        // It is T1TDPU or it is T1 Char but in data phase

       
        // Is Mbit set, then nothing more to do
        if (!(ReceivedBlockFrame[1] & 0x20)) {
            //
            // Toggle N(S) bit only after a successful I Block Transmission
            //
            fpICCDevice->Chaining = FALSE;
            fpICCDevice->NaSInterface = !(fpICCDevice->NaSInterface);

            return BLOCK_TRANSMISION_SUCCESS;
        }
        else {
            // Since Mbit is set, Send R-Block with the next N(s) expected from card. Section 5, Rules 2.2 and 5
            
            fpICCDevice->Chaining = TRUE;

            if (fpICCDevice->NaSCard){
                return SEND_R_BLOCK_0;
            }
            else {
                return SEND_R_BLOCK_1;
            }
        }
    }

    // No difference between T1 Char and T1 Tdpu in R-phase

    //
    // Is the Block received is a R block?
    //
    if ((ReceivedBlockFrame[1] & 0xC0) ==  RBLOCK) {
        

        // Is there an error?
        if (ReceivedBlockFrame[1] & 0x03) {
            //Re-transmit it
            if ((SentBlockFrame[1] & 0xc0) == 0x00) {
                return  I_BLOCK_RESEND;
            }
            else {
                return RESEND_BLOCK;
            }
        }

        if (T1Char && fpICCDevice->T1CharCmdDataPhase) {
            return  GET_DATA_T1_CHAR;
        }

        if (fpICCDevice->RBlockCounter == 3) {
            fpICCDevice->RBlockCounter = 0;
            return BLOCK_TRANSMISSION_TERMINATE;
        }
        fpICCDevice->RBlockCounter++;

        if (fpICCDevice->Chaining == FALSE) {

            //
            // if the received  R-Block is same as the last sent I-Block AND Chaining is not in progress, resend I-Block. Scenario 8
            //
            if ((ReceivedBlockFrame[1] & 0x10) >> 4 == (fpICCDevice->NaSInterface & 1) << 6) {
                return I_BLOCK_RESEND;
            } 
            else {
                //
                // Scenario 11/12
                //
                if (fpICCDevice->NaSInterface & 1) {
                    return SEND_R_BLOCK_1;
                } else {
                    return SEND_R_BLOCK_0;
                }
            }
        }
        else { 
            //
            // Chaining is in progress...
            //
            //   
            // Scenario 5
            //
            if ((ReceivedBlockFrame[1] & 0x10) >> 4 != (fpICCDevice->NaSInterface & 1) << 6) {
                // return I_BLOCK;
            }
            //
            // Scenario 23
            //
            if (ReceivedBlockFrame[1]  == SentBlockFrame[1]) {
                if (ReceivedBlockFrame[1] & 0x10) {
                    return SEND_R_BLOCK_1;
                } else {
                    return SEND_R_BLOCK_0;
                }
            }
           
        }

        // We can try giving S-Synch also if it doesn't respond to R-Block. 
        // S-Synch can be done only for 2nd Iblock on-wards.
    }    

    //
    // Is the Block Received is a S block? 
    //
    if ((ReceivedBlockFrame[1] & 0xC0) == 0xC0) {

        switch (ReceivedBlockFrame[1]) {

            case IFS_REQUEST:

               if (T1Char && fpICCDevice->T1CharCmdDataPhase) {
                    ReturnParameter = GET_DATA_T1_CHAR;
                    break;
                }
                // Save the new IFSD data
                fpICCDevice->IFSD = ReceivedBlockFrame[3];
                ReturnParameter = IFS_RESPONSE;
                break;

            case IFS_RESPONSE:
                //
                // It is T1 Char and also if in cmd phase handle it.
                //
                if (T1Char && fpICCDevice->T1CharCmdDataPhase)  { 

                    // If data needs to be received
                    if (ReceivedBlockFrame[2]){
                        return GET_DATA_T1_CHAR;
                    }  else {
                        return BLOCK_TRANSMISION_SUCCESS;
                    }            
                }  
                break;

            case ABORT_REQUEST:
                    fpICCDevice->Chaining = FALSE;
                    ReturnParameter = ABORT_RESPONSE;
                    break;

            case ABORT_RESPONSE:
                break;

            case WTX_REQUEST:

                if (T1Char && fpICCDevice->T1CharCmdDataPhase) {
                    ReturnParameter = GET_DATA_T1_CHAR;
                    break;
                }

                ReturnParameter = WTX_RESPONSE;
                break;                

            case RESYNCH_RESPONSE:
                break;

            case WTX_RESPONSE:              // Won't be received from card. Card will only generate WTX request.
                break;        
            case RESYNCH_REQUEST:           // Card won't issue ReSynch
                break;
            default:
                break;

        }  
  
    }                

   return ReturnParameter;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   CalculateLRCChecksum
//
// Description: Calculates LRC checksum
//
// Input:
//              UINT8            *BlockFrame
//              UINT32            BlockFrameLength
//
// Output: 
//              ICC_DEVICE* or NULL
//
// Notes: 
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CalculateLRCChecksum (
    UINT8       *BlockFrame, 
    UINT32      BlockFrameLength
)
{
    UINT32  i = 0;

    for (; i < BlockFrameLength - 1; i++ ){
        BlockFrame[BlockFrameLength-1] ^= BlockFrame[i];
    }
    
    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetICCDevice
//
// Description: Search the linked list to find the ICC_DEVICE for the given slot #.
//
// Input:
//              DEV_INFO        *fpDevInfo
//              UINT8            Slot
//
// Output: 
//              ICC_DEVICE* or NULL
//
// Notes: 
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
    UINT8           *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    dlink = fpDevInfo->ICCDeviceList.pHead;

    for ( ; dlink; dlink = dlink->pNext) {

        fpICCDevice = OUTTER(dlink, ICCDeviceLink, ICC_DEVICE);

        //
        // Slot # matches
        //
        if (fpICCDevice->Slot == Slot) {
            if (((UINT8*)fpICCDevice < gUsbData->fpMemBlockStart) ||
                ((UINT8*)((UINTN)fpICCDevice + sizeof(ICC_DEVICE)) > MemBlockEnd)) {
                return NULL;
            }
            return fpICCDevice;
        }      
          
    }

    return NULL;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   UpdateATRDataInfo
//
// Description: The routine update the Transmision protocol supported and other 
//              timing related data
//
// Input: 
//              DEV_INFO           *fpDevInfo
//              ICC_DEVICE        *fpICCDevice
//
// Output: 
//              None
//
// Notes:       This function looks into ATR data and updates CLASS A/B/C information, 
//              calculates ETU, WaitTime etc
//        
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateATRDataInfo(
    DEV_INFO            *fpDevInfo,
    ICC_DEVICE          *fpICCDevice
)
{
    UINT8    bData;
    UINT8    i=1;

    //
    // T0 is mandatory
    //
    fpICCDevice->AtrData.T0 = fpICCDevice->RawATRData[i];
    fpICCDevice->AtrData.NumberofHystoricalBytes = fpICCDevice->RawATRData[i] & 0xF;
    i++;

    //
    // Update TA1
    //
    if (fpICCDevice->AtrData.T0 & 0x10) {
        fpICCDevice->AtrData.TA1 = fpICCDevice->RawATRData[i];
        fpICCDevice->AtrData.TA1Present = TRUE;
        i++;
    } else {
        //
        // Default value if TA1 is not present
        //
        fpICCDevice->AtrData.TA1 = 0x11;        
    }

    bData = fpICCDevice->AtrData.TA1;
    fpICCDevice->GlobalFi = FiFmaxDi[(bData >> 4) * 3];
    fpICCDevice->GlobalFmax = (UINT8)FiFmaxDi[(bData >> 4) * 3 + 1];
    fpICCDevice->GlobalDi = (UINT8)FiFmaxDi[(bData& 0xF) * 3 + 2];


    //
    // Update TB1
    //
    if (fpICCDevice->AtrData.T0 & 0x20) {
        fpICCDevice->AtrData.TB1 = fpICCDevice->RawATRData[i];
        fpICCDevice->AtrData.TB1Present = TRUE;
        i++;
    }

    //
    // Update TC1
    //
    if (fpICCDevice->AtrData.T0 & 0x40) {
        fpICCDevice->AtrData.TC1 = fpICCDevice->RawATRData[i];
        fpICCDevice->AtrData.TC1Present = TRUE;
        i++;
    }

    //
    // Update TD1
    //
    if (fpICCDevice->AtrData.T0 & 0x80) {
        fpICCDevice->AtrData.TD1 = fpICCDevice->RawATRData[i];
        fpICCDevice->AtrData.TD1Present = TRUE;
        i++;
    }

    if (fpICCDevice->AtrData.TD1) {

        //
        // Update TA2
        //
        if (fpICCDevice->AtrData.TD1 & 0x10) {
            fpICCDevice->AtrData.TA2 = fpICCDevice->RawATRData[i];
            fpICCDevice->AtrData.TA2Present = TRUE;
            fpICCDevice->SpecificMode = fpICCDevice->AtrData.TA2 & BIT7 ? TRUE : FALSE;
            i++;
        }

        //
        // Update TB2
        //
        if (fpICCDevice->AtrData.TD1 & 0x20) {
            fpICCDevice->AtrData.TB2 = fpICCDevice->RawATRData[i];
            fpICCDevice->AtrData.TB2Present = TRUE;
            i++;
        }

        //
        // Update TC2
        //
        if (fpICCDevice->AtrData.TD1 & 0x40) {
            fpICCDevice->AtrData.TC2 = fpICCDevice->RawATRData[i];
            fpICCDevice->AtrData.TC2Present = TRUE;
            i++;
        }

        //
        // Update TD2
        //
        if (fpICCDevice->AtrData.TD1 & 0x80) {
            fpICCDevice->AtrData.TD2 = fpICCDevice->RawATRData[i];
            fpICCDevice->AtrData.TD2Present = TRUE;
            i++;
        }
    }

    //
    // Check if T15 is present else only CLASS A is supported. 
    // By default CLASS A is supported
    //
    fpICCDevice->ClassABC = 1;            

    for (bData = 1;  bData < MAX_ATR_LENGTH ;){

        //
        // Is it T15?
        //
        if ((fpICCDevice->RawATRData[bData] & 0xF) == 0xF){
            fpICCDevice->ClassABC = fpICCDevice->RawATRData[bData + 1] & 0x3F;
            fpICCDevice->StopClockSupport = fpICCDevice->RawATRData[bData + 1] >> 5; 

            fpICCDevice->AtrData.TD15 = fpICCDevice->RawATRData[bData];
            fpICCDevice->AtrData.TD15Present = TRUE;

            fpICCDevice->AtrData.TA15 = fpICCDevice->RawATRData[bData + 1];
            fpICCDevice->AtrData.TA15Present = TRUE;

            break;
        } else {
            // We need info on how many Transmission Protocols are supported by the 
            // card and what are those. Use these loop to do that.
            if (bData > 1) {    // Skip T0
                i = fpICCDevice->TransmissionProtocolSupported;
                fpICCDevice->TransmissionProtocolSupported |=  ( 1 << (fpICCDevice->RawATRData[bData] & 0x0F));
                if (i != fpICCDevice->TransmissionProtocolSupported) { 
                    fpICCDevice->NumofTransmissionProtocolSupported++;          
                }
            }                        

            // No more valid TDx?
            if (!(fpICCDevice->RawATRData[bData] & 0x80)) break;
            bData += FindNumberOfTs(fpICCDevice->RawATRData[bData]);
        }
    }

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetDefaultProtocol
//
// Description: Find the First offerred Transmission protocol.
//
// Input: 
//              ICC_DEVICE        *fpICCDevice
//
// Output:
//              TRANSMISSION_PROTOCOL        
//
// Notes:       Section 8.2.3 ISO 7816-3 2006-11-01: TD1 encodes first offered protocol. 
//              If TD1 not present assume T0.
//    
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
TRANSMISSION_PROTOCOL GetDefaultProtocol (
    ICC_DEVICE        *fpICCDevice
)
{

    if (fpICCDevice->AtrData.TD1Present) {
        return fpICCDevice->AtrData.TD1 & 0xf;
    }

    return T0_PROTOCOL;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   FindBestTA1Value
//
// Description: CCID which doesn't perform "Automatic parameter config. based on ATR
//
// Input: 
//              DEV_INFO           *fpDevInfo
//              ICC_DEVICE        *fpICCDevice
//
// Output:
//              UINT8       Best TA1 value
//
// Notes:
//  1. Calculate the Baud rate using TA1 value
//
//  2. If in CCID bNumDataRatesSupported = 0 then any value between dwDatRate 
//     and dwMaxDataRate is supported
//
//  3. Check if ICC baud rate is less tha dwMaxDataRate. If yes use that.
//
//  4. If  bNumDataRatesSupported is not zero get all possible values and try to 
//     match it and use that value.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 
FindBestTA1Value (
    DEV_INFO        *fpDevInfo,
    ICC_DEVICE      *fpICCDevice
)
{

    UINT32      ICCBaudrate;
    UINT8       Di = fpICCDevice->GlobalDi;
	SMARTCLASS_DESC	*CCIDDescriptor = (SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor;
    UINT8       *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return 0;
    }
    //
    // If Automatic parameter conf. based on ATR data is 
    //
    if (CCIDDescriptor->dwFeatures & AUTO_PARAMETER_CONFIG) {
        return fpICCDevice->AtrData.TA1;
    }

    ICCBaudrate =   (fpICCDevice->GlobalFmax * 1000 * fpICCDevice->GlobalDi)/fpICCDevice->GlobalFi;      

    if (fpDevInfo->DataRates && fpDevInfo->ClockFrequencies) {
        /*
        // Find the match
        for (i = fpDevInfo->pCCIDDescriptor->bNumDataRatesSupported; i; --i) {
            // Since the values may not match exactly give some leeway
            if (ICCBaudrate  >= (fpDevInfo->DataRates[i] - 1000) && ICCBaudrate  <= (fpDevInfo->DataRates[i] + 1000)){                
                // See whether the matched baud rate can be achieved with the supported frequencies                
                for (j = fpDevInfo->pCCIDDescriptor->bNumDataRatesSupported; j; --j) {
                    if (fpICCDevice->GlobalFmax == fpDevInfo->ClockFrequencies[i]) break;
                }
                if (j) {
                    CalcBaudRate =                 
                }
                else {
                }
                break;
            }
        }
        */
    } else {
        if (ICCBaudrate <= CCIDDescriptor->dwMaxDataRate) {
            return fpICCDevice->AtrData.TA1;
        } else {
            //
            // Can we decrement the Di value and try to match it
            //
            for ( ; Di ; --Di){
                ICCBaudrate =   (fpICCDevice->GlobalFmax * 1000 * Di)/fpICCDevice->GlobalFi;                
                if (ICCBaudrate <= CCIDDescriptor->dwMaxDataRate) {
                    return ((fpICCDevice->AtrData.TA1 & 0xF0) | Di);
                }
            }
        }
    }

    //
    // Worst case return the default value. 
    // Actuall we should fail saying this CCID/ICC combination isn't supported.
    //
    return fpICCDevice->AtrData.TA1;        

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   CalculateTimingValues
//
// Description: Based on the agreed upon TA1 value and Transmission protocol 
//              calculate the timing values
//
// Input: 
//              DEV_INFO           *fpDevInfo
//              ICC_DEVICE        *fpICCDevice
//
// Output:
//              None
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CalculateTimingValues (
    DEV_INFO          *fpDevInfo,
    ICC_DEVICE        *fpICCDevice
)
{

    UINT8   NValue;
    UINT8   bData;
    UINT8    TDCount = 0;

    fpICCDevice->bmFindIndex = fpICCDevice->AtrData.TA1;

    //
    // NValue defaults to zero if TC1 not present
    //
    NValue = fpICCDevice->AtrData.TC1Present == TRUE ? fpICCDevice->AtrData.TC1 : 0;

    //
    // Calculate 1 etu in micro sec
    //
    fpICCDevice->etu = fpICCDevice->GlobalFi / (fpICCDevice->GlobalDi * fpICCDevice->GlobalFmax); 

    //
    // Extra Gaurd Time GT in etu units (section 8.3)
    //
    if (fpICCDevice->AtrData.TA15Present) {
        fpICCDevice->ExtraGuardTime = 12 + 
                                (NValue / fpICCDevice->GlobalFmax  * fpICCDevice->GlobalFi/ fpICCDevice->GlobalDi);
    } else {
        fpICCDevice->ExtraGuardTime = 12 + (NValue / fpICCDevice->GlobalFmax) ;          
    }

    // Update Wait Time  (see section 10.2)
    // WT = WI * 960 * Fi /f where WI is TC2
    // Default if TC2 is not present
    bData = 10;         

    if (fpICCDevice->AtrData.TC2Present) {
        bData = fpICCDevice->AtrData.TC2;
    }    

    //
    // Calculate WT (wait time between two characters) in ETU units
    //
    fpICCDevice->WTwaittime = 960 * fpICCDevice->GlobalFi/(fpICCDevice->GlobalFmax);


    // update Block Width time and Epilogue bit
    // BWT = 11etu + 2 ^ BWI * 960 * Fd /f  (Section 11.4.3)
    // Default BWI is 4. Bit 7:4 in first TB for T1 encodes BWI
    // Fd = 372 (sec section 8.1)

    // Default values (11.4.3)
    fpICCDevice->BWI  = 4;
    fpICCDevice->CWI =  13;
    fpICCDevice->IFSC = 32;
    fpICCDevice->IFSD = 32;
    fpICCDevice->NAD = 0;

    for (bData = 1;  bData < MAX_ATR_LENGTH; ){

        // Look for the First TD for T= 1. It should from TD2
        if (TDCount < 2) {
            if (fpICCDevice->RawATRData[bData] & 0x80) {
                TDCount++;
                bData += FindNumberOfTs(fpICCDevice->RawATRData[bData]);
                continue;
            } else {
                break;
            }
        }

        // Is it T1?
        if ((fpICCDevice->RawATRData[bData] & 0xF) == 0x1){

            if (fpICCDevice->RawATRData[bData] & 0x10) {
                fpICCDevice->IFSC = fpICCDevice->RawATRData[bData + 1];
            }

            if (fpICCDevice->RawATRData[bData] & 0x20) {
                fpICCDevice->BWI = (fpICCDevice->RawATRData[bData + 2] & 0xF0) >> 4;
                fpICCDevice->CWI = fpICCDevice->RawATRData[bData + 2] & 0xF;
            }

            // Section 11.4.4
            if (fpICCDevice->RawATRData[bData] & 0x40) {
                fpICCDevice->EpilogueFields = (fpICCDevice->RawATRData[bData + 3] & 0x1);
            }

            break;
        }

        //
        // No more valid TDx?
        //
        if (!(fpICCDevice->RawATRData[bData] & 0x80)) break;

        bData += FindNumberOfTs(fpICCDevice->RawATRData[bData]);

    }    

    //
    // Block Widthtime in ETU units
    //
    fpICCDevice->BWT = ((1 << (fpICCDevice->BWI - 1)) * 960 * 372 /(fpICCDevice->GlobalFmax)) + 11;

    PrintTimingInfo(fpICCDevice);

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IssuePPSCmd
//
// Description: Issue PPS cmd to select T0/T1
//
// Input: 
//              DEV_INFO        *fpDevInfo
//              ICC_DEVICE      *fpICCDevice
//              UINT8           *Data : Points to the buffer which is sent to CCID. 
//                                      Refer Section 9.2 of 7816-3 spec for the format
//
// Output:
//              EFI_STATUS
//
// Notes:
//              This command is issued to CCID which doesn't support AUTO_PARAMETER_CONFIG 
//              or when default values or not acceptable
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IssuePPSCmd(
    DEV_INFO            *fpDevInfo,
    ICC_DEVICE          *fpICCDevice,
    UINT8               *Data,
    UINT8               DataLength
)
{

    EFI_STATUS    Status = EFI_SUCCESS;
    UINT8        *ResponseBuffer;
    UINT32        ResponseLength = DataLength;
    SMARTCLASS_DESC	*CCIDDescriptor = (SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor;
    UINT8        *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return EFI_DEVICE_ERROR;
    }    
    //
    // Allocate memory for receiving data
    //
    ResponseBuffer = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(DataLength));
    ASSERT(ResponseBuffer);
    if (!ResponseBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    MemFill((UINT8 *)ResponseBuffer, DataLength, 0);


    //
    //Check what level of Transmission Protocol is supported
    //
    ResponseLength = 0;
    if (!(CCIDDescriptor->dwFeatures & 0x70000)){
        ResponseLength = 2;                                 // For Character exchange only 2 bytes expected.
    }  


    Status = PCToRDRXfrBlock(fpDevInfo, fpICCDevice, DataLength, Data, 0, ResponseLength);
    if (CCIDDescriptor->dwFeatures & 0x70000){
        ResponseLength = 4;                                 // For TDPU expected data is 4
    }
    Status = RDRToPCDataBlock(fpDevInfo, fpICCDevice, &ResponseLength, ResponseBuffer);

    // If length is not same and only Character level Transmission is supported, 
    // issue another XfrBlock cmd to get the rest of the data
    if ((ResponseLength != DataLength) && !(CCIDDescriptor->dwFeatures & 0x70000)) {

        DataLength = ResponseLength;
        ResponseLength = 2;
        Status = PCToRDRXfrBlock(fpDevInfo, fpICCDevice, 0, Data, 0, ResponseLength);
        Status = RDRToPCDataBlock(fpDevInfo, fpICCDevice, &ResponseLength, ResponseBuffer + DataLength);
    
    }

    //
    // I/P and O/P should be identical for success
    //
    USB_MemFree(ResponseBuffer, (UINT8)GET_MEM_BLK_COUNT(DataLength));

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   VoltageSelection
//
// Description: Based on the dwFeatures register setting, power up CCID/ICC
//
// Input:
//              DEV_INFO           *fpDevInfo,
//              ICC_DEVICE        *fpICCDevice
//
// Output:
//              EFI_STATUS   
//
// Notes:       Based on dwFeatures value from SMART Class Descriptor either 
//              do an automatic Power-on or go through a manual
//              power up sequence and then callect the ATR data.
//    
//    
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
VoltageSelection(
    DEV_INFO          *fpDevInfo,
    ICC_DEVICE        *fpICCDevice
)
{

    EFI_STATUS   Status = EFI_DEVICE_ERROR;
    EFI_STATUS   ATRStatus = EFI_DEVICE_ERROR;
	SMARTCLASS_DESC	*CCIDDescriptor = (SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor;
    //
    // Get all voltage level supported by CCID
    //
    UINT8        VoltageLevelCCID = CCIDDescriptor->bVoltageSupport;        
    //
    // Select the lowest voltage
    //
    UINT8        VoltageMask = VOLT_18;                                                
    //
    // Successful poweron will result in ATR data
    //
    UINT32       BufferLength = MAX_ATR_LENGTH;                                        
    UINT8        *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return EFI_DEVICE_ERROR;
    }
    //
    // Make sure the first selection is valid
    //
    do {

        if (VoltageLevelCCID & VoltageMask) {
            break;
        }

        VoltageMask = VoltageMask >> 1;

    }while (VoltageMask);

    //
    // If Automatic Voltage selection is supported go for it. 
    // Discard the initialization done above
    if (CCIDDescriptor->dwFeatures & AUTO_ACTIVATION_VOLT_SELECTION){
        //
        // Automatic Voltage selection is supported            
        //
        VoltageLevelCCID = AUTO_VOLT;
        VoltageMask = 0;
    }

    do {

        //
        // Issue the cmd to Power it up
        //
        Status = PCtoRDRIccPowerOn (fpDevInfo, 
                                    fpICCDevice, 
                                    ((VoltageLevelCCID & VoltageMask) == 4) ?  3 : VoltageMask);

        if(EFI_ERROR(Status)) { 
            break;
        }

        //
        // Get the response to IccPoweron
        //
        BufferLength = MAX_ATR_LENGTH;
        Status = RDRToPCDataBlock ( fpDevInfo, 
                                    fpICCDevice, 
                                    &BufferLength, 
                                    fpICCDevice->RawATRData
                                    );

        //
        // if successfully powered up, ATR data should be available
        //
        if (!EFI_ERROR(Status) && BufferLength) {

            fpICCDevice->ConfiguredStatus |= (ICCPRESENT | VOLTAGEAPPLIED | ATRDATAPRESENT);

            PrintATRData(fpICCDevice->RawATRData);
        
            // From the ATR data, get the required information
            UpdateATRDataInfo(fpDevInfo, fpICCDevice);

            // ATR data got successfully and configured successfully. 
            ATRStatus = EFI_SUCCESS;
            break;

        }

        //
        // if Card not present    
        //
        if ((fpICCDevice->bStatus & 7) == 2) {
            Status = EFI_NOT_FOUND;
            break;
        }

        //
        // ICC is present but some error
        //
        fpICCDevice->ConfiguredStatus |= ICCPRESENT;

        //
        // Card present but voltage selection is not OK. Power it off and select next voltage
        //
        Status =  PCtoRDRIccPowerOff (fpDevInfo,  fpICCDevice);
        if (EFI_ERROR(Status)) break;

        Status = RDRToPCSlotStatus(fpDevInfo, fpICCDevice);
        if (EFI_ERROR(Status)) break;

        VoltageMask = VoltageMask >> 1;

        //
        // 10 msec delay before applying the next power class Spec 6.2.3
        //
        FixedDelay (10 * 1000);

    } while (VoltageMask);

    // Return the status of the ATR data read and configuration
    return ATRStatus;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   RateAndProtocolManagement
//
// Description: Based on the ATR data and the dwFeature register contend 
//              do the Rate and Protocol programming
//
// Input:
//              DEV_INFO           *fpDevInfo
//              ICC_DEVICE        *fpICCDevice
//
// Output:
//              EFI_STATUS
//
// Notes:       Based on data received from Power-on sequence (ATR data) and dwFetaures value, 
//              Speed of communicatin is established.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
RateAndProtocolManagement(
    DEV_INFO          *fpDevInfo,
    ICC_DEVICE        *fpICCDevice
)
{

    EFI_STATUS              Status = EFI_SUCCESS;
    PROTOCOL_DATA_T1        Data = {0};
    UINT8                   PPSData[] = {0xFF, 0x10, 0x11, 0x00};        
    UINT8                   Counter;
	SMARTCLASS_DESC			*CCIDDescriptor = (SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor;
    UINT32                  ClockFrequency = CCIDDescriptor->dwMaximumClock;
    UINT32                  DataRate = CCIDDescriptor->dwMaxDataRate;
    BOOLEAN                 FlagToIssueSetParameters = FALSE;
    TRANSMISSION_PROTOCOL   FirstOfferredProtocol;
    UINT8                   DefaultTA1 = fpICCDevice->AtrData.TA1;
    UINT8                   SetIFS[] = {0xFC};
    UINT32                  ResponseLength;
    UINT8                   ResponseBuffer[20];
    UINT32                  ExchangeLevel = (CCIDDescriptor->dwFeatures & 0x70000);
    UINT8                   *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return EFI_DEVICE_ERROR;
    }    
    FirstOfferredProtocol = GetDefaultProtocol(fpICCDevice);

    fpICCDevice->bProtocolNum = (UINT8)FirstOfferredProtocol;

    //
    // Check whether TA1 value is good enough for the reader. If not get the right value
    //
    fpICCDevice->AtrData.TA1 = FindBestTA1Value(fpDevInfo, fpICCDevice);    


    //
    // Check if more than one transmission protocol is supported. 
    // If yes then there may be a need for PPSCmd (ISO 7816-3:2006(E) Sec: 6.3.1)
    // Check if Automatic PPS negotiation done by CCID or not. If not issue one.
    // If TA2 is present Card is in Specific mode. So no need for PPS (7816-3:2006 see sec 6.3 fig 4)
    //

    // When PPS exchange must be made? (Page 19 CCID Rev 1.1) 
    // 1. If both AUTO_PPS_NEGOTIATION_CCID AND AUTO_PPS_NEGOTIATION_ACTIVE are not set PPS must be given in case of TDPU or Character
    //                          OR
    // 2. if AUTO_PPS_NEGOTIATION_ACTIVE is present AND TA2 not present AND the preferred protocol isn't USE_T0_T1_PROTOCOL

    if (((CCIDDescriptor->dwFeatures & (AUTO_PPS_NEGOTIATION_CCID | AUTO_PPS_NEGOTIATION_ACTIVE)) == 0 &&
            (ExchangeLevel <= 0x10000 ) && !fpICCDevice->AtrData.TA2Present) ||
        ((CCIDDescriptor->dwFeatures & AUTO_PPS_NEGOTIATION_ACTIVE) && !fpICCDevice->AtrData.TA2Present && 
            fpICCDevice->NumofTransmissionProtocolSupported > 1 && FirstOfferredProtocol != USE_T0_T1_PROTOCOL)) {
        //
        // Update PPS data if in case PPSCmd needs to be issued
        //
        PPSData[1] |= FirstOfferredProtocol;

        //
        // Update PPS2
        //
        PPSData[2] = fpICCDevice->AtrData.TA1;        
    
        //
        // Update checksum
        //
        for (Counter = 0; Counter < sizeof (PPSData) - 1; Counter++) {
            PPSData[sizeof (PPSData) - 1] ^= PPSData[Counter];
        }
    
        Status = IssuePPSCmd(fpDevInfo, fpICCDevice, PPSData, sizeof (PPSData));
    }
          
    if (CCIDDescriptor->dwFeatures & AUTO_PARAMETER_CONFIG) {   

        //
        // Issue GetParameters to get the Transmission Protocol and other parameters
        //
        Status = PCToRDRGetParameters(fpDevInfo, fpICCDevice);
        if (EFI_ERROR(Status)) return Status;
    
        Status = RDRToPCParameters(fpDevInfo, fpICCDevice);
        if (EFI_ERROR(Status)) return Status;        

        fpICCDevice->ExtraGuardTime = fpICCDevice->bGuardTime;
        fpICCDevice->WTwaittime = fpICCDevice->bWaitingInteger;
        fpICCDevice->IFSC =  fpICCDevice->bIFSC;
        fpICCDevice->NAD = fpICCDevice->nNadValue;

    } else {

        //
        // Now that the TA1 value and the protocol has been finalized, 
        // It is time to calculate the different timing parameters.
        //
        CalculateTimingValues (fpDevInfo, fpICCDevice);
    }

    //
    //If Automatic Parameters config. based on ATR data is not 
    //supported then issue SetParameters cmd
    //
    if (!(CCIDDescriptor->dwFeatures & AUTO_PPS_NEGOTIATION_ACTIVE)){  // 0x80

        //
        // Use the superset of the T0/T1 structure (ie T1 structure) even if it is T0. It should work.
        //
        Data.bmFindDindex = fpICCDevice->bmFindIndex;
        Data.bmTCCKST1 = fpICCDevice->bProtocolNum == 0  ? 0 : (fpICCDevice->EpilogueFields | 0x10);
        Data.bGuardTimeT1 = fpICCDevice->ExtraGuardTime;

        Data.bWaitingIntergersT1 = fpICCDevice->bProtocolNum == 0  ? 
                                fpICCDevice->WTwaittime : (fpICCDevice->BWI << 4 | fpICCDevice->CWI);

        Data.bClockStop = fpICCDevice->bClockStop;
        Data.bIFSC = fpICCDevice->IFSC;
        Data.bNadValue = fpICCDevice->NAD;
            
        Status = PCToRDRSetParameters(fpDevInfo, fpICCDevice, fpICCDevice->bProtocolNum, (VOID *)&Data);

        if (!EFI_ERROR(Status)){
            Status = RDRToPCParameters(fpDevInfo, fpICCDevice);
        } else {
            //
            // Handle failure cases. Look at it later.
            //
        }     
    }

    //
    // Based on T0 or T1 update Waittime. For T0 use WTWaittime, for T1 use BWT. 
    //
    if (fpICCDevice->bProtocolNum) {
        fpICCDevice->WaitTime = fpICCDevice->BWT;
    } else {
        fpICCDevice->WaitTime = fpICCDevice->WTwaittime;            
    }

    //
    // If Automatic ICC Clock Freq AND Automatic Buad Rate selection 
    // isn't supported issue SetDataRateAndClock cmd
    //
    if (!(CCIDDescriptor->dwFeatures & (AUTO_BAUD_RATE_SELECTION |AUTO_ICC_CLOCK_FREQ))){

    }

    //
    // Check if IFSC/IFSD needs to be increased. Default value is 0x20. T1 and TDPU/Char needs this cmd.
    //
    if (fpICCDevice->bProtocolNum){    
        switch(CCIDDescriptor->dwFeatures & 0x70000) { 
            case CHARACTER_LEVEL_EXCHANGE:
                // Both SUZCR90 and O2Micro oz77c6l1 didn't respond to SBlock call below without this delay
                FixedDelay(10 * 1000);      // 10msec delay. No break. Let the flow continue below.
            case TDPU_LEVEL_EXCHANGE:
              ResponseLength = 1;
                SetIFS[0] = (UINT8)CCIDDescriptor->dwMaxIFSD;          
                Status = TxRxT1TDPUChar (fpDevInfo, fpICCDevice, sizeof (SetIFS), SetIFS, IFS_REQUEST, &ResponseLength, ResponseBuffer);
                // Update the received IFSD
                if (!EFI_ERROR(Status) && ResponseLength == 1){
                    fpICCDevice->IFSD = ResponseBuffer[0];
                }
                break;
            default:
                break;
        }
    } 
    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:    ConfigureCCID
//
// Description: This function powers up, sets the clock/rate etc 
//              (configure CCID based on device capability)
//
// Input: 
//              DEV_INFO           *fpDevInfo,
//              ICC_DEVICE        *fpICCDevice
//
// Output:
//              EFI_STATUS
//
// Notes:       VoltageSelection, RateAndProtocolManagement
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ConfigureCCID(
    DEV_INFO          *fpDevInfo,
    ICC_DEVICE        *fpICCDevice
)
{
    EFI_STATUS  Status;
    UINT8       RetryCount = 3;

    //
    // Power up the device
    //
    do {
        Status = VoltageSelection(fpDevInfo, fpICCDevice);
        RetryCount--;

        //    
        // check for errors and do try to recover
        //
        if(EFI_ERROR(Status) || fpICCDevice->bStatus) {
            //
            // If card present but not powered up retry it. 
            // If card not present the exit immediatly
            //
            if (fpICCDevice->bStatus ==  2) {
                break;
            }            
        } else {
            break;
        }

    }while (RetryCount);

    //    
    //Configure the data Rate and select the Protocol
    //
    if (!EFI_ERROR(Status)){
        Status = RateAndProtocolManagement (fpDevInfo, fpICCDevice);
    }
    
    if (EFI_ERROR(Status)) {
        fpICCDevice->ConfiguredStatus = CONFIGFAILED;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDIssueBulkTransfer
//
// Description: This function executes a bulk transaction on the USB. The
//              transfer may be either DATA_IN or DATA_OUT packets containing
//              data sent from the host to the device or vice-versa. This
//              function wil not return until the request either completes
//              successfully or completes with error (due to time out, etc.)
//              Size of data can be upto 64K
//
// Input:   - DeviceInfo structure (if available else 0)
//          - Transfer direction
//              Bit 7   : Data direction
//                          0 Host sending data to device
//                          1 Device sending data to host
//              Bit 6-0 : Reserved
//          - Buffer containing data to be sent to the device or
//            buffer to be used to receive data. Value in
//          - Length request parameter, number of bytes of data
//            to be transferred in or out of the host controller
//
// Output:  Amount of data transferred
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
USBCCIDIssueBulkTransfer (
    DEV_INFO*   fpDevInfo, 
    UINT8       bXferDir,
    UINT8*      fpCmdBuffer, 
    UINT32      dSize
)
{
    return (*gUsbData->aHCDriverTable[GET_HCD_INDEX(gUsbData->HcTable
                [fpDevInfo->bHCNumber - 1]->bHCType)].pfnHCDBulkTransfer)
                (gUsbData->HcTable[fpDevInfo->bHCNumber -1],
                fpDevInfo, bXferDir,
                fpCmdBuffer, dSize);

    // Handle Bulk Transfer error here

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDIssueControlTransfer
//
// Description: Issues Control Pipe request to default pipe
//
// Parameters:     pDevInfo    DeviceInfo structure (if available else 0)
//          wRequest    Request type (low byte)
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
//              (ex: 1 : ABORT, 2 : GET_CLOCK_FREQUENCIES, 3: GET_DATA_RATES)
//      wIndex      wIndex request parameter (meaning varies)
//      wValue      wValue request parameter (meaning varies)
//      fpBuffer    Buffer containing data to be sent to the
//              device or buffer to be used to receive data
//      wLength     wLength request parameter, number of bytes
//              of data to be transferred in or out
//              of the host controller
//
// Output:  Number of bytes actually transferred
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
USBCCIDIssueControlTransfer(
    DEV_INFO*   fpDevInfo,     
    UINT16      wRequest,
    UINT16      wIndex,
    UINT16      wValue,
    UINT8       *fpBuffer,
    UINT16      wLength
)
{

    //
    // Not tested due to lack of H/W which supports it
    //
    return (*gUsbData->aHCDriverTable[GET_HCD_INDEX(gUsbData->HcTable
                [fpDevInfo->bHCNumber - 1]->bHCType)].pfnHCDControlTransfer)
                (gUsbData->HcTable[fpDevInfo->bHCNumber - 1],
                        fpDevInfo,
                        wRequest,
                        wIndex,
                        wValue,
                        fpBuffer,
                        wLength);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   FindNumberOfTs
//
// Description: Returns the # of Ts present in TDx
//
// Input:
//              UINT8    Data
//
// Output:
//              UINT8 - Returns number of TDx present in ATR data
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
FindNumberOfTs(
    UINT8    Data
)
{
    UINT8    Count = 0;
    UINT8    Mask = 0x10;

    for ( ;Mask; Mask = Mask << 1){
        if (Data & Mask) { 
            Count++;
        }
    }

    return Count;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PrintPCParameters
//
// Description: This function prints the information gathered from GetPCParameters
//
// Input:
//              UINT8 * Data   
//
// OutPut:
//              None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
PrintPCParameters(
    UINT8 * Data
)
{

    USB_DEBUG (DEBUG_LEVEL_3, "bProtocolNum     : %02X\n", Data[0]); 
    USB_DEBUG (DEBUG_LEVEL_3, "bmFindexDIndex   : %02X\n", Data[1]); 
    USB_DEBUG (DEBUG_LEVEL_3, "bmTCCKST0        : %02X\n", Data[2]); 
    USB_DEBUG (DEBUG_LEVEL_3, "bGaurdTime       : %02X\n", Data[3]); 
    USB_DEBUG (DEBUG_LEVEL_3, "bWaitingInterger : %02X\n", Data[4]); 
    USB_DEBUG (DEBUG_LEVEL_3, "bClockStop       : %02X\n", Data[5]); 
    USB_DEBUG (DEBUG_LEVEL_3, "bIFSC            : %02X\n", Data[6]); // Valid only for T1    
    USB_DEBUG (DEBUG_LEVEL_3, "bNadValue        : %02X\n", Data[7]); // Valid only for T1

    return;
} 


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PrintTimingInfo
//
// Description: This function prints the information gathered from ATR data
//
// Input:  
//              ICC_DEVICE    *fpICCDevice
//
// Output:
//              None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PrintTimingInfo(
    ICC_DEVICE    *fpICCDevice
)
{

    USB_DEBUG (DEBUG_LEVEL_3, "etu              : %02X  \n", fpICCDevice->etu); 
    USB_DEBUG (DEBUG_LEVEL_3, "GlobalFi         : %04x  \n", fpICCDevice->GlobalFi); 
    USB_DEBUG (DEBUG_LEVEL_3, "GlobalFmax       : %02X  \n", fpICCDevice->GlobalFmax); 
    USB_DEBUG (DEBUG_LEVEL_3, "GlobalDi         : %02X  \n", fpICCDevice->GlobalDi); 

    USB_DEBUG (DEBUG_LEVEL_3, "SpecificMode     : %02X  \n", fpICCDevice->SpecificMode); 

    USB_DEBUG (DEBUG_LEVEL_3, "ClassABC         : %02X  \n", fpICCDevice->ClassABC); 
    USB_DEBUG (DEBUG_LEVEL_3, "StopClockSupport : %02X  \n", fpICCDevice->StopClockSupport); 

    USB_DEBUG (DEBUG_LEVEL_3, "ExtraGuardTime   : %02X  \n", fpICCDevice->ExtraGuardTime); 
    USB_DEBUG (DEBUG_LEVEL_3, "WTwaittime       : %08x  \n", fpICCDevice->WTwaittime); 

    USB_DEBUG (DEBUG_LEVEL_3, "BWI              : %02X  \n", fpICCDevice->BWI); 
    USB_DEBUG (DEBUG_LEVEL_3, "CWI              : %02X  \n", fpICCDevice->CWI); 
    USB_DEBUG (DEBUG_LEVEL_3, "IFSC             : %02X  \n", fpICCDevice->IFSC); 
    USB_DEBUG (DEBUG_LEVEL_3, "NAD              : %02X  \n", fpICCDevice->NAD); 
    USB_DEBUG (DEBUG_LEVEL_3, "EpilogueFields   : %02X  \n", fpICCDevice->EpilogueFields); 
    USB_DEBUG (DEBUG_LEVEL_3, "BWT              : %02X  \n", fpICCDevice->BWT); 

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PrintATRData
//
// Description: This function Prints the RAW ATR Data
//
// Input:
//              UINT8       *ATRData
//
// Output:
//              None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PrintATRData(
    UINT8            *ATRData
)
{

    UINT8        TDx = 2;
    UINT8        i;


    USB_DEBUG (DEBUG_LEVEL_3, "    ATR Data \n");

    for (i=0; i< 32; i++) {
        USB_DEBUG (DEBUG_LEVEL_3, "%02X ", ATRData[i]);
    }

    i = 0;

    USB_DEBUG (DEBUG_LEVEL_3, "\nTS  : %02X  \n", ATRData[i++]); 

    TDx = ATRData[i];
    USB_DEBUG (DEBUG_LEVEL_3, "T0  : %02X  \n", ATRData[i++]); 
    USB_DEBUG (DEBUG_LEVEL_3, "TA1 : %02X  \n", TDx & 0x10 ? ATRData[i++] : 0); 
    USB_DEBUG (DEBUG_LEVEL_3, "TB1 : %02X  \n", TDx & 0x20 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TC1 : %02X  \n", TDx & 0x40 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TD1 : %02X  \n", TDx & 0x80 ? ATRData[i++] : 0);

    if (!(TDx & 0x80)) return;
    TDx = ATRData[i-1];

 
    USB_DEBUG (DEBUG_LEVEL_3, "TA2 : %02X \n", TDx & 0x10 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TB2 : %02X \n", TDx & 0x20 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TC2 : %02X \n", TDx & 0x40 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TD2 : %02X \n", TDx & 0x80 ? ATRData[i++] : 0);

    if (!(TDx & 0x80)) return;
    TDx = ATRData[i-1];

    USB_DEBUG (DEBUG_LEVEL_3, "TA3 : %02X \n", TDx & 0x10 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TB3 : %02X \n", TDx & 0x20 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TC3 : %02X \n", TDx & 0x40 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TD3 : %02X \n", TDx & 0x80 ? ATRData[i++] : 0);

    if (!(TDx & 0x80)) return;
    TDx = ATRData[i-1];

    USB_DEBUG (DEBUG_LEVEL_3, "TA4 : %02X \n", TDx & 0x10 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TB4 : %02X \n", TDx & 0x20 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TC4 : %02X \n", TDx & 0x40 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TD4 : %02X \n", TDx & 0x80 ? ATRData[i++] : 0);

    if (!(TDx & 0x80)) return;
    TDx = ATRData[i-1];

    USB_DEBUG (DEBUG_LEVEL_3, "TA5 : %02X \n", TDx & 0x10 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TB5 : %02X \n", TDx & 0x20 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TC5 : %02X \n", TDx & 0x40 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TD5 : %02X \n", TDx & 0x80 ? ATRData[i++] : 0);

    if (!(TDx & 0x80)) return;
    TDx = ATRData[i-1];

    USB_DEBUG (DEBUG_LEVEL_3, "TA6 : %02X \n", TDx & 0x10 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TB6 : %02X \n", TDx & 0x20 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TC6 : %02X \n", TDx & 0x40 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TD6 : %02X \n", TDx & 0x80 ? ATRData[i++] : 0);

    if (!(TDx & 0x80)) return;
    TDx = ATRData[i-1];

    USB_DEBUG (DEBUG_LEVEL_3, "TA7 : %02X \n", TDx & 0x10 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TB7 : %02X \n", TDx & 0x20 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TC7 : %02X \n", TDx & 0x40 ? ATRData[i++] : 0);
    USB_DEBUG (DEBUG_LEVEL_3, "TD7 : %02X \n", TDx & 0x80 ? ATRData[i++] : 0);

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PrintDescriptorInformation
//
// Description: Prints SMART class Descriptor data
//
// Input:
//              SMARTCLASS_DESC *fpCCIDDesc
//
// Output:
//              None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PrintDescriptorInformation (
    SMARTCLASS_DESC *fpCCIDDesc
)
{

    CHAR8    *Strings[] = {"CHARACTER", "TDPU", "Short ADPU", "Extended ADPU"};
    UINT8   Exchange = (fpCCIDDesc->dwFeatures & 0x70000) >> 16;

    USB_DEBUG (DEBUG_LEVEL_3, "Sizeof SMART Class Descriptor :  %X\n", sizeof (SMARTCLASS_DESC));
    USB_DEBUG (DEBUG_LEVEL_3, "bDescLength            :  %04X\n", fpCCIDDesc->bDescLength);
    USB_DEBUG (DEBUG_LEVEL_3, "bDescType              :  %04X\n", fpCCIDDesc->bDescType);
    USB_DEBUG (DEBUG_LEVEL_3, "bcdCCID                :  %04X\n", fpCCIDDesc->bcdCCID);
    USB_DEBUG (DEBUG_LEVEL_3, "bMaxSlotIndex          :  %04X\n", fpCCIDDesc->bMaxSlotIndex);
    USB_DEBUG (DEBUG_LEVEL_3, "bVoltageSupport        :  %04X\n", fpCCIDDesc->bVoltageSupport);
    USB_DEBUG (DEBUG_LEVEL_3, "dwProtocols            :  %04X\n", fpCCIDDesc->dwProtocols);
    USB_DEBUG (DEBUG_LEVEL_3, "dwDefaultClock         :  %04X\n", fpCCIDDesc->dwDefaultClock);
    USB_DEBUG (DEBUG_LEVEL_3, "dwMaximumClock         :  %04X\n", fpCCIDDesc->dwMaximumClock);
    USB_DEBUG (DEBUG_LEVEL_3, "bNumClockSupported     :  %04X\n", fpCCIDDesc->bNumClockSupported);
    USB_DEBUG (DEBUG_LEVEL_3, "dwDataRate             :  %04X\n", fpCCIDDesc->dwDataRate);
    USB_DEBUG (DEBUG_LEVEL_3, "dwMaxDataRate          :  %04X\n", fpCCIDDesc->dwMaxDataRate);
    USB_DEBUG (DEBUG_LEVEL_3, "bNumDataRatesSupported :  %04X\n", fpCCIDDesc->bNumDataRatesSupported);
    USB_DEBUG (DEBUG_LEVEL_3, "dwMaxIFSD              :  %04X\n", fpCCIDDesc->dwMaxIFSD);
    USB_DEBUG (DEBUG_LEVEL_3, "dwSynchProtocols       :  %04X\n", fpCCIDDesc->dwSynchProtocols);
    USB_DEBUG (DEBUG_LEVEL_3, "dwMechanical           :  %04X\n", fpCCIDDesc->dwMechanical);
    USB_DEBUG (DEBUG_LEVEL_3, "dwFeatures             :  %04X\n", fpCCIDDesc->dwFeatures);
    USB_DEBUG (DEBUG_LEVEL_3, "bClassGetResponse      :  %04X\n", fpCCIDDesc->dwMaxCCIDMessageLength);
    USB_DEBUG (DEBUG_LEVEL_3, "bClassGetResponse      :  %04X\n", fpCCIDDesc->bClassGetResponse);
    USB_DEBUG (DEBUG_LEVEL_3, "bClassEnvelope         :  %04X\n", fpCCIDDesc->bClassEnvelope);
    USB_DEBUG (DEBUG_LEVEL_3, "wLcdLayout             :  %04X\n", fpCCIDDesc->wLcdLayout);
    USB_DEBUG (DEBUG_LEVEL_3, "bPINSupport            :  %04X\n", fpCCIDDesc->bPINSupport);
    USB_DEBUG (DEBUG_LEVEL_3, "bMaxCCIDBusySlots      :  %04X\n", fpCCIDDesc->bMaxCCIDBusySlots);

    USB_DEBUG (DEBUG_LEVEL_3, "*************************************\n"); 
    USB_DEBUG (DEBUG_LEVEL_3, " Device is in:"); 
    USB_DEBUG (DEBUG_LEVEL_3, "%s Exchange mode\n", Strings[Exchange]); 
    USB_DEBUG (DEBUG_LEVEL_3, "*************************************\n"); 

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCID_ProcessInterruptData
//
// Description: This routine is called when InterruptIN messages is generated
//      
// Input:       pHCStruc    Pointer to HCStruc
//              pDevInfo    Pointer to device information structure
//              pTD         Pointer to the polling TD
//              pBuffer     Pointer to the data buffer
//
// Output:
//              UEB_ERROR/USB_SUCCESS
//
// Notes:       When an ICC card is inserted or removed Interrupt message is generated.   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBCCID_ProcessInterruptData (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Td,
    UINT8       *Buffer,
    UINT16      DataLength
)
{

    EFI_STATUS      Status;
    UINT8           Data;
    UINT8           Slot = 0;
    UINT8           bmSlotICCByte = 0;
    UINT32          SlotICCStatus = *(UINT32 *)(Buffer + 1);
	SMARTCLASS_DESC	*CCIDDescriptor = (SMARTCLASS_DESC*)DevInfo->pCCIDDescriptor;
    UINT8           *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);

    if (((UINT8*)DevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)DevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return USB_ERROR;
    }

    USB_DEBUG(DEBUG_LEVEL_3, "USBCCID_ProcessInterruptData.... %X %X %X %X\n", 
                *Buffer, *(Buffer +1), *(Buffer + 2), *(Buffer + 3));


    switch (*Buffer) {

        //
        // ICC Card either inserted or Removed
        //
        case RDR_TO_PC_NOTIFYSLOTCHANGE:        

            //
            // Find the # of bytes in this notification
            //
            Slot = CCIDDescriptor->bMaxSlotIndex + 1; // Make it 1 based
            bmSlotICCByte = (CCIDDescriptor->bMaxSlotIndex + 1) >> 2;

            if (Slot & 0x3) { 
                bmSlotICCByte++;
            }

            Slot = 0;
            do {
                Data = (SlotICCStatus >> Slot) & 0x3;
                //
                // Is there a change in status
                //
                if ((Data & 0x3) == 3) {                
                    Status = ICCInsertEvent (DevInfo, Slot);
                }
                if ((Data & 0x3) == 2) {                
                    Status = ICCRemovalEvent (DevInfo, Slot);
                }
                  Slot++;
            } while (Slot < (CCIDDescriptor->bMaxSlotIndex + 1));                        

            break;

        case RDR_TO_PC_HARDWAREERROR:        

            USB_DEBUG(DEBUG_LEVEL_3, "RDR To PC Hardware Error Slot %X Sequence %X Error Code %X \n", 
                            *Buffer, *(Buffer +1), *(Buffer + 2));
            break;

        default:
            break;
    }

    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ICCRemovalEvent
//
// Description: In response to Device removal, Interrupt-in message is received. 
//              Icc Device is removed from the linked list.
//
// Input:
//    DEV_INFO    *fpDevInfo,
//    UINT8        Slot
//
// Output:
//    EFI_STATUS    
//
// Notes: 
//    
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ICCRemovalEvent(
        DEV_INFO    *fpDevInfo,
        UINT8        Slot
)
{

    ICC_DEVICE        *fpICCDevice;
    
    fpICCDevice = GetICCDevice(fpDevInfo, Slot);
   
    if (fpICCDevice) {

        // Don't free up the memory. EFI driver (EfiUsbCCID) makes use of this data area to 
        // find whether ICC has been removed or added.
        // Before freeing up, clear the bytes

//        MemFill((UINT8 *)fpICCDevice, sizeof(ICC_DEVICE), 0);

        //
        //Free up the memory and remove it from linked list
        //
//        DListDelete (&(fpDevInfo->ICCDeviceList), &(fpICCDevice->ICCDeviceLink));
//        USB_MemFree(fpICCDevice, (UINT8)GET_MEM_BLK_COUNT(sizeof(ICC_DEVICE)));

        if (fpICCDevice->ConfiguredStatus) {
            fpICCDevice->ConfiguredStatus = 0;
        } else {
            //
            // Handle if IccRemovalEven is called multiple times
            //
            return EFI_SUCCESS;
        }

        USB_DEBUG(DEBUG_LEVEL_3, "ICC device removed - Slot : %X\n", Slot);

        if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {
            ICC_SmiQueuePut((void *)fpICCDevice);
        }
    }

    USB_DEBUG(DEBUG_LEVEL_3, "Removal: fpDevInfo %X fpICCDevice %X\n", fpDevInfo, fpICCDevice);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ICCInsertEvent
//
// Description: In response to Device Insertion, Interrupt-in message is received. 
//              Icc Device is added to the linked list and configured.
//
// Input:
//              DEV_INFO    *fpDevInfo,
//              UINT8        Slot
//
// Output:
//              EFI_STATUS    
//
// Notes:       ConfigureCCID, GetICCDevice
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ICCInsertEvent(
    DEV_INFO    *fpDevInfo,
    UINT8       Slot
)
{

    EFI_STATUS        Status;
    ICC_DEVICE        *fpICCDevice;
    BOOLEAN         NewDeviceAdded = FALSE;

    //
    // Check if the device already exist. if so use it.
    //
    fpICCDevice = GetICCDevice(fpDevInfo, Slot);

    if (!fpICCDevice) {
        //
        // Alocate memory for ICC_DEVICE and attach it to the linked list
        //
        fpICCDevice = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(ICC_DEVICE)));
        ASSERT(fpICCDevice);
        if (!fpICCDevice) {
            return EFI_OUT_OF_RESOURCES;
        }    
        MemFill((UINT8 *)fpICCDevice, sizeof(ICC_DEVICE), 0);

        //
        // Add to the slot list
        //
#if USB_RUNTIME_DRIVER_IN_SMM
        if (fpDevInfo->ICCDeviceList.pHead != NULL) {
            Status = AmiValidateMemoryBuffer((VOID*)(fpDevInfo->ICCDeviceList.pHead), 
                            (UINT32)sizeof(DLINK));
            if (EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            }
        }
        if (fpDevInfo->ICCDeviceList.pTail != NULL) {
            Status = AmiValidateMemoryBuffer((VOID*)(fpDevInfo->ICCDeviceList.pTail), 
                            (UINT32)sizeof(DLINK));
            if (EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            }
        }
#endif
        DListAdd(&(fpDevInfo->ICCDeviceList), &(fpICCDevice->ICCDeviceLink)); 
        NewDeviceAdded = TRUE;

    }

#if CCID_USE_INTERRUPT_INSERTION_REMOVAL
    // Handle Multiple ICCInsertEvent calls. Some cards generate 
    // Interrupt in Interrupt-IN endpoint and some don't.
    // For card which don't generate the intterupt, CCID API should be used to power up the device.
    if (fpICCDevice->ConfiguredStatus) {

        if (fpICCDevice->ConfiguredStatus == CONFIGFAILED) {
            return EFI_DEVICE_ERROR;
        }
        return EFI_SUCCESS;

    }
#endif
    
    fpICCDevice->ChildHandle = 0;
    fpICCDevice->Slot = Slot;
    fpICCDevice->WaitTime = INITWAITTIME;

    Status = ConfigureCCID(fpDevInfo, fpICCDevice);

#if CCID_USE_INTERRUPT_INSERTION_REMOVAL
    if(EFI_ERROR(Status)){

        //
        //Free up the memory and remove it from linked list
        //
#if USB_RUNTIME_DRIVER_IN_SMM
        if (fpDevInfo->ICCDeviceList.pHead != NULL) {
            Status = AmiValidateMemoryBuffer((VOID*)(fpDevInfo->ICCDeviceList.pHead), 
                            (UINT32)sizeof(DLINK));
            if (EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            }
        }
        if (fpDevInfo->ICCDeviceList.pTail != NULL) {
            Status = AmiValidateMemoryBuffer((VOID*)(fpDevInfo->ICCDeviceList.pTail), 
                            (UINT32)sizeof(DLINK));
            if (EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            }
        }
#endif
        DListDelete (&(fpDevInfo->ICCDeviceList), &(fpICCDevice->ICCDeviceLink));
        USB_MemFree(fpICCDevice, (UINT8)GET_MEM_BLK_COUNT(sizeof(ICC_DEVICE)));

    } else {
        USB_DEBUG(DEBUG_LEVEL_3, "ICC device added - Slot : %X\n", Slot);
    
        if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {
            ICC_SmiQueuePut((void *)fpICCDevice);
        }
    }

#else
    //
    // Even if configuration failed install the protocol in polling mode.         
    //
    USB_DEBUG(DEBUG_LEVEL_3, "ICC device added - Slot : %X\n", Slot);
    
    if ((gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) && NewDeviceAdded) {
        ICC_SmiQueuePut((void *)fpICCDevice);
    }
#endif

    USB_DEBUG(DEBUG_LEVEL_3, "Insert : fpDevInfo %X fpICCDevice %X\n", fpDevInfo, fpICCDevice);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ICC_SmiQueuePut
//
// Description: Puts the pointer  into the queue for processing.
//              updates queue head and tail. This data is read from EfiUSBCCID.C 
//              which installs AMI_CCID_IO_PROTOCOL
//
// Input:
//              (void *)fpICCDevice
//
// Output:
//              None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ICC_SmiQueuePut(
    VOID * d
)
{
    QUEUE_T* q = &gUsbData->ICCQueueCnnctDisc;

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
    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DoDevInfoInitialization
//
// Description: Do some USB device info data initialization 
//
// Input:
//              DEV_INFO    *fpDevInfo
//              UINT8       *fpDesc
//              UINT16      wStart
//              UINT16      wEnd
//
// Output:
//              EFI_STATUS
//
// Notes: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
DoDevInfoInitialization (
    DEV_INFO    *fpDevInfo,
    UINT8       *fpDesc,
    UINT16      wStart,
    UINT16      wEnd
)
{

    UINT8           bTemp;
    ENDP_DESC       *fpEndpDesc;
    INTRF_DESC      *fpIntrfDesc;
    SMARTCLASS_DESC *fpCCIDDesc = NULL;

    fpDevInfo->bDeviceType      = BIOS_DEV_TYPE_CCID;
    fpDevInfo->fpPollTDPtr      = 0;

    fpDevInfo->bCallBackIndex = USB_InstallCallBackFunction(USBCCID_ProcessInterruptData);

    //
    // Initialize the Initlist to hold data for each Slot 
    //
    DListInit(&(fpDevInfo->ICCDeviceList));
    fpIntrfDesc = (INTRF_DESC*)(fpDesc + wStart);

    //
    // Calculate the end of descriptor block
    //
    fpDesc+=((CNFG_DESC*)fpDesc)->wTotalLength; 
    fpEndpDesc = (ENDP_DESC*)((char*)fpIntrfDesc + fpIntrfDesc->bDescLength);

    do {
        if (fpIntrfDesc->bDescType == DESC_TYPE_SMART_CARD) {
            fpCCIDDesc = (SMARTCLASS_DESC *)fpIntrfDesc;
            break;
        }
        fpIntrfDesc = (INTRF_DESC*) ((UINT8 *)fpIntrfDesc + fpIntrfDesc->bDescLength);
    }while ((UINT8 *)fpIntrfDesc < fpDesc);

    if (!fpCCIDDesc) { 
        return EFI_DEVICE_ERROR;
    }

    fpDevInfo->pCCIDDescriptor = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(sizeof(SMARTCLASS_DESC)));
    ASSERT(fpDevInfo->pCCIDDescriptor);
    if (!fpDevInfo->pCCIDDescriptor) {
        return EFI_OUT_OF_RESOURCES;
    }      
    MemCopy((UINT8 *)fpCCIDDesc, (UINT8 *)(fpDevInfo->pCCIDDescriptor), sizeof(SMARTCLASS_DESC));
	fpCCIDDesc = (SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor;

    if (fpCCIDDesc->bNumDataRatesSupported) {

        fpDevInfo->DataRates = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(
                                            fpCCIDDesc->bNumDataRatesSupported * sizeof(UINT32)));
        ASSERT(fpDevInfo->DataRates);
        if (!fpDevInfo->DataRates) {
            return EFI_OUT_OF_RESOURCES;
        }      
        //
        // Issue GET_DATA_RATES cmd. Should interface number be zero?
        //
        USBCCIDIssueControlTransfer(fpDevInfo, 
                                    CCID_CLASS_SPECIFIC_GET_DATA_RATES, 
                                    0x0, 0, (UINT8 *)fpDevInfo->DataRates, 
                                    fpCCIDDesc->bNumDataRatesSupported * sizeof(UINT32)
                                    );
        
    } else {
        fpDevInfo->DataRates = 0;
    }

    if (fpCCIDDesc->bNumClockSupported) {

        fpDevInfo->ClockFrequencies = USB_MemAlloc((UINT8)GET_MEM_BLK_COUNT(
                                        fpCCIDDesc->bNumClockSupported * sizeof(UINT32)));
        ASSERT(fpDevInfo->ClockFrequencies);
        if (!fpDevInfo->ClockFrequencies) {
            return EFI_OUT_OF_RESOURCES;
        }
        //            
        // Issue GET_CLOCK_FREQUENCIES. Should interface number be zero?
        //
        USBCCIDIssueControlTransfer(fpDevInfo,  
                                    CCID_CLASS_SPECIFIC_GET_CLOCK_FREQUENCIES, 
                                    0x0, 0, (UINT8 *)fpDevInfo->DataRates,
                                    fpCCIDDesc->bNumClockSupported * sizeof(UINT32));
    } else {
        fpDevInfo->ClockFrequencies = 0;
    }

    PrintDescriptorInformation(fpDevInfo->pCCIDDescriptor);

    bTemp = 0x03;       // bit 1 = Bulk In, bit 0 = Bulk Out

    for( ;(fpEndpDesc->bDescType != DESC_TYPE_INTERFACE) && ((UINT8*)fpEndpDesc < fpDesc);
        fpEndpDesc = (ENDP_DESC*)((UINT8 *)fpEndpDesc + fpEndpDesc->bDescLength)){

		if(!(fpEndpDesc->bDescLength)) {  
			  // Br if 0 length desc (should never happen, but...)
			  break;  
		}

        if( fpEndpDesc->bDescType != DESC_TYPE_ENDPOINT ) {
            continue;
        }

        if ((fpEndpDesc->bEndpointFlags & EP_DESC_FLAG_TYPE_BITS) ==
                EP_DESC_FLAG_TYPE_BULK) {   // Bit 1-0: 10 = Endpoint does bulk transfers
            if(!(fpEndpDesc->bEndpointAddr & EP_DESC_ADDR_DIR_BIT)) {
                //
                // Bit 7: Dir. of the endpoint: 1/0 = In/Out
                // If Bulk-Out endpoint already found then skip subsequent ones
                // on the interface.
                //
                if (bTemp & 1) {
                    fpDevInfo->bBulkOutEndpoint = (UINT8)(fpEndpDesc->bEndpointAddr
                                                        & EP_DESC_ADDR_EP_NUM);
                    fpDevInfo->wBulkOutMaxPkt = fpEndpDesc->wMaxPacketSize;
                    bTemp &= 0xFE;
                }
            } else {
                //
                // If Bulk-In endpoint already found then skip subsequent ones
                // on the interface
                //
                if (bTemp & 2) {
                    fpDevInfo->bBulkInEndpoint  = (UINT8)(fpEndpDesc->bEndpointAddr
                                                        & EP_DESC_ADDR_EP_NUM);
                    fpDevInfo->wBulkInMaxPkt    = fpEndpDesc->wMaxPacketSize;
                    bTemp   &= 0xFD;
                }
            }
        }

        //
        // Check for and configure Interrupt endpoint if present
        //
        if ((fpEndpDesc->bEndpointFlags & EP_DESC_FLAG_TYPE_BITS) !=
                EP_DESC_FLAG_TYPE_INT) {    // Bit 1-0: 10 = Endpoint does interrupt transfers
			continue;
        }

		if (fpEndpDesc->bEndpointAddr & EP_DESC_ADDR_DIR_BIT) {
			fpDevInfo->IntInEndpoint = fpEndpDesc->bEndpointAddr;
			fpDevInfo->IntInMaxPkt = fpEndpDesc->wMaxPacketSize;
			fpDevInfo->bPollInterval = fpEndpDesc->bPollInterval;	
		}
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   USBCCIDInitialize
//
// Description: This function initializes CCID device related data
//
// Input:
//              None
//
// Output:      
//              None 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBCCIDInitialize ()
{
    USB_InstallCallBackFunction(USBCCID_ProcessInterruptData);
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDCheckForDevice
//
// Description: This routine checks for CCID type device from the
//              interface data provided
//
// Input:
//              DEV_INFO    *fpDevInfo
//              UINT8       bBaseClass
//              UINT8       bSubClass
//              UINT8       bProtocol
//
// Output:      
//              BIOS_DEV_TYPE_STORAGE type on success or 0FFH on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBCCIDCheckForDevice (
    DEV_INFO    *fpDevInfo,
    UINT8       bBaseClass,
    UINT8       bSubClass,
    UINT8       bProtocol
)
{

    if(bBaseClass == BASE_CLASS_CCID_STORAGE  && bProtocol == PROTOCOL_CCID) {
        return BIOS_DEV_TYPE_CCID;
    }

    return USB_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDConfigureDevice
//
// Description: This function checks an interface descriptor of a device
//              to see if it describes a USB CCID device.  If the device
//              is a CCID device,  then it is configured
//              and initialized.
//
// Input:
//              pHCStruc    HCStruc pointer
//              pDevInfo    Device information structure pointer
//              pDesc       Pointer to the descriptor structure
//              wEnd        End offset of the device descriptor
//
// Output:    
//              New device info structure, NULL on error
//
// Notes:       DoDevInfoInitialization
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USBCCIDConfigureDevice (
    HC_STRUC        *fpHCStruc,
    DEV_INFO        *fpDevInfo,
    UINT8           *fpDesc,
    UINT16          wStart,
    UINT16          wEnd
)
{

    EFI_STATUS        Status;
    INTRF_DESC      *fpIntrfDesc = (INTRF_DESC*)(fpDesc + wStart);

    USB_DEBUG (DEBUG_LEVEL_3, "USBCCIDConfigureDevice ....\n");

    //
    // Do some house keeping related DEV_INFO structure. No H/W access
    //
    Status = DoDevInfoInitialization(fpDevInfo, fpDesc, wStart, wEnd);

    if (EFI_ERROR(Status)) {
        return NULL;
    }

#if CCID_USE_INTERRUPT_INSERTION_REMOVAL
    //
    // if Interrupt EndPoint is supported
    //
    if (fpIntrfDesc->bNumEndpoints == 3) {
		fpDevInfo->PollingLength = fpDevInfo->IntInMaxPkt;
        (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDActivatePolling)
                    (fpHCStruc, fpDevInfo);
    }

#else

    Status = ICCInsertEvent(fpDevInfo, 0);

#endif

    //
    // Should we support CCID which doesn't support interrupt-IN Message.
    // Maybe not for now.
    //
    return  fpDevInfo;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBCCIDDisconnectDevice
//
// Description: This function disconnects the CCID device.
//
// Input:    
//              pDevInfo    Device info structure pointer
//
// Output:
//              None
//
//Notes:        Free up all memory allocated to the device. 
//              Remove ICC device from the device list.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBCCIDDisconnectDevice (
    DEV_INFO    *fpDevInfo
)
{

    ICC_DEVICE        *fpICCDevice;
    DLINK      *dlink = fpDevInfo->ICCDeviceList.pHead;
	HC_STRUC   *fpHCStruc = gUsbData->HcTable[fpDevInfo->bHCNumber - 1];
	SMARTCLASS_DESC *CCIDDescriptor = (SMARTCLASS_DESC*)fpDevInfo->pCCIDDescriptor;
    UINT8              *MemBlockEnd = gUsbData->fpMemBlockStart + (gUsbData->MemPages << 12);
    EFI_STATUS  Status = EFI_SUCCESS;

    if (((UINT8*)fpDevInfo->pCCIDDescriptor < gUsbData->fpMemBlockStart) ||
        ((UINT8*)fpDevInfo->pCCIDDescriptor > MemBlockEnd)) {
        return USB_ERROR;
    }

#if USB_RUNTIME_DRIVER_IN_SMM
    if (dlink != NULL) {
        Status = AmiValidateMemoryBuffer((VOID*)dlink, 
                            (UINT32)sizeof(DLINK));
        if (EFI_ERROR(Status)) {
            return USB_ERROR;
        }
    }
#endif

#if CCID_USE_INTERRUPT_INSERTION_REMOVAL
	// Stop polling the endpoint
	(*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDDeactivatePolling)(fpHCStruc,fpDevInfo);
	fpDevInfo->IntInEndpoint = 0;

#endif

    //
    // Free up all the memory allocated for each ICC device
    //
    while (dlink) {
        fpICCDevice = OUTTER(dlink, ICCDeviceLink, ICC_DEVICE);
        if (((UINT8*)fpICCDevice < gUsbData->fpMemBlockStart) ||
            ((UINT8*)((UINTN)fpICCDevice + sizeof(ICC_DEVICE)) > MemBlockEnd)) {
            return USB_ERROR;
        }
        USB_MemFree(fpICCDevice, (UINT8)GET_MEM_BLK_COUNT(sizeof(ICC_DEVICE)));
#if USB_RUNTIME_DRIVER_IN_SMM
        if (fpDevInfo->ICCDeviceList.pHead != NULL) {
            Status = AmiValidateMemoryBuffer((VOID*)(fpDevInfo->ICCDeviceList.pHead), 
                            (UINT32)sizeof(DLINK));
            if (EFI_ERROR(Status)) {
                return USB_ERROR;
            }
        }
        if (fpDevInfo->ICCDeviceList.pTail != NULL) {
            Status = AmiValidateMemoryBuffer((VOID*)(fpDevInfo->ICCDeviceList.pTail), 
                            (UINT32)sizeof(DLINK));
            if (EFI_ERROR(Status)) {
                return USB_ERROR;
            }
        }
#endif
        DListDelete (&(fpDevInfo->ICCDeviceList), &(fpICCDevice->ICCDeviceLink));
        if (!dlink->pNext) break;
        dlink = dlink->pNext;       
    }

    if (fpDevInfo->DataRates) {
        USB_MemFree(fpDevInfo->DataRates, 
                    (UINT8)GET_MEM_BLK_COUNT(CCIDDescriptor->bNumDataRatesSupported * sizeof(UINT32))
                    );
    }

    if (fpDevInfo->ClockFrequencies) {
        USB_MemFree(fpDevInfo->ClockFrequencies, 
                    (UINT8)GET_MEM_BLK_COUNT(CCIDDescriptor->bNumClockSupported * sizeof(UINT32))
                    );
    }

    //
    // Free up all the memory allocated for CCID Descriptor
    //
    USB_MemFree(CCIDDescriptor, 
                (UINT8)GET_MEM_BLK_COUNT(sizeof(SMARTCLASS_DESC))
                );

    fpDevInfo->pCCIDDescriptor = 0;

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
