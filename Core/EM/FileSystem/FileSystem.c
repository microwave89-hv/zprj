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
// $Header: /Alaska/SOURCE/Core/Modules/FileSystem/FileSystem.c 16    11/03/11 6:20a Rajeshms $
//
// $Revision: 16 $
//
// $Date: 11/03/11 6:20a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/FileSystem/FileSystem.c $
// 
// 16    11/03/11 6:20a Rajeshms
// [TAG]  		EIP73261
// [Category]  	Improvement
// [Description]  	FileSystem Driver Follow the UEFI Driver Model as per
// the UEFI Spec. and STOP function was Verified.
// [Files]  		FileSystem.c
// 
// 15    11/18/10 3:05p Felixp
// Removable media detection problem(EIP 47788).
// Symptoms: The "map -r" Shell command didn't detect removable media 
// such as floppy or CD if the media had been removed and than inserted
// back.
// 
// 14    8/28/09 12:28p Felixp
// Support for both UnicodeCollation and UnicodeCollation2 protocols 
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 13    8/28/09 11:59a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 12    7/02/09 5:47p Pats
// Updated to latest coding standard. No code changes.
//
// 11    4/13/07 7:07p Pats
// Edited to conform with coding standards. No code changes.
//
// 10    12/21/06 1:44p Felixp
// Bug fix in FileSystemInitUnicodeCollation: only first language in the
// list of UNICODE_COLLATION supported languages was checked.
//
// 9     9/13/06 3:42p Pats
// Corrected validation test comparing Media ID byte to first FAT byte to
// use Bytes Per Sector instead of Block Size in calculating FAT offset.
// This corrects problem of it not working on El Torito CD disks.
//
// 8     8/16/06 12:03p Markw
// Fixed UINTN* and UINT32* 64-bit issues.
//
// 7     8/15/06 6:30p Markw
// Reverting back to version 5.
//
// 5     3/29/06 2:53p Srinin
// Memory Deallocation problem fixed.
//
// 4     3/13/06 5:08p Pats
// Removed validation test using BS_BootSig. Added validation test
// comparing BPB_Media with first FAT byte.
//
// 3     3/13/06 2:23a Felixp
//
// 2     12/08/05 2:21p Pats
// Checked in from other directory, will latest fixes.
//
// 8     11/29/05 6:07p Pats
// Fixed problem of partition table being incorrectly recognized as a
// FAT12 drive boot sector.
//
// 7     11/03/05 2:15p Srinin
// Fixed VC7.1 warning msg.
//
// 6     8/15/05 1:16p Srinin
// SimpleFileSystemStart changed to return proper Status code.
//
// 4     6/21/05 4:00p Pats
// Removed commented-out debug code.
//
// 3     5/27/05 10:00a Srinin
// Volume size and Free space calculation modified.
//
// 2     5/24/05 11:56a Felixp
// reference to EfiDebugLib removed
//
// 1     4/26/05 6:05p Srinin
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: FileSystem.c
//
// Description: Installs Simple File System Protocol
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "FileSystem.h"

//----------------------------------------------------------------------

EFI_GUID                           gSimpleFileSystemBusDriverBindingProtocolGuid  = EFI_DRIVER_BINDING_PROTOCOL_GUID;
EFI_GUID                           guidLoadedImage                    = EFI_LOADED_IMAGE_PROTOCOL_GUID;
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
EFI_GUID                           gComponentNameProtocolGuid         = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#else
EFI_GUID                           gComponentNameProtocolGuid         = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
#endif
EFI_GUID                           gEfiBlockIoProtocolGuid            = EFI_BLOCK_IO_PROTOCOL_GUID;
EFI_GUID                           gEfiDiskIoProtocolGuid             = EFI_DISK_IO_PROTOCOL_GUID;
EFI_GUID                           gEfiGlobalVariableGuid             = EFI_GLOBAL_VARIABLE;
#ifndef EFI_UNICODE_COLLATION2_PROTOCOL_GUID //old Core
EFI_GUID                           gEfiUnicodeCollationProtocolGuid   = EFI_UNICODE_COLLATION_PROTOCOL_GUID;
#else
EFI_GUID                           gEfiUnicodeCollationProtocolGuid   = EFI_UNICODE_COLLATION2_PROTOCOL_GUID;
#endif
EFI_GUID                           gEfiFileInfoGuid                   = EFI_FILE_INFO_ID;
EFI_GUID                           gEfiFileSystemInfoGuid             = EFI_FILE_SYSTEM_INFO_ID;
EFI_GUID                           gEfiFileSystemVolumeLabelGuid      = EFI_FILE_SYSTEM_VOLUME_LABEL_ID;

EFI_UNICODE_COLLATION_PROTOCOL     *gFileSystemUnicodeCollationInterface = NULL;

extern EFI_COMPONENT_NAME_PROTOCOL gSimpleFileSystemDriverName;
extern EFI_GUID                    guidFS;

EFI_DRIVER_BINDING_PROTOCOL        gSimpleFileSystemDriverBinding = {
    SimpleFileSystemSupported,
    SimpleFileSystemStart,
    SimpleFileSystemStop,
    SIMPLE_FILE_SYSTEM_DRIVER_VERSION, // version
    NULL,                  // ImageHandle
    NULL                   // DriverBindingHandle
};

//----------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SimpleFileSystemEntryPoint
//
// Description:     Installs gSimpleFileSystemDriverBinding protocol
//
// Parameters:      EFI_HANDLE ImageHandle - Image handle for this driver
//                                           image
//                  EFI_SYSTEM_TABLE *SystemTable - pointer to the EFI
//                                                  system table
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
// NOTE(S):
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//  2. Install Driver Binding Protocol
//  3. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SimpleFileSystemEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                Status;
    EFI_LOADED_IMAGE_PROTOCOL *ThisImage;
    
    gSimpleFileSystemDriverBinding.DriverBindingHandle=ImageHandle;
    gSimpleFileSystemDriverBinding.ImageHandle=ImageHandle;
    
    InitAmiLib(ImageHandle, SystemTable);
    Status = pBS->InstallMultipleProtocolInterfaces(
                 &ImageHandle,
                 &gSimpleFileSystemBusDriverBindingProtocolGuid,&gSimpleFileSystemDriverBinding,
                 &gComponentNameProtocolGuid, &gSimpleFileSystemDriverName,
                 NULL
             );
             
             
#ifdef Debug_Level_1
    EfiDebugPrint(-1," SimpleFileSystemEntryPoint Exit Status %x\n",Status);
#endif
    
    Status = pBS->OpenProtocol (
                 ImageHandle,
                 &guidLoadedImage,
                 (VOID **)&ThisImage,
                 ImageHandle,
                 ImageHandle,
                 EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                 
    if (EFI_ERROR (Status)) return Status;
    
    ThisImage->Unload = UnloadSimpleFileSystemDriver;
    return Status;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UnloadSimpleFileSystemDriver
//
// Description:     Unloads this driver
//
// Parameters:      EFI_HANDLE ImageHandle - Image handle for this driver
//                                           image
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
UnloadSimpleFileSystemDriver (
    IN EFI_HANDLE ImageHandle
)
{
    EFI_HANDLE *Buffer;
    UINTN      NoOfHandles, i;
    EFI_STATUS Status;
    
    Status = pBS->LocateHandleBuffer (AllHandles, NULL, NULL, &NoOfHandles, &Buffer);
    
    if (EFI_ERROR(Status)) return Status;
    
    for (i = 0; i < NoOfHandles; i++) {
        pBS->DisconnectController(Buffer[i], ImageHandle, NULL);
    }
    
    if (Buffer) pBS->FreePool(Buffer);
    
    Status = pBS->UninstallMultipleProtocolInterfaces(
                 ImageHandle,
                 &gSimpleFileSystemBusDriverBindingProtocolGuid,&gSimpleFileSystemDriverBinding,
                 &gComponentNameProtocolGuid, &gSimpleFileSystemDriverName,
                 NULL);
                 
    return Status;
    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SimpleFileSystemSupported
//
// Description:     Checks whether Simple File System Protocol can be
//                  installed on the controller or not.
//
// Parameters:      EFI_DRIVER_BINDING_PROTOCOL *This - Pointer to this
//                                               instance of driver binding
//                                               protocol
//                  EFI_HANDLE Controller - Handle for this controller
//                  EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
//
// Return value:    EFI_STATUS - Status of the operation
//
// Modified:
//
// Referral(s):
//
//  NOTE(S):        DiskIO and BlockIO should have been installed on the
//                  controller.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SimpleFileSystemSupported(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
)
{

    EFI_STATUS            Status;
    EFI_DISK_IO_PROTOCOL  *DiskIo;
    EFI_BLOCK_IO_PROTOCOL *BlkIo;
    
//  Check if DiskIO can be opened by EFI_OPEN_PROTOCOL_BY_DRIVER
    Status = pBS->OpenProtocol( Controller,
                                &gEfiDiskIoProtocolGuid,
                                (VOID **)&DiskIo,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_BY_DRIVER );
                                
    if (EFI_ERROR (Status)) {
        goto Error;
    }
    
//  Close DiskIO Protocol
    Status = pBS->CloseProtocol (
                 Controller,
                 &gEfiDiskIoProtocolGuid,
                 This->DriverBindingHandle,
                 Controller);

    if (EFI_ERROR (Status)) {
        goto Error;
    }
    
                 
//  Check if BlockIO can be opened by EFI_OPEN_PROTOCOL_GET_PROTOCOL
    Status = pBS->OpenProtocol( Controller,
                                &gEfiBlockIoProtocolGuid,
                                (VOID **)&BlkIo,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                                
    if (EFI_ERROR (Status)) {
        goto Error;
    }
    
    return EFI_SUCCESS;

Error:

    if( Status != (EFI_ALREADY_STARTED || EFI_ACCESS_DENIED) ) {
        return EFI_UNSUPPORTED;
    } else { 
        return Status;
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SimpleFileSystemStart
//
// Description:     Installs Simple File Ssystem Protocol
//
// Parameters:      EFI_DRIVER_BINDING_PROTOCOL *This - Pointer to this
//                                               instance of driver binding
//                                               protocol
//                  EFI_HANDLE Controller - Handle for this controller
//                  EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
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
SimpleFileSystemStart (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
)
{

    EFI_STATUS            Status;
    EFI_DISK_IO_PROTOCOL  *DiskIo;
    EFI_BLOCK_IO_PROTOCOL *BlkIo;
    
//  Check if DiskIO can be opened by EFI_OPEN_PROTOCOL_BY_DRIVER
    Status = pBS->OpenProtocol( Controller,
                                &gEfiDiskIoProtocolGuid,
                                (VOID **)&DiskIo,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_BY_DRIVER );
                                
    if (EFI_ERROR (Status)) return EFI_DEVICE_ERROR;
    
//  Check if BlockIO can be opened by EFI_OPEN_PROTOCOL_GET_PROTOCOL
    Status = pBS->OpenProtocol( Controller,
                                &gEfiBlockIoProtocolGuid,
                                (VOID **)&BlkIo,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                                
    if (EFI_ERROR (Status)) {
        goto Error;
    }
    
//  Get the UnicodeCollation driver
    Status = FileSystemInitUnicodeCollation (This, &gFileSystemUnicodeCollationInterface);
    
    if (EFI_ERROR (Status)) {
        goto Error;
    }
    
    Status = DetectInstallVolume(DiskIo, BlkIo, Controller);
    
    if (EFI_ERROR(Status)) {    
        goto Error;
    }
        
    return EFI_SUCCESS;

Error:
    //
    // Close DiskIO Protocol
    //
    pBS->CloseProtocol (Controller,
                        &gEfiDiskIoProtocolGuid,
                        This->DriverBindingHandle,
                        Controller
                        );
    
    if( Status == EFI_OUT_OF_RESOURCES ) {
        return EFI_OUT_OF_RESOURCES;
    }
    return EFI_DEVICE_ERROR;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       SimpleFileSystemStop
//
// Description:     Uninstall Simple File system Protocol
//
// Parameters:      EFI_DRIVER_BINDING_PROTOCOL *This - Pointer to this
//                                               instance of driver binding
//                                               protocol
//                  EFI_HANDLE Controller - Handle for this controller
//                  EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
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
SimpleFileSystemStop (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN UINTN                       NumberOfChildren,
    IN EFI_HANDLE                  *ChildHandleBuffer
)
{

    EFI_STATUS                      Status;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    VOLUME_INFO                     *vi;
    
    Status = pBS->OpenProtocol ( Controller,
                                 &guidFS,
                                 &FileSystem,
                                 This->DriverBindingHandle,
                                 Controller,
                                 EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                                 
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;
    
    vi = (VOLUME_INFO *)FileSystem;
    
    if (NumberOfChildren) return EFI_DEVICE_ERROR;
    
    Status = pBS->UninstallMultipleProtocolInterfaces(
                 (vi->VolumeHandle),
                 &guidFS, &(vi->SimpleFileSystemProtocol),
                 NULL);
                 
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;
    
//  Close DISK_IO Protocol
    Status = pBS->CloseProtocol (
                 Controller,
                 &gEfiDiskIoProtocolGuid,
                 This->DriverBindingHandle,
                 Controller);
                 
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;
    
    Status = fsDeAllocateMemory(vi, vi->TempBuffer);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;
    
    Status = FreeUpResources (vi, EFI_NO_MEDIA);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;
    
    Status = pBS->FreePool(vi->CacheBuffer);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;
    
    Status = pBS->FreePool(vi);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       DetectInstallVolume
//
// Description:     Detects whether a valid volume is present or not
//
// Parameters:      EFI_DISK_IO_PROTOCOL *DiskIo - Pointer to disk IO
//                                                 structure
// Parameters:      EFI_BLOCK_IO_PROTOCOL *DiskIo - Pointer to boock IO
//                                                  structure
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
DetectInstallVolume(
    IN EFI_DISK_IO_PROTOCOL  *DiskIo,
    IN EFI_BLOCK_IO_PROTOCOL *BlkIo,
    IN EFI_HANDLE            Handle
)
{

    EFI_STATUS   Status;
    VOLUME_INFO  *vi;
    UINT32       TempBufferSize, i, Fat_Cache_Blocks, Dir_Cache_Blocks, \
    TotalCacheMemory, TotalCacheList;
    UINTN        CacheAddress, CacheListAddress;
    CACHE_HEADER *ch;
    
    Status = pBS->AllocatePool (EfiBootServicesData,
                                sizeof(VOLUME_INFO),
                                (VOID**)&vi);
                                
//  No need to close IDE_CONTROLLER_PROTOCOL
    if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;
    
    Zeromemory (vi, sizeof(VOLUME_INFO));
    
    vi->DiskIo = DiskIo;
    vi->BlkIo = BlkIo;
    vi->MediaID = vi->BlkIo->Media->MediaId;
    Status = DetectVolume(vi, FALSE);
    
    if (EFI_ERROR(Status)) {
        pBS->FreePool(vi);
        return Status;
    }
    
    vi->UnicodeCollationInterface = gFileSystemUnicodeCollationInterface;
    
    vi->SimpleFileSystemProtocol.OpenVolume = OpenVolume;
    vi->SimpleFileSystemProtocol.Revision = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION;
    vi->VolumeHandle = Handle;
    DListInit(&(vi->OpenFHs));
    DListInit(&(vi->OpenFIs));
    DListInit(&(vi->CacheList));
    
//  Allocate TempBuffer, max. cluster size which is 32KB
    TempBufferSize = vi->RootDirSectorCount << vi->BytesPerSecPowerof2;
    
    if (vi->BytesPerCluster > TempBufferSize) TempBufferSize = vi->BytesPerCluster;
    
    Status = fsAllocateMemory(vi, TempBufferSize, (VOID**)&vi->TempBuffer, FALSE);
    
//  Init the cache Buffers
    Fat_Cache_Blocks = vi->AllowedFatCacheSize / vi->BytesPerCluster;
    Dir_Cache_Blocks = vi->AllowedDirCacheSize / vi->BytesPerCluster;
    
    TotalCacheMemory = Fat_Cache_Blocks * vi->BytesPerCluster +
                       Dir_Cache_Blocks * vi->BytesPerCluster;
                       
    TotalCacheList = Fat_Cache_Blocks * sizeof (CACHE_HEADER) +
                     Dir_Cache_Blocks * sizeof (CACHE_HEADER);
                     
    Status = pBS->AllocatePool (EfiBootServicesData,
                                TotalCacheMemory + TotalCacheList,
                                (VOID**)&vi->CacheBuffer);
                                
    CacheAddress = (UINTN) (vi->CacheBuffer);
    CacheListAddress = (UINTN) (vi->CacheBuffer) + TotalCacheMemory;
    
    for (i = 0; i < Fat_Cache_Blocks + Dir_Cache_Blocks; i++) {
        ch = (CACHE_HEADER *)CacheListAddress;
        ch->AbsoluteOffset = 0;
        ch->AbsoluteOffsetEnd = 0;
        ch->Buffer = (UINT8 *) CacheAddress;
        ch->DIRTY_FLAG = FALSE;
        
        if ( i < Fat_Cache_Blocks) ch->DataRegion = FAT_REGION;
        
        else ch->DataRegion = DIRECTORY_REGION;
        
        DListAdd(&(vi->CacheList), &(ch->CacheLink));
        CacheAddress += vi->BytesPerCluster;
        CacheListAddress += sizeof (CACHE_HEADER);
    }
    
    Status = pBS->InstallMultipleProtocolInterfaces (
                 &(vi->VolumeHandle),
                 &guidFS, &(vi->SimpleFileSystemProtocol),
                 NULL);
                 
    if (EFI_ERROR(Status)) {
        pBS->FreePool(vi);
        return EFI_UNSUPPORTED;
    }
    
    return EFI_SUCCESS;
    
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       DetectVolume
//
// Description:     Detects the presence of a valid FAT volume
//
// Parameters:      VOLUME_INFO *vi - Pointer to the volume info structure
//                  BOOLEAN StatusCheck - Only reads MBR if true
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
DetectVolume (
    VOLUME_INFO *vi,
    BOOLEAN     StatusCheck
)
{

    EFI_STATUS Status;
    VOLUME_BPB *Bpb;
    UINT8      *Buffer;
    UINT8      *Buffer2;
    BOOLEAN    VALID_FAT = TRUE;
    UINT64     Offset;
    
    Status = fsAllocateMemory(vi, vi->BlkIo->Media->BlockSize, (VOID**)&Buffer, FALSE);
//  Status = pBS->AllocatePool (EfiBootServicesData,
//              vi->BlkIo->Media->BlockSize,
//              (VOID**)&Buffer);

    if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES; //No need to close IDE_CONTROLLER_PROTOCOL
    
//  Read Logical Sector 0
    Status= vi->DiskIo->ReadDisk (vi->DiskIo, vi->MediaID, 0, vi->BlkIo->Media->BlockSize, Buffer);

	// Read Second time if EFI_MEDIA_CHANGED is returned for media changeable devices 
	// (like CDROM/Floppy)
	if( Status == EFI_MEDIA_CHANGED ) {        
        vi->MediaID = vi->BlkIo->Media->MediaId;        
        Status= vi->DiskIo->ReadDisk (vi->DiskIo, vi->MediaID, 0, vi->BlkIo->Media->BlockSize, Buffer);
    }        
    if (EFI_ERROR(Status) || StatusCheck) {
//      pBS->FreePool(Buffer);
        fsDeAllocateMemory(vi, Buffer);
        vi->VolumeStatus = Status;
        return Status;
    }
    
    Bpb = (VOLUME_BPB *)Buffer;
    
    vi->FatType = FAT_UNKNOWN;
    
//  Check for 0x55aa at offset 510
    if ( *(UINT16 *) ((UINT8 *)Buffer + 510) != 0xaa55) {
//      pBS->FreePool(Buffer);
        fsDeAllocateMemory(vi, Buffer);
        return EFI_UNSUPPORTED;
    }
    
//  Check for valid jmp instruction
    if (Buffer[0] != 0xEB && Buffer[0] != 0xE9 ) VALID_FAT = FALSE;
    
//  Check for valid Bytes per Sector
    switch (Bpb->BPB_BytePerSec) {
        case 512:
            vi->BytesPerSecPowerof2 = 9;
            break;
        case 1024:
            vi->BytesPerSecPowerof2 = 10;
            break;
        case 2048:
            vi->BytesPerSecPowerof2 = 11;
            break;
        case 4096:
            vi->BytesPerSecPowerof2 = 12;
            break;
        default:
            VALID_FAT = FALSE;
    }
    
//  Check for Valid Sectors per cluster
    if (Bpb->BPB_SecPerClus != 1 && Bpb->BPB_SecPerClus != 2 &&
            Bpb->BPB_SecPerClus != 4 && Bpb->BPB_SecPerClus != 8 &&
            Bpb->BPB_SecPerClus != 16 && Bpb->BPB_SecPerClus != 32 &&
            Bpb->BPB_SecPerClus != 64 && Bpb->BPB_SecPerClus != 128) VALID_FAT = FALSE;
            
//  Check for Reserved Sector Count and Number of FATS
    if (Bpb->BPB_RsvdSecCnt == 0 || Bpb->BPB_NumFATs == 0) VALID_FAT = FALSE;
    
//  Both TotSec16 and TotSec32 cannot be zero
    if (Bpb->BPB_TotSec16 == 0 && Bpb->BPB_TotSec32 == 0) VALID_FAT = FALSE;
    
//  This test removed (3-13-06)
//  If it is a FAT12 or FAT16 disk, and the boot signature is not 29, reject the disk.
//  if (Bpb->BPB_FATSz16 != 0 && Bpb->BPB_FAT.BPB_FAT1216.BS_BootSig != 0x29) VALID_FAT = FALSE;

//  This test added (3-13-06)
//  If the media byte doesn't match the first FAT byte, reject the disk.
    if (VALID_FAT) {
        Status = fsAllocateMemory(vi, Bpb->BPB_BytePerSec, (VOID**)&Buffer2, FALSE);
        
        if (EFI_ERROR(Status)) {
            fsDeAllocateMemory(vi, Buffer);
            return EFI_OUT_OF_RESOURCES;
        }
        
        Offset = Bpb->BPB_RsvdSecCnt * Bpb->BPB_BytePerSec;
        Status= vi->DiskIo->ReadDisk (vi->DiskIo, vi->MediaID, Offset, Bpb->BPB_BytePerSec, Buffer2);
        
        if (EFI_ERROR(Status)) {
            fsDeAllocateMemory(vi, Buffer);
            fsDeAllocateMemory(vi, Buffer2);
            return Status;
        }
        
        if (Bpb->BPB_Media != Buffer2[0]) VALID_FAT = FALSE;
        
        fsDeAllocateMemory(vi, Buffer2);
    }
    
    if (!VALID_FAT) goto error_check;
    
    vi->RootDirSectorCount  = ((Bpb->BPB_RootEntCnt << 5 ) + (Bpb->BPB_BytePerSec - 1)) / Bpb->BPB_BytePerSec;
    
    vi->FATSz = Bpb->BPB_FATSz16;
    
    if (Bpb->BPB_FATSz16 == 0) vi->FATSz = Bpb->BPB_FAT.BPB_FAT32.BPB_FATSz32;
    
    vi->TotalSectors = Bpb->BPB_TotSec16;
    
    if (Bpb->BPB_TotSec16 == 0) vi->TotalSectors = Bpb->BPB_TotSec32;
    
    vi->DataSectors = vi->TotalSectors \
                      - Bpb->BPB_RsvdSecCnt  \
                      - vi->FATSz * Bpb->BPB_NumFATs \
                      - vi->RootDirSectorCount;
                      
    vi->CountOfDataClusters = vi->DataSectors / Bpb->BPB_SecPerClus;
    
// There could be a few sectors at the "end" of the disk that will not completely
// fill a cluster. Make sure these are not counted in the DataSectors.
    vi->DataSectors = vi->CountOfDataClusters * Bpb->BPB_SecPerClus;
    
    if (vi->CountOfDataClusters < 4085) {
        vi->FatType = FAT12;
        vi->EOCMark = 0x0ff8;
        
    } else if (vi->CountOfDataClusters < 65525) {
        vi->FatType = FAT16;
        vi->EOCMark = 0x0fff8;
        
    } else {
        vi->FatType = FAT32;
        vi->EOCMark = 0x0ffffff8;
    }
    
//  Calculate where Root Directory Entries are present
    if (vi->FatType == FAT32)
        vi->FirstRootDirSector = Bpb->BPB_FAT.BPB_FAT32.BPB_RootClus * Bpb->BPB_SecPerClus;
        
    else
        vi->FirstRootDirSector = Bpb->BPB_RsvdSecCnt + (Bpb->BPB_NumFATs * Bpb->BPB_FATSz16);
        
//  Copy Sector Zero Contends to VOLUME_BPB in vi
    pBS->CopyMem (&(vi->VolumeBPB), Buffer, sizeof(VOLUME_BPB));
    
    vi->BytesPerCluster = (UINT32)vi->VolumeBPB.BPB_SecPerClus << vi->BytesPerSecPowerof2;
    
//  Update CacheSize
    vi->AllowedFatCacheSize = FAT_CACHE_SIZE;
    
    if (FAT_CACHE_SIZE < vi->BytesPerCluster << 1) vi->AllowedFatCacheSize = vi->BytesPerCluster << 1;
    
    vi->AllowedDirCacheSize = DIR_CACHE_SIZE;
    
    if (DIR_CACHE_SIZE < vi->BytesPerCluster << 1) vi->AllowedDirCacheSize = vi->BytesPerCluster << 1;
    
error_check:
    fsDeAllocateMemory(vi, Buffer);
    
    if (vi->FatType == FAT_UNKNOWN) {
        vi->VolumeStatus = EFI_UNSUPPORTED;
        return EFI_UNSUPPORTED;
    }
    
    vi->VolumeStatus = EFI_SUCCESS;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       FileSystemInitUnicodeCollation
//
// Description:     Find the language Interface
//
// Parameters:      EFI_DRIVER_BINDING_PROTOCOL *This - Pointer to this
//                                               instance of driver binding
//                                               protocol
//                  UINT8 *LandCode - Pointer to the language code
//                  EFI_UNICODE_COLLATION_PROTOCOL *gFileSystemUnicodeCollationInterface
//                                                 - Pointer to pointer to unicode
//                                                 collation interfact structure
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
FileSystemInitUnicodeCollation (
    IN EFI_DRIVER_BINDING_PROTOCOL        *This,
    IN OUT EFI_UNICODE_COLLATION_PROTOCOL **gFileSystemUnicodeCollationInterface
)
{
    EFI_STATUS                     Status;

    if (*gFileSystemUnicodeCollationInterface != NULL) return EFI_SUCCESS;
    
    //  Locate all Unicode Collation Protocol
    Status = pBS->LocateProtocol(
        &gEfiUnicodeCollationProtocolGuid, NULL,
        gFileSystemUnicodeCollationInterface
    );
    return Status;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:     Zeromemory
//
// Description:   Zeros the contents of a specified memory location
//
// Parameters:    VOID *Buffer - location of memory to zero
//                UINT32 Size - Size in bytes to zero
//
// Return Value:  none
//
// Modified:
//
// Referral(s):
//
// NOTE(S):       For testing under Aptio and Alaska, 
//                This routine has been copied.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

void
Zeromemory (
    void   *Buffer,
    UINT32 Size
)
{
    UINT8 *Ptr;
    Ptr = Buffer;
    
    while (Size--) {
        *(Ptr++) = 0;
    }
    
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rig hts Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
