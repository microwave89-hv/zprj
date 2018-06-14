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
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciSmm/AhciSmm.h 8     11/24/14 11:56p Kapilporwal $
//
// $Revision: 8 $
//
// $Date: 11/24/14 11:56p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciSmm/AhciSmm.h $
// 
// 8     11/24/14 11:56p Kapilporwal
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
// 7     9/27/11 3:00a Rajeshms
// [TAG]  		EIP69295
// [Category]  	Improvement
// [Description]  	The Timeout values used by IDE and AHCI drivers are
// made as SDL tokens, so that the timeout values can be varied.
// [Files]  		IdeBusBoard.c, CORE_DXE.sdl, AhciSmm.h, AhciBus.h, IDESMM.h,
// Ata.c, Atapi.c, IdeBus.c, IdeBus.h, IdeBusMaster.c, IdeBusBoard.h
// 
// 6     3/15/11 4:12a Rameshr
// [TAG]- EIP 51884
// [Category]- New Feature
// [Description]- Added packet command function in AhciSMM for sending
// command in SMM handler
// [Files]- AhciSmm.c, AhciSmm.h, AhciSmmProtocols.h
// 
// 5     2/11/11 4:11a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AhciSmm.mak
// AhciSmm.dxs
// AhciSmm.c
// AhciSmm.h
// 
// 4     9/29/10 1:20p Mirk
// [TAG]		EIP44641
// [Synopsis]	Calpella: Build error when Token INDEX_DATA_PORT_ACCESS = 1
// in AhciSrc.sdl
// [Category]	Defect
// [Severity]	Normal
// [Resolution]	Updated AhciSmm.h and AhciSmm.mak to resolve build errors.
// [Files]		AhciSmm.h, AhciSmm.mak
// 
// 3     5/07/10 2:30p Krishnakumarg
// Updated the date in AMI header
// 
// 2     5/07/10 12:38p Krishnakumarg
// Updated the AMI header.
// 
// 1     4/28/09 6:39p Rameshr
// Initial Check-in
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//--------------------------------------------------------------------------
//
// Name: AHCISmm.h
//
// Description: Smm function definition
//
//--------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _EFI_AHCI_SMM_H_
#define _EFI_AHCI_SMM_H_

#ifndef ATAPI_BUSY_CLEAR_TIMEOUT
#define     ATAPI_BUSY_CLEAR_TIMEOUT            16000       // 16sec
#endif

#ifndef DMA_ATA_COMMAND_COMPLETE_TIMEOUT
#define     DMA_ATA_COMMAND_COMPLETE_TIMEOUT    5000            // 5Sec
#endif

#ifndef DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT
#define     DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT  16000           // 16Sec
#endif

#define     COMMAND_LIST_SIZE_PORT              0x800
#define     TIMEOUT_1SEC                        1000            // 1sec Serial ATA 1.0 Sec 5.2


#define PCI_CFG_ADDR(bus,dev,func,reg) \
    ((VOID*)(UINTN) (PCIEX_BASE_ADDRESS + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg))


EFI_STATUS
AhciSmmExecuteNonDataCommand (
    AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
    COMMAND_STRUCTURE                   CommandStructure,
    UINT8                               PortNumber,
    UINT8                               PMPortNumber, 
    DEVICE_TYPE                         DeviceType
);

EFI_STATUS
AhciSmmExecutePioDataCommand (
    AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
    COMMAND_STRUCTURE                   *CommandStructure,
    UINT8                               PortNumber,
    UINT8                               PMPortNumber, 
    DEVICE_TYPE                         DeviceType,
    BOOLEAN                             READWRITE 
    );

EFI_STATUS
AhciSmmExecuteDmaDataCommand (
    AHCI_BUS_SMM_PROTOCOL        *SataDevInterface, 
    COMMAND_STRUCTURE            *CommandStructure,
    UINT8                        PortNumber,
    UINT8                        PMPortNumber, 
    DEVICE_TYPE                  DeviceType,
    BOOLEAN                      READWRITE 
);

EFI_STATUS
AhciSmmInitPortOnS3Resume(
    AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
    UINT8                               Port
    );

EFI_STATUS
StartController (
    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,
    IN UINT32                               CIBitMask
);

EFI_STATUS
ReadWritePMPort (
    IN AHCI_BUS_SMM_PROTOCOL       *SataDevInterface,
    IN UINT8                        Port,
    IN UINT8                        RegNum,
    IN OUT UINT32                   *Data,
    IN BOOLEAN                      READWRITE
);
EFI_STATUS 
AhciSmmExecutePacketCommand (
    IN AHCI_BUS_SMM_PROTOCOL                *SataDevInterface, 
    IN COMMAND_STRUCTURE                    *CommandStructure,
    IN BOOLEAN                              READWRITE,
    UINT8                                   PortNumber,
    UINT8                                   PMPortNumber, 
    DEVICE_TYPE                             DeviceType
 );

#endif

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
