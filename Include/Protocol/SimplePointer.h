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
// $Header: /Alaska/BIN/Core/Include/Protocol/SimplePointer.h 2     3/13/06 1:40a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/SimplePointer.h $
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     8/30/04 11:38a Olegi
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SimplePointer.h
//
// Description:	SimplePointer protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SIMPLE_POINTER_PROTOCOL_H__
#define __SIMPLE_POINTER_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SIMPLE_POINTER_PROTOCOL_GUID \
	{0x31878c87,0xb75,0x11d5,0x9a,0x4f,0x0,0x90,0x27,0x3f,0xc1,0x4d}

GUID_VARIABLE_DECLARATION(gEfiSimplePointerProtocolGuid,EFI_SIMPLE_POINTER_PROTOCOL_GUID);

// Forward declaration
typedef	struct _EFI_SIMPLE_POINTER_PROTOCOL EFI_SIMPLE_POINTER_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SIMPLE_POINTER_RESET) (
	EFI_SIMPLE_POINTER_PROTOCOL	*This,
	BOOLEAN	ExtendedVerification);

typedef struct {
	INT32	RelativeMovementX;
	INT32	RelativeMovementY;
	INT32	RelativeMovementZ;
	BOOLEAN	LeftButton;
	BOOLEAN	RightButton;
} EFI_SIMPLE_POINTER_STATE;

typedef struct {
	UINT64	ResolutionX;
	UINT64	ResolutionY;
	UINT64	ResolutionZ;
	BOOLEAN	LeftButton;
	BOOLEAN	RightButton;
} EFI_SIMPLE_POINTER_MODE;

typedef EFI_STATUS (EFIAPI *EFI_SIMPLE_POINTER_GET_STATE) (
	EFI_SIMPLE_POINTER_PROTOCOL *This,
	EFI_SIMPLE_POINTER_STATE *State);

typedef struct _EFI_SIMPLE_POINTER_PROTOCOL {
	EFI_SIMPLE_POINTER_RESET		Reset;
	EFI_SIMPLE_POINTER_GET_STATE	GetState;
	EFI_EVENT						WaitForInput;
	EFI_SIMPLE_POINTER_MODE			*Mode;
} EFI_SIMPLE_POINTER_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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