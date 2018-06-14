//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/AHCI/INT13/AInt13.h 17    11/25/14 12:00a Kapilporwal $
//
// $Revision: 17 $
//
// $Date: 11/25/14 12:00a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/INT13/AInt13.h $
// 
// 17    11/25/14 12:00a Kapilporwal
// [TAG]  		EIP191939
// [Category]  	Improvement
// [Description]  	Issue about BIG_REAL_MODE_MMIO_ACCESS of AHCI module
// [Files]  		AI13.bin
// AHCIACC.ASM
// AhciInt13Dxe.c
// AhciInt13Dxe.dxs
// AhciInt13Smm.c
// AhciInt13Smm.cif
// AhciInt13Smm.dxs
// AhciInt13Smm.h
// AhciInt13Smm.mak
// AhciInt13Smm.sdl
// AInt13.c
// Aint13.cif
// AInt13.h
// AhciSmm.c
// AhciSmm.h
// AhciSmmProtocol.h
// 
// 16    11/29/12 12:58a Rameshr
// [TAG]  		EIP107365
// [Category]  	Improvement
// [Description]  	Increase the SATA_PORT_COUNT  to 32 to support 32 SATA
// devices on Legacyboot
// [Files]  		Aint13.h, Ahci.sdl ( Ain13.bin)
// 
// 15    8/02/12 8:12a Deepthins
// [TAG]  		EIP93480
// [Category]  	Bug Fix
// [Symptom]  	AHCI legacy support module is corrupting the memory.
// [RootCause]  	AHCI legacy support module is corrupting the memory as it
// was using wrong offset for storing the base address.
// [Solution]  	Properly calculating offset for storing the base address.
// [Files]  		AINT13.EQU, AInt13.c, AInt13.h and AHCIACC.ASM
// 
// 14    7/20/12 6:12a Anandakrishnanl
// [TAG]  		EIP88683
// [Category]  	New Feature
// [Description]  	EFI_ATA_PASS_THRU_PROTOCOL Support for Aptio IDE
// [Files]  		AhciBus.c
// AhciBus.h
// AInt13.h
// IdeBus.c
// IdeBus.h
// PIDEBus.h
// PAhciBus.h
// AtaPassThru.sdl
// AtaPassThru.mak	
// AtaPassThru.c	
// AtaPassThruSupport.h
// AtaPassThru.chm
// 
// 13    4/24/12 12:54a Deepthins
// [TAG]  		EIP86336
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Can't boot from AHCI if SATA_PORT_COUNT=12
// [RootCause]  	The controller number was not updated in DEV_INFO_STRUC
// for all the Hard Disk
// [Solution]  	Updated the controller number in the DEV_INFO_STRUC for
// all the AHCI devices.
// [Files]  		AInt13.c, AInt13.h
// 
// 12    1/13/12 12:18a Deepthins
// [TAG]  		EIP78099
// [Category]  	Improvement
// [Description]  	Handle multiple AHCI controller in legacy.
// [Files]  		Aint13.sdl , AInt13.c , AInt13.h , AHCIACC.ASM , AHCI.EQU ,
// AINT13.bin (AHCIACC.ASM , AINT13.EQU)
// 
// 11    11/29/11 4:27a Rameshr
// [TAG]  		EIP76393
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Any time AHCI is starting when EBDA size is more than 64K,
// the problem will show as memory corruption.
// [RootCause]  	AHCI INT13 code does not use EBDA properly when at the
// time of EBDA allocation current size of EBDA exceeds 64K
// [Solution]  	Modified code to extend the width of EbdaStart offset from
// 16-bit to 32-bit. 
// [Files]  		Aint13.asm, Ahcibsp.asm, Aint13.c, Aint13.h, Aint13.bin
// 
// 10    2/10/11 10:49a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		Aint13.mak
// AInt13.h
// AInt13.c
// 
// 9     6/21/10 5:32a Rameshr
// AHCI Legacy booting through MMIO reg.
// EIP 38444
// 
// 8     9/09/08 3:19p Michaela
// Added AHCI_CD_CSM_ID_OFFSET for assigning
// device numbers for CDs/DVDs in order to
// avoid a CSM16 conflict with PATA devices, which
// may be present on some systems
// 
// 7     5/28/08 9:41a Rameshraju
// Updated the AMI Address.
// 
// 6     5/13/08 4:31p Olegi
// Modifications in DEV_PARAM_STRUC and DEV_PTR_STRUC to accomodate the
// new AI13.BIN that is based on the latest AHCI Core8 src.
// 
// 3     3/28/08 12:16p Michaela
// updated copyright
// 
// 2     19/12/07 4:29p Anandakrishnanl
// 
// 1     12/07/07 11:17a Olegi
//
//****************************************************************************

#ifndef __AI13_HEADER__
#define __AI13_HEADER__

#include "efi.h"
#include "Protocol\PciIo.h"

#pragma pack(1)

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
//  Name:           AINT13.H
//  Description:    Definitions and structures for AHCI INT13
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

typedef struct _DEV_INFO_STRUC {
  UINT8			bDetectType;	// Detected Device Type (Details Below)
  UINT8			bInstalledType;	// Device Installed Type (See Below)
  UINT16		wStatus;		// Bit-mapped device Init Status (Details Below)
  UINT8			bInt13Num;		// Device# for INT13 (8xh)
  UINT8			bPMNum;			// Port Multipier Port #
  UINT8			bPortNum;		// SATA Port# (0-Based) where device is present
  UINT16		wBusDevFunc;	// Bus#, Dev#, Func# of Controller
  UINT8         bControllerNo;  // Ahci Controller number
  UINT32		dHbaBase;		// HBA Base Address of Generic Host Control Registers
  UINT32		dHbaCap;		// HBA Capabilities
  UINT32		dPortBase;		// Base Address of SATA port where device is present
  UINT8			bSelector;		// Device selector value
  UINT8			bIrq;			// IRQ used by this device
  UINT8			bInfoFlag;		// Information Flag (details below)
  UINT8			bSectorSizeN;	// N value of Sector size 2^N ;For 512bytes sector, N = 9
  UINT16		wSmartInfo;		// SMART info (details below)
  UINT32		dTotalSectorsLo;// Total #of sectors in device (1-based)
  UINT32		dTotalSectorsHi;
  UINT16		wXferCount;		// Device transfer count. Used for ATAPI packer size
  UINT8			bBlockInfo;
  UINT8			b32BitInfo;
  UINT8			bUDMAInfo;
  UINT8			bPIOInfo;
} DEV_INFO_STRUC;

typedef struct _CONTROLLER_INFO_STRUC
{
    UINT16      BusDevFun;		// Bus, Device and Function number for a controller
    UINT8		ControllerNo;	// Controler number for a controller
}CONTROLLER_INFO_STRUC;

// Details of bDetectType

#define DETECT_NO			0
#define DETECT_ATA			1
#define DETECT_ATAPI_CD		2
#define DETECT_ATAPI_ARMD	3

// Details of bInstalledType

#define INSTALLED_NO		0
#define INSTALLED_HDD		1
#define INSTALLED_CDROM		2
#define INSTALLED_ARMD_FDD 	3
#define INSTALLED_ARMD_HDD 	4

// Details of wStatus

//	Bit 0 = 1, successful (device is installed in this case)
//	Bit 1 = 1, Identify Device Failed
//	Bit 2 = 1, Invalid Device Geometry
//	Bit 3 = 1, Init device parameter failed
//	Bit 4 = 1, Recalibrate failed
//	Bit 5 = 1, SMART failed
//	Bit 6 = 1, Verify failed
//	Bit 7 = 1, Security Freeze Lock failed
//	Bit 8 = 1, Port Reset failed
//	Bit 9 = 1, SMART Event was found
//	Bit 10 = 1, Device will be supported by RIAD OROM, not AHCI OROM (ex. HDD)
//	Bit 14-11,  Reserved for future use
//	Bit 15 = 1, Device not supported

#define ST_SUCCESS				0x0001
#define ST_ID_DEV_ERR			0x0002
#define ST_DEV_GEOMETRY_ERR		0x0004
#define ST_INIT_DEV_PARAM_ERR	0x0008
#define ST_RECALI_ERR			0x0010
#define ST_SMART_ERR			0x0020
#define ST_VERIFY_ERR			0x0040
#define ST_FREEZE_LOCK_ERR		0x0080
#define ST_PORT_RESET_ERR		0x0100
#define ST_SMART_EVENT			0x0200
#define ST_RAID_SUPPORT_ERR		0x0400
#define ST_NOT_SUPPORT_ERR		0x8000


// Details of bInt13Num

// Bit 7 = 1, this bit must be set for CDs/HDDs
// AHCI_CD_CSM_ID_OFFSET, PATA CDs/DVDs use the device handle range 0x80-0x8F
//                        so this value will be added to ensure AHCI CDs/DVDs 
//                        are above that range

#define AHCI_CD_CSM_ID_OFFSET  0x10  


// Details of bInfoFlag, a bit-mapped field

//	Bit 0 = 1, Device supports removable media
//	Bit 1 = 1, 48bit LBA enabled
//	Bit 2 = 1, Device uses IRQ; 0, Device uses DRQ
//	Bit 6-2,   Reserved
//	Bit 7 = 1, ATAPI Device; 0, ATA Device

#define INFO_REMOVABLE	0x01
#define INFO_LBA_48		0x02
#define INFO_IRQ		0x04
#define INFO_ATAPI		0x80

// Details wSmartInfo

//	Bit 0 = 0/1, SMART (Not Supported/Supported)
//	Bit 1 = 0/1, SMART (Disabled/Enabled)
//	Bit 2 = 0/1, Device Status Good/Bad
//	Bit 7 = 0/1, SMART Execution Successful/Error
//  Bit 15-8,    Reserved

#define AHCI_SMART_SUPPORT			0x01
#define AHCI_SMART_ENABLE			0x02
#define AHCI_SMART_EN				0x02
#define AHCI_SMART_STATUS			0x04
#define AHCI_SMART_COMMAND_STATUS	0x80

#define SECTOR_LENGTH_N         9
#define SELECTOR_NON_LBA        0xA0
#define SELECTOR_LBA            0xE0
#define MAX_STND_XFER_SECTOR    0x80
#define MAX_EXTD_XFER_SECTOR    0x7F
#define BLOCK_SIZE              0x80
#define BLOCK_SIZE_N            0xB

typedef struct _DEV_PTR_STRUC {
  UINT8			bInt13Num;		// INT13 Drive# for this Port
  UINT8			bDetectType;	// Detected Device Type
  UINT8			bPMnum;			// Port Multipier port #
  UINT8			bPortNum;		// Port# (0-based) on Controller
  UINT32		dParamTablePtr;	// Ptr to device parameter table
  UINT32		dInfoTablePtr;	// Ptr to device info table
} DEV_PTR_STRUC;

typedef struct _DEV_PARAM_STRUC {
  UINT16        wMAXCYL;    // maximum no. of cylinders..INT13 interface. (logical)
  UINT8         bMAXHN;     // maximum no. of heads..INT13 interface. (logical)
  UINT8         bLBASIG;    // LBA signature
  UINT8         bLBASPT;    // #of sectors per track drive is configured for. (physical)
  UINT16        wWPCYL;     // start write precomp cyl no.
  UINT8         bReserved;  // reserved
  UINT8         bCBYTE;     // bit 3 for more than 8 heads
  UINT16        wLBACYL;    // #of cylinders drive is configured for. (physical)
  UINT8         bLBAHD;     // #of heads drive is configured for. (physical)
  UINT16        wLANDZ;     // Landing zone
  UINT8         bMAXSN;     // no. of sectors per track..INT13 interface. (logical)
  UINT8         bLBACHK;    // checksum..LBA
} DEV_PARAM_STRUC;

//
// The following definitions should be in sync with 16-bit definition
//
#define SATA_PORT_COUNT 32
#define MAX_DESCRIPTION_STRLEN 32

typedef struct _AHCI_SMM_RTS {
    UINT8   MiscInfo;
    UINT16  SmmAttr;
    UINT32  SmmPort;
    UINT32  SmmData;
} AHCI_SMM_RTS;

typedef struct _AHCI_RT_MISC_DATA {
    UINT8        NumAhciDevice;      // #of AHCI device installed by BIOS
    UINT8        RunAttribute;       // Bit-mapped information about runtime environment
    UINT8        AhciEbdaSizeK;      // Size of EBDA in unit of 1k that is created by AHCI init
    UINT32       AhciEbdaStart;      // Start offset of AHCI communication area in EBDA
    AHCI_SMM_RTS AhciSmmRt;          // Port and Data information to generate software SMI
} AHCI_RT_MISC_DATA;

typedef struct _DEV_BBS_OUTFIT {
    UINT8   DescString[MAX_DESCRIPTION_STRLEN];
} DEV_BBS_OUTFIT;

typedef struct _AHCI_I13_RTDATA {
    DEV_PARAM_STRUC DevParam[SATA_PORT_COUNT];
    DEV_INFO_STRUC  DevInfo[SATA_PORT_COUNT+1];
    DEV_PTR_STRUC   DevPtr[SATA_PORT_COUNT];
    AHCI_RT_MISC_DATA   AhciRtMiscData;
    DEV_BBS_OUTFIT  DevOutfit[SATA_PORT_COUNT];
} AHCI_I13_RTDATA;

typedef struct _AHCI_I13_DATA {
    AHCI_I13_RTDATA rtdata;
    UINT16          CheckForAhciCdromOffset;
    UINT16          AhciBcvOffset;
} AHCI_I13_DATA;

// Details of bSignature field:	A signature Axh indicates that the table is translated.
#define DPTBL_SIG_MASK		0x0F0
// A0h signature indicating LBA translation
#define LBA_SIGNATURE       0x0A0

//-------------------------------------------------------------------------
// Port registers
//
#define PORT_REGISTER_START         0x100
#define PORT_REGISTER_SET_SIZE      0x80
#define PORT_REGISTER_SET_SIZE_N    7

#define SIZE_CLCTFIS_AREA_K         4
#define A_EBDA_USED                 1
#define A_INT13_SWSMI_USED          BIT2

#define BAID_TYPE_HDD       1
#define BAID_TYPE_RMD_HDD   2
#define BAID_TYPE_CDROM	    3
#define BAID_TYPE_RMD_FDD   4
#define BAID_TYPE_FDD       5

#define DEFAULT_DEVICE_STATUS	0x50
#define SYSTYPE_ATA             0
#define DEVTYPE_SYS             1

EFI_STATUS  GetAccessInfo (EFI_PCI_IO_PROTOCOL*, UINT16*, UINT16*);
EFI_STATUS  InitCspData (UINT16, UINT16,UINT32,UINT8);
UINT16 CountDrives(IN EFI_HANDLE *HandleBuffer,
                   IN UINTN        HandleCount,
                   IN VOID         *Devices
                   );
#pragma pack()

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
