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
// $Header: /Alaska/BIN/Core/Include/Protocol/ConsoleControl.h 7     12/29/06 2:57p Felixp $
//
// $Revision: 7 $
//
// $Date: 12/29/06 2:57p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/ConsoleControl.h $
// 
// 7     12/29/06 2:57p Felixp
// 
// 6     3/13/06 1:40a Felixp
// 
// 5     8/23/05 11:43a Felixp
// 
// 4     7/15/05 7:16p Felixp
// CONSOLE_DEVICES_STARTED_PROTOCOL_GUID added.
// BDS uses it to notify Splitter that Console Devices have been started.
// Once Splitter receives notification, it will install ConIn and ConOut
// in System Table
// 
// 3     5/27/05 12:19a Felixp
// 
// 2     5/27/05 12:00a Felixp
// 
// 1     5/26/05 11:59p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	ConsoleControl.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __CONSOLE_CONTROL_PROTOCOL_H__
#define __CONSOLE_CONTROL_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_CONSOLE_CONTROL_PROTOCOL_GUID \
	{ 0xf42f7782, 0x12e, 0x4c12, 0x99, 0x56, 0x49, 0xf9, 0x43, 0x4, 0xf7, 0x21 }

GUID_VARIABLE_DECLARATION(gEfiConsoleControlProtocolGuid,EFI_CONSOLE_CONTROL_PROTOCOL_GUID);

// {EF9A3971-C1A0-4a93-BD40-5AA165F2DC3A}
#define CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID \
	{ 0xef9a3971, 0xc1a0, 0x4a93, 0xbd, 0x40, 0x5a, 0xa1, 0x65, 0xf2, 0xdc, 0x3a }

// {2DF1E051-906D-4eff-869D-24E65378FB9E}
#define CONSOLE_IN_DEVICES_STARTED_PROTOCOL_GUID \
	{ 0x2df1e051, 0x906d, 0x4eff, 0x86, 0x9d, 0x24, 0xe6, 0x53, 0x78, 0xfb, 0x9e }

typedef struct _EFI_CONSOLE_CONTROL_PROTOCOL EFI_CONSOLE_CONTROL_PROTOCOL;

typedef enum {
	EfiConsoleControlScreenText,
	EfiConsoleControlScreenGraphics,
	EfiConsoleControlScreenMaxValue
} EFI_CONSOLE_CONTROL_SCREEN_MODE;

typedef EFI_STATUS (EFIAPI *EFI_CONSOLE_CONTROL_PROTOCOL_GET_MODE)(
	IN EFI_CONSOLE_CONTROL_PROTOCOL *This,
	OUT EFI_CONSOLE_CONTROL_SCREEN_MODE *Mode,
	OUT BOOLEAN *UgaExists OPTIONAL, 
	OUT BOOLEAN *StdInLocked OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_CONSOLE_CONTROL_PROTOCOL_SET_MODE)(
	IN EFI_CONSOLE_CONTROL_PROTOCOL *This,
	OUT EFI_CONSOLE_CONTROL_SCREEN_MODE Mode
);

typedef EFI_STATUS (EFIAPI *EFI_CONSOLE_CONTROL_PROTOCOL_LOCK_STD_IN)(
	IN EFI_CONSOLE_CONTROL_PROTOCOL *This, IN CHAR16 *Password
);

struct _EFI_CONSOLE_CONTROL_PROTOCOL {
	EFI_CONSOLE_CONTROL_PROTOCOL_GET_MODE GetMode;
	EFI_CONSOLE_CONTROL_PROTOCOL_SET_MODE SetMode;
	EFI_CONSOLE_CONTROL_PROTOCOL_LOCK_STD_IN LockStdIn;
};

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
