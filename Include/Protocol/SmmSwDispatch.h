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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmSwDispatch.h 3     7/08/09 8:02p Markw $
//
// $Revision: 3 $
//
// $Date: 7/08/09 8:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmSwDispatch.h $
// 
// 3     7/08/09 8:02p Markw
// Update headers.
// 
// 2     3/28/07 2:48p Markw
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmSwDispatch.h
//
// Description:	SMM SW Dispatch Protocol header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_SW_DISPATCH_PROTOCOL_H__
#define __SMM_SW_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_SW_DISPATCH_PROTOCOL_GUID \
	{0xe541b773, 0xdd11, 0x420c, 0xb0, 0x26, 0xdf, 0x99, 0x36, 0x53, 0xf8, 0xbf}

GUID_VARIABLE_DECLARATION(gEfiSmmSwDispatchProtocolGuid,EFI_SMM_SW_DISPATCH_PROTOCOL_GUID);

typedef struct _EFI_SMM_SW_DISPATCH_PROTOCOL  EFI_SMM_SW_DISPATCH_PROTOCOL;



//******************************************************
// EFI_SMM_SW_DISPATCH_CONTEXT
//******************************************************
//
// A particular chipset may not support all possible software SMI
// input values. For example, the ICH supports only values 00h to
// 0FFh. The parent only allows a single child registration for
// each SwSmiInputValue.
//
typedef struct {
	UINTN	SwSmiInputValue;
} EFI_SMM_SW_DISPATCH_CONTEXT;


//******************************************************
// EFI_SMM_SW_DISPATCH
//******************************************************
typedef VOID (EFIAPI *EFI_SMM_SW_DISPATCH) (
	IN EFI_HANDLE					DispatchHandle,
	IN EFI_SMM_SW_DISPATCH_CONTEXT	*DispatchContext
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_SW_REGISTER) (
	IN EFI_SMM_SW_DISPATCH_PROTOCOL	*This,
	IN EFI_SMM_SW_DISPATCH			DispatchFunction,
	IN EFI_SMM_SW_DISPATCH_CONTEXT	*DispatchContext,
	OUT EFI_HANDLE					*DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_SW_UNREGISTER) (
IN EFI_SMM_SW_DISPATCH_PROTOCOL		*This,
IN EFI_HANDLE						DispatchHandle
);


struct _EFI_SMM_SW_DISPATCH_PROTOCOL {
	EFI_SMM_SW_REGISTER		Register;
	EFI_SMM_SW_UNREGISTER	UnRegister;
	UINTN					MaximumSwiValue;
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
