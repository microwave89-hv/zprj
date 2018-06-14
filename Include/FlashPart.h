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
// $Header: /Alaska/SOURCE/Flash_Combined_2/Core/FlashPart.h 14    12/15/09 5:46a Calvinchen $
//
// $Revision: 14 $
//
// $Date: 12/15/09 5:46a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Flash_Combined_2/Core/FlashPart.h $
// 
// 14    12/15/09 5:46a Calvinchen
// Improvement : Added Flash Chip Name support.
// 
// 13    6/24/09 3:11a Calvinchen
// (EIP22177) Updated for Aptio Source Enhancement. 
//
// 11    1/08/08 2:23p Robert
//
// 10    11/09/07 3:47p Alexp
// Added common FlashRead function.
//
// 9     10/09/07 5:47p Robert
// removed data structure that was added by mistake
//
// 7     2/21/07 11:52a Robert
// Removed unneeded extern definition
//
// 6     2/20/07 6:42p Robert
// added packing for the data structures in the flash module
//
// 5     2/16/07 3:50p Robert
// Updated the Flash_Part data structure to contain the FlashSectorSize
// parameter so that SPI parts could contain this information in its
// Identification Structure.  It is used to define the erase sector size
// for SPI parts
//
// 3     12/29/06 3:03p Felixp
//
// 2     12/20/06 1:47p Felixp
// Bug fix in BLOCK macro
//
// 1     12/18/06 3:39p Robert
// Initial Check in
//
// 1     10/31/06 2:30p Sivagarn
// Initial Checkin
//
//
//**********************************************************************

#ifndef __FLASH_H_
#define __FLASH_H_
#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

#include <Flash.h>


//============================================================================
// Flash part module function prototypes

typedef VOID (EFIAPI *FLASH_READ_COMMAND) (
    volatile UINT8* pByteAddress, 
    UINT8           *Byte, 
    UINT32          *Length
    );
typedef VOID (EFIAPI *FLASH_ERASE_COMMAND) (
    volatile UINT8* pBlockAddress
    );
typedef VOID (EFIAPI *FLASH_PROGRAM_COMMAND) (
    volatile UINT8* pByteAddress, 
    UINT8           *Byte, 
    UINT32          *Length
    );
typedef VOID (EFIAPI *FLASH_PAGE_PROGRAM_COMMAND) (
    volatile UINT8* pByteAddress, 
    UINT8*          Byte
    );
typedef BOOLEAN (EFIAPI *FLASH_IS_ERASE_COMPLETED) (
    volatile UINT8* pBlockAddress, 
    BOOLEAN         *pError, 
    UINTN           *pStatus
    );
typedef BOOLEAN (EFIAPI *FLASH_IS_PROGRAM_COMPLETED)(
    volatile UINT8* pByteAddress, 
    UINT8           *Byte, 
    UINT32          Length, 
    BOOLEAN         *pError, 
    UINTN           *pStatus
    );
typedef VOID (EFIAPI *FLASH_BLOCK_WRITE_ENABLE) (
    UINT8*          pBlockAddress
    );
typedef VOID (EFIAPI *FLASH_BLOCK_WRITE_DISABLE) (
    UINT8*          pBlockAddress
    );
typedef VOID (EFIAPI *FLASH_DEVICE_WRITE_ENABLE)(VOID);
typedef VOID (EFIAPI *FLASH_DEVICE_WRITE_DISABLE)(VOID);
typedef VOID (EFIAPI *FLASH_VIRTUAL_FIXUP)(EFI_RUNTIME_SERVICES *pRS);


//============================================================================
// Flash Part Structure Types

//<AMI_STHDR_START>
//============================================================================
// Structure:   OPCODE_CMD
//
// Description: This structure contains data that describe the different
//      commands for the flash parts
//
// Fields:
//      Opcode - UINT8 - Contains the command value
//      OpcodeType - UINT8 - Contains the type of command
//              - Read no Address
//              - Write no Address
//              - Read with Address
//              - Write with Address
//
// Referral:
//      None
//============================================================================
//<AMI_STHDR_END>
typedef struct _OPCODE_CMD
    {
    UINT8   Opcode;
    UINT8   OpcodeType;
    } OPCODE_CMD;

//<AMI_STHDR_START>
//============================================================================
// Structure:   FLASH_INFO
//
// Description:
//      This structure contains data that describe flash part
//      information that is needed for each family of parts for the
//      interface to work properly
//
// Fields:
//      Write - OPCODE_CMD - Contains data for the Command for the part
//      Read - OPCODE_CMD - Contains data for the Command for the part
//      Erase - OPCODE_CMD - Contains data for the Command for the part
//      ReadStatus - OPCODE_CMD - Contains data for the Command for the part
//      ReadId - OPCODE_CMD - Contains data for the Command for the part
//      WriteStatus - OPCODE_CMD - Contains data for the Command for the part
//      WriteStatusEnable - OPCODE_CMD - Contains data for the Command for
//              the part
//      WriteEnable - OPCODE_CMD - Contains data for the Command for the part
//      PageSize - UINT32 - the number of bytes that can be
//              programed into the part with one write command
//      SectorSize - UINT32 - The size of the area to be erased by the
//              Erase command
//
// Referral:
//      OPCODE_CMD
//============================================================================
//<AMI_STHDR_END>
typedef struct _FLASH_INFO {
    OPCODE_CMD  Write;
    OPCODE_CMD  Read;
    OPCODE_CMD  Erase;
    OPCODE_CMD  ReadStatus;
    OPCODE_CMD  ReadId;
    OPCODE_CMD  WriteStatus;
    OPCODE_CMD  WriteStatusEnable;
    OPCODE_CMD  WriteEnable;
    UINT32      PageSize;
    UINT32      SectorSize;
    } FLASH_INFO;


//<AMI_STHDR_START>
//============================================================================
// Structure:   FLASH_WRITE_DATA
//
// Description: This structure contains variables that define the data to be
//      read from or written to the flash part
//
// Fields:
//      Data - BOOLEAN - Defines whether this read or write command has data
//          associated with it
//      Length - UINT32 - Defines the amount of data to be read or written
//      Values - UINT8 * - Pointer to a buffer that can contain the data
//
// Referral:
//      None
//============================================================================
//<AMI_STHDR_END>
typedef struct _FLASH_WRITE_DATA {
    BOOLEAN     Data;
    UINT32      Length;
    UINT8       *Values;
    }FLASH_WRITE_DATA;

//<AMI_STHDR_START>
//============================================================================
// Structure:   FLASH_PART
//
// Description: This structure defines the generic interface for the flash part
//
// Fields:
//      FlashReadCommand - FLASH_READ_COMMAND - generic flash function for
//          reading the flash part
//      FlashEraseCommand - FLASH_ERASE_COMMAND - generic flash function for
//          erasing the flash part
//      FlashProgramCommand - FLASH_PROGRAM_COMMAND - generic flash function
//          for programming the flash part
//      FlashIsEraseCompleted - FLASH_IS_ERASE_COMPLETED - generic flash
//          function for checking if the erase command is finished
//      FlashIsProgramCompleted - FLASH_IS_PROGRAM_COMPLETED - generic flash
//          function for checking if the program command is finished
//      FlashBlockWriteEnable - FLASH_BLOCK_WRITE_ENABLE - generic flash
//          function for write enabling the defined block in the flash part
//      FlashBlockWriteDisable - FLASH_BLOCK_WRITE_DISABLE - generic flash
//          function for write disabling the defined block in the flash part
//      FlashDeviceWriteEnable - FLASH_DEVICE_WRITE_ENABLE - generic flash
//          function for write enabling the flash part
//      FlashDeviceWriteDisable - FLASH_DEVICE_WRITE_DISABLE - generic flash
//          function for write disabling the flash part
//      FlashVirtualFixup - FLASH_VIRTUAL_FIXUP - generic flash function for
//          providing the virtual addressing fixups needed for the flash
//          routines to work during runtime
//      FlashProgramSize - UINT32 - the amount of data that can be
//          programmed into the flash part during one program command
//      FlashSectorSize - UINT32 - the size of area that is erased from
//          the flash part during an erase command
//
// Referral:
//      The types mentioned above are pointers to functions
//
//============================================================================
//<AMI_STHDR_END>
typedef struct _FLASH_PART {
    FLASH_READ_COMMAND              FlashReadCommand;
    FLASH_ERASE_COMMAND             FlashEraseCommand;
    FLASH_PROGRAM_COMMAND           FlashProgramCommand;
    FLASH_IS_ERASE_COMPLETED        FlashIsEraseCompleted;
    FLASH_IS_PROGRAM_COMPLETED      FlashIsProgramCompleted;
    FLASH_BLOCK_WRITE_ENABLE        FlashBlockWriteEnable;
    FLASH_BLOCK_WRITE_DISABLE       FlashBlockWriteDisable;
    FLASH_DEVICE_WRITE_ENABLE       FlashDeviceWriteEnable;
    FLASH_DEVICE_WRITE_DISABLE      FlashDeviceWriteDisable;
    FLASH_VIRTUAL_FIXUP             FlashVirtualFixup;
    UINT32                          FlashProgramSize;
    UINT32                          FlashSectorSize;
    UINT8                           *FlashPartNumber;    
    } FLASH_PART;

extern UINTN FwhFeatureSpaceBase;


#pragma pack(pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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