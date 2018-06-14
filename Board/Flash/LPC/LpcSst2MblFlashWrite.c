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
// $Header: /Alaska/SOURCE/Flash_Combined_2/Core/LPC/LpcSst2MblFlashWrite.c 15    12/23/09 6:12a Calvinchen $
//
// $Revision: 15 $
//
// $Date: 12/23/09 6:12a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Flash_Combined_2/Core/LPC/LpcSst2MblFlashWrite.c $
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
// 12    11/13/08 1:33a Calvinchen
// Fixed Boot Block recovery and re-flash BIOS failed with using SST
// 49LF160C.
//
// 11    6/26/08 7:00a Calvinchen
// Generic bug fixed.
//
// 9     5/09/08 3:34a Calvinchen
// Added support for Winbond 39V080AP and STM M50LPW080.
//
// 8     1/07/08 3:28p Robert
// Updated for coding standard
//
// 7     12/07/07 1:45p Stacyh
// Updated to differentiate between LPC and FWH SST parts.
//
// 6     11/09/07 4:17p Alexp
// Added dummy FlashRead function. Not supported by this type of flash
// module
//
// 5     10/25/07 1:14p Fasihm
// Removed the directive AmiCspLib.h as it is not needed and is causing
// other Build Errors.
//
// 4     10/19/07 6:29p Robert
//
// 3     8/20/07 4:13p Radhikav
// Flash Part Data structure for SST 49LF160C changed.
//
// 2     7/09/07 10:05a Radhikav
// modified flashdevicewriteenable and disable functions.
//
// 1     5/16/07 1:00p Radhikav
//
//
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    LpcSst2MblFlashWrite.c
//
// Description: Support routines for the LPC Sst 2Mb part
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
#define SST_MANUFACTURER_ID         0xbf    // SST manufacturer  ID
#define SST49LF160C_DEVICE_ID       0x4c    // 2MB LPC
#define SST49LF160C                 0x4cbf  // SST 49LF160C
#define SST49LF016C			        0x5cbf
#define STM50LPW080                 0x2f20  // ST M50LPW080


#define READ_ARRAY_CMD              0xff
#define RD_STATUS_CMD               0x70
#define CLR_STATUS_CMD              0x50
#define ERASE_SET_CMD               0x20
#define ERASE_CNF_CMD               0xd0
#define PRG_SETUP_CMD               0x40
#define SECTOR_ERASE_SET_CMD        0x30 // SST 49LF160C only

#define RD_ID_CODE                  0x90

// SST49LF160C Status Register Bits

#define VPP_LOW                     0x08
#define PROGRAM_FAIL                0x10
#define ERASE_FAIL                  0x20
#define WSM_BUSY                    0x80

// Intel Lock Commands
#define UNLOCK                      0
#define WRITE_LOCK                  1

#define SECTOR_SIZE_4KB             0x1000  // Common 4kBytes sector size
#define SECTOR_SIZE_64KB            0x10000  // Common 64kBytes sector size

//----------------------------------------------------------------------------
// Module level global data
extern FLASH_PART   *FlashAPI;
extern UINT8        pFlashDeviceNumber[FLASH_PART_STRING_LENGTH];

//----------------------------------------------------------------------------
// Local Variable definitions

EFI_STATUS
InitSst2MbCheckId   (
    volatile UINT8*     pBlockAddress
    );
BOOLEAN
SstLpcIsEraseCompleted  (
    volatile UINT8      *pBlockAddress,
    BOOLEAN             *pError,
    UINTN               *pStatus
    );
BOOLEAN
SstLpcIsProgramCompleted    (
    volatile UINT8      *pByteAddress,
    UINT8               *Byte,
    UINT32              Length,
    BOOLEAN             *pError,
    UINTN               *pStatus
    );

static UINT8 gbEraseSetCmd = ERASE_SET_CMD;

//----------------------------------------------------------------------------
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Sst2mLpcCmdDelay
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
Sst2mLpcCmdDelay (VOID)
{
    IoWrite8 ( 0xeb, 0x55 );
    IoWrite8 ( 0xeb, 0xaa );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Sst2mLpcResetFlash
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
Sst2mLpcResetFlash  (
    IN volatile UINT8*      pAddress
)
{
    *pAddress = READ_ARRAY_CMD;// Return to read mode
    Sst2mLpcCmdDelay ();
    *pAddress = CLR_STATUS_CMD;// clear status
    Sst2mLpcCmdDelay ();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Sst2mLpcOperationCompleted
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
Sst2mLpcOperationCompleted  (
    IN volatile UINT8*      pAddress
)
{
    UINT8                   bLpcStatus;
    UINT32                  dTimeout = FLASH_RETRIES * 0x10000;

    do {
        *pAddress = RD_STATUS_CMD;          // read status.
        Sst2mLpcCmdDelay ();
        bLpcStatus = *pAddress;
        if ( bLpcStatus & WSM_BUSY ) {
            if ( bLpcStatus & ( VPP_LOW + PROGRAM_FAIL + ERASE_FAIL ) )
                return EFI_DEVICE_ERROR;
            else return EFI_SUCCESS;
        }
        dTimeout--;
    } while ( dTimeout != 0 );
    return EFI_TIMEOUT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstLpcEraseCommand
//
// Description: This API function erases a block in the flash. Flash model
//              specific code will branch out from this routine
//
// Input:       pBlockAddress   Block that need to be erased
//
// Output:      Nothing
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID
SstLpcEraseCommand  (
    IN volatile UINT8*      pBlockAddress
)
{
    EFI_STATUS          Status;
    UINT8               bFlashRetry;
    UINTN               nSectorAddr;
    UINT16              wNumSectors, wSectorCount;

    Sst2mLpcResetFlash( pBlockAddress );
    wNumSectors = ( FlashBlockSize / FlashAPI->FlashSectorSize );
    for ( wSectorCount = 0; wSectorCount < wNumSectors; wSectorCount++ ) {
        nSectorAddr = (UINTN)( wSectorCount * FlashAPI->FlashSectorSize );
        for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
            *(UINT8*)( (UINTN)pBlockAddress + nSectorAddr ) = gbEraseSetCmd;
            Sst2mLpcCmdDelay ();
            *(UINT8*)( (UINTN)pBlockAddress + nSectorAddr ) = ERASE_CNF_CMD;
            Sst2mLpcCmdDelay ();
            Status = Sst2mLpcOperationCompleted ( \
                            (UINT8*)((UINTN)pBlockAddress + nSectorAddr) );
            Sst2mLpcResetFlash( (UINT8*)((UINTN)pBlockAddress + nSectorAddr) );
            if ( Status != EFI_SUCCESS ) continue;
            if ( 0xFF == \
                    *(volatile UINT8*)((UINTN)pBlockAddress + nSectorAddr) ) {
                Status = EFI_SUCCESS;
                break;
            } else Status = EFI_DEVICE_ERROR;
        }
    }
//-    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstLpcIsEraseCompleted
//
// Description: This function verifies whether the block erase
//              command is completed and returns the status of the command
//
// Input:       *pBlockAddress  Location of the block erase
//              *pError         True on error and false on success
//              *Status         Error status code (0 - Success)
//
// Output:      TRUE        If operation completed successfully
//                          *pError = FALSE, *pStatus = 0
//              FALSE       If operation failed
//                          *pError = TRUE, *pStatus = error status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
BOOLEAN
SstLpcIsEraseCompleted  (
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
// Procedure:   SstLpcReadCommand
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
SstLpcReadCommand   (
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
// Procedure:   SstLpcProgramCommand
//
// Description: This function programs a byte data to the specified location
//
// Input:       *pByteAddress   Location where the data to be written
//              Data            Byte to be written
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID
SstLpcProgramCommand    (
    IN  volatile UINT8*     pByteAddress,
    OUT UINT8               *Byte,
    OUT UINT32              *Length
)
{
    EFI_STATUS          Status;
    UINT8               bFlashRetry;

    if ( *pByteAddress != *Byte ) {

        Sst2mLpcResetFlash( pByteAddress );
        for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
            *pByteAddress = PRG_SETUP_CMD; // Issue program command
            Sst2mLpcCmdDelay ();
            *pByteAddress = *Byte; // Program a byte
            Sst2mLpcCmdDelay ();
            // Check for completion of the program operation
            Status = Sst2mLpcOperationCompleted( pByteAddress );
            Sst2mLpcResetFlash( pByteAddress );
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
// Procedure:   SstLpcIsProgramCompleted
//
// Description: This function verifies whether the program (page or byte)
//              command is completed and returns the status of the command
//
// Input:       *pByteAddress   Location of the program command
//              Byte            Last data byte written
//              *pError         True on error and false on success
//              *Status         Error status code (0 - Success)
//
// Output:      TRUE        If operation completed successfully
//                          *pError = FALSE, *pStatus = 0
//              FALSE       If operation failed
//                          *pError = TRUE, *pStatus = error status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
BOOLEAN
SstLpcIsProgramCompleted    (
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
    IN volatile UINT8*  pBlockAddress,
    IN UINT8            LockState
)
{
    // Update the block lock register
    ((UINT8*)((UINTN)pBlockAddress - FlashDeviceBase + \
                            FwhFeatureSpaceBase))[2] = LockState;
    ((UINT8 *)((UINTN)pBlockAddress - FlashDeviceBase + \
                            FwhFeatureSpaceBase + 0x8000))[2] = LockState;
    ((UINT8 *)((UINTN)pBlockAddress - FlashDeviceBase + \
                            FwhFeatureSpaceBase + 0xA000))[2] = LockState;
    ((UINT8 *)((UINTN)pBlockAddress - FlashDeviceBase + \
                            FwhFeatureSpaceBase + 0xC000))[2] = LockState;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstLpcBlockWriteEnable
//
// Description: This function contains any flash specific code need to
//              enable a particular flash block write
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID
SstLpcBlockWriteEnable  (
    IN UINT8*               pBlockAddress
)
{
    SetBlockLock(pBlockAddress, UNLOCK);
//-    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstLpcBlockWriteDisable
//
// Description: This function contains any flash specific code need to
//              disable a particular flash block write
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID
SstLpcBlockWriteDisable (
    IN UINT8*               pBlockAddress
)
{
    SetBlockLock(pBlockAddress, WRITE_LOCK);
//-    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstLpcDeviceWriteEnable
//
// Description: This function contains any flash specific code need to
//              enable flash write
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID
SstLpcDeviceWriteEnable (VOID)
{
    //We don't have to do anything here because
    //Flash Device is write enabled by the South Bridge driver
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstLpcDeviceWriteDisable
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
static
VOID
SstLpcDeviceWriteDisable (VOID)
{
    //We don't have to do anything here because
    //we always keep flash device in the write enabled state
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SstLpcVirtualFixup
//
// Description: This function will be invoked by the core to convert
//              runtime pointers to virtual address
//
// Input:       *pRS    Pointer to runtime services
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static
VOID
SstLpcVirtualFixup  (
    IN EFI_RUNTIME_SERVICES *pRS
)
{
//  // Following is an example code for virtual address conversion
//  pRS->ConvertPointer(0, (VOID**)&FlashDeviceBase);

    return;
}



// Flash Part Data structure for SST 49LF160C

FLASH_PART mSstLpc2Mb =
    {
        SstLpcReadCommand,
        SstLpcEraseCommand,
        SstLpcProgramCommand,
        SstLpcIsEraseCompleted,
        SstLpcIsProgramCompleted,
        SstLpcBlockWriteEnable,
        SstLpcBlockWriteDisable,
        SstLpcDeviceWriteEnable,
        SstLpcDeviceWriteDisable,
        SstLpcVirtualFixup,
        1,                              // Number of bytes to program to the
        SECTOR_SIZE_64KB,               // Dummy value to hold place -
        NULL                            // Flash Part Number Pointer                           
    };                                  // Flash part in each program command


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   mSstLpcIdentify
//
// Description: This function identifies the supported LPC flash parts and
//              returns appropriate flash device API pointer. If flash part is
//              not supported by this module it will return FALSE.
//
//
// Input:       pBlockAddress   Block address of the flash part. Can be used to
//                              send ID command
//              **FlashApi      Pointer to hold the returned flash API
//
// Output:      TRUE            If flash part is supported, FlashApi contains
//                              routines to handle the flash requests
//              FALSe           Flash part is not supported
//
// Note:        This routine is part of the global flash init list. Make sure
//              it is properly linked to the init list "FlashList" (in SDL file)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
mSstLpcIdentify (
    IN volatile UINT8*      pBlockAddress,
    IN FLASH_PART           **Struct
)
{
    EFI_STATUS  Status = EFI_NOT_FOUND;

    Status = InitSst2MbCheckId( pBlockAddress );
    if ( Status != EFI_SUCCESS ) return FALSE;
    else {
        mSstLpc2Mb.FlashPartNumber = pFlashDeviceNumber;
        *Struct = &mSstLpc2Mb;
    }
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitSst2MbCheckId
//
// Description: This function identifies the supported LPC flash parts.
//
// Input:       pBlockAddress   Block address of the flash part. Can be used to
//                              send ID command
//
// Output:      EFI_SUCCESS     If flash part is supported
//              EFI_NOT_FOUND   Flash part is not supported
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InitSst2MbCheckId   (
    IN volatile UINT8*      pBlockAddress
)
{
    UINT8           VID, DID;
    EFI_STATUS      Status = EFI_NOT_FOUND;

    *pBlockAddress = READ_ARRAY_CMD;// Return to read mode
    Sst2mLpcCmdDelay ();

    *pBlockAddress = RD_ID_CODE;// Set to read ID code mode
    Sst2mLpcCmdDelay ();

    VID = *pBlockAddress;
    DID = *(pBlockAddress + 1);

    *pBlockAddress = READ_ARRAY_CMD;// Return to read mode

    switch ( ( DID << 8 ) + VID ) {
        case SST49LF160C :
        case SST49LF016C :
            gbEraseSetCmd = SECTOR_ERASE_SET_CMD;
            mSstLpc2Mb.FlashSectorSize = SECTOR_SIZE_4KB;
            MemCpy ( pFlashDeviceNumber, "SST 49LF016/160C", 16 );
            Status = EFI_SUCCESS;
            break;
        case STM50LPW080 :
            gbEraseSetCmd = ERASE_SET_CMD;
            mSstLpc2Mb.FlashSectorSize = SECTOR_SIZE_64KB;
            MemCpy ( pFlashDeviceNumber, "ST M50LPW080", 12 );
            Status = EFI_SUCCESS;
            break;
        default :
            Status = EFI_NOT_FOUND;
    }
    return Status;
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