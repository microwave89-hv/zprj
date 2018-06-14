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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/ps2mouse.h 6     9/19/11 9:37a Lavanyap $
//
// $Revision: 6 $
//
// $Date: 9/19/11 9:37a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/ps2mouse.h $
// 
// 6     9/19/11 9:37a Lavanyap
// [TAG]  		EIP66198
// [Category]  	Improvement
// [Description]  	Added Mouse Wheel support in PS2 and USB drivers. 
// [Files]  		usbdef.h, usbms.c, efiusbms.c, ps2mouse.h, mouse.c
// 
// 5     8/23/10 4:25a Rameshr
// Bug Fix : EIP 40838
// Symptoms: KBC.C build failed in DetectPS2Keyboard() if
// DETECT_PS2_KEYBOARD=0 & PS2MOUSE_SUPPORT=0
// Files Modified: Efismplpp.c, Kbc.c, Kbc.h, Mouse.c PS2ctl.cif,
// Ps2ctl.sdl, Ps2Kbd.c, Ps2Mouse.h
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
// 4     7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
// 
// 3     4/16/07 6:28p Pats
// Modified to conform with coding standards. No code changes.
// 
// 2     3/04/05 1:39p Mandal
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: ps2mouse.h
//
// Description: Ps2 mouse support header
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>


#include <Protocol\SimplePointer.h>

typedef struct {
    EFI_SIMPLE_POINTER_PROTOCOL iSmplPtr;
    EFI_SIMPLE_POINTER_MODE mode;
    EFI_SIMPLE_POINTER_STATE state;
    UINT8 saved_flags;
} MOUSE;


EFI_STATUS  MouseReset(
    MOUSE   *This,
    BOOLEAN ExtendedVerification
);

EFI_STATUS  MouseGetState(
    MOUSE *This,
    EFI_SIMPLE_POINTER_STATE *State
);

EFI_STATUS  DetectPS2mouse(
    MOUSE*
);

VOID OnWaitingOnMouse(
    EFI_EVENT Event, 
    MOUSE *Context
);

EFI_STATUS  InitMOUSE( 
    MOUSE** 
);

#define KBC_CMD_ENABLE_AUX  0x0A8
#define KBC_CMD_DISABLE_AUX 0x0A7
#define KBC_CMD_ENABLE_KBD  0x0AE
#define KBC_CMD_DISABLE_KBD 0x0AD
#define KBC_CMD_CHK_AUX     0x0A9
#define KBC_CMD_WRT_AUX     0x0D4


//----------------------------------------------------------------------------
// MOUSE  COMMANDS from  SYSTEM SET SAMPLING RATE & SET RESOLUTION
// Needs one more byte to be sent.
//----------------------------------------------------------------------------

#define RESET               0x0FF    // Reset.
#define DISABLE             0x0F5    // Disable.
#define ENABLE              0x0F4    // Enable.
#define SET_SAMPLING_RATE   0x0F3    // Set sampling rate.
#define READ_DEVICE_TYPE    0x0F2    // Read device type.
#define STATUS_REQUEST      0x0E9    // Status request.
#define SET_RESOLUTION      0x0E8    // Set resolution.
#define SET_SCALING_2X1     0x0E7    // Set scaling 2:1.
#define RESET_SCALING       0x0E6    // Set scaling 1:1.
#define REMOTE_MODE         0x0F0    // Set Remote Mode - mouse transfers 
                                     // packets by request
#define READ_DATA           0x0eb    // Forces thetransef of a mouse data packet
#define SET_STANDART        0x0f6    // Iitialize PS/2 and set standart state
//---------------------------------------
//  MOUSE RESPONSE ON COMMAND COMPLETION    
//---------------------------------------

#define ACK         0x0fa   // ACKnowledge
#define RSND        0x0fe   // RESEND
#define ERROR       0x0fc   // two invalid inputs received

//---------------------------------------
//  CCB Flags
//---------------------------------------

#define CCB_PCCOMPAT            0x40    // PC Compatibility mode
#define CCB_PS2MS_DISABLE       0x20    // Disable PS/2 mouse interface
#define CCB_KBD_DISABLE         0x10    // Disable in succession by mouse
#define CCB_SYSTEM              0x04    // 
#define CCB_MS_INTRPT           0x02    // 
#define CCB_KBD_INTRPT          0x01    // 


typedef struct {
    UINT8 flags;
    UINT8 x,y,z;    
} StdMouseDataPacket;

#define BUTTON_MID      0x04 
#define BUTTON_RIGHT    0x02
#define BUTTON_LEFT     0x01
#define MOUSE_X_NEG     0x10 
#define MOUSE_Y_NEG     0x20 
#define MOUSE_X_OVF     0x40 
#define MOUSE_Y_OVF     0x80 

#define NON_WHEEL_REPORT_FORMAT     3
#define WHEEL_REPORT_FORMAT         4


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
