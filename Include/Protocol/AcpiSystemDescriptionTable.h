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

//*************************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/AcpiSystemDescriptionTable.h 1     5/27/11 5:52p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/27/11 5:52p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/AcpiSystemDescriptionTable.h $
// 
// 1     5/27/11 5:52p Felixp
// 
// 1     5/13/11 4:50p Yakovlevs
// [TAG]  		EIP 56526 
// [Category]  	New Feature
// [Description]  	ACPI Manipulation Protocol Initial Checkin

//*************************************************************************
//<AMI_FHDR_START>
//
// Name: AcpiSystemDescriptionTable.h
//
// Description:
//  Definition of PI 1.2 Vol 5 ACPI System Description Table Protocol. 
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __ACPI_SYSTEM_DESCRIPTION_TABLE_H___
#define __ACPI_SYSTEM_DESCRIPTION_TABLE_H___
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>

#define EFI_ACPI_SDT_PROTOCOL_GUID \
  { 0xeb97088e, 0xcfdf, 0x49c6, 0xbe, 0x4b, 0xd9, 0x6, 0xa5, 0xb2, 0xe, 0x86 }
  
GUID_VARIABLE_DECLARATION(gEfiAcpiSdtProtocolGuid, EFI_ACPI_SDT_PROTOCOL_GUID);

typedef UINT32  EFI_ACPI_TABLE_VERSION;
typedef VOID    *EFI_ACPI_HANDLE;

//**********************************************************************
// ACPI Version bitmap definition:
//
// EFI_ACPI_TABLE_VERSION_1_0B - ACPI Version 1.0b (not supported curently)
// EFI_ACPI_TABLE_VERSION_2_0 - ACPI Version 2.0 
// EFI_ACPI_TABLE_VERSION_NONE - No ACPI Versions.  This might be used
//  to create memory-based operation regions or other information
//  that is not part of the ACPI "tree" but must still be found
//  in ACPI memory space and/or managed by the core ACPI driver.
//
//**********************************************************************
#define EFI_ACPI_TABLE_VERSION_NONE (1 << 0)
#define EFI_ACPI_TABLE_VERSION_1_0B (1 << 1)
#define EFI_ACPI_TABLE_VERSION_2_0  (1 << 2)
#define EFI_ACPI_TABLE_VERSION_3_0  (1 << 3)
#define EFI_ACPI_TABLE_VERSION_4_0  (1 << 4)
  
typedef UINT32 EFI_ACPI_DATA_TYPE;
#define EFI_ACPI_DATA_TYPE_NONE         0
#define EFI_ACPI_DATA_TYPE_OPCODE       1
#define EFI_ACPI_DATA_TYPE_NAME_STRING  2
#define EFI_ACPI_DATA_TYPE_OP           3
#define EFI_ACPI_DATA_TYPE_UINT         4
#define EFI_ACPI_DATA_TYPE_STRING       5
#define EFI_ACPI_DATA_TYPE_CHILD        6
  
typedef struct {
  UINT32    Signature;
  UINT32    Length;
  UINT8     Revision;
  UINT8     Checksum;
  CHAR8     OemId[6];
  CHAR8     OemTableId[8];
  UINT32    OemRevision;
  UINT32    CreatorId;
  UINT32    CreatorRevision;
} EFI_ACPI_SDT_HEADER;
  
typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_NOTIFICATION_FN)(
  IN EFI_ACPI_SDT_HEADER    *Table,     ///< A pointer to the ACPI table header.
  IN EFI_ACPI_TABLE_VERSION Version,    ///< The ACPI table's version.
  IN UINTN                  TableKey    ///< The table key for this ACPI table.
);
  
typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_GET_ACPI_TABLE2)(
  IN    UINTN                   Index,
  OUT   EFI_ACPI_SDT_HEADER     **Table,
  OUT   EFI_ACPI_TABLE_VERSION  *Version,
  OUT   UINTN                   *TableKey
);

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_REGISTER_NOTIFY)(
  IN BOOLEAN                    Register,
  IN EFI_ACPI_NOTIFICATION_FN   Notification
);

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_OPEN)(
  IN    VOID            *Buffer,
  OUT   EFI_ACPI_HANDLE *Handle 
);

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_OPEN_SDT)(
  IN    UINTN           TableKey,
  OUT   EFI_ACPI_HANDLE *Handle
);

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_CLOSE)(
  IN EFI_ACPI_HANDLE Handle
);

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_GET_CHILD)(
  IN EFI_ACPI_HANDLE        ParentHandle,
  IN OUT EFI_ACPI_HANDLE    *Handle
);

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_GET_OPTION)(
  IN        EFI_ACPI_HANDLE     Handle,
  IN        UINTN               Index,
  OUT       EFI_ACPI_DATA_TYPE  *DataType,
  OUT CONST VOID                **Data,
  OUT       UINTN               *DataSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_SET_OPTION)(
  IN        EFI_ACPI_HANDLE Handle,
  IN        UINTN           Index,
  IN CONST  VOID            *Data,
  IN        UINTN           DataSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_ACPI_FIND_PATH)(
  IN    EFI_ACPI_HANDLE HandleIn,
  IN    VOID            *AcpiPath,
  OUT   EFI_ACPI_HANDLE *HandleOut
);

typedef struct _EFI_ACPI_SDT_PROTOCOL {
  // Specifies the ACPI version supported by this protocol.
  EFI_ACPI_TABLE_VERSION    AcpiVersion;
  EFI_ACPI_GET_ACPI_TABLE2  GetAcpiTable;
  EFI_ACPI_REGISTER_NOTIFY  RegisterNotify;
  EFI_ACPI_OPEN             Open;
  EFI_ACPI_OPEN_SDT         OpenSdt;
  EFI_ACPI_CLOSE            Close;
  EFI_ACPI_GET_CHILD        GetChild;
  EFI_ACPI_GET_OPTION       GetOption;
  EFI_ACPI_SET_OPTION       SetOption;
  EFI_ACPI_FIND_PATH        FindPath;
} EFI_ACPI_SDT_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif // __ACPI_SYSTEM_DESCRIPTION_TABLE_H___

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
