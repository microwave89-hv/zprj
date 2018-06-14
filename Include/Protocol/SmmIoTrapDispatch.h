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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB Protocols/SmmIoTrapDispatch.h 1     2/08/12 8:26a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:26a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB Protocols/SmmIoTrapDispatch.h $
// 
// 1     2/08/12 8:26a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmmIoTrapDispatch.h
//
// Description: The header file for I/O Trap SMM Dispatch Protocol.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __SMM_IO_TRAP_DISPATCH_PROTOCOL_H__
#define __SMM_IO_TRAP_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

//follow Intel ref code IO TRAP GUID
//#define EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL_GUID \
//  { 0x58dc368d, 0x7bfa, 0x4e77, {0xab, 0xbc, 0xe, 0x29, 0x41, 0x8d, 0xf9, 0x30}}

// {BD18369D-C242-45ca-82AD-138AC2E29BAB}
//#define EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL_GUID \
//	{0xbd18369d, 0xc242, 0x45ca, 0x82, 0xad, 0x13, 0x8a, 0xc2, 0xe2, 0x9b, 0xab}

//GUID_VARIABLE_DECLARATION( gEfiSmmIoTrapDispatchProtocolGuid, \
//                                     EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL_GUID );

typedef enum {
  ReadIoCycle = 0,
  WriteIoCycle,
  ReadWriteIoCycle
} EFI_SMM_IOTRAP_OP_TYPE;

typedef enum {
  AccessAny = 0,
  AccessByte,
  AccessWord,
  AccessDWord
} EFI_SMM_ACCESS_WIDTH;

typedef struct {
  UINT16                    Address;
  UINT16                    Length;
  EFI_SMM_IOTRAP_OP_TYPE    TrapOpType;
  EFI_SMM_ACCESS_WIDTH      TrapWidth;
  UINT32                    TrapAddress;
  UINTN                     TrapData;
  UINT32                    TrapRegIndex;
} EFI_SMM_IO_TRAP_DISPATCH_CONTEXT;

typedef struct _EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL \
                                            EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL;

//******************************************************
// EFI_SMM_IO_TRAP_DISPATCH
//******************************************************
typedef VOID (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH) (
    IN EFI_HANDLE                           DispatchHandle,
    IN EFI_SMM_IO_TRAP_DISPATCH_CONTEXT     *Context
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_IO_TRAP_REGISTER) (
    IN EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL    *This,
    IN EFI_SMM_IO_TRAP_DISPATCH             DispatchFunction,
    IN EFI_SMM_IO_TRAP_DISPATCH_CONTEXT     *DispatchContext,
    OUT EFI_HANDLE                          *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_IO_TRAP_UNREGISTER) (
    IN EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL    *This,
    IN EFI_HANDLE                           DispatchHandle
);


struct _EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL {
    EFI_SMM_IO_TRAP_REGISTER                Register;
    EFI_SMM_IO_TRAP_UNREGISTER              UnRegister;
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
