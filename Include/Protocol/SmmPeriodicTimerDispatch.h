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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmPeriodicTimerDispatch.h 3     7/08/09 8:02p Markw $
//
// $Revision: 3 $
//
// $Date: 7/08/09 8:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmPeriodicTimerDispatch.h $
// 
// 3     7/08/09 8:02p Markw
// Update headers.
// 
// 2     3/28/07 2:41p Markw
// 
//**********************************************************************

//----------------------------------------------------------------------------
//<AMI_FHDR_START>
//
// Name: SmmPeriodicTimerDispatch.h 
//
// Description:	Smm Periodic Timer Dispatch Protocol header.
//
//<AMI_FHDR_END>
//----------------------------------------------------------------------------
#ifndef __SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL_H__
#define __SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL_GUID \
	{0x9cca03fc, 0x4c9e, 0x4a19, 0x9b, 0x6, 0xed, 0x7b, 0x47, 0x9b, 0xde, 0x55}

GUID_VARIABLE_DECLARATION(gEfiSmmPeriodicTimerDispatchProtocolGuid,EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL_GUID);

typedef struct _EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL;


//*******************************************************
// EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT
//*******************************************************
typedef struct {
	UINT64	Period;
	UINT64	SmiTickInterval;
	UINT64	ElapsedTime;
} EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT;

//*******************************************************
// EFI_SMM_PERIODIC_TIMER_DISPATCH
//*******************************************************
typedef VOID (EFIAPI *EFI_SMM_PERIODIC_TIMER_DISPATCH) (
	IN EFI_HANDLE								DispatchHandle,
	IN EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT	*DispatchContext
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_PERIODIC_TIMER_REGISTER) (
	IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL	*This,
	IN EFI_SMM_PERIODIC_TIMER_DISPATCH 			DispatchFunction,
	IN EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT 	*DispatchContext,
	OUT EFI_HANDLE 								*DispatchHandle
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_PERIODIC_TIMER_UNREGISTER) (
	IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL	*This,
	IN EFI_HANDLE								DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_PERIODIC_TIMER_INTERVAL) (
	IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL	*This,
	IN OUT UINT64								**SmiTickInterval
);


struct _EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL {
	EFI_SMM_PERIODIC_TIMER_REGISTER		Register;
	EFI_SMM_PERIODIC_TIMER_UNREGISTER	UnRegister;
	EFI_SMM_PERIODIC_TIMER_INTERVAL		GetNextShorterInterval;
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
