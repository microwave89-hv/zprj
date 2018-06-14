//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*****************************************************************************
// $Header: /Alaska/SOURCE/Core/EDK/DxeMain/DiskIo.c 27    8/12/11 12:23p Artems $
//
// $Revision: 27 $
//
// $Date: 8/12/11 12:23p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/DxeMain/DiskIo.c $
// 
// 27    8/12/11 12:23p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 
// 26    2/05/11 4:10p Artems
// Removed previous check-in changes
// 
// 25    1/06/11 5:52p Oleksiyy
// [TAG]  		EIP28607 
// [Category]  	Improvement
// [Description]  	System was hanging for some time if Floppy Media
// removed while writing in meda in progress.
// EFI_TPL_CALLBACK priority level rised during media related calls.
// [Files]  		DiskIo.c, Info.c, MediaAccess.c, Open.c, Partition.c
// 
// 24    8/27/09 5:21p Felixp
// 
// 23    8/27/09 4:40p Felixp
// 
// 20    8/21/09 4:29p Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 19    7/08/09 5:54p Vyacheslava
// Updated according to the coding standards.
//
// 18    4/24/07 4:10p Robert
// Updated headers to be compliant with the CHM Help Builder
//
// 17    4/19/07 12:57p Felixp
// Minor bug fix in handling of media not present in ReadDiskIo (along
// with IdeBus.c changes resolves SCT failure)
//
// 15    4/16/07 6:29p Felixp
// Fix: proper handling of media not present in ReadDiskIo
//
// 14    8/24/06 10:11a Felixp
// x64 support: warning/error fixes
//
// 11    10/28/05 9:03p Felixp
// bug fix in CalcAlignmentValues
//
// 10    10/28/05 2:03p Felixp
// bug fix in WriteDiskIo for the case when AboveAlign is not zero.
//

// 5     2/14/05 4:10p Felixp
// Small bug fix in ReadDiskIo (success returned in case of error)
//
// 4     2/11/05 6:09p Felixp
// - optimizations (both code size and speed)
// - SCT failure fixed
//
// 2     2/07/05 6:05p Felixp
// Small bug fix in ReadDiskIo and WriteDiskIo
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:    Disko.c
//
// Description: EFI Disk Io Generic Driver.
//
//<AMI_FHDR_END>
//*****************************************************************************
#include <Protocol/DiskIo.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/ComponentName2.h>
#include <AmiDxeLib.h>

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
//----------------------------------------------------------------------------
// Function Prototypes
EFI_STATUS EFIAPI DiskIoSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
);

EFI_STATUS  EFIAPI  DiskIoStart (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
);

EFI_STATUS  EFIAPI  DiskIoStop (
    IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN  EFI_HANDLE                     ControllerHandle,
    IN  UINTN                          NumberOfChildren,
    IN  EFI_HANDLE                     *ChildHandleBuffer
);

EFI_STATUS ReadDiskIo (
    IN EFI_DISK_IO_PROTOCOL *This,
    IN UINT32       MediaId,
    IN UINT64       Offset,
    IN UINTN        BufferSize,
    OUT VOID        *Buffer
);

EFI_STATUS WriteDiskIo (
    IN EFI_DISK_IO_PROTOCOL *This,
    IN UINT32               MediaId,
    IN UINT64               Offset,
    IN UINTN                BufferSize,
    IN VOID                 *Buffer
);

//----------------------------------------------------------------------------
// Data types
typedef struct _DISK_IO_DATA {
    EFI_DISK_IO_PROTOCOL    DiskIo;
    EFI_BLOCK_IO_PROTOCOL   *BlockIo;
} DISK_IO_DATA;

//----------------------------------------------------------------------------
// GUID Definitions
static EFI_GUID gEfiBlockIoProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;
static EFI_GUID gEfiDiskIoProtocolGuid = EFI_DISK_IO_PROTOCOL_GUID;
static EFI_GUID gEfiDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;

//----------------------------------------------------------------------------
// Module Scope Glo=bal Variables

EFI_DRIVER_BINDING_PROTOCOL gDiskIoDriverBindingProtocol = {
    DiskIoSupported,
    DiskIoStart,
    DiskIoStop,
    0x10,
    NULL,
    NULL
};

DISK_IO_DATA gDiskIoData = {
    {
        EFI_DISK_IO_PROTOCOL_REVISION,
        ReadDiskIo,
        WriteDiskIo
    },
    NULL
};

static EFI_BOOT_SERVICES *gBS = NULL;

//----------------------------------------------------------------------------
//Driver Name

#ifdef EFI_DEBUG
static UINT16 *gDriverName = L"AMI Disk I/O Driver";

//----------------------------------------------------------------------------
// Function Definitions

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Procedure:  ComponentNameGetControllerName
//
// DESCRIPTION: Retrieves a Unicode string that is the user readable name of
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
// RETURNS:
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
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

static EFI_STATUS ComponentNameGetDriverName(
    IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **DriverName )
{
    //Supports only English
    if (!Language || !DriverName) 
        return EFI_INVALID_PARAMETER;
    
    if ( !LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH) ) 
        return EFI_UNSUPPORTED;
    else 
        *DriverName = gDriverName;
    
    return EFI_SUCCESS;
}

//Component Name Protocol
static EFI_COMPONENT_NAME2_PROTOCOL gComponentName = {
    ComponentNameGetDriverName,
    ComponentNameGetControllerName,
    LANGUAGE_CODE_ENGLISH
};

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   DiskIoEntryPoint
//
// Description: Installs the Driver Binding Protocol for the Disk
//      I/O Driver
//
// Input:
//      ImageHandle - Identification Handle for the Disk I/O driver
//      *SystemTable - Pointer to the EFI System Handle
//
// Output:
//      EFI_SUCCESS - if the Binding Protocol is installed
//
//
// Modified:
//
// Referrals: InstallMultipleProtocolInterfaces
//
// Notes:
//  Here is the control flow of this function:
//  1. Initialize Ami Lib.
//  2. Install Driver Binding Protocol
//  3. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  DiskIoEntryPoint(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS  Status;
    
    // Initialize global variable for use in this driver
    gBS = SystemTable->BootServices;
    
    // initiaize the ImageHandle and DriverBindingHandle
    gDiskIoDriverBindingProtocol.DriverBindingHandle = NULL;
    gDiskIoDriverBindingProtocol.ImageHandle = ImageHandle;
    
    Status = gBS->InstallMultipleProtocolInterfaces(
        &gDiskIoDriverBindingProtocol.DriverBindingHandle,
        &gEfiDriverBindingProtocolGuid, 
        &gDiskIoDriverBindingProtocol,
#ifdef EFI_DEBUG
        &gEfiComponentName2ProtocolGuid, 
        &gComponentName,
#endif
        NULL
    );
    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   DiskIoSupported
//
// Description: Checks whether Block I/O protocol is installed on the
//      Controller
//
// Input:
//      *This - pointer to the Briver Binding instance of the
//          Disk I/O Protocol
//      Controller - The Controller that is looking for drivers that
//          operate on it
//      *RemainingDevicePath -
//
// Output:
//      EFI_SUCCESS - Driver supports the Controller that is passed in
//      EFI_UNSUPPORTED - The Driver Does not support the Controller
//              that is passed in
//
// Referrals: OpenProtocol CloseProtocol
//
// Notes:
//  Here is the control flow of this function:
//  1. Check whether Block I/O driver is installed and not being used
//      by another driver
//  2. Return EFI_SUCCESS or EFI_UNSUPPORTED
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI DiskIoSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
)
{
    EFI_STATUS Status;
    EFI_BLOCK_IO_PROTOCOL *BlockIo;
    
    // Check to see if the BlockIo Protocol in installed on the ControllerHandle
    //  if so, CloseProtocol and return success, otherwise exit with an error
    Status = gBS->OpenProtocol ( 
        ControllerHandle, 
        &gEfiBlockIoProtocolGuid,
        (VOID**)&BlockIo, 
        This->DriverBindingHandle,
        ControllerHandle,   
        EFI_OPEN_PROTOCOL_BY_DRIVER
    );
    
    if (EFI_ERROR(Status))
        return Status;
    
    return gBS->CloseProtocol (
        ControllerHandle, 
        &gEfiBlockIoProtocolGuid,
        This->DriverBindingHandle, 
        ControllerHandle 
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   DiskIoStart
//
// Description: Installs DiskIo Protocol on the Controller
//
// Input:
//      *This - Pointer to an instance of the Disk I/O protocol
//      Controller - The controller being operated on
//      *RemainingDevicePath -
//
// Output:
//      EFI_SUCCESS - if Driver was installed properly
//      Errors - Returns any error that would cause the protocol not
//          to be installed
//
// Referrals: OpenProtocol CloseProtocol InstallProtocolInterface
//      AllocatePool CopyMem FreePool
//
// Notes:
//  Here is the control flow of this function:
//  1. Open the Block I/O protocol BY_DRIVER
//  2. Allocate memory for the new instance of the Disk I/O Data Structure
//  3. Copy the Default Data into the newly allocated memory
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  EFIAPI  DiskIoStart (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
)
{
    EFI_STATUS Status;
    DISK_IO_DATA *DiskIo;
    
    // make sure that the controller handle has the BlockIo Protocol installed on it
    Status = gBS->OpenProtocol (
        ControllerHandle, 
        &gEfiBlockIoProtocolGuid,
        (VOID**)&gDiskIoData.BlockIo,
        This->DriverBindingHandle, 
        ControllerHandle,
        EFI_OPEN_PROTOCOL_BY_DRIVER
    );
    
    // If not error out
    if (EFI_ERROR (Status))  
        return Status;
    
    // Allocate memory for the private data structure for the instance of the driver
    Status = gBS->AllocatePool( 
        EfiBootServicesData,
        sizeof(DISK_IO_DATA), 
        &DiskIo 
    );
                                
    // if no memory is available, exit with error
    if (EFI_ERROR(Status)) 
        return Status;
    
    // copy the corrct data into it
    gBS->CopyMem(
        DiskIo, 
        &gDiskIoData, 
        sizeof(DISK_IO_DATA)
    );
    
    // Install the Protocol on the handle if it has a BlockIo Protocol alread installed
    Status = gBS->InstallProtocolInterface(
        &ControllerHandle, 
        &gEfiDiskIoProtocolGuid,
        EFI_NATIVE_INTERFACE, 
        &DiskIo->DiskIo
    );
    
    // If there is an error when installing the protocol, reverse everything that was done
    if (EFI_ERROR(Status)) {
        gBS->FreePool(DiskIo);
        gBS->CloseProtocol( 
            ControllerHandle, 
            &gEfiBlockIoProtocolGuid,
            This->DriverBindingHandle, 
            ControllerHandle
        );
    }
    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   DiskIoStop
//
// Description: Uninstalls DiskIo Protocol on the Controller
//
// Input:
//      *This - Pointer to an instance of the Disk I/O protocol
//      Controller - The controller being operated on
//      *RemainingDevicePath -
//
// Output:
//      EFI_SUCCESS - if Driver was Uninstalled properly
//      EFI_UNSUPPORTED - Disk I/O was not installed on the Controller
//      Errors - Returns any error that would cause the protocol not
//          to be installed
//
// Referrals: OpenProtocol CloseProtocol UnInstallProtocolInterface
//      FreePool
//
// Notes:
//  Here is the control flow of this function:
//  1. Open the Disk I/O protocol by GET_DERIVER
//  2. Uninstall the protocol
//  3. Free the allocated Memory
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  EFIAPI  DiskIoStop (
    IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN  EFI_HANDLE                     ControllerHandle,
    IN  UINTN                          NumberOfChildren,
    IN  EFI_HANDLE                     *ChildHandleBuffer
)
{
    EFI_STATUS Status;
    EFI_DISK_IO_PROTOCOL *DiskIoProtocol;
    DISK_IO_DATA *DiskIo;
    
    // Unistall all protocols installed installed in DriverBindingStart
    // open the disk Io protocol
    Status = gBS->OpenProtocol(
        ControllerHandle,
        &gEfiDiskIoProtocolGuid,
        (VOID**)&DiskIoProtocol,
        This->DriverBindingHandle,
        ControllerHandle,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
             
    if (EFI_ERROR (Status)) 
        return EFI_UNSUPPORTED;
    
    // Find the pointer to the parent structure
    //  in this case, DiskIo is the first element in the data structure
    DiskIo = (DISK_IO_DATA*)DiskIoProtocol;
    
    // Uninstall the protocol interface
    Status = gBS->UninstallProtocolInterface(
        ControllerHandle,
        &gEfiDiskIoProtocolGuid,
        &DiskIo->DiskIo
    );
             
    // if the interface is uninstalled then close the protocol
    if (!EFI_ERROR (Status)) {
        Status = gBS->CloseProtocol(
            ControllerHandle, 
            &gEfiBlockIoProtocolGuid,
            This->DriverBindingHandle, 
            ControllerHandle
        );
    }
    
    // if the protocol is closed, then free the data structure
    if (!EFI_ERROR (Status))
        Status = gBS->FreePool(DiskIo);
        
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   CalcAlignmentValues
//
// Description: Calculates FirstBlock, Numblocks, and the amount
//      of data above and below an alignment value
//
// Input:
//      *Media - pointer to the media data structure that is being
//          operated on
//      Offset - byte value that is the offset into the media that
//          indicates where the buffer starts
//      BufferSize - Size of the entire buffer to read
//
// Output:
//      *BelowAlign - Number of bytes below an aligned value where
//              the Buffer starts
//      *AboveAlign - Number of bytes above an aligned value where
//              the Buffer ends
//      *FirstBlock - First block that needs to be read to get the
//              entire buffer
//      *NumBlocks - number of blocks to be read
//
// Return: VOID
//
// Referrals: Div64
//
// Notes:
//  Here is the control flow of this function:
//  1. Calculate the first block of the media to read
//  2. calculate the number of blocks to read
//  3. Check for any data area that is ablove the final aligned block
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CalcAlignmentValues(
    IN  EFI_BLOCK_IO_MEDIA      *Media,
    IN  UINT64                  Offset,
    IN  UINT64                  BufferSize,
    OUT UINTN                   *BelowAlign,
    OUT UINTN                   *AboveAlign,
    OUT UINT64                  *FirstBlock,
    OUT UINT64                  *NumBlocks
)
{
    UINT64  Temp;
    
    // Find out if the Offset is aligned and the remainder if it is not
    // use 64 bit division function
    *FirstBlock = Div64(
        Offset, 
        Media->BlockSize, 
        BelowAlign
    );
    
    // Find out if the ending point is aligned and the remainder if it is not
    // use 64 bit division function
    Temp = Div64(
        Offset + BufferSize, 
        Media->BlockSize, 
        AboveAlign
    );
    
    // Calculate the total number of blocks to be read/written
    *NumBlocks = Temp - *FirstBlock;
    
    if (*AboveAlign) 
        (*NumBlocks)++;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   ReadDiskIo
//
// Description: Reads the data from the media specified by the parameters
//      that are passed in
//
// Input:
//      *This - Pointer to the Disk I/O protocol instance
//      MediaId - media ID of the device to read from
//      Offset - byte offset where to start reading
//      BufferSize - amount of data to read
//
// Output:
//      *Buffer - location to store the data read from the media
//
// Return:
//      EFI_SUCCESS - Function Read the Buffer properly or BufferSize = 0
//      EFI_MEDIA_CHANGED - Media changed since last operation
//      EFI_INVALID_PARAMETER - Buffer does not fit within the Media
//
// Referrals: Mul64 AllocatePool CalcAlignmentValues CopyMem
//      FreePool BlockIo->ReadBlock
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReadDiskIo (
    IN EFI_DISK_IO_PROTOCOL *This,
    IN UINT32 MediaId,
    IN UINT64 Offset,
    IN UINTN BufferSize,
    OUT VOID *Buffer
)
{
    DISK_IO_DATA    *Container;
    UINT64          StartBlock = 0;
    UINT64          NumBlocks  = 0;
    UINTN           BelowAlign = 0;
    UINTN           AboveAlign = 0;
    UINT32          IoAlign;
    UINTN           Temp;
    UINT8           *DataBuffer, *AlignDataBuffer;
    UINT32          BlockSize;
    EFI_STATUS      Status;
    
    // Get the pointer to the Container Structure
    // DiskIo is the first element of the Data Structure
    //  also define some variables for easier access
    Container = (DISK_IO_DATA*)This;
    BlockSize = Container->BlockIo->Media->BlockSize;
    IoAlign = Container->BlockIo->Media->IoAlign;
    
    // Error Check values here
    if (Container->BlockIo->Media->MediaPresent) {
        if (Container->BlockIo->Media->MediaId != MediaId)
            return EFI_MEDIA_CHANGED;
            
        if ( Offset + BufferSize > Mul64(Container->BlockIo->Media->LastBlock + 1, BlockSize) )
            return EFI_INVALID_PARAMETER;
    }
    
    if (!BufferSize) 
        return EFI_SUCCESS;
    
    if (!BlockSize) 
        return EFI_INVALID_PARAMETER;
    
    // find the needed data
    CalcAlignmentValues(
        Container->BlockIo->Media, 
        Offset, 
        BufferSize,
        &BelowAlign, 
        &AboveAlign, 
        &StartBlock, 
        &NumBlocks
    );
    
    // Allocate a buffer for use in pulling data out of selected blocks
    // Size is generated by total number of blocks to be read plus the IoAlignment
    //  value so that the buffer will have plenty of space in it if needed
    Temp = BlockSize * (UINTN)NumBlocks;
    
    if ( Temp>BufferSize || IoAlign && ( (UINTN)Buffer & (IoAlign - 1) ) ) {
        if (IoAlign > 1) 
            Temp += IoAlign;
        
        Status = gBS->AllocatePool(
            EfiBootServicesData, 
            Temp, 
            &DataBuffer 
        );
        
        // No buffer allocated: exit, no need to free the memory
        if (Status != EFI_SUCCESS)  
            return EFI_OUT_OF_RESOURCES;
        
        AlignDataBuffer = (IoAlign <= 1) ? 
            DataBuffer : DataBuffer + IoAlign - ( (UINTN)DataBuffer & (IoAlign - 1) );
            
    } else
        AlignDataBuffer = Buffer;
    
    Status = Container->BlockIo->ReadBlocks(
        Container->BlockIo, 
        MediaId, 
        StartBlock,
        BlockSize * (UINTN)NumBlocks, 
        AlignDataBuffer
    );
    
    if (AlignDataBuffer != Buffer) {
        gBS->CopyMem(
            Buffer, 
            AlignDataBuffer + BelowAlign, 
            BufferSize
        );
        gBS->FreePool(DataBuffer);
    }
    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   WriteDiskIo
//
// Description: Writes the data to the media specified by the parameters
//      that are passed in
//
// Input:
//      *This - Pointer to the Disk I/O protocol instance
//      MediaId - media ID of the device to write to
//      Offset - byte offset where to start wrtiing
//      BufferSize - amount of data to write
//
// Output:
//      *Buffer - location of data that should be written to the media
//
// Return:
//      EFI_SUCCESS - Function wrote the Buffer properly or BufferSize = 0
//      EFI_MEDIA_CHANGED - Media changed since last operation
//      EFI_INVALID_PARAMETER - Buffer does not fit within the Media
//
// Referrals: Mul64 AllocatePool CalcAlignmentValues CopyMem
//      FreePool BlockIo->ReadBlocks BlockIo->WriteBlocks
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS WriteDiskIo (
    IN EFI_DISK_IO_PROTOCOL *This,
    IN UINT32       MediaId,
    IN UINT64       Offset,
    IN UINTN        BufferSize,
    IN VOID         *Buffer
)
{
    DISK_IO_DATA    *Container;
    UINT64          StartBlock = 0;
    UINT64          NumBlocks  = 0;
    UINTN           BelowAlign = 0;
    UINTN           AboveAlign = 0;
    UINTN           IoAlign;
    UINT8           *DataBuffer, *AlignDataBuffer;
    UINT32          BlockSize;
    EFI_STATUS      Status;
    UINTN           Temp;
    
    // Get the pointer to the Container Structure
    // DiskIo is the first element of the Data Structure
    //  also define some variables for easier access
    Container = (DISK_IO_DATA*)This;
    BlockSize = Container->BlockIo->Media->BlockSize;
    IoAlign = Container->BlockIo->Media->IoAlign;
    
    // Error Check values here
    if (Container->BlockIo->Media->MediaId != MediaId)
        return EFI_MEDIA_CHANGED;
        
    if ( Offset + BufferSize > Mul64(Container->BlockIo->Media->LastBlock + 1, BlockSize) )
        return EFI_INVALID_PARAMETER;
        
    if (!BufferSize) 
        return EFI_SUCCESS;
    
    // find the needed data
    CalcAlignmentValues(
        Container->BlockIo->Media, 
        Offset, 
        BufferSize,
        &BelowAlign, 
        &AboveAlign, 
        &StartBlock, 
        &NumBlocks
    );
    
    // Allocate a buffer for use in pulling data out of selected blocks
    // Size is generated by total number of blocks to be read plus the IoAlignment
    //  value so that the buffer will have plenty of space in it if needed
    Temp = BlockSize * (UINTN)NumBlocks;
    
    if ( Temp>BufferSize || IoAlign && ( (UINTN)Buffer & (IoAlign - 1) ) ) {
        if (IoAlign > 1) 
            Temp += IoAlign;
        
        Status = gBS->AllocatePool(
            EfiBootServicesData, 
            Temp, 
            &DataBuffer 
        );
        
        // No buffer allocated: exit, no need to free the memory
        if (Status != EFI_SUCCESS)  
            return EFI_OUT_OF_RESOURCES;
        
        AlignDataBuffer = (IoAlign <= 1) ? 
            DataBuffer : DataBuffer + IoAlign - ( (UINTN)DataBuffer & (IoAlign - 1) );
                          
    } else {

        Status = Container->BlockIo->WriteBlocks(
            Container->BlockIo, 
            MediaId, 
            StartBlock, 
            BufferSize, 
            Buffer
        );
        return Status;
    }
    
    if ( AboveAlign && (NumBlocks > 1 || !BelowAlign) )  {
        // Read the block that contains the data at the beginning of the block
        Status = Container->BlockIo->ReadBlocks(
            Container->BlockIo, 
            MediaId,
            StartBlock + NumBlocks - 1, 
            BlockSize, 
            AlignDataBuffer
        );
                 
        // Check to see if the BlockIo protocol reported an error
        if (Status != EFI_SUCCESS) {
            gBS->FreePool(DataBuffer);
            return Status;
        }
        
        // just copy the data above the alignment address, not the complete block
        gBS->CopyMem(
            AlignDataBuffer + (UINTN)(NumBlocks - 1) * BlockSize + AboveAlign,
            AlignDataBuffer + AboveAlign, 
            BlockSize - AboveAlign
        );
    }
    
    // see if we need to only pull the data from the end of a block
    if (BelowAlign) {
        // read the block that contains the data at the end of the block
        // Advance StartBlock to the next block after reading the current block
        Status = Container->BlockIo->ReadBlocks(
            Container->BlockIo, 
            MediaId,
            StartBlock, 
            BlockSize, 
            AlignDataBuffer
        );

                 
        // Check to see if the BlockIo protocol reported an error
        if (Status != EFI_SUCCESS) {
            gBS->FreePool(DataBuffer);
            return Status;
        }
    }
    
    // Copy that data to allocated memory
    gBS->CopyMem(
        AlignDataBuffer + BelowAlign, 
        Buffer, 
        BufferSize
    );
    
    // Write full blocks of data from the block I/O driver
    Status = Container->BlockIo->WriteBlocks(
        Container->BlockIo, 
        MediaId, 
        StartBlock,
        (UINTN)NumBlocks * BlockSize, 
        AlignDataBuffer
    );
    
    // Free allocated memory
    gBS->FreePool(DataBuffer);
    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
