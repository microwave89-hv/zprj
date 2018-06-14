//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/AcpiTable.h 1     5/27/11 5:52p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/27/11 5:52p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/AcpiTable.h $
// 
// 1     5/27/11 5:52p Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  AcpiTable.h
//
// Description:	AcpiTable Protocol
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __ACPI_TABLE_PROTOCOL__H__
#define __ACPI_TABLE_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_ACPI_TABLE_PROTOCOL_GUID \
    { 0xffe06bdd, 0x6107, 0x46a6, 0x7b, 0xb2, 0x5a, 0x9c, 0x7e, 0xc5, 0x27, 0x5c }

GUID_VARIABLE_DECLARATION(gEfiAcpiTableProtocolGuid,EFI_ACPI_TABLE_PROTOCOL_GUID);

// Forward reference 
typedef struct _EFI_ACPI_TABLE_PROTOCOL 	EFI_ACPI_TABLE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_ACPI_TABLE_INSTALL_ACPI_TABLE)(
  IN   CONST EFI_ACPI_TABLE_PROTOCOL *This,
  IN   CONST VOID                    *AcpiTableBuffer,
  IN   UINTN                         AcpiTableBufferSize,
  OUT  UINTN                         *TableKey
);

typedef EFI_STATUS (EFIAPI *EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE)(
  IN CONST EFI_ACPI_TABLE_PROTOCOL *This,
  IN UINTN                         TableKey
);

struct _EFI_ACPI_TABLE_PROTOCOL {
  EFI_ACPI_TABLE_INSTALL_ACPI_TABLE   InstallAcpiTable;
  EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE UninstallAcpiTable;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif // __ACPI_TABLE_PROTOCOL__H__
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************