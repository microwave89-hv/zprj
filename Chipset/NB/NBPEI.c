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

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBPEI.c 57    5/28/14 3:03a Dennisliu $
//
// $Revision: 57 $
//
// $Date: 5/28/14 3:03a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBPEI.c $
// 
// 57    5/28/14 3:03a Dennisliu
// [TAG]           EIP161790
// [Category]      Improvement
// [Description]   DRAM Init BIT should be set after saving MRC S3 data to
// NVRAM in DXE Phase as Intel suggested.
// [Files]         NBPei.c; NBDxe.c;
//
// 56    8/14/13 6:44a Ireneyang
// [TAG]         EIP129631
// [Category]    BrugFix
// [Symptom]     RBU function is not working
// [Description] 1. The current make file doesn¡¦t build *.hdr file,
//                  we can use that file to verify RBU function under DOS.
//               2. We could build *.hdr file manually, and also verified
//                  the RBU function under DOS. But the RBU function is
//                  not working.
// [Files]       MemoryInit.sdl; MemoryInit.c; NBPEI.c;
//
// 55    6/26/13 4:35a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add new related items into structure.
// [Files]       NBPEI.c;
//
// 53    6/03/13 2:04a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Fix some PEG cards can't be detected.
// [Files]       NBPEI.c;
//
// 52    5/22/13 6:41a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add Token SG_GPIO_SUPPORT for GpioSupport.
// [Files]       NB.sdl; NBPEI.c;
//
// 51    5/13/13 6:26a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add PanelPowerEnable for enabling/disabling VDD force
// bit.
//               (Required only for early enabling of eDP panel)
// [Files]       NBSetup.c; GetSetupData.c; NbSetupData.h; NBPEI.c;
//
// 50    5/09/13 7:20a Ireneyang
// [TAG]         EIP119332
// [Category]    BrugFix
// [Symptom]     Some PEG Lan Cards on NorthBridge would cause hanging
//               issue when waking through them.
// [RootCause]   These Lan cards on NorthBridge do not clear PME for Nb's
//               slots. Therefore, this causes hanging issue.
// [Solution]    Checking if this PEG card is Lan card. If it's, then
//               clear PME status.
// [Files]       NBPEI.c;
//
// 48    5/09/13 7:08a Ireneyang
// [TAG]         EIP118377
// [Category]    BugFix
// [Symptom]     System became resuming from S5 when system is resuming
//               from S4.
// [Description] Reproducing steps (UEFI OS)
//               1. Boot into USB key, run afudos.exe
//               2. Remove USB key.
//               3. Warm reset and don't press any key.
//               4. Screen will show "Reboot and select proper Boot
// device...
//                  No boot option"
//               5. Warm reset and press DEL to enter BIOS setup.
//               6. Change "Launch Video OpROM policy" to "UEFI only".
//               7. Save and reset.
//               8. Press DEL key to enter BIOS setup.
//               9. Change "Launch CSM" to "Disable"
//              10. Save and reset,enter OS(UEFI WIN8)
//              11. Open any file and do "Hibernate" to enter inot S4.
//              12. Power on, resuming back from S4 to desktop, the file
//                  would be disappeared. It looks like it doesn't resume
//                  back from S4 but S5.
// [RootCause]   It's out of variable type for S4 resume.
// [Solution]    The variable type should be
// "PreviousMemoryTypeInformation"
//               but MemoryTypeInformation.
// [Files]       NBPEI.c
//
// 47    4/01/13 11:48p Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Reduce boot time through PEG.
// [Files]        NB.mak; NBDxe.c; NBPEI.c; NBPPI.h; Sa.asl;
//                PcieComplex.c; GraphicsInit.c; PciExpressInit.c;
//
// 46    3/14/13 1:37a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Fix some PEG card with no VGA can't work normally under
//                SG mode.
// [Files]        NBPEI.c;
//
// 45    3/07/13 6:14a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Make some default SaPlatformPolicy items flexible.
//                Define some SaPlatformPolicy items into NB_SETUP_DATA
//                structure.
// [Files]        NbSetupData.h; GetSetupData.c; NBPEI.c;
//
// 44    3/07/13 3:53a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Add "Hot only" option for Memory Refresh 2x support to
//                meet Intel Spec.
// [Files]        NBPEI.c; NB.uni; NB.sd; NbSetupData.h; GetSetupData.c;
//
// 43    3/04/13 3:16a Ireneyang
// [TAG]          EIP115090
// [Category]  	  Improvement
// [Description]  Memory data hasn't been cleared after running MRC base
//                memory test.
// [Files]        NB.sdl; NBPEI.c;
//
// 41    2/09/13 10:23a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.1.0
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c;
//
// 40    1/28/13 5:54a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.0.
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c;
//                NB.sd; NB.uni; NBDxeBoard.c
//
// 39    1/21/13 3:55a Jeffch
// [TAG]          None
// [Severity]     Bug Fix
// [Description]  Fixed RMT memory type error issue for ULT.
// [Files]        NBPei.c;
//
// 38    1/15/13 4:07a Jeffch
// [TAG]          None
// [Severity]     Bug Fix
// [Description]  Changed MRC error report status for SA RC 0.90.
// [Files]        NBPei.c; MemoryInit.c;
//
// 37    1/14/13 6:06a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Create setup item for  SA RC 0.90.
// [Files]        NBPei.c; GetNbSetupData.c NB.sd; NB.uni;
//
// 36    1/10/13 5:57a Jeffch
//
// [TAG]          None
// [Severity]     Important
// [Description]  Create DDR PowerDown and idle counter for setup item.
// [Files]        NBPei.c; NB.sd; NB.uni; GetSetupData.c; NbSetupData.h
//
// 35    1/03/13 7:27a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Follow MRC error report status.
// [Files]        NBPei.c
// [TAG]          None
// [Severity]     Improvement
// [Description]  Use SG GPIO ULT by token.
// [Files]        NBPei.c
//
// 34    12/24/12 2:55a Jeffch
// [TAG]         None
// [Category]    Improvement
// [Description] added ULT SKU auto disable PEG.
// [Files]        NBPei.c; NBDxe.c; NbPlatform.h; NB.sd;
// [TAG]         None
// [Category]    Bug Fix
// [Description] Remove tRPab and fixed XTU build fail issue.
// [Files]        NBPei.c; NBDxe.c; NB.sd;
//
// 33    12/22/12 2:26a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Create setup item for  SA RC 0.81.
// [Files]        NBPei.c; GetNbSetupData.c NB.sd; NB.uni;
// [TAG]          None
// [Severity]    Bug Fix
// [Description]  Fxied XTU MRC Timing bug.
// [Files]        NBPei.c;
//
// 32    12/18/12 5:14a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 0.81.
// [Files]        NBDxe.c; NBPei.c
//
// 31    12/03/12 5:56a Jeffch
// [TAG]           None
// [Category]      Improvement
// [Description]   optimize DetectNonComplaint function.
// [Description]   NBPEI.c, NBPPI.h, NBDxe.c
// [TAG]           None
// [Category]      Improvement
// [Description]   Change for mxm SgDgpuPwrEnable->Active =
// ACTIVE_dGPU_PWR_EN.
// [Description]   NBPEI.c, NBPPI.h, NBDxe.c
//
// 30    11/28/12 9:52p Jeffch
// [TAG]         DetectNonComplaint
// [Category]    Improvement
// [Description] added peg DetectNonComplaint function.
//
// 29    11/20/12 2:41a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update SA RC 0.80.
// [Files]        NBDxe.c; NBPei.c
//
// 28    11/14/12 5:37a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update XTU4.x function
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; NB.sd;
// NB.uni
//
// 27    11/12/12 12:11a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Change name SMRAMC to R_SA_SMRAMC for build error.
// [Files]        NBPei.c;
//
// 26    11/07/12 6:19a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Support ULT one BIOS
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h
//
// 25    10/30/12 7:05a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update SA RC 0.72.
// [Files]        NBDxe.c; NBPei.c
//
// 2     10/22/12 6:38a Jeffch
//
// 24    10/18/12 11:04p Jeffch
// [TAG]          None
// [Severity]     Important
// [Description] Support Disable AB SEG.
// [Files]        NBPei.c;
//
// 23    10/16/12 9:38a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Remove invalid code.
// [Files]        NBPei.c;
//
// 22    10/14/12 5:17a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Follow SA RC 0.71.
// [Files]        NBPei.c, NBDxe.c; NBGeneric.c; NBCspLib.h; NBSetup.c;
// Nb.sd; GetSetupData.c
//
// 21    10/14/12 12:21a Jeffch
// [TAG]         None
// [Severity]    Important
// [Description] Update by XTU4.0.
// [Files]       NBPei.c, NBDxe.c, NBCspLib.h, NBGeneric.c
// [TAG]         None
// [Severity]    Important
// [Description] Follow Update by Mahobay.
// [Files]       NBPei.c, NBDxe.c;
//
// 20    9/28/12 4:12a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   BDAT function support.
// [Files]         NB.sd, NBDxe.c, NBPEI.c, SystemAgent.sdl,
// BdatAccessHandler.sdl
//
// 19    9/26/12 9:20a Yurenlai
// [TAG]           None
// [Category]      Update
// [Severity]      Important
// [Description]   Changed for Shark Bay SA Framework Reference Code Beta
// Version 0.7.0.
// [Files]         NBPEI.c
//
// [TAG]           EIP101495
// [Category]      Improvement
// [Severity]      Important
// [Description]   Initialize SSID of B0:D3:F0 and B0:D2:F0/F1.
// [Files]         NB.h, NB.sdl, NBPEI.c
//
// 18    9/12/12 6:15a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Add RxCEM Loop back setup item.
// [Files]         GetSetupData.c, NB.sd, NB.uni, NBPEI.c, NbSetupData.h,
// NBPEI.c,
//
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Modified for Switchable Graphics support.
// [Files]         NBPEI.c, SwitchableGraphicsInit.c, SystemAgent.sdl
//
// 17    8/24/12 8:15a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Corrected GTT reference define.
// [Files]         NBDxe.c, NBPEI.c
//
// 16    7/27/12 8:34a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] IGfx Fource Disable Support.
// [Files]       GetSetupData.c, NB.sdl, NB.sd, NB.uni, NbSetupData.h,
// NBDxe.c, NBPEI.c
//
// 15    7/03/12 11:25p Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Fix building error.
// [Files]       NBPEI.c
//
// 14    7/03/12 6:44a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Change for SystemAgent RefCode Revision: 0.6.0.
// [Files]       NBPEI.DXS, NB.sd, NBDxe.c, NBPEI.c
//
// 13    6/14/12 4:49a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Add Notify BeforeMrc and AfterMrc.
// [Description]   NBPEI.c, NBPPI.h, MemoryInit.
//
// 12    6/14/12 4:47a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Fixed S4 resume fail.
// [Description]   NBPEI.c
//
// 11    4/26/12 2:52a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Adjust Intel System Agent module the Setup item and
// Policy.
// [Description]   GetSetupData.c, NB.sdl, NB.sd, NB.uni, NBDxe.c,
// NBPEI.c,
//                 NBSetup.c, NBSetupReset.c, NbSetupData.h
//
// 10    4/26/12 2:39a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Fixed PeiRamBootSupport = 1 warm boot system is hang.
// [Description]   NBPEI.c, NBCspLib.h
//
// 9     4/26/12 2:35a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Support Locate MRC error Report.
// [Description]   NBPEI.c, MemoryInit.c
//
// 8     4/05/12 4:46a Yurenlai
//
// [TAG]         None
// [Category]    New Feature
// [Severity]    Normal
// [Description] Enabled GDXC feature.
// [Files]       NBPEI.c
//
// 7     4/05/12 2:43a Yurenlai
// [TAG]  		EIP87103
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Add routine RetrieveGdxcMemorySize to support GDXC
// feature and SA RC rev. 0.5.5.
// [Files]  		NBPEI.c
//
// 6     4/05/12 2:39a Yurenlai
// [TAG]  		EIP87103
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change for SystemAgent RefCode Revision: 0.5.5 .
// [Files]  		NBDxe.c, NBPEI.c, NBSMI.C, NBGeneric.c, NB.sd, NBSetup.c,
// GetSetupData.c, NbSetupData.h
//
// 5     3/23/12 3:32a Yurenlai
// Fixed the build error of Help Builder.
//
// 4     3/22/12 11:08p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Fixed MRC_DEBUG_PRINT = 0 for not send MRC debug message.
// [Files]       NBPEI.c, MemoryInit.sdl, MrcOemDebugPrint.h
//
// 3     3/08/12 10:30p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Support MRC debug message print information and RMT
// message.
// [Files]       NBPEI.c
//
// 2     2/23/12 6:45a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Adjusted North Bridge the policy configuration.
//
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBPEI.C
//
// Description: This file contains code for North Bridge initialization
//              in the PEI stage
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Efi.h>
#include <Pei.h>
#include <token.h>
#include <HOB.h>
#include <StatusCodes.h>
#include <AmiLib.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>

#include <ppi\PciCfg2.h>
#include <ppi\CpuIo.h>
#include <ppi\NBPPI.h>
#include <ppi\CspLibPpi.h>
#include <ppi\smbus.h>
#include <ppi\ReadOnlyVariable2.h>
#include <Setup.h>
#include <CpuHobs.h>

#include <Core\EM\ACPI\AcpiS3.h>

#include <Protocol\NBMemInfo.h>

#include <Core\GUID\MemoryTypeInformation.h>

// Produced PPIs
#include <ppi\BaseMemorytest.h>

#if SystemAgent_SUPPORT
#include <PchAccess.h>
#include <MemInfoHob.h>
#include <SaDataHob\SaDataHob.h>
#define _SA_COMMON_DEFINITIONS_H_
#include <Ppi\SaPlatformPolicy\SaPlatformPolicy.h>
#include <SampleCode\Ppi\PlatformMemorySize\PlatformMemorySize.h>
#include <SampleCode\Ppi\PlatformMemoryRange\PlatformMemoryRange.h>
#endif

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
#include <PPI\PerfTunePpi.h>
#endif
#endif

#if SB_STALL_PPI_SUPPORT
#include <Ppi\Stall.h>
#endif

#include <Ppi\Wdt\Wdt.h>

#ifdef SSA_FLAG
#define __EDKII_GLUE_PEIM_H__
#include "SsaCallbackPeim.h"
#include "MrcOem.h"
#endif // SSA_FLAG

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

VOID NBResetCpuOnly (               // Do CPU Only Reset
    IN EFI_PEI_SERVICES     **PeiServices
);

VOID ProgramNBSubId (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI      *PciCfg
);

EFI_STATUS BaseMemoryTest (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN struct _PEI_BASE_MEMORY_TEST_PPI *This,
    IN EFI_PHYSICAL_ADDRESS     BeginAddress,
    IN UINT64                   MemoryLength,
    IN PEI_MEMORY_TEST_OP       Operation,
    OUT EFI_PHYSICAL_ADDRESS    *ErrorAddress
);

EFI_STATUS
EFIAPI
ChooseRanges (
    IN EFI_PEI_SERVICES                     **PeiServices,
    IN PEI_PLATFORM_MEMORY_RANGE_PPI        *This,
    IN OUT PEI_MEMORY_RANGE_OPTION_ROM      *OptionRomMask,
    IN OUT PEI_MEMORY_RANGE_SMRAM           *SmramMask,
    IN OUT PEI_MEMORY_RANGE_GRAPHICS_MEMORY *GraphicsMemoryMask,
    IN OUT  PEI_MEMORY_RANGE_PCI_MEMORY     *PciMemoryMask
);

EFI_STATUS
EFIAPI
GetPlatformMemorySize (
    IN      EFI_PEI_SERVICES                       **PeiServices,
    IN      struct _PEI_PLATFORM_MEMORY_SIZE_PPI   *This,
    IN OUT  UINT64                                 *MemorySize
);

EFI_STATUS NBPeiBeforeMrcPei (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

EFI_STATUS NBPeiEndOfMrcPei (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

EFI_STATUS ProgramNBRegBeforeEndofPei (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

EFI_STATUS CreateCPUHob(
  IN EFI_PEI_SERVICES **PeiServices
);

VOID
GtOcInit (
  IN      EFI_PEI_SERVICES      **PeiServices,
  IN      NB_SETUP_DATA          *NbSetupData
);

EFI_STATUS
InstallSaPlatformPolicyPpi (
  IN  EFI_PEI_SERVICES  **PeiServices,
  IN  NB_SETUP_DATA        *NbSetupData
);

#ifdef SSA_FLAG
MrcStatus
AmiSsaCallbackPpi (
  EFI_PEI_SERVICES                 **PeiServices,
  struct _SSA_BIOS_CALLBACKS_PPI   *SsaBiosCallBacksPpi,
  MRC_OEM_STATUS_COMMAND           StatusCommand,
  VOID                             *CheckpointData
);
#endif // SSA_FLAG

EFI_STATUS
MemoryErrorRead (
  IN      EFI_PEI_SERVICES      **PeiServices,
  IN      PEI_MEMORY_ERROR_REPORT_PPI      *This,
  IN OUT  UINT32                MemErrData
);


//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)
EFI_GUID gAmiNbPegInfoGuid               = AMI_NB_PEG_INFO_GUID;
EFI_GUID gAmiPEINbInitPolicyGuid         = AMI_PEI_NBINIT_POLICY_PPI_GUID;
EFI_GUID gBaseMemoryTestGuid             = PEI_BASE_MEMORY_TEST_GUID;
EFI_GUID gEfiPeiEndOfPeiPhasePpiGuid     = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;
EFI_GUID gAmiNbInfoHobGuid               = AMI_NB_INFO_HOB_GUID;
EFI_GUID gMrcInfoHobGuid                 = AMI_MRC_INFO_HOB_GUID;
//EFI_GUID gEfiNBMemoryInfoGuid          = EFI_NB_MEMORY_INFO_GUID;
EFI_GUID gEfiNbMrcS3DataGuid             = EFI_NB_MRC_S3_DATA_GUID;
EFI_GUID gSetupGuid                      = SETUP_GUID;
EFI_GUID gAmiMemoryErrorReportPpiGuid    = AMI_MEMORY_ERROR_REPORT_PPI_GUID;
EFI_GUID gWdtPpiGuid                     = WDT_PPI_GUID;
#if SB_STALL_PPI_SUPPORT
EFI_GUID gStallPpiGuid                   = EFI_PEI_STALL_PPI_GUID;
#endif
#if SystemAgent_SUPPORT
EFI_GUID  gSaPlatformPolicyPpiGuid       = SA_PLATFORM_POLICY_PPI_GUID;
EFI_GUID  gMemRestoreDataGuid            = EFI_MEMORY_RESTORE_DATA_GUID;
EFI_GUID  gAmiNbPegGen3PresetSearchGuid   = AMI_NB_PEG_GEN3_PRESET_SEARCH_GUID;
EFI_GUID  gPlatformMemorySizeGuid        = PEI_PLATFORM_MEMORY_SIZE_PPI_GUID;
EFI_GUID  gPlatformMemoryRangeGuid       = PEI_PLATFORM_MEMORY_RANGE_PPI_GUID;
EFI_GUID  gEfiMemoryTypeInformationGuid  = EFI_MEMORY_TYPE_INFORMATION_GUID;
#endif
EFI_GUID  gEfiGlobalVariableGuid          = EFI_GLOBAL_VARIABLE;

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
static EFI_GUID gPerfTunePpiGuid = PERF_TUNE_PPI_GUID;
EFI_GUID gAmiDddtPreFlagHobGuid = AMI_DDDT_PRESENT_FLAG_HOB_GUID;
#endif
#endif

// PPI Definition(s)

// PPI that are installed
static AMI_PEI_NBINIT_POLICY_PPI gAMIPEINBInitPolicyPpi = {
    TRUE
};

static PEI_PLATFORM_MEMORY_SIZE_PPI mMemorySize = {
  GetPlatformMemorySize
};

static PEI_PLATFORM_MEMORY_RANGE_PPI mPlatformMemoryRange = {
  ChooseRanges
};


static PEI_BASE_MEMORY_TEST_PPI gBaseMemoryTest = {
    BaseMemoryTest
};

static EFI_PEI_NB_CPU_ONLY_RESET_PPI gNBCpuOnlyResetPpi = {
    NBResetCpuOnly
};


#ifdef SSA_FLAG
static SSA_BIOS_CALLBACKS_PPI gAmiSsaCallbackPpi = {
    0,
    AmiSsaCallbackPpi,
    NULL
};
#endif // SSA_FLAG
static PEI_MEMORY_ERROR_REPORT_PPI gPeiMemoryErrorReportPpi = {
    MemoryErrorRead
};


//  Include any additional PPI needed for memory detection in this
//  list and define the functions in this file

static EFI_PEI_PPI_DESCRIPTOR mPpiList[] = {
#ifdef SSA_FLAG
    { EFI_PEI_PPI_DESCRIPTOR_PPI,
      &gSsaBiosCallBacksPpiGuid,
      &gAmiSsaCallbackPpi},
#endif // SSA_FLAG
    { EFI_PEI_PPI_DESCRIPTOR_PPI,
      &gAmiMemoryErrorReportPpiGuid,
      &gPeiMemoryErrorReportPpi },

    { EFI_PEI_PPI_DESCRIPTOR_PPI, \
      &gPlatformMemorySizeGuid, \
      &mMemorySize },
    { EFI_PEI_PPI_DESCRIPTOR_PPI, \
     &gPlatformMemoryRangeGuid, \
     &mPlatformMemoryRange },
    { EFI_PEI_PPI_DESCRIPTOR_PPI, \
      &gBaseMemoryTestGuid, \
      &gBaseMemoryTest },
    { EFI_PEI_PPI_DESCRIPTOR_PPI, \
      &gAmiPeiNBCpuOnlyResetPpiGuid, \
      &gNBCpuOnlyResetPpi },
    { (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST), \
      &gAmiPEINbInitPolicyGuid, \
      &gAMIPEINBInitPolicyPpi }
};

// PPI that are notified

static EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK, \
      &gAmiPeiBeforeMrcGuid, NBPeiBeforeMrcPei },
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK, \
      &gAmiPeiEndOfMemDetectGuid, NBPeiEndOfMrcPei },
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gEfiPeiEndOfPeiPhasePpiGuid, ProgramNBRegBeforeEndofPei },
};

// External Declaration(s)

// Function Definition(s)

UINT32 NBPcieBridge[] =
{
  {(UINT32)NB_PCIE_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, PCI_VID)},
  {(UINT32)NB_PCIE_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN1, PCI_VID)},
  {(UINT32)NB_PCIE_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN2, PCI_VID)},
  {0xFFFFFFFF}
};
// << (EIP69780)

//(EIP96114)
// Type Definition(s)
typedef struct {
    UINT8    Bus;
    UINT8    Dev;
    UINT8    Fun;
    UINT16   PegBitOffset;
} DEVICES_AFTER_PCIIO;

DEVICES_AFTER_PCIIO gDevicesTable[] = {
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN2, B_SA_DEVEN_D1F2EN_MASK },
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN1, B_SA_DEVEN_D1F1EN_MASK },
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN,  B_SA_DEVEN_D1F0EN_MASK },
    { 0xFF,         0xFF,         0xFF,        0,                     },
};

UINTN gDevicesTableCount = sizeof(gDevicesTable) / sizeof(DEVICES_AFTER_PCIIO);
//(EIP96114)

#ifdef RC_PEG_0
DEVICES_AFTER_PCIIO gDisablePegDevicesTable[] = {
#if RC_PEG_0 == 0
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN,  NULL },
#endif
#if !(defined RC_PEG_1) || RC_PEG_1 == 0
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN1, NULL },
#endif
#if !(defined RC_PEG_2) || RC_PEG_2 == 0
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN2, NULL },
#endif
    { 0xFF,        0xFF,         0xFF,         NULL }
};

UINTN gDisablePegCount = sizeof(gDisablePegDevicesTable) / sizeof(DEVICES_AFTER_PCIIO);
#endif

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBPEI_Init
//
// Description: This function is the entry point for this PEI.
//              it must be ported to do NB specific programming needed
//              at power-on, both in wakeup path as well as power-on path.
//
// Input:       FfsHeader   Pointer to the FFS file header
//              PeiServices Pointer to the PEI services table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//
// Notes:       This function should initialize North Bridge before memory
//              detection.
//              Install AMI_PEI_NBINIT_POLICY_PPI to indicate that NB Init
//              PEIM is installed
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI NBPEI_Init (
    IN EFI_FFS_FILE_HEADER      *FfsHeader,
    IN EFI_PEI_SERVICES         **PeiServices )
{

    EFI_STATUS                  Status;
    EFI_PEI_PCI_CFG2_PPI         *PciCfg;
    EFI_PEI_CPU_IO_PPI          *CpuIo;
    NB_SETUP_DATA               *NbSetupData = NULL;
#if defined SIO_SUPPORT && SIO_SUPPORT == 1// For SIO off. Without this compiler fails
#if defined SIO_Smsc1007 && SIO_Smsc1007 == 1
    UINT8         GpioDataReg3;
#endif
#endif

    // Get pointer to the PCI config PPI
    PciCfg = (*PeiServices)->PciCfg;
    CpuIo = (*PeiServices)->CpuIo;

    PEI_PROGRESS_CODE (PeiServices, PEI_CAR_NB_INIT);

    //Create CPU HOB
    CreateCPUHob(PeiServices);

    //
    // Allocate buffer for setup data variable.
    //
    Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (NB_SETUP_DATA), &NbSetupData);
    ASSERT_PEI_ERROR (PeiServices, Status);
    (*PeiServices)->SetMem ((VOID*) NbSetupData, sizeof (NB_SETUP_DATA), 0);

    GetNbSetupData( PeiServices, NbSetupData, TRUE );

    // Disable IGFX for UpSever
#if defined NB_IGFX_FORCE_DISABLE_SUPPORT && NB_IGFX_FORCE_DISABLE_SUPPORT == 1
    if(NbSetupData->IGfxForceDisable == 1)
    {
         NbSetupData->InternalGraphics = 0; // disable IGFX
         NbSetupData->PrimaryDisplay   = 1; // PEG Only
    }
#endif // NB_IGFX_FORCE_DISABLE_SUPPORT

#if defined SMM_THUNK_IN_CSM && SMM_THUNK_IN_CSM == 0
    // Enable Global SMRAM
    SET_PCI8_NB(R_SA_SMRAMC, 8); // 0x88
#else
#if defined SMM_THUNK_NO_AB_SEG && SMM_THUNK_NO_AB_SEG == 1
    // Enable Global SMRAM
    SET_PCI8_NB(R_SA_SMRAMC, 8); // 0x88
#endif
#endif

    // Install the NB Init Policy PPI
    Status = (*PeiServices)->InstallPpi(PeiServices, &mPpiList[0]);
    ASSERT_PEI_ERROR (PeiServices, Status);

    // Set up necessary PPI notifications
    Status = (*PeiServices)->NotifyPpi( PeiServices, &mNotifyList[0] );
    ASSERT_PEI_ERROR ( PeiServices, Status );

    // Program SSID
    ProgramNBSubId( PeiServices, PciCfg );

    // Install SaPlatformPolicyPpi
    InstallSaPlatformPolicyPpi (PeiServices, NbSetupData);

#if defined SIO_SUPPORT && SIO_SUPPORT == 1// For SIO off. Without this compiler fails
#if defined SIO_Smsc1007 && SIO_Smsc1007 == 1
  // Set up PWM or GMBus(I2C) panel backlight inverter.
  // General Purpose I/O Data Register 3, this is not a config reg, so no need to enter config mode.
  // From CRB schematic BIOS Note: Disable both BKLTSEL lines before enabling one.
  GpioDataReg3 = READ_IO8(Smsc1007_PME_BASE_ADDRESS + 0x0E);
  GpioDataReg3 |= (BIT07 | BIT01);
  WRITE_IO8(Smsc1007_PME_BASE_ADDRESS + 0x0E, GpioDataReg3);

  // Program SIO to switch inverter
  if ((NbSetupData->IgdLcdBlc == 0) || (NbSetupData->IgdLcdBlc == 2)) {

    // PWM backlight control
    // Choose L_BKLTSEL0# via GPIO37 to enable PWM backlight control
    GpioDataReg3 &= ~BIT07;  // L_BKLTSEL0#
  } else {

    // GMBus backlight control(also known as I2C)
    // Choose L_BKLTSEL1# via GPIO31 to enable GMBus to support backlight control
    GpioDataReg3 &= ~BIT01;  // L_BKLTSEL1#
  }

  WRITE_IO8(Smsc1007_PME_BASE_ADDRESS + 0x0E, GpioDataReg3);
#endif
#endif

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBResetCpuOnly
//
// Description: This function issues a CPU only reset.
//
// Input:       PeiServices - Pointer to the PEI services table
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NBResetCpuOnly (               // Do CPU Only Reset
    IN EFI_PEI_SERVICES     **PeiServices )
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramNBSubId
//
// Description: This function programs NB PCI devices sub-vendor ID and
//              sub-system ID.
//
// Input:       PeiServices - Pointer to the PEI services table
//              PciCfg      - Pointer to the PCI Configuration PPI
//
// Output:      VOID
//
// Notes:       1. This routine only programs the PCI device in NB, hence, we
//                 have to check the bus/device/function numbers whether they
//                 are a NB PCI device or not.
//              2. This routine is invoked by PEI phase.(After PEI permantent
//                 memory be installed)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProgramNBSubId (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI      *PciCfg )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    AMI_PEI_NB_CUSTOM_PPI       *NBPeiOemPpi;
    UINTN                       i = 0;
    UINT8                       SsidReg = 0;
    UINT32                      PciSid = 0xffffffff;
    AMI_NB_PCI_SSID_TABLE_STRUCT DefaultSIdTbl[] = {NB_PCI_DEVICES_SSID_TABLE};
    AMI_NB_PCI_SSID_TABLE_STRUCT *SsidTblPtr = DefaultSIdTbl;

    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gAmiPeiNBCustomPpiGuid, \
                                        0, \
                                        NULL, \
                                        &NBPeiOemPpi );

    if (Status == EFI_SUCCESS) {
        if (NBPeiOemPpi->SsidTable != NULL)
            SsidTblPtr = NBPeiOemPpi->SsidTable;
    }

    while (SsidTblPtr[i].PciAddr != 0xffffffffffffffff) {
        if ((SsidTblPtr[i].PciAddr == NB_BUS_DEV_FUN) || \
            (SsidTblPtr[i].PciAddr == NB_IGD_BUS_DEV_FUN) || \
            (SsidTblPtr[i].PciAddr == NB_IGD_BUS_DEV_FUN1) || \
            (SsidTblPtr[i].PciAddr == NB_HDA_BUS_DEV_FUN) || \
            (SsidTblPtr[i].PciAddr == NB_PCIEBRNx16_BUS_DEV_FUN) || \
            (SsidTblPtr[i].PciAddr == NB_PCIEBRNx8_BUS_DEV_FUN) || \
            (SsidTblPtr[i].PciAddr == NB_PCIEBRNx4_BUS_DEV_FUN)) \
        {
            if (SsidTblPtr[i].Sid == 0xffffffff) {
                Status = PciCfg->Read( PeiServices,
                                       PciCfg,
                                       EfiPeiPciCfgWidthUint32,
                                       SsidTblPtr[i].PciAddr,
                                       &PciSid);
            } else {
                PciSid = SsidTblPtr[i].Sid;
            }

            SsidReg = PCI_SVID;

            if((SsidTblPtr[i].PciAddr == NB_PCIEBRNx16_BUS_DEV_FUN) || \
               (SsidTblPtr[i].PciAddr == NB_PCIEBRNx8_BUS_DEV_FUN) || \
               (SsidTblPtr[i].PciAddr == NB_PCIEBRNx4_BUS_DEV_FUN) || \
               (SsidTblPtr[i].PciAddr == NB_PCIEBRN_BUS_DEV6_FUN))
            {
              SsidReg = R_SA_PEG_SS_OFFSET;
            }

            Status = PciCfg->Write( PeiServices,
                                    PciCfg,
                                    EfiPeiPciCfgWidthUint32,
                                    SsidTblPtr[i].PciAddr | SsidReg,
                                    &PciSid);

        }

        i++;
    }


}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBPeiBeforeMrcPei
//
// Description: This function can be Call NB PEI before Mrc.
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NotifyDescriptor - Pointer to the descriptor for the
//                                 notification event.
//              InvokePpi        - Pointer to the PPI that was installed
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBPeiBeforeMrcPei (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_PEI_CPU_IO_PPI          *CpuIo;
    EFI_PEI_PCI_CFG2_PPI         *PciCfg;

    CpuIo = (*PeiServices)->CpuIo;
    PciCfg = (*PeiServices)->PciCfg;

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "NBPeiBeforeMrc Start.\n"));

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "NBPeiBeforeMrc end.\n"));

    return  Status;
}

//(EIP96114)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbPegDetectNonComplaint
//
// Description: This function is Detect peg NonComplaint devices.
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NB_SETUP_DATA    - NbSetupData - NB Setup data stored in NVRAM
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NbPegDetectNonComplaint (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN  NB_SETUP_DATA               *NbSetupData
)
{
//    UINT16  DetectCount;
//    UINT16  Count;
    UINT16  i;
    UINT8   PegBus;
    UINT8   PegDev;
    UINT8   PegFun;
    UINT16  PegBitMap = 0;
    EFI_STATUS  Status = EFI_SUCCESS;
    NB_PEG_INFO_HOB *NbPegInfoHob;
    BOOLEAN  CardDetect[sizeof(gDevicesTable) / sizeof(DEVICES_AFTER_PCIIO)] = {FALSE};

    Status = (*PeiServices)->CreateHob (PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof (NB_PEG_INFO_HOB), (VOID **) &NbPegInfoHob);
    if (EFI_ERROR (Status)) return ;

    NbPegInfoHob->Header.Name = gAmiNbPegInfoGuid;

    for ( i = 0; i < gDevicesTableCount; i++)
    {
        PegBus = gDevicesTable[i].Bus;
        PegDev = gDevicesTable[i].Dev;
        PegFun = gDevicesTable[i].Fun;
        NbPegInfoHob->PegDeOverride[PegFun] = NbSetupData->PegDeEmphasis[PegFun];

        if (READ_PCI32(PegBus, PegDev, PegFun, 0) == 0xffffffff) continue;

        WRITE_PCI32 (PegBus, PegDev, PegFun, PCI_PBUS, 0x00010100);
        WRITE_PCI16 (1, 0, 0, PCI_VID, 0);
        CountTime(4000, PM_BASE_ADDRESS); // 1ms
        if(READ_PCI8 (PegBus, PegDev, PegFun, R_SA_PEG_SLOTSTS_OFFSET) & BIT06) {
           if(READ_PCI16 (1, 0, 0, PCI_VID) != 0xffff) {
              WRITE_PCI32 (PegBus, PegDev, PegFun, PCI_PBUS, 0x00000000);
              CardDetect[i] = TRUE;
              continue;
           }
        }

        RW_PCI8(PegBus, PegDev, PegFun, 0xD0, 0x01, 0xff); // Gen 1
        CountTime(4000, PM_BASE_ADDRESS); // 1ms
        if(READ_PCI8 (PegBus, PegDev, PegFun, R_SA_PEG_SLOTSTS_OFFSET) & BIT06) {
           if(READ_PCI16 (1, 0, 0, PCI_VID) != 0xffff) {
              NbPegInfoHob->PegDeOverride[PegFun] = 0; // Set 6DB.
              CardDetect[i] = TRUE;
           }
        }

        WRITE_PCI32 (PegBus, PegDev, PegFun, PCI_PBUS, 0x00000000);
     }
     if (NbSetupData->AlwaysEnablePeg != 1) {

        for ( i = 0; i < gDevicesTableCount; i++) {

           PegBus = gDevicesTable[i].Bus;
           PegDev = gDevicesTable[i].Dev;
           PegFun = gDevicesTable[i].Fun;

           if (READ_PCI32(PegBus, PegDev, PegFun, 0) == 0xffffffff) continue;

           if (CardDetect[i]) {
               continue;
           } else {

               // if devices insert D1 F1 or F2, do not disable F0.
               if(PegFun == 0 && (CardDetect[0] || CardDetect[1])) break;
               PegBitMap |= gDevicesTable[i].PegBitOffset;
               SET_MEM8 (NB_PCIE_CFG_ADDRESS(PegBus, PegDev, PegFun, R_SA_PEG_LCTL_OFFSET), BIT4);
               SET_MEM8 (NB_PCIE_CFG_ADDRESS(PegBus, PegDev, PegFun, R_SA_PEG_DEBUP2_OFFSET), BIT0);
           }
        }

        // Disable Peg
        RESET_PCI16_NB(R_SA_DEVEN, PegBitMap); // 0x54
     }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbClearPegCtrlRegVgaEnable
//
// Description: This function is Clear PEG 0x3E bit3 for 3D card.
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NB_SETUP_DATA    - NbSetupData - NB Setup data stored in NVRAM
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NbClearPegCtrlRegVgaEnable (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN  NB_SETUP_DATA               *NbSetupData
)
{
    UINT16  i;
    UINT8   PegBus;
    UINT8   PegDev;
    UINT8   PegFun;

    for ( i = 0; i < gDevicesTableCount; i++)
    {
        PegBus = gDevicesTable[i].Bus;
        PegDev = gDevicesTable[i].Dev;
        PegFun = gDevicesTable[i].Fun;
        if (READ_PCI32(PegBus, PegDev, PegFun, 0) == 0xffffffff) continue;
        if ((READ_PCI8 (PegBus, PegDev, PegFun, R_SA_PEG_SLOTSTS_OFFSET) & BIT06) == 0) continue; // 0xBA

        WRITE_PCI32 (PegBus, PegDev, PegFun, PCI_PBUS, 0x00010100);
        WRITE_PCI16 (1, 0, 0, PCI_VID, 0);

        // Clear Peg VgaEnable
        RESET_PCI8(PegBus, PegDev, PegFun, PCI_BRIDGE_CNTL, BIT03);
        WRITE_PCI32 (PegBus, PegDev, PegFun, PCI_PBUS, 0x00000000);
    }
}
//(EIP73801)
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBPeiEndOfMrcPei
//
// Description: This function can be Call NB PEI after Mrc.
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NotifyDescriptor - Pointer to the descriptor for the
//                                 notification event.
//              InvokePpi        - Pointer to the PPI that was installed
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBPeiEndOfMrcPei (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_PEI_CPU_IO_PPI          *CpuIo;
    EFI_PEI_PCI_CFG2_PPI         *PciCfg;
    NB_SETUP_DATA               *NbSetupData = NULL;
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
    WDT_PPI                     *WdtPpi = NULL;
#endif
    EFI_BOOT_MODE               BootMode;                           // [ EIP161790 ]


    CpuIo = (*PeiServices)->CpuIo;
    PciCfg = (*PeiServices)->PciCfg;

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "NBPeiAfterMrc Start.\n"));

    //
    // Allocate buffer for setup data variable.
    //
    Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (NB_SETUP_DATA), &NbSetupData);
    ASSERT_PEI_ERROR (PeiServices, Status);
    (*PeiServices)->SetMem ((VOID*) NbSetupData, sizeof (NB_SETUP_DATA), 0);

    GetNbSetupData( PeiServices, NbSetupData, TRUE );


    // Set DRAM Initialization Bit.
    //if ((READ_PCI8_SB(SB_REG_GEN_PMCON_2) & BIT07) == 0)          // [ EIP161790 ]
    //{
    //    SET_PCI8_SB(SB_REG_GEN_PMCON_2, BIT07); // 0xA2
    //}
    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if ((!EFI_ERROR (Status)) && (BootMode == BOOT_ON_S3_RESUME))
    {
        if ((READ_PCI8_SB(SB_REG_GEN_PMCON_2) & BIT07) == 0)
        {
            SET_PCI8_SB(SB_REG_GEN_PMCON_2, BIT07); // 0xA2
        }
    }

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
    //
    // Locate WDT PPI for access to Wdt->Disable()
    //
    Status = (*PeiServices)->LocatePpi (
                      PeiServices,
                      &gWdtPpiGuid,
                      0,
                      NULL,
                      &WdtPpi
                      );
    if (!EFI_ERROR (Status)) {
        WdtPpi->Disable();
    }
#endif

//(EIP96114)

#if (defined RC_PEG_0) && RC_PEG_0 == 1
    if (NbSetupData->DetectNonComplaint && NbSetupData->AlwaysEnablePeg != 2)
    {
        // Peg Detect NonComplaint devices.
        NbPegDetectNonComplaint(PeiServices, NbSetupData);
    }
#endif

    // if SG and have pGPU
    if (READ_PCI32(0, 2, 0, 0) != 0xffffffff && NbSetupData->PrimaryDisplay == 4) {
       // Clear PEG 0x3E bit3 for SG mode.
       NbClearPegCtrlRegVgaEnable(PeiServices, NbSetupData);
    }

    PEI_TRACE((TRACE_ALWAYS, PeiServices, "NBPeiAfterMrc end.\n"));

    return  Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ProgramNBRegBeforeEndofPei
//
// Description: This function can be used to program any NB regisater before
//              end of PEI phase.
//
// Input:       PeiServices      - Pointer to the PEI services table
//              NotifyDescriptor - Pointer to the descriptor for the
//                                 notification event.
//              InvokePpi        - Pointer to the PPI that was installed
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ProgramNBRegBeforeEndofPei (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_PEI_CPU_IO_PPI          *CpuIo;
    EFI_PEI_PCI_CFG2_PPI        *PciCfg;
    EFI_BOOT_MODE               BootMode;
    UINTN                       PegAddress;
    UINT8                       CapPtr = 0;
    UINT8                       i = 0;
    UINT8                       PrimaryBus, SecondaryBus;
    CpuIo = (*PeiServices)->CpuIo;
    PciCfg = (*PeiServices)->PciCfg;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);

    if (BootMode == BOOT_ON_S3_RESUME) {
        // Porting if needed.

        for (i = 0; NBPcieBridge[i] != 0xFFFFFFFF; i++)
        {
            if (READ_MEM32(NBPcieBridge[i]) == 0xFFFFFFFF) continue;
            if (!(READ_MEM8(NBPcieBridge[i] + R_SA_PEG_SLOTSTS_OFFSET) & BIT06)) continue;

            PrimaryBus = READ_MEM8 (NBPcieBridge[i] + PCI_PBUS + 1);
            SecondaryBus = READ_MEM8 (NBPcieBridge[i] + PCI_PBUS + 2);

            for (; PrimaryBus <= SecondaryBus; PrimaryBus++) {
              PegAddress = NB_PCIE_CFG_ADDRESS(PrimaryBus, 0, 0, 0);

              // Network Card.
              if (READ_MEM8(PegAddress + 0x0B) == 0x02) {
                 // Find Cap ID 0x01
                 CapPtr = NbFindCapPtr(PegAddress, 0x01);
                 if(CapPtr != 0) {
                    // Clear PME status
                    SET_MEM16((PegAddress + CapPtr + 0x04), BIT15);
                 }
              }
            }

            // Clear root port PME status
            SET_MEM8((NBPcieBridge[i] + 0xC2), BIT01);
        }

    }

    return  EFI_SUCCESS;
}

//----------------------------------------------------------------------------
// BaseMemoryTest
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BaseMemoryTest
//
// Description: This function performs the base memory test.
//
// Input:       PeiServices  - Pointer to the PEI services table
//              This         - Pointer to the Base Memory Test PPI
//              BeginAddress - The begin address for test.
//              MemoryLength - The length in byte for test.
//              Operation    - The memort test operated policy.
//              ErrorAddress - The error address when test is failed.
//
// Output:      EFI_STATUS
//              EFI_DEVICE_ERROR - Tge base memory test is failure.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS BaseMemoryTest (
    IN  EFI_PEI_SERVICES            **PeiServices,
    IN  PEI_BASE_MEMORY_TEST_PPI    *This,
    IN  EFI_PHYSICAL_ADDRESS        BeginAddress,
    IN  UINT64                      MemoryLength,
    IN  PEI_MEMORY_TEST_OP          Operation,
    OUT EFI_PHYSICAL_ADDRESS        *ErrorAddress )
{

#if defined PEI_MRC_BASE_MEMORY_TEST_ENABLE && PEI_MRC_BASE_MEMORY_TEST_ENABLE == 1
  UINT32                                 TestPattern;
  UINT32                                 TestMask;
  UINT32                                 SpanSize;
  EFI_PHYSICAL_ADDRESS                   TempAddress;

#if defined PeiRamBootSupport && PeiRamBootSupport == 1
 if(!CheckPeiFvCopyToRam(PeiServices)) return EFI_SUCCESS;
#endif

  (*PeiServices)->ReportStatusCode (
                                   PeiServices,
                                   EFI_PROGRESS_CODE,
                                   EFI_COMPUTING_UNIT_MEMORY + EFI_CU_MEMORY_PC_TEST,
                                   0,
                                   NULL,
                                   NULL
                                   );

  TestPattern = 0x5A5A5A5A;
  TestMask = 0;
  SpanSize = 0;

  //
  // Make sure we don't try and test anything above the max physical address range
  //
  ASSERT_PEI_ERROR (PeiServices, BeginAddress + MemoryLength < 0xFFFFFFFFFFFFFFFF);

  switch (Operation) {
  case Extensive:
    SpanSize = 0x4;
    break;
  case Sparse:
  case Quick:
    SpanSize = 0x40000;
    break;
  case Ignore:
    return EFI_SUCCESS;
  }

  //
  // Write the test pattern into memory range
  //
  TempAddress = BeginAddress;
  while (TempAddress < BeginAddress + MemoryLength) {
    (*(UINT32*)(UINTN)TempAddress) = TestPattern;
    TempAddress += SpanSize;
  }

  //
  // Read pattern from memory and compare it
  //
  TempAddress = BeginAddress;
  while (TempAddress < BeginAddress + MemoryLength) {
    if ((*(UINT32*)(UINTN)TempAddress) != TestPattern) {
      *ErrorAddress = TempAddress;
      (*PeiServices)->ReportStatusCode (
                                       PeiServices,
                                       EFI_ERROR_CODE + EFI_ERROR_UNRECOVERED,
                                       EFI_COMPUTING_UNIT_MEMORY + EFI_CU_MEMORY_EC_UNCORRECTABLE,
                                       0,
                                       NULL,
                                       NULL
                                       );
      return EFI_DEVICE_ERROR;
    } else {
    (*(UINT32*)(UINTN)TempAddress)  = 0;
    }
    TempAddress += SpanSize;
  }
#endif

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ChooseRanges
//
// Description: Find out which memory ranges to reserve on this platform
//
// Input:   PeiServices        - Pointer to the PEI services table.
//          This               - Pointer to the Pei platform memory range ppi.
//          OptionRomMask      - The reserve for option ROM usage.
//          SmramMask          - The reserve for smram usage.
//          GraphicsMemoryMask - The reserve for graphics memory usage.
//          PciMemoryMask      - The reserve for Pei Memory usage.
//
// Output:
//          EFI_STATUS         - EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ChooseRanges (
  IN    EFI_PEI_SERVICES                      **PeiServices,
  IN    PEI_PLATFORM_MEMORY_RANGE_PPI         *This,
  IN OUT  PEI_MEMORY_RANGE_OPTION_ROM         *OptionRomMask,
  IN OUT  PEI_MEMORY_RANGE_SMRAM              *SmramMask,
  IN OUT  PEI_MEMORY_RANGE_GRAPHICS_MEMORY    *GraphicsMemoryMask,
  IN OUT  PEI_MEMORY_RANGE_PCI_MEMORY         *PciMemoryMask
  )
{
  UINT16                       GraphicsControlRegister;
  UINT32                       IgdSize;
  UINT32                       GttSize;
  EFI_STATUS                   Status;
  SA_PLATFORM_POLICY_PPI       *SaPlatformPolicyPpi;
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
  VOID                        *FirstHob;
  DDDT_PRESENT_FLAG_HOB       *DddtPreFlagHob;
  UINT8    NumOcBins = (UINT8)(ReadMsr(0x194) >> 17) & 0x7;
  Status = (*PeiServices)->GetHobList(PeiServices, &FirstHob);
  ASSERT_PEI_ERROR(PeiServices, Status);

  // Get XTU devices Present HOB
  DddtPreFlagHob = (DDDT_PRESENT_FLAG_HOB*) FirstHob;
  while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &DddtPreFlagHob))) {
      if (guidcmp(&((EFI_HOB_GUID_TYPE*)DddtPreFlagHob)->Name, &gAmiDddtPreFlagHobGuid) == 0) {
              break;
      }
  }

  // default XTU graphics Present is disable
  DddtPreFlagHob->PresentFlag[BIOS_GRAPHICS_TURBO_RATIO_LIMIT_IMPLEMENTATION] = 0;
  DddtPreFlagHob->PresentFlag[BIOS_GRAPHICS_CORE_VOLTAGE_IMPLEMENTATION] = 0;

  //If cpu is lock version then clear runtime turbo DDD table flag.
  if(NumOcBins == 0)
      DddtPreFlagHob->PresentFlag[BIOS_RUNTIME_TURBO_OVERRIDE_IMPLEMENTATION] = 0;
#endif
#endif

  //
  // Get platform policy settings through the SaPlatformPolicy PPI
  //
  Status = (*PeiServices)->LocatePpi (
                            PeiServices,
                            &gSaPlatformPolicyPpiGuid,
                            0,
                            NULL,
                            &SaPlatformPolicyPpi
                            );
  if (EFI_ERROR (Status))SaPlatformPolicyPpi->GtConfig->InternalGraphics = 2;
  //
  // Choose regions to reserve for Option ROM usage.
  //
  *OptionRomMask = PEI_MR_OPTION_ROM_NONE;

  //
  // Choose regions to reserve for SMM usage.
  // Each block is 128KB which is defined in PlatformRange PPI.
  // Needs to convert the value of TSEG_SIZE from bytes to blocks.
  //
  *SmramMask = (TSEG_SIZE >> 17) | PEI_MR_SMRAM_CACHEABLE_MASK |
#if defined SMM_THUNK_IN_CSM && SMM_THUNK_IN_CSM == 0
                   PEI_MR_SMRAM_ABSEG_MASK |
#else
#if defined SMM_THUNK_NO_AB_SEG && SMM_THUNK_NO_AB_SEG == 1
                   PEI_MR_SMRAM_ABSEG_MASK |
#endif
#endif
                   PEI_MR_SMRAM_TSEG_MASK;

  //
  // Choose regions to reserve for Graphics Memory usage.
  //
  *GraphicsMemoryMask = PEI_MR_GRAPHICS_MEMORY_NONE;

  GraphicsControlRegister = READ_PCI16_NB (R_SA_GGC);
  if (((GraphicsControlRegister & B_SA_GGC_IVD_MASK) == 0) || (SaPlatformPolicyPpi->GtConfig->InternalGraphics == 1)) {
    //
    // IGD is enabled, fill the IGD and GTT stolen memory sizes.
    //
    IgdSize = (GraphicsControlRegister & B_SA_GGC_GMS_MASK) >> N_SA_GGC_GMS_OFFSET;

    //
    // Add a w/a to handle 1G Stolen Memory - As per SNB ConfigDB definition,
    // Max No of bits to support this encoding is '5' 0/0/0/GGC[7:3] which can
    // hold a value of '1Fh'.
    // For 1G, suggested encoding is '11h'. Set the GraphicsMemoryMask as '2048'
    // to reserve 1G stolen memory.
    //
    // *GraphicsMemoryMask = IgdSize * PEI_MR_GRAPHICS_MEMORY_32M_NOCACHE;
    // *GraphicsMemoryMask = 32 * 64
    // *GraphicsMemoryMask = 2048

    if (IgdSize == 0x11) {
        IgdSize = 0x20;
    }

    *GraphicsMemoryMask = IgdSize * PEI_MR_GRAPHICS_MEMORY_32M_NOCACHE;

    //
    // Add GTT memory to reserved graphics memory
    //
    GttSize = (GraphicsControlRegister & B_SA_GGC_GGMS_MASK) >> N_SA_GGC_GGMS_OFFSET;

    switch (GttSize) {
    case 1:
      *GraphicsMemoryMask += PEI_MR_GRAPHICS_MEMORY_1M_NOCACHE;
      break;

    case 2:
      *GraphicsMemoryMask += PEI_MR_GRAPHICS_MEMORY_2M_NOCACHE;
      break;
    }

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
  // if IGD is enabled ,XTU graphics Present is enable
  DddtPreFlagHob->PresentFlag[BIOS_GRAPHICS_TURBO_RATIO_LIMIT_IMPLEMENTATION] = 1;
  DddtPreFlagHob->PresentFlag[BIOS_GRAPHICS_CORE_VOLTAGE_IMPLEMENTATION] = 1;
#endif
#endif
  }

  *PciMemoryMask = 0;

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RetrieveGdxcMemorySize
//
// Description: Determine the memory size desired by GDXC
//
// Input:   PeiServices        - Pointer to the PEI services table.
//          MotSize            - Gdxc Mot memory size to return.
//          GdxcSize           - Gdxc Required memory size to return.
//
// Output:
//          VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
RetrieveGdxcMemorySize (
  IN EFI_PEI_SERVICES **PeiServices,
  IN OUT UINT64 *MotSize,
  IN OUT UINT64 *GdxcSize)
{
  UINT32          MchBar;
  UINT32          GdxcBar;
  UINT32          TempMotSize;
  UINT32          TempOclaSize;

  //
  // Get MchBAR
  //
  MchBar = MmPci32(0, 0, 0, R_SA_MCHBAR) & B_SA_MCHBAR_MCHBAR_MASK;
  //
  // Get GdxcBar
  //
  GdxcBar = MmioRead32(MchBar+NCDECS_CR_GDXCBAR_NCU_REG);
  GdxcBar &= NCDECS_CR_GDXCBAR_NCU_MAX;
  //
  // Determine Gdxc size: Includes MOT\PSMI\IOT (OCLA)
  //
  TempMotSize = MmioRead32(GdxcBar+0x18);
  *GdxcSize = (((TempMotSize & 0xFFFF0000) >> 16) - (TempMotSize & 0x0000FFFF) + 1) << 23;
  *MotSize = *GdxcSize;

  TempOclaSize = MmioRead32(GdxcBar+0x28);
  *GdxcSize += (((TempOclaSize & 0xFFFF0000) >> 16) - (TempOclaSize & 0x0000FFFF)) << 23;

  // Add 16MB if some allocated to MOT and/or IOT
  if (*GdxcSize != 0)
    *GdxcSize += (16 << 20);
}

EFI_MEMORY_TYPE_INFORMATION mDefaultMemoryTypeInformation[] = {
  { EfiACPIReclaimMemory,   0x5 },
  { EfiACPIMemoryNVS,       0x280 },
  { EfiReservedMemoryType,  0x500},
  { EfiRuntimeServicesData, 0x2A},
#ifdef EFI_DEBUG
  { EfiRuntimeServicesCode, 0x80 },
  { EfiBootServicesCode,    0x1000},
#else
  { EfiRuntimeServicesCode, 0x3A},
  { EfiBootServicesCode,    0x1000},
#endif
  { EfiMaxMemoryType,       0 }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetPlatformMemorySize
//
// Description: Get the platform for the minimum memory size
//
// Input:   PeiServices        - Pointer to the PEI services table.
//          This               - Pointer to the Pei platform memory range ppi.
//          MemorySize         - Platform for the minimum memory size.
//
// Output:
//          EFI_STATUS         - Status
//          EFI_ERROR          - Create hob fail
//          EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetPlatformMemorySize (
  IN    EFI_PEI_SERVICES             **PeiServices,
  IN    PEI_PLATFORM_MEMORY_SIZE_PPI *This,
  IN OUT  UINT64                     *MemorySize
  )
{
  EFI_STATUS                            Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI       *Variable;
  UINTN                                 DataSize;
  EFI_MEMORY_TYPE_INFORMATION           MemoryData [EfiMaxMemoryType + 1];
  UINTN                                 Index;
  EFI_BOOT_MODE                         BootMode;
  EFI_HOB_GUID_TYPE                     *Hob;
//  UINT64 GdxcRequiredMemSize;
//  UINT64 GdxcMotMemSize;

 // RetrieveGdxcMemorySize(PeiServices, &GdxcMotMemSize, &GdxcRequiredMemSize);

  // Accumulate maximum amount of memory needed
 // *MemorySize = (READ_PCI32_NB (R_SA_TSEGMB) & B_SA_TSEGMB_TSEGMB_MASK) - 0x1000000;
 // *MemorySize -= GdxcRequiredMemSize;

  *MemorySize = PEI_MIN_MEMORY_SIZE;

  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gEfiPeiReadOnlyVariable2PpiGuid,
                             0,
                             NULL,
                             &Variable
                             );
  ASSERT_PEI_ERROR (PeiServices, Status);

  Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
  ASSERT_PEI_ERROR (PeiServices, Status);

  DataSize = sizeof (MemoryData);

  Status = Variable->GetVariable (
                       Variable,
                       (BootMode == BOOT_ON_S4_RESUME)
                       ? L"PreviousMemoryTypeInformation"
                       : EFI_MEMORY_TYPE_INFORMATION_VARIABLE_NAME,
                       &gEfiMemoryTypeInformationGuid,
                       NULL,
                       &DataSize,
                       &MemoryData
                       );

  if (EFI_ERROR (Status) || ( BootMode == BOOT_ON_FLASH_UPDATE )) {
    if ( BootMode == BOOT_IN_RECOVERY_MODE ) {
      return EFI_SUCCESS;
    }

    // Use default value to avoid memory fragment. OS boot/installation fails
    // if there is not enough continuous memory available
    DataSize = sizeof (mDefaultMemoryTypeInformation);
        (*PeiServices)->CopyMem (MemoryData, mDefaultMemoryTypeInformation, DataSize);
  }

  for (Index = 0; Index < DataSize / sizeof (EFI_MEMORY_TYPE_INFORMATION); Index++) {
        *MemorySize += MemoryData[Index].NumberOfPages * EFI_PAGE_SIZE;
  }

  // Build the GUID'd HOB for DXE
  Status = (*PeiServices)->CreateHob (
                             PeiServices,
                             EFI_HOB_TYPE_GUID_EXTENSION,
                             (UINT16) (sizeof (EFI_HOB_GUID_TYPE) + DataSize),
                             &Hob
                             );
  if (EFI_ERROR (Status))return Status;

  ((EFI_HOB_GUID_TYPE *)(Hob))->Name = gEfiMemoryTypeInformationGuid;

  Hob++;

  // Copy memory data to Hob
  (*PeiServices)->CopyMem (Hob, MemoryData, DataSize);

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CreateCPUHob
//
// Description: Create Cpu Hob and initialize it.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//
// Output:
//      EFI_STATUS          - EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CreateCPUHob(
  IN EFI_PEI_SERVICES **PeiServices
)
{
    EFI_HOB_CPU                 *pCpu = NULL;
    EFI_STATUS                  Status;

    Status = (*PeiServices)->CreateHob( PeiServices, \
                                        EFI_HOB_TYPE_CPU, \
                                        sizeof(EFI_HOB_CPU), \
                                        &pCpu );
    if (Status == EFI_SUCCESS) {
        pCpu->SizeOfMemorySpace = 36;
        pCpu->SizeOfIoSpace = 16;
        MemSet(pCpu->Reserved, 6, 0);
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: DisablePegDevices
//
// Description: Check Disable Peg Devices.
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DisablePegDevices()
{
    UINT16              PegDisFun;
    UINT16              i;
#ifdef RC_PEG_0
   for ( i = 0; gDisablePegDevicesTable[i].Bus != 0xff; i++)
   {
     UINTN       PegAddress;
     UINT8       PegBus;
     UINT8       PegDev;
     UINT8       PegFun;

     PegBus = gDisablePegDevicesTable[i].Bus;
     PegDev = gDisablePegDevicesTable[i].Dev;
     PegFun = gDisablePegDevicesTable[i].Fun;

     PegAddress = NB_PCIE_CFG_ADDRESS(PegBus, PegDev, PegFun, 0);

     if (READ_MEM32(PegAddress) == 0xFFFFFFFF) continue;

     // Disable Link
//     CapPtr = NbFindCapPtr(PegAddress, 0x10);
//     SET_MEM8((PegAddress + CapPtr + 0x10), BIT04);
     SET_MEM8 ((PegAddress + R_SA_PEG_LCTL_OFFSET), BIT4);
     SET_MEM8 ((PegAddress + R_SA_PEG_DEBUP2_OFFSET), BIT0);
     SET_MEM32 ((PegAddress + R_SA_PEG_PEGCOMLCGCTRL_OFFSET), BIT30);
   }

    PegDisFun = 0
#if RC_PEG_0 == 0
             | B_SA_DEVEN_D1F0EN_MASK
#endif
#if !(defined RC_PEG_1) || RC_PEG_1 == 0
             | B_SA_DEVEN_D1F1EN_MASK
#endif
#if !(defined RC_PEG_2) || RC_PEG_2 == 0
             | B_SA_DEVEN_D1F2EN_MASK
#endif
            ;

   // Disable PEG
   if(PegDisFun != 0)
      RESET_PCI16_NB(R_SA_DEVEN, PegDisFun); // 0x54

#endif //#ifdef RC_PEG_0
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InstallSaPlatformPolicyPpi
//
// Description: InstallSaPlatformPolicyPpi: This Function installs the SNB SA POLICY PPI
//
// Parameters:
//  PeiServices - General purpose services available to every PEIM
//  NbSetupData   - NB Setup data stored in NVRAM
//
// Returns:
//     Status: Return Status
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InstallSaPlatformPolicyPpi (
  IN  EFI_PEI_SERVICES  **PeiServices,
  IN  NB_SETUP_DATA      *NbSetupData
)
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices = NULL;
  UINTN                           VariableSize;
  VOID                            *MrcS3ResumeData;
  VOID                            *PegGen3Data;
  EFI_PEI_CPU_IO_PPI              *CpuIo;
  EFI_PEI_PPI_DESCRIPTOR          *SaPlatformPolicyPpiDesc;
  SA_PLATFORM_POLICY_PPI          *SaPlatformPolicyPpi;
  SA_PLATFORM_DATA                *PlatformData;
  GT_CONFIGURATION                *GtConfig;
  MEMORY_CONFIGURATION            *MemConfig;
  PCIE_CONFIGURATION              *PcieConfig;
  OVERCLOCKING_CONFIGURATION      *OcConfig;
  PEG_GPIO_DATA                   *PegGpioData;
  SA_GPIO_INFO                    *SaPegReset;
#if defined SwitchableGraphics_SUPPORT && SwitchableGraphics_SUPPORT == 1
  SG_GPIO_DATA                    *SgGpioData;
  SA_GPIO_INFO                    *SgDgpuPwrOK;
  SA_GPIO_INFO                    *SgDgpuHoldRst;
  SA_GPIO_INFO                    *SgDgpuPwrEnable;
  SA_GPIO_INFO                    *SgDgpuPrsnt;
#endif
  UINTN                           MemoryCeiling = 0;
  UINT16                          LpcDeviceId;
  UINT16                          McDeviceId;
  UINTN                           i = 0;
  UINT16                          CapPtr = 0;

  CpuIo = (*PeiServices)->CpuIo;

  // Locate Variable Ppi
  Status = (*PeiServices)->LocatePpi (PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &VariableServices);
  ASSERT_PEI_ERROR (PeiServices, Status);

  // Allocate descriptor and PPI structures
  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (SA_PLATFORM_POLICY_PPI), &SaPlatformPolicyPpi);
  ASSERT_PEI_ERROR (PeiServices, Status);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (EFI_PEI_PPI_DESCRIPTOR), &SaPlatformPolicyPpiDesc);
  ASSERT_PEI_ERROR (PeiServices, Status);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (SA_PLATFORM_DATA), &PlatformData);
  ASSERT_PEI_ERROR (PeiServices, Status);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (GT_CONFIGURATION), &GtConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (MEMORY_CONFIGURATION), &MemConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PCIE_CONFIGURATION), &PcieConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (PEG_GPIO_DATA), &PegGpioData);
  ASSERT_PEI_ERROR (PeiServices, Status);

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (OVERCLOCKING_CONFIGURATION), &OcConfig);
  ASSERT_PEI_ERROR (PeiServices, Status);

#if defined SwitchableGraphics_SUPPORT && SwitchableGraphics_SUPPORT == 1
  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (SG_GPIO_DATA), &SgGpioData);
  ASSERT_PEI_ERROR (PeiServices, Status);
#endif

  // Set Default to Variable not found
  (*PeiServices)->SetMem ((VOID*) PlatformData, sizeof (SA_PLATFORM_DATA), 0);
  (*PeiServices)->SetMem ((VOID*) SaPlatformPolicyPpiDesc, sizeof (EFI_PEI_PPI_DESCRIPTOR), 0);
  (*PeiServices)->SetMem ((VOID*) GtConfig,     sizeof (GT_CONFIGURATION), 0);
  (*PeiServices)->SetMem ((VOID*) MemConfig,    sizeof (MEMORY_CONFIGURATION), 0);
  (*PeiServices)->SetMem ((VOID*) PcieConfig,   sizeof (PCIE_CONFIGURATION), 0);
  (*PeiServices)->SetMem ((VOID*) SaPlatformPolicyPpi, sizeof (SA_PLATFORM_POLICY_PPI), 0);
  (*PeiServices)->SetMem ((VOID*) PegGpioData,  sizeof (PEG_GPIO_DATA), 0);
  (*PeiServices)->SetMem ((VOID*) OcConfig,     sizeof (OVERCLOCKING_CONFIGURATION), 0);
#if defined SwitchableGraphics_SUPPORT && SwitchableGraphics_SUPPORT == 1
  (*PeiServices)->SetMem ((VOID*) SgGpioData,   sizeof (SG_GPIO_DATA), 0);
#endif

  SaPlatformPolicyPpi->PlatformData = PlatformData;
  SaPlatformPolicyPpi->GtConfig     = GtConfig;
  SaPlatformPolicyPpi->MemConfig    = MemConfig;
  SaPlatformPolicyPpi->PcieConfig   = PcieConfig;
  SaPlatformPolicyPpi->PcieConfig->PegGpioData = PegGpioData;
  SaPlatformPolicyPpi->OcConfig     = OcConfig;
#if defined SwitchableGraphics_SUPPORT && SwitchableGraphics_SUPPORT == 1
  SaPlatformPolicyPpi->SgGpioData   = SgGpioData;
#endif
  SaPlatformPolicyPpi->S3DataPtr    = NULL;

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (SA_GPIO_INFO), &SaPegReset);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) SaPegReset, sizeof (SA_GPIO_INFO), 0);
  SaPlatformPolicyPpi->PcieConfig->PegGpioData->SaPegReset = SaPegReset;

#if defined SwitchableGraphics_SUPPORT && SwitchableGraphics_SUPPORT == 1
  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (SA_GPIO_INFO), &SgDgpuPwrOK);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) SgDgpuPwrOK, sizeof (SA_GPIO_INFO), 0);
  SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrOK = SgDgpuPwrOK;

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (SA_GPIO_INFO), &SgDgpuPwrEnable);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) SgDgpuPwrEnable, sizeof (SA_GPIO_INFO), 0);
  SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrEnable = SgDgpuPwrEnable;

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (SA_GPIO_INFO), &SgDgpuHoldRst);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) SgDgpuHoldRst, sizeof (SA_GPIO_INFO), 0);;
  SaPlatformPolicyPpi->SgGpioData->SgDgpuHoldRst = SgDgpuHoldRst;

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (SA_GPIO_INFO), &SgDgpuPrsnt);
  ASSERT_PEI_ERROR (PeiServices, Status);
  (*PeiServices)->SetMem ((VOID*) SgDgpuPrsnt,   sizeof (SA_GPIO_INFO), 0);
  SaPlatformPolicyPpi->SgGpioData->SgDgpuPrsnt = SgDgpuPrsnt;
#endif

  //
  // Initialize the PPI
  //
  SaPlatformPolicyPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  SaPlatformPolicyPpiDesc->Guid  = &gSaPlatformPolicyPpiGuid;
  SaPlatformPolicyPpiDesc->Ppi   = SaPlatformPolicyPpi;

  // Read MC device ID
  McDeviceId = READ_PCI16_NB(R_SA_MC_DEVICE_ID);

  // Read PCH device ID
  LpcDeviceId = READ_PCI16_SB(R_PCH_LPC_DEVICE_ID);

    // Update the REVISION number
    SaPlatformPolicyPpi->Revision = SA_PLATFORM_POLICY_PPI_REVISION_15;

    // Get the Platform Configuration from NbSetupData
    SaPlatformPolicyPpi->PlatformData->SpdAddressTable[0]   = DIMM1_SMBUS_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->SpdAddressTable[1]   = DIMM2_SMBUS_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->SpdAddressTable[2]   = DIMM3_SMBUS_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->SpdAddressTable[3]   = DIMM4_SMBUS_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->MchBar               = (UINT32)NB_MCH_BASE_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->DmiBar               = (UINT32)NB_DMI_BASE_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->EpBar                = (UINT32)NB_EP_BASE_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->PciExpressBar        = (UINT32)PCIEX_BASE_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->SmbusBar             = (UINT32)SMBUS_BASE_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->EdramBar             = (UINT32)NB_DERAM_BASE_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->GdxcBar              = (UINT32)NB_GDXC_BASE_ADDRESS;
    SaPlatformPolicyPpi->PlatformData->TsegSize             = (UINT32)TSEG_SIZE;
    SaPlatformPolicyPpi->PlatformData->IedSize              = (UINT32)IED_SIZE;
    SaPlatformPolicyPpi->PlatformData->FastBoot             = NbSetupData->MrcFastBoot;

    if(NbSetupData->IsRunMemoryDown) {
       SaPlatformPolicyPpi->PlatformData->BoardId           = 0;
    } else {
       SaPlatformPolicyPpi->PlatformData->BoardId           = 0xff;
    }

    SaPlatformPolicyPpi->MemConfig->MrcFastBoot             = NbSetupData->MrcFastBoot;

    SaPlatformPolicyPpi->MemConfig->BClkFrequency           = 100 * 1000 * 1000;
    SaPlatformPolicyPpi->MemConfig->MaxRttWr                = NbSetupData->MaxRttWr;
    SaPlatformPolicyPpi->MemConfig->PowerDownMode           = NbSetupData->PowerDownMode0;
    SaPlatformPolicyPpi->MemConfig->PwdwnIdleCounter        = NbSetupData->PwdwnIdleCounter;
    SaPlatformPolicyPpi->MemConfig->RankInterleave          = NbSetupData->RankInterleave;
    SaPlatformPolicyPpi->MemConfig->EnhancedInterleave      = NbSetupData->EnhancedInterleave;
    SaPlatformPolicyPpi->MemConfig->WeaklockEn              = NbSetupData->WeaklockEn;
    SaPlatformPolicyPpi->MemConfig->EnCmdRate               = 7;
    SaPlatformPolicyPpi->MemConfig->CmdTriStateDis          = FALSE;
    SaPlatformPolicyPpi->MemConfig->RefreshRate2x           = NbSetupData->Refresh2X;

    SaPlatformPolicyPpi->MemConfig->McLock                  = NbSetupData->McLock;

    SaPlatformPolicyPpi->MemConfig->GdxcEnable              = NbSetupData->GdxcEnable;
    SaPlatformPolicyPpi->MemConfig->GdxcIotSize             = NbSetupData->GdxcIotSize;
    SaPlatformPolicyPpi->MemConfig->GdxcMotSize             = NbSetupData->GdxcMotSize;
    SaPlatformPolicyPpi->MemConfig->MemoryTrace             = NbSetupData->MemoryTrace;

    SaPlatformPolicyPpi->MemConfig->ECT                     = NbSetupData->ECT;
    SaPlatformPolicyPpi->MemConfig->SOT                     = NbSetupData->SOT;
    SaPlatformPolicyPpi->MemConfig->RDMPRT                  = NbSetupData->RDMPRT;
    SaPlatformPolicyPpi->MemConfig->RCVET                   = NbSetupData->RCVET;
    SaPlatformPolicyPpi->MemConfig->JWRL                    = NbSetupData->JWRL;
    SaPlatformPolicyPpi->MemConfig->FWRL                    = NbSetupData->FWRL;
    SaPlatformPolicyPpi->MemConfig->WRTC1D                  = NbSetupData->WRTC1D;
    SaPlatformPolicyPpi->MemConfig->RDTC1D                  = NbSetupData->RDTC1D;
    SaPlatformPolicyPpi->MemConfig->DIMMODTT                = NbSetupData->DIMMODTT;
    SaPlatformPolicyPpi->MemConfig->WRDST                   = NbSetupData->WRDST;
    SaPlatformPolicyPpi->MemConfig->WREQT                   = NbSetupData->WREQT;

    SaPlatformPolicyPpi->MemConfig->RDODTT                  = NbSetupData->RDODTT;
    SaPlatformPolicyPpi->MemConfig->RDEQT                   = NbSetupData->RDEQT;
    SaPlatformPolicyPpi->MemConfig->RDAPT                   = NbSetupData->RDAPT;
    SaPlatformPolicyPpi->MemConfig->WRTC2D                  = NbSetupData->WRTC2D;
    SaPlatformPolicyPpi->MemConfig->RDTC2D                  = NbSetupData->RDTC2D;
    SaPlatformPolicyPpi->MemConfig->CMDVC                   = NbSetupData->CMDVC;
    SaPlatformPolicyPpi->MemConfig->WRVC2D                  = NbSetupData->WRVC2D;
    SaPlatformPolicyPpi->MemConfig->RDVC2D                  = NbSetupData->RDVC2D;
    SaPlatformPolicyPpi->MemConfig->LCT                     = NbSetupData->LCT;
    SaPlatformPolicyPpi->MemConfig->RTL                     = NbSetupData->RTL;
    SaPlatformPolicyPpi->MemConfig->TAT                     = NbSetupData->TAT;
    SaPlatformPolicyPpi->MemConfig->MEMTST                  = NbSetupData->MEMTST;
    SaPlatformPolicyPpi->MemConfig->DIMMODTT1D              = NbSetupData->DIMMODTT1D;
    SaPlatformPolicyPpi->MemConfig->WRSRT                   = NbSetupData->WRSRT;
    SaPlatformPolicyPpi->MemConfig->DIMMRONT                = NbSetupData->DIMMRONT;
    SaPlatformPolicyPpi->MemConfig->ALIASCHK                = NbSetupData->ALIASCHK;
    SaPlatformPolicyPpi->MemConfig->RCVENC1D                = NbSetupData->RCVENC1D;
    SaPlatformPolicyPpi->MemConfig->RMC                     = NbSetupData->RMC;

    ///
    /// Channel Hash Configuration
    ///
    SaPlatformPolicyPpi->MemConfig->ChHashEnable            = NbSetupData->ChHashEnable;
    SaPlatformPolicyPpi->MemConfig->ChHashMask              = NbSetupData->ChHashMask;
    SaPlatformPolicyPpi->MemConfig->ChHashInterleaveBit     = NbSetupData->ChHashInterleaveBit;

    ///
    /// MrcUltPoSafeConfig
    /// 1 to enable, 0 to disable
    ///
//    SaPlatformPolicyPpi->MemConfig->MrcUltPoSafeConfig   = 0;

    if (GetPchSeries() == PchLp) {
       ///
       /// Interleaving mode of DQ/DQS pins - depends on board routing
       ///
       SaPlatformPolicyPpi->MemConfig->DqPinsInterleaved    = NbSetupData->DqPinsInterleaved;
    }

    // Get the Graphics configuration from the NbSetupData
    SaPlatformPolicyPpi->GtConfig->IgdDvmt50PreAlloc  = NbSetupData->IgdDvmt50PreAlloc;

    if (GetPchSeries() == PchLp) {
       NbSetupData->AlwaysEnablePeg = 2;
    }

    if (NbSetupData->AlwaysEnablePeg != 0) DisablePegDevices();

    //if AlwaysEnablePeg Auto and Enable send to Policy , disable device
    switch (NbSetupData->AlwaysEnablePeg) {
    case 0:
    case 1:
        SaPlatformPolicyPpi->PcieConfig->AlwaysEnablePeg = NbSetupData->AlwaysEnablePeg;
        break;
    case 2:
        // Disable Link
        for (i = 0; NBPcieBridge[i] != 0xFFFFFFFF; i++)
        {
            if (READ_MEM32(NBPcieBridge[i]) == 0xFFFFFFFF) continue;
            SET_MEM8((NBPcieBridge[i] + R_SA_PEG_LCTL_OFFSET), BIT04);
            SET_MEM8 ((NBPcieBridge[i] + R_SA_PEG_DEBUP2_OFFSET), BIT0);
            SET_MEM32 ((NBPcieBridge[i] + R_SA_PEG_PEGCOMLCGCTRL_OFFSET), BIT30);

        }
        // Disable PEG
        RESET_PCI16_NB(R_SA_DEVEN, (B_SA_DEVEN_D1F0EN_MASK | B_SA_DEVEN_D1F1EN_MASK | B_SA_DEVEN_D1F2EN_MASK)); // 0x54
        break;
    }

    SaPlatformPolicyPpi->GtConfig->InternalGraphics   = NbSetupData->InternalGraphics;
    SaPlatformPolicyPpi->GtConfig->PrimaryDisplay     = NbSetupData->PrimaryDisplay;
    SaPlatformPolicyPpi->GtConfig->ApertureSize       = NbSetupData->ApertureSize;

    // Control for enabling/disabling VDD force bit (Required only for early enabling of eDP panel)
    SaPlatformPolicyPpi->GtConfig->PanelPowerEnable   = NbSetupData->PanelPowerEnable;

    SaPlatformPolicyPpi->GtConfig->GttSize            = NbSetupData->GTTSize;
    SaPlatformPolicyPpi->GtConfig->GttMmAdr           = NB_TEMP_MMIO_BASE;

    // Get the PciExpress Configuration from the NbSetupData
    SaPlatformPolicyPpi->PcieConfig->DmiVc1   = NbSetupData->DmiVc1;
    SaPlatformPolicyPpi->PcieConfig->DmiVcp   = NbSetupData->DmiVcp;
    SaPlatformPolicyPpi->PcieConfig->DmiVcm   = NbSetupData->DmiVcm;
    SaPlatformPolicyPpi->PcieConfig->DmiGen2  = NbSetupData->DmiGen2;

    SaPlatformPolicyPpi->PcieConfig->PegGenx[0] = NbSetupData->PegGenx0;
    SaPlatformPolicyPpi->PcieConfig->PegGenx[1] = NbSetupData->PegGenx1;
    SaPlatformPolicyPpi->PcieConfig->PegGenx[2] = NbSetupData->PegGenx2;

    for (i = 0; i < SA_PEG_MAX_FUN; i++) {
      SaPlatformPolicyPpi->PcieConfig->PowerDownUnusedBundles[i] = NbSetupData->PowerDownUnusedBundles[i];
    }


  // UserBd = Mobile - 0; Desktop/UpServer - 1; ULT - 5;
  if(IS_SA_DEVICE_ID_MOBILE (McDeviceId)) {
    SaPlatformPolicyPpi->PlatformData->UserBd           = btCRBMB;
  } else {
    if (GetPchSeries() == PchLp) {
       SaPlatformPolicyPpi->PlatformData->UserBd           = btUser4;
    } else {
       SaPlatformPolicyPpi->PlatformData->UserBd           = btCRBDT;
    }
  }

    SaPlatformPolicyPpi->MemConfig->SpdProfileSelected  = NbSetupData->SpdProfileSelected;
    SaPlatformPolicyPpi->MemConfig->NModeSupport        = NbSetupData->NModeSupport;
    SaPlatformPolicyPpi->MemConfig->RMT                 = NbSetupData->RmtCrosserEnable;

#ifdef EFI_DEBUG
#if MRC_DEBUG_PRINT_SUPPORT
    SaPlatformPolicyPpi->MemConfig->MrcTimeMeasure = FALSE;
    SaPlatformPolicyPpi->MemConfig->SerialDebug = MSG_LEVEL_NOTE;
#else // #if MRC_DEBUG_PRINT_SUPPORT
    SaPlatformPolicyPpi->MemConfig->MrcTimeMeasure = FALSE;
    SaPlatformPolicyPpi->MemConfig->SerialDebug = MSG_LEVEL_WARNING;
#endif // #if MRC_DEBUG_PRINT_SUPPORT
#else   // EFI_DEBUG
    SaPlatformPolicyPpi->MemConfig->MrcTimeMeasure = FALSE;
    SaPlatformPolicyPpi->MemConfig->SerialDebug = MSG_LEVEL_NEVER;
#endif  // EFI_DEBUG

    SaPlatformPolicyPpi->MemConfig->DDR3Voltage = 0;
    SaPlatformPolicyPpi->MemConfig->DDR3VoltageWaitTime = NbSetupData->DDRVoltageWaitTime;
    SaPlatformPolicyPpi->MemConfig->RefClk = 0;
    SaPlatformPolicyPpi->MemConfig->Ratio = 0;

    //
    // Thermal Management Configuration
    //
    SaPlatformPolicyPpi->MemConfig->ThermalManagement = NbSetupData->MemoryThermalManagement;
    SaPlatformPolicyPpi->MemConfig->PeciInjectedTemp  = NbSetupData->PeciInjectedTemp;
    SaPlatformPolicyPpi->MemConfig->ExttsViaTsOnBoard = NbSetupData->ExttsViaTsOnBoard;
    SaPlatformPolicyPpi->MemConfig->ExttsViaTsOnDimm  = NbSetupData->ExttsViaTsOnBoard;
    SaPlatformPolicyPpi->MemConfig->VirtualTempSensor = NbSetupData->VirtualTempSensor;
    ///
    /// Options for Thermal settings
    ///
    SaPlatformPolicyPpi->MemConfig->EnableExtts            = NbSetupData->EnableExtts;
    SaPlatformPolicyPpi->MemConfig->EnableCltm             = NbSetupData->EnableCltm;
    SaPlatformPolicyPpi->MemConfig->EnableOltm             = NbSetupData->EnableOltm;
    SaPlatformPolicyPpi->MemConfig->EnablePwrDn            = NbSetupData->EnablePwrDn;
    SaPlatformPolicyPpi->MemConfig->Refresh2X              = NbSetupData->Refresh2XMode;
    SaPlatformPolicyPpi->MemConfig->LpddrThermalSensor     = NbSetupData->LpddrThermalSensor;
    SaPlatformPolicyPpi->MemConfig->LockPTMregs            = NbSetupData->LockPTMregs;
    SaPlatformPolicyPpi->MemConfig->UserPowerWeightsEn     = NbSetupData->UserPowerWeightsEn;

    SaPlatformPolicyPpi->MemConfig->EnergyScaleFact        = NbSetupData->EnergyScaleFact;
    SaPlatformPolicyPpi->MemConfig->RaplPwrFlCh1           = NbSetupData->RaplPwrFlCh1;
    SaPlatformPolicyPpi->MemConfig->RaplPwrFlCh0           = NbSetupData->RaplPwrFlCh0;

    SaPlatformPolicyPpi->MemConfig->RaplLim2Lock           = NbSetupData->RaplLim2Lock;
    SaPlatformPolicyPpi->MemConfig->RaplLim2WindX          = NbSetupData->RaplLim2WindX;
    SaPlatformPolicyPpi->MemConfig->RaplLim2WindY          = NbSetupData->RaplLim2WindY;
    SaPlatformPolicyPpi->MemConfig->RaplLim2Ena            = NbSetupData->RaplLim2Ena;
    SaPlatformPolicyPpi->MemConfig->RaplLim2Pwr            = NbSetupData->RaplLim2Pwr;
    SaPlatformPolicyPpi->MemConfig->RaplLim1WindX          = NbSetupData->RaplLim1WindX;
    SaPlatformPolicyPpi->MemConfig->RaplLim1WindY          = NbSetupData->RaplLim1WindY;
    SaPlatformPolicyPpi->MemConfig->RaplLim1Ena            = NbSetupData->RaplLim1Ena;
    SaPlatformPolicyPpi->MemConfig->RaplLim1Pwr            = NbSetupData->RaplLim1Pwr;

    SaPlatformPolicyPpi->MemConfig->WarmThresholdCh0Dimm0  = NbSetupData->WarmThresholdCh0Dimm0;
    SaPlatformPolicyPpi->MemConfig->WarmThresholdCh0Dimm1  = NbSetupData->WarmThresholdCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->WarmThresholdCh1Dimm0  = NbSetupData->WarmThresholdCh1Dimm0;
    SaPlatformPolicyPpi->MemConfig->WarmThresholdCh1Dimm1  = NbSetupData->WarmThresholdCh1Dimm1;
    SaPlatformPolicyPpi->MemConfig->HotThresholdCh0Dimm0   = NbSetupData->HotThresholdCh0Dimm0;
    SaPlatformPolicyPpi->MemConfig->HotThresholdCh0Dimm1   = NbSetupData->HotThresholdCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->HotThresholdCh1Dimm0   = NbSetupData->HotThresholdCh1Dimm0;
    SaPlatformPolicyPpi->MemConfig->HotThresholdCh1Dimm1   = NbSetupData->HotThresholdCh1Dimm1;
    SaPlatformPolicyPpi->MemConfig->WarmBudgetCh0Dimm0     = NbSetupData->WarmBudgetCh0Dimm0;
    SaPlatformPolicyPpi->MemConfig->WarmBudgetCh0Dimm1     = NbSetupData->WarmBudgetCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->WarmBudgetCh1Dimm0     = NbSetupData->WarmBudgetCh1Dimm0;
    SaPlatformPolicyPpi->MemConfig->WarmBudgetCh1Dimm1     = NbSetupData->WarmBudgetCh1Dimm1;
    SaPlatformPolicyPpi->MemConfig->HotBudgetCh0Dimm0      = NbSetupData->HotBudgetCh0Dimm0;
    SaPlatformPolicyPpi->MemConfig->HotBudgetCh0Dimm1      = NbSetupData->HotBudgetCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->HotBudgetCh1Dimm0      = NbSetupData->HotBudgetCh1Dimm0;
    SaPlatformPolicyPpi->MemConfig->HotBudgetCh1Dimm1      = NbSetupData->HotBudgetCh1Dimm1;

    SaPlatformPolicyPpi->MemConfig->IdleEnergyCh0Dimm1     = NbSetupData->IdleEnergyCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->IdleEnergyCh0Dimm0     = NbSetupData->IdleEnergyCh0Dimm0;
    SaPlatformPolicyPpi->MemConfig->PdEnergyCh0Dimm1       = NbSetupData->PdEnergyCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->PdEnergyCh0Dimm0       = NbSetupData->PdEnergyCh0Dimm0;
    SaPlatformPolicyPpi->MemConfig->ActEnergyCh0Dimm1      = NbSetupData->ActEnergyCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->ActEnergyCh0Dimm0      = NbSetupData->ActEnergyCh0Dimm0;
    SaPlatformPolicyPpi->MemConfig->RdEnergyCh0Dimm1       = NbSetupData->RdEnergyCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->RdEnergyCh0Dimm0       = NbSetupData->RdEnergyCh0Dimm0;
    SaPlatformPolicyPpi->MemConfig->WrEnergyCh0Dimm1       = NbSetupData->WrEnergyCh0Dimm1;
    SaPlatformPolicyPpi->MemConfig->WrEnergyCh0Dimm0       = NbSetupData->WrEnergyCh0Dimm0;

    SaPlatformPolicyPpi->MemConfig->IdleEnergyCh1Dimm1     = NbSetupData->IdleEnergyCh1Dimm1;
    SaPlatformPolicyPpi->MemConfig->IdleEnergyCh1Dimm0     = NbSetupData->IdleEnergyCh1Dimm0;
    SaPlatformPolicyPpi->MemConfig->PdEnergyCh1Dimm1       = NbSetupData->PdEnergyCh1Dimm1;
    SaPlatformPolicyPpi->MemConfig->PdEnergyCh1Dimm0       = NbSetupData->PdEnergyCh1Dimm0;
    SaPlatformPolicyPpi->MemConfig->ActEnergyCh1Dimm1      = NbSetupData->ActEnergyCh1Dimm1;
    SaPlatformPolicyPpi->MemConfig->ActEnergyCh1Dimm0      = NbSetupData->ActEnergyCh1Dimm0;
    SaPlatformPolicyPpi->MemConfig->RdEnergyCh1Dimm1       = NbSetupData->RdEnergyCh1Dimm1;
    SaPlatformPolicyPpi->MemConfig->RdEnergyCh1Dimm0       = NbSetupData->RdEnergyCh1Dimm0;
    SaPlatformPolicyPpi->MemConfig->WrEnergyCh1Dimm1       = NbSetupData->WrEnergyCh1Dimm1;
    SaPlatformPolicyPpi->MemConfig->WrEnergyCh1Dimm0       = NbSetupData->WrEnergyCh1Dimm0;

    SaPlatformPolicyPpi->MemConfig->SrefCfgEna             = NbSetupData->SrefCfgEna;
    SaPlatformPolicyPpi->MemConfig->SrefCfgIdleTmr         = NbSetupData->SrefCfgIdleTmr;
    SaPlatformPolicyPpi->MemConfig->ThrtCkeMinDefeat       = NbSetupData->ThrtCkeMinDefeat;
    SaPlatformPolicyPpi->MemConfig->ThrtCkeMinTmr          = NbSetupData->ThrtCkeMinTmr;

    if (GetPchSeries() == PchLp) {
      SaPlatformPolicyPpi->MemConfig->ThrtCkeMinDefeatLpddr = NbSetupData->ThrtCkeMinDefeatLpddr;
      SaPlatformPolicyPpi->MemConfig->ThrtCkeMinTmrLpddr    = NbSetupData->ThrtCkeMinTmrLpddr;
      SaPlatformPolicyPpi->MemConfig->EnablePwrDnLpddr      = NbSetupData->EnablePwrDnLpddr;
    }


    //
    // Scrambler
    //
    SaPlatformPolicyPpi->MemConfig->ScramblerSupport    = NbSetupData->ScramblerSupport;

    //
    // Power Mode Setting
    //
    SaPlatformPolicyPpi->MemConfig->ForceColdReset    = NbSetupData->ForceColdReset;
    //
    // Channel DIMM Disable
    //
    SaPlatformPolicyPpi->MemConfig->DisableDimmChannel[0] = NbSetupData->DisableDimmChannel0;
    SaPlatformPolicyPpi->MemConfig->DisableDimmChannel[1] = NbSetupData->DisableDimmChannel1;

    SaPlatformPolicyPpi->MemConfig->AutoSelfRefreshSupport = NbSetupData->AutoSelfRefreshSupport;
    SaPlatformPolicyPpi->MemConfig->ExtTemperatureSupport  = NbSetupData->ExtTemperatureSupport;

    ///
    /// Options for MC Register Offsets
    ///
    SaPlatformPolicyPpi->MemConfig->CAVrefCtlOffset    = NbSetupData->CAVrefCtlOffset;
    SaPlatformPolicyPpi->MemConfig->Ch0VrefCtlOffset   = NbSetupData->Ch0VrefCtlOffset;
    SaPlatformPolicyPpi->MemConfig->Ch1VrefCtlOffset   = NbSetupData->Ch1VrefCtlOffset;
    SaPlatformPolicyPpi->MemConfig->Ch0ClkPiCodeOffset = NbSetupData->Ch0ClkPiCodeOffset;
    SaPlatformPolicyPpi->MemConfig->Ch1ClkPiCodeOffset = NbSetupData->Ch1ClkPiCodeOffset;
    SaPlatformPolicyPpi->MemConfig->Ch0RcvEnOffset     = NbSetupData->Ch0RcvEnOffset;
    SaPlatformPolicyPpi->MemConfig->Ch0RxDqsOffset     = NbSetupData->Ch0RxDqsOffset;
    SaPlatformPolicyPpi->MemConfig->Ch0TxDqOffset      = NbSetupData->Ch0TxDqOffset;
    SaPlatformPolicyPpi->MemConfig->Ch0TxDqsOffset     = NbSetupData->Ch0TxDqsOffset;
    SaPlatformPolicyPpi->MemConfig->Ch0VrefOffset      = NbSetupData->Ch0VrefOffset;
    SaPlatformPolicyPpi->MemConfig->Ch1RcvEnOffset     = NbSetupData->Ch1RcvEnOffset;
    SaPlatformPolicyPpi->MemConfig->Ch1RxDqsOffset     = NbSetupData->Ch1RxDqsOffset;
    SaPlatformPolicyPpi->MemConfig->Ch1TxDqOffset      = NbSetupData->Ch1TxDqOffset;
    SaPlatformPolicyPpi->MemConfig->Ch1TxDqsOffset     = NbSetupData->Ch1TxDqsOffset;
    SaPlatformPolicyPpi->MemConfig->Ch1VrefOffset      = NbSetupData->Ch1VrefOffset;

    //
    // Initialize the 16bit CMOS location for scrambling seed storage when iFFS is enabled
    //
    SaPlatformPolicyPpi->ScramblerSeedCmosLocation = NB_CMOS_IFFS_SCRAMBLER_SEED;

    SaPlatformPolicyPpi->MemConfig->RemapEnable = NbSetupData->RemapEnable;

#ifdef BDAT_SUPPORT
    SaPlatformPolicyPpi->MemConfig->RmtBdatEnable =  NbSetupData->BdatAcpiTableSupport;
#endif

    SaPlatformPolicyPpi->PcieConfig->PegGen3Equalization = NbSetupData->PegGen3Equalization;

    //
    // PEG Sampler Calibration: 0 = Disabled, 1 = Enabled, 2 = Auto (default)
    //
    SaPlatformPolicyPpi->PcieConfig->PegSamplerCalibrate = NbSetupData->PegSamplerCalibrate;;

    //
    // PEG Gen3 Equalization Phase 2: 0 = Disabled (default), 1 = Enabled
    //
    SaPlatformPolicyPpi->PcieConfig->PegGen3EqualizationPhase2 = NbSetupData->PegGen3EqualizationPhase2;

    //
    // PEG Gen3 Preset Search: 0 = Disabled (default), 1 = Enabled
    // PEG Gen3 Preset Search dwell time: 400 ms
    // PEG Gen3 Preset Search Margin Steps: 2
    // PEG Gen3 Preset Search Start Margin: 15
    // PEG Gen3 Preset Search Error Target: 4
    //
    SaPlatformPolicyPpi->PcieConfig->PegGen3PresetSearch = NbSetupData->PegGen3PresetSearch;
    SaPlatformPolicyPpi->PcieConfig->PegGen3ForcePresetSearch = NbSetupData->PegGen3ForcePresetSearch;
    SaPlatformPolicyPpi->PcieConfig->PegGen3PresetSearchDwellTime = NbSetupData->PegGen3PresetSearchDwellTime;
    SaPlatformPolicyPpi->PcieConfig->PegGen3PresetSearchMarginSteps = NbSetupData->PegGen3PresetSearchMarginSteps;
    SaPlatformPolicyPpi->PcieConfig->PegGen3PresetSearchStartMargin = NbSetupData->PegGen3PresetSearchStartMargin;
    SaPlatformPolicyPpi->PcieConfig->PegGen3PresetSearchVoltageMarginSteps = NbSetupData->PegGen3PresetSearchVoltageMarginSteps;
    SaPlatformPolicyPpi->PcieConfig->PegGen3PresetSearchVoltageStartMargin = NbSetupData->PegGen3PresetSearchVoltageStartMargin;
    SaPlatformPolicyPpi->PcieConfig->PegGen3PresetSearchFavorTiming        = NbSetupData->PegGen3PresetSearchFavorTiming;
    SaPlatformPolicyPpi->PcieConfig->PegGen3PresetSearchErrorTarget        = NbSetupData->PegGen3PresetSearchErrorTarget;

    for (i = 0; i < 16; i++) {
        // RP preset goes to bits [3:0] and [19:16]
        // EP preset goes to bits [11:8] and [27:24]
        // EP hint   goes to bits [14:12] and [30:28]
        SaPlatformPolicyPpi->PcieConfig->Gen3RootPortPreset[i] = NbSetupData->Gen3RootPortPreset[i];
        SaPlatformPolicyPpi->PcieConfig->Gen3EndPointPreset[i] = NbSetupData->Gen3EndPointPreset[i];
        SaPlatformPolicyPpi->PcieConfig->Gen3EndPointHint[i] = NbSetupData->Gen3EndPointHint[i];
    }

    ///
    /// Parameters for PCIe ASPM flow control
    ///   InitPcieAspmAfterOprom:
    ///     0 (default) - PCIe ASPM will be initialized Before Oprom
    ///     1           - PCIe ASPM will be initialized After Oprom (required IOTRAP SMI handler)
    ///   Note: This setting should match supported mode!
    ///
    ///   SaIotrapSmiAddress:
    ///     IOTRAP SMI address for SA SMI callback handler. This should be given if platform supports InitPcieAspmAfterOprom = 1 scenario (SaLateInitSmm driver was compiled)
    ///
    SaPlatformPolicyPpi->PcieConfig->InitPcieAspmAfterOprom = NbSetupData->InitPcieAspmAfterOprom;
    SaPlatformPolicyPpi->PcieConfig->SaIotrapSmiAddress = NB_IOTRAP_SMI_ADDRESSE;

    ///
    /// Parameters for PCIe Gen3 device reset
    ///
    SaPlatformPolicyPpi->PcieConfig->PegGpioData->GpioSupport = NbSetupData->AllowPerstGpioUsage;
    if (SaPlatformPolicyPpi->PcieConfig->PegGpioData->GpioSupport) {
        ///
        /// PEG Reset: GPIO 50, Active Low (Mobile PDG)
        ///
        SaPlatformPolicyPpi->PcieConfig->PegGpioData->SaPegReset->Value  = NbSetupData->AllowPerstGpio;
        SaPlatformPolicyPpi->PcieConfig->PegGpioData->SaPegReset->Active = NbSetupData->AllowPerstGpioActive;
    }

    ///
    /// Enable/Disable RxCEM Loop back
    /// 1=Enable, 0=Disable (default)
    /// When enabled, Lane for loop back should be selected (0 ~ 15 and default is Lane 0)
    ///
    SaPlatformPolicyPpi->PcieConfig->RxCEMLoopback     = NbSetupData->RxCEMLoopback;
    SaPlatformPolicyPpi->PcieConfig->RxCEMLoopbackLane = NbSetupData->RxCEMLoopbackLane;

    ///
    /// Gen3 RxCTLE peaking default is 8
    ///
    for (i = 0; i < SA_PEG_MAX_BUNDLE; i++) {
        SaPlatformPolicyPpi->PcieConfig->Gen3RxCtleP[i] = NbSetupData->Gen3RxCtleP[i];
    }

    ///
    /// Initialize the SA PEG Data pointer for saved preset search results
    ///
    SaPlatformPolicyPpi->PcieConfig->PegDataPtr = NULL;

    SaPlatformPolicyPpi->PcieConfig->PegSwingControl = NbSetupData->SwingControl;

    SaPlatformPolicyPpi->PcieConfig->PegComplianceTestingMode  = NbSetupData->PegComplianceTestingMode;


    //
    // Read DDR Frequecy setting selected in Bios setup
    //
    switch (NbSetupData->DdrFreqLimit) {
    case DDR3_FREQ_1067:
        SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 1067;
        break;

    case DDR3_FREQ_1333:
        SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 1333;
        break;

    case DDR3_FREQ_1600:
        SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 1600;
        break;

    case DDR3_FREQ_1867:
        SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 1867;
        break;

    case DDR3_FREQ_2133:
        SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 2133;
        break;

    case DDR3_FREQ_2400:
        SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 2400;
        break;

    case DDR3_FREQ_2667:
        SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 2667;
        break;

    case DDR3_FREQ_AUTO:
    default:
        SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 0;
        break;

  }

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
{
  WDT_PPI     *WdtPpi = NULL;
  UINT8       WdtFlag = V_PCH_OC_WDT_CTL_STATUS_FAILURE;

  //
  // Locate WDT PPI for access to Wdt->CheckStatus()
  //
  Status = (*PeiServices)->LocatePpi (
                    PeiServices,
                    &gWdtPpiGuid,
                    0,
                    NULL,
                    &WdtPpi
                    );
  if (!EFI_ERROR (Status)) {
      WdtFlag = WdtPpi->CheckStatus();
  }

  if (WdtFlag == V_PCH_OC_WDT_CTL_STATUS_OK) {
      if(NbSetupData->SpdProfileSelected == 1) {  // UserDefault
          if(NbSetupData->OcDdrFreqLimit != 0)

              SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = NbSetupData->OcDdrFreqLimit;
 //             if (SettingData.MemoryClockMultiplier == 100)
 //                SaPlatformPolicyPpi->MemConfig->RefClk = MRC_REF_CLOCK_100;

              SaPlatformPolicyPpi->MemConfig->Ratio = \
                  NbFrequencyToRatio(SaPlatformPolicyPpi->MemConfig->DdrFreqLimit, MRC_REF_CLOCK_133, SaPlatformPolicyPpi->MemConfig->BClkFrequency);//SaPlatformPolicyPpi->MemConfig->RefClk);

              SaPlatformPolicyPpi->MemConfig->tCL   = NbSetupData->tCL;
              SaPlatformPolicyPpi->MemConfig->tCWL  = NbSetupData->tCWL;
              SaPlatformPolicyPpi->MemConfig->tFAW  = NbSetupData->tFAW;
              SaPlatformPolicyPpi->MemConfig->tRAS  = NbSetupData->tRAS;
              SaPlatformPolicyPpi->MemConfig->tRC   = NbSetupData->tRC;
              SaPlatformPolicyPpi->MemConfig->tRCD  = NbSetupData->tRCD;
              SaPlatformPolicyPpi->MemConfig->tREFI = NbSetupData->tREFI;
              SaPlatformPolicyPpi->MemConfig->tRFC  = NbSetupData->tRFC;
              SaPlatformPolicyPpi->MemConfig->tRP   = NbSetupData->tRP;
              SaPlatformPolicyPpi->MemConfig->tRRD  = NbSetupData->tRRD;
              SaPlatformPolicyPpi->MemConfig->tRTP  = NbSetupData->tRTP;
              SaPlatformPolicyPpi->MemConfig->tWR   = NbSetupData->tWR;
              SaPlatformPolicyPpi->MemConfig->tWTR  = NbSetupData->tWTR;
//              SaPlatformPolicyPpi->MemConfig->tWTR  = NbSetupData->tRPab;

      } else if (SaPlatformPolicyPpi->MemConfig->SpdProfileSelected >= 2) { // XMP
          SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 0;
      }

#ifndef EFI_DEBUG
      if (WdtPpi != NULL && SaPlatformPolicyPpi->MemConfig->SpdProfileSelected != 0) {
          WdtPpi->ReloadAndStart (10); // 10 Sec
      }
#endif

  } else if (WdtFlag == V_PCH_OC_WDT_CTL_STATUS_FAILURE) {
      SaPlatformPolicyPpi->MemConfig->SpdProfileSelected = 0; // Auto
      SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = 0;
  }
}
#endif
// (P20121012A) >> Update XTU 4.0
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
{
    PERF_TUNE_PPI *PerfTunePpi;
    BIOS_SETTING_DATA SettingData;

    Status = (*PeiServices)->LocatePpi(
        PeiServices,
        &gPerfTunePpiGuid,
        0,
        NULL,
        &PerfTunePpi);
    if (EFI_ERROR(Status))
    {
        ASSERT_PEI_ERROR(PeiServices, Status);
    }else{

      Status = PerfTunePpi->GetSettingData(PeiServices, &SettingData);
      if((!EFI_ERROR (Status)) && (!PerfTunePpi->IsRunDefault(PeiServices)))
      {

          SaPlatformPolicyPpi->MemConfig->SpdProfileSelected = (UINT8)SettingData.XmpProfilesSelect;
          if (SettingData.XmpProfilesSelect == 1) {  // UserDefault


              if (SettingData.MemoryClockMultiplier == 100)
                 SaPlatformPolicyPpi->MemConfig->RefClk = MRC_REF_CLOCK_100;

              SaPlatformPolicyPpi->MemConfig->Ratio = (UINT8)SettingData.DDRMul / 2;

              SaPlatformPolicyPpi->MemConfig->DdrFreqLimit = \
                  NbRatioToFrequency(SaPlatformPolicyPpi->MemConfig->Ratio, SaPlatformPolicyPpi->MemConfig->RefClk, SaPlatformPolicyPpi->MemConfig->BClkFrequency);

              SaPlatformPolicyPpi->MemConfig->tCL   = SettingData.tCL;
              SaPlatformPolicyPpi->MemConfig->tCWL  = SettingData.tCWL;
              SaPlatformPolicyPpi->MemConfig->tFAW  = SettingData.tFAW;
              SaPlatformPolicyPpi->MemConfig->tRAS  = SettingData.tRAS;
              SaPlatformPolicyPpi->MemConfig->tRC   = SettingData.tRC;
              SaPlatformPolicyPpi->MemConfig->tRCD  = SettingData.tRCD;
              SaPlatformPolicyPpi->MemConfig->tREFI = SettingData.tREFI;
              SaPlatformPolicyPpi->MemConfig->tRFC  = SettingData.tRFC;
              SaPlatformPolicyPpi->MemConfig->tRP   = SettingData.tRP;
              SaPlatformPolicyPpi->MemConfig->tRRD  = SettingData.tRRD;
              SaPlatformPolicyPpi->MemConfig->tRTP  = SettingData.tRTP;
              SaPlatformPolicyPpi->MemConfig->tWR   = SettingData.tWR;
              SaPlatformPolicyPpi->MemConfig->tWTR  = SettingData.tWTR;
              //SaPlatformPolicyPpi->MemConfig->tRPab  = SettingData.tRPab;
          } // SettingData.XmpProfilesSelect == 1

          WRITE_MEM8_MCH(0x5990, (UINT8)SettingData.RuntimeTurbo);

          NbSetupData->GtOcSupport   = 0; // if XTU is Enable, Default = disable.
          if((SettingData.GraphicTurboRatioLimit!=0xFFFF)){
            NbSetupData->GtMaxOcTurboRatio   = SettingData.GraphicTurboRatioLimit;
            NbSetupData->GtExtraTurboVoltage = SettingData.GraphicsCoreVoltageOverride;

			NbSetupData->GtVoltageOverride   = SettingData.GraphicsCoreVoltageOverride;
			NbSetupData->GtVoltageMode       = (UINT8)SettingData.GraphicsCoreVoltageMode;
            // GT offset
            if (SettingData.GraphicsCoreVoltageOffset >=0 && \
                SettingData.GraphicsCoreVoltageOffset <= 999){
                    NbSetupData->GtVoltageOffset     = ~(1000 - SettingData.GraphicsCoreVoltageOffset) + 1;
            }else if (SettingData.GraphicsCoreVoltageOffset >=1000 && \
                        SettingData.GraphicsCoreVoltageOffset <= 1998){
                    NbSetupData->GtVoltageOffset     = SettingData.GraphicsCoreVoltageOffset - 1000;
            }
            // SA offset
            if (SettingData.SystemAgentVoltageOffset >=0 && \
                SettingData.SystemAgentVoltageOffset <= 999){
                    NbSetupData->SaVoltageOffset     = ~(1000 - SettingData.SystemAgentVoltageOffset) + 1;
            }else if (SettingData.SystemAgentVoltageOffset >=1000 && \
                        SettingData.SystemAgentVoltageOffset <= 1998){
                    NbSetupData->SaVoltageOffset     = SettingData.SystemAgentVoltageOffset - 1000;
            }
            // IOA offset
            if (SettingData.IOAnalogVoltageOffset >=0 && \
                SettingData.IOAnalogVoltageOffset <= 999){
                    NbSetupData->IoaVoltageOffset     = ~(1000 - SettingData.IOAnalogVoltageOffset) + 1;
            }else if (SettingData.IOAnalogVoltageOffset >=1000 && \
                        SettingData.IOAnalogVoltageOffset <= 1998){
                    NbSetupData->IoaVoltageOffset     = SettingData.IOAnalogVoltageOffset - 1000;
            }

            // IOD offset
            if (SettingData.IODigitalVoltageOffset >=0 && \
                SettingData.IODigitalVoltageOffset <= 999){
                    NbSetupData->IodVoltageOffset     = ~(1000 - SettingData.IODigitalVoltageOffset) + 1;
            }else if (SettingData.IODigitalVoltageOffset >=1000 && \
                        SettingData.IODigitalVoltageOffset <= 1998){
                    NbSetupData->IodVoltageOffset     = SettingData.IODigitalVoltageOffset - 1000;
            }
			NbSetupData->GtOcSupport         = 1;
          }
        }else{
            NbSetupData->GtVoltageOffset        = 0;
            NbSetupData->GtVoltageOverride      = 0;
            NbSetupData->GtExtraTurboVoltage    = 0;
            NbSetupData->GtMaxOcTurboRatio      = READ_MEM8_MCH(0x5998);
            NbSetupData->SaVoltageOffset        = 0;
            NbSetupData->GtVoltageMode          = 0;
			NbSetupData->GtOcSupport            = 1;
            NbSetupData->IoaVoltageOffset       = 0;
            NbSetupData->IodVoltageOffset       = 0;
        }
    }
}
#endif
#endif

  ///
  /// Initialize the Overclocking Configuration
  ///
  if (NbSetupData->GtOcSupport == 0)
  {
      SaPlatformPolicyPpi->OcConfig->GtVoltageOffset     = 0;
      SaPlatformPolicyPpi->OcConfig->GtVoltageOverride   = 0;
      SaPlatformPolicyPpi->OcConfig->GtExtraTurboVoltage = 0;
      SaPlatformPolicyPpi->OcConfig->GtMaxOcTurboRatio   = 0;
      SaPlatformPolicyPpi->OcConfig->SaVoltageOffset     = 0;
      SaPlatformPolicyPpi->OcConfig->GtVoltageMode       = 0;
      SaPlatformPolicyPpi->OcConfig->OcSupport           = 0;
      SaPlatformPolicyPpi->OcConfig->IoaVoltageOffset    = 0;
      SaPlatformPolicyPpi->OcConfig->IodVoltageOffset    = 0;
  } else {
      SaPlatformPolicyPpi->OcConfig->GtVoltageOffset     = NbSetupData->GtVoltageOffset;
      SaPlatformPolicyPpi->OcConfig->GtVoltageOverride   = NbSetupData->GtVoltageOverride;
      SaPlatformPolicyPpi->OcConfig->GtExtraTurboVoltage = NbSetupData->GtExtraTurboVoltage;
      SaPlatformPolicyPpi->OcConfig->GtMaxOcTurboRatio   = NbSetupData->GtMaxOcTurboRatio;
      SaPlatformPolicyPpi->OcConfig->SaVoltageOffset     = NbSetupData->SaVoltageOffset;
      SaPlatformPolicyPpi->OcConfig->GtVoltageMode       = NbSetupData->GtVoltageMode;
      SaPlatformPolicyPpi->OcConfig->OcSupport           = 1;
      SaPlatformPolicyPpi->OcConfig->IoaVoltageOffset    = NbSetupData->IoaVoltageOffset;
      SaPlatformPolicyPpi->OcConfig->IodVoltageOffset    = NbSetupData->IodVoltageOffset;
  }
// (P20121012A) << Update XTU 4.0
  // Make sure we have a PPI.
  if (VariableServices != NULL) {

      // If Maximum TOLUD set to Dynamic assignment in BIOS setup, then set TOLUD/TOLM based on largest MMIO length of graphic controllers
      if (NbSetupData->MaxTolud == NB_MAX_TOLUD_DYNAMIC) {
        VariableSize = sizeof(UINT32);
        Status = VariableServices->GetVariable(
                                             VariableServices,
                                             L"MemCeil.",
                                             &gEfiNbMrcS3DataGuid,
                                             NULL,
                                             &VariableSize,
                                             &MemoryCeiling);

        if(Status == EFI_NOT_FOUND) {
          Status = VariableServices->GetVariable(
                                               VariableServices,
                                               L"MemCeil.",
                                               &gEfiGlobalVariableGuid,
                                               NULL,
                                               &VariableSize,
                                               &MemoryCeiling);
        }
        if(!EFI_ERROR(Status)) {
            if(MemoryCeiling >= 0xE0000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_3_5G;
            } else if(MemoryCeiling >= 0xD0000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_3_25G;
            } else if(MemoryCeiling >= 0xC0000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_3G;
            } else if(MemoryCeiling >= 0xB0000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_2_75G;
            } else if(MemoryCeiling >= 0xA0000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_2_5G;
            } else if(MemoryCeiling >= 0x90000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_2_25G;
            } else if(MemoryCeiling >= 0x80000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_2G;
            } else if(MemoryCeiling >= 0x70000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_1_75G;
            } else if(MemoryCeiling >= 0x60000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_1_5G;
            } else if(MemoryCeiling >= 0x50000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_1_25G;
            } else if(MemoryCeiling >= 0x40000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_1G;
            } else if(MemoryCeiling >= 0x30000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_0_75G;
            } else if(MemoryCeiling <= 0x20000000) {
                NbSetupData->MaxTolud = NB_MAX_TOLUD_0_5G;
            }
        } else {
          NbSetupData->MaxTolud = NB_MAX_TOLUD_DYNAMIC; // default value
        }
      }
  }

  //
  // Based on BIOS setup to determine maximum top of memory size below 4G, and reserved for MMIO
  //
  switch (NbSetupData->MaxTolud) {
  case NB_MAX_TOLUD_0_5G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0xE00;
    break;

  case NB_MAX_TOLUD_0_75G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0xD00;
    break;

  case NB_MAX_TOLUD_1G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0xC00;
    break;

  case NB_MAX_TOLUD_1_25G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0xB00;
    break;

  case NB_MAX_TOLUD_1_5G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0xA00;
    break;

  case NB_MAX_TOLUD_1_75G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0x900;
    break;

  case NB_MAX_TOLUD_2G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0x800;
    break;

  case NB_MAX_TOLUD_2_25G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0x700;
    break;

  case NB_MAX_TOLUD_2_5G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0x600;
    break;

  case NB_MAX_TOLUD_2_75G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0x500;
    break;

  default:

  case NB_MAX_TOLUD_3G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0x400;
    break;

  case NB_MAX_TOLUD_3_25G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0x300;
    break;

  case NB_MAX_TOLUD_3_5G:
    SaPlatformPolicyPpi->GtConfig->MmioSize = 0x200;
    break;
  }

  // EccSupport = 1 for UpSever and WS
  if (!(IS_SA_DEVICE_ID_SERVER (McDeviceId) || IS_PCH_LPT_LPC_DEVICE_ID_SERVER(LpcDeviceId)) &&
      (IS_PCH_LPT_LPC_DEVICE_ID_MOBILE(LpcDeviceId) || IS_PCH_LPT_LPC_DEVICE_ID_DESKTOP(LpcDeviceId))) {
      SaPlatformPolicyPpi->MemConfig->EccSupport = NbSetupData->EccSupport;
  } else {
      SaPlatformPolicyPpi->MemConfig->EccSupport = 1;
  }

  // Get the Memory Configuration from NbSetupData
  SaPlatformPolicyPpi->MemConfig->MaxTolud      = NbSetupData->MaxTolud;

#if defined SwitchableGraphics_SUPPORT && SwitchableGraphics_SUPPORT == 1
  if (NbSetupData->PrimaryDisplay == 4) // SG
  {
    SaPlatformPolicyPpi->PcieConfig->AlwaysEnablePeg  = 1; // Enable
    SaPlatformPolicyPpi->GtConfig->PrimaryDisplay   = 0; // IGFX

    ///
    /// Initialize the Switchable Graphics Configuration
    ///
    ///
    /// Switchable Graphics mode set as MUXLESS (By default)
    ///
    SaPlatformPolicyPpi->PlatformData->SgMode = SgModeMuxless;
    SaPlatformPolicyPpi->PlatformData->SgSubSystemId = 0x2112;

    ///
    /// Configure below based on the OEM platfrom design
    /// Switchable Graphics GPIO support - 1=Supported 0=Not Supported
    ///
    SaPlatformPolicyPpi->SgGpioData->GpioSupport = SG_GPIO_SUPPORT;

    if (SaPlatformPolicyPpi->SgGpioData->GpioSupport) {
        ///
        /// Initialzie the GPIO Configuration
        ///
        if (GetPchSeries() == PchLp) {
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrOK->Value = GPIO_dGPU_PWROK_ULT;         // dGPU PWROK GPIO assigned
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrOK->Active = ACTIVE_dGPU_PWROK_ULT;      // dGPU PWROK Active
            SaPlatformPolicyPpi->SgGpioData->SgDgpuHoldRst->Value = GPIO_dGPU_HOLD_RST_ULT;    // dGPU HLD RST GPIO assigned
            SaPlatformPolicyPpi->SgGpioData->SgDgpuHoldRst->Active = ACTIVE_dGPU_HOLD_RST_ULT; // dGPU HLD RST Active
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrEnable->Value = GPIO_dGPU_PWR_EN_ULT;    // dGPU PWR Enable GPIO assigned
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrEnable->Active = ACTIVE_dGPU_PWR_EN_ULT; // dGPU PWR Enable Active
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPrsnt->Value = GPIO_dGPU_PRSNT_ULT;         // dGPU_PRSNT# GPIO assigned
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPrsnt->Active = ACTIVE_dGPU_PRSNT_ULT;      // dGPU_PRSNT# Active Low

        } else{
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrOK->Value = GPIO_dGPU_PWROK;             // dGPU PWROK GPIO assigned
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrOK->Active = ACTIVE_dGPU_PWROK;          // dGPU PWROK Active
            SaPlatformPolicyPpi->SgGpioData->SgDgpuHoldRst->Value = GPIO_dGPU_HOLD_RST;        // dGPU HLD RST GPIO assigned
            SaPlatformPolicyPpi->SgGpioData->SgDgpuHoldRst->Active = ACTIVE_dGPU_HOLD_RST;     // dGPU HLD RST Active
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrEnable->Value = GPIO_dGPU_PWR_EN;        // dGPU PWR Enable GPIO assigned
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPwrEnable->Active = ACTIVE_dGPU_PWR_EN;     // dGPU PWR Enable Active
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPrsnt->Value = GPIO_dGPU_PRSNT;             // dGPU_PRSNT# GPIO assigned
            SaPlatformPolicyPpi->SgGpioData->SgDgpuPrsnt->Active = ACTIVE_dGPU_PRSNT;          // dGPU_PRSNT# Active Low
        }
    }
  }
#endif

#if (defined RC_PEG_0) && RC_PEG_0 == 1
  if (NbSetupData->DetectNonComplaint && NbSetupData->AlwaysEnablePeg != 2)
  {
    SaPlatformPolicyPpi->PcieConfig->AlwaysEnablePeg  = 1; // Enable
  }
#endif

  if (GetPchSeries() == PchLp) {
     SaPlatformPolicyPpi->PcieConfig->AlwaysEnablePeg = 2;
  }

  // Make sure we have a PPI.
  if (VariableServices != NULL) {

    // Get variable size first.
    // Set VariableSize = 0 in order to get the required size.
    VariableSize  = 0;
    MrcS3ResumeData  = NULL;

    Status = VariableServices->GetVariable (
                                VariableServices,
                                L"MrcS3Resume",
                                &gMemRestoreDataGuid,
                                NULL,
                                &VariableSize,
                                MrcS3ResumeData
                                );

    // Should fail with EFI_BUFFER_TOO_SMALL
    if (Status == EFI_BUFFER_TOO_SMALL) {

      // Allocate buffer for S3 data variable.
      Status = (*PeiServices)->AllocatePool (PeiServices, VariableSize, &MrcS3ResumeData);
      ASSERT_PEI_ERROR (PeiServices, Status);

      Status = VariableServices->GetVariable (
                                  VariableServices,
                                  L"MrcS3Resume",
                                  &gMemRestoreDataGuid,
                                  NULL,
                                  &VariableSize,
                                  MrcS3ResumeData
                                  );
    }

    if (Status == EFI_SUCCESS) {
      // MemoryConfig variable memory layout: MRC_OutputParames, MRC_S3Params
      // Increment the pointer, MrcS3ResumeData, to point to MRC_S3Params
      SaPlatformPolicyPpi->S3DataPtr = MrcS3ResumeData;
    }

    PegGen3Data = NULL;
    VariableSize = sizeof(SA_PEG_DATA);

    // Allocate buffer for PegGen3PresetSearch data variable.
    Status = (*PeiServices)->AllocatePool (PeiServices, VariableSize, &PegGen3Data);
    ASSERT_PEI_ERROR (PeiServices, Status);

    Status = VariableServices->GetVariable (
                                  VariableServices,
                                  L"PegGen3PresetSearchData",
                                  &gAmiNbPegGen3PresetSearchGuid,
                                  NULL,
                                  &VariableSize,
                                  PegGen3Data
                                  );

    if (Status == EFI_SUCCESS) {
      // Increment the pointer, PegGen3PresetSearch Data, to point to PegDataPtr
      SaPlatformPolicyPpi->PcieConfig->PegDataPtr = PegGen3Data;
    }

  }

  // Install SA Platform Policy PPI
  Status = (**PeiServices).InstallPpi (PeiServices, SaPlatformPolicyPpiDesc);
  ASSERT_PEI_ERROR (PeiServices, Status);

  return Status;
}

#ifdef SSA_FLAG

MrcStatus
AmiSsaCallbackPpi (
  EFI_PEI_SERVICES                 **PeiServices,
  struct _SSA_BIOS_CALLBACKS_PPI   *SsaBiosCallBacksPpi,
  MRC_OEM_STATUS_COMMAND           StatusCommand,
  VOID                             *CheckpointData)
{
    EFI_STATUS	                    Status;
    PEI_MEMORY_ERROR_REPORT_PPI     *MemoryErrorPpi;

    // if oem have reinstall gAmiMemoryErrorReportPpi, it can Locate AmiMemoryError for oem.
    Status = (*PeiServices)->LocatePpi(
        PeiServices, &gAmiMemoryErrorReportPpiGuid, 0, NULL,
        &MemoryErrorPpi );

    ASSERT_PEI_ERROR(PeiServices, Status);

    if (Status == EFI_SUCCESS)
        MemoryErrorPpi->AmiMemoryErrorRead(PeiServices, MemoryErrorPpi, (UINT32)StatusCommand);

    return StatusCommand;
}
#endif // #ifndef SSA_FLAG
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: MemoryErrorRead
//
// Description:
//       This function reports the error status after memory training.
//
// Parameters:
//  IN          EFI_PEI_SERVICES    PeiServices - PEI Services table pointer
//  IN          PEI_MEMORY_ERROR_REPORT_PPI *This - Pointer to the PPI structure
//  IN OUT      UINT32              MemErrData - Pointer to error data buffer
//
// Returns:
//      EFI_STATUS
//      EFI_SUCCESS     The function completed successfully.
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MemoryErrorRead (
  IN      EFI_PEI_SERVICES      **PeiServices,
  IN      PEI_MEMORY_ERROR_REPORT_PPI      *This,
  IN OUT  UINT32                MemErrData
  )
{
    EFI_STATUS	                    Status = EFI_SUCCESS;
    switch  (MemErrData) {
        case MRC_MC_CONFIG_ERROR :
        case MRC_MC_MEMORY_MAP_ERROR :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_CONFIGURING, EFI_ERROR_MAJOR);
            break;
        case    MRC_DIMM_RON_ERROR :
        case    MRC_DIMM_ODT_ERROR :
        case    MRC_WRITE_DS_ERROR :
        case    MRC_WRITE_SR_ERROR :
        case    MRC_WRITE_EQ_ERROR :
        case    MRC_READ_ODT_ERROR :
        case    MRC_READ_EQ_ERROR :
        case    MRC_READ_AMP_POWER_ERROR :
        case    MRC_CMP_OPT_ERROR :
        case    MRC_PWR_MTR_ERROR :
        case    MRC_SPD_PROCESSING_ERROR :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_SPD_FAIL, EFI_ERROR_MAJOR);
            break;
        case    MRC_RESET_ERROR :           ///<  before jedec reset
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_INVALID_TYPE, EFI_ERROR_MAJOR);
            break;
        case  MRC_PRE_TRAINING_ERROR :
        case  MRC_EARLY_COMMAND_ERROR :
        case  MRC_JEDEC_INIT_LPDDR3_ERROR :
        case  MRC_SENSE_AMP_OFFSET_ERROR :
        case  MRC_RECEIVE_ENABLE_ERROR :
        case  MRC_JEDEC_WRITE_LEVELING_ERROR :
        case  MRC_WRITE_TIMING_1D_ERROR :
        case  MRC_WRITE_TIMING_2D_ERROR :
        case  MRC_READ_TIMING_1D_ERROR :
        case  MRC_READ_TIMING_2D_ERROR :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_INVALID_SPEED, EFI_ERROR_MAJOR);
            break;
        case    MRC_ECC_CLEAN_ERROR :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_ERROR, EFI_ERROR_MAJOR);
            break;
        case    MRC_NO_MEMORY_DETECTED :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_NOT_DETECTED, EFI_ERROR_MAJOR);
            break;
        case    MRC_MEM_INIT_DONE_WITH_ERRORS :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_TEST, EFI_ERROR_MAJOR);
            break;
        case    MRC_WRITE_VREF_2D_ERROR :
        case    MRC_READ_VREF_2D_ERROR :
        case    MRC_LATE_COMMAND_ERROR :
        case    MRC_ROUND_TRIP_LAT_ERROR :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_NONE_USEFUL, EFI_ERROR_MAJOR);
            break;
        case    MRC_TURN_AROUND_ERROR :
        case    MRC_SAVE_MC_VALUES_ERROR :
        case    MRC_RMT_TOOL_ERROR :
        case    MRC_CPGC_MEMORY_TEST_ERROR :
        case    MRC_RESTORE_TRAINING_ERROR :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_MISMATCH, EFI_ERROR_MAJOR);
            break;
        case    MRC_SELF_REFRESH_EXIT_ERROR :
        case    MRC_MRC_NORMAL_MODE_ERROR :
        case    MRC_ALIAS_CHECK_ERROR :
        case    MRC_POST_TRAINING_ERROR :
        case    MRC_MC_ACTIVATE_ERROR :
        case    MRC_DONE_WITH_ERROR :
        case    MRC_FILL_RMT_STRUCTURE_ERROR :
            PEI_ERROR_CODE(PeiServices, PEI_MEMORY_NOT_INSTALLED, EFI_ERROR_MAJOR);
            break;
        default :              //Default to " N/A "
            break;
    }

    return Status;
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
