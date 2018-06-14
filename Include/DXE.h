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
// $Header: /Alaska/BIN/Core/Include/DXE.h 5     2/05/11 1:54p Artems $
//
// $Revision: 5 $
//
// $Date: 2/05/11 1:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/DXE.h $
// 
// 5     2/05/11 1:54p Artems
// Changed DXE_SERVICES_REVISION to match PI_SPECIFICATION version
// 
// 4     10/12/06 1:00p Felixp
// 
// 3     10/07/06 10:17a Felixp
// UEFI 2.0 definitions added
// 
// 2     3/04/05 10:24a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 6     9/24/04 9:01p Yakovlevs
// 
// 5     3/26/04 12:44a Felixp
// 
// 4     3/23/04 4:56p Felixp
// 
// 3     3/19/04 10:30a Markw
// Added HOB_LIST_GUID.
// 
// 2     3/03/04 5:04p Felixp
// 
// 1     2/26/04 3:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	dxe.h
//
// Description:	DXE definitions
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __DXE__H__
#define __DXE__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <efi.h>

#define DXE_SERVICES_TABLE_GUID \
	{0x5ad34ba,0x6f02,0x4214,0x95,0x2e,0x4d,0xa0,0x39,0x8e,0x2b,0xb9}
#define HOB_LIST_GUID \
	{0x7739f24c,0x93d7,0x11d4,0x9a,0x3a,0x0,0x90,0x27,0x3f,0xc1,0x4d}
#define EFI_APRIORI_GUID \
	{0xfc510ee7,0xffdc,0x11d4,0xbd,0x41,0x0,0x80,0xc7,0x3c,0x88,0x81}

#define DXE_SERVICES_SIGNATURE 0x565245535f455844
#ifndef PI_SPECIFICATION_VERSION
#define DXE_SERVICES_REVISION 91
#else
#define DXE_SERVICES_REVISION PI_SPECIFICATION_VERSION
#endif

//Let's make it backward compatible
//#if EFI_SPECIFICATION_VERSION<0x20000
//#if EFI_SPECIFICATION_VERSION<0x20000
// Additional event types defined by DXE CIS
#define EVT_NOTIFY_SIGNAL_ALL               0x00000400
#define EVT_SIGNAL_READY_TO_BOOT            0x00000203
#define EVT_SIGNAL_LEGACY_BOOT              0x00000204
//#endif

//Legacy boot event group defined by PI DXE CIS 1.0
#define EFI_EVENT_LEGACY_BOOT_GUID \
   { 0x2a571201, 0x4966, 0x47f6, 0x8b, 0x86, 0xf3, 0x1e, 0x41, 0xf3, 0x2f, 0x10 }
#define EFI_EVENT_GROUP_DXE_DISPATCH \
    {0x7081e22f, 0xcac6, 0x4053, 0x94, 0x68, 0x67, 0x57, 0x82, 0xcf, 0x88, 0xe5}

//Define default memory attributes for MMIO and System Memory 
#define GCD_COMMON_MMIO_CAPS (EFI_MEMORY_UC | EFI_MEMORY_WT | EFI_MEMORY_WB | EFI_MEMORY_WP | EFI_MEMORY_RUNTIME)

// Global Coherencey Domain types
typedef enum {
	EfiGcdMemoryTypeNonExistent,
	EfiGcdMemoryTypeReserved,
	EfiGcdMemoryTypeSystemMemory,
	EfiGcdMemoryTypeMemoryMappedIo,
	EfiGcdMemoryTypeMaximum
}EFI_GCD_MEMORY_TYPE;

typedef enum {
	EfiGcdIoTypeNonExistent,
	EfiGcdIoTypeReserved,
	EfiGcdIoTypeIo,
	EfiGcdIoTypeMaximum
} EFI_GCD_IO_TYPE;

typedef enum {
	EfiGcdAllocateAnySearchBottomUp,
	EfiGcdAllocateMaxAddressSearchBottomUp,
	EfiGcdAllocateAddress,
	EfiGcdAllocateAnySearchTopDown,
	EfiGcdAllocateMaxAddressSearchTopDown,
	EfiGcdMaxAllocateType
} EFI_GCD_ALLOCATE_TYPE;

typedef struct {
	EFI_PHYSICAL_ADDRESS  BaseAddress;
	UINT64                Length;
	UINT64                Capabilities;
	UINT64                Attributes;
	EFI_GCD_MEMORY_TYPE   GcdMemoryType;
	EFI_HANDLE            ImageHandle;
	EFI_HANDLE            DeviceHandle;
} EFI_GCD_MEMORY_SPACE_DESCRIPTOR;

typedef struct {
	EFI_PHYSICAL_ADDRESS  BaseAddress;
	UINT64                Length;
	EFI_GCD_IO_TYPE       GcdIoType;
	EFI_HANDLE            ImageHandle;
	EFI_HANDLE            DeviceHandle;
} EFI_GCD_IO_SPACE_DESCRIPTOR;

typedef EFI_STATUS (*EFI_ADD_MEMORY_SPACE)(
	IN EFI_GCD_MEMORY_TYPE GcdMemoryType, 
	IN EFI_PHYSICAL_ADDRESS BaseAddress,
	IN UINT64 Length, IN UINT64 Capabilities
);

typedef EFI_STATUS (*EFI_ADD_IO_SPACE)(
	IN EFI_GCD_IO_TYPE GcdIoType, IN EFI_PHYSICAL_ADDRESS BaseAddress,
	IN UINT64 Length
);


typedef EFI_STATUS (*EFI_GET_MEMORY_SPACE_DESCRIPTOR)(
	IN  EFI_PHYSICAL_ADDRESS BaseAddress,
	OUT EFI_GCD_MEMORY_SPACE_DESCRIPTOR *Descriptor
);

typedef EFI_STATUS (*EFI_GET_IO_SPACE_DESCRIPTOR)(
	IN  EFI_PHYSICAL_ADDRESS BaseAddress,
	OUT EFI_GCD_IO_SPACE_DESCRIPTOR *Descriptor
);

typedef EFI_STATUS (*EFI_ALLOCATE_MEMORY_SPACE)(
	IN EFI_GCD_ALLOCATE_TYPE GcdAllocateType,
	IN EFI_GCD_MEMORY_TYPE GcdMemoryType, IN UINTN Alignment,
	IN UINT64 Length, IN OUT EFI_PHYSICAL_ADDRESS *BaseAddress,
	IN EFI_HANDLE ImageHandle,IN EFI_HANDLE DeviceHandle OPTIONAL
);

typedef EFI_STATUS (*EFI_ALLOCATE_IO_SPACE)(
	IN EFI_GCD_ALLOCATE_TYPE GcdAllocateType,
	IN EFI_GCD_IO_TYPE GcdIoType, IN UINTN Alignment,
	IN UINT64 Length, IN OUT EFI_PHYSICAL_ADDRESS *BaseAddress,
	IN EFI_HANDLE ImageHandle, IN EFI_HANDLE DeviceHandle OPTIONAL
);

typedef EFI_STATUS (*EFI_FREE_MEMORY_SPACE)(
	IN EFI_PHYSICAL_ADDRESS BaseAddress, IN UINT64 Length
);

typedef EFI_STATUS (*EFI_FREE_IO_SPACE)(
	IN EFI_PHYSICAL_ADDRESS BaseAddress, IN UINT64 Length
);

typedef EFI_STATUS (*EFI_SET_MEMORY_SPACE_ATTRIBUTES)(
	IN EFI_PHYSICAL_ADDRESS	BaseAddress,
	IN UINT64 Length, IN UINT64 Attributes
);

typedef EFI_STATUS (*EFI_REMOVE_MEMORY_SPACE)(
	IN EFI_PHYSICAL_ADDRESS BaseAddress, IN UINT64 Length
);

typedef EFI_STATUS (*EFI_REMOVE_IO_SPACE)(
	IN EFI_PHYSICAL_ADDRESS BaseAddress, IN UINT64 Length
);

typedef EFI_STATUS (*EFI_GET_MEMORY_SPACE_MAP)(
	OUT UINTN *NumberOfDescriptors,
	OUT EFI_GCD_MEMORY_SPACE_DESCRIPTOR **MemorySpaceMap
);

typedef EFI_STATUS (*EFI_GET_IO_SPACE_MAP)(
	OUT UINTN *NumberOfDescriptors,
	OUT EFI_GCD_IO_SPACE_DESCRIPTOR	**IoSpaceMap
);

// Dispatcher Services
typedef EFI_STATUS (*EFI_DISPATCH) ();
typedef EFI_STATUS (*EFI_SCHEDULE) (
	IN EFI_HANDLE FirmwareVolumeHandle, IN EFI_GUID *FileName
);
typedef EFI_STATUS (*EFI_TRUST) (
	IN EFI_HANDLE FirmwareVolumeHandle, IN EFI_GUID *FileName
);
typedef EFI_STATUS (*EFI_PROCESS_FIRMWARE_VOLUME) (
	IN VOID *FirmwareVolumeHeader, IN UINTN Size,
	OUT EFI_HANDLE *FirmwareVolumeHandle
);

typedef struct {
	EFI_TABLE_HEADER Hdr;
	// Global Coherency Domain Services
	EFI_ADD_MEMORY_SPACE AddMemorySpace;
	EFI_ALLOCATE_MEMORY_SPACE AllocateMemorySpace;
	EFI_FREE_MEMORY_SPACE FreeMemorySpace;
	EFI_REMOVE_MEMORY_SPACE RemoveMemorySpace;
	EFI_GET_MEMORY_SPACE_DESCRIPTOR GetMemorySpaceDescriptor;
	EFI_SET_MEMORY_SPACE_ATTRIBUTES SetMemorySpaceAttributes;
	EFI_GET_MEMORY_SPACE_MAP GetMemorySpaceMap;
	EFI_ADD_IO_SPACE AddIoSpace;
	EFI_ALLOCATE_IO_SPACE AllocateIoSpace;
	EFI_FREE_IO_SPACE FreeIoSpace;
	EFI_REMOVE_IO_SPACE RemoveIoSpace;
	EFI_GET_IO_SPACE_DESCRIPTOR GetIoSpaceDescriptor;
	EFI_GET_IO_SPACE_MAP GetIoSpaceMap;
	// Dispatcher Services
	EFI_DISPATCH Dispatch;
	EFI_SCHEDULE Schedule;
	EFI_TRUST Trust;
	// Service to process a single firmware volume found in a capsule
	EFI_PROCESS_FIRMWARE_VOLUME ProcessFirmwareVolume;
} DXE_SERVICES;
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
