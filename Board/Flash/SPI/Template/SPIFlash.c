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
// $Header: /Alaska/SOURCE/Flash_Combined_2/Core/SPI/Template/SpiFlash.c 4     6/24/09 3:14a Calvinchen $
//
// $Revision: 4 $
//
// $Date: 6/24/09 3:14a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Flash_Combined_2/Core/SPI/Template/SpiFlash.c $
// 
// 4     6/24/09 3:14a Calvinchen
// (EIP22177) Updated for Aptio Source Enhancement. 
//
// 3     4/27/09 3:24a Calvinchen
// 2.(EIP20459) Added Multiple SPI CSP component support.
//
// 2     6/19/08 4:30a Calvinchen
//
// 1     3/13/08 6:32a Calvinchen
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
//----------------------------------------------------------------------------
// Includes
#include <efi.h>
#include <AmiDxeLib.h>
#include "FlashPart.h"
#include "SpiFlash.h"
#include "token.h"
//----------------------------------------------------------------------------
// Local defines for transaction types
/*  ---------------------   PORTING REQUIRED   ---------------------

// ICH8/9/10 SPI register defines.
#define     SPI_STS                     0x90    //  SPI Status
#define     SPI_CTL                     0x91    //  SPI Control
#define     SPI_ADR                     0x08    //  SPI Address
#define     SPI_DAT0                    0x10    //  SPI Data 0
#define     SPI_PREOP                   0x94    //  Prefix Opcode Configuration
#define     SPI_OPTYPE                  0x96    //  Opcode Type Configuration
#define     SPI_OPMENU                  0x98    //  Opcode Menu Configuration
//  SPI default opcode slots
#define     SPI_OPCODE_WRITE_INDEX      0x0
#define     SPI_OPCODE_READ_INDEX       0x1
#define     SPI_OPCODE_ERASE_INDEX      0x2
#define     SPI_OPCODE_READ_S_INDEX     0x3
#define     SPI_OPCODE_READ_ID_INDEX    0x4
#define     SPI_OPCODE_WRITE_S_INDEX    0x5
#define     SPI_OPCODE_WRITE_E_INDEX    0x6
#define     SPI_OPCODE_WRITE_S_E_INDEX  0x7
#define     SPI_PREFIX_WRITE_S_EN       0x1
#define     SPI_PREFIX_WRITE_EN         0x0
#define     SPI_MAX_DATA_TRANSFER       0x40
    ---------------------   PORTING REQUIRED   ---------------------*/
//----------------------------------------------------------------------------
// Module level global data
//============================================================================
extern UINT16       gFlashId;
extern FLASH_PART   *FlashAPI;
//----------------------------------------------------------------------------
// Function Externs
//-extern
//-VOID
//-SpiChipsetVirtualFixup  (
//-    IN EFI_RUNTIME_SERVICES *pRS
//-);
//----------------------------------------------------------------------------
// Local prototypes
VOID
CommonSpiEraseCommand   (
    volatile UINT8          *pBlockAddress
);
VOID
CommonSpiProgramCommand (
    volatile UINT8          *pByteAddress,
    UINT8                   *Byte,
    UINT32                  *Length
);
VOID
CommonSpiReadCommand    (
    volatile UINT8          *pByteAddress,
    UINT8                   *Byte,
    UINT32                  *Length
);
BOOLEAN
CommonSpiIsEraseCompleted   (
    volatile UINT8          *pBlockAddress,
    BOOLEAN                 *pError,
    UINTN                   *pStatus
);
BOOLEAN
CommonSpiIsProgramCompleted (
    volatile UINT8          *pByteAddress,
    UINT8                   *Byte,
    UINT32                  Length,
    BOOLEAN                 *pError,
    UINTN                   *pStatus
);
VOID
CommonSpiBlockWriteEnable   (
    volatile UINT8          *pBlockAddress
);
VOID
CommonSpiBlockWriteDisable  (
    volatile UINT8          *pBlockAddress
);
VOID
CommonSpiDeviceWriteEnable  (
    VOID
);
VOID
CommonSpiDeviceWriteDisable (
    VOID
);
VOID
CommonSpiDeviceVirtualFixup (
    EFI_RUNTIME_SERVICES    *pRS
);
//============================================================================
// Local Variables
//============================================================================
FLASH_PART mCommonSpiFlash ={
    CommonSpiReadCommand,
    CommonSpiEraseCommand,
    CommonSpiProgramCommand,
    CommonSpiIsEraseCompleted,
    CommonSpiIsProgramCompleted,
    CommonSpiBlockWriteEnable,
    CommonSpiBlockWriteDisable,
    CommonSpiDeviceWriteEnable,
    CommonSpiDeviceWriteDisable,
    CommonSpiDeviceVirtualFixup,
    1,                      // default value, should be changed in Init function
    SECTOR_SIZE_4KB
};
EX_FLASH_PART mExFlashPart = {
      {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},0,0},
      FLASH_SIZE,         // flash size, should be changed in Init function
      0,                  // flash part id, should be changed in Init function
      0                   // flash part string, should be changed in Init function
};
UINT8           gbDeviceVirtual = 0;
UINT8           gbDeviceWriteEnabled = 0;
//----------------------------------------------------------------------------
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IoDelay
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
IoDelay (VOID)
{
    UINT8               bTimeout;
    for ( bTimeout = 0; bTimeout < 33; bTimeout++ ) {
        IoWrite8( 0xEB, 0x55 );
        IoWrite8( 0xEB, 0xAA );
    }
    return ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WaitForSpiCycleDone
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
WaitForSpiCycleDone (VOID)
{
/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT16              wTimeout;
    UINT8               bCyclyDone;

    for ( wTimeout = 0, bCyclyDone = 0; wTimeout < 0xFFFF; wTimeout++ ) {
        bCyclyDone = *(volatile UINT8*)( gSPIBASE + SPI_STS );
        if ( bCyclyDone & BIT02 ) break;
    }
    // write BIT2 to clear CycleDone status
    *(volatile UINT8*)( gSPIBASE + SPI_STS ) = BIT02;

    ---------------------   PORTING REQUIRED   ---------------------*/
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CommonSpiReadStatus
//
// Description:
//
// Input:       None.
//
// Output:      Status Register which is read from SPI flash.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
CommonSpiReadStatus (VOID)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT16  wSpiCmd;
    // Opcode menu slot 3 is configured as "Read Status Register"
    wSpiCmd = SPI_OPCODE_READ_S_INDEX << 4;
    // indicate that data phase is required
    wSpiCmd += (1 << 14);
    // Set BIT1 (Go)
    *(volatile UINT16*)( gSPIBASE + SPI_CTL ) =  wSpiCmd + BIT01;
    // wait for spi cycle completed.
    WaitForSpiCycleDone();
    // return status register.
    return ( *(volatile UINT8*)( gSPIBASE + SPI_DAT0 ) );

    ---------------------   PORTING REQUIRED   ---------------------*/

    return ( (UINT8)EFI_NOT_READY );    // For Template compiling only.
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WaitForWriteOperationCompleted
//
// Description:
//
// Input:       None.
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
WaitForWriteOperationCompleted (VOID)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT16              wWaitStsRetry;
    UINT8               bStatus;

    for( wWaitStsRetry = 0; wWaitStsRetry < 0xFFFF; wWaitStsRetry++ ) {
        // read flash status register.
        bStatus = CommonSpiReadStatus();
        // Is operation busy ?
        if( !( bStatus & 0x1 ) ) break;
    }

    ---------------------   PORTING REQUIRED   ---------------------*/
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CommonSpiWriteStatus
//
// Description: Routine for Write SPI Status Register.
//
// Input:       None.
//
// Output:      Status Register which is read from SPI flash.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CommonSpiWriteStatus    (
    IN UINT8                bWriteData,
    IN UINT8                bOpcodeIndex,
    IN UINT8                bIsDataPhase,
    IN UINT8                bPrefixOp,
    IN UINT32               dSectorAddress
)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT16  wSpiCmd;

    *(volatile UINT8*)( gSPIBASE + SPI_DAT0 ) = bWriteData;
    *(volatile UINT32*)( gSPIBASE + SPI_ADR ) = dSectorAddress;
    // Opcode menu slot 3 is configured as "Read Status Register"
    wSpiCmd = bOpcodeIndex << 4;
    // indicate that data phase is required
    wSpiCmd += ( bIsDataPhase << 14 );
    // BIT3(Preop 1)
    wSpiCmd += ( bPrefixOp << 3 );
    // Set BIT1 (Go), BIT2(Atomic w/ Prefix),
    *(volatile UINT16*)( gSPIBASE + SPI_CTL ) =  wSpiCmd + BIT01 + BIT02;
    // wait for spi cycle completed.
    WaitForSpiCycleDone();
    // wait for SPI flash operation completed.
    WaitForWriteOperationCompleted();
    // return status register.
    return ;

    ---------------------   PORTING REQUIRED   ---------------------*/
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CommonSpiReadByte
//
// Description:
//
// Input:       dByteAddress    Address that need to be read.
//
// Output:      BYTE            Value which is read from SPI flash.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8
CommonSpiReadByte   (
    IN UINT32               dByteAddress
)
{

/*  ---------------------   PORTING REQUIRED   ---------------------
    UINT16  wSpiCmd;

    // update the
    *(volatile UINT32*)( gSPIBASE + SPI_ADR ) = dByteAddress;
    // Opcode menu slot 1 is configured as "Read Flash"
    wSpiCmd = ( SPI_OPCODE_READ_INDEX << 4 ) + BIT01;
    // indicate that data phase is required
    wSpiCmd += (1 << 14);
    *(volatile UINT16*)( gSPIBASE + SPI_CTL ) = wSpiCmd;
    // wait for spi cycle completed.
    WaitForSpiCycleDone();
    // return data.
    return( *(volatile UINT8*)( gSPIBASE + SPI_DAT0 ) );

    ---------------------   PORTING REQUIRED   ---------------------*/
    return ( (UINT8)EFI_NOT_READY );    // For Template compiling only.
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CommonConvertSpiAddress
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
CommonConvertSpiAddress   (
    IN volatile UINT8       *pAddress
)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    if ( gbDeviceVirtual ) {
        // pAddress - offset from Flash Device Base.
        pAddress -= FlashDeviceBase;
        // pAddress - 32bit memory mapping address.
        pAddress += (0xFFFFFFFF - FLASH_SIZE) + 1;
    }
    ---------------------   PORTING REQUIRED   ---------------------*/

    return ((UINT32)pAddress);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitializeSpiEnvironment
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
InitializeSpiEnvironment (
    IN FLASH_INFO       *FlashInfo
)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT32              dIchSpiFDOD;

    //Program first DWORD of opcode commands
    *((volatile UINT32*)( gSPIBASE+R_RCRB_SPI_OPMENU+0 )) = (UINT32)
        // Write Byte
        ( (FlashInfo->Write.Opcode << (SPI_OPCODE_WRITE_INDEX * 8))
        // Read Data
        | (FlashInfo->Read.Opcode << (SPI_OPCODE_READ_INDEX * 8))
        // Erase 64k Sector
        | (FlashInfo->Erase.Opcode << (SPI_OPCODE_ERASE_INDEX * 8))
        // Read Device Status Reg
        | (FlashInfo->ReadStatus.Opcode << (SPI_OPCODE_READ_S_INDEX * 8)) );

    //Program second DWORD of Opcode commands
    *((volatile UINT32*)( gSPIBASE+R_RCRB_SPI_OPMENU+4 )) = (UINT32)
        // Read device ID
        ( (FlashInfo->ReadId.Opcode << ((SPI_OPCODE_READ_ID_INDEX - 4) * 8))
        // Write Status Register
        | (FlashInfo->WriteStatus.Opcode << ((SPI_OPCODE_WRITE_S_INDEX - 4) * 8))
        // Write Status Enable Register
        | (FlashInfo->WriteStatusEnable.Opcode << ((SPI_OPCODE_WRITE_E_INDEX - 4) * 8)));

    //Program opcode types
    *((volatile UINT16*)( gSPIBASE+R_RCRB_SPI_OPTYPE )) = (UINT16)
        // write with address.
        ( FlashInfo->Write.OpcodeType << (SPI_OPCODE_WRITE_INDEX*2)
        // read with address.
        | FlashInfo->Read.OpcodeType << (SPI_OPCODE_READ_INDEX*2)
        // write with address.
        | FlashInfo->Erase.OpcodeType << (SPI_OPCODE_ERASE_INDEX*2)
        // read w/o no adress.
        | FlashInfo->ReadStatus.OpcodeType << (SPI_OPCODE_READ_S_INDEX*2)
        // read with address.
        | FlashInfo->ReadId.OpcodeType << (SPI_OPCODE_READ_ID_INDEX*2)
        // write w/o address.
        | FlashInfo->WriteStatus.OpcodeType << (SPI_OPCODE_WRITE_S_INDEX*2)
        // write w/o address.
        | FlashInfo->WriteStatusEnable.OpcodeType << (SPI_OPCODE_WRITE_E_INDEX*2) );

    //set up the prefix opcodes for commands
    *((volatile UINT16*)( gSPIBASE+R_RCRB_SPI_PREOP )) = (UINT16)
        ( ( FlashInfo->WriteStatusEnable.Opcode << 8 )
        | ( FlashInfo->WriteEnable.Opcode ) );

    // Here checks the BIOS region of Flash Descriptor Table.
    if ( mExFlashPart.FlashCommandMenu != NULL ) {
        if ( !gBiosRegionBase ) {
            *(volatile UINT32*)( gSPIBASE + ICH_SPI_FDOC ) = 0;
            dIchSpiFDOD = *(volatile UINT32*)( gSPIBASE + ICH_SPI_FDOD );
            if ( dIchSpiFDOD == 0x0FF0A55A )
            {
                *(volatile UINT32 *)( gSPIBASE + ICH_SPI_FDOC ) = (BIT13+BIT02);
                do {
                    dIchSpiFDOD = *(volatile UINT32*)( gSPIBASE+ICH_SPI_FDOD );
                } while( dIchSpiFDOD == 0x0FF0A55A );
                gBiosRegionBase = ( ( (dIchSpiFDOD >> 16) + 1 ) << 12 );
            }
            else
                gBiosRegionBase = mExFlashPart.FlashCapacity;
        }
    }
    return ;

    ---------------------   PORTING REQUIRED   ---------------------*/

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ReinitializeSpiEnvironment
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ReinitializeSpiEnvironment (
    IN FLASH_INFO           *FlashInfo
)
{
    return ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CommonSpiReadId
//
// Description:
//
// Input:
//
// Output:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
CommonSpiReadId (
    IN FLASH_INFO           *FlashInfo,
    IN UINT32               *dFlashId
)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT16              wSpiCmd = 0xFFFF;

    InitializeSpiEnvironment( FlashInfo );
    // Set SPI read-address = 0
    *(volatile UINT32*)( gSPIBASE + SPI_ADR ) = 0;
    // set opcode for "Read ID"
    wSpiCmd = SPI_OPCODE_READ_ID_INDEX << 4;
    // set transaction = 3 bytes
    wSpiCmd += ( ( 3 - 1 ) << 8 );
    // indicate that data phase is required
    wSpiCmd += ( 1 << 14 );
    // Go (BIT1)
    *(volatile UINT16*)( gSPIBASE + SPI_CTL ) =  wSpiCmd + BIT01;
    WaitForSpiCycleDone();
    IoDelay();
    *dFlashId = *(volatile UINT32*)( gSPIBASE + SPI_DAT0 ) & 0x00FFFFFF;
    TRACE ((-1, " FLASH ID  - %08X\n", *dFlashId));
    return  TRUE;

    ---------------------   PORTING REQUIRED   ---------------------*/

    return ( (UINT8)EFI_NOT_READY );    // For Template compiling only.
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiEraseCommand
//
// Description: This API function erases a block in the flash. Flash model
//              specific code will branch out from this routine
//
// Input:       pBlockAddress   Block that need to be erased
//
// Output:      Nothing
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CommonSpiEraseCommand   (
    IN volatile UINT8*      pBlockAddress
)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    volatile UINT32     dSectorAddr;
    UINT32              dNByte;
    UINT16              wEraseRetry, wNumSectors, wSector;
    UINT16              wSpiCmd;

    // These parts only erase in 64K sectors
    InitializeSpiEnvironment( mExFlashPart.FlashCommandMenu );
    wNumSectors = ( FlashBlockSize / FlashAPI->FlashSectorSize );
    for ( wSector = 0; wSector < wNumSectors ; wSector++ ) {
        dSectorAddr = (UINT32)
                        ( pBlockAddress + wSector * FlashAPI->FlashSectorSize );
        for ( dNByte = 0; dNByte < FlashAPI->FlashSectorSize; dNByte++ ) {
            if ( *(volatile UINT8*)( dSectorAddr + dNByte ) != 0xFF )  break;
        }
        if  ( dNByte == FlashAPI->FlashSectorSize )   break;
        for ( wEraseRetry = 0; wEraseRetry < FLASH_RETRIES; wEraseRetry++ ) {
            dSectorAddr += gBiosRegionBase;
            *(volatile UINT32*)( gSPIBASE + SPI_ADR ) = dSectorAddr;
            // opcode index 2 is programmed for erase command.
            // Set BIT1 (Go), BIT2(Atomic w/ Prefix)
            wSpiCmd = ( SPI_OPCODE_ERASE_INDEX << 4) + BIT01 + BIT02;
            *(volatile UINT16*)( gSPIBASE + SPI_CTL ) = wSpiCmd;
            // wait for chipset SPI cycle completed.
            WaitForSpiCycleDone();
            // wait for SPI flash operation completed.
            WaitForWriteOperationCompleted();
            // write operation appeared to succeed, now read back byte and compare.
            if ( CommonSpiReadByte( dSectorAddr ) == 0xFF )   break;
        }
    }

    ---------------------   PORTING REQUIRED   ---------------------*/

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiProgramCommand
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
CommonSpiProgramCommand (
    IN volatile UINT8*      pByteAddress,
    IN UINT8                *Byte,
    IN OUT UINT32           *Length
)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT8               bFlashRetry = 0, bProgBytes = 0, bNumBytes = 0;
    UINT16              wSpiCmd = 0, wRetry = 0, wMaxNumBytes = 0;

    InitializeSpiEnvironment( mExFlashPart.FlashCommandMenu );
    bProgBytes = mCommonSpiFlash.FlashProgramSize;
    if ( mCommonSpiFlash.FlashProgramSize != 1 ) {
        // Limit the max transfer to the number of bytes the chipset can
        // transfer per cycle
        if ( *Length >= SPI_MAX_DATA_TRANSFER )
            bProgBytes = SPI_MAX_DATA_TRANSFER;
        else
            bProgBytes = *Length;
        // this is currently for the WINBOND parts only
        // mask off lowest 8 bits of address so that we can determine how
        // many bytes we can write before we hit the end of a page
        wMaxNumBytes = 0x100 - ((UINT8)pByteAddress & 0xFF);
        if ( (UINT32)pByteAddress & 0x1 )   bProgBytes = 1;
        else if ( (UINT16)bProgBytes > wMaxNumBytes )
                bProgBytes = (UINT8)wMaxNumBytes;
    }
    for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
        // check if do the data need to be programmed ?
        for ( bNumBytes = 0; bNumBytes < bProgBytes; bNumBytes++ ) {
            if ( *( Byte + bNumBytes ) != 0xFF )    break;
        }

        // The data is empty and don't need to be programmed.
        if ( bNumBytes == bProgBytes )  break;
        // update data to chipset SPI data transfer registers.
        for ( bNumBytes = 0; bNumBytes < bProgBytes; bNumBytes++ ) {
            for ( wRetry = 0; wRetry < 0x400; wRetry ++ ) {
                *(volatile UINT8*)( gSPIBASE+SPI_DAT0+bNumBytes ) =
                                                            *( Byte+bNumBytes );
                // verified for checking the data is correct.
                if ( *(Byte+bNumBytes) == *(volatile UINT8*)
                                            ( gSPIBASE+SPI_DAT0+bNumBytes ) )
                    break;
            }
        }
        *(volatile UINT32*)( gSPIBASE + SPI_ADR ) =
                                    (UINT32)( pByteAddress + gBiosRegionBase );
        // BIT14 - indicate that it's data cycle.
        wSpiCmd = ( 1 << 14 );
        // BIT[8..13] - update the number of bytes to be written.
        wSpiCmd += ( bProgBytes - 1 ) << 8;
        // opcode index 0 is programmed for program command.
        // Set BIT1 (Go), BIT2(Atomic w/ Prefix)
        wSpiCmd += ( SPI_OPCODE_WRITE_INDEX << 4) + BIT01 + BIT02;
        *(volatile UINT16*)( gSPIBASE + SPI_CTL ) = wSpiCmd;
        // wait for chipset SPI cycle completed.
        WaitForSpiCycleDone();
        // wait for chipset SPI flash operation completed.
        WaitForWriteOperationCompleted();
        // write operation appeared to succeed, now read back byte and compare
        // set control for 1-byte data read, no prefix
        for ( bNumBytes = 0; bNumBytes < bProgBytes; bNumBytes++ ) {
            if (*(Byte + bNumBytes) != CommonSpiReadByte (
                        (UINT32)( pByteAddress + bNumBytes + gBiosRegionBase )))
                break;
        }
        if ( bNumBytes == bProgBytes )  break;
    }
    // Don't forget to return the number of bytes not written
    *Length = *Length - (UINT32)bProgBytes;
    return;

    ---------------------   PORTING REQUIRED   ---------------------*/

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiReadCommand
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
CommonSpiReadCommand   (
    IN  volatile UINT8      *pByteAddress,
    OUT UINT8               *Byte,
    IN  OUT UINT32          *Length
)
{
    UINT32              dReadAddress = 0, dNumBytes = 0;

    InitializeSpiEnvironment( &mExFlashPart.FlashCommandMenu );
    dReadAddress = CommonConvertSpiAddress ( pByteAddress );
    for ( dNumBytes = 0; dNumBytes < *Length ; dNumBytes++ )
        *( Byte + dNumBytes ) = CommonSpiReadByte( dReadAddress + dNumBytes );
    *Length = 0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiIsEraseCompleted
//
// Description: This function verifies whether the block erase
//      command is completed and returns the status of the command
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
BOOLEAN
CommonSpiIsEraseCompleted   (
    IN  volatile UINT8          *pBlockAddress,
    OUT BOOLEAN                 *pError,
    OUT UINTN                   *pStatus
)
{
    UINT32                      dNumBytes;

    for ( dNumBytes = 0; dNumBytes < FlashBlockSize; dNumBytes++ ) {
        if ( *(volatile UINT8*)( pBlockAddress + dNumBytes ) != 0xFF ) {
            *pStatus = EFI_NOT_READY;
            *pError = TRUE;
            break;
        }
    }
    *pError = FALSE;
    *pStatus = EFI_SUCCESS;
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiIsProgramCompleted
//
// Description: This function verifies whether the program (page or byte)
//      command is completed and returns the status of the command
//
// Input:   *pByteAddress   Location of the program command
//          Byte            Last data byte written
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
BOOLEAN
CommonSpiIsProgramCompleted (
    IN  volatile UINT8          *pByteAddress,
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
            *pStatus = EFI_NOT_READY;
            *pError = TRUE;
            break;
        }
    }
    *pError = FALSE;
    *pStatus = EFI_SUCCESS;
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiBlockWriteEnable
//
// Description: This function contains any flash specific code need to
//              enable a particular flash block write
//
// Input:   *pBlockAddress - Address within the block to write enable
//
// Output:      None
//
// Return:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CommonSpiBlockWriteEnable   (
    IN volatile UINT8       *pBlockAddress
)
{

/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT8                   bStatusReg = 0, bPrefixOp, bDataPhase = 1;
    UINT16                  wNumSector = 1;
    UINT32                  dSectorAddr = 0;

    bStatusReg = CommonSpiReadStatus();
    switch ( (UINT8)mExFlashPart.FlashVenDevId ) {
        // if SST flash, prefix 1 w/o address
        case 0xBF :
            bStatusReg &= 0x1C;
            bPrefixOp = SPI_PREFIX_WRITE_S_EN;
            break;
        // if ATMEL flash, prefix 0 w/ address
        case 0x1F :
            bStatusReg &= 0xC;
            dSectorAddr = ~(UINT32)mExFlashPart.FlashCapacity + 1;
            wNumSector = ( mExFlashPart.FlashCapacity/FlashAPI->FlashSectorSize );
            bPrefixOp = SPI_PREFIX_WRITE_EN;
            bDataPhase = 0;
            break;
        default :
        // default flash, prefix 0 w/o address
            bStatusReg &= 0x1C;
            bPrefixOp = SPI_PREFIX_WRITE_EN;
    }
    if ( bStatusReg ) {
        for ( ; wNumSector > 0; wNumSector-- ) {
            CommonSpiWriteStatus (  0,
                                    SPI_OPCODE_WRITE_S_INDEX,
                                    bDataPhase,
                                    bPrefixOp,
                                    dSectorAddr );
            dSectorAddr += FlashAPI->FlashSectorSize;
        }
    }

    ---------------------   PORTING REQUIRED   ---------------------*/

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiBlockWriteDisable
//
// Description: This function contains any flash specific code need to
//              disable a particular flash block write
//
// Input:   *pBlockAddress - Address within the block to write disable
//
// Output:  None
//
// Return:  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CommonSpiBlockWriteDisable  (
    IN volatile UINT8           *pBlockAddress
)
{
#if BLOCK_PROTECT_ENABLE
/*  ---------------------   PORTING REQUIRED   ---------------------

    UINT8                   bStatusReg = 0, bPrefixOp, bDataPhase = 1;
    UINT8                   bOpmenuIndex;
    UINT16                  wNumSector = 1;
    UINT32                  dSectorAddr = 0;

    bStatusReg = CommonSpiReadStatus();
    bOpmenuIndex = SPI_OPCODE_WRITE_S_INDEX;
    switch ( (UINT8)mExFlashPart.FlashVenDevId ) {
        // if SST flash, prefix 1 w/o address
        case 0xBF :
            bStatusReg &= 0x1C;
            bPrefixOp = SPI_PREFIX_WRITE_S_EN;
            break;
        // if ATMEL flash, prefix 0 w/ address
        case 0x1F :
            bStatusReg &= 0xC;
            dSectorAddr = ~(UINT32)mExFlashPart.FlashCapacity + 1;
            wNumSector = ( mExFlashPart.FlashCapacity/FlashAPI->FlashSectorSize );
            bPrefixOp = SPI_PREFIX_WRITE_EN;
            bOpmenuIndex = SPI_OPCODE_WRITE_E_INDEX;
            bDataPhase = 0;
            break;
        default :
        // default flash, prefix 0 w/o address
            bStatusReg &= 0x1C;
            bPrefixOp = SPI_PREFIX_WRITE_EN;
    }
    if ( !bStatusReg ) {
        for ( ; wNumSector > 0; wNumSector-- ) {
            CommonSpiWriteStatus (  0x1C,
                                    bOpmenuIndex,
                                    bDataPhase,
                                    bPrefixOp,
                                    dSectorAddr );
            dSectorAddr += FlashAPI->FlashSectorSize;
        }
    }

    ---------------------   PORTING REQUIRED   ---------------------*/
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiDeviceWriteEnable
//
// Description: This function contains any flash specific code need to
//              enable flash write
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
CommonSpiDeviceWriteEnable (VOID)
{
    // check is DeviceWrite enabled, if yes, don't enable it again, else, enable it.
    if ( !gbDeviceWriteEnabled ) {
        gbDeviceWriteEnabled = 1;
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiDeviceWriteDisable
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
VOID
CommonSpiDeviceWriteDisable (VOID)
{
    // check is DeviceWrite enabled, if yes, disable it, 
    // if no, don't disable it.
    if ( gbDeviceWriteEnabled ) {
        gbDeviceWriteEnabled = 0;
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CommonSpiDeviceVirtualFixup
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
CommonSpiDeviceVirtualFixup (
    IN EFI_RUNTIME_SERVICES  *pRS
)
{

//  // Following is an example code for virtual address conversion
//  pRS->ConvertPointer(0, (VOID**)&FlashDeviceBase);

//-    SpiChipsetVirtualFixup(pRS);
    gbDeviceVirtual = 1;

    return;
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