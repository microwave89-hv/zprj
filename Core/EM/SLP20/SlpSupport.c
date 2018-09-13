//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2011, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/BIN/Modules/SLP/SlpSupport.c 12    8/03/11 2:45p Vyacheslava $
//
// $Revision: 12 $
//
// $Date: 8/03/11 2:45p $
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/SLP/SlpSupport.c $
// 
// 12    8/03/11 2:45p Vyacheslava
// 
// 11    8/01/11 3:25p Vyacheslava
// [TAG]  		EIP64110
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	This file has been updated to be compliant with PI 1.2,
// and UEFI 2.3.1 specifications. 
// 
// 10    7/12/11 4:44p Vyacheslava
// 
// 9     7/12/11 3:56p Vyacheslava
// 
// 8     7/01/11 12:19p Vyacheslava
// [TAG]  		EIP63678
// [Category]  	Improvement
// [Description]  	Added checking for dummy binaries. 
// 
// 7     7/01/11 12:00p Vyacheslava
// [TAG]  		EIP63678
// [Category]  	New Feature
// [Description]  	Preserve the OEM Activation SLIC during the BIOS
// recovery path.
// [Files]  		SlpSupport.sdl
// SlpSupport.mak
// SlpSupport.c
// SlpSupport.dxs
// SlpSupport.h
// SlpSupport.cif
// 
// 6     8/25/10 11:44a Vyacheslava
// Added comments.
// 
// 5     5/18/10 4:15p Vyacheslava
// Update for OEM ID and OEM Table ID from the Marker binary. (EIP#38438)
// 
// 4     8/19/09 10:47a Vyacheslava
// Added support for ACPI 3.0 (EIP#25335 )
// 
// 3     6/01/09 4:53p Vyacheslava
// EIP#22212: Synopsis: (1) SimpleBootFlag, (2) SLP, (3) CSPLibrary
// Description: Aptio Enhancement Guidelines for Engineers
//
// 2     10/09/07 3:55p Vyacheslava
// Fixed issue with token conversion. Added function CopyToken.
//
// 1     3/30/07 3:39p Felixp
//
//****************************************************************************
//<AMI_FHDR_START>
//
// Name:  SlpSupport.c
//
// Description:
//  Updated the XSDT with the SLIC OEM Activation ACPI Table.
// 
//<AMI_FHDR_END>
//****************************************************************************


//---------------------------------------------------------------------------

#include <AmiDxeLib.h>
#include <Protocol/AcpiTable.h>
#include <AmiHobs.h>
#include "SlpSupport.h"

//---------------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LocateAndLoadRawData
//
// Description: This fills the PubKey and Marker structures of SLIC table.
//
// Input:       
//  *FfsGuid    - Pointer to GUID of the FFS file to read
//  *Address    - Address of the buffer to read data into
//  Size        - Size of the buffer
//
// Output:
//  EFI_STATUS    - Sucessful
//  EFI_NOT_FOUND - Couldn't find the binaries
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS LocateAndLoadRawData(
    IN EFI_GUID *FfsGuid,
    IN VOID *Address,
    IN UINTN Size )
{
    EFI_STATUS                   Status;
    EFI_HANDLE                   *HandleBuffer = NULL;
    UINTN                        NumberOfHandles;
    UINTN                        Index;
    UINT32                       Authentication;

#if PI_SPECIFICATION_VERSION >= 0x0001000A
    EFI_GUID EfiFirmwareVolumeProtocolGuid = EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID;
    EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVolumeProtocol = NULL;
#else
    EFI_GUID EfiFirmwareVolumeProtocolGuid = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;
    EFI_FIRMWARE_VOLUME_PROTOCOL *FwVolumeProtocol = NULL;
#endif

    // Locate the Firmware volume protocol
    Status = pBS->LocateHandleBuffer(
        ByProtocol,
        &EfiFirmwareVolumeProtocolGuid, 
        NULL,
        &NumberOfHandles,
        &HandleBuffer
    );
    if (EFI_ERROR(Status)) 
        return Status;
    
    // Find and read raw data
    for (Index = 0; Index < NumberOfHandles; Index++) {

        Status = pBS->HandleProtocol(
            HandleBuffer[Index],
            &EfiFirmwareVolumeProtocolGuid,
            &FwVolumeProtocol
        );
        if (EFI_ERROR(Status)) 
            continue;
        
        Status = FwVolumeProtocol->ReadSection(
            FwVolumeProtocol,
            FfsGuid,
            EFI_SECTION_RAW,
            0x0,
            &Address,
            &Size,
            &Authentication
        );
        if (Status == EFI_SUCCESS) 
            break;
    }
    
    pBS->FreePool(HandleBuffer);
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PreserveSlicBinaries
//
// Description: This function preserves the the Marker and PubKey binaries.
//
// Input:       VOID
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PreserveSlicBinaries(VOID)
{
    EFI_STATUS Status = EFI_NOT_FOUND;
    RECOVERY_IMAGE_HOB *RecoveryHob; 
    EFI_GUID HobListGuid = HOB_LIST_GUID;
    EFI_GUID RecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;
    EFI_GUID PubKeyGuid = OEM_SLP_PUBLIC_KEY_GUID;
    EFI_GUID MarkerGuid = OEM_SLP_MARKER_GUID;
	EFI_CONFIGURATION_TABLE	*Table = pST->ConfigurationTable;
    EFI_PHYSICAL_ADDRESS Addr;
	UINTN  i;
    UINT8  *FwPubKeyPtr = NULL;
    UINT8  *FwMarkerPtr = NULL;
    UINT8  *RecPubKeyPtr = NULL;
    UINT8  *RecMarkerPtr = NULL;

    // Find the Product Key place in the recovery HOB
	for( i = 0; i < pST->NumberOfTableEntries; i++, Table++ ) {

        if ( !MemCmp(&Table->VendorGuid, &HobListGuid, sizeof(EFI_GUID)) ) {

            RecoveryHob = Table->VendorTable;
            Status = FindNextHobByGuid(&RecoveryHobGuid, &RecoveryHob);
            if (!EFI_ERROR(Status)) {

                // Find Public Key and Marker binaries in the Recovery image
                Status = EFI_NOT_FOUND;
                for ( Addr = RecoveryHob->Address; Addr < RecoveryHob->Address + FLASH_SIZE; Addr++ ) {

                    // Find the Public Key binary GUID
                    if ( !MemCmp((UINT8*)Addr, &PubKeyGuid, sizeof(EFI_GUID)) )
                        RecPubKeyPtr = (UINT8*)Addr;

                    // Find the Marker binary GUID
                    else if ( !MemCmp((UINT8*)Addr, &MarkerGuid, sizeof(EFI_GUID)) )
                        RecMarkerPtr = (UINT8*)Addr;

                    // if all binaries are found then find original places in the Firmware
                    if ( RecPubKeyPtr != NULL && RecMarkerPtr != NULL ) {

                        // Find Public Key and Marker binaries in the BIOS firmware
                        for ( Addr = FLASH_DEVICE_BASE_ADDRESS; Addr < FLASH_UPPER_ADDRESS; Addr++ ) {
        
                            // Find the Public Key binary GUID
                            if ( !MemCmp((UINT8*)Addr, &PubKeyGuid, sizeof(EFI_GUID)) )
                                FwPubKeyPtr = (UINT8*)Addr;

                            // Find the Marker binary GUID
                            else if ( !MemCmp((UINT8*)Addr, &MarkerGuid, sizeof(EFI_GUID)) )
                                FwMarkerPtr = (UINT8*)Addr;
        
                            // Preserve the SLIC binaries
                            if ( FwPubKeyPtr != NULL && FwMarkerPtr != NULL ) {

                                MemCpy( 
                                    RecPubKeyPtr, 
                                    FwPubKeyPtr, 
                                    sizeof(OEM_PUBLIC_KEY_STRUCTURE) + sizeof(EFI_FFS_FILE_HEADER) + sizeof(UINT16)
                                );

                                MemCpy( 
                                    RecMarkerPtr, 
                                    FwMarkerPtr, 
                                    sizeof(WINDOWS_MARKER_STRUCTURE) + sizeof(EFI_FFS_FILE_HEADER) + sizeof(UINT16)
                                );

                                Status = EFI_SUCCESS;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    TRACE((TRACE_ALWAYS,"PreserveSlicBinaries: Status = %r\n",Status));
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PublishSlicTable
//
// Description: This function publish SLIC table in the ACPI.
//
// Input:       VOID
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PublishSlicTable(VOID)
{
    EFI_STATUS Status;
    EFI_GUID PubKeyGuid = OEM_SLP_PUBLIC_KEY_GUID;
    EFI_GUID MarkerGuid = OEM_SLP_MARKER_GUID;
    EFI_ACPI_SLP SlpTable = {
        {SLIC_SIG, sizeof(EFI_ACPI_SLP), 0x01, 0x00, {0}, {0}, ACPI_OEM_REV, CREATOR_ID_AMI, CREATOR_REV_MS},
        {0},
        {0}
    };
    EFI_ACPI_TABLE_PROTOCOL *AcpiTableProtocol = NULL;
    UINTN  TableKey = 0;
    
    // Locate SLP Public Key binary
    Status = LocateAndLoadRawData(
        &PubKeyGuid, 
        &SlpTable.PubKey, 
        sizeof(SlpTable.PubKey)
    );
    if (EFI_ERROR(Status)) {
        TRACE((TRACE_ALWAYS, "Slp Public Key Binaries Not Found!\n"));
        return Status;
    }
    
    // Locate SLP Marker binary
    Status = LocateAndLoadRawData(
        &MarkerGuid, 
        &SlpTable.WinMarker, 
        sizeof(SlpTable.WinMarker)
    );
    if (EFI_ERROR(Status)) {
        TRACE((TRACE_ALWAYS, "Slp Marker Binaries Not Found!\n"));
        return Status;
    }

    // The dummy SLIC will be not published
    if ( SlpTable.WinMarker.StructType == 0xFFFFFFFF && SlpTable.PubKey.StructType == 0xFFFFFFFF ) {
        TRACE((TRACE_ALWAYS, "SlpSupport: Found dummy binaries. The SLIC will be not published!\n"));
        return EFI_ABORTED;
    }

    // Copy OEM ID and OEM Table ID from Marker's binary to SLIC header
    MemCpy( 
        (UINT8*)&SlpTable.Header.OemId,
        (UINT8*)&SlpTable.WinMarker.sOEMID,
        sizeof(SlpTable.WinMarker.sOEMID)
    );
    MemCpy( 
        (UINT8*)&SlpTable.Header.OemTblId,
        (UINT8*)&SlpTable.WinMarker.sOEMTABLEID,
        sizeof(SlpTable.WinMarker.sOEMTABLEID)
    );

    // Locate the ACPI table protocol
    Status = pBS->LocateProtocol(
        &gEfiAcpiTableProtocolGuid, 
        NULL, 
        &AcpiTableProtocol
    );
    if (EFI_ERROR(Status)) {
        TRACE((TRACE_ALWAYS, "Unable to locate AcpiTableProtocol!\n"));
        return Status;
    }
    
    // Publish SLIC to ACPI table
    Status = AcpiTableProtocol->InstallAcpiTable(
        AcpiTableProtocol,
        &SlpTable,
        sizeof(EFI_ACPI_SLP), 
        &TableKey
    );
    if (!EFI_ERROR(Status))
        TRACE((TRACE_ALWAYS, "SLIC table has been published.\n"));

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SlpSupport_EntryPoint
//
// Description: This function is the entry point of the eModule.
//
// Input:       
//  ImageHandle  - Image handle
//  *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI SlpSupport_EntryPoint(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable )
{
    EFI_STATUS Status = EFI_SUCCESS;

    InitAmiLib(ImageHandle, SystemTable);

    // Check if it's a Recovery Mode then preserve the Marker and PubKey binaries
    if (GetBootMode() == BOOT_IN_RECOVERY_MODE)
        Status = PreserveSlicBinaries();
    if (!EFI_ERROR(Status))
        Status = PublishSlicTable();

    return Status;
}


//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2011, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
