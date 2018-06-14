//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Core/Modules/Recovery/IdeRecovery.c 15    4/02/12 12:54a Srilathasc $
//
// $Revision: 15 $
//
// $Date: 4/02/12 12:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/Recovery/IdeRecovery.c $
// 
// 15    4/02/12 12:54a Srilathasc
// [TAG]  		EIP81405
// [Category]  	Bug Fix
// [Symptom]  	Recovery mode did not work in hard disk
// [RootCause]  	Sufficient timeout to wait for DRQ was not given after
// command was written in AtaPioDataIn()
// [Solution]  	Increase the TIMEOUT to 10 seconds after the command is
// complete 
// 
// [Files]  		IdeRecovery.c
// 
// 14    2/21/12 5:04a Rameshr
// [TAG]  		EIP75596
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Boot to recovery mode without media in the CD drive.First
// time it will fail and next time while inserting Media , still recovery
// not success from CD.
// [RootCause]  	Atapi_DetectMedia will get called and irrespective of
// device status LookedForMedia flag getting updated
// [Solution]  	LookedForMedia flag updated only when the success
// detection of Media in the ODD
// [Files]  		IdeRecovery.c
// 
// 13    7/07/11 3:20a Lavanyap
// [TAG]  		EIP59029 
// [Category]  	Bug Fix
// [Symptom]  	Recovery failed in IDE mode in VIA platform.
// [RootCause]  	BSY/DRQ status checking was not done on the right port.
// [Solution]  	Select the proper device before checking the device
// status.
// [Files]  		IdeRecovery.c
// 
// 12    5/04/11 12:20p Artems
// Bug fix: rollback previous check-in changes
// 
// 11    2/14/11 4:06p Yul
// [TAG]  		EIP38288
// [Category]  	Enhanced
// [Description]  	Klocwork Issues II - Recovery
// 
// 10    1/07/10 12:01p Robert
// In Ata_ReadSectors()  Change the SectorCount variable to UINT16,
// removed the typecasting when setting this variable and added a
// typecasting to UINT8 when call the AtaPioDataIn()
// Removed previous changes for clearer functionality
// 
// 9     1/05/10 12:13p Robert
// in Ata_ReadSectors() if the need arises to call AtaPioDataIn with
// SectorCount == MaxBlock, no data was ever read.  A special case had to
// be created to handle the case when SectorCount == MaxBlock.
// Refer to EIP #33174 for more details
// 
// 8     7/01/09 4:19p Rameshr
// Coding Standard and File header updated.
//
// 7     3/04/09 1:32p Felixp
// Address in the file header is updated.
//
// 6     2/26/09 5:38p Felixp
// File header is updated (no code changes).
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	IdeRecovery.c
//
// Description:	IDE Recovery Implementation
//
//<AMI_FHDR_END>
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: IdeRecovery.c - PEI driver
//
// Description:	Implements EFI_PEI_RECOVERY_BLOCK_IO_PPI for ATA and ATAPI devices.
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#include <PEI.h>
#include <AmiPeiLib.h> 
#include <AmiLib.h> 
#include <Ppi\DeviceRecoveryBlockIo.h>
#include <Ppi\Stall.h>
#include <Protocol\BlockIo.h>
#include <Ppi\AtaController.h>


EFI_GUID gPeiStallPpiGuid              = EFI_PEI_STALL_PPI_GUID;
EFI_GUID gPeiAtaControllerPpiGuid      = PEI_ATA_CONTROLLER_PPI_GUID;
EFI_GUID gPeiBlockIoPpiGuid            = EFI_PEI_VIRTUAL_BLOCK_IO_PPI;
EFI_GUID gIdeRecoveryNativeModePpiGuid = PEI_IDE_RECOVERY_NATIVE_MODE_PPI_GUID;

//----------------------------------------------------------------------

//Atapi command definitions

#define EFI_MIN( a, b )       (((a) < (b)) ? (a) : (b))

#define ATAPI_SIGNATURE 0xEB14

#define CD_ROM_DEVICE 0x5

#define SK_NO_SENSE 0
#define SK_NOT_READY    2
#define SK_UNIT_ATTENTION   6

#define MAX_SENSE_KEY_COUNT 6

#pragma pack(1)

typedef struct
{
    UINT16 GeneralConfiguration_0;
    UINT16 Data_1_58[58];
    UINT32 TotalUserAddressableSectors_60;
    UINT16 Data_61_255[195];
} ATA_IDENTIFY_DATA;

typedef struct
{
    UINT8 PeripheralDeviceType_0 : 5;
    UINT8 Reserved_0             : 3;
    UINT8 Data_1_95[95];
} INQUIRY_DATA;

typedef struct
{
    UINT8 Data_0_1[2];
    UINT8 SenseKey_2 : 4;
    UINT8 Data_2     : 4;
    UINT8 Data_3_6[4];
    UINT8 AdditionalSenseLength_7;
    UINT8 Data_8_11[4];
    UINT8 AdditionalSenseCode_12;
    UINT8 AdditionalSenseCodeQualifier_13;
    UINT8 Data_14_17[4];
} REQUEST_SENSE_DATA;

typedef struct
{
    UINT8 LastLba0;
    UINT8 LastLba1;
    UINT8 LastLba2;
    UINT8 LastLba3;
    UINT8 BlockSize3;
    UINT8 BlockSize2;
    UINT8 BlockSize1;
    UINT8 BlockSize0;
} READ_CAPACITY_DATA;

#pragma pack()

#define PACKET_CMD                0xA0
#define ATA_IDENTIFY_DEVICE_CMD     0xEC
#define ATA_READ_SECTOR_CMD       0x20

#pragma pack(1)

typedef struct
{
    UINT8 OperationCode_0;
    UINT8 Data_1_3[3];
    UINT8 AllocationLength_4;
    UINT8 Data_5_11[7];
} GENERIC_CMD;

typedef struct
{
    UINT8 OperationCode_0;
    UINT8 Data_1;
    UINT8 Lba0;
    UINT8 Lba1;
    UINT8 Lba2;
    UINT8 Lba3;
    UINT8 Data_6;
    UINT8 TransferLengthMSB;
    UINT8 TransferLengthLSB;
    UINT8 Data_9_11[3];
} READ10_CMD;

typedef union
{
    UINT16      Data16[6];
    GENERIC_CMD Cmd;
    READ10_CMD  Read10;
} ATAPI_PACKET_COMMAND;

#pragma pack()

#define TEST_UNIT_READY       0x00
#define REQUEST_SENSE         0x03
#define INQUIRY               0x12
#define READ_CAPACITY         0x25
#define READ_10               0x28

#define DEFAULT_CTL           (0x0a)  // default content of device control register, disable INT
#define DEFAULT_CMD           (0xa0)

#define MAX_ATAPI_BYTE_COUNT  (0xfffe)

#pragma pack(1)

// IDE registers bit definitions

// Err Reg
#define ABRT_ERR  BIT02 //  Aborted Command


// Device/Head Reg
#define LBA_MODE  BIT06

// Status Reg
#define BSY   BIT07 // Controller Busy
#define DRDY  BIT06 // Drive Ready
#define DWF   BIT05 // Drive Write Fault
#define DRQ   BIT03 // Data Request
#define CORR  BIT02 // Corrected Data
#define ERR   BIT00 // Error

#pragma pack()

#define STALL_1_MILLI_SECOND  1000  // stall 1 ms

#define TIMEOUT  1000  // 1 second
#define COMMAND_COMPLETE_TIMEOUT 10000  // 10 seconds
#define LONGTIMEOUT  5000  // 5 seconds

//----------------------------------------------------------------------

typedef enum {
    EnumerateAtapi, EnumerateAta
} ENUMERATE_TYPE;
typedef enum {
    IdeLegacy, IdeNative, IdeMaxMode
} EFI_IDE_MODE;
typedef enum {
    IdePrimary, IdeSecondary, IdeMaxChannel
} EFI_IDE_CHANNEL;
typedef enum {
    IdeMaster, IdeSlave, IdeMaxDevice
} EFI_IDE_DEVICE;

// IDE Registers
typedef union
{
    UINT16 Command;       // when write
    UINT16 Status;        // when read
} IDE_CMD_OR_STATUS;

typedef union
{
    UINT16 Error;         // when read
    UINT16 Feature;       // when write
} IDE_ERROR_OR_FEATURE;

typedef union
{
    UINT16 AltStatus;     // when read
    UINT16 DeviceControl; // when write
} IDE_AltStatus_OR_DeviceControl;


// IDE registers set
typedef struct
{
    UINT16               Data;
    IDE_ERROR_OR_FEATURE Reg1;
    UINT16               SectorCount;
    UINT16               SectorNumber;
    UINT16               CylinderLsb;
    UINT16               CylinderMsb;
    UINT16               Head;
    IDE_CMD_OR_STATUS    Reg;

    IDE_AltStatus_OR_DeviceControl Alt;
    UINT16                         DriveAddress;
} IDE_BASE_REGISTERS;

typedef struct
{
    UINT8                  Device;
    BOOLEAN                LookedForMedia;
    IDE_BASE_REGISTERS     *IdeIoPortRegisters;
    EFI_PEI_BLOCK_IO_MEDIA MediaInfo;
} IDE_RECOVERY_DEVICE_INFO;

#define MAX_DEVICE_COUNT    8

typedef struct
{
    EFI_PEI_RECOVERY_BLOCK_IO_PPI RecoveryBlkIo;

    BOOLEAN                  HaveEnumeratedDevices;
    UINTN                    DeviceCount;
    IDE_RECOVERY_DEVICE_INFO *DeviceInfo[MAX_DEVICE_COUNT];
} IDE_RECOVERY_BLK_IO_DEV;

// IDE registers' fixed address
IDE_BASE_REGISTERS PrimaryChannelLegacyIdeIoPortRegisters = {
    0x1f0, 0x1f1, 0x1f2, 0x1f3, 0x1f4, 0x1f5, 0x1f6, 0x1f7, 0x3f6, 0x3f7
};

IDE_BASE_REGISTERS SecondaryChannelLegacyIdeIoPortRegisters = {
    0x170, 0x171, 0x172, 0x173, 0x174, 0x175, 0x176, 0x177, 0x376, 0x377
};

//AtaAtapiCommonInit should only be called once
BOOLEAN            gHaveCalledAtaAtapiCommonInit = FALSE;

BOOLEAN            gIdeRecoveryNativeModeSupport = FALSE;

IDE_BASE_REGISTERS PrimaryChannelNativeIdeIoPortRegisters = {
    0, 1, 2, 3, 4, 5, 6, 7,
    0, 1
};

IDE_BASE_REGISTERS SecondaryChannelNativeIdeIoPortRegisters = {
    0, 1, 2, 3, 4, 5, 6, 7,
    0, 1
};

IDE_BASE_REGISTERS *gNativeModePortRegsiters;
UINT8              gNativeIdeCount = 0;


//----------------------------------------------------------------------

// PEI Recovery Block I/O PPI

EFI_STATUS AtaAtapiCommonInit (
    IN EFI_PEI_SERVICES **PeiServices );

EFI_STATUS Atapi_GetNumberOfBlockDevices (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                        *NumberBlockDevices );
EFI_STATUS Atapi_GetBlockDeviceMediaInfo (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA       *MediaInfo );
EFI_STATUS Atapi_ReadBlocks (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    IN EFI_PEI_LBA                   StartLba,
    IN UINTN                         BufferSize,
    OUT VOID                         *Buffer );

EFI_STATUS Ata_GetNumberOfBlockDevices (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                        *NumberBlockDevices );
EFI_STATUS Ata_GetBlockDeviceMediaInfo (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA       *MediaInfo );
EFI_STATUS Ata_ReadBlocks (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    IN EFI_PEI_LBA                   StartLba,
    IN UINTN                         BufferSize,
    OUT VOID                         *Buffer );

// Private functions
VOID EnumerateDevices (
    IN OUT IDE_RECOVERY_BLK_IO_DEV *IdeRecoveryBlkIoDev,
    IN ENUMERATE_TYPE              EnumerateType );
BOOLEAN Atapi_DiscoverDevice (
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo );
BOOLEAN Ata_DiscoverDevice (
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo );

EFI_STATUS AtapiPacketCommandIn (
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    IN ATAPI_PACKET_COMMAND     *Packet,
    IN UINT16                   *Buffer,
    IN UINT32                   ByteCount,
    IN UINTN                    TimeoutInMilliSeconds );
EFI_STATUS Inquiry (
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo );
EFI_STATUS Atapi_DetectMedia (
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo );
EFI_STATUS TestUnitReady (
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo );
EFI_STATUS RequestSense (
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    OUT REQUEST_SENSE_DATA      *SenseBuffers,
    OUT UINT8                   *SenseCounts );
EFI_STATUS ReadCapacity (
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo );
EFI_STATUS Atapi_ReadSectors (
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    OUT VOID                    *Buffer,
    IN EFI_PEI_LBA              StartLba,
    IN UINTN                    NumberOfBlocks,
    IN UINTN                    BlockSize );

EFI_STATUS AtaPioDataIn (
    IN IDE_BASE_REGISTERS *IdeIoPortRegisters,
    OUT VOID              *Buffer,
    IN UINT32             ByteCount,
    IN UINT8              SectorCount,
    IN UINT8              SectorNumber,
    IN UINT8              CylinderLsb,
    IN UINT8              CylinderMsb,
    IN UINT8              Device,
    IN UINT8              Command );
EFI_STATUS AtaIdentify (
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    OUT ATA_IDENTIFY_DATA       *AtaIdentifyData );
EFI_STATUS Ata_ReadSectors (
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    OUT VOID                    *Buffer,
    IN EFI_PEI_LBA              StartLba,
    IN UINTN                    NumberOfBlocks,
    IN UINTN                    BlockSize );

EFI_STATUS WaitForBitsToClear (
    IN UINT16 Register,
    IN UINT8  Bits,
    IN UINTN  TimeoutInMilliSeconds );
EFI_STATUS WaitForBSYClear (
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds );
EFI_STATUS DRQClear (
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds );
EFI_STATUS DRQClear2 (
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds );

EFI_STATUS DRQReadyHelper (
    IN UINT16 StatusRegister,
    IN UINT16 ErrorRegister,
    IN UINTN  TimeoutInMilliSeconds );
EFI_STATUS DRQReady (
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds );
EFI_STATUS DRQReady2 (
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds );

EFI_STATUS CheckErrorStatus (
    IN UINT16 StatusReg );

VOID ZeroMem (
    OUT VOID *Buffer,
    IN UINTN Size );

//----------------------------------------------------------------------

EFI_PEI_PPI_DESCRIPTOR   Atapi_PpiDescriptor = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gPeiBlockIoPpiGuid,
    NULL
};

EFI_PEI_PPI_DESCRIPTOR   Ata_PpiDescriptor = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gPeiBlockIoPpiGuid,
    NULL
};

static EFI_PEI_SERVICES  **gPeiServices = NULL;
static EFI_PEI_STALL_PPI *gStallPpi     = NULL;


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Atapi_RecoveryPeimEntry
//
// Description:	Installs EFI_PEI_RECOVERY_BLOCK_IO_PPI for ATAPI devices.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Atapi_RecoveryPeimEntry(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS              Status          = EFI_SUCCESS;
    IDE_RECOVERY_BLK_IO_DEV *Atapi_BlkIoDev = NULL;

    if ( !gPeiServices ) {
        gPeiServices = PeiServices;
    }

    Status = (**PeiServices).AllocatePool( PeiServices, sizeof(IDE_RECOVERY_BLK_IO_DEV), &Atapi_BlkIoDev );

    if ( EFI_ERROR( Status )) {
        return EFI_OUT_OF_RESOURCES;
    }

    Atapi_BlkIoDev->HaveEnumeratedDevices = FALSE;
    Atapi_BlkIoDev->DeviceCount           = 0;

    Atapi_BlkIoDev->RecoveryBlkIo.GetNumberOfBlockDevices = Atapi_GetNumberOfBlockDevices;
    Atapi_BlkIoDev->RecoveryBlkIo.GetBlockDeviceMediaInfo = Atapi_GetBlockDeviceMediaInfo;
    Atapi_BlkIoDev->RecoveryBlkIo.ReadBlocks              = Atapi_ReadBlocks;
    Atapi_PpiDescriptor.Ppi = &Atapi_BlkIoDev->RecoveryBlkIo;

    Status = (**PeiServices).InstallPpi( PeiServices, &Atapi_PpiDescriptor );

    if ( EFI_ERROR( Status )) {
        return EFI_OUT_OF_RESOURCES;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Ata_RecoveryPeimEntry
//
// Description:	Installs EFI_PEI_RECOVERY_BLOCK_IO_PPI for ATA devices.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Ata_RecoveryPeimEntry(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS              Status        = EFI_SUCCESS;
    IDE_RECOVERY_BLK_IO_DEV *Ata_BlkIoDev = NULL;

    if ( !gPeiServices ) {
        gPeiServices = PeiServices;
    }

    Status = (**PeiServices).AllocatePool( PeiServices, sizeof(IDE_RECOVERY_BLK_IO_DEV), &Ata_BlkIoDev );

    if ( EFI_ERROR( Status )) {
        return EFI_OUT_OF_RESOURCES;
    }

    Ata_BlkIoDev->HaveEnumeratedDevices = FALSE;
    Ata_BlkIoDev->DeviceCount           = 0;

    Ata_BlkIoDev->RecoveryBlkIo.GetNumberOfBlockDevices = Ata_GetNumberOfBlockDevices;
    Ata_BlkIoDev->RecoveryBlkIo.GetBlockDeviceMediaInfo = Ata_GetBlockDeviceMediaInfo;
    Ata_BlkIoDev->RecoveryBlkIo.ReadBlocks              = Ata_ReadBlocks;
    Ata_PpiDescriptor.Ppi = &Ata_BlkIoDev->RecoveryBlkIo;

    Status = (**PeiServices).InstallPpi( PeiServices, &Ata_PpiDescriptor );

    if ( EFI_ERROR( Status )) {
        return EFI_OUT_OF_RESOURCES;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	AtaAtapiCommonInit
//
// Description:	Called by Atapi_RecoveryPeimEntry and Ata_RecoveryPeimEntry
//              functions. Initializes stuff, including
//              gIdeRecoveryNativeModeSupport,
//              PrimaryChannelNativeIdeIoPortRegisters,
//              SecondaryChannelNativeIdeIoPortRegisters.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaAtapiCommonInit(
    IN EFI_PEI_SERVICES **PeiServices )
{
    EFI_STATUS                       Status                    = EFI_SUCCESS;
    EFI_STATUS                       LegacyStatus              = EFI_NOT_FOUND;
    PEI_ATA_CONTROLLER_PPI           *AtaControllerPpi         = NULL;
    PEI_IDE_RECOVERY_NATIVE_MODE_PPI *IdeRecoveryNativeModePpi = NULL;
    UINT8 i     = 0;
    UINT8 Index = 0;


    Status = (**PeiServices).LocatePpi( PeiServices, &gPeiStallPpiGuid, 0, NULL, &gStallPpi );

    if ( EFI_ERROR( Status )) {
        return EFI_UNSUPPORTED;
    }

    Status = (**PeiServices).LocatePpi( PeiServices, &gPeiAtaControllerPpiGuid, 0, NULL, &AtaControllerPpi );

    if ( !(EFI_ERROR( Status ))) {
        LegacyStatus = AtaControllerPpi->EnableAtaChannel( PeiServices, AtaControllerPpi, PEI_ICH_IDE_PRIMARY | PEI_ICH_IDE_SECONDARY );
    }

    //
    //Find Number of Native mode IDE ppi installed
    //
    Index = 0;

    do
    {
        Status = (**PeiServices).LocatePpi( PeiServices, &gIdeRecoveryNativeModePpiGuid, Index, NULL, &IdeRecoveryNativeModePpi );

        if ( !(EFI_ERROR( Status ))) {
            Index++;
            gNativeIdeCount++;
        }
    } while ( Status == EFI_SUCCESS );

    //
    //if Legacy mode init fails and if there is no native PPI return with error.
    //
    if ((gNativeIdeCount == 00) && (LegacyStatus != EFI_SUCCESS)) {
        return EFI_UNSUPPORTED;
    }

    Status = (**PeiServices).AllocatePool( PeiServices, sizeof(IDE_BASE_REGISTERS) * 2 * gNativeIdeCount, &gNativeModePortRegsiters );

    //
    //Fill the base address values in gNativeModePortRegsiters
    //
    Index = 0;

    do
    {
        Status = (**PeiServices).LocatePpi( PeiServices, &gIdeRecoveryNativeModePpiGuid, Index, NULL, &IdeRecoveryNativeModePpi );

        if ( !(EFI_ERROR( Status ))) {
            gIdeRecoveryNativeModeSupport             = TRUE;
            gNativeModePortRegsiters[i].Data          = PrimaryChannelNativeIdeIoPortRegisters.Data + IdeRecoveryNativeModePpi->PCMDBarAddress;
            gNativeModePortRegsiters[i].Reg1.Error    = PrimaryChannelNativeIdeIoPortRegisters.Reg1.Error + IdeRecoveryNativeModePpi->PCMDBarAddress;
            gNativeModePortRegsiters[i].SectorCount   = PrimaryChannelNativeIdeIoPortRegisters.SectorCount + IdeRecoveryNativeModePpi->PCMDBarAddress;
            gNativeModePortRegsiters[i].SectorNumber  = PrimaryChannelNativeIdeIoPortRegisters.SectorNumber + IdeRecoveryNativeModePpi->PCMDBarAddress;
            gNativeModePortRegsiters[i].CylinderLsb   = PrimaryChannelNativeIdeIoPortRegisters.CylinderLsb + IdeRecoveryNativeModePpi->PCMDBarAddress;
            gNativeModePortRegsiters[i].CylinderMsb   = PrimaryChannelNativeIdeIoPortRegisters.CylinderMsb + IdeRecoveryNativeModePpi->PCMDBarAddress;
            gNativeModePortRegsiters[i].Head          = PrimaryChannelNativeIdeIoPortRegisters.Head + IdeRecoveryNativeModePpi->PCMDBarAddress;
            gNativeModePortRegsiters[i].Reg.Command   = PrimaryChannelNativeIdeIoPortRegisters.Reg.Command + IdeRecoveryNativeModePpi->PCMDBarAddress;
            gNativeModePortRegsiters[i].Alt.AltStatus = PrimaryChannelNativeIdeIoPortRegisters.Alt.AltStatus + IdeRecoveryNativeModePpi->PCNLBarAddress;
            gNativeModePortRegsiters[i].DriveAddress  = PrimaryChannelNativeIdeIoPortRegisters.DriveAddress + IdeRecoveryNativeModePpi->PCNLBarAddress;

            gNativeModePortRegsiters[i + 1].Data          = SecondaryChannelNativeIdeIoPortRegisters.Data + IdeRecoveryNativeModePpi->SCMDBarAddress;
            gNativeModePortRegsiters[i + 1].Reg1.Error    = SecondaryChannelNativeIdeIoPortRegisters.Reg1.Error + IdeRecoveryNativeModePpi->SCMDBarAddress;
            gNativeModePortRegsiters[i + 1].SectorCount   = SecondaryChannelNativeIdeIoPortRegisters.SectorCount + IdeRecoveryNativeModePpi->SCMDBarAddress;
            gNativeModePortRegsiters[i + 1].SectorNumber  = SecondaryChannelNativeIdeIoPortRegisters.SectorNumber += IdeRecoveryNativeModePpi->SCMDBarAddress;
            gNativeModePortRegsiters[i + 1].CylinderLsb   = SecondaryChannelNativeIdeIoPortRegisters.CylinderLsb + IdeRecoveryNativeModePpi->SCMDBarAddress;
            gNativeModePortRegsiters[i + 1].CylinderMsb   = SecondaryChannelNativeIdeIoPortRegisters.CylinderMsb + IdeRecoveryNativeModePpi->SCMDBarAddress;
            gNativeModePortRegsiters[i + 1].Head          = SecondaryChannelNativeIdeIoPortRegisters.Head + IdeRecoveryNativeModePpi->SCMDBarAddress;
            gNativeModePortRegsiters[i + 1].Reg.Command   = SecondaryChannelNativeIdeIoPortRegisters.Reg.Command + IdeRecoveryNativeModePpi->SCMDBarAddress;
            gNativeModePortRegsiters[i + 1].Alt.AltStatus = SecondaryChannelNativeIdeIoPortRegisters.Alt.AltStatus + IdeRecoveryNativeModePpi->SCNLBarAddress;
            gNativeModePortRegsiters[i + 1].DriveAddress  = SecondaryChannelNativeIdeIoPortRegisters.DriveAddress + IdeRecoveryNativeModePpi->SCNLBarAddress;
            i = i + 2;
            Index++;
        }
    } while ( Status == EFI_SUCCESS );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Atapi_GetNumberOfBlockDevices
//
// Description:	GetNumberOfBlockDevices function of
//              EFI_PEI_RECOVERY_BLOCK_IO_PPI.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Atapi_GetNumberOfBlockDevices(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                        *NumberBlockDevices )
{
    IDE_RECOVERY_BLK_IO_DEV *Atapi_BlkIoDev = NULL;

    if ( This == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    Atapi_BlkIoDev = (IDE_RECOVERY_BLK_IO_DEV*)This;

    if ( !Atapi_BlkIoDev->HaveEnumeratedDevices ) {
        EnumerateDevices( Atapi_BlkIoDev, EnumerateAtapi );
        Atapi_BlkIoDev->HaveEnumeratedDevices = TRUE;
    }
    *NumberBlockDevices = Atapi_BlkIoDev->DeviceCount;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Atapi_GetBlockDeviceMediaInfo
//
// Description:	GetBlockDeviceMediaInfo function of
//              EFI_PEI_RECOVERY_BLOCK_IO_PPI.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Atapi_GetBlockDeviceMediaInfo(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA       *MediaInfo )
{
    IDE_RECOVERY_BLK_IO_DEV *Atapi_BlkIoDev = NULL;
    EFI_STATUS              Status          = EFI_SUCCESS;

    if ((This == NULL) || (MediaInfo == NULL)) {
        return EFI_INVALID_PARAMETER;
    }

    Atapi_BlkIoDev = (IDE_RECOVERY_BLK_IO_DEV*)This;

    if ( !Atapi_BlkIoDev->HaveEnumeratedDevices ) {
        EnumerateDevices( Atapi_BlkIoDev, EnumerateAtapi );
        Atapi_BlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    if ( DeviceIndex > (Atapi_BlkIoDev->DeviceCount - 1)) {
        return EFI_INVALID_PARAMETER;
    }

    if ( !Atapi_BlkIoDev->DeviceInfo[DeviceIndex]->LookedForMedia ) {
        Status = Atapi_DetectMedia( Atapi_BlkIoDev->DeviceInfo[DeviceIndex] );
        
        if ( Status != EFI_SUCCESS ) {
            return EFI_DEVICE_ERROR;
        }
        Atapi_BlkIoDev->DeviceInfo[DeviceIndex]->LookedForMedia = TRUE;
    }

    *MediaInfo = Atapi_BlkIoDev->DeviceInfo[DeviceIndex]->MediaInfo;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Atapi_ReadBlocks
//
// Description:	ReadBlocks function of EFI_PEI_RECOVERY_BLOCK_IO_PPI.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Atapi_ReadBlocks(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    IN EFI_PEI_LBA                   StartLba,
    IN UINTN                         BufferSize,
    OUT VOID                         *Buffer )
{
    EFI_PEI_BLOCK_IO_MEDIA  MediaInfo;
    EFI_STATUS              Status          = EFI_SUCCESS;
    UINTN                   NumberOfBlocks  = 0;
    UINTN                   BlockSize       = 0;
    IDE_RECOVERY_BLK_IO_DEV *Atapi_BlkIoDev = NULL;

    if ( This == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    Atapi_BlkIoDev = (IDE_RECOVERY_BLK_IO_DEV*)This;

    if ( Buffer == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( BufferSize == 0 ) {
        return EFI_SUCCESS;
    }

    if ( !Atapi_BlkIoDev->HaveEnumeratedDevices ) {
        EnumerateDevices( Atapi_BlkIoDev, EnumerateAtapi );
        Atapi_BlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    if ( !Atapi_BlkIoDev->DeviceInfo[DeviceIndex]->LookedForMedia ) {
        Status = Atapi_GetBlockDeviceMediaInfo( PeiServices, This, DeviceIndex, &MediaInfo );

        if ( Status != EFI_SUCCESS ) {
            return Status;
        }
    } else {
        MediaInfo = Atapi_BlkIoDev->DeviceInfo[DeviceIndex]->MediaInfo;
    }

    BlockSize = MediaInfo.BlockSize;

    if ((BufferSize % BlockSize) != 0 ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( !MediaInfo.MediaPresent ) {
        return EFI_NO_MEDIA;
    }

    NumberOfBlocks = BufferSize / BlockSize;

    Status = Atapi_ReadSectors(
        Atapi_BlkIoDev->DeviceInfo[DeviceIndex],
        Buffer,
        StartLba,
        NumberOfBlocks,
        BlockSize
        );

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Ata_GetNumberOfBlockDevices
//
// Description:	GetNumberOfBlockDevices function of
//              EFI_PEI_RECOVERY_BLOCK_IO_PPI.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Ata_GetNumberOfBlockDevices(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                        *NumberBlockDevices )
{
    IDE_RECOVERY_BLK_IO_DEV *Ata_BlkIoDev = NULL;

    if ( This == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    Ata_BlkIoDev = (IDE_RECOVERY_BLK_IO_DEV*)This;

    if ( !Ata_BlkIoDev->HaveEnumeratedDevices ) {
        EnumerateDevices( Ata_BlkIoDev, EnumerateAta );
        Ata_BlkIoDev->HaveEnumeratedDevices = TRUE;
    }
    *NumberBlockDevices = Ata_BlkIoDev->DeviceCount;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Ata_GetBlockDeviceMediaInfo
//
// Description:	GetBlockDeviceMediaInfo function of
//              EFI_PEI_RECOVERY_BLOCK_IO_PPI.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Ata_GetBlockDeviceMediaInfo(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA       *MediaInfo )
{
    IDE_RECOVERY_BLK_IO_DEV *Ata_BlkIoDev          = NULL;
    EFI_STATUS              Status                 = EFI_SUCCESS;
    UINT8                   *Buffer                = NULL;
    UINT32                  SectorOfFirstPartition = 0;
    UINT16                  LowByte                = 0, HighByte = 0, BlockSize = 0;

    if ((This == NULL) || (MediaInfo == NULL)) {
        return EFI_INVALID_PARAMETER;
    }

    Ata_BlkIoDev = (IDE_RECOVERY_BLK_IO_DEV*)This;

    if ( !Ata_BlkIoDev->HaveEnumeratedDevices ) {
        EnumerateDevices( Ata_BlkIoDev, EnumerateAta );
        Ata_BlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    if ( DeviceIndex > (Ata_BlkIoDev->DeviceCount - 1)) {
        return EFI_INVALID_PARAMETER;
    }

    if ( !Ata_BlkIoDev->DeviceInfo[DeviceIndex]->LookedForMedia ) {
        Ata_BlkIoDev->DeviceInfo[DeviceIndex]->LookedForMedia = TRUE;

    }

    *MediaInfo = Ata_BlkIoDev->DeviceInfo[DeviceIndex]->MediaInfo;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Ata_ReadBlocks
//
// Description:	ReadBlocks function of EFI_PEI_RECOVERY_BLOCK_IO_PPI.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Ata_ReadBlocks(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    IN EFI_PEI_LBA                   StartLba,
    IN UINTN                         BufferSize,
    OUT VOID                         *Buffer )
{
    EFI_PEI_BLOCK_IO_MEDIA  MediaInfo;
    EFI_STATUS              Status         = EFI_SUCCESS;
    UINTN                   NumberOfBlocks = 0;
    UINTN                   BlockSize      = 0;
    IDE_RECOVERY_BLK_IO_DEV *Ata_BlkIoDev  = NULL;

    if ( This == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    Ata_BlkIoDev = (IDE_RECOVERY_BLK_IO_DEV*)This;

    if ( Buffer == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( BufferSize == 0 ) {
        return EFI_SUCCESS;
    }

    if ( !Ata_BlkIoDev->HaveEnumeratedDevices ) {
        EnumerateDevices( Ata_BlkIoDev, EnumerateAta );
        Ata_BlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    if ( !Ata_BlkIoDev->DeviceInfo[DeviceIndex]->LookedForMedia ) {
        Status = Ata_GetBlockDeviceMediaInfo(
                                    PeiServices,
                                    This,
                                    DeviceIndex,
                                    &MediaInfo
                                    );

        if ( Status != EFI_SUCCESS ) {
            return Status;
        }
    }  else {
        MediaInfo = Ata_BlkIoDev->DeviceInfo[DeviceIndex]->MediaInfo;
    }

    BlockSize = MediaInfo.BlockSize;

    if ( BufferSize % BlockSize != 0 ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( !MediaInfo.MediaPresent ) {
        return EFI_NO_MEDIA;
    }

    NumberOfBlocks = BufferSize / BlockSize;

    if ( StartLba > MediaInfo.LastBlock ) {
        return EFI_INVALID_PARAMETER;
    }

    if ((StartLba + NumberOfBlocks) > (MediaInfo.LastBlock + 1)) {
        return EFI_INVALID_PARAMETER;
    }

    Status = Ata_ReadSectors(
                        Ata_BlkIoDev->DeviceInfo[DeviceIndex],
                        Buffer,
                        StartLba,
                        NumberOfBlocks,
                        BlockSize
                        );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	EnumerateDevices
//
// Description:	Enumerates Ata or Atapi devices.  Called by
//              Ata_GetNumberOfBlockDevices or
//              Atapi_GetNumberOfBlockDevices.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EnumerateDevices(
    IN IDE_RECOVERY_BLK_IO_DEV *IdeRecoveryBlkIoDev,
    ENUMERATE_TYPE             EnumerateType )
{
    EFI_STATUS               Status      = EFI_SUCCESS;
    UINT8                    MaxModes    = IdeMaxMode;
    EFI_IDE_MODE             Mode        = 0;
    UINT8                    Channel     = 0;
    UINT8                    Device      = 0;
    UINTN                    DeviceCount = 0;
    IDE_RECOVERY_DEVICE_INFO DeviceInfo;
    UINT8                    NativeIdeModeCount = 0;


    if ( !gHaveCalledAtaAtapiCommonInit ) {
        AtaAtapiCommonInit( gPeiServices );
        gHaveCalledAtaAtapiCommonInit = TRUE;
    }

    if ( gIdeRecoveryNativeModeSupport ) {
        //
        //Based on the number of Nativemode PPI maximum mode support is adjusted
        //
        MaxModes = IdeMaxMode + gNativeIdeCount - 1;
    }  else {
        MaxModes = IdeNative;
    }

    for ( Mode = IdeLegacy; Mode < MaxModes; Mode++ ) {
        for ( Channel = IdePrimary; Channel < IdeMaxChannel; Channel++ ) {
            for ( Device = IdeMaster; Device < IdeMaxDevice; Device++ ) {

                DeviceInfo.Device = Device;
                if ( Mode == IdeLegacy ) {
                    if ( Channel == IdePrimary ) {
                        DeviceInfo.IdeIoPortRegisters = &PrimaryChannelLegacyIdeIoPortRegisters;
                    } else { //IdeSecondary
                        DeviceInfo.IdeIoPortRegisters = &SecondaryChannelLegacyIdeIoPortRegisters;
                    }
                } else { //IdeNative
                    if ( Channel == IdePrimary ) {
                        DeviceInfo.IdeIoPortRegisters = &gNativeModePortRegsiters[NativeIdeModeCount];
                    } else { //IdeSecondary
                        DeviceInfo.IdeIoPortRegisters = &gNativeModePortRegsiters[NativeIdeModeCount + 1];
                    }
                }

                if ( EnumerateType == EnumerateAtapi ) {
                    if ( Atapi_DiscoverDevice( &DeviceInfo )) {
                        Status = (**gPeiServices).AllocatePool( gPeiServices, sizeof(IDE_RECOVERY_DEVICE_INFO), &(IdeRecoveryBlkIoDev->DeviceInfo[DeviceCount]));

                        if ( EFI_ERROR( Status )) {
                            return;
                        }
                        DeviceInfo.MediaInfo.MediaPresent                            = FALSE;
                        DeviceInfo.MediaInfo.LastBlock                               = 0;
                        DeviceInfo.LookedForMedia                                    = FALSE;
                        *(IdeRecoveryBlkIoDev->DeviceInfo[DeviceCount])              = DeviceInfo;
                        DeviceCount++;
                    }
                } else { 
                    //
                    //EnumerateAta
                    //
                    if ( Ata_DiscoverDevice( &DeviceInfo )) {
                        Status = (**gPeiServices).AllocatePool( gPeiServices, sizeof(IDE_RECOVERY_DEVICE_INFO), &(IdeRecoveryBlkIoDev->DeviceInfo[DeviceCount]));

                        if ( EFI_ERROR( Status )) {
                            return;
                        }
                        DeviceInfo.MediaInfo.MediaPresent                            = TRUE;
                        DeviceInfo.MediaInfo.BlockSize                               = 0x200;
                        DeviceInfo.LookedForMedia                                    = FALSE;
                        *(IdeRecoveryBlkIoDev->DeviceInfo[DeviceCount])              = DeviceInfo;
                        DeviceCount++;
                    }
                }
            }
        }

        if ( Mode == IdeNative ) {
            //
            //index to the Next native mode PPI base address
            //
            NativeIdeModeCount = NativeIdeModeCount + 2;
        }
    }

    IdeRecoveryBlkIoDev->DeviceCount = DeviceCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Atapi_DiscoverDevice
//
// Description:	Called by EnumerateDevices.  Looks for ATAPI_SIGNATURE.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN Atapi_DiscoverDevice(
    IDE_RECOVERY_DEVICE_INFO *DeviceInfo )
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT8      Device      = DeviceInfo->Device;
    UINT16     HeadReg     = DeviceInfo->IdeIoPortRegisters->Head;
    UINT16     StatusReg   = DeviceInfo->IdeIoPortRegisters->Reg.Status;
    UINT16     CylinderLsb = DeviceInfo->IdeIoPortRegisters->CylinderLsb;
    UINT16     CylinderMsb = DeviceInfo->IdeIoPortRegisters->CylinderMsb;
    UINT8      StatusValue = 0;
    UINT8      Data8       = 0;

    //
    //	Select Device
    //
    IoWrite8( HeadReg, Device << 4 );
    StatusValue = IoRead8( StatusReg );

    if ((StatusValue == 0x7f) || (StatusValue == 0xff)) {
        return FALSE;
    }

    Status      = WaitForBSYClear( DeviceInfo->IdeIoPortRegisters, 31000 );
    StatusValue = IoRead8( StatusReg );

    if ( EFI_ERROR( Status )) {
        return FALSE;
    }

    Data8 = IoRead8( CylinderLsb );

    if ( Data8 == (ATAPI_SIGNATURE & 0xff)) {
        Data8 = IoRead8( CylinderMsb );

        if ( Data8 == (ATAPI_SIGNATURE >> 8)) {
            Status = Inquiry( DeviceInfo );

            if ( !EFI_ERROR( Status )) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Ata_DiscoverDevice
//
// Description:	Called by EnumerateDevices.  Looks at IDENTIFY data.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN Ata_DiscoverDevice(
    IDE_RECOVERY_DEVICE_INFO *DeviceInfo )
{
    EFI_STATUS        Status = EFI_SUCCESS;
    UINT8             Device      = DeviceInfo->Device;
    UINT16            HeadReg     = DeviceInfo->IdeIoPortRegisters->Head;
    UINT16            StatusReg   = DeviceInfo->IdeIoPortRegisters->Reg.Status;
    UINT16            CylinderLsb = DeviceInfo->IdeIoPortRegisters->CylinderLsb;
    UINT16            CylinderMsb = DeviceInfo->IdeIoPortRegisters->CylinderMsb;
    UINT8             StatusValue = 0;
    UINT8             Data8       = 0;

    ATA_IDENTIFY_DATA AtaIdentifyData;


    //
    //Select Device
    //
    IoWrite8( HeadReg, Device << 4 );
    StatusValue = IoRead8( StatusReg );

    if ((StatusValue == 0x7f) || (StatusValue == 0xff)) {
        return FALSE;
    }

    Status      = WaitForBSYClear( DeviceInfo->IdeIoPortRegisters, 31000 );
    StatusValue = IoRead8( StatusReg );

    if ( EFI_ERROR( Status )) {
        return FALSE;
    }

    Data8 = IoRead8( CylinderLsb );

    if ( Data8 == (ATAPI_SIGNATURE & 0xff)) {
        Data8 = IoRead8( CylinderMsb );

        if ( Data8 == (ATAPI_SIGNATURE >> 8)) {
            return FALSE;
        }
    }

    if ( AtaIdentify( DeviceInfo, &AtaIdentifyData ) == EFI_SUCCESS ) {
        if ((AtaIdentifyData.GeneralConfiguration_0 & 0x8000) == 0 ) {
            DeviceInfo->MediaInfo.DeviceType = MaxDeviceType;
            DeviceInfo->MediaInfo.LastBlock  = AtaIdentifyData.TotalUserAddressableSectors_60;
            return TRUE;
        }
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	AtapiPacketCommandIn
//
// Description:	Executes various ATAPI packet commands
//      (TEST_UNIT_READY, INQUIRY, REQUEST_SENSE, READ_CAPACITY, etc).
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtapiPacketCommandIn(
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    IN ATAPI_PACKET_COMMAND     *Packet,
    IN UINT16                   *Buffer,
    IN UINT32                   ByteCount,
    IN UINTN                    TimeoutInMilliSeconds )
{
    IDE_BASE_REGISTERS *IdeIoPortRegisters = DeviceInfo->IdeIoPortRegisters;

    UINT8              Device           = DeviceInfo->Device;
    UINT16             StatusReg        = IdeIoPortRegisters->Reg.Status;
    UINT16             HeadReg          = IdeIoPortRegisters->Head;
    UINT16             CommandReg       = IdeIoPortRegisters->Reg.Command;
    UINT16             FeatureReg       = IdeIoPortRegisters->Reg1.Feature;
    UINT16             CylinderLsbReg   = IdeIoPortRegisters->CylinderLsb;
    UINT16             CylinderMsbReg   = IdeIoPortRegisters->CylinderMsb;
    UINT16             DeviceControlReg = IdeIoPortRegisters->Alt.DeviceControl;
    UINT16             DataReg          = IdeIoPortRegisters->Data;
    EFI_STATUS         Status           = EFI_SUCCESS;
    UINT32             Count            = 0;
    UINT16             *CommandIndex    = NULL;
    UINT16             *ptrBuffer       = Buffer;
    UINT32             Index            = 0;
    UINT8              StatusValue      = 0;
    UINT32             WordCount        = 0;

    //
    // required transfer data in word unit.
    //
    UINT32             RequiredWordCount = 0;

    //
    // actual transfer data in word unit.
    //
    UINT32             ActualWordCount = 0;

    //
    // Select device via Device/Head Register.
    // DEFAULT_CMD: 0xa0 (1010,0000)
    //
    IoWrite8( HeadReg, (UINT8) ((Device << 4) | DEFAULT_CMD ));

    //
    // Set all the command parameters by fill related registers.
    // Before write to all the following registers, BSY and DRQ must be 0.
    //
    if ( DRQClear2(
             DeviceInfo->IdeIoPortRegisters,
             TIMEOUT
             ) != EFI_SUCCESS ) {
        return EFI_DEVICE_ERROR;
    }


    //
    // No OVL; No DMA
    //
    IoWrite8( FeatureReg, 0x00 );

    //
    // set the transfersize to MAX_ATAPI_BYTE_COUNT to let the device
    // determine how many data should be transfered.
    //
    IoWrite8( CylinderLsbReg, (UINT8) ( MAX_ATAPI_BYTE_COUNT & 0x00ff ));
    IoWrite8( CylinderMsbReg, (UINT8) ( MAX_ATAPI_BYTE_COUNT >> 8 ));

    //
    //  DEFAULT_CTL:0x0a (0000,1010)
    //  Disable interrupt
    //
    IoWrite8( DeviceControlReg, DEFAULT_CTL );

    //
    // Send Packet command to inform device
    // that the following data bytes are command packet.
    //
    IoWrite8( CommandReg, PACKET_CMD );

    Status = DRQReady( IdeIoPortRegisters, TimeoutInMilliSeconds );

    if ( Status != EFI_SUCCESS ) {
        return Status;
    }
    //
    // Send out command packet
    //
    CommandIndex = Packet->Data16;

    for ( Count = 0; Count < 6; Count++, CommandIndex++ ) {
        IoWrite16( DataReg, *CommandIndex );
        gStallPpi->Stall( gPeiServices, gStallPpi, 10 );
    }

    StatusValue = IoRead8( StatusReg );
    WaitForBSYClear( IdeIoPortRegisters, LONGTIMEOUT );
    StatusValue = IoRead8( StatusReg );

    if ((StatusValue & ERR) == ERR ) {
        //
        // Trouble! Something's wrong here... Wait some time and return. 3 second is
        // supposed to be long enough for a device reset latency or error recovery
        //
        gStallPpi->Stall( gPeiServices, gStallPpi, 100000 );

        return EFI_DEVICE_ERROR;
    }

    if ( Buffer == NULL || ByteCount == 0 ) {
        return EFI_SUCCESS;
    }
    //
    // call PioReadWriteData() function to get
    // requested transfer data form device.
    //
    ptrBuffer         = Buffer;
    RequiredWordCount = ByteCount / 2;
    //
    // ActuralWordCount means the word count of data really transfered.
    //
    ActualWordCount = 0;

    Status = EFI_SUCCESS;
    while ((Status == EFI_SUCCESS) && (ActualWordCount < RequiredWordCount))
    {
        //
        // before each data transfer stream, the host should poll DRQ bit ready,
        // which informs device is ready to transfer data.
        //
        if ( DRQReady2( IdeIoPortRegisters, TimeoutInMilliSeconds ) != EFI_SUCCESS ) {
            return CheckErrorStatus( StatusReg );
        }
        //
        // read Status Register will clear interrupt
        //
        StatusValue = IoRead8( StatusReg );

        //
        // get current data transfer size from Cylinder Registers.
        //
        WordCount = (( IoRead8( CylinderMsbReg ) << 8) | IoRead8( CylinderLsbReg )) & 0xffff;
        WordCount /= 2;

        //
        // perform a series data In/Out.
        //
        for ( Index = 0; (Index < WordCount) && (ActualWordCount < RequiredWordCount); Index++, ActualWordCount++ )
        {
            *ptrBuffer = IoRead16( DataReg );

            ptrBuffer++;
        }

        if (((GENERIC_CMD*) Packet)->OperationCode_0 == REQUEST_SENSE && ActualWordCount >= 4 ) {
            RequiredWordCount = EFI_MIN( RequiredWordCount,
                                (UINT32) ( 4 + (((REQUEST_SENSE_DATA*) Buffer)->AdditionalSenseLength_7 / 2))
                                );
        }
    }
    //
    // After data transfer is completed, normally, DRQ bit should clear.
    //
    Status = DRQClear2( IdeIoPortRegisters, TimeoutInMilliSeconds );

    if ( Status != EFI_SUCCESS ) {
        return EFI_DEVICE_ERROR;
    }
    //
    // read status register to check whether error happens.
    //
    Status = CheckErrorStatus( StatusReg );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Inquiry
//
// Description:	ATAPI packet command INQUIRY.   Uses AtapiPacketCommandIn.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Inquiry(
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo )
{
    ATAPI_PACKET_COMMAND Packet;
    EFI_STATUS           Status;
    INQUIRY_DATA         Idata;

    ZeroMem( &Packet, sizeof (ATAPI_PACKET_COMMAND));

    Packet.Cmd.OperationCode_0    = INQUIRY;
    Packet.Cmd.AllocationLength_4 = sizeof (INQUIRY_DATA);

    Status = AtapiPacketCommandIn(
        DeviceInfo,
        &Packet,
        (UINT16*)(&Idata),
        sizeof (INQUIRY_DATA),
        TIMEOUT
        );

    if ( Status != EFI_SUCCESS ) {
        return EFI_DEVICE_ERROR;
    }

    if ( Idata.PeripheralDeviceType_0 == CD_ROM_DEVICE ) {
        DeviceInfo->MediaInfo.DeviceType   = IdeCDROM;
        DeviceInfo->MediaInfo.MediaPresent = FALSE;
        DeviceInfo->MediaInfo.LastBlock    = 0;
        DeviceInfo->MediaInfo.BlockSize    = 0x800;
        return EFI_SUCCESS;
    } else {
        return EFI_UNSUPPORTED;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Atapi_DetectMedia
//
// Description:
//      -Loop: Issues ATAPI packet command TEST_UNIT_READY.
//      If this is not successful, then look at SENSE data.
//      If you get the sense data for (1) becoming ready, (2) media
//      changed, or (3) power on reset, then stall for some time and
//      continue looping with TEST_UNIT_READY and REQUEST_SENSE.
//      -If TEST_UNIT_READY is successful, then issue READ_CAPACITY
//      packet command, which should get device info.
//      -If TEST_UNIT_READY is not succesful or if the SENSE data
//      contains some other error (not one of the three listed above),
//      then return an error.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Atapi_DetectMedia(
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo )
{
    UINTN              Index = 0;
    REQUEST_SENSE_DATA SenseBuffers[MAX_SENSE_KEY_COUNT];
    EFI_STATUS         Status        = EFI_SUCCESS;
    UINT8              SenseCounts   = 0;
    BOOLEAN            DeviceIsReady = FALSE;

    DeviceInfo->MediaInfo.MediaPresent = FALSE;
    DeviceInfo->MediaInfo.LastBlock    = 0;

    DeviceIsReady = FALSE;

    for ( Index = 0; Index < 50; Index++ ) {
        Status = TestUnitReady( DeviceInfo );

        if ( Status == EFI_SUCCESS ) {
            DeviceIsReady = TRUE;
            break;
        }

        SenseCounts = MAX_SENSE_KEY_COUNT;
        Status      = RequestSense( DeviceInfo, SenseBuffers, &SenseCounts );

        if ( SenseCounts == 0 ) {
            gStallPpi->Stall( gPeiServices, gStallPpi, 250000 );
            continue;
        }

        if (((SenseBuffers[0].SenseKey_2 == SK_NOT_READY) && (SenseBuffers[0].AdditionalSenseCode_12 == 4) && (SenseBuffers[0].AdditionalSenseCodeQualifier_13 == 1))     // Becoming ready
            || ((SenseBuffers[0].SenseKey_2 == SK_UNIT_ATTENTION) && (SenseBuffers[0].AdditionalSenseCode_12 == 0x28) && (SenseBuffers[0].AdditionalSenseCodeQualifier_13 == 0))     // Media Changed
            || ((SenseBuffers[0].SenseKey_2 == SK_UNIT_ATTENTION) && (SenseBuffers[0].AdditionalSenseCode_12 == 0x29) && (SenseBuffers[0].AdditionalSenseCodeQualifier_13 == 0))) {   // Power on Reset
            gStallPpi->Stall( gPeiServices, gStallPpi, 250000 );
        } else {
            break;
        }
    }

    if ( DeviceIsReady ) {
        Status = ReadCapacity( DeviceInfo );
        return Status;
    }

    return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	TestUnitReady
//
// Description:	ATAPI command TEST_UINT_READY.  Uses AtapiPacketCommandIn.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TestUnitReady(
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo )
{
    ATAPI_PACKET_COMMAND Packet;
    EFI_STATUS           Status;

    ZeroMem( &Packet, sizeof (ATAPI_PACKET_COMMAND));
    Packet.Cmd.OperationCode_0 = TEST_UNIT_READY;

    Status = AtapiPacketCommandIn( DeviceInfo, &Packet, NULL, 0, TIMEOUT );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	RequestSense
//
// Description:	Send Request sense command
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RequestSense(
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    IN REQUEST_SENSE_DATA           *SenseBuffers,
    IN OUT UINT8                    *SenseCounts )
{
    EFI_STATUS           Status = EFI_SUCCESS;
    REQUEST_SENSE_DATA   *Sense = SenseBuffers;
    ATAPI_PACKET_COMMAND Packet;

    ZeroMem( SenseBuffers, sizeof (REQUEST_SENSE_DATA) * (*SenseCounts));

    ZeroMem( &Packet,      sizeof (ATAPI_PACKET_COMMAND));
    Packet.Cmd.OperationCode_0    = REQUEST_SENSE;
    Packet.Cmd.AllocationLength_4 = sizeof (REQUEST_SENSE_DATA);

    *SenseCounts = 0;

    while ( TRUE ) {
        Status = AtapiPacketCommandIn(
            DeviceInfo,
            &Packet,
            (UINT16*) Sense,
            sizeof (REQUEST_SENSE_DATA),
            TIMEOUT
            );

        if ( Status != EFI_SUCCESS ) {
            if ( *SenseCounts == 0 ) {
                return EFI_DEVICE_ERROR;
            } else {
                return EFI_SUCCESS;
            }
        }

        (*SenseCounts)++;

        if ( *SenseCounts == MAX_SENSE_KEY_COUNT ) {
            return EFI_SUCCESS;
        }

        //
        // We limit MAX sense data count to 20 in order to avoid dead loop. Some
        // incompatible ATAPI devices don't retrive NO_SENSE when there is no media.
        // In this case, dead loop occurs if we don't have a gatekeeper. 20 is
        // supposed to be large enough for any ATAPI device.
        // (Actually 6, not 20).
        if ( Sense->SenseKey_2 != SK_NO_SENSE ) {
            Sense++;
        } else {
            return EFI_SUCCESS;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	ReadCapacity
//
// Description:	ATAPI packet command READ_CAPACITY.
//      Uses AtapiPacketCommandIn.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReadCapacity(
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo )
{
    EFI_STATUS           Status;
    ATAPI_PACKET_COMMAND Packet;
    READ_CAPACITY_DATA   Data;

    ZeroMem( &Data,   sizeof (Data));

    if ( DeviceInfo->MediaInfo.DeviceType == IdeCDROM ) {
        ZeroMem( &Packet, sizeof (ATAPI_PACKET_COMMAND));
        Packet.Cmd.OperationCode_0 = READ_CAPACITY;
        Status                     = AtapiPacketCommandIn(
                                                    DeviceInfo,
                                                    &Packet,
                                                    (UINT16*)(&Data),
                                                    sizeof (READ_CAPACITY_DATA),
                                                    LONGTIMEOUT
                                                    );

        if ( Status == EFI_SUCCESS ) {
            if ( DeviceInfo->MediaInfo.DeviceType == IdeCDROM ) {
                DeviceInfo->MediaInfo.LastBlock    = (Data.LastLba0 << 24) | (Data.LastLba1 << 16) | (Data.LastLba2 << 8) | Data.LastLba3;
                DeviceInfo->MediaInfo.MediaPresent = TRUE;
                DeviceInfo->MediaInfo.BlockSize    = 0x800;
            }
            return EFI_SUCCESS;
        } else {
            return EFI_DEVICE_ERROR;
        }
    } else {
        return EFI_UNSUPPORTED;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Atapi_ReadSectors
//
// Description:	Helper function called by Atapi_ReadBlocks.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Atapi_ReadSectors(
    IN OUT IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    IN VOID                         *Buffer,
    IN EFI_PEI_LBA                  StartLba,
    IN UINTN                        NumberOfBlocks,
    IN UINTN                        BlockSize )
{
    ATAPI_PACKET_COMMAND Packet;
    READ10_CMD           *Read10Packet   = NULL;
    EFI_STATUS           Status          = EFI_SUCCESS;
    UINTN                BlocksRemaining = 0;
    UINT32               Lba32           = 0;
    UINT32               ByteCount       = 0;
    UINT16               SectorCount     = 0;
    VOID                 *ptrBuffer      = NULL;
    UINT16               MaxBlock        = 0;

    ZeroMem( &Packet, sizeof (ATAPI_PACKET_COMMAND));

    Read10Packet = &Packet.Read10;
    Lba32        = (UINT32) StartLba;
    ptrBuffer    = Buffer;

    //
    // limit the data bytes that can be transfered by one Read(10) Command
    //
    MaxBlock = (UINT16) ( 0x10000 / BlockSize );
    //
    // (64k bytes)
    //
    BlocksRemaining = NumberOfBlocks;

    Status = EFI_SUCCESS;
    while ( BlocksRemaining > 0 ) {
        if ( BlocksRemaining <= MaxBlock ) {
            SectorCount = (UINT16) BlocksRemaining;
        } else {
            SectorCount = MaxBlock;
        }

        Read10Packet->OperationCode_0 = READ_10;

        //
        // Lba0 ~ Lba3 specify the start logical block address of the data transfer.
        // Lba0 is MSB, Lba3 is LSB
        //
        Read10Packet->Lba3 = (UINT8) ( Lba32 & 0xff );
        Read10Packet->Lba2 = (UINT8) ( Lba32 >> 8 );
        Read10Packet->Lba1 = (UINT8) ( Lba32 >> 16 );
        Read10Packet->Lba0 = (UINT8) ( Lba32 >> 24 );

        //
        // TransferLengthMSB ~ TransferLengthLSB specify the transfer length in block unit.
        //
        Read10Packet->TransferLengthLSB = (UINT8) ( SectorCount & 0xff );
        Read10Packet->TransferLengthMSB = (UINT8) ( SectorCount >> 8 );

        ByteCount = (UINT32) ( SectorCount * BlockSize );

        Status = AtapiPacketCommandIn(
            DeviceInfo,
            &Packet,
            (UINT16*) ptrBuffer,
            ByteCount,
            LONGTIMEOUT
            );

        if ( Status != EFI_SUCCESS ) {
            return Status;
        }

        Lba32           += SectorCount;
        ptrBuffer        = (UINT8*) ptrBuffer + SectorCount * BlockSize;
        BlocksRemaining -= SectorCount;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	AtaPioDataIn
//
// Description:	Does ATA protocol Pio In with data.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaPioDataIn(
    IN IDE_BASE_REGISTERS *IdeIoPortRegisters,
    OUT VOID              *Buffer,
    IN UINT32             ByteCount,
    IN UINT8              SectorCount,
    IN UINT8              SectorNumber,
    IN UINT8              CylinderLsb,
    IN UINT8              CylinderMsb,
    IN UINT8              Device,
    IN UINT8              Command )
{
    EFI_STATUS Status = EFI_SUCCESS;

    UINT16     HeadReg           = IdeIoPortRegisters->Head;
    UINT16     SectorCountReg    = IdeIoPortRegisters->SectorCount;
    UINT16     SectorNumberReg   = IdeIoPortRegisters->SectorNumber;
    UINT16     CylinderLsbReg    = IdeIoPortRegisters->CylinderLsb;
    UINT16     CylinderMsbReg    = IdeIoPortRegisters->CylinderMsb;
    UINT16     CommandReg        = IdeIoPortRegisters->Reg.Command;
    UINT16     AltStatusRegister = IdeIoPortRegisters->Alt.AltStatus;
    UINT16     StatusReg         = IdeIoPortRegisters->Reg.Status;
    UINT16     DataReg           = IdeIoPortRegisters->Data;

    UINT32     WordCount = 0;
    UINT32     Increment = 0;
    UINT32     Index     = 0;
    UINT16     *Buffer16 = (UINT16*)Buffer;
    ;

    IoWrite8( HeadReg, Device );

    Status = WaitForBSYClear( IdeIoPortRegisters, TIMEOUT );

    if ( Status != EFI_SUCCESS ) {
        return EFI_DEVICE_ERROR;
    }

    Status = DRQClear2( IdeIoPortRegisters, TIMEOUT );

    if ( Status != EFI_SUCCESS ) {
        return EFI_DEVICE_ERROR;
    }

    Status = DRQClear2( IdeIoPortRegisters, TIMEOUT );

    if ( Status != EFI_SUCCESS ) {
        return EFI_DEVICE_ERROR;
    }

    IoWrite8( SectorCountReg,  SectorCount );
    IoWrite8( SectorNumberReg, SectorNumber );
    IoWrite8( CylinderLsbReg,  CylinderLsb );
    IoWrite8( CylinderMsbReg,  CylinderMsb );

    IoWrite8( CommandReg,      Command );

    IoRead8( AltStatusRegister );

    Increment = 256;
    WordCount = 0;

    while ( WordCount < ByteCount / 2 ) {
        Status = DRQReady2( IdeIoPortRegisters, COMMAND_COMPLETE_TIMEOUT );

        if ( Status != EFI_SUCCESS ) {
            return Status;
        }

        if ( CheckErrorStatus( StatusReg ) != EFI_SUCCESS ) {
            return EFI_DEVICE_ERROR;
        }

        if ((WordCount + Increment) > ByteCount / 2 ) {
            Increment = ByteCount / 2 - WordCount;
        }

        for ( Index = 0; Index < Increment; Index++ )
        {
            *Buffer16++ = IoRead16( DataReg );
        }

        WordCount += Increment;
    }

    Status = DRQClear( IdeIoPortRegisters, TIMEOUT );

    if ( Status != EFI_SUCCESS ) {
        return CheckErrorStatus( StatusReg );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	AtaIdentify
//
// Description:	ATA Identify command.  Uses AtaPioDataIn
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AtaIdentify(
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    OUT ATA_IDENTIFY_DATA       *AtaIdentifyData )
{
    return       AtaPioDataIn( DeviceInfo->IdeIoPortRegisters,
                               AtaIdentifyData,
                               sizeof (ATA_IDENTIFY_DATA),
                               0,
                               0,
                               0,
                               0,
                               DeviceInfo->Device << 4,
                               ATA_IDENTIFY_DEVICE_CMD
                               );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	Ata_ReadSectors
//
// Description:	Helper function called by Ata_ReadBlocks.
//
// Input:
//  IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo - pointer to the device info structure
//  IN OUT VOID *Buffer - Pointer to a buffer that will hold the Data that is read
//  IN EFI_PEI_LBA StartLba - the first LBA to read
//  IN UINTN NumberOfBlocks - total number of blocks to read
//  IN UINTN BlockSize - size of the blocks to be read
//
// Output:
//  EFI_SUCCESS - Read happened correctly
//  OTHER - any valid error from AtaPioDataIn() 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Ata_ReadSectors(
    IN IDE_RECOVERY_DEVICE_INFO *DeviceInfo,
    IN OUT VOID                 *Buffer,
    IN EFI_PEI_LBA              StartLba,
    IN UINTN                    NumberOfBlocks,
    IN UINTN                    BlockSize )
{
    EFI_STATUS Status          = EFI_SUCCESS;
    UINTN      BlocksRemaining = 0;
    UINT32     Lba32           = 0;
    UINT8      LbaLow          = 0;
    UINT8      LbaMid          = 0;
    UINT8      LbaHigh         = 0;
    UINT32     ByteCount       = 0;
    UINT16     SectorCount     = 0;
    VOID       *ptrBuffer      = NULL;
    UINT16     MaxBlock        = 0;
    UINT8      Dev             = 0;
    UINT8      Device          = 0;

    Lba32     = (UINT32) StartLba;
    ptrBuffer = Buffer;

    MaxBlock = (UINT16) ( 0x20000 / BlockSize );

    BlocksRemaining = NumberOfBlocks;

    Status = EFI_SUCCESS;
    Dev    = (DeviceInfo->Device << 4) | LBA_MODE;
    while ( BlocksRemaining > 0 ) {
        if ( BlocksRemaining < MaxBlock ) {
            SectorCount = BlocksRemaining;
        } else {
            SectorCount = MaxBlock;
        }
        LbaLow  = (UINT8) ( Lba32 & 0xff );
        LbaMid  = (UINT8) ( Lba32 >> 8 );
        LbaHigh = (UINT8) ( Lba32 >> 16 );

        ByteCount = (UINT32) ( SectorCount * BlockSize );

        Dev   |= (Lba32 >> 24);
        Status = AtaPioDataIn( DeviceInfo->IdeIoPortRegisters,
                               ptrBuffer,
                               ByteCount,
                               (UINT8) SectorCount, //sector count
                               LbaLow, //sector number
                               LbaMid, //lsb
                               LbaHigh, //msb
                               Dev,
                               ATA_READ_SECTOR_CMD
                               );

        if ( Status != EFI_SUCCESS ) {
            return Status;
        }

        Lba32           += SectorCount;
        ptrBuffer        = (UINT8*) ptrBuffer + SectorCount * BlockSize;
        BlocksRemaining -= SectorCount;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	WaitForBitsToClear
//
// Description:	Helper functin used by WaitForBSYClear, DRQClear, DRQClear2.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WaitForBitsToClear(
    UINT16 Register,
    UINT8  Bits,
    UINTN  TimeoutInMilliSeconds )
{
    UINTN Delay       = ((TimeoutInMilliSeconds * STALL_1_MILLI_SECOND) / 250) + 1;
    UINT8 StatusValue = 0;

    do {
        StatusValue = IoRead8( Register );

        if ((StatusValue & Bits) == 0x00 ) {
            break;
        }

        gStallPpi->Stall( gPeiServices, gStallPpi, 250 );

        Delay--;
    } while ( Delay );

    if ( Delay == 0 ) {
        return EFI_TIMEOUT;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	WaitForBSYClear
//
// Description: Wait for busy bit to clear
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WaitForBSYClear(
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds )
{
    return WaitForBitsToClear( IdeIoRegisters->Reg.Status, BSY, TimeoutInMilliSeconds );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	DRQClear
//
// Description: Wait for the DRQ bit clear
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DRQClear(
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds )
{
    return WaitForBitsToClear( IdeIoRegisters->Reg.Status, DRQ | BSY, TimeoutInMilliSeconds );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	DRQClear2
//
// Description: Wait for the DRQ bit clear in Alternate Status Reg
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DRQClear2(
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds )
{
    return WaitForBitsToClear( IdeIoRegisters->Alt.AltStatus, DRQ | BSY, TimeoutInMilliSeconds );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	DRQReadyHelper
//
// Description:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DRQReadyHelper(
    UINT16   StatusRegister,
    UINT16   ErrorRegister,
    IN UINTN TimeoutInMilliSeconds )
{
    UINTN Delay       = ((TimeoutInMilliSeconds * STALL_1_MILLI_SECOND) / 250) + 1;
    UINT8 StatusValue = 0;
    UINT8 ErrValue    = 0;

    do
    {
        //
        //  read Status Register will clear interrupt
        //
        StatusValue =  IoRead8( StatusRegister );

        //
        //  BSY==0,DRQ==1
        //
        if ((StatusValue & (BSY | DRQ)) == DRQ ) {
            break;
        }

        if ((StatusValue & (BSY | ERR)) == ERR ) {
            ErrValue = IoRead8( ErrorRegister );

            if ((ErrValue & ABRT_ERR) == ABRT_ERR ) {
                return EFI_ABORTED;
            }
        }

        gStallPpi->Stall( gPeiServices, gStallPpi, 250 );

        Delay--;
    } while ( Delay );

    if ( Delay == 0 ) {
        return EFI_TIMEOUT;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	DRQReady
//
// Description: Wait for the DRQ ready 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DRQReady(
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds )
{
    return DRQReadyHelper( IdeIoRegisters->Reg.Status, IdeIoRegisters->Reg1.Error, TimeoutInMilliSeconds );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	DRQReady2
//
// Description: Wait for the DRQ Ready in Alternate Status Reg
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DRQReady2(
    IN IDE_BASE_REGISTERS *IdeIoRegisters,
    IN UINTN              TimeoutInMilliSeconds )
{
    return DRQReadyHelper( IdeIoRegisters->Alt.AltStatus, IdeIoRegisters->Reg1.Error, TimeoutInMilliSeconds );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	CheckErrorStatus
//
// Description: Check for the Errros.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckErrorStatus(
    IN UINT16 StatusReg )
{
    UINT8 StatusValue = IoRead8( StatusReg );

    if ((StatusValue & (ERR | DWF | CORR)) == 0 ) {
        return EFI_SUCCESS;
    }

    return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	ZeroMem
//
// Description: Clear the Memory
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static
VOID ZeroMem(
    IN VOID  *Buffer,
    IN UINTN Size )
{
    UINT8 *ptr;

    ptr = Buffer;
    while ( Size-- )
    {
        *(ptr++) = 0;
    }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
