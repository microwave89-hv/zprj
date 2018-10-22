//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/csm.h 92    9/08/15 2:46p Olegi $
//
// $Revision: 92 $
//
// $Date: 9/08/15 2:46p $
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
//  Name:   CSM.H
//
//  Description: AMI CSM header file.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __CSM_HEADER__
#define __CSM_HEADER__

#include "efi.h"
#include <Protocol\DevicePath.h>
#include <Protocol\LegacyBios.h>
#include <Protocol\LegacyRegion.h>
#include <Protocol\Legacy8259.h>
#include <Protocol\LegacyInterrupt.h>
#include <Protocol\LegacyBiosPlatform.h>
#include <Protocol\SimpleTextOut.h >
#include <GenericSio.h>
#include <Protocol\LegacyBiosExt.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack (1)

#define EFI_LEGACY_BIOS_GUID  \
  { 0x2e3044ac, 0x879f, 0x490f, 0x97, 0x60, 0xbb, 0xdf, 0xaf, 0x69, 0x5f, 0x50 }


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_TO_COMPATIBILITY16_INIT_TABLE
//
// Description:  Data structure passed to Compatibility16InitializeYourself
//              function.
// Fields:
//  BiosLessThan1MB UINT32 Starting address of memory under 1 MB.The ending address is assumed to be 640 KB or 0x9FFFF.
//
//  HiPmmMemory UINT32 Starting address of the high memory block
//
//  HiPmmMemorySizeInBytes UINT32 Length of high memory block
//
//  ReverseThunkCallSegment UINT16 The segment of the reverse thunk call code
//
//  ReverseThunkCallOffset UINT16 The offset of the reverse thunk call code
//
//  Number820Entries UINT32 The number of E820 entries copied to the Compatibility16 BIOS
//
//  OsMemoryAbove1Mb UINT32 The amount of usable memory above 1 MB, e.g., E820 type 1 memory
//
//  ThunkStart UINT32 The start of thunk code in main memory. Memory cannot be used by BIOS or PMM.
//
//  ThunkSizeInBytes UINT32 The size of the thunk code
//
//  LowPmmMemory UINT32 Starting address of memory below 1MB
//
//  LowPmmMemorySizeInBytes UINT32 Length of low Memory block
//
// Referrals:   Compatibility16InitializeYourself
//
// Notes:   - The address of the ReverseThunkCall code is provided in case
//          the Compatibility16 code needs to invoke a Compatibility16
//          function.  It is not used to return from this function or any
//          other traditional BIOS interface function.  These functions simply
//          do a far return.
//          - CSM16 must handle cases where PMM pointers are NULL. That indicates
//          that PMM is not supported for that range. If both pointers are NULL
//          then PMM is not supported. That covers cases where no add-in cards
//          are supported and/or memory given to EFI.
//          - CSM16 must initialize PMM regions to zero prior to usage by OpROMs.
//          CSM16 can not assume the CSM32 had zeroed out the regions.
//          - CSM16 must monitor for EBDA size increase after OpROM is initalized
//          and adjust PMM below 1MB, if required.
//          - BiosLessThan1MB field is maintained for compatibility with the
//          previous versions of the specification and the CSM16 should not use this
//          field. The CSM16 should use LowPmmMemory and LowPmmMemorySizeInBytes fields
//          for the low memory that can be used for PMM.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT32         BiosLessThan1MB;
  UINT32         HiPmmMemory;
  UINT32         HiPmmMemorySizeInBytes;
  UINT16         ReverseThunkCallSegment;
  UINT16         ReverseThunkCallOffset;
  UINT32         NumberE820Entries;
  UINT32         OsMemoryAbove1Mb;
  UINT32         ThunkStart;
  UINT32         ThunkSizeInBytes;
  UINT32         LowPmmMemory;
  UINT32         LowPmmMemorySizeInBytes;
} EFI_TO_COMPATIBILITY16_INIT_TABLE;

//****************************************************
// CSM16 related equates
//****************************************************
// misc_info bits
#define CSM16_HEADLESS_INT19_RETRY_BIT  0x80
#define CSM16_I19_TRAP_BIT              0x40
#define CSM16_I13_HDD_MBR_WP_BIT        0x20
#define CSM16_NO_USB_BOOT_BIT           0x10
#define CSM16_NO_KBC_PRESENT_BIT        0x08
#define CSM16_ZIP_HDD_EMUL_BIT          0x04
#define CSM16_FLEXBOOT_ENABLE_BIT       0x02
#define CSM16_FLEXBOOT_ENABLE_SHIFT_CNT 1
#define CSM16_FAST_GATE_A20_BIT         0x01

// rt_cmos_byte bits
#define CSM_RT_CMOS_LTE_PONR_BIT        0x02
#define CSM_RT_CMOS_PARITY_BIT          0x08
#define CSM_RT_CMOS_SKIP_GA20_DEACTIVATION_BIT  0x10
#define CSM_RT_CPU_RM_ONBOOT_BIT        0x20
#define CSM_RT_CMOS_PS2_BIT             0x40
#define CSM_RT_CMOS_LTE_BIT             0x80

//****************************************************
// ACPI timer 
//****************************************************
#define ACPI_TMR_SIGNATURE              0x544D // Signature used is 'TM'
#define ACPI_TMR_WIDTH_SHIFT            31
#define ACPI_TMR_SIGNATURE_SHIFT        16

//****************************************************
// Type values
//****************************************************
#define STANDARD_IO      0x00
#define STANDARD_MEMORY  0x01

//****************************************************
// PortGranularity values
//****************************************************
#define  PORT_SIZE_8     0x00
#define  PORT_SIZE_16    0x01
#define  PORT_SIZE_32    0x02
#define  PORT_SIZE_64    0x03

//****************************************************
// DataGranularity values
//****************************************************
#define  DATA_SIZE_8     0x00
#define  DATA_SIZE_16    0x01
#define  DATA_SIZE_32    0x02
#define  DATA_SIZE_64    0x03

#define EFI_SEGMENT(_Adr) (UINT16)((UINT16) (((UINTN)(_Adr)) >> 4) & 0xf000)
#define EFI_OFFSET(_Adr)  (UINT16)(((UINT16)((UINTN)_Adr)) & 0xffff)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        SMM_FUNCTION
//
// Fields:
//  Function	UINT16 Function this Soft SMI is to initiate
//  Owner		UINT16 The definer of the function
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
   UINT16            Function          : 15;
   UINT16            Owner             : 1;
} SMM_FUNCTION;


//****************************************************************************
// Function values
//****************************************************************************
#define  INT15_D042           0x0000
#define  GET_USB_BOOT_INFO    0x0001
#define  DMI_PNP_50_57        0x0002
//
// Following is a description of the fields in the above definition.
//
// INT15_D042 -         System Configuration Data functions accessed via INT15 AX=0xD042.
// GET_USB_BOOT_INFO -  Retrieves USB boot device information for integration with BBS.
//  DMI_PNP_50_57 -     Process the DMI Plug and Play functions 0x50 through
//                      0x57 via SMM code.
//  The other values are reserved for future use.
//

//****************************************************************************
// Owner values
//****************************************************************************
#define  STANDARD_OWNER       0x0
#define  OEM_OWNER            0x1
//
// Following is a description of the fields in the above definition.
//
// STANDARD_OWNER - This document has defined the function.
// OEM_OWNER -      An agent, other than this document, has defined the function.
//

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    SMM_ATTRIBUTES
//
// Fields:
//  Type            UINT16 Access mechanism used to generate the soft SMI
//  PortGranularity UINT16 Size of "port" in bits
//  DataGranularity UINT16 Size of data in bits
//  Reserved        UINT16 Reserved for future use
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
   UINT16            Type              : 3;
   UINT16            PortGranularity   : 3;
   UINT16            DataGranularity   : 3;
   UINT16            Reserved          : 7;
} SMM_ATTRIBUTES;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    SMM_ENTRY
//
// Fields:
//  SmmAttributes   SMM_ATTRIBUTES Describes the access mechanism, SmmPort, and SmmData sizes
//  SmmFunction     SMM_FUNCTION Function Soft SMI is to perform
//  SmmPort	        UINT16 SmmPort size depends upon SmmAttributes and ranges from 2 bytes to 16 bytes
//  SmmData         UINT16 SmmData size depends upon SmmAttributes and ranges from 2 bytes to 16 bytes
//
// Referrals:   SMM_ATTRIBUTES, SMM_FUNCTION
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
   SMM_ATTRIBUTES    SmmAttributes;
   SMM_FUNCTION      SmmFunction;
   UINT16            SmmPort;
   UINT16            SmmData;
} SMM_ENTRY;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        SMM_TABLE
//
// Description:  SMM Table definitions; SMM table has a header that provides
//              the number of entries. Following the header is a variable
//              length amount of data.
// Fields:
//  NumSmmEntries   UINT16 Number of entries represented by SmmEntry
//  SmmEntry        SMM_ENTRY One entry per function
//
// Referrals:   SMM_ENTRY
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT16            NumSmmEntries;
  SMM_ENTRY         SmmEntry;
} SMM_TABLE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        LEGACY_DEVICE_FLAGS
//
// Fields:
//  A20Kybd     UINT32:1 A20 controller by keyboard controller.
//  A20Port92   UINT32:1 A20 controlled by port 0x92.
//  Reserved    UINT32:30 Reserved for future usage.
//
// Notes:   A20Kybd and A20Port92 are not mutually exclusive.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT32        A20Kybd:1;
  UINT32        A20Port92:1;
  UINT32        Reserved:30;
} LEGACY_DEVICE_FLAGS;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        DEVICE_PRODUCER_FLOPPY
//
// Fields:
//  Address         UINT16 I/O address assigned to the floppy
//  Irq             UINT8 IRQ assigned to the floppy.
//  Dma             UINT8 DMA assigned to the floppy.
//  NumberOfFloppy  UINT8 Number of floppies in the system.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT16          Address;
  UINT8           Irq;
  UINT8           Dma;
  UINT8           NumberOfFloppy;
} DEVICE_PRODUCER_FLOPPY;

typedef enum {FLOPPY_INSERTED, NO_FLOPPY_DISK, NO_FLOPPY_DRIVE} FDD_STATUS;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    DEVICE_PRODUCER_PARALLEL
//
// Fields:
//  Address UINT16 I/O address assigned to the parallel port
//  Irq     UINT8  IRQ assigned to the parallel port.
//  Dma     UINT8  DMA assigned to the parallel port.
//  Mode    PARALLEL_MODE Mode of the parallel port.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

//****************************************************************************
// Parallel Mode values
//****************************************************************************
#define DEVICE_PARALLEL_MODE_MODE_OUTPUT_ONLY    0x00
#define DEVICE_PARALLEL_MODE_MODE_BIDIRECTIONAL  0x01
#define DEVICE_PARALLEL_MODE_MODE_EPP            0x02
#define DEVICE_PARALLEL_MODE_MODE_ECP            0x03

typedef UINT8 PARALLEL_MODE;

typedef struct {
  UINT16          Address;
  UINT8           Irq;
  UINT8           Dma;
  PARALLEL_MODE   Mode;
} DEVICE_PRODUCER_PARALLEL;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        DEVICE_PRODUCER_SERIAL
//
// Fields:
//  Address     UINT16 I/O address assigned to the serial port
//  Irq         UINT8 IRQ assigned to the serial port
//  Mode        SERIAL_MODE Mode of serial port
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

//****************************************************************************
// Serial Mode values
//****************************************************************************
#define DEVICE_SERIAL_MODE_NORMAL                0x00
#define DEVICE_SERIAL_MODE_IRDA                  0x01
#define DEVICE_SERIAL_MODE_ASK_IR                0x02
#define DEVICE_SERIAL_MODE_DUPLEX_HALF           0x00
#define DEVICE_SERIAL_MODE_DUPLEX_FULL           0x10

typedef UINT8 SERIAL_MODE;
typedef struct {
  UINT16          Address;
  UINT8           Irq;
  SERIAL_MODE     Mode;
} DEVICE_PRODUCER_SERIAL;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        DEVICE_PRODUCER_DATA_HEADER
//
// Fields:
//  Serial      DEVICE_PRODUCER_SERIAL      Data for serial port x
//  Parallel    DEVICE_PRODUCER_PARALLEL    Data for parallel port x
//  Floppy      DEVICE_PRODUCER_FLOPPY      Data for floppy
//  MousePresent    UINT8   Flag to indicate if mouse is present
//  Flags       LEGACY_DEVICE_FLAGS         Miscellaneous Boolean state information passed to CSM
//
// Referrals:   DEVICE_PRODUCER_SERIAL, DEVICE_PRODUCER_PARALLEL,
//              DEVICE_PRODUCER_FLOPPY, LEGACY_DEVICE_FLAGS
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  DEVICE_PRODUCER_SERIAL    Serial[4];
  DEVICE_PRODUCER_PARALLEL  Parallel[3];
  DEVICE_PRODUCER_FLOPPY    Floppy;
  UINT8                     MousePresent;
  LEGACY_DEVICE_FLAGS       Flags;
} DEVICE_PRODUCER_DATA_HEADER;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_TO_COMPATIBILITY16_BOOT_TABLE
//
// Description:  Data structure passed to Compatibility16InitializeYourself
//              function.
// Fields:
//  MajorVersion    UINT16 The EfiCompatibility major version number.
//  MinorVersion    UINT16 The EfiCompatibility minor version number.
//  AcpiTable       UINT32 Location of the RSDT ACPI table.
//  SmbiosTable     UINT32 Location of the SMBIOS table in EFI memory.
//  SmbiosTableLength   UINT32 Length of the SMBIOS table in bytes.
//  SioData         DEVICE_PRODUCER_DATA_HEADER Standard traditional device information.
//  DevicePathType  UINT16 The default boot type. See notes for details.
//  PciIrqMask      UINT16 Mask of which IRQs have been assigned to PCI.
//  NumberE820Entries   UINT32 Number of E820 entries.
//  HddInfo         HDD_INFO Hard disk drive information, including raw Identify Drive data.
//  NumberBbsEntries    UINT32 Number of entries in the BBS table
//  BbsTable        UINT32 Pointer to the BBS table.
//  SmmTable        UINT32 Pointer to the SMM table.
//  OsMemoryAbove1Mb    UINT32 The amount of usable memory above 1 MB, i.e. E820 type 1 memory.
//  UnconventionalDeviceTable   UINT32 Information to boot off an unconventional device like a PARTIES partition.
//
// Referrals:   Compatibility16InitializeYourself, EFI_TO_COMPATIBILITY16_INIT_TABLE, HDD_INFO
//
// Notes: Following are the defined DevicePathType values:
//          FD = Floppy
//          HD = Hard Disk
//          CDROM = CD-ROM
//          PCMCIA = PCMCIA
//          USB = USB
//          NET = Networks
//          BEV = BBS BEV devices
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
//#define MAX_IDE_CONTROLLER 8
#define MAX_IDE_CONTROLLER 12
struct _UD_TABLE;

typedef struct {
  UINT16             MajorVersion;
  UINT16             MinorVersion;

  UINT32             AcpiTable;         // 4 GB range
  UINT32             SmbiosTable;       // 4 GB range
  UINT32             SmbiosTableLength;
  //
  // Legacy SIO state
  //
  DEVICE_PRODUCER_DATA_HEADER    SioData;
  UINT16             DevicePathType;
  UINT16             PciIrqMask;
  UINT32             NumberE820Entries;
  //
  // Controller & Drive Identify[2] per controller information
  //
  HDD_INFO           HddInfo[MAX_IDE_CONTROLLER];
  UINT32             NumberBbsEntries;
  UINT32             BbsTable;
  UINT32             SmmTable;
  UINT32             OsMemoryAbove1Mb;
  UINT32             UnconventionalDeviceTable;
} EFI_TO_COMPATIBILITY16_BOOT_TABLE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_LEGACY_INSTALL_PCI_HANDLER
//
// Fields:
//  PciBus              UINT8 The PCI bus of the device.
//  PciDeviceFun        UINT8 The PCI device in bits 7:3 and function in bits 2:0.
//  PciSegment          UINT8 The PCI segment of the device.
//  PciClass            UINT8 The PCI class code of the device.
//  PciSubclass         UINT8 The PCI subclass code of the device.
//  PciInterface        UINT8 The PCI interface code of the device.
//  PrimaryIrq          UINT8 The primary device IRQ.
//  PrimaryReserved     UINT8 Reserved.
//  PrimaryControl      UINT16 The primary device control I/O base.
//  PrimaryBase         UINT16 The primary device I/O base.
//  PrimaryBusMaster    UINT16 The primary device bus master I/O base.
//  SecondaryIrq        UINT8 The secondary device IRQ.
//  SecondaryReserved   UINT8 Reserved.
//  SecondaryControl    UINT16 The secondary device control I/O base.
//  SecondaryBase       UINT16 The secondary device I/O base.
//  SecondaryBusMaster  UINT16 The secondary device bus master I/O base.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT8              PciBus;
  UINT8              PciDeviceFun;
  UINT8              PciSegment;
  UINT8              PciClass;
  UINT8              PciSubclass;
  UINT8              PciInterface;
  //
  // Primary section
  //
  UINT8              PrimaryIrq;
  UINT8              PrimaryReserved;
  UINT16             PrimaryControl;
  UINT16             PrimaryBase;
  UINT16             PrimaryBusMaster;
  //
  // Secondary section
  //
  UINT8              SecondaryIrq;
  UINT8              SecondaryReserved;
  UINT16             SecondaryControl;
  UINT16             SecondaryBase;
  UINT16             SecondaryBusMaster;
} EFI_LEGACY_INSTALL_PCI_HANDLER;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_DISPATCH_OPROM_TABLE
//
// Fields:
//  PnpInstallationCheckSegment UINT16 Segment of the PnpInstallationCheck data structure.
//  PnpInstallationCheckOffset  UINT16 Offset of the PnpInstallationCheck data structure.
//  OpromSegment    UINT16 The segment where the OpROM was placed. Offset is assumed to be 3.
//  PciBus          UINT8 The PCI bus.
//  PciDeviceFunction   UINT8 The PCI device * 0x08 | PCI function.
//  NumberBbsEntries    UINT8   The number of valid BBS table entries upon entry and exit.
//  BbsTable            UINT32  Pointer to the BBS table.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
#define MAX_EXECUTED_OPROMS 32

typedef struct {
   IN UINT16               PnpInstallationCheckSegment;
   IN UINT16               PnpInstallationCheckOffset;
   IN UINT16               OpromSegment;
   IN UINT8                PciBus;
   IN UINT8                PciDeviceFunction;
   IN OUT UINT8            NumberBbsEntries;
   UINT32                  BbsTable;
   IN UINT16               FinalLocationSegment;
} EFI_DISPATCH_OPROM_TABLE;

typedef struct {
   UINTN        Seg;
   UINTN        Bus;
   UINTN        Dev;
   UINTN        Fun;
   UINTN        Flags;
   UINT8        DiskFrom;
   UINT8        DiskTo;
   VOID         *RomAddress;
   UINT32       RomSize;
} EXECUTED_PCI_ROM;

BOOLEAN Int86 (
    IN EFI_LEGACY_BIOS_PROTOCOL   *This,
    IN  UINT8                     BiosInt,
    IN  EFI_IA32_REGISTER_SET     *Regs
);

BOOLEAN FarCall86 (
  IN EFI_LEGACY_BIOS_PROTOCOL     *This,
  IN  UINT16                      Segment,
  IN  UINT16                      Offset,
  IN  EFI_IA32_REGISTER_SET       *Regs,
  IN  VOID                        *Stack,
  IN  UINTN                       StackSize
);

EFI_STATUS CheckPciRom (
  IN EFI_LEGACY_BIOS_PROTOCOL     *This,
  IN  EFI_HANDLE                  PciHandle,
  OUT VOID                        **RomImage, OPTIONAL
  OUT UINTN                       *RomSize,   OPTIONAL
  OUT UINTN                       *Flags
);

EFI_STATUS InstallPciRom (
  IN EFI_LEGACY_BIOS_PROTOCOL      *This,
  IN  EFI_HANDLE                   PciHandle,
  IN  VOID                         **RomImage,
  OUT UINTN                        *Flags,
  OUT UINT8                        *DiskStart, OPTIONAL
  OUT UINT8                        *DiskEnd, OPTIONAL
  OUT VOID                         **RomShadowAddress, OPTIONAL
  OUT UINT32                       *ShadowedRomSize OPTIONAL
);

EFI_STATUS
ShadowAllLegacyOproms (
    IN EFI_LEGACY_BIOS_PROTOCOL *This
);

EFI_STATUS FindEmbeddedRom(
    UINT16 ModuleId, UINT16 VendorId, UINT16 DeviceId,
    VOID **ImageStart, UINTN *ImageSize
);

EFI_STATUS
GetLegacyRegion (
  IN EFI_LEGACY_BIOS_PROTOCOL          *This,
  IN UINTN                             LegacyMemorySize,
  IN UINTN                             Region,
  IN UINTN                             Alignment,
  OUT VOID                             **LegacyMemoryAddress
);

EFI_STATUS
CopyLegacyRegion (
  IN EFI_LEGACY_BIOS_PROTOCOL          *This,
  IN UINTN                             LegacyMemorySize,
  IN VOID                              *LegacyMemoryAddress,
  IN VOID                              *LegacyMemorySourceAddress
);

EFI_STATUS
UnlockShadow(
    IN UINT8    *Address,
    IN UINTN    Size,
    OUT UINT32  *LockUnlockAddr,
    OUT UINT32  *LockUnlockSize
);

EFI_STATUS
LockShadow(
    IN UINT32  LockAddr,
    IN UINT32  LockSize
);

EFI_STATUS
RemoveDecodingForShadow(
    IN UINT32  DecodeAddr
);
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        AMIIRQ_HEADER
//
// Description: AMI IRQ Routing Table Header Structure
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
    UINT32  dSignature;         // '$IRT' signature
    UINT8   bTotalEntries;      // total number of slot entries present in the table
    UINT8   bUsedEntries;       // number of used slot entries in the table
    UINT16  wExclusiveIRQ;      // bitmap of IRQs used exclusively for PCI
    UINT32  dPtrIRQSlotStart;   // pointer to start of IRQ slot entries
} AMIIRQ_HEADER;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_ADDON_PCIBUS_TABLE
//
// Description: Table that holds the information about the buses generated by
//              P2P bridges that are not listed in $PIR table
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT8                    Bus;
  EFI_LEGACY_PIRQ_ENTRY    PirqEntry[4];
} EFI_ADDON_PCIBUS_TABLE;


//**********************************************************************
//
// The following sections is a list of the CSM16 APIs. They do not
// require definitions and given here for reference only. (And of course
// these headers could be used to prepare the interactive help file.)
//
//**********************************************************************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: Compatibility16InitializeYourself (Function 0)
//
// Description: Causes the Compatibility16 code to do any internal initialization
//              required.  The EFI_TO_COMPATIBILITY16_INIT_TABLE pointer is passed
//              into this function.
// Input:
//  AX = Compatibility16InitializeYourself
//  ES:BX = Pointer to EFI_TO_COMPATIBILITY16_INIT_TABLE
//
// Output: Status Codes Returned
//
// Referrals:   EFI_TO_COMPATIBILITY16_INIT_TABLE, EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: Compatibility16UpdateBbs (Function 1)
//
// Description: Causes the Compatibility16 BIOS to perform any drive number
//              translations to match the boot sequence.
// Input:
//  AX = Compatibility16UpdateBbs
//  ES:BX = Pointer to EFI_TO_COMPATIBILITY16_BOOT_TABLE
//
// Output: Status Codes Returned
//          EFI_SUCCESS 0x0000
//
// Referrals:   EFI_TO_COMPATIBILITY16_BOOT_TABLE, EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: Compatibility16PrepareToBoot (Function 2)
//
// Description: Allows the Compatibility16 code to perform any final actions
//              before booting.  The Compatibility16 code is read/write.
// Input:
//  AX = Compatibility16PrepareToBoot
//  ES:BX = Pointer to EFI_TO_COMPATIBILITY16_BOOT_TABLE structure
//
// Output: Status Codes Returned
//
// Referrals:   EFI_TO_COMPATIBILITY16_BOOT_TABLE, DEVICE_PRODUCER_DATA_HEADER
//              HDD_INFO, BBS_TABLE, BBS_STATUS_FLAGS, SMM_TABLE, UD_TABLE,
//              UDC_ATTRIBUTES, EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    Compatibility16Boot (Function 3)
//
// Description: Causes the Compatibility16 BIOS to boot. The Compatibility16
//              code is Read/Only.
// Input:   AX = Compatibility16Boot
//
// Output: Status Codes Returned
//
// Referrals:   EFI_TO_COMPATIBILITY16_BOOT_TABLE, EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        Compatibility16RetrieveLastBootDevice (Function 4)
//
// Description: Allows the Compatibility16 code to get the last device from
//              which a boot was attempted.  This is stored in CMOS and is
//              the priority number of the last attempted boot device.
//
// Input:       AX = Compatibility16RetrieveLastBootDevice
//
// Output:      AX = Returned status codes:
//                  EFI_SUCCESS 0x0000
//                  EFI_ABORTED 0x8015
//              BX = Priority number of the boot device
//
// Referrals:   EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        Compatibility16DispatchOprom (Function 5)
//
// Description: Allows the Compatibility16 code rehook INT13, INT18, and/or
//              INT19 after dispatching a legacy OpROM.
// Input:       AX = Compatibility16DispatchOprom
//              ES:BX = Pointer to EFI_DISPATCH_OPROM_TABLE
//
// Output:      AX =  Returned status codes
//              BX = Number of non-BBS-compliant devices found. Equals 0 if
//              BBS compliant.
//
// Referrals:   EFI_DISPATCH_OPROM_TABLE, EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        Compatibility16GetTableAddress (Function 6)
//
// Description: Finds a free area in the 0xFxxxx or 0xExxxx region of the
//              specified length and returns the address of that region.
// Input:       AX = Compatibility16GetTableAddress
//              BX = Allocation region
//                  00 = Allocate from either 0xE0000 or 0xF0000 64 KB blocks.
//                  Bit 0 = 1 Allocate from 0xF0000 64 KB block
//                  Bit 1 = 1 Allocate from 0xE0000 64 KB block
//              CX = Requested length in bytes.
//              DX = Required address alignment. Bit mapped. First non-zero bit
//              from the right is the alignment.
//
// Output:      AX = Returned status codes:
//                  EFI_SUCCESS 0x0000
//                  EFI_OUT_OF_RESOURCES    0x8009
//              DS:BX = Address of the region
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        Compatibility16SetKeyboardLeds (Function 7)
//
// Description: Enables the EfiCompatibility module to do any nonstandard
//              processing of keyboard LEDs or state.
// Input:       AX = Compatibility16SetKeyboardLeds
//              CL = LED status:
//                  Bit 0 - Scroll Lock         0 = Off
//                  Bit 1 - Num Lock
//                  Bit 2 - Caps Lock
// Output:      Status Codes Returned
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        Compatibility16InstallPciHandler (Function 8)
//
// Description: Enables the EfiCompatibility module to install an interrupt
//              handler for PCI mass media devices that do not have an OpROM
//              associated with them. An example is SATA
//
// Input:       AX = Compatibility16InstallPciHandler
//              ES:BX = Pointer to EFI_LEGACY_INSTALL_PCI_HANDLER structure
//
// Output: Status Codes Returned
//
// Referrals:   EFI_LEGACY_INSTALL_PCI_HANDLER
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#define MAX_DRIVE_NAME 32

typedef struct _DRIVE_DISPLAY_NAME {
    UINT8   DriveName[MAX_DRIVE_NAME];
} DRIVE_DISPLAY_NAME;

typedef struct _IDE_CONTROLLER_INFO_STRUC {
    UINT16      BusDevFun;                  // Bus, Device and Function number
    UINT8       ControllerNo;               // Controller number for IDE controller
} IDE_CONTROLLER_INFO_STRUC;

typedef struct {
    UINT8   ThunkCode[0x4000];              // 12KB = 4KB of code + 8KB of stack
    UINT8   InterruptRedirectionCode[24];   // 3 bytes of code per interrupt
    EFI_TO_COMPATIBILITY16_INIT_TABLE   Csm16InitTable;
    EFI_TO_COMPATIBILITY16_BOOT_TABLE   Csm16BootTable;
    EFI_LEGACY_INSTALL_PCI_HANDLER  PciHandler;
    EFI_DISPATCH_OPROM_TABLE        DispatchOpromTable;
    DRIVE_DISPLAY_NAME DriveDisplayName[2*MAX_IDE_CONTROLLER];
} THUNK_MEMORY;

#define MAX_E820_ENTRIES 256
typedef enum {
    MemRangeAvl         = 1,
    MemRangeRes         = 2,
    MemRangeAcpiReclaim = 3,
    MemRangeAcpiNVS     = 4
} E820_MEMORY_TYPE;

#define E820_EXTATTR_ADDRESS_RANGE_ENABLED 1
#define E820_EXTATTR_ADDRESS_RANGE_NONVOLATILE 2
typedef struct {
    UINT64              Adr;
    UINT64              Len;
    E820_MEMORY_TYPE    Type;
    UINT32              ExtendedAttr;
} E820_ENTRY;

#define PMM_TABLE_SIZE 0x1000
#define PMM_SYSTEM_HANDLE 0x24494D41        // Handle used by AMIBIOS 'AMI$'
#define EFI_MEMORY_HANDLE 0x24494645        // Handle used by EFI Memory 'EFI$'
typedef struct {
    UINT32              StartAddress;       // Start address of the memory block
    UINT32              Size;               // Size of the memory block in bytes
    UINT32              Handle;             // Associated handle
    UINT8               Reserved[4];        // Reserved for future use
} MEMORY_ALLOCATION_ENTRY;

typedef struct {
    UINT32              Signature;
    UINT8               Revision;
    UINT8               Length;
    UINT16              NextHeaderOffset;
    UINT8               Reserved;
    UINT8               Checksum;
    UINT32              DevId;
    UINT16              MfgPtr;
    UINT16              ProductNamePtr;
    UINT8               Class;
    UINT8               SubClass;
    UINT8               Interface;
    UINT8               DevIndicators;
    UINT16              BCV;
    UINT16              DisconnectVector;
    UINT16              BEV;
    UINT16              Reserved1;
    UINT16              StaticResourceVector;
} PCI_PNP_EXPANSION_HEADER;

#define MAX_BCV_OPROMS  32
typedef struct {
    UINT8   *Address;
    UINT8   *Data;
    UINT8   *rtData;
    UINT8   *rtDataAddr;
    UINT32  rtDataSize;
    BOOLEAN isEbda;
    UINT32  ebdaOffset;
} SAVED_PCI_ROM;

typedef struct {
    UINT8   irq_num;
    UINT32  irq_adr;
} IVT_SAVE_RESTORE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    BIOS_INFO
//
// Description:
//  This structure is not specified in CSM specification. It defines the useful 
//  fields for the global variable to be used throughout POST.
//
// Fields:
//  iBios           EFI_LEGACY_BIOS_PROTOCOL    LegacyBios instance pointer
//  iRegion         EFI_LEGACY_REGION_PROTOCOL  LegacyRegion instance pointer
//  iBiosPlatform   EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   LegacyPlatform instance pointer
//  iInterrupt      EFI_LEGACY_INTERRUPT_PROTOCOL   LegacyInterrupt instance pointer
//  i8259           EFI_LEGACY_8259_PROTOCOL    Legacy8259 instance pointer
//  hBios           EFI_HANDLE 
//  hImage          EFI_HANDLE  This driver LoadedImage handle 
//  hVga            EFI_HANDLE  Video controller handle
//  Csm16Header     EFI_COMPATIBILITY16_TABLE   Pointer to CSM16 header
//  Thunk           THUNK_MEMORY    Pointer to thunk memory area
//  Csm16EntrySeg   UINT16          CSM16 entry point segment
//  Csm16EntryOfs   UINT16          CSM16 entry point offset
//  BbsTable        BBS_TABLE       BBS table pointer
//  BbsEntriesNo    UINT8           Number of BBS entries
//  HddCount        UINT8           Number of hard disks in the system
//  E820Map         E820_ENTRY      E820 memory map entries
//  NumberE820Entries   UINT16      Number of E820 entries populated
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
    EFI_LEGACY_BIOS_PROTOCOL            iBios;
    EFI_LEGACY_REGION_PROTOCOL          *iRegion;
    EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *iBiosPlatform;
    EFI_LEGACY_INTERRUPT_PROTOCOL       *iInterrupt;
    EFI_LEGACY_8259_PROTOCOL            *i8259;
    EFI_HANDLE                          hBios;
    EFI_HANDLE                          hImage;
    EFI_HANDLE                          hVga;
    EFI_COMPATIBILITY16_TABLE           *Csm16Header;
    THUNK_MEMORY                        *Thunk;
    UINT16                              Csm16EntrySeg;
    UINT16                              Csm16EntryOfs;
    BBS_TABLE                           *BbsTable;
    UINT8                               BbsEntriesNo;
    UINT8                               HddCount;
    E820_ENTRY                          E820Map[MAX_E820_ENTRIES];
    UINT16                              NumberE820Entries;
} BIOS_INFO;

typedef struct {
    EFI_HANDLE  hImage;
    EFI_HANDLE  hBios;
    EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   iBiosPlatform;
} PLATFORM_BIOS_INFO;

EFI_STATUS BspUpdatePrt(
  IN  EFI_LEGACY_BIOS_PROTOCOL   *This,
  IN  VOID                       *RoutingTable
);

typedef struct _OEMINT_FUNC {
    UINT16  interrupt;
    UINT16  funcoffset;
} OEMINT_FUNC;

typedef struct _OEM16_FUNC {
    UINT16  funcID;
    UINT16  funcOffset;
} OEM16_FUNC;

typedef struct _LEGACY16_TO_EFI_DATA_TABLE_EXT {
    LEGACY16_TO_EFI_DATA_TABLE_STRUC    PublicData;
    UINT16  RbMinBusArrayOfs;
    UINT8   RbArrayCount;
} LEGACY16_TO_EFI_DATA_TABLE_EXT;

typedef struct {
    struct {
        UINT16  Offset;
        UINT16  Segment;
    } FarCall;
    EFI_IA32_REGISTER_SET   Regs;
    struct {
        UINT32  Stack;
        UINT32  StackSize;
    } StackData;
    BOOLEAN     isFarCall;  //if false, then INT86.
    UINT8       BiosInt;
} AMI_CSM_THUNK_DATA;

EFI_STATUS  Get16BitFuncAddress (UINT16, UINT32*);
UINTN       CopyLegacyTable(VOID*, UINT16, UINT16, UINT16);
EFI_STATUS  GetEmbeddedRom(UINT16, UINT16, UINT16, VOID**, UINTN*);
EFI_STATUS  GetBbsTable (BBS_TABLE**, UINT8*);
EFI_STATUS  AddBbsEntry(BBS_TABLE*);
EFI_STATUS  InsertBbsEntryAt(EFI_LEGACY_BIOS_EXT_PROTOCOL*, BBS_TABLE*, UINT8*);
EFI_STATUS  RemoveBbsEntryAt(EFI_LEGACY_BIOS_EXT_PROTOCOL*, UINT8);
EFI_STATUS  AllocateEbda(EFI_LEGACY_BIOS_EXT_PROTOCOL*, UINT8, UINT32*, UINT32*);
EFI_STATUS  UnlockShadow(UINT8*, UINTN, UINT32*, UINT32*);
EFI_STATUS  LockShadow(UINT32, UINT32);
EFI_STATUS  InitCompatibility16(BIOS_INFO*, EFI_SYSTEM_TABLE*);
EFI_STATUS  InitializeThunk(BIOS_INFO*);
EFI_STATUS  InitializeLegacyMemory(BIOS_INFO*);
EFI_STATUS  PrepareToBoot(EFI_LEGACY_BIOS_PROTOCOL*, UINT16*, struct _BBS_TABLE**);
EFI_STATUS  LegacyBoot(EFI_LEGACY_BIOS_PROTOCOL*, BBS_BBS_DEVICE_PATH*, UINT32, VOID*);
EFI_STATUS  GetBbsInfo(EFI_LEGACY_BIOS_PROTOCOL*, UINT16*, HDD_INFO**, UINT16*, BBS_TABLE**);
EFI_STATUS  UpdateKeyboardLedStatus(EFI_LEGACY_BIOS_PROTOCOL*, UINT8);
EFI_STATUS  EnableDisableNmi();
//EFI_STATUS GetAtaAtapiInfo(HDD_INFO**);
VOID        HaltApsBeforeBoot();
VOID        InstallLegacyMassStorageDevices();
VOID        GetExtendedMemSize(UINT32*);
UINT32      UpdateE820Map(E820_ENTRY *);
EFI_STATUS  UpdateCsm16Configuration(EFI_TO_COMPATIBILITY16_BOOT_TABLE*);
EFI_STATUS  InitCsmBoard(EFI_HANDLE, EFI_SYSTEM_TABLE*);
EFI_STATUS  InitCsmSimpleIn(EFI_HANDLE, EFI_SYSTEM_TABLE*);
EFI_STATUS  UpdateCmos();
EFI_STATUS  InitializePortingHooks (BIOS_INFO*);
OEM16_FUNC* InitializeOemInt(UINT16*);
UINTN       InitializeOem16(UINT16*);
FDD_STATUS  GetFDDStatus();
VOID        AllConnectedCallback (EFI_EVENT, VOID*);
EFI_STATUS  GetPlatformEmbeddedRom(UINT16, UINT16, UINT16, VOID**, UINTN*);
EFI_STATUS  GetComPortResource(UINT8, UINT16*, UINT8*);
EFI_STATUS  GetLptResource(UINT16*, UINT8*);
VOID        UpdatePciLastBusCallback(EFI_EVENT, VOID*);
EFI_STATUS  GetPlatformPciEmbeddedRom(EFI_PCI_IO_PROTOCOL*, VOID**, UINTN*);
EFI_STATUS  CheckOemPciSiblings(EFI_PCI_IO_PROTOCOL*, EXECUTED_PCI_ROM*);
EFI_STATUS  EnableOemPciSiblings(EFI_PCI_IO_PROTOCOL*);
EFI_STATUS  InstallIsaRom(EFI_LEGACY_BIOS_EXT_PROTOCOL*, UINTN);
EFI_STATUS  GetShadowRamAddress(UINT32*, UINT32, UINT32, UINT32);

// SD class/subclass defined in PCI.H in 4.6.3.7
#ifndef PCI_CL_SYSTEM_PERIPHERALS
#define PCI_CL_SYSTEM_PERIPHERALS		0x08
#endif
#ifndef PCI_CL_SYSTEM_PERIPHERALS_SCL_SD
#define PCI_CL_SYSTEM_PERIPHERALS_SCL_SD	0x05
#endif

VOID    DisconnectSerialIO();
VOID    ConnectSerialIO();
EFI_STATUS  LockConsole();
EFI_STATUS  UnlockConsole();
BOOLEAN IsAMICSM16(EFI_COMPATIBILITY16_TABLE*);
UINT8   ChecksumCSM16Header(EFI_COMPATIBILITY16_TABLE*);
EFI_STATUS  GetSystemMemoryMap(EFI_MEMORY_DESCRIPTOR**, UINTN*,UINTN*);
EFI_STATUS  ClearFreeMemory(EFI_PHYSICAL_ADDRESS,EFI_PHYSICAL_ADDRESS);
EFI_STATUS  Csm16Configuration(CSM16_CONFIGURATION_ACTION, CSM16_FEATURE, UINT32*);
EFI_STATUS  AllocateHiMemPmmBlock(UINTN, UINTN*);
VOID    FreePmmBeforeBoot (EFI_EVENT, VOID*);

#pragma pack ()
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
