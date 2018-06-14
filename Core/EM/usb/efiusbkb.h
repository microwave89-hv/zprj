//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbkb.h 25    11/26/13 4:09a Ryanchou $
//
// $Revision: 25 $
//
// $Date: 11/26/13 4:09a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbkb.h $
// 
// 25    11/26/13 4:09a Ryanchou
// [TAG]  		EIP142509
// [Category]  	Improvement
// [Description]  	Added usage 0x87 and 0x89.
// [Files]  		efiusbkb.c, efiusbkb.h
// 
// 24    8/23/13 6:08a Ryanchou
// Fix the AMI_MULTI_LANG_SUPPORT_PROTOCOL redefinition problem.
// 
// 23    7/24/13 2:33a Roberthsu
// [TAG]           EIP121333
// [Category]      Improvement
// [Description]   Multiple USB mouse support for UEFI USB mouse driver
// [Files]         efiusbhid.c,efiusbkb.h,efiusbms.c
// 
// 22    11/20/12 1:54a Deepthins
// [TAG]  		EIP106155 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Build error with lastest USB module and old core label
// [RootCause]  	Backward compatibility problem with old core label .
// [Solution]  	Provided required  definations when core label is 4.6.5.4
// or below.
// [Files]  		efiusbkb.h
// 
// 21    11/15/12 3:47a Ryanchou
// 
// 19    11/01/12 6:33a Deepthins
// [TAG]  		EIP101102
// [Category]  	Improvement
// [Description]  	Multi Language is supported in USB driver
// [Files]  		efiusbkb.c, efiusbkb.h
// 
// 18    3/20/12 10:32p Wilsonlee
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
// 17    12/29/11 1:56a Deepthins
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
// 16    9/23/11 12:33a Rameshr
// [TAG]  		EIP63054
// [Category]  	New Feature
// [Description]  	0000790: Add warning to ReadKeyStrokeEx for partial key
// press
// [Files]  		KeyboardCommonDefinitions.h, In.c, Kbc.h, Ps2Kbd.c,
// Efiusbkb.c, efiusbkb.h, efiusbhid.c
// 
// 15    7/15/11 6:23a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, efiusbpoint.c, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c,
// usb.c, usbdef.h, usbhid.c, usbkbd.c, usbkbd.h, usbms.c, usbpoint.c,
// usbrt.cif, usbsb.c, usbsetup.c, usbsrc.sdl, xhci.c
// 
// 14    5/14/10 10:55a Olegi
// PrintScreen/SysRq key, Menu Key, Left Logo and Right Logo Key support
// in USB Keyboard driver
// EIP 38214
// 
// 13    5/10/10 1:57a Rameshr
// Issue:UsbKeyboard Driver doesn’t differentiate between Left Shift and
// Right Shift Key.
// Solution: modified the driver to differentiate between Left
// Shift/Alt/Ctrl and Right Shift/Alt/Ctrl Key's.
// EIP 38256
// 
// 12    9/05/08 4:14p Olegi
// RepeatKey is moved from USB_KB_DEV structure to global data area.
// 
// 11    5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
// 
// 10    12/17/07 5:43p Rameshraju
// Added the core revision check for the AMI Keycode to build with OLD
// core.
// 
// 9     10/23/07 4:16p Olegi
// AmiKeycode protocol implementation.
// 
// 8     9/18/07 12:35p Olegi
// 
// 6     3/20/07 1:29p Olegi
//
// 4     5/03/06 9:59a Olegi
//
// 3     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
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

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           EfiUsbKb.h
//
//  Description:    AMI USB keyboard driver header file
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMI_USB_KB_H
#define _AMI_USB_KB_H


#include "amidef.h"
#include "usbdef.h"
#if (CORE_REVISION >= 0x3)
#include "Protocol\AmiKeycode.h"    // Available starting from Core 4.6.3
#endif

#define USBKB_DRIVER_VERSION 1

EFI_STATUS  SupportedUSBKeyboard(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, EFI_DEVICE_PATH_PROTOCOL *dp);
EFI_STATUS  InstallUSBKeyboard(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, EFI_DEVICE_PATH_PROTOCOL *dp,DEV_INFO *Dev_info,EFI_USB_IO_PROTOCOL *UsbIo );	//(EIP38434+)
EFI_STATUS  UninstallUSBKeyboard(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, UINTN numberOfChildren, EFI_HANDLE *children  );

										//(EIP38434+)>
EFI_STATUS 	InstallUSBAbsMouse(EFI_HANDLE Controller,DEV_INFO   *pDevInfo); 
EFI_STATUS UninstallUSBAbsMouse(IN EFI_HANDLE Controller); 
 
EFI_STATUS InstallUSBMouse(EFI_HANDLE Controller,EFI_USB_IO_PROTOCOL *UsbIo,DEV_INFO *DevInfo);
EFI_STATUS UninstallUSBMouse(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, UINTN numberOfChildren, EFI_HANDLE *children  );

EFI_STATUS  UsbHidInit(EFI_HANDLE  ImageHandle,EFI_HANDLE  ServiceHandle);	
EFI_STATUS  SupportedUSBHid(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, EFI_DEVICE_PATH_PROTOCOL *dp);
EFI_STATUS  InstallUSBHid(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, EFI_DEVICE_PATH_PROTOCOL *dp);
EFI_STATUS  UninstallUSBHid(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, UINTN numberOfChildren, EFI_HANDLE *children  );
										//<(EIP38434+)
#define USB_KB_DEV_SIGNATURE  EFI_SIGNATURE_32('u','k','b','d')
typedef struct
{
    UINTN                           Signature;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL  SimpleInput;
#if (CORE_REVISION >= 0x3)
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   SimpleInputEx;
    AMI_EFIKEYCODE_PROTOCOL         KeycodeInput;
#endif
 
    EFI_USB_IO_PROTOCOL             *io;
    DEV_INFO                        *dev_info;
    
} USB_KB_DEV;

typedef struct
{
    USB_KB_BUFFER                   KeyboardBuffer;
    UINT8                           LeftCtrlOn;
    UINT8                           LeftAltOn;
    UINT8                           LeftShiftOn;
    UINT8                           RightCtrlOn;
    UINT8                           RightAltOn;
    UINT8                           RightShiftOn;
    UINT8                           SysRqOn;
    UINT8                           MenuOn;
    UINT8                           LeftLogoOn;
    UINT8                           RightLogoOn;
    UINT8                           NumLockOn;
    UINT8                           CapsOn;
    UINT8                           ScrLkOn;
    UINT8                           LastKeyCodeArray[8];
    UINT8                           CurKeyChar;
    UINT8                           KeyChar[MAX_KEY_ALLOWED + 1];
    UINT8                           bHead;
    UINT8                           bTail;
    UINT8                           ToggleState;
}USB_KEYBOARD_DATA;
//
// Global Variables
//

#ifndef CR
#define CR(record, TYPE, field, signature) _CR(record, TYPE, field)
#endif
#define USB_KB_DEV_FROM_THIS(a,b) \
    CR(a, USB_KB_DEV, b, USB_KB_DEV_SIGNATURE)

#define MOD_CONTROL_L   0x01
#define MOD_CONTROL_R   0x10
#define MOD_SHIFT_L     0x02
#define MOD_SHIFT_R     0x20
#define MOD_ALT_L       0x04
#define MOD_ALT_R       0x40
#define MOD_WIN_L       0x08
#define MOD_WIN_R       0x80

typedef struct
{
    UINT8 Mask;
    UINT8 Key;
} KB_MODIFIER;

#define USB_KEYCODE_MAX_MAKE    0x86


#define USBKBD_VALID_KEYCODE(key)   ((UINT8)(key) > 3)

//
// Backward compatibility for Multi Language support
//
#if CORE_COMBINED_VERSION <= 0x4028E
#ifndef AMI_MULTI_LANG_SUPPORT_PROTOCOL_GUID

#define AMI_MULTI_LANG_SUPPORT_PROTOCOL_GUID \
    {0xb295bd1c, 0x63e3, 0x48e3, 0xb2, 0x65, 0xf7, 0xdf, 0xa2, 0x7, 0x1, 0x23}

typedef struct _AMI_MULTI_LANG_SUPPORT_PROTOCOL AMI_MULTI_LANG_SUPPORT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_KEYBOARD_LAYOUT_MAP)(
    IN      AMI_MULTI_LANG_SUPPORT_PROTOCOL *This,
    IN  OUT AMI_EFI_KEY_DATA *Keydata );

typedef struct _AMI_MULTI_LANG_SUPPORT_PROTOCOL {
    EFI_KEYBOARD_LAYOUT_MAP     KeyboardLayoutMap;
} AMI_MULTI_LANG_SUPPORT_PROTOCOL;

#endif
#endif

EFI_STATUS InitUSBKeyboard();
EFI_STATUS InitUSBMouse();

UINT8
KeypressCallback(
    HC_STRUC* fpHCStruc,
    DEV_INFO* fpDevInfo,
    UINT8* fpBuf1,
    UINT8* fpBuf2
    );

UINT8
KeyrepeatCallback(
    HC_STRUC* fpHCStruc,
    DEV_INFO* fpDevInfo,
    UINT8* fpBuf1,
    UINT8* fpBuf2);
EFI_STATUS

USBParseKey(
    OUT     UINT8       *KeyChar
    );


EFI_STATUS
USBKeyCodeToEFIScanCode(
    IN  UINT8           KeyChar,
    OUT EFI_INPUT_KEY   *Key
    );


EFI_STATUS
InitUSBKeyBuffer(
    IN OUT  USB_KB_BUFFER   *KeyboardBuffer
    );
										//(EIP83295)>
BOOLEAN
IsUSBKeyboardBufferEmpty(
    IN  USB_KB_BUFFER   *KeyboardBuffer
    );


BOOLEAN
IsUSBKeyboardBufferFull(
    IN  USB_KB_BUFFER   *KeyboardBuffer
    );
										//<(EIP83295)

EFI_STATUS
InsertKeyCode(
    IN OUT  USB_KB_BUFFER *KeyboardBuffer,
    IN      UINT8         Key,
    IN      UINT8         Down
    );


EFI_STATUS
RemoveKeyCode(
    IN OUT  USB_KB_BUFFER *KeyboardBuffer,
    OUT     USB_KEY       *UsbKey
    );


EFI_STATUS
InitUSBKeyCharBuffer();

BOOLEAN
IsUSBKeyCharEmpty();

BOOLEAN
IsUSBKeyCharFull();

EFI_STATUS
InsertKeyChar(
    UINT8           KeyChar
  );


EFI_STATUS
RemoveKeyChar(
    OUT     UINT8       *KeyChar
    );

EFI_STATUS
SetKeyLED();

EFI_STATUS
EFIAPI
UsbKbdReset (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  IN  BOOLEAN                 ExtendedVerification
  );

EFI_STATUS
EFIAPI
UsbKbdReadKeyStroke (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  OUT EFI_INPUT_KEY           *Key
  );

#if (CORE_REVISION >= 0x3)
EFI_STATUS
UsbKbdResetEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN  BOOLEAN                 ExtendedVerification
  );

EFI_STATUS
EFIAPI
UsbKbdReadKeyStrokeEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  OUT EFI_KEY_DATA *KeyData
  );

EFI_STATUS UsbKbdReadEfiKey(
    IN AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA *KeyData
);

EFI_STATUS
UsbKbdSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState
);

EFI_STATUS
UsbKbdRegisterKeyNotify (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT EFI_HANDLE *NotifyHandle
);

EFI_STATUS
UsbKbdUnregisterKeyNotify (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
  );
#endif
VOID
EFIAPI
UsbKbdWaitForKey (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  );

EFI_STATUS
USBKeyboardCheckForKey (
);

VOID StartPollingKey(
    EFI_EVENT Event, 
    VOID *Context
);

EFI_STATUS ProcessMultiLanguage(
    IN OUT  AMI_EFI_KEY_DATA                *KeyData
);

EFI_STATUS ReadAndProcessKey(
    VOID        *Key,
    UINT8       KeySize
);
#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
