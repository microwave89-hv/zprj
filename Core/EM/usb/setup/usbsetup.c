//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Setup/usbsetup.c 24    12/24/14 10:40p Wilsonlee $
//
// $Revision: 24 $
//
// $Date: 12/24/14 10:40p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/Setup/usbsetup.c $
// 
// 24    12/24/14 10:40p Wilsonlee
// [TAG]  		EIP196287
// [Category]  	Improvement
// [Description]  	Display info of connected usb controllers and remove or
// grayed-out some item according the connected usb controller number.
// [Files]  		uhcd.c, usbport.c, usb.uni, usb.sd, usbsetup.c,
// AmiUsbController.h, UsbPolicy.h
// 
// 23    8/20/14 5:26a Wilsonlee
// [TAG]  		EIP182011
// [Category]  	Improvement
// [Description]  	We don't need to update NVRAM variables in
// InstallUsbMass and UninstallUSBMass functions.
// [Files]  		efiusbmass.c, usbsetup.c
// 
// 22    6/26/14 1:18a Wilsonlee
// [TAG]  		EIP173387
// [Category]  	Improvement
// [Description]  	Remove TODO comments.
// [Files]  		usbsetup.c, xhci.c, usbmass.c, usbCCID.c, usb.c, uhci.c,
// syskbc.c, usbport.c, usbbus.c, uhcd.c, UsbBotPeim.c, PeiXhci.c,
// PeiEhci.c
// 
// 21    5/07/14 10:37a Wilsonlee
// [TAG]  		EIP166594
// [Category]  	Improvement
// [Description]  	Add the token "USB_SETUP_VARIABLE_RUNTIME_ACCESS" to
// control if we set runtime attribute for the setup variables used by USB
// module.
// [Files]  		usb.sdl, usbport.c, usbsetup.c
// 
// 20    4/29/14 10:23p Wilsonlee
// [TAG]  		EIP161709
// [Category]  	New Feature
// [Description]  	Dynamically update the usb device list in BIOS setup.
// [Files]  		usb.sdl, usb.sd, usbsetup.c, uhcd.c
// 
// 19    2/08/13 3:33a Roberthsu
// [TAG]           EIP112379 
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       USB device information is incorrect in Setup.
// [RootCause]     Memory copy size error.
// [Solution]      Change copy point device string size.
// [Files]         usbsetup.c
// 
// 18    10/25/12 1:37a Wilsonlee
// [TAG]  		EIP102493
// [Category]  	New Feature
// [Description]  	USB Module version is added to the setup page.
// [Files]  		usbsetup.c, usb.sd, usb.uni
// 
// 17    7/15/11 6:32a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, efiusbpoint.c, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c,
// usb.c, usbdef.h, usbhid.c, usbkbd.c, usbkbd.h, usbms.c, usbpoint.c,
// usbrt.cif, usbsb.c, usbsetup.c, usbsrc.sdl, xhci.c
// 
// 16    7/12/11 8:19a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
// 15    10/14/10 4:42p Olegi
// - Tabs replaced with spaces
// - Changed the existing logic of getting strings correlated to device
// number: from hardcoded table that was limted to 10 elements only (snum
// array). If more than 10 devices used, the whole logic caused memory
// corruption that ended with CPU exception.
// - Changed the logic of conversion decimal number to CHAR16 string +
// space as required.
// - Added limitations for input numbers to be smaller than 127 which is
// USB max device address; this limitation should never be approached but
// it protects string operations on numbers.
//
// 14    10/12/10 2:34a Rameshr
// [TAG]- EIP 44585
// [Category]-IMPROVEMENT
// [Description]- Number of maximum supported USB Mass Storage device
// increased from 8 to 16.
// [Files]- Uin13.bin, UsbPort.c, UsbInt13.h, Usb.c, Usbdef.h, Uasbmass.c,
// Usb.sd, usb.uni, UsbSetup.c, UsbSrc.sdl, UsbPolicy.h
//
// 13    4/12/10 12:19p Olegi
// Moving structure definitions to the .H file. EIP36942
//
// 12    1/29/10 5:15p Olegi
//
// 11    11/10/09 8:54a Olegi
// EIP30149: HII 2.1 compliance.
//
// 10    9/09/09 3:18p Davidd
// Removed the assertion caused by USB support disabled in setup - EIP
// 25360
//
// 9     12/18/08 10:47a Olegi
// Variable gEfiSetupGuid made static.
//
// 8     7/04/08 1:04p Olegi
//
// 7     6/27/08 6:00p Olegi
//
// 6     5/16/08 12:07p Olegi
// Compliance with AMI coding standard.
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           UsbSetup.c
//
//  Description:    USB driver setup related functions implementation.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include "Protocol/AMiUsbController.h"
#include <Protocol/UsbPolicy.h>

#define MAX_DEVS_LINE_LENGTH 80
#define MAX_DEVICE_NUMBER_LENGTH 10
#define MAX_DEVICE_AMOUNT 127

static EFI_GUID gEfiSetupGuid = SETUP_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetConnectedDevices
//
// Description: This function retrieves the information about connected
//              USB devices.
//
// Output:      returns TRUE if device connection status has changed since this
//              function is called last time; otherwise FALSE.
// Notes:       When FALSE is returned, none of the output parameters are valid.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetConnectedDevices(
    CHAR16                          *DevNumStr,
    CHAR16                          *ControllerNumStr,
    EFI_USB_PROTOCOL                *UsbProtocol,
    CONNECTED_USB_DEVICES_NUM       *Devs
)
{
    CHAR16 	StrMassStorage[] = L"Drive";
    CHAR16 	StrKeyboard[] = L"Keyboard";
    CHAR16 	StrMouse[] = L"Mouse";
    CHAR16 	StrPoint[] = L"Point"; 		//(EIP38434+)
    CHAR16 	StrMice[] = L"Mice";
    CHAR16 	StrHub[] = L"Hub";
	CHAR16 	StrCcid[] = L"SmartCard Reader";
    CHAR16 	StrUhci[] = L"UHCI";
    CHAR16 	StrOhci[] = L"OHCI";
    CHAR16 	StrEhci[] = L"EHCI";
    CHAR16 	StrXhci[] = L"XHCI";
    CHAR16 	Name[MAX_DEVS_LINE_LENGTH];
    CHAR16 	*StrPtr = Name;
    CHAR16 	NumberToString [MAX_DEVICE_NUMBER_LENGTH];
    UINTN 	NumSize;
    CHAR16 	Comma[] = L", ";
    CHAR16 	Space[] = L" ";
    CHAR16 	LeadingSpace[] = L"      None";
	UINT8	MassStorageNumber;
	UINT8 	KeyboardNumber; 
	UINT8	MouseNumber;
	UINT8	PointNumber; 
	UINT8	HubNumber; 
	UINT8	CcidNumber;	//(EIP38434)
	UINT8   UhciNumber;
    UINT8   OhciNumber;
    UINT8   EhciNumber;
    UINT8   XhciNumber;
    BOOLEAN	Is1stItem = TRUE;

    UsbProtocol->UsbReportDevices(Devs);
    MassStorageNumber = Devs->NumUsbMass;
    KeyboardNumber = Devs->NumUsbKbds;
    MouseNumber	 = Devs->NumUsbMice;
    PointNumber = Devs->NumUsbPoint;
    HubNumber = Devs->NumUsbHubs;
	CcidNumber = Devs->NumUsbCcids;
    UhciNumber = Devs->NumUhcis;
    OhciNumber = Devs->NumOhcis;
    EhciNumber = Devs->NumEhcis;
    XhciNumber = Devs->NumXhcis;

    // Form the string
    pBS->SetMem(StrPtr, MAX_DEVS_LINE_LENGTH * sizeof(CHAR16), 0);
    pBS->CopyMem(StrPtr, LeadingSpace, 10 * sizeof(CHAR16)); 
    StrPtr += 6;  // leave string pointer at "None"

    // Drive/Drives
    if ((MassStorageNumber) && (MassStorageNumber < MAX_DEVICE_AMOUNT)) {
        ItowEx(MassStorageNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        pBS->CopyMem(StrPtr, StrMassStorage, 10); 
        StrPtr += 5;		        // L"Drive"
        if (MassStorageNumber > 1) {
          *StrPtr++ = L's';   // L"Drives"
        }
        Is1stItem = FALSE;
    }

    // Keyboard/Keyboards
    if ((KeyboardNumber) && (KeyboardNumber < MAX_DEVICE_AMOUNT)) {
        if (!Is1stItem) {
            pBS->CopyMem(StrPtr, Comma, 4); 
            StrPtr += 2;    // L" ,"
        }
        ItowEx(KeyboardNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        // move pointer 1 more space then string length
        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        pBS->CopyMem(StrPtr, StrKeyboard, 16); 
        StrPtr += 8;    // L"Keyboard"
        if (KeyboardNumber > 1) {
          *StrPtr++ = L's'; // L"Keyboards"
        }
        Is1stItem = FALSE;
    }

    // Mouse/Mice
    if ((MouseNumber) && (MouseNumber < MAX_DEVICE_AMOUNT)) {
        if (!Is1stItem) {
            pBS->CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;    // L" ,"
        }
        ItowEx(MouseNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        // move pointer 1 more space then string length
        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        if (MouseNumber == 1) {
            pBS->CopyMem(StrPtr, StrMouse, 10);
            StrPtr += 5;        // L"Mouse"
        } else {
            pBS->CopyMem(StrPtr, StrMice, 8);
            StrPtr += 4;        // L"Mice"
        }
        Is1stItem = FALSE;
    }
										//(EIP38434+)>
    // Point/Points
    if ((PointNumber) && (PointNumber < MAX_DEVICE_AMOUNT)) {
        if (!Is1stItem) {
            pBS->CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;    // L" ,"
        }
        ItowEx(PointNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);
        // move pointer 1 more space then string length
        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        pBS->CopyMem(StrPtr, StrPoint, 10);
        StrPtr += 5;            // L"Point"
        if (PointNumber > 1) {
          *StrPtr++ = L's';     // L"Points"
        }
        Is1stItem = FALSE;
    } 
										//<(EIP38434+)
    // Hub/Hubs
    if ((HubNumber) && (HubNumber < MAX_DEVICE_AMOUNT)) {
        if (!Is1stItem) {
            pBS->CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;    // L" ,"
        }
        ItowEx(HubNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        // move pointer 1 more space then string length
        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;
        pBS->CopyMem(StrPtr, StrHub, 6);
        StrPtr += 3;            // L"Hub"
        if (HubNumber > 1) {
            *StrPtr++ = L's';   // L"Hubs"
        }
        Is1stItem = FALSE;
    }
	// Ccid/Ccids
	if (CcidNumber) {
		if (!Is1stItem) {
			pBS->CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;	// L" ,"
		}
        ItowEx(CcidNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        // move pointer 1 more space then string length
        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;

        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;	//	L" "

		pBS->CopyMem(StrPtr, StrCcid, 32); 
        StrPtr += 16;           // L"SmartCard Reader"
		if (CcidNumber > 1) {
			*StrPtr++ = L's';   // L'SmartCard Readers'
		}
		Is1stItem = FALSE;
	}

    pBS->CopyMem(DevNumStr, Name, MAX_DEVS_LINE_LENGTH * sizeof(CHAR16));

    Is1stItem = TRUE;
    StrPtr = Name;
    // Form the string
    pBS->SetMem(StrPtr, MAX_DEVS_LINE_LENGTH * sizeof(CHAR16), 0);
    pBS->CopyMem(StrPtr, LeadingSpace, 10 * sizeof(CHAR16)); 
    StrPtr += 6;  // leave string pointer at "None"

    // Drive/Drives
    if (UhciNumber) {
        ItowEx(UhciNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;
        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;

        pBS->CopyMem(StrPtr, StrUhci, 8); 
        StrPtr += 4;		  // L"UHCI"
        if (UhciNumber > 1) {
          *StrPtr++ = L's';   // L"UHCIs"
        }
        Is1stItem = FALSE;
    }

	if (OhciNumber) {
		if (!Is1stItem) {
			pBS->CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;	// L" ,"
		}
        ItowEx(OhciNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        // move pointer 1 more space then string length
        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;

        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;	//	L" "

		pBS->CopyMem(StrPtr, StrOhci, 8); 
        StrPtr += 4;            // L"OHCI"
		if (OhciNumber > 1) {
			*StrPtr++ = L's';   // L'OHCIs'
		}
		Is1stItem = FALSE;
	}

	if (EhciNumber) {
		if (!Is1stItem) {
			pBS->CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;	// L" ,"
		}
        ItowEx(EhciNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        // move pointer 1 more space then string length
        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;

        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;	//	L" "

		pBS->CopyMem(StrPtr, StrEhci, 8); 
        StrPtr += 4;            // L"EHCI"
		if (EhciNumber > 1) {
			*StrPtr++ = L's';   // L'EHCIs'
		}
		Is1stItem = FALSE;
	}

	if (XhciNumber) {
		if (!Is1stItem) {
			pBS->CopyMem(StrPtr, Comma, 4);
            StrPtr += 2;	// L" ,"
		}
        ItowEx(XhciNumber, NumberToString, 10, FALSE);
        NumSize = Wcslen(NumberToString);

        // move pointer 1 more space then string length
        pBS->CopyMem(StrPtr, NumberToString, (NumSize * sizeof (CHAR16)));
        StrPtr += NumSize;

        // move pointer 1 more space
        pBS->CopyMem(StrPtr, Space, 2);
        StrPtr += 1;	//	L" "

		pBS->CopyMem(StrPtr, StrXhci, 8); 
        StrPtr += 4;            // L"XHCI"
		if (XhciNumber > 1) {
			*StrPtr++ = L's';   // L'XHCIs'
		}
		Is1stItem = FALSE;
	}

    pBS->CopyMem(ControllerNumStr, Name, MAX_DEVS_LINE_LENGTH * sizeof(CHAR16));

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetMassDeviceName
//
// Description: This function retrieves the USB mass storage device ASCII name.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
GetMassDeviceName(
    UINT8               *DevName,
    UINT8               DevAddr,
    EFI_USB_PROTOCOL *UsbProtocol
)
{
    CHAR8   Data[48];
    UINT8   NextDev;

    // Get the name using USBMassAPIGetDeviceInformation
    NextDev = UsbProtocol->UsbGetNextMassDeviceName(Data, sizeof(Data), DevAddr);
    if (NextDev != 0xFF) {
        Sprintf((char*)DevName, "%a", Data);
    }
    return NextDev;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitUSBStrings
//
// Description: This function is eLink'ed with the chain executed right before
//              the Setup.
//
//----------------------------------------------------------------------------

VOID
InitUSBStrings(
    EFI_HII_HANDLE HiiHandle,
    UINT16          Class
)
{
    CHAR16  DevNumStr[MAX_DEVS_LINE_LENGTH];
    CHAR16  ControllerNumStr[MAX_DEVS_LINE_LENGTH];
    CHAR8   MassStr[MAX_DEVS_LINE_LENGTH];
    UINT8   NextDev;
    UINT16  MassDev[16] = {
        STRING_TOKEN(STR_USB_MASS_DEVICE1),
        STRING_TOKEN(STR_USB_MASS_DEVICE2),
        STRING_TOKEN(STR_USB_MASS_DEVICE3),
        STRING_TOKEN(STR_USB_MASS_DEVICE4),
        STRING_TOKEN(STR_USB_MASS_DEVICE5),
        STRING_TOKEN(STR_USB_MASS_DEVICE6),
        STRING_TOKEN(STR_USB_MASS_DEVICE7),
        STRING_TOKEN(STR_USB_MASS_DEVICE8),
        STRING_TOKEN(STR_USB_MASS_DEVICE9),
        STRING_TOKEN(STR_USB_MASS_DEVICE10),
        STRING_TOKEN(STR_USB_MASS_DEVICE11),
        STRING_TOKEN(STR_USB_MASS_DEVICE12),
        STRING_TOKEN(STR_USB_MASS_DEVICE13),
        STRING_TOKEN(STR_USB_MASS_DEVICE14),
        STRING_TOKEN(STR_USB_MASS_DEVICE15),
        STRING_TOKEN(STR_USB_MASS_DEVICE16)

    };
    UINT8               MassDevValid[16];
    UINT8               i;
    UINTN               VariableSize;
    USB_MASS_DEV_NUM    SetupData;
    EFI_STATUS          Status;
    EFI_USB_PROTOCOL    *UsbProtocol;
    EFI_GUID            UsbProtocolGuid = EFI_USB_PROTOCOL_GUID;
	CONNECTED_USB_DEVICES_NUM       DevNum;
    UINT32              VariableAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    USB_CONTROLLER_NUM  UsbControllerNum;

#if USB_SETUP_VARIABLE_RUNTIME_ACCESS
    VariableAttributes |= EFI_VARIABLE_RUNTIME_ACCESS;
#endif


    if (Class!=ADVANCED_FORM_SET_CLASS) {
        return;
    }
                                        //(EIP102493+)>
    InitString(HiiHandle, STRING_TOKEN(STR_USB_MODULE_VER), L"%d.%02d.%02d", 
       USB_DRIVER_MAJOR_VER, USB_DRIVER_MINOR_VER, USB_DRIVER_BUILD_VER);
                                        //<(EIP102493+)

    Status = pBS->LocateProtocol(&UsbProtocolGuid, NULL, &UsbProtocol);
//####  ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return;
    }

    // Number of connected devices
    GetConnectedDevices(DevNumStr, ControllerNumStr, UsbProtocol, &DevNum);
    
    TRACE((-1, "Devices total: %d KBDs, %d HUBs, %d MICE, %d POINT %d MASS %d CCID\n",
        DevNum.NumUsbKbds, DevNum.NumUsbHubs, DevNum.NumUsbMice,
        DevNum.NumUsbPoint, DevNum.NumUsbMass, DevNum.NumUsbCcids));
    
    InitString(HiiHandle, STRING_TOKEN(STR_USB_DEVICES_ENABLED_LIST), L"%s", DevNumStr);
    InitString(HiiHandle, STRING_TOKEN(STR_USB_CONTROLLERS_ENABLED_LIST), L"%s", ControllerNumStr);

    // Mass storage device names
    for (i = 0, NextDev = 0; i < 16; i++) {
        NextDev = GetMassDeviceName(MassStr, NextDev, UsbProtocol);
        if (NextDev == 0xFF) {
            break;    // No more devices
        }
        InitString(HiiHandle, MassDev[i], L"%S", MassStr);
        if (NextDev & 0x80) {
            break;     // Last device
        }
    }

    for (i = 0; i < 16; i++) {
        if (i < DevNum.NumUsbMass) {
            MassDevValid[i] = 1;
        } else {
            MassDevValid[i] = 0;
        }
    }

    VariableSize = sizeof(USB_MASS_DEV_VALID);

    Status = pRS->SetVariable(L"UsbMassDevValid",
        &gEfiSetupGuid,
        VariableAttributes,
        VariableSize,
        &MassDevValid);

    VariableSize = sizeof(SetupData);
    Status = pRS->GetVariable(L"UsbMassDevNum",
        &gEfiSetupGuid,
        NULL,
        &VariableSize,
        &SetupData);

    if (EFI_ERROR(Status)) {
        return;
    }

    SetupData.IsInteractionAllowed = 0;
    SetupData.UsbMassDevNum = DevNum.NumUsbMass;

    Status = pRS->SetVariable(L"UsbMassDevNum",
        &gEfiSetupGuid,
        VariableAttributes,
        VariableSize,
        &SetupData);

    VariableSize = sizeof(UsbControllerNum);
    Status = pRS->GetVariable(L"UsbControllerNum",
        &gEfiSetupGuid,
        NULL,
        &VariableSize,
        &UsbControllerNum);

    if (EFI_ERROR(Status)) {
        return;
    }

    UsbControllerNum.UhciNum = DevNum.NumUhcis;
    UsbControllerNum.OhciNum = DevNum.NumOhcis;
    UsbControllerNum.EhciNum = DevNum.NumEhcis;
    UsbControllerNum.XhciNum = DevNum.NumXhcis;

    Status = pRS->SetVariable(L"UsbControllerNum",
        &gEfiSetupGuid,
        VariableAttributes,
        VariableSize,
        &UsbControllerNum);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateUSBStrings
//
// Description: This function is updating usb setup page dynamically.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UpdateUSBStrings(
    EFI_HII_HANDLE HiiHandle,
    UINT16          Class,
    UINT16          SubClass,
    UINT16          Key
)
{
    UINT8       MassDevValid[16];
    UINT8       i;
    UINT8       NextDev;
    UINTN       VariableSize;
    EFI_GUID    UsbProtocolGuid = EFI_USB_PROTOCOL_GUID;
    EFI_STATUS  Status;
    EFI_USB_PROTOCOL                *UsbProtocol;
    CONNECTED_USB_DEVICES_NUM       DevNum;
    USB_MASS_DEV_NUM                MassDevNumData;
    USB_CONTROLLER_NUM              UsbControllerNum;
    CHAR16      DevNumStr[MAX_DEVS_LINE_LENGTH];
    CHAR16      ControllerNumStr[MAX_DEVS_LINE_LENGTH];
    CHAR8       MassStr[MAX_DEVS_LINE_LENGTH];
    UINT16      MassDev[16] = {
                    STRING_TOKEN(STR_USB_MASS_DEVICE1),
                    STRING_TOKEN(STR_USB_MASS_DEVICE2),
                    STRING_TOKEN(STR_USB_MASS_DEVICE3),
                    STRING_TOKEN(STR_USB_MASS_DEVICE4),
                    STRING_TOKEN(STR_USB_MASS_DEVICE5),
                    STRING_TOKEN(STR_USB_MASS_DEVICE6),
                    STRING_TOKEN(STR_USB_MASS_DEVICE7),
                    STRING_TOKEN(STR_USB_MASS_DEVICE8),
                    STRING_TOKEN(STR_USB_MASS_DEVICE9),
                    STRING_TOKEN(STR_USB_MASS_DEVICE10),
                    STRING_TOKEN(STR_USB_MASS_DEVICE11),
                    STRING_TOKEN(STR_USB_MASS_DEVICE12),
                    STRING_TOKEN(STR_USB_MASS_DEVICE13),
                    STRING_TOKEN(STR_USB_MASS_DEVICE14),
                    STRING_TOKEN(STR_USB_MASS_DEVICE15),
                    STRING_TOKEN(STR_USB_MASS_DEVICE16)
                };
    
    if (Key == USB_DEVICES_ENABLED_REFRESH_KEY) {
        
        Status = pBS->LocateProtocol(&UsbProtocolGuid, NULL, &UsbProtocol);

        if (EFI_ERROR(Status)) {
            return;
        }

        // Number of connected devices
        GetConnectedDevices(DevNumStr, ControllerNumStr, UsbProtocol, &DevNum);

        InitString(HiiHandle, STRING_TOKEN(STR_USB_DEVICES_ENABLED_LIST), L"%s", DevNumStr);

        // Mass storage device names
        for (i = 0, NextDev = 0; i < 16; i++) {
            NextDev = GetMassDeviceName(MassStr, NextDev, UsbProtocol);
            if (NextDev == 0xFF) {
                break;    // No more devices
            }
            InitString(HiiHandle, MassDev[i], L"%S", MassStr);
            if (NextDev & 0x80) {
                break;     // Last device
            }
        }

        VariableSize = sizeof(MassDevValid);
    	   
    	Status = HiiLibGetBrowserData(
                    &VariableSize, &MassDevValid,
                    &gEfiSetupGuid, L"UsbMassDevValid");
        
        if (EFI_ERROR(Status)) {
            return;
        }
        	   	   	    
        for (i = 0; i < 16; i++) {
            if (i < DevNum.NumUsbMass) {
                MassDevValid[i] = 1;
            } else {
                MassDevValid[i] = 0;
            }
        }

    	Status = HiiLibSetBrowserData(
                    VariableSize, &MassDevValid,
                    &gEfiSetupGuid, L"UsbMassDevValid");
             
        if (EFI_ERROR(Status)) {
            return;
        }

        VariableSize = sizeof(MassDevNumData);

    	Status = HiiLibGetBrowserData(
                    &VariableSize, &MassDevNumData,
                    &gEfiSetupGuid, L"UsbMassDevNum");
        
        if (EFI_ERROR(Status)) {
            return;
        }

        MassDevNumData.UsbMassDevNum = DevNum.NumUsbMass;

    	Status = HiiLibSetBrowserData(
                    VariableSize, &MassDevNumData,
                    &gEfiSetupGuid, L"UsbMassDevNum");
        
        VariableSize = sizeof(UsbControllerNum);

    	Status = HiiLibGetBrowserData(
                    &VariableSize, &UsbControllerNum,
                    &gEfiSetupGuid, L"UsbControllerNum");
        
        if (EFI_ERROR(Status)) {
            return;
        }

        UsbControllerNum.UhciNum = DevNum.NumUhcis;
        UsbControllerNum.OhciNum = DevNum.NumOhcis;
        UsbControllerNum.EhciNum = DevNum.NumEhcis;
        UsbControllerNum.XhciNum = DevNum.NumXhcis;

    	Status = HiiLibSetBrowserData(
                    VariableSize, &UsbControllerNum,
                    &gEfiSetupGuid, L"UsbControllerNum");
        
    }	
    
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
