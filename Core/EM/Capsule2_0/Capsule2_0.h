//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Core/Modules/Capsule2_0/Capsule2_0.h 1     5/24/12 4:22p Artems $
//
// $Revision: 1 $
//
// $Date: 5/24/12 4:22p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/Capsule2_0/Capsule2_0.h $
// 
// 1     5/24/12 4:22p Artems
// [TAG]  		EIP74625
// [Category]  	New Feature
// [Description]  	New Capsule PPI required by latest Intel's MRC code
// [Files]  		Capsule2_0.cif
// Capsule2_0.sdl
// Capsule2_0.mak
// Capsule2_0.c
// Capsule2_0.h
// Capsule2_0Runtime.c
// Capsule2_0Bds.c
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Capsule2_0.h
//
// Description:	Capsule PPI functions definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_PRIVATE__H__
#define __HII_PRIVATE__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>
#include <Efi.h>

#define MAX_CAPSULE_ADDRESS 0x100000000 //4GB

#define CAPSULE_BLOCK_DONE        0x0001
#define CAPSULE_BLOCK_RELOCATED   0x0002
#define CAPSULE_BLOCK_PROCESSING  0x0004
#define CAPSULE_BLOCK_OVERLAPPING 0x0008

typedef struct {
    UINT32 OriginalAddress;
    UINT32 Size;
    UINT32 RelocatedAddress;
    UINT32 Attributes;
} CAPSULE_BLOCK;

typedef struct {
    UINT32 Address;
    UINT32 Size;
} MEMORY_BLOCK;

EFI_STATUS CoreCapsuleCoalesce(
    IN EFI_PEI_SERVICES  **PeiServices,
    IN OUT VOID          **MemoryBase,
    IN OUT UINTN         *MemSize
);

EFI_STATUS CoreCheckCapsuleUpdate(
    IN EFI_PEI_SERVICES  **PeiServices
);

EFI_STATUS CoreCapsuleCreateState(
    IN EFI_PEI_SERVICES  **PeiServices,
    IN VOID              *CapsuleBase,
    IN UINTN             CapsuleSize  
);

EFI_CAPSULE_BLOCK_DESCRIPTOR * GetCapsuleLocation(
    IN EFI_PEI_SERVICES **PeiServices
);

UINTN GetCapsuleDataSize(
    IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr,
    OUT UINTN *NoOfChunks
);

BOOLEAN BufferOverlap(
    IN MEMORY_BLOCK *Buffer1,
    IN MEMORY_BLOCK *Buffer2
);

EFI_STATUS AdjustBuffer(
    IN MEMORY_BLOCK *Free,
    IN MEMORY_BLOCK *Unmovable,
    IN OUT MEMORY_BLOCK *Movable,
    IN BOOLEAN FromTop
);

EFI_STATUS FindFreeBuffer(
    IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr,
    IN UINTN RequiredSize,
    IN OUT VOID **BaseAddress,
    IN UINTN AvailableSize,
    IN BOOLEAN FromTop
);

VOID CoalesceCapsule(
    IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr,
    IN VOID *Start,
    IN UINTN Size
);

VOID SaveCapsulePointers(
    IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr, 
    IN UINTN ArraySize,
    OUT CAPSULE_BLOCK *Array
);

UINTN FindOverlaps(
    IN CAPSULE_BLOCK *Array,
    IN UINTN ArraySize,
    IN MEMORY_BLOCK *Probe
);

EFI_STATUS FindFreeBufferEx(
    IN CAPSULE_BLOCK *Array,
    IN UINTN ArraySize,
    IN MEMORY_BLOCK *Available,
    IN MEMORY_BLOCK *Reserved,
    OUT MEMORY_BLOCK *Free
);

EFI_STATUS RelocateOverlaps(
    IN CAPSULE_BLOCK *Array,
    IN UINTN ArraySize,
    IN MEMORY_BLOCK *Available,
    IN MEMORY_BLOCK *Reserved
);

EFI_STATUS CoalesceCapsuleByParts(
    IN CAPSULE_BLOCK *Array,
    IN UINTN ArraySize,
    IN VOID *Buffer,
    IN UINTN BufferSize
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************