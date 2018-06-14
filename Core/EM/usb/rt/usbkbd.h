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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbkbd.h 20    3/18/16 12:03a Wilsonlee $
//
// $Revision: 20 $
//
// $Date: 3/18/16 12:03a $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/usbkbd.h $
// 
// 20    3/18/16 12:03a Wilsonlee
// [TAG]  		EIP257506
// [Category]  	Improvement
// [Description]  	Add USB_KEYREPEAT_INTERVAL token to change the key
// repeat interval.
// [Files]  		usb.sdl, xhci.h, usbkbd.h, uhci.c, ohci.c, ehci.c
// 
// 19    3/02/16 9:42p Wilsonlee
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
// 18    2/24/15 5:50a Wilsonlee
// [TAG]  		EIP149716
// [Category]  	Improvement
// [Description]  	Error Handling in USB mouse data.
// [Files]  		usbms.c, usbkbd.h, syskbc.c, xhci.c
// 
// 17    5/06/14 5:16a Ryanchou
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
// 16    2/26/14 1:56a Wilsonlee
// [TAG]  		EIP149854
// [Category]  	Improvement
// [Description]  	Add data length parameter to polling callback function.
// [Files]  		usbkbd.c, uhci.c, usb.c, usbhub.c, usbCCID.c, usbms.c,
// usbhid.c, usbpoint.c, usbkbd.h, ehci.c, ohci.c, xhci.c, usbdef.h
// 
// 15    12/30/13 3:42a Wilsonlee
// [TAG]  		EIP148411
// [Category]  	Improvement
// [Description]  	Check if CCB_MOUSE_INTRPT is set before we sent mouse
// data.
// [Files]  		usbkbd.h, syskbc.c
// 
// 14    7/04/13 5:49a Roberthsu
// [[TAG]           EIP127014 
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Mouse drifting not smooth
// [RootCause]     Bbecause Efi simple point protocol RelativeMovementX
// type is INT32.
// [Solution]      Transfer data type to INT32.
// [Files]         usbdef.h,usbhid.c,usbms.c,usbkbd.h
// 
// 13    1/11/13 4:16a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 12    5/22/12 10:57a Jittenkumarp
// [TAG]  		EIP87959 
// [Category]  	New Feature
// [Description]  	Proper Error path in the USB driver, incase KBC Input
// buffer is full
// [Files]  		usbkbd.h, syskbc.c
// 
// 11    5/03/12 6:28a Roberthsu
// [TAG]           EIP84455
// [Category]      Improvement
// [Description]   Implement usb hid device gencric.
// [Files]  		amiusb.c,amiusbhc.c,efiusbhid.c,efiusbkb.c,ehci.c,ohci.c,uhc
// d.c,uhci.c,usbdef.h,usbhid.c,usbhub.c,usbkbd.c,usbkbd.h,usbms.c,usbsb.c
// ,usbsrc.sdl
// 
// 10    7/15/11 6:11a Ryanchou
// [TAG]  		EIP38434
// [Category]  	New Feature
// [Description]  	Added USB HID report protocol support.
// [Files]  		amiusb.c, AmiUsbController.h, amiusbhc.c, efiusbkb.c,
// efiusbkb.h, ehci.c, ohci.c, uhcd.c uhcd.cif, uhci.c, usb.c, usbdef.h,
// usbkbd.c, usbkbd.h, usbms.c, usbrt.cif, usbsb.c, usbsetup.c,
// usbsrc.sdl, xhci.c
// 
// 9     9/16/09 11:10a Olegi
// 
// 8     9/15/09 12:21p Olegi
// Added KEY_REPEAT_LOGIC functionality. EIP#25841
// 
// 7     9/05/08 4:22p Olegi
// 
// 6     5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 5     3/20/07 12:21p Olegi
//
// 3     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 2     8/25/05 7:19p Andriyn
// USB Keyboard and mouse to use EMUL 60/64 for passing data to KBC.
// Fall-back when EMUL 60/64 is not present
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
//  Name:           UsbKbd.h
//
//  Description:    AMI USB keyboard support header
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

// Avoid including multiple instance of this file
#ifndef     __USBKBD_H
#define     __USBKBD_H

#include "token.h"

// Make/break code equates

#define KBC_AUTO_REPEAT_BIT_MASK    (0x01 << 9)
#define KBC_PASSWORD_FLAG_BIT_MASK  (0x01 << 10)
#define KBC_SCANNER_STATUS_BIT_MASK (0x01 << 11)
#define KBC_PORT6064_TRAP_BIT_MASK  (0x01 << 12)
#define KBC_MK_BRK_CODE_BIT_MASK    (0x01 << 13)

#define USB_GEN_MAKE_CODE  0x020
#define USB_GEN_BREAK_CODE 0x030


// Equates used by keyboard controller scanner code
#define LEFT_ALT        0x011   // Left-ALT scan code (set 2)
#define LEFT_CTRL       0x014   // Left-CTRL scan code (set 2)
#define LEFT_SHIFT      0x012   // Left-SHIFT scan code (set 2)
#define RIGHT_SHIFT     0x059   // Right-SHIFT scan code (set 2)

// Extended status flag bit definitions
#define KBCEXT_LED_UPDATE_IN_PROGRESS_BIT   BIT0

// Scan code for base case only
#define RIGHT_ALT       0x011+0x80  // Local code id (scan-2)
#define RIGHT_CTRL      0x014+0x80  // Local code id (scan-2)
#define LEFT_MS_KEY     0x01F+0x80  // Microsoft left key
#define RIGHT_MS_KEY    0x027+0x80  // Microsoft right key
#define APP_MS_KEY      0x02F+0x80  // Microsoft application key
#define RIGHT_ENTER     0x05A+0x80  // Local code id (scan-2)

// Equates for KB shift key status information
#define KB_FUNCTION_BIT         7   // Function key LED bit
#define KB_FUNCTION_BIT_MASK    (1 << KB_FUNCTION_BIT)
#define KB_SCROLL_LOCK_BIT      6   // Scroll key LED bit
#define KB_SCROLL_LOCK_BIT_MASK (1 << KB_SCROLL_LOCK_BIT)
#define KB_CAPS_LOCK_BIT        5   // CAPS lock key LED bit
#define KB_CAPS_LOCK_BIT_MASK   (1 << KB_CAPS_LOCK_BIT)
#define KB_NUM_LOCK_BIT         4   // NUM lock key LED bit
#define KB_NUM_LOCK_BIT_MASK    (1 << KB_NUM_LOCK_BIT   )
#define KB_ALT_KEY_BIT          3   // ALT key status bit
#define KB_ALT_KEY_BIT_MASK     (1 << KB_ALT_KEY_BIT    )
#define KB_CTRL_KEY_BIT         2   // CTRL key status bit
#define KB_CTRL_KEY_BIT_MASK    (1 << KB_CTRL_KEY_BIT   )
#define KB_LSHIFT_KEY_BIT       1   // LSHIFT key status bit
#define KB_LSHIFT_KEY_BIT_MASK  (1 << KB_LSHIFT_KEY_BIT)
#define KB_RSHIFT_KEY_BIT       0   // RSHIFT key status bit
#define KB_RSHIFT_KEY_BIT_MASK  (1 << KB_RSHIFT_KEY_BIT)

#define KBC_SCAN_CODE_SET_BIT_SHIFT 0
#define KBC_SET_SCAN_CODE_SET2      (0x02 << KBC_SCAN_CODE_SET_BIT_SHIFT)
#define KBC_SCAN_CODE_SET_BIT_MASK  (0x03 << KBC_SCAN_CODE_SET_BIT_SHIFT)

#if USB_KEYREPEAT_INTERVAL
#define REPEAT_INTERVAL 16
#define KBC_TYPE_RATE_BIT_SHIFT     1
#define KBC_TYPE_RATE_BIT_MASK      (0x05 << KBC_TYPE_RATE_BIT_SHIFT)

#define KBC_TYPE_DELAY_BIT_SHIFT    4
#define KBC_TYPE_DELAY_BIT_MASK     (0x05 << KBC_TYPE_DELAY_BIT_SHIFT)

#else
#define REPEAT_INTERVAL 8
#define KBC_TYPE_RATE_BIT_SHIFT     2
#define KBC_TYPE_RATE_BIT_MASK      (0x07 << KBC_TYPE_RATE_BIT_SHIFT)

#define KBC_TYPE_DELAY_BIT_SHIFT    6
#define KBC_TYPE_DELAY_BIT_MASK     (0x07 << KBC_TYPE_DELAY_BIT_SHIFT)
#endif


// Scan code common to all the cases (base, control, shift and alt cases)
#define PRINT_SCREEN        (0x07C + 0x80)    // Local code id (scan-2)

// Scan code common to base and control cases
#define PAUSE_KEY       (0x07E + 0x80)    // Local code id (scan-2)

// Scan code common to base and shift cases
#define SLASH_KEY       (0x4A + 0x80)     // Local code id (scan-2)

// Scan code common to base, shift and num lock cases
#define END_KEY         (0x069 + 0x80)    // Local code id (scan-2)
#define LEFT_KEY        (0x06B + 0x80)    // Local code id (scan-2)
#define HOME_KEY        (0x06C + 0x80)    // Local code id (scan-2)
#define INSERT_KEY      (0x070 + 0x80)    // Local code id (scan-2)
#define DEL_KEY         (0x071 + 0x80)    // Local code id (scan-2)
#define DOWN_KEY        (0x072 + 0x80)    // Local code id (scan-2)
#define RIGHT_KEY       (0x074 + 0x80)    // Local code id (scan-2)
#define UP_KEY          (0x075 + 0x80)    // Local code id (scan-2)
#define PAGE_DOWN_KEY   (0x07A + 0x80)    // Local code id (scan-2)
#define PAGE_UP_KEY     (0x07D + 0x80)    // Local code id (scan-2)

#define CCB_TRANSLATE_SCAN_CODE_BIT_MASK    BIT6
#define KBC_COMMAND_REG     0x64
#define KBC_SUBCOMMAND_REG  0x60
#define KBC_STATUS_REG      0x64
#define KBC_DATA_REG        0x60

#define MOUSE_ENABLED_BIT               7
#define MOUSE_ENABLED_BIT_MASK          (1 << MOUSE_ENABLED_BIT)
#define MOUSE_DATA_READY_BIT            6
#define MOUSE_DATA_READY_BIT_MASK       (1 << MOUSE_DATA_READY_BIT)
#define MOUSE_DATA_FROM_USB_BIT         5
#define MOUSE_DATA_FROM_USB_BIT_MASK    (1 << MOUSE_DATA_FROM_USB_BIT)
  // Mouse data size = 1:4byte data, 0:3byte data
#define MOUSE_4BYTE_DATA_BIT            4
#define MOUSE_4BYTE_DATA_BIT_MASK       (1 << MOUSE_4BYTE_DATA_BIT)

#define KBC_DATA_TX_ORDER_BIT_MASK  0x03 << 14
#define KBC_DATA_TX_ORDER_INC_VALUE 0x01 << 14
#define KBC_DATA_TX_ORDER_KB_FIRST  0x02 << 14

#define CCB_KEYBOARD_INTRPT                 BIT0
#define CCB_MOUSE_INTRPT                    BIT1    
#define CCB_KEYBOARD_DISABLED               BIT4
#define CCB_MOUSE_DISABLED                  BIT5
#define CCB_TRANSLATE_SCAN_CODE_BIT_MASK    BIT6

#ifndef USB_KBD_SET_LED_TIMEOUT_MS
#define USB_KBD_SET_LED_TIMEOUT_MS 100
#endif

UINT8       ByteReadIO(UINT16);
void        ByteWriteIO(UINT16, UINT8);

UINT8       USBMouse_GetFromMouseBuffer ();
void        USBKeyRepeat(HC_STRUC*, UINT8);
UINT8       USBKBC_GetFromCharacterBuffer();

UINT8   USBKB_ConvertSet2CodeToSet1Code(UINT8);
void    USBKBC_SendToCharacterBuffer(UINT8);
UINT8   USBTrap_GetCurrentScanCodeSetNumber();
UINT8   USBKB_ConvertScanCodeBetweenCodeSet(UINT8, UINT8*);
//void  SYSKBC_UpdateLEDState(UINT8);
UINT8    KBC_WaitForInputBufferToBeFree( );
UINT8   KBC_WaitForOutputBufferToBeFilled( );
void    USBKB_GenerateType1MakeCode( );
void    USBKB_GenerateType1BreakCode( );
void    USBKB_GenerateType2MakeCode( );
void    USBKB_GenerateType2BreakCode( );
UINT8   USBTrap_GetOverrunCode( );
void    USBKB_DiscardCharacter(UINT8*);
UINT16  USBKB_CheckForExtendedKey(UINT8);
UINT16  USBKB_CheckForNumericKeyPadKey(UINT8);
UINT8   USBKBC_CheckCharacterBufferFull(UINT8);
void    USBKB_UpdateLEDState(UINT8);
UINT8   USBKB_ConvertUSBKeyCodeToScanCodeSet2 (UINT8);
UINT16  USBKB_CheckModifierKeyPress (UINT8);
UINT8   KBC_WriteCommandByte(UINT8);
UINT8   KBC_ReadDataByte(UINT8 *);
void    KBC_WriteSubCommandByte(UINT8);
EFI_STATUS    SYSKBC_SendKBCData();

extern  UINT8       USB_InstallCallBackFunction (CALLBACK_FUNC);

extern  DEV_INFO*   USB_GetDeviceInfoStruc(UINT8, DEV_INFO*,UINT8, HC_STRUC*);
extern  UINT8       USBLogError(UINT16);
extern  void        USBKeyRepeat(HC_STRUC*, UINT8);
#if USB_DEV_MOUSE
extern  UINT8       USBMSSendMouseData();
extern  void        USBMSUpdateMouseInterface();
#endif

void        USBKBDInitialize (void);
UINT8       USBKBDDisconnectDevice (DEV_INFO*);

void    USBKBC_GetAndStoreCCB();
DEV_INFO*   USBKBDConfigureDevice (DEV_INFO*);  //(EIP84455)
UINT16  USBKBDFindUSBKBDeviceTableEntry(DEV_INFO*);
UINT16  USBKBDConnectKeyboard(DEV_INFO*);
UINT8   USBKBDProcessKeyboardData ( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8	UsbKbdSetLed(DEV_INFO*, UINT8);

void    USBKB_GenerateScanCode ( UINT8, UINT8, UINT16 );

VOID    UsbScanner(DEV_INFO*, UINT8*);
VOID    USBKB_Scanner (DEV_INFO*, UINT8*);
VOID    USBKB_Int9(UINT8*);

VOID    ProcessKeyCode(UINT8);

VOID    LegacyAutoRepeat(HC_STRUC*);
VOID    SysKbcAutoRepeat(HC_STRUC*);
VOID    SysNoKbcAutoRepeat();
VOID    USBKBKeyrepeatCallback();
VOID    USBKBDPeriodicInterruptHandler(HC_STRUC*);
                                        //(EIP84455+)>
UINT8   USBHIDProcessData( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);               
UINT8   USBMSProcessMouseData ( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   USBAbsProcessMouseData ( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
                                        //<(EIP84455+)

typedef struct _LEGACY_USB_KEY_MODIFIERS {
    UINT8   ScrlLock    : 1;
    UINT8   NumLock     : 1;
    UINT8   CapsLock    : 1;
    UINT8   Ctrl        : 1;
    UINT8   Alt         : 1;
    UINT8   Shift       : 1;
} LEGACY_USB_KEY_MODIFIERS;

typedef struct _LEGACY_USB_KEYBOARD {
    UINT8 KeyCodeStorage[6];
    LEGACY_USB_KEY_MODIFIERS    KeyModifierState;
    UINT8 KeyToRepeat;
} LEGACY_USB_KEYBOARD;

										//(EIP38434+)>
typedef struct {
    union {
		UINT8		   Modifier;
	struct {
		UINT8		   KB_RSHIFT	: 1;// RSHIFT key status bit
		UINT8		   KB_LSHIFT	: 1;// LSHIFT key status bit
		UINT8		   KB_CTRL		: 1;// CTRL key status bit
		UINT8		   KB_ALT		: 1;// ALT key status bit
		UINT8		   KB_NUM_LOCK		: 1;// NUM lock key LED bit
		UINT8		   KB_CAPS_LOCK 	: 1;// CAPS lock key LED bit
		UINT8		   KB_SCROLL_LOCK	: 1;// Scroll key LED bit
		UINT8		   KB_FUNCTION		: 1;// Function key LED bit 		
	} Modify;
    };
		UINT8	Reserved;
		UINT8	Keycode[6];
}USBKBD_DATA;

//              0   Bit     Description
//              -------------------------------------------
//                   0      If set, button 1 is pressed
//                   1      If set, button 2 is pressed
//                   2      If set, button 3 is pressed
//                   3-7        Reserved
//              -------------------------------------------
//              1   X displacement value
//              2   Y displacement value
typedef struct {
    union {
		UINT8		   ButtonByte;
	struct {
		UINT8		   BUTTON1		: 1;// RSHIFT key status bit
		UINT8		   BUTTON2		: 1;// LSHIFT key status bit
		UINT8		   BUTTON3		: 1;// CTRL key status bit
		UINT8		   RESERVED		: 5;// ALT key status bit
	} BUTTON;
    };
		UINT8	X;
		UINT8	Y;
		UINT8 	Z;
        UINT16  EfiX;                   //(EIP127014)
        UINT16  EfiY;                   //(EIP127014)
        UINT8   FillUsage;              //(EIP127014)
}USBMS_DATA;

typedef struct {
		UINT8	Button;
		UINT16	X;
		UINT16	Y;
		UINT16 	Pressure;
}USBABS_DATA; 
										//<(EIP38434+)
#endif      // __USB_H

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
