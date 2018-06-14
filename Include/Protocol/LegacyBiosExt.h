//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/LegacyBiosExt.h 37    1/10/14 12:17p Olegi $
//
// $Revision: 37 $
//
// $Date: 1/10/14 12:17p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Protocol/LegacyBiosExt.h $
// 
// 37    1/10/14 12:17p Olegi
// EIP149769: LegacyToEfi boot management
// Changed default setting, added new token to extend the functionality
// 
// 36    10/18/13 12:39p Olegi
// EIP139866
// Create interface to manage LegacyToEfi CSM feature
// 
// 35    10/07/13 10:22a Olegi
// [TAG]  		EIP138427
// [Category]  	New Feature
// [Description]  	Create interface to let OEM customers change CSM16
// variables
// [Files] csm.c, csm.h, csmlib.c, legacybiosext.h
// 
// 34    9/26/13 10:43a Olegi
// 
// 33    8/14/13 8:37a Olegi
// [TAG]  		EIP132753
// [Category]  	Improvement
// Legacy2Efi module support
// 
// 32    12/26/12 3:26p Olegi
// 
// 31    7/23/12 12:10p Olegi
// [TAG]  		EIP92416
// [Description]  	Testing request for Smbios (INT)a_4.6.5.1_SMBIOS_32
// label
// LegacyBiosExt protocol is rearranged to match the one used by the
// SMBIOS.
// 
// 30    12/23/11 2:14p Olegi
// [TAG]  		EIP78921
// [Category]  	Improvement
// [Description]  	CsmBlockIo should create device handle in BBS table
// 
// 29    3/15/11 3:50p Olegi
// [TAG]  		EIP55913
// [Category]  	Improvement
// [Description]  	Remove LastOpromAddress from EFI_COMPATIBILITY16_TABLE
// structure
// [Files]  		Csm.c LegacyBios.h LegacyBiosExt.h
// 
// 28    3/14/11 10:00a Olegi
// [TAG]  		EIP54942
// [Category]  	New Feature
// [Description]  	CLP support implementation
// [Files]  		CsmOprom.c LegacyBiosExt.h
// 
// 27    9/13/10 5:50p Vyacheslava
// Added ReverseThunkPtrOfs variable.
// 
// 26    8/18/10 5:25p Olegi
// added two fields to LEGACY16_TO_EFI_DATA_TABLE structure: offset of
// "$EFI" and offset of SMBIOS header. EIP42457
// 
// 25    7/27/10 2:14p Olegi
// Added ReverseThunkPtrOfs field to LEGACY16_TO_EFI_DATA_TABLE_STRUC
// structure. EIP39674.
// 
// 24    7/08/10 11:29a Olegi
// Added EFI_AMI_LEGACYBOOT_PROTOCOL_GUID definition.
// 
// 23    5/17/10 4:27p Olegi
// 
// 22    5/14/10 4:09p Olegi
// 
// 21    4/28/10 11:55a Olegi
// 
// 20    1/27/10 6:28p Olegi
// 
// 19    1/12/10 11:51a Olegi
// Copyright message updated.
// 
// 18    8/07/09 4:33p Olegi
// SD binary ID definition added.
// 
// 17    7/02/08 1:51p Olegi
// 
// 16    5/22/08 11:47a Olegi
// Added CSM16_OEM_BEFORE_CALL_BOOT_VECTOR definition.
// 
// 15    5/08/08 6:03p Olegi
// Added definition of OPROM_MULTIPLE_MODULEID
// 
// 14    1/31/08 6:09p Olegi
// Modifications in AllocateEbda API
// 
// 13    1/16/08 2:05p Olegi
// 
// 12    1/16/08 1:54p Olegi
// AllocateEbda interface is updated.
// 
// 9     12/03/07 4:01p Olegi
// Added   three new interface functions: UnlockShadow, LockShadow, and
// Get16BitFuncAddress.
// 
// 8     11/14/07 12:36p Olegi
// 
// 7     10/24/07 12:28p Olegi
// Function AllocateEbda added to LegacyBiosExt protocol.
// 
// 6     8/21/07 11:27a Olegi
// 
// 5     8/09/07 4:24p Olegi
// 
// 4     7/13/07 8:44a Olegi
// 
// 3     6/21/07 10:31a Olegi
// 
// 2     6/18/07 5:52p Olegi
// 
// 1     6/13/07 10:44a Olegi
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    LegacyBiosExt.h
//
// Description: AMI extensions to LegacyBios protocol
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LEGACY_BIOS_EXT_PROTOCOL_H__
#define __LEGACY_BIOS_EXT_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
//#include <EFI.h>
#include <Protocol\LegacyRegion.h>
#include <Protocol\LegacyBios.h>

#define EFI_LEGACY_BIOS_EXT_PROTOCOL_GUID            \
  { 0x8e008510, 0x9bb1, 0x457d, 0x9f, 0x70, 0x89, 0x7a, 0xba, 0x86, 0x5d, 0xb9 }

GUID_VARIABLE_DECLARATION(gEfiLegacyBiosExtProtocolGuid,EFI_LEGACY_BIOS_EXT_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#pragma pack (1)

typedef struct _EFI_LEGACY_BIOS_EXT_PROTOCOL EFI_LEGACY_BIOS_EXT_PROTOCOL;

//****************************************************************************
// Embedded Legacy ROM ID definitions
//****************************************************************************
#define CSM16_VENDORID      0
#define CSM16_DEVICEID      0
#define CSM16_AHCI_RT_DID   1
#define CSM16_USB_RT_DID    2
#define CSM16_PNP_RT_DID    3
#define CSM16_SD_BOOT_DID   4

//****************************************************************************
// OEM Module ID definitions. Note: use CSM16_VENDORID and CSM16_DEVICEID as
// vendor/device ID for these modules.
//****************************************************************************
#define CSM16_MODULEID      1
#define SERVICEROM_MODULEID 2
#define OEM_MODULEID        3

#define OPROM_MODULEID          0x20
#define OPROM_MULTIPLE_MODULEID (0xa0 << 8)

//****************************************************************************
//		CSM16 API equates
//****************************************************************************
#define CSM16_OEM_HW_RESET          1
#define CSM16_OEM_NMI               2
#define CSM16_SMBIOS_PNP            3
#define CSM16_OEM_AFTER_SWSMI       4
#define CSM16_OEM_BEFORE_SWSMI      5
#define CSM16_OEM_ON_BOOT_FAIL      6
#define CSM16_CSP_AHCI_ACCESSHBA    7
#define CSM16_OEM_BEFORE_CALL_BOOT_VECTOR    8
#define CSM16_OEM_PROBE_KBC         9
#define CSM16_OEM_VIRUS_WARNING     10
#define CSM16_OEM_SERIAL_ACCESS     11
#define CSM16_OEM_BEFORE_CALL_INT19 12
#define CSM16_OEM_TRY_NEXT_BOOT     14

#define MAX_OEM16_FUNC_NUM          14

typedef struct{
    UINT16 ModuleId, VendorId, DeviceId;
    UINT32 Size;
} OPROM_HEADER;

typedef struct {
    UINT16 ModuleId;
    UINT16 VendorId;
    UINT16 DeviceId;
} PARTIAL_OPROM_HEADER;


typedef EFI_STATUS (EFIAPI *EFI_AMICSM_GET_EMBEDDED_ROM) (
    IN UINT16 ModuleId,
    IN UINT16 VendorId,
    IN UINT16 DeviceId,
    OUT VOID **ImageStart,
    OUT UINTN *ImageSize
);

typedef EFI_STATUS (EFIAPI *EFI_AMICSM_GET_BBS_TABLE) (
    IN OUT BBS_TABLE **BbsTable,
    IN OUT UINT8 *BbsCount
);

typedef EFI_STATUS (EFIAPI *EFI_AMICSM_ADD_BBS_ENTRY) (
    IN BBS_TABLE *BbsEntry
);

typedef EFI_STATUS (EFIAPI *EFI_AMICSM_INSERT_BBS_ENTRY_AT) (
    IN EFI_LEGACY_BIOS_EXT_PROTOCOL *This,
    IN OUT BBS_TABLE *BbsEntry,
    IN OUT UINT8 *EntryNumber
);

typedef EFI_STATUS (EFIAPI *EFI_AMICSM_REMOVE_BBS_ENTRY_AT) (
    IN EFI_LEGACY_BIOS_EXT_PROTOCOL *This,
    IN UINT8 EntryNumber
);

typedef EFI_STATUS (EFIAPI *EFI_AMICSM_ALLOCATE_EBDA) (
    IN EFI_LEGACY_BIOS_EXT_PROTOCOL *This,
    IN UINT8    RequestedSizeKB,
    OUT UINT32  *NewEbdaAddress,
    OUT UINT32  *EbdaStartOffset
);

typedef EFI_STATUS (EFIAPI *EFI_AMICSM_UNLOCK_SHADOW) (
    IN UINT8    *Address,
    IN UINTN    Size,
    OUT UINT32  *LockUnlockAddr,
    OUT UINT32  *LockUnlockSize
);

typedef EFI_STATUS (EFIAPI *EFI_AMICSM_LOCK_SHADOW) (
    IN UINT32  LockAddr,
    IN UINT32  LockSize
);

typedef struct _LEGACY16_TO_EFI_DATA_TABLE_STRUC {
    UINT32 MiscInfoAddress;         // 32-bit address of misc_info variable
    UINT32 RtCmosByteAddress;       // 32-bit address of rt_cmos_byte variable
    UINT32 SmiFlashTableAddress;    // 32-bit address of RUN_CSEG:smiflash_table variable
    UINT16 CdrBevOffset;
    UINT16 CDROMSupportAPIOfs;
    UINT16 AddedPnpFunctionsOfs;
    UINT16 BaidRmdVectorCntOfs;
    UINT16 ReverseThunkPtrOfs;
    UINT16 ReverseThunkStackPtrOfs;
    UINT16 Compatibility16TableOfs;
    UINT16 SmbiosTableOfs;
    UINT16 StartOfFreeE000Ofs;
    UINT16 ReadjustHddPrioritiesOfs;
    UINT16 BootBufferPtrOfs;
} LEGACY16_TO_EFI_DATA_TABLE_STRUC;

typedef EFI_STATUS (*EFI_AMICSM_GET_16BIT_FUNC_ADDRESS)(UINT16 id, UINT32 *Addr);

typedef UINTN (*EFI_AMICSM_COPY_LEGACY_TABLE)(
    IN VOID *Table,
    IN UINT16 TableSize,
    IN UINT16 Alignment,
    IN UINT16 Csm16LocationAttribute
);

typedef EFI_STATUS (*EFI_AMICSM_INSTALL_ISA_ROM)(
    IN EFI_LEGACY_BIOS_EXT_PROTOCOL *This,
    IN UINTN    RomAddress
);

typedef EFI_STATUS (*EFI_AMICSM_GET_SHADOWRAM_ADDRESS)(
    IN OUT UINT32   *AddrMin,
    IN UINT32       AddrMax,
    IN UINT32       Size,
    IN UINT32       Alignment
);

//---------------------------------//
// CSM16_CONFIGURATION definitions //
//---------------------------------//-------------------------------------
typedef enum {
    Csm16FeatureGet,
    Csm16FeatureSet,
    Csm16FeatureReset
} CSM16_CONFIGURATION_ACTION;

typedef enum {
    Csm16HeadlessI19Retry,
    Csm16I13MbrWriteProtect,
    Csm16LegacyFree,
    Csm16ZipHddEmulation,
    Csm16NoUsbBoot,
    Csm16I19Trap,
    Csm16Flexboot,
    Csm16GA20,
    Csm16SkipGA20Deactivation,
    Csm16Nmi,
    Csm16CpuRealModeOnBoot,
    Csm16PS2,
    Csm16LegacyToEfi,
    Csm16LegacyToEfiPonr,
    Csm16FeatureMax
} CSM16_FEATURE;

typedef EFI_STATUS (*EFI_AMICSM16_CONFIGURATION) (
    IN CSM16_CONFIGURATION_ACTION ConfigAction,
    IN CSM16_FEATURE Param,
    OUT OPTIONAL UINT32 *Data
);

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:        EFI_LEGACY_BIOS_EXT_PROTOCOL
//
// Description: Extends LegacyBios protocol with the AMI implementation specific
//              CSM funcitons and data.
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _EFI_LEGACY_BIOS_EXT_PROTOCOL {
  EFI_AMICSM_GET_EMBEDDED_ROM GetEmbeddedRom;
  EFI_AMICSM_ADD_BBS_ENTRY AddBbsEntry;
  EFI_AMICSM_INSERT_BBS_ENTRY_AT InsertBbsEntryAt;
  EFI_AMICSM_REMOVE_BBS_ENTRY_AT RemoveBbsEntryAt;
  EFI_AMICSM_ALLOCATE_EBDA AllocateEbda;
  EFI_AMICSM_UNLOCK_SHADOW UnlockShadow;
  EFI_AMICSM_LOCK_SHADOW LockShadow;
  EFI_AMICSM_GET_16BIT_FUNC_ADDRESS Get16BitFuncAddress;
  EFI_AMICSM_COPY_LEGACY_TABLE CopyLegacyTable;
  EFI_AMICSM_INSTALL_ISA_ROM InstallIsaRom;
  EFI_AMICSM_GET_SHADOWRAM_ADDRESS GetShadowRamAddress;
  EFI_AMICSM_GET_BBS_TABLE GetBbsTable;
  EFI_AMICSM16_CONFIGURATION Csm16Configuration;
} EFI_LEGACY_BIOS_EXT_PROTOCOL;

// PCI Interrupt installation protocol

#define EFI_PCIIRQ_PGM_PROTOCOL_GUID \
  { 0x9400d59b, 0xe9c, 0x4f6c, 0xb5, 0x9a, 0xfc, 0x20, 0x0, 0x9d, 0xb9, 0xec };

typedef struct {
    VOID    *PciIo;
    UINT8   Irq;
} PROGRAMMED_PCIIRQ_CTX;

#define EFI_AMI_LEGACYBOOT_PROTOCOL_GUID            \
  {0x120d28aa, 0x6630, 0x46f0, 0x81, 0x57, 0xc0, 0xad, 0xc2, 0x38, 0x3b, 0xf5};

VOID SignalAmiLegacyBootEvent(VOID);

// CLP support related definitions

// The following PCIR data structure is the extended version of PCI_DATA_STRUCTURE
// from PCI.H. It can be removed once PCI header file is generically updated.
typedef struct {
    UINT32          Signature;
    UINT16          VendorId;
    UINT16          DeviceId;
    UINT16          Reserved0;
    UINT16          Length;
    UINT8           Revision;
    UINT8           ClassCode[3];
    UINT16          ImageLength;
    UINT16          CodeRevision;
    UINT8           CodeType;
    UINT8           Indicator;
    UINT16          MaxRtImageLength;
    UINT16          CfgUtilPointer;
    UINT16          ClpEntryPoint;
} PCI_PCIR30_DATA_STRUCTURE;

#define EFI_CLP_PROTOCOL_GUID \
    {0xcbbee336, 0x2682, 0x4cd6, 0x81, 0x8b, 0xa, 0xd, 0x96, 0x7e, 0x5a, 0x67};

typedef struct _EFI_CLP_PROTOCOL EFI_CLP_PROTOCOL;

typedef EFI_STATUS (*EFI_CLP_EXECUTE) (
    IN EFI_CLP_PROTOCOL *This,
    IN UINT8            *CmdInputLine,
    IN UINT8            *CmdResponseBuffer,
    OUT UINT32          *CmdStatus
);

typedef struct _EFI_CLP_PROTOCOL {
    EFI_HANDLE      Handle;
    UINT16          EntrySeg;
    UINT16          EntryOfs;
    EFI_CLP_EXECUTE Execute;
} EFI_CLP_PROTOCOL;

#pragma pack ()

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
