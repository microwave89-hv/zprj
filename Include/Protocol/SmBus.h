//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
//**********************************************************************//
// $Header: /Alaska/BIN/Core/Include/Protocol/SmBus.h 3     1/16/09 9:51a Felixp $
//
// $Revision: 3 $
//
// $Date: 1/16/09 9:51a $
//*****************************************************************************
// Revision	History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/SmBus.h $
// 
// 3     1/16/09 9:51a Felixp
// SM Bus Protocol and PPI headers are updated. Common code moved into
// newly created header file (Include\SmBus.h).
// 
// 1     11/07/05 3:40p Sivagarn
// Initial Checkin
//
//*****************************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
// Name:		SmBus.h
//
// Description:	This file contains the protocol definitions for Smbus protocol
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef __SMBUS_HC_PROTOCOL_H__
#define __SMBUS_HC_PROTOCOL_H__
#include <EFI.h>
#include <SmBus.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SMBUS_HC_PROTOCOL_GUID  \
  {0xe49d33ed, 0x513d, 0x4634, 0xb6, 0x98, 0x6f, 0x55, 0xaa, 0x75, 0x1c, 0x1b}

GUID_VARIABLE_DECLARATION(gEfiSmbusProtocolGuid,EFI_SMBUS_HC_PROTOCOL_GUID);

typedef struct _EFI_SMBUS_HC_PROTOCOL EFI_SMBUS_HC_PROTOCOL;
typedef struct _EFI_SMBUS_DATA_STRUC SMBUS_DATA_STRUC;
                  

//******************************************************* 
// EFI_SMBUS_NOTIFY_FUNCTION 
//*******************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SMBUS_NOTIFY_FUNCTION) (
  IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
  IN      UINTN                         Data
);
//******************************************************* 
// EFI_SMBUS_HC_EXECUTE_OPERATION 
//*******************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SMBUS_HC_EXECUTE_OPERATION) (
  IN EFI_SMBUS_HC_PROTOCOL *This,
  IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
  IN      EFI_SMBUS_DEVICE_COMMAND      Command,
  IN      EFI_SMBUS_OPERATION           Operation,
  IN      BOOLEAN                       PecCheck,
  IN OUT  UINTN                         *Length,
  IN OUT  VOID                          *Buffer
  );
//******************************************************* 
// EFI_SMBUS_HC_PROTOCOL_ARP_DEVICE 
//*******************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SMBUS_HC_PROTOCOL_ARP_DEVICE) (
  IN EFI_SMBUS_HC_PROTOCOL *This,
  IN      BOOLEAN                       ArpAll,
  IN      EFI_SMBUS_UDID                *SmbusUdid, OPTIONAL
  IN OUT  EFI_SMBUS_DEVICE_ADDRESS      *SlaveAddress OPTIONAL
);
//******************************************************* 
// EFI_SMBUS_HC_PROTOCOL_GET_ARP_MAP 
//*******************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SMBUS_HC_PROTOCOL_GET_ARP_MAP) (
  IN EFI_SMBUS_HC_PROTOCOL *This,
  IN OUT  UINTN                         *Length,
  IN OUT  EFI_SMBUS_DEVICE_MAP          **SmbusDeviceMap
);
//******************************************************* 
// EFI_SMBUS_HC_PROTOCOL_NOTIFY 
//*******************************************************
typedef
EFI_STATUS
(EFIAPI *EFI_SMBUS_HC_PROTOCOL_NOTIFY) (
  IN EFI_SMBUS_HC_PROTOCOL *This,
  IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
  IN      UINTN                         Data,
  IN      EFI_SMBUS_NOTIFY_FUNCTION     NotifyFunction
);
//******************************************************* 
// EFI_SMBUS_HC_PROTOCOL 
//*******************************************************
typedef struct _EFI_SMBUS_HC_PROTOCOL {
  EFI_SMBUS_HC_EXECUTE_OPERATION    Execute;
  EFI_SMBUS_HC_PROTOCOL_ARP_DEVICE  ArpDevice;
  EFI_SMBUS_HC_PROTOCOL_GET_ARP_MAP GetArpMap;
  EFI_SMBUS_HC_PROTOCOL_NOTIFY      Notify;
};

#ifdef __cplusplus
}
#endif
#endif	// __SMBUS_CTRL_H__
//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
