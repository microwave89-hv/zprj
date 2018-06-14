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
// $Header: /Alaska/SOURCE/Core/Modules/PciBus/DeviceIo.c 1     3/12/07 12:02p Yakovlevs $
//
// $Revision: 1 $
//
// $Date: 3/12/07 12:02p $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/PciBus/DeviceIo.c $
// 
// 1     3/12/07 12:02p Yakovlevs
// 
// 3     4/03/06 5:17p Felixp
// Updated to support new PCI infrastructure
// 
// 1     4/01/05 12:45p Robert
// Initial Checkin
// 
// 1     1/21/05 6:27p Sivagarn
// NB Chipset Template Initial Checkin - Based on template version 0001
//
//
//*****************************************************************************

//<AMI_FHDR_START>
//
// Name:	DeviceIo_c
//
// Description:	This file contains the DeviceIo Protocol and its construction.
//
//<AMI_FHDR_END>
//*****************************************************************************

#include <Token.h>
#if AMI_ROOT_BRIDGE_SUPPORT == 1
/****** DO NOT WRITE ABOVE THIS LINE *******/

#include "PciHostBridge.h"
#include <Protocol\PciIo.h>
#include <Protocol\DevicePath.h>

typedef struct {
	EFI_DEVICE_IO_INTERFACE			DeviceIo;
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*RootBridgeIo;
	EFI_DEVICE_PATH_PROTOCOL					*DevicePath;
} PRIVATE_DEVICE_IO;

EFI_GUID gPciIoProtocolGuid	= EFI_PCI_IO_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathProtocolGuid=EFI_DEVICE_PATH_PROTOCOL_GUID;

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: DeviceIoMemRead
//
// Description:	Read memory into a buffer.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN EFI_IO_WIDTH				Width
//	IN UINT64					Address
//	IN UINTN					Count
//	IN OUT VOID					*Buffer
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: PciMemRead
//
// Notes:
//  Here is the control flow of this function:
//	1. Validate width parameter. The parameter is a subset of the one used by RootBridgeIo.
//  2. Call PciRootBridgeIo PciMemRead and return its Status.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoMemRead (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_WIDTH				Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
)
{
	if (Width >= IO_UINT64) return EFI_INVALID_PARAMETER;
	return PciMemRead (((PRIVATE_DEVICE_IO*)This)->RootBridgeIo,Width,Address,Count,Buffer);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoMemWrite
//
// Description:	Write memory from a buffer.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN EFI_IO_WIDTH				Width
//	IN UINT64					Address
//	IN UINTN					Count
//	IN OUT VOID					*Buffer
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: PciMemWrite
//
// Notes:
//  Here is the control flow of this function:
//	1. Validate width parameter. The parameter is a subset of the one used by RootBridgeIo.
//  2. Call PciRootBridgeIo PciMemWrite and return its Status.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoMemWrite (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_WIDTH				Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
)
{
	if (Width >= IO_UINT64) return EFI_INVALID_PARAMETER;
	return PciMemWrite (((PRIVATE_DEVICE_IO*)This)->RootBridgeIo,Width,Address,Count,Buffer);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoIoRead
//
// Description:	Read Io into a buffer.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN EFI_IO_WIDTH				Width
//	IN UINT64					Address
//	IN UINTN					Count
//	IN OUT VOID					*Buffer
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: PciIoRead
//
// Notes:
//  Here is the control flow of this function:
//	1. Validate width parameter. The parameter is a subset of the one used by RootBridgeIo.
//  2. Call PciRootBridgeIo PciIoRead and return its Status.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoIoRead (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_WIDTH				Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
)
{
	if (Width >= IO_UINT64) return EFI_INVALID_PARAMETER;
	return PciIoRead (((PRIVATE_DEVICE_IO*)This)->RootBridgeIo,Width,Address,Count,Buffer);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoIoWrite
//
// Description:	Write Io from a buffer.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
///	IN EFI_IO_WIDTH				Width
//	IN UINT64					Address
//	IN UINTN					Count
//	IN OUT VOID					*Buffer
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: PciIoWrite
//
// Notes:
//  Here is the control flow of this function:
//	1. Validate width parameter. The parameter is a subset of the one used by RootBridgeIo.
//  2. Call PciRootBridgeIo PciIoWrite and return its Status.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoIoWrite (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_WIDTH				Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
)
{
	if (Width >= IO_UINT64) return EFI_INVALID_PARAMETER;
	return PciIoWrite (((PRIVATE_DEVICE_IO*)This)->RootBridgeIo,Width,Address,Count,Buffer);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoPciRead
//
// Description:	Read Pci registers into a buffer.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN EFI_IO_WIDTH				Width
//	IN UINT64					Address
//	IN UINTN					Count
//	IN OUT VOID					*Buffer
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: PciRead
//
// Notes:
//  Here is the control flow of this function:
//	1. Validate width parameter. The parameter is a subset of the one used by RootBridgeIo.
//  2. Call PciRootBridgeIo PciRead and return its Status.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoPciRead (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_WIDTH				Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
)
{
	if (Width >= IO_UINT64) return EFI_INVALID_PARAMETER;
	return PciRead (((PRIVATE_DEVICE_IO*)This)->RootBridgeIo,Width,Address,Count,Buffer);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoPciWrite
//
// Description:	Write Pci registers from a buffer.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN EFI_IO_WIDTH				Width
//	IN UINT64					Address
//	IN UINTN					Count
//	IN OUT VOID					*Buffer
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: PciWrite
//
// Notes:
//  Here is the control flow of this function:
//	1. Validate width parameter. The parameter is a subset of the one used by RootBridgeIo.
//  2. Call PciRootBridgeIo PciWrite and return its Status.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoPciWrite (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_WIDTH				Width,
	IN UINT64					Address,
	IN UINTN					Count,
	IN OUT VOID					*Buffer
)
{
	if (Width >= IO_UINT64) return EFI_INVALID_PARAMETER;
	return PciWrite (((PRIVATE_DEVICE_IO*)This)->RootBridgeIo,Width,Address,Count,Buffer);
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoPciDevicePath
//
// Description:	Get a device path for a Pci Bus/Device/Function.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN UINT64					PciAddress
//	IN OUT EFI_DEVICE_PATH		**PciDevicePath
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: LocateHandleBuffer HandleProtocol GetLocation DPCopy FreePool
//
// Notes:
//  Here is the control flow of this function:
//	1. Locate handes of the PciIo Protocol.
//  2. Call the PciIo function GetLocation to find the matching PciDevicePath.
//  3. If match found, copy the the DevicePath on the same handle as the PciIo
//     Protocol. Otherwise, return EFI_UNSUPPORTED.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoPciDevicePath (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN UINT64					PciAddress,
	IN OUT EFI_DEVICE_PATH_PROTOCOL		**PciDevicePath
)
{
	EFI_PCI_IO_PROTOCOL	*PciIo;
	EFI_DEVICE_PATH_PROTOCOL		*Path;

	UINTN		Segment, Bus, Device, Function;
	EFI_STATUS	Status;
	UINTN		NoHandles;
	EFI_HANDLE	*HandleBuffer;
	UINTN		i;

	EFI_PCI_CONFIGURATION_ADDRESS PciAddr;
	*(UINT64*)&PciAddr = PciAddress;

	Status = pBS->LocateHandleBuffer (
		ByProtocol,
		&gPciIoProtocolGuid,
		NULL,
		&NoHandles,
		&HandleBuffer);
	if (EFI_ERROR(Status)) return Status;

	for(i = 0; i < NoHandles; ++i)
	{
		Status = pBS->HandleProtocol(
			HandleBuffer[i],
			&gPciIoProtocolGuid,
			&PciIo
			);
		if (EFI_ERROR(Status)) goto Exit;			//Should never get an error here.

		Status = PciIo->GetLocation(PciIo,
			&Segment,
			&Bus,
			&Device,
			&Function
		);
		if (EFI_ERROR(Status)) goto Exit;			//Should never get an error here.


		//Note: Difference in DeviceIo and PciRootBridgeIo defintion of PciAddress for bits [64:32].
		//DeviceIo [39:32] = Segment  and PciRootBridgeIo [64:32] = Extended register
		if (Segment != (PciAddr.ExtendedRegister&0xff)) continue;
		if (Bus != PciAddr.Bus || Device != PciAddr.Device || Function != PciAddr.Function) continue;

		Status = pBS->HandleProtocol(
			HandleBuffer[i],
			&gEfiDevicePathProtocolGuid,
			&Path
			);
		if (EFI_ERROR(Status))
		{
			Status = EFI_UNSUPPORTED;	//Should never get an error here. Should always have a device path.
			goto Exit;
		}

		*PciDevicePath = DPCopy(Path);					//Copy device path.
		Status = EFI_SUCCESS;
		goto Exit;
	}
	Status = EFI_UNSUPPORTED;
Exit:
	pBS->FreePool(HandleBuffer);
	return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoMap
//
// Description:	Map a device address to a host address.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN EFI_IO_OPERATION_TYPE	Operation
//	IN EFI_PHYSICAL_ADDRESS		*HostAddress
//	IN OUT UINTN				*NumberOfBytes
//	OUT EFI_PHYSICAL_ADDRESS	*DeviceAddress
//	OUT VOID					**Mapping
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: Map
//
// Notes:
//  Here is the control flow of this function:
//	1. Verify Operation. It is a subset of the PciRootBridgeIo Map Operation.
//  2. Verify valid map address range. Can not map any addresses over 4G.
//  3. Call PciRootBridgeIo Map.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoMap (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_IO_OPERATION_TYPE	Operation,
	IN EFI_PHYSICAL_ADDRESS		*HostAddress,
	IN OUT UINTN				*NumberOfBytes,
	OUT EFI_PHYSICAL_ADDRESS	*DeviceAddress,
	OUT VOID					**Mapping
)
{
	if ((unsigned)Operation > EfiBusMasterCommonBuffer) return EFI_INVALID_PARAMETER;
	if ((*HostAddress + *NumberOfBytes) > 0xffffffff) return EFI_UNSUPPORTED;

	return Map(
		((PRIVATE_DEVICE_IO*)This)->RootBridgeIo,
		Operation,
		(VOID*)(*HostAddress),
		NumberOfBytes,
		DeviceAddress,
		Mapping);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoUnmap
//
// Description:	Unmap a device.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN VOID						*Mapping
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: Unmap
//
// Notes:
//  Here is the control flow of this function:
//	1. Call PciRootBridgeIo UnMap.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoUnmap (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN VOID						*Mapping
)
{
	return Unmap(((PRIVATE_DEVICE_IO*)This)->RootBridgeIo, Mapping);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoAllocateBuffer
//
// Description:	Allocate a buffer.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN EFI_ALLOCATE_TYPE		Type
//	IN EFI_MEMORY_TYPE			MemoryType
//	IN UINTN					Pages
//	IN OUT EFI_PHYSICAL_ADDRESS	*HostAddress
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: AllocatePages
//
// Notes:
//  Here is the control flow of this function:
//	1. Verify inputs to function.
//  2. If allocate type is AllocateAnyPages, change max address of 4G-1.
//	3. If allocate type is AllocateMaxAddress of 4G, change max address to 4G-1.
//  4. If allocate type is AllocateAddress, verify address is les than 4G.
//  3. Call BootServices Alloate.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoAllocateBuffer (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN EFI_ALLOCATE_TYPE		Type,
	IN EFI_MEMORY_TYPE			MemoryType,
	IN UINTN					Pages,
	IN OUT EFI_PHYSICAL_ADDRESS	*HostAddress
)
{
	EFI_STATUS				Status;
	EFI_ALLOCATE_TYPE		AllocateType = Type;	//May be changed in the code below.


	if (HostAddress == NULL) return EFI_INVALID_PARAMETER;
	if (AllocateType >= MaxAllocateType) return EFI_INVALID_PARAMETER;

	// The only valid memory types are EfiBootServicesData and EfiRuntimeServicesData
	if (MemoryType != EfiBootServicesData && MemoryType != EfiRuntimeServicesData)
		return EFI_INVALID_PARAMETER;

	if (AllocateType == AllocateAnyPages)
	{
		AllocateType = AllocateMaxAddress;
		*HostAddress = 0xffffffff;
	} else if (AllocateType == AllocateMaxAddress && *HostAddress > 0xffffffff)
	{
		*HostAddress = 0xffffffff;
	} else	//AllocateAddress
	{
		if (*HostAddress + 4096 * Pages > 0xffffffff) return EFI_UNSUPPORTED;
	}


	Status = pBS->AllocatePages (AllocateType, MemoryType, Pages, HostAddress);
	if (EFI_ERROR(Status)) return Status;

	return EFI_SUCCESS;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoFlush
//
// Description:	Flush cache lines.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE *This
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: Flush
//
// Notes:
//  Here is the control flow of this function:
//	1. Call PciRootBridgeIo Flush.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoFlush (
	IN EFI_DEVICE_IO_INTERFACE *This
)
{
	return Flush(((PRIVATE_DEVICE_IO*)This)->RootBridgeIo);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	DeviceIoFreeBuffer
//
// Description:	Free a buffer.
//
// Input:
//	IN EFI_DEVICE_IO_INTERFACE	*This
//	IN UINTN					Pages
//	IN EFI_PHYSICAL_ADDRESS		HostAddress
//
// Output:
//	EFI_STATUS
//
// Modified:
//
// Referrals: FreeBuffer
//
// Notes:
//  Here is the control flow of this function:
//	1. Call PciRootBridgeIo FreeBuffer.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS DeviceIoFreeBuffer (
	IN EFI_DEVICE_IO_INTERFACE	*This,
	IN UINTN					Pages,
	IN EFI_PHYSICAL_ADDRESS		HostAddress
)
{
	return FreeBuffer(((PRIVATE_DEVICE_IO*)This)->RootBridgeIo,Pages,(VOID*)HostAddress);
}


EFI_DEVICE_IO_INTERFACE gDeviceIo = {
	{DeviceIoMemRead,DeviceIoMemWrite},
	{DeviceIoIoRead,DeviceIoIoWrite},
	{DeviceIoPciRead,DeviceIoPciWrite},
	DeviceIoMap,
	DeviceIoPciDevicePath,
	DeviceIoUnmap,
	DeviceIoAllocateBuffer,
	DeviceIoFlush,
	DeviceIoFreeBuffer
};


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:	ConstructDeviceIoProtocol
//
// Description:	Construct a DeviceIo protocol.
//
// Input:
// IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*RootBridgeIo
// IN EFI_DEVICE_PATH					*Path
//
// Output:
//	EFI_DEVICE_IO_INTERFACE *
//
// Modified:
//
// Referrals: AllocatePool
//
// Notes:
//  Here is the control flow of this function:
//	1. Allocate moemory for Private DeviceIo.
//  2. Copy DeviceIo functions to private structure.
//  3. Copy pointer RootBridgeIo to private structure.
//  4. Copy pointer to RootBridgeIo path to private structure.
//  5. Return pointer to private structure.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_DEVICE_IO_INTERFACE * ConstructDeviceIoProtocol(EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	* RootBridgeIo, EFI_DEVICE_PATH_PROTOCOL *Path)
{
	EFI_STATUS			Status;
	PRIVATE_DEVICE_IO	*PrivateDeviceIo;

	Status = pBS->AllocatePool(EfiBootServicesData, sizeof(PRIVATE_DEVICE_IO),&PrivateDeviceIo);
	if (EFI_ERROR(Status)) return 0;

	PrivateDeviceIo->DeviceIo = gDeviceIo;
	PrivateDeviceIo->RootBridgeIo = RootBridgeIo;
	PrivateDeviceIo->DevicePath = Path;

	return (EFI_DEVICE_IO_INTERFACE*)PrivateDeviceIo;
}


/****** DO NOT WRITE BELOW THIS LINE *******/
#endif	//#if AMI_ROOT_BRIDGE_SUPPORT == 1


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
