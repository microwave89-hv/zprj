//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/HotKeys.h 3     3/13/06 1:40a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/HotKeys.h $
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:38a Mandal
// 
// 1     2/01/05 1:14a Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     10/28/04 10:19a Olegi
// 
// 1     9/30/04 3:38p Olegi
// Initial HotKeys protocol checkin.

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	HotKeys.h
//
// Description:	HotKeys protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HOT_KEYS_PROTOCOL_H__
#define __HOT_KEYS_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_HOT_KEYS_PROTOCOL_GUID \
	{0xf1e48287, 0x3fe1, 0x4535, 0x89, 0xab, 0x48, 0xd6, 0xc3, 0xda, 0x27, 0x59}

GUID_VARIABLE_DECLARATION(gEfiHotKeysProtocolGuid,EFI_HOT_KEYS_PROTOCOL_GUID);

//
// Keyboard extension functions definitions
//
typedef EFI_STATUS (*KEY_EXTENDED_FUNC) (VOID* Context);

typedef struct _KEY_ASSOCIATION {
	UINT8				KeyCode;
	UINT8				KeyAttrib;
	BOOLEAN				ReportKey;
	KEY_EXTENDED_FUNC	KeyExtendedFunc;
	VOID*				FunctionContext;
} KEY_ASSOCIATION;

//
// Forward declaration
//
//typedef	struct _HOT_KEYS_PROTOCOL HOT_KEYS_PROTOCOL;

typedef EFI_STATUS (EFIAPI *REGISTER_HOT_KEY) (
	IN KEY_ASSOCIATION *HotKey,
	IN BOOLEAN ReplaceExisting
);

typedef EFI_STATUS (EFIAPI *UNREGISTER_HOT_KEYS) ();

typedef struct _HOT_KEYS_PROTOCOL {
	REGISTER_HOT_KEY RegisterHotKey;
	UNREGISTER_HOT_KEYS UnregisterHotKeys;
} HOT_KEYS_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
