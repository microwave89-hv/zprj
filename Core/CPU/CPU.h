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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CPU.h 3     10/17/12 2:20a Davidhsieh $
//
// $Revision: 3 $
//
//
// $Date: 10/17/12 2:20a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CPU.h $
// 
// 3     10/17/12 2:20a Davidhsieh
// [TAG]                None
// [Category]         Improvement
// [Description]      Setup items CTDP BIOS, C8, C9 and C10 created
// 
// 2     9/26/12 10:53a Davidhsieh
// [TAG]              None
// [Description]    Add CPU APIC ID data variable for S3 resume
// 
// 1     2/07/12 3:58a Davidhsieh
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		Cpu.h
//
// Description:	Common header for the CPU.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __CPU_H__
#define __CPU_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <efi.h>

#ifdef PEI_COMPILE		//In PEI, this must be defined before including this file.
#include <pei.h>
#include <Ppi/Stall.h>
#endif

#define MP_CPU_APIC_ID_DATA_GUID \
    {0x1456cc6e, 0x22ac, 0x5289, 0x33, 0xba, 0x2e, 0x13, 0xbb, 0xda, 0xba, 0xee}
    
// Define the equates here
//CPU APIC includes
#define APIC_ALL_EXCLUDING_SELF	(3 << 18)
#define APIC_SIPI			    (6 << 8)
#define APIC_INIT			    (5 << 8)
#define APIC_SMI                (2 << 8)
#define APIC_DELIVERY_STATUS    (1 << 12)
#define APIC_LEVEL_ASSERT	    (1 << 14)
#define APIC_LEVEL_DEASSERT	    (0 << 14)
#define APIC_NO_SHORT_HAND      (0 << 18)


#define	MSR_XAPIC_BASE				0x1B
#define		XAPIC_BASE_BSP_BIT		8
#define     XAPIC_X2APIC_ENABLE_BIT 10
#define		XAPIC_GLOBAL_ENABLE_BIT	11


#define	XAPIC_ENABLE_BIT			8	// SVR SW APIC Enable/Disable Bit
#define	APIC_PRESENT_BIT			9	// APIC Present bit in Feature Flags

#define	MASK_ICR_CLEAR				0xFFF33000	// AND mask for ICR reserved bit
#define	OR_MASK_INIT_IPI			0x00004500	// OR mask to send INIT IPI
#define	OR_MASK_USE_DEST_FIELD		0x00000000	// OR mask to set dest field = "Dest Field"

//Cstate
#define C1_SUB_STATES_MASK	  0x000000f0
#define C3_SUB_STATES_MASK	  0x00000f00
#define	C6_SUB_STATES_MASK	  0x0000f000
#define	C7_SUB_STATES_MASK	  0x000f0000
#define	C8_SUB_STATES_MASK	  0x00f00000
#define	C9_SUB_STATES_MASK	  0x0f000000
#define	C10_SUB_STATES_MASK	  0xf0000000

//-----------------------------------------------------------------------------
//              Local APIC Register Equates
//-----------------------------------------------------------------------------
#define	LOCAL_APIC_ID               0x20
#define	LOCAL_APIC_VERSION          0x30
#define	LOCAL_APIC_TASK_PRI         0x80
#define	LOCAL_APIC_ARB_PRI          0x90
#define	LOCAL_APIC_PROC_PRI         0xa0
#define	LOCAL_APIC_EOI              0xb0
#define	LOCAL_APIC_LDR              0xd0
#define	LOCAL_APIC_DEST_FORMAT      0xe0
#define	LOCAL_APIC_SVR              0xf0
#define	LOCAL_APIC_ISR0             0x100
#define	LOCAL_APIC_TMR0             0x180
#define	LOCAL_APIC_IRR0             0x200
#define	LOCAL_APIC_ERR_STAT         0x280
#define	LOCAL_APIC_ICR_LO           0x300
#define	LOCAL_APIC_ICR_HI           0x310
#define	LOCAL_APIC_LVT              0x320
#define	LOCAL_APIC_PERF             0x340
#define	LOCAL_APIC_LVT_LINT0        0x350
#define	LOCAL_APIC_LVT_LINT1        0x360
#define	LOCAL_APIC_LVT_ERR          0x370
#define	LOCAL_APIC_ITC              0x380
#define	LOCAL_APIC_TIMER            0x390
#define	LOCAL_APIC_TMR_DIV          0x3e0

#define PSD_SW_ALL  0xfc
#define PSD_SW_ANY  0xfd
#define PSD_HW_ALL  0xfe

#define TSD_HW_ALL  0xfe

#define MSR_IA32_PLATFORM_ID        0x17
#define MSR_CHL_CONTROLS            0x2d
  #define  B_FORWARD_CODE_DISABLE       (1<<9)
#define MSR_IA32_CR_PIC_MSG_CONTROL 0x2e
#define MSR_CORE_THREAD_COUNT       0x35
#define MSR_IA32_FEATURE_CONTROL    0x3a
  #define SMRR_LOCK_BIT                 0x1
  #define SMRR_ENABLE_BIT               0x3
  #define SMRR_ENABLE_MASK              (1<<3)
#define MSR_SMM_SAVE_CONTROL        0x3e  
#define MSR_IA32_BIOS_UPDT_TRIG     0x79
#define MSR_IA32_BIOS_SIGN_ID       0x8b
#define MSR_PMG_CST_CONFIG_CONTROL  0xe2
#define MSR_PMG_IO_CAPTURE_ADDR     0xe4
#define MSR_PLATFORM_INFO           0xce
  #define TCC_ACTIVE_OFFSET_PROGRAMMABLE_BIT 30
  #define XE_TDP_TDC_PROGRAMMABLE_BIT		29
  #define XE_CORE_RATIO_PROGRAMMABLE_BIT	28
  #define SMM_SAVE_CONTROL_BIT	16
  #define MAX_NON_TURBO_RATIO_OFFSET	8
  #define MAX_NON_TURBO_RATIO_MASK	0xff 
#define MSR_FEATURE_CONFIG       0x13c
  #define MSR_FEATURE_CONFIG_LOCK   1
#define MSR_IA32_MCG_CAP         0x179
#define MSR_IA32_MCG_CTL         0x17b
#define MSR_FLEX_RATIO           0x194
#define MSR_IA32_PERF_STATUS     0x198
#define MSR_IA32_PERF_CTL        0x199
#define MSR_IA32_CLOCK_MODULATION 0x19a
  #define CLK_MOD_ENABLE             0x10
#define MSR_IA32_MISC_ENABLE     0x1a0
  #define TURBO_DISABLE_MASK         ((UINT64)1 << 38)
  #define TURBO_MODE_DISABLE_BIT 38
#define MSR_MISC_FEATURE_CONTROL	0x1a4
  #define DATA_REUSE_OPT            0x40
  #define DCU_IP_PREFETCHER         0x8
  #define DCU_STREAMER_PREFETCHER   0x4
  #define MLC_SPATIAL_PREFETCHER	0x2
  #define MLC_STREAMER_PREFETCHER   0x1
#define MSR_MISC_PWR_MGMT       0x1aa
  #define EIST_HW_COORD_DIS_BIT 0
  #define ENG_PERF_BIAS_EN_BIT  1
  #define LOCK_TM_INT_BIT       22
#define MSR_TURBO_POWER_CURRENT_LIMIT 0x1ac
  #define TDC_LIMIT_OVERRIDE_ENABLE_BIT	31
  #define TDC_LIMIT_MASK		0x7FFF0000
  #define TDC_LIMIT_OFFSET	16
  #define TDP_LIMIT_OVERRIDE_ENABLE_BIT	15
  #define TDP_LIMIT_MASK		0x7FFF
  #define TDP_LIMIT_OFFSET	0 
#define MSR_TURBO_RATIO_LIMIT		0x1ad
  #define MAX_RATIO_LIMIT_8C_OFFSET	56
  #define MAX_RATIO_LIMIT_7C_OFFSET	48
  #define MAX_RATIO_LIMIT_6C_OFFSET	40
  #define MAX_RATIO_LIMIT_5C_OFFSET	32
  #define MAX_RATIO_LIMIT_4C_OFFSET	24
  #define MAX_RATIO_LIMIT_3C_OFFSET	16
  #define MAX_RATIO_LIMIT_2C_OFFSET	8
  #define MAX_RATIO_LIMIT_1C_OFFSET	0
  #define MAX_RATIO_LIMIT_MASK		0xff
#define MSR_IA32_ENERGY_PERF_BIAS   0x1b0
#define MSR_FERR_CAPABILITY         0x1f1
#define MSR_EMRR_PHYSBASE           0x1f4
#define MSR_EMRR_PHYSMASK           0x1f5
#define  B_EMRR_VALID                (1 << 11)
#define MSR_IA32_PLATFORM_DCA_CAP   0x1f8
#define MSR_IA32_DCA_CAP            0x1f9
#define MSR_IA32_DCA_0_CAP          0x1fa
#define MSR_POWER_CTL               0x1fc
#define MSR_IA32_MC0_CTL            0x400
#define MSR_IA32_MC0_STATUS         0x401

// Generic MTRR equates
#define MTRR_ATTRIB_WB           6

#define MSR_IA32_MTRR_CAP        0xfe
  #define SMRR_SUPPORT_BIT       11
  #define SMRR_SUPPORT_MASK      (1 << 11)
  #define EMRR_SUPPORT_MASK      (1 << 12)
#define	MTRR_PHYS_BASE_0		0x200
#define	MTRR_PHYS_MASK_0		0x201
#define	MTRR_PHYS_BASE_1		0x202
#define	MTRR_PHYS_MASK_1		0x203
#define	MTRR_PHYS_BASE_2		0x204
#define	MTRR_PHYS_MASK_2		0x205
#define	MTRR_PHYS_BASE_3		0x206
#define	MTRR_PHYS_MASK_3		0x207
#define	MTRR_PHYS_BASE_4		0x208
#define	MTRR_PHYS_MASK_4		0x209
#define	MTRR_PHYS_BASE_5		0x20a
#define	MTRR_PHYS_MASK_5		0x20b
#define	MTRR_PHYS_BASE_6		0x20c
#define	MTRR_PHYS_MASK_6		0x20d
#define	MTRR_PHYS_BASE_7		0x20e
#define	MTRR_PHYS_MASK_7		0x20f
#define	MTRR_FIX_64K_00000		0x250
#define	MTRR_FIX_16K_80000		0x258
#define	MTRR_FIX_16K_A0000		0x259
#define	MTRR_FIX_4K_C0000		0x268
#define	MTRR_FIX_4K_C8000		0x269
#define	MTRR_FIX_4K_D0000		0x26a
#define	MTRR_FIX_4K_D8000		0x26b
#define	MTRR_FIX_4K_E0000		0x26c
#define	MTRR_FIX_4K_E8000		0x26d
#define	MTRR_FIX_4K_F0000		0x26e
#define	MTRR_FIX_4K_F8000		0x26f
#define MSR_IA32_MC8_CTL2       0x288
#define	MTRR_DEF_TYPE			0x2ff
#define MSR_NO_EVICT_MODE       0x2e0
#define   B_MSR_NO_EVICT_MODE_SETUP 1
#define   B_MSR_NO_EVICT_MODE_RUN   2
#define MSR_UNCORE_CR_MEMLOCK_COMMANDS  0x2e2

#define MSR_PP0_CURRENT_CONFIG      0x601
#define MSR_PP1_CURRENT_CONFIG      0x602
#define MSR_PACKAGE_POWER_SKU_LIMIT 0x606
#define MSR_PKGC3_IRTL              0x60a
#define MSR_PKGC6_IRTL              0x60b
#define MSR_PKGC7_IRTL              0x60c
#define MSR_TURBO_POWER_LIMIT       0x610
  #define POWER_LIMIT_1_MASK	    0x7fff
  #define POWER_LIMIT_1_TIME_MASK   0xfe0000
  #define POWER_LIMIT_2_MASK        (UINT64)0x7fff00000000
#define MSR_PACKAGE_POWER_SKU       0x614
#define MSR_PP0_POWER_LIMIT         0x638
#define MSR_PP1_POWER_LIMIT         0x640

#define MSR_EXT_XAPIC_LOGICAL_APIC_ID   0x802
#define MSR_EXT_XAPIC_VERSION           0x803
#define MSR_EXT_XAPIC_SVR               0x80f
#define  B_MSR_XAPIC_SVR_SOFTWARE_ENABLE    (1 << 8)
#define MSR_EXT_XAPIC_ICR               0x830
#define MSR_EXT_XAPIC_LVT_LINT0         0x835
#define MSR_EXT_XAPIC_LVT_LINT1         0x836

#define GAINESTOWN      0x106a0
#define WESTMERE        0x206c0
#define NEHALEM_EX      0x206e0
#define WESTMERE_EX     0x206f0
#define SANDY_BRIDGE    0x206a0
#define JAKETOWN        0x206d0
#define IVY_BRIDGE      0x306a0

#define NUM_OF_FIXED_MTRRS      11

VOID LockInc32(UINT32 *);

typedef struct {
    UINT32 SmrrSupport:1;
    UINT32 DcaSupport:1;
    UINT32 Rsv1:30;
    UINT32 Rsv2:32;
} BOARD_ADDITIONAL_FEATURE_FLAGS;

typedef struct {
    UINT32 FeatureEcx;
    UINT32 FeatureEdx;
    UINT32 ExtFeatureEax;
    UINT32 ExtFeatureEbx;
    UINT32 ExtFeatureEcx;
    UINT32 ExtFeatureEdx;
    BOARD_ADDITIONAL_FEATURE_FLAGS Flags;
} BOARD_CPU_FEATURES;

UINT32 GetMinCpuFeatures(
    IN UINT8                NumCpus,
    IN VOID                 *MpData,
    IN BOARD_CPU_FEATURES   *AllFeatures,
    OUT BOARD_CPU_FEATURES  *Feature
);


#pragma pack (1)
typedef struct {
	UINT16	Limit;
	UINTN   Base;       //This shared between 32 bit and 64 bit.
} DESCRIPTOR_TABLE;

typedef struct _MP_CPU_APICID_DATA {
  UINT8  NumberOfCpu;
  UINT8  ApicId[32];
} MP_CPU_APICID_DATA;
#pragma pack()

#define MP_AP_ONLY 0
#define MP_BSP_AP 1

#define MP_PARALLEL  0
#define MP_SERIALIZE 1

#define MP_FREERUN 0
#define MP_WAIT    1
UINT32 StartCpus(
#ifdef PEI_COMPILE
	IN EFI_PEI_SERVICES		**PeiServices,
	IN EFI_PEI_STALL_PPI	*PeiStall,
#endif
	IN VOID		            *ApGlobalData OPTIONAL,
	IN BOOLEAN				AllCpus,
	IN UINT32				ApicId,		//If only 1 cpu
    IN VOID                 *Address
);

VOID StartAllAps(
#ifdef PEI_COMPILE
	IN EFI_PEI_SERVICES	**PeiServices,
	IN EFI_PEI_STALL_PPI *PeiStall,
#endif
	OUT VOID **MpData
);
VOID PrepareApsForNormalExec(
#ifdef PEI_COMPILE
    IN EFI_PEI_SERVICES     **PeiServices,
#endif
    IN VOID    *MpData
);
VOID EarlyExecuteFunctionOnRunningCpus(
    IN VOID     *MpData,
    IN VOID 	(*Function)(UINT32, VOID *Context), //First parameters will always be 0.
    IN VOID     *Context
);
VOID RestartAp(
#ifdef PEI_COMPILE
	IN EFI_PEI_SERVICES		**PeiServices,
	IN EFI_PEI_STALL_PPI	*PeiStall,
#endif
	IN VOID		*MpData,
	IN UINT32	Cpu
);

VOID SetHaltFunction(
	IN VOID *MpData,
    IN VOID *Function
);

UINT32 GetNumCpus(VOID *MpData);
VOID ExecuteFunctionOnRunningCpus(
	IN VOID 	*MpData,
	IN BOOLEAN	ExecuteOnBsp,
	IN BOOLEAN	Serialize,
	IN BOOLEAN	Block,
	IN VOID 	(*Function)(UINT32 Cpu, VOID *Context),
	IN VOID 	*Context
);
BOOLEAN ExecuteFunctionOnCpu(
	IN VOID 	*MpData,
	IN UINT32 	Cpu,
	IN BOOLEAN	Block,
	IN VOID 	(*Function)(UINT32 Cpu, VOID *Context),
	IN VOID 	*Context
);
VOID HaltAllAps(
	IN VOID *MpData,
	IN BOOLEAN WaitUntilHalted
);
VOID HaltCpu(
	IN VOID *MpData,
	IN UINT32 Cpu,
	IN BOOLEAN WaitUntilHalted
);
BOOLEAN IsCpuHalted(
	IN VOID   *MpData,
	IN UINT32 Cpu
);

BOOLEAN IsCpuIdle(
	IN VOID   *MpData,
	IN UINT32 Cpu
);

BOOLEAN AreCpusIdle(
	IN VOID *MpData
);

UINT32 WhoIsBsp(VOID *MpData);

UINT32 GetCpuBist(IN VOID *MpData, IN UINT32 Cpu);
UINT32 GetCpuNumByApicId(VOID *MpData, UINT32 ApicId);

VOID SwitchBsp(
#ifdef PEI_COMPILE
	IN EFI_PEI_SERVICES	**PeiServices,
	IN EFI_PEI_STALL_PPI *PeiStall,
#endif
    IN VOID *MpData,
    IN UINT32 NewBsp
);

VOID ProgramLocalApic(IN UINT32 Cpu, IN VOID *Context);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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
