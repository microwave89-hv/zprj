//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/AHCI/INT13/AhciInt13Dxe.c 1     11/25/14 12:09a Kapilporwal $Revision:
//
// $Date: 11/25/14 12:09a $Log: /Alaska/SOURCE/Modules/AHCI/INT13/AhciInt13Dxe.c $
// 
// 
//
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
//
// Name:    AhciInt13Dxe.c
//
// Description: 
//    This file will register one CALLBACK function, AmiLegacyBootNotify(),
//    it will collect AHCI Int13 runtime data from gAhciI13Data and
//    send it to SMM for AHCI INT13 SMI handler.
//****************************************************************************
//<AMI_FHDR_END>

//---------------------------------------------------------------------------
#include <Token.h>
#include <AmiDxeLib.h>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION>=0x4028B)
#include <Protocol/SmmCommunication.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/LegacyBiosExt.h>
#include <Protocol/PciIo.h>
#include <Protocol/BlockIo.h>
#include <Protocol/PDiskInfo.h>
#include <Protocol/PIDEController.h>
#include <Protocol/PIDEBus.h>
#include <Protocol/PAhciBus.h>
#include "AInt13.h"
#include "AhciInt13Smm.h"

AHCI_I13_RTDATA             *gAhciI13Data = NULL;
extern EFI_GUID             gAint13SmmDataGuid;
EFI_GUID                    gEfiLegacyBiosProtocolGuid = EFI_LEGACY_BIOS_PROTOCOL_GUID;
EFI_GUID                    gEfiDiskInfoProtocolGuid = EFI_DISK_INFO_PROTOCOL_GUID;
EFI_GUID                    gEfiEventLegacyBootGuid = EFI_EVENT_LEGACY_BOOT_GUID;

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          IsSataDeviceInAhciMode
//
// Description: Check input BBS device is a SATA DEVICE in AHCI mode.
//
// Input:         BBS_TABLE* - Pointer to an entry in BBS table
//
// Output:        UINT8   TRUE  - It is a SATA device and in AHCI mode
//                        FALSE - It is not a SATA device or not in AHCI mode
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
IsSataDeviceInAhciMode (
    IN  BBS_TABLE   *BbsEntry
)
{

    if((BbsEntry->DeviceType == BBS_HARDDISK || BbsEntry->DeviceType == BBS_CDROM)) {
        if(BbsEntry->Class == MASS_STORAGE || BbsEntry->SubClass == AHCI_CONTROLLER ){
            return TRUE;
        }
    }

    return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          InitializeAhciI13Data
//
// Description: It initializes AHCI INT13 runtime data pointer (gAhciI13Data).
//
// Input:         BBS_TABLE* - Pointer to an entry in BBS table
//
// Output:        VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
InitializeAhciI13Data (
    IN  BBS_TABLE   *BbsEntry
)
{
    UINT16      StrSeg = 0, StrOff = 0;
    UINT32      DevOutfitAddr = 0, DevOutfitStartAddr = 0;
    UINT8       AInt13No = 0, DevNo = 0;

    if(!gAhciI13Data) {
        // INT13 Drive number (0x80~0x8F)
        AInt13No = (UINT8)(BbsEntry->InitPerReserved >> 8);
        DevNo = AInt13No & 0x7F; // Drive index

        // Get address of drive description string i.e. AHCI_I13_RTDATA.DevOutfit[DevNo]
        StrSeg = BbsEntry->DescStringSegment;
        StrOff = BbsEntry->DescStringOffset;
        DevOutfitAddr = (UINT32)((UINTN)StrSeg << 4) + (UINT32)StrOff;

        // Now get address of description string of 1st drive i.e. AHCI_I13_RTDATA.DevOutfit[0]
        DevOutfitStartAddr = DevOutfitAddr - (sizeof(DEV_BBS_OUTFIT)*DevNo);
        // Now get base address of AHCI_I13_RTDATA structure
        gAhciI13Data = (AHCI_I13_RTDATA*)(DevOutfitStartAddr - EFI_FIELD_OFFSET(AHCI_I13_RTDATA, DevOutfit));
    }

    return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          TransferAhciInt13SmmDataToSmm
//
// Description: It uses EFI_SMM_COMMUNICATION_PROTOCOL API to transfer data 
//              from Non-SMM mode to SMM mode.
//
// Input:         VOID* - Pointer to data to be transfered
//                UINTN - size of the data
//                EFI_GUID* - Pointer to GUID identifier for the data
//
// Output:        EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
TransferAhciInt13SmmDataToSmm (
    IN  VOID    *pData,
    IN  UINTN   DataSize,
    IN  EFI_GUID *pGuid
)
{
    EFI_SMM_COMMUNICATION_PROTOCOL *gSmmCommunication = NULL;
    EFI_SMM_COMMUNICATE_HEADER     *SmmCommunicateHeader;
    UINT8                          *CommunicateBuffer = NULL;
    UINTN                          CommunicateBufferSize;
    EFI_STATUS                     Status;

    if ( pData == NULL || DataSize == 0 || pGuid == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    // Calculate Size of Communication buffer
    CommunicateBufferSize  = (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)) + DataSize; // Header size (without data) + data size

    // Allocate memory for Communication Buffer.
    Status = pBS->AllocatePool( EfiBootServicesData,
                                CommunicateBufferSize,
                                (VOID**)&CommunicateBuffer );
    if ( EFI_ERROR( Status )) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    // Copy SMM Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)CommunicateBuffer;

    // Copy data GUID
    pBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, pGuid, sizeof( EFI_GUID ) );

    // Updated data length
    SmmCommunicateHeader->MessageLength  = DataSize;

    // Copy Data Here
    pBS->CopyMem( &SmmCommunicateHeader->Data, pData, DataSize );

    // Locate EFI_SMM_COMMUNICATION_PROTOCOL
    Status = pBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &gSmmCommunication);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    // Send data to SMM using protocol API
    Status = gSmmCommunication->Communicate (gSmmCommunication, CommunicateBuffer, &CommunicateBufferSize);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    // Free memory allocated for Communication Buffer.
    Status = pBS->FreePool(CommunicateBuffer);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          AmiLegacyBootNotify
//
// Description:     This function will be called upon legacy boot event. It 
//    collects information about all AHCI devices present in the system and 
//    send it to SMM so that AHCI INT13 SMI handler can use it.
//    Operation:
//    1. Locate EFI_LEGACY_BIOS_PROTOCOL and get All BBS entries and look
//       for entry corresponding to a drive in AHCI mode
//    2. If a valid entry is found then it will use AHCI INT13 runtime
//       data and AHCI bus interface data to fill data required by AHCI
//       INT13 SMI handler.
//    3. This newly created data structure will be transfered to SMM using
//       SmmCommunicationProtocol API.
//
// Input:         EFI_EVENT - Event
//                VOID* - Pointer to Context
//
// Output:        VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
AmiLegacyBootNotify(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_STATUS  Status;
    UINT16      HddCount = 0;
    HDD_INFO    *HddInfo = NULL;
    BBS_TABLE   *BbsTable = NULL;
    UINT16      BbsCount = 0;
    UINT8       DevNo = 0;
    UINTN       SegNum;
    UINTN       BusNum;
    UINTN       DevNum;
    UINTN       FuncNum;
    UINT16      i = 0;
    EFI_LEGACY_BIOS_PROTOCOL *LegacyBios;
    EFI_DISK_INFO_PROTOCOL   *DiskInfo = NULL;
    SATA_DEVICE_INTERFACE    *SataDevInterface = NULL;
    SMM_AINT13_DRIVE_INFO    *pDriveInfo = NULL;
    AHCI_INT13_SMM_DATA          *AhciInt13SmmData   = NULL;

    // Run this function only once
    pBS->CloseEvent(Event);

    // Locate EFI_LEGACY_BIOS_PROTOCOL
    Status = pBS->LocateProtocol(  &gEfiLegacyBiosProtocolGuid,
                                   NULL,
                                   &LegacyBios);
    if (EFI_ERROR(Status)) {
        return;
    }

    // Get BBS_TABLE
    Status = LegacyBios->GetBbsInfo( LegacyBios,
                                     &HddCount,
                                     &HddInfo,
                                     &BbsCount,
                                     &BbsTable);
    if (EFI_ERROR(Status)) {
        return;
    }

    // Allocate Memory for AhciInt13SmmData buffer.
    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(AHCI_INT13_SMM_DATA),
                                (VOID**)&AhciInt13SmmData );
    if ( EFI_ERROR( Status )) {
        ASSERT_EFI_ERROR(Status);
        return;
    }

    // Initialize drive count to 0
    AhciInt13SmmData->DriveCount = 0;

    // Loop through all BBS entries
    for (i = 0; i < BbsCount; i++) {

        // Process if this BDS entry is corresponding to a HDD in AHCI mode
        if (IsSataDeviceInAhciMode(&BbsTable[i])) {

            // NOTE: We don't need EFI_DISK_INFO_PROTOCOL this is just to get SATA_DEVICE_INTERFACE structure.
            Status = pBS->HandleProtocol ( (EFI_HANDLE)BbsTable[i].IBV1, &gEfiDiskInfoProtocolGuid, &DiskInfo );
            if(EFI_ERROR(Status)) {
                continue; // Goto next BBS entry
            }
            SataDevInterface = ((SATA_DISK_INFO *)DiskInfo)->SataDevInterface;

            // Fill data in AhciInt13SmmData
            pDriveInfo = &(AhciInt13SmmData->DriveInfo[AhciInt13SmmData->DriveCount]);
            pDriveInfo->DriveNum = (UINT8)(BbsTable[i].InitPerReserved >> 8);
            pDriveInfo->PMPortNum = SataDevInterface->PMPortNumber;
            pDriveInfo->PortNum = SataDevInterface->PortNumber;
            SataDevInterface->AhciBusInterface->PciIO->GetLocation(
                                            SataDevInterface->AhciBusInterface->PciIO,
                                            &SegNum, &BusNum, &DevNum, &FuncNum
                                            );
            pDriveInfo->BusNo = (UINT8)BusNum;
            pDriveInfo->DevNo = (UINT8)DevNum;
            pDriveInfo->FuncNo = (UINT8)FuncNum;
            pDriveInfo->DeviceType = SataDevInterface->DeviceType;
            if(pDriveInfo->DeviceType == ATAPI) {
                pDriveInfo->Lun = SataDevInterface->AtapiDevice->Lun;
                pDriveInfo->BlockSize = SataDevInterface->AtapiDevice->BlockSize;
            } else {
                // Initialize AHCI INT13 runtime data
                if(!gAhciI13Data) {
                    InitializeAhciI13Data(&BbsTable[i]);
                }
                // Get drive index in device parameter array of gAhciI13Data
                DevNo = pDriveInfo->DriveNum & 0x7F;

                // Fill the information using gAhciI13Data
                pDriveInfo->wMAXCYL = gAhciI13Data->DevParam[DevNo].wMAXCYL;
                pDriveInfo->bMAXHN = gAhciI13Data->DevParam[DevNo].bMAXHN;
                pDriveInfo->bMAXSN = gAhciI13Data->DevParam[DevNo].bMAXSN;
                pDriveInfo->wLBACYL = gAhciI13Data->DevParam[DevNo].wLBACYL;
                pDriveInfo->bLBAHD = gAhciI13Data->DevParam[DevNo].bLBAHD;
                pDriveInfo->bLBASPT = gAhciI13Data->DevParam[DevNo].bLBASPT;
            }
            pDriveInfo->RCommand = SataDevInterface->ReadCommand;
            pDriveInfo->WCommand = SataDevInterface->WriteCommand;

            AhciInt13SmmData->DriveCount += 1; // Update drive count
        }
    }

    // Save AhciInt13SmmData in SMM
    if(AhciInt13SmmData->DriveCount != 0) {
        Status = TransferAhciInt13SmmDataToSmm ( AhciInt13SmmData, sizeof(AHCI_INT13_SMM_DATA), &gAint13SmmDataGuid );
    }

    // Free the Memory Allocated for AhciInt13SmmData Buffer.
    Status = pBS->FreePool(AhciInt13SmmData);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          AhciInt13DxeEntry
//
// Description: This is entry point function. It registers a call back function
//              for Legacy boot event.
//
// Input:         EFI_HANDLE - Standard EFI Image handle
//                EFI_SYSTEM_TABLE* - Pointer to System Table
//
// Output:        EFI_STATUS
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AhciInt13DxeEntry(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_EVENT   Event;

    InitAmiLib(ImageHandle, SystemTable);

    Status = pBS->CreateEventEx (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  AmiLegacyBootNotify,
                  NULL,
                  &gEfiEventLegacyBootGuid,
                  &Event
                  );

    return Status;
}
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
