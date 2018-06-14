/** @file
  This file is SampleCode for Intel CPU DXE Platform Policy initialzation.

@copyright
  Copyright (c) 2009 - 2013 Intel Corporation. All rights reserved
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
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"

#if (EFI_SPECIFICATION_VERSION >= 0x2000A)
#include EFI_PROTOCOL_DEFINITION (HiiDatabase)
#else
#include EFI_PROTOCOL_DEFINITION (Hii)
#endif
#include EFI_PROTOCOL_DEFINITION (CpuInfo)
#include "CpuPolicyInitDxe.h"
#if (EFI_SPECIFICATION_VERSION >= 0x2000A)
#include "UefiIfrLibrary.h"
#endif

//-#include "FlashMap.h"
#include "CpuPlatformLib.h"

#define SMM_FROM_SMBASE_DRIVER            0x55
#define SW_SMI_FROM_SMMBASE               SMM_FROM_SMBASE_DRIVER

#define PLATFORM_CPU_MAX_FSB_FREQUENCY    1066
#endif

//(AMI_CHG+)>
VOID CallDxeCpuPolicyInitList(
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN OUT DXE_CPU_PLATFORM_POLICY_PROTOCOL       *mCpuPolicyDataPtr);
//<(AMI_CHG+)
EFI_EXP_BASE10_DATA mCoreFrequencyList[] = {
  { 0, 0}, ///< 0 Means "Auto", also, the first is the default.
  {-1, 0} ///< End marker
};

EFI_EXP_BASE10_DATA mFsbFrequencyList[] = {
  { 0, 0}, ///< 0 Means "Auto", also, the first is the default.
  {-1, 0} ///< End marker
};

DXE_CPU_PLATFORM_POLICY_PROTOCOL mCpuPolicyData  = { 0 };
CPU_CONFIG                       mCpuConfig      = { 0 };
POWER_MGMT_CONFIG                mCpuPmConfig    = { 0 };
SECURITY_CONFIG                  mSecurityConfig = { 0 };
#if defined(TXT_SUPPORT_FLAG) && (TXT_SUPPORT_FLAG == 1)
TXT_FUNCTION_CONFIG mTxtFunctionConfig = { 0 };
#endif

///
/// Function implementations
///
/**
  Platform function to get MAX CPU count

  @param[in] This               - platform policy protocol
  @param[in] MaxThreadsPerCore  - variable that will store MaxThreadsPerCore
  @param[in] MaxCoresPerDie     - variable that will store MaxCoresPerDie
  @param[in] MaxDiesPerPackage  - variable that will store MaxDiesPerPackage
  @param[in] MaxPackages        - variable that will store MaxPackages

  @retval EFI_SUCCESS           - Always return success
**/
EFI_STATUS
EFIAPI
PlatformCpuGetMaxCount (
  IN DXE_CPU_PLATFORM_POLICY_PROTOCOL *This,
  OUT UINT32                          *MaxThreadsPerCore,
  OUT UINT32                          *MaxCoresPerDie,
  OUT UINT32                          *MaxDiesPerPackage,
  OUT UINT32                          *MaxPackages
  )
{
  *MaxThreadsPerCore  = 2;
  *MaxCoresPerDie     = 4;
  *MaxDiesPerPackage  = 1;
  *MaxPackages        = 1;

  return EFI_SUCCESS;
}

/**
  Get CPU information

  @param[in] This                - platform policy protocol
  @param[in] Location            - structure that describe CPU location information
  @param[in] PlatformCpuInfo     - structure that will be updated for platform CPU information

  @retval EFI_INVALID_PARAMETER  - PlatformCpuInfo is NULL
  @retval EFI_SUCCESS            - platform CPU info structure has been updated
**/
EFI_STATUS
EFIAPI
PlatformCpuGetCpuInfo (
  IN DXE_CPU_PLATFORM_POLICY_PROTOCOL *This,
  IN CPU_PHYSICAL_LOCATION            *Location,
  IN OUT PLATFORM_CPU_INFORMATION     *PlatformCpuInfo
  )
{
#if (EFI_SPECIFICATION_VERSION < 0x2000A)
  EFI_HII_PROTOCOL *Hii;
#endif
  STRING_REF SocketNameToken;
  STRING_REF FillByOemToken;
  EFI_STATUS Status;
  UINT64     MsrValue;
  UINT8      CpuSku;

  SocketNameToken = 0;
  FillByOemToken  = 0;

  ///
  /// For Processor SocketName definition.
  ///
  if (PlatformCpuInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

#if (EFI_SPECIFICATION_VERSION >= 0x2000A)
  Status = IfrLibNewString (PlatformCpuInfo->StringHandle, &SocketNameToken, L"U3E1");
  ASSERT_EFI_ERROR (Status);

  Status = IfrLibNewString (PlatformCpuInfo->StringHandle, &FillByOemToken, L"To Be Filled By O.E.M.");
  ASSERT_EFI_ERROR (Status);
#else
  Status = gBS->LocateProtocol (
                  &gEfiHiiProtocolGuid,
                  NULL,
                  (VOID **) &Hii
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Hii->NewString (
          Hii,
          NULL,
          PlatformCpuInfo->StringHandle,
          &SocketNameToken,
          L"U3E1"
          );

  Hii->NewString (
          Hii,
          NULL,
          PlatformCpuInfo->StringHandle,
          &FillByOemToken,
          L"To Be Filled By O.E.M."
          );
#endif

  PlatformCpuInfo->ApicID           = Location->Thread;
  PlatformCpuInfo->ReferenceString  = 0;
  CpuSku = GetCpuSku ();
  switch (CpuSku) {
    case EnumCpuTrad:
      PlatformCpuInfo->SocketType = 0x2d; // @todo EfiProcessorSocketLGA1150, pending updated SMBIOS spec release
      break;

    case EnumCpuUlt:
      PlatformCpuInfo->SocketType = 0x2e; // @todo EfiProcessorSocketBGA1168, pending updated SMBIOS spec release
      break;

    default:
      PlatformCpuInfo->SocketType = EfiProcessorSocketOther;
      break;
  }
  PlatformCpuInfo->SocketName                 = SocketNameToken;

  MsrValue = AsmReadMsr64 (MSR_PLATFORM_INFO);
  PlatformCpuInfo->MaxCoreFrequency.Value     = (100 * (((UINT32) MsrValue >> N_PLATFORM_INFO_MAX_RATIO) & B_PLATFORM_INFO_RATIO_MASK));
  PlatformCpuInfo->MaxCoreFrequency.Exponent  = 6;

  PlatformCpuInfo->MaxFsbFrequency.Value      = PLATFORM_CPU_MAX_FSB_FREQUENCY;
  PlatformCpuInfo->MaxFsbFrequency.Exponent   = 6;

  PlatformCpuInfo->PlatformCoreFrequencyList  = mCoreFrequencyList;
  PlatformCpuInfo->PlatformFsbFrequencyList   = mFsbFrequencyList;

  PlatformCpuInfo->AssetTag                   = FillByOemToken;
  PlatformCpuInfo->SerialNumber               = FillByOemToken;
  PlatformCpuInfo->PartNumber                 = FillByOemToken;

  return EFI_SUCCESS;
}

/**
  Get the microcode patch.

  @param[in] This           - Driver context.
  @param[in] MicrocodeData  - Retrieved image of the microcode.

  @retval EFI_SUCCESS       - Image found.
  @retval EFI_NOT_FOUND     - image not found.
**/
EFI_STATUS
PlatformCpuRetrieveMicrocode (
  IN DXE_CPU_PLATFORM_POLICY_PROTOCOL *This,
  OUT UINT8                           **MicrocodeData
  )
{
  /*EFI_CPU_MICROCODE_HEADER  *Microcode;
  UINTN                     MicrocodeStart;
  UINTN                     MicrocodeEnd;
  UINTN                     TotalSize;

  ///
  /// Microcode binary in SEC
  ///
  MicrocodeStart = FLASH_REGION_MICROCODE_BASE +
    ((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) FLASH_REGION_MICROCODE_BASE)->HeaderLength +
    sizeof (EFI_FFS_FILE_HEADER);

  MicrocodeEnd = FLASH_REGION_MICROCODE_BASE + FLASH_REGION_MICROCODE_SIZE;

  if (*MicrocodeData == NULL) {
    *MicrocodeData = (UINT8 *) (UINTN) MicrocodeStart;
  } else {
    if (*MicrocodeData < (UINT8 *) (UINTN) MicrocodeStart) {
      return EFI_NOT_FOUND;
    }

    TotalSize = (UINTN) (((EFI_CPU_MICROCODE_HEADER *) *MicrocodeData)->TotalSize);
    if (TotalSize == 0) {
      TotalSize = 2048;
    }
    //
    // Add alignment check - begin
    //
    if ((TotalSize & 0x7FF) != 0) {
      TotalSize = (TotalSize & 0xFFFFF800) + 0x800;
    }
    //
    // Add alignment check - end
    //

    *MicrocodeData += TotalSize;

    Microcode = (EFI_CPU_MICROCODE_HEADER *) *MicrocodeData;
    if (*MicrocodeData >= (UINT8 *) (UINTN) (MicrocodeEnd) || Microcode->TotalSize == (UINT32) -1) {
      return EFI_NOT_FOUND;
    }

  }


  return EFI_SUCCESS;*/
  return EFI_NOT_FOUND;
}

/**
  Initilize Intel Cpu DXE Platform Policy

  @param[in] ImageHandle        Image handle of this driver.
  @param[in] SystemTable        Global system service table.

  @retval EFI_SUCCESS           Initialization complete.
  @exception EFI_UNSUPPORTED    The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR      Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
CpuPolicyInitDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS Status;
  CPU_FAMILY CpuFamilyId;

  CpuFamilyId = GetCpuFamily();

  mCpuPolicyData.Revision             = DXE_PLATFORM_CPU_POLICY_PROTOCOL_REVISION_7;
  mCpuPolicyData.CpuConfig            = &mCpuConfig;
  mCpuPolicyData.PowerMgmtConfig      = &mCpuPmConfig;
  mCpuPolicyData.SecurityConfig       = &mSecurityConfig;

  mCpuConfig.RetrieveMicrocode        = PlatformCpuRetrieveMicrocode;
  mCpuConfig.GetMaxCount              = PlatformCpuGetMaxCount;
  mCpuConfig.GetCpuInfo               = PlatformCpuGetCpuInfo;
  mSecurityConfig.TxtFunctionConfig   = NULL;
#ifdef TXT_SUPPORT_FLAG
  mSecurityConfig.TxtFunctionConfig   = &mTxtFunctionConfig;
#endif  // TXT_SUPPORT_FLAG
  mCpuConfig.SmmbaseSwSmiNumber       = SW_SMI_FROM_SMMBASE;

  mCpuConfig.HtState                  = CPU_FEATURE_ENABLE;
  mCpuConfig.LimitCpuidMaximumValue   = CPU_FEATURE_DISABLE;
  mCpuConfig.ExecuteDisableBit        = CPU_FEATURE_ENABLE;
  mCpuConfig.VmxEnable                = CPU_FEATURE_ENABLE;
  mCpuConfig.SmxEnable                = CPU_FEATURE_ENABLE;
  mCpuConfig.MachineCheckEnable       = CPU_FEATURE_ENABLE;
  mCpuConfig.MonitorMwaitEnable       = CPU_FEATURE_ENABLE;
  mCpuConfig.XapicEnable              = CPU_FEATURE_DISABLE;
  mCpuConfig.AesEnable                = CPU_FEATURE_ENABLE;
  mCpuConfig.DebugInterfaceEnable     = CPU_FEATURE_DISABLE;
  mCpuConfig.DebugInterfaceLockEnable = CPU_FEATURE_ENABLE;
  mCpuConfig.MlcStreamerPrefetcher    = CPU_FEATURE_ENABLE;
  mCpuConfig.MlcSpatialPrefetcher     = CPU_FEATURE_ENABLE;
  mCpuConfig.EnableDts                = CPU_FEATURE_DISABLE;
  mCpuConfig.BspSelection             = 0;
  mCpuConfig.ApIdleManner             = 1;
  mCpuConfig.ApHandoffManner          = 1;
  ///
  /// Virtual wire to A
  ///
  mCpuConfig.FviReport = 1;
  ///
  /// Default Enable FVI SMBIOS Report
  ///
  mCpuConfig.FviSmbiosType = 0xDD;
  ///
  /// Default SMBIOS Type 221
  ///
  /// Initialize Power Management Config
  /// Allocate and set Power Management policy structure to recommended defaults
  ///
  mCpuPmConfig.pFunctionEnables     = AllocateZeroPool (sizeof (PPM_FUNCTION_ENABLES));
  mCpuPmConfig.pCustomRatioTable    = AllocateZeroPool (sizeof (PPM_CUSTOM_RATIO_TABLE));
  mCpuPmConfig.pTurboSettings       = AllocateZeroPool (sizeof (PPM_TURBO_SETTINGS));
  mCpuPmConfig.pRatioLimit          = AllocateZeroPool ((sizeof (UINT8) * 4));
  mCpuPmConfig.pPpmLockEnables      = AllocateZeroPool (sizeof (PPM_LOCK_ENABLES));
  mCpuPmConfig.pCustomCtdpSettings  = AllocateZeroPool (sizeof (PPM_CUSTOM_CTDP));
  mCpuPmConfig.ThermalFuncEnables   = AllocateZeroPool (sizeof (THERM_FUNCTION_ENABLES));

  if ((mCpuPmConfig.pFunctionEnables == NULL) ||
      (mCpuPmConfig.pCustomRatioTable == NULL) ||
      (mCpuPmConfig.pTurboSettings == NULL) ||
      (mCpuPmConfig.pPpmLockEnables == NULL) ||
      (mCpuPmConfig.pCustomCtdpSettings == NULL) ||
      (mCpuPmConfig.ThermalFuncEnables == NULL)
      ) {
    return EFI_OUT_OF_RESOURCES;
  }

  mCpuPmConfig.pFunctionEnables->Eist                   = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->Cx                     = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->C1e                    = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->C3                     = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->C6                     = PPM_ENABLE;
  if (CpuFamilyId == EnumCpuHswUlt) {
    mCpuPmConfig.pFunctionEnables->C8                   = PPM_ENABLE;
    mCpuPmConfig.pFunctionEnables->C9                   = PPM_ENABLE;
    mCpuPmConfig.pFunctionEnables->C10                  = PPM_ENABLE;
  }
  mCpuPmConfig.pFunctionEnables->DeepCState             = DeepC7S;
  mCpuPmConfig.pFunctionEnables->C1AutoDemotion         = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->C3AutoDemotion         = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->C1UnDemotion           = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->C3UnDemotion           = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->PkgCStateDemotion      = PPM_DISABLE;
  mCpuPmConfig.pFunctionEnables->PkgCStateUnDemotion    = PPM_DISABLE;
  mCpuPmConfig.ThermalFuncEnables->BiProcHot            = PPM_ENABLE;
  mCpuPmConfig.ThermalFuncEnables->DisableProcHotOut    = PPM_DISABLE;
  mCpuPmConfig.ThermalFuncEnables->DisableVRThermalAlert= PPM_DISABLE;
  mCpuPmConfig.ThermalFuncEnables->ProcHotResponce      = PPM_DISABLE;
  mCpuPmConfig.ThermalFuncEnables->TStates              = PPM_DISABLE;
  mCpuPmConfig.pFunctionEnables->Xe                     = PPM_DISABLE;
  mCpuPmConfig.pFunctionEnables->TurboMode              = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->PowerLimit2            = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->EnergyEfficientPState  = PPM_ENABLE;
  mCpuPmConfig.pFunctionEnables->CStatePreWake          = PPM_ENABLE;
  mCpuPmConfig.ThermalFuncEnables->AutoThermalReporting   = PPM_ENABLE;

  mCpuPmConfig.pFunctionEnables->LongLatencyC6          = PPM_DISABLE;
  mCpuPmConfig.pFunctionEnables->LongLatencyC7          = PPM_ENABLE;
  mCpuPmConfig.ThermalFuncEnables->ThermalMonitor       = PPM_ENABLE;
  mCpuPmConfig.ThermalFuncEnables->Pl1ThermalControl    = 2; ///< AUTO
  mCpuPmConfig.ThermalFuncEnables->Pl1ThermalControlFloor.FloorIA   = Percent100;
  mCpuPmConfig.ThermalFuncEnables->Pl1ThermalControlFloor.FloorGT   = Percent100;
  mCpuPmConfig.ThermalFuncEnables->Pl1ThermalControlFloor.FloorPCH  = Percent100;
  mCpuPmConfig.pFunctionEnables->LakeTiny               = PPM_DISABLE;
  mCpuPmConfig.pFunctionEnables->TimedMwait             = PPM_DISABLE;

  mCpuPmConfig.CustomPowerUnit                          = PowerUnit125MilliWatts;
  mCpuPmConfig.pTurboSettings->PowerLimit1              = AUTO;
  mCpuPmConfig.pTurboSettings->PowerLimit2              = AUTO;
  mCpuPmConfig.pTurboSettings->PowerLimit1Time          = AUTO;
  mCpuPmConfig.pTurboSettings->PowerLimit3              = AUTO;
  mCpuPmConfig.pTurboSettings->PowerLimit3Time          = AUTO;
  mCpuPmConfig.pTurboSettings->PowerLimit3DutyCycle     = AUTO;
  mCpuPmConfig.pTurboSettings->PowerLimit3Lock          = PPM_ENABLE;
  mCpuPmConfig.pTurboSettings->ConfigTdpLevel           = 0;
  mCpuPmConfig.pTurboSettings->ConfigTdpLock            = PPM_DISABLE;
  mCpuPmConfig.pCustomCtdpSettings->ConfigTdpCustom     = PPM_DISABLE;

  mCpuPmConfig.pTurboSettings->TurboPowerLimitLock      = PPM_DISABLE;
  mCpuPmConfig.pTurboSettings->EnergyPolicy             = 0;

  mCpuPmConfig.pPpmLockEnables->PmgCstCfgCtrlLock       = PPM_ENABLE;
  mCpuPmConfig.pPpmLockEnables->OverclockingLock        = PPM_DISABLE;
  mCpuPmConfig.pPpmLockEnables->ProcHotLock             = PPM_DISABLE;
  mCpuPmConfig.S3RestoreMsrSwSmiNumber                  = SW_SMI_S3_RESTORE_MSR;
  mCpuPmConfig.PkgCStateLimit = PkgAuto;

  mCpuPmConfig.CstateLatencyControl0TimeUnit = TimeUnit1024ns;
  mCpuPmConfig.CstateLatencyControl1TimeUnit = TimeUnit1024ns;
  mCpuPmConfig.CstateLatencyControl2TimeUnit = TimeUnit1024ns;
  mCpuPmConfig.CstateLatencyControl0Irtl = C3_LATENCY;
  mCpuPmConfig.CstateLatencyControl1Irtl = C6_C7_SHORT_LATENCY;
  mCpuPmConfig.CstateLatencyControl2Irtl = C6_C7_LONG_LATENCY;
  if (CpuFamilyId == EnumCpuHswUlt) {
    mCpuPmConfig.CstateLatencyControl3TimeUnit = TimeUnit1024ns;
    mCpuPmConfig.CstateLatencyControl4TimeUnit = TimeUnit1024ns;
    mCpuPmConfig.CstateLatencyControl5TimeUnit = TimeUnit1024ns;
    mCpuPmConfig.CstateLatencyControl3Irtl = C8_LATENCY;
    mCpuPmConfig.CstateLatencyControl4Irtl = C9_LATENCY;
    //
    // If PS4 is disabled, program 2750us to MSR_C_STATE_LATENCY_CONTROL_5
    //
    mCpuPmConfig.CstateLatencyControl5Irtl = C10_LATENCY;
  }
  mCpuPmConfig.RfiFreqTunningOffsetIsNegative = 0;
  mCpuPmConfig.RfiFreqTunningOffset = 0;

  if (CpuFamilyId == EnumCpuHswUlt) {
    //
    // Calibrate 24MHz BCLK support; 0: NO_CALIBRATE, 1: PCODE_CALIBRATE, 2: BIOS_CALIBRATE (Default :1)
    //
    mCpuPmConfig.PcodeCalibration                   = 1;
    mCpuPmConfig.EnableRerunPcodeCalibration        = PPM_DISABLE;
  }
  ///
  /// TxT platform config initiate
  ///
#if defined(TXT_SUPPORT_FLAG) && (TXT_SUPPORT_FLAG == 1)
  mTxtFunctionConfig.ResetAux = 0;
#endif

  //AMI_REMOVE_TEMP_FOR_COMPILE
  //UpdateDxeCpuPlatformPolicy (&mCpuPolicyData);   //(AMI_CHG)
  CallDxeCpuPolicyInitList(SystemTable, &mCpuPolicyData);   // (AMI_CHG+)
  ///
  /// Install the DXE_CPU_PLATFORM_POLICY_PROTOCOL interface
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gDxeCpuPlatformPolicyProtocolGuid,
                  &mCpuPolicyData,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);
  return Status;
}
