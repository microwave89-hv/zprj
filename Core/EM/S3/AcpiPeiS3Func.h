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
// $Header: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Restore/AcpiPeiS3Func.h 1     2/03/11 4:09p Oleksiyy $
//
// $Revision: 1 $
//
// $Date: 2/03/11 4:09p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/S3Support/S3Restore/AcpiPeiS3Func.h $
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
// 3     3/26/09 4:51p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 2     8/22/05 4:06p Markw
// Removed get cpu info.
// 
// 1     5/06/05 1:44p Markw
// 
//**********************************************************************

#ifndef __ACPI_PEI_S3_FUNC_H__
#define __ACPI_PEI_S3_FUNC_H__

#include <Efi.h>
#include "AcpiS3.h"

#ifdef __cplusplus
extern "C" {
#endif


ACPI_VARIABLE_SET * GetAcpiS3Info(
	IN EFI_PEI_SERVICES **PeiServices
);


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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
