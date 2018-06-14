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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/SMM/SmmDispatcher.c 5     6/17/16 4:14a Chienhsieh $
//
// $Revision: 5 $
//
// $Date: 6/17/16 4:14a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/SMM/SmmDispatcher.c $
// 
// 5     6/17/16 4:14a Chienhsieh
// Roll back #if condition: "ENABLE_SEND_SMI_IPI_IN_SMM" as Rev.3
// 
// 4     7/08/15 4:26a Chienhsieh
// 
// 3     12/19/12 6:25a Wesleychen
// Set a #if condition: "ENABLE_SEND_SMI_IPI_IN_SMM" to isolate send SMI
// IPI in SMM for avoid system stay in an unstable state when numerous
// SMI# are generated.
// 
// 2     10/31/12 6:30a Wesleychen
// Modify SMM InterruptManage function to execute Non-PI handler after PI
// handler.
// 
// 75    10/03/11 2:53p Markw
// Add SMM Machine Check handler.
// Files: SmmDispatcher.c, SmmDispatcherAsm.asm
// 
// 74    9/28/11 4:52p Markw
// [TAG]  		EIP71122
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	System may hang randomly in PI 1.1 mode.
// [RootCause]  	PI 1.1 SMST was initialized using uninitialized gSmmBase.
// [Solution]  	Initialize gSmmBase before initializing PI 1.1 SMST.
// [Files]  		SmmDispatcher.c
// 
// 73    6/01/11 3:09p Markw
// [TAG]  		EIP61586
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	None
// [RootCause]  	SMM security issue. Need ITP, specific board, and memory
// to exploit.
// SMM Dispatcher reads a pointer out of SMM. It uses this pointer to
// access outside of SMM.
// To exploit, the pointer would have to modified to write inside of SMM
// to update code to allow SMM code to access the function call outside of
// SMM.
// Then, the exploit would have update a callback structure with an
// address outside of SMM.
// [Solution]  	Copy the pointer inside of SMM. Thus, a direct write
// outside of SMM without reading a pointer outside of SMM first.
// [Files]  		SmmDispatcher.c
// 
// 72    4/15/11 4:39p Markw
// [TAG]  		EIP57440
// [Category]  	New Feature
// [Description]  	PI 1.1 update of Manage function from previous
// check-in.
// [Files]  		SmmDispatcher.c
// 
// 71    3/31/11 6:44p Markw
// [TAG]  		EIP57440
// [Category]  	Improvement
// [Description]  	Separate Framework and PI 1.1 registered SMI source
// handlers function return status checking.
// [Files]  		SmmDispatcher.c
// 
// 69    2/07/11 3:29p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
// 67    10/13/10 1:15p Markw
// Fix compiler warning form Timeout->EndValue = ((UINT32)EndValue) & ((1
// << NUM_BITS_IN_ACPI_TIMER) - 1);
// 
// 66    9/10/10 5:05p Markw
// Typecase to UINT8 when comparing savestate eax with SW SMI number.
// 
// 65    4/29/10 11:23a Markw
// Added some additional asserts on allocating SMM memory during SMM
// initialization.
// 
// 64    4/27/10 7:28p Markw
// EIP 37921 - Update timeout functions to fix boundary condition in
// timeout.
// 
// 63    3/02/10 1:49p Markw
// Added functions/structures for Save/Restore CPU state in SMM.
// 
// 62    2/25/10 5:24p Markw
// Install AmiSmmInfo Protocol.
// 
// 61    2/18/10 4:31p Markw
// EIP 34991 -  Update CPU detection of CPU that generated SW SMI. It is
// possible that multiple SW SMI may be generated simutaneously.
// The CPU reported as generated the SW SMI by SwSMiCpuTrigger will the
// first CPU that matches SW_SMI_IO_ADDRESS not just the first CPU found
// that generated a SW SMI.
// 
// 60    11/23/09 11:27a Markw
// Remove ASSERT when SBSP not in SMM.
// 
// 59    11/23/09 10:59a Markw
// Renamed TIMEOUT to SMM_TIMEOUT.
// 
// 58    9/09/09 5:17p Markw
// EIP #25506 - Use token for x2apic support.
// 
// 57    8/05/09 3:03p Markw
// EIP #24914 - Add early local x2APIC support.
// 
// 56    7/08/09 8:04p Markw
// Update headers.
// 
// 55    5/12/09 7:22p Markw
// Fix mismatch #if/#endif when updating AMI_DEBUGGER_SUPPORT.
// 
// 54    5/12/09 7:04p Markw
// EIP #22087 - When AMI Debugger enabled, save IDT for IDT
// re-initialization in SmmEntry.asm.
// 
// 53    1/22/09 1:03p Markw
// EIP #18671 (OPEN) Clear SW SMI status and set EOS inside SMM. Also
// check for private SW SMI as well as private function. Call Clear
// function inside SMM.
// 
// 52    12/24/08 10:54a Markw
// EIP #18423: Adjust EBDA location as more EBDA data is allocated.
// 
// 51    12/01/08 1:55p Markw
// 
// 50    11/25/08 4:09p Markw
// Remove TRACE. Hangs during runtime OS.
// 
// 49    11/25/08 11:25a Markw
// Reinitialize the InSmm variable.
// 
// 48    11/24/08 7:13p Markw
// Save/restore upper byte of Interrupt command register. Check if no IPI
// pending before issuing interrupt.
// 
// 47    11/21/08 4:59p Markw
// SBSP if available dispatches. S3 reinitialization. User ACPI timer for
// time.out.
// 
// 46    11/12/08 4:57p Markw
// Dynamically update the CurrentlyExecutingCpu in SMM SYSTEM TABLE.
// 
// 45    10/03/08 9:45a Markw
// Fix race condindition when sync APs with BSP. Under some conditions
// some APs skip the SmmStartupAp control loop.
// 
// 44    9/26/08 4:52p Markw
// The Private InSmm is now a pointer.
// 
// 43    9/09/08 3:06p Markw
// Align Dispatcher to 4k.
// 
// 42    9/07/08 12:44a Markw
// Separate SMM Private structure into inside SMM and outside SMM
// structure.
// 
// 41    9/04/08 12:26a Markw
// Always have timeout on AP. Check SMM IPI pending status.
// 
// 40    8/28/08 3:54p Markw
// 
// 39    8/28/08 3:52p Markw
// 
// 38    8/12/08 5:58p Markw
// Use SMM instance BSP, not not runtime BSP. Call dispatcher even for SMM
// software SMIs.
// 
// 37    6/10/08 6:45p Markw
// Disable SMM Thunk, if SMM is in TSEG and no CSM.
// 
// 36    6/09/08 5:51p Markw
// Any CPU can be BSP now. Created a Common Entry. Start APs that have not
// started yet.
// 
// 35    5/23/08 11:19a Markw
// Don't allow callbacks once the flag is set.
// 
// 34    3/03/08 6:58p Markw
// Add 32-bit registers to SMM 16-bit thunk.
// 
// 33    11/21/07 1:06p Markw
// Header updates.
// 
// 32    11/21/07 12:56p Markw
// Always install thunk protocol.
// 
// 31    11/14/07 2:02p Markw
// Added SMRR support and updated SMM Cache for non-SMRR.
// Updated SMM interrupt handeling because of complier optimization bug.
// 
// 30    10/29/07 3:38p Markw
// 
// 29    10/29/07 10:58a Markw
// Smm Thunk:
// * Code and data different segments.
// * Code position independent.
// * Switch for CSM for code and EBDA for data.
// 
// 28    10/24/07 12:02p Markw
// SMM Thunk code position independent. Data in a separate segment than
// code in Smm Thunk.
// Combined BSP and AP SmmEntry.
// 
// 27    9/10/07 1:39p Markw
// Add Interrupt Handling in SMM.
// 
// 26    7/25/07 2:11p Markw
// Limit number of CPUs in SMM to maximum in case system shutsdown in SMM.
// 
// 25    6/14/07 11:01a Markw
// Comment change.
// 
// 24    4/13/07 11:03a Markw
// Update header.
// 
// 23    3/27/07 11:42a Markw
// Fix get SmmBases in dispatcher for APs if BSP is in TSEG.
// 
// 22    3/14/07 5:58p Markw
// Allow the BSP to service the SMI if APs time-out.
// 
// 21    2/07/07 11:06a Markw
// Add Smm Cpu State protocol.
// 
// 20    1/30/07 11:58a Markw
// Added code to exit if not all CPUs enter SMM.
// 
// 19    1/11/07 12:29p Markw
// Use switch to enable/disable legacy code during build.
// 
// 18    1/10/07 5:29p Markw
// Only install SMM Thunk if BSP entry below 1MB.
// 
// 17    1/09/07 6:45p Markw
// Remove dependencies on SMM_BSP_BASE. Use SMM Hob.
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		SmmDispatcher.c
//
// Description:	Contains the SMM dispatcher code for BSP & APs
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

//This include should be first.
#include "SmmPrivateShared.h"
#include <Protocol\SmmThunk.h>
#include <AmiSmm.h>
#include <Protocol\SmmCpuState.h>
#include <Protocol\AmiSmmInfo.h>
#if SMM_USE_PI
#include "SmmPi.h"
#include <Protocol\SmmCpu.h>
#include <Protocol\SmmControl2.h>
#else
#include <smm.h>
#include <Protocol\SmmControl.h>
#endif
#include "AmiCspLib.h"

//CPU APIC includes
#define APIC_ALL_EXCLUDING_SELF (3 << 18)
#define APIC_SIPI               (6 << 8)
#define APIC_INIT               (5 << 8)
#define APIC_SMI                (2 << 8)
#define APIC_DELIVERY_STATUS    (1 << 12)
#define APIC_LEVEL_ASSERT       (1 << 14)
#define APIC_LEVEL_DEASSERT     (0 << 14)
#define APIC_NO_SHORT_HAND      (0 << 18)

#define MSR_EXT_XAPIC_ICR        0x830

EFI_GUID	gEfiSmmThunkProtocolGuid = EFI_SMM_THUNK_PROTOCOL_GUID;
EFI_GUID	gSwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
EFI_GUID    gEfiSmmCpuSaveStateProtocolGuid = EFI_SMM_CPU_SAVE_STATE_PROTOCOL_GUID;
EFI_GUID    gAmiSmmInfoProtcolGuid = AMI_SMM_INFO_PROTOCOL_GUID;
#if SMM_USE_PI
EFI_GUID    gEfiCpuIo2ProtocolGuid = EFI_SMM_CPU_IO2_PROTOCOL_GUID;
#endif

UINT8       **gSmmBase;

SMM_ENTRY_INIT_STRUCT       *gSmmEntryData;
SW_SMI_CPU_TRIGGER          *gSwSmiCpuTrigger;
EFI_SMM_CPU_SAVE_STATE_PROTOCOL gEfiSmmCpuSaveState;
SMM_BASE_PRIVATE_STRUCT     *gBasePrivate;
SMM_DISPATCHER_PRIVATE_STRUCT *gDispatcherPrivate;
volatile BOOLEAN    gEntrySemaphore = FALSE;
volatile BOOLEAN    gUseSbsp;
UINT32              gSbsp;
volatile BOOLEAN    gReleaseStartedCpus = FALSE;
volatile UINT32     gNumCpusReady = 0;
volatile BOOLEAN    gAllCpusInSync = FALSE;
volatile BOOLEAN    gReadyForApsToExecute;
volatile UINT8      gInitSemaphore = 0;
BOOLEAN             *gInSmm;


#if SMM_USE_FRAMEWORK
extern EFI_SMM_SYSTEM_TABLE gSmmSystemTable;
#endif
#if SMM_USE_PI
extern EFI_SMM_SYSTEM_TABLE2 gSmmSystemTable2;
extern EFI_SMM_CPU_PROTOCOL gEfiSmmCpuProtocol;
#endif

EFI_SMM_SAVE_RESTORE_FUNCTION SmmSaveRestoreFunctionTable[] = {
    SmmSaveRestoreEnvironment
    NULL
};

#if SMM_USE_PI
EFI_SMM_ENTRY_CONTEXT gEfiSmmEntryContext;  //For now, hardcode.
UINTN gEfiSmmEntryContextSize = sizeof(EFI_SMM_ENTRY_CONTEXT);
#endif

void * Allocate(
    IN VOID *Address OPTIONAL,
    IN UINTN Size,
    UINTN Alignment OPTIONAL
);

VOID InitializeMemoryManager(SMM_BASE_PRIVATE_STRUCT    *Private);
VOID InitializeSmmSystemTable();
VOID InitializeSmmPiSystemTable();
BOOLEAN IsSwSmiTrigger(UINT8 *SmmBase, UINT16 SwSmiPort);
VOID StartAllCpus(SMM_ENTRY_INIT_STRUCT *SmmEntryInit);
VOID HoldStartedCpus(SMM_ENTRY_INIT_STRUCT *SmmEntryInit);
VOID SmmBspEntry(SMM_ENTRY_INIT_STRUCT *SmmEntryInit);
VOID SmmApEntry(SMM_ENTRY_INIT_STRUCT *SmmEntryInit);
UINT32 LockInc32(UINT32 *);
VOID LockDec32(UINT32 *);
VOID MachineCheckHandler();
VOID InitCrc();

EFI_STATUS InterruptManage(
    IN CONST EFI_GUID *HandlerType,
    IN CONST VOID *Context OPTIONAL,
    IN OUT VOID *CommBuffer OPTIONAL,
    IN OUT UINTN *CommBufferSize OPTIONAL
);

typedef struct {
    UINT32  OverFlow;
    UINT32  EndValue;
    UINT32  OldTimerValue;
} SMM_TIMEOUT;

EFI_STATUS StartTimeout(SMM_TIMEOUT *Timeout, UINT32 Time);
EFI_STATUS HasItTimedOut(SMM_TIMEOUT *Timeout);

BOOLEAN EfiSmmFarCall86Ex(
    IN EFI_SMM_THUNK_PROTOCOL           *This,
    IN  UINT16                          Segment,
    IN  UINT16                          Offset,
    IN  SMM_THUNK_IA32_REGISTER_SET_EX  *Regs,
    IN  VOID                            *Stack,
    IN  UINTN                           StackSize
);

//TODOx64: move it to a library header
VOID CPULib_Pause();

BOOLEAN Xchg8(IN OUT volatile UINT8 *, IN UINT8);

//This typedef is the same as EFI_SMM_HANDLER_ENTRY_POINT2 in SmmPi.h.
typedef EFI_STATUS (EFIAPI *SMM_HANDLER_ENTRY) (
    IN EFI_HANDLE DispatchHandle,
    IN CONST VOID *Context OPTIONAL,
    IN OUT VOID *CommBuffer OPTIONAL,
    IN OUT UINTN *CommBufferSize OPTIONAL
);

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CommonEntry
//
// Description: BSP and APs start here from SmmEntry.asm.
//
// Input: 
//  IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit
//
// Output: 
//  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CommonEntry(IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit)
{
    //Two groups of CPUs where come through this function.
    //1. The initial group all at once. They race for the semaphore.
    //   The winning CPU will try to start any other that has not been started.
    //2. The CPUs that got started or stragglers after the time-out.
    //
    //The SMM Dispatcher will be run by the SBSP if it has been started.
    //Otherwise, the winning CPU in #1 will run the Dispatcher.
    //
    //If SMM generates S3, flags will not be reset.

    UINT32 CpuNo = SmmEntryInit->CpuNo;
    volatile UINT8  IsNotFirstCpu = TRUE;
    CPU_LIB_SMM_SAVE_RESTORE_DATA   CpuSaveRestoreData;

    CpuLib_SmmSaveCpuState(&CpuSaveRestoreData);       //This not save state area.

    //Use gSmmEntryData, so all CPUs use the same SmmInit.
    //Re-initialize the variables on first entry and S3 resume.
    if (gSmmEntryData->SmmInit) {
        volatile UINT8 HoldCpus = 1;
        HoldCpus = Xchg8(&gInitSemaphore, HoldCpus);
        if (!HoldCpus) {
            UINT8 i;
            gDispatcherPrivate->NumCpusInSmm = 0;
            gNumCpusReady = 0;
            gAllCpusInSync = FALSE;
            gEntrySemaphore = FALSE;    //This be reset once, or all CPUs go into hold loop.

            for(i = 0; i < gDispatcherPrivate->NumCpus; ++i) {
                gDispatcherPrivate->SmmCpuInfo[i].InSmm =  FALSE;
            }

            gSmmEntryData->SmmInit = 0; //This must be last; it releases the other CPUs.
        } else {
            while (gSmmEntryData->SmmInit) CPULib_Pause();
        }
    }

    //InSmm must be before LockIn32, otherwise StartAllCpus fucntion could 
    //exit time-out loop, and InSmm would be false, so BSP would not execute
    //dispatcher.
    gDispatcherPrivate->SmmCpuInfo[CpuNo].InSmm =  TRUE;

	LockInc32(&gDispatcherPrivate->NumCpusInSmm);

    if (gEntrySemaphore == 0) { //This if causes fewer memory exchanges.
        IsNotFirstCpu = Xchg8(&gEntrySemaphore, IsNotFirstCpu);
    }

    if (!IsNotFirstCpu) {   //This is the first CPU.
        StartAllCpus(SmmEntryInit);
    } else {
        HoldStartedCpus(SmmEntryInit);
    }

    gDispatcherPrivate->SmmCpuInfo[CpuNo].InSmm =  FALSE;

    CpuLib_SmmRestoreCpuState(&CpuSaveRestoreData);       //This not save state area.
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: StartAllCpus
//
// Description:
//  One random CPU enters here. Waits for CPUs to sync. If no sync, tries to
//   start CPUs that didn't enter SMM. 
//
// Input: 
//  IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit
//
// Output: 
//  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID StartAllCpus(IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit)
{
    SMM_TIMEOUT Timeout;
    UINT32 i;

    //Wait until all APs and BSP are synced.
    StartTimeout(&Timeout, SMM_TIME_OUT_US);

    while(gDispatcherPrivate->NumCpusInSmm < gDispatcherPrivate->NumCpus
        && !EFI_ERROR(HasItTimedOut(&Timeout))) CPULib_Pause();

    //If not all CPUs get control in SMM, try to start other CPUs.
    if (gDispatcherPrivate->NumCpusInSmm < gDispatcherPrivate->NumCpus) { 
        for (i = 0; i < gDispatcherPrivate->NumCpus; ++i) {
            if (!gDispatcherPrivate->SmmCpuInfo[i].InSmm) {
                UINT32 ApicId = gDispatcherPrivate->SmmCpuInfo[i].ApicId;
#if LOCAL_X2APIC_SUPPORT
                if (CPULib_IsLocalX2ApicEnabled()) {
                    while(ReadMsr(MSR_EXT_XAPIC_ICR) & APIC_DELIVERY_STATUS);   //Wait until idle.
                    ReadWriteMsr(MSR_EXT_XAPIC_ICR,
                        Shl64(ApicId, 32) + APIC_NO_SHORT_HAND + APIC_LEVEL_ASSERT + APIC_SMI,
                        0xfff32000);
                 } else {
#endif
#if ENABLE_SEND_SMI_IPI_IN_SMM
                    UINT32 SaveHighByte = *(UINT32*)(LOCAL_APIC_BASE + APIC_ICR_HIGH_REGISTER);
                    //Wait until IPI is Idle
                    while(
                        MemRead32((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_LOW_REGISTER)) & APIC_DELIVERY_STATUS
                    );
    
                    //Send IPI to APIC ID.
                    MemReadWrite32(
                        (UINT32*)(LOCAL_APIC_BASE + APIC_ICR_HIGH_REGISTER),
                        ApicId << 24, 
                        0x00ffffff
                    );
                    MemReadWrite32(
                        (UINT32*)(LOCAL_APIC_BASE + APIC_ICR_LOW_REGISTER),
                        (0 << 18) + (1 << 14) + (2 << 8),
                        0
                    );
                    //Restore high byte. Before SMI, BIOS, OS, etc may have 
                    *(UINT32*)(LOCAL_APIC_BASE + APIC_ICR_HIGH_REGISTER) = SaveHighByte;
#endif
#if LOCAL_X2APIC_SUPPORT
                }
#endif
            }
        }

        //If not all CPUs get control in SMM.
        StartTimeout(&Timeout, SMM_TIME_OUT_US);    //uS
        while(gDispatcherPrivate->NumCpusInSmm < gDispatcherPrivate->NumCpus
            && !EFI_ERROR(HasItTimedOut(&Timeout))) CPULib_Pause();
    }

    //Has SBSP been started.
    gUseSbsp = gDispatcherPrivate->SmmCpuInfo[gSbsp].InSmm;

    //The ASSERT below is to signal SBSP not in SMM when testing SMM.
    //It is generally not an error when the ASSERT below is triggered. It is triggered when debugging, non-SMM errors, etc.
    //The SMM Dispatcher is designed to process correctly if SBSP is not in SMM.
    //DEBUG ASSERT(gUseSbsp);

    gReleaseStartedCpus = TRUE;

     if (gUseSbsp) {
        if (SmmEntryInit->CpuNo == gSbsp) SmmBspEntry(SmmEntryInit);
        else SmmApEntry(SmmEntryInit);
    } else {
        SmmBspEntry(SmmEntryInit);  //BSP has not started, so use this as the BSP.
    }

    //reset flags before exiting.
    gEntrySemaphore = FALSE;
    gReleaseStartedCpus = FALSE;    //This must be reset last because this releases APs to resume.
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: HoldStartedCpus
//
// Description:
//  Hold loop for CPU to sync. All but one CPU will enter here.
//
// Input: 
//  IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit
//
// Output: 
//  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID HoldStartedCpus(IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit)
{
    //Wait until trying to start all CPUs.
    while(!gReleaseStartedCpus) CPULib_Pause();
    
    //All CPUs have been started.
    if (gUseSbsp) {
        if (SmmEntryInit->CpuNo == gSbsp) SmmBspEntry(SmmEntryInit);
        else SmmApEntry(SmmEntryInit);
    } else {
        SmmApEntry(SmmEntryInit);
    }

    //Wait until flags are reset by First CPU.
    while (gReleaseStartedCpus) CPULib_Pause();
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmBspEntry
//
// Description: Call Smm call back or dispatch handlers.
//
// Input: 
//  IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit
//
// Output: 
//  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmBspEntry(IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit)
{
    static BOOLEAN DisallowCallbacks = FALSE;
    UINT32      i;
#if INTEL_MP_SW_SMI_PATCH == 1
    EFI_SMM_CPU_SAVE_STATE  *OrigCpuSaveState = 0;
#endif
    UINT32      CpuNo = SmmEntryInit->CpuNo;
    BOOLEAN     IsCallBackFunction = FALSE;

#if SMM_USE_FRAMEWORK
    gSmmSystemTable.CurrentlyExecutingCpu = CpuNo + 1;
#endif
    gDispatcherPrivate->SmmBspNumber = CpuNo;
#if SMM_USE_PI
	gEfiSmmEntryContext.CurrentlyExecutingCpu = CpuNo;
    gSmmSystemTable2.CurrentlyExecutingCpu = CpuNo; //This 0-based, Framework is 1-based.
#endif

    //Copy save state area.
#if SMM_USE_FRAMEWORK
    CPU_GetSaveState(gSmmBase[CpuNo], &gSmmSystemTable.CpuSaveState[CpuNo].Ia32SaveState);
#endif

    //Indicates APs can execute function for a driver when released.
    gReadyForApsToExecute = TRUE;

    LockInc32((UINT32*)&gNumCpusReady);
    while (gNumCpusReady < gDispatcherPrivate->NumCpusInSmm) CPULib_Pause();
    gAllCpusInSync = TRUE;

    //Make OEM Call to save state.
    for (i = 0; SmmSaveRestoreFunctionTable[i] != NULL; ++i) SmmSaveRestoreFunctionTable[i](TRUE);

    //Check if software smi, and the CPU that caused it.
    gSwSmiCpuTrigger->Cpu = (UINTN)-1;

    for(i = 0; i < gDispatcherPrivate->NumCpus; ++i) {
        if (IsSwSmiTrigger(gSmmBase[i], SW_SMI_IO_ADDRESS)) {
            UINT8 SwSmi = IoRead8(SW_SMI_IO_ADDRESS);
#if SMM_USE_FRAMEWORK
            if ( SwSmi == (UINT8)gSmmSystemTable.CpuSaveState[i].Ia32SaveState.EAX) {
#else
                UINT8 RegAl;
                EFI_STATUS Status;
                Status = gEfiSmmCpuProtocol.ReadSaveState(
                    &gEfiSmmCpuProtocol,
                    1,
                    EFI_SMM_SAVE_STATE_REGISTER_RAX,
                    i,
                    &RegAl
                );
                if (EFI_ERROR(Status) || SwSmi == RegAl) {  //Assume if error, then this is the correct CPU.
#endif
                gSwSmiCpuTrigger->Cpu = i;
                break;
            }
        }
    }

//Intel only uses save state CpuSaveState[0] for software SMIs, event though it may
//be generated by a AP. If INTEL_MP_SW_SMI_PATCH is enabled, it will temporarily,
//set CpuSaveState[0] to the AP that generated SMI. However, this means CpuSaveState[x]
//may be invalid.
//
//The PIWG should come up with a permanent solution.
//
#if INTEL_MP_SW_SMI_PATCH == 1
    if ((INTN)gSwSmiCpuTrigger->Cpu > 0) {
        OrigCpuSaveState = gSmmSystemTable.CpuSaveState;
        gSmmSystemTable.CpuSaveState = &OrigCpuSaveState[gSwSmiCpuTrigger->Cpu];
        gSwSmiCpuTrigger->Cpu = 0;
    }
#endif

    if (gDispatcherPrivate->FloatingPointSave) {
//The XMM is already before executing C because of possible optimizations.
//      _asm FXSAVE gSmmSystemTable.CpuOptionalFloatingPointState //Save Floating Point Context;
    }

    *gInSmm = TRUE; //SMM BASE protocol InSmm function returns this variable.
    //This CallBackFunc is only called during boot services before shell.
    if (!DisallowCallbacks) {
        //Check both CallBackFunc and software smi.
        //This is done in case asynchronous SMI occurs between setting up CallBackFunc and SW SMI.
        IsCallBackFunction = gBasePrivate->CallBackFunc && IoRead8(SW_SMI_IO_ADDRESS) == SMMBASE_CALLBACK;

        if (IsCallBackFunction) {
            gBasePrivate->CallBackFunc();
            gBasePrivate->CallBackFunc = 0;
            if (gBasePrivate->DisallowCallbacks) DisallowCallbacks = TRUE;
        }
    }

    gInitSemaphore = 0;     //Clear this away from loop to be sure 2 CPUs don't do xchg.

#if SMM_USE_PI
    InterruptManage(NULL, NULL, &gEfiSmmEntryContext, &gEfiSmmEntryContextSize);    //Execute root handlers
#else
    InterruptManage(NULL, NULL, NULL, NULL);    //Execute root handlers
#endif

    *gInSmm = FALSE; //SMM BASE protocol InSmm function returns this variable.
        
    if (gDispatcherPrivate->FloatingPointSave) {
//The XMM is already before executing C because of possible optimizations.
//      _asm FXRSTOR gSmmSystemTable.CpuOptionalFloatingPointState	//Restore Floating Point Context;
    }

    if (IsCallBackFunction) {
        //This will clear the SW SMI Status. This is done last in case an incorrect
        // implementation Clear, clears all statuses.
        //
        //This will not be called during runtime.
#if SMM_USE_PI
        ((EFI_SMM_CONTROL2_PROTOCOL*)gDispatcherPrivate->SmmControl)->Clear((EFI_SMM_CONTROL2_PROTOCOL*)gDispatcherPrivate->SmmControl, FALSE);
#else
        ((EFI_SMM_CONTROL_PROTOCOL*)gDispatcherPrivate->SmmControl)->Clear((EFI_SMM_CONTROL_PROTOCOL*)gDispatcherPrivate->SmmControl, FALSE);
#endif
    }

//Restore CpuSaveState.
#if INTEL_MP_SW_SMI_PATCH == 1
    if(OrigCpuSaveState) gSmmSystemTable.CpuSaveState = OrigCpuSaveState;
#endif

    //Make OEM Call to restore state.
    for (i = 0; SmmSaveRestoreFunctionTable[i] != NULL; ++i) SmmSaveRestoreFunctionTable[i](FALSE);

#if SMM_USE_FRAMEWORK
    //Copy save state area.
    CPU_RestoreSaveState(gSmmBase[CpuNo], &gSmmSystemTable.CpuSaveState[CpuNo].Ia32SaveState);
#endif

    gReadyForApsToExecute = FALSE;   //Used to indicate that BSP is exiting SMM mode.

    LockDec32(&gDispatcherPrivate->NumCpusInSmm);
    while(gDispatcherPrivate->NumCpusInSmm > 0) CPULib_Pause();

    gNumCpusReady = 0;      //Initialize count.
    gAllCpusInSync = FALSE; //This must be set last. Releases CPUs from SmmApEntry.
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmApEntry
//
// Description: APs after switching to protected mode will jump here.
//
// Input:
//  IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit
//
// Output:
//	VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmApEntry(IN SMM_ENTRY_INIT_STRUCT *SmmEntryInit)
{
    volatile SMM_AP_CPU_CONTROL *SmmApCpuControl = &gDispatcherPrivate->SmmApCpuControl[SmmEntryInit->CpuNo];
    UINT32      CpuNo = SmmEntryInit->CpuNo;

    //Copy save state area.
#if SMM_USE_FRAMEWORK
    CPU_GetSaveState(gSmmBase[CpuNo], &gSmmSystemTable.CpuSaveState[CpuNo].Ia32SaveState);
#endif

    LockInc32((UINT32*)&gNumCpusReady);
    while(!gAllCpusInSync) CPULib_Pause();

    while(gReadyForApsToExecute) {
        if (SmmApCpuControl->Procedure) {
            SmmApCpuControl->Procedure(SmmApCpuControl->ProcArguments);
            SmmApCpuControl->Procedure = 0;
        }
        CPULib_Pause();
    }

#if SMM_USE_FRAMEWORK
    CPU_RestoreSaveState(
        (UINT8*)SmmEntryInit->SmmEntryStart - 0x8000,
        &gSmmSystemTable.CpuSaveState[SmmEntryInit->CpuNo].Ia32SaveState
    );
#endif

    LockDec32(&gDispatcherPrivate->NumCpusInSmm);

    while(gAllCpusInSync) CPULib_Pause();	//Wait until BSP is ready.
}


//*******************************************************
//EFI SMM Handler Return Code
//*******************************************************
#define EFI_HANDLER_SUCCESS			0x0000
#define EFI_HANDLER_CRITICAL_EXIT	0x0001
#define EFI_HANDLER_SOURCE_QUIESCED	0x0002
#define EFI_HANDLER_SOURCE_PENDING	0x0003

EFI_STATUS InterruptManage(
    IN CONST EFI_GUID *HandlerType,
    IN CONST VOID *Context OPTIONAL,
    IN OUT VOID *CommBuffer OPTIONAL,
    IN OUT UINTN *CommBufferSize OPTIONAL
)
{
    HANDLER_LIST    *Link;
#if SMM_USE_PI
    EFI_STATUS      Status = EFI_INTERRUPT_PENDING; //Default: Interrupt not handled.
#else
    EFI_STATUS      Status = EFI_HANDLER_SUCCESS;
#endif
    EFI_STATUS      HdlrStatus;

    for (Link = gDispatcherPrivate->HandlerListHead; Link; Link = Link->Link) {
        if (HandlerType == NULL)  {
            if (!Link->IsRoot) continue;
        } else {
            if (Link->IsRoot || (guidcmp((EFI_GUID*)HandlerType, &Link->HandlerType) != 0)) continue;
        }

#if SMM_USE_PI
        if(Link->IsPi) {
            HdlrStatus = ((SMM_HANDLER_ENTRY)Link->EntryPoint)(
                Link->SmmImageHandle, Context, CommBuffer, CommBufferSize
            );

            //TODO: PI 1.1 spec SmiManage function EFI_SUCCESS description questionable.
            //Review with PI work group.

            switch(HdlrStatus) {
            case EFI_WARN_INTERRUPT_SOURCE_PENDING:
                break;
            //TODO: Comment out for now because of build error related to core header files.
            //case EFI_INTERRUPT_PENDING:
            //    return EFI_INTERRUPT_PENDING;
            case EFI_WARN_INTERRUPT_SOURCE_QUIESCED:
                Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;  //Change status to interrupt handled.
                break;
            case EFI_SUCCESS:
                if (Link->IsRoot) {
                    Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;  //Change status to interrupt handled.
                    break;    //Continue checking other root handlers.
                }
                return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
            default:
                break;
            }
        }
#endif
#if 0//SMM_USE_FRAMEWORK
        if (!Link->IsPi) {
            HdlrStatus = ((EFI_SMM_CALLBACK_ENTRY_POINT)Link->EntryPoint)(
                Link->SmmImageHandle, Link->CommunicationBuffer, Link->SourceSize
            );
            switch(HdlrStatus) {
            case EFI_HANDLER_CRITICAL_EXIT:
            case EFI_HANDLER_SOURCE_QUIESCED:
                return EFI_HANDLER_CRITICAL_EXIT;
            case EFI_HANDLER_SUCCESS:
            case EFI_HANDLER_SOURCE_PENDING:
            default:
                Status = EFI_SUCCESS;
                break;
            }
        }
    #endif
    }
#if SMM_USE_FRAMEWORK
    if (HandlerType == NULL)
    {
        for (Link = gDispatcherPrivate->HandlerListHead; Link; Link = Link->Link)
        {
            if (!Link->IsRoot)
                continue;

            if (!Link->IsPi)
            {
                HdlrStatus = ((EFI_SMM_CALLBACK_ENTRY_POINT)Link->EntryPoint)(Link->SmmImageHandle, Link->CommunicationBuffer, Link->SourceSize);
                switch(HdlrStatus)
                {
                    case EFI_HANDLER_CRITICAL_EXIT:
                    case EFI_HANDLER_SOURCE_QUIESCED:
                        return EFI_HANDLER_CRITICAL_EXIT;
                    case EFI_HANDLER_SUCCESS:
                    case EFI_HANDLER_SOURCE_PENDING:
                    default:
                        Status = EFI_SUCCESS;
                        break;
                }
            }
        }
    }
#endif
    return Status;
}


//SMM thunk either requires AB Segment of CSM.
#if SMM_THUNK_NO_AB_SEG == 0 || SMM_THUNK_IN_CSM == 1

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	EfiSmmFarCall86Ex
//
// Description:
//  Smm Thunk call. If no stack, this will push flags to simulate int call.
//
// Input:   
//  IN EFI_SMM_THUNK_PROTOCOL           *This,
//  IN  UINT16                          Segment -16-bit segment to call
//  IN  UINT16                          Offset  -16-bit offset to call
//  IN  SMM_THUNK_IA32_REGISTER_SET_EX  *Regs   -Preload registers before call
//  IN  VOID                            *Stack  -Stack before call optional
//  IN  UINTN                           StackSize - if no stack, this should be zero.
//
// Output:  BOOLEAN
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN EfiSmmFarCall86Ex(
    IN EFI_SMM_THUNK_PROTOCOL           *This,
    IN  UINT16                          Segment,
    IN  UINT16                          Offset,
    IN  SMM_THUNK_IA32_REGISTER_SET_EX  *Regs,
    IN  VOID                            *Stack,
    IN  UINTN                           StackSize
)
{
    SMM_THUNK_DATA *SmmThunkData = gDispatcherPrivate->SmmThunkData;

#if SMM_THUNK_IN_CSM == 1
    if (gDispatcherPrivate->EbdaStartOffset) {
        UINT32 CurrentEbda = (UINT32)(UINTN)(*(UINT16*)0x40e << 4);
        SmmThunkData =(SMM_THUNK_DATA *) (CurrentEbda + gDispatcherPrivate->EbdaStartOffset);
    }
#endif
    
    SmmThunkData->FarCall.Segment = Segment;
    SmmThunkData->FarCall.Offset = Offset;

	//Copy address for stack
    if (Stack) {
        SmmThunkData->Stack.Stack = (UINT32)Stack;
        SmmThunkData->Stack.StackSize = (UINT32)StackSize;
    } else SmmThunkData->Stack.StackSize = 0;

    //Copy thunk registers.
    SmmThunkData->Regs = *Regs;

    gDispatcherPrivate->SmmThunkProc();		    //Do Far call.

    //Restore thunk registers.
    *Regs = SmmThunkData->Regs;

    return TRUE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   EfiSmmFarCall86
//
// Description:
//  Smm Thunk call. If no stack, this will push flags to simulate int call.
//
// Input:
//  IN EFI_SMM_THUNK_PROTOCOL       *This,
//  IN  UINT16                      Segment -16-bit segment to call
//  IN  UINT16                      Offset  -16-bit offset to call
//  IN  SMM_THUNK_IA32_REGISTER_SET *Regs   -Preload registers before call
//  IN  VOID                        *Stack  -Stack before call optional
//  IN  UINTN                       StackSize - if no stack, this should be zero.
//
// Output:  BOOLEAN
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN EfiSmmFarCall86(
    IN EFI_SMM_THUNK_PROTOCOL       *This,
    IN  UINT16                      Segment,
    IN  UINT16                      Offset,
    IN  SMM_THUNK_IA32_REGISTER_SET *Regs,
    IN  VOID                        *Stack,
    IN  UINTN                       StackSize
)
{
    SMM_THUNK_IA32_REGISTER_SET_EX  RegsEx;
    BOOLEAN RetValue;

    RegsEx.X.AX = Regs->X.AX;
    RegsEx.X.BX = Regs->X.BX;
    RegsEx.X.CX = Regs->X.CX;
    RegsEx.X.DX = Regs->X.DX;
    RegsEx.X.SI = Regs->X.SI;
    RegsEx.X.DI = Regs->X.DI;
    RegsEx.X.Flags = Regs->X.Flags;
    RegsEx.X.ES = Regs->X.ES;
    RegsEx.X.CS = Regs->X.CS;
    RegsEx.X.SS = Regs->X.SS;
    RegsEx.X.DS = Regs->X.DS;
    RegsEx.X.BP = Regs->X.BP;

    RetValue =  EfiSmmFarCall86Ex(
        This,
        Segment,
        Offset,
        &RegsEx,
        Stack,
        StackSize
    );

    Regs->X.AX = RegsEx.X.AX;
    Regs->X.BX = RegsEx.X.BX;
    Regs->X.CX = RegsEx.X.CX;
    Regs->X.DX = RegsEx.X.DX;
    Regs->X.SI = RegsEx.X.SI;
    Regs->X.DI = RegsEx.X.DI;
    Regs->X.Flags = RegsEx.X.Flags;
    Regs->X.ES = RegsEx.X.ES;
    Regs->X.CS = RegsEx.X.CS;
    Regs->X.SS = RegsEx.X.SS;
    Regs->X.DS = RegsEx.X.DS;
    Regs->X.BP = RegsEx.X.BP;

    return RetValue;
}

EFI_SMM_THUNK_PROTOCOL EfiSmmThunkProtocol = {EfiSmmFarCall86, EfiSmmFarCall86Ex};

#endif

#pragma pack (1)
typedef struct {
    UINT16  LoOffset;
    UINT16  Segment;
    UINT16  DescBits;   //Will be set to 0x0f00 Present=1, DPL = 0, D = 1 (32bit)
    UINT16  HiOffset;
#ifdef EFIx64
    UINT32  Hi32Offset;
    UINT32  Rsv;
#endif
} INTR_GATE_DESC;

typedef struct {
    UINT8   MovAlOp;
    UINT8   InterruptNum;
    UINT8   JmpOp;
    UINT8   RelOffset;
} INT_ENTRY_POINT;

INT_ENTRY_POINT gIntEntryTemplate = {    //No global memory
    0xb0,           //mov al, Int
    0,              //Int
    0xeb,           //jmp
    0xfe            // to itself
};

typedef struct {
    UINT8   PushEaxOp;
    UINT8   MovAlOp;
    UINT8   MovAlValue;
    UINT8   OutAlOp;
    UINT8   OutAlValue;
    UINT8   PopEaxOp;
#ifdef EFIx64
    UINT8   Ext64Op;
#endif
    UINT8   IretValue;
} EOI_TEMPLATE;

EOI_TEMPLATE EoiTemplate = {
    0x50,           //push eax/rax
    0xb0, 0x20,     //mov al, 20h   ;EOI
    0xe6, 0x20,     //out 20h, al   ;Sent Master EOI to interrupt controller.
    0x58,           //pop eax/rax
#ifdef EFIx64
    0x48,           //Ext 64-bit Opcode.
#endif
    0xcf            //iret
};

#pragma pack()

#define NUM_EXCEPTIONS 19

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitInterrupts
//
// Description:
//  Install Interrupt Handlers. Initialize the interrupt descriptors.
//
// Input:   VOID
//
// Output:  VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitInterrupts()
{
#if AMI_DEBUGGER_SUPPORT
    CPULib_SaveIdt(&gDispatcherPrivate->Idt);
    return;
#else

    UINT32       	i;
    UINT16      	Segment;
    INT_ENTRY_POINT *IntEntryPoint;
    INTR_GATE_DESC  *IntGateDescs;
#ifdef EFIx64
    UINT16          *DummyIrqHandler;
#else
    UINT8           *DummyIrqHandler;
#endif

    //Allocate memory for addresses of interrupt Handlers.
    DummyIrqHandler = Allocate(0, sizeof(*DummyIrqHandler), 0);
    ASSERT(DummyIrqHandler != NULL);

#ifdef EFIx64
    *DummyIrqHandler = 0xcf48;	//IRET
#else
    *DummyIrqHandler = 0xcf;
#endif

    IntEntryPoint = Allocate(0, sizeof(INT_ENTRY_POINT) * NUM_EXCEPTIONS, 0);
    ASSERT(IntEntryPoint != NULL);

    //Initialize interrupt entry points using template.
    for(i = 0; i < NUM_EXCEPTIONS; ++i) {
        gIntEntryTemplate.InterruptNum = i;
        IntEntryPoint[i] = gIntEntryTemplate;
    }

    //Alocate space for Interrupt Descriptor Table. 256 entries/8 bytes.
    IntGateDescs = Allocate(0, 256 * sizeof(*IntGateDescs),0);
    ASSERT(IntGateDescs != NULL);

    Segment = GetCsSegment();

    //Setup halts for exceptions.
    for (i = 0 ; i < NUM_EXCEPTIONS; ++i) {
        UINTN IntHndlrAddr = (UINTN)&IntEntryPoint[i];
        if (i == 18) IntHndlrAddr = (UINTN)MachineCheckHandler;

        IntGateDescs[i].LoOffset=(UINT16)IntHndlrAddr;
        IntGateDescs[i].HiOffset=(UINT16)((UINT32)IntHndlrAddr >> 16);
        IntGateDescs[i].Segment=Segment;
        IntGateDescs[i].DescBits=0x8e00;  //Present=1, DPL = 0, D = 1 (32bit)
#ifdef EFIx64
        IntGateDescs[i].Hi32Offset = 0;
        IntGateDescs[i].Rsv = 0;
#endif
    }

    //Initialize the rest for dummy irets except timer to be overwritten below.
    for (; i < 256 ; ++i) {
        IntGateDescs[i].LoOffset=(UINT16)DummyIrqHandler;
        IntGateDescs[i].HiOffset=(UINT16)((UINT32)DummyIrqHandler >> 16);
        IntGateDescs[i].Segment=Segment;
        IntGateDescs[i].DescBits=0x8e00;  //Present=1, DPL = 0, D = 1 (32bit)
#ifdef EFIx64
        IntGateDescs[i].Hi32Offset = 0;
        IntGateDescs[i].Rsv = 0;
#endif
    }

//Setup EOI for timer interrupt.
    {
        VOID *TimerEoi = Allocate(0, sizeof(EOI_TEMPLATE), 0);
        ASSERT(TimerEoi != NULL);
        MemCpy(TimerEoi, &EoiTemplate, sizeof(EOI_TEMPLATE));

        IntGateDescs[MASTER_INTERRUPT_BASE].LoOffset=*(UINT16*)&TimerEoi;
        IntGateDescs[MASTER_INTERRUPT_BASE].HiOffset=*(((UINT16*)&TimerEoi)+1);
    }    

    gDispatcherPrivate->Idt.Base=(UINT32)(UINTN)IntGateDescs;
#ifdef EFIx64
    gDispatcherPrivate->Idt.Limit=16*256-1;
#else
    gDispatcherPrivate->Idt.Limit=8*256-1;
#endif
#endif
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: StartTimeout
//
// Description:
//  Initialize timeout for a specified about of time in uS.
//
// Input:
//  OUT SMM_TIMEOUT *Timeout
//  IN UINT32 Time
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS StartTimeout(OUT SMM_TIMEOUT *Timeout, IN UINT32 Time)   //uS
{
    UINT64  TicksNeeded;
    UINT64  EndValue;
    
    //
    // There are 3.58 ticks per us.
    //
    // TicksNeeded = Time * 358 / 100
    //
    TicksNeeded = Div64 (Mul64 (Time, 358), 100, NULL);
    
    // Read ACPI Timer
    Timeout->OldTimerValue = IoRead32(PM_TMR_BLK_ADDRESS);
    EndValue = TicksNeeded + Timeout->OldTimerValue;
    
    //
    // Calculate Overflow and EndValue from FullEndValue,
    // based on number of bits in ACPI Timer
    //
    Timeout->OverFlow = (UINT32)Shr64 (EndValue, NUM_BITS_IN_ACPI_TIMER);
    Timeout->EndValue = ((UINT32)EndValue) & (UINT32)(((UINT64)1 << NUM_BITS_IN_ACPI_TIMER) - 1);
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: HasItTimedOut
//
// Description:
//  Return EFI_TIMEOUT if timer has expired.
//
// Input:
//  IN OUT SMM_TIMEOUT *Timeout
//
// Output:  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS HasItTimedOut(IN OUT SMM_TIMEOUT *Timeout)
{
    UINT32 TimerValue;

    //Read ACPI Timer
    TimerValue = IoRead32(PM_TMR_BLK_ADDRESS);

    if (Timeout->OverFlow > 0) {
        //
        // See if the current timer value is less than the previous value.
        // If it is, then the timer had wrapped around.
        //
        if (TimerValue < Timeout->OldTimerValue) {
            --Timeout->OverFlow;
        }
        
        // Update OldTimerValue
        Timeout->OldTimerValue = TimerValue;
        return EFI_SUCCESS;
    }
    
    //
    // See if the current timer value is less than the previous value.
    // If it is, then we are done.
    //
    if (TimerValue < Timeout->OldTimerValue) return EFI_TIMEOUT;
    
    // If we passed the EndValue, we are done.
    if (TimerValue >= Timeout->EndValue) return EFI_TIMEOUT;
    
    // Update OldTimerValue
    Timeout->OldTimerValue = TimerValue;
    
    return EFI_SUCCESS;
}

EFI_STATUS GetNumOfCpusInsideSmm(
    IN  AMI_SMM_INFO_PROTOCOL   *This,
    OUT UINT32 *Cpus
)
{
    if (Cpus == NULL) return EFI_INVALID_PARAMETER;
    *Cpus = gDispatcherPrivate->NumCpusInSmm;
    return EFI_SUCCESS;
}

AMI_SMM_INFO_PROTOCOL gAmiSmmInfo = {
    0,  //Protocol Ver
    GetNumOfCpusInsideSmm
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitializeDispatcher
//
// Description: Initialize Dispatcher.
//
// Input:
//  IN EFI_HANDLE		ImageHandle
//  IN EFI_SYSTEM_TABLE	*SystemTable
//
// Output:
//  EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitializeDispatcher(
    IN  EFI_HANDLE				        ImageHandle,
    IN  EFI_SYSTEM_TABLE	            *SystemTable,
    IN  SMM_BASE_PRIVATE_STRUCT	        *BasePrivate,
    IN  SMM_DISPATCHER_PRIVATE_STRUCT   *DispatcherPrivate,
    OUT VOID                            **SmstTable,
    OUT VOID                            **SmstTable2
)
{
    //SwSmiCpuTrigger is temporary. When installed in the configuration table
    // a copy will be made. The copy will be used.
    SW_SMI_CPU_TRIGGER	SwSmiCpuTrigger = {(UINTN)-1};
    VOID  *Address;
    UINT8 *SmmAllocMemoryStart = BasePrivate->SmmAllocMemoryStart;
    SMM_HOB     *SmmHob = BasePrivate->SmmHob;
    EFI_HANDLE	Handle=NULL;
    EFI_STATUS	Status;
    UINT32   i;
//-------------------------------
    InitAmiLib(ImageHandle, SystemTable);

    gBasePrivate = BasePrivate;
    gDispatcherPrivate = DispatcherPrivate;

    gInSmm = gBasePrivate->InSmm;   //Initialize pointer SMM BASE function InSmm to notify if inside of SMM.

    InitializeMemoryManager(BasePrivate);

    //Allocate Image
    Address = Allocate(gBasePrivate->Pe32DispatcherImage, BasePrivate->Pe32DispatcherImageSize, 0);
    ASSERT(Address != NULL);

    InitInterrupts();

    gSmmBase = (UINT8**)Allocate(0, sizeof(UINT8**) * SmmHob->NumCpus, 0);
    ASSERT(gSmmBase != NULL);

    gEfiSmmCpuSaveState.CpuSaveState = (EFI_SMM_CPU_STATE**)Allocate(0, sizeof(EFI_SMM_CPU_STATE*) * SmmHob->NumCpus, 0);
    ASSERT(gEfiSmmCpuSaveState.CpuSaveState != NULL);

/*
    //Any Cpu number can be BSP.
    for(i = 0; i < SmmHob->NumCpus; ++i) {
        gSmmBase[i] = (UINT8*)(SmmHob->SmmBase[i]);
        gEfiSmmCpuSaveState.CpuSaveState[i] = (EFI_SMM_CPU_STATE*)(SmmHob->SmmBase[i] + 0x10000-0x400);
    }
*/

    //CPU Number 0 must be BSP.
    gSmmBase[0] = (UINT8*)(SmmHob->SmmBase[SmmHob->Bsp]);
    gEfiSmmCpuSaveState.CpuSaveState[0] = (EFI_SMM_CPU_STATE*)(SmmHob->SmmBase[SmmHob->Bsp] + 0x10000-0x400);


    for(i = 0; i < SmmHob->NumCpus; ++i) {
        static UINT32 ApNum = 0; //BSP is given CPU #0, and APs 1,2...
        if (i == SmmHob->Bsp) continue;
        ++ApNum;

        gSmmBase[ApNum] = (UINT8*)(SmmHob->SmmBase[i]);
        gEfiSmmCpuSaveState.CpuSaveState[ApNum] = (EFI_SMM_CPU_STATE*)(SmmHob->SmmBase[i] + 0x10000-0x400);
    }

    gSmmEntryData = (SMM_ENTRY_INIT_STRUCT *) (gSmmBase[0] + 0x8004);
    gSmmEntryData->DispatcherEntry = CommonEntry;
    gSmmEntryData->DispatcherPrivate = DispatcherPrivate;

    gSbsp = 0;//SmmHob->Bsp;

    InitCrc();
#if SMM_USE_PI
    InitializeSmmPiSystemTable();
#endif
#if SMM_USE_FRAMEWORK
    InitializeSmmSystemTable();
#endif


//If installed, it will install on both SMST tables.
#if SMM_USE_PI
    Status = gSmmSystemTable2.SmmInstallConfigurationTable(
		&gSmmSystemTable2,
		&gSwSmiCpuTriggerGuid,
		&SwSmiCpuTrigger,
		sizeof(SW_SMI_CPU_TRIGGER)
	);
	ASSERT_EFI_ERROR(Status);
#else
    Status = gSmmSystemTable.SmmInstallConfigurationTable(
        &gSmmSystemTable,
        &gSwSmiCpuTriggerGuid,
        &SwSmiCpuTrigger,
        sizeof(SW_SMI_CPU_TRIGGER)
    );
    ASSERT_EFI_ERROR(Status);
#endif

#if SMM_USE_PI
    gSwSmiCpuTrigger = gSmmSystemTable2.SmmConfigurationTable[0].VendorTable;
#else
    gSwSmiCpuTrigger = gSmmSystemTable.SmmConfigurationTable[0].VendorTable;
#endif

#if SMM_USE_FRAMEWORK
    *SmstTable = &gSmmSystemTable;
#endif
#if SMM_USE_PI
	*SmstTable2 = &gSmmSystemTable2;
#endif

#if SMM_USE_FRAMEWORK
    pBS->InstallMultipleProtocolInterfaces (
        &Handle,
        &gAmiSmmInfoProtcolGuid,            &gAmiSmmInfo,
        &gEfiSmmCpuSaveStateProtocolGuid,   &gEfiSmmCpuSaveState,
//SMM thunk either requires AB Segment or CSM.
#if SMM_THUNK_NO_AB_SEG == 0 || SMM_THUNK_IN_CSM == 1
        &gEfiSmmThunkProtocolGuid,          &EfiSmmThunkProtocol,
#endif
        NULL
    );
#endif

#if SMM_USE_PI
    Handle = NULL;
    gSmmSystemTable2.SmmInstallProtocolInterface(
        &Handle,
        &gAmiSmmInfoProtcolGuid,
        EFI_NATIVE_INTERFACE,
        &gAmiSmmInfo
    );

    Handle = NULL;
    gSmmSystemTable2.SmmInstallProtocolInterface(
        &Handle, 
        &gEfiSmmCpuSaveStateProtocolGuid,
        EFI_NATIVE_INTERFACE,
        &gEfiSmmCpuSaveState
    );

#if SMM_THUNK_NO_AB_SEG == 0 || SMM_THUNK_IN_CSM == 1
	Handle = NULL;
    gSmmSystemTable2.SmmInstallProtocolInterface(
        &Handle,
        &gEfiSmmThunkProtocolGuid,
        EFI_NATIVE_INTERFACE,
        &EfiSmmThunkProtocol
    );
#endif

    Handle = NULL;
    gSmmSystemTable2.SmmInstallProtocolInterface(
        &Handle,
        &gEfiCpuIo2ProtocolGuid,
        EFI_NATIVE_INTERFACE,
        &gSmmSystemTable2.SmmIo
    );

    Handle = NULL;
    gSmmSystemTable2.SmmInstallProtocolInterface(
        &Handle, 
        &gEfiCpuProtocolGuid,
        EFI_NATIVE_INTERFACE,
        &gEfiSmmCpuProtocol
    );
#endif

    return EFI_SUCCESS;
}

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
