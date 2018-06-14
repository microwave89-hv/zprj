//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctGuidLib/IsctAcpiTableStorage/IsctAcpiTableStorage.c 1     9/02/12 11:20p Bensonlai $
//
// $Revision: 1 $
//
// $Date: 9/02/12 11:20p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctGuidLib/IsctAcpiTableStorage/IsctAcpiTableStorage.c $
// 
// 1     9/02/12 11:20p Bensonlai
// Intel Smart Connect Technology initially releases.
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  IsctAcpiTableStorage.c
//
// Description:	The GUID definition for Isct ACPI table storage file name
//
//<AMI_FHDR_END>
//**********************************************************************

//
// Statements that include other files
//
#include "EdkIIGlueDxe.h"
#include "IsctAcpiTableStorage.h"

//
// Protocol GUID definition
//
EFI_GUID  gIsctAcpiTableStorageGuid = ISCT_ACPI_TABLE_STORAGE_GUID;

//
// Protocol description
//
EFI_GUID_STRING
  (&gIsctAcpiTableStorageGuid, "Isct ACPI Table Storage File Name", "Isct ACPI Table Storage file name GUID");

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
