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

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB Protocols/SmmPchIoTrapDispatch2.h 1     2/08/12 8:26a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:26a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB Protocols/SmmPchIoTrapDispatch2.h $
// 
// 1     2/08/12 8:26a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmmIoTrap2Dispatch.h
//
// Description: The header file for I/O Trap # 2 SMM Dispatch Protocol.
//
// Note: This GUID & Contexts are followed Platform Initialization 
//       specification 1.2
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __SMM_IO_TRAP_DISPATCH2_PROTOCOL_H__
#define __SMM_IO_TRAP_DISPATCH2_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

//#### {58DC368D-7BFA-4E77-ABBC-0E29418DF930}
//#####define EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL_GUID \
//####  {0x58dc368d, 0x7bfa, 0x4e77, 0xab, 0xbc, 0x0e, 0x29, 0x41, 0x8d, 0xf9, 0x30}
// For avoid conflicting with Intel RC's "EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL_GUID",
// therefore AMI modifies the IO trap #2 GUID.
#define EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL_GUID \
  {0xf1507845, 0x6494, 0x4377, 0xa1, 0x15, 0x45, 0xdf, 0xe6, 0x5f, 0x5d, 0x71}

GUID_VARIABLE_DECLARATION( gEfiSmmIoTrapDispatch2ProtocolGuid, \
                                    EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL_GUID );

// I/O Trap valid types

typedef enum {
    WriteTrap = 0,
    ReadTrap,
    ReadWriteTrap,
    IoTrapTypeMaximum
} EFI_SMM_IO_TRAP_DISPATCH_TYPE;

// I/O Trap #2 context structure containing information about the I/O Trap
// event that should invoke the handler

typedef struct {
    UINT16                        Address;
    UINT16                        Length;
    EFI_SMM_IO_TRAP_DISPATCH_TYPE  Type;
} EFI_SMM_IO_TRAP_REGISTER_CONTEXT;

// I/O Trap #2 context structure containing information about the I/O Trap
// that occurred.

typedef struct {
    UINT32                        WriteData;
} EFI_SMM_IO_TRAP_CONTEXT;

typedef struct _EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL \
                                           EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL;

//******************************************************
// EFI_SMM_IO_TRAP_DISPATCH2
//******************************************************
typedef VOID (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH2) (
    IN EFI_HANDLE                           DispatchHandle,
    IN EFI_SMM_IO_TRAP_CONTEXT              *Context
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH2_REGISTER) (
    IN EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL   *This,
    IN EFI_SMM_IO_TRAP_DISPATCH2            DispatchFunction,
    IN OUT EFI_SMM_IO_TRAP_REGISTER_CONTEXT *DispatchContext,
    OUT EFI_HANDLE                          *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH2_UNREGISTER) (
    IN EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL   *This,
    IN EFI_HANDLE                           DispatchHandle
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
