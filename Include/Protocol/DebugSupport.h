//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/DebugSupport.h 4     5/13/11 6:35p Oleksiyy $
//
// $Revision: 4 $
//
// $Date: 5/13/11 6:35p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DebugSupport.h $
// 
// 4     5/13/11 6:35p Oleksiyy
// [TAG]  		EIP56645 
// [Category]  	Improvement
// [Description]  	Status Code PI 1.2 Specification Update
// [Files]  		DebugSupport.h, StatusCodeDataTypeId.h and StatusCodes.h
// 
// 3     12/27/06 7:34a Felixp
// Updated to be complient with UEFI 2.0 Specification.
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     3/21/04 1:42p Felixp
// 
// 1     1/02/04 3:00p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DebugSupport.h
//
// Description:	DebugSupport protocol is for providing functions to 
//              support source level debugging. Some of these difinitions
//              are used by other protocols, such as the EFI_CPU_ARCH_PROTOCOL.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_DEBUG_SUPPORT_PROTOCOL__H__
#define __EFI_DEBUG_SUPPORT_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_DEBUG_SUPPORT_PROTOCOL_GUID \
    {0x2755590C,0x6F3C,0x42FA,0x9E,0xA4,0xA3,0xBA,0x54,0x3C,0xDA,0x25}

GUID_VARIABLE_DECLARATION(gEfiDebugSupportProtocolGuid,EFI_DEBUG_SUPPORT_PROTOCOL_GUID);

typedef struct _EFI_DEBUG_SUPPORT_PROTOCOL EFI_DEBUG_SUPPORT_PROTOCOL;

//At the time of publication of this specification, the latest revision of the PE/COFF specification
//was 6.2. The definition of IMAGE_FILE_MACHINE_EBC is not included in revision 6.2 of the
//PE/COFF specification. It will be added in a future revision of the PE/COFF specification

#define IMAGE_FILE_MACHINE_I386 0x014C
#define IMAGE_FILE_MACHINE_IA64 0x0200
#define IMAGE_FILE_MACHINE_EBC  0x0EBC
#define EFI_IMAGE_MACHINE_X64   0x8664

    typedef enum {
        IsaIa32 = IMAGE_FILE_MACHINE_I386, // 0x014C
        IsaIpf  = IMAGE_FILE_MACHINE_IA64, // 0x0200
        IsaEbc  = IMAGE_FILE_MACHINE_EBC,  // 0x0EBC
		IsaX64  = EFI_IMAGE_MACHINE_X64	   // 0x8664
    } EFI_INSTRUCTION_SET_ARCHITECTURE;

typedef EFI_STATUS (EFIAPI *EFI_GET_MAXIMUM_PROCESSOR_INDEX) (
    IN EFI_DEBUG_SUPPORT_PROTOCOL   *This,
    OUT UINTN                       *MaxProcessorIndex);


    
    // System context for virtual EBC processors
    typedef struct {
        UINT64 R0, R1, R2, R3, R4, R5, R6, R7;
        UINT64 Flags;
        UINT64 ControlFlags;
        UINT64 Ip;
    } EFI_SYSTEM_CONTEXT_EBC;    


        // FXSAVE_STATE - FP / MMX / XMM registers
        typedef struct {
            UINT16 Fcw;
            UINT16 Fsw;
            UINT16 Ftw;
            UINT16 Opcode;
            UINT32 Eip;
            UINT16 Cs;
            UINT16 Reserved1;
            UINT32 DataOffset;
            UINT16 Ds;
            UINT8 Reserved2[10];
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
			  UINT8   St0Mm0[10], Reserved3[6];
			  UINT8   St1Mm1[10], Reserved4[6];
			  UINT8   St2Mm2[10], Reserved5[6];
			  UINT8   St3Mm3[10], Reserved6[6];
			  UINT8   St4Mm4[10], Reserved7[6];
			  UINT8   St5Mm5[10], Reserved8[6];
			  UINT8   St6Mm6[10], Reserved9[6];
			  UINT8   St7Mm7[10], Reserved10[6];
			  UINT8   Xmm0[16];
			  UINT8   Xmm1[16];
			  UINT8   Xmm2[16];
			  UINT8   Xmm3[16];
			  UINT8   Xmm4[16];
			  UINT8   Xmm5[16];
			  UINT8   Xmm6[16];
			  UINT8   Xmm7[16];
			  UINT8   Reserved11[14 * 16];
			} EFI_FX_SAVE_STATE_IA32;
#else
            UINT8 St0Mm0[10], Reserved3[6];
            UINT8 St0Mm1[10], Reserved4[6];
            UINT8 St0Mm2[10], Reserved5[6];
            UINT8 St0Mm3[10], Reserved6[6];
            UINT8 St0Mm4[10], Reserved7[6];
            UINT8 St0Mm5[10], Reserved8[6];
            UINT8 St0Mm6[10], Reserved9[6];
            UINT8 St0Mm7[10], Reserved10[6];
            UINT8 Reserved11[22 * 16];
        } EFI_FXSAVE_STATE;
#endif

    // System context for IA-32 processors
    typedef struct {
        UINT32 ExceptionData; // ExceptionData is
        // additional data pushed
        // on the stack by some
        // types of IA-32
        // exceptions
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  		EFI_FX_SAVE_STATE_IA32 FxSaveState;
#else
        EFI_FXSAVE_STATE FxSaveState;
#endif
        UINT32 Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
        UINT32 Cr0, Cr1 /* Reserved */, Cr2, Cr3, Cr4;
        UINT32 Eflags;
        UINT32 Ldtr, Tr;
        UINT32 Gdtr[2], Idtr[2];
        UINT32 Eip;
        UINT32 Gs, Fs, Es, Ds, Cs, Ss;
        UINT32 Edi, Esi, Ebp, Esp, Ebx, Edx, Ecx, Eax;
    } EFI_SYSTEM_CONTEXT_IA32;


//
//  X64 processor exception types
//
#define EXCEPT_X64_DIVIDE_ERROR    0
#define EXCEPT_X64_DEBUG           1
#define EXCEPT_X64_NMI             2
#define EXCEPT_X64_BREAKPOINT      3
#define EXCEPT_X64_OVERFLOW        4
#define EXCEPT_X64_BOUND           5
#define EXCEPT_X64_INVALID_OPCODE  6
#define EXCEPT_X64_DOUBLE_FAULT    8
#define EXCEPT_X64_INVALID_TSS     10
#define EXCEPT_X64_SEG_NOT_PRESENT 11
#define EXCEPT_X64_STACK_FAULT     12
#define EXCEPT_X64_GP_FAULT        13
#define EXCEPT_X64_PAGE_FAULT      14
#define EXCEPT_X64_FP_ERROR        16
#define EXCEPT_X64_ALIGNMENT_CHECK 17
#define EXCEPT_X64_MACHINE_CHECK   18
#define EXCEPT_X64_SIMD            19

//
//  X64 processor context definition
//
// FXSAVE_STATE
// FP / MMX / XMM registers (see fxrstor instruction definition)
//
	typedef struct {
	  UINT16  Fcw;
	  UINT16  Fsw;
	  UINT16  Ftw;
	  UINT16  Opcode;
	  UINT64  Rip;
	  UINT64  DataOffset;
	  UINT8   Reserved1[8];
	  UINT8   St0Mm0[10], Reserved2[6];
	  UINT8   St1Mm1[10], Reserved3[6];
	  UINT8   St2Mm2[10], Reserved4[6];
	  UINT8   St3Mm3[10], Reserved5[6];
	  UINT8   St4Mm4[10], Reserved6[6];
	  UINT8   St5Mm5[10], Reserved7[6];
	  UINT8   St6Mm6[10], Reserved8[6];
	  UINT8   St7Mm7[10], Reserved9[6];
	  UINT8   Xmm0[16];
	  UINT8   Xmm1[16];
	  UINT8   Xmm2[16];
	  UINT8   Xmm3[16];
	  UINT8   Xmm4[16];
	  UINT8   Xmm5[16];
	  UINT8   Xmm6[16];
	  UINT8   Xmm7[16];
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
	  //
	  // NOTE: UEFI 2.0 spec definition as follows. It should be updated 
	  // after spec update.
	  //
	  UINT8   Reserved11[14 * 16];
#else
	  UINT8   Xmm8[16];
	  UINT8   Xmm9[16];
	  UINT8   Xmm10[16];
	  UINT8   Xmm11[16];
	  UINT8   Xmm12[16];
	  UINT8   Xmm13[16];
	  UINT8   Xmm14[16];
	  UINT8   Xmm15[16];
	  UINT8   Reserved10[6 * 16];
#endif
	} EFI_FX_SAVE_STATE_X64;
	
	typedef struct {
	  UINT64                ExceptionData;
	  EFI_FX_SAVE_STATE_X64 FxSaveState;
	  UINT64                Dr0;
	  UINT64                Dr1;
	  UINT64                Dr2;
	  UINT64                Dr3;
	  UINT64                Dr6;
	  UINT64                Dr7;
	  UINT64                Cr0;
	  UINT64                Cr1;  /* Reserved */
	  UINT64                Cr2;
	  UINT64                Cr3;
	  UINT64                Cr4;
	  UINT64                Cr8;
	  UINT64                Rflags;
	  UINT64                Ldtr;
	  UINT64                Tr;
	  UINT64                Gdtr[2];
	  UINT64                Idtr[2];
	  UINT64                Rip;
	  UINT64                Gs;
	  UINT64                Fs;
	  UINT64                Es;
	  UINT64                Ds;
	  UINT64                Cs;
	  UINT64                Ss;
	  UINT64                Rdi;
	  UINT64                Rsi;
	  UINT64                Rbp;
	  UINT64                Rsp;
	  UINT64                Rbx;
	  UINT64                Rdx;
	  UINT64                Rcx;
	  UINT64                Rax;
	  UINT64                R8;
	  UINT64                R9;
	  UINT64                R10;
	  UINT64                R11;
	  UINT64                R12;
	  UINT64                R13;
	  UINT64                R14;
	  UINT64                R15;
	} EFI_SYSTEM_CONTEXT_X64;


    // System context for Itanium processor family
    typedef struct {
        UINT64 Reserved;
        UINT64 R1, R2, R3, R4, R5, R6, R7, R8, R9, R10,
            R11, R12, R13, R14, R15, R16, R17, R18, R19, R20,
            R21, R22, R23, R24, R25, R26, R27, R28, R29, R30,
            R31;
        UINT64 F2[2], F3[2], F4[2], F5[2], F6[2],
            F7[2], F8[2], F9[2], F10[2], F11[2],
            F12[2], F13[2], F14[2], F15[2], F16[2],
            F17[2], F18[2], F19[2], F20[2], F21[2],
            F22[2], F23[2], F24[2], F25[2], F26[2],
            F27[2], F28[2], F29[2], F30[2], F31[2];
        UINT64 Pr;
        UINT64 B0, B1, B2, B3, B4, B5, B6, B7;
        // application registers
        UINT64 ArRsc, ArBsp, ArBspstore, ArRnat;
        UINT64 ArFcr;
        UINT64 ArEflag, ArCsd, ArSsd, ArCflg;
        UINT64 ArFsr, ArFir, ArFdr;
        UINT64 ArCcv;
        UINT64 ArUnat;
        UINT64 ArFpsr;
        UINT64 ArPfs, ArLc, ArEc;
        // control registers
        UINT64 CrDcr, CrItm, CrIva, CrPta, CrIpsr, CrIsr;
        UINT64 CrIip, CrIfa, CrItir, CrIipa, CrIfs, CrIim;
        UINT64 CrIha;
        // debug registers
        UINT64 Dbr0, Dbr1, Dbr2, Dbr3, Dbr4, Dbr5, Dbr6, Dbr7;
        UINT64 Ibr0, Ibr1, Ibr2, Ibr3, Ibr4, Ibr5, Ibr6, Ibr7;
        // virtual registers
        UINT64 IntNat; // nat bits for R1-R31
    } EFI_SYSTEM_CONTEXT_IPF;

    //
    // ARM processor context definition
    //
    typedef struct {
        UINT32 R0;
        UINT32 R1;
        UINT32 R2;
        UINT32 R3;
        UINT32 R4;
        UINT32 R5;
        UINT32 R6;
        UINT32 R7;
        UINT32 R8;
        UINT32 R9;
        UINT32 R10;
        UINT32 R11;
        UINT32 R12;
        UINT32 SP;
        UINT32 LR;
        UINT32 PC;
        UINT32 CPSR;
        UINT32 DFSR;
        UINT32 DFAR;
        UINT32 IFSR;
    } EFI_SYSTEM_CONTEXT_ARM;


    typedef union {
        EFI_SYSTEM_CONTEXT_EBC  *SystemContextEbc;
        EFI_SYSTEM_CONTEXT_IA32 *SystemContextIa32;
		EFI_SYSTEM_CONTEXT_X64  *SystemContextX64;
        EFI_SYSTEM_CONTEXT_IPF  *SystemContextIpf;
    } EFI_SYSTEM_CONTEXT;    

typedef VOID (*EFI_PERIODIC_CALLBACK) (
    IN OUT EFI_SYSTEM_CONTEXT SystemContext);    

typedef EFI_STATUS (EFIAPI *EFI_REGISTER_PERIODIC_CALLBACK) (
    IN EFI_DEBUG_SUPPORT_PROTOCOL *This,
    IN UINTN ProcessorIndex,
    IN EFI_PERIODIC_CALLBACK PeriodicCallback);

    typedef INTN EFI_EXCEPTION_TYPE;

    // EBC Exception types
    #define EXCEPT_EBC_UNDEFINED 0
    #define EXCEPT_EBC_DIVIDE_ERROR 1
    #define EXCEPT_EBC_DEBUG 2
    #define EXCEPT_EBC_BREAKPOINT 3
    #define EXCEPT_EBC_OVERFLOW 4
    #define EXCEPT_EBC_INVALID_OPCODE 5
    #define EXCEPT_EBC_STACK_FAULT 6
    #define EXCEPT_EBC_ALIGNMENT_CHECK 7
    #define EXCEPT_EBC_INSTRUCTION_ENCODING 8
    #define EXCEPT_EBC_BAD_BREAK 9
    #define EXCEPT_EBC_SINGLE_STEP 10

    // IA-32 Exception types
    #define EXCEPT_IA32_DIVIDE_ERROR 0
    #define EXCEPT_IA32_DEBUG 1
    #define EXCEPT_IA32_NMI 2
    #define EXCEPT_IA32_BREAKPOINT 3
    #define EXCEPT_IA32_OVERFLOW 4
    #define EXCEPT_IA32_BOUND 5
    #define EXCEPT_IA32_INVALID_OPCODE 6
    #define EXCEPT_IA32_DOUBLE_FAULT 8
    #define EXCEPT_IA32_INVALID_TSS 10
    #define EXCEPT_IA32_SEG_NOT_PRESENT 11
    #define EXCEPT_IA32_STACK_FAULT 12
    #define EXCEPT_IA32_GP_FAULT 13
    #define EXCEPT_IA32_PAGE_FAULT 14
    #define EXCEPT_IA32_FP_ERROR 16
    #define EXCEPT_IA32_ALIGNMENT_CHECK 17
    #define EXCEPT_IA32_MACHINE_CHECK 18
    #define EXCEPT_IA32_SIMD 19

    // Itanium Processor Family Exception types
    #define EXCEPT_IPF_VHTP_TRANSLATION 0
    #define EXCEPT_IPF_INSTRUCTION_TLB 1
    #define EXCEPT_IPF_DATA_TLB 2
    #define EXCEPT_IPF_ALT_INSTRUCTION_TLB 3
    #define EXCEPT_IPF_ALT_DATA_TLB 4
    #define EXCEPT_IPF_DATA_NESTED_TLB 5
    #define EXCEPT_IPF_INSTRUCTION_KEY_MISSED 6
    #define EXCEPT_IPF_DATA_KEY_MISSED 7
    #define EXCEPT_IPF_DIRTY_BIT 8
    #define EXCEPT_IPF_INSTRUCTION_ACCESS_BIT 9
    #define EXCEPT_IPF_DATA_ACCESS_BIT 10
    #define EXCEPT_IPF_BREAKPOINT 11
    #define EXCEPT_IPF_EXTERNAL_INTERRUPT 12
    // 13 - 19 reserved
    #define EXCEPT_IPF_PAGE_NOT_PRESENT 20
    #define EXCEPT_IPF_KEY_PERMISSION 21
    #define EXCEPT_IPF_INSTRUCTION_ACCESS_RIGHTS 22
    #define EXCEPT_IPF_DATA_ACCESS_RIGHTS 23
    #define EXCEPT_IPF_GENERAL_EXCEPTION 24
    #define EXCEPT_IPF_DISABLED_FP_REGISTER 25
    #define EXCEPT_IPF_NAT_CONSUMPTION 26
    #define EXCEPT_IPF_SPECULATION 27
    // 28 reserved
    #define EXCEPT_IPF_DEBUG 29
    #define EXCEPT_IPF_UNALIGNED_REFERENCE 30
    #define EXCEPT_IPF_UNSUPPORTED_DATA_REFERENCE 31
    #define EXCEPT_IPF_FP_FAULT 32
    #define EXCEPT_IPF_FP_TRAP 33
    #define EXCEPT_IPF_LOWER_PRIVILEGE_TRANSFER_TRAP 34
    #define EXCEPT_IPF_TAKEN_BRANCH 35
    #define EXCEPT_IPF_SINGLE_STEP 36
    // 37 - 44 reserved
    #define EXCEPT_IPF_IA32_EXCEPTION 45
    #define EXCEPT_IPF_IA32_INTERCEPT 46
    #define EXCEPT_IPF_IA32_INTERRUPT 47

    //
    // ARM processor exception types
    //
    #define EXCEPT_ARM_RESET 0
    #define EXCEPT_ARM_UNDEFINED_INSTRUCTION 1
    #define EXCEPT_ARM_SOFTWARE_INTERRUPT 2
    #define EXCEPT_ARM_PREFETCH_ABORT 3
    #define EXCEPT_ARM_DATA_ABORT 4
    #define EXCEPT_ARM_RESERVED 5
    #define EXCEPT_ARM_IRQ 6
    #define EXCEPT_ARM_FIQ 7
    //
    // For coding convenience, define the maximum valid ARM
    // exception.
    //
    #define MAX_ARM_EXCEPTION EXCEPT_ARM_FIQ

    typedef VOID (*EFI_EXCEPTION_CALLBACK) (
        IN EFI_EXCEPTION_TYPE ExceptionType,
        IN OUT EFI_SYSTEM_CONTEXT SystemContext);

typedef EFI_STATUS (EFIAPI *EFI_REGISTER_EXCEPTION_CALLBACK) (
    IN EFI_DEBUG_SUPPORT_PROTOCOL   *This,
    IN UINTN                        ProcessorIndex,
    IN EFI_EXCEPTION_CALLBACK       ExceptionCallback,
    IN EFI_EXCEPTION_TYPE           ExceptionType);
    
typedef EFI_STATUS (EFIAPI *EFI_INVALIDATE_INSTRUCTION_CACHE) (
    IN EFI_DEBUG_SUPPORT_PROTOCOL   *This,
    IN UINTN                        ProcessorIndex,
    IN VOID                         *Start,
    IN UINT64                       Length);
    

typedef struct _EFI_DEBUG_SUPPORT_PROTOCOL {
    EFI_INSTRUCTION_SET_ARCHITECTURE    Isa;
    EFI_GET_MAXIMUM_PROCESSOR_INDEX     GetMaximumProcessorIndex;
    EFI_REGISTER_PERIODIC_CALLBACK      RegisterPeriodicCallback;
    EFI_REGISTER_EXCEPTION_CALLBACK     RegisterExceptionCallback;
    EFI_INVALIDATE_INSTRUCTION_CACHE    InvalidateInstructionCache;
} EFI_DEBUG_SUPPORT_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
