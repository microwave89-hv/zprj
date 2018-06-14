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
// $Header: /Alaska/BIN/Core/Include/Protocol/PciRootBridgeIo.h 4     2/05/11 2:33p Artems $
//
// $Revision: 4 $
//
// $Date: 2/05/11 2:33p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/PciRootBridgeIo.h $
// 
// 4     2/05/11 2:33p Artems
// Added EFI_PCI_CONFIGURATION_ADDRESS definition
// 
// 3     10/06/08 3:32p Yakovlevs
// UEFI 2.1 Update
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     2/05/04 6:26p Markw
// Added EFI_PCI_CONFIGURATION_ADDRESS structure.
// 
// 1     2/03/04 10:23a Markw
// 
// 1     2/03/04 10:22a Markw
// 
// 1     1/26/04 3:25p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: PciRootBridgeIo_h
//
// Description:	Provides functions to access memory/io/pci behind a Pci bridge.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __PCI_ROOT_BRIDGE_IO_PROTOCOL_H__
#define __PCI_ROOT_BRIDGE_IO_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID \
	{0x2F707EBB,0x4A1A,0x11d4,0x9A,0x38,0x00,0x90,0x27,0x3F,0xC1,0x4D}

GUID_VARIABLE_DECLARATION(gEfiPciRootBridgeIoProtocolGuid,EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID);

//*******************************************************
// EFI PCI Root Bridge I/O Protocol Attribute bits
//*******************************************************
#define EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO	0x0001
#define EFI_PCI_ATTRIBUTE_ISA_IO				0x0002
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO		0x0004
#define EFI_PCI_ATTRIBUTE_VGA_MEMORY			0x0008
#define EFI_PCI_ATTRIBUTE_VGA_IO				0x0010
#define EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO		0x0020
#define EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO		0x0040
#define EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE	0x0080
#define EFI_PCI_ATTRIBUTE_MEMORY_CACHED			0x0800
#define EFI_PCI_ATTRIBUTE_MEMORY_DISABLE		0x1000
#define EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE	0x8000
//UIEFI 2.1 update
#define EFI_PCI_ATTRIBUTE_ISA_IO_16             0x10000
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO_16     0x20000
#define EFI_PCI_ATTRIBUTE_VGA_IO_16             0x40000

//*******************************************************
// EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH
//*******************************************************
typedef enum {
	EfiPciWidthUint8,
	EfiPciWidthUint16,
	EfiPciWidthUint32,
	EfiPciWidthUint64,
	EfiPciWidthFifoUint8,
	EfiPciWidthFifoUint16,
	EfiPciWidthFifoUint32,
	EfiPciWidthFifoUint64,
	EfiPciWidthFillUint8,
	EfiPciWidthFillUint16,
	EfiPciWidthFillUint32,
	EfiPciWidthFillUint64,
	EfiPciWidthMaximum
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH;
	
//*******************************************************
// EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION
//*******************************************************
typedef enum {
	EfiPciOperationBusMasterRead,
	EfiPciOperationBusMasterWrite,
	EfiPciOperationBusMasterCommonBuffer,
	EfiPciOperationBusMasterRead64,
	EfiPciOperationBusMasterWrite64,
	EfiPciOperationBusMasterCommonBuffer64,
	EfiPciOperationMaximum
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION;


typedef struct {
	UINT8	Register;
	UINT8	Function;
	UINT8	Device;
	UINT8	Bus;
	UINT32	ExtendedRegister;
} EFI_PCI_CONFIGURATION_ADDRESS;

#define EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS EFI_PCI_CONFIGURATION_ADDRESS

typedef struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL;

//*******************************************************
// EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN UINT64									Address,
	IN UINT64									Mask,
	IN UINT64									Value,
	IN UINT64									Delay,
	OUT UINT64									*Result
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN UINT64									Address,
	IN UINT64									Mask,
	IN UINT64									Value,
	IN UINT64									Delay,
	OUT UINT64									*Result
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN UINT64									Address,
	IN UINTN									Count,
	IN OUT VOID									*Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_COPY_MEM) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN UINT64									DestAddress,
	IN UINT64									SrcAddress,
	IN UINTN									Count
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_MAP) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL				*This,
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION	Operation,
	IN VOID											*HostAddress,
	IN OUT UINTN									*NumberOfBytes,
	OUT EFI_PHYSICAL_ADDRESS						*DeviceAddress,
	OUT VOID										**Mapping
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_UNMAP) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This,
	IN VOID								*Mapping
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ALLOCATE_BUFFER) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This,
	IN EFI_ALLOCATE_TYPE				Type,
	IN EFI_MEMORY_TYPE					MemoryType,
	IN UINTN 							Pages,
	OUT VOID 							**HostAddress,
	IN UINT64							Attributes
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FREE_BUFFER) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This,
	IN UINTN							Pages,
	IN VOID								*HostAddress
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FLUSH) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GET_ATTRIBUTES) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This,
	OUT UINT64							*Supports OPTIONAL,
	OUT UINT64							*Attributes OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_SET_ATTRIBUTES) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*This,
	IN UINT64							Attributes,
	IN OUT UINT64 						*ResourceBase OPTIONAL,
	IN OUT UINT64 						*ResourceLength OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_CONFIGURATION) (
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
	OUT VOID **Resources
);

//**********************************************************************
//<AMI_THDR_START>
//
// Name:        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS
//
// Description: This provides north bridge functions to open, close, lock,
//              and describe SMM space.
//
// Fields:     Name        Type					Description
//        ------------------------------------------------------------
//		  Read	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM	- definition to read Mem/Io/Pci.
//		  Write	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM  - definition to read Mem/Io/Pci.
//<AMI_THDR_END>
//**********************************************************************
typedef struct {
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM	Read;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM	Write;
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS;

//**********************************************************************
//<AMI_THDR_START>
//
// Name:        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL
//
// Description: Functions to access Pci Root Bridge for reading/writting
//              Memory/IO/config space.
//
// Fields:     Name        Type					Description
//        ------------------------------------------------------------
//	ParentHandle	EFI_HANDLE 
//	PollMem			EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM
//	PollIo			EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM		
//	Mem				EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS			
//	Io				EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS			
//	Pci				EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS			
//	CopyMem			EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_COPY_MEM		
//	Map				EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_MAP				
//	Unmap			EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_UNMAP			
//	AllocateBuffer	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ALLOCATE_BUFFER	
//	FreeBuffer		EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FREE_BUFFER		
//	Flush			EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FLUSH			
//	GetAttributes	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GET_ATTRIBUTES	
//	SetAttributes	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_SET_ATTRIBUTES	
//	Configuration	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_CONFIGURATION	
//	SegmentNumber	UINT32											
//
//<AMI_THDR_END>
//**********************************************************************
struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL {
	EFI_HANDLE ParentHandle;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM		PollMem;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM		PollIo;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS			Mem;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS			Io;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS			Pci;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_COPY_MEM		CopyMem;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_MAP				Map;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_UNMAP			Unmap;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ALLOCATE_BUFFER	AllocateBuffer;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FREE_BUFFER		FreeBuffer;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FLUSH			Flush;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GET_ATTRIBUTES	GetAttributes;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_SET_ATTRIBUTES	SetAttributes;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_CONFIGURATION	Configuration;
	UINT32											SegmentNumber;
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
