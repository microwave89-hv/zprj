//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/kbc.h 25    11/07/12 12:25a Srikantakumarp $
//
// $Revision: 25 $
//
// $Date: 11/07/12 12:25a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/kbc.h $
// 
// 25    11/07/12 12:25a Srikantakumarp
// [TAG]  		EIP99411
// [Category]  	Improvement
// [Description]  	Add port validation check in the PS2Ctrl module before
// starting the driver.
// [Files]  		kbc.c, kbc.h, mouse.c, ps2main.c, CORE_DXE.sdl, Tokens.c
// 
// 23    10/18/12 9:00a Deepthins
// [TAG]  		EIP70313
// [Category]  	Improvement
// [Description]  	Used CheckIssueLEDCmd in function LEDsOnOff instead of
// OutToKb(Kbd, 0xED)
// [Files]  		kbc.c, ps2kbd.c and kbc.h
// 
// 22    5/02/12 2:28a Deepthins
// [TAG]  		EIP63116
// [Category]  	Improvement
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Ps2kbd.c, Mouse.c, kbc.h, kbc.c
// 
// 21    4/24/12 2:18a Deepthins
// [TAG]  		EIP85747 
// [Category]  	Improvement
// [Description]  	USB-ReadKeyStrokeEx is returning EFI_SUCCESS with
// KEY_STATE_EXPOSED for Caps, Num and Scroll Lock Key's.
// KEY_STATE_EXPOSED only for the ShiftState Key's and not for togglestate
// key's.
// 
// [Files]  		Efiusbkb.c, ps2kbd.c and kbc.h
// 
// 20    2/01/12 1:59a Deepthins
// [TAG]  		EIP63116
// [Category]  	New Feature
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Token.c, Ps2main.c, Ps2kbd.c, Mouse.c, kbc.h, kbc.c,
// CORE_DXE.sdl
// 
// 19    9/22/11 6:32a Rameshr
// [TAG]  		EIP63054
// [Category]  	New Feature
// [Description]  	0000790: Add warning to ReadKeyStrokeEx for partial key
// press
// [Files]  		KeyboardCommonDefinitions.h, In.c, Kbc.h, Ps2Kbd.c,
// Efiusbkb.c, efiusbkb.h
// 
// 18    8/02/11 4:43a Rameshr
// [TAG] - EIP 58974
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - Yellow exclamation mark in Windows when PS2 KB/MS are not
// present.
// [RootCause]- ACPI name space variable reports that PS2 device present 
// [Solution] - Updated the SIO device status based on the device present
// after BDS.
// [Files] - Kbc.c, Kbc.h , Ps2main.c
// 
// 17    1/05/11 1:00a Rameshr
// [TAG]  		EIPEIP 35306
// [Category]  	Improvement
// [Description]  	Report the Ps2 Controller and Device Error Codes.
// [Files]  		AmiStatuscodes.h, Kbc.c, Kbc.h,Ps2ctl.sdl, ps2kbd.c,
// ps2main.c ,Statuscode.h
// 
// 16    12/10/10 5:30a Rameshr
// [TAG] - EIP 47011
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - DTM IO Tests fail due to presence of PS/2 devices that are
// not ready - no PS/2 devices attached during test.
// [RootCause]- PS2 device _STA method returns that, device is present .
// [Solution] - Updated the SIO device status based on the device
// presence.
// [Files] - Kbc.c , Kbc.h, Mouse.c
// 
// 15    8/23/10 4:23a Rameshr
// Bug Fix : EIP 40838
// Symptoms: KBC.C build failed in DetectPS2Keyboard() if
// DETECT_PS2_KEYBOARD=0 & PS2MOUSE_SUPPORT=0
// Files Modified: Efismplpp.c, Kbc.c, Kbc.h, Mouse.c PS2ctl.cif,
// Ps2ctl.sdl, Ps2Kbd.c, Ps2Mouse.c
// Details: 
// 1) Added Detect_PS2_Mouse sdl token and modified the code.
// 2) INSTALL_KEYBOARD_MOUSE_ALWAYS sdl token added.
//    1 - Install the Keyboard- SimpleTextIn, Mouse - AbsPointer Always, 
//    0 - Install the Keyboard- SimpleTextIn, Mouse - AbsPointer only if
// the device is present at the time of detection.
//    This is for Ps2Keyboard Hot plug support in EFI 
// 3) Code clean up in mouse.c EfiSmplpp.c ,ps2mouse.h
// 4) Unused file automaton.h removed.
// 
// 14    7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
// 
// 13    4/21/08 5:49p Olegi
// Removed keyboard modifiers bits definition, they should be taken from
// SimpleTextInEx.h
// 
// 12    4/09/08 10:19a Olegi
// Changed the key attributes (modifiers and shift state) reporting.
// 
// 11    9/07/07 4:34p Olegi
// EFI_KEY code implementation.
// 
// 10    8/31/07 2:17p Olegi
// Added SimpleTextInEx definitions.
// 
// 9     4/16/07 6:28p Pats
// Modified to conform with coding standards. No code changes.
// 
// 8     3/13/06 2:38a Felixp
// 
// 7     1/09/06 11:38a Felixp
// 
// 5     12/22/05 10:22a Srinin
// ProcessKBDData added.
// 
// 4     10/11/05 4:11p Srinin
// New function declarations added.
// 
// 3     8/30/05 1:15p Srinin
// KEYBOARD struct modified.
// 
// 2     3/04/05 1:38p Mandal
// 
// 1     2/01/05 1:10a Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     10/28/04 10:19a Olegi
// 
// 3     9/30/04 8:13a Olegi
// HotKeys added.
// 
// 2     9/17/04 7:02p Olegi
// 
// 1     8/27/04 3:17p Olegi
// Initial VSS checkin.
// 
// 4     8/18/04 6:37p Olegi
// Header and footer added.
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: kbc.h
//
// Description: Keyboard Controller functions header
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __PS2_KBC_SUPPORT_H__
#define __PS2_KBC_SUPPORT_H__

#include <Protocol\Cpu.h>
#include <Protocol\Legacy8259.h>
//
// KBC command/status/data IO ports
//
#define KBC_CMDSTS_PORT 0x64
#define KBC_DATA_PORT   0x60

//
// KBC status bits definition
//
#define KBC_OBF         0x01
#define KBC_IBF         0x02 
#define KBC_SYSFLAG     0x04 
#define KBC_CMD_DATA    0x08
#define KBC_INHIBIT_SW  0x10
#define KBC_AUX_OBF     0x20
#define KBC_TIMEOUT_ERR 0x40
#define KBC_PARITY_ERR  0x80

//
//    COMMANDS from KEYBOARD to SYSTEM
//
#define KB_ACK_COM          0xFA    // ACKNOWLEDGE command
#define KB_RSND_COM         0xFE    // RESEND command
#define KB_OVRN_COM         0xFF    // OVERRUN command
#define KB_DIAG_FAIL_COM    0xFD    // DIAGNOSTIC FAILURE command

#define KBD_ENABLE_SCANNING 0xF4    
#define KBD_DISABLE_SCANNING 0xF5   
#define KBD_RESET           0xFF    

#define rKeyboardID         0xF2
#define rMouseID            0xF2

//
// Keyboard scanner states
//
#define KBST_READY      0
#define KBST_E0         1
#define KBST_E1         2

#define BUFFER_SIZE  16
#define SYSTEM_KEYBOARD_IRQ 0x01
#define SYSTEM_MOUSE_IRQ    0x0C
#define SLAVE_IRQ           0X02
// LED inter command state
#define ED_COMMAND_ISSUED       0x01
#define ED_DATA_ISSUED          0x02

typedef struct {
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL iSimpleIn;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL iSimpleInEx;
    AMI_EFIKEYCODE_PROTOCOL iKeycodeInEx;
    AMI_EFI_KEY_DATA KeyData;
    BOOLEAN KeyIsReady;
    UINT8  ScannerState;
    AMI_EFI_KEY_DATA* pBufHead;
    AMI_EFI_KEY_DATA* pBufTail;
    AMI_EFI_KEY_DATA* pBufStart;
    AMI_EFI_KEY_DATA* pBufEnd;
    UINT8  Count;
//    UINT16 Modifiers;
    UINT8  Indicators;
    UINT8  LEDCommandState;
    UINT8  CommandResponded;           
} KEYBOARD;

typedef struct {
    UINT8   KbdBuffer[BUFFER_SIZE];
    UINT8   KbdIndex;
} KEYBOARD_IRQ_STORE;

EFI_STATUS KBCBatTest();
UINT8 Read8042(UINT8 bCmd);
UINT8 ObFullRead();
void WriteKeyboardCommand(UINT8 bCmd);
void WriteKeyboardData(UINT8 bCmd);
void Write8042CommandByte(UINT8 bCCB);
void IbFree();
EFI_STATUS IbFreeTimeout(UINT32 TimeoutValue);
void IoDelay();
void AutodetectKbdMousePorts();
EFI_STATUS ReadDevice(UINT8 bCmd, UINT8 *Data, UINT8 Response);
BOOLEAN ObFullReadTimeout(UINT8* data,  UINT32 msec, BOOLEAN ONLYOBF);
UINT8 IssueCommand(UINT8 bCmd);
UINT8 AuxDeviceCommand(UINT8 bCmd);
EFI_STATUS OutToKb(KEYBOARD* kbd, UINT8 bCmd);
EFI_STATUS InsertKeyToBuffer (KEYBOARD* kbd, AMI_EFI_KEY_DATA *key);
EFI_STATUS GetKeyFromBuffer (KEYBOARD* kbd, VOID* key, UINT8 size);
BOOLEAN CheckKeyinBuffer (KEYBOARD* kbd);
void ReadAndProcessKey(void *Context);
void DisableKeyboard();
EFI_STATUS EnableKeyboard();
void DisableAuxDevice();
void EnableAuxDevice();
void LEDsOnOff(KEYBOARD* kbd);
void CheckIssueLEDCmd (KEYBOARD *kbd);
void ProcessKBDResponse (KEYBOARD *kbd, UINT8 bData); 
EFI_STATUS DetectPS2Keyboard();
EFI_STATUS DetectPS2KeyboardAndMouse();
void HandleKBDData(void *Context, UINT8 data);
void ProcessKBDData (KEYBOARD *kbd, UINT8 data);
BOOLEAN ObFullReadMTimeout(UINT8* data, UINT32 msec);
EFI_STATUS ReadDeviceM(UINT8 bCmd, UINT8 *Data, UINT8 Response);
EFI_STATUS InitHotKeys(EFI_HANDLE Controller);
EFI_STATUS ProcessHotKey(UINT8 code, UINT16 modifiers);
EFI_STATUS DetectPs2Mouse();
EFI_STATUS GetMouseData();
VOID UpdateSioVariableForKeyboardMouse(
    EFI_EVENT   Event,
    VOID        *Context
);
EFI_STATUS
CheckPartialKey (
    KEYBOARD    *Kbd,
    EFI_KEY_DATA        *Key
);
VOID InitKeyboardIrq(VOID);     
void ProcessLEDCommandData(KEYBOARD* kbd);
EFI_STATUS ProcessMultiLanguage(
    IN OUT  AMI_EFI_KEY_DATA                *KeyData
	);
#endif  // __PS2_KBC_SUPPORT_H__

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
