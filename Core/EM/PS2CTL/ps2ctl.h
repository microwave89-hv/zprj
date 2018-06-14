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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/ps2ctl.h 15    4/27/11 4:35a Lavanyap $
//
// $Revision: 15 $
//
// $Date: 4/27/11 4:35a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/ps2ctl.h $
// 
// 15    4/27/11 4:35a Lavanyap
// [TAG] - EIP49407
// [Category] - IMPROVEMENT
// [Description] - Move the Ps2 driver SDL tokens from Core Source to Core
// Bin,So that we don't need to add Core source for changing the Ps2
// driver SDL tokens.
// [Files] - Ps2Ctl.sdl, ps2kbd.c, ps2main.c, ps2ctl.h, kbc.c, mouse.c,
// hotkey.c, CORE_DXE.sdl, Tokens.c
// 
// 14    1/24/11 3:41p Pats
// [TAG] - EIP 18488
// [Category] - Enhancement
// [Severity] - Normal
// [Symptom] - PS2CTL: Need hooks for port swap, Keybaord mouse detect.
// [RootCause] - Support may be needed for kbc controller or SIO with
// different support from AMI KB-5.
// [Solution] - Added definition of AutodetectKbdMousePortsPtr.
// [Files] - ps2ctl.h
// NOTE: Implementation of this change requires changes to CORE_DXE.sdl
// and BdsBoard.c.
// 
// 13    7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
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
// 8     4/10/07 10:04a Felixp
// LookupHID routine renamed to LookupPs2Hid to avoid linking issue when
// linking with FloppyCtrl module
// 
// 7     3/13/06 2:38a Felixp
// 
// 6     1/09/06 11:38a Felixp
// 
// 4     12/22/05 10:22a Srinin
// 
// 3     10/11/05 4:11p Srinin
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
// 7     9/30/04 8:13a Olegi
// HotKeys added.
// 
// 6     9/21/04 5:51p Olegi
// 
// 5     8/27/04 3:17p Olegi
// Header and footer added.
// 
// 4     8/18/04 6:37p Olegi
// Header and footer added.
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: ps2ctl.h
//
// Description: PS/2 Controller DXE driver header
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#ifndef __PS2_MAIN_H__
#define __PS2_MAIN_H__

#include <Efi.h>
#include <AmiDxeLib.h>
#include <Protocol\DevicePath.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\SimpleTextIn.h>
#include <Protocol\SimpleTextInEx.h>
#include <Protocol\AmiKeycode.h>
#include <Protocol\SimplePointer.h>
#include <token.h>
#define TRACEKBD 


#define PS2_DRIVER_VER 0x10
#define DEVICETYPE_MOUSE     1
#define DEVICETYPE_KEYBOARD  2
extern EFI_SYSTEM_TABLE     *gSysTable;


EFI_STATUS StartMouse(EFI_DRIVER_BINDING_PROTOCOL *This,
        EFI_HANDLE Controller);
EFI_STATUS StartKeyboard(EFI_DRIVER_BINDING_PROTOCOL *This,
        EFI_HANDLE Controller);
EFI_STATUS StopMouse(EFI_DRIVER_BINDING_PROTOCOL *This,
        EFI_HANDLE Controller);
EFI_STATUS StopKeyboard(EFI_DRIVER_BINDING_PROTOCOL *This,
        EFI_HANDLE Controller);

typedef EFI_STATUS (*STARTSTOPPROC)(EFI_DRIVER_BINDING_PROTOCOL *This, 
    EFI_HANDLE Controller);

typedef struct PS2DEV_TABLE_tag {
    UINT32 hid;
    UINT32 uid;
    UINT8  DeviceType;
    STARTSTOPPROC start;
    STARTSTOPPROC stop;
    CHAR16* name;
} PS2DEV_TABLE;

typedef void (*STATEMACHINEPROC)(void*);
void PS2DataDispatcher(void*);
UINT8 KBCGetData();

BOOLEAN LookupPs2Hid(PS2DEV_TABLE*, UINT32, UINT32, PS2DEV_TABLE**);
EFI_STATUS GetPS2_DP(EFI_DRIVER_BINDING_PROTOCOL*, EFI_HANDLE, ACPI_HID_DEVICE_PATH**, UINT32);

typedef VOID (*AUTODETECT_KBD_MOUSE_PORTS)();
typedef EFI_STATUS (*DETECT_KBC_DEVICE)();
extern AUTODETECT_KBD_MOUSE_PORTS AutodetectKbdMousePortsPtr;
extern DETECT_KBC_DEVICE DetectKeyboardPtr;
extern DETECT_KBC_DEVICE DetectMousePtr;

#endif  // __PS2_MAIN_H__

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
