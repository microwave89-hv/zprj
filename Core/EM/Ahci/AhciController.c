//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciController.c 41    1/27/14 4:57a Rameshr $
//
// $Revision: 41 $
//
// $Date: 1/27/14 4:57a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciController.c $
// 
// 41    1/27/14 4:57a Rameshr
// [TAG]  		EIP148180
// [Category]  	Improvement
// [Description]  	Change from EFI_MBR_WRITE_PROTECTION_PROTOCOL to
// AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL
// [Files]  		Ahcibus.c, Ahcibus.h, AhciComponentName.c, AhciController.c
// 
// 40    12/20/13 4:06a Rameshr
// [TAG]  		EIP126640
// [Category]  	Improvement
// [Description]  	AHCIBUS driver need to preserve the port settings in
// GeneratePortReset 
// [Files]  		Ahcibus.c, AhciController.c
// 
// 39    8/27/13 4:16a Rameshr
// [TAG]  		EIP125560
// [Category]  	Improvement
// [Description]  	MbrWriteProtectionProtocol file name changesd to
// AmiMbrWriteProtectionProtocol.h
// [Files]  		AhciController.c, AhciBus.h, Ahcibus.c
// 
// 38    7/01/13 5:32a Kapilporwal
// [TAG]  		EIP125560
// [Category]  	Improvement
// [Description]  	 	Please support Boot Sector Virus Protection for CSM
// Disabled Mode
// [Files]  		VirusProtect.c, VirusProtect.dxs, AhciBus.c,
// AhciController.c, CsmBlockIo.c, CsmInt13.c, Ata.c, IdeBus.c,
// SdioBlkIo.c, SdioDriver.c, efiusbmass.c
// 
// 37    11/18/12 11:45p Rameshr
// [TAG]  		EIP102518
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	SCT failure for ATAPI BlockIO
// [RootCause]  	BufferSize and IOAllign checking not added for Atapi
// BlockIO protocol functions
// [Solution]  	Added BufferSize and IOAllign checking for Atapi BlockIO
// protocol functions
// [Files]  		AhciController.c
// 
// 36    9/17/12 12:52a Rameshr
// [TAG]  		EIP100335
// [Category]  	Improvement
// [Description]  	Port Multiplier spend long time to connect device.
// [Files]  		Ahcibus.c , AhciController.c
// 
// 35    9/17/12 12:43a Anandakrishnanl
// [TAG]  		EIP100847
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hangs when Memory allocation >4Gb in AHCI Mode
// [RootCause]  	DBAU not programmed for AhciController
// [Solution]  	Fixed by Programming DBAU in PRDT Table
// [Files]  		AhciController.c
// 
// 34    8/21/12 2:28a Rameshr
// [TAG]  		EIP98526
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	FIS and CommandList Base address store and restore wont
// work incase of recursive call
// [RootCause]  	FIS and CommandList Base address store and restore wont
// work incase of recursive call
// [Solution]  	FIS and Command List base Address save and restore done
// properly when the function called recursively.
// [Files]  		Ahcicontroller.c
// 
// 33    8/17/12 3:10a Srikantakumarp
// [TAG]  		EIP95863
// [Category]  	Bug Fix
// [Symptom]  	AhciSmm doesnt save and restore the upper 32bits of FBU and
// CLBU
// [RootCause]  	As Windows uses the 64bit address for FIS Base Address
// and Command List Base Address, and AHCISMM driver doesn't take care of
// the upper 32bit value of those which cause the failure in AhciSMM
// driver.
// [Solution]  	Save and Restore the upper 32bits of FBU and CLBU in
// AhciSmm Driver.
// [Files]  		AhciController.c, AhciSmm.c
// 
// 32    8/16/12 3:06a Rajeshms
// [TAG]  		EIP97048
// [Category]  	New Feature
// [Description]  	ATAPI PassThru Support using
// EFI_EXT_SCSI_PASS_THRU_PROTOCOL.
// [Files]  		AhciBus.c, AhciController.c, IdeBus.c, Atapi.c, PIDEBus.h,
// PAhciBus.h, ScsiPassThruAtapi.sdl, ScsiPassThruAtapi.mak,
// ScsiPassThruAtapi.c, ScsiPassThruAtapiSupport.h, ScsiPassThruAtapi.chm,
// ScsiPassThruExt.h
// 
// 31    2/03/12 3:23a Rameshr
// [TAG]  		EIP82275
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	SataReadWritePio doesn't work if the ReadSector count is
// more than 256 sectors
// [RootCause]  	Buffer Address not incremented for the next Read
// [Solution]  	Handled the buffer address properly for the next Pio Read
// [Files]  		AhciController.c
// 
// 30    11/08/11 5:19a Deepthins
// [TAG]  		EIP74607
// [Category]  	Improvement
// [Description]  	Block IO Read/Write function, the alignment should be
// proper. IoAlign value is 0 or 1 means that the buffer can be placed
// anywhere in memory. Otherwise, IoAlign must be a power of 2, and the
// requirement is that the start address of a buffer must be evenly
// divisible by IoAlign with no remainder.
// [Files]  		Ata.c, Atapi.c and AhciController.c
// 
// 29    11/07/11 4:31a Deepthins
// [TAG]  		EIP74607
// [Category]  	Improvement
// [Description]  	IoAlign value is 0 or 1 means that the buffer can be
// placed anywhere in memory. Otherwise, IoAlign must be a power of 2, and
// the requirement is that the start address of a buffer must be
// evenlydivisible by 2 to the power of IoAlign with no remainder.
// [Files]  		AhciController.c
// 
// 28    11/07/11 2:30a Deepthins
// [TAG]  		EIP73941
// [Category]  	Improvement
// [Description]  	BufferSize is 0, ReadBlock function should return
// EFI_SUCCESS without actual reading.
// [Files]  		AhciController.c
// 
// 27    5/09/11 6:29a Anandv
// [TAG] - EIP59552
// [Category] - BUG FIX
// [Severity] - Normal
// [Symptom] -AhciController.c file in Ahci driver needs modification to
// Support Index/Data Port access method for getting the FIS Address.
// [RootCause] - FISAddress was Obtained using MMIO method irrespective of
// "INDEX_DATA_PORT_ACCESS" SDL token.
// [Solution] - FISAddress is now obtained using Port I/O or MMIO method
// depending on 
// "INDEX_DATA_PORT_ACCESS" SDL token.
// [Files] - AhciController.c
// 
// 26    3/29/11 1:03a Lavanyap
// [TAG] - EIP53849
// [Category] - BUG FIX
// [Severity] - Normal
// [Symptom] - Ide Bus Sources cannot build in IA32 DEBUG mode.
// [RootCause] - It happened because of usage of << and * with UINT64
// values in AtaPioDataOut() and SataPioDataOut().
// [Solution] - Shl64 and Mul64 functions have been implemented to operate
// UINT64 values.
// [Files] - Ata.c, AhciController.c
// 
// 25    2/21/11 3:38a Rameshr
// Helpbuilder Issue Resolved
// 
// 24    2/18/11 5:06a Rameshr
// [TAG]- EIP 37975
// [Category]-IMPROVEMENT
// [Description]- Klocwork Issues II - IDE/Ahci module
// [Files]- AhciBus.c, AhciController.c
// 
// 23    2/11/11 4:22a Rameshr
// [TAG]  		EIP53730
// [Category]  	Improvement
// [Description]  	Add Odd Loading type information into ATAPI_DEVICE
// structure in AHCI mode
// [Files]  		AhciBus.c
// AhciController.c
// AhciBus.h
// 
// 22    2/10/11 10:35a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AhciSrc.mak
// AhciBus.c
// AhciController.c
// AhciComponentName.c
// AhciBus.h
// AhciController.h
// 
// 21    12/23/10 3:59a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 20    4/16/10 4:15p Pats
// EIP 30719: Support for the HDD with sector size more than 512bytes.
// 
// 19    9/22/09 10:53a Krishnakumarg
// Code modified to update SataDevInterface->identifydata in
// GetIdentifyData function instead of returning in global variable -
// EIP26411
// 
// 18    9/21/09 12:34p Krishnakumarg
// It takes a long time to detect large size HDD(eg. 500GB, 1TB size)
// under AHCI mode-EIP26499.
// Replaced TAB with spaces for AMI code standard
// 
// 17    8/12/09 5:07p Davidd
// Corrected command parameter error in all PACKET_COMMAND - EIP 24817
// 
// 16    6/22/09 11:35a Rameshr
// Odd Type information Saved in Atapi Device Structure.
// EIP:21548
// 
// 15    6/18/09 4:27p Rameshr
// if the Erase command timeout value is 0 or 255, wait for the Erase
// command completion without timeout value
// EIP:20630
// 
// 14    4/29/09 10:54a Rameshr
// 
// 13    4/28/09 3:51p Rameshr
// 
// HDD password support in RAID mode
// EIP:20421
// 
// 12    3/29/09 11:08a Rameshr
// Security Erase command timeout value should be from the Identify packet
// command word 89
// EIP 20630
// 
// 11    12/11/08 1:55p Srinin
// After COMRESET, wait for shadow status register to get synced up with
// D2H FIS
// 
// 10    26/09/08 12:32p Anandakrishnanl
// Fixed Ahci Block Write Issue Which Exceeds 4MB. Added the Proper Offset
// of Descriptor and Fixed Valid  PRDT_I Bit.
// 
// 9     13/08/08 2:24p Anandakrishnanl
// Fixed the Minor error that occured in Previous Checkin for EfiDiag NO
// Media Issue
// 
// 8     12/08/08 11:26a Anandakrishnanl
// Fixed the error reported by EFI Diag r(CD/DVD test) to return
// EFI_NO_MEDIA.
// 
// 7     5/28/08 9:38a Rameshraju
// Based on the SDL token index/data or MMIO method used to access the
// AHCI configuration space.
// 
// 6     5/09/08 10:05a Rameshraju
// Default status initilized.
// 
// 5     4/10/08 12:52p Srinin
// PMPort field in Command header and in FIS is set to zero instead of 0xF
// when PORT 0 is accessed.
// 
// 4     4/03/08 4:40p Srinin
// In ReadytoAcceptCmd Status was not initialized. Fixed it.
// 
// 3     3/24/08 6:19p Fasihm
// Fixed issue that few HDDs not detected because of PhyRdy Change bit.
// 
// 2     7/03/08 5:31p Anandakrishnanl
// Added Smart Support as a seperate Driver and Corresponding changes to
// invoke Smart Protocols and removed SDL-Token
// 
// 1     28/02/08 6:03p Anandakrishnanl
// AHCI Bus Driver initial check-in.
// 
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: AhciController.c
//
// Description: Provides Access to AHCI Controller
//
//<AMI_FHDR_END>
//**********************************************************************

#include "AhciBus.h"

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
extern AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL *AmiBlkWriteProtection;
#endif

BOOLEAN gPortReset = FALSE;             // Avoid Re-entry
BOOLEAN gSoftReset = FALSE;             // Avoid Re-entry
UINT32  gCommandListBaseAddress = 0;
UINT32  gFisBaseAddress;
UINT32  gCommandListBaseAddress2;
UINT32  gFisBaseAddress2;

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SataBlkRead
//
// Description: Read from the Sata ATA Device
//
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL        *This,
//  IN UINT32                       MediaId,
//  IN EFI_LBA                      LBA,
//  IN UINTN                        BufferSize,
//  OUT VOID                        *Buffer
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: SataAtaBlkReadWrite 
//
// Notes:   
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataBlkRead(
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer
 )
{

    EFI_STATUS  Status;

    Status =  SataAtaBlkReadWrite(This, MediaId, LBA, BufferSize, Buffer, 0);
 
    TRACE((TRACE_ALWAYS,"AHCI Read: LBA : %lx ByteCount : %lx\n", LBA, BufferSize));

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SataBlkWrite
//
// Description: Write to Sata ATA Device
//
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL        *This,
//  IN UINT32                       MediaId,
//  IN EFI_LBA                      LBA,
//  IN UINTN                        BufferSize,
//  OUT VOID                        *Buffer
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: SataAtaBlkReadWrite 
//
// Notes:   
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataBlkWrite(
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer
 )
{

    EFI_STATUS  Status;

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
    if(AmiBlkWriteProtection != NULL) {
        // Get user input
        Status = AmiBlkWriteProtection->BlockIoWriteProtectionCheck( 
                                                    AmiBlkWriteProtection,
                                                    This,
                                                    LBA,
                                                    BufferSize
                                                    );
        // Abort operation if denied
        if(Status == EFI_ACCESS_DENIED) {
            return Status;
        }
    } 
#endif

    Status =  SataAtaBlkReadWrite(This, MediaId, LBA, BufferSize, Buffer, 1);

    TRACE((TRACE_ALWAYS,"AHCI Write: LBA : %lx ByteCount : %lx\n", LBA, BufferSize));

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SataAtaBlkReadWrite
//
// Description: Read/Write to/from Sata ATA Device
//
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL        *This,
//  IN UINT32                       MediaId,
//  IN EFI_LBA                      LBA,
//  IN UINTN                        BufferSize,
//  OUT VOID                        *Buffer,
//  BOOLEAN                         READWRITE
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: SataReadWriteBusMaster, SataReadWritePio 
//
// Notes:   
//  1. Check for validity of the input
//  2. Issue DMA or PIO Read/Write call.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataAtaBlkReadWrite (
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer,
    BOOLEAN                         READWRITE
)
{

    EFI_STATUS  Status = EFI_DEVICE_ERROR;
    SATA_DEVICE_INTERFACE   *SataDevInterface = ((SATA_BLOCK_IO *)This)->SataDevInterface;
    EFI_BLOCK_IO_MEDIA      *BlkMedia = This->Media;
    UINTN                   DataN;
    UINTN                   BufferAddress;

    // Check if Media ID matches
    if (BlkMedia->MediaId != MediaId) return EFI_MEDIA_CHANGED;

    if (BufferSize == 0) return EFI_SUCCESS;
    
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

    // Check whether the block size is multiple of BlkMedia->BlockSize
    DataN = BufferSize % BlkMedia->BlockSize;
    if (DataN) return EFI_BAD_BUFFER_SIZE;

    // Check for Valid start LBA #
    if (LBA > BlkMedia->LastBlock) return EFI_INVALID_PARAMETER;

    // Check for Valid End LBA #
    DataN = BufferSize / BlkMedia->BlockSize;
    if (LBA + DataN > BlkMedia->LastBlock + 1) return EFI_INVALID_PARAMETER;

    #if IDEBUSMASTER_SUPPORT
    if (DMACapable(SataDevInterface)) {     
    Status = SataReadWriteBusMaster (SataDevInterface, Buffer, BufferSize, LBA, 
                        READWRITE ? SataDevInterface->WriteCommand : SataDevInterface->ReadCommand, 
                        READWRITE);
        return Status;
    }
    #endif

    Status = SataReadWritePio (SataDevInterface, Buffer, BufferSize, LBA, 
                        READWRITE ? SataDevInterface->WriteCommand : SataDevInterface->ReadCommand, 
                        READWRITE);

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SataAtapiBlkRead
//
// Description: Read from the Sata ATAPI Device
//
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL        *This,
//  IN UINT32                       MediaId,
//  IN EFI_LBA                      LBA,
//  IN UINTN                        BufferSize,
//  OUT VOID                        *Buffer
//
// Output:
//      EFI_STATUS
//
// Modified:
// 
// Referrals: SataAtapiBlkReadWrite 
//
// Notes:
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SataAtapiBlkRead(
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer
 )
{

    EFI_STATUS  Status;

    Status =  SataAtapiBlkReadWrite(This, MediaId, LBA, BufferSize, Buffer, 0);

    TRACE((TRACE_ALWAYS,"AHCI ATAPI Read: LBA : %lx ByteCount : %lx\n", LBA, BufferSize));

    return Status;



}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SataAtapiBlkWrite
//
// Description: Write to Sata ATAPI Device
//
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL        *This,
//  IN UINT32                       MediaId,
//  IN EFI_LBA                      LBA,
//  IN UINTN                        BufferSize,
//  OUT VOID                        *Buffer
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: SataAtapiBlkReadWrite
//
// Notes:
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataAtapiBlkWrite(
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer
 )
{

    EFI_STATUS  Status;

    Status =  SataAtapiBlkReadWrite(This, MediaId, LBA, BufferSize, Buffer, 1);

    TRACE((TRACE_ALWAYS,"AHCI ATAPI Read: LBA : %lx ByteCount : %lx\n", LBA, BufferSize));

    return Status;

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   SataAtapiBlkReadWrite
//
// Description: Read/Write to/from Sata ATAPI Device
//
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL        *This,
//  IN UINT32                       MediaId,
//  IN EFI_LBA                      LBA,
//  IN UINTN                        BufferSize,
//  OUT VOID                        *Buffer
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:   
//  1. Check for validity of Inputs
//  2. Check whether Media is present or not
//  3. Issue ATAPi Packet command
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataAtapiBlkReadWrite(
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN UINT32                       MediaId,
    IN EFI_LBA                      LBA,
    IN UINTN                        BufferSize,
    OUT VOID                        *Buffer,
    BOOLEAN                         READWRITE
 )
{

    EFI_STATUS  Status = EFI_DEVICE_ERROR;
    SATA_DEVICE_INTERFACE   *SataDevInterface = ((SATA_BLOCK_IO *)This)->SataDevInterface;
    EFI_BLOCK_IO_MEDIA      *BlkMedia = This->Media;
    UINTN                   DataN;
    ATAPI_DEVICE            *AtapiDevice = SataDevInterface->AtapiDevice;
    COMMAND_STRUCTURE       CommandStructure;
    INTN                    TotalNumberofBlocks;
    INTN                    TransferLength;
    UINTN                   BytesRemainingTobeRead;
    VOID                    *TempBuffer = Buffer;
    UINTN                   BufferAddress;


    //  Check if Media Present

    if (BlkMedia->MediaPresent == FALSE) {
        Status = DetectAtapiMedia(SataDevInterface);
        if (Status == EFI_SUCCESS) return EFI_MEDIA_CHANGED;
        if (Status == EFI_NO_MEDIA) return Status;
        return EFI_DEVICE_ERROR;
    }

    //  Check if Media ID matches

    if (BlkMedia->MediaId != MediaId) return EFI_MEDIA_CHANGED;

    if (BufferSize == 0) return EFI_SUCCESS;

    // If IoAlign values is 0 or 1, means that the buffer can be placed
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign
    // with no remainder.

    (VOID *)BufferAddress = Buffer;
    if((BlkMedia->IoAlign > 1 ) && (BufferAddress % BlkMedia->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }

    //  Check whether the block size is multiple of BlkMedia->BlockSize

    DataN = BufferSize % BlkMedia->BlockSize;
    if (DataN) return EFI_BAD_BUFFER_SIZE;

    //  Check for Valid start LBA #

    if (LBA > BlkMedia->LastBlock) return EFI_INVALID_PARAMETER;

    //  Check for Valid End LBA #8

    DataN = BufferSize / BlkMedia->BlockSize;
    if (LBA + DataN > BlkMedia->LastBlock + 1) return EFI_INVALID_PARAMETER;


    TotalNumberofBlocks = BufferSize / AtapiDevice->BlockSize;

    for (; TotalNumberofBlocks >  0; TotalNumberofBlocks -= TransferLength) {  

        ZeroMemory (&CommandStructure, sizeof(CommandStructure));

        // Calculate # of blocks to be transferred

        if (TotalNumberofBlocks > 0xffff) 
            TransferLength = 0xffff;
        else
            TransferLength = TotalNumberofBlocks;

        BytesRemainingTobeRead = TransferLength * AtapiDevice->BlockSize;

        if (READWRITE) CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = SataDevInterface->WriteCommand;
        else CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = SataDevInterface->ReadCommand;
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[1] = AtapiDevice->Lun << 5;
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[2] = (UINT8)(((UINT32) LBA) >>  24);
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[3] = (UINT8)(((UINT32) LBA) >> 16);
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[4] = (UINT8)(((UINT16) LBA) >> 8);
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[5] = (UINT8)(((UINT8) LBA) & 0xff);
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[7] = (UINT8) (TransferLength >> 8);        // MSB
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[8] = (UINT8) (TransferLength & 0xff);      // LSB
        CommandStructure.Buffer = TempBuffer;
        CommandStructure.ByteCount = (UINT32)BytesRemainingTobeRead;

        Status = ExecutePacketCommand(SataDevInterface, &CommandStructure, READWRITE);

        if (Status != EFI_SUCCESS) {

            // Some error has occured
            // Check if Device is getting ready. If yes, wait till it gets ready

            if (AtapiDevice->Atapi_Status == BECOMING_READY) {
                Status = TestUnitReady(SataDevInterface);
            }

            if (Status == EFI_MEDIA_CHANGED ) {
                Status = DetectAtapiMedia(SataDevInterface);
                if (Status == EFI_SUCCESS) return EFI_MEDIA_CHANGED;    // Return Media Change
                if (Status == EFI_NO_MEDIA) {
                    SataDevInterface->SataBlkIo->BlkIo.Media->MediaPresent = FALSE;
                    return Status;
                }
            }
            return Status;
        }

        if (CommandStructure.ByteCount != BytesRemainingTobeRead) return EFI_DEVICE_ERROR;

        // Update pointer

        (UINT8 *) TempBuffer += BytesRemainingTobeRead;
        LBA += TransferLength;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SataReset
//
// Description: Reset ATA device
//
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL        *This,
//  IN BOOLEAN                      ExtendedVerification
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataReset (
    IN EFI_BLOCK_IO_PROTOCOL        *This,
    IN BOOLEAN                      ExtendedVerification
 )
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SataBlkFlush
//
// Description: Flush the cache
// Input:
//  IN EFI_BLOCK_IO_PROTOCOL            *This,
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals:  
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataBlkFlush(
    IN EFI_BLOCK_IO_PROTOCOL        *This
 )
{
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SataReadWritePio
//
// Description: Issues Read/Write Command and Read/Write the data from/to the ATA device
//
// Input:
//  IN IDE_BUS_PROTOCOL             *IdeBusInterface,
//  IN OUT VOID                     *Buffer,
//  UINTN                           ByteCount,
//  UINT64                          LBA
//  IN UINT8                        ReadWriteCommand,
//  IN BOOLEAN                      ReadWrite        Read/Write = 0/1
//
// Output:
//  *Buffer, EFI_STATUS
//
// Modified:
//      
// Referrals: ExecutePioDataCommand 
//
// Notes:   
//  1. Get the Max. number of sectors that can be Read/written in one Read/Write PIO command
//  2. Update the Command Structure
//  3. Issue ExecutePioDataCommand.
//  4. If all the bytes are read exit else goto step 2 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataReadWritePio(
    IN SATA_DEVICE_INTERFACE        *SataDevInterface,
    IN OUT VOID                     *Buffer,
    IN UINTN                        ByteCount,
    IN UINT64                       LBA,
    IN UINT8                        ReadWriteCommand,
    IN BOOLEAN                      READWRITE
 ) 
{
    EFI_STATUS                      Status;
    UINT32                          SectorCount;
    INT64                           MaxSectorCount;
    INT64                           Total_Number_Of_Sectors;
    COMMAND_STRUCTURE               CommandStructure;
    UINT32                          SectorSize = ATA_SECTOR_BYTES;
    UINT8                           *TempBuffer = Buffer;
    if (Check48BitCommand(ReadWriteCommand)) 
        MaxSectorCount = MAX_SECTOR_COUNT_PIO_48BIT;
    else 
        MaxSectorCount = MAX_SECTOR_COUNT_PIO;

    //
    // Calculate Sector Size
    //
    if((SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
       (!(SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
       (SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
        // The sector size is in words 117-118.
        SectorSize = (UINT32)(SataDevInterface->IdentifyData.Reserved_104_126[13] + \
                              (SataDevInterface->IdentifyData.Reserved_104_126[14] << 16)) * 2;
    }

    if (SectorSize > ByteCount) SectorSize = (UINT32)ByteCount;

    // Calculate the total number of Sectors to be transferred
    Total_Number_Of_Sectors = ByteCount / SectorSize ;

    for ( ;Total_Number_Of_Sectors > 0; Total_Number_Of_Sectors -= MaxSectorCount) {

        if (Total_Number_Of_Sectors > MaxSectorCount) SectorCount = 0;
        else SectorCount = (UINT32) Total_Number_Of_Sectors;

        ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));

        if (Check48BitCommand (ReadWriteCommand)) {  
            CommandStructure.LBALowExp = (UINT8)Shr64(LBA,24);
            CommandStructure.LBAMidExp = (UINT8)Shr64(LBA,32);
            CommandStructure.LBAHighExp = (UINT8)Shr64(LBA,40);
            CommandStructure.Device = 0x40;                                 // 48Bit LBA
        }
        else {                                                              // 28 Bit LBA
            CommandStructure.Device = ((UINT8) ((UINT32) LBA >> 24) & 0x0f) | 0x40;   
        }
        
        CommandStructure.SectorCount = (UINT16) SectorCount;
        CommandStructure.LBALow = (UINT8)LBA;
        CommandStructure.LBAMid = (UINT8)(((UINT32)LBA >>8) & 0xff);
        CommandStructure.LBAHigh = (UINT8)(((UINT32)LBA >>16) & 0xff);
        CommandStructure.Command = ReadWriteCommand;

        CommandStructure.Buffer = TempBuffer;
        CommandStructure.ByteCount = (UINT32)(SectorCount == 0 ? MaxSectorCount : Total_Number_Of_Sectors) * SectorSize ;

        Status = ExecutePioDataCommand (SataDevInterface, &CommandStructure, READWRITE); // Returns # of bytes read

        if (EFI_ERROR(Status)) { 
            return EFI_DEVICE_ERROR; 
        }

        TempBuffer += CommandStructure.ByteCount;
        SectorCount = CommandStructure.ByteCount / SectorSize ;
        LBA += SectorCount;

    }

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SataPioDataOut
//
// Description: Issues Read/Write Command with SubCommand feature
//              and Reads/Writes data to the ATA device.
//
// Input:
//    IN SATA_DEVICE_INTERFACE        *SataDevInterface,
//    IN OUT VOID                     *Buffer,
//    IN UINTN                        ByteCount,
//    IN UINT8                        Features,
//    IN UINT16                       LBALow,
//    IN UINT8                        LBALowExp,
//    IN UINT8                        LBAMid,
//    IN UINT8                        LBAMidExp,
//    IN UINT8                        LBAHigh,
//    IN UINT8                        LBAHighExp,
//    IN UINT8                        ReadWriteCommand
//    IN BOOLEAN                      READWRITE
//
// Output:
//    EFI_STATUS
//
// Modified:
//      
// Referrals: ExecutePioDataCommand 
//
// Notes:   
//  1. Get the Max. number of sectors that can be transferred in one Read/Write PIO command
//  2. Update the Command Structure
//  3. Issue ExecutePioDataCommand.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SataPioDataOut (
    IN SATA_DEVICE_INTERFACE        *SataDevInterface,
    IN OUT VOID                     *Buffer,
    IN UINTN                        ByteCount,
    IN UINT8                        Features,
    IN UINT8                        LBALow,
    IN UINT8                        LBALowExp,
    IN UINT8                        LBAMid,
    IN UINT8                        LBAMidExp,
    IN UINT8                        LBAHigh,
    IN UINT8                        LBAHighExp,
    IN UINT8                        ReadWriteCommand,
    IN BOOLEAN                      READWRITE
 )
{
    EFI_STATUS                      Status;
    UINT32                          SectorCount;
    INT64                           MaxSectorCount;
    INT64                           Total_Number_Of_Sectors;
    COMMAND_STRUCTURE               CommandStructure;
    UINT32                          SectorSize = ATA_SECTOR_BYTES;
    UINT64                          LBA = 0;
    UINT64                          LBAHighDword = 0;

    if (Check48BitCommand(ReadWriteCommand)) { 
        MaxSectorCount = MAX_SECTOR_COUNT_PIO_48BIT;
        //
        //	if 48 Bit LBA form Upper Dword
        //
        LBAHighDword |= LBAHighExp;
        LBAHighDword = ( Shl64(( Shl64( LBAHighDword, 8)| LBAMidExp), 8)| LBALowExp);
    } else { 
        MaxSectorCount = MAX_SECTOR_COUNT_PIO;
    }
    //
    //	Complete LBA
    //
    LBA |= LBAHigh;
    LBA = (( Shl64(( Shl64( LBA, 8) | LBAMid ), 8)| LBALow)| Shl64( LBAHighDword, 24 ));

    //
    // Calculate Sector Size
    //
    if((SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
       (!(SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
       (SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
        // The sector size is in words 117-118.
        SectorSize = (UINT32)(SataDevInterface->IdentifyData.Reserved_104_126[13] + \
                              (SataDevInterface->IdentifyData.Reserved_104_126[14] << 16)) * 2;
    }

    if (SectorSize > ByteCount) SectorSize = (UINT32)ByteCount;

    // Calculate the total number of Sectors to be transferred
    Total_Number_Of_Sectors = ByteCount / SectorSize ;

    for ( ;Total_Number_Of_Sectors > 0; Total_Number_Of_Sectors -= MaxSectorCount) {

        if ( Total_Number_Of_Sectors > MaxSectorCount ) SectorCount = 0;
        else SectorCount = (UINT32) Total_Number_Of_Sectors;

        ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));

        if (Check48BitCommand (ReadWriteCommand)) {
            //
            // If 48Bit LBA then form Upper DWord  
            //
            CommandStructure.LBALowExp  = LBALowExp;
            CommandStructure.LBAMidExp  = LBAMidExp;
            CommandStructure.LBAHighExp = LBAHighExp;
            CommandStructure.Device     = 0x40;
        }
        else {                                                              // 28 Bit LBA
            CommandStructure.Device = ((UINT8) LBAHigh & 0x0f) | 0x40;   
        }

        CommandStructure.Features    = Features;                            // SubCommand
        CommandStructure.SectorCount = (UINT16) SectorCount;
        CommandStructure.LBALow      = LBALow;
        CommandStructure.LBAMid      = LBAMid;
        CommandStructure.LBAHigh     = LBAHigh;
        CommandStructure.Command     = ReadWriteCommand;

        CommandStructure.Buffer    = Buffer;
        CommandStructure.ByteCount = (UINT32)(SectorCount == 0 ? MaxSectorCount : Total_Number_Of_Sectors) * SectorSize ;

        Status = ExecutePioDataCommand (SataDevInterface, &CommandStructure, READWRITE); // Returns # of bytes read
        if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

        SectorCount = CommandStructure.ByteCount / SectorSize ;
        LBA += SectorCount;

    }

    return EFI_SUCCESS;

}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   SataReadWriteBusMaster
//
// Description: Issues Read/Write Command and Read/Write the data from/to the ATA device
//              using BusMaster
//
// Input:
//  SATA_DEVICE_INTERFACE           *SataDevInterface,
//  IN OUT VOID                     *Buffer,
//  IN UINTN                        ByteCount,
//  IN UINT64                       LBA,
//  IN UINT8                        ReadWriteCommand,
//  IN BOOLEAN                      READWRITE
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: ExecuteDmaDataCommand
//
// Notes:   
//  1. Get the Max. number of sectors that can be Read/written in one Read/Write Bus master command
//  2. Update the Command Structure
//  3. Issue ExecutePioDataCommand.
//  4. If all the bytes are read exit else goto step 2 
//
//<AMI_PHDR_END>
//**********************************************************************                
EFI_STATUS
SataReadWriteBusMaster(
    SATA_DEVICE_INTERFACE           *SataDevInterface,
    IN OUT VOID                     *Buffer,
    IN UINTN                        ByteCount,
    IN UINT64                       LBA,
    IN UINT8                        ReadWriteCommand,
    IN BOOLEAN                      READWRITE
 ) 
{

    EFI_STATUS              Status;
    UINTN                   Total_Number_Of_Sectors,MaxSectorCount;
    UINTN                   CurrentSectorCount,CurrentByteCount;
    UINT8                   *TempBuffer = Buffer;
    COMMAND_STRUCTURE       CommandStructure;
    UINT32                  SectorSize = ATA_SECTOR_BYTES;

    if (Check48BitCommand(ReadWriteCommand)) 
        MaxSectorCount = MAX_SECTOR_COUNT_PIO_48BIT;
    else 
        MaxSectorCount = MAX_SECTOR_COUNT_PIO;

    //
    // Calculate Sector Size
    //
    if((SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT14) && // WORD 106 valid? - BIT 14 - 1
       (!(SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT15)) && // WORD 106 valid? - BIT 15 - 0
       (SataDevInterface->IdentifyData.Reserved_104_126[2] & BIT12)) { // WORD 106 bit 12 - Sectorsize > 256 words
        // The sector size is in words 117-118.
        SectorSize = (UINT32)(SataDevInterface->IdentifyData.Reserved_104_126[13] + \
                              (SataDevInterface->IdentifyData.Reserved_104_126[14] << 16)) * 2;
    }
    if (SectorSize > ByteCount) SectorSize = (UINT32)ByteCount;

    Total_Number_Of_Sectors = ByteCount / SectorSize ;

    do {
        if (Total_Number_Of_Sectors > MaxSectorCount) CurrentSectorCount = 0;
            else CurrentSectorCount = Total_Number_Of_Sectors;
        CurrentByteCount = (CurrentSectorCount == 0 ? MaxSectorCount : CurrentSectorCount) * SectorSize ;

        ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));

        CommandStructure.Buffer = TempBuffer;
        CommandStructure.ByteCount = (UINT32)CurrentByteCount;
        CommandStructure.Command = ReadWriteCommand;

        if (Check48BitCommand (ReadWriteCommand)) {  
            // 48 Bit LBA   
            // Write the Upper LBA DWORD and Upper byte of Sector Count
            CommandStructure.LBALowExp = (UINT8)Shr64(LBA,24);
            CommandStructure.LBAMidExp = (UINT8) Shr64(LBA,32);
            CommandStructure.LBAHighExp = (UINT8) Shr64(LBA,40);
            CommandStructure.Device = 0x40;     // 48Bit LBA
        }
        else {                                                  // 28 Bit LBA
            CommandStructure.Device = ((UINT8) ((UINT32) LBA >> 24) & 0x0f) | 0x40;
        }

        CommandStructure.SectorCount = (UINT16) CurrentSectorCount;
        CommandStructure.LBALow = (UINT8)LBA;
        CommandStructure.LBAMid = (UINT8) (((UINT32)LBA >>8) & 0xff);
        CommandStructure.LBAHigh = (UINT8) (((UINT32)LBA >>16) & 0xff);

        Status = ExecuteDmaDataCommand (SataDevInterface, &CommandStructure, READWRITE); // Returns # of bytes read
        if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

        CurrentByteCount = CommandStructure.ByteCount;
        CurrentSectorCount = CurrentByteCount / SectorSize;

        TempBuffer += CurrentByteCount;
        Total_Number_Of_Sectors -= (CurrentSectorCount == 0 ? MaxSectorCount : CurrentSectorCount);
        LBA += (CurrentSectorCount == 0 ? MaxSectorCount : CurrentSectorCount);

    } while (Total_Number_Of_Sectors);

    return EFI_SUCCESS;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   Check48BitCommand
//
// Description: Checks if the command is for 48-bit LBA
//
// Input:
//  IN UINT8            Command
//
// Output:
//      TRUE/FLASE
//
// Modified:
//      
// Referrals: 
//
// Notes:   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
Check48BitCommand (
    IN UINT8                        Command
 )
{
    if ( Command == READ_SECTORS_EXT || 
         Command == READ_MULTIPLE_EXT || 
         Command == WRITE_SECTORS_EXT || 
         Command == WRITE_MULTIPLE_EXT ||
         Command == READ_DMA_EXT    ||
         Command == WRITE_DMA_EXT ) 
        return TRUE;
    else
        return FALSE; 
}   

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ExecuteNonDataCommand
//
// Description: Issue a  Non-Data command to the SATA Device
//
// Input:           
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,  
//  IN COMMAND_STRUCTURE                   CommandStructure
//
// Output: 
//      EFI_STATUS     
//
// Modified:
//
// Referrals: StopController, ReadytoAcceptCmd, StartController, WaitforCommandComplete
//
// Notes:   
//  1. Stop the Controller
//  2. Check if the device is ready to accept a Command. 
//  3. Build Command list
//  4. Start the Controller.
//  5. Wait till command completes. Check for errors.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ExecuteNonDataCommand (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
    IN COMMAND_STRUCTURE                   CommandStructure
)
{
    EFI_STATUS           Status;
    AHCI_BUS_PROTOCOL    *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    AHCI_COMMAND_LIST    *CommandList = (AHCI_COMMAND_LIST *)(UINTN) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE   *Commandtable = (AHCI_COMMAND_TABLE *)(UINTN)AhciBusInterface->PortCommandTableBaseAddr;

    Status = StopController(AhciBusInterface, SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(AhciBusInterface, SataDevInterface,FALSE);
        return Status;
    }

    BuildCommandList(SataDevInterface, CommandList, AhciBusInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, CommandStructure, CommandList, Commandtable);

    // Data-in
    CommandList->Ahci_Cmd_W = 0; 
       
    // Update of Command Register
    Commandtable->CFis.Ahci_CFis_C = 1;

    StartController(AhciBusInterface, SataDevInterface, BIT00);

    Status = WaitforCommandComplete(SataDevInterface, NON_DATA_CMD, ATAPI_BUSY_CLEAR_TIMEOUT );
    
    //  Stop Controller
    StopController(AhciBusInterface, SataDevInterface,FALSE);

    return Status;    

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ExecutePioDataCommand
//
// Description: Ececute PIO Data In/Out command
//
// Input:           
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,  
//  IN OUT COMMAND_STRUCTURE               *CommandStructure
//  IN BOOLEAN                             READWRITE
//
// Output:      
//         EFI_STATUS, CommandStructure->ByteCount 
//
// Modified:
//
// Referrals: StopController, ReadytoAcceptCmd, BuildCommandList, BuildCommandFIS, BuildAtapiCMD
//            BuildPRDT, StartController, WaitforCommandComplete
//  
// Notes:   
//  1. Stop the Controller
//  2. Check if the device is ready to accept a Command. 
//  3. Build Command list
//  4. Start the Controller.
//  5. Wait till command completes. Check for errors.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ExecutePioDataCommand (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
    IN OUT COMMAND_STRUCTURE               *CommandStructure,
    IN BOOLEAN                             READWRITE
)
{
    EFI_STATUS              Status;
    AHCI_BUS_PROTOCOL       *AhciBusInterface = SataDevInterface->AhciBusInterface;
    AHCI_COMMAND_LIST       *CommandList = (AHCI_COMMAND_LIST *)(UINTN) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE      *Commandtable = (AHCI_COMMAND_TABLE *)(UINTN)AhciBusInterface->PortCommandTableBaseAddr;


    Status = StopController(AhciBusInterface, SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(AhciBusInterface, SataDevInterface,FALSE);
        return Status;
    }
    BuildCommandList(SataDevInterface, CommandList, AhciBusInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildAtapiCMD(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildPRDT(SataDevInterface, *CommandStructure, CommandList, Commandtable);

    if (READWRITE) {
        CommandList->Ahci_Cmd_W = 1;        
    }
    else {
        CommandList->Ahci_Cmd_W = 0;        
    }
    Commandtable->CFis.Ahci_CFis_C = 1;

    StartController(AhciBusInterface, SataDevInterface, BIT00);

    // For Security Erase command the time out value comes from Identify Data.    
    if(CommandStructure->Command == SECURITY_ERASE_UNIT ) {
        UINT32  EraseCommandTimeout;
        EraseCommandTimeout= (UINT32)(SataDevInterface->IdentifyData.Time_security_Earse_89);
        if(EraseCommandTimeout <= 254) {
            EraseCommandTimeout=EraseCommandTimeout * 2 * 1000 * 60; //Value * 2Minitues
        } else {
            EraseCommandTimeout= 0;                                 // No timeout
        }  
        Status = WaitforCommandComplete(SataDevInterface, PIO_DATA_IN_CMD, EraseCommandTimeout);
    } else {
        Status = WaitforCommandComplete(SataDevInterface, PIO_DATA_IN_CMD, 
                    SataDevInterface->DeviceType == ATA? DMA_ATA_COMMAND_COMPLETE_TIMEOUT \
                    : DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT );
    }
    
    CommandStructure->ByteCount = CommandList->Ahci_Cmd_PRDBC;

    //  Stop Controller
    StopController(AhciBusInterface, SataDevInterface,FALSE);

    return Status;    

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ExecuteDmaDataCommand
//
// Description: 
//
// Input:           
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,  
//  IN COMMAND_STRUCTURE                   *CommandStructure
//  IN BOOLEAN                              READWRITE
//
// Output:      
//  EFI_STATUS
//
// Modified:
//      
// Referrals: StopController, ReadytoAcceptCmd, BuildCommandList, BuildCommandFIS, BuildAtapiCMD
//            BuildPRDT, StartController, WaitforCommandComplete 
//
// Notes:   
//  1. Stop the Controller
//  2. Check if the device is ready to accept a Command. 
//  3. Build Command list
//  4. Start the Controller.
//  5. Wait till command completes. Check for errors.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ExecuteDmaDataCommand (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
    IN COMMAND_STRUCTURE                   *CommandStructure,
    IN BOOLEAN                             READWRITE
)
{

    EFI_STATUS              Status;
    AHCI_BUS_PROTOCOL       *AhciBusInterface = SataDevInterface->AhciBusInterface;
    AHCI_COMMAND_LIST       *CommandList = (AHCI_COMMAND_LIST *)(UINTN) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE      *Commandtable = (AHCI_COMMAND_TABLE *)(UINTN)AhciBusInterface->PortCommandTableBaseAddr;


    Status = StopController(AhciBusInterface, SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(AhciBusInterface, SataDevInterface,FALSE);
        return Status;
    }
    BuildCommandList(SataDevInterface, CommandList, AhciBusInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildAtapiCMD(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildPRDT(SataDevInterface, *CommandStructure, CommandList, Commandtable);

    // Data-in
    if (READWRITE) {
        CommandList->Ahci_Cmd_W = 1;        
    }
    else {
        CommandList->Ahci_Cmd_W = 0  ;        
    }
    Commandtable->CFis.Ahci_CFis_C = 1;

    StartController(AhciBusInterface, SataDevInterface, BIT00);

    Status = WaitforCommandComplete(SataDevInterface, DMA_DATA_IN_CMD, 
                    SataDevInterface->DeviceType == ATA? DMA_ATA_COMMAND_COMPLETE_TIMEOUT \
                    : DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT );
    
    if (!EFI_ERROR(Status)){
        //Check if the required BYTES have been received
        if (CommandList->Ahci_Cmd_PRDBC != CommandStructure->ByteCount){
            Status = EFI_DEVICE_ERROR;
        }
    }
    //  Stop Controller
    StopController(AhciBusInterface, SataDevInterface,FALSE);

    CommandStructure->ByteCount = CommandList->Ahci_Cmd_PRDBC;

    return Status;    

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ExecutePacketCommand
//
// Description: Execute a Atapi Packet command
//
// Input:           
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,  
//  IN COMMAND_STRUCTURE                   *CommandStructure
//  IN BOOLEAN                              READWRITE
//
// Output:      
//  EFI_STATUS
//
// Modified:
//      
// Referrals: StopController, ReadytoAcceptCmd, BuildCommandList, BuildCommandFIS, BuildAtapiCMD
//            BuildPRDT, StartController, WaitforCommandComplete 
//
// Notes:   
//  1. Stop the Controller
//  2. Check if the device is ready to accept a Command. 
//  3. Build Command list
//  4. Start the Controller.
//  5. Wait till command completes. Check for errors.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS 
ExecutePacketCommand (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
    IN COMMAND_STRUCTURE                   *CommandStructure,
    IN BOOLEAN                             READWRITE
 )
{

    EFI_STATUS              Status;
    AHCI_BUS_PROTOCOL       *AhciBusInterface = SataDevInterface->AhciBusInterface;
    AHCI_COMMAND_LIST       *CommandList = (AHCI_COMMAND_LIST *)(UINTN) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE      *Commandtable = (AHCI_COMMAND_TABLE *)(UINTN)AhciBusInterface->PortCommandTableBaseAddr;
    UINT32                  AhciBaseAddr = (UINT32)AhciBusInterface->AhciBaseAddress;
    ATAPI_DEVICE            *AtapiDevice = SataDevInterface->AtapiDevice;
    UINT8                   Port = SataDevInterface->PortNumber;
    UINT8                   Data8;

    CommandStructure->LBAMid = (UINT8)(CommandStructure->ByteCount);
    CommandStructure->LBAHigh = (UINT8)(CommandStructure->ByteCount >> 8);
    CommandStructure->Command = PACKET_COMMAND;

    Status = StopController(AhciBusInterface, SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(AhciBusInterface, SataDevInterface,FALSE);
        return Status;
    }
    BuildCommandList(SataDevInterface, CommandList, AhciBusInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildAtapiCMD(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildPRDT(SataDevInterface, *CommandStructure, CommandList, Commandtable);

    if (READWRITE) {
        CommandList->Ahci_Cmd_W = 1;        
    }
    else {
        CommandList->Ahci_Cmd_W = 0;        
    }
    Commandtable->CFis.Ahci_CFis_C = 1;

    StartController(AhciBusInterface, SataDevInterface, BIT00);

    Status = WaitforCommandComplete(SataDevInterface, PIO_DATA_IN_CMD, 
                    SataDevInterface->DeviceType == ATA? DMA_ATA_COMMAND_COMPLETE_TIMEOUT \
                    : DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT );


    // Handle ATAPI device error
    if (EFI_ERROR(Status) && SataDevInterface->DeviceType == ATAPI) {
        Data8 = HBA_PORT_REG8 (AhciBaseAddr, Port, HBA_PORTS_TFD);
        if (Data8 & CHK ){
            return HandleAtapiError(SataDevInterface);
            
        }        
    }
    AtapiDevice->Atapi_Status = EFI_SUCCESS;

    CommandStructure->ByteCount = CommandList->Ahci_Cmd_PRDBC;

    //  Stop Controller
    StopController(AhciBusInterface, SataDevInterface,FALSE);

    return Status;    

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HandleAtapiError
//
// Description: Check for ATAPI Errors
//
// Input:           
//    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
//
// Output:      
//  EFI_STATUS  
//
// Modified:
//      
// Referrals: ExecutePacketCommand
//
// Notes:   
//  1. Execute ATAPI Request Sense command.
//  2. Check for Device getting ready, Media Change, No Media and other errors. Update AtapiDevice->Atapi_Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
HandleAtapiError (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface
 )
{

    EFI_STATUS              Status;
    UINT8                   Data8 = 0;
    UINT8                   SenseData[256];
    COMMAND_STRUCTURE       CommandStructure;
    ATAPI_DEVICE            *AtapiDevice = SataDevInterface->AtapiDevice;
    AHCI_BUS_PROTOCOL       *AhciBusInterface = SataDevInterface->AhciBusInterface;
    UINT32                  AhciBaseAddr = (UINT32)AhciBusInterface->AhciBaseAddress;
    UINT8                   Port = SataDevInterface->PortNumber;

    AtapiDevice->Atapi_Status = DEVICE_ERROR;

    ZeroMemory (SenseData, 256);
    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));

    CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = ATAPI_REQUEST_SENSE;
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[4] = 0xff;

    CommandStructure.ByteCount =  256;
    CommandStructure.Buffer = SenseData;

    Status = ExecutePacketCommand(SataDevInterface, &CommandStructure, 0);

    if (EFI_ERROR(Status)) {
        Data8 = HBA_PORT_REG8 (AhciBaseAddr, Port, HBA_PORTS_TFD);
    }

    SataDevInterface->AtapiSenseDataLength = 0;

    // Check for DF and CHK
    if (Data8 & (DF | CHK)) { 
        goto exit_HandleAtapiError_with_Reset;
    }    

    if (!EFI_ERROR(Status)){
        //
        // Store the SenseData whcih would be used by ScsiPassThruAtapi PassThru Interface.
        //
        pBS->CopyMem( SataDevInterface->AtapiSenseData, SenseData, 256);
        SataDevInterface->AtapiSenseDataLength = CommandStructure.ByteCount;

        AtapiDevice->Atapi_Status = DEVICE_ERROR;
        Status = EFI_DEVICE_ERROR;              // Default Value    

        if (((SenseData[2] & 0xf) == 2) && (SenseData[12] == 0x3a)) {
            Status = EFI_NO_MEDIA;
            AtapiDevice->Atapi_Status = MEDIUM_NOT_PRESENT;
        }
        if (((SenseData[2] & 0xf) == 2) && (SenseData[12] == 0x04) && (SenseData[13] == 0x01)) {
            Status = EFI_MEDIA_CHANGED;
            AtapiDevice->Atapi_Status = BECOMING_READY;
        }
    
        if (((SenseData[2] & 0xf) == 6) && (SenseData[12] == 0x28)){
                Status = EFI_MEDIA_CHANGED;
                AtapiDevice->Atapi_Status = MEDIA_CHANGED;
        }

        if (((SenseData[2] & 0xf) == 7) && (SenseData[12] == 0x27)){
                Status = EFI_WRITE_PROTECTED;
                AtapiDevice->Atapi_Status = WRITE_PROTECTED_MEDIA;
        }

        if (((SenseData[2] & 0xf) == 6) && (SenseData[12] == 0x29)){
                AtapiDevice->Atapi_Status = POWER_ON_OR_DEVICE_RESET;
        }

        if (((SenseData[2] & 0xf) == 5) && (SenseData[0] == 0x70)){
                AtapiDevice->Atapi_Status = ILLEGAL_REQUEST;
        }
    }    

exit_HandleAtapiError_with_Reset:
        return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadWritePMPort
//
// Description: Read/Write routine to PM ports
//
// Input:           
//  IN SATA_DEVICE_INTERFACE       *SataDevInterface,
//  IN UINT8                        Port,
//  IN UINT8                        RegNum,
//  IN OUT UINT32                   *Data
//  IN BOOLEAN                      READWRITE       // TRUE for Write
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: StopController, ReadytoAcceptCmd, BuildCommandList, BuildCommandFIS, BuildAtapiCMD
//            BuildPRDT, StartController, WaitforCommandComplete 
//
// Notes:   
//  1. Update Command Structure for READ/Write Port Multiplier command
//  2. Issue command
//  3. Check for errors.
//  4. Read the out data in case of READ.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ReadWritePMPort (
    IN SATA_DEVICE_INTERFACE        *SataDevInterface,
    IN UINT8                        Port,
    IN UINT8                        RegNum,
    IN OUT UINT32                   *Data,
    IN BOOLEAN                      READWRITE
)
{
    EFI_STATUS                  Status;
    COMMAND_STRUCTURE           CommandStructure;
    AHCI_RECEIVED_FIS           *PortFISBaseAddr = (AHCI_RECEIVED_FIS *)(UINTN)(SataDevInterface->PortFISBaseAddr);
    AHCI_BUS_PROTOCOL           *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    AHCI_COMMAND_LIST           *CommandList = (AHCI_COMMAND_LIST *)(UINTN) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE          *Commandtable = (AHCI_COMMAND_TABLE *)(UINTN)AhciBusInterface->PortCommandTableBaseAddr;

    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));

    CommandStructure.Command = READ_PORT_MULTIPLIER;

    if (READWRITE) {
        CommandStructure.SectorCount = (UINT16) (*Data & 0xFF);
        CommandStructure.LBALow = (UINT8) (*Data >> 8);
        CommandStructure.LBAMid = (UINT8)(*Data >> 16);
        CommandStructure.LBAHigh = (UINT8)(*Data >> 24);
        CommandStructure.Command = WRITE_PORT_MULTIPLIER;
    }

    CommandStructure.Device = Port;
    CommandStructure.Features = RegNum;

    Status = StopController(AhciBusInterface, SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(AhciBusInterface, SataDevInterface,FALSE);
        return Status;
    }

    BuildCommandList(SataDevInterface, CommandList, AhciBusInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, CommandStructure, CommandList, Commandtable);

    // Data-in
    CommandList->Ahci_Cmd_W = 0; 
       
    // Update of Command Register
    Commandtable->CFis.Ahci_CFis_C = 1;

    // Update the Port Address
    CommandList->Ahci_Cmd_PMP = CONTROL_PORT;
    Commandtable->CFis.AHci_CFis_PmPort = CONTROL_PORT; 

    StartController(AhciBusInterface, SataDevInterface, BIT00);

    Status = WaitforCommandComplete(SataDevInterface, NON_DATA_CMD, TIMEOUT_1SEC);
    
    //  Stop Controller
    StopController(AhciBusInterface, SataDevInterface,FALSE);

    if (!READWRITE) {
        *Data = 0;
        if (!EFI_ERROR(Status)) {
            *Data = PortFISBaseAddr->Ahci_Rfis[12] |    
                    (PortFISBaseAddr->Ahci_Rfis[4] << 8) |  
                    (PortFISBaseAddr->Ahci_Rfis[5] << 16) |     
                    (PortFISBaseAddr->Ahci_Rfis[6] << 24);  
        }
    }
    
    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetIdentifyData
//
// Description: Reaturn Identify data from SATA device
//
// Input:           
//    IN SATA_DEVICE_INTERFACE               *SataDevInterface,  
//
// Output:      
//      gIdentifyDataBuffer
//      EFI_STATUS
// Modified:
//      
// Referrals: 
//
// Notes:   
//  1. Build CommandStructure.
//  2. Issue ExecutePioDataCommand
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
GetIdentifyData (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface 
)
{
    EFI_STATUS                  Status;
    COMMAND_STRUCTURE           CommandStructure;
    IDENTIFY_DATA               tIdentifyData;

    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));

    //  Read Identifydata
    CommandStructure.Buffer = &tIdentifyData;
    CommandStructure.ByteCount = sizeof(IDENTIFY_DATA);
    CommandStructure.Device = 0;
    CommandStructure.Command = SataDevInterface->DeviceType == ATA ? IDENTIFY_COMMAND : IDENTIFY_PACKET_COMMAND;

    Status = ExecutePioDataCommand (SataDevInterface, &CommandStructure, FALSE);
    
    if (CommandStructure.ByteCount != sizeof(IDENTIFY_DATA)) { Status = EFI_DEVICE_ERROR; }

    if(!EFI_ERROR(Status))
        pBS->CopyMem(&(SataDevInterface->IdentifyData), &tIdentifyData, sizeof(IDENTIFY_DATA)); 

    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SataAtapiInquiryData
//
// Description: Return ATAPI Inquiry data
//
// Input:
//  IN SATA_DEVICE_INTERFACE           *SataDevInterface,
//  OUT UINT8                          *InquiryData,
//  IN OUT UINT16                      *InquiryDataSize
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: ExecutePioDataCommand
//
// Notes:   
//  1. Update CommandStructure
//  2. Issue ExecutePioDataCommand
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataAtapiInquiryData (
    IN SATA_DEVICE_INTERFACE           *SataDevInterface,
    OUT UINT8                          *InquiryData,
    IN OUT UINT16                      *InquiryDataSize
)
{

    EFI_STATUS          Status;
    COMMAND_STRUCTURE   CommandStructure;
    
    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer = InquiryData;
    CommandStructure.ByteCount = *InquiryDataSize;
    CommandStructure.Command = PACKET_COMMAND;
    CommandStructure.LBAMid = (UINT8)*InquiryDataSize;
    CommandStructure.LBAHigh = (UINT8)(*InquiryDataSize >> 8);

    CommandStructure.AtapiCmd.Ahci_Atapi_Command[0]=ATAPI_INQUIRY;
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[4]=(UINT8)*InquiryDataSize;

    Status = ExecutePioDataCommand (SataDevInterface, &CommandStructure, 0); 

    if (!EFI_ERROR(Status)) {
        *InquiryDataSize = (UINT16)CommandStructure.ByteCount;
    }

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   DetectAtapiMedia
//
// Description: Detects whether a Media is present in the ATAPI Removable device or not.
//
// Input:
//  IN SATA_DEVICE_INTERFACE           *SataDevInterface,
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: TestUnitReady, ExecutePacketCommand 
//
// Notes:   
//  1. Issue Read Capacity command for CDROM or Read Format command for other ATAPI devices.
//  2. If step 1  is successfull, update last LBA, Block Size, Read/Write capable, Media ID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
DetectAtapiMedia(
    IN SATA_DEVICE_INTERFACE           *SataDevInterface
 )
{
    UINT8               *InputData, LoopCount;
    ATAPI_DEVICE        *AtapiDevice = SataDevInterface->AtapiDevice;
    EFI_BLOCK_IO_MEDIA  *BlkMedia = SataDevInterface->SataBlkIo->BlkIo.Media;
    EFI_STATUS          Status = EFI_NOT_FOUND;
    UINT16              ByteCount = 256, Data16;
    COMMAND_STRUCTURE   CommandStructure;
    BOOLEAN             ReadCapacity=FALSE;
    
    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));

//  Default Values
    BlkMedia->MediaPresent = FALSE;
    BlkMedia->LastBlock = 0x100;                            // Dummy value
    SataDevInterface->ReadCommand = ATAPI_READ_10;  
    SataDevInterface->WriteCommand = ATAPI_WRITE_10;

    Status = TestUnitReady(SataDevInterface);
    if ((Status != EFI_MEDIA_CHANGED) && (Status != EFI_SUCCESS)) {
        return Status;
    }

//  Issue Read Capacity command
    Status = pBS->AllocatePool (EfiBootServicesData, ByteCount, (VOID**)&InputData);
    if (EFI_ERROR(Status)) return Status;

//  For CDROM use Read Capacity command else use Read Format Command
    if (AtapiDevice->DeviceType == CDROM_DEVICE){
        BlkMedia->BlockSize = CDROM_BLOCK_SIZE;         // Default size
        AtapiDevice->BlockSize = (UINT16)(BlkMedia->BlockSize);
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = ATAPI_READ_CAPACITY;
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[1] = AtapiDevice->Lun << 5;
        Data16 = 8;
    }
    else {
        BlkMedia->BlockSize = LS120_BLOCK_SIZE;         // Default Size
        AtapiDevice->BlockSize = (UINT16)(BlkMedia->BlockSize);
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = ATAPI_READ_FORMAT_CAPACITIES;
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[1] = AtapiDevice->Lun << 5;
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[7] = (UINT8)(ByteCount >> 8);
        CommandStructure.AtapiCmd.Ahci_Atapi_Command[8] = (UINT8)(ByteCount & 0xff);
        Data16 = ByteCount;
    }

    for (LoopCount  = 0; LoopCount < 5; LoopCount++) {          // 5sec loop
        ByteCount = Data16;
        ZeroMemory (InputData, ByteCount);
        CommandStructure.Buffer  = InputData;
        CommandStructure.ByteCount = ByteCount;
        Status = ExecutePacketCommand(SataDevInterface, &CommandStructure, 0);
        if(CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] == ATAPI_READ_FORMAT_CAPACITIES && 
            AtapiDevice->Atapi_Status == ILLEGAL_REQUEST) {
            //
            //If the Read Format Capacities not supported by device, try 
            //ReadCapacity command
            //
            ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));
            BlkMedia->BlockSize = CDROM_BLOCK_SIZE;         // Default size
            AtapiDevice->BlockSize = (UINT16)(BlkMedia->BlockSize);
            CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = ATAPI_READ_CAPACITY;
            CommandStructure.AtapiCmd.Ahci_Atapi_Command[1] = AtapiDevice->Lun << 5;
            Data16 = 8;
            ReadCapacity=TRUE;
        }
        if (AtapiDevice->Atapi_Status == EFI_SUCCESS) break;
        if (AtapiDevice->Atapi_Status == MEDIUM_NOT_PRESENT) break;
    } 

    if (Status == EFI_SUCCESS) {
        if(ReadCapacity == TRUE) {
            BlkMedia->LastBlock = InputData[0] << 24 | InputData[1] << 16 | InputData[2] << 8 | InputData[3];
            BlkMedia->LastBlock--; 
            BlkMedia->MediaPresent = TRUE;
            BlkMedia->MediaId ++;
            BlkMedia->BlockSize = InputData[4] << 24 | InputData[5] << 16 | InputData[6] << 8 | InputData[7];
            AtapiDevice->BlockSize = BlkMedia->BlockSize;
            BlkMedia->ReadOnly = FALSE;
        } else if (AtapiDevice->DeviceType == CDROM_DEVICE) {
            BlkMedia->LastBlock = InputData[0] << 24 | InputData[1] << 16 | InputData[2] << 8 | InputData[3];
            BlkMedia->LastBlock--;
            BlkMedia->BlockSize = CDROM_BLOCK_SIZE;
            AtapiDevice->BlockSize = (UINT16)(BlkMedia->BlockSize);
            BlkMedia->MediaPresent = TRUE;
            BlkMedia->MediaId ++;
            BlkMedia->ReadOnly = TRUE;
        } else if (InputData[8] != 3) {         // No media present
            BlkMedia->LastBlock = InputData[4] << 24 | InputData[5] << 16 | InputData[6] << 8 | InputData[7];
            BlkMedia->LastBlock--; 
            BlkMedia->MediaPresent = TRUE;
            BlkMedia->MediaId ++;
            BlkMedia->BlockSize = InputData[9] << 16 | InputData[10] << 8 | InputData[11];
            BlkMedia->ReadOnly = FALSE;
            AtapiDevice->BlockSize = (UINT16)(BlkMedia->BlockSize);
        }

//      Update ReadOnly Status
        if (AtapiDevice->DeviceType != CDROM_DEVICE) {
            ByteCount = 256;
            ZeroMemory (InputData, ByteCount);
            ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));
            CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = ATAPI_MODE_SENSE;
            CommandStructure.AtapiCmd.Ahci_Atapi_Command[2] = RETURN_ALL_PAGES;
            CommandStructure.AtapiCmd.Ahci_Atapi_Command[7] = (UINT8)(ByteCount >> 8);
            CommandStructure.AtapiCmd.Ahci_Atapi_Command[8] = (UINT8)(ByteCount & 0xff);
            CommandStructure.Buffer  = InputData;
            CommandStructure.ByteCount= ByteCount;
            Status = ExecutePacketCommand(SataDevInterface, &CommandStructure, 0);
            if ((Status == EFI_SUCCESS) && (ByteCount > 8)) {
                BlkMedia->ReadOnly = (InputData[3] & 0x80) != 0 ? TRUE : FALSE;
            }
        }
    }

    pBS->FreePool(InputData);
    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SataCheckOddType
//
// Description: Return ODD type
//
// Input:
//  IN SATA_DEVICE_INTERFACE           *SataDevInterface,
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: ExecutePioDataCommand
//
// Notes:   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataGetOddType (
    IN SATA_DEVICE_INTERFACE           *SataDevInterface,
    IN OUT UINT16                      *OddType
)

{

    EFI_STATUS          Status;
    COMMAND_STRUCTURE   CommandStructure;
    UINT8               *ProfileData;    

    Status = pBS->AllocatePool (EfiBootServicesData,16,(VOID**)&ProfileData);

    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer = ProfileData;
    CommandStructure.ByteCount = 16;
    CommandStructure.Command = PACKET_COMMAND;
    CommandStructure.LBAMid = 16;
    CommandStructure.LBAHigh = 0;

    CommandStructure.AtapiCmd.Ahci_Atapi_Command[0]= ATAPI_GET_CONFIGURATION;
    //
    // Get the Feature Discriptor.
    //
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[1] = FEATURE_DISCRIPTOR;
    //
    // Get the Profile list
    //
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[3] = GET_PROFILE_LIST;
    //
    // Responce Data Size
    //
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[8] = 0x10;

    Status = ExecutePioDataCommand (SataDevInterface, &CommandStructure, 0); 

    if (!EFI_ERROR(Status)) {
        //
        // Get the Profile Number
        //
        *OddType=(UINT16 )(((ProfileData[sizeof(GET_CONFIGURATION_HEADER)+4]) << 8) + ProfileData[sizeof(GET_CONFIGURATION_HEADER)+5]);
    }
   
    pBS->FreePool(ProfileData);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SataGetOddLoadingType
//
// Description: Return ODD Loading type information
//
// Input:
//  IN SATA_DEVICE_INTERFACE           *SataDevInterface,
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: ExecutePioDataCommand
//
// Notes:   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SataGetOddLoadingType (
    IN SATA_DEVICE_INTERFACE           *SataDevInterface,
    IN OUT UINT8                       *OddLoadingType
)

{

    EFI_STATUS          Status;
    COMMAND_STRUCTURE   CommandStructure;
    UINT8               *ProfileData;    

    Status = pBS->AllocatePool (EfiBootServicesData,16,(VOID**)&ProfileData);

    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Buffer = ProfileData;
    CommandStructure.ByteCount = 16;
    CommandStructure.Command = PACKET_COMMAND;
    CommandStructure.LBAMid = 16;
    CommandStructure.LBAHigh = 0;

    CommandStructure.AtapiCmd.Ahci_Atapi_Command[0]= ATAPI_GET_CONFIGURATION;
    //
    // Get the Feature Discriptor.
    //
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[1] = FEATURE_DISCRIPTOR;
    //
    // Get the Removable Medium feature
    //
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[3] = GET_REMOVEABLE_MEDIUM_FEATURE;
    //
    // Responce Data Size
    //
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[8] = 0x10;

    Status = ExecutePioDataCommand (SataDevInterface, &CommandStructure, 0); 

    if (!EFI_ERROR(Status)) {
        //
        // Get the ODD Loading Type
        //
        *OddLoadingType=(UINT8 )(((ProfileData[sizeof(GET_CONFIGURATION_HEADER)+4]) & 0xE0) >> 5);
    }
   
    pBS->FreePool(ProfileData);
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   TestUnitReady
//
// Description: Issues Start/Stop unit Command
//
// Input:
//  IN SATA_DEVICE_INTERFACE           *SataDevInterface
//
// Output:
//      EFI_STATUS          EFI_SUCCESS           : If Media is accessible
//                          EFI_NO_MEDIA
//                          EFI_MEDIA_CHANGED
//                          EFI_DEVICE_ERROR
//
// Modified:
//      
// Referrals: ExecutePacketCommand
//
// Notes:   
//  1. Update CommandStructure for ATAPI_TEST_UNIT_READY command
//  2. Issue ExecutePacketCommand
//  3. Check if the device is ready to accept command, whether Media is present or not.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
TestUnitReady(
    IN SATA_DEVICE_INTERFACE           *SataDevInterface
 )
{

    EFI_STATUS                      Status = EFI_SUCCESS;
    ATAPI_DEVICE                    *AtapiDevice = SataDevInterface->AtapiDevice;
    UINT16                          LoopCount;
    COMMAND_STRUCTURE               CommandStructure;
    
    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = ATAPI_TEST_UNIT_READY;
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[1] = AtapiDevice->Lun << 5;
    CommandStructure.Buffer  = NULL;
    CommandStructure.ByteCount  =  0x100;

    for (LoopCount  = 0; LoopCount < 1000; LoopCount++) {           // 10sec loop ( 1000 * 10 msec = 10Sec)
        Status = ExecutePacketCommand(SataDevInterface, &CommandStructure, 0);
        if (Status == EFI_SUCCESS) break;
        if (AtapiDevice->Atapi_Status == MEDIUM_NOT_PRESENT) break;
        if (AtapiDevice->Atapi_Status == MEDIA_CHANGED) break;
        pBS->Stall(10000); // 10msec
    } 

    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildCommandList
//
// Description: Builds command list
//
// Input:           
//  IN SATA_DEVICE_INTERFACE            *SataDevInterface,  
//  IN AHCI_COMMAND_LIST                *CommandList,
//  IN UINT32                           CommandTableBaseAddr
//
// Output:      
//  EFI_STATUS
//  
// Modified:
//      
// Referrals: 
//
// Notes:   
//  1. Update CommandList bits
//  2. Not all fields like Ahci_Cmd_A are updated.
//  3. Port number is set to 0xF (Control port) if PM Port number is 0xFF.  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
BuildCommandList (
    IN SATA_DEVICE_INTERFACE            *SataDevInterface, 
    IN AHCI_COMMAND_LIST                *CommandList,
    IN UINT32                           CommandTableBaseAddr
)
{

 
    ZeroMemory (CommandList, sizeof(AHCI_COMMAND_LIST));
    // CommandList->Ahci_Cmd_A = SataDevInterface->DeviceType == ATAPI ? 1 : 0;      // set elsewhere 
    CommandList->Ahci_Cmd_P = 0;       
    CommandList->Ahci_Cmd_R = 0;       
    CommandList->Ahci_Cmd_B = 0;       
    CommandList->Ahci_Cmd_Rsvd1 = 0;       
    CommandList->Ahci_Cmd_PMP = SataDevInterface->PMPortNumber == 0xFF ? 0x0 : SataDevInterface->PMPortNumber;       
    CommandList->Ahci_Cmd_PRDTL = 0;       
    CommandList->Ahci_Cmd_PRDBC = 0;       
    CommandList->Ahci_Cmd_CTBA = CommandTableBaseAddr;       
    CommandList->Ahci_Cmd_CTBAU = 0;

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildCommandFIS
//
// Description: Build Command FIS
//
// Input:           
//  IN SATA_DEVICE_INTERFACE                *SataDevInterface,  
//  IN COMMAND_STRUCTURE                    CommandStructure,
//  IN AHCI_COMMAND_LIST                    *CommandList,
//  IN AHCI_COMMAND_TABLE                   *Commandtable
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:   
//  1. Update Command FIS data area.
//  2. Update the Command FIS lenght in Command List table  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
BuildCommandFIS (
    IN SATA_DEVICE_INTERFACE                *SataDevInterface, 
    IN COMMAND_STRUCTURE                    CommandStructure,
    IN AHCI_COMMAND_LIST                    *CommandList,
    IN AHCI_COMMAND_TABLE                   *Commandtable
)
{


    ZeroMemory (Commandtable, sizeof(AHCI_COMMAND_TABLE));

    Commandtable->CFis.Ahci_CFis_Type = FIS_REGISTER_H2D;
    Commandtable->CFis.AHci_CFis_PmPort = SataDevInterface->PMPortNumber == 0xFF ? 0x0 : SataDevInterface->PMPortNumber;
//  Commandtable->CFis.Ahci_CFis_C = 1;          // Set elsewhere
    Commandtable->CFis.Ahci_CFis_Cmd = CommandStructure.Command;

    Commandtable->CFis.Ahci_CFis_Features = CommandStructure.Features;
    Commandtable->CFis.Ahci_CFis_FeaturesExp = CommandStructure.FeaturesExp;

    Commandtable->CFis.Ahci_CFis_SecNum = CommandStructure.LBALow;
    Commandtable->CFis.Ahci_CFis_SecNumExp = CommandStructure.LBALowExp;

    Commandtable->CFis.Ahci_CFis_ClyLow = CommandStructure.LBAMid;
    Commandtable->CFis.Ahci_CFis_ClyLowExp = CommandStructure.LBAMidExp;

    Commandtable->CFis.Ahci_CFis_ClyHigh = CommandStructure.LBAHigh;
    Commandtable->CFis.Ahci_CFis_ClyHighExp = CommandStructure.LBAHighExp;

    Commandtable->CFis.Ahci_CFis_SecCount = (UINT8)(CommandStructure.SectorCount);
    Commandtable->CFis.Ahci_CFis_SecCountExp = (UINT8)(CommandStructure.SectorCount >> 8);

    Commandtable->CFis.Ahci_CFis_DevHead = CommandStructure.Device;
    Commandtable->CFis.Ahci_CFis_Control = CommandStructure.Control;    

    CommandList->Ahci_Cmd_CFL = FIS_REGISTER_H2D_LENGTH / 4;

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildAtapiCMD
//
// Description: 
//
// Input:           
//  IN SATA_DEVICE_INTERFACE                *SataDevInterface,  
//  IN COMMAND_STRUCTURE                    CommandStructure
//  IN AHCI_COMMAND_LIST                    *CommandList,
//  IN AHCI_COMMAND_TABLE                   *Commandtable
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Copy Packet data to command table
//  2. Set Atapi bit in Command List    
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
BuildAtapiCMD(
    IN SATA_DEVICE_INTERFACE                *SataDevInterface, 
    IN COMMAND_STRUCTURE                    CommandStructure,
    IN AHCI_COMMAND_LIST                    *CommandList,
    IN AHCI_COMMAND_TABLE                   *Commandtable
)
{


    pBS->CopyMem(&(Commandtable->AtapiCmd),&(CommandStructure.AtapiCmd),sizeof(AHCI_ATAPI_COMMAND));

    if (Commandtable->CFis.Ahci_CFis_Cmd == PACKET_COMMAND){ // Is it a packet command?         
        CommandList->Ahci_Cmd_A = 1;
    }

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildPRDT
//
// Description: Build PRDT table
//
// Input:           
//  IN SATA_DEVICE_INTERFACE                *SataDevInterface,  
//  IN COMMAND_STRUCTURE                    CommandStructure
//  IN AHCI_COMMAND_LIST                    *CommandList,
//  IN AHCI_COMMAND_TABLE                   *Commandtable
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Build as many PRDT table entries based on ByteCount.
//  2. Set the I flag for the lasr PRDT table.
//  3. Update PRDT table lenght in CommandList
//  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
BuildPRDT (
    IN SATA_DEVICE_INTERFACE                *SataDevInterface, 
    IN COMMAND_STRUCTURE                    CommandStructure,
    IN AHCI_COMMAND_LIST                    *CommandList,
    IN AHCI_COMMAND_TABLE                   *Commandtable
)
{

    AHCI_BUS_PROTOCOL       *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    UINT32                  ByteCount = CommandStructure.ByteCount;
    UINT16                  Prdtlength = 0;
    AHCI_COMMAND_PRDT       *PrdtTable = &(Commandtable->PrdtTable);

    for (;ByteCount; (UINT8 *)PrdtTable += sizeof(AHCI_COMMAND_PRDT)){
        PrdtTable->Ahci_Prdt_DBA = (UINT32)(UINTN)CommandStructure.Buffer;
        PrdtTable->Ahci_Prdt_DBAU = (UINT32)Shr64((UINTN)CommandStructure.Buffer, 32);
        PrdtTable->Ahci_Prdt_DBC = ByteCount >= PRD_MAX_DATA_COUNT ? (PRD_MAX_DATA_COUNT - 1) : (ByteCount - 1);
        ByteCount -= (PrdtTable->Ahci_Prdt_DBC + 1);
        PrdtTable->Ahci_Prdt_I = 0;
        Prdtlength+= sizeof(AHCI_COMMAND_PRDT);
        if ((UINT32)(Prdtlength + 0x80) >= AhciBusInterface->PortCommandTableLength) {
            //ASSERT_EFI_ERROR(EFI_OUT_OF_RESOURCES);
            break;
        }
        (UINT8 *)CommandStructure.Buffer += PrdtTable->Ahci_Prdt_DBC + 1;
    }
    //  Set I flag only for the last entry.
    (UINT8 *)PrdtTable -= sizeof(AHCI_COMMAND_PRDT);
    PrdtTable->Ahci_Prdt_I = 1;
    CommandList->Ahci_Cmd_PRDTL = Prdtlength / sizeof(AHCI_COMMAND_PRDT);

    return EFI_SUCCESS;

}

 
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StartController
//
// Description: 
//
// Input:           
//    IN AHCI_BUS_PROTOCOL                  *AhciBusInterface,
//    IN SATA_DEVICE_INTERFACE              *SataDevInterface,
//    IN UINT32                             CIBitMask
//
// Output:      
//  EFI_STATUS
// Modified:
//
// Referrals: 
//
// Notes:   
//  1. Clear Status register
//  2. Enable FIS and CR running bit
//  3. Enable Start bit
//  4. Update CI bit mask
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
StartController (
    IN AHCI_BUS_PROTOCOL                    *AhciBusInterface, 
    IN SATA_DEVICE_INTERFACE                *SataDevInterface,
    IN UINT32                               CIBitMask
)
{

    UINT32      AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    UINT8       Port = SataDevInterface->PortNumber;

    // Clear Status
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    // Enable FIS Receive
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_FRE);     

    // Wait till FIS is running
    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_FR,
                                    HBA_PORTS_CMD_FR,
                                    HBA_FR_CLEAR_TIMEOUT);

    // Clear FIS Receive area
    ZeroMemory ((VOID *)(UINTN)SataDevInterface->PortFISBaseAddr, RECEIVED_FIS_SIZE);

    // Enable ST
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_ST);

    // Enable Command Issued
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CI, CIBitMask);

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WaitforCommandComplete
//
// Description: Wait till cmd completes
//
// Input:           
//    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
//    IN COMMAND_TYPE                        CommandType,
//    IN UINTN                               TimeOut
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Check for SError bits. If set return error.
//  2. For PIO IN/Out and Packet IN/OUT command wait till PIO Setup FIS is received
//  3. If D2H register FIS is received, exit the loop.
//  4. Check for SError and TFD bits.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
WaitforCommandComplete  (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
    IN COMMAND_TYPE                        CommandType,
    IN UINTN                               TimeOut    
)
{

    AHCI_BUS_PROTOCOL  *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    UINT32      AhciBaseAddr = (UINT32)AhciBusInterface->AhciBaseAddress;
    UINT8       Port = SataDevInterface->PortNumber;
    UINT32      Data32_SERR, Data32_IS, i;
    BOOLEAN     PxSERR_ERROR = FALSE, PIO_SETUP_FIS = FALSE;
    volatile AHCI_RECEIVED_FIS   *FISReceiveAddress = (AHCI_RECEIVED_FIS *)(UINTN)SataDevInterface->PortFISBaseAddr;
    UINTN       TimeOutCount = TimeOut;

    i=0;
    do {
        pBS->Stall(500);

        //  Check for Error bits
        Data32_SERR = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_SERR);
        if (Data32_SERR & HBA_PORTS_ERR_CHK) {
            PxSERR_ERROR = TRUE;
            break;
        }

        //  Check for Error bits
        Data32_IS = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_IS);
        if (Data32_IS & HBA_PORTS_IS_ERR_CHK) {
            PxSERR_ERROR = TRUE;
            break;
        }
        
        switch (CommandType) {

            case PIO_DATA_IN_CMD:
            case PIO_DATA_OUT_CMD:
            case PACKET_PIO_DATA_IN_CMD:
            case PACKET_PIO_DATA_OUT_CMD:
                // check if PIO setup received
                if(FISReceiveAddress->Ahci_Psfis[0] == FIS_PIO_SETUP) {
                    FISReceiveAddress->Ahci_Psfis[0] = 0;
                    TimeOutCount = TimeOut;
                    PIO_SETUP_FIS = TRUE;                         
                }
                break;
            default: 
                break;
            
        }

        // check if D2H register FIS is received
        if(FISReceiveAddress->Ahci_Rfis[0] == FIS_REGISTER_D2H) break;

        // For PIO Data in D2H register FIS is not received. So rely on BSY bit
        if ((CommandType == PIO_DATA_IN_CMD) &&  PIO_SETUP_FIS &&
                    !((HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_TFD) & 
                    (HBA_PORTS_TFD_BSY | HBA_PORTS_TFD_DRQ)))){
            break;
        }
        //If the Timeout is 0, Then there is no timeout for command processing  
        if(TimeOut==0) {
            continue;
        }
        i++;
    } while(i < TimeOutCount * 2);

    if (PxSERR_ERROR) {
        // clear the status and return error
        HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
        HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR);         
        return EFI_DEVICE_ERROR;    
    }    

    // check if CI register is zero
    if (HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_CI)){
        return EFI_DEVICE_ERROR;                
    }

    // check for status bits
    if (HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_TFD) & (HBA_PORTS_TFD_ERR | HBA_PORTS_TFD_DRQ)){
        return EFI_DEVICE_ERROR;                
    }

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StopController
//
// Description: Stop FIS and CR
//
// Input:           
//    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//    IN SATA_DEVICE_INTERFACE               *SataDevInterface
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: GeneratePortReset
//
// Notes:
//  1. clear ST bit and wait till CR bits gets reset
//  2. if not generate Port reset
//  3. Clear FIS running bit.
//  4. Clear status register
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
StopController(
    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
    IN BOOLEAN                              StartOrStop
) 
{

    UINT8       Port = SataDevInterface->PortNumber;
    UINT8       PMPort = SataDevInterface->PMPortNumber;
    UINT32      AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    EFI_STATUS  Status;
    UINT32      PortFISBaseAddr = SataDevInterface->PortFISBaseAddr;
    UINT32      CommandListBaseAddress = SataDevInterface->PortCommandListBaseAddr;
    UINT32      Data32;

    if(StartOrStop && (HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_CLB) != CommandListBaseAddress)) {
        gCommandListBaseAddress=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_CLB);
        gFisBaseAddress=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_FB);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLB,CommandListBaseAddress);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FB,PortFISBaseAddr);
        
        //
        // Saving the Upper 32 bits of FIS and Command List Registers
        //
        gCommandListBaseAddress2=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_CLBU);
        gFisBaseAddress2=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_FBU);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLBU,0);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FBU,0);
    }

    // Clear Start
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~(HBA_PORTS_CMD_ST));
    // Make sure CR is 0 with in 500msec
    Status = WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_CR,
                            HBA_CR_CLEAR_TIMEOUT);

    if (EFI_ERROR(Status)) { 

        // Get the Port Speed allowed and Interface Power Management Transitions Allowed
        // Pass the values for PortReset. 
        Data32 = HBA_PORT_REG32 ((UINT32)(AhciBusInterface->AhciBaseAddress), Port, HBA_PORTS_SCTL);
        Data32 &= 0xFF0;          

        Status = GeneratePortReset(AhciBusInterface, SataDevInterface, Port, PMPort,
                                    (UINT8)((Data32 & 0xF0) >> 4), (UINT8)(Data32 >> 8));
    };

    if (EFI_ERROR(Status)) {
        goto StopController_ErrorExit;
    }

    //  Clear FIS receive enable.
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, 
                                    HBA_PORTS_CMD, ~(HBA_PORTS_CMD_FRE));
    //  Make sure FR is 0 with in 500msec
    Status = WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_FR,
                            HBA_FR_CLEAR_TIMEOUT);


StopController_ErrorExit:

    // Clear Status register
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    if(!StartOrStop  && gCommandListBaseAddress) {
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLB,gCommandListBaseAddress);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FB,gFisBaseAddress);
        //
        // Restoring the Upper 32 bits of FIS and Command List Registers
        //
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLBU,gCommandListBaseAddress2);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FBU,gFisBaseAddress2);

        gCommandListBaseAddress = 0;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadytoAcceptCmd
//
// Description: Check if the device is ready to accept cmd.
//
// Input:           
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,
//
// Output:
//  EFI_STATUS      
//
// Modified:
//      
// Referrals: GeneratePortReset, ReadWritePMPort
//
// Notes:
//  1. Check the device is ready to accept the command. BSY and DRQ should be de-asserted.  
//  2. If set, generate Port reset
//  3. In case Port Multiplier is connected to the port, enable all the ports of the Port Multiplier.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ReadytoAcceptCmd (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface
)
{

    EFI_STATUS              Status = EFI_SUCCESS;
    AHCI_BUS_PROTOCOL       *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    UINT32                  AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    UINT8                   Port = SataDevInterface->PortNumber;
    UINT8                   PMPort = SataDevInterface->PMPortNumber;
    SATA_DEVICE_INTERFACE   *SataPMDevInterface, *SataPMPortDevInterface;
    UINT32                  Data32 = 0, Init_SStatus = 0;
    UINT8                   PowerManagement, Speed;

    // Is the Device ready to accept the command
    if (HBA_PORT_REG8 (AhciBaseAddr, Port, HBA_PORTS_TFD) & (HBA_PORTS_TFD_BSY | HBA_PORTS_TFD_DRQ)){
        Data32 = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_SCTL);
        Data32 &= 0xFF0;          
        // make sure the status we read is for the right port
        Status = GeneratePortReset(AhciBusInterface, SataDevInterface, Port, 0xFF,
                          (UINT8)((Data32 & 0xF0) >> 4), (UINT8)(Data32 >> 8));
        if (EFI_ERROR(Status)) return Status;

        // If it is a PMPort, Make sure all the Ports are in enabled state.
        SataPMDevInterface = GetSataDevInterface(AhciBusInterface, Port, 0xFF);
        if (!SataPMDevInterface) { 
            return EFI_DEVICE_ERROR;
        }
        if (SataPMDevInterface->DeviceType == PMPORT) {
            for (PMPort = 0; PMPort < SataPMDevInterface->NumPMPorts; PMPort++){
                SataPMPortDevInterface = GetSataDevInterface(AhciBusInterface, Port, PMPort);
                if (!SataPMPortDevInterface) continue;
                    ReadWritePMPort (SataDevInterface, PMPort, PSCR_0_SSTATUS, &Init_SStatus, FALSE);
                    if ((Init_SStatus & HBA_PORTS_SSTS_DET_MASK) == HBA_PORTS_SSTS_DET_PCE) { 
                        Data32 = SataPMPortDevInterface->SControl;
                        ReadWritePMPort (SataDevInterface, PMPort, PSCR_2_SCONTROL, &Data32, TRUE);
                    }
                    else {
                        Speed = (UINT8)((SataDevInterface->SControl >> 4) & 0xF);
                        PowerManagement = (UINT8)((SataDevInterface->SControl >> 8) & 0xF);
                        GeneratePortReset(AhciBusInterface, SataDevInterface, Port, PMPort, 
                                            Speed, PowerManagement);
                    }
                    Data32 = HBA_PORTS_ERR_CLEAR;
                    ReadWritePMPort (SataDevInterface, PMPort, PSCR_1_SERROR, &Data32, TRUE);
                }
        }
    } 
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HostReset
//
// Description: 
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//
// Output:      
//
// Modified:
//      
//
// Referrals: 
//
// Notes:   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
HostReset (
    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface 
)
{

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GeneratePortReset
//
// Description: Issue a Port Reset
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
//  IN UINT8                               CurrentPort, 
//  IN UINT8                               Speed,
//  IN UINT8                               PowerManagement
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadWritePMPort, HandlePortComReset
//
// Notes:   
//  1. Issue port reset by setting DET bit in SControl register
//  2. Call HandlePortComReset to check the status of the reset.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
GeneratePortReset (
    AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    UINT8                               Port,
    UINT8                               PMPort,
    UINT8                               Speed,
    UINT8                               PowerManagement
)
{

    EFI_STATUS  Status;
    UINT32      AhciBaseAddr = (UINT32) AhciBusInterface->AhciBaseAddress;
    volatile    AHCI_RECEIVED_FIS  *FISAddress =  (AHCI_RECEIVED_FIS *)HBA_PORT_REG32(AhciBaseAddr, Port, HBA_PORTS_FB);
    UINT32      Data32;

    TRACE_AHCI_LEVEL2((-1,"AHCI: PortReset on Port : %x PMPort : %x", Port, PMPort));

    if (!FISAddress) return EFI_DEVICE_ERROR;   // FIS receive address is not programmed.

    if (gPortReset) return EFI_SUCCESS;
    gPortReset = TRUE;

    // Disable Start bit
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~HBA_PORTS_CMD_ST);

    // Wait till CR is cleared    
    Status = WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_CR,
                            HBA_CR_CLEAR_TIMEOUT);

    // Clear Status register
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
    if (PMPort != 0xFF) {
        Data32 = HBA_PORTS_ERR_CLEAR;
        ReadWritePMPort (SataDevInterface, PMPort, PSCR_1_SERROR, &Data32, TRUE);
    }
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 
    
    //  Enable FIS Receive Enable
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_FRE);     

    // Wait till FIS is running and then clear the data area
    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_FR,
                                    HBA_PORTS_CMD_FR,
                                    HBA_FR_CLEAR_TIMEOUT);

        
    FISAddress->Ahci_Rfis[0] = 0;

    if (PMPort == 0xFF) {
        // Issue Port COMRESET
       HBA_PORT_REG32_AND_OR (AhciBaseAddr, Port, HBA_PORTS_SCTL, 0xFFFFF000, 
                    HBA_PORTS_SCTL_DET_INIT + (Speed << 4) + (PowerManagement << 8));     
        pBS->Stall (1000);                               // 1msec
        HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_SCTL, ~HBA_PORTS_SCTL_DET_MASK);
    }
    else {
        Data32 = HBA_PORTS_SCTL_DET_INIT + (Speed << 4) + (PowerManagement << 8);
        ReadWritePMPort (SataDevInterface, PMPort, PSCR_2_SCONTROL, &Data32, TRUE);
        pBS->Stall (1000);                               // 1msec
        Data32 = (Speed << 4) + (PowerManagement << 8);
        ReadWritePMPort (SataDevInterface, PMPort, PSCR_2_SCONTROL, &Data32, TRUE);
    }
    
    Status = HandlePortComReset(AhciBusInterface, SataDevInterface, Port, PMPort);

    //  Disable FIS Receive Enable
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~HBA_PORTS_CMD_FRE);

    SataDevInterface->SControl = (Speed << 4) + (PowerManagement << 8);

    gPortReset = FALSE;     

    if (EFI_ERROR(Status)) {
        TRACE_AHCI_LEVEL2((-1," Status : %r\n", Status));
        return EFI_DEVICE_ERROR;
    }

    TRACE_AHCI_LEVEL2((-1," Status : %r\n", Status));
    return EFI_SUCCESS;    

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GenerateSoftReset
//
// Description: Generate Soft Reset
//
// Input:           
//  IN SATA_DEVICE_INTERFACE                *SataDevInterface,
//  In UINT8                                PMPort
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: StopController, ReadytoAcceptCmd, BuildCommandList, BuildCommandFIS, StartController
//
// Notes:   
//  1. Issue a Control register update, H2D register FIS with reset bit set.
//  2. Wait for 100usec
//  3. Issue a Control register update, H2D register FIS with reset bit reset.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
GenerateSoftReset (
    IN SATA_DEVICE_INTERFACE                *SataDevInterface,
    IN UINT8                                PMPort

)
{

    EFI_STATUS           Status;
    AHCI_BUS_PROTOCOL    *AhciBusInterface = SataDevInterface->AhciBusInterface; 
    UINT32               AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    AHCI_COMMAND_LIST    *CommandList = (AHCI_COMMAND_LIST *)(UINTN) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE   *Commandtable = (AHCI_COMMAND_TABLE *)(UINTN)AhciBusInterface->PortCommandTableBaseAddr;
    COMMAND_STRUCTURE     CommandStructure;
    UINT32                Data32;
    UINT8                 Port = SataDevInterface->PortNumber;

    TRACE_AHCI_LEVEL2((-1,"AHCI: SoftReset on Port : %x PMPort : %x", Port, PMPort));

    PROGRESS_CODE(DXE_IDE_RESET);

    if (gSoftReset) return EFI_SUCCESS;
    
    gSoftReset = TRUE;

    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));

    Status = StopController(AhciBusInterface, SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) {
        goto GenerateSoftReset_Exit;
    }


    // if Command list Override is supported, set CLO bit
    Data32 = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_TFD) & (HBA_PORTS_TFD_DRQ | HBA_PORTS_TFD_BSY);
    if ((AhciBusInterface->HBACapability & HBA_CAP_SCLO) && Data32){
        HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_CLO);
        Status = WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_CLO,
                            BUSY_CLEAR_TIMEOUT);
    }

    CommandStructure.Control = 4;
    BuildCommandList(SataDevInterface, CommandList, (UINT32)(UINTN)Commandtable);
    BuildCommandFIS(SataDevInterface, CommandStructure, CommandList, Commandtable);

    CommandList->Ahci_Cmd_W = 0; 
    // Update of Control Register
    Commandtable->CFis.Ahci_CFis_C = 0;
    CommandList->Ahci_Cmd_R = 1;
    CommandList->Ahci_Cmd_C= 1;

    if (PMPort != 0xFF) Commandtable->CFis.AHci_CFis_PmPort = PMPort;

    StartController(AhciBusInterface, SataDevInterface, BIT00);
    // Wait till command is processed
    Status = WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CI,
                            BIT00,
                            ONE_MILLISECOND * 5);

    // Is the command complete?
    if (EFI_ERROR(Status)){
        goto GenerateSoftReset_Exit;
    }
    pBS->Stall (100);               // 100 usec

    ZeroMemory (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    BuildCommandList(SataDevInterface, CommandList, (UINT32)(UINTN)Commandtable);
    BuildCommandFIS(SataDevInterface, CommandStructure, CommandList, Commandtable);

    CommandList->Ahci_Cmd_W = 0; 
    // Update of Control Register
    Commandtable->CFis.Ahci_CFis_C = 0;
    if (PMPort != 0xFF) Commandtable->CFis.AHci_CFis_PmPort = PMPort;

    StartController(AhciBusInterface, SataDevInterface, BIT00);    
    Status = WaitforCommandComplete(SataDevInterface, NON_DATA_CMD, ATAPI_BUSY_CLEAR_TIMEOUT);

    //  Stop Controller
    StopController(AhciBusInterface, SataDevInterface,FALSE);

GenerateSoftReset_Exit:

    gSoftReset = FALSE;
    TRACE_AHCI_LEVEL2((-1," Status : %r\n", Status));
    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HandlePortComReset
//
// Description: Check if COM Reset is successful or not
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort, 
//  
// Output:      
//  EFI_STATUS      
//
// Modified:
//
// Referrals: ReadSCRRegister, WriteSCRRegister
//
// Notes:   
//  1. Check if Link is active. If not return error.
//  2. If Link is present, wait for PhyRdy Change bit to be set.
//  3. Clear SError register
//  4. Wait for D2H register FIS
//  5. Check the Status register for errors.
//  6. If COMRESET is success wait for sometime if the device is ATAPI or GEN1
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
HandlePortComReset(
    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
    IN UINT8                               Port,
    IN UINT8                               PMPort
)
{

    EFI_STATUS Status = EFI_SUCCESS;
    BOOLEAN     DeviceDetected = FALSE;
    UINT32      Data32, i, SStatusData;
    UINT32      AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);
    volatile    AHCI_RECEIVED_FIS  *FISAddress;
    UINT32      SError = 0;
    //  Check if detection is complete
    for (i = 0; i < HBA_PRESENCE_DETECT_TIMEOUT; i++){   // Total delay 10msec
        SStatusData = ReadSCRRegister (AhciBusInterface, SataDevInterface, Port, PMPort, 0); // SStatus
        SStatusData &= HBA_PORTS_SSTS_DET_MASK;            
        if ((SStatusData == HBA_PORTS_SSTS_DET_PCE) || (SStatusData == HBA_PORTS_SSTS_DET)) { 
            DeviceDetected = TRUE;
            break; 
        }
        pBS->Stall (1000);                               // 1msec
    }

    if (DeviceDetected) {
        // Wait till PhyRdy Change bit is set
        if (PMPort == 0xFF) {
            Status = WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_SERR,
                            HBA_PORTS_SERR_EX,
                            HBA_PORTS_SERR_EX,
                            ATAPI_BUSY_CLEAR_TIMEOUT);
        }
        else {
            Status = WaitforPMMemSet (SataDevInterface, PMPort, PSCR_1_SERROR, 
                    HBA_PORTS_SERR_EX, HBA_PORTS_SERR_EX, ATAPI_BUSY_CLEAR_TIMEOUT);
        }

        FISAddress =  (AHCI_RECEIVED_FIS *)HBA_PORT_REG32(AhciBaseAddr, Port, HBA_PORTS_FB);

        for (i = 0; i < ATAPI_BUSY_CLEAR_TIMEOUT; ) {
            SError = ReadSCRRegister (AhciBusInterface, SataDevInterface, Port, PMPort, 2); // SError
            if (SError & HBA_PORTS_ERR_CHK) {
              WriteSCRRegister (AhciBusInterface, SataDevInterface, Port, PMPort, 1, HBA_PORTS_ERR_CLEAR ); //SError
            }
            if(FISAddress->Ahci_Rfis[0] == FIS_REGISTER_D2H) {break;}
            pBS->Stall (1000);              // 1msec Strange. Delay is needed for read to succeed. 
                if (PMPort != 0xFF) {i+= 100;}  // For device behind PM Port, there is a delay in writing to the register. So count can be decreased.
                    else { i++; }
        } 

        // Wait till PxTFD gets updated from D2H FIS
        for (i = 0; i < 100; i++){   // Total delay 10msec        
            WriteSCRRegister (AhciBusInterface, SataDevInterface, Port, PMPort, 1, HBA_PORTS_ERR_CLEAR); //SError
            if((FISAddress->Ahci_Rfis[2] & HBA_PORTS_TFD_MASK) == (HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_TFD) & HBA_PORTS_TFD_MASK)) break;
            pBS->Stall (100);                               // 100usec
        }

        // check for errors
        if (FISAddress->Ahci_Rfis[2] & (HBA_PORTS_TFD_BSY | HBA_PORTS_TFD_ERR)) Status = EFI_DEVICE_ERROR;

        Data32 = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_IS); 
        if (Data32 & (BIT30 + BIT29 + BIT28 + BIT27 + BIT26)) Status = EFI_DEVICE_ERROR;

        // Clear the status
        WriteSCRRegister (AhciBusInterface, SataDevInterface, Port, PMPort, 1, HBA_PORTS_ERR_CLEAR); //SError
        HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    }
    else {
        Status = EFI_DEVICE_ERROR;
    }


    return Status;   

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadSCRRegister
//
// Description: 
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort,
//  IN UINT8                               Register (0 : SStatus 1: SError 2: SControl)
//
// Output:      
//      UINT32
// Modified:
//
// Referrals: 
//
// Notes:   
//  1. Check if the device is connected directly to the port
//  2. if yes, read to the AHCI Controller else write to the Port Multiplier register. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
UINT32
ReadSCRRegister (
    IN AHCI_BUS_PROTOCOL       *AhciBusInterface, 
    IN SATA_DEVICE_INTERFACE   *SataDevInterface,
    IN UINT8                    Port, 
    IN UINT8                    PMPort, 
    IN UINT8                    Register
)
{

    UINT32  Data32 = 0;
    UINT32  Reg = HBA_PORTS_SSTS;

    if (PMPort != 0xFF) {
        ReadWritePMPort (SataDevInterface, PMPort, Register, &Data32, FALSE);
    }
    else {
        if (Register == 1) Reg = HBA_PORTS_SCTL;
        if (Register == 2) Reg = HBA_PORTS_SERR;
        Data32 = HBA_PORT_REG32 (AhciBusInterface->AhciBaseAddress, Port, Reg);
    }

    return Data32;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WriteSCRRegister
//
// Description: Write to SCONTROL/Serror/SStatus register
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort,
//  IN UINT8                               Register, (0 : SStatus 1: SError 2: SControl)
//  IN UINT32                              Data32
//  
// Output:      
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:   
//  1. Check if the device is connected directly to the port
//  2. if yes, write to the AHCI Controller else write to the Port Multiplier register
//  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
WriteSCRRegister (
    IN AHCI_BUS_PROTOCOL       *AhciBusInterface, 
    IN SATA_DEVICE_INTERFACE   *SataDevInterface,
    IN UINT8                    Port, 
    IN UINT8                    PMPort, 
    IN UINT8                    Register,
    IN UINT32                   Data32
)
{

    UINT32  Reg = HBA_PORTS_SSTS;

    if (PMPort != 0xFF) {
        ReadWritePMPort (SataDevInterface, PMPort, Register, &Data32, TRUE);
    }
    else {
        if (Register == 2) Reg = HBA_PORTS_SCTL;
        if (Register == 1) Reg = HBA_PORTS_SERR;
        HBA_PORT_REG32_OR (AhciBusInterface->AhciBaseAddress, Port, Reg, Data32); 
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WaitforPMMemSet
//
// Description: Wait for memory to be set to the test value.
//
// Input:       
//              SATA_DEVICE_INTERFACE   *SataDevInterface,
//              PMPort
//              Register
//              MaskValue        - The mask value of memory
//              TestValue        - The test value of memory
//              WaitTimeInMs     - The time out value for wait memory set
//
// Output:      EFI_SUCCESS      - HBA reset successfully.
//              EFI_DEVICE_ERROR - HBA failed to complete hardware reset.
//
// Modified:
//
// Referrals: 
//
// Notes:   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS 
WaitforPMMemSet (
    IN SATA_DEVICE_INTERFACE   *SataDevInterface,
    IN UINT8                   PMPort,
    IN UINT8                   Register,
    IN UINT32                  AndMask,
    IN UINT32                  TestValue,
    IN UINT32                  WaitTimeInMs
)
{
    UINT32  Data32;

    while(WaitTimeInMs!=0){ 
        ReadWritePMPort (SataDevInterface, PMPort, Register, &Data32, FALSE);
        if((Data32 & AndMask) == TestValue) {return EFI_SUCCESS;}
        pBS->Stall (1000);  //  1Msec
        WaitTimeInMs--;
   }
   return EFI_DEVICE_ERROR;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CheckValidDevice
//
// Description: Check for valid ATA/ATAPI/PMPORT signature 
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Check if Link is active
//  2. Enable FIS and Command list run bits
//  3. Check for valid signature    
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS 
CheckValidDevice (
    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    IN UINT8                               Port,
    IN UINT8                               PMPort
)
{

    UINT8   Data8;
    UINT32  Data32;
    UINT32      AhciBaseAddr = (UINT32)(AhciBusInterface->AhciBaseAddress);

    // Check if Link is active
    Data8 = (UINT8)(HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_SSTS) & HBA_PORTS_SSTS_DET_MASK);
    if (Data8 != HBA_PORTS_SSTS_DET_PCE)  return EFI_DEVICE_ERROR;

    // Enable FIS receive and CI so that TFD gets updated properly
    // Clear out the command slot
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CI, 0);

   // Enable FIS Receive
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_FRE | HBA_PORTS_CMD_ST);

    // Wait till FIS is running
    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_FR,
                                    HBA_PORTS_CMD_FR,
                                    HBA_FR_CLEAR_TIMEOUT);
    
    // Wait till CR list is running
    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_CR,
                                    HBA_PORTS_CMD_CR,
                                    HBA_FR_CLEAR_TIMEOUT);

    // Clear Start Bit
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~(HBA_PORTS_CMD_ST));
    WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_CR,
                            HBA_CR_CLEAR_TIMEOUT);

    //Clear FIS Receive enable bit
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~(HBA_PORTS_CMD_FRE));
    WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_FR,
                            HBA_FR_CLEAR_TIMEOUT);


    // Check if valid signature is present
    Data32 = HBA_PORT_REG32(AhciBaseAddr, Port, HBA_PORTS_SIG);
    if (Data32 != ATA_SIGNATURE_32 && Data32 != ATAPI_SIGNATURE_32 && Data32 != PMPORT_SIGNATURE)
        return EFI_DEVICE_ERROR;

    Data8 = HBA_PORT_REG8 (AhciBaseAddr, Port, HBA_PORTS_TFD);
    if (Data8 & (HBA_PORTS_TFD_BSY | HBA_PORTS_TFD_DRQ)) return EFI_DEVICE_ERROR;

    return EFI_SUCCESS;

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************