//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/ServiceBinding.h 1     5/24/12 3:18p Artems $
//
// $Revision: 1 $
//
// $Date: 5/24/12 3:18p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/ServiceBinding.h $
// 
// 1     5/24/12 3:18p Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Added definition for EFI_SERVICE_BINDING_PROTOCOL
// [Files]  		ServiceBinding.h
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	ServiceBinging.h
//
// Description:	EFI_SERVICE_BINDING Protocol Definition.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SERVICE_BINDING_PROTOCOL_H__
#define __SERVICE_BINDING_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

typedef struct _EFI_SERVICE_BINDING_PROTOCOL EFI_SERVICE_BINDING_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SERVICE_BINDING_CREATE_CHILD) (
    IN EFI_SERVICE_BINDING_PROTOCOL *This,
    IN OUT EFI_HANDLE *ChildHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SERVICE_BINDING_DESTROY_CHILD) (
    IN EFI_SERVICE_BINDING_PROTOCOL*This,
    IN EFI_HANDLE ChildHandle
);

struct _EFI_SERVICE_BINDING_PROTOCOL {
    EFI_SERVICE_BINDING_CREATE_CHILD CreateChild;
    EFI_SERVICE_BINDING_DESTROY_CHILD DestroyChild;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
