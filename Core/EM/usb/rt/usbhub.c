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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbhub.c 54    10/16/16 10:12p Wilsonlee $
//
// $Revision: 54 $
//
// $Date: 10/16/16 10:12p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbhub.c $
// 
// 54    10/16/16 10:12p Wilsonlee
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
// 53    3/02/16 9:41p Wilsonlee
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
// 52    9/01/15 10:17p Wilsonlee
// [TAG]  		EIP235482
// [Category]  	Improvement
// [Description]  	Select this alternate setting for multiple TTs hubs.
// [Files]  		usbhub.c, usb.c, amiusb.h, usbdef.h
// 
// 51    5/11/15 4:32a Wilsonlee
// [TAG]  		EIP216986
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BIOS can't find Realtek usb Lan dongle if this device is in
// some hubs.
// [RootCause]  	USB 3.0 hub may not set Connect Status Change bit.
// [Solution]  	Set the connect change flag if the BH Reset change or
// Reset change is set.
// [Files]  		usbhub.c
// 
// 50    2/24/15 10:33p Wilsonlee
// [TAG]  		EIP204948
// [Category]  	Improvement
// [Description]  	Reset the port if the link is Inactive.
// [Files]  		usbhub.c
// 
// 49    2/05/15 5:46a Wilsonlee
// [TAG]  		EIP202436
// [Category]  	Improvement
// [Description]  	Issues a SetPortFeature(PORT_POWER) request for hub
// ports over-current recovery.
// [Files]  		usbhub.c
// 
// 48    1/22/15 10:19p Wilsonlee
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
// 47    6/20/14 3:14a Wilsonlee
// [TAG]  		EIP173968
// [Category]  	Improvement
// [Description]  	Use MaxPacketSize of hubs to poll data for the device
// compatibility issue.
// [Files]  		usbhub.c
// 
// 46    5/01/14 3:38a Ryanchou
// [TAG]  		EIP165208
// [Category]  	Improvement
// [Description]  	Add 20 ms delay after port reset completed.
// [Files]  		usbhub.c
// 
// 45    4/30/14 6:15a Ryanchou
// [TAG]  		EIP151374
// [Category]  	Improvement
// [Description]  	Calculates maximum data length to be reported in the
// HID device.
// [Files]  		ehci.c, ohci.c, uhci.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, xhci.c
// 
// 44    2/26/14 1:55a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 43    11/26/13 4:18a Ryanchou
// [TAG]  		EIP143124
// [Category]  	Improvement
// [Description]  	Added 1 ms delay after HUB port reset.
// [Files]  		usbhub.c
// 
// 42    11/26/13 1:25a Wilsonlee
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
// 41    7/22/13 10:31p Wilsonlee
// [TAG]  		EIP125357
// [Category]  	Improvement
// [Description]  	Check if the port releases to a select host controller.
// [Files]  		uhci.c, usb.c, usbhub.c, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 40    6/30/13 11:40p Wilsonlee
// [TAG]  		EIP121374
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB flash is not recognized after re-plugged on DOS.
// [RootCause]  	Some devices need to wait for that they are being settle.
// [Solution]  	Delay for 50 ms allowing port to settle when pluged in
// devices.
// [Files]  		usbhub.c, usbdef.h
// 
// 39    3/19/13 3:58a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 38    3/18/13 4:49a Ryanchou
// [TAG]  		EIP98377
// [Category]  	Improvement
// [Description]  	Optimize USB controller timing.
// [Files]  		usb.sdl, usbport.c, ehci.c, elib.c, ohci.c, uhci.c,
// usbdef.h, usbhub.c, xhci.c, uhcd.c
// 
// 37    1/23/13 4:05a Wilsonlee
// [TAG]  		EIP111239
// [Category]  	Improvement
// [Description]  	Handle the recovery state of the devces which are
// behind the USB3 hub.
// [Files]  		usbhub.c
// 
// 36    1/11/13 4:15a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 35    12/07/12 3:04a Ryanchou
// 
// 34    11/10/12 7:03a Ryanchou
// [TAG]  		EIP103966
// [Category]  	Improvement
// [Description]  	Always issue set port power request to HiSpeed USB hub.
// [Files]  		usbhub.c
// 
// 33    11/10/12 6:39a Ryanchou
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
// 32    9/28/12 2:39a Wilsonlee
// [TAG]  		EIP93154
// [Category]  	Improvement
// [Description]  	Change the unit of the FixedDelay from 15 us to 1 us.
// [Files]  		amiusb.h, xhci.c, ehci.c, ohci.c, uhci.c, usb.c, usbCCID.c,
// usbmass.c, usbhub.c, elib.c
// 
// 31    5/03/12 6:26a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 30    3/04/12 4:40a Wilsonlee
// [TAG]  		EIP77526
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	BBS is not correct to detect BMC's USB virtual device
// [RootCause]  	It is failed to sets port feature for resetting hub
// ports.
// [Solution]  	We enlarge the timeout value for setting port feature.
// [Files]  		usbhub.c
// 
// 29    8/08/11 5:18a Ryanchou
// [TAG]  		EIP60561
// [Category]  	New Feature
// [Description]  	Add USB timing policy protocol for timing override.
// [Files]  		ehci.c, guids.c, ohci.c, uhcd.c, uhci.c usb.c, usbdef.h,
// usbhub.c, usbmass.c, UsbPolicy.h, usbport.c usbsrc.sdl
// 
// 28    6/21/11 11:04a Ryanchou
// [TAG]  		EIP59579
// [Category]  	Improvement
// [Description]  	USB device information structure should be reserved for
// the UsbIO to use even install driver fail.
// [Files]  		usbmass.c, usbkbd.c, usbhub.c
// 
// 27    3/30/11 8:14a Ryanchou
// [TAG]  		EIP54126
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Sometimes system hangs at checkpoint 0xB4.
// [RootCause]  	The bLength field of configuration descriptor is zero.
// [Solution]  	Check wether bLength field is zero before paring next
// descriptor.
// [Files]  		usb.c, usbbus.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c
// 
// 26    3/29/11 10:56p Ryanchou
// [TAG]  		EIP55401
// [Category]  	Improvement
// [Description]  	Improve the USB 3.0 device compatibility.
// [Files]  		ehci.c, ehci.h, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c,
// xhci.c
// 
// 25    2/22/11 5:07a Ryanchou
// [TAG]  		EIP53108
// [Category]  	Improvement
// [Description]  	Change the order of the request "Set Hub Depth".
// [Files]  		usbhub.c
// 
// 24    2/18/11 1:50a Ryanchou
// [TAG]  		EIP52299
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB device can't detected after warm reset.
// [RootCause]  	If configure device fail first time, the connect status
// change will be clear, and second time port reset will not be issued.
// [Solution]  	Remove check connect status change.
// [Files]  		usbhub.c
// 
// 23    11/11/10 11:37p Ryanchou
// [TAG]  		EIP45578
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB 3.0 device can't be detected.
// [RootCause]  	Address Device Command fails.
// [Solution]  	Reset the device and attempt the Address Device Command
// again.
// [Files]  		ehci.c, ohci.c, uhci.c, usb.c, usbdef.h, usbhub.c, xhci.c
// 
// 22    10/20/10 10:24a Ryanchou
// EIP44702: Added USB 3.0 hub support.
// 
// 21    9/24/10 5:38p Olegi
// EIP38221: Added the code that properly initializes
// DEV_INFO.bIntEndpoint field; interrupt endpoint polling is using this
// endpoint number.
// 
// 20    7/13/10 5:10a Ryanchou
// EIP39838: Fixed configure USB hub fail.
// 
// 19    6/28/10 2:55a Ryanchou
// Add back 50ms delay after reseting a USB device.
// 
// 18    6/22/10 9:30a Ryanchou
// EIP39374: Fixed USB key hot plug issue.
// 
// 17    4/19/10 1:53p Olegi
// 
// 16    10/07/09 9:48a Olegi
// USB Hub error handling improvement. EIP#25601.
// 
// 15    5/22/09 1:47p Olegi
// Added the special treatment for in-built hubs.
// 
// 14    5/08/09 8:58a Olegi
// Bugfix in USBHub_ProcessHubData.
// 
// 13    12/16/08 10:49a Olegi
// Correction in the return values: 0 changed to NULL. EIP#17767.
// 
// 11    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 10    7/09/07 2:11p Olegi
// Changed the maximum data size of the BulkTransfer from 1kB to 64kB.
// 
// 9     4/17/07 8:24a Olegi
// Device detection algorythm update, in sync with Core8.
// 
// 8     3/20/07 12:19p Olegi
//
// 7     12/20/06 2:30p Olegi
//
// 5     10/26/06 4:01p Andriyn
//
// 4     7/10/06 2:58p Andriyn
// Fix: code simplifications
//
// 3     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 2     3/06/06 6:24p Olegi
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           UsbHub.c
//
//  Description:    AMI USB Hub support implementation
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "amiusb.h"

extern  USB_GLOBAL_DATA *gUsbData;

VOID*   USB_MemAlloc(UINT16);
UINT8   USB_MemFree(void _FAR_*, UINT16);
DEV_INFO*   USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);
UINT8   USB_StopDevice (HC_STRUC*,  UINT8, UINT8);
VOID    FixedDelay(UINTN);
UINT8   USB_ProcessPortChange (HC_STRUC*, UINT8, UINT8, UINT8);
UINT8   USB_InstallCallBackFunction (CALLBACK_FUNC  pfnCallBackFunction);
UINT8   USBCheckPortChange (HC_STRUC*, UINT8, UINT8);
UINT8	UsbControlTransfer(HC_STRUC*, DEV_INFO*, DEV_REQ, UINT16, VOID*);

UINT8   USBHUBDisconnectDevice (DEV_INFO*);
UINT8   USBHub_EnablePort(HC_STRUC*, UINT8, UINT8);
UINT8   USBHub_DisablePort(HC_STRUC*, UINT8, UINT8);
UINT8   USBHub_ResetPort(HC_STRUC*, UINT8, UINT8);

VOID    UsbHubDeviceInit(VOID);
UINT8   USBHubCheckDeviceType (DEV_INFO*, UINT8, UINT8, UINT8);
UINT8   USBHub_ProcessHubData(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
DEV_INFO*   USBHUBConfigureDevice (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT16);
UINT8	UsbHubResetPort(HC_STRUC*, DEV_INFO*, UINT8, BOOLEAN);

UINT8	UsbHubCearHubFeature(HC_STRUC*, DEV_INFO*, HUB_FEATURE);
UINT8	UsbHubClearPortFeature(HC_STRUC*, DEV_INFO*, UINT8, HUB_FEATURE);
UINT8	UsbHubGetHubDescriptor(HC_STRUC*, DEV_INFO*, VOID*, UINT16);
UINT8	UsbHubGetHubStatus(HC_STRUC*, DEV_INFO*, UINT32*);
UINT8	UsbHubGetPortStatus(HC_STRUC*, DEV_INFO*, UINT8, UINT32*);
UINT8	UsbHubGetErrorCount(HC_STRUC*, DEV_INFO*, UINT8, UINT16*);
UINT8	UsbHubSetHubDescriptor(HC_STRUC*, DEV_INFO*, VOID*, UINT16);
UINT8	UsbHubSetHubFeature(HC_STRUC*, DEV_INFO*, HUB_FEATURE);
UINT8	UsbHubSetHubDepth(HC_STRUC*, DEV_INFO*, UINT16);
UINT8	UsbHubSetPortFeature(HC_STRUC*, DEV_INFO*, UINT8, HUB_FEATURE);

PUBLIC
void
USBHubFillDriverEntries (DEV_DRIVER *fpDevDriver)
{
    fpDevDriver->bDevType               = BIOS_DEV_TYPE_HUB;
//  fpDevDriver->bBaseClass             = BASE_CLASS_HUB;
//  fpDevDriver->bSubClass              = SUB_CLASS_HUB;
    fpDevDriver->bProtocol              = 0;
    fpDevDriver->pfnDeviceInit          = UsbHubDeviceInit;
    fpDevDriver->pfnCheckDeviceType     = USBHubCheckDeviceType;
    fpDevDriver->pfnConfigureDevice     = USBHUBConfigureDevice;
    fpDevDriver->pfnDisconnectDevice    = USBHUBDisconnectDevice;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHUBConfigureDevice
//
// Description: This function checks an interface descriptor of a device
//              to see if it describes a USB hub.  If the device is a hub,
//              then it is configured and initialized.
//
// Input:   pHCStruc    HCStruc pointer
//          pDevInfo    Device information structure pointer
//          pDesc       Pointer to the descriptor structure
//                      supported by the device
//          wStart      Start offset of the device descriptor
//          wEnd        End offset of the device descriptor
//
// Output:  New device info structure, 0 on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USBHUBConfigureDevice (
    HC_STRUC*   fpHCStruc,
    DEV_INFO*   fpDevInfo,
    UINT8*      fpDesc,
    UINT16  wStart,
    UINT16  wEnd)
{
    UINT8           bPortNum;
    UINTN          DelayValue;
    UINT8*          fpBuffer;
    HUB_DESC        *fpHubDesc;
    UINT8           Status;
	DEV_INFO*		ParentHub;
	BOOLEAN			SetPortPower = FALSE;
    ENDP_DESC       *fpEndpDesc;
    INTRF_DESC      *fpIntrfDesc;
    INTRF_DESC      *AltIntrfDesc;
    UINT16          DescLength;
    UINT16          TotalLength;

	USB3_HUB_PORT_STATUS*	Usb3HubPortSts = (USB3_HUB_PORT_STATUS*)&gUsbData->dHubPortStatus;	

    //
    // Set the BiosDeviceType field in DeviceTableEntry[0].  This serves as a flag
    // that indicates a usable interface has been found in the current
    // configuration. This is needed so we can check for other usable interfaces
    // in the current configuration (i.e. composite device), but not try to search
    // in other configurations.
    //
    fpDevInfo->bDeviceType = BIOS_DEV_TYPE_HUB;
    fpDevInfo->bCallBackIndex = USB_InstallCallBackFunction(USBHub_ProcessHubData);

    fpIntrfDesc = (INTRF_DESC*)(fpDesc + wStart);

    // Check if the hub supports multiple TTs.
    if (fpDevInfo->Flag & DEV_INFO_ALT_SETTING_IF) {
        DescLength = wStart;
        TotalLength = ((CNFG_DESC*)fpDesc)->wTotalLength;
        for (;DescLength < TotalLength;) {
            AltIntrfDesc = (INTRF_DESC*)(fpDesc + DescLength);
            if ((AltIntrfDesc->bDescLength == 0) || 
                ((AltIntrfDesc->bDescLength + DescLength) > TotalLength)) {
                break;
            }
            if ((AltIntrfDesc->bDescType == DESC_TYPE_INTERFACE) && (AltIntrfDesc->bAltSettingNum != 0)) {
                if ((AltIntrfDesc->bBaseClass == BASE_CLASS_HUB) && 
                    (AltIntrfDesc->bSubClass == SUB_CLASS_HUB) && 
                    (AltIntrfDesc->bProtocol == PROTOCOL_HUB_MULTIPLE_TTS)) {
                    fpDevInfo->bProtocol = AltIntrfDesc->bProtocol;
                    fpDevInfo->bAltSettingNum = AltIntrfDesc->bAltSettingNum;
                    fpIntrfDesc = AltIntrfDesc;
                    break;
                }
            }
            if (AltIntrfDesc->bDescLength) {
                DescLength += (UINT16)AltIntrfDesc->bDescLength;
            } else {
                break;
            }
        }
    }

    fpDesc+=((CNFG_DESC*)fpDesc)->wTotalLength; // Calculate the end of descriptor block
    fpEndpDesc = (ENDP_DESC*)((char*)fpIntrfDesc + fpIntrfDesc->bDescLength);

    for( ;(fpEndpDesc->bDescType != DESC_TYPE_INTERFACE) && ((UINT8*)fpEndpDesc < fpDesc);
        fpEndpDesc = (ENDP_DESC*)((UINT8 *)fpEndpDesc + fpEndpDesc->bDescLength)){

        if(!(fpEndpDesc->bDescLength)) {
            break;  // Br if 0 length desc (should never happen, but...)
        }

        if( fpEndpDesc->bDescType != DESC_TYPE_ENDPOINT ) {
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
			fpDevInfo->IntInEndpoint = fpEndpDesc->bEndpointAddr;
			fpDevInfo->IntInMaxPkt = fpEndpDesc->wMaxPacketSize;
			fpDevInfo->bPollInterval = fpEndpDesc->bPollInterval;
			break;
		}
    }

    if ((fpHCStruc->dHCFlag & HC_STATE_CONTROLLER_WITH_RMH) &&
        (fpDevInfo->bHubDeviceNumber & BIT7)) {
        fpDevInfo->wIncompatFlags |= USB_INCMPT_RMH_DEVICE;
    }

	fpDevInfo->HubDepth = 0;
	ParentHub = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR, 
						NULL, fpDevInfo->bHubDeviceNumber, NULL);
	if(ParentHub) {
		fpDevInfo->HubDepth = ParentHub->HubDepth + 1;
	}
	
	if(fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_SUPER) {
		UsbHubSetHubDepth(fpHCStruc, fpDevInfo, fpDevInfo->HubDepth);
	}

    //
    // Allocate memory for getting hub descriptor
    //
    fpBuffer    = USB_MemAlloc(sizeof(MEM_BLK));
    if (!fpBuffer) {
		//USB_AbortConnectDev(fpDevInfo);   //(EIP59579-)
		return NULL;
    }

	Status = UsbHubGetHubDescriptor(fpHCStruc, fpDevInfo, fpBuffer, sizeof(MEM_BLK));
    if(Status != USB_SUCCESS) {    // Error
        USB_MemFree(fpBuffer, sizeof(MEM_BLK));
        //USB_AbortConnectDev(fpDevInfo);   //(EIP59579-)
		return NULL;
    }
    fpHubDesc                   = (HUB_DESC*)fpBuffer;
    fpDevInfo->bHubNumPorts     = fpHubDesc->bNumPorts;
    fpDevInfo->bHubPowerOnDelay = fpHubDesc->bPowerOnDelay; // Hub's ports have not been enumerated

    if (fpDevInfo->Flag & DEV_INFO_ALT_SETTING_IF) {
        if (fpDevInfo->bAltSettingNum != 0) {
            // Select this alternate setting for multiple TTs.
            UsbSetInterface(fpHCStruc, fpDevInfo, fpDevInfo->bAltSettingNum);
        }
    }

    //
    // Turn on power to all of the hub's ports by setting its port power features.
    // This is needed because hubs cannot detect a device attach until port power
    // is turned on.
    //
    for (bPortNum = 1; bPortNum <= fpDevInfo->bHubNumPorts; bPortNum++)
    {
        if (fpDevInfo->wIncompatFlags & USB_INCMPT_RMH_DEVICE &&
            bPortNum == fpHCStruc->DebugPort)
        {
            continue;
        }

		if (fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_SUPER) {
			UsbHubGetPortStatus(fpHCStruc, fpDevInfo, bPortNum, &gUsbData->dHubPortStatus);
			if (Usb3HubPortSts->PortStatus.Power == 1) {
				continue;
			}
		}

		UsbHubSetPortFeature(fpHCStruc, fpDevInfo, bPortNum, PortPower);
		SetPortPower = TRUE;
    }

    //
    // Delay the amount of time specified in the PowerOnDelay field of
    // the hub descriptor: in ms, add 30 ms to the normal time and multiply
    // by 64 (in 15us).
    //
    if(SetPortPower) {
        if (!(fpDevInfo->wIncompatFlags & USB_INCMPT_RMH_DEVICE)) {
	        if (gUsbData->PowerGoodDeviceDelay == 0) {
	            DelayValue = (UINTN)fpDevInfo->bHubPowerOnDelay * 2 * 1000;  // "Auto"
	        } else {
	            DelayValue = (UINTN)gUsbData->PowerGoodDeviceDelay * 1000* 1000;  // convert sec->15 mcs units
	        }
	        FixedDelay(DelayValue);
        }
    }

    fpDevInfo->fpPollTDPtr  = 0;
    fpDevInfo->fpPollEDPtr  = 0;

    //
    // Free the allocated buffer
    //
    USB_MemFree(fpBuffer, sizeof(MEM_BLK));

    fpDevInfo->HubPortConnectMap = 0;

    //
    // Check for new devices behind the hub
    //
    for (bPortNum = 1; bPortNum <= fpDevInfo->bHubNumPorts; bPortNum++) {
        USBCheckPortChange(fpHCStruc, fpDevInfo->bDeviceAddress, bPortNum);
    }

	fpDevInfo->PollingLength = fpDevInfo->IntInMaxPkt;

    // Start polling the new device's interrupt endpoint.
    (*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDActivatePolling)
                (fpHCStruc, fpDevInfo);

    return fpDevInfo;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHubDisconnect
//
// Description: This routine disconnects the hub by disconnecting all the
//      devices behind it
//
// Input:   pDevInfo    Device info structure pointer
//
// Output:  Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHUBDisconnectDevice (DEV_INFO*   fpDevInfo)
{
    HC_STRUC* fpHCStruc = gUsbData->HcTable[fpDevInfo->bHCNumber - 1];
    UINT8 bPort;

	// Stop polling the endpoint
	(*gUsbData->aHCDriverTable[GET_HCD_INDEX(fpHCStruc->bHCType)].pfnHCDDeactivatePolling)(fpHCStruc,fpDevInfo);
	fpDevInfo->IntInEndpoint = 0;

    //
    // A hub device is being disconnected.  For each of the hub's ports disconnect
    // any child device connected.
    //
    fpHCStruc = gUsbData->HcTable[fpDevInfo->bHCNumber - 1];

    for (bPort = 1; bPort <= (UINT8)fpDevInfo->bHubNumPorts; bPort++)
    {
        if (fpDevInfo->wIncompatFlags & USB_INCMPT_RMH_DEVICE &&
            bPort == fpHCStruc->DebugPort)
        {
            continue;
        }

        USB_StopDevice (fpHCStruc,  fpDevInfo->bDeviceAddress, bPort);
    }

    return USB_SUCCESS;

}

VOID
UsbHubDeviceInit(
    VOID
)
{
    USB_InstallCallBackFunction(USBHub_ProcessHubData);
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHubCheckDeviceType
//
// Description: This routine checks for hub type device from the
//      interface data provided
//
// Input:   bBaseClass  USB base class code
//          bSubClass   USB sub-class code
//          bProtocol   USB protocol code
//
// Output:  BIOS_DEV_TYPE_HUB type on success or 0FFH on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHubCheckDeviceType(
    DEV_INFO    *DevInfo,
    UINT8       BaseClass,
    UINT8       SubClass,
    UINT8       Protocol
)
{
    if (BaseClass == BASE_CLASS_HUB) {
        return BIOS_DEV_TYPE_HUB;
    } else {
        return USB_ERROR;
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHub_GetPortStatus
//
// Description: This routine returns the hub port status
//
// Input:   fpDevInfo   USB device - the hub whose status has changed
//              bit 7   : 1 - Root hub, 0 for other hubs
//              bit 6-0 : Device address of the hub
//      bPortNum    Port number
//      pHCStruc    HCStruc of the host controller
//
// Output:  Port status flags (Refer USB_PORT_STAT_XX equates)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHub_GetPortStatus (
    HC_STRUC*   HcStruc,
    UINT8       HubAddr,
    UINT8       PortNum,
    BOOLEAN     ClearChangeBits
)
{
    UINT8       PortSts = USB_PORT_STAT_DEV_OWNER;
	UINT8		Status;
    DEV_INFO    *DevInfo;
	HUB_FEATURE	Feature;
	UINT16		PortChange;
	UINT8		i = 0;

	HUB_PORT_STATUS*		HubPortSts = (HUB_PORT_STATUS*)&gUsbData->dHubPortStatus;
	USB3_HUB_PORT_STATUS*	Usb3HubPortSts = (USB3_HUB_PORT_STATUS*)&gUsbData->dHubPortStatus;	

    DevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR, NULL, HubAddr, HcStruc);
    ASSERT(DevInfo);
	if (DevInfo == NULL) {
        return 0;
    }

    if (DevInfo->wIncompatFlags & USB_INCMPT_RMH_DEVICE &&
		PortNum == HcStruc->DebugPort){
        return 0;
    }

    Status = UsbHubGetPortStatus(HcStruc, DevInfo, PortNum, &gUsbData->dHubPortStatus);
    if (Status == USB_ERROR) {
        return USB_ERROR;
    }

	USB_DEBUG(DEBUG_LEVEL_3, "Hub port[%d] status: %08x\n", PortNum, gUsbData->dHubPortStatus);

	if (DevInfo->bEndpointSpeed == USB_DEV_SPEED_SUPER) {
		for (i = 0; i < 20; i++) {
			if (Usb3HubPortSts->PortStatus.Reset == 0) {
                break;
            }
			FixedDelay(10 * 1000);	   // 10ms
			UsbHubGetPortStatus(HcStruc, DevInfo, PortNum, &gUsbData->dHubPortStatus);
		}

		switch (Usb3HubPortSts->PortStatus.LinkState) {
			case USB3_HUB_PORT_LINK_U0:
			case USB3_HUB_PORT_LINK_RXDETECT:
				break;
            case USB3_HUB_PORT_LINK_RECOVERY:
                for (i = 0; i < 20; i++) {
				    FixedDelay(10 * 1000);
                    UsbHubGetPortStatus(HcStruc, DevInfo, PortNum, &gUsbData->dHubPortStatus);
                    if (Usb3HubPortSts->PortStatus.LinkState != USB3_HUB_PORT_LINK_RECOVERY) {
                        break;
                    }
                }
			    break;
			case USB3_HUB_PORT_LINK_POLLING:
			    for (i = 0; i < 50; i++) {
                    FixedDelay(10 * 1000);
                    UsbHubGetPortStatus(HcStruc, DevInfo, PortNum, &gUsbData->dHubPortStatus);
                    if (Usb3HubPortSts->PortStatus.LinkState != USB3_HUB_PORT_LINK_POLLING) {
                        break;
                    }
                }
                if (Usb3HubPortSts->PortStatus.LinkState == USB3_HUB_PORT_LINK_U0 || 
                    Usb3HubPortSts->PortStatus.LinkState == USB3_HUB_PORT_LINK_RXDETECT) {
                    break;
			    }
            case USB3_HUB_PORT_LINK_INACTIVE:
                // A downstream port can only exit from this state when directed, 
                // or upon detection of an absence of a far-end receiver termination 
                // or upon a Warm Reset.
                // The Timeout of SS.Inactive.Quiet is 12 ms.
                FixedDelay(12 * 1000);
                UsbHubGetPortStatus(HcStruc, DevInfo, PortNum, &gUsbData->dHubPortStatus);
                if (Usb3HubPortSts->PortStatus.LinkState == USB3_HUB_PORT_LINK_RXDETECT) {
                    break;
                }
			case USB3_HUB_PORT_LINK_COMPLIANCE_MODE:
				UsbHubResetPort(HcStruc, DevInfo, PortNum, TRUE);
				break;
			default:
				PortSts |= USB_PORT_STAT_DEV_CONNECTED;
				break;
		}
		if (Usb3HubPortSts->PortChange.ConnectChange) {
			PortSts |= USB_PORT_STAT_DEV_CONNECT_CHANGED;
            DevInfo->HubPortConnectMap &= (UINT16) (~(1 << PortNum));
			//UsbHubClearPortFeature(HcStruc, DevInfo, PortNum, PortConnectChange);
		}
		if (Usb3HubPortSts->PortStatus.Connected) {
            DevInfo->HubPortConnectMap |= (UINT16) (1 << PortNum);
			PortSts |= USB_PORT_STAT_DEV_CONNECTED | USB_PORT_STAT_DEV_SUPERSPEED;
	
			// USB 3.0 hub may not set Connect Status Change bit,
			// set the connect change flag if the BH Reset change or Reset change is set.
			if (Usb3HubPortSts->PortChange.BhResetChange || Usb3HubPortSts->PortChange.ResetChange) {
				PortSts |= USB_PORT_STAT_DEV_CONNECT_CHANGED;
			}
			if (Usb3HubPortSts->PortStatus.Enabled) {
				PortSts |= USB_PORT_STAT_DEV_ENABLED;
			}
		}
        if (Usb3HubPortSts->PortChange.OverCurrentChange) {
            if ((Usb3HubPortSts->PortStatus.OverCurrent == 0) && 
                (Usb3HubPortSts->PortStatus.Power == 0)) {
                UsbHubSetPortFeature(HcStruc, DevInfo, PortNum, PortPower);
                FixedDelay((UINTN)(DevInfo->bHubPowerOnDelay * 2 * 1000));
            }
        }
	} else {
		if (HubPortSts->PortChange.ConnectChange) {
			PortSts |= USB_PORT_STAT_DEV_CONNECT_CHANGED;
			//UsbHubClearPortFeature(HcStruc, DevInfo, PortNum, PortConnectChange);
            DevInfo->HubPortConnectMap &= (UINT16) (~(1 << PortNum));
			//if(HubPortSts->PortStatus.Connected) {
				// Delay for 100ms allowing power to settle.
				//FixedDelay(gUsbData->UsbTimingPolicy.HubPortConnect * 1000);	   // 50ms
			//}
		}
		if (HubPortSts->PortStatus.Connected) {
			PortSts |= USB_PORT_STAT_DEV_CONNECTED;
            DevInfo->HubPortConnectMap |= (UINT16) (1 << PortNum);
			if (HubPortSts->PortStatus.LowSpeed) {
				PortSts |= USB_PORT_STAT_DEV_LOWSPEED;
			} else if (HubPortSts->PortStatus.HighSpeed) {
				PortSts |= USB_PORT_STAT_DEV_HISPEED;
			} else {
				PortSts |= USB_PORT_STAT_DEV_FULLSPEED;
			}
			if (HubPortSts->PortStatus.Enabled) {
				PortSts |= USB_PORT_STAT_DEV_ENABLED;
			}
		}
        if (HubPortSts->PortChange.OverCurrentChange) {
            if ((HubPortSts->PortStatus.OverCurrent == 0) && 
                (HubPortSts->PortStatus.Power == 0)) {
                UsbHubSetPortFeature(HcStruc, DevInfo, PortNum, PortPower);
                FixedDelay((UINTN)(DevInfo->bHubPowerOnDelay * 2 * 1000));
            }
        }
	}
	
	// Clear all port status change
	//UsbHubGetPortStatus(HcStruc, DevInfo, PortNum, &gUsbData->dHubPortStatus);
    if (ClearChangeBits == TRUE) {
    	PortChange = (*((UINT16*)&HubPortSts->PortChange));
    	for (Feature = PortConnectChange; Feature <= PortResetChange; Feature++) {
    		if (PortChange & 1) {
    			UsbHubClearPortFeature(HcStruc, DevInfo, PortNum, Feature);
    		}
    		PortChange >>= 1;
    	}

    	if (DevInfo->bEndpointSpeed == USB_DEV_SPEED_SUPER) {
    		if (Usb3HubPortSts->PortChange.LinkStateChange) {
    			UsbHubClearPortFeature(HcStruc, DevInfo, PortNum, PortLinkStateChange);
    		}
    		if (Usb3HubPortSts->PortChange.ConfigErrorChange) {
    			UsbHubClearPortFeature(HcStruc, DevInfo, PortNum, PortConfigErrorChange);
    		}
    		if (Usb3HubPortSts->PortChange.BhResetChange) {
    			UsbHubClearPortFeature(HcStruc, DevInfo, PortNum, BhPortResetChange);
    		}
    	}
    }

    return PortSts;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHub_DisablePort
//
// Description: This routine disables the hub port
//
// Input:   bHubAddr    USB device address of the hub whose status
//              has changed
//              bit 7   : 1 - Root hub, 0 for other hubs
//              bit 6-0 : Device address of the hub
//      bPortNum    Port number
//      pHCStruc    HCStruc of the host controller
//
// Output:  USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHub_DisablePort(
    HC_STRUC*   fpHCStruc,
    UINT8       bHubAddr,
    UINT8       bPortNum)
{
    DEV_INFO*   fpDevInfo;

	HUB_PORT_STATUS*	HubPortSts = (HUB_PORT_STATUS*)&gUsbData->dHubPortStatus;
	
    //
    // Get DeviceInfo pointer
    //
    fpDevInfo   = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR,
                            (DEV_INFO*)0,
                            bHubAddr,
                            fpHCStruc);
//
// Disable the hub/port by clearing its Enable feature
//
    if (fpDevInfo->wIncompatFlags & USB_INCMPT_RMH_DEVICE &&
            bPortNum == fpHCStruc->DebugPort)
    {
        return USB_SUCCESS;
    }

	if(fpDevInfo->bEndpointSpeed == USB_DEV_SPEED_SUPER) return USB_SUCCESS;

	UsbHubGetPortStatus(fpHCStruc, fpDevInfo, bPortNum, &gUsbData->dHubPortStatus);

    // Perform control transfer with device request as HUB_RQ_CLEAR_PORT_FEATURE,
    // wIndex = Port number, wValue = HUB_FEATURE_PORT_ENABLE,
    // fpBuffer = 0 and wlength = 0
    //
    if(HubPortSts->PortStatus.Enabled) {
	    UsbHubClearPortFeature(fpHCStruc, fpDevInfo, bPortNum, PortEnable);
    }

    return USB_SUCCESS;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHub_EnablePort
//
// Description: This routine enables the hub port
//
// Input:   bHubAddr    USB device address of the hub whose status
//              has changed
//              bit 7   : 1 - Root hub, 0 for other hubs
//              bit 6-0 : Device address of the hub
//      bPortNum    Port number
//      pHCStruc    HCStruc of the host controller
//
// Output:  USB_SUCCESS if the hub port is enabled. USB_ERROR otherwise
//
// Modified:    Nothing
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHub_EnablePort(
    HC_STRUC*   fpHCStruc,
    UINT8       bHubAddr,
    UINT8       bPortNum)
{
    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHub_ResetPort
//
// Description: This routine resets the hub port
//
// Input:   HCStruc    HCStruc of the host controller
//			HubAddr    USB device address of the hub whose status
//              		has changed
//              bit 7   : 1 - Root hub, 0 for other hubs
//              bit 6-0 : Device address of the hub
//      	PortNum    Port number
//
// Output:  USB_SUCCESS if the hub port is enabled. USB_ERROR otherwise
//
// Modified:    Nothing
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHub_ResetPort(
    HC_STRUC*   HcStruc,
    UINT8       HubAddr,
    UINT8       PortNum)
{
	UINT8		Status;
    DEV_INFO*   DevInfo;

    //
    // Get DeviceInfo pointer
    //
    DevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR, 
    						(DEV_INFO*)0, HubAddr, HcStruc);
    if (DevInfo == NULL) return USB_ERROR;

    if ((DevInfo->wIncompatFlags & USB_INCMPT_RMH_DEVICE) && 
		(PortNum == HcStruc->DebugPort)) {
        return USB_SUCCESS;
    }
	Status = UsbHubResetPort(HcStruc, DevInfo, PortNum, FALSE);

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBHub_ProcessHubData
//
// Description: This routine is called with USB hub status change
//      report data
//
// Input:   pHCStruc    Pointer to HCStruc
//          pDevInfo    Pointer to device information structure
//          pTD         Pointer to the polling TD
//          pBuffer     Pointer to the data buffer
//
//
// Notes:   The status change data is an array of bit flags:
//          Bit     Description
//      ----------------------------------------------------------
//          0   Indicate connect change status for all ports
//          1   Indicate connect change status for port 1
//          2   Indicate connect change status for port 2
//          ...     ..............
//          n   Indicate connect change status for port n
//      -----------------------------------------------------------
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBHub_ProcessHubData (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Td,
    UINT8       *Buffer,
    UINT16      DataLength
 )
{
    UINT8       PortNum;
    UINT16      PortMap;
    BOOLEAN     ConnectDelay = FALSE;

    USB_DEBUG(DEBUG_LEVEL_3, "USBHub_ProcessHubData, gUsbData->bEnumFlag = %d\n", gUsbData->bEnumFlag);
    //
    // Check for enum flag and avoid hub port enumeration if needed
    //
    if (gUsbData->bEnumFlag == TRUE) return USB_SUCCESS;
    
    for (PortNum = 1; PortNum <= DevInfo->bHubNumPorts; PortNum++) {
        PortMap = (UINT16)(1 << PortNum);
        if (*(UINT16*)Buffer & PortMap) {
            if (!ConnectDelay && ((~DevInfo->HubPortConnectMap) & PortMap)) {
                //Delay for 50 ms allowing port to settle.
                FixedDelay(50 * 1000);
                ConnectDelay = TRUE;
            }
            //
            // Set enumeration flag so that another device will not get enabled
            //
            gUsbData->bEnumFlag = TRUE;

            USBCheckPortChange(HcStruc, DevInfo->bDeviceAddress, PortNum);

            //
            // Reset enumeration flag so that other devices can be enumerated
            //
            gUsbData->bEnumFlag = FALSE;
        }
    }
	return USB_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubResetPort
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubResetPort(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8		Port,
    BOOLEAN		WarmReset)
{
	UINT8		Status;
	UINT8		i;
	BOOLEAN		IsResetChange;

	HUB_PORT_STATUS*		HubPortSts = (HUB_PORT_STATUS*)&gUsbData->dHubPortStatus;
	USB3_HUB_PORT_STATUS*	Usb3HubPortSts = (USB3_HUB_PORT_STATUS*)&gUsbData->dHubPortStatus;	

	if (WarmReset && DevInfo->bEndpointSpeed == USB_DEV_SPEED_SUPER) {
		Status = UsbHubSetPortFeature(HcStruc, DevInfo, Port, BhPortReset);
		if(Status != USB_SUCCESS) return USB_ERROR;
		
		for(i = 0; i < 10; i++) {
			FixedDelay(10 * 1000);
			Status = UsbHubGetPortStatus(HcStruc, DevInfo, Port, &gUsbData->dHubPortStatus);
			if(Status != USB_SUCCESS) return USB_ERROR;
		
			if(Usb3HubPortSts->PortChange.BhResetChange) break;
		}
		if (!Usb3HubPortSts->PortChange.BhResetChange) {
			return USB_ERROR;
		}
		
		Status = UsbHubClearPortFeature(HcStruc, DevInfo, Port, BhPortResetChange);
		if(Status != USB_SUCCESS) return USB_ERROR;
		
		Status = UsbHubClearPortFeature(HcStruc, DevInfo, Port, PortResetChange);
		if(Status != USB_SUCCESS) return USB_ERROR;

	} else {
		Status = UsbHubSetPortFeature(HcStruc, DevInfo, Port, PortReset);
		if(Status != USB_SUCCESS) return USB_ERROR;

        // The duration of the Resetting state is nominally 10 ms to 20 ms
        FixedDelay(20 * 1000);      // 20 ms delay

		for(i = 0; i < 10; i++) {
			Status = UsbHubGetPortStatus(HcStruc, DevInfo, Port, &gUsbData->dHubPortStatus);
			if(Status != USB_SUCCESS) return USB_ERROR;

			if(DevInfo->bEndpointSpeed == USB_DEV_SPEED_SUPER) {
				IsResetChange = Usb3HubPortSts->PortChange.ResetChange ? TRUE : FALSE;
			} else {
				IsResetChange = HubPortSts->PortChange.ResetChange ? TRUE : FALSE;
			}

			if(IsResetChange) break;

            FixedDelay(5 * 1000);      // 5 ms delay
		}
		if (!IsResetChange) {
			return USB_ERROR;
		}

		Status = UsbHubClearPortFeature(HcStruc, DevInfo, Port, PortResetChange);
		if(Status != USB_SUCCESS) return USB_ERROR;

		if (DevInfo->bEndpointSpeed != USB_DEV_SPEED_SUPER) {
			if (!(DevInfo->wIncompatFlags & USB_INCMPT_RMH_DEVICE)) {
				FixedDelay(20 * 1000);	   // 20 ms
			} else if (HubPortSts->PortStatus.LowSpeed == 1) {
				// 1 ms delay for Low-Speed device
				FixedDelay(1 * 1000);
			}
		}
	}
	return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubCearHubFeature
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubCearHubFeature(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    HUB_FEATURE	HubFeature)
{
	return USB_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubClearPortFeature
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubClearPortFeature(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8		Port,
    HUB_FEATURE	PortFeature)
{
	DEV_REQ	DevReq;

	DevReq.wRequestType = HUB_RQ_CLEAR_PORT_FEATURE;
	DevReq.wValue = PortFeature;
	DevReq.wIndex = Port;
	DevReq.wDataLength = 0;

	return UsbControlTransfer(HcStruc, DevInfo, DevReq, 50, NULL);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubGetHubDescriptor
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubGetHubDescriptor(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    VOID*		Buffer,
    UINT16		Length)
{
	DEV_REQ	DevReq;

	DevReq.wRequestType = USB_RQ_GET_CLASS_DESCRIPTOR;
	DevReq.wValue = DevInfo->bEndpointSpeed == 
						USB_DEV_SPEED_SUPER ? DESC_TYPE_SS_HUB << 8 : DESC_TYPE_HUB << 8;
	DevReq.wIndex = 0;
	DevReq.wDataLength = Length;

	return UsbControlTransfer(HcStruc, DevInfo, DevReq, 150, Buffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubGetHubStatus
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubGetHubStatus(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT32*		HubStatus)
{
	return USB_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubGetPortStatus
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubGetPortStatus(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
	UINT8		Port,
    UINT32*		PortStatus)
{
	DEV_REQ	DevReq;

	DevReq.wRequestType = HUB_RQ_GET_PORT_STATUS;
	DevReq.wValue = 0;
	DevReq.wIndex = Port;
	DevReq.wDataLength = 4;

	return UsbControlTransfer(HcStruc, DevInfo, DevReq, 150, PortStatus);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubGetErrorCount
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubGetErrorCount(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8		Port,
    UINT16*		ErrorCount)
{
	return USB_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubSetHubDescriptor
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubSetHubDescriptor(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
	VOID*		Buffer,
    UINT16		Length)
{
	return USB_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubSetHubFeature
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubSetHubFeature(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    HUB_FEATURE	HubFeature)
{
	return USB_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubSetHubDepth
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubSetHubDepth(
	HC_STRUC*	HcStruc,
	DEV_INFO*	DevInfo,
	UINT16		HubDepth)
{
	DEV_REQ	DevReq;

	DevReq.wRequestType = HUB_RQ_SET_HUB_DEPTH;
	DevReq.wValue = HubDepth;
	DevReq.wIndex = 0;
	DevReq.wDataLength = 0;

	return UsbControlTransfer(HcStruc, DevInfo, DevReq, 50, NULL);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UsbHubSetPortFeature
//
// Description: 
//
// Input:   
//
// Output: USB_ERROR on error, USB_SUCCESS on success
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbHubSetPortFeature(
	HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8		Port,
    HUB_FEATURE	PortFeature)
{
	DEV_REQ	DevReq;

	DevReq.wRequestType = HUB_RQ_SET_PORT_FEATURE;
	DevReq.wValue = PortFeature;
	DevReq.wIndex = Port;
	DevReq.wDataLength = 0;

	return UsbControlTransfer(HcStruc, DevInfo, DevReq, 100, NULL);		//(EIP77526)		 
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
