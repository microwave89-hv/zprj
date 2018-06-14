//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CPUCspLib.h 5     2/07/13 3:57a Hsingyingchung $
//
// $Revision: 5 $
//
// $Date: 2/07/13 3:57a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CPUCspLib.h $
// 
// 5     2/07/13 3:57a Hsingyingchung
// [TAG]  		EIP112631
// [Category]  	Improvement
// 
// 4     12/20/12 10:27a Hsingyingchung
// [TAG]  		EIP108128
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	"Max non-turbo ratio" can't show in BIOS setup when first
// boot after flashing BIOS
// [RootCause]  	Doesn't initialize max non-turbo ratio value when first
// boot after flashing BIOS.
// [Solution]  	Add initialize code for max non-turbo ratio.
// 
// 3     11/23/12 2:08a Hsingyingchung
// [TAG]  		EIP99095
// [Category]  	Improvement
// [Description]  	Update by XTU 4.X
// 
// 2     5/17/12 9:40p Davidhsieh
// 
// 1     2/07/12 3:58a Davidhsieh
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:        CpuCspLib.h
//
// Description: Header file for Cpu Csp Lib.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __CPULIB_H__
#define __CPULIB_H__

#include <efi.h>
#include <pei.h>
#include "amihobs.h"
#include "smm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    EFI_STATUS_CODE_DATA    DataHeader;
    UINT32                  Bist;
} AMI_STATUS_CODE_CPU_BIST_DATA;

#pragma pack(push, 1)

typedef struct {
    UINT32 HeaderVersion;
    UINT32 UpdateRevision;
    UINT32 Date;
    UINT32 CpuSignature;
    UINT32 Checksum;
    UINT32 LoaderRevison;
    UINT32 Flags:8;
    UINT32 RV3:24;
    UINT32 DataSize;
    UINT32 TotalSize;
    UINT32 RV4[3];
} MICROCODE_HEADER;

typedef struct {
    UINT32  CpuSignature;
    UINT32  Flags;
    UINT32  Checksum;
} PROC_SIG;

typedef struct {
    UINT32      Count;
    UINT32      Checksum;
    UINT8       Rsv[12];
    PROC_SIG    ProcSig[1];
} MICROCODE_EXT_PROC_SIG_TABLE;

#pragma pack(pop)

// {CD541D77-6699-4b36-A31E-1AA4C5D5B946}
#define AMI_STATUS_CODE_CPU_BIST_DATA_GUID \
    {0xcd541d77, 0x6699, 0x4b36, 0xa3, 0x1e, 0x1a, 0xa4, 0xc5, 0xd5, 0xb9, 0x46}

UINT64  ReadMsr (UINT32 Msr);
VOID    WriteMsr(UINT32 Msr, UINT64 Value);
VOID    ReadWriteMsr(UINT32 Msr, UINT64 Value, UINT64 Mask);
VOID    CPULib_CpuID(UINT32 CpuIDIndex, UINT32 * RegEAX, UINT32 * RegEBX, 
                UINT32 * RegECX, UINT32 * RegEDX);
UINT32  GetCpuSignature();
UINT32  GetCpuFamily(UINT32 CpuSignature);
UINT32  GetCpuModel(UINT32 CpuSignature);
UINT32  GetCpuPlatformId();
UINT32  GetSmrrBaseMsr();
UINT8   NumSupportedThreadsPerCore();
UINT8   NumSupportedCpuCores();
UINT8   NumCpuCores();
UINT8   NumLogicalCpus();
BOOLEAN IsHtEnabled();
BOOLEAN IsHt0();
BOOLEAN IsCore0();
BOOLEAN isXDSupported(CPU_FEATURES *Features);
BOOLEAN isTurboModeSupported();
BOOLEAN isFullUnlockCpuSuuported();
BOOLEAN isXETdcTdpLimitSupported();
BOOLEAN isXECoreRatioLimitSupported();
BOOLEAN isLimitCpuidSupported();
BOOLEAN IsMachineCheckSupported(CPU_FEATURES *Features);
BOOLEAN IsEnergyPerfBiasSupported();
BOOLEAN IsCxInterruptFilteringSupported();
BOOLEAN IsVmxSupported(CPU_FEATURES *Features);
BOOLEAN IsSmxSupported(CPU_FEATURES *Features);
BOOLEAN IsSmrrSupported(CPU_FEATURES *Features);
BOOLEAN IsX64Supported(CPU_FEATURES *Features);

BOOLEAN CPULib_IsVmxEnabled();
BOOLEAN CPULib_IsSmxEnabled();
BOOLEAN CPULib_IsSmrrEnabled();
BOOLEAN CPULib_IsLocalX2ApicEnabled();
BOOLEAN CPULib_IsFeatureControlLocked();
UINT32  NumberOfCpuSocketsPopulated();
VOID    DisableCacheInCR0();
VOID    EnableCacheInCR0();
VOID    CPULib_DisableInterrupt();
VOID    CPULib_EnableInterrupt();
BOOLEAN CPULib_GetInterruptState();
VOID*   CPULIB_GetPageTable();
VOID    CPULib_Pause();
UINT16  GetCsSegment();
UINT64  ReadRtdsc();
VOID    WaitForever();
VOID    HltCpu();
VOID    WaitForSemaphore(volatile VOID*);
VOID    WaitUntilZero8(volatile VOID*);
VOID    WaitUntilZero32(volatile VOID*);
UINT16  GetCsSegment();
UINT32  CPULIB_GetCstateLatency(IN UINT8 Cstate);
UINT32  CPULIB_GetCstatePower(IN UINT8 Cstate);
VOID*   CPULib_FindMicrocode();
UINT32  CPULib_GetMicrocodeVer();
VOID    ClearDirectionFlag();

UINT32 SmmGetBaseSaveBufferSize();
VOID SmmSetupDefaultHandler(IN VOID *SmmBaseSaveBuffer, IN SMM_HOB *SmmHob);
VOID SmmRemoveDefaultHandler(IN VOID *SmmBaseSaveBuffer);
VOID SmmBaseChangeOnCpu(VOID *SmmBase);

VOID CPU_GetSaveState (
    UINT8                       *SmmBase, 
    EFI_SMI_CPU_SAVE_STATE      *SstSaveState);

VOID CPU_RestoreSaveState(
    UINT8                       *SmmBase, 
    EFI_SMI_CPU_SAVE_STATE      *SstSaveState);

VOID CPU_SmmMemoryInit(IN SMM_HOB *SmmHob);

typedef struct {
    UINT8 ClkModEn;     //> 0 if Clk Mod En.
} CPU_LIB_SMM_SAVE_RESTORE_DATA;

VOID CpuLib_SmmSaveCpuState(IN OUT CPU_LIB_SMM_SAVE_RESTORE_DATA*);
VOID CpuLib_SmmRestoreCpuState(IN CPU_LIB_SMM_SAVE_RESTORE_DATA*);

BOOLEAN IsSwSmiTrigger(UINT8 *SmmBase, UINT16 SwSmiPort);

EFI_STATUS CPULib_SmmReadSaveState(
    UINT8       *SmmBase, 
    UINT8		*SstSaveState,
    BOOLEAN     UseSstSaveState,
    IN UINT8    Width,
    IN UINT32	Register,
    OUT VOID    *Buffer
);
EFI_STATUS CpuLib_SmmReadSaveStateFxSave(
        IN UINT8    *FxSave,
        IN UINT8    Width,
        IN UINT32   Register,
        OUT VOID    *Buffer
);
EFI_STATUS CPULib_SmmWriteSaveState(
    UINT8       *SmmBase, 
    UINT8		*SstSaveState,
    BOOLEAN     UseSstSaveState,
    IN UINT8    Width,
    IN UINT32	Register,
    OUT CONST VOID    *Buffer
);
EFI_STATUS CpuLib_SmmWriteSaveStateFxSave(
        IN UINT8    *FxSave,
        IN UINT8    Width,
        IN UINT32   Register,
        OUT VOID    *Buffer
);

EFI_STATUS CPUProgramPAMRegisters(
    EFI_BOOT_SERVICES       *gBS, EFI_RUNTIME_SERVICES  *gRS,
    UINT32 StartAddress, UINT32 Length, UINT8   Setting, UINT32 *Granularity
);

VOID EnableMachineCheck();

VOID CPULib_LockByteInc(UINT8* ptr);
VOID CPULib_LockByteDec(UINT8* ptr);
VOID CPULib_LoadGdt(VOID *ptr);
VOID CPULib_SaveGdt(VOID *ptr);
VOID CPULib_LoadIdt(VOID *ptr);
VOID CPULib_SaveIdt(VOID *ptr);

UINT32 MemRead32(UINT32 *Address);
VOID MemReadWrite32(UINT32 *Address, UINT32 Value, UINT32 Mask);

UINT8 IsPowerCycle();
BOOLEAN isBCLKRatioSuuported();
EFI_STATUS GetOcCapability(IN UINT8 DomainID, OUT UINT64 *MsrBuf);
EFI_STATUS GetSVIDConfig(OUT UINT64 *MsrBuf);
EFI_STATUS GetVoltFreq(IN UINT8 DomainID, OUT UINT64 *MsrBuf);
EFI_STATUS GetFIVRConfig(OUT UINT64 *MsrBuf);


#ifdef PERF_TUNE_SUPPORT
#if PERF_TUNE_SUPPORT == 1

#define AMI_OVERCLOCK_CONFIG_HOB_GUID \
 {0x27a29ef7, 0x90e7, 0x4592, 0x99, 0xbe, 0xa3, 0xae, 0x97, 0xca, 0xdb, 0x2a}

#define AMI_INTERNAL_CPU_RATIO_LIMIT \
 {0xdf2982fa, 0xaa6c, 0x4b8d, 0x8a, 0x82, 0x85, 0xf8, 0x1e, 0xe8, 0x72, 0x19}

#pragma pack(1)
//Domain ID define
#define DOMAIN_MAX_NUM 6
#define IA 0
#define GT 1
#define RING 2
#define SA 3
#define IOD 4
#define IOA 5

typedef struct {
  UINT8 	MaxOcRatioLimit;
  BOOLEAN	RatioOcSupported;
  BOOLEAN	VoltageOverridesSupported;
  BOOLEAN	VoltageOffsetSupported;
} OC_CAP_ITEM; //overclocking capability

typedef struct {
  UINT8     MaxOcRatio;
  BOOLEAN   VoltageTargetMode;  // 0: Adaptive, 1: Override
  UINT16	VoltageTarget;
  INT16	    VoltageOffset;
} VOLT_FREQ_DEF_ITEM;

typedef struct {
  OC_CAP_ITEM           OCCap[DOMAIN_MAX_NUM]; 
  VOLT_FREQ_DEF_ITEM    VFDef[DOMAIN_MAX_NUM]; 
  BOOLEAN               SvidDisable;           // 0: Disable, 1: Enable
  UINT16                SvidVoltageOverride;   // External VR voltage override
  BOOLEAN               FivrFaultsDisable;     // 0: Disable, 1: Enable
  BOOLEAN               FivrEfficiencyDisable; // 0: Disable, 1: Enable
  BOOLEAN               OcSupport;
  UINT8 				IsPowerCycle;           // 0: Not power cycle, 1: power cycle
  UINT8                 IsCpuRunDefault;        // 0: Not run default, 1: Cpu Change, 2:Watch Dog timeout
} OVERCLOCKING_CONFIG_DATA;

typedef struct _OVERCLOCKING_CONFIG_HOB {
	EFI_HOB_GUID_TYPE	        EfiHobGuidType;
	OVERCLOCKING_CONFIG_DATA	OverclockData;
} OVERCLOCKING_CONFIG_HOB;

typedef struct {
  UINT8                MaxNonTurboRatio;
} CPU_RATIO_LIMIT_DATA;

typedef struct _CPU_RATIO_LIMIT_HOB {
	EFI_HOB_GUID_TYPE	        EfiHobGuidType;
	CPU_RATIO_LIMIT_DATA	    CpuRatioLimitData;
    BOOLEAN                     IsChangeCpu;
} CPU_RATIO_LIMIT_HOB;

#pragma pack()

#endif  //end of #if PERF_TUNE_SUPPORT == 1
#endif  //end of #ifdef PERF_TUNE_SUPPORT == 1

#ifdef __cplusplus
}
#endif
#endif


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-20113, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

