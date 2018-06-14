//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/FFS.h 9     5/22/12 10:20a Artems $
//
// $Revision: 9 $
//
// $Date: 5/22/12 10:20a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/FFS.h $
// 
// 9     5/22/12 10:20a Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	In certain cases system may hang
// [RootCause]  	File Efi.h was included inside #pragma <stack> statement,
// which may lead to different offsets in Boot and Runtime services
// functions
// [Solution]  	Moved Efi.h out of #pragma statement
// [Files]  		FFS.h
// 
// 8     3/16/11 11:32p Felixp
// Several identifiers have been updated to match with the latest revision
// of the PI spec.
// 
// 7     3/09/11 5:36p Artems
// PI 1.0 clean-up
// 
// 6     2/05/11 1:50p Artems
// Added PI 1.0-1.1 support
// 
// 5     8/20/10 12:43p Felixp
// 
// 4     8/20/10 12:41p Felixp
// Customized compression type (EFI_CUSTOMIZED_COMPRESSION) is added.
// 
// 3     4/12/06 1:19p Felixp
// 
// 2     3/13/06 1:15a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 3     1/24/05 2:23p Felixp
// clean up
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 4     10/21/04 2:45p Felixp
// pack(1) added (EFI_COMPRESSION_SECTION_HEADER asked for it)
// 
// 3     12/16/03 5:08p Markw
// Removed some duplicate definitions.
// 
// 2     12/16/03 5:06p Markw
// Changed tabs to spaces.
// 
// 1     12/16/03 1:06p Markw
// Created. Contains structs and definitions for Firmware Volume, Files,
// Sections.
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    FFS.H
//
// Description:    
// Filesystem headers from specifications:
//  Intel Platform Innovation Framework for EFI Firmware Volume Specification
// 
//  Intel Platform Innovation Framework for EFI Firmware File System Specification
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __FFS__H__
#define __FFS__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>
#pragma pack(push,1)


//*************************************************
// EFI_FVB_ATTRIBUTES
//*************************************************
typedef UINT32 EFI_FVB_ATTRIBUTES;
typedef UINT32 EFI_FVB_ATTRIBUTES_2;
// Attributes bit definitions
#if PI_SPECIFICATION_VERSION < 0x00010000
#define EFI_FVB_READ_DISABLED_CAP   0x00000001
#define EFI_FVB_READ_ENABLED_CAP    0x00000002
#define EFI_FVB_READ_STATUS         0x00000004
#define EFI_FVB_WRITE_DISABLED_CAP  0x00000008
#define EFI_FVB_WRITE_ENABLED_CAP   0x00000010
#define EFI_FVB_WRITE_STATUS        0x00000020
#define EFI_FVB_LOCK_CAP            0x00000040
#define EFI_FVB_LOCK_STATUS         0x00000080
#define EFI_FVB_STICKY_WRITE        0x00000200
#define EFI_FVB_MEMORY_MAPPED       0x00000400
#define EFI_FVB_ERASE_POLARITY      0x00000800
#define EFI_FVB_ALIGNMENT_CAP       0x00008000
#define EFI_FVB_ALIGNMENT_2         0x00010000
#define EFI_FVB_ALIGNMENT_4         0x00020000
#define EFI_FVB_ALIGNMENT_8         0x00040000
#define EFI_FVB_ALIGNMENT_16        0x00080000
#define EFI_FVB_ALIGNMENT_32        0x00100000
#define EFI_FVB_ALIGNMENT_64        0x00200000
#define EFI_FVB_ALIGNMENT_128       0x00400000
#define EFI_FVB_ALIGNMENT_256       0x00800000
#define EFI_FVB_ALIGNMENT_512       0x01000000
#define EFI_FVB_ALIGNMENT_1K        0x02000000
#define EFI_FVB_ALIGNMENT_2K        0x04000000
#define EFI_FVB_ALIGNMENT_4K        0x08000000
#define EFI_FVB_ALIGNMENT_8K        0x10000000
#define EFI_FVB_ALIGNMENT_16K       0x20000000
#define EFI_FVB_ALIGNMENT_32K       0x40000000
#define EFI_FVB_ALIGNMENT_64K       0x80000000

#else //#if PI_SPECIFICATION_VERSION < 0x00010000

#define EFI_FVB2_READ_DISABLED_CAP  0x00000001
#define EFI_FVB2_READ_ENABLED_CAP   0x00000002
#define EFI_FVB2_READ_STATUS        0x00000004
#define EFI_FVB2_WRITE_DISABLED_CAP 0x00000008
#define EFI_FVB2_WRITE_ENABLED_CAP  0x00000010
#define EFI_FVB2_WRITE_STATUS       0x00000020
#define EFI_FVB2_LOCK_CAP           0x00000040
#define EFI_FVB2_LOCK_STATUS        0x00000080
#define EFI_FVB2_STICKY_WRITE       0x00000200
#define EFI_FVB2_MEMORY_MAPPED      0x00000400
#define EFI_FVB2_ERASE_POLARITY     0x00000800
#define EFI_FVB2_READ_LOCK_CAP      0x00001000
#define EFI_FVB2_READ_LOCK_STATUS   0x00002000
#define EFI_FVB2_WRITE_LOCK_CAP     0x00004000
#define EFI_FVB2_WRITE_LOCK_STATUS  0x00008000
#define EFI_FVB2_ALIGNMENT          0x001F0000
#define EFI_FVB2_ALIGNMENT_1        0x00000000
#define EFI_FVB2_ALIGNMENT_2        0x00010000
#define EFI_FVB2_ALIGNMENT_4        0x00020000
#define EFI_FVB2_ALIGNMENT_8        0x00030000
#define EFI_FVB2_ALIGNMENT_16       0x00040000
#define EFI_FVB2_ALIGNMENT_32       0x00050000
#define EFI_FVB2_ALIGNMENT_64       0x00060000
#define EFI_FVB2_ALIGNMENT_128      0x00070000
#define EFI_FVB2_ALIGNMENT_256      0x00080000
#define EFI_FVB2_ALIGNMENT_512      0x00090000
#define EFI_FVB2_ALIGNMENT_1K       0x000A0000
#define EFI_FVB2_ALIGNMENT_2K       0x000B0000
#define EFI_FVB2_ALIGNMENT_4K       0x000C0000
#define EFI_FVB2_ALIGNMENT_8K       0x000D0000
#define EFI_FVB2_ALIGNMENT_16K      0x000E0000
#define EFI_FVB2_ALIGNMENT_32K      0x000F0000
#define EFI_FVB2_ALIGNMENT_64K      0x00100000
#define EFI_FVB2_ALIGNMENT_128K     0x00110000
#define EFI_FVB2_ALIGNMENT_256K     0x00120000
#define EFI_FVB2_ALIGNMNET_512K     0x00130000
#define EFI_FVB2_ALIGNMENT_1M       0x00140000
#define EFI_FVB2_ALIGNMENT_2M       0x00150000
#define EFI_FVB2_ALIGNMENT_4M       0x00160000
#define EFI_FVB2_ALIGNMENT_8M       0x00170000
#define EFI_FVB2_ALIGNMENT_16M      0x00180000
#define EFI_FVB2_ALIGNMENT_32M      0x00190000
#define EFI_FVB2_ALIGNMENT_64M      0x001A0000
#define EFI_FVB2_ALIGNMENT_128M     0x001B0000
#define EFI_FVB2_ALIGNMENT_256M     0x001C0000
#define EFI_FVB2_ALIGNMENT_512M     0x001D0000
#define EFI_FVB2_ALIGNMENT_1G       0x001E0000
#define EFI_FVB2_ALIGNMENT_2G       0x001F0000

#endif //#if PI_SPECIFICATION_VERSION < 0x00010000

// Extended Header Header. Located via ExtHeaderOffset.
// The extended headers follow each other in memory and are 
// terminated by ExtHeaderType EFI_FV_EXT_TYPE_END
typedef struct {
  UINT16  ExtEntrySize;
  UINT16  ExtEntryType;
} EFI_FIRMWARE_VOLUME_EXT_ENTRY;

// GUID that maps OEM file types to GUIDs
#define EFI_FV_EXT_TYPE_OEM_TYPE  0x01
typedef struct {
  EFI_FIRMWARE_VOLUME_EXT_ENTRY   Hdr;
  UINT32                          TypeMask;
  EFI_GUID                        Types[1];
} EFI_FIRMWARE_VOLUME_EXT_HEADER_OEM_TYPE;

// Unique name of the FV
typedef struct {
  EFI_GUID          FvName;
  UINT32            ExtHeaderSize;
} EFI_FIRMWARE_VOLUME_EXT_HEADER;


//************************************************************
// EFI_FV_FILE_ATTRIBUTES
//************************************************************
typedef UINT32 EFI_FV_FILE_ATTRIBUTES;
#define EFI_FV_FILE_ATTRIB_ALIGNMENT 0x0000001F

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        FvBlockMapEntry
//
// Description: This describes the Firmware Volume Flash Block Structure.
//              It is used in the Firmware Volume Header. There maybe
//              multiple entries in the array. The array ends with
//              NumBlocks=BlockLength=0
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//        NumBlocks        UINT32       Number of blocks of same size
//        BlockLength      UINT32       Length of each block.
//
//**********************************************************************
typedef struct {
	UINT32 NumBlocks;
	UINT32 BlockLength;
} FvBlockMapEntry;

#define FV_SIGNATURE 'HVF_'

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_FIRMWARE_VOLUME_HEADER
//
// Description: This is the header for each firmware volume.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//	      ZeroVector[16]    UINT8	   Volume is created with all zeros.			
//                                     Utility may modify these values,
//                                     such as a jump address.
//                                      
//	      FileSystemGuid    EFI_GUID   Name of File System
//	      FvLength          UINT64     Length of File System				
//	      Signature         UINT32     _FVH				
//	      Attributes        EFI_FVB_ATTRIBUTES
//	      HeaderLength      UINT16			
//	      Checksum          UINT16     Header sums to zero.				
//	      Reserved[3]       UINT8				
//	      Revision          UINT8	   Current revision of header.
//	      FvBlockMap[1]     FvBlockMapEntry
//                                      See	definition of FvBlockMapEntry.
//                                      This is a variable array.
//
//**********************************************************************
typedef struct {
	UINT8               ZeroVector[16];
	EFI_GUID            FileSystemGuid;
	UINT64              FvLength;
	UINT32              Signature;
#if PI_SPECIFICATION_VERSION < 0x00010000
	EFI_FVB_ATTRIBUTES    Attributes;
#else
	EFI_FVB_ATTRIBUTES_2  Attributes;
#endif
	UINT16              HeaderLength;
	UINT16              Checksum;
    UINT16              ExtHeaderOffset;
    UINT8               Reserved[1];
	UINT8               Revision;
	FvBlockMapEntry     FvBlockMap[1];	
} EFI_FIRMWARE_VOLUME_HEADER;



typedef UINT8 EFI_FV_FILETYPE;

#define EFI_FV_FILETYPE_ALL                     0x00
#define EFI_FV_FILETYPE_RAW                     0x01
#define EFI_FV_FILETYPE_FREEFORM                0x02
#define EFI_FV_FILETYPE_SECURITY_CORE           0x03
#define EFI_FV_FILETYPE_PEI_CORE                0x04
#define EFI_FV_FILETYPE_DXE_CORE                0x05
#define EFI_FV_FILETYPE_PEIM                    0x06
#define EFI_FV_FILETYPE_DRIVER                  0x07
#define EFI_FV_FILETYPE_COMBINED_PEIM_DRIVER    0x08
#define EFI_FV_FILETYPE_APPLICATION             0x09
// The value 0x0A is reserved and should not be used
#define EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE   0x0B
#define EFI_FV_FILETYPE_SMM                     0x0A
#define EFI_FV_FILETYPE_COMBINED_SMM_DXE        0x0C
#define EFI_FV_FILETYPE_SMM_CORE                0x0D
#define EFI_FV_FILETYPE_OEM_MIN                 0xc0
#define EFI_FV_FILETYPE_OEM_MAX                 0xdf
#define EFI_FV_FILETYPE_DEBUG_MIN               0xe0
#define EFI_FV_FILETYPE_DEBUG_MAX               0xef
#define EFI_FV_FILETYPE_FFS_MIN                 0xf0
#define EFI_FV_FILETYPE_FFS_MAX                 0xff

// 7A9354D9-0468-444a-81CE-0BF617D890DF
#define EFI_FIRMWARE_FILE_SYSTEM_GUID \
	{0x7A9354D9,0x0468,0x444a,0x81,0xCE,0x0B,0xF6,0x17,0xD8,0x90,0xDF}

#define EFI_FIRMWARE_FILE_SYSTEM2_GUID \
    { 0x8c8ce578, 0x8a3d, 0x4f1c, { 0x99, 0x35, 0x89, 0x61, 0x85, 0xc3, 0x2d, 0xd3 } }

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_FFS_INTEGRITY_CHECK  
//
// Description: This union make it easier to access the filed that
//               can be either a checksum or Tail Reference.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//        struct Checksum
//          Header         UINT8
//          File           UINT8
//        TailReference    UINT16
//
//**********************************************************************
typedef union {
    struct {
        UINT8	Header;
        UINT8	File;
    } Checksum;
#if PI_SPECIFICATION_VERSION < 0x00010000
    UINT16 TailReference;
#else
    UINT16 Checksum16;
#endif
} EFI_FFS_INTEGRITY_CHECK;

//************************************************************
// EFI_FFS_FILE_ATTRIBUTES
//************************************************************
typedef UINT8 EFI_FFS_FILE_ATTRIBUTES;
// FFS File Attributes
#if PI_SPECIFICATION_VERSION < 0x00010000
#define FFS_ATTRIB_TAIL_PRESENT     0x01
#define FFS_ATTRIB_RECOVERY         0x02
#define FFS_ATTRIB_HEADER_EXTENSION 0x04
#else
#define FFS_ATTRIB_LARGE_FILE       0x01
#define FFS_ATTRIB_FIXED            0x04
#endif
#define FFS_ATTRIB_DATA_ALIGNMENT   0x38
#define FFS_ATTRIB_CHECKSUM         0x40

//************************************************************
// EFI_FFS_FILE_STATE
//************************************************************
typedef UINT8 EFI_FFS_FILE_STATE;
// FFS File State Bits
#define EFI_FILE_HEADER_CONSTRUCTION    0x01
#define EFI_FILE_HEADER_VALID           0x02
#define EFI_FILE_DATA_VALID             0x04
#define EFI_FILE_MARKED_FOR_UPDATE      0x08
#define EFI_FILE_DELETED                0x10
#define EFI_FILE_HEADER_INVALID         0x20

#if PI_SPECIFICATION_VERSION < 0x00010000
typedef UINT16 EFI_FFS_FILE_TAIL;
#endif

#define EFI_FV_FILETYPE_FFS_PAD 0xF0


//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_FFS_FILE_HEADER
//
// Description: Each file has this header. Each FFS File Header must be
//               8-bytes aligned.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//        Name             EFI_GUID				
//        IntegrityCheck   EFI_FFS_INTEGRITY_CHECK	
//        Type             EFI_FV_FILETYPE			
//        Attributes       EFI_FFS_FILE_ATTRIBUTES 
//        Size[3]          UINT8					
//        State            EFI_FFS_FILE_STATE		
//
//**********************************************************************
typedef struct {
	EFI_GUID                Name;
	EFI_FFS_INTEGRITY_CHECK IntegrityCheck;
	EFI_FV_FILETYPE         Type;
	EFI_FFS_FILE_ATTRIBUTES Attributes;
	UINT8                   Size[3];
	EFI_FFS_FILE_STATE      State;
} EFI_FFS_FILE_HEADER;


// {1BA0062E-C779-4582-8566-336AE8F78F09}
#define EFI_FFS_VOLUME_TOP_FILE_GUID \
	{0x1BA0062E,0xC779,0x4582,0x85,0x66,0x33,0x6A,0xE8,0xF7,0x8F,0x9};

//************************************************************
// EFI_SECTION_TYPE
//************************************************************
typedef UINT8 EFI_SECTION_TYPE;
//************************************************************
// The section type EFI_SECTION_ALL is a pseudo type. It is
// used as a wild card when retrieving sections. The section
// type EFI_SECTION_ALL matches all section types.
//************************************************************

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_COMMON_SECTION_HEADER
//
// Description: Each section type has this common header. Each section
//               must be 4-byte aligned.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//	      Size[3]          UINT8
//	      Type             EFI_SECTION_TYPE
//
//**********************************************************************
typedef struct {
    UINT8               Size[3];
    EFI_SECTION_TYPE    Type;
} EFI_COMMON_SECTION_HEADER;

#define EFI_SECTION_ALL 0x00

//************************************************************
// Encapsulation section Type values
//************************************************************
#define EFI_SECTION_COMPRESSION     0x01
#define EFI_SECTION_GUID_DEFINED    0x02
//************************************************************
// Leaf section Type values
//************************************************************
#define EFI_SECTION_PE32                    0x10
#define EFI_SECTION_PIC                     0x11
#define EFI_SECTION_TE                      0x12
#define EFI_SECTION_DXE_DEPEX               0x13
#define EFI_SECTION_VERSION                 0x14
#define EFI_SECTION_USER_INTERFACE          0x15
#define EFI_SECTION_COMPATIBILITY16         0x16
#define EFI_SECTION_FIRMWARE_VOLUME_IMAGE   0x17
#define EFI_SECTION_FREEFORM_SUBTYPE_GUID   0x18
#define EFI_SECTION_RAW                     0x19
#define EFI_SECTION_PEI_DEPEX               0x1B
#define EFI_SECTION_SMM_DEPEX               0x1C

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_COMPRESSION_SECTION_HEADER
//
// Description: T
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//
//**********************************************************************
typedef struct {
    UINT32  UncompressedLength;
    UINT8   CompressionType;
} EFI_COMPRESSION_SECTION_HEADER;

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_COMPRESSION_SECTION_HEADER
//
// Description: T
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//
//**********************************************************************
typedef struct {
    EFI_COMMON_SECTION_HEADER       CommonHeader;
//TODO: This definition DOES not match FV spec. However, that's how it is defined in EDK
//    EFI_COMPRESSION_SECTION_HEADER  CompressionHeader;
  UINT32                    UncompressedLength;
  UINT8                     CompressionType;
} EFI_COMPRESSION_SECTION;

//************************************************************
// CompressionType values
//************************************************************
#define EFI_NOT_COMPRESSED          0x00
#define EFI_STANDARD_COMPRESSION    0x01
#define EFI_CUSTOMIZED_COMPRESSION  0x02

typedef struct {
    EFI_COMMON_SECTION_HEADER   CommonHeader;
    EFI_GUID                    SectionDefinitionGuid;
    UINT16                      DataOffset;
    UINT16                      Attributes;
} EFI_GUID_DEFINED_SECTION;

//*****************************************************
// Bit values for GuidedSectionHeader.Attributes
//*****************************************************
#define EFI_GUIDED_SECTION_PROCESSING_REQUIRED  0x01
#define EFI_GUIDED_SECTION_AUTH_STATUS_VALID    0x02

typedef struct {
    EFI_COMMON_SECTION_HEADER   CommonHeader;
    UINT16                      BuildNumber;
    CHAR16                      VersionString[1];
} EFI_VERSION_SECTION;

typedef struct {
    EFI_COMMON_SECTION_HEADER   CommonHeader;
    EFI_GUID                    SubTypeGuid;
} EFI_FREEFORM_SUBTYPE_GUID_SECTION;

typedef struct {
    EFI_COMMON_SECTION_HEADER   CommonHeader;
    CHAR16                      FileNameString[1];
} EFI_USER_INTERFACE_SECTION;

typedef EFI_COMMON_SECTION_HEADER EFI_PE32_SECTION;
typedef EFI_COMMON_SECTION_HEADER EFI_PIC_SECTION;
typedef EFI_COMMON_SECTION_HEADER EFI_TE_SECTION;
typedef EFI_COMMON_SECTION_HEADER EFI_COMPATIBILITY16_SECTION;
typedef EFI_COMMON_SECTION_HEADER EFI_FIRMWARE_VOLUME_IMAGE_SECTION;

#pragma pack(pop)
/****** DO NOT WRITE BELOW THIS LINE *******/
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
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************