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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmPowerButtonDispatch.h 3     7/08/09 8:02p Markw $
//
// $Revision: 3 $
//
// $Date: 7/08/09 8:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmPowerButtonDispatch.h $
// 
// 3     7/08/09 8:02p Markw
// Update headers.
// 
// 2     3/28/07 2:45p Markw
// 
// 1     3/18/07 1:54p Markw
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
// 1     2/17/04 5:15p Markw
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: PowerButtonDispatch.h
//
// Description:	Power Button Dispatch Protocol Header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_POWER_BUTTON_DISPATCH_PROTOCOL_H__
#define __SMM_POWER_BUTTON_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL_GUID \
	{0xb709efa0, 0x47a6, 0x4b41, 0xb9, 0x31, 0x12, 0xec, 0xe7, 0xa8, 0xee, 0x56 }

GUID_VARIABLE_DECLARATION(gEfiSmmPowerButtonDispatchProtocolGuid,EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL_GUID);

typedef struct _EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL;

//******************************************************
// EFI_POWER_BUTTON_PHASE
//******************************************************
typedef enum {
	PowerButtonEntry, PowerButtonExit
} EFI_POWER_BUTTON_PHASE;
// Power Button. Example, Use for changing LEDs before ACPI OS is
// on.
// - DXE/BDS Phase
// - OS Install Phase

//******************************************************
// EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT
//******************************************************
typedef struct {
	EFI_POWER_BUTTON_PHASE	Phase;
} EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT;

//******************************************************
// EFI_SMM_POWER_BUTTON_DISPATCH
//******************************************************
typedef VOID (EFIAPI *EFI_SMM_POWER_BUTTON_DISPATCH) (
	IN EFI_HANDLE								DispatchHandle,
	IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT	*DispatchContext
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_POWER_BUTTON_REGISTER) (
	IN EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL	*This,
	IN EFI_SMM_POWER_BUTTON_DISPATCH			DispatchFunction,
	IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT	*DispatchContext,
	OUT EFI_HANDLE								*DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_POWER_BUTTON_UNREGISTER) (
	IN EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL	*This,
	IN EFI_HANDLE								DispatchHandle
);

struct _EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL {
	EFI_SMM_POWER_BUTTON_REGISTER	Register;
	EFI_SMM_POWER_BUTTON_UNREGISTER	UnRegister;
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
