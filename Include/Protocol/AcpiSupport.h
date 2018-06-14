//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/AcpiSupport.h 9     6/16/11 3:26p Felixp $Revision: 6 $
//
// $Date: 6/16/11 3:26p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/AcpiSupport.h $
// 
// 9     6/16/11 3:26p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 8     5/27/11 5:53p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		AcpiSupport.h
//
// Description:	Definition of the ACPI Support protocol.  
//				This is defined in the Tiano ACPI External 
//				Product Specification, revision 0.5.1.
//
//**********************************************************************
#ifndef __ACPI_SUPPORT_PROTOCOL_H__
#define __ACPI_SUPPORT_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
/****** DO NOT WRITE ABOVE THIS LINE *******/
//**********************************************************************
#include <EFI.h>

// ACPI Support Protocol GUID
#define EFI_ACPI_SUPPORT_GUID \
	{0xdbff9d55, 0x89b7, 0x46da, 0xbd, 0xdf, 0x67, 0x7d, 0x3d, 0xc0, 0x24, 0x1d }

GUID_VARIABLE_DECLARATION(gEfiAcpiSupportGuid,EFI_ACPI_SUPPORT_GUID);

#include <Protocol/AcpiSystemDescriptionTable.h>

// Forward reference 
typedef struct _EFI_ACPI_SUPPORT_PROTOCOL 	EFI_ACPI_SUPPORT_PROTOCOL;

//**********************************************************************
// Protocol Data Definitions
#define EFI_ACPI_TABLE_VERSION_X    	(EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0 | EFI_ACPI_TABLE_VERSION_4_0)
#define EFI_ACPI_TABLE_VERSION_ALL  	(EFI_ACPI_TABLE_VERSION_1_0B|EFI_ACPI_TABLE_VERSION_X)

//**********************************************************************
// Protocol Member Functions
//**********************************************************************

// Retrieve a copy of an ACPI table and the handle of the table.
typedef EFI_STATUS (EFIAPI *EFI_ACPI_GET_ACPI_TABLE) (
	IN 	EFI_ACPI_SUPPORT_PROTOCOL    	*This,
  	IN 	INTN							Index,
  	OUT VOID							**Table,
  	OUT EFI_ACPI_TABLE_VERSION			*Version,
  	OUT UINTN							*Handle );

// Add, update, or remove a table.
typedef EFI_STATUS (EFIAPI *EFI_ACPI_SET_ACPI_TABLE) (
  	IN 	EFI_ACPI_SUPPORT_PROTOCOL		*This,
  	IN 	VOID							*Table    OPTIONAL,
  	IN 	BOOLEAN							Checksum,
  	IN 	EFI_ACPI_TABLE_VERSION			Version,
  	IN 	OUT	UINTN						*Handle );

// Publish tables to the outside world
typedef EFI_STATUS (EFIAPI *EFI_ACPI_PUBLISH_TABLES) (
	IN 	EFI_ACPI_SUPPORT_PROTOCOL		*This,
  	IN 	EFI_ACPI_TABLE_VERSION			Version );

// ACPI Support Protocol
typedef struct _EFI_ACPI_SUPPORT_PROTOCOL {
	EFI_ACPI_GET_ACPI_TABLE     		GetAcpiTable;
	EFI_ACPI_SET_ACPI_TABLE     		SetAcpiTable;
	EFI_ACPI_PUBLISH_TABLES     		PublishTables;
} EFI_ACPI_SUPPORT_PROTOCOL;

#if BACKWARD_COMPATIBLE_MODE
#include <Protocol/AcpiTable.h>
#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_ACPI_SUPPORT_PROTOCOL_H
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

