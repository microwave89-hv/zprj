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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusDxe.h 1     6/06/12 8:00a Victortu $
//
// $Revision: 1 $
//
// $Date: 6/06/12 8:00a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusDxe.h $
// 
// 1     6/06/12 8:00a Victortu
// Implement EFI_PEI_SMBUS2_PPI Support.
// 
// 9     8/03/11 8:18a Abelwu
// Updated AMI_SMBUS_SMM_PROTOCOL_GUID for following INTEL RC.
// 
// 8     7/19/11 8:27a Abelwu
// [TAG]  		NONE
// [Category]  	New Feature
// [Description]  	Added SMBus SMM Protocol support.
// [Files]  		SmBusDxe.h
// 
// 7     6/27/11 2:26p Artems
// Updated year in file header
// 
// 6     6/17/11 5:52p Artems
// EIP 53378: Replaced tabs with spaces, formatted to follow coding
// standard
// 
// 5     5/18/11 11:50a Artems
// 
// 4     10/16/09 7:11p Artems
// Updated copyright header
// 
// 3     3/03/09 4:36p Artems
// EIP 19949 Added support for multiple SM Bus controllers that
// represented by different PCI devices
// 
// 2     1/28/09 6:52p Artems
// Modified in accordance with coding standard
// 
// 1     1/09/09 6:53p Artems
// New implementation of SMBus EIP 16730
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:        SmBusDxe.h
//
// Description: This file contains DXE SMBUS Driver functions and data
//              structures definition.
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef __SMBUS_DXE__H__
#define __SMBUS_DXE__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <AmiDxeLib.h>
#include <Protocol/Smbus.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include "SmBusCommon.h"

#define AMI_SMBUS_SMM_PROTOCOL_GUID \
  {0x72e40094, 0x2ee1, 0x497a, 0x8f, 0x33, 0x4c, 0x93, 0x4a, 0x9e, 0x9c, 0xc}

#define MAX_DXE_ARP_DEVICES 0x30

#pragma pack(1)

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: SMBUS_DXE_PRIVATE
//
// Description: AMI SMBUS driver PEI private data structure
//
// Fields: Name         Type                        Description
//----------------------------------------------------------------------------
// SmBusProtocol        EFI_SMBUS_HC_PROTOCOL       SMBUS host controller protocol structure
// Identifier           EFI_GUID                    SMBUS host controller identifier
// SmBusContext         SMBUS_PRIVATE               SMBUS private data structure
// PciIo                EFI_PCI_IO_PROTOCOL*        Pointer to PCI IO protocol of SMBUS device
// NotifyList           DLIST                       Linked list of notify callbacks
// NotifyEvent          EFI_EVENT                   EFI_EVENT structure
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct _SMBUS_DXE_PRIVATE
{
    EFI_SMBUS_HC_PROTOCOL    SmBusProtocol;
    EFI_GUID                 Identifier;    
    SMBUS_PRIVATE            SmBusContext;
    EFI_PCI_IO_PROTOCOL      *PciIo;
    DLIST                    NotifyList;
    EFI_EVENT                NotifyEvent;
} SMBUS_DXE_PRIVATE;

#pragma pack()

typedef struct {
    DLINK                         Link;
    EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress;
    UINTN                         Data;
    EFI_SMBUS_NOTIFY_FUNCTION     NotifyFunction;
} SMBUS_NOTIFY_LINK;    

EFI_STATUS SmBusDxeExecute (
  IN      EFI_SMBUS_HC_PROTOCOL         *This,
  IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
  IN      EFI_SMBUS_DEVICE_COMMAND      Command,
  IN      EFI_SMBUS_OPERATION           Operation,
  IN      BOOLEAN                       PecCheck,
  IN OUT  UINTN                         *Length,
  IN OUT  VOID                          *Buffer
);

EFI_STATUS SmBusDxeArpDevice (
  IN      EFI_SMBUS_HC_PROTOCOL         *This,
  IN      BOOLEAN                       ArpAll,
  IN      EFI_SMBUS_UDID                *SmbusUdid, OPTIONAL
  IN OUT  EFI_SMBUS_DEVICE_ADDRESS      *SlaveAddress OPTIONAL
);

EFI_STATUS SmBusDxeGetArpMap (
  IN      EFI_SMBUS_HC_PROTOCOL         *This,
  IN OUT  UINTN                         *Length,
  IN OUT  EFI_SMBUS_DEVICE_MAP          **SmbusDeviceMap
);

EFI_STATUS SmBusDxeNotify (
  IN      EFI_SMBUS_HC_PROTOCOL         *This,
  IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
  IN      UINTN                         Data,
  IN      EFI_SMBUS_NOTIFY_FUNCTION     NotifyFunction
);

EFI_STATUS  DriverBindingSupported ( 
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
);

EFI_STATUS  DriverBindingStart ( 
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
);

EFI_STATUS  DriverBindingStop ( 
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   ControllerHandle,
    IN  UINTN                       NumberOfChildren,
    IN  EFI_HANDLE                  *ChildHandleBuffer
);

EFI_STATUS InitializeNotifyPolling (
    IN SMBUS_DXE_PRIVATE *Context
);

VOID PollSmbusNotify (
    IN  EFI_EVENT Event,
    IN  VOID      *Context
);

VOID RetrieveHobData (
    IN OUT SMBUS_DXE_PRIVATE *Context
);

VOID SmBusDxeWait(
    IN UINTN Microseconds
    );

/*
VOID SmBusDxeInitialize(
    IN SMBUS_PRIVATE *Context
    );
*/

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
