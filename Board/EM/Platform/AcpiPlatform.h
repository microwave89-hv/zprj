//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatform.h 12    7/11/14 4:00a Joshchou $
//
// $Revision: 12 $
//
// $Date: 7/11/14 4:00a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/AcpiPlatform.h $
// 
// 12    7/11/14 4:00a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Support Debug Port Table.
// [Files]  		AcpiPlatform.c
// AcpiPlatform.h
// AcpiPlatform.cif
// 
// 11    4/23/14 4:21a Joshchou
// 
// 10    9/27/13 10:43a Joshchou
// [TAG]  		EIP137454
// [Category]  	New Feature
// [Description]  	Follow Intel sample code to add LPIT table.
// 
// 9     9/18/13 6:26a Joshchou
// [TAG]  		EIP136411
// [Category]  	Improvement
// [Description]  	Support MWAIT LPI State Descriptor[1].
// 
// 8     7/16/13 6:00a Alanlin
// [TAG] EIP127540
// [Category] Normal
// [Severity] Normal
// [Description] Windows* 8.1 Micro-PEP (uPEP) ASL Support Version 0.5
// [Files] AcpiPlatform.c, AcpiPlatform.h
// 
// 7     6/28/13 5:22a Alanlin
// [TAG] None
// [Category] Important
// [Severity] Important
// [Description]  Fixed that Processors device are disappeared under OS
// device manager.
// [Files] AcpiPlatform.c, AcpiPlatform.h
// 
// 6     11/20/12 7:08a Alanlin
// [TAG] None
// [Category] New Feature
// [Severity] Important
// [Description] SensorHub SSDT acpi table support
// [Files] Acpiplatform.c, Acpiplatform.cif, Acpiplatform.h,
// SsdtSensorHub.asl, SsdtSensorHub.mak, SsdtSensorHub.sdl 
// 
// [TAG] None
// [Category] Important
// [Severity] Important
// [Description] Update Shark Bay Client ACPI Reference Code Beta Version
// 0.8.0
// 
// 5     11/09/12 5:18a Alanlin
// [TAG]           None
// [Category]      New Feature
// [Severity]      Important
// [Description]   ZpOdd SSDT acpi table support
// [Files]         Acpiplatform.c, Acpiplatform.cif, Acpiplatform.h,
//                 Acpiplatform.sd, Acpiplatform.uni
// 
// 4     10/31/12 4:40a Alanlin
// [TAG]         None
// [Category]    New Feature
// [Severity]    Normal
// [Description] Support Acpi Debug SSDT.              
// 
// 3     9/12/12 7:21a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Remove AOAC for Intel Smart Connect Technology module.
// [Files]         GlobalNvsArea.h, GloblNvs.asl
// 
// 2     8/31/12 4:48a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Implement Runtime D3.
// [Files]         AcpiPlatform.c, AcpiPlatform.cif, AcpiPlatform.h,
// AcpiPlatform.sd, AcpiPlatform.sdl, AcpiPlatform.uni, GlobalNvsArea.h,
// SsdtRtd3.cif, SsdtRtd3.mak, Ult0Rtd3.asl, SsdtRtd3.sdl
// 
// 1     2/09/12 12:30a Yurenlai
// Initial check in.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        AcpiPlatform.h
//
// Description: AcpiPlatform header file, define all the AcpiPlatform module
//              specific equates and structures in this file.
//
//<AMI_FHDR_END>
//*************************************************************************

#define EFI_MSR_IA32_PLATFORM_ID        0x17
#define EFI_MSR_IA32_CR_PIC_MSG_CONTROL 0x2e
#define EFI_MSR_CORE_THREAD_COUNT       0x35
#define EFI_MSR_IA32_FEATURE_CONTROL    0x3a

#define AML_NAME_OP           0x08
#define AML_EXT_OP            0x5b
#define AML_EXT_DEVICE_OP     0x82
#define AML_EXT_PROCESSOR_OP  0x83
#define AML_NOOP_OP           0xa3

#define PCH_SMBUS_ENABLE_PEC  0x1

//-jeff For EDK
// Common table header, this prefaces all ACPI tables, including FACS, but
// excluding the RSD PTR structure

#ifndef EFI_SIGNATURE_16
#define EFI_SIGNATURE_16(A, B)  ((A) | (B << 8))
#endif

#ifndef EFI_SIGNATURE_32
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))
#endif

//
// ACPI table information used to initialize tables.
//
#define EFI_ACPI_3_0_DEBUG_PORT_TABLE_SIGNATURE  EFI_SIGNATURE_32('D', 'B', 'G', 'P')
#define EFI_ACPI_DBGP_TABLE_REVISION         0x01
#define EFI_ACPI_OEM_DBGP_REVISION           0x00000000
#define EFI_ACPI_CREATOR_ID                   0x5446534D         // "MSFT"
#define EFI_ACPI_CREATOR_REVISION             0x00000005F

typedef struct {
  UINT32  Signature;
  UINT32  Length;
} EFI_ACPI_COMMON_HEADER;

typedef struct
{
    UINT32 Signature;
    UINT32 Length;
    UINT8  Revision;
    UINT8  Checksum;
    UINT8  OemId[6];
    UINT64 OemTableId;
    UINT32 OemRevision;
    UINT32 CreatorId;
    UINT32 CreatorRevision;
} EFI_ACPI_DESCRIPTION_HEADER;


#pragma pack(1)
typedef union _MSR_REGISTER {
  UINT64  Qword;

  struct _DWORDS {
    UINT32  Low;
    UINT32  High;
  } Dwords;

  struct _BYTES {
    UINT8 FirstByte;
    UINT8 SecondByte;
    UINT8 ThirdByte;
    UINT8 FouthByte;
    UINT8 FifthByte;
    UINT8 SixthByte;
    UINT8 SeventhByte;
    UINT8 EighthByte;
  } Bytes;

} MSR_REGISTER;

///
/// ACPI 2.0 Generic Address Space definition
///
typedef struct _EFI_ACPI_2_0_GENERIC_ADDRESS_STRUCTURE{
  UINT8   AddressSpaceId;
  UINT8   RegisterBitWidth;
  UINT8   RegisterBitOffset;
  UINT8   Reserved;
  UINT64  Address;
} EFI_ACPI_2_0_GENERIC_ADDRESS_STRUCTURE;

typedef struct {
  ACPI_HDR                                  Header;
  UINT8                                     InterfaceType;
  UINT8                                     Reserved_37[3];
  EFI_ACPI_2_0_GENERIC_ADDRESS_STRUCTURE    BaseAddress;
} EFI_ACPI_DEBUG_PORT_DESCRIPTION_TABLE;


#define PTID_FFS_TABLE_STORAGE_GUID \
     { 0x95DFCAE5, 0xBB28, 0x4d6b, 0xB1, 0xE2, 0x3A, 0xF3, 0xA6, 0xBF, 0x43, 0x4F }
#define RTD3_FFS_TABLE_GUID \
     { 0x7FFC3536, 0x0A8A, 0x448B, 0x95, 0xF4, 0x39, 0xF5, 0xB9, 0xF0, 0x9A, 0xDD }
#define ACPIDEBUG_FFS_TABLE_GUID \
     { 0x94AB6AED, 0x9719, 0x48ef, 0x83, 0x1C, 0x2E, 0x9C, 0x29, 0x75, 0x8C, 0x33 }
#define ZPODD_FFS_TABLE_GUID \
     { 0xE42A76A1, 0xD4B3, 0x4c26, 0xA1, 0xBB, 0x84, 0xA3, 0x50, 0x2A, 0x77, 0x9F }
#define INTELSENSORHUB_FFS_TABLE_GUID \
     { 0xA3201EEC, 0x1612, 0x4577, 0x89, 0x24, 0xCB, 0x32, 0xD5, 0x42, 0xD2, 0x2C }
#define IRMT_FFS_TABLE_STORAGE_GUID \
     { 0xCE2007C7, 0xB389, 0x49c5, 0x84, 0xE3, 0xDB, 0x36, 0xA1, 0xF0, 0x99, 0x3B }
#pragma pack()


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
