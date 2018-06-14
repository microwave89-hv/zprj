//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/SMM.h 2     10/25/12 8:51a Wesleychen $
//
// $Revision: 2 $
//
// $Date: 10/25/12 8:51a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/SMM.h $
// 
// 2     10/25/12 8:51a Wesleychen
// Update Core to 4.6.5.4.
// 
// 8     6/22/11 2:39p Markw
// Add exclusions around typedef EFI_AP_PROCEDURE.
// 
// 7     2/05/11 1:53p Artems
// Redesigned to support both PI 0.91 and PI 1.0-1.1 requirements
// 
// 6     1/16/08 11:51a Markw
// Add CR4 to save state table.
// 
// 5     1/08/08 12:09p Markw
// small reformatting
// 
// 4     1/08/08 11:54a Markw
// Add GDTand IDT to EFI_SMI_CPU_STATE.
// 
// 3     5/25/06 9:53a Markw
// 
// 2     1/10/06 2:54p Markw
// Add SMM Mp Service.
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     2/10/04 10:31a Markw
// 
// 1     1/26/04 3:25p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: Smm.h
//
// Description: Smst table definitions.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __SMM__H__
#define __SMM__H__

#include <efi.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SMM_SMST_SIGNATURE 'TSMS'
#define EFI_SMM_SYSTEM_TABLE_REVISION (0<<16) | (0x09)

#define EFI_SMM_CPU_IO_GUID \
    {0x5f439a0b,0x45d8,0x4682,0xa4,0xf4,0xf0,0x57,0x6b,0x51,0x34,0x41}

GUID_VARIABLE_DECLARATION(gEfiSmmCpuIoGuid,EFI_SMM_CPU_IO_GUID);

typedef struct {
    UINT8  Reserved1[240];
    UINT32  CR4;
    UINT32  Reserved2;
    UINT32  SMBASE;
    UINT32  SMMRevId;
    UINT16  IORestart;
    UINT16  AutoHALTRestart;
    UINT8   Reserved3[132];
    UINT32  GDTBase;
    UINT8   Reserved4[8];
    UINT32  IDTBase;
    UINT8   Reserved5[16];
    UINT32  ES;
    UINT32  CS;
    UINT32  SS;
    UINT32  DS;
    UINT32  FS;
    UINT32  GS;
    UINT32  LDTBase;
    UINT32  TR;
    UINT32  DR7;
    UINT32  DR6;
    UINT32  EAX;
    UINT32  ECX;
    UINT32  EDX;
    UINT32  EBX;
    UINT32  ESP;
    UINT32  EBP;
    UINT32  ESI;
    UINT32  EDI;
    UINT32  EIP;
    UINT32  EFLAGS;
    UINT32  CR3;
    UINT32  CR0;
} EFI_SMI_CPU_SAVE_STATE;

typedef struct {
    UINT64  reserved;
    UINT64  r1;
    UINT64  r2;
    UINT64  r3;
    UINT64  r4;
    UINT64  r5;
    UINT64  r6;
    UINT64  r7;
    UINT64  r8;
    UINT64  r9;
    UINT64  r10;
    UINT64  r11;
    UINT64  r12;
    UINT64  r13;
    UINT64  r14;
    UINT64  r15;
    UINT64  r16;
    UINT64  r17;
    UINT64  r18;
    UINT64  r19;
    UINT64  r20;
    UINT64  r21;
    UINT64  r22;
    UINT64  r23;
    UINT64  r24;
    UINT64  r25;
    UINT64  r26;
    UINT64  r27;
    UINT64  r28;
    UINT64  r29;
    UINT64  r30;
    UINT64  r31;
    UINT64  pr;
    UINT64  b0;
    UINT64  b1;
    UINT64  b2;
    UINT64  b3;
    UINT64  b4;
    UINT64  b5;
    UINT64  b6;
    UINT64  b7;

    // application registers
    UINT64  ar_rsc;
    UINT64  ar_bsp;
    UINT64  ar_bspstore;
    UINT64  ar_rnat;
    UINT64  ar_fcr;
    UINT64  ar_eflag;
    UINT64  ar_csd;
    UINT64  ar_ssd;
    UINT64  ar_cflg;
    UINT64  ar_fsr;
    UINT64  ar_fir;
    UINT64  ar_fdr;
    UINT64  ar_ccv;
    UINT64  ar_unat;
    UINT64  ar_fpsr;
    UINT64  ar_pfs;
    UINT64  ar_lc;
    UINT64  ar_ec;

    // control registers
    UINT64  cr_dcr;
    UINT64  cr_itm;
    UINT64  cr_iva;
    UINT64  cr_pta;
    UINT64  cr_ipsr;
    UINT64  cr_isr;
    UINT64  cr_iip;
    UINT64  cr_ifa;
    UINT64  cr_itir;
    UINT64  cr_iipa;
    UINT64  cr_ifs;
    UINT64  cr_iim;
    UINT64  cr_iha;

    // debug registers
    UINT64  dbr0;
    UINT64  dbr1;
    UINT64  dbr2;
    UINT64  dbr3;
    UINT64  dbr4;
    UINT64  dbr5;
    UINT64  dbr6;
    UINT64  dbr7;
    UINT64  ibr0;
    UINT64  ibr1;
    UINT64  ibr2;
    UINT64  ibr3;
    UINT64  ibr4;
    UINT64  ibr5;
    UINT64  ibr6;
    UINT64  ibr7;

    // virtual registers
    UINT64  int_nat;    // nat bits for R1-R31
} EFI_PMI_SYSTEM_CONTEXT;

typedef union {
    EFI_SMI_CPU_SAVE_STATE  Ia32SaveState;
    //P072911: Make this structure is the same with SmmBase.h
    //EFI_PMI_SYSTEM_CONTEXT  ItaniumSaveState;
} EFI_SMM_CPU_SAVE_STATE;

////////////////////////////////////////////////////////////////////////

typedef struct {
    UINT16  Fcw;
    UINT16  Fsw;
    UINT16  Ftw;
    UINT16  Opcode;
    UINT32  Eip;
    UINT16  Cs;
    UINT16  Rsvd1;
    UINT32  DataOffset;
    UINT16  Ds;
    UINT8   Rsvd2[10];
    UINT8   St0Mm0[10], Rsvd3[6];
    UINT8   St0Mm1[10], Rsvd4[6];
    UINT8   St0Mm2[10], Rsvd5[6];
    UINT8   St0Mm3[10], Rsvd6[6];
    UINT8   St0Mm4[10], Rsvd7[6];
    UINT8   St0Mm5[10], Rsvd8[6];
    UINT8   St0Mm6[10], Rsvd9[6];
    UINT8   St0Mm7[10], Rsvd10[6];
    UINT8   Rsvd11[22*16];
} EFI_SMI_OPTIONAL_FPSAVE_STATE;

typedef struct {
    UINT64  f2[2];
    UINT64  f3[2];
    UINT64  f4[2];
    UINT64  f5[2];
    UINT64  f6[2];
    UINT64  f7[2];
    UINT64  f8[2];
    UINT64  f9[2];
    UINT64  f10[2];
    UINT64  f11[2];
    UINT64  f12[2];
    UINT64  f13[2];
    UINT64  f14[2];
    UINT64  f15[2];
    UINT64  f16[2];
    UINT64  f17[2];
    UINT64  f18[2];
    UINT64  f19[2];
    UINT64  f20[2];
    UINT64  f21[2];
    UINT64  f22[2];
    UINT64  f23[2];
    UINT64  f24[2];
    UINT64  f25[2];
    UINT64  f26[2];
    UINT64  f27[2];
    UINT64  f28[2];
    UINT64  f29[2];
    UINT64  f30[2];
    UINT64  f31[2];
} EFI_PMI_OPTIONAL_FLOATING_POINT_CONTEXT;

typedef union {
    EFI_SMI_OPTIONAL_FPSAVE_STATE           Ia32FpSave;
    EFI_PMI_OPTIONAL_FLOATING_POINT_CONTEXT ItaniumFpSave;
} EFI_SMM_FLOATING_POINT_SAVE_STATE;

////////////////////////////////////////////////////////////////////////

typedef EFI_STATUS (EFIAPI *EFI_SMM_HANDLER_ENTRY_POINT) (
    IN EFI_HANDLE   SmmImageHandle,
    IN OUT VOID     *CommunicationBuffer OPTIONAL,
    IN OUT UINTN    *SourceSize OPTIONAL
);

typedef struct _EFI_SMM_SYSTEM_TABLE EFI_SMM_SYSTEM_TABLE;

typedef EFI_STATUS (EFIAPI *EFI_SMM_INSTALL_CONFIGURATION_TABLE) (
    IN EFI_SMM_SYSTEM_TABLE *SystemTable,
    IN EFI_GUID             *Guid,
    IN VOID                 *Table,
    IN UINTN                TableSize
);

#ifndef EFI_SMM_IO_WIDTH_DEF
#define EFI_SMM_IO_WIDTH_DEF
typedef enum {
    SMM_IO_UINT8 = 0,
    SMM_IO_UINT16 = 1,
    SMM_IO_UINT32 = 2,
    SMM_IO_UINT64 = 3
} EFI_SMM_IO_WIDTH;
#endif

typedef struct _EFI_SMM_CPU_IO_INTERFACE EFI_SMM_CPU_IO_INTERFACE;

typedef EFI_STATUS (EFIAPI * EFI_SMM_CPU_IO) (
    IN EFI_SMM_CPU_IO_INTERFACE *This,
    IN EFI_SMM_IO_WIDTH         Width,
    IN UINT64                   Address,
    IN UINTN                    Count,
    IN OUT VOID                 *Buffer
);

typedef struct {
    EFI_SMM_CPU_IO  Read;
    EFI_SMM_CPU_IO  Write;
} EFI_SMM_IO_ACCESS;

struct _EFI_SMM_CPU_IO_INTERFACE {
    EFI_SMM_IO_ACCESS   Mem;
    EFI_SMM_IO_ACCESS   Io;
};

#ifndef EFI_AP_PROCEDURE_TYPE_DEFINED
#define EFI_AP_PROCEDURE_TYPE_DEFINED
typedef VOID (*EFI_AP_PROCEDURE) (
    IN VOID                     *Buffer
);
#endif

typedef EFI_STATUS (EFIAPI *EFI_SMM_STARTUP_THIS_AP) (
    IN EFI_AP_PROCEDURE         Procedure,
    IN UINTN                    CpuNumber,
    IN OUT VOID                 *ProcArguments  OPTIONAL
);

struct _EFI_SMM_SYSTEM_TABLE {
    EFI_TABLE_HEADER                    Hdr;
    CHAR16                              *SmmFirmwareVendor;
    UINT32                              SmmFirmwareRevision;
    
    EFI_SMM_INSTALL_CONFIGURATION_TABLE SmmInstallConfigurationTable;
    
    // I/O Services
    EFI_GUID                            EfiSmmCpuIoGuid;
    EFI_SMM_CPU_IO_INTERFACE            SmmIo;
    
    // Runtime memory service
    EFI_ALLOCATE_POOL                   SmmAllocatePool;
    EFI_FREE_POOL                       SmmFreePool;
    EFI_ALLOCATE_PAGES                  SmmAllocatePages;
    EFI_FREE_PAGES                      SmmFreePages;
    
    // Mp service
    EFI_SMM_STARTUP_THIS_AP             SmmStartupThisAp;

    // CPU information records
    UINTN                               CurrentlyExecutingCpu;
    UINTN                               NumberOfCpus;
    EFI_SMM_CPU_SAVE_STATE              *CpuSaveState;
    EFI_SMM_FLOATING_POINT_SAVE_STATE   *CpuOptionalFloatingPointState;
    
    // Extensibility table
    UINTN                               NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE             *SmmConfigurationTable;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
