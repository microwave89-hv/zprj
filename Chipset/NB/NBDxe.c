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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBDxe.c 50    12/02/14 3:20a Dennisliu $
//
// $Revision: 50 $
//
// $Date: 12/02/14 3:20a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBDxe.c $
// 
// 50    12/02/14 3:20a Dennisliu
// [TAG]  		EIP194524
// [Category]  	Spec Update
// [Description]  	Shark Bay SA Reference Code Production Version 1.9.0
// 
// 49    5/28/14 3:03a Dennisliu
// [TAG]           EIP161790
// [Category]      Improvement
// [Description]   DRAM Init BIT should be set after saving MRC S3 data to
// NVRAM in DXE Phase as Intel suggested.
// [Files]         NBPei.c; NBDxe.c;
//
// 48    5/13/14 10:40p Dennisliu
// [TAG]           EIP167027
// [Category]      Improvement
// [Description]   [SharkBay Aptio4]Variable's attribute needs to be
// reviewed by SA component driver
// [Files]         NBDXEBoard.c; IntelSaGopSetup.c; IntelSaGopPolicy.c;
// NBDxe.c; NbPciCSP.c; PciHostBridge.c;
//
// 47    7/16/13 6:57a Jeffch
// [TAG]          None
// [Severity]     Improvement
// [Description]  Remove same offset acpi device.
// [Files]        NBDXE.c;
//
// 46    7/09/13 4:23a Ireneyang
// [TAG]         EIP128014
// [Category]    BrugFix
// [Symptom]     When populating PC3L DIMM x2 or upper DIMM slot only,
//               DMI type17 has wrong values.
// [RootCause]   When using Dimm with SPD funciton, there's no need to
//               use when using memorydown way to get spd data.
// [Solution]    Only when using memorydown Dimm needs to get SPD data.
// [Files]       NBDxe.c;
//
// 45    5/24/13 6:21a Jeffch
// [TAG]          None
// [Severity]     BugFix
// [Description]  Fix smbios type 17 data is incorrect for memory down
// system .
// [Files]        NBDxe.c;
//
// 44    4/01/13 11:47p Ireneyang
// # [TAG]          None
// [Severity]     Improvement
// [Description]  Reduce boot time through PEG.
// [Files]        NB.mak; NBDxe.c; NBPEI.c; NBPPI.h; Sa.asl;
//                PcieComplex.c; GraphicsInit.c; PciExpressInit.c;
//
// 43    3/15/13 1:56a Ireneyang
// [TAG]          EIP118133
// [Severity]     BugFix
// [Description]  Fix and restructure PlatformConfig setting of SA policy.
// [Files]        NBDxe.c; GetSetupData.c; NbSetupData.h;
//
// 42    3/12/13 2:30a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Remove related SaSsdt acpi data to DSDT
// [Files]        SaInit.c; INTELGFX.ASL; Sa.asl; SaSsdt.asl;
//                SaSsdtTables.sdl; NBDxe.c; NB.mak;
//
// 41    3/07/13 2:20a Ireneyang
// [TAG]          None
// [Severity]     Bug Fix
// [Description]  Intel Display Device disappear after S3 resume.
// [Files]        NBDXE.c;
//
// 39    2/09/13 10:23a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.1.0
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c;
//
// 38    1/28/13 5:53a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.0.
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c;
//                NB.sd; NB.uni; NBDxeBoard.c
//
// 37    1/11/13 1:49a Jeffch
// [TAG]          None
// [Severity]     Bug Fix
// [Description]  Fixed Peg error log init bug.
// [Files]        NBDXE.c;
//
// 36    1/10/13 6:00a Jeffch
// [TAG]          None
// [Severity]     Bug Fix
// [Description]  Fixed not program HDA codec for SaHDAVerbtable link bug.
// [Files]        NBDXE.c; GetSetupData.c; NbSetupData.h
//
// 35    1/03/13 7:30a Jeffch
// [TAG]          None
// [Severity]     Improvement
// [Description]  added SaHDAVerbtable link to OEM.
// [Files]        NBDxe.c; NbSetupData.h; GetSetupData.c;
//
// 34    12/24/12 3:16a Jeffch
// [TAG]         None
// [Category]    Bug Fix
// [Description] fixed XTU not have create XMP GACI table.
// [Files]         NBDxe.c;
//
// 33    12/24/12 3:06a Jeffch
// [TAG]         None
// [Category]    Bug Fix
// [Description] fixed XTU build fail issue.
// [Files]         NBDxe.c;
//
// 32    12/24/12 2:55a Jeffch
// [TAG]         None
// [Category]    Improvement
// [Description] added ULT SKU auto disable PEG.
// [Files]        NBPei.c; NBDxe.c; NbPlatform.h; NB.sd;
// [TAG]         None
// [Category]    Bug Fix
// [Description] Remove tRPab and fixed XTU build fail issue.
// [Files]        NBPei.c; NBDxe.c; NB.sd;
//
// 31    12/22/12 2:28a Jeffch
// [TAG]          None
// [Severity]     Bug Fix
// [Description]  Fxied anyway show Memory Timing default value.
// [Files]        NBPei.c;
//
// 30    12/19/12 7:15a Jeffch
// [TAG]          VddVoltage
// [Severity]     Bug Fix
// [Description]  Fixed show error Memory Voltage value.
// [Files]        NBDxe.c;
//
// 29    12/18/12 5:14a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 0.81.
// [Files]        NBDxe.c; NBPei.c
//
// 28    12/14/12 5:29a Jeffch
// // [TAG]          None
// // [Severity]     Important
// // [Description]  Show memory voltage.
// // [Files]        NB.sd; NB.uni; NBDxe.c.
//
// 27    12/03/12 5:57a Jeffch
// [TAG]           None
// [Category]      Improvement
// [Description]   optimize DetectNonComplaint function.
// [Description]   NBPEI.c, NBPPI.h, NBDxe.c
//
// 2     11/29/12 3:41a Jeffch
//
// 26    11/29/12 2:32a Jeffch
// [TAG]         None
// [Category]    Improvement
// [Description] added bootime check IGFX Available.
// [Files]       NBDxe.c; NbPlatform.h; NB.sd;
//
// 23    11/20/12 2:57a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update SA RC 0.80.
// [Files]        NBDxe.c; NBPei.c
//
// 22    11/14/12 5:38a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update XTU4.x function
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; NB.sd;
// NB.uni
//
// 21    11/07/12 6:22a Jeffch
// [TAG]          EIP106013
// [Severity]     Important
// [Description]   Sound and image abnormal with HDMI.
// [Files]        NBDxe.c;
//
// 20    10/30/12 7:02a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update SA RC 0.72.
// [Files]        NBDxe.c; NBPei.c
//
// 19    10/16/12 9:39a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  SA RC 0.71 for support ULT.
// [Files]        NBDxe.c;
//
// 18    10/14/12 5:17a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Follow SA RC 0.71.
// [Files]        NBPei.c, NBDxe.c; NBGeneric.c; NBCspLib.h; NBSetup.c;
// Nb.sd; GetSetupData.c
//
// 17    10/14/12 12:22a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]   Update by XTU4.0.
// [Files]        NBPei.c, NBDxe.c, NBCspLib.h, NBGeneric.c
// [TAG]          None
// [Severity]     Important
// [Description]  Follow Update by Mahobay.
// [Files]        NBPei.c, NBDxe.c;
//
// 16    9/28/12 4:12a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   BDAT function support.
// [Files]         NB.sd, NBDxe.c, NBPEI.c, SystemAgent.sdl,
// BdatAccessHandler.sdl
//
// 15    9/12/12 6:17a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Restore Performance Tuning the skip part
// [Files]         NBDxe.c
//
// 14    8/31/12 2:32a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Update Board ID for Haswell platform.
// [Files]         NBDxe.c
//
// 13    8/24/12 8:13a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Corrected GTT reference define.
// [Files]         NBDxe.c, NBPEI.c
//
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Remove useless iME_SUPPORT.
// [Files]         NBDxe.c
//
// 12    8/14/12 4:32a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Change for SystemAgent RefCode Revision: 0.6.1.
// [Files]       NB.sdl, NB.sd, NBCSP.CIF, NBDxe.c, NB.ASL, SaAudio.asl
//
// 11    7/27/12 8:38a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] IGfx Fource Disable Support.
// [Files]       GetSetupData.c, NB.sdl, NB.sd, NB.uni, NbSetupData.h,
// NBDxe.c, NBPEI.c
//
// [TAG]         None
// [Category]    Improvement
// [Description] Adjusted NB policy debault.
// [Files]       NB.sd, NBDxe.c
//
// [TAG]         None
// [Category]    Improvement
// [Description] Change to before Dxe SaInit to set maximum payload.
// [Files]       NBDxe.c
//
// 10    7/03/12 6:44a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Change for SystemAgent RefCode Revision: 0.6.0.
// [Files]       NBPEI.DXS, NB.sd, NBDxe.c, NBPEI.c
//
// 9     7/03/12 6:39a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Change the Save/Restore NB Registers position.
// [Files]       NB.ASL, NBAcpi.c, NBDxe.c
//
// 8     6/14/12 4:56a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Set Max Payload Size for EDS.
// [Description]   NBDxe.c
//
// 7     6/14/12 4:55a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Fix some devices work abnormal in the PEG slot.
// [Description]   NBDxe.c
//
// 6     4/26/12 2:52a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Adjust Intel System Agent module the Setup item and
// Policy.
// [Description]   GetSetupData.c, NB.sdl, NB.sd, NB.uni, NBDxe.c,
// NBPEI.c,
//                 NBSetup.c, NBSetupReset.c, NbSetupData.h
//
// 5     4/05/12 5:45a Yurenlai
// [TAG]         None
// [Category]    New Feature
// [Severity]    Normal
// [Description] Enabled GDXC feature.
// [Files]       NBDxe.c, NBPEI.c
//
// 3     4/05/12 5:12a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Severity]    Important
// [Description] Correct the Memory Info.
// [Files]       NBDxe.c
//
// 2     4/05/12 2:34a Yurenlai
// [TAG]  		EIP87103
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change for SystemAgent RefCode Revision: 0.5.5 .
// [Files]  		NBDxe.c, NBPEI.c, NBSMI.C, NBGeneric.cm NB.sd, NBSetup.c,
// GetSetupData.c, NbSetupData.h
//
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBDXE.C
//
// Description: This file contains code for North Bridge initialization
//              in the DXE stage
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Efi.h>
#include <Token.h>
#include <DXE.h>
#include <AmiDxeLib.h>
#include <AmiHobs.h>
#include <Setup.h>
#include <AmiCspLib.h>
#include <PciBus.h>
//#include "NbS3Save.h"
#include <Acpi20.h>
#include <AMIVfr.h>
#include <ppi\NBPPI.h>
// Consumed Protocols
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\NBPlatformData.h>

#if ACPI_SUPPORT
 #if defined(PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010014)
 #include <Protocol\AcpiSystemDescriptionTable.h>
 #else
 #include <Protocol\AcpiSupport.h>
 #endif
#endif

#define _SA_COMMON_DEFINITIONS_H_
#include <Protocol\SaPlatformPolicy\SaPlatformPolicy.h>
#include <Protocol\AmiUsbController.h>
#include <SaDataHob\SaDataHob.h>
#include <Hob.h>
#include "MemInfoHob.h"
#include <Protocol\MemInfo\MemInfo.h>

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
#include <PerfTune.h>
#include <Protocol\PerfTuneProtocol.h>
#endif
#endif

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
#include <Protocol\Wdt\Wdt.h>
#endif

#include <Protocol\PchS3Support\PchS3Support.h>

#if NB_ERROR_LOG_SUPPORT
#include <Protocol\GenericElog.h>
#endif

#include <Protocol\ConsoleControl.h>
#include <Protocol\SmBus.h>
#include <AmiLoadCsmPolicy.h>

#include <SaGlobalNvsArea\SaGlobalNvsArea.h>
#include <Protocol\GlobalNvsArea\GlobalNvsArea.h>

#ifndef EFI_SIGNATURE_16
#define EFI_SIGNATURE_16(A, B)  ((A) | (B << 8))
#endif

#ifndef EFI_SIGNATURE_32
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))
#endif

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

#ifndef SMM_SUPPORT
  #define SMM_SUPPORT 0
#endif

#define NB_TEMP_PCI_BUS         0x10

// Macro Definition(s)

// Type Definition(s)
typedef struct {
    UINT8 Bus;
    UINT8 Dev;
    UINT8 Fun;
    VOID *Process;
} DEVICES_AFTER_PCIIO;


#define RC_EFI_ACPI_VARIABLE_GUID \
  { \
    0xc020489e, 0x6db2, 0x4ef2, 0x9a, 0xa5, 0xca, 0x6, 0xfc, 0x11, 0xd3, 0x6a \
  }

#define EFI_PCI_ENUMERATION_COMPLETE_GUID \
  {  \
   0x30cfe3e7, 0x3de1, 0x4586, { 0xbe, 0x20, 0xde, 0xab, 0xa1, 0xb3, 0xb7, 0x93  } \
  }

typedef struct {
    ///
    /// Acpi Related variables
    ///
    EFI_PHYSICAL_ADDRESS  AcpiReservedMemoryBase;
    UINT32                AcpiReservedMemorySize;
    EFI_PHYSICAL_ADDRESS  S3ReservedLowMemoryBase;
    EFI_PHYSICAL_ADDRESS  AcpiBootScriptTable;
    EFI_PHYSICAL_ADDRESS  RuntimeScriptTableBase;
    EFI_PHYSICAL_ADDRESS  AcpiFacsTable;
    UINT64                SystemMemoryLength;
    ACPI_CPU_DATA         AcpiCpuData;
    ///
    /// VGA OPROM to support Video Re-POST for Linux S3
    ///
    EFI_PHYSICAL_ADDRESS  VideoOpromAddress;
    UINT32                VideoOpromSize;

    ///
    /// S3 Debug extension
    ///
    EFI_PHYSICAL_ADDRESS  S3DebugBufferAddress;
    EFI_PHYSICAL_ADDRESS  S3ResumeNvsEntryPoint;
} RC_ACPI_VARIABLE_SET;


// Function Prototype(s)

EFI_STATUS NBDXE_BoardInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable,
    IN NB_SETUP_DATA        *SetupData
);

VOID NbInitAfterDeviceInstall (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

VOID InitNbRegsBeforeBoot (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

VOID InitRcAcpiVariableSet(
    IN EFI_EVENT Event,
    IN VOID *Context
);

EFI_STATUS InstallNbMemoryInfo (
    IN EFI_SYSTEM_TABLE *SystemTable
);

VOID CreateNbAcpiComponent ( VOID );

EFI_STATUS NbSmmInit (
    IN EFI_EVENT        Event,
    IN VOID             *Context);

#ifdef CSM_OPRROM_POLICY_GUID
VOID NbCheckOprom (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);
#endif

VOID NbSetupNvramUpdatedCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

VOID NbPciEnumerationCompleteProtocolCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

VOID NbExitPmAuthProtocolCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

EFI_STATUS InstallDxePlatformSaPolicy (VOID);

EFI_STATUS
RmrrUpdateCallback (
  IN EFI_EVENT          Event,
  IN VOID               *Context
);

EFI_STATUS NBDXE_ShadowRam (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
);

// (P20121012A) >> Update XTU 4.0
EFI_STATUS NbReportXmpInfo(
  IN EFI_EVENT          Event,
  IN VOID               *Context
);

typedef struct {
  UINT32           tCK;
  MrcFrequency  DDRFreq;
  UINT8            RefClkFlag;  // 0 = invalid freq. 1 = valid only at 133 RefClk, 2 = valid only at 100 RefClk, 3 = valid at both.
} NbTRangeTable;

typedef struct {
  MrcFrequency  DDRFreq;
  MrcTiming     TimingData;
} NbXmpProfileData;

typedef struct {
  NbXmpProfileData XmpProfileTiming[2];
} XmpDimmData;

//NbXmpProfileData                XmpProfileTiming[2] = {0};
//XmpDimmData                     XmpDimm[4] = {0};
//XmpDimmData                     XmpChannel[2] = {0};

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
VOID NbXTUSetGACITable(
  IN EFI_EVENT Event,
  IN VOID *Context
);

DDDT_PRESENT_FLAG_HOB	 *gDddtPresentFlagHob = NULL;
#endif
#endif
// (P20121012A) << Update XTU 4.0
//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo = NULL;
AMI_S3_SAVE_PROTOCOL            *gBootScript = NULL;
EFI_EVENT                       gEvent;
EFI_EVENT                       gEvtBootScript;
VOID                            *gNBInitNotifyReg = NULL;
VOID                            *gUpdateCsmProtocolNotifyReg = NULL;
NB_SETUP_DATA                   *gNbSetupData = NULL;
VOID                            *gCsmOpromReg = NULL;
VOID                            *gNbSetupNvramUpdatedReg = NULL;
VOID                            *gPciEnumerationCompleteProtocolReg = NULL;
VOID                            *gNbExitPmAuthProtocolReg = NULL;
VOID                            *gInterface = NULL;
MEM_INFO_PROTOCOL               gMemInfoHobProtocol;
NB_PLATFORM_DATA                NBPlatformData = {0};
UINT32                          gBClkFrequency = 0;
BOOLEAN                         gHideIGFXdevice;
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
PERF_TUNE_ASL_PROTOCOL          *gPerfTuneAslProtocol = NULL;
#endif
#endif
MrcProfile                      MemoryProfile = 0;
MrcTiming                       *NBMrcTimingData;


// GUID Definition(s)

EFI_GUID gEfiPciRootBridgeIoProtocolGuid = \
                                         EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
EFI_GUID gEfiPciIoProtocolGuid           = EFI_PCI_IO_PROTOCOL_GUID;
EFI_GUID gSetupNvramUpdatedGuid          = AMITSE_NVRAM_UPDATE_GUID;
EFI_GUID gHobListGuid                    = HOB_LIST_GUID;
//EFI_GUID gMrcS3ResumeDataHobGuid       = AMI_MRC_S3_RESUME_DATA_HOB_GUID;
EFI_GUID gDxePlatformSaPolicyGuid        = DXE_PLATFORM_SA_POLICY_GUID;
EFI_GUID gMemInfoProtocolGuid            = MEM_INFO_PROTOCOL_GUID;
EFI_GUID gMemRestoreDataGuid             = EFI_MEMORY_RESTORE_DATA_GUID;
EFI_GUID gAmiNbPegGen3PresetSearchGuid   = AMI_NB_PEG_GEN3_PRESET_SEARCH_GUID;
EFI_GUID gMrcInfoHobGuid                 = AMI_MRC_INFO_HOB_GUID;
EFI_GUID gSetupGuid                      = SETUP_GUID;
EFI_GUID gAmiLoadCsmGuid                 = AMI_LOAD_CSM_GUID;
EFI_GUID gConOutStartedCheckGuid         = CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID;
EFI_GUID gExitPmAuthProtocolGuid         = EXIT_PM_AUTH_PROTOCOL_GUID;
EFI_GUID gEfiSmbusProtocolGuid           = EFI_SMBUS_HC_PROTOCOL_GUID;
EFI_GUID gAmiNbPegInfoGuid               = AMI_NB_PEG_INFO_GUID;
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
EFI_GUID gPerfTuneAslProtocolGuid         = PERF_TUNE_ASL_PROTOCOL_GUID;
EFI_GUID gAmiPerfTuneDataHobGuid          = AMI_PERF_TUNE_DATA_HOB_GUID;
EFI_GUID gAmiInternalFactoryTdcTdpHobGuid = AMI_INTERNAL_FACTORY_TDC_TDP_HOB_GUID;
#endif
#endif

#ifdef CSM_OPRROM_POLICY_GUID
EFI_GUID gCsmOpromPolicyGuid = CSM_OPRROM_POLICY_GUID;
#endif

#if NB_ERROR_LOG_SUPPORT
EFI_GUID gElogProtocolGuid        = EFI_SM_ELOG_PROTOCOL_GUID;
#endif

extern EFI_GUID gSaDataHobGuid;
extern EFI_GUID gEfiSmmAccessProtocolGuid;

#if (CORE_VERSION >= 4600)
//----------------------------------------------------------------------------
//THIS TABLE MUST BE FILLED WITH RESOURCE REGIONS DECODED BY THE NB FOR ITSELF
//!!! NOTE :Use Attributes field == -1 to mark an IO Space Resource.
//          you must provide valid attributes for Memory Mapped IO regions.
//----------------------------------------------------------------------------

CSP_RES_ITEM gNbCspResTable[] = {
//----------------------------------------------------------------------------
// UINT64 ResBase  UINTN ResLength  GCD_MEMORY_TYPE ResType  UINT64 Attributes
//----------------------------------------------------------------------------
//Add PCI Express region
{ PCIEX_BASE_ADDRESS,   PCIEX_LENGTH,EfiGcdMemoryTypeMemoryMappedIo , \
                                         (EFI_MEMORY_UC|EFI_MEMORY_RUNTIME)},
//Local APICs dedicated Space
{ LOCAL_APIC_BASE   ,   0x00001000  ,EfiGcdMemoryTypeMemoryMappedIo , \
                                         (EFI_MEMORY_UC|EFI_MEMORY_RUNTIME)},
//Egress Port Base Address Region
{ NB_EP_BASE_ADDRESS,   4*1024      ,EfiGcdMemoryTypeMemoryMappedIo , \
                                                               EFI_MEMORY_UC},
//MCH Memory Mapped Base Address Region
{ NB_MCH_BASE_ADDRESS,  16*1024     ,EfiGcdMemoryTypeMemoryMappedIo , \
                                                               EFI_MEMORY_UC},
//Root Complex Base Address Region
{ NB_DMI_BASE_ADDRESS,   4*1024     ,EfiGcdMemoryTypeMemoryMappedIo , \
                                                               EFI_MEMORY_UC},
//Edram Base Address Region
{ NB_DERAM_BASE_ADDRESS, 16*1024    ,EfiGcdMemoryTypeMemoryMappedIo , \
                                                               EFI_MEMORY_UC},
//GDXC Base Address Region
{ NB_GDXC_BASE_ADDRESS,   4*1024    ,EfiGcdMemoryTypeMemoryMappedIo , \
                                                               EFI_MEMORY_UC},
//Here Goes Reserved IO Space
//IO Used for PCI Config access
{ NB_PCICFG_SPACE_INDEX_REG , 8     ,EfiGcdIoTypeIo         ,       -1      },

};

UINTN   gNbCspResCount = sizeof(gNbCspResTable) / sizeof(CSP_RES_ITEM);

#endif


DEVICES_AFTER_PCIIO gDevicesTable[] = {
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN,  NULL },
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN1, NULL },
    { PCIEBRN_BUS, PCIEBRN_DEV,  PCIEBRN_FUN2, NULL },
    { 0xFF,         0xFF,         0xFF,         NULL }
};

UINTN gEventCount = sizeof(gDevicesTable) / sizeof(DEVICES_AFTER_PCIIO);

PCIE_ASPM_DEV_INFO mPcieAspmDevsOverride[] = {
  ///
  /// Tekoa w/o iAMT
  ///
  {0x8086, 0x108b, 0xff, 2, 2},
  ///
  /// Tekoa A2
  ///
  {0x8086, 0x108c, 0x00, 0, 0},
  ///
  /// Tekoa others
  ///
  {0x8086, 0x108c, 0xff, 2, 2},
  ///
  /// Vidalia
  ///
  {0x8086, 0x109a, 0xff, 2, 2},
  ///
  /// 3945ABG
  ///
  {0x8086, 0x4222, 0xff, 2, 3},
  ///
  /// 3945ABG
  ///
  {0x8086, 0x4227, 0xff, 2, 3},
  ///
  /// 3945ABG
  ///
  {0x8086, 0x4228, 0xff, 2, 3},
  ///
  /// End of table
  ///
  {SA_PCIE_DEV_END_OF_TABLE, 0, 0, 0, 0}
};

PCIE_LTR_DEV_INFO mPcieLtrDevsOverride[] = {
  ///
  /// Place holder for PCIe devices with correct LTR requirements
  ///
  ///
  /// End of table
  ///
  {SA_PCIE_DEV_END_OF_TABLE, 0, 0, 0, 0}
};
// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//----------------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBDXE_Init
//
// Description: This function is the entry point for this DXE. This function
//              initializes the chipset NB before PCI Bus enumeration.
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBDXE_Init (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    CPUINFO_HOB         *CpuInfoHob = NULL;
    EFI_GUID            AmiCpuinfoHobGuid = AMI_CPUINFO_HOB_GUID;
    UINT8               i = 0;
    UINTN               VariableSize;
    EFI_EVENT           Event;
    VOID                *HobData;
    VOID                *VariableData;
    UINTN               S3DataOffset;
    UINT16              McDeviceId;
    UINT16              LpcDeviceId;
    VOID                *Protocol = NULL;
    VOID                *NotifyReg = NULL;
    UINT32              Attributes = 0;         // [ EIP167027 ]


    InitAmiLib(ImageHandle, SystemTable);

    PROGRESS_CODE (DXE_NB_INIT);

    Status = pBS->LocateProtocol( &gEfiPciRootBridgeIoProtocolGuid, \
                                  NULL, \
                                  &gPciRootBridgeIo );
    ASSERT_EFI_ERROR(Status);

    Status = pBS->LocateProtocol( AMI_S3_SAVE_PROTOCOL_GUID, \
                                  NULL, \
                                  &gBootScript );
    ASSERT_EFI_ERROR(Status);

    VariableData    = NULL;
    S3DataOffset = 0;

    HobData = (EFI_HOB_GENERIC_HEADER *) GetEfiConfigurationTable (pST, &gHobListGuid);
    if (!HobData)ASSERT_EFI_ERROR (EFI_NOT_FOUND);

    Status = FindNextHobByGuid (&gSaDataHobGuid, &HobData);
    if (Status == EFI_SUCCESS) {

      // Use the hob to save PegGen3PresetSearch Configuration Data
      S3DataOffset = (UINTN) &(((SA_DATA_HOB *) 0)->PegData);

      //Status = pRS->SetVariable (             // [ EIP167027 ]
      //              L"PegGen3PresetSearchData",
      //              &gAmiNbPegGen3PresetSearchGuid,
      //              (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS),
      //              sizeof(SA_PEG_DATA),
      //             (UINT8 *) HobData + S3DataOffset
      //              );
      Status = pRS->SetVariable (
                    L"PegGen3PresetSearchData",
                    &gAmiNbPegGen3PresetSearchGuid,
                    (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS),
                    sizeof(SA_PEG_DATA),
                   (UINT8 *) HobData + S3DataOffset
                    );
      ASSERT_EFI_ERROR(Status);

    }

    HobData = (EFI_HOB_GENERIC_HEADER *) GetEfiConfigurationTable (pST, &gHobListGuid);
    if (!HobData)ASSERT_EFI_ERROR (EFI_NOT_FOUND);

    Status = FindNextHobByGuid (&gMemRestoreDataGuid, &HobData);
    if (Status == EFI_SUCCESS) {

      // Use the hob to save Memory Configuration Data
      S3DataOffset = (UINTN) &(((HOB_SAVE_MEMORY_DATA *) 0)->MrcData.SysSave);

      //Status = pRS->SetVariable (             // [ EIP167027 ]
      //              L"MrcS3Resume",
      //              &gMemRestoreDataGuid,
      //              (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS),
      //              sizeof(SysSave),
      //             (UINT8 *) HobData + S3DataOffset
      //              );
      Status = pRS->SetVariable (
                    L"MrcS3Resume",
                    &gMemRestoreDataGuid,
                    (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS),
                    sizeof(SysSave),
                   (UINT8 *) HobData + S3DataOffset
                    );
      ASSERT_EFI_ERROR(Status);

    }

    // Set DRAM Initialization Bit.             // [ EIP161790 ]
    if ((READ_PCI8_SB(SB_REG_GEN_PMCON_2) & BIT07) == 0)
    {
        SET_PCI8_SB(SB_REG_GEN_PMCON_2, BIT07); // 0xA2
    }

    // Read the NB Setup Data
    VariableSize = sizeof (NB_SETUP_DATA);
    Status = pBS->AllocatePool( EfiBootServicesData, \
                                VariableSize, \
                                &gNbSetupData );
    ASSERT_EFI_ERROR(Status);

    GetNbSetupData( pRS, gNbSetupData, FALSE );

    // Read the NB Platform Data
    VariableSize = sizeof (NB_PLATFORM_DATA);
    //Status = pRS->GetVariable (               // [ EIP167027 ]
    //          L"NBPlatformData",
    //          &gSetupGuid,
    //          NULL,
    //          &VariableSize,
    //          &NBPlatformData
    //          );
    Status = pRS->GetVariable (
              L"NBPlatformData",
              &gSetupGuid,
              &Attributes,
              &VariableSize,
              &NBPlatformData
              );
    if (EFI_ERROR(Status))
        Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;

   // Check CPU is Support IGFX.
   NBPlatformData.IGFXCapability = (READ_PCI32_NB (R_SA_MC_CAPID0_A_OFFSET) & BIT11) ? FALSE : TRUE;

   NBPlatformData.PegAvailable = (GetPchSeries() == PchLp) ? FALSE : TRUE;
   // Check IGFX is Available.
   NBPlatformData.IGFXAvailable = (READ_PCI32_IGD (R_SA_IGD_VID) != 0xFFFFFFFF) ? TRUE : FALSE;

#if defined NB_IGFX_FORCE_DISABLE_SUPPORT && NB_IGFX_FORCE_DISABLE_SUPPORT == 1
    if(gNbSetupData->IGfxForceDisable == 1)
        NBPlatformData.IGFXAvailable = 0;
#endif // NB_IGFX_FORCE_DISABLE_SUPPORT

   // Read MC device ID
   McDeviceId = READ_PCI16_NB(R_SA_MC_DEVICE_ID);

   // Read PCH device ID
   LpcDeviceId = READ_PCI16_SB(R_PCH_LPC_DEVICE_ID);

   NBPlatformData.PresentCPU = 2;

   // Mobile - 0; Desktop - 2; UpServer - 3; FlavorWorkStation - 4;
   if(IS_SA_DEVICE_ID_MOBILE(McDeviceId)) {
       NBPlatformData.UserBoard = FlavorMobile;
   } else if(IS_SA_DEVICE_ID_DESKTOP (McDeviceId) | IS_SA_DEVICE_ID_SERVER(McDeviceId)) {
       if(IS_PCH_LPT_LPC_DEVICE_ID_WS (LpcDeviceId)) {
           NBPlatformData.UserBoard = FlavorWorkStation;
       } else if(IS_PCH_LPT_LPC_DEVICE_ID_SERVER (LpcDeviceId)) {
           NBPlatformData.UserBoard = FlavorUpServer;
       } else {
           NBPlatformData.UserBoard = FlavorDesktop;
       }
   } else {
       NBPlatformData.UserBoard = FlavorDesktop;
   }

   Status = NBDXE_BoardInit(ImageHandle, SystemTable, gNbSetupData);

   //
   // Detect if CSM is exist. If it's not, the shawdow ram can be set.
   //
   Status = pBS->LocateProtocol( &gAmiLoadCsmGuid, \
                                 NULL, \
                                 &gInterface );
   if(EFI_ERROR(Status))
   {
     Status = NBDXE_ShadowRam(ImageHandle, SystemTable);
   }

#if PciHostBridge_SUPPORT
    CreateNbAcpiComponent();
#endif

    Status = RegisterProtocolCallback( &gEfiPciIoProtocolGuid, \
                                       NbInitAfterDeviceInstall, \
                                       NULL, &gEvent, &gNBInitNotifyReg );
    ASSERT_EFI_ERROR(Status);

    Status = RegisterProtocolCallback( &gConOutStartedCheckGuid,
                                       NbPciEnumerationCompleteProtocolCallback,
                                       NULL, &gEvent, &gPciEnumerationCompleteProtocolReg );
    ASSERT_EFI_ERROR(Status);

    Status = RegisterProtocolCallback( &gExitPmAuthProtocolGuid, \
                                       NbExitPmAuthProtocolCallback, \
                                       NULL, \
                                       &Event, \
                                       &gNbExitPmAuthProtocolReg );
    ASSERT_EFI_ERROR(Status);

    Status = CreateReadyToBootEvent( TPL_NOTIFY, InitNbRegsBeforeBoot, \
                                     NULL, &gEvent );
    ASSERT_EFI_ERROR(Status);

    Status = CreateReadyToBootEvent(
                    (TPL_CALLBACK - 1),
                    InitRcAcpiVariableSet,
                    NULL,
                    &Event);
    ASSERT_EFI_ERROR(Status);

    Status = InstallDxePlatformSaPolicy ();
    ASSERT_EFI_ERROR(Status);

    Status = InstallNbMemoryInfo ( SystemTable );
    ASSERT_EFI_ERROR(Status);

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
    if(!EFI_ERROR(Status))
    {
        EFI_EVENT Event;
        VOID *Reg;

        Status = pBS->LocateProtocol (&gPerfTuneAslProtocolGuid, NULL, &gPerfTuneAslProtocol);
        if(Status == EFI_SUCCESS)
        {
            NbXTUSetGACITable(NULL,NULL);
        }else{
            //Create event for Notify XTU setting
            Status = RegisterProtocolCallback(
                            &gPerfTuneAslProtocolGuid,
                            NbXTUSetGACITable,
                            NULL, &Event, &Reg);
            ASSERT_EFI_ERROR(Status);
        }
    }
#endif
#endif

#ifdef CSM_OPRROM_POLICY_GUID
    Status = RegisterProtocolCallback( &gCsmOpromPolicyGuid, \
                                       NbCheckOprom, \
                                       NULL, \
                                       &Event, \
                                       &gCsmOpromReg );

    ASSERT_EFI_ERROR(Status);
#endif

    Status = RegisterProtocolCallback( &gSetupNvramUpdatedGuid,
                                       NbSetupNvramUpdatedCallback,
                                       NULL,
                                       &Event,
                                       &gNbSetupNvramUpdatedReg );

#if (CORE_VERSION >= 4600)
    Status = LibAllocCspResource( gNbCspResTable, \
                                  gNbCspResCount, \
                                  ImageHandle, \
                                  SystemTable );
#endif

#if SMM_SUPPORT
    Status = pBS->LocateProtocol(&gEfiSmmAccessProtocolGuid, NULL, &Protocol);
    if (EFI_ERROR(Status))
    {
        Status = RegisterProtocolCallback(
                        &gEfiSmmAccessProtocolGuid,
                        NbSmmInit,
                        NULL,
                        &Event,
                        &NotifyReg);
        ASSERT_EFI_ERROR(Status);
    }
    else
    {
        Status = NbSmmInit(NULL, NULL);
        ASSERT_EFI_ERROR(Status);
    }
#endif

#ifndef OVERRIDE_FOR_SET_MAX_PAYLOAD
  {
    UINTN       PegAddress;
    UINT8       PegBus;
    UINT8       PegDev;
    UINT8       PegFun;
    UINTN       i;

    for ( i = 0; gDevicesTable[i].Bus != 0xff; i++)
    {
        PegBus = gDevicesTable[i].Bus;
        PegDev = gDevicesTable[i].Dev;
        PegFun = gDevicesTable[i].Fun;

        if (READ_PCI32 (PegBus, PegDev, PegFun, PCI_VID) == 0xFFFFFFFF) continue;

        // Haswell EDS 2.19.35
        // Default indicates 256B max supported payload for
        // Transaction Layer Packets (TLP) for x16 PEG only.
        // x8 and x4 PEG are limited to 128B support.
        PegAddress = NB_PCIE_CFG_ADDRESS(PegBus, PegDev, PegFun, 0);
        if (((READ_MMIO16 (PegAddress + R_SA_PEG_LSTS_OFFSET) & 0x01F0) >> 4) != 0x10)
            RESET_MMIO8 (PegAddress + R_SA_PEG_DCAP_OFFSET, BIT0 + BIT1 + BIT2);
    }
  }
#endif // OVERRIDE_FOR_SET_MAX_PAYLOAD

    // Save SETUP variables.
    //Status = pRS->SetVariable (               // [ EIP167027 ]
    //  L"NBPlatformData",
    //  &gSetupGuid,
    //  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
    //  sizeof (NB_PLATFORM_DATA),
    //  &NBPlatformData
    //  );
    Status = pRS->SetVariable (
      L"NBPlatformData",
      &gSetupGuid,
      Attributes,
      sizeof (NB_PLATFORM_DATA),
      &NBPlatformData
      );
    ASSERT_EFI_ERROR (Status);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitNbRegsBeforeBoot
//
// Description: This function can initialize any NB registers before DXE
//              stage exiting.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitNbRegsBeforeBoot (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
//#if defined   Remove_SaSsdt_Data_To_Dsdt && Remove_SaSsdt_Data_To_Dsdt
  UINT32                     Index;
  EFI_ACPI_SUPPORT_PROTOCOL  *As;
  FACP_20                    *Table = NULL;
  EFI_ACPI_TABLE_VERSION     Version;
  UINTN                      Handle;
  ACPI_HDR                   *DsdtPtr = NULL;
  EFI_STATUS                 Status;
  ASL_OBJ_INFO               ObjInfo;
  UINT16                     ASLDeviceOP;
  UINT8                      ASLDeviceOPLength;
  UINT8                      *ptr;
  UINT8                      i;
  UINT8                      j;
#if defined   Remove_SaSsdt_Data_To_Dsdt && Remove_SaSsdt_Data_To_Dsdt
  UINT8                      *GlobalSaptr, *SAptr;
  SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL    *SaGlobalNvsArea, *GlobalSaNvsArea;
  EFI_GUID                gSaGlobalNvsAreaProtocolGuid  = SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL_GUID;
  EFI_GUID                gEfiGlobalSaNvsAreaProtocolGuid = EFI_GLOBAL_SANVS_AREA_PROTOCOL_GUID;
#endif
  UINT8                      *ptr1;
  UINT16                     PXSXASLDeviceOP;
  UINT8                      PXSXASLDeviceOPLength;
  UINT8                      HPMEASLMethodOPLength;
  UINT16                     HPMEASLMethodOPLength16;
  UINT16                     ASLDeviceOPLength16;
  UINT32                     *Signature;

#if NB_ERROR_LOG_SUPPORT == 1
#if NB_ECC_ERROR_LOG_SUPPORT == 1

    if(gNbSetupData->EccSupport) {

        if (((READ_MEM32_MCH(0x5004) & (BIT24 | BIT25)) != 0) ||
           ((READ_MEM32_MCH(0x5008) & (BIT24 | BIT25)) != 0))
        {
             RW_MEM32_MCH(0x40B8, 0, (BIT14 | BIT16 | BIT17));
             RW_MEM32_MCH(0x44B8, 0, (BIT14 | BIT16 | BIT17));

             // Disable Error and SCI Commands
             RW_PCI16_NB(0xCA, 0, (BIT00 | BIT01));
             RW_PCI16_NB(0xCE, 0, (BIT00 | BIT01));

             // Enable SMI Command
             //SET_PCI8_NB(0xC8, BIT00);
             RW_PCI16_NB(0xCC, (BIT00 | BIT01), 0);
        }

    }

#endif
#endif

#if defined   Remove_SaSsdt_Data_To_Dsdt && Remove_SaSsdt_Data_To_Dsdt
    ///
    ///  Locate the SA SSDT NVS Protocol.
    ///
    Status = pBS->LocateProtocol (
                    &gSaGlobalNvsAreaProtocolGuid,
                    NULL,
                    &SaGlobalNvsArea
                    );
    ASSERT_EFI_ERROR (Status);

    //
    //  Locate the SA Global NVS Protocol.
    //
    Status = pBS->LocateProtocol (
                    &gEfiGlobalSaNvsAreaProtocolGuid,
                    NULL,
                    &GlobalSaNvsArea
                    );
    ASSERT_EFI_ERROR (Status);

    // Update SA SSDT GNVS data to Global DSDT SA GNVS
    SAptr = (UINT8*)(SaGlobalNvsArea->Area);
    GlobalSaptr = (UINT8*)(GlobalSaNvsArea->Area);
    TRACE((TRACE_ALWAYS, "Global SA GNVS PTR=0x%08X, SA SSDT GNVS PTR=0x%08X\n", GlobalSaptr, SAptr));

    for (Index = 0; Index < sizeof (SYSTEM_AGENT_GLOBAL_NVS_AREA); Index++) {
          *(UINT8*)(GlobalSaptr + Index) = (UINT8)*(UINT8*)(SAptr + Index);
    }

#endif

    // It must be only one instance of such protocol
    Status = pBS->LocateProtocol(&gEfiAcpiSupportGuid, NULL, &As);
    if(EFI_ERROR(Status)) {
        TRACE((-1, "ACPI Support Protocol is not ready for NB components\n"));
        return;
    }
    TRACE((-1,"NB Locate Protocol(ACPISupport)- %r Success\n", Status));

    // Find DSDT ACPI Table
    for (Index = 0; Index < ACPI_RSDT_TABLE_NUM; Index++) {
      Status = As->GetAcpiTable(As, Index, &Table, &Version, &Handle);
      if (EFI_ERROR(Status)) break;//no more tables left
      if ((Table->Header.Signature == FACP_SIG) && (DsdtPtr == NULL)) {
          DsdtPtr = (ACPI_HDR*)Table->DSDT;

          TRACE((-1, "NBDxe: Found DSDT Table at 0x%08X\n", DsdtPtr));


          break;
      }
    }

    Status = GetAslObj( (UINT8*)(DsdtPtr + 1), DsdtPtr->Length - sizeof(ACPI_HDR) - 1,
							"P0P2", otDevice, &ObjInfo );

    if (!EFI_ERROR(Status))
    {
      ptr = (UINT8*)(ObjInfo.DataStart) - 7;
      (UINT16)ASLDeviceOP = *(UINT32*)(ptr);
      (UINT8)ASLDeviceOPLength = *(UINT32*)(ptr + 2);

      TRACE((TRACE_ALWAYS, "SA POP2 Device PTR=0x%08X, ASLDeviceOP=0x%X, ASLDeviceOPLength=0x%X\n", ptr, (UINT16)ASLDeviceOP, (UINT8)ASLDeviceOPLength));
      if (ASLDeviceOP == 0x825B)  // Is DeviceOP ?
      {
        for ( i = 0; i < ASLDeviceOPLength + 2; i++) {
          *(UINT8*)(ptr + i) = 0;
        }
      }
    }

    Status = GetAslObj( (UINT8*)(DsdtPtr + 1), DsdtPtr->Length - sizeof(ACPI_HDR) - 1,
							"P0PA", otDevice, &ObjInfo );

    if (!EFI_ERROR(Status))
    {
      ptr = (UINT8*)(ObjInfo.DataStart) - 7;
      (UINT16)ASLDeviceOP = *(UINT32*)(ptr);
      (UINT8)ASLDeviceOPLength = *(UINT32*)(ptr + 2);

      TRACE((TRACE_ALWAYS, "SA POPA Device PTR=0x%08X, ASLDeviceOP=0x%X, ASLDeviceOPLength=0x%X\n", ptr, (UINT16)ASLDeviceOP, (UINT8)ASLDeviceOPLength));
      if (ASLDeviceOP == 0x825B)  // Is ASL DeviceOP ?
      {
        for ( i = 0; i < ASLDeviceOPLength + 2; i++) {
          *(UINT8*)(ptr + i) = 0;
        }
      }
    }

    Status = GetAslObj( (UINT8*)(DsdtPtr + 1), DsdtPtr->Length - sizeof(ACPI_HDR) - 1,
							"P0PB", otDevice, &ObjInfo );

    if (!EFI_ERROR(Status))
    {
      ptr = (UINT8*)(ObjInfo.DataStart) - 7;
      (UINT16)ASLDeviceOP = *(UINT32*)(ptr);
      (UINT8)ASLDeviceOPLength = *(UINT32*)(ptr + 2);

      TRACE((TRACE_ALWAYS, "SA POPB Device PTR=0x%08X, ASLDeviceOP=0x%X, ASLDeviceOPLength=0x%X\n", ptr, (UINT16)ASLDeviceOP, (UINT8)ASLDeviceOPLength));
      if (ASLDeviceOP == 0x825B)  // Is ASL DeviceOP ?
      {
        for ( i = 0; i < ASLDeviceOPLength + 2; i++) {
          *(UINT8*)(ptr + i) = 0;
        }
      }
    }

   if (GetPchSeries() == PchLp) {
    if(gNbSetupData->PrimaryDisplay == 4) {

    Status = GetAslObj( (UINT8*)(DsdtPtr + 1), DsdtPtr->Length - sizeof(ACPI_HDR) - 1,
							"RP05", otDevice, &ObjInfo );
    if (!EFI_ERROR(Status))
    {
      ptr = (UINT8*)(ObjInfo.DataStart) - 8;
      (UINT16)ASLDeviceOP = *(UINT32*)(ptr);
      (UINT8)ASLDeviceOPLength = *(UINT32*)(ptr + 2);
      ASLDeviceOPLength16 = (ASLDeviceOPLength & 0x0F);
      (UINT8)ASLDeviceOPLength = *(UINT32*)(ptr + 3);
      ASLDeviceOPLength16 = (ASLDeviceOPLength << 4) | ASLDeviceOPLength16;

      TRACE((TRACE_ALWAYS, "RP05 Device PTR=0x%08X, ASLDeviceOP=0x%X, ASLDeviceOPLength=0x%X\n", ptr, (UINT16)ASLDeviceOP, (UINT16)ASLDeviceOPLength16));
      if (ASLDeviceOP == 0x825B)  // Is ASL DeviceOP ?
      {
          Status = GetAslObj( (UINT8*)(ptr + 1), ASLDeviceOPLength16 - sizeof(ACPI_HDR) - 1,
							     "_STA", otMethod, &ObjInfo );
          if (!EFI_ERROR(Status))
          {
             ptr1 = (UINT8*)(ObjInfo.DataStart) - 5;
             TRACE((TRACE_ALWAYS, "_STA Method PTR=0x%08X\n", ptr1));
             *(UINT8*)ptr1 = 'X';
          }

          //remove device PXSX
          Status = GetAslObj( (UINT8*)(ptr + 1), ASLDeviceOPLength16 - sizeof(ACPI_HDR) - 1,
							     "PXSX", otDevice, &ObjInfo );
          if (!EFI_ERROR(Status))
          {

             ptr1 = (UINT8*)(ObjInfo.DataStart) - 7;
             (UINT16)PXSXASLDeviceOP = *(UINT32*)(ptr1);
             (UINT8)PXSXASLDeviceOPLength = *(UINT32*)(ptr1 + 2);
             TRACE((TRACE_ALWAYS, "PXSX Device PTR=0x%08X, ASLDeviceOP=0x%X, ASLDeviceOPLength=0x%X\n", ptr1, (UINT16)PXSXASLDeviceOP, (UINT8)PXSXASLDeviceOPLength));

             if (PXSXASLDeviceOP == 0x825B)  // Is ASL DeviceOP ?
             {
               for ( i = 0; i < PXSXASLDeviceOPLength + 2; i++) {
               *(UINT8*)(ptr1 + i) = 0;
               }
             }
          }

          Status = GetAslObj( (UINT8*)(ptr + 1), ASLDeviceOPLength16 - sizeof(ACPI_HDR) - 1,
							     "HPME", otMethod, &ObjInfo );
          if (!EFI_ERROR(Status))
          {
             ptr1 = (UINT8*)(ObjInfo.DataStart) - 8;
            (UINT8)HPMEASLMethodOPLength = *(UINT32*)(ptr1 + 1);
            HPMEASLMethodOPLength16 = (HPMEASLMethodOPLength & 0x0F);
            (UINT8)HPMEASLMethodOPLength = *(UINT32*)(ptr1 + 2);
            HPMEASLMethodOPLength16 = (HPMEASLMethodOPLength << 4) | HPMEASLMethodOPLength16;
            TRACE((TRACE_ALWAYS, "HPME Method PTR=0x%08X,HPMEASLMethodOPLength16=0x%X\n", ptr1,(UINT16)HPMEASLMethodOPLength16));

             for ( i = 0; i < HPMEASLMethodOPLength16 ; i++) {
                Signature = (UINT32 *) (ptr1 + i);
                   //TRACE((TRACE_ALWAYS, "PXSX Notify PTR%d = 0x%08X\n", i,Signature));
                if(*Signature == EFI_SIGNATURE_32 ('P', 'X', 'S', 'X')){
                   TRACE((TRACE_ALWAYS, "PXSX Notify PTR = 0x%08X\n", Signature));
                   for ( j = 0; j < 7 ; j++) {
                      *(UINT8*)(ptr1 + i + j -1) = 0;
                   }
                }
             }
          }


      }
    }
    }// if(gNbSetupData->PrimaryDisplay == 4) {
   }//if (GetPchSeries() == PchLp)

    //Kill the Event
    pBS->CloseEvent(Event);

}

VOID InitRcAcpiVariableSet(
    IN EFI_EVENT Event,
    IN VOID *Context)
{
    EFI_STATUS Status;
    EFI_GUID mEfiAcpiVariableGuid = EFI_ACPI_VARIABLE_GUID;
    EFI_GUID mRcEfiAcpiVariableGuid = RC_EFI_ACPI_VARIABLE_GUID;
    ACPI_VARIABLE_SET *pAcpiVariableSet = NULL;
    RC_ACPI_VARIABLE_SET *pRcAcpiVariableSet = NULL;
    UINTN VariableSize = sizeof(UINT32);
    UINT32 Attributes;

    //Status = pRS->GetVariable (               // [ EIP167027 ]
    //                L"AcpiGlobalVariable",
    //                &mEfiAcpiVariableGuid,
    //                NULL,
    //                &VariableSize,
    //                &pAcpiVariableSet
    //                );
    Status = pRS->GetVariable (
                    L"AcpiGlobalVariable",
                    &mEfiAcpiVariableGuid,
                    &Attributes,
                    &VariableSize,
                    &pAcpiVariableSet
                    );
    if (EFI_ERROR(Status))
    {
        return;
    }

    Status = pBS->AllocatePool(
                    EfiACPIMemoryNVS,
                    sizeof(RC_ACPI_VARIABLE_SET),
                    &pRcAcpiVariableSet
                    );
    ASSERT_EFI_ERROR(Status);

    pBS->SetMem(pRcAcpiVariableSet, sizeof(RC_ACPI_VARIABLE_SET), 0);

    pRcAcpiVariableSet->AcpiReservedMemoryBase = pAcpiVariableSet->AcpiReservedMemoryBase;
    pRcAcpiVariableSet->AcpiReservedMemorySize = pAcpiVariableSet->AcpiReservedMemorySize;
    pRcAcpiVariableSet->S3ReservedLowMemoryBase = pAcpiVariableSet->S3ReservedLowMemoryBase;
    pRcAcpiVariableSet->AcpiBootScriptTable = pAcpiVariableSet->AcpiBootScriptTable;
    pRcAcpiVariableSet->RuntimeScriptTableBase = pAcpiVariableSet->RuntimeScriptTableBase;
    pRcAcpiVariableSet->AcpiFacsTable = pAcpiVariableSet->AcpiFacsTable[0];
    pRcAcpiVariableSet->SystemMemoryLength = pAcpiVariableSet->SystemMemoryLength;
    pRcAcpiVariableSet->AcpiCpuData = pAcpiVariableSet->AcpiCpuData;

    //Status = pRS->SetVariable(                // [ EIP167027 ]
    //                L"AcpiGlobalVariable",
    //                &mRcEfiAcpiVariableGuid,
    //                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
    //                sizeof(UINT64),
    //                &pRcAcpiVariableSet
    //                );
    Status = pRS->SetVariable(
                    L"AcpiGlobalVariable",
                    &mRcEfiAcpiVariableGuid,
                    Attributes,
                    sizeof(UINT64),
                    &pRcAcpiVariableSet
                    );
    ASSERT_EFI_ERROR(Status);

    //Kill the Event
    Status = pBS->CloseEvent(Event);
    ASSERT_EFI_ERROR(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetExtCapStrucAddr
//
// Description: This routine is called to get the 16-bit offset of a
//              structure which can be located using the PCI Extended
//              Capabilities Pointer mechanism.
//
// Input:       Bus       - The PCI bus number of the PCI device.
//              Dev       - The PCI device number of the PCI device.
//              Fun       - The PCI function number of the PCI device.
//              FindCapNo - The Extended Capability ID to be found.
//              CapPtr16  - The offset address of desired structure
//
// Output:      EFI_STATUS
//                  EFI_NOT_FOUND - The desired structure is not found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetExtCapStrucAddr (
    IN UINT8                Bus,
    IN UINT8                Dev,
    IN UINT8                Fun,
    IN UINT16               FindCapNo,
    OUT UINT16              *CapPtr16 )
{
    UINT32          Buffer32;

    *CapPtr16 = 0x100;

    Buffer32 = READ_PCI32(Bus, Dev, Fun, *CapPtr16);
    while (Buffer32 != 0xffffffff) {
        if ((UINT16)Buffer32 == FindCapNo) return EFI_SUCCESS;
        *CapPtr16 = (UINT16)((Buffer32 >> 20) & 0xfffc);
        if (*CapPtr16 == 0) break;
        Buffer32 = READ_PCI32(Bus, Dev, Fun, *CapPtr16);
    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetLegCapStrucAddr
//
// Description: This routine is called to get the 16-bit offset of a
//              structure which can be located using the PCI Legacy
//              Capabilities Pointer mechanism.
//
// Input:       Bus       - The PCI bus number of the PCI device.
//              Dev       - The PCI device number of the PCI device.
//              Fun       - The PCI function number of the PCI device.
//              FindCapNo - The Legacy Capability ID to be found.
//              CapPtr16  - The offset address of desired structure
//
// Output:      EFI_STATUS
//                  EFI_NOT_FOUND - The desired structure is not found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetLegCapStrucAddr (
    IN UINT8                Bus,
    IN UINT8                Dev,
    IN UINT8                Fun,
    IN UINT8                FindCapNo,
    OUT UINT16              *CapPtr16 )
{
    UINT8           Buffer8;

    if (READ_PCI32(Bus, Dev, Fun, PCI_VID) != 0xffffffff) {
        if (READ_PCI16(Bus, Dev, Fun, 6) & 0x10) {
            *CapPtr16 = ((READ_PCI8(Bus, Dev, Fun, 14) & 0x7f) == 2) ? \
                                                                    0x14:0x34;
            *CapPtr16 = (UINT16)READ_PCI8(Bus, Dev, Fun, *CapPtr16);
            if (*CapPtr16 == 0) return EFI_NOT_FOUND;
            Buffer8 = READ_PCI8(Bus, Dev, Fun, *CapPtr16);
            while (Buffer8 != 0) {
                if (Buffer8 == FindCapNo) return EFI_SUCCESS;
                Buffer8 = (UINT8)(*CapPtr16) + 1;
                *CapPtr16 = (UINT16)(READ_PCI8(Bus, Dev, Fun, Buffer8));
                if (*CapPtr16 == 0) break;
                Buffer8 = READ_PCI8(Bus, Dev, Fun, *CapPtr16);
            }
        }
    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FindPciGraphicAdapter
//
// Description: This routine tries to find any PCI graphic adapter on the
//              PCI bus.
//
// Input:       None
//
// Output:      EFI_STATUS
//              EFI_NOT_FOUND - No PCI Graphic Adapter to be found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FindPciGraphicAdapter (VOID)
{
    UINT8                   StartBus;
    UINT8                   EndBus;
    UINT8                   Bus;
    UINT8                   Dev;
    UINT8                   Fun;
    UINT8                   EndFun;
    UINT8                   Buffer8;
    UINT32                  Vid32;

    StartBus = READ_PCI8(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, PCIBR_REG_SBUSN);
    EndBus = READ_PCI8(PCIBR_BUS, PCIBR_DEV, PCIBR_FUN, PCIBR_REG_SUBUSN);

    for (Bus = StartBus; Bus <= EndBus; Bus++) {
        for (Dev = 0; Dev <= PCI_MAX_DEVICE; Dev++) {
            Vid32 = READ_PCI32(Bus, Dev, 0, PCI_VID);
            if (Vid32 != 0xffffffff) {
                Buffer8 = READ_PCI8(Bus, Dev, 0, PCI_HDR);
                EndFun = (Buffer8 & 0x80) ? 8 : 1;
                for (Fun = 0; Fun < EndFun; Fun++) {
                    Vid32 = READ_PCI32(Bus, Dev, Fun, PCI_VID);
                    if (Vid32 != 0xffffffff) {
                        Buffer8=READ_PCI8(Bus, Dev, Fun, PCI_BCC);
                        if (Buffer8 == 3) return EFI_SUCCESS;
                    }
                }
            }
        }
    }

    return EFI_NOT_FOUND;
}
#if NB_PCIE_ERROR_LOG_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbEnablePciDevErr
//
// Description: Enable the error register of PCI-Express Device.
//
// Input:      IN UINT64 Address - PCIE devices Address
//
// Output:     VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NbEnablePciDevErr(
     IN UINT64 Address
)
{
  UINT32 DevBaseAddr = (UINT32)Address;
  UINT8  CapPtr;

  // Clear Error Status
  WRITE_MEM8_S3(gBootScript, DevBaseAddr + 0x07, 0xff);//(BIT0 | BIT1 | BIT2 | BIT3));

  CapPtr = NbFindCapPtr(DevBaseAddr, 0x10);
  if(CapPtr != 0)
  {
    // Clear Device Error Status
    SET_MEM8_S3(gBootScript, DevBaseAddr + CapPtr + 0x0A, (BIT0 | BIT1 | BIT2));
    // Enable the error bits of Device Control
    SET_MEM8_S3(gBootScript, DevBaseAddr + CapPtr + 0x08, (BIT0 | BIT1 | BIT2));
  }

  // Root?
//  if ((READ_MEM8(DevBaseAddr + CapPtr + 0x02) & 0xF0) == 0x40)
  // if device is bridge
  if (READ_MEM16(DevBaseAddr + 0x0A) == 0x0604)
  {
    WRITE_MEM8_S3(gBootScript, DevBaseAddr + 0x1F, 0xff);//(BIT0 | BIT1 | BIT2 | BIT3));
    if(CapPtr != 0)
      SET_MEM8_S3(gBootScript, DevBaseAddr + CapPtr + 0x1C, (BIT0 | BIT1 | BIT2));
  }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NbPciExpressDeviceInitialize
//
// Description: Init NB Pcie devices error register
//
// Input:    IN UINT64  Address - PCIE devices Address
//
// Output:   VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NbPciExpressDeviceInitialize(
     IN UINT64 Address
)
{
  UINT8   Dev;
  UINT8   Func;
  UINT8   CurrentBus;
  UINT16  Buffer16;
  UINT64  DevAddress;
  UINT8   PciFun = (Address >> 12) & 0x07;
  UINT8   CapPtr;
  UINT8   Buffer8;

  CapPtr = NbFindCapPtr(Address, 0x10);
  Buffer8 = READ_MEM8(Address + CapPtr + 0x08);
  Buffer8 &= 0xF0;
  Buffer8 |= (BIT03 | BIT02 | BIT01 | BIT00);

  WRITE_MEM8_S3( gBootScript, \
                 Address + CapPtr + 0x08, \
                 Buffer8 );

  CurrentBus = READ_MEM8((UINT32)Address + PCIBR_REG_SBUSN);

  for (Dev = 0; Dev < 32; Dev++)
  {
    for (Func = 0; Func < 8; Func++)
    {
      DevAddress = (UINT64)NB_PCIE_CFG_ADDRESS(CurrentBus, Dev, Func, 0);

      if (READ_MEM16(DevAddress) == 0xFFFF)
        continue;

      NbEnablePciDevErr(DevAddress);

      Buffer16 = READ_MEM16((UINT32)NB_PCIE_CFG_ADDRESS(CurrentBus, Dev, 0, 0) + PCI_SCC);
      if (Buffer16 == 0x0604)
      {
        DevAddress = (UINT64)NB_PCIE_CFG_ADDRESS(CurrentBus, Dev, 0, 0);
        NbPciExpressDeviceInitialize(DevAddress);
      }
    }
  }
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbInitAfterDeviceInstall
//
// Description: This callback function is called when a PCI I/O Protocol is
//              installed.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbInitAfterDeviceInstall (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
    EFI_STATUS              Status;
    EFI_HANDLE              Handle;
    EFI_PCI_IO_PROTOCOL     *PciIo;
    UINTN                   BufferSize = 20 * sizeof(EFI_HANDLE);
    UINTN                   PciSeg;
    UINTN                   PciBus;
    UINTN                   PciDev;
    UINTN                   PciFun;
    UINT8                   PciSeg8;
    UINT8                   PciBus8;
    UINT8                   PciDev8;
    UINT8                   PciFun8;
    static UINT8            BrBus = 0;
    UINT16                  CapPtr16 = 0;
    PCI_DEV_INFO            *PciDevInfo = NULL;

    Status = pBS->LocateHandle( ByRegisterNotify, NULL, gNBInitNotifyReg, \
                                &BufferSize, &Handle );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    // Locate PciIo protocol installed on Handle

    Status = pBS->HandleProtocol( Handle, &gEfiPciIoProtocolGuid, &PciIo );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    // Get PCI Device Bus/Device/Function Numbers
    Status = PciIo->GetLocation(PciIo, &PciSeg, &PciBus, &PciDev, &PciFun);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    PciSeg8 = (UINT8)PciSeg;
    PciBus8 = (UINT8)PciBus;
    PciDev8 = (UINT8)PciDev;
    PciFun8 = (UINT8)PciFun;

    if (NB_PCI_CFG_ADDRESS(PciBus, PciDev, PciFun, 0) == NB_PCIEBRN_BUS_DEV_FUN)
    {

    }

    if (NB_PCI_CFG_ADDRESS(PciBus, PciDev, PciFun, 0) == NB_IGD_BUS_DEV_FUN) {

    }

    if ((BrBus != 0) && (PciBus == BrBus)) {

    }

    if (((UINT8)PciBus == PCIEBRN_BUS) && \
        ((UINT8)PciDev == PCIEBRN_DEV) && \
        (((UINT8)PciFun >= PCIEBRN_FUN) || ((UINT8)PciFun <= PCIEBRN_FUN2))) {

    }

    pBS->CloseEvent(Event);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RegisterDisplayDIMMPopulationErrMsg
//
// Description: Notification function on SimpleIn protocol Installation
//
// Input:       SystemTable - Pointer to the System Table
//
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
EFIAPI
RegisterDisplayDIMMPopulationErrMsg (
  IN    EFI_SYSTEM_TABLE            *SystemTable
  )
{

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InstallNbMemoryInfo
//
// Description: This function collects all memory information and creates a
//              structure use for other DXE drivers.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InstallNbMemoryInfo (
    IN EFI_SYSTEM_TABLE *SystemTable )
{
  EFI_STATUS             Status;
  EFI_HANDLE             Handle=NULL;
  EFI_GUID               MemInfoHobGuid = EFI_MEMORY_RESTORE_DATA_GUID;
  HOB_SAVE_MEMORY_DATA    *MemInfoHob;
  UINT8                   node;
  UINT8                   Ch;
  UINT8                   Dimm;
  UINT8                   Slot0;
  UINT8                   Slot1;
  UINT8                   Slot2;
  UINT8                   Slot3;
  VOID                    *FirstHob;
  BOOLEAN                 MemoryTimingValuesInitialized;

  //
  // Get the HOB list and install MemInfo protocol
  //
  FirstHob = GetEfiConfigurationTable(SystemTable,&gHobListGuid);
  if (!FirstHob)return EFI_INVALID_PARAMETER;

  MemInfoHob = (HOB_SAVE_MEMORY_DATA *) FirstHob;

  while (!EFI_ERROR (Status = FindNextHobByType (EFI_HOB_TYPE_GUID_EXTENSION, &MemInfoHob))) {
    if (guidcmp (&MemInfoHob->EfiHobGuidType.Name, &MemInfoHobGuid) == 0) {
      break;
    }
  }

  MemoryTimingValuesInitialized = FALSE;

  if (Status == EFI_SUCCESS) {
    gMemInfoHobProtocol.MemInfoData.memSize = (UINT16)MemInfoHob->MrcData.SysOut.Outputs.MemoryMapData.TotalPhysicalMemorySize;
    gMemInfoHobProtocol.MemInfoData.ddrFreq = (UINT16)MemInfoHob->MrcData.SysOut.Outputs.Frequency;
    gMemInfoHobProtocol.MemInfoData.VddVoltage[0] = (UINT16)MemInfoHob->MrcData.SysOut.Outputs.VddVoltage[0];

    gMemInfoHobProtocol.MemInfoData.EccSupport = MemInfoHob->MrcData.SysOut.Outputs.EccSupport;
    gMemInfoHobProtocol.MemInfoData.RefClk = MemInfoHob->MrcData.SysOut.Outputs.RefClk;
    gMemInfoHobProtocol.MemInfoData.Ratio = MemInfoHob->MrcData.SysOut.Outputs.Ratio;
    NBPlatformData.DDR3Type = MemInfoHob->MrcData.SysOut.Outputs.DdrType;
    gBClkFrequency = MemInfoHob->MrcData.SysIn.Inputs.BClkFrequency;
    MemoryProfile = gMemInfoHobProtocol.MemInfoData.Profile = MemInfoHob->MrcData.SysIn.Inputs.MemoryProfile;

    //
    // Getting the tRAS
    // See MRC_TimingConfiguration.c for tRAS algorithm
    //
    for (node = 0; node < NODE_NUM; node++) {
      for (Ch = 0; Ch < CH_NUM; Ch++) {
        for (Dimm = 0; Dimm < DIMM_NUM; Dimm++) {
          gMemInfoHobProtocol.MemInfoData.dimmSize[(node << 2) + (Ch << 1) + Dimm] = (UINT16) MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Dimm[Dimm].DimmCapacity;
          TRACE (
            (TRACE_ALWAYS,
            "Node %d Ch %d Dimm %d Size: %d\n",
            node,
            Ch,
            Dimm,
            gMemInfoHobProtocol.MemInfoData.dimmSize[(node << 2) + (Ch << 1) + Dimm])
            );
          gMemInfoHobProtocol.MemInfoData.DimmExist[(node << 2) + (Ch << 1) + Dimm] = (MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Dimm[Dimm].Status == DIMM_PRESENT) ? TRUE : FALSE;
          gMemInfoHobProtocol.MemInfoData.RankInDimm[(node << 2) + (Ch << 1) + Dimm] = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Dimm[Dimm].RankInDIMM;
          gMemInfoHobProtocol.MemInfoData.DimmsSpdData[(node << 2) + (Ch << 1) + Dimm] = NULL;

          //
          // Updating tCL, tRCD and tRP to MemInfoHobProtocol from MemInfoHob
          //
          if (MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Dimm[Dimm].Status == DIMM_PRESENT) {
            gMemInfoHobProtocol.MemInfoData.Timing[0].tCL   = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tCL;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tCWL  = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tCWL;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tFAW  = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tFAW;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tRAS  = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tRAS;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tRC   = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tRC;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tRCD  = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tRCD;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tREFI = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tREFI;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tRFC  = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tRFC;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tRP   = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tRP;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tRRD  = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tRRD;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tRTP  = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tRTP;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tWR   = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tWR;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tWTR  = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tWTR;
            gMemInfoHobProtocol.MemInfoData.Timing[0].tRPab = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing[MemoryProfile].tRPab;

            NBMrcTimingData = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing;

            NBPlatformData.XmpProfile1 = (NBMrcTimingData[2].tCK != 0) ? TRUE : FALSE;
            NBPlatformData.XmpProfile2 = (NBMrcTimingData[3].tCK != 0) ? TRUE : FALSE;

            //
            // mrc input spd send to smbios memory spd data.
            //
            if(gNbSetupData->IsRunMemoryDown)
               gMemInfoHobProtocol.MemInfoData.DimmsSpdData[(node << 2) + (Ch << 1) + Dimm] = (UINT8*)&MemInfoHob->MrcData.SysIn.Inputs.Controller[0].Channel[Ch].Dimm[Dimm].Spd;

//          gMemInfoHobProtocol.MemInfoData.NMode = MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[Ch].Timing.NMode;
            //
            // Since we have only one setup varaiable to keep track of each memory timing, We inititialize the Memory Info HOB with the first occurence of data
            //
            MemoryTimingValuesInitialized = TRUE;
          }
        }
      }
    }

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 0
#if defined APAC_NB_SETUP_SUPPORT || defined NB_SETUP_SUPPORT
#if APAC_NB_SETUP_SUPPORT == 1 || NB_SETUP_SUPPORT == 1
{
    SETUP_DATA             *SetupData = NULL;
    EFI_GUID               SetupGuid  = SETUP_GUID;
    UINTN                  VarSize = 0;
    WDT_PROTOCOL           *WdtProtocol = NULL;
    EFI_GUID               WdtProtocolGuid = WDT_PROTOCOL_GUID;
    UINT32                 Attributes;          // [ EIP167027 ]


    if (MemoryTimingValuesInitialized) {
        //Status = GetEfiVariable(L"Setup", &SetupGuid, NULL, &VarSize, &SetupData);    // [ EIP167027 ]
        Status = GetEfiVariable(L"Setup", &SetupGuid, &Attributes, &VarSize, &SetupData);
        if (!EFI_ERROR(Status)) {
            //

            Status = pBS->LocateProtocol(&WdtProtocolGuid, NULL, &WdtProtocol);
            if (!EFI_ERROR(Status)) {
                if (WdtProtocol->CheckStatus() == V_PCH_OC_WDT_CTL_STATUS_FAILURE)
                    SetupData->SpdProfileSelected = 0; // Auto
            }

              SetupData->tCL   = NBMrcTimingData[MemoryProfile].tCL;
              SetupData->tCWL  = NBMrcTimingData[MemoryProfile].tCWL;
              SetupData->tFAW  = NBMrcTimingData[MemoryProfile].tFAW;
              SetupData->tRAS  = NBMrcTimingData[MemoryProfile].tRAS;
              SetupData->tRC   = NBMrcTimingData[MemoryProfile].tRC;
              SetupData->tRCD  = NBMrcTimingData[MemoryProfile].tRCD;
              SetupData->tREFI = NBMrcTimingData[MemoryProfile].tREFI;
              SetupData->tRFC  = NBMrcTimingData[MemoryProfile].tRFC;
              SetupData->tRP   = NBMrcTimingData[MemoryProfile].tRP;
              SetupData->tRRD  = NBMrcTimingData[MemoryProfile].tRRD;
              SetupData->tRTP  = NBMrcTimingData[MemoryProfile].tRTP;
              SetupData->tWR   = NBMrcTimingData[MemoryProfile].tWR;
              SetupData->tWTR  = NBMrcTimingData[MemoryProfile].tWTR;
              SetupData->tRPab = NBMrcTimingData[MemoryProfile].tRPab;

            SetupData->OcDdrFreqLimit = gMemInfoHobProtocol.MemInfoData.ddrFreq;

            //Status = pRS->SetVariable (       // [ EIP167027 ]
            //                    L"Setup",
            //                    &SetupGuid,
            //                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
            //                    sizeof(SETUP_DATA),
            //                    SetupData);
            Status = pRS->SetVariable (
                                L"Setup",
                                &SetupGuid,
                                Attributes,
                                sizeof(SETUP_DATA),
                                SetupData);
            ASSERT_EFI_ERROR (Status);
        }
    }
}
#endif
#endif
#endif

    // Mobile - 0; Desktop - 2; UpServer - 3; FlavorWorkStation - 4;
    if (NBPlatformData.UserBoard != FlavorMobile) {

      Slot0 = (MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[0].Dimm[0].Status == DIMM_PRESENT) ? TRUE : FALSE;
      Slot1 = (MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[0].Dimm[1].Status == DIMM_PRESENT) ? TRUE : FALSE;
      Slot2 = (MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[1].Dimm[0].Status == DIMM_PRESENT) ? TRUE : FALSE;
      Slot3 = (MemInfoHob->MrcData.SysOut.Outputs.Controller[0].Channel[1].Dimm[1].Status == DIMM_PRESENT) ? TRUE : FALSE;

      //
      // Channel 0          Channel 1
      // Slot0   Slot1      Slot0   Slot1      - Population            AIO board
      // 0          0          0          0          - Invalid        - Invalid
      // 0          0          0          1          - Valid          - Invalid
      // 0          0          1          0          - Invalid        - Valid
      // 0          0          1          1          - Valid          - Valid
      // 0          1          0          0          - Valid          - Invalid
      // 0          1          0          1          - Valid          - Invalid
      // 0          1          1          0          - Invalid        - Invalid
      // 0          1          1          1          - Valid          - Invalid
      // 1          0          0          0          - Invalid        - Valid
      // 1          0          0          1          - Invalid        - Invalid
      // 1          0          1          0          - Invalid        - Valid
      // 1          0          1          1          - Invalid        - Valid
      // 1          1          0          0          - Valid          - Valid
      // 1          1          0          1          - Valid          - Invalid
      // 1          1          1          0          - Invalid        - Valid
      // 1          1          1          1          - Valid          - Valid
      //
      if ((Slot0 && (Slot1 == 0)) || (Slot2 && (Slot3 == 0))) {
        RegisterDisplayDIMMPopulationErrMsg (SystemTable);
      }
    }

    Status = pBS->InstallMultipleProtocolInterfaces (
                &Handle,
                &gMemInfoProtocolGuid,
                &gMemInfoHobProtocol,
                NULL
                );
    }

    return EFI_SUCCESS;
}

#ifdef CSM_OPRROM_POLICY_GUID
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbCheckOprom
//
// Description: This callback function is called before/after processing all
//              PCI optonal ROM.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbCheckOprom (
    IN EFI_EVENT   Event,
    IN VOID        *Context )
{
    EFI_STATUS                  Status;
    UINTN                       BufferSize = sizeof(EFI_HANDLE);
    EFI_HANDLE                  Handle;
    CSM_PLATFORM_POLICY_DATA    *Data;
    UINTN                       Seg;
    UINTN                       Bus;
    UINTN                       Dev;
    UINTN                       Fun;

    Status = pBS->LocateHandle( ByRegisterNotify, \
                                NULL, \
                                gCsmOpromReg, \
                                &BufferSize, \
                                &Handle );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    // Locate CSM Platform Policy data
    Status = pBS->HandleProtocol( Handle, &gCsmOpromPolicyGuid, &Data );

    if ( EFI_ERROR(Status) ) return;
    if (Data == NULL) return;
    if (Data->ExecuteThisRom == FALSE) return;
	if(Data->PciIo == NULL) return;

    Status = Data->PciIo->GetLocation( Data->PciIo, &Seg, &Bus, &Dev, &Fun );

    // Close the event if needed.
    // pBS->CloseEvent(Event);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbSetupNvramUpdatedCallback
//
// Description: This callback function is called after Setup NVRAM variable
//              being updated.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbSetupNvramUpdatedCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    EFI_STATUS              Status;
    NB_SETUP_DATA           *NBSetupData = NULL;
    UINTN                   VariableSize = sizeof(NB_SETUP_DATA);

    Status = pBS->AllocatePool( EfiBootServicesData, \
                                VariableSize, \
                                &NBSetupData );
    ASSERT_EFI_ERROR(Status);

    GetNbSetupData( pRS, NBSetupData, FALSE );

    // Free memory used for setup data
    pBS->FreePool( NBSetupData );

    pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbPciEnumerationCompleteProtocolCallback
//
// Description: Install gEfiPciEnumerationCompleteProtocolGuid Protocol.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbPciEnumerationCompleteProtocolCallback (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context)
{
    EFI_STATUS  Status;
    EFI_GUID    gEfiPciEnumerationCompleteProtocolGuid = EFI_PCI_ENUMERATION_COMPLETE_GUID;
    EFI_HANDLE  Handle = NULL;

    Status = pBS->InstallProtocolInterface (
                  &Handle,
                  &gEfiPciEnumerationCompleteProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL);
    ASSERT_EFI_ERROR(Status);

    pBS->CloseEvent(Event);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbExitPmAuthProtocolCallback
//
// Description: This callback function is called after ExitPmAuthProtocol
//              being installed.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbExitPmAuthProtocolCallback (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context)
{
  EFI_STATUS  Status;
  VOID        *ProtocolPointer;
  UINTN       PegAddress;
  UINT32      Data32And;
  UINT32      Data32Or;
  UINT32      Data32;
  UINT16      Data16;
  UINT8       PegBus;
  UINT8       PegDev;
  UINT8       PegFun;
  UINTN       i;
#if NB_PCIE_ERROR_LOG_SUPPORT
  UINT8                   CapPtr = 0;
  EFI_SM_ELOG_PROTOCOL    *GenericElogProtocol = NULL;
#endif
  //
  // Check whether this is real ExitPmAuth notification, or just a SignalEvent
  //
  Status = pBS->LocateProtocol (&gExitPmAuthProtocolGuid, NULL, &ProtocolPointer);
  if (EFI_ERROR (Status)) return;


  for ( i = 0; gDevicesTable[i].Bus != 0xff; i++)
  {

     PegBus = gDevicesTable[i].Bus;
     PegDev = gDevicesTable[i].Dev;
     PegFun = gDevicesTable[i].Fun;

     Data32 = READ_PCI32 (PegBus, PegDev, PegFun, PCI_VID);

     if (Data32 == 0xFFFFFFFF) continue;

     //
     // 6.3.7  Virtual Channel Configuration of PCI Express Port
     // Set the VC0RCTL register D1:F0 Offset 114h [7:1] = 7Fh
     //
     PegAddress = NB_PCIE_CFG_ADDRESS(PegBus, PegDev, PegFun, 0);
     Data32And = 0xFFFFFF00 + BIT0;
     Data32Or  = BIT1 + BIT2 + BIT3 + BIT4 + BIT5 +BIT6 + BIT7;
       RW_MEM32_S3(gBootScript, (PegAddress + R_SA_PEG_VC0RCTL0_OFFSET), Data32Or, ~Data32And);

     //
     // Store the Root port Bus assignemnt for S3 resume path
     //
     PegAddress = NB_PCIE_CFG_ADDRESS(PegBus, PegDev, PegFun, PCI_PBUS);
     Data32 = READ_MEM32 (PegAddress);

     BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
                                 gBootScript, \
                                 EfiBootScriptWidthUint32, \
                                 PegAddress, \
                                 1, \
                                 &Data32 );

     PegAddress = NB_PCIE_CFG_ADDRESS(PegBus, PegDev, PegFun, PCI_BAR3);
     Data16 = READ_MEM16 (PegAddress);

     BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
                                 gBootScript, \
                                 EfiBootScriptWidthUint16, \
                                 PegAddress, \
                                 1, \
                                 &Data16 );

#if NB_PCIE_ERROR_LOG_SUPPORT
      Status = pBS->LocateProtocol( &gElogProtocolGuid,
                                    NULL,
                                    &GenericElogProtocol );
      if (!EFI_ERROR (Status)) {
          PegAddress = NB_PCIE_CFG_ADDRESS(PegBus, PegDev, PegFun, 0);
          // if enable PCI SERR and PERR
          if((READ_MEM16(PegAddress + PCI_CMD) & (BIT6 | BIT8)) == (BIT6 | BIT8))
          {
             NbPciExpressDeviceInitialize(PegAddress);

             // Clear Error status
             WRITE_MEM8_S3(gBootScript, PegAddress + 0x07, 0xff);
             WRITE_MEM8_S3(gBootScript, PegAddress + 0x1F, 0xff);

             CapPtr = NbFindCapPtr(PegAddress, 0x10);

             if (CapPtr != 0)
             {
                // Clear Device Error status
                SET_MEM8_S3(gBootScript, PegAddress + CapPtr + 0x0A, (BIT0 | BIT1 | BIT2));
                // Enable the error bits of Device Control
                SET_MEM8_S3(gBootScript, PegAddress + CapPtr + 0x08, (BIT0 | BIT1 | BIT2));
                // Enable the error bits of Root Control
                SET_MEM8_S3(gBootScript, PegAddress + CapPtr + 0x1C, (BIT2));
             }
          }
      }
#endif

  }

  pBS->CloseEvent(Event);

}

//----------------------------------------------------------------------------
#if (ACPI_SUPPORT)

UINT8    ACPI_OEM_ID[6]     = T_ACPI_OEM_ID ;//CONVERT_TO_STRING(T_ACPI_OEM_ID);
UINT8    ACPI_OEM_TBL_ID[8] = T_ACPI_OEM_TBL_ID ;//CONVERT_TO_STRING(T_ACPI_OEM_TBL_ID);

UINTN           mMcfgTblHandle=0;
EFI_EVENT       mAcpiEvent;
VOID            *mAcpiReg;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CreateNbAcpiCallback
//
// Description: This function will create all ACPI components for NB when
//              ACPI support protocol is available.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreateNbAcpiCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    MCFG_20                     *mcfg;
    EFI_ACPI_TABLE_PROTOCOL     *At;
    UINT8 i;
    UINTN                       TableKey;

    // It must be only one instance of such protocol
    Status = pBS->LocateProtocol( &gEfiAcpiTableProtocolGuid, NULL, &At );
    TRACE((-1,"PciHostCSHooks: LocateProtocol(ACPITableProtocol) = %r\n", Status));
    if(EFI_ERROR(Status)) return;

//--------------------------------
  //it must be only one instance of such protocol
    mcfg=MallocZ(sizeof(MCFG_20));
    ASSERT(mcfg);
    if(!mcfg) return;

    //Fill Table header;
    mcfg->Header.Signature=MCFG_SIG;
    mcfg->Header.Length=sizeof(MCFG_20);
    mcfg->Header.Revision=1;
    mcfg->Header.Checksum=0;
    for (i=0;i<6;i++) {
      mcfg->Header.OemId[i]=ACPI_OEM_ID[i];
    }

    for (i=0;i<8;i++) {
      mcfg->Header.OemTblId[i]=ACPI_OEM_TBL_ID[i];
    }
    mcfg->Header.OemRev=ACPI_OEM_REV;
    mcfg->Header.CreatorId=0x5446534d;  // "MSFT" 4D 53 46 54
    mcfg->Header.CreatorRev=0x97;

    //fill MCFG Fields
    mcfg->BaseAddr=PCIEX_BASE_ADDRESS;  // Base address of 256MB extended config space
    mcfg->PciSeg=0;                     // Segment # of PCI Bus
    mcfg->StartBus=0;                   // Start bus number of PCI segment
    mcfg->EndBus=(UINT8)((PCIEX_LENGTH >> 20) - 1);// End bus number of PCI segment

    // Add table
    Status = At->InstallAcpiTable( At, mcfg, sizeof(MCFG_20), &TableKey );
    TRACE((-1,"PciHostCSHooks: ACPITable->InstallAcpiTable(MCFG)=%r\n",Status));
    ASSERT_EFI_ERROR(Status);

    //free memory used for table image
    pBS->FreePool(mcfg);

    //Kill the Event
    pBS->CloseEvent(Event);

}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CreateNbAcpiComponent
//
// Description: This function creates all ACPI components supported by NB.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreateNbAcpiComponent (VOID)
{
    EFI_STATUS      Status = EFI_SUCCESS;

#if (ACPI_SUPPORT)
    Status = RegisterProtocolCallback( &gEfiAcpiTableProtocolGuid, \
                                           CreateNbAcpiCallback, \
                                           NULL, \
                                           &mAcpiEvent, \
                                           &mAcpiReg );
    // If System Description Table Protocol has been installed we can use
    // it rigth on the way
        pBS->SignalEvent( mAcpiEvent );
#endif

}

// Protocols that are installed
DXE_PLATFORM_SA_POLICY_PROTOCOL   mDxePlatformSaPolicy      = { 0 };

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InstallDxePlatformSaPolicy
//
// Description: This Function installs the SNB SA POLICY PROTOCOL
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InstallDxePlatformSaPolicy (VOID)
{
    VOID                         *Registration;
    EFI_EVENT                    Event;
    EFI_STATUS                   Status;
    EFI_STATUS                   FindNbPegHobStatus = EFI_NOT_FOUND;
    EFI_HANDLE                   Handle;
    VOID                         *HobData;
    SB_SETUP_DATA                *SBSetupData = NULL;
    UINTN                        VariableSize = sizeof(SB_SETUP_DATA);
    UINT8                        Index;
    UINT16                       McDeviceId;
    UINT32                       RegEax, RegEbx, RegEcx, RegEdx, CpuSteppingId, CpuFamilyId;

    Status = pBS->AllocatePool( EfiBootServicesData, \
                                VariableSize, \
                                &SBSetupData );
    ASSERT_EFI_ERROR(Status);

    // Read the Setup Data
    GetSbSetupData( pRS, SBSetupData, FALSE );

    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof (SA_VTD_CONFIGURATION),
                    &(mDxePlatformSaPolicy.Vtd)
                    );
    ASSERT_EFI_ERROR (Status);

    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof (SA_MEMORY_CONFIGURATION),
                    &(mDxePlatformSaPolicy.MemoryConfig)
                    );
    ASSERT_EFI_ERROR (Status);

    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    (sizeof (UINT8) * DIMM_SLOT_NUM),
                    (VOID **) &mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable
                    );
    ASSERT_EFI_ERROR (Status);

    Status = pBS->AllocatePool (EfiBootServicesData,
                    sizeof (SA_PCIE_CONFIGURATION),
                    &(mDxePlatformSaPolicy.PcieConfig)
                    );
    ASSERT_EFI_ERROR (Status);

    Status = pBS->AllocatePool (EfiBootServicesData,
                    sizeof (SA_IGD_CONFIGURATION),
                    &(mDxePlatformSaPolicy.IgdConfig)
                    );
    ASSERT_EFI_ERROR (Status);

    Status = pBS->AllocatePool (EfiBootServicesData,
                    sizeof (SA_MISC_CONFIGURATION),
                    &(mDxePlatformSaPolicy.MiscConfig)
                    );
    ASSERT_EFI_ERROR (Status);

    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof (SA_DEFAULT_SVID_SID),
                    (VOID **) &mDxePlatformSaPolicy.MiscConfig->DefaultSvidSid
                    );
    ASSERT_EFI_ERROR (Status);

    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof (SA_HDA_VERB_TABLE),
                    (VOID **) &mDxePlatformSaPolicy.MiscConfig->SaHdaVerbTable
                    );
    ASSERT_EFI_ERROR (Status);
#if ( defined(SwitchableGraphics_SUPPORT) && (SwitchableGraphics_SUPPORT == 1) )
    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    sizeof (SA_DEFAULT_SVID_SID),
                    (VOID **) &mDxePlatformSaPolicy.VbiosConfig
                    );
    ASSERT_EFI_ERROR (Status);
#endif

    // RMRR Base and Limit Address for USB
    Status = pBS->AllocatePool (
                    EfiBootServicesData,
                    (sizeof (EFI_PHYSICAL_ADDRESS) * 2),
                    (VOID **) &mDxePlatformSaPolicy.Vtd->RmrrUsbBaseAddress
                    );
    ASSERT_EFI_ERROR (Status);

    // Read MC device ID
    McDeviceId = READ_PCI16_NB(R_SA_MC_DEVICE_ID);

    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);

    CpuSteppingId = RegEax & 0x0000000F;
    CpuFamilyId = RegEax & 0x0FFF0FF0;

    NBPlatformData.VTdAvailable = (READ_PCI32_NB(0xe4) & BIT23) ? 0 : 1;


    mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable[0] = DIMM1_SMBUS_ADDRESS;
    mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable[1] = DIMM2_SMBUS_ADDRESS;
    mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable[2] = DIMM3_SMBUS_ADDRESS;
    mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable[3] = DIMM4_SMBUS_ADDRESS;

    mDxePlatformSaPolicy.MemoryConfig->ChannelASlotMap    = 0x03;
    mDxePlatformSaPolicy.MemoryConfig->ChannelBSlotMap    = 0x03;

#if A1_MEMORY_SOCKETS == 2
    mDxePlatformSaPolicy.MemoryConfig->ChannelASlotMap    = 0x01;
    mDxePlatformSaPolicy.MemoryConfig->ChannelBSlotMap    = 0x01;
#endif

#if A1_MEMORY_SOCKETS == 6
    mDxePlatformSaPolicy.MemoryConfig->ChannelASlotMap    = 0x07;
    mDxePlatformSaPolicy.MemoryConfig->ChannelBSlotMap    = 0x07;
#endif


    mDxePlatformSaPolicy.Vtd->BaseAddress[0] = NB_VTD_BASE_ADDRESS;
    mDxePlatformSaPolicy.Vtd->BaseAddress[1] = NB_VTD_BASE_ADDRESS + 0x1000;

    // System Agent Configuration Misc

    mDxePlatformSaPolicy.MiscConfig->ChapDeviceEnable = gNbSetupData->SaDevice7;;
    mDxePlatformSaPolicy.MiscConfig->Device4Enable    = (gNbSetupData->SaDevice4);
    mDxePlatformSaPolicy.MiscConfig->CridEnable       = gNbSetupData->EnableNbCrid;
    mDxePlatformSaPolicy.MiscConfig->DefaultSvidSid->SubSystemVendorId = gNbSetupData->NBDxeSubSystemVendorId;
    mDxePlatformSaPolicy.MiscConfig->DefaultSvidSid->SubSystemId       = gNbSetupData->NBDxeSubSystemId;

    mDxePlatformSaPolicy.MiscConfig->AudioEnable      = gNbSetupData->SaAudioEnable;
    mDxePlatformSaPolicy.MiscConfig->FviReport        = 1;    // Default Enable FVI SMBIOS Report
    mDxePlatformSaPolicy.MiscConfig->FviSmbiosType    = 0xDD; // Default SMBIOS Type 221

    // Port B
//    gNbSaHdaVerbTableData[4] &= 0xFFFFFF00;
//    if (gNbSetupData->SaHdmiCodecPortB == 0)
//      gNbSaHdaVerbTableData[4] |= 0x58;
//    else
//      gNbSaHdaVerbTableData[4] |= 0x18;

    // Port C
//    gNbSaHdaVerbTableData[8] &= 0xFFFFFF00;
//    if (gNbSetupData->SaHdmiCodecPortC == 0)
//      gNbSaHdaVerbTableData[8] |= 0x58;
//    else
//      gNbSaHdaVerbTableData[8] |= 0x18;

    // Port D
//    gNbSaHdaVerbTableData[12] &= 0xFFFFFF00;
//    if (gNbSetupData->SaHdmiCodecPortD == 0)
//      gNbSaHdaVerbTableData[12] |= 0x58;
//    else
//      gNbSaHdaVerbTableData[12] |= 0x18;

//    if ((CpuFamilyId == 0x000306C0) && (CpuSteppingId < 2)) { // B0

        if (gNbSetupData->NbSaHdaVerbTable != NULL) {
          mDxePlatformSaPolicy.MiscConfig->SaHdaVerbTableNum   = gNbSetupData->NbSaHdaVerbTableNum;
          (pBS->CopyMem) (&mDxePlatformSaPolicy.MiscConfig->SaHdaVerbTable[0], &gNbSetupData->NbSaHdaVerbTable[0], sizeof (SA_HDA_VERB_TABLE_HEADER));
          mDxePlatformSaPolicy.MiscConfig->SaHdaVerbTable[0].VerbTableData = gNbSetupData->NbSaHdaVerbTable[0].VerbTableData;
        }

//    } else {
//      mDxePlatformSaPolicy.MiscConfig->SaHdaVerbTable[0].VerbTableData = &(gNbSaHdaVerbTableData[1]);
//    }

    //
    // BIOS must update USB RMRR base address
    //
    mDxePlatformSaPolicy.Vtd->RmrrUsbBaseAddress[0] = 0x3E2E0000;
    mDxePlatformSaPolicy.Vtd->RmrrUsbBaseAddress[1] = 0x3E2FFFFF;

    // Protocol revision number
    mDxePlatformSaPolicy.Revision = DXE_SA_PLATFORM_POLICY_PROTOCOL_REVISION_8;

    // Init DxePlaformSaPolicy if Setup Variable is exist
    mDxePlatformSaPolicy.Vtd->VtdEnable           = gNbSetupData->EnableVtd;

    // PCIE related Setup data
    mDxePlatformSaPolicy.PcieConfig->DmiAspm      = gNbSetupData->NBDmiAspm;
    mDxePlatformSaPolicy.PcieConfig->DmiExtSync   = gNbSetupData->NBDmiExtSync;
    mDxePlatformSaPolicy.PcieConfig->DmiDeEmphasis = gNbSetupData->DmiDeEmphasis;
    mDxePlatformSaPolicy.PcieConfig->DmiIot = gNbSetupData->DmiIot;
    mDxePlatformSaPolicy.PcieConfig->C7Allowed = gNbSetupData->C7Allowed;
    for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
       mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[Index].LtrEnable            = gNbSetupData->LtrEnable[Index];
       mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[Index].LtrMaxSnoopLatency   = gNbSetupData->LtrMaxSnoopLatency[Index];//V_SA_LTR_MAX_SNOOP_LATENCY_VALUE;
       mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[Index].LtrMaxNoSnoopLatency = gNbSetupData->LtrMaxNoSnoopLatency[Index];//V_SA_LTR_MAX_NON_SNOOP_LATENCY_VALUE;
       mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[Index].ObffEnable           = gNbSetupData->ObffEnable[Index];
    }



    if (gNbSetupData->DetectNonComplaint == 1) {
       HobData = (EFI_HOB_GENERIC_HEADER *) GetEfiConfigurationTable (pST, &gHobListGuid);
       if (HobData) {
          FindNbPegHobStatus = FindNextHobByGuid (&gAmiNbPegInfoGuid, &HobData);
       }
    }

    for (Index = 0; Index < 3; Index++) {
        mDxePlatformSaPolicy.PcieConfig->PegAspm[Index]       = gNbSetupData->PegAspm[Index];
        mDxePlatformSaPolicy.PcieConfig->PegAspmL0s[Index]    = gNbSetupData->PegAspmL0s[Index];
        if (EFI_ERROR (FindNbPegHobStatus)) {
           mDxePlatformSaPolicy.PcieConfig->PegDeEmphasis[Index] = gNbSetupData->PegDeEmphasis[Index];
        } else {
           mDxePlatformSaPolicy.PcieConfig->PegDeEmphasis[Index] = ((NB_PEG_INFO_HOB *)HobData)->PegDeOverride[Index];
        }
    }

    mDxePlatformSaPolicy.PcieConfig->PcieAspmDevsOverride = mPcieAspmDevsOverride;
    mDxePlatformSaPolicy.PcieConfig->PcieLtrDevsOverride  = mPcieLtrDevsOverride;

    // IGD related Setup data
    mDxePlatformSaPolicy.IgdConfig->RenderStandby = gNbSetupData->RenderStandby;

    mDxePlatformSaPolicy.IgdConfig->DeepRenderStandby = gNbSetupData->DeepRenderStandby;

    if (GetPchSeries() == PchLp) {
       mDxePlatformSaPolicy.IgdConfig->CdClk             = 1;
    } else {
       mDxePlatformSaPolicy.IgdConfig->CdClk             = 2; // (EIP106013)
    }


    mDxePlatformSaPolicy.IgdConfig->PlatformConfig    = gNbSetupData->AcpiLowPowerS0Idle;


#ifdef BDAT_SUPPORT
    mDxePlatformSaPolicy.MemoryConfig->RmtBdatEnable = gNbSetupData->BdatAcpiTableSupport;
#endif

#if ( defined(SwitchableGraphics_SUPPORT) && (SwitchableGraphics_SUPPORT == 1) )
    ///
    /// Initialize the Switchable Graphics DXE Policies
    ///

    ///
    /// 1 = Load secondary display device VBIOS
    /// 0 = Do not load
    ///
    mDxePlatformSaPolicy.VbiosConfig->LoadVbios = 0;    // Shark Bay SA Reference Code Production Version 1.9.0 [ EIP194524 ]
    ///
    /// 1 = Execute the secondary display device VBIOS (only if LoadVbios == 1)
    /// 0 = Do no execute
    ///
    mDxePlatformSaPolicy.VbiosConfig->ExecuteVbios = 0;
    ///
    /// 1 = secondary display device VBIOS Source is PCI Card
    /// 0 = secondary display device VBIOS Source is FW Volume
    ///
    mDxePlatformSaPolicy.VbiosConfig->VbiosSource = 1;
#endif

    Handle = NULL;
    // Install protocol to to allow access to this Policy.
    Status = pBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &gDxePlatformSaPolicyGuid,
                    &mDxePlatformSaPolicy,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);


    // Register Callback function for updating USB Rmrr address
    Status = pBS->CreateEvent (
                    EFI_EVENT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    RmrrUpdateCallback,
                    NULL,
                    &Event
                    );

    if (!EFI_ERROR (Status)) {
      Status = pBS->RegisterProtocolNotify (
                      &gEfiUsbProtocolGuid,
                      Event,
                      &Registration
                      );
    }

  // Free memory used for setup data
  pBS->FreePool( SBSetupData );

  return Status;

}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------
//
// Procedure:   RmrrUpdateCallback
//
// Description: This Function is update IGD & USB Rmrr BaseAddress
//
// Input:       Event             A pointer to the Event that triggered the callback.
//              Context           A pointer to private data registered with the callback function.
//
// Output:      None
//--------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RmrrUpdateCallback (
  IN EFI_EVENT          Event,
  IN VOID               *Context
)
{
  EFI_STATUS                      Status;
  EFI_USB_PROTOCOL                *UsbProtocol;
  DXE_PLATFORM_SA_POLICY_PROTOCOL *DxePlatformSaPolicy;
  UINT16                          IgdMode;
  UINT16                          GttMode;
  UINT32                          IgdMemSize;
  UINT32                          GttMemSize;
  EFI_PHYSICAL_ADDRESS            RmrrIGDBaseAddress;
  EFI_PHYSICAL_ADDRESS            RmrrIGDSize;
  DXE_SERVICES                    *DxeSvcTbl = NULL;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR GcdMemorySpaceDescriptor;
  UINT64                          Attributes;

  pBS->CloseEvent(Event);
  //
  // Update USB Reserved Memory Base Address and Limit Address for VT-d.
  //
  Status = pBS->LocateProtocol (&gDxePlatformSaPolicyGuid, NULL, &DxePlatformSaPolicy);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = pBS->LocateProtocol (&gEfiUsbProtocolGuid, NULL, &UsbProtocol);
  if (!EFI_ERROR (Status))
  {

      Status = UsbProtocol->UsbGetRuntimeRegion (
                              &DxePlatformSaPolicy->Vtd->RmrrUsbBaseAddress[0],
                              &DxePlatformSaPolicy->Vtd->RmrrUsbBaseAddress[1]
                              );

      TRACE ((TRACE_ALWAYS, "RmrrUsbBaseAddress = 0x%X\n", DxePlatformSaPolicy->Vtd->RmrrUsbBaseAddress[0]));
      TRACE ((TRACE_ALWAYS, "RmrrUsbLimitAddress = 0x%X\n", DxePlatformSaPolicy->Vtd->RmrrUsbBaseAddress[1]));
  }

  if (READ_PCI32_IGD (R_SA_IGD_VID) == 0xFFFFFFFF)  return Status;

  Status  = LibGetDxeSvcTbl(&DxeSvcTbl);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) return Status;

  //
  // Calculate IGD memsize
  //
  IgdMode = (READ_PCI16_NB (R_SA_GGC) & B_SA_GGC_GMS_MASK) >> 3;
  if (IgdMode <= V_SA_GGC_GMS_512MB)
  {
    IgdMemSize = IgdMode * 32 * (1024) * (1024);
  } else if (IgdMode >= 0x11) // V_SA_GGC_GMS_1024MB
  {
    IgdMemSize = 0x20 * 32 * (1024) * (1024);
  } else {
    IgdMemSize = 0;
  }

  //
  // Calculate GTT mem size
  //
  GttMode = (READ_PCI16_NB (R_SA_GGC) & B_SA_GGC_GGMS_MASK) >> N_SA_GGC_GGMS_OFFSET;
  if (GttMode <= V_SA_GGC_GGMS_2MB)
  {
    GttMemSize = GttMode * (1024) * (1024);
  } else {
    GttMemSize = 0;
  }

  if ((IgdMemSize + GttMemSize) == 0)  return Status;

  RmrrIGDBaseAddress = (EFI_PHYSICAL_ADDRESS)((READ_PCI32_NB (R_SA_TOLUD) & ~(0x01)) - IgdMemSize - GttMemSize);
  RmrrIGDSize        = (EFI_PHYSICAL_ADDRESS)(IgdMemSize + GttMemSize);

  Status      = DxeSvcTbl->GetMemorySpaceDescriptor (RmrrIGDBaseAddress, &GcdMemorySpaceDescriptor);
  ASSERT_EFI_ERROR (Status);

  Attributes = GcdMemorySpaceDescriptor.Attributes | EFI_MEMORY_RUNTIME;

  Status=DxeSvcTbl->SetMemorySpaceAttributes(RmrrIGDBaseAddress,RmrrIGDSize,Attributes);
  ASSERT_EFI_ERROR(Status);

  TRACE ((TRACE_ALWAYS, "RmrrIGDBaseAddress = 0x%X\n", RmrrIGDBaseAddress));
  TRACE ((TRACE_ALWAYS, "RmrrIGDSize = 0x%X\n", RmrrIGDSize));

  return Status;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------
//
// Procedure:   NBDXE_ShadowRam
//
// Description: For setting PAM0\PAM5\PAM6 to "Disable", "Read Only", "Write Only", or "R/W Enable"
//              under not using legacy.
//
// Input:       EFI_HANDLE
//              EFI_SYSTEM_TABL
//
// Output:      None
//--------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBDXE_ShadowRam (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS         Status = EFI_SUCCESS;
    UINT8              Default_PAM0 = (UINT8)(NB_F0000_PAM0 << 4);
    UINT8              Default_PAM5 = (UINT8)((NB_E0000_PAM5 << 4) | NB_E0000_PAM5);
    UINT8              Default_PAM6 = (UINT8)((NB_E8000_PAM6 << 4) | NB_E8000_PAM6);

    //
	// Set "Disable", "Read Only", "Write Only", or "R/W Enable" as Token value into PAM0\PAM5\PAM6.
	//
    WRITE_PCI8_NB (0x80, Default_PAM0);
    WRITE_PCI8_NB (0x85, Default_PAM5);
    WRITE_PCI8_NB (0x86, Default_PAM6);

    return Status;
}


#if defined (PERF_TUNE_SUPPORT) && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
#define OC_MAILBOX_MSR                  0x00000150
#define MAILBOX_WAIT_TIMEOUT  1000  ///< 1 millisecond
#define OC_LIB_CMD_GET_OC_CAPABILITIES              0x01
#define OC_LIB_CMD_GET_VOLTAGE_FREQUENCY            0x10
#define OC_LIB_COMPLETION_CODE_SUCCESS              0x00
#define BIT0_MASK             0x1
#define MAX_RATIO_MASK        0x000000FF
#define VOLTAGE_TARGET_MASK   0x000FFF00
#define VOLTAGE_TARGET_OFFSET 8
#define VOLTAGE_MODE_MASK     0x00100000
#define VOLTAGE_MODE_OFFSET   20
#define VOLTAGE_OFFSET_MASK   0xFFE00000
#define VOLTAGE_OFFSET_OFFSET 21

#define MILLIVOLTS_PER_VOLT  1000
#define MAX_TARGET_MV      4095
#define MAX_OFFSET_MV      500

#define CONVERT_TO_FIXED_POINT_VOLTS  0
#define CONVERT_TO_BINARY_MILLIVOLT   1

#define OC_CAPS_MAX_RATIO_MASK          0x000000FF
#define OC_CAPS_RATIO_SUPPORT_MASK      0x00000100
#define OC_CAPS_RATIO_SUPPORT_OFFSET    8
#define OC_CAPS_OVERRIDE_SUPPORT_MASK   0x00000200
#define OC_CAPS_OVERRIDE_SUPPORT_OFFSET 9
#define OC_CAPS_OFFSET_SUPPORT_MASK     0x00000400
#define OC_CAPS_OFFSET_SUPPORT_OFFSET   10
//
// Bit 10 is the S11.0.10V sign bit
//
#define FIXED_POINT_SIGN_BIT_MASK 0x0400
#define INT16_SIGN_BIT_MASK       0x8000

//
// tCL Macro definitions
//
#ifndef tCL_MINIMUM
#define tCL_MINIMUM   4
#endif
#ifndef tCL_MAXIMUM
#define tCL_MAXIMUM   18
#endif
#define tCL_NumOfValues tCL_MAXIMUM - tCL_MINIMUM + 1
//
// tRP Macro definitions
//
#ifndef tRP_MINIMUM
#define tRP_MINIMUM   4
#endif
#ifndef tRP_MAXIMUM
#define tRP_MAXIMUM   15
#endif
#define tRP_NumOfValues tRP_MAXIMUM - tRP_MINIMUM + 1
//
// tRCD Macro definitions
//
#ifndef tRCD_MINIMUM
#define tRCD_MINIMUM   4
#endif
#ifndef tRCD_MAXIMUM
#define tRCD_MAXIMUM   20
#endif
#define tRCD_NumOfValues tRCD_MAXIMUM - tRCD_MINIMUM + 1
//
// tRAS Macro definitions
//
#ifndef tRAS_MINIMUM
#define tRAS_MINIMUM   10
#endif
#ifndef tRAS_MAXIMUM
#define tRAS_MAXIMUM   40
#endif
#define tRAS_NumOfValues tRAS_MAXIMUM - tRAS_MINIMUM + 1
//
// tWR Macro definitions
//
#ifndef tWR_MINIMUM
#define tWR_MINIMUM   5
#endif
#ifndef tWR_MAXIMUM
#define tWR_MAXIMUM   30
#endif
#define tWR_NumOfValues tWR_MAXIMUM - tWR_MINIMUM + 1
//
// tRFC Macro definitions
//
#ifndef tRFC_MINIMUM
#define tRFC_MINIMUM   1
#endif
#ifndef tRFC_MAXIMUM
#define tRFC_MAXIMUM   511
#endif
#define tRFC_NumOfValues tRFC_MAXIMUM - tRFC_MINIMUM + 1
//
// tRRD Macro definitions
//
#ifndef tRRD_MINIMUM
#define tRRD_MINIMUM   4
#endif
#ifndef tRRD_MAXIMUM
#define tRRD_MAXIMUM   7
#endif
#define tRRD_NumOfValues tRRD_MAXIMUM - tRRD_MINIMUM + 1
//
// tWTR Macro definitions
//
#ifndef tWTR_MINIMUM
#define tWTR_MINIMUM   4
#endif
#ifndef tWTR_MAXIMUM
#define tWTR_MAXIMUM   10
#endif
#define tWTR_NumOfValues tWTR_MAXIMUM - tWTR_MINIMUM + 1
//
// tRTP Macro definitions
//
#ifndef tRTP_MINIMUM
#define tRTP_MINIMUM   4
#endif
#ifndef tRTP_MAXIMUM
#define tRTP_MAXIMUM   15
#endif

#define tRTP_NumOfValues tRTP_MAXIMUM - tRTP_MINIMUM + 1
//
// tFAW Macro definitions
//
#ifndef tFAW_MINIMUM
#define tFAW_MINIMUM   10
#endif
#ifndef tFAW_MAXIMUM
#define tFAW_MAXIMUM   54
#endif
#define tFAW_NumOfValues tFAW_MAXIMUM - tFAW_MINIMUM + 1
//
// tRC Macro definitions
//
#ifndef tRC_MINIMUM
#define tRC_MINIMUM   1
#endif
#ifndef tRC_MAXIMUM
#define tRC_MAXIMUM   4095
#endif
#define tRC_NumOfValues tRC_MAXIMUM - tRC_MINIMUM + 1
//
//
// tCWL Macro definitions
//
#ifndef tCWL_MINIMUM
#define tCWL_MINIMUM   5
#endif
#ifndef tCWL_MAXIMUM
#define tCWL_MAXIMUM   12
#endif
#define tCWL_NumOfValues tCWL_MAXIMUM - tCWL_MINIMUM + 1
//
// tREFI Macro definitions
//
#ifndef tREFI_MINIMUM
#define tREFI_MINIMUM   1
#endif
#ifndef tREFI_MAXIMUM
#define tREFI_MAXIMUM   10000
#endif
#define tREFI_NumOfValues tREFI_MAXIMUM - tREFI_MINIMUM + 1
//
// tRPab Macro definitions
//
#ifndef tRPab_MINIMUM
#define tRPab_MINIMUM   4
#endif
#ifndef tRPab_MAXIMUM
#define tRPab_MAXIMUM   18
#endif
#define tRPab_NumOfValues tRPab_MAXIMUM - tRPab_MINIMUM + 1
//
//
// iGfxRatio Macro definitions
//
#ifndef iGfxRatio_MINIMUM
#define iGfxRatio_MINIMUM   17
#endif
#ifndef iGfxRatio_MAXIMUM
#define iGfxRatio_MAXIMUM   60
#endif
#define iGfxRatio_NumOfValues iGfxRatio_MAXIMUM - iGfxRatio_MINIMUM + 1

//
// iGfxVolt Macro definitions
//
#ifndef iGfxVoltOverride_MINIMUM
#define iGfxVoltOverride_MINIMUM    0
#endif
#ifndef iGfxVoltOverride_MAXIMUM
#define iGfxVoltOverride_MAXIMUM    2000
#endif
#define iGfxVoltOverride_NumOfValues iGfxVoltOverride_MAXIMUM - iGfxVoltOverride_MINIMUM + 1

#ifndef iGfxVoltOffset_MINIMUM
#define iGfxVoltOffset_MINIMUM    0
#endif
#ifndef iGfxVoltOffset_MAXIMUM
#define iGfxVoltOffset_MAXIMUM    1000
#endif
#define iGfxVoltOffset_NumOfValues iGfxVoltOffset_MAXIMUM - iGfxVoltOffset_MINIMUM + 1

#ifndef SaVoltOffset_MINIMUM
#define SaVoltOffset_MINIMUM    0
#endif
#ifndef SaVoltOffset_MAXIMUM
#define SaVoltOffset_MAXIMUM    1000
#endif
#define SaVoltOffset_NumOfValues SaVoltOffset_MAXIMUM - SaVoltOffset_MINIMUM + 1

#ifndef IoaVoltOffset_MINIMUM
#define IoaVoltOffset_MINIMUM    0
#endif
#ifndef IoaVoltOffset_MAXIMUM
#define IoaVoltOffset_MAXIMUM    1000
#endif
#define IoaVoltOffset_NumOfValues IoaVoltOffset_MAXIMUM - IoaVoltOffset_MINIMUM + 1

#ifndef IodVoltOffset_MINIMUM
#define IodVoltOffset_MINIMUM    0
#endif
#ifndef IodVoltOffset_MAXIMUM
#define IodVoltOffset_MAXIMUM    1000
#endif
#define IodVoltOffset_NumOfValues IodVoltOffset_MAXIMUM - IodVoltOffset_MINIMUM + 1

//========================================== GACI TABLE ======================================================

//     GACI_DATA    DevNameGaciData   {ControlID,NumberOfValues,\
//     Precision,Flags,DefaultDataValue,MinDataValue,MaxDataValue,MinDisplayValue,MaxDisplayValue}
static GACI_DATA    tCLGaciData	       = {BIOS_TCL_IMPLEMENTATION,\
       tCL_NumOfValues,         0,        0,        0, tCL_MINIMUM,  tCL_MAXIMUM,  tCL_MINIMUM,  tCL_MAXIMUM};

static GACI_DATA    tCWLGaciData	   = {BIOS_TCWL_IMPLEMENTATION,\
       tCWL_NumOfValues,        0,        0,        0, tCWL_MINIMUM, tCWL_MAXIMUM, tCWL_MINIMUM, tCWL_MAXIMUM};

static GACI_DATA    tREFIGaciData	   = {BIOS_TREFI_IMPLEMENTATION,\
       tREFI_NumOfValues,        0,        0,        0, tREFI_MINIMUM, tREFI_MAXIMUM, tREFI_MINIMUM, tREFI_MAXIMUM};

static GACI_DATA    tRASGaciData       = {BIOS_TRAS_IMPLEMENTATION,\
       tRAS_NumOfValues,        0,        0,        0, tRAS_MINIMUM, tRAS_MAXIMUM, tRAS_MINIMUM, tRAS_MAXIMUM};

static GACI_DATA    tRPGaciData	       = {BIOS_TRP_IMPLEMENTATION,\
       tRP_NumOfValues,         0,        0,        0, tRP_MINIMUM,  tRP_MAXIMUM,  tRP_MINIMUM,  tRP_MAXIMUM};

static GACI_DATA    tRCDGaciData       = {BIOS_TRCD_IMPLEMENTATION,\
       tRCD_NumOfValues,        0,        0,        0, tRCD_MINIMUM, tRCD_MAXIMUM, tRCD_MINIMUM, tRCD_MAXIMUM};

static GACI_DATA    tWRGaciData        = {BIOS_TWR_IMPLEMENTATION,\
       tWR_NumOfValues,         0,        0,        0, tWR_MINIMUM,  tWR_MAXIMUM,  tWR_MINIMUM,  tWR_MAXIMUM};

static GACI_DATA    tRFCGaciData       = {BIOS_TRFC_IMPLEMENTATION,\
       tRFC_NumOfValues,        0,        0,        0, tRFC_MINIMUM, tRFC_MAXIMUM, tRFC_MINIMUM, tRFC_MAXIMUM};

static GACI_DATA    tRRDGaciData       = {BIOS_TRRD_IMPLEMENTATION,\
       tRRD_NumOfValues,        0,        0,        0, tRRD_MINIMUM, tRRD_MAXIMUM, tRRD_MINIMUM, tRRD_MAXIMUM};

static GACI_DATA    tWTRGaciData       = {BIOS_TWTR_IMPLEMENTATION,\
       tWTR_NumOfValues,        0,        0,        0, tWTR_MINIMUM, tWTR_MAXIMUM, tWTR_MINIMUM, tWTR_MAXIMUM};

static GACI_DATA    tRTPGaciData       = {BIOS_TRTP_IMPLEMENTATION,\
       tRTP_NumOfValues,        0,        0,        0, tRTP_MINIMUM, tRTP_MAXIMUM, tRTP_MINIMUM, tRTP_MAXIMUM};

static GACI_DATA    tFAWGaciData       = {BIOS_TFAW_IMPLEMENTATION,\
       tFAW_NumOfValues,        0,        0,        0, tFAW_MINIMUM, tFAW_MAXIMUM, tFAW_MINIMUM, tFAW_MAXIMUM};

static GACI_DATA    tRCGaciData        = {BIOS_TRC_IMPLEMENTATION,\
       tRC_NumOfValues,         0,        0,        0,  tRC_MINIMUM,  tRC_MAXIMUM,  tRC_MINIMUM,  tRC_MAXIMUM};

//static GACI_DATA    tRPabGaciData        = {BIOS_TRPAB_IMPLEMENTATION,\
//       tRPab_NumOfValues,         0,        0,        0,  tRPab_MINIMUM,  tRPab_MAXIMUM,  tRPab_MINIMUM,  tRPab_MAXIMUM};

static GACI_DATA    DramMultiGaciData  = {BIOS_DDR_MULT_IMPLEMENTATION,\
       0xFFFF,                  2,        0,        0,                 0,                 0,                 0,                 0};

static GACI_DATA    XmpProfSelData     = {BIOS_XMP_PROFILE_SELECTION_IMPLEMENTATION,\
       3,                       0,        0,        0,                 0,                 3,                 0,                 3};

static GACI_DATA    CpuRuntimeTurbo    = {BIOS_RUNTIME_TURBO_OVERRIDE_IMPLEMENTATION,\
       0,                       0,        0,        0,                 0,                 0,                 0,                 0};

static GACI_DATA    iGfxTurboRatioData = {BIOS_GRAPHICS_TURBO_RATIO_LIMIT_IMPLEMENTATION,\
       iGfxRatio_NumOfValues,   1,        0,        0, 0, iGfxRatio_MAXIMUM, 0, iGfxRatio_MAXIMUM};

//static GACI_DATA    iGfxVoltageData    = {BIOS_GRAPHICS_CORE_VOLTAGE_IMPLEMENTATION,\
//       iGfxVolt_NumOfValues,    0,        0,        0,  iGfxVolt_MINIMUM,  iGfxVolt_MAXIMUM,  iGfxVolt_MINIMUM,  iGfxVolt_MAXIMUM};

static GACI_DATA    iGfxVoltageOverride = {BIOS_GRAPHICS_CORE_VOLTAGE_OVERRIDE_IMPLEMENTATION,\
       iGfxVoltOverride_NumOfValues,        3,        0,        0, iGfxVoltOverride_MINIMUM, iGfxVoltOverride_MAXIMUM, iGfxVoltOverride_MINIMUM, iGfxVoltOverride_MAXIMUM};

static GACI_DATA    iGfxVoltageMode    = {BIOS_GRAPHICS_CORE_VOLTAGE_MODE_IMPLEMENTATION,\
       1,                                   0,        0,        0,                  0,                 1,                0,                 1};

static GACI_DATA    iGfxVoltageOffset  = {BIOS_GRAPHICS_CORE_VOLTAGE_OFFSET_IMPLEMENTATION,\
       2001,          0,        0,        1000, 0, 2000, 0xFFFFFc18, 1000};

static GACI_DATA    SaVoltageOffset      = {BIOS_SYSTEM_AGENT_VOLTAGE_OFFSET_IMPLEMENTATION,\
       2001,          0,        0,        1000, 0, 2000, 0xFFFFFc18, 1000};

static GACI_DATA    IoaVoltageOffset      = {BIOS_IO_ANALOG_VOLTAGE_OFFSET_IMPLEMENTATION,\
       2001,          0,        0,        1000, 0, 2000, 0xFFFFFc18, 1000};

static GACI_DATA    IodVoltageOffset      = {BIOS_IO_DIGITAL_VOLTAGE_OFFSET_IMPLEMENTATION,\
       2001,          0,        0,        1000, 0, 2000, 0xFFFFFc18, 1000};

static GACI_DATA    MemClockMultiplier  = {BIOS_MEM_CLOCK_MULTIPLIER_IMPLEMENTATION,\
       0xFFFF,                  2,        0,        0,                 0,                 0,                 0,                 0};

//========================================== XMP Profile TABLE ======================================================
//Profile 1 data
//     GXDV         DevNameGxdvData     = {ControlID,                Reserved, Precision, DisplayValue};
static GXDV_DATA    Pro1tCLGxdvData     = {BIOS_TCL_IMPLEMENTATION,         0,         0,            8};
static GXDV_DATA    Pro1tRASGxdvData    = {BIOS_TRAS_IMPLEMENTATION,        0,         0,           23};
static GXDV_DATA    Pro1tRPGxdvData     = {BIOS_TRP_IMPLEMENTATION,         0,         0,            8};
static GXDV_DATA    Pro1tRCDGxdvData    = {BIOS_TRCD_IMPLEMENTATION,        0,         0,            8};
static GXDV_DATA    Pro1tWRGxdvData     = {BIOS_TWR_IMPLEMENTATION,         0,         0,            9};
static GXDV_DATA    Pro1tRFCGxdvData    = {BIOS_TRFC_IMPLEMENTATION,        0,         0,           73};
static GXDV_DATA    Pro1tRRDGxdvData    = {BIOS_TRRD_IMPLEMENTATION,        0,         0,            4};
static GXDV_DATA    Pro1tWTRGxdvData    = {BIOS_TWTR_IMPLEMENTATION,        0,         0,            5};
static GXDV_DATA    Pro1tRTPGxdvData    = {BIOS_TRTP_IMPLEMENTATION,        0,         0,            5};
static GXDV_DATA    Pro1tFAWGxdvData    = {BIOS_TFAW_IMPLEMENTATION,        0,         0,           20};
static GXDV_DATA    Pro1tRCGxdvData     = {BIOS_TRC_IMPLEMENTATION,         0,         0,           20};
static GXDV_DATA    Pro1tREFIGxdvData   = {BIOS_TREFI_IMPLEMENTATION,       0,         0,           1000};
static GXDV_DATA    Pro1tCWLGxdvData    = {BIOS_TCWL_IMPLEMENTATION,        0,         0,           8};
//static GXDV_DATA    Pro1tRPabGxdvData   = {BIOS_TRPAB_IMPLEMENTATION,        0,         0,           4};
static GXDV_DATA    Pro1DdrMulGxdvData  = {BIOS_DDR_MULT_IMPLEMENTATION,    0,         0,         	16};
static GXDV_DATA	Pro1DdrClkMulGxdvData  = {BIOS_MEM_CLOCK_MULTIPLIER_IMPLEMENTATION, 0,2,		   133};

//profile 2 data
//     GXDV         DevNameGxdvData     = {ControlID,                Reserved, Precision, DisplayValue};
static GXDV_DATA    Pro2tCLGxdvData     = {BIOS_TCL_IMPLEMENTATION,         0,         0,            7};
static GXDV_DATA    Pro2tRASGxdvData    = {BIOS_TRAS_IMPLEMENTATION,        0,         0,           22};
static GXDV_DATA    Pro2tRPGxdvData     = {BIOS_TRP_IMPLEMENTATION,         0,         0,            7};
static GXDV_DATA    Pro2tRCDGxdvData    = {BIOS_TRCD_IMPLEMENTATION,        0,         0,            7};
static GXDV_DATA    Pro2tWRGxdvData     = {BIOS_TWR_IMPLEMENTATION,         0,         0,            8};
static GXDV_DATA    Pro2tRFCGxdvData    = {BIOS_TRFC_IMPLEMENTATION,        0,         0,           72};
static GXDV_DATA    Pro2tRRDGxdvData    = {BIOS_TRRD_IMPLEMENTATION,        0,         0,            4};
static GXDV_DATA    Pro2tWTRGxdvData    = {BIOS_TWTR_IMPLEMENTATION,        0,         0,            5};
static GXDV_DATA    Pro2tRTPGxdvData    = {BIOS_TRTP_IMPLEMENTATION,        0,         0,            5};
static GXDV_DATA    Pro2tFAWGxdvData    = {BIOS_TFAW_IMPLEMENTATION,        0,         0,           20};
static GXDV_DATA    Pro2tRCGxdvData     = {BIOS_TRC_IMPLEMENTATION,         0,         0,           20};
static GXDV_DATA    Pro2tREFIGxdvData   = {BIOS_TREFI_IMPLEMENTATION,       0,         0,           1000};
static GXDV_DATA    Pro2tCWLGxdvData    = {BIOS_TCWL_IMPLEMENTATION,        0,         0,           8};
//static GXDV_DATA    Pro2tRPabGxdvData   = {BIOS_TRPAB_IMPLEMENTATION,        0,         0,           4};
static GXDV_DATA    Pro2DdrMulGxdvData  = {BIOS_DDR_MULT_IMPLEMENTATION,    0,         0,         	18};
static GXDV_DATA	Pro2DdrClkMulGxdvData  = {BIOS_MEM_CLOCK_MULTIPLIER_IMPLEMENTATION, 0,2,		   133};
//===================================================================================================================


static
MrcFrequency
NbGetDimmFrequency (
  IN     UINT32             tCK
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: GetIGDSettings
//
// Description: Update XTU GACI Table function .
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
UINT32  GetIGDSettings(void)
{
    UINT32              GTTMMADR;// = 0xF7800000;
    UINT32              Data32;

    //
    // Program GT PM Settings if GTTMMADR allocation is Successful
    //
    GTTMMADR = (UINT32)NB_TEMP_MMIO_BASE;
    WRITE_PCI32_IGD (R_SA_IGD_GTTMMADR, (GTTMMADR | BIT02)); // 0x10

    //
    // Enable Bus Master, I/O and Memory access on 0:2:0
    //
    SET_PCI8_IGD (R_SA_IGD_CMD , (BIT02 | BIT01)); // 0x04

    TRACE((-1,"GT Overclocking Support is enabled in BIOS Setup\n"));

    //
    // Wait for Mailbox ready
    //
    while (READ_MEM32 ((UINTN)(GTTMMADR + 0x138124)) & BIT31) {
        Data32 = READ_MEM32 ((UINTN)(GTTMMADR + 0x138124));
    };

    //
    // Mailbox Command - MAILBOX_GTDRIVER_CMD_READ_OVERCLOCK_PARAMS to READ OC SUPPORT
    //
    Data32 = 0x8000000C;
    WRITE_MEM32 ((UINTN)(GTTMMADR + 0x138124), Data32);

    //
    // Wait for Mailbox ready
    //
    while (READ_MEM32 ((UINTN)(GTTMMADR + 0x138124)) & BIT31) {
        Data32 = READ_MEM32 ((UINTN)(GTTMMADR + 0x138124));
    };


    if (READ_MEM32 ((UINTN)(GTTMMADR + 0x138128)) & BIT31)
    {
        Data32 = READ_MEM32 ((UINTN)(GTTMMADR + 0x138128));
        return Data32;
    }
    return Data32;
}

EFI_STATUS GetDddtPresentFlagHob()
{
    EFI_STATUS          Status;
    EFI_GUID            gDddtPreFlagHobGuid = AMI_DDDT_PRESENT_FLAG_HOB_GUID;
    VOID                *gDddtPreFlagHobList = NULL;
    UINTN               FlagCount = (sizeof(BIOS_SETTING_DATA) - sizeof(BIOS_SETTING_HDR))/sizeof(UINT16);

// Get Hob List
    gDddtPreFlagHobList = GetEfiConfigurationTable(pST, &gHobListGuid);
    if (!gDddtPreFlagHobList) return EFI_NOT_FOUND;

// Find CPUID Checksum Data Hob.
    gDddtPresentFlagHob = (DDDT_PRESENT_FLAG_HOB*)gDddtPreFlagHobList;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &gDddtPresentFlagHob)))
	{
        if (guidcmp(&gDddtPresentFlagHob->EfiHobGuidType.Name, &gDddtPreFlagHobGuid) == 0)
            break;
    }

	if (EFI_ERROR(Status)) return EFI_NOT_FOUND;
    return Status;
}

typedef union _OC_MAILBOX_INTERFACE {
  UINT32  InterfaceData;
  struct {
    UINT8   CommandCompletion:8;
    UINT8   Param1:8;
    UINT8   Param2:8;
    UINT8   Reserved:7;
    UINT8   RunBusy:1;
  } Fields;
} OC_MAILBOX_INTERFACE;

typedef struct _OC_MAILBOX_FULL {
  UINT32 Data;
  OC_MAILBOX_INTERFACE Interface;
} OC_MAILBOX_FULL;

typedef struct {
  UINT8 	MaxOcRatio;
  UINT8	  VoltageTargetMode;
  UINT16	VoltageTarget;
  INT16	  VoltageOffset;
} VOLTAGE_FREQUENCY_SETTINGS;

typedef struct {
  VOLTAGE_FREQUENCY_SETTINGS 	VfSettings;
  UINT8 		DomainId;
} VOLTAGE_FREQUENCY_ITEM;

typedef struct {
  UINT8   MaxOcRatioLimit;
  BOOLEAN RatioOcSupported;
  BOOLEAN VoltageOverridesSupported;
  BOOLEAN VoltageOffsetSupported;
  UINT8   DomainId;
} OC_CAPABILITIES_ITEM;

typedef union _OC_MAILBOX_COMMAND {
  UINT32  InterfaceData;
  struct {
    UINT8   CommandCompletion:8;
    UINT8   Param1:8;
    UINT8   Param2:8;
    UINT8   Reserved:7;
    UINT8   RunBusy:1;
  } Fields;
} OC_MAILBOX_COMMAND;

typedef struct _OC_MAILBOX_ITEM {
  UINT32 Data;
  OC_MAILBOX_COMMAND Interface;
} OC_MAILBOX_ITEM;


EFI_STATUS
EFIAPI PollOcMailboxReady (
  )
/**

  Poll the run/busy bit of the mailbox until available or timeout expires.

  @param[IN]  MailboxType,

  @retval EFI_STATUS

**/
{
  EFI_STATUS      Status;
  UINT16          StallCount;
  UINT8           RunBusyBit;
  UINT64          MsrData;
  OC_MAILBOX_FULL OcMailboxFull;

  Status = EFI_SUCCESS;
  StallCount = 0;
  RunBusyBit = 1;

  do {
//      case MAILBOX_TYPE_OC:
        ///
        /// Read the OC mailbox run/busy state
        ///
        MsrData = ReadMsr(OC_MAILBOX_MSR);
        pBS->CopyMem (&OcMailboxFull.Data, &MsrData, sizeof(OcMailboxFull));
        RunBusyBit = OcMailboxFull.Interface.Fields.RunBusy;
//      break;
    //
    // Wait for 1us
    //
    CountTime(4, PM_BASE_ADDRESS);
    StallCount++;
  }
  while ((RunBusyBit == 1) && (StallCount < MAILBOX_WAIT_TIMEOUT));

  if ((RunBusyBit == 0) && (StallCount == MAILBOX_WAIT_TIMEOUT)) {
    TRACE ((TRACE_ALWAYS, "(MAILBOX) Mailbox interface timed out.\n"));
    Status = EFI_TIMEOUT;
  }
  return Status;
}


EFI_STATUS
EFIAPI OcMailboxRead (
  IN  UINT32  MailboxCommand,
  OUT UINT32  *MailboxDataPtr,
  OUT UINT32  *MailboxStatus

  )
/**

  Generic Mailbox function for mailbox read commands. This function will write
  the read request, and populate the read results in the output data.

  @param[IN]  MailboxType,
  @param[IN]  MailboxCommand,
  @param[OUT] *MailboxDataPtr,
  @param[OUT] *MailboxStatus

  @retval EFI_STATUS

**/
{
  EFI_STATUS          Status;
  UINT64              MsrData;
  OC_MAILBOX_FULL     OcMailboxFull;
  OC_MAILBOX_FULL     OcMailboxFullVerify;

  ///
  ///  Poll the run/busy to ensure the interface is available
  ///
  Status = PollOcMailboxReady();
  if (EFI_ERROR(Status)) {
    return Status;
  }

  TRACE ((TRACE_ALWAYS, "(MAILBOX) Mailbox Read Command = %2X\n", (UINT8)MailboxCommand));

  // MAILBOX_TYPE_OC:
      ///
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      ///
      OcMailboxFull.Interface.InterfaceData = MailboxCommand;
      OcMailboxFull.Data = *MailboxDataPtr;
      OcMailboxFull.Interface.Fields.RunBusy = 1;
      pBS->CopyMem  (&MsrData, &OcMailboxFull, sizeof(MsrData));

      ///
      /// Write mailbox command to OC mailbox
      ///
      WriteMsr (OC_MAILBOX_MSR, MsrData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollOcMailboxReady();

      ///
      /// Read the OC mailbox to verify read completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      ///
      MsrData = ReadMsr (OC_MAILBOX_MSR);
      pBS->CopyMem (&OcMailboxFull, &MsrData, sizeof(OcMailboxFull));

      CountTime(40000, PM_BASE_ADDRESS); // 10ms

      MsrData = ReadMsr (OC_MAILBOX_MSR);
      pBS->CopyMem  (&OcMailboxFullVerify, &MsrData, sizeof(OcMailboxFullVerify));

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (OcMailboxFull.Interface.InterfaceData != OcMailboxFullVerify.Interface.InterfaceData ){
        if (OcMailboxFull.Data != OcMailboxFullVerify.Data) {
          TRACE ((TRACE_ALWAYS, "(MAILBOX) Mailbox read data is corrupted.\n"));
          return EFI_INVALID_PARAMETER;
        }
      }

      ///
      ///  Copy Overclocking mailbox completion code and read results
      ///
      *MailboxStatus = OcMailboxFull.Interface.Fields.CommandCompletion;
      pBS->CopyMem(MailboxDataPtr, &OcMailboxFull.Data, sizeof(UINT32));


  TRACE ((TRACE_ALWAYS, "(MAILBOX) Mailbox Status = %2X\n", *MailboxStatus));

  return Status;
}

VOID
ConvertVoltageTarget (
  IN  UINT16  InputVoltageTarget,
  OUT UINT16* OutputVoltageTarget,
  IN  UINT8   ConversionType
  )
/**

  Converts the input voltage target to the fixed point U12.2.10 Volt format or
  the Binary millivolts representation based on the ConversionType

@param[IN]  InputVoltageTarget
@param[OUT] *OutputVoltageTarget
@param[IN]  ConversionType - 0:fixed point, 1:Binary millivolts

**/
{
  ///  Fixed point representation:
  ///
  ///  U12.2.10V format
  ///  | | | |
  ///  | | | v
  ///  | | v Exponent
  ///  | v Significand Size
  ///  v Size
  ///  Signed/Unsigned
  ///
  ///  Float Value = Significand x (Base ^ Exponent)
  ///  (Base ^ Exponent) = 2 ^ 10 = 1024
  ///

  if (InputVoltageTarget == 0){
    *OutputVoltageTarget = 0;
    return;
  }

  if(ConversionType == CONVERT_TO_FIXED_POINT_VOLTS){
    ///
    /// Input Voltage is in number of millivolts. Clip the input Voltage
    /// to the max allowed by the fixed point format
    ///
    if (InputVoltageTarget > MAX_TARGET_MV)
      InputVoltageTarget = MAX_TARGET_MV;

    ///
    /// InputTargetVoltage is the significand in mV. Need to convert to Volts
    ///
    *OutputVoltageTarget = (InputVoltageTarget * 1024)/ MILLIVOLTS_PER_VOLT;

  }
  else if (ConversionType == CONVERT_TO_BINARY_MILLIVOLT){
    ///
    /// InputVoltage is specified in fixed point representation, need to
    /// convert to millivolts
    ///
    *OutputVoltageTarget = (InputVoltageTarget * MILLIVOLTS_PER_VOLT)/1024;
  }

  return;
}

VOID
ConvertVoltageOffset (
  IN  INT16   InputVoltageOffset,
  OUT INT16*  OutputVoltageOffset,
  IN  UINT8   ConversionType
  )
/**

  Converts the input votlage Offset to the fixed point S11.0.10 Volt format or
  to Binary illivolts representation based on the ConversionType.

@param[IN]  InputVoltageTarget
@param[OUT] *OutputVoltageTarget
@param[IN]  ConversionType - 0:fixed point, 1:Signed Binary millivolts


**/
{
  BOOLEAN NumIsNegative;
  ///  Fixed point representation:
  ///
  ///  S11.0.10V format
  ///  | | | |
  ///  | | | v
  ///  | | v Exponent
  ///  | v Significand Size
  ///  v Size
  ///  Signed/Unsigned
  ///
  ///  Float Value = Significand x (Base ^ Exponent)
  ///  (Base ^ Exponent) = 2 ^ 10 = 1024
  ///
  *OutputVoltageOffset = 0;
  NumIsNegative = FALSE;

  if (InputVoltageOffset == 0){
    *OutputVoltageOffset = 0;
    return;
  }

  if (ConversionType == CONVERT_TO_FIXED_POINT_VOLTS){
    ///
    /// Input Voltage is in INT16 representation. Check if numenr is negative
    ///
    if ( (InputVoltageOffset & INT16_SIGN_BIT_MASK) != 0){
      NumIsNegative = TRUE;
      ///
      /// Need to 2's complement adjust to make this number positive for
      /// voltage calculation
      ///
      InputVoltageOffset = (~InputVoltageOffset+1) & (INT16_SIGN_BIT_MASK -1);
    }

    ///
    /// Clip the input Voltage Offset to 500mv
    ///
    if (InputVoltageOffset > MAX_OFFSET_MV) {
      InputVoltageOffset = MAX_OFFSET_MV;
    }

    ///
    /// Convert to fixed point representation
    ///
    *OutputVoltageOffset = (InputVoltageOffset * 1024)/ MILLIVOLTS_PER_VOLT;
    if (NumIsNegative){
      /// 2's complement back to a negative number
      *OutputVoltageOffset = ~(*OutputVoltageOffset) + 1;
    }
  }
  else if (ConversionType == CONVERT_TO_BINARY_MILLIVOLT){
    ///
    /// Input Voltage is in fixed point representation. Check if number negative
    ///
    if( (InputVoltageOffset & FIXED_POINT_SIGN_BIT_MASK)!= 0){
      NumIsNegative = TRUE;
      ///
      /// Need to 2's complement adjust to make this number positive for
      /// voltage calculation
      ///
      InputVoltageOffset = (~InputVoltageOffset+1) & (FIXED_POINT_SIGN_BIT_MASK -1);
    }

    ///
    ///  Convert to INT16 representation in millivolts
    ///
    *OutputVoltageOffset = (InputVoltageOffset * MILLIVOLTS_PER_VOLT)/1024;
    if (NumIsNegative){
      /// 2's complement back to a negative number
      *OutputVoltageOffset = ~(*OutputVoltageOffset) + 1;
    }
  }

  return;
}

EFI_STATUS
EFIAPI GetOcCapabilities (
  OUT OC_CAPABILITIES_ITEM *OcCapabilities,
  OUT UINT32               *LibStatus
  )
/**
  Get the overclocking capabilities for a given CPU Domain

  @param[OUT] *OcCapabilities
  @param[OUT] *LibStatus

  @retval EFI_STATUS
**/
{
  EFI_STATUS      Status;
  UINT32          CommandId;
  OC_MAILBOX_ITEM OcCapsMsg;

  Status = EFI_SUCCESS;

//  ZeroMem(&OcCapsMsg,sizeof(OC_MAILBOX_ITEM));

  ///
  /// Convert OC capabilties message to Mailbox command format
  ///
  CommandId = OC_LIB_CMD_GET_OC_CAPABILITIES;
  //ConvertToMailboxFormat((VOID *)OcCapabilities, &OcCapsMsg, CommandId);
  OcCapsMsg.Data = 0;
  OcCapsMsg.Interface.Fields.CommandCompletion = CommandId;
  OcCapsMsg.Interface.Fields.Param1 = 1;
  ///
  ///  Read From the OC Library
  ///
  Status = OcMailboxRead(OcCapsMsg.Interface.InterfaceData, &OcCapsMsg.Data, LibStatus);

  ///
  ///  Copy mailbox data to OC Capabilities structure
  ///
  if ( (Status == EFI_SUCCESS) && (*LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS)) {
    OcCapabilities->MaxOcRatioLimit =
            (UINT8) OcCapsMsg.Data & OC_CAPS_MAX_RATIO_MASK;

    OcCapabilities->RatioOcSupported =
            (UINT8) ((OcCapsMsg.Data & OC_CAPS_RATIO_SUPPORT_MASK) >> OC_CAPS_RATIO_SUPPORT_OFFSET);

    OcCapabilities->VoltageOverridesSupported =
            (UINT8) ((OcCapsMsg.Data & OC_CAPS_OVERRIDE_SUPPORT_MASK) >> OC_CAPS_OVERRIDE_SUPPORT_OFFSET);

    OcCapabilities->VoltageOffsetSupported =
            (UINT8) ((OcCapsMsg.Data & OC_CAPS_OFFSET_SUPPORT_MASK) >> OC_CAPS_OFFSET_SUPPORT_OFFSET);
  }

  return Status;
}

EFI_STATUS
EFIAPI GetVoltageFrequencyItem (
  OUT VOLTAGE_FREQUENCY_ITEM  * VfSettings,
  OUT UINT32                  *LibStatus
  )
/**

  Gets the Voltage and Frequency information for a given CPU domain

  @param[OUT] *VfSettings
  @param[OUT] *LibStatus

  @retval EFI_STATUS

**/
{
  EFI_STATUS      Status;
  UINT32          CommandId;
  UINT16          TempVoltageTarget;
  INT16           TempVoltageOffset;
  OC_MAILBOX_ITEM VfMsg;

  Status = EFI_SUCCESS;

  ///
  /// Convert v/f command to Mailbox command format
  ///
  CommandId = OC_LIB_CMD_GET_VOLTAGE_FREQUENCY;

//  ConvertToMailboxFormat((VOID*)VfSettings, &VfMsg, CommandId);

  ///
  /// Voltage Frequency Settings are on a per domain basis
  ///
  VfMsg.Data = 0;
  VfMsg.Interface.Fields.CommandCompletion = CommandId;
  VfMsg.Interface.Fields.Param1 = 1;

  ///
  ///  Read From the OC Library
  ///
  Status = OcMailboxRead(VfMsg.Interface.InterfaceData, &VfMsg.Data, LibStatus);

  ///
  ///  Copy mailbox data to VfSettings
  ///
  if ( (Status == EFI_SUCCESS) && (*LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS)){
    VfSettings->VfSettings.MaxOcRatio = (UINT8) (VfMsg.Data & MAX_RATIO_MASK);
    VfSettings->VfSettings.VoltageTargetMode = (UINT8) ( (VfMsg.Data & VOLTAGE_MODE_MASK) >> VOLTAGE_MODE_OFFSET);

    TempVoltageTarget = (UINT16) (VfMsg.Data  & VOLTAGE_TARGET_MASK) >> VOLTAGE_TARGET_OFFSET;
    ConvertVoltageTarget(TempVoltageTarget, &VfSettings->VfSettings.VoltageTarget, CONVERT_TO_BINARY_MILLIVOLT);

    TempVoltageOffset = (INT16)((VfMsg.Data  & VOLTAGE_OFFSET_MASK) >> VOLTAGE_OFFSET_OFFSET);
    ConvertVoltageOffset(TempVoltageOffset, &VfSettings->VfSettings.VoltageOffset, CONVERT_TO_BINARY_MILLIVOLT);
  }

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NbXTUSetGACITable
//
// Description: Update XTU GACI Table function .
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

VOID NbXTUSetGACITable(
     IN EFI_EVENT Event,
     IN VOID *Context
)
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT8    *Buffer = NULL;
    UINTN    Len = 0;
    UINT8    channel = 0;
    EFI_GUID gXtuDataHobGuid = AMI_PERF_TUNE_DATA_HOB_GUID;
    UINT8    NumOcBins = (UINT8)(ReadMsr(0x194) >> 17) & 0x7;
    VOID     *FirstHob;
    AMI_INTERNAL_FACTORY_TDC_TDP_HOB    *TdcTdpHob = NULL;
    BOOLEAN  TdcTdpHobFound = FALSE, OcDataHobFound = FALSE;
    UINT16   OneCoreRatioLimit;
    UINT16   MaxNonTurboRatio;
    UINT8    MemRatio, RefClkRatio;
    UINT32    CurrentRatio;
    OC_CAPABILITIES_ITEM OcCaps;
    UINT32      LibStatus;
    PERF_TUNE_DATA_HOB	*PerfTuneDataHob = NULL;
	UINT32	 MemFreq;
    MrcFrequency                        DDRFrequency[2] = {fNoInit};

    if (gPerfTuneAslProtocol == NULL)
    {
       Status = pBS->LocateProtocol(&gPerfTuneAslProtocolGuid, NULL, &gPerfTuneAslProtocol);
       if(EFI_ERROR(Status))goto Done;
    }

    FirstHob = GetEfiConfigurationTable(pST, &gHobListGuid);

    TdcTdpHob = (AMI_INTERNAL_FACTORY_TDC_TDP_HOB*)FirstHob;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &TdcTdpHob))) {
        if (guidcmp(&TdcTdpHob->EfiHobGuidType.Name, &gAmiInternalFactoryTdcTdpHobGuid) == 0) {
            TdcTdpHobFound = TRUE;
            break;
        }
    }

    FirstHob = GetEfiConfigurationTable(pST, &gHobListGuid);

    PerfTuneDataHob = (PERF_TUNE_DATA_HOB*)FirstHob;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &PerfTuneDataHob))) {
       if (guidcmp(&PerfTuneDataHob->EfiHobGuidType.Name, &gXtuDataHobGuid) == 0) {
          OcDataHobFound = TRUE;
          break;
       }
    }

//========================== GACI TABLE =============================================
//------------------------- tCL Setting ----------------------------------------
    Len = sizeof(tCLGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tCLGaciData.DefaultDataValue = NBMrcTimingData[0].tCL;//DefaultData.tCL;

    MemCpy(Buffer, &tCLGaciData, sizeof(tCLGaciData));
    Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tCL);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tCWL Setting ---------------------------------------
    Len = sizeof(tCWLGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tCWLGaciData.DefaultDataValue = NBMrcTimingData[0].tCWL;//DefaultData.tCWL;

    MemCpy(Buffer, &tCWLGaciData, sizeof(tCWLGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tCWL);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tREFI Setting ---------------------------------------
    Len = sizeof(tREFIGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tREFIGaciData.DefaultDataValue = NBMrcTimingData[0].tREFI;//DefaultData.tREFI;

    MemCpy(Buffer, &tREFIGaciData, sizeof(tREFIGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tREFI);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tRCD Setting ---------------------------------------
    Len = sizeof(tRCDGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tRCDGaciData.DefaultDataValue = NBMrcTimingData[0].tRCD;//DefaultData.tRCD;

    MemCpy(Buffer, &tRCDGaciData, sizeof(tRCDGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tRCD);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tRP Setting ----------------------------------------
    Len = sizeof(tRPGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tRPGaciData.DefaultDataValue = NBMrcTimingData[0].tRP;//DefaultData.tRP;

    MemCpy(Buffer, &tRPGaciData, sizeof(tRPGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tRP);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tRAS Setting ---------------------------------------
    Len = sizeof(tRASGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tRASGaciData.DefaultDataValue = NBMrcTimingData[0].tRAS;//DefaultData.tRAS;

    MemCpy(Buffer, &tRASGaciData, sizeof(tRASGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tRAS);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tWR Setting ---------------------------------------
    Len = sizeof(tWRGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tWRGaciData.DefaultDataValue = NBMrcTimingData[0].tWR;//DefaultData.tWR;

    MemCpy(Buffer, &tWRGaciData, sizeof(tWRGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tWR);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tRFC Setting ---------------------------------------
    Len = sizeof(tRFCGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tRFCGaciData.DefaultDataValue = NBMrcTimingData[0].tRFC;//DefaultData.tRFC;

    MemCpy(Buffer, &tRFCGaciData, sizeof(tRFCGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tRFC);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tRRD Setting ---------------------------------------
    Len = sizeof(tRRDGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;
    tRRDGaciData.DefaultDataValue = NBMrcTimingData[0].tRRD;//DefaultData.tRRD;

    MemCpy(Buffer, &tRRDGaciData, sizeof(tRRDGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tRRD);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tWTR Setting ---------------------------------------
    Len = sizeof(tWTRGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tWTRGaciData.DefaultDataValue = NBMrcTimingData[0].tWTR;//DefaultData.tWTR;

    MemCpy(Buffer, &tWTRGaciData, sizeof(tWTRGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tWTR);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tRTP Setting ---------------------------------------
    Len = sizeof(tRTPGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tRTPGaciData.DefaultDataValue = NBMrcTimingData[0].tRTP;//DefaultData.tRTP;

    MemCpy(Buffer, &tRTPGaciData, sizeof(tRTPGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tRTP);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tFAW Setting ---------------------------------------
    Len = sizeof(tFAWGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tFAWGaciData.DefaultDataValue = NBMrcTimingData[0].tFAW;//DefaultData.tFAW;

    MemCpy(Buffer, &tFAWGaciData, sizeof(tFAWGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tFAW);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tRC Setting ---------------------------------------
    Len = sizeof(tRCGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

    tRCGaciData.DefaultDataValue = NBMrcTimingData[0].tRC;//DefaultData.tRC;

    MemCpy(Buffer, &tRCGaciData, sizeof(tRCGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tRC);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//------------------------- tRPab Setting ---------------------------------------
//    Len = sizeof(tRPabGaciData);
//    Buffer = MallocZ(Len);
//    if(!Buffer) goto Done;

//    tRPabGaciData.DefaultDataValue = NBMrcTimingData[0].tRPab;//DefaultData.tRPab;

//    MemCpy(Buffer, &tRPabGaciData, sizeof(tRPabGaciData));
//	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)NBMrcTimingData[MemoryProfile].tRPab);
//    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
//    pBS->FreePool(Buffer);
//----------------------------- iGfX Core Ratio Limit ---------------------------
    if (READ_PCI32_IGD (R_SA_IGD_VID) != 0xFFFFFFFF) {

       Status = GetOcCapabilities(&OcCaps,&LibStatus);
       if ( (Status == EFI_SUCCESS) && (LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS)) {

          Len = sizeof(iGfxTurboRatioData);
          Buffer = MallocZ(Len);


					CurrentRatio = OcCaps.MaxOcRatioLimit;

					iGfxTurboRatioData.MinDataValue		= READ_MEM8_MCH(0x5998); // Rpm
					iGfxTurboRatioData.MaxDataValue		= CurrentRatio;
					iGfxTurboRatioData.DefaultDataValue = READ_MEM8_MCH(0x5998); // Rpm


    			iGfxTurboRatioData.MinDisplayValue = iGfxTurboRatioData.MinDataValue * 5;
    			iGfxTurboRatioData.MaxDisplayValue = iGfxTurboRatioData.MaxDataValue * 5;
					iGfxTurboRatioData.NumberOfValues = iGfxTurboRatioData.MaxDataValue - iGfxTurboRatioData.MinDataValue + 1;


          MemCpy(Buffer, &iGfxTurboRatioData, sizeof(iGfxTurboRatioData));

          Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
          pBS->FreePool(Buffer);
//------------------------------- iGfX Voltage mode -------------------------------
             Len = sizeof(iGfxVoltageMode);
             Buffer = MallocZ(Len);

             iGfxVoltageMode.MaxDataValue = 1;
             iGfxVoltageMode.MaxDisplayValue = 1;
             iGfxVoltageMode.NumberOfValues = 2;

             MemCpy(Buffer, &iGfxVoltageMode, sizeof(iGfxVoltageMode));

             Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
             pBS->FreePool(Buffer);
//------------------------------- iGfX Voltage  -------------------------------
//             Len = sizeof(iGfxVoltageData);
//             Buffer = MallocZ(Len);

             //GtOcVolt = CurrentVfItem.VfSettings.VoltageTarget;

//             MemCpy(Buffer, &iGfxVoltageData, sizeof(iGfxVoltageData));

             //Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, (UINT16)GtOcVolt);

//             Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
//            pBS->FreePool(Buffer);
//------------------------------- iGfX Voltage Override-------------------------------
             Len = sizeof(iGfxVoltageOverride);
             Buffer = MallocZ(Len);


             MemCpy(Buffer, &iGfxVoltageOverride, sizeof(iGfxVoltageOverride));


             Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
             pBS->FreePool(Buffer);

//------------------------------- iGfX Voltage Offset-------------------------------
          Len = sizeof(iGfxVoltageOffset);
          Buffer = MallocZ(Len);


          MemCpy(Buffer, &iGfxVoltageOffset, sizeof(iGfxVoltageOffset));


          Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
          pBS->FreePool(Buffer);
      } // GetVoltageFrequencyItem
   } // if have IGFX ?
//------------------------------- Sa Voltage Offset -------------------------------
          Len = sizeof(SaVoltageOffset);
          Buffer = MallocZ(Len);

          MemCpy(Buffer, &SaVoltageOffset, sizeof(SaVoltageOffset));
          Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
          pBS->FreePool(Buffer);

//------------------------------- IOA Voltage Offset -------------------------------
          Len = sizeof(IoaVoltageOffset);
          Buffer = MallocZ(Len);

          MemCpy(Buffer, &IoaVoltageOffset, sizeof(IoaVoltageOffset));
          Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
          pBS->FreePool(Buffer);

//------------------------------- IOD Voltage Offset -------------------------------
          Len = sizeof(IodVoltageOffset);
          Buffer = MallocZ(Len);

          MemCpy(Buffer, &IodVoltageOffset, sizeof(IodVoltageOffset));
          Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
          pBS->FreePool(Buffer);
//------------------------------- Runtime Turbo -------------------------------
    if (TdcTdpHobFound) {

        Len = sizeof(CpuRuntimeTurbo);
        Buffer = MallocZ(Len);
        if(!Buffer) goto Done;

        OneCoreRatioLimit = (UINT16)(TdcTdpHob->OneCoreRatioLimit);
        MaxNonTurboRatio = ((UINT16)ReadMsr(0xCE) >> 8) & 0xFF;

        if(OcDataHobFound) {
            if(PerfTuneDataHob->PerfTuneDataHob.RuntimeTurboEanble == 0x1) {
                if(PerfTuneDataHob->PerfTuneDataHob.RuntimeTurbo == 0xFFFF)
                    WRITE_MEM8_MCH(0x5990, (UINT8)OneCoreRatioLimit);
                else
                    WRITE_MEM8_MCH(0x5990, (UINT8)PerfTuneDataHob->PerfTuneDataHob.RuntimeTurbo);
            } else {
                WRITE_MEM8_MCH(0x5990, 0xFF);
            }
        }

        CpuRuntimeTurbo.DefaultDataValue = OneCoreRatioLimit;

        if (NumOcBins == 7) {
                CpuRuntimeTurbo.MaxDataValue    = 0x3b; //max ratio is 59.
                CpuRuntimeTurbo.MaxDisplayValue = 0x3b;
        } else if((NumOcBins > 0) && (NumOcBins < 7)) {
                CpuRuntimeTurbo.MaxDataValue    = OneCoreRatioLimit + NumOcBins;
                CpuRuntimeTurbo.MaxDisplayValue = OneCoreRatioLimit + NumOcBins;
        }

        CpuRuntimeTurbo.MinDataValue    = MaxNonTurboRatio;
        CpuRuntimeTurbo.MinDisplayValue = MaxNonTurboRatio;
        CpuRuntimeTurbo.NumberOfValues  = CpuRuntimeTurbo.MaxDataValue - CpuRuntimeTurbo.MinDataValue + 1;

        MemCpy(Buffer, &CpuRuntimeTurbo, sizeof(CpuRuntimeTurbo));

        Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
        pBS->FreePool(Buffer);
    }
//-------------------------- Mem Freq Setting ----------------------------------------
    Len = sizeof(DramMultiGaciData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

	MemFreq = gMemInfoHobProtocol.MemInfoData.ddrFreq;
	MemRatio = (NbFrequencyToRatio(MemFreq, gMemInfoHobProtocol.MemInfoData.RefClk, gBClkFrequency)*2);
	DramMultiGaciData.DefaultDataValue = (UINT32)MemRatio;

    MemCpy(Buffer, &DramMultiGaciData, sizeof(DramMultiGaciData));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, MemRatio);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//----------------------------Memory Clock Multiplier-----------------------
    Len = sizeof(MemClockMultiplier);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

	if(gMemInfoHobProtocol.MemInfoData.RefClk == MRC_REF_CLOCK_100){
		RefClkRatio = 100;
	}else{
		RefClkRatio = 133;
	}

	MemClockMultiplier.DefaultDataValue = (UINT32)RefClkRatio;
    MemCpy(Buffer, &MemClockMultiplier, sizeof(MemClockMultiplier));
	Status = gPerfTuneAslProtocol->SyncHwValue(Buffer, RefClkRatio);
    Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
    pBS->FreePool(Buffer);
//-------------------------- XMP Profile Selection -------------------------

    Len = sizeof(XmpProfSelData);
    Buffer = MallocZ(Len);
    if(!Buffer) goto Done;

   //Add core to Update the Minimum and Maximum.
   //According to XMP profile count.

   // Default
   XmpProfSelData.MaxDataValue = 1;
   XmpProfSelData.MaxDisplayValue = 1;
   XmpProfSelData.NumberOfValues = 2;

   DDRFrequency[0] = NbGetDimmFrequency(NBMrcTimingData[2].tCK);
   DDRFrequency[1] = NbGetDimmFrequency(NBMrcTimingData[3].tCK);

   if (DDRFrequency[0] != fNoInit && DDRFrequency[1] == fNoInit) { // Porfile 1
        XmpProfSelData.MaxDataValue = 2;
        XmpProfSelData.MaxDisplayValue = 2;
        XmpProfSelData.NumberOfValues = 3;
   } else if (DDRFrequency[0] != fNoInit && DDRFrequency[1] != fNoInit) { // Both Profile
        XmpProfSelData.MaxDataValue = 3;
        XmpProfSelData.MaxDisplayValue = 3;
        XmpProfSelData.NumberOfValues = 4;
   }

   MemCpy(Buffer, &XmpProfSelData, Len);

   Status = gPerfTuneAslProtocol->SetGaciData(Buffer, Len);
   pBS->FreePool(Buffer);
//---------------------------- GXDV START -----------------------------------

   Len = sizeof(GXDV_DATA);
   Len = (UINTN)Mul64(Len, 30); // 32 mean, define GXDV count.
   Buffer = MallocZ(Len);
   if(!Buffer) goto Done;

   //Add code to change profile 1 display value
   if (DDRFrequency[0] != fNoInit) {
        MemRatio = NbFrequencyToRatio(DDRFrequency[0], gMemInfoHobProtocol.MemInfoData.RefClk, gBClkFrequency);

        Pro1tCLGxdvData.DisplayValue    = (UINT32)NBMrcTimingData[2].tCL;
        Pro1tRASGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tRAS;
        Pro1tRPGxdvData.DisplayValue    = (UINT32)NBMrcTimingData[2].tRP;
        Pro1tRCDGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tRCD;
        Pro1tWRGxdvData.DisplayValue    = (UINT32)NBMrcTimingData[2].tWR;
        Pro1tRFCGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tRFC;
        Pro1tRRDGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tRRD;
        Pro1tWTRGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tWTR;
        Pro1tRTPGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tRTP;
        Pro1tFAWGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tFAW;
        Pro1tRCGxdvData.DisplayValue    = (UINT32)NBMrcTimingData[2].tRC;
        Pro1tREFIGxdvData.DisplayValue  = (UINT32)NBMrcTimingData[2].tREFI;
        Pro1tCWLGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tCWL;
//        Pro1tRPabGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[2].tRPab;
        Pro1DdrMulGxdvData.DisplayValue = (UINT32)DDRFrequency[0];
		Pro1DdrMulGxdvData.DisplayValue = (UINT32)MemRatio * 2;
		Pro1DdrClkMulGxdvData.DisplayValue = (UINT32)RefClkRatio;

    }

    //Add code to change Profile 2 display value
    if (DDRFrequency[1]  != fNoInit) {
        MemRatio = NbFrequencyToRatio(DDRFrequency[1], gMemInfoHobProtocol.MemInfoData.RefClk, gBClkFrequency);

        Pro2tCLGxdvData.DisplayValue    = (UINT32)NBMrcTimingData[3].tCL;
        Pro2tRASGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[3].tRAS;
        Pro2tRPGxdvData.DisplayValue    = (UINT32)NBMrcTimingData[3].tRP;
        Pro2tRCDGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[3].tRCD;
        Pro2tWRGxdvData.DisplayValue    = (UINT32)NBMrcTimingData[3].tWR;
        Pro2tRFCGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[3].tRFC;
        Pro2tRRDGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[3].tRRD;
        Pro2tWTRGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[3].tWTR;
        Pro2tRTPGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[3].tRTP;
        Pro2tFAWGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[3].tFAW;
        Pro2tRCGxdvData.DisplayValue    = (UINT32)NBMrcTimingData[3].tRC;
        Pro2tREFIGxdvData.DisplayValue  = (UINT32)NBMrcTimingData[3].tREFI;
        Pro2tCWLGxdvData.DisplayValue   = (UINT32)NBMrcTimingData[3].tCWL;
//        Pro1tRPabGxdvData.DisplayValue  = (UINT32)NBMrcTimingData[3].tRPab;
        Pro2DdrMulGxdvData.DisplayValue = (UINT32)DDRFrequency[1];
		Pro2DdrMulGxdvData.DisplayValue = (UINT32)MemRatio * 2;
		Pro2DdrClkMulGxdvData.DisplayValue = (UINT32)RefClkRatio;
    }

    MemCpy(Buffer, &Pro1tCLGxdvData, Len);

    if (DDRFrequency[0] == fNoInit && DDRFrequency[1] == fNoInit) // Default
        Status = gPerfTuneAslProtocol->SetGxdvData(XmpNotSupport,Buffer, Len);
    else if (DDRFrequency[0] != fNoInit && DDRFrequency[1] == fNoInit) // Profile 1
        Status = gPerfTuneAslProtocol->SetGxdvData(Profiles1,Buffer, Len);
    else if (DDRFrequency[0] != fNoInit && DDRFrequency[1] != fNoInit) // Both Profile
        Status = gPerfTuneAslProtocol->SetGxdvData(Both,Buffer, Len);

    pBS->FreePool(Buffer);

//---------------------------- GXDV END -----------------------------------

Done:
    // Kill event
    pBS->CloseEvent(Event);
}
#endif
#endif


EFI_STATUS ReadSpdData (
	IN  EFI_SMBUS_HC_PROTOCOL	*Smbus,
	IN  UINT8	                SpdSalveAddr,
	IN	UINT8					Offset,
	IN	UINTN					Count,
	OUT	UINT8					*Buffer
	)
{
	EFI_STATUS					Status;
	UINTN						Index;
	UINTN						Length;
	EFI_SMBUS_OPERATION			Operation;
	EFI_SMBUS_DEVICE_COMMAND	Command;
    EFI_SMBUS_DEVICE_ADDRESS    SlaveAddress;

	SlaveAddress.SmbusDeviceAddress = SpdSalveAddr >> 1;


	for (Index = 0; Index < Count; Index++)
	{
		Command = Offset + Index;

		Length = 1;
		Operation = EfiSmbusReadByte;
		Status = Smbus->Execute (Smbus,
							SlaveAddress,
							Command,
							Operation,
							FALSE,
							&Length,
							&Buffer[Index] );
		if (EFI_ERROR(Status)) return Status;
	}

	return EFI_SUCCESS;
}

#define MRC_FREQUENCY_MTB_OFFSET  1000000
#define MRC_FREQUENCY_FTB_OFFSET  1000
#define MRC_DDR3_800_TCK_MIN      2500000   /// 1/(800/2) femtoseconds
#define MRC_DDR3_1000_TCK_MIN     2000000   /// 1/(1000/2) femtoseconds
#define MRC_DDR3_1067_TCK_MIN     1875000   /// 1/(1067/2) femtoseconds
#define MRC_DDR3_1200_TCK_MIN     1666666   /// 1/(1200/2) femtoseconds
#define MRC_DDR3_1333_TCK_MIN     1500000   /// 1/(1333/2) femtoseconds
#define MRC_DDR3_1400_TCK_MIN     1428571   /// 1/(1400/2) femtoseconds
#define MRC_DDR3_1600_TCK_MIN     1250000   /// 1/(1600/2) femtoseconds
#define MRC_DDR3_1800_TCK_MIN     1111111   /// 1/(1800/2) femtoseconds
#define MRC_DDR3_1867_TCK_MIN     1071428   /// 1/(1867/2) femtoseconds
#define MRC_DDR3_2000_TCK_MIN     1000000   /// 1/(2000/2) femtoseconds
#define MRC_DDR3_2133_TCK_MIN     937500    /// 1/(2133/2) femtoseconds
#define MRC_DDR3_2200_TCK_MIN     909090    /// 1/(2200/2) femtoseconds
#define MRC_DDR3_2400_TCK_MIN     833333    /// 1/(2400/2) femtoseconds
#define MRC_DDR3_2600_TCK_MIN     769230    /// 1/(2600/2) femtoseconds
#define MRC_DDR3_2667_TCK_MIN     750000    /// 1/(2667/2) femtoseconds
#define MRC_DDR3_2800_TCK_MIN     714285    /// 1/(2800/2) femtoseconds
#define TREFIMULTIPLIER           1000      /// tREFI value defined in XMP 1.3 spec is actually in thousands of MTB units.
#define MAX(a,b)   (((a) > (b)) ? (a) : (b))
#define MIN(a,b)   (((a) < (b)) ? (a) : (b))

const NbTRangeTable NbRange[] = {
  { 0xFFFFFFFF,            fUnSupport, (0 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_800_TCK_MIN,  f800,       (1 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1000_TCK_MIN, f1000,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1067_TCK_MIN, f1067,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1200_TCK_MIN, f1200,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1333_TCK_MIN, f1333,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1400_TCK_MIN, f1400,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1600_TCK_MIN, f1600,      (1 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1800_TCK_MIN, f1800,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_1867_TCK_MIN, f1867,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2000_TCK_MIN, f2000,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2133_TCK_MIN, f2133,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2200_TCK_MIN, f2200,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2400_TCK_MIN, f2400,      (1 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2600_TCK_MIN, f2600,      (0 << MRC_REF_CLOCK_133) | (1 << MRC_REF_CLOCK_100) },
  { MRC_DDR3_2667_TCK_MIN, f2667,      (1 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) },
  { 0,                     fNoInit,    (0 << MRC_REF_CLOCK_133) | (0 << MRC_REF_CLOCK_100) }
};

static BOOLEAN
NbGetDimmTimeBase (
  IN     SPD_EXTREME_MEMORY_PROFILE  *const XmpSpd,
  IN     UINT8             MemoryProfile,
  OUT    INT32             *const Mtb,
  OUT    INT32             *const Ftb
  )
{
  UINT8                        SpdMtbDividend;
  UINT8                        SpdMtbDivisor;
  UINT8                        SpdFtbDividend;
  UINT8                        SpdFtbDivisor;


    SpdFtbDividend  = XmpSpd->Header.FineTimeBase.Bits.Dividend;
    SpdFtbDivisor   = XmpSpd->Header.FineTimeBase.Bits.Divisor;
    SpdMtbDividend  = XmpSpd->Header.MediumTimeBase[MemoryProfile].Dividend.Bits.Dividend;
    SpdMtbDivisor   = XmpSpd->Header.MediumTimeBase[MemoryProfile].Divisor.Bits.Divisor;

    *Ftb  = (SpdFtbDivisor == 0) ? 0 : (SpdFtbDividend * MRC_FREQUENCY_FTB_OFFSET) / SpdFtbDivisor;
    *Mtb  = (SpdMtbDivisor == 0) ? 0 : (SpdMtbDividend * MRC_FREQUENCY_MTB_OFFSET) / SpdMtbDivisor;

  return (*Mtb == 0) ? FALSE : TRUE;
}

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C

static
MrcFrequency
NbGetDimmFrequency (
  IN     UINT32             tCK
  )
{
  UINT32                              Index;
  MrcFrequency                        XmpFrequency = fNoInit;
  UINT32                              NbRangeSize        = (sizeof (NbRange) / sizeof (NbTRangeTable)) - 1;

  if(tCK == 0 || tCK == 0xffffffff) return fNoInit;

     for (Index = 0; Index < NbRangeSize; Index++) {
       if ((tCK <= NbRange[Index].tCK) && (tCK > NbRange[Index + 1].tCK)) {
         XmpFrequency = NbRange[Index].DDRFreq;
         break;
       }
     }

     while (Index) {
       if ((NbRange[Index].RefClkFlag & (1 << gMemInfoHobProtocol.MemInfoData.RefClk)) == MRC_REF_CLOCK_133) {
         XmpFrequency = NbRange[--Index].DDRFreq;
       } else break;
     }

  return XmpFrequency;
}
/*
static
BOOLEAN
NbGetDimmFrequency (
  IN     SPD_EXTREME_MEMORY_PROFILE  *const XmpSpd,
  IN     UINT8             MemoryProfile,
  IN     UINT8             DimmCount
  )
{
  INT32                               MediumTimebase;
  INT32                               FineTimebase;
  INT32                               tCKminMtb;
  INT32                               tCKminFine;
  INT32                               tCKmin;
  UINT32                              NbRangeSize        = (sizeof (NbRange) / sizeof (NbTRangeTable)) - 1;
  UINT32                              Index;
  UINT32                              TimingMTB;
  INT32                               TimingFTB;
  SPD_EXTREME_MEMORY_PROFILE_DATA     *ExtremeData;
  NbXmpProfileData                    *ProfileTimingData;
  MrcFrequency                        XmpFrequency;
  UINT32                              Calculated;
  UINT32                              tAAmin;
  UINT32                              tAAminFine;

  XmpFrequency = fNoInit;
  tCKmin      = 0;
  tCKminMtb   = 0;
  tCKminFine  = 0;
  TimingMTB   = 0;
  TimingFTB   = 0;
  Calculated  = 0;
  tAAmin      = 0;
  tAAminFine  = 0;

  ProfileTimingData = &XmpDimm[DimmCount].XmpProfileTiming[MemoryProfile];

  if(NbGetDimmTimeBase (XmpSpd, MemoryProfile, &MediumTimebase, &FineTimebase)) {
     ExtremeData = &XmpSpd->Data[MemoryProfile];
     tCKminMtb   = ExtremeData->tCKmin.Bits.tCKmin;
     tCKminFine  = ExtremeData->tCKminFine.Bits.tCKminFine;
     tCKmin = (MediumTimebase * tCKminMtb) + (FineTimebase * tCKminFine);

     for (Index = 0; Index < NbRangeSize; Index++) {
       if ((tCKmin <= NbRange[Index].tCK) && (tCKmin > NbRange[Index + 1].tCK)) {
         XmpFrequency = NbRange[Index].DDRFreq;
         ProfileTimingData->TimingData.tCK = NbRange[Index].tCK;
         break;
       }
     }

     while (Index) {
       if ((NbRange[Index].RefClkFlag & (1 << gMemInfoHobProtocol.MemInfoData.RefClk)) == MRC_REF_CLOCK_133) {
         XmpFrequency = NbRange[--Index].DDRFreq;
       } else break;
     }
//  *tCKminIndex = Index;

     // tCL
     tAAmin     = ExtremeData->tAAmin.Bits.tAAmin;
     tAAminFine = ExtremeData->tAAminFine.Bits.tAAminFine;
     tAAmin  = (MediumTimebase * tAAmin) + (FineTimebase * tAAminFine);
     ProfileTimingData->TimingData.tCL = (UINT16) ((tAAmin + (ProfileTimingData->TimingData.tCK - 1)) / ProfileTimingData->TimingData.tCK);
     ProfileTimingData->TimingData.tCL = MIN (ProfileTimingData->TimingData.tCL, tCL_MAXIMUM);
     // tCWL
     TimingMTB = ExtremeData->tCWLmin.Bits.tCWLmin;
     ProfileTimingData->TimingData.tCWL = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tCWL = MIN (ProfileTimingData->TimingData.tCWL, tCWL_MAXIMUM);
     // tWR
     TimingMTB = ExtremeData->tWRmin.Bits.tWRmin;
     Calculated = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     //
     // Special case, tWRmin values of 9, 11, 13, and 15 are not supported by DDR3 Mode Register 0 (MR0).
     // If we see one of these values, then add one clock to it in order to make it valid.
     //
     if ((9 == Calculated) || (11 == Calculated) || (13 == Calculated) || (15 == Calculated)) {
       Calculated++;
     }
     ProfileTimingData->TimingData.tWR = Calculated;
     ProfileTimingData->TimingData.tWR = MIN (ProfileTimingData->TimingData.tWR, tWR_MAXIMUM);
     // tRRD
     TimingMTB = ExtremeData->tRRDmin.Bits.tRRDmin;
     ProfileTimingData->TimingData.tRRD = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tRRD = MIN (ProfileTimingData->TimingData.tRRD, tRRD_MAXIMUM);
     // tRCD
     TimingMTB = ExtremeData->tRCDmin.Bits.tRCDmin;
     TimingFTB = ExtremeData->tRCDminFine.Bits.tRCDminFine;
     ProfileTimingData->TimingData.tRCD = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tRCD = MIN (ProfileTimingData->TimingData.tRCD, tRCD_MAXIMUM);
     // tRP
     TimingMTB = ExtremeData->tRPmin.Bits.tRPmin;
     TimingFTB = ExtremeData->tRPminFine.Bits.tRPminFine;
     ProfileTimingData->TimingData.tRP = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tRP = MIN (ProfileTimingData->TimingData.tRP, tRP_MAXIMUM);
     // tRAS
     TimingMTB = ((UINT32) (ExtremeData->tRASMintRCMinUpper.Bits.tRASminUpper) << 8) | (UINT32) (ExtremeData->tRASmin.Bits.tRASmin);
     ProfileTimingData->TimingData.tRAS = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tRAS = MIN (ProfileTimingData->TimingData.tRAS, tRAS_MAXIMUM);
     // tRFC
     TimingMTB = ExtremeData->tRFCmin.Bits.tRFCmin;
     ProfileTimingData->TimingData.tRFC = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tRFC = MIN (ProfileTimingData->TimingData.tRFC, tRFC_MAXIMUM);

     // tWTR
     TimingMTB = ExtremeData->tWTRmin.Bits.tWTRmin;
     ProfileTimingData->TimingData.tWTR = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tWTR = MIN (ProfileTimingData->TimingData.tWTR, tWTR_MAXIMUM);

     // tRTP
     TimingMTB = ExtremeData->tRTPmin.Bits.tRTPmin;
     ProfileTimingData->TimingData.tRTP = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tRTP = MIN (ProfileTimingData->TimingData.tRTP, tRTP_MAXIMUM);

     // tFAW
     TimingMTB = ((UINT32) (ExtremeData->tFAWMinUpper.Bits.tFAWminUpper) << 8) | (UINT32) (ExtremeData->tFAWmin.Bits.tFAWmin);
     ProfileTimingData->TimingData.tFAW = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tFAW = MIN (ProfileTimingData->TimingData.tFAW, tFAW_MAXIMUM);

     // tRC
     TimingMTB = ((UINT32) (ExtremeData->tRASMintRCMinUpper.Bits.tRCminUpper) << 8) | (UINT32) (ExtremeData->tRCmin.Bits.tRCmin);
     TimingFTB = ExtremeData->tRCminFine.Bits.tRCminFine;
     ProfileTimingData->TimingData.tRC = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) + (tCKmin - 1)) / tCKmin;
     ProfileTimingData->TimingData.tRC = MIN (ProfileTimingData->TimingData.tRC, tRC_MAXIMUM);

     // tREFI
     TimingMTB = ExtremeData->tREFImin.Bits.tREFImin;
     ProfileTimingData->TimingData.tREFI = (UINT32)Div64 (((Mul64 (MediumTimebase, TimingMTB * TREFIMULTIPLIER) + (tCKmin - 1))), tCKmin, NULL);
     ProfileTimingData->TimingData.tREFI = MIN (ProfileTimingData->TimingData.tREFI, tREFI_MAXIMUM);
     //NMode
     TimingMTB = ExtremeData->SystemCmdRate.Bits.NMode;
     if (TimingMTB > 0) {
        ProfileTimingData->TimingData.NMode  = ((MediumTimebase * TimingMTB) + (tCKmin - 1)) / tCKmin;
     }
  }

  ProfileTimingData->DDRFreq = XmpFrequency;

  if (XmpFrequency != fNoInit) return TRUE;

  return FALSE;
}
*/
#endif
#endif

EFI_STATUS NbReportXmpInfo(
  IN EFI_EVENT          Event,
  IN VOID               *Context
)
{
/*
	EFI_STATUS					Status;
	EFI_SMBUS_HC_PROTOCOL		*Smbus;
    SPD_EXTREME_MEMORY_PROFILE  XmpSpd;
    VOID                        *SpdData = &XmpSpd;
    UINT8                       i, DimmCount;

    Status = pBS->LocateProtocol( &gEfiSmbusProtocolGuid, \
                                  NULL, \
                                  &Smbus );
    if (EFI_ERROR(Status))return Status;


    for (i = DIMM1_SMBUS_ADDRESS, DimmCount = 0; DimmCount < 4; i += 2, DimmCount++) {
       Status = ReadSpdData(Smbus, i, 176, 2, (UINT8*)SpdData);
       if (EFI_ERROR(Status) || (XmpSpd.Header.XmpId != 0x4A0C)) continue;
       Status = ReadSpdData(Smbus, i, 176, 79, (UINT8*)SpdData);
       if (EFI_ERROR(Status)) continue;

       if(XmpSpd.Header.XmpOrgConf.Bits.ProfileEnable1) {
         NBPlatformData.XmpProfile1 = 1;
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
         NbGetDimmFrequency (SpdData, 0, DimmCount);
#endif
#endif
       } else continue;

       if(XmpSpd.Header.XmpOrgConf.Bits.ProfileEnable2) {
         NBPlatformData.XmpProfile2 = 1;
#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
         NbGetDimmFrequency (SpdData, 1, DimmCount);
#endif
#endif
       }
    }

#if defined PERF_TUNE_SUPPORT && PERF_TUNE_SUPPORT == 1
#if defined IXTU_LABLE_VERSION && IXTU_LABLE_VERSION >= 0x00C
    // Channel 0 XmpProfile 1~2
    XmpChannel[0].XmpProfileTiming[0].DDRFreq = MAX(XmpDimm[0].XmpProfileTiming[0].DDRFreq, XmpDimm[1].XmpProfileTiming[0].DDRFreq);
    XmpChannel[0].XmpProfileTiming[1].DDRFreq = MAX(XmpDimm[0].XmpProfileTiming[1].DDRFreq, XmpDimm[1].XmpProfileTiming[1].DDRFreq);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tCL = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tCL, XmpDimm[1].XmpProfileTiming[0].TimingData.tCL);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tCL = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tCL, XmpDimm[1].XmpProfileTiming[1].TimingData.tCL);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tCWL = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tCWL, XmpDimm[1].XmpProfileTiming[0].TimingData.tCWL);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tCWL = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tCWL, XmpDimm[1].XmpProfileTiming[1].TimingData.tCWL);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tWR = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tWR, XmpDimm[1].XmpProfileTiming[0].TimingData.tWR);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tWR = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tWR, XmpDimm[1].XmpProfileTiming[1].TimingData.tWR);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tRRD = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tRRD, XmpDimm[1].XmpProfileTiming[0].TimingData.tRRD);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tRRD = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tRRD, XmpDimm[1].XmpProfileTiming[1].TimingData.tRRD);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tRCD = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tRCD, XmpDimm[1].XmpProfileTiming[0].TimingData.tRCD);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tRCD = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tRCD, XmpDimm[1].XmpProfileTiming[1].TimingData.tRCD);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tRP = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tRP, XmpDimm[1].XmpProfileTiming[0].TimingData.tRP);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tRP = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tRP, XmpDimm[1].XmpProfileTiming[1].TimingData.tRP);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tRAS = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tRAS, XmpDimm[1].XmpProfileTiming[0].TimingData.tRAS);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tRAS = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tRAS, XmpDimm[1].XmpProfileTiming[1].TimingData.tRAS);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tRFC = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tRFC, XmpDimm[1].XmpProfileTiming[0].TimingData.tRFC);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tRFC = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tRFC, XmpDimm[1].XmpProfileTiming[1].TimingData.tRFC);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tWTR = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tWTR, XmpDimm[1].XmpProfileTiming[0].TimingData.tWTR);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tWTR = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tWTR, XmpDimm[1].XmpProfileTiming[1].TimingData.tWTR);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tRTP = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tRTP, XmpDimm[1].XmpProfileTiming[0].TimingData.tRTP);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tRTP = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tRTP, XmpDimm[1].XmpProfileTiming[1].TimingData.tRTP);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tFAW = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tRC, XmpDimm[1].XmpProfileTiming[0].TimingData.tFAW);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tFAW = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tRC, XmpDimm[1].XmpProfileTiming[1].TimingData.tFAW);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tREFI = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tREFI, XmpDimm[1].XmpProfileTiming[0].TimingData.tREFI);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tREFI = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tREFI, XmpDimm[1].XmpProfileTiming[1].TimingData.tREFI);
    XmpChannel[0].XmpProfileTiming[0].TimingData.tRC = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.tRC, XmpDimm[1].XmpProfileTiming[0].TimingData.tRC);
    XmpChannel[0].XmpProfileTiming[1].TimingData.tRC = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.tRC, XmpDimm[1].XmpProfileTiming[1].TimingData.tRC);
    XmpChannel[0].XmpProfileTiming[0].TimingData.NMode = MAX(XmpDimm[0].XmpProfileTiming[0].TimingData.NMode, XmpDimm[1].XmpProfileTiming[0].TimingData.NMode);
    XmpChannel[0].XmpProfileTiming[1].TimingData.NMode = MAX(XmpDimm[0].XmpProfileTiming[1].TimingData.NMode, XmpDimm[1].XmpProfileTiming[1].TimingData.NMode);

    // Channel 1 XmpProfile 1~2
    XmpChannel[1].XmpProfileTiming[0].DDRFreq = MAX(XmpDimm[2].XmpProfileTiming[0].DDRFreq, XmpDimm[3].XmpProfileTiming[0].DDRFreq);
    XmpChannel[1].XmpProfileTiming[1].DDRFreq = MAX(XmpDimm[2].XmpProfileTiming[1].DDRFreq, XmpDimm[3].XmpProfileTiming[1].DDRFreq);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tCL = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tCL, XmpDimm[3].XmpProfileTiming[0].TimingData.tCL);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tCL = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tCL, XmpDimm[3].XmpProfileTiming[1].TimingData.tCL);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tCWL = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tCWL, XmpDimm[3].XmpProfileTiming[0].TimingData.tCWL);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tCWL = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tCWL, XmpDimm[3].XmpProfileTiming[1].TimingData.tCWL);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tWR = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tWR, XmpDimm[3].XmpProfileTiming[0].TimingData.tWR);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tWR = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tWR, XmpDimm[3].XmpProfileTiming[1].TimingData.tWR);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tRRD = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tRRD, XmpDimm[3].XmpProfileTiming[0].TimingData.tRRD);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tRRD = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tRRD, XmpDimm[3].XmpProfileTiming[1].TimingData.tRRD);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tRCD = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tRCD, XmpDimm[3].XmpProfileTiming[0].TimingData.tRCD);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tRCD = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tRCD, XmpDimm[3].XmpProfileTiming[1].TimingData.tRCD);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tRP = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tRP, XmpDimm[3].XmpProfileTiming[0].TimingData.tRP);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tRP = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tRP, XmpDimm[3].XmpProfileTiming[1].TimingData.tRP);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tRAS = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tRAS, XmpDimm[3].XmpProfileTiming[0].TimingData.tRAS);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tRAS = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tRAS, XmpDimm[3].XmpProfileTiming[1].TimingData.tRAS);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tRFC = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tRFC, XmpDimm[3].XmpProfileTiming[0].TimingData.tRFC);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tRFC = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tRFC, XmpDimm[3].XmpProfileTiming[1].TimingData.tRFC);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tWTR = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tWTR, XmpDimm[3].XmpProfileTiming[0].TimingData.tWTR);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tWTR = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tWTR, XmpDimm[3].XmpProfileTiming[1].TimingData.tWTR);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tRTP = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tRTP, XmpDimm[3].XmpProfileTiming[0].TimingData.tRTP);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tRTP = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tRTP, XmpDimm[3].XmpProfileTiming[1].TimingData.tRTP);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tFAW = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tRC, XmpDimm[3].XmpProfileTiming[0].TimingData.tFAW);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tFAW = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tRC, XmpDimm[3].XmpProfileTiming[1].TimingData.tFAW);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tREFI = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tREFI, XmpDimm[3].XmpProfileTiming[0].TimingData.tREFI);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tREFI = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tREFI, XmpDimm[3].XmpProfileTiming[1].TimingData.tREFI);
    XmpChannel[1].XmpProfileTiming[0].TimingData.tRC = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.tRC, XmpDimm[3].XmpProfileTiming[0].TimingData.tRC);
    XmpChannel[1].XmpProfileTiming[1].TimingData.tRC = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.tRC, XmpDimm[3].XmpProfileTiming[1].TimingData.tRC);
    XmpChannel[1].XmpProfileTiming[0].TimingData.NMode = MAX(XmpDimm[2].XmpProfileTiming[0].TimingData.NMode, XmpDimm[3].XmpProfileTiming[0].TimingData.NMode);
    XmpChannel[1].XmpProfileTiming[1].TimingData.NMode = MAX(XmpDimm[2].XmpProfileTiming[1].TimingData.NMode, XmpDimm[3].XmpProfileTiming[1].TimingData.NMode);

    // Output XmpProfile 1~2
    XmpProfileTiming[0].DDRFreq = MAX(XmpChannel[0].XmpProfileTiming[0].DDRFreq, XmpChannel[1].XmpProfileTiming[0].DDRFreq);
    XmpProfileTiming[1].DDRFreq = MAX(XmpChannel[0].XmpProfileTiming[1].DDRFreq, XmpChannel[1].XmpProfileTiming[1].DDRFreq);
    XmpProfileTiming[0].TimingData.tCL = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tCL, XmpChannel[1].XmpProfileTiming[0].TimingData.tCL);
    XmpProfileTiming[1].TimingData.tCL = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tCL, XmpChannel[1].XmpProfileTiming[1].TimingData.tCL);
    XmpProfileTiming[0].TimingData.tCWL = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tCWL, XmpChannel[1].XmpProfileTiming[0].TimingData.tCWL);
    XmpProfileTiming[1].TimingData.tCWL = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tCWL, XmpChannel[1].XmpProfileTiming[1].TimingData.tCWL);
    XmpProfileTiming[0].TimingData.tWR = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tWR, XmpChannel[1].XmpProfileTiming[0].TimingData.tWR);
    XmpProfileTiming[1].TimingData.tWR = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tWR, XmpChannel[1].XmpProfileTiming[1].TimingData.tWR);
    XmpProfileTiming[0].TimingData.tRRD = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tRRD, XmpChannel[1].XmpProfileTiming[0].TimingData.tRRD);
    XmpProfileTiming[1].TimingData.tRRD = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tRRD, XmpChannel[1].XmpProfileTiming[1].TimingData.tRRD);
    XmpProfileTiming[0].TimingData.tRCD = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tRCD, XmpChannel[1].XmpProfileTiming[0].TimingData.tRCD);
    XmpProfileTiming[1].TimingData.tRCD = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tRCD, XmpChannel[1].XmpProfileTiming[1].TimingData.tRCD);
    XmpProfileTiming[0].TimingData.tRP = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tRP, XmpChannel[1].XmpProfileTiming[0].TimingData.tRP);
    XmpProfileTiming[1].TimingData.tRP = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tRP, XmpChannel[1].XmpProfileTiming[1].TimingData.tRP);
    XmpProfileTiming[0].TimingData.tRAS = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tRAS, XmpChannel[1].XmpProfileTiming[0].TimingData.tRAS);
    XmpProfileTiming[1].TimingData.tRAS = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tRAS, XmpChannel[1].XmpProfileTiming[1].TimingData.tRAS);
    XmpProfileTiming[0].TimingData.tRFC = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tRFC, XmpChannel[1].XmpProfileTiming[0].TimingData.tRFC);
    XmpProfileTiming[1].TimingData.tRFC = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tRFC, XmpChannel[1].XmpProfileTiming[1].TimingData.tRFC);
    XmpProfileTiming[0].TimingData.tWTR = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tWTR, XmpChannel[1].XmpProfileTiming[0].TimingData.tWTR);
    XmpProfileTiming[1].TimingData.tWTR = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tWTR, XmpChannel[1].XmpProfileTiming[1].TimingData.tWTR);
    XmpProfileTiming[0].TimingData.tRTP = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tRTP, XmpChannel[1].XmpProfileTiming[0].TimingData.tRTP);
    XmpProfileTiming[1].TimingData.tRTP = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tRTP, XmpChannel[1].XmpProfileTiming[1].TimingData.tRTP);
    XmpProfileTiming[0].TimingData.tFAW = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tFAW, XmpChannel[1].XmpProfileTiming[0].TimingData.tFAW);
    XmpProfileTiming[1].TimingData.tFAW = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tFAW, XmpChannel[1].XmpProfileTiming[1].TimingData.tFAW);
    XmpProfileTiming[0].TimingData.tREFI = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tREFI, XmpChannel[1].XmpProfileTiming[0].TimingData.tREFI);
    XmpProfileTiming[1].TimingData.tREFI = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tREFI, XmpChannel[1].XmpProfileTiming[1].TimingData.tREFI);
    XmpProfileTiming[0].TimingData.tRC = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.tRC, XmpChannel[1].XmpProfileTiming[0].TimingData.tRC);
    XmpProfileTiming[1].TimingData.tRC = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.tRC, XmpChannel[1].XmpProfileTiming[1].TimingData.tRC);
    XmpProfileTiming[0].TimingData.NMode = MAX(XmpChannel[0].XmpProfileTiming[0].TimingData.NMode, XmpChannel[1].XmpProfileTiming[0].TimingData.NMode);
    XmpProfileTiming[1].TimingData.NMode = MAX(XmpChannel[0].XmpProfileTiming[1].TimingData.NMode, XmpChannel[1].XmpProfileTiming[1].TimingData.NMode);
#endif
#endif

    Status = pRS->SetVariable (
      L"NBPlatformData",
      &gSetupGuid,
      EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
      sizeof (NB_PLATFORM_DATA),
      &NBPlatformData
      );
    ASSERT_EFI_ERROR (Status);

    // Kill event
    pBS->CloseEvent(Event);
*/
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
