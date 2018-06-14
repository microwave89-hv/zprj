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
// $Header: /Alaska/BIN/Core/Include/Protocol/CpuIo2.h 2     5/27/11 5:53p Felixp $
//
// $Revision: 2 $
//
// $Date: 5/27/11 5:53p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/CpuIo2.h $
// 
// 2     5/27/11 5:53p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 1     4/15/11 2:38p Artems
// EIP 56523: Added protocol definition as per PI spec v 1.2
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    CpuIo2.h
//
// Description: EFI_CPU_IO2_PROTOCOL definition file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_CPU_IO2_PROTOCOL_H__
#define __EFI_CPU_IO2_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

#if PI_SPECIFICATION_VERSION < 0x10014
#define EFI_CPU_IO2_PROTOCOL_GUID \
    { 0xB0732526, 0x38C8, 0x4b40, 0x88, 0x77, 0x61, 0xC7, 0xB0, 0x6A, 0xAC, 0x45 }
#else
#define EFI_CPU_IO2_PROTOCOL_GUID \
    { 0xad61f191, 0xae5f, 0x4c0e, 0xb9, 0xfa, 0xe8, 0x69, 0xd2, 0x88, 0xc6, 0x4f }
#endif

GUID_VARIABLE_DECLARATION(gEfiCpuIo2ProtocolGuid, EFI_CPU_IO2_PROTOCOL_GUID);


//*******************************************************
// EFI_CPU_IO_PROTOCOL_WIDTH
//*******************************************************
typedef enum {
    EfiCpuIoWidthUint8,
    EfiCpuIoWidthUint16,
    EfiCpuIoWidthUint32,
    EfiCpuIoWidthUint64,
    EfiCpuIoWidthFifoUint8,
    EfiCpuIoWidthFifoUint16,
    EfiCpuIoWidthFifoUint32,
    EfiCpuIoWidthFifoUint64,
    EfiCpuIoWidthFillUint8,
    EfiCpuIoWidthFillUint16,
    EfiCpuIoWidthFillUint32,
    EfiCpuIoWidthFillUint64,
    EfiCpuIoWidthMaximum
} EFI_CPU_IO_PROTOCOL_WIDTH;

typedef struct _EFI_CPU_IO2_PROTOCOL EFI_CPU_IO2_PROTOCOL;

typedef EFI_STATUS
(EFIAPI *EFI_CPU_IO_PROTOCOL_IO_MEM) (
    IN EFI_CPU_IO2_PROTOCOL          *This,
    IN EFI_CPU_IO_PROTOCOL_WIDTH     Width,
    IN UINT64                        Address,
    IN UINTN                         Count,
    IN OUT VOID                      *Buffer
);

typedef struct {
    EFI_CPU_IO_PROTOCOL_IO_MEM      Read;
    EFI_CPU_IO_PROTOCOL_IO_MEM      Write;
} EFI_CPU_IO_PROTOCOL_ACCESS;


struct _EFI_CPU_IO2_PROTOCOL {
  EFI_CPU_IO_PROTOCOL_ACCESS        Mem;
  EFI_CPU_IO_PROTOCOL_ACCESS        Io;
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
