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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmCpu.h 2     3/04/11 3:35p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:35p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmCpu.h $
// 
// 2     3/04/11 3:35p Markw
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
// Name: SmmCpu.h
//
// Description:	Smm CPU Protocol
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_CPU_PROTOCOL_H__
#define __SMM_CPU_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_CPU_PROTOCOL_GUID \
    {0xeb346b97, 0x975f, 0x4a9f, 0x8b, 0x22, 0xf8, 0xe9, 0x2b, 0xb3, 0xd5, 0x69}

GUID_VARIABLE_DECLARATION(gEfiCpuProtocolGuid, EFI_SMM_CPU_PROTOCOL_GUID);

//Forward Declaration
typedef struct _EFI_SMM_CPU_PROTOCOL EFI_SMM_CPU_PROTOCOL;

#define EFI_SMM_SAVE_STATE_REGISTER_LMA_32BIT 32
#define EFI_SMM_SAVE_STATE_REGISTER_LMA_64BIT 64

typedef enum {
    EFI_SMM_SAVE_STATE_REGISTER_GDTBASE = 4,
    EFI_SMM_SAVE_STATE_REGISTER_IDTBASE = 5,
    EFI_SMM_SAVE_STATE_REGISTER_LDTBASE = 6,
    EFI_SMM_SAVE_STATE_REGISTER_GDTLIMIT = 7,
    EFI_SMM_SAVE_STATE_REGISTER_IDTLIMIT = 8,
    EFI_SMM_SAVE_STATE_REGISTER_LDTLIMIT = 9,
    EFI_SMM_SAVE_STATE_REGISTER_LDTINFO = 10,
    EFI_SMM_SAVE_STATE_REGISTER_ES = 20,
    EFI_SMM_SAVE_STATE_REGISTER_CS = 21,
    EFI_SMM_SAVE_STATE_REGISTER_SS = 22,
    EFI_SMM_SAVE_STATE_REGISTER_DS = 23,
    EFI_SMM_SAVE_STATE_REGISTER_FS = 24,
    EFI_SMM_SAVE_STATE_REGISTER_GS = 25,
    EFI_SMM_SAVE_STATE_REGISTER_LDTR_SEL = 26,
    EFI_SMM_SAVE_STATE_REGISTER_TR_SEL = 27,
    EFI_SMM_SAVE_STATE_REGISTER_DR7 = 28,
    EFI_SMM_SAVE_STATE_REGISTER_DR6 = 29,
    EFI_SMM_SAVE_STATE_REGISTER_R8 = 30,
    EFI_SMM_SAVE_STATE_REGISTER_R9 = 31,
    EFI_SMM_SAVE_STATE_REGISTER_R10 = 32,
    EFI_SMM_SAVE_STATE_REGISTER_R11 = 33,
    EFI_SMM_SAVE_STATE_REGISTER_R12 = 34,
    EFI_SMM_SAVE_STATE_REGISTER_R13 = 35,
    EFI_SMM_SAVE_STATE_REGISTER_R14 = 36,
    EFI_SMM_SAVE_STATE_REGISTER_R15 = 37,
    EFI_SMM_SAVE_STATE_REGISTER_RAX = 38,
    EFI_SMM_SAVE_STATE_REGISTER_RBX = 39,
    EFI_SMM_SAVE_STATE_REGISTER_RCX = 40,
    EFI_SMM_SAVE_STATE_REGISTER_RDX = 41,
    EFI_SMM_SAVE_STATE_REGISTER_RSP = 42,
    EFI_SMM_SAVE_STATE_REGISTER_RBP = 43,
    EFI_SMM_SAVE_STATE_REGISTER_RSI = 44,
    EFI_SMM_SAVE_STATE_REGISTER_RDI = 45,
    EFI_SMM_SAVE_STATE_REGISTER_RIP = 46,
    EFI_SMM_SAVE_STATE_REGISTER_RFLAGS = 51,
    EFI_SMM_SAVE_STATE_REGISTER_CR0 = 52,
    EFI_SMM_SAVE_STATE_REGISTER_CR3 = 53,
    EFI_SMM_SAVE_STATE_REGISTER_CR4 = 54,
    EFI_SMM_SAVE_STATE_REGISTER_FCW = 256,
    EFI_SMM_SAVE_STATE_REGISTER_FSW = 257,
    EFI_SMM_SAVE_STATE_REGISTER_FTW = 258,
    EFI_SMM_SAVE_STATE_REGISTER_OPCODE = 259,
    EFI_SMM_SAVE_STATE_REGISTER_FP_EIP = 260,
    EFI_SMM_SAVE_STATE_REGISTER_FP_CS = 261,
    EFI_SMM_SAVE_STATE_REGISTER_DATAOFFSET = 262,
    EFI_SMM_SAVE_STATE_REGISTER_FP_DS = 263,
    EFI_SMM_SAVE_STATE_REGISTER_MM0 = 264,
    EFI_SMM_SAVE_STATE_REGISTER_MM1 = 265,
    EFI_SMM_SAVE_STATE_REGISTER_MM2 = 266,
    EFI_SMM_SAVE_STATE_REGISTER_MM3 = 267,
    EFI_SMM_SAVE_STATE_REGISTER_MM4 = 268,
    EFI_SMM_SAVE_STATE_REGISTER_MM5 = 269,
    EFI_SMM_SAVE_STATE_REGISTER_MM6 = 270,
    EFI_SMM_SAVE_STATE_REGISTER_MM7 = 271,
    EFI_SMM_SAVE_STATE_REGISTER_XMM0 = 272,
    EFI_SMM_SAVE_STATE_REGISTER_XMM1 = 273,
    EFI_SMM_SAVE_STATE_REGISTER_XMM2 = 274,
    EFI_SMM_SAVE_STATE_REGISTER_XMM3 = 275,
    EFI_SMM_SAVE_STATE_REGISTER_XMM4 = 276,
    EFI_SMM_SAVE_STATE_REGISTER_XMM5 = 277,
    EFI_SMM_SAVE_STATE_REGISTER_XMM6 = 278,
    EFI_SMM_SAVE_STATE_REGISTER_XMM7 = 279,
    EFI_SMM_SAVE_STATE_REGISTER_XMM8 = 280,
    EFI_SMM_SAVE_STATE_REGISTER_XMM9 = 281,
    EFI_SMM_SAVE_STATE_REGISTER_XMM10 = 282,
    EFI_SMM_SAVE_STATE_REGISTER_XMM11 = 283,
    EFI_SMM_SAVE_STATE_REGISTER_XMM12 = 284,
    EFI_SMM_SAVE_STATE_REGISTER_XMM13 = 285,
    EFI_SMM_SAVE_STATE_REGISTER_XMM14 = 286,
    EFI_SMM_SAVE_STATE_REGISTER_XMM15 = 287,
    //
    // Pseudo-Registers
    //
    EFI_SMM_SAVE_STATE_REGISTER_IO = 512,
    EFI_SMM_SAVE_STATE_REGISTER_LMA = 513
} EFI_SMM_SAVE_STATE_REGISTER;

typedef enum {
    EFI_SMM_SAVE_STATE_IO_WIDTH_UINT8  = 0,
    EFI_SMM_SAVE_STATE_IO_WIDTH_UINT16 = 1,
    EFI_SMM_SAVE_STATE_IO_WIDTH_UINT32 = 2,
    EFI_SMM_SAVE_STATE_IO_WIDTH_UINT64 = 3
} EFI_SMM_SAVE_STATE_IO_WIDTH;

typedef enum {
    EFI_SMM_SAVE_STATE_IO_TYPE_INPUT  = 1,
    EFI_SMM_SAVE_STATE_IO_TYPE_OUTPUT = 2,
    EFI_SMM_SAVE_STATE_IO_TYPE_STRING = 4,
    EFI_SMM_SAVE_STATE_IO_TYPE_REP_PREFIX = 8
} EFI_SMM_SAVE_STATE_IO_TYPE;


typedef struct _EFI_SMM_SAVE_STATE_IO_INFO {
    UINT64 IoData;
    UINT16 IoPort;
    EFI_SMM_SAVE_STATE_IO_WIDTH IoWidth;
    EFI_SMM_SAVE_STATE_IO_TYPE  IoType;
} EFI_SMM_SAVE_STATE_IO_INFO;

typedef EFI_STATUS (EFIAPI *EFI_SMM_READ_SAVE_STATE) (
    IN CONST EFI_SMM_CPU_PROTOCOL   *This,
    IN UINTN                        Width,
    IN EFI_SMM_SAVE_STATE_REGISTER  Register,
    IN UINTN                        CpuIndex,
    OUT VOID                        *Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_WRITE_SAVE_STATE) (
    IN CONST EFI_SMM_CPU_PROTOCOL   *This,
    IN UINTN                        Width,
    IN EFI_SMM_SAVE_STATE_REGISTER  Register,
    IN UINTN                        CpuIndex,
    IN CONST VOID                   *Buffer
);

typedef struct _EFI_SMM_CPU_PROTOCOL {
    EFI_SMM_READ_SAVE_STATE  ReadSaveState;
    EFI_SMM_WRITE_SAVE_STATE WriteSaveState;
} EFI_SMM_CPU_PROTOCOL;

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
