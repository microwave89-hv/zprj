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

//*************************************************************************
// $Header: /Alaska/SOURCE/Flash_Combined_2/Core/STD/StdMxicFlashWrite.c 7     1/20/12 5:00a Calvinchen $
//
// $Revision: 7 $
//
// $Date: 1/20/12 5:00a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Flash_Combined_2/Core/STD/StdMxicFlashWrite.c $
// 
// 7     1/20/12 5:00a Calvinchen
// Added support for SST 39VF160x/320x.
// 
// 6     7/21/11 5:11a Calvinchen
// 
// 5     2/10/11 5:39a Calvinchen
// [TAG]  		EIP50771
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Sometime vendor id return incorrect value. 
// [RootCause]  	There should have a 10ns delay according SSTVF1681
// specification.
// [Solution]  	Added an IO delay before read Vendor/Device ID. 
// [Files]  		StdMxicFlashWrite.c
// 
// 4     12/23/09 6:13a Calvinchen
// Improvement:
// 1.Added FWH/LPC/STD Flash Device Number support.
// 2.Changed for SMIFlash module Label "4.6.3.6_SMIFLASH_12" or later
// 
// 3     12/15/09 5:50a Calvinchen
// 1. Modified for adding flash chip name support.
// 2. Bug fixed : Programming failed with SST 39VF1681.
// 
// 2     11/16/09 1:51a Calvinchen
// 
// 1     11/02/09 4:34a Calvinchen
// Added support for MXIC 29LV640DB/T and SST SST39VF1681/1682.
//
//
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:    MxicFlashWrite.c
//
// Description: Flash update routines
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
// Includes
#include <efi.h>
#include <AmiDxeLib.h>
#include "FlashPart.h"
#include "token.h"


//----------------------------------------------------------------------
// Local MACRO Definitions
#define UNLOCK              0
#define LOCK                1
#define SECTOR_SIZE_8KB     0x2000          // 8kbytes sector size
#define SECTOR_SIZE_64KB    0x10000        // 64kBytes sector size

//----------------------------------------------------------------------------
// Flash Part Specific Definitions

#define Mx29LV640DB     0xcbc2
#define Mx29LV640DT     0xc9c2
#define Sst39VF1601     0x4bbf
#define Sst39VF1602     0x4abf
#define Sst39VF1681     0xc8bf
#define Sst39VF1682     0xc9bf
#define Sst39VF3201     0x5bbf
#define Sst39VF3202     0x5abf
#define Stm29W160ET     0xc420
#define Stm29W160EB     0x4920

//----------------------------------------------------------------------------
// Module level global data
extern UINT8    pFlashDeviceNumber[FLASH_PART_STRING_LENGTH];

//----------------------------------------------------------------------------
// Function Prototypes
VOID
MxicFlashEraseCommand   (
    volatile UINT8      *pBlockAddress
    );
VOID
MxicFlashReadCommand    (
    volatile UINT8      *pByteAddress,
    UINT8               *Data,
    UINT32              *Length
    );
VOID
MxicFlashProgramCommand (
    volatile UINT8      *pByteAddress,
    UINT8               *Data,
    UINT32              *Length
    );
BOOLEAN
MxicFlashIsEraseCompleted   (
    volatile UINT8      *pBlockAddress,
    BOOLEAN             *pError,
    UINTN               *pStatus
    );
BOOLEAN
MxicFlashIsProgramCompleted (
    volatile UINT8      *pByteAddress,
    UINT8               *Byte, 
    UINT32              Length,
    BOOLEAN             *pError, 
    UINTN               *pStatus
    );
VOID 
MxicFlashBlockWriteEnable   (
    UINT8*              pBlockAddress
    );
VOID
MxicFlashBlockWriteDisable  (
    UINT8*              pBlockAddress
    );
VOID 
MxicFlashDeviceWriteEnable  (
    VOID
    );
VOID 
MxicFlashDeviceWriteDisable (
    VOID
    );
VOID 
MxicFlashVirtualFixup   (
    EFI_RUNTIME_SERVICES *pRS
    );

extern FLASH_PART   *FlashAPI;
//----------------------------------------------------------------------------
// Module specific variables
FLASH_PART mStdMxicFlash =
    {
        MxicFlashReadCommand,
        MxicFlashEraseCommand,
        MxicFlashProgramCommand,
        MxicFlashIsEraseCompleted,
        MxicFlashIsProgramCompleted,
        MxicFlashBlockWriteEnable,
        MxicFlashBlockWriteDisable,
        MxicFlashDeviceWriteEnable,
        MxicFlashDeviceWriteDisable,
        MxicFlashVirtualFixup,  // Mxic flash device virtual address 
                                // fix up routine
        1,                      // Number of bytes to program to the
                                // Flash part in each program command
        SECTOR_SIZE_64KB,       // Dummy value to hold place - only used in SPI
        NULL                    // Flash Part Number Pointer                   
    };

//----------------------------------------------------------------------------
// Function definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicResetFlash
//
// Description: This function resets the Mxic flash part
//
// Input:   None
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
MxicResetFlash  ( 
    IN volatile UINT8*      pAddress 
)
{
    *pAddress = 0xf0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicWriteBufferAbortReset
//
// Description: This function resets the Mxic flash part
//
// Input:   None
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
MxicWriteBufferAbortReset   (
    IN volatile UINT8*      pAddress 
)
{
    pAddress[0xaaa] = 0xaa;
    pAddress[0x555] = 0x55;
    pAddress[0xaaa] = 0xf0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicFlashReadCommand
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

static 
VOID 
MxicFlashReadCommand    (
    IN  volatile UINT8*     pByteAddress, 
    OUT UINT8               *Byte, 
    OUT UINT32              *Length
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
// Procedure:   MxicStdWaitForOperationCompleted
//
// Description:
//      This function verifies whether the command sent to the FWH part
//      has completed and returns the status of the command
//
// Input:
//  IN volatile UINT8*  pAddress    Location to check the device status
//
// Output:
//      EFI_SUCCESS -
//      EFI_TIMEOUT -
//      EFI_DEVICE_ERROR -
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
EFI_STATUS 
MxicStdWaitForOperationCompleted (
    IN volatile UINT8*      pAddress
)
{
    UINT8                   bData1, bData2;
    UINT32                  dTimeout = FLASH_RETRIES * 0x1000000;
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
// Procedure:   MxicFlashEraseCommand
//
// Description: This API function erases a block in the flash. Flash model
//              specific code will branch out from this routine
//
// Input:       pBlockAddress   Block that need to be erased
//
// Output:      Nothing
//
// Returns:     None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
MxicFlashEraseCommand   (
    IN volatile UINT8*      pBlockAddress
)
{
    EFI_STATUS          Status;
    UINT8               bFlashRetry;
    UINT16              wNumSectors, wSector;
    UINT32              i;
    volatile UINT8*     pSectorAddr;

    MxicWriteBufferAbortReset ( pBlockAddress );
    wNumSectors = ( FlashBlockSize / FlashAPI->FlashSectorSize );    
    for ( wSector = 0; wSector < wNumSectors; wSector++ ) {
        pSectorAddr = pBlockAddress + wSector * FlashAPI->FlashSectorSize;
        for ( i = 0; i < FlashAPI->FlashSectorSize; i++ ) {
            if ( *(pSectorAddr + i) != 0xFF ) break;
        }
        if ( i == FlashAPI->FlashSectorSize ) break;
        for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
            pSectorAddr[0xaaa] = 0xaa;
            pSectorAddr[0x555] = 0x55;
            pSectorAddr[0xaaa] = 0x80;
            pSectorAddr[0xaaa] = 0xaa;
            pSectorAddr[0x555] = 0x55;
            *pSectorAddr = 0x30;
            Status = MxicStdWaitForOperationCompleted ( pSectorAddr );
            MxicWriteBufferAbortReset ( pSectorAddr );
            if ( Status != EFI_SUCCESS ) continue;
            if ( *pSectorAddr != 0xFF ) Status = EFI_DEVICE_ERROR;
            else {
                Status = EFI_SUCCESS;
                break;
            }
        }
    }       
//-    return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicFlashIsEraseCompleted
//
// Description: This function verifies whether the block erase
//              command is completed and returns the status of the command
//
// Input:   *pBlockAddress  Location of the block erase
//
// Output:  *pError         True on error and false on success
//          *Status         Error status code (0 - Success)
//
// Return:  TRUE        If operation completed successfully
//                          *pError = FALSE, *pStatus = 0
//          FALSE       If operation failed
//                          *pError = TRUE, *pStatus = error status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
BOOLEAN 
MxicFlashIsEraseCompleted   (
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
// Procedure:   MxicFlashProgramCommand
//
// Description: This function programs a byte data to the specified location
//
// Input:   *pByteAddress - Location where the data to be written
//          *Byte - Byte to be written
//          *Length - Number of bytes to write
//
// Output:  *Length - Number of bytes still left to write
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
MxicFlashProgramCommand (
    IN volatile UINT8*      pByteAddress,
    IN UINT8                *Byte,
    IN OUT UINT32           *Length
)
{
    volatile UINT8* pBlockAddress = (volatile UINT8*)BLOCK(pByteAddress);
    UINT8           bFlashRetry;
    EFI_STATUS      Status = EFI_SUCCESS;


    if ( *Byte != *pByteAddress ) {
        MxicWriteBufferAbortReset ( pBlockAddress );
        for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
            // Program Command Sequence
            pBlockAddress[0xaaa] = 0xaa;
            pBlockAddress[0x555] = 0x55;
            pBlockAddress[0xaaa] = 0xa0;
            *pByteAddress = *Byte;
            Status = MxicStdWaitForOperationCompleted ( pBlockAddress );
//            MxicWriteBufferAbortReset ( pBlockAddress );
            if ( Status != EFI_SUCCESS ) continue;
            if ( *pByteAddress != *Byte ) Status = EFI_DEVICE_ERROR;
            else {
                Status = EFI_SUCCESS;
                break;
            }
        }
    } else Status = EFI_SUCCESS;
    *Length = *Length - 1;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicFlashIsProgramCompleted
//
// Description: This function verifies whether the program (page or byte)
//              command is completed and returns the status of the command
//
// Input:   *pByteAddress   Location of the program command
//          *Byte           Pointer to data written
//          Length          Amount of data to check
//
// Output:  *pError         True on error and false on success
//          *Status         Error status code (0 - Success)
//
// Return:  TRUE        If operation completed successfully
//                          *pError = FALSE, *pStatus = 0
//          FALSE       If operation failed
//                          *pError = TRUE, *pStatus = error status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
BOOLEAN 
MxicFlashIsProgramCompleted (
    IN  volatile UINT8*         pByteAddress,
    IN  UINT8                   *Byte, 
    IN  UINT32                  Length,
    OUT BOOLEAN                 *pError,
    OUT UINTN                   *pStatus
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
// Procedure:   MxicFlashBlockWriteEnable
//
// Description: This function contains any flash specific code need to
//      enable a particular flash block write
//
// Input:   None
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
MxicFlashBlockWriteEnable   (
    IN UINT8*               pBlockAddress
)
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicFlashBlockWriteDisable
//
// Description: This function contains any flash specific code need to
//      disable a particular flash block write
//
// Input:   None
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
MxicFlashBlockWriteDisable  (
    IN UINT8*               pBlockAddress
)
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicFlashDeviceWriteEnable
//
// Description: This function contains any flash specific code need to
//      enable flash write
//
// Input:   None
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
MxicFlashDeviceWriteEnable (VOID)
{
    //We don't have to do anything here because
    //Flash Device is write enabled by the South Bridge driver
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicFlashDeviceWriteDisable
//
// Description: This function contains any flash specific code need to
//      disable flash write
//
// Input:   None
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
MxicFlashDeviceWriteDisable (VOID)
{
    //We don't have to do anything here because
    //we always keep flash device in the write enabled state
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MxicFlashVirtualFixup
//
// Description: This function will be invoked by the core to convert
//      runtime pointers to virtual address
//
// Input:   *pRS    Pointer to runtime services
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static
VOID
MxicFlashVirtualFixup(
    IN EFI_RUNTIME_SERVICES *pRS
)
{

//  // Following is an example code for virtual address conversion
//  pRS->ConvertPointer(0, (VOID**)&FlashDeviceBase);

    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   mStdMxicIdentify
//
// Description: This function identifies the supported Mxic flash part and
//      returns appropriate flash device API pointer. If flash part is
//      not supported by this module it will return FALSE.
//
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
// Note:    This routine is part of the global flash init list. Make sure
//      it is properly linked to the init list "FlashList" (in SDL file)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
mStdMxicIdentify (
    IN  volatile UINT8*     pBlockAddress,
    OUT FLASH_PART          **Struct
)
{
    UINT8   bVenID, bDevID_1, bDevID_2;

    MxicWriteBufferAbortReset( pBlockAddress );

    pBlockAddress[0xaaa] = 0xaa;
    pBlockAddress[0x555] = 0x55;
    pBlockAddress[0xaaa] = 0x90;
    // Delay before read flash ID.
    IoWrite8 ( 0xeb, 0x55 );
    bVenID = *pBlockAddress;
    bDevID_1 = *(pBlockAddress + 0x01);
    bDevID_2 = *(pBlockAddress + 0x02);

    MxicWriteBufferAbortReset( pBlockAddress );

    // Check for SST39VF1681/1682 support.
    switch ((bDevID_1 << 8) + bVenID) {
        case Sst39VF1601:
        case Sst39VF1602:
        case Sst39VF1681:
        case Sst39VF1682:
        case Sst39VF3201:
        case Sst39VF3202:
            MemCpy ( pFlashDeviceNumber, "SST 39VF1681/1682/3201/3202", 27 );
            mStdMxicFlash.FlashPartNumber = pFlashDeviceNumber; 
            *Struct = &mStdMxicFlash;
            return TRUE;             
        case Stm29W160ET:
        case Stm29W160EB:
            MemCpy ( pFlashDeviceNumber, "ST M29W160B/T", 13 );
            mStdMxicFlash.FlashSectorSize = SECTOR_SIZE_8KB;
            mStdMxicFlash.FlashPartNumber = pFlashDeviceNumber; 
            *Struct = &mStdMxicFlash;
            return TRUE;             
    }
    // Check for Mxic 29LV640DB/T support.
    switch ((bDevID_2 << 8) + bVenID) {
        case Mx29LV640DB:
        case Mx29LV640DT:
            MemCpy ( pFlashDeviceNumber, "MXIC 29LV640B/T", 15 );
            mStdMxicFlash.FlashPartNumber = pFlashDeviceNumber; 
            *Struct = &mStdMxicFlash;
            return TRUE;             
    }
    return FALSE;
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
