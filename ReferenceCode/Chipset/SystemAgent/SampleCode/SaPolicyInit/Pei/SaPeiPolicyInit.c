/** @file
  This file is SampleCode for Intel SA PEI Platform Policy initialzation.

@copyright
  Copyright (c) 1999 - 2014 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement

**/
#include "SaPeiPolicyInit.h"

///
/// This IO Trap address can be overridden by defining it
/// in compiling environment variable
/// It must not conflict with other IO address in platform
///
#ifndef SA_IOTRAP_SMI_ADDRESS
#define SA_IOTRAP_SMI_ADDRESS 0x2000
#endif

EFI_STATUS
SaPeiPolicyInitEntryPoint (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
/**
  This PEIM performs SA PEI Platform Policy initialzation.

  @param[in] FfsHeader    - Pointer to Firmware File System file header.
  @param[in] PeiServices  - General purpose services available to every PEIM.

  @retval EFI_SUCCESS - The PPI is installed and initialized.
  @retval EFI ERRORS  - The PPI is not successfully installed.
**/
{
  EFI_STATUS                  Status;
  EFI_PEI_PPI_DESCRIPTOR      *SaPlatformPolicyPpiDesc;
  SA_PLATFORM_POLICY_PPI      *SaPlatformPolicyPpi;
  SA_PLATFORM_DATA            *PlatformData;
  GT_CONFIGURATION            *GtConfig;
  MEMORY_CONFIGURATION        *MemConfig;
  PCIE_CONFIGURATION          *PcieConfig;
  OVERCLOCKING_CONFIGURATION  *OcConfig;
  PEG_GPIO_DATA               *PegGpioData;
  CPU_FAMILY                  CpuFamilyId;
#ifdef SG_SUPPORT
  SG_GPIO_DATA                *SgGpioData;
#endif
  UINT8                       Index;
  ///
  /// Allocate descriptor and PPI structures
  ///
  SaPlatformPolicyPpi = (SA_PLATFORM_POLICY_PPI *) AllocatePool (sizeof (SA_PLATFORM_POLICY_PPI));
  ASSERT (SaPlatformPolicyPpi != NULL);
  EfiCommonLibZeroMem (SaPlatformPolicyPpi, sizeof (SA_PLATFORM_POLICY_PPI));

  SaPlatformPolicyPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocatePool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  ASSERT (SaPlatformPolicyPpiDesc != NULL);
  EfiCommonLibZeroMem (SaPlatformPolicyPpiDesc, sizeof (EFI_PEI_PPI_DESCRIPTOR));

  PlatformData = (SA_PLATFORM_DATA *) AllocatePool (sizeof (SA_PLATFORM_DATA));
  ASSERT (PlatformData != NULL);
  EfiCommonLibZeroMem (PlatformData, sizeof (SA_PLATFORM_DATA));

  GtConfig = (GT_CONFIGURATION *) AllocatePool (sizeof (GT_CONFIGURATION));
  ASSERT (GtConfig != NULL);
  EfiCommonLibZeroMem (GtConfig, sizeof (GT_CONFIGURATION));

  MemConfig = (MEMORY_CONFIGURATION *) AllocatePool (sizeof (MEMORY_CONFIGURATION));
  ASSERT (MemConfig != NULL);
  EfiCommonLibZeroMem (MemConfig, sizeof (MEMORY_CONFIGURATION));

  PcieConfig = (PCIE_CONFIGURATION *) AllocatePool (sizeof (PCIE_CONFIGURATION));
  ASSERT (PcieConfig != NULL);
  EfiCommonLibZeroMem (PcieConfig, sizeof (PCIE_CONFIGURATION));

  PegGpioData = (PEG_GPIO_DATA *) AllocatePool (sizeof (PEG_GPIO_DATA));
  ASSERT (PegGpioData != NULL);
  EfiCommonLibZeroMem (PegGpioData, sizeof (PEG_GPIO_DATA));

  OcConfig = (OVERCLOCKING_CONFIGURATION *) AllocatePool (sizeof (OVERCLOCKING_CONFIGURATION));
  ASSERT (OcConfig != NULL);
  EfiCommonLibZeroMem (OcConfig, sizeof (OVERCLOCKING_CONFIGURATION));

#ifdef SG_SUPPORT
  SgGpioData = (SG_GPIO_DATA *) AllocatePool (sizeof (SG_GPIO_DATA));
  ASSERT (SgGpioData != NULL);
  EfiCommonLibZeroMem (SgGpioData, sizeof (SG_GPIO_DATA));
#endif

  SetMem ((VOID *) SaPlatformPolicyPpi, sizeof (SA_PLATFORM_POLICY_PPI), 0);

  ///
  /// Initialize the PPI
  ///
  SaPlatformPolicyPpiDesc->Flags  = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  SaPlatformPolicyPpiDesc->Guid   = &gSaPlatformPolicyPpiGuid;
  SaPlatformPolicyPpiDesc->Ppi    = SaPlatformPolicyPpi;

  ///
  /// Update the REVISION number
  ///
  SaPlatformPolicyPpi->Revision = SA_PLATFORM_POLICY_PPI_REVISION_15;

  CpuFamilyId = GetCpuFamily();

  ///
  /// Initialize the Platform Configuration
  ///
  PlatformData->SpdAddressTable[0]  = 0xA0;
  PlatformData->SpdAddressTable[1]  = 0xA2;
  PlatformData->SpdAddressTable[2]  = 0xA4;
  PlatformData->SpdAddressTable[3]  = 0xA6;
  PlatformData->MchBar              = 0xfed10000;
  PlatformData->DmiBar              = 0xfed18000;
  PlatformData->EpBar               = 0xfed19000;
  PlatformData->EdramBar            = 0xfed80000;
  PlatformData->PciExpressBar       = (UINTN) PcdGet64 (PcdPciExpressBaseAddress);
  PlatformData->SmbusBar            = 0xEFA0;
  PlatformData->TsegSize            = 0x800000;
  PlatformData->IedSize             = 0x400000;
  PlatformData->FastBoot            = 0;
  PlatformData->GdxcBar             = 0xFED84000;
  PlatformData->BoardId             = 0;

  SaPlatformPolicyPpi->PlatformData = PlatformData;
  ///
  /// Initialize the Graphics configuration
  ///
  GtConfig->GttSize             = 2;
  GtConfig->IgdDvmt50PreAlloc   = 1;
  GtConfig->InternalGraphics    = 2;
  GtConfig->PrimaryDisplay      = 3;
  GtConfig->ApertureSize        = 2;
  GtConfig->PanelPowerEnable    = 0;
  SaPlatformPolicyPpi->GtConfig = GtConfig;

  ///
  /// Initialize the Memory Configuration
  ///
  MemConfig->EccSupport             = 1;
  MemConfig->DdrFreqLimit           = 0;
  MemConfig->MaxTolud               = 0;
  MemConfig->SpdProfileSelected     = 0;
  MemConfig->NModeSupport           = 0;
  MemConfig->ScramblerSupport       = 1;
  MemConfig->PowerDownMode          = 0xFF;
  MemConfig->PwdwnIdleCounter       = 0x80;
  MemConfig->RankInterleave         = TRUE;
  MemConfig->EnhancedInterleave     = TRUE;
  MemConfig->WeaklockEn             = TRUE;
  MemConfig->EnCmdRate              = 7;
  MemConfig->CmdTriStateDis         = FALSE;
  MemConfig->RefreshRate2x          = FALSE;
  MemConfig->AutoSelfRefreshSupport = TRUE;
  MemConfig->ExtTemperatureSupport  = TRUE;

  ///
  /// Thermal Management Configuration
  ///
  MemConfig->ThermalManagement  = 1;
  MemConfig->PeciInjectedTemp   = 0;
  MemConfig->ExttsViaTsOnBoard  = 0;
  MemConfig->ExttsViaTsOnDimm   = 0;
  MemConfig->VirtualTempSensor  = 0;
  ///
  /// Channel DIMM Disable
  ///
  MemConfig->DisableDimmChannel[0]  = 0;
  MemConfig->DisableDimmChannel[1]  = 0;
  ///
  /// Channel Hash Configuration
  ///
  MemConfig->ChHashEnable         = TRUE;
  MemConfig->ChHashMask           = 0x30CE;
  MemConfig->ChHashInterleaveBit  = 1;
  ///
  /// Options for Thermal settings
  ///
  MemConfig->EnableExtts            = 0;
  MemConfig->EnableCltm             = 0;
  MemConfig->EnableOltm             = 0;
  MemConfig->EnablePwrDn            = 1;
  if (CpuFamilyId == EnumCpuHswUlt) {
    MemConfig->EnablePwrDnLpddr = 0;
  }
  MemConfig->Refresh2X              = 0;
  MemConfig->LpddrThermalSensor     = 1;
  MemConfig->LockPTMregs            = 0;
  MemConfig->UserPowerWeightsEn     = 0;

  MemConfig->EnergyScaleFact        = 3;
  MemConfig->RaplPwrFlCh1           = 0;
  MemConfig->RaplPwrFlCh0           = 0;

  MemConfig->RaplLim2Lock           = 0;
  MemConfig->RaplLim2WindX          = 0;
  MemConfig->RaplLim2WindY          = 0;
  MemConfig->RaplLim2Ena            = 0;
  MemConfig->RaplLim2Pwr            = 0;
  MemConfig->RaplLim1WindX          = 0;
  MemConfig->RaplLim1WindY          = 0;
  MemConfig->RaplLim1Ena            = 0;
  MemConfig->RaplLim1Pwr            = 0;

  MemConfig->WarmThresholdCh0Dimm0  = 0xFF;
  MemConfig->WarmThresholdCh0Dimm1  = 0xFF;
  MemConfig->WarmThresholdCh1Dimm0  = 0xFF;
  MemConfig->WarmThresholdCh1Dimm1  = 0xFF;
  MemConfig->HotThresholdCh0Dimm0   = 0xFF;
  MemConfig->HotThresholdCh0Dimm1   = 0xFF;
  MemConfig->HotThresholdCh1Dimm0   = 0xFF;
  MemConfig->HotThresholdCh1Dimm1   = 0xFF;
  MemConfig->WarmBudgetCh0Dimm0     = 0xFF;
  MemConfig->WarmBudgetCh0Dimm1     = 0xFF;
  MemConfig->WarmBudgetCh1Dimm0     = 0xFF;
  MemConfig->WarmBudgetCh1Dimm1     = 0xFF;
  MemConfig->HotBudgetCh0Dimm0      = 0xFF;
  MemConfig->HotBudgetCh0Dimm1      = 0xFF;
  MemConfig->HotBudgetCh1Dimm0      = 0xFF;
  MemConfig->HotBudgetCh1Dimm1      = 0xFF;

  MemConfig->IdleEnergyCh0Dimm1     = 0;
  MemConfig->IdleEnergyCh0Dimm0     = 0;
  MemConfig->PdEnergyCh0Dimm1       = 0;
  MemConfig->PdEnergyCh0Dimm0       = 0;
  MemConfig->ActEnergyCh0Dimm1      = 0;
  MemConfig->ActEnergyCh0Dimm0      = 0;
  MemConfig->RdEnergyCh0Dimm1       = 0;
  MemConfig->RdEnergyCh0Dimm0       = 0;
  MemConfig->WrEnergyCh0Dimm1       = 0;
  MemConfig->WrEnergyCh0Dimm0       = 0;

  MemConfig->IdleEnergyCh1Dimm1     = 0;
  MemConfig->IdleEnergyCh1Dimm0     = 0;
  MemConfig->PdEnergyCh1Dimm1       = 0;
  MemConfig->PdEnergyCh1Dimm0       = 0;
  MemConfig->ActEnergyCh1Dimm1      = 0;
  MemConfig->ActEnergyCh1Dimm0      = 0;
  MemConfig->RdEnergyCh1Dimm1       = 0;
  MemConfig->RdEnergyCh1Dimm0       = 0;
  MemConfig->WrEnergyCh1Dimm1       = 0;
  MemConfig->WrEnergyCh1Dimm0       = 0;

  MemConfig->SrefCfgEna             = 1;
  MemConfig->SrefCfgIdleTmr         = 0x200;
  MemConfig->ThrtCkeMinDefeat       = 0;
  MemConfig->ThrtCkeMinTmr          = 0x30;
  if (CpuFamilyId == EnumCpuHswUlt) {
    MemConfig->ThrtCkeMinDefeatLpddr = 1;
    MemConfig->ThrtCkeMinTmrLpddr    = 0x40;
  }


  MemConfig->McLock               = TRUE;

  MemConfig->GdxcEnable           = TRUE;
  MemConfig->GdxcIotSize          = 4;
  MemConfig->GdxcMotSize          = 12;
  
  MemConfig->MemoryTrace          = 0;

  MemConfig->ECT                  = 0;
  MemConfig->SOT                  = 1;
  MemConfig->RDMPRT               = 1;
  MemConfig->RCVET                = 1;
  MemConfig->JWRL                 = 1;
  MemConfig->FWRL                 = 0;
  MemConfig->WRTC1D               = 1;
  MemConfig->RDTC1D               = 1;
  MemConfig->DIMMODTT             = 1;
  MemConfig->WRDST                = 0;
  MemConfig->WREQT                = 1;
  MemConfig->RDODTT               = 1;
  MemConfig->RDEQT                = 0;
  MemConfig->RDAPT                = 1;
  MemConfig->WRTC2D               = 1;
  MemConfig->RDTC2D               = 1;
  MemConfig->CMDVC                = 1;
  MemConfig->WRVC2D               = 1;
  MemConfig->RDVC2D               = 1;
  MemConfig->LCT                  = 1;
  MemConfig->RTL                  = 1;
  MemConfig->TAT                  = 1;
  MemConfig->RMT                  = 0;
  MemConfig->MEMTST               = 0;
  MemConfig->DIMMODTT1D           = 0;
  MemConfig->WRSRT                = 0;
  MemConfig->DIMMRONT             = 1;
  MemConfig->ALIASCHK             = 1;
  MemConfig->RCVENC1D             = 1;
  MemConfig->RMC                  = 1;

  MemConfig->RemapEnable          = TRUE;
  MemConfig->RmtBdatEnable        = FALSE;
  MemConfig->MrcTimeMeasure       = FALSE;
  MemConfig->MrcFastBoot          = TRUE;
  MemConfig->DDR3Voltage          = 0;
  MemConfig->DDR3VoltageWaitTime  = 0;
  MemConfig->RefClk               = 0;
  MemConfig->Ratio                = 0;
  MemConfig->BClkFrequency        = 100 * 1000 * 1000;
  MemConfig->MaxRttWr             = 0;
  ///
  /// MrcUltPoSafeConfig
  /// 1 to enable, 0 to disable
  ///
  MemConfig->MrcUltPoSafeConfig   = 0;

  if (CpuFamilyId == EnumCpuHswUlt) {
    ///
    /// Interleaving mode of DQ/DQS pins - depends on board routing
    ///
    MemConfig->DqPinsInterleaved    = FALSE;
  }

  SaPlatformPolicyPpi->MemConfig  = MemConfig;

  ///
  /// Initialize the PciExpress Configuration
  ///
  PcieConfig->DmiVc1          = 0;
  PcieConfig->DmiVcp          = 1;
  PcieConfig->DmiVcm          = 1;
  PcieConfig->DmiGen2         = 1;
  PcieConfig->AlwaysEnablePeg = 0;
  for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
    PcieConfig->PegGenx[Index] = 0;
  }

  for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
    PcieConfig->PowerDownUnusedBundles[Index] = 0xFF;
  }

  PcieConfig->PegGen3Equalization       = 1;
  PcieConfig->PegSamplerCalibrate       = 0;
  PcieConfig->PegSwingControl           = 2;
  PcieConfig->PegComplianceTestingMode  = 0;

  ///
  /// PEG Gen3 Preset Search:                          0 = Disabled, 1 = Enabled (default)
  /// PEG Gen3 Force Preset Search (always re-search): 0 = Disabled (default), 1 = Enabled
  /// PEG Gen3 Preset Search Dwell Time:               400 usec
  /// PEG Gen3 Preset Search Timing Margin Steps:      2
  /// PEG Gen3 Preset Search Timing Start Margin:      15
  /// PEG Gen3 Preset Search Voltage Margin Steps:     2
  /// PEG Gen3 Preset Search Voltage Start Margin:     20
  /// PEG Gen3 Preset Search Favor Timing:             0 = Timing + Voltage (default), 1 = Timing only
  /// PEG Gen3 Preset Search Error Target:             4
  ///
  PcieConfig->PegGen3PresetSearch                   = 1;
  PcieConfig->PegGen3ForcePresetSearch              = 0;
  PcieConfig->PegGen3PresetSearchDwellTime          = STALL_ONE_MILLI_SECOND;
  PcieConfig->PegGen3PresetSearchStartMargin        = 15;
  PcieConfig->PegGen3PresetSearchVoltageStartMargin = 20;
  PcieConfig->PegGen3PresetSearchErrorTarget        = 1;

  for (Index = 0; Index < SA_PEG_MAX_LANE; Index++) {
    PcieConfig->Gen3RootPortPreset[Index] = 8;
    PcieConfig->Gen3EndPointPreset[Index] = 7;
    PcieConfig->Gen3EndPointHint[Index]   = 2;
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
  PcieConfig->InitPcieAspmAfterOprom = FALSE;
  PcieConfig->SaIotrapSmiAddress     = SA_IOTRAP_SMI_ADDRESS;

  ///
  /// Parameters for PCIe Gen3 device reset
  /// Note: Refer to the Platform Design Guide (PDG) for additional information about this GPIO.
  ///
  PegGpioData->GpioSupport = TRUE;
  if (PegGpioData->GpioSupport) {
    PegGpioData->SaPegReset = (SA_GPIO_INFO *) AllocatePool (sizeof (SA_GPIO_INFO));
    ASSERT (PegGpioData->SaPegReset != NULL);
    if (PegGpioData->SaPegReset == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    ///
    /// PEG Reset: GPIO 50, Active Low (Mobile PDG)
    ///
    PegGpioData->SaPegReset->Value  = 50;
    PegGpioData->SaPegReset->Active = 0;
    PcieConfig->PegGpioData         = PegGpioData;
  }

  ///
  /// Enable/Disable RxCEM Loop back
  /// 1=Enable, 0=Disable (default)
  /// When enabled, Lane for loop back should be selected (0 ~ 15 and default is Lane 0)
  ///
  PcieConfig->RxCEMLoopback     = 0;
  PcieConfig->RxCEMLoopbackLane = 0;

  ///
  /// Gen3 RxCTLE peaking default is 8
  ///
  for (Index = 0; Index < SA_PEG_MAX_BUNDLE; Index++) {
    PcieConfig->Gen3RxCtleP[Index] = 8;
  }

  ///
  /// Initialize the SA PEG Data pointer for saved preset search results
  ///
  PcieConfig->PegDataPtr = NULL;

  SaPlatformPolicyPpi->PcieConfig = PcieConfig;

  ///
  /// Initialize the Overclocking Configuration
  ///
  OcConfig->GtVoltageOffset     = 0;
  OcConfig->GtVoltageOverride   = 0;
  OcConfig->GtExtraTurboVoltage = 0;
  OcConfig->GtMaxOcTurboRatio   = 0;
  OcConfig->SaVoltageOffset     = 0;
  OcConfig->GtVoltageMode       = 0;
  OcConfig->OcSupport           = 0;
  OcConfig->IoaVoltageOffset    = 0;
  OcConfig->IodVoltageOffset    = 0;

  SaPlatformPolicyPpi->OcConfig = OcConfig;


#ifdef SG_SUPPORT
  ///
  /// Initialize the Switchable Graphics Configuration
  ///
  ///
  /// Switchable Graphics mode set as MUXLESS (By default)
  ///
  PlatformData->SgMode = SgModeMuxless;
  PlatformData->SgSubSystemId = 0x2112;

  SaPlatformPolicyPpi->PlatformData = PlatformData;

  ///
  /// Configure below based on the OEM platfrom design
  /// Switchable Graphics GPIO support - 1=Supported, 0=Not Supported
  ///
  SgGpioData->GpioSupport = TRUE;

  if (SgGpioData->GpioSupport) {
    ///
    /// Initialzie the GPIO Configuration
    ///
    ///
    /// dGPU PWROK GPIO assigned
    ///
    SgGpioData->SgDgpuPwrOK = (SA_GPIO_INFO *) AllocatePool (sizeof (SA_GPIO_INFO));
    ASSERT (SgGpioData->SgDgpuPwrOK != NULL);
    if (SgGpioData->SgDgpuPwrOK == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    SgGpioData->SgDgpuPwrOK->Value = 17;
    ///
    /// dGPU PWROK Active High
    ///
    SgGpioData->SgDgpuPwrOK->Active = 1;

    ///
    /// dGPU HLD RST GPIO assigned
    ///
    SgGpioData->SgDgpuHoldRst = (SA_GPIO_INFO *) AllocatePool (sizeof (SA_GPIO_INFO));
    ASSERT (SgGpioData->SgDgpuHoldRst != NULL);
    if (SgGpioData->SgDgpuHoldRst == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    SgGpioData->SgDgpuHoldRst->Value = 50;
    ///
    /// dGPU HLD RST Active Low
    ///
    SgGpioData->SgDgpuHoldRst->Active = 0;

    if (CpuFamilyId == EnumCpuHswUlt) {
      SgGpioData->SgDgpuHoldRst->Value = 48;
	}

    ///
    /// dGPU PWR Enable GPIO assigned
    ///
    SgGpioData->SgDgpuPwrEnable = (SA_GPIO_INFO *) AllocatePool (sizeof (SA_GPIO_INFO));
    ASSERT (SgGpioData->SgDgpuPwrEnable != NULL);
    if (SgGpioData->SgDgpuPwrEnable == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    SgGpioData->SgDgpuPwrEnable->Value = 54;
    ///
    /// dGPU PWR Enable Active Low
    ///
    SgGpioData->SgDgpuPwrEnable->Active = 0;

    if (CpuFamilyId == EnumCpuHswUlt) {
      SgGpioData->SgDgpuPwrEnable->Value = 84;
	}

    ///
    /// dGPU_PRSNT# GPIO assigned
    ///
    SgGpioData->SgDgpuPrsnt = (SA_GPIO_INFO *) AllocatePool (sizeof (SA_GPIO_INFO));
    ASSERT (SgGpioData->SgDgpuPrsnt != NULL);
    if (SgGpioData->SgDgpuPrsnt == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    SgGpioData->SgDgpuPrsnt->Value = 67;
    ///
    /// dGPU_PRSNT# Active Low
    ///
    SgGpioData->SgDgpuPrsnt->Active = 0;

    SaPlatformPolicyPpi->SgGpioData = SgGpioData;
  }
#endif

  ///
  /// Initialize the DataPtr for S3 resume
  ///
  SaPlatformPolicyPpi->S3DataPtr = NULL;

  UpdatePeiSaPlatformPolicy (PeiServices, SaPlatformPolicyPpi);

  ///
  /// Install SA Platform Policy PPI
  ///
  Status = (**PeiServices).InstallPpi (PeiServices, SaPlatformPolicyPpiDesc);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
