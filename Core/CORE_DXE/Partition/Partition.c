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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/Partition/Partition.c 21    10/27/11 3:57p Artems $
//
// $Revision: 21 $
//
// $Date: 10/27/11 3:57p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/Partition/Partition.c $
// 
// 21    10/27/11 3:57p Artems
// EIP 73250: Verified DriverBinding Stop function frees all resources
// allocated by Start function
// 
// 20    10/25/11 12:01p Artems
// EIP 70530: Fixed bugs reported by SCT 2.3.1
// 
// 19    8/12/11 12:16p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 
// 18    5/02/11 5:58p Artems
// EIP 59571: Extended partition driver functionality - support of BlockIO
// protocol version 3
// 
// 17    2/05/11 3:52p Artems
// Removed previous check-in changes
// 
// 16    1/06/11 5:59p Oleksiyy
// [TAG]        EIP28607 
// [Category]   Improvement
// [Description]    System was hanging for some time if Floppy Media
// removed while writing in meda in progress.
// EFI_TPL_CALLBACK priority level rised during media related calls.
// [Files]          DiskIo.c, Info.c, MediaAccess.c, Open.c, Partition.c
// 
// 15    2/04/10 3:06p Oleksiyy
// EIP 31633 Minor fixes. OpenProtocol error status handling added to 
// DriverBindingStop function. 
// 
// 14    8/28/09 9:10a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 13    7/09/09 5:01p Oleksiyy
// Files clean-up
//
// 12    1/16/09 11:25a Felixp
// Bug fix in the DriverBindingStop function.
// The stop function was unconditionally closing disk I/O protocol.
// The protocol should only be closed when no child devices exist.
//
// 11    1/07/08 4:21p Robert
// Updated for coding standard
//
// 10    4/26/07 9:32a Robert
// Updated for CHM and Coding Standard compliance
//
// 8     3/23/07 5:13p Robert
// More coding standard changes and updated the copyright date
//
// 7     3/22/07 5:39p Robert
// Updated Files for coding standard
//
// 6     10/10/06 3:43p Yakovlevs
// Uncommented GPT Partition discovery
//
// 5     8/24/06 12:34p Felixp
// x64 support (fixes for warnings/errors)
//
// 3     10/28/05 8:36p Felixp
// DriverBindingSupported: Device Path test changed from BY_DRIVER to
// TEST_PROTOCOL
//
// 2     2/08/05 12:50p Felixp
// Bug fix in ReadBlocks and WriteBlocks: attemp to read/write
// Last LBA on the partition returned EFI_INVALID_PARAMETER
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    Partition.c
//
// Description: EFI Partition Generic Driver. Provides the Driver
//      Binding protocol and a Block I/O protocol for Partition detection
//      and interaction
//
//<AMI_FHDR_END>
//**********************************************************************
//;-------------------------------------------------------------------------
// Includes
#include "partition.h"


//;-------------------------------------------------------------------------
// Global Variables
EFI_BOOT_SERVICES   *gBS;
EFI_GUID    gUnusedPartitionGuid = EFI_PART_TYPE_UNUSED_GUID;
static EFI_GUID gEfiDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;

EFI_STATUS  gDevicePathStatus = EFI_SUCCESS;
EFI_STATUS  gDiskIoStatus = EFI_SUCCESS;

//;-------------------------------------------------------------------------
//GUID Variables
static EFI_GUID gDevicePathGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID    gBlockIoGuid    = EFI_BLOCK_IO_PROTOCOL_GUID;
EFI_GUID    gDiskIoGuid     = EFI_DISK_IO_PROTOCOL_GUID;

//;-------------------------------------------------------------------------
// Function Prototypes
EFI_STATUS DriverBindingSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL               *RemainingDevicePath  );

EFI_STATUS EFIAPI DriverBindingStart (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL               *RemainingDevicePath  );

EFI_STATUS EFIAPI DriverBindingStop (
    IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
    IN  EFI_HANDLE                    ControllerHandle,
    IN  UINTN                         NumberOfChildren,
    IN  EFI_HANDLE                    *ChildHandleBuffer);

EFI_STATUS Reset (
    IN EFI_BLOCK_IO_PROTOCOL  *This,
    IN BOOLEAN        ExtendedVerification);

EFI_STATUS ReadBlocks (
    IN EFI_BLOCK_IO_PROTOCOL      *This,
    IN UINT32                 MediaId,
    IN EFI_LBA                Lba,
    IN UINTN                  BufferSize,
    OUT VOID                  *Buffer  );

EFI_STATUS WriteBlocks (
    IN EFI_BLOCK_IO_PROTOCOL          *This,
    IN UINT32                 MediaId,
    IN EFI_LBA                Lba,
    IN UINTN                  BufferSize,
    OUT VOID                  *Buffer );

EFI_STATUS FlushBlocks ( IN EFI_BLOCK_IO_PROTOCOL  *PartBlockIo);

//;-------------------------------------------------------------------------
// Protocol Definition
EFI_BLOCK_IO_PROTOCOL   mPartitionBlockIo =
{
    EFI_BLOCK_IO_PROTOCOL_REVISION3,
    NULL,
    Reset,
    ReadBlocks,
    WriteBlocks,
    FlushBlocks
};


//;-------------------------------------------------------------------------
// Partition Driver Binding Procol
EFI_DRIVER_BINDING_PROTOCOL gPartitionDriverBinding =
{
    DriverBindingSupported,
    DriverBindingStart,
    DriverBindingStop,
    0x10,
    NULL,
    NULL
};


//;-------------------------------------------------------------------------
// Function Definitions
#ifdef EFI_DEBUG
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
#ifndef LANGUAGE_CODE_ENGLISH
#define LANGUAGE_CODE_ENGLISH "eng"
#endif
static BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2
){
    return    LangCode1[0]==LangCode2[0] 
           && LangCode1[1]==LangCode2[1]
           && LangCode1[2]==LangCode2[2];
}
static EFI_GUID gEfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#endif
//Driver Name
static UINT16 *gDriverName=L"AMI Partition Driver";

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Procedure:  ComponentNameGetControllerName
//
// Description: Retrieves a Unicode string that is the user readable name of
//              the controller that is being managed by an EFI Driver.
//
// Input:
//    This - A pointer to the EFI_COMPONENT_NAME_PROTOCOL
//          instance.
//    ControllerHandle - The handle of a controller that the driver specified
//          by This is managing.  This handle specifies the controller whose
//          name is to be returned.
//    ChildHandle - The handle of the child controller to retrieve the name
//          of.  This is an optional parameter that may be NULL.  It will be
//          NULL for device drivers.  It will also be NULL for a bus drivers
//          that wish to retrieve the name of the bus controller.  It will
//          not be NULL for a bus driver that wishes to retrieve the name of
//          a child controller.
//    Language - A pointer to a three character ISO 639-2 language identifier.
//          This is the language of the controller name that that the caller
//          is requesting, and it must match one of the languages specified
//          in Supported Languages.  The number of languages supported by a
//          driver is up to the driver writer.
//
// Output:
//    ControllerName - A pointer to the Unicode string to return.  This
//          Unicode string is the name of the controller specified by
//          ControllerHandle and ChildHandle in the language specified by
//          Language from the point of view of thedriver specified by This.
//
// Returns:
//    EFI_SUCCESS - The Unicode string for the user readable name in the
//          language specified by Language for the driver specified by This
//          was returned in DriverName.
//    EFI_INVALID_PARAMETER - ControllerHandle is not a valid EFI_HANDLE.
//    EFI_INVALID_PARAMETER - ChildHandle is not NULL and it is not a valid
//                            EFI_HANDLE.
//    EFI_INVALID_PARAMETER - Language is NULL.
//    EFI_INVALID_PARAMETER - ControllerName is NULL.
//    EFI_UNSUPPORTED - The driver specified by This is not currently
//          managing the controller specified by ControllerHandle and
//          ChildHandle.
//    EFI_UNSUPPORTED - The driver specified by This does not support the
//          language specified by Language.
//
// Referrals:
//
// Notes:
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS ComponentNameGetControllerName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN  EFI_HANDLE                   ControllerHandle,
    IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **ControllerName )
{
    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: ComponentNameGetDriverName
//
// Description: Returns the Driver Name if the language is supported
//
// Input:
//          This - Pointer to the instance of this driver
//          Language - Current operating language
//          DriverName - return parameter that will contain the Driver's Name
//
// Output: DriverName - return parameter that will contain the Driver's Name
//
// Returns:
//      EFI_SUCCESS - Driver loaded
//      EFI_INVALID_PARAMETER - If the Language or DriverName variable is
//              not defined
//      EFI_UNSUPPORTED - If the current laungage is not supported
//
// Referrals:
//
// Notes:
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS ComponentNameGetDriverName(
    IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **DriverName)
{
    //Supports only English
    if (!Language || !DriverName) return EFI_INVALID_PARAMETER;
    
    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH)) 
        return EFI_UNSUPPORTED;
    else 
        *DriverName=gDriverName;
    
    return EFI_SUCCESS;
}

//Component Name Protocol
static EFI_COMPONENT_NAME2_PROTOCOL gComponentName =
{
    ComponentNameGetDriverName,
    ComponentNameGetControllerName,
    LANGUAGE_CODE_ENGLISH
};
#endif


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: PartitionEntryPoint
//
// Description: Register Driver Binding protocol for this driver.
//
// Input:
//      ImageHandle - Identification Handle for the Partition
//              Block I/O driver
//      *SystemTable - Pointer to the EFI System Table
//
// Returns:
//      EFI_SUCCESS - Driver Binding Protocol Loaded
//       other       - Driver Binding Protocol not loaded
//
// Referrals: InitAmiLib InstallMultipleProtocolInterfaces
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PartitionEntryPoint (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS  Status;
    
    InitAmiLib(ImageHandle, SystemTable);
    
    gBS = SystemTable->BootServices;
    
    // initiaize the ImageHandle and DriverBindingHandle
    gPartitionDriverBinding.DriverBindingHandle = NULL;
    gPartitionDriverBinding.ImageHandle = ImageHandle;
    
    // Install driver binding protocol here
    Status = gBS->InstallMultipleProtocolInterfaces (
                 &gPartitionDriverBinding.DriverBindingHandle,
                 &gEfiDriverBindingProtocolGuid,
                 &gPartitionDriverBinding,
#ifdef EFI_DEBUG
                 &gEfiComponentName2ProtocolGuid, &gComponentName,
#endif
                 NULL);
                 
                 
    return Status;
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: DriverBindingSupported
//
// Description: Test to see if this driver supports ControllerHandle. Any
//      ControllerHandle than contains a BlockIo and DiskIo protocol can be
//      supported.
//
// Input:
//    This                - Protocol instance pointer.
//    ControllerHandle    - Handle of device to test
//    RemainingDevicePath - Not used
//
// Output: None
//
// Returns:
//    EFI_SUCCESS          - This driver supports this device
//    EFI_ALREADY_STARTED - This driver is already running on this device
//    other               - This driver does not support this device
//
// Referrals: OpenProtocol CloseProtocol
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS DriverBindingSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL               *RemainingDevicePath
)
{
    EFI_DISK_IO_PROTOCOL                    *DiskIo;
    EFI_STATUS                  Status;
    
    // see if the DevicePath is installed on controllerHandle
    Status = gBS->OpenProtocol(ControllerHandle, &gDevicePathGuid,
                               NULL,   This->DriverBindingHandle,
                               ControllerHandle, EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
                               
    if (EFI_ERROR(Status))
        return Status;
        
    // Close the Device Path Protocol once the tests have been done
    gBS->CloseProtocol(ControllerHandle, &gDevicePathGuid,
                       This->DriverBindingHandle, ControllerHandle);
                       
    // see if the DiskIo has already been started on controllerHandle
    Status = gBS->OpenProtocol(ControllerHandle, &gDiskIoGuid,
                               &DiskIo, This->DriverBindingHandle,
                               ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER);
                               
    if (EFI_ERROR(Status))
        return Status;
        
    // Close the DiskIo protocol once the tests have been done
    gBS->CloseProtocol(ControllerHandle, &gDiskIoGuid,
                       This->DriverBindingHandle, ControllerHandle);
                       
    // Now check for BlockIo Protocol
    Status = gBS->OpenProtocol(ControllerHandle, &gBlockIoGuid,
                               NULL, This->DriverBindingHandle, ControllerHandle,
                               EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
                               
    // return the status of finding the BlockIo protocol.
    //  if it gets this far the driver supports this device
    return Status;
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: DriverBindingStart
//
// Description: Start this driver on ControllerHandle by opening a Block IO and
//      Disk IO protocol, reading Device Path, and creating a child handle with
//      a Disk IO and device path protocol.
//
// Input:
//    This                - Protocol instance pointer.
//    ControllerHandle    - Handle of device to bind driver to
//    RemainingDevicePath - Not used
//
// Output: None
//
// Return:
//    EFI_SUCCESS         - This driver is added to DeviceHandle
//    other               - This driver does not support this device
//
// Referrals: OpenProtocol CloseProtocol GptDiscoverPartitions
//      ElToritoCreateChildHandle MbrCreateChildHandle
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS EFIAPI DriverBindingStart (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL               *RemainingDevicePath
)
{
    EFI_DEVICE_PATH_PROTOCOL    *ParentDevicePath;
    EFI_STATUS              Status;
    EFI_BLOCK_IO_PROTOCOL           *BlockIo;
    EFI_DISK_IO_PROTOCOL                *DiskIo;
    
    // Open the BlockIo protocol first because we are opening it by
    //  GET_PROTOCOL, if this fails it does not need to be closed. It is
    //  opened by GET_PROTOCOL because DiskIo already opens it BY_DRIVER
    Status = gBS->OpenProtocol(ControllerHandle, &gBlockIoGuid,
                               &BlockIo, This->DriverBindingHandle,
                               ControllerHandle, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                               
    if (EFI_ERROR (Status))
        return Status;
        
    Status = gBS->OpenProtocol(ControllerHandle, &gDevicePathGuid,
                               &ParentDevicePath,  This->DriverBindingHandle,
                               ControllerHandle, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                               
    if  (EFI_ERROR (Status))
        return Status;
        
    // Check to see if the Controller has already been started by
    //  another driver
    // Now open the DiskIo protocol for the controller
    Status = gBS->OpenProtocol(ControllerHandle, &gDiskIoGuid,
                               &DiskIo, This->DriverBindingHandle,
                               ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER);
                               
    if  (EFI_ERROR (Status))
    {
        // if there is an error, close all opened protocols, only close
        //  this one if
        // Close the Device Path protocol once the tests have been done
        gBS->CloseProtocol(ControllerHandle, &gDevicePathGuid,
                           This->DriverBindingHandle, ControllerHandle);
                           
        return Status;
    }
    
    
    // parse the devices and create the child   handles
    if (BlockIo->Media->MediaPresent == TRUE)
    {
        Status = EFI_NOT_FOUND;
        
        // search for the children
        Status = GptDiscoverPartitions(This, BlockIo, DiskIo,
                                       ParentDevicePath, ControllerHandle);
                                       
        if (EFI_ERROR(Status))
            Status = ElToritoCreateChildHandle(This, BlockIo, DiskIo,
                                               ParentDevicePath, ControllerHandle);
                                               
        if (EFI_ERROR(Status))
            Status = MbrCreateChildHandle(This, BlockIo, DiskIo,
                                          ParentDevicePath, ControllerHandle);
    }
    
    else
        Status = EFI_NO_MEDIA;
        
        
    // Now close all protocols  That were not already started
    if (EFI_ERROR(Status) )
    {
        gBS->CloseProtocol(ControllerHandle, &gDevicePathGuid,
                           This->DriverBindingHandle, ControllerHandle);
                           
        gBS->CloseProtocol(ControllerHandle, &gDiskIoGuid,
                           This->DriverBindingHandle, ControllerHandle);
    }
    
    return Status;
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: DriverBindingStop
//
// Description: Stop this driver on ControllerHandle. Support stoping
//      any child handles created by this driver.
//
// Input:
//    This              - Protocol instance pointer.
//    DeviceHandle      - Handle of device to stop driver on
//    NumberOfChildren  - Number of Children in the ChildHandleBuffer
//    ChildHandleBuffer - List of handles for the children we need to stop.
//
// Output: None
//
// Return:
//    EFI_SUCCESS         - This driver is removed DeviceHandle
//    other               - This driver was not removed from this device
//
// Referrals: CloseProtocol OpenProtocol FlushBlocks MemCmp FreePool
//      UninstallMultipleProtocolInterfaces
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS EFIAPI DriverBindingStop  (
    IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
    IN  EFI_HANDLE                    ControllerHandle,
    IN  UINTN                         NumberOfChildren,
    IN  EFI_HANDLE                    *ChildHandleBuffer
)
{

    EFI_HANDLE  Handle = *ChildHandleBuffer;
    PARTITION_DATA  *Child = NULL;
    EFI_BLOCK_IO_PROTOCOL   *BlockIo;
    EFI_GUID        *PartType = NULL;
    BOOLEAN         ChildrenLeft = FALSE;
    EFI_STATUS      Status;
    UINTN           Idx = 0;
    
    
    // Close these protocols if there are no children left
    if (NumberOfChildren == 0)
    {
        gBS->CloseProtocol(ControllerHandle, &gDiskIoGuid,
                           This->DriverBindingHandle, ControllerHandle);
                           
        return  EFI_SUCCESS;
    }
    
    // There are children, uninstall protocols and uninstall interfaces,
    //  and free memory
    while (Idx < NumberOfChildren)
    {
        Status = gBS->OpenProtocol(ChildHandleBuffer[Idx], &gBlockIoGuid,
                          (VOID **)&BlockIo, This->DriverBindingHandle,
                          ControllerHandle, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if (EFI_ERROR(Status)) 
        {
            Idx++;
            continue;
        }
                          
        Child = (PARTITION_DATA *)BlockIo;
        
        // clear all buffers for the current device
        BlockIo->FlushBlocks(BlockIo);
        
        // now close all handles
        gBS->CloseProtocol(ControllerHandle, &gDiskIoGuid,
                           This->DriverBindingHandle, ChildHandleBuffer[Idx]);
                           
        // look for a non 0 Partition type GUID
        // if non zero, set the point to the address, otherwise leave pointer
        //  as zero
        if (MemCmp(&Child->PartGuid, &gUnusedPartitionGuid, sizeof(EFI_GUID)))
            PartType = &Child->PartGuid;
            
        // Create the new handle for the child device
        Status = gBS->UninstallMultipleProtocolInterfaces (
                     ChildHandleBuffer[Idx],
                     &gDevicePathGuid,   Child->DevPath,
                     &gBlockIoGuid,      &Child->BlockIo,
                     PartType,           NULL,
                     NULL );
                     
        if (EFI_ERROR(Status))
            ChildrenLeft = TRUE;
            
        // free the memory that was allocated for The Child handle and the
        //  device path for the child handle


        if (Child->DevPath != NULL)
            gBS->FreePool(Child->DevPath);
                
        if (Child->BlockIo.Media != NULL)
            gBS->FreePool(Child->BlockIo.Media);
                
        gBS->FreePool(Child);

        
        // Increment Child Handle Pointer
        Idx++;
        
        // clear PartGuid pointer for the next child
        PartType = NULL;
    }
    
    // if there are childrem left, exit with error
    if (ChildrenLeft == TRUE)
        return EFI_DEVICE_ERROR;
        
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: Reset
//
// Description: Reset the parent Block Device.
//
// Input:
//    This                 - Protocol instance pointer.
//    ExtendedVerification - Driver may perform diagnostics on reset.
//
// Output: None
//
// Return:
//    EFI_SUCCESS            - The device was reset.
//    EFI_DEVICE_ERROR      - The device is not functioning properly and could
//                            not be reset.
//
// Referrals: ParentBlockIo->Reset
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Reset (
    IN EFI_BLOCK_IO_PROTOCOL      *This,
    IN BOOLEAN            ExtendedVerification
)
{
    PARTITION_DATA  *PartData;
    
    if (This == NULL)
        return EFI_INVALID_PARAMETER;
        
    // Find the parent's BlockIo Protocol
    PartData = (PARTITION_DATA *) This;
    
    return PartData->ParentBlockIo->Reset(PartData->ParentBlockIo,
                                          ExtendedVerification);
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: ReadBlocks
//
// Description: Reads blocks from the parent device
//
// Input:
//    This       - Protocol instance pointer.
//    MediaId    - Id of the media, changes every time the media is replaced.
//    Lba        - The starting Logical Block Address to read from
//    BufferSize - Size of Buffer, must be a multiple of device block size.
//
// Output:
//    Buffer     - Buffer containing read data
//
// Return:
//    EFI_SUCCESS           - The data was read correctly from the device.
//    EFI_DEVICE_ERROR      - The device reported an error while performing the read.
//    EFI_NO_MEDIA          - There is no media in the device.
//    EFI_MEDIA_CHANGED     - The MediaId does not match the current device.
//    EFI_BAD_BUFFER_SIZE   - The Buffer was not a multiple of the block size of the
//                            device.
//    EFI_INVALID_PARAMETER - The read request contains device addresses that are not
//                            valid for the device.
//
// Referrals: Mul64 ReadDisk
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadBlocks ( IN EFI_BLOCK_IO_PROTOCOL  *This,
                        IN UINT32     MediaId,
                        IN EFI_LBA    Lba,
                        IN UINTN    BufferSize,
                        OUT VOID    *Buffer
                      )
{
    PARTITION_DATA  *PartData;
    EFI_DISK_IO_PROTOCOL        *DiskIo;
    UINT64          Start;
    
    if (This == NULL)
        return EFI_INVALID_PARAMETER;
    
    // Find the parent BlockIo Protocol
    PartData = (PARTITION_DATA *) This;

    if(MediaId != PartData->BlockIo.Media->MediaId)
        return EFI_MEDIA_CHANGED;

    if(BufferSize == 0)
        return EFI_SUCCESS;
    
    if (BufferSize % PartData->BlockIo.Media->BlockSize != 0)
        return EFI_BAD_BUFFER_SIZE;
        
    // calculate the byte from which to start the read
    Start = (Mul64(PartData->StartingLba,
                   PartData->ParentBlockIo->Media->BlockSize) +
             Mul64(Lba, This->Media->BlockSize));
             
    // check to see if the read will go beyond the end of the
    //  current partition
    if ( ((Start + BufferSize - 1) >=
            Mul64(PartData->EndingLba+1,
                  PartData->ParentBlockIo->Media->BlockSize)) ||
            (Buffer ==  NULL))
        return EFI_INVALID_PARAMETER;
        
        
    // Make call directly to DiskIo of  the device

    DiskIo  = PartData->ParentDiskIo;
    
    return DiskIo->ReadDisk(DiskIo, MediaId, Start, BufferSize, Buffer);
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: WriteBlocks
//
// Description: Write blocks to the parent device
//
// Input:
//      This       - Protocol instance pointer.
//      MediaId    - Id of the media, changes every time the media is replaced.
//      Lba        - The starting Logical Block Address to read from
//      BufferSize - Size of Buffer, must be a multiple of device block size.
//      Buffer     - Buffer containing read data
//
// Output: None
//
// Return:
//    EFI_SUCCESS           - The data was written correctly to the device.
//    EFI_WRITE_PROTECTED   - The device can not be written to.
//    EFI_DEVICE_ERROR      - The device reported an error while performing the write.
//    EFI_NO_MEDIA          - There is no media in the device.
//    EFI_MEDIA_CHANGED     - The MediaId does not match the current device.
//    EFI_BAD_BUFFER_SIZE   - The Buffer was not a multiple of the block size of the
//                            device.
//    EFI_INVALID_PARAMETER - The write request contains a LBA that is not
//                            valid for the device.
//
// Referrals: Mul64 WriteDisk
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WriteBlocks (
    IN EFI_BLOCK_IO_PROTOCOL  *This,
    IN UINT32         MediaId,
    IN EFI_LBA        Lba,
    IN UINTN          BufferSize,
    IN VOID           *Buffer
)
{
    PARTITION_DATA  *PartData;
    EFI_DISK_IO_PROTOCOL        *DiskIo;
    UINT64          Start;

    if (This == NULL)
        return EFI_INVALID_PARAMETER;

    // Find the parent BlockIo Protocol
    PartData = (PARTITION_DATA *) This;

    if(MediaId != PartData->BlockIo.Media->MediaId)
        return EFI_MEDIA_CHANGED;
    
    if (BufferSize % PartData->BlockIo.Media->BlockSize != 0)
        return EFI_BAD_BUFFER_SIZE;
        
    // calculated the start address of the write command
    Start = Mul64(PartData->StartingLba,
                  PartData->ParentBlockIo->Media->BlockSize) +
            Mul64(Lba, This->Media->BlockSize);
            
    if ( ((Start + BufferSize - 1) >=
            Mul64(PartData->EndingLba+1,
                  PartData->ParentBlockIo->Media->BlockSize)) ||
            (Buffer ==  NULL))
        return EFI_INVALID_PARAMETER;
        
    DiskIo = PartData->ParentDiskIo;
    
    return DiskIo->WriteDisk(DiskIo, MediaId, Start, BufferSize, Buffer);
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: FlushBlocks
//
// Description: Flush the parent Block Device.
//
// Input:  This - Protocol instance pointer.
//
// Output: None
//
// Return:
//    EFI_SUCCESS       - All outstanding data was written to the device
//    EFI_DEVICE_ERROR - The device reported an error while writing back
//                      the data
//    EFI_NO_MEDIA     - There is no media in the device.
//
// Referrals: ParentBlockIo->FlushBlocks
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FlushBlocks (
    IN EFI_BLOCK_IO_PROTOCOL  *This
)
{
    PARTITION_DATA  *PartData;
    
    if (This == NULL)
        return EFI_INVALID_PARAMETER;
        
    PartData = (PARTITION_DATA *) This;
    
    // return the same value that the device specific BlockIo instance returns
    return PartData->ParentBlockIo->FlushBlocks(PartData->ParentBlockIo);
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
// Procedure: CreateChildHandle
//
// Description: Generic create child handle for the partition driver.  This
//      should work for GPT, MBR, and El Torito.
//
// Input:
//      *This - Pointer to the current instance of the blockIo protocol
//      *PData - a pointer to the start of the private data structure for
//          the partition
//      BlockSize - the blocksize for the partition
//
// Output:
//
// Return:
//      EFI_SUCCESS - Child created
//      other - no child created
//
// Referrals: AllocatePool FreePool CopyMem MemCmp Div64 OpenProtocol
//    InstallMultipleProtocolInterfaces UninstallMultipleProtocolInterfaces
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS  CreateChildHandle(
    IN  EFI_DRIVER_BINDING_PROTOCOL *This,
    IN  PARTITION_DATA              *PData,
    IN  UINT32                      BlockSize
)
{
    PARTITION_DATA      *Child;
    EFI_BLOCK_IO_MEDIA  *Media;
    EFI_STATUS          Status;
    EFI_GUID            *PartType = NULL;
    UINTN               Temp;
    
    
    // allocate memory for the Child handle
    Status = gBS->AllocatePool(EfiBootServicesData, sizeof(PARTITION_DATA), &Child);
    if (EFI_ERROR(Status))
        return EFI_OUT_OF_RESOURCES;
        
    Status = gBS->AllocatePool(EfiBootServicesData, sizeof(EFI_BLOCK_IO_MEDIA), &Media);
    if (EFI_ERROR(Status)) {
        gBS->FreePool(Child);
        return EFI_OUT_OF_RESOURCES;
    }
    
    // Copy the data from one location to the other,
    gBS->CopyMem(Child, PData, sizeof(PARTITION_DATA));
    
    // get the BlockIo protocol for the partition driver and the
    //  media information from the parent device
    gBS->CopyMem(&Child->BlockIo, &mPartitionBlockIo, sizeof(EFI_BLOCK_IO_PROTOCOL));
                 
    // just point to the media info for the device, that way we don't have to
    // worry about changing values
    Child->BlockIo.Media = Media;
    
    gBS->CopyMem(Media, PData->ParentBlockIo->Media, sizeof(EFI_BLOCK_IO_MEDIA));
                 
    Media->LogicalPartition = TRUE;
    Media->BlockSize = BlockSize;
    Media->IoAlign = 1;                             //no alignment requirements
    Media->LowestAlignedLba = 0;                   //added in Revision 2
    Media->LogicalBlocksPerPhysicalBlock = 0;      //added in Revision 2
    Media->OptimalTransferLengthGranularity = 0;   //added in Revision 3
    
    // Calculate the last block of the partition
    Media->LastBlock = Div64( Mul64(PData->EndingLba - PData->StartingLba + 1,
                                    Child->ParentBlockIo->Media->BlockSize),
                              BlockSize, &Temp) - 1;
                              
    // look for a non 0 Partition type GUID
    // if non zero, set the point to the address, otherwise leave
    //  pointer as zero
    if (MemCmp(&Child->PartGuid, &gUnusedPartitionGuid, sizeof(EFI_GUID)))
        PartType = &Child->PartGuid;
        
    // Create the new handle for the child device
    Child->Handle = NULL;
    Status = gBS->InstallMultipleProtocolInterfaces (
                                    &Child->Handle,
                                    &gDevicePathGuid, Child->DevPath,
                                    &gBlockIoGuid, &Child->BlockIo,
                                    PartType, NULL,
                                    NULL );
             
    // Now open the diskIo protocol for the child, if the install multiple
    //  protocol interface returns SUCCESS
    if (!EFI_ERROR(Status)) {
        Status = gBS->OpenProtocol ( Child->ParentHandle, 
                                     &gDiskIoGuid,
                                     &Child->ParentDiskIo, 
                                     This->DriverBindingHandle,
                                     Child->Handle, 
                                     EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );
                                   
        if (EFI_ERROR(Status)) {
            Status = gBS->UninstallMultipleProtocolInterfaces (
                                    &Child->Handle,
                                    &gDevicePathGuid, Child->DevPath,
                                    &gBlockIoGuid, &Child->BlockIo,
                                    PartType, NULL,
                                    NULL );
        //free all resources
            gBS->FreePool(Child->DevPath);
            gBS->FreePool(Media);
            gBS->FreePool(Child);
        }
    }
    
    return Status;
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
