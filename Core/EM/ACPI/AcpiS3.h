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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/AcpiS3.h 6     3/26/09 4:51p Oleksiyy $
//
// $Revision: 6 $
//
// $Date: 3/26/09 4:51p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/AcpiS3.h $
// 
// 6     3/26/09 4:51p Oleksiyy
// New ACPI Core implementation - improves logic, execution time and
// memory usage of ACPI module.
// 
// 5     4/15/08 9:15p Yakovlevs
// Functions Headers added
// 
// 4     4/09/08 5:14p Yakovlevs
// Make S3 Save code remember all possible locations of FACS.
// 
// 3     11/20/06 4:14a Yakovlevs
// updated structure of ACPI_CPU_DATA to match with declared in MRC code
// 
// 2     9/22/06 6:10p Markw
// 64-bit fix.
// 
// 1     5/04/05 12:24p Markw
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	AcpiS3.h
//
// Description:	ACPI S3 data structures definitions
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __ACPI_S3_H__
#define __ACPI_S3_H__

#include <Efi.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ACPI_GLOBAL_VARIABLE	L"AcpiGlobalVariable"
#define EFI_ACPI_VARIABLE_GUID \
	{0xaf9ffd67,0xec10,0x488a,0x9d,0xfc,0x6c,0xbf,0x5e,0xe2,0x2c,0x2e}

#pragma pack (1)
typedef struct {
	UINT16	Limit;
	UINT32	Base;
} PSEUDO_DESCRIPTOR;
#pragma pack()

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: ACPI_CPU_DATA
//
// Description: ACPI Cpu related data
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// APState                 BOOLEAN
// S3BootPath              BOOLEAN
// WakeUpBuffer            EFI_PHYSICAL_ADDRESS
// GdtrProfile             EFI_PHYSICAL_ADDRESS
// IdtrProfile             EFI_PHYSICAL_ADDRESS
// CpuPrivateData          EFI_PHYSICAL_ADDRESS
// StackAddress            EFI_PHYSICAL_ADDRESS
// MicrocodePointerBuffer  EFI_PHYSICAL_ADDRESS
// SmramBase               EFI_PHYSICAL_ADDRESS
// SmmStartImageBase       EFI_PHYSICAL_ADDRESS
// SmmStartImageSize       UINT32
// NumberOfCpus            UINT32
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>

typedef struct ACPI_CPU_DATA {
  BOOLEAN               APState;
  BOOLEAN               S3BootPath;
  EFI_PHYSICAL_ADDRESS  WakeUpBuffer;
  EFI_PHYSICAL_ADDRESS  GdtrProfile;
  EFI_PHYSICAL_ADDRESS  IdtrProfile;
  EFI_PHYSICAL_ADDRESS  CpuPrivateData;
  EFI_PHYSICAL_ADDRESS  StackAddress;
  EFI_PHYSICAL_ADDRESS  MicrocodePointerBuffer;
  EFI_PHYSICAL_ADDRESS  SmramBase;
  EFI_PHYSICAL_ADDRESS  SmmStartImageBase;
  UINT32                SmmStartImageSize;
  UINT32                NumberOfCpus;
} ACPI_CPU_DATA;

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: ACPI_VARIABLE_SET
//
// Description: The structure combine all ACPI related variables into one 
// in order to boost performance
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// AcpiReservedMemoryBase   EFI_PHYSICAL_ADDRESS
// AcpiReservedMemorySize   UINT32
// S3ReservedLowMemoryBase  EFI_PHYSICAL_ADDRESS
// AcpiBootScriptTable      EFI_PHYSICAL_ADDRESS
// RuntimeScriptTableBase   EFI_PHYSICAL_ADDRESS
// AcpiFacsTable[3]         EFI_PHYSICAL_ADDRESS
// SystemMemoryLength       UINT64
// AcpiCpuData              ACPI_CPU_DATA
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>

typedef struct _ACPI_VARIABLE_SET {
	//
	// Acpi Related variables
	//
	EFI_PHYSICAL_ADDRESS	AcpiReservedMemoryBase;
	UINT32			AcpiReservedMemorySize;
	EFI_PHYSICAL_ADDRESS	S3ReservedLowMemoryBase;
	EFI_PHYSICAL_ADDRESS	AcpiBootScriptTable;
	EFI_PHYSICAL_ADDRESS	RuntimeScriptTableBase;
	EFI_PHYSICAL_ADDRESS	AcpiFacsTable[3];
	UINT64			SystemMemoryLength;
	ACPI_CPU_DATA		AcpiCpuData;
} ACPI_VARIABLE_SET;




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
