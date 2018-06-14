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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/FirmwareVolumeBlock.h 1     11/18/14 5:13a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 11/18/14 5:13a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/FirmwareVolumeBlock.h $
// 
// 1     11/18/14 5:13a Chienhsieh
// Update rev6.
// 
// 6     2/25/13 5:35p Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Added definition of LBA_TERMINATOR
// [Files]  		FirmwareVolumeBlock.h
// 
// 5     6/16/11 5:33p Felixp
// FORWARD_COMPATIBLE_MODE definitions removed (they are not needed in the
// Core version of the header).
// 
// 1     6/16/11 4:57p Felixp
// 
// 4     6/16/11 3:33p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 3     6/10/11 12:58p Artems
// Added backward compatibility macro definition for PI mode
// 
// 2     5/27/11 5:53p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
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
// 2     12/31/03 2:50p Markw
// Added S Header.
// 
// 1     12/18/03 4:14p Markw
// 
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	FirmwareVolumeBlock.h
//
// Description:	This file is an include file used to define the Protocol for the
//		        Firmware Volume Block Protocol.
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef __FIRMWARE_VOLUME_BLOCK_PROTOCOL_H__
#define __FIRMWARE_VOLUME_BLOCK_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <FFS.h>

#if PI_SPECIFICATION_VERSION<0x00010000
// 0xDE28BC59-6228-41BD-BDF6-A3B9ADB58DA1
#define FW_VOLUME_BLOCK_PROTOCOL_GUID \
    {0xDE28BC59, 0x6228, 0x41BD, 0xBD, 0xF6, 0xA3, 0xB9,0xAD,0xB5, 0x8D, 0xA1}
#define EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID FW_VOLUME_BLOCK_PROTOCOL_GUID
#else
#define EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID \
  { 0x8f644fa9, 0xe850, 0x4db1, 0x9c, 0xe2, 0xb, 0x44, 0x69, 0x8e, 0x8d, 0xa4 }
#if BACKWARD_COMPATIBLE_MODE
#define FW_VOLUME_BLOCK_PROTOCOL_GUID EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID
#endif // BACKWARD_COMPATIBLE_MODE
#endif

#define EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL_GUID EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID
#define EFI_LBA_LIST_TERMINATOR 0xFFFFFFFFFFFFFFFF

GUID_VARIABLE_DECLARATION(gEfiFirmwareVolumeBlockProtocolGuid, EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL_GUID);
GUID_VARIABLE_DECLARATION(gEfiFirmwareVolumeBlock2ProtocolGuid, EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL_GUID);

typedef struct _EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL;
typedef EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL;    

typedef EFI_STATUS (EFIAPI * EFI_FVB_GET_ATTRIBUTES) (
    IN EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL   *This,
    OUT EFI_FVB_ATTRIBUTES                  *Attributes);

typedef EFI_STATUS (EFIAPI * EFI_FVB_SET_ATTRIBUTES) (
    IN EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL   *This,
    IN OUT EFI_FVB_ATTRIBUTES               *Attributes);

typedef EFI_STATUS (EFIAPI * EFI_FVB_GET_PHYSICAL_ADDRESS) (
    IN EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL   *This,
    OUT EFI_PHYSICAL_ADDRESS                *Address);

typedef EFI_STATUS (EFIAPI * EFI_FVB_GET_BLOCK_SIZE) (
    IN EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL   *This,
    IN EFI_LBA                              Lba,
    OUT UINTN                               *BlockSize,
    OUT UINTN                               *NumberOfBlocks);

typedef EFI_STATUS (EFIAPI *EFI_FVB_READ)(
    IN EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL   *This,
    IN EFI_LBA                              Lba,
    IN UINTN                                Offset,
    IN OUT UINTN                            *NumBytes,
    OUT UINT8                               *Buffer);

typedef EFI_STATUS (EFIAPI * EFI_FVB_WRITE) (
    IN EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL   *This,
    IN EFI_LBA                              Lba,
    IN UINTN                                Offset,
    IN OUT UINTN                            *NumBytes,
    IN UINT8                                *Buffer);

typedef EFI_STATUS (EFIAPI * EFI_FVB_ERASE_BLOCKS) (
    IN EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL *This,...);

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL
//
// Description: Firmware Volume Protocol Block Gets/Sets attributes,
//              reads/writes/erases blocks in the firmware volume.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//        GetAttributes      EFI_FVB_GET_ATTRIBUTES
//        SetAttributes      EFI_FVB_SET_ATTRIBUTES
//        GetPhysicalAddress EFI_FVB_GET_PHYSICAL_ADDRESS
//        GetBlockSize       EFI_FVB_GET_BLOCK_SIZE
//        Read               EFI_FVB_READ
//        Write              EFI_FVB_WRITE
//        EraseBlocks        EFI_FVB_ERASE_BLOCKS
//        ParentHandle       EFI_HANDLE
//
//<AMI_SHDR_END>
//**********************************************************************
typedef struct _EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL {
    EFI_FVB_GET_ATTRIBUTES          GetAttributes;
    EFI_FVB_SET_ATTRIBUTES          SetAttributes;
    EFI_FVB_GET_PHYSICAL_ADDRESS    GetPhysicalAddress;
    EFI_FVB_GET_BLOCK_SIZE          GetBlockSize;
    EFI_FVB_READ                    Read;
    EFI_FVB_WRITE                   Write;
    EFI_FVB_ERASE_BLOCKS            EraseBlocks;
    EFI_HANDLE                      ParentHandle;
} EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL;

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
