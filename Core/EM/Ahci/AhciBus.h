//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciBus.h 18    6/25/14 10:04a Anandakrishnanl $
//
// $Revision: 18 $
//
// $Date: 6/25/14 10:04a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciBus.h $
// 
// 18    6/25/14 10:04a Anandakrishnanl
// [TAG]  		EIP170118
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	MDAT can't program correctly in AHCI module
// [RootCause]  	Identify Data Word 76_79 Offset for DiPM Support/Enabled
// is incorrect for validation
// [Solution]  	Changed separating DiPM and Device Sleep into two routines
// and also modified the tokens to disable both support by default .
// Corrected Identify data validations.
// [Files]  		  AhciBus.c
//   AhciBus.h
//   AhciSrc.sdl
//   PAhciBus.h
//   PIDEBus.h 
// 
// 17    1/27/14 4:56a Rameshr
// [TAG]  		EIP148180
// [Category]  	Improvement
// [Description]  	change from EFI_MBR_WRITE_PROTECTION_PROTOCOL to
// AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL
// [Files]  		Ahcibus.c, Ahcibus.h, AhciComponentName.c, AhciController.c
// 
// 16    12/18/13 3:21a Srikantakumarp
// [TAG]    EIP127356
// [Category]    Improvement
// [Description]    Flash NVRAM seems to cause HDD can't be unlocked when
// S3 resume.
// [Files]    IdeSecurity.c, IDESMM.c, HddPassword.c, AhciBus.c, AhciBus.h
// 
// 15    8/27/13 4:18a Rameshr
// [TAG]  		EIP125560
// [Category]  	Improvement
// [Description]  	MbrWriteProtectionProtocol file name changesd to
// AmiMbrWriteProtectionProtocol.h
// [Files]  		AhciController.c, AhciBus.h, Ahcibus.c
// 
// 14    7/23/13 11:54p Srikantakumarp
// [TAG]  		EIP129989
// [Category]  	Improvement
// [Description]  	Added DIPM support in Aptio 4.x AHCIBUS driver.
// [Files]  		AhciBus.c, AhciBus.h, AhciController.h, AhciSrc.sdl,
// PAhciBus.h
// 
// 13    7/22/13 2:07a Rameshr
// [TAG]  		EIP129028
// [Category]  	Improvement
// [Description]  	Implement the POWERUP_IN_STANDBY_MODE support in
// AHCIBUS driver
// [Files]  		Ahcibus.c, Ahcibus.h, Pahcibus.h
// 
// 12    7/18/13 4:22a Rameshr
// [TAG]  		EIP127919
// [Category]  	Improvement
// [Description]  	"Device is Atapi" bit of PxCMD will be set if the ATAPI
// device connected on the Port and "Drive LED on ATAPI" Enabled by AHCI
// platform policy
// [Files]  		Pahcibus.h, Ahcibus.c, Ahcibus.h
// 
// 11    7/20/12 6:10a Anandakrishnanl
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
// 10    9/27/11 3:02a Rajeshms
// [TAG]  		EIP69295
// [Category]  	Improvement
// [Description]  	The Timeout values used by IDE and AHCI drivers are
// made as SDL tokens, so that the timeout values can be varied.
// [Files]  		IdeBusBoard.c, CORE_DXE.sdl, AhciSmm.h, AhciBus.h, IDESMM.h,
// Ata.c, Atapi.c, IdeBus.c, IdeBus.h, IdeBusMaster.c, IdeBusBoard.h
// 
// 9     9/19/11 3:05a Lavanyap
// [TAG]  		EIP69398
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Function ConfigureController() has a runtime error (NULL
// pointer dereference)
// [RootCause]  	variable SupportedModes has been initialized again in
// ConfigureController().
// [Solution]  	variable SupportedModes is passed as an input parameter
// for ConfigureController() and ConfigureDevice().
// [Files]  		AhciBus.c, AhciBus.h
// 
// 8     2/11/11 4:23a Rameshr
// [TAG]  		EIP53730
// [Category]  	Improvement
// [Description]  	Add Odd Loading type information into ATAPI_DEVICE
// structure in AHCI mode
// [Files]  		AhciBus.c
// AhciController.c
// AhciBus.h
// 
// 7     2/10/11 10:35a Rameshr
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
// 6     12/23/10 3:59a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 5     5/07/10 11:45a Krishnakumarg
// Coding standard update
// 
// 4     6/22/09 11:34a Rameshr
// Odd Type information Saved in Atapi Device Structure.
// EIP:21548
// 
// 3     4/28/09 3:58p Rameshr
// 
// HDD password support in RAID mode
// EIP:20421
// 
// 2     5/28/08 9:39a Rameshraju
// Based on the SDL token index/data or MMIO method used to access the
// AHCI configuration space.
// 
// 1     28/02/08 6:03p Anandakrishnanl
// AHCI Bus Driver initial check-in.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    AhciBus.h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _AhciBus_
#define _AhciBus_

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
#include <Protocol\PAhciBus.h>
#include <protocol\AtaPassThru.h>
#include <protocol\StorageSecurityCommand.h>
#include "AhciController.h"

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
#include <Protocol\AmiBlockIoWriteProtection.h>
#endif

#define     TRACE_AHCI_LEVEL2
#define      TRACE_AHCI             TRACE

#ifdef Debug_Level_1
VOID EfiDebugPrint (IN  UINTN ErrorLevel,IN  CHAR8 *Format,...);
#endif

#define     AHCI_BUS_DRIVER_VERSION     0x01
#define     ONE_MILLISECOND             1000

#define     COMMAND_LIST_SIZE_PORT      0x800

#ifndef ATAPI_BUSY_CLEAR_TIMEOUT
#define     ATAPI_BUSY_CLEAR_TIMEOUT    16000       // 16sec
#endif

#ifndef S3_BUSY_CLEAR_TIMEOUT
#define     S3_BUSY_CLEAR_TIMEOUT       10000                   // 10Sec
#endif

#define     BUSY_CLEAR_TIMEOUT          1000                    // 1Sec
#define     DRDY_TIMEOUT                1000                    // 1Sec
#define     DRQ_TIMEOUT                 10                      // 10msec
#define     DRQ_CLEAR_TIMEOUT           1000                    // 1sec
#define     DRQ_SET_TIMEOUT             10                      // 10msec
#define     HP_COMMAND_COMPLETE_TIMEOUT 2000                    // 2Sec
#define     COMMAND_COMPLETE_TIMEOUT    5000                    // 5Sec

#ifndef DMA_ATA_COMMAND_COMPLETE_TIMEOUT
#define     DMA_ATA_COMMAND_COMPLETE_TIMEOUT    5000            // 5Sec
#endif

#ifndef DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT
#define     DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT  16000           // 16Sec
#endif

#ifndef ATAPI_RESET_COMMAND_TIMEOUT
#define     ATAPI_RESET_COMMAND_TIMEOUT 5000
#endif

#ifndef POWERON_BUSY_CLEAR_TIMEOUT
#define     POWERON_BUSY_CLEAR_TIMEOUT  10000                   // 10 Sec
#endif

#define     TIMEOUT_1SEC                1000                    // 1sec Serial ATA 1.0 Sec 5.2



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

//  PCI Config Space equates
#define     PROGRAMMING_INTERFACE_OFFSET        0x09
#define     IDE_SUB_CLASS_CODE                  0x0A
    #define SCC_IDE_CONTROLLER                  0x01
    #define SCC_AHCI_CONTROLLER                 0x06
    #define SCC_RAID_CONTROLLER                 0x04
#define     IDE_BASE_CLASS_CODE                 0x0B
    #define BASE_CODE_IDE_CONTROLLER            0x01
#define     PRIMARY_COMMAND_BLOCK_OFFSET        0x10
#define     PRIMARY_CONTROL_BLOCK_OFFSET        0x14
#define     SECONDARY_COMMAND_BLOCK_OFFSET      0x18
#define     SECONDARY_CONTROL_BLOCK_OFFSET      0x1C
#define     LEGACY_BUS_MASTER_OFFSET            0x20

#define     EFI_SUCCESS_ACTIVE_SET              0x80000000


EFI_STATUS
CreateIdeDevicePath (
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                   Controller,
    IDE_BUS_INIT_PROTOCOL           *IdeBusInitInterface,
    IDE_BUS_PROTOCOL                *IdeBusInterface,
    IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath,
    UINT8                           Current_Channel,  
    UINT8                           Current_Device
);

EFI_STATUS
InitIdeBlockIO (
    IDE_BUS_PROTOCOL                *IdeBusInterface
);

EFI_STATUS
InitIdeDiskInfo (
    IDE_BUS_PROTOCOL                *IdeBusInterface
);

EFI_STATUS
InstallAhciBusProtocol (
    IN EFI_HANDLE                    Controller,
    AHCI_BUS_PROTOCOL               *IdeBusInitInterface,
    EFI_IDE_CONTROLLER_INIT_PROTOCOL *IdeControllerInterface,
    EFI_PCI_IO_PROTOCOL              *PciIO
);

EFI_STATUS
AhciInitController (
    AHCI_BUS_PROTOCOL               *AhciBusInterface
);

EFI_STATUS
CheckPortImplemented (
    AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    UINT8                               Port
);

EFI_STATUS
AhciDetectDevice (
    AHCI_BUS_PROTOCOL              *AhciBusInterface, 
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface, 
    UINT8                               Port, 
    UINT8                               PMPortNumber
);

EFI_STATUS
CheckDevicePresence (
    SATA_DEVICE_INTERFACE               *SataDevInterface,
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface, 
    UINT8                               Port, 
    UINT8                               PMPort
);

EFI_STATUS
CheckPMDevicePresence (
    SATA_DEVICE_INTERFACE   			*SataDevInterface,
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface, 
    UINT8                               Port, 
    UINT8                               PMPort
);

EFI_STATUS
ConfigureDevice (
    SATA_DEVICE_INTERFACE         *SataDevInterface,
    EFI_ATA_COLLECTIVE_MODE       **SupportedModes
);

EFI_STATUS
ConfigureController (
    SATA_DEVICE_INTERFACE         *SataDevInterface,
    EFI_ATA_COLLECTIVE_MODE       *SupportedModes
);

VOID 
InitializeDipm(
    SATA_DEVICE_INTERFACE         *SataDevInterface
);

VOID
InitializeDeviceSleep (
    SATA_DEVICE_INTERFACE         *SataDevInterface
);

EFI_STATUS
HostReset (
    AHCI_BUS_PROTOCOL                   *AhciBusInterface 
);


EFI_STATUS
GeneratePortReset (
    AHCI_BUS_PROTOCOL             *AhciBusInterface, 
    SATA_DEVICE_INTERFACE         *SataDevInterface,  
    UINT8                          Port,
    UINT8                          PMPort,
    UINT8                          Speed,
    UINT8                          PowerManagement
);

EFI_STATUS
GenerateSoftReset (
    SATA_DEVICE_INTERFACE               *SataDevInterface,
    UINT8                               PMPort
);

EFI_STATUS
GetIdentifyData (
    SATA_DEVICE_INTERFACE          *SataDevInterface 
);

EFI_STATUS
HandlePortComReset(
    AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    SATA_DEVICE_INTERFACE               *SataDevInterface,
    UINT8                               Port,
	UINT8                               PMPort
);

EFI_STATUS 
CheckValidDevice (
    AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    UINT8                               Port,
    UINT8                               PMPort
);

SATA_DEVICE_INTERFACE*
GetSataDevInterface(
    AHCI_BUS_PROTOCOL              *AhciBusInterface, 
    UINT8                          Port,
    UINT8                          PMPort
);

EFI_STATUS
ExecuteNonDataCommand (
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    COMMAND_STRUCTURE                   CommandStructure
);

EFI_STATUS
ExecutePioDataCommand (
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    COMMAND_STRUCTURE                   *CommandStructure,
    BOOLEAN                             READWRITE
);

EFI_STATUS
ExecuteDmaDataCommand (
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    COMMAND_STRUCTURE                   *CommandStructure,
    BOOLEAN                             READWRITE
);

EFI_STATUS
SataReadWritePio(
	IN SATA_DEVICE_INTERFACE        *SataDevInterface,
	IN OUT VOID						*Buffer,
	IN UINTN						ByteCount,
	IN UINT64						LBA,
	IN UINT8						ReadWriteCommand,
	IN BOOLEAN						READWRITE
) ;

EFI_STATUS
SataPioDataOut (
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
    IN UINT8                        Command,
    IN BOOLEAN                      READWRITE
) ;

EFI_STATUS
WaitforCommandComplete  (
    SATA_DEVICE_INTERFACE               *SataDevInterface,
    COMMAND_TYPE                        CommandType,
    UINTN                               TimeOut    
);

UINT8
ReturnMSBset(
 UINT32				Data
);

EFI_STATUS
StartController (
    AHCI_BUS_PROTOCOL                    *AhciBusInterface, 
    SATA_DEVICE_INTERFACE               *SataDevInterface,
	UINT32							  	CIBitMask
);

EFI_STATUS
ReadytoAcceptCmd (
    SATA_DEVICE_INTERFACE               *SataDevInterface
);

EFI_STATUS
StopController(
    AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    SATA_DEVICE_INTERFACE               *SataDevInterface,
    BOOLEAN                             StartOrStop
) ;

EFI_STATUS
DetectAndConfigureDevice (
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     Controller,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath,
	AHCI_BUS_PROTOCOL		    	  *AhciBusInterface,
    EFI_IDE_CONTROLLER_INIT_PROTOCOL  *IdeControllerInterface,
	UINT8							  Port,
	UINT8							  PMPort
);		

EFI_STATUS
ConfigurePMPort (
	SATA_DEVICE_INTERFACE   *SataDevInterface
);

EFI_STATUS
ReadWritePMPort (
	SATA_DEVICE_INTERFACE   *SataDevInterface,
	UINT8					Port,
	UINT8					RegNum,
	UINT32					*Data,
	BOOLEAN					READWRITE	
);

UINT32
ReadSCRRegister (
	AHCI_BUS_PROTOCOL       *AhciBusInterface, 
	SATA_DEVICE_INTERFACE   *SataDevInterface, 
	UINT8					Port, 
	UINT8					PMPort, 
	UINT8		    		Register
);

EFI_STATUS
WriteSCRRegister (
    AHCI_BUS_PROTOCOL       *AhciBusInterface, 
	SATA_DEVICE_INTERFACE   *SataDevInterface,
	UINT8					Port, 
	UINT8					PMPort, 
	UINT8		    		Register,
	UINT32					Data32
);

EFI_STATUS
WritePMPort (
	SATA_DEVICE_INTERFACE   *SataDevInterface,
	UINT8					Port,
	UINT8					RegNum,
	UINT32					Data	
);

EFI_STATUS
BuildCommandList (
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
	AHCI_COMMAND_LIST           		*CommandList,
	UINT32								CommandTableBaseAddr
);

EFI_STATUS
BuildCommandFIS (
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    COMMAND_STRUCTURE                   CommandStructure,
    AHCI_COMMAND_LIST    				*CommandList,
    AHCI_COMMAND_TABLE   				*Commandtable
);

EFI_STATUS
BuildAtapiCMD(
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    COMMAND_STRUCTURE                   CommandStructure,
    AHCI_COMMAND_LIST    				*CommandList,
    AHCI_COMMAND_TABLE   				*Commandtable
);

EFI_STATUS
BuildPRDT
(
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    COMMAND_STRUCTURE                   CommandStructure,
    AHCI_COMMAND_LIST    				*CommandList,
    AHCI_COMMAND_TABLE   				*Commandtable
);

EFI_STATUS 
WaitForMemSet (
	IN UINT32 BaseAddr,
	IN UINT8  Port,
	IN UINT8  Register,
    IN UINT32 AndMask,
    IN UINT32 TestValue,
    IN UINT32 WaitTimeInMs
);

EFI_STATUS 
WaitforPMMemSet (
	IN SATA_DEVICE_INTERFACE   *SataDevInterface,
    IN UINT8 				   PMPort,
	IN UINT8				   Register,
    IN UINT32 				   AndMask,
    IN UINT32 				   TestValue,
    IN UINT32 				   WaitTimeInMs
);

EFI_STATUS 
WaitForMemClear (
	IN UINT32 BaseAddr,
	IN UINT8  Port,
	IN UINT8  Register,
    IN UINT32 AndMask,
    IN UINT32 WaitTimeInMs
);

EFI_STATUS
CreateSataDevicePath (
	IN EFI_DRIVER_BINDING_PROTOCOL    	*This,
	IN EFI_HANDLE                   	Controller,
	IN SATA_DEVICE_INTERFACE            *SataDevInterface,	
	IN OUT EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
);

EFI_STATUS
InitSataBlockIO (
	IN SATA_DEVICE_INTERFACE            *SataDevInterface
);

EFI_STATUS
InitSataDiskInfo (
	IN SATA_DEVICE_INTERFACE            *SataDevInterface
);

EFI_STATUS
InitAcousticSupport (
	IN SATA_DEVICE_INTERFACE            *SataDevInterface
);	

EFI_STATUS
InitSMARTSupport (
	IN SATA_DEVICE_INTERFACE            *SataDevInterface
);	

EFI_STATUS
SMARTReturnStatusWrapper(
	IN SATA_DEVICE_INTERFACE            *SataDevInterface
);

EFI_STATUS
ConfigurePowerUpInStandby (
    IN SATA_DEVICE_INTERFACE            *SataDevInterface
);

EFI_STATUS 
AhciBusSupported(
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     Controller,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
);

EFI_STATUS 
AhciBusStart (
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     Controller,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath 
);

EFI_STATUS 
AhciBusStop (
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     Controller,
    IN UINTN                          NumberOfChildren,
    IN EFI_HANDLE                     *ChildHandleBuffer
);


EFI_STATUS
DiskInfoInquiry (
	IN EFI_DISK_INFO_PROTOCOL	*This,
	IN OUT VOID					*InquiryData,
	IN OUT UINT32				*InquiryDataSize
);

EFI_STATUS
DiskInfoIdentify (
	EFI_DISK_INFO_PROTOCOL			*This,
	IN OUT VOID						*IdentifyData,
	IN OUT UINT32					*IdentifyDataSize
);

EFI_STATUS
DiskInfoSenseData(
	EFI_DISK_INFO_PROTOCOL   	*This,
	VOID						*SenseData,
	UINT32						*SenseDataSize,
	UINT8						*SenseDataNumber
);

EFI_STATUS
DiskInfoWhichIDE
(
	IN EFI_DISK_INFO_PROTOCOL	*This,
	OUT UINT32					*IdeChannel,
	OUT UINT32					*IdeDevice
);

#define ZeroMemory(Buffer,Size) pBS->SetMem(Buffer,Size,0)


BOOLEAN
DMACapable(
    SATA_DEVICE_INTERFACE       *SataDevInterface
); 

EFI_STATUS
SataBlkRead(
	IN EFI_BLOCK_IO_PROTOCOL 		*This,
	IN UINT32 					    MediaId,
	IN EFI_LBA 					    LBA,
	IN UINTN 					    BufferSize,
	OUT VOID 					    *Buffer
);

EFI_STATUS
SataBlkWrite(
	IN EFI_BLOCK_IO_PROTOCOL 		*This,
	IN UINT32 					    MediaId,
	IN EFI_LBA 					    LBA,
	IN UINTN 					    BufferSize,
	OUT VOID 					    *Buffer
);

EFI_STATUS
SataAtaBlkReadWrite (
	IN EFI_BLOCK_IO_PROTOCOL 		*This,
	IN UINT32 					    MediaId,
	IN EFI_LBA 					    LBA,
	IN UINTN 					    BufferSize,
	OUT VOID 					    *Buffer,
    BOOLEAN                         READWRITE
);

EFI_STATUS
SataAtapiBlkRead(
	IN EFI_BLOCK_IO_PROTOCOL 		*This,
	IN UINT32 					    MediaId,
	IN EFI_LBA 					    LBA,
	IN UINTN 					    BufferSize,
	OUT VOID 					    *Buffer
);

EFI_STATUS
SataAtapiBlkWrite(
	IN EFI_BLOCK_IO_PROTOCOL 		*This,
	IN UINT32 					    MediaId,
	IN EFI_LBA 					    LBA,
	IN UINTN 					    BufferSize,
	OUT VOID 					    *Buffer
);

EFI_STATUS
SataReset (
	IN EFI_BLOCK_IO_PROTOCOL		*This,
	IN BOOLEAN					    ExtendedVerification
);

EFI_STATUS
SataBlkFlush(
	IN EFI_BLOCK_IO_PROTOCOL		*This
);

EFI_STATUS
SataReadWriteBusMaster(
	SATA_DEVICE_INTERFACE           *SataDevInterface,
	IN OUT VOID						*Buffer,
	IN UINTN						ByteCount,
	IN UINT64						LBA,
	IN UINT8						ReadWriteCommand,
	IN BOOLEAN						READWRITE
);

EFI_STATUS
SataAtapiInquiryData (
	SATA_DEVICE_INTERFACE           *SataDevInterface,
	UINT8						    *InquiryData,
	UINT16						    *InquiryDataSize
);

EFI_STATUS
DetectAtapiMedia(
	SATA_DEVICE_INTERFACE           *SataDevInterface
);

EFI_STATUS
TestUnitReady(
	SATA_DEVICE_INTERFACE           *SataDevInterface
);

EFI_STATUS 
ExecutePacketCommand (
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    COMMAND_STRUCTURE                   *CommandStructure,
    BOOLEAN                             READWRITE
);

EFI_STATUS
SataAtapiBlkReadWrite(
	IN EFI_BLOCK_IO_PROTOCOL 		*This,
	IN UINT32 					    MediaId,
	IN EFI_LBA 					    LBA,
	IN UINTN 					    BufferSize,
	OUT VOID 					    *Buffer,
    BOOLEAN                         READWRITE
);

EFI_STATUS
HandleAtapiError (
    SATA_DEVICE_INTERFACE               *SataDevInterface
);

BOOLEAN
Check48BitCommand (
	IN UINT8			            Command
);

EFI_STATUS
InitSMARTSupport (
	IN SATA_DEVICE_INTERFACE   *SataDevInterface 
);

EFI_STATUS
SMARTReturnStatusWrapper(
	IN SATA_DEVICE_INTERFACE   *SataDevInterface 
);

EFI_STATUS
SataGetOddType (
	IN SATA_DEVICE_INTERFACE           *SataDevInterface,
	IN OUT UINT16					   *OddType
);

EFI_STATUS
SataGetOddLoadingType (
    IN SATA_DEVICE_INTERFACE           *SataDevInterface,
    IN OUT UINT8                       *OddLoadingType
);

ODD_TYPE 
GetEnumOddType(
    IN  UINT16                      OddType
);

EFI_STATUS
ConfigureSataPort (
    IN SATA_DEVICE_INTERFACE   *SataDevInterface
);


#if INDEX_DATA_PORT_ACCESS
UINT32
ReadDataDword(
	IN	UINTN	BaseAddr,
	IN  UINTN	Index
);

UINT16
ReadDataWord(
	IN	UINTN	BaseAddr,
	IN  UINTN	Index
);

UINT8
ReadDataByte(
	IN	UINTN	BaseAddr,
	IN  UINTN	Index
);

VOID
WriteDataDword(
	IN	UINTN	BaseAddr,
	IN  UINTN	Index, 
	IN	UINTN	Data
);

VOID
WriteDataWord(
	IN	UINTN	BaseAddr,
	IN  UINTN	Index, 
	IN	UINTN	Data
);

VOID
WriteDataByte(
	IN	UINTN	BaseAddr,
	IN  UINTN	Index,
	IN	UINTN	Data
);
#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
