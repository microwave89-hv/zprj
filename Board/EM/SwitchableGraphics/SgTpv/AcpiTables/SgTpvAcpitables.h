//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvAcpitables.h 6     6/05/13 5:08a Joshchou $
//
// $Revision: 6 $
//
// $Date: 6/05/13 5:08a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvAcpitables.h $
// 
// 6     6/05/13 5:08a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Increase the size of RBUF to support hybrid Vbios.
// 
// 5     1/15/13 6:07a Joshchou
// [TAG]  		EIP107237
// [Category]  	Improvement
// [Description]  	Modify for support SG on ULT plaform
// 
// 4     12/18/12 6:22a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update for SA RC 081
// 
// 3     10/16/12 4:41a Joshchou
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update for SA and ACPI RC 0.7.1
// [Files]  		SgTpvAcpitables.h
// 
// 2     9/09/12 10:57p Joshchou
// 
//**********************************************************************

#ifndef _SG_TPV_ACPITABLES_H_
#define _SG_TPV_ACPITABLES_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "EfiScriptLib.h"
#endif

#include "Acpi3_0.h"
#include <Token.h>
#include <Protocol\Mxm30.h>

#include "CpuRegs.h"
#include "CpuPlatformLib.h"

//#include EFI_PROTOCOL_DEPENDENCY (PciIo)
#include EFI_PROTOCOL_DEPENDENCY (AcpiSupport)
#include EFI_PROTOCOL_DEPENDENCY (FirmwareVolume)
#include EFI_PROTOCOL_DEPENDENCY (SaGlobalNvsArea)
#include EFI_GUID_DEFINITION (SaDataHob)
#include EFI_PROTOCOL_DEFINITION (SaPlatformPolicy)

#define MemoryRead16(Address)   * (UINT16 *) (Address)
#define MemoryRead8(Address)    * (UINT8 *) (Address)

extern EFI_BOOT_SERVICES    *gBS;
extern EFI_GUID             gSaGlobalNvsAreaProtocolGuid;
extern VOID                 *VbiosAddress;
extern UINT32               VbiosSize;
extern UINT8                EndpointBus;
extern UINT16               GpioBaseAddress;

extern CPU_FAMILY CpuFamilyId;

SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL  *SaGlobalNvsArea;

// Function Prototype declaration
EFI_STATUS LoadTpvAcpiTables();
EFI_STATUS InstallNvidiaOpRegion (VOID);
EFI_STATUS InstallAmdOpRegion (VOID);

//----------------------------------------------------------------------------
//
// Switchable Graphics defines.
//
//----------------------------------------------------------------------------

//
// SSDT Guid file
//
#define NVIDIA_VID              0x10DE
#define NVOPT_SSID_OFFSET       0x40

#define AMD_SVID_OFFSET         0x4C
#define AMD_SDID_OFFSET         0x4E
#define AMD_VID                 0x1002

//
// OpRegion Header #defines.
//
#define NVIG_HEADER_SIGNATURE    "NVSG-IGD-DSM-VAR"
#define NVIG_OPREGION_SIZE       1
#define NVIG_OPREGION_VER        0x00000201
#define NVHM_HEADER_SIGNATURE    "NvSwitchable_Gfx"
#define NVHM_OPREGION_SIZE       129
#define NVHM_OPREGION_VER        0x00000201
#define APXM_HEADER_SIGNATURE    "AMD--PowerXpress"
#define APXM_OPREGION_SIZE       129
#define APXM_OPREGION_VER        0x00000201

//
// OpRegion structures:
//
// Note: These structures are packed to 1 byte offsets because the exact
// data location is requred by the supporting design specification due to
// the fact that the data is used by ASL and Graphics driver code compiled
// separatly.
//

//
// NVIG OpRegion
//
#pragma pack (1)
typedef struct {
  // OpRegion Header             // Byte offset(decimal)

  CHAR8   NISG[0x10];            // 0            NVIG OpRegion Signature
  UINT32  NISZ;                  // 16           NVIG OpRegion Size in KB
  UINT32  NIVR;                  // 20           NVIG OpRegion Version

  // OpRegion Data
  UINT32  GPSS;                  // 24           Policy Selection Switch Status (Current GPU)
  UINT16  GACD;                  // 32           Active Displays
  UINT16  GATD;                  // 34           Attached Displays
  CHAR8   LDES;                  // 36           Lid Event State
  CHAR8   DKST;                  // 37           Dock State
  CHAR8   DACE;                  // 38           Display ACPI Event
  CHAR8   DHPE;                  // 39           Display Hot-Plug Event
  CHAR8   DHPS;                  // 40           Display Hot-Plug Status
  CHAR8   SGNC;                  // 41           Notify Code (Cause of Notify(..,0xD0))
  CHAR8   GPPO;                  // 42           Policy Override
  CHAR8   USPM;                  // 43           Update Scaling Preference Mask
  CHAR8   GPSP;                  // 44           Panel Scaling Preference
  CHAR8   TLSN;                  // 45           Toggle List Sequence Number
  CHAR8   DOSF;                  // 46           Flag for _DOS
  UINT16  ELCL;                  // 47           Endpoint Link Contol Register Value

} NVIG_OPREGION;                 // Total 49  Bytes
#pragma pack ()

//
// NVHM OpRegion
//
#pragma pack (1)
typedef struct {
  // OpRegion Header             // Byte offset(decimal)

  CHAR8   NVSG[0x10];            // 0            NVHM OpRegion Signature
  UINT32  NVSZ;                  // 16           NVHM OpRegion Size in KB
  UINT32  NVVR;                  // 20           NVHM OpRegion Version

  // OpRegion Data
  UINT32  NVHO;                  // 24           NVHM Opregion Address
  UINT32  RVBS;                  // 28           Nvidia VBIOS Image Size
  CHAR8   RBUF[0x20000];         // 32           64KB VBIOS
  UINT32  MXML;                  // 64k+32       Nvidia Mxm3 Buffer length
#if MXM30_SUPPORT == 1
  CHAR8   MXM3[MXM_ROM_MAX_SIZE];// 64k+36       Nvidia Mxm3 Buffer
#else
  CHAR8   MXM3[200];
#endif
} NVHM_OPREGION;                 // Total 65568 Bytes
#pragma pack ()

//
// Entire Nvidia OpRegion
//
#pragma pack(1)
typedef struct {
  NVIG_OPREGION          *NvIgOpRegion;                 // 47  Bytes   
  NVHM_OPREGION          *NvHmOpRegion;                 // 65568 Bytes
} NVIDIA_OPREGION;                                      // Total 65615 Bytes
#pragma pack()

//
// APXM OpRegion
//
#pragma pack (1)
typedef struct {
  // OpRegion Header        // Byte offset(decimal)
                
  CHAR8   APSG[0x10];       // 0            APXM OpRegion Signature
  UINT32  APSZ;             // 16           APXM OpRegion Size in KB
  UINT32  APVR;             // 20           APXM OpRegion Version

  // OpRegion Data
  UINT32  APXA;             // 24           PX OpRegion Address
  UINT32  RVBS;             // 28           PX Runtime VBIOS Image Size
  UINT16  NTLE;             // 32           Total number of toggle list entries
  UINT16  TLEX[15];         // 34           The display combinations in the list...
  UINT16  TGXA;             // 64           Target GFX adapter as notified by ATPX function 5
  UINT16  AGXA;             // 66           Active GFX adapter as notified by ATPX function 6
  CHAR8   GSTP;             // 68           GPU switch transition in progress
  CHAR8   DSWR;             // 69           Display Switch Request
  CHAR8   SPSR;             // 70           System power source change request
  CHAR8   DCFR;             // 71           Display configuration change request
  CHAR8   EMDR;             // 72           Expansion Mode Change Request
  CHAR8   PXGS;             // 73           PowerXpress graphics switch toggle request
  UINT16  CACD;             // 74           Currently Active Displays
  UINT16  CCND;             // 76           Currently Connected Displays
  UINT16  NACD;             // 78           Next Active Index
  CHAR8   EXPM;             // 80           Expansion Mode
  UINT16  TLSN;             // 81           Toggle list sequence index
  UINT16  ELCL;             // 83           Endpoint Link Contol Register Value

  CHAR8   RBUF[0x20000];    // 83           VBIOS 128KB
} APXM_OPREGION;            // Total 65626   Bytes
#pragma pack ()

//
// Entire AMD OpRegion
//
#pragma pack (1)
typedef struct {
 APXM_OPREGION                          *ApXmOpRegion;                // Total 65617   Bytes
} AMD_OPREGION;
#pragma pack ()

#endif

//**********************************************************************
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
