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
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmEdd.h 7     1/12/10 11:50a Olegi $
//
// $Revision: 7 $
//
// $Date: 1/12/10 11:50a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmEdd.h $
// 
// 7     1/12/10 11:50a Olegi
// Copyright message updated.
// 
// 6     4/27/07 5:14p Olegi
// CSM.CHM file preparation.
//
// 5     3/13/06 2:38p Felixp
//
// 4     10/13/05 6:21p Olegi
//
// 3     4/20/05 4:54p Andriyn
// USB_DEVICE_PATH is in core now
//
// 2     3/04/05 1:45p Mandal
//
// 1     2/15/05 11:00a Olegi
// Initial VSS check-in.
//
//
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:            CsmEdd.h
//
// Description:     EDD support definitions file
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _CSM_EDD_H_
#define _CSM_EDD_H_

#pragma pack(1)

typedef struct {
    UINT8   Bus;
    UINT8   Device;
    UINT8   Function;
    UINT8   Controller;
    UINT32  Reserved;
} EDD_PCI;

typedef struct {
    UINT16  Base;
    UINT16  Reserved;
    UINT32  Reserved2;
} EDD_LEGACY;

typedef union {
    EDD_PCI     Pci;
    EDD_LEGACY  Legacy;
} EDD_INTERFACE_PATH;

typedef struct {
    UINT8   Master;
    UINT8   Reserved[15];
} EDD_ATA;

typedef struct {
    UINT8   Master;
    UINT8   Lun;
    UINT8   Reserved[14];
} EDD_ATAPI;

typedef struct {
    UINT16  TargetId;
    UINT64  Lun;
    UINT8   Reserved[6];
} EDD_SCSI;

typedef struct {
    UINT64   SerialNumber;
    UINT64   Reserved;
} EDD_USB;

typedef struct {
    UINT64  Guid;
    UINT64  Reserved;
} EDD_1394;

typedef struct {
    UINT64  Wwn;
    UINT64  Lun;
} EDD_FIBRE;

typedef union {
    EDD_ATA     Ata;
    EDD_ATAPI   Atapi;
    EDD_SCSI    Scsi;
    EDD_USB     Usb;
    EDD_1394    FireWire;
    EDD_FIBRE   FibreChannel;
} EDD_DEVICE_PATH;

typedef struct _UNKNOWN_VENDOR_DEVICE_PATH {
  VENDOR_DEVICE_PATH              DevicePath;
  UINT8                           LegacyDriveLetter;
} UNKNOWN_DEVICE_VENDOR_DEVICE_PATH;

//typedef struct _CONTROLLER_DEVICE_PATH {
//  EFI_DEVICE_PATH_PROTOCOL        Header;
//  UINT32                          Controller;
//} CONTROLLER_DEVICE_PATH;

//typedef struct _ATAPI_DEVICE_PATH {
//  EFI_DEVICE_PATH_PROTOCOL        Header;
//  UINT8                           Channel;
//  UINT8                           Device;
//  UINT16                          Lun;
//} ATAPI_DEVICE_PATH;

//typedef struct _SCSI_DEVICE_PATH {
//  EFI_DEVICE_PATH_PROTOCOL        Header;
//  UINT16                          TargetId;
//  UINT16                          Lun;
//} SCSI_DEVICE_PATH;

//typedef struct _FIBRE_CHANNEL_DEVICE_PATH {
//  EFI_DEVICE_PATH_PROTOCOL        Header;
//  UINT32                          Reserved;
//  UINT64                          WorldWideNumber;
//  UINT64                          Lun;
//} FIBRECHANNEL_DEVICE_PATH;

//typedef struct _F1394_DEVICE_PATH {
//  EFI_DEVICE_PATH_PROTOCOL        Header;
//  UINT32                          Reserved;
//  UINT64                          _1394Guid;
//} F1394_DEVICE_PATH;
/* AndriyN : must belong to DevicePath.h
typedef struct _USB_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL      Header;
    UINT8                                   ParentPortNumber;
    UINT8                                   InterfaceNumber;
} USB_DEVICE_PATH;
*/

// Union of all possible device paths
typedef union {
  EFI_DEVICE_PATH_PROTOCOL             DevPath;
  PCI_DEVICE_PATH                      Pci;
//  PCCARD_DEVICE_PATH                   PcCard;
//  MEMMAP_DEVICE_PATH                   MemMap;
  VENDOR_DEVICE_PATH                   Vendor;
  UNKNOWN_DEVICE_VENDOR_DEVICE_PATH    UnknownVendor;
  CONTROLLER_DEVICE_PATH               Controller;
//  ACPI_HID_DEVICE_PATH                 Acpi;
  ACPI_HID_DEVICE_PATH                     Acpi;
  ATAPI_DEVICE_PATH                    Atapi;
  SCSI_DEVICE_PATH                     Scsi;
  FIBRECHANNEL_DEVICE_PATH            FibreChannel;
  F1394_DEVICE_PATH                    F1394;
  USB_DEVICE_PATH                      Usb;
  USB_CLASS_DEVICE_PATH                UsbClass;
  I20_DEVICE_PATH                      I20;
//  MAC_ADDR_DEVICE_PATH                 MacAddr;
  IPv4_DEVICE_PATH                     Ipv4;
  IPv6_DEVICE_PATH                     Ipv6;
  INFINIBAND_DEVICE_PATH               InfiniBand;
  UART_DEVICE_PATH                     Uart;
  HARDDRIVE_DEVICE_PATH                HardDrive;
  CDROM_DEVICE_PATH                    CD;
//  FILEPATH_DEVICE_PATH                 FilePath;
//  MEDIA_PROTOCOL_DEVICE_PATH           MediaProtocol;
//  BBS_BBS_DEVICE_PATH                  Bbs;
} EFI_DEV_PATH;

#define HARDWARE_DEVICE_PATH      0x01
#define HW_VENDOR_DP              0x04
#define MESSAGING_DEVICE_PATH     0x03
#define MSG_ATAPI_DP              0x01
#define HW_CONTROLLER_DP          0x05
#define MSG_SCSI_DP               0x02
#define MSG_1394_DP               0x04
#define MSG_FIBRECHANNEL_DP       0x03

typedef struct {
    UINT16              StructureSize;
    UINT16              Flags;
    UINT32              MaxCylinders;
    UINT32              MaxHeads;
    UINT32              SectorsPerTrack;
    UINT64              PhysicalSectors;
    UINT16              BytesPerSector;
    UINT32              FDPT;
    UINT16              Key;
    UINT8               DevicePathLength;
    UINT8               Reserved1;
    UINT16              Reserved2;
    CHAR8               HostBusType[4];
    CHAR8               InterfaceType[8];
    EDD_INTERFACE_PATH  InterfacePath;
    EDD_DEVICE_PATH     DevicePath;
    UINT8               Reserved3;
    UINT8               Checksum;
} EDD_DRIVE_PARAMETERS;

// Flag definitions for above
#define EDD_GEOMETRY_VALID          0x02
#define EDD_DEVICE_REMOVABLE        0x04
#define EDD_WRITE_VERIFY_SUPPORTED  0x08
#define EDD_DEVICE_CHANGE           0x10
#define EDD_DEVICE_LOCKABLE         0x20

// For WIN98 limitation
#define EDD_DEVICE_GEOMETRY_MAX     0x40


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    EDD_DEVICE_ADDRESS_PACKET
//
// Description:  Device address packet used during EDD data transfers
//
// Fields:
//  PacketSizeInBytes   UINT8   Packet size in bytes
//  Zero                UINT8
//  NumberOfBlocks      UINT8   # of blocks to transfer
//  Zero2               UINT8
//  SegOffset           UINT32  Data address below 1MB
//  LBA                 UINT64  Device Logical Block Address
//  TransferBuffer      UINT64  Transfer Buffer
//  ExtendedBlockCount  UINT32  Transferred blocks counter
//  Zero3               UINT32
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
    UINT8   PacketSizeInBytes; // 0x18
    UINT8   Zero;
    UINT8   NumberOfBlocks; // Max 0x7f
    UINT8   Zero2;
    UINT32  SegOffset;
    UINT64  LBA;
    UINT64  TransferBuffer;
    UINT32  ExtendedBlockCount; // Max 0xffffffff
    UINT32  Zero3;
} EDD_DEVICE_ADDRESS_PACKET;

#define UNKNOWN_DEVICE_GUID \
  { 0xcf31fac5, 0xc24e, 0x11d2,  0x85, 0xf3, 0x0, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b  }

#define EDD_VERSION_30  0x30

// Int 13 Error Messages
#define ERR_PASS                   0x00
#define ERR_WRITE_PROTECTED        0x03
#define ERR_SECTOR_NOT_FOUND       0x04
#define ERR_RESET_FAILED           0x05
#define ERR_DISK_CHANGED           0x06
#define ERR_DRIVE_DOES_NOT_EXIST   0x07
#define ERR_DMA_ERROR              0x08
#define ERR_DATA_BOUNADRY_ERROR    0x09
#define ERR_BAD_SECTOR             0x0a
#define ERR_BAD_TRACK              0x0b
#define ERR_MEDIA_TYPE_NOT_FOUND   0x0c
#define ERR_INVALID_FORMAT         0x0d
#define ERR_ECC_ERROR              0x10
#define ERR_ECC_CORRECTED_ERROR    0x11
#define ERR_HARD_DRIVE_FAILURE     0x20
#define ERR_SEEK_FAILED            0x40
#define ERR_DRIVE_TIMEOUT          0x80
#define ERR_DRIVE_NOT_READY        0xaa
#define ERR_UNDEFINED_ERROR        0xbb
#define ERR_WRITE_FAULT            0xcc
#define ERR_SENSE_FAILED           0xff

#define MAX_EDD11_XFER  0xfe00

// PCI classes not defined in PCI.h
#define PCI_BASE_CLASS_INTELLIGENT  0x0e
#define PCI_SUB_CLASS_INTELLIGENT   0x00

#define EFI_SEGMENT(_Adr) (UINT16)((UINT16) (((UINTN)(_Adr)) >> 4) & 0xf000)
#define EFI_OFFSET(_Adr)  (UINT16)(((UINT16)((UINTN)_Adr)) & 0xffff)

#pragma pack()

// Local data structures

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    CSM_LEGACY_DRIVE
//
// Description:  Hard drive data structure
//
// Fields:
//  Letter          CHAR8   Drive letter
//  Number          UINT8   INT13 drive handle
//  EddVersion      UINT8   EDD version supported by the drive
//  ExtendedInt13   BOOLEAN Extended INT13 support status
//  DriveLockingAndEjecting BOOLEAN Locking/Ejecting support
//  Edd             BOOLEAN EDD support status
//  Extensions64Bit BOOLEAN 64 bit extension support
//  ParametersValid BOOLEAN Valid parameters (Parameters field) indicator
//  ErrorCode       UINT8   Error code field
//  FdptPointer     VOID*   Pointer to FDPT
//  Floppy          BOOLEAN Device-is-a-floppy indicator
//  AtapiFloppy     BOOLEAN Device-is-an-ATAPI-floppy indicator
//  MaxHead         UINT8   Number of heads
//  MaxSector       UINT8   Number of sectors
//  MaxCylinder     UINT16  Number of cylinders
//  Pad             UINT16
//  Parameters      EDD_DRIVE_PARAMETERS    EDD drive parameters
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
    CHAR8                   Letter;
    UINT8                   Number;
    UINT8                   EddVersion;
    BOOLEAN                 ExtendedInt13;
    BOOLEAN                 DriveLockingAndEjecting;
    BOOLEAN                 Edd;
    BOOLEAN                 Extensions64Bit;
    BOOLEAN                 ParametersValid;
    UINT8                   ErrorCode;
    VOID                    *FdptPointer;
    BOOLEAN                 Floppy;
    BOOLEAN                 AtapiFloppy;
    UINT8                   MaxHead;
    UINT8                   MaxSector;
    UINT16                  MaxCylinder;
    UINT16                  Pad;
    EDD_DRIVE_PARAMETERS    Parameters;
} CSM_LEGACY_DRIVE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    CSM_BLOCK_IO_DEV
//
// Description:  CSM BlockIo device properies
//
// Fields:
//  BlockIo     EFI_BLOCK_IO_PROTOCOL       BlockIo protocol instance
//  Handle      EFI_HANDLE                  EFI device handle
//  ControllerHandle    EFI_HANDLE          EFI controller handle
//  BlockMedia  EFI_BLOCK_IO_MEDIA          BlockIo device media
//  DevicePath  EFI_DEVICE_PATH_PROTOCOL*   Device path
//  PciIo       EFI_PCI_IO_PROTOCOL*        Device PciIo
//  LegacyBios  EFI_LEGACY_BIOS_PROTOCOL*   Legacy Bios instance pointer
//  Drive       CSM_LEGACY_DRIVE            Drive data pointer
//  HwInt       UINT8                       Hardware interrupt used by this device
//  HwIntHandler    UINT32                  Storage for the original HW interrupt
//
// Referrals:   CSM_LEGACY_DRIVE
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
    EFI_BLOCK_IO_PROTOCOL       BlockIo;
    EFI_HANDLE                  Handle;
    EFI_HANDLE                  ControllerHandle;
    EFI_BLOCK_IO_MEDIA          BlockMedia;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    EFI_LEGACY_BIOS_PROTOCOL    *LegacyBios;
    CSM_LEGACY_DRIVE            Drive;
    UINT8                       HwInt;
    UINT32                      HwIntHandler;
} CSM_BLOCK_IO_DEV;

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
