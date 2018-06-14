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
// $Header: /Alaska/SOURCE/Modules/OpalSecurity/OPALSECURITY/OpalSecurity.c 3     12/21/11 8:36p Rajkumarkc $
//
// $Revision: 3 $
//
// $Date: 12/21/11 8:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OpalSecurity/OPALSECURITY/OpalSecurity.c $
// 
// 3     12/21/11 8:36p Rajkumarkc
// [TAG]         EIP77142
// [Category]    BUG FIX & IMPROVEMENT
// [Description] BUG FIX - Changed Little Endian format to Big Endian
//               format while sending commands.
//               IMPROVEMENT - Added support to Lock the Opal hdd if
//               it's unlocked on Bios POST.
// [Files]       IdeOpalSec.c, AhciOpalSec.c, OpalSecurity.c,
//               OpalSecurity.h, OpalSecurity.sdl
// 
// 2     5/19/11 5:59a Anandakrishnanl
// [TAG]  		EIP53565 
// [Category]  	New Feature
// [Description]  	UEFI2.3+ Specifications defines Storage Security
// protocol which needs to be implemented.
// [Files]  		AhciBus.c,IdeBus.c,AHCIOpalSec.c,IDEOpalSec.c,OpalSecurity.c
// ,OpalSecurity.chm,OpalSecurity.cif,OpalSecurity.h,OpalSecurity.mak,Opal
// Security.sdl,PIDEBus.h,StorageSecurityProtocol.CIF,StorageSecurityProto
// col.h
// 
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: OpalSecurity.c
//
// Description: Opal Security Support
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "OpalSecurity.h"

static EFI_GUID gOpalSecInitProtocolGuid       = OPAL_SEC_INIT_PROTOCOL_GUID;
static EFI_GUID gStorageSecurityProtocolGuid   = EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID;

OPAL_SECURITY_INIT_PROTOCOL           *gOpalSecInitProtocol;
STORAGE_SECURITY_COMMAND_PROTOCOL     *gStorageSecurityProtocol;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   OpalSecEntryPoint
//
// Description: This function is the entry point for OpalSecurity 
//              Driver.
//
// Input:
//  EFI_HANDLE          ImageHandle     Image handle.
//  EFI_SYSTEM_TABLE    *SystemTable    Pointer to the EFI system table.
//
// Output:
//  EFI_SUCCESS : OpalSecurity Interface successfully installed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
OpalSecEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable 
)
{
    EFI_HANDLE Handle = NULL;
    EFI_STATUS Status = EFI_SUCCESS;

    InitAmiLib( ImageHandle, SystemTable );

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(OPAL_SECURITY_INIT_PROTOCOL),
                                (VOID**)&gOpalSecInitProtocol );

    if ( EFI_ERROR( Status )){
        return Status;
    }

    gOpalSecInitProtocol->InstallOpalSecurityInterface        = InstallOpalSecurityInterface;
    gOpalSecInitProtocol->UnInstallOpalSecurityInterface      = UnInstallOpalSecurityInterface;

    Status = pBS->InstallProtocolInterface(
        &Handle,
        &gOpalSecInitProtocolGuid,
        EFI_NATIVE_INTERFACE,
        gOpalSecInitProtocol
        );

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   InstallOpalSecurityInterface
//
// Description: Installs StorageSecurityProtocol if the drive supports 
//                Trusted commands
//
// Input:
//      IN VOID             *BusInterface
//      IN BOOLEAN          ModeFlag
//
// Output:
//  EFI_SUCCESS    : StorageSecurity supported.
//  Others         : Not supported.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
InstallOpalSecurityInterface(
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag 
)
{
    EFI_STATUS Status ;
    IDENTIFY_DATA         IdentifyData;
    EFI_HANDLE            IdeDeviceHandle = NULL;

    if ( ModeFlag == FALSE ){
        IdentifyData    = ((IDE_BUS_PROTOCOL*)BusInterface)->IdeDevice.IdentifyData;
        IdeDeviceHandle = ((IDE_BUS_PROTOCOL*)BusInterface)->IdeDeviceHandle;
    }else{
        IdentifyData    = ((SATA_DEVICE_INTERFACE*)BusInterface)->IdentifyData;
        IdeDeviceHandle = ((SATA_DEVICE_INTERFACE*)BusInterface)->IdeDeviceHandle;
    }

    if(!(IdentifyData.Trusted_Computing_Support & 0x01)){
        return EFI_UNSUPPORTED;
    }

    //
    // StorageSecurity Protocol
    //
    Status = pBS->AllocatePool( EfiBootServicesData,
                           sizeof(EFI_STORAGE_SECURITY_COMMAND_PROTOCOL),
                           (VOID**)&gStorageSecurityProtocol );

    if ( ModeFlag == FALSE ){
        gStorageSecurityProtocol->ReceiveData = IdeReceiveData;
        gStorageSecurityProtocol->SendData    = IdeSendData;
    }else{
        gStorageSecurityProtocol->ReceiveData = AhciReceiveData;
        gStorageSecurityProtocol->SendData    = AhciSendData;
    }
    gStorageSecurityProtocol->BusInterface = BusInterface;

    Status = pBS->InstallMultipleProtocolInterfaces(
                      &IdeDeviceHandle,
                      &gStorageSecurityProtocolGuid, gStorageSecurityProtocol,
                      NULL );

// TPer Lock On Reset Feature Support
#if TPer_LOCK_ON_RESET
  
    // Below error status check is to determine if gStorageSecurityProtocol has been
    // installed successfully or not. In case if code inserted in between, this check
    // has to be handled properly.

    if (!EFI_ERROR(Status)) { 
        GetAndStoreSecurityProtocolInformation(
            (EFI_STORAGE_SECURITY_COMMAND_PROTOCOL*)gStorageSecurityProtocol,
            BusInterface
            );
        IssueLockOnResetCommand(
            (EFI_STORAGE_SECURITY_COMMAND_PROTOCOL*)gStorageSecurityProtocol, 
            BusInterface, 
            ModeFlag
            );
    }
#endif

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   UnInstallOpalSecurityInterface
//
// Description: Uninstalls the Opal Security Init Protocol.
//
// Input:
//      IN VOID             *BusInterface,
//      IN BOOLEAN          ModeFlag
//
// Output:
//  EFI_SUCCESS                      : Security Mode supported.
//  EFI_DEVICE_ERROR/EFI_UNSUPPORTED : Not supported.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
UnInstallOpalSecurityInterface(
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag 
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE            IdeDeviceHandle;

    if ( ModeFlag == FALSE ){
        IdeDeviceHandle = ((IDE_BUS_PROTOCOL*)BusInterface)->IdeDeviceHandle;
    }else{
        IdeDeviceHandle = ((SATA_DEVICE_INTERFACE*)BusInterface)->IdeDeviceHandle;
    }

    //
    //  Install Devicepath and BLOCK_IO on a new handle
    //
    Status = pBS->UninstallMultipleProtocolInterfaces(
        IdeDeviceHandle,
        &gOpalSecInitProtocolGuid,
        gOpalSecInitProtocol,
        NULL );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetAndStoreSecurityProtocolInformation
//
// Description: Get and store Security Protocol Information
//
// Input:
//      IN VOID             *BusInterface,
//      IN BOOLEAN          ModeFlag
//
// Output: NONE
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
GetAndStoreSecurityProtocolInformation(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN VOID    *BusInterface
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    SP0_TRUSTED_RECEIVE_PARAMETER_DATA *QueryBuffer = NULL;
    UINT16  ListLength = 0;
    UINT8   SpByte = 0;

    UINTN QueryBufferSize = sizeof(SP0_TRUSTED_RECEIVE_PARAMETER_DATA);

    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(UINT8)*QueryBufferSize, (VOID**)&QueryBuffer);
    if(EFI_ERROR(Status))return EFI_OUT_OF_RESOURCES;

    Status = GetSecurityProtocolInformation(This, QueryBuffer, &QueryBufferSize);
    // GetSecurityProtocolInformation returns error Status. Unsupported Security Protocol.   
    if(EFI_ERROR(Status))  return EFI_UNSUPPORTED;
            
    // The List Length field indicates the total length, in bytes, of the supported security protocol list.
    ListLength = QueryBuffer->ListLengthHigh << 8 | QueryBuffer->ListLengthLow;

    ((STORAGE_SECURITY_COMMAND_PROTOCOL*)This)->SupportedProtocolList = QueryBuffer;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   GetSecurityProtocolInformation
//
// Description: Get Security Protocol Information
//
// Input:     IN    EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
//            OUT   VOID                *QueryBuffer,
//            OUT   UINTN               *QueryBufferSize
//      
//
// Output: NONE
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
GetSecurityProtocolInformation(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN OUT VOID                *QueryBuffer,
    IN OUT UINTN               *QueryBufferSize
 )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    Status = This->ReceiveData( This,
                        0,
                        0,
                        SECURITY_PROTOCOL_INFORMATION,   // Security Protocol ID
                        0x00,   // SP specific id
                        0x200,  // TranferLength
                        QueryBuffer,
                        QueryBufferSize
                        );
    return Status;
    
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IssueLockOnResetCommand
//
// Description: Issues LockOnReset Command.
//
// Input:
//      IN VOID             *BusInterface,
//      IN BOOLEAN          ModeFlag
//
// Output: NONE
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
IssueLockOnResetCommand(
    IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    IN VOID    *BusInterface,
    IN BOOLEAN ModeFlag
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    IDENTIFY_DATA         IdentifyData;
    EFI_HANDLE            IdeDeviceHandle = NULL;
  
    UINT16  ListLength = 0;
    UINT8   SpByte = 0;
    SP0_TRUSTED_RECEIVE_PARAMETER_DATA *SupportedProtocolList = ((STORAGE_SECURITY_COMMAND_PROTOCOL*)This)->SupportedProtocolList;

    if ( ModeFlag == FALSE ){
        IdentifyData    = ((IDE_BUS_PROTOCOL*)BusInterface)->IdeDevice.IdentifyData;
        IdeDeviceHandle = ((IDE_BUS_PROTOCOL*)BusInterface)->IdeDeviceHandle;
    }else{
        IdentifyData    = ((SATA_DEVICE_INTERFACE*)BusInterface)->IdentifyData;
        IdeDeviceHandle = ((SATA_DEVICE_INTERFACE*)BusInterface)->IdeDeviceHandle;
    }

    // The List Length field indicates the total length, in bytes, of the supported security protocol list.
    ListLength = SupportedProtocolList->ListLengthHigh << 8 | SupportedProtocolList->ListLengthLow;
    if(ListLength == 0)  return EFI_UNSUPPORTED;

    // Check the Secutiy supported Protocol List is 0xEE for IEEE 1667 or 0x02 for Native TCG
    for(SpByte = 0; SpByte < ListLength; SpByte++){

        if(SupportedProtocolList->SupportedSPList[SpByte] == SECURITY_PROTOCOL_2)  {
            // Found Supported Security Protocol list NativeTcg.Issue Tcg TPer Reset
            Status = NativeTcgTPerReset(This);
            break; 
        }

        if(SupportedProtocolList->SupportedSPList[SpByte] == SECURITY_PROTOCOL_IEEE1667)  {
            // Found Supported Security Protocol list IEEE 1667. Issue Silo TPer Reset
            // Check if IEEE 1667 bit (bit 7) set in the AdditionalSupported field to 
            // determine whether the device supports Trusted Send/Receive.

            if(!(IdentifyData.Reserved_69_74[0] & 0x80)){
                Status = IEEE67TPerReset(This);
                break; 
            }
        } 
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   NativeTcgTPerReset
//
// Description: Native Tcg TPer Reset
//
// Input:        IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
//
// Output: NONE
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
NativeTcgTPerReset(
        IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This
){
    EFI_STATUS Status = EFI_SUCCESS;
    VOID *TcgResetDataBuffer = NULL;
    UINT32 BufferSize = 0x200;

    Status = pBS->AllocatePool(EfiBootServicesData, BufferSize, (VOID**)&TcgResetDataBuffer);
    if(EFI_ERROR(Status))return EFI_OUT_OF_RESOURCES;

    pBS->SetMem(TcgResetDataBuffer, BufferSize, 0);
    
    // Determined the device supports Native TCG Security Support Protocol 2. Issue TPer Reset.
    Status = This->SendData( This,
                      0,
                      0,
                      SECURITY_PROTOCOL_2,   // Security Protocol 2 ID
                      0x0400, // SP specific id
                      0x200,  // TranferLength - Non zero Value
                      TcgResetDataBuffer
                      );
    pBS->FreePool(TcgResetDataBuffer);

    return Status;
    
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IEEE67TPerReset
//
// Description: IEEE67 TPer Reset 
//
// Input:         IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
//      
//
// Output: NONE
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
IEEE67TPerReset(
        IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT16  SiloTypeIdentifier = 0;
    UINT16   IeeeSilo = 0;
    TCG_SILO_TYPE_IDENTIFIER *ProbeHostDataBuffer = NULL;
    TCG_SILO_TYPE_IDENTIFIER *SupportedSilosArrayBuffer = NULL;

    UINTN SupportedSilosArrayBufferSize = sizeof(TCG_SILO_TYPE_IDENTIFIER);
    UINTN ProbeHostDataBufferSize = sizeof(TCG_SILO_TYPE_IDENTIFIER);
        
    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(UINT8)*ProbeHostDataBufferSize, (VOID**)&ProbeHostDataBuffer);
    if(EFI_ERROR(Status))return EFI_OUT_OF_RESOURCES;

    // Check if TPer has TCG silo by sending probe command to PROBE SILO
    Status = This->SendData( This,
                          0,
                          0,
                          SECURITY_PROTOCOL_IEEE1667,   // Security Protocol ID
                          0x0100, // SP specific id
                          0x200,  // TranferLength
                          ProbeHostDataBuffer
                         );
    if(!EFI_ERROR(Status)) {
        Status = pBS->AllocatePool(EfiBootServicesData, sizeof(UINT8)*SupportedSilosArrayBufferSize, (VOID**)&SupportedSilosArrayBuffer);
        if(EFI_ERROR(Status))return EFI_OUT_OF_RESOURCES;

        // Followed by Trusted Receive Probe command to PROBE SILO
        Status = This->ReceiveData( This,
                            0,
                            0,
                            SECURITY_PROTOCOL_IEEE1667,   // Security Protocol ID
                            0x0100, // SP specific id
                            0x200,  // TranferLength
                            SupportedSilosArrayBuffer,
                            &SupportedSilosArrayBufferSize
                            );

        if(!EFI_ERROR(Status)) {
             // Scan for Silo Identifier(0x0104) available to send TPer Reset silo command payload to Tcg Silo
             SiloTypeIdentifier = SupportedSilosArrayBuffer->SiloTypeIdentifierHigh << 8 | SupportedSilosArrayBuffer->SiloTypeIdentifierLow;
             // Search for IEEE std allocated identifiers only to find  0x0104 present: IEEE  - 0100h to 01FFh 
             for(IeeeSilo = 0x100; IeeeSilo < 0x200; IeeeSilo++)  {
                 if(IeeeSilo == SiloTypeIdentifier) {
                     Status = IssueTPerResetTcgSilo(This);
                     return Status;     
                 }
             }
        }
    }
 
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IssueTPerResetTcgSilo
//
// Description: Issue TPer Reset
//
// Input:         IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
//      
//
// Output: NONE
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
IssueTPerResetTcgSilo(
        IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This
){
    EFI_STATUS Status = EFI_SUCCESS;
    TCG_SILO_TYPE_IDENTIFIER *IeeeResetDataBuffer = NULL;

    UINTN IeeeResetDataBufferSize = sizeof(TCG_SILO_TYPE_IDENTIFIER);

    Status = pBS->AllocatePool(EfiBootServicesData, sizeof(UINT8)*IeeeResetDataBufferSize, (VOID**)&IeeeResetDataBuffer);
    if(EFI_ERROR(Status))return EFI_OUT_OF_RESOURCES;

    // Determined the device supports TCG silo. Issue TPer Reset silo command payload to the TCG silo
    Status = This->SendData( This,
                         0,
                         0,
                         SECURITY_PROTOCOL_IEEE1667,   // Security Protocol ID
                         0x0500, // SP specific id
                         0x200,  // TranferLength
                         IeeeResetDataBuffer
                         );
    pBS->FreePool(IeeeResetDataBuffer);

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
