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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusDxe.c 1     6/06/12 8:00a Victortu $
//
// $Revision: 1 $
//
// $Date: 6/06/12 8:00a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusDxe.c $
// 
// 1     6/06/12 8:00a Victortu
// Implement EFI_PEI_SMBUS2_PPI Support.
// 
// 11    7/21/11 7:32a Abelwu
// [TAG]  		None
// [Category]  	New Feature
// [Description]  	Added SMBus SMM protocol support.
// [Files]  		SmBusDxe.c
// 
// 10    7/19/11 8:28a Abelwu
// [TAG]  		EIP63768
// [Category]  	Improvement
// [Description]  	1. Supported Core 4.6.5.x PI 1.2 / uEFI 2.3.1
// compliance
// 2. Added SMBus SMM protocol support.
// 
// 9     6/17/11 5:54p Artems
// EIP 53378: Replaced tabs with spaces, formatted to follow coding
// standard
// 
// 8     5/18/11 11:51a Artems
// 
// 7     1/27/11 9:48p Abelwu
// Supports SMBUS Protocol in early DXE phase. (EIP#40778)
// 
// 6     10/13/10 4:16p Artems
// EIP 45184 - fixed pointer size to be same in IA32 and X64 mode
// 
// 5     10/16/09 7:32p Artems
// Updated copyright header
// 
// 4     3/03/09 4:36p Artems
// EIP 19949 Added support for multiple SM Bus controllers that
// represented by different PCI devices
// 
// 3     1/29/09 4:20p Artems
// Change "Note" to "Notes" for HelpBuilder
// 
// 2     1/28/09 6:51p Artems
// Modified in accordance with coding standard
// 
// 1     1/09/09 6:53p Artems
// New implementation of SMBus EIP 16730
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:        SmBusDxe.c
//
// Description: SMBUS DXE functions implementation
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiHobs.h>
#include "SmBusDxe.h"
#include <Protocol\PciRootBridgeIo.h>

#define MICROSECOND     10
#define MILLISECOND     (1000 * MICROSECOND)
#define ONESECOND       (1000 * MILLISECOND)

extern EFI_GUID SmBusIdentifierGuid;

EFI_DRIVER_BINDING_PROTOCOL SmBusDriverBindingProtocol = {
    DriverBindingSupported,
    DriverBindingStart,
    DriverBindingStop,
    0x10,
    NULL,
    NULL
    };

SMBUS_DXE_PRIVATE *gPrivate;
EFI_HANDLE gControllerHandle = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmBusEarlyDxeDriver
//
// Description: This function configures and installs SMBUS protocol before
//              SMBus EFI 1.1 drvier is installed.
//
// Input:       None
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - SMBUS protocol has been installed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmBusEarlyDxeDriver ( VOID )
{
    EFI_STATUS                      Status;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo = NULL;
    EFI_GUID                        EfiPciRootBridgeIoProtocolGuid = \
                                        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
/* Porting Required
    UINT32                          IoBase32;
    UINT16                          Cmd16;
Porting End */

    Status = pBS->AllocatePool( EfiBootServicesData, \
                                sizeof(SMBUS_DXE_PRIVATE), \
                                &gPrivate );
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->AllocatePool( \
                        EfiBootServicesData, \
                        sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_DXE_ARP_DEVICES, \
                        &(gPrivate->SmBusContext.ArpDeviceList) );
    if (EFI_ERROR(Status)) {
        pBS->FreePool( gPrivate );
        return Status;
    }

    gPrivate->SmBusProtocol.Execute   = SmBusDxeExecute;
    gPrivate->SmBusProtocol.ArpDevice = SmBusDxeArpDevice;
    gPrivate->SmBusProtocol.GetArpMap = SmBusDxeGetArpMap;
    gPrivate->SmBusProtocol.Notify    = SmBusDxeNotify;

    gPrivate->NotifyEvent = NULL;
    gPrivate->Identifier = SmBusIdentifierGuid;

    gPrivate->SmBusContext.SmBusWait = SmBusDxeWait;
    gPrivate->SmBusContext.MaxDevices = MAX_DXE_ARP_DEVICES;
    RetrieveHobData( gPrivate );

/* Porting Required
    Status = pBS->LocateProtocol( &EfiPciRootBridgeIoProtocolGuid, \
                                  NULL, \
                                  &PciRootBridgeIo );
    // Update SMBus I/O Base Address
    PciRootBridgeIo->Pci.Read( PciRootBridgeIo, \
                               EfiPciWidthUint32, \
                               SMBUS_REG(SMBUS_REG_BASE_ADDR), \
                               1, \
                               &IoBase32 );
    IoBase32 &= 0xfffffffe;
    gPrivate->SmBusContext.SmBusBase = (UINT16)IoBase32;

    // Enable SMBus controller I/O decode.
    PciRootBridgeIo->Pci.Read( PciRootBridgeIo, \
                               EfiPciWidthUint16, \
                               SMBUS_REG(SMBUS_REG_PCICMD), \
                               1, \
                               &Cmd16 );
    Cmd16 |= 1;
    PciRootBridgeIo->Pci.Write( PciRootBridgeIo, \
                                EfiPciWidthUint16, \
                                SMBUS_REG(SMBUS_REG_PCICMD), \
                                1, \
                                &Cmd16 );
Porting End */

    Status = pBS->InstallProtocolInterface( &gControllerHandle, \
                                            &gEfiSmbusProtocolGuid, \
                                            EFI_NATIVE_INTERFACE,
                                            &gPrivate->SmBusProtocol );

    if (EFI_ERROR(Status)) {
        TRACE((-1, "SBSmbusDxe: Install Protocol Interface Failed.\n"));
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmBusSmmExecute
//
// Description: This Protocol Function can be used to execute SMBus command
//              on a particular SMBus controller in SMM.
//
// Input:       *This        - Pointer to the SMBus Protocol structure
//              SlaveAddress - Address of the SMBus device
//              Command      - Command to be sent to the device
//              Operation    - SMBus operation to be performed
//              PecCheck     - Flag indicating the usage of PEC
//              *Length      - Length of the data in the Buffer (IN or OUT)
//              *Buffer      - Pointer to the buffer with the data (IN or OUT)
//
// Output:      EFI_STATUS
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmBusSmmExecute (
    IN EFI_SMBUS_HC_PROTOCOL            *This,
    IN EFI_SMBUS_DEVICE_ADDRESS         SlaveAddress,
    IN EFI_SMBUS_DEVICE_COMMAND         Command,
    IN EFI_SMBUS_OPERATION              Operation,
    IN BOOLEAN                          PecCheck,
    IN OUT UINTN                        *Length,
    IN OUT VOID                         *Buffer )
{
    EFI_STATUS  Status = EFI_UNSUPPORTED;
/*
    // Porting Required
    UINT16      SmBusBase = READ_PCI16_SMBUS(SMBUS_REG_BASE_ADDR) & 0xfff0;
    UINT16      SmBusCmd = READ_PCI16_SMBUS(SMBUS_REG_PCICMD);

    if (SmBusBase == 0) { // Assign a new I/O if the original address is 0
        WRITE_PCI16_SMBUS(SMBUS_REG_BASE_ADDR, SMBUS_BASE_ADDRESS);
        SmBusBase = SMBUS_BASE_ADDRESS;
    }

    gPrivate->SmBusContext.SmBusBase = SmBusBase;

    if ((SmBusCmd & 1) == 0) { // Enable I/O command if needed.
        WRITE_PCI16_SMBUS(SMBUS_REG_PCICMD, 1);
    }
    // Porting End

    Status = Execute( &(((SMBUS_DXE_PRIVATE *)This)->SmBusContext), \
                      SlaveAddress, \
                      Command, \
                      Operation, \
                      PecCheck, \
                      Length, \
                      Buffer );

    // Porting Required
    // Restore the SMBus PCI Command Register
    WRITE_PCI16_SMBUS(SMBUS_REG_PCICMD, SmBusCmd);
    // Porting End
*/
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SMBusInSmmInit
//
// Description: This function installs SMBus SMM protocol for the SMBus
//              controller present in the SB.
//
// Input:       ImageHandle  - Image handle for the SB component
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SMBusInSmmInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_HANDLE                  Handle = NULL;
    EFI_GUID                    SmmSmbusProtocolGuid = \
                                                AMI_SMBUS_SMM_PROTOCOL_GUID;
    static SMBUS_DXE_PRIVATE    SmbusSmmPrivate;

    gPrivate = &SmbusSmmPrivate;
    gPrivate->SmBusProtocol.Execute   = SmBusSmmExecute;
    gPrivate->SmBusProtocol.ArpDevice = SmBusDxeArpDevice;
    gPrivate->SmBusProtocol.GetArpMap = SmBusDxeGetArpMap;
    gPrivate->SmBusProtocol.Notify    = SmBusDxeNotify;

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    Status = InitAmiSmmLib( ImageHandle, SystemTable );
    if (EFI_ERROR(Status)) return Status;

    return pSmst->SmmInstallProtocolInterface( &Handle, \
                                               &SmmSmbusProtocolGuid, \
                                               EFI_NATIVE_INTERFACE, \
                                               &gPrivate->SmBusProtocol );
#else
    return pBS->InstallProtocolInterface( &Handle,
                                          &SmmSmbusProtocolGuid,
                                          EFI_NATIVE_INTERFACE,
                                          &gPrivate->SmBusProtocol );
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SMBusNotInSmmInit
//
// Description: This function installs SMBus DXE protocol for the SMBus
//              controller present in the SB.
//
// Input:       ImageHandle  - Image handle for the SB component
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SMBusNotInSmmInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS  Status;

    Status = SmBusEarlyDxeDriver();

#if SMBUS_BLINDING_PROTOCOL_SUPPORT
    SmBusDriverBindingProtocol.ImageHandle = ImageHandle;
    SmBusDriverBindingProtocol.DriverBindingHandle = ImageHandle;
    Status = pBS->InstallMultipleProtocolInterfaces( \
                                             &ImageHandle, \
                                             &gEfiDriverBindingProtocolGuid, \
                                             &SmBusDriverBindingProtocol, \
                                             NULL );
#endif
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmBusDxeEntryPoint
//
// Description: This function installs SMBus DXE/SMM protocols for the SMBus
//              controller present in the SB.
//
// Input:       ImageHandle  - Image handle for the SB component
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmBusDxeEntryPoint (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    InitAmiLib(ImageHandle, SystemTable);

    return InitSmmHandlerEx( ImageHandle, \
                             SystemTable, \
                             SMBusInSmmInit, \
                             SMBusNotInSmmInit );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DriverBindingSupported
//
//  Description: SMBUS DXE Driver binding protocol Supported function
//
//  Input:       IN EFI_DRIVER_BINDING_PROTOCOL* This - pointer to EFI_DRIVER_BINDING_PROTOCOL structure
//               IN EFI_HANDLE ControllerHandle - handle of controller to serve
//               IN EFI_DEVICE_PATH_PROTOCOL* RemainingDevicePath - pointer to EFI_DEVICE_PATH_PROTOCOL structure
//
//  Output:      EFI_SUCCESS - driver supports given controller
//               EFI_UNSUPPORTED - given controller not supported  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS  DriverBindingSupported ( 
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
)
{
    EFI_STATUS          Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINT8               PciData[4];

    Status = pBS->OpenProtocol (
                            ControllerHandle,
                            &gEfiPciIoProtocolGuid,
                            (VOID **) &PciIo,
                            This->DriverBindingHandle,
                            ControllerHandle,
                            EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR (Status))
        return EFI_UNSUPPORTED;

  //
  // See if this is a PCI Smbus Controller by looking at the Class Code Register
  //
    Status = PciIo->Pci.Read (
                            PciIo,
                            EfiPciIoWidthUint32,
                            0x8,
                            1,
                            (VOID *)PciData );
    if (EFI_ERROR (Status))
        return EFI_UNSUPPORTED;

    pBS->CloseProtocol (
         ControllerHandle,
         &gEfiPciIoProtocolGuid,
         This->DriverBindingHandle,
         ControllerHandle );

    return (PciData[3] == 0x0c && PciData[2] == 0x05) ? EFI_SUCCESS : EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DriverBindingStart
//
//  Description: SMBUS DXE Driver binding protocol Start function
//
//  Input:       IN EFI_DRIVER_BINDING_PROTOCOL* This - pointer to EFI_DRIVER_BINDING_PROTOCOL structure
//               IN EFI_HANDLE ControllerHandle - handle of controller to serve
//               IN EFI_DEVICE_PATH_PROTOCOL* RemainingDevicePath - pointer to EFI_DEVICE_PATH_PROTOCOL structure
//
//  Output:      EFI_SUCCESS - driver supports given controller
//               EFI_UNSUPPORTED - given controller not supported  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS  DriverBindingStart ( 
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
)
{
    EFI_STATUS Status;
    SMBUS_DXE_PRIVATE *Private;
    static BOOLEAN          EarlyDxeProtocol = TRUE;

    if (EarlyDxeProtocol) {
        Status = pBS->UninstallProtocolInterface( gControllerHandle, \
                                                  &gEfiSmbusProtocolGuid, \
                                                  &gPrivate->SmBusProtocol );
        if (Status == EFI_SUCCESS) {
            pBS->FreePool( gPrivate->SmBusContext.ArpDeviceList );
            pBS->FreePool( gPrivate );
        }
        EarlyDxeProtocol = FALSE;
    }

    Status = pBS->AllocatePool(EfiBootServicesData, 
                               sizeof(SMBUS_DXE_PRIVATE),
                               &Private);
    if(EFI_ERROR(Status))
        return Status;

    Status = pBS->AllocatePool(EfiBootServicesData, 
                               sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_DXE_ARP_DEVICES,
                               &(Private->SmBusContext.ArpDeviceList));
    if(EFI_ERROR(Status))
        return Status;

    Status = pBS->OpenProtocol (
                            ControllerHandle,
                            &gEfiPciIoProtocolGuid,
                            (VOID **) &(Private->PciIo),
                            This->DriverBindingHandle,
                            ControllerHandle,
                            EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR (Status))
    {
        pBS->FreePool(Private->SmBusContext.ArpDeviceList);
        pBS->FreePool(Private);
        return Status;
    }

    Private->SmBusProtocol.Execute   = SmBusDxeExecute;
    Private->SmBusProtocol.ArpDevice = SmBusDxeArpDevice;
    Private->SmBusProtocol.GetArpMap = SmBusDxeGetArpMap;
    Private->SmBusProtocol.Notify    = SmBusDxeNotify;

    Private->NotifyEvent = NULL;
    Private->Identifier = SmBusIdentifierGuid;

    Private->SmBusContext.SmBusWait = SmBusDxeWait;
    Private->SmBusContext.MaxDevices = MAX_DXE_ARP_DEVICES;
    RetrieveHobData(Private);

//TODO Fill Private->SmBusContext.SmBusBase with value read from PCI device

    DListInit(&(Private->NotifyList));

    Status = pBS->InstallMultipleProtocolInterfaces(
                    &ControllerHandle,
                    &gEfiSmbusProtocolGuid, &Private->SmBusProtocol,
                    NULL);
    if (EFI_ERROR (Status))
    {
        pBS->CloseProtocol(
                        ControllerHandle,
                        &gEfiPciIoProtocolGuid,
                        This->DriverBindingHandle,
                        ControllerHandle );
        pBS->FreePool(Private->SmBusContext.ArpDeviceList);
        pBS->FreePool(Private);
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   DriverBindingStop
//
//  Description: SMBUS DXE Driver binding protocol Stop function
//
//  Input:       IN EFI_DRIVER_BINDING_PROTOCOL* This - pointer to EFI_DRIVER_BINDING_PROTOCOL structure
//               IN EFI_HANDLE ControllerHandle - handle of controller to serve
//               IN UINTN NumberOfChildren - number of child devices of controller
//               IN EFI_HANDLE* ChildHandleBuffer - pointer to child devices handles array
//
//  Output:      EFI_SUCCESS - driver was successfully uninstalled from controller
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS  DriverBindingStop ( 
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   ControllerHandle,
    IN  UINTN                       NumberOfChildren,
    IN  EFI_HANDLE                  *ChildHandleBuffer
)
{
    EFI_STATUS              Status;
    SMBUS_DXE_PRIVATE       *Private;
    EFI_SMBUS_HC_PROTOCOL   *SmBusProtocol;

    Status = pBS->OpenProtocol (
                        ControllerHandle, 
                        &gEfiSmbusProtocolGuid, 
                        &SmBusProtocol, 
                        This->DriverBindingHandle, 
                        ControllerHandle, 
                        EFI_OPEN_PROTOCOL_GET_PROTOCOL );
    if (EFI_ERROR (Status))
        return EFI_NOT_STARTED;

    pBS->CloseProtocol (
                    ControllerHandle, 
                    &gEfiSmbusProtocolGuid, 
                    This->DriverBindingHandle, 
                    ControllerHandle );

    Private = (SMBUS_DXE_PRIVATE *) SmBusProtocol;  

    // uninstall the protocol
    Status = pBS->UninstallMultipleProtocolInterfaces ( 
                    ControllerHandle,            
                    &gEfiSmbusProtocolGuid, &Private->SmBusProtocol,
                    NULL );
    if (EFI_ERROR (Status))
        return Status;

    if(Private->NotifyEvent != 0)
    {
        SMBUS_NOTIFY_LINK *NotifyLink = (SMBUS_NOTIFY_LINK *)(Private->NotifyList.pHead);
        SMBUS_NOTIFY_LINK *DeleteLink;

        pBS->CloseEvent(Private->NotifyEvent);
        while(NotifyLink != 0)
        {
            DeleteLink = NotifyLink;
            NotifyLink = (SMBUS_NOTIFY_LINK *)NotifyLink->Link.pNext;
            pBS->FreePool(DeleteLink);
        }
    }

    pBS->CloseProtocol (
                    ControllerHandle, 
                    &gEfiPciIoProtocolGuid, 
                    This->DriverBindingHandle, 
                    ControllerHandle );
    pBS->FreePool(Private->SmBusContext.ArpDeviceList);
    pBS->FreePool(Private);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusPeiExecute
//
// Description: EFI_SMBUS_HC_PROTOCOL Execute function
//
// Input:       IN EFI_SMBUS_HC_PROTOCOL *This - pointer to EFI_SMBUS_HC_PROTOCOL structure
//              IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress - slave address
//              IN EFI_SMBUS_DEVICE_COMMAND Command - command
//              IN EFI_SMBUS_OPERATION Operation - operation
//              IN BOOLEAN PecCheck - parity check flag
//              IN OUT UINTN *Length - pointer to size of data buffer
//              IN OUT VOID *Buffer - pointer to data buffer
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusDxeExecute (
    IN      EFI_SMBUS_HC_PROTOCOL         *This,
    IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
    IN      EFI_SMBUS_DEVICE_COMMAND      Command,
    IN      EFI_SMBUS_OPERATION           Operation,
    IN      BOOLEAN                       PecCheck,
    IN OUT  UINTN                         *Length,
    IN OUT  VOID                          *Buffer
)
{
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)This;

    return Execute(
                &(Private->SmBusContext),
                SlaveAddress,
                Command,
                Operation,
                PecCheck,
                Length,
                Buffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusDxeArpDevice
//
// Description: EFI_SMBUS_HC_PROTOCOL ArpDevice function
//
// Input:       IN EFI_SMBUS_HC_PROTOCOL *This - pointer to EFI_SMBUS_HC_PROTOCOL structure
//              IN EFI_PEI_SMBUS_PPI *This - pointer to PPI
//              IN BOOLEAN ArpAll - Enumerate all devices flag
//              IN EFI_SMBUS_UDID *SmbusUdid - pointer to device ID to assign new address
//              IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress - pointer to return assigned address
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusDxeArpDevice (
    IN      EFI_SMBUS_HC_PROTOCOL         *This,
    IN      BOOLEAN                       ArpAll,
    IN      EFI_SMBUS_UDID                *SmbusUdid, OPTIONAL
    IN OUT  EFI_SMBUS_DEVICE_ADDRESS      *SlaveAddress OPTIONAL
)
{
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)This;

    return ArpDevice(
                &(Private->SmBusContext),
                ArpAll,
                SmbusUdid,
                SlaveAddress);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusDxeGetArpMap
//
// Description: EFI_SMBUS_HC_PROTOCOL GetArpMap function
//
// Input:       IN EFI_SMBUS_HC_PROTOCOL *This - pointer to EFI_SMBUS_HC_PROTOCOL structure
//              IN OUT UINTN *Length - pointer to store size of address map
//              IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap - pointer to store pointer to address map
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusDxeGetArpMap (
    IN      EFI_SMBUS_HC_PROTOCOL         *This,
    IN OUT  UINTN                         *Length,
    IN OUT  EFI_SMBUS_DEVICE_MAP          **SmbusDeviceMap
)
{
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)This;

    return GetArpMap(
                &(Private->SmBusContext),
                Length,
                SmbusDeviceMap);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusDxeNotify
//
// Description: EFI_SMBUS_HC_PROTOCOL Notify function
//
// Input:       IN EFI_SMBUS_HC_PROTOCOL *This - pointer to EFI_SMBUS_HC_PROTOCOL structure
//              IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress - address of notification device
//              IN UINTN Data - notification data
//              IN EFI_SMBUS_NOTIFY_FUNCTION NotifyFunction - pointer to callback function
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmBusDxeNotify (
    IN      EFI_SMBUS_HC_PROTOCOL         *This,
    IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
    IN      UINTN                         Data,
    IN      EFI_SMBUS_NOTIFY_FUNCTION     NotifyFunction
)
{
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)This;
    SMBUS_NOTIFY_LINK *NewLink;
    EFI_STATUS        Status;

    if(NotifyFunction == NULL)
        return EFI_INVALID_PARAMETER;

    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(SMBUS_NOTIFY_LINK), &NewLink);
    if(EFI_ERROR(Status))
        return Status;

    NewLink->SlaveAddress   = SlaveAddress;
    NewLink->Data           = Data;
    NewLink->NotifyFunction = NotifyFunction;

    DListAdd(&(Private->NotifyList), (DLINK *)NewLink);
    if(Private->NotifyList.Size == 1)
        Status = InitializeNotifyPolling(Private);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitializeNotifyPolling
//
// Description: Function initializes host notify polling periodic event
//
// Input:       IN SMBUS_DXE_PRIVATE *Context - pointer to SMBUS device private data
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitializeNotifyPolling (
    IN SMBUS_DXE_PRIVATE *Context
)
{
    EFI_STATUS Status;

    Status = pBS->CreateEvent (
                  (EFI_EVENT_TIMER | EFI_EVENT_NOTIFY_SIGNAL),
                  TPL_CALLBACK,
                  PollSmbusNotify, 
                  Context,
                  &Context->NotifyEvent );
    if (EFI_ERROR(Status))
        return Status;

    Status = pBS->SetTimer (
                  Context->NotifyEvent,
                  TimerPeriodic,
                  ONESECOND );
    if (EFI_ERROR(Status))
        return Status;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PollSmbusNotify
//
// Description: Function performs periodic check of host notifications
//
// Input:       IN EFI_EVENT Event - periodic check event
//              IN VOID *Context - event calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PollSmbusNotify (
    IN  EFI_EVENT Event,
    IN  VOID      *Context
)
{
    EFI_STATUS Status;
    EFI_SMBUS_DEVICE_ADDRESS Address;
    UINTN Data;
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)Context;
    SMBUS_NOTIFY_LINK *NotifyLink = (SMBUS_NOTIFY_LINK *)(Private->NotifyList.pHead);

    Status = CheckNotify(&(Private->SmBusContext), &Address, &Data);
    if (EFI_ERROR(Status))
        return;

    while(NotifyLink != NULL)
    {
        if(Address.SmbusDeviceAddress == NotifyLink->SlaveAddress.SmbusDeviceAddress && 
           Data == NotifyLink->Data)
            NotifyLink->NotifyFunction(Address, Data);

        NotifyLink = (SMBUS_NOTIFY_LINK *)NotifyLink->Link.pNext;
    }
}

//-------------------------------------------------------------------
// Struct EFI_SMBUS_DEVICE_MAP has one member, that declared as UINTN
// Due to this declaration this struct may have different size if
// compiled in x64 mode - 4 bytes in PEI and 8 bytes in DXE
// So we need mediator structure, to convert from PEI to DXE map, that
// was saved in Hob in PEI phase
//-------------------------------------------------------------------

#pragma pack(1)
typedef struct {
    UINT32  Address;
    EFI_SMBUS_UDID Udid;
} PEI_EFI_SMBUS_DEVICE_MAP;
#pragma pack()

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RetrieveHobData
//
// Description: Function reads device map created in PEI phase
//
// Input:       IN OUT SMBUS_DXE_PRIVATE *Context - pointer to device private data
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RetrieveHobData (
    IN OUT SMBUS_DXE_PRIVATE *Private
)
{
    AMI_SMBUS_HOB *Hob;
    EFI_GUID      HobListGuid = HOB_LIST_GUID;
    EFI_STATUS    Status;
    SMBUS_PRIVATE *Context = &(Private->SmBusContext);

    PEI_EFI_SMBUS_DEVICE_MAP *PeiMap;
    UINT32 i;

    Context->BoardReservedAddressCount = 0;
    Context->BoardReservedAddressList = 0;
    Context->ArpDeviceCount = 0;

    Hob = (AMI_SMBUS_HOB *)GetEfiConfigurationTable(pST, &HobListGuid);

    if(Hob == NULL)
        return;

    Status = FindNextHobByGuid(&(Private->Identifier), &Hob);
    if(EFI_ERROR(Status))
        return;

    Context->BoardReservedAddressCount = Hob->BoardReservedAddressCount;
    Context->BoardReservedAddressList = (UINT8 *)(UINTN)Hob->BoardReservedAddressList;
    Context->ArpDeviceCount = Hob->ArpDeviceCount;

    PeiMap = (PEI_EFI_SMBUS_DEVICE_MAP *)Hob->ArpDeviceList;
    for(i = 0; i < Hob->ArpDeviceCount; i++)
    {
        Context->ArpDeviceList[i].SmbusDeviceAddress.SmbusDeviceAddress = PeiMap[i].Address;
        Context->ArpDeviceList[i].SmbusDeviceUdid = PeiMap[i].Udid;
    }
/*
    MemCpy(Context->ArpDeviceList, 
           Hob->ArpDeviceList,
           Context->ArpDeviceCount * sizeof(EFI_SMBUS_DEVICE_MAP));
*/
}

//**********************************************************************
//                  Porting functions
//**********************************************************************

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmBusDxeWait
//
// Description: This function waits given number of microseconds
//
// Input:       IN UINTN Microseconds - number of microseconds to wait
//
// Output:      None
//
// Notes:       Porting required
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmBusDxeWait(
    IN UINTN Microseconds
)
{
//Porting required - implement wait function for pei phase
}

/*
VOID SmBusDxeInitialize(
    IN SMBUS_PRIVATE *Context
    )
{
//Porting required - initialize PCI device and fill SmBusBase

}
*/

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
