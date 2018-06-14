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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/Partition/Mbr.c 12    4/16/10 4:24p Pats $
//
// $Revision: 12 $
//
// $Date: 4/16/10 4:24p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/Partition/Mbr.c $
// 
// 12    4/16/10 4:24p Pats
// EIP 30719: Support for the HDD with sector size more than 512bytes.
// 
// 11    2/04/10 3:03p Oleksiyy
// EIP 31633 Minor Fix
// 
// 10    7/09/09 5:01p Oleksiyy
// Files clean-up
//
// 9     11/13/08 6:10p Felixp
// Bug fix in MbrCreateChildHandle: unsed part of the signature (12 bytes)
// in hard driver device path was never initialized.
//
// 8     1/07/08 4:21p Robert
// Updated for coding standard
//
// 7     4/25/07 11:52a Robert
// Updated for CHM and coding standard commpliance
//
// 5     5/19/06 10:47p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
//
// 3     7/12/05 5:01p Robert
// The Free BSD operating system created a partition that referenced
// itself.  This was not checked for in the partition driver so an
// infinite loop was created.
// this reference now causes an error condition..
//
// 2     2/11/05 6:13p Felixp
// Code optimized by using DPAddNode instead of DPAdd
//
// 6     12/21/04 4:54p Markw
// Modified device path defines for consistency.
//
// 5     12/02/04 5:54p Robert
// Partition driver version works
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    Mbr.c
//
// Description: EFI Mbr Partition Generic Driver.  This file finds all
//      the partitions defined in the MBR found on a Device
//
//<AMI_FHDR_END>
//**********************************************************************
//-----------------------------------------------------------------------------
// Includes
#include "partition.h"
#include "mbr.h"


//-----------------------------------------------------------------------------
// Global Variables
EFI_GUID gMbrPartition  = EFI_PART_TYPE_LEGACY_MBR_GUID;



//-----------------------------------------------------------------------------
// Function Prototypes



//-----------------------------------------------------------------------------
// Function Definitions

//-----------------------------------------------------------------------------
//<AMI_PHDR_START>
// Procedure: CheckValidMbr
//
// Description: Makes sure the Master Boot Record has valid partitions
//
// Input:
//  *BlockIo - Pointer to the parent blockIo Protocol
//  *Mbr - pointer to a data structure that contains the MBR for
//          the current drive
//
// Output:  None
//
// Returns:
//      TRUE - MBR is valid
//      FALSE - MBR is invalid
//
// Referrals:  ReadBlocks
//
//<AMI_PHDR_END>
//-----------------------------------------------------------------------------

BOOLEAN CheckValidMbr(
    IN  EFI_BLOCK_IO_PROTOCOL       *BlockIo,
    IN  MASTER_BOOT_RECORD  *Mbr
)
{
    EFI_STATUS  Status;
    EFI_LBA     EndLba;
    UINT8       PartitionFound = 0;
    UINT8       Idx;
    UINT8       Loop2;
    
    // read the first block of the Harddrive
    Status = BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId, 0,
                                 BlockIo->Media->BlockSize, Mbr);
                                 
    if (Mbr->Sig != MBR_SIGNATURE)
        return FALSE;
        
    // check for valid LBA range for all the partitions
    for (Idx = 0; Idx < NUM_MBR_PARTITIONS; Idx++)
    {
        // ignore partitions whose OSType or Size is zero
        if ((Mbr->PartRec[Idx].OSType == 0)
                ||  (Mbr->PartRec[Idx].SizeInLba == 0))
            continue;
            
        if (Mbr->PartRec[Idx].StartingLba == 0)
            continue;
            
        PartitionFound++;
        
        EndLba = Mbr->PartRec[Idx].StartingLba
                 + Mbr->PartRec[Idx].SizeInLba - 1;
                 
        // check to make sure the partition does not exceed the length
        //  of the disk
        if (EndLba > BlockIo->Media->LastBlock)
            return FALSE;
            
        // Now loop through all partitions to make sure they don't overlap
        for (Loop2 = Idx+1; Loop2 < NUM_MBR_PARTITIONS; Loop2++)
        {
            // ignore partitions whose OSType or Size is zero
            if ((Mbr->PartRec[Loop2].OSType == 0)
                    ||  (Mbr->PartRec[Loop2].SizeInLba == 0))
                continue;
                
            // check for overlapping partitions
            if ( EndLba >= Mbr->PartRec[Loop2].StartingLba )
                return FALSE;
        }
    }
    
    if (PartitionFound)
        return TRUE;
    else
        return FALSE;
}



//-----------------------------------------------------------------------------
//<AMI_PHDR_START>
// Procedure: MbrCreateChildHandle
//
// Description: Searches Master Boot Record for partitions
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
// Referrals: AllocatePool FreePool CheckValidMbr SetMem ReadBlocks
//      CopyMem CreateChildHandle SET_NODE_LENGTH
//<AMI_PHDR_END>
//-----------------------------------------------------------------------------

EFI_STATUS MbrCreateChildHandle(
    IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
    IN  EFI_BLOCK_IO_PROTOCOL           *BlockIo,
    IN  EFI_DISK_IO_PROTOCOL            *DiskIo,
    IN  EFI_DEVICE_PATH_PROTOCOL        *DevicePath,
    IN  EFI_HANDLE                      ControllerHandle
)
{
    EFI_STATUS                  Status;
    MASTER_BOOT_RECORD          *Mbr = NULL;
    MASTER_BOOT_RECORD          *ExtPart = NULL;
    UINT8                       Idx;
    UINT32                      PartitionExists = 0;
    PARTITION_DATA              PData;
    EFI_GUID                    *PartType = NULL;
    EFI_LBA                     Lba;
    HARDDRIVE_DEVICE_PATH       HdDp;
    
    
    // allocate memory for the MBR and then read the data from the disk
    Status = gBS->AllocatePool( EfiBootServicesData,
                                BlockIo->Media->BlockSize, &Mbr);
                                
    if (EFI_ERROR(Status))
        return EFI_OUT_OF_RESOURCES;
        
    // check to see if the current drive has a valid MBR and a valid
    //  partition on the drive
    if (CheckValidMbr(BlockIo, Mbr) == FALSE)
    {
        gBS->FreePool(Mbr);
        return EFI_INVALID_PARAMETER;
    }
    
    // To get here there is a valid partition
    // create a handle for the partitions
    
    // set up the device path header for the partition
    HdDp.Header.Type = MEDIA_DEVICE_PATH;
    HdDp.Header.SubType = MEDIA_HARDDRIVE_DP;
    SET_NODE_LENGTH(&HdDp.Header,sizeof(HARDDRIVE_DEVICE_PATH));
    
    // Loop through the partitions
    for (Idx=0; Idx < NUM_MBR_PARTITIONS; Idx++)
    {
        // skip over empty partitions
        if ((Mbr->PartRec[Idx].OSType == 0)
                || (Mbr->PartRec[Idx].SizeInLba == 0))
            continue;
            
        // Take care of repetative data assignment
        // clear the data structure
        gBS->SetMem(&PData, sizeof(PARTITION_DATA), 0);
        
        // set up the device path for the partition
        HdDp.MBRType = MBR_TYPE_MASTER_BOOT_RECORD;
        HdDp.SignatureType = SIGNATURE_TYPE_MBR;
        pBS->SetMem(&HdDp.Signature,sizeof(HdDp.Signature),0);
        PData.Handle = NULL;
        PData.ParentBlockIo = BlockIo;
        PData.ParentDiskIo = DiskIo;
        
        
        // Now that a valid partition is found process it
        // TODO: are there any other types of extended partitions
        //  if so, add them to this if statement
        if ((Mbr->PartRec[Idx].OSType == EXTENDED_PARTITION) ||
                (Mbr->PartRec[Idx].OSType == WIN95_EXTENDED_PARTITION))
        {
            // process the logical partitions that may or may not exist
            Status = gBS->AllocatePool( EfiBootServicesData,
                                        BlockIo->Media->BlockSize, &ExtPart);
                                        
            if (EFI_ERROR(Status))
            {
                gBS->FreePool(Mbr);
                return EFI_OUT_OF_RESOURCES;
            }
            
            // defines where to start reading the next MBR/partition
            //  table from
            Lba = Mbr->PartRec[Idx].StartingLba;
            
            // loop through logical partitions: any number of
            //  possible partitions
            while (TRUE)
            {
                // if the table points back to itself, exit
                if ( Lba == 0)
                    break;
                    
                // get Partition table from the first block of the device
                Status = BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId,
                                             Lba, BlockIo->Media->BlockSize, ExtPart);
                                             
                // check to see if the disk was read
                // Also check for All logical partitions having an OSType
                //  of 0x05 or EXTENDED_PARTITION
                if (EFI_ERROR(Status))
                {
                    gBS->FreePool(Mbr);
                    gBS->FreePool(ExtPart);
                    return Status;
                }
                
                // make sure this is a valid partition
                if (ExtPart->PartRec[0].OSType == NO_PARTITION)
                    break;
                    
                // check for problems that make the partition invalid
                if ((Lba + ExtPart->PartRec[0].SizeInLba) >
                        (Mbr->PartRec[Idx].StartingLba
                         + Mbr->PartRec[Idx].SizeInLba))
                    break;
                    
                // register the Partition
                HdDp.PartitionNumber = ++PartitionExists;
                
                // notice that the start of the partition is after the
                //  partition table
                HdDp.PartitionStart = ExtPart->PartRec[0].StartingLba + Lba;
                HdDp.PartitionSize = ExtPart->PartRec[0].SizeInLba;
                gBS->CopyMem(&HdDp.Signature, &ExtPart->UniqueMbrSig,
                             sizeof(UINT32));
                PData.StartingLba = HdDp.PartitionStart;
                PData.EndingLba = HdDp.PartitionStart
                                  + ExtPart->PartRec[0].SizeInLba - 1;
                                  
                // create device path
                PData.DevPath = DPAddNode(DevicePath, &HdDp.Header);
                
                // Store Parent Handle
                PData.ParentHandle = ControllerHandle;
                
                // if the OSType member is 0xEF this variable set.
                //  otherwise it is left as 0
                if (ExtPart->PartRec[0].OSType == EFI_SYSTEM_PARTITION)
                    gBS->CopyMem(&PData.PartGuid, &gMbrPartition,
                                 sizeof (EFI_GUID));
                                 
                // This is a valid GPT partition:  Add a child instance
                Status = CreateChildHandle(This, &PData, BlockIo->Media->BlockSize);
                
                // check to see if the next partition is an extended partition
                if ((ExtPart->PartRec[1].OSType != EXTENDED_PARTITION) &&
                        (ExtPart->PartRec[1].OSType != WIN95_EXTENDED_PARTITION) )
                    break;
                    
                // get set up for the next partition.  The Starting Lba
                //  address is a relative address inside the extended
                //  partition add the starting address of the extended
                //  partition to get the actual LBA where it starts
                Lba = ExtPart->PartRec[1].StartingLba
                      + Mbr->PartRec[Idx].StartingLba;
            }
        }
        
        else // process primary partition
        {
            // set up the device path for the partition
            HdDp.PartitionNumber = ++PartitionExists;
            HdDp.PartitionStart = Mbr->PartRec[Idx].StartingLba;
            HdDp.PartitionSize = Mbr->PartRec[Idx].SizeInLba;
            gBS->CopyMem(HdDp.Signature, &Mbr->UniqueMbrSig, sizeof(UINT32));
            
            // create device path
            PData.DevPath = DPAddNode(DevicePath, &HdDp.Header);
            
            // save pertinent info
            PData.StartingLba = Mbr->PartRec[Idx].StartingLba;
            PData.EndingLba = Mbr->PartRec[Idx].StartingLba
                              + Mbr->PartRec[Idx].SizeInLba - 1;
                              
            // Store Parent Handle
            PData.ParentHandle = ControllerHandle;
            
            // if the OSType member is 0xEF is this variable set.
            //  otherwise it is left as 0
            if (Mbr->PartRec[Idx].OSType == 0xEF)
                gBS->CopyMem(&PData.PartGuid, &gMbrPartition,
                             sizeof (EFI_GUID));
                             
            // This is a valid GPT partition:  Add a child instance
            Status = CreateChildHandle(This, &PData, BlockIo->Media->BlockSize);
            
        }
    }
    
    gBS->FreePool(Mbr);
    gBS->FreePool(ExtPart);
    
    return EFI_SUCCESS;
}

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
