//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmStandbyButtonDispatch.h 3     7/08/09 8:02p Markw $
//
// $Revision: 3 $
//
// $Date: 7/08/09 8:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmStandbyButtonDispatch.h $
// 
// 3     7/08/09 8:02p Markw
// Update headers.
// 
// 2     3/28/07 2:44p Markw
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------//
// Name: StandbyButtonDispatch.h
//
// Description:	Standby Button Dispatch Protocol Header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL_H__
#define __SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL_GUID \
	{0x78965b98, 0xb0bf, 0x449e, 0x8b, 0x22, 0xd2, 0x91, 0x4e, 0x49, 0x8a, 0x98}

GUID_VARIABLE_DECLARATION(gEfiSmmStandbyButtonDispatchProtocolGuid,EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL_GUID);

typedef struct _EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL;


//*****************************************************
// EFI_STANDBY_BUTTON_PHASE;
//*****************************************************
typedef enum {
	Entry, Exit
} EFI_STANDBY_BUTTON_PHASE;

//
// Standby Button. Example, Use for changing LEDs before ACPI OS
// is on.
// - DXE/BDS Phase
// - OS Install Phase
//


//*****************************************************
// EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT
//*****************************************************
typedef struct {
	EFI_STANDBY_BUTTON_PHASE	Phase;
} EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT;

//*****************************************************
// EFI_SMM_STANDBY_BUTTON_DISPATCH
//*****************************************************
typedef VOID (EFIAPI *EFI_SMM_STANDBY_BUTTON_DISPATCH) (
	IN EFI_HANDLE								DispatchHandle,
	IN EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT	*DispatchContext
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_STANDBY_BUTTON_REGISTER) (
	IN EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL	*This,
	IN EFI_SMM_STANDBY_BUTTON_DISPATCH			DispatchFunction,
	IN EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT	*DispatchContext,
	OUT EFI_HANDLE								*DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_STANDBY_BUTTON_UNREGISTER) (
	IN EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL	*This,
	IN EFI_HANDLE								DispatchHandle
);

struct _EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL {
	EFI_SMM_STANDBY_BUTTON_REGISTER Register;
	EFI_SMM_STANDBY_BUTTON_UNREGISTER UnRegister;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
