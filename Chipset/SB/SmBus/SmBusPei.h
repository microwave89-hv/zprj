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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusPei.h 1     6/06/12 8:00a Victortu $
//
// $Revision: 1 $
//
// $Date: 6/06/12 8:00a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusPei.h $
// 
// 1     6/06/12 8:00a Victortu
// Implement EFI_PEI_SMBUS2_PPI Support.
// 
// 8     7/21/11 7:31a Abelwu
// [TAG]  		EIP63768
// [Category]  	Improvement
// [Description]  	Supported Core 4.6.5.x PI 1.2 / uEFI 2.3.1 compliance
// [Files]  		SmBusPei.h
// 
// 7     7/19/11 8:02a Abelwu
// [TAG]  		EIP63768
// [Category]  	Improvement
// [Description]  	Supported Core 4.6.5.x PI 1.2 / uEFI 2.3.1 compliance
// [Files]  		SmBusPei.h
// 
// 6     6/27/11 2:26p Artems
// Updated year in file header
// 
// 5     6/17/11 5:52p Artems
// EIP 53378: Replaced tabs with spaces, formatted to follow coding
// standard
// 
// 4     10/16/09 7:10p Artems
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
// Name:        SmBusPei.h
//
// Description: This file contains PEI SMBUS Driver functions and data structures definition
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMBUS_PEI__H__
#define __SMBUS_PEI__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Ppi/Smbus2.h>

#include "SmBusCommon.h"

#define MAX_PEI_ARP_DEVICES 8

#pragma pack(1)

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: SMBUS_PEI_PRIVATE
//
// Description: AMI SMBUS driver PEI private data structure
//
// Fields: Name         Type                        Description
//----------------------------------------------------------------------------
// SmBusPpi             EFI_PEI_SMBUS/2_PPI         SMBUS (2) PPI structure
// Identifier           EFI_GUID                    SMBUS controller identifier
// SmBusContext         SMBUS_PRIVATE               SMBUS private data structure
// NotifyDesc           EFI_PEI_NOTIFY_DESCRIPTOR   Notify descriptor structure
// SmBusPpiDesc         EFI_PEI_PPI_DESCRIPTOR      PPI descriptor structure
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct _SMBUS_PEI_PRIVATE
{
    EFI_PEI_SMBUS2_PPI        SmBusPpi;
    SMBUS_PRIVATE             SmBusContext;
    EFI_PEI_NOTIFY_DESCRIPTOR NotifyDesc;
    EFI_PEI_PPI_DESCRIPTOR    SmBusPpiDesc;
} SMBUS_PEI_PRIVATE;

#pragma pack()

EFI_STATUS SmBusPeiEntryPoint (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices
);

EFI_STATUS SmBusPeiExecute (
    IN CONST EFI_PEI_SMBUS2_PPI *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN EFI_SMBUS_DEVICE_COMMAND Command,
    IN EFI_SMBUS_OPERATION Operation,
    IN BOOLEAN PecCheck,
    IN OUT UINTN *Length,
    IN OUT VOID *Buffer
);

EFI_STATUS SmBusPeiArpDevice (
    IN CONST EFI_PEI_SMBUS2_PPI *This,
    IN BOOLEAN ArpAll,
    IN EFI_SMBUS_UDID *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
);

EFI_STATUS SmBusPeiGetArpMap (
    IN CONST EFI_PEI_SMBUS2_PPI *This,
    IN OUT UINTN *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
);

EFI_STATUS SmBusPeiNotify (
    IN CONST EFI_PEI_SMBUS2_PPI *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN UINTN Data,
    IN EFI_PEI_SMBUS_NOTIFY2_FUNCTION NotifyFunction
);

EFI_STATUS SmBusEndOfPeiCallback (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
);

VOID SmBusPeiWait(
    IN UINTN Microseconds
);

VOID SmBusPeiInitialize(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN SMBUS_PRIVATE                *Context
);

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
