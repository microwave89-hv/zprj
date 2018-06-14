//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/Partition/ElTorito.h 5     7/09/09 5:01p Oleksiyy $
//
// $Revision: 5 $
//
// $Date: 7/09/09 5:01p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/Partition/ElTorito.h $
// 
// 5     7/09/09 5:01p Oleksiyy
// Files clean-up
//
// 4     1/16/09 3:02p Felixp
// New Feature:
// CD-ROM handling code is updated to create additional logical instance
// of the Bock I/O protocol
// based on primary volume descriptor of the CR-ROM.
// The instance is used by the ISO 9660 file systems driver
// (separate eModule. Not part of the Core) to implement file system
// protocol.
// The new parittion driver funcionality is only enabled when ISO 9660
// file systems driver
// ($/Source/Modules/FsIso9660) is included into the project.
//
// 2     12/02/04 5:54p Robert
// Partition driver version works
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    <ElTorito.h>
//
// Description: EFI El Torito Partition Generic Driver Header.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EL_TORITO_H__
#define __EL_TORITO_H__

#define CDROM_BOOT_PRI_VOL_DESCRIPTOR_SECTOR    16
#define CDROM_BOOT_REC_VOL_DESCRIPTOR_SECTOR    17

#define CDROM_BLOCK_SIZE        2048

#define CDROM_BOOTABLE          0x88


#define NO_EMULATION            0x00
#define FLOPPY_12               0x01
#define FLOPPY_144              0x02
#define FLOPPY_288              0x03
#define HARD_DRIVE              0x04


#define HD_BLOCK_SIZE           512
#define FLOPPY_144_SIZE_LBA     720
#define FLOPPY_288_SIZE_LBA     1440
#define FLOPPY_12_SIZE_LBA      615

#define EL_TORITO_SPEC "EL TORITO SPECIFICATION"

// {BA7C46D1-9C5E-4fc8-943D-1A491F23FE01}
#define AMI_ISO9660_MEDIA_GUID \
    { 0xba7c46d1, 0x9c5e, 0x4fc8, 0x94, 0x3d, 0x1a, 0x49, 0x1f, 0x23, 0xfe, 0x1 }


//<AMI_GHDR_START>
//------------------------------------------------------------------
// Name: Data_Structures
//
// Description:
//      Data Structures needed for El Torito
//
//      BOOT_RECORD - Data Structure definition of a boot record
//          that is contained within an El Torito Disk
//
//      EL_TORITO_ENTRIES - A union of possible structs that could be
//          contained within an entry on the disk
//
//------------------------------------------------------------------
//<AMI_GHDR_END>
#pragma pack(1)

typedef struct _BOOT_RECORD
{
    UINT8       BootIndicator;
    CHAR8       IsoId[5];
    UINT8       Version;
    CHAR8       Identifier[32];
    UINT8       Unused[32];
    UINT32      BootCatalog;
    UINT8       Unused2[5];
    UINT32      VolSpaceSize[2];
} BOOT_RECORD_DESC;



typedef union
{
    struct
    {
        UINT8   HeaderId;
        UINT8   PlatformId;
        UINT16  Res0;
        CHAR8   Id[24];
        UINT16  Checksum;
        UINT16  Sig;
    } ValEntry;
    
    
    struct
    {
        UINT8   BootId;
        UINT8   MediaType;
        UINT16  LoadSegment;
        UINT8   SystemType;
        UINT8   Unused;
        UINT16  SectorCount;
        UINT32  LoadLba;
    } DefaultEntry;
    
    
    struct
    {
        UINT8   HeaderId;
        UINT8   PlatformId;
        UINT16  NumSectionEntries;
        CHAR8   IdString[28];
    } SecHeader;
    
    
    struct
    {
        UINT8   BootId;
        UINT8   MediaType;
        UINT16  LoadSegment;
        UINT8   SystemType;
        UINT8   Unused;
        UINT16  SectorCount;
        UINT32  LoadLba;
        UINT8   SelectionType;
        UINT8   Criteria[19];
    } SecEntry;
    
} EL_TORITO_ENTRIES;

typedef struct
{
    UINT8   VolDescType;
    CHAR8   StdId[5];
    UINT8   VolDescVer;
} VOLUME_DESCRIPTOR_HEADER;

typedef struct
{
    UINT32  Year;
    UINT16  Month;
    UINT16  Day;
    UINT16  Hour;
    UINT16  Minute;
    UINT16  Second;
    UINT16  HSecond;
    INT8    Offset;
} CD_DATE_TIME;

typedef struct
{
    UINT8  Year;
    UINT8  Month;
    UINT8  Day;
    UINT8  Hour;
    UINT8  Minute;
    UINT8  Second;
    INT8    Offset;
} FILE_DATE_TIME;

typedef struct
{
    UINT8   RecordLength;
    UINT8   ExtAttrRecLength;
    UINT64  StartLba;
    UINT64  DataLength;
    FILE_DATE_TIME  RecTime;
    UINT8   Flags;
    UINT8   FileUnitSize;
    UINT8   InterleaveGap;
    UINT32  VolSeqNum;
    UINT8   FileIdLength;
    UINT8   FileId[1];
} ROOT_DIR_HEADER;

typedef struct
{
    VOLUME_DESCRIPTOR_HEADER Header;
    UINT8   Flags;
    CHAR8   SysId[32];
    CHAR8   VolId[32];
    UINT64  Unused;
    UINT64  VolSpaceSize;
    CHAR8   EscSeq[32];
    UINT32  VolSetSize;
    UINT32  VolSeqNum;
    UINT32  LBlockSize;
    UINT64  PathTblSize;
    UINT32  LPathTbl1;
    UINT32  LPathTbl2;
    UINT32  MPathTbl1;
    UINT32  MPathTbl2;
    ROOT_DIR_HEADER Root;
    CHAR8   VolSetId[128];
    CHAR8   PublisherId[128];
    CHAR8   DataPrepId[128];
    CHAR8   ApplicationId[128];
    CHAR8   CopyrightFileId[37];
    CHAR8   AbstractFileId[37];
    CHAR8   BiblioFileId[37];
    CD_DATE_TIME CreationTime;
    CD_DATE_TIME ModifyTime;
    CD_DATE_TIME ExpireTime;
    CD_DATE_TIME EffectiveTime;
    UINT8   FileStrucVer;
    UINT8   Unused1;
} PRIMARY_VOLUME_DESC_HEADER;

typedef struct
{
    VENDOR_DEVICE_PATH Dp;
    UINT64             VolumeSize;
    ROOT_DIR_HEADER    Root;
    CHAR8              VolumeLabel[32];
} AMI_ISO9660_DEVICE_PATH;

#pragma pack()

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
