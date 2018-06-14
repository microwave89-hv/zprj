//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/LegacyBiosPlatform.h 15    4/24/12 6:41p Olegi $
//
// $Revision: 15 $
//
// $Date: 4/24/12 6:41p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/LegacyBiosPlatform.h $
// 
// 15    4/24/12 6:41p Olegi
// [TAG]  		EIP86770
// [Category]  	Improvement
// [Description]  	Added EfiGetBcvSkipDeviceList to
// EFI_GET_PLATFORM_INFO_MODE structure.
// 
// 14    1/12/10 11:51a Olegi
// Copyright message updated.
// 
// 13    12/02/09 9:57a Olegi
// Extended the parameters of GetPlatformInfo with
// EfiGetPlatformNmiInformation.
// 
// 12    12/09/08 3:33p Olegi
// 
// 11    12/04/08 5:57p Olegi
// 
// 10    11/12/08 5:02p Olegi
// 
// 9     4/27/07 5:49p Olegi
// 
// 8     4/27/07 5:17p Olegi
// CSM.CHM file preparation.
//
// 7     3/13/06 2:43p Felixp
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    LegacyBiosPlatform.h
//
// Description: LegacyBiosPlatform protocol declaration
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LEGACY_BIOS_PLATFORM_PROTOCOL_H__
#define __LEGACY_BIOS_PLATFORM_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_LEGACY_BIOS_PLATFORM_PROTOCOL_GUID \
    { 0x783658a3, 0x4172, 0x4421, 0xa2, 0x99, 0xe0, 0x9, 0x7, 0x9c, 0xc, 0xb4 }

GUID_VARIABLE_DECLARATION(gEfiLegacyBiosPlatformProtocolGuid,EFI_LEGACY_BIOS_PLATFORM_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/DevicePath.h>
#pragma pack(1)

typedef struct _EFI_LEGACY_BIOS_PLATFORM_PROTOCOL EFI_LEGACY_BIOS_PLATFORM_PROTOCOL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_PLATFORM_PREPARE_TO_BOOT
//
// Description: Prepares the attempt to boot a traditional OS.
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  BbsDevicePath   EFI Device Path from BootXXXX variable.
//  BbsTable        A list of BBS entries of type BBS_TABLE.
//  LoadOptionsSize Size of LoadOption in bytes.
//  LoadOptions     LoadOption from BootXXXX variable.
//  EfiToLegacyBootTable    Pointer to EFI_TO_COMPATIBILITY16_BOOT_TABLE.
//
// Output:
//  EFI_SUCCESS Ready to boot.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_PLATFORM_PREPARE_TO_BOOT) (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL     *This,
  IN  BBS_BBS_DEVICE_PATH                   *BbsDevicePath,
  IN  VOID                                  *BbsTable,
  IN  UINT32                                LoadOptionsSize,
  IN  VOID                                  *LoadOptions,
  IN  VOID                                  *EfiToLegacyBootTable
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_PLATFORM_TRANSLATE_PIRQ
//
// Description: This function translates the given PIRQ back through all
//              buses, if required, and returns the true PIRQ and associated IRQ.
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  PciBus      PCI bus number for this device.
//  PciDevice   PCI device number for this device.
//  PciFunction PCI function number for this device.
//  Pirq        The PIRQ. PIRQ A = 0, PIRQ B = 1, and so on.
//  PirqIrq     IRQ assigned to the indicated PIRQ.
//
// Output:
//  EFI_SUCCESS The PIRQ was translated.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_PLATFORM_TRANSLATE_PIRQ) (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL  *This,
  IN  UINTN                              PciBus,
  IN  UINTN                              PciDevice,
  IN  UINTN                              PciFunction,
  IN  OUT UINT8                          *Pirq,
  OUT UINT8                              *PciIrq
  );


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_PIRQ_ENTRY
//
// Description: EFI_LEGACY_BIOS_PLATFORM_GET_ROUTING_TABLE related definition
//
// Fields:
//  Pirq    UINT8   If nonzero, a value assigned by the IBV.
//  IrqMask UINT16  If nonzero, the IRQs that can be assigned to this device.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT8                    Pirq;
  UINT16                   IrqMask;
} EFI_LEGACY_PIRQ_ENTRY;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_IRQ_ROUTING_ENTRY
//
// Description: EFI_LEGACY_BIOS_PLATFORM_GET_ROUTING_TABLE related definition
//
// Fields:
//  Bus     UINT8   PCI bus of the entry.
//  Device  UINT8   PCI device of this entry.
//  PirqEntry   EFI_LEGACY_PIRQ_ENTRY   An IBV value and IRQ mask for PIRQ pins A through D.
//  Slot    UINT8   If nonzero, the slot number assigned by the board manufacturer.
//  Reserved    UINT8   Reserved for future use.
//
// Referrals:   EFI_LEGACY_PIRQ_ENTRY
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct {
  UINT8                    Bus;
  UINT8                    Device;
  EFI_LEGACY_PIRQ_ENTRY    PirqEntry[4];
  UINT8                    Slot;
  UINT8                    Reserved;
} EFI_LEGACY_IRQ_ROUTING_ENTRY;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_PIRQ_TABLE_HEADER
//
// Description: EFI_LEGACY_BIOS_PLATFORM_GET_ROUTING_TABLE related definition
//
// Fields:
//  Signature       UINT32  "$PIR".
//  MinorVersion    UINT8   0x00.
//  MajorVersion    UINT8   0x01 for table version 1.0.
//  TableSize       UINT16  0x20 + RoutingTableEntries * 0x10.
//  Bus             UINT8   PCI interrupt router bus.
//  DevFunc         UINT8   PCI interrupt router device/function.
//  PciOnlyIrq      UINT16  If nonzero, bit map of IRQs reserved for PCI.
//  CompatibleVid   UINT16  Vendor ID of a compatible PCI interrupt router.
//  CompatibleDid   UINT16  Device ID of a compatible PCI interrupt router.
//  Minport         UINT32  If nonzero, a value passed directly to the IRQ miniport's Initialize function.
//  Reserved        UINT8[11]   Reserved for future usage.
//  Checksum        UINT8   This byte plus the sum of all other bytes in the LocalPirqTable equal 0x00.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT32                   Signature;
  UINT8                    MinorVersion;
  UINT8                    MajorVersion;
  UINT16                   TableSize;
  UINT8                    Bus;
  UINT8                    DevFun;
  UINT16                   PciOnlyIrq;
  UINT16                   CompatibleVid;
  UINT16                   CompatibleDid;
  UINT32                   Miniport;
  UINT8                    Reserved[11];
  UINT8                    Checksum;
} EFI_LEGACY_PIRQ_TABLE_HEADER;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY
//
// Description: EFI_LEGACY_BIOS_PLATFORM_GET_ROUTING_TABLE related definition
//
// Fields:
//  Irq     UINT8   IRQ for this entry.
//  Used    UINT8   Status of this IRQ
//
// Notes: The field Used data definitions below:
//              PCI_UNUSED  0x00 - This IRQ has not been assigned to PCI.
//              PCI_USED    0xFF - This IRQ has been assigned to PCI.
//              LEGACY_USED 0xFE - This IRQ has been used by an SIO legacy device and
//                          cannot be used by PCI.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT8                    Irq;
  UINT8                    Used;
} EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_BIOS_PLATFORM_GET_ROUTING_TABLE
//
// Description: Returns information associated with PCI IRQ routing.
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//
//  RoutingTable    Pointer to the PCI IRQ routing table. This location is the $PIR table
//      minus the header. The contents are described by the PCI IRQ Routing Table 
//      Specification and consist of RoutingTableEntries of EFI_LEGACY_IRQ_ROUTING_ENTRY.
//
//  RoutingTableEntries     Number of entries in the PCI IRQ routing table.
//
//  LocalPirqTable          $PIR table. It consists of EFI_LEGACY_PIRQ_TABLE_HEADER,
//      immediately followed by RoutingTable.
//
//  PirqTableSize           Size of $PIR table.
//
//  LocalIrqPriorityTable   A priority table of IRQs to assign to PCI. This table 
//      consists of IrqPriorityTableEntries of EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY
//      and is used to prioritize the allocation of IRQs to PCI.
//
//  IrqPriorityTableEntries Number of entries in the priority table.
//
// Output:
//  EFI_SUCCESS Data was returned successfully.
//
// Referrals:
//  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL, EFI_LEGACY_IRQ_ROUTING_ENTRY,
//  EFI_LEGACY_PIRQ_TABLE_HEADER, EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_PLATFORM_GET_ROUTING_TABLE) (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *This,
  OUT VOID                                **RoutingTable,
  OUT UINTN                               *RoutingTableEntries,
  OUT VOID                                **LocalPirqTable, OPTIONAL
  OUT UINTN                               *PirqTableSize, OPTIONAL
  OUT VOID                                **LocalIrqPriorityTable, OPTIONAL
  OUT UINTN                               *IrqPriorityTableEntries OPTIONAL
  );


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_GET_PLATFORM_HOOK_MODE
//
// Description: Mode definitions for EFI_LEGACY_BIOS_PLATFORM_HOOKS
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef enum {
  EfiPlatformHookPrepareToScanRom       = 0,
  EfiPlatformHookShadowServiceRoms      = 1,
  EfiPlatformHookAfterRomInit           = 2
} EFI_GET_PLATFORM_HOOK_MODE;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_BIOS_PLATFORM_HOOKS
//
// Description: Allows platform to perform any required action after a LegacyBios
//              operation.
// Input:       
//  DeviceHandle    List of PCI devices in the system.
//  ShadowAddress   First free OpROM area, after other OpROMs have been dispatched.
//  Compatibility16Table    Pointer to the Compatibility16 Table.
//  AdditionalData          Pointer to additional data returned - mode specific.
//
// Output:
//  EFI_SUCCESS     The operation performed successfully.
//  EFI_UNSUPPORTED Mode is not supported on this platform.
//  EFI_SUCCESS     Mode specific.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
struct _EFI_COMPATIBILITY16_TABLE;
typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_PLATFORM_HOOKS) (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL *This,
  IN  EFI_GET_PLATFORM_HOOK_MODE        Mode,
  IN  UINT16                            Type,
  IN  EFI_HANDLE                        OPTIONAL DeviceHandle,
  IN OUT UINTN                          OPTIONAL *ShadowAddress,
  IN struct _EFI_COMPATIBILITY16_TABLE  *Compatibility16Table,
  OUT VOID                              OPTIONAL **AdditionalData
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_BIOS_PLATFORM_SMM_INIT
//
// Description: Loads and registers the Compatibility16 handler with the EFI SMM code.
//
// Input:
//  This     Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  EfiToCompatibility16BootTable    The boot table passed to the Compatibility16.
//
// Output:
//  EFI_SUCCESS         The SMM code loaded.
//  EFI_DEVICE_ERROR    The SMM code failed to load.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_PLATFORM_SMM_INIT) (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *This,
  IN  VOID                                *EfiToCompatibility16BootTable
  );


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_GET_PLATFORM_HANDLE_MODE
//
// Description: Mode definitions for EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_HANDLE
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef enum {
  EfiGetPlatformVgaHandle       = 0,
  EfiGetPlatformIdeHandle       = 1,
  EfiGetPlatformIsaBusHandle    = 2,
  EfiGetPlatformUsbHandle       = 3
} EFI_GET_PLATFORM_HANDLE_MODE;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_HANDLE
//
// Description: Returns a buffer of handles for the requested subfunction.
//
// Input:
//  This    Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  Mode    Specifies what handle to return.
//              GetVgaHandle
//              GetIdeHandle
//              GetIsaBusHandle
//              GetUsbHandle
//  Type            Handle Modifier - Mode specific
//  HandleBuffer    Pointer to buffer containing all Handles matching the specified criteria.
//                      Handles are sorted in priority order. Type EFI_HANDLE is defined in
//                      InstallProtocolInterface() in the EFI 1.10 Specification.
//  HandleCount     Number of handles in HandleBuffer.
//  AdditionalData  Pointer to additional data returned - mode specific..
//
// Output:
//  EFI_SUCCESS The handle is valid.
//  EFI_UNSUPPORTED Mode is not supported on this platform.
//  EFI_NOT_FOUND   The handle is not known.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_HANDLE) (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL     *This,
  IN  EFI_GET_PLATFORM_HANDLE_MODE          Mode,
  IN  UINT16                                Type,
  OUT EFI_HANDLE                            **HandleBuffer,
  OUT UINTN                                 *HandleCount,
  OUT VOID                                  OPTIONAL **AdditionalData
  );


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_GET_PLATFORM_INFO_MODE
//
// Description: Mode definitions for EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_INFO
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef enum {
  EfiGetPlatformBinaryMpTable       = 0,
  EfiGetPlatformBinaryOemIntData    = 1,
  EfiGetPlatformBinaryOem16Data     = 2,
  EfiGetPlatformBinaryOem32Data     = 3,
  EfiGetPlatformBinaryTpmBinary     = 4,
  EfiGetPlatformBinarySystemRom     = 5,
  EfiGetPlatformPciExpressBase      = 6,
  EfiGetPlatformPmmSize             = 7,
  EfiGetPlatformEndRomShadowAddr    = 8,
  EfiGetPlatformOpromVideoMode      = 9,
  EfiGetPlatformIntSaveRestoreTable = 10,
  EfiGetPlatformPciIrqMask          = 11,
  EfiGetPlatformGateA20Information  = 12,
  EfiGetPlatformNmiInformation      = 13,
  EfiGetBcvSkipDeviceList           = 14,
} EFI_GET_PLATFORM_INFO_MODE;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_INFO
//
// Description: Finds the binary data or other platform information.
//              Refer to the subfunctions for additional information.
//
// Input:
//  This    Indicates the EFI_LEGACY_BIOS_PLATFORM_PROTOCOL instance.
//  Mode    Specifies what data to return:
//                  GetMpTable
//                  GetOemIntData
//                  GetOem16Data
//                  GetOem32Data
//                  GetTpmBinary
//                  GetSystemRom
//                  GetPciExpressBase
//                  GetPmmSize
//                  GetPlatformEndRomShadowAddr
//                  EfiGetOpromVideoSwitchingMode
//                  EfiGetInterruptSaveRestoreTable
//
//  Table       Pointer to OEM legacy 16-bit code or data.
//  TableSize   Size of data.
//  Location    Location to place table. 0x00 - Either 0xE0000 or 0xF0000 64 KB blocks.
//                  Bit 0 = 1 0xF0000 64 KB block.
//                  Bit 1 = 1 0xE0000 64 KB block.
//                  Note: Multiple bits can be set.
//  Alignment   Bit-mapped address alignment granularity. The first nonzero bit from the
//                  right is the address granularity.
//  LegacySegment   Segment where EfiCompatibility code will place the table or data.
//  LegacyOffset    Offset where EfiCompatibility code will place the table or data.
//
// Output:
//      EFI_SUCCESS     The data was returned successfully.
//      EFI_UNSUPPORTED Mode is not supported on this platform.
//      EFI_NOT_FOUND   Binary image not found.
//
// Referrals: EFI_GET_PLATFORM_INFO_MODE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_INFO) (
  IN  EFI_LEGACY_BIOS_PLATFORM_PROTOCOL           *This,
  IN  EFI_GET_PLATFORM_INFO_MODE                  Mode,
  IN OUT VOID                                     **Table,
  IN OUT UINTN                                    *TableSize,
  IN OUT UINTN                                    *Location,
  OUT UINTN                                       *Alignment,
  IN UINT16                                       LegacySegment,
  IN UINT16                                       LegacyOffset
  );


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_PLATFORM_PROTOCOL
//
// Description: The EFI_LEGACY_BIOS_PLATFORM_PROTOCOL is used to abstract the
//              platform-specific traditional hardware and or policy decisions
//              from the generic EfiCompatibility code.
// Fields:
//  GetPlatformInfo EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_INFO Gets binary data or other platform information.
//  GetPlatformHandle EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_HANDLE Returns a buffer of all handles matching the requested subfunction.
//  SmmInit EFI_LEGACY_BIOS_PLATFORM_SMM_INIT Loads and initializes the traditional BIOS SMM handler.
//  PlatformHooks EFI_LEGACY_BIOS_PLATFORM_HOOKS Allows platform to perform any required actions after a LegacyBios operation.
//  GetRoutingTable EFI_LEGACY_BIOS_PLATFORM_GET_ROUTING_TABLE Gets $PIR table.
//  TranslatePirq   EFI_LEGACY_BIOS_PLATFORM_TRANSLATE_PIRQ Translates the given PIRQ to the final value after traversing any PCI bridges.
//  PrepareToBoot   EFI_LEGACY_BIOS_PLATFORM_PREPARE_TO_BOOT Final platform function before the system attempts to boot to a traditional OS.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _EFI_LEGACY_BIOS_PLATFORM_PROTOCOL {
  EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_INFO   GetPlatformInfo;
  EFI_LEGACY_BIOS_PLATFORM_GET_PLATFORM_HANDLE GetPlatformHandle;
  EFI_LEGACY_BIOS_PLATFORM_SMM_INIT            SmmInit;
  EFI_LEGACY_BIOS_PLATFORM_HOOKS               PlatformHooks;
  EFI_LEGACY_BIOS_PLATFORM_GET_ROUTING_TABLE   GetRoutingTable;
  EFI_LEGACY_BIOS_PLATFORM_TRANSLATE_PIRQ      TranslatePirq;
  EFI_LEGACY_BIOS_PLATFORM_PREPARE_TO_BOOT     PrepareToBoot;
} EFI_LEGACY_BIOS_PLATFORM_PROTOCOL;

#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
