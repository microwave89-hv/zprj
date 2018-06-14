/** @file
  This file is SampleCode for Intel PCH DXE Platform Policy initialzation.

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
#include "PchPolicyInitDxe.h"
#include "..\Common\PchPolicyInitCommon.h"

#define SW_SMI_BIOS_LOCK              0xA9
#define PCI_CLASS_NETWORK             0x02
#define PCI_CLASS_NETWORK_ETHERNET    0x00
#define PCI_CLASS_NETWORK_OTHER       0x80

DXE_PCH_PLATFORM_POLICY_PROTOCOL  mPchPolicyData        = { 0 };
PCH_DEVICE_ENABLING               mPchDeviceEnabling    = { 0 };
PCH_USB_CONFIG                    mPchUsbConfig         = { 0 };
PCH_PCI_EXPRESS_CONFIG            mPchPciExpressConfig  = { 0 };
PCH_SATA_CONFIG                   mPchSataConfig        = { 0 };
PCH_AZALIA_CONFIG                 mPchAzaliaConfig      = { 0 };
PCH_SMBUS_CONFIG                  mPchSmbusConfig       = { 0 };
PCH_MISC_PM_CONFIG                mPchMiscPmConfig      = { 0 };
PCH_IO_APIC_CONFIG                mPchIoApicConfig      = { 0 };
PCH_DEFAULT_SVID_SID              mPchDefaultSvidSid    = { 0 };
PCH_LOCK_DOWN_CONFIG              mPchLockDownConfig    = { 0 };
PCH_THERMAL_CONFIG                mPchThermalConfig     = { 0 };
PCH_LPC_HPET_CONFIG               mPchHpetConfig        = { 0 };
PCH_LPC_SIRQ_CONFIG               mSerialIrqConfig      = { 0 };
PCH_DMI_CONFIG                    mPchDmiConfig         = { 0 };
PCH_PWR_OPT_CONFIG                mPchPwrOptConfig      = { 0 };
PCH_MISC_CONFIG                   mPchMiscConfig        = { 0 };
PCH_AUDIO_DSP_CONFIG              mAudioDspConfig       = { 0 };
PCH_SERIAL_IO_CONFIG              mSerialIoConfig      = { 0 };

UINT8 mSmbusRsvdAddresses[4] = {
  0xA0,
  0xA2,
  0xA4,
  0xA6
};

PCH_PCIE_DEVICE_ASPM_OVERRIDE mDevAspmOverride[] = {
  //
  // Intel PRO/Wireless
  //
  {0x8086, 0x422b, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x422c, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x4238, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x4239, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  //
  // Intel WiMAX/WiFi Link
  //
  {0x8086, 0x0082, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0085, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0083, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0084, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0086, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0087, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0088, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0089, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x008F, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0090, 0xff, 0xff, 0xff, PchPcieAspmL1, PchPcieL1L2Override, 0xFFFF, 0xFFFFFFFF},
  //
  // Intel Crane Peak WLAN NIC
  //
  {0x8086, 0x08AE, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x08AF, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Crane Peak w/BT WLAN NIC
  //
  {0x8086, 0x0896, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0897, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Kelsey Peak WiFi, WiMax
  //
  {0x8086, 0x0885, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0886, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 105
  //
  {0x8086, 0x0894, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0895, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 135
  //
  {0x8086, 0x0892, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0893, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 2200
  //
  {0x8086, 0x0890, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0891, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 2230
  //
  {0x8086, 0x0887, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x0888, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel Centrino Wireless-N 6235
  //
  {0x8086, 0x088E, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x088F, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel CampPeak 2 Wifi
  //
  {0x8086, 0x08B5, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  {0x8086, 0x08B6, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF},
  //
  // Intel WilkinsPeak 1 Wifi
  //
  {0x8086, 0x08B3, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2AndL1SubstatesOverride, 0x0154, 0x00000003},
  {0x8086, 0x08B3, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1SubstatesOverride,        0x0158, 0x00000003},
  {0x8086, 0x08B4, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2AndL1SubstatesOverride, 0x0154, 0x00000003},
  {0x8086, 0x08B4, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1SubstatesOverride,        0x0158, 0x00000003},
  //
  // Intel Wilkins Peak 2 Wifi
  //
  {0x8086, 0x08B1, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2AndL1SubstatesOverride, 0x0154, 0x00000003},
  {0x8086, 0x08B1, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1SubstatesOverride,        0x0158, 0x00000003},
  {0x8086, 0x08B2, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2AndL1SubstatesOverride, 0x0154, 0x00000003},
  {0x8086, 0x08B2, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1SubstatesOverride,        0x0158, 0x00000003},
  //
  // Intel Wilkins Peak PF Wifi
  //
  {0x8086, 0x08B0, 0xff, PCI_CLASS_NETWORK, PCI_CLASS_NETWORK_OTHER, PchPcieAspmL1,       PchPcieL1L2Override,               0xFFFF, 0xFFFFFFFF}

};

//
// Function implementations
//

/**
  Initilize Intel PCH DXE Platform Policy

  @param[in] ImageHandle          Image handle of this driver.
  @param[in] SystemTable          Global system service table.

  @retval EFI_SUCCESS             Initialization complete.
  @exception EFI_UNSUPPORTED      The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
PchPolicyInitDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_HANDLE  Handle;
  EFI_STATUS  Status;
  UINT8       PortIndex;
  UINTN       Index;
  PCH_SERIES  PchSeries;
  PchSeries = GetPchSeries();
  //
  // General intialization
  //
  mPchPolicyData.Revision             = DXE_PCH_PLATFORM_POLICY_PROTOCOL_REVISION_7;
  mPchPolicyData.BusNumber            = 0;

  mPchPolicyData.DeviceEnabling       = &mPchDeviceEnabling;
  mPchPolicyData.UsbConfig            = &mPchUsbConfig;
  mPchPolicyData.PciExpressConfig     = &mPchPciExpressConfig;
  mPchPolicyData.SataConfig           = &mPchSataConfig;
  mPchPolicyData.AzaliaConfig         = &mPchAzaliaConfig;
  mPchPolicyData.SmbusConfig          = &mPchSmbusConfig;
  mPchPolicyData.MiscPmConfig         = &mPchMiscPmConfig;
  mPchPolicyData.IoApicConfig         = &mPchIoApicConfig;
  mPchPolicyData.DefaultSvidSid       = &mPchDefaultSvidSid;
  mPchPolicyData.LockDownConfig       = &mPchLockDownConfig;
  mPchPolicyData.ThermalConfig        = &mPchThermalConfig;
  mPchPolicyData.HpetConfig           = &mPchHpetConfig;
  mPchPolicyData.SerialIrqConfig      = &mSerialIrqConfig;
  mPchPolicyData.DmiConfig            = &mPchDmiConfig;
  mPchPolicyData.PwrOptConfig         = &mPchPwrOptConfig;
  mPchPolicyData.MiscConfig           = &mPchMiscConfig;
  mPchPolicyData.AudioDspConfig       = &mAudioDspConfig;
  mPchPolicyData.SerialIoConfig       = &mSerialIoConfig;

  ///
  /// PCH BIOS Spec Rev 0.5.0 Section 3.6 Flash Security Recommendations,
  /// Intel strongly recommends that BIOS sets the BIOS Interface Lock Down bit. Enabling this bit
  /// will mitigate malicious software attempts to replace the system BIOS option ROM with its own code.
  /// We always enable this as a platform policy.
  ///
  mPchLockDownConfig.BiosInterface          = PCH_DEVICE_ENABLE;
  mPchLockDownConfig.GlobalSmi              = PCH_DEVICE_ENABLE;
  mPchLockDownConfig.GpioLockDown           = PCH_DEVICE_DISABLE;
  mPchLockDownConfig.RtcLock                = PCH_DEVICE_ENABLE;
  ///
  /// While BiosLock is enabled, BIOS can only be modified from SMM after ExitPmAuth.
  ///
  mPchLockDownConfig.BiosLock                 = PCH_DEVICE_DISABLE;
  ///
  /// If PchBiosLockIoTrapAddress is 0, BIOS will allocate available IO address with
  /// 256 byte range from GCD and pass it to PchBiosLockIoTrapAddress.
  ///
  mPchLockDownConfig.PchBiosLockIoTrapAddress = 0;
  ///
  /// Initialize policy to default values when variable isn't found.
  ///
  mPchDeviceEnabling.Lan                = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.Azalia             = 2;
  mPchDeviceEnabling.Sata               = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.Smbus              = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.PciClockRun        = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.Display            = 1;
  mPchDeviceEnabling.Crid               = PCH_DEVICE_DISABLE;
  mPchDeviceEnabling.SerialIoDma        = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.SerialIoI2c0       = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.SerialIoI2c1       = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.SerialIoSpi0       = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.SerialIoSpi1       = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.SerialIoUart0      = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.SerialIoUart1      = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.SerialIoSdio       = PCH_DEVICE_ENABLE;
  mPchDeviceEnabling.AudioDsp           = PCH_DEVICE_DISABLE;

  ///
  /// Init USB related setting
  ///
  InitPchUsbConfig (&mPchUsbConfig);

  ///
  /// PCI Express related settings from setup variable
  ///
  mPchPciExpressConfig.RootPortClockGating    = PCH_DEVICE_ENABLE;
  mPchPciExpressConfig.TempRootPortBusNumMin  = 2;
  mPchPciExpressConfig.TempRootPortBusNumMax  = 4;

  for (PortIndex = 0; PortIndex < GetPchMaxPciePortNum (); PortIndex++) {
    mPchPciExpressConfig.RootPort[PortIndex].Enable             = PCH_DEVICE_ENABLE;
    mPchPciExpressConfig.RootPort[PortIndex].FunctionNumber     = PortIndex;
    mPchPciExpressConfig.RootPort[PortIndex].PhysicalSlotNumber = PortIndex;
    mPchPciExpressConfig.RootPort[PortIndex].Aspm               = 4;
    mPchPciExpressConfig.RootPort[PortIndex].SlotImplemented    = 1;
    mPchPciExpressConfig.RootPort[PortIndex].L1Substates        = 3;

  }
  mPchPciExpressConfig.RootPort[7].HotPlug      = 1;
  mPchPciExpressConfig.NumOfDevAspmOverride     = sizeof (mDevAspmOverride) / sizeof (PCH_PCIE_DEVICE_ASPM_OVERRIDE);
  mPchPciExpressConfig.DevAspmOverride          = mDevAspmOverride;
  mPchPciExpressConfig.EnableSubDecode          = 0;
  mPchPciExpressConfig.PchPcieSbdePort          = 0;
  mPchPciExpressConfig.RootPortFunctionSwapping = 1;

  for (PortIndex = 0; PortIndex < GetPchMaxSataPortNum (); PortIndex++) {
    mPchSataConfig.PortSettings[PortIndex].Enable           = PCH_DEVICE_ENABLE;
    mPchSataConfig.PortSettings[PortIndex].HotPlug          = PCH_DEVICE_DISABLE;
    mPchSataConfig.PortSettings[PortIndex].InterlockSw      = PCH_DEVICE_DISABLE;
    mPchSataConfig.PortSettings[PortIndex].External         = PCH_DEVICE_DISABLE;
    mPchSataConfig.PortSettings[PortIndex].SpinUp           = PCH_DEVICE_DISABLE;
    mPchSataConfig.PortSettings[PortIndex].SolidStateDrive  = PCH_DEVICE_DISABLE;
    mPchSataConfig.PortSettings[PortIndex].DevSlp           = PCH_DEVICE_DISABLE;
    mPchSataConfig.PortSettings[PortIndex].EnableDitoConfig = PCH_DEVICE_DISABLE;
    mPchSataConfig.PortSettings[PortIndex].DmVal            = 15;
    mPchSataConfig.PortSettings[PortIndex].DitoVal          = 625;
  }

  mPchSataConfig.RaidAlternateId  = PCH_DEVICE_DISABLE;
  mPchSataConfig.Raid0            = PCH_DEVICE_ENABLE;
  mPchSataConfig.Raid1            = PCH_DEVICE_ENABLE;
  mPchSataConfig.Raid10           = PCH_DEVICE_ENABLE;
  mPchSataConfig.Raid5            = PCH_DEVICE_ENABLE;
  mPchSataConfig.Irrt             = PCH_DEVICE_ENABLE;
  mPchSataConfig.OromUiBanner     = PCH_DEVICE_ENABLE;
  mPchSataConfig.HddUnlock        = PCH_DEVICE_ENABLE;
  mPchSataConfig.LedLocate        = PCH_DEVICE_ENABLE;
  mPchSataConfig.IrrtOnly         = PCH_DEVICE_ENABLE;
  mPchSataConfig.SmartStorage     = PCH_DEVICE_ENABLE;
  mPchSataConfig.OromUiDelay      = PchSataOromDelay2sec;
  mPchSataConfig.TestMode         = PCH_DEVICE_DISABLE;
  mPchSataConfig.SalpSupport      = PCH_DEVICE_ENABLE;
  mPchSataConfig.LegacyMode       = PCH_DEVICE_DISABLE;
  mPchSataConfig.SpeedSupport     = PchSataSpeedSupportDefault;

  ///
  /// AzaliaConfig
  ///
  mPchAzaliaConfig.Pme            = PCH_DEVICE_DISABLE;
  mPchAzaliaConfig.ResetWaitTimer = 300;
  mPchAzaliaConfig.DS             = 1;
  mPchAzaliaConfig.DA             = 0;

  ///
  /// Reserved SMBus Address
  ///
  mPchSmbusConfig.NumRsvdSmbusAddresses = 4;
  mPchSmbusConfig.RsvdSmbusAddressTable = mSmbusRsvdAddresses;

  ///
  /// MiscPm Configuration
  ///
  mPchMiscPmConfig.PchDeepSxPol                         = PchDeepSxPolDisable;
  mPchMiscPmConfig.WakeConfig.PmeB0S5Dis                = PCH_DEVICE_DISABLE;
  mPchMiscPmConfig.WakeConfig.WolEnableOverride         = PCH_DEVICE_DISABLE;
  mPchMiscPmConfig.WakeConfig.Gp27WakeFromDeepSx        = PCH_DEVICE_ENABLE;
  mPchMiscPmConfig.WakeConfig.PcieWakeFromDeepSx        = PCH_DEVICE_DISABLE;
  mPchMiscPmConfig.PowerResetStatusClear.MeWakeSts      = PCH_DEVICE_ENABLE;
  mPchMiscPmConfig.PowerResetStatusClear.MeHrstColdSts  = PCH_DEVICE_ENABLE;
  mPchMiscPmConfig.PowerResetStatusClear.MeHrstWarmSts  = PCH_DEVICE_ENABLE;

  mPchMiscPmConfig.PchSlpS3MinAssert                    = PchSlpS350ms;
  mPchMiscPmConfig.PchSlpS4MinAssert                    = PchSlpS44s;
  mPchMiscPmConfig.PchSlpSusMinAssert                   = PchSlpSus4s;
  mPchMiscPmConfig.PchSlpAMinAssert                     = PchSlpA2s;
  mPchMiscPmConfig.PchPwrCycDur                         = 4;  // 4-5 seconds (PCH default setting)
  mPchMiscPmConfig.SlpStrchSusUp                        = PCH_DEVICE_DISABLE;
  mPchMiscPmConfig.SlpLanLowDc                          = PCH_DEVICE_DISABLE;

  ///
  /// Io Apic configuration
  ///
  mPchIoApicConfig.BdfValid                             = 1;
  mPchIoApicConfig.BusNumber                            = 0xF0;
  mPchIoApicConfig.DeviceNumber                         = 0x1F;
  mPchIoApicConfig.FunctionNumber                       = 0x00;
  mPchIoApicConfig.IoApicEntry24_39                     = PCH_DEVICE_ENABLE;

  ///
  /// Default Svid Sdid configuration
  ///
  mPchDefaultSvidSid.SubSystemVendorId                  = V_PCH_INTEL_VENDOR_ID;
  mPchDefaultSvidSid.SubSystemId                        = V_PCH_DEFAULT_SID;

  ///
  /// Thermal configuration - Initialize policy to default values when variable isn't found.
  ///
  mPchThermalConfig.ThermalAlertEnable.TselLock                   = PCH_DEVICE_ENABLE;
  mPchThermalConfig.ThermalAlertEnable.TscLock                    = PCH_DEVICE_ENABLE;
  mPchThermalConfig.ThermalAlertEnable.TsmicLock                  = PCH_DEVICE_ENABLE;
  mPchThermalConfig.ThermalAlertEnable.PhlcLock                   = PCH_DEVICE_ENABLE;
  mPchThermalConfig.ThermalThrottling.TTLevels.SuggestedSetting   = PCH_DEVICE_ENABLE;
  mPchThermalConfig.ThermalThrottling.TTLevels.PchCrossThrottling = PCH_DEVICE_ENABLE;
  mPchThermalConfig.ThermalThrottling.DmiHaAWC.SuggestedSetting   = PCH_DEVICE_ENABLE;
  mPchThermalConfig.ThermalThrottling.SataTT.SuggestedSetting     = PCH_DEVICE_ENABLE;
  mPchThermalConfig.ThermalDeviceEnable                           = PCH_DEVICE_DISABLE;
  ///
  /// The value in this field is valid only if it is between 00h and 17Fh.
  /// 0x17F is the hottest temperature and 0x000 is the lowest temperature
  ///
  mPchThermalConfig.PchHotLevel = 0x000;

  ///
  /// HEPT Configuration
  ///
  mPchHpetConfig.BdfValid       = 1;
  for (Index = 0; Index < PCH_HPET_BDF_MAX; Index++) {
    mPchHpetConfig.Hpet[Index].BusNumber       = 0xF0;
    mPchHpetConfig.Hpet[Index].DeviceNumber    = 0x0F;
    mPchHpetConfig.Hpet[Index].FunctionNumber  = 0x00;
  }
  ///
  /// Initialize Serial IRQ Config
  ///
  mSerialIrqConfig.SirqEnable       = TRUE;
  mSerialIrqConfig.StartFramePulse  = PchSfpw4Clk;
  mSerialIrqConfig.SirqMode         = PchContinuousMode;

  ///
  /// DMI related settings
  ///
  mPchDmiConfig.DmiAspm         = PCH_DEVICE_ENABLE;
  mPchDmiConfig.DmiExtSync      = PCH_DEVICE_DISABLE;
  mPchDmiConfig.DmiIot          = PCH_DEVICE_DISABLE;

  ///
  /// Power Optimizer related settings
  ///
  mPchPwrOptConfig.PchPwrOptDmi      = PCH_DEVICE_ENABLE;
  mPchPwrOptConfig.PchPwrOptGbe      = PCH_DEVICE_ENABLE;
  mPchPwrOptConfig.PchPwrOptXhci     = PCH_DEVICE_DISABLE;
  mPchPwrOptConfig.PchPwrOptEhci     = PCH_DEVICE_DISABLE;
  mPchPwrOptConfig.PchPwrOptSata     = PCH_DEVICE_ENABLE;
  mPchPwrOptConfig.MemCloseStateEn   = PCH_DEVICE_ENABLE;
  mPchPwrOptConfig.InternalObffEn    = PCH_DEVICE_ENABLE;
  mPchPwrOptConfig.ExternalObffEn    = PCH_DEVICE_DISABLE;  // De-feature OBFF from LPT-H/LPT-LP.
  mPchPwrOptConfig.NumOfDevLtrOverride      = 0;
  mPchPwrOptConfig.DevLtrOverride           = NULL;
  for (PortIndex = 0; PortIndex < GetPchMaxPciePortNum (); PortIndex++) {
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].LtrEnable             = PCH_DEVICE_ENABLE;
    //
    // De-feature OBFF from LPT-H/LPT-LP.
    // Doesn't enable Obff policy anymore.
    //
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].ObffEnable            = PCH_DEVICE_DISABLE;
  }
  mPchPwrOptConfig.LegacyDmaDisable  = PCH_DEVICE_DISABLE;
  for (PortIndex = 0; PortIndex < GetPchMaxPciePortNum (); PortIndex++) {
    if (PchSeries == PchLp) {
      mPchPwrOptConfig.PchPwrOptPcie[PortIndex].LtrMaxSnoopLatency                 = 0x1003;
      mPchPwrOptConfig.PchPwrOptPcie[PortIndex].LtrMaxNoSnoopLatency               = 0x1003;
    }
    if (PchSeries == PchH) {
      mPchPwrOptConfig.PchPwrOptPcie[PortIndex].LtrMaxSnoopLatency                 = 0x0846;
      mPchPwrOptConfig.PchPwrOptPcie[PortIndex].LtrMaxNoSnoopLatency               = 0x0846;
    }
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].LtrConfigLock                      = PCH_DEVICE_ENABLE;
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].SnoopLatencyOverrideMode           = 2;
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].SnoopLatencyOverrideMultiplier     = 2;
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].SnoopLatencyOverrideValue          = 60;
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].NonSnoopLatencyOverrideMode        = 2;
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].NonSnoopLatencyOverrideMultiplier  = 2;
    mPchPwrOptConfig.PchPwrOptPcie[PortIndex].NonSnoopLatencyOverrideValue       = 60;
  }

  ///
  /// Misc. Config
  ///
  /// FviSmbiosType is the SMBIOS OEM type (0x80 to 0xFF) defined in SMBIOS Type 14 - Group
  /// Associations structure - item type. FVI structure uses it as SMBIOS OEM type to provide
  /// version information. The default value is type 221.
  ///
  mPchMiscConfig.FviSmbiosType  = 0xDD;

  ///
  /// DCI (Direct Connect Interface) Configuration
  ///
  mPchMiscConfig.DciEn  = PCH_DEVICE_DISABLE;

  ///
  /// Audio Dsp Configuration
  ///
  mAudioDspConfig.AudioDspD3PowerGating     = PCH_DEVICE_ENABLE;
  mAudioDspConfig.AudioDspAcpiMode          = 1; //1: ACPI mode, 0: PCI mode
  mAudioDspConfig.AudioDspAcpiInterruptMode = 1; //1: ACPI mode, 0: PCI mode
  mAudioDspConfig.AudioDspBluetoothSupport  = PCH_DEVICE_DISABLE; // Bluetooth SCO disabled

  ///
  /// Serial IO Configuration
  ///
  mSerialIoConfig.SerialIoMode              = PchSerialIoIsAcpi;
  switch(PchStepping()) {
    default:
       mSerialIoConfig.SerialIoInterruptMode = PchSerialIoIsAcpi;
       break;
  }
  mSerialIoConfig.Ddr50Support      = PCH_DEVICE_DISABLE;
  
  mSerialIoConfig.I2c0VoltageSelect = PchSerialIoIs18V;
  mSerialIoConfig.I2c1VoltageSelect = PchSerialIoIs33V;


  ///
  /// Update policy by platform setting
  ///
  UpdateDxePchPlatformPolicy (&mPchPolicyData);

#ifdef USB_PRECONDITION_ENABLE_FLAG
  ///
  /// Update Precondition option for S4 resume.
  /// Skip Precondition for S4 resume in case this boot may not connect BIOS USB driver.
  /// If BIOS USB driver will be connected always for S4, then disable below update.
  /// To keep consistency during boot, must enabled or disabled below function in both PEI and DXE
  /// PlatformPolicyInit driver.
  ///
  if (mPchUsbConfig.UsbPrecondition == TRUE) {
    if (GetBootModeHob () == BOOT_ON_S4_RESUME) {
      mPchUsbConfig.UsbPrecondition = FALSE;
      DEBUG ((EFI_D_INFO, "BootMode is BOOT_ON_S4_RESUME, disable Precondition\n"));
    }
  }
#endif  // USB_PRECONDITION_ENABLE_FLAG
  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gDxePchPlatformPolicyProtocolGuid,
                  &mPchPolicyData,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;

}
