//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/FloppyCtrl/FloppyCtrl.h 17    7/02/09 12:54p Yul $
//
// $Revision: 17 $
//
// $Date: 7/02/09 12:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/FloppyCtrl/FloppyCtrl.h $
// 
// 17    7/02/09 12:54p Yul
// Syns to coding standards
//
// 16    7/02/09 10:14a Yul
// Update Header and Tailer and syns with coding standards
//
// 15    4/13/07 1:37p Ambikas
// Coding standards changes: changed spaces, dashes, etc.
//
// 14    4/13/07 11:58a Ambikas
//
// 13    4/13/07 11:56a Ambikas
// Coding standard changes: updated the year in the AMI copyright header and footer;
// removed two commented out function headers (MotorOff, GetFloppyModel).
//
// 12    4/10/07 10:01a Felixp
// LookupHID routine renamed to LookupFloppyHid to avoid linking issue
// when linking with PS2CTRL module
//
// 11    9/13/06 10:08a Felixp
//
// 10    3/13/06 2:22a Felixp
//
// 9     12/21/05 11:39a Ambikas
// Added function prototype CheckMRQBit_NoDelay.
//
// 8     12/20/05 10:27p Ambikas
// Minor changes: Added new bit definitions for FLOPP_CTRL_PROTOCOL field
// UINT8 FdcFlag. FLOPPY_CTRL_PROTOCOL: FLOPPY_DISK_FORMAT
// FloppyDiskFormat replaces field UINT8 MediaType. Added various bit
// other definitions.
//
// 7     3/25/05 6:20p Felixp
//
// 6     3/25/05 7:58a Felixp
//
// 5     3/24/05 6:29p Felixp
// Included stall.h file.
//
// 4     3/24/05 11:52a Eswark
// Added Floppy  peim code based on recovery specifixcation.
//
// 3     3/22/05 4:47p Eswark
// Added Pei support.
//
// 2     3/04/05 11:27a Mandal
//
//**********************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: FloppyCtrl.h
//
// Description:	FloppyCtrl deader file -
//  function delcarations, structs, constants
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>


#ifndef __FLOPPY_CTRL_H__
#define __FLOPPY_CTRL_H__

#if !defined(PEI_FLOPPY_CTRL) && !defined(DXE_FLOPPY_CTRL)
  #define PEI_FLOPPY_CTRL
  #define DXE_FLOPPY_CTRL
#endif

//----------------------------------------------------------------------

#include <Efi.h>
#include <AmiDxeLib.h>
#include <AmiPeiLib.h>
#include <Protocol\DevicePath.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\SimpleTextIn.h>
#include <Protocol\SimplePointer.h>
#include <token.h>
#include "ppi\DeviceRecoveryBlockIo.h"
#include <Ppi\Stall.h>
#include "protocol\BlockIo.h"
#include "protocol\AmiSio.h"
#include <Protocol\ComponentName.h>
#include <Dxe.h>
#include <AcpiRes.h>
#include "pei.h"

//----------------------------------------------------------------------

#define EFI_FLOPPY_CTRL_INTERFACE_REVISION 0x00010000
extern EFI_SYSTEM_TABLE *gSysTable;

//----------------------------------------------------------------------

// PEIM specific code start

EFI_STATUS
EFIAPI FdcBlkRead (
    IN EFI_BLOCK_IO_PROTOCOL *This,
    IN UINT32                MediaId,
    IN EFI_LBA               LBA,
    IN UINTN                 BufferSize,
    OUT VOID                 *Buffer );

typedef
EFI_STATUS
(EFIAPI * PEI_FDC_BLK_RESET)(
    IN EFI_BLOCK_IO_PROTOCOL *This
    );


EFI_STATUS PeimReadBlocks (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    IN EFI_PEI_LBA                   StartLBA,
    IN UINTN                         BufferSize,
    OUT VOID                         *Buffer );

EFI_STATUS GetNumberOfBlockDevices (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                        *NumberBlockDevices );

EFI_STATUS GetBlockDeviceMediaInfo (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA       *MediaInfo );

// PEIM specific code end
//----------------------------------------------------------------------

// Floppy Disk Controller Commands
typedef struct FDD_CMD_PKT_tag
{
    UINT8 CommandCode;
    UINT8 HeadDdrSel;
    UINT8 Cylinder;
    UINT8 Head;
    UINT8 Sector;
    UINT8 Size;
    UINT8 TrackLength;
    UINT8 GapLength;
    UINT8 DataLength;
} FDD_CMD_PKT;

typedef struct
{
    UINT8 CommandCode;
    UINT8 HeadDdrSel;
} FDD_CALIBRATE_CMD;

typedef struct
{
    UINT8 CommandCode;
    UINT8 Ctrldata1;
    UINT8 Ctrldata2;
} FDD_SPECIFY_CMD;

typedef struct
{
    UINT8 CommandCode;
    UINT8 DiskHeadSel;
    UINT8 NewCylinder;
} FDD_SEEK_CMD;

typedef struct
{
    UINT8 CommandCode;
    UINT8 DiskHeadSel;
    UINT8 Cylinder;
    UINT8 Head;
    UINT8 Sector;
    UINT8 EndOfTrack;
    UINT8 GapLength;
    UINT8 ScanTestPause;
} FDD_SCAN_CMD;

typedef struct
{
    UINT8 Status0;
    UINT8 Status1;
    UINT8 Status2;
    UINT8 Cylinder;
    UINT8 Head;
    UINT8 SectorNumber;
    UINT8 SectorSize;
} FDD_RESULT_PACKET;

typedef enum
{
    DoubleDensity720Kb,
    HighDensity1_44Mb,
    ExtraHighDensity2_88Mb
} FLOPPY_DISK_FORMAT;

typedef struct FLOPPY_CTRL_PROTOCOL_tag
{
    //Don't add any member of this structure before this place add it at the end
    EFI_BLOCK_IO_PROTOCOL         BlkIo;
    EFI_BLOCK_IO_MEDIA            BlkIoMedia;
    EFI_PEI_RECOVERY_BLOCK_IO_PPI PeimRecBlk;
    FDD_CMD_PKT                   CmdRdWrSect;
    FDD_SEEK_CMD                  CmdSeek;
    FDD_CALIBRATE_CMD             CmdCalibrate;
    FDD_SPECIFY_CMD               CmdSpecify;
    FDD_RESULT_PACKET             ResultPacket;
    UINT8                         FdcFlag;
    //Bit0 Drive initilization success
    //Bit1 Drive initilization failure
    //Bit2 Drive motor on
    //Bit3 Drive write protected
    UINT8              PrCyl;     //ek1123
    UINT8              TimerFlag; //ek1122
    EFI_EVENT          Event;     //ek1122
    UINT8              DmaFlag;
    UINT8              DriveNum;
    UINT8              FloppyType;
    UINT16             BaseAddr;
    FLOPPY_DISK_FORMAT FloppyDiskFormat;
    UINT8              MaxSectors;
    UINT8              *DMABuffer;
    UINT8              *TempBuffer;
} FLOPPY_CTRL_PROTOCOL;

typedef struct DMA_INIT_tag
{
    UINT8 PortAddr;
    UINT8 Value;
} DMA_INIT;

//FLOPPY_CTRL_PROTOCOL FdcFlag bit definitions
#define FDC_FLAG_NOT_INTIALIZED         0
#define FDC_FLAG_DRIVE_INIT_SUCCESS BIT00
#define FDC_FLAG_DRIVE_INIT_ERROR       BIT01
#define FDC_FLAG_MOTOR_ON                       BIT02
#define FDC_FLAG_WRITE_PROTECTED        BIT03

#define DXE_FLAG    0xAB
#define PEI_FLAG    0xCD

#define FLOPPY_DMA_CHANNAL  0x02
#define FLOPPY_IRQ          0x06
#define START_MOTOR         0x01
#define STOP_MOTOR          0x00
#define DMA_IRQ_CHAN_EN     0x01
#define DMA_IRQ_CHAN_DIS    0x00
#define FLOPPY_INTR         0x0e

// Digital output register bits
#define DRVA_SEL            00  // 00 =Drive0(A)
#define DRVB_SEL            01  // 01 =Drive0(B)
#define DRVC_SEL            02  // 02 =Drive0(C)
#define DRVD_SEL            03  // 03 =Drive0(D)
#define CTRL_EN_BIT         BIT02
#define DMA_IRQEN_BIT       BIT03
#define MOTORA_START_BIT    BIT04
#define MOTORB_START_BIT    BIT05
#define MOTORC_START_BIT    BIT06
#define MOTORD_START_BIT    BIT07

// Main Status register bits
#define DRVA_ACT            00      // DriveA in positioning mode
#define DRVB_ACT            01      // DriveB in positioning mode
#define DRVC_ACT            02      // DriveC in positioning mode
#define DRVD_ACT            03      // DriveD in positioning mode
#define BUSY_BIT            BIT04
#define NDMA_BIT            BIT05
#define DIO_BIT             BIT06
#define MRQ_BIT             BIT07

// Digital Input Register bits
#define DISK_CHG_STS_BIT        BIT07

// FDC Data Transfer commands
#define RD_SECTOR_CMD       0x06
#define RD_TRACK_CMD        0x02
#define WR_SECTOR_CMD       0x05
#define WR_DEL_SECTOR_CMD   0x09
#define RD_DEL_SECTOR_CMD   0x0C
#define RD_TRACK_CMD        0x02
#define FORMAT_TRACK_CMD    0x0D

//Bits for Read/Write Sector Command
#define M_COMMAND_BIT_MULTITRACK_OPERATION  BIT07
#define F_COMMAND_BIT_MFM_RECORDING_METHOD  BIT06
#define S_COMMAND_BIT_SKIP_MODE                         BIT05

//Bits for Result Status 0
#define IC1_STATUS0_BIT_INTERRUPT_CODE          BIT07
#define IC0_STATUS0_BIT_INTERRUPT_CODE          BIT06

// ControlCommands
#define RD_SECTOR_ID        0x0A
#define CALIBRATE_CMD       0x07
#define SPECIFY_CMD         0x03
#define FIX_DRIVE_DATA_CMD  0x03
#define CHECK_INT_STATUS_CMD    0x08
#define CHECK_DRV_STATUS_CMD    0x04
#define SEEK_CMD            0x0F
#define PARK_RW_HEAD_CMD    0x0F
#define INVALID_CMD         0x00

// Extended commands
#define VERIFY_COMMAND      0x16

// temp remove
#define SCAN_EQU_CMD        0x11
#define SCAN_LOW_EQU_CMD    0x19
#define SCAN_HIGH_EQU_CMD   0x1D

// DMA registers

#define DMA1_ADDR_REG       0x04
#define DMA1_COUNT_REG      0x05
#define DMA1_STS_REG        0x08
#define DMA1_CMD_REG        0x08
#define DMA1_REQ_REG        0x09
#define DMA1_CH_MASK_REG    0x0A
#define DMA1_MODE_REG       0x0B
#define DMA1_RESET_REG      0x0C
#define DMA1_INTER_REG      0x0D
#define DMA1_MASK_REG       0x0F
#define DMA1_PAGE_REG       0x81


#define DMA_MAX_ADDR_LIMIT  0xFB0000
#define DMA_BUFFER_LIMIT    0xFFFFFF
#define READ_OPERATION      0x0F
#define WRITE_OPERATION     0x00
#define SECTOR_SIZE         512
#define NUM_PAGES           05

// Function declarations
BOOLEAN    LookupFloppyHid( UINT32, UINT32 );
EFI_STATUS GetFloppy_DP( EFI_DRIVER_BINDING_PROTOCOL *, EFI_HANDLE, ACPI_HID_DEVICE_PATH * *, UINT32, BOOLEAN );
EFI_STATUS FloppyDriveInit (
    FLOPPY_CTRL_PROTOCOL* );
void DriveReady (
    FLOPPY_CTRL_PROTOCOL* );
EFI_STATUS CheckBusyBit (
    FLOPPY_CTRL_PROTOCOL* );
EFI_STATUS CheckMRQBit (
    FLOPPY_CTRL_PROTOCOL* );
EFI_STATUS CheckMRQBit_NoDelay (
    FLOPPY_CTRL_PROTOCOL *FloppyInterface );
void DMAInitForFloppy (
    IN VOID*,
    IN UINTN,
    IN BOOLEAN );
EFI_STATUS InitFloppyBlockIO ( );
VOID InitFloppyBlockIOLastBlockAndMaxSectors (
    FLOPPY_CTRL_PROTOCOL *FloppyInterface );
EFI_STATUS MotorOn (
    FLOPPY_CTRL_PROTOCOL* );
void SetDataRate (
    FLOPPY_CTRL_PROTOCOL* );
EFI_STATUS CheckMediaChange (
    FLOPPY_CTRL_PROTOCOL* );
void       Delay( UINT32 );
EFI_STATUS Specify (
    FLOPPY_CTRL_PROTOCOL* );
EFI_STATUS Calibrate (
    FLOPPY_CTRL_PROTOCOL* );
EFI_STATUS MotorOff( EFI_EVENT, VOID* );
EFI_STATUS FdcBlkRead (
    IN  EFI_BLOCK_IO_PROTOCOL*,
    IN  UINT32,
    IN  EFI_LBA,
    IN  UINTN,
    OUT VOID* );
EFI_STATUS FdcBlkWrite (
    IN  EFI_BLOCK_IO_PROTOCOL*,
    IN  UINT32,
    IN  EFI_LBA,
    IN  UINTN,
    OUT VOID* );
EFI_STATUS Seek( FLOPPY_CTRL_PROTOCOL *, UINT8, UINT8 );
EFI_STATUS FddReadWriteFn (
    IN  EFI_BLOCK_IO_PROTOCOL*,
    IN  UINT32,
    IN  EFI_LBA,
    IN  UINTN,
    IN  UINT8,
    OUT VOID* );
EFI_STATUS FdcReset (
    IN EFI_BLOCK_IO_PROTOCOL*,
    IN BOOLEAN );
EFI_STATUS FdcBlkFlush (
    IN EFI_BLOCK_IO_PROTOCOL* );
EFI_STATUS CtrlReset (
    FLOPPY_CTRL_PROTOCOL* );
EFI_STATUS ChkDrSts( FLOPPY_CTRL_PROTOCOL *, UINT8 );
void       CopyBuffer( VOID *, VOID *, UINTN );
EFI_STATUS CheckMSRDOBit (
    FLOPPY_CTRL_PROTOCOL* );
EFI_STATUS CheckMSRDIBit (
    FLOPPY_CTRL_PROTOCOL* );
void DMAChInit ( );
#endif  // __FLOPPY_CTRL_H__

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
