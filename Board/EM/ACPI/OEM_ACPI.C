//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Modules/ACPI/Template/Board/OEM_ACPI.C 3     12/22/10 5:11p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 12/22/10 5:11p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Board/OEM_ACPI.C $
// 
// 3     12/22/10 5:11p Oleksiyy
// [TAG]  		EIP49816
// [Category]  	Improvement
// [Description]  	Function OemAcpiSetPlatformId added as eLink
// [Files]  		ACPi.mak, ACPI.sdl and OEM_ACPI.c
// 
// 2     3/26/09 4:47p Oleksiyy
// New ACPI Core realization - improves logic, execution time and memory
// usage of ACPI module.
// 
// 1     2/18/09 3:50p Oleksiyy
// 
// 1     1/12/09 11:40a Yakovlevs
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	OEM_ACPI.C
//
// Description:	Oem hooks used in ACPI Module
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Efi.h>
#include <ACPI.h>
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include "AcpiOemElinks.h"
typedef EFI_STATUS (ACPI_OEM_FUNCTION)(IN OUT ACPI_HDR *AcpiHdr);

extern ACPI_OEM_FUNCTION OEM_LIST EndOfOemList;
ACPI_OEM_FUNCTION* AcpiOemPartsList[] = {OEM_LIST NULL};
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   OemAcpiSetPlatformId
//
//  Description:
//  This function provides platform specific OEM_ID and OEM_TABLE_ID to 
//  overwrite default ACPI Table header.
//
//  Input:
// 	IN OUT ACPI_HDR *AcpiHdr    - ACPI TABLE header
//
//  Output:
//  EFI_STATUS  EFI_SUCCESS if Values overwtitten.
//              EFI_INSUPPORTED if no need to change values - use default.
//
//  NOTE: UINT8 *AcpiOemId[6]; UINT8 *AcpiOemTblId[8] avoid buffer overrun!
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS OemAcpiSetPlatformId(IN OUT ACPI_HDR *AcpiHdr){
    EFI_STATUS       Status=EFI_UNSUPPORTED;
//----------------------------------------
// Any additional variables goes here...

    UINTN i;

//----------------------------------------
//////////////////////////////////////////////////////////////////////////
// PORTING GOES HERE: CALL CHIPSET SPECIFIC FUNCTION TO GET PLATFORM ID //
// AND MODIY AcpiOemId[6], AcpiOemTblId[8] PARAMETERS ACCORDINALLY      //
//////////////////////////////////////////////////////////////////////////
    
    for (i=0; AcpiOemPartsList[i]; i++) Status = AcpiOemPartsList[i](AcpiHdr);



//////////////////////////////////////////////////////////////////////////
//                      PORTING ENDS HERE                               //
//////////////////////////////////////////////////////////////////////////
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************