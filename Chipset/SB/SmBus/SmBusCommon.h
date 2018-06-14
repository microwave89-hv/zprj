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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusCommon.h 1     6/06/12 8:00a Victortu $
//
// $Revision: 1 $
//
// $Date: 6/06/12 8:00a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmBus/SmBusCommon.h $
// 
// 1     6/06/12 8:00a Victortu
// Implement EFI_PEI_SMBUS2_PPI Support.
// 
// 5     6/27/11 2:26p Artems
// Updated year in file header
// 
// 4     6/17/11 5:52p Artems
// EIP 53378: Replaced tabs with spaces, formatted to follow coding
// standard
// 
// 3     10/16/09 7:08p Artems
// Updated copyright header
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
// Name:        SmBusCommon.h
//
// Description: This file contains shared PEI and DXE Smbus functions and 
//              data structures definitions
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef __SMBUS_COMMON__H__
#define __SMBUS_COMMON__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <AmiCspLib.h>
#include <SmBus.h>

#define   SMBUS_ADDRESS_ARP           0x61  // 1100 001 X SMBus Device Default Address

#define   SMBUS_DATA_PREPARE_TO_ARP   0x01
#define   SMBUS_DATA_RESET_DEVICE     0x02
#define   SMBUS_DATA_GET_UDID_GENERAL 0x03
#define   SMBUS_DATA_ASSIGN_ADDRESS   0x04

#define SMBUS_SPEC_RESERVED_ADDRESS       21
#define GET_UDID_BUFFER_SIZE              17

#define SMBUS_LOWEST_AVAILABLE_ADDRESS   0x08
#define SMBUS_HIGHEST_AVAILABLE_ADDRESS  0x77

typedef VOID (* SMBUS_WAIT ) (
    IN  UINTN   Microseconds
    );

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name: SMBUS_PRIVATE
//
// Description: AMI SMBUS driver private data structure
//
// Fields: Name                 Type                    Description
//----------------------------------------------------------------------------
// SmBusBase                    UINT16                  SMBUS device base IO address
// SmBusWait                    SMBUS_WAIT              Pointer to Wait function
// MaxDevices                   UINT8                   Maximum number of supported devices
// BoardReservedAddressCount    UINT8                   Number of board reserved addesses
// BoardReservedAddressList     UINT8*                  Pointer to board reserved addresses list
// ArpDeviceCount               UINT8                   Number of current devices
// ArpDeviceList                EFI_SMBUS_DEVICE_MAP*   Pointer to list of current devices
// 
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct _SMBUS_PRIVATE
{
    UINT16               SmBusBase;
    SMBUS_WAIT           SmBusWait;
    UINT8                MaxDevices;
    UINT8                BoardReservedAddressCount;
    UINT8                *BoardReservedAddressList;
    UINT8                ArpDeviceCount;
    EFI_SMBUS_DEVICE_MAP *ArpDeviceList;

} SMBUS_PRIVATE;


//*******************************************************
//      Shared functions prototypes
//*******************************************************

VOID SmBusRead (
    IN   UINT16 SmBusBase,
    IN   UINT16 Offset,
    IN   UINTN  ByteCount,
    OUT  UINT8  *Buffer
);

VOID SmBusWrite (
    IN   UINT16 SmBusBase,
    IN   UINT16 Offset,
    IN   UINTN  ByteCount,
    IN   UINT8  *Buffer
);

EFI_STATUS Execute (
    IN     SMBUS_PRIVATE            *Context,
    IN     EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN     EFI_SMBUS_DEVICE_COMMAND Command,
    IN     EFI_SMBUS_OPERATION      Operation,
    IN     BOOLEAN                  PecCheck,
    IN OUT UINTN                    *Length,
    IN OUT VOID                     *Buffer
);

EFI_STATUS CheckNotify (
    IN  SMBUS_PRIVATE            *Context,
    OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress,
    OUT UINTN                    *Data
);

EFI_STATUS ArpDevice (
    IN     SMBUS_PRIVATE            *Context,
    IN     BOOLEAN                  ArpAll,
    IN     EFI_SMBUS_UDID           *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
);

EFI_STATUS GetArpMap (
    IN     SMBUS_PRIVATE        *Context,
    IN OUT UINTN                *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
);

EFI_STATUS PrepareToArp (
    IN SMBUS_PRIVATE *Context
);

EFI_STATUS ArpDeviceDirected (
    IN     SMBUS_PRIVATE            *Context,
    IN     EFI_SMBUS_UDID           *SmbusUdid,
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress
);

EFI_STATUS ArpDeviceFull (
    IN SMBUS_PRIVATE *Context
);

EFI_STATUS AssignAddress (
    IN SMBUS_PRIVATE        *Context,
    IN EFI_SMBUS_DEVICE_MAP *DeviceMap
);

EFI_STATUS GetUdidGeneral (
    IN  SMBUS_PRIVATE        *Context,
    OUT EFI_SMBUS_DEVICE_MAP *DeviceMap
);

BOOLEAN IsAddressAvailable (
    IN SMBUS_PRIVATE *Context,
    IN UINT8         Address
);

UINT8 GetAvailableAddress (
    IN SMBUS_PRIVATE *Context
);

VOID ConvertMapToBuffer (
    IN EFI_SMBUS_DEVICE_MAP *DeviceMap,
    OUT UINT8               *Buffer
);

VOID ConvertBufferToMap (
    OUT EFI_SMBUS_DEVICE_MAP *DeviceMap,
    IN UINT8                 *Buffer
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

