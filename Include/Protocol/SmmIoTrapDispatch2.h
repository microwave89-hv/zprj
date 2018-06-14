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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmIoTrapDispatch2.h 2     3/04/11 3:36p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmIoTrapDispatch2.h $
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
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmBiosWriteDispatch2.h
//
// Description:	SMM BIOS write Dispatch Protocol header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_IO_TRAP_DISPATCH_PROTOCOL2_H__
#define __SMM_IO_TRAP_DISPATCH_PROTOCOL2_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <Efi.h>
#include <SmmPi.h>

#define EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL_GUID \
    {0x58dc368d, 0x7bfa, 0x4e77, 0xab, 0xbc, 0xe, 0x29, 0x41, 0x8d, 0xf9, 0x30 }

GUID_VARIABLE_DECLARATION(gEfiSmmIoTrapDispatch2ProtocolGuid, EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL_GUID);

typedef enum {
    WriteTrap,
    ReadTrap,
    ReadWriteTrap,
    IoTrapTypeMaximum
} EFI_SMM_IO_TRAP_DISPATCH_TYPE;

typedef struct {
    UINT16 Address;
    UINT16 Length;
    EFI_SMM_IO_TRAP_DISPATCH_TYPE Type;
} EFI_SMM_IO_TRAP_REGISTER_CONTEXT;

typedef struct {
    UINT32 WriteData;
} EFI_SMM_IO_TRAP_CONTEXT;

typedef struct _EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL  EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH2_REGISTER) (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2       DispatchFunction,
    IN OUT   EFI_SMM_IO_TRAP_REGISTER_CONTEXT   *RegisterContext,
    OUT      EFI_HANDLE *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH2_UNREGISTER) (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                         DispatchHandle
);

struct _EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL {
    EFI_SMM_IO_TRAP_DISPATCH2_REGISTER      Register;
    EFI_SMM_IO_TRAP_DISPATCH2_UNREGISTER    UnRegister;
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
