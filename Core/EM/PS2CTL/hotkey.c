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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/hotkey.c 9     4/27/11 4:38a Lavanyap $
//
// $Revision: 9 $
//
// $Date: 4/27/11 4:38a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/hotkey.c $
// 
// 9     4/27/11 4:38a Lavanyap
// [TAG] - EIP49407
// [Category] - IMPROVEMENT
// [Description] - Move the Ps2 driver SDL tokens from Core Source to Core
// Bin,So that we don't need to add Core source for changing the Ps2
// driver SDL tokens.
// [Files] - Ps2Ctl.sdl, ps2kbd.c, ps2main.c, ps2ctl.h, kbc.c, mouse.c,
// hotkey.c, CORE_DXE.sdl, Tokens.c
// 
// 8     12/01/10 6:13a Anandv
// [TAG] - EIP 45947
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - Build Error on disabling INIT_DEFAULT_HOTKEYS SDL Token.
// [RootCause] - KEY_ASSOCIATION structure variable not declared based on
// INIT_DEFAULT_HOTKEYS SDL Token.
// [Solution] - KEY_ASSOCIATION structure variable declared based on
// INIT_DEFAULT_HOTKEYS SDL Token
// [Files] - hotkey.c
// 
// 7     8/23/10 4:31a Rameshr
// Bug Fix: EIP 40818
// Symptoms: Pause/Break function key has no function in logo screen
// FilesModified: HotKey.c
// Details:Pause key doesn't have valid Ps2 SCAN code. ProcesshotKey
// function will get 0 as input for Pause key and it tries to execute the
// invalid function.So getting exception.
// 
// 6     1/06/10 12:09a Rameshr
// Sometimes reset fail in BIOS Setup
// EIP:33327
// Ctrl+alt+del+Shift key also should reset the system
// 
// 5     7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
// 
// 4     4/21/08 5:48p Olegi
// Bugfix in RegisterHotKey routine for multiple hot keys.
// 
// 3     4/09/08 10:19a Olegi
// Changed the key attributes (modifiers and shift state) reporting.
// 
// 2     4/16/07 6:28p Pats
// Modified to conform with coding standards. No code changes.
// 
// 1     2/01/05 1:11a Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     10/28/04 10:19a Olegi
// 
// 1     9/30/04 8:07a Olegi
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:        hotkeys.c
//
// Description: PS/2 keyboard hotkeys support routines
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#include "ps2ctl.h"
#include "kbc.h"
#include <Protocol\HotKeys.h>

EFI_GUID gHotKeysGuid = EFI_HOT_KEYS_PROTOCOL_GUID;

HOT_KEYS_PROTOCOL HotKeysProtocol;
KEY_ASSOCIATION *HotKeys_Table;

extern UINT8   MaxHotKeys;
extern BOOLEAN InitDefaultHotKeys;



//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CopyKey
//
// Description:     HotKey helper function - Copies key codes from source to
//                  target buffers
//
// Parameters:      
//    KEY_ASSOCIATION *SrcKey - Pointer to source buffer
//    KEY_ASSOCIATION *TrgKey - Pointer to target buffer
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CopyKey (
    IN KEY_ASSOCIATION *SrcKey,
    IN KEY_ASSOCIATION *TrgKey
    )
{
    TrgKey->KeyCode = SrcKey->KeyCode;
    TrgKey->KeyAttrib = SrcKey->KeyAttrib;
    TrgKey->ReportKey = SrcKey->ReportKey;
    TrgKey->KeyExtendedFunc = SrcKey->KeyExtendedFunc;
    TrgKey->FunctionContext = SrcKey->FunctionContext;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       RegisterHotKey
//
// Description:     This is HotKey protocol API implementation function.
//                  It registers the "extended" key function.
//
// Parameters:      KEY_ASSOCIATION *HotKey - Key code to register
//                  BOOLEAN ReplaceExisting - a rule that tells whether or
//                      not we will replace the existing function; this 
//                      parameter will not be considered in case the function
//                      for a given key is not assigned yet.
//
// Output  :        EFI_SUCCESS if function is successfully registered
//                  EFI_OUT_OF_RESOURCES if we already have reached 
//                      MAX_HOTKEYS registered functions and we are not 
//                      replacing the existing one
//                  EFI_ACCESS_DENIED if requested key has been already
//                      assigned, can be returned only when ReplaceExisting
//                      is FALSE
//
// Modified:        HotKeys_Table
//      
// Referrals:       HotKeys_Table
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RegisterHotKey (
    IN KEY_ASSOCIATION *HotKey,
    IN BOOLEAN ReplaceExisting )
{

    KEY_ASSOCIATION *hk = HotKeys_Table;
    UINT8 i;
    UINT8 emptySpot = 0xFF;
    //
    // See if the key is already registered, at the same time find the empty
    // spot in HotKeys_Table
    //
    for (i = 0; i < MaxHotKeys; i++, hk++) {
        if (!hk->KeyCode) { // empty entry found
            if (emptySpot == 0xff) {
                emptySpot = i;
            }
            continue;
        }
        if ((hk->KeyCode == HotKey->KeyCode) && (hk->KeyAttrib == HotKey->KeyAttrib)) {
            if (ReplaceExisting) {
                CopyKey(HotKey, hk);
                return EFI_SUCCESS;
            }
            else {
                return EFI_ACCESS_DENIED;
            }
        }
    }
    //
    // We are here if the key duplicate is not found
    //
    if (emptySpot == 0xFF) {
        return EFI_OUT_OF_RESOURCES;    // no empty space found either
    }

    CopyKey(HotKey, &HotKeys_Table[emptySpot]); // fill in the new entry
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UnregisterHotKeys
//
// Description:     This is HotKey protocol API implementation function.
//                  It unregisters all "extended" key functions.
//
// Parameters:      None
//
// Output:          EFI_SUCCESS if functions are successfully unregistered
//                  EFI_ACCESS_DENIED if functions are not unregistered
//
// Modified:        HotKeys_Table
//      
// Referrals:       HotKeys_Table
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UnregisterHotKeys()
{
    UINT8 i;
    KEY_ASSOCIATION ZeroedEntry = {0};

    for (i = 0; i < MaxHotKeys; i++) {
        CopyKey(&ZeroedEntry, &HotKeys_Table[i]);
    }
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ResetSystem
//
// Description:     This routine performs a warm boot of the system
//
// Parameters:      VOID *Context - Pointer to context
//
// Output:          EFI_SUCCESS
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ResetSystem (
    VOID    *Context )
{
    gSysTable->RuntimeServices->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       InitHotKeys
//
// Description:     This routine is called from StartKeyboard function,
//                  it initializes the PS/2 keyboard hot keys and produces
//                  HotKeys protocol.
//
// Parameters:      EFI_HANDLE Controller - Handle for this driver
//
// Output:          EFI_STATUS - Status of the operation
//
// Modified:        HotKeysProtocol
//      
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitHotKeys (
    EFI_HANDLE Controller )
{
    EFI_STATUS Status;
    KEY_ASSOCIATION hk;
    //
    // Publish the hot key registration interface
    //
    HotKeysProtocol.RegisterHotKey = RegisterHotKey;
    HotKeysProtocol.UnregisterHotKeys = UnregisterHotKeys;
    Status = gSysTable->BootServices->InstallProtocolInterface (
        &Controller,
        &gHotKeysGuid,
        EFI_NATIVE_INTERFACE,
        &HotKeysProtocol
    );
    // 
    // Initialise the hotkeys table list
    //
    Status = pBS->AllocatePool( 
                    EfiBootServicesData,
                    MaxHotKeys * sizeof(KEY_ASSOCIATION),
                    &HotKeys_Table );
    pBS->SetMem( HotKeys_Table, MaxHotKeys * sizeof(KEY_ASSOCIATION), 0);

    if ( InitDefaultHotKeys ) {
        //
        // Register Ctl+Alt+Del combination for Soft Reset
        //
        hk.KeyCode = 0x53;

        hk.ReportKey = TRUE;
        hk.KeyExtendedFunc = ResetSystem;
        hk.FunctionContext = NULL;

        hk.KeyAttrib = LEFT_CONTROL_PRESSED | LEFT_ALT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = LEFT_CONTROL_PRESSED | RIGHT_ALT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = RIGHT_CONTROL_PRESSED | LEFT_ALT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = RIGHT_CONTROL_PRESSED | RIGHT_ALT_PRESSED;
        RegisterHotKey(&hk, TRUE);

        hk.KeyAttrib = LEFT_CONTROL_PRESSED | LEFT_ALT_PRESSED | LEFT_SHIFT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = LEFT_CONTROL_PRESSED | RIGHT_ALT_PRESSED | LEFT_SHIFT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = RIGHT_CONTROL_PRESSED | LEFT_ALT_PRESSED | LEFT_SHIFT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = RIGHT_CONTROL_PRESSED | RIGHT_ALT_PRESSED | LEFT_SHIFT_PRESSED;
        RegisterHotKey(&hk, TRUE);

        hk.KeyAttrib = LEFT_CONTROL_PRESSED | LEFT_ALT_PRESSED | RIGHT_SHIFT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = LEFT_CONTROL_PRESSED | RIGHT_ALT_PRESSED | RIGHT_SHIFT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = RIGHT_CONTROL_PRESSED | LEFT_ALT_PRESSED | RIGHT_SHIFT_PRESSED;
        RegisterHotKey(&hk, TRUE);
        hk.KeyAttrib = RIGHT_CONTROL_PRESSED | RIGHT_ALT_PRESSED | RIGHT_SHIFT_PRESSED;
        RegisterHotKey(&hk, TRUE);

    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ProcessHotKey
//
// Description:     This routine searches the HotKey table for the matching
//                  key and executes the corresponding "key extension"
//                  function.
//
// Parameters:      UINT8  Code - key make code
//                  UINT16 KeyShiftState - Shift/Alt/Ctrl modifiers:
//                  RIGHT_SHIFT_PRESSED     0x00000001
//                  LEFT_SHIFT_PRESSED      0x00000002
//                  RIGHT_CONTROL_PRESSED   0x00000004
//                  LEFT_CONTROL_PRESSED    0x00000008
//                  RIGHT_ALT_PRESSED       0x00000010
//                  LEFT_ALT_PRESSED        0x00000020
//                  RIGHT_LOGO_PRESSED      0x00000040
//                  LEFT_LOGO_PRESSED       0x00000080
//
// Output:          EFI_SUCCESS if 1)key is not found or 2)key is found,
//                      function executed and key has to be reported back
//                      to the caller;
//                  EFI_NOT_READY if key is found but is not to be reported
//                      back to the caller.
// Referrals:       HotKeys_Table
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ProcessHotKey (
    UINT8   Code,
    UINT16  KeyShiftState
)
{
    KEY_ASSOCIATION *hk = HotKeys_Table;
    UINT8 i;

    //
    // Validate the Input Data
    //
    if(Code == 0 && KeyShiftState == 0) {
        return EFI_NOT_READY;
    }

    //
    // Find the match in the table
    //
    for (i = 0; i < MaxHotKeys; i++) {
        if ((hk->KeyCode == Code) && (hk->KeyAttrib == (UINT8)KeyShiftState)) {
            //
            // Match found - execute the function
            //
            hk->KeyExtendedFunc(hk->FunctionContext);
            return (hk->ReportKey)? EFI_SUCCESS: EFI_NOT_READY;
        }
        hk++;
    }
    return EFI_SUCCESS;
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
