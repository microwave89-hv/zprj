#pragma warning(disable: 4001)
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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbms.c 50    10/16/16 10:12p Wilsonlee $
//
// $Revision: 50 $
//
// $Date: 10/16/16 10:12p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbms.c $
// 
// 50    10/16/16 10:12p Wilsonlee
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
// 49    4/29/15 5:29a Wilsonlee
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
// 48    2/24/15 5:50a Wilsonlee
// [TAG]  		EIP149716
// [Category]  	Improvement
// [Description]  	Error Handling in USB mouse data.
// [Files]  		usbms.c, usbkbd.h, syskbc.c, xhci.c
// 
// 47    12/24/14 9:33p Wilsonlee
// [TAG]  		EIP194683
// [Category]  	Improvement
// [Description]  	Add the flag "USB_INCMPT_HID_BOOT_PROTOCOL_ONLY" of usb
// bad device table to keep devices use boot protocol.
// [Files]  		usbkbd.c, usbms.c, usbhid.c, usbdef.h
// 
// 46    8/12/14 3:04a Wilsonlee
// [TAG]  		EIP180970
// [Category]  	Improvement
// [Description]  	Update X and Y data to usbmousedata and install
// SimplePointerProtocol interface if the mouses are using boot protocol
// interface.
// [Files]  		efiusbhid.c, usbms.c
// 
// 45    5/06/14 5:16a Ryanchou
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
// 44    2/26/14 1:55a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 43    12/30/13 3:47a Wilsonlee
// [TAG]  		EIP148707
// [Category]  	Improvement
// [Description]  	We need to store wheel data before clearing the buffer.
// [Files]  		usbms.c, efiusbms.c
// 
// 42    8/22/13 6:33a Wilsonlee
// [TAG]  		EIP122944
// [Category]  	Improvement
// [Description]  	Remove mouse_flag3 and check the mouse interface status
// in the CCB byte before we send the data to KBC.
// [Files]  		syskbc.c, usbms.c
// 
// 41    7/04/13 5:46a Roberthsu
// [TAG]           EIP127014 
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Mouse drifting not smooth
// [RootCause]     Bbecause Efi simple point protocol RelativeMovementX
// type is INT32.
// [Solution]      Transfer data type to INT32.
// [Files]         usbdef.h,usbhid.c,usbms.c,usbkbd.h
// 
// 40    1/11/13 4:15a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 39    11/10/12 6:39a Ryanchou
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
// 38    8/21/12 2:33a Roberthsu
// [TAG]           EIP91835
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Wireless mouse auto click" problem
// [RootCause]     Because button status and X Y in different packet.
// [Solution]      Save button status.
// [Files]         usbms.c
// 
// 37    8/07/12 12:07a Roberthsu
// [TAG]           EIP95351
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Usb mouse work unnormal
// [RootCause]     This mouse will send garbage data.
// [Solution]      Change check section
// [Files]         usbms.c
// 
// 36    5/03/12 6:30a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 35    9/27/11 1:40a Roberthsu
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
// 34    9/19/11 9:34a Lavanyap
// [TAG]  		EIP66198
// [Category]  	Improvement
// [Description]  	Added Mouse Wheel support in PS2 and USB drivers.
// [Files]  		usbdef.h, usbms.c, efiusbms.c, ps2mouse.h, mouse.c
// 
// 33    8/05/11 2:03a Ryanchou
// 
// 32    7/15/11 6:11a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c, usb.c, usbdef.h,
// usbkbd.c, usbkbd.h, usbms.c, usbrt.cif, usbsb.c, usbsetup.c,
// usbsrc.sdl, xhci.c
// 
// 31    7/12/11 11:40p Ryanchou
// [TAG] EIP63752
// [Bug fix] Left click status lost on USB Mousee.
// [Symptom] First time Getstate will return that Left Click is Pressed.
// On the Second GetState Call it will return that Left click released.
// [Root Cause] We are clearing the Button status once we send the data.
// So next time getstate will return that left click is released.
// [Solution] We should not clear the ButtonStatus.Insteed of OR the data,
// we should have taken directly from the fpBuffer.
// 
// 30    5/03/11 6:56a Ryanchou
// [TAG]  		EIP57745
// [Category]  	Improvement
// [Description]  	The token CHECK_MOUSE_FLAG is depend on CSM version,
// remove the token and check CSM verion to support this feature or not.
// [Files]  		syskbc.c, usbms.c, usbsrc.sdl
// 
// 29    3/30/11 8:16a Ryanchou
// [TAG]  		EIP54126
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Sometimes system hangs at checkpoint 0xB4.
// [RootCause]  	The bLength field of configuration descriptor is zero.
// [Solution]  	Check wether bLength field is zero before paring next
// descriptor.
// [Files]  		usb.c, usbbus.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c
// 
// 28    3/17/11 12:23a Ryanchou
// [TAG]  		EIP49214
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	USB mouse can't work on legacy free system
// [RootCause]  	The key repeat SMI didn't enabled.
// [Solution]  	Enable the key repeat SMI if receive mouse data.
// [Files]  		usbms.c
// 
// 27    2/10/11 7:41a Ryanchou
// [TAG]  		EIP52206
// [Category]  	Improvement
// [Description]  	Remote wakeup command should be sent before sleep,
// comment out  the command.
// [Files]  		usbkbd.c, usbms.c
// 
// 26    1/17/11 4:35a Ryanchou
// [TAG]  		EIP51108
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Some HID devices that has two interfaces can't work.
// [RootCause]  	BIOS using the wrong endpoint to poll KBD/MS data. 
// [Solution]  	Get the first interrupt in endpoint when parsing
// descriptors.
// [Files]  		usbkbd.c, usbms.c
// 
// 25    9/24/10 5:38p Olegi
// EIP38221: Added the code that properly initializes
// DEV_INFO.bIntEndpoint field; interrupt endpoint polling is using this
// endpoint number.
// 
// 24    9/16/10 1:08p Olegi
// - removed junk function code
// - EIP40959:: activate mouse polling depending on the project settings
// 
// 23    9/08/10 8:05a Ryanchou
// EIP43822: Add a toekn "CHECK_MOUSE_FLAG", the token controls whether
// apply EIP40121 solution.
// 
// 22    8/30/10 12:16p Olegi
// Send mouse data only when driver is active; EIP40121
// 
// 21    6/22/10 9:11p Olegi
// EIP39708: Added new incompatibility type for HIDs that ignore boot
// protocol.
// 
// 20    5/11/10 1:52p Olegi
// Corrected the mouse data report. EIP37798
// 
// 19    11/24/09 11:39a Olegi
// EIP#29733 - BIOS adds an USB API (Block KBC Access)
// 
// 18    9/10/09 3:58p Davidd
// Corrected build error caused by previous change.
// 
// 17    9/10/09 9:43a Olegi
// EIP25224: When set boot protocol for mouse, the interface number may
// not be 0. Some keyboard/mouse composite devices have one more
// interface.
// 
// 16    7/07/08 4:01p Olegi
// 
// 15    5/16/08 12:06p Olegi
// 
// 14    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 13    12/17/07 4:04p Olegi
// KBC emulation support added.
// 
// 12    3/29/07 6:40p Olegi
// 
// 11    3/20/07 12:20p Olegi
//
// 9     4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 8     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 7     2/06/06 9:35a Andriyn
//
// 6     1/24/06 12:28p Andriyn
//
// 5     8/27/05 3:44p Andriyn
// Fix: lost mouse click when mouse is not moving
//
// 4     8/26/05 12:25p Andriyn
// Simulate Mouse Sampling rate by disabling Mouse Polling (reduce USB
// SMI# generation)
//
// 3     8/25/05 7:19p Andriyn
// USB Keyboard and mouse to use EMUL 60/64 for passing data to KBC.
// Fall-back when EMUL 60/64 is not present
//
// 2     8/04/05 5:03p Andriyn
// cosmetic changes
//
// 1     3/28/05 6:20p Olegi
//
// 2     3/18/05 9:41a Olegi
// Correction in Y coordinate calculations.
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           UsbMs.c
//
//  Description:    AMI USB mouse support implementation
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "amiusb.h"
#include "usbkbd.h"

extern  USB_GLOBAL_DATA     *gUsbData;

extern  UINT8 IsKbcAccessBlocked;	//(EIP29733+)

extern  EFI_EMUL6064MSINPUT_PROTOCOL* gMsInput;

VOID        USBMSInitialize (VOID);
DEV_INFO*   USBMSConfigureDevice (HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT16);
UINT8       USBMSProcessMouseData (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID        USBKeyRepeat(HC_STRUC*, UINT8);
VOID		SetMouseData (UINT8*, USBMS_DATA*, UINT8, UINT8, HID_REPORT_FIELD*);		//(EIP127014+)		
EFI_STATUS  SendMouseData(PS2MouseData*);
UINT8       OrgButtonStatus = 0;		//(EIP91835)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBMSInitialize
//
// Description: This routine is called once to initialize the USB mouse data
//              area
//
// Input:       None
//
// Output:      Nothing
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBMSInitialize()
{
    //
    // Initialize the mouse input buffer head and tail values
    //
    gUsbData->fpMouseInputBufferHeadPtr = &gUsbData->aMouseInputBuffer[0];
    gUsbData->fpMouseInputBufferTailPtr = &gUsbData->aMouseInputBuffer[0];
    USB_DEBUG(DEBUG_LEVEL_3, "USBMSInitialize: Head and Tail are at %x\n", gUsbData->fpMouseInputBufferHeadPtr);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBMSConfigureDevice
//
// Description: This routine checks an interface descriptor of the USB device
//              detected to see if it describes a HID/Boot/Mouse device.
//              If the device matches the above criteria, then the device is
//              configured and initialized
//
// Input:       HcStruc   HCStruc pointer
//              DevInfo   Device information structure pointer
//              Desc      Pointer to the descriptor structure
//              Start      Offset within interface descriptor
//                      supported by the device
//              End        End offset of the device descriptor
//
// Output:      FPDEV_INFO  New device info structure, 0 on error
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

DEV_INFO*
USBMSConfigureDevice (
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Desc,
    UINT16      Start,
    UINT16      End)
{
    return NULL;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBMSProcessMouseData
//
// Description: This function is called at regular intervals with USB mouse
//              report data. This function handles the translation of USB
//              mouse data into PS/2 mouse data, and makes the PS/2 data
//              available to software using ports 60/64 to communicate with
//              a PS/2 mouse.
//
// Input:       HcStruc   Pointer to HCStruc
//              DevInfo   Pointer to device information structure
//              Td        Pointer to the polling TD
//              Buffer    Pointer to the data buffer
//
// Output:      Nothing
//
// Notes:       The format of 3 byte data packet is as follow:
//               Byte              Description
//          -----------------------------------------------------------
//              0   Bit     Description
//              -------------------------------------------
//                   0      If set, button 1 is pressed
//                   1      If set, button 2 is pressed
//                   2      If set, button 3 is pressed
//                   3-7        Reserved
//              -------------------------------------------
//              1   X displacement value
//              2   Y displacement value
//          -----------------------------------------------------------
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBMSProcessMouseData (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Td,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UINT8*              MachineConfigPtr = (UINT8*)(UINTN)0x410;
    PS2MouseData        MouseData;
    USBMS_DATA          TempData;
    INT32               Coordinates;
	HID_REPORT_FIELD 	*Field = NULL;
	UINT8 	            OffsetTmp = 0;
    UINT8               XStart;
    UINT8               XEnd;
    UINT8               YStart;
    UINT8               YEnd;
    UINT8               ButtonStart;
    UINT8               WheelStart;
    UINT8               i;
    UINT16              j;
    UINT8               ButtonSet = 0;
    UINT8               XSet = 0;
    UINT8               YSet = 0;
    UINT8               WheelSet = 0;

    //Is KBC access allowed?
    if (IsKbcAccessBlocked) {
        return USB_SUCCESS; //(EIP29733+)
    }
    
    MemSet(&TempData, sizeof(USBMS_DATA), 0);	//(EIP127014)

    if (DevInfo->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
        //serach button and X Y
        for (i = 0; i < DevInfo->HidReport.FieldCount; i++) {
			Field = DevInfo->HidReport.Fields[i];

            //Check if it is input?
            if (!(Field->Flag & HID_REPORT_FIELD_FLAG_INPUT)) {
				continue;
            }
            //if report id is exist, check first byte
            if (Field->ReportId != 0 && Field->ReportId != Buffer[0]) {
				continue;
            }

            // Check if the field is contant.
            if (Field->Flag & HID_REPORT_FIELD_FLAG_CONSTANT) {
                OffsetTmp += Field->ReportCount * Field->ReportSize;
                continue;
            }
            
            //Check Button
            if ((Field->UsagePage == 9) && (Field->UsageCount != 0) && (Field->Usages[0] == 1)) {
                ButtonSet = 1;
                ButtonStart = OffsetTmp;
                if (Field->ReportId != 0) {
                    ButtonStart += 8;
                }
                ButtonStart /= 8;
                TempData.ButtonByte = *(Buffer + ButtonStart);
            }
            //Check X,Y
			if ((Field->UsagePage == 1) && (Field->UsageCount != 0)) {
                for (j = 0; j < Field->UsageCount; j++) {
					//find X
                    if (Field->Usages[j] == 0x30) {
                        XSet = 1;         
                        XStart = (OffsetTmp + j * Field->ReportSize); 
                        if (Field->ReportId != 0) {
                            XStart += 8;
                        }
                        XEnd = XStart + Field->ReportSize;
                        TempData.FillUsage = 0x30;	//(EIP127014)
                        SetMouseData(Buffer, &TempData, XStart, XEnd, Field);
					}
                    //find Y
					if (Field->Usages[j] == 0x31) {
                        YSet = 1;         
						YStart = (OffsetTmp + j * Field->ReportSize);
                        if (Field->ReportId != 0) {
                            YStart += 8;
                        }
						YEnd = YStart + Field->ReportSize;
                        TempData.FillUsage = 0x31;
						SetMouseData(Buffer, &TempData, YStart, YEnd, Field);
					}
					//find Wheel
                    if (Field->Usages[j] == 0x38) {
                        WheelSet = 1;
                        WheelStart = (OffsetTmp + j * Field->ReportSize) / 8;
                        if (Field->ReportId != 0) {
                            WheelStart += 1;
                        }
                        TempData.Z = *(Buffer + WheelStart);
					}
				}
			}
            OffsetTmp += Field->ReportCount * Field->ReportSize;
		}
                                        
        for (i = 0; i < 8; i++) {
        	Buffer[i] = 0;
        }

		//fill MS DATA
        if (ButtonSet != 0) {
    		*Buffer = TempData.ButtonByte;
            OrgButtonStatus = TempData.ButtonByte;
        } else {
            *Buffer = OrgButtonStatus;
        }
        
        if (XSet == 1) {
    	    *(Buffer + 1) = TempData.X;
        }
        if (YSet == 1) {
		    *(Buffer + 2) = TempData.Y;
        }
        if (WheelSet == 1) { 
		    *(Buffer + 3) = TempData.Z;
        }
	} else {
        TempData.EfiX = *((INT8*)Buffer + 1);
        TempData.EfiY = *((INT8*)Buffer + 2);
    }

    if (DevInfo->wIncompatFlags & USB_INCMPT_BOOT_PROTOCOL_IGNORED) {
        Buffer++;
    }
    
	if ((BOOT_PROTOCOL_SUPPORT == 0) && 
        !(DevInfo->wIncompatFlags & USB_INCMPT_HID_BOOT_PROTOCOL_ONLY)) {
        if (!(ButtonSet || XSet || YSet || WheelSet)) {
            return USB_SUCCESS;
        }
    }
    
 
    if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {

        gUsbData->MouseData.ButtonStatus = *(UINT8*)Buffer;

        Coordinates = (INT16)TempData.EfiX;		//(EIP127014)
        gUsbData->MouseData.MouseX += Coordinates;

        Coordinates = (INT16)TempData.EfiY;		//(EIP127014)
        gUsbData->MouseData.MouseY += Coordinates;

        Coordinates= *((INT8*)Buffer + 3);
        gUsbData->MouseData.MouseZ += Coordinates;

        return USB_SUCCESS; // Here should be code that prepares buffer for AMIUHCD
    }

    if (!(*MachineConfigPtr & BIT2)) {
        return USB_SUCCESS;    // No mouse indication in BIOS Data area equipment byte
    }
/*
										//(EIP57745+)>
    //
    // Check the version of CSM16, support is available for ver 7.64 or later
    //
    {
        UINT8	MjCsmVer = *(UINT8*)0xF0018;
        UINT8	MnCsmVer = *(UINT8*)0xF0019;
		UINT8	mouse_flag3 = *((UINT8*)((UINTN)((*(UINT16*)0x40E) << 4) + 0x30));

        if (MjCsmVer > 7 || MnCsmVer > 0x63) {
			if(!(mouse_flag3 & BIT0)) {
				return USB_SUCCESS;
			}
        }
    } 
										//<(EIP57745+)
*/
    //
    // Check mouse data availability
    //
    if (gMsInput != 0) {
        //
        // Get mouse status byte and prepare it.
        // Bit 2, 1, 0 = Middle, right and left button status
        // Bit 3 is always 1
        //
        MouseData.flags = (*(UINT8*)Buffer) & 7 | 8;

        //
        // Get mouse X, Y position
        //
        MouseData.x = (*((UINT8*)Buffer + 1));
        MouseData.y = (UINT8)(-*((INT8*)Buffer + 2)); // Y data is opposite in USB than PS2

        //
        // Verify the direction of X-axis movement
        //
        if (MouseData.x >= 0x80) {
            MouseData.flags |= 0x10;    // Negative X-axis movement
        }
        if (MouseData.y >= 0x80) {
            MouseData.flags |= 0x20;    // Negative Y-axis movement
        }

        if (gUsbData->kbc_support || (gUsbData->dUSBStateFlag & USB_FLAG_6064EMULATION_ON)) {
            SendMouseData(&MouseData);
            USBKeyRepeat(NULL, 2);          // Enable Key repeat	//(EIP49214+)
        }				    
    }

    return USB_SUCCESS;
}
										//(EIP127014+)>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetMouseData
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

VOID
SetMouseData (
    UINT8           	*Buffer,
    USBMS_DATA 	    	*MsData,
    UINT8 		    	Start,
    UINT8 		    	End,
    HID_REPORT_FIELD	*Field
)
{
	UINT8 	ReportSize;
    UINT8   Size;
    UINT8   PreSkip;
    UINT8   PostSkip;
	UINT16  TempData = 0;
    UINT16  MinMask = 0;
    UINT16  Multi = 1;
    UINT16  Resolution;
    UINT16  Count = 0;
    UINT16  i;

    if ((Field->PhysicalMax == 0) && (Field->PhysicalMin == 0)) {
        Field->PhysicalMax = Field->LogicalMax;
        Field->PhysicalMin = Field->LogicalMin;
    }
    if (Field->UnitExponent != 0) {
        Count = (~Field->UnitExponent) + 1;
    }
    
    for (i = 0; i < Count; i++){
        Multi = Multi * 10;
    }        
    
    Resolution = ((INT16)Field->LogicalMax - (INT16)Field->LogicalMin) * Multi /
                 ((INT16)Field->PhysicalMax - (INT16)Field->PhysicalMin);

	ReportSize = End - Start;
    MinMask = ((~MinMask) >> ReportSize) << ReportSize;

	Size = ReportSize / 8;
    
    if ((ReportSize % 8) != 0) {
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

    if (TempData > Field->LogicalMax) {
        TempData |= MinMask;
    }

    if (MsData->FillUsage == 0x30) {
        MsData->EfiX = TempData;
        MsData->X = (UINT8)TempData; 
    }
    if (MsData->FillUsage == 0x31) {
        MsData->EfiY = TempData;
        MsData->Y = (UINT8)TempData; 
    } 

	return;
} 
										//<(EIP127014+)
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
