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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/Partition/ElTorito.c 21    8/28/12 3:14p Pats $
//
// $Revision: 21 $
//
// $Date: 8/28/12 3:14p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/Partition/ElTorito.c $
// 
// 21    8/28/12 3:14p Pats
// [TAG]  EIP99287
// [Category]  Bug Fix
// [Severity]  Important
// [Symptom]  Problem booting certain HDD emulation ElTorito CD/DVD's.
// [RootCause] If the CD has ElTorito and ISO9660 partitions, the block
// sizeread will be  the ISO9660 block size, but the ElTorito partition
// needs the HDD block size
// [Solution] Set block size to HDD block size if HDD emulation detected.
// [Files]  Eltorito.c
// 
// 20    5/10/12 5:54a Rameshr
// [TAG]  		EIP88924
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	UEFI 2.3.1 SCT block io read test fail
// [RootCause]  	If the CD has two Boot image , two blockio will be
// installed by Partition driver. But the second blockIo , LastBlock value
// is wrong
// [Solution]  	2nd logical blockIO LastBlock size calculation corrected.
// [Files]  		Eltorito.c
// 
// 19    9/27/11 7:43p Yul
// [TAG]  		EIP69053
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System cannot boot to WINPE from CD/DVD.
// [RootCause]  	Blocksize change 
// [Solution]  	Blocksize change 
// [Files]  		EIOorito.c
// 
// 18    5/10/11 11:21a Pats
// [TAG] - EIP 57859 
// [Category]- BUG FIX
// [Severity]- Normal
// [Symptom] - On EFI shell, though CD media is recognized as a Block
// device, is not recognized as a File system.
// [RootCause] - Blocksize change from EIP 30719.
// [Solution] - Removed change from EIP 30719.
// [Files] - ElTorito.c
// 
// 17    4/16/10 4:24p Pats
// EIP 30719: Support for the HDD with sector size more than 512bytes.
// 
// 16    10/20/09 5:02p Felixp
// Check for a block I/O device errors is added in
// ElToritoCreateChildHandle function.
// 
// 14    7/09/09 5:01p Oleksiyy
// Files clean-up
//
// 13    4/23/09 11:54a Oleksiyy
// Memory free error fix
//
// 12    2/19/09 1:02p Artems
// EIP 19052 Minor improvement to support CD burned with Windows Explorer
//
// 11    1/16/09 3:02p Felixp
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
// 10    1/07/08 4:21p Robert
// Updated for coding standard
//
// 9     4/24/07 5:31p Robert
// Updated Headers to compile with CHM creation
//
// 8     3/22/07 5:39p Robert
// Updated Files for coding standard
//
// 7     8/24/06 12:34p Felixp
// x64 support (fixes for warnings/errors)
//
// 5     5/19/06 10:47p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
//
// 3     5/05/05 5:07p Robert
// When reading the data for the Volume Descriptor.  There was no check
// for the Status of the Read Blocks call.  If this returned an error then it
// was continuing on.  Now it exits when an error is found
//
// 2     2/11/05 6:13p Felixp
// Code optimized by using DPAddNode instead of DPAdd
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 3     12/21/04 4:53p Markw
// Modified device path defines for consistency.
//
// 2     12/02/04 5:54p Robert
// Partition driver version works
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    ElTorito.c
//
// Description: EFI El Torito Partition Support Functions
//
//<AMI_FHDR_END>
//**********************************************************************

//=============================================================================
// Includes
#include "Partition.h"
#include "ElTorito.h"
#include "mbr.h"

extern BOOLEAN Iso9660FileSystemSupportEnabled;
EFI_GUID VendorDpGuid = AMI_ISO9660_MEDIA_GUID;

//=============================================================================
// Local Variables

//=============================================================================
// Function Definitions



//<AMI_PHDR_START>
//=============================================================================
// Procedure: ElToritoCreateChildHandle
//
// Description: Searches CDROM disk for El Torito bootable partitions
//      and creates a child handle for each one found
//
// Input:
//      *This - Pointer to the instance of this blockIo protocol
//      *BlockIo - Pointer to the parent blockIo Protocol
//      *DiskIo - Pointer to the parent DiskIo protocol
//      *DevicePath - Pointer to the Parent's device path
//      ControllerHandle - the parent's controller handle
//
// Output:
//
// Returns:
//      EFI_SUCCESS - Partition found
//      EFI_INVALID_MEDIA - a parameter passed in or in the data structure
//          is invalid
//      EFI_NO_MEDIA - No partitions found
//      EFI_OUT_OF RESOURCES - Not enough resources to allocate memory
//
// Referrals: ReadBlocks AllocatePool MemCmp FreePool Div64 SetMem
//      CreateChildHandle DPAddNode SET_NODE_LENGTH
//
//=============================================================================
//<AMI_PHDR_END>
EFI_STATUS  ElToritoCreateChildHandle (
    IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
    IN  EFI_BLOCK_IO_PROTOCOL           *BlockIo,
    IN  EFI_DISK_IO_PROTOCOL            *DiskIo,
    IN  EFI_DEVICE_PATH_PROTOCOL        *DevicePath,
    IN  EFI_HANDLE                      ControllerHandle
)
{
    PARTITION_DATA          PData, DData;
    EFI_STATUS              Status;
    EFI_LBA                 Lba;
    BOOT_RECORD_DESC        *VolDesc = NULL;
    EL_TORITO_ENTRIES       *Entry = NULL, *StartEntry = NULL;
    CDROM_DEVICE_PATH       CdDp;
    UINT32                  BlockSize;
    UINT16                  Checksum;
    UINT16                  *Temp = NULL;
    UINTN                   Idx;
    UINT32                  VolSize;
    UINT32                  Sectors;
    UINTN                   BootEntry;
    UINTN                   Dummy;
    
    AMI_ISO9660_DEVICE_PATH      VendorDp;
    PRIMARY_VOLUME_DESC_HEADER  *PrimVolDesc;
    
    
// TODO:  The El Torito spec says that the Boot Record Volume only exists on the last session
//          we need to find the last session on the CD

    // Verify that the CDROM is using the correct block size
    if (BlockIo->Media->BlockSize != CDROM_BLOCK_SIZE)
    {
        return EFI_INVALID_PARAMETER;
    }
    
    // Allocate memory for the Boot Record Volume
    Status = gBS->AllocatePool(EfiBootServicesData, BlockIo->Media->BlockSize, &VolDesc);
    
    if (EFI_ERROR(Status))
        return EFI_OUT_OF_RESOURCES;
        
    // CDROM Spec says sector 16 contains the Primary Volume descriptor
    Lba = CDROM_BOOT_PRI_VOL_DESCRIPTOR_SECTOR;
    
    Status = BlockIo->ReadBlocks( BlockIo, BlockIo->Media->MediaId, Lba,
                         BlockIo->Media->BlockSize, VolDesc );
    if (EFI_ERROR(Status))
    {
        gBS->FreePool(VolDesc);
        return EFI_INVALID_PARAMETER;
    }
                         
    // Check for valid volume descriptor signature
    if (MemCmp (VolDesc->IsoId, "CD001", 5))
    {
        gBS->FreePool(VolDesc);
        return EFI_INVALID_PARAMETER;
    }
    
//***********************************************************************
//                   Add Logical partition for ISO 9660 support
//***********************************************************************
    PrimVolDesc = (PRIMARY_VOLUME_DESC_HEADER *)VolDesc;
    BlockSize = CDROM_BLOCK_SIZE;
    
    //Set Vendor device path
    VendorDp.Dp.Header.Type = MEDIA_DEVICE_PATH;
    VendorDp.Dp.Header.SubType = MEDIA_VENDOR_DP;
    VendorDp.Dp.Guid = VendorDpGuid;
    VendorDp.VolumeSize = PrimVolDesc->VolSpaceSize;
    VendorDp.Root = PrimVolDesc->Root;
    MemCpy(VendorDp.VolumeLabel, PrimVolDesc->VolId, 32);
    SET_NODE_LENGTH(&VendorDp.Dp.Header,sizeof(AMI_ISO9660_DEVICE_PATH));
    
    
    // clear the data structure
    gBS->SetMem(&DData, sizeof(PARTITION_DATA), 0);
    
    // create new device path
    DData.DevPath = DPAddNode(DevicePath, &(VendorDp.Dp.Header));
    
    // save pertinent info
    DData.Handle = NULL;
    DData.ParentBlockIo = BlockIo;
    DData.ParentDiskIo = DiskIo;
    DData.StartingLba = 0;
    DData.EndingLba = BlockIo->Media->LastBlock;
    
    // Store Parent Handle
    DData.ParentHandle = ControllerHandle;
    
//***********************************************************************
//                           End of ISO 9660 support
//***********************************************************************

    // Get the Volume Space Size from Primary Volume Descriptor,
    //  the 32-bit numerical value is stored in Both-Little and Big Endian
    VolSize = VolDesc->VolSpaceSize[0];
    
    
    // El Torito Spec says sector 17 contains the Boot Record
    //  Volume:  Read and verify the data
    Lba = CDROM_BOOT_REC_VOL_DESCRIPTOR_SECTOR;
    
    Status = BlockIo->ReadBlocks( BlockIo, BlockIo->Media->MediaId, Lba,
                                  BlockIo->Media->BlockSize, VolDesc );
                                  
    if (EFI_ERROR(Status))
    {
        gBS->FreePool(VolDesc);
        VolDesc = NULL;
        goto EndOfEltorito;
    }
    
    // Validate the info in the Boot Record
    if ((VolDesc->BootIndicator != 0) || ( MemCmp (VolDesc->IsoId, "CD001", 5)) ||
            (VolDesc->Version != 1) || (MemCmp(VolDesc->Identifier, EL_TORITO_SPEC, 23) ) )
    {
        // not a valid boot Record
        gBS->FreePool(VolDesc);
        VolDesc = NULL;
        goto EndOfEltorito;
    }
    
    // There is a valid boot record.  move on to the Boot catalog
    Lba = VolDesc->BootCatalog;
    
    Status = gBS->AllocatePool(EfiBootServicesData, BlockIo->Media->BlockSize, &StartEntry);
    
    if (EFI_ERROR(Status))
    {
        gBS->FreePool(VolDesc);
        VolDesc = NULL;
        goto EndOfEltorito;
    }
    
    // Now load the Boot Catalog and find all the partitions
    BlockIo->ReadBlocks( BlockIo, BlockIo->Media->MediaId, Lba,
                         BlockIo->Media->BlockSize, StartEntry );
                         
    // get pointer to the first entry in the Boot Record
    Entry = (EL_TORITO_ENTRIES *)StartEntry;
    
    if ((Entry->ValEntry.HeaderId != 1) || (Entry->ValEntry.Sig != 0xaa55))
    {
        gBS->FreePool(VolDesc);
        VolDesc = NULL;
        gBS->FreePool(StartEntry);
        StartEntry = NULL;
        goto EndOfEltorito;
    }
    
    // Now Calculate checksum
    Checksum = 0;
    Temp = (UINT16 *)Entry;
    
    for (Idx = 0; Idx < 16; Idx++)
        Checksum += Temp[Idx];
        
    // if the checksum is not 0 then the Boot catalog is considered invalid
    if (Checksum)
    {
        gBS->FreePool(VolDesc);
        VolDesc = NULL;
        gBS->FreePool(StartEntry);
        StartEntry = NULL;
        goto EndOfEltorito;
    }
    
    // The checksum is zero so here we go
    
    // Find and install the Boot entries
    //  loop through the boot catalog looking for bootable entries
    //  start at the second entry in the boot catalog,
    //  the first is the validation entry
    Entry++;
    
    for ( Idx = 0, BootEntry = 0; Idx < ((CDROM_BLOCK_SIZE/ sizeof(EL_TORITO_ENTRIES)) - 1);
            Idx++, Entry++)
    {
        // if it isn't bootable, get next entry
        if (Entry->DefaultEntry.BootId != CDROM_BOOTABLE)
            continue;


        BlockSize = BlockIo->Media->BlockSize;        
        if( (BlockSize == 0) || (BlockSize == 0xFFFFFFFF) ) {
            BlockSize = 512;
        }
        TRACE((TRACE_DXE_CORE, "BlockSize is %d, MediaID is %d\n", BlockSize, BlockIo->Media->MediaId));

        Sectors = Entry->DefaultEntry.SectorCount;
        TRACE((TRACE_DXE_CORE, "Sector count is %d\n", Sectors));
        TRACE((TRACE_DXE_CORE, "Media Type is %d\n", Entry->DefaultEntry.MediaType));
        
        // use this switch to set the Partition Size
        switch (Entry->DefaultEntry.MediaType)
        {
            case FLOPPY_144:
                Sectors = FLOPPY_144_SIZE_LBA;
                break;
            case FLOPPY_288:
                Sectors = FLOPPY_288_SIZE_LBA;
                break;
            case FLOPPY_12:
                Sectors = FLOPPY_12_SIZE_LBA;
                break;
                
            case NO_EMULATION:
                BlockSize = CDROM_BLOCK_SIZE;
                break;
                
            case HARD_DRIVE:
                BlockSize = 512;
                break;
            default:
                continue;
        }
        
        
        if ((Idx != 0) && (BootEntry == 0))
            BootEntry++;
            
        CdDp.BootEntry = (UINT32) BootEntry++;
        
        CdDp.PartitionStart = Entry->DefaultEntry.LoadLba;
        
        if (Sectors < 2) 
            CdDp.PartitionSize = (VolSize > BlockIo->Media->LastBlock + 1) ? 
                                (UINT32)(BlockIo->Media->LastBlock - CdDp.PartitionStart + 1) : 
                                (UINT32)(VolSize - CdDp.PartitionStart);

        else
            CdDp.PartitionSize = Div64(Sectors* BlockSize + BlockIo->Media->BlockSize - 1,
                                       BlockIo->Media->BlockSize, &Dummy );
                                       
        // set up the device path for the partition
        CdDp.Header.Type = MEDIA_DEVICE_PATH;
        CdDp.Header.SubType = MEDIA_CDROM_DP;
        SET_NODE_LENGTH(&CdDp.Header,sizeof(CDROM_DEVICE_PATH));
        
        // clear the data structure
        gBS->SetMem(&PData, sizeof(PARTITION_DATA), 0);
        
        // create new device path
        PData.DevPath = DPAddNode(DevicePath, &CdDp.Header);
        
        // save pertinent info
        PData.Handle = NULL;
        PData.ParentBlockIo = BlockIo;
        PData.ParentDiskIo = DiskIo;
        PData.StartingLba = CdDp.PartitionStart;
        PData.EndingLba = CdDp.PartitionStart + CdDp.PartitionSize - 1;
        
        // Store Parent Handle
        PData.ParentHandle = ControllerHandle;
        
        // This is a valid GPT partition:  Add a child instance
        Status = CreateChildHandle(This, &PData, BlockSize);
    }
    
EndOfEltorito:

    if (VolDesc != NULL)    gBS->FreePool(VolDesc);
    
    if (StartEntry != NULL) gBS->FreePool(StartEntry);
    
    if (Iso9660FileSystemSupportEnabled)
    {
        Status = CreateChildHandle(This, &DData, CDROM_BLOCK_SIZE);
    }
    
    return Status;
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
