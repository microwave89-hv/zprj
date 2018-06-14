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
// $Header: /Alaska/SOURCE/Core/Modules/FileSystem/Open.c 25    4/30/12 2:02p Pats $
//
// $Revision: 25 $
//
// $Date: 4/30/12 2:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/FileSystem/Open.c $
// 
// 25    4/30/12 2:02p Pats
// [TAG] EIP87352
// [Category] Bug Fix
// [Symptom] FAT Direcotry Opean/Creation Issue
// [RootCause] If a directory open was attempted with EFI_FILE_MODE_CREATE
// set, check for existing directory was not done.
// [Solution] Check for existing directory if opened with
// EFI_FILE_MODE_CREATE set in ProcessOpenFileHandle(). 
// [Files] Open.c
// 
// 24    11/28/11 11:09a Pats
// [TAG] - EIP 75631
// [Category] - BUG FIX
// [Severity] - Major
// [Symptom] - If an application name includes a path, it won't run.
// [Root Cause] - In the function ProcessOpenFileHandle(), the driver
// attempts to replace "\" in the path with a zero, but the code was one
// off, and the character past the "\" was being replaced.
// [Solution] - Modified the function ProcessOpenFileHandle() to replace
// the proper character.
// [Files] - Open.c
// 
// 23    10/24/11 10:55a Artems
// EIP 73254: Remove "magic number" from source
// 
// 22    5/05/11 3:44p Pats
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
// 21    2/05/11 3:20p Artems
// Bug fix - restore original TPL in all branches of OpenFileHandle
// function
// 
// 20    1/13/11 12:24p Pats
// [TAG] - EIP 51705 
// [Category]- BUG FIX
// [Severity]- Major
// [Symptom] - If the volume label is the same name as a directory or
// file, the directory or file cannot be accessed. Also, a new directory
// cannot be created with the same name as the volume.
// [RootCause] - The functions FindMatchingFH() and FindMatchingDirEntry()
// did not check for ATTR_VOLUME_ID.
// [Solution] - Modified above functions to check for ATTR_VOLUME_ID.
// [Files] - open.c
// 
// 19    1/06/11 5:53p Oleksiyy
// [TAG]  		EIP28607 
// [Category]  	Improvement
// [Description]  	System was hanging for some time if Floppy Media
// removed while writing in meda in progress.
// EFI_TPL_CALLBACK priority level rised during media related calls.
// 
// [Files]  		DiskIo.c, Info.c, MediaAccess.c, Open.c, Partition.c
// 
// 18    1/06/11 5:03p Pats
// [TAG] - EIP 49934
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - The new EDKII shell was not displaying filesystem devices
// properly.
// [RootCause] - Root directory file name was "\", with a size of one.
// Shell expected a null name for the root directory.
// [Solution] - Changed root directory name to null.
// [Files] - open.c, function OpenRoot().
// 
// 17    12/03/10 10:08a Pats
// EIP 44532: USB key is not returning file list as expected.
// Problem: ReadFIleHandle was not resetting pointers when a directory
// read returned an error.
// Solution. Changed ReadFileHandle to reset pointers on error condition.
// 
// 16    7/07/10 3:00p Pats
// EIP 38291: Fails Klocwork test.
// Problem: No error return if file handle is null in
// ProcessOpenFileHandle()
// Solution: Added error return.
// Problem: Variable vi initialized improperly.
// Solution: Changed initialization (moved to after possible error exit).
// 
// 15    6/11/10 5:39p Pats
// EIP 39171: Long name sometimes not displayed, only short name.
// FetchLongName() in Open.c did not handle case where long name spilt
// over 2 clusters. Function modified to handle the case.
// 
// 14    1/22/10 4:39p Yul
// Refer to EIP 32983.
// 
// 13    12/17/09 12:44p Felixp
// SCT workaround: CloseFileHandle function is updated to validate input
// parameter before using it (EIP 32474).
// SCT passes handle of the deleted file.
// 
// 12    7/02/09 5:47p Pats
// Updated to latest coding standard. No code changes.
//
// 11    7/30/08 11:36a Pats
// Bug fix for file renaming.
//
// 10    4/13/07 7:07p Pats
// Edited to conform with coding standards. No code changes.
//
// 9     8/24/06 9:32a Felixp
// bug fix in CreateDirEntryInDisk
//
// 8     8/16/06 12:03p Markw
// Fixed UINTN* and UINT32* 64-bit issues.
//
// Fixed VC7.1 warning msg.
//
// 4     6/21/05 4:00p Pats
// Modified to call MarkVolumeDirty when EFI_VOLUME_CORRUPTED error
// occurs. Removed commented-out debug code.
//
// 3     6/21/05 9:57a Pats
// Corrected some spelling to match changes in Info.c.
//
// 2     5/27/05 10:02a Srinin
// Fix for Media change and free space calculation.
//
// 1     4/26/05 6:05p Srinin
//
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: Open.c
//
// Description:  Handles Opening File Handles.
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

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
// Procedure:   OpenVolume
//
// Description: Opens a file system Volume.
//
// Parameters:
//  IN  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This - File System Protocol Instance
//  OUT EFI_FILE_PROTOCOL **Root
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
OpenVolume (
    IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
    OUT EFI_FILE_PROTOCOL              **Root
)
{

    EFI_STATUS           Status;
    FILE_HANDLE          *RootHandle = NULL;
    FILE_HANDLE_INSTANCE *RootInstance = NULL;
    VOLUME_INFO          *VolumeInfo = (VOLUME_INFO *)This;
    FAT_TYPE             Old_FAT_Type = VolumeInfo->FatType;
    UINT32               Length;
    
    if (VolumeInfo->RootFH && (VolumeInfo->VolumeStatus == EFI_MEDIA_CHANGED || VolumeInfo->VolumeStatus == EFI_NO_MEDIA)) {
        FreeUpResources (VolumeInfo, VolumeInfo->VolumeStatus); // Media changed occurred earlier
    }
    
    if (VolumeInfo->RootFH) {
        if (VolumeInfo->BlkIo->Media->RemovableMedia) {
            Status = DetectVolume(VolumeInfo, TRUE); // Just reads the sector 0
            
            if (EFI_ERROR(Status)) {
                FreeUpResources (VolumeInfo, Status);
                goto ContinueOpen;
            }
        }
        
        RootHandle = VolumeInfo->RootFH;  // Everything is fine
        
    } else {
ContinueOpen:
        VolumeInfo->VolumeStatus = EFI_UNSUPPORTED;
        VolumeInfo->BlockSize = VolumeInfo->BlkIo->Media->BlockSize;
        VolumeInfo->ReadOnly = VolumeInfo->BlkIo->Media->ReadOnly;
        VolumeInfo->MediaID = VolumeInfo->BlkIo->Media->MediaId;
        Status = DetectVolume(VolumeInfo, FALSE);
        
        if (EFI_ERROR(Status)) return Status;
        
        if (Old_FAT_Type && Old_FAT_Type != VolumeInfo->FatType) return EFI_UNSUPPORTED;
        
//  Create a FILE_HANDLE for Root Directory. Called for the first time.
//  VolumeInfo->VolumeSize = VolumeInfo->TotalSectors * VolumeInfo->VolumeBPB.BPB_BytePerSec;
//  Only count Data Sectors when determining Volume Size, to match DOS
        VolumeInfo->VolumeSize = Mul64((UINT64)VolumeInfo->DataSectors, (UINT32)VolumeInfo->VolumeBPB.BPB_BytePerSec);
        VolumeInfo->FreeSpaceinClusters = (UINTN)-1; // Means not calculated yet
        VolumeInfo->FreeSpaceinSector1 = (UINTN)-1;
        Status= OpenRoot(VolumeInfo, &RootHandle);
        VolumeInfo->LastFreeCluster = (UINTN)-1;
        
        if (EFI_ERROR(Status)) return Status;
        
        VolumeInfo->RootFH = RootHandle;
		DListAdd((DLIST *)(UINTN)&(VolumeInfo->OpenFHs),(DLINK *)(UINTN)&(RootHandle->ViFHLink)); 
    }
    
    if (!VolumeInfo->FileSystemName) {
        Status = pBS->AllocatePool (EfiBootServicesData, 80, (VOID**)&VolumeInfo->FileSystemName);
        Wcscpy (VolumeInfo->FileSystemName, L"FAT");
        Length = (UINT32) Wcslen(VolumeInfo->FileSystemName);
        
        switch (VolumeInfo->FatType) {
            case  FAT12:
                Wcscpy (VolumeInfo->FileSystemName + Length, L"12 ");
                break;
            case  FAT16:
                Wcscpy (VolumeInfo->FileSystemName + Length, L"16 ");
                break;
            case  FAT32:
                Wcscpy (VolumeInfo->FileSystemName + Length, L"32 ");
                break;
            default:
                Wcscpy (VolumeInfo->FileSystemName + Length, L"UnKnown ");
        };
        
        Length = (UINT32) Wcslen(VolumeInfo->FileSystemName);
        
        Wcscpy (VolumeInfo->FileSystemName + Length, L"File System [");
        
        Length = (UINT32) Wcslen(VolumeInfo->FileSystemName);
        
        if (VolumeInfo->VolumeSize < 0x100000)  { //Less than 1MB
            ItowEx(Shr64 (VolumeInfo->VolumeSize, 10), VolumeInfo->FileSystemName + Length, 10, FALSE);
            Length = (UINT32) Wcslen(VolumeInfo->FileSystemName);
            Wcscpy (VolumeInfo->FileSystemName + Length, L"KB]");
            
        } else if (VolumeInfo->VolumeSize < 0x40000000)  { //Less than 1GB
            ItowEx(Shr64 (VolumeInfo->VolumeSize, 20), VolumeInfo->FileSystemName + Length, 10, FALSE);
            Length = (UINT32) Wcslen(VolumeInfo->FileSystemName);
            Wcscpy (VolumeInfo->FileSystemName + Length, L"MB]");
            
        } else {
            ItowEx(Shr64 (VolumeInfo->VolumeSize, 30), VolumeInfo->FileSystemName + Length, 10, FALSE);
            Length = (UINT32) Wcslen(VolumeInfo->FileSystemName);
            Wcscpy (VolumeInfo->FileSystemName + Length, L"GB]");
        }
    }
    
    
//  Create a FILE_HANDLE_INSTANCE
    Status = CreateFileHandleInstance(RootHandle, &RootInstance, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE);
    
//  Return FILE_HANDLE_INSTANCE
    if (Status == EFI_SUCCESS) *Root = (EFI_FILE_PROTOCOL *)RootInstance;
    
    VolumeInfo->VolumeStatus = Status;
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure: OpenRoot
//
// Description: Opens the Root Directory on the Volume.
//
// Parameters:
//  IN VOLUME_INFO        *VolumeInfo - Volume Info Structure
//  IN OUT FILE_HANDLE    **Root - Root directory handle
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
OpenRoot(
    IN VOLUME_INFO     *VolumeInfo,
    IN OUT FILE_HANDLE **Root
)
{

    EFI_STATUS  Status;
    FILE_HANDLE *RootHandle;
    
    Status = fsAllocateMemory(VolumeInfo, sizeof(FILE_HANDLE), (VOID**)&RootHandle, TRUE);
    
    if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;
    
    Status = fsAllocateMemory(VolumeInfo, 4, (VOID**)&(RootHandle->FileNameLFN), FALSE);
    
    RootHandle->FileNameLFN[0]= 0;
    RootHandle->ROOTDIR = TRUE;
    RootHandle->VolumeInterface = VolumeInfo;
    RootHandle->DirectoryEntry.Dir_Attr =  EFI_FILE_DIRECTORY;
    RootHandle->HandleStatus=  EFI_SUCCESS;
    
    if (VolumeInfo->FatType == FAT32) {
        RootHandle->DirCluster = VolumeInfo->VolumeBPB.BPB_FAT.BPB_FAT32.BPB_RootClus;
        RootHandle->DirOffset = 0;
    }
    
	DListInit((DLIST *)(UINTN)&(RootHandle->DirList));
    *Root = RootHandle;
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   CreateFileHandleInstance
//
// Description: Creates an instance of a file handle
//
// Parameters:
//  IN FILE_HANDLE              *fh - Handle of the file to work on
//  IN OUT FILE_HANDLE_INSTANCE **fhi - File handle instance
//  IN UINT64                   OpenMode - Open mode (read, write, both)
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CreateFileHandleInstance (
    IN FILE_HANDLE              *fh,
    IN OUT FILE_HANDLE_INSTANCE **fhi,
    IN UINT64                   OpenMode
)
{

    EFI_STATUS           Status;
    VOLUME_INFO          *Vi = fh->VolumeInterface;
    FILE_HANDLE_INSTANCE *nfi;
    
    Status = fsAllocateMemory(Vi, sizeof(FILE_HANDLE_INSTANCE), (VOID**)&nfi, TRUE);
    
    if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;
    
    nfi->Position = 0;
    nfi->HandleInstanceStatus = EFI_SUCCESS;
    nfi->CurrentCluster = FIRSTCLUSTER(fh->DirectoryEntry);
    nfi->pFH = fh;
    nfi->OpenMode = OpenMode;
    InitEFIFileInterface(&(nfi->FileHandle));
    fh->InstancesCount++;
	DListAdd((DLIST *)(UINTN)&(Vi->OpenFIs), (DLINK *)(UINTN)&(nfi->ViFILink));
    *fhi = nfi;
    return EFI_SUCCESS;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   InitEFIFileInterface
//
// Description: Initializes the EFI_FILE_PROTOCOL interface
//
// Parameters:
//  EFI_FILE_PROTOCOL *EFIFileInterface - Interface structure
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: OpenProtocol CloseProtocol
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

void
InitEFIFileInterface (
    EFI_FILE_PROTOCOL *EFIFileInterface
)
{

    EFIFileInterface->Revision = SIMPLE_FILE_SYSTEM_DRIVER_VERSION;
    EFIFileInterface->Open = OpenFileHandle;
    EFIFileInterface->Close = CloseFileHandle;
    EFIFileInterface->Delete = DeleteFileHandle;
    EFIFileInterface->Read = ReadFileHandle;
    EFIFileInterface->Write = WriteFileHandle;
    EFIFileInterface->GetPosition = GetPositionFileHandle;
    EFIFileInterface->SetPosition = SetPositionFileHandleThis;
    EFIFileInterface->GetInfo = GetInfoFileHandle;
    EFIFileInterface->SetInfo = SetInfoFileHandle;
    EFIFileInterface->Flush = FlushFileHandle;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   OpenFileHandle
//
// Description: Opens a file handle (when a file is opened)
//
// Parameters:
//  IN EFI_FILE_PROTOCOL  *This - File System Protocol instance
//  OUT EFI_FILE_PROTOCOL **NewHandle - Handle of open file
//  IN CHAR16             *FileName - Unicode name of file
//  IN UINT64             OpenMode - Open mode (read, write, both)
//  IN UINT64             Attributes - Attributes of open file
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
OpenFileHandle (
    IN EFI_FILE_PROTOCOL  *This,
    OUT EFI_FILE_PROTOCOL **NewHandle,
    IN CHAR16             *FileName,
    IN UINT64             OpenMode,
    IN UINT64             Attributes
)
{

    EFI_STATUS           Status;
    FILE_HANDLE_INSTANCE *Fi= (FILE_HANDLE_INSTANCE *) This;
	FILE_HANDLE				*ParentFh;
	VOLUME_INFO				*Vi;
    EFI_TPL                 SaveTpl;
    EFI_TPL                 NextTpl;
#ifdef Debug_OpenFile
    EfiDebugPrint(-1,"OpenFile: %S OpenMode %lx Attribute %lx\n", FileName, OpenMode, Attributes);
#endif
    
//  Validate Inputs
    switch (OpenMode) {
        case (EFI_FILE_MODE_READ):
        case (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE):
        case (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE):
            break;
        default:
            return EFI_INVALID_PARAMETER;
    }
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);
	Status = ValidateCurrentStatus (Fi);
	if (EFI_ERROR(Status)) 
    {
        pBS->RestoreTPL(SaveTpl);
        return Status;
    }
    ParentFh = Fi->pFH;
    Vi = ParentFh->VolumeInterface;
	if (Vi->ReadOnly && OpenMode & EFI_FILE_MODE_WRITE) 
    {
        pBS->RestoreTPL(SaveTpl);
        return EFI_WRITE_PROTECTED;
    }
    if (FileName == NULL) 
    {
        pBS->RestoreTPL(SaveTpl);
        return EFI_NOT_FOUND;
    }
    if ( Attributes & ~EFI_FILE_VALID_ATTR) 
    {
        pBS->RestoreTPL(SaveTpl);
        return EFI_NOT_FOUND;
    }
    Status = ProcessOpenFileHandle (Fi, &FileName, NewHandle, OpenMode, Attributes);
    pBS->RestoreTPL(SaveTpl);    
#ifdef Debug_OpenFile
    EfiDebugPrint(-1,"OpenFile Status:  %x\n", Status);
#endif
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ReadFileHandle
//
// Description: Read from a file (normal file or directory)
//
// Parameters:
//  IN EFI_FILE_PROTOCOL *This - File System Protocol instance
//  IN OUT UINTN         *BufferSize - Size of read buffer
//  OUT VOID             *Buffer - Points to read buffer
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ReadFileHandle (
    IN EFI_FILE_PROTOCOL *This,
    IN OUT UINTN         *BufferSize,
    OUT VOID             *Buffer
)
{

    EFI_STATUS              Status = EFI_UNSUPPORTED;
    FILE_HANDLE_INSTANCE    *fhi = (FILE_HANDLE_INSTANCE *)This;
	FILE_HANDLE				*Pfh;
	FILE_HANDLE				*fh1; 
	DIR_ENTRY_LIST			*Del;
	UINT32					Position;
    FILE_HANDLE_INSTANCE    TempFhi;
    FILE_HANDLE             TempPfh;
    EFI_TPL                 SaveTpl;
    EFI_TPL                 NextTpl;

    if (*BufferSize > 0xffffffff) return EFI_INVALID_PARAMETER;

    TempFhi = *fhi;
	Status = ValidateCurrentStatus (fhi);
	if (EFI_ERROR(Status)) return Status;
    Pfh = fhi->pFH;
    TempPfh = *Pfh;
#ifdef Debug_ReadFile
	EfiDebugPrint(TRACE_ALWAYS,"ReadFile: %S Position %lx Length %x \n", Pfh->FileNameLFN, fhi->Position, *BufferSize);
#endif
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);

//  Check if this Instance is a Directory.
    if (Pfh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY) {
    
//  Check if Dir List has been changed. If so, release the list and read it again.
        if (Pfh->DirListChanged == TRUE) {
            RemoveAllDirList (Pfh);
            Pfh->DirListChanged = FALSE;
        }
        
//  Check if the file Handle has a valid DIR_ENTRY_LIST
        if (!Pfh->DirList.pHead) {
            Status = ReadAllDirectoryEntries (Pfh);
            
            if (EFI_ERROR(Status)) {
                pBS->RestoreTPL(SaveTpl);
                return Status;
            }
        }
        
//  If Dir_List has been changed, this should take care of it.
        if (fhi->Position != 0) {
            Status = LocateDel (Pfh->DirList.pHead, fhi->CurrentCluster, fhi->CurrentClusterOffset, &Del, &Position);
            fhi->Position = Position;
        }
        
        
        for (;; fhi->Position++) {
            Status = GetDirListAtPosition (Pfh, fhi->Position, &Del);
            
            if (!Del) {
                *BufferSize = 0;    //  End of entries
                pBS->RestoreTPL(SaveTpl);
                return EFI_SUCCESS;
            }
            
//    Check whether it is a Label
            if ((Del->DirectoryEntry.Dir_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID)) != ATTR_VOLUME_ID)
                break;
        }
        
///////////////////////////////////////////////
//A long Process. Do we need to reduce it
        Status = CreateFHFromDirEntryList(Del, Pfh, &fh1);
        
        if (EFI_ERROR(Status)){
            pBS->RestoreTPL(SaveTpl);
            return Status;
        }
        
        Status = GetFileInfoFromFH (fh1, BufferSize, Buffer);

        if (EFI_ERROR(Status)) {
            *fhi = TempFhi;
            *Pfh = TempPfh;
            pBS->RestoreTPL(SaveTpl);
            return Status;
        }

//A long Process. Do we need to reduce it
///////////////////////////////////////////////

        fhi->Position++;
        
//  Make sure CurrentCluster and CurrentClusterOffset gets updated to the new position
        for (;; fhi->Position++) {
            Status = GetDirListAtPosition (Pfh, fhi->Position, &Del);
            
            if (!Del) break;
            
//    Check whether it is a Label
            if ((Del->DirectoryEntry.Dir_Attr & (ATTR_DIRECTORY | ATTR_VOLUME_ID)) != ATTR_VOLUME_ID)
                break;
        }
        
//  Update the CurrentCluster, CurrentClusterOffset for the new position
        if (Del) {
            fhi->CurrentCluster =  Del->Cluster;
            fhi->CurrentClusterOffset = Del->Offset;
            
        } else {
            fhi->CurrentCluster = (UINTN) -1;
            fhi->CurrentClusterOffset = (UINTN)-1;
            Status = EFI_SUCCESS;
        }
        
        RemoveFH(fh1);
        
    } else {
//  It is File.
        //Buffer size is on input is required to be less than 4G.
        Status = ReadFromFile (fhi, Buffer, (UINT32*)BufferSize, DATA_REGION);
    }
    pBS->RestoreTPL(SaveTpl);
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   WriteFileHandle
//
// Description: Writes to a file
//
// Parameters:
//  IN EFI_FILE_PROTOCOL *This,
//  IN OUT UINTN         *BufferSize,
//  IN VOID              *Buffer
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
WriteFileHandle (
    IN EFI_FILE_PROTOCOL *This,
    IN OUT UINTN         *BufferSize,
    IN VOID              *Buffer
)
{
    EFI_TPL              SaveTpl;
    EFI_TPL              NextTpl;
    EFI_STATUS           Status;
    FILE_HANDLE_INSTANCE *fhi = (FILE_HANDLE_INSTANCE *)This;
    
#ifdef Debug_WriteFile
	FILE_HANDLE				*Pfh;
	VOLUME_INFO				*vi;
#endif

    if (*BufferSize > 0xffffffff) return EFI_INVALID_PARAMETER;

	Status = ValidateCurrentStatus (fhi);
	if (EFI_ERROR(Status)) return Status;
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);
#ifdef Debug_WriteFile
	Pfh = fhi->pFH;
	vi = Pfh->VolumeInterface;	
	EfiDebugPrint(TRACE_ALWAYS,"WriteFile: %S FSize %x Pos %lx Len %x LoCluster %x\n", 
				Pfh->FileNameLFN, Pfh->DirectoryEntry.Dir_FileSize, fhi->Position, *BufferSize, Pfh->DirectoryEntry.Dir_FstClusLO);
#endif
     
	Status = CheckFileWrite (fhi, FALSE);
    if (EFI_ERROR(Status)){
        pBS->RestoreTPL(SaveTpl); 
        return Status;
    }
    
    //Buffer size is on input is required to be less than 4G.
    Status = WriteToFile (fhi, Buffer, (UINT32*)BufferSize, DATA_REGION);
    pBS->RestoreTPL(SaveTpl);
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   SetInfoFileHandle
//
// Description: Sets file info
//
// Parameters:
//  IN EFI_FILE_PROTOCOL  *This,
//  IN EFI_GUID           *InformationType,
//  IN UINTN              BufferSize,
//  IN VOID               *Buffer
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SetInfoFileHandle(
    IN EFI_FILE_PROTOCOL *This,
    IN EFI_GUID          *InformationType,
    IN UINTN             BufferSize,
    IN VOID              *Buffer
)
{


    EFI_STATUS           Status = EFI_UNSUPPORTED;
    FILE_HANDLE_INSTANCE *fhi = (FILE_HANDLE_INSTANCE *)This;
	FILE_HANDLE				*Pfh;
	VOLUME_INFO				*vi;	
    EFI_TPL                 SaveTpl;
    EFI_TPL                 NextTpl;

	Status = ValidateCurrentStatus (fhi);
	if (EFI_ERROR(Status)) return Status;
    Pfh = fhi->pFH;
    vi = Pfh->VolumeInterface;
	if (vi->ReadOnly) return EFI_WRITE_PROTECTED;
    
//  Compare the GUID
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);
    if (!guidcmp(InformationType, &gEfiFileInfoGuid)) {
        Status = SetfileInfo (This, fhi, BufferSize, Buffer);
        
        if (EFI_ERROR(Status)){
            pBS->RestoreTPL(SaveTpl);
            return Status;
        }
    }
    
    else {
        if (!guidcmp(InformationType, &gEfiFileSystemInfoGuid)) {
            Status = SetSystemInfo (vi, BufferSize, (EFI_FILE_SYSTEM_INFO *)Buffer);
            
            if (EFI_ERROR(Status)){
                pBS->RestoreTPL(SaveTpl);
                return Status;
            }
            
            Status = FlushFileHandle(This);
            
            if (EFI_ERROR(Status)){
                pBS->RestoreTPL(SaveTpl);
                return Status;
            }
            
        } else {
            if (!guidcmp(InformationType, &gEfiFileSystemVolumeLabelGuid)) {
                Status = SetVolumeLabel (vi, BufferSize, Buffer);
                
                if (EFI_ERROR(Status)){
                    pBS->RestoreTPL(SaveTpl);
                    return Status;
                }
                
                Status = FlushFileHandle(This);
                
                if (EFI_ERROR(Status)) {
                    pBS->RestoreTPL(SaveTpl);
                    return Status;
                }
                
            } else {
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
// Procedure:   DeleteFileHandle
//
// Description: Deletes a file
//
// Parameters:
//  IN EFI_FILE_PROTOCOL *This - File Protocol instance
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes: For FAT32, Cluster(s) occupied by root directory will not be released
//      as Del/rm command will not give a call to delete RootHandle.
//      In a empty FAt32 disk, free space will be less by clusters occupied by ROOT Directory
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
DeleteFileHandle (
    IN EFI_FILE_PROTOCOL *This
)
{

    EFI_STATUS           Status;
    FILE_HANDLE_INSTANCE *fhi = (FILE_HANDLE_INSTANCE *)This, *fhi1;
	FILE_HANDLE				*fh;
	FILE_HANDLE				*PPfh;
	VOLUME_INFO				*vi;	
	UINT32					ClusterCount;
//	UINT32					Sector, SectorOffset, ClusterCount;
	UINT8					DirErase = DIR_ENTRY_ERASE;
	DLINK					*dlink;
	DIR_ENTRY_LIST			*Del;
	UINT32					Position;
    EFI_TPL                 SaveTpl;
    EFI_TPL                 NextTpl;

	Status = ValidateCurrentStatus (fhi);
	if (EFI_ERROR(Status)) return Status;

    fh = fhi->pFH;
    vi = fh->VolumeInterface;
    PPfh = fh->Parent;
    dlink = PPfh->DirList.pHead ;

#ifdef Debug_DeleteFile
	EfiDebugPrint(TRACE_ALWAYS,"Del File: %S Dir Cluster %x Dir Offset %x\n", fh->FileNameLFN, fh->DirCluster, fh->DirOffset);
#endif
    

	if ( vi->ReadOnly || fh->ROOTDIR 
       || fh->DirectoryEntry.Dir_Attr & ATTR_READ_ONLY
       || !(fhi->OpenMode & EFI_FILE_MODE_WRITE)){

        CloseFileHandle (This);
        
#ifdef Debug_DeleteFile
        EfiDebugPrint(-1,"DEL WARN FAILURE Instances Open %x\n", fh->InstancesCount);
#endif
        return EFI_WARN_DELETE_FAILURE;
    }
    
    if (fh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY) {
        if (fh->DirList.Size > 2) {
            CloseFileHandle (This);
#ifdef Debug_DeleteFile
            EfiDebugPrint(-1,"DEL WARN FAILURE Dir Not Empty\n");
#endif
            return EFI_WARN_DELETE_FAILURE;
        }
        
//###DEBUG
//  TODO TODO TODO
//  Before removing the Directory Entry, check if it is empty.
//  TODO TODO TODO
//##DEBUG END
//    Release all Dir_List
        RemoveAllDirList(fh);
    }
    
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);
    
    if (fh->DirCluster || fh->DirOffset) {
        fh->DirectoryEntry.Dir_Name[0] = DirErase;
        fh->DirEntryChanged = TRUE;
//  Update the FAT Chain
        UnlinkFat(vi, FIRSTCLUSTER(fh->DirectoryEntry), &ClusterCount);
    }
    
//  Check if DIR_LIST is valid. If yes, remove from the list.
    Status = LocateDel (fh->Parent->DirList.pHead, fh->DirCluster, fh->DirOffset, &Del, &Position);
    
    if (!EFI_ERROR(Status)) RemoveDirList(PPfh, Del);
    
//  Force next Scan for the parent directory to begin from the beginning
    fh->Parent->FreeDirEntryCluster = 0;
    fh->Parent->FreeDirEntryOffset = 0;
    
//  Remove File Handle and File List
    CloseFileHandle (This);
    
//  Check for multiple instances
    if (fh->InstancesCount ) {
        dlink = vi->OpenFIs.pHead;
        
        for ( ; dlink; ) {
            fhi1 = OUTTER(dlink, ViFILink, FILE_HANDLE_INSTANCE);
            
            if (fhi1->pFH == fh) {
                fhi1->HandleInstanceStatus = EFI_NOT_FOUND;
                fhi1->pFH = NULL;
                fh->InstancesCount--;
            }
            
            dlink = dlink->pNext;
        }
    }
    
    Status = RemoveFH(fh);
    pBS->RestoreTPL(SaveTpl);    
#ifdef Debug_DeleteFile
    EfiDebugPrint(-1,"Del File Success\n");
#endif
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FlushFileHandle
//
// Description: Flushes a file (writes any portion left in cache)
//
// Parameters:
//  IN EFI_FILE_PROTOCOL *This - File Protocol instance
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FlushFileHandle (
    IN EFI_FILE_PROTOCOL *This
)
{

    EFI_STATUS           Status;
    FILE_HANDLE_INSTANCE *fhi = (FILE_HANDLE_INSTANCE *)This;
	FILE_HANDLE				*Pfh;
	VOLUME_INFO				*vi;
	DLINK					*dlink;
	CACHE_HEADER			*ch;
    EFI_TPL                 SaveTpl;
    EFI_TPL                 NextTpl;

	Status = ValidateCurrentStatus (fhi);
	if (EFI_ERROR(Status)) return Status;

    Pfh =fhi->pFH;
    vi = Pfh->VolumeInterface;
    dlink = vi->CacheList.pHead;
    if (fhi->OpenMode == EFI_FILE_MODE_READ) return EFI_ACCESS_DENIED;
    
    if (vi->ReadOnly) return EFI_ACCESS_DENIED;
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);
    for ( ; dlink; ) {
    
        ch = OUTTER(dlink, CacheLink, CACHE_HEADER);
        
        if (ch->DIRTY_FLAG) {
            Status= vi->DiskIo->WriteDisk (vi->DiskIo, vi->MediaID, ch->AbsoluteOffset, (UINT32) (ch->AbsoluteOffsetEnd - ch->AbsoluteOffset), ch->Buffer);
            
            if (EFI_ERROR(Status)) {
                HandleDiskIoError(vi, Status);
                pBS->RestoreTPL(SaveTpl);
                return Status;
            }
            
            ch->DIRTY_FLAG = FALSE;
        }
        
        dlink = dlink->pNext;
        
    }
    pBS->RestoreTPL(SaveTpl);
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ProcessOpenFileHandle
//
// Description: Performs whatever is needed to process an open handle
//              (create dir. entry, create instance, allocate clusters)
//
// Parameters:
//  IN  FILE_HANDLE_INSTANCE  *ParentFi - Parent file handle instance
//  IN  CHAR16                **FileName - Unicode file name
//  OUT EFI_FILE_PROTOCOL     **NewHandle - New file handle
//  IN UINT64                 OpenMode - Open mode (read, write, both)
//  IN UINT64                 Attributes - File attributes
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ProcessOpenFileHandle(
    IN FILE_HANDLE_INSTANCE *Fi,
    IN CHAR16               **FileName,
    OUT EFI_FILE_PROTOCOL   **NewHandle,
    IN UINT64               OpenMode,
    IN UINT64               Attributes
)
{

    EFI_STATUS           Status;
    FILE_HANDLE          *fh = Fi->pFH, *fh1;
    VOLUME_INFO          *Vi = fh->VolumeInterface;
    CHAR16               *Next;
    UINT32               Length;
    CHAR16               NextCompName[MAX_TOTAL_PATH_LENGTH];
    FILE_HANDLE_INSTANCE *fhi;
    DIR_ENTRY_LIST       *Del;
    CHAR16               CurrentDir[] = {'.', 0};
    CHAR16               ParentDir[] = {'.', '.', 0};
    UINT8                *Buffer;
    BOOLEAN              DirFound = FALSE;

    if (EFI_ERROR(fh->HandleStatus)) return fh->HandleStatus;
    
    Next = *FileName;
    
    if ((*FileName)[0] == '\\') {
        fh = Vi->RootFH;
        (*FileName) += 1;
    }
    
//  Check for '\\' at the end of the FileName. If so remove it. Eg: \windows\system
    Length = (UINT32) Wcslen(*FileName);
    
    if (Length > 2 && (*FileName)[Length-1] == '\\') (*FileName)[Length-1] = 0;
    
    Status = EFI_SUCCESS;
    
    while (!          EFI_ERROR(Status)) {
    
        if (          EFI_ERROR(GetNextCompName (FileName, NextCompName))) return EFI_NOT_FOUND;
        
        if (NextCompName[0] == 0) break;
        
        if (!FatLfnIsValid (NextCompName)) return EFI_NOT_FOUND;
        
        if (!Wcscmp(NextCompName, CurrentDir)) continue;
        
        if (!Wcscmp(NextCompName, ParentDir)) {
            if (fh == Vi->RootFH) {
                Status = EFI_NOT_FOUND;
                break;
            }
            
            fh = fh->Parent;
            
            if (!fh) {
                Status = EFI_NOT_FOUND;
                break;
            }
            
            continue;
        }
        
//  A component name is present. Parent should be directory. Else return error
        if (!(fh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY)) {
            Status = EFI_NOT_FOUND;
            break;
        }
        
//  Check whether a match can be found for nextcompname
        if (FindMatchingFH(Vi, NextCompName, fh, &fh1)) {
            fh = fh1;
            Status = EFI_SUCCESS;
            continue;
        }
        
//  See if the Linked List is Valid
        if (!fh->DirList.pHead) {
            ReadAllDirectoryEntries (fh);
            
            if (EFI_ERROR(Status)) return Status;
        }
        
        Status = EFI_NOT_FOUND;
        
        DirFound = FALSE;
        if (FindMatchingDirEntry (fh, NextCompName, &Del)) {
            DirFound = TRUE; // Flag existing directory found
            Status = CreateFHFromDirEntryList(Del, fh, &fh1);
            
            //  Add to the List in Volume Interface
            if (Status == EFI_SUCCESS) {
                fh = fh1;
            }
        }
    }
    
    if (EFI_ERROR(Status)) {
    
//  Make sure NextCompName is the last compname.
        if ((*FileName[0]) != 0) return EFI_NOT_FOUND;
        
//  If it is a file that needs to be openend, and not found create one. For directories return error.
        if (OpenMode & EFI_FILE_MODE_CREATE) {

            if (!fh) return EFI_NOT_FOUND;

            if (!(fh->DirectoryEntry.Dir_Attr & ATTR_DIRECTORY)) {
                // if this is not a directory then the input is just a filename. So get the parent handle of this instance
                fh = fh->Parent;
            }

//    Create a file entry in the parent directory
            Status = CreateDirectoryEntry (fh, NextCompName, &fh1, Attributes);
            
            if (EFI_ERROR(Status)) return Status;
            
            fh = fh1;
            
        } else return EFI_NOT_FOUND;
    }
    
//  Create an instance
    Status = CreateFileHandleInstance (fh, &fhi, OpenMode);
    *NewHandle = (EFI_FILE_PROTOCOL *) fhi;
    
//  If asked to create a directory, and it already exists, the UEFI spec says to
//  just open and return EFI_SUCCESS.
    if (DirFound && (OpenMode & EFI_FILE_MODE_CREATE)) {
        return EFI_SUCCESS;
    }

    if ((fhi->pFH->DirectoryEntry.Dir_Attr == ATTR_DIRECTORY) &&
            (OpenMode & EFI_FILE_MODE_CREATE)) { // If creating a new directory, create dot and dotdot entries

//  Allocate Cluster for the sub Directory that was created before.
//  The new allocated cluster should be cleared.
//  fsAllocateMemory (Vi, Vi->BytesPerCluster, (void **)&Buffer, TRUE);
        GetTempBuffer (Vi, &Buffer);
        Zeromemory (Buffer, Vi->BytesPerCluster);
        Length = Vi->BytesPerCluster;
        Status = WriteToFile (fhi, Buffer, &Length, DIRECTORY_REGION);
        
        if (EFI_ERROR(Status)) return Status;
        
//  fsDeAllocateMemory(Vi, Buffer);
        ReleaseTempBuffer(Vi);
        
        fhi->Position = 0;
        fhi->pFH->DirectoryEntry.Dir_FileSize = 0;
        
        if (fhi->pFH->DirEntryChanged == TRUE) UpdateDirListFromFHDir(fhi->pFH);
        
        fhi->pFH->DirEntryChanged = FALSE;
        fhi->pFH->FreeDirEntryCluster = FIRSTCLUSTER(fh->DirectoryEntry);
        fhi->pFH->FreeDirEntryOffset = 0;
        
//  Create '.' entry
        Status = CreateDirectoryEntry(fh, CurrentDir, &fh1, ATTR_DIRECTORY);
        
        if (EFI_ERROR(Status)) return Status;
        
        RemoveFH(fh1);
        
//  Create'..' entry
        Status = CreateDirectoryEntry(fh, ParentDir, &fh1, ATTR_DIRECTORY);
        
        if (EFI_ERROR(Status)) return Status;
        
        RemoveFH(fh1);
        
    }
    
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ReadAllDirectoryEntries
//
// Description: Reads entries in a directory
//
// Parameters:
//  IN FILE_HANDLE    *fh - File handle structure
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadFileHandle, ProcessOpenFileHandle
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ReadAllDirectoryEntries (
    IN FILE_HANDLE *fh
)
{

    EFI_STATUS  Status;
    CHAR16      lfn[256], *lfnBuffer;
    UINT32      Offset, SlotNumber = 0, BufferSize, OrgBufferSize, Slots;
    UINT32      BytesReadPerLoop;
    UINT8       *Buffer;
    VOLUME_INFO *Vi = fh->VolumeInterface;
    UINT32      ClusterNumber, Cluster;
    
    if (Vi->TotalDirEntryList > DIRECTORTY_ENTRIES_CACHED) FreeUpDirEntries (Vi, NULL);
    
// Allocate space for a temp buffer.
    BytesReadPerLoop = Vi->BytesPerCluster;
    
    if (fh->ROOTDIR && (Vi->FatType != FAT32))
        BytesReadPerLoop = Vi->RootDirSectorCount << Vi->BytesPerSecPowerof2;
        
    GetTempBuffer (Vi, &Buffer);
    
    for (ClusterNumber = 0; ; ClusterNumber++, Cluster = 0) {
    
        Status = ReadClusterOfDirectoryEntries(fh, ClusterNumber, &Cluster, Buffer, &BytesReadPerLoop);
        
        if (Status == EFI_SUCCESS && BytesReadPerLoop == 0) {
            break;      // Empty Directory or End of Directory reached
        }
        
        if (EFI_ERROR(Status)) break;
        
        OrgBufferSize = BytesReadPerLoop;
        BufferSize = BytesReadPerLoop;
        Offset = 0;
        
        for ( ; BufferSize; Offset += sizeof (DIR_ENTRY_32), BufferSize = OrgBufferSize - Offset) {
        
            if (!(FindShortName (Buffer, &Offset, BufferSize))) break;
            
//    Find a matching LFN
            Slots = FetchLongName(fh, (DIR_ENTRY_32 *)(Buffer), Offset, lfn, ClusterNumber, BytesReadPerLoop);
            
            if (Slots == 0) ExtractShortFileName (Vi, lfn, Buffer + Offset);
            
            Status = fsAllocateMemory (Vi, (UINT32)((Wcslen(lfn) * sizeof (CHAR16))+ 2), (VOID**)&lfnBuffer, FALSE);
            pBS->CopyMem (lfnBuffer, lfn, (Wcslen(lfn) * sizeof (CHAR16))+ 2);
            
//    Create a Dir Entry List and add it to the Parent File Handle
//    Valid Entry has been found. *lfn, DirectoryEntry, Offset
            AddToDirList (fh, *(DIR_ENTRY_32 *)(Buffer + Offset), lfnBuffer, Cluster, Offset, SlotNumber);
            SlotNumber++;
        }
        
        if (Offset == -1) break;          // No more directory Entries.
        
        if (fh->ROOTDIR && (Vi->FatType != FAT32)) break; // Only one loop.
    }
    
    ReleaseTempBuffer (Vi);
    
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ReadClusterOfDirectoryEntries
//
// Description: Reads one cluster of directory entries
//
// Parameters:
//  IN FILE_HANDLE    *fh,
//  IN UINT32         ClusterNumber -- 0-based number of which cluster to read
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadAllDirectoryEntries
//
// Notes: For end of cluster, BufferSize = 0 and EFI_SUCCESS returned.
//      For FAT12/16, All the Root Directories are read in one shot.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ReadClusterOfDirectoryEntries (
    IN FILE_HANDLE *fh,
    IN UINT32      ClusterNumber,
    OUT UINT32     *ClusterRead,
    UINT8          *Buffer,
    UINT32         *BufferSize
)
{
    EFI_STATUS  Status;
    VOLUME_INFO *Vi = fh->VolumeInterface;
    UINT32      Cluster;
    UINT32      Sector;
    UINT32      i;
    
// Find the starting sector of the cluster to read.
    Cluster = FIRSTCLUSTER(fh->DirectoryEntry);
    
    if (fh->ROOTDIR && (Vi->FatType != FAT32)) {
//        Offset = ClusterNumber * (UINT32)Vi->VolumeBPB.BPB_SecPerClus;
//        if(Offset >= Vi->RootDirSectorCount) return EFI_NOT_FOUND; // Requested cluster is beyond directory
        if (ClusterNumber) {
            *BufferSize = 0;
            return EFI_SUCCESS; // For FAT12/16 root dir, Clusternumber should be always zero.
        }
        
        Sector = Vi->VolumeBPB.BPB_RsvdSecCnt + Vi->FATSz * Vi->VolumeBPB.BPB_NumFATs;
        *ClusterRead  = Sector;
        
    } else {
        if (Vi->FatType == FAT32 && fh->ROOTDIR) Cluster = Vi->VolumeBPB.BPB_FAT.BPB_FAT32.BPB_RootClus;
        
        if (ClusterNumber != 0) {
            for (i=0; i<ClusterNumber ; i++) { // Follow the fat chain to find the desired cluster
                Status = ReadFatClusterNumber(Vi, Cluster, 0, &Cluster);
                
                if (EFI_ERROR(Status)) return EFI_NOT_FOUND;
                
                if (Cluster < 2) {
                    MarkVolumeDirty (Vi);
                    return EFI_VOLUME_CORRUPTED;
                }
                
                if (Cluster >= Vi->EOCMark) {
                    *BufferSize = 0; // End of Directory reached.
                    return EFI_SUCCESS; // Requested cluster is beyond directory end
                }
            }
        }
        
//    Convert this cluster to a sector.
        Sector = ClusterToSector(Vi, Cluster);
        *ClusterRead = Cluster;
    }
    
// Read one cluster of the directory into the temp buffer.
    Status = FsReadMedia (Vi,
                          Buffer,
                          (UINT64)Sector,
                          0,
                          *BufferSize,
                          DIRECTORY_REGION);
                          
    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   AddToDirList
//
// Description: Adds a directory entry to DirList
//
// Parameters:
//  IN FILE_HANDLE    *fh - File Handle
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadAllDirectoryEntries
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AddToDirList (
    FILE_HANDLE  *fh,
    DIR_ENTRY_32 DirectoryEntry,
    CHAR16       *lfn,
    UINT32       Cluster,
    UINT32       Offset,
    UINT32       SlotNumber

)
{
    DIR_ENTRY_LIST *Del;
    EFI_STATUS     Status;
    
    Status = fsAllocateMemory(fh->VolumeInterface, sizeof(DIR_ENTRY_LIST), (VOID**)&Del, FALSE);
    
    if (EFI_ERROR(Status)) return Status;
    
    pBS->CopyMem (&(Del->DirectoryEntry), &DirectoryEntry, sizeof(DIR_ENTRY_32));
    Del->FileNameLFN = lfn;
    Del->Cluster = Cluster;
    Del->Offset= Offset;
    Del->SlotNumber= SlotNumber;
	DListAdd((DLIST *)(UINTN)&(fh->DirList), (DLINK *)(UINTN)&(Del->DirLink));
    fh->VolumeInterface->TotalDirEntryList++;
    return EFI_SUCCESS;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   CreateFHFromDirEntryList
//
// Description: Creates a file handle from directory entry list
//
// Parameters:
//  IN DIR_ENTRY_LIST *Del - Directory entry list
//  IN FILE_HANDLE    *fh - Directory file handle
//  OUT FILE_HANDLE   **fh1 - New file handle
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadFileHandle, ProcessOpenFileHandle
//
// Notes: Should not link the FH to any LIST
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CreateFHFromDirEntryList(
    IN DIR_ENTRY_LIST *Del,
    IN FILE_HANDLE    *fh,
    OUT FILE_HANDLE   **fh1
)
{

    FILE_HANDLE *nfh;
    EFI_STATUS  Status;
    
    Status = fsAllocateMemory(fh->VolumeInterface, sizeof(FILE_HANDLE), (VOID**)&nfh, TRUE);
    
    if (EFI_ERROR(Status)) return Status;
    
    Status = fsAllocateMemory(fh->VolumeInterface, (UINT32)((Wcslen(Del->FileNameLFN) * sizeof(CHAR16)) + 2), (VOID**)&(nfh->FileNameLFN), FALSE);
    
    if (EFI_ERROR(Status)) return Status;
    
//  Initialize FILE_HANDLE_STRUCTURE
    nfh->VolumeInterface = fh->VolumeInterface;
    nfh->HandleStatus = EFI_SUCCESS;
    nfh->ROOTDIR = FALSE;
    pBS->CopyMem (&(nfh->DirectoryEntry), &(Del->DirectoryEntry), sizeof(DIR_ENTRY_32));
    Wcscpy(nfh->FileNameLFN, Del->FileNameLFN);
    nfh->DirCluster = Del->Cluster;
    nfh->DirOffset = Del->Offset;
    nfh->SlotNumber = Del->SlotNumber;
    nfh->Parent = fh;
    *fh1 = nfh;
    
//  Add the new FH to the parent's Child List
	DListAdd((DLIST *)(UINTN)&(fh->ChildList), (DLINK *)(UINTN)&(nfh->ChildLink));

//	Add to VolumeInterface List
	DListAdd((DLIST *)(UINTN)&(fh->VolumeInterface->OpenFHs), (DLINK *)(UINTN)&(nfh->ViFHLink));
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FindMatchingFH
//
// Description: Finds the Child FH, whose name matches with the input.
//              In the Attributes, check whther both are file or Directory
//
// Parameters:
//  IN VOLUME_INFO  *Vi - Volume info structure
//  IN CHAR16       *NextCompName - Unicode name to compare
//  IN FILE_HANDLE  *fh - Parent file handle
//  OUT FILE_HANDLE **fh1 - Child file handle
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ProcessOpenFileHandle
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
FindMatchingFH (
    IN VOLUME_INFO  *Vi,
    IN CHAR16       *NextCompName,
    IN FILE_HANDLE  *fh,
    OUT FILE_HANDLE **fh1
)
{


    DLINK       *fhlink = fh->ChildList.pHead;
    FILE_HANDLE *fh2;
    
    for ( ; fhlink; ) {
        fh2 = OUTTER(fhlink, ChildLink, FILE_HANDLE);
        
        if (!Wcscmpcaseinsensitive (fh2->FileNameLFN, NextCompName)) {
            if (!(fh2->DirectoryEntry.Dir_Attr & ATTR_VOLUME_ID)) {
                if (fh2->HandleStatus == EFI_SUCCESS) {
                    *fh1 = fh2;
                    return TRUE;
                }
            }
        }
        
        fhlink = fhlink->pNext;
    }
    
    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FindMatchingDirEntry
//
// Description: Finds a directory entry matching the input name
//
// Parameters:
//  IN FILE_HANDLE     *fh - Directory file handle
//  IN CHAR16          *NextCompName - Unicode name to match
//  OUT DIR_ENTRY_LIST **Del - Directory list where found
//
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ProcessOpenFileHandle
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
FindMatchingDirEntry (
    IN FILE_HANDLE     *fh,
    IN CHAR16          *NextCompName,
    OUT DIR_ENTRY_LIST **Del
)
{

    DLINK          *dlink = fh->DirList.pHead;
    DIR_ENTRY_LIST *del;
    
    for ( ; dlink; ) {
        del = OUTTER(dlink, DirLink, DIR_ENTRY_LIST);
        
        if (!Wcscmpcaseinsensitive (del->FileNameLFN, NextCompName)) {
            if (!(del->DirectoryEntry.Dir_Attr & ATTR_VOLUME_ID)) {
                *Del = del;
                return TRUE;
            }
        }
        
        dlink = dlink->pNext;
    }
    
    return FALSE;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FindMatchingSFNDirEntry
//
// Description: Finds short file name directory entry matching input
//
// Parameters:
//  IN FILE_HANDLE     *fh - Directory file handle
//  IN CHAR8           *ShortFileName - Name to find
//  OUT DIR_ENTRY_LIST **Del - Directory list where found
//
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
FindMatchingSFNDirEntry (
    IN FILE_HANDLE     *fh,
    IN CHAR8           *ShortFileName,
    OUT DIR_ENTRY_LIST **Del
)
{

    DLINK          *dlink = fh->DirList.pHead;
    DIR_ENTRY_LIST *del;
    UINT8          Attrb;
    
    for ( ; dlink; ) {
        del = OUTTER(dlink, DirLink, DIR_ENTRY_LIST);
        Attrb = del->DirectoryEntry.Dir_Attr;
        del->DirectoryEntry.Dir_Attr = 0; // Generate a NULL terminated string
        
        if (!Strcmp((CHAR8 *)&del->DirectoryEntry, ShortFileName)) {
            del->DirectoryEntry.Dir_Attr = Attrb; // restore Attribute
            *Del = del;
            return TRUE;
        }
        
        del->DirectoryEntry.Dir_Attr = Attrb; // restore Attribute
        dlink = dlink->pNext;
    }
    
    return FALSE;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   Wcscmpcaseinsensitive
//
// Description: Case insensitive unicode string compare
//
// Parameters:
//  CHAR16 *string1 - First string
//  CHAR16 *string2 - Second string
//
// Return Value:
//  INT - Difference where mis-matched
//
// Modified:
//
// Referrals: FindMatchingFH, FindMatchingDirEntry
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

int Wcscmpcaseinsensitive(
    CHAR16 *string1,
    CHAR16 *string2
)
{

    CHAR16 ch1, ch2;
    
    while (*string1) {
        if (*string1 >=0x61 && *string1<=0x7a) ch1 = *string1 - 0x20;
        
        else ch1 = *string1;
        
        if (*string2 >=0x61 && *string2<=0x7a) ch2 = *string2 - 0x20;
        
        else ch2 = *string2;
        
        if (ch1 != ch2) break;
        
        *string1++;
        *string2++;
    }
    
    return *string1 - *string2;     // Don't use ch1 - ch2
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetDirListAtPosition
//
// Description: Get directory list at current position in directory file
//
// Parameters:
//  FILE_HANDLE       *Pfh - Parent file handle
//  UINT64            Position - Current position
//  DIR_ENTRY_LIST    **Del - Directory entry list
//
// Return Value:
//
// Modified:
//
// Referrals: ReadFileHandle
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetDirListAtPosition(
    FILE_HANDLE    *Pfh,
    UINT64         Position,
    DIR_ENTRY_LIST **Del
)
{

    EFI_STATUS Status = EFI_NOT_FOUND;
    DLINK      *dlink = Pfh->DirList.pHead;
    
    *Del = NULL;
    
    if (!dlink) return Status;
    
    while (Position && dlink) {
        if (!dlink->pNext) break;
        
        dlink = dlink->pNext;
        Position--;
    };
    
    if (Position == 0 && dlink) {
        Status = EFI_SUCCESS;
        *Del = OUTTER(dlink, DirLink, DIR_ENTRY_LIST);
    }
    
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   CloseFileHandle
//
// Description: Closes an open file
//
// Parameters:
//  IN EFI_FILE_PROTOCOL *This - File Protocol instance
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: DeleteFileHandle
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CloseFileHandle (
    IN EFI_FILE_PROTOCOL *This
)
{

    EFI_STATUS           Status;
    FILE_HANDLE_INSTANCE *fhi = (FILE_HANDLE_INSTANCE *)This;
    FILE_HANDLE          *Pfh = fhi->pFH;
    VOLUME_INFO          *vi;	
    void                 *Buffer;
    UINT32               BufferSize, Difference;
    EFI_TPL              SaveTpl;
    EFI_TPL              NextTpl;

	Status = ValidateCurrentStatus (fhi);
	if (EFI_ERROR(Status)) return Status;
    
#ifdef Debug_CloseFileHandle
    EfiDebugPrint(-1,"CloseFileHandle: %S Dir Cluster %x Dir Offset %x\n", Pfh->FileNameLFN, Pfh->DirCluster, Pfh->DirOffset);
#endif
    
//  Device Removal or Media Not Present
    if (!Pfh) {
        Status = pBS->FreePool(fhi);
        return EFI_SUCCESS;
    }
    NextTpl = FindNextTpl (EFI_TPL_CALLBACK);
    SaveTpl = pBS->RaiseTPL (NextTpl);    
    vi = Pfh->VolumeInterface;

//  Check if FreeSpace and Last Free Cluster needs to be updated for FAT32
    if (vi->FatType == FAT32 && vi->FreeSpaceinClusters != -1) {
        Difference = vi->FreeSpaceinSector1 - vi->FreeSpaceinClusters;
        
        if (vi->FreeSpaceinSector1 < vi->FreeSpaceinClusters) Difference = vi->FreeSpaceinClusters - vi->FreeSpaceinSector1;
        
        if (Difference > 0x100) {
//      ReadFSInfo
            BufferSize = vi->VolumeBPB.BPB_BytePerSec;
            GetTempBuffer (vi, &Buffer);
            
            Status = FsReadMedia (vi, Buffer, (UINT64)vi->VolumeBPB.BPB_FAT.BPB_FAT32.BPB_FSInfo, FSI_Free_Count, 8, FAT_REGION);
            
            if (EFI_ERROR(Status)) goto Memallocate_error;
            
            *(UINT32 *) ((UINT8 *)Buffer) = vi->FreeSpaceinClusters;
            *(UINT32 *) ((UINT8 *)Buffer + 4) = vi->LastFreeCluster;
            Status = FsWriteMedia (vi, Buffer, (UINT64)vi->VolumeBPB.BPB_FAT.BPB_FAT32.BPB_FSInfo, FSI_Free_Count, 8, FAT_REGION);
            vi->FreeSpaceinSector1 = vi->FreeSpaceinClusters;
            ReleaseTempBuffer(vi);
        }
    }
    
Memallocate_error:

    if (Pfh->DirEntryChanged == TRUE) {
        UpdateDirListFromFHDir(Pfh);
        Pfh->DirEntryChanged = FALSE;
    }
    
	DListDelete ((DLIST *)(UINTN)&(vi->OpenFIs), (DLINK *)(UINTN)&(fhi->ViFILink));
    fsDeAllocateMemory (vi, fhi);
    
    if (vi->TotalDirEntryList > DIRECTORTY_ENTRIES_CACHED) {
        if (vi->OpenFHs.Size > MAX_OPEN_FHS) FreeUpFHEntries (vi, NULL);
        
        FreeUpDirEntries (vi, Pfh->Parent);
    }
    
//  This should be always after FreeUpDirEntries. When called from 
//  DeleteFileHandle will have problem otherwise.
    if (Pfh) Pfh->InstancesCount -= 1;  
    
    FlushFileHandle(This);
    
    pBS->RestoreTPL(SaveTpl);

    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FreeUpFHEntries
//
// Description: Release all file handles whose instance count is 0
//
// Parameters:
//  VOLUME_INFO       *vi - Volume info
//  FILE_HANDLE       *pfh - Parent file handle
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: CloseFileHandle
//
// Notes:
//  Don't remove pfh
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FreeUpFHEntries (
    VOLUME_INFO *vi,
    FILE_HANDLE *pfh
)
{

    DLINK       *dlink = vi->OpenFHs.pHead;
    FILE_HANDLE *lfh;
    
//  Go through all the FHs in Volume Interface and release all whose Instance
//  count is 0, no DIR list is present and childlist is NULL
//  Don't delete:
//  1. If Instance count is more than 0 
//  2. If Dir List is present,
//  3. If it is a Root Dir, 
//  4. If Child List is present, 
//  5. If it is a i/p fh
//  6. If the i/p FH is the parent of the fh.
    for ( ; dlink; ) {
        lfh = OUTTER(dlink, ViFHLink, FILE_HANDLE);
        dlink = dlink->pNext;
        
        if (lfh->InstancesCount == 0 && !(lfh->DirList.pHead) &&
                !(lfh->ROOTDIR) && !(lfh->ChildList.pHead) && lfh != pfh) RemoveFH(lfh);
    }
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FreeUpDirEntries
//
// Description: Free up cached directory entries
//
// Parameters:
//  VOLUME_INFO       *vi - Volume info
//  FILE_HANDLE       *pfh - Parent file handle
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadAllDirectoryEntries, CloseFileHandle
//
// Notes:
//  Don't remove pfh
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
FreeUpDirEntries (
    VOLUME_INFO *vi,
    FILE_HANDLE *pfh
)
{

    DLINK       *dlink = vi->OpenFHs.pHead;
    FILE_HANDLE *lfh;
    
    for ( ; dlink; ) {
        if (vi->TotalDirEntryList <= DIRECTORTY_ENTRIES_CACHED) break;
        
        lfh = OUTTER(dlink, ViFHLink, FILE_HANDLE);
        
        if (lfh != pfh && lfh->DirList.pHead) RemoveAllDirList(lfh);
        
        dlink = dlink->pNext;
    }
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   RemoveAllDirList
//
// Description: Removes all directory lists from cache (needs to be re-read)
//
// Parameters:
//  FILE_HANDLE *lfh - list file handle
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadFileHandle, DeleteFileHandle, FreeUpDirEntries
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveAllDirList(
    FILE_HANDLE *lfh
)
{

    DLINK          *dlink = lfh->DirList.pHead;
    DIR_ENTRY_LIST *Del;
    
    for ( ; dlink; ) {
        Del = OUTTER(dlink, DirLink, DIR_ENTRY_LIST);
        dlink = dlink->pNext;
        RemoveDirList (lfh, Del);
    }
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   RemoveDirList
//
// Description: Removes a directory list from cache
//
// Parameters:
//  FILE_HANDLE    *fh - Directory file handle
//  DIR_ENTRY_LIST *Del - Directory list
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: DeleteFileHandle, RemoveAllDirList
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
RemoveDirList (
    FILE_HANDLE    *fh,
    DIR_ENTRY_LIST *Del
)
{

    fh->VolumeInterface->TotalDirEntryList--;
    
    fsDeAllocateMemory (fh->VolumeInterface, Del->FileNameLFN);
	DListDelete ((DLIST *)(UINTN)&(fh->DirList), (DLINK *)(UINTN)&(Del->DirLink));
    fsDeAllocateMemory (fh->VolumeInterface, Del);
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FetchLongName
//
// Description: Fetch a long name from a directory entry
//
// Parameters:
//  FILE_HANDLE  *fh - File handle of the directory
//  DIR_ENTRY_32 *Buffer - Buffer containing directory entry
//  UINT32       BufferPos - Position in buffer
//  UINT16       *Name - Unicode name placed here
//  UINT32       ClusterNumber - Current directory cluster
//  UINT32       ClusterSize - Cluster size in bytes
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadAllDirectoryEntries
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
FetchLongName (
    FILE_HANDLE  *fh,
    DIR_ENTRY_32 *Buffer,
    UINT32       BufferPos,
    UINT16       *Name,
    UINT32       ClusterNumber,
    UINT32       ClusterSize
)
{

    DIR_ENTRY_LFN *LfnSlot  = (DIR_ENTRY_LFN *) ((UINT8 *)Buffer + BufferPos);
    UINT8         Checksum = LfnChecksum((UINT8 *) Buffer + BufferPos);
    CHAR8         Order    = 0;
    UINT32        NamePos  = 0;
    UINT32        k;
    UINT32        Cluster = 0;
    EFI_STATUS    Status;
    BOOLEAN       Backup = FALSE;
    
    do {
        if (--LfnSlot < (DIR_ENTRY_LFN *) Buffer) { // Long name is split over 2 clusters
            Status = ReadClusterOfDirectoryEntries(fh, ClusterNumber-1, &Cluster, (UINT8*)Buffer, &ClusterSize);
            Backup = TRUE; // We had to back up into the previous cluster to get the whole name
            if (EFI_ERROR(Status) || (Status == EFI_SUCCESS && ClusterSize == 0)) { Order = 0; goto exit; };
            LfnSlot  = (DIR_ENTRY_LFN *) ((UINT8 *)Buffer + ClusterSize);
            LfnSlot--;
        }
        if (Order > MAX_LFN_SLOTS) { Order = 0; goto exit; };    // Max of 20 LFN slots are possible 255 chars max.
        
        if ((LfnSlot->Dir_Attr & ATTR_LONG_NAME_MASK) != (ATTR_LONG_NAME)) { Order = 0; goto exit; };
        
        if (++Order != (LfnSlot->Dir_Order & 0x1F)) { Order = 0; goto exit; };
        
        if (Checksum != LfnSlot->Dir_Checksum) { Order = 0; goto exit; };
        
        // Ok, the LFN slot is valid, attach it to the long name
        for (k = 0; k < 5; k++) Name[NamePos++] = LfnSlot->Dir_Name0_4[k];
        
        for (k = 0; k < 6; k++) Name[NamePos++] = LfnSlot->Dir_Name5_10[k];
        
        for (k = 0; k < 2; k++) Name[NamePos++] = LfnSlot->Dir_Name11_12[k];
    } while (!(LfnSlot->Dir_Order & 0x40));
    
// If the name was exactly 13 characters long in the last slot, add a terminating zero.
// Otherwise, it will already end in a zero.
    if (Name[NamePos - 1] != 0x0000) Name[NamePos] = 0x0000;
exit:
    if (Backup) { // Re-read the old cluster if we had to back up
        Status = ReadClusterOfDirectoryEntries(fh, ClusterNumber, &Cluster, (UINT8*)Buffer, &ClusterSize);
        if (EFI_ERROR(Status)) Order = 0;
    }
    return Order;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   LfnChecksum
//
// Description: Calculate long file name entry section checksum
//
// Parameters:
//  UINT8 *D - Pointer to long name entry
//
//
// Return Value:
//  UINT8 - Checksum
//
// Modified:
//
// Referrals: FetchLongName
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
LfnChecksum(
    UINT8 *D
)
{
    UINT8 Sum = 0;
    UINT8 i;
    
    for (i = 11; i != 0; i--) {
        Sum = ((Sum & 1)  ? 0x80 : 0) + (Sum >> 1) + *D++;
    }
    
    return Sum;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   FindShortName
//
// Description: Return a valid short name Directory Entry from DirCluster
//              beginning from ReadPosition.
//
// Parameters:
//    UINT8       *Buffer - Buffer to search in
//    UINT32      *Offset - Offset in buffer where entry found
//    UINT32      BufferSize - Size of buffer
//
//
// Return Value:
//  BOOLEAN - True = name found
//
// Modified:
//
// Referrals: ReadAllDirectoryEntries
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
FindShortName (
    UINT8  *Buffer,
    UINT32 *Offset,
    UINT32 BufferSize
)
{
    DIR_ENTRY_32 *Entry  = (DIR_ENTRY_32 *)(Buffer + *Offset);
    UINT32       i;
    
    for (i = *Offset; BufferSize; i+=sizeof(DIR_ENTRY_32),BufferSize-=sizeof(DIR_ENTRY_32)) {
        if (Entry->Dir_Name[0] == 0) {
			*Offset = (UINTN)-1;
            return FALSE; // no more directory Entries.
        }
        
        if (((Entry->Dir_Attr & ATTR_LONG_NAME_MASK) != (ATTR_LONG_NAME)) &&
                (Entry->Dir_Name[0] > 0x1f) &&
                (Entry->Dir_Name[0] != 0xe5)) {
            *Offset = i; // Point offset to short name found
            
            return TRUE;
        }
        
        Entry++;
    }
    
    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   CreateDirectoryEntry
//
// Description: Creates a directory entry
//
// Parameters:
//  IN  FILE_HANDLE       *fh - File handle
//  IN  CHAR16            *NextCompName - Unicode name to create
//  OUT FILE_HANDLE       **fh1 - File handle for new name
//  IN UINT64             Attributes
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ProcessOpenFileHandle
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CreateDirectoryEntry (
    IN FILE_HANDLE  *fh,
    IN CHAR16       *NextCompName,
    OUT FILE_HANDLE **fh1,
    IN UINT64       Attributes
)
{

    EFI_STATUS     Status;
    UINT32         DirCluster, DirClusterOffset;
    UINT32         Length;
    CHAR8          DirEntry[32];
    DIR_ENTRY_32   *Entry = (DIR_ENTRY_32 *) &DirEntry;
    CHAR16         *lfn;
    DIR_ENTRY_LIST *Del;
    
    Status = CreateDirEntryInDisk (fh, NextCompName, Attributes, &DirCluster, &DirClusterOffset, Entry);
    
    if (EFI_ERROR(Status)) return Status;
    
//  Create a Dir_List Entry
    Length = (UINT32)(Wcslen(NextCompName) * sizeof(CHAR16)) + 2;
    Status = fsAllocateMemory(fh->VolumeInterface, (UINT32) Length, (VOID**)&lfn, FALSE);
    pBS->CopyMem(lfn, NextCompName, Length);
    AddToDirList (fh, *Entry, lfn, DirCluster, DirClusterOffset, (UINTN)-1);
    
    Del = OUTTER(fh->DirList.pTail, DirLink, DIR_ENTRY_LIST);
//  Create a File Handle
    Status = CreateFHFromDirEntryList(Del, fh, fh1);
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   CreateDirEntryInDisk
//
// Description: Creates a directory entry on the disk
//
// Parameters:
//  IN  FILE_HANDLE     *fh - File handle
//  IN  CHAR16          *NextCompName - Name to create
//  IN  UINT64          Attributes - Attributes for entry
//  OUT UINT32          *DirCluster - Cluster of entry created
//  OUT UINT32          *DirClusterOffset - Offset in cluster
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: CreateDirectoryEntry
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CreateDirEntryInDisk (
    IN FILE_HANDLE *fh,
    IN CHAR16      *NextCompName,
    IN UINT64      Attributes,
    OUT UINT32     *DirCluster,
    OUT UINT32     *DirClusterOffset,
    DIR_ENTRY_32   *Entry
)
{

    EFI_STATUS            Status;
    VOLUME_INFO           *Vi = fh->VolumeInterface;
    CHAR8                 ShortFileName[11];
    EFI_TIME              EfiTime;
    EFI_TIME_CAPABILITIES Capabilities;
    UINT32                Sector, SectorOffset;
    BOOLEAN               LastDirEntry = FALSE;
    UINT32                Length;
    BOOLEAN               LfnNeeded = FALSE;
    UINT8                 *Slots;
    UINT32                NumSlots = 0;
    
    if (Vi->ReadOnly) return EFI_WRITE_PROTECTED;
    
    Status = GenUniqueShortFname (fh, NextCompName, ShortFileName, &LfnNeeded);
    
    if (EFI_ERROR(Status)) return Status;
    
//  Create Short Directory entry
    Zeromemory (Entry, sizeof(DIR_ENTRY_32));
    pBS->CopyMem(Entry, ShortFileName, 11);
    Entry->Dir_Attr         = (UINT8)Attributes;
    pRS->GetTime(&EfiTime, &Capabilities);
    EfiToFatTime (EfiTime, &Entry->Dir_CrtDate, &Entry->Dir_CrtTime);
    Entry->Dir_LstAccDate   = Entry->Dir_CrtDate;
    Entry->Dir_WrtTime      = Entry->Dir_CrtTime;
    Entry->Dir_WrtDate      = Entry->Dir_CrtDate;
    
//  Update the Cluster number in case of '.' entry.
    if (NextCompName[0] == '.' && NextCompName[1] == 0) {
        Length = FIRSTCLUSTER(fh->DirectoryEntry);
        Entry->Dir_FstClusHI = (UINT16)  (Length >> 16);
        Entry->Dir_FstClusLO = (UINT16)  Length;
    }
    
    
    fsAllocateMemory (Vi, (MAX_LFN_SLOTS + 2) * sizeof(DIR_ENTRY_32), (void **)&Slots, FALSE);
    
    if (LfnNeeded) {
        Status = SplitLFN (NextCompName, Entry, (DIR_ENTRY_LFN *)Slots, &NumSlots);
        
        if (EFI_ERROR(Status)) goto Error;
    }
    
// Assuming a short filename FILENAME.EXT (FILENAMEEXT), generate a
// name in the form FILENA~1.EXT, where n is a count beginning with 1.
//  GenUniqueFileName(fh, NextCompName, &ShortFileName);

//  Append Short Directory Entry at the End of Long File Name slots
    Length = NumSlots * sizeof(DIR_ENTRY_32);
    pBS->CopyMem(Slots + Length, Entry, sizeof(DIR_ENTRY_32));
    Length += sizeof(DIR_ENTRY_32);   // This is the total length
    
    Status = LocateFreeDirEntry(fh, Length, DirCluster,
                                DirClusterOffset,  &LastDirEntry);
                                
    if (EFI_ERROR(Status)) goto Error;
    
    GetSectorAddressDir(fh, *DirCluster, *DirClusterOffset, &Sector, &SectorOffset);
    Status = FsWriteMedia (Vi, Slots, Sector, SectorOffset, Length, DIRECTORY_REGION);
    
    if (EFI_ERROR(Status)) goto Error;
    
    *DirClusterOffset += Length;
    
    if (LastDirEntry == TRUE) {
        fh->FreeDirEntryCluster = *DirCluster;
        fh->FreeDirEntryOffset = *DirClusterOffset;
        
    } else {
        fh->DirListChanged = TRUE;
    }
    
    *DirClusterOffset -= sizeof(DIR_ENTRY_32);
    
Error:

    fsDeAllocateMemory (Vi, Slots);
    
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   GetTempBuffer
//
// Description: Gets a temporary buffer
//
// Parameters:
//    VOLUME_INFO     *Vi - Volume info
//    VOID            **Buffer - Buffer
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ProcessOpenFileHandle, ReadAllDirectoryEntries, CloseFileHandle
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
GetTempBuffer (
    VOLUME_INFO *Vi,
    VOID        **Buffer
)
{

    *Buffer = (UINT8 *)(Vi->TempBuffer);
    Vi->TempBufferInUse = TRUE;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ReleaseTempBuffer
//
// Description: Releases a temporary buffer
//
// Parameters:
//  VOLUME_INFO     *Vi - Volume Info
//
// Return Value:
//  EFI_STATUS
//
// Modified:
//
// Referrals: ProcessOpenFileHandle, ReadAllDirectoryEntries, CloseFileHandle
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
ReleaseTempBuffer (
    VOLUME_INFO *Vi
)
{
    Vi->TempBufferInUse = FALSE;
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
