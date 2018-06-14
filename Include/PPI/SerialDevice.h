//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
// $Header: /Alaska/BIN/Core/Modules/Recovery/SerialDevice.h 2     2/13/12 4:14a Rajeshms $
//
// $Revision: 2 $
//
// $Date: 2/13/12 4:14a $
//*****************************************************************************
// Revision	History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/Recovery/SerialDevice.h $
// 
// 2     2/13/12 4:14a Rajeshms
// [TAG]  		EIP80704
// [Category]  	New Feature
// [Description]  	Serial Recovery support through PCI Serial Port .
// [Files]  		PciSerialRecovery.mak, PciSerialRecovery.sdl,
// PciSerialRecovery.c, PciSerialRecovery.h, PciSerialRecovery.chm,
// PciSerialRecovery.dxs, SerialRecovery.c, SerialDevice.h
// 
// 1     7/10/09 10:40a Rameshr
// Initial Check-in
// -Recovery from Multiple Serial Device support Added
// 
//
//*****************************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	SerialDevice.h
//
// Description: Protocol Header for the Serial Recovery Device.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _PEI_SERIAL_DEVICE_PPI_H
#define _PEI_SERIAL_DEVICE_PPI_H
#ifdef __cplusplus
extern "C" {
#endif

#include "EFI.h"
#include "PEI.h"

#define PEI_RECOVERY_SERIAL_MODE_PPI_GUID \
  { 0x5e7063d3, 0xc12, 0x475b, 0x98, 0x35, 0x14, 0xab, 0xb1, 0xcb, 0xe, 0xe9 }


enum {
    SerialDataReg,
    InteruptEnableReg,
    FifoControlReg,
    LineControlReg,
    ModemControlReg,
    LineStatusReg,
    ModemStatusReg
};

typedef struct _PEI_RECOVERY_SERIAL_MODE_PPI PEI_RECOVERY_SERIAL_MODE_PPI;

typedef UINT8 (EFIAPI *SERIAL_READ) (
    IN  PEI_RECOVERY_SERIAL_MODE_PPI *This,
    IN  UINT8   Offset
);

typedef VOID (EFIAPI *SERIAL_WRITE) (
    IN  PEI_RECOVERY_SERIAL_MODE_PPI *This,
    IN  UINT8   Offset,
    IN  UINT8   Data
);

#pragma pack(1)
struct _PEI_RECOVERY_SERIAL_MODE_PPI {
    UINT64          SerialDeviceBaseAddress;
    SERIAL_READ     ReadSerialDevice;
    SERIAL_WRITE    WriteSerialDevice;
};
#pragma pack()

#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

