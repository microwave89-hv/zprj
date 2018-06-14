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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmCpuState.h 2     7/08/09 8:01p Markw $
//
// $Revision: 2 $
//
// $Date: 7/08/09 8:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmCpuState.h $
// 
// 2     7/08/09 8:01p Markw
// Update headers.
// 
// 1     2/07/07 11:00a Markw
// 
// 1     2/07/07 10:59a Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: SmmCpuSaveState.h
//
// Description:	This provides the SMM Cpu Save State protocol.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SMM_CPU_SAVE_STATE_PROTOCOL_H__
#define __SMM_CPU_SAVE_STATE_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_CPU_SAVE_STATE_PROTOCOL_GUID \
    {0x21f302ad,0x6e94,0x471b,0x84,0xbc,0xb1,0x48,0x0,0x40,0x3a,0x1d} 

GUID_VARIABLE_DECLARATION(gEfiSmmCpuSaveStateProtocolGuid,EFI_SMM_CPU_SAVE_STATE_PROTOCOL_GUID);

typedef struct _EFI_SMM_CPU_SAVE_STATE_PROTOCOL EFI_SMM_CPU_SAVE_STATE_PROTOCOL;

typedef struct _EFI_SMM_CPU_STATE32 {
    UINT8   Reserved1[0xf8];        // fe00h
    UINT32  SMBASE;                 // fef8h
    UINT32  SMMRevId;               // fefch
    UINT16  IORestart;              // ff00h
    UINT16  AutoHALTRestart;        // ff02h
    UINT32  IEDBASE;                // ff04h
    UINT8   Reserved2[0x98];        // ff08h
    UINT32  IOMemAddr;              // ffa0h
    UINT32  IOMisc;                 // ffa4h
    UINT32  _ES;
    UINT32  _CS;
    UINT32  _SS;
    UINT32  _DS;
    UINT32  _FS;
    UINT32  _GS;
    UINT32  _LDTBase;
    UINT32  _TR;
    UINT32  _DR7;
    UINT32  _DR6;
    UINT32  _EAX;
    UINT32  _ECX;
    UINT32  _EDX;
    UINT32  _EBX;
    UINT32  _ESP;
    UINT32  _EBP;
    UINT32  _ESI;
    UINT32  _EDI;
    UINT32  _EIP;
    UINT32  _EFLAGS;
    UINT32  _CR3;
    UINT32  _CR0;
} EFI_SMM_CPU_STATE32;

typedef struct _EFI_SMM_CPU_STATE64 {
    UINT8   Reserved1[0x1d0];       // fc00h
    UINT32  GdtBaseHiDword;         // fdd0h
    UINT32  LdtBaseHiDword;         // fdd4h
    UINT32  IdtBaseHiDword;         // fdd8h
    UINT8   Reserved2[0xc];         // fddch
    UINT64  IO_EIP;                 // fde8h
    UINT8   Reserved3[0x50];        // fdf0h
    UINT32  _CR4;                   // fe40h
    UINT8   Reserved4[0x48];        // fe44h
    UINT32  GdtBaseLoDword;         // fe8ch
    UINT32  GdtLimit;               // fe90h
    UINT32  IdtBaseLoDword;         // fe94h
    UINT32  IdtLimit;               // fe98h
    UINT32  LdtBaseLoDword;         // fe9ch
    UINT32  LdtLimit;               // fea0h
    UINT32  LdtInfo;                // fea4h
    UINT8   Reserved5[0x50];        // fea8h
    UINT32  SMBASE;                 // fef8h
    UINT32  SMMRevId;               // fefch
    UINT16  AutoHALTRestart;        // ff00h
    UINT16  IORestart;              // ff02h
    UINT32  IEDBASE;                // ff04h
    UINT8   Reserved6[0x14];        // ff08h
    UINT64  _R15;                   // ff1ch
    UINT64  _R14;
    UINT64  _R13;
    UINT64  _R12;
    UINT64  _R11;
    UINT64  _R10;
    UINT64  _R9;
    UINT64  _R8;
    UINT64  _RAX;                   // ff5ch
    UINT64  _RCX;
    UINT64  _RDX;
    UINT64  _RBX;
    UINT64  _RSP;
    UINT64  _RBP;
    UINT64  _RSI;
    UINT64  _RDI;
    UINT64  IOMemAddr;              // ff9ch
    UINT32  IOMisc;                 // ffa4h
    UINT32  _ES;                    // ffa8h
    UINT32  _CS;
    UINT32  _SS;
    UINT32  _DS;
    UINT32  _FS;
    UINT32  _GS;
    UINT32  _LDTR;                  // ffc0h
    UINT32  _TR;
    UINT64  _DR7;                   // ffc8h
    UINT64  _DR6;
    UINT64  _RIP;                   // ffd8h
    UINT64  IA32_EFER;              // ffe0h
    UINT64  _RFLAGS;                // ffe8h
    UINT64  _CR3;                   // fff0h
    UINT64  _CR0;                   // fff8h
} EFI_SMM_CPU_STATE64;

typedef union _EFI_SMM_CPU_STATE {
    struct {
        UINT8               Reserved[0x200];
        EFI_SMM_CPU_STATE32 x86;
    };
    EFI_SMM_CPU_STATE64 x64;
} EFI_SMM_CPU_STATE;

#define EFI_SMM_MIN_REV_ID_x64      0x30006

typedef struct _EFI_SMM_CPU_SAVE_STATE_PROTOCOL {
    EFI_SMM_CPU_STATE     **CpuSaveState;
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
