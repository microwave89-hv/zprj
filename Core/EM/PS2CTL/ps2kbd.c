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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/ps2kbd.c 63    11/01/12 6:42a Deepthins $
//
// $Revision: 63 $
//
// $Date: 11/01/12 6:42a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/ps2kbd.c $
// 
// 63    11/01/12 6:42a Deepthins
// [TAG]  		EIP101100 
// [Category]  	Improvement
// [Description]  	Multi Language is supported in Ps2ctl driver
// [Files]  		CORE_DXE.sdl, kbc.h, ps2kbd.c and Tokens.c
// 
// 62    10/18/12 9:51a Deepthins
// [TAG]  		EIP95111
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	PS2 mouse is not working in setup.
// [RootCause]  	In stream mode data reporting is disabled by default. The
// mouse will not actually issue any movement data packets until it
// receives the "Enable Data Reporting" (0xF4) command. So even when the
// DETECT_PS2_KEYBOARD and DETECT_PS2_MOUSE token is disabled we need to
// send command 0xf4 to Enable Data Reporting.
// 
// [Solution]  	In MouseReset function, Set sampleRate ,Resolution and
// Enable streaming.
// [Files]  		mouse.c and ps2kbd.c
// 
// 61    10/18/12 9:03a Deepthins
// [TAG]  		EIP70313
// [Category]  	Improvement
// [Description]  	Used CheckIssueLEDCmd in function LEDsOnOff instead of
// OutToKb(Kbd, 0xED)
// [Files]  		kbc.c, ps2kbd.c and kbc.h
// 
// 60    7/13/12 7:21a Rajeshms
// [TAG]  		EIP57005 
// [Category]  	Improvement
// [Description]  	Need to clear Struck Keys in StartKeyboard() &
// KbdReset() for some kinds of Notebook KBC. Implemented this feature
// based on CLEAR_PENDING_KEYS_IN_PS2 token.
// [Files]  		Ps2Kbd.c, CORE_DXE.sdl
// 
// 59    7/09/12 3:13a Rajeshms
// [TAG]  		EIP94186
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	side effect after adding the solution of can not catch F8
// key event on Keyboard - PS2 KB generic implement (EIP6986)
// [RootCause]  	BDA is Checked even when CSM is not launched. So even
// though keys are not pressed Junk Keys are reproted
// [Solution]  	Checked whether CSm is launched based of Presence of
// Legacy BIOS Protocol.
// [Files]  		Ps2Kbd.c
// 
// 58    5/31/12 7:56a Srilathasc
// [TAG]  		EIP89947
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Ps2Keyboard doesn't work after reconnect -r command from
// Shell
// [RootCause]  	The keyboard driver's stop function does not uninstall
// AMIEFIKEYCODE Protocol.
// [Solution]  	AMIEFIKEYCODE Protocol uninstalled in stop function. 
// [Files]  		ps2kbd.c
// 
// 57    5/24/12 6:49a Nimishsv
// [TAG]  		EIP90180
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Ps2driver doesn't return the proper ShiftState if the valid
// Unicode char's are pressed.
// [RootCause]  	Shift State was not cleared for printable characters
// [Solution]  	Shift state is cleared for printable characters
// [Files]  		ps2kbd.c
// 
// 56    5/02/12 2:29a Deepthins
// [TAG]  		EIP63116
// [Category]  	Improvement
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Ps2kbd.c, Mouse.c, kbc.h, kbc.c
// 
// 55    4/30/12 2:22a Rajeshms
// [TAG]  		EIP86986 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Can not detect F8 key on PS2 Keyboard while booting to EFI
// aware OS.
// [RootCause]  	Make code of F8 key (0x42) is taken by int09h and  EFI
// aware OS calls only one ReadKeyStroke() for any key catch, Now PS2
// driver will take Break Code of F8 key(0xC2) and returns EFI_NOT_READY.
// [Solution]  	Multiple Read from PS2 keyboard is implemented and read
// exits if any valid key is detected. Also, the BDA keyboard buffer is
// checked for any missed key in EFI.
// [Files]  		ps2kbd.c, kbc.c, CORE_DXE.sdl
// 
// 54    4/24/12 2:19a Deepthins
// [TAG]  		EIP85747 
// [Category]  	Improvement
// [Description]  	USB-ReadKeyStrokeEx is returning EFI_SUCCESS with
// KEY_STATE_EXPOSED for Caps, Num and Scroll Lock Key's.
// KEY_STATE_EXPOSED only for the ShiftState Key's and not for togglestate
// key's.
// [Files]  		Efiusbkb.c, ps2kbd.c and kbc.h
// 
// 53    4/23/12 8:52a Jittenkumarp
// [TAG]  		EIP84902 
// [Category]  	Bug Fix
// [Symptom]  	Enter key is not working in PS2 key board
// [RootCause]  	Filling wrong EFI KEY value in
// ScancodeToEfi_table.Therefor Enter key is interpreted wrongly as
// EfiKeyC12.
// [Solution]  	Replaced EfiKeyC12 value with EfiKeyEnter value to
// Interpreted Enter key properly.
// 
// [Files]  		ps2kbd.c
// 
// 52    4/10/12 2:35a Rameshr
// [TAG]  		EIP87058
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Not able to recognise Pause Key Click using ReadKeyStroke
// [RootCause]  	Pause Key detection should be done always and only the
// pause key action should be controlled by PAUSEKEY_SUPPORT SDL token
// [Solution]  	SDL token checking removed for the Pause Key detection
// [Files]  		Ps2kbd.c
// 
// 51    2/01/12 2:01a Deepthins
// [TAG]  		EIP63116
// [Category]  	New Feature
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Token.c, Ps2main.c, Ps2kbd.c, Mouse.c, kbc.h, kbc.c,
// CORE_DXE.sdl
// 
// 50    9/22/11 7:39a Rameshr
// [TAG]  		EIP63054
// [Category]  	New Feature
// [Description]  	0000790: Add warning to ReadKeyStrokeEx for partial key
// press
// [Files]  		KeyboardCommonDefinitions.h, In.c, Kbc.h, Ps2Kbd.c,
// Efiusbkb.c, efiusbkb.h
// 
// 49    6/21/11 12:24p Davidd
// [TAG]           EIP55334
// [Category]      New Feature
// [Description]   Add optional code to clear keyboard buffer at
// ReadyToBoot in PS2KB driver
// [Files]         core_dxe.sdl
//                 ps2kbd.c
// 
// 48    4/27/11 4:34a Lavanyap
// [TAG] - EIP49407
// [Category] - IMPROVEMENT
// [Description] - Move the Ps2 driver SDL tokens from Core Source to Core
// Bin,So that we don't need to add Core source for changing the Ps2
// driver SDL tokens.
// [Files] - Ps2Ctl.sdl, ps2kbd.c, ps2main.c, ps2ctl.h, kbc.c, mouse.c,
// hotkey.c, CORE_DXE.sdl, Tokens.c
// 
// 47    1/05/11 12:58a Rameshr
// [TAG]  		EIPEIP 35306
// [Category]  	Improvement
// [Description]  	Report the Ps2 Controller and Device Error Codes.
// [Files]  		AmiStatuscodes.h, Kbc.c, Kbc.h,Ps2ctl.sdl, ps2kbd.c,
// ps2main.c ,Statuscode.h
// 
// 46    8/23/10 4:21a Rameshr
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
// 45    8/19/10 8:08a Fredericko
// [TAG]    	  EIP40711 
// [Category]  BUG FIX
// [Severity]	  Normal
// [Symptom]  Keyboard sometimes does not work in DOS if KBD is being
// pressed hapazardly during post.
// [RootCause] After reprogramming of Interrupt Controller base; if
// keyboard is being pressed hapardzadly, KBD IRQ could be missed and KBD
// might not work in DOS.
// [Solution]	Follow proper procedures to Reset KBD controller after
// reprogramming the base of the Interrrupt controller
// [Files] Thunk.c in CSM
// 
// 44    7/20/10 4:31a Rameshr
// Corrected the FreePool call in UnRegisterKeyNotify function
// 
// 43    5/14/10 11:07a Olegi
// Added FreePool call in UnRegisterKeyNotify function.
//
// 42    5/10/10 1:50a Rameshr
// Issue:Shift Key issues in RegsiterkeyNotify function
// Solution: ShiftKeyState and KeyToggleState verified for
// RegisterKeyNotify callback function.
// EIP 38211
//
// 41    5/10/10 1:41a Rameshr
// PrintKey/SysRq key, Menu Key, Left Logo and Right Logo Key support
// added in Ps2 Keyboard driver
// EIP 38212
//
// 40    3/15/10 2:40p Krishnakumarg
// Pressing DEL key continously intermittently or sticking does not enter
// setup. EIP: 34615
//
// 39    1/29/10 2:11p Krishnakumarg
// When user press "Ctrl+Break" key, the Scr Lk LED will turn on - #EIP
// 34317
//
// 38    8/13/09 3:02p Rameshr
// When item "num-lock status" set off, Num-lock will keep open until in
// DOS.
// EIP:21757
//
// 37    7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
//
// 36    6/26/09 4:03p Rameshr
// Symptom: Shift Key Status get set when DELL key pressed more
// frequently.
// Reason: DELL key scan code E0 taken by Reset Function and Int9. This
// has been handled by modifiying Reset function and using BDA.
// EIP:22611
//
// 35    3/30/09 10:28a Pats
// Issue: EIP 19547 - Pause key support needed in Aptio
// Solution: Function HandleKBDData modified to pass EFI_KEY vaule of
// pause key on rather than rejecting it.
//
// 34    1/23/09 9:54a Rameshr
// Symptom:SCT failure in ReadKeystrokeEx function.
// Solution: Validated the Input parameters Keydata for the
// ReadKeystrokeEx Function.
// Eip: 19039
//
// 33    11/17/08 10:04a Rameshraju
// Problem:SCT failure on RegisterKeyNotify, SetState and
// UnregisterKeyNotify.
// Fix : Validated the input parameters for RegisterKeyNotify, SetState
// and UnregisterKeyNotify.
// EIP:17578
//
// 32    10/08/08 4:56p Olegi
// Implemented the Register/Unregister key notofocation function in
// SimpletextinEx protocol.
//
// 31    8/15/08 10:57a Olegi
// Correction in KbdReset function.
//
// 30    8/13/08 9:54a Olegi
// Change in KbdReset function, EIP#8330.
//
// 29    6/05/08 4:26p Olegi
// Added support for extended keys (EIP#13630)
//
// 28    6/05/08 3:19p Olegi
// Bugfix in processing the '5' key on a keypad when NumLock is off:
// nothing should be reported.
//
// 27    5/09/08 10:11a Olegi
// ProcessByte function modified
//
// 26    4/22/08 4:31p Felixp
// Additional progress codes added
//
// 25    4/21/08 5:49p Olegi
//
// 24    4/09/08 10:19a Olegi
// Changed the key attributes (modifiers and shift state) reporting.
//
// 23    10/25/07 4:48p Olegi
//
// 22    10/24/07 6:00p Olegi
//
// 21    10/23/07 4:04p Olegi
// Lock keys maintenance modifications.
//
// 20    9/18/07 11:51a Olegi
//
// 19    9/18/07 11:47a Olegi
//
// 18    9/17/07 3:56p Olegi
//
// 17    9/10/07 1:14p Olegi
//
// 16    9/07/07 4:34p Olegi
// EFI_KEY code implementation.
//
// 15    8/31/07 2:44p Olegi
// Added SimpleTextInEx definitions.
//
// 14    6/22/07 2:14p Pats
// Fixed problem of right Ctrl and Alt keys "sticking" and causing reset
// when Ctrl-Alt-Del pressed sequentially rather than all at once.
//
// 13    4/19/07 1:00p Felixp
// File reformatted to comply with AMI coding standards
//
// 11    4/17/07 10:34a Pats
// Modified to comply with coding standard. No code changes.
//
// 10    5/05/06 5:23p Ambikas
//
// 9     3/13/06 2:38a Felixp
//
// 8     1/09/06 11:38a Felixp
//
// 6     12/22/05 10:21a Srinin
// Optimized KBD Enable/Disable call
//
// 5     10/27/05 1:04p Srinin
// In KbdReset, KBD driver buffer is cleared.
//
// 4     10/11/05 4:09p Srinin
// KBD reset function implemented and other minor changes done.
//
// 3     8/30/05 1:08p Srinin
// KeyBoard buffer and handling of keys which send 4 scan codes modified.
//
// 2     3/04/05 3:55p Olegi
// Shift states corrected for non-letter keys.
//
// 1     2/01/05 1:10a Felixp
//
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 2     12/16/04 2:28p Olegi
// Fix: Caps-Lock made irrelevant to the upper row of keys.
//
// 1     10/28/04 10:19a Olegi
//
// 10    9/30/04 8:13a Olegi
// HotKeys added.
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: ps2kbd.c
//
// Description: PS/2 keyboard support routines
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "ps2ctl.h"
#include "kbc.h"


#define     E0_STATUS_IN_BDA        BIT1
#define     E1_STATUS_IN_BDA        BIT0
#define     LEGACY_8259_CONTROL_REGISTER_MASTER 0x20

#if CHECK_BDA_KEYBOARD_BUFFER
#if CSM_SUPPORT
#include <Protocol/LegacyBios.h>
UINT16      BdaSeg      = 0x400;
UINT16      *BdaKbdHead = (UINT16 *)0x41A;
UINT16      *BdaKbdTail = (UINT16 *)0x41C;
EFI_LEGACY_BIOS_PROTOCOL    *gLegacy=NULL;
BOOLEAN     gLegacyBiosProtocolFound = FALSE;
#endif
#endif

/*
Table 2. PS/2 Scan Codes Supported in Windows 2000/Windows XP and Windows Me

HID usage/ key name  Set 1Make  Set 1Break  Set 2Make  Set 2Break
 Scan Next Track       E0 19       E0 99       E0 4D     E0 F0 4D
 Scan Previous Track   E0 10       E0 90       E0 15     E0 F0 15
 Stop                  E0 24       E0 A4       E0 3B     E0 F0 3B
 Play/ Pause           E0 22       E0 A2       E0 34     E0 F0 34
 Mute                  E0 20       E0 A0       E0 23     E0 F0 23
 Volume Increment      E0 30       E0 B0       E0 32     E0 F0 32
 Volume Decrement      E0 2E       E0 AE       E0 21     E0 F0 21
 AL Email Reader       E0 6C       E0 EC       E0 48     E0 F0 48
 AC Search             E0 65       E0 E5       E0 10     E0 F0 10
 AC Home               E0 32       E0 B2       E0 3A     E0 F0 3A
 AC Back               E0 6A       E0 EA       E0 38     E0 F0 38
 AC Forward            E0 69       E0 E9       E0 30     E0 F0 30
 AC Stop               E0 68       E0 E8       E0 28     E0 F0 28
 AC Refresh            E0 67       E0 E7       E0 20     E0 F0 20
 AC Bookmarks          E0 66       E0 E6       E0 18     E0 F0 18
 AL Calculator*        E0 21       E0 A1       E0 2B     E0 F0 2B
 AL Local Browser*     E0 6B       E0 EB       E0 40     E0 F0 40
 AL Consumer Control Configuration*
                       E0 6D       E0 ED       E0 50     E0 F0 50
*/
static  UINT8 E0EnhancedKeys[] = {0x20,0x30,0x2E};  // only mute, volume-up, down
BOOLEAN IsEnhancedKey( UINT8 data)
{
    UINTN   i;

    data &= 0x7F;   // reset MSB
    for ( i = 0; i < sizeof(E0EnhancedKeys); i++) {
        if ( data == E0EnhancedKeys[i]) {
            return  TRUE;
        }
    }
    return  FALSE;
}

//----------------------------------------------------------------------

extern  BOOLEAN InsideGetMouseData;
extern  BOOLEAN KBDEnableState;
extern  UINT8   LedsAtStartup;
extern  BOOLEAN InsideMouseReset;
BOOLEAN InsideKbdReadKey = FALSE;
BOOLEAN InsideOnWaitingOnKey = FALSE;
BOOLEAN InsideKbdReset = FALSE;
extern BOOLEAN InsidePS2DataDispatcher;
static EFI_GUID gAmiMultiLangSupportGuid = AMI_MULTI_LANG_SUPPORT_PROTOCOL_GUID;
AMI_MULTI_LANG_SUPPORT_PROTOCOL *gPs2MultiLangSupportProtocol=NULL;

EFI_STATUS KbdReset(
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
    BOOLEAN ExtendedVerification);

EFI_STATUS KbdReadKey(
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
    EFI_INPUT_KEY *key);

EFI_STATUS KbdResetEx(
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
    BOOLEAN ExtendedVerification );

EFI_STATUS KbdReadKeyEx (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    OUT EFI_KEY_DATA *KeyData
);

EFI_STATUS KbdReadEfiKeyEx (
    IN AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA *KeyData
);

EFI_STATUS SetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState
);

EFI_STATUS RegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT EFI_HANDLE *NotifyHandle
);

EFI_STATUS UnRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
);

void OnWaitingOnKey(EFI_EVENT Event, void *Context);

#if CLEAR_PENDING_KEYS_IN_PS2
VOID Ps2KbdReset ( VOID );
VOID ClearOBF ( VOID );
#endif


typedef struct _KEY_WAITING_RECORD{
  DLINK                                         Link;
  EFI_KEY_DATA                                  Context;
  EFI_KEY_NOTIFY_FUNCTION                       Callback;
} KEY_WAITING_RECORD;

DLIST                               mPs2KeyboardData;
KEY_WAITING_RECORD                  *mPs2KeyboardRecord;
EFI_EVENT                           Ps2KeyEvent;
#define     KEY_POLLING_INTERVAL    500000
VOID StartPollingKey(EFI_EVENT Event, VOID *Context);


extern STATEMACHINEPROC DrivePS2KbdMachine;
void ReadAndProcessKey(void*);
void ProcessByte(KEYBOARD *Kbd, UINT8 data, BOOLEAN fourth_byte);
void ResetStateMachine(KEYBOARD *Kbd);
void LEDsOnOff(KEYBOARD* Kbd);

static UINT8 E0SeqA[4]  = {0x2A, 0xAA, 0x46, 0xB6};
static UINT8 E0SeqB[11] = {0xD3, 0xD0, 0xCF, 0xC7, 0xD2, 0xCB, 0xD1, 0xC9, 0xCD, 0xC8, 0xB5};
static UINT8 E1Seq[5]   = {0x1D, 0x45, 0xE1, 0x9D, 0xC5};

static UINT8 code_table[59] = { // Lower case keys
0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8,
9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 13,
0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'','`',
0,'\\','z','x','c','v','b','n','m',',','.','/',0,
'*', 0, ' ', 0};
static UINT8 Code_Table[59] = { // Upper case keys
0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 8,
9, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 13,
0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
'*', 0, ' ',0};

static UINT8 ScancodeToEfi_table[59] = { // EFI keys (UEFI Spec 2.1, Ch.28.4, Pg.1325)
0, EfiKeyEsc, EfiKeyE1, EfiKeyE2, EfiKeyE3,EfiKeyE4, EfiKeyE5, EfiKeyE6,
EfiKeyE7, EfiKeyE8, EfiKeyE9, EfiKeyE10, EfiKeyE11, EfiKeyE12, EfiKeyBackSpace,
EfiKeyTab, EfiKeyD1, EfiKeyD2, EfiKeyD3, EfiKeyD4, EfiKeyD5, EfiKeyD6, EfiKeyD7,
EfiKeyD8, EfiKeyD9, EfiKeyD10, EfiKeyD11, EfiKeyD12, EfiKeyEnter,
EfiKeyCapsLock, EfiKeyC1, EfiKeyC2, EfiKeyC3, EfiKeyC4, EfiKeyC5, EfiKeyC6, EfiKeyC7,
EfiKeyC8, EfiKeyC9, EfiKeyC10, EfiKeyC11, EfiKeyE0,
EfiKeyLShift, EfiKeyD13, EfiKeyB1, EfiKeyB2, EfiKeyB3, EfiKeyB4, EfiKeyB5, EfiKeyB6,
EfiKeyB7, EfiKeyB8, EfiKeyB9, EfiKeyB10, EfiKeyRshift,
0, 0, EfiKeySpaceBar, 0};

typedef struct {
    UINT8 makecode;
    UINT8 efi_scancode;
    UINT8 efi_key;
}EFI_EXTKEY;

static EFI_EXTKEY ScanCode_Table[] = {
    0x3B, EFI_SCAN_F1, EfiKeyF1,
    0x3C, EFI_SCAN_F2, EfiKeyF2,
    0x3D, EFI_SCAN_F3, EfiKeyF3,
    0x3E, EFI_SCAN_F4, EfiKeyF4,
    0x3F, EFI_SCAN_F5, EfiKeyF5,
    0x40, EFI_SCAN_F6, EfiKeyF6,
    0x41, EFI_SCAN_F7, EfiKeyF7,
    0x42, EFI_SCAN_F8, EfiKeyF8,
    0x43, EFI_SCAN_F9, EfiKeyF9,
    0x44, EFI_SCAN_F10, EfiKeyF10,
    0x57, EFI_SCAN_F11, EfiKeyF11,
    0x58, EFI_SCAN_F12, EfiKeyF12,
    0x47, EFI_SCAN_HOME, EfiKeyHome,
    0x48, EFI_SCAN_UP, EfiKeyUpArrow,
    0x49, EFI_SCAN_PGUP, EfiKeyPgUp,
    0x4B, EFI_SCAN_LEFT, EfiKeyLeftArrow,
    0x4D, EFI_SCAN_RIGHT, EfiKeyRightArrow,
    0x4F, EFI_SCAN_END, EfiKeyEnd,
    0x50, EFI_SCAN_DN, EfiKeyDownArrow,
    0x51, EFI_SCAN_PGDN, EfiKeyPgDn,
    0x52, EFI_SCAN_INS, EfiKeyIns,
    0x53, EFI_SCAN_DEL, EfiKeyDel,
    0xFF, 0xFF, 0xFF  // End of table
};

static UINT8 KeyPad_Table[] = {
    '7','8','9','-','4','5','6','+','1','2','3','0','.'
};

static UINT8 KeyPadEfiCode_Table[] = {
    EfiKeySeven, EfiKeyEight, EfiKeyNine, EfiKeyMinus,
    EfiKeyFour, EfiKeyFive, EfiKeySix, EfiKeyPlus,
    EfiKeyOne, EfiKeyTwo, EfiKeyThree,
    EfiKeyZero, EfiKeyPeriod
};

KEYBOARD                    gKbd;
KEYBOARD_IRQ_STORE          gKeyboardIrqBuffer;
EFI_CPU_ARCH_PROTOCOL       *gCpuArch;
EFI_LEGACY_8259_PROTOCOL    *mLegacy8259;
BOOLEAN                     gKeyboardIrqInstall=FALSE;
BOOLEAN                     gKeyboardDriverStart=FALSE;

extern	BOOLEAN             Ps2MouseDetected;
extern  BOOLEAN             KbdIrqSupport;
extern  BOOLEAN             KbRdBeforeInstall; 
extern  BOOLEAN             InsideGetMouseData;
extern  BOOLEAN             KBDEnableState;

#if CLEAR_PS2KB_BUFFER_AT_READYTOBOOT
EFI_EVENT	gClearKbBufferEvent;

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ClearKbBuffer
//
// Description:
//  This function clear PS2 KB buffer
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
ClearKbBuffer(
    IN EFI_EVENT	Event, 
    IN VOID 		*Context
)
{
    KEYBOARD	*Kbd = &gKbd;
	UINT8		*BdaKbHead = (UINT8*)((UINTN) 0x41a);
	UINT8		*BdaKbTail = (UINT8*)((UINTN) 0x41c);
	UINT8		*BdaKbBuffer = (UINT8*)((UINTN) 0x41e);

    Kbd->pBufHead = Kbd->pBufStart;
    Kbd->pBufTail = Kbd->pBufStart;

    pBS->SetMem(Kbd->pBufStart, BUFFER_SIZE * sizeof (AMI_EFI_KEY_DATA), 0);

	// Empty KB Buffer in BDA
    pBS->SetMem(BdaKbBuffer, 32, 0);
	*BdaKbTail = *BdaKbHead;

	pBS->CloseEvent(Event);

    return EFI_SUCCESS;
}
#endif


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: UpdateVariabletoCheckBda
//
// Description:
//  This function updates variable Legacy BIOS Protocol found,to check BDA
//  for pending keys in EFI.
//
// Input:   
//  IN EFI_EVENT Event - signalled event
//  IN VOID *Context - pointer to event context
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
#if CHECK_BDA_KEYBOARD_BUFFER
#if CSM_SUPPORT
VOID UpdateVariabletoCheckBda(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_STATUS Status;
    //
    // Update Variable to check BDA if Legacy Bios Protocol Found.
    //
    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &gLegacy);        
    if (!EFI_ERROR(Status)) {
        gLegacyBiosProtocolFound = TRUE;
    }
}
#endif
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       StartKeyboard
//
// Description:     This routine is called from Driver Binding Start function,
//                  it starts the keyboard
//
// Paremeters:      EFI_DRIVER_BINDING_PROTOCOL *This - A pointer to the
//                      EFI_DRIVER_BINDING_PROTOCOL instance
//                  EFI_HANDLE Controller - Handle for this controller
//
// Output:          EFI_STATUS - status of the operation
//
// Referrals:       gEfiSimpleTextInProtocolGuid
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS StartKeyboard(
    EFI_DRIVER_BINDING_PROTOCOL     *This,
    EFI_HANDLE                      Controller)
{

    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL *pDummyDevPath;
    KEYBOARD* Kbd = &gKbd;
    KEYBOARD_IRQ_STORE*         KbIrqBuffer = &gKeyboardIrqBuffer;
    UINT8                       Index=0;
#if CHECK_BDA_KEYBOARD_BUFFER
#if CSM_SUPPORT
    EFI_EVENT 	Event;
	VOID *pRegistration;
#endif
#endif

    if (EFI_ERROR(gSysTable->BootServices->OpenProtocol(
            Controller,
            &gEfiDevicePathProtocolGuid,
            &pDummyDevPath,
            This->DriverBindingHandle,
            Controller,
            EFI_OPEN_PROTOCOL_BY_DRIVER))) {
        return EFI_INVALID_PARAMETER;
    }

#if CLEAR_PENDING_KEYS_IN_PS2
    //
    // Reset the keyboard and Clear Pending Keys as some
    // NoteBook Kbc needs reset and Clearing the OBF.
    //
    Ps2KbdReset();
    ClearOBF ();
#endif

    DetectPS2KeyboardAndMouse();

    if (EFI_ERROR(DetectPS2Keyboard())) {
        gSysTable->BootServices->CloseProtocol(
            Controller,
            &gEfiDevicePathProtocolGuid,
            This->DriverBindingHandle,
            Controller);

        return EFI_DEVICE_ERROR;
    }

    //
    // Initialize keyboard interface functions
    //
    (Kbd->iSimpleIn).Reset = KbdReset;
    (Kbd->iSimpleIn).ReadKeyStroke = KbdReadKey;

    (Kbd->iSimpleInEx).Reset = KbdResetEx;
    (Kbd->iSimpleInEx).ReadKeyStrokeEx = KbdReadKeyEx;
    (Kbd->iSimpleInEx).SetState = SetState;
    (Kbd->iSimpleInEx).RegisterKeyNotify = RegisterKeyNotify;
    (Kbd->iSimpleInEx).UnregisterKeyNotify = UnRegisterKeyNotify;

    (Kbd->iKeycodeInEx).Reset = KbdResetEx;
    (Kbd->iKeycodeInEx).ReadEfikey = KbdReadEfiKeyEx;
    (Kbd->iKeycodeInEx).SetState = SetState;
    (Kbd->iKeycodeInEx).RegisterKeyNotify = RegisterKeyNotify;
    (Kbd->iKeycodeInEx).UnregisterKeyNotify = UnRegisterKeyNotify;

    gSysTable->BootServices->CreateEvent(
        EVT_NOTIFY_WAIT,
        TPL_NOTIFY,
        OnWaitingOnKey,
        Kbd,
        &Kbd->iSimpleIn.WaitForKey);

    gSysTable->BootServices->CreateEvent(
        EVT_NOTIFY_WAIT,
        TPL_NOTIFY,
        OnWaitingOnKey,
        Kbd,
        &Kbd->iSimpleInEx.WaitForKeyEx);

    gSysTable->BootServices->CreateEvent(
        EVT_NOTIFY_WAIT,
        TPL_NOTIFY,
        OnWaitingOnKey,
        Kbd,
        &Kbd->iKeycodeInEx.WaitForKeyEx);

    //
    // Install protocol interfaces for the keyboard device.
    //
    Status = gSysTable->BootServices->InstallMultipleProtocolInterfaces (
        &Controller,
        &gEfiSimpleTextInProtocolGuid, &Kbd->iSimpleIn,
        &gEfiSimpleTextInExProtocolGuid, &Kbd->iSimpleInEx,
        &gAmiEfiKeycodeProtocolGuid, &Kbd->iKeycodeInEx,
        NULL
    );

    if (EFI_ERROR(Status)) {
        gSysTable->BootServices->CloseProtocol(
            Controller,
            &gEfiDevicePathProtocolGuid,
            This->DriverBindingHandle,
            Controller);

        gSysTable->BootServices->CloseEvent(Kbd->iSimpleIn.WaitForKey);
        gSysTable->BootServices->CloseEvent(Kbd->iSimpleInEx.WaitForKeyEx);
        gSysTable->BootServices->CloseEvent(Kbd->iKeycodeInEx.WaitForKeyEx);
    }

    if (!(EFI_ERROR(Status))) {
        //
        // Initialize keyboard device
        //
        Kbd->KeyIsReady = FALSE;
        Kbd->ScannerState = KBST_READY;
        Kbd->KeyData.KeyState.KeyToggleState = LedsAtStartup;
        Kbd->KeyData.KeyState.KeyToggleState |= TOGGLE_STATE_VALID;
        Kbd->KeyData.KeyState.KeyShiftState = SHIFT_STATE_VALID;

        Kbd->pBufStart = MallocZ(BUFFER_SIZE * sizeof (AMI_EFI_KEY_DATA));
        if(!Kbd->pBufStart) return EFI_OUT_OF_RESOURCES;
        Kbd->pBufHead = Kbd->pBufStart;
        Kbd->pBufTail = Kbd->pBufStart;
        Kbd->pBufEnd = Kbd->pBufStart + BUFFER_SIZE;

        DrivePS2KbdMachine = ReadAndProcessKey;

        //
        // Set LED's
        //
        LEDsOnOff(Kbd);

        InitHotKeys(Controller);                // Produce HotKeys protocol

//      for (Count = 3; Count; Count--) {
//          if(IssueCommand(0xF4) == 0xFA) break;       // Clear the KBD buffer
//      }

        Kbd->LEDCommandState = 0;

#if CLEAR_PS2KB_BUFFER_AT_READYTOBOOT
	    gSysTable->BootServices->CreateEvent(
						            EFI_EVENT_SIGNAL_READY_TO_BOOT,
						            TPL_NOTIFY,
						            ClearKbBuffer,
						            NULL,
						            &gClearKbBufferEvent);
#endif

#if CHECK_BDA_KEYBOARD_BUFFER
#if CSM_SUPPORT
        RegisterProtocolCallback(
		&gEfiLegacyBiosProtocolGuid, UpdateVariabletoCheckBda,
		NULL, &Event,&pRegistration
	    );
        
        //
        // Check whether Legacy BIOS Protocol Installed.
        //
        UpdateVariabletoCheckBda(NULL,NULL);        

#endif
#endif
    }

    DListInit(&mPs2KeyboardData);

    Status = pBS->CreateEvent(
                    EVT_TIMER | EFI_EVENT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    StartPollingKey,
                    Kbd,
                    &Ps2KeyEvent
    );

    //
    // if before keyboard driver starts data is available in buffer
    // it will be collected in local buffer in KeyboardInterrupt?Handler
    // only if KBD_READ_BEFORE_INSTALL = 1, the avalable data in local 
    // buffer is processed.
    //
    if(KbRdBeforeInstall){
        for (Index=0;Index < KbIrqBuffer->KbdIndex; Index++){
            ProcessKBDData(Kbd, KbIrqBuffer->KbdBuffer[Index]);
        }
    }
    gKeyboardDriverStart = TRUE;
    //
    // Re enable keyboard irq as it was previously disabled.
    // if KBD_READ_BEFORE_INSTALL = 0 then initialize keyboard irq here
    //
    if(KbdIrqSupport){
        if(KbRdBeforeInstall){   
            gKeyboardIrqInstall = TRUE;
            //
            // Now enable the interrupt
            //
            mLegacy8259->EnableIrq(mLegacy8259, SYSTEM_KEYBOARD_IRQ, FALSE);
        }
        else {
            InitKeyboardIrq();
        }
    }
    //
    // Enable the Keyboard and Keyboard Interrupt. We must initilize this  
    // one for the Keyboard to work on Legacy mode. And also Legacy mode AMIUSB driver 
    // expects Keyboard and Interrupt should be enabled once Port 60/64 is present.
    //
    Write8042CommandByte(0x65);
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       StopKeyboard
//
// Description:     This routine is called from Driver Binding Stop function.
//
// Paremeters:      EFI_DRIVER_BINDING_PROTOCOL *This - A pointer to the
//                      EFI_DRIVER_BINDING_PROTOCOL instance
//                  EFI_HANDLE Controller - Handle for this controller
//
// Output:          EFI_STATUS - status of the operation
//
// Referrals:       gEfiSimpleTextInProtocolGuid
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS StopKeyboard(
    EFI_DRIVER_BINDING_PROTOCOL     *This,
    EFI_HANDLE                      Controller)
{
    KEYBOARD* Kbd = &gKbd;
    EFI_STATUS Status;

    //
    // Uninstall protocol interfaces from the keyboard device.
    //
    Status = gSysTable->BootServices->UninstallMultipleProtocolInterfaces (
        Controller,
        &gEfiSimpleTextInProtocolGuid, &Kbd->iSimpleIn,
        &gEfiSimpleTextInExProtocolGuid, &Kbd->iSimpleInEx,
        &gAmiEfiKeycodeProtocolGuid, &Kbd->iKeycodeInEx,
        NULL
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Close protocols that is open during Start
    //
    Status = gSysTable->BootServices->CloseProtocol(
        Controller,
        &gEfiDevicePathProtocolGuid,
        This->DriverBindingHandle,
        Controller);

    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Kill wait event
    //
    gSysTable->BootServices->CloseEvent(Kbd->iSimpleIn.WaitForKey);
    gSysTable->BootServices->CloseEvent(Kbd->iSimpleInEx.WaitForKeyEx);
    gSysTable->BootServices->CloseEvent(Kbd->iKeycodeInEx.WaitForKeyEx);
    gSysTable->BootServices->CloseEvent(Ps2KeyEvent);

    pBS->FreePool(Kbd->pBufStart);


    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       KbdReset
//
// Description:     Resets the input device hardware. This routine is a part
//                  of SimpleTextIn protocol implementation.
//
// Parameters:      EFI_SIMPLE_TEXT_INPUT_PROTOCOL
//                  *This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL
//                  instance.
//                  BOOLEAN
//                  ExtendedVerification - Indicates that the driver may
//                  perform a more exhaustive verification operation of the
//                  device during reset.
//
// Output:          EFI_SUCCESS The device was reset.
//                  EFI_DEVICE_ERROR The device is not functioning correctly
//                  and could not be reset.
//
// Modified:        KBDEnableState
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS KbdReset(
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
    BOOLEAN                         ExtendedVerification )
{
    UINT8   bCount, bData, bBCount;
    KEYBOARD* Kbd = &gKbd;
    EFI_STATUS Status;

    //
    // Check for keyboard IRQ support
    //
    if(KbdIrqSupport && gKeyboardIrqInstall) {
        //
        // Now Disable the interrupt
        //
        mLegacy8259->DisableIrq(mLegacy8259, SYSTEM_KEYBOARD_IRQ);
    }
    InsideKbdReset = TRUE;
    Kbd->KeyIsReady = FALSE;
    Kbd->ScannerState = KBST_READY;

    Kbd->pBufHead = Kbd->pBufStart;
    Kbd->pBufTail = Kbd->pBufStart;

    pBS->SetMem(Kbd->pBufStart, BUFFER_SIZE * sizeof (AMI_EFI_KEY_DATA), 0);

    DisableKeyboard();
    PROGRESS_CODE(DXE_KEYBOARD_RESET);
  
    for (bBCount = 0; bBCount < 4; bBCount++) {
        for (bCount = 0; bCount < 3; bCount++) {
            Status = ReadDevice(KBD_DISABLE_SCANNING, &bData, KB_ACK_COM);
            if (!EFI_ERROR(Status)) {
                break;
            }
        }
        if (EFI_ERROR(Status)) {
            continue;
        }
        for (bCount = 0; bCount < 3; bCount++) {
            Status = ReadDevice(KBD_ENABLE_SCANNING, &bData, KB_ACK_COM);
            if (!EFI_ERROR(Status)) {
                break;
            }
        }
        if (!EFI_ERROR(Status)) {
            break;
        }
    }
    //
    // Report the Buffer FULL error code if there is failure.
    //
    if (EFI_ERROR(Status)) {
        ERROR_CODE (DXE_KEYBOARD_BUFFER_FULL_ERROR, EFI_ERROR_MAJOR);
    }
    
    KBDEnableState = FALSE;
    Status = EnableKeyboard();
    
    if (EFI_ERROR(Status)) {
        //
        // Report the KBC Controller error code.
        //
        ERROR_CODE (DXE_KEYBOARD_CONTROLLER_ERROR, EFI_ERROR_MAJOR);
    }

#if CLEAR_PENDING_KEYS_IN_PS2
    //
    // Clear OBF as some Notebook KBC has some keys even after
    // disabling and enabling scanning.
    //
    ClearOBF ();
#endif
                                           
    if(!gKeyboardIrqInstall){
        LEDsOnOff(Kbd);
    }

    Kbd->LEDCommandState = 0;
    InsideKbdReset = FALSE;

    if(KbdIrqSupport && gKeyboardIrqInstall) {
        

        //
        // Now enable the interrupt
        //
        mLegacy8259->EnableIrq(mLegacy8259, SYSTEM_KEYBOARD_IRQ, FALSE);
    }

    return EFI_SUCCESS;

}


EFI_STATUS KbdResetEx(
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
    BOOLEAN ExtendedVerification )
{
    return KbdReset(0, ExtendedVerification);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       KbdReadKey
//
// Description:     Reads the next keystroke from the input device. This
//                  routine is a part of SimpleTextIn protocol
//                  implementation.
//
// Paremeters:      EFI_SIMPLE_TEXT_INPUT_PROTOCOL
//                  This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL
//                      instance.
//                  EFI_INPUT_KEY
//                  InputKey -  A pointer to a buffer that is to be filled in
//                      with the keystroke information for the key that was
//                      pressed.
//
// Output:          EFI_SUCCESS - The keystroke information was returned.
//                  EFI_NOT_READY - There was no keystroke data available.
//                  EFI_DEVICE_ERROR - The keystroke information was not
//                      returned due to hardware errors.
//
// Modified:        InsideKbdReadKey
//
// Referral(s):     InsideGetMouseData, InsideGetMouseData,
//                  InsideOnWaitingOnKey
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS KbdReadKey(
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
    EFI_INPUT_KEY                   *InputKey )
{
    KEYBOARD* Kbd = &gKbd;

    if (InsideGetMouseData || InsideKbdReadKey || InsideOnWaitingOnKey || InsideKbdReset || InsideMouseReset) {
        return GetKeyFromBuffer (Kbd, (VOID*)InputKey, sizeof(EFI_INPUT_KEY));
    }

    InsideKbdReadKey = TRUE;

    PS2DataDispatcher(This);

    InsideKbdReadKey = FALSE;

#if CHECK_BDA_KEYBOARD_BUFFER
#if CSM_SUPPORT
    if( gLegacyBiosProtocolFound ) {
        if (!CheckKeyinBuffer(Kbd)) {
            if( *BdaKbdHead != *BdaKbdTail ) {
                ProcessKBDData (Kbd, *((UINT8 *)(*BdaKbdHead + BdaSeg + 1)));            
                *BdaKbdHead += 2;
                if(*BdaKbdHead == 0x3E) {
                    *BdaKbdHead = 0x1E;
                }
            }
        }
    }
#endif
#endif

    return GetKeyFromBuffer (Kbd, (VOID*)InputKey, sizeof(EFI_INPUT_KEY));

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       KbdReadKeyEx
//
// Description:     Reads the next keystroke from the input device. This
//                  routine is a part of SimpleTextInEx protocol
//                  implementation.
//
// Paremeters:      EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
//                  *This - A pointer to the EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
//                      instance.
//
// Output:          EFI_INPUT_KEY
//                  *key -  A pointer to a buffer that is filled in with the
//                          keystroke state data for the key that was pressed.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
KbdReadKeyEx (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    OUT EFI_KEY_DATA *KeyData
)
{
    EFI_STATUS Status;
    KEYBOARD *Kbd = &gKbd;

    if(KeyData == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    if (!InsideGetMouseData && !InsideKbdReadKey && !InsideOnWaitingOnKey && !InsideKbdReset && !InsideMouseReset) {
        InsideKbdReadKey = TRUE;
        PS2DataDispatcher(This);
        InsideKbdReadKey = FALSE;
    }

#if CHECK_BDA_KEYBOARD_BUFFER
#if CSM_SUPPORT
    if( gLegacyBiosProtocolFound ) {
        if (!CheckKeyinBuffer(Kbd)) {
            if( *BdaKbdHead != *BdaKbdTail ) {
                ProcessKBDData (Kbd, *((UINT8 *)(*BdaKbdHead + BdaSeg + 1)));            
                *BdaKbdHead += 2;
                if(*BdaKbdHead == 0x3E) {
                    *BdaKbdHead = 0x1E;
                }
            }
        }
    }
#endif
#endif

    Status = GetKeyFromBuffer (Kbd, (VOID*)KeyData, sizeof(EFI_KEY_DATA));
    if (EFI_ERROR(Status)) {

        pBS->SetMem(KeyData, sizeof (EFI_KEY_DATA), 0);
        //
        // Check the partial Key. If found return Success with NULL data 
        // in EFI_INPUT_KEY.
        //
        Status=CheckPartialKey(Kbd, (EFI_KEY_DATA*)KeyData);
        return Status;
    }

    return EFI_SUCCESS;
}

EFI_STATUS KbdReadEfiKeyEx (
    IN AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA *KeyData
)
{
    EFI_STATUS Status;
    KEYBOARD *Kbd = &gKbd;

    if (!InsideGetMouseData && !InsideKbdReadKey && !InsideOnWaitingOnKey && !InsideKbdReset && !InsideMouseReset) {
        InsideKbdReadKey = TRUE;
        PS2DataDispatcher(This);
        InsideKbdReadKey = FALSE;
    }


#if CHECK_BDA_KEYBOARD_BUFFER
#if CSM_SUPPORT
    if( gLegacyBiosProtocolFound ) {        
        //
        // If there is no key, check whether any key is present BDA Keyboard buffer as 
        // we may miss any key in legacy mode.
        //
        if (!CheckKeyinBuffer(Kbd)) {
            if( *BdaKbdHead != *BdaKbdTail ) {
                //
                // Get the scan code from BDA keyboard buffer and process it.
                //
                ProcessKBDData (Kbd, *((UINT8 *)(*BdaKbdHead + BdaSeg + 1)));            
                *BdaKbdHead += 2;
                //
                // Check whether we have reached end of circular buffer, if reached initialize
                // header to beginning of the buffer.
                //
                if(*BdaKbdHead == 0x3E) {
                    *BdaKbdHead = 0x1E;
                }
            }
        }
    }
#endif
#endif

    Status = GetKeyFromBuffer (Kbd, (VOID*)KeyData, sizeof(AMI_EFI_KEY_DATA));
    if (EFI_ERROR(Status)) {
        pBS->SetMem(KeyData, sizeof (AMI_EFI_KEY_DATA), 0);
        //
        // Check the partial Key. If found return Success with NULL data 
        // in EFI_INPUT_KEY.
        //
        Status=CheckPartialKey(Kbd, (EFI_KEY_DATA*)KeyData);
        return Status;
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SetState
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
SetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState
)
{
    BOOLEAN ChgSL = FALSE;
    BOOLEAN ChgCL = FALSE;
    BOOLEAN ChgNL = FALSE;

    KEYBOARD* Kbd = &gKbd;

    if(KeyToggleState == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(*KeyToggleState & TOGGLE_STATE_VALID) ||
        ((*KeyToggleState & (~(TOGGLE_STATE_VALID | KEY_STATE_EXPOSED | 
                            SCROLL_LOCK_ACTIVE | NUM_LOCK_ACTIVE | CAPS_LOCK_ACTIVE)))) ) {
        return EFI_UNSUPPORTED;
    }


    ChgSL = ((*KeyToggleState & SCROLL_LOCK_ACTIVE)!=0) ^ ((Kbd->KeyData.KeyState.KeyToggleState & SCROLL_LOCK_ACTIVE)!=0);
    ChgNL = ((*KeyToggleState & NUM_LOCK_ACTIVE)!=0) ^ ((Kbd->KeyData.KeyState.KeyToggleState & NUM_LOCK_ACTIVE)!=0);
    ChgCL = ((*KeyToggleState & CAPS_LOCK_ACTIVE)!=0) ^ ((Kbd->KeyData.KeyState.KeyToggleState & CAPS_LOCK_ACTIVE)!=0);

    if (ChgSL || ChgCL || ChgNL) {
        Kbd->KeyData.KeyState.KeyToggleState &= ~(SCROLL_LOCK_ACTIVE | NUM_LOCK_ACTIVE | CAPS_LOCK_ACTIVE);

        if (*KeyToggleState & SCROLL_LOCK_ACTIVE) Kbd->KeyData.KeyState.KeyToggleState |= SCROLL_LOCK_ACTIVE;
        if (*KeyToggleState & NUM_LOCK_ACTIVE) Kbd->KeyData.KeyState.KeyToggleState |= NUM_LOCK_ACTIVE;
        if (*KeyToggleState & CAPS_LOCK_ACTIVE) Kbd->KeyData.KeyState.KeyToggleState |= CAPS_LOCK_ACTIVE;

        LEDsOnOff(Kbd);
    }

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:       StartPollingKey
//
// Description:     Get the keys from the keyboard controller
//
// Paremeters:      IN EFI_EVENT  Event      event that has been signaled
//                  IN VOID       *Context
//
// Output:          None
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID StartPollingKey(EFI_EVENT Event, VOID *Context)
{
    if (!InsideGetMouseData && !InsideKbdReadKey && !InsideOnWaitingOnKey && !InsideKbdReset && !InsideMouseReset) {
        InsideKbdReadKey = TRUE;
        PS2DataDispatcher(Context);
        InsideKbdReadKey = FALSE;
    }
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CheckKeyNotify
//
// Description:     Call the notification function based on the key pressed
//
// Input:           Key - Key pressed
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
CheckKeyNotify(AMI_EFI_KEY_DATA *Key)
{

    KEY_WAITING_RECORD *Ps2KeyIn = OUTTER(mPs2KeyboardData.pHead, Link, KEY_WAITING_RECORD);
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

    // if the list is empty return the status that was passed in
    if (Ps2KeyIn == NULL)
        return EFI_SUCCESS;

    // check for a handle that was already identified
    while ( Ps2KeyIn != NULL)
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
        if (Ps2KeyIn->Context.Key.ScanCode != 0) {
            if( Ps2KeyIn->Context.Key.ScanCode == Key->Key.ScanCode) {
                KeyScanCodeMatch=TRUE;
            }
        } else {
            KeyScanCodeMatch=TRUE;
        }

        //
        // Check the Uncide Code Matching
        //

        if(Ps2KeyIn->Context.Key.UnicodeChar == Key->Key.UnicodeChar) {
            KeyUniCodeMatch=TRUE;
        }

        if(Ps2KeyIn->Context.KeyState.KeyShiftState & SHIFT_STATE_VALID){

            //
            // Check the ShiftKey Matching. Left Shift Key is matched with
            // Left or Right Shift Key. Same for Right Shift Key
            //
            if (Ps2KeyIn->Context.KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED)) {
                if(Key->KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED)) {
                    ShiftKeyMatch=TRUE;
                }
            } else {
                ShiftKeyMatch=TRUE;
            }

            //
            // Check the Ctrl Matching. Left Ctrl Key is matched with
            // Left or Right Ctrl Key. Same for Right Ctrl Key
            //
            if (Ps2KeyIn->Context.KeyState.KeyShiftState & (RIGHT_CONTROL_PRESSED | LEFT_CONTROL_PRESSED)) {
                if(Key->KeyState.KeyShiftState & (RIGHT_CONTROL_PRESSED | LEFT_CONTROL_PRESSED)) {
                    CtrlKeyMatch=TRUE;
                }
            } else {
                CtrlKeyMatch=TRUE;
            }

            //
            // Check the Alt Matching. Left Alt Key is matched with
            // Left or Right Alt Key. Same for Right Alt Key
            //
            if (Ps2KeyIn->Context.KeyState.KeyShiftState & (RIGHT_ALT_PRESSED | LEFT_ALT_PRESSED)) {
                if(Key->KeyState.KeyShiftState & (RIGHT_ALT_PRESSED | LEFT_ALT_PRESSED)) {
                    AltKeyMatch=TRUE;
                }
            } else {
                AltKeyMatch=TRUE;
            }

            //
            // Check the Logo Matching. Left Logo Key is matched with
            // Left or Right Logo Key. Same for Right Logo Key
            //
            if (Ps2KeyIn->Context.KeyState.KeyShiftState & (RIGHT_LOGO_PRESSED | LEFT_LOGO_PRESSED)) {
                if(Key->KeyState.KeyShiftState & (RIGHT_LOGO_PRESSED | LEFT_LOGO_PRESSED)) {
                    LogoKeyMatch=TRUE;
                }
            } else {
                LogoKeyMatch=TRUE;
            }

            //
            // Check the Menu Key Matching
            //
            if (Ps2KeyIn->Context.KeyState.KeyShiftState & MENU_KEY_PRESSED) {
                if(Key->KeyState.KeyShiftState & MENU_KEY_PRESSED) {
                    MenuKeyMatch=TRUE;
                }
            } else {
                MenuKeyMatch=TRUE;
            }

            //
            // Check the SysRq Key Matching
            //
            if (Ps2KeyIn->Context.KeyState.KeyShiftState & SYS_REQ_PRESSED) {
                if(Key->KeyState.KeyShiftState & SYS_REQ_PRESSED) {
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
        if(Ps2KeyIn->Context.KeyState.KeyToggleState & TOGGLE_STATE_VALID){
            if(Ps2KeyIn->Context.KeyState.KeyToggleState == Key->KeyState.KeyToggleState) {
                KeyToggleKeyMatch=TRUE;
            }
        } else {
            KeyToggleKeyMatch=TRUE;
        }

        //
        // If everything matched, call the callback function.
        //
        if(KeyScanCodeMatch & KeyUniCodeMatch & KeyShiftCodeMatch & KeyToggleKeyMatch) {
            //Call the notification function
            //
            Ps2KeyIn->Callback(&Ps2KeyIn->Context);
        }
        // go to the next element in the list
        Ps2KeyIn = OUTTER(Ps2KeyIn->Link.pNext, Link, KEY_WAITING_RECORD);
    }

    // if it is a new handle return the status pass in
    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       RegisterKeyNotify
//
// Description:     Register the callback function for the specific Key
//
// Input:           This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
//                          instance.
//                  KeyData - Key value
//                  KeyNotificationFunction- Pointer to the Notification Function
//                  NotificationHandle - Handle to be unregisterd
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
RegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT EFI_HANDLE *NotifyHandle
)
{
    EFI_STATUS                  Status;


    if(KeyData == NULL || KeyNotificationFunction == NULL || NotifyHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Create database record and add to database
    //
    Status = pBS->AllocatePool (
                      EfiRuntimeServicesData,
                      sizeof (KEY_WAITING_RECORD),
                      &mPs2KeyboardRecord
                      );

    if(EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Gather information about the registration request
    //

    mPs2KeyboardRecord->Context   = *KeyData;
    mPs2KeyboardRecord->Callback  = KeyNotificationFunction;

    DListAdd (&mPs2KeyboardData, &(mPs2KeyboardRecord->Link));

    //
    // Child's handle will be the address linked list link in the record
    //
    *NotifyHandle = (EFI_HANDLE) (&mPs2KeyboardRecord->Link);

    if(mPs2KeyboardData.Size == 1) {
        pBS->SetTimer(Ps2KeyEvent,
                        TimerPeriodic,
                        KEY_POLLING_INTERVAL);
    }

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UnRegisterKeyNotify
//
// Description:     Unregister the callback function
//
// Input:          This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
//                          instance.
//                  NotificationHandle - Handle to be unregisterd
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
UnRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
)
{

    DLINK               *ListPtr;
    KEY_WAITING_RECORD  *Ps2KeyIn;

    if(NotificationHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    ListPtr = mPs2KeyboardData.pHead;
    while ( ListPtr != NULL)
    {
        Ps2KeyIn = OUTTER(ListPtr, Link, KEY_WAITING_RECORD);
        if ( (&Ps2KeyIn->Link) == NotificationHandle)
        {
            DListDelete(&mPs2KeyboardData, ListPtr);
            pBS->FreePool(Ps2KeyIn);
            break;
        }

        ListPtr = ListPtr->pNext;
    }

    if(ListPtr == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if(mPs2KeyboardData.Size == 0) {
        pBS->SetTimer(Ps2KeyEvent,
                        TimerCancel,
                        0);
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       OnWaitingOnKey
//
// Description:     Callback for the EFI_SIMPLE_TEXT_INPUT_PROTOCOL.WaitForKey
//                  event;
//                  checks whether the new key is available and if so -
//                  signals the event.
//
// Input:           EFI_EVENT Event - Event to signal
//                  void Context - Event specific context (pointer to Kbd
//                      device)
//
// Output:          None
//
// Modified:        InsideOnWaitingOnKey
//
// Referrals:       InsideGetMouseData, InsideKbdReadKey,
//                  InsideOnWaitingOnKey
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
OnWaitingOnKey (
    EFI_EVENT   Event,
    VOID        *Context )
{

    if (InsideGetMouseData || InsideKbdReadKey || InsideOnWaitingOnKey || InsideKbdReset || InsideMouseReset) {
        if (CheckKeyinBuffer((KEYBOARD*)Context)) gSysTable->BootServices->SignalEvent(Event);
        return;
    }

    InsideOnWaitingOnKey = TRUE;

    PS2DataDispatcher(Context); // Process new keys if available

    InsideOnWaitingOnKey = FALSE;

    if (CheckKeyinBuffer((KEYBOARD*)Context))
    {
        gSysTable->BootServices->SignalEvent(Event);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ReadAndProcessKey
//
// Description:     PS2 keyboard keys processor, called from main PS2
//                  dispatcher.
//                  It gets the key from KBC output buffer and calls
//                  HandleKBDData.
//
// Paremeters:      void *Context - keyboard device pointer
//
// Output:          None
//
// Notes:           PS2 output buffer has data, incoming key is processed,
//                  Context->KeyIsReady is updated.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ReadAndProcessKey (
    VOID    *Context )
{

    KEYBOARD *Kbd = &gKbd;
    UINT8 data;

    data = KBCGetData();
    ProcessKBDData (Kbd, data);
    return;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ProcessKBDData
//
// Description:     If key is ready, processes any hotkey, and inserts key
//                  in buffer
//
// Parameters:
//      KEYBOARD    *Kbd - Pointer to key buffer
//      UINT8       data - Key data
//
// Output:          None
//
// Notes:           Incoming key is processed, Context->KeyIsReady is updated
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ProcessKBDData (
    KEYBOARD    *Kbd,
    UINT8       data
)
{
    EFI_KEY_DATA    DummyKey;

    HandleKBDData(Kbd, data);
    if (Kbd->KeyIsReady) {

        ProcessHotKey(Kbd->KeyData.PS2ScanCode,
            (UINT16)Kbd->KeyData.KeyState.KeyShiftState);
        InsertKeyToBuffer(Kbd, &Kbd->KeyData);
        Kbd->KeyIsReady = FALSE;
    } else {
        if (Kbd->KeyData.Key.ScanCode == 0 && Kbd->KeyData.Key.UnicodeChar == 0 && Kbd->ScannerState == KBST_READY ) {
            //
            // If the Key ShiftState has valid key, report as Partial Key
            //
            if ((Kbd->KeyData.KeyState.KeyShiftState & ~SHIFT_STATE_VALID) != 0) {

                pBS->CopyMem(&DummyKey, &Kbd->KeyData, sizeof(EFI_KEY_DATA)); 
                DummyKey.KeyState.KeyToggleState |= KEY_STATE_EXPOSED;
                CheckKeyNotify((AMI_EFI_KEY_DATA*)&DummyKey);
            }
        }
    }
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       HandleKBDData
//
// Description:     Processes the input data. If a callback function is
//                  associated with the key, then it is executed.
//
// Paremeters:
//      KEYBOARD    *Kbd - Pointer to key buffer
//      UINT8       data - Key data
//
// Output:          None
//
//
// Notes:           This routine can be called re-entrantly from LEDsOnOff(OutToKb)
//                  e.g. when Numlock and Del is pressed continously.
//                  Incoming key is processed, Context->KeyIsReady is updated.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
HandleKBDData (
    KEYBOARD    *Kbd,
    UINT8       data )
{
    //
    // PS2 keyboard could send one, two, four or six bytes in a row.
    // Kbd->ScannerState is ST_READY if it is the first byte
    //
    if (Kbd->ScannerState == KBST_READY)
    {
        switch (data) {
            case 0xE0:
                Kbd->ScannerState = KBST_E0;
                break;
            case 0xE1:
                Kbd->ScannerState = KBST_E1;
                break;
            default:
                ProcessByte(Kbd, data, FALSE);
        }
        return;
    }
    else    // Multi-byte sequence is being processed
    {
        if (Kbd->ScannerState == KBST_E1)   // Processing E1 state
        {
            if (data != E1Seq[Kbd->Count]) {    // Wrong byte in a sequence
                ResetStateMachine(Kbd);
                return;
            }
            //
            // E1 sequence data is correct, proceed
            //
            if  (Kbd->Count == 2) { // The ONLY 2-key sequence starting with E1 is Pause
                Kbd->KeyData.EfiKey = EfiKeyPause;
                Kbd->KeyIsReady = TRUE;
                ResetStateMachine(Kbd);
                return;
            }
            if  (Kbd->Count == 4) { // E1 sequence has finished
                ProcessByte(Kbd, data, FALSE);
                ResetStateMachine(Kbd);
                return;
            }
            //
            // E1 sequence is not complete, update the counter and return
            //
            Kbd->Count++;
            return;
        }
        else    // Kbd->ScannerState == ST_E0 - processing E0 state
        {

            //
            // For E0 state the Count values will be:
            //   0 for 1st and 2nd byte
            //   2 for 3rd byte (if available)
            //   1 for 4th byte (if available)
            // No validity checking will be done for 2nd,3rd and 4th bytes
            //

        if (Kbd->ScannerState == KBST_E0) {
            if ( IsEnhancedKey( data)) {
                ResetStateMachine(Kbd);
                return;
            }
            // Processing E0 state, if data is 2A or AA or MSB bit is
            // set (break key) ignore it.
            if  (data == 0x2A || data == 0xAA || data & 0x80 && \
                // except in special case of alt, ctrl, Print key, Left Logo, Right Logo and Menu Key
                 data != 0xb8 && data != 0x9d && data != 0xB7 && \
                 data != 0xDB && data != 0xDC && data != 0xDD) {
                ResetStateMachine(Kbd);
                return;
            }
            else {
                ProcessByte(Kbd, data, TRUE);
                ResetStateMachine(Kbd);
                return;
            }
        }
        ProcessByte(Kbd, data, FALSE);
        ResetStateMachine(Kbd);
        return;

        }
    }
}



void ResetStateMachine(KEYBOARD *Kbd)
{
    Kbd->ScannerState = KBST_READY;
    Kbd->Count = 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       IsLetter
//
// Description:     Returns TRUE if the given make code belongs to the
//                  alphabetical symbol, otherwise returns FALSE.
//
// Paremeters:      UINT8 data - The character to test
//
// Output:          BOOLEAN - True if character is letter
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
IsLetter (
    UINT8   data )
{
    if ((data >= 0x10 && data <= 0x19) ||   // Q...P
        (data >= 0x1E && data <= 0x26) ||   // A...L
        (data >= 0x2C && data <= 0x32)) {   // Z...M
        return TRUE;
    }
    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ProcessByte
//
// Description:     Checks for valid key, updates key modifiers, keyboard
//                  queue head and tail as well as Kbd->KeyIsReady field.
//
// Input:           KEYBOARD *Kbd - A pointer to the KEYBOARD device.
//                  UINT8 data - byte to process
//                  BOOLEAN long_sequence - the indication of whether it is a
//                  4 byte sequence or not; used to differentiate Shift keys
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ProcessByte (
    KEYBOARD    *Kbd,
    UINT8       Data,
    BOOLEAN     long_sequence )
{
    BOOLEAN bUpperCase, bShifted;
    EFI_EXTKEY *extkey;
    static BOOLEAN Make_Capslock = FALSE, Make_SCRLOCK = FALSE, Make_NUMLOCK = FALSE;
    UINT8   *KeyboardTypeBda = (UINT8*)((UINTN) 0x496);


    Kbd->KeyData.Key.ScanCode = 0;
    Kbd->KeyData.Key.UnicodeChar = 0;
    Kbd->KeyData.PS2ScanCode = Data;

    //
    // Process ESC key
    //
    if (Data == 1) {
        Kbd->KeyData.Key.ScanCode = EFI_SCAN_ESC;
        Kbd->KeyData.EfiKey = EfiKeyEsc;
        Kbd->KeyIsReady = TRUE;
        return;
    }

    //
    // Get the E0, E1 Status from BDA (40:96). If those bit get set means Int9 processed the E0
    // E1 data and before processing other Scan code it came out of Legacy mode.
    // Now EFI driver sees other scan code that's part of the E0 and E1 scan. So we don't want to Process
    // those data.
    //
#if CHECK_BDA_KEYBOARD_BUFFER
#if CSM_SUPPORT
    if( gLegacyBiosProtocolFound ) {
        if(*KeyboardTypeBda & (E0_STATUS_IN_BDA + E1_STATUS_IN_BDA)) {
            *KeyboardTypeBda &=~(E0_STATUS_IN_BDA + E1_STATUS_IN_BDA);
            return;
        }
    }
#endif
#endif

    //
    // Process key modifiers: xyzLock (update LEDs) and Ctrl/Alt/Shift
    //
    switch (Data) {
        case 0x38:
            if (Kbd->ScannerState == KBST_E0) {
                Kbd->KeyData.KeyState.KeyShiftState |= RIGHT_ALT_PRESSED;
            } else {
                Kbd->KeyData.KeyState.KeyShiftState |= LEFT_ALT_PRESSED;
            }
            return; //break;
        case 0xB8:
            if (Kbd->ScannerState == KBST_E0) {
                Kbd->KeyData.KeyState.KeyShiftState &= ~RIGHT_ALT_PRESSED;
            } else {
                Kbd->KeyData.KeyState.KeyShiftState &= ~LEFT_ALT_PRESSED;
            }
            return; //break;

        case 0x1D:
            if (Kbd->ScannerState == KBST_E0) {
                Kbd->KeyData.KeyState.KeyShiftState |= RIGHT_CONTROL_PRESSED;
            } else {
                Kbd->KeyData.KeyState.KeyShiftState |= LEFT_CONTROL_PRESSED;
            }
            return; //break;
        case 0x9D:
            if (Kbd->ScannerState == KBST_E0) {
                Kbd->KeyData.KeyState.KeyShiftState &= ~RIGHT_CONTROL_PRESSED;
            } else {
                Kbd->KeyData.KeyState.KeyShiftState &= ~LEFT_CONTROL_PRESSED;
            }
            return; //break;

        case 0x2A: {
            Kbd->KeyData.KeyState.KeyShiftState |= LEFT_SHIFT_PRESSED; return; //break;
        }
        case 0xAA: // could be a part of a long break code
            if (!long_sequence) {
                Kbd->KeyData.KeyState.KeyShiftState &= ~LEFT_SHIFT_PRESSED;
            }
            return; //break;

        case 0x36: Kbd->KeyData.KeyState.KeyShiftState |= RIGHT_SHIFT_PRESSED; return; //break;
        case 0xB6: Kbd->KeyData.KeyState.KeyShiftState &= ~RIGHT_SHIFT_PRESSED; return; //break;

        case 0x3A:
                if (!Make_Capslock) {
                    Kbd->KeyData.KeyState.KeyToggleState ^= CAPS_LOCK_ACTIVE;
                    Make_Capslock = TRUE;
                }
                Kbd->KeyData.EfiKey = EfiKeyCapsLock;
                Kbd->KeyIsReady = TRUE;
                break;

        case 0xBA: Make_Capslock = FALSE; break;

        case 0x46:
                if (Kbd->ScannerState != KBST_E0){
                        if (!Make_SCRLOCK) {
                            Kbd->KeyData.KeyState.KeyToggleState ^= SCROLL_LOCK_ACTIVE;
                            Make_SCRLOCK = TRUE;
                        }
                        Kbd->KeyData.EfiKey = EfiKeySLck;
                        Kbd->KeyIsReady = TRUE;
                }
                break;

        case 0xC6:
                if (Kbd->ScannerState != KBST_E0){
                    Make_SCRLOCK = FALSE;
                }
                break;
        case 0x45:
                if (!Make_NUMLOCK) {
                    Kbd->KeyData.KeyState.KeyToggleState ^= NUM_LOCK_ACTIVE;
                    Make_NUMLOCK = TRUE;
                }
                Kbd->KeyData.EfiKey = EfiKeyNLck;
                Kbd->KeyIsReady = TRUE;
                break;

        case 0xC5: Make_NUMLOCK = FALSE; break;
        //
        // Handle the PrintScreen/SysRq make Code
        //
        case 0x37:
                if (Kbd->ScannerState == KBST_E0) {
                    Kbd->KeyData.KeyState.KeyShiftState |= SYS_REQ_PRESSED;
                    return;
                }
                break;

        //
        // Handle the PrintScreen/SysRq breakcode
        //
        case 0xB7:
                if (Kbd->ScannerState == KBST_E0) {
                    Kbd->KeyData.KeyState.KeyShiftState &= ~ SYS_REQ_PRESSED;
                    return;
                }
                break;

        //
        // Handle the Left Logo make Code
        //
        case 0x5B:
                if (Kbd->ScannerState == KBST_E0) {
                    Kbd->KeyData.KeyState.KeyShiftState |= LEFT_LOGO_PRESSED;
                    return;
                }
                break;

        //
        // Handle the Left Logo breakcode
        //
        case 0xDB:
                if (Kbd->ScannerState == KBST_E0) {
                    Kbd->KeyData.KeyState.KeyShiftState &= ~ LEFT_LOGO_PRESSED;
                    return;
                }
                break;

        //
        // Handle the Right Logo make Code
        //
        case 0x5C:
                if (Kbd->ScannerState == KBST_E0) {
                    Kbd->KeyData.KeyState.KeyShiftState |= RIGHT_LOGO_PRESSED;
                    return;
                }
                break;

        //
        // Handle the Right Logo breakcode
        //
        case 0xDC:
                if (Kbd->ScannerState == KBST_E0) {
                    Kbd->KeyData.KeyState.KeyShiftState &= ~ RIGHT_LOGO_PRESSED;
                    return;
                }
                break;

        //
        // Handle the Menu Key make Code
        //
        case 0x5D:
                if (Kbd->ScannerState == KBST_E0) {
                    Kbd->KeyData.KeyState.KeyShiftState |= MENU_KEY_PRESSED;
                    return;
                }
                break;

        //
        // Handle the Meny Key breakcode
        //
        case 0xDD:
                if (Kbd->ScannerState == KBST_E0) {
                    Kbd->KeyData.KeyState.KeyShiftState &= ~ MENU_KEY_PRESSED;
                    return;
                }
                break;

        case 0xFA: ProcessKBDResponse(Kbd, Data); break;
        case 0xFE: ProcessKBDResponse(Kbd, Data); break;
        case 0xFF: ProcessKBDResponse(Kbd, Data); break;
    }

    //
    // Process main block of keys
    //
    if (Data < 0x3A && !(Kbd->ScannerState == KBST_E0 && Data == 0x37)) {// Exceptional case is Printscreen/sys req

        bShifted = Kbd->KeyData.KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED);

        if (Kbd->ScannerState == KBST_E0) bShifted = 0;  // Check for '/' in Keypad. Otherwise '?' will be sent


        if (IsLetter(Data)) {   // for not-a-letter Caps-Lock must not work
            bUpperCase = (Kbd->KeyData.KeyState.KeyToggleState & CAPS_LOCK_ACTIVE)? !bShifted: bShifted;
        }
        else {
            bUpperCase = bShifted;
        }
        if (bUpperCase) {
            Kbd->KeyData.Key.UnicodeChar = Code_Table[Data];    // UPPER CASE TABLE
        }
        else {
            Kbd->KeyData.Key.UnicodeChar = code_table[Data];    // lower case table
        }
        Kbd->KeyData.EfiKey = ScancodeToEfi_table[Data];
        if (Kbd->KeyData.Key.UnicodeChar != 0) {
            Kbd->KeyIsReady = TRUE;
        }
        return;
    }

// UK Keyboard "|\" (EfiKeyB0)
// data = 0x56(ScanCode Set1), EfiKeyB0, "|\"
    if ( Data == 0x56) {
        bShifted = Kbd->KeyData.KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED);
        if ( Kbd->ScannerState == KBST_E0) bShifted = 0;  // Check for '/' in Keypad. Otherwise '?' will be sent
        bUpperCase = bShifted;      // for not-a-letter Caps-Lock must not work
        if (bUpperCase) {
            Kbd->KeyData.Key.UnicodeChar = '|';     // UPPER CASE TABLE
        }
        else {
            Kbd->KeyData.Key.UnicodeChar = '\\';    // lower case
        }
        Kbd->KeyData.EfiKey = EfiKeyB0;
        Kbd->KeyIsReady = TRUE;
        return;
    }

    //
    // Process keypad keys.  Exceptional cases:  -, + on keypad
    // Keypad numbers when NUMLOCK only is ON OR Shift only is pressed.
    if (Kbd->ScannerState != KBST_E0) {
        if ((Data > 0x46) && (Data < 0x54) && !long_sequence) {
            if (((Kbd->KeyData.KeyState.KeyToggleState & NUM_LOCK_ACTIVE)   // Only NUMLOCK in ON
                    && ((Kbd->KeyData.KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED)) == 0))
                || (((Kbd->KeyData.KeyState.KeyToggleState & NUM_LOCK_ACTIVE) == 0)   // Only shift key is pressed
                    && (Kbd->KeyData.KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED)))
                || Data == 0x4a || Data ==0x4e) // check for -,  + keys in keypad
            {
                Kbd->KeyData.Key.UnicodeChar = KeyPad_Table[Data-0x47];
                Kbd->KeyData.EfiKey = KeyPadEfiCode_Table[Data-0x47];
                Kbd->KeyIsReady = TRUE;
                return;
            }
        }
    }
    //
    // Process F-keys
    //
    for (extkey = ScanCode_Table; extkey->makecode != 0xFF; extkey++) {
        if (Data == extkey->makecode) {
            Kbd->KeyData.Key.ScanCode = extkey->efi_scancode;
            Kbd->KeyData.EfiKey = extkey->efi_key;
            Kbd->KeyIsReady = TRUE;
            return;
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       LEDsOnOff
//
// Description:     Turns keyboard LEDs on and off.
//
// Input:           KEYBOARD *Kbd - A pointer to the KEYBOARD device.
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

void LEDsOnOff (
    KEYBOARD*   Kbd )
{

    UINT8 bIndicators = Kbd->KeyData.KeyState.KeyToggleState & 7;    // SCRL/NUM/CPSL
    
    if (InsidePS2DataDispatcher) return;
    InsidePS2DataDispatcher = TRUE;

    //
    // Check for keyboard IRQ support
    //
    if(KbdIrqSupport){
        if(gKeyboardIrqInstall && KBDEnableState){
            if (bIndicators != Kbd->Indicators){
                //
                // Turn on/off the lights
                //
                Kbd->CommandResponded = NULL;
                //
                // Issue Keyboard LED Command 0xED
                //
                CheckIssueLEDCmd(Kbd);
                if(Kbd->LEDCommandState == ED_COMMAND_ISSUED) {
                    //
                    // LED command "ED" has been issues. Process the Data here itself.
                    //
                    UINT32	Counter; 
                    for (Counter = 1000; Counter > 0; Counter--) {
                        //
                        // The Interrupt handler will handle the response
                        // and set the Kbd->LEDCommandState to zero in both
                        // case with or without error. Exit once the response is
                        // handled.
                        //
                        if(Kbd->LEDCommandState == 0) {
                            break;
                        }
		                gSysTable->BootServices->Stall(1000);
                
                    }
                }
            }
            Kbd->LEDCommandState = NULL;
            InsidePS2DataDispatcher = FALSE;
            return;
        }
    }                                                

     
    if (bIndicators != Kbd->Indicators) {
        //
        // Issue Keyboard LED Command 0xED
        //
        CheckIssueLEDCmd(Kbd);

        //
        //Process the led command and data
        //
        ProcessLEDCommandData(Kbd);
    }

    InsidePS2DataDispatcher = FALSE;
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetKeyFromBuffer
//
// Description:     Gets the next key from the circular buffer
//
// Input:           KEYBOARD *Kbd - A pointer to the KEYBOARD device.
//                  EFI_INPUT_KEY *key - Pointer to input key data
//
// Output:          EFI_SUCCESS - key.ScanCode and key.UnicodeChar updated
//                  EFI_NOT_READY - no key in buffer
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetKeyFromBuffer (
    KEYBOARD    *Kbd,
    VOID        *Key,
    UINT8       KeySize
)
{
    AMI_EFI_KEY_DATA    TempKey;

    if (Kbd->pBufHead == Kbd->pBufTail) return EFI_NOT_READY;

    pBS->CopyMem(&TempKey, Kbd->pBufHead, sizeof(AMI_EFI_KEY_DATA));

    
    TempKey.EfiKeyIsValid = 1;
    TempKey.PS2ScanCodeIsValid = 1;

    ProcessMultiLanguage(&TempKey);
    
    if (TempKey.Key.UnicodeChar != 0) {
        TempKey.KeyState.KeyShiftState &= ~(RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED);
    }

    pBS->CopyMem(Key, &TempKey, KeySize);

    Kbd->pBufHead++;
    if (Kbd->pBufHead >= Kbd->pBufEnd) Kbd->pBufHead = Kbd->pBufStart;  // Point to the beginning

    return EFI_SUCCESS;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       InsertKeyToBuffer
//
// Description:     Insert the key into the circular buffer
//
// Input:           KEYBOARD *Kbd - A pointer to the KEYBOARD device.
//                  AMI_EFI_INPUT_KEY key - input key data
//
// Output:          EFI_SUCCESS - Key placed in buffer
//                  EFI_WARN_BUFFER_TOO_SMALL - Buffer to small
//
// Notes:           If buffer is full, the EFI_WARN_BUFFER_TOO_SMALL.
//                  Tail points to the new Data.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InsertKeyToBuffer (
    KEYBOARD            *Kbd,
    AMI_EFI_KEY_DATA    *Key
)
{
    AMI_EFI_KEY_DATA    *Temp = Kbd->pBufTail;

    CheckKeyNotify(Key);
    if (Kbd->pBufTail != Kbd->pBufHead) {   // Check if space available
        Temp++;
        if (Temp >= Kbd->pBufEnd) Temp = Kbd->pBufStart;
        if (Kbd->pBufHead == Temp) return EFI_WARN_BUFFER_TOO_SMALL; // No more space
    }

    *Kbd->pBufTail = *Key;
    Kbd->pBufTail++;

    if (Kbd->pBufTail >= Kbd->pBufEnd) Kbd->pBufTail = Kbd->pBufStart;

    return EFI_SUCCESS;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CheckKeyinBuffer
//
// Description:     Checks if any key is present in the buffer
//
// Input:           KEYBOARD *Kbd - A pointer to the KEYBOARD device.
//
// Output:          BOOLEAN - TRUE if a key is in the buffer, FALSE otherwise.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
CheckKeyinBuffer (
    KEYBOARD* Kbd
)
{
    if (Kbd->pBufHead == Kbd->pBufTail) return FALSE;
    return TRUE;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CheckPartialKey
//
// Description:     Gets the next key from the circular buffer
//
// Input:           KEYBOARD *Kbd - A pointer to the KEYBOARD device.
//                  EFI_INPUT_KEY *key - Pointer to input key data
//
// Output:          EFI_SUCCESS - Partial Key Found
//                  EFI_NOT_READY - no key in buffer
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CheckPartialKey (
    KEYBOARD        *Kbd,
    EFI_KEY_DATA    *Key
)
{

    if (Kbd->KeyData.Key.ScanCode == 0 && Kbd->KeyData.Key.UnicodeChar == 0) {
        //
        // If the Key ShiftState has valid key, report as Partial Key
        //
        if ((Kbd->KeyData.KeyState.KeyShiftState & ~SHIFT_STATE_VALID) != 0) {

            pBS->CopyMem(Key, &Kbd->KeyData, sizeof(EFI_KEY_DATA)); 
            Key->KeyState.KeyToggleState |= KEY_STATE_EXPOSED;
            CheckKeyNotify((AMI_EFI_KEY_DATA*)Key);
            return EFI_SUCCESS;
        }
    }

     return EFI_NOT_READY;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: KeyboardInterruptHandler
//
// Description: An interrupt handler for keyboard IRQ.
//
//
// Input:     InterruptType  Interrupt type
//            SystemContext  System context
//
// Output:    EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID KeyboardInterruptHandler(
    IN EFI_EXCEPTION_TYPE   InterruptType,
    IN EFI_SYSTEM_CONTEXT   SystemContext
)
{
    KEYBOARD_IRQ_STORE* KbIrqBuffer = &gKeyboardIrqBuffer;
    KEYBOARD *Kbd = &gKbd;
    UINT8 bIndicators = Kbd->KeyData.KeyState.KeyToggleState & 7;    // SCRL/NUM/CPSL
    UINT8 Data = IoRead8(KBC_DATA_PORT);
 
    gCpuArch->DisableInterrupt(gCpuArch);

    //
    // Stored received acknowledgement
    //
    switch (Data) {
        case 0xFA:
             Kbd->CommandResponded = KB_ACK_COM;
             if (Kbd->LEDCommandState == ED_COMMAND_ISSUED) {
                Kbd->LEDCommandState = ED_DATA_ISSUED;
                Kbd->Indicators = bIndicators;
                WriteKeyboardData(bIndicators);
                break;
             }

             if (Kbd->LEDCommandState == ED_DATA_ISSUED) {
                Kbd->LEDCommandState = 0;
                break;
             }

             break;
        case 0xFE:
             Kbd->CommandResponded = KB_RSND_COM;
             if (Kbd->LEDCommandState == ED_COMMAND_ISSUED || Kbd->LEDCommandState == ED_DATA_ISSUED) {
//              Error occured. Clear out the current indicator bits.
//              Modifiers will have the correct bits that needs to be set.
//              Next Call to CheckIssueLEDCmd will detect the mismatch
//              and start the LED sequence.
                WriteKeyboardData(0xF4);
                Kbd->LEDCommandState = 0;
                Kbd->KeyData.KeyState.KeyToggleState &=
                    ~(SCROLL_LOCK_ACTIVE | NUM_LOCK_ACTIVE | CAPS_LOCK_ACTIVE);
                    Kbd->Indicators &= 0xf0;     
             }
             break;
        case 0xFF:
             Kbd->CommandResponded = KB_RSND_COM;
             Kbd->LEDCommandState = 0;
             break;
        default:
            //
            // If key has been pressed before keyboard start then data will be saved in local buffer
            // else data will be processed
            //
            if(!gKeyboardDriverStart){
                if (KbIrqBuffer->KbdIndex < BUFFER_SIZE){
                    KbIrqBuffer->KbdBuffer[KbIrqBuffer->KbdIndex]=Data;
                    KbIrqBuffer->KbdIndex++;
                }
			}
             else {
                ProcessKBDData (Kbd, Data);
            }
            break;
    }

    //
    // End of interrupt command sent
    //
    mLegacy8259->EndOfInterrupt(mLegacy8259, SYSTEM_KEYBOARD_IRQ);
    gCpuArch->EnableInterrupt(gCpuArch);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:       InitKeyboardIrq
//
// Description:     To initialize keyboard interrupt, register keyboard
//                  handler, and enable the keyboard interrupt
// 
// Input:           
//
// Paremeters:      
//
// Output:          None
//
//
//<AMI_PHDR_END>
//**********************************************************************
VOID InitKeyboardIrq(VOID)
{

    EFI_STATUS          Status;
    KEYBOARD_IRQ_STORE* KbIrqBuffer                 = &gKeyboardIrqBuffer;
    EFI_GUID            gEfiLegacy8259ProtocolGuid  = EFI_LEGACY_8259_PROTOCOL_GUID;
    EFI_GUID            gEfiCpuArchProtocolGuid     = EFI_CPU_ARCH_PROTOCOL_GUID;
    UINT32              KeyboardVector              = NULL;
   
    if (!gKeyboardIrqInstall){
        Status = pBS->LocateProtocol(&gEfiLegacy8259ProtocolGuid, NULL, &mLegacy8259);
        if (EFI_ERROR(Status)) {
			return;
		}

        // Find the CPU Arch Protocol
        Status = pBS->LocateProtocol(&gEfiCpuArchProtocolGuid, NULL, &gCpuArch);
        if (EFI_ERROR(Status)) {
			return;
		}

        //
        // Get keyboard Interrupt vector
        //
        Status = mLegacy8259->GetVector(mLegacy8259, SYSTEM_KEYBOARD_IRQ, (UINT8 *) & KeyboardVector);
        if (EFI_ERROR(Status)) {
			return;
		}

        //
        // Register interrupt handler for keyboard
        //
        Status = gCpuArch->RegisterInterruptHandler(gCpuArch, KeyboardVector, KeyboardInterruptHandler);
        if (EFI_ERROR(Status)) {
			return;
		}

        KbIrqBuffer->KbdIndex=0;
        gKeyboardIrqInstall = TRUE;

        //
        // Now enable the interrupt
        //
        mLegacy8259->EnableIrq(mLegacy8259, SYSTEM_KEYBOARD_IRQ, FALSE);
    }
    return;
}

#if CLEAR_PENDING_KEYS_IN_PS2
// <AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: ClearOBF
//
// Description:
//  Clears any pending keys in Ps2 Output Buffer. 
//
// Input:
//  VOID
//
// Output:  
//  VOID
//  
// Modified:
//
// Referrals:
//
// Notes: This OBF clear is done since some PS2 KBC has pending keys even
//        after resetting the Keyboard.
//--------------------------------------------------------------------------- 
// <AMI_PHDR_END>
VOID
ClearOBF( 
VOID 
)
{
    UINT8 bData;
    UINT8 Counter=200;

    pBS->Stall(10*1000);

    while( IoRead8(KBC_CMDSTS_PORT) & KBC_OBF )
    {
        bData = IoRead8(KBC_DATA_PORT);
        //
        // wait 10 ms for KBC OBF output.
        //
        pBS->Stall(10*1000);
        Counter--;
        //
        // If still keys are present after 2 sec. exit from the loop.
        //
        if(Counter==NULL) {
            break;
        }
    }
    return; 
}

// <AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: Ps2KbdReset
//
// Description:
//  Reset the Ps2 Keyboard by sending disabling and Enabling scanning. 
//
// Input:
//  VOID
//
// Output:  
//  VOID
//  
// Modified:
//
// Referrals:
//
// Notes:
//
//--------------------------------------------------------------------------- 
// <AMI_PHDR_END>
VOID
Ps2KbdReset(
VOID
)
{
    EFI_STATUS Status;
    UINT8   bCount, bData, bBCount;

    //
    // Disable and enable keyboard to reset.
    //
    DisableKeyboard();

    for (bBCount = 0; bBCount < 4; bBCount++) {
        for (bCount = 0; bCount < 3; bCount++) {
            Status = ReadDevice(KBD_DISABLE_SCANNING, &bData, KB_ACK_COM);
            if (!EFI_ERROR(Status)) {
                break;
            }    
        }

        if (EFI_ERROR(Status)) {
            continue; 
        }

        for (bCount = 0; bCount < 3; bCount++) {
            Status = ReadDevice(KBD_ENABLE_SCANNING, &bData, KB_ACK_COM);
            if (!EFI_ERROR(Status)) { 
                break;
            }
        }

        if (!EFI_ERROR(Status)) {
            break;
        }
    }

    EnableKeyboard();
    return;
}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ProcessLEDCommandData
//
// Description:     Process the LED command and data.
//
// Input:           KEYBOARD *Kbd - A pointer to the KEYBOARD device.
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ProcessLEDCommandData(
    KEYBOARD*   Kbd )
{

    UINT32	Counter;
    UINT8   data;

    if(Kbd->LEDCommandState == ED_COMMAND_ISSUED) {
        //
        // LED command "ED" has been issued. Disable the keyboard and 
	    // Process the Data here itself.
        //
 
        DisableKeyboard();

        for (Counter = 1000; Counter > 0; Counter--) {
            for(data = IoRead8(KBC_CMDSTS_PORT); data & KBC_OBF; data = IoRead8(KBC_CMDSTS_PORT)) {
                if (!(data & KBC_AUX_OBF)) {
                    //
                    // Handle the Command or Data Status
                    //
                        DrivePS2KbdMachine(NULL);
                }
            }
 
            //
            // If the command and data is processed with or without error, exit here.
            //
            if(Kbd->LEDCommandState == 0) {
                return;
            }
		    gSysTable->BootServices->Stall(1000);			
        }
        EnableKeyboard();
    }
    return;
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
    IN OUT  AMI_EFI_KEY_DATA                *KeyData)
{
    EFI_STATUS Status;

    if(gPs2MultiLangSupportProtocol == NULL) {
        Status= pBS->LocateProtocol (
                  &gAmiMultiLangSupportGuid,
                  NULL,
                  &gPs2MultiLangSupportProtocol
                  );
        if(EFI_ERROR(Status)) {
            return EFI_NOT_FOUND;
        }
    }    
    Status = gPs2MultiLangSupportProtocol->KeyboardLayoutMap(gPs2MultiLangSupportProtocol,KeyData);

    return Status;
}

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
