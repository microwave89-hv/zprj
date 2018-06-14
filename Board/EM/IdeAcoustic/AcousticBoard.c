//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/HddAcoustic/AcousticBoard.c 6     6/09/14 10:02a Anbuprakashp $
//
// $Revision: 6 $
//
// $Date: 6/09/14 10:02a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddAcoustic/AcousticBoard.c $
// 
// 6     6/09/14 10:02a Anbuprakashp
// [TAG]  		EIP172447
// [Category]  	Improvement
// [Description]  	Runtime attribute set for the some of the variable used
// by HddAcoustic driver(Aptio-IV) that needs to be reviewed
// [Files]  		AcousticBoard.c
// 
// 5     3/05/12 3:12a Rameshr
// [TAG]  		EIP82971
// [Category]  	Improvement
// [Description]  	Added dynamich PCIe base Support in IdeAcoustic
// [Files]  		AcousticBoard.c, AcousticSetup.c
// 
// 4     2/10/11 11:27a Pats
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
// 3     1/07/11 12:14p Pats
// Handles counting of devices on second controller differently depending
// on token SECOND_CONTROLLER_COUNTS_BY_DEVICE.
// 
// 2     1/06/11 4:38p Pats
// On some platforms, the 2nd controller is present, but not used, in AHCI
// mode. The 2nd controller should not be registered in this case.
// InstallAcousticPlatformProtocol() is modified to not register the 2nd
// controller in AHCI mode.
// 
// 1     1/05/11 12:22a Rameshr
// Initial check-in for Hdd Acoustic Management Support.
// 
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:    AcousticBoard.C
//
// Description: This file contains DXE stage board component code for Acoustic 
//              support
//
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "Acoustic.h"

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

EFI_GUID BdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
EFI_GUID SetupEnterProtocolGuid             = AMITSE_SETUP_ENTER_GUID;
EFI_GUID gSetupGuid                         = SETUP_GUID;
EFI_GUID gAcousticSetupProtocolguid         = ACOUSTIC_SETUP_PROTOCOL_GUID;

VOID *gAcousticNotifyReg = NULL;
VOID *gAcousticProgNotifyReg = NULL;
VOID *gAcousticSetupNotifyReg = NULL;
UINT8 gIdeControllerLocation[] = IDE_CONTROLLER_LOCATION;
UINT8 gIdeControllerLocation2[] = SECOND_CONTROLLER_LOCATION;

ACOUSTIC_SETUP_PROTOCOL *gAcousticSetupProtocol2 = NULL;
ACOUSTIC_SETUP_PROTOCOL *gAcousticSetupProtocol5 = NULL;

VOID InstallAcousticPlatformProtocol(IN EFI_EVENT Event, IN VOID *Context);
VOID SetupEntryCallback(IN EFI_EVENT Event, IN VOID *Context);
VOID AcousticProgramming(IN EFI_EVENT Event, IN VOID *Context);

#if DYNAMIC_PCIEXBASE_SUPPORT
UINT32 GetPciBaseAddr(VOID);
#define PCIEX_BASE GetPciBaseAddr()
#else
#define PCIEX_BASE PCIEX_BASE_ADDRESS
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Acoustic_BoardInit
//
// Description: This function installs the the ACOUSTIC_SETUP_PROTOCOL which
//              would be used in ahci/ide bus driver.
//
// Input:       ImageHandle - ImageHandle of the loaded driver
//              SystemTable - Pointer to the System Table
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
Acoustic_BoardInit (
IN EFI_HANDLE           ImageHandle,
IN EFI_SYSTEM_TABLE     *SystemTable 
)
{
    EFI_STATUS              Status;
    EFI_EVENT               Event;

    InitAmiLib(ImageHandle, SystemTable);

#if LOCAL_ACOUSTIC_SETUP
    Status = RegisterProtocolCallback( &gEfiPciIoProtocolGuid,
                                       InstallAcousticPlatformProtocol,
                                       NULL,
                                       &Event,
                                       &gAcousticNotifyReg );
    ASSERT_EFI_ERROR(Status);
#endif

    Status = RegisterProtocolCallback( &BdsAllDriversConnectedProtocolGuid, 
                                       AcousticProgramming, 
                                       NULL, 
                                       &Event, 
                                       &gAcousticProgNotifyReg );

    ASSERT_EFI_ERROR(Status);
    //
    //Install callback on entring into Setup
    //
    Status = RegisterProtocolCallback( &SetupEnterProtocolGuid, 
                                        SetupEntryCallback,
                                        NULL,
                                        &Event, 
                                        &gAcousticSetupNotifyReg);     
    ASSERT_EFI_ERROR(Status);   

    return  EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InstallAcousticPlatformProtocol
//
// Description: This function initializes some Setup values and Acoustic
//              Protocol values.
//
// Input:       IN EFI_EVENT    Event
//              IN VOID         *Context
//
// Output:      None
//
// Notes:       This needs to be ported for each controller.
//              gAcousticSetupProtocolguid needs to be installed for each IDE/SATA
//              controller on the system.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
InstallAcousticPlatformProtocol (
    IN EFI_EVENT        Event,
    IN VOID             *Context 
)
{
    EFI_STATUS  Status;
    UINTN                   BufferSize = sizeof (EFI_HANDLE);
    EFI_HANDLE              Handle;
    UINTN                   PciSeg;
    UINTN                   PciBus;
    UINTN                   PciDev;
    UINTN                   PciFun;
    EFI_PCI_IO_PROTOCOL     *PciIo;
    UINT8                   i;
    SETUP_DATA              *SetupData = NULL;
    UINTN                   VariableSize = NULL;
    ACOUSTIC_SETUP_PROTOCOL *gAcousticSetupProtocol;
    UINTN                   PciAddress;
    UINT8                   SataMode;
    //
    // Callback on PCIIo Protocol
    //
    Status = pBS->LocateHandle( ByRegisterNotify, 
                                NULL, 
                                gAcousticNotifyReg, 
                                &BufferSize, 
                                &Handle );
    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) {
        return;
    }
    //
    // Locate PciIo protocol installed on Handle
    //
    Status = pBS->HandleProtocol( Handle, &gEfiPciIoProtocolGuid, &PciIo );
    ASSERT_EFI_ERROR(Status);
    //
    // Get PCI Device Bus/Device/Function Numbers
    //
    Status = PciIo->GetLocation( PciIo, &PciSeg, &PciBus, &PciDev, &PciFun );
    ASSERT_EFI_ERROR(Status);

    if (EFI_ERROR(Status)) {
        return;
    }
    if ( ((PciBus == gIdeControllerLocation[0]) && \
          (PciDev == gIdeControllerLocation[1]) && \
          (PciFun == gIdeControllerLocation[2])) || \
         ((PciBus == gIdeControllerLocation2[0]) && \
          (PciDev == gIdeControllerLocation2[1]) && \
          (PciFun == gIdeControllerLocation2[2])) ) {

        PciAddress = MmPciAddress(PCIEX_BASE, 
                                  gIdeControllerLocation[0], 
                                  gIdeControllerLocation[1], 
                                  gIdeControllerLocation[2], 
                                  PCI_SCC);

        SataMode = *((volatile UINT8 *)(UINTN)(PciAddress));

        if ( (PciBus == gIdeControllerLocation2[0]) && \
             (PciDev == gIdeControllerLocation2[1]) && \
             (PciFun == gIdeControllerLocation2[2]) && \
             (SataMode != PCI_CL_MASS_STOR_SCL_IDE) ) {
            return; // If in AHCI mode, don't register 2nd controller.
        }

        Status = pBS->AllocatePool (EfiBootServicesData,
                            sizeof(ACOUSTIC_SETUP_PROTOCOL),
                            (VOID**)&gAcousticSetupProtocol);
        if (EFI_ERROR(Status)) {
            return;
        }

        Status = pBS->AllocatePool(EfiBootServicesData, 
                                    ACOUSTIC_DEVICE_COUNT, 
                                    &gAcousticSetupProtocol->AcousticSupportIndv);

        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) {
            return;
        }

        pBS->SetMem(gAcousticSetupProtocol->AcousticSupportIndv, ACOUSTIC_DEVICE_COUNT, 0);

        Status = pBS->AllocatePool(EfiBootServicesData, 
                                    ACOUSTIC_DEVICE_COUNT,
                                    &gAcousticSetupProtocol->AcousticLevelIndv);

        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) {
            return;
        }

        pBS->SetMem(gAcousticSetupProtocol->AcousticLevelIndv, ACOUSTIC_DEVICE_COUNT, 0);

        Status = pBS->AllocatePool(EfiBootServicesData, 
                                    ACOUSTIC_DEVICE_COUNT,
                                    &gAcousticSetupProtocol->DeviceDetected);

        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) {
            return;
        }

        pBS->SetMem(gAcousticSetupProtocol->DeviceDetected, ACOUSTIC_DEVICE_COUNT, 0);

        gAcousticSetupProtocol->ControllerNumber = 0;

        if ( (PciBus == gIdeControllerLocation2[0]) && \
             (PciDev == gIdeControllerLocation2[1]) && \
             (PciFun == gIdeControllerLocation2[2]) ) {
            gAcousticSetupProtocol->ControllerNumber = 1;
        }

        Status = GetEfiVariable( L"Setup",
                                 &gSetupGuid,
                                 NULL,
                                 &VariableSize,
                                 &SetupData);

        if (!EFI_ERROR(Status)) { 
            gAcousticSetupProtocol->DeviceCount = ACOUSTIC_DEVICE_COUNT;
            gAcousticSetupProtocol->AcousticPwrMgmt = SetupData->AcousticPwrMgmt;
            gAcousticSetupProtocol->AcousticLevel   = SetupData->AcousticLevel;

#if INDIVIDUAL_ACOUSTIC_SUPPORT
            if ( (PciBus == gIdeControllerLocation2[0]) && \
                 (PciDev == gIdeControllerLocation2[1]) && \
                 (PciFun == gIdeControllerLocation2[2]) ) {
                for (i = 0; i < NUMBER_OF_PORTS_ON_SECOND_CONTROLLER ; i++ ) { // Only 2 ports on 2nd controller
                    if (gAcousticSetupProtocol->AcousticPwrMgmt) {
                        gAcousticSetupProtocol->AcousticLevelIndv[i] = 
                                            SetupData->AcousticLevelIndv[i+NUMBER_OF_PORTS_ON_FIRST_CONTROLLER];
                    } else {
                        gAcousticSetupProtocol->AcousticLevelIndv[i] = ACOUSTIC_SUPPORT_DISABLE;
                    }
                }
            } else {
                for (i = 0; i<ACOUSTIC_DEVICE_COUNT; i++ ) {
                    if (gAcousticSetupProtocol->AcousticPwrMgmt) {
                        gAcousticSetupProtocol->AcousticLevelIndv[i] = SetupData->AcousticLevelIndv[i];
                    } else {
                        gAcousticSetupProtocol->AcousticLevelIndv[i] = ACOUSTIC_SUPPORT_DISABLE;
                    }
                }
            }
#else
            for (i = 0; i<ACOUSTIC_DEVICE_COUNT; i++ ){
                if (gAcousticSetupProtocol->AcousticPwrMgmt) {
                    gAcousticSetupProtocol->AcousticLevelIndv[i] = SETUP_DATA.AcousticLevel;
                } else {
                    gAcousticSetupProtocol->AcousticLevelIndv[i] = ACOUSTIC_SUPPORT_DISABLE;
                }
            }

#endif
        } else {
            //
            //Incase setup data is not available, initilaize with some defaults
            //
            gAcousticSetupProtocol->AcousticPwrMgmt = ACOUSTIC_SUPPORT_DISABLE;
            gAcousticSetupProtocol->AcousticLevel   = ACOUSTIC_LEVEL_BYPASS;
#if INDIVIDUAL_ACOUSTIC_SUPPORT
            for (i = 0; i<ACOUSTIC_DEVICE_COUNT; i++ ){
                gAcousticSetupProtocol->AcousticLevelIndv[i] = ACOUSTIC_LEVEL_BYPASS;
            }
#endif
    }
        //
        //Install AcousticSetup Protocol on the ""Controller""
        //
        Status = pBS->InstallProtocolInterface(
                      &Handle,
                      &gAcousticSetupProtocolguid,
                      EFI_NATIVE_INTERFACE,
                      gAcousticSetupProtocol
                      );

        if ( (PciBus == gIdeControllerLocation2[0]) && \
             (PciDev == gIdeControllerLocation2[1]) && \
             (PciFun == gIdeControllerLocation2[2]) ) {
            gAcousticSetupProtocol5 = gAcousticSetupProtocol;
        } else {
            gAcousticSetupProtocol2 = gAcousticSetupProtocol;
        }
    }

    if (SetupData) {
        pBS->FreePool (SetupData);
    }

    if (gAcousticSetupProtocol2 && gAcousticSetupProtocol5) {
        Status = pBS->CloseEvent (Event);    
    }
    
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetupEntryCallback
//
// Description: This function loads setup variables with Acoustic protocol values
//
// Input:       IN EFI_EVENT    Event
//              IN VOID         *Context
//
// Output:      None
//
// Notes:       This needs to be ported for each controller.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SetupEntryCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
)
{
    EFI_STATUS              Status;    
    SETUP_DATA              *SetupData = NULL;
    UINTN                   VariableSize = NULL;
    UINT8                   i;
    UINT32                  SetupDataAttributes = 0;

    //
    // Kill the Event once It's exected.
    //
    Status = pBS->CloseEvent (Event);
    //
    // If the protocol not used, return
    //
    if (gAcousticSetupProtocol2 == NULL) return;

    Status = GetEfiVariable( L"Setup",
                            &gSetupGuid,
                            &SetupDataAttributes,
                            &VariableSize,
                            &SetupData);

    for (i = 0; i < gAcousticSetupProtocol2->DeviceCount; i++) { 
        SetupData->AcousticSupported[i] = gAcousticSetupProtocol2->AcousticSupportIndv[i];
        SetupData->AcDevicePresent[i] = gAcousticSetupProtocol2->DeviceDetected[i];
    }

    if ( gAcousticSetupProtocol5 != NULL ) {
        for (i = 0; i < NUMBER_OF_PORTS_ON_SECOND_CONTROLLER ; i++) { // Only 2 ports on 2nd controller
            SetupData->AcousticSupported[i + NUMBER_OF_PORTS_ON_FIRST_CONTROLLER] = 
                                                        gAcousticSetupProtocol5->AcousticSupportIndv[i];
            SetupData->AcDevicePresent[i + NUMBER_OF_PORTS_ON_FIRST_CONTROLLER] = 
                                                        gAcousticSetupProtocol5->DeviceDetected[i];
        }
    }

    Status = pRS->SetVariable(L"Setup",
                              &gSetupGuid,
                              SetupDataAttributes,
                              sizeof(SETUP_DATA),
                              SetupData);

    if (SetupData) {
        pBS->FreePool (SetupData);
    }

    return;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
