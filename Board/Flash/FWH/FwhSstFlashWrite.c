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
// $Header: /Alaska/SOURCE/Flash_Combined_2/Core/FWH/FwhSstFlashWrite.c 13    12/23/09 6:12a Calvinchen $
//
// $Revision: 13 $
//
// $Date: 12/23/09 6:12a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Flash_Combined_2/Core/FWH/FwhSstFlashWrite.c $
// 
// 13    12/23/09 6:12a Calvinchen
// Improvement:
// 1.Added FWH/LPC/STD Flash Device Number support.
// 2.Changed for SMIFlash module Label "4.6.3.6_SMIFLASH_12" or later
// 
// 12    12/15/09 5:47a Calvinchen
// Modified for adding flash chip name support.
// 
// 11    6/24/09 3:12a Calvinchen
// (EIP22177) Updated for Aptio Source Enhancement. 
//
// 10    6/26/08 6:59a Calvinchen
// Generic bug fixed.
//
// 8     5/09/08 3:33a Calvinchen
//
// 7     12/07/07 1:47p Stacyh
// Updated to differentiate between LPC and FWH SST parts.
//
// 6     11/09/07 4:15p Alexp
// Added dummy FlashRead function. Not supported by this type of flash
// module
//
// 5     5/24/07 12:07p Fasihm
// Updated code to match the code review standards.
//
// 4     3/26/07 7:22p Robert
// Coding standard updates
//
// 3     2/16/07 3:47p Robert
// Updated the Flash Part Data Structure to contain the Sector Size
// Parameter.  This is just a dummy parameter for Firmware Hub
//
// 2     12/20/06 10:16a Felixp
// Bug fix in SetLockState. Function updated to work in virtual addressing
// mode
// (after SetVirtualAddress map has been called).
//
// 1     12/18/06 3:39p Robert
// Initial Check in
//
//
//**********************************************************************

//<AMI_FHDR_START>
//
// Name:    FlashWrite.c
//
// Description: Flash update routines
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
// Includes
#include <efi.h>
#include <AmiDxeLib.h>  //QUANTA_CHANGES
#include "FlashPart.h"
#include "token.h"


//----------------------------------------------------------------------
// Local MACRO Definitions
#define UNLOCK 0
#define LOCK 1

//----------------------------------------------------------------------------
// Flash Part Specific Definitions

#define VENDOR_ID           0xbf // Intel Manufacturers ID
#define DEVICE_ID0          0x60 // 512K Firmware Hub
#define DEVICE_ID1          0x5a // 1 Meg Firmware Hub

#define READ_ARRAY_CMD      0xff
#define RD_STATUS_CMD       0x70
#define CLR_STATUS_CMD      0x50
#define ERASE_SET_CMD       0x20
#define ERASE_CNF_CMD       0xd0
#define PRG_SETUP_CMD       0x40

// Intel Status Register Bits
#define VPP_LOW             0x08
#define PROGRAM_FAIL        0x10
#define ERASE_FAIL          0x20
#define WSM_BUSY            0x80

// Intel Lock Commands
#define UNLOCK              0
#define WRITE_LOCK          1

//----------------------------------------------------------------------------
// Module level global data
extern UINT8    pFlashDeviceNumber[FLASH_PART_STRING_LENGTH];

//----------------------------------------------------------------------------
// Function Prototypes
VOID 
SstFlashEraseCommand    (
    volatile UINT8  *pBlockAddress
);
VOID 
SstFlashReadCommand (
    volatile UINT8  *pByteAddress,
    UINT8           *Data, 
    UINT32          *Length
);
VOID 
SstFlashProgramCommand  (
    volatile UINT8  *pByteAddress,
    UINT8           *Data, 
    UINT32          *Length
);
BOOLEAN 
SstFlashIsEraseCompleted    (
    volatile UINT8  *pBlockAddress,
    BOOLEAN         *pError, 
    UINTN           *pStatus
);
BOOLEAN 
SstFlashIsProgramCompleted  (
    volatile UINT8  *pByteAddress,
    UINT8           *Byte, 
    UINT32          Length,
    BOOLEAN         *pError, 
    UINTN           *pStatus
);
VOID 
SstFlashBlockWriteEnable    (
    UINT8*          pBlockAddress
);
VOID 
SstFlashBlockWriteDisable   (
    UINT8*          pBlockAddress
);
VOID 
SstFlashDeviceWriteEnable   (
    VOID
);
VOID 
SstFlashDeviceWriteDisable  (
    VOID
);
VOID 
SstFlashVirtualFixup    (
    EFI_RUNTIME_SERVICES *pRS
);



//----------------------------------------------------------------------------
// Module specific variables
FLASH_PART mSstFirmwareHub =
    {
        SstFlashReadCommand,
        SstFlashEraseCommand,
        SstFlashProgramCommand,
        SstFlashIsEraseCompleted,
        SstFlashIsProgramCompleted,
        SstFlashBlockWriteEnable,
        SstFlashBlockWriteDisable,
        SstFlashDeviceWriteEnable,
        SstFlashDeviceWriteDisable,
        SstFlashVirtualFixup, // SST flash device virtual address 
                              // fix up routine
        1,                    // Number of bytes to program to the
                              // Flash part in each program command
        0,                    // Dummy value to hold place - only used in SPI
        NULL                  // Flash Part Number Pointer
    };

//----------------------------------------------------------------------------
// Function definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstFwhResetFlash
//
// Description: This function resets the SST flash part
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
SstFwhResetFlash    ( 
    IN volatile UINT8*      pAddress 
)
{
    pAddress[0x5555] = 0xaa;
    pAddress[0x2aaa] = 0x55;
    pAddress[0x5555] = 0xf0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstFlashReadCommand
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
SstFlashReadCommand (
    IN      volatile UINT8* pByteAddress, 
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
// Procedure:   SstFwhWaitForOperationCompleted
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
SstFwhWaitForOperationCompleted (
    IN volatile UINT8*      pAddress
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
// Procedure:   SstFlashEraseCommand
//
// Description: This API function erases a block in the flash. Flash model
//              specific code will branch out from this routine
//
// Input:       pBlockAddress   Block that need to be erased
//
// Output:      Nothing
//
// Returns:  None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
SstFlashEraseCommand    (
    IN volatile UINT8*      pBlockAddress
)
{
    EFI_STATUS          Status;
    UINT8               bFlashRetry;

    SstFwhResetFlash ( pBlockAddress );
    for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
        pBlockAddress[0x5555] = 0xaa;
        pBlockAddress[0x2aaa] = 0x55;
        pBlockAddress[0x5555] = 0x80;
        pBlockAddress[0x5555] = 0xaa;
        pBlockAddress[0x2aaa] = 0x55;
        *pBlockAddress=0x50;
        Status = SstFwhWaitForOperationCompleted ( pBlockAddress );
        SstFwhResetFlash ( pBlockAddress );
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
// Procedure:   SSTFlashIsEraseCompleted
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
SstFlashIsEraseCompleted    (
    IN  volatile UINT8      *pBlockAddress,
    OUT BOOLEAN             *pError,
    OUT UINTN               *pStatus)
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
// Procedure:   SSTFlashProgramCommand
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
SstFlashProgramCommand  (
    IN      volatile UINT8* pByteAddress,
    IN      UINT8           *Byte,
    IN OUT  UINT32          *Length
)
{
    volatile UINT8* pBlockAddress = (volatile UINT8*)BLOCK(pByteAddress);
    UINT8           bFlashRetry;
    EFI_STATUS      Status;

    if ( *Byte != *pByteAddress ) {
        SstFwhResetFlash ( pBlockAddress );
        for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
            // Program Command Sequence
            pBlockAddress[0x5555] = 0xaa;
            pBlockAddress[0x2aaa] = 0x55;
            pBlockAddress[0x5555] = 0xa0;
            *pByteAddress = *Byte;
            Status = SstFwhWaitForOperationCompleted ( pByteAddress );
            SstFwhResetFlash ( pBlockAddress );
            if ( Status != EFI_SUCCESS ) continue;
            if ( *pByteAddress != *Byte ) Status = EFI_DEVICE_ERROR;
            else {
                Status = EFI_SUCCESS;
                break;
            }
        }
    } else Status = EFI_SUCCESS;
    *Length = *Length - 1;
//-    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstFlashIsProgramCompleted
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
SstFlashIsProgramCompleted  (
    IN  volatile UINT8*     pByteAddress,
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
// Input:   volatile UINT8* pBlockAddress - This is location where the data
//                  is to be written
//          UINT8 LockState - Value to use to set the Lock register for the
//                  block defined by pBlockAddress
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
void 
SetBlockLock    (
    IN volatile UINT8*  pBlockAddress,  
    IN UINT8            LockState
)
{
    // Update the block lock register
    ((UINT8*)((UINTN)pBlockAddress - FlashDeviceBase + \
                                        FwhFeatureSpaceBase))[2] = LockState;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SSTFlashBlockWriteEnable
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
SstFlashBlockWriteEnable    (
    IN UINT8*               pBlockAddress
)
{
    SetBlockLock(pBlockAddress, UNLOCK);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SSTFlashBlockWriteDisable
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
SstFlashBlockWriteDisable   (
    IN UINT8*               pBlockAddress
)
{
    SetBlockLock(pBlockAddress, WRITE_LOCK);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SSTFlashDeviceWriteEnable
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
SstFlashDeviceWriteEnable (VOID)
{
    //We don't have to do anything here because
    //Flash Device is write enabled by the South Bridge driver
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SSTFlashDeviceWriteDisable
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
SstFlashDeviceWriteDisable (VOID)
{
    //We don't have to do anything here because
    //we always keep flash device in the write enabled state
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SSTFlashVirtualFixup
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
SstFlashVirtualFixup(
    IN EFI_RUNTIME_SERVICES *pRS
)
{

//  // Following is an example code for virtual address conversion
//  pRS->ConvertPointer(0, (VOID**)&FlashDeviceBase);

    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   mSstFwhIdentify
//
// Description: This function identifies the supported SST flash parts and
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
mSstFwhIdentify (
    IN  volatile UINT8*     pBlockAddress,
    OUT FLASH_PART          **Struct
)
{
    UINT8   VID;
    UINT8   DID;

    SstFwhResetFlash( pBlockAddress );

    pBlockAddress[0x5555] = 0xaa;
    pBlockAddress[0x2aaa] = 0x55;
    pBlockAddress[0x5555] = 0x90;

    VID = *pBlockAddress;
    DID = *(pBlockAddress + 1);

    SstFwhResetFlash( pBlockAddress );

    // check for valid ID
    if ((VID == VENDOR_ID) && ((DID == DEVICE_ID0) || (DID == DEVICE_ID1)))
    {
        MemCpy ( pFlashDeviceNumber, "SST 49LF004/008", 15 );
        mSstFirmwareHub.FlashPartNumber = pFlashDeviceNumber;
        *Struct = &mSstFirmwareHub;
        return TRUE;
    }
    else
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
