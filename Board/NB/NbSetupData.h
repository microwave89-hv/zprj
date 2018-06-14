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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NbSetupData.h 23    6/21/13 5:20a Ireneyang $
//
// $Revision: 23 $
//
// $Date: 6/21/13 5:20a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NbSetupData.h $
// 
// 23    6/21/13 5:20a Ireneyang
// Update to SBY SA RC 1.6.0.
// 
// 22    5/22/13 5:13a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add RCVENC1D into NB_SETUP_DATA for setting.
// [Files]       GetSetupData.c;
// 
// 21    5/13/13 6:27a Ireneyang
// [TAG]         None
// [Category]    Improvement
// [Description] Add PanelPowerEnable for enabling/disabling VDD force
// bit.
//               (Required only for early enabling of eDP panel)
// [Files]       NBSetup.c; GetSetupData.c; NbSetupData.h; NBPEI.c;
// 
// 20    3/15/13 1:57a Ireneyang
// [TAG]          EIP118133
// [Severity]     BugFix
// [Description]  Fix and restructure PlatformConfig setting of SA policy.
// [Files]        NBDxe.c; GetSetupData.c; NbSetupData.h;
// 
// 19    3/07/13 6:12a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Make some default SaPlatformPolicy items flexible. 
//                Define some SaPlatformPolicy items into NB_SETUP_DATA
//                structure.  
// [Files]        NbSetupData.h; GetSetupData.c; NBPEI.c; 
// 
// 18    3/07/13 3:44a Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Add "Hot only" option for Memory Refresh 2x support to 
//                meet Intel Spec.
// [Files]        NBPEI.c; NB.uni; NB.sd; NbSetupData.h; GetSetupData.c; 
// 
// 17    2/09/13 10:25a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.1.0
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; 
// 
// 16    1/28/13 3:48a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 1.0.
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; 
//                NB.sd; NB.uni; NBDxeBoard.c
// 
// 15    1/14/13 6:10a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Create setup item for  SA RC 0.90.
// [Files]        NBPei.c; GetNbSetupData.c NB.sd; NB.uni;
// 
// 14    1/10/13 6:01a Jeffch
// [TAG]          None
// [Severity]     Bug Fix
// [Description]  Fixed not program HDA codec for SaHDAVerbtable link bug.
// [Files]        NBDXE.c; GetSetupData.c; NbSetupData.h
// [TAG]          None
// [Severity]     Important
// [Description]  Create DDR PowerDown and idle counter for setup item.
// [Files]        NBPei.c; NB.sd; NB.uni; GetSetupData.c; NbSetupData.h
// 
// 13    1/03/13 7:31a Jeffch
// [TAG]          None
// [Severity]     Improvement
// [Description]  added SaHDAVerbtable link to OEM.
// [Files]        NBDxe.c; NbSetupData.h; GetSetupData.c;
// 
// 12    12/22/12 2:30a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Create setup item for  SA RC 0.81.
// [Files]        NBPei.c; GetNbSetupData.c NB.sd; NB.uni;
// 
// 11    12/18/12 5:17a Jeffch
// [TAG]          None
// [Severity]     Spec update
// [Description]  Update SA RC 0.81.
// [Files]        GetSetupData.c; NbSetupData.h;
// 
// 10    12/14/12 4:53a Jeffch
// [TAG]          EIP106709
// [Severity]     Important
// [Description]  Support PCIE Primary display.
// [Files]        NB.sd; NBDXEboard.c; NB.uni;
// GetSetupData.c;NbSetupData.h;
// 
// 9     11/14/12 5:33a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Update XTU4.x function
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h; NBDXE.c; NB.sd;
// NB.uni
// 
// 8     11/07/12 6:25a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Support ULT one BIOS
// [Files]        NBPei.c; GetSetupData.c; NbSetupData.h
// 
// 7     10/18/12 11:17p Jeffch
//  [TAG]          EIP104234
//  [Severity]     Important
//  [Description]  Fixed cannot compile 4.6.5.3_Intel_SA-RC_071_019a with
//      NB_ERROR_LOG_SUPPORT.
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
// 2     4/05/12 2:23a Yurenlai
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

#ifndef __NB_SETUP_DATA_H__ // To Avoid this header get compiled twice
#define __NB_SETUP_DATA_H__

#include <Efi.h>

#ifdef __cplusplus
extern "C" {
#endif
   
typedef struct  _NB_SETUP_DATA  NB_SETUP_DATA;

#pragma pack(push, 1)

typedef struct {
  UINT32  VendorDeviceId;
  UINT16  SubSystemId;
  UINT8   RevisionId; ///< 0xFF applies to all steppings
  UINT8   FrontPanelSupport;
  UINT16  NumberOfRearJacks;
  UINT16  NumberOfFrontJacks;
} NB_SA_HDA_VERB_TABLE_HEADER;

typedef struct {
  NB_SA_HDA_VERB_TABLE_HEADER  VerbTableHeader;
  UINT32                    *VerbTableData;
} NB_SA_HDA_VERB_TABLE;

typedef struct _NB_SETUP_DATA {
    UINT8   GdxcEnable;
    UINT8   GdxcIotSize;
    UINT8   GdxcMotSize;
    UINT8   MemoryTrace;

    UINT8   ECT;
    UINT8   SOT;
    UINT8   RDMPRT;
    UINT8   RCVET;
    UINT8   JWRL;
    UINT8   FWRL;
    UINT8   WRTC1D;
    UINT8   RDTC1D;
    UINT8   DIMMODTT;
    UINT8   WRDST;
    UINT8   WREQT;

    UINT8   RDODTT;
    UINT8   RDEQT;
    UINT8   RDAPT;
    UINT8   WRTC2D;
    UINT8   RDTC2D;
    UINT8   CMDVC;
    UINT8   WRVC2D;
    UINT8   RDVC2D;
    UINT8   LCT;
    UINT8   RTL;
    UINT8   TAT;
    UINT8   MEMTST;
    UINT8   DIMMODTT1D;
    UINT8   WRSRT;
    UINT8   DIMMRONT;
    UINT8   ALIASCHK;
    UINT8   RCVENC1D;
    UINT8   RMC;

    UINT8   ClttConfig;
    UINT8   Altitude;
    UINT8   Tcrit;
    UINT8   Thigh;
    UINT16  BwLimitTf;
    UINT8   WarmThreshold;
    UINT8   BwLimitWarm;
    UINT8   HotThreshold;
    UINT8   BwLimitHot;
    UINT8   DoubleRefreshControl;

    UINT8   ReadVref;
    UINT8   InternalReadVref;

    UINT16  NBDxeSubSystemVendorId;
    UINT16  NBDxeSubSystemId;       

    UINT8   IgdBootType;
    UINT8   DisplayPipeB;
    UINT8   LcdPanelType;
    UINT8   SdvoPanelType;
    UINT8   LcdPanelScaling;
    UINT8   IGfxForceDisable;

    UINT8   RenderStandby;
    UINT8   DeepRenderStandby;

    // GT related
    UINT8   GtOcSupport;
    INT16   GtVoltageOffset;
    UINT16  GtVoltageOverride;
    UINT16  GtExtraTurboVoltage;
    UINT16  GtMaxOcTurboRatio;
    INT16   SaVoltageOffset;
    UINT8   GtVoltageMode;
    INT16   IoaVoltageOffset;
    INT16   IodVoltageOffset; 

    // LCD
    UINT8   IgdLcdBlc;
    UINT8   IgdLcdIBia;
    UINT8   IgdLcdSSCC;
    UINT8   IgdTV1Standard;
    UINT8   IgdTV2Standard;
    UINT8   AlsEnable;
    UINT8   LowPowerMode;
    UINT8   ActiveLFP;
    UINT8   LfpColorDepth;
    UINT8   GTTSize;
    UINT8   ApertureSize;
    UINT8   PanelPowerEnable;

    // PEG
    UINT8   PegAspm[3];  
    UINT8   PegAspmL0s[3];
    UINT8   PegDeEmphasis[3];
    UINT8   AlwaysEnablePeg;
    UINT8   PegSamplerCalibrate;
    UINT8   SwingControl;
    UINT8   PegComplianceTestingMode;
    UINT8   PegGen3Equalization;
    UINT8   PegGen3EqualizationPhase2;
    UINT8   PegGen3PresetSearch;
    UINT8   PegGen3ForcePresetSearch;
    UINT16  PegGen3PresetSearchDwellTime;
    UINT8   PegGen3PresetSearchMarginSteps;
    UINT8   PegGen3PresetSearchStartMargin;
    UINT8   PegGen3PresetSearchVoltageMarginSteps;
    UINT8   PegGen3PresetSearchVoltageStartMargin;
    UINT8   PegGen3PresetSearchFavorTiming;
    UINT16  PegGen3PresetSearchErrorTarget;
    UINT8   RxCEMLoopback;
    UINT8   RxCEMLoopbackLane;
    UINT8   Gen3RootPortPreset[16];
    UINT8   Gen3EndPointPreset[16];
    UINT8   Gen3EndPointHint[16];
    UINT8   Gen3RxCtleP[8];
    UINT8   InitPcieAspmAfterOprom;
    UINT8   AllowPerstGpioUsage;
    UINT8   AllowPerstGpio;
    UINT8   AllowPerstGpioActive;
    UINT8   LtrEnable[3];
    UINT16  LtrMaxSnoopLatency[3];
    UINT16  LtrMaxNoSnoopLatency[3];
    UINT8   ObffEnable[3];
    UINT8   PowerDownUnusedBundles[3];
    UINT8   C7Allowed; 
    // DVMT5.0 Graphic memory setting
    UINT8   IgdDvmt50PreAlloc;
    UINT8   IgdDvmt50TotalAlloc;

    // SA Device Control
    UINT8   SaDevice7;
    UINT8   SaDevice4;
    UINT8   SaAudioEnable;    // Device3
//    UINT8   SaHdmiCodecPortB;
//    UINT8   SaHdmiCodecPortC;
//    UINT8   SaHdmiCodecPortD;
    UINT8   NbSaHdaVerbTableNum;
    NB_SA_HDA_VERB_TABLE  *NbSaHdaVerbTable;
    // VTD  
    UINT8   EnableVtd;
    //SSVID WorkAround
    UINT8   EnableNbCrid;
    UINT8   BdatAcpiTableSupport;
    // DMI 
    UINT8   DmiVc1;
    UINT8   DmiVcp;
    UINT8   DmiVcm;
    UINT8   DmiGen2;
    UINT8   DmiDeEmphasis;
    UINT8   DmiIot;
    // ASPM
    UINT8   NBDmiAspm;
    UINT8   NBDmiExtSync;
    UINT8   PrimaryDisplay;
    UINT8   DetectNonComplaint;
    UINT8   PrimaryPeg;
    UINT8   PrimaryPcie;
    UINT8   IGpuPortConfig;
    UINT8   InternalGraphics;
    // Graphics Turbo IMON Current
    UINT8   GfxTurboIMON;
  // Digital port mode select
    UINT8   DigitalPortBMode;
    UINT8   DigitalPortCMode;
    UINT8   DigitalPortDMode;
    // MRC
    UINT8   EccSupport;
    UINT8   MrcFastBoot;
    UINT8   ForceColdReset;
    UINT8   RemapEnable;
    UINT8   DisableDimmChannel0;
    UINT8   DisableDimmChannel1;
    UINT8   CAVrefCtlOffset;       ///< REVISION_11 - CA Vref Control Offset
    UINT8   Ch0VrefCtlOffset;      ///< REVISION_11 - Channel 0 DQ Vref Control Offset
    UINT8   Ch1VrefCtlOffset;      ///< REVISION_11 - Channel 1 DQ Vref Control Offset
    UINT8   Ch0ClkPiCodeOffset;    ///< REVISION_11 - Channel 0 Clk Pi Code Offset
    UINT8   Ch1ClkPiCodeOffset;    ///< REVISION_11 - Channel 1 Clk Pi Code Offset
    UINT8   Ch0RcvEnOffset;        ///< REVISION_11 - Channel 0 Receive Enable Offset
    UINT8   Ch0RxDqsOffset;        ///< REVISION_11 - Channel 0 Read DQS Offset
    UINT8   Ch0TxDqOffset;         ///< REVISION_11 - Channel 0 Write DQ Offset
    UINT8   Ch0TxDqsOffset;        ///< REVISION_11 - Channel 0 Write DQS Offset
    UINT8   Ch0VrefOffset;         ///< REVISION_11 - Channel 0 Vref Offset
    UINT8   Ch1RcvEnOffset;        ///< REVISION_11 - Channel 1 Receive Enable Offset
    UINT8   Ch1RxDqsOffset;        ///< REVISION_11 - Channel 1 Read DQS Offset
    UINT8   Ch1TxDqOffset;         ///< REVISION_11 - Channel 1 Write DQ Offset
    UINT8   Ch1TxDqsOffset;        ///< REVISION_11 - Channel 1 Write DQS Offset
    UINT8   Ch1VrefOffset;         ///< REVISION_11 - Channel 1 Vref Offset
    BOOLEAN AutoSelfRefreshSupport;///< REVISION_11 - FALSE = No auto self refresh support, TRUE = auto self refresh support.
    BOOLEAN ExtTemperatureSupport; ///< REVISION_11 - FALSE = No extended temperature support, TRUE = extended temperature support.
    UINT8   MaxRttWr;              ///< REVISION_11 - Maximum DIMM RTT_WR to use in power training 0 = Off, 1 = 120 ohms
    UINT32  BClkFrequency;
    UINT8   MaxTolud;
    UINT8   DdrFreqLimit;
    UINT16  OcDdrFreqLimit;
    UINT8   DDRLVOption;
    UINT32  DDRVoltageWaitTime;
    UINT8   SpdProfileSelected;
    UINT8   NModeSupport;
    UINT8   ScramblerSupport;
    UINT8   RmtCrosserEnable;
    UINT8   ExitMode;
    UINT8   PowerDownMode0;
    UINT8   PowerDownMode1;
    UINT8   PwdwnIdleCounter;
    UINT8   WeaklockEn;
    UINT8   McLock;
    UINT8   EnhancedInterleave;
    UINT8   RankInterleave;
    UINT8   PegGenx0;
    UINT8   PegGenx1;
    UINT8   PegGenx2;

    UINT8   MemoryThermalManagement;
    UINT8   ThermalThresholdWarm;
    UINT8   ThermalThresholdHot;
    UINT8   ThermalThresholdCritical;
    UINT8   PeciInjectedTemp;
    UINT8   ExttsViaTsOnBoard;
    UINT8   ExttsViaTsOnDimm;
    UINT8   VirtualTempSensor;
//    UINT8   RefreshRate2x;
    UINT8   ChHashEnable;
    UINT16  ChHashMask;
    UINT8   ChHashInterleaveBit;
    BOOLEAN DqPinsInterleaved;
    //
    // Thermal Options
    //
    UINT8   EnableExtts;           ///< REVISION_10
    UINT8   EnableCltm;            ///< REVISION_10
    UINT8   EnableOltm;            ///< REVISION_10
    UINT8   EnablePwrDn;           ///< REVISION_10
    UINT8   Refresh2X;             ///< REVISION_10
    UINT8   Refresh2XMode;         ///< REVISION_10
    UINT8   LpddrThermalSensor;    ///< REVISION_10
    UINT8   LockPTMregs;           ///< REVISION_10
    UINT8   UserPowerWeightsEn;    ///< REVISION_10
    UINT8   EnergyScaleFact;       ///< REVISION_10
    UINT8   RaplPwrFlCh1;          ///< REVISION_10
    UINT8   RaplPwrFlCh0;          ///< REVISION_10
    UINT8   RaplLim2Lock;          ///< REVISION_10
    UINT8   RaplLim2WindX;         ///< REVISION_10
    UINT8   RaplLim2WindY;         ///< REVISION_10
    UINT8   RaplLim2Ena;           ///< REVISION_10
    UINT16  RaplLim2Pwr;           ///< REVISION_10
    UINT8   RaplLim1WindX;         ///< REVISION_10
    UINT8   RaplLim1WindY;         ///< REVISION_10
    UINT8   RaplLim1Ena;           ///< REVISION_10
    UINT16  RaplLim1Pwr;           ///< REVISION_10
    UINT8   WarmThresholdCh0Dimm0; ///< REVISION_10
    UINT8   WarmThresholdCh0Dimm1; ///< REVISION_10
    UINT8   WarmThresholdCh1Dimm0; ///< REVISION_10
    UINT8   WarmThresholdCh1Dimm1; ///< REVISION_10
    UINT8   HotThresholdCh0Dimm0;  ///< REVISION_10
    UINT8   HotThresholdCh0Dimm1;  ///< REVISION_10
    UINT8   HotThresholdCh1Dimm0;  ///< REVISION_10
    UINT8   HotThresholdCh1Dimm1;  ///< REVISION_10
    UINT8   WarmBudgetCh0Dimm0;    ///< REVISION_10
    UINT8   WarmBudgetCh0Dimm1;    ///< REVISION_10
    UINT8   WarmBudgetCh1Dimm0;    ///< REVISION_10
    UINT8   WarmBudgetCh1Dimm1;    ///< REVISION_10
    UINT8   HotBudgetCh0Dimm0;     ///< REVISION_10
    UINT8   HotBudgetCh0Dimm1;     ///< REVISION_10
    UINT8   HotBudgetCh1Dimm0;     ///< REVISION_10
    UINT8   HotBudgetCh1Dimm1;     ///< REVISION_10
    UINT8   IdleEnergyCh0Dimm1;    ///< REVISION_10
    UINT8   IdleEnergyCh0Dimm0;    ///< REVISION_10
    UINT8   PdEnergyCh0Dimm1;      ///< REVISION_10
    UINT8   PdEnergyCh0Dimm0;      ///< REVISION_10
    UINT8   ActEnergyCh0Dimm1;     ///< REVISION_10
    UINT8   ActEnergyCh0Dimm0;     ///< REVISION_10
    UINT8   RdEnergyCh0Dimm1;      ///< REVISION_10
    UINT8   RdEnergyCh0Dimm0;      ///< REVISION_10
    UINT8   WrEnergyCh0Dimm1;      ///< REVISION_10
    UINT8   WrEnergyCh0Dimm0;      ///< REVISION_10
    UINT8   IdleEnergyCh1Dimm1;    ///< REVISION_10
    UINT8   IdleEnergyCh1Dimm0;    ///< REVISION_10
    UINT8   PdEnergyCh1Dimm1;      ///< REVISION_10
    UINT8   PdEnergyCh1Dimm0;      ///< REVISION_10
    UINT8   ActEnergyCh1Dimm1;     ///< REVISION_10
    UINT8   ActEnergyCh1Dimm0;     ///< REVISION_10
    UINT8   RdEnergyCh1Dimm1;      ///< REVISION_10
    UINT8   RdEnergyCh1Dimm0;      ///< REVISION_10
    UINT8   WrEnergyCh1Dimm1;      ///< REVISION_10
    UINT8   WrEnergyCh1Dimm0;      ///< REVISION_10
    UINT8   SrefCfgEna;            ///< REVISION_10
    UINT16  SrefCfgIdleTmr;        ///< REVISION_10
    UINT8   ThrtCkeMinDefeat;      ///< REVISION_10
    UINT8   ThrtCkeMinTmr;         ///< REVISION_10
    UINT8   ThrtCkeMinDefeatLpddr; ///< REVISION_10
    UINT8   ThrtCkeMinTmrLpddr;    ///< REVISION_10
    UINT8   EnablePwrDnLpddr;      ///< REVISION_10 - Enable Power Down for LPDDR
    UINT8   IsRunMemoryDown;
    UINT16  tCL;
    UINT16  tRCD;
    UINT16  tRP;
    UINT16  tRAS;
    UINT16  tWR;
    UINT16  tRFC;
    UINT16  tRRD;
    UINT16  tWTR;
    UINT16  tRTP;
    UINT16  tRC;
    UINT16  tFAW;
    UINT16  tCWL;  // (P20121012A) 
    UINT16  tREFI; // (P20121012A) 
    UINT16  tRPab;
    UINT8   SmbiosLogging;  // SmbiosLogging Setup       
    UINT8   AcpiLowPowerS0Idle;  //ULT PlatformConfig
} NB_SETUP_DATA;

#pragma pack(pop)

VOID GetNbSetupData (
    IN VOID                 *Service,
    IN OUT NB_SETUP_DATA    *NbSetupData,
    IN BOOLEAN              Pei
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
