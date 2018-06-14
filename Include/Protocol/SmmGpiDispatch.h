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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmGpiDispatch.h 3     7/08/09 8:02p Markw $
//
// $Revision: 3 $
//
// $Date: 7/08/09 8:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmGpiDispatch.h $
// 
// 3     7/08/09 8:02p Markw
// Update headers.
// 
// 2     3/28/07 2:41p Markw
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmGpiDispatch.h
//
// Description:	SMM GPI Dispatch Protocol header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_GPI_DISPATCH_PROTOCOL_H__
#define __SMM_GPI_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_GPI_DISPATCH_PROTOCOL_GUID \
	{0xe0744b81, 0x9513, 0x49cd, 0x8c, 0xea, 0xe9, 0x24, 0x5e, 0x70, 0x39, 0xda}

GUID_VARIABLE_DECLARATION(gEfiSmmGpiDispatchProtocolGuid,EFI_SMM_GPI_DISPATCH_PROTOCOL_GUID);

typedef struct _EFI_SMM_GPI_DISPATCH_PROTOCOL EFI_SMM_GPI_DISPATCH_PROTOCOL;

typedef struct {
	UINTN GpiNum;
} EFI_SMM_GPI_DISPATCH_CONTEXT;

//**********************************************
// EFI_SMM_GPI_DISPATCH
//**********************************************
typedef VOID (EFIAPI *EFI_SMM_GPI_DISPATCH) (
	IN EFI_HANDLE					DispatchHandle,
	IN EFI_SMM_GPI_DISPATCH_CONTEXT	*DispatchContext
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_GPI_REGISTER) (
	IN EFI_SMM_GPI_DISPATCH_PROTOCOL	*This,
	IN EFI_SMM_GPI_DISPATCH				DispatchFunction,
	IN EFI_SMM_GPI_DISPATCH_CONTEXT		*DispatchContext,
	OUT EFI_HANDLE						*DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_GPI_UNREGISTER) (
	IN EFI_SMM_GPI_DISPATCH_PROTOCOL	*This,
	IN EFI_HANDLE						DispatchHandle
);

struct _EFI_SMM_GPI_DISPATCH_PROTOCOL {
	EFI_SMM_GPI_REGISTER	Register;
	EFI_SMM_GPI_UNREGISTER	UnRegister;
	UINTN					NumSupportedGpis;
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
