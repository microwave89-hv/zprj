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
// $Header: /Alaska/BIN/Core/Include/HOB.h 8     6/16/11 2:54p Felixp $
//
// $Revision: 8 $
//
// $Date: 6/16/11 2:54p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/HOB.h $
// 
// 8     6/16/11 2:54p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 7     6/16/11 9:25a Felixp
// Backward compatible definitions of the capsule HOB are added.
// 
// 6     4/13/11 6:38p Artems
// EIP 56529: Replaced old Capsule HOB definitions with new one as per PI
// spec v.1.2
// 
// 5     2/05/11 1:49p Artems
// Added FirmwareVolumeHob2 type
// 
// 4     4/26/10 9:55a Felixp
// Clean up
// 
// 3     5/22/09 1:35p Felixp
// Clean up
// 
// 2     5/19/06 10:18p Felixp
// EFI_HOB_POINTERS renamed to EFI_PEI_HOB_POINTERS
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 4     3/19/04 11:04a Markw
// Removed ; at end of define.
// 
// 3     1/06/04 5:01p Yakovlevs
// 
// 2     12/17/03 11:05a Markw
// Added includes
// 
// 1     12/16/03 10:41a Markw
// Move HOB.h to include directory.
// 
// 1     12/12/03 3:40p Markw
// Hob definitions
// 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    HOB.H
//
// Description:    
// EFI Header file. It has standard definitions defined by the 
// EFI Specification Version 1.10 12/01/02
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HOB__H__
#define __HOB__H__

#include "efi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NextHob(Hob,Type) ((Type *) ((UINT8 *) Hob + ((EFI_HOB_GENERIC_HEADER *)Hob)->HobLength))

//******************************************************
// HobType values
//******************************************************
#define EFI_HOB_TYPE_HANDOFF                0x0001
#define EFI_HOB_TYPE_MEMORY_ALLOCATION      0x0002
#define EFI_HOB_TYPE_RESOURCE_DESCRIPTOR    0x0003
#define EFI_HOB_TYPE_GUID_EXTENSION         0x0004
#define EFI_HOB_TYPE_FV                     0x0005
#define EFI_HOB_TYPE_CPU                    0x0006
#define EFI_HOB_TYPE_MEMORY_POOL            0x0007
#define EFI_HOB_TYPE_FV2                    0x0009
#define EFI_HOB_TYPE_LOAD_PEIM_UNUSED       0x000A
#define EFI_HOB_TYPE_UEFI_CAPSULE           0x000B
#define EFI_HOB_TYPE_UNUSED                 0xFFFE
#define EFI_HOB_TYPE_END_OF_HOB_LIST        0xFFFF
    
    

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_GENERIC_HEADER
//
// Description: This is a generic header for all HOBs.
//
// Fields:     Name        Type        Description
//        ------------------------------------------------------------
//        HobType        UINT16    Type of Hob
//        HobLength      UINT16    Length of HOB
//        Reserved       UINT32
//
//**********************************************************************
    

typedef struct _EFI_HOB_GENERIC_HEADER{
    UINT16    HobType;
    UINT16    HobLength;
    UINT32    Reserved;
} EFI_HOB_GENERIC_HEADER;




//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_HANDOFF_INFO_TABLE
//
// Description: This is a generic header for all HOBs.
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header               EFI_HOB_GENERIC_HEADER
//        Version              UINT32
//        BootMode             EFI_BOOT_MODE
//        EfiMemoryTop         EFI_PHYSICAL_ADDRESS
//        EfiMemoryBottom      EFI_PHYSICAL_ADDRESS
//        EfiFreeMemoryTop     EFI_PHYSICAL_ADDRESS
//        EfiFreeMemoryBottom  EFI_PHYSICAL_ADDRESS
//        EfiEndOfHobList      EFI_PHYSICAL_ADDRESS
//
//**********************************************************************
typedef struct _EFI_HOB_HANDOFF_INFO_TABLE {
    EFI_HOB_GENERIC_HEADER  Header;
    UINT32                  Version;
    EFI_BOOT_MODE           BootMode;
    EFI_PHYSICAL_ADDRESS    EfiMemoryTop;
    EFI_PHYSICAL_ADDRESS    EfiMemoryBottom;
    EFI_PHYSICAL_ADDRESS    EfiFreeMemoryTop;
    EFI_PHYSICAL_ADDRESS    EfiFreeMemoryBottom;
    EFI_PHYSICAL_ADDRESS    EfiEndOfHobList;
} EFI_HOB_HANDOFF_INFO_TABLE;

// Version values
#define EFI_HOB_HANDOFF_TABLE_VERSION        0x0009


//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_MEMORY_ALLOCATION_HEADER
//
// Description: Memory Description used by EFI_HOB_MEMORY_ALLOCATION HOB.
//              This stores the purpose (as a GUID), the location,
//              and type as used by the EFI 1.1 allocate pages.
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Name                EFI_GUID                    Purpose
//        MemoryBaseAddress   EFI_PHYSICAL_ADDRESS        Start
//        MemoryLength        UINT64                      Length
//        MemoryType          EFI_MEMORY_TYPE             Type used by allocate pages.
//        Reserved[4]         UINT8
//
//**********************************************************************
typedef struct _EFI_HOB_MEMORY_ALLOCATION_HEADER {
    EFI_GUID                Name;
    EFI_PHYSICAL_ADDRESS    MemoryBaseAddress;
    UINT64                  MemoryLength;
    EFI_MEMORY_TYPE         MemoryType;         // UINT32
    UINT8                   Reserved[4];        // Padding for Itanium
                                                // processor family
} EFI_HOB_MEMORY_ALLOCATION_HEADER;


//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_MEMORY_ALLOCATION
//
// Description: Describes memory not used by the HOB list.
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header               EFI_HOB_GENERIC_HEADER
//        AllocDescriptor      EFI_HOB_MEMORY_ALLOCATION_HEADER  - Memory desciption
//        Additional fields pertaining to the Name Guid.
//
//**********************************************************************
typedef struct _EFI_HOB_MEMORY_ALLOCATION {
    EFI_HOB_GENERIC_HEADER Header;
    EFI_HOB_MEMORY_ALLOCATION_HEADER AllocDescriptor;
    //
    // Additional data pertaining to the Name Guid.
    //
} EFI_HOB_MEMORY_ALLOCATION;


//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_MEMORY_ALLOCATION_STACK
//
// Description: Descibes PEI BSP Physical Memory Stack.
//              Same structure as EFI_HOB_MEMORY_ALLOCATION,
//              except AllocDescriptor has a specific Name of
//              EFI_HOB_MEMORY_ALLOC_STACK_GUID.
//              
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header               EFI_HOB_GENERIC_HEADER
//        AllocDescriptor      EFI_HOB_MEMORY_ALLOCATION_HEADER  - Memory desciption
//
//**********************************************************************
typedef struct _EFI_HOB_MEMORY_ALLOCATION_STACK {
    EFI_HOB_GENERIC_HEADER              Header;
    EFI_HOB_MEMORY_ALLOCATION_HEADER    AllocDescriptor;
} EFI_HOB_MEMORY_ALLOCATION_STACK;

#define EFI_HOB_MEMORY_ALLOC_STACK_GUID \
    {0x4ed4bf27, 0x4092, 0x42e9, 0x80, 0x7d, 0x52, 0x7b, 0x1d, 0x0,0xc9, 0xbd};


//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_MEMORY_ALLOCATION_BSP_STORE
//
// Description: Descibes PEI BSP Physical Memory Store.
//              This for the Itanium CPU only.
//              Same structure as EFI_HOB_MEMORY_ALLOCATION,
//              except AllocDescriptor has a specific Name of
//              EFI_HOB_MEMORY_ALLOC_BSP_STORE_GUID.
//              
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header              EFI_HOB_GENERIC_HEADER
//        AllocDescriptor     EFI_HOB_MEMORY_ALLOCATION_HEADER  - Memory desciption
//
//**********************************************************************
typedef struct _EFI_HOB_MEMORY_ALLOCATION_BSP_STORE {
    EFI_HOB_GENERIC_HEADER              Header;
    EFI_HOB_MEMORY_ALLOCATION_HEADER    AllocDescriptor;
} EFI_HOB_MEMORY_ALLOCATION_BSP_STORE;

#define EFI_HOB_MEMORY_ALLOC_BSP_STORE_GUID \
    {0x564b33cd, 0xc92a, 0x4593, 0x90, 0xbf, 0x24, 0x73, 0xe4, 0x3c,0x63, 0x22};


//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_MEMORY_ALLOCATION
//
// Description: 
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header              EFI_HOB_GENERIC_HEADER
//        AllocDescriptor     EFI_HOB_MEMORY_ALLOCATION_HEADER  - Memory desciption
//        ModuleName          EFI_GUID
//        EntryPoint          EFI_PHYSICAL_ADDRESS
//
//**********************************************************************
typedef struct {
    EFI_HOB_GENERIC_HEADER              Header;
    EFI_HOB_MEMORY_ALLOCATION_HEADER    MemoryAllocationHeader;
    EFI_GUID                            ModuleName;
    EFI_PHYSICAL_ADDRESS                EntryPoint;
} EFI_HOB_MEMORY_ALLOCATION_MODULE;

#define EFI_HOB_MEMORY_ALLOC_MODULE_GUID \
    {0xf8e21975, 0x899, 0x4f58, 0xa4, 0xbe, 0x55, 0x25, 0xa9, 0xc6,0xd7, 0x7a}

//*********************************************************
// EFI_RESOURCE_TYPE
//*********************************************************
typedef UINT32 EFI_RESOURCE_TYPE;
#define EFI_RESOURCE_SYSTEM_MEMORY          0x00000000
#define EFI_RESOURCE_MEMORY_MAPPED_IO       0x00000001
#define EFI_RESOURCE_IO                     0x00000002
#define EFI_RESOURCE_FIRMWARE_DEVICE        0x00000003
#define EFI_RESOURCE_MEMORY_MAPPED_IO_PORT  0x00000004
#define EFI_RESOURCE_MEMORY_RESERVED        0x00000005
#define EFI_RESOURCE_IO_RESERVED            0x00000006
#define EFI_RESOURCE_MAX_MEMORY_TYPE        0x00000007

//*******************************************************
// EFI_RESOURCE_ATTRIBUTE_TYPE
//*******************************************************
typedef UINT32 EFI_RESOURCE_ATTRIBUTE_TYPE;
// These types can be ORed together as needed.
//
// The first three enumerations describe settings
//
#define EFI_RESOURCE_ATTRIBUTE_PRESENT      0x00000001
#define EFI_RESOURCE_ATTRIBUTE_INITIALIZED  0x00000002
#define EFI_RESOURCE_ATTRIBUTE_TESTED       0x00000004
//
// The rest of the settings describe capabilities
//
#define EFI_RESOURCE_ATTRIBUTE_SINGLE_BIT_ECC           0x00000008
#define EFI_RESOURCE_ATTRIBUTE_MULTIPLE_BIT_ECC         0x00000010
#define EFI_RESOURCE_ATTRIBUTE_ECC_RESERVED_1           0x00000020
#define EFI_RESOURCE_ATTRIBUTE_ECC_RESERVED_2           0x00000040
#define EFI_RESOURCE_ATTRIBUTE_READ_PROTECTED           0x00000080
#define EFI_RESOURCE_ATTRIBUTE_WRITE_PROTECTED          0x00000100
#define EFI_RESOURCE_ATTRIBUTE_EXECUTION_PROTECTED      0x00000200
#define EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE              0x00000400
#define EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE        0x00000800
#define EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE  0x00001000
#define EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE     0x00002000
#define EFI_RESOURCE_ATTRIBUTE_16_BIT_IO                0x00004000
#define EFI_RESOURCE_ATTRIBUTE_32_BIT_IO                0x00008000
#define EFI_RESOURCE_ATTRIBUTE_64_BIT_IO                0x00010000
#define EFI_RESOURCE_ATTRIBUTE_UNCACHED_EXPORTED        0x00020000


//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_RESOURCE_DESCRIPTOR
//
// Description: Used to describe system memory map including system memory,
//              MMIO, IO, and Firmware Device.
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header              EFI_HOB_GENERIC_HEADER
//        Owner               EFI_GUID
//        ResourceType        EFI_RESOURCE_TYPE
//        ResourceAttribute   EFI_RESOURCE_ATTRIBUTE_TYPE
//        PhysicalStart       EFI_PHYSICAL_ADDRESS
//        ResourceLength      UINT64
//
//**********************************************************************
typedef struct _EFI_HOB_RESOURCE_DESCRIPTOR {
    EFI_HOB_GENERIC_HEADER          Header;
    EFI_GUID                        Owner;
    EFI_RESOURCE_TYPE               ResourceType;
    EFI_RESOURCE_ATTRIBUTE_TYPE     ResourceAttribute;
    EFI_PHYSICAL_ADDRESS            PhysicalStart;
    UINT64                          ResourceLength;
} EFI_HOB_RESOURCE_DESCRIPTOR;

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_GUID_TYPE
//
// Description: Implementation specific data here.
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header              EFI_HOB_GENERIC_HEADER
//        Name                EFI_GUID
//        Guid specific data here.
//
//**********************************************************************
typedef struct _EFI_HOB_GUID_TYPE {
    EFI_HOB_GENERIC_HEADER  Header;
    EFI_GUID                Name;
    //
    // Guid specific data goes here
    //
} EFI_HOB_GUID_TYPE;

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_FIRMWARE_VOLUME
//
// Description: Describes Base and Length of a Firmware Volume
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header              EFI_HOB_GENERIC_HEADER
//        BaseAddress         EFI_PHYSICAL_ADDRESS
//        Length              UINT64
//
//**********************************************************************
typedef struct {
    EFI_HOB_GENERIC_HEADER  Header;
    EFI_PHYSICAL_ADDRESS    BaseAddress;
    UINT64                  Length;
} EFI_HOB_FIRMWARE_VOLUME;

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_FIRMWARE_VOLUME2
//
// Description: Describes a Firmware Volume.
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header              EFI_HOB_GENERIC_HEADER        
//        BaseAddress         EFI_PHYSICAL_ADDRESS          Base Address of Firmware Volume
//        Length              UINT64                        Length of the Firmware Volume
//        FvName              EFI_GUID                      Guid of the Firmware Volume
//        FileName            EFI_GUID                      Guid of the FFS which contained the Firmware Volume
//**********************************************************************
typedef struct _EFI_HOB_FIRMWARE_VOLUME2{
    EFI_HOB_GENERIC_HEADER  Header;
    EFI_PHYSICAL_ADDRESS    BaseAddress;
    UINT64                  Length;
    EFI_GUID                FvName;
    EFI_GUID                FileName;
} EFI_HOB_FIRMWARE_VOLUME2;

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_CPU
//
// Description: Describes the maximum physical addressablity of Memory
//              and IO of the processor.
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header              EFI_HOB_GENERIC_HEADER
//        SizeOfMemorySpace   UINT8
//        SizeOfIoSpace       UINT8
//        Reserved[6]         UINT8
//
//**********************************************************************
typedef struct _EFI_HOB_CPU {
    EFI_HOB_GENERIC_HEADER  Header;
    UINT8                   SizeOfMemorySpace;
    UINT8                   SizeOfIoSpace;
    UINT8                   Reserved[6];
} EFI_HOB_CPU;

//Unkown usuage
typedef struct _EFI_HOB_MEMORY_POOL {
    EFI_HOB_GENERIC_HEADER    Header;
} EFI_HOB_MEMORY_POOL;

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_HOB_UEFI_CAPSULE
//
// Description: Describes Capsule Volume Base and Length
//
// Fields:     Name            Type                        Description
//        ------------------------------------------------------------
//        Header            EFI_HOB_GENERIC_HEADER
//        BaseAddress       EFI_PHYSICAL_ADDRESS
//        Length            UINT64
//
//**********************************************************************
typedef struct {
    EFI_HOB_GENERIC_HEADER  Header;
    EFI_PHYSICAL_ADDRESS    BaseAddress;
    UINT64                  Length;
} EFI_HOB_UEFI_CAPSULE;

#if BACKWARD_COMPATIBLE_MODE
#define EFI_HOB_TYPE_CV EFI_HOB_TYPE_UEFI_CAPSULE
typedef EFI_HOB_UEFI_CAPSULE EFI_HOB_CAPSULE_VOLUME;
#endif // BACKWARD_COMPATIBLE_MODE

//**********************************************************************
//<AMI_SHDR_START>
//
// Name:        EFI_PEI_HOB_POINTERS
//
// Description:  Union of all the possible HOB Types
//
//**********************************************************************
typedef union {
	EFI_HOB_GENERIC_HEADER              *Header;
	EFI_HOB_HANDOFF_INFO_TABLE          *HandoffInformationTable;
	EFI_HOB_MEMORY_ALLOCATION           *MemoryAllocation;
	EFI_HOB_MEMORY_ALLOCATION_BSP_STORE *MemoryAllocationBspStore;
	EFI_HOB_MEMORY_ALLOCATION_STACK     *MemoryAllocationStack;
	EFI_HOB_MEMORY_ALLOCATION_MODULE    *MemoryAllocationModule;
	EFI_HOB_RESOURCE_DESCRIPTOR         *ResourceDescriptor;
	EFI_HOB_GUID_TYPE                   *Guid;
	EFI_HOB_FIRMWARE_VOLUME             *FirmwareVolume;
    EFI_HOB_FIRMWARE_VOLUME2            *FirmwareVolume2;
	EFI_HOB_CPU                         *Cpu;
	EFI_HOB_MEMORY_POOL                 *Pool;
	EFI_HOB_UEFI_CAPSULE                *CapsuleVolume;
	UINT8                               *Raw;
} EFI_PEI_HOB_POINTERS;
/****** DO NOT WRITE BELOW THIS LINE *******/

#ifdef __cplusplus
}
#endif
#endif
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