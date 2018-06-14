//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/BlockIo.h 5     4/21/11 12:50p Artems $
//
// $Revision: 5 $
//
// $Date: 4/21/11 12:50p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/BlockIo.h $
// 
// 5     4/21/11 12:50p Artems
// EIP 58686: add new structure fields for UEFI 2.3.1 specification
// compliance
// 
// 4     3/13/06 1:40a Felixp
// 
// 3     3/04/05 10:31a Mandal
// 
// 2     2/08/05 11:49a Felixp
// EFI_LBA definition removed since it's already defined in EFI.h
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     8/19/04 6:26p Robert
//
// 1     1/26/04 3:25p Markw
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: BlockIo.h
//
// Description: EFI_BLOCK_IO_PROTOCOL definition file
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __BLOCK_IO_PROTOCOL_H__
#define __BLOCK_IO_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_BLOCK_IO_PROTOCOL_GUID \
    { 0x964e5b21, 0x6459, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 ((2<<16) | (31))

GUID_VARIABLE_DECLARATION(gEfiBlockIoProtocolGuid,EFI_BLOCK_IO_PROTOCOL_GUID);

// Forward reference for pure ANSI compatability
typedef struct _EFI_BLOCK_IO_PROTOCOL EFI_BLOCK_IO_PROTOCOL;

//=============================================================================
typedef struct {
    UINT32      MediaId;
    BOOLEAN     RemovableMedia;
    BOOLEAN     MediaPresent;
    BOOLEAN     LogicalPartition;
    BOOLEAN     ReadOnly;
    BOOLEAN     WriteCaching;
    UINT32      BlockSize;
    UINT32      IoAlign;
    EFI_LBA     LastBlock;
    EFI_LBA     LowestAlignedLba;                   //added in Revision 2
    UINT32      LogicalBlocksPerPhysicalBlock;      //added in Revision 2
    UINT32      OptimalTransferLengthGranularity;   //added in Revision 3
} EFI_BLOCK_IO_MEDIA;

//=============================================================================
// Function: Reset
//
// Description: resets the block device hardware.
//
// Inputs:
//      This - Indicates a pointer to the calling context.
//      ExtendedVerification - Indicates that the driver may perform a more exhaustive
//          verification operation of the device during reset.
//
// Outputs: Returns EFI_STATUS
//
// Notes:
//
//=============================================================================
typedef EFI_STATUS (EFIAPI *EFI_BLOCK_RESET) (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN BOOLEAN               ExtendedVerification
);

//=============================================================================
// Function: ReadBlocks
//
// Description: function reads the requested number of blocks from the device. All the
//      blocks are read, or an error is returned.
//
// Inputs:
//      This Indicates a pointer to the calling context.
//      MediaId - The media ID that the read request is for.
//      LBA - The starting logical block address to read from on the device.
//      BufferSize - The size of the Buffer in bytes. This must be a multiple of the intrinsic
//          block size of the device.
//
// Outputs:
//      Buffer - A pointer to the destination buffer for the data. The caller is responsible
//          for either having implicit or explicit ownership of the buffer.
//
// Notes:
//
//=============================================================================
typedef EFI_STATUS (EFIAPI *EFI_BLOCK_READ) (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    OUT VOID                 *Buffer
);

//=============================================================================
// Function: WriteBlocks
//
// Description: writes the requested number of blocks to the device. All blocks
//      are written, or an error is returned.
//
// Inputs:
//      This - Indicates a pointer to the calling context.
//      MediaId - The media ID that the write request is for.
//      LBA - The starting logical block address to be written.
//      BufferSize - The size in bytes of Buffer. This must be a multiple of the intrinsic
//          block size of the device.
//      Buffer - A pointer to the source buffer for the data.
//
// Outputs: returns EFI_STATUS
//
// Notes:
//
//=============================================================================
typedef EFI_STATUS (EFIAPI *EFI_BLOCK_WRITE) (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    IN VOID                  *Buffer
);

//=============================================================================
// Function: FlushBlocks
//
// Description: flushes all modified data to the physical block device.
//
// Inputs:
//      This - Indicates a pointer to the calling context.
//
// Outputs: returns EFI_STATUS
//
// Notes:
//
//=============================================================================
typedef EFI_STATUS (EFIAPI *EFI_BLOCK_FLUSH) ( 
    IN EFI_BLOCK_IO_PROTOCOL *This 
);

//=============================================================================
// Protocol Definition
struct _EFI_BLOCK_IO_PROTOCOL {
    UINT64              Revision;
    EFI_BLOCK_IO_MEDIA  *Media;
    EFI_BLOCK_RESET     Reset;
    EFI_BLOCK_READ      ReadBlocks;
    EFI_BLOCK_WRITE     WriteBlocks;
    EFI_BLOCK_FLUSH     FlushBlocks;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
