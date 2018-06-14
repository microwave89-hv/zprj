//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmTcoDispatch.h 1     11/21/08 4:39p Yul $
//
// $Revision: 1 $
//
// $Date: 11/21/08 4:39p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmTcoDispatch.h $
// 
// 1     11/21/08 4:39p Yul
// 
// 2     8/01/08 2:49p Yul
// Update for code review
// 
// 1     12/14/07 12:42p Alexp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: SmmTCODispatch_h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SMM_TCO_DISPATCH_PROTOCOL_H__
#define __SMM_TCO_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_TCO_DISPATCH_PROTOCOL_GUID \
{0xe2d6bb1, 0xc624, 0x446d, 0x99, 0x82, 0x69, 0x3c, 0xd1, 0x81, 0xa6, 0x7} 

GUID_VARIABLE_DECLARATION(gEfiSmmTcoDispatchProtocolGuid, \
							EFI_SMM_TCO_DISPATCH_PROTOCOL_GUID);

typedef struct _EFI_SMM_TCO_DISPATCH_PROTOCOL  \
				EFI_SMM_TCO_DISPATCH_PROTOCOL;



//******************************************************
// EFI_SMM_TCO_DISPATCH_CONTEXT
//******************************************************
typedef struct {
	UINTN	TcoBitOffset;
} EFI_SMM_TCO_DISPATCH_CONTEXT;


//******************************************************
// EFI_SMM_TCO_DISPATCH
//******************************************************
typedef VOID (EFIAPI *EFI_SMM_TCO_DISPATCH) (
	IN EFI_HANDLE					DispatchHandle,
	IN EFI_SMM_TCO_DISPATCH_CONTEXT	*DispatchContext
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_TCO_REGISTER) (
	IN EFI_SMM_TCO_DISPATCH_PROTOCOL	*This,
	IN EFI_SMM_TCO_DISPATCH			DispatchFunction,
	IN EFI_SMM_TCO_DISPATCH_CONTEXT	*DispatchContext,
	OUT EFI_HANDLE					*DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_TCO_UNREGISTER) (
IN EFI_SMM_TCO_DISPATCH_PROTOCOL		*This,
IN EFI_HANDLE						DispatchHandle
);


struct _EFI_SMM_TCO_DISPATCH_PROTOCOL {
	EFI_SMM_TCO_REGISTER		Register;
	EFI_SMM_TCO_UNREGISTER		UnRegister;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
