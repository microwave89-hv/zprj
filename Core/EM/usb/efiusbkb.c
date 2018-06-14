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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbkb.c 87    5/28/15 5:01a Wilsonlee $
//
// $Revision: 87 $
//
// $Date: 5/28/15 5:01a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbkb.c $
// 
// 87    5/28/15 5:01a Wilsonlee
// [TAG]  		EIP218997
// [Category]  	Improvement
// [Description]  	Break the GetQueue loop if UninstallDevice is failed.
// [Files]  		usbbus.c, efiusbkb.c, efiusbmass.c, efiusbms.c,
// efiusbpoint.c, efiusbhid.c
// 
// 86    4/23/15 11:28p Wilsonlee
// [TAG]  		EIP213823
// [Category]  	Improvement
// [Description]  	The memory type for "mUsbKeyboardRecord" is changed
// from EfiRuntimeServicesData to EfiBootServicesData.
// [Files]  		efiusbkb.c
// 
// 85    6/05/14 9:04p Wilsonlee
// [TAG]  		EIP171786
// [Category]  	Improvement
// [Description]  	The PS2 scan code of "0x64 Keyboard Non-US \ and |" is
// 0x56 and "0x67 Keypad =" is 0x59.
// [Files]  		efiusbkb.c
// 
// 84    12/20/13 7:36a Ryanchou
// [TAG]  		EIP145616
// [Category]  	Improvement
// [Description]  	Check if the key has been registered before.
// [Files]  		efiusbkb.c
// 
// 83    11/26/13 4:09a Ryanchou
// [TAG]  		EIP142509
// [Category]  	Improvement
// [Description]  	Added usage 0x87 and 0x89.
// [Files]  		efiusbkb.c, efiusbkb.h
// 
// 82    11/05/13 4:47a Ryanchou
// [TAG]  		EIP135636
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	NumLock LED cannot be on/off properly.
// [RootCause]  	It is the side effect of EIP #107429 changes, the
// keyboard does not generate break code when pressing NumLock.
// [Solution]  	Remove the EIP #107429 changes.
// [Files]  		amiusb.c, usbkbd.c, efiusbkb.c
// 
// 81    7/15/13 8:33a Rameshr
// [TAG]  		EIP124584
// [Category]  	Improvement
// [Description]  	Tab, Backspace, Enter Key's are considerd as Non
// printable Key's.
// [Files]  		efiusbkb.c
// 
// 80    3/07/13 9:10a Ryanchou
// [TAG]  		EIP114307
// [Category]  	Improvement
// [Description]  	Verified the record present in the linked list and if
// it's not present, start from the head node again.
// [Files]  		efiusbkb.c
// 
// 79    2/21/13 10:10a Ryanchou
// 
// 77    1/11/13 4:19a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 76    12/09/12 12:12a Wilsonlee
// [TAG]  		EIP107429
// [Category]  	Improvement
// [Description]  	Process the make code even if there is no break code.
// [Files]  		efiusbkb.c, amiusb.c
// 
// 75    11/26/12 9:57p Wilsonlee
// [TAG]  		EIP100370
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	The root cause is that a timer event of
// UsbKeyEvent(KEY_POLLING_INTERVAL(500000)) would be created while the
// function of SimpleTextInEX->RegisterKeyNotify() being invoked, but if
// we disconnect the Simple text in controllers through
// pBS->DisconnectController (HandleBuffer[Index], NULL, NULL), this timer
// still alive.
// [RootCause]  	The registered keys in mUsbKeyboardData queue are not
// cleaned when the USB keyboard driver is removed, which cause the timer
// to keep running and the stopping condition in function
// UsbKbdUnregisterKeyNotify could not be reached.
// [Solution]  	Examine the mUsbKeyboardData queue at UninstallUSBKeyboard
// and remove the registered keys inside if they are not empty.
// [Files]  		efiusbkb.c
// 
// 74    11/15/12 3:47a Ryanchou
// 
// 72    11/01/12 6:32a Deepthins
// [TAG]  		EIP101102 
// [Category]  	Improvement
// [Description]  	Multi Language is supported in USB driver
// [Files]  		efiusbkb.c, efiusbkb.h
// 
// 71    10/24/12 1:24a Wilsonlee
// [TAG]  		EIP100370
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	The root cause is that a timer event of
// UsbKeyEvent(KEY_POLLING_INTERVAL(500000)) would be created while the
// function of SimpleTextInEX->RegisterKeyNotify() being invoked, but if
// we disconnect the Simple text in controllers through
// pBS->DisconnectController (HandleBuffer[Index], NULL, NULL), this timer
// still alive.
// [RootCause]  	The registered keys in mUsbKeyboardData queue are not
// cleaned when the USB keyboard driver is removed, which cause the timer
// to keep running and the stopping condition in function
// UsbKbdUnregisterKeyNotify could not be reached.
// [Solution]  	Examine the mUsbKeyboardData queue at UninstallUSBKeyboard
// and remove the registered keys inside if they are not empty.
// [Files]  		efiusbkb.c
// 
// 70    9/24/12 8:37a Ryanchou
// Correct the KeyToggleState check in UsbKbdSetState.
// 
// 69    8/29/12 8:36a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 68    8/06/12 11:45p Roberthsu
// [TAG]           EIP91889
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       CSInSetState has no function when Bootup NumLock State
// is set to OFF
// [RootCause]     UsbKbdSetState does not work.
// [Solution]      Store ToggleState in function UsbKbdSetState.
// [Files]         efiusbkb.c
// 
// 67    5/22/12 10:32a Lavanyap
// [TAG]  		EIP88049 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Keyboard LED status is synchronised when it is plugged out
// and in.
// [RootCause]  	Existing LED state is not updated when a keyboard is
// installed.
// [Solution]  	Updated existing LED state when a keyboard is installed.
// [Files]  		efiusbkb.c
// 
// 66    5/03/12 5:56a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 65    5/03/12 4:03a Ryanchou
// [TAG]  		EIP85918
// [Category]  	Improvement
// [Description]  	Change the reset type of Ctrl+Alt+Del to EfiResetWarm.
// [Files]  		efiusbkb.c
// 
// 64    4/24/12 3:37a Roberthsu
// [TAG]           EIP83888
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Can not catch F8 key event on Keyboard
// [RootCause]     OS only call readkeystroke once.If OS get break key
// readkeystroke will return EFI_NOT_READY.
// [Solution]      UsbKbdReadKeyStroke will serach available key in usb
// data buffer.Fixed key repeat can not 
//                 work  when efi to legacy or legacy to efi.
// [Files]         efiusbkb.c,usbkbd.c
// 
// 63    4/24/12 2:14a Deepthins
// [TAG]  		EIP85747 
// [Category]  	Improvement
// [Description]  	USB-ReadKeyStrokeEx is returning EFI_SUCCESS with
// KEY_STATE_EXPOSED for Caps, Num and Scroll Lock Key's.
// KEY_STATE_EXPOSED only for the ShiftState Key's and not for togglestate
// key's.
// [Files]  		Efiusbkb.c, ps2kbd.c and kbc.h
// 
// 62    4/10/12 2:38a Rameshr
// [TAG]  		EIP87058
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Not able to recognise Pause Key Click using ReadKeyStroke
// [RootCause]  	Pause Key detection should be done always and only the
// pause key action should be controlled by PAUSEKEY_SUPPORT SDL token
// [Solution]  	SDL token checking removed for the Pause Key detection
// [Files]  		efiusbkb.c
// 
// 61    3/20/12 10:32p Wilsonlee
// [TAG]  		EIP83295
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System will hang at B2 when do S3/S4 long run test or DOS
// reboot test.
// [RootCause]  	It causes the stack problem when we call
// IsUSBKeyboardBufferEmpty function.
// [Solution]  	Change to use pointer as parameter to
// IsUSBKeyboardBufferEmpty function.
// [Files]  		efiusbkb.c, efisubkb.h, usbmass.c, ehci.c
// 
// 60    3/02/12 3:55a Rameshr
// [TAG]  		EIP81563
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Press SHIFT key will result in the ReadKeyStroke return
// unexpected ScanCode and UnicodeChar
// [RootCause]  	When the Partial Key returned, ScanCode and Unicode are
// not filled correctly.
// [Solution]  	Initilized the Scan code and UniCode to NULL Value.
// [Files]  		Efiusbkb.c
// 
// 59    2/21/12 5:24a Rameshr
// [TAG]  		EIP82772
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Usb Keyboard works even if the SimpleTextin uninstalled for
// the UsbKeyboard
// [RootCause]  	RegsiterKeyNotify Function event not stopped even after
// SimpleTextin Uninstalled
// [Solution]  	Stopped the KeyPolling Event if no more USB keyboard in
// the system
// [Files]  		efiusbkb.c
// 
// 58    12/29/11 12:37a Deepthins
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
// [Files]  		Efiusbkb.c, Efiusbhid.c, efiusbkb.c
// 
// 57    12/14/11 2:09a Ryanchou
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
// 56    9/23/11 12:32a Rameshr
// [TAG]  		EIP63054
// [Category]  	New Feature
// [Description]  	0000790: Add warning to ReadKeyStrokeEx for partial key
// press
// [Files]  		KeyboardCommonDefinitions.h, In.c, Kbc.h, Ps2Kbd.c,
// Efiusbkb.c, efiusbkb.h, efiusbhid.c
// 
// 55    8/25/11 11:49a Davidd
// [TAG]  		EIPEIP55336
// [Description]  	Removed EFI_DEADLOOP() in ClearUsbKbBuffer function
// from previous check-in file version 54. It was used during testing and
// inadvertently left over at the time of check-in.
// [Files]  		efiusbkb.c
// 
// 54    8/16/11 2:29p Davidd
// [TAG]           EIP55336
// [Category]      New Feature
// [Description]   Add optional code to clear keyboard buffer at
// ReadyToBoot in USB driver
// [Files]         Efiusbkb.c
//                 Usbsrc.sdl
// 
// 53    7/15/11 6:23a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, efiusbpoint.c, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c,
// usb.c, usbdef.h, usbhid.c, usbkbd.c, usbkbd.h, usbms.c, usbpoint.c,
// usbrt.cif, usbsb.c, usbsetup.c, usbsrc.sdl, xhci.c
// 
// 52    5/30/11 2:54a Ryanchou
// [TAG]  		EIP60562
// [Category]  	Improvement
// [Description]  	F11/F12 efi scan code correction.
// [Files]  		efiusbkb.c
// 
// 51    5/03/11 10:47a Ryanchou
// [TAG]  		EIP59272
// [Category]  	Improvement
// [Description]  	According Uefi 2.1 Aptio porting document, changes made
// to install the component name protocol.
// [Files]  		componentname.c, componentname.h, efiusbkb.c, efiusbmass.c,
// efiusbms.c, uhcd.c, uhcd.h, usbbus.c
// 
// 50    3/04/11 1:30p Olegi
// 
// 49    3/04/11 1:25p Olegi
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
// 48    10/12/10 4:37a Rameshr
// [TAG] - EIP 42956
// [Category]- BUG FIX
// [Severity]- Major
// [Symptom] - KeyNotificationFunction gets control twice for every key
// press in USB keyboard
// [RootCause] - KeyNotificationFunction gets called for each Key Press
// and Key Release 
// [Solution] - Previous check-in has the wrong solution and corrected
// now.
// [Files] - EfiUsbKb.c
// 
// 47    9/13/10 1:56a Rameshr
// [TAG] - EIP 42956
// [Category]- BUG FIX
// [Severity]- Major
// [Symptom] - KeyNotificationFunction gets control twice for every key
// press in USB keyboard
// [RootCause] - KeyNotificationFunction gets called for each Key Press
// and Key Release 
// [Solution] - Added code to check only call KeyNotificationFunction on
// Key Press.
// [Files] - EfiUsbKb.c 
// 
// 46    7/20/10 4:34a Rameshr
// Corrected the FreePool call in UnRegisterKeyNotify function
// 
// 45    5/14/10 10:57a Olegi
// - Tabs converted to spaces
// - Added FreePool call in UnregisterKeyNotify function
//
// 44    5/10/10 2:31a Rameshr
// Issue:Usb Keyboard driver doesn't handle the Shift Key properly in
// RegsiterkeyNotify function
// Solution: ShiftKeyState and KeyToggleState verified for
// RegisterKeyNotify callback function.
// EIP 38213
//
// 43    5/10/10 2:04a Rameshr
// PrintScreen/SysRq key, Menu Key, Left Logo and Right Logo Key support
// in USB Keyboard driver
// EIP 38214
//
// 42    5/10/10 1:57a Rameshr
// Issue:UsbKeyboard Driver doesn’t differentiate between Left Shift and
// Right Shift Key.
// Solution: modified the driver to differentiate between Left
// Shift/Alt/Ctrl and Right Shift/Alt/Ctrl Key's.
// EIP 38256
//
// 41    2/24/10 3:52p Olegi
// Updated PS2ScanCodeIsValid field while returning AMI_KEYCODE from USB
// keyboard.
//
// 40    2/23/10 1:36p Olegi
// Work around Klockwork issues. EIP34370
//
// 39    9/15/09 12:01p Olegi
// Implemented a circular buffer in KeypressCallback; related (indirectly)
// to EIP#25841
//
// 38    8/13/09 2:59p Rameshr
// When item "num-lock status" set off, Num-lock will keep open until in
// DOS.
// EIP:21757
//
// 37    5/07/09 5:20p Olegi
// Numeric keypad scancode correction.
//
// 36    3/30/09 10:33a Pats
// Issue: EIP 19547 - Pause key support needed in Aptio
// Solution: Functions UsbParseKey and USBKeyCodeToEFIScanCode modified to
// pass EFI_KEY vaule of pause key on rather than rejecting it.
//
// 35    1/22/09 3:00p Olegi
// Bugfix for EIP#19039.
//
// 34    1/07/09 11:01a Olegi
// Bugfix for EIP#18267
//
// 33    11/17/08 10:20a Rameshraju
// Problem:SCT failure on RegisterKeyNotify, SetState and
// UnregisterKeyNotify.
// Fix : Validated the input parameters for RegisterKeyNotify, SetState
// and UnregisterKeyNotify.
// EIP:17578
//
// 32    10/08/08 4:34p Olegi
// Implemented the Register/Unregister key notofocation function in
// SimpletextinEx protocol.
//
// 31    10/03/08 3:32p Olegi
//
// 30    9/05/08 4:15p Olegi
// fpCallbackNotify functions removed.
//
// 29    8/07/08 11:52a Olegi
// Bugfix in UsbKbdReadKeyStrokeEx.
//
// 28    6/05/08 3:34p Olegi
//
// 27    6/05/08 3:27p Olegi
// Bugfix in processing '5' key on a keypad: when NumLock is off, it
// should not produce a character.
//
// 26    5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
//
// 25    12/17/07 5:42p Rameshraju
// Added the core revision check for the AMI Keycode to build with OLD
// core.
//
// 24    10/25/07 4:47p Olegi
//
// 23    10/23/07 4:16p Olegi
// AmiKeycode protocol implementation.
//
// 22    9/18/07 12:18p Olegi
//
// 19    7/26/07 4:26p Olegi
// F11 and F12 keys are not ignored anymore.
//
// 18    7/13/07 11:44a Olegi
// F11 and F12 codes added.
//
// 17    4/17/07 8:22a Olegi
// Bugfix in UninstallUSBKeyboard function.
//
// 16    3/20/07 1:29p Olegi
//
// 15    12/08/06 3:25p Olegi
// Bugfix in the sequence of multiple keyboard
// installation/deinstallation.
//
// 13    10/12/06 7:12p Andriyn
// Support unexpected plug-off USB device
//
// 12    7/19/06 3:54p Olegi
//
// 11    5/03/06 9:59a Olegi
//
// 10    3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 9     3/01/06 3:53p Olegi
// Added USB_LEGACY_PLATFORM_SUPPORT.
//
// 8     1/11/06 11:54a Olegi
// EfiResetShutdown has changed to EfiResetCold.
//
// 7     11/22/05 4:06p Andriyn
// Fix: EFI shell hangs when Ctrl-Al-Del reset the system from USB
// keyboard
//
// 6     6/15/05 4:05p Olegi
// EfiResetShutdown is replaced with EfiResetWarm on Ctl+Alt+Del.
//
// 5     6/01/05 5:10p Olegi
// Debug message shortened.
//
// 4     5/19/05 8:06p Olegi
// Aptio changes in driver 8.1 implementation.
//
// 3     5/17/05 7:51p Andriyn
// USB BUS pre-release
//
// 2     5/10/05 4:13p Andriyn
// USBBUS implementation
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//****************************************************************************
//<AMI_FHDR_START>
//
//  Name:           EfiUsbKb.c
//
//  Description:    USB Keyboard Efi driver implementation
//
//<AMI_FHDR_END>
//****************************************************************************

#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"
#include "efiusbkb.h"
#include "usbkbd.h"

#include "componentname.h"
#include "usbbus.h"

#ifndef KEY_STATE_EXPOSED
#define KEY_STATE_EXPOSED   0x40
#endif

#define     KEY_POLLING_INTERVAL    500000

extern  USB_GLOBAL_DATA *gUsbData;
extern  EFI_GUID gEfiHotPlugDeviceGuid;
extern  EFI_EVENT   UsbKeyEvent;

EFI_STATUS  UsbCheckKeyNotify(UINT8 Key);

USB_KEYBOARD_DATA*   gUsbKeyboardData;

#if CLEAR_USB_KB_BUFFER_AT_READYTOBOOT
EFI_EVENT 		gClearUsbKbBufferEvent;
#endif

typedef struct _KEY_WAITING_RECORD{
  DLINK                                         Link;
  USB_KB_DEV*                                   UsbKbDev;	//(EIP100370+)
  EFI_KEY_DATA                                  Context;
  EFI_KEY_NOTIFY_FUNCTION                       Callback;
  BOOLEAN                                       CallbackStatus;
} KEY_WAITING_RECORD;

DLIST                               mUsbKeyboardData;
KEY_WAITING_RECORD                  *mUsbKeyboardRecord;
BOOLEAN                             KeyProcessed=TRUE;
static EFI_GUID                     gAmiMultiLangSupportGuid = AMI_MULTI_LANG_SUPPORT_PROTOCOL_GUID;
AMI_MULTI_LANG_SUPPORT_PROTOCOL     *gMultiLangSupportProtocol;


//
// USB Key Code to Efi key mapping table
// Format:
// <efi scan code>, <unicode w/o shift>, <unicode w shift>, <PS2 scan code>
//
static
UINT8 KeyConvertionTable[USB_KEYCODE_MAX_MAKE][4] = {
    SCAN_NULL,      'a',    'A',    0x1e,   // 0x04
    SCAN_NULL,      'b',    'B',    0x30,   // 0x05
    SCAN_NULL,      'c',    'C',    0x2e,   // 0x06
    SCAN_NULL,      'd',    'D',    0x20,   // 0x07
    SCAN_NULL,      'e',    'E',    0x12,   // 0x08
    SCAN_NULL,      'f',    'F',    0x21,   // 0x09
    SCAN_NULL,      'g',    'G',    0x22,   // 0x0A
    SCAN_NULL,      'h',    'H',    0x23,   // 0x0B
    SCAN_NULL,      'i',    'I',    0x17,   // 0x0C
    SCAN_NULL,      'j',    'J',    0x24,   // 0x0D
    SCAN_NULL,      'k',    'K',    0x25,   // 0x0E
    SCAN_NULL,      'l',    'L',    0x26,   // 0x0F
    SCAN_NULL,      'm',    'M',    0x32,   // 0x10
    SCAN_NULL,      'n',    'N',    0x31,   // 0x11
    SCAN_NULL,      'o',    'O',    0x18,   // 0x12
    SCAN_NULL,      'p',    'P',    0x19,   // 0x13
    SCAN_NULL,      'q',    'Q',    0x10,   // 0x14
    SCAN_NULL,      'r',    'R',    0x13,   // 0x15
    SCAN_NULL,      's',    'S',    0x1f,   // 0x16
    SCAN_NULL,      't',    'T',    0x14,   // 0x17
    SCAN_NULL,      'u',    'U',    0x16,   // 0x18
    SCAN_NULL,      'v',    'V',    0x2f,   // 0x19
    SCAN_NULL,      'w',    'W',    0x11,   // 0x1A
    SCAN_NULL,      'x',    'X',    0x2d,   // 0x1B
    SCAN_NULL,      'y',    'Y',    0x15,   // 0x1C
    SCAN_NULL,      'z',    'Z',    0x2c,   // 0x1D
    SCAN_NULL,      '1',    '!',    0x02,   // 0x1E
    SCAN_NULL,      '2',    '@',    0x03,   // 0x1F
    SCAN_NULL,      '3',    '#',    0x04,   // 0x20
    SCAN_NULL,      '4',    '$',    0x05,   // 0x21
    SCAN_NULL,      '5',    '%',    0x06,   // 0x22
    SCAN_NULL,      '6',    '^',    0x07,   // 0x23
    SCAN_NULL,      '7',    '&',    0x08,   // 0x24
    SCAN_NULL,      '8',    '*',    0x09,   // 0x25
    SCAN_NULL,      '9',    '(',    0x0a,   // 0x26
    SCAN_NULL,      '0',    ')',    0x0b,   // 0x27
    SCAN_NULL,      0x0d,   0x0d,   0x1c,   // 0x28   Enter
    SCAN_ESC,       0x00,   0x00,   0x01,   // 0x29   Esc
    SCAN_NULL,      0x08,   0x08,   0x0e,   // 0x2A   Backspace
    SCAN_NULL,      0x09,   0x09,   0x0f,   // 0x2B   Tab
    SCAN_NULL,      ' ',    ' ',    0x39,   // 0x2C   Spacebar
    SCAN_NULL,      '-',    '_',    0x0c,   // 0x2D
    SCAN_NULL,      '=',    '+',    0x0d,   // 0x2E
    SCAN_NULL,      '[',    '{',    0x1a,   // 0x2F
    SCAN_NULL,      ']',    '}',    0x1b,   // 0x30
    SCAN_NULL,      '\\',   '|',    0x2b,   // 0x31
    SCAN_NULL,      '\\',   '|',    0x2b,   // 0x32  Keyboard US \ and |
    SCAN_NULL,      ';',    ':',    0x27,   // 0x33
    SCAN_NULL,      '\'',   '"',    0x28,   // 0x34
    SCAN_NULL,      '`',    '~',    0x29,   // 0x35  Keyboard Grave Accent and Tlide
    SCAN_NULL,      ',',    '<',    0x33,   // 0x36
    SCAN_NULL,      '.',    '>',    0x34,   // 0x37
    SCAN_NULL,      '/',    '?',    0x35,   // 0x38
    SCAN_NULL,      0x00,   0x00,   0x3a,   // 0x39   CapsLock
    SCAN_F1,        0x00,   0x00,   0x3b,   // 0x3A
    SCAN_F2,        0x00,   0x00,   0x3c,   // 0x3B
    SCAN_F3,        0x00,   0x00,   0x3d,   // 0x3C
    SCAN_F4,        0x00,   0x00,   0x3e,   // 0x3D
    SCAN_F5,        0x00,   0x00,   0x3f,   // 0x3E
    SCAN_F6,        0x00,   0x00,   0x40,   // 0x3F
    SCAN_F7,        0x00,   0x00,   0x41,   // 0x40
    SCAN_F8,        0x00,   0x00,   0x42,   // 0x41
    SCAN_F9,        0x00,   0x00,   0x43,   // 0x42
    SCAN_F10,       0x00,   0x00,   0x44,   // 0x43
 										//(EIP60562)>
    SCAN_F11,       0x00,   0x00,   0x57,   // 0x44   F11
    SCAN_F12,       0x00,   0x00,   0x58,   // 0x45   F12
 										//<(EIP60562)
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x46   PrintScreen
    SCAN_NULL,      0x00,   0x00,   0x46,   // 0x47   Scroll Lock
    SCAN_PAUSE,     0x00,   0x00,   0x00,   // 0x48   Pause
    SCAN_INSERT,    0x00,   0x00,   0x52,   // 0x49
    SCAN_HOME,      0x00,   0x00,   0x47,   // 0x4A
    SCAN_PAGE_UP,   0x00,   0x00,   0x49,   // 0x4B
    SCAN_DELETE,    0x00,   0x00,   0x53,   // 0x4C
    SCAN_END,       0x00,   0x00,   0x4f,   // 0x4D
    SCAN_PAGE_DOWN, 0x00,   0x00,   0x51,   // 0x4E
    SCAN_RIGHT,     0x00,   0x00,   0x4d,   // 0x4F
    SCAN_LEFT,      0x00,   0x00,   0x4b,   // 0x50
    SCAN_DOWN,      0x00,   0x00,   0x50,   // 0x51
    SCAN_UP,        0x00,   0x00,   0x48,   // 0x52
    SCAN_NULL,      0x00,   0x00,   0x45,   // 0x53   NumLock
    SCAN_NULL,      '/',    '/',    0x35,   //  0x54
    SCAN_NULL,      '*',    '*',    0x37,   // 0x55
    SCAN_NULL,      '-',    '-',    0x4a,   // 0x56
    SCAN_NULL,      '+',    '+',    0x4e,   // 0x57
    SCAN_NULL,      0x0d,   0x0d,   0x1c,   // 0x58
    SCAN_END,       '1',    '1',    0x4f,   // 0x59
    SCAN_DOWN,      '2',    '2',    0x50,   // 0x5A
    SCAN_PAGE_DOWN, '3',    '3',    0x51,   // 0x5B
    SCAN_LEFT,      '4',    '4',    0x4b,   // 0x5C
    SCAN_NULL,      '5',    '5',    0x4c,   // 0x5D
    SCAN_RIGHT,     '6',    '6',    0x4d,   // 0x5E
    SCAN_HOME,      '7',    '7',    0x47,   // 0x5F
    SCAN_UP,        '8',    '8',    0x48,   // 0x60
    SCAN_PAGE_UP,   '9',    '9',    0x49,   // 0x61
    SCAN_INSERT,    '0',    '0',    0x52,   // 0x62
    SCAN_DELETE,    '.',    '.',    0x53,   // 0x63
    SCAN_NULL,      '\\',   '|',    0x56,   // 0x64 Keyboard Non-US \ and |
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x65 Keyboard Application
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x66 Keyboard Power
    SCAN_NULL,      '=' ,   '=',    0x59,   // 0x67 Keypad =

    SCAN_F13,       0x00,   0x00,   0x64,   // 0x68 F13
    SCAN_F14,       0x00,   0x00,   0x65,   // 0x69 F14
    SCAN_F15,       0x00,   0x00,   0x66,   // 0x6A F15
    SCAN_F16,       0x00,   0x00,   0x67,   // 0x6B F16
    SCAN_F17,       0x00,   0x00,   0x68,   // 0x6C F17
    SCAN_F18,       0x00,   0x00,   0x69,   // 0x6D F18
    SCAN_F19,       0x00,   0x00,   0x6A,   // 0x6E F19
    SCAN_F20,       0x00,   0x00,   0x6B,   // 0x6F F20
    SCAN_F21,       0x00,   0x00,   0x6C,   // 0x70 F21
    SCAN_F22,       0x00,   0x00,   0x6D,   // 0x71 F22
    SCAN_F23,       0x00,   0x00,   0x6E,   // 0x72 F23
    SCAN_F24,       0x00,   0x00,   0x76,   // 0x73 F24

    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x74
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x75
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x76
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x77
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x78
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x79
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x7A
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x7B
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x7C
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x7D
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x7E
    SCAN_MUTE,      0x00,   0x00,   0x00,   // 0x7F
    SCAN_VOLUME_UP, 0x00,   0x00,   0x00,   // 0x80
    SCAN_VOLUME_DOWN, 0x00, 0x00,   0x00,   // 0x81
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x82
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x83
    SCAN_NULL,      0x00,   0x00,   0x00,   // 0x84
    SCAN_NULL,      '.',    0x00,   0x7E,   // 0x85
    SCAN_NULL,      '=',    0x00,   0x00,   // 0x86
    SCAN_NULL,      '\\',   '_',    0x73,   // 0x87 backslash
    SCAN_NULL,      0x00,   0x00,   0x70,   // 0x88
    SCAN_NULL,      0xA5,   '|',    0x7D,   // 0x89 Yen Symbol
 };

KB_MODIFIER KB_Mod[8] = {
    { MOD_CONTROL_L,  0xe0 }, // 11100000
    { MOD_CONTROL_R,  0xe4 }, // 11100100
    { MOD_SHIFT_L,    0xe1 }, // 11100001
    { MOD_SHIFT_R,    0xe5 }, // 11100101
    { MOD_ALT_L,      0xe2 }, // 11100010
    { MOD_ALT_R,      0xe6 }, // 11100110
    { MOD_WIN_L,      0xe3 }, // 11100011
    { MOD_WIN_R,      0xe7 }, // 11100111
};


UINT8 UsbToEfiKeyTable[USB_KEYCODE_MAX_MAKE] = {
    EfiKeyC1, //      'a',    'A',    0x1e,   // 0x04
    EfiKeyB5, //      'b',    'B',    0x30,   // 0x05
    EfiKeyB3, //      'c',    'C',    0x2e,   // 0x06
    EfiKeyC3, //      'd',    'D',    0x20,   // 0x07
    EfiKeyD3, //      'e',    'E',    0x12,   // 0x08
    EfiKeyC4, //      'f',    'F',    0x21,   // 0x09
    EfiKeyC5, //      'g',    'G',    0x22,   // 0x0A
    EfiKeyC6, //      'h',    'H',    0x23,   // 0x0B
    EfiKeyD8, //      'i',    'I',    0x17,   // 0x0C
    EfiKeyC7, //      'j',    'J',    0x24,   // 0x0D
    EfiKeyC8, //      'k',    'K',    0x25,   // 0x0E
    EfiKeyC9, //      'l',    'L',    0x26,   // 0x0F
    EfiKeyB7, //      'm',    'M',    0x32,   // 0x10
    EfiKeyB6, //      'n',    'N',    0x31,   // 0x11
    EfiKeyD9, //      'o',    'O',    0x18,   // 0x12
    EfiKeyD10,//       'p',    'P',    0x19,   // 0x13
    EfiKeyD1, //      'q',    'Q',    0x10,   // 0x14
    EfiKeyD4, //      'r',    'R',    0x13,   // 0x15
    EfiKeyC2, //      's',    'S',    0x1f,   // 0x16
    EfiKeyD5, //      't',    'T',    0x14,   // 0x17
    EfiKeyD7, //      'u',    'U',    0x16,   // 0x18
    EfiKeyB4, //      'v',    'V',    0x2f,   // 0x19
    EfiKeyD2, //      'w',    'W',    0x11,   // 0x1A
    EfiKeyB2, //      'x',    'X',    0x2d,   // 0x1B
    EfiKeyD6, //      'y',    'Y',    0x15,   // 0x1C
    EfiKeyB1, //      'z',    'Z',    0x2c,   // 0x1D
    EfiKeyE1, //      '1',    '!',    0x02,   // 0x1E
    EfiKeyE2, //      '2',    '@',    0x03,   // 0x1F
    EfiKeyE3, //      '3',    '#',    0x04,   // 0x20
    EfiKeyE4, //      '4',    '$',    0x05,   // 0x21
    EfiKeyE5, //      '5',    '%',    0x06,   // 0x22
    EfiKeyE6, //      '6',    '^',    0x07,   // 0x23
    EfiKeyE7, //      '7',    '&',    0x08,   // 0x24
    EfiKeyE8, //      '8',    '*',    0x09,   // 0x25
    EfiKeyE9, //      '9',    '(',    0x0a,   // 0x26
    EfiKeyE10,  //       '0',    ')',    0x0b,   // 0x27
    EfiKeyEnter,//       0x0d,   0x0d,   0x1c,   // 0x28   Enter
    EfiKeyEsc,  //      0x00,   0x00,   0x01,   // 0x29   Esc
    EfiKeyBackSpace,    //       0x08,   0x08,   0x0e,   // 0x2A   Backspace
    EfiKeyTab,      //   0x09,   0x09,   0x0f,   // 0x2B   Tab
    EfiKeySpaceBar, //   ' ',    ' ',    0x39,   // 0x2C   Spacebar
    EfiKeyE11,      //   '-',    '_',    0x0c,   // 0x2D
    EfiKeyE12,      //   '=',    '+',    0x0d,   // 0x2E
    EfiKeyD11,      //   '[',    '{',    0x1a,   // 0x2F
    EfiKeyD12,      //   ']',    '}',    0x1b,   // 0x30
    EfiKeyD13,      //   '\\',   '|',    0x2b,   // 0x31
    EfiKeyC12,      //   '\\',   '|',    0x2b,   // 0x32  Keyboard Non-US # and ~
    EfiKeyC10,      //   ';',    ':',    0x27,   // 0x33
    EfiKeyC11,      //   '\'',   '"',    0x28,   // 0x34
    EfiKeyE0,       //   '`',    '~',    0x29,   // 0x35  Keyboard Grave Accent and Tlide
    EfiKeyB8,       //   ',',    '<',    0x33,   // 0x36
    EfiKeyB9,       //   '.',    '>',    0x34,   // 0x37
    EfiKeyB10,      //   '/',    '?',    0x35,   // 0x38
    EfiKeyCapsLock, //   0x00,   0x00,   0x00,   // 0x39   CapsLock
    EfiKeyF1,       //   0x00,   0x00,   0x3b,   // 0x3A
    EfiKeyF2,       //   0x00,   0x00,   0x3c,   // 0x3B
    EfiKeyF3,       //   0x00,   0x00,   0x3d,   // 0x3C
    EfiKeyF4,       //   0x00,   0x00,   0x3e,   // 0x3D
    EfiKeyF5,       //   0x00,   0x00,   0x3f,   // 0x3E
    EfiKeyF6,       //   0x00,   0x00,   0x40,   // 0x3F
    EfiKeyF7,       //   0x00,   0x00,   0x41,   // 0x40
    EfiKeyF8,       //   0x00,   0x00,   0x42,   // 0x41
    EfiKeyF9,       //   0x00,   0x00,   0x43,   // 0x42
    EfiKeyF10,      //   0x00,   0x00,   0x44,   // 0x43
    EfiKeyF11,      //   0x00,   0x00,   0x85,   // 0x44   F11
    EfiKeyF12,      //   0x00,   0x00,   0x86,   // 0x45   F12
    EfiKeyPrint,    //   0x00,   0x00,   0x00,   // 0x46   PrintScreen
    EfiKeySLck,     //   0x00,   0x00,   0x00,   // 0x47   Scroll Lock
    EfiKeyPause,    //   0x00,   0x00,   0x00,   // 0x48   Pause
    EfiKeyIns,      //   0x00,   0x00,   0x52,   // 0x49
    EfiKeyHome,     //   0x00,   0x00,   0x47,   // 0x4A
    EfiKeyPgUp,     //   0x00,   0x00,   0x49,   // 0x4B
    EfiKeyDel,      //   0x00,   0x00,   0x53,   // 0x4C
    EfiKeyEnd,      //   0x00,   0x00,   0x4f,   // 0x4D
    EfiKeyPgDn,     //   0x00,   0x00,   0x51,   // 0x4E
    EfiKeyRightArrow, // 0x00,   0x00,   0x4d,   // 0x4F
    EfiKeyLeftArrow,  // 0x00,   0x00,   0x4b,   // 0x50
    EfiKeyDownArrow,  // 0x00,   0x00,   0x50,   // 0x51
    EfiKeyUpArrow,    // 0x00,   0x00,   0x48,   // 0x52
    EfiKeyNLck,       // 0x00,   0x00,   0x00,   // 0x53   NumLock
    EfiKeySlash,      // '/',    '/',    0x35,   // 0x54
    EfiKeyAsterisk,   // '*',    '*',    0x37,   // 0x55
    EfiKeyMinus,      // '-',    '-',    0x4a,   // 0x56
    EfiKeyPlus,       // '+',    '+',    0x4e,   // 0x57
    EfiKeyEnter,      // 0x0d,   0x0d,   0x1c,   // 0x58
    EfiKeyOne,        // '1',    '1',    0x02,   // 0x59
    EfiKeyTwo,        // '2',    '2',    0x03,   // 0x5A
    EfiKeyThree,      // '3',    '3',    0x04,   // 0x5B
    EfiKeyFour,       // '4',    '4',    0x05,   // 0x5C
    EfiKeyFive,       // '5',    '5',    0x06,   // 0x5D
    EfiKeySix,        // '6',    '6',    0x07,   // 0x5E
    EfiKeySeven,      // '7',    '7',    0x08,   // 0x5F
    EfiKeyEight,      // '8',    '8',    0x09,   // 0x60
    EfiKeyNine,       // '9',    '9',    0x0a,   // 0x61
    EfiKeyZero,       // '0',    '0',    0x0b,   // 0x62
    EfiKeyPeriod,     // '.',    '.',    0x53,   // 0x63
    EfiKeyD13,        // '\\',   '|',    0x2b,   // 0x64 Keyboard Non-US \ and |
    0,               // 0x00,    0x00,   0x00,   // 0x65 Keyboard Application
    0,               // 0x00,    0x00,   0x00,   // 0x66 Keyboard Power
    0,               // '=' ,    '=',    0x0d    // 0x67 Keypad =

    0,              // 0x00,   0x00,   0x08,   // 0x68 F13
    0,              // 0x00,   0x00,   0x10,   // 0x69 F14
    0,              // 0x00,   0x00,   0x18,   // 0x6A F15
    0,              // 0x00,   0x00,   0x20,   // 0x6B F16
    0,              // 0x00,   0x00,   0x28,   // 0x6C F17
    0,              // 0x00,   0x00,   0x30,   // 0x6D F18
    0,              // 0x00,   0x00,   0x38,   // 0x6E F19
    0,              // 0x00,   0x00,   0x40,   // 0x6F F20
    0,              // 0x00,   0x00,   0x48,   // 0x70 F21
    0,              // 0x00,   0x00,   0x50,   // 0x71 F22
    0,              // 0x00,   0x00,   0x57,   // 0x72 F23
    0,              // 0x00,   0x00,   0x5F,   // 0x73 F24

    0,             // 0x00,   0x00,   0x00,   // 0x74
    0,             // 0x00,   0x00,   0x00,   // 0x75
    0,             // 0x00,   0x00,   0x00,   // 0x76
    0,             // 0x00,   0x00,   0x00,   // 0x77
    0,             // 0x00,   0x00,   0x00,   // 0x78
    0,             // 0x00,   0x00,   0x00,   // 0x79
    0,             // 0x00,   0x00,   0x00,   // 0x7A
    0,             // 0x00,   0x00,   0x00,   // 0x7B
    0,             // 0x00,   0x00,   0x00,   // 0x7C
    0,             // 0x00,   0x00,   0x00,   // 0x7D
    0,             // 0x00,   0x00,   0x00,   // 0x7E
    0,             // 0x00,   0x00,   0x00,   // 0x7F
    0,             // 0x00,   0x00,   0x00,   // 0x80
    0,             // 0x00,   0x00,   0x00,   // 0x81
    0,             // 0x00,   0x00,   0x00,   // 0x82
    0,             // 0x00,   0x00,   0x00,   // 0x83
    0,             // 0x00,   0x00,   0x00,   // 0x84
    0,             // '.',    0x00,   0x6D,   // 0x85
    0,             // '=',    0x00,   0x00,   // 0x86
    EfiKeyB0,             // 0x00,   0x00,   0x51,   // 0x87
    0,             // '\\',   0x00,   0x13,   // 0x88
    EfiKeyD13,      // 0xA5,   0x00,   0x6A,   // 0x89 Yen Symbol
};


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdGetControllerName
//
// Description: USB EFI keyboard driver driver protocol function that
//              returns the keyboard controller name.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16*
UsbKbdGetControllerName(
    EFI_HANDLE Controller,
    EFI_HANDLE Child
)
{
    return NULL;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitUSBKeyboard
//
// Description: Initialize USB Keyboard device and all private data structures.
//
// Input:       None
//
// Output:      EFI_SUCCESS or EFI_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitUSBKeyboard()
{
    InitUSBKeyBuffer(&(gUsbKeyboardData->KeyboardBuffer));
    InitUSBKeyCharBuffer();
    gUsbData->EfiKeyboardBuffer = &gUsbKeyboardData->KeyboardBuffer;

    gUsbKeyboardData->LeftCtrlOn     = 0;
    gUsbKeyboardData->LeftAltOn      = 0;
    gUsbKeyboardData->LeftShiftOn    = 0;
    gUsbKeyboardData->RightCtrlOn     = 0;
    gUsbKeyboardData->RightAltOn     = 0;
    gUsbKeyboardData->RightShiftOn   = 0;
    gUsbKeyboardData->SysRqOn        = 0;
    gUsbKeyboardData->MenuOn         = 0;
    gUsbKeyboardData->LeftLogoOn     = 0;
    gUsbKeyboardData->RightLogoOn    = 0;
    gUsbKeyboardData->NumLockOn  = 0;
    gUsbKeyboardData->CapsOn     = 0;
    gUsbKeyboardData->ScrLkOn    = 0;
                                        //(EIP91889-)>
//	    gUsbKeyboardData->ToggleState =0;
//	    SetKeyLED();
                                        //<(EIP91889-)
    gBS->SetMem(gUsbKeyboardData->LastKeyCodeArray, sizeof(UINT8)*8, 0);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        KeypressCallback
//
// Description: This routine is called every time the keyboard data is updated
//
// Input:      HcStruc, DevInfo, fpBuf2 always NULL
//             Buf1  - Pointer to 8 bytes USB data array
//
// Output:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
KeypressCallback(
    HC_STRUC* HcStruc,
    DEV_INFO* DevInfo,
    UINT8* Buf1,
    UINT8* Buf2)

{

    UINT8       *CurKeyCodeBuffer;
    UINT8       *OldKeyCodeBuffer;
    UINT8       CurModifierMap;
    UINT8       OldModifierMap;
    UINT8       i;
    UINT8       j;
    BOOLEAN     Down;
    BOOLEAN     KeyRelease,KeyPress;
    UINT8       SavedTail;
    USB_KEY     UsbKey;
    UINT8       NewRepeatKey = 0;
    UINT8       *fPtr, *fPtrEnd;

    OldKeyCodeBuffer = gUsbKeyboardData->LastKeyCodeArray;

    if(gUsbData->aKBCUsbDataBufferHead == gUsbData->aKBCUsbDataBufferTail) {
        return EFI_SUCCESS;
    }

    fPtrEnd = gUsbData->aKBCUsbDataBufferStart +
                sizeof (gUsbData->aKBCUsbDataBufferStart);

    fPtr = gUsbData->aKBCUsbDataBufferTail;
    CurKeyCodeBuffer = fPtr;
    fPtr+=8;

    //
    // Check for buffer end condition
    //
    if(fPtr >= fPtrEnd)
        fPtr = gUsbData->aKBCUsbDataBufferStart;
    gUsbData->aKBCUsbDataBufferTail = fPtr;

    //
    // checks for new key stroke.
    // if no new key got, return immediately.
    //
    for (i = 0; i < 8; i ++) {
        if(OldKeyCodeBuffer[i] != CurKeyCodeBuffer[i]) {
            break;
        }
    }

    if(i == 8) {
        return EFI_SUCCESS;
    }

    //
    // Parse the modifier key
    //
    CurModifierMap = CurKeyCodeBuffer[0];
    OldModifierMap = OldKeyCodeBuffer[0];

    //
    // handle modifier key's pressing or releasing situation.
    //
    for (i = 0; i < 8; i ++) {
        if ((CurModifierMap & KB_Mod[i].Mask) !=
                (OldModifierMap & KB_Mod[i].Mask)) {
            //
            // if current modifier key is up, then
            // CurModifierMap & KB_Mod[i].Mask = 0;
            // otherwize it is a non-zero value.
            // Inserts the pressed modifier key into key buffer.
            //
            Down = (UINT8)(CurModifierMap & KB_Mod[i].Mask);
            InsertKeyCode(&(gUsbKeyboardData->KeyboardBuffer),KB_Mod[i].Key,Down);
        }
    }

    //
    // handle normal key's releasing situation
    //
    KeyRelease = FALSE;
    for (i = 2; i < 8; i ++) {

        if(!USBKBD_VALID_KEYCODE(OldKeyCodeBuffer[i])) {
            continue;
        }

        KeyRelease = TRUE;
        for (j = 2; j < 8; j ++) {

            if(!USBKBD_VALID_KEYCODE(CurKeyCodeBuffer[j])) {
                continue;
            }

            if (OldKeyCodeBuffer[i] == CurKeyCodeBuffer[j]) {
                KeyRelease = FALSE;
                break;
            }
        }

        if (KeyRelease) {
            InsertKeyCode(&(gUsbKeyboardData->KeyboardBuffer),OldKeyCodeBuffer[i],0);
            //
            // the original reapeat key is released.
            //
            if (OldKeyCodeBuffer[i] == gUsbData->RepeatKey) {
                gUsbData->RepeatKey = 0;
            }
        }
    }
    //
    // handle normal key's pressing situation
    //
    KeyPress = FALSE;
    for (i = 2; i < 8; i ++) {
        if(!USBKBD_VALID_KEYCODE(CurKeyCodeBuffer[i])) {
            continue;
        }

        KeyPress = TRUE;
        for (j = 2; j < 8; j ++) {
            if(!USBKBD_VALID_KEYCODE(OldKeyCodeBuffer[j])) {
                continue;
            }

            if (CurKeyCodeBuffer[i] == OldKeyCodeBuffer[j]) {
                KeyPress = FALSE;
                break;
            }
        }

        if(KeyPress) {
            InsertKeyCode(&(gUsbKeyboardData->KeyboardBuffer),CurKeyCodeBuffer[i],1);
            //
            // NumLock, ScrollLock or CapsLock pressed
            //
            if(CurKeyCodeBuffer[i] == 0x53 ||
                CurKeyCodeBuffer[i] == 0x47 ||
                    CurKeyCodeBuffer[i] == 0x39) {
                gUsbData->RepeatKey = 0;
            }
            else
            {
                NewRepeatKey = CurKeyCodeBuffer[i];
                //
                // do not repeat the original repeated key
                //
                gUsbData->RepeatKey = 0;
            }
        }
    }

    //
    // Update LastKeycodeArray[] buffer in the
    // Usb Keyboard Device data structure.
    //
    for (i = 0; i < 8; i ++) {
        gUsbKeyboardData->LastKeyCodeArray[i] = CurKeyCodeBuffer[i];
    }

    //
    // pre-process KeyboardBuffer, pop out the ctrl,alt,del key in sequence
    // and judge whether it will invoke reset event.
    //
    SavedTail = gUsbKeyboardData->KeyboardBuffer.bTail;
    i = gUsbKeyboardData->KeyboardBuffer.bHead;
    KeyProcessed=FALSE;
    while(i != SavedTail) {
        RemoveKeyCode(&(gUsbKeyboardData->KeyboardBuffer),&UsbKey);
                                        //(EIP84455+)>
        switch(UsbKey.KeyCode) {
            case 0xe0:
                if(UsbKey.Down) 
                    gUsbKeyboardData->LeftCtrlOn = 1;
                break;

            case 0xe4:
                if(UsbKey.Down) 
                    gUsbKeyboardData->RightCtrlOn = 1;
                break;

            case 0xe2:
               if(UsbKey.Down) 
                    gUsbKeyboardData->LeftAltOn = 1;
                break;
            case 0xe6:
                if(UsbKey.Down) 
                    gUsbKeyboardData->RightAltOn = 1;
                break;
                                        //<(EIP84455+)
            case 0x4c:      // Del Key Code
            case 0x63:
                if(UsbKey.Down) {
                    if((gUsbKeyboardData->LeftCtrlOn | gUsbKeyboardData->RightCtrlOn)  && (gUsbKeyboardData->LeftAltOn | gUsbKeyboardData->RightAltOn)) {
                    	gRT->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
                    }
                }
                break;

            default:
                break;
        }

        //
        // insert the key back to the buffer.
        // so the key sequence will not be destroyed.
        //
        InsertKeyCode(&(gUsbKeyboardData->KeyboardBuffer),
                UsbKey.KeyCode,
                UsbKey.Down);

        i = gUsbKeyboardData->KeyboardBuffer.bHead;

    }
    KeyProcessed=TRUE;
    //
    // If have new key pressed, update the RepeatKey value
    //
    if(NewRepeatKey != 0) {
        gUsbData->RepeatKey = NewRepeatKey;
    }

    return  EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        KeyrepeatCallback
//
// Description: This routine is called every time the key repeat is requested
//
// Input:       All input pointers are NULL, need them for callback function
//              parameters list
//
// Output:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
KeyrepeatCallback(
  HC_STRUC* HcStruc,
  DEV_INFO* DevInfo,
  UINT8* Buf1,
  UINT8* Buf2)

{
    //
    // Do nothing when there is no repeat key.
    //
    if(gUsbData->RepeatKey) {
        //
        // Inserts one Repeat key into keyboard buffer,
        //
        InsertKeyCode(
        &(gUsbKeyboardData->KeyboardBuffer),
        gUsbData->RepeatKey,
        1
        );
    }
    return USB_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBParseKey
//
// Description: Retrieves a key character after parsing the raw data
//              in keyboard buffer.
//
// Input:       KeyChar - pointer to the key character after key parsing.
//
// Output:      USB_SUCCESS or USB_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS USBParseKey (
  UINT8 *KeyChar)
{
    USB_KEY UsbKey;

    *KeyChar = 0;

    while (!IsUSBKeyboardBufferEmpty(&(gUsbKeyboardData->KeyboardBuffer))) {	//(EIP83295)
        //
        // pops one raw data off.
        //
        RemoveKeyCode(&(gUsbKeyboardData->KeyboardBuffer),&UsbKey);

        //
        // Key Release
        //
        if (!UsbKey.Down) {
            switch(UsbKey.KeyCode) {
                case 0xe0:  // fall through
                    gUsbKeyboardData->LeftCtrlOn = 0;
                    break;

                case 0xe4:
                    gUsbKeyboardData->RightCtrlOn = 0;
                    break;

                case 0xe1:  // fall through
                    gUsbKeyboardData->LeftShiftOn = 0;
                    break;
                case 0xe5:
                    gUsbKeyboardData->RightShiftOn = 0;
                    break;

                case 0xe2:  // fall through
                    gUsbKeyboardData->LeftAltOn = 0;
                    break;
                case 0xe6:
                    gUsbKeyboardData->RightAltOn = 0;
                    break;

                case 0xe3:  // fall through
                    gUsbKeyboardData->LeftLogoOn = 0;
                    break;
                case 0xe7:
                    gUsbKeyboardData->RightLogoOn = 0;
                    break;

                case 0x46:
                    gUsbKeyboardData->SysRqOn = 0;
                    break;

                case 0x65:
                    gUsbKeyboardData->MenuOn = 0;
                    break;

                default:
                    break;
                }
            continue;
        }

        //
        // Analyzes key pressing situation
        //
        switch (UsbKey.KeyCode) {
            case 0xe0:  // fall through
                gUsbKeyboardData->LeftCtrlOn = 1;
                continue;
            case 0xe4:
                gUsbKeyboardData->RightCtrlOn = 1;
                continue;

            case 0xe1:  // fall through
                gUsbKeyboardData->LeftShiftOn = 1;
                continue;
            case 0xe5:
                gUsbKeyboardData->RightShiftOn = 1;
                continue;

            case 0xe2:  // fall through
                gUsbKeyboardData->LeftAltOn = 1;
                continue;
            case 0xe6:
                gUsbKeyboardData->RightAltOn = 1;
                continue;

            case 0xe3:  // fall through
                gUsbKeyboardData->LeftLogoOn = 1;
                continue;
            case 0xe7:
                gUsbKeyboardData->RightLogoOn = 1;
                continue;
            //
            // SysRq Key
            //
            case 0x46:
                gUsbKeyboardData->SysRqOn = 1;
                continue;
            //
            // Menu Key
            //
            case 0x65:
                gUsbKeyboardData->MenuOn = 1;
                continue;

            case 0x53:
                gUsbKeyboardData->NumLockOn ^= 1;
                SetKeyLED();
                break;

            case 0x39:
                gUsbKeyboardData->CapsOn ^= 1;
                SetKeyLED();
                break;

            case 0x47:
                gUsbKeyboardData->ScrLkOn ^= 1;
                SetKeyLED();
                break;

            //
            // PrintScreen,ScrollLock,Pause,Application,Power
            // keys are not valid EFI key
            //
            case 0x66:
                continue;

            default:
                break;
        }

        //
        // When encountered Del Key...
        //
        if (UsbKey.KeyCode == 0x4c || UsbKey.KeyCode == 0x63) {
            if((gUsbKeyboardData->LeftCtrlOn | gUsbKeyboardData->RightCtrlOn)  && (gUsbKeyboardData->LeftAltOn | gUsbKeyboardData->RightAltOn)) {
                gRT->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
            }
        }

        *KeyChar = UsbKey.KeyCode;
        return EFI_SUCCESS;
    }

    return EFI_NOT_READY;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        USBKeyCodeToEFIScanCode
//
// Description: Converts USB Keyboard code to EFI Scan Code
//
// Input:       KeyChar - Indicates the key code that will be interpreted.
//              Key     - A pointer to a buffer that is filled in with
//                          the keystroke information for the key that
//                          was pressed.
//
// Output:      EFI_SUCCESS, EFI_NOT_READY
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBKeyCodeToEFIScanCode(
    UINT8           KeyChar,
    EFI_INPUT_KEY   *Key
)
{
    UINT8 Index;

    if (!USBKBD_VALID_KEYCODE(KeyChar)) {
        return EFI_NOT_READY;
    }

    //
    // valid USB Key Code starts from 4
    //
    Index = (UINT8)(KeyChar - 4);

    if (Index >= USB_KEYCODE_MAX_MAKE){
        return EFI_NOT_READY;
    }

    Key->ScanCode = KeyConvertionTable[Index][0];

    if (gUsbKeyboardData->LeftShiftOn || gUsbKeyboardData->RightShiftOn) {

        Key->UnicodeChar = KeyConvertionTable[Index][2];

    } else {

        Key->UnicodeChar = KeyConvertionTable[Index][1];
    }

    if ((gUsbKeyboardData->NumLockOn == 0) && gUsbKeyboardData->LeftShiftOn == 0 && gUsbKeyboardData->RightShiftOn == 0 && (Index == 0x5d-4)) {
        Key->UnicodeChar = 0;
    }

    if (gUsbKeyboardData->CapsOn) {

        if (Key->UnicodeChar >= 'a' && Key->UnicodeChar <= 'z') {

            Key->UnicodeChar = KeyConvertionTable[Index][2];

        } else if (Key->UnicodeChar >= 'A' && Key->UnicodeChar <= 'Z') {

            Key->UnicodeChar = KeyConvertionTable[Index][1];

        }
    }

    if (KeyChar >= 0x59 && KeyChar <=0x63 && Key->ScanCode != SCAN_NULL) {

        if (gUsbKeyboardData->NumLockOn && !(gUsbKeyboardData->LeftShiftOn | gUsbKeyboardData->RightShiftOn)) {

            Key->ScanCode = SCAN_NULL;

        } else {

            Key->UnicodeChar = 0x00;
        }
    }
    //
    // CapsLock, NumLock and ScrLock must be reported as valid keys even though their
    // ScanCode and UnicodeChar are zeroes
    //
//    if (KeyChar == 0x53 || KeyChar == 0x39 || KeyChar == 0x47 ) return EFI_SUCCESS;

    if (KeyChar == 0x53 || KeyChar == 0x39 || KeyChar == 0x47 || KeyChar == 0x48 ) {
        return EFI_SUCCESS;
    }

    if(Key->UnicodeChar == 0 && Key->ScanCode == SCAN_NULL) {
        return EFI_NOT_READY;
    }

    return EFI_SUCCESS;

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitUSBKeyBuffer
//
// Description: Initialize USB Keyboard Buffer.
//
// Input:       None
//
// Output:      EFI_SUCCESS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitUSBKeyBuffer(USB_KB_BUFFER *KeyboardBuffer)
{
    EfiZeroMem(KeyboardBuffer,sizeof(USB_KB_BUFFER));

    KeyboardBuffer->bHead = KeyboardBuffer->bTail;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        IsUSBKeyboardBufferEmpty
//
// Description: Check whether USB Keyboard buffer is empty.
//
// Input:       KeyboardBuffer  - pointer to USB Keyboard Buffer.
//
// Output:      TRUE if buffer is empty, FALSE otherwise
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
										//(EIP83295)>
BOOLEAN
IsUSBKeyboardBufferEmpty(USB_KB_BUFFER *KeyboardBuffer)
{
    //
    // meet FIFO empty condition
    //
    return (BOOLEAN)(KeyboardBuffer->bHead == KeyboardBuffer->bTail);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        IsUSBKeyboardBufferFull
//
// Description: Check whether USB Keyboard buffer is full.
//
// Input:       KeyboardBuffer  - pointer to USB Keyboard Buffer.
//
// Output:      TRUE if buffer is full, FALSE otherwise
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
IsUSBKeyboardBufferFull(USB_KB_BUFFER   *KeyboardBuffer)
{
    return (BOOLEAN)(((KeyboardBuffer->bTail + 1) % (MAX_KEY_ALLOWED + 1)) ==
                            KeyboardBuffer->bHead);
}
										//<(EIP83295)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InsertKeyCode
//
// Description: Inserts a key code into keyboard buffer.
//
// Input:       KeyboardBuffer  - pointer to USB Keyboard Buffer.
//
// Output:      EFI_SUCCESS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InsertKeyCode(
    USB_KB_BUFFER   *KeyboardBuffer,
    UINT8           Key,
    UINT8           Down
  )
{
    USB_KEY         UsbKey;

    if(KeyProcessed && Down) {
        UsbCheckKeyNotify(Key);
    }

    //
    // if keyboard buffer is full, throw the
    // first key out of the keyboard buffer.
    //
    if (IsUSBKeyboardBufferFull (KeyboardBuffer)) {	//(EIP83295)
        RemoveKeyCode(KeyboardBuffer,&UsbKey);
    }

    KeyboardBuffer->buffer[KeyboardBuffer->bTail].KeyCode = Key;
    KeyboardBuffer->buffer[KeyboardBuffer->bTail].Down = Down;

    //
    // adjust the tail pointer of the FIFO keyboard buffer.
    //
    KeyboardBuffer->bTail = (UINT8)((KeyboardBuffer->bTail + 1)
                % (MAX_KEY_ALLOWED + 1)) ;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        RemoveKeyCode
//
// Description: Removes a key code from the keyboard buffer.
//
// Input:       KeyboardBuffer  - pointer to USB Keyboard Buffer.
//              UsbKey          - pointer to buffer that contains usb key code.
//
// Output:      EFI_SUCCESS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveKeyCode(
    USB_KB_BUFFER *KeyboardBuffer,
    USB_KEY       *UsbKey
)
{
    if (IsUSBKeyboardBufferEmpty (KeyboardBuffer)) {	//(EIP83295)
        return EFI_DEVICE_ERROR;
    }

    UsbKey->KeyCode = KeyboardBuffer->buffer[KeyboardBuffer->bHead].KeyCode;
    UsbKey->Down = KeyboardBuffer->buffer[KeyboardBuffer->bHead].Down;

    //
    // adjust the head pointer of the FIFO keyboard buffer.
    //
    KeyboardBuffer->bHead = (UINT8)((KeyboardBuffer->bHead + 1) %
                        (MAX_KEY_ALLOWED + 1)) ;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitUSBKeyCharBuffer
//
// Description: Initialize USB Keyboard Buffer for Keyboard ASCII data.
//
// Input:       None
//
// Output:      EFI_SUCCESS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitUSBKeyCharBuffer()
{
    EfiZeroMem((VOID*)&(gUsbKeyboardData->KeyChar[0]),sizeof(UINT8) * MAX_KEY_ALLOWED + 1 );

    gUsbKeyboardData->bHead = gUsbKeyboardData->bTail;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        IsUSBKeyCharEmpty
//
// Description: Check whether USB Keyboard ASCII data buffer is empty.
//
// Input:       None
//
// Output:      TRUE if buffer is empty, FALSE otherwise
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
IsUSBKeyCharEmpty()
{
    //
    // meet FIFO empty condition
    //
    return (BOOLEAN)(gUsbKeyboardData->bHead == gUsbKeyboardData->bTail);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        IsUSBKeyboardBufferFull
//
// Description: Check whether USB Keyboard ASCII data buffer is full.
//
// Input:       None
//
// Output:      TRUE if buffer is full, FALSE otherwise
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
IsUSBKeyCharFull()
{
    return (BOOLEAN)(((gUsbKeyboardData->bTail + 1) % (MAX_KEY_ALLOWED + 1)) ==
                            gUsbKeyboardData->bHead);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InsertKeyCode
//
// Description: Inserts a USB Keyboard ASCII data into keyboard buffer.
//
// Input:       UINT8   KeyChar - USB Key Data
//
// Output:      EFI_SUCCESS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InsertKeyChar(
    UINT8           KeyChar
  )
{
    UINT8         TempKey;

    //
    // if keyboard buffer is full, throw the
    // first key out of the keyboard buffer.
    //
    if (IsUSBKeyCharFull()) {
        RemoveKeyChar(&TempKey);
    }

    gUsbKeyboardData->KeyChar[gUsbKeyboardData->bTail] = KeyChar;

    //
    // adjust the tail pointer of the FIFO keyboard buffer.
    //
    gUsbKeyboardData->bTail = (UINT8)((gUsbKeyboardData->bTail + 1)
                % (MAX_KEY_ALLOWED + 1)) ;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        RemoveKeyCode
//
// Description: Removes a USB Keyboard ASCII data from the keyboard buffer.
//
// Input:       UINT8   KeyChar - USB Keyboard Data
//
// Output:      EFI_SUCCESS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveKeyChar(
    UINT8       *KeyChar
)
{
    if (IsUSBKeyCharEmpty()) {
        return EFI_DEVICE_ERROR;
    }

    *KeyChar = gUsbKeyboardData->KeyChar[gUsbKeyboardData->bHead];

    //
    // adjust the head pointer of the FIFO keyboard buffer.
    //
    gUsbKeyboardData->bHead = (UINT8)((gUsbKeyboardData->bHead + 1) %
                        (MAX_KEY_ALLOWED + 1)) ;

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        SetKeyLED
//
// Description: Sets USB Keyboard LED state.
//
// Input:       None
//
// Output:      EFI_SUCCESS
//
// Notes:       UsbKbd can be NULL; in this case LEDs on all keyboards will
//              be refreshed. This is useful when the new keyboard is connected
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SetKeyLED()
{
    LED_MAP         Led;
    URP_STRUC       Urp;    // USB Request Packet

    //
    // Set each field in Led map.
    //
    if (gUsbKeyboardData)
    {
        Led.NumLock = (UINT8)gUsbKeyboardData->NumLockOn;
        Led.CapsLock = (UINT8)gUsbKeyboardData->CapsOn;
        Led.ScrLock = (UINT8)gUsbKeyboardData->ScrLkOn;
        Led.Resrvd = 0;
        Urp.ApiData.KbLedsData.fpLedMap = (UINT32)(UINTN)&Led;
    }
    else
    {
        Urp.ApiData.KbLedsData.fpLedMap = 0;
    }
    //
    // Lighten up LEDs.
    //
    Urp.bFuncNumber         = USB_API_LIGHTEN_KEYBOARD_LEDS;
    Urp.bSubFunc            = 0;

	InvokeUsbApi(&Urp);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:      SupportedUSBKeyboard
//
// Description: Verifies if usb keyboard support can be installed on a device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SupportedUSBKeyboard(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath)
{
    EFI_USB_INTERFACE_DESCRIPTOR    Desc;
    EFI_STATUS                      Status;
    EFI_USB_IO_PROTOCOL             *UsbIo;

    Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
        &UsbIo, This->DriverBindingHandle,
        Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL );
    if( EFI_ERROR(Status))
        return Status;

    Status = UsbIo->UsbGetInterfaceDescriptor(UsbIo, &Desc  );
    if(EFI_ERROR(Status))
        return EFI_UNSUPPORTED;

    if ( Desc.InterfaceClass == BASE_CLASS_HID &&
        Desc.InterfaceSubClass == SUB_CLASS_BOOT_DEVICE &&
        Desc.InterfaceProtocol == PROTOCOL_KEYBOARD)
    {
        return EFI_SUCCESS;
    } else {
        return EFI_UNSUPPORTED;
    }
}

#if CLEAR_USB_KB_BUFFER_AT_READYTOBOOT
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ClearUsbKbBuffer
//
// Description:
//  This function clear USB KB buffers
//
// Input:   
//  IN EFI_EVENT	Event - signalled event
//  IN VOID 		*Context - pointer to event context
//
// Output:
//      VOID
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS
ClearUsbKbBuffer(
    IN EFI_EVENT	Event, 
    IN VOID 		*Context
)
{
    InitUSBKeyBuffer(&(gUsbKeyboardData->KeyboardBuffer));
    gUsbKeyboardData->CurKeyChar = 0;

	// Clear KB buffers in USB_GLOBAL_DATA
    EfiZeroMem(gUsbData->aKBCCharacterBufferStart, 128);
	gUsbData->fpKBCCharacterBufferHead = gUsbData->aKBCCharacterBufferStart;
	gUsbData->fpKBCCharacterBufferTail = gUsbData->aKBCCharacterBufferStart;

    EfiZeroMem(gUsbData->aKBCScanCodeBufferStart, 16);
    gUsbData->fpKBCScanCodeBufferPtr = gUsbData->aKBCScanCodeBufferStart;

    EfiZeroMem(gUsbData->aKBCUsbDataBufferStart, 32);
    gUsbData->aKBCUsbDataBufferHead = gUsbData->aKBCUsbDataBufferStart;
    gUsbData->aKBCUsbDataBufferTail = gUsbData->aKBCUsbDataBufferStart;

    EfiZeroMem(gUsbData->aKBInputBuffer, 16);

	pBS->CloseEvent(Event);

    return EFI_SUCCESS;
}
#endif


										//(EIP38434+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InstallUSBKeyboard
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
InstallUSBKeyboard(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
	DEV_INFO*       			Dev_info,			
    EFI_USB_IO_PROTOCOL     	*UsbIo 
)
{
    EFI_STATUS              Status;
    USB_KB_DEV*             UsbKbd;

    USB_DEBUG(DEBUG_USBHC_LEVEL,
        "USB: InstallUSBKeyboard: starting...\n");

    VERIFY_EFI_ERROR(
        Status = gBS->AllocatePool( EfiBootServicesData,
        sizeof(USB_KB_DEV), &UsbKbd ));
    EfiZeroMem(UsbKbd, sizeof(USB_KB_DEV));
      
    UsbKbd->dev_info = Dev_info;  
    //
    // Initialize UsbKbd
    //
    ASSERT_EFI_ERROR(Status);

    UsbKbd->io = UsbIo;
    UsbKbd->Signature = USB_KB_DEV_SIGNATURE;
    UsbKbd->SimpleInput.Reset = UsbKbdReset;
    UsbKbd->SimpleInput.ReadKeyStroke = UsbKbdReadKeyStroke;

#if (CORE_REVISION >= 0x3)
    UsbKbd->SimpleInputEx.Reset = UsbKbdResetEx;
    UsbKbd->SimpleInputEx.ReadKeyStrokeEx = UsbKbdReadKeyStrokeEx;
    UsbKbd->SimpleInputEx.SetState = UsbKbdSetState;
    UsbKbd->SimpleInputEx.RegisterKeyNotify = UsbKbdRegisterKeyNotify;
    UsbKbd->SimpleInputEx.UnregisterKeyNotify = UsbKbdUnregisterKeyNotify;

    UsbKbd->KeycodeInput.Reset = UsbKbdResetEx;
    UsbKbd->KeycodeInput.ReadEfikey = UsbKbdReadEfiKey;
    UsbKbd->KeycodeInput.SetState = UsbKbdSetState;
    UsbKbd->KeycodeInput.RegisterKeyNotify = UsbKbdRegisterKeyNotify;
    UsbKbd->KeycodeInput.UnregisterKeyNotify = UsbKbdUnregisterKeyNotify;

    VERIFY_EFI_ERROR(
        Status = gBS->CreateEvent (
                EFI_EVENT_NOTIFY_WAIT,
                EFI_TPL_NOTIFY,
                UsbKbdWaitForKey,
                UsbKbd,
                &UsbKbd->SimpleInputEx.WaitForKeyEx));

    VERIFY_EFI_ERROR(
        Status = gBS->CreateEvent (
                EFI_EVENT_NOTIFY_WAIT,
                EFI_TPL_NOTIFY,
                UsbKbdWaitForKey,
                UsbKbd,
                &UsbKbd->KeycodeInput.WaitForKeyEx));

#endif

#if CLEAR_USB_KB_BUFFER_AT_READYTOBOOT
    // Create event on ready to boot to clear KB buffer
    VERIFY_EFI_ERROR(
	    Status = pBS->CreateEvent(
	            EFI_EVENT_SIGNAL_READY_TO_BOOT,
	            TPL_NOTIFY,
	            ClearUsbKbBuffer,
	            NULL,
	            &gClearUsbKbBufferEvent));
#endif

    // Setup the WaitForKey event
    //
    VERIFY_EFI_ERROR(
        Status = gBS->CreateEvent (
                EFI_EVENT_NOTIFY_WAIT,
                EFI_TPL_NOTIFY,
                UsbKbdWaitForKey,
                UsbKbd,
                &UsbKbd->SimpleInput.WaitForKey));

    //
    // Install protocol interfaces for the USB keyboard device:
    //
    // Install simple txt in protocol interface
    // for the usb keyboard device.
    // Usb keyboard is a hot plug device, and expected to work immediately
    // when plugging into system, so a HotPlugDeviceGuid is installed onto
    // the usb keyboard device handle, to distinguish it from other conventional
    // console devices.
    //
    Status = gBS->InstallMultipleProtocolInterfaces (&Controller,
                &gEfiHotPlugDeviceGuid, NULL,
                &gEfiSimpleTextInProtocolGuid,&UsbKbd->SimpleInput,
#if (CORE_REVISION >= 0x3)
                &gEfiSimpleTextInExProtocolGuid,&UsbKbd->SimpleInputEx,
                &gAmiEfiKeycodeProtocolGuid,&UsbKbd->KeycodeInput,
#endif
                NULL
                );

    ASSERT_EFI_ERROR (Status);

    USB_DEBUG(DEBUG_USBHC_LEVEL,
        "USB: InstallUSBKeyboard: done (%x).\n", Status);

    SetKeyLED();

    return Status;
}
										//<(EIP38434+)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UninstallUSBKeyboard
//
// Description: Uninstalls SimpleTxtIn protocol on a given handle
//
// Input:       Controller - controller handle.
//
// Output:      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UninstallUSBKeyboard(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
)
{
    EFI_STATUS      Status;
    USB_KB_DEV*     UsbKbd=0;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *SimpleIn;
    DLINK               *ListPtr  = NULL;   //(EIP100370+)
    KEY_WAITING_RECORD  *UsbKeyIn = NULL;   //(EIP100370+)
    

    Status = pBS->OpenProtocol( Controller,
                                &gEfiSimpleTextInProtocolGuid,
                                (VOID **)&SimpleIn,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);

   
    UsbKbd = USB_KB_DEV_FROM_THIS(SimpleIn, SimpleInput);

                                        //(EIP100370+)>
#if (CORE_REVISION >= 0x3)
    ListPtr = mUsbKeyboardData.pHead;
    while (ListPtr != NULL) {
        UsbKeyIn = OUTTER(ListPtr, Link, KEY_WAITING_RECORD);
		ListPtr = ListPtr->pNext;
        if (UsbKbd == UsbKeyIn->UsbKbDev) {
			DListDelete(&mUsbKeyboardData, &UsbKeyIn->Link);
            pBS->FreePool(UsbKeyIn);
        }
    }

	if (mUsbKeyboardData.Size == 0) {
		pBS->SetTimer(UsbKeyEvent,
						TimerCancel,
						0);
	}
#endif
                                        //<(EIP100370+)
    
    //
    // Uninstall protocol interfaces for the USB keyboard device
    //
    Status = gBS->UninstallMultipleProtocolInterfaces ( Controller,
                &gEfiHotPlugDeviceGuid, NULL,
                &gEfiSimpleTextInProtocolGuid, &UsbKbd->SimpleInput,
#if (CORE_REVISION >= 0x3)
                &gEfiSimpleTextInExProtocolGuid,&UsbKbd->SimpleInputEx,
                &gAmiEfiKeycodeProtocolGuid,&UsbKbd->KeycodeInput,
#endif
                NULL);

    if (EFI_ERROR(Status)) {
        return Status;
    }
										//(EIP38434+)>
//	    VERIFY_EFI_ERROR(
//	        gBS->CloseProtocol (
//	        Controller, &gEfiUsbIoProtocolGuid,
//	        This->DriverBindingHandle, Controller));
										//<(EIP38434+)
    //
    // Close the WaitForKey event
    //
    VERIFY_EFI_ERROR(
        gBS->CloseEvent (UsbKbd->SimpleInput.WaitForKey));

#if (CORE_REVISION >= 0x3)
    VERIFY_EFI_ERROR(
        gBS->CloseEvent (UsbKbd->SimpleInputEx.WaitForKeyEx));

    VERIFY_EFI_ERROR(
        gBS->CloseEvent (UsbKbd->KeycodeInput.WaitForKeyEx));
#endif

    VERIFY_EFI_ERROR(
        gBS->FreePool(UsbKbd));

    return Status;
}


/***********************************************************************/
/*                                                                     */
/*            SimpleTextIn Protocol implementation routines            */
/*                                                                     */
/***********************************************************************/

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdReset
//
// Description: Reset USB keyboard
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbKbdReset (
    IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
    IN  BOOLEAN                         ExtendedVerification
)
{
    EFI_STATUS        Status;

    //
    // Non Exhaustive reset: only reset private data structures.
    //
    if(!ExtendedVerification) {
        InitUSBKeyBuffer(&(gUsbKeyboardData->KeyboardBuffer));
        InitUSBKeyCharBuffer();

        return EFI_SUCCESS;
    }

    //
    // Exhaustive reset
    //
    Status = InitUSBKeyboard();
    InitUSBKeyCharBuffer();
    if(EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    return  EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdReadKeyStroke
//
// Description: Retrieves the key stroke from the keyboard buffer.
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbKbdReadKeyStroke (
    IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
    OUT EFI_INPUT_KEY                   *Key
)
{
    EFI_STATUS      Status;

    Status = ReadAndProcessKey(Key, sizeof(EFI_INPUT_KEY));
    if(Key->UnicodeChar == 0 && Key->ScanCode == SCAN_NULL) {
        return EFI_NOT_READY;
    }

    return Status;

}

#if (CORE_REVISION >= 0x3)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdResetEx
//
// Description: Reset USB keyboard
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UsbKbdResetEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN  BOOLEAN                 ExtendedVerification
)
{
    return UsbKbdReset(0, ExtendedVerification);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdReadKeyStrokeEx
//
// Description: Retrieves the key stroke from the keyboard buffer.
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UsbKbdReadKeyStrokeEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  OUT EFI_KEY_DATA *KeyData
)
{

    if(KeyData == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    return ReadAndProcessKey(KeyData, sizeof(EFI_KEY_DATA));
}

EFI_STATUS UsbKbdReadEfiKey(
    IN AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA *KeyData
)
{
    EFI_STATUS Status;

    if(KeyData == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    

    Status = ReadAndProcessKey(KeyData, sizeof(AMI_EFI_KEY_DATA));
    if (Status == EFI_SUCCESS && !(KeyData->KeyState.KeyToggleState & KEY_STATE_EXPOSED)) {
      KeyData->EfiKeyIsValid = 1;
      KeyData->PS2ScanCodeIsValid = 1;
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UsbKbdSetState
//
// Description:     Set certain state for the input device.
//
// Paremeters:      This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
//                          instance.
//                  KeyToggleState - Pointer to the EFI_KEY_TOGGLE_STATE to
//                          set the state for the input device.
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbKbdSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState
)
{
    BOOLEAN ChgSL = FALSE;
    BOOLEAN ChgCL = FALSE;
    BOOLEAN ChgNL = FALSE;

    if(KeyToggleState == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(*KeyToggleState & TOGGLE_STATE_VALID) ||
        ((*KeyToggleState & (~(TOGGLE_STATE_VALID | KEY_STATE_EXPOSED | 
                            SCROLL_LOCK_ACTIVE | NUM_LOCK_ACTIVE | CAPS_LOCK_ACTIVE)))) ) {
        return EFI_UNSUPPORTED;
    }

    //
    // Set the new modifier's state only if the requested state is different from the
    // current one.
    //
    if((UINT8)*KeyToggleState != gUsbKeyboardData->ToggleState){                 //(EIP91889)
	    gUsbKeyboardData->ToggleState = (*KeyToggleState);     //(EIP91889+)
        gUsbKeyboardData->ScrLkOn = (*KeyToggleState & SCROLL_LOCK_ACTIVE)? 1 : 0;
        gUsbKeyboardData->NumLockOn = (*KeyToggleState & NUM_LOCK_ACTIVE)? 1 : 0;
        gUsbKeyboardData->CapsOn = (*KeyToggleState & CAPS_LOCK_ACTIVE)? 1 : 0;

        SetKeyLED();
    }
    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ValidateKeyRecord
//
// Description:     Check for Record is present or Not
//
// Paremeters:      KEY_WAITING_RECORD - *UsbKeyIn
//
// Output:          FALSE - If Record is deleted from list
//                  TRUE  - If Record is present in List
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
ValidateKeyRecord (
    IN KEY_WAITING_RECORD    *UsbKeyIn
)
{
    KEY_WAITING_RECORD *TempRecord = OUTTER(mUsbKeyboardData.pHead, Link, KEY_WAITING_RECORD);

    while ( TempRecord != NULL) {
        if(TempRecord == UsbKeyIn) {
            return TRUE;
        }  
        // go to the next element in the list
        TempRecord = OUTTER(TempRecord->Link.pNext, Link, KEY_WAITING_RECORD);
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CheckKeyNotify
//
// Description:     Call the notification function based on the key pressed
//
// Paremeters:      Key - Key pressed
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UsbCheckKeyNotify(UINT8 KeyChar)
{

    EFI_INPUT_KEY   Key;
    EFI_STATUS      Status;
    KEY_WAITING_RECORD *UsbKeyIn = OUTTER(mUsbKeyboardData.pHead, Link, KEY_WAITING_RECORD);
    BOOLEAN     KeyScanCodeMatch=FALSE;
    BOOLEAN     KeyUniCodeMatch=FALSE;
    BOOLEAN     ShiftKeyMatch=FALSE;
    BOOLEAN     CtrlKeyMatch=FALSE;
    BOOLEAN     AltKeyMatch=FALSE;
    BOOLEAN     LogoKeyMatch=FALSE;
    BOOLEAN     MenuKeyMatch=FALSE;
    BOOLEAN     SysRqKeyMatch=FALSE;
    BOOLEAN     KeyShiftCodeMatch=FALSE;
    BOOLEAN     KeyToggleKeyMatch=FALSE;
    BOOLEAN     CallBackCalled=FALSE;

    // if the list is empty return the status that was passed in
    if (UsbKeyIn == NULL)
        return EFI_SUCCESS;

    EfiZeroMem((VOID*)&Key,sizeof(EFI_INPUT_KEY));

    //
    // Translate saved ASCII byte into EFI_INPUT_KEY and PS/2 Scan Code
    //
    Status = USBKeyCodeToEFIScanCode(KeyChar,&Key);

    // check for a handle that was already identified
    while ( UsbKeyIn != NULL)
    {
        KeyScanCodeMatch=FALSE;
        KeyUniCodeMatch=FALSE;
        ShiftKeyMatch=FALSE;
        CtrlKeyMatch=FALSE;
        AltKeyMatch=FALSE;
        LogoKeyMatch=FALSE;
        MenuKeyMatch=FALSE;
        SysRqKeyMatch=FALSE;
        KeyShiftCodeMatch=FALSE;
        KeyToggleKeyMatch=FALSE;

        //
        // Check the Scan Code if the Scan code is not 0
        //
        if (UsbKeyIn->Context.Key.ScanCode != 0) {
            if( UsbKeyIn->Context.Key.ScanCode == Key.ScanCode) {
                KeyScanCodeMatch=TRUE;
            }
        } else {
            KeyScanCodeMatch=TRUE;
        }

        //
        // Check the Uncide Code Matching
        //

        if(UsbKeyIn->Context.Key.UnicodeChar == Key.UnicodeChar) {
            KeyUniCodeMatch=TRUE;
        }

        if(UsbKeyIn->Context.KeyState.KeyShiftState & SHIFT_STATE_VALID){

            //
            // Check the ShiftKey Matching. Left Shift Key is matched with
            // Left or Right Shift Key. Same for Right Shift Key
            //
            if (UsbKeyIn->Context.KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED)) {
                if(gUsbKeyboardData->LeftShiftOn || gUsbKeyboardData->RightShiftOn) {
                    ShiftKeyMatch=TRUE;
                }
            } else {
                ShiftKeyMatch=TRUE;
            }

            //
            // Check the Ctrl Matching. Left Ctrl Key is matched with
            // Left or Right Ctrl Key. Same for Right Ctrl Key
            //
            if (UsbKeyIn->Context.KeyState.KeyShiftState & (RIGHT_CONTROL_PRESSED | LEFT_CONTROL_PRESSED)) {
                if(gUsbKeyboardData->LeftCtrlOn || gUsbKeyboardData->RightCtrlOn) {
                    CtrlKeyMatch=TRUE;
                }
            } else {
                CtrlKeyMatch=TRUE;
            }

            //
            // Check the Alt Matching. Left Alt Key is matched with
            // Left or Right Alt Key. Same for Right Alt Key
            //
            if (UsbKeyIn->Context.KeyState.KeyShiftState & (RIGHT_ALT_PRESSED | LEFT_ALT_PRESSED)) {
                if(gUsbKeyboardData->LeftAltOn || gUsbKeyboardData->RightAltOn) {
                    AltKeyMatch=TRUE;
                }
            } else {
                AltKeyMatch=TRUE;
            }

            //
            // Check the Logo Matching. Left Logo Key is matched with
            // Left or Right Logo Key. Same for Right Logo Key
            //
            if (UsbKeyIn->Context.KeyState.KeyShiftState & (RIGHT_LOGO_PRESSED | LEFT_LOGO_PRESSED)) {
                if(gUsbKeyboardData->LeftLogoOn || gUsbKeyboardData->RightLogoOn) {
                    LogoKeyMatch=TRUE;
                }
            } else {
                LogoKeyMatch=TRUE;
            }

            //
            // Check the Menu Key Matching
            //
            if (UsbKeyIn->Context.KeyState.KeyShiftState & MENU_KEY_PRESSED) {
                if(gUsbKeyboardData->MenuOn) {
                    MenuKeyMatch=TRUE;
                }
            } else {
                MenuKeyMatch=TRUE;
            }

            //
            // Check the SysRq Key Matching
            //
            if (UsbKeyIn->Context.KeyState.KeyShiftState & SYS_REQ_PRESSED) {
                if(gUsbKeyboardData->SysRqOn) {
                    SysRqKeyMatch=TRUE;
                }
            } else {
                SysRqKeyMatch=TRUE;
            }

            KeyShiftCodeMatch=ShiftKeyMatch & CtrlKeyMatch & AltKeyMatch
                                & LogoKeyMatch & MenuKeyMatch & SysRqKeyMatch;
        }else {
            KeyShiftCodeMatch=TRUE;
        }
        //
        // Check the Key Toggle State
        //
        if(UsbKeyIn->Context.KeyState.KeyToggleState & TOGGLE_STATE_VALID){
            if((UsbKeyIn->Context.KeyState.KeyToggleState & ~KEY_STATE_EXPOSED) ==
               (TOGGLE_STATE_VALID | gUsbKeyboardData->ScrLkOn | gUsbKeyboardData->NumLockOn | gUsbKeyboardData->CapsOn)) {
                KeyToggleKeyMatch=TRUE;
            }
        } else {
            KeyToggleKeyMatch=TRUE;
        }

        //
        // If everything matched, call the callback function.
        //
        if(KeyScanCodeMatch && KeyUniCodeMatch && KeyShiftCodeMatch && KeyToggleKeyMatch && (!UsbKeyIn->CallbackStatus)) {

            //Call the notification function
            UsbKeyIn->CallbackStatus=TRUE;
            CallBackCalled=TRUE;
            UsbKeyIn->Callback(&UsbKeyIn->Context);

            if(ValidateKeyRecord(UsbKeyIn)) {

                // go to the next element in the list
                UsbKeyIn = OUTTER(UsbKeyIn->Link.pNext, Link, KEY_WAITING_RECORD);
            } else {

                // Record deleted. So go to the first element in the list
                UsbKeyIn = OUTTER(mUsbKeyboardData.pHead, Link, KEY_WAITING_RECORD);
            }
            continue;
        }
        // go to the next element in the list
        UsbKeyIn = OUTTER(UsbKeyIn->Link.pNext, Link, KEY_WAITING_RECORD);
    }

    if(CallBackCalled) {
        UsbKeyIn = OUTTER(mUsbKeyboardData.pHead, Link, KEY_WAITING_RECORD);
        while ( UsbKeyIn != NULL) {
            UsbKeyIn->CallbackStatus=FALSE;
            // go to the next element in the list
            UsbKeyIn = OUTTER(UsbKeyIn->Link.pNext, Link, KEY_WAITING_RECORD);
        }
    }

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdRegisterKeyNotify
//
// Description: Installs a callback notification function on a key
//
// Input:           This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
//                          instance.
//                  KeyData - Key value
//                  KeyNotificationFunction- Pointer to the Notification Function
//                  NotificationHandle - Handle to be unregisterd
//
// Output:          None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbKbdRegisterKeyNotify (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT EFI_HANDLE *NotifyHandle
)
{
    EFI_STATUS			Status;
    USB_KB_DEV			*UsbKbd = 0;    //(EIP100370+)
	DLINK				*Link = NULL;
	KEY_WAITING_RECORD	*NotifyLink = NULL;

    if (KeyData == NULL || KeyNotificationFunction == NULL || NotifyHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

	// Check if the key has been reistered
	for (Link = mUsbKeyboardData.pHead; Link != NULL; Link = Link->pNext) {
		NotifyLink = OUTTER(Link, Link, KEY_WAITING_RECORD);
		if (MemCmp(&NotifyLink->Context, KeyData, sizeof(EFI_KEY_DATA)) == 0 &&
			NotifyLink->Callback == KeyNotificationFunction) {
			*NotifyHandle = (EFI_HANDLE)(&NotifyLink->Link);
			return EFI_SUCCESS;
		}
	}

    //
    // Create database record and add to database
    //
    Status = gBS->AllocatePool(
                      EfiBootServicesData,
                      sizeof (KEY_WAITING_RECORD),
                      &mUsbKeyboardRecord
                      );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    UsbKbd = USB_KB_DEV_FROM_THIS (This, SimpleInputEx);    //(EIP100370+)
    //
    // Gather information about the registration request
    //

    mUsbKeyboardRecord->UsbKbDev  = UsbKbd;    //(EIP100370+)
    mUsbKeyboardRecord->Context   = *KeyData;
    mUsbKeyboardRecord->Callback  = KeyNotificationFunction;
    mUsbKeyboardRecord->CallbackStatus = FALSE;

    DListAdd (&mUsbKeyboardData, &(mUsbKeyboardRecord->Link));

    //
    // Child's handle will be the address linked list link in the record
    //
    *NotifyHandle = (EFI_HANDLE) (&mUsbKeyboardRecord->Link);

    if(mUsbKeyboardData.Size == 1) {
        pBS->SetTimer(UsbKeyEvent,
                        TimerPeriodic,
                        KEY_POLLING_INTERVAL);
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdRegisterKeyNotify
//
// Description: Uninstalls a callback notification function on a key
//
// Input:          This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
//                          instance.
//                  NotificationHandle - Handle to be unregisterd
//
// Output:          None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbKbdUnregisterKeyNotify (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
)
{
    DLINK               *ListPtr;
    KEY_WAITING_RECORD  *UsbKeyIn;
    USB_KB_DEV*         UsbKbd = USB_KB_DEV_FROM_THIS (This, SimpleInputEx);	//(EIP100370+)

    if(NotificationHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    ListPtr = mUsbKeyboardData.pHead;
                                        //(EIP100370)>
    while (ListPtr != NULL) {
        UsbKeyIn = OUTTER(ListPtr, Link, KEY_WAITING_RECORD);
        if ((&UsbKeyIn->Link) == NotificationHandle &&
        	 UsbKeyIn->UsbKbDev == UsbKbd) {
            DListDelete(&mUsbKeyboardData, ListPtr);
            pBS->FreePool(UsbKeyIn);
            break;
        }

        ListPtr = ListPtr->pNext;
    }

    if (ListPtr == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (mUsbKeyboardData.Size == 0) {
        pBS->SetTimer(UsbKeyEvent,
                        TimerCancel,
                        0);
    }

    return EFI_SUCCESS;
                                        //<(EIP100370)
}

#endif


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdWaitForKey
//
// Description: Checks if a key is pending, if so - signals the event.
//
// Output:      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
UsbKbdWaitForKey (
    IN  EFI_EVENT   Event,
    IN  VOID        *Context
    )
{
    if(IsUSBKeyCharEmpty()) {
        if (EFI_ERROR(USBKeyboardCheckForKey())) {
            return;
        }
    }
    //
    // If has key pending, signal the event.
    //
    gBS->SignalEvent(Event);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbKbdReadKeyStroke
//
// Description: Checks if a key is pending, if so - signals the event.
//
// Output:      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
USBKeyboardCheckForKey ()
{
    EFI_STATUS      Status;
    UINT8           KeyChar;

    KeypressCallback (NULL, NULL, gUsbData->aKBCScanCodeBufferStart, NULL);

    //
    // Fetch raw data from the USB keyboard input,
    // and translate it into ASCII data.
    //
    Status = USBParseKey(&KeyChar);
    if(EFI_ERROR(Status)) {
        return Status;
    }

    InsertKeyChar(KeyChar);
    return  EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:       StartPollingKey
//
// Description:     Get the keys from the USB Keyboard buffer and process it 
//
// Paremeters:      IN EFI_EVENT  Event      event that has been signaled
//                  IN VOID       *Context
//
// Output:          None
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID StartPollingKey(
    EFI_EVENT Event, 
    VOID *Context
)
{

    EFI_STATUS      Status;
    UINT8           KeyChar;

    KeypressCallback (NULL, NULL, gUsbData->aKBCScanCodeBufferStart, NULL);

    //
    // Fetch raw data from the USB keyboard input,
    // and translate it into ASCII data.
    //
    Status = USBParseKey(&KeyChar);

    if(EFI_ERROR(Status)) {
        //
        //If the Key ShiftState has valid key, report as Partial Key
        //
        if (gUsbKeyboardData->LeftShiftOn || gUsbKeyboardData->LeftCtrlOn || gUsbKeyboardData->LeftAltOn || 
            gUsbKeyboardData->LeftLogoOn || gUsbKeyboardData->RightShiftOn || gUsbKeyboardData->RightCtrlOn || 
            gUsbKeyboardData->RightAltOn || gUsbKeyboardData->RightLogoOn || gUsbKeyboardData->SysRqOn || gUsbKeyboardData->MenuOn) {

            //
            // Check the Partial Key for the RegsiterKeyNotify callback function
            //
//	            gUsbKeyboardData->ToggleState = (gUsbKeyboardData->ScrLkOn | gUsbKeyboardData->NumLockOn << 1 | gUsbKeyboardData->CapsOn << 2);     //(EIP91889-)
            UsbCheckKeyNotify(0);
        }

        return;
    }
            
    InsertKeyChar(KeyChar);

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ReadAndProcessKey
//
// Description:     It processes the key and sets its states.
//
// Paremeters:      Key - VOID Pointer
//                  KeySize - Size of the structure.
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadAndProcessKey(
    VOID        *Key,
    UINT8       KeySize
)
{

    AMI_EFI_KEY_DATA    TempKey;
    EFI_STATUS          Status = EFI_SUCCESS;
    UINT8               KeyChar;

    TempKey.Key.UnicodeChar = 0;
    TempKey.Key.ScanCode = SCAN_NULL;
    EfiZeroMem(&(TempKey.KeyState),sizeof(EFI_KEY_STATE));

    //
    // if there is no saved ASCII byte, fetch it
    // by calling USBKeyboardCheckForKey().
    //
    if(IsUSBKeyCharEmpty()) {
                                        //(EIP83888+)>
       do {
            Status = USBKeyboardCheckForKey();
            if(!(EFI_ERROR(Status))) 
             break;   
        }while(gUsbData->aKBCUsbDataBufferHead != gUsbData->aKBCUsbDataBufferTail);        
        if(EFI_ERROR(Status)) { 
            if (gUsbKeyboardData->LeftShiftOn || gUsbKeyboardData->LeftCtrlOn || gUsbKeyboardData->LeftAltOn || 
                gUsbKeyboardData->LeftLogoOn || gUsbKeyboardData->RightShiftOn || gUsbKeyboardData->RightCtrlOn || 
                gUsbKeyboardData->RightAltOn || gUsbKeyboardData->RightLogoOn || gUsbKeyboardData->SysRqOn || gUsbKeyboardData->MenuOn) {

                TempKey.KeyState.KeyToggleState = KEY_STATE_EXPOSED;
            }
            else {
                return Status;
            }
        }
        
    }
   
    if(!EFI_ERROR(Status)) {    
        RemoveKeyChar(&KeyChar);
    
        //
        // Translate saved ASCII byte into EFI_INPUT_KEY and PS/2 Scan Code
        //
        Status = USBKeyCodeToEFIScanCode(KeyChar,&(TempKey.Key));
        if(EFI_ERROR(Status)) {
            return Status;
        }
        TempKey.EfiKey = UsbToEfiKeyTable[KeyChar-4];
        TempKey.PS2ScanCode = KeyConvertionTable[KeyChar-4][3];
    } 
    

//	    gUsbKeyboardData->ToggleState = (gUsbKeyboardData->ScrLkOn | gUsbKeyboardData->NumLockOn << 1 | gUsbKeyboardData->CapsOn << 2);     //(EIP91889-)

    TempKey.KeyState.KeyToggleState |= TOGGLE_STATE_VALID;
    if (gUsbKeyboardData->ScrLkOn) {
        TempKey.KeyState.KeyToggleState |= SCROLL_LOCK_ACTIVE;
    }
    if (gUsbKeyboardData->NumLockOn) {
        TempKey.KeyState.KeyToggleState |= NUM_LOCK_ACTIVE;
    }
    if (gUsbKeyboardData->CapsOn) {
        TempKey.KeyState.KeyToggleState |= CAPS_LOCK_ACTIVE;
    }

    TempKey.KeyState.KeyShiftState = SHIFT_STATE_VALID;
    if (gUsbKeyboardData->LeftShiftOn) {
        TempKey.KeyState.KeyShiftState |= LEFT_SHIFT_PRESSED;
    }
    if (gUsbKeyboardData->LeftCtrlOn) {
        TempKey.KeyState.KeyShiftState |= LEFT_CONTROL_PRESSED;
    }
    if (gUsbKeyboardData->LeftAltOn) {
        TempKey.KeyState.KeyShiftState |= LEFT_ALT_PRESSED;
    }
    if (gUsbKeyboardData->LeftLogoOn) {
        TempKey.KeyState.KeyShiftState |= LEFT_LOGO_PRESSED;
    }

    if (gUsbKeyboardData->RightShiftOn) {
        TempKey.KeyState.KeyShiftState |= RIGHT_SHIFT_PRESSED;
    }
    if (gUsbKeyboardData->RightCtrlOn) {
        TempKey.KeyState.KeyShiftState |= RIGHT_CONTROL_PRESSED;
    }
    if (gUsbKeyboardData->RightAltOn) {
        TempKey.KeyState.KeyShiftState |= RIGHT_ALT_PRESSED;
    }
    if (gUsbKeyboardData->RightLogoOn) {
        TempKey.KeyState.KeyShiftState |= RIGHT_LOGO_PRESSED;
    }
    if (gUsbKeyboardData->SysRqOn) {
        TempKey.KeyState.KeyShiftState |= SYS_REQ_PRESSED;
    }
    if (gUsbKeyboardData->MenuOn) {
        TempKey.KeyState.KeyShiftState |= MENU_KEY_PRESSED;
    }

    ProcessMultiLanguage(&TempKey);


    // Tab, BackSpace and Enter Key are considerd that it's non Printable
    // Char and returned the ShiftKey status as it is. 

    if( TempKey.Key.UnicodeChar != 9 && TempKey.Key.UnicodeChar != 8 
        && TempKey.Key.UnicodeChar != 13 && TempKey.Key.UnicodeChar != 0) {
        TempKey.KeyState.KeyShiftState &= ~(RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED);
    }    

    pBS->CopyMem(Key, &TempKey, KeySize);
    return EFI_SUCCESS; 
}
    

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ProcessMultiLanguage
//
// Description:     It maps the current key to a Unicode character from
//                  the keyboard layout
//
// Paremeters:      KeyData - Pointer to the AMI_EFI_KEY_DATA .
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ProcessMultiLanguage(
    IN OUT  AMI_EFI_KEY_DATA                *KeyData
)
{
    EFI_STATUS Status;

    if(gMultiLangSupportProtocol == NULL) {
        Status= pBS->LocateProtocol (
                  &gAmiMultiLangSupportGuid,
                  NULL,
                  &gMultiLangSupportProtocol
                  );
        if(EFI_ERROR(Status)) {
            return EFI_NOT_FOUND;
        }
    }    

    return gMultiLangSupportProtocol->KeyboardLayoutMap(gMultiLangSupportProtocol,KeyData);
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
