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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmThunk.h 5     7/08/09 8:02p Markw $
//
// $Revision: 5 $
//
// $Date: 7/08/09 8:02p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmThunk.h $
// 
// 5     7/08/09 8:02p Markw
// Update headers.
// 
// 4     5/21/09 9:52a Markw
// Added comments for the FarCall86 and FarCall86Ex may be used to do INT
// XX calls.
// 
// 3     3/03/08 6:35p Markw
// Added 32-bit register for smm thunk.
// 
// 2     10/29/07 11:00a Markw
// Update register name. It was the same as CSM, which caused a symbol
// redefintion when CSM headers are used with this header.
// 
// 1     3/18/07 1:54p Markw
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:    SmmThunk.h
//
// Description: This file is an include file used to define the Protocol for the
//              SMM Thunk Protocol.
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef __SMM_THUNK_PROTOCOL_H__
#define __SMM_THUNK_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_THUNK_PROTOCOL_GUID \
    {0x2a82fce6,0x8bb6,0x413e,0xb9,0xeb,0x45,0xdf,0xc0,0x52,0x2d,0xf3}

GUID_VARIABLE_DECLARATION(gEfiSmmThunkProtocolGuid,EFI_SMM_THUNK_PROTOCOL_GUID);

typedef struct _EFI_SMM_THUNK_PROTOCOL EFI_SMM_THUNK_PROTOCOL;

//
// SMM Thunk specification constant and types
//

typedef struct {
    UINT16 CF:1;
    UINT16 Reserved1:1;
    UINT16 PF:1;
    UINT16 Reserved2:1;
    UINT16 AF:1;
    UINT16 Reserved3:1;
    UINT16 ZF:1;
    UINT16 SF:1;
    UINT16 TF:1;
    UINT16 IF:1;
    UINT16 DF:1;
    UINT16 OF:1;
    UINT16 IOPL:2;
    UINT16 NT:1;
    UINT16 Reserved4:1;
} SMM_THUNK_FLAGS_REG;

typedef struct {
    UINT16          AX;
    UINT16          BX;
    UINT16          CX;
    UINT16          DX;
    UINT16          SI;
    UINT16          DI;
    SMM_THUNK_FLAGS_REG Flags;
    UINT16          ES;
    UINT16          CS;
    UINT16          SS;
    UINT16          DS;
    UINT16          BP;
} SMM_THUNK_WORD_REGS;

typedef struct {
    UINT8           AL, AH;
    UINT8           BL, BH;
    UINT8           CL, CH;
    UINT8           DL, DH;
} SMM_THUNK_BYTE_REGS;

typedef union {
    SMM_THUNK_WORD_REGS X;
    SMM_THUNK_BYTE_REGS H;
} SMM_THUNK_IA32_REGISTER_SET;

typedef struct {
    UINT32 CF:1;
    UINT32 Reserved1:1;
    UINT32 PF:1;
    UINT32 Reserved2:1;
    UINT32 AF:1;
    UINT32 Reserved3:1;
    UINT32 ZF:1;
    UINT32 SF:1;
    UINT32 TF:1;
    UINT32 IF:1;
    UINT32 DF:1;
    UINT32 OF:1;
    UINT32 IOPL:2;
    UINT32 NT:1;
    UINT32 Reserved4:1;
    UINT32 RF:1;
    UINT32 VM:1;
    UINT32 AC:1;
    UINT32 VIF:1;
    UINT32 VIP:1;
    UINT32 ID:1;
    UINT32 Reserved5:10;
} SMM_THUNK_FLAGS_REG_EX;

typedef struct {
    UINT32          EAX;
    UINT32          EBX;
    UINT32          ECX;
    UINT32          EDX;
    UINT32          ESI;
    UINT32          EDI;
    SMM_THUNK_FLAGS_REG_EX Flags;
    UINT16          ES;
    UINT16          CS;
    UINT16          SS;
    UINT16          DS;
    UINT16          FS;
    UINT16          GS;
    UINT32          EBP;
} SMM_THUNK_DWORD_REGS_EX;

typedef struct {
    UINT16          AX;
    UINT16          Reserved1;
    UINT16          BX;
    UINT16          Reserved2;
    UINT16          CX;
    UINT16          Reserved3;
    UINT16          DX;
    UINT16          Reserved4;
    UINT16          SI;
    UINT16          Reserved5;
    UINT16          DI;
    UINT16          Reserved6;
    SMM_THUNK_FLAGS_REG Flags;
    UINT16          Reserved7;
    UINT16          ES;
    UINT16          CS;
    UINT16          SS;
    UINT16          DS;
    UINT16          FS;
    UINT16          GS;
    UINT16          BP;
    UINT16          Reserved8;
} SMM_THUNK_WORD_REGS_EX;

typedef struct {
    UINT8           AL;
    UINT8           AH;
    UINT16          Reserved1;
    UINT8           BL;
    UINT8           BH;
    UINT16          Reserved2;
    UINT8           CL;
    UINT8           CH;
    UINT16          Reserved3;
    UINT8           DL;
    UINT8           DH;
    UINT16          Reserved4;
} SMM_THUNK_BYTE_REGS_EX;

typedef union {
    SMM_THUNK_DWORD_REGS_EX E;
    SMM_THUNK_WORD_REGS_EX  X;
    SMM_THUNK_BYTE_REGS_EX  H;
} SMM_THUNK_IA32_REGISTER_SET_EX;

typedef BOOLEAN (EFIAPI *EFI_SMM_FARCALL86) (
    IN EFI_SMM_THUNK_PROTOCOL       *This,
    IN  UINT16                      Segment,
    IN  UINT16                      Offset,
    IN  SMM_THUNK_IA32_REGISTER_SET *Regs,
    IN  VOID                        *Stack,
    IN  UINTN                       StackSize
);

typedef BOOLEAN (EFIAPI *EFI_SMM_FARCALL86_EX) (
    IN EFI_SMM_THUNK_PROTOCOL           *This,
    IN  UINT16                          Segment,
    IN  UINT16                          Offset,
    IN  SMM_THUNK_IA32_REGISTER_SET_EX  *Regs,
    IN  VOID                            *Stack,
    IN  UINTN                           StackSize
);

//The FarCall86 and FarCall86Ex may be used to do INT XX calls.
//INT XX call:
// Stack = NULL
// StackSize = 0,
// Segment = Segment of INT xx.
// Offset = Offset of INT xx.

typedef struct _EFI_SMM_THUNK_PROTOCOL {
    EFI_SMM_FARCALL86       FarCall86;
    EFI_SMM_FARCALL86_EX    FarCall86Ex;
} EFI_SMM_THUNK_PROTOCOL;


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
