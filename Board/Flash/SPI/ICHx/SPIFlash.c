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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Flash/SPI/ICHx/SPIFlash.c 1     11/02/17 1:44a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 11/02/17 1:44a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Flash/SPI/ICHx/SPIFlash.c $
// 
// 1     11/02/17 1:44a Chienhsieh
// [TAG]  		EIP358409
// [Category]  	Improvement
// [Description]  	[SAx0039][Flash_17/16/14/11/10/09/08/7] SPI security
// [Files]  		Board\Flash\SPI\ICHx\SPIFlash.c
// 
// 19    6/10/13 5:26a Calvinchen
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hangs in EFI OS if Nvram Garbage collection occurred
// [RootCause]  	RCBA base don't convert to virtual address causes system
// hangs at checking TOP_SWAP bit.
// [Solution]  	Need to convert RCBA base.
// [Files]  		SPIFlash.c
// 
// 18    3/08/13 3:37a Calvinchen
// [TAG]  		EIP110515
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Microchip SST26VF064B & SST26VF064BA 8MB SPI Flash part
// support 
// [RootCause]  	Need "Global Block Protection Unlock" before programming.
// [Solution]  	Added "Global Block Protection Unlock" before programming.
// [Files]  		SPIFlash.c
// 
// 17    12/11/12 5:54a Calvinchen
// [TAG]  		EIP108531
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Unable to use AMI Flash Lib inside DXE Core
// [RootCause]  	Procedure Name duplicated
// [Solution]  	Rename IoDelay to SpiIoDelay
// [Files]  		SpiFlash.c
// 
// 16    10/31/12 3:08a Calvinchen
// [TAG]  		EIP104018
// [Category]  	Improvement
// [Description]  	Changes for Top Swap enabled.
// [Files]  		SpiFlash.c
// 
// 15    10/18/12 3:05a Calvinchen
// Added SFDP support for VSCC.
// 
// 14    9/25/12 12:10a Calvinchen
// [TAG]  		EIP97017
// [Category]  	Improvement
// [Description]  	1. MahoBay Flash error fail save
// 2. Keep Quad Enable bit (Bit6) of Status Register for MXIC flash.
// [Files]  		SPIFlash.c
// 
// 13    1/12/12 1:08a Calvinchen
// [TAG]  		EIP80707
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Flash Error
// [RootCause]  	Coding Mistake.
// [Solution]  	Fix coding mistake.
// [Files]  		SPIFlash.c
// 
// 12    2/10/11 3:27a Calvinchen
// Bug Fixed : (EIP#53185)Reading 64 Bytes failed if cross over 4K
// boundary.
// Description : This is supposed to be an ICH/PCH limitation.
// 
// 11    10/25/10 9:41a Calvinchen
// Very Slow SPI Read Byte Access.
// 
// 10    10/25/10 6:22a Calvinchen
// (EIP45843)Very Slow SPI Read Byte Access.
// 
// 9     9/14/10 3:25a Calvinchen
// Added the "SPI_INITIALIAL_WITH_VSCC" token for VSCC register
// initialize.
// 
// 8     5/21/10 2:14a Calvinchen
// Bug fixed: Build failed with "undeclared identifier".
// 
// 7     3/11/10 6:41a Calvinchen
// Improvement : Added SST AAIWordProgram SPI command to speed up the
// programming time with Intel chipset.
// 
// 6     6/24/09 3:25a Calvinchen
// (EIP22177) Updated for Aptio Source Enhancement.
//
// 5     4/27/09 3:30a Calvinchen
// 2.(EIP20459) Added Multiple SPI CSP component support.
//
// 4     12/03/08 1:00a Calvinchen
// (EIP17945)Bug Fixed : Fail to unlock the BIOS region of Flash
// Descriptor.
//
// 3     8/26/08 3:02a Calvinchen
// 1.Fixed Fail to un-protect ATMEL flash.
// 2.Fixed Building failed if ICH_FDOC/FDOD not defined.
// 3.Increase the Timeout counter for waiting the ICH SPI cycle done.
//
// 2     6/26/08 6:56a Calvinchen
// Generic bug fixed.
//
// 1     3/13/08 6:37a Calvinchen
// Added support for Intel ICHx SPI.
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
// ICH8/9/10 SPI register defines.
#define     SPI_STS                     0x90    //  SPI Status
#define     SPI_CTL                     0x91    //  SPI Control
#define     SPI_ADR                     0x08    //  SPI Address
#define     SPI_DAT0                    0x10    //  SPI Data 0
#define     SPI_PREOP                   0x94    //  Prefix Opcode Configuration
#define     SPI_OPTYPE                  0x96    //  Opcode Type Configuration
#define     SPI_OPMENU                  0x98    //  Opcode Menu Configuration
#define     RCRB_MMIO_BUC               0x3414  //  Backed Up Control Register
//  SPI default opcode slots
#define     SPI_OPCODE_WRITE_INDEX      0x0
#define     SPI_OPCODE_READ_INDEX       0x1
#define     SPI_OPCODE_ERASE_INDEX      0x2
#define     SPI_OPCODE_READ_S_INDEX     0x3
#define     SPI_OPCODE_READ_ID_INDEX    0x4
#define     SPI_OPCODE_WRITE_S_INDEX    0x5
#define     SPI_OPCODE_WRITE_S_E_INDEX  0x6
#define     SPI_OPCODE_WRITE_E_INDEX    0x7
#define     SPI_OPCODE_AAI_INDEX        0x6
#define     SPI_OPCODE_WRITE_D_INDEX    0x7
#define     SPI_PREFIX_WRITE_S_EN       0x1
#define     SPI_PREFIX_WRITE_EN         0x0
#define     SPI_MAX_DATA_TRANSFER       0x40
#define     ICHX_FDOC                   0xb0    // Flash Descriptor Observability Control Register
#define     ICHX_FDOD                   0xb4    // Flash Descriptor Observability Data Register
#define     FLASH_VALID_SIGNATURE       0x0ff0a55a
#define     NO_ADDRESS_UPDATE           0
#ifndef     SPI_OPCODE_TYPE_READ_NO_ADDRESS
#define     SPI_OPCODE_TYPE_READ_NO_ADDRESS     0x0
#define     SPI_OPCODE_TYPE_WRITE_NO_ADDRESS    0x1
#define     SPI_OPCODE_TYPE_READ_WITH_ADDRESS   0x2
#define     SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS  0x3
#endif
#define     SPI_FLASH_DEVICE_BASE_ADDRESS       (0xFFFFFFFF-FLASH_SIZE+1)   // [ EIP358409 ]
//----------------------------------------------------------------------------
// Module level global data
extern UINT16       gFlashId;
extern FLASH_PART   *FlashAPI;
//----------------------------------------------------------------------------
// Function Externs
extern
VOID
SpiChipsetVirtualFixup  (
    IN EFI_RUNTIME_SERVICES *pRS
);
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
// [ EIP358409 ]+>>>
VOID
SpiBlockProtectUpdate (
    IN volatile UINT8           *pBlockAddress,
    IN UINT8                    bStatusData
);
// [ EIP358409 ]+<<<
//----------------------------------------------------------------------------
// Local Variables
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
      FLASH_SIZE,           // flash size, should be changed in Init function
      0,                    // flash part id, should be changed in Init function
      0                     // flash part string, should be changed in
                            // Init function
};
volatile UINT8  *gSPIBASE = (UINT8*)(UINTN)(SB_RCBA + SPI_BASE_ADDRESS);
volatile UINT8  *gRCBABASE = (UINT8*)(UINTN)SB_RCBA;
UINT8           gbDeviceVirtual = 0;
UINT8           gbDeviceWriteEnabled = 0;
//----------------------------------------------------------------------------
// Function Definitions

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SpiIoDelay
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
SpiIoDelay (VOID)
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
    UINT32              dTimeout;
    UINT8               bCyclyDone;

    for ( dTimeout = 0, bCyclyDone = 0; dTimeout < 0x4000000; dTimeout++ ) {
        bCyclyDone = *(volatile UINT8*)( gSPIBASE + SPI_STS );
        if ( bCyclyDone & BIT02 ) break;
    }
    // write BIT2 to clear CycleDone status
    *(volatile UINT8*)( gSPIBASE + SPI_STS ) = BIT02;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SpiWriteDisable
//
// Description: This procedure issuess SPI Write Disable if AAIWordProgram. 
//
// Input:       None.
//
// Output:      None.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SpiWriteDisable (VOID)
{
    // Opcode menu slot 7 is configured as "Write Disable" if AAIWordProgram.
    *(volatile UINT16*)(gSPIBASE + SPI_CTL) = \
                                ( SPI_OPCODE_WRITE_D_INDEX << 4) + BIT01;
    // wait for chipset SPI cycle completed.
    WaitForSpiCycleDone();
    return ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CheckAaiWordProram
//
// Description: This procedure checks whether issues the AAIWordProgram command. 
//
// Input:       dAddr   - Start address to be written.
//              dLength - Number of bytes to be written.
//
// Output:      TRUE    - Yes
//              FALSE   - No
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
CheckAaiWordProram (
    IN UINT32               dAddr,
    IN UINT32               dLength
)
{
    if ((mExFlashPart.AAIWordProgram != 0) && !(dAddr & 1) && (dLength >= 2))
        return TRUE;
    return FALSE;    
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
CommonSpiReadStatus   (
    IN UINT32               dUpdateAddr
)
{
    UINT16  wSpiCmd;

    if( dUpdateAddr ) *(volatile UINT32*)( gSPIBASE + SPI_ADR ) = dUpdateAddr;
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
    UINT16              wWaitStsRetry;
    UINT8               bStatus;

    for( wWaitStsRetry = 0; wWaitStsRetry < 0xFFFF; wWaitStsRetry++ ) {
        // read flash status register.
        bStatus = CommonSpiReadStatus( NO_ADDRESS_UPDATE );
        // Is operation busy ?
        if( !( bStatus & 0x1 ) ) break;
    }
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
    UINT8           bData;
    UINT32          dLength = sizeof(UINT8);
    CommonSpiReadCommand((volatile UINT8*)dByteAddress, &bData, &dLength);
    return bData;
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
EFI_STATUS
CommonConvertSpiAddress   (
    IN  volatile UINT8      *pAddress,
    OUT UINT32              *pdCnvtAddress
)
{
    UINT32              dIchSpiFDOD;
    static UINT32       gBiosRegionBase = 0, gBiosRegionLimit = 0;

    // if flash identified, here checks the BIOS region of Flash
    // Descriptor Table.
    if ( mExFlashPart.FlashVenDevId ) {
        if ( !gBiosRegionBase ) {
            *(volatile UINT32*)( gSPIBASE + ICHX_FDOC ) = 0;
            dIchSpiFDOD = *(volatile UINT32*)( gSPIBASE + ICHX_FDOD );
            if ( dIchSpiFDOD == FLASH_VALID_SIGNATURE ) {
                *(volatile UINT32*)( gSPIBASE + ICHX_FDOC ) = ( BIT13 + BIT02 );
                do {
                    dIchSpiFDOD = *(volatile UINT32*)( gSPIBASE + ICHX_FDOD );
                } while( dIchSpiFDOD == FLASH_VALID_SIGNATURE );
                gBiosRegionBase = ( ( (dIchSpiFDOD >> 16) + 1 ) << 12 );
                gBiosRegionLimit = ((dIchSpiFDOD >> 4) | 0xfff) + 1;
            }
            else {
                gBiosRegionBase = mExFlashPart.FlashCapacity;
                gBiosRegionLimit = mExFlashPart.FlashCapacity;
            }    
        }
    }
    if ( gbDeviceVirtual ) {
        // pAddress - offset from Flash Device Base.
        pAddress -= FlashDeviceBase;
        // pAddress - 32bit memory mapping address.
        pAddress += (0xFFFFFFFF - FLASH_SIZE) + 1;
    }
    // pAddress - physical address in flash.
    pAddress += gBiosRegionBase;
    if ((UINT32)pAddress >= gBiosRegionLimit) return EFI_INVALID_PARAMETER;
    *pdCnvtAddress = (UINT32)pAddress;
    return EFI_SUCCESS;
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
    IN OUT  FLASH_INFO      *FlashInfo
)
{
    //Program first DWORD of opcode commands
    *((volatile UINT32*)( gSPIBASE + R_RCRB_SPI_OPMENU + 0 )) = (UINT32)
        // Write Byte
        ( (FlashInfo->Write.Opcode << (SPI_OPCODE_WRITE_INDEX * 8)) | \
        // Read Data
          (FlashInfo->Read.Opcode << (SPI_OPCODE_READ_INDEX * 8)) | \
        // Erase 64k Sector
          (FlashInfo->Erase.Opcode << (SPI_OPCODE_ERASE_INDEX * 8)) | \
        // Read Device Status Reg
          (FlashInfo->ReadStatus.Opcode << (SPI_OPCODE_READ_S_INDEX * 8)) );

    //Program second DWORD of Opcode commands
    *((volatile UINT32*)( gSPIBASE + R_RCRB_SPI_OPMENU + 4 )) = (UINT32)
        // Read device ID
      ((FlashInfo->ReadId.Opcode << ((SPI_OPCODE_READ_ID_INDEX - 4) * 8)) | \
        // Write Status Register
       (FlashInfo->WriteStatus.Opcode << \
                                    ((SPI_OPCODE_WRITE_S_INDEX - 4) * 8)) | \
        // Write Status Enable Register
       (FlashInfo->WriteStatusEnable.Opcode << \
                                    ((SPI_OPCODE_WRITE_S_E_INDEX - 4) * 8)));

    //Program opcode types
    *((volatile UINT16*)( gSPIBASE + R_RCRB_SPI_OPTYPE )) = (UINT16)
        // write with address.
        (FlashInfo->Write.OpcodeType << (SPI_OPCODE_WRITE_INDEX * 2) | \
        // read with address.
         FlashInfo->Read.OpcodeType << (SPI_OPCODE_READ_INDEX * 2) | \
        // write with address.
         FlashInfo->Erase.OpcodeType << (SPI_OPCODE_ERASE_INDEX * 2) | \
        // read w/o no adress.
         FlashInfo->ReadStatus.OpcodeType << (SPI_OPCODE_READ_S_INDEX * 2) | \
        // read with address.
         FlashInfo->ReadId.OpcodeType << (SPI_OPCODE_READ_ID_INDEX * 2) | \
        // write w/o address.
         FlashInfo->WriteStatus.OpcodeType << (SPI_OPCODE_WRITE_S_INDEX * 2) | \
        // write w/o address.
         FlashInfo->WriteStatusEnable.OpcodeType << \
                                    (SPI_OPCODE_WRITE_S_E_INDEX * 2));

    //set up the prefix opcodes for commands
    *((volatile UINT16*)( gSPIBASE + R_RCRB_SPI_PREOP )) = (UINT16)
        ( ( FlashInfo->WriteStatusEnable.Opcode << 8 ) | \
                                    ( FlashInfo->WriteEnable.Opcode ) );

    //set up Program Opcode and Optype if AAIWordProgram.
    if (mExFlashPart.AAIWordProgram != 0) {
        UINT8  bOpType = 0;
        *((volatile UINT16*)(gSPIBASE + R_RCRB_SPI_OPMENU + 6)) = 0x4ad; 
        bOpType = *((volatile UINT8*)(gSPIBASE + R_RCRB_SPI_OPTYPE + 1));
        bOpType = ((bOpType & 0xf) | \
                 (SPI_OPCODE_TYPE_WRITE_NO_ADDRESS << 6) | \
                 (SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS << 4));
        *((volatile UINT8*)(gSPIBASE + R_RCRB_SPI_OPTYPE + 1)) = bOpType;
    }
    return ;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SerialFlashDiscoveryForQuadRead
//
// Description: This procedure checks SPI Quad Read support through SFDP.
//
// Input:       None.
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SerialFlashDiscoveryForQuadRead (VOID)
{
#if defined SPI_INITIALIZE_WITH_VSCC && SPI_INITIALIZE_WITH_VSCC == 1
    UINT8               SfdpData[256]; 
    UINT16              wSpiCmd, wOffset, j;
    UINT32              Index;
    // Serial Flash Discoverable Parameters Command "0x5A".
  	*(volatile UINT8*)(gSPIBASE + SPI_OPMENU + 7) = 0x5a;
  	// Do nothing if SPI Registers is locked.
  	if (*(volatile UINT8*)(gSPIBASE + SPI_OPMENU + 7) != 0x5a) 
  	    return EFI_WRITE_PROTECTED;
  	// Update SPI OpMenu[7] to "READ WITH ADDRESS".
  	SfdpData[0] = *(volatile UINT8*)(gSPIBASE + SPI_OPTYPE + 1);
    *(volatile UINT8*)(gSPIBASE + SPI_OPTYPE + 1) = (SfdpData[0] & 0x3f) | 0x80;
   	MemSet(SfdpData, 256, 0);
    for (Index = 0; Index < 256; Index += 64) {
    	// Set SPI read-address = 0, 64, 128, 256 
    	*(volatile UINT32*)(gSPIBASE + SPI_ADR) = Index;
    	// set opcode for "5A"
    	wSpiCmd = SPI_OPCODE_WRITE_E_INDEX << 4;
    	// set transaction = 64 bytes
    	wSpiCmd += ((64 - 1) << 8);
    	// indicate that data phase is required
    	wSpiCmd += (1 << 14);
    	// Go (BIT1)
    	*(volatile UINT16*)(gSPIBASE + SPI_CTL) =  wSpiCmd + BIT01;
    	WaitForSpiCycleDone();
    	for (j = 0; j < 64; j++)
    	    *(SfdpData + Index + j) = *(volatile UINT8*)(gSPIBASE + SPI_DAT0 + j);
  	    // Serial Flash Discoverable Parameters (SFDP) Signature = 50444653h
    	if (Index == 0) {
    	    wOffset = 0;
    	    if (*(UINT32*)&SfdpData[wOffset] != 0x50444653) {
                if (*(UINT32*)&SfdpData[++wOffset] != 0x50444653) 
                    return EFI_UNSUPPORTED;
            }        
        }            
    }
  	// SFDP opode at address Ch bits 23:00 = Parameter ID 0 table Address
  	Index = (*(UINT32*)&SfdpData[wOffset + 0xC] & 0x00FFFFFF);
  	// SFDP opode at address 05h(SFPD Major Revisions) must = 0001h
  	// SFDP opode at address 0Ah(Serial Flash Basic Major Revisions) must = 0001h
  	if ((SfdpData[wOffset + 5] != 0x1) || (SfdpData[wOffset + 0xA] != 0x1) || \
        ((Index + 0x10) > 256)) return EFI_UNSUPPORTED;
    // Parameter ID 0 Table BIT[21] - Fast Read Quad I/O.
    // Parameter ID 0 Table BIT[22] - Fast Read Quad Output.
    if (*(UINT32*)&SfdpData[Index + 1] & (BIT21 + BIT22)) return EFI_SUCCESS;
#endif
    return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GlobalBlockProtectionUnlock
//
// Description: This procedure unlocks "Global Block Protection" for Microchip
//              26VF series flash parts. 
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GlobalBlockProtectionUnlock (VOID)
{
    UINT8           SavedOpType;
    
    if (mExFlashPart.GlobalBlockUnlock != TRUE) return;
    // Serial Flash Discoverable Parameters Command "0x5A".
  	*(volatile UINT8*)(gSPIBASE + SPI_OPMENU + 7) = 0x98;
  	// Do nothing if SPI Registers is locked.
  	if (*(volatile UINT8*)(gSPIBASE + SPI_OPMENU + 7) != 0x98) return;
  	// Update SPI OpMenu[7] to "WRITE W/O ADDRESS".
  	SavedOpType = *(volatile UINT8*)(gSPIBASE + SPI_OPTYPE + 1);
    *(volatile UINT8*)(gSPIBASE + SPI_OPTYPE + 1) = (SavedOpType & 0x3f) | BIT06;
    // Opcode menu slot 7 is configured as "Write Disable" if AAIWordProgram.
    *(volatile UINT16*)(gSPIBASE + SPI_CTL) = \
                                    (SPI_OPCODE_WRITE_D_INDEX << 4) + BIT01;
    // wait for chipset SPI cycle completed.
    WaitForSpiCycleDone();
    return ;
}
// [ EIP358409 ]+>>>
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RemoveWriteStatusOpcode
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
RemoveWriteStatusOpcode (
    IN OUT  FLASH_INFO      *FlashInfo
)
{
    
	FlashInfo->WriteStatus.Opcode = FlashInfo->ReadId.Opcode;
	FlashInfo->WriteStatus.OpcodeType = FlashInfo->ReadId.OpcodeType;
	
    //Program second DWORD of Opcode commands
    *((volatile UINT32*)( gSPIBASE + R_RCRB_SPI_OPMENU + 4 )) = (UINT32)
        // Read device ID
      ((FlashInfo->ReadId.Opcode << ((SPI_OPCODE_READ_ID_INDEX - 4) * 8)) | \
        // Write Status Register
       (FlashInfo->WriteStatus.Opcode << \
                                    ((SPI_OPCODE_WRITE_S_INDEX - 4) * 8)) | \
        // Write Status Enable Register
       (FlashInfo->WriteStatusEnable.Opcode << \
                                    ((SPI_OPCODE_WRITE_S_E_INDEX - 4) * 8)));

    //Program opcode types
    *((volatile UINT16*)( gSPIBASE + R_RCRB_SPI_OPTYPE )) = (UINT16)
        // write with address.
        (FlashInfo->Write.OpcodeType << (SPI_OPCODE_WRITE_INDEX * 2) | \
        // read with address.
         FlashInfo->Read.OpcodeType << (SPI_OPCODE_READ_INDEX * 2) | \
        // write with address.
         FlashInfo->Erase.OpcodeType << (SPI_OPCODE_ERASE_INDEX * 2) | \
        // read w/o no adress.
         FlashInfo->ReadStatus.OpcodeType << (SPI_OPCODE_READ_S_INDEX * 2) | \
        // read with address.
         FlashInfo->ReadId.OpcodeType << (SPI_OPCODE_READ_ID_INDEX * 2) | \
        // write w/o address.
         FlashInfo->WriteStatus.OpcodeType << (SPI_OPCODE_WRITE_S_INDEX * 2) | \
        // write w/o address.
         FlashInfo->WriteStatusEnable.OpcodeType << \
                                    (SPI_OPCODE_WRITE_S_E_INDEX * 2));

   
    return ;
}
// [ EIP358409 ]+<<<
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
    IN OUT  FLASH_INFO      *FlashInfo
)
{
    UINT8 *BlockAddress;    // [ EIP358409 ]
#if defined SPI_INITIALIZE_WITH_VSCC && SPI_INITIALIZE_WITH_VSCC == 1
    // Program UPPER/LOWER VSCC register.
    UINT32          dVSCC = 0;
    EFI_STATUS      Status;
    // Erase Opcode. 
    dVSCC = FlashInfo->Erase.Opcode << 8;
    // Block/Sector Erase Size.
    if (FlashInfo->SectorSize == SECTOR_SIZE_4KB) dVSCC |= BIT00;
    else if (FlashInfo->SectorSize == SECTOR_SIZE_8KB) dVSCC |= BIT01;
    else if (FlashInfo->SectorSize == SECTOR_SIZE_64KB) dVSCC |= (BIT00 + BIT01);
    // Write Granularity.
    if (FlashInfo->PageSize != 1) dVSCC |= BIT02;
    // Write Status Required.
    if (FlashInfo->WriteStatusEnable.Opcode == 0x50) dVSCC |= BIT03;
    // Write Enable On Write Status.
    if (FlashInfo->WriteStatusEnable.Opcode == 0x39) dVSCC |= BIT04;
    Status = SerialFlashDiscoveryForQuadRead();
    if (!EFI_ERROR(Status)) {
        switch ((UINT8)mExFlashPart.FlashVenDevId) {
            case 0xEF : // Winbond         
            case 0x37 : // AMIC
            case 0x01 : // Spansion
                dVSCC |= BIT5;  break;
            case 0xC2 : // MXIC
                dVSCC |= BIT6;  break;
            case 0x1F : // Atmel
                dVSCC |= (BIT5 + BIT6); break;
            case 0xBF : // SST/Microchip
                dVSCC |= BIT7;  break;
                break;
            default : break;
        }
    }    
    if (Status != EFI_WRITE_PROTECTED) {
#if LOWER_VSCC_REG != 0
        *(volatile UINT32*)(gSPIBASE + LOWER_VSCC_REG) = dVSCC;
#endif 
#if UPPER_VSCC_REG != 0
        *(volatile UINT32*)(gSPIBASE + UPPER_VSCC_REG) = dVSCC;
#endif 
    }
#endif 
    GlobalBlockProtectionUnlock();
    InitializeSpiEnvironment ( FlashInfo );
// [ EIP358409 ]+>>>
	BlockAddress = (UINT8*)SPI_FLASH_DEVICE_BASE_ADDRESS;
	SpiBlockProtectUpdate (BlockAddress, 0);
	RemoveWriteStatusOpcode(FlashInfo);	
// [ EIP358409 ]+<<<
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
    IN      FLASH_INFO      *FlashInfo,
    IN OUT  UINT32          *dFlashId
)
{
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
    SpiIoDelay();
    *dFlashId = *(volatile UINT32*)( gSPIBASE + SPI_DAT0 ) & 0x00FFFFFF;
    return  TRUE;
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
    volatile UINT32     dSectorAddr;
    UINT32              dNByte, dPhyAddress;
    UINT16              wEraseRetry, wNumSectors, wSector;
    UINT16              wSpiCmd;

    // These parts only erase in 64K sectors
    InitializeSpiEnvironment( &mExFlashPart.FlashCommandMenu );
    wNumSectors = ( FlashBlockSize / FlashAPI->FlashSectorSize );
    for ( wSector = 0; wSector < wNumSectors ; wSector++ ) {
        dSectorAddr = (UINT32)(pBlockAddress + \
                                (wSector * FlashAPI->FlashSectorSize));
        if (EFI_ERROR(CommonConvertSpiAddress( \
                (volatile UINT8*)dSectorAddr, &dPhyAddress))) return;
        for ( dNByte = 0; dNByte < FlashAPI->FlashSectorSize; dNByte++ ) {
            if (0xFF != CommonSpiReadByte(dSectorAddr + dNByte)) break;
        }
        if  ( dNByte == FlashAPI->FlashSectorSize )   continue;
        for ( wEraseRetry = 0; wEraseRetry < FLASH_RETRIES; wEraseRetry++ ) {
            *(volatile UINT32*)( gSPIBASE + SPI_ADR ) = dPhyAddress;
            // opcode index 2 is programmed for erase command.
            // Set BIT1 (Go), BIT2(Atomic w/ Prefix)
            wSpiCmd = ( SPI_OPCODE_ERASE_INDEX << 4) + BIT01 + BIT02;
            *(volatile UINT16*)( gSPIBASE + SPI_CTL ) = wSpiCmd;
            // wait for chipset SPI cycle completed.
            WaitForSpiCycleDone();
            // wait for SPI flash operation completed.
            WaitForWriteOperationCompleted();
            // write operation appeared to succeed, now read back byte
            // and compare.
            if (CommonSpiReadByte(dSectorAddr) == 0xFF)   break;
        }
    }
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
    IN volatile UINT8       *pByteAddress,
    IN UINT8                *Byte,
    IN OUT UINT32           *Length
)
{
    UINT8               bFlashRetry = 0;
    UINT16              wProgBytes = 0, wNumBytes = 0;
    UINT16              wSpiCmd = 0, wRetry = 0, wMaxNumBytes = 0;
    UINT32              dPhyAddress = 0;


    InitializeSpiEnvironment( &mExFlashPart.FlashCommandMenu );
    wProgBytes = mCommonSpiFlash.FlashProgramSize;
    if ( mCommonSpiFlash.FlashProgramSize != 1 ) {
        // Limit the max transfer to the number of bytes the chipset can
        // transfer per cycle
        if ( *Length >= SPI_MAX_DATA_TRANSFER )
            wProgBytes = SPI_MAX_DATA_TRANSFER;
        else wProgBytes = *Length;
        // this is currently for the WINBOND parts only
        // mask off lowest 8 bits of address so that we can determine how
        // many bytes we can write before we hit the end of a page
        wMaxNumBytes = 0x100 - ((UINT32)pByteAddress & 0xFF);
        if ( (UINT32)pByteAddress & 0x1 )   wProgBytes = 1;
        else if ( wProgBytes > wMaxNumBytes ) wProgBytes = wMaxNumBytes;
    } else if(CheckAaiWordProram((UINT32)pByteAddress, *Length)) wProgBytes = 2;
    for ( bFlashRetry = 0; bFlashRetry < FLASH_RETRIES; bFlashRetry++ ) {
        // check if do the data need to be programmed ?
        for ( wNumBytes = 0; wNumBytes < wProgBytes; wNumBytes++ ) {
            if ( *( Byte + wNumBytes ) != 0xFF )    break;
        }
        // The data is empty and don't need to be programmed.
        if ( wNumBytes == wProgBytes )  break;
        // update data to chipset SPI data transfer registers.
        for ( wNumBytes = 0; wNumBytes < wProgBytes; wNumBytes++ ) {
            for ( wRetry = 0; wRetry < 0x400; wRetry ++ ) {
                *(volatile UINT8*)( gSPIBASE + SPI_DAT0 + wNumBytes ) = \
                                                         *( Byte + wNumBytes );
                // verified for checking the data is correct.
                if ( *( Byte + wNumBytes ) == \
                        *(volatile UINT8*)( gSPIBASE + SPI_DAT0 + wNumBytes ) )
                    break;
            }
        }
        if (EFI_ERROR(CommonConvertSpiAddress( \
                (volatile UINT8*)pByteAddress, &dPhyAddress))) return;
        *(volatile UINT32*)( gSPIBASE + SPI_ADR ) = dPhyAddress;
        // BIT14 - indicate that it's data cycle.
        wSpiCmd = ( 1 << 14 );
        // BIT[8..13] - update the number of bytes to be written.
        wSpiCmd += ( wProgBytes - 1 ) << 8;
        // opcode index 0 is programmed for program command.
        // Set BIT1 (Go), BIT2(Atomic w/ Prefix)
        if (CheckAaiWordProram(dPhyAddress, wProgBytes))
            wSpiCmd += ( SPI_OPCODE_AAI_INDEX << 4) + BIT01 + BIT02;
        else wSpiCmd += ( SPI_OPCODE_WRITE_INDEX << 4) + BIT01 + BIT02;
        *(volatile UINT16*)( gSPIBASE + SPI_CTL ) = wSpiCmd;
        // wait for chipset SPI cycle completed.
        WaitForSpiCycleDone();
        // wait for chipset SPI flash operation completed.
        WaitForWriteOperationCompleted();
        // Issue SPI Write Disable if SST AAIWordProgram supported.
        if (CheckAaiWordProram(dPhyAddress, wProgBytes)) SpiWriteDisable();
        // write operation appeared to succeed, now read back byte and compare
        // set control for 1-byte data read, no prefix
        for ( wNumBytes = 0; wNumBytes < wProgBytes; wNumBytes++ ) {
            if (*(Byte + wNumBytes) != \
                CommonSpiReadByte((UINT32)(pByteAddress + wNumBytes))) break;
        }
        if ( wNumBytes == wProgBytes )  break;
    }
    // Don't forget to return the number of bytes not written
    *Length = *Length - (UINT32)wProgBytes;
    return;
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
VOID CommonSpiReadCommand   (
    IN  volatile UINT8      *pByteAddress,
    OUT UINT8               *Byte,
    IN  OUT UINT32          *Length
)
{
    UINT32              dReadAddress = 0; 
    UINT16              wSpiCmd, i, wMaxRead = 0;

    InitializeSpiEnvironment( &mExFlashPart.FlashCommandMenu );
    if (EFI_ERROR(CommonConvertSpiAddress( \
                (volatile UINT8*)pByteAddress, &dReadAddress))) return;
    wMaxRead = 0x100 - (dReadAddress & 0xff);
    if (wMaxRead > SPI_MAX_DATA_TRANSFER) wMaxRead = SPI_MAX_DATA_TRANSFER;
    if (wMaxRead > *Length) wMaxRead = (UINT16)*Length;
    // update the read address.
    *(volatile UINT32*)( gSPIBASE + SPI_ADR ) = dReadAddress;
    // Opcode menu slot 1 is configured as "Read Flash"
    wSpiCmd = ( SPI_OPCODE_READ_INDEX << 4 ) + BIT01;
    // indicate that data phase is required
    wSpiCmd += (1 << 14);
    // BIT[8..13] - update the number of bytes to be read.
    wSpiCmd += (wMaxRead - 1) << 8;
    *(volatile UINT16*)( gSPIBASE + SPI_CTL ) = wSpiCmd;
    // wait for spi cycle completed.
    WaitForSpiCycleDone();
    // read data
    for (i = 0; i < wMaxRead; i++) 
        *(Byte + i) = *(volatile UINT8*)(gSPIBASE + SPI_DAT0 + i);
    *Length = *Length - (UINT32)wMaxRead;
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
    UINT8                       bByte;

    for ( dNumBytes = 0; dNumBytes < FlashBlockSize; dNumBytes++ ) {
        // Check for Top Swap enabled
        if (*(volatile UINT8*)(gRCBABASE + RCRB_MMIO_BUC) & BIT00)
            bByte = CommonSpiReadByte((UINT32)(pBlockAddress + dNumBytes));
        else bByte = *(volatile UINT8*)(pBlockAddress + dNumBytes);
        if (bByte != 0xFF) {   
            if ( pStatus ) *pStatus = EFI_NOT_READY;
            if ( pError ) *pError = TRUE;
            return FALSE;
        }
    }
    if ( pError ) *pError = FALSE;
    if ( pStatus ) *pStatus = EFI_SUCCESS;
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
    UINT8                       bByte, bReadByte;

    for ( dNumBytes = 0; dNumBytes < Length; dNumBytes++ ) {
        bByte = *(Byte + dNumBytes);
        // Check for Top Swap enabled
        if (*(volatile UINT8*)(gRCBABASE + RCRB_MMIO_BUC) & BIT00)
            bReadByte = CommonSpiReadByte((UINT32)(pByteAddress + dNumBytes));
        else bReadByte = *(volatile UINT8*)(pByteAddress + dNumBytes);
        if (bByte != bReadByte) {   
            if ( pStatus ) *pStatus = EFI_NOT_READY;
            if ( pError ) *pError = TRUE;
            return FALSE;
        }
    }
    if ( pError ) *pError = FALSE;
    if ( pStatus ) *pStatus = EFI_SUCCESS;
    return TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SpiBlockProtectUpdate
//
// Description: This function writes the status register.
//
// Input:   *pBlockAddress - Address within the block to write enable.
//          bStatusData - Value to be written to Status Register.
//
// Output:      None
//
// Return:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
SpiBlockProtectUpdate (
    IN volatile UINT8           *pBlockAddress,
    IN UINT8                    bStatusData
)
{
    UINT8                   bStatusReg = 0, bPrefixOp, bDataPhase = 1, bBPbits;
    UINT32                  dSectorAddr = 0;

    if (EFI_ERROR(CommonConvertSpiAddress(pBlockAddress, &dSectorAddr))) return;
    bStatusReg = CommonSpiReadStatus (dSectorAddr);
    bPrefixOp = SPI_PREFIX_WRITE_EN;    // Use Prefix 0 w/o address
    switch ( (UINT8)mExFlashPart.FlashVenDevId ) {
        case 0xBF :
            // if SST flash, prefix 1 w/o address
            if (mExFlashPart.GlobalBlockUnlock == TRUE) return;
            bBPbits = (BIT02 + BIT03 + BIT04 + BIT05);
            bPrefixOp = SPI_PREFIX_WRITE_S_EN;
            break;
        case 0x1F :
            // if ATMEL flash, prefix 0 w/ address
            bBPbits = (BIT02 + BIT03);
            break;
        case 0x20 :
            // if MXIC flash, keep Quad Enable bit (BIT6) state.
            bBPbits = (BIT02 + BIT03 + BIT04 + BIT06);
            break;
        default :
            bBPbits = (BIT02 + BIT03 + BIT04);
    }
    bStatusReg &= bBPbits;              // keep valid bits.
    bStatusData &= bBPbits;             // keep valid bits.
    if (bStatusReg != bStatusData) {
        CommonSpiWriteStatus (  bStatusData, \
                                SPI_OPCODE_WRITE_S_INDEX, \
                                bDataPhase, \
                                bPrefixOp, \
                                dSectorAddr );
    }                                
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
    SpiBlockProtectUpdate (pBlockAddress, 0);
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
    SpiBlockProtectUpdate (pBlockAddress, 0xff);
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
    // check is DeviceWrite enabled, if yes, don't enable it again,
    // else, enable it.
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
    pRS->ConvertPointer(0, (VOID **)&gSPIBASE);
    pRS->ConvertPointer(0, (VOID **)&gRCBABASE);
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