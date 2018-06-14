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
// $Header: /Alaska/BIN/Core/Include/SmBus.h 2     2/05/11 2:05p Artems $
//
// $Revision: 2 $
//
// $Date: 2/05/11 2:05p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/SmBus.h $
// 
// 2     2/05/11 2:05p Artems
// Added helper macros to simplify SMBUS address handling
// 
// 1     1/16/09 9:57a Felixp
// SM Bus Protocol and PPI headers are updated. Common code moved into
// newly created header file (Include\SmBus.h).
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SmBus.h
//
// Description:	SM BUS data structure declarations
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SMBUS_MAIN__H__
#define __SMBUS_MAIN__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>

#pragma pack(1)

// PEC BIT is bit 22 in SMBUS address
#define SMBUS_LIB_PEC_BIT   (1 << 22)

/**
  Macro that converts SMBUS slave address, SMBUS command, SMBUS data length,
  and PEC to a value that can be passed to the SMBUS Library functions.

  Computes an address that is compatible with the SMBUS Library functions.
  The unused upper bits of SlaveAddress, Command, and Length are stripped
  prior to the generation of the address.
  
  @param  SlaveAddress    SMBUS Slave Address.  Range 0..127.
  @param  Command         SMBUS Command.  Range 0..255.
  @param  Length          SMBUS Data Length.  Range 0..32.
  @param  Pec             TRUE if Packet Error Checking is enabled.  Otherwise FALSE.

**/
#define SMBUS_LIB_ADDRESS(SlaveAddress,Command,Length,Pec)  \
  ( ((Pec) ? SMBUS_LIB_PEC_BIT: 0)      | \
    (((SlaveAddress) & 0x7f) << 1)      | \
    (((Command)      & 0xff) << 8)      | \
    (((Length)       & 0x3f) << 16)       \
  )

#define SMBUS_LIB_SLAVE_ADDRESS(SmBusAddress)      (((SmBusAddress) >> 1)  & 0x7f)
#define SMBUS_LIB_COMMAND(SmBusAddress)            (((SmBusAddress) >> 8)  & 0xff)
#define SMBUS_LIB_LENGTH(SmBusAddress)             (((SmBusAddress) >> 16) & 0x3f)
#define SMBUS_LIB_PEC(SmBusAddress)     ((BOOLEAN) (((SmBusAddress) & SMBUS_LIB_PEC_BIT) != 0))
#define SMBUS_LIB_RESERVED(SmBusAddress)            ((SmBusAddress) & ~(((1 << 22) - 2) | SMBUS_LIB_PEC_BIT))

typedef struct {
  UINTN   SmbusDeviceAddress:7;
} EFI_SMBUS_DEVICE_ADDRESS;

typedef UINTN EFI_SMBUS_DEVICE_COMMAND;

typedef enum _EFI_SMBUS_OPERATION {
  EfiSmbusQuickRead,
  EfiSmbusQuickWrite,
  EfiSmbusReceiveByte,
  EfiSmbusSendByte,
  EfiSmbusReadByte,
  EfiSmbusWriteByte,
  EfiSmbusReadWord,
  EfiSmbusWriteWord,
  EfiSmbusReadBlock,
  EfiSmbusWriteBlock,
  EfiSmbusProcessCall,
  EfiSmbusBWBRProcessCall
} EFI_SMBUS_OPERATION;
//******************************************************
// EFI_SMBUS_UDID 
//******************************************************
typedef struct {
  UINT32  VendorSpecificId;
  UINT16  SubsystemDeviceId;
  UINT16  SubsystemVendorId;
  UINT16  Interface;
  UINT16  DeviceId;
  UINT16  VendorId;
  UINT8   VendorRevision;
  UINT8   DeviceCapabilities;
} EFI_SMBUS_UDID;
//******************************************************* 
// EFI_SMBUS_DEVICE_MAP 
//*******************************************************
typedef struct {
  EFI_SMBUS_DEVICE_ADDRESS  SmbusDeviceAddress;
  EFI_SMBUS_UDID            SmbusDeviceUdid;
} EFI_SMBUS_DEVICE_MAP;
#pragma pack()
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
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
