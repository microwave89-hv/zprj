//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/KeyboardCommonDefinitions.h 2     9/23/11 12:37a Rameshr $
//
// $Revision: 2 $
//
// $Date: 9/23/11 12:37a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/KeyboardCommonDefinitions.h $
// 
// 2     9/23/11 12:37a Rameshr
// [TAG]           EIP63054
// [Category]      New Feature
// [Description]   0000790: Add warning to ReadKeyStrokeEx for partial key
// press
// [Files]         KeyboardCommonDefinitions.h, In.c, Kbc.h, Ps2Kbd.c,
// Efiusbkb.c, efiusbkb.h, efiusbhid.c
// 
// 1     7/21/11 4:02p Artems
// EIP 64356: Combine common keyboard definitions in one file
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	KeyboardCommonDefinitions.h
//
// Description:	This file contains definitions common for HiiKeyboard,
//              SimpleTextIn protocol and Ami keyboard PPI
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __KEYBOARD_COMMON_DEFINITIONS__H__
#define __KEYBOARD_COMMON_DEFINITIONS__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

//
// EFI Scan codes 
//
#define EFI_SCAN_NULL		    0x00
#define EFI_SCAN_UP			    0x01
#define EFI_SCAN_DN			    0x02
#define EFI_SCAN_RIGHT		    0x03
#define EFI_SCAN_LEFT		    0x04
#define EFI_SCAN_HOME		    0x05
#define EFI_SCAN_END		    0x06
#define EFI_SCAN_INS		    0x07
#define EFI_SCAN_DEL		    0x08
#define EFI_SCAN_PGUP		    0x09
#define EFI_SCAN_PGDN		    0x0A
#define EFI_SCAN_F1			    0x0B
#define EFI_SCAN_F2			    0x0C
#define EFI_SCAN_F3			    0x0D
#define EFI_SCAN_F4			    0x0E
#define EFI_SCAN_F5			    0x0F
#define EFI_SCAN_F6			    0x10
#define EFI_SCAN_F7			    0x11
#define EFI_SCAN_F8			    0x12
#define EFI_SCAN_F9			    0x13
#define EFI_SCAN_F10		    0x14
#define EFI_SCAN_F11		    0x15
#define EFI_SCAN_F12		    0x16
#define EFI_SCAN_ESC		    0x17

#define SHIFT_STATE_VALID       0x80000000
#define RIGHT_SHIFT_PRESSED     0x00000001
#define LEFT_SHIFT_PRESSED      0x00000002
#define RIGHT_CONTROL_PRESSED   0x00000004
#define LEFT_CONTROL_PRESSED    0x00000008
#define RIGHT_ALT_PRESSED       0x00000010
#define LEFT_ALT_PRESSED        0x00000020
#define RIGHT_LOGO_PRESSED      0x00000040
#define LEFT_LOGO_PRESSED       0x00000080
#define MENU_KEY_PRESSED        0x00000100
#define SYS_REQ_PRESSED         0x00000200

#define TOGGLE_STATE_VALID      0x80
#define SCROLL_LOCK_ACTIVE      0x01
#define NUM_LOCK_ACTIVE         0x02
#define CAPS_LOCK_ACTIVE        0x04
#define KEY_STATE_EXPOSED       0x40

//*******************************************************
// EFI_INPUT_KEY
//*******************************************************
typedef struct {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

//*******************************************************
// EFI_KEY_TOGGLE_STATE
//*******************************************************
typedef UINT8 EFI_KEY_TOGGLE_STATE;

//*******************************************************
// EFI_KEY_STATE
//*******************************************************
//
// Any Shift or Toggle State that is valid should have
// high order bit set.
//
typedef struct EFI_KEY_STATE {
    UINT32               KeyShiftState;
    EFI_KEY_TOGGLE_STATE KeyToggleState;
} EFI_KEY_STATE;

//***************************************************
// EFI_KEY
//***************************************************
typedef enum {
    EfiKeyLCtrl,        EfiKeyA0,           EfiKeyLAlt,         EfiKeySpaceBar,
    EfiKeyA2,           EfiKeyA3,           EfiKeyA4,           EfiKeyRCtrl,
    EfiKeyLeftArrow,    EfiKeyDownArrow,    EfiKeyRightArrow,   EfiKeyZero,
    EfiKeyPeriod,       EfiKeyEnter,        EfiKeyLShift,       EfiKeyB0,
    EfiKeyB1,           EfiKeyB2,           EfiKeyB3,           EfiKeyB4,
    EfiKeyB5,           EfiKeyB6,           EfiKeyB7,           EfiKeyB8,
    EfiKeyB9,           EfiKeyB10,          EfiKeyRShift,       EfiKeyUpArrow,
    EfiKeyOne,          EfiKeyTwo,          EfiKeyThree,        EfiKeyCapsLock,
    EfiKeyC1,           EfiKeyC2,           EfiKeyC3,           EfiKeyC4,
    EfiKeyC5,           EfiKeyC6,           EfiKeyC7,           EfiKeyC8,
    EfiKeyC9,           EfiKeyC10,          EfiKeyC11,          EfiKeyC12,
    EfiKeyFour,         EfiKeyFive,         EfiKeySix,          EfiKeyPlus,
    EfiKeyTab,          EfiKeyD1,           EfiKeyD2,           EfiKeyD3,
    EfiKeyD4,           EfiKeyD5,           EfiKeyD6,           EfiKeyD7,
    EfiKeyD8,           EfiKeyD9,           EfiKeyD10,          EfiKeyD11,
    EfiKeyD12,          EfiKeyD13,          EfiKeyDel,          EfiKeyEnd,
    EfiKeyPgDn,         EfiKeySeven,        EfiKeyEight,        EfiKeyNine,
    EfiKeyE0,           EfiKeyE1,           EfiKeyE2,           EfiKeyE3,
    EfiKeyE4,           EfiKeyE5,           EfiKeyE6,           EfiKeyE7,
    EfiKeyE8,           EfiKeyE9,           EfiKeyE10,          EfiKeyE11,
    EfiKeyE12,          EfiKeyBackSpace,    EfiKeyIns,          EfiKeyHome,
    EfiKeyPgUp,         EfiKeyNLck,         EfiKeySlash,        EfiKeyAsterisk,
    EfiKeyMinus,        EfiKeyEsc,          EfiKeyF1,           EfiKeyF2,
    EfiKeyF3,           EfiKeyF4,           EfiKeyF5,           EfiKeyF6,
    EfiKeyF7,           EfiKeyF8,           EfiKeyF9,           EfiKeyF10,
    EfiKeyF11,          EfiKeyF12,          EfiKeyPrint,        EfiKeySLck,
    EfiKeyPause
} EFI_KEY;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
