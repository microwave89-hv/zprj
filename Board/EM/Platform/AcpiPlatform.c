//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/EM/Platform/AcpiPlatform.c 4     4/19/16 7:43a Chienhsieh $
//
// $Revision: 4 $
//
// $Date: 4/19/16 7:43a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/EM/Platform/AcpiPlatform.c $
// 
// 4     4/19/16 7:43a Chienhsieh
// 
// 34    7/11/14 4:00a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Support Debug Port Table.
// [Files]  		AcpiPlatform.c
// AcpiPlatform.h
// AcpiPlatform.cif
// 
// 33    5/15/14 3:14a Joshchou
// [TAG]  		EIP167036
// [Category]  	Improvement
// [Description]  	 review the attributes of variable.
// [Files]  		AcpiPlatform.c
// AcpiPlatform.h
// AcpiPlatform.sd
// AcpiPlatform.cif
// 
// 32    4/23/14 4:21a Joshchou
// 
// 31    9/27/13 10:43a Joshchou
// [TAG]  		EIP137454
// [Category]  	New Feature
// [Description]  	Follow Intel sample code to add LPIT table.
// 
// 30    9/18/13 8:00a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Fix the CppCheck error.
// 
// 29    9/18/13 6:25a Joshchou
// [TAG]  		EIP136411
// [Category]  	Improvement
// [Description]  	Support MWAIT LPI State Descriptor[1].
// 
// 28    7/19/13 2:57a Alanlin
// [TAG] None
// [Category] Important
// [Severity] Important
// [Description] Fixed the system may hang up when DEBUG_MODE is ON.
// While trying to use SetAcpiTable to create LPIT table, reture status is
// EFI_INVALID_PARAMETER.
// [Files] AcpiPlatform.c
// 
// 27    7/16/13 5:58a Alanlin
// [TAG] EIP125350
// [Category] Normal
// [Severity] Normal
// [Description] System BIOS Support for the Hardware Button for Windows*
// 8.1 - Rev.0.5
// [Files] AcpiPlatform.c, AcpiPlatform.sd, AcpiPlatform.uni
// 
// [TAG] EIP127540
// [Category] Normal
// [Severity] Normal
// [Description] Windows* 8.1 Micro-PEP (uPEP) ASL Support Version 0.5
// [Files] AcpiPlatform.c, AcpiPlatform.h
// 
// 26    7/15/13 5:32a Alanlin
// [TAG] EIP129086
// [Category] Important
// [Severity] Important
// [Description] Update Shark Bay Client ACPI Reference Code Beta Version
// 1.6.1
// 
// 25    6/28/13 5:22a Alanlin
// [TAG] None
// [Category] Important
// [Severity] Important
// [Description]  Fixed that Processors device are disappeared under OS
// device manager.
// [Files] AcpiPlatform.c, AcpiPlatform.h
// 
// 24    6/04/13 10:18a Alanlin
// [TAG] None 
// [Category] Improvement
// [Severity] Normal
// [Description] Follow Intel CRB BIOS v126 to set default configuraton
// setting of RTD3 devices.
// [Files] AcpiPlatform.c, AcpiPlatform.sd, AcpiPlatform.uni
// 
// 23    3/26/13 9:30a Alanlin
// [TAG] EIP119125
// [Category] Important
// [Severity] Important
// [Description] Update Shark Bay Client ACPI Reference Code Beta Version
// 1.3.1
// 
// 22    3/15/13 6:59a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Add a "Remove_SaSsdt_Data_To_Dsdt" token, it can remove
// related Sa Ssdt acpi data to Dsdt.
// [Files] PlatformExternal.asl, Acpiplatform.c, EC.asl, GloblNvs.asl,
// Gpe.asl, Video.asl.
// 
// 21    2/21/13 1:16a Alanlin
// [TAG] EIP114876
// [Category] Normal
// [Severity] Normal
// [Description] To close Readytoboot event-function : CallbackBootScript
// 
// 20    2/15/13 1:12a Alanlin
// [TAG] EIP114919
// [Category] Important
// [Severity] Important
// [Description] Update Shark Bay Client ACPI Reference Code Beta Version
// 1.1.0
// 
// 19    1/28/13 11:13p Alanlin
// [TAG] EIP113555
// [Category] Important
// [Severity] Important
// [Description] Update Shark Bay Client ACPI Reference Code Beta Version
// 1.0.0
// 
// 18    1/18/13 3:57a Alanlin
// 
// 17    1/15/13 5:46a Alanlin
// [TAG] None
// [Category] Normal
// [Severity] Normal
// [Description] Add setup item and setting for DPTF
// [Files] Acpiplatform.c, Acpiplatform.sd, Acpiplatform.uni,
// PlatformSetup.h
// 
// 16    12/18/12 11:02p Alanlin
// [TAG] EIP107188
// [Category] Important
// [Severity] Important
// [Description] USB 3.0 port can't work when RTD3 is Enabled in setup
// menu.
// [Files] Acpiplatform.c, Acpiplatform.mak, Acpiplatform.sd,
// Acpiplatform.uni.
// 
// 15    11/26/12 6:04a Alanlin
// [TAG] None
// [Category] Improvement
// [Severity] Normal
// [Description] Include Rtd3FFRD.asl for Haswell - FFRD SKU Board.
//                       BRRtd3.asl for Haswell - Basking Ridge Board.
// [Files] SsdtRtd3.cif, SsdtRtd3.sdl, Rtd3FFRD.asl, BRRtd3.asl,
// Acpiplatform.c
// 
// [TAG] None
// [Category] Improvement
// [Severity] Important
// [Description] Fixed the system has blue screen when RTD3 is Enabled.
// [Files] SsdtZpOdd.sdl, Acpiplatform.c
// 
// 14    11/20/12 7:08a Alanlin
// [TAG] None
// [Category] New Feature
// [Severity] Important
// [Description] SensorHub SSDT acpi table support
// [Files] Acpiplatform.c, Acpiplatform.cif, Acpiplatform.h,
// SsdtSensorHub.asl, SsdtSensorHub.mak, SsdtSensorHub.sdl 
// 
// [TAG] None
// [Category] Important
// [Severity] Important
// [Description] Update Shark Bay Client ACPI Reference Code Beta Version
// 0.8.0
// 
// 13    11/09/12 5:17a Alanlin
// [TAG]           None
// [Category]      New Feature
// [Severity]      Important
// [Description]   ZpOdd SSDT acpi table support
// [Files]         Acpiplatform.c, Acpiplatform.cif, Acpiplatform.h,
//                 Acpiplatform.sd, Acpiplatform.uni
// 
// 12    10/31/12 4:38a Alanlin
// [TAG]         None
// [Category]    Improvement
// [Severity]    Normal
// [Description] Fine tune Platform Board Information.
// 
// [TAG]         None
// [Category]    New Feature
// [Severity]    Normal
// [Description] Support Acpi Debug SSDT.              
//  
// [TAG]         None
// [Category]    Improvement
// [Severity]    Normal
// [Description] Removed all SaGlobalNvsArea Structure, move to SA module
// to initial.   
// 
// 11    10/15/12 11:40a Alanlin
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Updated for RC 0.7.1
// 
// 10    9/12/12 7:20a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Remove AOAC for Intel Smart Connect Technology module.
// [Files]         GlobalNvsArea.h, GloblNvs.asl
// 
// 9     8/31/12 4:47a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Update Board ID for Haswell platform.
// [Files]         AcpiPlatform.c, AcpiPlatform.sdl, PlatformInfo.sdl,
// AcpiAsl.sdl
// 
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Implement Runtime D3.
// [Files]         AcpiPlatform.c, AcpiPlatform.cif, AcpiPlatform.h,
// AcpiPlatform.sd, AcpiPlatform.sdl, AcpiPlatform.uni, GlobalNvsArea.h,
// SsdtRtd3.cif, SsdtRtd3.mak, Ult0Rtd3.asl, SsdtRtd3.sdl
// 
// 8     8/14/12 9:19a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Remove useless Dppm policy.
// [Files]       AcpiPlatform.c
// 
// 7     7/27/12 5:11a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Create DPTF and CPPC setup item.
// [Files]       AcpiPlatform.c, AcpiPlatform.sd, AcpiPlatform.uni,
// PlatformSetup.h
// 
// 6     7/03/12 1:28a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Update Shark Bay Client ACPI Reference Code Alpha 2
// 0.6.0.
// [Files]       ReferenceCode\AcpiTables\*.*, GlobalNvsArea.h,
// AcpiPlatform.c, PlatformInfo.c, PlatformEC.asl
// 
// 5     4/25/12 1:28p Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Initilize ACPI DXE Platform Policy.
// [Files]       AcpiPlatform.c, AcpiPlatform.mak
// 
// 3     4/05/12 7:46a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Severity]    Important
// [Description] Fixed building error for Intel System Agent
// Label:"4.6.5.3_Intel_SA-RC_055_004".
// [Files]       PlatformSetupInfo.c, PlatformSetupInfo.mak,
// AcpiPlatform.c, PlatformInfo.c
// 
// 1     2/09/12 12:30a Yurenlai
// Initial check in.
// 
//*************************************************************************
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        AcpiPlatform.c
//
// Description: Installs EFI_GLOBAL_NVS_AREA_PROTOCOL_GUID
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <token.h>
#include <Acpi11.h>
#include <Acpi20.h>
#include <Protocol\AcpiSupport.h>
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
///#include "CPUCspLib.h"
//#include "EfiCommonLib.h"
//#include "CpuFuncs.h"
///#include "Cpu.h"
//#include <Acpi.h>
#include <AcpiRes.h>
#include <SaGlobalNvsArea\SaGlobalNvsArea.h>
#include <Protocol\GlobalNvsArea\GlobalNvsArea.h>
#include <AcpiPlatform.h>
#include <PlatformInfo.h>
#include <Setup.h>
#if CRB_EC_SUPPORT == 1
#include <KscLib.h>
#endif
#include <Protocol\PchPlatformPolicy\PchPlatformPolicy.h>
#include <PlatformSetup.h>

#ifndef PPM_C3
#define PPM_C3                    0x8
#endif

#ifndef FADT_C3_LATENCY
#define FADT_C3_LATENCY    57
#endif

EFI_GUID gEfiGlobalNvsAreaProtocolGuid = EFI_GLOBAL_NVS_AREA_PROTOCOL_GUID;
EFI_GUID gEfiGlobalSaNvsAreaProtocolGuid = EFI_GLOBAL_SANVS_AREA_PROTOCOL_GUID;
EFI_GUID gPlatformInfoProtocolGuid = EFI_PLATFORM_INFO_PROTOCOL_GUID;
EFI_GUID gSetupGuid = SETUP_GUID;
#if defined   PTID_SUPPORT && PTID_SUPPORT
EFI_GUID gAcpiPtidFfsTableStorageGuid = PTID_FFS_TABLE_STORAGE_GUID;
#endif
#if defined   IntelRMT_SUPPORT && IntelRMT_SUPPORT
EFI_GUID gAcpiIRMTFfsTableStorageGuid = IRMT_FFS_TABLE_STORAGE_GUID;
#endif
#if defined   RTD3_SUPPORT && RTD3_SUPPORT
EFI_GUID gAcpiRtd3FfsTableGuid = RTD3_FFS_TABLE_GUID;
#endif
#if defined   ACPIDEBUG_SUPPORT && ACPIDEBUG_SUPPORT
EFI_GUID gAcpiDebugFfsTableGuid = ACPIDEBUG_FFS_TABLE_GUID;
#endif
#if defined   ZPODD_SUPPORT && ZPODD_SUPPORT
EFI_GUID gAcpiZpOddFfsTableGuid = ZPODD_FFS_TABLE_GUID;
#endif
#if defined   INTELSENSORHUB_SUPPORT && INTELSENSORHUB_SUPPORT
EFI_GUID gAcpiIntelSensorHubFfsTableGuid = INTELSENSORHUB_FFS_TABLE_GUID;
#endif
#if defined LPIT_SUPPORT && LPIT_SUPPORT
EFI_GUID gAcpiLpitGuid = LPIT_GUID;
#endif

EFI_GLOBAL_NVS_AREA_PROTOCOL  mGlobalNvsArea;
SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL    gSaGlobalNvsArea;

VOID *GetDSDTTable ();
EFI_ACPI_SUPPORT_PROTOCOL	*gEfiAcpiSupport = 0;
PLATFORM_INFO_PROTOCOL      *gPlatformInfoProtocol;
VOID CallbackBootScript(IN EFI_EVENT Event, IN VOID *Context);
EFI_EVENT                   gEvtBootScript;
static  SETUP_DATA          *gSetupData = NULL;

VOID DsdtTableUpdate (PACPI_HDR   DsdtTable);
//VOID DsdtTableUpdate1 (PACPI_HDR   DsdtTable);
VOID LoadDbgpTable();

#if defined LPIT_SUPPORT && LPIT_SUPPORT
VOID LoadLpitTable ();
#endif
#if defined   PTID_SUPPORT && PTID_SUPPORT
VOID LoadSsdtPtidTable ();
EFI_STATUS LocateSupportProtocol (IN EFI_GUID *Protocol,OUT VOID **Instance,IN BOOLEAN Type );
#endif
#if defined   IntelRMT_SUPPORT && IntelRMT_SUPPORT
VOID LoadSsdtIRMTTable ();
EFI_STATUS LocateIRMTSupportProtocol (IN EFI_GUID *Protocol,OUT VOID **Instance,IN BOOLEAN Type );
#endif
#if defined   RTD3_SUPPORT && RTD3_SUPPORT
VOID LoadSsdtRtd3Table ();
EFI_STATUS LocateRTD3SupportProtocol (IN EFI_GUID *Protocol,OUT VOID **Instance,IN BOOLEAN Type );
#endif
#if defined   ACPIDEBUG_SUPPORT && ACPIDEBUG_SUPPORT
VOID LoadSsdtAcpiDebugTable ();
EFI_STATUS LocateAcpiDebugSupportProtocol (IN EFI_GUID *Protocol,OUT VOID **Instance,IN BOOLEAN Type );
#define  AcpiDebugBufferSize    0x10000 // 64k buffer data
#define  ACPI_DEBUG_STR "INTEL ACPI DEBUG"
#define  AML_NAME_OP         0x08
#if defined   ZPODD_SUPPORT && ZPODD_SUPPORT
VOID LoadSsdtZpOddTable ();
EFI_STATUS LocateZPODDSupportProtocol (IN EFI_GUID *Protocol,OUT VOID **Instance,IN BOOLEAN Type );
#endif
#if defined   INTELSENSORHUB_SUPPORT && INTELSENSORHUB_SUPPORT
VOID LoadSsdtIntelSensorHubTable ();
EFI_STATUS LocateIntelSensorHubSupportProtocol (IN EFI_GUID *Protocol,OUT VOID **Instance,IN BOOLEAN Type );
#endif

//
// ASL NAME structure 
//
#pragma pack(1)
typedef struct {
  UINT8   NameOp;       //  Byte [0]=0x08:NameOp.
  UINT32  NameString;   //  Byte [4:1]=Name of object.
  UINT8   DWordPrefix;  //  Byte [5]=0x0C:DWord Prefix.
  UINT32  Value;        //  0   ; Value of named object.
} NAME_LAYOUT;
#pragma pack()
#endif

#include <AcpiInfo\AcpiInfo.h>
#include <AcpiPlatformPolicy\AcpiPlatformPolicy.h>
EFI_GUID gAcpiPlatformPolicyProtocolGuid = ACPI_PLATFORM_POLICY_PROTOCOL_GUID;

// Protocols that are installed
ACPI_PLATFORM_POLICY_PROTOCOL mAcpiPlatformPolicyProtocol = { 0 };
EFI_ACPI_INFO_PROTOCOL      mAcpiInfoProtocol = { 0 };

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CheckPlatformSupportRtD3
//
// Description: Check if platform support RtD3
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckPlatformSupportRtD3 ()
{
  BOOLEAN                       RtD3Supported;
  PCH_SERIES                    PchSeries = GetPchSeries();

      RtD3Supported = FALSE;
  if (IS_SA_DEVICE_ID_MOBILE (READ_PCI16_NB (R_SA_MC_DEVICE_ID))) {
     if (PchSeries == PchLp) {
      RtD3Supported = TRUE;
     }
  }

  return RtD3Supported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CheckPlatformSupportCPPC
//
// Description: Check if platform support CPPC
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckPlatformSupportCPPC ()
{
  BOOLEAN                       CPPCSupported;

  if (!(IS_SA_DEVICE_ID_MOBILE (READ_PCI16_NB (R_SA_MC_DEVICE_ID)))) {
      CPPCSupported = FALSE;
  } else {
      CPPCSupported = TRUE;
  }

  return CPPCSupported;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InstallAcpiDxePlatformPolicy
//
// Description: Initilize ACPI DXE Platform Policy.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InstallAcpiDxePlatformPolicy (IN UINT32 SetupAttributes)
{
    EFI_STATUS                   Status;
    EFI_HANDLE                   Handle;
    SETUP_PLATFORM_DATA          SetupPlatformData;

  ///
  /// Initialize the EFI Driver Library
  ///
  mAcpiPlatformPolicyProtocol.Revision        = ACPI_PLATFORM_POLICY_PROTOCOL_REVISION_1;
  mAcpiPlatformPolicyProtocol.BoardId         = gPlatformInfoProtocol->BoardId;

  mAcpiPlatformPolicyProtocol.EnableDptf      = 0;
  mAcpiPlatformPolicyProtocol.EnableCppc      = 0;
  mAcpiPlatformPolicyProtocol.EnableCppcPlatformSCI = 0;
  
  TRACE((TRACE_ALWAYS, "InstallAcpiDxePlatformPolicy setup variable attributes = %x \n", SetupAttributes));

  SetupPlatformData.PlatformSupportCppc       = 0;     
  SetupPlatformData.PlatformSupportRtD3       = 0;

#if ACPIDEBUG_SUPPORT
  if (gSetupData != NULL) {
    mAcpiPlatformPolicyProtocol.EnableAcpiDebug = gSetupData->AcpiDebugSupport;
  }
#endif

#if RTD3_SUPPORT
  if (!CheckPlatformSupportRtD3()) {
    mAcpiPlatformPolicyProtocol.EnableRtD3 = 0;
  } else if (gSetupData != NULL) {
    SetupPlatformData.PlatformSupportRtD3 = 1;
    mAcpiPlatformPolicyProtocol.EnableRtD3 = gSetupData->Rtd3Support;
  }
#endif

#if Dptf_SUPPORT
  if (gSetupData != NULL) {
    mAcpiPlatformPolicyProtocol.EnableDptf      = gSetupData->EnableDptf;
    if(gSetupData->EnableDptf==1){
      if (gSetupData->EnableSaDevice==1){
         gSetupData->SaDevice4=1;
      }
      else{
         gSetupData->SaDevice4=0;         
      }
      gSetupData->ThermalDeviceEnable=gSetupData->EnablePchDevice;
    }

    Status = pRS->SetVariable (
       L"Setup",
       &gSetupGuid,
       SetupAttributes,
       sizeof(SETUP_DATA),
       gSetupData
    );
  }
#endif

#if CPPC_SUPPORT
  if (!CheckPlatformSupportCPPC()) {
    mAcpiPlatformPolicyProtocol.EnableCppc      = 0;
    mAcpiPlatformPolicyProtocol.EnableCppcPlatformSCI = 0;
  } else if (gSetupData != NULL) {
    SetupPlatformData.PlatformSupportCppc = 1;
    mAcpiPlatformPolicyProtocol.EnableCppc      = gSetupData->EnableCppc;
    mAcpiPlatformPolicyProtocol.EnableCppcPlatformSCI = gSetupData->EnableCppcPlatformSCI;
  }
#endif

  TRACE((TRACE_ALWAYS, "SetupPlatformData.PlatformSupportCppc = %x \n", SetupPlatformData.PlatformSupportCppc)); 
  TRACE((TRACE_ALWAYS, "SetupPlatformData.PlatformSupportRtD3 = %x \n", SetupPlatformData.PlatformSupportRtD3)); 

  Status = pRS->SetVariable (
    L"SetupPlatformData",
    &gSetupGuid,
    EFI_VARIABLE_BOOTSERVICE_ACCESS,
    sizeof (SETUP_PLATFORM_DATA),
    &SetupPlatformData
    );
  TRACE((TRACE_ALWAYS, "SetVariable SetupPlatformData Status = %r \n", Status));

  Handle = NULL;
  Status = pBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gAcpiPlatformPolicyProtocolGuid,
                  &mAcpiPlatformPolicyProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Install ACPI_INFO_PROTOCOL
  ///
  mAcpiInfoProtocol.Revision   = ACPI_INFO_PROTOCOL_REVISION_1;
  ///
  /// RCVersion[32:0] is the release number.
  /// For example: 
  /// Acpi Framework 0.5.0 should be 00 05 00 00 (0x00050000)
  ///
  mAcpiInfoProtocol.RCVersion  = ACPI_RC_VERSION;

  Handle = NULL;
  Status = pBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gEfiAcpiInfoProtocolGuid,
                  &mAcpiInfoProtocol,
                  NULL
                  );


  return Status;

}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	AcpiPlatformInit
//
// Description:
//
// Input:
//
// Output:
//      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//  Here is the control flow of this function:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS 
AcpiPlatformInit (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_GUID                gAcpiSupportGuid = EFI_ACPI_SUPPORT_GUID; 
  PACPI_HDR               DsdtTable;
  UINT32                  Length;
  UINT8                   *ptr;
  UINT32                  RegEax, RegEbx, RegEcx, RegEdx;
  ASL_OBJ_INFO            ObjInfo;
  MSR_REGISTER            MsrCoreThreadCount;  
#if CRB_EC_SUPPORT == 1
  UINT8                   PortDataOut = 0;
#endif
  UINT8                   ECSmbusThermalReportingEnabled = 0;
  UINT8                   ECSMBusMsgLenth = 0;
  UINT8                   ECSMBusPECEnabled = 0;
  NB_SETUP_DATA           *NbSetupData = NULL;
  SB_SETUP_DATA           *SbSetupData = NULL;
  UINTN                   VariableSize = NULL;
  UINT16                  McDeviceId;
  UINT8					  USBRTD3 = 0;
  PCH_SERIES                    PchSeries = GetPchSeries();
  UINT32                  SetupAttributes = 0;

  InitAmiLib(ImageHandle,SystemTable);

  Status = pBS->AllocatePool (EfiACPIMemoryNVS, 
                              sizeof (EFI_GLOBAL_NVS_AREA), 
                              &mGlobalNvsArea.Area);
  ASSERT_EFI_ERROR (Status);
  pBS->SetMem (mGlobalNvsArea.Area, sizeof (EFI_GLOBAL_NVS_AREA), 0);

#if defined   Remove_SaSsdt_Data_To_Dsdt && Remove_SaSsdt_Data_To_Dsdt
  Status = pBS->AllocatePool (EfiACPIMemoryNVS, 
                              sizeof (SYSTEM_AGENT_GLOBAL_NVS_AREA), 
                              &gSaGlobalNvsArea.Area);
  ASSERT_EFI_ERROR (Status);
  pBS->SetMem (gSaGlobalNvsArea.Area, sizeof (SYSTEM_AGENT_GLOBAL_NVS_AREA), 0);
#endif
  //
  // mGlobalNvsArea.Area has the address of GNVS in ACPI NVS area
  // update this as GNVS opRegion field of GNVS area in DSDT.
  //
  Status = pBS->LocateProtocol(&gAcpiSupportGuid, NULL, &gEfiAcpiSupport);
  ASSERT_EFI_ERROR (Status);
  
  // Read MC device ID
  McDeviceId = READ_PCI16_NB(R_SA_MC_DEVICE_ID);

  DsdtTable = GetDSDTTable();
  if (DsdtTable) {
      Length = DsdtTable->Length - sizeof(ACPI_HDR);
      ptr = (UINT8*)DsdtTable + sizeof(ACPI_HDR);
      Status = GetAslObj(ptr, Length, "GNVS", otOpReg, &ObjInfo);
      ASSERT_EFI_ERROR (Status);

      ptr = (UINT8*)ObjInfo.DataStart;
      *(UINT32*)(ptr + 2) = (UINT32)(UINTN)mGlobalNvsArea.Area;      
      *(UINT16*)(ptr + 2 + 5) = sizeof (EFI_GLOBAL_NVS_AREA); 
      TRACE((TRACE_ALWAYS, "ACPI Global NVS Ptr=0x%X, Length=0x%X\n", (UINT32)(UINTN) mGlobalNvsArea.Area, sizeof (EFI_GLOBAL_NVS_AREA)));

#if defined   Remove_SaSsdt_Data_To_Dsdt && Remove_SaSsdt_Data_To_Dsdt
      Length = DsdtTable->Length - sizeof(ACPI_HDR);
      ptr = (UINT8*)DsdtTable + sizeof(ACPI_HDR);
      Status = GetAslObj(ptr, Length, "SANV", otOpReg, &ObjInfo);
      ASSERT_EFI_ERROR (Status);

      ptr = (UINT8*)ObjInfo.DataStart;
      *(UINT32*)(ptr + 2) = (UINT32)(UINTN)gSaGlobalNvsArea.Area;      
      *(UINT16*)(ptr + 2 + 5) = sizeof (SYSTEM_AGENT_GLOBAL_NVS_AREA); 
      TRACE((TRACE_ALWAYS, "ACPI Global SA NVS Ptr=0x%X, Length=0x%X\n", (UINT32)(UINTN) gSaGlobalNvsArea.Area, sizeof (SYSTEM_AGENT_GLOBAL_NVS_AREA)));
#endif

      if(!IS_SA_DEVICE_ID_MOBILE(McDeviceId)) {   
        DsdtTableUpdate (DsdtTable);  // This DsdtTable update is for non-Mobile platform.
      }
  }

   LoadDbgpTable();

#if defined LPIT_SUPPORT && LPIT_SUPPORT
  if (PchSeries == PchLp) {
   LoadLpitTable();
  }
#endif

  Status = pBS->LocateProtocol(&gPlatformInfoProtocolGuid, NULL, &gPlatformInfoProtocol);
  ASSERT_EFI_ERROR (Status);

  // Update the PlatformFlavor
  mGlobalNvsArea.Area->PlatformFlavor = gPlatformInfoProtocol->PlatformFlavor;

  // Update the Platform Board ID
  mGlobalNvsArea.Area->BoardId = gPlatformInfoProtocol->BoardId;
  
  // Update the Board Revision
  mGlobalNvsArea.Area->BoardRev = gPlatformInfoProtocol->BoardRev;

  // Initialize AMI Setup Data 
  Status = GetEfiVariable(
      L"Setup",
      &gSetupGuid,
      &SetupAttributes,
      &VariableSize,
      &gSetupData
  );

  // Initilize ACPI DXE Platform Policy
  Status = InstallAcpiDxePlatformPolicy (SetupAttributes);
  ASSERT_EFI_ERROR(Status);

#if LOW_POWER_S0_IDLE_CAPABLE == 1
  mGlobalNvsArea.Area->LowPowerS0Idle = 0;
  if (LOW_POWER_S0_IDLE_CAPABLE) {
    if (gSetupData->AcpiLowPowerS0Idle == 1) {
      mGlobalNvsArea.Area->LowPowerS0Idle = 1;
      mGlobalNvsArea.Area->PB1E = gSetupData->PowerButton10SecOVR | BIT3; //Bit3: Slate/Laptop Mode Flag, 0: Slate, 1: Laptop
      mGlobalNvsArea.Area->PEPC = mGlobalNvsArea.Area->PEPC | gSetupData->LowPowerIdleSATA;
      mGlobalNvsArea.Area->ECNO = gSetupData->EcNotification;
      mGlobalNvsArea.Area->ECDB = gSetupData->EcCSDebugLight;
      mGlobalNvsArea.Area->SHSB = gSetupData->SensorStandby;
      mGlobalNvsArea.Area->PL1LimitCS = gSetupData->CSPL1Limit;
      mGlobalNvsArea.Area->PL1LimitCSValue = gSetupData->CSPL1Value;
    }
  }
#endif

  if (mGlobalNvsArea.Area->LowPowerS0Idle == 0) {
//      DsdtTableUpdate1 (DsdtTable);  
  } // mGlobalNvsArea.Area->LowPowerS0Idle = 0


  if (EFI_ERROR (Status)) {
    mGlobalNvsArea.Area->NativePCIESupport = 0;
  } else {
    mGlobalNvsArea.Area->NativePCIESupport = gSetupData->PciExpNative;
  }

#if Dptf_SUPPORT
  mGlobalNvsArea.Area->EnableDptfDevice                     = gSetupData->EnableDptf;
  if (gSetupData->EnableDptf) {
    mGlobalNvsArea.Area->EnableSaDevice                     = gSetupData->EnableSaDevice;
    mGlobalNvsArea.Area->ActiveThermalTripPointSA           = gSetupData->ActiveThermalTripPointSa;
    mGlobalNvsArea.Area->PassiveThermalTripPointSA          = gSetupData->PassiveThermalTripPointSa;
    mGlobalNvsArea.Area->CriticalThermalTripPointSA         = gSetupData->CriticalThermalTripPointSa;
    mGlobalNvsArea.Area->HotThermalTripPointSA              = gSetupData->HotThermalTripPointSa;

    mGlobalNvsArea.Area->EnablePchDevice                    = gSetupData->EnablePchDevice;
    mGlobalNvsArea.Area->ActiveThermalTripPointPCH          = gSetupData->ActiveThermalTripPointPch;
    mGlobalNvsArea.Area->PassiveThermalTripPointPCH         = gSetupData->PassiveThermalTripPointPch;
    mGlobalNvsArea.Area->CriticalThermalTripPointPCH        = gSetupData->CriticalThermalTripPointPch;
    mGlobalNvsArea.Area->HotThermalTripPointPCH             = gSetupData->HotThermalTripPointPch;

    mGlobalNvsArea.Area->EnableMemoryDevice                 = gSetupData->EnableMemDevice;
    mGlobalNvsArea.Area->ActiveThermalTripPointTMEM         = gSetupData->ActiveThermalTripPointMem;
    mGlobalNvsArea.Area->PassiveThermalTripPointTMEM        = gSetupData->PassiveThermalTripPointMem;
    mGlobalNvsArea.Area->CriticalThermalTripPointTMEM       = gSetupData->CriticalThermalTripPointMem;
    mGlobalNvsArea.Area->HotThermalTripPointTMEM            = gSetupData->HotThermalTripPointMem;

    mGlobalNvsArea.Area->EnableAmbientDevice                = gSetupData->EnableAmbientDevice;
    mGlobalNvsArea.Area->ActiveThermalTripPointAmbient      = gSetupData->ActiveThermalTripPointAmbient;
    mGlobalNvsArea.Area->PassiveThermalTripPointAmbient     = gSetupData->PassiveThermalTripPointAmbient;
    mGlobalNvsArea.Area->CriticalThermalTripPointAmbient    = gSetupData->CriticalThermalTripPointAmbient;
    mGlobalNvsArea.Area->HotThermalTripPointAmbient         = gSetupData->HotThermalTripPointAmbient;

    mGlobalNvsArea.Area->EnableSkinDevice                   = gSetupData->EnableSkinDevice;
    mGlobalNvsArea.Area->ActiveThermalTripPointSkin         = gSetupData->ActiveThermalTripPointSkin;
    mGlobalNvsArea.Area->PassiveThermalTripPointSkin        = gSetupData->PassiveThermalTripPointSkin;
    mGlobalNvsArea.Area->CriticalThermalTripPointSkin       = gSetupData->CriticalThermalTripPointSkin;
    mGlobalNvsArea.Area->HotThermalTripPointSkin            = gSetupData->HotThermalTripPointSkin;

    mGlobalNvsArea.Area->EnableExhaustFanDevice             = gSetupData->EnableExhaustDevice;
    mGlobalNvsArea.Area->ActiveThermalTripPointExhaustFan   = gSetupData->ActiveThermalTripPointExhaust;
    mGlobalNvsArea.Area->PassiveThermalTripPointExhaustFan  = gSetupData->PassiveThermalTripPointExhaust;
    mGlobalNvsArea.Area->CriticalThermalTripPointExhaustFan = gSetupData->CriticalThermalTripPointExhaust;
    mGlobalNvsArea.Area->HotThermalTripPointExhaustFan      = gSetupData->HotThermalTripPointExhaust;

    mGlobalNvsArea.Area->EnableVRDevice                     = gSetupData->EnableVRDevice;
    mGlobalNvsArea.Area->ActiveThermalTripPointVR           = gSetupData->ActiveThermalTripPointVR;
    mGlobalNvsArea.Area->PassiveThermalTripPointVR          = gSetupData->PassiveThermalTripPointVR;
    mGlobalNvsArea.Area->CriticalThermalTripPointVR         = gSetupData->CriticalThermalTripPointVR;
    mGlobalNvsArea.Area->HotThermalTripPointVR              = gSetupData->HotThermalTripPointVR;

    mGlobalNvsArea.Area->PpccStepSize               = gSetupData->PpccStepSize;
    mGlobalNvsArea.Area->LPOEnable                  = gSetupData->LPOEnable;
    mGlobalNvsArea.Area->LPOStartPState             = gSetupData->LPOStartPState;
    mGlobalNvsArea.Area->LPOStepSize                = gSetupData->LPOStepSize;
    mGlobalNvsArea.Area->LPOPowerControlSetting     = gSetupData->LPOPowerControl;
    mGlobalNvsArea.Area->LPOPerformanceControlSetting   = gSetupData->LPOPerformanceControl;
    mGlobalNvsArea.Area->EnableCtdpPolicy           = gSetupData->EnableCTDP;
    mGlobalNvsArea.Area->EnableLpmPolicy            = gSetupData->EnableLPM;
    mGlobalNvsArea.Area->CurrentLowPowerMode        = gSetupData->LPMSetting;
    mGlobalNvsArea.Area->EnableFan1Device           = gSetupData->Fan1Device;
    mGlobalNvsArea.Area->EnableFan2Device           = gSetupData->Fan2Device;
    mGlobalNvsArea.Area->EnableDisplayParticipant   = gSetupData->DisplayParticipant;
    mGlobalNvsArea.Area->EnablePowerDevice          = gSetupData->PowerParticipant;
    mGlobalNvsArea.Area->EnablePowerPolicy          = gSetupData->PowerPolicy;
    mGlobalNvsArea.Area->EnableActivePolicy         = gSetupData->ActivePolicy;
    mGlobalNvsArea.Area->EnablePassivePolicy        = gSetupData->PassivePolicy;
    mGlobalNvsArea.Area->EnableCriticalPolicy       = gSetupData->CriticalPolicy;
    mGlobalNvsArea.Area->EnableCoolingModePolicy    = gSetupData->CoolingModePolicy;
    mGlobalNvsArea.Area->EnableCurrentExecutionUnit = 1;
    mGlobalNvsArea.Area->TargetGfxFreq              = 400;
    mGlobalNvsArea.Area->TrtRevision                = gSetupData->TrtRevision;
  }
#endif

  Status = pBS->AllocatePool (EfiBootServicesData, sizeof(NB_SETUP_DATA), (VOID **)&NbSetupData);
  GetNbSetupData( pRS, NbSetupData, FALSE );
  Status = pBS->AllocatePool (EfiBootServicesData, sizeof(SB_SETUP_DATA), (VOID **)&SbSetupData);
  GetSbSetupData( pRS, SbSetupData, FALSE );

  mGlobalNvsArea.Area->NFCEnable           	        = SbSetupData->NFCE;

  mGlobalNvsArea.Area->Ac0TripPoint                 = SbSetupData->Ac0TripPoint;
  mGlobalNvsArea.Area->Ac0FanSpeed                  = SbSetupData->Ac0FanSpeed;
  mGlobalNvsArea.Area->Ac1TripPoint                 = SbSetupData->Ac1TripPoint;
  mGlobalNvsArea.Area->Ac1FanSpeed                  = SbSetupData->Ac1FanSpeed;

  mGlobalNvsArea.Area->PassiveThermalTripPoint      = SbSetupData->PassiveThermalTripPoint;
  mGlobalNvsArea.Area->PassiveTc1Value              = SbSetupData->PassiveTc1Value;
  mGlobalNvsArea.Area->PassiveTc2Value              = SbSetupData->PassiveTc2Value;
  mGlobalNvsArea.Area->PassiveTspValue              = SbSetupData->PassiveTspValue;
  mGlobalNvsArea.Area->CriticalThermalTripPoint     = SbSetupData->CriticalThermalTripPoint;     

#if CRB_EC_SUPPORT == 1
  if(IS_SA_DEVICE_ID_MOBILE(McDeviceId)) {
    mGlobalNvsArea.Area->EcAvailable = 1;
    mGlobalNvsArea.Area->IUBE = 1;
    mGlobalNvsArea.Area->IUCE = 1;
    mGlobalNvsArea.Area->IUDE = 1;
  }
#endif

#if defined   ACPIDEBUG_SUPPORT && ACPIDEBUG_SUPPORT
  if (gSetupData->AcpiDebugSupport){
    LoadSsdtAcpiDebugTable();
  }
#endif

#if defined   PTID_SUPPORT && PTID_SUPPORT
  mGlobalNvsArea.Area->PeciAccessMethod             = gSetupData->PeciAccessMethod;
  if (gSetupData->PtidSupport){
    LoadSsdtPtidTable();
  }
#endif

#if defined   IntelRMT_SUPPORT && IntelRMT_SUPPORT
  if (gSetupData->IRMTSupport){
    LoadSsdtIRMTTable();
    mGlobalNvsArea.Area->INSC         = (gSetupData->IRMTHWNotification << 1) | (gSetupData->IRMTState);
  }
#endif

#if defined   INTELSENSORHUB_SUPPORT && INTELSENSORHUB_SUPPORT
    LoadSsdtIntelSensorHubTable();
#endif

#if defined   ZPODD_SUPPORT && ZPODD_SUPPORT
    LoadSsdtZpOddTable();
#endif

#if defined   RTD3_SUPPORT && RTD3_SUPPORT
    mGlobalNvsArea.Area->Rtd3Support                  = gSetupData->Rtd3Support;
    mGlobalNvsArea.Area->VRSD                         = gSetupData->VRStaggeringDelay;
    mGlobalNvsArea.Area->VRRD                         = gSetupData->VRRampUpDelay;
    mGlobalNvsArea.Area->Rtd3P0dl                     = gSetupData->Rtd3P0dl;
    mGlobalNvsArea.Area->Rtd3P3dl                     = gSetupData->Rtd3P3dl;
    mGlobalNvsArea.Area->AUDD                         = gSetupData->Rtd3Audio;
    mGlobalNvsArea.Area->DSPD                         = gSetupData->Rtd3ADSP;
    mGlobalNvsArea.Area->I20D                         = gSetupData->Rtd3I2C0;
    mGlobalNvsArea.Area->IC0D                         = gSetupData->Rtd3SensorHub;
    mGlobalNvsArea.Area->I21D                         = gSetupData->Rtd3I2C1;
    mGlobalNvsArea.Area->IC1S                         = gSetupData->Rtd3I2C1PS0;
    mGlobalNvsArea.Area->IC1D                         = gSetupData->Rtd3TouchPanel;

    mGlobalNvsArea.Area->PepDevice                    = (gSetupData->PepSata << 1) | (gSetupData->PepGfx);
    mGlobalNvsArea.Area->PSCP                         = gSetupData->PCapping;
  
    if (gSetupData->XhciP0 == 1){
    	USBRTD3 = 1;
    }else if (gSetupData->XhciP0 == 2){
      	USBRTD3 = 2;
    }
    if (gSetupData->XhciP1 == 1){
      	USBRTD3 += 0x10;
    }else if (gSetupData->XhciP1 == 2){
      	USBRTD3 += 0x20;
    }
    mGlobalNvsArea.Area->UsbPowerResourceTest         = USBRTD3;
    mGlobalNvsArea.Area->RIC0                     	  = gSetupData->RIC0;
    mGlobalNvsArea.Area->RCG0                         = 0;
    if (gSetupData->RTD3ZPODD){
    mGlobalNvsArea.Area->RCG0                         = mGlobalNvsArea.Area->RCG0 | BIT0;
    }
    if (gSetupData->RTD3USBCamera){
    mGlobalNvsArea.Area->RCG0                         = mGlobalNvsArea.Area->RCG0 | BIT1;
    }
    if (gSetupData->RTD3MiniSataPort3 == 1){
    mGlobalNvsArea.Area->RCG0                         = mGlobalNvsArea.Area->RCG0 | BIT2;
    }else if (gSetupData->RTD3MiniSataPort3 == 2){
    mGlobalNvsArea.Area->RCG0                         = mGlobalNvsArea.Area->RCG0 | BIT3;
    }

    mGlobalNvsArea.Area->RWAG                         = gSetupData->RTD3WaGpio;

  if (gSetupData->Rtd3Support){
    LoadSsdtRtd3Table();
  } // (gSetupData->Rtd3Support)
#endif

#if defined   iME_SUPPORT && iME_SUPPORT
  ECSmbusThermalReportingEnabled                = SbSetupData->TrEnabled;  
  ECSMBusMsgLenth                               = SbSetupData->SMBusECMsgLen;
  ECSMBusPECEnabled                             = SbSetupData->SMBusECMsgPEC;
#else
#if CRB_EC_SUPPORT == 1
  ECSmbusThermalReportingEnabled                = 0x0;  
  ECSMBusMsgLenth                               = 0x0;
  ECSMBusPECEnabled                             = 0x0;
#endif
#endif


  // Enable TS-on-DIMM if present and enabled in SETUP, update NVS for use by DPPM code.
#if defined   (iME_SUPPORT) && (iME_SUPPORT==1)
#if (DIMM_SLOT_NUM == 2)
    if (SbSetupData->TrSmbusConfig > 0) {
#endif

#if (DIMM_SLOT_NUM == 4)
    if((SbSetupData->TsOnDimm1) || (SbSetupData->TsOnDimm2) || \
       (SbSetupData->TsOnDimm3) || (SbSetupData->TsOnDimm4)) {
#endif
      mGlobalNvsArea.Area->TsOnDimmEnabled = PCH_DEVICE_ENABLE;
    } else {
      mGlobalNvsArea.Area->TsOnDimmEnabled = PCH_DEVICE_DISABLE;
    }
    
#else
    mGlobalNvsArea.Area->TsOnDimmEnabled = PCH_DEVICE_DISABLE;
#endif

#if CRB_EC_SUPPORT == 1
 if (mGlobalNvsArea.Area->EcAvailable) {
  // Locate KSC protocol.
  Status = InitializeKscLib ();

  if (Status == EFI_SUCCESS) {

    if(ECSmbusThermalReportingEnabled) {

      // SMBus Message length 
      Status = SendKscCommand (KSC_C_PCH_SMBUS_MSG_LENGTH);
      if(Status == EFI_SUCCESS) {
        SendKscData(ECSMBusMsgLenth);
      }
      // EC SMBus Packet Error Checking Enable (PEC) cmd 
      if(ECSMBusPECEnabled) {
        SendKscCommand (KSC_C_PCH_SMBUS_PEC_EN);
      }else {
        SendKscCommand (KSC_C_PCH_SMBUS_PEC_DIS);
      }

      if (mGlobalNvsArea.Area->TsOnDimmEnabled) {
        SendKscCommand (KSC_TS_ON_DIMM_EN); // TS-on-DIMM thermal monitoring enable command
      } else {
        SendKscCommand (KSC_TS_ON_DIMM_DIS); // TS-on-DIMM thermal monitoring Disable command
      }

      SendKscCommand (KSC_EC_PCH_SMBUS_EN); // EC PCH SMBus thermal monitoring Enable cmd
    }else {
    
      SendKscCommand (KSC_EC_PCH_SMBUS_DIS); // EC PCH SMBus thermal monitoring Disable cmd
    }

  }
 }
#endif
  // Platform Thermal code end

  //Get platform cpuid
  CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
  mGlobalNvsArea.Area->PlatformCpuId  = (RegEax & 0x0FFFFF);
  
  //
  // Nehalem MSR 0x35 CORE_THREAD_COUNT
  // [31:16] - total number of enabled cores in the package
  // [15:0]  - total number of enabled threads in the package
  //
  MsrCoreThreadCount.Qword = ReadMsr (EFI_MSR_CORE_THREAD_COUNT);
  
  //
  // ThreadCount : Number of Enabled Threads
  //
  mGlobalNvsArea.Area->ThreadCount = MsrCoreThreadCount.Bytes.FirstByte;

  // HPLL VCO = MCHBAR + C0Fh [2:0]
  //SNB_TODO  mGlobalNvsArea.Area->IgdHpllVco
  //-jeff mGlobalNvsArea.Area->IgdHpllVco  = READ_MEM8_MCH(0xC0F) & 0x07;       // 189  HPLL VCO

  mGlobalNvsArea.Area->ApicEnable                 = 1;
  mGlobalNvsArea.Area->EmaEnable                  = 0;
//For mobile platform, the number of batteries is updated by EC.asl
  mGlobalNvsArea.Area->NumberOfBatteries          = 0;
  mGlobalNvsArea.Area->BatteryCapacity0           = 100;
  mGlobalNvsArea.Area->BatteryStatus0             = 84;
  mGlobalNvsArea.Area->SmscComPort                = 1;
  mGlobalNvsArea.Area->IdeMode                    = 0;

  // Set default power state to AC. 
  // For mobile, EC.ASL, will update with current power state. 
  mGlobalNvsArea.Area->PowerState                 = 1;    
  mGlobalNvsArea.Area->PcieDockStatus             = 0;

#if CRB_EC_SUPPORT == 1
  if (mGlobalNvsArea.Area->EcAvailable) {
    // Initialize KSC library for later KSC Access
    Status = InitializeKscLib ();
    if (Status == EFI_SUCCESS) {

      // Call KSC lib to get PCIe dock status
      PortDataOut = 0;
      Status = SendKscCommand (KSC_C_DOCK_STATUS);
      if (Status == EFI_SUCCESS) {
        Status = ReceiveKscData (&PortDataOut);
      }

      //
      // the bit0 is PCIe Dock Status, 1 = docked
      //
      mGlobalNvsArea.Area->PcieDockStatus = (PortDataOut & 1);
    }
  }
#endif

  // Configure USB Sideband Deferring feature for ACPI
  if (mGlobalNvsArea.Area->BoardId == BoardIdGraysReef){
    mGlobalNvsArea.Area->HostAlertVector1 = 0x1F; // GPIO 15 for GPE _L1F
    mGlobalNvsArea.Area->HostAlertVector2 = 0x1B; // GPIO 11 for GPE _L1B
  }
  else{
    mGlobalNvsArea.Area->HostAlertVector1 = 0xFF; // dummy value to signal no USB SBD support
    mGlobalNvsArea.Area->HostAlertVector2 = 0xFF; // dummy value to signal no USB SBD support
  }

  mGlobalNvsArea.Area->Revision         = GLOBAL_NVS_AREA_REVISION_1; 

{
  mGlobalNvsArea.Area->ComIrqShareMode = gSetupData->F81216ComIrqShareMode ;
} 

  Status = pBS->InstallMultipleProtocolInterfaces (&ImageHandle,
                                                   &gEfiGlobalNvsAreaProtocolGuid,
                                                   &mGlobalNvsArea,
                                                   NULL);

#if defined   Remove_SaSsdt_Data_To_Dsdt && Remove_SaSsdt_Data_To_Dsdt
  Status = pBS->InstallMultipleProtocolInterfaces (&ImageHandle,
                                                   &gEfiGlobalSaNvsAreaProtocolGuid,
                                                   &gSaGlobalNvsArea,
                                                   NULL);
#endif

  Status = CreateReadyToBootEvent(
              TPL_CALLBACK,
              CallbackBootScript,
              NULL,
              &gEvtBootScript
              );


  pBS->FreePool(NbSetupData);
  pBS->FreePool(SbSetupData);

  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CallbackBootScript
//
//  This function will be called when ReadyToBoot event will be signaled and
//  will update related Platform information to global NVS area. 
//  
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//**********************************************************************
VOID CallbackBootScript (
    IN EFI_EVENT        Event,
    IN VOID             *Context )
{
  UINT32                  ThermalBaseB = 0;
  UINT32                  PchFdRegSave = 0;
  UINT16                  OLD_IAPC_BOOT_ARCH;
  PFACP_20                FadtPointer;
  INTN                    Index;
  PACPI_HDR               Table;
  EFI_ACPI_TABLE_VERSION  Version;
  UINTN                   TableHandle;
  EFI_STATUS              Status;
  UINTN                   VariableSize = NULL;
  SETUP_DATA              *SetupData = NULL;
  UINT8                  Buffer8;

  //
  // Update TBARB and TBARBH if configured by DPPM
  //
  PchFdRegSave = READ_MEM32_RCRB(R_PCH_RCRB_FUNC_DIS);
  RESET_MEM32_RCRB(R_PCH_RCRB_FUNC_DIS, B_PCH_RCRB_FUNC_DIS_THERMAL);
  ThermalBaseB = READ_PCI32(THERMAL_BUS, THERMAL_DEV, THERMAL_FUN, R_PCH_THERMAL_TBARB) & B_PCH_THERMAL_TBARB_MASK;
  WRITE_MEM32_RCRB(R_PCH_RCRB_FUNC_DIS, PchFdRegSave);

  if ((ThermalBaseB != 0) && (ThermalBaseB != B_PCH_THERMAL_TBARB_MASK)) {
    mGlobalNvsArea.Area->TBARB = (UINT32) ThermalBaseB;
    mGlobalNvsArea.Area->TBARBH = (UINT32) 0;
  } else {
    mGlobalNvsArea.Area->TBARB = (UINT32) 0;
    mGlobalNvsArea.Area->TBARBH = (UINT32) 0;
  }

  // Initialize AMI Setup Data 
  Status = GetEfiVariable(
      L"Setup",
      &gSetupGuid,
      NULL,
      &VariableSize,
      &SetupData
  );

  Index = 0;
  do {
    Status = gEfiAcpiSupport->GetAcpiTable(gEfiAcpiSupport,
                                         Index,
                                         &Table,
                                         &Version,
                                         &TableHandle);

    if (Status == EFI_NOT_FOUND) {
      break;
    }
    if (Table->Signature == FACP_SIG) {
      FadtPointer = (PFACP_20) Table;
      if (mGlobalNvsArea.Area->PpmFlags & PPM_C3) {
        FadtPointer->P_LVL3_LAT = FADT_C3_LATENCY;
      }
      OLD_IAPC_BOOT_ARCH = FadtPointer->IAPC_BOOT_ARCH;
      //
      // if Native ASPM is disabled, set FACP table to skip Native ASPM
      //
      if ((SetupData->PciExpNative == 0)|| (SetupData->NativeAspmEnable == 0x0)) {
        FadtPointer->IAPC_BOOT_ARCH |= 0x10;
      }
  
      //if (FadtPointer->IAPC_BOOT_ARCH != OLD_IAPC_BOOT_ARCH) {
      if ((FadtPointer->IAPC_BOOT_ARCH != OLD_IAPC_BOOT_ARCH) || (mGlobalNvsArea.Area->PpmFlags & PPM_C3)) {
        Status = gEfiAcpiSupport->SetAcpiTable (gEfiAcpiSupport, Table, TRUE, Version, &TableHandle);
        ASSERT_EFI_ERROR (Status);
      }
      pBS->FreePool (Table);
    }
    Index++;
  } while (1);


    if (READ_PCI32(SATA_BUS, SATA_DEV, SATA_FUN, PCI_VID) != 0xffffffff) {
            Buffer8 = READ_PCI8(SATA_BUS, SATA_DEV, SATA_FUN, SATA_REG_PCS + 1 );
            mGlobalNvsArea.Area->SPST             = (Buffer8 & BIT0 );
            mGlobalNvsArea.Area->SPST             = mGlobalNvsArea.Area->SPST | (Buffer8  & BIT1);
            mGlobalNvsArea.Area->SPST             = mGlobalNvsArea.Area->SPST | (Buffer8  & BIT2);
            mGlobalNvsArea.Area->SPST             = mGlobalNvsArea.Area->SPST | (Buffer8  & BIT3);

    }

  // Kill the Event
  pBS->CloseEvent(Event);
}

VOID LoadDbgpTable()
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_ACPI_DEBUG_PORT_DESCRIPTION_TABLE   *DBGP;
    EFI_ACPI_SUPPORT_PROTOCOL       *As;
    UINT8                           OemId[6] = T_ACPI_OEM_ID ;//CONVERT_TO_STRING(T_ACPI_OEM_ID);
    UINT8                           OemTblId[8] = \
                                            T_ACPI_OEM_TBL_ID ;//CONVERT_TO_STRING(T_ACPI_OEM_TBL_ID);
    UINTN                           mDbgpTblHandle;


    Status = pBS->LocateProtocol(&gEfiAcpiSupportGuid, NULL, &As);
    DBGP = MallocZ(sizeof(EFI_ACPI_DEBUG_PORT_DESCRIPTION_TABLE));
    ASSERT(DBGP);
        if (DBGP) {
            // Fill Table header;
            DBGP->Header.Signature = EFI_ACPI_3_0_DEBUG_PORT_TABLE_SIGNATURE;
            DBGP->Header.Length    = sizeof(EFI_ACPI_DEBUG_PORT_DESCRIPTION_TABLE);
            DBGP->Header.Revision  = EFI_ACPI_DBGP_TABLE_REVISION;
            DBGP->Header.Checksum  = 0;
            MemCpy(&(DBGP->Header.OemId[0]), OemId, 6);
            MemCpy(&(DBGP->Header.OemTblId[0]), OemTblId, 8);
            DBGP->Header.OemRev  = EFI_ACPI_OEM_DBGP_REVISION;
            DBGP->Header.CreatorId  = EFI_ACPI_CREATOR_ID;
            DBGP->Header.CreatorRev = CORE_REVISION;
            // Fill DBGP Fields  
	    DBGP->BaseAddress.AddressSpaceId = 1;
	    DBGP->BaseAddress.RegisterBitWidth = 8;
	    DBGP->BaseAddress.RegisterBitOffset = 0;
	    DBGP->BaseAddress.Reserved = 0;
	    DBGP->BaseAddress.Address = 0x3F8;

            // Add table 
            mDbgpTblHandle = 0;
            Status = As->SetAcpiTable( As, \
                                       DBGP, \
                                       TRUE, \
                                       EFI_ACPI_TABLE_VERSION_ALL, \
                                       &mDbgpTblHandle );
            TRACE((-1,"ACPISupport.SetAcpiTable() = %r \n", Status));
            ASSERT_EFI_ERROR(Status);
    
            // Free memory used for table image
            pBS->FreePool(DBGP);
        }

}

#if defined LPIT_SUPPORT && LPIT_SUPPORT
VOID LoadLpitTable()
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *Table;
  UINTN                         Size;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        FvStatus;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_VERSION        Version;
  EFI_ACPI_DESCRIPTION_HEADER   *TableHeader;
  EFI_ACPI_TABLE_PROTOCOL       *AcpiTable;
  BOOLEAN                        LoadTable;
  

  FwVol = NULL;
  Table = NULL;
  //
  // Locate FV protocol.
  //

  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  
  //
  // Look for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiFirmwareVolumeProtocolGuid,
                  &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    &gAcpiLpitGuid,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );
    //
    // If we found it, then we are done
    //
    
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Find the Table protocol
  //
  Status = pBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **)&AcpiTable);
  ASSERT_EFI_ERROR (Status);



  //
  // Read tables from the storage file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                          FwVol,
                          &gAcpiLpitGuid,
                          EFI_SECTION_RAW,
                          Instance,
                          &Table,
                          &Size,
                          &FvStatus
                          );

    if (!EFI_ERROR (Status)) {
      
      LoadTable = FALSE;
      TableHeader = (EFI_ACPI_DESCRIPTION_HEADER *) Table;
      ///
      /// Check the Signature ID to modify the table
      ///
      if (!LoadTable) {
      switch (((EFI_ACPI_DESCRIPTION_HEADER *) TableHeader)->Signature) {

      case 0x5449504c: //EFI_ACPI_LOW_POWER_IDLE_TABLE_SIGNATURE
        LoadTable = TRUE;
        //LpitAcpiTable = (EFI_ACPI_DESCRIPTION_HEADER *) Table;
        //LpitTableUpdate (LpitAcpiTable, &Version);
        break;

      default:
        break;
      }
      }
  ///
  /// Update the LPIT table in the ACPI tables.
  ///
  if (LoadTable) {
  TableHandle = 0;
    Status = AcpiTable->InstallAcpiTable (
                          AcpiTable,
                          Table,
                          Table->Length,
                          &TableHandle
                          );
  ASSERT_EFI_ERROR (Status);
  } 

      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }
}
#endif

#if defined   PTID_SUPPORT && PTID_SUPPORT
VOID LoadSsdtPtidTable()
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  EFI_ACPI_SUPPORT_PROTOCOL     *AcpiSupport;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *Table;
  UINTN                         Size;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        FvStatus;
  ACPI_HDR                   *TableHeader;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_VERSION        Version;
  

  AcpiSupport   = NULL;
  FwVol = NULL;
  Table = NULL;

  //
  // Locate FV protocol.
  //

  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  
  //
  // Look for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiFirmwareVolumeProtocolGuid,
                  &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    &gAcpiPtidFfsTableStorageGuid,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );

    //
    // If we found it, then we are done
    //
    
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateSupportProtocol (
            &gEfiAcpiSupportGuid,
            &AcpiSupport,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the storage file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                          FwVol,
                          &gAcpiPtidFfsTableStorageGuid,
                          EFI_SECTION_RAW,
                          Instance,
                          &Table,
                          &Size,
                          &FvStatus
                          );

    if (!EFI_ERROR (Status)) {
      //
      // This should be a PTID SSDT table 
      //      
      TableHeader = (ACPI_HDR *) Table;
      if (MemCmp (&TableHeader->OemTblId, "PtidDevc", 8) == 0) {
        //
        // This is PTID  SSDT. We  load the table
        //
        TableHandle = 0;
        Status = AcpiSupport->SetAcpiTable (
                                AcpiSupport,
                                Table,
                                TRUE,
                                Version,
                                &TableHandle
                                );
        ASSERT_EFI_ERROR (Status);
      }

      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }
  Status = AcpiSupport->PublishTables (
                          AcpiSupport,
                          (EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0)
                          );
  ASSERT_EFI_ERROR (Status);
}

EFI_STATUS
LocateSupportProtocol (
  IN EFI_GUID                       *Protocol,
  OUT VOID                          **Instance,
  IN     BOOLEAN                    Type
  )
/*++

Routine Description:

  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

Arguments:

  Protocol      The protocol to find.
  Instance      Return pointer to the first instance of the protocol
  Type          TRUE if the desired protocol is a FV protocol

Returns:

  EFI_SUCCESS           The function completed successfully.
  EFI_NOT_FOUND         The protocol could not be located.
  EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.

--*/
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NumberOfHandles;
  EFI_FV_FILETYPE         FileType;
  UINT32                  FvStatus;
  EFI_FV_FILE_ATTRIBUTES  Attributes;
  UINTN                   Size;
  UINTN                   i;

  FvStatus = 0;
  //
  // Locate protocol.
  //
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  Protocol,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }
  //
  // Looking for FV with ACPI storage file
  //
  for (i = 0; i < NumberOfHandles; i++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                    HandleBuffer[i],
                    Protocol,
                    Instance
                    );
    ASSERT (!EFI_ERROR (Status));

    if (!Type) {
      //
      // Not looking for the FV protocol, so find the first instance of the
      // protocol.  There should not be any errors because our handle buffer
      // should always contain at least one or LocateHandleBuffer would have
      // returned not found.
      //
      break;
    }

    //
    // See if it has the ACPI storage file
    //
    Status = ((EFI_FIRMWARE_VOLUME_PROTOCOL *) (*Instance))->ReadFile (
                                                              *Instance,
                                                              &gAcpiPtidFfsTableStorageGuid,
                                                              NULL,
                                                              &Size,
                                                              &FileType,
                                                              &Attributes,
                                                              &FvStatus
                                                              );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  return Status;
}
#endif

#if defined   IntelRMT_SUPPORT && IntelRMT_SUPPORT
VOID LoadSsdtIRMTTable()
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  EFI_ACPI_SUPPORT_PROTOCOL     *AcpiSupport;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *Table;
  UINTN                         Size;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        FvStatus;
  ACPI_HDR                   *TableHeader;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_VERSION        Version;
  

  AcpiSupport   = NULL;
  FwVol = NULL;
  Table = NULL;

  //
  // Locate FV protocol.
  //

  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  
  //
  // Look for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiFirmwareVolumeProtocolGuid,
                  &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    &gAcpiIRMTFfsTableStorageGuid,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );

    //
    // If we found it, then we are done
    //
    
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateIRMTSupportProtocol (
            &gEfiAcpiSupportGuid,
            &AcpiSupport,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the storage file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                          FwVol,
                          &gAcpiIRMTFfsTableStorageGuid,
                          EFI_SECTION_RAW,
                          Instance,
                          &Table,
                          &Size,
                          &FvStatus
                          );

    if (!EFI_ERROR (Status)) {
      //
      // This should be a PTID SSDT table 
      //      
      TableHeader = (ACPI_HDR *) Table;
      if (MemCmp (&TableHeader->OemTblId, "IntelRMT", 8) == 0) {
        //
        // This is Intel RMT SSDT. We  load the table
        //
        TableHandle = 0;
        Status = AcpiSupport->SetAcpiTable (
                                AcpiSupport,
                                Table,
                                TRUE,
                                Version,
                                &TableHandle
                                );
        ASSERT_EFI_ERROR (Status);
      }

      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }
  Status = AcpiSupport->PublishTables (
                          AcpiSupport,
                          (EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0)
                          );
  ASSERT_EFI_ERROR (Status);
}

EFI_STATUS
LocateIRMTSupportProtocol (
  IN EFI_GUID                       *Protocol,
  OUT VOID                          **Instance,
  IN     BOOLEAN                    Type
  )
/*++

Routine Description:

  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

Arguments:

  Protocol      The protocol to find.
  Instance      Return pointer to the first instance of the protocol
  Type          TRUE if the desired protocol is a FV protocol

Returns:

  EFI_SUCCESS           The function completed successfully.
  EFI_NOT_FOUND         The protocol could not be located.
  EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.

--*/
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NumberOfHandles;
  EFI_FV_FILETYPE         FileType;
  UINT32                  FvStatus;
  EFI_FV_FILE_ATTRIBUTES  Attributes;
  UINTN                   Size;
  UINTN                   i;

  FvStatus = 0;
  //
  // Locate protocol.
  //
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  Protocol,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }
  //
  // Looking for FV with ACPI storage file
  //
  for (i = 0; i < NumberOfHandles; i++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                    HandleBuffer[i],
                    Protocol,
                    Instance
                    );
    ASSERT (!EFI_ERROR (Status));

    if (!Type) {
      //
      // Not looking for the FV protocol, so find the first instance of the
      // protocol.  There should not be any errors because our handle buffer
      // should always contain at least one or LocateHandleBuffer would have
      // returned not found.
      //
      break;
    }

    //
    // See if it has the ACPI storage file
    //
    Status = ((EFI_FIRMWARE_VOLUME_PROTOCOL *) (*Instance))->ReadFile (
                                                              *Instance,
                                                              &gAcpiPtidFfsTableStorageGuid,
                                                              NULL,
                                                              &Size,
                                                              &FileType,
                                                              &Attributes,
                                                              &FvStatus
                                                              );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  return Status;
}
#endif


#if defined   INTELSENSORHUB_SUPPORT && INTELSENSORHUB_SUPPORT
VOID LoadSsdtIntelSensorHubTable()
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  EFI_ACPI_SUPPORT_PROTOCOL     *AcpiSupport;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *Table;
  UINTN                         Size;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        FvStatus;
  ACPI_HDR                   *TableHeader;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_VERSION        Version;
  

  AcpiSupport   = NULL;
  FwVol = NULL;
  Table = NULL;

  //
  // Locate FV protocol.
  //

  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  
  //
  // Look for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiFirmwareVolumeProtocolGuid,
                  &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    &gAcpiIntelSensorHubFfsTableGuid,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );

    //
    // If we found it, then we are done
    //
    
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateIntelSensorHubSupportProtocol (
            &gEfiAcpiSupportGuid,
            &AcpiSupport,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the storage file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                          FwVol,
                          &gAcpiIntelSensorHubFfsTableGuid,
                          EFI_SECTION_RAW,
                          Instance,
                          &Table,
                          &Size,
                          &FvStatus
                          );

    if (!EFI_ERROR (Status)) {
      //
      // This should be a PTID SSDT table 
      //      
      TableHeader = (ACPI_HDR *) Table;
      if (MemCmp (&TableHeader->OemTblId, "sensrhub", 8) == 0) {
        //
        // This is PTID  SSDT. We  load the table
        //
        TableHandle = 0;
        Status = AcpiSupport->SetAcpiTable (
                                AcpiSupport,
                                Table,
                                TRUE,
                                Version,
                                &TableHandle
                                );
        ASSERT_EFI_ERROR (Status);
      }

      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }
  Status = AcpiSupport->PublishTables (
                          AcpiSupport,
                          (EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0)
                          );
  ASSERT_EFI_ERROR (Status);
}

EFI_STATUS
LocateIntelSensorHubSupportProtocol (
  IN EFI_GUID                       *Protocol,
  OUT VOID                          **Instance,
  IN     BOOLEAN                    Type
  )
/*++

Routine Description:

  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

Arguments:

  Protocol      The protocol to find.
  Instance      Return pointer to the first instance of the protocol
  Type          TRUE if the desired protocol is a FV protocol

Returns:

  EFI_SUCCESS           The function completed successfully.
  EFI_NOT_FOUND         The protocol could not be located.
  EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.

--*/
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NumberOfHandles;
  EFI_FV_FILETYPE         FileType;
  UINT32                  FvStatus;
  EFI_FV_FILE_ATTRIBUTES  Attributes;
  UINTN                   Size;
  UINTN                   i;

  FvStatus = 0;
  //
  // Locate protocol.
  //
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  Protocol,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }
  //
  // Looking for FV with ACPI storage file
  //
  for (i = 0; i < NumberOfHandles; i++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                    HandleBuffer[i],
                    Protocol,
                    Instance
                    );
    ASSERT (!EFI_ERROR (Status));

    if (!Type) {
      //
      // Not looking for the FV protocol, so find the first instance of the
      // protocol.  There should not be any errors because our handle buffer
      // should always contain at least one or LocateHandleBuffer would have
      // returned not found.
      //
      break;
    }

    //
    // See if it has the ACPI storage file
    //
    Status = ((EFI_FIRMWARE_VOLUME_PROTOCOL *) (*Instance))->ReadFile (
                                                              *Instance,
                                                              &gAcpiIntelSensorHubFfsTableGuid,
                                                              NULL,
                                                              &Size,
                                                              &FileType,
                                                              &Attributes,
                                                              &FvStatus
                                                              );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  return Status;
}

#endif

#if defined   ZPODD_SUPPORT && ZPODD_SUPPORT
VOID LoadSsdtZpOddTable()
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  EFI_ACPI_SUPPORT_PROTOCOL     *AcpiSupport;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *Table;
  UINTN                         Size;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        FvStatus;
  ACPI_HDR                   *TableHeader;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_VERSION        Version;
  BOOLEAN                       LoadTable;
  PCH_SERIES                    PchSeries = GetPchSeries();


  AcpiSupport   = NULL;
  FwVol = NULL;
  Table = NULL;

  //
  // Locate FV protocol.
  //

  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  
  //
  // Look for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiFirmwareVolumeProtocolGuid,
                  &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    &gAcpiZpOddFfsTableGuid,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );

    //
    // If we found it, then we are done
    //
    
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateZPODDSupportProtocol (
            &gEfiAcpiSupportGuid,
            &AcpiSupport,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the storage file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                          FwVol,
                          &gAcpiZpOddFfsTableGuid,
                          EFI_SECTION_RAW,
                          Instance,
                          &Table,
                          &Size,
                          &FvStatus
                          );

    if (!EFI_ERROR (Status)) {
      //
      // This should be a ZPODD SSDT table 
      //
      LoadTable   = FALSE;      
      TableHeader = (ACPI_HDR *) Table;
#if defined   STD_ZPODD_SUPPORT && STD_ZPODD_SUPPORT
      if ((MemCmp (&TableHeader->OemTblId, "zpodd", 8) == 0) && (PchSeries == PchH)){
         LoadTable   = TRUE;      
      }
#endif
#if defined   ULT_ZPODD_SUPPORT && ULT_ZPODD_SUPPORT
      if ((MemCmp (&TableHeader->OemTblId, "zpoddult", 8) == 0) && (PchSeries == PchLp)) {
         LoadTable   = TRUE;      
      }
#endif
        //
        // This is ZPODD  SSDT. We  load the table
        //
        if (LoadTable) {
          TableHandle = 0;
          Status = AcpiSupport->SetAcpiTable (
                                  AcpiSupport,
                                  Table,
                                  TRUE,
                                  Version,
                                  &TableHandle
                                  );
          ASSERT_EFI_ERROR (Status);
          Status = AcpiSupport->PublishTables (
                                  AcpiSupport,
                                  (EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0)
                                  );
          ASSERT_EFI_ERROR (Status);
        }

      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }
}

EFI_STATUS
LocateZPODDSupportProtocol (
  IN EFI_GUID                       *Protocol,
  OUT VOID                          **Instance,
  IN     BOOLEAN                    Type
  )
/*++

Routine Description:

  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

Arguments:

  Protocol      The protocol to find.
  Instance      Return pointer to the first instance of the protocol
  Type          TRUE if the desired protocol is a FV protocol

Returns:

  EFI_SUCCESS           The function completed successfully.
  EFI_NOT_FOUND         The protocol could not be located.
  EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.

--*/
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NumberOfHandles;
  EFI_FV_FILETYPE         FileType;
  UINT32                  FvStatus;
  EFI_FV_FILE_ATTRIBUTES  Attributes;
  UINTN                   Size;
  UINTN                   i;

  FvStatus = 0;
  //
  // Locate protocol.
  //
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  Protocol,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }
  //
  // Looking for FV with ACPI storage file
  //
  for (i = 0; i < NumberOfHandles; i++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                    HandleBuffer[i],
                    Protocol,
                    Instance
                    );
    ASSERT (!EFI_ERROR (Status));

    if (!Type) {
      //
      // Not looking for the FV protocol, so find the first instance of the
      // protocol.  There should not be any errors because our handle buffer
      // should always contain at least one or LocateHandleBuffer would have
      // returned not found.
      //
      break;
    }

    //
    // See if it has the ACPI storage file
    //
    Status = ((EFI_FIRMWARE_VOLUME_PROTOCOL *) (*Instance))->ReadFile (
                                                              *Instance,
                                                              &gAcpiZpOddFfsTableGuid,
                                                              NULL,
                                                              &Size,
                                                              &FileType,
                                                              &Attributes,
                                                              &FvStatus
                                                              );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  return Status;
}

#endif

#if defined   (RTD3_SUPPORT) && (RTD3_SUPPORT==1)
VOID LoadSsdtRtd3Table()
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  EFI_ACPI_SUPPORT_PROTOCOL     *AcpiSupport;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *Table;
  UINTN                         Size;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        FvStatus;
  ACPI_HDR                   *TableHeader;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_VERSION        Version;
  

  AcpiSupport   = NULL;
  FwVol = NULL;
  Table = NULL;

  //
  // Locate FV protocol.
  //

  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  
  //
  // Look for FV with ACPI RTD3 file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiFirmwareVolumeProtocolGuid,
                  &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI RTD3 file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    &gAcpiRtd3FfsTableGuid,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );

    //
    // If we found it, then we are done
    //
    
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateRTD3SupportProtocol (
            &gEfiAcpiSupportGuid,
            &AcpiSupport,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the RTD3 file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                          FwVol,
                          &gAcpiRtd3FfsTableGuid,
                          EFI_SECTION_RAW,
                          Instance,
                          &Table,
                          &Size,
                          &FvStatus
                          );

    if (!EFI_ERROR (Status)) {
      //
      // This should be a RTD3 SSDT table 
      //      
      TableHeader = (ACPI_HDR *) Table;
#if  ULT0RTD3_SUPPORT 
      if (MemCmp (&TableHeader->OemTblId, "Ult0Rtd3", 8) == 0) {
#endif
#if  BRRTD3_SUPPORT 
      if (MemCmp (&TableHeader->OemTblId, "BR0_Rtd3", 8) == 0) {
#endif
#if  RTD3FFRD_SUPPORT 
      if (MemCmp (&TableHeader->OemTblId, "HSW-FFRD", 8) == 0) {
#endif
        //
        // This is RTD3 SSDT. We load the table
        //
        TableHandle = 0;
        Status = AcpiSupport->SetAcpiTable (
                                AcpiSupport,
                                Table,
                                TRUE,
                                Version,
                                &TableHandle
                                );
        ASSERT_EFI_ERROR (Status);
      }

      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }
  Status = AcpiSupport->PublishTables (
                          AcpiSupport,
                          (EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0)
                          );
  ASSERT_EFI_ERROR (Status);
}

EFI_STATUS
LocateRTD3SupportProtocol (
  IN EFI_GUID                       *Protocol,
  OUT VOID                          **Instance,
  IN     BOOLEAN                    Type
  )
/*++

Routine Description:

  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

Arguments:

  Protocol      The protocol to find.
  Instance      Return pointer to the first instance of the protocol
  Type          TRUE if the desired protocol is a FV protocol

Returns:

  EFI_SUCCESS           The function completed successfully.
  EFI_NOT_FOUND         The protocol could not be located.
  EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.

--*/
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NumberOfHandles;
  EFI_FV_FILETYPE         FileType;
  UINT32                  FvStatus;
  EFI_FV_FILE_ATTRIBUTES  Attributes;
  UINTN                   Size;
  UINTN                   i;

  FvStatus = 0;
  //
  // Locate protocol.
  //
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  Protocol,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }
  //
  // Looking for FV with ACPI storage file
  //
  for (i = 0; i < NumberOfHandles; i++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                    HandleBuffer[i],
                    Protocol,
                    Instance
                    );
    ASSERT (!EFI_ERROR (Status));

    if (!Type) {
      //
      // Not looking for the FV protocol, so find the first instance of the
      // protocol.  There should not be any errors because our handle buffer
      // should always contain at least one or LocateHandleBuffer would have
      // returned not found.
      //
      break;
    }

    //
    // See if it has the ACPI RTD3 file
    //
    Status = ((EFI_FIRMWARE_VOLUME_PROTOCOL *) (*Instance))->ReadFile (
                                                              *Instance,
                                                              &gAcpiRtd3FfsTableGuid,
                                                              NULL,
                                                              &Size,
                                                              &FileType,
                                                              &Attributes,
                                                              &FvStatus
                                                              );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  return Status;
}
#endif

#if defined   ACPIDEBUG_SUPPORT && ACPIDEBUG_SUPPORT
VOID LoadSsdtAcpiDebugTable()
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *FwVol;
  EFI_ACPI_SUPPORT_PROTOCOL     *AcpiSupport;
  INTN                          Instance;
  EFI_ACPI_COMMON_HEADER        *Table;
  UINTN                         Size;
  EFI_FV_FILETYPE               FileType;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINT32                        FvStatus;
  ACPI_HDR                   *TableHeader;
  UINTN                         TableHandle;
  EFI_ACPI_TABLE_VERSION        Version;
  EFI_PHYSICAL_ADDRESS          BaseAddressMem = 0;
  UINT32                        BufferIndex;
  UINT32                        BufferEnd;
  UINT8                         *CurrPtr;
  UINT32                        *Signature;
  NAME_LAYOUT                   *NamePtr;
  UINT8                         UpdateCounter;


  AcpiSupport   = NULL;
  FwVol = NULL;
  Table = NULL;

  //
  // Reserve 64kb buffer of system memory to store Acpi Debug data.
  //
  BaseAddressMem = 0xFFFFFFFF;
  Status = pBS->AllocatePages (
                  AllocateMaxAddress,
                  EfiReservedMemoryType,
                  EFI_SIZE_TO_PAGES (AcpiDebugBufferSize),
                  &BaseAddressMem
                  );
  ASSERT_EFI_ERROR(Status);

  BufferIndex = (UINT32) BaseAddressMem;
  BufferEnd = BufferIndex + AcpiDebugBufferSize;
  //
  // Clear the 64kb buffer
  //
  pBS->SetMem ((VOID *)(UINTN)BaseAddressMem, AcpiDebugBufferSize, 0x78);
  //
  // Write a signature to the first line of the buffer, "INTEL ACPI DEBUG".
  //
  pBS->CopyMem ((VOID *)(UINTN)BufferIndex, ACPI_DEBUG_STR, sizeof(ACPI_DEBUG_STR) - 1);
  //
  // leave the Index after the signature
  //
  BufferIndex += sizeof(ACPI_DEBUG_STR) - 1;
  TRACE((TRACE_ALWAYS, "ACPI Debug address =0x%08X\n", BaseAddressMem));

  //
  // Locate FV protocol.
  //

  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiFirmwareVolumeProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  ASSERT_EFI_ERROR (Status);
  
  //
  // Look for FV with ACPIDebug file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {

    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiFirmwareVolumeProtocolGuid,
                  &FwVol
                  );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI Debug file
    //
    Size      = 0;
    FvStatus  = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    &gAcpiDebugFfsTableGuid,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );

    //
    // If we found it, then we are done
    //
    
    if (Status == EFI_SUCCESS) {
      break;
    }
  }
  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);

  //
  // By default, a table belongs in all ACPI table versions published.
  //
  Version = EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0;

  //
  // Find the AcpiSupport protocol
  //
  Status = LocateAcpiDebugSupportProtocol (
            &gEfiAcpiSupportGuid,
            &AcpiSupport,
            FALSE
            );
  ASSERT_EFI_ERROR (Status);

  //
  // Read tables from the AcpiDebug file.
  //
  Instance = 0;

  while (Status == EFI_SUCCESS) {
    //
    // Read the ACPI tables
    //
    Status = FwVol->ReadSection (
                          FwVol,
                          &gAcpiDebugFfsTableGuid,
                          EFI_SECTION_RAW,
                          Instance,
                          &Table,
                          &Size,
                          &FvStatus
                          );

    if (!EFI_ERROR (Status)) {
      //
      // This should be a AcpiDebug SSDT table 
      //      
      TableHeader = (ACPI_HDR *) Table;
      if (MemCmp (&TableHeader->OemTblId, "ADebTabl", 8) == 0) {
        //
        // Patch some pointers for the ASL code before loading the SSDT.
        //
        UpdateCounter = 1;
        for (CurrPtr = (UINT8 *) TableHeader; CurrPtr <= ((UINT8 *) TableHeader + TableHeader->Length), UpdateCounter < 4; CurrPtr++) {
           Signature = (UINT32 *) (CurrPtr + 1);
           //
           // patch DPTR (address of Acpi debug memory buffer)
           //
           if ((*CurrPtr == AML_NAME_OP) && *Signature == EFI_SIGNATURE_32 ('D', 'P', 'T', 'R')) {
             NamePtr = (NAME_LAYOUT *) CurrPtr;
             NamePtr->Value  = (UINT32) BaseAddressMem;
             UpdateCounter++;
           }
          //
          // patch EPTR (end of Acpi debug memory buffer)
          //
           if ((*CurrPtr == AML_NAME_OP) && *Signature == EFI_SIGNATURE_32 ('E', 'P', 'T', 'R')) {
             NamePtr = (NAME_LAYOUT *) CurrPtr;
             NamePtr->Value  = (UINT32) BufferEnd;
             UpdateCounter++;
           }
          //
          // patch CPTR (used as an index that starts after the buffer signature)
          //
           if ((*CurrPtr == AML_NAME_OP) && *Signature == EFI_SIGNATURE_32 ('C', 'P', 'T', 'R')) {
             NamePtr = (NAME_LAYOUT *) CurrPtr;
             NamePtr->Value  = (UINT32) BufferIndex;
             UpdateCounter++;
           }
        }
        //
        // This is AcpiDebug SSDT. We load the table
        //
        TableHandle = 0;
        Status = AcpiSupport->SetAcpiTable (
                                AcpiSupport,
                                Table,
                                TRUE,
                                Version,
                                &TableHandle
                                );
        ASSERT_EFI_ERROR (Status);
      }

      //
      // Increment the instance
      //
      Instance++;
      Table = NULL;
    }
  }
  Status = AcpiSupport->PublishTables (
                          AcpiSupport,
                          (EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0)
                          );
  ASSERT_EFI_ERROR (Status);
}

EFI_STATUS
LocateAcpiDebugSupportProtocol (
  IN EFI_GUID                       *Protocol,
  OUT VOID                          **Instance,
  IN     BOOLEAN                    Type
  )
/*++

Routine Description:

  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

Arguments:

  Protocol      The protocol to find.
  Instance      Return pointer to the first instance of the protocol
  Type          TRUE if the desired protocol is a FV protocol

Returns:

  EFI_SUCCESS           The function completed successfully.
  EFI_NOT_FOUND         The protocol could not be located.
  EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.

--*/
{
  EFI_STATUS              Status;
  EFI_HANDLE              *HandleBuffer;
  UINTN                   NumberOfHandles;
  EFI_FV_FILETYPE         FileType;
  UINT32                  FvStatus;
  EFI_FV_FILE_ATTRIBUTES  Attributes;
  UINTN                   Size;
  UINTN                   i;

  FvStatus = 0;
  //
  // Locate protocol.
  //
  Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  Protocol,
                  NULL,
                  &NumberOfHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }
  //
  // Looking for FV with ACPI storage file
  //
  for (i = 0; i < NumberOfHandles; i++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = pBS->HandleProtocol (
                    HandleBuffer[i],
                    Protocol,
                    Instance
                    );
    ASSERT (!EFI_ERROR (Status));

    if (!Type) {
      //
      // Not looking for the FV protocol, so find the first instance of the
      // protocol.  There should not be any errors because our handle buffer
      // should always contain at least one or LocateHandleBuffer would have
      // returned not found.
      //
      break;
    }

    //
    // See if it has the ACPI RTD3 file
    //
    Status = ((EFI_FIRMWARE_VOLUME_PROTOCOL *) (*Instance))->ReadFile (
                                                              *Instance,
                                                              &gAcpiDebugFfsTableGuid,
                                                              NULL,
                                                              &Size,
                                                              &FileType,
                                                              &Attributes,
                                                              &FvStatus
                                                              );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  pBS->FreePool (HandleBuffer);

  return Status;
}
#endif

VOID *GetDSDTTable ()
{
  INTN    Index;
  PACPI_HDR Table;
  EFI_ACPI_TABLE_VERSION  Version;
  UINTN   Handle;
  EFI_STATUS  Status;

  for (Index = 0;;++Index) {
    Status = gEfiAcpiSupport->GetAcpiTable(gEfiAcpiSupport,
                                           Index,
                                           &Table,
                                           &Version,
                                           &Handle);
    if (EFI_ERROR(Status)) return 0;
    if (((PACPI_HDR)Table)->Signature == FACP_SIG) return(VOID*)(UINTN)((PFACP32)Table)->DSDT;

  }
}

VOID
DsdtTableUpdate (
  PACPI_HDR   DsdtTable
  )
/*++

  Routine Description:

    Update the DSDT table

  Arguments:

    DsdtTable   - The table points to DSDT table.

  Returns:

    None

--*/
{
  UINT8                 *CurrPtr;
  UINT8                 *DsdtPointer;
  UINT32                *Signature;
  UINT8                 *Operation;
  //
  // Loop through the ASL looking for values that we must fix up.
  //
  CurrPtr = (UINT8 *) DsdtTable;
  for (DsdtPointer = CurrPtr;
       DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
       DsdtPointer++
      ) {
    Signature = (UINT32 *) DsdtPointer;
      //
      // SNB_TODO
      // SV Boards need it?
      //

      //
      // Desktop specific update can be put here.
      //
      switch (*Signature) {
        //
        // GPIO14 is not used on desktop, so related stuff should be removed in DSDT.
        //
        case (EFI_SIGNATURE_32 ('_', 'P', 'R', 'W')):
          //
          // Check if the next object to signature is the NAME of PWRB device.
          //
          Operation = DsdtPointer - 1;
          if ((*Operation == AML_NAME_OP) && (*(DsdtPointer + 8) == 0x1E)) {
            //
            // Rename _PRW (unrecognized name so OS will ignore)
            //
            *DsdtPointer = 'O';
          }
          break;
        case (EFI_SIGNATURE_32 ('_', 'L', '1', 'E')):
          //
          // Rename _L1E method (unrecognized method so OS will ignore)
          //
          *DsdtPointer = 'O';
          break;        
        default:
          break;
      }
  } 
  return; 
}

/*
VOID
DsdtTableUpdate1 (
  PACPI_HDR   DsdtTable
  )
{
  UINT8                 *CurrPtr;
  UINT8                 *DsdtPointer;
  UINT32                *Signature, *Signature1;

  CurrPtr = (UINT8 *) DsdtTable;

  for (DsdtPointer = CurrPtr;
       DsdtPointer <= (CurrPtr + ((EFI_ACPI_COMMON_HEADER *) CurrPtr)->Length);
       DsdtPointer++
      ) {
    Signature = (UINT32 *) (DsdtPointer + 3);
    Signature1 = (UINT32 *) (DsdtPointer + 14);
      //
    if ((*DsdtPointer == AML_EXT_OP) &&
        (*(DsdtPointer + 1)== AML_EXT_PROCESSOR_OP) &&
        (*(Signature1 ) == EFI_SIGNATURE_32 ('_', 'D', 'E', 'P'))
        ) {
         switch(*Signature){
            case (EFI_SIGNATURE_32 ('C', 'P', 'U', '0')):
            case (EFI_SIGNATURE_32 ('C', 'P', 'U', '1')):
            case (EFI_SIGNATURE_32 ('C', 'P', 'U', '2')):
            case (EFI_SIGNATURE_32 ('C', 'P', 'U', '3')):
            case (EFI_SIGNATURE_32 ('C', 'P', 'U', '4')):
            case (EFI_SIGNATURE_32 ('C', 'P', 'U', '5')):
            case (EFI_SIGNATURE_32 ('C', 'P', 'U', '6')):
            case (EFI_SIGNATURE_32 ('C', 'P', 'U', '7')):

            TRACE((-1, "Processor CPU0 Point at 0x%08X\n", DsdtPointer));
                 *(DsdtPointer + 14) = 'X';
                 break;
            default:
                 break;
         }// end switch      

    }

  } 
  return; 
}
*/

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
