//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmInt13.c 18    6/18/15 10:15a Olegi $
//
// $Revision: 18 $
//
// $Date: 6/18/15 10:15a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/CsmInt13.c $
// 
// 18    6/18/15 10:15a Olegi
// [TAG]  		EIP221923
// [Category]  	Bug Fix
// [Symptom]  	CsmBlockIO issue for 4K Sector size - Do the changes of
// EIP219657 to Aptio4 CSMBlockIo.
// 
// 17    12/23/13 3:14p Olegi
// EIP148138: use AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL instead of
// EFI_MBR_WRITE_PROTECTION_PROTOCOL
// 
// 16    12/23/13 10:22a Olegi
// EIP148123: CSM includes file which name has been changed
// 
// 15    7/01/13 5:56a Kapilporwal
// [TAG]  		EIP125560
// [Category]  	Improvement
// [Description]  	 	Please support Boot Sector Virus Protection for CSM
// Disabled Mode
// [Files]  		VirusProtect.c, VirusProtect.dxs, AhciBus.c,
// AhciController.c, CsmBlockIo.c, CsmInt13.c, Ata.c, IdeBus.c,
// SdioBlkIo.c, SdioDriver.c, efiusbmass.c
// 
// 14    3/09/12 3:22a Deepthins
// [TAG]  		EIP73940
// [Category]  	Improvement
// [Description]  	CSM BlockIo functions, ReadBlock and WriteBlock should
// return EFI_INVALID_PARAMETER if alignment is not proper.
// [Files]  		CsmInt13.c
// 
// 13    5/27/11 5:47a Rameshr
// [TAG]- EIP 58687
// [Category]-IMPROVEMENT
// [Description]- Update implementation of EFI_BLOCK_IO_PROTOCOL as
// described in UEFI specification v 2.3.1, page 12.8
// [Files]- CsmInt13.c
// 
// 12    1/12/10 11:50a Olegi
// Copyright message updated.
// 
// 11    5/09/08 10:37a Olegi
// Low memory segment is normalized before INT13 execution.
// 
// 10    4/27/07 5:14p Olegi
// CSM.CHM file preparation.
//
// 9     12/07/06 4:00p Olegi
//
// 8     3/13/06 2:38p Felixp
//
// 7     10/13/05 6:20p Olegi
// Added HW interrupt handling.
//
// 6     9/06/05 11:55a Olegi
//
// 5     6/26/05 7:19a Olegi
// Actual drive parameters size is used while copying extended drive
// parameters data.
//
// 4     3/04/05 1:43p Mandal
//
// 3     3/02/05 8:24a Olegi
//
// 2     2/21/05 9:33a Olegi
//
// 1     2/15/05 10:59a Olegi
// Initial VSS check-in.
//
//
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    CsmInt13.c
//
// Description: CSM Block I/O module. Support module containing reset,
//              flush, read and write functions.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "CsmBlockIo.h"
#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
#include <Protocol\AmiBlockIoWriteProtection.h>
extern AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL *gBlockIoWriteProtectionProtocol;
#endif

//extern    EFI_BOOT_SERVICES       *pBS;
extern  EFI_GUID                gEfiBlockIoProtocolGuid;

// Global variables

// Packet buffer under 1 MB for all version EDD calls
extern EDD_DEVICE_ADDRESS_PACKET    *mEDDPacketBuffer;

// This is a buffer for INT 13h func 48 information
extern CSM_LEGACY_DRIVE             *mDriveParameterBuffer;

// EDD 1.1 transfer buffer
extern VOID                         *mEDDTransferBuffer;

// Local function prototypes
BOOLEAN
GetInt13DeviceParameters (
    CSM_BLOCK_IO_DEV          *CsmBlockIoDev,
    IN CSM_LEGACY_DRIVE       *Drive
);

BOOLEAN
GetInt13Extensions (
    CSM_BLOCK_IO_DEV          *CsmBlockIoDev,
    IN CSM_LEGACY_DRIVE       *Drive
);

BOOLEAN
GetDriveParameters (
    CSM_BLOCK_IO_DEV          *CsmBlockIoDev,
    IN  CSM_LEGACY_DRIVE      *Drive
);

VOID
PatchHwInterrupt(
    CSM_BLOCK_IO_DEV          *CsmBlockIoDev
);

VOID
RestoreHwInterrupt(
    CSM_BLOCK_IO_DEV          *CsmBlockIoDev
);

UINT32 gTempHwIntSav;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    InitBlockIo
//
// Description: Initializes BlockIo protocol for a given device
//
// Input:       Device to initialize
//
// Output:      TRUE initialization succeeded, FALSE otherwise
//
// Referrals:   CSM_BLOCK_IO_DEV, GetInt13DeviceParameters, GetInt13Extensions
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
InitBlockIo (
    IN  CSM_BLOCK_IO_DEV        *Dev
)
{
    EFI_BLOCK_IO_PROTOCOL       *BlockIo;
    EFI_BLOCK_IO_MEDIA          *BlockMedia;
    CSM_LEGACY_DRIVE            *Drive;

    BlockIo = &Dev->BlockIo;
    BlockIo->Media = &Dev->BlockMedia;
    BlockMedia = BlockIo->Media;
    Drive = &Dev->Drive;

#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION > 0x4028a
    if(pST->Hdr.Revision >= 0x0002001F) {
        BlockIo->Revision    = EFI_BLOCK_IO_PROTOCOL_REVISION3;
    } else {
        BlockIo->Revision    = 1;
    }
#else
    BlockIo->Revision    = 1;
#endif

    if (GetInt13DeviceParameters (Dev, Drive)) {
        if (GetInt13Extensions (Dev, Drive)) {
            BlockMedia->LastBlock = (EFI_LBA)Drive->Parameters.PhysicalSectors - 1;
            BlockMedia->BlockSize = (UINT32)Drive->Parameters.BytesPerSector;

            if ((Drive->Parameters.Flags & EDD_DEVICE_REMOVABLE) == EDD_DEVICE_REMOVABLE) {
                BlockMedia->RemovableMedia = TRUE;
            }

        } else {
        //  No extensions, use Legacy parameters.
            BlockMedia->BlockSize = 512;
            BlockMedia->LastBlock = (Drive->MaxHead + 1) * Drive->MaxSector * (Drive->MaxCylinder + 1) - 1;
        }

//  TRACE((-1," BlockSize = %d  LastBlock = %d\n", BlockMedia->BlockSize, BlockMedia->LastBlock));
        // If the BlockSize is more than 512 bytes per sector, don't install the BlockIO Protocol 
        // for the device: Int13 function supports only 512 bytes per sector. 
        if(BlockMedia->BlockSize != 512) {
        	return FALSE;
        }
        BlockMedia->LogicalPartition = FALSE;
        BlockMedia->WriteCaching = FALSE;

        BlockMedia->ReadOnly = FALSE;       // Set for removable media in case no media present
        BlockMedia->MediaPresent = TRUE;    // ditto

        BlockIo->Reset = CsmBlockIoReset;
        BlockIo->FlushBlocks = CsmBlockIoFlushBlocks;

    //  Need logic here to test for EDD and set read/write functions if so
        if (!Drive->ExtendedInt13) {
        // No Int 13 extensions, use Legacy functions
            BlockIo->ReadBlocks = LegacyCsmReadBlocks;
            BlockIo->WriteBlocks = LegacyCsmWriteBlocks;
/*      } else if ((Drive->EddVersion == EDD_VERSION_30) && (Drive->Extensions64Bit)) {
            //  Use EDD 3.0 functions
            BlockIo->ReadBlocks = Edd30CsmReadBlocks;
            BlockIo->WriteBlocks = Edd30CsmWriteBlocks;
*/
        } else {
            //  Assume EDD 1.1 Read and Write functions.
            BlockIo->ReadBlocks = Edd11CsmReadBlocks;
            BlockIo->WriteBlocks = Edd11CsmWriteBlocks;
        }

        BlockMedia->LogicalPartition = FALSE;
        BlockMedia->WriteCaching = FALSE;

	//
	// Check for Core Version > 4.6.5.0
	//
#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION > 0x4028a

    if(pST->Hdr.Revision >= 0x0002001F) {
        //
        // Default value set to 1 logical blocks per PhysicalBlock
        //
        BlockMedia->LogicalBlocksPerPhysicalBlock=1;

        //
        // Default value set to 0 for Lowest Aligned LBA
        //
        BlockMedia->LowestAlignedLba=0;

        BlockMedia->OptimalTransferLengthGranularity=BlockMedia->BlockSize;
    }

#endif

        return TRUE;
    }
    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        GetInt13DeviceParameters
//
// Description: Get hard drive parameters using INT13 function 8
//
// Input:       BlockIo device, Drive
//
// Output:      TRUE if operation is successful, FALSE otherwise
//
// Referrals:   CSM_BLOCK_IO_DEV, CSM_LEGACY_DRIVE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
GetInt13DeviceParameters (
    CSM_BLOCK_IO_DEV    *CsmBlockIoDev,
    IN CSM_LEGACY_DRIVE *Drive
)
{
    BOOLEAN                 CarryFlag;
    UINT16                  Cylinder;
    EFI_IA32_REGISTER_SET   Regs;

    Regs.H.AH = 0x08;
    Regs.H.DL = Drive->Number;
    PatchHwInterrupt(CsmBlockIoDev);
    CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
    RestoreHwInterrupt(CsmBlockIoDev);
    CarryFlag = (BOOLEAN)Regs.X.Flags.CF;
//  TRACE((-1," GetInt13DeviceParameters: INT 13 08 DL=%02x : CF=%d AH=%02x\n", Drive->Number, CarryFlag, Regs.H.AH));

    if (CarryFlag || Regs.H.AH != 0x00) {
        Drive->ErrorCode = Regs.H.AH;
        return FALSE;
    }

    if (Drive->Floppy) {
        if (Regs.H.BL == 0x10) {
            Drive->AtapiFloppy = TRUE;
        } else {
            Drive->MaxHead = Regs.H.DH;
            Drive->MaxSector = Regs.H.CL;
            Drive->MaxCylinder = Regs.H.CH;
            if (Drive->MaxSector == 0) {
                return FALSE;
            }
        }
    } else {
        Drive->MaxHead = (UINT8)(Regs.H.DH & 0x3f);
        Cylinder = (UINT16)(((UINT16)Regs.H.DH & 0xc0) << 4);
        Cylinder |= (UINT16)(((UINT16)Regs.H.CL & 0xc0) << 2);
        Drive->MaxCylinder =  (UINT16)(Cylinder + Regs.H.CH);
        Drive->MaxSector = (UINT8)(Regs.H.CL & 0x3f);
    }
    return TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    GetInt13Extensions
//
// Description: Executes INT13 func 41 to check EDD extensions
//
// Input:       BlockIo device, Drive
//
// Output:      TRUE if operation is successful, FALSE otherwise
//
// Referrals:   CSM_BLOCK_IO_DEV, CSM_LEGACY_DRIVE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
GetInt13Extensions(
    CSM_BLOCK_IO_DEV    *CsmBlockIoDev,
    IN CSM_LEGACY_DRIVE *Drive
)
{
    BOOLEAN CarryFlag;
    EFI_IA32_REGISTER_SET Regs;

    Regs.H.AH = 0x41;
    Regs.X.BX = 0x55aa;
    Regs.H.DL = Drive->Number;
    PatchHwInterrupt(CsmBlockIoDev);
    CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
    RestoreHwInterrupt(CsmBlockIoDev);
    CarryFlag = (BOOLEAN)Regs.X.Flags.CF;
//  TRACE((-1, " GetInt13Extensions: INT 13 41 DL=%02x : CF=%d BX=%04x\n", Drive->Number, CarryFlag, Regs.X.BX));

    if (CarryFlag || Regs.X.BX != 0xaa55) {
        Drive->ExtendedInt13 = FALSE;
        Drive->DriveLockingAndEjecting = FALSE;
        Drive->Edd = FALSE;
        return(FALSE);
    }
    Drive->EddVersion = Regs.H.AH;
    Drive->ExtendedInt13 = (BOOLEAN)((Regs.X.CX & 0x01) == 0x01);
    Drive->DriveLockingAndEjecting = (BOOLEAN)((Regs.X.CX & 0x02) == 0x02);
    Drive->Edd = (BOOLEAN)((Regs.X.CX & 0x04) == 0x04);
    Drive->Extensions64Bit = (BOOLEAN)(Regs.X.CX & 0x08);

    Drive->ParametersValid = (UINT8)GetDriveParameters(CsmBlockIoDev, Drive);
    return TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    GetDriveParameters
//
// Description: Executes INT13 function 48 to get hard disk parameters
//
// Input:       BlockIo device, Drive
//
// Output:      TRUE if operation is successful, FALSE otherwise
//
// Referrals:   CSM_BLOCK_IO_DEV, CSM_LEGACY_DRIVE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
GetDriveParameters(
    CSM_BLOCK_IO_DEV        *CsmBlockIoDev,
    IN  CSM_LEGACY_DRIVE    *Drive
)
{
    BOOLEAN                 CarryFlag;
    EFI_IA32_REGISTER_SET   Regs;
    UINTN                   PointerMath;
    UINT8                   Temp;
    UINT8                   FloppyTable [] = {
        1,  9,  79, // Type 3 -- 720 Kb
        1,  18, 79, // Type 4 -- 1.44 Mb
        0,  1,  0,      // No type 5
        1,  36, 79,     // Type 6 -- 2.88 Mb
        0,  1,  0,
        0,  1,  0,
        0,  1,  0,
        0,  1,  0,
        0,  1,  0,
        1,  9,  39,     // Type C -- 360 Kb
        1,  15, 79      // Type D -- 1.2 Mb
        };

    Regs.H.AH = 0x48;
    Regs.H.DL = Drive->Number;

    //  Get Int13 Parameters
    mDriveParameterBuffer->Parameters.StructureSize = sizeof(EDD_DRIVE_PARAMETERS);
    Regs.X.DS = EFI_SEGMENT(&mDriveParameterBuffer->Parameters);
    Regs.X.SI = EFI_OFFSET(&mDriveParameterBuffer->Parameters);

    PatchHwInterrupt(CsmBlockIoDev);
    CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
    CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

    if (CarryFlag || Regs.H.AH != 0x00) {
        RestoreHwInterrupt(CsmBlockIoDev);
        Drive->ErrorCode = Regs.H.AH;
        pBS->SetMem(&Drive->Parameters, sizeof(Drive->Parameters), 0xaf);
        return FALSE;
    }

//  Copy parameters into real mode buffer
    pBS->SetMem (&Drive->Parameters, sizeof(Drive->Parameters), 0);
    pBS->CopyMem (
        &Drive->Parameters,
        &mDriveParameterBuffer->Parameters,
        mDriveParameterBuffer->Parameters.StructureSize // updated by int 13 call
        );

    if (Drive->AtapiFloppy) {

    //  Get Media type
        Regs.H.AH = 0x20;
        Regs.H.DL = Drive->Number;
        CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
        CarryFlag = (BOOLEAN)Regs.X.Flags.CF;
        if (CarryFlag) {

        //  Unknown or no media present
            if ((Drive->Parameters.Flags & EDD_GEOMETRY_VALID) == EDD_GEOMETRY_VALID) {
                Drive->MaxHead = (UINT8)(Drive->Parameters.MaxHeads - 1);
                Drive->MaxSector = (UINT8)Drive->Parameters.SectorsPerTrack;
                ASSERT(Drive->MaxSector != 0);
                Drive->MaxCylinder = (UINT16)(Drive->Parameters.MaxCylinders - 1);
            } else {
                Drive->MaxHead = 0;
                Drive->MaxSector = 1;
                Drive->MaxCylinder = 0;
            }

        } else {

        //  Media present -- get parameters
            Drive->MaxHead = 0;
            Drive->MaxSector = 1;
            Drive->MaxCylinder = 0;                 // Assume unknown media
            if(Regs.H.AL != 10) {
                if((Regs.H.AL >= 3) && (Regs.H.AL <= 0xd)) {
                    Temp = (Regs.H.AL - 3) * 3;             // First drive type is 3
                    Drive->MaxHead = FloppyTable[Temp];
                    Drive->MaxSector = FloppyTable[Temp+1];
                    Drive->MaxCylinder = FloppyTable[Temp+2];
                }
            } else {
                if ((Drive->Parameters.Flags & EDD_GEOMETRY_VALID) == EDD_GEOMETRY_VALID) {
                    Drive->MaxHead = (UINT8)(Drive->Parameters.MaxHeads - 1);
                    Drive->MaxSector = (UINT8)Drive->Parameters.SectorsPerTrack;
                    ASSERT(Drive->MaxSector != 0);
                    Drive->MaxCylinder = (UINT16)(Drive->Parameters.MaxCylinders - 1);
                } else {
                    Drive->MaxHead = 0;
                    Drive->MaxSector = 1;
                    Drive->MaxCylinder = 0;
                }
            }
        }
        Drive->Parameters.PhysicalSectors = (Drive->MaxHead + 1) * Drive->MaxSector * (Drive->MaxCylinder + 1);
        Drive->Parameters.BytesPerSector = 512;
    }

    // This data comes from the BIOS so it may not allways be valid
    //  since the BIOS may reuse this buffer for future accesses
    PointerMath = EFI_SEGMENT(Drive->Parameters.FDPT) << 4;
    PointerMath += EFI_OFFSET(Drive->Parameters.FDPT);
    Drive->FdptPointer = (VOID *)PointerMath;

    RestoreHwInterrupt(CsmBlockIoDev);

    return TRUE;
}

// BLOCK I/O FUNCTIONS

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    CsmBlockIoFlushBlocks
//
// Description: BlockIo protocol function that flushes data onto the device
//
// Input:       Instance of the EFI_BLOCK_IO_PROTOCOL
//
// Output:      Status of the operation
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmBlockIoFlushBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This
    )
{
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    CsmBlockIoFlushBlocks
//
// Description: BlockIo protocol function that resets the device
//
// Input:
//   Instance of the EFI_BLOCK_IO_PROTOCOL
//   ExtendedVerification request
//
// Output:      Status of the operation
//
// Referrals:   CSM_BLOCK_IO_DEV, EFI_IA32_REGISTER_SET
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmBlockIoReset (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  BOOLEAN               ExtendedVerification
    )
{
    CSM_BLOCK_IO_DEV       *CsmBlockIoDev;
    EFI_IA32_REGISTER_SET  Regs;
    BOOLEAN                CarryFlag;
    EFI_STATUS              Status  = EFI_SUCCESS;

    CsmBlockIoDev = (CSM_BLOCK_IO_DEV *) This;

    PatchHwInterrupt(CsmBlockIoDev);

    Regs.H.AH = 0x00;
    Regs.H.DL = CsmBlockIoDev->Drive.Number;
    CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
    CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

//      TRACE((-1, " CsmBlockIoReset: INT 13 00 DL=%02x : CF=%d AH=%02x\n", CsmBlockIoDev->Drive.Number, CarryFlag, Regs.H.AH));

    if (CarryFlag) {
        if (Regs.H.AL == ERR_RESET_FAILED) {
            Regs.H.AH = 0x00;
            Regs.H.DL = CsmBlockIoDev->Drive.Number;
            CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
            CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

//              TRACE((-1, "CsmBlockIoReset: INT 13 00 DL=%02x : CF=%d AH=%02x\n", CsmBlockIoDev->Drive.Number, CarryFlag, Regs.H.AH));

            if (CarryFlag) {
                CsmBlockIoDev->Drive.ErrorCode = Regs.H.AH;
                Status = EFI_DEVICE_ERROR;
            }
        }
    }

    RestoreHwInterrupt(CsmBlockIoDev);

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    Edd30CsmReadBlocks
//
// Description: Read device using EDD3.0 read function
//
// Input:   BlockIo protocol instance, Media ID, read data buffer
//
// Output:  Status of the operation
//
// Referrals:   EFI_LBA
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
Edd30CsmReadBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    )
{
    EFI_BLOCK_IO_MEDIA          *Media;
    CSM_BLOCK_IO_DEV            *CsmBlockIoDev;
    EDD_DEVICE_ADDRESS_PACKET   *AddressPacket; // I exist only for readability
    EFI_IA32_REGISTER_SET       Regs;
    UINT64                      TransferBuffer;
    UINTN                       NumberOfBlocks;
    UINTN                       TransferByteSize;
    UINTN                       BlockSize;
    CSM_LEGACY_DRIVE            *Drive;
    BOOLEAN                     CarryFlag;
    UINTN                       MaxTransferBlocks;
    EFI_BLOCK_IO_PROTOCOL                *BlockIo;
    EFI_STATUS                  Status = EFI_SUCCESS;

    Media = This->Media;
    BlockSize = Media->BlockSize;

//  Check for error conditions
    if (MediaId != Media->MediaId) return EFI_MEDIA_CHANGED;
    if (LBA > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if ((LBA + (BufferSize / BlockSize) - 1) > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if (BufferSize % BlockSize != 0) return EFI_BAD_BUFFER_SIZE;
    if (Buffer == NULL) return EFI_INVALID_PARAMETER;
    if (BufferSize == 0) return EFI_SUCCESS;

//  CsmBlockIoDev = ((CSM_BLOCK_IO_DEV *) ((CHAR8 *)(This) - (CHAR8 *) &(((CSM_BLOCK_IO_DEV *) 0)->BlockIo)));
    CsmBlockIoDev = (CSM_BLOCK_IO_DEV *) This;
    AddressPacket = mEDDPacketBuffer;

    MaxTransferBlocks = MAX_EDD11_XFER/BlockSize;

    TransferBuffer = (UINT64)Buffer;

    PatchHwInterrupt(CsmBlockIoDev);

    while (BufferSize) {
        NumberOfBlocks = BufferSize/BlockSize;
        NumberOfBlocks = NumberOfBlocks > MaxTransferBlocks ? MaxTransferBlocks : NumberOfBlocks; // Max transfer MaxTransferBlocks

        AddressPacket->PacketSizeInBytes = sizeof(EDD_DEVICE_ADDRESS_PACKET);
        AddressPacket->Zero = 0;
        AddressPacket->NumberOfBlocks = (UINT8)NumberOfBlocks;
        AddressPacket->Zero2 = 0;
        AddressPacket->SegOffset = 0xffffffff;
        AddressPacket->LBA = (UINT64)LBA;
        AddressPacket->TransferBuffer = TransferBuffer;

        Regs.H.AH = 0x42;
        Regs.H.DL = CsmBlockIoDev->Drive.Number;
        Regs.X.SI = EFI_OFFSET(AddressPacket);
        Regs.X.DS = EFI_SEGMENT(AddressPacket);

        CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
        CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

// TRACE((-1, " Edd30CsmReadBlocks: INT 13 42 DL=%02x : CF=%d AH=%02x\n", CsmBlockIoDev->Drive.Number, CarryFlag, Regs.H.AH));

        Media->MediaPresent = TRUE;
        if (CarryFlag) {
        //  If we have a carry, figure out the error.
            CsmBlockIoDev->Drive.ErrorCode = Regs.H.AH;
            if (CsmBlockIoDev->Drive.ErrorCode == ERR_DISK_CHANGED) {
                Media->MediaId++;
                Drive = &CsmBlockIoDev->Drive;
                if (GetInt13DeviceParameters(CsmBlockIoDev, Drive)) {
                    if (GetInt13Extensions (CsmBlockIoDev, Drive)) {
                        Media->LastBlock = (EFI_LBA)Drive->Parameters.PhysicalSectors - 1;
                        Media->BlockSize = (UINT32)Drive->Parameters.BytesPerSector;
                    } else {
                        ASSERT(FALSE);
                    }
                    Media->ReadOnly = FALSE;
                    pBS->HandleProtocol(CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, (VOID **)&BlockIo);
                    pBS->ReinstallProtocolInterface (CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, BlockIo, BlockIo);
                    Status = EFI_MEDIA_CHANGED;
                    goto Exit;
                }
            }

            if (Media->RemovableMedia) {
                Media->MediaPresent = FALSE;
            }

            Status = EFI_DEVICE_ERROR;
            goto Exit;
        }

        TransferByteSize = NumberOfBlocks * BlockSize;
        BufferSize = BufferSize - TransferByteSize;
        TransferBuffer += TransferByteSize;
        LBA += NumberOfBlocks;
    }
Exit:
    RestoreHwInterrupt(CsmBlockIoDev);

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    Edd30CsmWriteBlocks
//
// Description: Write device using EDD3.0 write function
//
// Input:   BlockIo protocol instance, Media ID, write data buffer
//
// Output:  Status of the operation
//
// Referrals:   EFI_LBA
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
Edd30CsmWriteBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    )
{
    EFI_BLOCK_IO_MEDIA          *Media;
    CSM_BLOCK_IO_DEV            *CsmBlockIoDev;
    EDD_DEVICE_ADDRESS_PACKET   *AddressPacket;
    EFI_IA32_REGISTER_SET       Regs;
    UINT64                      TransferBuffer;
    UINTN                       NumberOfBlocks;
    UINTN                       TransferByteSize;
    UINTN                       BlockSize;
    CSM_LEGACY_DRIVE            *Drive;
    BOOLEAN                     CarryFlag;
    UINTN                       MaxTransferBlocks;
    EFI_BLOCK_IO_PROTOCOL                *BlockIo;
    EFI_STATUS                  Status = EFI_SUCCESS;

    Media = This->Media;
    BlockSize = Media->BlockSize;

    if (MediaId != Media->MediaId) return EFI_MEDIA_CHANGED;
    if (LBA > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if ((LBA + (BufferSize / BlockSize) - 1) > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if (BufferSize % BlockSize != 0) return EFI_BAD_BUFFER_SIZE;
    if (Buffer == NULL) return EFI_INVALID_PARAMETER;
    if (BufferSize == 0) return EFI_SUCCESS;

    CsmBlockIoDev = (CSM_BLOCK_IO_DEV *) This;
    AddressPacket = mEDDPacketBuffer;

    MaxTransferBlocks = MAX_EDD11_XFER/BlockSize;

    PatchHwInterrupt(CsmBlockIoDev);

    TransferBuffer = (UINT64)Buffer;
    while (BufferSize) {
        NumberOfBlocks = BufferSize/BlockSize;
        NumberOfBlocks = NumberOfBlocks > MaxTransferBlocks ? MaxTransferBlocks : NumberOfBlocks; // Max transfer MaxTransferBlocks
        AddressPacket->PacketSizeInBytes = sizeof(EDD_DEVICE_ADDRESS_PACKET);
        AddressPacket->Zero = 0;
        AddressPacket->NumberOfBlocks = (UINT8)NumberOfBlocks;
        AddressPacket->Zero2 = 0;
        AddressPacket->SegOffset = 0xffffffff;
        AddressPacket->LBA = (UINT64)LBA;
        AddressPacket->TransferBuffer = TransferBuffer;

        Regs.H.AH = 0x43;
        Regs.H.AL = 0x00; // Write Verify Off
        Regs.H.DL = (UINT8)(CsmBlockIoDev->Drive.Number);
        Regs.X.SI = EFI_OFFSET(AddressPacket);
        Regs.X.DS = EFI_SEGMENT(AddressPacket);

        CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
        CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

//          TRACE((-1, " Edd30CsmWriteBlocks: INT 13 43 DL=%02x : CF=%d AH=%02x\n", CsmBlockIoDev->Drive.Number, CarryFlag, Regs.H.AH));

        Media->MediaPresent = TRUE;
        if (CarryFlag) {
        //  If we have a carry, figure out the error.
            CsmBlockIoDev->Drive.ErrorCode = Regs.H.AH;
            if (CsmBlockIoDev->Drive.ErrorCode == ERR_DISK_CHANGED) {
                Media->MediaId++;
                Drive = &CsmBlockIoDev->Drive;
                if (GetInt13DeviceParameters(CsmBlockIoDev, Drive)) {
                    if (GetInt13Extensions (CsmBlockIoDev, Drive)) {
                        Media->LastBlock = (EFI_LBA)Drive->Parameters.PhysicalSectors - 1;
                        Media->BlockSize = (UINT32)Drive->Parameters.BytesPerSector;
                    } else {
                        ASSERT(FALSE);
                    }
                    Media->ReadOnly = FALSE;
                    pBS->HandleProtocol(CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, (VOID **)&BlockIo);
                    pBS->ReinstallProtocolInterface (CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, BlockIo, BlockIo);
                    Status = EFI_MEDIA_CHANGED;
                    goto Exit;
                }
            } else if (CsmBlockIoDev->Drive.ErrorCode == ERR_WRITE_PROTECTED) {
                Media->ReadOnly = TRUE;
                return EFI_WRITE_PROTECTED;
            }

            if (Media->RemovableMedia) {
                Media->MediaPresent = FALSE;
            }
            Status = EFI_DEVICE_ERROR;
            goto Exit;
        }

        Media->ReadOnly = FALSE;
        TransferByteSize = NumberOfBlocks * BlockSize;
        BufferSize = BufferSize - TransferByteSize;
        TransferBuffer += TransferByteSize;
        LBA += NumberOfBlocks;
    }
Exit:
    RestoreHwInterrupt(CsmBlockIoDev);
    return Status;
}


// Older read/write methods
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    Edd11CsmReadBlocks
//
// Description: Read device using EDD1.1 read function
//
// Input:   BlockIo protocol instance, Media ID, read data buffer
//
// Output:  Status of the operation
//
// Referrals:   EFI_LBA
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
Edd11CsmReadBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    )
{
    EFI_BLOCK_IO_MEDIA          *Media;
    CSM_BLOCK_IO_DEV            *CsmBlockIoDev;
    EDD_DEVICE_ADDRESS_PACKET   *AddressPacket;
    EFI_IA32_REGISTER_SET       Regs;
    UINT64                      TransferBuffer;
    UINTN                       NumberOfBlocks;
    UINTN                       TransferByteSize;
    UINTN                       BlockSize;
    CSM_LEGACY_DRIVE            *Drive;
    BOOLEAN                     CarryFlag;
    UINTN                       MaxTransferBlocks;
    EFI_BLOCK_IO_PROTOCOL                *BlockIo;
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINT16                      AlignedOffset;
    UINT16                      AlignedSegment;
    UINTN                       BufferAddress;

    Media = This->Media;
    BlockSize = Media->BlockSize;

    if (MediaId != Media->MediaId) return EFI_MEDIA_CHANGED;
    if (BufferSize == 0) return EFI_SUCCESS;
    if (LBA > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if ((LBA + (BufferSize / BlockSize) - 1) > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if (BufferSize % BlockSize != 0) return EFI_BAD_BUFFER_SIZE;
    if (Buffer == NULL) return EFI_INVALID_PARAMETER;

    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    (VOID *)BufferAddress = Buffer;
    if((Media->IoAlign > 1 ) && (BufferAddress % Media->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }

    CsmBlockIoDev = (CSM_BLOCK_IO_DEV *) This;
    AddressPacket = mEDDPacketBuffer;

    MaxTransferBlocks = MAX_EDD11_XFER/BlockSize;

    PatchHwInterrupt(CsmBlockIoDev);

    TransferBuffer = (UINT64)mEDDTransferBuffer;
    while (BufferSize) {
        NumberOfBlocks = BufferSize / BlockSize;
        NumberOfBlocks = NumberOfBlocks > MaxTransferBlocks ? MaxTransferBlocks : NumberOfBlocks; // Max transfer MaxTransferBlocks
        AddressPacket->PacketSizeInBytes = sizeof(EDD_DEVICE_ADDRESS_PACKET);
        AddressPacket->Zero = 0;
        AddressPacket->NumberOfBlocks = (UINT8)NumberOfBlocks;
        AddressPacket->Zero2 = 0;

        //
        // Normalize TransferBuffer address if needed
        //
        AlignedOffset = EFI_OFFSET(TransferBuffer);
        AlignedSegment = EFI_SEGMENT(TransferBuffer);
        if(AlignedOffset != 0) {
            AlignedSegment = AlignedSegment + (AlignedOffset >> 4);
            AlignedOffset = 0;
        }

        AddressPacket->SegOffset = AlignedSegment << 16;
        AddressPacket->SegOffset |= AlignedOffset;

        AddressPacket->LBA = (UINT64)LBA;

        Regs.H.AH = 0x42;
        Regs.H.DL = CsmBlockIoDev->Drive.Number;
        Regs.X.SI = EFI_OFFSET(AddressPacket);
        Regs.X.DS = EFI_SEGMENT(AddressPacket);

        CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
        CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

//          TRACE((-1, "Edd11CsmReadBlocks: INT 13 42 DL=%02x : CF=%d AH=%02x : LBA 0x%lx  Block(s) %0d \n", CsmBlockIoDev->Drive.Number, CarryFlag, Regs.H.AH, LBA, NumberOfBlocks));

        Media->MediaPresent = TRUE;
        if (CarryFlag) {
        //  If we have a carry, figure out the error.
            CsmBlockIoDev->Drive.ErrorCode = Regs.H.AH;
            if (CsmBlockIoDev->Drive.ErrorCode == ERR_DISK_CHANGED) {
                Media->MediaId++;
                Drive = &CsmBlockIoDev->Drive;
                if (GetInt13DeviceParameters(CsmBlockIoDev, Drive)) {
                    if (GetInt13Extensions (CsmBlockIoDev, Drive)) {
                        Media->LastBlock = (EFI_LBA)Drive->Parameters.PhysicalSectors - 1;
                        Media->BlockSize = (UINT32)Drive->Parameters.BytesPerSector;
                    } else {
                        ASSERT(FALSE);
                    }
                //  The media has changed.
                    Media->ReadOnly = FALSE;
                    pBS->HandleProtocol(CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, (VOID **)&BlockIo);
                    pBS->ReinstallProtocolInterface (CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, BlockIo, BlockIo);
                    Status = EFI_MEDIA_CHANGED;
                    goto Exit;
                }
            }

            if (Media->RemovableMedia) {
                Media->MediaPresent = FALSE;
            }

            Status = EFI_DEVICE_ERROR;
            goto Exit;
        }

        TransferByteSize = NumberOfBlocks * BlockSize;
        pBS->CopyMem (Buffer, (VOID *)(UINTN)TransferBuffer, TransferByteSize);
        BufferSize = BufferSize - TransferByteSize;
        Buffer = (VOID *)((UINT8 *)Buffer + TransferByteSize);
        LBA += NumberOfBlocks;
    }
Exit:
    RestoreHwInterrupt(CsmBlockIoDev);
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    Edd11CsmWriteBlocks
//
// Description: Write device using EDD1.1 write function
//
// Input:   BlockIo protocol instance, Media ID, write data buffer
//
// Output:  Status of the operation
//
// Referrals:   EFI_LBA
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
Edd11CsmWriteBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    )
{
    EFI_BLOCK_IO_MEDIA          *Media;
    CSM_BLOCK_IO_DEV            *CsmBlockIoDev;
    EDD_DEVICE_ADDRESS_PACKET   *AddressPacket; // I exist only for readability
    EFI_IA32_REGISTER_SET       Regs;
    UINT64                      TransferBuffer;
    UINTN                       NumberOfBlocks;
    UINTN                       TransferByteSize;
    UINTN                       BlockSize;
    CSM_LEGACY_DRIVE            *Drive;
    BOOLEAN                     CarryFlag;
    UINTN                       MaxTransferBlocks;
    EFI_BLOCK_IO_PROTOCOL                *BlockIo;
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINT16                      AlignedOffset;
    UINT16                      AlignedSegment;
    UINTN                       BufferAddress;

    Media = This->Media;
    BlockSize = Media->BlockSize;

    if (MediaId != Media->MediaId) return EFI_MEDIA_CHANGED;
    if (BufferSize == 0) return EFI_SUCCESS;
    if (LBA > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if ((LBA + (BufferSize / BlockSize) - 1) > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if (BufferSize % BlockSize != 0) return EFI_BAD_BUFFER_SIZE;
    if (Buffer == NULL) return EFI_INVALID_PARAMETER;

    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    (VOID *)BufferAddress = Buffer;
    if((Media->IoAlign > 1 ) && (BufferAddress % Media->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }

    CsmBlockIoDev = (CSM_BLOCK_IO_DEV *) This;
    AddressPacket = mEDDPacketBuffer;

    MaxTransferBlocks = MAX_EDD11_XFER/BlockSize;

    PatchHwInterrupt(CsmBlockIoDev);

    TransferBuffer = (UINT64)mEDDTransferBuffer;
    while (BufferSize) {
        NumberOfBlocks = BufferSize/BlockSize;
        NumberOfBlocks = NumberOfBlocks > MaxTransferBlocks ? MaxTransferBlocks : NumberOfBlocks; // Max transfer MaxTransferBlocks
        AddressPacket->PacketSizeInBytes = sizeof(EDD_DEVICE_ADDRESS_PACKET);
        AddressPacket->Zero = 0;
        AddressPacket->NumberOfBlocks = (UINT8)NumberOfBlocks;
        AddressPacket->Zero2 = 0;

        //
        // Normalize TransferBuffer address if needed
        //
        AlignedOffset = EFI_OFFSET(TransferBuffer);
        AlignedSegment = EFI_SEGMENT(TransferBuffer);

        if (AlignedOffset != 0) {
            AlignedSegment =  AlignedSegment + (AlignedOffset >> 4);
            AlignedOffset = 0;
        }

        AddressPacket->SegOffset = AlignedSegment << 16;
        AddressPacket->SegOffset |= AlignedOffset;

        AddressPacket->LBA = (UINT64)LBA;

        Regs.H.AH = 0x43;
        Regs.H.AL = 0x00; // Write Verify disable
        Regs.H.DL = CsmBlockIoDev->Drive.Number;
        Regs.X.SI = EFI_OFFSET(AddressPacket);
        Regs.X.DS = EFI_SEGMENT(AddressPacket);

        TransferByteSize = NumberOfBlocks * BlockSize;
        pBS->CopyMem ((VOID *)(UINTN)TransferBuffer, Buffer, TransferByteSize);

        CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
        CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

//          TRACE((-1, "Edd11CsmWriteBlocks: INT 13 43 DL=%02x : CF=%d AH=%02x\n: LBA 0x%lx  Block(s) %0d \n", CsmBlockIoDev->Drive.Number, CarryFlag, Regs.H.AH, LBA, NumberOfBlocks));

        Media->MediaPresent = TRUE;
        if (CarryFlag) {
        //  If we have a carry, figure out the error.
            CsmBlockIoDev->Drive.ErrorCode = Regs.H.AH;
            if (CsmBlockIoDev->Drive.ErrorCode == ERR_DISK_CHANGED) {
                Media->MediaId++;
                Drive = &CsmBlockIoDev->Drive;
                if (GetInt13DeviceParameters(CsmBlockIoDev, Drive)) {
                    if (GetInt13Extensions (CsmBlockIoDev, Drive)) {
                        Media->LastBlock = (EFI_LBA)Drive->Parameters.PhysicalSectors - 1;
                        Media->BlockSize = (UINT32)Drive->Parameters.BytesPerSector;
                    } else {
                        ASSERT(FALSE);
                    }
                //  The media has changed.
                    Media->ReadOnly = FALSE;
                    pBS->HandleProtocol(CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, (VOID **)&BlockIo);
                    pBS->ReinstallProtocolInterface (CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, BlockIo, BlockIo);
                    Status = EFI_MEDIA_CHANGED;
                    goto Exit;
                }
            } else if (CsmBlockIoDev->Drive.ErrorCode == ERR_WRITE_PROTECTED) {
                Media->ReadOnly = TRUE;
                Status = EFI_WRITE_PROTECTED;
                goto Exit;
            }

            if (Media->RemovableMedia) {
                Media->MediaPresent = FALSE;
            }

            Status = EFI_DEVICE_ERROR;
            goto Exit;
        }

        Media->ReadOnly = FALSE;
        BufferSize = BufferSize - TransferByteSize;
        Buffer = (VOID *)((UINT8 *)Buffer + TransferByteSize);
        LBA += NumberOfBlocks;
    }
Exit:
    RestoreHwInterrupt(CsmBlockIoDev);
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    LegacyCsmReadBlocks
//
// Description: Read device using INT13 function 2
//
// Input:   BlockIo protocol instance, Media ID, read data buffer
//
// Output:  Status of the operation
//
// Referrals:   EFI_LBA
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LegacyCsmReadBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    )
{
    EFI_BLOCK_IO_MEDIA      *Media;
    CSM_BLOCK_IO_DEV        *CsmBlockIoDev;
    EFI_IA32_REGISTER_SET   Regs;
    UINTN                   UpperCylinder, Temp;
    UINTN                   Cylinder, Head, Sector;
    UINTN                   NumberOfBlocks, TransferByteSize;
    UINTN                   ShortLba, CheckLba;
    UINTN                   BlockSize;
    CSM_LEGACY_DRIVE        *Drive;
    BOOLEAN                 CarryFlag;
    UINTN                   Retry;
    EFI_BLOCK_IO_PROTOCOL            *BlockIo;
    EFI_STATUS              Status = EFI_SUCCESS;
    UINTN                   BufferAddress;

    Media = This->Media;
    BlockSize = Media->BlockSize;

    if (MediaId != Media->MediaId) return EFI_MEDIA_CHANGED;
    if (BufferSize == 0) return EFI_SUCCESS;
    if (LBA > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if ((LBA + (BufferSize / BlockSize) - 1) > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if (BufferSize % BlockSize != 0) return EFI_BAD_BUFFER_SIZE;
    if (Buffer == NULL) return EFI_INVALID_PARAMETER;

    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    (VOID *)BufferAddress = Buffer;
    if((Media->IoAlign > 1 ) && (BufferAddress % Media->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }

    CsmBlockIoDev = (CSM_BLOCK_IO_DEV *) This;
    ShortLba = (UINTN) LBA;

    PatchHwInterrupt(CsmBlockIoDev);

    while (BufferSize) {
    //  Convert LBA to CHS.
        Sector = (ShortLba % CsmBlockIoDev->Drive.MaxSector) + 1;
        Temp = ShortLba / CsmBlockIoDev->Drive.MaxSector;
        Head = Temp % (CsmBlockIoDev->Drive.MaxHead + 1);
        Cylinder = Temp / (CsmBlockIoDev->Drive.MaxHead + 1);
    //  Limit number of blocks to one head and cylindar
        NumberOfBlocks = BufferSize/BlockSize;
        Temp = CsmBlockIoDev->Drive.MaxSector - Sector + 1;
        NumberOfBlocks = NumberOfBlocks > Temp ? Temp : NumberOfBlocks;

        Retry = 3;
    //  Loop to perform the read
        do {
          Regs.H.AH = 2;
          Regs.H.AL = (UINT8) NumberOfBlocks;
          Regs.H.DL = CsmBlockIoDev->Drive.Number;

          UpperCylinder = (Cylinder & 0x0f00) >> 2;

          CheckLba = Cylinder*(CsmBlockIoDev->Drive.MaxHead + 1) + Head;
          CheckLba = CheckLba*CsmBlockIoDev->Drive.MaxSector +  Sector - 1;

//          ASSERT(CheckLba == ShortLba);

          Regs.H.CL = (UINT8) ((Sector & 0x3f) + (UpperCylinder & 0xff));
          Regs.H.DH = (UINT8) (Head & 0x3f);
          Regs.H.CH = (UINT8) (Cylinder & 0xff);

          Regs.X.BX = EFI_OFFSET(mEDDTransferBuffer);
          Regs.X.ES = EFI_SEGMENT(mEDDTransferBuffer);

          CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
          CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

//              TRACE((-1, "LegacyCsmReadBlocks: INT 13 02 DL=%02x : CF=%d AH=%02x\n", CsmBlockIoDev->Drive.Number, CarryFlag, Regs.H.AH));

          Retry--;
        } while (CarryFlag && Retry !=0 && Regs.H.AH != ERR_DISK_CHANGED);

        Media->MediaPresent = TRUE;
        if (CarryFlag) {
        //  If we have a carry, figure out the error.
            CsmBlockIoDev->Drive.ErrorCode = Regs.H.AH;
            if (CsmBlockIoDev->Drive.ErrorCode == ERR_DISK_CHANGED) {
                Media->MediaId++;
                Drive = &CsmBlockIoDev->Drive;
                if (GetInt13DeviceParameters(CsmBlockIoDev, Drive)) {
                //  The media has changed
                    if (GetInt13Extensions (CsmBlockIoDev, Drive)) {
                        Media->LastBlock = (EFI_LBA)Drive->Parameters.PhysicalSectors - 1;
                        Media->BlockSize = (UINT32)Drive->Parameters.BytesPerSector;
                    } else {
                        Media->LastBlock = (Drive->MaxHead + 1) * Drive->MaxSector * (Drive->MaxCylinder + 1) - 1;
                        Media->BlockSize = 512;
                    }
                    Media->ReadOnly = FALSE;
                    pBS->HandleProtocol(CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, (VOID **)&BlockIo);
                    pBS->ReinstallProtocolInterface (CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, BlockIo, BlockIo);
                    Status = EFI_MEDIA_CHANGED;
                    goto Exit;
                }
            }

            if (Media->RemovableMedia) {
                Media->MediaPresent = FALSE;
            }

            Status = EFI_DEVICE_ERROR;
            goto Exit;
        }

        TransferByteSize = NumberOfBlocks * BlockSize;
        pBS->CopyMem (Buffer, mEDDTransferBuffer, TransferByteSize);

        ShortLba = ShortLba + NumberOfBlocks;
        BufferSize = BufferSize - TransferByteSize;
        Buffer = (VOID *)((UINT8 *)Buffer + TransferByteSize);
    }
Exit:
    RestoreHwInterrupt(CsmBlockIoDev);
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    LegacyCsmWriteBlocks
//
// Description: Write device using INT13 function 3
//
// Input:   BlockIo protocol instance, Media ID, write data buffer
//
// Output:  Status of the operation
//
// Referrals:   EFI_LBA
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LegacyCsmWriteBlocks (
    IN  EFI_BLOCK_IO_PROTOCOL          *This,
    IN  UINT32                MediaId,
    IN  EFI_LBA               LBA,
    IN  UINTN                 BufferSize,
    OUT VOID                  *Buffer
    )
{
    EFI_BLOCK_IO_MEDIA      *Media;
    CSM_BLOCK_IO_DEV        *CsmBlockIoDev;
    EFI_IA32_REGISTER_SET   Regs;
    UINTN                   UpperCylinder, Temp;
    UINTN                   Cylinder, Head, Sector;
    UINTN                   NumberOfBlocks, TransferByteSize;
    UINTN                   ShortLba, CheckLba;
    UINTN                   BlockSize;
    CSM_LEGACY_DRIVE        *Drive;
    BOOLEAN                 CarryFlag;
    UINTN                   Retry;
    EFI_BLOCK_IO_PROTOCOL            *BlockIo;
    EFI_STATUS              Status = EFI_SUCCESS;
    UINTN                   BufferAddress;

    Media = This->Media;
    BlockSize = Media->BlockSize;

    if (MediaId != Media->MediaId) return EFI_MEDIA_CHANGED;
    if (BufferSize == 0) return EFI_SUCCESS;
    if (LBA > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if ((LBA + (BufferSize / BlockSize) - 1) > Media->LastBlock) return EFI_INVALID_PARAMETER;
    if (BufferSize % BlockSize != 0) return EFI_BAD_BUFFER_SIZE;
    if (Buffer == NULL) return EFI_INVALID_PARAMETER;
    
    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    (VOID *)BufferAddress = Buffer;
    if((Media->IoAlign > 1 ) && (BufferAddress % Media->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
    // Verify if write is allowed
    if(gBlockIoWriteProtectionProtocol != NULL) {
        Status = gBlockIoWriteProtectionProtocol->BlockIoWriteProtectionCheck(
                    gBlockIoWriteProtectionProtocol,
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

    CsmBlockIoDev = (CSM_BLOCK_IO_DEV *) This;
    ShortLba = (UINTN) LBA;

    PatchHwInterrupt(CsmBlockIoDev);

    while(BufferSize) {
    //  Convert LBA to CHS
        Sector = (ShortLba % CsmBlockIoDev->Drive.MaxSector) + 1;
        Temp = ShortLba / CsmBlockIoDev->Drive.MaxSector;
        Head = Temp % (CsmBlockIoDev->Drive.MaxHead + 1);
        Cylinder = Temp / (CsmBlockIoDev->Drive.MaxHead + 1);

    //  Limit number of blocks to one head and cylindar
        NumberOfBlocks = BufferSize/BlockSize;
        Temp = CsmBlockIoDev->Drive.MaxSector - Sector + 1;
        NumberOfBlocks = NumberOfBlocks > Temp ? Temp : NumberOfBlocks;


        Retry = 3;
    //  Loop to perform the write.
        do {
            Regs.H.AH = 3;
            Regs.H.AL = (UINT8) NumberOfBlocks;
            Regs.H.DL = CsmBlockIoDev->Drive.Number;

            UpperCylinder = (Cylinder & 0x0f00) >> 2;

            CheckLba = Cylinder*(CsmBlockIoDev->Drive.MaxHead + 1) + Head;
            CheckLba = CheckLba*CsmBlockIoDev->Drive.MaxSector +  Sector - 1;

//            ASSERT(CheckLba == ShortLba);

            Regs.H.CL = (UINT8) ((Sector & 0x3f) + (UpperCylinder & 0xff));
            Regs.H.DH = (UINT8) (Head & 0x3f);
            Regs.H.CH = (UINT8) (Cylinder & 0xff);

            Regs.X.BX = EFI_OFFSET(mEDDTransferBuffer);
            Regs.X.ES = EFI_SEGMENT(mEDDTransferBuffer);

            TransferByteSize = NumberOfBlocks * BlockSize;
            pBS->CopyMem (mEDDTransferBuffer, Buffer, TransferByteSize);

            CsmBlockIoDev->LegacyBios->Int86 (CsmBlockIoDev->LegacyBios, 0x13, &Regs);
            CarryFlag = (BOOLEAN)Regs.X.Flags.CF;

//                TRACE((-1, "LegacyCsmWriteBlocks: INT 13 03 DL=%02x : CF=%d AH=%02x\n", CsmBlockIoDev->Drive.Number, CarryFlag, Regs.H.AH));

            Retry--;
        } while (CarryFlag && Retry !=0 && Regs.H.AH != ERR_DISK_CHANGED);

        Media->MediaPresent = TRUE;
        if (CarryFlag) {
        //  If we have a carry, figure out the error.
            CsmBlockIoDev->Drive.ErrorCode = Regs.H.AH;
            if (CsmBlockIoDev->Drive.ErrorCode == ERR_DISK_CHANGED) {
                Media->MediaId++;
                Drive = &CsmBlockIoDev->Drive;
                if (GetInt13DeviceParameters(CsmBlockIoDev, Drive)) {
                    if (GetInt13Extensions (CsmBlockIoDev, Drive)) {
                        Media->LastBlock = (EFI_LBA)Drive->Parameters.PhysicalSectors - 1;
                        Media->BlockSize = (UINT32)Drive->Parameters.BytesPerSector;
                    } else {
                        Media->LastBlock = (Drive->MaxHead + 1) * Drive->MaxSector * (Drive->MaxCylinder + 1) - 1;
                        Media->BlockSize = 512;
                     }
                //  The media has changed.
                    Media->ReadOnly = FALSE;
                    pBS->HandleProtocol(CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, (VOID **)&BlockIo);
                    pBS->ReinstallProtocolInterface (CsmBlockIoDev->Handle, &gEfiBlockIoProtocolGuid, BlockIo, BlockIo);
                    Status = EFI_MEDIA_CHANGED;
                    goto Exit;
                }
            } else if (CsmBlockIoDev->Drive.ErrorCode == ERR_WRITE_PROTECTED) {
                Media->ReadOnly = TRUE;
                Status = EFI_WRITE_PROTECTED;
                goto Exit;
            }

            if (Media->RemovableMedia) {
                Media->MediaPresent = FALSE;
            }

            Status = EFI_DEVICE_ERROR;
            goto Exit;
        }
        Media->ReadOnly = FALSE;
        ShortLba = ShortLba + NumberOfBlocks;
        BufferSize = BufferSize - TransferByteSize;
        Buffer = (VOID *)((UINT8 *)Buffer + TransferByteSize);
    }

Exit:
    RestoreHwInterrupt(CsmBlockIoDev);

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        PatchHwInterrupt
//
// Description: Saves HW interrupt vector used by this device
//
// Input:       BlockIo device
//
// Output:      None
//
// Referrals:   CSM_BLOCK_IO_DEV
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
PatchHwInterrupt(
    CSM_BLOCK_IO_DEV    *CsmBlockIoDev
)
{
    UINT32 *ivt = (UINT32*)0;
    if (CsmBlockIoDev->HwInt) {
        gTempHwIntSav = ivt[CsmBlockIoDev->HwInt];
        ivt[CsmBlockIoDev->HwInt] = CsmBlockIoDev->HwIntHandler;
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:    RestoreHwInterrupt
//
// Description: Restores HW interrupt saved by PatchHwInterrupt
//
// Input:       BlockIo device
//
// Output:      None
//
// Referrals:   CSM_BLOCK_IO_DEV, PatchHwInterrupt
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
RestoreHwInterrupt(
    CSM_BLOCK_IO_DEV    *CsmBlockIoDev
)
{
    UINT32 *ivt = (UINT32*)0;
    if (CsmBlockIoDev->HwInt) {
        ivt[CsmBlockIoDev->HwInt] = gTempHwIntSav;
    }
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
