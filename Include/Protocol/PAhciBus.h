//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/PAhciBus.h 3     2/01/15 11:02p Chienhsieh $
//
// $Revision: 3 $
//
// $Date: 2/01/15 11:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Include/Protocol/PAhciBus.h $
// 
// 3     2/01/15 11:02p Chienhsieh
// Update v12 for AHCI module labeled 27.
// 
// 12    6/25/14 10:08a Anandakrishnanl
// [TAG]  		EIP170118
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	MDAT can't program correctly in AHCI module
// [RootCause]  	Identify Data Word 76_79 Offset for DiPM Support/Enabled
// is incorrect for validation
// [Solution]  	Changed separating DiPM and Device Sleep into two routines
// and also modified the tokens to disable both support by default .
// Corrected Identify data validations
// [Files]  		  AhciBus.c
//   AhciBus.h
//   AhciSrc.sdl
//   PAhciBus.h
//   PIDEBus.h 
// 
// 11    7/23/13 11:58p Srikantakumarp
// [TAG]  		EIP129989
// [Category]  	Improvement
// [Description]  	Added DIPM support in Aptio 4.x AHCIBUS driver.
// [Files]  		AhciBus.c, AhciBus.h, AhciController.h, AhciSrc.sdl,
// PAhciBus.h
// 
// 10    7/22/13 2:10a Rameshr
// [TAG]  		EIP129028
// [Category]  	Improvement
// [Description]  	Implement the POWERUP_IN_STANDBY_MODE support in
// AHCIBUS driver
// [Files]  		Ahcibus.c, Ahcibus.h, Pahcibus.h
// 
// 9     7/18/13 4:23a Rameshr
// [TAG]  		EIP127919
// [Category]  	Improvement
// [Description]  	"Device is Atapi" bit of PxCMD will be set if the ATAPI
// device connected on the Port and "Drive LED on ATAPI" Enabled by AHCI
// platform policy
// [Files]  		Pahcibus.h, Ahcibus.c, Ahcibus.h
// 
// 8     11/28/12 7:22a Deepthins
// [TAG]  		EIP104011 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	AhciBaseAddress build x86 problem
// [RootCause]  	When x64_BUILD is disabled, UINTN is UINT32, when copied
// to UINT64 can cause data loss
// [Solution]  	AhciBaseAddress is defined as UINT32 instead of UINTN.
// [Files]  		AtaPassThru.c ,PAhciBus.h
// 
// 7     9/10/12 3:05a Rameshr
// [TAG]  		EIP95440
// [Category]  	Improvement
// [Description]  	Add HddSecurity and HddSmart feature under UEFI Raid
// driver mode
// [Files]  		Ahcibus.c, Pahcibus.h, Aint13.c
// 
// 6     8/16/12 3:16a Rajeshms
// [TAG]  		EIP97048
// [Category]  	New Feature
// [Description]  	ATAPI PassThru Support using
// EFI_EXT_SCSI_PASS_THRU_PROTOCOL.
// [Files]  		AhciBus.c, AhciController.c, IdeBus.c, Atapi.c, PIDEBus.h,
// PAhciBus.h, ScsiPassThruAtapi.sdl, ScsiPassThruAtapi.mak,
// ScsiPassThruAtapi.c, ScsiPassThruAtapiSupport.h, ScsiPassThruAtapi.chm,
// ScsiPassThruExt.h
// 
// 5     7/20/12 6:16a Anandakrishnanl
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
// 4     12/23/10 3:49a Lavanyap
// [TAG] - EIP41445
// [Category] - NEW FEATURE
// [Description] - Created SataPioDataOut and AtaPioDataOut protocol
// function that can accept additional input parameters.
// [Files] - AhciBus.h, AhciBus.c, AhciController.c, Ata.c, IdeBus.c,
//           IdeBus.h, IdeBusMaster.c,PAhciBus.h, PIdeBus.h
// 
// 3     1/11/10 12:15p Krishnakumarg
// Added DiPM in AHCI_BUS_PROTOCOL - EIP 30041
// 
// 2     9/08/09 9:21a Krishnakumarg
// Acoustic member variables added to AHCI_BUS_PROTOCOL
// 
// 1     28/02/08 7:51p Anandakrishnanl
// Added PIdeBus.h and PAhciBus.h to generic Protocol for HddSecurity
// support.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AhciBus.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _PAchiBus_
#define _PAchiBus_

#ifdef __cplusplus
extern "C" {
#endif



#define AHCI_BUS_INIT_PROTOCOL_GUID \
        {0xB2FA4764, 0x3B6E, 0x43D3, 0x91, 0xDF, 0x87, 0xD1, 0x5A, 0x3E, 0x56, 0x68}


GUID_VARIABLE_DECLARATION(gAciBusInitProtocolGuid,AHCI_BUS_INIT_PROTOCOL_GUID);


#define AHCI_PLATFORM_POLICY_PROTOCOL_GUID \
        {0x17706d27, 0x83fe, 0x4770,0x87, 0x5f, 0x4c, 0xef, 0x4c, 0xb8, 0xf6, 0x3d}

GUID_VARIABLE_DECLARATION(gAciPlatformPolicyProtocolGuid,AHCI_PLATFORM_POLICY_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <AmiDxeLib.h>

// Forward reference for pure ANSI compatability
typedef	struct _SATA_DEVICE_INTERFACE SATA_DEVICE_INTERFACE;
typedef	struct _AHCI_BUS_PROTOCOL AHCI_BUS_PROTOCOL;

#define		COMMAND_COMPLETE_TIMEOUT	5000					// 5Sec

#pragma pack(1)

typedef struct {
  UINT32   Lowdword;
  UINT32   Upperdword;
} STRUCT_U64_U32;

//typedef enum {	
//  ATA = 0,
//  ATAPI = 1,
//  PMPORT = 2
//} DEVICE_TYPE;

typedef enum {	
  NON_DATA_CMD = 0,
  PIO_DATA_IN_CMD = 1,
  PIO_DATA_OUT_CMD = 2,
  DMA_DATA_IN_CMD = 3,
  DMA_DATA_OUT_CMD = 4,
  PACKET_PIO_DATA_IN_CMD = 5,
  PACKET_PIO_DATA_OUT_CMD = 6,
  PACKET_DMA_DATA_IN_CMD = 7,
  PACKET_DMA_DATA_OUT_CMD = 8,
} COMMAND_TYPE;


typedef struct {
  DLIST   AhciControllerList;
  DLINK   AhciControllerLink;
} AHCI_CONTOLLER_LINKED_LIST;

typedef struct _AHCI_ATAPI_COMMAND{
  	UINT8    		Ahci_Atapi_Command[0x10];
} AHCI_ATAPI_COMMAND;

typedef struct{
	VOID 						*Buffer;
	UINT32						ByteCount;
    UINT8						Features;
    UINT8						FeaturesExp;
    UINT16						SectorCount;
    UINT8						LBALow;
    UINT8						LBALowExp;
    UINT8						LBAMid;
    UINT8						LBAMidExp;
    UINT8						LBAHigh;
    UINT8						LBAHighExp;
    UINT8						Device;
    UINT8						Command;
	UINT8						Control;
    AHCI_ATAPI_COMMAND          AtapiCmd;
}COMMAND_STRUCTURE;

typedef EFI_STATUS (*EFI_SATA_DEV_RAED_WRITE_PIO) (
	IN SATA_DEVICE_INTERFACE                *SataDevInterface,
	IN OUT VOID						        *Buffer,
	IN UINTN						        ByteCount,
	IN UINT64						        LBA,
	IN UINT8						        ReadWriteCommand,
	IN BOOLEAN						        READWRITE
);

typedef EFI_STATUS (*EFI_SATA_DEV_PIO_DATA_IN) (
    IN SATA_DEVICE_INTERFACE                *SataDevInterface, 
    IN OUT COMMAND_STRUCTURE                *CommandStructure,
    IN BOOLEAN                              READWRITE

);

typedef EFI_STATUS (*EFI_SATA_DEV_PIO_DATA_OUT) (
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
);
typedef EFI_STATUS (*EFI_SATA_DEV_NON_DATA_CMD) (
   IN SATA_DEVICE_INTERFACE                 *SataDevInterface, 
    IN COMMAND_STRUCTURE                    CommandStructure
);

typedef EFI_STATUS (*EFI_SATA_DEV_WAIT_FOR_CMD_COMPLETE) (
    IN SATA_DEVICE_INTERFACE                *SataDevInterface,
    IN COMMAND_TYPE                         CommandType,
    IN UINTN                                TimeOut    

);

typedef EFI_STATUS (*EFI_SATA_GENERATE_PORT_RESET) (
    AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
    SATA_DEVICE_INTERFACE               *SataDevInterface, 
    UINT8                               Port,
    UINT8                               PMPort,
    UINT8                               Speed,
    UINT8                               PowerManagement   
);

typedef EFI_STATUS (*EFI_EXECUTE_PACKET_COMMAND) (
    IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
    IN COMMAND_STRUCTURE                   *CommandStructure,
    IN BOOLEAN                             READWRITE
);

typedef struct _AHCI_BUS_PROTOCOL{
	EFI_HANDLE                          ControllerHandle;
    UINT32                              AhciBaseAddress;
    UINT32                              AhciVersion;
    UINT32                              HBACapability;
    UINT32                              HBAPortImplemented;        // Bit Map
    UINT32                              PortCommandListBaseAddr;
    UINT32                              PortCommandListLength;
    UINT32                              PortCommandTableBaseAddr;
    UINT32                              PortCommandTableLength;
    UINT32                              PortFISBaseAddr;
    UINT32                              PortFISBaseAddrEnd;
    DLIST                               SataDeviceList;
	EFI_DEVICE_PATH_PROTOCOL		    *DevicePathProtocol;
    EFI_IDE_CONTROLLER_INIT_PROTOCOL    *IdeControllerInterface;
    EFI_PCI_IO_PROTOCOL					*PciIO;
    UINT32                              Address1;                   // Unmodified PortFISBaseAddr
    UINT32                              Address2;                   // Unmodified PortCommandListBaseAddr
    UINT8                               NumberofPortsImplemented;   // 1 based Count
	BOOLEAN								AHCIRAIDMODE;				// Set to TRUE in AHCI mode, FALSE in RAID mode

    EFI_SATA_DEV_RAED_WRITE_PIO         SataReadWritePio;
    EFI_SATA_DEV_PIO_DATA_IN            ExecutePioDataCommand;
    EFI_SATA_DEV_PIO_DATA_OUT           SataPioDataOut;
    EFI_SATA_DEV_NON_DATA_CMD           ExecuteNonDataCommand;
    EFI_SATA_DEV_WAIT_FOR_CMD_COMPLETE  WaitforCommandComplete;
    EFI_SATA_GENERATE_PORT_RESET        GeneratePortReset;
    EFI_EXECUTE_PACKET_COMMAND          ExecutePacketCommand;

	BOOLEAN								Acoustic_Enable;            // Acoustic Support
	UINT8								Acoustic_Management_Level;  // Acoustic Level
    UINT8                               DiPM;
    UINT16                              PrevPortNum;
    UINT16                              PrevPortMultiplierPortNum;

}AHCI_BUS_PROTOCOL;

typedef struct _SATA_DISK_INFO{ 
	EFI_DISK_INFO_PROTOCOL				DiskInfo;				// should be the first Entry
	SATA_DEVICE_INTERFACE			    *SataDevInterface;
}SATA_DISK_INFO;

typedef struct _SATA_BLOCK_IO{ 
	EFI_BLOCK_IO_PROTOCOL				BlkIo;					// should be the first Entry
	SATA_DEVICE_INTERFACE				*SataDevInterface;
}SATA_BLOCK_IO;

typedef struct _SATA_DEVICE_INTERFACE{
	EFI_HANDLE				            IdeDeviceHandle;
    UINT8                               PortNumber;
    UINT8                               PMPortNumber; 
	UINT8								NumPMPorts;			// Number of Ports in PM, Valid for PMPORT only
    UINT8                               DeviceState;
    UINT32                              Signature;
	UINT32								SControl;
	DEVICE_TYPE				            DeviceType;

	UINT8					            PIOMode;
	UINT8					            SWDma;
	UINT8					            MWDma;
	UINT8					            UDma;
	UINT8					            IORdy;
	UINT8					            ReadCommand;
	UINT8					            WriteCommand;
    IDENTIFY_DATA			            IdentifyData;
	EFI_UNICODE_STRING_TABLE            *UDeviceName;
	ATAPI_DEVICE			            *AtapiDevice;
    UINT8                               AtapiSenseData[256];
    UINT8                               AtapiSenseDataLength;

    UINT32                              PortCommandListBaseAddr;
    UINT32                              PortFISBaseAddr;

    AHCI_BUS_PROTOCOL                   *AhciBusInterface;
	EFI_DEVICE_PATH_PROTOCOL            *DevicePathProtocol; 
    SATA_BLOCK_IO                       *SataBlkIo;
    SATA_DISK_INFO                      *SataDiskInfo;
	SECURITY_PROTOCOL					*IdeSecurityInterface;
	SMART_INTERFACE						*SMARTInterface;
	POWER_MGMT_INTERFACE				*PowerMgmtInterface;

    DLINK                               SataDeviceLink; 
    DLIST                               PMSataDeviceList;         // for devices behind Port Multiplier
    DLINK                               PMSataDeviceLink; 
}SATA_DEVICE_INTERFACE;

typedef struct{
	BOOLEAN         RaidDriverMode;				// Set to TRUE For UEFI Raid driver and FALSE for Legacy Raid option rom 
    BOOLEAN         AhciBusAtapiSupport;        // Set to FALSE For UEFI Raid driver and TRUE for Legacy Raid option rom 
    BOOLEAN         DriverLedOnAtapiEnable;     // Set to TRUE to enable the Drive LED on ATAPI Enable (DLAE) bit
    BOOLEAN         PowerUpInStandbySupport;
    BOOLEAN         PowerUpInStandbyMode;
    BOOLEAN         DipmSupport;                  // Set to TRUE to Support the Device initiated power management.
    BOOLEAN         DipmEnable;                   // Set to TRUE to Enable the Device initiated power management.
    BOOLEAN         DeviceSleepSupport;           // Set to TRUE to Support the Device Sleep
    BOOLEAN         DeviceSleepEnable;   
} AHCI_PLATFORM_POLICY_PROTOCOL;

#pragma pack()

#endif // #ifndef GUID_VARIABLE_DEFINITION
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************