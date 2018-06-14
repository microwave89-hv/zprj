/*++

   Copyright (c)  1999 - 2007 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Module Name:

   TcgPrivate.h

   Abstract:

   Private interface used internally by TCG modules

   --*/
/*++
   This file contains an 'Intel Peripheral Driver' and uniquely
   identified as "Intel Mobile Silicon Support Module" and is
   licensed for Intel Mobile CPUs and chipsets under the terms of your
   license agreement with Intel or your vendor.  This file may
   be modified by the user, subject to additional terms of the
   license agreement
   --*/

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgPrivate.h 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgPrivate.h $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 11:59a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:58p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 8     3/29/11 12:25p Fredericko
// 
// 7     3/28/11 12:23p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 6     7/09/10 3:32p Fredericko
// Updated TCG structures for image measurement.
// 
// 5     5/19/10 5:20p Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgPrivate.h
//
// Description: 
//  Header file for Tcg private protocol definitions
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _TCG_PRIVATE_H_
#define _TCG_PRIVATE_H_

#define EFI_TCG_PRIVATE_INTERFACE_GUID  \
    { 0x8c4c9a41, 0xbf56, 0x4627, 0x9e, 0xa, 0xc8, 0x38, 0x6d, 0x66, 0x11, 0x5c }


#define TCG_EFI_IMAGE_DOS_SIGNATURE     0x5A4D      // MZ
#define TCG_EFI_TE_IMAGE_HEADER_SIGNATURE     0x5A56      // TE
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_EXPORT      0
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_IMPORT      1
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_RESOURCE    2
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_EXCEPTION   3
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_SECURITY    4
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_BASERELOC   5
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_DEBUG       6
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_COPYRIGHT   7
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_GLOBALPTR   8
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_TLS         9
#define TCG_EFI_IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG 10
#define TCG_MBR_TYPE_EFI_PARTITION_TABLE_HEADER   0x02
#define TCG_EFI_IMAGE_NUMBER_OF_DIRECTORY_ENTRIES 16
#define END_DEVICE_PATH_TYPE 0x7F
#define END_ENTIRE_DEVICE_PATH_SUBTYPE 0xFF
#define EFI_DP_TYPE_MASK                    0x7F
#define EFI_DP_TYPE_UNPACKED                0x80
#define END_INSTANCE_DEVICE_PATH_SUBTYPE    0x01
// Type definitions for the Hard drive device path
#define TCG_MBR_TYPE_MASTER_BOOT_RECORD 0x01
#define TCG_MBR_TYPE_EFI_PARTITION_TABLE_HEADER     0x02

// Needed Partition Type definitions for MBR
#define TCG_NO_PARTITION                0x0
#define TCG_EXTENDED_PARTITION          0x05
#define TCG_WIN95_EXTENDED_PARTITION    0x0f




#define DP_IS_END_TYPE(a)
#define DP_IS_END_SUBTYPE(a)        ( ((a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )

#define DevicePathType(a)           ( ((a)->Type) & EFI_DP_TYPE_MASK )
#define DevicePathSubType(a)        ( (a)->SubType )
#define DevicePathNodeLength(a)     ( ((a)->Length[0]) | ((a)->Length[1] << 8) )

#define IsDevicePathEndType(a)      ( DevicePathType(a) == END_DEVICE_PATH_TYPE )
#define IsDevicePathEndSubType(a)   ( (a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )
#define IsDevicePathEnd(a)          ( IsDevicePathEndType(a) && IsDevicePathEndSubType(a) )
#define NextDevicePathNode(a)       ( (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + DevicePathNodeLength(a)))

#define IsDevicePathEnd(a)          ( IsDevicePathEndType(a) && IsDevicePathEndSubType(a) )

typedef struct {
  UINT32  VirtualAddress;
  UINT32  Size;
} TCG_EFI_IMAGE_DATA_DIRECTORY;

typedef struct {
  UINT16  Machine;
  UINT16  NumberOfSections;
  UINT32  TimeDateStamp;
  UINT32  PointerToSymbolTable;
  UINT32  NumberOfSymbols;
  UINT16  SizeOfOptionalHeader;
  UINT16  Characteristics;
} TCG_EFI_IMAGE_FILE_HEADER;


#if EFIx64
typedef struct {
  //
  // Standard fields.
  //
  UINT16                    Magic;
  UINT8                     MajorLinkerVersion;
  UINT8                     MinorLinkerVersion;
  UINT32                    SizeOfCode;
  UINT32                    SizeOfInitializedData;
  UINT32                    SizeOfUninitializedData;
  UINT32                    AddressOfEntryPoint;
  UINT32                    BaseOfCode;
  //
  // NT additional fields.
  //
  UINT64                    ImageBase;
  UINT32                    SectionAlignment;
  UINT32                    FileAlignment;
  UINT16                    MajorOperatingSystemVersion;
  UINT16                    MinorOperatingSystemVersion;
  UINT16                    MajorImageVersion;
  UINT16                    MinorImageVersion;
  UINT16                    MajorSubsystemVersion;
  UINT16                    MinorSubsystemVersion;
  UINT32                    Win32VersionValue;
  UINT32                    SizeOfImage;
  UINT32                    SizeOfHeaders;
  UINT32                    CheckSum;
  UINT16                    Subsystem;
  UINT16                    DllCharacteristics;
  UINT64                    SizeOfStackReserve;
  UINT64                    SizeOfStackCommit;
  UINT64                    SizeOfHeapReserve;
  UINT64                    SizeOfHeapCommit;
  UINT32                    LoaderFlags;
  UINT32                    NumberOfRvaAndSizes;
  TCG_EFI_IMAGE_DATA_DIRECTORY  DataDirectory[TCG_EFI_IMAGE_NUMBER_OF_DIRECTORY_ENTRIES];
} TCG_EFI_IMAGE_OPTIONAL_HEADER64;

typedef struct {
  UINT32                      Signature;
  TCG_EFI_IMAGE_FILE_HEADER       FileHeader;
  TCG_EFI_IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} TCG_EFI_IMAGE_NT_HEADERS64;


typedef TCG_EFI_IMAGE_OPTIONAL_HEADER64 TCG_EFI_IMAGE_OPTIONAL_HEADER;
typedef TCG_EFI_IMAGE_NT_HEADERS64      TCG_EFI_IMAGE_NT_HEADERS;

#else

typedef struct {
  //
  // Standard fields.
  //
  UINT16                    Magic;
  UINT8                     MajorLinkerVersion;
  UINT8                     MinorLinkerVersion;
  UINT32                    SizeOfCode;
  UINT32                    SizeOfInitializedData;
  UINT32                    SizeOfUninitializedData;
  UINT32                    AddressOfEntryPoint;
  UINT32                    BaseOfCode;
  UINT32                    BaseOfData;
  //
  // NT additional fields.
  //
  UINT32                    ImageBase;
  UINT32                    SectionAlignment;
  UINT32                    FileAlignment;
  UINT16                    MajorOperatingSystemVersion;
  UINT16                    MinorOperatingSystemVersion;
  UINT16                    MajorImageVersion;
  UINT16                    MinorImageVersion;
  UINT16                    MajorSubsystemVersion;
  UINT16                    MinorSubsystemVersion;
  UINT32                    Win32VersionValue;
  UINT32                    SizeOfImage;
  UINT32                    SizeOfHeaders;
  UINT32                    CheckSum;
  UINT16                    Subsystem;
  UINT16                    DllCharacteristics;
  UINT32                    SizeOfStackReserve;
  UINT32                    SizeOfStackCommit;
  UINT32                    SizeOfHeapReserve;
  UINT32                    SizeOfHeapCommit;
  UINT32                    LoaderFlags;
  UINT32                    NumberOfRvaAndSizes;
  TCG_EFI_IMAGE_DATA_DIRECTORY  DataDirectory[TCG_EFI_IMAGE_NUMBER_OF_DIRECTORY_ENTRIES];
} TCG_EFI_IMAGE_OPTIONAL_HEADER32;

typedef struct {
  UINT32                      Signature;
  TCG_EFI_IMAGE_FILE_HEADER       FileHeader;
  TCG_EFI_IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} TCG_EFI_IMAGE_NT_HEADERS32;


typedef TCG_EFI_IMAGE_OPTIONAL_HEADER32 TCG_EFI_IMAGE_OPTIONAL_HEADER;
typedef TCG_EFI_IMAGE_NT_HEADERS32      TCG_EFI_IMAGE_NT_HEADERS;
#endif

#define TCG_EFI_IMAGE_SIZEOF_SHORT_NAME 8

typedef struct {
  UINT8 Name[TCG_EFI_IMAGE_SIZEOF_SHORT_NAME];
  union {
    UINT32  PhysicalAddress;
    UINT32  VirtualSize;
  } Misc;
  UINT32  VirtualAddress;
  UINT32  SizeOfRawData;
  UINT32  PointerToRawData;
  UINT32  PointerToRelocations;
  UINT32  PointerToLinenumbers;
  UINT16  NumberOfRelocations;
  UINT16  NumberOfLinenumbers;
  UINT32  Characteristics;
} TCG_EFI_IMAGE_SECTION_HEADER;

typedef struct {
  UINT16                    Signature;            // signature for TE format = "VZ"
  UINT16                    Machine;              // from the original file header
  UINT8                     NumberOfSections;     // from the original file header
  UINT8                     Subsystem;            // from original optional header
  UINT16                    StrippedSize;         // how many bytes we removed from the header
  UINT32                    AddressOfEntryPoint;  // offset to entry point -- from original optional header
  UINT32                    BaseOfCode;           // from original image -- required for ITP debug
  UINT64                    ImageBase;            // from original file header
  TCG_EFI_IMAGE_DATA_DIRECTORY  DataDirectory[2];     // only base relocation and debug directory
} TCG_EFI_TE_IMAGE_HEADER;

typedef struct {
  UINT16  e_magic;    // Magic number
  UINT16  e_cblp;     // Bytes on last page of file
  UINT16  e_cp;       // Pages in file
  UINT16  e_crlc;     // Relocations
  UINT16  e_cparhdr;  // Size of header in paragraphs
  UINT16  e_minalloc; // Minimum extra paragraphs needed
  UINT16  e_maxalloc; // Maximum extra paragraphs needed
  UINT16  e_ss;       // Initial (relative) SS value
  UINT16  e_sp;       // Initial SP value
  UINT16  e_csum;     // Checksum
  UINT16  e_ip;       // Initial IP value
  UINT16  e_cs;       // Initial (relative) CS value
  UINT16  e_lfarlc;   // File address of relocation table
  UINT16  e_ovno;     // Overlay number
  UINT16  e_res[4];   // Reserved words
  UINT16  e_oemid;    // OEM identifier (for e_oeminfo)
  UINT16  e_oeminfo;  // OEM information; e_oemid specific
  UINT16  e_res2[10]; // Reserved words
  UINT32  e_lfanew;   // File address of new exe header
} TCG_EFI_IMAGE_DOS_HEADER;


// GPT Partition Entry
//<AMI_STHDR_START>
//============================================================================
// Structure:   PARTITION_ENTRY
//
// Description: Data Structure definition of a partion entry in the GPT table
//
// Fields:
//      PartitionTypeGuid - EFI_GUID - contains GUID that defines that type
//          of GUID
//      UniquePartitionGuid - EFI_GUID - contains unique GUID for each
//          partition
//      StartingLba - EFI_LBA - first LBA of the partition
//      EndingLba - EFI_LBA - last logical block address
//      Attributes - UINT64 - UEFI defined attributes
//          Bit 0 - Partition is required for platform to function
//          Bits 1 - 47 - undefined
//          Bits 48 - 64 - reserved for GUID specific use
//      PartitionName[36] - CHAR16 - unicode string containing the name of
//          the partition
//
// Referral:
//      EFI_LBA
//============================================================================
//<AMI_STHDR_END>
typedef struct
{
    EFI_GUID    PartitionTypeGuid;
    EFI_GUID    UniquePartitionGuid;
    EFI_LBA     StartingLba;
    EFI_LBA     EndingLba;
    UINT64      Attributes;
    CHAR16      PartitionName[36];
} TCG_EFI_PARTITION_ENTRY;


typedef struct
{
    EFI_TABLE_HEADER    Header;
    EFI_LBA             MyLba;
    EFI_LBA             AlternateLba;
    EFI_LBA             FirstUsableLba;
    EFI_LBA             LastUsableLba;
    EFI_GUID            DiskGuid;
    EFI_LBA             PartitionEntryLba;
    UINT32              NumberOfPartitionEntries;
    UINT32              SizeOfPartitionEntry;
    UINT32              Crc32;
} TCG_EFI_PARTITION_TABLE_HEADER;


typedef struct {
   TCG_EFI_PARTITION_TABLE_HEADER EfiPartitionHeader;
   UINTN                          NumberOfPartitions;
   TCG_EFI_PARTITION_ENTRY        Partitions[1];
} TCG_EFI_GPT_DATA;


//
// EFI TCG Platform Protocol
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCG_MEASURE_PE_IMAGE) (
  IN      BOOLEAN                   BootPolicy,
  IN      EFI_PHYSICAL_ADDRESS      ImageAddress,
  IN      UINTN                     ImageSize,
  IN      UINTN                     LinkTimeBase,
  IN      UINT16                    ImageType,
  IN      EFI_HANDLE                DeviceHandle,
  IN      EFI_DEVICE_PATH_PROTOCOL  *FilePath
  );


typedef
EFI_STATUS
(EFIAPI *EFI_TCG_MEASURE_ACTION) (
  IN      CHAR8                     *ActionString
  );


typedef
EFI_STATUS
(EFIAPI *EFI_TCG_MEASURE_GPT_TABLE) (
  IN      EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );


typedef struct _EFI_TCG_PLATFORM_PROTOCOL {
  EFI_TCG_MEASURE_PE_IMAGE          MeasurePeImage;
  EFI_TCG_MEASURE_ACTION            MeasureAction;
  EFI_TCG_MEASURE_GPT_TABLE         MeasureGptTable;
} EFI_TCG_PLATFORM_PROTOCOL;

extern EFI_GUID gEfiTcgPrivateInterfaceGuid;
#endif  // _TCG_PRIVATE_H_
