//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Flash/SPI/SpiIdentify.c 2     4/24/13 11:11p Thomaschen $
//
// $Revision: 2 $
//
// $Date: 4/24/13 11:11p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Flash/SPI/SpiIdentify.c $
// 
// 2     4/24/13 11:11p Thomaschen
// 
// 37    3/08/13 3:12a Calvinchen
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
// 36    2/18/13 5:15a Calvinchen
// [TAG]  		EIP114488
// [Category]  	Improvement
// [Description]  	1. Added MXIC MX25U6435F SPI Flash part support
// 2. Added GigaDevice 25LQ series flash part.
// [Files]  		SpiFlash.h
// SpiIdentify.c
// 
// 35    1/14/13 5:40a Calvinchen
// [TAG]  		EIP110515
// [Category]  	Improvement
// [Description]  	Microchip SST26VF064B & SST26VF064BA 8MB SPI Flash part
// support
// [Files]  		SpiFlash.h
// SpiIdentify.c
// 
// 34    12/13/12 2:23a Calvinchen
// Added support for winbond W25Q F and W series Flash Parts.
// 
// 33    10/18/12 3:29a Calvinchen
// Improvement:
// 1. Changed N25Q128 to 4K erase.
// 2. Added N25Q128A support. 
// Bug Fixed :1. Fixed for ESMT 25L B Series.
// 
// 32    7/18/12 6:10a Calvinchen
// 1. Changed N25Q128 to 4K erase.
// 2. Added N25Q128A support.
// 
// 31    4/27/12 5:12a Calvinchen
// [TAG]  		EIP86044
// [Category]  	Improvement
// [Description]  	[Pegatron-DT] SMIFlash module update for display SPIROM
// size in AFU
// [Files]  		SpiFlash.sdl
// SpiIdentify.c
// 
// 30    4/02/12 1:41a Klzhan
// [TAG]  		EIP86044
// [Category]  	Improvement
// [Description]  	Customized AFU to support a parameter to display the
// current SPI's name and size
// 
// 29    10/31/11 6:46a Calvinchen
// [TAG]  		EIP68872
// [Category]  	Improvement
// [Description]  	Added ESMT 25L64QA.
// [Files]  		SpiFlash.h
// SpiIdentify.c
// 
// 28    8/24/11 7:58a Calvinchen
// Improvement :
// Added Token "FAST_READ_SUPPORT" for switching the SPI
// Read(03)/FastRead(0B)/DualOutputFastRead(3B) command. To use the
// FastRead and the Dual Output Fast Read command MUST have Hardware SPI
// support. **Only validated with Intel Mahobay platform (Southbridge:
// PatherPoint)**
// 
// 27    8/02/11 12:05a Calvinchen
// [TAG]  		EIP48934
// [Category]  	Improvement
// [Description]  	Missing support for flash device Numonyx NX25Q064 on
// Sugarbay platform
// [Files]  		SpiIdentify.c
// 
// 26    7/21/11 5:07a Calvinchen
// [TAG]  		EIP65366
// [Category]  	Improvement
// [Description]  	New SPI Flash supports for EON 25QH and ESMT 25L PA
// flash part. 
// [Files]  		SpiFlash.h
// SpiIdentify.c
// 
// 25    4/08/11 3:08a Chunweitseng
// [TAG]  		EIP57327
// [Category]  	Improvement
// [Description]  	 Added Support for FIDELIX FM25Q32A/64A and AMIC
// 25LQ032.
// 
// [Files]  		SpiFlash.h, SpiIdentify.c
// 
// 24    2/17/11 3:36a Klzhan
// Add support 64K flash.
// 
// 23    2/10/11 5:43a Calvinchen
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
// 22    11/25/10 3:02a Calvinchen
// Added Support for Micron/Numonyx N25Q128.
// 
// 19    9/14/10 3:31a Calvinchen
// Improved for adding the "SPI_INITIALIAL_WITH_VSCC" token support for
// Intel ICHx SPI. 
// 
// 18    5/21/10 2:13a Calvinchen
// Bug fixed: Build failed with "undeclared identifier".
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
// 12    12/15/09 5:49a Calvinchen
// Improvement :
// 1.Added support for GigaDevie 25Q80/16.
// 2.Added Flash Chip Name support.
//
// 10    6/24/09 3:14a Calvinchen
// (EIP22177) Updated for Aptio Source Enhancement.
//
// 9     5/11/09 7:21a Calvinchen
// Added support for SST 25VF064C and MXIC MX25L1635/3235/6435..
//
// 7     3/12/09 4:47a Calvinchen
// Improvement : Added Unprotect Command OpCode (39h) to AMTEL SPI
// FLASH_INFO structure.
// Bug Fixed : Sometimes failed to unlock the Block Protect of SST SPI
// flash if Label "4.6.3_Flash_Combined_2_6" or later.
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
// 7     3/26/07 7:22p Robert
// Coding standard updates
//
// 6     2/20/07 6:45p Robert
// added support for the new sector size variable in the data structure
// and added support for the changed lock functionality
//
// 5     2/13/07 3:45p Robert
// added support for SST 25VF016B and fixed a coding error in one of the
// identify functions  prototype
//
// 4     2/13/07 11:30a Robert
//
// 1     12/18/06 3:39p Robert
// Initial Check in
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    SpiIdentify.c
//
// Description: Provides device specific indentify functions for the
//  supported spi parts
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------------
// Includes
#include <efi.h>
#include <AmiDxeLib.h>
#include "FlashPart.h"
#include "SpiFlash.h"
#include "token.h"
//----------------------------------------------------------------------------
// Local defines for transaction types
#ifndef SPI_OPCODE_TYPE_READ_NO_ADDRESS
#define SPI_OPCODE_TYPE_READ_NO_ADDRESS     0x0
#define SPI_OPCODE_TYPE_WRITE_NO_ADDRESS    0x1
#define SPI_OPCODE_TYPE_READ_WITH_ADDRESS   0x2
#define SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS  0x3
#endif
//----------------------------------------------------------------------------
// Module level global data
UINT32  MfgDevId = 0;
extern  UINT16          gFlashId;
extern  FLASH_PART      mCommonSpiFlash;
extern  EX_FLASH_PART   mExFlashPart;
extern  UINT8           pFlashDeviceNumber[FLASH_PART_STRING_LENGTH];
//----------------------------------------------------------------------------
// Extern Function Prototypes
extern
BOOLEAN
CommonSpiReadId (
    FLASH_INFO          *FlashInfo,
    UINT32              *dFlashId
);
extern
VOID
ReinitializeSpiEnvironment (
    FLASH_INFO          *FlashInfo
);
//----------------------------------------------------------------------------
// Flash Part Data Structures
FLASH_INFO Sst_25VF =
    {
        // Write Byte
        {SPI_SST25LF_COMMAND_WRITE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
         // Read Data
        {SPI_SST25VF_COMMAND_READ,          SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Erase 4k Sector
        {SPI_SST25LF_COMMAND_ERASE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Device Status Reg
        {SPI_SST25LF_COMMAND_READ_STATUS,   SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Read device ID
        {SPI_SST25VF_COMMAND_READ_ID,       SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Write Status Register
        {SPI_SST25LF_COMMAND_WRITE_S,       SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Status Enable
        {SPI_SST25LF_COMMAND_WRITE_S_EN,    SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Enable
        {SPI_SST25LF_COMMAND_WRITE_ENABLE,  SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        1,                                  // Page Size
        SECTOR_SIZE_4KB
    };

FLASH_INFO Sst_25LF =
    {
        // Write Byte
        {SPI_SST25LF_COMMAND_WRITE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Data
        {SPI_SST25LF_COMMAND_READ,          SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Erase 4k Sector
        {SPI_SST25LF_COMMAND_ERASE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Device Status Reg
        {SPI_SST25LF_COMMAND_READ_STATUS,   SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Read device ID
        {SPI_SST25LF_COMMAND_READ_ID,       SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Write Status Register
        {SPI_SST25LF_COMMAND_WRITE_S,       SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Status Enable
        {SPI_SST25LF_COMMAND_WRITE_S_EN,    SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Enable
        {SPI_SST25LF_COMMAND_WRITE_ENABLE,  SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        1,                                  // Page Size
        SECTOR_SIZE_4KB
    };

FLASH_INFO Stm_25PE =
    {
        // Write Byte
        {SPI_M25PExx_COMMAND_WRITE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Data
        {SPI_M25PExx_COMMAND_READ,          SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Erase 64k Sector
        {SPI_M25PExx_COMMAND_ERASE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Device Status Reg
        {SPI_M25PExx_COMMAND_READ_STATUS,   SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Read device ID
        {SPI_M25PExx_COMMAND_READ_ID,       SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Status Register
        {SPI_M25PExx_COMMAND_WRITE_S,       SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Status Enable - Not available on this part
        {0,                                 SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Enable
        {SPI_M25PExx_COMMAND_WRITE_ENABLE,  SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        256,
        SECTOR_SIZE_64KB
    };

FLASH_INFO Atmel_26DF =
    {
        // Write Byte
        {SPI_AT26DF_COMMAND_WRITE,          SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Data
        {SPI_AT26DF_COMMAND_READ,           SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Erase 4k Sector
        {SPI_AT26DF_COMMAND_ERASE,          SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Device Status Reg
        {SPI_AT26DF_COMMAND_READ_STATUS,    SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Read device ID
        {SPI_AT26DF_COMMAND_READ_ID,        SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Status Register
        {SPI_AT26DF_COMMAND_WRITE_S,        SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Status Enable
        {SPI_AT26DF_COMMAND_UNPROTECT,      SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Enable
        {SPI_AT26DF_COMMAND_WRITE_ENABLE,   SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        256,
        SECTOR_SIZE_4KB
    };
//----------------------------------------------------------------------------
// Functions Definitions

//----------------------------------------------------------------------------
// Identify Functions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IdentifySst_25LF
//
// Description: This function identifies the supported SPI flash parts and
//              returns appropriate flash device API pointer. If flash part is
//              not supported by this module it will return FALSE.
//              Supports the following SPI parts
//              SST 25LF040/080/106A, ESMT 25L004/008/016A
//
//
// Input:       pBlockAddress   Block address of the flash part. Can be used to
//                              send ID command
//
// Output:      **FlashApi      Pointer to hold the returned flash API
//
// Return:      TRUE            If flash part is supported, FlashApi contains
//                              routines to handle the flash requests
//              FALSE           Flash part is not supported
//
// Note:        This routine is part of the global flash init list. Make sure
//              it is properly linked to the init list "FlashList" (in SDL file)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IdentifySst_25LF    (
    IN  volatile UINT8      *pBlockAddress,
    OUT FLASH_PART          **FlashStruct
)
{
    if ( !CommonSpiReadId( &Sst_25LF, &MfgDevId ) )    return FALSE;
    switch ( (UINT16)MfgDevId ) {
        // Is SST 4M SPI flash part ?
        case SST_25LF040A :
            mExFlashPart.FlashCapacity = 0x80000;
            MemCpy ( pFlashDeviceNumber, "SST 25LF040", 14 );
            break;
        // Is SST 8M SPI flash part ?
        case SST_25LF080A :
            mExFlashPart.FlashCapacity = 0x100000;
            MemCpy ( pFlashDeviceNumber, "SST 25LF080", 14 );
            break;
        default :
            return  FALSE;
    }
    *FlashStruct = &mCommonSpiFlash;
    MemCpy( &mExFlashPart.FlashCommandMenu, &Sst_25LF, sizeof(FLASH_INFO) );
    mExFlashPart.FlashVenDevId = MfgDevId;
    gFlashId = MfgDevId;
    *(UINT32*)(pFlashDeviceNumber + FLASH_PART_STRING_LENGTH - 4) = \
                                                mExFlashPart.FlashCapacity;
    (*FlashStruct)->FlashProgramSize = Sst_25LF.PageSize;
    (*FlashStruct)->FlashSectorSize = Sst_25LF.SectorSize;
    (*FlashStruct)->FlashPartNumber = pFlashDeviceNumber;
    // Update the OpCode to OpMenu immediately if need.
    // ReinitializeSpiEnvironment ( &mExFlashPart.FlashCommandMenu );
    return  TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IdentifyAtmel_26DF
//
// Description: This function identifies the supported LPC flash parts and
//              returns appropriate flash device API pointer. If flash part is
//              not supported by this module it will return FALSE.
//              Supports the following SPI parts
//              ATMEL 26DFxx parts
//
// Input:   pBlockAddress   Block address of the flash part. Can be used to
//                              send ID command
//
// Output:  **FlashApi      Pointer to hold the returned flash API
//
// Return:  TRUE            If flash part is supported, FlashApi contains
//                              routines to handle the flash requests
//          FALSE           Flash part is not supported
//
// Note:   This routine is part of the global flash init list. Make sure
//         it is properly linked to the init list "FlashList" (in SDL file)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IdentifyAtmel_26DF  (
    IN  volatile UINT8      *pBlockAddress,
    OUT FLASH_PART          **FlashStruct
)
{
    if ( !CommonSpiReadId( &Atmel_26DF, &MfgDevId ) )    return FALSE;
    switch ( (UINT16)MfgDevId ) {
        // Is Atmel 4M SPI flash part ?
        case ATMEL_26DF041 :
            mExFlashPart.FlashCapacity = 0x80000;
            MemCpy ( pFlashDeviceNumber, "ATMEL 26DF041/25DF041", 21 );
            break;
        // Is Atmel 8M SPI flash part ?
        case ATMEL_26DF081 :
            mExFlashPart.FlashCapacity = 0x100000;
            MemCpy ( pFlashDeviceNumber, "ATMEL 26DF081/25DF081", 21 );
            break;
        // Is Atmel 16M SPI flash part ?
        case ATMEL_26DF161 :
        case ATMEL_25DQ161 :
            mExFlashPart.FlashCapacity = 0x200000;
            MemCpy ( pFlashDeviceNumber, "ATMEL 26DF161/25DQ161", 21 );
            break;
        // Is Atmel 32M SPI flash part ?
        case ATMEL_26DF321 :
            mExFlashPart.FlashCapacity = 0x400000;
            MemCpy ( pFlashDeviceNumber, "ATMEL 26DF321/25DF321", 21 );
            break;
        // Is Atmel 64M SPI flash part ?
        case ATMEL_25DF641 :
            mExFlashPart.FlashCapacity = 0x800000;
            MemCpy ( pFlashDeviceNumber, "ATMEL 26DF641/25DF641", 21 );
            break;
        default :   return  FALSE;
    }
    *FlashStruct = &mCommonSpiFlash;
    MemCpy( &mExFlashPart.FlashCommandMenu, &Atmel_26DF, sizeof(FLASH_INFO) );
    mExFlashPart.FlashVenDevId = MfgDevId;
    gFlashId = MfgDevId;
    *(UINT32*)(pFlashDeviceNumber + FLASH_PART_STRING_LENGTH - 4) = \
                                                mExFlashPart.FlashCapacity;
    (*FlashStruct)->FlashProgramSize = Atmel_26DF.PageSize;
    (*FlashStruct)->FlashSectorSize = Atmel_26DF.SectorSize;
    (*FlashStruct)->FlashPartNumber = pFlashDeviceNumber;
    // Update the OpCode to OpMenu immediately if need.
    ReinitializeSpiEnvironment ( &mExFlashPart.FlashCommandMenu );
    return  TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   StmCheckMemoryCapacity
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
StmCheckMemoryCapacity  (
    IN UINT32               dVenDevId
)
{
    switch ( ( dVenDevId & 0x00FF0000 ) >> 16 ) {
        case 0x10 : return ( 0x10000 );
        case 0x11 : return ( 0x20000 );
        case 0x12 : return ( 0x40000 );
        case 0x13 : return ( 0x80000 );
        case 0x14 : return ( 0x100000 );
        case 0x15 : return ( 0x200000 );
        case 0x36 : // MX25U32xx 
        case 0x16 : return ( 0x400000 );
        case 0x37 : // MX25U64xx 
        case 0x17 : return ( 0x800000 );
        case 0x18 : return ( 0x1000000 );
    }
    return ( FLASH_SIZE );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SpansionCheckMemoryCapacity
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
SpansionCheckMemoryCapacity  (
    IN UINT32               dVenDevId
)
{
    switch ( ( dVenDevId & 0x00FF0000 ) >> 16 ) {
        case 0x12 : return ( 0x80000 );
        case 0x13 : return ( 0x100000 );
        case 0x14 : return ( 0x200000 );
        case 0x46 :                         // PMC 25LQ032
        case 0x15 : return ( 0x400000 );
        case 0x16 : return ( 0x800000 );
        case 0x17 : return ( 0x1000000 );
    }
    return ( FLASH_SIZE );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IntelCheckMemoryCapacity
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
IntelCheckMemoryCapacity  (
    IN UINT32               dVenDevId
)
{
    switch ( ( dVenDevId & 0x00FF0000 ) >> 16 ) {
        case 0x11 :
        case 0x15 :   return ( 0x200000 );
        case 0x12 :
        case 0x16 :   return ( 0x400000 );
        case 0x13 :
        case 0x17 :   return ( 0x800000 );
    }
    return ( FLASH_SIZE );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SstCheckMemoryCapacity
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
SstCheckMemoryCapacity  (
    IN UINT32               dVenDevId
)
{
    switch ( ( dVenDevId & 0x00FF0000 ) >> 16 ) {
        case 0x8c :   return ( 0x40000 );
        case 0x8d :   return ( 0x80000 );
        case 0x8e :   return ( 0x100000 );
        case 0x01 :   // SST 26VF016
        case 0x41 :   return ( 0x200000 );
        case 0x02 :   // SST 26VF032
        case 0x4a :   return ( 0x400000 );
        case 0x43 :   // SST 26VF064
        case 0x4b :   return ( 0x800000 );
    }
    return ( FLASH_SIZE );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IdentifySTM_25PExx
//
// Description: This function identifies the supported SPI flash parts and
//              returns appropriate flash device API pointer. If flash part is
//              not supported by this module it will return FALSE.
//              Supports the following SPI parts
//              ST Micro M25P80, M25P40
//
// Input:   pBlockAddress   Block address of the flash part. Can be used to
//                              send ID command
//
// Output:  **FlashApi      Pointer to hold the returned flash API
//
// Return:  TRUE            If flash part is supported, FlashApi contains
//                              routines to handle the flash requests
//          FALSE           Flash part is not supported
//
// Note:   This routine is part of the global flash init list. Make sure
//         it is properly linked to the init list "FlashList" (in SDL file)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IdentifyStm_25PExx  (
    IN  volatile UINT8      *pBlockAddress,
    OUT FLASH_PART          **FlashStruct
)
{
    if ( !CommonSpiReadId( &Stm_25PE, &MfgDevId ) )    return FALSE;
    switch ( (UINT16)MfgDevId ) {
        // erase page size = 256 bytes.
        case STM_25PExx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_256B;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_PAGE_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "STM/Numonyx 25PE Series", 23 );
            break;
        // erase sector size = 4K bytes.
        case SST_26VFxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            mExFlashPart.GlobalBlockUnlock = TRUE;
            mExFlashPart.FlashCapacity = SstCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "SST 26VF Series", 15 );
            break;
        case PMC_25LVxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_PMC25LV_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = \
                                SpansionCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "PMC 25LV/LQ Series", 18 );
            break;
        case AMIC_25Lxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            mExFlashPart.FlashCapacity = \
                                SpansionCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "AMIC 25L Series", 15 );
            break;
        case AMIC_25Lxxx_ID :
        case AMIC_25LQxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "AMIC 25L/LQ Series", 18 );
            break;
        case EON_25Fxx_ID :
        case EON_25Qxx_ID :
        case EON_25QHxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "EON 25F/Q/QH Series", 19 );
            break;         
        case STM_25PXxx_ID :
        case STM_25PFxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy (pFlashDeviceNumber, "STM/Micron/Numonyx 25PF/PX Series", 33);
            break;
        case MXIC_25Lxxxx_ID :
        case MXIC_25Lxx35_ID :
        case MXIC_25Lxx36_ID :
        case MXIC_25Uxx35_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "MXIC 25L/U Series", 17 );
            break;
        case WINBOND_25Xxx_ID :
        case WINBOND_25Qxx_ID :
        case WINBOND_25QxxF_ID :
        case WINBOND_25QxxW_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "Winbond 25X/Q Series", 20 );
            break;
        case GD_25Qxx_ID :
        case GD_25LQxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "GigaDevice 25Q Series", 21 );
            break;
        // erase block size = 64K bytes.
        case EON_25Pxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "EON 25P Series", 14 );
            break;         
        case STM_25Pxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            if (mExFlashPart.FlashCapacity == 0x1000000) {
                Stm_25PE.SectorSize = SECTOR_SIZE_256KB;  
            }       
            MemCpy (pFlashDeviceNumber, "STM/Micron/Numonyx 25P Series", 29);
            break;
        case Numonyx_25Qxx_ID :
        case Numonyx_25QxxA_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy (pFlashDeviceNumber, "Micron/Numonyx 25Q Series", 25);
            break;
        case SPANSION_25FLxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            mExFlashPart.FlashCapacity = \
                                    SpansionCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "Spansion 25FL Series", 19 );
            break;
        case SPANSION_25FLxxxP_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            mExFlashPart.FlashCapacity = \
                                    StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "Spansion 25FL(P) Series", 23 );
            break;
        case INTEL_25Fxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            mExFlashPart.FlashCapacity = IntelCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "Intel/Numonyx 25F160/320", 24 );
            break;
        case FM_25Qxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "FIDELIX 25Q Series", 18 );
            break;
        case ESMT_25Lxx_ID :
        case ESMT_25LxxQ_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_MXIC_M25L_COMMAND_ERASE;
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "ESMT 25L QA/PA Series", 21 );
            break;
        default :
            return  FALSE;
    }
    *FlashStruct = &mCommonSpiFlash;
    MemCpy( &mExFlashPart.FlashCommandMenu, &Stm_25PE, sizeof(FLASH_INFO) );
    mExFlashPart.FlashVenDevId = MfgDevId;
    gFlashId = MfgDevId;
    *(UINT32*)(pFlashDeviceNumber + FLASH_PART_STRING_LENGTH - 4) = \
                                                mExFlashPart.FlashCapacity;
    (*FlashStruct)->FlashProgramSize = Stm_25PE.PageSize;
    (*FlashStruct)->FlashSectorSize = Stm_25PE.SectorSize;
    (*FlashStruct)->FlashPartNumber = pFlashDeviceNumber;
    // Update the OpCode to OpMenu immediately if need.
    ReinitializeSpiEnvironment ( &mExFlashPart.FlashCommandMenu );
    return  TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IdentifySst_25VF
//
// Description: This function identifies the supported SPI flash parts and
//              returns appropriate flash device API pointer. If flash part is
//              not supported by this module it will return FALSE.
//              Supports the following SPI parts
//              SST 25VF040B/080B/016B/032B, ESMT
//
// Input:   pBlockAddress   Block address of the flash part. Can be used to
//                              send ID command
//
// Output:  **FlashApi      Pointer to hold the returned flash API
//
// Return:  TRUE            If flash part is supported, FlashApi contains
//                              routines to handle the flash requests
//          FALSE           Flash part is not supported
//
// Note:   This routine is part of the global flash init list. Make sure
//         it is properly linked to the init list "FlashList" (in SDL file)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IdentifySst_25VF    (
    IN  volatile UINT8      *pBlockAddress,
    OUT FLASH_PART          **FlashStruct
)
{
    if ( !CommonSpiReadId( &Sst_25VF, &MfgDevId ) )    return FALSE;
    switch ( (UINT16)MfgDevId ) {
        case SST_25VFxxx_ID :
            mExFlashPart.FlashCapacity = SstCheckMemoryCapacity( MfgDevId );
            if (mExFlashPart.FlashCapacity >= 0x800000) Sst_25VF.PageSize = 256;
#if defined AAI_WORD_PROGRAM && AAI_WORD_PROGRAM == 1
            else mExFlashPart.AAIWordProgram = TRUE;    
#endif
            MemCpy ( pFlashDeviceNumber, "SST 25VF Series", 15 );
            break;
        case ESMT_25LxxxT_ID :
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            MemCpy ( pFlashDeviceNumber, "ESMT 25L T Series", 17 );
            break;
        case ESMT_25LxxxB_ID :
            mExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            Sst_25VF.WriteStatusEnable.Opcode = 0;
            MemCpy ( pFlashDeviceNumber, "ESMT 25L B Series", 17 );
            break;
        default :   return  FALSE;
    }
    *FlashStruct = &mCommonSpiFlash;
    MemCpy( &mExFlashPart.FlashCommandMenu, &Sst_25VF, sizeof(FLASH_INFO) );
    mExFlashPart.FlashVenDevId = MfgDevId;
    *(UINT32*)(pFlashDeviceNumber + FLASH_PART_STRING_LENGTH - 4) = \
                                                mExFlashPart.FlashCapacity;
    gFlashId = MfgDevId;
    (*FlashStruct)->FlashProgramSize = Sst_25VF.PageSize;
    (*FlashStruct)->FlashSectorSize = Sst_25VF.SectorSize;
    (*FlashStruct)->FlashPartNumber = pFlashDeviceNumber;
    // Update the OpCode to OpMenu immediately if need.
    ReinitializeSpiEnvironment ( &mExFlashPart.FlashCommandMenu );
    return  TRUE;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
