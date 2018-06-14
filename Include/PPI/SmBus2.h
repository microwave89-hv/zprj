//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/PPI/SmBus2.h 1     5/27/11 5:50p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/27/11 5:50p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/SmBus2.h $
// 
// 1     5/27/11 5:50p Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  SmBus2.h
//
// Description:	SmBus2 PPI definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SMBUS2_PPI__H__
#define __SMBUS2_PPI__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <PEI.h>
#include <SmBus.h>

#define	EFI_PEI_SMBUS2_PPI_GUID	\
	{0x9ca93627, 0xb65b, 0x4324, 0xa2, 0x2, 0xc0, 0xb4, 0x61, 0x76,	0x45, 0x43}

GUID_VARIABLE_DECLARATION(gEfiPeiSmbus2PpiGuid, EFI_PEI_SMBUS2_PPI_GUID);

typedef struct _EFI_PEI_SMBUS2_PPI EFI_PEI_SMBUS2_PPI;

//******************************************************* 
// EFI_PEI_SMBUS2_PPI_EXECUTE_OPERATION 
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PEI_SMBUS2_PPI_EXECUTE_OPERATION) (
	IN CONST EFI_PEI_SMBUS2_PPI     *This,
	IN EFI_SMBUS_DEVICE_ADDRESS     SlaveAddress,
	IN EFI_SMBUS_DEVICE_COMMAND     Command,
	IN EFI_SMBUS_OPERATION          Operation,
	IN BOOLEAN                      PecCheck,
	IN OUT UINTN                    *Length,
	IN OUT VOID                     *Buffer
	);


//******************************************************* 
// EFI_PEI_SMBUS2_PPI_ARP_DEVICE
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PEI_SMBUS2_PPI_ARP_DEVICE) (
	IN CONST EFI_PEI_SMBUS2_PPI           *This,
	IN BOOLEAN                      ArpAll,
	IN EFI_SMBUS_UDID               *SmbusUdid, OPTIONAL
	IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
	);

//******************************************************* 
// EFI_PEI_SMBUS2_PPI_GET_ARP_MAP
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PEI_SMBUS2_PPI_GET_ARP_MAP) (
	IN CONST EFI_PEI_SMBUS2_PPI *This,
	IN OUT UINTN                *Length,
	IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
	);

//******************************************************* 
// EFI_SMBUS_NOTIFY2_FUNCTION 
//*******************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_PEI_SMBUS_NOTIFY2_FUNCTION) (
	IN CONST EFI_PEI_SMBUS2_PPI      *This,
	IN EFI_SMBUS_DEVICE_ADDRESS     SlaveAddress,
	IN UINTN                        Data
);

//******************************************************* 
// EFI_PEI_SMBUS_PPI_NOTIFY
//*******************************************************
typedef EFI_STATUS (EFIAPI *EFI_PEI_SMBUS2_PPI_NOTIFY) (
	IN EFI_PEI_SMBUS2_PPI               *This,
	IN EFI_SMBUS_DEVICE_ADDRESS         SlaveAddress,
	IN UINTN                            Data,
	IN EFI_PEI_SMBUS_NOTIFY2_FUNCTION    NotifyFunction
	);

//******************************************************* 
// EFI_PEI_SMBUS2_PPI
//*******************************************************
typedef struct _EFI_PEI_SMBUS2_PPI {
	EFI_PEI_SMBUS2_PPI_EXECUTE_OPERATION    Execute;
	EFI_PEI_SMBUS2_PPI_ARP_DEVICE           ArpDevice;
	EFI_PEI_SMBUS2_PPI_GET_ARP_MAP          GetArpMap;
	EFI_PEI_SMBUS2_PPI_NOTIFY               Notify;
    EFI_GUID                                Identifier;
} EFI_PEI_SMBUS2_PPI;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
