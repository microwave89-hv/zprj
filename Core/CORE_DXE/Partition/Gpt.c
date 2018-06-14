//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/Partition/Gpt.c 16    7/19/12 10:26a Artems $
//
// $Revision: 16 $
//
// $Date: 7/19/12 10:26a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/Partition/Gpt.c $
// 
// 16    7/19/12 10:26a Artems
// [TAG]  		EIP94126
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	GPT system recovery can't work and backup GPT partition
// will also be destroyed after GPT recovery.
// [RootCause]  	Incorrect LBA used to restore GPT partition
// [Solution]  	Use correct LBA
// [Files]  		Gpt.c
// 
// 15    5/02/11 5:57p Artems
// EIP 59571: New partition driver functionality as per UEFI spec v.2.3.1
// 
// 14    11/23/10 4:43p Vyacheslava
// [TAG]        EIP45145 
// [Category]   New Feature
// [Description]    A new feature has done by Cire Lin: We're did the code
// for repairing GPT table. If CRC checking fails then it will run
// CopyGpt() to repair GPT table. 
// 
// 13    4/16/10 4:24p Pats
// EIP 30719: Support for the HDD with sector size more than 512bytes.
// 
// 12    2/04/10 2:07p Oleksiyy
// Minor fixes
// 
// 11    7/09/09 5:01p Oleksiyy
// Files clean-up
//
// 10    4/03/09 5:24p Oleksiyy
// EIP 20879: Linux GPT discovering logic improvement.
//
// 9     1/07/08 4:21p Robert
// Updated for coding standard
//
// 8     4/24/07 6:07p Robert
// Update for CHM compliance
//
// 7     4/12/07 7:04p Robert
// Coding Standard Updates
//
// 6     3/22/07 5:39p Robert
// Updated Files for coding standard
//
// 5     10/10/06 3:22p Yakovlevs
// Bug fixes. The GPT Partition Driver working now.
//
// 4     5/19/06 10:47p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
//
// 3     2/11/05 6:14p Felixp
// - Code optimized by using DPAddNode instead of DPAdd
// - bug fixes
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    Gpt.c
//
// Description: EFI GPT Partition Generic Driver.
//      This file detects whether or not the system has a GPT format
//      for the drive and sets up all partitions on the drive
//
//<AMI_FHDR_END>
//**********************************************************************

//-----------------------------------------------------------------------------
// Includes
#include "Partition.h"
#include "Gpt.h"
#include "Mbr.h"

//-----------------------------------------------------------------------------
// global variables


//-----------------------------------------------------------------------------
// Function Definitions


//-----------------------------------------------------------------------------
//<AMI_PHDR_START>
// Procedure: AdjustBufferSize
//
// Description: Calculates correct Buffer size for BlockIO trasfer
//
// Input:       EFI_BLOCK_IO_PROTOCOL *BlockIo  BlockIo Protocol Interface
//              UINTN               *BufferSize Pointer To the Size Needed
//
// Output:      Modifies Buffer Size to reflect correct number of bytes
//
// Returns:     Nothing
//
// Referrals:
//
//<AMI_PHDR_END>
//-----------------------------------------------------------------------------

VOID AdjustBufferSize(IN EFI_BLOCK_IO_PROTOCOL *BlockIo, IN OUT UINTN *BufferSize)
{
    UINTN   sz;
    
    // Calculate the size of trazaction
    sz=BlockIo->Media->BlockSize * (*BufferSize/BlockIo->Media->BlockSize);
    
    if (*BufferSize % BlockIo->Media->BlockSize) sz+=BlockIo->Media->BlockSize;
    
    *BufferSize=sz;
}


//-----------------------------------------------------------------------------
//<AMI_PHDR_START>
//
// Procedure: CopyGpt
//
// Description: Copies a valid GPT to the location of an invalid one
//
// Input:
//      BlockIo - pointer to the BlockIo partition so we can read and write
//          to the Block Device
//      DiskIo - Unused at this time
//      Destination - Pointer to where the valid GPT will be copied
//      Source - Pointer to a valid GPT
//
// Output: None - A valid GPT will be written to the Destination address
//
// Returns: None
//
// Referrals: CopyMem ReadBlocks CalculateCrc32 AllocatePool AdjustBufferSize
//      WriteBlocks FreePool
//
//<AMI_PHDR_END>
//-----------------------------------------------------------------------------

VOID CopyGpt(
    EFI_BLOCK_IO_PROTOCOL   *BlockIo,
    EFI_DISK_IO_PROTOCOL    *DiskIo,
    GPT_HEADER              *Destination,
    GPT_HEADER              *Source
)
{
    EFI_STATUS          Status;
    UINT8               *EntryArray;
    EFI_LBA             EntryLba;
    UINTN               Size;
    UINT32              Crc32;
    
    // Calculate Buffer Size for Enrty array
    Size = Source->NumberOfPartitionEntries * Source->SizeOfPartitionEntry;
    AdjustBufferSize(BlockIo, &Size);
    
    if (Source->MyLba == 1) 
        EntryLba = Source->LastUsableLba + 1;
    else 
        EntryLba = Source->AlternateLba + 1;
    
    // Copy the GPT Header
    gBS->CopyMem( Destination, Source, sizeof(GPT_HEADER) );
    
    Destination->MyLba = Source->AlternateLba;
    Destination->AlternateLba = Source->MyLba;
    Destination->PartitionEntryLba = EntryLba;
    Destination->Crc32 = 0;
    Destination->Header.CRC32 = 0;
    
    // Allocate Memory for Source Patrition Table Array
    Status = gBS->AllocatePool( EfiBootServicesData, Size, &EntryArray );
    
    // Zero it out
    gBS->SetMem( EntryArray, Size, 0 );
    
    // Read Source's Partition Table Entry Array to the buffer
    Status = BlockIo->ReadBlocks(
        BlockIo, 
        BlockIo->Media->MediaId,
        Source->PartitionEntryLba, 
        Size, 
        EntryArray
    );
                               
    // Calculate CRC32 of GIUID Partition Table Entry Array
    gBS->CalculateCrc32(
        (UINT8*)EntryArray,
        Source->NumberOfPartitionEntries * Source->SizeOfPartitionEntry,
        &Crc32
    );
    Destination->Crc32 = Crc32;

    gBS->CalculateCrc32(
        (UINT8*)Destination,
        sizeof(GPT_HEADER),
        &Crc32
    );
    Destination->Header.CRC32 = Crc32;
    
    
    // Write to Destination Partition Header Block
    Status = BlockIo->WriteBlocks(
        BlockIo,
        BlockIo->Media->MediaId,
        Destination->MyLba, 
        BlockIo->Media->BlockSize,
        Destination
    );

    // Write Destination Partition Table Entry Array
    Status = BlockIo->WriteBlocks(
        BlockIo, 
        BlockIo->Media->MediaId,
        Destination->PartitionEntryLba, 
        Size,
        EntryArray
    );
                                
    gBS->FreePool(EntryArray);
}


//<AMI_PHDR_START>
//=============================================================================
// Procedure: ValidateGptHeader
//
// Description: Checks if the GPT table is valid
//
// Input:
//      BlockIo - Pointer to the Parent BlockIo instance
//      GptHeader - Pointer to a memory area that contains the GPT header
//          to validate
//      HdrLoc - Header location
//
// Output: None
//
// Returns:
//      EFI_SUCCESS - GPT is valid
//      EFI_INVALID_PARAMETER - checks to see if the CRC, signature, and Header
//          Location are vlaid
//      EFI_OUT_OF_RESOURCES - Not enough free memory to allocate to read the
//          GPT entry table
//
// Referrals: CalculateCrc32 MemCmp AdjustBufferSize AllocatePool ReadBlocks
//      FreePool
//
//=============================================================================
//<AMI_PHDR_END>
EFI_STATUS ValidateGptHeader(
    IN EFI_BLOCK_IO_PROTOCOL    *BlockIo,
    IN GPT_HEADER       *GptHeader,
    IN EFI_LBA          HdrLoc
)
{
    EFI_STATUS          Status;
    UINT32              Crc;
    UINT32              Temp32;
    UINTN               Size;
    PARTITION_ENTRY     *GptEntryTable;
    
    
    // Get CRC of the Partition Header
    Temp32 = GptHeader->Header.CRC32;
    GptHeader->Header.CRC32 = 0;
    
    gBS->CalculateCrc32((UINT8*)GptHeader, sizeof(GPT_HEADER), &Crc);
    GptHeader->Header.CRC32 = Crc;
    
    // Check calculated CRC
    // Check signature
    // Check that MyLBA parameter points to the location of the current Header
    if (MemCmp(EFI_GPT_HEADER_ID, &GptHeader->Header.Signature, sizeof(UINT64))
            || (Temp32 != Crc)
            || (GptHeader->MyLba != HdrLoc) )
        return EFI_INVALID_PARAMETER;
        
    // Calculate the size of trasaction
    Size = GptHeader->NumberOfPartitionEntries *
           GptHeader->SizeOfPartitionEntry;
    AdjustBufferSize(BlockIo,&Size);
    
    // allocate memory for the Entry array
    Status = gBS->AllocatePool( EfiBootServicesData, Size, &GptEntryTable);
    
    if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;
    
    // get the data from the entry array
    BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId,
                        GptHeader->PartitionEntryLba,
                        Size, GptEntryTable);
                        
    // calculate the CRC value for the entry array
    gBS->CalculateCrc32((UINT8*)GptEntryTable,
                        GptHeader->NumberOfPartitionEntries*
                        GptHeader->SizeOfPartitionEntry, &Crc);
                        
    // the the allocated memory
    if (GptEntryTable != NULL ) gBS->FreePool(GptEntryTable);
    
    // check if the CRC that was calculated matches the value that was stored
    if (Crc != GptHeader->Crc32) return EFI_INVALID_PARAMETER;
    
    // All checks passed, the GPT is valid
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//=============================================================================
// Procedure: VerifyPartionTables
//
// Description: Check if either GPT is valid.  if only one is then fix the other
//      if both are bad, then it is not a valid GPT system.  return error
//
// Input:
//      BlockIo - pointer to the BlockIo partition so we can read and write
//          to the Block Device
//      DiskIo - Unused at this time
//
// Output:
//       GPT - pointer to a memory space for one GPT
//
// Returns: EFI_SUCCESS - If a valid GPT is found
//          EFI_UNSUPPORTED - if no valid GPT is found
//          EFI_OUT_OF_RESOURCES - not enough allocateable memory is available
//
// Referrals: AllocatePool ReadBlocks FreePool AdjustBufferSize
//      ValidateGPTHeader CopyGPT CopyMem
//
// Notes
//
//=============================================================================
//<AMI_PHDR_END>
EFI_STATUS VerifyPartionTables(
    IN      EFI_BLOCK_IO_PROTOCOL   *BlockIo,
    IN      EFI_DISK_IO_PROTOCOL    *DiskIo,
    OUT     GPT_HEADER              *Gpt
)
{
    EFI_STATUS  Status;
    GPT_HEADER  *Primary = NULL;
    GPT_HEADER  *Secondary = NULL;
    MASTER_BOOT_RECORD  *Pmbr = NULL;
    UINTN       Size;
    UINT8       i, FoundPP = 0;
    
    // Allocate a buffer for the Protective MBR
    Status = gBS->AllocatePool(EfiBootServicesData, BlockIo->Media->BlockSize, &Pmbr);
    
    if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;
    
    // Read the Protective MBR from LBA #0
    Status = BlockIo->ReadBlocks (BlockIo, BlockIo->Media->MediaId, 0,
                                  BlockIo->Media->BlockSize, Pmbr);
                                  
    if (EFI_ERROR (Status))
    {
        gBS->FreePool(Pmbr);
        return Status;
    }
    
    for (i=0; i < 4; i++)
    
        // See if Protective MBR is valid and if not free allocated memory and return EFI_UNSUPPORTED
        if ((Pmbr->PartRec[i].BootIndicator == 0x00) && (Pmbr->PartRec[i].OSType == 0xee) &&
                (Pmbr->PartRec[i].StartingLba == 1)) FoundPP++;
                
    if (FoundPP == 0)
    {
        gBS->FreePool(Pmbr);
        return EFI_UNSUPPORTED;
    }
    
    // Allocate memory to hold the data for the Primary and Secondary GPT headers
    // Allocate Primary
    Size=sizeof(GPT_HEADER);
    AdjustBufferSize(BlockIo, &Size);
    
    Status = gBS->AllocatePool(EfiBootServicesData, Size, &Primary);
    
    // if error is returned, exit with No resources available
    if (EFI_ERROR(Status))
    {
        gBS->FreePool(Pmbr);
        return EFI_OUT_OF_RESOURCES;
    }
    
    // Allocate for secondary header
    Status = gBS->AllocatePool(EfiBootServicesData, Size, &Secondary);
    
    // if error, free memory allocated for primary and then exit with no resources available
    if (EFI_ERROR(Status))
    {
        gBS->FreePool(Pmbr);
        gBS->FreePool(Primary);
        return EFI_OUT_OF_RESOURCES;
    }
    
    // Read primary and backup table
    BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId, 1, Size, Primary);
    BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId, BlockIo->Media->LastBlock, Size, Secondary);
    
    // read primary header from the block device and verify if it is valid
    if (EFI_ERROR(ValidateGptHeader(BlockIo, Primary, 1)))
    {
        // if primary is not valid, check secondary to see if it is valid
        if (EFI_ERROR(ValidateGptHeader(BlockIo, Secondary, BlockIo->Media->LastBlock)))
        {
            gBS->FreePool(Pmbr);
            gBS->FreePool(Primary);
            gBS->FreePool(Secondary);
            return EFI_UNSUPPORTED;
        }
        
        // if secondary table is good, copy to primary
        else
        {
            CopyGpt(BlockIo, DiskIo, Primary, Secondary);
        }
    }
    
    // if primary is good, check secondary
    else
    {
        // if secondary is bad, copy primary to secondary
        if (EFI_ERROR(ValidateGptHeader(BlockIo, Secondary, BlockIo->Media->LastBlock)))
        {
            CopyGpt(BlockIo, DiskIo, Secondary, Primary);
        }
    }
    
    // now that both tables are fixed, copy to GPT output variable and exit
    gBS->CopyMem(Gpt, Primary, sizeof(GPT_HEADER));
    
    // before we exit free all memory allocation and exit with success
    gBS->FreePool(Pmbr);
    gBS->FreePool(Primary);
    gBS->FreePool(Secondary);
    
    return EFI_SUCCESS;
}



//<AMI_PHDR_START>
//=============================================================================
// Procedure: GPTDiscoverPartitions
//
// Description: Searches GPT Table for partitions
//
// Input:
//  *This - Pointer to the instance of this blockIo protocol
//  *BlockIo - Pointer to the parent blockIo Protocol
//  *DiskIo - Pointer to the parent DiskIo protocol
//  *DevicePath - Pointer to the Parent's device path
//  ControllerHandle - the parent's controller handle
//
// Output:  None
//
// Returns:
//      EFI_SUCCESS - Driver loaded
//       other       - Driver not loaded
//
// Referrals: AllocatePool FreePool VerifyPartionTables AdjustBufferSize
//      MemCmp SetMem CopyMem CreateChildHandle SET_NODE_LENGTH
//
//=============================================================================
//<AMI_PHDR_END>
EFI_STATUS GptDiscoverPartitions (
    IN  EFI_DRIVER_BINDING_PROTOCOL *This,
    IN  EFI_BLOCK_IO_PROTOCOL       *BlockIo,
    IN  EFI_DISK_IO_PROTOCOL        *DiskIo,
    IN  EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
    IN  EFI_HANDLE                  ControllerHandle
)
{
    EFI_STATUS              Status;
    GPT_HEADER              *Gpt = NULL;
    UINT8                   *EntryArray = NULL;
    PARTITION_ENTRY         *PartEntry=NULL;
    HARDDRIVE_DEVICE_PATH   HdDp;
    PARTITION_DATA          PData;
    UINTN                   Idx;
    UINTN                   Size;
    
    
    // Allocate memory for a valid GPT partiton header
    Status = gBS->AllocatePool(EfiBootServicesData, sizeof(GPT_HEADER), &Gpt);
    
    if (EFI_ERROR(Status))
        return EFI_OUT_OF_RESOURCES;
        
//    EFI_DEADLOOP();
    // verify that the GPT headers on this BlockIo device are valid
    if (EFI_ERROR(VerifyPartionTables(BlockIo, DiskIo, Gpt )) )
    {
        gBS->FreePool(Gpt);
        return  EFI_INVALID_PARAMETER;
    }
    
    // If this gets executed, then the Headers are valid and the Entry array
    //  has the correct CRC value
    // Now parse through the Entry Array and create instances for each
    //  partition on the media
    // Check Entry Table Crc
    Size = Gpt->NumberOfPartitionEntries * Gpt->SizeOfPartitionEntry;
    AdjustBufferSize(BlockIo, &Size);
    
    Status = gBS->AllocatePool(EfiBootServicesData, Size, &EntryArray);
    
    if (EFI_ERROR(Status))
    {
        gBS->FreePool(Gpt);
        return EFI_OUT_OF_RESOURCES;
    }
    
    BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId,
                        Gpt->PartitionEntryLba, Size, EntryArray);
                        
    for (Idx = 0; Idx < Gpt->NumberOfPartitionEntries; Idx++)
    {
        PartEntry = (PARTITION_ENTRY *)(EntryArray + Idx * Gpt->SizeOfPartitionEntry);
        
        // Check to see if this is an unused partition
        if (!(MemCmp(&PartEntry->PartitionTypeGuid, &gUnusedPartitionGuid, sizeof(EFI_GUID))))
            continue; // This is an unused partition

        if(PartEntry->Attributes & 0x2) //bit 1 of Attributes set?
            continue;                   //no BlockIo for this partition - UEFI spec 2.3.1 p.5.3.3 table 19
            
        // clear the data structure
        gBS->SetMem(&PData, sizeof(PARTITION_DATA), 0);
        
        // set up the device path for the partition
        HdDp.Header.Type = MEDIA_DEVICE_PATH;
        HdDp.Header.SubType = MEDIA_HARDDRIVE_DP;
        SET_NODE_LENGTH(&HdDp.Header,sizeof(HARDDRIVE_DEVICE_PATH));
        
        // Idx is 0 based so add one so that partitionNumber is 1 based
        HdDp.PartitionNumber = (UINT32) Idx + 1;
        HdDp.PartitionStart = PartEntry->StartingLba;
        HdDp.PartitionSize = PartEntry->EndingLba - PartEntry->StartingLba + 1;
        gBS->CopyMem(&HdDp.Signature, &PartEntry->UniquePartitionGuid,
                     sizeof(EFI_GUID));
        HdDp.MBRType = MBR_TYPE_EFI_PARTITION_TABLE_HEADER;
        HdDp.SignatureType = SIGNATURE_TYPE_GUID;
        
        PData.DevPath = DPAddNode(DevicePath, &HdDp.Header);
        
        // save pertinent info
        PData.Handle = NULL;
        PData.ParentHandle = ControllerHandle;
        PData.ParentBlockIo = BlockIo;
        PData.ParentDiskIo = DiskIo;
        PData.StartingLba = PartEntry->StartingLba;
        PData.EndingLba = PartEntry->EndingLba;
        gBS->CopyMem(&PData.PartGuid, &PartEntry->PartitionTypeGuid,
                     sizeof (EFI_GUID));
                     
        // This is a valid GPT partition:  Add a child instance
        Status = CreateChildHandle(This, &PData, BlockIo->Media->BlockSize);
        
    }
    
    gBS->FreePool(Gpt);
    gBS->FreePool(EntryArray);
    
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
