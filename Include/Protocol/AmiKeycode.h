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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/AmiKeycode.h 1     6/04/13 1:51a Thomaschen $
//
// $Revision: 1 $
//
// $Date: 6/04/13 1:51a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/AmiKeycode.h $
// 
// 1     6/04/13 1:51a Thomaschen
// Fixed for EIP118202.
// 
// 10    10/25/12 2:36a Deepthins
// [TAG]  		EIP99475
// [Category]  	Improvement
// [Description]  	Multi language module Support in the console splitter
// [Files]  		ConSplit.c, ConSplit.h , In.c and AmiKeycode.h
// 
// 9     7/21/11 3:57p Artems
// EIP 64356: Combine common keyboard definitions in one file
// 
// 8     10/13/09 6:06p Felixp
// Hii.h renamed to UefiHii.h
// 
// 7     10/09/09 3:53p Felixp
// UEFI 2.1 related changes (new protocols added; existing protocols
// updated; one protocol deleted).
// 
// 6     8/21/09 10:19a Felixp
// define GUID_VARIABLE_DECLARATION macro only if it has not been already
// defined.
// 
// 5     10/23/07 4:37p Olegi
// Added PS2ScanCode field to the protocol.
// 
// 4     9/18/07 11:52a Olegi
// 
// 3     9/18/07 11:43a Olegi
// 
// 2     9/17/07 3:53p Olegi
// Removed EFI.H inclusion so that this header file can be also used in
// EDK drivers.
// 
// 1     9/07/07 4:35p Olegi
// 
// 2     8/24/07 3:03p Olegi
// 
// 1     8/23/07 2:44p Olegi
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiKeycode.h
//
// Description:	AMI_EFIKEYCODE_PROTOCOL definition
//
// Note: Currently this file is used both in Aptio and EDK files (MiniSetup.h)
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __AMI_KEYCODE_PROTOCOL_H__
#define __AMI_KEYCODE_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h> 
#include <KeyboardCommonDefinitions.h>

#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif

#define AMI_EFIKEYCODE_PROTOCOL_GUID \
    {0x0adfb62d, 0xff74, 0x484c, 0x89, 0x44, 0xf8, 0x5c, 0x4b, 0xea, 0x87, 0xa8}

#define AMI_MULTI_LANG_SUPPORT_PROTOCOL_GUID \
    {0xb295bd1c, 0x63e3, 0x48e3, 0xb2, 0x65, 0xf7, 0xdf, 0xa2, 0x7, 0x1, 0x23}
GUID_VARIABLE_DECLARATION(gAmiEfiKeycodeProtocolGuid,AMI_EFIKEYCODE_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION

#include <Protocol/SimpleTextInEx.h>

typedef	struct _AMI_EFIKEYCODE_PROTOCOL AMI_EFIKEYCODE_PROTOCOL;
typedef struct _AMI_MULTI_LANG_SUPPORT_PROTOCOL AMI_MULTI_LANG_SUPPORT_PROTOCOL;

typedef struct {
    EFI_INPUT_KEY Key;
    EFI_KEY_STATE KeyState;
    EFI_KEY EfiKey;
    UINT8 EfiKeyIsValid;
    UINT8 PS2ScanCode;
    UINT8 PS2ScanCodeIsValid;
} AMI_EFI_KEY_DATA;

typedef EFI_STATUS (EFIAPI *AMI_READ_EFI_KEY) (
    IN AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA *KeyData
);

typedef struct _AMI_EFIKEYCODE_PROTOCOL {
    EFI_INPUT_RESET_EX Reset;
    AMI_READ_EFI_KEY ReadEfikey;
    EFI_EVENT WaitForKeyEx;
    EFI_SET_STATE SetState;
    EFI_REGISTER_KEYSTROKE_NOTIFY RegisterKeyNotify;
    EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
} AMI_EFIKEYCODE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_KEYBOARD_LAYOUT_MAP)(
    IN      AMI_MULTI_LANG_SUPPORT_PROTOCOL *This,
    IN  OUT AMI_EFI_KEY_DATA *Keydata );

typedef struct _AMI_MULTI_LANG_SUPPORT_PROTOCOL {
    EFI_KEYBOARD_LAYOUT_MAP     KeyboardLayoutMap;
} AMI_MULTI_LANG_SUPPORT_PROTOCOL;
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