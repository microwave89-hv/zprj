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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbkbd.c 70    10/16/16 10:11p Wilsonlee $
//
// $Revision: 70 $
//
// $Date: 10/16/16 10:11p $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbkbd.c $
// 
// 70    10/16/16 10:11p Wilsonlee
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
// 69    7/21/16 11:00p Wilsonlee
// Build error if USB_HID_KEYREPEAT_USE_SETIDLE is 1.
// 
// 68    3/02/16 9:41p Wilsonlee
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
// 67    12/24/14 9:33p Wilsonlee
// [TAG]  		EIP194683
// [Category]  	Improvement
// [Description]  	Add the flag "USB_INCMPT_HID_BOOT_PROTOCOL_ONLY" of usb
// bad device table to keep devices use boot protocol.
// [Files]  		usbkbd.c, usbms.c, usbhid.c, usbdef.h
// 
// 66    11/23/14 9:24p Wilsonlee
// [TAG]  		EIP190127
// [Category]  	Improvement
// [Description]  	Remove scan code algorithm update.
// [Files]  		usbkbd.c
// 
// 65    11/23/14 9:10p Wilsonlee
// [TAG]  		EIP188119
// [Category]  	Improvement
// [Description]  	Disconnect devices and uninstall usb device related
// protocols if we call stop api for the host controllers.
// [Files]  		usbkbd.c, usbbus.c, uhcd.h, uhcd.c
// 
// 64    8/07/14 2:20a Wilsonlee
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
// 63    7/04/14 7:31a Wilsonlee
// [TAG]  		EIP176044
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	NEC USB keyboard doesn't work
// [RootCause]  	When we extract input report data, the report offset is
// incorrect if ReportId isn't 0.
// [Solution]  	Adjust report offset.
// [Files]  		usbkbd.c
// 
// 62    5/15/14 5:41a Wilsonlee
// Fix the code check error result.
// 
// 61    5/06/14 5:15a Ryanchou
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
// 60    2/26/14 1:55a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 59    11/05/13 4:47a Ryanchou
// [TAG]  		EIP135636
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	NumLock LED cannot be on/off properly.
// [RootCause]  	It is the side effect of EIP #107429 changes, the
// keyboard does not generate break code when pressing NumLock.
// [Solution]  	Remove the EIP #107429 changes.
// [Files]  		amiusb.c, usbkbd.c, efiusbkb.c
// 
// 58    3/07/13 8:53a Ryanchou
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
// 57    1/23/13 4:35a Wilsonlee
// [TAG]  		EIP109538
// [Category]  	Improvement
// [Description]  	Fix the code check error result.
// [Files]  		usbkbd.c, usbCCID.c, usbbus.c, efiusbccid.c
// 
// 56    1/11/13 4:15a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 55    1/07/13 12:56a Wilsonlee
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
// 54    12/19/12 3:38a Roberthsu
// [TAG]  		EIP107262
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	CHOC keyboard can not work.
// [RootCause]  	Usage offset error.
// [Solution]  	Count correct usage offset.Ceck correct usage offset.
// [Files]  		usbkbd.c
// 
// 53    12/02/12 10:34p Roberthsu
// [TAG]           EIP102150
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Push key and unplug KB , character  repeat can not.
// stop
// [RootCause]     Because repeat key does not clear when usb keyboard
// unplug.
// [Solution]      When keyboard disconnrct, clear keyboard device id with
// device id buffer and scancode buffer.
// [Files]         amiusb.c,syskbc.c,uhcd.c,usbkbd.c
// 
// 52    11/20/12 9:08p Wilsonlee
// [TAG]  		EIP90887
// [Category]  	New Feature
// [Description]  	Add a hook to check keyboard buffer for speicial chars.
// [Files]  		usb.sdl, usbrt.mak, usbkbd.c
// 
// 51    11/14/12 4:26a Roberthsu
// [TAG]           EIP105587
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Rapoo keyboard press key have some garbage key.
// [RootCause]     Get report descriptor need skip constant data.
// [Solution]      Skip constant data.
// [Files]         usbkbd.c
// 
// 50    11/10/12 6:39a Ryanchou
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
// 49    8/07/12 4:47a Roberthsu
// [TAG]           EIP93637
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Keyboard operate incorrectly in BIOS
// [RootCause]     When keyboard disconnect.Usb keyboard buffer does not
// clear.
// [Solution]      Clear usb keyboard buffer and repeat key.
// [Files]         usbkbd.c
// 
// 48    8/06/12 11:53p Roberthsu
// [TAG]           EIP95349
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Roccat ISKU Keyboard can not work
// [RootCause]     Variable value overflow.
// [Solution]      Change variable type.
// [Files]         usbkbd.c
// 
// 47    5/23/12 7:56a Roberthsu
// [TAG]           EIP90797
// [Category]      Improvement
// [Description]   Fix keyboard buffer transfer error
// [Files]         usbkbd.c
// 
// 46    5/03/12 6:27a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 45    4/24/12 3:40a Roberthsu
// [TAG]           EIP83888
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Can not catch F8 key event on Keyboard
// [RootCause]     OS only call readkeystroke once.If OS get break key
// readkeystroke will return EFI_NOT_READY.
// [Solution]      UsbKbdReadKeyStroke will serach available key in usb
// data buffer.Fixed key repeat can not work  when efi to legacy or legacy
// to efi.
// [Files]         efiusbkb.c,usbkbd.c
// 
// 44    3/05/12 1:26a Rameshr
// [TAG]  		EIP81057
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Stall after RAID BIOS
// [RootCause]  	Make code and break code handled by different environment
// ( EFI, Legacy)
// [Solution]  	If the Makecode processed by Legacy, the breakcode also
// send to Legacy. The same applies for EFI also.
// [Files]  		UsbKbd.c
// 
// 43    1/04/12 6:56a Ryanchou
// [TAG]  		EIP72505
// [Category]  	Improvement
// [Description]  	Clear the legacy USB keyboard buffer when switching
// between EFI and legacy.
// [Files]  		syskbc.c, uhcd.c, usbkbd.c
// 
// 42    12/22/11 6:36a Roberthsu
// [TAG]           EIP77936
// [Category]      Improvement
// [Description]   Chang set_idle command timeout to 1sec
// [Files]         usbkbd.c
// 
// 41    11/03/11 11:51p Roberthsu
// [TAG]  		EIP73685
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Ducky keyboard can not work.
// [RootCause]  	Ducky keyboard report key usage is by usage keyboard
// arrow.
// [Solution]  	Get start offset by keyboard usage page .
// [Files]  		usbkbd.c
// 
// 40    9/27/11 1:37a Roberthsu
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
// 39    7/15/11 6:11a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c, usb.c, usbdef.h,
// usbkbd.c, usbkbd.h, usbms.c, usbrt.cif, usbsb.c, usbsetup.c,
// usbsrc.sdl, xhci.c
// 
// 38    7/13/11 3:32a Ryanchou
// [TAG]  		EIP63973
// [Category]  	Improvement
// [Description]  	Change the order of Set Protocol command and Set Idle
// command.
// [Files]  		usbkbd.c
// 
// 37    6/21/11 11:02a Ryanchou
// [TAG]  		EIP59579
// [Category]  	Improvement
// [Description]  	USB device information structure should be reserved for
// the UsbIO to use even install driver fail.
// [Files]  		usbmass.c, usbkbd.c, usbms.c
// 
// 36    3/30/11 8:17a Ryanchou
// [TAG]  		EIP54126
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Sometimes system hangs at checkpoint 0xB4.
// [RootCause]  	The bLength field of configuration descriptor is zero.
// [Solution]  	Check wether bLength field is zero before paring next
// descriptor.
// [Files]  		usb.c, usbbus.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c
// 
// 35    2/10/11 7:40a Ryanchou
// [TAG]  		EIP52206
// [Category]  	Improvement
// [Description]  	Remote wakeup command should be sent before sleep,
// comment out  the command.
// [Files]  		usbkbd.c, usbms.c
// 
// 34    1/17/11 4:34a Ryanchou
// [TAG]  		EIP51108
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Some HID devices that has two interfaces can't work.
// [RootCause]  	BIOS using the wrong endpoint to poll KBD/MS data. 
// [Solution]  	Get the first interrupt in endpoint when parsing
// descriptors.
// [Files]  		usbkbd.c, usbms.c
// 
// 33    9/24/10 5:38p Olegi
// EIP38221: Added the code that properly initializes
// DEV_INFO.bIntEndpoint field; interrupt endpoint polling is using this
// endpoint number.
// 
// 32    3/11/10 9:41a Olegi
// 
// 31    11/24/09 11:38a Olegi
// EIP#29733 - BIOS adds an USB API (Block KBC Access)
// 
// 30    11/13/09 9:13a Olegi
// EIP31023: key repeat rates are defined by SDL tokens.
// 
// 29    9/15/09 12:21p Olegi
// Added KEY_REPEAT_LOGIC functionality. EIP#25841
// 
// 28    5/05/09 10:21a Olegi
// Modification in USBKBDConnectKeyboard. Resolves the problem of device
// being reconnected using the SW (DisconnectController->ConnectController
// sequence). EIP#21456.
// 
// 27    4/20/09 9:26a Olegi
// Completion of the fix for EIP#19563.
// 
// 26    3/27/09 10:15a Olegi
// Modifications in USBKBDProcessKeyboardData: keypress and key release
// are synchronized between the modes (EFI/Legacy). If key is pressed in
// one mode and released in the other, then keypress is discarded. This
// fixes the problem of accidental key repeat sequence due to the mode
// change. EIP #19563.
// 
// 25    9/19/08 4:44p Olegi
// Bugfix in USBKBDPeriodicInterruptHandler (EIP#16452) that takes care of
// the key release situation.
// 
// 24    9/05/08 4:19p Olegi
// Removed calls to fpCallbackNotify functions, they are implemented in
// SMI.
// 
// 23    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 21    12/17/07 4:04p Olegi
// KBC emulation support added.
// 
// 20    30/10/07 2:02p Anandakrishnanl
// Updated USBKBDPeriodicInterruptHandler to see if CallbackNotify2 is not
// NULL beforfe calling it.
// 
// 19    30/10/07 12:20p Anandakrishnanl
// Updated USBKBDPeriodicInterruptHandler to see if CallbackNotify3 is not
// NULL beforfe calling it.
// 
// 18    9/27/07 4:12p Olegi
// 
// 17    3/20/07 12:17p Olegi
// Legacy free related changes.
//
// 15    10/18/06 9:40a Andriyn
// Fix: race condition on hot-plug in / plug-off
//
// 14    5/17/06 3:52p Fredericko
// Fix: Mouse Button events get lost: no auto-repeat
//
// 13    4/26/06 12:26p Olegi
//
// 12    4/14/06 6:39p Olegi
// Conversion to be able to use x64 compiler.
//
// 11    3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 10    3/06/06 6:23p Olegi
//
// 9     3/01/06 3:50p Olegi
// ProcessKeyboardData is change to use USB_FLAG_RUNNING_UNDER_OS flag.
//
// 8     2/06/06 9:34a Andriyn
//
// 7     8/26/05 12:25p Andriyn
// Simulate Mouse Sampling rate by disabling Mouse Polling (reduce USB
// SMI# generation)
//
// 6     8/25/05 7:19p Andriyn
// USB Keyboard and mouse to use EMUL 60/64 for passing data to KBC.
// Fall-back when EMUL 60/64 is not present
//
// 5     8/11/05 9:53a Olegi
// 60/64 port emulation related fixes for EMU6064 driver.
//
// 4     8/04/05 5:58p Andriyn
// Legacy over LegacyFree
//
// 2     6/01/05 5:22p Olegi
// Debug message shortened.
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           UsbKbd.c
//
//  Description:    USB keyboard driver SMI routines
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "amiusb.h"
#include "USBKBD.H"
#include <UsbDevDriverElinks.h>         //(EIP90887+)

extern USB_GLOBAL_DATA *gUsbData;
extern BOOLEAN gKeyRepeatStatus;
extern UINT16 gKbcSetTypeRate11CharsSec;
extern UINT16 gKbcSetTypeDelay500MSec;
UINT8   gLastKeyCodeArray[8]={0,0,0,0,0,0,0,0};

//----------------------------------------------------------------------------
// Typematic rate delay table will have counts to generate key repeat delays.
// Since the periodic interrupt is set to 8msec the following repeat times
// will generate necessary delay.
// First three numbers are meant to define the frequency of the repeated keys;
// four other numbers are used to define the amount of delay between the first
// keypress-and-hold til the key actually starts repeating; the appropriate values
// of this table are selected using the equates defined in UsbKbd.h
//
UINT8   aTypematicRateDelayTable[]      =   {2, 4, 8, 16, 32, 48, 64, 96};

//
// The global data variables are stored in USB_GLOBAL_DATA structure and can be accessed through
// gUsbData->xxx
//

LEGACY_USB_KEYBOARD mLegacyKeyboard;

extern UINT8 IsKbcAccessBlocked;		//(EIP29733+)
extern  VOID USBKB_LEDOn();

BOOLEAN     gEfiMakeCodeGenerated=FALSE;
BOOLEAN     gLegacyMakeCodeGenerated=FALSE;

extern EFI_EMUL6064KBDINPUT_PROTOCOL* gKbdInput ;

UINT8	UsbControlTransfer(HC_STRUC*, DEV_INFO*, DEV_REQ, UINT16, VOID*);

UINT32	ExtractInputReportData (UINT8 *Report, UINT16 Offset, UINT16 Size);
                                        //(EIP90887+)>
typedef	BOOLEAN (KBD_BUFFER_CHECK_FUNCTIONS)( 
    DEV_INFO*   DevInfo,
    UINT8       *Buffer
	);
extern KBD_BUFFER_CHECK_FUNCTIONS KBD_BUFFER_CHECK_ELINK_LIST EndOfInitList;
KBD_BUFFER_CHECK_FUNCTIONS* KbdBufferCheckFunctionsList[] = {KBD_BUFFER_CHECK_ELINK_LIST NULL};
                                        //<(EIP90887+)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKBDInitialize (VOID)
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
USBKBDInitialize (VOID)
{
    UINT8       bTemp;

    //
    // Initialize the typematic rate to 500 ms, 10.9 Char/Sec and auto repeat flag
    // to disabled
    //
    gUsbData->wUSBKBC_StatusFlag |= ((gKbcSetTypeRate11CharsSec << KBC_TYPE_RATE_BIT_SHIFT) +
                                        (gKbcSetTypeDelay500MSec << KBC_TYPE_DELAY_BIT_SHIFT));

    USB_DEBUG (DEBUG_LEVEL_5, "USBKBDInitialize:  CodeBufferStart : %lx\n", gUsbData->aKBCScanCodeBufferStart);

    //
    // Initialize the scanner buffer
    //
    gUsbData->fpKBCScanCodeBufferPtr       = gUsbData->aKBCScanCodeBufferStart;
    gUsbData->bLastUSBKeyCode              = 0;

    //
    // Initialize the character buffer
    //
    gUsbData->fpKBCCharacterBufferHead     = gUsbData->aKBCCharacterBufferStart;
    gUsbData->fpKBCCharacterBufferTail     = gUsbData->aKBCCharacterBufferStart;

    //
    // Initialize the USB Data buffer
    //
    gUsbData->aKBCUsbDataBufferHead     = gUsbData->aKBCUsbDataBufferStart;
    gUsbData->aKBCUsbDataBufferTail     = gUsbData->aKBCUsbDataBufferStart;

    gUsbData->fpKeyRepeatDevInfo=NULL;

    //
    // Set scan code set to 2 in the scanner flag
    //
    gUsbData->wUSBKBC_StatusFlag           |= KBC_SET_SCAN_CODE_SET2;

    gUsbData->bUSBKBShiftKeyStatus = 0;

    //
    // Get the keyboard controller command byte (CCB) and store it locally
    //
    //USBKBC_GetAndStoreCCB();
    gUsbData->bCCB = 0x40;

    for (bTemp=0; bTemp<6; bTemp++) mLegacyKeyboard.KeyCodeStorage[bTemp] = 0;
    mLegacyKeyboard.KeyToRepeat = 0;

    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   USBKBDConfigureKeyboard
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
USBKBDConfigureDevice (
    DEV_INFO*   DevInfo
)
{
    UINT16          Index;

    DevInfo->fpPollTDPtr  = 0;                                      
    Index = USBKBDFindUSBKBDeviceTableEntry(DevInfo);
    if (Index == 0xFFFF) {
        Index  = USBKBDFindUSBKBDeviceTableEntry(NULL);
    }
    if (Index != 0xFFFF) {
        gUsbData->aUSBKBDeviceTable[Index] = DevInfo;
        if (!(gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI)) {
            if (BOOT_PROTOCOL_SUPPORT || (DevInfo->HidReport.Flag & HID_REPORT_FLAG_LED_FLAG) ||
                (DevInfo->wIncompatFlags & USB_INCMPT_HID_BOOT_PROTOCOL_ONLY)) {
                USBKB_LEDOn();
            }
        }
    } else {    
        return 0;
    }
    
    return DevInfo;
}
                                        //<(EIP84455+)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKBDFindUSBKBDeviceTableEntry
//
// Description: This routine searches for the HID table entry which matches
//              the provided device info structure
//
// Input:       fpDevInfo   Pointer to DeviceInfo structure
//
// Output:      offset of the HID table for the requested fpDevinfo
//              0xFFFF -on error
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16
USBKBDFindUSBKBDeviceTableEntry(DEV_INFO* fpDevinfo)
{
    UINT16      wCount ;

    for (wCount = 0; wCount < USB_DEV_HID_COUNT; wCount++)
    {
        if(gUsbData->aUSBKBDeviceTable[wCount] == fpDevinfo )
            return wCount;
    }
    USB_DEBUG (DEBUG_LEVEL_3, "No Free KBD DevInfo Entry\n");
    return 0xFFFF;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKBDDisconnectDevice
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
USBKBDDisconnectDevice (
    DEV_INFO*   DevInfo
)
{
    UINT16      Index;
                                        //(EIP93637+)>
    UINT8       ScanCodeCount = (UINT8)(gUsbData->fpKBCScanCodeBufferPtr - 
                         (UINT8*)gUsbData->aKBCScanCodeBufferStart);   //(EIP102150+) 
    UINT8       i = 0;
    UINT8       CurrentDeviceId;
    UINT8       Key;

    USB_KB_BUFFER   *KeyboardBuffer;
    KeyboardBuffer = gUsbData->EfiKeyboardBuffer;

    Index = USBKBDFindUSBKBDeviceTableEntry(DevInfo);
    if (Index == 0xFFFF) {
        USBLogError(USB_ERR_KBCONNECT_FAILED);
        return USB_ERROR;
    } else {
        CurrentDeviceId = (UINT8)(1 << ((DevInfo->bDeviceAddress) -1));
        while ((i < ScanCodeCount) && (ScanCodeCount != 0)) {     
            if (gUsbData->aKBCDeviceIDBufferStart[i] & CurrentDeviceId) {
                gUsbData->aKBCDeviceIDBufferStart[i] &= ~CurrentDeviceId;
                if (gUsbData->aKBCDeviceIDBufferStart[i] == 0) {
                    Key = gUsbData->aKBCScanCodeBufferStart[i]; 
                    if ((Key == HID_UP_KEYBOARD_RIGHT_SHIFT) ||
                        (Key == HID_UP_KEYBOARD_LEFT_SHIFT)) {
                        gUsbData->bUSBKBShiftKeyStatus &= ~(KB_RSHIFT_KEY_BIT_MASK+KB_LSHIFT_KEY_BIT_MASK);
                    }
                    USBKB_DiscardCharacter(&gUsbData->aKBCShiftKeyStatusBufferStart[i]); 
                    gUsbData->fpKBCScanCodeBufferPtr--;
                    ScanCodeCount--;
                    continue;
                }
            }
            i++;
        }
        if (gUsbData->fpKeyRepeatDevInfo == DevInfo) {
            for (i = 0; i < 8; i++) {
                *(gLastKeyCodeArray + i) = 0;
            }
            if(KeyboardBuffer->buffer[KeyboardBuffer->bHead].KeyCode == gUsbData->RepeatKey)
            {
                gUsbData->RepeatKey = 0;   
                KeyboardBuffer->bHead = KeyboardBuffer->bTail;
            }
        }
        gUsbData->aUSBKBDeviceTable[Index] = 0;
        return USB_SUCCESS;
    }
                                        //<(EIP93637+)
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKBC_CheckCharacterBufferFull
//
// Description: This routine checks whether the character buffer can hold
//              'N'+1 character
//
// Input:       bCount  Space needed in the buffer (in characters)
//
// Output:       0 If buffer is full
//              <> 0 If buffer is not full
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
USBKBC_CheckUsbDataBufferFull (UINT8 bCount)
{
    UINT8   *dHead, *dTail, *dStart, *dEnd;

    dHead = gUsbData->aKBCUsbDataBufferHead;
    dTail = gUsbData->aKBCUsbDataBufferTail;
    dStart = gUsbData->aKBCUsbDataBufferStart;
    dEnd = dStart + sizeof (gUsbData->aKBCUsbDataBufferStart);
    ++bCount;
    do {
        ++dHead;
        if(dHead == dEnd) dHead = dStart;
        if(dHead == dTail) return 0;
        --bCount;
    } while(bCount);

    return  0xFF;
}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKBC_SendToCharacterBuffer
//
// Description: This routine puts a character into the character buffer.
//              Character buffer pointers are also updated
//
// Input:       Nothing
//
// Output:      Nothing
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

void
USBKBC_SendToUsbDataBuffer (UINT8 *fpSrc)
{
    UINT8 *fPointer;
	UINT8 *fPtrEnd;
	UINT8 i;

    fPtrEnd = ( gUsbData->aKBCUsbDataBufferStart +
                sizeof (gUsbData->aKBCUsbDataBufferStart));

    fPointer = gUsbData->aKBCUsbDataBufferHead;

	for (i = 0; i < 8; i++) {
		*fPointer++ = *fpSrc++;
	}

    if(fPointer == fPtrEnd) {
        fPointer = gUsbData->aKBCUsbDataBufferStart;
    }

    gUsbData->aKBCUsbDataBufferHead = fPointer;

    return;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKBDProcessKeyboardData
//
// Description: This routine is called with USB keyboard report data.  This
//              routine handles the translation of  USB keyboard data
//              into PS/2 keyboard data, and makes the PS/2 data available
//              to software using ports 60/64h by communicating with
//              PS/2 keyboard controller.
//
// Input:       fpHCStruc   Pointer to HCStruc
//              fpDevInfo   Pointer to device information structure
//              fpTD        Pointer to the polling TD
//              fpBuffer    Pointer to the data buffer
//
// Output:      Nothing
//
// Notes:   TD's control status field has the packet length (0 based).
//      It could be one of three values 0,1 or 7 indicating packet
//      lengths of 1, 2 & 8 repectively.
//      The format of 8 byte data packet is as follow:
//           Byte              Description
//      -----------------------------------------------------------
//          0   Modifier key (like shift, cntr & LED status)
//          1   Reserved
//          2   Keycode of 1st key pressed
//          3   Keycode of 2nd key pressed
//          4   Keycode of 3rd key pressed
//          5   Keycode of 4th key pressed
//          6   Keycode of 5th key pressed
//          7   Keycode of 6th key pressed
//      -----------------------------------------------------------
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
USBKBDProcessKeyboardData (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Td,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UINT8               Count = 8;
	HID_REPORT_FIELD	*Field = NULL;
	UINT8				FieldIndex = 0;
	UINT32				BitOffset = 0;
	BOOLEAN				ValidData = FALSE;
	UINT8				Data = 0;
	UINT16				Index = 0;
	UINT8				UsageBuffer[32] = {0};
	UINT16				UsageIndex = 0;
	UINT8				i;
    UINTN               OemHookIndex;

	if (DevInfo->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
		for (FieldIndex = 0; FieldIndex < DevInfo->HidReport.FieldCount; FieldIndex++) {
			Field = DevInfo->HidReport.Fields[FieldIndex];

			// Check if the field is input report.
			if (!(Field->Flag & HID_REPORT_FIELD_FLAG_INPUT)) {
				continue;
			}
	
			//if report id exist, check first byte
			if ((Field->ReportId != 0) && (Field->ReportId != Buffer[0])) {
				continue;
			}

			// Check if the field is contant.
            if (Field->Flag & HID_REPORT_FIELD_FLAG_CONSTANT) {
			    BitOffset += Field->ReportCount * Field->ReportSize;
                continue;
            }

            //find start offset
			if (Field->UsagePage == HID_UP_KEYBOARD) {
                ValidData = TRUE;
                
                // If Report ID tags are used in the report descriptor, the first byte is
                // report id, we offset 8 bits to get data.  
				if (Field->ReportId != 0) {
					BitOffset += 8;
				}

				for (Index = 0; Index < Field->ReportCount; Index++) {
					Data = ExtractInputReportData(Buffer, 
						BitOffset + (Index * Field->ReportSize), Field->ReportSize);

					if ((Data < Field->LogicalMin) || (Data > Field->LogicalMax)) {
						continue;
					}
                    
					Data = Field->Flag & HID_REPORT_FIELD_FLAG_VARIABLE ?
							(Data != 0 ? Field->Usages[Index] : Data) :
							Field->Usages[Data - Field->LogicalMin];

					if ((Data != 0) && (UsageIndex < COUNTOF(UsageBuffer))) {
						UsageBuffer[UsageIndex++] = Data;
					}
				}
                if (Field->ReportId != 0) {
                    BitOffset -= 8;
                }
            }
			BitOffset += Field->ReportCount * Field->ReportSize;
		}

		if (ValidData == FALSE) {
			return USB_SUCCESS;
		}

        MemSet(Buffer, 8, 0);

        // Translate the report data to boot protocol data.
        
        // 0   Modifier key (like shift, cntr & LED status)
        // 1   Reserved
        // 2   Keycode of 1st key pressed
        // 3   Keycode of 2nd key pressed
        // 4   Keycode of 3rd key pressed
        // 5   Keycode of 4th key pressed
        // 6   Keycode of 5th key pressed
        // 7   Keycode of 6th key pressed

        for (Index = 0, i = 0; Index < UsageIndex; Index++) {
            if (UsageBuffer[Index] >= HID_UP_KEYBOARD_LEFT_CTRL && 
                UsageBuffer[Index] <= HID_UP_KEYBOARD_RIGHT_GUI) {
            	Buffer[0] |= 1 << (UsageBuffer[Index] - HID_UP_KEYBOARD_LEFT_CTRL);
            } else {
            	if (i < 6) {
            		Buffer[i + 2] = UsageBuffer[Index];
					i++;
            	}
            }
        }               
	}
                                        //(EIP90887+)>
    // Call all the OEM hooks that wants to check KBD buffer    
    for (OemHookIndex = 0; KbdBufferCheckFunctionsList[OemHookIndex]; OemHookIndex++) {
        if (KbdBufferCheckFunctionsList[OemHookIndex](DevInfo, Buffer)) {
            return USB_SUCCESS;
		}
	}
	                                    //<(EIP90887+)	
	//Is KBC access allowed?
	if (IsKbcAccessBlocked) {
		if (!(gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) || !gEfiMakeCodeGenerated) {
			return USB_SUCCESS;
		}
		MemSet(Buffer, 8, 0);
	}

    //
    // Save the device info pointer for later use
    //
    gUsbData->fpKeyRepeatDevInfo = DevInfo;

    for (i = 0, Count = 8; i < 8; i++, Count--) {
		if (Buffer[i]) {
			break;
		}
    }

    if ((gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI)) {
        if (Count==0) {
            gEfiMakeCodeGenerated=FALSE;
        } else {
            gEfiMakeCodeGenerated=TRUE;
            gLegacyMakeCodeGenerated=FALSE;
        }
    } else {
        if (Count==0) {
            gLegacyMakeCodeGenerated=FALSE;
        } else {
            gLegacyMakeCodeGenerated=TRUE;
            gEfiMakeCodeGenerated=FALSE;
        }
    }

    //
    // checks for new key stroke.
    // if no new key got, return immediately.
    //
    for (i = 0; i < 8; i ++) {
        if (Buffer[i] != gLastKeyCodeArray[i]) {
            break;
        }
    }

#if USB_HID_KEYREPEAT_USE_SETIDLE == 1 
    if ((i == 8) && gKeyRepeatStatus) {
        USBKBDPeriodicInterruptHandler(HcStruc);
        return USB_SUCCESS;
    }
#endif

    //
    // Update LastKeycodeArray[] buffer in the
    // Usb Keyboard Device data structure.
    //
    for (i = 0; i < 8; i ++) {
        gLastKeyCodeArray[i] = Buffer[i];
    }

    if ((!(gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) || gLegacyMakeCodeGenerated) &&(!gEfiMakeCodeGenerated))
    {
        if (Count==0) {
            gLegacyMakeCodeGenerated=FALSE;
        }
        UsbScanner(DevInfo, Buffer);
    } else {
        if(Count==0) {
            gEfiMakeCodeGenerated=FALSE;
        }

        if(USBKBC_CheckUsbDataBufferFull(8) == 0) {
            return EFI_SUCCESS;
        }

        USBKBC_SendToUsbDataBuffer(Buffer);

        //
        // Reload the typematic rate value
        //
        gUsbData->wRepeatRate = aTypematicRateDelayTable[
            (gUsbData->wUSBKBC_StatusFlag & KBC_TYPE_DELAY_BIT_MASK) >>
                            KBC_TYPE_DELAY_BIT_SHIFT];
        gUsbData->wRepeatCounter = 0;

        //
        // Enable periodic interrupt to catch the repeat key
        //
        if (Count==0) {
            USBKeyRepeat(NULL, 1);  // Disable Key repeat
        } else {
            USBKeyRepeat(NULL, 2);  // Enable Key repeat
        }
    }

    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKBDPeriodicInterruptHandler
//
// Description: This routine is called every 16ms and is used to send
//              the characters read from USB keyboard to the keyboard
//              controller for legacy operation. Also this function updates
//              the keyboard LED status
//
// Input:       fpHCStruc   Pointer to the HCStruc structure
//
// Output:      Nothing
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBKBDPeriodicInterruptHandler (HC_STRUC* fpHcStruc)
{
    if (gUsbData->dUSBStateFlag & USB_FLAG_RUNNING_UNDER_EFI) {
                                        //(EIP83888+)>
		if (!(*(UINT32*)gLastKeyCodeArray ||
				   *(UINT32*)(gLastKeyCodeArray + 4))) {    //(EIP93637)
                                        //<(EIP83888+)
			//
			// Keyboard data is zero, the key is released - stop repeating the key
			//
			USBKeyRepeat(NULL, 1);	// Disable Key repeat
			return;
		} else {
			//
			// Check whether keyboard buffer is not empty;
			// Execute Efi callback function if repeat counter is expired
			//
			gUsbData->wRepeatCounter++;
			if (gUsbData->wRepeatCounter >= gUsbData->wRepeatRate) {
				//
				// Repeat rate is reached.
				// Reload repeat delay counter with keyrepeat delay value; original
				// type delay value will be restored in ProcessKeyboardData
				//
				gUsbData->wRepeatRate	   = aTypematicRateDelayTable[
					(gUsbData->wUSBKBC_StatusFlag & KBC_TYPE_RATE_BIT_MASK) >>
							KBC_TYPE_RATE_BIT_SHIFT];
				gUsbData->wRepeatCounter   = 0;

				USBKBKeyrepeatCallback();
			}
			//
			// Reenable periodic interrupt handler
			//
			USBKeyRepeat(NULL, 2);	// Enable Key repeat
		}
    } else {    // Not under EFI
        LegacyAutoRepeat(fpHcStruc);
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbScanner
//
// Description: This routine is executed to convert USB scan codes into PS/2
//              make/bread codes.
//
// Input:       fpDevInfo   - USB keyboard device
//              fpBuffer    - USB scan codes data buffer
//
// Output:      Nothing
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbScanner(
    DEV_INFO *fpDevInfo,
    UINT8 *fpBuffer
)
{
    if(gUsbData->kbc_support || ((gUsbData->dUSBStateFlag & USB_FLAG_6064EMULATION_ON) 
        && (gUsbData->dUSBStateFlag & USB_FLAG_6064EMULATION_IRQ_SUPPORT))) {
        USBKBC_GetAndStoreCCB();
        USBKB_Scanner (fpDevInfo, fpBuffer);
        USBKB_UpdateLEDState (0xFF);
    }else {
        USBKB_Int9(fpBuffer);
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        LegacyAutoRepeat
//
// Description: This routine is called periodically based on 8ms TD and used
//              to implement the key repeat.
//
// Input:       Hc   Pointer to the HCStruc structure
//
// Output:      Nothing
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
LegacyAutoRepeat(
    HC_STRUC *Hc
)
{
    if(gUsbData->kbc_support || ((gUsbData->dUSBStateFlag & USB_FLAG_6064EMULATION_ON) 
        && (gUsbData->dUSBStateFlag & USB_FLAG_6064EMULATION_IRQ_SUPPORT))) {
        SysKbcAutoRepeat(Hc);
    } else {
        SysNoKbcAutoRepeat();
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKBKeyrepeatCallback
//
// Description: This routine is called every time the key repeat is requested
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
USBKBKeyrepeatCallback()
{
    USB_KEY         UsbKey;
    USB_KB_BUFFER   *KeyboardBuffer;

    if(!gUsbData->RepeatKey) return;     // Do nothing when there is no repeat key.

    KeyboardBuffer = gUsbData->EfiKeyboardBuffer;

    //
    // If keyboard buffer is full, throw the first key out of the keyboard buffer.
    //
    if (((KeyboardBuffer->bTail + 1) % (MAX_KEY_ALLOWED + 1)) == KeyboardBuffer->bHead) {

        UsbKey.KeyCode = KeyboardBuffer->buffer[KeyboardBuffer->bHead].KeyCode;
        UsbKey.Down = KeyboardBuffer->buffer[KeyboardBuffer->bHead].Down;

        //
        // adjust the head pointer of the FIFO keyboard buffer.
        //
        KeyboardBuffer->bHead = (UINT8)((KeyboardBuffer->bHead + 1) % (MAX_KEY_ALLOWED + 1));
    }

    KeyboardBuffer->buffer[KeyboardBuffer->bTail].KeyCode = gUsbData->RepeatKey;
    KeyboardBuffer->buffer[KeyboardBuffer->bTail].Down = 1;

    //
    // adjust the tail pointer of the FIFO keyboard buffer.
    //
    KeyboardBuffer->bTail = (UINT8)((KeyboardBuffer->bTail + 1) % (MAX_KEY_ALLOWED + 1));

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdSetLed
//
// Description: This routine set the USB keyboard LED status.
//
// Input:       DevInfo		Pointer to device information structure
//				LedStatus	LED status
//
// Output:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
UsbKbdSetLed (
	DEV_INFO    *DevInfo,
	UINT8		LedStatus
)
{
	HC_STRUC	*HcStruc = gUsbData->HcTable[DevInfo->bHCNumber - 1];
	DEV_REQ		DevReq = {0};
	UINT8		Status;
	UINT8		ReportId = 0;
	UINT16		ReportLen;
	UINT8		*ReportData = NULL;
	UINT8		Index;

	if ((DevInfo->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) && 
		!(DevInfo->HidReport.Flag & HID_REPORT_FLAG_LED_FLAG)) {
		return USB_ERROR;
	}

	ReportData = USB_MemAlloc(GET_MEM_BLK_COUNT(4));
	if (ReportData == NULL) return USB_ERROR;

	ReportLen = 1;
	ReportData[0] = LedStatus & 0x7;

	if (DevInfo->HidReport.Flag & HID_REPORT_FLAG_REPORT_PROTOCOL) {
        if (DevInfo->HidReport.Fields == NULL) {
            USB_MemFree(ReportData, GET_MEM_BLK_COUNT(4));
            return USB_ERROR;
        }
		for (Index = 0; Index < DevInfo->HidReport.FieldCount; Index++) {
			//find start offset
			if ((DevInfo->HidReport.Fields[Index]->UsagePage == 0x8) &&
				(DevInfo->HidReport.Fields[Index]->ReportId != 0) &&
				(DevInfo->HidReport.Fields[Index]->Usages[0] == 1)) {
				ReportId = DevInfo->HidReport.Fields[Index]->ReportId;
				ReportData[1] = ReportData[0];
				ReportData[0] = ReportId;
				ReportLen++;
			}
		}
	}
    if (DevInfo->IntOutEndpoint == 0) {
    	DevReq.wRequestType = HID_RQ_SET_REPORT;
    	DevReq.wValue = (0x02 << 8) | ReportId;		// Output
    	DevReq.wIndex = DevInfo->bInterfaceNum;
    	DevReq.wDataLength = ReportLen;
    
    	Status = UsbControlTransfer(HcStruc, DevInfo, DevReq, USB_KBD_SET_LED_TIMEOUT_MS, ReportData);
    } else {
        Status = UsbInterruptTransfer(HcStruc, DevInfo, DevInfo->IntOutEndpoint, 
            DevInfo->IntOutMaxPkt, ReportData, ReportLen, USB_KBD_SET_LED_TIMEOUT_MS);
    }

	USB_MemFree(ReportData, GET_MEM_BLK_COUNT(4));
	return Status;
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
