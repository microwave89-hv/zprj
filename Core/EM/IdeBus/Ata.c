//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/IdeBus/Ata.c 34    1/03/12 11:22p Rajkumarkc $
//
// $Revision: 34 $
//
// $Date: 1/03/12 11:22p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/IdeBus/Ata.c $
// 
// 34    1/03/12 11:22p Rajkumarkc
// // [TAG]        EIP 79612 & 80003
// // [Category]  	Bug Fix
// // [Description]System hangs with Blue screen during Win8 installation
// //              in IDE Mode (AMD Platforms)
// //              Use PLATFORM_IDE_PROTOCOL data instead of hard coded
// //              macro POWERON_BUSY_CLEAR_TIMEOUT in Ata.c file
// // [Files]  		Ata.c
// 
// 33    12/05/11 6:12p Rajkumarkc
// [TAG]  		EIP77142 
// [Category]  	Improvement
// [Description]	Added the function 'IdeNonDataCommandExp' in the
// 'IDE_BUS_PROTOCOL' and removed
//               the existing function 'IdeNonDataCommand' for supporting
// the upper 24bits of LBA.
// [Files]
//     Ata.c
//     IdeBus.c
//     Idebus.h
//     PIDEBus.h
// 
// 32    11/08/11 5:15a Deepthins
// [TAG]  		EIP74607 
// [Category]  	Improvement
// [Description]  	Block IO Read/Write function, the allignment should be
// proper. IoAlign value is 0 or 1 means that the buffer can be placed
// anywhere in memory. Otherwise, IoAlign must be a power of 2, and the
// requirement is that the start address of a buffer must be evenly
// divisible by IoAlign with no remainder.
// [Files]  		Ata.c, Atapi.c, AhciController.c
// 
// 31    11/07/11 4:25a Deepthins
// [TAG]  		EIP74607
// [Category]  	Improvement
// [Description]  	 IoAlign values is 0 or 1 means that the buffer can be
// placed anywhere in memory. Otherwise, IoAlign must be a power of 2, and
// the requirement is that the start address of a buffer must be evenly
// divisible by 2 to the power of IoAlign with no remainder.
// [Files]  		Ata.c
// 
// 30    11/07/11 12:37a Deepthins
// [TAG]  		EIP73941
// [Category]  	Improvement
// [Description]  	BufferSize is 0 , ReadBlock function should return
// EFI_SUCCESS without actual reading.
// [Files]  		Ata.c
// 
// 29    9/27/11 3:10a Rajeshms
// [TAG]  		EIP69295
// [Category]  	Improvement
// [Description]  	The Timeout values used by IDE and AHCI drivers are
// made as SDL tokens, so that the timeout values can be varied.
// [Files]  		IdeBusBoard.c, CORE_DXE.sdl, AhciSmm.h, AhciBus.h, IDESMM.h,
// Ata.c, Atapi.c, IdeBus.c, IdeBus.h, IdeBusMaster.c, IdeBusBoard.h
// 
// 28    8/12/11 4:12a Lavanyap
// [TAG]  		EIP66476
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	AtaPioDataOut fails for data write commands
// [RootCause]  	TempBuffer pointer has been assigned for both data read
// and write commands.
// [Solution]  	TempBuffer pointer has to be assigned only for data read
// commands.
// [Files]  		Ata.c
// 
// 27    3/28/11 4:44p Artems
// EIP 53849: fixed bug with build error in 32-bit debug mode
// 
// 26    12/23/10 3:54a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 25    11/02/10 12:01a Rameshr
// [TAG] - EIP 45266
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - E-SATA card will hang up on post and debug card show "AE
// [RootCause]- Device doesn't support any of the UDMA mode and function
// ReturnMsbbit returns incorrect values 
// [Solution] - If any of the bit is not set in Input value, ReturnMsbbit
// returns 0xFF.
// [Files] - Ata.c, AhciBus.c
// 
// 24    10/11/10 11:27a Krishnakumarg
// [TAG] - EIP 43249
// [Category] - IMPROVEMENT
// [Severity] - Minor
// [Symptom]  - Non-Ascii character in comments causing build problem in
// japanese XP
// [RootCause]- Presence of Non-Ascii character
// [Solution] -  Remove Non-Ascii character present in the file
// [Files] - IdeSecurity.c,IDESMM.c, InstallIdeSmi, Ata.c, Atapi.c,
// IDEBusComponentName.c, IdeBusMaster.c, IdeHPA.c, IdePowerManagement.c
// 
// 23    9/24/10 12:47a Rameshr
// [TAG] - EIP 44713
// [Category]- BUG FIX
// [Severity]- Major
// [Symptom] - SECURITY_ERASE_UNIT command is not working
// [RootCause] - Security Erase unit command timeout value is not proper.
// So getting Timeout error for this command. 
// [Solution] - Security Erase command timeout value should be from the
// Identify packet command word 89 
// [Files] - Ata.c
// 
// 22    8/25/10 4:07a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: All.
// 
// 21    4/16/10 4:05p Pats
// EIP 30719: Support for the HDD with sector size more than 512bytes.
// 
// 20    7/01/09 12:23p Rameshr
// Coding Standard and File header updated.
//
// 19    6/16/09 10:13a Rameshr
// if the Erase command timeout value is 0 or 255, wait for the Erase
// command completion without timeout value
// EIP:20630
//
// 18    3/29/09 11:13a Rameshr
// Security Erase command timeout value should be from the Identify packet
// command word 89
// EIP 20630
//
// 17    4/22/08 2:02p Felixp
// DXE_IDE_DETECT progress code moved from ATA.c to IdeBus.c
// DXE_IDE_ENABLE progress code added
//
// 16    3/06/08 4:42p Ambikas
//
// 15    3/04/08 7:51p Felixp
//
// 13    28/02/08 7:06p Anandakrishnanl
// Changed timeout values and DMA capability logic for DisableIdeInterrupt
// routine.
//
// 12    13/04/07 2:59p Anandakrishnanl
// Ide Bus Module - Update source files to comply with AMI coding
// standard"!!!
//
// 11    5/03/07 11:40a Anandakrishnanl
// Fix in Check Controller presence to detect Hard disk above 400 GB.
//
// 10    2/12/07 3:41p Pats
// Eliminated Check Drive Ready to reduce boot time on reset.
//
// 9     10/27/06 4:20p Felixp
// Reverted back to the previous version
//
// 7     10/12/06 2:02p Srinin
// Fixed problem in multiple read/Write word in PIO mode.
//
// 6     8/24/06 9:30a Felixp
// x64 support (bug fixes)
//
// 5     3/13/06 2:20a Felixp
//
// 4     1/09/06 11:36a Felixp
//
// 2     12/14/05 3:06p Srinin
// Idedevice detection logic modified.
//
// 1     12/01/05 9:43a Felixp
//
// 11    9/27/05 4:41p Olegi
// DisableIdeInterrupt is modified, added code to clear interrupt request.
//
// 10    8/22/05 4:31p Srinin
// ATA/ATAPI identification changed.
//
// 9     7/18/05 4:31p Felixp
// 64-bit compatibility warnings removed
//
// 8     4/25/05 9:55a Felixp
// bug fix in IssueAtaReadWriteCommand
//
// 7     3/04/05 11:33a Mandal
//
// 6     2/24/05 12:21p Felixp
// bug fix in AtaBlkRead and AtaBlkWrite functions:
// EFI_INVALID_PARAMETER was returned when last block is read or written
// to
//
// 5     2/01/05 12:59p Srinin
// IDE HotPlug Support added.
//
// 4     1/28/05 1:19p Felixp
// IdeBus is linked together with CORE_DXE
//
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 2     1/05/05 11:21a Srinin
// BusMaster and Password Support added.
//
// 1     12/10/04 1:01p Srinin
// Initial Checkin of IdeBus Driver.
//
//

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: Ata.c
//
// Description:	ATA Services
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>


#include "IdeBus.h"
#include <Protocol\IdeBusBoard.h>

extern PLATFORM_IDE_PROTOCOL    *gPlatformIdeProtocol;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	DetectIdeDevice
//
// Description:	Detects the ATA/ATAPI device
//
// Input:
//  IDE_BUS_PROTOCOL    *IdeBusInterface;
//
// Output:
//  EFI_STATUS
//
// Modified:
//
// Referrals: IdeBusStart
//
// Notes:
//  Here is the control flow of this function:
// 1. If controller not present return EFI_NOT_FOUND
// 2. If BSY bit not clear and DRDY not set, return EFI_DEVICE_ERROR
// 3. If Identify command fails, return EFI_NOT_FOUND
// 4. Else return Success
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DetectIdeDevice(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_STATUS Status;
    UINT16     Index;
    IO_REGS    Regs = IdeBusInterface->IdeDevice.Regs;
    UINT8      Data8;

    //
    // Check if the controller is present
    //
    Status = ControllerPresence( IdeBusInterface );

    if ( Status == EFI_NOT_FOUND ) {
        //
        // Status Reg is 0xff
        //
        return EFI_NOT_FOUND;  
    }

    if ( Status == EFI_DEVICE_ERROR ) {
        IdeSoftReset( IdeBusInterface );

        //
        //3 Sec loop
        //    
        for ( Index = 0; Index < 300; Index++ ) {
            //
            //check for BSY bit to be clear
            //
            Status = WaitforBitClear( IdeBusInterface->PciIO,
                                      Regs.CommandBlock.StatusReg,
                                      BSY,
                                      1 );          // 1 msec

            if ( Status == EFI_SUCCESS ) {
                break;
            }
            pBS->Stall( 10000 );                    // 10Msec
        }

        Status = ControllerPresence( IdeBusInterface );

        if ( EFI_ERROR( Status )) {
            //
            // Device couldn't be detected
            //
            return EFI_NOT_FOUND;   
        }
    }

    //    
    //Disable Interrupt
    //    
    DisableIdeInterrupt( IdeBusInterface );

    //
    //Select the drive
    //
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.DeviceReg,
                  IdeBusInterface->IdeDevice.Device << 4 );

    //
    //Check for BSY bit to be clear
    //
    Status = WaitforBitClear( IdeBusInterface->PciIO,
                              Regs.CommandBlock.StatusReg,
                              BSY,
                              gPlatformIdeProtocol->PoweonBusyClearTimeout ); // 10 sec

    //
    //Check Drive ready. ATAPI devices will not set DRDY bit after reset
    //
    Status = CheckDriveReady( IdeBusInterface );

    if ( EFI_ERROR( Status )) {
        Status = AtapiIdentifyCommand( IdeBusInterface,
                                    &(IdeBusInterface->IdeDevice.IdentifyData));
        IdeBusInterface->IdeDevice.DeviceType = ATAPI;
        return Status;
    }

    //
    //Detect ATA device
    //
    Status = AtaIdentifyCommand( IdeBusInterface,
                              &(IdeBusInterface->IdeDevice.IdentifyData));
    IdeBusInterface->IdeDevice.DeviceType = ATA;

    if ( Status == EFI_SUCCESS ) {
        return EFI_SUCCESS;
    }

    //
    //Detect ATAPI Device. After failing the ATA Identify command, ATAPI device if present, 
    //should have the signature EB14h
    //
    Status = EFI_NOT_FOUND;
    IdeReadByte( IdeBusInterface->PciIO,
                     Regs.CommandBlock.LBAMidReg,
                     &Data8 );

    if ( Data8 == (ATAPI_SIGNATURE & 0xff)) {
        IdeReadByte( IdeBusInterface->PciIO,
                     Regs.CommandBlock.LBAHighReg,
                     &Data8 );

        if ( Data8 == (ATAPI_SIGNATURE >> 8)) {
            IdeBusInterface->IdeDevice.DeviceType = ATAPI;
            Status = AtapiIdentifyCommand( IdeBusInterface,
                                            &(IdeBusInterface->IdeDevice.
                                            IdentifyData));
        }
    }

    if ( EFI_ERROR( Status )) {
        return EFI_NOT_FOUND;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	ControllerPresence
//
// Description:	Detects the ATA/ATAPI Controller
//
// Input:
//	IDE_BUS_PROTOCOL			*IdeBusInterface;
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: DetectIdeDevice
//
// Notes:
//  Here is the control flow of this function:
// 1. Select the drive
// 2. Read status Register
// 3. If Status_Reg = 0xff, return Not_Found
// 4. Check if Busy bit is clear, return Found
// 5. If the BUS is not floating return EFI_DEVICE_ERROR
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControllerPresence(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    UINT8   Device = IdeBusInterface->IdeDevice.Device;
    IO_REGS Regs   = IdeBusInterface->IdeDevice.Regs;
    UINT8   Data8;
    UINT8   Temp;
    UINT16  Index;

    //
    //Select the drive
    //
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.DeviceReg,
                  Device << 4 );

    //
    //Read the status Register
    //
    IdeReadByte( IdeBusInterface->PciIO, Regs.CommandBlock.StatusReg, &Data8 );

    if ( Data8 == 0xff ) {
        return EFI_NOT_FOUND;
    }

    Index = 0;

    do
    {
        //
        // Status Register is not 0xff.
        //
        Temp = Data8;

        //60 usec delay
        pBS->Stall( 60 );

        //
        //Read the status Register
        //
        IdeReadByte( IdeBusInterface->PciIO,
                     Regs.CommandBlock.StatusReg,
                     &Data8 );

        //
        //Return Success if controller present
        //
        if ( !(Data8 & 0x80)) {
            return EFI_SUCCESS;
        }

        Data8 |= Temp;
        //
        //Keep bits 7,6,3 and 0
        //    
        Data8 &= 0xc9;

        if ( Data8 == 0xc9 ) {
            //Check for Bus Floating
            //Select the drive
            Data8 = (Device & 1) ? 0xA0 : 0xB0;
            IdeWriteByte( IdeBusInterface->PciIO,
                          Regs.CommandBlock.DeviceReg,
                          Data8 );
            IdeWriteByte( IdeBusInterface->PciIO,
                          Regs.CommandBlock.SectorCountReg,
                          0xff );
            IdeReadByte( IdeBusInterface->PciIO,
                         Regs.CommandBlock.DeviceReg,
                         &Temp );
            //Decide Controller Present or Not
            return (Temp == Data8) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
        }
        Index++;
    } while ( Index < 350 );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtaReset
//
// Description:	Reset ATA device
//
// Input:
//	IN IDE_BUS_PROTOCOL			*IdeBusInterface,
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitIdeBlockIO
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaReset(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN BOOLEAN               ExtendedVerification )
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtaBlkRead
//
// Description:	Read from ATA device
// Input:
//	IN EFI_BLOCK_IO_PROTOCOL                        *This,
//	IN UINT32                                       MediaId,
//	IN EFI_LBA                                      LBA,
//	IN UINTN                                        BufferSize,
//	OUT VOID                                        *Buffer
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitIdeBlockIO, AtaReadWritePio
//
// Notes:
//	1. Check for error conditions.
//	2. Call AtaReadWritePio.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaBlkRead(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    OUT VOID                 *Buffer )
{
    UINTN              DataN;
    EFI_STATUS         Status;
    IDE_BUS_PROTOCOL   *IdeBusInterface = ((IDE_BLOCK_IO*)This)->IdeBusInterface;
    EFI_BLOCK_IO_MEDIA *BlkMedia = This->Media;
    UINT32             BlockSize = BlkMedia->BlockSize;
    UINTN              BufferAddress;

    //    
    //Check if Media ID matches
    //
    if ( BlkMedia->MediaId != MediaId ) {
        return EFI_MEDIA_CHANGED;
    }

    if ( BlkMedia->MediaPresent == FALSE ) {
        return EFI_NO_MEDIA;
    }

    if ( BufferSize == 0 ) {
        return EFI_SUCCESS;
    }

    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    (VOID *)BufferAddress = Buffer;
    if((BlkMedia->IoAlign > 1 ) && (BufferAddress % BlkMedia->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }
    
    //
    //Check whether the block size is multiple of BlkMedia->BlockSize
    //
    DataN = BufferSize % BlkMedia->BlockSize;

    if ( DataN ) {
        return EFI_BAD_BUFFER_SIZE;
    }

    //
    //Check for Valid start LBA #
    //
    if ( LBA > BlkMedia->LastBlock ) {
        return EFI_INVALID_PARAMETER;
    }

    //
    //Check for Valid End LBA #
    //
    DataN = BufferSize / BlkMedia->BlockSize;

    if ( LBA + DataN > BlkMedia->LastBlock + 1 ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( gPlatformIdeProtocol->IdeBusMasterSupport ) {
        if ( DMACapable( IdeBusInterface )) {
            Status = AtaReadWriteBusMaster( IdeBusInterface,
                                        Buffer,
                                        BufferSize,
                                        LBA,
                                        IdeBusInterface->IdeDevice.ReadCommand,
                                        0 );
            return Status;
        }
    }


    Status = AtaReadWritePio( IdeBusInterface,
                              Buffer,
                              BufferSize,
                              LBA,
                              IdeBusInterface->IdeDevice.ReadCommand,
                              0 );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtaBlkWrite
//
// Description:	Write to ATA device
// Input:
//	IN EFI_BLOCK_IO_PROTOCOL                        *This,
//	IN UINT32                                       MediaId,
//	IN EFI_LBA                                      LBA,
//	IN UINTN                                        BufferSize,
//	OUT VOID                                        *Buffer
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitIdeBlockIO, AtaReadWritePio
//
// Notes:
//	1. Check for error conditions.
//	2. Call AtaReadWritePio.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaBlkWrite(
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    IN VOID                  *Buffer )
{
    UINTN              DataN;
    EFI_STATUS         Status;
    IDE_BUS_PROTOCOL   *IdeBusInterface = ((IDE_BLOCK_IO*)This)->IdeBusInterface;
    EFI_BLOCK_IO_MEDIA *BlkMedia = This->Media;
    UINT32             BlockSize = BlkMedia->BlockSize;
    UINTN              BufferAddress;

    //
    //Check if Media ID matches
    //
    if ( BlkMedia->MediaId != MediaId ) {
        return EFI_MEDIA_CHANGED;
    }

    if ( BufferSize == 0 ) {
        return EFI_SUCCESS;
    }

    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    (VOID *)BufferAddress = Buffer;
    if((BlkMedia->IoAlign > 1 ) && (BufferAddress % BlkMedia->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }

    //
    //Check whether the block size is multiple of BlkMedia->BlockSize
    //
    DataN = BufferSize % BlkMedia->BlockSize;

    if ( DataN ) {
        return EFI_BAD_BUFFER_SIZE;
    }

    //
    //Check for Valid start LBA #
    //
    if ( LBA > BlkMedia->LastBlock ) {
        return EFI_INVALID_PARAMETER;
    }

    //
    //Check for Valid End LBA #
    //
    DataN = BufferSize / BlkMedia->BlockSize;

    if ( LBA + DataN > BlkMedia->LastBlock + 1 ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( gPlatformIdeProtocol->IdeBusMasterSupport ) {
        if ( DMACapable( IdeBusInterface )) {
            Status = AtaReadWriteBusMaster( IdeBusInterface,
                                        Buffer,
                                        BufferSize,
                                        LBA,
                                        IdeBusInterface->IdeDevice.WriteCommand,
                                        1 );
             return Status;
         }
    }

    Status = AtaReadWritePio( IdeBusInterface,
                              Buffer,
                              BufferSize,
                              LBA,
                              IdeBusInterface->IdeDevice.WriteCommand,
                              1 );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtaBlkFlush
//
// Description:	Flush the cache
// Input:
//	IN EFI_BLOCK_IO_PROTOCOL                        *This,
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: InitIdeBlockIO
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaBlkFlush(
    IN EFI_BLOCK_IO_PROTOCOL *This )
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtaReadWritePio
//
// Description:	Issues Read/Write Command and Read/Write the data from/to the ATA device
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	VOID                                                    *Buffer,
//	UINTN							ByteCount,
//	UINT64							LBA
//	IN UINT8						ReadWriteCommand,
//	IN BOOLEAN						ReadWrite		 Read/Write = 0/1
//
// Output:
//	*Buffer
//
// Modified:
//
// Referrals: AtaBlkWrite, AtaBlkRead
//
// Notes:
//	1. Check if Multiple sectors can be read/written to the ATA device.
//	2. Check for 48-bit LBA support.
//	3. Issue the command based on step 1 and step 2 results.
//	4. check for errors.
//	5. If success read/write data.
//	6. Based on step 1 results, complete the read/write sequence
//	7. If all sectors are not completed, goto step 3.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaReadWritePio(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer,
    IN UINTN            ByteCount,
    IN UINT64           LBA,
    IN UINT8            ReadWriteCommand,
    IN BOOLEAN          ReadWrite )
{
    EFI_STATUS           Status;
    INT32                WordCount;
    UINT32               SectorCount;
    UINTN                Remainder;
    UINT8                Data8;
    IDE_DEVICE_INTERFACE *IdeDevice  = &(IdeBusInterface->IdeDevice);
    UINT8                BlockSize   = 1;                         // 1 sector Default
    VOID                 *TempBuffer;
    IO_REGS              Regs        = IdeBusInterface->IdeDevice.Regs;
    INT64                LoopCount;
    INT64                MaxSectorCount;
    INT64                Total_Number_Of_Sectors;
    UINT32               EraseCommandTimeout = 0;
    UINT32               SectorSize = ATA_SECTOR_BYTES;
    BOOLEAN              SectorGTBytes = FALSE;

    //
    //Check if the device supports Multiple sector Read/Write
    //
    if  ( IdeDevice->IdentifyData.Valid_Bits_59 & 0x100 ) {
        BlockSize = (UINT8) IdeDevice->IdentifyData.Valid_Bits_59;
    }

    //
    //	Error Checking
    //
    if ( BlockSize == 0 ) {
        BlockSize = 1;
    }

    if((IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
       (!(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
       (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
        // The sector size is in words 117-118.
        SectorSize = (UINT32)(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[13] + \
                              (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[14] << 16)) * 2;
    }
    //
    //	Disable Interrupt
    //
    IdeWriteByte( IdeBusInterface->PciIO, Regs.ControlBlock.DeviceControlReg, 2 );

    if ( Check48BitCommand( ReadWriteCommand )) {
        MaxSectorCount = MAX_SECTOR_COUNT_PIO_48BIT;
    }
    else {
        MaxSectorCount = MAX_SECTOR_COUNT_PIO;
    }

    //
    //Calculate the total number of Sectors to be transferred
    //
    Total_Number_Of_Sectors = ByteCount / SectorSize;         //512
    // If the caller is requesting less bytes than one sector, we need to
    // allocate space for one sector.
    if ((ByteCount < SectorSize) && (ByteCount > 0)) {
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    SectorSize,
                                    (VOID**)&TempBuffer );
        if ( EFI_ERROR( Status )) {
            return EFI_OUT_OF_RESOURCES;
        }
        SectorGTBytes = TRUE;
        Total_Number_Of_Sectors = 1;
    } else {
        TempBuffer = Buffer;
    }

    for (;
         Total_Number_Of_Sectors > 0;
         Total_Number_Of_Sectors -= MaxSectorCount )
    {
        if ( Total_Number_Of_Sectors > MaxSectorCount ) {
            SectorCount = 0;
        } else {
            SectorCount = (UINT32) Total_Number_Of_Sectors;
        }

        Status = IssueAtaReadWriteCommand( IdeBusInterface,
                                           LBA,
                                           SectorCount,
                                           ReadWriteCommand,
                                           NULL );

        if ( EFI_ERROR( Status )) {
            return EFI_INVALID_PARAMETER;
        }

        //
        //Update LBA for next loop
        //
        if ( SectorCount ) {
            LBA       += SectorCount;                                 
            LoopCount  = (SectorCount / BlockSize);
            LoopCount += ((SectorCount % BlockSize) > 0 ? 1 : 0);
        }
        else {
            LBA       += MaxSectorCount;
            LoopCount  = Div64( MaxSectorCount, BlockSize, &Remainder );
            LoopCount += (Remainder > 0 ? 1 : 0);
        }

        //
        //For Security Erase command the time out value comes from Identify Data.
        //
        if ( ReadWriteCommand == SECURITY_ERASE_UNIT ) {
            EraseCommandTimeout = (UINT32)( IdeBusInterface->IdeDevice.IdentifyData.Time_security_Earse_89 );

            if ( EraseCommandTimeout <= 254 ) {
                EraseCommandTimeout = EraseCommandTimeout * 2 * 1000 * 60; //Value * 2Minitues
            }
            else {
                EraseCommandTimeout = 0;                                 // No Timeout Value
            }
        }

        //
        //Read Data
        //
        for (; LoopCount > 0; LoopCount -= 1 ) {
            //
            //Wait for Command completion
            //
            if ( ReadWriteCommand == SECURITY_ERASE_UNIT ) {
                Status = WaitForCmdCompletionWithTimeOutValue( IdeBusInterface,
                                                                EraseCommandTimeout );
            }
            else {
                Status = WaitForCmdCompletion( IdeBusInterface );
            }

            if ( EFI_ERROR( Status )) {
                return EFI_DEVICE_ERROR;
            }

            //
            //Check for DRQ
            //
            Status = WaitforBitSet( IdeBusInterface->PciIO,
                                    Regs.ControlBlock.AlternateStatusReg,
                                    DRQ,
                                    DRQ_TIMEOUT );

            if ( EFI_ERROR( Status )) {
                return EFI_DEVICE_ERROR;
            }

            //
            //Caluculate # of Words to be read/written
            //
            if ( SectorCount ) {
                if ( SectorCount >= BlockSize ) {
                    WordCount = (BlockSize * SectorSize) / 2;
                }
                else {
                    WordCount = (SectorCount * SectorSize) / 2;   // Partial Block will be transferred
                }
            }
            else {
                WordCount = (BlockSize * SectorSize) / 2;
            }

            if ( BlockSize == 1 ) {
                WordCount = (SectorSize) / 2;
            }

            if ( ReadWrite ) {
                Status = IdeWriteMultipleWord( IdeBusInterface->PciIO,
                                               Regs.CommandBlock.DataReg,
                                               WordCount,
                                               TempBuffer );
            } else {
                Status = IdeReadMultipleWord( IdeBusInterface->PciIO,
                                              Regs.CommandBlock.DataReg,
                                              WordCount,
                                              TempBuffer );
            }

            if ( EFI_ERROR( Status )) {
                return EFI_DEVICE_ERROR;
            }

            //
            //Check for errors.
            //
            IdeReadByte( IdeBusInterface->PciIO,
                         Regs.CommandBlock.StatusReg,
                         &Data8 );

            if ( Data8 & 0x21 ) {          // ERR OR DF bit set ?
                return EFI_DEVICE_ERROR;
            }

            ((UINT8*)TempBuffer) += (WordCount * 2);

            if ( SectorCount ) {
                SectorCount -= (WordCount * 2) / SectorSize;
            }
            else {
                SectorCount = (UINT32) ( MaxSectorCount - ((WordCount * 2) / SectorSize));
            }
        }                                                                   
    }                                                                       
    if (SectorGTBytes) {
        pBS->CopyMem( Buffer, TempBuffer, ByteCount);
        pBS->FreePool( TempBuffer );
    }

    //
    //	Check for errors
    //    
    if ( ReadWriteCommand == SECURITY_ERASE_UNIT ) {
        Status = WaitForCmdCompletionWithTimeOutValue( IdeBusInterface,
                                                       EraseCommandTimeout );
    } else {
        Status = WaitForCmdCompletion( IdeBusInterface );
    }

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtaPioDataIn
//
// Description:	Issues command which require data to be read
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	VOID                                                    *Buffer,
//	UINT32							ByteCount,
//	UINT8							SectorCount,
//	UINT8							LBALow,
//	UINT8							LBAMid,
//	UINT8							LBAHigh,
//	UINT8							Device,
//	UINT8							Command,
//	BOOLEAN							Multiple  // to determine the block size
// Output:
//	*Buffer
//
// Modified:
//
// Referrals:
//
// Notes:
//		Used to get Identify command data etc.
//	1. Issue the command
//	2. Check for errors.
//	3. Check if Data is ready. If yes, read it else return error.
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaPioDataIn(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    OUT VOID            *Buffer,
    IN UINT32           ByteCount,
    IN UINT8            Features,
    IN UINT8            SectorCount,
    IN UINT8            LBALow,
    IN UINT8            LBAMid,
    IN UINT8            LBAHigh,
    IN UINT8            Device,
    IN UINT8            Command,
    IN BOOLEAN          Multiple )
{
    IO_REGS    Regs = IdeBusInterface->IdeDevice.Regs;
    EFI_STATUS Status;
    UINT8      Data8;
    UINT32     BlockSize;
    VOID       *TempBuffer = Buffer;
    UINT32     SectorSize = ATA_SECTOR_BYTES;
    INT64       TempByteCount;


    if((IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
       (!(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
       (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
        // The sector size is in words 117-118.
        SectorSize = (UINT32)(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[13] + \
                              (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[14] << 16)) * 2;
    }

    if ( Multiple ) {
        BlockSize = SectorSize * (IdeBusInterface->IdeDevice.IdentifyData.Valid_Bits_59 & 0x0f);
    }
    else {                  
        //
        // Only one block of data to read
        //
        BlockSize = SectorSize;
    }

    if (ByteCount < SectorSize) BlockSize = ByteCount;

    // Make the byte count a signed number.
    TempByteCount = (INT64)ByteCount;

    //
    //Select the drive
    //
    IdeWriteByte(   IdeBusInterface->PciIO,
                    Regs.CommandBlock.DeviceReg,
                    Device );

    //
    //	Issue the Command
    //
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.FeatureReg,
                  Features );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.SectorCountReg,
                  SectorCount );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBALowReg,
                  LBALow );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBAMidReg,
                  LBAMid );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBAHighReg,
                  LBAHigh );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.CommandReg,
                  Command );

    for (; TempByteCount > 0; TempByteCount -= BlockSize ) {

        //
        //Wait for 400nsec before reading the status. To accomplish it, read ATL_STATUS and ignore the result
        //
        IdeReadByte( IdeBusInterface->PciIO,
                     Regs.ControlBlock.AlternateStatusReg,
                     &Data8 );

        //
        //Check for BSY bit to be clear
        //
        Status = WaitforBitClear( IdeBusInterface->PciIO,
                                  Regs.ControlBlock.AlternateStatusReg,
                                  BSY,
                                  COMMAND_COMPLETE_TIMEOUT );

        if ( EFI_ERROR( Status )) {
            return EFI_DEVICE_ERROR;
        }

        //
        //Check if DRQ is set else it is an error
        //
        IdeReadByte( IdeBusInterface->PciIO,
                     Regs.CommandBlock.StatusReg,
                     &Data8 );

        //
        // DRQ bit set ?
        //
        if ( !(Data8 & 0x08)) {       
            //
            // Handle Error condition		
            //
            return EFI_DEVICE_ERROR;
        }

        if ( Data8 & 0x21 ) {          
            return EFI_DEVICE_ERROR;
        }

        Status = IdeReadMultipleWord( IdeBusInterface->PciIO,
                                      Regs.CommandBlock.DataReg,
                                      BlockSize / 2,
                                      TempBuffer );
        //
        //		Wait for DRQ to go low
        //
        WaitforBitClear( IdeBusInterface->PciIO,
                         Regs.CommandBlock.StatusReg,
                         DRQ,
                         DRQ_CLEAR_TIMEOUT );

        if ( EFI_ERROR( Status )) {
            return EFI_DEVICE_ERROR;
        }
        ((UINT8*)TempBuffer) += BlockSize;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtaPioDataOut
//
// Description:	Issues Read/Write Command and Read/Write the data from/to the ATA device
//               with SubCommand Support.
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	VOID                            *Buffer,
//	UINTN							ByteCount,
//  UINT8                           Features,
//	UINT32							SectorCountIn,
//	UINT8							LBALow,
//	UINT8							LBALowExp,
//	UINT8							LBAMid,
//	UINT8							LBAMidExp,
//	UINT8							LBAHigh,
//	UINT8							LBAHighExp,
//	UINT8							Device,
//	UINT8							Command,
//	BOOLEAN						    ReadWrite, // Read/Write = 0/1
//	BOOLEAN							Multiple   // to determine the block size
// Output:
//	*Buffer
//
// Modified:
//
// Referrals:
//
// Notes:
//	1. Check if Multiple sectors can be read/written to the ATA device.
//	2. Check for 48-bit LBA support.
//	3. Issue the command based on step 1 and step 2 results.
//	4. check for errors.
//	5. If success read/write data.
//	6. Based on step 1 results, complete the read/write sequence
//	7. If all sectors are not completed, goto step 3.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AtaPioDataOut(
         IN IDE_BUS_PROTOCOL *IdeBusInterface,
         IN OUT VOID         *Buffer,
         IN UINTN            ByteCount,
         IN UINT8            Features,
         IN UINT32           SectorCountIn,
         IN UINT8            LBALow,
         IN UINT8            LBALowExp,
         IN UINT8            LBAMid,
         IN UINT8            LBAMidExp,
         IN UINT8            LBAHigh,
         IN UINT8            LBAHighExp,
         IN UINT8            Device,
         IN UINT8            Command,
         IN BOOLEAN          ReadWrite,
         IN BOOLEAN          Multiple )
{
    EFI_STATUS           Status;
    INT32                WordCount;
    UINT32               SectorCount;
    UINTN                Remainder;
    UINT8                Data8;
    IDE_DEVICE_INTERFACE *IdeDevice  = &(IdeBusInterface->IdeDevice);
    UINT8                BlockSize   = 1;                         // 1 sector Default
    VOID                 *TempBuffer;
    IO_REGS              Regs        = IdeBusInterface->IdeDevice.Regs;
    INT64                LoopCount;
    INT64                MaxSectorCount;
    INT64                Total_Number_Of_Sectors;
    UINT32               EraseCommandTimeout = 0;
    UINT32               SectorSize = ATA_SECTOR_BYTES;
    BOOLEAN              SectorGTBytes = FALSE;
    UINT64               LBA = 0;
    UINT64               LBAHighDword = 0;
    INT64                i;

    //
    // Check if the device supports Multiple sector Read/Write
    //    
    if  ( IdeDevice->IdentifyData.Valid_Bits_59 & 0x100 ) {
        BlockSize = (UINT8) IdeDevice->IdentifyData.Valid_Bits_59;
    }

    //
    // Error Checking
    //
    if ( BlockSize == 0 ) {
       BlockSize = 1;
    }

    if((IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
       (!(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
       (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
        // The sector size is in words 117-118.
        SectorSize = (UINT32)(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[13] + \
                              (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[14] << 16)) * 2;
    }
    //
    //	Disable Interrupt
    //
    IdeWriteByte( IdeBusInterface->PciIO, Regs.ControlBlock.DeviceControlReg, 2 );

    if ( Check48BitCommand( Command )) {
        MaxSectorCount = MAX_SECTOR_COUNT_PIO_48BIT;
        //
        //	if 48 Bit LBA form Upper Dword
        //
        LBAHighDword |= LBAHighExp;
        LBAHighDword = ( Shl64(( Shl64( LBAHighDword, 8)| LBAMidExp), 8)| LBALowExp);
    }
    else {
        MaxSectorCount = MAX_SECTOR_COUNT_PIO;
    }
    //
    //	Complete LBA	 
    //
    LBA |= LBAHigh;
    LBA = (( Shl64(( Shl64( LBA, 8) | LBAMid ), 8)| LBALow)| Shl64( LBAHighDword, 24 ));

    //
    //Calculate the total number of Sectors to be transferred
    //
    Total_Number_Of_Sectors = ByteCount / SectorSize;         //512
    // If the caller is requesting less bytes than one sector, we need to
    // allocate space for one sector.
    if (!ReadWrite && ((ByteCount < SectorSize) && (ByteCount > 0))) {
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    SectorSize,
                                    (VOID**)&TempBuffer );
        if ( EFI_ERROR( Status )) {
            return EFI_OUT_OF_RESOURCES;
        }
        SectorGTBytes = TRUE;
        Total_Number_Of_Sectors = 1;
    } else {
        TempBuffer = Buffer;
    }

    for (;
         Total_Number_Of_Sectors > 0;
         Total_Number_Of_Sectors -= MaxSectorCount )
    {
        if ( Total_Number_Of_Sectors > MaxSectorCount ) {
            SectorCount = 0;
        } else {
            SectorCount = (UINT32) Total_Number_Of_Sectors;
        }

        Status = IssueAtaReadWriteCommand( IdeBusInterface,
                                           LBA,
                                           SectorCount,
                                           Command,
                                           Features );

        if ( EFI_ERROR( Status )) {
            return EFI_INVALID_PARAMETER;
        }

        //
        //Update LBA for next loop
        //
        if ( SectorCount ) {
            LBA       += SectorCount;
            LoopCount  = (SectorCount / BlockSize);
            LoopCount += ((SectorCount % BlockSize) > 0 ? 1 : 0);
        }
        else {
            LBA       += MaxSectorCount;
            LoopCount  = Div64( MaxSectorCount, BlockSize, &Remainder );
            LoopCount += (Remainder > 0 ? 1 : 0);
        }

        //
        //Read Data
        //
        for (; LoopCount > 0; LoopCount -= 1 ) {
            //
            //Wait for Command completion
            //
            Status = WaitForCmdCompletion( IdeBusInterface );

            if ( EFI_ERROR( Status )) {
                return EFI_DEVICE_ERROR;
            }
            //
            //Check for DRQ
            //
            Status = WaitforBitSet( IdeBusInterface->PciIO,
                                    Regs.ControlBlock.AlternateStatusReg,
                                    DRQ,
                                    DRQ_TIMEOUT );

            if ( EFI_ERROR( Status )) {
                return EFI_DEVICE_ERROR;
            }

            //
            //Calculate # of Words to be read/written
            //

            WordCount = SectorSize / 2;

            if ( ReadWrite ) {

                for ( i=0 ; i<Total_Number_Of_Sectors ;i++ ) {
            
                    Status = IdeWriteMultipleWord( IdeBusInterface->PciIO,
                                                   Regs.CommandBlock.DataReg,
                                                   WordCount,
                                                   TempBuffer );
                    ((UINT8*)TempBuffer) += SectorSize;
                    pBS->Stall(100);   //10ms Delay after 1 sector write
                }

            } else {
     
                for ( i=0 ; i<Total_Number_Of_Sectors ;i++ ) {

                    Status = IdeReadMultipleWord( IdeBusInterface->PciIO,
                                                  Regs.CommandBlock.DataReg,
                                                  WordCount,
                                                  TempBuffer );
                    (UINT8 *)TempBuffer += SectorSize;
                    pBS->Stall(100);   //10ms Delay after 1 sector read

                }
               ((UINT8*)TempBuffer) -= Mul64( Total_Number_Of_Sectors, SectorSize);
            }

            if ( EFI_ERROR( Status )) {
                return EFI_DEVICE_ERROR;
            }

            //
            //Check for errors.
            //
            IdeReadByte( IdeBusInterface->PciIO,
                         Regs.CommandBlock.StatusReg,
                         &Data8 );

            if ( Data8 & 0x21 ) {          // ERR OR DF bit set ?
                return EFI_DEVICE_ERROR;
            }

//            ((UINT8*)TempBuffer) += (WordCount * 2);

            if ( SectorCount ) {
                SectorCount -= (WordCount * 2) / SectorSize;
            }
            else {
                SectorCount = (UINT32) ( MaxSectorCount - ((WordCount * 2) / SectorSize));
            }
        }
    }
    if (SectorGTBytes) {
        pBS->CopyMem( Buffer, TempBuffer, ByteCount);
        pBS->FreePool( TempBuffer );
    }

    //
    //	Check for errors
    //    
    Status = WaitForCmdCompletion( IdeBusInterface );

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IssueAtaReadWriteCommand
//
// Description:	Issues ATA Read/Write Command
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	UINT64							LBA,
//	INT32							SectorCount,
//	UINT8							Command
//  UINT8                           Features         OPTIONAL   
//
// Output:
//				EFI_STATUS
// Modified:
//
// Referrals: AtaReadWritePio
//
// Notes:
//	1. Select the drive.
//	2. check if BSY and DRQ bits are zero.
//	3. Issue the command.
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IssueAtaReadWriteCommand(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN UINT64           LBA,
    IN INT32            SectorCount,
    IN UINT8            Command,
    IN UINT8            Features )
{
    EFI_STATUS           Status;
    IDE_DEVICE_INTERFACE *IdeDevice = &(IdeBusInterface->IdeDevice);
    IO_REGS              Regs       = IdeBusInterface->IdeDevice.Regs;
    UINT8                Device     = (IdeDevice->Device << 4);

    //
    // Select the drive
    //    
    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.DeviceReg, Device );

    //
    //Before Writing to Sector Count Reg, BSY and DRQ bit should be zero
    //
    Status = WaitforBitClear( IdeBusInterface->PciIO,
                              Regs.ControlBlock.AlternateStatusReg,
                              BSY | DRQ,
                              DRQ_TIMEOUT );

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Check for DRDY
    //
    Status = WaitforBitSet( IdeBusInterface->PciIO,
                            Regs.ControlBlock.AlternateStatusReg,
                            DRDY,
                            DRDY_TIMEOUT );

    if ( EFI_ERROR( Status )) {
        return EFI_TIMEOUT;
    }

    if ( Check48BitCommand( Command )) {
        //		48 Bit LBA
        //		Write the Upper LBA DWORD and Upper byte of Sector Count
        IdeWriteByte(   IdeBusInterface->PciIO,
                         Regs.CommandBlock.SectorCountReg,
                         (UINT8)( SectorCount >> 8 ));

        IdeWriteByte(   IdeBusInterface->PciIO,
                        Regs.CommandBlock.LBALowReg,
                        (UINT8)Shr64( LBA, 24 ));

        IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.LBAMidReg,
                      (UINT8) Shr64( LBA, 32 ));

        IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.LBAHighReg,
                      (UINT8) Shr64( LBA, 40 ));

        Device = (IdeDevice->Device << 4) | 0x40;       // 48Bit LBA
    }
    else {                                              // 28 Bit LBA
        Device = ((UINT8) ((UINT32) LBA >> 24 ) & 0x0f) | (IdeDevice->Device << 4) | 0x40;
    }

    //
    //Select the drive
    //
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.DeviceReg,
                  Device );

    //
    //Issue command
    //
    if ( Features ) {
        IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.FeatureReg,  //SubCommand
                      Features );
    }
    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.SectorCountReg,
                  (UINT8) SectorCount );

    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.LBALowReg,
                  (UINT8)LBA );

    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.LBAMidReg,
                  (UINT8) (((UINT32)LBA >> 8) & 0xff ));

    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.LBAHighReg,
                  (UINT8) (((UINT32)LBA >> 16) & 0xff ));

    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.CommandReg,
                  Command );

    //
    //Wait for 400nsec for status to be available
    //
    pBS->Stall( 1 );
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeNonDataCommand
//
// Description:	Issues command where no data transfer takes place
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	VOID                                                    *Buffer,
//	UINT32							ByteCount,
//	UINT8							SectorCount,
//	UINT8							LBALow,
//	UINT8							LBAMid,
//	UINT8							LBAHigh,
//	UINT8							Device,
//	UINT8							Command,
// Output:
//	*Buffer
//
// Modified:
//
// Referrals: IdeSetFeatureCommand
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeNonDataCommand(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN UINT8            Features,
    IN UINT8            SectorCount,
    IN UINT8            LBALow,
    IN UINT8            LBAMid,
    IN UINT8            LBAHigh,
    IN UINT8            Device,
    IN UINT8            Command )
{
    IO_REGS    Regs = IdeBusInterface->IdeDevice.Regs;
    EFI_STATUS Status;
    UINT8      Data8;

    //
    //Select the drive
    //
    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.DeviceReg, Device );

    //
    //Wiat for DRDY to be set
    //
    Status = WaitforBitSet( IdeBusInterface->PciIO,
                            Regs.ControlBlock.AlternateStatusReg,
                            DRDY,
                            DRDY_TIMEOUT );

    if ( EFI_ERROR( Status )) {
        return EFI_TIMEOUT;
    }

    //
    //Issue the Command
    //
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.FeatureReg,
                  Features );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.SectorCountReg,
                  SectorCount );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBALowReg,
                  LBALow );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBAMidReg,
                  LBAMid );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBAHighReg,
                  LBAHigh );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.CommandReg,
                  Command );

    //
    //Wait for 400nsec before reading the status. To accomplish it, read ATL_STATUS and ignore the result
    //
    IdeReadByte( IdeBusInterface->PciIO,
                 Regs.ControlBlock.AlternateStatusReg,
                 &Data8 );

    //
    //Check for BSY bit to be clear
    //
    Status = WaitforBitClear( IdeBusInterface->PciIO,
                              Regs.ControlBlock.AlternateStatusReg,
                              BSY | DRQ,
                              gPlatformIdeProtocol->PoweonBusyClearTimeout );

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Check for any errors
    //
    IdeReadByte( IdeBusInterface->PciIO, Regs.CommandBlock.StatusReg, &Data8 );

    if ( Data8 & (DF | ERR)) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeNonDataCommandExp
//
// Description:	Issues command where no data transfer takes place
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	VOID                                                    *Buffer,
//	UINT32							ByteCount,
//	UINT8							SectorCount,
//	UINT8							SectorCountExp,
//	UINT8							LBALow,
//	UINT8							LBALowExp,
//	UINT8							LBAMid,
//	UINT8							LBAMidExp,
//	UINT8							LBAHigh,
//	UINT8							LBAHighExp,
//	UINT8							Device,
//	UINT8							Command,
// Output:
//	*Buffer
//
// Modified:
//
// Referrals: IdeSetFeatureCommand
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeNonDataCommandExp(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN UINT8            Features,
    IN UINT8            SectorCount,
    IN UINT8            SectorCountExp,
    IN UINT8            LBALow,
    IN UINT8            LBALowExp,
    IN UINT8            LBAMid,
    IN UINT8            LBAMidExp,
    IN UINT8            LBAHigh,
    IN UINT8            LBAHighExp,
    IN UINT8            Device,
    IN UINT8            Command )
{
    IO_REGS    Regs = IdeBusInterface->IdeDevice.Regs;
    EFI_STATUS Status;
    UINT8      Data8;

    //
    //Select the drive
    //
    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.DeviceReg, Device );

    //
    //Wiat for DRDY to be set
    //
    Status = WaitforBitSet( IdeBusInterface->PciIO,
                            Regs.ControlBlock.AlternateStatusReg,
                            DRDY,
                            DRDY_TIMEOUT );

    if ( EFI_ERROR( Status )) {
        return EFI_TIMEOUT;
    }

    //		48 Bit LBA
    //		Write the Upper LBA DWORD and Upper byte of Sector Count
    IdeWriteByte(   IdeBusInterface->PciIO,
                    Regs.CommandBlock.SectorCountReg,
                    SectorCountExp);

    IdeWriteByte(   IdeBusInterface->PciIO,
                    Regs.CommandBlock.LBALowReg,
                    LBALowExp);

    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.LBAMidReg,
                  LBAMidExp);

    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.LBAHighReg,
                  LBAHighExp);

    //
    //Issue the Command
    //
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.FeatureReg,
                  Features );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.SectorCountReg,
                  SectorCount );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBALowReg,
                  LBALow );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBAMidReg,
                  LBAMid );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.LBAHighReg,
                  LBAHigh );
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.CommandReg,
                  Command );

    //
    //Wait for 400nsec before reading the status. To accomplish it, read ATL_STATUS and ignore the result
    //
    IdeReadByte( IdeBusInterface->PciIO,
                 Regs.ControlBlock.AlternateStatusReg,
                 &Data8 );

    //
    //Check for BSY bit to be clear
    //
    Status = WaitforBitClear( IdeBusInterface->PciIO,
                              Regs.ControlBlock.AlternateStatusReg,
                              BSY | DRQ,
                              gPlatformIdeProtocol->PoweonBusyClearTimeout );

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Check for any errors
    //
    IdeReadByte( IdeBusInterface->PciIO, Regs.CommandBlock.StatusReg, &Data8 );

    if ( Data8 & (DF | ERR)) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtaIdentifyCommand
//
// Description:	Issues IDENTIFY DATA command (0xEC)
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	IN OUT VOID						*Buffer
//
// Output:
//	*Buffer
//
// Modified:
//
// Referrals: AtaPioDataIn
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaIdentifyCommand(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer )
{
    EFI_STATUS Status = AtaPioDataIn(
        IdeBusInterface,
        Buffer,
        512,
        0,
        0,
        0,
        0,
        0,
        IdeBusInterface->IdeDevice.Device << 4,
        IDENTIFY_COMMAND,
        FALSE );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	AtapiIdentifyCommand
//
// Description:	Issues IDENTIFY PACKET DATA command (0xA1)
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	IN OUT VOID						*Buffer
//
// Output:
//	*Buffer
//
// Modified:
//
// Referrals: AtaPioDataIn
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtapiIdentifyCommand(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer )
{
    return AtaPioDataIn(
               IdeBusInterface,
               Buffer,
               512,                // Byte Count
               0,
               0,
               0,
               0,
               0,
               IdeBusInterface->IdeDevice.Device << 4,
               IDENTIFY_PACKET_COMMAND,
               FALSE );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	GetIdentifyData
//
// Description:	Gets Identify command data.
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:	ATA/ATAPI device type should have beeen known already.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetIdentifyData(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer )
{
    //
    //check whether it is a ATA or ATAPI device
    //
    if ( IdeBusInterface->IdeDevice.DeviceType == ATAPI ) {
        return AtaPioDataIn(
                   IdeBusInterface,
                   Buffer,
                   512,                // Byte Count
                   0,
                   0,
                   0,
                   0,
                   0,
                   IdeBusInterface->IdeDevice.Device << 4,
                   IDENTIFY_PACKET_COMMAND,
                   FALSE );
    }
    else {
        EFI_STATUS Status = AtaPioDataIn(
            IdeBusInterface,
            Buffer,
            512,
            0,
            0,
            0,
            0,
            0,
            IdeBusInterface->IdeDevice.Device << 4,
            IDENTIFY_COMMAND,
            FALSE );

        return Status;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeSetFeatureCommand
//
// Description:	Issue a ATA Non-Data Command
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals: IdeNonDataCommand
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeSetFeatureCommand(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8               SubCommand,
    UINT8               Mode )
{
    return IdeNonDataCommand(
               IdeBusInterface,
               SubCommand,
               Mode,
               0,
               0,
               0,
               IdeBusInterface->IdeDevice.Device << 4,
               SET_FEATURE_COMMAND );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeSoftReset
//
// Description:	Issue a Soft Reset
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals: DetectIdeDevice
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeSoftReset(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    UINT8   Device = IdeBusInterface->IdeDevice.Device;
    IO_REGS Regs   = IdeBusInterface->IdeDevice.Regs;
    UINT8   Data8;

    PROGRESS_CODE( DXE_IDE_RESET );

    //
    //Select the drive. Not needed.
    //
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.DeviceReg,
                  Device << 4 );

    //
    //Read the status Register
    //
    IdeReadByte( IdeBusInterface->PciIO, Regs.CommandBlock.StatusReg, &Data8 );

    //
    //If BSY bit set, don't issue Soft reset
    //
    if ( Data8 & 0x80 ) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Assert SRST, disable nIEN
    //
    Data8 = SRST | nIEN;
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.ControlBlock.DeviceControlReg,
                  Data8 );
    pBS->Stall( 100 );               // 100 usec

    //
    //Deassert SRST
    //
    Data8 = nIEN;
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.ControlBlock.DeviceControlReg,
                  Data8 );
    pBS->Stall( 10000 );             // 10 msec

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	WaitForCmdCompletionWithTimeOutValue
//
// Description:	Waits for BSY bit to get clear
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface
//  IN UINT32						TimeOutValue
//
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals: AtaReadWritePio
//
// Notes:	Wait for BSY bit to get clear. Check for any errors.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WaitForCmdCompletionWithTimeOutValue(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN UINT32           TimeOutvalue )
{
    UINT8      Data8;
    EFI_STATUS Status;
    IO_REGS    Regs = IdeBusInterface->IdeDevice.Regs;

    //	Read ATL_STATUS and ignore the result. Just a delay
    IdeReadByte( IdeBusInterface->PciIO,
                 Regs.ControlBlock.AlternateStatusReg,
                 &Data8 );

    // if the Timeout Value is 0, check Busy bit to clear without Timeout Value.
    // Otherwise Use the Timeout value to check the Busy bit to clear.
    if ( TimeOutvalue == 0 ) {
        //
        //Check for BSY bit to be clear without Timout value
        //
        Status = WaitforBitClearWithoutTimeout(
                                IdeBusInterface->PciIO,
                                Regs.ControlBlock.
                                AlternateStatusReg,
                                BSY );
    }
    else {
        //
        //Check for BSY bit to be clear
        //
        Status = WaitforBitClear( IdeBusInterface->PciIO,
                                  Regs.ControlBlock.AlternateStatusReg,
                                  BSY,
                                  TimeOutvalue );
    }

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    //Check for errors.
    IdeReadByte( IdeBusInterface->PciIO,
                 Regs.CommandBlock.StatusReg,
                 &Data8 );

    if ( Data8 & (ERR | DF)) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	WaitForCmdCompletion
//
// Description:	Waits for BSY bit to get clear
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface
//
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals: AtaReadWritePio
//
// Notes:	Wait for BSY bit to get clear. Check for any errors.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WaitForCmdCompletion(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    UINT8      Data8;
    EFI_STATUS Status;
    IO_REGS    Regs = IdeBusInterface->IdeDevice.Regs;

    //
    //Read ATL_STATUS and ignore the result. Just a delay
    //
    IdeReadByte( IdeBusInterface->PciIO,
                 Regs.ControlBlock.AlternateStatusReg,
                 &Data8 );

    //
    //Check for BSY bit to be clear
    //
    Status = WaitforBitClear( IdeBusInterface->PciIO,
                              Regs.ControlBlock.AlternateStatusReg,
                              BSY,
                              COMMAND_COMPLETE_TIMEOUT );

    if ( EFI_ERROR( Status )) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Check for errors.
    //
    IdeReadByte( IdeBusInterface->PciIO, Regs.CommandBlock.StatusReg, &Data8 );

    if ( Data8 & (ERR | DF)) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	DisableIdeInterrupt
//
// Description:	Disabled Interrupt generation feature
//
// Input:
//	IDE_BUS_PROTOCOL			*IdeBusInterface;
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void DisableIdeInterrupt(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    IO_REGS Regs = IdeBusInterface->IdeDevice.Regs;
    UINT8   Data8, Flags;

    //
    // Disable IEN
    //
    IdeWriteByte( IdeBusInterface->PciIO, Regs.ControlBlock.DeviceControlReg, 2 );

    //
    //Clear interrupt status
    //
    IdeReadByte( IdeBusInterface->PciIO,
                 Regs.BusMasterBlock.BMStatusRegister,
                 &Data8 );
    Flags = Data8;
    //
    // Preserve DMA capabilities and set Interrupt bit
    //
    Data8 = (Data8 & 0x60);                      

    if ( Flags & BM_INTERRUPT ) {
        Data8 |= BM_INTERRUPT;
    }
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.BusMasterBlock.BMStatusRegister,
                  Data8 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	CheckDriveReady
//
// Description:	Check if BSY is cleared and DRDY set
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckDriveReady(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    IO_REGS Regs = IdeBusInterface->IdeDevice.Regs;
    UINT8   Data8;

    //
    //Select the drive
    //
    IdeWriteByte( IdeBusInterface->PciIO,
                  Regs.CommandBlock.DeviceReg,
                  IdeBusInterface->IdeDevice.Device << 4 );

    //
    //Read Alt Status
    //
    IdeReadByte( IdeBusInterface->PciIO,
                 Regs.ControlBlock.DeviceControlReg,
                 &Data8 );

    if ((Data8 & 0xc0) == 0x40 ) {
        return EFI_SUCCESS;
    }

    return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	WaitforBitSet
//
// Description:	Checks for a particular Bit to be set for a given amount of time
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	UINT16							AlternateStatusReg,
//	UINT8							BitSet,
//	UINT32							TimeOut
//
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WaitforBitSet(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    UINT16                 AlternateStatusReg,
    UINT8                  BitSet,
    UINT32                 TimeOut )
{
    UINT8 Delay;
    UINT8 Data8;

    for (; TimeOut > 0; TimeOut-- )
    {
        for ( Delay = 100; Delay > 0; Delay-- )
        {
            IdeReadByte( PciIO, AlternateStatusReg, &Data8 );

            if ( Data8 & BitSet ) {
                return EFI_SUCCESS;
            }
            pBS->Stall( 10 );        // 10usec
        }
    }
    return EFI_TIMEOUT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	WaitforBitClear
//
// Description:	Waits for the given bit to be clear
//
// Input:
//	UINT16		AlternateStatus,
//	UINT8		BitClear
//	UINT32		BUSY_CLEAR_TIMEOUT		// Millisecond
//
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WaitforBitClear(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    UINT16                 AlternateStatus,
    UINT8                  BitClear,
    UINT32                 Timeout )
{
    UINT8 Delay;
    UINT8 Data8;

    for (; Timeout > 0; Timeout-- )
    {
        for ( Delay = 100; Delay > 0; Delay-- )
        {
            IdeReadByte( PciIO, AlternateStatus, &Data8 );

            if ( !(Data8 & BitClear)) {
                return EFI_SUCCESS;
            }
            pBS->Stall( 10 );                // 10 Usec
        }
    }
    return EFI_TIMEOUT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	WaitforBitClearWithoutTimeout
//
// Description:	Waits for the given bit to be clear
//
// Input:
//	UINT16		AlternateStatus,
//	UINT8		BitClear
//
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WaitforBitClearWithoutTimeout(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    UINT16                 AlternateStatus,
    UINT8                  BitClear )
{
    UINT8 Data8;

    do
    {
        IdeReadByte( PciIO, AlternateStatus, &Data8 );

        if ( !(Data8 & BitClear)) {
            return EFI_SUCCESS;
        }
        pBS->Stall( 10 );                // 10 Usec
    } while ( 1 );

    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	ReturnMSBset
//
// Description:	Returns the MOST significant Bit set.
//
// Input:
//	UINT32		Data
//
// Output:
//		UINT8
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 ReturnMSBset(
    UINT32 Data )
{
    UINT8 Index;
    UINT8 Value = 0xFF; 

    for ( Index = 0; Index < 32; Index++ )
    {
        if ( Data & 1 ) {
            Value = Index;
        }
        Data >>= 1;
    }

    return Value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeReadByte
//
// Description:	Reads 1 Byte of data from the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	OUT UINT8						*Data8
//
// Output:
//	OUT UINT8						*Data8
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeReadByte(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    OUT UINT8              *Data8 )
{
    PciIO->Io.         Read(
        PciIO,
        EfiPciIoWidthFifoUint8,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        1,
        Data8 );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeReadMultipleByte
//
// Description:	Reads N Bytes of data from the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	IN UINT64						Count
//	OUT UINT8						*Data8
//
// Output:
//	OUT UINT8						*Data8
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeReadMultipleByte(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Count,
    OUT UINT8              *Data8 )
{
    EFI_STATUS Status;

    Status = PciIO->Io.Read(
        PciIO,
        EfiPciIoWidthFifoUint8,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        Count,
        Data8 );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeReadWord
//
// Description:	Reads 1 Word of data from the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	OUT UINT16						*Data16
//
// Output:
//	OUT UINT16						*Data16
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeReadWord(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    OUT UINT16             *Data16 )
{
    EFI_STATUS Status;

    Status = PciIO->Io.Read(
        PciIO,
        EfiPciIoWidthFifoUint16,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        1,
        Data16 );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeReadMultipleWord
//
// Description:	Reads N Word of data from the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	IN UINT32						Count   (Count in WORDS)
//	OUT UINT8						*Data16
//
// Output:
//	OUT UINT16						*Data16
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeReadMultipleWord(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Count,
    OUT UINT16             *Data16 )
{
    EFI_STATUS Status;
    UINT16     *Buffer         = Data16;
    BOOLEAN    MemoryAllocated = FALSE;

    //
    //Allocate memory only if ADDRESS is not WORD aligned
    //
    if ((UINTN)Data16 & 1 ) {
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    Count * sizeof(UINT16),
                                    (VOID**)&Buffer );           

        if ( EFI_ERROR( Status )) {
            return EFI_OUT_OF_RESOURCES;
        }
        MemoryAllocated = TRUE;
    }

    Status = PciIO->Io.Read(
        PciIO,
        EfiPciIoWidthFifoUint16,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        Count,
        Buffer );

    if ( MemoryAllocated ) {
        pBS->CopyMem( Data16, Buffer, Count * sizeof(UINT16));
        pBS->FreePool( Buffer );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeWriteByte
//
// Description:	Writes 1 Byte of data to the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	OUT UINT8						Data8
//
// Output:
//	OUT UINT8						*Data8
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeWriteByte(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT8               Data8 )
{
    PciIO->Io.Write(
        PciIO,
        EfiPciIoWidthFifoUint8,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        1,
        &Data8 );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeWriteMultipleByte
//
// Description:	Writes N Bytes of data to the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	IN UINT32						Count  (Count in BYTES)
//	IN UINT8						*Data8
//
// Output:
// EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeWriteMultipleByte(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Count,
    IN UINT8               *Data8 )
{
    EFI_STATUS Status;

    Status = PciIO->Io.Write(
        PciIO,
        EfiPciIoWidthFifoUint8,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        Count,
        Data8 );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeWriteWord
//
// Description:	Writes 1 word of data to the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	OUT UINT16						*Data16
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeWriteWord(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT16              Data16 )
{
    PciIO->Io.Write(
        PciIO,
        EfiPciIoWidthFifoUint16,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        1,
        &Data16 );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeWriteMultipleWord
//
// Description:	Writes N Words of data to the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	IN UINT64						Count (Count in WORDS)
//	IN UINT16						*Data16
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
// Count : # of WORDs to write
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeWriteMultipleWord(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Count,
    IN UINT16              *Data16 )
{
    EFI_STATUS Status;
    UINT16     *Buffer         = Data16;
    BOOLEAN    MemoryAllocated = FALSE;

    //
    //	Allocate memory only if ADDRESS is not WORD aligned
    //
    if ((UINTN)Data16 & 1 ) {
        Status = pBS->AllocatePool( EfiBootServicesData,
                                    Count * sizeof(UINT16),
                                    (VOID**)&Buffer );           

        if ( EFI_ERROR( Status )) {
            return EFI_OUT_OF_RESOURCES;
        }
        MemoryAllocated = TRUE;

        pBS->CopyMem( Buffer, Data16, Count * sizeof(UINT16));
    }

    Status = PciIO->Io.Write(
        PciIO,
        EfiPciIoWidthFifoUint16,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        Count,
        Buffer );

    if ( MemoryAllocated ) {
        pBS->FreePool( Buffer );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	IdeWriteDword
//
// Description:	Writes 1 Dword of data to the IO port
//
// Input:
//	IN EFI_PCI_IO_PROTOCOL			*PciIO,
//	IN UINT16						Register,
//	OUT UINT16						*Data16
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeWriteDword(
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Data32 )
{
    PciIO->Io.Write(
        PciIO,
        EfiPciIoWidthFifoUint32,
        EFI_PCI_IO_PASS_THROUGH_BAR,
        Register,
        1,
        &Data32 );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:	Check48BitCommand
//
// Description:	Checks if the command is for 48-bit LBA
//
// Input:
//	IN UINT8			Command
//
// Output:
//		TRUE/FLASE
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN Check48BitCommand(
    IN UINT8 Command )
{
    if ( Command == READ_SECTORS_EXT
         || Command == READ_MULTIPLE_EXT
         || Command == WRITE_SECTORS_EXT
         || Command == WRITE_MULTIPLE_EXT
         || Command == READ_DMA_EXT
         || Command == WRITE_DMA_EXT ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
