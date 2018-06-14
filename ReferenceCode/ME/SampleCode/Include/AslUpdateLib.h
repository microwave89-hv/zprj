/** @file
  ASL dynamic update library definitions.
  This library provides dymanic update to various ASL structures.
  There may be different libraries for different environments (PEI, BS, RT, SMM).
  Make sure you meet the requirements for the library (protocol dependencies, use
  restrictions, etc).

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/
#ifndef _ASL_UPDATE_LIB_H_
#define _ASL_UPDATE_LIB_H_

//
// Include files
//
#include "Acpi.h"
#include "Acpi3_0.h"

#include EFI_PROTOCOL_DEPENDENCY (AcpiSupport)
#include EFI_PROTOCOL_DEPENDENCY (AcpiTable)

//
// AML parsing definitions
//
#define AML_NAME_OP       0x08
#define AML_SCOPE_OP      0x10
#define AML_PACKAGE_OP    0x12
#define AML_METHOD_OP     0x14
#define AML_OPREGION_OP   0x80
#define AML_DEVICE_OP     0x82
#define AML_PROCESSOR_OP  0x83

//
// Magic number definition for values to be updated
//
#define UINT16_BIT_MAGIC_NUMBER 0xFFFF
#define UINT32_BIT_MAGIC_NUMBER 0xFFFFFFFF

///
/// ASL PSS package structure layout
///
#pragma pack(1)
typedef struct {
  UINT8   NameOp;         ///< 12h ;First opcode is a NameOp.
  UINT8   PackageLead;    ///< 20h ;First opcode is a NameOp.
  UINT8   NumEntries;     ///< 06h ;First opcode is a NameOp.
  UINT8   DwordPrefix1;   ///< 0Ch
  UINT32  CoreFrequency;  ///< 00h
  UINT8   DwordPrefix2;   ///< 0Ch
  UINT32  Power;          ///< 00h
  UINT8   DwordPrefix3;   ///< 0Ch
  UINT32  TransLatency;   ///< 00h
  UINT8   DwordPrefix4;   ///< 0Ch
  UINT32  BMLatency;      ///< 00h
  UINT8   DwordPrefix5;   ///< 0Ch
  UINT32  Control;        ///< 00h
  UINT8   DwordPrefix6;   ///< 0Ch
  UINT32  Status;         ///< 00h
} PSS_PACKAGE_LAYOUT;
#pragma pack()

/**
  Initialize the ASL update library state.
  This must be called prior to invoking other library functions.

  @param[in] None

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
InitializeAslUpdateLib (
  VOID
  )
;

/**
  This procedure will update two kinds of asl code.
  1:  Operating Region base address and length.
  2:  Resource Consumption structures in device LDRC.

  @param[in] AslSignature         The signature of Operation Region that we want to update.
  @param[in] BaseAddress          Base address of IO trap.
  @param[in] Length               Length of IO address.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
UpdateAslCode (
  IN     UINT32                   AslSignature,
  IN     UINT16                   BaseAddress,
  IN     UINT8                    Length
  )
;

/**
  This function uses the ACPI support protocol to locate an ACPI table.
  It is really only useful for finding tables that only have a single instance,
  e.g. FADT, FACS, MADT, etc.  It is not good for locating SSDT, etc.

  @param[in] Signature            Pointer to an ASCII string containing the OEM Table ID from the ACPI table header
  @param[in] Table                Updated with a pointer to the table
  @param[in] Handle               AcpiSupport protocol table handle for the table found
  @param[in] Version              The version of the table desired

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
LocateAcpiTableBySignature (
  IN      UINT32                        Signature,
  IN OUT  EFI_ACPI_DESCRIPTION_HEADER   **Table,
  IN OUT  UINTN                         *Handle,
  IN OUT  EFI_ACPI_TABLE_VERSION        *Version
  )
;

/**
  This function uses the ACPI support protocol to locate an ACPI SSDT table.

  @param[in] TableId              Pointer to an ASCII string containing the OEM Table ID from the ACPI table header
  @param[in] TableIdSize          Length of the TableId to match.  Table ID are 8 bytes long, this function
                                  will consider it a match if the first TableIdSize bytes match
  @param[in] Table                Updated with a pointer to the table
  @param[in] Handle               AcpiSupport protocol table handle for the table found
  @param[in] Version              See AcpiSupport protocol, GetAcpiTable function for use

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
LocateAcpiTableByOemTableId (
  IN      UINT8                         *TableId,
  IN      UINT8                         TableIdSize,
  IN OUT  EFI_ACPI_DESCRIPTION_HEADER   **Table,
  IN OUT  UINTN                         *Handle,
  IN OUT  EFI_ACPI_TABLE_VERSION        *Version
  )
;

/**
  This function calculates and updates an UINT8 checksum.

  @param[in] Buffer               Pointer to buffer to checksum
  @param[in] Size                 Number of bytes to checksum
  @param[in] ChecksumOffset       Offset to place the checksum result in

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
AcpiChecksum (
  IN VOID                         *Buffer,
  IN UINTN                        Size,
  IN UINTN                        ChecksumOffset
  )
;
#endif
