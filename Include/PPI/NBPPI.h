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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB PPI/NBPPI.h 6     4/08/13 8:13a Ireneyang $
//
// $Revision: 6 $
//
// $Date: 4/08/13 8:13a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB PPI/NBPPI.h $
// 
// 6     4/08/13 8:13a Ireneyang
// Update SA RC to 1.4.0.0.
// 
// 5     4/08/13 7:22a Ireneyang
// Update SA RC to 1.4.0.0.
//
// 4     4/01/13 11:49p Ireneyang
// [TAG]          None
// [Severity]     Improvement
// [Description]  Reduce boot time through PEG.
// [Files]        NB.mak; NBDxe.c; NBPEI.c; NBPPI.h; Sa.asl;
//                PcieComplex.c; GraphicsInit.c; PciExpressInit.c;
// 
// 3     12/03/12 5:53a Jeffch
// [TAG]           None
// [Category]      Improvement
// [Description]   optimize DetectNonComplaint function.
// [Description]   NBPEI.c, NBPPI.h, NBDxe.c
// 
// 2     6/14/12 4:29a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Add Notify BeforeMrc and AfterMrc.
// [Description]   NBPEI.c, NBPPI.h, MemoryInit.c
// 
// 1     2/08/12 4:35a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBPPI.h
//
// Description: This header file contains the PPI definition for the NB.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef FILE_PEI_NBINIT_POLICY_PPI_H_
#define FILE_PEI_NBINIT_POLICY_PPI_H_

#include "HOB.h"

// {9CE4D938-9C87-41d0-9E55-34923FAF8B4F}
#define AMI_PEI_NBINIT_POLICY_PPI_GUID \
 {0x9ce4d938, 0x9c87, 0x41d0, 0x9e, 0x55, 0x34, 0x92, 0x3f, 0xaf, 0x8b, 0x4f}

// {E813E116-C099-4D21-9c34-A552D5E9A5D0}
#define AMI_PEI_MRC_DEFAULT_GUID \
 {0xe813e116, 0xc099, 0x4d21, 0x9c, 0x34, 0xa5, 0x52, 0xd5, 0xe9, 0xa5, 0xd0}

// {71A8917B-0891-4E27-8A73-A9B334840393}
#define AMI_PEI_BEFORE_MRC_GUID \
 {0x71a8917b, 0x891, 0x4e27, 0x8a, 0x73, 0xa9, 0xb3, 0x34, 0x84, 0x3, 0x93}

// {64C96700-6B4C-480C-A3E1-B8BDE8F602B2}
#define AMI_PEI_AFTER_MRC_GUID \
 {0x64c96700, 0x6b4c, 0x480c, 0xa3, 0xe1, 0xb8, 0xbd, 0xe8, 0xf6, 0x2, 0xb2}

// {633194BE-1697-11E1-B5F0-2CB24824019B}
#define AMI_PEI_END_OF_MRC_GUID \
 {0x633194be, 0x1697, 0x11e1, 0xb5, 0xf0, 0x2c, 0xb2, 0x48, 0x24, 0x01, 0x9b}

// {9F58E424-B96B-45A5-ADDC-D2FE394A99D9}
#define AMI_PEI_END_MEMORY_DETECT_GUID \
 {0x9f58e424, 0xb96b, 0x45a5, 0xad, 0xdc, 0xd2, 0xfe, 0x39, 0x4a, 0x99, 0xd9}

// {584CC99F-4BE8-43d1-A45A-933DC39479FC}
#define AMI_PEI_SET_NB_SUBID_PPI_GUID \
 {0x584cc99f, 0x4be8, 0x43d1, 0xa4, 0x5a, 0x93, 0x3d, 0xc3, 0x94, 0x79, 0xfc}

// {1F0F049E-3A68-4c97-865A-BC5EED7920E7}
#define AMI_PEI_NB_CPU_ONLY_RESET_PPI_GUID \
 {0x1f0f049e, 0x3a68, 0x4c97, 0x86, 0x5a, 0xbc, 0x5e, 0xed, 0x79, 0x20, 0xe7}

// {584CC99F-4BE8-43d1-A45A-933DC39479FC}
#define AMI_PEI_NB_CUSTOM_PPI_GUID \
 {0x584cc99f, 0x4be8, 0x43d1, 0xa4, 0x5a, 0x93, 0x3d, 0xc3, 0x94, 0x79, 0xfc}

//-MrcErrorInfo Example 
#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif
//-MrcErrorInfo Example end
GUID_VARIABLE_DECLARATION(gAmiPeiNBCustomPpiGuid, AMI_PEI_NB_CUSTOM_PPI_GUID);

#define PEI_MEMORY_RANGE_OPTION_ROM         UINT32

#define PEI_MR_OPTION_ROM_ALL               0xFFFFFFFF
#define PEI_MR_OPTION_ROM_NONE              0x00000000
#define PEI_MR_OPTION_ROM_C0000_16K         0x00000001
#define PEI_MR_OPTION_ROM_C4000_16K         0x00000002
#define PEI_MR_OPTION_ROM_C8000_16K         0x00000004
#define PEI_MR_OPTION_ROM_CC000_16K         0x00000008
#define PEI_MR_OPTION_ROM_D0000_16K         0x00000010
#define PEI_MR_OPTION_ROM_D4000_16K         0x00000020
#define PEI_MR_OPTION_ROM_D8000_16K         0x00000040
#define PEI_MR_OPTION_ROM_DC000_16K         0x00000080
#define PEI_MR_OPTION_ROM_E0000_16K         0x00000100
#define PEI_MR_OPTION_ROM_E4000_16K         0x00000200
#define PEI_MR_OPTION_ROM_E8000_16K         0x00000400
#define PEI_MR_OPTION_ROM_EC000_16K         0x00000800
#define PEI_MR_OPTION_ROM_F0000_16K         0x00001000
#define PEI_MR_OPTION_ROM_F4000_16K         0x00002000
#define PEI_MR_OPTION_ROM_F8000_16K         0x00004000
#define PEI_MR_OPTION_ROM_FC000_16K         0x00008000

//
// SMRAM Memory Range
//
#define PEI_MEMORY_RANGE_SMRAM              UINT32
#define PEI_MR_SMRAM_ALL                    0xFFFFFFFF
#define PEI_MR_SMRAM_NONE                   0x00000000
#define PEI_MR_SMRAM_CACHEABLE_MASK         0x80000000
#define PEI_MR_SMRAM_SEGTYPE_MASK           0x00FF0000
#define PEI_MR_SMRAM_ABSEG_MASK             0x00010000
#define PEI_MR_SMRAM_HSEG_MASK              0x00020000
#define PEI_MR_SMRAM_TSEG_MASK              0x00040000
//
// If adding additional entries, SMRAM Size
// is a multiple of 128KB. 
//
#define PEI_MR_SMRAM_SIZE_MASK              0x0000FFFF
#define PEI_MR_SMRAM_SIZE_128K_MASK         0x00000001
#define PEI_MR_SMRAM_SIZE_256K_MASK         0x00000002
#define PEI_MR_SMRAM_SIZE_512K_MASK         0x00000004
#define PEI_MR_SMRAM_SIZE_1024K_MASK        0x00000008
#define PEI_MR_SMRAM_SIZE_2048K_MASK        0x00000010
#define PEI_MR_SMRAM_SIZE_4096K_MASK        0x00000020
#define PEI_MR_SMRAM_SIZE_8192K_MASK        0x00000040


#define PEI_MR_SMRAM_ABSEG_128K_NOCACHE     0x00010001
#define PEI_MR_SMRAM_HSEG_128K_CACHE        0x80020001
#define PEI_MR_SMRAM_HSEG_128K_NOCACHE      0x00020001
#define PEI_MR_SMRAM_TSEG_128K_CACHE        0x80040001
#define PEI_MR_SMRAM_TSEG_128K_NOCACHE      0x00040001
#define PEI_MR_SMRAM_TSEG_256K_CACHE        0x80040002
#define PEI_MR_SMRAM_TSEG_256K_NOCACHE      0x00040002
#define PEI_MR_SMRAM_TSEG_512K_CACHE        0x80040004
#define PEI_MR_SMRAM_TSEG_512K_NOCACHE      0x00040004
#define PEI_MR_SMRAM_TSEG_1024K_CACHE       0x80040008
#define PEI_MR_SMRAM_TSEG_1024K_NOCACHE     0x00040008
#define PEI_MR_SMRAM_TSEG_8192K_CACHE       0x80040040
#define PEI_MR_SMRAM_TSEG_8192K_NOCACHE     0x00040040

//
// Graphics Memory Range
//
#define PEI_MEMORY_RANGE_GRAPHICS_MEMORY    UINT32
#define PEI_MR_GRAPHICS_MEMORY_ALL          0xFFFFFFFF
#define PEI_MR_GRAPHICS_MEMORY_NONE         0x00000000
#define PEI_MR_GRAPHICS_MEMORY_CACHEABLE    0x80000000
//
// If adding additional entries, Graphics Memory Size
// is a multiple of 512KB. 
//
#define PEI_MR_GRAPHICS_MEMORY_SIZE_MASK    0x0000FFFF
#define PEI_MR_GRAPHICS_MEMORY_512K_NOCACHE 0x00000001
#define PEI_MR_GRAPHICS_MEMORY_512K_CACHE   0x80000001
#define PEI_MR_GRAPHICS_MEMORY_1M_NOCACHE   0x00000002
#define PEI_MR_GRAPHICS_MEMORY_1M_CACHE     0x80000002
#define PEI_MR_GRAPHICS_MEMORY_2M_NOCACHE   0x00000004
#define PEI_MR_GRAPHICS_MEMORY_2M_CACHE     0x80000004
#define PEI_MR_GRAPHICS_MEMORY_4M_NOCACHE   0x00000008
#define PEI_MR_GRAPHICS_MEMORY_4M_CACHE     0x80000008
#define PEI_MR_GRAPHICS_MEMORY_8M_NOCACHE   0x00000010
#define PEI_MR_GRAPHICS_MEMORY_8M_CACHE     0x80000010
#define PEI_MR_GRAPHICS_MEMORY_16M_NOCACHE  0x00000020
#define PEI_MR_GRAPHICS_MEMORY_16M_CACHE    0x80000020
#define PEI_MR_GRAPHICS_MEMORY_32M_NOCACHE  0x00000040
#define PEI_MR_GRAPHICS_MEMORY_32M_CACHE    0x80000040
#define PEI_MR_GRAPHICS_MEMORY_48M_NOCACHE  0x00000060
#define PEI_MR_GRAPHICS_MEMORY_48M_CACHE    0x80000060
#define PEI_MR_GRAPHICS_MEMORY_64M_NOCACHE  0x00000080
#define PEI_MR_GRAPHICS_MEMORY_64M_CACHE    0x80000080
#define PEI_MR_GRAPHICS_MEMORY_96M_NOCACHE  0x000000C0
#define PEI_MR_GRAPHICS_MEMORY_96M_CACHE    0x800000C0
#define PEI_MR_GRAPHICS_MEMORY_128M_NOCACHE 0x00000100
#define PEI_MR_GRAPHICS_MEMORY_128M_CACHE   0x80000100
#define PEI_MR_GRAPHICS_MEMORY_256M_NOCACHE 0x00000200
#define PEI_MR_GRAPHICS_MEMORY_256M_CACHE   0x80000200
#define PEI_MR_GRAPHICS_MEMORY_96M_NOCACHE  0x000000C0
#define PEI_MR_GRAPHICS_MEMORY_96M_CACHE    0x800000C0
#define PEI_MR_GRAPHICS_MEMORY_160M_NOCACHE 0x00000140
#define PEI_MR_GRAPHICS_MEMORY_160M_CACHE   0x80000140
#define PEI_MR_GRAPHICS_MEMORY_192M_NOCACHE 0x00000180
#define PEI_MR_GRAPHICS_MEMORY_192M_CACHE   0x80000180
#define PEI_MR_GRAPHICS_MEMORY_224M_NOCACHE 0x000001C0
#define PEI_MR_GRAPHICS_MEMORY_224M_CACHE   0x800001C0
#define PEI_MR_GRAPHICS_MEMORY_256M_NOCACHE 0x00000200
#define PEI_MR_GRAPHICS_MEMORY_256M_CACHE   0x80000200
#define PEI_MR_GRAPHICS_MEMORY_288M_NOCACHE 0x00000240
#define PEI_MR_GRAPHICS_MEMORY_288M_CACHE   0x80000240
#define PEI_MR_GRAPHICS_MEMORY_320M_NOCACHE 0x00000280
#define PEI_MR_GRAPHICS_MEMORY_320M_CACHE   0x80000280
#define PEI_MR_GRAPHICS_MEMORY_352M_NOCACHE 0x000002C0
#define PEI_MR_GRAPHICS_MEMORY_352M_CACHE   0x800002C0
#define PEI_MR_GRAPHICS_MEMORY_384M_NOCACHE 0x00000300
#define PEI_MR_GRAPHICS_MEMORY_384M_CACHE   0x80000300
#define PEI_MR_GRAPHICS_MEMORY_416M_NOCACHE 0x00000340
#define PEI_MR_GRAPHICS_MEMORY_416M_CACHE   0x80000340
#define PEI_MR_GRAPHICS_MEMORY_448M_NOCACHE 0x00000380
#define PEI_MR_GRAPHICS_MEMORY_448M_CACHE   0x80000380
#define PEI_MR_GRAPHICS_MEMORY_480M_NOCACHE 0x000003C0
#define PEI_MR_GRAPHICS_MEMORY_480M_CACHE   0x800003C0
#define PEI_MR_GRAPHICS_MEMORY_512M_NOCACHE 0x00000400
#define PEI_MR_GRAPHICS_MEMORY_512M_CACHE   0x80000400

//
// Pci Memory Hole
//
#define PEI_MEMORY_RANGE_PCI_MEMORY              UINT32
#define PEI_MR_PCI_MEMORY_SIZE_512M_MASK         0x00000001


GUID_VARIABLE_DECLARATION(gAmiPeiMrcDefaultGuid, AMI_PEI_MRC_DEFAULT_GUID);
GUID_VARIABLE_DECLARATION(gAmiPeiBeforeMrcGuid, AMI_PEI_BEFORE_MRC_GUID);
GUID_VARIABLE_DECLARATION(gAmiPeiAfterMrcGuid, AMI_PEI_AFTER_MRC_GUID);
GUID_VARIABLE_DECLARATION(gAmiPeiEndOfMemDetectGuid, AMI_PEI_END_OF_MRC_GUID);
GUID_VARIABLE_DECLARATION(gSetNBSubIdPpiGuid, AMI_PEI_SET_NB_SUBID_PPI_GUID);
GUID_VARIABLE_DECLARATION(gAmiPeiNBCpuOnlyResetPpiGuid, \
                                         AMI_PEI_NB_CPU_ONLY_RESET_PPI_GUID);

typedef struct _AMI_PEI_NBINIT_POLICY_PPI   AMI_PEI_NBINIT_POLICY_PPI;

typedef struct _AMI_PEI_NBINIT_POLICY_PPI {
    UINTN                       unFlag;
} AMI_PEI_NBINIT_POLICY_PPI;

#define AMI_MRC_INFO_HOB_GUID \
 {0xa6351a87, 0x2965, 0x4718, 0x88, 0xc7, 0x0b, 0x5b, 0x5a, 0xc0, 0xb5, 0xe4}

#define AMI_NB_MRC_INFO_GUID \
 {0x6737934b, 0xa27e, 0x4c05, 0xad, 0x5b, 0x6a, 0xb8, 0x62, 0x73, 0x68, 0x0b}

//85226559-0def-48d8-a8c9-b746d6a4df01
#define AMI_MEMORY_ERROR_REPORT_PPI_GUID \
  { 0x85226559, 0x0def, 0x48d8, 0xa8, 0xc9, 0xb7, 0x46, 0xd6, 0xa4, 0xdf, 0x01 }

// {7D971640-6815-408a-AC4F-BCB7A3BD9336}
#define AMI_NB_PEG_INFO_GUID \
  { 0x7d971640, 0x6815, 0x408a, 0xac, 0x4f, 0xbc, 0xb7, 0xa3, 0xbd, 0x93, 0x36 }

// {E1E2A446-0365-4c65-919C-0371C3F9F5FF}
#define AMI_NB_PEG_GEN3_PRESET_SEARCH_GUID \
  { 0xe1e2a446, 0x365, 0x4c65,  0x91, 0x9c, 0x03, 0x71, 0xc3, 0xf9, 0xf5, 0xff }


#define NB_MRC_INFO_VARIABLE L"NBMrcInfo"

typedef struct  _EFI_PEI_SET_NB_SID_PPI     EFI_PEI_SET_NB_SID_PPI;

typedef EFI_STATUS (EFIAPI *EFI_PEI_NB_SUBID_SET) (
    IN EFI_PEI_SERVICES         **PeiServices
);

typedef struct _EFI_PEI_SET_NB_SID_PPI {
    EFI_PEI_NB_SUBID_SET        PeiSetNBSubId;
} EFI_PEI_SET_NB_SID_PPI;

typedef struct _EFI_PEI_NB_CPU_ONLY_RESET_PPI  EFI_PEI_NB_CPU_ONLY_RESET_PPI;

typedef VOID (EFIAPI *EFI_PEI_NB_CPU_ONLY_RESET) (
    IN EFI_PEI_SERVICES         **PeiServices
);

typedef
EFI_STATUS
(EFIAPI *PEI_AMI_MEMORY_ERROR_READ) (
  IN      EFI_PEI_SERVICES                      **PeiServices,  ///< Pointer to PeiServices
  IN struct _PEI_MEMORY_ERROR_REPORT_PPI        *This,          ///< Pointer to the PPI structure
  IN OUT  UINT32                                MemErrData     ///< Memory Error Data Buffer
);

typedef struct _EFI_PEI_NB_CPU_ONLY_RESET_PPI {
    EFI_PEI_NB_CPU_ONLY_RESET   GenerateCpuOnlyReset;
} EFI_PEI_NB_CPU_ONLY_RESET_PPI;

typedef enum {
    FreqAuto = 0,
    Freq800  = 800,
    Freq1067 = 1067,
    Freq1333 = 1333,
    Freq1600 = 1600,
    Freq1867 = 1867,
    Freq2133 = 2133,
    FreqUnSupport
} MemFrequency;


// Porting Request.
typedef struct {
    UINT32  dRegEBP;
    UINT32  dRegEBX;
    UINT16  wMmioSSKPD;
    UINT8   bMmioC0DRT1;
    UINT8   bMmioC1DRT1;
    UINT8   bRCVENMT;
    UINT32  dMmioC0REOST;
    UINT32  dMmioC1REOST;
} NB_MRC_INFO;

typedef struct {
    EFI_HOB_GUID_TYPE       Guid;
    NB_MRC_INFO             pMrcInfo;
} MRC_INFO_HOB;

typedef struct {
    EFI_HOB_GUID_TYPE       Guid;
    UINT8		    tCKminMTBUnits;
} MRC_DEFAULT_HOB;

#ifndef _PEI_HOB_H_
#ifndef __HOB__H__
typedef struct _EFI_HOB_GENERIC_HEADER {
  UINT16  HobType;
  UINT16  HobLength;
  UINT32  Reserved;
} EFI_HOB_GENERIC_HEADER;

typedef struct _EFI_HOB_GUID_TYPE {
  EFI_HOB_GENERIC_HEADER  Header;
  EFI_GUID                Name;
} EFI_HOB_GUID_TYPE;
#endif
#endif

typedef struct {
  EFI_HOB_GUID_TYPE Header;
  UINT8             PegDeOverride[3];
} NB_PEG_INFO_HOB;

typedef struct _AMI_NB_PCI_SSID_TABLE_STRUCT AMI_NB_PCI_SSID_TABLE_STRUCT;

typedef struct _AMI_NB_PCI_SSID_TABLE_STRUCT {
    UINT64                      PciAddr;
    UINT32                      Sid;
} AMI_NB_PCI_SSID_TABLE_STRUCT;

typedef struct _AMI_NB_PCH_SKU_DEVICE_ID_TABLE_STRUCT {
    UINT16                      VenderID;
    UINT16                      DeviceID;
} AMI_NB_PCH_SKU_DEVICE_ID_TABLE_STRUCT;

typedef struct _AMI_PEI_NB_CUSTOM_PPI       AMI_PEI_NB_CUSTOM_PPI;

typedef struct _AMI_PEI_NB_CUSTOM_PPI {
    AMI_NB_PCI_SSID_TABLE_STRUCT *SsidTable;
} AMI_PEI_NB_CUSTOM_PPI;

typedef struct _PEI_MEMORY_ERROR_REPORT_PPI {
    PEI_AMI_MEMORY_ERROR_READ           AmiMemoryErrorRead;
} PEI_MEMORY_ERROR_REPORT_PPI;

#endif

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
