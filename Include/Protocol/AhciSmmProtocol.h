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
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciSmm/AhciSmmProtocol.h 7     11/24/14 11:57p Kapilporwal $
//
// $Revision: 7 $
//
// $Date: 11/24/14 11:57p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciSmm/AhciSmmProtocol.h $
// 
// 7     11/24/14 11:57p Kapilporwal
// [TAG]  		EIP191939
// [Category]  	Improvement
// [Description]  	Issue about BIG_REAL_MODE_MMIO_ACCESS of AHCI module
// [Files]  		AI13.bin
// AHCIACC.ASM
// AhciInt13Dxe.c
// AhciInt13Dxe.dxs
// AhciInt13Smm.c
// AhciInt13Smm.cif
// AhciInt13Smm.dxs
// AhciInt13Smm.h
// AhciInt13Smm.mak
// AhciInt13Smm.sdl
// AInt13.c
// Aint13.cif
// AInt13.h
// AhciSmm.c
// AhciSmm.h
// AhciSmmProtocol.h
// 
// 6     5/05/11 7:39a Rameshr
// [TAG]  		EIP51884
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Build error in pervious EIP 51884 check-in
// [RootCause]  	Atapi structure was missing.
// [Solution]  	Added Atapi Structure into AHCI_BUS_SMM_PROTOCOL
// [Files]  		AhciSmmProtocol.h
// 
// 5     3/15/11 4:13a Rameshr
// [TAG]- EIP 51884
// [Category]- New Feature
// [Description]- Added packet command function in AhciSMM for sending
// command in SMM handler
// [Files]- AhciSmm.c, AhciSmm.h, AhciSmmProtocols.h
// 
// 4     2/11/11 4:12a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AhciSmmProtocol.h
// 
// 3     5/07/10 2:31p Krishnakumarg
// Updated the date in AMI header
// 
// 2     5/07/10 11:48a Krishnakumarg
// Updated the AMI Header
// 
// 1     4/28/09 6:39p Rameshr
// Initial Check-in
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//--------------------------------------------------------------------------
//
// Name: AHCISmmProtocol.h
//
// Description: Protocol definition
//
//--------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _EFI_AHCI_SMM_PROTOCOLS_H_
#define _EFI_AHCI_SMM_PROTOCOLS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define AHCI_SMM_PROTOCOL_GUID \
        {0xB2FA5764, 0x3B6E, 0x43D3, 0x91, 0xDF, 0x87, 0xD1, 0x5A, 0x3E, 0x56, 0x68}

GUID_VARIABLE_DECLARATION(gAhciSmmProtocolGuid,AHCI_SMM_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION

#include <Protocol\PAhciBus.h>

typedef struct _AHCI_BUS_SMM_PROTOCOL AHCI_BUS_SMM_PROTOCOL;

typedef EFI_STATUS (*EFI_AHCI_SMM_SATA_DEV_PIO_DATA_IN) (
    IN AHCI_BUS_SMM_PROTOCOL                    *SataDevInterface, 
    IN OUT COMMAND_STRUCTURE                    *CommandStructure,
    UINT8                                       PortNumber,
    UINT8                                       PMPortNumber, 
    DEVICE_TYPE                                 DeviceType,
    IN BOOLEAN                                  READWRITE

);

typedef EFI_STATUS (*EFI_AHCI_SMM_SATA_DEV_DMA_DATA_IN) (
    IN AHCI_BUS_SMM_PROTOCOL                   *SataDevInterface, 
    IN OUT COMMAND_STRUCTURE                    *CommandStructure,
    UINT8                                       PortNumber,
    UINT8                                       PMPortNumber, 
    DEVICE_TYPE                                 DeviceType,
    IN BOOLEAN                                  READWRITE
);

typedef EFI_STATUS (*EFI_AHCI_SMM_SATA_DEV_NON_DATA_CMD) (
    IN AHCI_BUS_SMM_PROTOCOL                    *SataDevInterface, 
    IN COMMAND_STRUCTURE                        CommandStructure,
    UINT8                                       PortNumber,
    UINT8                                       PMPortNumber, 
   	DEVICE_TYPE                                 DeviceType
);

typedef EFI_STATUS (*EFI_AHCI_SMM_SATA_DEV_PACKET_CMD) (
    IN AHCI_BUS_SMM_PROTOCOL                    *SataDevInterface, 
    IN COMMAND_STRUCTURE                        *CommandStructure,
    IN BOOLEAN                                  READWRITE,
    UINT8                                       PortNumber,
    UINT8                                       PMPortNumber, 
   	DEVICE_TYPE                                 DeviceType
);

typedef EFI_STATUS (*EFI_AHCI_SMM_INIT_ON_S3) (
    IN AHCI_BUS_SMM_PROTOCOL                    *SataDevInterface, 
    IN UINT8                                    Port
);

typedef struct _AHCI_BUS_SMM_PROTOCOL{
    UINT64                                      AhciBaseAddress;
    UINT32                                      PortCommandTableBaseAddr;
    UINT32                                      PortCommandListBaseAddr;
    UINT32                                      PortFISBaseAddr;
    UINT8                                       PortNumber;
    UINT8                                       PMPortNumber; 
   	DEVICE_TYPE                                 DeviceType;
	ATAPI_DEVICE			                    AtapiDevice;
    EFI_AHCI_SMM_INIT_ON_S3                     AhciSmmInitPortOnS3Resume;
    EFI_AHCI_SMM_SATA_DEV_PIO_DATA_IN           AhciSmmExecutePioDataCommand;
    EFI_AHCI_SMM_SATA_DEV_DMA_DATA_IN           AhciSmmExecuteDmaDataCommand;
    EFI_AHCI_SMM_SATA_DEV_NON_DATA_CMD          AhciSmmExecuteNonDataCommand;
    EFI_AHCI_SMM_SATA_DEV_PACKET_CMD            AhciSmmExecutePacketCommand;
}AHCI_BUS_SMM_PROTOCOL;

#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif
#endif

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
