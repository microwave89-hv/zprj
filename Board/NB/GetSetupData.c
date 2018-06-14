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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/GetSetupData.c 32    6/26/13 4:39a Ireneyang $
//
// $Revision: 32 $
//
// $Date: 6/26/13 4:39a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/GetSetupData.c $
// 
// 32    6/26/13 4:39a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add new related items into structure.
// [Files]       NBPEI.c; GetSetupData.c;
// 
// 30    6/21/13 5:21a Ireneyang
// Update to SBY SA RC 1.6.0.
// 
// 29    6/03/13 2:18a Ireneyang
// 
// 28    5/22/13 5:14a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add RCVENC1D into NB_SETUP_DATA for setting.
// [Files]       GetSetupData.c;
// 
// 27    5/13/13 6:28a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add PanelPowerEnable for enabling/disabling VDD force
//               bit. (Required only for early enabling of eDP panel)
// [Files]       NBSetup.c; GetSetupData.c; NbSetupData.h; NBPEI.c;
// 
// 26    4/09/13 4:03a Ireneyang
// [TAG]          None
// [Severity]     BugFix
// [Description]  Fix C7 function can't work with SA RC 1.4.0.0.
// [Files]        SgDgpu.asl; GetSetupData.c;
// 
// 25    3/15/13 6:28a Jeffch
// [TAG]          PCH_SKU
// [Severity]     BugFix
// [Description]  Fix Build error issue.
// [Files]        GetSetupData.c;
// 
// 24    3/15/13 1:58a Ireneyang
// [TAG]          EIP118133
// [Severity]     BugFix
// [Description]  Fix and restructure PlatformConfig setting of SA policy.
// [Files]        NBDxe.c; GetSetupData.c; NbSetupData.h;
// 
// 23    3/14/13 3:55a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Update to SBY SA RC PV 1.3.0. 
// [Files]        NBPEI.c; *.*;
// 
// 22    3/07/13 6:11a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Make some default SaPlatformPolicy items flexible. 
//                Define some SaPlatformPolicy items into NB_SETUP_DATA
//                structure.  
// [Files]        NbSetupData.h; GetSetupData.c; NBPEI.c; 
// 
// 21    3/07/13 3:44a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Add "Hot only" option for Memory Refresh 2x support to 
//                meet Intel Spec.
// [Files]        NBPEI.c; NB.uni; NB.sd; NbSetupData.h; GetSetupData.c; 
// 
// 20    2/23/13 6:14a Ireneyang
// Update to SBY SA RC PV 1.2.0.
// 
// 19    2/09/13 10:25a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.1.0
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; 
// 
// 18    1/28/13 3:47a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.0.
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; 
//                NB.sd; NB.uni; NBDxeBoard.c
// 
// 17    1/14/13 6:11a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Create setup item for  SA RC 0.90.
// [Files]        NBPei.c; GetNbSetupData.c NB.sd; NB.uni;
// 
// 16    1/10/13 6:00a Jeffch
// [TAG]          None
// [Severity]     Bug Fix
// [Description]  Fixed not program HDA codec for SaHDAVerbtable link bug.
// [Files]        NBDXE.c; GetSetupData.c; NbSetupData.h
// [TAG]          None
// [Severity]     Important
// [Description]  Create DDR PowerDown and idle counter for setup item.
// [Files]        NBPei.c; NB.sd; NB.uni; GetSetupData.c; NbSetupData.h
// 
// 15    1/07/13 1:41a Jeffch
// [TAG]          None
// [Severity]     Improvement
// [Description]  Change MRC DEBUG PRINT enable default value.
// [Files]        GetSetupData.c;
// 
// 14    1/03/13 7:31a Jeffch
// [TAG]          None
// [Severity]     Improvement
// [Description]  added SaHDAVerbtable link to OEM.
// [Files]        NBDxe.c; NbSetupData.h; GetSetupData.c;
// 
// 13    12/22/12 2:30a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Create setup item for  SA RC 0.81.
// [Files]        NBPei.c; GetNbSetupData.c NB.sd; NB.uni;
// 
// 12    12/18/12 5:17a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 0.81.
// [Files]        GetSetupData.c; NbSetupData.h;
// 
// 11    12/14/12 4:52a Jeffch
// [TAG]          EIP106709
// [Severity]     Important
// [Description]  Support PCIE Primary display.
// [Files]        NB.sd; NBDXEboard.c; NB.uni;
// GetSetupData.c;NbSetupData.h;
// 
// 10    11/14/12 5:33a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update XTU4.x function
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; NB.sd;
// NB.uni
// 
// 9     11/07/12 6:25a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Support ULT one BIOS
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h
// 
// 8     10/18/12 11:17p Jeffch
// [TAG]          EIP104234
// [Severity]     Important
// [Description]  Fixed cannot compile 4.6.5.3_Intel_SA-RC_071_019a with
// NB_ERROR_LOG_SUPPORT.
// [Files]        GetSetupData.c; NbSetupData.h
// 
// 7     10/14/12 5:18a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Follow SA RC 0.71.
// [Files]        NBPei.c, NBDxe.c; NBGeneric.c; NBCspLib.h; NBSetup.c;
// Nb.sd; GetSetupData.c
// 
// 6     10/14/12 12:41a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description] Update by XTU4.0.
// [Files]        NB.h, GetSetupData.c, NbSetupData.h
// [TAG]          None
// [Severity]     Important
// [Description]  Follow Update by Mahobay.
// [Files]        NB.sdl, NB.mak.c; NBDXEBoard.c
// 
// 5     9/12/12 6:37a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Add RxCEM Loop back setup item.
// [Files]         GetSetupData.c, NB.sd, NB.uni, NBPEI.c, NbSetupData.h,
// NBPEI.c 
// 
// 4     7/27/12 8:46a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] IGfx Fource Disable Support.
// [Files]       GetSetupData.c, NB.sdl, NB.sd, NB.uni, NbSetupData.h,
// NBDxe.c, NBPEI.c
// 
// 3     4/26/12 3:00a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Adjust Intel System Agent module the Setup item and
// Policy.
// [Description]   GetSetupData.c, NB.sdl, NB.sd, NB.uni, NBDxe.c,
// NBPEI.c,
//                 NBSetup.c, NBSetupReset.c, NbSetupData.h
// 
// 2     4/05/12 2:22a Yurenlai
// [TAG]  		EIP87103
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change for SystemAgent RefCode Revision: 0.5.5 .
// [Files]  		NBDxe.c, NBPEI.c, NBSMI.C, NBGeneric.cm NB.sd, NBSetup.c,
// GetSetupData.c, NbSetupData.h
// 
// 1     2/08/12 4:33a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        GetSetupData.c
//
// Description: Custom North Bridge setup data behavior implementation
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <AmiCspLib.h>
#include <Setup.h>
#include <Ppi\ReadOnlyVariable2.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef VOID (NB_OEM_SETUP_CALLBACK) (
    IN VOID                 *Services,
    IN OUT NB_SETUP_DATA    *NbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
);

// Function Prototype(s)

VOID NbSetupCallbacks (
    IN VOID              *Services,
    IN OUT NB_SETUP_DATA *NbSetupData,
    IN SETUP_DATA        *SetupData,
    IN BOOLEAN           Pei 
);
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// GUID Definition(s)

static EFI_GUID gSetupGuid = SETUP_GUID;
static EFI_GUID gPeiReadOnlyVar2PpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;

// Protocol/Ppi Definition(s)

// External Declaration(s)

extern NB_OEM_SETUP_CALLBACK NB_OEM_SETUP_CALLBACK_LIST EndOfList;

// Variable Declaration(s)

NB_OEM_SETUP_CALLBACK* NbOemSetupCallbackList[] = \
                                            {NB_OEM_SETUP_CALLBACK_LIST NULL};


// Function Definition(s)
UINT32            gNbSaHdaVerbTableData[] = {
  ///
  /// Audio Verb Table - 0x80862807
  ///
  /// Pin Widget 5 - PORT B
  ///
  0x00571C10,
  0x00571D00,
  0x00571E56,
  0x00571F18,
  ///
  /// Pin Widget 6 - PORT C
  ///
  0x00671C20,
  0x00671D00,
  0x00671E56,
  0x00671F18,
  ///
  /// Pin Widget 7 - PORT D
  ///
  0x00771C30,
  0x00771D00,
  0x00771E56,
  0x00771F18
};

NB_SA_HDA_VERB_TABLE gNbSaHdaVerbTable[] = {
  { 
      {
      0x80862807, ///< Vendor ID/Device ID
      0x0000,     ///< SubSystem ID
      0xFF,       ///< Revision ID
      0x02,       ///< Front panel support (1=yes, 2=no)
      0x0003,     ///< Number of Rear Jacks
      0x0000      ///< Number of Front Jacks
      },
    0             ///< Pointer to verb table data, need to be inited in the code.
  }
};
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbOemSetupCallbacks
//
// Description: This function calls registered callbacks for OEM/custom setup.
//
// Input:       *Services    - Pointer to PeiServices or RuntimeServices
//                             structure  
//              *NbSetupData - Pointer to custom setup data to return
//              *SetupData   - Pointer to system setup data.
//              Pei          - Pei flag. If TRUE we are in PEI phase
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbOemSetupCallbacks (
    IN VOID              *Services,
    IN OUT NB_SETUP_DATA *NbSetupData,
    IN SETUP_DATA        *SetupData,
    IN BOOLEAN           Pei )
{
    UINTN   i;

    for (i = 0; NbOemSetupCallbackList[i] != NULL; i++) 
        NbOemSetupCallbackList[i]( Services, NbSetupData, SetupData, Pei);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetNbSetupData
//
// Description: This function returns custom setup data from system SetupData
//              variable 
//
// Input:       *Services    - Pointer to PeiServices or RuntimeServices
//                             structure  
//              *NbSetupData - Pointer to custom setup data to return
//              Pei          - Pei flag. If TRUE we are in PEI phase
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetNbSetupData (
    IN VOID                 *Services,
    IN OUT NB_SETUP_DATA    *NbSetupData,
    IN BOOLEAN              Pei )
{
    EFI_STATUS                      Status;
    SETUP_DATA                      SetupData;
    EFI_PEI_SERVICES                **PeiServices;
    EFI_RUNTIME_SERVICES            *RunServices;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadOnlyVariable = NULL;
    UINTN                           VariableSize = sizeof(SETUP_DATA);
    UINTN                           i;
    // Porting Start
    //  Update NB_SETUP_DATA according to the default values.

    NbSetupData->GdxcEnable            = 1;
    NbSetupData->GdxcIotSize           = 4;
    NbSetupData->GdxcMotSize           = 12;
    NbSetupData->MemoryTrace           = 0;

    NbSetupData->ECT                   = 0;
    NbSetupData->SOT                   = 1;
    NbSetupData->RDMPRT                = 1;
    NbSetupData->RCVET                 = 1;
    NbSetupData->JWRL                  = 1;
    NbSetupData->FWRL                  = 0;
    NbSetupData->WRTC1D                = 1;
    NbSetupData->RDTC1D                = 1;
    NbSetupData->DIMMODTT              = 1;
    NbSetupData->WRDST                 = 0;
    NbSetupData->WREQT                 = 1;

    NbSetupData->RDODTT                = 1;
    NbSetupData->RDEQT                 = 0;
    NbSetupData->RDAPT                 = 1;
    NbSetupData->WRTC2D                = 1;
    NbSetupData->RDTC2D                = 1;
    NbSetupData->CMDVC                 = 1;
    NbSetupData->WRVC2D                = 1;
    NbSetupData->RDVC2D                = 1;
    NbSetupData->LCT                   = 1;
    NbSetupData->RTL                   = 1;
    NbSetupData->TAT                   = 1;
    NbSetupData->MEMTST                = 0;
    NbSetupData->DIMMODTT1D            = 0;
    NbSetupData->WRSRT                 = 0;
    NbSetupData->DIMMRONT              = 1;
    NbSetupData->ALIASCHK              = 1;
    NbSetupData->RCVENC1D              = 1;
    NbSetupData->RMC                   = 1;

    NbSetupData->ClttConfig            = 0;
    NbSetupData->Altitude              = 0;
    NbSetupData->Tcrit                 = 0;
    NbSetupData->Thigh                 = 0;
    NbSetupData->BwLimitTf             = 1023;
    NbSetupData->WarmThreshold         = 0;
    NbSetupData->BwLimitWarm           = 0;
    NbSetupData->HotThreshold          = 0;
    NbSetupData->BwLimitHot            = 0;
    NbSetupData->DoubleRefreshControl  = 0;

    NbSetupData->ReadVref              = 0;
    NbSetupData->InternalReadVref      = 0;

    NbSetupData->NBDxeSubSystemVendorId  = V_SA_MC_VID;
    NbSetupData->NBDxeSubSystemId        = 0x2010;

    NbSetupData->IgdBootType           = 0;
    NbSetupData->DisplayPipeB          = 0;
    NbSetupData->LcdPanelType          = 0;
    NbSetupData->SdvoPanelType         = 0;
    NbSetupData->LcdPanelScaling       = 0;
    NbSetupData->GtOcSupport           = 0;
    NbSetupData->GtVoltageOffset       = 0;
    NbSetupData->GtMaxOcTurboRatio     = 0x16;
    NbSetupData->GtVoltageOverride     = 0;
    NbSetupData->GtExtraTurboVoltage   = 0;
    NbSetupData->SaVoltageOffset       = 0;
    NbSetupData->GtVoltageMode         = 0;
    NbSetupData->IoaVoltageOffset      = 0;
    NbSetupData->IodVoltageOffset      = 0;

    NbSetupData->IgdLcdBlc             = 0;
    NbSetupData->IgdLcdIBia            = 6;
    NbSetupData->IgdLcdSSCC            = 1;
    NbSetupData->IgdTV1Standard        = 0;
    NbSetupData->IgdTV2Standard        = 0;
    NbSetupData->AlsEnable             = 0;
    NbSetupData->ActiveLFP             = 1;
    NbSetupData->LfpColorDepth         = 0;
    NbSetupData->AlwaysEnablePeg       = 0;
    for(i = 0; i < 3; i++) {
        NbSetupData->PegAspm[i] = 3;
        NbSetupData->PegAspmL0s[i] = 3;
        NbSetupData->PegDeEmphasis[i] = 1;
        NbSetupData->LtrEnable[i]              = 1;
        NbSetupData->LtrMaxSnoopLatency[i]     = V_SA_LTR_MAX_SNOOP_LATENCY_VALUE;
        NbSetupData->LtrMaxNoSnoopLatency[i]   = V_SA_LTR_MAX_NON_SNOOP_LATENCY_VALUE;
        NbSetupData->ObffEnable[i]             = 1;
        NbSetupData->PowerDownUnusedBundles[i] = 0xFF;
    }
    NbSetupData->PegSamplerCalibrate   = 2;
    NbSetupData->SwingControl          = 0;
    NbSetupData->PegComplianceTestingMode = 0;
    NbSetupData->PegGen3Equalization   = 1;
    NbSetupData->PegGen3EqualizationPhase2 = 2;
    NbSetupData->PegGen3PresetSearch = 0;
    NbSetupData->PegGen3ForcePresetSearch = 0;
    NbSetupData->PegGen3PresetSearchDwellTime = 1000;
    NbSetupData->PegGen3PresetSearchMarginSteps = 2;
    NbSetupData->PegGen3PresetSearchStartMargin = 15;
    NbSetupData->PegGen3PresetSearchVoltageMarginSteps = 2;
    NbSetupData->PegGen3PresetSearchVoltageStartMargin = 20;
    NbSetupData->PegGen3PresetSearchFavorTiming = 0;
    NbSetupData->PegGen3PresetSearchErrorTarget = 1;
    //do not use i[16] 
    for(i = 0; i < 16; i++) {
       NbSetupData->Gen3RootPortPreset[i]    = 8;
       NbSetupData->Gen3EndPointPreset[i]    = 7;
       NbSetupData->Gen3EndPointHint[i]   = 2; 
    }

    for (i = 0; i < 8 ; i++ ) {
       NbSetupData->Gen3RxCtleP[i]     = 8;
    }

    NbSetupData->InitPcieAspmAfterOprom = 0;
    NbSetupData->AllowPerstGpioUsage   = 1;
    NbSetupData->AllowPerstGpio        = 50;
    NbSetupData->AllowPerstGpioActive  = 0;
    NbSetupData->RxCEMLoopback         = 0;
    NbSetupData->RxCEMLoopbackLane     = 0;
    NbSetupData->IGfxForceDisable      = 1;
    NbSetupData->GfxTurboIMON          = 31;
    NbSetupData->RenderStandby         = 1;
    NbSetupData->DeepRenderStandby     = 1;
    NbSetupData->PrimaryDisplay        = 3;
    NbSetupData->DetectNonComplaint    = 0;
    NbSetupData->PrimaryPeg            = 0;
    NbSetupData->PrimaryPcie           = 0;
    NbSetupData->IGpuPortConfig        = 1;
    NbSetupData->DigitalPortBMode      = 0;
    NbSetupData->DigitalPortCMode      = 0;
    NbSetupData->DigitalPortDMode      = 0;
    NbSetupData->InternalGraphics      = 2;
    NbSetupData->GTTSize               = 2;
    NbSetupData->ApertureSize          = 2;
    NbSetupData->PanelPowerEnable      = 0;
    NbSetupData->IgdDvmt50PreAlloc     = 2;
    NbSetupData->IgdDvmt50TotalAlloc   = 2;
    NbSetupData->LowPowerMode          = 1;
    NbSetupData->EnableVtd             = 0;
    NbSetupData->SaDevice7             = 0;
    NbSetupData->SaDevice4             = 0;
    NbSetupData->SaAudioEnable         = 0;
    NbSetupData->NbSaHdaVerbTable      = gNbSaHdaVerbTable;
    NbSetupData->NbSaHdaVerbTable->VerbTableData = gNbSaHdaVerbTableData;
    NbSetupData->NbSaHdaVerbTableNum   = sizeof (gNbSaHdaVerbTable) / sizeof (NB_SA_HDA_VERB_TABLE);
//    NbSetupData->SaHdmiCodecPortB      = 0;
//    NbSetupData->SaHdmiCodecPortC      = 0;
//    NbSetupData->SaHdmiCodecPortD      = 1;
    NbSetupData->EnableNbCrid          = 0;
    NbSetupData->ChHashEnable          = 1;
    NbSetupData->ChHashMask            = 0x30CE;
    NbSetupData->ChHashInterleaveBit   = 1;
    NbSetupData->DqPinsInterleaved     = FALSE;
    NbSetupData->MaxTolud              = 0;
    NbSetupData->OcDdrFreqLimit        = 1333;
    NbSetupData->DdrFreqLimit          = 0;
    NbSetupData->MemoryThermalManagement  = 1;
    NbSetupData->ThermalThresholdWarm     = 80;
    NbSetupData->ThermalThresholdHot      = 90;
    NbSetupData->ThermalThresholdCritical = 100;
    NbSetupData->PeciInjectedTemp        = 0;
    NbSetupData->ExttsViaTsOnBoard       = 0;
    NbSetupData->ExttsViaTsOnDimm        = 0;
    NbSetupData->VirtualTempSensor       = 0;
    NbSetupData->SpdProfileSelected      = 0;
    NbSetupData->DDRLVOption             = 0;
    NbSetupData->DDRVoltageWaitTime      = 2000000;
    NbSetupData->EccSupport             = 1;
    NbSetupData->NModeSupport           = 0;
    NbSetupData->ScramblerSupport       = 1;
    NbSetupData->WeaklockEn             = 1;
    NbSetupData->McLock                 = 1;
    NbSetupData->AutoSelfRefreshSupport = TRUE;
    NbSetupData->ExtTemperatureSupport  = TRUE;

    NbSetupData->CAVrefCtlOffset    = 6;
    NbSetupData->Ch0VrefCtlOffset   = 6;
    NbSetupData->Ch1VrefCtlOffset   = 6;
    NbSetupData->Ch0ClkPiCodeOffset = 6;
    NbSetupData->Ch1ClkPiCodeOffset = 6;
    NbSetupData->Ch0RcvEnOffset     = 3;
    NbSetupData->Ch0RxDqsOffset     = 3;
    NbSetupData->Ch0TxDqOffset      = 3;
    NbSetupData->Ch0TxDqsOffset     = 3;
    NbSetupData->Ch0VrefOffset      = 6;
    NbSetupData->Ch1RcvEnOffset     = 3;
    NbSetupData->Ch1RxDqsOffset     = 3;
    NbSetupData->Ch1TxDqOffset      = 3;
    NbSetupData->Ch1TxDqsOffset     = 3;
    NbSetupData->Ch1VrefOffset      = 6;

    NbSetupData->BClkFrequency      = 100 * 1000 * 1000;
    NbSetupData->MaxRttWr           = 0;

#if MRC_DEBUG_PRINT_SUPPORT
    NbSetupData->MrcFastBoot           = 0;
    NbSetupData->RmtCrosserEnable      = 1;
    NbSetupData->BdatAcpiTableSupport  = 1;
#else
    NbSetupData->MrcFastBoot           = 1;
    NbSetupData->RmtCrosserEnable      = 0;
    NbSetupData->BdatAcpiTableSupport  = 0;
#endif
    NbSetupData->ForceColdReset        = 0;
    NbSetupData->RemapEnable           = 1;
    NbSetupData->DisableDimmChannel0   = 0;
    NbSetupData->DisableDimmChannel1   = 0;
    NbSetupData->ExitMode              = 0xff;
    NbSetupData->PowerDownMode0        = 0x06;
    NbSetupData->PowerDownMode1        = 0xff;
    NbSetupData->PwdwnIdleCounter      = 0x80;
    NbSetupData->EnhancedInterleave    = 1;
    NbSetupData->RankInterleave        = 1;
    NbSetupData->DmiVc1                = 1;
    NbSetupData->DmiVcp                = 1;
    NbSetupData->DmiVcm                = 1;
    NbSetupData->DmiGen2               = 2;
    NbSetupData->DmiDeEmphasis         = 0;
    NbSetupData->DmiIot                = 0;
    NbSetupData->C7Allowed             = 0;

    NbSetupData->PegGenx0              = 0;
    NbSetupData->PegGenx1              = 0;
    NbSetupData->PegGenx2              = 0;
    NbSetupData->NBDmiAspm             = 0;
    NbSetupData->NBDmiExtSync          = 0;
    NbSetupData->LockPTMregs           = 0;
    NbSetupData->Refresh2X             = 0;
    NbSetupData->Refresh2XMode         = 0;
    NbSetupData->LpddrThermalSensor    = 1;
    NbSetupData->SrefCfgEna            = 1;
    NbSetupData->SrefCfgIdleTmr        = 512;
    NbSetupData->ThrtCkeMinDefeat      = 1;
    NbSetupData->ThrtCkeMinTmr         = 48;
    NbSetupData->ThrtCkeMinDefeatLpddr = 1;
    NbSetupData->ThrtCkeMinTmrLpddr    = 64;
    NbSetupData->EnablePwrDn           = 1;
    NbSetupData->EnablePwrDnLpddr      = 0;
    NbSetupData->EnableExtts           = 0;
    NbSetupData->EnableCltm            = 0;
    NbSetupData->EnableOltm            = 0;
    NbSetupData->WarmThresholdCh0Dimm0 = 0xFF;
    NbSetupData->WarmThresholdCh0Dimm1 = 0xFF;
    NbSetupData->WarmThresholdCh1Dimm0 = 0xFF;
    NbSetupData->WarmThresholdCh1Dimm1 = 0xFF;
    NbSetupData->HotThresholdCh0Dimm0  = 0xFF;
    NbSetupData->HotThresholdCh0Dimm1  = 0xFF;
    NbSetupData->HotThresholdCh1Dimm0  = 0xFF;
    NbSetupData->HotThresholdCh1Dimm1  = 0xFF;
    NbSetupData->WarmBudgetCh0Dimm0    = 0xFF;
    NbSetupData->WarmBudgetCh0Dimm1    = 0xFF;
    NbSetupData->WarmBudgetCh1Dimm0    = 0xFF;
    NbSetupData->WarmBudgetCh1Dimm1    = 0xFF;
    NbSetupData->HotBudgetCh0Dimm0     = 0xFF;
    NbSetupData->HotBudgetCh0Dimm1     = 0xFF;
    NbSetupData->HotBudgetCh1Dimm0     = 0xFF;
    NbSetupData->HotBudgetCh1Dimm1     = 0xFF;
    NbSetupData->UserPowerWeightsEn    = 0;
    NbSetupData->EnergyScaleFact       = 4;
    NbSetupData->IdleEnergyCh0Dimm1    = 10;
    NbSetupData->IdleEnergyCh0Dimm0    = 10;
    NbSetupData->IdleEnergyCh1Dimm1    = 10;
    NbSetupData->IdleEnergyCh1Dimm0    = 10;
    NbSetupData->PdEnergyCh0Dimm1      = 6;
    NbSetupData->PdEnergyCh0Dimm0      = 6;
    NbSetupData->PdEnergyCh1Dimm1      = 6;
    NbSetupData->PdEnergyCh1Dimm0      = 6;
    NbSetupData->ActEnergyCh0Dimm1     = 172;
    NbSetupData->ActEnergyCh0Dimm0     = 172;
    NbSetupData->ActEnergyCh1Dimm1     = 172;
    NbSetupData->ActEnergyCh1Dimm0     = 172;
    NbSetupData->RdEnergyCh0Dimm1      = 212;
    NbSetupData->RdEnergyCh0Dimm0      = 212;
    NbSetupData->RdEnergyCh1Dimm1      = 212;
    NbSetupData->RdEnergyCh1Dimm0      = 212;
    NbSetupData->WrEnergyCh0Dimm1      = 221;
    NbSetupData->WrEnergyCh0Dimm0      = 221;
    NbSetupData->WrEnergyCh1Dimm1      = 221;
    NbSetupData->WrEnergyCh1Dimm0      = 221;
    NbSetupData->RaplPwrFlCh1          = 0;
    NbSetupData->RaplPwrFlCh0          = 0;
    NbSetupData->RaplLim2Lock          = 0;
    NbSetupData->RaplLim2WindX         = 1;
    NbSetupData->RaplLim2WindY         = 10;
    NbSetupData->RaplLim2Ena           = 0;
    NbSetupData->RaplLim2Pwr           = 222;
    NbSetupData->RaplLim1WindX         = 0;
    NbSetupData->RaplLim1WindY         = 0;
    NbSetupData->RaplLim1Ena           = 0;
    NbSetupData->RaplLim1Pwr           = 0;
    NbSetupData->IsRunMemoryDown       = 0;
    NbSetupData->tCL                   = 4;
    NbSetupData->tRCD                  = 3;
    NbSetupData->tRP                   = 3;
    NbSetupData->tRAS                  = 9;
    NbSetupData->tWR                   = 5;
    NbSetupData->tRFC                  = 15;
    NbSetupData->tRRD                  = 4;
    NbSetupData->tWTR                  = 3;
    NbSetupData->tRTP                  = 4;
    NbSetupData->tRC                   = 1;
    NbSetupData->tFAW                  = 10;
    NbSetupData->tCWL                  = 5;
    NbSetupData->tREFI                 = 1;
    NbSetupData->tRPab                 = 4;
    // SmbiosLogging Setup
    NbSetupData->SmbiosLogging         = 0;
    NbSetupData->AcpiLowPowerS0Idle    = 1;
        // Porting End

    if (Pei) {
        PeiServices = (EFI_PEI_SERVICES **)Services;
        Status = (*PeiServices)->LocatePpi( PeiServices, \
                                            &gPeiReadOnlyVar2PpiGuid, \
                                            0, \
                                            NULL, \
                                            &ReadOnlyVariable );

        if (!EFI_ERROR(Status)) {
            Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                                    L"Setup", \
                                                    &gSetupGuid, \
                                                    NULL, \
                                                    &VariableSize, \
                                                    &SetupData );
        }
    } else {
        RunServices = (EFI_RUNTIME_SERVICES *)Services;
        Status = RunServices->GetVariable( L"Setup", \
                                           &gSetupGuid, \
                                           NULL, \
                                           &VariableSize, \
                                           &SetupData );
    }


    if (EFI_ERROR(Status)) {
        NbOemSetupCallbacks( Services, NbSetupData, NULL, Pei );
    } else {
        NbOemSetupCallbacks( Services, NbSetupData, &SetupData, Pei );
    }


}

#if defined NB_SETUP_SUPPORT && NB_SETUP_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NbSetupCallbacks
//
// Description: This function returns NB Chipset setup data from system SetupData
//              variable 
//
// Input:       *Services    - Pointer to PeiServices or RuntimeServices
//                             structure  
//              *NbSetupData - Pointer to custom setup data to return
//              *SetupData   - Pointer to system setup data.
//              Pei          - Pei flag. If TRUE we are in PEI phase
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NbSetupCallbacks (
    IN VOID              *Services,
    IN OUT NB_SETUP_DATA *NbSetupData,
    IN SETUP_DATA        *SetupData,
    IN BOOLEAN           Pei )
{
    UINTN    i;

    if (SetupData != NULL) {

        // Porting Start
        NbSetupData->GdxcEnable            = SetupData->GdxcEnable;
        //  Update NB_SETUP_DATA according to the setup datas.
        NbSetupData->IgdBootType           = SetupData->IgdBootType;
        NbSetupData->DisplayPipeB          = SetupData->DisplayPipeB;
        NbSetupData->LcdPanelType          = SetupData->LcdPanelType;
        NbSetupData->SdvoPanelType         = SetupData->SdvoPanelType;
        NbSetupData->LcdPanelScaling       = SetupData->LcdPanelScaling;
        NbSetupData->IgdLcdBlc             = SetupData->IgdLcdBlc;
        NbSetupData->IgdLcdIBia            = SetupData->IgdLcdIBia;
        NbSetupData->IgdLcdSSCC            = SetupData->IgdLcdSSCC;
        NbSetupData->IgdTV1Standard        = SetupData->IgdTV1Standard;
        NbSetupData->IgdTV2Standard        = SetupData->IgdTV2Standard;
        NbSetupData->AlsEnable             = SetupData->AlsEnable;
        NbSetupData->ActiveLFP             = SetupData->ActiveLFP;
        NbSetupData->LfpColorDepth         = SetupData->LfpColorDepth;
        NbSetupData->AlwaysEnablePeg       = SetupData->AlwaysEnablePeg;
        for(i = 0; i < 3; i++) {
            NbSetupData->PegAspm[i] = SetupData->PegAspm[i];
            NbSetupData->PegAspmL0s[i] = SetupData->PegAspmL0s[i];
            NbSetupData->PegDeEmphasis[i] = SetupData->PegDeEmphasis[i];
        }
        NbSetupData->PegSamplerCalibrate   = SetupData->PegSamplerCalibrate;
        NbSetupData->SwingControl          = SetupData->SwingControl;
        NbSetupData->PegGen3Equalization   = SetupData->PegGen3Equalization;
        NbSetupData->PegGen3EqualizationPhase2      = SetupData->PegGen3EqualizationPhase2;
        NbSetupData->PegGen3PresetSearch            = SetupData->PegGen3PresetSearch;
        NbSetupData->PegGen3ForcePresetSearch       = SetupData->PegGen3ForcePresetSearch;
        NbSetupData->PegGen3PresetSearchDwellTime   = SetupData->PegGen3PresetSearchDwellTime;
        NbSetupData->PegGen3PresetSearchMarginSteps = SetupData->PegGen3PresetSearchMarginSteps;
        NbSetupData->PegGen3PresetSearchStartMargin = SetupData->PegGen3PresetSearchStartMargin;
        NbSetupData->PegGen3PresetSearchVoltageMarginSteps = SetupData->PegGen3PresetSearchVoltageMarginSteps;
        NbSetupData->PegGen3PresetSearchVoltageStartMargin = SetupData->PegGen3PresetSearchVoltageStartMargin;
        NbSetupData->PegGen3PresetSearchFavorTiming = SetupData->PegGen3PresetSearchFavorTiming;
        NbSetupData->PegGen3PresetSearchErrorTarget = SetupData->PegGen3PresetSearchErrorTarget;
        //do not use i[16] 
        for(i = 0; i < 16; i++) {
           NbSetupData->Gen3RootPortPreset[i] = SetupData->Gen3RootPortPreset[i];
           NbSetupData->Gen3EndPointPreset[i] = SetupData->Gen3EndPointPreset[i];
           NbSetupData->Gen3EndPointHint[i]   = SetupData->Gen3EndPointHint[i];
        }

        for (i = 0; i < 8 ; i++ ) {
           NbSetupData->Gen3RxCtleP[i]     = SetupData->Gen3RxCtleP[i];
        }
        NbSetupData->InitPcieAspmAfterOprom = SetupData->InitPcieAspmAfterOprom;
        NbSetupData->AllowPerstGpioUsage    = SetupData->AllowPerstGpioUsage;
        NbSetupData->RxCEMLoopback          = SetupData->RxCEMLoopback;
        NbSetupData->RxCEMLoopbackLane      = SetupData->RxCEMLoopbackLane;
        NbSetupData->IGfxForceDisable       = SetupData->IGfxForceDisable;
        NbSetupData->GfxTurboIMON           = SetupData->GfxTurboIMON;
        NbSetupData->RenderStandby          = SetupData->RenderStandby;
        NbSetupData->DeepRenderStandby      = SetupData->DeepRenderStandby;
        NbSetupData->GtOcSupport            = SetupData->GtOcSupport;
        NbSetupData->GtMaxOcTurboRatio      = SetupData->GtMaxOcTurboRatio;
        NbSetupData->GtExtraTurboVoltage    = SetupData->GtExtraTurboVoltage;
        NbSetupData->PrimaryDisplay         = SetupData->PrimaryDisplay;
        NbSetupData->DetectNonComplaint     = SetupData->DetectNonComplaint;
        NbSetupData->PrimaryPeg             = SetupData->PrimaryPeg;
        NbSetupData->PrimaryPcie            = SetupData->PrimaryPcie;
        NbSetupData->IGpuPortConfig         = SetupData->IGpuPortConfig;
        NbSetupData->DigitalPortBMode       = SetupData->DigitalPortBMode;
        NbSetupData->DigitalPortCMode      = SetupData->DigitalPortCMode;
        NbSetupData->DigitalPortDMode      = SetupData->DigitalPortDMode;
        NbSetupData->InternalGraphics      = SetupData->InternalGraphics;
        NbSetupData->GTTSize               = SetupData->GTTSize;
        NbSetupData->ApertureSize          = SetupData->ApertureSize;
        NbSetupData->IgdDvmt50PreAlloc     = SetupData->IgdDvmt50PreAlloc;
        NbSetupData->IgdDvmt50TotalAlloc   = SetupData->IgdDvmt50TotalAlloc;
        NbSetupData->LowPowerMode          = SetupData->LowPowerMode;
        NbSetupData->EnableVtd             = SetupData->EnableVtd;
        NbSetupData->SaDevice7             = SetupData->SaDevice7;
        NbSetupData->SaDevice4             = SetupData->SaDevice4;
        NbSetupData->SaAudioEnable         = SetupData->SaAudioEnable;
        NbSetupData->C7Allowed             = SetupData->C7Allowed;
 //       NbSetupData->SaHdmiCodecPortB      = SetupData->SaHdmiCodecPortB;
 //       NbSetupData->SaHdmiCodecPortC      = SetupData->SaHdmiCodecPortC;
 //       NbSetupData->SaHdmiCodecPortD      = SetupData->SaHdmiCodecPortD;

        NbSetupData->EnableNbCrid          = SetupData->EnableNbCrid;
        NbSetupData->ChHashEnable          = SetupData->ChHashEnable;
        NbSetupData->ChHashMask            = SetupData->ChHashMask;
        NbSetupData->ChHashInterleaveBit   = SetupData->ChHashInterleaveBit;
        NbSetupData->BdatAcpiTableSupport  = SetupData->BdatAcpiTableSupport;
        NbSetupData->MaxTolud              = SetupData->MaxTolud;
        NbSetupData->DdrFreqLimit          = SetupData->DdrFreqLimit;
        NbSetupData->OcDdrFreqLimit        = SetupData->OcDdrFreqLimit;
        NbSetupData->MemoryThermalManagement = SetupData->MemoryThermalManagement;
        NbSetupData->PeciInjectedTemp        = SetupData->PeciInjectedTemp;
        NbSetupData->ExttsViaTsOnBoard       = SetupData->ExttsViaTsOnBoard;
        NbSetupData->ExttsViaTsOnDimm        = SetupData->ExttsViaTsOnDimm;
        NbSetupData->VirtualTempSensor       = SetupData->VirtualTempSensor;
        NbSetupData->SpdProfileSelected      = SetupData->SpdProfileSelected;
        NbSetupData->DDRLVOption             = SetupData->DDRLVOption;
        NbSetupData->DDRVoltageWaitTime      = SetupData->DDRVoltageWaitTime;
        NbSetupData->EccSupport            = SetupData->EccSupport;
        NbSetupData->NModeSupport          = SetupData->NModeSupport;
        NbSetupData->ScramblerSupport      = SetupData->ScramblerSupport;
        NbSetupData->RmtCrosserEnable      = SetupData->RmtCrosserEnable;
        NbSetupData->MrcFastBoot           = SetupData->MrcFastBoot;
        NbSetupData->ForceColdReset        = SetupData->ForceColdReset;

        NbSetupData->RemapEnable           = SetupData->RemapEnable;
        NbSetupData->DisableDimmChannel0   = SetupData->DisableDimmChannel0;
        NbSetupData->DisableDimmChannel1   = SetupData->DisableDimmChannel1;
        NbSetupData->ExitMode              = SetupData->ExitMode;
        NbSetupData->PowerDownMode0        = SetupData->PowerDownMode0;
        NbSetupData->PowerDownMode1        = SetupData->PowerDownMode1;
        NbSetupData->PwdwnIdleCounter      = SetupData->PwdwnIdleCounter;
        NbSetupData->EnhancedInterleave    = SetupData->EnhancedInterleave;
        NbSetupData->RankInterleave        = SetupData->RankInterleave;
        NbSetupData->WeaklockEn            = SetupData->WeaklockEn;
        NbSetupData->McLock                = SetupData->McLock;
        NbSetupData->DmiVc1                = SetupData->DmiVc1;
        NbSetupData->DmiVcp                = SetupData->DmiVcp;
        NbSetupData->DmiVcm                = SetupData->DmiVcm;
        NbSetupData->DmiGen2               = SetupData->DmiGen2;
        NbSetupData->DmiDeEmphasis         = SetupData->DmiDeEmphasis;
        NbSetupData->DmiIot                = SetupData->DmiIot;
        NbSetupData->PegGenx0              = SetupData->PegGenx0;
        NbSetupData->PegGenx1              = SetupData->PegGenx1;
        NbSetupData->PegGenx2              = SetupData->PegGenx2;
        NbSetupData->NBDmiAspm             = SetupData->NBDmiAspm;
        NbSetupData->NBDmiExtSync          = SetupData->NBDmiExtSync;
        NbSetupData->LockPTMregs           = SetupData->LockPTMregs;
        NbSetupData->Refresh2X             = SetupData->Refresh2X;
        if (SetupData->Refresh2X)
          NbSetupData->Refresh2XMode       = SetupData->Refresh2XMode;
        else
          NbSetupData->Refresh2XMode       = 0;
        NbSetupData->LpddrThermalSensor    = SetupData->LpddrThermalSensor;
        NbSetupData->SrefCfgEna            = SetupData->SrefCfgEna;
        NbSetupData->SrefCfgIdleTmr        = SetupData->SrefCfgIdleTmr;
        NbSetupData->ThrtCkeMinDefeat      = SetupData->ThrtCkeMinDefeat;
        NbSetupData->ThrtCkeMinTmr         = SetupData->ThrtCkeMinTmr;
        NbSetupData->ThrtCkeMinDefeatLpddr = SetupData->ThrtCkeMinDefeatLpddr;
        NbSetupData->ThrtCkeMinTmrLpddr    = SetupData->ThrtCkeMinTmrLpddr;
        NbSetupData->EnablePwrDnLpddr      = SetupData->EnablePwrDnLpddr;
        NbSetupData->EnableExtts           = SetupData->EnableExtts;
        NbSetupData->EnableCltm            = SetupData->EnableCltm;
        NbSetupData->EnableOltm            = SetupData->EnableOltm;
        NbSetupData->WarmThresholdCh0Dimm0 = SetupData->WarmThresholdCh0Dimm0;
        NbSetupData->WarmThresholdCh0Dimm1 = SetupData->WarmThresholdCh0Dimm1;
        NbSetupData->WarmThresholdCh1Dimm0 = SetupData->WarmThresholdCh1Dimm0;
        NbSetupData->WarmThresholdCh1Dimm1 = SetupData->WarmThresholdCh1Dimm1;
        NbSetupData->HotThresholdCh0Dimm0  = SetupData->HotThresholdCh0Dimm0;
        NbSetupData->HotThresholdCh0Dimm1  = SetupData->HotThresholdCh0Dimm1;
        NbSetupData->HotThresholdCh1Dimm0  = SetupData->HotThresholdCh1Dimm0;
        NbSetupData->HotThresholdCh1Dimm1  = SetupData->HotThresholdCh1Dimm1;
        NbSetupData->WarmBudgetCh0Dimm0    = SetupData->WarmBudgetCh0Dimm0;
        NbSetupData->WarmBudgetCh0Dimm1    = SetupData->WarmBudgetCh0Dimm1;
        NbSetupData->WarmBudgetCh1Dimm0    = SetupData->WarmBudgetCh1Dimm0;
        NbSetupData->WarmBudgetCh1Dimm1    = SetupData->WarmBudgetCh1Dimm1;
        NbSetupData->HotBudgetCh0Dimm0     = SetupData->HotBudgetCh0Dimm0;
        NbSetupData->HotBudgetCh0Dimm1     = SetupData->HotBudgetCh0Dimm1;
        NbSetupData->HotBudgetCh1Dimm0     = SetupData->HotBudgetCh1Dimm0;
        NbSetupData->HotBudgetCh1Dimm1     = SetupData->HotBudgetCh1Dimm1;

        NbSetupData->UserPowerWeightsEn    = SetupData->UserPowerWeightsEn;
        NbSetupData->EnergyScaleFact       = SetupData->EnergyScaleFact;
        NbSetupData->IdleEnergyCh0Dimm1    = SetupData->IdleEnergyCh0Dimm1;
        NbSetupData->IdleEnergyCh0Dimm0    = SetupData->IdleEnergyCh0Dimm0;
        NbSetupData->IdleEnergyCh1Dimm1    = SetupData->IdleEnergyCh1Dimm1;
        NbSetupData->IdleEnergyCh1Dimm0    = SetupData->IdleEnergyCh1Dimm0;
        NbSetupData->PdEnergyCh0Dimm1      = SetupData->PdEnergyCh0Dimm1;
        NbSetupData->PdEnergyCh0Dimm0      = SetupData->PdEnergyCh0Dimm0;
        NbSetupData->PdEnergyCh1Dimm1      = SetupData->PdEnergyCh1Dimm1;
        NbSetupData->PdEnergyCh1Dimm0      = SetupData->PdEnergyCh1Dimm0;
        NbSetupData->ActEnergyCh0Dimm1     = SetupData->ActEnergyCh0Dimm1;
        NbSetupData->ActEnergyCh0Dimm0     = SetupData->ActEnergyCh0Dimm0;
        NbSetupData->ActEnergyCh1Dimm1     = SetupData->ActEnergyCh1Dimm1;
        NbSetupData->ActEnergyCh1Dimm0     = SetupData->ActEnergyCh1Dimm0;
        NbSetupData->RdEnergyCh0Dimm1     = SetupData->RdEnergyCh0Dimm1;
        NbSetupData->RdEnergyCh0Dimm0     = SetupData->RdEnergyCh0Dimm0;
        NbSetupData->RdEnergyCh1Dimm1     = SetupData->RdEnergyCh1Dimm1;
        NbSetupData->RdEnergyCh1Dimm0     = SetupData->RdEnergyCh1Dimm0;
        NbSetupData->WrEnergyCh0Dimm1     = SetupData->WrEnergyCh0Dimm1;
        NbSetupData->WrEnergyCh0Dimm0     = SetupData->WrEnergyCh0Dimm0;
        NbSetupData->WrEnergyCh1Dimm1     = SetupData->WrEnergyCh1Dimm1;
        NbSetupData->WrEnergyCh1Dimm0     = SetupData->WrEnergyCh1Dimm0;

        NbSetupData->RaplPwrFlCh1          = SetupData->RaplPwrFlCh1;
        NbSetupData->RaplPwrFlCh0          = SetupData->RaplPwrFlCh0;
        NbSetupData->RaplLim2Lock          = SetupData->RaplLim2Lock;
        NbSetupData->RaplLim2WindX         = SetupData->RaplLim2WindX;
        NbSetupData->RaplLim2WindY         = SetupData->RaplLim2WindY;
        NbSetupData->RaplLim2Ena           = SetupData->RaplLim2Ena;
        NbSetupData->RaplLim2Pwr           = SetupData->RaplLim2Pwr;
        NbSetupData->RaplLim1WindX         = SetupData->RaplLim1WindX;
        NbSetupData->RaplLim1WindY         = SetupData->RaplLim1WindY;
        NbSetupData->RaplLim1Ena           = SetupData->RaplLim1Ena;
        NbSetupData->RaplLim1Pwr           = SetupData->RaplLim1Pwr;

        NbSetupData->tCL                   = SetupData->tCL;
        NbSetupData->tRCD                  = SetupData->tRCD;
        NbSetupData->tRP                   = SetupData->tRP;
        NbSetupData->tRAS                  = SetupData->tRAS;
        NbSetupData->tWR                   = SetupData->tWR;
        NbSetupData->tRFC                  = SetupData->tRFC;
        NbSetupData->tRRD                  = SetupData->tRRD;
        NbSetupData->tWTR                  = SetupData->tWTR;
        NbSetupData->tRTP                  = SetupData->tRTP;
        NbSetupData->tRC                   = SetupData->tRC;
        NbSetupData->tFAW                  = SetupData->tFAW;
        NbSetupData->tCWL                  = SetupData->tCWL;
        NbSetupData->tREFI                 = SetupData->tREFI;
        NbSetupData->tRPab                 = SetupData->tRPab;
        // SmbiosLogging Setup
#if defined (ErrorLogging_SUPPORT) && ErrorLogging_SUPPORT == 1
        NbSetupData->SmbiosLogging         = SetupData->SmbiosLogging;
#endif

#if defined (LOW_POWER_S0_IDLE_CAPABLE) && LOW_POWER_S0_IDLE_CAPABLE == 1
    #if defined (PCH_SKU) && PCH_SKU == 1
        NbSetupData->AcpiLowPowerS0Idle = !(SetupData->AcpiLowPowerS0Idle);
    #else
        NbSetupData->AcpiLowPowerS0Idle = 0;
    #endif
#endif
        // Porting End
    }
}

#endif
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
