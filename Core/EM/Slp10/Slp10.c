//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/Slp10/Slp10.c 1     6/18/09 5:31p Vyacheslava $
//
// $Revision: 1 $
//
// $Date: 6/18/09 5:31p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Slp10/Slp10.c $
// 
// 1     6/18/09 5:31p Vyacheslava
// Initial Creation
// 
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name: Slp10.c
//
// Description: Implementation of the SLP 1.0 eModule.
//
//<AMI_FHDR_END>
//*****************************************************************************

//----------------------------------------------------------------------------

#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol/LegacyBiosExt.h>
#include "Slp10.h"

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    Slp10_EntryPoint
// 
// Description:  This function is the entry point of the Slp10 eModule.
//               
// Parameter:    
//  ImageHandle - Image handle for this driver image.
//  SystemTable - Pointer to the EFI system table.
//
// Return value: EFI_STATUS
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS Slp10_EntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;
    EFI_GUID EfiLegacyBiosExtProtocolGuid = EFI_LEGACY_BIOS_EXT_PROTOCOL_GUID;
    EFI_GUID BiosFeaturesSectionGuid = BIOS_FEATURES_SECTION_GUID;
    EFI_LEGACY_BIOS_EXT_PROTOCOL *LegacyBiosExtProtocol = NULL;
    UINT8 *DataPtr = NULL;
    UINTN Size = 0;
    UINTN Address;

    InitAmiLib( ImageHandle, SystemTable );

    // Get OEM data from Aptio FV
    Status = ReadImageResource(
        ImageHandle, 
        &BiosFeaturesSectionGuid, 
        &DataPtr, 
        &Size
    );
    if (EFI_ERROR(Status))
        return Status;

    // Locate the Aptio extended Legacy Protocol
    Status = pBS->LocateProtocol( 
        &EfiLegacyBiosExtProtocolGuid, 
        NULL, 
        &LegacyBiosExtProtocol
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status))
        return Status;

    // Copy OEM Data to Legacy Table
    Address = LegacyBiosExtProtocol->CopyLegacyTable(
        ((BIOS_OEM_DATA*)DataPtr)->Data,    // Pointer to SLP data
        OEM_DATA_SPACE_SIZE,                // Size of the data
        1,                                  // Alignment
        OEM_DATA_LOCATION_BIT               // Location Attribute
    );
    ASSERT_EFI_ERROR(Address);

    Status = pBS->FreePool(DataPtr);
    ASSERT_EFI_ERROR(Status);
    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
