//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/Modules/FileSystem/MediaAccess.c 11    10/24/11 10:55a Artems $
//
// $Revision: 11 $
//
// $Date: 10/24/11 10:55a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/FileSystem/MediaAccess.c $
// 
// 11    10/24/11 10:55a Artems
// EIP 73254: Remove "magic number" from source
// 
// 10    5/05/11 3:44p Pats
// [TAG] - EIP 58999 
// [Category]- BUG FIX
// [Severity]- Major
// [Symptom] - Cannot launch Shell from USB Filesystem device in Debug
// mode with latest Filesystem driver.
// [RootCause] - Functions using DISKIO were raising TPL to a fixed level.
// [Solution] - Modified above functions to check for the higher of the
// fixed level or current level.
// [Files] - Info.c, MediaAccess.c, Open.c, FileSystem.h
// 
// 9     1/06/11 5:55p Oleksiyy
// [TAG]  		EIP28607 
// [Category]  	Improvement
// [Description]  	System was hanging for some time if Floppy Media
// removed while writing in meda in progress.
// EFI_TPL_CALLBACK priority level rised during media related calls.
// 
// [Files]  		DiskIo.c, Info.c, MediaAccess.c, Open.c, Partition.c
// 
// 8     7/02/09 5:47p Pats
// Updated to latest coding standard. No code changes.
//
// 7     4/13/07 7:07p Pats
// Edited to conform with coding standards. No code changes.
//
// 6     8/25/06 12:10p Felixp
// Bug fix in GetNextCompName
//
// 5     8/25/06 12:06p Felixp
// Bug fix in GetNextCompName
//
// 5     11/03/05 2:17p Srinin
// Fixed VC7.1 warning msg.
//
// 4     7/06/05 11:25a Pats
// Modified function RemoveFH to delete child Dlist only if the parent is
// valid. Fixes problem of booting to floppy failing under certain
// conditions.
//
// 2     5/27/05 10:01a Srinin
// Fix for Media change and SCT long file name handling.
//
// 1     4/26/05 6:05p Srinin
//
//
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: MediaAccess.c
//
// Description:  Handles all Media access
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "FileSystem.h"
#define EFI_TPL_CALLBACK TPL_CALLBACK
//----------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       FsReadMedia
//
// Description:     Reads a specified no. of bytes from media at a specified
//                  location (abs. sector and offset in sector)
//
// Parameters:
//  VOLUME_INFO     *vi,            Pointer to Volume Info structure
//  UINT8           *Buffer,        Valid Buffer pointer should be Passed
//  UINT64          Sector,         Start Sector number
//  UINT32          Offset,         Offset within the sector to read  from
//  UINT32          ByteCount,      Number of bytes to read from the offset
//  REGIONS         DataRegion      See descriptions of REGION. Primarily
//                                  used to dtermine caching algorithm.
//typedef enum {
//  RESERVED_REGION,
//  FAT_REGION,
//  DIRECTORY_REGION,
//  DATA_REGION
//} REGIONS;
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FsReadMedia (
    VOLUME_INFO *vi,
    UINT8       *Buffer,
    UINT64      Sector,
    UINT32      Offset,
    UINT32      ByteCount,
    REGIONS     DataRegion
)
{

    EFI_STATUS   Status;
    UINT64       AbsoluteOffset;
    UINT8        *cBuffer;
    UINT32       cBufferLength;
    CACHE_HEADER *ch = NULL;
    
//  Convert Sector number to Absolute offset.
    AbsoluteOffset =        Shl64 (Sector, vi->BytesPerSecPowerof2) + Offset;
    
    if (DataRegion == DATA_REGION) {
        Status= vi->DiskIo->ReadDisk (vi->DiskIo, vi->MediaID, AbsoluteOffset, ByteCount, Buffer);
        
        if (EFI_ERROR(Status)) HandleDiskIoError(vi, Status);
        
        return Status;
    }
    
//  DATA_REGION is FAT or DIRECTORY
    for ( ; ByteCount; ) {
        Status = CheckCached(vi, AbsoluteOffset, ByteCount, &cBuffer, &cBufferLength, &ch, DataRegion);
        
        if (EFI_ERROR(Status)) {
            HandleDiskIoError(vi, Status);
            return Status;
        }
        
        pBS->CopyMem(Buffer, cBuffer, cBufferLength);
        ByteCount -= cBufferLength;
        Buffer += cBufferLength;
        AbsoluteOffset += cBufferLength;
    }
    
    return EFI_SUCCESS;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CheckCached
//
// Description:     Checks to see if the media data we're working with is
//                  cached
//
// Parameters:
//  VOLUME_INFO     *vi,                Pointer to volume info structure
//  UINT64          AbsoluteOffset,     Absolute offset of data
//  UINT32          ByteCount,          Byte Count of data
//  UINT8           **cBuffer,          Cache buffer
//  UINT32          *cBufferLength      Cache buffer length
//  CACHE_HEADER    **ch                Cache header stucture
//  REGIONS         DataRegion          See descriptions of REGION. Primarily
//                                      used to dtermine caching algorithm.
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CheckCached (
    VOLUME_INFO  *vi,
    UINT64       AbsoluteOffset,
    UINT32       ByteCount,
    UINT8        **cBuffer,
    UINT32       *cBufferLength,
    CACHE_HEADER **ch,
    REGIONS      DataRegion
)
{

    EFI_STATUS   Status;
    UINT32       Mask;
    UINT64       AlignedAbsoluteOffset;
    UINT32       AlignedBytecount;
    CACHE_HEADER *ch1 = NULL;
    
    if (!IsCacheHit(vi, DataRegion, AbsoluteOffset, ByteCount, cBuffer, cBufferLength, &ch1)) {
    
//      No match found for AbsoluteOffset
        Mask = 0x80000000;
        Mask -= vi->BytesPerCluster;
        Mask |= 0xf0000000;
        AlignedAbsoluteOffset = AbsoluteOffset;
        *(UINT32 *)&AlignedAbsoluteOffset = *(UINT32 *)&AbsoluteOffset & Mask;
        AlignedBytecount = vi->BytesPerCluster;
        
        CreateSpaceforCache (vi, AlignedBytecount, DataRegion, &ch1);
        Status= vi->DiskIo->ReadDisk (vi->DiskIo, vi->MediaID, AlignedAbsoluteOffset, AlignedBytecount, ch1->Buffer);
        
        if (EFI_ERROR(Status)) {
            HandleDiskIoError(vi, Status);
            return Status;
        }
        
        ch1->AbsoluteOffset = AlignedAbsoluteOffset;
        ch1->AbsoluteOffsetEnd = AlignedAbsoluteOffset + AlignedBytecount;
        ch1->DIRTY_FLAG = FALSE;
        ch1->DataRegion = DataRegion;
        DListDelete (&(vi->CacheList), &(ch1->CacheLink));
        DListAdd(&(vi->CacheList), &(ch1->CacheLink));
        
#ifdef Debug_Caching
        EfiDebugPrint(-1,"Caching Offset %lx End Offset %lx MemAddress %x\n", ch1->AbsoluteOffset, ch1->AbsoluteOffsetEnd, ch1->Buffer);
#endif
        
        if (!(IsCacheHit(vi, DataRegion, AbsoluteOffset, ByteCount, cBuffer, cBufferLength, &ch1))) {
            Status = EFI_DEVICE_ERROR;
            ASSERT_EFI_ERROR(Status); // something wrong in the algorithm
        }
    }
    
    *ch = ch1;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       IsCacheHit
//
// Description:
//
// Parameters:
//  VOLUME_INFO     *vi,                Pointer to volume info structure
//  UINT64          AbsoluteOffset,     Absolute offset of data
//  UINT32          ByteCount,          Byte Count of data
//  UINT8           **cBuffer,          Cache buffer
//  UINT32          *cBufferLength      Cache buffer length
//
// Return value:    BOOLEAN - True if cache hit
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
IsCacheHit (
    VOLUME_INFO  *vi,
    REGIONS      DataRegion,
    UINT64       AbsoluteOffset,
    UINT32       ByteCount,
    UINT8        **cBuffer,
    UINT32       *cBufferLength,
    CACHE_HEADER **ch1
)
{

    DLINK        *dlink = vi->CacheList.pTail;
    CACHE_HEADER *ch;
    
    for ( ; dlink; ) {
    
        ch = OUTTER(dlink, CacheLink, CACHE_HEADER);
        
        if (ch->DataRegion == DataRegion && AbsoluteOffset >= ch->AbsoluteOffset && AbsoluteOffset < ch->AbsoluteOffsetEnd) {
        
            *cBuffer = (UINT8 *)(ch->Buffer + (UINT32) (AbsoluteOffset - ch->AbsoluteOffset));
            *cBufferLength = (UINT32) (ch->AbsoluteOffsetEnd - AbsoluteOffset);
            
            if (*cBufferLength > ByteCount) *cBufferLength = ByteCount;
            
//          Important. Remove the link and add it to the end.
//          As least used data area will be moved to the front of the LIST
            DListDelete (&(vi->CacheList), &(ch->CacheLink));
            DListAdd(&(vi->CacheList), &(ch->CacheLink));
            *ch1 = ch;
            return TRUE;
        }
        
        dlink = dlink->pPrev;
        
    }
    
    return FALSE;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CreateSpaceforCache
//
// Description:     Creates space on media for cache
//
// Parameters:
//  VOLUME_INFO     *vi,            Volume info structure
//  UINT32          ByteCount,      Bytes of space to create
//  REGIONS         DataRegion      See descriptions of REGION. Primarily used
//                                  to dtermine caching algorithm.
//
// Return value:    None
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

void
CreateSpaceforCache (
    VOLUME_INFO  *vi,
    UINT32       ByteCount,
    REGIONS      DataRegion,
    CACHE_HEADER **ch1
)
{

    EFI_STATUS   Status;
    DLINK        *dlink = vi->CacheList.pHead;
    CACHE_HEADER *ch;
    
    for ( ; dlink; ) {
    
        ch = OUTTER(dlink, CacheLink, CACHE_HEADER);
        dlink = dlink->pNext;
        
        if (ch->DataRegion != DataRegion) continue;
        
        if (ch->DIRTY_FLAG) {
            Status= vi->DiskIo->WriteDisk (vi->DiskIo, vi->MediaID, ch->AbsoluteOffset, (UINT32) (ch->AbsoluteOffsetEnd - ch->AbsoluteOffset), ch->Buffer);
            
            if (EFI_ERROR(Status)) HandleDiskIoError(vi, Status);
            
            ch->DIRTY_FLAG = FALSE;
        }
        
        *ch1 = ch;
        break;
        
    }
    
    return;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       FsWriteMedia
//
// Description:     Writes a specified no. of bytes to media at a specified
//                  location (abs. sector and offset in sector)
//
// Parameters:
//  VOLUME_INFO     *vi,
//  UINT8           *Buffer,        Valid Buffer pointer should be Passed
//  UINT64          Sector,         Start Sector number
//  UINT32          Offset,         Offset within the sector to read from
//  UINT32          ByteCount,      Number of bytes to read from the offset
//  REGIONS         DataRegion      See descriptions of REGION. Primarily used
//                                  to dtermine caching algorithm.
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FsWriteMedia (
    VOLUME_INFO *vi,
    UINT8       *Buffer,
    UINT64      Sector,
    UINT32      Offset,
    UINT32      ByteCount,
    REGIONS     DataRegion
)
{

    EFI_STATUS   Status = EFI_SUCCESS;
    UINT64       AbsoluteOffset;
    UINT8        *cBuffer = NULL;
    UINT32       cBufferLength;
    CACHE_HEADER *ch = NULL;
    
//  Convert Sector number to Absolute offset.
    AbsoluteOffset = Shl64 (Sector, vi->BytesPerSecPowerof2) + Offset;
    
    if (DataRegion == DATA_REGION) {
        Status= vi->DiskIo->WriteDisk (vi->DiskIo, vi->MediaID, AbsoluteOffset, ByteCount, Buffer);
        
        if (EFI_ERROR(Status)) HandleDiskIoError(vi, Status);
        
        return Status;
    }
    
//###DEBUG
    /*
       //  Check for cache hit
        do {
            if (!IsCacheHit (vi, DataRegion, AbsoluteOffset, ByteCount, &cBuffer, &cBufferLength, &ch)) {
       //          Cache the region, before writing it
                for (AbsoluteOffset1 = AbsoluteOffset, ByteCount1 = ByteCount; ByteCount1; ) {
                    Status = CheckCached(vi, AbsoluteOffset1, ByteCount1, &cBuffer1, &cBufferLength1, DataRegion);
                    if (EFI_ERROR(Status)) {
                        HandleDiskIoError(vi, Status);
                        return Status;
                    }
                    ByteCount1 -= cBufferLength1;
                    AbsoluteOffset1 += cBufferLength1;
                }
                continue;
            }
       //      Copy i/p buffer to the cache. Update the flag
            pBS->CopyMem(cBuffer, Buffer, cBufferLength);
            Buffer += cBufferLength;
            ByteCount -= cBufferLength;
            ch->DIRTY_FLAG = TRUE;
        }
        while (ByteCount);
     */
//###DEBUG END
    do {
        Status = CheckCached(vi, AbsoluteOffset, ByteCount, &cBuffer, &cBufferLength, &ch, DataRegion);
        
        if (EFI_ERROR(Status)) {
            HandleDiskIoError(vi, Status);
            return Status;
        }
        
        pBS->CopyMem(cBuffer, Buffer, cBufferLength);
        ByteCount -= cBufferLength;
        Buffer += cBufferLength;
        AbsoluteOffset += cBufferLength;
        ch->DIRTY_FLAG = TRUE;
    }   while (ByteCount);
    
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       HandleDiskIoError
//
// Description:     Handles disk read/write error
//
// Parameters:
//  VOLUME_INFO     *vi,    Volume Info Structure
//
// Return value:    None
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

void
HandleDiskIoError (
    VOLUME_INFO *vi,
    EFI_STATUS  Status

)
{

//###DEBUG
// We may need some error handling here
//###DEBUG END
    if (Status == EFI_MEDIA_CHANGED || Status == EFI_NO_MEDIA)
        FreeUpResources (vi, Status);
        
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       FreeUpResources
//
// Description:     Frees up resouces when volumes opened/closed
//
// Parameters:
//  VOLUME_INFO     *vi,        Volume info structure
//  EFI_STATUS      Status      Status to update file handles with
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FreeUpResources (
    VOLUME_INFO *vi,
    EFI_STATUS  Status
)
{

    DLINK                *dlink = vi->OpenFIs.pHead;
    FILE_HANDLE          *fh;
    FILE_HANDLE_INSTANCE *fhi;
    CACHE_HEADER         *ch;
    
    
//      Go through the list of Open File Handles Instances and update the status
    while (dlink) {
        fhi = OUTTER(dlink, ViFILink, FILE_HANDLE_INSTANCE);
        fhi->HandleInstanceStatus = Status;
        fhi->pFH = NULL;
        DListDelete (&(vi->OpenFIs), &(fhi->ViFILink));
        
        if (!dlink->pNext) break;
        
        dlink = dlink->pNext;
    }
    
    
//      Release all File_Handles/DirList
    dlink = vi->OpenFHs.pHead;
    
    while (dlink) {
        fh = OUTTER(dlink, ViFHLink, FILE_HANDLE);
        fh->InstancesCount = 0;
        dlink = dlink->pNext;
        
        if (fh->DirList.pHead) RemoveAllDirList(fh);
        
        if (fh->ROOTDIR) vi->RootFH = NULL;
        
        RemoveFH(fh);
    }
    
//      Update the Status in VOLUME_INFO
    vi->VolumeStatus = Status;
    vi->ValidVolumeID = FALSE;
    
    if (vi->FileSystemName) pBS->FreePool (vi->FileSystemName);
    
    vi->FileSystemName = NULL;
    
////////////////////////////////////////////////////////////////////////////////////////

    dlink = vi->CacheList.pTail;
    
    if (!dlink) return FALSE;
    
    for ( ; dlink; ) {
        ch = OUTTER(dlink, CacheLink, CACHE_HEADER);
        ch->AbsoluteOffset = 0;
        ch->AbsoluteOffsetEnd = 0;
        ch->DIRTY_FLAG = FALSE;
        dlink = dlink->pPrev;
    }
    
////////////////////////////////////////////////////////////////////////////////////////

    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ValidateCurrentStatus
//
// Description:     Validates status if file handle instance
//
// Parameters:
//  FILE_HANDLE_INSTANCE    *fhi
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ValidateCurrentStatus (
    FILE_HANDLE_INSTANCE *fhi
)
{
    FILE_HANDLE *Pfh = fhi->pFH;
    
    if (fhi->HandleInstanceStatus != EFI_SUCCESS) return fhi->HandleInstanceStatus;
    
    if (!Pfh) return EFI_NOT_FOUND;
    
    if (Pfh->HandleStatus != EFI_SUCCESS) return Pfh->HandleStatus;
    
    if (EFI_ERROR(Pfh->VolumeInterface->VolumeStatus)) return Pfh->VolumeInterface->VolumeStatus;
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetPositionFileHandle
//
// Description:     Gets position in an open file handle
//
// Parameters:
//  IN EFI_FILE_PROTOCOL *This,
//  IN UINT64 *Position
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetPositionFileHandle (
    IN EFI_FILE_PROTOCOL *This,
    IN UINT64            *Position
)
{

    EFI_STATUS           Status;
    FILE_HANDLE_INSTANCE *fhi = (FILE_HANDLE_INSTANCE *)This;
    FILE_HANDLE          *Pfh = fhi->pFH;
    VOLUME_INFO          *vi = Pfh->VolumeInterface;
    
    Status = ValidateCurrentStatus (fhi);
    
    if (EFI_ERROR(Status)) return Status;
    
    if (fhi->HandleInstanceStatus | Pfh->HandleStatus | vi->VolumeStatus) return EFI_UNSUPPORTED;
    
    if (Pfh->DirectoryEntry.Dir_Attr & (ATTR_VOLUME_ID | ATTR_DIRECTORY)) return EFI_UNSUPPORTED;
    
    *Position = fhi->Position;
    
#ifdef Debug_GetPosition
    EfiDebugPrint(-1,"GetPosition: File Name %s Position %x\n", Pfh->FileNameLFN, buffer->FileSize, Position);
#endif
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SetPositionFileHandleThis
//
// Description:     Sets position in current file handle instance
//
// Parameters:
//  IN EFI_FILE_PROTOCOL *This,
//  IN UINT64 Position
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SetPositionFileHandleThis (
    IN EFI_FILE_PROTOCOL *This,
    IN UINT64            Position
)
{
    EFI_TPL              SaveTpl;
    EFI_TPL              NextTpl;
    EFI_STATUS           Status;
    FILE_HANDLE_INSTANCE *fhi = (FILE_HANDLE_INSTANCE *)This;
    
    Status = ValidateCurrentStatus (fhi);
    
    if (EFI_ERROR(Status)) return Status;
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);
    Status = SetPositionFileHandle (fhi, Position);
    pBS->RestoreTPL(SaveTpl);    
    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SetPositionFileHandle
//
// Description:     Sets position in an open file handle
//
// Parameters:
//  IN FILE_HANDLE_INSTANCE *fhi,
//  IN UINT64               Position
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SetPositionFileHandle (
    IN FILE_HANDLE_INSTANCE *fhi,
    IN UINT64               Position
)
{

    FILE_HANDLE *Pfh = fhi->pFH;
    VOLUME_INFO *vi = Pfh->VolumeInterface;
    
#ifdef Debug_SetPosition
    EfiDebugPrint(-1,"SetPosition: %s Pos %lx", fhi->pFH->FileNameLFN, Position);
#endif
    
    if (fhi->HandleInstanceStatus | Pfh->HandleStatus | vi->VolumeStatus) return EFI_UNSUPPORTED;
    
    if (Pfh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY) {
        if (Position != 0) return EFI_UNSUPPORTED;
    }
    
    fhi->Position = Position;
    
//TODO TODO TODO
// If Position is beyond the filesize, update the file position.
// For reads issues Device_error. While writing, extend the file.
//TODO TODO TODO

//  Update  internal data Area
    if (fhi->Position == -1) fhi->Position = Pfh->DirectoryEntry.Dir_FileSize;
    
    if (fhi->Position == 0) {
        fhi->CurrentCluster = FIRSTCLUSTER(fhi->pFH->DirectoryEntry);
        fhi->CurrentClusterOffset = 0;
        
    } else {
        GetClusterPosition(fhi, fhi->Position, &fhi->CurrentCluster, &fhi->CurrentClusterOffset);
    }
    
#ifdef Debug_SetPosition
    EfiDebugPrint(-1," Clus %x  ClusOffset %x\n", fhi->CurrentCluster, fhi->CurrentClusterOffset);
#endif
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       RemoveFH
//
// Description:     Romoves file handle (closed file)
//
// Parameters:
//  FILE_HANDLE         *fh
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveFH (
    FILE_HANDLE *fh
)
{

    VOLUME_INFO *vi = fh->VolumeInterface;
    
#ifdef Debug_RemoveFH
    EfiDebugPrint(-1,"RemoveFH: %s\n", fh->FileNameLFN);
#endif
    
//  Check if there any open instances for this FH
    if (fh->InstancesCount) return EFI_ACCESS_DENIED;
    
//  Check if DLIST is NULL.
    if (fh->DirList.pHead) return EFI_ACCESS_DENIED;
    
    fsDeAllocateMemory(vi, fh->FileNameLFN);
    DListDelete (&(vi->OpenFHs),           &(fh->ViFHLink));
    
// Delete child Dlist only if parent is valid.
    if (fh->Parent) DListDelete (&(fh->Parent->ChildList), &(fh->ChildLink));
    
    fsDeAllocateMemory(vi, fh);
    
#ifdef Debug_RemoveFH
    EfiDebugPrint(-1,"RemoveFH Success\n");
#endif
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetNextCompName
//
// Description:     Gets next component name in path
//
// Parameters:
//  IN OUT CHAR16   **FileName,
//  IN CHAR16       *NextCompName
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetNextCompName (
    IN OUT CHAR16 **FileName,
    IN CHAR16     *NextCompName
)
{

    UINT32 Index = 0;
    NextCompName[Index] = (*FileName)[Index];
    
    while ((*FileName)[Index] !=0 && (*FileName)[Index] != '\\') {
        NextCompName[Index] = (*FileName)[Index];
        Index++;
        
        if (Index >= MAX_TOTAL_PATH_LENGTH) return EFI_INVALID_PARAMETER;
    }
    
    NextCompName[Index] = 0;
    
//  Point *FileName beyond the trailing '\\'
    if ((*FileName)[Index] == '\\') {
        Index++;
    }
    
//  After '\\' it should not be  0.
    if (Index != 0 && (*FileName)[Index - 1] == '\\' &&
            (*FileName)[Index] == 0) {
        return EFI_INVALID_PARAMETER;
    }
    
    *FileName = (*FileName) + Index;
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       fsAllocateMemory
//
// Description:     Allocates memory for use by file system driver
//
// Parameters:
//  VOLUME_INFO     *vi
//  VOID            **Buffer
//  UINT32          Size
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
fsAllocateMemory (
    VOLUME_INFO *vi,
    UINT32      Size,
    VOID        **Buffer,
    BOOLEAN     CLEAR
)
{

    EFI_STATUS Status;
    UINTN      Address = (UINTN) Buffer;
    UINT32     Length;
    
    
    if (Size <= 1024) {
        Status = InternalMemAllocate (vi, Size, Buffer, CLEAR);
        return Status;
    }
    
    Status = pBS->AllocatePool (EfiBootServicesData,
                                Size,
                                (VOID**)Buffer);
                                
    Address = (UINTN) *Buffer;
    Address -=0xc;          // Point to the Size
    Length = *(UINT32 *)Address; // Get the size
    
    if (Status == EFI_SUCCESS) vi->AllocatedMemorySize += Length;
    
    if (Status == EFI_SUCCESS && CLEAR) Zeromemory (*Buffer, Size);
    
#ifdef  Debug_Allocatememory
    EfiDebugPrint(-1,"AllocateMemory : %x  Total mememory Allocated : %x\n", Length, vi->AllocatedMemorySize);
#endif
    
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       fsDeAllocateMemory
//
// Description:     De-allocates memory used by file system driver
//
// Parameters:
//  VOLUME_INFO     *vi,
//  void            *Buffer
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
fsDeAllocateMemory (
    VOLUME_INFO *vi,
    void        *Buffer
)
{
    UINTN      Address = (UINTN) Buffer;
    UINT32     Size;
    EFI_STATUS Status;
    
    
    Status = FreeMemory (vi, Buffer);
    
    if (Status == EFI_SUCCESS) return EFI_SUCCESS;
    
    Address -=0xc;          // Point to the Size
    Size = *(UINT32 *)Address; // Get the size
    vi->AllocatedMemorySize -= Size;
    Status = pBS->FreePool(Buffer);
    
    if (Status == EFI_SUCCESS) Buffer = NULL;
    
#ifdef  Debug_Allocatememory
    EfiDebugPrint(-1,"DeAllocateMemory : %x  Total mememory Allocated : %x\n", Size, vi->AllocatedMemorySize);
#endif
    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       InternalMemAllocate
//
// Description:     Adds allocated memory to internal manager
//
// Parameters:
//  VOLUME_INFO     *vi,
//  UINT32          Size,
//  VOID            **Buffer,
//  BOOLEAN         CLEAR
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InternalMemAllocate (
    VOLUME_INFO *vi,
    UINT32      Size,
    VOID        **Buffer,
    BOOLEAN     CLEAR
)
{
    EFI_STATUS Status = EFI_OUT_OF_RESOURCES;
    DLINK      *dlink = vi->MemList.pTail;
    MEM_HEADER *Mem;
    UINT32     Blocks;
    
    Blocks = Size / MEMALLOCSIZE;
    
    if (Size % MEMALLOCSIZE) Blocks++;
    
    for ( ; ; ) {
        if (!dlink)  {
            Status = AddBlocktoInternalMemManager (vi);
            
            if (EFI_ERROR(Status)) return Status;
            
            dlink = vi->MemList.pTail;
        }
        
        Mem = OUTTER(dlink, MemLink, MEM_HEADER);
        Status = GetMemory (Mem, Blocks, Buffer, CLEAR);
        
        if (Status == EFI_SUCCESS) return Status;
        
        dlink = dlink->pPrev;
    }
    
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetMemory
//
// Description:     Gets memory for a buffer
//
// Parameters:
//  MEM_HEADER  *Mem,
//  UINT32      Blocks,
//  VOID        **Buffer,
//  BOOLEAN     CLEAR
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetMemory (
    MEM_HEADER *Mem,
    UINT32     Blocks,
    VOID       **Buffer,
    BOOLEAN    CLEAR
)
{
    UINT32     i, FreeBlockCounts = 0, StartBlock, Count;
    UINT8      *MemMap = (UINT8 *)(Mem->AddresMap);
    EFI_STATUS Status = EFI_NOT_FOUND;
    
    for (i = 0; i < MEMBLOCKSIZE / MEMALLOCSIZE; i++) {
        if (!MemMap[i]) {
            if (!FreeBlockCounts) StartBlock = i;
            
            FreeBlockCounts++;
            
            if (FreeBlockCounts >=  Blocks) {
                Status = EFI_SUCCESS;
                break;
            }
            
        } else FreeBlockCounts = 0;
    }
    
    if (Status == EFI_SUCCESS) {
        *Buffer = (void *)(Mem->BufferStart + StartBlock * MEMALLOCSIZE);
        
        for (i = 0, Count = 1; i < Blocks; i++, StartBlock++, Count++)
            MemMap[StartBlock] = Count;
            
        if (CLEAR) Zeromemory (*Buffer, MEMALLOCSIZE * Blocks);
    }
    
    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       FreeMemory
//
// Description:
//
// Parameters:
//  VOLUME_INFO         *Vi,
//  VOID                *Buffer
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FreeMemory (
    VOLUME_INFO *vi,
    VOID        *Buffer
)
{

    EFI_STATUS Status = EFI_NOT_FOUND;
    DLINK      *dlink = vi->MemList.pHead;
    MEM_HEADER *Mem;
    UINT32     StartBlock, Count;
    
    for ( ; dlink ; ) {
        Mem = OUTTER(dlink, MemLink, MEM_HEADER);
        
        if (Buffer >= (void *)(Mem->BufferStart) && Buffer < (void *)(Mem->BufferEnd)) {
        
            StartBlock  = (UINT32) (((UINTN)Buffer - Mem->BufferStart) / MEMALLOCSIZE);
            
            Status = EFI_SUCCESS;
            
            for (Count = 1; ; Count++, StartBlock++)
                if (((UINT8 *)(Mem->AddresMap))[StartBlock] == Count) ((UINT8 *)(Mem->AddresMap))[StartBlock] = 0;
                
                else break;
                
        }
        
        if (Status == EFI_SUCCESS) break;
        
        dlink = dlink->pNext;
    }
    
    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       InternalMemAllocate
//
// Description:
//
// Parameters:
//  VOLUME_INFO         *Vi,
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AddBlocktoInternalMemManager (
    VOLUME_INFO *vi
)
{
    EFI_STATUS Status;
    UINT32     *Buffer;
    MEM_HEADER *Mem;
    Status = pBS->AllocatePool (EfiBootServicesData,
                                MEMBLOCKSIZE + MEMBLOCKSIZE / MEMALLOCSIZE,
                                (VOID**)&Buffer);
                                
    if (EFI_ERROR(Status)) return Status;
    
    vi->AllocatedMemorySize += MEMBLOCKSIZE + MEMBLOCKSIZE / MEMALLOCSIZE;
    
    Status = pBS->AllocatePool (EfiBootServicesData,
                                sizeof (MEM_HEADER),
                                (VOID**)&Mem);
                                
    if (EFI_ERROR(Status)) return Status;
    
    vi->AllocatedMemorySize += sizeof (MEM_HEADER);
    
    Mem->AddresMap = (UINTN) Buffer;
    Mem->AddresMapLength = MEMBLOCKSIZE / MEMALLOCSIZE;
    Mem->BufferStart = (UINTN) (Buffer) + MEMBLOCKSIZE / MEMALLOCSIZE;
    Mem->BufferEnd = Mem->BufferStart + MEMBLOCKSIZE;
    DListAdd(&(vi->MemList), &(Mem->MemLink));
    Zeromemory (Buffer, MEMBLOCKSIZE / MEMALLOCSIZE);
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       FatLfnIsValid
//
// Description:     Checks for valid long file name
//
// Parameters:
//  CHAR16      *Name
//
// Return value:    BOOLEAN - True if long file name is valid
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
FatLfnIsValid (
    CHAR16 *Name
)
{
    CHAR16  *p1, *p2;
    BOOLEAN IsAllDot;
    
    IsAllDot = TRUE;
    
    p1 = Name;
    
    do {
        if (*p1 != '.') {
            IsAllDot = FALSE;
        }
        
        p1++;
    } while (*p1);
    
    if (IsAllDot) {
        return TRUE;
    }
    
    //
    // Strip off starting/trailing spaces and trailing periods
    //
    for (p1 = Name; *p1 && *p1 == ' '; p1++) {
        ;
    }
    
    p2 = Name;
    
    while (*p1) {
        *p2 = *p1;
        p1++;
        p2++;
    }
    
    *p2 = 0;
    
    for (p1 = Name + Wcslen(Name) - 1;
            p1 >= Name && (*p1 == ' ' || *p1 == '.');
            p1--) {
        ;
    }
    
    *(p1 + 1) = 0;
    
    //
    // We don't allow zero length name
    //
    if (*Name == 0) {
        return FALSE;
    }
    
    //
    // See if there is any illegal characters within the name
    //
    while (*Name) {
        if (    *Name < 0x20 ||
                *Name == '\"' ||
                *Name == '*' ||
                *Name == '/' ||
                *Name == ':' ||
                *Name == '<' ||
                *Name == '>' ||
                *Name == '?' ||
                *Name == '\\' ||
                *Name == '|' ) {
            return FALSE;
        }
        
        Name++;
    }
    
    return TRUE;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ExtractShortFileName
//
// Description:     Extracts short file name from buffer
//
// Parameters:
//  VOLUME_INFO         *Vi,
//  CHAR16              *lfn,
//  UINT8               *Buffer
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

ExtractShortFileName (
    VOLUME_INFO         *Vi,
    CHAR16              *lfn,
    UINT8               *Buffer
)
{

    CHAR16 *p1;
    
//  Copy 8 characters
    Vi->UnicodeCollationInterface->FatToStr (Vi->UnicodeCollationInterface,
            8,
            Buffer,
            lfn);
            
            
//  Remove trailing Spaces
    for (p1 = lfn + 7; p1 >= lfn && (*p1 == ' '); p1--) {
        ;
    }
    
    p1++;
//  P1 Points to the first Space in the 8 character sequence
    Vi->UnicodeCollationInterface->FatToStr (Vi->UnicodeCollationInterface,
            3,
            Buffer + 8,
            p1 + 1); // leave space for '.'
            
    *(p1 + 4) = 0;          // if all three characters are valid
    
    if (*(p1 + 1) != ' ') {
        *p1 = '.';          // extension is valid
        
        if (*(p1 + 3) == ' ') *(p1 + 3) = 0;
        
        if (*(p1 + 2) == ' ') *(p1 + 2) = 0;
        
        if (*(p1 + 1) == ' ') *(p1 + 1) = 0;
        
    } else {
        *p1 = 0;            // No extension
    }
    
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
