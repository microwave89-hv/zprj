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
// $Header: /Alaska/SOURCE/Core/Modules/IdeBus/IdeBusMaster.c 11    9/27/11 3:16a Rajeshms $
//
// $Revision: 11 $
//
// $Date: 9/27/11 3:16a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/IdeBus/IdeBusMaster.c $
// 
// 11    9/27/11 3:16a Rajeshms
// [TAG]  		EIP69295
// [Category]  	Improvement
// [Description]  	The Timeout values used by IDE and AHCI drivers are
// made as SDL tokens, so that the timeout values can be varied.
// [Files]  		IdeBusBoard.c, CORE_DXE.sdl, AhciSmm.h, AhciBus.h, IDESMM.h,
// Ata.c, Atapi.c, IdeBus.c, IdeBus.h, IdeBusMaster.c, IdeBusBoard.h
// 
// 10    12/23/10 3:56a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 9     10/11/10 11:30a Krishnakumarg
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
// 8     8/25/10 4:13a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
// IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
// IdeHpa.c, IdePowerManagement.c
// 
// 7     4/16/10 4:05p Pats
// EIP 30719: Support for the HDD with sector size more than 512bytes.
// 
// 6     7/01/09 12:23p Rameshr
// Coding Standard and File header updated.
//
// 5     1/08/09 4:55p Rameshraju
// Symptom: When we have HDD and CD-ROM connected, system hangs while
// booting through Cd-ROM
// RootCause: Interrupt is not cleared properly on Bus master Atapi
// read/write, that cause further interrupts not to be generated.
// Solution: Clear the Bus master interrupt status if set
//
// 4     9/30/08 4:43p Felixp
// Bug fix(EIP 15310):Invalid error code (EFI_DEVICE_ERROR instead of
// EFI_NO_MEDIA) was returned for removable devices with no media
//
// 2     13/04/07 3:02p Anandakrishnanl
// Ide Bus Module - Update source files to comply with AMI coding
// standard"!!!
//
// 1     12/01/05 9:43a Felixp
//
// 8     11/03/05 10:53a Srinin
// VC7 compilation error fixed. 64KB buffer alignment removed for
// Busmaster.
// It should be Dword aligned.
//
// 7     9/27/05 4:38p Olegi
// Change in AtaReadWriteBusMaster routine - clear interrupt status after
// every read/write.
//
// 6     3/04/05 11:34a Mandal
//
// 5     2/11/05 6:17p Felixp
// Bug fix: data corruption during DMA write operation
//
// 4     2/10/05 6:15p Felixp
// Bug fix (in case of transfer of 64K*N bytes, the last 64K block was
// lost)
//
// 3     1/28/05 12:10p Srinin
// Before Setting up Busmater registers select the device.
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     1/05/05 11:21a Srinin
// IDE BusMaster Support added.
//
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: IDEBusMaster.c
//
// Description:	BusMaster Services
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "IdeBus.h"
#include <Protocol\IdeBusBoard.h>

extern PLATFORM_IDE_PROTOCOL    *gPlatformIdeProtocol;
extern VOID *gDescriptorBuffer;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	AtaReadWriteBusMaster
//
// Description:	Issues Read/Write Command and Read/Write the data from/to the ATA device
//				using BusMaster
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	VOID                                                    *Buffer,
//	UINT32							ByteCount,
//	UINT64							LBA
//
// Output:
//	*Buffer
//
// Modified:
//
// Referrals: AtaBlkWrite, AtaBlkRead
//
// Notes:
//		1. Create Descriptor Table
//		2. Issue ATA Read/Write command. Enable BusMastering
//		3. Wait for Data Transfer
//		4. Check for errors
//		5. If success, check if any more data need to transferred, if yes, goto step 1
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaReadWriteBusMaster(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer,
    IN UINTN            ByteCount,
    IN UINT64           LBA,
    IN UINT8            ReadWriteCommand,
    IN BOOLEAN          READWRITE )
{
    EFI_STATUS Status;
    EFI_STATUS DMAStatus;
    UINTN      RemaingByteCount;
    UINTN      Total_Number_Of_Sectors;
    UINTN      MaxSectorCount;
    UINTN      CurrentSectorCount;
    UINTN      CurrentByteCount;
    UINT8      *TempBuffer;
    IO_REGS    Regs        = IdeBusInterface->IdeDevice.Regs;
    UINTN      DMATimeout;
    UINTN      DescriptorBuffer;
    UINT8      Data8;
    UINT32     SectorSize = ATA_SECTOR_BYTES;
    BOOLEAN    SectorGTBytes = FALSE;
    //
    //Select the drive
    //
    IdeWriteByte( IdeBusInterface->PciIO, Regs.CommandBlock.DeviceReg, IdeBusInterface->IdeDevice.Device << 4 );

    if ( Check48BitCommand( ReadWriteCommand )) {
        MaxSectorCount = MAX_SECTOR_COUNT_PIO_48BIT;
    }
    else {
        MaxSectorCount = MAX_SECTOR_COUNT_PIO;
    }

    //
    // Calculate Sector Size
    //
    if((IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
       (!(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
       (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
        // The sector size is in words 117-118.
        SectorSize = (UINT32)(IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[13] + \
                              (IdeBusInterface->IdeDevice.IdentifyData.Reserved_104_126[14] << 16)) * 2;
    }

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

    do
    {
        if ( Total_Number_Of_Sectors > MaxSectorCount ) {
            CurrentSectorCount = 0;
        }
        else {
            CurrentSectorCount = Total_Number_Of_Sectors;
        }
        CurrentByteCount = (CurrentSectorCount == 0 ? MaxSectorCount : CurrentSectorCount) * SectorSize;

        DescriptorBuffer = (UINTN) gDescriptorBuffer;
        Status           = CreateDescriptorTable( &DescriptorBuffer, TempBuffer, CurrentByteCount, &RemaingByteCount );

        if ( EFI_ERROR( Status )) {
            return Status;
        }

        Status = InitBusMasterRegisters( IdeBusInterface, DescriptorBuffer, READWRITE );

        MaskandSaveInterrupt( IdeBusInterface );
        //
        //Enable Interrupt
        //
        IdeWriteByte( IdeBusInterface->PciIO, Regs.ControlBlock.DeviceControlReg, 0 );

        StartStopBusMastering( IdeBusInterface, TRUE );

        Status = IssueAtaReadWriteCommand( IdeBusInterface, LBA, (UINT32)CurrentSectorCount, ReadWriteCommand, NULL );

        if ( EFI_ERROR( Status )) {
            return EFI_DEVICE_ERROR;
        }

        //Timeout = 5000msec + Number of Sectors * 2
        DMATimeout = ((CurrentSectorCount == 0 ? MaxSectorCount : CurrentSectorCount) << 1) + gPlatformIdeProtocol->DmaAtaCompleteCommandTimeout;

        DMAStatus = WaitforDMAtoCompletion( IdeBusInterface, DMATimeout );

        Status = HandleATABMErrors( IdeBusInterface );

        StartStopBusMastering( IdeBusInterface, FALSE );
        //
        //Disable Interrupt
        //
        IdeWriteByte( IdeBusInterface->PciIO, Regs.ControlBlock.DeviceControlReg, 2 );
        //
        //Clear interrupt status
        //
        IdeReadByte( IdeBusInterface->PciIO,
                     IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMStatusRegister,
                     &Data8 );

        if ( Data8 & 4 ) {
            IdeWriteByte( IdeBusInterface->PciIO,
                          IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMStatusRegister,
                          Data8 );
        }

        RestoreInterrupt( IdeBusInterface );

        //
        //Check the status from WaitforDMAtoCompletion. More Descriptors are never formed. So EFI_SUCCESS_ACTIVE_SET is an error.
        //
        if ( EFI_ERROR( DMAStatus )) {
            return EFI_DEVICE_ERROR;
        }

        if ( EFI_ERROR( Status )) {
            return EFI_DEVICE_ERROR;
        }

        TempBuffer              += CurrentByteCount;
        Total_Number_Of_Sectors -= (CurrentSectorCount == 0 ? MaxSectorCount : CurrentSectorCount);
        LBA                     += (CurrentSectorCount == 0 ? MaxSectorCount : CurrentSectorCount);
    } while ( Total_Number_Of_Sectors );

    if (SectorGTBytes) {
        pBS->CopyMem( Buffer, TempBuffer, ByteCount);
        pBS->FreePool( TempBuffer );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	AtapiReadWriteBusMaster
//
// Description:	Read/Write data from/to the ATAPI device
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	VOID                                                    *Buffer,
//	UINTN							ByteCount,
//	UINT64							LBA,
//	UINT8							ReadWriteCommand,
//	BOOLEAN							READWRITE
//
// Output:
//		EFI_STATUS
//
// Modified:
//
// Referrals: AtapiBlkRead, AtapiBlkWrite
//
// Notes:
//	1. Prepare ATAPI Command Packet
//	2. Check for errors. If Media_Change, detect the new atapi media if present and return status accordingly.
//	3. Read/write data if the command packet is issues successfully.
//	4. Repeat from step 1 untill all data has been read/written.
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AtapiReadWriteBusMaster(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer,
    IN UINTN            ByteCount,
    IN UINT64           LBA,
    IN UINT8            ReadWriteCommand,
    IN BOOLEAN          READWRITE )
{
    EFI_STATUS   Status;
    EFI_STATUS   DMAStatus;
    INTN         TotalNumberofBlocks;
    INTN         TransferLength;
    UINTN        BytesRemainingTobeRead;
    UINTN        RemaingByteCount;
    ATAPI_DEVICE *AtapiDevice = IdeBusInterface->IdeDevice.AtapiDevice;
    VOID         *TempBuffer  = Buffer;
    IO_REGS      Regs         = IdeBusInterface->IdeDevice.Regs;
    UINT8        Data8;
    UINTN        DescriptorBuffer = (UINTN)gDescriptorBuffer;

    //
    //Check for CHK bit in status register before proceeding, if set give ATAPI reset
    //
    Status = CheckCHKonEntry( IdeBusInterface );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    TotalNumberofBlocks = ByteCount / AtapiDevice->BlockSize;

    for (; TotalNumberofBlocks >  0; TotalNumberofBlocks -= TransferLength )
    {
        //
        //Clear the buffer
        //
        ZeroMemory( AtapiDevice->PacketBuffer, AtapiDevice->PacketSize );

        //
        //Calculate # of blocks to be transferred
        //
        if ( TotalNumberofBlocks > 0xffff ) {
            TransferLength = 0xffff;
        }
        else {
            TransferLength = TotalNumberofBlocks;
        }

        //Update the buffer
        AtapiDevice->PacketBuffer[0] = ReadWriteCommand;
        AtapiDevice->PacketBuffer[1] = AtapiDevice->Lun << 5;
        AtapiDevice->PacketBuffer[2] = ((UINT32) LBA) >>  24;
        AtapiDevice->PacketBuffer[3] = ((UINT32) LBA) >> 16;
        AtapiDevice->PacketBuffer[4] = ((UINT16) LBA) >> 8;
        AtapiDevice->PacketBuffer[5] = ((UINT8) LBA) & 0xff;

        AtapiDevice->PacketBuffer[7] = (UINT8) ( TransferLength >> 8 );           // MSB
        AtapiDevice->PacketBuffer[8] = (UINT8) ( TransferLength & 0xff );     // LSB

        BytesRemainingTobeRead = TransferLength * AtapiDevice->BlockSize;

        Status = CreateDescriptorTable( &DescriptorBuffer, TempBuffer, BytesRemainingTobeRead, &RemaingByteCount );

        if ( EFI_ERROR( Status )) {
            return Status;
        }

        Status = InitBusMasterRegisters( IdeBusInterface, DescriptorBuffer, READWRITE );

        MaskandSaveInterrupt( IdeBusInterface );

        //Enable Interrupt
        IdeWriteByte( IdeBusInterface->PciIO, Regs.ControlBlock.DeviceControlReg, 0 );

        StartStopBusMastering( IdeBusInterface, TRUE );

        Status = IssueAtapiPacketCommand( IdeBusInterface, (UINT16*) AtapiDevice->PacketBuffer, DMA, 0xffff );

        if ( EFI_ERROR( Status )) {
            return Status;
        }

        DMAStatus = WaitforDMAtoCompletion( IdeBusInterface, gPlatformIdeProtocol->DmaAtaPiCompleteCommandTimeout );

        //Check for errors
        Status = HandleAtapiError( IdeBusInterface );

        StartStopBusMastering( IdeBusInterface, FALSE );

        //Disable Interrupt
        IdeWriteByte( IdeBusInterface->PciIO, Regs.ControlBlock.DeviceControlReg, 2 );

        //Clear interrupt status
        IdeReadByte( IdeBusInterface->PciIO,
                     IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMStatusRegister,
                     &Data8 );

        if ( Data8 & 4 ) {
            IdeWriteByte( IdeBusInterface->PciIO,
                          IdeBusInterface->IdeDevice.Regs.BusMasterBlock.BMStatusRegister,
                          Data8 );
        }

        RestoreInterrupt( IdeBusInterface );

        if ( Status != EFI_SUCCESS ) {
            //Some error has occured
            //Check if Device is getting ready. If yes, wait till it gets ready
            if ( AtapiDevice->Atapi_Status == BECOMING_READY ) {
                Status = TestUnitReady( IdeBusInterface );
            }

            if ( Status == EFI_MEDIA_CHANGED ) {
                Status = DetectAtapiMedia( IdeBusInterface );

                // This may happen during initial power-up also. If ReinstallProtocol  needs to be done,
                // then differentiate between power-up nad other cases.
                if ( Status == EFI_SUCCESS ) {
                    return EFI_MEDIA_CHANGED;    // Return Media Change
                }
            }
            return Status;
        }

        //
        //If WaitforDMAtoCompletion returns a error, read the status register again to make sure it is indeed a failure.
        //
        IdeReadByte( IdeBusInterface->PciIO, Regs.BusMasterBlock.BMStatusRegister, &Data8 );

        if ( Data8 & (BM_ERROR | BM_ACTIVE)) {
            return EFI_DEVICE_ERROR;
        }

        //Update pointer
        (UINT8*) TempBuffer += BytesRemainingTobeRead;
        LBA                 += TransferLength;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	CreateDescriptorTable
//
// Description:	Creates a IDE BUS master Descriptor Table
//
// Input:
//	IN OUT VOID						**DescriptorBuffer  // 128KB buffer
//	IN UINT32						StartAddress
//	IN UINT32						ByteCount
//	OUT	UINTN						*FinalByteCount
//
// Output:
//	DescriptorBuffer, EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//		1. Create a Physical Region Descriptor for IDE  Bus Master.
//		2. FinalByteCount will be the total # of Bytes that can be transferred
//			using this Descriptor. Most of the time FinalByteCount will be equal to ByteCount.
///			If the Descriptor Buffer exceeds 64K, then partial transfer will take place.
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CreateDescriptorTable(
    IN OUT UINTN *DescriptorBuffer,
    IN UINT8     *StartAddress,
    IN UINTN     ByteCount,
    OUT UINTN    *RemainingByteCount )
{
    UINT16                      Index;
    UINTN                       Address = (UINTN) &(*StartAddress);
    BUS_MASTER_DESCRIPTOR_TABLE *DescriptorTable;

    //64KB alignment
    *DescriptorBuffer &= 0xffff0000;
    *DescriptorBuffer += 0x10000;
    DescriptorTable    =        (BUS_MASTER_DESCRIPTOR_TABLE*)(*DescriptorBuffer);


    //Address should be DWORD aligned
    if ( Address & 0x3 ) {
        return EFI_INVALID_PARAMETER;
    }

    //Restore Address
    Address = (UINTN) &(*StartAddress);

    for ( Index = 0; Index <  0x10000 / 8; Index++ )
    {
        DescriptorTable[Index].BaseAddress = (UINT32) Address;
        DescriptorTable[Index].Flag        = 0;
        //
        // if Start address is not 64KB aligned, then bytecount cannot be 64KB (Data tranfer cannot cross 64KB boundry
        //
        if ( Address & 0xffff ) {
            DescriptorTable[Index].ByteCount = 0x10000 - (UINT16)( Address & 0xffff );

            if ( DescriptorTable[Index].ByteCount > ByteCount ) {
                DescriptorTable[Index].ByteCount = (UINT16)ByteCount;
            }
            ByteCount -= DescriptorTable[Index].ByteCount;
            Address   += DescriptorTable[Index].ByteCount;

            if ( ByteCount == 0 ) {
                break;
            }
        }
        else {                                    // address is 64KB aligned
            if ( ByteCount >= 0x10000 ) {
                DescriptorTable[Index].ByteCount = 0;
                ByteCount                       -= 0x10000;
                Address                         += 0x10000;

                if ( ByteCount == 0 ) {
                    break;
                }
            }
            else {
                DescriptorTable[Index].ByteCount = (UINT16) ByteCount;
                ByteCount                        = 0;
                break;
            }
        }
    }

    //
    //Update EOT
    //
    DescriptorTable[Index].Flag = 0x8000;

    *RemainingByteCount = ByteCount;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitBusMasterRegisters
//
// Description:	Initialize Bus Master registers
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	IN OUT VOID						*DescriptorBuffer
//	IN BOOLEAN						ReadWrite
//
// Output:
//	DescriptorBuffer, EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//		1. Create a Physical Region Descriptor for IDE  Bus Master.
//		2. FinalByteCount will be the total # of Bytes that can be transferred
//			using this Descriptor. Most of the time FinalByteCount will be equal to ByteCount.
///			If the Descriptor Buffer exceeds 64K, then partial transfer will take place.
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitBusMasterRegisters(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT UINTN        DescriptorBuffer,
    IN BOOLEAN          ReadWrite )

{
    IO_REGS Regs = IdeBusInterface->IdeDevice.Regs;
    UINT8   Data8;

    //
    //Update Read/Write Control and clear Start/Stop bit
    //
    IdeWriteByte( IdeBusInterface->PciIO, Regs.BusMasterBlock.BMCommandRegister, (ReadWrite == FALSE ? 1 : 0) << 3 );

    //
    //Clear the status
    //
    IdeReadByte( IdeBusInterface->PciIO, Regs.BusMasterBlock.BMStatusRegister, &Data8 );
    Data8 |= BM_INTERRUPT | BM_ERROR;
    IdeWriteByte( IdeBusInterface->PciIO, Regs.BusMasterBlock.BMStatusRegister, Data8 );

    //
    //Update Descriptor Table Pointer
    //
    IdeWriteDword( IdeBusInterface->PciIO, Regs.BusMasterBlock.BMDescriptorTablePointerReg, (UINT32) DescriptorBuffer );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	StartStopBusMastering
//
// Description:	Start/Stop Bus mAstering
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	IN BOOLEAN						StartStop       //	Start = TRUE
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//		Don't destroy Read/Write Control bit
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS StartStopBusMastering(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN BOOLEAN          StartStop )
{
    IO_REGS Regs = IdeBusInterface->IdeDevice.Regs;
    UINT8   Data8;

    //
    //Update  Start/Stop bit in Command Register
    //
    IdeReadByte( IdeBusInterface->PciIO, Regs.BusMasterBlock.BMCommandRegister, &Data8 );
    Data8 &= 0xFE;
    Data8 |= (StartStop == TRUE ? 1 : 0);
    IdeWriteByte( IdeBusInterface->PciIO, Regs.BusMasterBlock.BMCommandRegister, Data8 );
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	WaitforDMAtoCompletion
//
// Description:	Start/Stop Bus mAstering
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//	IN UINT32						TimeDelay (msec)
//
// Output:
//		EFI_STATUS   Success : If DMA completes with or with out Error.
//		EFI_DEVICE_ERROR	 : If timed out.
//
// Modified:
//
// Referrals:
//
// Notes:
//		1. Check for Interrupt bit set. If yes, command completed.
//		2. Check for Active bit to go Zero. If yes, command completed.
//		3. Waits for a max. of TimeDelay/10,000 sec for the command to get completed.
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WaitforDMAtoCompletion(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN UINTN            TimeDelay )
{
    UINT8   Data8;
    UINT8   Index2;
    UINT32  Index;
    IO_REGS Regs = IdeBusInterface->IdeDevice.Regs;

    for ( Index = 0; Index < TimeDelay; Index++ )
    {
        for ( Index2 = 0; Index2 < 10; Index2++ )
        {
            IdeReadByte( IdeBusInterface->PciIO, Regs.BusMasterBlock.BMStatusRegister, &Data8 );

            if ((Data8 & (BM_INTERRUPT | BM_ACTIVE)) == 4 ) {
                return EFI_SUCCESS;
            }

            if ((Data8 & (BM_INTERRUPT | BM_ACTIVE)) == 5 ) {
                return EFI_SUCCESS_ACTIVE_SET;
            }

            if ((Data8 & BM_ERROR) == 2 ) {
                return EFI_DEVICE_ERROR;
            }
            pBS->Stall( 100 );                           // 100 usec
        }
    }

    return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	HandleATABMErrors
//
// Description:		Check for any errors
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
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
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HandleATABMErrors(
    IN IDE_BUS_PROTOCOL *IdeBusInterface )
{
    EFI_STATUS Status;

    Status = WaitForCmdCompletion( IdeBusInterface );
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	MaskandSaveInterrupt
//
// Description:	Mask IDE interrupt
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//
// Output:
//
// Modified:
//
// Referrals: AtaReadWriteBusMaster
//
// Notes:
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MaskandSaveInterrupt(
    IDE_BUS_PROTOCOL *IdeBusInterface )
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	RestoreInterrupt
//
// Description:	Restore the Interrupt mask
//
// Input:
//	IN IDE_BUS_PROTOCOL				*IdeBusInterface,
//
// Output:
//
// Modified:
//
// Referrals: AtaReadWriteBusMaster
//
// Notes:
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RestoreInterrupt(
    IDE_BUS_PROTOCOL *IdeBusInterface )
{
    return EFI_SUCCESS;
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
