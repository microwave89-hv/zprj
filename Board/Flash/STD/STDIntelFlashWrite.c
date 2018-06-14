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

//*************************************************************************
// $Header: /Alaska/SOURCE/Flash_Combined_2/Core/STD/STDIntelFlashWrite.c 6     12/23/09 6:13a Calvinchen $Revision:
//
// $Revision: 6 $
//
// $Date: 12/23/09 6:13a $Log: $
//
//
//
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    StdIntelFlashWrite.c
//
// Description: Flash update routines
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------
// Includes
#include <efi.h>
#include <FlashPart.h>
#include <AmiDxeLib.h>
#include "token.h"

//----------------------------------------------------------------------
// define local MACROS

//Flash Part Specific Tokens
#define VENDOR_ID           0x88 // Intel Manufacturers ID
#define DEVICE_ID64T        0x17 // 64M TB
#define DEVICE_ID128T       0x18 // 128M TB
#define DEVICE_ID256T       0x19 // 256M TB
#define DEVICE_ID64B        0x1A // 64M BB
#define DEVICE_ID128B       0x1B // 128M BB
#define DEVICE_ID256B       0x1C // 256M BB

//Flash Part Specific Tokens
#define READ_ARRAY_CMD      0xff
#define RD_STATUS_CMD       0x70
#define CLR_STATUS_CMD      0x50
#define ERASE_SET_CMD       0x20
#define ERASE_CNF_CMD       0xd0
#define PRG_SETUP_CMD       0x40

#define RD_ID_CODE          0x90

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
IntelFlashEraseCommand  (
    volatile UINT8      *pBlockAddress
    );
VOID 
IntelFlashReadCommand   (
    volatile UINT8      *pByteAddress,
    UINT8               *Data, 
    UINT32              *Length
    );//{};
VOID 
IntelFlashProgramCommand    (
    volatile UINT8      *pByteAddress,
    UINT8               *Data, 
    UINT32              *Length
    );
BOOLEAN 
IntelFlashIsEraseCompleted  (
    volatile UINT8      *pBlockAddress,
    BOOLEAN             *pError, 
    UINTN               *pStatus
    );
BOOLEAN 
IntelFlashIsProgramCompleted    (
    volatile UINT8      *pByteAddress,
    UINT8               *Byte, 
    UINT32              Length,
    BOOLEAN             *pError, 
    UINTN               *pStatus
    );
VOID 
IntelFlashBlockWriteEnable  (
    UINT8*              pBlockAddress
    );
VOID 
IntelFlashBlockWriteDisable (
    UINT8*              pBlockAddress
    );
VOID 
IntelFlashDeviceWriteEnable (
    VOID
    );
VOID 
IntelFlashDeviceWriteDisable    (
    VOID
    );
VOID 
IntelFlashVirtualFixup  (
    EFI_RUNTIME_SERVICES    *pRS
    );


//========================================================================
// Local Variable definitions

// Flash Part Data structure fo the intel 82802ACC
FLASH_PART mIntelSTD =
    {
        IntelFlashReadCommand,
        IntelFlashEraseCommand,
        IntelFlashProgramCommand,
        IntelFlashIsEraseCompleted,
        IntelFlashIsProgramCompleted,
        IntelFlashBlockWriteEnable,
        IntelFlashBlockWriteDisable,
        IntelFlashDeviceWriteEnable,
        IntelFlashDeviceWriteDisable,
        IntelFlashVirtualFixup,
        1,              // Number of bytes to program to the
                        // Flash part in each program command
        0,              // Dummy value to hold place - only used in SPI
        NULL            // Flash Part Number Pointer                   
    };



//========================================================================
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelSTDCmdDelay
//
// Description: This function resets the Sst flash part
//
// Input:   None
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
IntelSTDCmdDelay (VOID)
{
    IoWrite8 ( 0xeb, 0x55 );
    IoWrite8 ( 0xeb, 0xaa );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelSTDResetFlash
//
// Description: This function resets the Sst flash part
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
IntelSTDResetFlash  ( 
    IN volatile UINT8*      pAddress 
)
{
    *pAddress = READ_ARRAY_CMD;// Return to read mode
    IntelSTDCmdDelay ();
    *pAddress = CLR_STATUS_CMD;// clear status
    IntelSTDCmdDelay ();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelSTDOperationCompleted
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
IntelSTDOperationCompleted  (
    IN volatile UINT8*      pAddress
)
{
    UINT8                   bSTDStatus;
    UINT32                  dTimeout = FLASH_RETRIES * 0x10000;

    do {
        *pAddress = RD_STATUS_CMD;          // read status.
        IntelSTDCmdDelay ();
        bSTDStatus = *pAddress;
        if ( bSTDStatus & WSM_BUSY ) {
            if ( bSTDStatus & ( VPP_LOW + PROGRAM_FAIL + ERASE_FAIL ) )
                return EFI_DEVICE_ERROR;
            else return EFI_SUCCESS;
        }
        dTimeout--;
    } while ( dTimeout != 0 );
    return EFI_TIMEOUT;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelFlashEraseCommand
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
IntelFlashEraseCommand  (
    IN volatile UINT8*      pBlockAddress
)
{
    EFI_STATUS          Status;
    UINT8               bFlashRetry;
    UINT8       i;

    for(i=0 ; i<4 ; i++) {
        // Some block size is 32K
        (UINT32)pBlockAddress += 0x8000;
        IntelSTDResetFlash( pBlockAddress );
        for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
            *pBlockAddress = ERASE_SET_CMD;
            IntelSTDCmdDelay ();
            *pBlockAddress = ERASE_CNF_CMD;
            IntelSTDCmdDelay ();
            Status = IntelSTDOperationCompleted( pBlockAddress );
            IntelSTDResetFlash( pBlockAddress );
            if ( Status != EFI_SUCCESS ) continue;
            if ( *pBlockAddress != 0xFF ) Status = EFI_DEVICE_ERROR;
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
// Procedure:   IntelFlashIsEraseCompleted
//
// Description: This function verifies whether the block erase
//              command is completed and returns the status of the command
//
// Input:       *pBlockAddress  Location of the block erase
//
// Output:      *pError     True on error and false on success
//              *Status     Error status code (0 - Success)
//
// Return:      TRUE        If operation completed successfully
//                          *pError = FALSE, *pStatus = 0
//              FALSE       If operation failed
//                          *pError = TRUE, *pStatus = error status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
BOOLEAN 
IntelFlashIsEraseCompleted  (
    IN  volatile UINT8*     pBlockAddress,
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
// Procedure:   IntelFlashProgramCommand
//
// Description: This function programs a byte data to the specified location
//
// Input:   *pByteAddress   Location where the data to be written
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
IntelFlashProgramCommand    (
    IN      volatile UINT8* pByteAddress,
    IN      UINT8           *Byte,
    IN OUT  UINT32          *Length
)
{
    UINT8               bFlashRetry;
    EFI_STATUS          Status;
    UINT16              Word = 0;
    UINT16*             adjAddress;
    BOOLEAN             Program_Word = FALSE;

    (UINT32)adjAddress = (UINT32)pByteAddress & 0xFFFFFFFE;
    if (*pByteAddress != *Byte) {
        // Word Program Only , Adjust Input word data
        if((UINT32)pByteAddress & 1) {
            // Get Last Byte of current address
            Word = (*Byte) << 8;
            Word += *(UINT8*)((UINT32)pByteAddress - 1);
        } else {
            if(*Length > 1) {
                // Get Next Byte from Input Buffer
                Word = *(Byte + 1) << 8;
                Program_Word = TRUE;
            } else {
                // Get Next Byte of current address
                Word = (*(UINT8*)((UINT32)pByteAddress + 1)) << 8;
            }
            Word += *Byte;
        }
        IntelSTDResetFlash( (volatile UINT8*)adjAddress );
        for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
            *(UINT16*)adjAddress = PRG_SETUP_CMD; // Issue program command
            IntelSTDCmdDelay ();
            *(UINT16*)adjAddress = Word; // Program a Word
            IntelSTDCmdDelay ();
            // Check for completion of the program operation
            Status = IntelSTDOperationCompleted( (volatile UINT8*)adjAddress );
            IntelSTDResetFlash( (volatile UINT8*)adjAddress );
            if ( Status != EFI_SUCCESS ) continue;
            if ( *adjAddress != Word ) Status = EFI_DEVICE_ERROR;
            else {
                Status = EFI_SUCCESS;
                break;
            }
        }
        // Input data is match
    } else Status = EFI_SUCCESS;
    if ( !Program_Word ) *Length = *Length - 1;
    else *Length = *Length - 2;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelFlashIsProgramCompleted
//
// Description: This function verifies whether the program (page or byte)
//              command is completed and returns the status of the command
//
// Input:       *pByteAddress   Location of the program command
//              Byte            Last data byte written
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
static 
BOOLEAN 
IntelFlashIsProgramCompleted    (
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
// Procedure:   IntelFlashReadCommand
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
IntelFlashReadCommand   (
    IN volatile UINT8*      pByteAddress, 
    IN UINT8                *Byte, 
    IN UINT32               *Length
)
{
    UINT32              dNumBytes = 0;
    
    // Changes for SMIFlash module label "4.6.3.6_SMIFLASH_12" or later.
    for ( dNumBytes = 0; dNumBytes < *Length ; dNumBytes++ )
        *( Byte + dNumBytes ) = *(UINT8*)((UINT32)pByteAddress + dNumBytes );
    *Length = 0;
    return ;
//-    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SetBlockLock
//
// Description: This function programs a page of data at a time
//
// Input:   *pBlockAddress - This is location where the data
//                  is to be written
//          LockState - Value to use to set the Lock register for the
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
    IN volatile UINT8*      pBlockAddress,  
    IN UINT8                LockState
)
{
//-    // Update the block lock register
//-    ((UINT8 *)((UINTN)pBlockAddress - FlashDeviceBase
//-                                + FwhFeatureSpaceBase))[2] = LockState;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelFlashBlockWriteEnable
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
IntelFlashBlockWriteEnable  (
    IN UINT8*               pBlockAddress
)
{
//-    SetBlockLock(pBlockAddress, UNLOCK);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelFlashBlockWriteDisable
//
// Description: This function contains any flash specific code need to
//              disable a particular flash block write
//
// Input:       None
//
// Output:      None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
IntelFlashBlockWriteDisable (
    IN UINT8*               pBlockAddress
)
{
//-    SetBlockLock(pBlockAddress, WRITE_LOCK);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelFlashDeviceWriteEnable
//
// Description: This function contains any flash specific code need to
//              enable flash write
//
// Input:       None
//
// Output:      None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
IntelFlashDeviceWriteEnable (VOID)
{
    //We don't have to do anything here because
    //Flash Device is write enabled by the South Bridge driver
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelFlashDeviceWriteDisable
//
// Description: This function contains any flash specific code need to
//              disable flash write
//
// Input:       None
//
// Output:      None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static 
VOID 
IntelFlashDeviceWriteDisable (VOID)
{
    //We don't have to do anything here because
    //we always keep flash device in the write enabled state
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelFlashVirtualFixup
//
// Description: This function will be invoked by the core to convert
//              runtime pointers to virtual address
//
// Input:       *pRS    Pointer to runtime services
//
// Output:      None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static 
VOID 
IntelFlashVirtualFixup  ( 
    IN EFI_RUNTIME_SERVICES *pRS
)
{
//  // Following is an example code for virtual address conversion
//  pRS->ConvertPointer(0, (VOID**)&FlashDeviceBase);

    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IntelSTDIdentify
//
// Description: This function identifies the supported LPC flash parts and
//              returns appropriate flash device API pointer. If flash part is
//              not supported by this module it will return FALSE.
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
//          it is properly linked to the init list "FlashList" (in SDL file)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN 
IntelSTDIdentify    (
    IN  volatile UINT8*     pBlockAddress,
    OUT FLASH_PART          **Struct
)
{
    UINT8 VID, DID;

//-    SetBlockLock(pBlockAddress, UNLOCK);

    *pBlockAddress = RD_ID_CODE;// Set to read ID code mode
    VID = *pBlockAddress;
    DID = *(pBlockAddress + 2);
    *pBlockAddress = READ_ARRAY_CMD;// Return to read mode

    if ((VID == VENDOR_ID) && 
        (DID == DEVICE_ID64T || DID == DEVICE_ID128T || \
         DID == DEVICE_ID256T || DID == DEVICE_ID64B || \
         DID == DEVICE_ID128B || DID == DEVICE_ID256B)) {
        // If your Block size is 128K, please modify your FLASH_BLOCK_SIZE
        // to 128K in flash.sdl .
        MemCpy ( pFlashDeviceNumber, "Numonyx 28F640/128/256P30B/T", 28 );
        mIntelSTD.FlashPartNumber = pFlashDeviceNumber;
        *Struct = &mIntelSTD;
        return TRUE;
    } else return FALSE;
}
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
