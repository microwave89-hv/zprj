#pragma warning(disable: 4001)
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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbpoint.c 17    4/29/15 5:29a Wilsonlee $
//
// $Revision: 17 $
//
// $Date: 4/29/15 5:29a $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbpoint.c $
// 
// 17    4/29/15 5:29a Wilsonlee
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
// 16    4/14/15 11:46p Wilsonlee
// [TAG]  		EIP213778
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Issue with right button on usb absolute mouses.
// [RootCause]  	For the absolute device, it has digitizers page
// (UsagePage is 0xD) or button page (UsagePage is 0x9). We clear button
// data even if it is from button page.
// [Solution]  	Clear the unnecessary bits if the data is from digitizers
// page and return all button data if it is from button page.
// [Files]  		usbpoint.c
// 
// 15    9/04/14 7:42a Wilsonlee
// [TAG]  		EIP183463
// [Category]  	Improvement
// [Description]  	In UEFI spec, the definitions of bits within
// ActiveButtons are EFI_ABSP_TouchActive and EFI_ABS_AltActive, we don't
// support AltActive, clear the unnecessary bits.
// [Files]  		usbpoint.c
// 
// 14    5/12/14 3:29a Wilsonlee
// [TAG]  		EIP168389
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Usb tip switch data may not be correct if the device is
// multi-touch.
// [RootCause]  	We get the data from the other point, but we only support
// one point.
// [Solution]  	Only get the first point data.
// [Files]  		usbpoint.c
// 
// 13    5/06/14 5:16a Ryanchou
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
// 12    2/26/14 1:56a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 11    3/08/13 4:18a Roberthsu
// [TAG]           EIP114280
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       vPro KVM Mouse can not work.
// [RootCause]     Get wrong button offset.
// [Solution]      Check usagemin  get correct button offset.
// [Files]         usbpoint.c
// 
// 10    1/11/13 4:16a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 9     11/10/12 6:40a Ryanchou
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
// 8     10/26/12 8:49a Roberthsu
// [TAG]           EIP101990 
// [Category]      Improvement
// [Description]   Add check inpurt mode.
// [Files]         usbhid.c,usbpoint.c
// 
// 7     9/14/12 5:11a Roberthsu
// [TAG]           EIP101018
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Button funtion not work
// [RootCause]     Get wrong button status offset.
// [Solution]      Get correct button status offset.
// [Files]         usbpoint.c
// 
// 6     3/05/12 2:18a Roberthsu
// [TAG]           EIP81983
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Setup menu no response after update N-trig firmware.
// [RootCause]     LogicalMax need use report item's value.
// [Solution]      Correct LogicalMax parameter.
// [Files]         usbpoint.c
// 
// 5     1/13/12 4:06a Roberthsu
// [TAG]           EIP80173
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Cando touch screen cannot work .
// [RootCause]     Touch screen need send set_idle command.
// [Solution]      Add set_idle command.
// [Files]         usbpoint.c
// 
// 4     1/09/12 1:05a Roberthsu
// [TAG]           EIP79323
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Touch Screen cannot work smoothly
// [RootCause]     There are some empty data.
// [Solution]      Check empty data then exit.
// [Files]         usbpoint.c
// 
// 3     11/21/11 10:58p Roberthsu
// [TAG]           EIP75015
// [Category]      Improvement
// [Description]   Report button status direct.
// [Files]         usbpoint.c
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
// 1     7/15/11 6:18a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, efiusbpoint.c, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c,
// usb.c, usbdef.h, usbhid.c, usbkbd.c, usbkbd.h, usbms.c, usbpoint.c,
// usbrt.cif, usbsb.c, usbsetup.c, usbsrc.sdl, xhci.c
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           UsbPoint.c
//
//  Description:    AMI USB Absolute Device support implementation
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "amiusb.h"
#include "usbkbd.h"
#include <Protocol/AbsPointerProtocol.h>

extern  USB_GLOBAL_DATA     *gUsbData;

static BOOLEAN globalAbsolutePolling = TRUE;

UINT8       USBAbsProcessMouseData (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID		SetABSData (UINT8*,UINT16*,UINT8,UINT8,UINT16);			 
UINT16      PerviousXPosition = 0;
UINT16      PerviousYPosition = 0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBAbsConfigureDevice 
//
// Description: This routine checks an interface descriptor of the USB device
//              detected to see if it describes a HID/Boot/Mouse device.
//              If the device matches the above criteria, then the device is
//              configured and initialized
//
// Input:       HcStruc   HCStruc pointer
//              DevInfo   Device information structure pointer
//              Desc      Pointer to the descriptor structure
//              Start     Offset within interface descriptor
//                      supported by the device
//              End       End offset of the device descriptor
//
// Output:      FPDEV_INFO  New device info structure, 0 on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USBAbsConfigureDevice (
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Desc,
    UINT16      Start,
    UINT16      End
)
{
    return NULL;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBAbsProcessMouseData
//
// Description: 
//
// Input:       HcStruc   Pointer to HCStruc
//              DevInfo   Pointer to device information structure
//              Td        Pointer to the polling TD
//              Buffer    Pointer to the data buffer
//
// Output:      Nothing
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBAbsProcessMouseData (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Td,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
	USBABS_DATA	        AbsBuffer;
	HID_REPORT_FIELD	*Field = NULL;
	UINT8 	            OffsetTmp = 0;
    UINT8               XStart = 0;
    UINT8               XEnd;
    UINT8               YStart = 0;
    UINT8               YEnd;
    UINT8               ButtonStart = 0;
    UINT8               ButtonEnd = 0;
    UINT8               i;
    UINT16              j;
	UINT16 	            MaxX;
    UINT16              MaxY;
    BOOLEAN             SetButtonData = FALSE;
    BOOLEAN             SetXData = FALSE;
    BOOLEAN             SetYData = FALSE;

    AbsBuffer.X =0;
    AbsBuffer.Y =0;
    AbsBuffer.Button =0;
    
	for (i = 0; i < DevInfo->HidReport.FieldCount; i++) {
		Field = DevInfo->HidReport.Fields[i];

		//Check is input?
		if (!(Field->Flag & HID_REPORT_FIELD_FLAG_INPUT)) {
			continue;
		}

		// Check if report id is matched
		if (Field->ReportId != 0 && Field->ReportId != Buffer[0]) {
			continue;
		}

        // Check if the field is contant.
        if (Field->Flag & HID_REPORT_FIELD_FLAG_CONSTANT) {
            OffsetTmp += Field->ReportCount * Field->ReportSize;
            continue;
        }

		if ((Field->UsagePage == 0xd) && (Field->UsageCount != 0)) {
			for (j = 0; j < Field->UsageCount; j++) {
				//Check Tip switch
				if (Field->Usages[j] == 0x42) {					//(EIP79323)
                    if (SetButtonData == TRUE) {
                        break;
                    }
					ButtonStart = OffsetTmp;
					if (Field->ReportId != 0) {
						ButtonStart += 8; 
					}
                    ButtonEnd = ButtonStart + (Field->ReportSize * Field->ReportCount);		//(EIP101990)
                    SetABSData(Buffer, (UINT16*)(&AbsBuffer.Button), ButtonStart, ButtonEnd, 0xffff);        				//(EIP101990) 
                    SetButtonData = TRUE;
                    //In UEFI spec, the definitions of bits within ActiveButtons are EFI_ABSP_TouchActive
                    // and EFI_ABS_AltActive, we don't support AltActive, clear the unnecessary bits.
                    AbsBuffer.Button &= EFI_ABSP_TouchActive;
				}
			}
		}

		//Check Button
		if ((Field->UsagePage == 9) && (Field->UsageCount != 0) && (Field->Usages[0] == 1)) {	//(EIP114280)
            if (SetButtonData == TRUE) {
                break;
            }
			ButtonStart = OffsetTmp;
			if (Field->ReportId != 0) {
				ButtonStart += 8;
			}
            ButtonEnd = ButtonStart + Field->ReportSize * Field->ReportCount;		//(EIP101018)
            SetABSData(Buffer, (UINT16*)(&AbsBuffer.Button), ButtonStart, ButtonEnd, 0xffff);        				//(EIP101018)
            SetButtonData = TRUE;
		}

		//Check X,Y
		if ((Field->UsagePage == 1) && (Field->UsageCount != 0)) {
			for (j = 0; j < Field->UsageCount; j++) {
				//find X
				if (Field->Usages[j] == 0x30) {
                    if (SetXData == TRUE) {
                        break;
                    }
					XStart = OffsetTmp + (j * Field->ReportSize);
					if (Field->ReportId != 0) {
						XStart += 8;
					}
					XEnd = XStart + Field->ReportSize;
					SetABSData(Buffer, &AbsBuffer.X, XStart, XEnd, Field->LogicalMax);        //(EIP81983)
                    SetXData = TRUE;
					MaxX = Field->LogicalMax;
				}

				//find Y
				if (Field->Usages[j] == 0x31) {
                    if (SetYData == TRUE) {
                        break;
                    }
					YStart = OffsetTmp + (j * Field->ReportSize);
					if (Field->ReportId != 0) {
						YStart += 8;
					}
					YEnd = YStart + Field->ReportSize;
					MaxY = Field->LogicalMax; 
					SetABSData(Buffer, &AbsBuffer.Y, YStart, YEnd, Field->LogicalMax);        //(EIP81983)
                    SetYData = TRUE;
				}
			}
		}
		OffsetTmp += Field->ReportCount * Field->ReportSize;
	}
	
    if (AbsBuffer.Button == 0 && AbsBuffer.X == 0 && AbsBuffer.Y == 0) {
        return USB_SUCCESS;
    }
    
    if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {
        gUsbData->AbsMouseData[0].ButtonStauts = AbsBuffer.Button;
        gUsbData->AbsMouseData[0].Xcoordinate = AbsBuffer.X;
        gUsbData->AbsMouseData[0].Ycoordinate = AbsBuffer.Y;
        gUsbData->AbsMouseData[0].Pressure = 0;
		gUsbData->AbsMouseData[0].Max_X = MaxX;
		gUsbData->AbsMouseData[0].Max_Y = MaxY;
    }
    return USB_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetABSData
//
// Description: 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
SetABSData (
    UINT8       *Buffer,
    UINT16 		*ReportData,
    UINT8 		Start,
    UINT8 		End,
    UINT16 		Maxvalue
)
{
	UINT8 	ReportSize;
    UINT8   Size;
    UINT8   PreSkip;
    UINT8   PostSkip;
	UINT32  TempData = 0;
    
	ReportSize = End - Start;
	Size = ReportSize / 8;
    
	if ((ReportSize % 8) !=0) {
        Size++;
    }

	ASSERT(Size > 0 && Size <= sizeof(TempData));
    if ((Size == 0) || (Size > sizeof(TempData))) {
        return;
    }
    
	MemCpy(&TempData, Buffer + Start / 8, Size);
    
	PreSkip = Start % 8;
	PostSkip = End % 8;

	if (PreSkip != 0) {
		TempData = TempData >> PreSkip;
	}
    
	if (PostSkip != 0) {
		TempData = TempData << PostSkip;
		TempData = TempData >> PostSkip;
	}
    
	if (TempData > Maxvalue) {
		TempData &= Maxvalue;
	}
    
	*ReportData = (UINT16)TempData;
	USB_DEBUG (DEBUG_LEVEL_4, "out data %x\n",*ReportData);
    
	return;
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
