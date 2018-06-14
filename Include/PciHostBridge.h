//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
//**********************************************************************
// $Header: /Alaska/BIN/Core/Modules/PciBus/PciHostBridge.h 16    4/05/11 10:56a Yakovlevs $Revision:$
//
// $Date: 4/05/11 10:56a $
//**********************************************************************
// Revision History
// ----------------
//$Log: /Alaska/BIN/Core/Modules/PciBus/PciHostBridge.h $
// 
// 16    4/05/11 10:56a Yakovlevs
// selfreference removed.
// 
// 15    8/16/10 1:14p Yakovlevs
// Separated VGA attributes from Glaobal Compatibility attributes.
// 
// 14    3/01/10 5:59p Yakovlevs
// Multi-ROOT Generic Support Added.
// 
// 13    9/22/09 6:07p Yakovlevs
// 1.	Added definitions to support changes for EIP 23548 (Support MMIO
// allocation above 4GB).
// 
// 12    8/21/09 4:36p Yakovlevs
// Added ImageHandle field in HostBridge and RootBridge Structures.
// Added definitions for default PCI_MAX .. MIN Resource boubdaries.
// 
// 11    4/28/09 3:53p Yakovlevs
// Changes related to AmiBoardInfo protocol and Multiplatform support.
// 
// 10    3/27/09 12:35p Yakovlevs
// Added missing IO_16 attributes from UEFI 2.1 spec
// 
// 9     3/23/09 4:51p Yakovlevs
// Added generic support for PCI Express Hot-Plug.
//**********************************************************************
#ifndef _PCI_HOST_BRIDGE_H_
#define _PCI_HOST_BRIDGE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>
#if AMI_ROOT_BRIDGE_SUPPORT == 1

//**********************************************************************
//Includes goes here
#include <Efi.h>
#include <Dxe.h>
#include <Protocol\PciHostBridgeResourceAllocation.h>
#include <Protocol\PciHotPlugInit.h>
#include <Protocol\PciPlatform.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\DeviceIo.h>
#include <Protocol\AmiBoardInfo.h>
#include <AcpiRes.h>

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		EFI_PCI_CFG_ADDRESS
//
// Description:	Macro defining PCI Config Spase access UCING PCI Express Base
//
// Notes: 
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
#ifndef EFI_PCI_CFG_ADDRESS
#define	EFI_PCI_CFG_ADDRESS(bus,dev,func,reg)	\
 ((UINT64) ( (((UINTN)bus) << 24)+(((UINTN)dev)	<< 16) + (((UINTN)func)	<< 8) + ((UINTN)reg)))& 0x00000000ffffffff
#endif


//Defining ROOT BRIDGE Compatibility  Attributes group
#define PCI_ROOT_COMPATIBILITY_ATTRIBUTES 	(EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO |	EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO| \
	 EFI_PCI_ATTRIBUTE_ISA_IO | EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO | EFI_PCI_ATTRIBUTE_ISA_IO_16)

#define PCI_ROOT_VGA_ATTRIBUTES 	(EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO  | EFI_PCI_ATTRIBUTE_VGA_MEMORY | \
     EFI_PCI_ATTRIBUTE_VGA_IO | EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO_16 | EFI_PCI_ATTRIBUTE_VGA_IO_16)

#define MAX_PCI_BUSES   0xFF
#define MIN_PCI_IO      0x1000
#define MAX_PCI_IO      0xFFFF
#define MIN_PCI_MMIO32  0x100000    
#define MAX_PCI_MMIO32  0xFFFFFFFF
#define MIN_PCI_MMIO64  0x100000000    
#define MAX_PCI_MMIO64  0xFFFFFFFFFFFFFFFF


//**********************************************************************
//Private Data Definitions
//**********************************************************************

//forward declaration
typedef struct _PCI_HOST_BRG_DATA PCI_HOST_BRG_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_ROOT_BRIDGE_MAPPING
//
// Description:	Structure used to specify RootBridge Specific Mapping 
// Information for DMA transfere.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	Operation	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION	PciRoot Bridge IO Operation Description. 
//	NumBytes	UINTN		Number Of Bytes in Mapping Buffer.
//	HostAddr	EFI_PHYSICAL_ADDRESS	Buffer Address of the device who initiated BM transfere.
//	DeviceAddr	EFI_PHYSICAL_ADDRESS	Buffer Address of the device who receives BM transfere.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_ROOT_BRIDGE_MAPPING {
  	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION	Operation;
  	UINTN                                      	NumPages;
  	EFI_PHYSICAL_ADDRESS                       	HostAddr;
  	EFI_PHYSICAL_ADDRESS                       	DeviceAddr;
}	PCI_ROOT_BRIDGE_MAPPING;


typedef enum {
    raBus=0,
    raIo,
    raMmio32,
    raMmio64,
    raMaxRes
} ACPI_RES_TYPE;


typedef struct _ACPI_RES_DATA{
    UINT64                  Min;
    UINT64                  Len;
    UINT64                  Max;
    UINT64                  Gra;
    UINT64                  AddrUsed;
    EFI_GCD_ALLOCATE_TYPE   AllocType;
} ACPI_RES_DATA;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_ROOT_BRG_DATA
//
// Description:	Private RootBridge Data Structure
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	RbIoProtocol	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	This PCI Root Bridge IO Protocol Instance. 
//  RbHandle		EFI_HANDLE					This PCI Root Bridge EFI_HANDLE.
//	DevPath			*EFI_DEVICE_PATH_PROTOCOL	This PCI Root Bridge Device Path Protocol instance.
//	Owner			*PCI_HOST_BRG_DATA			Pointer on the Host Bridge Private Data Structure who owns this Root Bridge.
//	DevIoProtocol	*EFI_DEVICE_IO_INTERFACE	This PCI Root Bridge Device IO Protocol instance.
//	Supports		UINT64						Set of Attirbutes Supported by this PCI Root Bridge.
//	Attributes		UINT64						Set of currently supported Attirbutes by this PCI Root Bridge.
//	ResInitCnt		UINTN						To make this and following 2 fields look like T_ITEM_LIST type.
//  ResCount		UINTN						Number of ACPI QWord Resource descriptors of this PCI Root Bridge.
//	RbRes			**ASLR_QWORD_ASD			Pointer to the array of pointers at the resource descriptors of this PCI Root Bridge. 
//	Mapping			*PCI_ROOT_BRIDGE_MAPPING	When Mapping is set this pointer points on Private RB Mapping Structure.
//	BusesSet		BOOLEAN						Flag to indicate that Bus Allocation Phase is over.
//	ResSubmited 	BOOLEAN						Flag to indicate that Resources were submited by the PciBus Driver.
//	ResAsquired		BOOLEAN						Flag to indicate that Resource request was sutisfied by the GCD.
//	Reserved		UINT8						Reserved field to make this structure end at 4 byte alignment.
//  BusXlatEntry    *PCI_BUS_XLAT_HDR           Pointer at AMI SDL Generated Bus Translate table corresponded to THIS Root Bridge. 
//  RbAslName       *CHAR8                      Pointer to the String of THIS Root Bridge Device in ACPI Name Space.
//  AcpiRbRes[]     ACPI_RES_DATA               Array holding THIS Root Bridge Resource Information for ACPI 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_ROOT_BRG_DATA {
	EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL		RbIoProtocol;
	EFI_HANDLE							RbHandle;
	EFI_HANDLE                          ImageHandle;
	EFI_DEVICE_PATH_PROTOCOL			*DevPath;
	PCI_HOST_BRG_DATA					*Owner;
	EFI_DEVICE_IO_INTERFACE				*DevIoProtocol;
	UINT64								Supports;
	UINT64								Attributes;
	//make it as T_ITEM_LIST type
	UINTN								ResInitCnt;
	UINTN								ResCount;
	ASLR_QWORD_ASD						**RbRes;
	PCI_ROOT_BRIDGE_MAPPING				*Mapping;
	BOOLEAN								BusesSet;
	BOOLEAN								ResSubmited;
	BOOLEAN								ResAsquired;
	BOOLEAN								NotPresent;
    PCI_BUS_XLAT_HDR                    *BusXlatEntry;
    CHAR8                               *RbAslName;
    ACPI_RES_DATA                      	AcpiRbRes[raMaxRes];//BUS; IO; MMIO32; MMIO64; 
} PCI_ROOT_BRG_DATA;

typedef enum  {
    ptBus=0,    //0
    ptIo,       //1
    ptMmio32,   //2
    ptMmio32pf, //3
    ptMmio64,   //4
    ptMmio64pf,  //5
    ptMaxType
} HP_PADD_RES_TYPE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		HPC_LOCATION_DATA
//
// Description:	Private HostBridge Data Structure. It holds all information 
// related to HPC and HPB Location in the System.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	HpcLocation     EFI_HPC_LOCATION        HPC Location Information in terms of Device Path.
//	Owner           *PCI_HOST_BRG_DATA      Back Pointer to Locate this Data structure Owner.
//  SlotHdr		    PCI_BUS_XLAT_HDR		AMI SDL Generated SLOT Bus Xlat Information (AmiBoardInfoProtocol).
//	Padding[]		UINTN64					Array, holding Padding Information for particular Resource type.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _HPC_LOCATION_DATA {
    EFI_HPC_LOCATION    HpcLocation;
    PCI_ROOT_BRG_DATA   *Owner;
    PCI_BUS_XLAT_HDR    *SlotHdr;
    UINT64              Padding[ptMaxType];
} HPC_LOCATION_DATA;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_HPC_DATA
//
// Description:	Private HostBridge Data Structure. It holds all Hot Plug 
// related Information. Used to Produce EFI_PCI_HOT_PLUG_INIT_PROTOCOL.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	RootHotplugProtocol EFI_PCI_HOT_PLUG_INIT_PROTOCOL	This PCI Root Hot Plug Controller Initialization Protocol Instance.
//  HbHandle		EFI_HANDLE					This PCI Host Bridge EFI_HANDLE.
//	HpclInitCnt		UINTN						To make this and following 2 fields look like T_ITEM_LIST type.
//	HpcLocCount     UINTN						Number of Root Bridges Hot Plug Location Data Structures Associated with THIS HOST.
//	HpcLocData		**HPC_LOCATION_DATA			Pointer to the array of pointers at the private PCI Hot Plug Controller Location Data. 
//	Owner           *PCI_HOST_BRG_DATA	        Back Pointer to Locate this Data structure Owner.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_HPC_DATA {
    //The Protocol coming first...
    EFI_PCI_HOT_PLUG_INIT_PROTOCOL  RootHotplugProtocol;
    //HPC Location data... to make it look like T_ITEM_LIST
    UINTN               HpclInitCnt;
    UINTN               HpcLocCount;
    HPC_LOCATION_DATA   **HpcLocData;
    PCI_HOST_BRG_DATA   *Owner;
} PCI_HPC_DATA;



//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:		PCI_HOST_BRG_DATA
//
// Description:	Private HostBridge Data Structure. This is the Starting 
//              point for PCI Subsystem.
//
// Fields:		
//	Name			Type					Description
//   ------------------------------------------------------------------
//	ResAllocProtocol EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL	This PCI Host Bridge Resource Allocation Protocol Instance.
//  HbHandle		EFI_HANDLE					This PCI Host Bridge EFI_HANDLE.
//	RbInitCnt		UINTN						To make this and following 2 fields look like T_ITEM_LIST type.
//	RootBridgeCount UINTN						Number of PCI_ROOT_BRG_DATA structures (Root Bridges) this host will group.
//	RootBridges		**PCI_ROOT_BRG_DATA			Pointer to the array of pointers at the private PCI Root Bridge Data Structure. 
//	AllocPhase		EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE	Current Phase of PCI Bus Enumeration.
//	AllocAttrib		UINT64						This PCI Host Bridge Allocation Attributes.
//	EnumStarted		BOOLEAN						Flag to indicate that PCI Bus Enumeration has started.
//	Reserved[3]		UINT8						Reserved fields to make this structure end at 4 byte alignment.
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _PCI_HOST_BRG_DATA {
	EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL	ResAllocProtocol;
	EFI_HANDLE											HbHandle;
	EFI_HANDLE											ImageHandle;
	//make it as T_ITEM_LIST type
	UINTN												RbInitCnt;
	UINTN												RootBridgeCount;
	PCI_ROOT_BRG_DATA									**RootBridges;
	//----------------------------
	EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE		AllocPhase;
	UINT64												AllocAttrib;
	BOOLEAN												EnumStarted;
	UINT8												Reserved[3];
    //Optional Protocols - one instance per HOST
    PCI_HPC_DATA                                        *HpcData;
//    EFI_PCI_PLATFORM_PROTOCOL                           *PlatformProtocol;
}PCI_HOST_BRG_DATA;

//**********************************************************************//
//Global Variables
//extern UINTN			gRbCountTbl[];
//extern ASLR_QWORD_ASD	*gRbBusesTbl;
//extern UINT64			gRbSupportsTbl[];
//extern UINT64			gHbAllocAttribTbl[];
//**********************************************************************//
//Some Helper Functions
EFI_STATUS GetResources(PCI_ROOT_BRG_DATA *RootBrg, ASLR_QWORD_ASD **Resources, ASLR_TYPE_ENUM ResType);

//-----------------------------------------------------------------------
//Function Prototypes for PciRootBridgeIo
//-----------------------------------------------------------------------
EFI_STATUS PollMem (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN  UINT64			Address,
	IN  UINT64			Mask,
	IN  UINT64			Value,
	IN  UINT64			Delay,
	OUT UINT64			*Result);

EFI_STATUS PollIo (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN  UINT64			Address,
	IN  UINT64			Mask,
	IN  UINT64			Value,
	IN  UINT64			Delay,
	OUT UINT64			*Result);

EFI_STATUS PciMemRead (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN     UINT64		Address,
	IN     UINTN		Count,
	IN OUT VOID			*Buffer);

EFI_STATUS PciMemWrite (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN     UINT64		Address,
	IN     UINTN		Count,
	IN OUT VOID			*Buffer);

EFI_STATUS PciIoRead (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN     UINT64		UserAddress,
	IN     UINTN		Count,
	IN OUT VOID			*UserBuffer);

EFI_STATUS PciIoWrite (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN     UINT64		UserAddress,
	IN     UINTN		Count,
	IN OUT VOID			*UserBuffer);

EFI_STATUS CopyMem (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL			*This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH	Width,
	IN     UINT64		DestAddress,
	IN     UINT64		SrcAddress,
	IN     UINTN		Count);

EFI_STATUS PciRead (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL        *This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH  Width,
	IN     UINT64		Address,
	IN     UINTN		Count,
	IN OUT VOID			*Buffer);

EFI_STATUS PciWrite (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL        *This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH  Width,
	IN     UINT64		Address,
	IN     UINTN		Count,
	IN OUT VOID			*Buffer);

EFI_STATUS Map (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL            *This,
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION  Operation,
	IN     VOID					*HostAddress,
	IN OUT UINTN				*NumberOfBytes,
	OUT    EFI_PHYSICAL_ADDRESS	*DeviceAddress,
	OUT    VOID					**Mapping);

EFI_STATUS Unmap (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	IN  VOID			*Mapping);

EFI_STATUS AllocateBuffer (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	IN  EFI_ALLOCATE_TYPE	Type,
	IN  EFI_MEMORY_TYPE		MemoryType,
	IN  UINTN				Pages,
	OUT VOID				**HostAddress,
	IN  UINT64				Attributes);

EFI_STATUS FreeBuffer (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	IN  UINTN			Pages,
	OUT VOID			*HostAddress);

EFI_STATUS Flush (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This);

EFI_STATUS GetAttributes (
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	OUT UINT64			*Supported,
	OUT UINT64			*Attributes);

EFI_STATUS SetAttributes (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	IN     UINT64		Attributes,
	IN OUT UINT64		*ResourceBase,
	IN OUT UINT64		*ResourceLength);

EFI_STATUS Configuration (
	IN     EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
	OUT    VOID			**Resources);

EFI_DEVICE_IO_INTERFACE * ConstructDeviceIoProtocol(
	IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*RootBridgeIo,
	IN EFI_DEVICE_PATH_PROTOCOL *Path);


/****** DO NOT WRITE BELOW THIS LINE *******/
#endif 

#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
