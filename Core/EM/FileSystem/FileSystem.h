//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/FileSystem/FileSystem.h 13    10/24/11 10:56a Artems $
//
// $Revision: 13 $
//
// $Date: 10/24/11 10:56a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/FileSystem/FileSystem.h $
// 
// 13    10/24/11 10:56a Artems
// EIP 73254: Remove "magic number" from source, added new #define macro
// 
// 12    5/05/11 3:44p Pats
// [TAG] - EIP 58999 
// [Category]- BUG FIX
// [Severity]- Major
// [Symptom] - Cannot launch Shell from USB Filesystem device in Debug
// mode with latest Filesystem driver.
// [RootCause] - Functions using DISKIO were raising TPL to a fixed level.
// [Solution] - Modified above functions to check for the higher of the
// fixed level or current level.
// [Files] - Info.c, MediaAccess.c, Open.c, FileSystem.h
// 
// 11    6/11/10 5:41p Pats
// EIP 39171: Long name sometimes not displayed, only short name.
// FetchLongName() in Open.c did not handle case where long name spilt
// over 2 clusters. Function modified to handle the case.
// Prototype changed here in this file.
// 
// 10    8/28/09 11:59a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 9     7/02/09 5:47p Pats
// Updated to latest coding standard. No code changes.
//
// 8     4/13/07 7:07p Pats
// Edited to conform with coding standards. No code changes.
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: FileSystem.h
//
// Description: Header file for Simple File System driver
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#ifndef _SimpleFileSystem_
#define _SimpleFileSystem_

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------

#include <Efi.h>
#include <Token.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include "Protocol\PciIo.h"
#include "Protocol\DevicePath.h"
#include "protocol\DriverBinding.h"
#include "protocol\BlockIo.h"
#include "protocol\DiskIo.h"
#include "Protocol\PDiskInfo.h"
#include "Protocol\SimpleFileSystem.h"
#include "Protocol\UnicodeCollation.h"
#include "Protocol\LoadedImage.h"
#include <Protocol\ComponentName.h>

#define     SIMPLE_FILE_SYSTEM_DRIVER_VERSION       0x010000
#define     BS_OEMName_Offset           3
#define     BPB_BytePerSec_Offset       11
#define     BPB_SecPerClus_Offset       13
#define     BPB_RsvdSecCnt_Offset       14
#define     BPB_NumFATs_Offset          16
#define     BPB_RootEntCnt_Offset       17
#define     BPB_TotSec16_Offset         19
#define     BPB_Media_Offset            21
#define     BPB_FATSz16_Offset          22
#define     BPB_SecPerTrk_Offset        24
#define     BPB_NumHeads_Offset         26
#define     BPB_Hiddsec_Offset          28
#define     BPB_TotSec32_Offset         32


#define     BS_DrvNum_Offset            36
#define     BS_Reserved1_Offset         37
#define     BS_BootSig_Offset           38
#define     BS_VolID_Offset             39
#define     BS_VolLab_Offset            43
#define     BS_FilSysType_Offset        54

#define     BPB_FATSz32_Offset          36
#define     BPB_ExtFlags_Offset         40
#define     BPB_FSVer_Offset            42
#define     BPB_RootClus_Offset         44
#define     BPB_FSInfo_Offset           48
#define     BPB_BkBootSec_Offset        50
#define     BPB_Rserved_Offset          52
#define     BS_DrvNum_32_Offset         64
#define     BS_Reserved1_32_Offset      65
#define     BS_BootSig_32_Offset        66
#define     BS_VolID_32_Offset          67
#define     BS_VolLab_32_Offset         71
#define     BS_FilSysType_32_Offset     82

#define     ATTR_READ_ONLY              0x01
#define     ATTR_HIDDEN                 0x02
#define     ATTR_SYSTEM                 0x04
#define     ATTR_VOLUME_ID              0x08
#define     ATTR_DIRECTORY              0x10
#define     ATTR_ARCHIVE                0x20
#define     ATTR_LONG_NAME              (ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID)
#define     ATTR_LONG_NAME_MASK         (ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID | ATTR_ARCHIVE | ATTR_DIRECTORY)

#define     DIR_ENTRY_ERASE             0xE5
#define     MAX_LFN_LENGTH              255
#define     MAX_TOTAL_PATH_LENGTH       260
#define     MAX_LFN_SLOTS               20

#define     MEMBLOCKSIZE                0x8000
#define     MEMALLOCSIZE                0x40
#define     MAX_OPEN_FHS                0x20
#define     FSI_Free_Count              488
#define     FSI_Nxt_Free                492

#pragma pack(1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        FAT_DATE
//
// Description: File date structure
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct {
        UINT16 Day : 5;
        UINT16 Month : 4;
        UINT16 Year : 7;          // From 1980
    } FAT_DATE;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        FAT_TIME
//
// Description: File time structure
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct {
        UINT16 DoubleSecond : 5;
        UINT16 Minute : 6;
        UINT16 Hour : 5;
    } FAT_TIME;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        FAT_DATE_TIME
//
// Description: Contains FAT_TIME and FAT_DATE
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct {
        FAT_TIME Time;
        FAT_DATE Date;
    } FAT_DATE_TIME;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        FAT_TYPE
//
// Description: Enumeration of fat types
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef enum {
        FAT12 = 1,
        FAT16,
        FAT32,
        FAT_UNKNOWN
    } FAT_TYPE;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        REGIONS
//
// Description: Enumeration of volume regions
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef enum {
        RESERVED_REGION,
        FAT_REGION,
        DIRECTORY_REGION,
        DATA_REGION
    } REGIONS;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        ACCESS_METHOD
//
// Description: Enumeration of access methods (read or write)
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef enum {
        READ_BLOCK,
        WRITE_BLOCK
    } ACCESS_METHOD;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        DIR_ENTRY_32
//
// Description: Structure of a FAT32 directory entry
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct _DIR_ENTRY_32 {
    
        UINT8 Dir_Name[11];
        UINT8 Dir_Attr;
        UINT8 Dir_NTRes;
        UINT8 Dir_CrtTimeTenth;
        UINT16 Dir_CrtTime;
        UINT16 Dir_CrtDate;
        UINT16 Dir_LstAccDate;
        UINT16 Dir_FstClusHI;
        UINT16 Dir_WrtTime;
        UINT16 Dir_WrtDate;
        UINT16 Dir_FstClusLO;
        UINT32 Dir_FileSize;
        
    } DIR_ENTRY_32;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        DIR_ENTRY_LFN
//
// Description: Structure of a long file name directory entry
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct _DIR_ENTRY_LFN {
        UINT8 Dir_Order;                    // Sequence number for slot
        CHAR16 Dir_Name0_4[5];              // First 5 Unicode characters
        UINT8 Dir_Attr;                     // Attributes, always 0x0F
        UINT8 Dir_Reserved;                 // Reserved, always 0x00
        UINT8 Dir_Checksum;                 // Checksum of 8.3 name
        CHAR16 Dir_Name5_10[6];             // 6 more Unicode characters
        UINT16 Dir_FstClus;                 // First cluster number, must be 0
        CHAR16 Dir_Name11_12[2];            // Last 2 Unicode characters
    } DIR_ENTRY_LFN;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        BPB_COMMON
//
// Description: Structure of the common part of the BIOS parameter block
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct  _BPB_COMMON {
        UINT8 BS_JmpBoot[3];
        UINT8 BS_OEMName[8];
        UINT16 BPB_BytePerSec;
        UINT8 BPB_SecPerClus;
        UINT16 BPB_RsvdSecCnt;
        UINT8 BPB_NumFATs;
        UINT16 BPB_RootEntCnt;
        UINT16 BPB_TotSec16;
        UINT8 BPB_Media;
        UINT16 BPB_FATSz16;
        UINT16 BPB_SecPerTrk;
        UINT16 BPB_NumHeads;
        UINT32 BPB_Hiddsec;
        UINT32 BPB_TotSec32;
    } BPB_COMMON;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        BPB_FAT_12_16
//
// Description: Structure of the FAT 12 or 16 unique part of the BPB
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct  _BPB_FAT_12_16 {
        UINT8 BS_DrvNum;
        UINT8 BS_Reserved1;
        UINT8 BS_BootSig;
        UINT32 BS_VolID;
        UINT8 BS_VolLab[11];
        UINT8 BS_FilSysType[8];
    } BPB_FAT_12_16;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        BPB_FAT_32
//
// Description: Structure of the FAT 32 unique part of the BPB
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct  _BPB_FAT_32 {
        UINT32 BPB_FATSz32;
        UINT16 BPB_ExtFlags;
        UINT16 BPB_FSVer;
        UINT32 BPB_RootClus;
        UINT16 BPB_FSInfo;
        UINT16 BPB_BkBootSec;
        UINT8 BPB_Rserved[12];
        UINT8 BS_DrvNum_32;
        UINT8 BS_Reserved1_32;
        UINT8 BS_BootSig_32;
        UINT8 BS_VolID_32[4];
        UINT8 BS_VolLab_32[11];
        UINT8 BS_FilSysType_32[8];
    } BPB_FAT_32;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        VOLUME_BPB
//
// Description: Structure of the Volume BIOS Parameter Block. Combines common,
//              FAT 12-16, and FAT 32 parts
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct  _VOLUME_BPB {
        UINT8 BS_JmpBoot[3];
        UINT8 BS_OEMName[8];
        UINT16 BPB_BytePerSec;
        UINT8 BPB_SecPerClus;
        UINT16 BPB_RsvdSecCnt;
        UINT8 BPB_NumFATs;
        UINT16 BPB_RootEntCnt;
        UINT16 BPB_TotSec16;
        UINT8 BPB_Media;
        UINT16 BPB_FATSz16;
        UINT16 BPB_SecPerTrk;
        UINT16 BPB_NumHeads;
        UINT32 BPB_Hiddsec;
        UINT32 BPB_TotSec32;
        union {
            BPB_FAT_12_16 BPB_FAT1216;
            BPB_FAT_32 BPB_FAT32;
        } BPB_FAT;
    } VOLUME_BPB;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        VOLUME_INFO
//
// Description: Structure containing all Volume Information
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct _VOLUME_INFO {
    
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL SimpleFileSystemProtocol;       // This should be the first entry in this structure
        EFI_HANDLE VolumeHandle;
        EFI_STATUS VolumeStatus;                            // Global status that can be used by any open handles
        
        FAT_TYPE FatType;
        UINT32 EOCMark;
        VOLUME_BPB VolumeBPB;
        BOOLEAN ValidVolumeID;
        CHAR16 VolumeID[12];
        CHAR16 *FileSystemName;
        UINT8 BytesPerSecPowerof2;
        UINT32 BytesPerCluster;
        UINT32 FirstRootDirSector;
        UINT32 RootDirSectorCount;                          // 0 for FAT32
        UINT32 FATSz;                                       // Size of 1 FAT
        UINT32 TotalSectors;
        UINT32 DataSectors;
        UINT32 CountOfDataClusters;
        
//  Volume information for EFI_FILE_SYSTEM_INFO
        UINT64 VolumeSize;
        UINT32 FreeSpaceinClusters;
        UINT32 FreeSpaceinSector1;
        UINT32 BlockSize;
        BOOLEAN ReadOnly;
        UINT32 LastFreeCluster;
        UINT32 FreeClusterBlocks;
        
        EFI_DISK_IO_PROTOCOL *DiskIo;
        EFI_BLOCK_IO_PROTOCOL *BlkIo;
        UINT32 MediaID;
        EFI_UNICODE_COLLATION_PROTOCOL *UnicodeCollationInterface;
        
        UINT32 AllocatedMemorySize;
        UINT32 TotalDirEntryList;
        UINT32 AllowedFatCacheSize;
        UINT32 AllowedDirCacheSize;
        UINT32 FATCacheSize;
        UINT32 DirCacheSize;
        UINT32 *TempBuffer;
        UINT32 *CacheBuffer;
        BOOLEAN TempBufferInUse;
        struct _FILE_HANDLE * RootFH;
        DLIST OpenFHs;
        DLIST OpenFIs;
        DLIST CacheList;
        DLIST MemList;
        
    } VOLUME_INFO;
    
    
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        FILE_HANDLE
//
// Description: Structure containing File Handle information
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct _FILE_HANDLE {
    
        VOLUME_INFO *VolumeInterface;
        EFI_STATUS HandleStatus;
        BOOLEAN ROOTDIR;
        
        CHAR16 *FileNameLFN;                        // Points to the long Filename if not points to 8.3
        DIR_ENTRY_32 DirectoryEntry;                // 8.3 entry
        
        UINT32 DirCluster;                          // Cluster at which this entry is present. For Root directory (FAT12/16) it is the sector count.
        UINT32 DirOffset;                           // Offset with in the cluster
        UINT16 InstancesCount;                      // No of Instances opened so far
        UINT32 SlotNumber;                          // Same as in DIR_ENTRY_LIST
        UINT32 FreeDirEntryCluster;                 // For FAT12/16 and ROOT directory, not valid.
        UINT32 FreeDirEntryOffset;                  //
        
        BOOLEAN DirEntryChanged;
        BOOLEAN DirListChanged;
        struct _FILE_HANDLE *Parent;                // Points to the parent directory
        DLIST DirList;                              // List if Directory Entries
        DLINK ViFHLink;                             // This link is for the DLIST OpenFHs in VOLUME_INFO
        
        DLIST ChildList;
        DLINK ChildLink;
        
    } FILE_HANDLE;
    
    
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        FILE_HANDLE_INSTANCE
//
// Description: Structure containing File Handle Instance information
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct _FILE_HANDLE_INSTANCE {
    
        EFI_FILE_PROTOCOL FileHandle;                       // Should be the first entry in the structure
        EFI_STATUS HandleInstanceStatus;
        FILE_HANDLE *pFH;
        UINT64 OpenMode;                            // Open Modes
        UINT64 Position;                            //
        UINT32 CurrentCluster;                      // will point to sector number where the position is pointing currently
        UINT32 CurrentClusterOffset;                        // will point to sector number where the position is pointing currently
        BOOLEAN MEDIA_NOT_VALID;                    // Will be true if for any reason current instances cannot use the volume Eg: Change in Media
        DLINK ViFILink;                             // This link is for the DLIST OpenFIs in the VOLUME_INFO
        
    } FILE_HANDLE_INSTANCE;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        DIR_ENTRY_LIST
//
// Description: Structure containing directory entry information
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct {
    
        DIR_ENTRY_32 DirectoryEntry;                // 8.3 entry
        CHAR16 *FileNameLFN;                        // Points to the long Filename if not points to 8.3
        UINT32 Cluster;                             // Not valid for FAT12/16 ROOT
        UINT32 Offset;                              // For ROOT Fat12/16, offset is from the beginning.
        UINT32 SlotNumber;                          // Used for EFI DIR
        DLINK DirLink;                              //
        
    } DIR_ENTRY_LIST;
    

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        CACHE_HEADER
//
// Description: Structure containing cache header information
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct {
    
        UINT64 AbsoluteOffset;
        UINT64 AbsoluteOffsetEnd;
        UINT8 *Buffer;
        BOOLEAN DIRTY_FLAG;
        REGIONS DataRegion;
        DLINK CacheLink;
        
    } CACHE_HEADER;
    
    
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        MEM_HEADER
//
// Description: Structure containing memory header information
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

    typedef struct {
    
        UINTN AddresMap;
        UINT32 AddresMapLength;
        UINTN BufferStart;
        UINTN BufferEnd;
        DLINK MemLink;
        
    } MEM_HEADER;
    
#pragma pack()
    
#define FIRSTCLUSTER(D) (((UINT32) D.Dir_FstClusHI << 16) + (UINT32) D.Dir_FstClusLO)
#define CLUSTERSREQUIRED(N) (N + Vol->BytesPerCluster - 1) / Vol->BytesPerCluster
#define  FAT12_EOC(EntryValue)  (EntryValue >= 0x0FF8)
#define  FAT16_EOC(EntryValue)  (EntryValue >= 0xFFF8)
#define  FAT32_EOC(EntryValue)  (EntryValue >= 0x0FFFFFF8)
    
    
    EFI_STATUS
    SimpleFileSystemSupported(
        IN EFI_DRIVER_BINDING_PROTOCOL *This,
        IN EFI_HANDLE                  Controller,
        IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
    );
    
    EFI_STATUS
    SimpleFileSystemStart (
        IN EFI_DRIVER_BINDING_PROTOCOL *This,
        IN EFI_HANDLE                  Controller,
        IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
    );
    
    EFI_STATUS
    SimpleFileSystemStop (
        IN EFI_DRIVER_BINDING_PROTOCOL *This,
        IN EFI_HANDLE                  Controller,
        IN UINTN                       NumberOfChildren,
        IN EFI_HANDLE                  *ChildHandleBuffer
    );
    
    EFI_STATUS
    FileSystemInitUnicodeCollation (
        IN EFI_DRIVER_BINDING_PROTOCOL        *This,
        IN OUT EFI_UNICODE_COLLATION_PROTOCOL **gFileSystemUnicodeCollationInterface
    );
    
    EFI_STATUS
    DetectInstallVolume(
        IN EFI_DISK_IO_PROTOCOL  *DiskIo,
        IN EFI_BLOCK_IO_PROTOCOL *BlkIo,
        IN EFI_HANDLE            Handle
    );
    
    EFI_STATUS
    DetectVolume (
        VOLUME_INFO *VolumeInterface,
        BOOLEAN     StatusCheck
    );
    
    EFI_STATUS
    OpenVolume (
        IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
        OUT EFI_FILE_PROTOCOL              **Root
    );
    
    EFI_STATUS
    OpenRoot(
        IN VOLUME_INFO     *VolumeInfo,
        IN OUT FILE_HANDLE **Root
    );
    
    EFI_STATUS
    CreateFileHandleInstance (
        IN FILE_HANDLE              *Root,
        IN OUT FILE_HANDLE_INSTANCE **FileInstance,
        IN UINT64                   OpenMode
    );
    
    void
    InitEFIFileInterface (
        EFI_FILE_PROTOCOL *EFIFileInterface
    );
    
    EFI_STATUS
    OpenVolume (
        IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
        OUT EFI_FILE_PROTOCOL              **Root
    );
    
    EFI_STATUS
    OpenFileHandle (
        IN EFI_FILE_PROTOCOL  *This,
        OUT EFI_FILE_PROTOCOL **NewHandle,
        IN CHAR16             *FileName,
        IN UINT64             OpenMode,
        IN UINT64             Attributes
    );
    
    EFI_STATUS
    CloseFileHandle (
        IN EFI_FILE_PROTOCOL *This
    );
    
    EFI_STATUS
    DeleteFileHandle (
        IN EFI_FILE_PROTOCOL *This
    );
    
    EFI_STATUS
    ReadFileHandle (
        IN EFI_FILE_PROTOCOL *This,
        IN OUT UINTN         *BufferSize,
        OUT VOID             *Buffer
    );
    
    EFI_STATUS
    WriteFileHandle (
        IN EFI_FILE_PROTOCOL *This,
        IN OUT UINTN         *BufferSize,
        IN VOID              *Buffer
    );
    
    EFI_STATUS
    GetPositionFileHandle (
        IN EFI_FILE_PROTOCOL *This,
        IN UINT64            *Position
    );
    
    EFI_STATUS
    SetPositionFileHandleThis (
        IN EFI_FILE_PROTOCOL *This,
        OUT UINT64           Position
    );
    
    
    EFI_STATUS
    SetPositionFileHandle (
        IN FILE_HANDLE_INSTANCE *fhi,
        IN UINT64               Position
    );
    
    EFI_STATUS
    GetInfoFileHandle (
        IN EFI_FILE_PROTOCOL *This,
        IN EFI_GUID          *InformationType,
        IN OUT UINTN         *BufferSize,
        OUT VOID             *Buffer
    );
    
    
    EFI_STATUS
    SetInfoFileHandle (
        IN EFI_FILE_PROTOCOL *This,
        IN EFI_GUID          *InformationType,
        IN UINTN             BufferSize,
        IN VOID              *Buffer
    );
    
    EFI_STATUS
    FlushFileHandle (
        IN EFI_FILE_PROTOCOL *This
    );
    
    EFI_STATUS
    ProcessOpenFileHandle(
        IN FILE_HANDLE_INSTANCE *ParentFi,
        IN CHAR16               **FileName,
        OUT EFI_FILE_PROTOCOL   **NewHandle,
        IN UINT64               OpenMode,
        IN UINT64               Attributes
    );
    
    EFI_STATUS
    CreateDirectoryEntry (
        IN FILE_HANDLE  *fh,
        IN CHAR16       *NextCompName,
        OUT FILE_HANDLE **fh1,
        IN UINT64       Attributes
    );
    
    EFI_STATUS
    CreateDirEntryInDisk (
        IN FILE_HANDLE *fh,
        IN CHAR16      *NextCompName,
        IN UINT64      Attributes,
        OUT UINT32     *FreeDirCluster,
        OUT UINT32     *FreeDirClusterOffset,
        DIR_ENTRY_32   *Entry
    );
    
    BOOLEAN
    FindMatchingFH (
        IN VOLUME_INFO  *Vi,
        IN CHAR16       *NextCompName,
        IN FILE_HANDLE  *fh,
        OUT FILE_HANDLE **fh1
    );
    
    EFI_STATUS
    ReadAllDirectoryEntries (
        IN FILE_HANDLE *fh
    );
    
    EFI_STATUS
    CreateFHFromDirEntryList(
        IN DIR_ENTRY_LIST *Del,
        IN FILE_HANDLE    *fh,
        OUT FILE_HANDLE   **fh1
    );
    
    BOOLEAN
    FindMatchingDirEntry (
        IN FILE_HANDLE     *fh,
        IN CHAR16          *NextCompName,
        OUT DIR_ENTRY_LIST **Del
    );
    
    BOOLEAN
    FindMatchingSFNDirEntry (
        IN FILE_HANDLE     *fh,
        IN CHAR8           *ShortFileName,
        OUT DIR_ENTRY_LIST **Del
    );
    
    EFI_STATUS
    AddToDirList (
        FILE_HANDLE  *fh,
        DIR_ENTRY_32 DirectoryEntry,
        CHAR16       *lfn,
        UINT32       Cluster,
        UINT32       Offset,
        UINT32       SlotNumber
    );
    
    EFI_STATUS
    GetDirListAtPosition(
        FILE_HANDLE    *Pfh,
        UINT64         Position,
        DIR_ENTRY_LIST **Del
    );
    
    EFI_STATUS
    GetNextCompName (
        IN OUT CHAR16 **FileName,
        IN CHAR16     *NextCompName
    );
    
    void
    RemoveDirEntries (
        IN FILE_HANDLE *Rfh,
        IN FILE_HANDLE *fh
    );
    
    EFI_STATUS
    RemoveFH (
        FILE_HANDLE *fh
    );
    
    EFI_STATUS
    FreeUpDirEntries (
        VOLUME_INFO *vi,
        FILE_HANDLE *pfh
    );
    
    EFI_STATUS
    FreeUpFHEntries (
        VOLUME_INFO *vi,
        FILE_HANDLE *pfh
    );
    
    EFI_STATUS
    RemoveAllDirList(
        FILE_HANDLE *lfh
    );
    
    
    EFI_STATUS
    RemoveDirList (
        FILE_HANDLE    *fh,
        DIR_ENTRY_LIST *Del
    );
    
    BOOLEAN
    FatLfnIsValid (
        CHAR16 *Name
    );
    
    EFI_STATUS
    fsAllocateMemory (
        VOLUME_INFO *vi,
        UINT32      Size,
        VOID        **Buffer,
        BOOLEAN     CLEAR
    );
    
    EFI_STATUS
    fsDeAllocateMemory (
        VOLUME_INFO *vi,
        void        *Buffer
    );
    
    EFI_STATUS
    GetVolumeLabel (
        VOLUME_INFO  *vi,
        IN OUT UINTN *BufferSize,
        OUT VOID     *Buffer
    );
    
    EFI_STATUS
    SetVolumeLabel (
        VOLUME_INFO *vi,
        IN UINTN    BufferSize,
        OUT VOID    *Buffer
    );
    
    EFI_STATUS
    GetfileInfo (
        IN FILE_HANDLE_INSTANCE *fhi,
        IN OUT UINTN            *BufferSize,
        OUT VOID                *Buffer
    );
    
    EFI_STATUS
    SetfileInfo (
        IN EFI_FILE_PROTOCOL    *This,
        IN FILE_HANDLE_INSTANCE *fhi,
        IN UINTN                BufferSize,
        OUT VOID                *Buffer
    );
    
    EFI_STATUS
    GetFileInfoFromFH (
        FILE_HANDLE  *Pfh,
        IN OUT UINTN *BufferSize,
        OUT VOID     *Buffer
    );
    
    VOID
    FatToEfiTime (
        EFI_TIME *EfiTime,
        UINT16   Date,
        UINT16   Time
    );
    
    VOID
    EfiToFatTime (
        EFI_TIME EfiTime,
        UINT16   *Date,
        UINT16   *Time
    );
    
    EFI_STATUS
    GetSystemInfo (
        IN VOLUME_INFO           *vi,
        IN OUT UINTN             *BufferSize,
        OUT EFI_FILE_SYSTEM_INFO *Buffer
    );
    
    EFI_STATUS
    SetSystemInfo (
        IN VOLUME_INFO           *vi,
        IN UINTN                 BufferSize,
        OUT EFI_FILE_SYSTEM_INFO *Buffer
    );
    
    UINT32
    ReturnFreeSpace (
        IN VOLUME_INFO *vi
    );
    
    EFI_STATUS
    GetVolumeLabel (
        IN VOLUME_INFO *vi,
        IN OUT UINTN   *BufferSize,
        OUT VOID       *Buffer
    );
    
    UINT8
    LfnChecksum(
        UINT8 *D
    );
    
    UINT8
    FetchLongName (
        FILE_HANDLE  *fh,
        DIR_ENTRY_32 *Buffer,
        UINT32       BufferPos,
        UINT16       *Name,
        UINT32       ClusterNumber,
        UINT32       ClusterSize
    );
    
    BOOLEAN
    FindShortName (
        UINT8  *Buffer,
        UINT32 *Offset,
        UINT32 BufferSize
    );
    
    EFI_STATUS
    FsReadMedia (
        VOLUME_INFO *vi,
        UINT8       *Buffer,
        UINT64      Sector,
        UINT32      Offset,
        UINT32      ByteCount,
        REGIONS     DataRegion
    );
    
    EFI_STATUS
    FsWriteMedia (
        VOLUME_INFO *vi,
        UINT8       *Buffer,
        UINT64      SectorCount,
        UINT32      Offset,
        UINT32      ByteCount,
        REGIONS     DataRegion
    );
    
    void
    HandleDiskIoError (
        VOLUME_INFO *vi,
        EFI_STATUS  Status
        
    );
    
    ExtractShortFileName (
        VOLUME_INFO         *Vi,
        CHAR16              *lfn,
        UINT8               *Buffer
    );
    
    EFI_STATUS
    CheckCached (
        VOLUME_INFO  *vi,
        UINT64       AbsoluteOffset,
        UINT32       ByteCount,
        UINT8        **cBuffer,
        UINT32       *cBufferLength,
        CACHE_HEADER **ch,
        REGIONS      DataRegion
    );
    
    BOOLEAN
    IsCacheHit (
        VOLUME_INFO  *vi,
        REGIONS      DataRegion,
        UINT64       AbsoluteOffset,
        UINT32       ByteCount,
        UINT8        **cBuffer,
        UINT32       *cBufferLength,
        CACHE_HEADER **ch1
    );
    
    void
    CreateSpaceforCache (
        VOLUME_INFO  *vi,
        UINT32       ByteCount,
        REGIONS      DataRegion,
        CACHE_HEADER **ch1
    );
    
    EFI_STATUS
    ReadClusterOfDirectoryEntries (
        IN FILE_HANDLE *fh,
        IN UINT32      ClusterNumber,
        OUT UINT32     *ClusterRead,
        UINT8          *Buffer,
        UINT32         *BufferSize
    );
    
    EFI_STATUS
    ReadFatClusterNumber (
        IN VOLUME_INFO *Vol,
        IN UINT32      Cluster,
        IN UINT8       FatNumber,
        OUT UINT32     *Value
    );
    
    EFI_STATUS
    FatClusterNumberLocation (
        IN VOLUME_INFO *Vol,
        IN UINT32      Cluster,
        IN UINT8       FatNumber,
        OUT UINT32     *Sector,
        OUT UINT32     *SectorOffset
    );
    
    EFI_STATUS
    WriteFatClusterNumber (
        IN VOLUME_INFO *Vol,
        IN UINT32      Cluster,
        IN UINT8       FatNumber,
        IN UINT32      Value
    );
    
    EFI_STATUS
    UnlinkFat (
        IN VOLUME_INFO *Vol,
        IN UINT32      Cluster,
        OUT UINT32     *ClusterCount
    );
    
    EFI_STATUS
    FindFreeClusters (
        IN VOLUME_INFO *Vol,
        IN UINT32      From,
        IN UINT32      To,
        OUT UINT32     *StartCluster,
        IN OUT UINT32  *FreeClusters,
        OUT UINT32     *TotalFree
    );
    
    EFI_STATUS
    FindNextFreeCluster (
        IN VOLUME_INFO *Vol,
        OUT UINT32     *Cluster
    );
    
    EFI_STATUS
    GetFreeClusterCount (
        IN VOLUME_INFO *Vol,
        OUT UINT32     *FreeClustersCount,
        OUT UINT32     *FreeClusterBlock,
        OUT UINT32     *FreeBlockCount
    );
    
    UINT32
    ClusterToSector (
        IN VOLUME_INFO *Vol,
        IN UINT32      Cluster
    );
    
    UINT32
    SectorToCluster (
        IN VOLUME_INFO *Vol,
        IN OUT UINT32  Sector
    );
    
    EFI_STATUS
    GetClusterCount (
        IN VOLUME_INFO *Vol,
        IN OUT UINT32  Cluster
    );
    
    int
    Wcscmpcaseinsensitive(
        CHAR16 *string1,
        CHAR16 *string2
    );
    
    EFI_STATUS
    ReadFromFile (
        IN FILE_HANDLE_INSTANCE *File,
        IN OUT VOID             *Buffer,
        IN OUT UINT32           *Size,
        IN REGIONS              DataRegion
    );
    
    EFI_STATUS
    WriteToFile (
        IN FILE_HANDLE_INSTANCE *File,
        IN OUT VOID             *Buffer,
        IN OUT UINT32           *Size,
        IN REGIONS              DataRegion
    );
    
    
    EFI_STATUS
    AllocateFirstCluster (
        IN FILE_HANDLE_INSTANCE *File,
        OUT UINT32              *Cluster
    );
    
    EFI_STATUS
    AllocateAndLinkClusters (
        IN VOLUME_INFO *Vol,
        IN UINT32      BeginCluster,
        IN UINT32      Size,
        OUT UINT32     *FirstCluster,
        OUT UINT32     *ClusterCount
    );
    
    static int AllocateAndLinkNewCluster (
        VOLUME_INFO *Vol,
        IN UINT32   PrevCluster,
        OUT UINT32  *Cluster
    );
    
    
    EFI_STATUS
    ExtendFile (
        IN FILE_HANDLE_INSTANCE *fhi,
        IN UINT32               Length
    );
    
    EFI_STATUS
    GetContiguousClusters (
        IN VOLUME_INFO *Vol,
        IN UINT32      Size,
        IN OUT UINT32  Cluster,
        OUT UINT32     *LastCluster,
        OUT UINT32     *Count
    );
    
    VOID
    GetAbsSectorInfo (
        IN VOLUME_INFO *Vol,
        IN UINT32      Cluster,
        IN UINT32      ClusterOffset,
        OUT UINT32     *Sector,
        OUT UINT32     *SectorOffset
    );
    
    EFI_STATUS
    GetClusterPosition (
        IN FILE_HANDLE_INSTANCE *File,
        IN UINT64               Position,
        OUT UINT32              *Cluster,
        OUT UINT32              *ClusterOffset
    );
    
    UINT32
    GetEocValue (
        IN VOLUME_INFO *Vol
    );
    
    EFI_STATUS
    ValidateCurrentStatus (
        FILE_HANDLE_INSTANCE *fhi
    );
    
    VOID
    GetSectorAddressDir (
        FILE_HANDLE *fh,
        UINT32      Cluster,
        UINT32      ClusterOffset,
        UINT32      *Sector,
        UINT32      *SectorOffset
    );
    
    EFI_STATUS
    UpdateAccAndWriteTime (
        IN OUT DIR_ENTRY_LIST *del
    );
    
    EFI_STATUS
    UpdateAccDate(
        IN OUT DIR_ENTRY_LIST *del
    );
    
    BOOLEAN
    UpdateAccDateRequired (
        IN OUT DIR_ENTRY_LIST *del
    );
    
    EFI_STATUS
    GetSpaceforDirEntry(
        IN FILE_HANDLE *fh,
        IN UINT32      FreeBytesRequired,
        OUT UINT32     *FreeDirCluster,
        OUT UINT32     *FreeDirClusterOffset,
        BOOLEAN        *LastDirEntry
    );
    
    EFI_STATUS
    CheckforValidDirSpace (
        IN VOLUME_INFO *Vi,
        IN BOOLEAN     ROOTDIR,
        IN UINT32      Cluster,
        IN UINT32      Offset,
        IN UINT32      FreeBytesRequired,
        IN UINT32      *FreeDirCluster,
        IN UINT32      *FreeDirClusterOffset
    );
    
    EFI_STATUS
    LocateFreeDirEntry(
        IN FILE_HANDLE *fh,
        IN UINT32      FreeBytesRequired,
        OUT UINT32     *FreeDirCluster,
        OUT UINT32     *FreeDirClusterOffset,
        BOOLEAN        *LastDirEntry
    );
    
    EFI_STATUS
    GenShortFilename (
        IN VOLUME_INFO *Vol,
        IN CHAR16      *InPath,
        OUT CHAR8      *ShortName
    );
    
    EFI_STATUS
    UpdateDirListFromFHDir (
        FILE_HANDLE *fh
    );
    
    EFI_STATUS
    LocateDel (
        DLINK          *dlink,
        UINT32         Cluster,
        UINT32         ClusterOffset,
        DIR_ENTRY_LIST **Del,
        UINT32         *Position
    );
    
    EFI_STATUS
    GenUniqueShortFname (
        IN FILE_HANDLE *fh,
        IN CHAR16      *LongName,
        OUT CHAR8      *ShortName,
        OUT BOOLEAN    *LfnNeeded
    );
    
    EFI_STATUS
    SplitLFN (
        IN CHAR16         *LongName,
        IN DIR_ENTRY_32   *ShortEntry,
        OUT DIR_ENTRY_LFN *Slot,
        OUT UINT32        *NumSlots
    );
    
    EFI_STATUS
    ZeroOutdisk (
        IN VOLUME_INFO *Vi,
        IN UINT32      Cluster,
        IN UINT32      ClusterOffset,
        IN UINT32      Size
    );
    
    EFI_STATUS
    ShrinkClusters (
        IN VOLUME_INFO *Vol,
        IN UINT32      StartCluster,
        IN UINT32      ClusterCount
    );
    
    UINT32
    GetClustersRequired (
        IN VOLUME_INFO *Vol,
        IN UINT32      N
    );
    
    EFI_STATUS
    UpdateFreeSpace (
        IN VOLUME_INFO *vi,
        IN UINT32      Count,
        IN BOOLEAN     Add
    );
    
    EFI_STATUS
    FreeUpResources (
        VOLUME_INFO *vi,
        EFI_STATUS  Status
    );
    
    EFI_STATUS
    MarkVolumeDirty (
        IN VOLUME_INFO *vi
    );
    
    EFI_STATUS
    UnloadSimpleFileSystemDriver (
        IN EFI_HANDLE ImageHandle
    );
    
    void
    Zeromemory (
        void   *Buffer,
        UINT32 Size
    );
    
    EFI_STATUS
    CheckFileWrite (
        FILE_HANDLE_INSTANCE *fhi,
        BOOLEAN              IgnoreOpenMode
    );
    
    VOID EfiInitializeDriverLib(
        IN EFI_HANDLE       ImageHandle,
        IN EFI_SYSTEM_TABLE *SystemTable
    );
    
    EFI_STATUS
    InternalMemAllocate (
        VOLUME_INFO *vi,
        UINT32      Size,
        VOID        **Buffer,
        BOOLEAN     CLEAR
    );
    
    EFI_STATUS
    AddBlocktoInternalMemManager (
        VOLUME_INFO *vi
    );
    
    EFI_STATUS
    GetMemory (
        MEM_HEADER *Mem,
        UINT32     Blocks,
        VOID       **Buffer,
        BOOLEAN    CLEAR
    );
    
    EFI_STATUS
    FreeMemory (
        VOLUME_INFO *vi,
        VOID        *Buffer
    );
    
    
    VOID
    GetTempBuffer (
        VOLUME_INFO *vi,
        VOID        **Buffer
    );
    
    VOID
    ReleaseTempBuffer (
        VOLUME_INFO *vi
    );
    
    void
    PrintOpenfhiandfh  (
        VOLUME_INFO *vi
    );
    
    VOID Labcpy(
        CHAR16 *string1,
        CHAR16 * string2
    );
    
    UINTN Lablen(
        CHAR16 *string
    );
    
    EFI_TPL
    FindNextTpl (
    EFI_TPL     TplLevel
    );

    VOID EfiDebugPrint (
        IN UINTN ErrorLevel,
        IN CHAR8 *Format,
        ...
    );
    
    /****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
