//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Modules/Recovery/DeviceRecoveryBlockIo.h 1     12/01/05 9:35a Felixp $
//
// $Revision: 1 $
//
// $Date: 12/01/05 9:35a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/Recovery/DeviceRecoveryBlockIo.h $
// 
// 1     12/01/05 9:35a Felixp
// 
// 2     3/22/05 9:33p Felixp
// 
// 1     3/22/05 9:16p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DeviceRecoveryBlockIo.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __DeviceRecoveryBlockIo__H__
#define __DeviceRecoveryBlockIo__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#define EFI_PEI_VIRTUAL_BLOCK_IO_PPI \
{ 0x695d8aa1, 0x42ee, 0x4c46, 0x80, 0x5c,0x6e, 0xa6, 0xbc, 0xe7, 0x99, 0xe3 }

typedef struct _EFI_PEI_RECOVERY_BLOCK_IO_PPI EFI_PEI_RECOVERY_BLOCK_IO_PPI;

typedef EFI_STATUS (EFIAPI *EFI_PEI_GET_NUMBER_BLOCK_DEVICES) (
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
	OUT UINTN *NumberBlockDevices
);

//***********************************************************
// EFI_PEI_BLOCK_DEVICE_TYPE
//***********************************************************
typedef enum {
	LegacyFloppy = 0,
	IdeCDROM = 1,
	IdeLS120 = 2,
	UsbMassStorage = 3,
	MaxDeviceType
} EFI_PEI_BLOCK_DEVICE_TYPE;

//***************************************************
// EFI_PEI_BLOCK_IO_MEDIA
//***************************************************
typedef struct {
	EFI_PEI_BLOCK_DEVICE_TYPE DeviceType;
	BOOLEAN MediaPresent;
	UINTN LastBlock;
	UINTN BlockSize;
} EFI_PEI_BLOCK_IO_MEDIA;

typedef EFI_STATUS (EFIAPI *EFI_PEI_GET_DEVICE_MEDIA_INFORMATION) (
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
	IN UINTN DeviceIndex, OUT EFI_PEI_BLOCK_IO_MEDIA *MediaInfo
);

//*****************************************************
// EFI_PEI_LBA
//*****************************************************
typedef UINT64 EFI_PEI_LBA;

typedef EFI_STATUS (EFIAPI *EFI_PEI_READ_BLOCKS) (
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
	IN UINTN DeviceIndex, IN EFI_PEI_LBA StartLBA,
	IN UINTN BufferSize, OUT VOID *Buffer
);

struct _EFI_PEI_RECOVERY_BLOCK_IO_PPI {
	EFI_PEI_GET_NUMBER_BLOCK_DEVICES GetNumberOfBlockDevices;
	EFI_PEI_GET_DEVICE_MEDIA_INFORMATION GetBlockDeviceMediaInfo;
	EFI_PEI_READ_BLOCKS ReadBlocks;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
