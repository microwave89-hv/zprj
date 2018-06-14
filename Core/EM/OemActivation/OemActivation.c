//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//*****************************************************************************
// $Header: /Alaska/SOURCE/Modules/OemActivation/OemActivation.c 19    5/22/12 4:27p Vyacheslava $
//
// $Revision: 19 $
//
// $Date: 5/22/12 4:27p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/OemActivation/OemActivation.c $
// 
// 19    5/22/12 4:27p Vyacheslava
// [TAG]  		EIP90324
// [Description]  	The OA3MSDMvariable variable has improper GUID. 
// 
// 18    2/23/12 12:19p Vyacheslava
// Fixed build error for 32 bit mode. 
// 
// 17    1/12/12 9:20a Vyacheslava
// [TAG]  		EIP80094
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	There are duplicated MSDM published in the ACPI in PI 1.2
// 
// 16    10/28/11 5:37p Vyacheslava
// [TAG]  		EIP64110
// [Category]  	Improvement
// 
// 15    9/26/11 11:19a Vyacheslava
// [TAG]  		EIP64110
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	changed protocol SmmCpuState to SmmCpuProtocol
// 
// 14    9/23/11 3:16p Vyacheslava
// [TAG]  		EIP64110
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	Changed according to Aptio 4.6.5.x Components Porting
// Guide (Conversion of the SMM Drivers). 
// 
// 13    8/08/11 10:15a Vyacheslava
// 
// 12    8/03/11 2:24p Vyacheslava
// [TAG]  		EIP64110 
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	Updated to be compliant with PI 1.2, and UEFI 2.3.1
// specifications. 
// 
// 11    7/07/11 11:12a Vyacheslava
// [TAG]  		EIP62009
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	if OEM_ACTIVATION_TABLE_LOCATION is not zero, the code does
// not compile.
// 
// 10    6/16/11 10:55a Vyacheslava
// [TAG]  		EIP62009
// [Category]  	New Feature
// [Description]  	Preserve the OA30 key during the BIOS recovery path. 
// 
// 9     6/10/11 11:00a Vyacheslava
// 
// 8     5/24/11 3:53p Vyacheslava
// [TAG]  		EIP59717 
// [Category]  	New Feature
// [Description]  	Changed SW SMI protocol according to request from the
// Utility. 
// 
// 7     5/20/11 12:34p Vyacheslava
// [TAG]  		EIP59717
// [Category]  	New Feature
// [Description]  	Added code that updates ACPI table in OS Runtime. 
// 
// 6     5/18/11 11:21a Vyacheslava
// [TAG]  		EIP59717
// [Category]  	New Feature
// [Description]  	Implementation according comment#8 in the EIP#59717.
// 
// 5     4/29/11 12:44p Vyacheslava
// [TAG]  		EIP58139
// [Category]  	New Feature
// [Description]  	Added code to place Oem Activation Key in NCB.
// 
// 4     12/17/10 1:46p Vyacheslava
// [TAG]  		EIP48520 
// [Category]  	Improvement
// [Description]  	- Deleted temporary structure for testing FID; 
// - Simplified MSDM structure; 
// 
// 3     12/16/10 5:02p Vyacheslava
// - Added checking for FID version;
// - Fixed bug with structure overflow;
// 
// 2     11/19/10 4:18p Vyacheslava
// [TAG]  		EIP48520
// [Category]  	Improvement
// [Description]  	- $FID structure should not be redefined but updated
// where it belong: FwVersion.h in CSPLIB component
// - the 49 bytes of $FID should be intialized with 0xff 
// - the loading of the MSDM from $FID should be done based on the length
// of the MSDM field as specified in the $FID structure and not hardcoded
// to 49 bytes
// - checksum field should be initilized to 0x0 not 0x88 (which is the
// checksum value of the example of the Microsoft spec)
// 
// 1     11/18/10 1:15p Vyacheslava
// Initial creation
// 
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name: OemActivation.c
//
// Description: Microsoft OEM Activation 3.0
//
//<AMI_FHDR_END>
//*****************************************************************************


#include <AmiDxeLib.h>
#include <Protocol/AcpiTable.h>
#include <PPI/FwVersion.h>
#include <AmiHobs.h>
#include "OemActivation.h"



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LocateSectionResource
//
// Description: This function locate resource binary by GUID. 
//
// Input:
//  pResourceGuid        - pointer to recourse GUID
//  pResourceSectionGuid - pointer to recourse section GUID
//  Address              - pointer to returning address of the resource
//
// Output:  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS LocateSectionResource(
    IN  EFI_GUID *pResourceGuid,
    IN  EFI_GUID *pResourceSectionGuid,
    OUT UINT8 **Address )
{
    EFI_STATUS Status;
    EFI_HANDLE *HandleBuffer = NULL;
    UINTN  NumberOfHandles;
    UINTN  Index;
    UINT32 Authentication;
    UINTN  i;
    EFI_GUID *pGuid = NULL;
    UINTN  SectionSize;

#if PI_SPECIFICATION_VERSION<0x0001000A
    EFI_GUID EfiFirmwareVolumeProtocolGuid = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;
    EFI_FIRMWARE_VOLUME_PROTOCOL *FwVolumeProtocol = NULL;
#else
    EFI_GUID EfiFirmwareVolumeProtocolGuid = EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID;
    EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVolumeProtocol = NULL;
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
        return EFI_NOT_FOUND;
    
    // Find and read raw data
    for (Index = 0; Index < NumberOfHandles; Index++) {

        Status = pBS->HandleProtocol(
            HandleBuffer[Index],
            &EfiFirmwareVolumeProtocolGuid,
            &FwVolumeProtocol
        );
        if (EFI_ERROR(Status)) 
            continue;
        
        i = 0;
        while(1) {
            SectionSize = 0;
            Status = FwVolumeProtocol->ReadSection(
                FwVolumeProtocol,
                pResourceGuid,
                EFI_SECTION_FREEFORM_SUBTYPE_GUID,
                i++,
                &pGuid,
                &SectionSize,
                &Authentication
            );
            if (EFI_ERROR(Status))
                break;
            else if ( !guidcmp(pGuid, pResourceSectionGuid ) ) {
                *Address = (UINT8*)pGuid;
                goto LocateSectionResource_exit;
            }
            pBS->FreePool(pGuid);
            pGuid = NULL;
        } 
    }
    
LocateSectionResource_exit:
    pBS->FreePool(HandleBuffer);
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetProductKey
//
// Description: This function locates the Product Key. 
//
// Input:   Address - pointer to returning address of the Product Key structure.
//
// Output:  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetProductKey( 
    IN EFI_PHYSICAL_ADDRESS StartAddr, 
    IN EFI_PHYSICAL_ADDRESS EndAddr, 
    OUT UINT8 **Address )
{
    EFI_STATUS Status = EFI_NOT_FOUND;
    EFI_GUID FidTableSectionGuid = FID_TABLE_SECTION_GUID;
    EFI_PHYSICAL_ADDRESS i;

    for ( i = StartAddr; i < EndAddr; i++ )
        if ( !MemCmp((UINT8*)i, &FidTableSectionGuid, sizeof(EFI_GUID)) ) {

            // skip the GUID
            i += sizeof(EFI_GUID);

            // Check version of the FID table
            if ( ((FW_VERSION*)i)->StructVersion < FID_SUPPORTED_VERSION ) {
                TRACE((TRACE_ALWAYS, "OEM Activation: FID table version %d unsupported!!!\n",((FW_VERSION*)i)->StructVersion));
                Status = EFI_UNSUPPORTED;
                break;
            }

            // skip the ACPI header
            *Address = (UINT8*)((FW_VERSION*)i)->OemActivationKey;
            TRACE((TRACE_ALWAYS, "OEM Activation: Product Key Address %X\n",*Address));

            Status = EFI_SUCCESS;
            break;
        }
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PreserveProductKey
//
// Description: This function preserves the Product Key.
//
// Input:       VOID
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PreserveProductKey(VOID)
{
    EFI_STATUS Status = EFI_NOT_FOUND;
    RECOVERY_IMAGE_HOB *RecoveryHob; 
    EFI_GUID HobListGuid = HOB_LIST_GUID;
    EFI_GUID RecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;
    EFI_CONFIGURATION_TABLE *Table = pST->ConfigurationTable;
    UINTN  i;
    UINT8  *ProductKey;
    UINT8  *ProductKeyPreserve;

    // Find the Product Key place in the recovery HOB
    for( i = 0; i < pST->NumberOfTableEntries; i++, Table++ ) {

        if ( !MemCmp(&Table->VendorGuid, &HobListGuid, sizeof(EFI_GUID)) ) {

            RecoveryHob = Table->VendorTable;
            Status = FindNextHobByGuid(&RecoveryHobGuid, &RecoveryHob);
            if (!EFI_ERROR(Status)) {

#if OEM_ACTIVATION_TABLE_LOCATION == 0
                // Get the Product Key pointer in the recovery HOB
                Status = GetProductKey(
                    RecoveryHob->Address + FLASH_SIZE - FV_BB_SIZE, 
                    RecoveryHob->Address + FLASH_SIZE - sizeof(EFI_GUID), 
                    &ProductKeyPreserve
                );
                if (!EFI_ERROR(Status)) {
                    // Get the Product Key pointer in the Flash memory
                    Status = GetProductKey(FV_BB_BASE, FV_BB_END_ADDR, &ProductKey);
                    if (EFI_ERROR(Status))
                        break;
                    MemCpy( ProductKeyPreserve, ProductKey, sizeof(EFI_ACPI_MSDM_TABLE) - sizeof(ACPI_HDR) );
                }
#else
                ProductKeyPreserve = (UINT8*)(RecoveryHob->Address + FLASH_SIZE - OEM_ACTIVATION_TABLE_OFFSET);
                ProductKey = (UINT8*)OEM_ACTIVATION_TABLE_ADDRESS;
                MemCpy( ProductKeyPreserve, ProductKey, sizeof(EFI_ACPI_MSDM_TABLE) - sizeof(ACPI_HDR) );
                Status = EFI_SUCCESS;
#endif
            }
        }
    }
    TRACE((TRACE_ALWAYS,"PreserveProductKey: Status %r\n",Status));
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   OemActivation_EntryPoint
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

EFI_STATUS EFIAPI OemActivation_EntryPoint(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable )
{
    EFI_STATUS Status;
    EFI_GUID FidTableGuid = FID_TABLE_GUID;
    EFI_GUID FidTableSectionGuid = FID_TABLE_SECTION_GUID;
    FW_VERSION *Fid;
    UINT8  *FidSection = NULL;
    EFI_ACPI_MSDM_TABLE *Msdm = NULL;
    EFI_OA3_MSDM_STRUCTURE MsdmVariable = {0};
    EFI_GUID AmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
    UINTN  i;
    
    InitAmiLib(ImageHandle, SystemTable);

    // Check if it's a Recovery Mode then preserve the Product Key
    if (GetBootMode() == BOOT_IN_RECOVERY_MODE) {
        Status = PreserveProductKey();
        return Status;
    }
    
    // Locate the $FID table
    Status = LocateSectionResource(
        &FidTableGuid, 
        &FidTableSectionGuid, 
        &FidSection
    );
    if (EFI_ERROR(Status)) {
        TRACE((TRACE_ALWAYS, "OEM Activation: FID table Not Found!!!\n"));
        return Status;
    }
    Fid = (FW_VERSION*)(FidSection + sizeof(EFI_GUID)); // skip the GUID

#if OEM_ACTIVATION_TABLE_LOCATION == 0
    // Check version of the FID table
    if ( Fid->StructVersion < FID_SUPPORTED_VERSION ) {
        TRACE((TRACE_ALWAYS, "OEM Activation: FID table version %d is unsupported!!!\n",Fid->StructVersion));
        return EFI_UNSUPPORTED;
    }
#endif

    // Create MSDM table
    Status = pBS->AllocatePool( EfiACPIMemoryNVS, sizeof(EFI_ACPI_MSDM_TABLE), &Msdm );
    if (EFI_ERROR(Status))
        return Status;
    Msdm->Header.Signature  = MSDM_SIG;
    Msdm->Header.Length     = sizeof(EFI_ACPI_MSDM_TABLE);
    Msdm->Header.Revision   = MSDM_REVISION;
    Msdm->Header.OemRev     = ACPI_OEM_REV;
    Msdm->Header.CreatorId  = CREATOR_ID_AMI;
    Msdm->Header.CreatorRev = CREATOR_REV_MS;

    // Copy OEM ID and OEM Table ID 
    MemCpy( 
        (UINT8*)&Msdm->Header.OemId,
        (UINT8*)&Fid->OemId,
        sizeof(Fid->OemId)
    );
    MemCpy( 
        (UINT8*)&Msdm->Header.OemTblId,
        (UINT8*)&Fid->OemTableId,
        sizeof(Fid->OemTableId)
    );

    // Copy OEM Activation Key
    MemCpy( 
        (UINT8*)&Msdm->Version,
#if OEM_ACTIVATION_TABLE_LOCATION == 0
        (UINT8*)&Fid->OemActivationKey,         // Copy Key from the FID structure
#else
        (UINT8*)OEM_ACTIVATION_TABLE_ADDRESS,   // Copy Key from the NCB
#endif
        sizeof(EFI_ACPI_MSDM_TABLE) - sizeof(ACPI_HDR) 
    );
    pBS->FreePool(FidSection);

    // Check if there is empty Product Key 
    for ( i = 0; i < sizeof(Msdm->Data); i++ ) {

        if ( Msdm->Data[i] != 0xFF ) {

            EFI_ACPI_TABLE_PROTOCOL *AcpiTableProtocol = NULL;
            UINTN  TableKey = 0;

            // Locate the ACPI support protocol
            Status = pBS->LocateProtocol(
                &gEfiAcpiTableProtocolGuid, 
                NULL, 
                &AcpiTableProtocol
            );
            if (EFI_ERROR(Status))
                TRACE((TRACE_ALWAYS, "OEM Activation: Unable to locate AcpiSupportProtocol!\n"));
                
            else {
                // Publish MSDM ACPI table
                Status = AcpiTableProtocol->InstallAcpiTable(
                    AcpiTableProtocol,
                    Msdm,
                    sizeof(EFI_ACPI_MSDM_TABLE),
                    &TableKey
                );
                if (EFI_ERROR(Status))
                    TRACE((TRACE_ALWAYS, "OEM Activation: SetAcpiTable failed!\n"));
                else
                    TRACE((TRACE_ALWAYS, "OEM Activation: MSDM table has been published.\n"));
            }
            pBS->FreePool(Msdm);
            return Status;
        }
    }

    TRACE((TRACE_ALWAYS, "OEM Activation: Found empty Product Key.\n"));

    MsdmVariable.MsdmAddress = (EFI_PHYSICAL_ADDRESS)Msdm;
#if OEM_ACTIVATION_TABLE_LOCATION == 1
    MsdmVariable.ProductKeyAddress = (EFI_PHYSICAL_ADDRESS)OEM_ACTIVATION_TABLE_ADDRESS;
#endif

    Status = pRS->SetVariable(
        EFI_OA3_MSDM_VARIABLE,
        &AmiGlobalVariableGuid,
        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
        sizeof(EFI_OA3_MSDM_STRUCTURE),
        &MsdmVariable
    );
    ASSERT_EFI_ERROR(Status);
    TRACE((TRACE_ALWAYS, "OEM Activation: MsdmAddress=%X\n",MsdmVariable.MsdmAddress));

    return Status;
}


//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
