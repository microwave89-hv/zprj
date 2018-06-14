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
// $Header: /Alaska/BIN/Core/Include/Protocol/DeviceIo.h 4     3/13/06 1:40a Felixp $
//
// $Revision: 4 $
//
// $Date: 3/13/06 1:40a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/DeviceIo.h $
// 
// 4     3/13/06 1:40a Felixp
// 
// 3     8/15/05 9:03a Andriyn
// 
// 2     3/04/05 10:33a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     8/26/04 3:56p Markw
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	DeviceIo_h
//
// Description:	This file is an include file used to define the Protocol for the
//		        DeviceIo Protocol.
//
//<AMI_FHDR_END>
//*****************************************************************************

#ifndef __DEVICE_IO_PROTOCOL_H__
#define __DEVICE_IO_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

// af6ac311-84c3-11d2-8e3c-00a0c969723b }
#define DEVICE_IO_PROTOCOL \
	{0xaf6ac311,0x84c3,0x11d2,0x8e,0x3c,0x00,0xa0,0xc9,0x69,0x72,0x3b}

typedef struct _EFI_DEVICE_IO_INTERFACE EFI_DEVICE_IO_INTERFACE;

//*******************************************************
// EFI_IO_WIDTH
//*******************************************************
typedef enum {
	IO_UINT8	= 0,
	IO_UINT16	= 1,
	IO_UINT32	= 2,
	IO_UINT64	= 3
} EFI_IO_WIDTH;

//*******************************************************
// EFI_IO_OPERATION_TYPE
//*******************************************************
typedef enum {
	EfiBusMasterRead,
	EfiBusMasterWrite,
	EfiBusMasterCommonBuffer
} EFI_IO_OPERATION_TYPE;


//*******************************************************
// EFI_DEVICE_IO
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_DEVICE_IO) (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_WIDTH				Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
);
//*******************************************************
// EFI_IO_ACCESS
//*******************************************************
typedef struct {
	EFI_DEVICE_IO Read;
	EFI_DEVICE_IO Write;
} EFI_IO_ACCESS;

typedef EFI_STATUS (EFIAPI *EFI_PCI_DEVICE_PATH) (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN UINT64					PciAddress,
	IN OUT EFI_DEVICE_PATH_PROTOCOL		**PciDevicePath
);

typedef EFI_STATUS (EFIAPI *EFI_IO_MAP) (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_OPERATION_TYPE	Operation,
	IN EFI_PHYSICAL_ADDRESS		*HostAddress,
	IN OUT UINTN				*NumberOfBytes,
	OUT EFI_PHYSICAL_ADDRESS	*DeviceAddress,
	OUT VOID					**Mapping
);

typedef EFI_STATUS (EFIAPI *EFI_IO_UNMAP) (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN VOID						*Mapping
);

typedef EFI_STATUS (EFIAPI *EFI_IO_ALLOCATE_BUFFER) (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_ALLOCATE_TYPE		Type,
	IN EFI_MEMORY_TYPE			MemoryType,
	IN UINTN					Pages,
	IN OUT EFI_PHYSICAL_ADDRESS	*HostAddress
);

typedef EFI_STATUS (EFIAPI *EFI_IO_FLUSH) (
	IN EFI_DEVICE_IO_INTERFACE *This
);

typedef EFI_STATUS (EFIAPI *EFI_IO_FREE_BUFFER) (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN UINTN					Pages,
	IN EFI_PHYSICAL_ADDRESS		HostAddress
);

struct _EFI_DEVICE_IO_INTERFACE {
	EFI_IO_ACCESS			Mem;
	EFI_IO_ACCESS			Io;
	EFI_IO_ACCESS			Pci;
	EFI_IO_MAP				Map;
	EFI_PCI_DEVICE_PATH		PciDevicePath;
	EFI_IO_UNMAP			Unmap;
	EFI_IO_ALLOCATE_BUFFER	AllocateBuffer;
	EFI_IO_FLUSH			Flush;
	EFI_IO_FREE_BUFFER		FreeBuffer;
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
