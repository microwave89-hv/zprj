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
// $Header: /Alaska/SOURCE/Core/Modules/IdeBus/IdeBus.h 29    7/20/12 6:14a Anandakrishnanl $
//
// $Revision: 29 $
//
// $Date: 7/20/12 6:14a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/IdeBus/IdeBus.h $
// 
// 29    7/20/12 6:14a Anandakrishnanl
// [TAG]  		EIP88683
// [Category]  	New Feature
// [Description]  	EFI_ATA_PASS_THRU_PROTOCOL Support for Aptio IDE
// [Files]  		AhciBus.c
// AhciBus.h
// AInt13.h
// IdeBus.c
// IdeBus.h
// PIDEBus.h
// PAhciBus.h
// AtaPassThru.sdl
// AtaPassThru.mak	
// AtaPassThru.c	
// AtaPassThruSupport.h
// AtaPassThru.chm
// 
// 28    12/05/11 6:12p Rajkumarkc
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
// 27    9/27/11 3:14a Rajeshms
// [TAG]  		EIP69295
// [Category]  	Improvement
// [Description]  	The Timeout values used by IDE and AHCI drivers are
// made as SDL tokens, so that the timeout values can be varied.
// [Files]  		IdeBusBoard.c, CORE_DXE.sdl, AhciSmm.h, AhciBus.h, IDESMM.h,
// Ata.c, Atapi.c, IdeBus.c, IdeBus.h, IdeBusMaster.c, IdeBusBoard.h
// 
// 26    4/12/11 4:06a Rameshr
// [TAG]- EIP 53710
// [Category]- New Feature
// [Description]- ATAPI ODD loading type information added into ATAPI
// device structure 
// [Files]- Atapi.c, Idebus.c, IdeBus.h 
// 
// 25    12/23/10 3:55a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 24    11/08/10 6:11p Felixp
// The Core source files are updated to remove upper ASCII characters
// (above 128) 
// from the comment blocks. The characters caused build errors 
// with Japanese version of Microsoft compiler.
// 
// 23    8/25/10 4:14a Rameshr
// New Feature: EIP 37748
// Description: Move all the IDEBus Source driver SDL token into IdeBus
// Bin Driver.
// FilesModified: Ata.c, Atapi.c, idebus.c, IdeBus.h,
// IdebuscomponentName.c, IdeBusmaster.c IdeBusSrc.mak IdebusSrc.sdl
// IdeHpa.c, IdePowerManagement.c
// 
// 22    7/01/09 12:22p Rameshr
// Coding Standard and File header updated.
//
// 21    6/22/09 11:39a Rameshr
// Odd Type information Saved in Atapi Device Structure.
// EIP:21548
//
// 20    5/01/09 5:17p Felixp
// Prototype for WaitForCmdCompletionWithTimeOutValue is added to resolve
// compilation error.
//
// 19    7/03/08 5:40p Anandakrishnanl
// Removed Smart related Definitions and Function Prototypes since Smart
// feature is in Seperate Driver Now.
//
// 16    28/02/08 7:00p Anandakrishnanl
// Removed few definitions and function declarations and moved to
// IdeSecurity module.
//
// 15    10/23/07 4:16p Felixp
// IDE Security support moved from Sources to Binary
//
// 14    14/08/07 1:51p Anandakrishnanl
// Changes made for password storing in NVRAM which converts HDD dataInfo
// to string in ConvertHddDataIdToString function.
//
// 13    22/06/07 12:40p Anandakrishnanl
// HardDisk Security Support Module Added.
// Need ACPI Module and SB Module and under Core\Include we updated
// Setup.h.
// Also New IdeBus bin module.
//
// 12    13/04/07 3:02p Anandakrishnanl
// Ide Bus Module - Update source files to comply with "AMI coding
// standard"!!!
//
// 11    2/12/07 3:39p Pats
// Increased POWERON_BUSY_CLEAR_TIMEOUT to 10 sec.
//
// 10    11/17/06 2:58p Ambikas
//
// 9     10/27/06 4:20p Felixp
// Reverted back to the previous version
//
// 7     8/24/06 9:30a Felixp
// x64 support (bug fixes)
//
// 5     3/13/06 2:20a Felixp
//
// 4     1/09/06 11:36a Felixp
//
// 2     12/14/05 3:02p Srinin
// HDD password related equates added.
//
// 1     12/01/05 9:43a Felixp
//
// 10    11/03/05 10:41a Srinin
// VC7 compilation error fixed.
//
// 9     3/04/05 11:33a Mandal
//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	IdeBus.h
//
// Description:	This file contains the Includes, Definitions, typedefs,
//		        Variable and External Declarations, Structure and
//              function prototypes needed for the IdeBus driver
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#ifndef _IdeBus_
#define _IdeBus_

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Token.h>
#include <Dxe.h>
#include <AmiDxeLib.h>
#include "Protocol\PciIo.h"
#include "Protocol\DevicePath.h"
#include "protocol\DriverBinding.h"
#include "protocol\BlockIo.h"
#include "Protocol\PDiskInfo.h"
#include "Protocol\PIDEController.h"
#include "Protocol\PIDEBus.h"
#include <Protocol\ComponentName.h>
#include <Protocol\BootScriptSave.h>
#include <protocol\AtaPassThru.h>


#define     IDE_BUS_DRIVER_VERSION              0x01

#define     PRIMARY_COMMAND_BLOCK               0x1F0
#define     PRIMARY_CONTROL_BLOCK               0x3F6
#define     SECONDARY_COMMAND_BLOCK             0x170
#define     SECONDARY_CONTROL_BLOCK             0x376

#define     BUSY_CLEAR_TIMEOUT                  1000            // 1Sec
#define     DRDY_TIMEOUT                        1000            // 1Sec
#define     DRQ_TIMEOUT                         10              // 10msec
#define     DRQ_CLEAR_TIMEOUT                   1000            // 1sec
#define     DRQ_SET_TIMEOUT                     10              // 10msec
#define     HP_COMMAND_COMPLETE_TIMEOUT         2000            // 2Sec
#define     COMMAND_COMPLETE_TIMEOUT            5000            // 5Sec

#define     BLKIO_REVISION                      1

#define     DEVICE_DISABLED                     0
#define     DEVICE_IN_RESET_STATE               1
#define     DEVICE_DETECTION_FAILED             2
#define     DEVICE_DETECTED_SUCCESSFULLY        3
#define     DEVICE_CONFIGURED_SUCCESSFULLY      4
#define     DEVICE_REMOVED                      5
#define     CONTROLLER_NOT_PRESENT              0xff

#define     ENUMERATE_ALL                       0xff
#define     ENUMERATE_PRIMARY_MASTER            0x0
#define     ENUMERATE_PRIMARY_SLAVE             0x1
#define     ENUMERATE_SECONDARY_MASTER          0x2
#define     ENUMERATE_SECONDARY_SLAVE           0x3
#define     INQUIRY_DATA_LENGTH                 0x96
#define     READ_CAPACITY_DATA_LENGTH           0x08

//	PCI Config Space equates
#define     PROGRAMMING_INTERFACE_OFFSET        0x09
#define     IDE_SUB_CLASS_CODE                  0x0A
#define     SCC_IDE_CONTROLLER              0x01
#define     SCC_AHCI_CONTROLLER             0x06
#define     SCC_RAID_CONTROLLER             0x04
#define     IDE_BASE_CLASS_CODE                 0x0B
#define     BASE_CODE_IDE_CONTROLLER        0x01
#define     PRIMARY_COMMAND_BLOCK_OFFSET        0x10
#define     PRIMARY_CONTROL_BLOCK_OFFSET        0x14
#define     SECONDARY_COMMAND_BLOCK_OFFSET      0x18
#define     SECONDARY_CONTROL_BLOCK_OFFSET      0x1C
#define     LEGACY_BUS_MASTER_OFFSET            0x20

#define     EFI_SUCCESS_ACTIVE_SET              0x80000000
#define ZeroMemory( Buffer, Size ) pBS->SetMem( Buffer, Size, 0 )


//###DEBUG  Uncomment the following for Required Debug Level.

//#define   Debug_Level_1
//#define   Debug_Level_2
//#define   Debug_Level_3

//###DEBUG END

// Forward reference for pure ANSI compatability
typedef struct _IDE_BUS_PROTOCOL IDE_BUS_PROTOCOL;

typedef struct
{
    UINT32 Lowdword;
    UINT32 Upperdword;
} STRUCT_U64_U32;

VOID EfiDebugPrint (
    IN UINTN ErrorLevel,
    IN CHAR8 *Format,
    ... );

EFI_STATUS CreateIdeDevicePath (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IDE_BUS_INIT_PROTOCOL          *IdeBusInitInterface,
    IDE_BUS_PROTOCOL               *IdeBusInterface,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath,
    UINT8                          Current_Channel,
    UINT8                          Current_Device );

EFI_STATUS InitIdeBlockIO (
    IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS InitIdeDiskInfo (
    IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS
InstallBusInitProtocol(
    IN EFI_HANDLE Controller,
    IDE_BUS_INIT_PROTOCOL           * IdeBusInitInterface,
    VOID    * IdeControllerInterface
    );

EFI_STATUS
ConfigureIdeDeviceAndController(
    IDE_BUS_PROTOCOL                * IdeBusInterface,
    VOID         * IdeControllerInterface,
    IDE_BUS_INIT_PROTOCOL           * IdeBusInitInterface
    );

UINT8 ReturnMSBset (
    UINT32 Data );

EFI_STATUS IdeReadByte (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    OUT UINT8              *Data8 );

EFI_STATUS IdeReadMultipleByte (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Count,
    OUT UINT8              *Data8 );

EFI_STATUS IdeReadWord (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    OUT UINT16             *Data16 );

EFI_STATUS IdeReadMultipleWord (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Count,
    OUT UINT16             *Data16 );

EFI_STATUS IdeWriteByte (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT8               Data8 );

EFI_STATUS IdeWriteMultipleByte (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Count,
    IN UINT8               *Data8 );

EFI_STATUS IdeWriteWord (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT16              Data16 );

EFI_STATUS IdeWriteMultipleWord (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Count,
    IN UINT16              *Data16 );

EFI_STATUS IdeWriteDword (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    IN UINT16              Register,
    IN UINT32              Data32 );

EFI_STATUS AtaReadWritePio (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    VOID                *Buffer,
    UINTN               ByteCount,
    UINT64              LBA,
    UINT8               readWriteCommand,
    BOOLEAN             ReadWrite );

EFI_STATUS IssueAtaReadWriteCommand (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT64              LBA,
    INT32               SectorCount,
    UINT8               Command, 
    UINT8               Features );

EFI_STATUS AtaPioDataIn (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    VOID                *Buffer,
    UINT32              ByteCount,
    UINT8               Features,
    UINT8               SectorCount,
    UINT8               LBALow,
    UINT8               LBAMid,
    UINT8               LBAHigh,
    UINT8               DeviceReg,
    UINT8               Command,
    BOOLEAN             Multiple );

EFI_STATUS AtaPioDataOut (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    VOID                 *Buffer,
    UINTN                ByteCount,
    UINT8                Features,
    UINT32               SectorCountIn,
    UINT8                LBALow,
    UINT8                LBALowExp,
    UINT8                LBAMid,
    UINT8                LBAMidExp,
    UINT8                LBAHigh,
    UINT8                LBAHighExp,
    UINT8                Device,
    UINT8                Command,
    BOOLEAN              ReadWrite,
    BOOLEAN              Multiple );

EFI_STATUS IdeNonDataCommand (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8               Features,
    UINT8               SectorCount,
    UINT8               LBALow,
    UINT8               LBAMid,
    UINT8               LBAHigh,
    UINT8               Device,
    UINT8               Command );

EFI_STATUS IdeNonDataCommandExp (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8               Features,
    UINT8               SectorCount,
    UINT8               SectorCountExp,
    UINT8               LBALow,
    UINT8               LBALowExp,
    UINT8               LBAMid,
    UINT8               LBAMidExp,
    UINT8               LBAHigh,
    UINT8               LBAHighExp,
    UINT8               Device,
    UINT8               Command );

EFI_STATUS AtaIdentifyCommand (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer );

EFI_STATUS AtapiIdentifyCommand (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer );

EFI_STATUS GetIdentifyData (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer );

EFI_STATUS IdeSetFeatureCommand (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8               SubCommand,
    UINT8               Mode );

EFI_STATUS IdeSoftReset (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS WaitForCmdCompletion (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS WaitForCmdCompletionWithTimeOutValue (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN UINT32           TimeOutvalue );

EFI_STATUS CheckDriveReady (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS WaitforBitSet (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    UINT16                 AlternateStatusReg,
    UINT8                  BitSet,
    UINT32                 TimeOut );

EFI_STATUS WaitforBitClear (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    UINT16                 AlternateStatus,
    UINT8                  BitSet,
    UINT32                 Timeout );

EFI_STATUS WaitforBitClearWithoutTimeout (
    IN EFI_PCI_IO_PROTOCOL *PciIO,
    UINT16                 AlternateStatus,
    UINT8                  BitClear );

EFI_STATUS ControllerPresence (
    IDE_BUS_PROTOCOL *IdeBusInterface );

void DisableIdeInterrupt (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS DetectIdeDevice (
    IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS ConfigureIdeDevice (
    IDE_BUS_PROTOCOL      *IdeBusInterface,
    IDE_BUS_INIT_PROTOCOL *IdeBusInitInterface );

EFI_STATUS InitAcousticSupport (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS UpdateBaseAddress (
    IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS IdeBusSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath );

EFI_STATUS IdeBusStart (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath );

EFI_STATUS IdeBusStop (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  Controller,
    IN UINTN                       NumberOfChildren,
    IN EFI_HANDLE                  *ChildHandleBuffer );

EFI_STATUS AtaReset (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN BOOLEAN               ExtendedVerification );

EFI_STATUS AtaBlkRead (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    OUT VOID                 *Buffer );

EFI_STATUS AtaBlkWrite (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    IN VOID                  *Buffer );

EFI_STATUS AtaBlkFlush (
    IN EFI_BLOCK_IO_PROTOCOL *This );

EFI_STATUS AtapiReset (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN BOOLEAN               ExtendedVerification );

EFI_STATUS AtapiBlkRead (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    OUT VOID                 *Buffer );

EFI_STATUS AtapiBlkWrite (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    IN VOID                  *Buffer );

EFI_STATUS AtapiBlkFlush (
    IN EFI_BLOCK_IO_PROTOCOL *This );

EFI_STATUS DetectAtapiMedia (
    IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS AtapiInquiryData (
    IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8            *InquiryData,
    IN OUT UINT16    *InquiryDataSize );

EFI_STATUS AtapiReadWritePio (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    VOID                *Buffer,
    UINTN               ByteCount,
    UINT64              LBA,
    UINT8               ReadWriteCommand,
    BOOLEAN             READWRITE );

EFI_STATUS AtapiWritePio (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    VOID                *Buffer,
    UINTN               ByteCount,
    UINT64              LBA,
    UINT8               WriteCommand );

EFI_STATUS GeneralAtapiCommandAnddData (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8               *Buffer,
    UINT16              ByteCount );

EFI_STATUS IssueAtapiPacketCommand (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT16              *PacketBuffer,
    UINT8               Features,
    UINT16              ByteCount );

EFI_STATUS IssueAtapiReset (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN BOOLEAN          TESTUNITREADY );

EFI_STATUS HandleAtapiError (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS DiskInfoInquiry (
    IN EFI_DISK_INFO_PROTOCOL *This,
    IN OUT VOID               *InquiryData,
    IN OUT UINT32             *InquiryDataSize );

EFI_STATUS DiskInfoIdentify (
    EFI_DISK_INFO_PROTOCOL *This,
    IN OUT VOID            *IdentifyData,
    IN OUT UINT32          *IdentifyDataSize );

EFI_STATUS DiskInfoSenseData (
    EFI_DISK_INFO_PROTOCOL *This,
    VOID                   *SenseData,
    UINT32                 *SenseDataSize,
    UINT8                  *SenseDataNumber );

EFI_STATUS DiskInfoWhichIDE (
    IN EFI_DISK_INFO_PROTOCOL *This,
    OUT UINT32                *IdeChannel,
    OUT UINT32                *IdeDevice );

EFI_STATUS GetOddType (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT UINT16       *OddType );

EFI_STATUS GetOddLoadingType(
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT UINT8        *OddLoadingType );

ODD_TYPE GetEnumOddType (
    IN UINT16 OddType );

BOOLEAN Check48BitCommand (
    UINT8 Command );

EFI_STATUS StartStopUnitCommand (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN UINT8            LoEjStart );

EFI_STATUS TestUnitReady (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS CheckCHKonEntry (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS ReadAtapiData (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    void                *Data,
    UINT16              *BytesRead );

EFI_STATUS WriteAtapiData (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    OUT void            *Data,
    OUT UINT16          *BytesRead );

EFI_STATUS GeneralAtapiCommandAndData (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8               *PacketBuffer,
    UINT8               *Buffer,
    UINT16              *ByteCount );

EFI_STATUS AtaReadWriteBusMaster (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer,
    IN UINTN            ByteCount,
    IN UINT64           LBA,
    IN UINT8            ReadWriteCommand,
    IN BOOLEAN          ReadWrite );

EFI_STATUS AtapiReadWriteBusMaster (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT VOID         *Buffer,
    IN UINTN            ByteCount,
    IN UINT64           LBA,
    IN UINT8            ReadWriteCommand,
    IN BOOLEAN          READWRITE );

EFI_STATUS CreateDescriptorTable (
    IN OUT UINTN *DescriptorBuffer,
    IN UINT8     *StartAddress,
    IN UINTN     ByteCount,
    OUT UINTN    *RemainingByteCount );

EFI_STATUS InitBusMasterRegisters (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN OUT UINTN        DescriptorBuffer,
    IN BOOLEAN          ReadWrite );

EFI_STATUS StartStopBusMastering (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN BOOLEAN          StartStop );

EFI_STATUS WaitforDMAtoCompletion (
    IN IDE_BUS_PROTOCOL *IdeBusInterface,
    IN UINTN            TimeDelay );

BOOLEAN DMACapable (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS HandleATABMErrors (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS MaskandSaveInterrupt (
    IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS RestoreInterrupt (
    IDE_BUS_PROTOCOL *IdeBusInterface );

void PrintIdeDeviceInfo (
    IDE_BUS_PROTOCOL *IdeBusInterface );

//---------------------------------------------------------------------------
// IDE POWER MANAGEMENT SUPPORT START
//---------------------------------------------------------------------------


EFI_STATUS InitIDEPowerManagement (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

UINT8 ConvertStanbyTimeoutValue (
    IN UINT8 StandbyTimeout );

EFI_STATUS InstallIDEPowerMgmtInterface (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS StopIDEPowerMgmtInterface (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );


// IDE POWER MANAGEMENT INTERFACE SUPPORT START
//---------------------------------------------------------------------------
  
EFI_STATUS CheckPowerMode (
    IN IDE_POWER_MGMT_INTERFACE *IdePowerMgmtInterface,
    IN OUT UINT8                *PowerMode );

EFI_STATUS IdleMode (
    IN IDE_POWER_MGMT_INTERFACE *IdePowerMgmtInterface,
    IN UINT8                    StandbyTimeout );

EFI_STATUS StandbyMode (
    IN IDE_POWER_MGMT_INTERFACE *IdePowerMgmtInterface,
    IN UINT8                    StandbyTimeout );

EFI_STATUS AdvancePowerMgmtMode (
    IN IDE_POWER_MGMT_INTERFACE *IdePowerMgmtInterface,
    IN UINT8                    AdvPowerMgmtLevel );

// IDE POWER MANAGEMENT INTERFACE SUPPORT END
//---------------------------------------------------------------------------
// IDE POWER MANAGEMENT SUPPORT END
//---------------------------------------------------------------------------

// HOST PROTECTED AREA SUPPORT START
//---------------------------------------------------------------------------


EFI_STATUS InstallHPAInterface (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS StopHPAInterface (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS GetNativeMaxAddress (
    IN IDE_HPA_INTERFACE *This,
    OUT UINT64           *LBA );

EFI_STATUS SetMaxAddress (
    IN IDE_HPA_INTERFACE *This,
    OUT UINT64           LBA,
    IN BOOLEAN           Volatile );

EFI_STATUS HPADisabledLastLBA (
    IN IDE_HPA_INTERFACE *This,
    OUT UINT64           *LBA
);

EFI_STATUS SetMaxPassword (
    IN IDE_HPA_INTERFACE *This,
    IN UINT8             *PasswordBuffer );

EFI_STATUS SetMaxLock (
    IN IDE_HPA_INTERFACE *This );

EFI_STATUS SetMaxUnLock (
    IN IDE_HPA_INTERFACE *This,
    IN UINT8             *PasswordBuffer );

EFI_STATUS SetMaxFreezeLock (
    IN IDE_HPA_INTERFACE *This );

EFI_STATUS IssueSetMaxPasswordCmd (
    IDE_BUS_PROTOCOL *IdeBusInterface,
    UINT8            *PasswordBuffer,
    UINT8            Cmd );

// HOST PROTECTED AREA SUPPORT END
//---------------------------------------------------------------------------

// IDE HP SUPPORT START
//---------------------------------------------------------------------------

VOID IdeHPTimer (
    IN EFI_EVENT Event,
    IN VOID      *Context );

EFI_STATUS CheckHPControllerPresence (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

EFI_STATUS FlagDeviceRemoval (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );

//  IDE HP SUPPORT END
//---------------------------------------------------------------------------
EFI_STATUS IssueFreezeLockCommand (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );
EFI_STATUS ReturnSecurityStatusWrapper (
    IN IDE_SECURITY_PROTOCOL *This,
    UINT16                   *SecurityStatus );

EFI_STATUS InstallIdeFeatures (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );
VOID UnInstallIdeFeatures (
    IN IDE_BUS_PROTOCOL *IdeBusInterface );


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

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
