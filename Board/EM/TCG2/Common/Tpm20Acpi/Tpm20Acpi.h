//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20Acpi/Tpm20Acpi.h 1     4/21/14 2:19p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:19p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/Tpm20PlatformDxe/Tpm20Acpi/Tpm20Acpi.h $
// 
// 1     4/21/14 2:19p Fredericko
// 
// 1     10/08/13 12:06p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:58p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: 
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _TPM20ACPI_H_
#define _TPM20ACPI_H_

#include <Efi.h>
#include <Protocol\AcpiTable.h>
#include <Hob.h>

#define ME_DATA_HOB_GUID \
  { 0x1e94f097, 0x5acd, 0x4089, 0xb2, 0xe3, 0xb9, 0xa5, 0xc8, 0x79, 0xa7, 0x0c }

#define INTERNAL_NVS_AREA_PROTOCOL_GUID \
  { \
    0x74e1e48, 0x8132, 0x47a1, 0x8c, 0x2c, 0x3f, 0x14, 0xad, 0x9a, 0x66, 0xdc \
  }

#define EFI_SIGNATURE_16(A, B)        ((A) | (B << 8))
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))

#ifndef EFI_ACPI_5_0_TRUSTED_COMPUTING_PLATFORM_2_TABLE_SIGNATURE
#define EFI_ACPI_5_0_TRUSTED_COMPUTING_PLATFORM_2_TABLE_SIGNATURE  EFI_SIGNATURE_32('T', 'P', 'M', '2')

#define EFI_SIGNATURE_64(A, B, C, D, E, F, G, H) \
    (EFI_SIGNATURE_32 (A, B, C, D) | ((UINT64) (EFI_SIGNATURE_32 (E, F, G, H)) << 32))

#endif

#define TPM20TABLEOEMREVISION 1
#define CREATOR_ID_AMI        0x20494D41  //" IMA""AMI "(AMI)
#define EFI_TPM2_ACPI_TABLE_START_METHOD_ACPI  2
#define EFI_TPM2_ACPI_TABLE_REVISION  3

#pragma pack (1)


typedef struct {
  UINT32                           Signature;
  UINT32                           Length;
  UINT8                            Revision;
  UINT8                            Checksum;
  UINT8                            OemId[6];
  UINT64                           OemTableId;
  UINT32                           OemRevision;
  UINT32                           CreatorId;
  UINT32                           CreatorRevision;
} EFI_ACPI_DESCRIPTION_HEADER;

typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER Header;
  UINT32                      Flags;
  UINT64                      AddressOfControlArea;
  UINT32                      StartMethod;
} EFI_TPM2_ACPI_TABLE;

typedef struct {
  UINT32   Reserved;
  UINT32   Error;
  UINT32   Cancel;
  UINT32   Start;
  UINT64   InterruptControl;
  UINT32   CommandSize;
  UINT64   Command;
  UINT32   ResponseSize;
  UINT64   Response;
} EFI_TPM2_ACPI_CONTROL_AREA;

typedef struct {
  UINT64            BufferAddress;
}INTEL_PTT_HOB_DATA;

#pragma pack ()

#define GET_HOB_TYPE( Hob )     ((Hob).Header->HobType)
#define GET_HOB_LENGTH( Hob )   ((Hob).Header->HobLength)
#define GET_NEXT_HOB( Hob )     ((Hob).Raw + GET_HOB_LENGTH( Hob ))
#define END_OF_HOB_LIST( Hob )  (GET_HOB_TYPE( Hob ) ==\
                                 EFI_HOB_TYPE_END_OF_HOB_LIST)

EFI_STATUS GetNextGuidHob(
    IN OUT VOID          **HobStart,
    IN EFI_GUID          * Guid,
    OUT VOID             **Buffer,
    OUT UINTN            *BufferSize OPTIONAL );

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
