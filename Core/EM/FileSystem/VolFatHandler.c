//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/FileSystem/VolFatHandler.c 9     12/02/09 9:29a Pats $
//
// $Revision: 9 $
//
// $Date: 12/02/09 9:29a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/FileSystem/VolFatHandler.c $
// 
// 9     12/02/09 9:29a Pats
// EIP 32115: The fat driver in aptio does not calculate free space
// correctly.
// Solution: AllocateAndLinkClusters() changed to calculate new cluster
// for free space differently, and to fix error path.
// 
// 8     7/02/09 5:47p Pats
// Updated to latest coding standard. No code changes.
//
// 7     5/17/07 4:00p Srinin
// Uninitialized varaible FreeClusters in UpdateFreeSpace initialized.
//
// 6     4/13/07 7:07p Pats
// Edited to conform with coding standards. No code changes.
//
// 5     4/05/07 12:14p Pats
// Fixed GetFreeClusterCount function. BufferSize variable was not being
// handled properly on large disks.
//
// 4     9/13/06 5:57p Pats
// Fixed problem of free space reported incorrectly on El Torito CD.
//
// 7     11/03/05 2:16p Srinin
// Fixed VC7.1 warning msg.
//
// 6     9/14/05 4:30p Pats
// Fixed problem of free disk space being calculated incorrectly in some
// cases.
//
// 5     7/19/05 2:58p Pats
// Removed a little unnecessary code and added comments.
//
// 4     6/21/05 3:45p Pats
// Added function MarkVolumeDirty, to mark FAT16 and FAT32 volumes if any
// EFI_VOLUME_CORRUPTED error occurs.
//
// 3     6/16/05 4:18p Pats
// Fixed problem in UnlinkFat -- did not unlink FAT12 files properly in
// every case.
//
// 2     5/27/05 10:02a Srinin
// Fix for free space calculation.
//
// 1     4/26/05 6:05p Srinin
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:    VolFatHndlr.c
//
// Description: Fat File System driver -- Volume Level Fat Handler
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "FileSystem.h"

//----------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:     GetSectorAddressDir
//
// Description:   Gets the absolute sector of a directory
//
// Parameters:
//  FILE_HANDLE *fh - File Handle
//  UINT32      Cluster - Cluster of directory
//  UINT32      ClusterOffset - Offset in cluster
//  UINT32      *Sector - Absolute sector of directory
//  UINT32      *SectorOffset - Offset in sector
//
// Return value: None
//
// Modified:
//
// Referrals:
//
// Notes:   Use this routine if DIR region neeeds to be Read/Written.
//          For Data Region or FAT32 ROOT dir use GetAbsSectorInfo
//          For FAT12/16 root dir, Cluster is not valid. ClusterOffset
//          is the relative offset within the Root Dir Region.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
GetSectorAddressDir (
    FILE_HANDLE *fh,
    UINT32      Cluster,
    UINT32      ClusterOffset,
    UINT32      *Sector,
    UINT32      *SectorOffset
)
{
    VOLUME_INFO *vi = fh->VolumeInterface;
    
    if (fh->ROOTDIR && (vi->FatType != FAT32)) {
        *Sector = ClusterOffset / vi->VolumeBPB.BPB_BytePerSec + vi->FirstRootDirSector;
        *SectorOffset = ClusterOffset % vi->VolumeBPB.BPB_BytePerSec;
        
    } else {
        GetAbsSectorInfo (vi, Cluster, ClusterOffset, Sector, SectorOffset);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FatClusterNumberLocation
//
// Description: Returns the location (sector and offset) of a valid cluster
//              number in the specified FAT.
//
// Parameters:
//  IN VOLUME_INFO      *Vol,       The volume structure
//  IN UINTN            Cluster,    A cluster number
//  IN UINTN            FatNumber,  The fat number (0 or 1)
//
// Return value:
//  EFI_STATUS
//    EFI_SUCCESS - Cluster located
//      OUT UINT32          *Sector,        Fat sector in which cluster is located
//      OUT UINT32          *SectorOffset   Offset in the sector where cluster is
//    other       - Cluster not located
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FatClusterNumberLocation (
    IN VOLUME_INFO *Vol,
    IN UINT32      Cluster,
    IN UINT8       FatNumber,
    OUT UINT32     *Sector,
    OUT UINT32     *SectorOffset
)
{
    UINT32 FatOffset;
    
    if (Cluster > Vol->CountOfDataClusters + 2) {
        return EFI_INVALID_PARAMETER;
    }
    
    switch (Vol->FatType) {
        case FAT12:
            FatOffset = Cluster + (Cluster / 2);
            break;
        case FAT16:
            FatOffset = Cluster * 2;
            break;
        case FAT32:
            FatOffset = Cluster * 4;
            break;
        default:
            return EFI_UNSUPPORTED;
    }
    
    *Sector       = FatNumber * Vol->FATSz + Vol->VolumeBPB.BPB_RsvdSecCnt
                    + FatOffset / Vol->VolumeBPB.BPB_BytePerSec;
    *SectorOffset = FatOffset % Vol->VolumeBPB.BPB_BytePerSec;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ReadFatClusterNumber
//
// Description: Reads a single cluster number from the specified fat table
//
// Parameters:
//  IN VOLUME_INFO      *Vol,       The volume structure
//  IN UINTN            Cluster,    A cluster number
//  IN UINT8            FatNumber,  The fat number (0 or 1)
//  OUT UINT32          *Value      The returned cluster number
//
// Return value:
//  EFI_STATUS
//    EFI_SUCCESS - Cluster read
//    other       - Cluster not read
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ReadFatClusterNumber (
    IN VOLUME_INFO *Vol,
    IN UINT32      Cluster,
    IN UINT8       FatNumber,
    OUT UINT32     *Value
)
{
    EFI_STATUS Status;
    UINT32     Sector = 0;
    UINT32     SectorOffset = 0;
    UINT32     ValueSize;
    
    Status = FatClusterNumberLocation(Vol, Cluster, FatNumber, &Sector, &SectorOffset);
    
    if (EFI_ERROR(Status)) return Status;
    
    if (Vol->FatType == FAT32) ValueSize = sizeof(UINT32);
    
    else ValueSize = sizeof(UINT16);
    
    Status = FsReadMedia (Vol,
                          (UINT8 *)Value,
                          (UINT64)Sector,
                          SectorOffset,
                          ValueSize,
                          FAT_REGION);
                          
    if (EFI_ERROR(Status)) return Status;
    
    switch (Vol->FatType) {
        case FAT12:
        
            if (Cluster & 0x0001) *Value >>= 4;
            
            *Value &= 0x0fff;
            break;
        case FAT16:
            *Value &= 0x0ffff;
            break;
        case FAT32:
            *Value &= 0x0fffffff;       // FAT32 actually uses 28 bits
            break;
        default:
            return EFI_UNSUPPORTED;
    }
    
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   WriteFatClusterNumber
//
// Description: Writes a single cluster number into the specified FAT table
//
// Parameters:
//  IN VOLUME_INFO      *Vol,       The volume structure
//  IN UINTN            Cluster,    A cluster number
//  IN UINT8            FatNumber,  The fat number (0 or 1)
//  IN UINT32           Value       The cluster value to be written
//
// Return value:
//  EFI_STATUS
//    EFI_SUCCESS - Cluster written
//    other       - Cluster not written
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
WriteFatClusterNumber (
    IN VOLUME_INFO *Vol,
    IN UINT32      Cluster,
    IN UINT8       FatNumber,
    IN UINT32      Value
)
{
    EFI_STATUS Status;
    UINT32     Sector = 0;
    UINT32     SectorOffset = 0;
    UINT32     TempValue;
    UINT32     ValueSize;
    
    Status = FatClusterNumberLocation(Vol, Cluster, FatNumber, &Sector, &SectorOffset);
    
    if (EFI_ERROR(Status)) return Status;
    
    if (Vol->FatType == FAT32) ValueSize = sizeof(UINT32);
    
    else ValueSize = sizeof(UINT16);
    
    switch (Vol->FatType) {
        case FAT12:
            Status = FsReadMedia (Vol,
                                  (UINT8 *)&TempValue,
                                  (UINT64)Sector,
                                  SectorOffset,
                                  ValueSize,
                                  FAT_REGION);
                                  
            if (EFI_ERROR(Status)) return Status;
            
            if (Cluster & 0x0001) {
                Value <<= 4;
                TempValue &= 0x000f;
                
            } else {
                Value &= 0x0FFF;
                TempValue &= 0xf000;
            }
            
            TempValue |= (UINT16)Value;
            break;
        case FAT16:
            TempValue = (UINT16)Value;
            break;
        case FAT32:
            Value   &= 0x0fffffff;
            TempValue = Value;
            break;
        default:
            return EFI_UNSUPPORTED;
    }
    
    Status = FsWriteMedia (Vol,
                           (UINT8 *)&TempValue,
                           (UINT64)Sector,
                           SectorOffset,
                           ValueSize,
                           FAT_REGION);
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:     AllocateAndLinkClusters
//
// Description:   Allocates clusters for use in a file
//
// Parameters:
//  IN VOLUME_INFO *Vol - Volume info
//  IN UINT32      BeginCluster - Beginning cluster no.
//  IN UINT32      Size - Size to allocate
//  OUT UINT32     *FirstCluster - First cluster allocated
//  OUT UINT32     *ClusterCount - Count of clusters allocated
//
// Return value:  EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AllocateAndLinkClusters (
    IN VOLUME_INFO      *Vol,
    IN UINT32           BeginCluster,
    IN UINT32           Size,
    OUT UINT32          *FirstCluster,
    OUT UINT32          *ClusterCount
)
{

    UINT32     ClustersRequired, NewCluster = 2, Dummy, NewBlocks, k, j;
    EFI_STATUS Status;

    *FirstCluster = 0;
    *ClusterCount = 0;

//  Calculate the # of Clusters required.
    ClustersRequired = GetClustersRequired (Vol, Size);

    if (Vol->FreeSpaceinClusters != -1 && Vol->FreeSpaceinClusters < ClustersRequired)
        return  EFI_VOLUME_FULL;

    do {

        NewBlocks = ClustersRequired;

        if (Vol->LastFreeCluster != -1) NewCluster = Vol->LastFreeCluster;
        else {
            Status = ReturnFreeSpace(Vol);
            NewCluster = Vol->LastFreeCluster;
            if (EFI_ERROR(Status)) return Status;
        }

        Status = FindFreeClusters(Vol, NewCluster, Vol->CountOfDataClusters+2, &NewCluster, &NewBlocks, &Dummy);
        if (EFI_ERROR(Status)) {
            if (Status == EFI_NOT_FOUND && NewCluster != 2) {
//              No cluster found after the current one, try from the start of the disk.
                NewBlocks = ClustersRequired;
                Status = FindFreeClusters(Vol, 2, Vol->CountOfDataClusters+2, &NewCluster, &NewBlocks, &Dummy);
                if (EFI_ERROR(Status)) {
                    if (Status == EFI_NOT_FOUND) return EFI_VOLUME_FULL; else return Status;
                }
            }
            else if (Status == EFI_NOT_FOUND) return EFI_VOLUME_FULL;
            if (EFI_ERROR(Status)) return Status;
        }

        if (!*FirstCluster) *FirstCluster = NewCluster;

//      Add new cluster(s) to fat chain.
        for (k=1; k <= NewBlocks; k++) {

            for (j=0; j < Vol->VolumeBPB.BPB_NumFATs; j++) {            // Update all fats.
//              Chain the new cluster
                if (BeginCluster >=2) {
                    Status = WriteFatClusterNumber(Vol, BeginCluster, j, NewCluster);
                    if (EFI_ERROR(Status)) return Status;
                }
//              Update the EOCfot the Last Block
                Status = WriteFatClusterNumber(Vol, NewCluster, j, Vol->EOCMark);
                if (EFI_ERROR(Status)) return Status;
            }   // end of j

#ifdef Debug_AllocateClusters
            EfiDebugPrint(-1,"%x", NewCluster);
#endif

            BeginCluster = NewCluster;
            NewCluster++;
        } // end for (k)
       *ClusterCount += NewBlocks;
        ClustersRequired -= NewBlocks;
        UpdateFreeSpace (Vol, NewBlocks,  FALSE);       // Subtract from Free space
    }while (ClustersRequired);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   UnlinkFat
//
// Description: Unlinks (marks as free) all the clusters of the chain
//              starting from cluster Cluster (that must be part of a valid
//              chain) until the EOC.
//
// Parameters:
//  IN VOLUME_INFO      *Vol,       The volume structure
//  IN UINTN            Cluster     A cluster number
//
// Return value:
//  EFI_STATUS
//    EFI_SUCCESS - Chain unlinked.
//    other       - Chain not unlinked
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UnlinkFat (
    IN VOLUME_INFO *Vol,
    IN UINT32      Cluster,
    OUT UINT32     *ClusterCount
)
{
    EFI_STATUS Status;
    UINT8      i;
    UINT32     Next;
    
    *ClusterCount = 0;
    
    do {
        if (!Cluster) return EFI_NOT_FOUND;
        
        Status = ReadFatClusterNumber(Vol, Cluster, 0, &Next);
        
        if (EFI_ERROR(Status)) return Status;
        
        if (Next < 2) {
            MarkVolumeDirty (Vol);
            return EFI_VOLUME_CORRUPTED;
        }
        
        /* Update every FAT in the volume */
        for (i = 0; i < Vol->VolumeBPB.BPB_NumFATs; i++) {
            Status = WriteFatClusterNumber(Vol, Cluster, i, 0);
            
            if (EFI_ERROR(Status)) return Status;
        }
        
        Cluster = Next;
        ++*ClusterCount;
    } while (Next < Vol->EOCMark);   // Repeat till end of chain found.
    
    UpdateFreeSpace (Vol, *ClusterCount, TRUE);         // Add to Free space
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FindFreeClusters
//
// Description: Searches a volume for a free cluster in the specified range
//              of clusters.
//
// Parameters:
//  IN VOLUME_INFO      *Vol,           The volume structure
//  IN UINT32           From,           Cluster to start search at
//  IN UINT32           To,             End of search range
//  OUT UINT32          *StartCluster   Free cluster found
//  IN OUT UINT32       *FreeClusters   In - free clustere requested.
//                                      Out - Free clusters found
//  OUT UINT32          *TotalFree      Total free clusters found in this
//                                      search
//
// Return value:
//  EFI_STATUS
//    EFI_SUCCESS   - Free cluster found, Vol->LastFreeCluster updated.
//    EFI_NOT_FOUND - Free cluster not found.
//    other         - any other error.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FindFreeClusters (
    IN VOLUME_INFO *Vol,
    IN UINT32      From,
    IN UINT32      To,
    OUT UINT32     *StartCluster,
    IN OUT UINT32  *FreeClusters,
    OUT UINT32     *TotalFree
)
{
    EFI_STATUS Status;
    UINT32     Count = 0;
    UINT32     FreeCount = 0;
    UINT32     LastFree = 0;
    UINT32     FreeBlock = 0;
    UINT32     PrevFreeCount, PrevFreeBlock;
    UINT32     i;
    UINT32     Value;
    
//  if (From == 0) return (FindNextFreeCluster (Vol, Cluster));

    for (i = From; i < To; i++) {
        Status = ReadFatClusterNumber(Vol, i, 0, &Value);
        
        if (EFI_ERROR(Status)) return Status;
        
        if (Value == 0) {
            Count++;
            
            if (i != (LastFree + 1)) {
                PrevFreeBlock = FreeBlock;
                PrevFreeCount = FreeCount;
                FreeBlock = i; // Reset free block if not contiguous
                FreeCount = 0; // Restart free count
            }
            
            LastFree = i;
            FreeCount++;
            
            if (FreeCount >= *FreeClusters) { // If we found the requested count
                *FreeClusters = FreeCount;
                *StartCluster = Vol->LastFreeCluster = FreeBlock;
                *TotalFree = Count;
                return EFI_SUCCESS;
            }
        }
    }
    
    if (Count) {
        *TotalFree = Count;
        
        if (FreeCount > PrevFreeCount) {  // in case the last free block is not the largest.
            *StartCluster = FreeBlock;
            *FreeClusters = FreeCount;
            
        } else {
            *StartCluster = PrevFreeBlock;
            *FreeClusters = PrevFreeCount;
        }
        
        return EFI_SUCCESS;
        
    } else return EFI_NOT_FOUND;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ClusterToSector
//
// Description: Converts a custer number to an absolute sector number
//              (relative to the beginning of the volume).
//
// Parameters:
//  IN VOLUME_INFO      *Vol,         The volume structure
//  OUT UINTN           Cluster       The cluster to be converted
//
// Return value:
//  Returns the sector number.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
ClusterToSector (
    IN VOLUME_INFO *Vol,
    IN UINT32      Cluster
)
{
    UINT32 Offset;
    UINT32 Sector;
    
    Offset = Vol->VolumeBPB.BPB_RsvdSecCnt + Vol->FATSz * Vol->VolumeBPB.BPB_NumFATs +
             Vol->RootDirSectorCount;
             
    if (Cluster) Sector = (Cluster - 2) * (UINT32)Vol->VolumeBPB.BPB_SecPerClus + Offset;
    
    else Sector = Offset;
    
    return Sector;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   SectorToCluster
//
// Description: Converts an absolute sector number (relative to the beginning
//              of a volume) to a cluster number, and the sector within that
//              cluster.
//
// Parameters:
//  IN VOLUME_INFO      *Vol,         The volume structure
//  OUT UINTN           Sector        The sector to be converted
//
// Return value:
//  Sector - The sector offset in the returned cluster.
//  Returns the sector number.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
SectorToCluster (
    IN VOLUME_INFO *Vol,
    IN OUT UINT32  Sector
)
{
    UINT32 Temp1;
    UINT32 Temp2;
    
    // Calculate offset to 1st data sector
    Temp1 = Vol->VolumeBPB.BPB_RsvdSecCnt + Vol->FATSz * Vol->VolumeBPB.BPB_NumFATs +
            Vol->RootDirSectorCount;
    Temp2 = Sector - Temp1; // "Normalize" the sector
    Temp1 = Temp2 / (UINT32)Vol->VolumeBPB.BPB_SecPerClus; // Calculate the cluster number
    Sector = Temp2 % (UINT32)Vol->VolumeBPB.BPB_SecPerClus; // Get sector within cluster
    return Temp1 + 2; // Account for first cluster being no. 2
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetClusterCount
//
// Description: Gets the cluster count of a file (usually a directory,
//              because Dir_FileSize is zero for these, and we need to
//              know the file size).
//
// Parameters:
//  IN VOLUME_INFO      *Vol,         The volume structure
//  IN OUT UINT32       Cluster       In - the first cluster. Out - count
//
// Return value:
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetClusterCount (
    IN VOLUME_INFO *Vol,
    IN OUT UINT32  Cluster
)
{
    UINT32 Count = 0;
    UINT32 TempCluster = 0;
    
    // If the first cluster is EOC, return a count of 0.
    if (Cluster >= Vol->EOCMark) {
        Cluster = Count;
        return EFI_SUCCESS;
    }
    
    // Follow the chain and count the clusters until EOC.
    do {
        ReadFatClusterNumber(Vol, Cluster, 0, &TempCluster);
        
        if (TempCluster < 2) {
            MarkVolumeDirty (Vol);
            return EFI_VOLUME_CORRUPTED;
        }
        
        Count++;
        Cluster = TempCluster;
    } while (Cluster < Vol->EOCMark);
    
    // Return the count in Cluster.
    Cluster = Count;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetClustersRequired
//
// Description: Gets the amount of clusters required to store N blocks.
//
// Parameters:
//  IN VOLUME_INFO      *Vol,   The volume structure
//  IN UINT32           N       A byte count
//
// Return value:
//  Returns the required clusters.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
GetClustersRequired (
    IN VOLUME_INFO *Vol,
    IN UINT32      N
)
{
    return (N + Vol->BytesPerCluster - 1) / (Vol->BytesPerCluster);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetContiguousClusters
//
// Description: Gets the nunber of contiguous clusters starting from the
//              specified cluster
//
// Parameters:
//  IN VOLUME_INFO      *Vol,   The volume structure
//  IN OUT UINT32       Cluster The cluster to start with
//
// Return value:
//  Returns the number of contiguous clusters in Cluster.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetContiguousClusters (
    IN VOLUME_INFO *Vol,
    IN UINT32      Size,
    IN UINT32      Cluster,
    OUT UINT32     *NextCluster,
    OUT UINT32     *Count
)
{
    EFI_STATUS Status;
    UINT32     TotalBytes;
    
    if (Cluster == Vol->EOCMark) {
        *Count = 0;
        return EFI_SUCCESS;
    }
    
    *Count = 1;
    
    TotalBytes = Vol->BytesPerCluster;
    
    do {
        Status = ReadFatClusterNumber(Vol, Cluster, 0, NextCluster);
        
        if (EFI_ERROR(Status)) return Status;
        
        if (TotalBytes >= Size) break;
        
        if (*NextCluster >= Vol->EOCMark) break;
        
        if (*NextCluster < 2) {
            MarkVolumeDirty (Vol);
            return EFI_VOLUME_CORRUPTED;
        }
        
        if (*NextCluster == (Cluster + 1)) {
            ++*Count;
            TotalBytes += Vol->BytesPerCluster;
            Cluster = *NextCluster;
        }
    } while (Cluster == *NextCluster);
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetClusterPosition
//
// Description: Gets the nunber of contiguous clusters starting from the
//              specified cluster
//
// Parameters:
//  IN VOLUME_INFO      *Vol,   The volume structure
//  IN OUT UINT32       Cluster The cluster to start with
//
// Return value:
//  Returns the number of contiguous clusters in Cluster.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetClusterPosition (
    IN FILE_HANDLE_INSTANCE *File,
    IN UINT64               Position,
    OUT UINT32              *Cluster,
    OUT UINT32              *ClusterOffset
)
{
    EFI_STATUS  Status;
    VOLUME_INFO *Vol = File->pFH->VolumeInterface;
    UINT32      ClusterCount;
    UINT32      TempCluster, NextCluster;
    UINT32      i;
    
    
    NextCluster = TempCluster = FIRSTCLUSTER(File->pFH->DirectoryEntry);
// Get the count of clusters that Position is from the beginning of the file.
    ClusterCount = (UINT32)Position / Vol->BytesPerCluster;
    *Cluster = 0;
    *ClusterOffset = 0;
    
    if (TempCluster) {
        for (i=0; i<ClusterCount; i++, TempCluster = NextCluster) {
            Status = ReadFatClusterNumber(Vol, TempCluster, 0, &NextCluster);
            
            if (EFI_ERROR(Status)) return Status;
            
            if (NextCluster >= Vol->EOCMark) break;
        }
        
//      Is the Position is set to EOF, then cluster will be the last valid
//      cluster and offset set to Vol->BytesPerCluster
//      else Cluster and cluster offset will be a valid pointer to the
//      Position
        *Cluster = NextCluster;
        *ClusterOffset = (UINT32)Position % Vol->BytesPerCluster;
        
        if (!*ClusterOffset) {
            if (NextCluster >= Vol->EOCMark) {
                File->CurrentCluster = TempCluster;
                File->CurrentClusterOffset = Vol->BytesPerCluster;
            }
        }
    }
    
//TODO TODO
//  Should be removed later
//  if (*Cluster >= Vol->EOCMark) {
//      _asm jmp $
//  }
//TODO TODO

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetAbsSectorInfo
//
// Description: Gets the nunber of contiguous clusters starting from the
//              specified cluster
//
// Parameters:
//  IN VOLUME_INFO      *Vol,   The volume structure
//  IN OUT UINT32       Cluster The cluster to start with
//
// Return value:
//  Returns the number of contiguous clusters in Cluster.
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
GetAbsSectorInfo (
    IN VOLUME_INFO *Vol,
    IN UINT32      Cluster,
    IN UINT32      ClusterOffset,
    OUT UINT32     *Sector,
    OUT UINT32     *SectorOffset
)
{
    *Sector = ClusterToSector(Vol, Cluster) + (ClusterOffset / (UINT32)Vol->VolumeBPB.BPB_BytePerSec);
    *SectorOffset = ClusterOffset % (UINT32)Vol->VolumeBPB.BPB_BytePerSec;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ShrinkClusters
//
// Description: Reduces the number of clusters used by a file
//              (part of it deleted).
//
// Parameters:
//  IN VOLUME_INFO      *Vol,
//  IN UINT32           StartCluster,
//  IN UINT32           ClusterCount
//
// Return value: EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//  ClusterCount :  Total number of Final clusters starting from StartCluster
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ShrinkClusters (
    IN VOLUME_INFO *Vol,
    IN UINT32      StartCluster,
    IN UINT32      ClusterCount
)
{
    EFI_STATUS Status;
    UINT32     LastCluster, NextCluster = StartCluster;
    UINT32     i;
    
//  Get to the particular Cluster#
    for ( i = 0; i < ClusterCount;  i++, StartCluster = NextCluster) {
        LastCluster = StartCluster;
        Status = ReadFatClusterNumber (Vol, StartCluster, 0, &NextCluster);
        
        if (EFI_ERROR(Status)) return Status;
    }
    
//      Truncate it
    if (ClusterCount) {
        for (i = 0; i < Vol->VolumeBPB.BPB_NumFATs; i++) {
            Status = WriteFatClusterNumber(Vol, LastCluster, i, Vol->EOCMark);
            
            if (EFI_ERROR(Status)) return Status;
        }
    }
    
//  Free Up the remaining
    Status = UnlinkFat (Vol, NextCluster, &ClusterCount); // Unlink From this Cluster
    return Status;
    
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetFreeClusterCount
//
// Description: Gets the count of free clusters on a disk.
//
// Parameters:
//  IN VOLUME_INFO      *Vol,               The volume structure
//  OUT UINT32          *FreeClusters       Free clusters on volume
//  OUT UINT32          *FreeClusterBlock   First cluster in a block of free clusters
//  OUT UINT32          *FreeBlockCount     Number of clusters in the free block.
//
// Return value:
//  EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetFreeClusterCount (
    IN VOLUME_INFO *Vol,
    OUT UINT32     *FreeClustersCount,
    OUT UINT32     *FreeClusterBlock,
    OUT UINT32     *FreeBlockCount
)
{
    EFI_STATUS Status;
    UINT32     Count = 0;
    UINT32     FreeCount = 1;
    UINT32     LastFree = 2;
    UINT32     FreeBlock = 0;
    UINT32     PrevFreeCount = 0, PrevFreeBlock;
    UINT32     i,j;
    UINT32     Value;
    UINT8      *Buffer;
    UINT32     BufferSize;
    UINT32     BufferOffset = 0;
    UINT32     FatSize;
    UINT32     FatOffset;
    UINT32     CountSize, CompareSize;
    UINT32     TotalClusters;
    UINT32     Sector;
    
//  Read in a maximum of 1 megabyte of the fat at a time for this calcuation
    FatSize = Vol->FATSz * (UINT32)Vol->VolumeBPB.BPB_BytePerSec;
    
    if (FatSize > 0xfffff) BufferSize = 0x100000;
    
    else BufferSize = FatSize;
    
    Status = fsAllocateMemory (Vol, BufferSize, &Buffer, FALSE);
    
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;
    
    TotalClusters = Vol->CountOfDataClusters;
    j = i = 2;          // For the first round start from Cluster 2
    
    while (TotalClusters) {
    
//      Sector = Vol->FATSz + Vol->VolumeBPB.BPB_RsvdSecCnt + BufferOffset / (UINT32)Vol->VolumeBPB.BPB_BytePerSec;
        Sector = Vol->VolumeBPB.BPB_RsvdSecCnt + BufferOffset / (UINT32)Vol->VolumeBPB.BPB_BytePerSec;
        Status = FsReadMedia (Vol,
                              (UINT8 *)Buffer,
                              (UINT64)Sector,
                              0,
                              BufferSize,
                              DATA_REGION);
                              
        if (    EFI_ERROR(Status)) goto GetFreeClusterCount_Error;
        
//      FAT12 or FAT16 will never have FAT size larger than 1MB
//      if (Vol->FatType != FAT32) CountSize = BufferSize/2; else CountSize = BufferSize/4;
        if (BufferSize == FatSize) {
            CountSize = TotalClusters;
            
        } else {
            CountSize = BufferSize / 4;  // We could only have CountSize exceeding TotalClusters if FAT32
        }
        
//      if (CountSize > TotalClusters) CountSize = TotalClusters;
        if (i == 2) CompareSize = CountSize + 2;
        
        else CompareSize = CountSize;
        
        for (; i < CompareSize; i++, j++) {
//          Status = ReadFatClusterNumber(Vol, i, 0, &Value);
            switch (Vol->FatType) {
                case FAT12:
                    FatOffset = i + (i / 2);
                    (UINT16)Value = *(UINT16 *)((UINT8 *)Buffer + FatOffset);
                    
                    if (i & 0x0001) Value >>= 4;
                    
                    else Value &= 0x0fff;
                    
                    break;
                case FAT16:
                    FatOffset = i * 2;
                    (UINT16)Value = *(UINT16 *)((UINT8 *)Buffer + FatOffset);
                    Value &= 0x0ffff;
                    break;
                case FAT32:
                    FatOffset = i * 4;
                    Value = *(UINT32 *)((UINT8 *)Buffer + FatOffset);
                    Value &= 0x0fffffff;       // FAT32 actually uses 28 bits
                    break;
                default:
                    Status = EFI_UNSUPPORTED;
                    break;
            }
            
            if (EFI_ERROR(Status)) goto GetFreeClusterCount_Error;
            
            if (Value == 0) {
                Count++;
                
                if (j != (LastFree + 1)) {
                    if (FreeCount > PrevFreeCount) {  // in case the last free block found is not the largest.
                        PrevFreeBlock = FreeBlock;
                        PrevFreeCount = FreeCount;
                    }
                    
                    FreeBlock = j; // Reset free block if not contiguous
                    FreeCount = 0; // Restart free count
                }
                
                LastFree = j;
                FreeCount++;
            }
        }
        
        BufferOffset += BufferSize;
        FatSize -= BufferSize;
        
        if (FatSize > 0xfffff) BufferSize = 0x100000;
        
        else BufferSize = FatSize;
        
//      Check for last group of clusters.
        if (TotalClusters >= CountSize) {
            TotalClusters -= CountSize;
            
        } else {
            CountSize = TotalClusters;  // Adjust count size and buffer size if in last cluster group
            BufferSize = TotalClusters * 4;
        }
        
// It's possible that the original Total Cluster count could have been incorrect.
// Check that here.
        if (TotalClusters && (BufferSize > FatSize)) {
            TRACE((TRACE_ALWAYS, "TotalClusters was incorrect -- fixing it.\n"));
            BufferSize = FatSize;
            CountSize = TotalClusters = (BufferSize / 4);
            TRACE((TRACE_ALWAYS, "Buffer adjusted to 0x%X bytes\n", BufferSize));
        }
        
        i = 0;          // From Second round, start from Cluster 0
    }
    
    fsDeAllocateMemory (Vol, Buffer);
    
    if (Count) {
        *FreeClustersCount = Count;
        
        if (FreeCount > PrevFreeCount) {  // in case the last free block is not the largest.
            *FreeClusterBlock = FreeBlock;
            *FreeBlockCount = FreeCount;
            
        } else {
            *FreeClusterBlock = PrevFreeBlock;
            *FreeBlockCount = PrevFreeCount;
        }
        
        return EFI_SUCCESS;
        
    } else return EFI_NOT_FOUND;
    
GetFreeClusterCount_Error:
    fsDeAllocateMemory (Vol, Buffer);
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ReturnFreeSpace
//
// Description: Returns the amount of free space (in clusters) on a volume
//
// Parameters:
//  IN VOLUME_INFO      *vi - Volume info structure
//
// Return value:  UINT32 - free space in clusters
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32
ReturnFreeSpace (
    IN VOLUME_INFO *vi
)
{

    UINT32 FreeClusterCount, StartFreeClusterBlock, nClusterBlocks;
    
    if (vi->FreeSpaceinClusters != -1 && vi->LastFreeCluster != -1) return vi->FreeSpaceinClusters;
    
    GetFreeClusterCount(vi, &FreeClusterCount, &StartFreeClusterBlock, &nClusterBlocks);
    
    if (FreeClusterCount > vi->CountOfDataClusters) FreeClusterCount = 0;
    
    vi->FreeSpaceinClusters = FreeClusterCount;
    vi->LastFreeCluster = StartFreeClusterBlock;
    vi->FreeClusterBlocks = nClusterBlocks;
    return vi->FreeSpaceinClusters;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   UpdateFreeSpace
//
// Description: Updates the volume info free space in clusters
//
// Parameters:
//  IN VOLUME_INFO      *vi - Volume info structure
//
// Return value: EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateFreeSpace (
    IN VOLUME_INFO *vi,
    IN UINT32      Count,
    IN BOOLEAN     Add
)
{

    UINT32 FreeClusters = vi->FreeSpaceinClusters;
    
    if (vi->FreeSpaceinClusters == -1 ) FreeClusters = ReturnFreeSpace (vi);
    
    if (Add) vi->FreeSpaceinClusters += Count;
    
    else if (FreeClusters) vi->FreeSpaceinClusters -= Count;
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   MarkVolumeDirty
//
// Description: Marks a volume as dirty so that the OS will know to fix it.
//
// Parameters:
//  IN VOLUME_INFO      *vi - Volume info structure
//
// Return value:
//
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
MarkVolumeDirty (
    IN VOLUME_INFO *vi
)
{
    EFI_STATUS Status;
    UINT32     Temp;
    
    Status = ReadFatClusterNumber (vi, 1, 0, &Temp);
    
    if (EFI_ERROR(Status)) return Status;
    
    switch (vi->FatType) {
        case FAT12:
            return EFI_SUCCESS;     // Not supported in FAT21 -- ignore.
        case FAT16: {
                Temp &= ~0x8000;    // Set dirty bit in FAT header.
                break;
            }
        case FAT32: {
                Temp &= ~0x08000000;
                break;
            }
        default:
            return EFI_SUCCESS;
    }
    
    Status = WriteFatClusterNumber (vi, 1, 0, Temp);
    
    if (EFI_ERROR(Status)) return Status;
    
// We don't have to write the 2nd fat, since the volume is dirty anyway, and
// Windows or DOS will fix it. This saves a little code.
//  Status = WriteFatClusterNumber (vi, 1, 1, Temp);
//  if (EFI_ERROR(Status)) return Status;
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
