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
// $Header: /Alaska/SOURCE/Core/Modules/FileSystem/Info.c 15    5/05/11 3:44p Pats $
//
// $Revision: 15 $
//
// $Date: 5/05/11 3:44p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/FileSystem/Info.c $
// 
// 15    5/05/11 3:44p Pats
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
// 14    2/25/11 2:44p Pats
// [TAG] - EIP 54399
// [Category]- BUG FIX
// [Severity] - Urgent
// [Symptom] - SCT 2.3 fails Bootable Image Support Test\Simple File
// System Protocol
// [RootCause] - Does not check for matching name when attempting to
// change file name.
// [Solution] - Modified function SetfileInfo() to check for matching
// name.
// [Files] - info.c
// 
// 13    1/19/11 4:56p Pats
// [TAG] - EIP 52430
// [Category]- BUG FIX
// [Severity] - Normal
// [Symptom] - When a directory is moved, the long name of the old
// directory is not deleted.
// [RootCause] - Only the short name component was being deleted in
// SetFileInfo().
// [Solution] - Modified function SetfileInfo() to delete the long name
// component also.
// [Files] - info.c
// 
// 12    1/14/11 2:59p Pats
// [TAG] - EIP 51754
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - The shell "mv" command makes directories dissapear.
// [RootCause] - Directorys were not removed from cache when deleted..
// [Solution] - Modified function SetfileInfo() to remove directories from
// cache when deleted.
// [Files] - info.c
// 
// 11    1/06/11 5:54p Oleksiyy
// [TAG]  		EIP28607
// [Category]  	Improvement
// [Description]  	System was hanging for some time if Floppy Media
// removed while writing in meda in progress.
// EFI_TPL_CALLBACK priority level rised during media related calls.
// 
// [Files]  		DiskIo.c, Info.c, MediaAccess.c, Open.c, Partition.c
// 
// 10    1/22/10 4:39p Yul
// Refer to EIP 32983.
// 
// 9     7/02/09 5:47p Pats
// Updated to latest coding standard. No code changes.
//
// 8     4/13/07 7:07p Pats
// Edited to conform with coding standards. No code changes.
//
// 7     8/16/06 12:03p Markw
// Fixed UINTN* and UINT32* 64-bit issues.
//
// 10    11/03/05 2:16p Srinin
// Fixed VC7.1 warning msg.
//
// 9     8/08/05 3:55p Markw
// In SetVolumeLabel, after CreateDirectoryEntry, check if valid file
// handle before removing.
//
// 6     6/22/05 4:29p Pats
// Added function Labcpy() to replace Wcscpy() so that volume labels are
// copied correctly. Dumps period added by ExtractShortFileName.
//
// 4     6/21/05 9:51a Pats
// Fixed GetVolumeLabel so that it properly handles the case when there is
// no label on the volume, to pass SCT tests.
//
// 3     6/16/05 4:17p Pats
// Modified to mark both long and short name entries deleted when a file
// is deleted, instead of just short name entries.
//
// 2     4/27/05 5:30p Srinin
// 'MV' command supported (Move file/Directories in a volume)
//
// 1     4/26/05 6:05p Srinin
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: Info.c
//
// Description:  Simple File System driver information handling functions
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------

#include "FileSystem.h"
#define EFI_TPL_CALLBACK TPL_CALLBACK
//----------------------------------------------------------------------

extern EFI_GUID gEfiFileSystemVolumeLabelGuid;
extern EFI_GUID gEfiFileInfoGuid;
extern EFI_GUID gEfiFileSystemInfoGuid;

//----------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UpdateAccAndWriteTime
//
// Description:     Updates access and write times in a directory entry
//
// Parameters:      DIR_ENTRY_LIST *del - pointer to the directory entry list
//                                        structure
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
UpdateAccAndWriteTime (
    DIR_ENTRY_LIST *del
)
{

    EFI_TIME              EfiTime;
    EFI_TIME_CAPABILITIES Capabilities;
    UINT16                DummyTime;
    
    pRS->GetTime(&EfiTime, &Capabilities);
    EfiToFatTime (EfiTime, &del->DirectoryEntry.Dir_LstAccDate, &DummyTime);
    EfiToFatTime (EfiTime, &del->DirectoryEntry.Dir_WrtDate,    &del->DirectoryEntry.Dir_WrtTime);
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UpdateAccDate
//
// Description:     Updates the access date in a directory entry
//
// Parameters:      DIR_ENTRY_LIST *del - pointer to the directory entry list
//                                        structure
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
UpdateAccDate(
    DIR_ENTRY_LIST *del
)
{

    EFI_TIME              EfiTime;
    EFI_TIME_CAPABILITIES Capabilities;
    UINT16                DummyTime;
    
    pRS->GetTime(&EfiTime, &Capabilities);
    EfiToFatTime (EfiTime, &del->DirectoryEntry.Dir_LstAccDate, &DummyTime);
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UpdateAccDateRequired
//
// Description:     Indicates when update of the access date of a file is
//                  required
//
// Parameters:      DIR_ENTRY_LIST *del - pointer to the directory entry list
//                                        structure
//
// Return value:    BOOLEAN - True if update required
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
UpdateAccDateRequired (
    DIR_ENTRY_LIST *del
)
{

    EFI_TIME              EfiTime;
    EFI_TIME_CAPABILITIES Capabilities;
    UINT16                DummyTime;
    UINT16                DummyDate;
    
    pRS->GetTime(&EfiTime, &Capabilities);
    EfiToFatTime (EfiTime, &DummyDate, &DummyTime);
    
    if (DummyDate == del->DirectoryEntry.Dir_LstAccDate) return FALSE;
    
    del->DirectoryEntry.Dir_LstAccDate = DummyDate;
    return TRUE;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetInfoFileHandle
//
// Description:     Returns file info, system info, or the label of a volume
//                  depending on information type specified
//
// Parameters:      EFI_FILE_PROTOCOL *This - Pointer to this instance of
//                                            file protocol
//                  EFI_GUID *InformationType - Pointer to information type
//                                              requested
//                  UINTN *BufferSize - Pointer to size of buffer
//                  VOID *Buffer - Pointer to buffer for returned info
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
GetInfoFileHandle(
    IN EFI_FILE_PROTOCOL *This,
    IN EFI_GUID          *InformationType,
    IN OUT UINTN         *BufferSize,
    OUT VOID             *Buffer
)
{

    EFI_STATUS           Status = EFI_UNSUPPORTED;
    FILE_HANDLE_INSTANCE *fhi = (FILE_HANDLE_INSTANCE *)This;
    FILE_HANDLE             *Pfh;
    VOLUME_INFO             *vi;
    EFI_TPL                 SaveTpl;
    EFI_TPL                 NextTpl;
    
    Status = ValidateCurrentStatus (fhi);
    
    if (EFI_ERROR(Status)) return Status;
    Pfh = fhi->pFH;
    vi = Pfh->VolumeInterface;
//  Compare the GUID
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);
    if (!guidcmp(InformationType, &gEfiFileInfoGuid))
        Status = GetfileInfo (fhi, BufferSize, Buffer);
        
    else  {
        if (!guidcmp(InformationType, &gEfiFileSystemInfoGuid))
            Status = GetSystemInfo (vi, BufferSize, (EFI_FILE_SYSTEM_INFO *)Buffer);
            
        else {
            if (!guidcmp(InformationType, &gEfiFileSystemVolumeLabelGuid))
                Status = GetVolumeLabel (vi, BufferSize, Buffer);
                
            else{
                pBS->RestoreTPL(SaveTpl);
                return EFI_UNSUPPORTED;
            }
        }
    }
    pBS->RestoreTPL(SaveTpl);    
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetfileInfo
//
// Description:     Returns information on a file
//
// Parameters:      FILE_HANDLE_INSTANCE *fh1 - Pointer to file handle
//                                              instance
//                  UINTN *BufferSize - Pointer to size of buffer
//                  VOID *Buffer - Ponter to buffer for returned data
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
GetfileInfo (
    IN FILE_HANDLE_INSTANCE *fhi,
    IN OUT UINTN            *BufferSize,
    OUT VOID                *Buffer
)
{

    FILE_HANDLE *Pfh = fhi->pFH;
    return (GetFileInfoFromFH (Pfh, BufferSize, Buffer));
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetSystemInfo
//
// Description:     Returns file system info on a volume
//
// Parameters:      VOLUME_INFO *vi - Pointer to volume info structure
//                  UINTN *BufferSize - Pointer to size of buffer
//                  VOID *Buffer - Ponter to buffer for returned data
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
GetSystemInfo (
    IN VOLUME_INFO           *vi,
    IN OUT UINTN             *BufferSize,
    OUT EFI_FILE_SYSTEM_INFO *Buffer
)
{

    UINTN Length = 0;
    GetVolumeLabel (vi, &Length, Buffer);
    
    if (*BufferSize < Length + EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO, VolumeLabel)) {
    
#ifdef Debug_GetSystemInfo
        EfiDebugPrint(TRACE_ALWAYS,"GetSystemInfo: I/P BufferSize %x O/P BufferSize %x\n", *BufferSize, Length + EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO, VolumeLabel));
#endif
        
        *BufferSize = Length + EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO, VolumeLabel);
        return EFI_BUFFER_TOO_SMALL;
        
    }
    
    Buffer->Size = Length + EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO, VolumeLabel);
    Buffer->ReadOnly = vi->ReadOnly;
    Buffer->VolumeSize = vi->VolumeSize;
    Buffer->FreeSpace =     Mul64(ReturnFreeSpace(vi), vi->BytesPerCluster);
    Buffer->BlockSize = vi->BytesPerCluster;
    GetVolumeLabel (vi, BufferSize, ((UINT8 *)Buffer) + EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO, VolumeLabel));
    *BufferSize +=                                      EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO, VolumeLabel);
    
#ifdef Debug_GetSystemInfo
    EfiDebugPrint(TRACE_ALWAYS,"GetSystemInfo: VolumeLabel %s, BufferSize %x\n", Buffer->VolumeLabel, *BufferSize);
    EfiDebugPrint(TRACE_ALWAYS,"Size %lx, ReadOnly %x, VolumeSize %lx, FreeSpace %lx, BlockSize %x\n", Buffer->Size, Buffer->ReadOnly, Buffer->VolumeSize, Buffer->FreeSpace, Buffer->BlockSize);
#endif
    
    return EFI_SUCCESS;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetVolumeLabel
//
// Description:     Returns label of a volume
//
// Parameters:      VOLUME_INFO *vi - Pointer to volume info structure
//                  UINTN *BufferSize - Pointer to size of buffer
//                  VOID *Buffer - Ponter to buffer for returned data
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
GetVolumeLabel (
    IN VOLUME_INFO *vi,
    IN OUT UINTN   *BufferSize,
    OUT VOID       *Buffer
)
{

    EFI_STATUS     Status;
    EFI_STATUS     LocalStatus;
    FILE_HANDLE    *fh = vi->RootFH;
    UINTN          Length;
    DLINK          *dlink;
	DIR_ENTRY_LIST	*del=NULL;
    
    if (vi->ValidVolumeID) {
        Length = Wcslen (vi->VolumeID) << 1;
        
#ifdef Debug_GetVolumeLabel
        EfiDebugPrint(-1,"GetVolumeLabel: VolLabel %s I/P BufferSize %x O/P BufferSize %x\n", vi->VolumeID, *BufferSize, Length + 2);
#endif
        
        if (*BufferSize < (Length + 2)) {
            *BufferSize = Length + 2;
            return EFI_BUFFER_TOO_SMALL;
        }
        
        Wcscpy (Buffer, vi->VolumeID);
        *BufferSize = Length + 2;
        return EFI_SUCCESS;
        
    } else {
        if (*BufferSize < 2) {
            Status = EFI_BUFFER_TOO_SMALL; // To pass SCT test.
            
        } else Status = EFI_NOT_FOUND;
    }
    
    
//  See if the Linked List is Valid
    if (!fh->DirList.pHead) ReadAllDirectoryEntries (fh);
    
    dlink = fh->DirList.pHead;
    LocalStatus = EFI_UNSUPPORTED;
    
    if (!dlink) return EFI_UNSUPPORTED;
    
    for ( ; dlink; ) {
        del = OUTTER(dlink, DirLink, DIR_ENTRY_LIST);
        
        if ((del->DirectoryEntry.Dir_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID)) == ATTR_VOLUME_ID) {
            LocalStatus = EFI_SUCCESS;
            break;
        }
        
        dlink = dlink->pNext;
    }
    
    if (LocalStatus == EFI_SUCCESS) {
        Length = Lablen (del->FileNameLFN) << 1;
        
        if (Length <= 22) {
            Zeromemory (vi->VolumeID, sizeof (vi->VolumeID));
            Labcpy (vi->VolumeID, del->FileNameLFN); // Don't put "." in name
            vi->ValidVolumeID = TRUE;
        }
        
        if (*BufferSize < (Length + 2)) {
        
#ifdef Debug_GetVolumeLabel
            EfiDebugPrint(-1,"GetVolumeLabel: VolLabel %s I/P BufferSize %x O/P BufferSize %x\n", vi->VolumeID, *BufferSize, Length + 2);
#endif
            
            *BufferSize = Length + 2;
            return EFI_BUFFER_TOO_SMALL;
        }
        
        Status = EFI_SUCCESS;
        Labcpy (Buffer, del->FileNameLFN);
        *BufferSize = Length >> 1;
        
#ifdef Debug_GetVolumeLabel
        EfiDebugPrint(-1,"GetVolumeLabel: VolLabel %s I/P BufferSize %x O/P BufferSize %x\n", Buffer, *BufferSize, Length + 2);
#endif
        
    }
    
// If there is no volume label, we must return a null label of size 2.
    else if (Status == EFI_NOT_FOUND) {
        if (*BufferSize >= 2) Zeromemory (Buffer, 2);
        
        *BufferSize = 2;
        Status = EFI_SUCCESS;
        
    } else if (Status == EFI_BUFFER_TOO_SMALL) *BufferSize = 2;
    
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SetfileInfo
//
// Description:     Sets the information on a file (updates dir entry)
//
// Parameters:      FILE_HANDLE_INSTANCE *fh1 - Pointer to file handle
//                                              instance
//                  UINTN *BufferSize - Pointer to size of buffer
//                  VOID *Buffer - Ponter to buffer containing new data
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
SetfileInfo (
    IN EFI_FILE_PROTOCOL    *This,
    IN FILE_HANDLE_INSTANCE *fhi,
    IN OUT UINTN            BufferSize,
    OUT VOID                *Buffer
)
{

    EFI_STATUS           Status;
    EFI_FILE_PROTOCOL    *NewHandle;
    FILE_HANDLE          *fh = fhi->pFH;
    FILE_HANDLE          *ParentFh = fh->Parent;
    DIR_ENTRY_LIST       *Del = NULL;
    FILE_HANDLE_INSTANCE *Newfhi;
    VOLUME_INFO          *vi = fh->VolumeInterface;
    EFI_FILE_INFO        *buffer = Buffer;
    UINT16               Dummy;
    UINT32               Length;
    UINT32               OldClusterCount, NewClusterCount;
    UINT8                DirErase = DIR_ENTRY_ERASE;
    CHAR16               *NewFileName;
    BOOLEAN              IsSizeChange = fh->DirectoryEntry.Dir_FileSize != (UINT32)(buffer->FileSize) ? TRUE : FALSE;
    BOOLEAN              IsNameChange = (BOOLEAN)Wcscmpcaseinsensitive(buffer->FileName, fh->FileNameLFN);
    
#ifdef Debug_SetFileInfo
    EfiDebugPrint(-1,"SetFileInfo: %S I/P BufferSize %x\n",        fh->FileNameLFN,  BufferSize);
    EfiDebugPrint(-1,"FileSize %lx, Physical %lx Attribute %lx\n", buffer->FileSize, buffer->PhysicalSize, buffer->Attribute);
#endif
    
    Length = EFI_FIELD_OFFSET(EFI_FILE_INFO,FileName);
    
    if (BufferSize < Length) return EFI_BAD_BUFFER_SIZE;
    
//  Is it a Directory Entry, attr can't be set
//  For a file, it cannot be set as Directory
    if ((fh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY) ^
            ((UINT8)(buffer->Attribute) & ATTR_DIRECTORY)) return EFI_ACCESS_DENIED;
            
//  For Root Directory no entries can be modified
    if (fh->ROOTDIR) return EFI_ACCESS_DENIED;
    
    if (buffer->Attribute & ~EFI_FILE_VALID_ATTR) return EFI_INVALID_PARAMETER;
    
    if (fh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY && IsSizeChange) return EFI_ACCESS_DENIED;
    
    if (vi->ReadOnly) return EFI_WRITE_PROTECTED;
    
    if ((fh->DirectoryEntry.Dir_Attr & ATTR_READ_ONLY ||
            fhi->OpenMode == EFI_FILE_MODE_READ) && (IsSizeChange || IsNameChange))
        return EFI_ACCESS_DENIED;
        
//  Update Attribute
#ifdef Debug_SetFileInfo
    EfiDebugPrint(-1, "Updated Attribute %x\n", fh->DirectoryEntry.Dir_Attr);
#endif
    
    fh->DirectoryEntry.Dir_Attr = (UINT8) buffer->Attribute;
    
//  Rename File/Directory?
    if (IsNameChange) {
    
#ifdef Debug_SetFileInfo
        EfiDebugPrint(-1,"SetFileInfo: New File Name %S Old FileName %S \n", buffer->FileName, fh->FileNameLFN);
#endif
        
//      Copy the Input FileName
        Length = (UINT32) (Wcslen(buffer->FileName) * sizeof (CHAR16))+ 2;
        Status = fsAllocateMemory (vi, Length, &NewFileName, FALSE);
        pBS->CopyMem (NewFileName, buffer->FileName, Length);
        
        if (FindMatchingDirEntry (ParentFh, NewFileName, &Del)) {
            fsDeAllocateMemory (vi, NewFileName);
            return EFI_ACCESS_DENIED; // Name already exists, can't rename to it
        }

        Status = ProcessOpenFileHandle (fhi, &NewFileName, &NewHandle, EFI_FILE_MODE_CREATE | 3, 0);
        fsDeAllocateMemory (vi, NewFileName);
        
        if (EFI_ERROR(Status)) return Status;
        
        Newfhi = (FILE_HANDLE_INSTANCE *) NewHandle;
        
//      Delete the old Entry
        if (fh->DirCluster || fh->DirOffset) {
            fh->DirectoryEntry.Dir_Name[0] = DirErase;
            Status = UpdateDirListFromFHDir(fh);
            if (EFI_ERROR(Status)) return Status;
			//Remove directory list from cache when deleted.
			RemoveAllDirList(fh);
        }
        
//      Other than FileName, copy all the directory entries.
        pBS->CopyMem (&(Newfhi->pFH->DirectoryEntry.Dir_Attr), &(fh->DirectoryEntry.Dir_Attr), 32 - 11);
        
//      Transfer Information from New to Old
        fhi->pFH = Newfhi->pFH;
        
//      Release the NewFileHandle Instance Created.
        DListDelete (&(vi->OpenFIs), &(Newfhi->ViFILink));
        fsDeAllocateMemory (vi, Newfhi);
        
        RemoveAllDirList(fh->Parent);           // Dir Listing for OLD File Handle
        RemoveAllDirList(Newfhi->pFH->Parent);  // Dir Listing for New File Handle
        fh->InstancesCount--;
        RemoveFH(fh);                   // Remove old File Handle
        fh = Newfhi->pFH;               // fh points to new FH
//###DEBUG
        /*
           //      For Directories, ".." entry should point to the new Parent.
                if (fh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY) {
           //          Read 40h Bytes
                    GetTempBuffer (vi, &TempBuffer);
                    GetSectorAddressDir(fh, FIRSTCLUSTER(fh->DirectoryEntry), 0, &Sector, &SectorOffset);
                    Status = FsReadMedia (vi, TempBuffer, Sector, SectorOffset, 0x40, DIRECTORY_REGION);
                    if (EFI_ERROR(Status)) return Status;
        
                    if (TempBuffer [0] == '.' && TempBuffer[0x20] == '.' && TempBuffer[0x21] == '.') {
                        (UINT32) TempBuffer += sizeof (DIR_ENTRY_32);
                        ((DIR_ENTRY_32 *) TempBuffer)->Dir_FstClusLO = fh->Parent->DirectoryEntry.Dir_FstClusLO;
                        ((DIR_ENTRY_32 *) TempBuffer)->Dir_FstClusHI = fh->Parent->DirectoryEntry.Dir_FstClusHI;
                        Status = FsWriteMedia (vi, TempBuffer, Sector, SectorOffset, 0x40, DIRECTORY_REGION);
                        if (EFI_ERROR(Status)) return Status;
                    }
                    ReleaseTempBuffer(vi);
                }
         */
//###DEBUG END
        fh->DirectoryEntry.Dir_Attr |= ATTR_ARCHIVE;
        
    }
    
//  Update the Date and Time?
    if (*(UINT32 *)&(buffer->CreateTime) != 0)
        EfiToFatTime(buffer->CreateTime,       &fh->DirectoryEntry.Dir_CrtDate,    &fh->DirectoryEntry.Dir_CrtTime);
        
    if (*(UINT32 *)&(buffer->LastAccessTime) != 0)
        EfiToFatTime(buffer->LastAccessTime,   &fh->DirectoryEntry.Dir_LstAccDate, &Dummy);
        
    if (*(UINT32 *)&(buffer->ModificationTime) != 0)
        EfiToFatTime(buffer->ModificationTime, &fh->DirectoryEntry.Dir_WrtDate,    &fh->DirectoryEntry.Dir_WrtTime);
        
//      Newsize smaller than Original size?
    if (fh->DirectoryEntry.Dir_FileSize > (UINT32)(buffer->FileSize))  {
    
        Status = CheckFileWrite (fhi, FALSE);
        
        if (EFI_ERROR(Status)) return Status;
        
#ifdef Debug_SetFileInfo
        EfiDebugPrint(-1,"SetFileInfo: File Name %S New Size %x Old Size %x\n", buffer->FileName, buffer->FileSize, fh->DirectoryEntry.Dir_FileSize);
#endif
        
        Length = fh->DirectoryEntry.Dir_FileSize - (UINT32)(buffer->FileSize);
        OldClusterCount = GetClustersRequired(vi, fh->DirectoryEntry.Dir_FileSize);
        NewClusterCount = GetClustersRequired(vi, (UINT32)(buffer->FileSize));
        
        if (NewClusterCount < OldClusterCount)
            ShrinkClusters (vi, FIRSTCLUSTER(fh->DirectoryEntry), NewClusterCount);
            
        fh->DirectoryEntry.Dir_FileSize = (UINT32)(buffer->FileSize);
        fh->DirectoryEntry.Dir_Attr |= ATTR_ARCHIVE;
        
        if (buffer->FileSize == 0 ) {
            fh->DirectoryEntry.Dir_FstClusLO = 0;
            fh->DirectoryEntry.Dir_FstClusHI = 0;
            SetPositionFileHandle (fhi, 0);
        }
        
        if (fhi->Position > buffer->FileSize) {
            SetPositionFileHandle (fhi, 0);
        }
    }
    
//      Newsize bigger than Original size?
    if (fh->DirectoryEntry.Dir_FileSize < buffer->FileSize) {
    
#ifdef Debug_SetFileInfo
        EfiDebugPrint(-1,"SetFileInfo: File Name %S New Size %x Old Size %x\n", buffer->FileName, buffer->FileSize, fh->DirectoryEntry.Dir_FileSize);
#endif
        
        Status = CheckFileWrite (fhi, FALSE);
        
        if (EFI_ERROR(Status)) return Status;
        
//          Get the Size in Bytes to be grown
        Length = (UINT32) (buffer->FileSize) - fh->DirectoryEntry.Dir_FileSize;
        Status = ExtendFile (fhi, Length);
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
//          Update New File Size
        fh->DirectoryEntry.Dir_FileSize = (UINT32)(buffer->FileSize);
        
    }
    
    
    Status = UpdateDirListFromFHDir(fh);
    fhi->pFH->DirEntryChanged = FALSE;
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UpdateDirListFromFHDir
//
// Description:     Updates directory list from file handle directory entry
//
// Parameters:      FILE_HANDLE *fh - Pointer to file handle structure
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):         Updates DIR list from FH Directory Entry and also writes
//                  to the disk.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UpdateDirListFromFHDir (
    FILE_HANDLE *fh
)
{
    EFI_STATUS     Status;
    DIR_ENTRY_LIST *Del;
    UINT32         Sector, SectorOffset, Position;
    UINT8          TempDirEntry[32];
    UINT32         TempOffset, TempSector;
    UINTN          i;
    
#ifdef Debug_CloseFileHandle
//  EfiDebugPrint(-1,"Update Dir Entry: %s, Dir Cluster %x, Dir Offset %x\n", fh->FileNameLFN, fh->DirCluster, fh->DirOffset);
#endif

    Status = LocateDel (fh->Parent->DirList.pHead, fh->DirCluster, fh->DirOffset, &Del, &Position);
    
    if (!EFI_ERROR(Status)) {
        pBS->CopyMem (&(Del->DirectoryEntry), &fh->DirectoryEntry, sizeof(DIR_ENTRY_32));
        Del->Cluster = fh->DirCluster;
        Del->Offset = fh->DirOffset;
        Del->SlotNumber = fh->SlotNumber;
    }
    
    GetSectorAddressDir(fh->Parent, fh->DirCluster, fh->DirOffset, &Sector, &SectorOffset);
    
    if (fh->DirectoryEntry.Dir_Name[0] == DIR_ENTRY_ERASE) {
        TempSector = Sector;
        TempOffset = SectorOffset;
        
        if (TempOffset == 0) {
            TempSector--;
            TempOffset = fh->VolumeInterface->VolumeBPB.BPB_BytePerSec;
        }
        
        for (i = 0; i < MAX_LFN_SLOTS; i++) {
            TempOffset -= sizeof(DIR_ENTRY_LFN);
            Status = FsReadMedia (fh->VolumeInterface, (void *)&TempDirEntry, TempSector, TempOffset, sizeof(DIR_ENTRY_32), DIRECTORY_REGION);
            
            if (TempDirEntry[11] == (ATTR_LONG_NAME)) {
                TempDirEntry[0] = DIR_ENTRY_ERASE; // Mark long entry erased.
                Status = FsWriteMedia (fh->VolumeInterface, (void *)&TempDirEntry, TempSector, TempOffset, sizeof(DIR_ENTRY_32), DIRECTORY_REGION);
                
            } else break;
            
            if (TempOffset == 0) {
                TempSector--;
                TempOffset = fh->VolumeInterface->VolumeBPB.BPB_BytePerSec;
            }
        }
    }
    
    return               FsWriteMedia (fh->VolumeInterface, (void *)&fh->DirectoryEntry, Sector,SectorOffset, sizeof(DIR_ENTRY_32), DIRECTORY_REGION);
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   LocateDel
//
// Description:
//
// Input:
//
// Output:
//
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
LocateDel (
    DLINK          *dlink,
    UINT32         Cluster,
    UINT32         ClusterOffset,
    DIR_ENTRY_LIST **Del,
    UINT32         *Position
)
{

    EFI_STATUS     Status = EFI_NOT_FOUND;
//  DLINK                   *dlink = fh->Parent->DirList.pHead;
    DIR_ENTRY_LIST *del;
    
    *Del = NULL;
    *Position = 0;
    
//  Copy this info to DIR_LIST if Present
    for ( ; dlink; dlink = dlink->pNext, ++*Position) {
        del = OUTTER(dlink, DirLink, DIR_ENTRY_LIST);
        
//      if (del->Cluster == fh->DirCluster && del->Offset == fh->DirOffset) {
        if (del->Cluster == Cluster && del->Offset == ClusterOffset) {
            *Del = del;
            Status = EFI_SUCCESS;
            break;
        }
    }
    
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SetSystemInfo
//
// Description:     Sets the information in a volume label
//
// Parameters:      VOLUME_INFO *vi - Pointer to volume info structure
//                  UINTN *BufferSize - Pointer to size of buffer
//                  VOID *Buffer - Ponter to buffer containing new data
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
SetSystemInfo (
    IN VOLUME_INFO           *vi,
    IN UINTN                 BufferSize,
    OUT EFI_FILE_SYSTEM_INFO *Buffer
)
{

    EFI_STATUS           Status;
    EFI_FILE_SYSTEM_INFO *buffer = Buffer;
    UINT32               Length = (UINT32)Wcslen(Buffer->VolumeLabel) + 2;
    
#ifdef Debug_SetSystemInfo
    Length += EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO, VolumeLabel);
    
    EfiDebugPrint(-1,"SetSystemInfo: VolumeLabel %s, BufferSize %x BufferRequired %x\n",     Buffer->VolumeLabel, BufferSize,       Length);
    EfiDebugPrint(-1,"Size %lx, ReadOnly %x, VolumeSize %lx, FreeSpace %lx, BlockSize %x\n", Buffer->Size,        Buffer->ReadOnly, Buffer->VolumeSize, Buffer->FreeSpace, Buffer->BlockSize);
#endif
    
    if (BufferSize < (EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO, VolumeLabel) + 2) || buffer->Size > BufferSize) {
        return EFI_BAD_BUFFER_SIZE;
    }
    
//  if (BufferSize < Length) return EFI_BAD_BUFFER_SIZE;

//  Only Volume Label can be set
    Status = SetVolumeLabel  (vi, Length, &Buffer->VolumeLabel);
    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SetVolumeLabel
//
// Description:     Updates the label on a volume
//
// Parameters:      VOLUME_INFO *vi - Pointer to volume info structure
//                  UINTN *BufferSize - Pointer to size of buffer
//                  VOID *Buffer - Ponter to buffer containing new label
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
SetVolumeLabel (
    IN VOLUME_INFO *vi,
    IN UINTN       BufferSize,
    OUT VOID       *Buffer
)
{

    EFI_STATUS     Status;
    UINT8          VolumeLabel[12];
    UINT32         Sector, SectorOffset, Length;
    FILE_HANDLE    *fh = vi->RootFH, *fh1;
    DLINK          *dlink;
    DIR_ENTRY_LIST *del;
    UINT8          i;
    
//  Convert the Unicode string to English
//  Shell Doen't support remove of LABEL right now.
//  if (!BufferSize ) return EFI_BAD_BUFFER_SIZE;

    Length = (UINT32)Wcslen(Buffer) * sizeof (CHAR16) + 2;
    
#ifdef Debug_SetVolumeLabel
    EfiDebugPrint(-1,"SetVolumeLabel: VolumeLabel %s BufferSize %x Length %x\n", Buffer, BufferSize, Length);
#endif
    
    Length = EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_VOLUME_LABEL, VolumeLabel);
    
    if (BufferSize < Length + 2) return EFI_BAD_BUFFER_SIZE;
    
    MemSet(VolumeLabel, 11, 0x20); // Fill short name with spaces
    vi->UnicodeCollationInterface->StrToFat (vi->UnicodeCollationInterface,
            Buffer,
            11,
            VolumeLabel);
    VolumeLabel[11] = 0;
    
//  Update volume Label in vi->Volume
    if (Strlen(VolumeLabel) > 11) return EFI_BAD_BUFFER_SIZE;
    
    vi->UnicodeCollationInterface->FatToStr(vi->UnicodeCollationInterface, 11, VolumeLabel, vi->VolumeID);
    
    for (i=0; i<11; i++) {
        if (vi->VolumeID[i] == 0x20) break;
    }
    
    vi->VolumeID[i] = 0;
    vi->ValidVolumeID = TRUE;
    
//  Check if Volume ID Directory Entry is present. If so Modify it.
    if (!fh->DirList.pHead) ReadAllDirectoryEntries (fh);
    
    dlink = fh->DirList.pHead;
    Status = EFI_NOT_FOUND;
    
    for ( ; dlink; dlink = dlink->pNext) {
        del = OUTTER(dlink, DirLink, DIR_ENTRY_LIST);
        
        if ((del->DirectoryEntry.Dir_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID)) == ATTR_VOLUME_ID) {
        
            pBS->CopyMem(&del->DirectoryEntry.Dir_Name, VolumeLabel, 11);
            
//          Update LastAcc date and Wrtdate/Time and the Attribute
            UpdateAccAndWriteTime (del);
            del->DirectoryEntry.Dir_Attr |= ATTR_ARCHIVE;
            
            if (VolumeLabel[0] == 0x20) del->DirectoryEntry.Dir_Name[0] = 0xE5;
            
            GetSectorAddressDir (fh, del->Cluster, del->Offset, &Sector, &SectorOffset);
            Status = FsWriteMedia (vi, (void *)&del->DirectoryEntry, Sector, SectorOffset, sizeof(DIR_ENTRY_32), DIRECTORY_REGION);
            
            if (EFI_ERROR(Status)) return Status;
            
            if (VolumeLabel[0] == 0x20) RemoveDirList(fh, del);
            
            break;
        }
    }
    
    
    if (Status == EFI_NOT_FOUND && VolumeLabel[0] != 0x20) {
        fh1 = 0;
        CreateDirectoryEntry (fh, vi->VolumeID, &fh1, ATTR_VOLUME_ID |ATTR_ARCHIVE);
        
        if (fh1) RemoveFH(fh1);         // FILE_HANDLE Created is not needed.
    }
    
    return EFI_SUCCESS;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetFileInfoFromFH
//
// Description:     Returns information on a file from it's handle
//
// Parameters:      FILE_HANDLE_INSTANCE *fh1 - Pointer to file handle
//                                              instance
//                  UINTN *BufferSize - Pointer to size of buffer
//                  VOID *Buffer - Ponter to buffer for returned data
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
GetFileInfoFromFH (
    FILE_HANDLE  *Pfh,
    IN OUT UINTN *BufferSize,
    OUT VOID     *Buffer
)
{
    VOLUME_INFO   *vi = Pfh->VolumeInterface;
    EFI_FILE_INFO *buffer = Buffer;
    UINTN         Length;
    
    Length = (UINT32)Wcslen(Pfh->FileNameLFN) * sizeof (CHAR16) + 2;
    Length += EFI_FIELD_OFFSET(EFI_FILE_INFO,FileName);
    
//  Length += sizeof(EFI_FILE_INFO);
    if (*BufferSize < Length) {
#ifdef Debug_GetFileInfo_1
        EfiDebugPrint(-1,"GetFileInfo: %S BufferSize %x LengthRequired %x Status: EFI_BUFFER_TOO_SMALL\n", Pfh->FileNameLFN, *BufferSize, Length + 2);
#endif
        *BufferSize = Length;
        return EFI_BUFFER_TOO_SMALL;
    }
    
    *BufferSize = Length;
    buffer->Size = Length;
    buffer->FileSize = Pfh->DirectoryEntry.Dir_FileSize;
    buffer->PhysicalSize = buffer->FileSize;
    
    Length = (Pfh->DirectoryEntry.Dir_FileSize % vi->BytesPerCluster);
    
    if (Length)
        buffer->PhysicalSize += vi->BytesPerCluster - (Pfh->DirectoryEntry.Dir_FileSize % vi->BytesPerCluster);
        
    FatToEfiTime (&(buffer->CreateTime),       Pfh->DirectoryEntry.Dir_CrtDate,    Pfh->DirectoryEntry.Dir_CrtTime);
    FatToEfiTime (&(buffer->LastAccessTime),   Pfh->DirectoryEntry.Dir_LstAccDate, 0);
    FatToEfiTime (&(buffer->ModificationTime), Pfh->DirectoryEntry.Dir_WrtDate,    Pfh->DirectoryEntry.Dir_WrtTime);
    buffer->Attribute = Pfh->DirectoryEntry.Dir_Attr & EFI_FILE_VALID_ATTR;
    Wcscpy (buffer->FileName, Pfh->FileNameLFN);
#ifdef Debug_GetFileInfo_0
    EfiDebugPrint(-1,"GetFileInfo: %S File Size %lx \n", Pfh->FileNameLFN, buffer->FileSize);
#endif
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       FatToEfiTime
//
// Description:     Converts time/date in FAT format to EFI format
//
// Parameters:      EFI_TIME *EfiTime - Ponter to returned time in EFI format
//                  UINT16 Date - Date in FAT format
//                  UINT16 Time - Time in FAT format
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

VOID
FatToEfiTime (
    EFI_TIME *EfiTime,
    UINT16   Date,
    UINT16   Time
)
{

    EfiTime->Year = (UINT16) (((FAT_DATE*) &Date)->Year + 1980);
    EfiTime->Month = (UINT8 ) ((FAT_DATE*) &Date)->Month;
    EfiTime->Day = (UINT8) ((FAT_DATE*) &Date)->Day;
    EfiTime->Hour = (UINT8) ((FAT_TIME*) &Time)->Hour;
    EfiTime->Minute = (UINT8) ((FAT_TIME*) &Time)->Minute;
    EfiTime->Second = (UINT8) ((FAT_TIME*) &Time)->DoubleSecond;
    EfiTime->Nanosecond = 0;
    EfiTime->TimeZone = EFI_UNSPECIFIED_TIMEZONE;
    EfiTime->Pad1 = 0;
    EfiTime->Daylight = 0;
    EfiTime->Pad2 = 0;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       EfiToFatTime
//
// Description:     Converts date/time in EFI format to FAT format
//
// Parameters:      EFI_TIME EfiTime - Time in EFI format
//                  UINT16 *Date - Pointer to returned date in FAT format
//                  UINT16 *Time - Pointer to returned time in FAT format
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

VOID
EfiToFatTime (
    EFI_TIME EfiTime,
    UINT16   *Date,
    UINT16   *Time
)
{

    ((FAT_DATE*)Date)->Year = EfiTime.Year - 1980;
    ((FAT_DATE*)Date)->Month    = EfiTime.Month;
    ((FAT_DATE*)Date)->Day  = EfiTime.Day;
    ((FAT_TIME*)Time)->Hour = EfiTime.Hour;
    ((FAT_TIME*)Time)->Minute   = EfiTime.Minute;
    ((FAT_TIME*)Time)->DoubleSecond = EfiTime.Second;
    
}

// Special string copy for volume labels.
// Skips the "." that ExtractShortFileName puts in. Replaces Wcscpy().
VOID Labcpy(
    CHAR16 *string1,
    CHAR16 * string2
)
{
    while (*string2) {
        if ((CHAR8)*string2 != '.') {
            *string1++ = *string2++;
            
        } else *string2++;
    }
}

// Special string length counter for volume labels.
// Skips the "." that ExtractShortFileName puts in. Replaces Wcslen().
UINTN Lablen(
    CHAR16 *string
)
{
    UINTN length=0;
    
    while (*string++) {
        if ((CHAR8)*string != '.') length++;
    }
    
    return length;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FindNextTpl
//
// Description: Returns the higher of a desired TPL level or the current
//              next higher TPL level
//
// Parameters:  EFI_TPL TplLevel -- desired level to raise to
//
// Return Value: EFI_TPL
//
// Modified:
//
// Referral(s):
//
// NOTE(S):     
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_TPL
FindNextTpl (
    EFI_TPL     TplLevel
    )
{
    EFI_TPL NextTpl;

    NextTpl = pBS->RaiseTPL (TPL_HIGH_LEVEL);
    pBS->RestoreTPL(NextTpl);\
    if(NextTpl<=TplLevel) NextTpl = TplLevel;
    return NextTpl;
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
