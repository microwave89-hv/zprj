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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/LegacyBios.h 19    3/15/11 3:48p Olegi $
//
// $Revision: 19 $
//
// $Date: 3/15/11 3:48p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/LegacyBios.h $
// 
// 19    3/15/11 3:48p Olegi
// [TAG]  		EIP55913
// [Category]  	Improvement
// [Description]  	Remove LastOpromAddress from EFI_COMPATIBILITY16_TABLE
// structure
// [Files]  		Amilegacy16.bin, LegacyBios.h, LegacyBiosExt.h, Csm.c
// 
// 18    1/12/10 11:51a Olegi
// Copyright message updated.
// 
// 17    6/12/07 10:10a Olegi
// Changed MAX_BBS_ENTRIES_NO from 64 to 256 to comply with EDK protocol
// file.
// 
// 16    4/27/07 5:17p Olegi
// CSM.CHM file preparation.
//
// 15    4/10/07 5:21p Olegi
//
// 14    2/06/07 10:47a Olegi
//
// 13    9/15/06 4:18p Davidd
// Update the EfiSystemTable type in EFI_COMPATIBILITY16_TABLE to UINT32
// per CSM Spec Ver 0.96
//
// 12    8/14/06 10:01a Olegi
//
// 11    5/25/06 2:30p Olegi
//
// 10    3/13/06 2:43p Felixp
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    LegacyBios.h
//
// Description: LegacyBios protocol declaration
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LEGACY_BIOS_PROTOCOL_H__
#define __LEGACY_BIOS_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_LEGACY_BIOS_PROTOCOL_GUID            \
  { 0xdb9a1e3d, 0x45cb, 0x4abb, 0x85, 0x3b, 0xe5, 0x38, 0x7f, 0xdb, 0x2e, 0x2d}

GUID_VARIABLE_DECLARATION(gEfiLegacyBiosProtocolGuid,EFI_LEGACY_BIOS_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/DevicePath.h>
#pragma pack (1)

typedef struct _EFI_LEGACY_BIOS_PROTOCOL EFI_LEGACY_BIOS_PROTOCOL;

#define F0000_BIT       1
#define E0000_BIT       2

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EFI_COMPATIBILITY16_TABLE
//
// Desription:
//  There is a table located within the traditional BIOS in either the 0xF000:xxxx
//  or 0xE000:xxxx physical address range. It is located on a 16-byte boundary and
//  provides the physical address of the entry point for the Compatibility16
//  functions. These functions provide the platform-specific information that is
//  required by the generic EfiCompatibility code. The functions are invoked via
//  thunking by using EFI_LEGACY_BIOS_PROTOCOL.FarCall86() with the 32-bit physical
//  entry point defined below.
//
// Fields:
//  Signature       UINT32  The string "$EFI"
//  TableChecksum   UINT8   The value required such that byte checksum of TableLength equals zero.
//  TableLength     UINT8   The length of this table.
//  EfiMajorRevision UINT8  The major EFI revision for which this table was generated.
//  EfiMinorRevision UINT8  The minor EFI revision for which this table was generated.
//  TableMajorRevision UINT8    The major revision of this table.
//  TableMinorRevision UINT8    The minor revision of this table.
//  Reserved           UINT16   Reserved for future usage.
//  Compatibility16CallSegment  UINT16  The segment of the entry point.
//  Compatibility16CallOffset   UINT16  The offset of the entry point.
//  PnPInstallationCheckSegment UINT16  The segment of the PnP installation check structure.
//  PnPInstallationCheckOffset  UINT16  The offset of the PnP installation check structure.
//  EfiSystemTable      UINT32  The address of the EFI system resources table.
//  OemIdStringPointer  UINT32  The address of an OEM-provided identifier string, 0-terminated.
//  AcpiRsdPtrPointer   UINT32  The 32-bit physical address where ACPI RSD PTR is stored.
//  OemRevision         UINT16  The OEM revision number. Usage is undefined.
//  E820Pointer         UINT32  The 32-bit physical address where INT15 E820 data is stored.
//  E820Length          UINT32  The length of the E820 data and is filled in by the EfiCompatibility code.
//  IrqRoutingTablePointer UINT32 The 32-bit physical address where the $PIR table is stored.
//  IrqRoutingTableLength  UINT32 The length of the $PIR table and is filled in by the EfiCompatibility code.
//  MpTablePtr      UINT32  The 32-bit physical address where the MP table is stored.
//  MpTableLength   UINT32  The length of the MP table and is filled in by the EfiCompatibility code.
//  OemintSegment   UINT16  The segment of the OEM-specific INT  table/code.
//  OemIntOffset    UINT16  The offset of the OEM-specific INT  table/code.
//  Oem32Segment    UINT16  The segment of the OEM-specific 32-bit table/code.
//  Oem32Offset     UINT16  The offset of the OEM-specific 32-bit table/code.
//  Oem16Segment    UINT16  The segment of the OEM-specific 16-bit table/code.
//  Oem16Offset     UINT16  The offset of the OEM-specific 16-bit table/code.
//  TpmSegment      UINT16  The segment of the TPM binary passed to 16-bit CSM.
//  TpmOffset       UINT16  The offset of the TPM binary passed to 16-bit CSM.
//  IbvPointer      UINT32  A pointer to a string identifying the independent BIOS vendor.
//  PciExpressBase  UINT32  This field is the base value of the start of the PCI Express memory-mapped configuration registers.
//  LastpciBus      UINT8   Maximum PCI bus number assigned.
//  LastOpromAddress    UINT32  The last address that can be occupied by the Option ROM.
//
// Notes:
//  1) The string "$EFI" denotes the start of the EfiCompatibility table. Byte 0 is
//  "I," byte 1 is "F," byte 2 is "E," and byte 3 is "$" and is normally accessed
//  as a DWORD or UINT32.
//  2) The E820Pointer, IrqRoutingTablePointer, and MpTablePtr values are generated
//  by calling the Compatibility16GetTableAddress() function and converted to
//  32-bit physical pointers.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _EFI_COMPATIBILITY16_TABLE {
  UINT32                    Signature;
  UINT8                     TableChecksum;
  UINT8                     TableLength;
  UINT8                     EfiMajorRevision;
  UINT8                     EfiMinorRevision;
  UINT8                     TableMajorRevision;
  UINT8                     TableMinorRevision;
  UINT16                    Reserved;
  UINT16                    Compatibility16CallSegment;
  UINT16                    Compatibility16CallOffset;
  UINT16                    PnPInstallationCheckSegment;
  UINT16                    PnPInstallationCheckOffset;
  UINT32                    EfiSystemTable;
  UINT32                    OemIdStringPointer;
  UINT32                    AcpiRsdPtrPointer;
  UINT16                    OemRevision;
  UINT32                    E820Pointer;
  UINT32                    E820Length;
  UINT32                    IrqRoutingTablePointer;
  UINT32                    IrqRoutingTableLength;
  UINT32                    MpTablePtr;
  UINT32                    MpTableLength;
  UINT16                    OemIntSegment;
  UINT16                    OemIntOffset;
  UINT16                    Oem32Segment;
  UINT16                    Oem32Offset;
  UINT16                    Oem16Segment;
  UINT16                    Oem16Offset;
  UINT16                    TpmSegment;
  UINT16                    TpmOffset;
  UINT32                    IbvPointer;
  UINT32                    PciExpressBase;
  UINT8                     LastPciBus;
} EFI_COMPATIBILITY16_TABLE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    HDD_INFO
//
// Fields:
//  Status UINT16   Status of IDE device. See Notes for details.
//  Bus     UINT32  PCI bus of IDE controller.
//  Device  UINT32  PCI device of IDE controller.
//  Function            UINT32  PCI function of IDE controller.
//  CommandBaseAddress  UINT16  Command ports base address.
//  ControlBaseAddress  UINT16  Control ports base address.
//  BusMasterAddress    UINT16  Bus master address.
//  IdentifyDrive       ATAPI_IDENTIFY  Data that identifies the drive data.
//
// Notes:
//  The values for the Status field are the following:
//      HDD_PRIMARY              0x01
//      HDD_SECONDARY            0x02
//      HDD_MASTER_ATAPI         0x04
//      HDD_SLAVE_ATAPI          0x08
//      HDD_MASTER_IDE           0x20
//      HDD_SLAVE_IDE            0x40
//      HDD_SATA_PATA            0x80
//  There is one HDD_INFO structure per IDE controller. The IdentifyDrive is
//  one per drive. Index 0 is master and index 1 is slave.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _ATAPI_IDENTIFY {
  UINT16    Raw[256];
} ATAPI_IDENTIFY;

//*************************************************
// IDE device status values
//*************************************************

#define HDD_PRIMARY              0x01
#define HDD_SECONDARY            0x02
#define HDD_MASTER_ATAPI         0x04
#define HDD_SLAVE_ATAPI          0x08
#define HDD_MASTER_IDE           0x20
#define HDD_SLAVE_IDE            0x40
#define HDD_SATA_PATA            0x80

typedef struct _HDD_INFO {
  UINT16                    Status;
  UINT32                    Bus;
  UINT32                    Device;
  UINT32                    Function;
  UINT16                    CommandBaseAddress;
  UINT16                    ControlBaseAddress;
  UINT16                    BusMasterAddress;
  UINT8                     HddIrq;
  ATAPI_IDENTIFY            IdentifyDrive[2];
} HDD_INFO;


//****************************************************
// BBS related definitions
//****************************************************

//
// BootPriority values
//
#define BBS_DO_NOT_BOOT_FROM        0xFFFC
#define BBS_LOWEST_PRIORITY         0xFFFD
#define BBS_UNPRIORITIZED_ENTRY     0xFFFE
#define BBS_IGNORE_ENTRY            0xFFFF
//
// Following is a description of the above fields.
//
// BBS_DO_NOT_BOOT_FROM -   Removes a device from the boot list but still
//                          allows it to be enumerated as a valid device
//                          under MS-DOS*.
// BBS_LOWEST_PRIORITY -    Forces the device to be the last boot device.
// BBS_UNPRIORITIZED_ENTRY -    Value that is placed in the BBS_TABLE.BootPriority
//                          field before priority has been assigned but that
//                          indicates it is valid entry.  Other values indicate
//                          the priority, with 0x0000 being the highest priority.
// BBS_IGNORE_ENTRY -       When placed in the BBS_TABLE.BootPriority field,
//                          indicates that the entry is to be skipped.
//

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        BBS_STATUS_FLAGS
//
// Fields:
//  OldPosition UINT16:4    Prior priority.
//  Reserved1   UINT16:4    Reserved for future use.
//  Enabled     UINT16:1    If 0, ignore this entry.
//  Failed      UINT16:1    0-Not known if boot failure occurred; 1-Boot attempt failed.
//  MediaPresent UINT16:2   State of media present, see notes.
//  Reserved2   UINT16:4    Reserved for future use.
//
//  Notes:
//      MediaPresent field details:
//          00 = No bootable media is present in the device.
//          01 = Unknown if a bootable media present.
//          10 = Media is present and appears bootable.
//          11 = Reserved.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT16                   OldPosition : 4;
  UINT16                   Reserved1   : 4;
  UINT16                   Enabled     : 1;
  UINT16                   Failed      : 1;
  UINT16                   MediaPresent: 2;
  UINT16                   Reserved2   : 4;
} BBS_STATUS_FLAGS;



//****************************************************
// DeviceType values
//****************************************************
#define    BBS_FLOPPY        0x01
#define    BBS_HARDDISK      0x02
#define    BBS_CDROM         0x03
#define    BBS_PCMCIA        0x04
#define    BBS_USB           0x05
#define    BBS_EMBED_NETWORK 0x06
#define    BBS_BEV_DEVICE    0x80
#define    BBS_UNKNOWN       0xff



//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    BBS_TABLE
//
// Fields:
//  BootPriority    UINT16 The boot priority for this boot device.
//  Bus         UINT32  The PCI bus for this boot device.
//  Device      UINT32  The PCI device for this boot device.
//  Function    UINT32  The PCI function for the boot device.
//  Class       UINT8   The PCI class for this boot device..
//  SubClass    UINT8   The PCI Subclass for this boot device.
//  MfgString   UINT32  Segment:offset address of an ASCIIZ description.
//  DeviceType  UINT16  BBS device type.
//  StatusFlags BBS_STATUS_FLAGS    Status of this boot device.
//  BootHandler UINT32  Segment:Offset address of boot loader for IPL devices.
//  DescString  UINT32  Segment:offset address of an ASCIIZ description string.
//  InitPerReserved         UINT32  Reserved.
//  AdditionalIrq??Handler  UINT32  See notes for details.
//  AssignedDriveNumber     UINT8   The drive number(0x80 -0x8?) assigned by the 16-bit code.
//  IBV1                    UINT32  IBV specific field.
//  IBV2                    UINT32  IBV specific field.
//
//  Notes:
//      The use of AdditionalIrq??Handler fields is IBV dependent. They can be
//      used to flag that an OpROM has hooked the specified IRQ. The OpROM
//      may be BBS compliant as some SCSI BBS-compliant OpROMs also hook IRQ
//      vectors in order to run their BIOS Setup.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _BBS_TABLE {
  UINT16                BootPriority;
  UINT32                Bus;
  UINT32                Device;
  UINT32                Function;
  UINT8                 Class;
  UINT8                 SubClass;
  UINT16                MfgStringOffset;
  UINT16                MfgStringSegment;
  UINT16                DeviceType;
  BBS_STATUS_FLAGS      StatusFlags;
  UINT16                BootHandlerOffset;
  UINT16                BootHandlerSegment;
  UINT16                DescStringOffset;
  UINT16                DescStringSegment;
  UINT32                InitPerReserved;
  UINT32                AdditionalIrq13Handler;
  UINT32                AdditionalIrq18Handler;
  UINT32                AdditionalIrq19Handler;
  UINT32                AdditionalIrq40Handler;
  UINT8                 AssignedDriveNumber;
  UINT32                AdditionalIrq41Handler;
  UINT32                AdditionalIrq46Handler;
  UINT32                IBV1;
  UINT32                IBV2;
} BBS_TABLE;

#define MAX_BBS_ENTRIES_NO  256

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_IA32_REGISTER_SET
// Name:        EFI_BYTE_REGS
// Name:        EFI_WORD_REGS
// Name:        EFI_DWORD_REGS
// Name:        EFI_FLAGS_REG
// Name:        EFI_EFLAGS_REG
//
// Description: These register set definitions are used in EFI_LEGACY_BIOS_INT86
//              and EFI_LEGACY_BIOS_FARCALL86 fuctions.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
  UINT16     CF:1;
  UINT16     Reserved1:1;
  UINT16     PF:1;
  UINT16     Reserved2:1;
  UINT16     AF:1;
  UINT16     Reserved3:1;
  UINT16     ZF:1;
  UINT16     SF:1;
  UINT16     TF:1;
  UINT16     IF:1;
  UINT16     DF:1;
  UINT16     OF:1;
  UINT16     IOPL:2;
  UINT16     NT:1;
  UINT16     Reserved4:1;
} EFI_FLAGS_REG;

#define CARRY_FLAG  0x01

typedef struct {
    UINT32          CF:1;
    UINT32          Reserved1:1;
    UINT32          PF:1;
    UINT32          Reserved2:1;
    UINT32          AF:1;
    UINT32          Reserved3:1;
    UINT32          ZF:1;
    UINT32          SF:1;
    UINT32          TF:1;
    UINT32          IF:1;
    UINT32          DF:1;
    UINT32          OF:1;
    UINT32          IOPL:2;
    UINT32          NT:1;
    UINT32          Reserved4:2;
    UINT32          VM:1;
    UINT32          Reserved5:14;
} EFI_EFLAGS_REG;

typedef struct {
    UINT32           EAX;
    UINT32           EBX;
    UINT32           ECX;
    UINT32           EDX;
    UINT32           ESI;
    UINT32           EDI;
    EFI_EFLAGS_REG   EFlags;
    UINT16           ES;
    UINT16           CS;
    UINT16           SS;
    UINT16           DS;
    UINT16           FS;
    UINT16           GS;
    UINT32           EBP;
} EFI_DWORD_REGS;

typedef struct {
    UINT16           AX;
    UINT16           ReservedAX;
    UINT16           BX;
    UINT16           ReservedBX;
    UINT16           CX;
    UINT16           ReservedCX;
    UINT16           DX;
    UINT16           ReservedDX;
    UINT16           SI;
    UINT16           ReservedSI;
    UINT16           DI;
    UINT16           ReservedDI;
    EFI_FLAGS_REG    Flags;
    UINT16           ReservedFlags;
    UINT16           ES;
    UINT16           CS;
    UINT16           SS;
    UINT16           DS;
    UINT16           FS;
    UINT16           GS;
    UINT16           BP;
    UINT16           ReservedBP;
} EFI_WORD_REGS;

typedef struct {
    UINT8            AL, AH;
    UINT16           ReservedAX;
    UINT8            BL, BH;
    UINT16           ReservedBX;
    UINT8            CL, CH;
    UINT16           ReservedCX;
    UINT8            DL, DH;
    UINT16           ReservedDX;
} EFI_BYTE_REGS;

typedef union {
  EFI_DWORD_REGS  E;
  EFI_WORD_REGS   X;
  EFI_BYTE_REGS   H;
} EFI_IA32_REGISTER_SET;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_INT86
//
// Description: Issues a traditional software INT.
//
// Input:
//  This    -   Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  BiosInt -   The software INT requested.
//  Regs    -   The IA-32 registers.
//
// Output:
//  FALSE   INT completed. Status returned in Regs.
//  TRUE    INT was not completed.
//
// Referrals:   EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
BOOLEAN
(EFIAPI *EFI_LEGACY_BIOS_INT86) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  UINT8                           BiosInt,
  IN OUT  EFI_IA32_REGISTER_SET       *Regs
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_FARCALL86
//
// Description: This function performs a far call into Compatibility16 or
//              traditional OpROM code at the specified Segment:Offset.
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  Segment     Segment of 16-bit mode call.
//  Offset      Offset of 16-bit mode call.
//  Regs        The IA-32 registers, type EFI_IA32_REGISTER_SET
//  Stack       Caller-allocated stack that is used to pass arguments.
//  StackSize   Size of Stack in bytes.
//
// Output:
//  FALSE   FarCall() completed. Status returned in Regs
//  TRUE    FarCall() was not completed.
//
// Referrals:   EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
BOOLEAN
(EFIAPI *EFI_LEGACY_BIOS_FARCALL86) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  UINT16                          Segment,
  IN  UINT16                          Offset,
  IN  EFI_IA32_REGISTER_SET           *Regs,
  IN  VOID                            *Stack,
  IN  UINTN                           StackSize
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_CHECK_ROM
//
// Description: Tests to see if a traditional PCI ROM exists for this device
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  PciHandle   The handle for this device. Type EFI_HANDLE is defined in
//              InstallProtocolInterface() in the EFI 1.10 Specification.
//  RomImage    Pointer to the ROM image.
//  RomSize     The size of the ROM image.
//  Flags       The type of ROM discovered. Multiple bits can be set, as follows:
//                      00 = No ROM
//                      01 = ROM Found
//                      02 = ROM is a valid legacy ROM
//
// Output:      EFI_SUCCESS A traditional OpROM is available for this device.
//              EFI_UNSUPPORTED A traditional OpROM is not supported.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_CHECK_ROM) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  EFI_HANDLE                      PciHandle,
  OUT VOID                            **RomImage, OPTIONAL
  OUT UINTN                           *RomSize,   OPTIONAL
  OUT UINTN                           *Flags
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_INSTALL_ROM
//
// Description: Shadows an OpROM
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  PciHandle   The PCI PC-AT* OpROM from this device's ROM BAR will be loaded
//  RomImage    A PCI PC-AT ROM image.  This argument is non-NULL if there is
//      no hardware associated with the ROM and thus no PciHandle; otherwise it
//      must be NULL. An example is the PXE base code.
//  Flags       The type of ROM discovered. Multiple bits can be set, as follows:
//                      00 = No ROM.
//                      01 = ROM found.
//                      02 = ROM is a valid legacy ROM.
//  DiskStart   Disk number of the first device hooked by the ROM. If DiskStart is
//              the same as DiskEnd, no disks were hooked.
//  DiskEnd     Disk number of the last device hooked by the ROM.
//  RomShadowAddress    Shadow address of PC-AT ROM.
//  ShadowedRomSize     Size in bytes of RomShadowAddress.
//
// Output:
//  EFI_SUCCESS The OpROM was shadowed
//  EFI_UNSUPPORTED The PciHandle was not found
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_INSTALL_ROM) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  EFI_HANDLE                      PciHandle,
  IN  VOID                            **RomImage,
  OUT UINTN                           *Flags,
  OUT UINT8                           *DiskStart, OPTIONAL
  OUT UINT8                           *DiskEnd, OPTIONAL
  OUT VOID                            **RomShadowAddress, OPTIONAL
  OUT UINT32                          *ShadowedRomSize OPTIONAL
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_BOOT
//
// Description: Boots a traditional OS
//
// Input:
//  This            Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  BootOption      The EFI device path from BootXXXX variable.
//  LoadOptionSize  Size of LoadOption.
//  LoadOption      The load option from BootXXXX variable.
//
// Output:
//  EFI_DEVICE_ERROR    Failed to boot from any boot device and
//  memory is uncorrupted.
//
// Notes:   This function normally never returns. It will either boot the OS
//          or reset the system if memory has been "corrupted" by loading a
//          boot sector and passing control to it.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_BOOT) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  BBS_BBS_DEVICE_PATH             *BootOption,
  IN  UINT32                          LoadOptionsSize,
  IN  VOID                            *LoadOptions
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_UPDATE_KEYBOARD_LED_STATUS
//
// Description: Updates the BDA to reflect status of the Scroll Lock,
//              Num Lock, and Caps Lock keys and LEDs.
//
// Input:
//  This    Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  Leds    Current LED status, as follows:
//                      Bit 0 - Scroll Lock         0 = Off
//                      Bit 1 - Num Lock
//                      Bit 2 - Caps Lock
// Output:
//  EFI_SUCCESS The BDA was updated successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_UPDATE_KEYBOARD_LED_STATUS) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  UINT8                           Leds
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_GET_BBS_INFO
//
// Description: Presents BBS information to external agents.
//
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  HddCount    Number of HDD_INFO structures.
//  HddInfo     Onboard IDE controller information.
//  BbsCount    Number of BBS_TABLE structures.
//  BbsTable    BBS entry.
//
// Output:  EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_GET_BBS_INFO) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  OUT  UINT16                         *HddCount,
  OUT  struct _HDD_INFO               **HddInfo,
  OUT  UINT16                         *BbsCount,
  IN OUT  struct _BBS_TABLE           **BbsTable
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_SHADOW_ALL_LEGACY_OPROMS
//
// Description: Allows external agents to force loading of all legacy OpROMs.
//              This function can be invoked before GetBbsInfo() to ensure all
//              devices are counted.
// Input:
//  This    Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//
// Output:
//  EFI_SUCCESS OpROMs are shadowed successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_SHADOW_ALL_LEGACY_OPROMS) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_PREPARE_TO_BOOT
//
// Description: This function is called when booting an EFI-aware OS with legacy
//              hard disks. The legacy hard disks may or may not be the boot
//              device but will be accessed by the EFI-aware OS.
// Input:
//  This        Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  BbsCount    Number of BBS_TABLE structures.
//  BbsTable    BBS entry.
//
// Output:
//  EFI_SUCCESS Boot is prepared successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_PREPARE_TO_BOOT) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  OUT  UINT16                         *BbsCount,
  OUT  struct _BBS_TABLE              **BbsTable
  );


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_GET_LEGACY_REGION
//
// Description: This function is called when EFI needs to reserve an area
//              in the 0xE0000 or 0xF0000 64 KB blocks.
// Input:
//  This                Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  LegacyMemorySize    Requested size in bytes of the region.
//  Region              Requested region.
//                              00 = Either 0xE0000 or 0xF0000 blocks.
//                              Bit0 = 1 Specify 0xF0000 block
//                              Bit1 = 1 Specify 0xE0000 block
//  Alignment   Bit-mapped value specifying the address alignment of the requested
//                  region. The first nonzero value from the right is alignment.
//
// Output:
//  LegacyMemoryAddress     Address assigned.
//  EFI_SUCCESS The requested region was assigned.
//  EFI_ACCESS_DENIED   The function was previously invoked.
//  Other   The requested region was not assigned.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_GET_LEGACY_REGION) (
  IN EFI_LEGACY_BIOS_PROTOCOL          *This,
  IN UINTN                             LegacyMemorySize,
  IN UINTN                             Region,
  IN UINTN                             Alignment,
  OUT VOID                             **LegacyMemoryAddress
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_COPY_LEGACY_REGION
//
// Description: This function is called when copying data to the region
//              assigned by EFI_LEGACY_BIOS_PROTOCOL.GetLegacyRegion().
//
// Input:
//  This    Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  LegacyMemorySize    Size in bytes of the memory to copy.
//  LegacyMemoryAddress The location within the region returned by
//                          EFI_LEGACY_BIOS_PROTOCOL.GetLegacyRegion().
//  LegacyMemorySourceAddress   Source of the data to copy.
//
// Output:
//      EFI_SUCCESS The data was copied successfully.
//      EFI_ACCESS_DENIED   Either the starting or ending address is out of bounds.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_COPY_LEGACY_REGION) (
  IN EFI_LEGACY_BIOS_PROTOCOL          *This,
  IN UINTN                             LegacyMemorySize,
  IN VOID                              *LegacyMemoryAddress,
  IN VOID                              *LegacyMemorySourceAddress
  );


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    UDC_ATTRIBUTES
//
// Fields:
//  DirectoryServiceValidity    UINT8:1 This bit set indicates that the ServiceAreaData is valid.
//  RacbaUsedFlag   UINT8:1 This bit set indicates to use the RACBA only if DirectoryServiceValidity is 0.
//  ExecuteHddDiagnosticsFlag   UINT8:1 This bit set indicates to execute hard disk diagnostics.
//  Reserved    UINT8:5 Reserved for future use. Set to 0.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
   UINT8             DirectoryServiceValidity      : 1;
   UINT8             RabcaUsedFlag     : 1;
   UINT8             ExecuteHddDiagnosticsFlag     : 1;
   UINT8             Reserved    : 5;
} UDC_ATTRIBUTES;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        UD_TABLE
//
// Fields:
//  Attributes  UDC_ATTRIBUTES This field contains the bit-mapped attributes of the PARTIES information.
//  DeviceNumber    UINT8 This field contains the zero-based device on which the selected ServiceDataArea is present.
//  BbsTableEntryNumberForParentDevice  UINT8 This field contains the zero-based index into the BbsTable for the parent device.
//  BbsTableEntryNumberForBoot  UINT8   This field contains the zero-based index into the BbsTable for the boot entry.
//  BbsTableEntryNumberForHddDiag UINT8 This field contains the zero-based index into the BbsTable for the HDD diagnostics entry.
//  BeerData        UINT8[128]  The raw Beer data.
//  ServiceAreaData UINT8[64]   The raw data of selected service area.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
   UDC_ATTRIBUTES    Attributes;
   UINT8             DeviceNumber;
   UINT8             BbsTableEntryNumberForParentDevice;
   UINT8             BbsTableEntryNumberForBoot;
   UINT8             BbtTableEntryNumberForHddDiag;
   UINT8             BeerData[128];
   UINT8             ServiceAreaData[64];
} UD_TABLE;


//----------------------------------------------------------------------------
// PCI Bus Xlat protocol definition
//
// {CB5C54C0-230D-43db-922C-24D34F8C915C}
#define AMICSM_PCIBUSNUM_XLAT_PROTOCOL_GUID            \
    {0xcb5c54c0, 0x230d, 0x43db, 0x92, 0x2c, 0x24, 0xd3, 0x4f, 0x8c, 0x91, 0x5c}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        AMICSM_GET_PCIBUS_XLAT_NUMBER
//
// Description: This function returns the PCI bus number translated according
//              to Xlat table defined in BusNumXlat.inc. This translation file
//              is generated by AMISDL using "BUSNUM_XLAT" output type.
//
// Input:       Build time PCI bus number - 1st coulmn of the xlat table
//
// Output:      EFI_SUCCESS, real PCI bus number - 2nd column of the xlat table
//              EFI_NOT_FOUND, the requested bus is not found in the xlat table
//              EFI_INVALID_PARAMETER, if NULL pointer is supplied on input
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *AMICSM_GET_PCIBUS_XLAT_NUMBER) (
  IN OUT UINT8  *busNumber
);

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        AMICSM_PCIBUSNUM_XLAT_PROTOCOL
//
// Description: This protocol defines the function that returns the PCI
//              according to the table generated by AMISDL out of the list
//              of PCI-PCI bridges.
// Fields:
//  GetXlatPciBusNum AMICSM_GET_PCIBUS_XLAT_NUMBER Returns the translated bus number
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _AMICSM_PCIBUSNUM_XLAT_PROTOCOL {
    AMICSM_GET_PCIBUS_XLAT_NUMBER    GetXlatPciBusNum;
} AMICSM_PCIBUSNUM_XLAT_PROTOCOL;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_BOOT_UNCONVENTIONAL_DEVICE
//
// Description: This function is called when either booting to an unconventional
//              device such as a PARTIES partition and/or executing hard disk
//              diagnostics.
// Input:
//  This
//      Indicates the EFI_LEGACY_BIOS_PROTOCOL instance.
//  Attributes
//      Flags used to interpret the rest of the input parameters. Type UDC_ATTRIBUTES
//      is defined in Compatibility16PrepareToBoot().
//  BbsEntry
//      The zero-based index into the BbsTable for the parent device. Type BBS_TABLE
//      is defined in Compatibility16PrepareToBoot().
//  BeerData
//      Pointer to the 128 bytes of raw Beer data.
//  ServiceAreaData
//      Pointer to the 64 bytes of raw service area data. It is up to the caller to
//      select the appropriate service area and point to it.
//
// Output:
//  EFI_INVALID_PARAMETER   Either the Attribute and/or pointers do not match.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

typedef
EFI_STATUS
(EFIAPI *EFI_LEGACY_BIOS_BOOT_UNCONVENTIONAL_DEVICE) (
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN UDC_ATTRIBUTES                   Attributes,
  IN UINTN                            BbsEntry,
  IN VOID                             *BeerData,
  IN VOID                             *ServiceAreaData
  );


//*****************************************************************
//       Compatibility16 Functions
//*****************************************************************
typedef enum {
  Compatibility16InitializeYourself,    // 0000,
  Compatibility16UpdateBbs,             // 0001,
  Compatibility16PrepareToBoot,         // 0002,
  Compatibility16Boot,                  // 0003,
  Compatibility16RetrieveLastBootDevice,// 0004,
  Compatibility16DispatchOprom,         // 0005,
  Compatibility16GetTableAddress,       // 0006,
  Compatibility16SetKeyboardLeds,       // 0007,
  Compatibility16InstallPciHandler      // 0008,
} EFI_COMPATIBILITY_FUNCTIONS;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_PROTOCOL
//
// Description: Abstracts the traditional BIOS from the rest of EFI. The
//              LegacyBoot() member function allows the BDS to support booting
//              a traditional OS. EFI thunks drivers that make EFI bindings for
//              BIOS INT services use all the other member functions.
// Fields:
//  Int86       EFI_LEGACY_BIOS_INT86       Performs traditional software INT.
//  FarCall86   EFI_LEGACY_BIOS_FARCALL86   Performs a 16-bit far call.
//  CheckPciRom EFI_LEGACY_BIOS_CHECK_ROM   Checks if a traditional OpROM exists for this device.
//  InstallPciRom EFI_LEGACY_BIOS_INSTALL_ROM Loads a traditional OpROM in traditional OpROM address space.
//  LegacyBoot  EFI_LEGACY_BIOS_BOOT        Boots a traditional OS.
//  UpdateKeyboardLedStatus EFI_LEGACY_BIOS_UPDATE_KEYBOARD_LED_STATUS Updates BDA to reflect the current EFI keyboard LED status.
//  GetBbsInfo  EFI_LEGACY_BIOS_GET_BBS_INFO Allows an external agent, such as BIOS Setup, to get the BBS data.
//  ShadowAllLegacyOproms   EFI_LEGACY_BIOS_SHADOW_ALL_LEGACY_OPROMS Causes all legacy OpROMs to be shadowed.
//  PrepareToBoot       EFI_LEGACY_BIOS_PREPARE_TO_BOOT Performs all actions prior to boot.
//  GetLegacyRegion     EFI_LEGACY_BIOS_GET_LEGACY_REGION Allows EFI to reserve an area in the 0xE0000 or 0xF0000 block.
//  CopyLegacyRegion    EFI_LEGACY_BIOS_COPY_LEGACY_REGION Allows EFI to copy data to the area specified by GetLegacyRegion.
//  BootUnconventionalDevice    EFI_LEGACY_BIOS_BOOT_UNCONVENTIONAL_DEVICE Allows the user to boot off an unconventional device.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _EFI_LEGACY_BIOS_PROTOCOL {
  EFI_LEGACY_BIOS_INT86           Int86;
  EFI_LEGACY_BIOS_FARCALL86       FarCall86;
  EFI_LEGACY_BIOS_CHECK_ROM       CheckPciRom;
  EFI_LEGACY_BIOS_INSTALL_ROM     InstallPciRom;
  EFI_LEGACY_BIOS_BOOT            LegacyBoot;
  EFI_LEGACY_BIOS_UPDATE_KEYBOARD_LED_STATUS
                                  UpdateKeyboardLedStatus;
  EFI_LEGACY_BIOS_GET_BBS_INFO    GetBbsInfo;
  EFI_LEGACY_BIOS_SHADOW_ALL_LEGACY_OPROMS
                                  ShadowAllLegacyOproms;
  EFI_LEGACY_BIOS_PREPARE_TO_BOOT
                                  PrepareToBootEFI;
  EFI_LEGACY_BIOS_GET_LEGACY_REGION
                                  GetLegacyRegion;
  EFI_LEGACY_BIOS_COPY_LEGACY_REGION
                                  CopyLegacyRegion;
  EFI_LEGACY_BIOS_BOOT_UNCONVENTIONAL_DEVICE
                                  BootUnconventionalDevice;
} EFI_LEGACY_BIOS_PROTOCOL;

#pragma pack ()

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
