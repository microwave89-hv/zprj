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
// $Header: /Alaska/SOURCE/Flash_Combined_2/Core/LPC/LpcFlashWrite.c 15    12/23/09 6:12a Calvinchen $
//
// $Revision: 15 $
//
// $Date: 12/23/09 6:12a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Flash_Combined_2/Core/LPC/LpcFlashWrite.c $
// 
// 15    12/23/09 6:12a Calvinchen
// Improvement:
// 1.Added FWH/LPC/STD Flash Device Number support.
// 2.Changed for SMIFlash module Label "4.6.3.6_SMIFLASH_12" or later
// 
// 14    12/15/09 5:47a Calvinchen
// Modified for adding Flash chip name support.
// 
// 13    6/24/09 3:13a Calvinchen
// (EIP22177) Updated for Aptio Source Enhancement. 
//
// 12    6/26/08 7:00a Calvinchen
// Generic bug fixed.
//
// 10    5/09/08 3:34a Calvinchen
// Added support for Winbond 39V080AP and STM M50LPW080.
//
// 9     1/11/08 11:33a Robert
//
// 8     1/07/08 3:28p Robert
// Updated for coding standard
//
// 7     11/09/07 4:16p Alexp
// Added dummy FlashRead function. Not supported by this type of flash
// module
//
// 6     3/30/07 12:41p Robert
// coding standard errors
//
// 5     3/26/07 7:22p Robert
// Coding standard updates
//
// 4     2/16/07 3:47p Robert
// Updated the Flash Part Data Structure to contain the Sector Size
// Parameter.  This is just a dummy parameter for LPC parts
//
// 2     1/05/07 3:14p Felixp
// 1. Support for SST49LF080A Device added
// 2. Bug fix in ProgramCommand function
// 3. Clean up
//
// 1     12/18/06 3:39p Robert
// Initial Check in
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        LPCFlashWrite.C
//
// Description: This file contains LPC flash write related code. The
//      following are the flash parts currently supported and/or tested:
//              SST 49LF020A        Tested
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------------
// Includes
#include <efi.h>
#include <AmiDxeLib.h>
#include <FlashPart.h>
#include <token.h>

//----------------------------------------------------------------------------
// Flash part related tokens
#define SST_MANUFACTURER_ID     0xbf
#define SST49LF020A_DEVICE_ID   0x52
#define SST49LF080A_DEVICE_ID   0x5b
#define SST49LF020A             0x52bf
#define SST49LF080A             0x5bbf
#define WINBOND_W39V080A        0xd0da

#define COMMAND_SEQUENCE_1      0xaa
#define COMMAND_SEQUENCE_2      0x55
#define BYTE_PROGRAM_CMD        0xa0
#define BLOCK_ERASE_CMD_1       0x80
#define BLOCK_ERASE_CMD_2       0x30
#define LPC_ID_CMD              0x90
#define LPC_RESET_CMD           0xf0

#define UNLOCK                  0
#define WRITE_LOCK              1

//----------------------------------------------------------------------------
// Module level global data
extern UINT8    pFlashDeviceNumber[FLASH_PART_STRING_LENGTH];

//----------------------------------------------------------------------------
// Function prototypes
EFI_STATUS
InitSstAndCheckId   (
    volatile UINT8      *pBlockAddress
    );
VOID
LpcFlashEraseCommand    (
    volatile UINT8      *pBlockAddress
    );
VOID
LpcFlashReadCommand (
    volatile UINT8      *pByteAddress,
    UINT8               *Data,
    UINT32              *Length
    );
VOID
LpcFlashProgramCommand  (
    volatile UINT8      *pByteAddress,
    UINT8               *Data,
    UINT32              *Length
    );
BOOLEAN
LpcFlashIsEraseCompleted    (
    volatile UINT8      *pBlockAddress,
    BOOLEAN             *pError,
    UINTN               *pStatus
    );
BOOLEAN
LpcFlashIsProgramCompleted  (
    volatile UINT8      *pByteAddress,
    UINT8               *Byte,
    UINT32              Length,
    BOOLEAN             *pError,
    UINTN               *pStatus
    );
VOID
LpcFlashBlockWriteEnable    (
    UINT8               *pBlockAddress
    );
VOID
LpcFlashBlockWriteDisable   (
    UINT8               *pBlockAddress
    );
VOID
LpcFlashDeviceWriteEnable   (
    VOID
    );
VOID
LpcFlashDeviceWriteDisable  (
    VOID
    );
EFI_STATUS
LpcOperationCompleted   (
    volatile UINT8      *pAddress
    );//,
VOID
LpcResetFlash   (
    volatile UINT8      *pBlockAddress
    );
VOID
LpcFlashVirtualFixup    (
    EFI_RUNTIME_SERVICES *pRS
    );
UINT8   gbLpcFlashEraseCommand;
//----------------------------------------------------------------------------
// Module specific variables
FLASH_PART mCommonLpcFlash = {
    LpcFlashReadCommand,            // dummy byte read command
    LpcFlashEraseCommand,           // block erase command
    LpcFlashProgramCommand,         // byte program command
    LpcFlashIsEraseCompleted,       // erase complete identifier command
    LpcFlashIsProgramCompleted,     // program complete identifier command
    LpcFlashBlockWriteEnable,       // block write enable command
    LpcFlashBlockWriteDisable,      // block write disable command
    LpcFlashDeviceWriteEnable,      // write enable command
    LpcFlashDeviceWriteDisable,     // write disable command
    LpcFlashVirtualFixup,           // virtual address fix up routine
    1,                              // Number of bytes to program to the
                                    // Flash part in each program command
    0,                          // Dummy value to hold place - only used in SPI
    NULL                        // Flash Part Number Pointer                   
    };

//----------------------------------------------------------------------------
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   mLpcFlashIdentify
//
// Description: This function identifies the supported Lpc flash parts and
//      returns appropriate flash device API pointer. If flash part is
//      not supported by this module it will return FALSE.
//
//
// Input:   pBlockAddress   Block address of the flash part. Can be used to
//                              send ID command
// Output:  **FlashApi      Pointer to hold the returned flash API
//
// Return:  TRUE            If flash part is supported, FlashApi contains
//                              routines to handle the flash requests
//          FALSE           Flash part is not supported
//
// Note:    This routine is part of the global flash init list. Make sure
//          it is properly linked to the init list "FlashList" (in SDL file)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
mLpcFlashIdentify   (
    IN  volatile UINT8      *pBlockAddress,
    OUT FLASH_PART          **FlashApi
)
{
    EFI_STATUS Status;

    Status = InitSstAndCheckId( pBlockAddress );
    if ( Status != EFI_SUCCESS  ) return FALSE;
    else {
        mCommonLpcFlash.FlashPartNumber = pFlashDeviceNumber;
        *FlashApi = &mCommonLpcFlash;
    }    
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashReadCommand
//
// Description: This function programs a byte data to the specified location
//
// Input:   *pByteAddress   Location where the data to be written
//          Bytes - data to be written.
//          Length - number of bytes to write
//
// Output:  Length - number of bytes that were not written
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
LpcFlashReadCommand (
    IN      volatile UINT8  *pByteAddress,
    IN OUT  UINT8           *Byte,
    IN OUT  UINT32          *Length
)
{
    UINT32              dNumBytes = 0;
    
    // Changes for SMIFlash module label "4.6.3.6_SMIFLASH_12" or later.
    for ( dNumBytes = 0; dNumBytes < *Length ; dNumBytes++ )
        *( Byte + dNumBytes ) = *(UINT8*)((UINT32)pByteAddress + dNumBytes );
    *Length = 0;
    return ;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashEraseCommand
//
// Description: This API function erases a block in the flash. Flash model
//              specific code will branch out from this routine
//
// Input:       pBlockAddress   Block that need to be erased
//
// Output:      Nothing
//
// Return:      Nothing
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
LpcFlashEraseCommand    (
    IN volatile UINT8       *pBlockAddress
)
{
    EFI_STATUS          Status;
    UINT8               bFlashRetry;

    LpcResetFlash ( pBlockAddress );
    for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
        pBlockAddress[0x5555] = COMMAND_SEQUENCE_1;
        pBlockAddress[0x2aaa] = COMMAND_SEQUENCE_2;
        pBlockAddress[0x5555] = BLOCK_ERASE_CMD_1;
        pBlockAddress[0x5555] = COMMAND_SEQUENCE_1;
        pBlockAddress[0x2aaa] = COMMAND_SEQUENCE_2;
        *pBlockAddress = gbLpcFlashEraseCommand;
        Status = LpcOperationCompleted( pBlockAddress );
        LpcResetFlash ( pBlockAddress );
        if ( Status != EFI_SUCCESS ) continue;
        if ( *pBlockAddress != 0xFF ) Status = EFI_DEVICE_ERROR;
        else {
            Status = EFI_SUCCESS;
            break;
        }
    }
//-    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcOperationCompleted
//
// Description: This function verifies whether the previous (erase or
//              program) command is completed and returns the status
//              of the command
//
// Input:   *pAddress   Location of the previous operation
//
// Output:  *pError     True on error and false on success
//          *Status     Error status code (0 - Success)
//
// Return:  TRUE        If operation completed successfully
//                          *pError = FALSE, *pStatus = 0
//          FALSE       If operation failed
//                          *pError = TRUE, *pStatus = error status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
LpcOperationCompleted   (
    IN volatile UINT8       *pAddress
)
{
    UINT8                   bData1, bData2;
    UINT32                  dTimeout = FLASH_RETRIES * 0x10000;
    EFI_STATUS              Status = EFI_TIMEOUT;

    do {
        bData1 = (*pAddress) & 0x40;
        bData2 = (*pAddress) & 0x40;
        if ( bData1 == bData2 ) return EFI_SUCCESS;
        dTimeout--;
    } while ( dTimeout != 0 );                 // Check for Bit 6 Toggle
    return EFI_TIMEOUT;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashProgramCommand
//
// Description: This function programs a byte data to the specified location
//
// Input:   *pByteAddress   Location where the data to be written
//          *Data - Byte to be written
//          *Length - Number of bytes to write
//
// Output:  *Length - Number of bytes left to write
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
LpcFlashProgramCommand  (
    IN      volatile UINT8  *pByteAddress,
    IN      UINT8           *Data,
    IN OUT  UINT32          *Length
)
{
    volatile UINT8* pBlockAddress = (volatile UINT8 *)BLOCK(pByteAddress);
    UINT8           bFlashRetry;
    EFI_STATUS      Status;

    if (*Data != *pByteAddress)
    {
        LpcResetFlash ( pBlockAddress );
        for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
            // Program Command Sequence
            pBlockAddress[0x5555] = COMMAND_SEQUENCE_1;
            pBlockAddress[0x2aaa] = COMMAND_SEQUENCE_2;
            pBlockAddress[0x5555] = BYTE_PROGRAM_CMD;
            *pByteAddress=*Data;
            Status = LpcOperationCompleted ( pByteAddress );
            if ( Status != EFI_SUCCESS ) continue;
            if ( *pByteAddress != *Data ) Status = EFI_DEVICE_ERROR;
            else {
                Status = EFI_SUCCESS;
                break;
            }
        }
        LpcResetFlash ( pBlockAddress );
    } else Status = EFI_SUCCESS;
    *Length = *Length - 1;
//-    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashIsEraseCompleted
//
// Description: This function verifies whether the block erase
//              command is completed and returns the status of the command
//
// Input:       *pBlockAddress  Location of the block erase
//
// Output:      *pError         True on error and false on success
//              *Status         Error status code (0 - Success)
//
// Return:      TRUE        If operation completed successfully
//                          *pError = FALSE, *pStatus = 0
//              FALSE       If operation failed
//                          *pError = TRUE, *pStatus = error status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
LpcFlashIsEraseCompleted    (
    IN  volatile UINT8      *pBlockAddress,
    OUT BOOLEAN             *pError,
    OUT UINTN               *pStatus
)
{
    UINT32                      dNumBytes;

    for ( dNumBytes = 0; dNumBytes < FlashBlockSize; dNumBytes++ ) {
        if ( *(volatile UINT8*)( pBlockAddress + dNumBytes ) != 0xFF ) {
            if ( pError ) *pError = TRUE;
            if ( pStatus ) *pStatus = EFI_DEVICE_ERROR;
            return FALSE;
        }
    }
    if ( pError ) *pError = FALSE;
    if ( pStatus ) *pStatus = EFI_SUCCESS;
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashIsProgramCompleted
//
// Description: This function verifies whether the program (page or byte)
//              command is completed and returns the status of the command
//
// Input:   *pByteAddress - Location of the program command
//          *Byte - Last data byte written
//          Length - Amount of data that was written
//
// Output:  *pError - True on error and false on success
//          *Status - Error status code (0 - Success)
//
// Return:  TRUE        If operation completed successfully
//                          *pError = FALSE, *pStatus = 0
//          FALSE       If operation failed
//                          *pError = TRUE, *pStatus = error status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
LpcFlashIsProgramCompleted  (
    IN  volatile UINT8      *pByteAddress,
    IN  UINT8               *Byte,
    IN  UINT32              Length,
    OUT BOOLEAN             *pError,
    OUT UINTN               *pStatus
)
{
    UINT32                      dNumBytes;
    UINT8                       bByte;

    for ( dNumBytes = 0; dNumBytes < Length; dNumBytes++ ) {
        bByte = * ( Byte + dNumBytes );
        if ( bByte != *(volatile UINT8*)( pByteAddress + dNumBytes ) ) {
            if ( pError ) *pError = TRUE;
            if ( pStatus ) *pStatus = EFI_DEVICE_ERROR;
            return FALSE;
        }
    }
    if ( pError ) *pError = FALSE;
    if ( pStatus ) *pStatus = EFI_SUCCESS;
    return TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetBlockLock
//
// Description: This function programs a page of data at a time
//
// Input:      volatile UINT8* pBlockAddress - This is location where the data
//                  is to be written
//              UINT8 LockState - Value to use to set the Lock register for the
//                  block defined by pBlockAddress
//
// Output:      None
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
void
SetBlockLock    (
    IN volatile UINT8*      pBlockAddress,
    IN UINT8                LockState
)
{
    // Update the block lock register
    ((UINT8*)((UINTN)pBlockAddress - FlashDeviceBase + \
                                        FwhFeatureSpaceBase))[2] = LockState;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashBlockWriteEnable
//
// Description: This function contains any flash specific code need to
//              enable a particular flash block write
//
// Input:       None
//
// Output:      None
//
// Return:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
LpcFlashBlockWriteEnable    (
    IN UINT8                *pBlockAddress
)
{
    SetBlockLock(pBlockAddress, UNLOCK);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashBlockWriteDisable
//
// Description: This function contains any flash specific code need to
//              disable a particular flash block write
//
// Input:       None
//
// Output:      None
//
// Return:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
LpcFlashBlockWriteDisable   (
    IN UINT8                *pBlockAddress
)
{
    SetBlockLock(pBlockAddress, WRITE_LOCK);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashDeviceWriteEnable
//
// Description: This function contains any flash specific code need to
//              enable flash write
//
// Input:       None
//
// Output:      None
//
// Return:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
LpcFlashDeviceWriteEnable (VOID)
{
    // Flash device does not support this feature
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashDeviceWriteDisable
//
// Description: This function contains any flash specific code need to
//              disable flash write
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
LpcFlashDeviceWriteDisable (VOID)
{
    // Flash device does not support this feature
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcFlashVirtualFixup
//
// Description: This function will be invoked by the core to convert
//              runtime pointers to virtual address
//
// Input:       *pRS    Pointer to runtime services
//
// Output:      None
//
// Return:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID
LpcFlashVirtualFixup    (
    IN EFI_RUNTIME_SERVICES *pRS
)
{
//  // Following is an example code for virtual address conversion
//  pRS->ConvertPointer(0, (VOID**)&FlashDeviceBase);

    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LpcResetFlash
//
// Description: This function resets the Lpc flash part
//
// Input:       None
//
// Output:      None
//
// Return:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID
LpcResetFlash   (
    IN volatile UINT8*      pBlockAddress)
{
    pBlockAddress[0x5555] = COMMAND_SEQUENCE_1;
    pBlockAddress[0x2aaa] = COMMAND_SEQUENCE_2;
    pBlockAddress[0x5555] = LPC_RESET_CMD;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitSstAndCheckId
//
// Description: This function checks whether the flash device on the system
//              is SST Lpc flash
//
//
// Input:       None
//
// Output:      None
//
// Return:      TRUE            If flash part is identified as SST
//              FALSE           If non-SST Lpc flash part identified
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InitSstAndCheckId   (
    IN volatile UINT8*      pBlockAddress
)
{
    UINT8               ManfactureID, DeviceID;

    LpcResetFlash(pBlockAddress);
    pBlockAddress[0x5555] = COMMAND_SEQUENCE_1;
    pBlockAddress[0x2aaa] = COMMAND_SEQUENCE_2;
    pBlockAddress[0x5555] = LPC_ID_CMD;
    ManfactureID = *pBlockAddress;
    DeviceID = *(pBlockAddress + 1);
    LpcResetFlash(pBlockAddress);
    switch ( ( DeviceID << 8 ) + ManfactureID ) {
        case SST49LF020A :
        case SST49LF080A :
            gbLpcFlashEraseCommand = 0x50;
            MemCpy ( pFlashDeviceNumber, "SST 49LF020/080A", 16 );
            break;
        case WINBOND_W39V080A :
            gbLpcFlashEraseCommand = 0x30;
            MemCpy ( pFlashDeviceNumber, "Winbond W39V080A", 16 );
            break;
        default :
            return EFI_NOT_FOUND;
    }
    return EFI_SUCCESS;
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