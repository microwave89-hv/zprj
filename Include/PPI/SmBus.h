//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/PPI/SmBus.h 7     6/16/11 3:18p Felixp $
//
// $Revision: 7 $
//
// $Date: 6/16/11 3:18p $
//*****************************************************************************
// Revision	History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/SmBus.h $
// 
// 7     6/16/11 3:18p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 6     5/27/11 5:52p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 5     1/16/09 9:49a Felixp
// SM Bus Protocol and PPI headers are updated. Common code moved into
// newly created header file (Include\SmBus.h).
// 
// 4     9/04/07 12:31p Felixp
// Added EFI_PEI_SMBUS2_PPI GUID and structures as defined in Platform
// Initialization Specification version 1.0.
// 
// 2     6/23/05 10:51a Robert
// Updated to reflect the new public spec from Intel
// 
// 1		 12/12/03	11:03a Robert
// Initial checkin of	the	SmBus	PPI	and	the	PPI	subcomponent
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	SmBus.h.c
//
// Description:	This file contains SmBus PPI definitions
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef	_SM_BUS_PPI_H
#define	_SM_BUS_PPI_H
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>
#include <SmBus.h>

//----------------------------------------------------------------------------
// Definition for EFI_PEI_SMBUS_PPI
//----------------------------------------------------------------------------
#define	EFI_PEI_SMBUS_PPI_GUID	\
	{0xabd42895, 0x78cf, 0x4872, 0x84, 0x44, 0x1b, 0x5c, 0x18, 0xb,	0xfb, 0xda}

GUID_VARIABLE_DECLARATION(gPeiSmbusPpiGuid,EFI_PEI_SMBUS_PPI_GUID);

typedef struct _EFI_PEI_SMBUS_PPI EFI_PEI_SMBUS_PPI;


//******************************************************* 
// EFI_SMBUS_NOTIFY_FUNCTION 
//*******************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_PEI_SMBUS_NOTIFY_FUNCTION) (
	IN EFI_PEI_SERVICES				**PeiServices,
	IN EFI_PEI_SMBUS_PPI 			*This,
	IN EFI_SMBUS_DEVICE_ADDRESS     SlaveAddress,
	IN UINTN                        Data
);
//******************************************************* 
// EFI_PEI_SMBUS_PPI_EXECUTE_OPERATION 
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PEI_SMBUS_PPI_EXECUTE_OPERATION) (
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_SMBUS_PPI *This,
	IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
	IN EFI_SMBUS_DEVICE_COMMAND Command,
	IN EFI_SMBUS_OPERATION Operation,
	IN BOOLEAN PecCheck,
	IN OUT UINTN *Length,
	IN OUT VOID *Buffer
	);
//******************************************************* 
// EFI_PEI_SMBUS_PPI_ARP_DEVICE
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PEI_SMBUS_PPI_ARP_DEVICE) (
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_SMBUS_PPI *This,
	IN BOOLEAN ArpAll,
	IN EFI_SMBUS_UDID *SmbusUdid, OPTIONAL
	IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
	);
//******************************************************* 
// EFI_PEI_SMBUS_PPI_GET_ARP_MAP
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PEI_SMBUS_PPI_GET_ARP_MAP) (
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_SMBUS_PPI *This,
	IN OUT UINTN *Length,
	IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
	);
//******************************************************* 
// EFI_PEI_SMBUS_PPI_NOTIFY
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PEI_SMBUS_PPI_NOTIFY) (
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_SMBUS_PPI *This,
	IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
	IN UINTN Data,
	IN EFI_PEI_SMBUS_NOTIFY_FUNCTION NotifyFunction
	);
//******************************************************* 
// EFI_PEI_SMBUS_PPI
//*******************************************************
typedef struct _EFI_PEI_SMBUS_PPI {
	EFI_PEI_SMBUS_PPI_EXECUTE_OPERATION Execute;
	EFI_PEI_SMBUS_PPI_ARP_DEVICE ArpDevice;
	EFI_PEI_SMBUS_PPI_GET_ARP_MAP GetArpMap;
	EFI_PEI_SMBUS_PPI_NOTIFY Notify;
} EFI_PEI_SMBUS_PPI;
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Definition for EFI_PEI_SMBUS2_PPI
//----------------------------------------------------------------------------
#if BACKWARD_COMPATIBLE_MODE
#include <Ppi/SmBus2.h>
#pragma warning ( disable : 4090 4028)
GUID_VARIABLE_DECLARATION(gPeiSmbus2PpiGuid,EFI_PEI_SMBUS2_PPI_GUID);
#endif

/******	DO NOT WRITE BELOW THIS	LINE *******/
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
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
