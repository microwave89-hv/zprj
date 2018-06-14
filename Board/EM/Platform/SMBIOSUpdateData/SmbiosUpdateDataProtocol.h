/*++
Copyright (c) 2009 Intel Corporation. All rights reserved.
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
--*/

#ifndef _EFI_SMBOS_UPDATE_DATA_PROTOCOL_H_
#define _EFI_SMBOS_UPDATE_DATA_PROTOCOL_H_

#include <Protocol\SMBios.h>
#include <Protocol\SmbiosGetFlashDataProtocol.h>

#define EFI_SMBIOS_UPDATE_DATA_PROTOCOL_GUID \
  {0x67269263, 0xaf1, 0x45dd, 0x93, 0xc8, 0x29, 0x99, 0x21, 0xd0, 0xe1, 0xe9}

typedef struct _EFI_SMBIOS_UPDATE_DATA_PROTOCOL EFI_SMBIOS_UPDATE_DATA_PROTOCOL;

typedef UINT16 (EFIAPI *EFI_SMBIOS_UPDATE_DATA_GET_FREE_HANDLE) (
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
);

typedef UINT16 (EFIAPI *EFI_SMBIOS_UPDATE_DATA_FIND_STRUCTURE) (
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT8 Type, 
    IN  UINT8 Index
); 

typedef UINT8 * (EFIAPI *EFI_SMBIOS_UPDATE_DATA_GET_STRUCTURE_BASE) (
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
); 

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_UPDATE_DATA_DELETE_STRUCTURE) (
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
);

typedef UINT8 * (EFIAPI *EFI_SMBIOS_UPDATE_DATA_COPY_STRUCTURE) (
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
);

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_UPDATE_DATA_INSERT_STRUCTURE) (
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT8                     *StructurePtrTemp,
    IN  UINT16                    BufferSize
);

typedef struct _EFI_SMBIOS_UPDATE_DATA_PROTOCOL {
    EFI_SMBIOS_UPDATE_DATA_GET_FREE_HANDLE    SMBIOS_GetFreeHandle;
    EFI_SMBIOS_UPDATE_DATA_FIND_STRUCTURE     SMBIOS_FindStructure;
    EFI_SMBIOS_UPDATE_DATA_GET_STRUCTURE_BASE SMBIOS_GetStructureBase;
    EFI_SMBIOS_UPDATE_DATA_DELETE_STRUCTURE   SMBIOS_DeleteStructure;
    EFI_SMBIOS_UPDATE_DATA_COPY_STRUCTURE     SMBIOS_CopyStructure;
    EFI_SMBIOS_UPDATE_DATA_INSERT_STRUCTURE   SMBIOS_InsertStructure;
};

UINT16
SMBIOS_GetFreeHandle(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint
);

UINT16
SMBIOS_FindStructure(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT8 Type, 
    IN  UINT8 Index
);

UINT8 *
SMBIOS_GetStructureBase(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
);

EFI_STATUS
SMBIOS_DeleteStructure(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
);

UINT8 *
SMBIOS_CopyStructure(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT16                    Handle
);

EFI_STATUS
SMBIOS_InsertStructure(
    IN  SMBIOS_TABLE_ENTRY_POINT  *pSmbiosTableEntryPoint,
    IN  UINT8                     *StructurePtrTemp,
    IN  UINT16                    BufferSize
);  

#endif
