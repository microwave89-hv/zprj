/** @file
  This file is SampleCode for Intel CPU PEI Platform Policy initialization.

@copyright
  Copyright (c) 2010 - 2014 Intel Corporation. All rights reserved
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
#include "CpuPolicyInitPei.h"

//(AMI_CHG+)>
VOID CallPeiCpuPolicyInitList(
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN OUT PEI_CPU_PLATFORM_POLICY_PPI  *PeiCpuPolicyPpi);
//<(AMI_CHG+)
/**
  This PEIM performs CPU PEI Platform Policy initialization.

  @param[in] FfsHeader               Pointer to Firmware File System file header.
  @param[in] PeiServices             General purpose services available to every PEIM.

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI ERRORS              The PPI is not successfully installed.
**/
EFI_STATUS
EFIAPI
CpuPolicyInitPeiEntryPoint (
  IN EFI_FFS_FILE_HEADER *FfsHeader,
  IN EFI_PEI_SERVICES    **PeiServices
  )
{
  EFI_STATUS                  Status;
  EFI_PEI_PPI_DESCRIPTOR      *CpuPlatformPolicyPpiDesc;
  PEI_CPU_PLATFORM_POLICY_PPI *CpuPlatformPolicyPpi;
  CPU_CONFIG_PPI              *CpuConfig;
  SECURITY_CONFIG_PPI         *SecurityConfig;
  PFAT_CONFIG                 *PfatConfig;
  POWER_MGMT_CONFIG_PPI       *PowerMgmtConfig;
  OVERCLOCKING_CONFIG_PPI     *OcConfig;
  BOOT_GUARD_CONFIG           *BootGuardConfig;
#if defined(TXT_SUPPORT_FLAG) && (TXT_SUPPORT_FLAG == 1)
  TXT_CONFIG *TxtConfig;
#endif
  UINT8 PlatIdStr[] = "SHARK BAY";

  ///
  /// Allocate memory for the CPU Policy Ppi and Descriptor
  ///
  Status = ((*PeiServices)->AllocatePool)(PeiServices, sizeof (EFI_PEI_PPI_DESCRIPTOR), &CpuPlatformPolicyPpiDesc);
  ASSERT_EFI_ERROR (Status);

  Status = ((*PeiServices)->AllocatePool)(PeiServices, sizeof (PEI_CPU_PLATFORM_POLICY_PPI), &CpuPlatformPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = ((*PeiServices)->AllocatePool)(PeiServices, sizeof (CPU_CONFIG_PPI), &CpuConfig);
  ASSERT_EFI_ERROR (Status);

  Status = ((*PeiServices)->AllocatePool)(PeiServices, sizeof (SECURITY_CONFIG_PPI), &SecurityConfig);
  ASSERT_EFI_ERROR (Status);

  Status = ((*PeiServices)->AllocatePool)(PeiServices, sizeof (PFAT_CONFIG), &PfatConfig);
  ASSERT_EFI_ERROR (Status);

  Status = ((*PeiServices)->AllocatePool)(PeiServices, sizeof (POWER_MGMT_CONFIG_PPI), &PowerMgmtConfig);
  ASSERT_EFI_ERROR (Status);

  Status = ((*PeiServices)->AllocatePool)(PeiServices, sizeof (OVERCLOCKING_CONFIG_PPI), &OcConfig);
  ASSERT_EFI_ERROR (Status);

#if defined(TXT_SUPPORT_FLAG) && (TXT_SUPPORT_FLAG == 1)
  Status = ((*PeiServices)->AllocatePool)(PeiServices, sizeof (TXT_CONFIG), &TxtConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  Status = ((*PeiServices)->AllocatePool) (PeiServices, sizeof (BOOT_GUARD_CONFIG), &BootGuardConfig);
  ASSERT_EFI_ERROR (Status);

  CpuPlatformPolicyPpi->Revision                    = PEI_CPU_PLATFORM_POLICY_PPI_REVISION_8;
  CpuPlatformPolicyPpi->CpuConfig                   = CpuConfig;
  CpuPlatformPolicyPpi->SecurityConfig              = SecurityConfig;
  CpuPlatformPolicyPpi->SecurityConfig->PfatConfig  = PfatConfig;
  CpuPlatformPolicyPpi->PowerMgmtConfig             = PowerMgmtConfig;
  CpuPlatformPolicyPpi->OverclockingConfig          = OcConfig;
  CpuPlatformPolicyPpi->CpuPlatformPpiPtr           = (UINTN) CpuPlatformPolicyPpi;

#if defined(TXT_SUPPORT_FLAG) && (TXT_SUPPORT_FLAG == 1)
  CpuPlatformPolicyPpi->SecurityConfig->TxtConfig = TxtConfig;
#else
  CpuPlatformPolicyPpi->SecurityConfig->TxtConfig = NULL;
#endif

  CpuPlatformPolicyPpi->SecurityConfig->BootGuardConfig = BootGuardConfig;
    
  CpuConfig->CpuRatioOverride     = CPU_FEATURE_DISABLE;
  CpuConfig->CpuRatio             = 63;
  CpuConfig->CpuMaxNonTurboRatio  = 63;
  CpuConfig->BistOnReset          = CPU_FEATURE_DISABLE;
  CpuConfig->HyperThreading       = CPU_FEATURE_ENABLE;
  CpuConfig->VmxEnable            = CPU_FEATURE_ENABLE;
  CpuConfig->ActiveCoreCount      = 0;

  ///
  /// If CpuConfig->Pfat is set to ENABLE '1' then
  ///   PlatformData->SmmBwp (found in PchPolicyInitPei.c file) has to be set to ENABLE '1'
  /// This is a PFAT Security requirement that needs to be addressed
  /// If CpuConfig->Pfat is set to DISABLE '0' then
  ///   PlatformData->SmmBwp (found in PchPolicyInitPei.c file) value don't care, it can be
  ///   set to either ENABLE '1' or DISABLE '0' based on customer implementation
  ///
  CpuConfig->Pfat = CPU_FEATURE_DISABLE;
  ZeroMem (&PfatConfig->Ppdt, sizeof (PPDT));
  PfatConfig->Ppdt.PpdtMajVer             = PPDT_MAJOR_VERSION;
  PfatConfig->Ppdt.PpdtMinVer             = PPDT_MINOR_VERSION;
  CopyMem (&PfatConfig->Ppdt.PlatId[0], &PlatIdStr[0], sizeof (PlatIdStr));
  PfatConfig->Ppdt.PfatModSvn             = PFAT_SVN;
  PfatConfig->Ppdt.BiosSvn                = 0x01380000;
  PfatConfig->Ppdt.ExecLim                = 0;
  PfatConfig->Ppdt.PlatAttr               = 0;
  PfatConfig->Ppdt.LastSfam               = MIN_SFAM_COUNT - 1;
  if (PfatConfig->Ppdt.LastSfam > (MAX_SFAM_COUNT - 1)) {
    PfatConfig->Ppdt.LastSfam             = MAX_SFAM_COUNT - 1;
  }
  ///
  /// SfamData [LastSfam + 1]
  ///
  PfatConfig->Ppdt.SfamData[0].FirstByte  = 0x00580000;
  PfatConfig->Ppdt.SfamData[0].LastByte   = 0x0058FFFF;
  PfatConfig->Ppdt.PpdtSize               = (sizeof (PPDT) - sizeof (PfatConfig->Ppdt.SfamData) + ((PfatConfig->Ppdt.LastSfam + 1) * sizeof (SFAM_DATA)));
  PfatConfig->PpdtHash[0]  = 0xae7295370672663c;
  PfatConfig->PpdtHash[1]  = 0x220375c996d23a36;
  PfatConfig->PpdtHash[2]  = 0x73aaea0f2afded9d;
  PfatConfig->PpdtHash[3]  = 0x707193b768a0829e;
  ZeroMem (&PfatConfig->PupHeader, sizeof (PUP_HEADER));
  PfatConfig->PupHeader.Version         = PUP_HDR_VERSION;
  CopyMem (&PfatConfig->PupHeader.PlatId[0], &PlatIdStr[0], sizeof (PlatIdStr));
  PfatConfig->PupHeader.PkgAttributes   = 0;
  PfatConfig->PupHeader.PslMajorVer     = PSL_MAJOR_VERSION;
  PfatConfig->PupHeader.PslMinorVer     = PSL_MINOR_VERSION;
  PfatConfig->PupHeader.BiosSvn         = PfatConfig->Ppdt.BiosSvn;
  PfatConfig->PupHeader.EcSvn           = 0;
  PfatConfig->PupHeader.VendorSpecific  = 0x808655AA;
  ZeroMem (&PfatConfig->PfatLog, sizeof (PFAT_LOG));
  PfatConfig->PfatLog.Version         = PFAT_LOG_VERSION;
  PfatConfig->PfatLog.LastPage        = 0;
  if (PfatConfig->PfatLog.LastPage > (MAX_PFAT_LOG_PAGE - 1)) {
    PfatConfig->PfatLog.LastPage      = MAX_PFAT_LOG_PAGE - 1;
  }
  PfatConfig->PfatLog.LoggingOptions  = 0;
  PfatConfig->NumSpiComponents  = 2;
  PfatConfig->ComponentSize[0]  = EnumSpiCompSize8MB;
  PfatConfig->ComponentSize[1]  = EnumSpiCompSize8MB;
  PfatConfig->PfatMemSize       = 0x05;

  CpuConfig->MlcStreamerPrefetcher        = CPU_FEATURE_ENABLE;
  CpuConfig->MlcSpatialPrefetcher         = CPU_FEATURE_ENABLE;

  PowerMgmtConfig->RatioLimit[0]          = 0;
  PowerMgmtConfig->RatioLimit[1]          = 0;
  PowerMgmtConfig->RatioLimit[2]          = 0;
  PowerMgmtConfig->RatioLimit[3]          = 0;
  PowerMgmtConfig->TccActivationOffset    = 0;
  PowerMgmtConfig->VrCurrentLimit         = VR_CURRENT_DEFAULT;
  PowerMgmtConfig->VrCurrentLimitLock     = CPU_FEATURE_DISABLE;
  PowerMgmtConfig->Xe                     = CPU_FEATURE_DISABLE;
  PowerMgmtConfig->BootInLfm              = CPU_FEATURE_DISABLE;
  ///
  /// VrMiscIoutSlope      = 0x200 default
  /// VrMiscIoutOffsetSign = 0 means it's positive offset. 1= negative offset
  /// VrMiscIoutOffset     = 0 means it's 0%, 625 means 6.25% (range is +6.25% ~ -6.25%)
  ///
  PowerMgmtConfig->VrMiscIoutSlope        = 0x200;
  PowerMgmtConfig->VrMiscIoutOffsetSign   = 0;
  PowerMgmtConfig->VrMiscIoutOffset       = 0;

  PowerMgmtConfig->VrMiscMinVid                = V_MSR_VR_MISC_CONFIG_MIN_VID_DEFAULT;
  PowerMgmtConfig->VrMiscIdleExitRampRate      = CPU_FEATURE_ENABLE;
  PowerMgmtConfig->VrMiscIdleEntryRampRate     = CPU_FEATURE_DISABLE;
  PowerMgmtConfig->VrMiscIdleEntryDecayEnable  = CPU_FEATURE_ENABLE;
  if (GetCpuFamily() == EnumCpuHswUlt) {
    PowerMgmtConfig->VrMiscSlowSlewRateConfig  = V_MSR_VR_MISC_CONFIG_SLOW_SLEW_RATE_CONFIG_DEFAULT;
    PowerMgmtConfig->VrMisc2FastRampVoltage    = V_MSR_VR_MISC_CONFIG2_FAST_RAMP_VOLTAGE_DEFAULT;
    PowerMgmtConfig->VrMisc2MinC8Voltage       = V_MSR_VR_MISC_CONFIG2_MIN_C8_VOLTAGE_DEFAULT;
    PowerMgmtConfig->VrPSI4enable              = CPU_FEATURE_ENABLE;
  }
  PowerMgmtConfig->Psi1Threshold        = PSI1_THRESHOLD_DEFAULT;
  PowerMgmtConfig->Psi2Threshold        = PSI2_THRESHOLD_DEFAULT;
  PowerMgmtConfig->Psi3Threshold        = PSI3_THRESHOLD_DEFAULT;

  PowerMgmtConfig->FivrSscEnable        = 1;
  PowerMgmtConfig->FivrSscPercent       = 62;

  ///
  /// Initiate TxT policy
  ///
#if defined(TXT_SUPPORT_FLAG) && (TXT_SUPPORT_FLAG == 1)
  ZeroMem (TxtConfig, sizeof (TXT_CONFIG));
  CpuConfig->Txt                = 0;
  TxtConfig->SinitMemorySize    = TXT_SINIT_MEMORY_SIZE;
  TxtConfig->TxtHeapMemorySize  = TXT_HEAP_MEMORY_SIZE;
  TxtConfig->TxtDprMemoryBase   = 0;
  TxtConfig->TxtDprMemorySize   = 0;
  TxtConfig->BiosAcmBase        = 0;
  TxtConfig->BiosAcmSize        = 0;
  TxtConfig->McuUpdateDataAddr  = 0;
  TxtConfig->TgaSize            = TXT_TGA_MEMORY_SIZE;
  TxtConfig->TxtLcpPdBase       = TXT_LCP_PD_BASE;
  TxtConfig->TxtLcpPdSize       = TXT_LCP_PD_SIZE;
#endif
  ///
  /// Initialize Overclocking Data
  ///
  OcConfig->CoreVoltageOffset       = 0;
  OcConfig->CoreVoltageOverride     = 0;
  OcConfig->CoreExtraTurboVoltage   = 0;
  OcConfig->CoreMaxOcTurboRatio     = 0;
  OcConfig->ClrVoltageOffset        = 0;
  OcConfig->ClrVoltageOverride      = 0;
  OcConfig->ClrExtraTurboVoltage    = 0;
  OcConfig->ClrMaxOcTurboRatio      = 0;
  OcConfig->SvidVoltageOverride     = 0;
  OcConfig->SvidEnable              = 0;
  OcConfig->FivrFaultsEnable        = 0;
  OcConfig->FivrEfficiencyEnable    = 0;
  OcConfig->CoreVoltageMode         = 0;
  OcConfig->ClrVoltageMode          = 0;
  OcConfig->OcSupport               = 0;
  OcConfig->BitReserved             = 0;

  //
  // Initialize Boot Guard data
  //
  BootGuardConfig->TpmType              = TpmTypeMax;
  BootGuardConfig->BypassTpmInit        = FALSE;
  BootGuardConfig->MeasuredBoot         = FALSE;
  BootGuardConfig->BootGuardSupport     = FALSE;
  BootGuardConfig->DisconnectAllTpms    = FALSE;
  BootGuardConfig->ByPassTpmEventLog    = FALSE;

   //AMI_CHG
  //UpdatePeiCpuPlatformPolicy (PeiServices, CpuPlatformPolicyPpi); //(AMI_CHG)  
  CallPeiCpuPolicyInitList(PeiServices, CpuPlatformPolicyPpi);   // (AMI_CHG+)  

  ///
  /// Update the CPU Policy Ppi Descriptor
  ///
  CpuPlatformPolicyPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  CpuPlatformPolicyPpiDesc->Guid  = &gPeiCpuPlatformPolicyPpiGuid;
  CpuPlatformPolicyPpiDesc->Ppi   = CpuPlatformPolicyPpi;

  ///
  /// Install the CPU PEI Platform Policy PPI
  ///
  Status = (**PeiServices).InstallPpi (PeiServices, CpuPlatformPolicyPpiDesc);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
