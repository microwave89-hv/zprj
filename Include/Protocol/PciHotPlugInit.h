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
// $Header: /Alaska/BIN/Core/Include/Protocol/PciHotPlugInit.h 2     3/13/06 1:40a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/PciHotPlugInit.h $
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
#ifndef __PCI_HOT_PLUG_INIT_PROTOCOL_H__
#define __PCI_HOT_PLUG_INIT_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
/****** DO NOT WRITE ABOVE THIS LINE *******/
#include <EFI.h>

//**********************************************************************
#define EFI_PCI_HOT_PLUG_INIT_PROTOCOL_GUID \
  { 0xaa0e8bc1, 0xdabc, 0x46b0, 0xa8, 0x44, 0x37, 0xb8, 0x16, 0x9b, 0x2b, 0xea }

GUID_VARIABLE_DECLARATION(gEfiPciHotPlugInitProtocolGuid,EFI_PCI_HOT_PLUG_INIT_PROTOCOL_GUID);
  
typedef struct _EFI_PCI_HOT_PLUG_INIT_PROTOCOL EFI_PCI_HOT_PLUG_INIT_PROTOCOL;

#define  EFI_HPC_STATE_INITIALIZED    0x01
#define  EFI_HPC_STATE_ENABLED        0x02

typedef UINT16 EFI_HPC_STATE;

typedef struct{
  	EFI_DEVICE_PATH_PROTOCOL  	*HpcDevicePath;
	EFI_DEVICE_PATH_PROTOCOL  	*HpbDevicePath;
} EFI_HPC_LOCATION;


typedef enum{
	EfiPaddingPciBus,
  	EfiPaddingPciRootBridge
}EFI_HPC_PADDING_ATTRIBUTES;

typedef EFI_STATUS (EFIAPI *EFI_GET_ROOT_HPC_LIST)(
	IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL    	*This,
	OUT UINTN                            	*HpcCount,
	OUT EFI_HPC_LOCATION                	**HpcList
); 

typedef EFI_STATUS (EFIAPI *EFI_INITIALIZE_ROOT_HPC)(
	IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL     	*This,
	IN  EFI_DEVICE_PATH_PROTOCOL          	*HpcDevicePath,
  	IN  UINT64                          	HpcPciAddress,
  	IN  EFI_EVENT                         	Event, OPTIONAL
  	OUT EFI_HPC_STATE                    	*HpcState
); 

typedef EFI_STATUS (EFIAPI *EFI_GET_PCI_HOT_PLUG_PADDING)(
  	IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL       *This,
  	IN  EFI_DEVICE_PATH_PROTOCOL          	*HpcDevicePath,
  	IN  UINT64                            	HpcPciAddress,
  	OUT EFI_HPC_STATE                    	*HpcState,
  	OUT VOID                              	**Padding,
  	OUT EFI_HPC_PADDING_ATTRIBUTES       	*Attributes
); 


// Prototypes for the PCI Hot Plug Init Protocol
typedef struct _EFI_PCI_HOT_PLUG_INIT_PROTOCOL {
  	EFI_GET_ROOT_HPC_LIST                   GetRootHpcList;
  	EFI_INITIALIZE_ROOT_HPC                 InitializeRootHpc;
  	EFI_GET_PCI_HOT_PLUG_PADDING			GetResourcePadding;
} EFI_PCI_HOT_PLUG_INIT_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
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
