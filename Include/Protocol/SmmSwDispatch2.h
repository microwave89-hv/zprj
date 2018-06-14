//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmSwDispatch2.h 2     3/04/11 3:36p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmSwDispatch2.h $
// 
// 2     3/04/11 3:36p Markw
// Update headers.
// 
// 1     2/07/11 4:03p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		mm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmSwDispatch2.h
//
// Description:	SMM SW Dispatch Protocol header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_SW_DISPATCH2_PROTOCOL_H__
#define __SMM_SW_DISPATCH2_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <SmmPi.h>

#define EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID \
    {0x18a3c6dc, 0x5eea, 0x48c8, 0xa1, 0xc1, 0xb5, 0x33, 0x89, 0xf9, 0x89, 0x99} 

GUID_VARIABLE_DECLARATION(gEfiSmmSwDispatch2ProtocolGuid,EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID);

typedef struct _EFI_SMM_SW_DISPATCH2_PROTOCOL  EFI_SMM_SW_DISPATCH2_PROTOCOL;

//
// A particular chipset may not support all possible software SMI input values.
// For example, the ICH supports only values 00h to 0FFh.  The parent only allows a single
// child registration for each SwSmiInputValue.
//
typedef struct {
    UINTN SwSmiInputValue;
} EFI_SMM_SW_REGISTER_CONTEXT;

//
// The DispatchFunction will be called with Context set to the same value as was passed into
// this function in RegisterContext and with CommBuffer (and CommBufferSize) pointing
// to an instance of EFI_SMM_SW_CONTEXT indicating the index of the CPU which generated the
// software SMI.
//
typedef struct {
    UINTN SwSmiCpuIndex;//The 0-based index of the CPU which generated the software SMI.
    UINT8 CommandPort;  //This value corresponds directly to the CommandPort parameter used in the call to Trigger().
    UINT8 DataPort;     //This value corresponds directly to the DataPort parameter used in the call to Trigger().
} EFI_SMM_SW_CONTEXT;

typedef struct _EFI_SMM_SW_DISPATCH2_PROTOCOL EFI_SMM_SW_DISPATCH2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_SW_REGISTER2)(
    IN  CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
    IN        EFI_SMM_HANDLER_ENTRY_POINT2   DispatchFunction,
    IN  CONST EFI_SMM_SW_REGISTER_CONTEXT    *RegisterContext,
    OUT       EFI_HANDLE                     *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_SW_UNREGISTER2)(
    IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
    IN       EFI_HANDLE                     DispatchHandle
);

//
// The EFI_SMM_SW_DISPATCH2_PROTOCOL provides the ability to install child handlers for the
// given software.  These handlers will respond to software interrupts.
//
struct _EFI_SMM_SW_DISPATCH2_PROTOCOL {
    EFI_SMM_SW_REGISTER2    Register;
    EFI_SMM_SW_UNREGISTER2  UnRegister;
    UINTN                   MaximumSwiValue;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
