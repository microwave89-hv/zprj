/** @file
  Header file for the SwitchableGraphics Dxe driver.
  This driver loads SwitchableGraphics ACPI tables.

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
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

#ifndef _SWITCHABLE_GRAPHICS_DXE_H_
#define _SWITCHABLE_GRAPHICS_DXE_H_

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "EfiScriptLib.h"
#endif

#include "CpuRegs.h"
#include "CpuPlatformLib.h"

#include "PchAccess.h"
#include "Acpi3_0.h"
#include "SaAccess.h"

#include EFI_PROTOCOL_DEPENDENCY (PciIo)
#include EFI_PROTOCOL_DEPENDENCY (AcpiTable)
#include EFI_PROTOCOL_DEPENDENCY (FirmwareVolume)
#include EFI_PROTOCOL_DEPENDENCY (SaGlobalNvsArea)
#include EFI_GUID_DEFINITION (SaDataHob)
#include EFI_PROTOCOL_DEFINITION (SaPlatformPolicy)

///
/// SG ACPI table data storage file
///
#include EFI_GUID_DEFINITION (SgAcpiTableStorage)

///
/// Switchable Graphics defines.
///
#define CONVENTIONAL_MEMORY_TOP 0xA0000 ///< 640 KB
#define BIN_FILE_SIZE_MAX       0x10000

#define OPTION_ROM_SIGNATURE    0xAA55

#define MemoryRead16(Address)   * (UINT16 *) (Address)
#define MemoryRead8(Address)    * (UINT8 *) (Address)

///
/// PEG Capability Equates
///
#define PEG_CAP_ID  0x10
#define PEG_CAP_VER 0x2

#pragma pack(1)
typedef struct {
  UINT16  Signature;  ///< 0xAA55
  UINT8   Reserved[22];
  UINT16  PcirOffset;
} VBIOS_OPTION_ROM_HEADER;
#pragma pack()

#pragma pack(1)
typedef struct {
  UINT32  Signature;  ///< "PCIR"
  UINT16  VendorId;
  UINT16  DeviceId;
  UINT16  Reserved0;
  UINT16  Length;
  UINT8   Revision;
  UINT8   ClassCode[3];
  UINT16  ImageLength;
  UINT16  CodeRevision;
  UINT8   CodeType;
  UINT8   Indicator;
  UINT16  Reserved1;
} VBIOS_PCIR_STRUCTURE;
#pragma pack()

/**
  Initialize the SwitchableGraphics support.

  @param[in] ImageHandle         - Handle for the image of this driver
  @param[in] DxePlatformSaPolicy - SA DxePlatformPolicy protocol

  @retval EFI_SUCCESS         - SwitchableGraphics initialization complete
  @retval EFI_OUT_OF_RESOURCES - Unable to allocated memory
**/
EFI_STATUS
SwitchableGraphicsInit (
  IN EFI_HANDLE                      ImageHandle,
  IN EFI_SYSTEM_TABLE                *SystemTable,
  IN DXE_PLATFORM_SA_POLICY_PROTOCOL *DxePlatformSaPolicy
  )
;

/**
  Load and execute the dGPU VBIOS.

  @param[in] VbiosData - Pointer to VbiosData policy for Load/Execute and VBIOS Source.
      LoadVbios    - 0 = Do Not Load   ; 1 = Load VBIOS
      ExecuteVbios - 0 = Do Not Execute; 1 = Execute VBIOS
      VbiosSource  - 0 = PCIE Device   ; 1 = FirmwareVolume => TBD

  @retval EFI_SUCCESS     - Load and execute successful.
  @exception EFI_UNSUPPORTED - Secondary VBIOS not loaded.
**/
EFI_STATUS
LoadAndExecuteDgpuVbios (
  IN SA_SG_VBIOS_CONFIGURATION  *VbiosConfig
  )
;

/**
  Initialize the runtime SwitchableGraphics support data for ACPI tables in GlobalNvs.
  @param[in] SgInfoDataHob   - Pointer to Hob for SG system details.
  @param[in] DxePlatformSgPolicy - Pointer to the loaded image protocol for this driver.

  @retval EFI_SUCCESS - The data updated successfully.
**/
EFI_STATUS
UpdateGlobalNvsData (
  IN SG_INFO_HOB                     SgInfo,
  IN DXE_PLATFORM_SA_POLICY_PROTOCOL *DxePlatformSaPolicy
  )
;

/**
  Do an AllocatePages () of type AllocateMaxAddress for EfiBootServicesCode
  memory.

  @param[in] AllocateType     - Allocated Legacy Memory Type
  @param[in] StartPageAddress - Start address of range
  @param[in] Pages            - Number of pages to allocate
  @param[in, out] Result      - Result of allocation

  @retval EFI_SUCCESS - Legacy16 code loaded
  @retval Other       - No protocol installed, unload driver.
**/
EFI_STATUS
AllocateLegacyMemory (
  IN  EFI_ALLOCATE_TYPE         AllocateType,
  IN  EFI_PHYSICAL_ADDRESS      StartPageAddress,
  IN  UINTN                     Pages,
  IN OUT  EFI_PHYSICAL_ADDRESS  *Result
  )
;

/**
  Search and return the offset of desired Pci Express Capability ID
    CAPID list:
      0x0001 = Advanced Error Rreporting Capability
      0x0002 = Virtual Channel Capability
      0x0003 = Device Serial Number Capability
      0x0004 = Power Budgeting Capability

    @param[in] Bus       -   Pci Bus Number
    @param[in] Device    -   Pci Device Number
    @param[in] Function  -   Pci Function Number
    @param[in] CapId     -   Extended CAPID to search for

    @retval 0       - CAPID not found
    @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
PcieFindExtendedCapId (
  IN UINT8  Bus,
  IN UINT8  Device,
  IN UINT8  Function,
  IN UINT16 CapId
  )
;

/**
  Find the Offset to a given Capabilities ID
    CAPID list:
      0x01 = PCI Power Management Interface
      0x04 = Slot Identification
      0x05 = MSI Capability
      0x10 = PCI Express Capability

    @param[in] Bus       -   Pci Bus Number
    @param[in] Device    -   Pci Device Number
    @param[in] Function  -   Pci Function Number
    @param[in] CapId     -   CAPID to search for

    @retval 0       - CAPID not found
    @retval Other   - CAPID found, Offset of desired CAPID
**/
UINT32
PcieFindCapId (
  IN UINT8 Bus,
  IN UINT8 Device,
  IN UINT8 Function,
  IN UINT8 CapId
  )
;

/**
  Read SG GPIO value

  @param[in] Value - PCH GPIO number and Active value
      Bit0 to Bit7    - PCH GPIO Number
      Bit8            - GPIO Active value (0 = Active Low; 1 = Active High)

  @retval GPIO read value.
**/
BOOLEAN
GpioRead (
  IN UINT8 Value
  )
;

/**
  Write SG GPIO value

  @param[in] Value - PCH GPIO number and Active value
      Bit0 to Bit7    - PCH GPIO Number
      Bit8            - GPIO Active value (0 = Active Low; 1 = Active High)
  @param[in] Level - Write data (0 = Disable; 1 = Enable)
**/
VOID
GpioWrite (
  IN UINT8   Value,
  IN BOOLEAN Level
  )
;

/**
  Load Intel SG SSDT Tables

  @param[in] None

  @retval EFI_SUCCESS - SG SSDT Table load successful.
**/
EFI_STATUS
LoadAcpiTables (
  VOID
  )
;


VOID
EFIAPI
SgExitPmAuthCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  );

#endif
