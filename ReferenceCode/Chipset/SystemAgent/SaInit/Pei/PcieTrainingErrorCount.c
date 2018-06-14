/** @file
  Error Counting for PEG training.

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/

#include "PcieTraining.h"

#ifdef PEG_FLAG

UINT32
OpenMonitor (
  IN EFI_PEI_SERVICES       **PeiServices,
  IN SA_PLATFORM_POLICY_PPI *SaPlatformPolicyPpi,
  IN PEI_STALL_PPI          *StallPpi
  )
{
  UINT32 MonitorPort;

  InitMonitor (SaPlatformPolicyPpi->PlatformData->MchBar, SaPlatformPolicyPpi->PlatformData->GdxcBar);
  MonitorPort = EnableMonitor ();
  FullMonitorReset (MonitorPort);
  ProgramMonitor (MonitorPort, PeiServices, StallPpi);

  return MonitorPort;
}

VOID
CloseMonitor (
  IN SA_PLATFORM_POLICY_PPI *SaPlatformPolicyPpi,
  IN UINT32                 MonitorPort
  )
{
  FullMonitorReset (MonitorPort);
  DisableMonitor ();
  TearDownMonitor (SaPlatformPolicyPpi->PlatformData->MchBar, SaPlatformPolicyPpi->PlatformData->GdxcBar);

  return;
}

UINT32
SaPcieGetErrorCount (
  IN UINT32 MonitorPort,
  IN UINT8  PcieController
  )
{
  UINT32 Data32;

  Data32 = Mmio32 (MonitorPort, (0xC + (PcieController * 0x10)));

  return Data32;
}

VOID
SaPcieClearErrorCount (
  IN UINT32           MonitorPort,
  IN EFI_PEI_SERVICES **PeiServices,
  IN PEI_STALL_PPI    *StallPpi
  )
{
  FullMonitorReset (MonitorPort);
  ProgramMonitor (MonitorPort, PeiServices, StallPpi);

  return;
}

VOID
InitMonitor (
  IN UINT32 MchBar,
  IN UINT32 GdxcBar
  )
{
  Mmio32 (MchBar, 0x6430)  = 0x3;
  Mmio32 (MchBar, 0x6434)  = 0x76543210;
  McD1PciCfg32 (0x630)     = 0xB;
  McD1PciCfg32 (0x600)     = 0x60B;
  McD1PciCfg32 (0x604)     = 0x76543980;
  McD1F1PciCfg32 (0x600)   = 0x60B;
  McD1F1PciCfg32 (0x604)   = 0x76543280;
  McD1F2PciCfg32 (0x600)   = 0xB;
  McD1F2PciCfg32 (0x604)   = 0x76543210;
  Mmio32 (MchBar, 0x6438)  = 0x680000;
  Mmio32 (GdxcBar, 0xA04)  = 0xA;

  return;
}

VOID
TearDownMonitor (
  IN UINT32 MchBar,
  IN UINT32 GdxcBar
  )
{
  Mmio32 (MchBar, 0x6430)  = 0x0;
  Mmio32 (MchBar, 0x6434)  = 0x0;
  McD1PciCfg32 (0x630)     = 0x0;
  McD1PciCfg32 (0x600)     = 0x0;
  McD1PciCfg32 (0x604)     = 0x0;
  McD1F1PciCfg32 (0x600)   = 0x0;
  McD1F1PciCfg32 (0x604)   = 0x0;
  McD1F2PciCfg32 (0x600)   = 0x0;
  McD1F2PciCfg32 (0x604)   = 0x0;
  Mmio32 (MchBar, 0x6438)  = 0x0;
  Mmio32 (GdxcBar, 0xA04)   = 0x0;

  return;
}

UINT32
EnableMonitor (
  VOID
  )
{
  UINT32 Data32;

  Data32 = (McD0PciCfg32 (0140) & ~(07));
  Mmio32Or (Data32, 0124, 040000);
  Mmio64 (Data32, 0700020) = (UINT64) SA_PEI_MONITOR_OFFSET;
  Mmio16Or (Data32, 0700004, 02);

  return SA_PEI_MONITOR_OFFSET;
}

VOID
DisableMonitor (
  VOID
  )
{
  UINT32 Data32;

  Data32 = (McD0PciCfg32 (0140) & ~(07));
  Mmio16And (Data32, 0700004, 0177775);
  Mmio64And (Data32, 0700020, 07777);
  Mmio32And (Data32, 0124, 037777737777);

  return;
}

VOID
FullMonitorReset (
  IN UINT32 MonitorPort
  )
{
  Mmio32 (MonitorPort, 0x0)  = 0x40000;
  Mmio32 (MonitorPort, 0x4)  = 0x0;
  Mmio32 (MonitorPort, 0x10) = 0x40000;
  Mmio32 (MonitorPort, 0x14) = 0x0;
  Mmio32 (MonitorPort, 0x20) = 0x40000;
  Mmio32 (MonitorPort, 0x24) = 0x0;
  Mmio32 (MonitorPort, 0x8)  = 0xFF000000;
  Mmio32 (MonitorPort, 0x18) = 0xFF000000;
  Mmio32 (MonitorPort, 0x28) = 0xFF000000;
  Mmio32 (MonitorPort, 0xC)  = 0x0;
  Mmio32 (MonitorPort, 0x1C) = 0x0;
  Mmio32 (MonitorPort, 0x2C) = 0x0;

  return;
}

VOID
ProgramMonitor (
  IN UINT32           MonitorPort,
  IN EFI_PEI_SERVICES **PeiServices,
  IN PEI_STALL_PPI    *StallPpi
  )
{
  Mmio32 (MonitorPort, 0x4)  = 0xA100;
  Mmio32 (MonitorPort, 0x14) = 0xA101;
  Mmio32 (MonitorPort, 0x24) = 0xA102;
  Mmio32 (MonitorPort, 0x0)  = 0x110000;
  StallPpi->Stall (PeiServices, StallPpi, 1 * STALL_ONE_MILLI_SECOND);

  Mmio32 (MonitorPort, 0x0)  = 0x22100;
  Mmio32 (MonitorPort, 0x10) = 0x22101;
  Mmio32 (MonitorPort, 0x20) = 0x22102;

  return;
}

#endif // PEG_FLAG
