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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuDxe.c 21    6/11/15 10:33p Crystallee $
//
// $Revision: 21 $
//
// $Date: 6/11/15 10:33p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuDxe.c $
// 
// 21    6/11/15 10:33p Crystallee
// [TAG]  		EIP207854
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Txt test fail with TCG2 module
// [RootCause]  	Tokne TCG_SUPPORT was removed.
// [Solution]  	Add TCG2Support token.
// 
// 20    5/24/15 11:36p Davidhsieh
// [TAG]  		EIP215675
// [Category]  	New Feature
// [Description]  	Smm Access Check feautre support
// [Files]  	Cpu.sdl, CpuDxe.c, CpuSpSmi.sdl, CpuSpsmi.c
// 
// 19    8/28/13 6:00a Crystallee
// [TAG]  		EIP134339
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	[Sharkbay]Build error after update Haswell Cpu module
// [RootCause]  	If token TCG_SUPPORT is disabled, TpmSupport setup data
// will not define, then cause built error.
// [Solution]  	Add token TCG_SUPPORT condition when use TpmSupport setup
// data.
// 
// 18    7/23/13 7:45a Crystallee
// [TAG]  		EIP128089
// [Category]  	Improvement
// [Description]  	TXT will be disabled and grayed out in Setup when TPM
// Support is disabled.
// 
// 17    3/20/13 2:49a Crystallee
// [TAG]  		EIP118478
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	AES-NI setup item disappear after set ASN-NI to disable.
// [RootCause]  	We determine AES support from the ASE support bit in
// CPUID function 1, but it will change with AES MSR.
// [Solution]  	Determine AES support before CPU RC DXE initialize.
// 
// 16    2/27/13 5:00a Crystallee
// [TAG]  		EIP115822
// [Category]  	Improvement
// [Description]  	Add SMBIOS type7 information for L4 cache if CPU
// supported
// And create a token to control this.
// 
// 15    2/22/13 2:07a Crystallee
// [TAG]  		EIP112238
// [Category]  	Improvement
// [Description]  	Refer Intel BIOS and provide setup items for Intel
// Haswell RC policy.
// 
// 14    12/18/12 7:09a Davidhsieh
// [TAG]  		EIP93180
// [Category]  	Improvement
// [Description]            Do not create timer callback to clear
// direction flag, clear direction flag operation is in interrupt entry.
// 
// 13    11/23/12 4:19a Davidhsieh
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Ctdp setup item is not displayed in setup menu
// [RootCause]  	The cTDPAvailable value is not initialzied
// [Solution]  	Initial cTDPAvailable value
// 
// 12    11/08/12 6:18a Davidhsieh
// [TAG]  		EIP105401
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	CpuSignature and FeatureFlags of MPS table are incorrect
// [RootCause]             Cpu Signature and FeatureFlags in CpuInfo are
// not initialized
// [Solution]                 Initialize Cpu Signature and FeatureFlags in
// CpuInfo 
// 
// 11    11/07/12 4:36a Davidhsieh
// [TAG]                None
// [Category]         Improvement
// [Description]      L4 Cache support improve
// 
// 10    10/17/12 2:20a Davidhsieh
// [TAG]                None
// [Category]         Improvement
// [Description]      Setup items CTDP BIOS, C8, C9 and C10 created
// 
// 9     10/17/12 1:58a Davidhsieh
// [TAG]                     None
// [Category]  	Improvement
// [Description]  	L4 cache support
// 
// 8     9/26/12 10:53a Davidhsieh
// [TAG]              None
// [Description]    Add CPU APIC ID data variable for S3 resume
// 
// 7     7/10/12 2:48a Davidhsieh
// [TAG]  		EIP93180
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	The "Event Kernel-Power 137" error event log shows while
// resumed from HS3/S3 in Windows8 (not-UEFI boot mode)
// [RootCause]  	The save MTRRs action is too early, the saved value is
// differnet from the value in OS
// [Solution]  	Move the MTRR save action to AMI_LEGACYBOOT event
// 
// 6     5/20/12 11:38p Davidhsieh
// [TAG]  		EIP89382
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hangs when booting to UEFI Red Hat Linux OS with
// Network cable plugged in
// [RootCause]  	Red Hat Linux OS sets ¡§Direction Flag¡¨ and clears it
// immediately after few instructions. But before it has been cleared,
// Timer interrupt has been generated and MemSet () has function has been
// called inside UEFINetworkStack Timer callback handler. As the
// "Direction flag" is set ¡§MemSet¡¨ function stores data in reverse
// direction which results in data corruption.
// [Solution]  	Timer Callback function has been created with Higher
// priority level (TPL_NOTIFY + 14) and "direction flag" has been cleared
// inside the callback function.
// 
// 5     5/17/12 9:34p Davidhsieh
// [TAG]  		EIP89591
// [Category]  	Improvement
// [Description]  	Make the CPU wakup buffer locatioin depends on token
// PMM_EBDA_LOMEM_SIZE
// 
// 4     3/20/12 3:22a Davidhsieh
// Create SMBIOS type4 and type7 in AMI CPU module part
// 
// 3     3/16/12 3:11a Davidhsieh
// Setup items create for CPU RC policy
// 
// 2     2/23/12 2:06a Davidhsieh
// [TAG]  		EIP72056
// [Category]  	Improvement
// [Description]  	Change EFI_MP_PROC_CONTEXT to follow Intel CPU driver
// 
// 1     2/07/12 3:58a Davidhsieh
//
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        CpuDxe.c
//
// Description:
//  Installs CPU Architectural Protocol.
//  processor interrupt vector table. The CPU Architectural
//  Protocol enables/disables/get state of interrupts, set
//  memory range cache type, and installs/uninstalls
//  interrupt handlers.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <token.h>
#include <AmiCspLib.h>
#include <Protocol\AmiCpuInfo.h>
#include <Protocol\DxeSmmReadyToLock.h>
#include "CpuDxe.h"
#include "PlatformCpuLib.h"

#ifdef CSM_SUPPORT
#include <Protocol\LegacyBiosExt.h>
EFI_GUID  gAmiLegacyBootProtocolGuid      = EFI_AMI_LEGACYBOOT_PROTOCOL_GUID;
#endif

#if AMI_PEI_DEBUG_SUPPORT
#include "PeiDbgDxeCpuLib.h"

#define AMI_DEBUGGER_CPU_PROTOCOL_GUID \
  { 0xab21acc3, 0xba33, 0xee2c, 0x66, 0xbc, 0x12, 0x56, 0x77, 0x11, 0x1a, 0xb2 }
  
typedef struct _AMI_DEBUGGER_CPU_PROTOCOL AMI_DEBUGGER_CPU_PROTOCOL;  

typedef
EFI_STATUS
(EFIAPI *DEBUGGER_GET_APTIO_INT_HANDLER) (
    IN OUT UINT32*   InterruptHandlerHaltAddr  
  );

typedef
EFI_STATUS
(EFIAPI *DEBUGGER_FIXUP_PEI_EXCEPTION_HANDLER) (
  IN IDTEntry_T*           IdtEntry,
  IN UINT32    i  
  );
  
typedef
EFI_STATUS
(EFIAPI *DEBUGGER_SETUP_EXCEPTION_HANDLER) (VOID);

typedef
EFI_STATUS
(EFIAPI *DEBUGGER_IS_DEBUGGER_IRQ_HANDLER) (
  IN EFI_EXCEPTION_TYPE           InterruptType,
  IN EFI_CPU_INTERRUPT_HANDLER    InterruptHandler
  );

typedef struct _AMI_DEBUGGER_CPU_PROTOCOL {
    DEBUGGER_GET_APTIO_INT_HANDLER       DebuggerGetAptioIntHandler;
	DEBUGGER_FIXUP_PEI_EXCEPTION_HANDLER DebuggerFixUpPEIExceptionHandlers;
	DEBUGGER_SETUP_EXCEPTION_HANDLER     DebuggerSetupExceptionHandler;
	DEBUGGER_IS_DEBUGGER_IRQ_HANDLER     DebuggerIsDebuggerIrqHadler;	
};


#endif

#define DELAY_CALCULATE_CPU_PERIOD  200     //uS

#if CPU_MODULE_CREATE_SMBIOS_TABLES == 1
VOID CpuSmbios();
#endif

#define AMI_BEFORE_CPU_RC_PROTOCOL_GUID \
  { 0x1d26adc3, 0xb011, 0xee2c, 0x21, 0x77, 0x89, 0xbb, 0xaa, 0xcc, 0x33, 0x92 }

// Add EFI_MP_PROC_CONTEXT_FROM_RC relavant structures
typedef struct {
  UINT32              ApicID;
  BOOLEAN             Enabled;
  EFI_CPU_DESIGNATION Designation;
  EFI_MP_HEALTH       Health;
  UINTN               PackageNumber;
  UINTN               NumberOfCores;
  UINTN               NumberOfThreads;
  UINT64              ProcessorPALCompatibilityFlags;
  UINT64              ProcessorTestMask;
} EFI_MP_PROC_CONTEXT_FROM_RC;

UINT32 *FindPtrToPrivCpuInfoPkg(
    IN UINT32 Package
);

EFI_GUID gHobListGuid               = HOB_LIST_GUID;
EFI_GUID gEfiMpServicesProtocolGuid = EFI_MP_SERVICES_PROTOCOL_GUID;
EFI_GUID gAmiCpuinfoHobGuid         = AMI_CPUINFO_HOB_GUID;
EFI_GUID gAmiCpuInfoProtocolGuid    = AMI_CPU_INFO_PROTOCOL_GUID;
EFI_GUID gAmiCpuInfo2ProtocolGuid   = AMI_CPU_INFO_2_PROTOCOL_GUID;
EFI_GUID gAmiBeforeCpuRcProtocolGuid  = AMI_BEFORE_CPU_RC_PROTOCOL_GUID;
EFI_GUID gMpCpuApicIdDataGuid = MP_CPU_APIC_ID_DATA_GUID;
#if AMI_PEI_DEBUG_SUPPORT
EFI_GUID gAmiDebuggerCpuProtocolGuid  = AMI_DEBUGGER_CPU_PROTOCOL_GUID;
#endif
EFI_MP_SERVICES_PROTOCOL *gEfiMpServicesProtocol;
EFI_MP_PROC_CONTEXT_FROM_RC *gEfiMpProcContext;

UINTN                     gNumOfCpus;  
UINTN	                  gMaximumNumberOfCPUs;
UINTN	                  gNumberOfEnabledCPUs;
UINTN 	                  gRendezvousIntNumber;
UINTN	                  gRendezvousProcLength;

UINT32                    gNumOfCpuCores;
UINT32                    gNumOfThreads;

UINT32      gRegEax, gRegEbx, gRegEcx, gRegEdx;

EFI_EVENT 	gAmiMpEvent;
VOID		*gAmiMpEventRegistration = 0;

EFI_EVENT 	gSmmFeaEnEvent;
VOID		*gSmmFeaEnReg = 0;

static VOID   *gAcpiData;
static UINT32 gAcpiDataNumEntries;

static CHAR8 gProcObjPath = '\0';

CPUINFO_HOB             *gCpuInfoHob;
AMI_CPU_INFO            *gAmiCpuInfo;
VOID 			        *gSetupHandle;
CPU_FEATURES            gCpuFeatures;
EFI_PHYSICAL_ADDRESS    gTempBuffer;
BOOLEAN                 IsFreeMemBelow1MB;

VOID CreatePrivateAmiCpuInfo2();
UINT32 * GetPtrToPrivateAmiCpuInfo2Entry(
    IN UINT32 Package,
    IN UINT32 Core,
    IN UINT32 Thread
);

#if AMI_PEI_DEBUG_SUPPORT
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InterruptHandlerHalt
//
// Description: Default CPU Exception. Halts CPU.
//
// Input:
//      IN EFI_EXCEPTION_TYPE   Exception
//      IN EFI_SYSTEM_CONTEXT   Context
//
// Output:
//      VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InterruptHandlerHalt(EFI_EXCEPTION_TYPE Exception,EFI_SYSTEM_CONTEXT Context)
{
    ERROR_CODE(EFI_SOFTWARE_IA32_EXCEPTION | (UINT32)Exception, EFI_ERROR_MAJOR);
    checkpoint((UINT8)Exception);
    TRACE((TRACE_DXE_CPU,"ERROR: CPU Exception %X\n",Exception));
    EFI_DEADLOOP();
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: DebuggerGetAptioInterruptHandlerHalt
//
// Description: 
//
// Input:
//    
//     
//
// Output:
//      VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DebuggerGetAptioInterruptHandlerHalt(
    IN OUT UINT32*   InterruptHandlerHaltAddr
)
{
    
    *InterruptHandlerHaltAddr = (UINT32)InterruptHandlerHalt;
    TRACE((TRACE_DXE_CPU,"InterruptHandlerHalt =  %X\n",InterruptHandlerHalt));
    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: DebuggerIsItPEIDebugIRQHandlerToHookup
//
// Description: 
//
// Input:
//    
//     
//
// Output:
//      VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DebuggerFixUpPEIDebuggerExceptionHandlers(
    IN IDTEntry_T*           IdtEntry,
    IN UINT32    i
)
{
    
    FixUpPEIDebuggerExceptionHandlers((IDTEntry_T*)IdtEntry,i);
    return EFI_SUCCESS;

}    

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: DebuggerSetupPEIDebuggerExceptionHandlers
//
// Description: 
//
// Input:
//      
//
// Output:
//    
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DebuggerSetupPEIDebuggerExceptionHandlers(VOID)
{

    SetupPEIDebuggerExceptionHandlers( );
    return EFI_SUCCESS;

}    
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: DebuggerIsItPEIDebugIRQHandlerToHookup
//
// Description: 
//
// Input:
//    
//     
//
// Output:
//      VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DebuggerIsItPEIDebugIRQHandlerToHookup(
    IN EFI_EXCEPTION_TYPE           InterruptType,
    IN EFI_CPU_INTERRUPT_HANDLER    InterruptHandler)
{

    IsItPEIDebugIRQHandlerToHookup(InterruptType,InterruptHandler);
    return EFI_SUCCESS;

}    
#endif
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   CalculateTimerPeriod
//
// Description: Calculate CPU time period.
//
// Input: VOID
//
// Output:
//      UINT64 Timer Period
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT64 CalculateTimerPeriod()
{
    UINT64  Timer1;
    UINT64  Timer2;

    EFI_TPL OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);

    Timer1 = ReadRtdsc();

    pBS->Stall(DELAY_CALCULATE_CPU_PERIOD);

    Timer2 = ReadRtdsc();

    pBS->RestoreTPL(OldTpl);

    return Div64(DELAY_CALCULATE_CPU_PERIOD * (UINT64)1000000000, (UINT32)(Timer2-Timer1),NULL);    //50us * 10E15  femtosec;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: GetCpuInfo
//
// Description: Protocol function to get Cpu Info.
//
// Input:
//      IN AMI_CPU_INFO_PROTOCOL    *This
//      IN UINTN                    Cpu
//      OUT AMI_CPU_INFO            **Info
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetCpuInfo(
    IN AMI_CPU_INFO_PROTOCOL    *This,
    IN UINTN                    Cpu,
    OUT AMI_CPU_INFO            **Info
)
{
    if (Cpu >= gNumOfCpus) return EFI_INVALID_PARAMETER;
    *Info = &gAmiCpuInfo[Cpu];
    return EFI_SUCCESS;
}

AMI_CPU_INFO_PROTOCOL gAmiCpuInfoProtocol = {GetCpuInfo};

static CACHE_DESCRIPTOR_INFO gZeroCacheDesc = {0, 0, 0, 0, 0};

typedef struct {
    UINT32 NumCores;    //Number of cores in Package.
    UINT32 NumEntries;  //Each cache descriptor should have same number of entries, max of 4.
    AMI_CPU_INFO_2_CACHE_DESCR PkgCacheDesc[4];   //Total of the cores
    AMI_CPU_INFO_2_CACHE_DESCR CoreCacheDesc[4];  //Internal implementation assumes symmetry among cores.
                                                  //If this every changes, internal implementation will be updated.
} PKG_CACHE_DESCR;

static PKG_CACHE_DESCR *gPkgCacheDesc; //Array of Package Cache Descriptions.


typedef struct {
    UINT32 CacheType:5;
    UINT32 CacheLevel:3;
    UINT32 NotUsed:24;
} CPUID4_EAX_CACHE_INFO;

typedef struct {
    UINT32  LineSize:12;
    UINT32  Partitions:10;
    UINT32  Ways:10;
} CPUID4_EBX_CACHE_INFO;

#define MAX_NUM_CACHE_DESC  8

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FindPtrToPrivCpuInfoPkg
//
// Description: Pointer to internal Package information.
//
// Input:
//  IN UINT32  PkgPtr -- Internal package information.
//
// Output:  UINT32 * -- Internal Core information.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 *FindPtrToPrivCpuInfoPkg(
    IN UINT32 Package
)
{
    UINT32 *p = (UINT32*)(gPrivateAmiCpuInfo2 + 1);
    UINT32 i;

    if (Package >= *p) return (UINT32*)-1;   //Package does not exist.
    p++; //now p = Num cores of package 0.

    //Skip entries for previous packages.
    for (i = 0; i < Package; ++i) {
        UINT32 NumCores = *p++;    //p = now number of threads
        UINT32 j;
        for (j = 0; j < NumCores; ++j) {
            UINT32 NumThreads = *p++;
            p += NumThreads * PRIVATE_INFO_NUM_OF_CPU_DATA;
        }
    }
    return p;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FindPtrToPrivCpuInfoCore
//
// Description: Pointer to internal Core information.
//
// Input:
//  IN UINT32* PkgPtr -- Internal package information.
//  IN UINT32  Core
//
// Output:  UINT32 * -- Internal Core information.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 *FindPtrToPrivCpuInfoCore(
    IN UINT32 *PkgPtr,
    IN UINT32 Core
)
{
    UINT32 *p = PkgPtr;
    UINT32 NumCores = *p++;
    UINT32 i;
    if (Core >= NumCores) return (UINT32*)-1;   //Core does not exist.

    //Skip previous cores.
    for (i = 0; i < Core; ++i) {
        UINT32 NumThreads = *p++;
        p += NumThreads * PRIVATE_INFO_NUM_OF_CPU_DATA;
    }
    return p;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FindPtrToPrivCpuInfoThread
//
// Description: Pointer to internal Core information.
//
// Input:
//  IN UINT32* CorePtr -- Internal core information.
//  IN UINT32  Thread
//
// Output:  UINT32 * -- Internal thread information.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 *FindPtrToPrivCpuInfoThread(
    IN UINT32 *CorePtr,
    IN UINT32 Thread
)
{
    UINT32 *p = CorePtr;
    UINT32 NumThreads = *p++;
    if (Thread >= NumThreads) return (UINT32*)-1;   //Thread does not exist.
    p += Thread * PRIVATE_INFO_NUM_OF_CPU_DATA;
    return p;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetBoardSocketNumber
//
// Description: Get socket number from Apic ID.
//
// Input:
//  IN UINT32 ApicId
//
// Output:  UINT32 - Physical Socket Id
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 GetBoardSocketNumber(IN UINT32 ApicId)
{
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;
    UINT8  MaxThreadsPackage;

    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);

    MaxThreadsPackage = (UINT8)(RegEbx >> 16);
    
    return ApicId / MaxThreadsPackage;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetNumPackages
//
// Description: Get the number of packages populated and sockets.
//
// Input:
//	IN AMI_CPU_INFO_2_PROTOCOL  *This
//  OUT UINT32                  *NumPopulatedPackages
//  OUT UINT32                  *NumBoardSockets OPTIONAL
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetNumPackages(
	IN AMI_CPU_INFO_2_PROTOCOL  *This,
    OUT UINT32                  *NumPopulatedPackages,
    OUT UINT32                  *NumBoardSockets OPTIONAL
)
{
    //First entry after protocol functions is number of discovered packages.
    /*UINT32 *p = (UINT32*)(gPrivateAmiCpuInfo2 + 1);

    *NumPopulatedPackages = *p;
    //NUMBER_CPU_SOCKETS must be ported if more than 1 socket.
    ASSERT(*NumPopulatedPackages <= NUMBER_CPU_SOCKETS);
    if (NumBoardSockets) {
        *NumBoardSockets = NUMBER_CPU_SOCKETS;

        //In case of porting error, Board sockets can never be less than Populated packages.
        if (*NumPopulatedPackages > *NumBoardSockets) *NumBoardSockets = *NumPopulatedPackages;
    }*/
    
    if(NumPopulatedPackages == NULL)
        return EFI_INVALID_PARAMETER;
        
    *NumPopulatedPackages = 1;

   if (NumBoardSockets)
        *NumBoardSockets = 1;
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetNumCoresThreads
//
// Description: Get the number of Cores
//
// Input:
//  IN AMI_CPU_INFO_2_PROTOCOL  *This,
//  IN UINT32                   Package
//  OUT UINT32                  *NumEnabledCores
//  OUT UINT32                  *NumEnabledThreads - This value is total for package.
//  OUT UINT32                  *NumDisabledCores OPTIONAL -- Flag must be set in Protocol.
//  OUT UINT32                  *NumEnabledThreads OPTIONAL  -- Flag must be set in Protocol.
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetNumCoresThreads(
	IN AMI_CPU_INFO_2_PROTOCOL  *This,
    IN UINT32                   Package,
    OUT UINT32                  *NumEnabledCores,
    OUT UINT32                  *NumEnabledThreads,
    OUT UINT32                  *NumDisabledCores OPTIONAL,
    OUT UINT32                  *NumDisabledThreads OPTIONAL
)
{
    UINT32 *p = FindPtrToPrivCpuInfoPkg(Package);
    UINT32 TotNumCores;
    UINT32 TotNumThreads = 0;
    UINT32 i;

    if (NumEnabledCores == NULL || NumEnabledThreads == NULL)
        return EFI_INVALID_PARAMETER;
        
    if (p == (UINT32*) -1) return EFI_INVALID_PARAMETER;

    //After package is number of cores.
    TotNumCores = *p++;
    for (i = 0; i < TotNumCores; ++i) {
        UINT32 NumThreads = *p++; //After core is Number of Threads
        TotNumThreads += NumThreads;
        p += NumThreads * PRIVATE_INFO_NUM_OF_CPU_DATA;    //APIC ID and CPU NUM;
    }

    *NumEnabledCores = TotNumCores;
    *NumEnabledThreads = TotNumThreads;

    if (NumDisabledCores) *NumDisabledCores = 0;        //Flag not set in Protocol.
    if (NumDisabledThreads) *NumDisabledThreads = 0;    //Flag not set in Protocol.*/

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetNumThreads
//
// Description: Get the number of Threads
//
// Input:
//  IN AMI_CPU_INFO_2_PROTOCOL  *This
//  IN UINT32                   Package
//  IN UINT32                   Core
//  OUT UINT32                  *NumEnabledThreads
//  OUT UINT32                  *NumDisabledThreads OPTIONAL  -- Flag must be set if valid
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetNumThreads(
	IN AMI_CPU_INFO_2_PROTOCOL  *This,
    IN UINT32                   Package,
    IN UINT32                   Core,
    OUT UINT32                  *NumEnabledThreads,
    OUT UINT32                  *NumDisabledThreads OPTIONAL
)
{
    UINT32 *p = FindPtrToPrivCpuInfoPkg(Package);
    
    if (NumEnabledThreads == NULL) return EFI_INVALID_PARAMETER;
    
    if (p == (UINT32*) -1) return EFI_INVALID_PARAMETER;

    p = FindPtrToPrivCpuInfoCore(p, Core);
    if (p == (UINT32*) -1) return EFI_INVALID_PARAMETER;

    *NumEnabledThreads = *p;
    if (NumDisabledThreads) *NumDisabledThreads = 0;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetSbsp
//
// Description: Get SBSP
//
// Input:
//  IN AMI_CPU_INFO_2_PROTOCOL  *This
//  OUT UINT32                  *Package
//  OUT UINT32                  *Core
//  OUT UINT32                  *Thread
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetSbsp(
	IN AMI_CPU_INFO_2_PROTOCOL  *This,
    OUT UINT32                  *Package,
    OUT UINT32                  *Core,
    OUT UINT32                  *Thread
)
{
    //Desktop system, it must be package0, core0, thread0
    if (Package == NULL || Core == NULL || Thread == NULL)
        return EFI_INVALID_PARAMETER;
        
    *Package = 0;
    *Core = 0;
    *Thread = 0;
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetApicInfo
//
// Description: Get Apic Number and Version
//
// Input:
//  IN AMI_CPU_INFO_2_PROTOCOL  *This
//  IN UINT32                   Package
//  IN UINT32                   Core
//  IN UINT32                   Thread
//  OUT UINT32                  *ApicId
//  OUT UINT32                  *ApicVer OPTIONAL
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetApicInfo(
	IN AMI_CPU_INFO_2_PROTOCOL  *This,
    IN UINT32                   Package,
    IN UINT32                   Core,
    IN UINT32                   Thread,
    OUT UINT32                  *ApicId,
    OUT UINT32                  *ApicVer OPTIONAL
)
{
    UINT32 *p = GetPtrToPrivateAmiCpuInfo2Entry(
        Package, Core, Thread);
    UINT32 CpuNum;
    
    if (ApicId == NULL) return EFI_INVALID_PARAMETER;
    
    if (p == (UINT32*) -1) return EFI_INVALID_PARAMETER;

    //p points to 32-bit APIC ID and 32-bit CPU Num for internal structures.

    *ApicId = *p++;

    if (ApicVer) {
        CpuNum = *p;
        *ApicVer = (UINT8)MemRead32((UINT32*)(UINTN)(LOCAL_APIC_BASE + APIC_VERSION_REGISTER));
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetAcpiInfo
//
// Description: Get Cpu ACPI information.
//
// Input:
//  IN AMI_CPU_INFO_2_PROTOCOL  *This
//  OUT VOID                    **AcpiData  - ACPI Data
//  OUT UINT32                  *NumEntries - Number of Entries in data.
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetAcpiInfo(
	IN AMI_CPU_INFO_2_PROTOCOL  *This,
    OUT VOID                    **AcpiData,
    OUT UINT32                  *NumEntries
)
{   
    if (AcpiData == NULL || NumEntries == NULL)
        return EFI_INVALID_PARAMETER;
        
    *AcpiData = gAcpiData;
    *NumEntries = gAcpiDataNumEntries;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetPackageCacheDescr
//
// Description: Get the package Cache Information
//
// Input:
//  IN AMI_CPU_INFO_2_PROTOCOL      *This
//  IN UINT32                       Package - Socket number. Intenal socket number (continous)
//  OUT AMI_CPU_INFO_2_CACHE_DESCR  **Description - Updates pointer to pointer with pointer to Cache information. 
//  OUT UINT32                      *NumEntries - Number of AMI_CPU_INFO_2_CACHE_DESCR Entries.
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetPackageCacheDescr(
    IN AMI_CPU_INFO_2_PROTOCOL      *This,
    IN UINT32                       Package,
    OUT AMI_CPU_INFO_2_CACHE_DESCR  **Description,
    OUT UINT32                      *NumEntries
)
{
    PKG_CACHE_DESCR *PkgCacheDesc;

    if (Package >= NumberOfCpuSocketsPopulated()) return EFI_INVALID_PARAMETER;
    
    if (Description == NULL || NumEntries == NULL)
        return EFI_INVALID_PARAMETER;

    PkgCacheDesc = &gPkgCacheDesc[Package];
    *Description = &PkgCacheDesc->PkgCacheDesc[0];
    *NumEntries = PkgCacheDesc->NumEntries;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetCoreCacheDescr
//
// Description: Get the Core Cache Information
//
// Input:
//  IN AMI_CPU_INFO_2_PROTOCOL      *This
//  IN UINT32                       Package - Socket number. Internal socket number (continous)
//  IN UINT32                       Core - Core number. Internal core number (continous)
//  OUT AMI_CPU_INFO_2_CACHE_DESCR  **Description - Updates pointer to pointer with pointer to Cache information. 
//  OUT UINT32                      *NumEntries - Number of AMI_CPU_INFO_2_CACHE_DESCR Entries.
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetCoreCacheDescr(
    IN AMI_CPU_INFO_2_PROTOCOL      *This,
    IN UINT32                       Package,
    IN UINT32                       Core,
    OUT AMI_CPU_INFO_2_CACHE_DESCR  **Description,
    OUT UINT32                      *NumEntries
)
{
    PKG_CACHE_DESCR *PkgCacheDesc;    

    if (Package >= NumberOfCpuSocketsPopulated()) return EFI_INVALID_PARAMETER;
    
    if (Description == NULL || NumEntries == NULL)
        return EFI_INVALID_PARAMETER;
    
    PkgCacheDesc = &gPkgCacheDesc[Package];
    
    if (Core >= PkgCacheDesc->NumCores) return EFI_INVALID_PARAMETER;

    *Description = &PkgCacheDesc->CoreCacheDesc[0];
    *NumEntries = PkgCacheDesc->NumEntries;
    return EFI_SUCCESS;
}

PRIVATE_AMI_CPU_INFO_2_PROTOCOL PrivateAmiCpuInfo2Init = {
    {
        1,          //ProtocolVer
        0,          //Flags
        GetNumPackages,
        GetNumCoresThreads,
        GetNumThreads,
        GetSbsp,
        GetApicInfo,
        GetAcpiInfo,
        GetPackageCacheDescr,
        GetCoreCacheDescr
    }
    //Additional information will allocated.
};

PRIVATE_AMI_CPU_INFO_2_PROTOCOL *gPrivateAmiCpuInfo2;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SizeOfPrivateAmiCpuInfo2
//
// Description: Size of Private Ami Cpu Info 2 structure to be allocated.
//
// Input: VOID
//
// Output:  UINT32 -- Size
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 SizeOfPrivateAmiCpuInfo2()
{
    //See PRIVATE_AMI_CPU_INFO_2_PROTOCOL defintion for comments on internal CPU information.

    UINT32 Size = sizeof(AMI_CPU_INFO_2_PROTOCOL);
    UINT32 NumSockets = 1;
    UINT32 CpuNum = 0;
    UINT32 j;
    
    Size += sizeof(UINT32);  //Number of populated sockets entry.    
    Size += sizeof(UINT32); //Number of cores for socket;
    for (j = 0; j < gNumOfCpuCores; ++j) {    
        Size += sizeof(UINT32); //Number of thread per core.
        Size += gNumOfThreads * sizeof(UINT32) * PRIVATE_INFO_NUM_OF_CPU_DATA;    //APIC ID and CPU NUM;
        CpuNum += gNumOfThreads;
        ASSERT(CpuNum <= gNumOfCpus);
    }    
    return Size;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FillPrivateAmiCpuInfo2
//
// Description: Fill CPU information in Private Ami Cpu Info structure.
//
// Input: VOID
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID FillPrivateAmiCpuInfo2()
{
    //See PRIVATE_AMI_CPU_INFO_2_PROTOCOL defintion for comments on internal CPU information.

    UINT32 *p = (UINT32*)(gPrivateAmiCpuInfo2 + 1);
    UINT32 NumSockets = 1;
    UINT32 CpuNum = 0;
    UINT32 i;
    UINT32 j;
    UINT32 k;

    *gPrivateAmiCpuInfo2 = PrivateAmiCpuInfo2Init;
    *p++ = NumSockets;
    for (i = 0; i < NumSockets; ++i) {
        *p++ = gNumOfCpuCores;        
        for (j = 0; j < gNumOfCpuCores; ++j) {            
            *p++ = gNumOfThreads;
            for (k = 0; k < gNumOfThreads; ++k) {                
                *p++ = gEfiMpProcContext[CpuNum].ApicID;
                *p++ = CpuNum;
                ++CpuNum;
                ASSERT(CpuNum <= gNumOfCpus);
            }
        }
    }
}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetPtrToPrivateAmiCpuInfo2Entry
//
// Description: Get pointer to APIC/Cpu Num
//
// Input:
//  IN UINT32 Package
//  IN UINT32 Core
//  IN UINT32 Thread
//
// Output:  UINT32 *
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 * GetPtrToPrivateAmiCpuInfo2Entry(
    IN UINT32 Package,
    IN UINT32 Core,
    IN UINT32 Thread
)
{
    UINT32 *p;

    p = FindPtrToPrivCpuInfoPkg(Package);
    if (p == (UINT32*) -1) return (UINT32*)-1;   //Package does not exist.

    p = FindPtrToPrivCpuInfoCore(p, Core);
    if (p == (UINT32*) -1) return (UINT32*)-1;   //Core does not exist.

    p = FindPtrToPrivCpuInfoThread(p, Thread);
    return p;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetCpuPkgCoreThrdByNum
//
// Description: Get CPU Package/Core/Thread by CPU Number. Number sequencial to APIC ID.
//
// Input:
//  IN UINT32 CpuNum
//  OUT UINT32 *Package
//  OUT UINT32 *Core
//  OUT UINT32 *Thread
//
// Output:  BOOLEAN -- If found, return TRUE.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetCpuPkgCoreThrdByNum(
    IN UINT32 CpuNum,
    OUT UINT32 *Package,
    OUT UINT32 *Core,
    OUT UINT32 *Thread
)
{
    UINT32 *p = (UINT32*)(gPrivateAmiCpuInfo2 + 1);
    UINT32 NumPkgs = *p++;
    UINT32 Pkg;

    for (Pkg = 0; Pkg < NumPkgs; ++Pkg) {
        UINT32 NumCores = *p++;
        UINT32 Cor;
        for (Cor = 0; Cor < NumCores; ++Cor) {
            UINT32 NumThrds = *p++;
            UINT32 Thrd;
            for (Thrd = 0; Thrd < NumThrds; ++Thrd) {
                ++p;    //Skip ApicId;
                if (*p++ == CpuNum) {
                    *Package = Pkg;
                    *Core = Cor;
                    *Thread = Thrd;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FillAcpiData
//
// Description: Fill ACPI Data structure
//
// Input:
//  IN ACPI_PROCESSOR_INFO *AcpiProcData
//  IN UINT32 Package
//  IN UINT32 Core
//  IN UINT32 Thread
//  IN BOOLEAN Bsp
//
// Output:  BOOLEAN -- If filled, return TRUE.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN FillAcpiData(
    OUT ACPI_PROCESSOR_INFO *AcpiProcData,
    IN UINT32 Package,
    IN UINT32 Core,
    IN UINT32 Thread,
    IN BOOLEAN Bsp
)
{
    UINT32 ApicId;
    UINT32 CpuNum;
    UINT32 CpuSignature, CpuIdEBX, CpuIdECX, FeatureFlags;

    static UINT32 ProcId = 1;

    UINT32 *ptr = GetPtrToPrivateAmiCpuInfo2Entry(Package, Core, Thread);
    if (ptr == (UINT32*) -1) return FALSE;
    //ptr points to 32-bit APIC ID and 32-bit CPU Num for internal structures.

    ApicId = *ptr++;
    CpuNum = *ptr;
    CPULib_CpuID(1, &CpuSignature, &CpuIdEBX, &CpuIdECX, &FeatureFlags);

    AcpiProcData->Type = ACPI_PROCESSOR_INFO_TYPE;    //0
    AcpiProcData->Length = sizeof(ACPI_PROCESSOR_INFO);
    AcpiProcData->Enable = 1;
    AcpiProcData->Bsp = Bsp;
    AcpiProcData->Package = Package;
    AcpiProcData->Core = Core;
    AcpiProcData->Thread = Thread;
    AcpiProcData->ApicId = ApicId;      //LAPIC number for processor.
    //AcpiProcData->ApicVer = gCpuInfoHob->Cpuinfo[CpuNum].ApicVer;
    AcpiProcData->ApicVer = (UINT8)MemRead32((UINT32*)(UINTN)(LOCAL_APIC_BASE + APIC_VERSION_REGISTER));
    AcpiProcData->CpuSignature = CpuSignature;
    AcpiProcData->FeatureFlags = FeatureFlags & (BIT0 | BIT7 | BIT8 | BIT9);
    AcpiProcData->ProcId = ProcId;     //ASL processor object ID.
    //AcpiProcData->ProcObjPath = (EFI_PHYSICAL_ADDRESS)(UINTN)&gProcObjPath;  //ASL processor object ID.
    AcpiProcData->LocalApicType = FALSE;            //All processors will either be xAPIC or x2APIC Mode not mixed.
    ++ProcId;
    return TRUE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: AddLocalApicCoreEntries
//
// Description: Create Private Ami Cpu Info2 Acpi Data.
//
// Input:
//  IN UINT32 Package - Processor package
//  IN UINT32 Thread - Processor thread (usually either 0 or 1 for HT)
//
// Output:  BOOLEAN - TRUE if any entries added.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN AddLocalApicCoreEntries(
    IN UINT32 Package,
    IN UINT32 Thread,
    IN BOOLEAN Bsp,
    IN UINT32 BspCore
){
    UINT32 NumEnabledCores;
    UINT32 NumEnabledThreads;
    UINT32 Core;
    BOOLEAN ValidEntry;
    AMI_CPU_INFO_2_PROTOCOL *AmiCpu2Info = (AMI_CPU_INFO_2_PROTOCOL*)gPrivateAmiCpuInfo2;
    ACPI_PROCESSOR_INFO *AcpiProcData = (ACPI_PROCESSOR_INFO *)gAcpiData;
    static UINT32 Entry = 0;

    AmiCpu2Info->GetNumCoresThreads(AmiCpu2Info, Package, &NumEnabledCores, &NumEnabledThreads, NULL, NULL);
    NumEnabledThreads = NumEnabledThreads / NumEnabledCores;

    if (Thread >= NumEnabledThreads) return FALSE;    //Different packages could have different numbers of threads;

    ValidEntry = FillAcpiData(
        &AcpiProcData[Entry],
        Package,
        BspCore,
        Thread,
        Bsp && Thread == 0
    );
    if (ValidEntry) ++Entry;

    for (Core = 0; Core < NumEnabledCores; ++Core) {
        if (Core == BspCore) continue;
        ValidEntry = FillAcpiData(
            &AcpiProcData[Entry],
            Package,
            Core,
            Thread,
            FALSE
        );
        if (ValidEntry) ++Entry;
    }

    return TRUE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CreateAcpiData
//
// Description: Create Private Ami Cpu Info2 Acpi Data.
//
// Input: VOID
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreateAcpiData()
{
	EFI_STATUS  Status;
	UINT32      Package;
	UINT32      Thread;
    UINT32      BspPackage;
    UINT32      BspCore;
    UINT32      BspThread;
	UINT32      MaxPackages;
    BOOLEAN     ProcessedEntries;
    AMI_CPU_INFO_2_PROTOCOL *AmiCpu2Info = (AMI_CPU_INFO_2_PROTOCOL*)gPrivateAmiCpuInfo2;

    gAcpiDataNumEntries = (UINT32)gNumOfCpus;
    
    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(ACPI_PROCESSOR_INFO) * gNumOfCpus, &gAcpiData);
    ASSERT_EFI_ERROR(Status);

    Status = AmiCpu2Info->GetSbsp(
	    AmiCpu2Info,
        &BspPackage,
        &BspCore,
        &BspThread
    );
    ASSERT_EFI_ERROR(Status);

    Status = AmiCpu2Info->GetNumPackages(AmiCpu2Info, &MaxPackages, NULL);
    ASSERT_EFI_ERROR(Status);
    Thread = 0;     //Thread count for a core.

    do {            //Thread
        ProcessedEntries = FALSE;

        //Bsp is always first entry.
        if (AddLocalApicCoreEntries(BspPackage, Thread, TRUE, BspCore))
            ProcessedEntries = TRUE;

        for (Package = 0; Package < MaxPackages; ++Package) {
            if (Package == BspPackage) continue;
            if (AddLocalApicCoreEntries(Package, Thread, FALSE, BspCore))
                ProcessedEntries = TRUE;
        }
        ++Thread;
    } while (ProcessedEntries);     //No more threads
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:  GetCacheSharedThreads
//
// Description: Return number of shared threads for a Information.
//
// Input:  IN UINT8 Level - Cache level
//
// Output: UINT8 - Number of shared threads.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 GetCacheSharedThreads(IN UINT8 Level)
{
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;
    UINT32 i = 0;

    for(;;) {
        RegEcx = i;
        CPULib_CpuID(4, &RegEax, &RegEbx, &RegEcx, &RegEdx);
        if ((RegEax & 0x1f) == 0) break;
        if (((RegEax >> 5) & 7) == Level) return 1 + ((RegEax >> 14)& 0xfff);
        ++i;
    }
    return 0;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CreateCacheData
//
// Description: Get Cache information.
//
// Input: VOID
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreateCacheData()
{
    AMI_CPU_INFO_2_PROTOCOL *AmiCpu2Info = (AMI_CPU_INFO_2_PROTOCOL*)gPrivateAmiCpuInfo2;
    UINT32  NumPackages;
    UINT32  Package;
    UINT32  CpuNum;
    EFI_STATUS Status;

    BOOLEAN IsLxSharedByPackage[5];

                                                                                                                                                //Assume between CPUs on the board, similar cache sharing. Only like CPUs can power the board.
    IsLxSharedByPackage[1] = GetCacheSharedThreads(1) > 2 ? TRUE: FALSE;
    IsLxSharedByPackage[2] = GetCacheSharedThreads(2) > 2 ? TRUE: FALSE;
    IsLxSharedByPackage[3] = GetCacheSharedThreads(3) > 2 ? TRUE: FALSE;
	IsLxSharedByPackage[4] = GetCacheSharedThreads(4) > 2 ? TRUE: FALSE;

    Status = AmiCpu2Info->GetNumPackages(AmiCpu2Info, &NumPackages, NULL);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(PKG_CACHE_DESCR) * NumPackages, &gPkgCacheDesc);
    ASSERT_EFI_ERROR(Status);

    MemSet(gPkgCacheDesc, sizeof(PKG_CACHE_DESCR) * NumPackages, 0);

    //Assume symmetry between the cores in a package. This never likely to change.
    for(Package = 0, CpuNum = 0; CpuNum < gNumOfCpus; ++Package) {
        AMI_CPU_INFO *AmiCpuInfo    = &gAmiCpuInfo[CpuNum];
        PKG_CACHE_DESCR *PkgDesc    = &gPkgCacheDesc[Package];
        CACHE_DESCRIPTOR_INFO *CacheInfo    = AmiCpuInfo->CacheInfo;
        UINT32 NumCores             = AmiCpuInfo->NumCores;
        UINT32 Entry = 0;

        ASSERT (Package < NumPackages);

        PkgDesc->NumCores = NumCores;

        while(CacheInfo->Desc != 0) {
            AMI_CPU_INFO_2_CACHE_DESCR *PkgCacheDesc = &PkgDesc->PkgCacheDesc[Entry];
            AMI_CPU_INFO_2_CACHE_DESCR *CoreCacheDesc = &PkgDesc->CoreCacheDesc[Entry];

            ASSERT(Entry < MAX_NUM_CACHE_DESC);
            ASSERT(CacheInfo->Level < 5);

            CoreCacheDesc->LengthDesc = sizeof(AMI_CPU_INFO_2_CACHE_DESCR);
            CoreCacheDesc->Level = CacheInfo->Level;
            CoreCacheDesc->Type = CacheInfo->Type;
            CoreCacheDesc->Size = CacheInfo->Size;
            CoreCacheDesc->Associativity = CacheInfo->Associativity;
            CoreCacheDesc->Shared = IsLxSharedByPackage[CacheInfo->Level] + 1;

            if (CoreCacheDesc->Type == 3) {
                CoreCacheDesc->Type = 2;   //Translate type from AMI CPU INFO 1 to AMI CPU INFO 2.
            }

            MemCpy(PkgCacheDesc, CoreCacheDesc, sizeof(AMI_CPU_INFO_2_CACHE_DESCR));

            PkgCacheDesc->Size *= !IsLxSharedByPackage[CacheInfo->Level] ? NumCores : 1;

            ++Entry;
            ++CacheInfo;
        }
        CpuNum += NumCores * (AmiCpuInfo->NumHts ? 2 : 1)                             ;
        PkgDesc->NumEntries = Entry;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CreatePrivateAmiCpuInfo2
//
// Description: Create Private Ami Cpu Info2 structure.
//
// Input: VOID
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreatePrivateAmiCpuInfo2()
{
    EFI_STATUS Status;

    
    Status = pBS->AllocatePool(
        EfiBootServicesData,
        SizeOfPrivateAmiCpuInfo2(),
        &gPrivateAmiCpuInfo2
    );
    ASSERT_EFI_ERROR(Status);
    
    FillPrivateAmiCpuInfo2();
    
    CreateAcpiData();
    
    CreateCacheData();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: FillCacheDesc
//
// Description: Update cache information with CPUID 4.
//
// Input:
//  CACHE_DESCRIPTOR_INFO * CacheInfo - Array to be filled of cache info structures.
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID FillCacheDesc(CACHE_DESCRIPTOR_INFO * CacheInfo)
{
    CPUID4_EAX_CACHE_INFO EaxInfo;
    CPUID4_EBX_CACHE_INFO EbxInfo;
    UINT32 RegEcx;
    UINT32 RegEdx;
    UINT32 CacheCount;

    for (CacheCount  = 0; CacheCount < (MAX_NUM_CACHE_DESC - 1); ++CacheCount) {
        RegEcx = CacheCount;
        CPULib_CpuID(4, (UINT32*)&EaxInfo, (UINT32*)&EbxInfo, &RegEcx, &RegEdx);
        if (EaxInfo.CacheType == 0) break; //No more cache.

        CacheInfo[CacheCount].Desc = 0xff;  //Unused.
        CacheInfo[CacheCount].Level = EaxInfo.CacheLevel;
        switch (EaxInfo.CacheType) {
        case 1: CacheInfo[CacheCount].Type = 0; break;
        case 2: CacheInfo[CacheCount].Type = 1; break;
        case 3: CacheInfo[CacheCount].Type = 3; break;
        }

        CacheInfo[CacheCount].Size =
            (EbxInfo.Ways + 1) * (EbxInfo.Partitions + 1) * (EbxInfo.LineSize + 1) * (RegEcx + 1) /
             1024;
        CacheInfo[CacheCount].Associativity = EbxInfo.Ways + 1;
    }
    CacheInfo[CacheCount] = gZeroCacheDesc;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CreatePrivateAmiCpuInfo1
//
// Description: Create Private Ami Cpu Info1 structure.
//
// Input: VOID
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreatePrivateAmiCpuInfo1()
{
    EFI_STATUS      Status;
    AMI_CPU_INFO    *AmiCpuInfo;
    UINT64          MicroCodeVersion;
    UINT32          CpuSignature;
    UINT32          i;
    UINT32          Bclk;
    UINT32          RegEAX, RegEBX, RegECX, RegEDX;
    UINT32          FeatureEcx, FeatureEdx;
    UINT32          ExtFeatureEdx;
    CHAR8           *BrandString;    
    CHAR8           *BrandString1;    
    UINT64          TimerPeriod;
    UINT8           *pos1;
    BOOLEAN         Ht0 = IsHt0();   //True, if not hyper-threaded CPU.
    //AMI_CPU_INFO    *AmiCpuInfo = &gAmiCpuInfo[Cpu];

    
      //Allocate memory for AMI_CPU_INFO. This will be filled by CPU initialization.
    Status = pBS->AllocatePool(
        EfiBootServicesData,
        sizeof(AMI_CPU_INFO) * gNumOfCpus,
        &gAmiCpuInfo
    );
    ASSERT_EFI_ERROR(Status);
    
    //Get Cpu Signature
    CpuSignature = GetCpuSignature();
    
    //Use 100 for bclk for Sandy Bridge and Ivy Bridge
    Bclk = 100;
    
    //Allocate memory for Brand string
    Status = pBS->AllocatePool(EfiBootServicesData, 49, &BrandString);
    ASSERT_EFI_ERROR(Status);
    BrandString1 = BrandString;
    //Get Brand string
    CPULib_CpuID(0x80000002, &RegEAX, &RegEBX, &RegECX, &RegEDX);
    *(UINT32*)BrandString = RegEAX; BrandString +=4;
    *(UINT32*)BrandString = RegEBX; BrandString +=4;
    *(UINT32*)BrandString = RegECX; BrandString +=4;
    *(UINT32*)BrandString = RegEDX; BrandString +=4;

    CPULib_CpuID(0x80000003, &RegEAX, &RegEBX, &RegECX, &RegEDX);
    *(UINT32*)BrandString = RegEAX; BrandString +=4;
    *(UINT32*)BrandString = RegEBX; BrandString +=4;
    *(UINT32*)BrandString = RegECX; BrandString +=4;
    *(UINT32*)BrandString = RegEDX; BrandString +=4;

    CPULib_CpuID(0x80000004, &RegEAX, &RegEBX, &RegECX, &RegEDX);
    *(UINT32*)BrandString = RegEAX; BrandString +=4;
    *(UINT32*)BrandString = RegEBX; BrandString +=4;
    *(UINT32*)BrandString = RegECX; BrandString +=4;
    *(UINT32*)BrandString = RegEDX; BrandString +=4;
    *BrandString = '\0';
    
    BrandString = BrandString1;    
        
    //Using CPUID to get related feature
    CPULib_CpuID(1, &RegEAX, &RegEBX, &FeatureEcx, &FeatureEdx);
    CPULib_CpuID(0x80000001, &RegEAX, &RegEBX, &RegECX, &ExtFeatureEdx);
    
    //Get loaded Microcode version, MSR 0x8b [EDX] = Microcode version   
    MicroCodeVersion = ReadMsr(0x8b);
    MicroCodeVersion = *((UINT32*)&MicroCodeVersion + 1); //ignore upper 32-bits.

    TimerPeriod = CalculateTimerPeriod();   //10^-15 s.
    
    for(i = 0; i < gNumOfCpus; i++ )
    {    
    
        AmiCpuInfo = &gAmiCpuInfo[i];
            
            
        Status = pBS->AllocatePool(EfiBootServicesData, MAX_NUM_CACHE_DESC * sizeof(CACHE_DESCRIPTOR_INFO), &AmiCpuInfo->CacheInfo);
        ASSERT_EFI_ERROR(Status);
            
        FillCacheDesc(AmiCpuInfo->CacheInfo);   //Get Cache Information.
        //Remove leading spaces. After removing leading spaces, the Brand String can not be
        //freed. However, it should never be freed.
        
        AmiCpuInfo->BrandString = BrandString;
        
        while (*AmiCpuInfo->BrandString == ' ') ++AmiCpuInfo->BrandString;
        
        //Remove extra spaces in middle.
        pos1 = AmiCpuInfo->BrandString;
        
        for(;;) {
            UINT8 *pos2;
            UINT8 *pos3;
            while (*pos1 != ' ' && *pos1 != '\0') ++pos1;   //Find next space.
            if (*pos1 == '\0') break;                       //If found terminator, break.
            if (*++pos1 != ' ') continue;                   //If not second space, continue scanning.
            pos2 = pos1;                                    //Found 2 spaces.
            while(*++pos2 == ' ');                          //Skip spaces.
            pos3 = pos1;
            while(*pos2 != '\0') *pos3++ = *pos2++;         //copy string
            *pos3++ = '\0';                                 //Add terminator.
        }       
        
        AmiCpuInfo->Version      = CpuSignature;
        AmiCpuInfo->X64Supported = (ExtFeatureEdx >> 29) & 1;
        AmiCpuInfo->Ht0          = Ht0;
        AmiCpuInfo->Features     = Shl64(FeatureEcx, 32) + FeatureEdx;
        AmiCpuInfo->NumCores     = gNumOfCpuCores;
        AmiCpuInfo->NumHts       = IsHtEnabled() * 2;   //Either 2 or 0.
        AmiCpuInfo->FSBFreq      = Bclk;
        AmiCpuInfo->Voltage         = 0;    //Voltage is variable, and no information os available.       
        AmiCpuInfo->MicroCodeVers   = (UINT32)MicroCodeVersion;
        AmiCpuInfo->IntendedFreq = ((UINT32)ReadMsr(0x198) >> 8) * Bclk;
        AmiCpuInfo->ActualFreq      = 1000000000/(UINT32)TimerPeriod;            
    }
   
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GlobalDataInitialize
//
// Description: Cpu Dxe Entrypoint.
//
// Input:
//  IN EFI_HANDLE       ImageHandle   -- Handle assigned to this driver.
//  IN EFI_SYSTEM_TABLE *SystemTable  -- Efi System table.
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GlobalDataInitialize(VOID)
{

    EFI_STATUS  Status;
    UINT64 MsrData = ReadMsr(MSR_CORE_THREAD_COUNT);    
    EFI_MP_PROC_CONTEXT_FROM_RC *ptr;
    UINT32 i;
    UINTN  BufferSize;
        
    gNumOfCpuCores = ((UINT32)(MsrData >> 16 & 0xff));
    //Locate MP services protocol provided by CPU RC
    Status = pBS->LocateProtocol(&gEfiMpServicesProtocolGuid, NULL, &gEfiMpServicesProtocol);    
    ASSERT_EFI_ERROR(Status);
    
    if (!EFI_ERROR(Status)){
        //Get number of Cpus on system
        gEfiMpServicesProtocol->GetGeneralMPInfo(
                                    gEfiMpServicesProtocol,
                                    &gNumOfCpus,
                                    &gMaximumNumberOfCPUs,   
                                    &gNumberOfEnabledCPUs,   
                                    &gRendezvousIntNumber,   
                                    &gRendezvousProcLength
                                   );    
    
    }else{
        return Status;
    }
    
    gNumOfThreads = (UINT32)(gNumOfCpus / gNumOfCpuCores);    
    //TRACE((-1, "Cpu MP service cpus = %x cores %x threads %x\n", gNumOfCpus, gNumOfCpuCores, gNumOfThreads));        
    
    //Get MP processor context of each CPU
    Status = pBS->AllocatePool(
        EfiBootServicesData,
        sizeof(EFI_MP_PROC_CONTEXT_FROM_RC) * gNumOfCpus,
        &gEfiMpProcContext
    );
    
    ptr = gEfiMpProcContext;
    BufferSize = sizeof(EFI_MP_PROC_CONTEXT_FROM_RC);
    for(i = 0; i < gNumOfCpus; i++ , ptr++)
    {
        gEfiMpServicesProtocol->GetProcessorContext(
                                    gEfiMpServicesProtocol,
                                    i,
                                    &BufferSize,
                                    ptr
                                ); 
    }
    
    return Status;
}    

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: PrepareToBoot
//
// Description: Handler executed before OS.
//
// Input:
//      IN EFI_EVENT    Event
//      IN VOID         *Context
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PrepareToBoot(IN EFI_EVENT Event, IN VOID *Context)
{
    //Trigger SWSMI to save CPU fixed & varible MTRRs
    IoWrite8(SW_SMI_IO_ADDRESS, SW_SMI_SAVE_MSR);
    
}
#if CPU_SETUP_SET_BOOT_RATIO
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CpuSetBootRatio
//
// Description: Adjust CPU boot ratio base on setup item
//
// Input:
//      None
//
// Output:
//      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CpuSetBootRatio(VOID)
{

    UINT8 MaxRatio = Shr64(ReadMsr(MSR_PLATFORM_INFO),8) & 0xff;
    UINT8 MinRatio = Shr64(ReadMsr(MSR_PLATFORM_INFO),40) & 0xff;
    UINT8 DesireRatio = (UINT8)GetPlatformCpuBootRatio(gSetupHandle);  
    
    if (DesireRatio == 0 || DesireRatio == 0xff)
        return;
        
    if (DesireRatio < MinRatio || DesireRatio > MaxRatio)
        DesireRatio = MaxRatio;
        
    ReadWriteMsr(MSR_IA32_MISC_ENABLE, BIT16, (UINT64)-1);    
    WriteMsr(0x199, DesireRatio << 8);
                    
    
}
#endif
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   AmiCpuMpServiceCallback
//
// Description: Cpu Dxe Entrypoint.
//
// Input:
//  IN EFI_EVENT       Event    -- 
//  IN VOID *          Context  -- 
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID AmiCpuMpServiceCallback(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS  Status;
    EFI_HANDLE  Handle=0;
    EFI_EVENT   BootEvent;
    VOID        *FirstHob;
    UINT32      CpuSignature = GetCpuSignature();
    UINT32      CpuSigNoVer = CpuSignature & 0xfffffff0;
    UINT32      RegEax, RegEbx, RegEcx, RegEdx;
    UINT8       CpuVer = CpuSignature & 0xf;
    BOOLEAN     X2ApicEnabled = CPULib_IsLocalX2ApicEnabled();
    UINT32      NumSocketsPop = NumberOfCpuSocketsPopulated();
    UINT32      i;
    BOOLEAN     IsSandyBridge =  (CpuSigNoVer == SANDY_BRIDGE || CpuSigNoVer == JAKETOWN);
    BOOLEAN     IsIvyBridge = (CpuSigNoVer == IVY_BRIDGE);
    VOID        *pRegistration = NULL;	
    MP_CPU_APICID_DATA  MpCpuApicIdData;
	UINT8       *TpmBaseAddr = (UINT8*)0xfed40000;
    
    
    //MSR 0xCE[28] Programmable Ratio Limits for Turbo Mode Supported    
    BOOLEAN     IsXeCoreRatioLimitSupport = ReadMsr(MSR_PLATFORM_INFO) & 0x10000000 ? 1:0;   
    //MSR 0xCE[29] Programmable Ratio Limits for Turbo Mode Supported    
    BOOLEAN     IsPwrLimitConfigSupport   = ReadMsr(MSR_PLATFORM_INFO) & 0x20000000 ? 1:0;   
    //MSR 0xCE[30] Programmable TCC Acivation Offset Supported    
    BOOLEAN     IsTccAcitveOffsetSupport  = ReadMsr(MSR_PLATFORM_INFO) & 0x40000000 ? 1:0;
    //MSR 0xCE[33:34] Programmable TCC Acivation Offset Supported    
    BOOLEAN     IsCtdpSupport  = Shr64(ReadMsr(MSR_PLATFORM_INFO), 33) & 0x3 ? 1:0;
    //InitAmiLib(ImageHandle,SystemTable);

    PROGRESS_CODE(DXE_CPU_INIT);
    
    //Free the memory
    if (IsFreeMemBelow1MB)
        pBS->FreePages(gTempBuffer, EFI_SIZE_TO_PAGES(PMM_EBDA_LOMEM_SIZE) - 1);
    
    //Init global data for later usage
    Status = GlobalDataInitialize();
       
    //Create AMI private CpuInfo1 and CpuInfo2 for AMI other module usage   
    CreatePrivateAmiCpuInfo1();       
    CreatePrivateAmiCpuInfo2();    
   
     Status = pBS->InstallProtocolInterface(
                    &TheImageHandle,
                    &gAmiCpuInfo2ProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    gPrivateAmiCpuInfo2
                );
                
     Status = pBS->InstallProtocolInterface(
                    &TheImageHandle,
                    &gAmiCpuInfoProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gAmiCpuInfoProtocol
                );           
        
    // Get CPU feature & set SetupCpuFeatures variable to hide unsupported setup items
	DxeInitPlatformCpuLib(pBS, pRS, &gSetupHandle);

    FirstHob = GetEfiConfigurationTable(pST,&gHobListGuid);
    if (!FirstHob) return;    

    //Fill CpuInfoHob
    gCpuInfoHob = (CPUINFO_HOB*)FirstHob;

    //Find CpuInfo Hob & Update it
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION,&gCpuInfoHob))) {
        if (guidcmp(&gCpuInfoHob->EfiHobGuidType.Name,&gAmiCpuinfoHobGuid) == 0) break;
    }
    if (EFI_ERROR(Status)) return;

    for (i = 0; i < gNumOfCpuCores; ++i) {                
        gCpuInfoHob->Cpuinfo[i].ApicId = gEfiMpProcContext[i].ApicID;
    }

    MpCpuApicIdData.NumberOfCpu = (UINT8)gNumOfCpus;
    for (i = 0; i < gNumOfCpus; ++i) {
        MpCpuApicIdData.ApicId[i] = (UINT8)(gEfiMpProcContext[i].ApicID);
    }
    Status = pRS->SetVariable(
			    L"CPUS3APICID",
			    &gMpCpuApicIdDataGuid,
			    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
			    sizeof(MP_CPU_APICID_DATA),
			    &MpCpuApicIdData );
    
        
    gCpuFeatures = gCpuInfoHob->CpuFeatures;
 
    //Init setup feature data
#if TCG_SUPPORT || TCG2Support
	PlatformCpuSmxSupport(gSetupHandle, IsSmxSupported(&gCpuFeatures));
#else
	PlatformCpuSmxSupport(gSetupHandle, FALSE);
#endif
    PlatformCpuXdSupport(gSetupHandle, isXDSupported(&gCpuFeatures));
    PlatformCpuLimitCpuidSupport(gSetupHandle, isLimitCpuidSupported());
    PlatformCpuVtSupport(gSetupHandle, IsVmxSupported(&gCpuFeatures));
    PlatformCpuHtSupport(gSetupHandle, NumSupportedThreadsPerCore() > 1);
    PlatformCpuMultiCoreSupport(gSetupHandle, NumSupportedCpuCores() >  1);
    PlatformCpuMultiSocketSupport(gSetupHandle, NUMBER_CPU_SOCKETS > 1);
    PlatformCpuMultiSocketPopulated(gSetupHandle, NumberOfCpuSocketsPopulated() > 1);
    PlatformCpuSocketSetPopulated(gSetupHandle, 0, TRUE);
    PlatformCpuTccActiveOffsetSupport(gSetupHandle, IsTccAcitveOffsetSupport);
    PlatformCpuXeCoreRatioLimitSupport(gSetupHandle, IsXeCoreRatioLimitSupport);
    //All CPU should support Current Limit Programming 
    PlatformCpuCurrentLimitSupport(gSetupHandle, TRUE);
    PlatformCpuPwrLimitConfigSupport(gSetupHandle, IsPwrLimitConfigSupport);
    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    PlatformCpuEistSupport(gSetupHandle, !!(RegEcx & (1 << 7)));
    PlatformCpuAesSupport(gSetupHandle, !!(gRegEcx & (1 << 25)));
	PlatformCpuPkgCStateDemotionSupport(gSetupHandle, (RegEax > 0x0306C1));
    PlatformCpuTurboModeSupport(gSetupHandle, isTurboModeSupported());
    CPULib_CpuID(5, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    PlatformCpuC3Support(gSetupHandle, !!(RegEdx & C3_SUB_STATES_MASK));
    PlatformCpuC6Support(gSetupHandle, !!(RegEdx & C6_SUB_STATES_MASK));
    PlatformCpuC7Support(gSetupHandle, !!(RegEdx & C7_SUB_STATES_MASK));
    PlatformCpuC8Support(gSetupHandle, !!(RegEdx & C8_SUB_STATES_MASK));
    PlatformCpuC9Support(gSetupHandle, !!(RegEdx & C9_SUB_STATES_MASK));
    PlatformCpuC10Support(gSetupHandle, !!(RegEdx & C10_SUB_STATES_MASK));    
    PlatformCpuCtdpSupport(gSetupHandle, IsCtdpSupport);
	PlatformTpmDevicePresent(gSetupHandle, (*TpmBaseAddr != 0xff));
    	
	Status = DxePlatformCpuSaveSupportedData(pRS);
    ASSERT_EFI_ERROR(Status);

#if CPU_SETUP_SET_BOOT_RATIO
    CpuSetBootRatio();
#endif

#if CPU_MODULE_CREATE_SMBIOS_TABLES == 1
    CpuSmbios();
#endif
	
	Status = pBS->CreateEvent(
        EVT_SIGNAL_EXIT_BOOT_SERVICES,
        TPL_CALLBACK,
        PrepareToBoot,
        (VOID*)TRUE,
        &BootEvent
    );
    ASSERT_EFI_ERROR(Status);
	
#ifdef CSM_SUPPORT
    
    Status = RegisterProtocolCallback(
		        &gAmiLegacyBootProtocolGuid,
		        PrepareToBoot,
		        NULL, 
		        &BootEvent, 
		        &pRegistration );
		        
#endif

	CpuDxeMiscFuncs();
	
    return;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   AmiCpuSmmFeatureEnCallbacks
//
// Description: Callback for trigger SMI to enable Cpu SMM feature in SMM
//
// Input:
//  IN EFI_EVENT       Event    -- 
//  IN VOID *          Context  -- 
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AmiCpuSmmFeatureEnCallbacks(IN EFI_EVENT Event, IN VOID *Context)
{

#ifdef SW_SMI_ENABLE_SMM_FEATURE    
    pBS->CloseEvent(Event);
#if SMM_ACCESS_CHECK_ENABLE    
    IoWrite8(SW_SMI_IO_ADDRESS, SW_SMI_ENABLE_SMM_FEATURE);
#endif    
#endif    
    
}    
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   DxeInitializeCpu
//
// Description: Cpu Dxe Entrypoint.
//
// Input:
//  IN EFI_HANDLE       ImageHandle   -- Handle assigned to this driver.
//  IN EFI_SYSTEM_TABLE *SystemTable  -- Efi System table.
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DxeInitializeCpu(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
    
    EFI_STATUS Status;
    AMI_BEFORE_CPU_RC_PROTOCOL     *AmiBeforeCpuRcProtocol;

#if AMI_PEI_DEBUG_SUPPORT
    AMI_DEBUGGER_CPU_PROTOCOL      *AmiDebuggerCpuProtocol;
#endif    

    InitAmiLib(ImageHandle,SystemTable);

	// Get CPU support feature before CPU RC DXE initialize
	CPULib_CpuID(1, &gRegEax, &gRegEbx, &gRegEcx, &gRegEdx);
    
    Status = RegisterProtocolCallback(
    	&gEfiMpServicesProtocolGuid,
        AmiCpuMpServiceCallback,
        NULL,
        &gAmiMpEvent,
        &gAmiMpEventRegistration
    );
    
    Status = RegisterProtocolCallback(
        &gEfiDxeSmmReadyToLockProtocolGuid,
        AmiCpuSmmFeatureEnCallbacks,
        NULL,
        &gSmmFeaEnEvent,
        &gSmmFeaEnReg
    );
    ASSERT_EFI_ERROR(Status);
    
    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(AMI_BEFORE_CPU_RC_PROTOCOL),
                                (VOID**)&AmiBeforeCpuRcProtocol );
    
    
     Status = pBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gAmiBeforeCpuRcProtocolGuid, AmiBeforeCpuRcProtocol,
        NULL );
#if AMI_PEI_DEBUG_SUPPORT

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(AMI_DEBUGGER_CPU_PROTOCOL),
                                (VOID**)&AmiDebuggerCpuProtocol );

    AmiDebuggerCpuProtocol->DebuggerGetAptioIntHandler = DebuggerGetAptioInterruptHandlerHalt;                                
    AmiDebuggerCpuProtocol->DebuggerFixUpPEIExceptionHandlers = DebuggerFixUpPEIDebuggerExceptionHandlers;
    AmiDebuggerCpuProtocol->DebuggerSetupExceptionHandler = DebuggerSetupPEIDebuggerExceptionHandlers;
    AmiDebuggerCpuProtocol->DebuggerIsDebuggerIrqHadler = DebuggerIsItPEIDebugIRQHandlerToHookup;
    
    Status = pBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gAmiDebuggerCpuProtocolGuid, AmiDebuggerCpuProtocol,
        NULL );
#endif
         
     gTempBuffer = 0xA0000 - PMM_EBDA_LOMEM_SIZE;
     IsFreeMemBelow1MB = FALSE;
     Status = pBS->AllocatePages (
                    AllocateAddress,
                    EfiBootServicesData,
                    EFI_SIZE_TO_PAGES(PMM_EBDA_LOMEM_SIZE) - 1,
                    &gTempBuffer
                    );

    if (!EFI_ERROR(Status))
        IsFreeMemBelow1MB = TRUE;
        
    return EFI_SUCCESS;

}

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

