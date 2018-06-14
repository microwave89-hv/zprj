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
// $Header: /Alaska/BIN/Core/Include/Protocol/PciPlatform.h 2     3/13/06 1:40a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/PciPlatform.h $
// 
// 2     3/13/06 1:40a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<This File Name>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __PCI_PLATFORM_PROTOCOL_H__
#define __PCI_PLATFORM_PROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif
/****** DO NOT WRITE ABOVE THIS LINE *******/

//**********************************************************************
#include <EFI.h>

// Protocol for GUID.
#define EFI_PCI_PLATFORM_PROTOCOL_GUID \
{ 0x7d75280, 0x27d4, 0x4d69, 0x90, 0xd0, 0x56, 0x43, 0xe2, 0x38, 0xb3, 0x41}

GUID_VARIABLE_DECLARATION(gEfiPciPlatformProtocolGuid,EFI_PCI_PLATFORM_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/PciHostBridgeResourceAllocation.h>

typedef struct _EFI_PCI_PLATFORM_PROTOCOL EFI_PCI_PLATFORM_PROTOCOL;

typedef UINT32 EFI_PCI_PLATFORM_POLICY;

//-------------------------------------------------
#define	EFI_RESERVE_NONE_IO_ALIAS        0x0000
#define	EFI_RESERVE_ISA_IO_ALIAS         0x0001
#define	EFI_RESERVE_ISA_IO_NO_ALIAS      0x0002
#define	EFI_RESERVE_VGA_IO_ALIAS         0x0004
#define	EFI_RESERVE_VGA_IO_NO_ALIAS      0x0008


typedef enum {
	ChipsetEntry,
	ChipsetExit,
	MaximumChipsetPhase
} EFI_PCI_CHIPSET_EXECUTION_PHASE;

//-------------------------------------------------
// Protocol Function Definitions
//-------------------------------------------------
typedef EFI_STATUS (EFIAPI * EFI_PCI_PLATFORM_PHASE_NOTIFY)(
	IN 	EFI_PCI_PLATFORM_PROTOCOL              			*This,
	IN  EFI_HANDLE                               		HostBridge,
	IN  EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE	Phase,
	IN  EFI_PCI_CHIPSET_EXECUTION_PHASE                 ChipsetPhase  
);

//-------------------------------------------------
typedef EFI_STATUS (EFIAPI * EFI_PCI_PLATFORM_PREPROCESS_CONTROLLER)(
  	IN 	EFI_PCI_PLATFORM_PROTOCOL              			*This,
  	IN  EFI_HANDLE                                     	HostBridge,
  	IN  EFI_HANDLE                                     	RootBridge,
  	IN  EFI_PCI_CONFIGURATION_ADDRESS					PciAddress,
  	IN  EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE	Phase,
  	IN  EFI_PCI_CHIPSET_EXECUTION_PHASE					ChipsetPhase
);

//-------------------------------------------------
typedef EFI_STATUS (EFIAPI * EFI_PCI_PLATFORM_GET_PLATFORM_POLICY)(
  	IN 	EFI_PCI_PLATFORM_PROTOCOL            			*This,
  	OUT EFI_PCI_PLATFORM_POLICY                       	*PciPolicy
);

//-------------------------------------------------
typedef EFI_STATUS (EFIAPI *EFI_PCI_PLATFORM_GET_PCI_ROM)(        
	IN 	EFI_PCI_PLATFORM_PROTOCOL						*This,
	IN 	EFI_HANDLE                     					PciHandle,
	OUT VOID											**RomImage,
	OUT UINTN											*RomSize              
);

//-------------------------------------------------
typedef struct _EFI_PCI_PLATFORM_PROTOCOL {
	EFI_PCI_PLATFORM_PHASE_NOTIFY          				PhaseNotify;
	EFI_PCI_PLATFORM_PREPROCESS_CONTROLLER 				PlatformPrepController;
	EFI_PCI_PLATFORM_GET_PLATFORM_POLICY   				GetPlatformPolicy;
	EFI_PCI_PLATFORM_GET_PCI_ROM           				GetPciRom;
} EFI_PCI_PLATFORM_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
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
