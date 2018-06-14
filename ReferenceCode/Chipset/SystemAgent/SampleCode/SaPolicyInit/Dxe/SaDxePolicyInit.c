/** @file
  This file is a wrapper for Intel SA Platform Policy driver.
  Get Setup Value to initilize Intel SA DXE Platform Policy.

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
#include "SaDxePolicyInit.h"

DXE_PLATFORM_SA_POLICY_PROTOCOL mDxePlatformSaPolicy;

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
///
/// Function implementations
///
/**
  Initilize Intel SA DXE Platform Policy

  @param[in] ImageHandle       Image handle of this driver.
  @param[in] SystemTable       Global system service table.

  @retval EFI_SUCCESS           Initialization complete.
  @exception EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR      Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
SaDxePolicyInitEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS  Status;
  UINT8       pegFn;
  UINT8       Index;

  SetMem (&mDxePlatformSaPolicy, sizeof (DXE_PLATFORM_SA_POLICY_PROTOCOL), 0);
  Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (SA_VTD_CONFIGURATION), &(mDxePlatformSaPolicy.Vtd));
  ASSERT_EFI_ERROR (Status);
  Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (SA_MEMORY_CONFIGURATION), &(mDxePlatformSaPolicy.MemoryConfig));
  ASSERT_EFI_ERROR (Status);
  Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (SA_PCIE_CONFIGURATION), &(mDxePlatformSaPolicy.PcieConfig));
  ASSERT_EFI_ERROR (Status);
  Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (SA_IGD_CONFIGURATION), &(mDxePlatformSaPolicy.IgdConfig));
  ASSERT_EFI_ERROR (Status);
  Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (SA_MISC_CONFIGURATION), &(mDxePlatformSaPolicy.MiscConfig));
  ASSERT_EFI_ERROR (Status);
#ifdef SG_SUPPORT
  Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (SA_SG_VBIOS_CONFIGURATION), &(mDxePlatformSaPolicy.VbiosConfig));
  ASSERT_EFI_ERROR (Status);
#endif

  ///
  /// SA DXE Policy Init
  ///
  mDxePlatformSaPolicy.Revision = DXE_SA_PLATFORM_POLICY_PROTOCOL_REVISION_8;

  ///
  /// Initialize the VTD Configuration
  ///
  mDxePlatformSaPolicy.Vtd->VtdEnable       = 0;
  mDxePlatformSaPolicy.Vtd->BaseAddress[0]  = 0xFED90000;
  mDxePlatformSaPolicy.Vtd->BaseAddress[1]  = 0xFED91000;
  ///
  /// RMRR Base and Limit Address for USB
  ///
  Status = (gBS->AllocatePool) (EfiBootServicesData, (sizeof (EFI_PHYSICAL_ADDRESS) * 2), (VOID **) &mDxePlatformSaPolicy.Vtd->RmrrUsbBaseAddress);
  ASSERT_EFI_ERROR (Status);
  ///
  /// BIOS must update USB RMRR base address
  ///
  mDxePlatformSaPolicy.Vtd->RmrrUsbBaseAddress[0] = 0x3E2E0000;
  mDxePlatformSaPolicy.Vtd->RmrrUsbBaseAddress[1] = 0x3E2FFFFF;

  ///
  /// Initialize the PCIE Configuration
  ///
  mDxePlatformSaPolicy.PcieConfig->DmiAspm = PcieAspmL0sL1;
  ///
  /// PEG ASPM per port configuration. 3 PEG controllers i.e. 0,1,2
  ///
  for (pegFn = 0; pegFn < 3; pegFn++) {
    mDxePlatformSaPolicy.PcieConfig->PegAspm[pegFn]       = PcieAspmAutoConfig;
    mDxePlatformSaPolicy.PcieConfig->PegAspmL0s[pegFn]    = 0;
    mDxePlatformSaPolicy.PcieConfig->PegDeEmphasis[pegFn] = 1;
  }

  mDxePlatformSaPolicy.PcieConfig->DmiExtSync     = 0;
  mDxePlatformSaPolicy.PcieConfig->DmiDeEmphasis  = 0;
  mDxePlatformSaPolicy.PcieConfig->DmiIot = 0;
  mDxePlatformSaPolicy.PcieConfig->C7Allowed = 0;
  for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
    mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[Index].LtrEnable            = 1;
    mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[Index].LtrMaxSnoopLatency   = V_SA_LTR_MAX_SNOOP_LATENCY_VALUE;
    mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[Index].LtrMaxNoSnoopLatency = V_SA_LTR_MAX_NON_SNOOP_LATENCY_VALUE;
    mDxePlatformSaPolicy.PcieConfig->PegPwrOpt[Index].ObffEnable           = 1;
  }

  mDxePlatformSaPolicy.PcieConfig->PcieAspmDevsOverride = mPcieAspmDevsOverride;
  mDxePlatformSaPolicy.PcieConfig->PcieLtrDevsOverride  = mPcieLtrDevsOverride;

  ///
  /// Initialize the Memory Configuration
  ///
  ///
  /// DIMM SMBus addresses info
  /// Refer to the SpdAddressTable[] mapping rule in SaPlatformPolicy.h
  ///
  Status = (gBS->AllocatePool) (EfiBootServicesData, (sizeof (UINT8) * 4), (VOID **) &mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable);
  ASSERT_EFI_ERROR (Status);

  mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable[0] = DIMM_SMB_SPD_P0C0D0;
  mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable[1] = DIMM_SMB_SPD_P0C0D1;
  mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable[2] = DIMM_SMB_SPD_P0C1D0;
  mDxePlatformSaPolicy.MemoryConfig->SpdAddressTable[3] = DIMM_SMB_SPD_P0C1D1;

  mDxePlatformSaPolicy.MemoryConfig->ChannelASlotMap    = 0x01;
  mDxePlatformSaPolicy.MemoryConfig->ChannelBSlotMap    = 0x01;
  mDxePlatformSaPolicy.MemoryConfig->RmtBdatEnable      = 0x00;

  ///
  /// Initialize the Graphics configuration
  ///
  mDxePlatformSaPolicy.IgdConfig->RenderStandby     = 1;
  mDxePlatformSaPolicy.IgdConfig->VbtAddress        = 0x00000000;
  mDxePlatformSaPolicy.IgdConfig->Size              = 0;
  mDxePlatformSaPolicy.IgdConfig->CdClk             = 0;
  mDxePlatformSaPolicy.IgdConfig->PlatformConfig    = 1;

  ///
  /// SA internal devices and misc configuration
  ///
  mDxePlatformSaPolicy.MiscConfig->ChapDeviceEnable = FALSE;
  mDxePlatformSaPolicy.MiscConfig->Device4Enable    = FALSE;
  mDxePlatformSaPolicy.MiscConfig->CridEnable       = FALSE;
  mDxePlatformSaPolicy.MiscConfig->AudioEnable      = TRUE;
  mDxePlatformSaPolicy.MiscConfig->FviReport        = 1;
  ///
  /// Default Enable FVI SMBIOS Report
  ///
  mDxePlatformSaPolicy.MiscConfig->FviSmbiosType = 0xDD;
  ///
  /// Default SMBIOS Type 221
  ///
  Status = (gBS->AllocatePool) (EfiBootServicesData, sizeof (SA_DEFAULT_SVID_SID), (VOID **) &mDxePlatformSaPolicy.MiscConfig->DefaultSvidSid);
  ASSERT_EFI_ERROR (Status);
  mDxePlatformSaPolicy.MiscConfig->DefaultSvidSid->SubSystemVendorId = V_SA_MC_VID;
  ///
  /// 0x8086;
  ///
  mDxePlatformSaPolicy.MiscConfig->DefaultSvidSid->SubSystemId = 0x2010;


#ifdef SG_SUPPORT
  ///
  /// Initialize the Switchable Graphics DXE Policies
  ///

  ///
  /// 1 = Load secondary display device VBIOS
  /// 0 = Do not load
  ///
  mDxePlatformSaPolicy.VbiosConfig->LoadVbios = 0;
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

  UpdateDxeSaPlatformPolicy (&mDxePlatformSaPolicy);

  ///
  /// Install protocol to to allow access to this Policy.
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gDxePlatformSaPolicyGuid,
                  &mDxePlatformSaPolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
