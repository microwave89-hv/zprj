/** @file
  This file is SampleCode for Intel PCH PEI Platform Policy initialzation.

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
#include "PchPolicyInitPei.h"
#include "..\Common\PchPolicyInitCommon.h"
#ifdef RAPID_START_FLAG
#include "RapidStartCommonLib.h"
#endif

/**
  This PEIM performs PCH PEI Platform Policy initialzation.

  @param[in] FfsHeader            Pointer to Firmware File System file header.
  @param[in] PeiServices          General purpose services available to every PEIM.

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI ERRORS              The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
PchPolicyInitPeiEntryPoint (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
{
  EFI_STATUS                    Status;
  EFI_PEI_PPI_DESCRIPTOR        *PchPlatformPolicyPpiDesc;
  PCH_PLATFORM_POLICY_PPI       *PchPlatformPolicyPpi;
  PCH_GBE_CONFIG                *GbeConfig;
  PCH_THERMAL_MANAGEMENT        *ThermalMgmt;
  PCH_MEMORY_THROTTLING         *MemoryThrottling;
  PCH_HPET_CONFIG               *HpetConfig;
  PCH_SATA_CONTROL              *SataConfig;
  PCH_SATA_TRACE_CONFIG         *SataTraceConfig;
  PCH_PCIE_CONFIG               *PcieConfig;
  PCH_IOAPIC_CONFIG             *IoApicConfig;
  PCH_PLATFORM_DATA             *PlatformData;
  PCH_USB_CONFIG                *UsbConfig;
#ifdef USB_PRECONDITION_ENABLE_FLAG
  EFI_BOOT_MODE                 BootMode;
#endif  // USB_PRECONDITION_ENABLE_FLAG
  UINT8                         PortIndex;

  PchPlatformPolicyPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  ASSERT (PchPlatformPolicyPpiDesc != NULL);
  if (PchPlatformPolicyPpiDesc == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  PchPlatformPolicyPpi = (PCH_PLATFORM_POLICY_PPI *) AllocateZeroPool (sizeof (PCH_PLATFORM_POLICY_PPI));
  ASSERT (PchPlatformPolicyPpi != NULL);
  if (PchPlatformPolicyPpi == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  GbeConfig = (PCH_GBE_CONFIG *) AllocateZeroPool (sizeof (PCH_GBE_CONFIG));
  ASSERT (GbeConfig != NULL);
  if (GbeConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  ThermalMgmt = (PCH_THERMAL_MANAGEMENT *) AllocateZeroPool (sizeof (PCH_THERMAL_MANAGEMENT));
  ASSERT (ThermalMgmt != NULL);
  if (ThermalMgmt == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  MemoryThrottling = (PCH_MEMORY_THROTTLING *) AllocateZeroPool (sizeof (PCH_MEMORY_THROTTLING));
  ASSERT (MemoryThrottling != NULL);
  if (MemoryThrottling == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  HpetConfig = (PCH_HPET_CONFIG *) AllocateZeroPool (sizeof (PCH_HPET_CONFIG));
  ASSERT (HpetConfig != NULL);
  if (HpetConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SataConfig = (PCH_SATA_CONTROL *) AllocateZeroPool (sizeof (PCH_SATA_CONTROL));
  ASSERT (SataConfig != NULL);
  if (SataConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SataTraceConfig = (PCH_SATA_TRACE_CONFIG *) AllocateZeroPool (sizeof (PCH_SATA_TRACE_CONFIG));
  ASSERT (SataTraceConfig != NULL);
  if (SataTraceConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  PcieConfig = (PCH_PCIE_CONFIG *) AllocateZeroPool (sizeof (PCH_PCIE_CONFIG));
  ASSERT (PcieConfig != NULL);
  if (PcieConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  IoApicConfig = (PCH_IOAPIC_CONFIG *) AllocateZeroPool (sizeof (PCH_IOAPIC_CONFIG));
  ASSERT (IoApicConfig != NULL);
  if (IoApicConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  PlatformData = (PCH_PLATFORM_DATA *) AllocateZeroPool (sizeof (PCH_PLATFORM_DATA));
  ASSERT (PlatformData != NULL);
  if (PlatformData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  UsbConfig = (PCH_USB_CONFIG *) AllocateZeroPool (sizeof (PCH_USB_CONFIG));
  ASSERT (UsbConfig != NULL);
  if (UsbConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  PchPlatformPolicyPpi->Revision                = PCH_PLATFORM_POLICY_PPI_REVISION_4;
  PchPlatformPolicyPpi->BusNumber               = 0;
  PchPlatformPolicyPpi->Rcba                    = PCH_LPC_RCBA_BASE_ADDRESS;
  PchPlatformPolicyPpi->PmBase                  = PCH_LPC_ACPI_BASE_ADDRESS;
  PchPlatformPolicyPpi->GpioBase                = PCH_LPC_GPIO_BASE_ADDRESS;
  PchPlatformPolicyPpi->Port80Route             = 0;

  PchPlatformPolicyPpi->GbeConfig               = GbeConfig;
  PchPlatformPolicyPpi->ThermalMgmt             = ThermalMgmt;
  PchPlatformPolicyPpi->HpetConfig              = HpetConfig;
  PchPlatformPolicyPpi->SataConfig              = SataConfig;
  PchPlatformPolicyPpi->PcieConfig              = PcieConfig;
  PchPlatformPolicyPpi->IoApicConfig            = IoApicConfig;
  PchPlatformPolicyPpi->PlatformData            = PlatformData;
  PchPlatformPolicyPpi->UsbConfig               = UsbConfig;

  GbeConfig->EnableGbe      = 1;
  ThermalMgmt->MemoryThrottling                                 = MemoryThrottling;
  MemoryThrottling->Enable                                      = PCH_DEVICE_DISABLE;
  MemoryThrottling->TsGpioPinSetting[TsGpioC].PmsyncEnable      = PCH_DEVICE_ENABLE;
  MemoryThrottling->TsGpioPinSetting[TsGpioD].PmsyncEnable      = PCH_DEVICE_ENABLE;
  MemoryThrottling->TsGpioPinSetting[TsGpioC].C0TransmitEnable  = PCH_DEVICE_ENABLE;
  MemoryThrottling->TsGpioPinSetting[TsGpioD].C0TransmitEnable  = PCH_DEVICE_ENABLE;
  MemoryThrottling->TsGpioPinSetting[TsGpioC].PinSelection      = 1;
  MemoryThrottling->TsGpioPinSetting[TsGpioD].PinSelection      = 0;

  HpetConfig->Enable = 1;
  HpetConfig->Base = PCH_HPET_BASE_ADDRESS;

  SataConfig->SataMode = PchSataModeAhci;
  SataConfig->SataTraceConfig = SataTraceConfig;

  SataTraceConfig->TestMode        = PCH_DEVICE_DISABLE;
  for( PortIndex = 0; PortIndex < 6; PortIndex++ ) {
    SataTraceConfig->PortRxEq[PortIndex].GenSpeed[0].Enable = PCH_DEVICE_DISABLE;
    SataTraceConfig->PortRxEq[PortIndex].GenSpeed[1].Enable = PCH_DEVICE_DISABLE;
    SataTraceConfig->PortRxEq[PortIndex].GenSpeed[2].Enable = PCH_DEVICE_DISABLE;
    SataTraceConfig->PortRxEq[PortIndex].GenSpeed[0].RxEq = 0x0;
    SataTraceConfig->PortRxEq[PortIndex].GenSpeed[1].RxEq = 0x0;
    SataTraceConfig->PortRxEq[PortIndex].GenSpeed[2].RxEq = 0x0;
  }

  PcieConfig->PcieSpeed[0] = PchPcieAuto;
  PcieConfig->PcieSpeed[1] = PchPcieAuto;
  PcieConfig->PcieSpeed[2] = PchPcieAuto;
  PcieConfig->PcieSpeed[3] = PchPcieAuto;
  PcieConfig->PcieSpeed[4] = PchPcieAuto;
  PcieConfig->PcieSpeed[5] = PchPcieAuto;
  PcieConfig->PcieSpeed[6] = PchPcieAuto;
  PcieConfig->PcieSpeed[7] = PchPcieAuto;

  IoApicConfig->IoApicId = 0x02;
  IoApicConfig->ApicRangeSelect = 0x00;
  IoApicConfig->IoApicEntry24_39 = PCH_DEVICE_ENABLE;

  PlatformData->EcPresent = 0;
  ///
  /// PlatformData->SmmBwp value directly depends on the value of CpuConfig->Pfat
  /// (found in CpuPolicyInitPei.c file)
  /// If CpuConfig->Pfat is set to 1 (enabled) then
  ///   PlatformData->SmmBwp has to be set to 1 (enabled)
  /// This is a PFAT Security requirement that needs to be addressed
  /// If CpuConfig->Pfat is set to 0 (disabled) then
  ///   PlatformData->SmmBwp value don't care, it can be set to either
  ///   1 (enabled) or 0 (disabled) based on customer implementation
  ///
  PlatformData->SmmBwp    = 0;

  ///
  /// Temporary Memory Base Address for PCI devices to be used to initialize MMIO registers.
  /// Minimum size is 64KB bytes.
  ///
  PlatformData->TempMemBaseAddr   = PCH_TEMP_MEM_BASE_ADDRESS;

  ///
  /// Init USB related setting
  ///
  InitPchUsbConfig (UsbConfig);

  PchPlatformPolicyPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  PchPlatformPolicyPpiDesc->Guid  = &gPchPlatformPolicyPpiGuid;

  UpdatePeiPchPlatformPolicy (PeiServices, PchPlatformPolicyPpi);
#ifdef RAPID_START_FLAG
  if (RapidStartResumeCheck () == TRUE) {
    ///
    /// This is RapidStart resume, skip the UsbPrecondition feature in PEI phase
    ///
    PchPlatformPolicyPpi->UsbConfig->UsbPrecondition = 0;
  }
#endif


  PchPlatformPolicyPpiDesc->Ppi = PchPlatformPolicyPpi;
#ifdef USB_PRECONDITION_ENABLE_FLAG
  ///
  /// Update Precondition option for S4 resume. 
  /// Skip Precondition for S4 resume in case this boot may not connect BIOS USB driver.
  /// If BIOS USB driver will be connected always for S4, then disable below update.
  /// To keep consistency during boot, must enabled or disabled below function in both PEI and DXE
  /// PlatformPolicyInit driver.
  ///
  if (UsbConfig->UsbPrecondition == TRUE) {
    (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (BootMode == BOOT_ON_S4_RESUME) {
      UsbConfig->UsbPrecondition = FALSE;
      DEBUG ((EFI_D_INFO, "BootMode is BOOT_ON_S4_RESUME, disable Precondition\n"));
    }
  }
#endif  // USB_PRECONDITION_ENABLE_FLAG

  ///
  /// Install PCH Platform Policy PPI
  ///
  Status = (**PeiServices).InstallPpi (PeiServices, PchPlatformPolicyPpiDesc);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
