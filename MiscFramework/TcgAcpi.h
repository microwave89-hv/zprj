#ifndef _TCG_ACPI_3_0_H_
#define _TCG_ACPI_3_0_H_

#define EFI_ACPI_TABLE_GUID \
  { \
    0xeb9d2d30, 0x2d88, 0x11d3, 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d \
  }

#define EFI_ACPI_20_TABLE_GUID \
  { \
    0x8868e871, 0xe4f1, 0x11d3, 0xbc, 0x22, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 \
  }

#define EFI_ACPI_30_TABLE_GUID EFI_ACPI_20_TABLE_GUID

extern EFI_GUID gEfiAcpiTableGuid;
extern EFI_GUID gEfiAcpi20TableGuid;
extern EFI_GUID gEfiAcpi30TableGuid;
//#include "Acpi.h"


#pragma pack(1)

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


//
// "TCPA" Trusted Computing Platform Alliance Capabilities Table
//
#define EFI_ACPI_3_0_TRUSTED_COMPUTING_PLATFORM_ALLIANCE_CAPABILITIES_TABLE_SIGNATURE 0x41504354


#pragma pack()

#endif
