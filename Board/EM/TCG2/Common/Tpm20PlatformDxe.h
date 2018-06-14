//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20PlatformDxe.h 1     4/21/14 2:18p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:18p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20PlatformDxe.h $
// 
// 1     4/21/14 2:18p Fredericko
// 
// 1     10/08/13 12:06p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 3     8/30/13 11:04p Fredericko
// 
// 2     7/11/13 6:17p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20).
// 
// 1     7/10/13 5:58p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 11    1/20/12 9:20p Fredericko
// 
// 10    12/30/11 5:06p Fredericko
// [TAG]  		EIP78141
// [Category]  	New Feature
// [Description]  	Added hooks to override generic TPM platform hash
// functions.
// [Files]  		1. AmiTcgPlatform.sdl
// 2. AmiTcgPlatformPei.h
// 3. AmiTcgPlatformPeiLib.c
// 4. AmiTcgPlatformPeiAfterMem.c
// 5. AmiTcgPlatformDxe.c
// 6. AmiTcgPlatformDxe.h
// 
// 9     11/28/11 7:31p Fredericko
// [TAG]  		EIP63922
// [Category]  	Improvement
// [Description]  	Support for Smbios label 30 and up. Callback on
// publishing of Smbios tables
// [Files]		AmiTcgPlatformDxe.c
// 
// 8     10/10/11 11:36a Fredericko
// [TAG]  		EIP70220
// [Category]  	Improvement
// [Description]  	Remove dependency on CSM
// [Files]  		TcgLegacy.sdl
// AmiTcgPlatformDxe.c
// AmiTcgPlatformDxe.h
// xTcgDxe.c
// 
// 7     10/10/11 12:12a Fredericko
// [TAG]  		EIP70220
// [Category]  	Improvement
// [Description]  	Remove dependency on CSM
// [Files]  		TcgLegacy.sdl
// AmiTcgPlatformDxe.c
// AmiTcgPlatformDxe.h
// xTcgDxe.c
// 
// 6     7/25/11 3:43a Fredericko
// [TAG]  		EIP65177
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Tcg Ppi Spec ver 1.2 update
// 
// 5     4/28/11 6:34p Fredericko
// Removed VFR compile
// 
// 4     4/26/11 1:54p Fredericko
// Added support for function level override of specific functions. GUID
// definitions added
// 
// 3     4/06/11 10:40a Fredericko
// Core 4.6.5.0 build error changes
// 
// 2     3/29/11 2:27p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
//
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiTcgPlatformDxe.h
//
// Description:	Header file for AmiTcgPlatformDxe
//
//<AMI_FHDR_END>
//*************************************************************************
#include <efi.h>
#include <TcgMisc.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <Tpm20Includes\TrEEProtocol.h>
#include "protocol\TpmDevice\TpmDevice.h"
#include <Tpm20Includes\Tpm20.h>

//--------------------------------------------------------------------------
//GUID Definitions
//--------------------------------------------------------------------------
#define EFI_SMBIOS_TABLE_GUID \
  { \
    0xeb9d2d31, 0x2d88, 0x11d3, 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d \
  }


#define EFI_DP_TYPE_MASK                    0x7F
#define EFI_DP_TYPE_UNPACKED                0x80
#define END_INSTANCE_DEVICE_PATH_SUBTYPE    0x01
#define END_DEVICE_PATH_TYPE                0x7F
#define END_ENTIRE_DEVICE_PATH_SUBTYPE      0xFF

#define DP_IS_END_TYPE(a)
#define DP_IS_END_SUBTYPE(a)        ( ((a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )

#define DevicePathType(a)           ( ((a)->Type) & EFI_DP_TYPE_MASK )
#define DevicePathSubType(a)        ( (a)->SubType )
#define DevicePathNodeLength(a)     ( ((a)->Length[0]) | ((a)->Length[1] << 8) )

#define IsDevicePathEndType(a)      ( DevicePathType(a) == END_DEVICE_PATH_TYPE )
#define IsDevicePathEndSubType(a)   ( (a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )
#define IsDevicePathEnd(a)          ( IsDevicePathEndType(a) && IsDevicePathEndSubType(a) )
#define NextDevicePathNode(a)       ( (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + DevicePathNodeLength(a)))


#define MBR_SIGNATURE               0xaa55

#define EXTENDED_DOS_PARTITION      0x05
#define EXTENDED_WINDOWS_PARTITION  0x0F

#define MAX_MBR_PARTITIONS          4

#define PMBR_GPT_PARTITION          0xEE
#define EFI_PARTITION               0xEF

#define MBR_SIZE                    512


//---------------------------------------------------------------------------
//      Structure Definitions
//---------------------------------------------------------------------------
#pragma pack(push, 1)

//
// ------------------------------------------------------------------
// Name: Data_Structures
//
// Description:
//      Data Structures needed for MBR
//
//      MASTER_BOOT_RECORD - Data Structure definition of the
//          MBR located in the first block on an MBR drive
//
//      MBR_PARTITION - Data Structure definition for each
//          partition in the MBR
//
// ------------------------------------------------------------------
//
#pragma pack(1)

///
/// Data Structure definition for each partition in the MBR
///
typedef struct _MBR_PARTITION {
  UINT8 BootIndicator;
  UINT8 StartHead;
  UINT8 StartSector;
  UINT8 StartTrack;
  UINT8 OSIndicator;
  UINT8 EndHead;
  UINT8 EndSector;
  UINT8 EndTrack;
  UINT8 StartingLBA[4];
  UINT8 SizeInLBA[4];
} MBR_PARTITION_RECORD;

///
/// Data Structure definition of the MBR located in the first block on an MBR drive
///
typedef struct _MASTER_BOOT_RECORD {
  UINT8                 BootStrapCode[440];
  UINT8                 UniqueMbrSignature[4];
  UINT8                 Unknown[2];
  MBR_PARTITION_RECORD  Partition[MAX_MBR_PARTITIONS];
  UINT16                Signature;
} MASTER_BOOT_RECORD;


#define EFI_GPT_HEADER_ID  "EFI PART"


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
} GPT_HEADER;


///
/// GPT Partition Table Header.
///
typedef struct {
  ///
  /// The table header for the GPT partition Table.
  /// This header contains EFI_PTAB_HEADER_ID.
  ///
  EFI_TABLE_HEADER  Header;
  ///
  /// The LBA that contains this data structure.
  ///
  EFI_LBA           MyLBA;
  ///
  /// LBA address of the alternate GUID Partition Table Header.
  ///
  EFI_LBA           AlternateLBA;
  ///
  /// The first usable logical block that may be used
  /// by a partition described by a GUID Partition Entry.
  ///
  EFI_LBA           FirstUsableLBA;
  ///
  /// The last usable logical block that may be used
  /// by a partition described by a GUID Partition Entry.
  ///
  EFI_LBA           LastUsableLBA;
  ///
  /// GUID that can be used to uniquely identify the disk.
  ///
  EFI_GUID          DiskGUID;
  ///
  /// The starting LBA of the GUID Partition Entry array.
  ///
  EFI_LBA           PartitionEntryLBA;
  ///
  /// The number of Partition Entries in the GUID Partition Entry array.
  ///
  UINT32            NumberOfPartitionEntries;
  ///
  /// The size, in bytes, of each the GUID Partition
  /// Entry structures in the GUID Partition Entry
  /// array. This field shall be set to a value of 128 x 2^n where n is
  /// an integer greater than or equal to zero (e.g., 128, 256, 512, etc.).
  ///
  UINT32            SizeOfPartitionEntry;
  ///
  /// The CRC32 of the GUID Partition Entry array.
  /// Starts at PartitionEntryLBA and is
  /// computed over a byte length of
  /// NumberOfPartitionEntries * SizeOfPartitionEntry.
  ///
  UINT32            PartitionEntryArrayCRC32;
} EFI_PARTITION_TABLE_HEADER;

///
/// GPT Partition Entry.
///
typedef struct {
  ///
  /// Unique ID that defines the purpose and type of this Partition. A value of
  /// zero defines that this partition entry is not being used.
  ///
  EFI_GUID  PartitionTypeGUID;
  ///
  /// GUID that is unique for every partition entry. Every partition ever
  /// created will have a unique GUID.
  /// This GUID must be assigned when the GUID Partition Entry is created.
  ///
  EFI_GUID  UniquePartitionGUID;
  ///
  /// Starting LBA of the partition defined by this entry
  ///
  EFI_LBA   StartingLBA;
  ///
  /// Ending LBA of the partition defined by this entry.
  ///
  EFI_LBA   EndingLBA;
  ///
  /// Attribute bits, all bits reserved by UEFI
  /// Bit 0:      If this bit is set, the partition is required for the platform to function. The owner/creator of the
  ///             partition indicates that deletion or modification of the contents can result in loss of platform
  ///             features or failure for the platform to boot or operate. The system cannot function normally if
  ///             this partition is removed, and it should be considered part of the hardware of the system.
  ///             Actions such as running diagnostics, system recovery, or even OS install or boot, could
  ///             potentially stop working if this partition is removed. Unless OS software or firmware
  ///             recognizes this partition, it should never be removed or modified as the UEFI firmware or
  ///             platform hardware may become non-functional.
  /// Bit 1:      If this bit is set, then firmware must not produce an EFI_BLOCK_IO_PROTOCOL device for
  ///             this partition. By not producing an EFI_BLOCK_IO_PROTOCOL partition, file system
  ///             mappings will not be created for this partition in UEFI.
  /// Bit 2:      This bit is set aside to let systems with traditional PC-AT BIOS firmware implementations
  ///             inform certain limited, special-purpose software running on these systems that a GPT
  ///             partition may be bootable. The UEFI boot manager must ignore this bit when selecting
  ///             a UEFI-compliant application, e.g., an OS loader.
  /// Bits 3-47:  Undefined and must be zero. Reserved for expansion by future versions of the UEFI
  ///             specification.
  /// Bits 48-63: Reserved for GUID specific use. The use of these bits will vary depending on the
  ///             PartitionTypeGUID. Only the owner of the PartitionTypeGUID is allowed
  ///             to modify these bits. They must be preserved if Bits 0-47 are modified..
  ///
  UINT64    Attributes;
  ///
  /// Null-terminated name of the partition.
  ///
  CHAR16    PartitionName[36];
} EFI_PARTITION_ENTRY;




typedef struct tdEFI_GPT_DATA {
  EFI_PARTITION_TABLE_HEADER  EfiPartitionHeader;
  UINTN                       NumberOfPartitions; 
  EFI_PARTITION_ENTRY         Partitions[1];
} EFI_GPT_DATA;

#define TPM20_PP_NO_ACTION                               0
#define TPM20_PP_CLEAR_CONTROL_CLEAR                     5
#define TPM20_PP_CLEAR_CONTROL_CLEAR_2                   14
#define TPM20_PP_SET_NO_PPI_CLEAR_FALSE                  17
#define TPM20_PP_SET_NO_PPI_CLEAR_TRUE                   18
#define TPM20_PP_CLEAR_CONTROL_CLEAR_3                   21
#define TPM20_PP_CLEAR_CONTROL_CLEAR_4                   22

#define TPM20_PP_NO_ACTION_MAX                           20


typedef UINT8  TPMI_YES_NO;
typedef UINT32 ClearControl_In;
typedef UINT32 Clear_In;

#pragma pack(push, 1)

typedef struct {
  TPM_ST tag;
  UINT32 paramSize;
  TPM_CC commandCode;
} INT_TPM2_COMMAND_HEADER;

typedef struct {
  TPM_ST tag;
  UINT32 paramSize;
  TPM_RC responseCode;
} INT_TPM2_RESPONSE_HEADER;

typedef struct {
  INT_TPM2_COMMAND_HEADER   Header;
  TPMI_RH_CLEAR             Auth;
  UINT32                    AuthorizationSize;
  TPMS_AUTH_SESSION_COMMAND PwapAuth;
  TPMI_YES_NO               Disable;
} TPM2_CLEAR_CONTROL_COMMAND;

typedef struct {
  INT_TPM2_RESPONSE_HEADER  Header;
  UINT32                    ParameterSize;
  TPMS_AUTH_SESSION_COMMAND PwapAuthSeq;
} TPM2_CLEAR_CONTROL_RESPONSE;

typedef struct {
  INT_TPM2_COMMAND_HEADER   Header;
  TPMI_RH_CLEAR             Auth;
  UINT32                    AuthorizationSize;
  TPMS_AUTH_SESSION_COMMAND PwapAuth;
} TPM2_CLEAR_COMMAND;

typedef struct {
  INT_TPM2_RESPONSE_HEADER  Header;
  UINT32                    ParameterSize;
  TPMS_AUTH_SESSION_COMMAND PwapAuthSeq;
} TPM2_CLEAR_RESPONSE;


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

#define EFI_TCG_PLATFORM_PROTOCOL_GUID  \
  { 0x8c4c9a41, 0xbf56, 0x4627, 0x9e, 0xa, 0xc8, 0x38, 0x6d, 0x66, 0x11, 0x5c }


#pragma pack(pop)
#pragma pack(pop)

//**********************************************************************
//              Function Declarations
//**********************************************************************



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
