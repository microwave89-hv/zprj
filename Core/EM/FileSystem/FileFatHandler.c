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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/FileSystem/FileFatHandler.c 1     10/25/12 8:53a Wesleychen $
//
// $Revision: 1 $
//
// $Date: 10/25/12 8:53a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/FileSystem/FileFatHandler.c $
// 
// 1     10/25/12 8:53a Wesleychen
// Update it for EIP#104620.
// 
// 7     10/05/12 5:50p Pats
// [TAG] EIP99324
// [Category] Bug Fix
// [Symptom] Image files used in GUI Version of AMIDiag getting renamed
// [RootCause] If the long name component of a directory was in a separate
// cluster from the short name component, it was being over-written.
// [Solution] Added new function FindLongNamePiece() to FileFatHandler.c.
// It is called from GetSpaceforDirEntry().
// [Files] FileFatHandler.c
// 
// 6     6/11/10 5:40p Pats
// EIP 39171: Long name sometimes not displayed, only short name.
// FetchLongName() in Open.c did not handle case where long name spilt
// over 2 clusters. Function modified to handle the case.
// Call to FetchLongName() changed here because parameters changed.
// 
// 5     7/02/09 5:47p Pats
// Updated to latest coding standard. No code changes.
//
// 4     4/13/07 7:07p Pats
// Edited to conform with coding standards. No code changes.
//
// 3     6/21/05 4:00p Pats
// Modified to call MarkVolumeDirty when EFI_VOLUME_CORRUPTED error
// occurs. Removed commented-out debug code.
//
// 2     6/16/05 4:14p Pats
// Modified to return error if reading file with premature EOF in fat
// chain.
//
// 1     4/26/05 6:05p Srinin
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:    FileFatHndlr.c
//
// Description: Fat File System driver -- File Level Fat Handler
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#include "FileSystem.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       LocateFreeDirEntry
//
// Description:     Locates a free entry in a directory
//
// Parameters:      FILE_HANDLE *fh - Handle of file requireing entry
//                  UINT32 FreeBytesRequired - No. of bytes required for
//                                             the new entry
//                  UINT32 *FreeDirCluster - Returned Cluster of free entry
//                  UINT32 *FreeDirClusterOffset - Offset of free entry
//
// Returned value:  EFI_STATUS - Status of the operation
//
// Modified:        None
//
// Referral(s):     None
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LocateFreeDirEntry(
    IN FILE_HANDLE *fh,
    IN UINT32      FreeBytesRequired,
    OUT UINT32     *FreeDirCluster,
    OUT UINT32     *FreeDirClusterOffset,
    OUT BOOLEAN    *LastDirEntry
)
{

    EFI_STATUS  Status;
    VOLUME_INFO *Vi = fh->VolumeInterface;
    
    //  If free Dir Entry not found earlier, use the long method
    if (fh->FreeDirEntryCluster == 0 && fh->FreeDirEntryOffset == 0)
        return GetSpaceforDirEntry(fh, FreeBytesRequired, FreeDirCluster, FreeDirClusterOffset, LastDirEntry);
        
    //  Use the existing data to speed up the search
    Status =   CheckforValidDirSpace (Vi, fh->ROOTDIR, fh->FreeDirEntryCluster, fh->FreeDirEntryOffset,
                                      FreeBytesRequired, FreeDirCluster, FreeDirClusterOffset);
                                      
    if (Status == EFI_SUCCESS) *LastDirEntry = TRUE;
    
    //  Above Routine failed. For FAT12/16, limited ROOT directory entries are
    //  available. So go through the entire list.
    if (EFI_ERROR(Status) && fh->ROOTDIR && (Vi->FatType != FAT32))
        return GetSpaceforDirEntry(fh, FreeBytesRequired, FreeDirCluster, FreeDirClusterOffset, LastDirEntry);
        
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FindLongNamePiece
//
// Description: Returns TRUE if there is a valid long name part of a
//              directory entry at Offset position in Buffer.
//
// Parameters:
//    UINT8       *Buffer - Buffer to search in
//    UINT32      *Offset - Offset in buffer where entry found
//
// Return Value:
//  BOOLEAN - True = Long name piece found
//
// Modified:
//
// Referrals: GetSpaceforDirEntry
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
FindLongNamePiece (
    UINT8  *Buffer,
    UINT32 *Offset
)
{
    DIR_ENTRY_32 *Entry  = (DIR_ENTRY_32 *)(Buffer + *Offset);

    if ((Entry->Dir_Name[0] == 0) || (Entry->Dir_Name[0] == 0xE5)) {
        return FALSE; // not an existing entry.
    }

    if ( ((Entry->Dir_Attr & ATTR_LONG_NAME_MASK) == (ATTR_LONG_NAME)) &&
            ((Entry->Dir_Name[0] >> 4) == 0) ||
            ((Entry->Dir_Name[0] >> 4) >= 4) ) {

        return TRUE;
    }

    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetSpaceforDirEntry
//
// Description:     Enlarges directory to make space for a new entry
//
// Parameters:      FILE_HANDLE *fh - Handle of file requireing entry
//                  UINT32 FreeBytesRequired - No. of bytes required for
//                                             the new entry
//                  UINT32 *FreeDirCluster - Returned Cluster of free entry
//                  UINT32 *FreeDirClusterOffset - Offset of free entry
//                  BOOLEAN *LastDirEntry - True if new entry is the last one
//                                          in the directory
//
// Return Value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referrals:
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetSpaceforDirEntry(
    IN FILE_HANDLE *fh,
    IN UINT32      FreeBytesRequired,
    OUT UINT32     *FreeDirCluster,
    OUT UINT32     *FreeDirClusterOffset,
    BOOLEAN        *LastDirEntry
)
{

    EFI_STATUS  Status;
    UINT32      Offset, BufferSize, OrgBufferSize;
    UINT32      BytesReadPerLoop;
    UINT8       *Buffer;
    VOLUME_INFO *Vi = fh->VolumeInterface;
    UINT32      ClusterNumber, Cluster, LastValidCluster;
    UINT32      CurrentOffset, Slots;
    UINT16      lfn[256];
    
    
    // Allocate space for a temp buffer.
    BytesReadPerLoop = Vi->BytesPerCluster;
    
    if (fh->ROOTDIR && (Vi->FatType != FAT32))
        BytesReadPerLoop = Vi->RootDirSectorCount << Vi->BytesPerSecPowerof2;
        
        
    GetTempBuffer (Vi, &Buffer);
//###DEBUG
//  Status = fsAllocateMemory (Vi, BytesReadPerLoop, &Buffer, FALSE);
//  Status = fsAllocateMemory (Vi,  256, (VOID**)&lfn, FALSE);
//    if(EFI_ERROR(Status)) return EFI_NOT_FOUND;
//###DEBUG END
    LastValidCluster = FIRSTCLUSTER(fh->DirectoryEntry);
    
    for (ClusterNumber = 0; ClusterNumber < Vi->CountOfDataClusters ; ClusterNumber++) {
        Cluster = 0;
        Status = ReadClusterOfDirectoryEntries(fh, ClusterNumber, &Cluster, Buffer, &BytesReadPerLoop);
        
        if (EFI_ERROR(Status)) return Status;
        
        if (Status == EFI_SUCCESS && BytesReadPerLoop == 0) {
        
            if (fh->ROOTDIR && (Vi->FatType != FAT32)) return EFI_ACCESS_DENIED; // Dir. entry cannot be created
            
//###DEBUG
            /*
             #ifdef Debug_AllocateClusters
                EfiDebugPrint(-1,"DirName %s Clusters ", fh->FileNameLFN);
             #endif
                        Status = AllocateAndLinkClusters (Vi, LastValidCluster, Vi->BytesPerCluster, &Cluster, &ClusterCount);
             #ifdef Debug_AllocateClusters
                EfiDebugPrint(-1,"\n");
             #endif
             *FreeDirClusterOffset = 0;
             *FreeDirCluster = Cluster;
            
               //           Zero out the New cluster allocated.
                        Status = ZeroOutdisk(Vi, Cluster, *FreeDirClusterOffset, Vi->BytesPerCluster);
             */
//###DEBUG END
            Status =     CheckforValidDirSpace (Vi, fh->ROOTDIR, LastValidCluster, Vi->BytesPerCluster,
                                                FreeBytesRequired, FreeDirCluster, FreeDirClusterOffset);
            *LastDirEntry = TRUE;
            break;
        }
        
        LastValidCluster = Cluster;
        OrgBufferSize = BytesReadPerLoop;
        BufferSize = BytesReadPerLoop;
        CurrentOffset = Offset = 0;
        *FreeDirCluster = Cluster;
        Status = EFI_NOT_FOUND;
        
        for ( ; CurrentOffset < OrgBufferSize; Offset = CurrentOffset, BufferSize = OrgBufferSize - CurrentOffset) {
        
            if (Buffer[Offset] == 0) {
                Status = CheckforValidDirSpace (Vi, fh->ROOTDIR, Cluster, Offset,
                                                FreeBytesRequired, FreeDirCluster, FreeDirClusterOffset);
                *LastDirEntry = TRUE;
                break;
            }
            
            
            if (FindShortName (Buffer, &Offset, BufferSize)) {
                Slots = FetchLongName(fh, (DIR_ENTRY_32 *)(Buffer), Offset, lfn, ClusterNumber, BytesReadPerLoop);
                
                if (Offset && ((Offset - Slots * sizeof(DIR_ENTRY_32) - CurrentOffset) >= FreeBytesRequired)) {
                    *FreeDirClusterOffset = CurrentOffset;
                    *LastDirEntry = FALSE;
                    Status = EFI_SUCCESS;
                    break;
                }
                
                CurrentOffset = Offset + sizeof(DIR_ENTRY_32);
                continue;
                
            } else {

                if (BufferSize > 0) {
                    while (FindLongNamePiece (Buffer, &CurrentOffset)) {
                        CurrentOffset += sizeof(DIR_ENTRY_32);
                        BufferSize -= sizeof(DIR_ENTRY_32);
                        if (BufferSize == 0) break;
                    }
                }

                if (BufferSize >= FreeBytesRequired) {
                    *FreeDirClusterOffset = CurrentOffset;
                    *LastDirEntry = FALSE;
                    Status = EFI_SUCCESS;
                }
                
                break;
            }
        }
        
        if (Status == EFI_SUCCESS) break;
        
    }
    
//###DEBUG
//  fsDeAllocateMemory (Vi, Buffer);
//  fsDeAllocateMemory (Vi, lfn);
//###DEBUG END
    ReleaseTempBuffer (Vi);
    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CheckforValidDirSpace
//
// Description: Cluster and Offset should point after the last valid directory entry.
//
// Parameters:
//  IN VOLUME_INFO *Vi - Volume info structure
//  IN BOOLEAN     ROOTDIR - true if root directory
//  IN UINT32      Cluster - Starting cluster
//  IN UINT32      Offset - Offset in cluster
//  IN UINT32      FreeBytesRequired
//  IN UINT32      *FreeDirCluster
//  IN UINT32      *FreeDirClusterOffset
//
// Return Value: EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:   No Directory Entry Will be created which crosses CLUSTER BOUNDRY
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
CheckforValidDirSpace (
    IN VOLUME_INFO *Vi,
    IN BOOLEAN     ROOTDIR,
    IN UINT32      Cluster,
    IN UINT32      Offset,
    IN UINT32      FreeBytesRequired,
    IN UINT32      *FreeDirCluster,
    IN UINT32      *FreeDirClusterOffset
)
{

    EFI_STATUS Status = EFI_SUCCESS;
    UINT32     ByteToCompare = Vi->BytesPerCluster;
    UINT32     Sector, SectorOffset, ClusterCount;
    UINT8      BData;
    
    
    if (ROOTDIR && (Vi->FatType != FAT32)) ByteToCompare = Vi->RootDirSectorCount << Vi->BytesPerSecPowerof2;
    
    if (ByteToCompare - Offset >= FreeBytesRequired) {
//      Free Entry Found with in the cluster
        *FreeDirCluster = Cluster;
        *FreeDirClusterOffset = Offset;
        return Status;
    }
    
//  For ROOT and FAT12/16, new clusters cannot be added.
    if (ROOTDIR && (Vi->FatType != FAT32)) return EFI_ACCESS_DENIED;
    
//  From Cluster/offset to end of Cluster make sure there are no '0' in the first Byte Position of the directory Entry.
    for ( ; ByteToCompare - Offset; ) {
        GetAbsSectorInfo(Vi, Cluster, Offset, &Sector, &SectorOffset);
        Status = FsReadMedia (Vi, &BData, Sector, SectorOffset, 1, DIRECTORY_REGION);
        
        if (BData == 0) {
            BData = DIR_ENTRY_ERASE;
            Status = FsWriteMedia (Vi, &BData, Sector, SectorOffset, 1, DIRECTORY_REGION);
        }
        
        Offset += sizeof (DIR_ENTRY_32);
    }
    
#ifdef Debug_AllocateClusters
    EfiDebugPrint(-1,"Dir Name Not found");
#endif
//  Allocate a New Cluster
//  Status = AllocateAndLinkNewCluster (Vi, Cluster, FreeDirCluster);
    Status = AllocateAndLinkClusters (Vi, Cluster, Vi->BytesPerCluster, FreeDirCluster, &ClusterCount);
#ifdef Debug_AllocateClusters
    EfiDebugPrint(-1,"\n");
#endif
    *FreeDirClusterOffset = 0;
    
//  Zero out the New cluster allocated.
    Status = ZeroOutdisk(Vi, *FreeDirCluster, *FreeDirClusterOffset, Vi->BytesPerCluster);
    return Status;
    
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ZeroOutdisk
//
// Description: Zeros out directory region of disk
//
// Parameters:
//  IN VOLUME_INFO *Vi - Volume info structure
//  IN UINT32      Cluster - Cluster in directory region to zero
//  IN UINT32      ClusterOffset - Offset in cluster
//  IN UINT32      Size - Size to zero
//
// Return value: EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
ZeroOutdisk (
    IN VOLUME_INFO *Vi,
    IN UINT32      Cluster,
    IN UINT32      ClusterOffset,
    IN UINT32      Size
)
{
    UINT32     Sector, SectorOffset;
    UINT8      *Buffer;
    EFI_STATUS Status;
    
//  fsAllocateMemory (Vi, Size, (void **)&Buffer,  TRUE);
    GetTempBuffer (Vi, &Buffer);
    Zeromemory (Buffer, Size);
    GetAbsSectorInfo(Vi, Cluster, ClusterOffset, &Sector, &SectorOffset);
    Status = FsWriteMedia (Vi, Buffer, Sector, SectorOffset, Size, DIRECTORY_REGION);
//  fsDeAllocateMemory(Vi, Buffer);
    ReleaseTempBuffer (Vi);
    
    if (EFI_ERROR(Status)) {
        HandleDiskIoError (Vi, Status);
        return Status;
    }
    
    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ExtendFile
//
// Description: Extends a file on the disk (it is written to)
//
// Parameters:
//  IN FILE_HANDLE_INSTANCE *fhi - File handle instance
//  IN UINT32               Length - Length to extend
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
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
ExtendFile (
    IN FILE_HANDLE_INSTANCE *fhi,
    IN UINT32               Length
)
{

    UINT64      OrgPosition;
    FILE_HANDLE *fh = fhi->pFH;
    VOLUME_INFO *vi = fhi->pFH->VolumeInterface;
    EFI_STATUS  Status;
    UINT32      FirstCluster, NewClusterCount, RemainingClusterLength = 0;
    
#ifdef Debug_WriteFile
    EfiDebugPrint(-1,"File to be Extended by Length %x \n", Length);
#endif
    
//  Save the Current Position
    OrgPosition = fhi->Position;
    
//  Set the Position to the End of the File
    SetPositionFileHandle (fhi, -1);
    
//  Check if there is remaming space in the current cluster
    if (fhi->CurrentCluster)
        RemainingClusterLength = vi->BytesPerCluster - fhi->CurrentClusterOffset;
        
    if (Length > RemainingClusterLength) {
        Length = Length - RemainingClusterLength;
#ifdef Debug_AllocateClusters
        EfiDebugPrint(-1,"FileName %s Clusters ", fh->FileNameLFN);
#endif
        Status = AllocateAndLinkClusters(vi, fhi->CurrentCluster, Length, &FirstCluster, &NewClusterCount);
#ifdef Debug_AllocateClusters
        EfiDebugPrint(-1,"\n");
#endif
        
        if (EFI_ERROR(Status)) return Status;
    }
    
    if (fhi->CurrentCluster == 0 && fhi->CurrentClusterOffset == 0) {
        fh->DirectoryEntry.Dir_FstClusLO = (UINT16) FirstCluster;
        fh->DirectoryEntry.Dir_FstClusHI = FirstCluster >> 16;
    }
    
//  Restore File Position
    SetPositionFileHandle (fhi, OrgPosition);
    
    fh->DirectoryEntry.Dir_Attr |= ATTR_ARCHIVE;
    fh->DirEntryChanged = TRUE;
    return EFI_SUCCESS;
    
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ReadWriteExistingBlock
//
// Description: Reads or writes an existing file. If writing, writes
//              only an existing block, with no new allocation.
//
// Parameters:
//  IN FILE_HANDLE_INSTANCE *File - File handle instance
//  IN OUT VOID             *Buffer - Output biffer
//  IN OUT UINT32           *Size - Size written or read
//  IN REGIONS              DataRegion - Region of disk used (dir, fat, normal)
//  IN ACCESS_METHOD        Method - Method (read or write)
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
ReadWriteExistingBlock (
    IN FILE_HANDLE_INSTANCE *File,
    IN OUT VOID             *Buffer,
    IN OUT UINT32           *Size,
    IN REGIONS              DataRegion,
    IN ACCESS_METHOD        Method
)
{
    EFI_STATUS  Status;
    VOLUME_INFO *Vol = File->pFH->VolumeInterface;
    UINT32      TotalContigousBytes;
    UINT32      TotalBytesRead = 0;
    UINT32      NextCluster, ClusterCount, AbsSector, AbsSectorOffset, AccessBytes;
    UINT32      Position =  (UINT32) File->Position;
    
    do {
    
        Status = GetContiguousClusters(Vol, *Size + File->CurrentClusterOffset, File->CurrentCluster,
                                       &NextCluster, &ClusterCount); // CurrentSector and CurrentSectorOffset
                                       
        if (EFI_ERROR(Status)) break;
        
        if (!ClusterCount) break;
        
        TotalContigousBytes = (ClusterCount * (UINT32)Vol->VolumeBPB.BPB_SecPerClus) << Vol->BytesPerSecPowerof2;
        TotalContigousBytes -= File->CurrentClusterOffset;
        
        if ( TotalContigousBytes > *Size) AccessBytes = *Size;
        
        else AccessBytes = TotalContigousBytes;
        
        GetAbsSectorInfo (Vol, File->CurrentCluster, File->CurrentClusterOffset, &AbsSector, &AbsSectorOffset);
        
        if ((Method == READ_BLOCK) && (AccessBytes == 0)) {
            MarkVolumeDirty (Vol);
            return EFI_VOLUME_CORRUPTED; // Will happen if early EOF.
        }
        
        if (Method == READ_BLOCK) {
            Status = FsReadMedia (Vol,
                                  Buffer,
                                  AbsSector,
                                  AbsSectorOffset,
                                  AccessBytes,
                                  DATA_REGION);
                                  
        } else {
            Status = FsWriteMedia (Vol,
                                   Buffer,
                                   AbsSector,
                                   AbsSectorOffset,
                                   AccessBytes,
                                   DATA_REGION);
        }
        
        if (EFI_ERROR(Status)) {
            break;
        }
        
        (UINT8 *)Buffer += AccessBytes;
        TotalBytesRead +=AccessBytes;
        *Size   -= AccessBytes;
        Position += AccessBytes;
        File->Position = Position;
//###DEBUG
//TODO TODO TODO TODO
//Can call getpositionfilehandle to save some space.
//TODO TODO TODO TODO
//###DEBUG END
        File->CurrentCluster += ((AccessBytes + File->CurrentClusterOffset) / Vol->BytesPerCluster);
        File->CurrentClusterOffset = (AccessBytes + File->CurrentClusterOffset) % Vol->BytesPerCluster;
        
        if (!File->CurrentClusterOffset) {
            if (NextCluster >= Vol->EOCMark) {
                File->CurrentCluster--;
                File->CurrentClusterOffset = Vol->BytesPerCluster;
                
            } else File->CurrentCluster = NextCluster;
        }
    } while (*Size);
    
    *Size = TotalBytesRead;
    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ReadFromFile
//
// Description: Reads a specified number of bytes from a file into a
//              specified buffer, beginning at a specified position
//              in the file. Updates Size to number of bytes read.
//              Updates Position to position after data read.
//
// Parameters:
//  IN FILE_HANDLE_INSTANCE *File - File handle instance
//  IN OUT VOID             *Buffer - Buffer to read into
//  IN OUT UINT32           *Size - Size to read (updated with size read)
//  IN REGIONS              DataRegion - Region of disk (dir, fat, normal)
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
ReadFromFile (
    IN FILE_HANDLE_INSTANCE *File,
    IN OUT VOID             *Buffer,
    IN OUT UINT32           *Size,
    IN REGIONS              DataRegion
)
{
    EFI_STATUS    Status;
    UINT32        Position =  (UINT32) File->Position;
    ACCESS_METHOD Method = READ_BLOCK;
    
    
//  If Position (Zero Based) beyond EOF?
    if (Position >= File->pFH->DirectoryEntry.Dir_FileSize) {
        *Size = 0;
        
        if (Position == File->pFH->DirectoryEntry.Dir_FileSize)
            return EFI_SUCCESS;
            
        else
            return EFI_DEVICE_ERROR;
    }
    
//  If bytes to be read exceed the file size, truncate it.
    if ((Position + *Size) > File->pFH->DirectoryEntry.Dir_FileSize) *Size = File->pFH->DirectoryEntry.Dir_FileSize - Position;
    
    Status =     ReadWriteExistingBlock (File,
                                         Buffer,
                                         Size,
                                         DataRegion,
                                         Method);
    return Status;
    
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   WriteToFile
//
// Description: Writes a specified number of bytes to a file from a
//              specified buffer, beginning at a specified position
//              in the file. Updates Size to number of bytes written.
//              Updates Position to position after data written.
//
// Parameters:
//  IN FILE_HANDLE_INSTANCE *File - File handle instance
//  IN OUT VOID             *Buffer - Buffer to write from
//  IN OUT UINT32           *Size - Size to write (updated with written)
//  IN REGIONS              DataRegion - Data region (dir, fat, normal)
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
WriteToFile (
    IN FILE_HANDLE_INSTANCE *File,
    IN OUT VOID             *Buffer,
    IN OUT UINT32           *Size,
    IN REGIONS              DataRegion
)
{
    EFI_STATUS    Status;
    VOLUME_INFO   *Vol = File->pFH->VolumeInterface;
    UINT32        Position =  (UINT32) File->Position;
    ACCESS_METHOD Method = WRITE_BLOCK;
    UINT32        TempSize, RemainingBytes;
    
    if (File->pFH->DirectoryEntry.Dir_Attr & ATTR_READ_ONLY) return EFI_ACCESS_DENIED;
    
    if ((Position + *Size) <= File->pFH->DirectoryEntry.Dir_FileSize) {
// First case -- Writing to existing portion of file (over-writing existing file).
        Status = ReadWriteExistingBlock(File, Buffer, Size, DataRegion, Method);
        
        if (     EFI_ERROR(Status)) return Status; // Or other error processing
        
#ifdef Debug_WriteFile
        EfiDebugPrint(-1,"WriteToFile: Position %lx Length %x \n", File->Position, *Size);
#endif
        
    } else if (File->pFH->DirectoryEntry.Dir_FileSize == 0) {
// Second case -- Writing to new unallocated space.
        Status = ExtendFile (File, *Size);
        
        if (EFI_ERROR(Status)) return Status; // Or other error processing
        
        File->pFH->DirectoryEntry.Dir_FileSize = *Size;
        Status = ReadWriteExistingBlock(File, Buffer, Size, DataRegion, Method);
        
        if (EFI_ERROR(Status)) return Status; // Or other error processing
        
#ifdef Debug_WriteFile
        EfiDebugPrint(-1,"WriteToFile: Position %lx Length %x \n", File->Position, *Size);
#endif
        
    } else {
// Third case -- Overwriting existing file, and extending it to unallocated space.
        RemainingBytes = *Size;
        
        if (Position < File->pFH->DirectoryEntry.Dir_FileSize) {
            TempSize = File->pFH->DirectoryEntry.Dir_FileSize - Position;
            Status = ReadWriteExistingBlock(File, Buffer, &TempSize, DataRegion, Method);
            
            if (EFI_ERROR(Status)) return Status; // Or other error processing
            
#ifdef Debug_WriteFile
            EfiDebugPrint(-1,"WriteToFile: Position %lx Length %x \n", File->Position, TempSize);
#endif
            Position = (UINT32) File->Position;
            RemainingBytes = *Size - TempSize;
        }
        
//  TODO TODO TODO TODO
//  if Position is greater than FileSize, the extended buffer should be zerod out
//  TODO TODO TODO TODO
//      Extend the File
        if (RemainingBytes) {
            TempSize = Position - File->pFH->DirectoryEntry.Dir_FileSize + RemainingBytes;
            Status = ExtendFile (File, TempSize);
            
            if (EFI_ERROR(Status)) return Status; // Or other error processing
            
            File->pFH->DirectoryEntry.Dir_FileSize += TempSize;
            Status = ReadWriteExistingBlock(File, Buffer, &RemainingBytes, DataRegion, Method);
            
            if (EFI_ERROR(Status)) return Status; // Or other error processing
            
#ifdef Debug_WriteFile
            EfiDebugPrint(-1,"WriteToFile: Position %lx FileSize %x \n",
                          File->Position, File->pFH->DirectoryEntry.Dir_FileSize);
#endif
                          
        }
    }
    
    return EFI_SUCCESS;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CheckFileWrite
//
// Description: Checks if file can be written to
//
// Parameters:
//  FILE_HANDLE_INSTANCE *fhi - File Handle instance
//  BOOLEAN              IgnoreOpenMode - If true, ignore mode file was
//                                         open with
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
CheckFileWrite (
    FILE_HANDLE_INSTANCE *fhi,
    BOOLEAN              IgnoreOpenMode
)
{

    FILE_HANDLE *Pfh = fhi->pFH;
    VOLUME_INFO *vi = Pfh->VolumeInterface;
    
    //  Check for Write Protect
    if (vi->ReadOnly || Pfh->DirectoryEntry.Dir_Attr & ATTR_READ_ONLY)
        return EFI_WRITE_PROTECTED;
        
    if (Pfh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY)
        return EFI_UNSUPPORTED;    // see sec 11-27 For Directory writes
        
    //  Check the attribute of the FILE. Is it opened in Readonly mode
    if (!IgnoreOpenMode)
        if (fhi->OpenMode == EFI_FILE_MODE_READ) return EFI_ACCESS_DENIED;
        
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
