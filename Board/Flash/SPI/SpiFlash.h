//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Flash/SPI/SpiFlash.h 2     4/24/13 11:10p Thomaschen $
//
// $Revision: 2 $
//
// $Date: 4/24/13 11:10p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Flash/SPI/SpiFlash.h $
// 
// 2     4/24/13 11:10p Thomaschen
// 
// 29    3/08/13 3:12a Calvinchen
// [TAG]  		EIP110515
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Microchip SST26VF064B & SST26VF064BA 8MB SPI Flash part
// support 
// [RootCause]  	Need "Global Block Protection Unlock" before programming.
// [Solution]  	Added "Global Block Protection Unlock" before programming.
// [Files]  		SpiFlash.h
// SpiIdentify.c
// SpiFlash.cif
// 
// 28    2/18/13 5:14a Calvinchen
// [TAG]  		EIP114488
// [Category]  	Improvement
// [Description]  	1. Added MXIC MX25U6435F SPI Flash part support
// 2. Added GigaDevice 25LQ series flash part.
// [Files]  		SpiFlash.h
// SpiIdentify.c
// 
// 27    1/14/13 5:40a Calvinchen
// [TAG]  		EIP110515
// [Category]  	Improvement
// [Description]  	Microchip SST26VF064B & SST26VF064BA 8MB SPI Flash part
// support
// [Files]  		SpiFlash.h
// SpiIdentify.c
// 
// 26    12/13/12 2:22a Calvinchen
// Added support for winbond W25Q F and W series Flash Parts.
// 
// 25    7/18/12 6:10a Calvinchen
// 1. Changed N25Q128 to 4K erase.
// 2. Added N25Q128A support.
// 
// 24    10/31/11 6:46a Calvinchen
// [TAG]  		EIP68872
// [Category]  	Improvement
// [Description]  	Added ESMT 25L64QA.
// [Files]  		SpiFlash.h
// SpiIdentify.c
// 
// 23    8/24/11 7:58a Calvinchen
// Improvement :
// Added Token "FAST_READ_SUPPORT" for switching the SPI
// Read(03)/FastRead(0B)/DualOutputFastRead(3B) command. To use the
// FastRead and the Dual Output Fast Read command MUST have Hardware SPI
// support. **Only validated with Intel Mahobay platform (Southbridge:
// PatherPoint)**
// 
// 22    7/21/11 5:07a Calvinchen
// [TAG]  		EIP65366
// [Category]  	Improvement
// [Description]  	New SPI Flash supports for EON 25QH and ESMT 25L PA
// flash part. 
// [Files]  		SpiFlash.h
// SpiIdentify.c
// 
// 21    4/08/11 3:05a Chunweitseng
// [TAG]  		EIP57327
// [Category]  	Improvement
// [Description]  	 Added Support for FIDELIX FM25Q32A/64A and AMIC
// 25LQ032.
// 
// [Files]  		SpiFlash.h, SpiIdentify.c
// 
// 20    2/10/11 5:43a Calvinchen
// [TAG]  		EIP53437
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Corrected Numonyx M25P128 Minimum Sector Size to 256K. 
// [RootCause]  	None.
// [Solution]  	None.
// [Files]  		SpiFlash.sdl
// SpiFlash.mak
// SpiFlash.h
// SpiIdentify.c
// SpiFlash.cif
// 
// 19    11/30/10 3:28a Calvinchen
// Added Numonyx N25Q Series.
// 
// 17    3/11/10 6:43a Calvinchen
// Improvement : Added SST AAIWordProgram SPI command to speed up the
// programming time.
// 
// 16    1/07/10 5:34a Calvinchen
// Addes support for Spansion S25FL128/129P.
// 
// 15    12/31/09 1:50a Klzhan
// Improvement : Support EON 25Q32/64.
// 
// 14    12/23/09 6:13a Calvinchen
// Improvement:1.Added FWH/LPC/STD Flash Device Number support.
// 
// 13    12/22/09 2:30a Calvinchen
// Added support for ATMEL 25DQ161.
// 
// 12    12/16/09 3:45a Calvinchen
// 
// 11    12/15/09 5:49a Calvinchen
// Improvement : 
// 1.Added support for GigaDevie 25Q80/16.
// 2.Added Flash Chip Name support.
// 
// 9     6/24/09 3:14a Calvinchen
// (EIP22177) Updated for Aptio Source Enhancement. 
//
// 8     5/11/09 7:21a Calvinchen
// Added support for SST 25VF064C and MXIC MX25L1635/3235/6435..
//
// 7     4/27/09 3:19a Calvinchen
// 1.Added support for Winbond 25Q128
// 2.(EIP20459) Added Multiple SPI CSP component support.
//
// 6     12/10/08 5:53a Calvinchen
// Added support for Winbond W25Q80/16 1M/2M SPI flash.
//
// 5     9/30/08 10:09a Calvinchen
// According to Intel ICH7/ICH8/ICH9/ICH10 - SPI Family Flash Programming
// Guide Application Note - Rev#2.4,
// Section#5.3 Software Sequencing Opcode Requirements and
// Recommendations,It is strongly recommended that the "9Fh" JEDEC ID be
// used instead of "90h" or "AB".
// Intel utilities such as the Flash Programming tool (Fprog.exe and
// fpt.exe) will incorrectly detect the flash part in the system and it
// may lead to undesired program operation.
//
// 4     9/11/08 2:30a Calvinchen
// Added support for EON 25F32.
//
// 3     8/26/08 2:54a Calvinchen
// 1.Added support for AMTME 25DF641.
// 2.Fixed Fail to un-protect ATMEL flash.
// 3.Fixed building failed if $(CFLAGS) = /W4.
//
// 2     5/09/08 3:35a Calvinchen
// Added support for STM M25PF32.
//
// 1     3/13/08 6:31a Calvinchen
//
// 12    3/05/08 9:11a Robert
//
// 11    2/13/08 6:14p Robert
//
// 2     2/13/08 6:03p Robert
// coding updates and addition of Intel SPI part
//
// 10    1/07/08 3:05p Robert
// updated for coding standard
//
// 9     1/02/08 12:04p Robert
// Added the MX25L1605 device ID
//
// 8     11/09/07 3:49p Alexp
// Added SPI opcode Read Index
//
// 7     10/24/07 4:23p Robert
// Needed to add a function prototype for SpiTransfer()
//
// 6     10/09/07 1:11p Robert
// added a new VID/DID and cleaned up other additions of parts
//
// 5     10/01/07 4:19a Klzhan
// Added support for AMIC A25L080 , MXIC 25L6405 25L3205 , ST 25P32 .
//
// 4     8/20/07 2:22p Robert
// Added support for Atmel AT26DF321 and for winbond w25x32 parts
//
// 3     8/02/07 2:51p Artems
// Added support Atmel 1MB
//
// 2     2/20/07 6:44p Robert
// removed some unneeded definitions and added a few new ones
//
// 1     12/18/06 3:39p Robert
// Initial Check in
//
// 2     11/16/06 6:27p Robert
// removed unused definition
//
// 1     10/31/06 2:30p Sivagarn
// Initial Checkin
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    SpiFlash.h
//
// Description: Contains Vendor IDs and Device IDs for ths supported
//      parts.  also contains the command values for each supported part
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _SPIFlash_H_
#define _SPIFlash_H_


#include <token.h>
#include "Board\Sb\Sb.h"


VOID SpiFlashLock(UINT16 MfgDevId, BOOLEAN Lock);


//-------------------------------------------------------------------
// Supported SPI devices
// MFG and Device code
#define SST_25LF040A                0x44bf
#define SST_25LF040                 0x40bf
#define SST_25LF080A                0x80bf

#define SST_25VF040B                0x8dbf
#define SST_25VF080B                0x8ebf
#define SST_25VF016B                0x41bf
#define SST_25VF032B                0x4abf
#define SST_25VFxxx_ID              0x25bf
#define SST_26VFxxx_ID              0x26bf


//PMC 25LVxxx Device ID/Manufacturer ID
#define PMC_25LV040                 0x7e9d
#define PMC_25LVxxx_ID              0x9d7f

#define ATMEL_26DF041               0x441f
#define ATMEL_26DF081               0x451f
#define ATMEL_26DF161               0x461f
#define ATMEL_26DF321               0x471f  // ATMEL 26DF321 32Mbit
#define ATMEL_25DF641               0x481f  // ATMEL 25DF641 64Mbit
#define ATMEL_25DQ161               0x861f

//Winbond W25Xxx Device ID/Manufacturer ID
#define WINBOND_W25X10              0x10ef
#define WINBOND_W25X20              0x11ef
#define WINBOND_W25X40              0x12ef
#define WINBOND_W25X80              0x13ef
#define WINBOND_W25X16              0x14ef
#define WINBOND_25Xxx_ID            0x30ef
#define WINBOND_25Qxx_ID            0x40ef
#define WINBOND_25QxxW_ID           0x50ef
#define WINBOND_25QxxF_ID           0x60ef

// MXIC Device ID/Manufacturer ID
#define MX25L4005_DEVICE_ID         0x13c2
#define MX25L8005_DEVICE_ID         0x14c2
#define MX25L1605_DEVICE_ID         0x15c2
#define MX25L3205_DEVICE_ID         0x16c2
#define MX25L6405_DEVICE_ID         0x17c2
#define MXIC_25Lxxxx_ID             0x20c2
#define MXIC_25Lxx35_ID             0x24c2
#define MXIC_25Lxx36_ID             0x5ec2
#define MXIC_25Uxx35_ID             0x25c2

// Spansion S25FL008A Device ID/Manufacturer ID
#define SPANSION_25FL004A           0x1201
#define SPANSION_25FL008A           0x1301
#define SPANSION_25FLxxx_ID         0x0201
#define SPANSION_25FLxxxP_ID        0x2001

// ESMT F25L00xA Device ID/Manufacturer ID
#define ESMT_25L004A                0x128c
#define ESMT_25L008A                0x138c
#define ESMT_25L016A                0x148c
#define ESMT_25L032A                0x158c
#define ESMT_25LxxxT_ID             0x208c
#define ESMT_25LxxxB_ID             0x218c
#define ESMT_25Lxx_ID               0x408c
#define ESMT_25LxxQ_ID              0x418c

// ST Micro/Micron/Numonyx M25Pxx Device ID/Manufacturer ID
#define STM_M25P40                  0x1320
#define STM_M25P80                  0x1420
#define STM_M25P32                  0x2020
#define STM_25PExx_ID               0x8020
#define STM_25PXxx_ID               0x7120      // M25PX16/32
#define STM_25PFxx_ID               0x7020      // M25PF32
#define STM_25Pxx_ID                0x2020      // M25P16/32/64
#define Numonyx_25Qxx_ID            0xBA20      // N25Q16/32/64/128
#define Numonyx_25QxxA_ID           0xBB20      // N25Q16/32/64/128

// AMIC 25Lxx Device ID/Manufacturer ID
#define AMIC_25Lxx_ID               0x377f
#define AMIC_25Lxxx_ID              0x3037
#define AMIC_25LQxxx_ID             0x4037

// EON  25P/Fxx Device ID/Manufacturer ID
#define EON_25Fxx_ID                0x311c
#define EON_25Pxx_ID                0x201c
#define EON_25Qxx_ID                0x301c
#define EON_25QHxx_ID               0x701c

// INTEL 25Fxxx Device ID/Manufacturer ID
#define INTEL_25Fxxx_ID             0x8989
#define INTEL_25Fxxx_ID             0x8989

// Giga Device GD25Qxx Device ID/Manufacturer ID
#define GD_25Qxx_ID                 0x40C8
#define GD_25LQxx_ID                0x60C8

// FIDELIX Device FM_25Qxx Device ID/Manufacturer ID
#define FM_25Qxx_ID                 0x32F8

//-------------------------------------------------------------------
//  NOTE: Assuming that 8Mbit flash will only contain a 4Mbit binary.
//        Treating 4Mbit and 8Mbit devices the same.

//-------------------------------------------------------------------
// BIOS Base Address
#define BIOS_BASE_ADDRESS_4M 0xfff80000
#define BIOS_BASE_ADDRESS_8M 0xfff00000

//-------------------------------------------------------------------
// block and sector sizes
#define SECTOR_SIZE_256B    0x100       // 4kBytes sector size
#define SECTOR_SIZE_4KB     0x1000      // 4kBytes sector size
#define SECTOR_SIZE_8KB     0x2000      // 8kbytes sector size
#define SECTOR_SIZE_64KB    0x10000     // 64kBytes sector size
#define SECTOR_SIZE_256KB   0x40000     // 256kBytes sector size
#define BLOCK_SIZE_32KB     0x8000      // 32Kbytes block size

//-------------------------------------------------------------------
// Flash commands

// Commands for SST 25LFxx and 25VFxx parts
#define SPI_SST25LF_COMMAND_WRITE         0x02
#define SPI_SST25LF_COMMAND_READ          0x03
#if FAST_READ_SUPPORT == 0
#define SPI_SST25VF_COMMAND_READ          0x03        // Read Byte
#elif FAST_READ_SUPPORT == 1
#define SPI_SST25VF_COMMAND_READ          0x0B        // Fast Read
#elif FAST_READ_SUPPORT == 2
#define SPI_SST25VF_COMMAND_READ          0x3B        // Dual Output Fast Read
#endif
#define SPI_SST25LF_COMMAND_ERASE         0x20
#define SPI_SST25LF_COMMAND_WRITE_DISABLE 0x04
#define SPI_SST25LF_COMMAND_READ_STATUS   0x05
#define SPI_SST25LF_COMMAND_WRITE_ENABLE  0x06
//#define SPI_SST25LF_COMMAND_READ_ID       0xab
#define SPI_SST25LF_COMMAND_READ_ID       0x90
#define SPI_SST25VF_COMMAND_READ_ID       0x9f
#define SPI_SST25LF_COMMAND_WRITE_S_EN    0x50
#define SPI_SST25LF_COMMAND_WRITE_S       0x01

// PMC commands
#define SPI_PMC25LV_COMMAND_WRITE         0x02
#define SPI_PMC25LV_COMMAND_READ          0x03
#define SPI_PMC25LV_COMMAND_ERASE         0xd7
#define SPI_PMC25LV_COMMAND_WRITE_DISABLE 0x04
#define SPI_PMC25LV_COMMAND_READ_STATUS   0x05
#define SPI_PMC25LV_COMMAND_WRITE_ENABLE  0x06
#define SPI_PMC25LV_COMMAND_READ_ID       0xab
#define SPI_PMC25LV_COMMAND_WRITE_S_EN    0x06
#define SPI_PMC25LV_COMMAND_WRITE_S       0x01

// Atmel commands
#define SPI_AT26DF_COMMAND_WRITE         0x02
#if FAST_READ_SUPPORT == 0
#define SPI_AT26DF_COMMAND_READ          0x03        // Read Byte
#elif FAST_READ_SUPPORT == 1
#define SPI_AT26DF_COMMAND_READ          0x0B        // Fast Read
#elif FAST_READ_SUPPORT == 2
#define SPI_AT26DF_COMMAND_READ          0x3B        // Dual Output Fast Read
#endif
#define SPI_AT26DF_COMMAND_ERASE         0x20
#define SPI_AT26DF_COMMAND_WRITE_DISABLE 0x04
#define SPI_AT26DF_COMMAND_READ_STATUS   0x05
#define SPI_AT26DF_COMMAND_WRITE_ENABLE  0x06
#define SPI_AT26DF_COMMAND_READ_ID       0x9f
#define SPI_AT26DF_COMMAND_WRITE_S_EN    0x00
#define SPI_AT26DF_COMMAND_WRITE_S       0x01
// ATMEL 26DF321 32Mbit SPI Flash part support
#define SPI_AT26DF_COMMAND_PROTECT       0x36
#define SPI_AT26DF_COMMAND_UNPROTECT     0x39

// Winbond W25Xxx serial flash commands
#define SPI_WIN_W25X_COMMAND_WRITE         0x02     // page program
#define SPI_WIN_W25X_COMMAND_READ          0x03     // Read Byte
#define SPI_WIN_W25X_COMMAND_ERASE         0x20     // erase 4K sectors
#define SPI_WIN_W25X_COMMAND_WRITE_DISABLE 0x04     // Write Disable
#define SPI_WIN_W25X_COMMAND_READ_STATUS   0x05     // read Status Register
#define SPI_WIN_W25X_COMMAND_WRITE_ENABLE  0x06     // Write Enable
#define SPI_WIN_W25X_COMMAND_READ_ID       0x90     // Manufacturer/Device ID
#define SPI_WIN_W25X_COMMAND_WRITE_S       0x01     // Write Status register

// MXIC MX25Lx005 commands
#define SPI_MXIC_M25L_COMMAND_WRITE             0x02        // page program
#define SPI_MXIC_M25L_COMMAND_READ              0x03        // Read Byte
#define SPI_MXIC_M25L_COMMAND_ERASE             0x20        // erase 4K sectors
#define SPI_MXIC_M25L_COMMAND_WRITE_DISABLE     0x04        // Write Disable
#define SPI_MXIC_M25L_COMMAND_READ_STATUS       0x05        // read Status Register
#define SPI_MXIC_M25L_COMMAND_WRITE_ENABLE      0x06        // Write Enable
#define SPI_MXIC_M25L_COMMAND_READ_ID           0x9f        // Manufacturer/Device ID
#define SPI_MXIC_M25L_COMMAND_WRITE_S           0x01        // Write Status register

// Spansion S25FL00xA commands
#define SPI_S25FL00xA_COMMAND_WRITE             0x02        // page program
#define SPI_S25FL00xA_COMMAND_READ              0x03        // Read Byte
#define SPI_S25FL00xA_COMMAND_ERASE             0xd8        // erase 64K sectors
#define SPI_S25FL00xA_COMMAND_WRITE_DISABLE     0x04        // Write Disable
#define SPI_S25FL00xA_COMMAND_READ_STATUS       0x05        // read Status Register
#define SPI_S25FL00xA_COMMAND_WRITE_ENABLE      0x06        // Write Enable
#define SPI_S25FL00xA_COMMAND_READ_ID           0x9f        // Manufacturer/Device ID
#define SPI_S25FL00xA_COMMAND_WRITE_S           0x01        // Write Status register

// ESMT F25L00xA commands
#define SPI_ESMT_F25L00x_COMMAND_WRITE          0x02        // page program
#define SPI_ESMT_F25L00x_COMMAND_READ           0x03        // Read Byte
#define SPI_ESMT_F25L00x_COMMAND_ERASE          0x20        // erase 4K sectors
#define SPI_ESMT_F25L00x_COMMAND_WRITE_DISABLE  0x04        // Write Disable
#define SPI_ESMT_F25L00x_COMMAND_READ_STATUS    0x05        // read Status Register
#define SPI_ESMT_F25L00x_COMMAND_WRITE_ENABLE   0x06        // Write Enable
#define SPI_ESMT_F25L00x_COMMAND_READ_ID        0x90        // Manufacturer/Device ID
#define SPI_ESMT_F25L00x_COMMAND_WRITE_S_EN     0x50        // Write Status Enable register
#define SPI_ESMT_F25L00x_COMMAND_WRITE_S        0x01        // Write Status register

// ST Micro M25Pxx commands
#define SPI_M25Pxx_COMMAND_WRITE            0x02        // page program
#define SPI_M25Pxx_COMMAND_READ             0x03        // Read Byte
#define SPI_M25Pxx_COMMAND_ERASE            0xd8        // erase 64K sectors
#define SPI_M25Pxx_COMMAND_WRITE_DISABLE    0x04        // Write Disable
#define SPI_M25Pxx_COMMAND_READ_STATUS      0x05        // read Status Register
#define SPI_M25Pxx_COMMAND_WRITE_ENABLE     0x06        // Write Enable
#define SPI_M25Pxx_COMMAND_READ_ID          0x9f        // Manufacturer/Device ID
#define SPI_M25Pxx_COMMAND_WRITE_S          0x01        // Write Status register

// ST Micro M25Pxx commands
#define SPI_M25PExx_COMMAND_WRITE           0x02        // page program
#if FAST_READ_SUPPORT == 0
#define SPI_M25PExx_COMMAND_READ            0x03        // Read Byte
#elif FAST_READ_SUPPORT == 1
#define SPI_M25PExx_COMMAND_READ            0x0B        // Fast Read
#elif FAST_READ_SUPPORT == 2
#define SPI_M25PExx_COMMAND_READ            0x3B        //  Dual Output Fast Read
#endif
#define SPI_M25PExx_COMMAND_ERASE           0xD8        // erase 64K sectors
#define SPI_M25PExx_COMMAND_PAGE_ERASE      0xDB        // erase 256 byte pages
#define SPI_M25PExx_COMMAND_WRITE_DISABLE   0x04        // Write Disable
#define SPI_M25PExx_COMMAND_READ_STATUS     0x05        // read Status Register
#define SPI_M25PExx_COMMAND_WRITE_ENABLE    0x06        // Write Enable
#define SPI_M25PExx_COMMAND_READ_ID         0x9F        // Manufacturer/Device ID
#define SPI_M25PExx_COMMAND_WRITE_S         0x01        // Write Status register


//#define SECTOR_SIZE_4KB   0x1000  // Common 4kBytes sector size
//#define SECTOR_SIZE_64KB  0x10000  // Common 64kBytes sector size
#define BLOCK_SIZE_64KB     0x00010000  // Common 64kBytes block size
#define MAX_FWH_SIZE        0x00100000  // 8Mbit (Note that this can also be used for the 4Mbit )


extern const UINT8 SpiMaxTransfer;

// SPI default opcode slots
extern const UINT8 SpiOpcodeWriteIndex;
extern const UINT8 SpiOpcodeReadIndex;
extern const UINT8 SpiOpcodeEraseIndex;
extern const UINT8 SpiOpcodeWriteStatusIndex;

#endif

//<AMI_STHDR_START>
//============================================================================
// Structure:   EX_FLASH_PART
//
// Description: This structure contains variables that define the detals and
//              and command set of flash part.
//
// Fields:
//      FlashCommandMenu - FLASH_INFO - Defines the flash part command sets.
//      FlashCapacity - UINT32 - Defines the Capacity of flash part.
//      FlashVenDevId - UINT32 - Defines the Vendor and Device ID of flash part.
//      DeviceName - UINT8 * - Pointer to a buffer that can contain the part
//          number of flash part (Reserved for future used).
//
// Referral:
//      None
//============================================================================
//<AMI_STHDR_END>
#pragma pack(push, 1)

typedef struct _EX_FLASH_PART {
    FLASH_INFO                      FlashCommandMenu;
    UINT32                          FlashCapacity;
    UINT32                          FlashVenDevId;
    UINT8                           AAIWordProgram;
    UINT8                           GlobalBlockUnlock;
    UINT8                           bReserved[2];
} EX_FLASH_PART;

#pragma pack(pop)
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
