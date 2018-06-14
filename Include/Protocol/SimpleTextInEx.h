//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/SimpleTextInEx.h 11    9/22/11 6:16a Rameshr $
//
// $Revision: 11 $
//
// $Date: 9/22/11 6:16a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/SimpleTextInEx.h $
// 
// 11    9/22/11 6:16a Rameshr
// [TAG]  		EIP63054
// [Category]  	New Feature
// [Description]  	Undo Pervious check-in.
// 
// 9     7/21/11 3:58p Artems
// EIP 64356: Combine common keyboard definitions in one file
// 
// 8     8/21/09 10:19a Felixp
// define GUID_VARIABLE_DECLARATION macro only if it has not been already
// defined.
// 
// 7     3/17/08 4:56p Rameshraju
// Build error resolved.
// 
// 6     10/18/07 11:23a Felixp
// 
// 5     10/17/07 4:24p Felixp
// 
// 4     10/17/07 4:10p Felixp
// Clean up
// 
// 2     8/24/07 3:03p Olegi
// 
// 1     8/23/07 2:44p Olegi
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SimpleTextInEx.h
//
// Description:	SimpleTextInEx protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SIMPLE_TEXT_INPUT_EX_PROTOCOL_H__
#define __SIMPLE_TEXT_INPUT_EX_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h> 
#include <KeyboardCommonDefinitions.h>

#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID \
    {0xdd9e7534, 0x7762, 0x4698, 0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}

GUID_VARIABLE_DECLARATION(gEfiSimpleTextInExProtocolGuid,EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION

typedef	struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_INPUT_RESET_EX) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN BOOLEAN ExtendedVerification
);


typedef struct {
    EFI_INPUT_KEY Key;
    EFI_KEY_STATE KeyState;
} EFI_KEY_DATA;

typedef EFI_STATUS (EFIAPI *EFI_INPUT_READ_KEY_EX) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    OUT EFI_KEY_DATA *KeyData
);

typedef EFI_STATUS (EFIAPI *EFI_SET_STATE) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState
);

typedef EFI_STATUS (EFIAPI *EFI_KEY_NOTIFY_FUNCTION) (
    IN EFI_KEY_DATA *KeyData
);

typedef EFI_STATUS (EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT EFI_HANDLE *NotifyHandle
);

typedef EFI_STATUS (EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
);

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
    EFI_INPUT_RESET_EX Reset;
    EFI_INPUT_READ_KEY_EX ReadKeyStrokeEx;
    EFI_EVENT WaitForKeyEx;
    EFI_SET_STATE SetState;
    EFI_REGISTER_KEYSTROKE_NOTIFY RegisterKeyNotify;
    EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************