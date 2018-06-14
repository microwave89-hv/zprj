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
// $Header: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Restore/AcpiPeiS3Func.c 2     7/19/11 11:34a Oleksiyy $
//
// $Revision: 2 $
//
// $Date: 7/19/11 11:34a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Restore/AcpiPeiS3Func.c $
// 
// 2     7/19/11 11:34a Oleksiyy
// [TAG]  		EIP64108 
// [Category]  	Improvement
// [Description]  	ACPI, convert or update all eModules to be compliant
// with PI 1.2, and UEFI 2.3.1 specifications. 
// [Files]  		AcpiCore.c, mptable.c, AcpiS3Save.c, S3Resume.dxs,
// S3Resume.c, AcpiPeiS3Func.c, BootScriptExecuter.c and DxeIpl.c
// 
// 1     2/03/11 4:09p Oleksiyy
// [TAG]  		EIP53402 
// [Category]  	Improvement
// [Description]  	Create new label of ACPI with separate S3 Functionality
// [Files]  		S3Restore.cif
// S3Restore.sdl
// S3Restore.mak
// S3Resume.dxs
// AcpiS3Wake.asm
// S3Resume.c
// AcpiPeiS3Func.c
// AcpiPeiS3Func.h
// BootScriptExecuter.c
// 
// 7     3/26/09 4:51p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 6     4/29/08 4:38p Felixp
// Bug fix in GetAcpiS3Info: Initialize AcpiVariableSet variable with NULL
// to make sure there is no junk in the high 4 bytes in x64 mode.
// 
// 5     4/15/08 9:15p Yakovlevs
// Functions Headers added

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:    AcpiPeiS3Func.c
//
//  Description: ACPI S3 PEI support functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <EFI.h>
#include <Pei.h>
#include <Ppi\ReadOnlyVariable2.h>
#include <AmiPeiLib.h>
#include "AcpiS3.h"

CHAR16		gAcpiGlobalVariable[]	= ACPI_GLOBAL_VARIABLE;
EFI_GUID	gEfiAcpiVariableGuid	= EFI_ACPI_VARIABLE_GUID;

extern EFI_GUID gEfiPeiReadOnlyVariable2PpiGuid;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   GetAcpiS3Info
//
//  Description:
//  This function reads ACPI_VARIABLE_SET data from NVRAM and returns pointer to it 
//
//  Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to pointer to PEI services
//
//  Output:
//  ACPI_VARIABLE_SET* - pointer to ACPI_VARIABLE_SET structure (NULL if error occured)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

ACPI_VARIABLE_SET * GetAcpiS3Info(
	IN EFI_PEI_SERVICES **PeiServices
)
{
	EFI_PEI_READ_ONLY_VARIABLE2_PPI		*ReadOnlyVariable;
	ACPI_VARIABLE_SET					*AcpiVariableSet = NULL;

	UINTN		VariableSize = sizeof(ACPI_VARIABLE_SET*);
	EFI_STATUS	Status;

	Status = (*PeiServices)->LocatePpi(
		PeiServices,
		&gEfiPeiReadOnlyVariable2PpiGuid,
		0,
		NULL,
		&ReadOnlyVariable		
	);
	ASSERT_PEI_ERROR(PeiServices, Status);

	Status = ReadOnlyVariable->GetVariable(
		ReadOnlyVariable,
		gAcpiGlobalVariable,
		&gEfiAcpiVariableGuid,
		NULL,
		&VariableSize,
		&AcpiVariableSet
	);
	if (EFI_ERROR(Status)) return NULL;
	return AcpiVariableSet;
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

