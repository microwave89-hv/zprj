//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/FirmwareVolume.h 4     6/16/11 3:22p Felixp $
//
// $Revision: 4 $
//
// $Date: 6/16/11 3:22p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/FirmwareVolume.h $
// 
// 4     6/16/11 3:22p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 3     5/27/11 5:53p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 2     2/05/11 2:30p Artems
// Added PI 1.0-1.1 compatibility
// 
// 1     3/13/06 1:38a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 4     12/31/03 2:41p Markw
// Fix structure help
// 
// 3     12/19/03 2:21p Markw
// Add EFI_FV_... Attribute definition
// 
// 2     12/18/03 12:53p Markw
// Header changes
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	FirmwareVolume.h 
//
// Description:	This file is an include file used to define the Protocol for the
//		        Firmware Volume Protocol.
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef __FIRMWARE_VOLUME_PROTOCOL_H__
#define __FIRMWARE_VOLUME_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <FFS.h>

#if BACKWARD_COMPATIBLE_MODE && PI_SPECIFICATION_VERSION>=0x00010000
#include <Protocol/FirmwareVolume2.h>    
#define EFI_FIRMWARE_VOLUME_PROTOCOL_GUID EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID
GUID_VARIABLE_DECLARATION(gEfiFirmwareVolumeProtocolGuid, EFI_FIRMWARE_VOLUME_PROTOCOL_GUID);
typedef EFI_FIRMWARE_VOLUME2_PROTOCOL EFI_FIRMWARE_VOLUME_PROTOCOL;

#else
// 389F751F-1838-4388-8390-CD8154BD27F8
#define EFI_FIRMWARE_VOLUME_PROTOCOL_GUID \
    {0x389F751F,0x1838,0x4388,0x83,0x90,0xCD,0x81,0x54,0xBD,0x27,0xF8}

GUID_VARIABLE_DECLARATION(gEfiFirmwareVolumeProtocolGuid, EFI_FIRMWARE_VOLUME_PROTOCOL_GUID);

//************************************************************
// EFI_FV_ATTRIBUTES
//************************************************************
typedef UINT64 EFI_FV_ATTRIBUTES;

//************************************************************
// EFI_FV_ATTRIBUTES bit definitions
//************************************************************
#define EFI_FV_READ_DISABLE_CAP         0x0000000000000001
#define EFI_FV_READ_ENABLE_CAP          0x0000000000000002
#define EFI_FV_READ_STATUS              0x0000000000000004
#define EFI_FV_WRITE_DISABLE_CAP        0x0000000000000008
#define EFI_FV_WRITE_ENABLE_CAP         0x0000000000000010
#define EFI_FV_WRITE_STATUS             0x0000000000000020
#define EFI_FV_LOCK_CAP 		        0x0000000000000040
#define EFI_FV_LOCK_STATUS 		        0x0000000000000080
#define EFI_FV_WRITE_POLICY_RELIABLE    0x0000000000000100
#define EFI_FV_ALIGNMENT_CAP            0x0000000000008000
#define EFI_FV_ALIGNMENT_2              0x0000000000010000
#define EFI_FV_ALIGNMENT_4              0x0000000000020000
#define EFI_FV_ALIGNMENT_8              0x0000000000040000
#define EFI_FV_ALIGNMENT_16             0x0000000000080000
#define EFI_FV_ALIGNMENT_32             0x0000000000100000
#define EFI_FV_ALIGNMENT_64             0x0000000000200000
#define EFI_FV_ALIGNMENT_128            0x0000000000400000
#define EFI_FV_ALIGNMENT_256            0x0000000000800000
#define EFI_FV_ALIGNMENT_512            0x0000000001000000
#define EFI_FV_ALIGNMENT_1K             0x0000000002000000
#define EFI_FV_ALIGNMENT_2K             0x0000000004000000
#define EFI_FV_ALIGNMENT_4K             0x0000000008000000
#define EFI_FV_ALIGNMENT_8K             0x0000000010000000
#define EFI_FV_ALIGNMENT_16K            0x0000000020000000
#define EFI_FV_ALIGNMENT_32K            0x0000000040000000
#define EFI_FV_ALIGNMENT_64K            0x0000000080000000


struct _EFI_FIRMWARE_VOLUME_PROTOCOL;
typedef struct _EFI_FIRMWARE_VOLUME_PROTOCOL EFI_FIRMWARE_VOLUME_PROTOCOL;

typedef EFI_STATUS (EFIAPI * EFI_FV_GET_ATTRIBUTES) (
    IN EFI_FIRMWARE_VOLUME_PROTOCOL *This,
    OUT EFI_FV_ATTRIBUTES           *FvAttributes);


typedef EFI_STATUS (EFIAPI * EFI_FV_SET_ATTRIBUTES) (
    IN EFI_FIRMWARE_VOLUME_PROTOCOL *This,
    IN OUT EFI_FV_ATTRIBUTES        *FvAttributes);

typedef EFI_STATUS (EFIAPI * EFI_FV_READ_FILE) (
    IN EFI_FIRMWARE_VOLUME_PROTOCOL *This,
    IN EFI_GUID                     *NameGuid,
    IN OUT VOID                     **Buffer,
    IN OUT UINTN                    *BufferSize,
    OUT EFI_FV_FILETYPE             *FoundType,
    OUT EFI_FV_FILE_ATTRIBUTES      *FileAttributes,
    OUT UINT32                      *AuthenticationStatus);

typedef EFI_STATUS (EFIAPI * EFI_FV_READ_SECTION) (
    IN EFI_FIRMWARE_VOLUME_PROTOCOL *This,
    IN EFI_GUID                     *NameGuid,
    IN EFI_SECTION_TYPE             SectionType,
    IN UINTN                        SectionInstance,
    IN OUT VOID                     **Buffer,
    IN OUT UINTN                    *BufferSize,
    OUT UINT32                      *AuthenticationStatus);


//************************************************************
// EFI_FV_WRITE_POLICY
//************************************************************
typedef UINT32 EFI_FV_WRITE_POLICY;
#define EFI_FV_UNRELIABLE_WRITE 0x00000000
#define EFI_FV_RELIABLE_WRITE   0x00000001

//************************************************************
// EFI_FV_WRITE_FILE_DATA
//************************************************************
typedef struct {
    EFI_GUID                *NameGuid;
    EFI_FV_FILETYPE         Type;
    EFI_FV_FILE_ATTRIBUTES  FileAttributes;
    VOID                    *Buffer;
    UINT32                  BufferSize;
} EFI_FV_WRITE_FILE_DATA;

typedef EFI_STATUS (EFIAPI * EFI_FV_WRITE_FILE) (
    IN EFI_FIRMWARE_VOLUME_PROTOCOL *This,
    IN UINT32                       NumberOfFiles,
    IN EFI_FV_WRITE_POLICY          WritePolicy,
    IN EFI_FV_WRITE_FILE_DATA       *FileData);

typedef EFI_STATUS (EFIAPI * EFI_FV_GET_NEXT_FILE) (
    IN EFI_FIRMWARE_VOLUME_PROTOCOL *This,
    IN OUT VOID                     *Key,
    IN OUT EFI_FV_FILETYPE          *FileType,
    OUT EFI_GUID                    *NameGuid,
    OUT EFI_FV_FILE_ATTRIBUTES      *Attributes,
    OUT UINTN                       *Size);

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_FIRMWARE_VOLUME_PROTOCOL
//
// Description: Firmware Volume Protocol for Reading/Seting Volume Attributes
//		Read/Writing Files.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//        GetVolumeAttributes EFI_FV_GET_ATTRIBUTES   
//        SetVolumeAttributes EFI_FV_SET_ATTRIBUTES   
//        ReadFile            EFI_FV_READ_FILE        
//        ReadSection         EFI_FV_READ_SECTION     
//        WriteFile           EFI_FV_WRITE_FILE       
//        GetNextFile         EFI_FV_GET_NEXT_FILE    
//        KeySize             UINT32                  
//        ParentHandle        EFI_HANDLE              
//
//<AMI_SHDR_END>
//**********************************************************************
typedef struct _EFI_FIRMWARE_VOLUME_PROTOCOL {
    EFI_FV_GET_ATTRIBUTES   GetVolumeAttributes;
    EFI_FV_SET_ATTRIBUTES   SetVolumeAttributes;
    EFI_FV_READ_FILE        ReadFile;
    EFI_FV_READ_SECTION     ReadSection;
    EFI_FV_WRITE_FILE       WriteFile;
    EFI_FV_GET_NEXT_FILE    GetNextFile;
    UINT32                  KeySize;
    EFI_HANDLE              ParentHandle;
} EFI_FIRMWARE_VOLUME_PROTOCOL;
#endif // #else PI_SPECIFICATION_VERSION>=0x00010000
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
