//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/HddAcoustic/Acoustic.c 5     12/19/11 1:09a Rameshr $
//
// $Revision: 5 $
//
// $Date: 12/19/11 1:09a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddAcoustic/Acoustic.c $
// 
// 5     12/19/11 1:09a Rameshr
// [TAG]  		EIP77527
// [Category]  	Improvement
// [Description]  	IdeSecurity, IdeAcoustic and IdeSmart changes should be
// done based on the Core Version checking.
// [Files]  		IdeSecurity.c, IdeSmart.c , Acoustic.c 
// 
// 4     12/05/11 6:22p Rajkumarkc
// [TAG]  		EIP77142 
// [Category]  	Improvement
// [Description]	Added the function 'IdeNonDataCommandExp' in the
// 'IDE_BUS_PROTOCOL' and removed the existing function
// 'IdeNonDataCommand' for supporting the upper 24bits of LBA.
// [Files]
//     Ata.c, IdeBus.c, Idebus.h, PIDEBus.h, Acoustic.c, IdeSecurity.c,
// IdeSMART.c
// 
// 3     2/10/11 11:25a Pats
// [TAG] - EIP 52920
// [Category]- Function Request
// [Severity]- Minor
// [Symptom] - The Acoustic mode (Bypass/Quiet/Max Performance) of port 5
// is invalid on AMD SB700.
// [RootCause] - Special case where 2nd controller counts by incrementing
// device number only not handled properly
// [Solution] - Modified functions that handle this case.
// [Files] - Acoustic.c, AcousticBoard.c, AcousticSetup.c
// 
// 2     1/07/11 12:07p Pats
// Changed the name of a variable from SataPortIndex to IdeDevice, for
// consistancy. No coding change.
// 
// 1     1/05/11 12:22a Rameshr
// Initial check-in for Hdd Acoustic Management Support.
// 
//**********************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: Acoustic.c
//
// Description: Initialize and provide a protocol for the Acoustic support.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Efi.h>
#include <Dxe.h>

#include "Acoustic.h"   

extern EFI_GUID gAcousticSetupProtocolguid;

EFI_GUID gEfiDiskInfoProtocolGuid           = EFI_DISK_INFO_PROTOCOL_GUID;
EFI_GUID gEfiBlockIoProtocolGuid            = EFI_BLOCK_IO_PROTOCOL_GUID;
EFI_GUID gEfiAhciBusProtocolGuid            = AHCI_BUS_INIT_PROTOCOL_GUID;
EFI_GUID gEfiIdeBusInitProtocolGuid         = IDE_BUS_INIT_PROTOCOL_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AcousticEntryPoint
//
// Description: This routine is the entry point for the Acoustic driver. It
//              Initializes various controllers and installs Driver Binding
//              protocol 
//
// Input:       ImageHandle     Handle to this driver image
//              SystemTable     Pointer to the system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
AcousticEntryPoint (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);

#ifdef Debug_Level_1
    TRACE((-1,"AcousticEntryPoint Status = %x\n", Status));
#endif

    Acoustic_BoardInit (ImageHandle, SystemTable);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AcousticProgramming
//
// Description: This function is called after all the controllers have been 
//              dispatched and at the end of BDS phase.
//
//
// Input:       IN EFI_EVENT    Event
//              IN VOID         *Context
//
// Output:      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
AcousticProgramming (
    IN EFI_EVENT        Event,
    IN VOID             *Context 
)
{
    EFI_STATUS                      Status;
    EFI_DISK_INFO_PROTOCOL          *DiskInfo;
    EFI_PCI_IO_PROTOCOL             *PciIo;
    EFI_DEVICE_PATH_PROTOCOL        *Dp;
    ACOUSTIC_SETUP_PROTOCOL         *AcousticSetupProtocol;
    IDENTIFY_DATA                   *IdentifyDriveInfo = NULL;
    UINT32                          IdeDevice, IdeChannel, PortIndex;
    UINTN                           i, j, Number, Number1;
    EFI_HANDLE                      *Controller_Handle = NULL, *Device_Handle = NULL, Handle = NULL;
    SETUP_DATA                      *SetupData = NULL;
    UINT32                          BufferSize;
    UINT16                          CurrentLevel;
    UINT8                           SubClassCode;

    Status = pBS->CloseEvent (Event);

    Status = pBS->LocateHandleBuffer(ByProtocol,&gAcousticSetupProtocolguid, NULL, &Number, &Controller_Handle);
    if (EFI_ERROR(Status)) {
        return;
    }
    //
    // Get the Identify Data
    //
    Status = pBS->AllocatePool(EfiBootServicesData, sizeof (IDENTIFY_DATA), &IdentifyDriveInfo);
    ASSERT_EFI_ERROR (Status);

    for(i=0; i<Number; i++) {
        Status = pBS->HandleProtocol(Controller_Handle[i],&gAcousticSetupProtocolguid,&AcousticSetupProtocol);
        if (EFI_ERROR(Status)) {
            continue;
        }

        Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiDiskInfoProtocolGuid, NULL, &Number1, &Device_Handle);
        if (EFI_ERROR(Status)) {
            continue;
        }

        for(j = 0; j < Number1; j++) {
            // 
            // Now try to locate the Controller on which the device is connected
            //
            Status = pBS->HandleProtocol(Device_Handle[j],&gEfiDevicePathProtocolGuid,&Dp); 
            if (EFI_ERROR(Status)) {
                continue;
            }
                
            Status = pBS->LocateDevicePath(&gEfiPciIoProtocolGuid, &Dp, &Handle);
            //
            // If the controller handle doesn't match then it is a different IDE controller
            //
            if (Handle != Controller_Handle[i]) {
                continue;
            }

            Status = pBS->HandleProtocol(Device_Handle[j], &gEfiDiskInfoProtocolGuid, &DiskInfo);
            if (EFI_ERROR(Status)) {
                continue;
            }

            Status = pBS->HandleProtocol(Controller_Handle[i], &gEfiPciIoProtocolGuid, &PciIo);
            if (EFI_ERROR(Status)) {
                continue;
            }

            Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xA, 1, &SubClassCode);
            //
            // Get the location of the drive
            //
            Status = DiskInfo->WhichIde (DiskInfo, &IdeChannel, &IdeDevice);

            if (SubClassCode == 1) {           // Ide mode
                PortIndex = (IdeChannel * 2) + IdeDevice;
                if (PortIndex == 1 || PortIndex == 2) {
                    PortIndex ^= 3;
                }
            } else {
                PortIndex = IdeChannel;
            }
#if SECOND_CONTROLLER_COUNTS_BY_DEVICE
            if ( (SubClassCode == 1) && \
                 (AcousticSetupProtocol->ControllerNumber == 1) ) {
                PortIndex = IdeDevice;
            }
#endif
            AcousticSetupProtocol->DeviceDetected[PortIndex] = 1;

            BufferSize = sizeof (IDENTIFY_DATA);

            Status = DiskInfo->Identify (DiskInfo, IdentifyDriveInfo, &BufferSize);
            ASSERT_EFI_ERROR (Status);
            if (EFI_ERROR(Status)) {
                continue;
            }
            //
            // Does it support Acoustics?
            //
            if (!(IdentifyDriveInfo->Command_Set_Supported_83 & AUTOMATIC_ACOUSTIC_FEATURE_SET_SUPPORTED)) { 
                AcousticSetupProtocol->AcousticSupportIndv[PortIndex] = 0;
                continue;
            }
            //
            // Get the drive's current acoustic value
            //
            CurrentLevel = (IdentifyDriveInfo->Acoustic_Level_94);
            //
            // Acoustic is supported by the drive
            //
            AcousticSetupProtocol->AcousticSupportIndv[PortIndex] = 1;

            if (AcousticSetupProtocol->AcousticLevelIndv[PortIndex] != ACOUSTIC_SUPPORT_DISABLE) {
                if (AcousticSetupProtocol->AcousticLevelIndv[PortIndex] == ACOUSTIC_LEVEL_BYPASS) {
                    if ( (CurrentLevel & 0xFF) != (CurrentLevel >> 8) ) { // If not already set
                        Status = IssueSetFeatureCmd(Controller_Handle[i], 
                                                    Device_Handle[j],
                                                    ACOUSTIC_MANAGEMENT_ENABLE,
                                                    (UINT8)(IdentifyDriveInfo->Acoustic_Level_94 >> 8));
                    }
                } else {
                    if ( AcousticSetupProtocol->AcousticLevelIndv[PortIndex] != (UINT8)(CurrentLevel & 0xFF) ) {
                        Status = IssueSetFeatureCmd(Controller_Handle[i], 
                                                    Device_Handle[j],
                                                    ACOUSTIC_MANAGEMENT_ENABLE,
                                                    AcousticSetupProtocol->AcousticLevelIndv[PortIndex]);
                    }
                }
            } else {
                //
                // Acoustic disabled in Setup but not in drive then issue cmd
                //
                if (IdentifyDriveInfo->Command_Set_Enabled_86 & AUTOMATIC_ACOUSTIC_FEATURE_SET_SUPPORTED) {
                    Status = IssueSetFeatureCmd(Controller_Handle[i], 
                                                Device_Handle[j], 
                                                ACOUSTIC_MANAGEMENT_DISABLE, 
                                                0);
                }
            }
        }
    }

    pBS->FreePool (IdentifyDriveInfo);

    if (Controller_Handle) {
        pBS->FreePool (Controller_Handle);
    }

    if (Device_Handle) {
        pBS->FreePool (Device_Handle);
    }

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IssueSetFeatureCmd
//
// Description: This function issues the SetFeature cmd
//
// Input:       EFI_HANDLE  ControllerHandle,
//              EFI_HANDLE  DeviceHandle,
//              UINT8       SubCommand,
//              UINT8       Mode
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
IssueSetFeatureCmd (
    EFI_HANDLE  ControllerHandle,
    EFI_HANDLE  DeviceHandle,
    UINT8       SubCommand,
    UINT8       Mode
)
{
    EFI_STATUS              Status;
    EFI_BLOCK_IO_PROTOCOL   *BlockIO;
    AHCI_BUS_PROTOCOL       *AhciBusInterface;
    SATA_DEVICE_INTERFACE   *SataDevInterface;
    IDE_BUS_PROTOCOL        *IdeBusInterface;
    COMMAND_STRUCTURE       CommandStructure = {0};

    Status = pBS->HandleProtocol(DeviceHandle, &gEfiBlockIoProtocolGuid, &BlockIO);
    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) {
        return  Status;
    }
    //
    // Check if IDE/AHCI by check if IDEBus/AHCUBus Protocol is installed
    //
    Status = pBS->OpenProtocol( ControllerHandle,
                                &gEfiIdeBusInitProtocolGuid,
                                &IdeBusInterface,
                                TheImageHandle,
                                ControllerHandle,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL );
    if(!EFI_ERROR(Status)) {
        //
        // We are in IDE mode
        //
        IdeBusInterface = ((IDE_BLOCK_IO *)BlockIO)->IdeBusInterface;

        //
        // Idebus API changed from Core 4.6.5.2. Added Core Version check for the OLD 
        // Core support.
        //
#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028b) 

        Status = IdeBusInterface->IdeNonDataCommand(IdeBusInterface,
                                                       SubCommand, Mode, 0, 0, 0, 0, 0,
                                                       0, 0, IdeBusInterface->IdeDevice.Device << 4,
                                                       SET_FEATURE_COMMAND);
#else
        Status = IdeBusInterface->IdeNonDataCommand(IdeBusInterface,
                                                       SubCommand, Mode, 0,
                                                       0, 0, IdeBusInterface->IdeDevice.Device << 4,
                                                       SET_FEATURE_COMMAND);
#endif
        return  Status;
    }

    Status = pBS->OpenProtocol( ControllerHandle,
                                &gEfiAhciBusProtocolGuid,
                                &AhciBusInterface,
                                TheImageHandle,
                                ControllerHandle,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL );

    if(!EFI_ERROR(Status)) {
        SataDevInterface = ((SATA_BLOCK_IO *)BlockIO)->SataDevInterface;
        //
        // It is in AHCI mode
        //
        CommandStructure.Command = SET_FEATURE_COMMAND;
        CommandStructure.Features = SubCommand;
        CommandStructure.SectorCount = Mode;
        Status = AhciBusInterface->ExecuteNonDataCommand (SataDevInterface, CommandStructure);
    }

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************