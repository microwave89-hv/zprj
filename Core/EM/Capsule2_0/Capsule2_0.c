//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Capsule2_0/Capsule2_0.c 3     4/16/14 3:12a Chaseliu $
//
// $Revision: 3 $
//
// $Date: 4/16/14 3:12a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Capsule2_0/Capsule2_0.c $
// 
// 3     4/16/14 3:12a Chaseliu
// [TAG]           EIP163569
// [Category]      Improvement
// [Description]   Update for support 2014 BIOS Security Disclosures.
// [Files]
// Library\PeiLib.c
// Library\EfiLib.c
// Core\EM\NVRAM\NVRAMDXE.c
// Core\EM\Capsule2_0\Capsule2_0.c
// Core\CORE_DXE\FwVolBlock.c
// 
// 2     4/16/13 5:42a Thomaschen
// Fixed for EIP106722.
// 
// 7     3/07/14 5:14p Artems
// EIP 154318
// Added fixes addressed in review comment
// 
// 6     2/28/14 5:54p Artems
// EIP 154318: fixed vulnerability with capsule block descriptors count
// overflow
// 
// 5     2/07/13 5:18p Artems
// [TAG]  		EIP106722
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Win8 firmware update doesn't work
// [RootCause]  	For Win8 update capsule CapsuleRecovery device didn't
// skip capsule header
// [Solution]  	Added unique GUID to distinguish between AFU and Win8
// capsule update
// [Files]  		Capsule2_0.c CapsuleRecovery.c Capsule.h
// 
// 4     11/30/12 6:10p Artems
// [TAG]  		EIP107134
// [Category]  	Improvement
// [Description]  	Potential security holes in Aptio 4 Capsule eModule
// [Files]  		Capsule2_0.c
// 
// 3     7/31/12 6:18p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Added support for APTIO_FW_UPDATE capsule
// [Files]  		Capsule2_0.c
// 
// 2     7/20/12 10:44a Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Support of Microsoft ESRT spec
// [Files]  		Capsule.c
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
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: Capsule2_0.c
//
// Description: Capsule PPI implementation
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiPeiLib.h>
#include <AmiHobs.h>
#include <Capsule.h>
#include <Ppi/Capsule.h>
#include "Capsule2_0.h"

static EFI_GUID CapsuleVariableGuid = EFI_CAPSULE_AMI_GUID;
static EFI_GUID AmiCapsuleHobGuid = AMI_CAPSULE_HOB_GUID;

static PEI_CAPSULE_PPI CapsulePpi = {
    CoreCapsuleCoalesce,
    CoreCheckCapsuleUpdate,
    CoreCapsuleCreateState
};

static EFI_PEI_PPI_DESCRIPTOR PpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gPeiCapsulePpiGuid, 
        &CapsulePpi
    }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   Capsule20PeiInit
//
//  Description:
//  This function installs capsule PPI
//
//  Input:
//  IN EFI_FFS_FILE_HEADER *FfsHeader - pointer to this file header
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PEI_SERVICES
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EFIAPI Capsule20PeiInit (
    IN EFI_FFS_FILE_HEADER       *FfsHeader,
    IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS Status;

    Status = CoreCheckCapsuleUpdate(PeiServices);
    if(!EFI_ERROR(Status))
        Status = (*PeiServices)->InstallPpi(PeiServices, PpiList);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CoreCapsuleCoalesce
//
//  Description:
//  This function coalesces capsule data in continuous block of memory
//
//  Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PEI_SERVICES
//  IN OUT VOID **MemoryBase - pointer to start of available memory
//  IN OUT UINTN *MemSize - pointer to available memory size
//
//  Output:
//  EFI_SUCCESS - capsule coalesced successfully
//  EFI_ERROR - not enough memory to complete operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CoreCapsuleCoalesce (
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT VOID         **MemoryBase,
    IN OUT UINTN        *MemSize
)
{
    EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr;
    UINTN Size;
    EFI_STATUS Status;
    VOID *Start = *MemoryBase;
    UINTN BufferSize = *MemSize;
    UINTN NoOfChunks;

    Ptr = GetCapsuleLocation(PeiServices);
    if(Ptr == NULL)
        return EFI_NOT_FOUND;

    Size = GetCapsuleDataSize(Ptr, &NoOfChunks);
    if(Size == 0 || Size > MAX_CAPSULE_SIZE)
        return EFI_NOT_FOUND;

    if(Size > BufferSize)
        return EFI_BUFFER_TOO_SMALL;

/* First try to find continuous block, not overlapped with capsule data */
    Status = FindFreeBuffer(Ptr, Size, &Start, BufferSize, TRUE);
    if(!EFI_ERROR(Status)) {
        CoalesceCapsule(Ptr, Start, Size);
        *MemoryBase = Start;
        *MemSize = Size;
        return EFI_SUCCESS;
    }

/* Large enough buffer not found try to coalesce capsule piece by piece */
/* Get buffer to store mailbox information */
/* we will allocate buffer from the bottom of available memory */
    Status = FindFreeBuffer(Ptr, sizeof(CAPSULE_BLOCK) * NoOfChunks, &Start, BufferSize, FALSE);
    if(EFI_ERROR(Status))
        return Status;
/* recalculate available buffer size */
    BufferSize = (UINTN)Start - (UINTN)(*MemoryBase);
    if(Size > BufferSize)
        return EFI_BUFFER_TOO_SMALL;

/* store mailbox info for future use */
    SaveCapsulePointers(Ptr, NoOfChunks, (CAPSULE_BLOCK *)Start);

    Status = CoalesceCapsuleByParts((CAPSULE_BLOCK *)Start, NoOfChunks, *MemoryBase, BufferSize);
    if(!EFI_ERROR(Status)) {
        *MemSize = Size;    //since we will coalesce from start of available memory *MemoryBase value will be valid
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CoreCheckCapsuleUpdate
//
//  Description:
//  This function checks if capsule is present
//
//  Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PEI_SERVICES
//
//  Output:
//  EFI_SUCCESS - capsule present
//  EFI_NOT_FOUND - capsule not present or is beyond the 4GB boundaries
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CoreCheckCapsuleUpdate (
    IN EFI_PEI_SERVICES   **PeiServices
)
{
    EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr;

    Ptr = GetCapsuleLocation(PeiServices);
    return (Ptr == NULL) ? EFI_NOT_FOUND : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CoreCapsuleCreateState
//
//  Description:
//  This function copies coalesced capsule into reserved block of memory and creates HOB
//  with capsule parameters
//
//  Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PEI_SERVICES
//  IN VOID *CapsuleBase - coalesced capsule start address
//  IN UINTN CapsuleSize - capsule size
//
//  Output:
//  EFI_SUCCESS - capsule present
//  EFI_ERROR - not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CoreCapsuleCreateState(
    IN EFI_PEI_SERVICES  **PeiServices,
    IN VOID              *CapsuleBase,
    IN UINTN             CapsuleSize  
)
{
    EFI_STATUS Status;
    UINTN TotalSize = 0;
    EFI_CAPSULE_HEADER *Cap;
    VOID *SaveCap;
    AMI_CAPSULE_HOB *Hob;
    UINTN Pages;
    EFI_PHYSICAL_ADDRESS Save;
    static EFI_GUID AmiFwCapsuleGuid = APTIO_FW_CAPSULE_GUID;
    static EFI_GUID W8FwUpdateImageCapsuleGuid = W8_FW_UPDATE_IMAGE_CAPSULE_GUID;

    static EFI_GUID RecoveryBootModeGuid = EFI_PEI_BOOT_IN_RECOVERY_MODE_PEIM_PPI;
    static EFI_PEI_PPI_DESCRIPTOR RecoveryModePpi = {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &RecoveryBootModeGuid, NULL
    };

    Cap = (EFI_CAPSULE_HEADER *)CapsuleBase;

    while(TotalSize < CapsuleSize) {
        Pages = EFI_SIZE_TO_PAGES(Cap->CapsuleImageSize);
        Status = (*PeiServices)->AllocatePages(PeiServices, EfiBootServicesData, Pages, &Save);
        if(EFI_ERROR(Status))
            return Status;

        SaveCap = (VOID *)(UINTN)Save;
        MemCpy(SaveCap, Cap, Cap->CapsuleImageSize);

        Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof(AMI_CAPSULE_HOB), &Hob);
        if(EFI_ERROR(Status))
            return Status;

        Hob->Header.Name = AmiCapsuleHobGuid;
        Hob->CapsuleData = (EFI_PHYSICAL_ADDRESS)(UINTN)SaveCap;
        Hob->CapsuleGuid = Cap->CapsuleGuid;
        Hob->CapsuleLength = Cap->CapsuleImageSize;

        if(!guidcmp(&(Cap->CapsuleGuid), &AmiFwCapsuleGuid) ||
           !guidcmp(&(Cap->CapsuleGuid), &W8FwUpdateImageCapsuleGuid)) {
            (*PeiServices)->SetBootMode(PeiServices, BOOT_ON_FLASH_UPDATE);
            (*PeiServices)->InstallPpi(PeiServices, &RecoveryModePpi);
        }

        TotalSize += Cap->CapsuleImageSize;
        (UINT8 *)Cap += Cap->CapsuleImageSize;
    }
    return EFI_SUCCESS;
}


/* ----------- Capsule service functions ------------ */

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetCapsuleLocation
//
//  Description:
//  This function returns pointer to capsule mailbox
//
//  Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PEI_SERVICES
//
//  Output:
//  EFI_CAPSULE_BLOCK_DESCRIPTOR * - pointer to mailbox, or NULL
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_CAPSULE_BLOCK_DESCRIPTOR * GetCapsuleLocation(
    IN EFI_PEI_SERVICES **PeiServices
)
{
    EFI_STATUS Status;
    UINTN VarSize = sizeof (EFI_PHYSICAL_ADDRESS);
    EFI_PHYSICAL_ADDRESS MailBox = 0;

    Status = PeiGetVariable(PeiServices, CAPSULE_UPDATE_VAR, &CapsuleVariableGuid, NULL, &VarSize, &MailBox);
    PEI_TRACE((-1, PeiServices, "Get capsule variable %r, addr %lx\n", Status, MailBox));
    if(EFI_ERROR(Status)) 
        return NULL;

    if(MailBox >= MAX_CAPSULE_ADDRESS)
        return NULL;            //no support for Capsule above 4GB

    return (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)MailBox;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetCapsuleDataSize
//
//  Description:
//  This function returns capsule size calculated from mailbox data
//
//  Input:
//  IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr - pointer to capsule mailbox
//  OUT UINTN *NoOfChunks - pointer where to store quantity of capsule pieces
//
//  Output:
//  UINTN - capsule size in bytes or 0
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN GetCapsuleDataSize(
    IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr,
    OUT UINTN *NoOfChunks
)
{
    UINT64 Result = 0;
    UINTN Chunks = 0;

    do {
        if(Ptr->DataBlock >= MAX_CAPSULE_ADDRESS)   //pointer above 4GB
            return 0;

        if(Ptr->Length != 0) {
            if(Ptr->Length > MAX_CAPSULE_SIZE - Result)
                return 0;
            Result += Ptr->Length;
            Chunks++;
            Ptr++;
        } else if (Ptr->DataBlock != NULL) {
            if(Ptr == (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)(Ptr->ContinuationPointer))
            //when continuation pointer points to itself it's either error or malicious capsule, we won't process it
                return 0;
            Ptr = (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)(Ptr->ContinuationPointer);
        } else {
            break;
        }
    } while(Chunks <= MAX_CAPSULE_BLOCK_DESCRIPTOR_COUNT);

    if(Chunks <= MAX_CAPSULE_BLOCK_DESCRIPTOR_COUNT) {
        *NoOfChunks = Chunks;
        return (UINTN)Result;
    } else 
        return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   BufferOverlap
//
//  Description:
//  This function checks if two buffers overlap each other
//
//  Input:
//  IN MEMORY_BLOCK *Buffer1 - buffer1 parameters
//  IN MEMORY_BLOCK *Buffer2 - buffer2 parameters
//
//  Output:
//  TRUE - buffers overlap, FALSE otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BufferOverlap(
    IN MEMORY_BLOCK *Buffer1,
    IN MEMORY_BLOCK *Buffer2
)
{
    return ((Buffer2->Address > (Buffer1->Address + Buffer1->Size)) || 
            (Buffer1->Address > (Buffer2->Address + Buffer2->Size))) ? FALSE : TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   AdjustBuffer
//
//  Description:
//  This function moves one block of memory within free range to avoid overlap
//  with another buffer
//
//  Input:
//  IN MEMORY_BLOCK *Free - free memory range parameters
//  IN MEMORY_BLOCK *Unmovable - parameters of overlapping buffer that can't be moved
//  IN OUT MEMORY_BLOCK *Movable - parameters of overlapping buffer that can be moved
//  IN BOOLEAN FromTop - flag of moving direction in free range(TRUE - move from top, FALSE - 
//                       move from bottom
//
//  Output:
//  EFI_SUCCESS - buffer moved successfully
//  EFI_BUFFER_TOO_SMALL - not enough memory to move buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AdjustBuffer(
    IN MEMORY_BLOCK *Free,
    IN MEMORY_BLOCK *Unmovable,
    IN OUT MEMORY_BLOCK *Movable,
    IN BOOLEAN FromTop
)
{
    if(!BufferOverlap(Unmovable, Movable))
        return EFI_SUCCESS;

    if(FromTop) {
/* Move movable block to the end of unmovalbe */
        Movable->Address = Unmovable->Address + Unmovable->Size;
    } else {
/* Move movable block before unmovable */
        Movable->Address = Unmovable->Address - Movable->Size;
    }

    return (BufferOverlap(Unmovable, Free)) ? EFI_BUFFER_TOO_SMALL : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindFreeBuffer
//
//  Description:
//  This function searches for free continuous block of memory of required size
//
//  Input:
//  IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr - pointer to capsule mailbox
//  IN UINTN RequiredSize - size of buffer required
//  IN OUT VOID **BaseAddress - on input pointer to start of free memory, on output
//                              start of requested buffer
//  IN UINTN AvailableSize - size of free memory
//  IN BOOLEAN FromTop - flag of moving direction in free range(TRUE - move from top, FALSE - 
//                       move from bottom
//
//  Output:
//  EFI_SUCCESS - buffer moved successfully
//  EFI_BUFFER_TOO_SMALL - not enough memory to move buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindFreeBuffer(
    IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr,
    IN UINTN RequiredSize,
    IN OUT VOID **BaseAddress,
    IN UINTN AvailableSize,
    IN BOOLEAN FromTop
)
{
    EFI_STATUS Status;
    MEMORY_BLOCK FreeMemory;
    MEMORY_BLOCK RequiredMemory;
    MEMORY_BLOCK Unmovable;

    FreeMemory.Address = (UINT32)(UINTN)(*BaseAddress);
    FreeMemory.Size = AvailableSize;

    RequiredMemory.Size = RequiredSize;

    if(FromTop) { 
/* start looking for available space from the top of available buffer */
        RequiredMemory.Address = FreeMemory.Address;
    } else {
/* start looking for available space from the bottom of available buffer */
        RequiredMemory.Address = AvailableSize - RequiredSize;
    }

    do {
        /* First check if we overlapped with mailbox itself */
        Unmovable.Address = (UINT32)Ptr;
        Unmovable.Size = sizeof(EFI_CAPSULE_BLOCK_DESCRIPTOR);
        Status = AdjustBuffer(&FreeMemory, &Unmovable, &RequiredMemory, FromTop);
        if(EFI_ERROR(Status))
            return Status;

        if(Ptr->Length != 0) {
            /* Now check if we overlapped with DataBlock */
            Unmovable.Address = (UINT32)(Ptr->DataBlock);
            Unmovable.Size = (UINT32)(Ptr->Length);
            Status = AdjustBuffer(&FreeMemory, &Unmovable, &RequiredMemory, FromTop);
            Ptr++;
        } else if (Ptr->DataBlock != NULL) {
            Ptr = (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)(Ptr->ContinuationPointer);
        } else {
            break;  //we've reached end of mailbox
        }
    } while (!EFI_ERROR(Status));

    if(!EFI_ERROR(Status)) {
        *BaseAddress = (VOID *)(UINTN)RequiredMemory.Address;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CoalesceCapsule
//
//  Description:
//  This function coalesces capsule from mailbox to continuous block of memory
//
//  Input:
//  IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr - pointer to capsule mailbox
//  IN VOID *Start - pointer to start of continuous block of memory
//  IN UINTN Size - size of continuous block of memory
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CoalesceCapsule(
    IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr,
    IN VOID *Start,
    IN UINTN Size
)
{
    UINT8 *Walker = (UINT8 *)Start;
    UINT64 Stop = 0;

    do {
        if(Ptr->Length != 0) {
            MemCpy(Walker, (VOID *)(UINTN)(Ptr->DataBlock), (UINTN)Ptr->Length);
            Walker += Ptr->Length;
            Stop += Ptr->Length;
            Ptr++;
        } else if(Ptr->DataBlock != NULL) {
            Ptr = (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)(Ptr->ContinuationPointer);
        } else {
            break;  //we've reached end of mailbox
        }
    } while (Stop <= Size);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   SaveCapsulePointers
//
//  Description:
//  This function relocates and reformats capsule mailbox for further processing
//
//  Input:
//  IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr - pointer to capsule mailbox
//  IN UINTN ArraySize - size of array to store capsule mailbox pointers
//  OUT CAPSULE_BLOCK *Array - pointer where to store capsule mailbox pointers
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveCapsulePointers(
    IN EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr, 
    IN UINTN ArraySize,
    OUT CAPSULE_BLOCK *Array
)
{
    UINTN i = 0;
    do {
        if(Ptr->Length != 0) {
            Array[i].OriginalAddress = (UINT32)Ptr->DataBlock;
            Array[i].Size = (UINT32)Ptr->Length;
            Array[i].RelocatedAddress = 0;
            Array[i].Attributes = 0;
            i++;
            Ptr++;
        } else if(Ptr->DataBlock != NULL) {
            Ptr = (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)(Ptr->ContinuationPointer);
        } else {
            break;
        }
    } while(i <= ArraySize);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindOverlaps
//
//  Description:
//  This function checks if given memory block overlaps with other blocks of capsule
//
//  Input:
//  IN CAPSULE_BLOCK *Array - pointer to capsule blocks array
//  IN UINTN ArraySize - size of array of capsule blocks
//  IN MEMORY_BLOCK *Probe - pointer to memory block to check against
//
//  Output:
//  UINTN - number of overlaps found or 0 if there are no overlaps
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN FindOverlaps(
    IN CAPSULE_BLOCK *Array,
    IN UINTN ArraySize,
    IN MEMORY_BLOCK *Probe
)
{
    UINTN i;
    MEMORY_BLOCK Unmovable;
    UINTN Overlap = 0;

    for(i = 0; i < ArraySize; i++) {
        if(Array[i].Attributes & CAPSULE_BLOCK_PROCESSING ||
           Array[i].Attributes & CAPSULE_BLOCK_DONE)
            continue;

        Unmovable.Address = (Array[i].Attributes & CAPSULE_BLOCK_RELOCATED) ? 
                                Array[i].RelocatedAddress : Array[i].OriginalAddress;
        Unmovable.Size = Array[i].Size;
        if(BufferOverlap(&Unmovable, Probe)) {
            Overlap++;
            Array[i].Attributes |= CAPSULE_BLOCK_OVERLAPPING;
        }
    }
    return Overlap;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   FindFreeBufferEx
//
//  Description:
//  This function searches for continuous memory block in free range, and if not found
//  in already processed capsule blocks
//
//  Input:
//  IN CAPSULE_BLOCK *Array - pointer to capsule blocks array
//  IN UINTN ArraySize - size of array of capsule blocks
//  IN MEMORY_BLOCK *Available - available memory block parameters
//  IN MEMORY_BLOCK *Reserved - occupied memory block parameters
//  IN OUT MEMORY_BLOCK *Free - parameters for block that requires allocation
//
//  Output:
//  EFI_SUCCESS - block relocated successfully
//  EFI_BUFFER_TOO_SMALL - not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindFreeBufferEx(
    IN CAPSULE_BLOCK *Array,
    IN UINTN ArraySize,
    IN MEMORY_BLOCK *Available,
    IN MEMORY_BLOCK *Reserved,
    IN OUT MEMORY_BLOCK *Free
)
{
    UINTN i;
    MEMORY_BLOCK Unmovable;
    EFI_STATUS Status;

    Free->Address = Available->Address;

    for(i = 0; i < ArraySize; i++) {
        if(Array[i].Attributes & CAPSULE_BLOCK_PROCESSING ||
           Array[i].Attributes & CAPSULE_BLOCK_DONE)
            continue;

        Unmovable.Address = (Array[i].Attributes & CAPSULE_BLOCK_RELOCATED) ? 
                                Array[i].RelocatedAddress : Array[i].OriginalAddress;
        Unmovable.Size = Array[i].Size;
        Status = AdjustBuffer(Available, &Unmovable, Free, TRUE);
        if(EFI_ERROR(Status))
            break;
    }

    if(!EFI_ERROR(Status)) {
        return Status;      //buffer found
    }
/* try to find free space in previously processed chunks */
    for(i = 0; i < ArraySize; i++) {
        if(Array[i].Attributes & CAPSULE_BLOCK_PROCESSING || Free->Size > Array[i].Size)
            continue;

        if(Array[i].Attributes & CAPSULE_BLOCK_DONE &&
           !(Array[i].Attributes & CAPSULE_BLOCK_RELOCATED) ) { 
        /* if chunk was processed but not relocated, original address may be free */
            Free->Address = Array[i].OriginalAddress;
            if(!BufferOverlap(Free, Reserved)) {
                return EFI_SUCCESS;
            }
        }
    }
    return EFI_BUFFER_TOO_SMALL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   RelocateOverlaps
//
//  Description:
//  This function moves capsule blocks that overlap with reserved block
//
//  Input:
//  IN CAPSULE_BLOCK *Array - pointer to capsule blocks array
//  IN UINTN ArraySize - size of array of capsule blocks
//  IN MEMORY_BLOCK *Available - available memory block parameters
//  IN MEMORY_BLOCK *Reserved - occupied memory block parameters
//
//  Output:
//  EFI_SUCCESS - block relocated successfully
//  EFI_BUFFER_TOO_SMALL - not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RelocateOverlaps(
    IN CAPSULE_BLOCK *Array,
    IN UINTN ArraySize,
    IN MEMORY_BLOCK *Available,
    IN MEMORY_BLOCK *Reserved
)
{
    UINTN i;
    MEMORY_BLOCK Free;
    VOID *Source;
    EFI_STATUS Status;

    for(i = 0; i < ArraySize; i++) {
        if(!(Array[i].Attributes & CAPSULE_BLOCK_OVERLAPPING))
            continue;

        Free.Size = Array[i].Size;
        Status = FindFreeBufferEx(Array, ArraySize, Available, Reserved, &Free);
        if(EFI_ERROR(Status))
            return Status;

        Source = (Array[i].Attributes & CAPSULE_BLOCK_RELOCATED) ? 
                    (VOID *)Array[i].RelocatedAddress : (VOID *)Array[i].OriginalAddress;
        MemCpy((VOID *)(Free.Address), Source, Array[i].Size);
        Array[i].Attributes |= CAPSULE_BLOCK_RELOCATED;
        Array[i].Attributes &= ~CAPSULE_BLOCK_OVERLAPPING;
        Array[i].RelocatedAddress = Free.Address;
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   CoalesceCapsuleByParts
//
//  Description:
//  This function coalesces capsule from capsule blocks
//
//  Input:
//  IN CAPSULE_BLOCK *Array - pointer to capsule blocks array
//  IN UINTN ArraySize - size of array of capsule blocks
//  IN VOID *Buffer - pointer to start of continuous block of memory
//  IN UINTN BufferSize - size of continuous block of memory
//
//  Output:
//  EFI_SUCCESS - block relocated successfully
//  EFI_BUFFER_TOO_SMALL - not enough memory to perform operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CoalesceCapsuleByParts(
    IN CAPSULE_BLOCK *Array,
    IN UINTN ArraySize,
    IN VOID *Buffer,
    IN UINTN BufferSize
)
{
    UINTN i;
    UINTN Overlap;
    VOID *Source;
    EFI_STATUS Status;
    MEMORY_BLOCK Available;
    MEMORY_BLOCK Reserved;
    MEMORY_BLOCK Current;

    Current.Address = (UINT32)Buffer;
    Reserved.Address = Current.Address;
    Reserved.Size = 0;
    Available.Size = BufferSize;

    for(i = 0; i < ArraySize; i++) {
        Array[i].Attributes |= CAPSULE_BLOCK_PROCESSING;
        Current.Size = Array[i].Size;
        Available.Address = Current.Address + Current.Size;
        Available.Size -= Array[i].Size; //reserve space
        Reserved.Size += Array[i].Size;
        Overlap = FindOverlaps(Array, ArraySize, &Current);
        if(Overlap > 0) {
            Status = RelocateOverlaps(Array, ArraySize, &Available, &Reserved);
            if(EFI_ERROR(Status))
                return Status;
        }

        Source = (Array[i].Attributes & CAPSULE_BLOCK_RELOCATED) ? 
            (VOID *)(Array[i].RelocatedAddress) : (VOID *)(Array[i].OriginalAddress);
        MemCpy((VOID *)(Current.Address), Source, Array[i].Size);
        Current.Address += Array[i].Size;
        Array[i].Attributes &= ~CAPSULE_BLOCK_PROCESSING;
        Array[i].Attributes |= CAPSULE_BLOCK_DONE;
    }

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************