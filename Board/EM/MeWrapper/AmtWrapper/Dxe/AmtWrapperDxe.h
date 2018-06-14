//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AmtWrapperDxe.h 3     4/18/13 1:55a Klzhan $
//
// $Revision: 3 $
//
// $Date: 4/18/13 1:55a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AmtWrapperDxe.h $
// 
// 3     4/18/13 1:55a Klzhan
// [TAG]  		EIP119190
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	BIOS doesn't wait for KVM pass code input.
// [RootCause]  	The Con Out Start protocol GUID is different in AMI and
// ME RC.
// [Solution]  	Install ME RC ConOut Protocol when AMI ConOut Protocol
// installed.
// [Files]  		AmtWrapperDxe.c
// AmtWrapperDxe.h
// 
// 2     4/24/12 12:36a Klzhan
// Update modulepart to latest
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:43a Klzhan
// Initial Check-in
// 
// 2     12/28/10 2:00a Klzhan
// Improvement : Enable/Disable Terminal item for SOL redirection.
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            AmtWrapperDxe.h
//
// Description:     Header file for Amt Wrapper Dxe module
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _AMT_WRAPPER_DXE_H_
#define _AMT_WRAPPER_DXE_H_

#include "Efi.h"
#include "EfiDriverLib.h"
#include "EfiCommonLib.h"
#include "BdsLib.h"
#include "EfiScriptLib.h"
#if defined(LEGACYSREDIR_SUPPORT) && (LEGACYSREDIR_SUPPORT == 1)
#include "Protocol\LegacySredir.h"
#endif
#include "AmtLib.h"
#include "MeAccess.h"

#include EFI_PROTOCOL_CONSUMER   (AmtPlatformPolicy)
#include EFI_PROTOCOL_CONSUMER   (AmtWrapper)
#include EFI_PROTOCOL_CONSUMER   (BootScriptSave)
#include EFI_PROTOCOL_CONSUMER   (PciRootBridgeIo)
#include EFI_PROTOCOL_CONSUMER   (ActiveManagement)
#include EFI_PROTOCOL_CONSUMER   (PciIo)
#include EFI_PROTOCOL_CONSUMER   (SerialIo)

#include EFI_GUID_DEFINITION    (MeBiosExtensionSetup)

#define R_PCI_SVID                          0x2C

#define     DISPLAY_SCREEN              0x01				// for LegacySredr CSM16
#define     SUPPORT8025                 0x02				// for LegacySredr CSM16

// define for SREDIR_DISPLAY_MODE
#define 	DISPLAY_BY_SETUP			0x00
#define 	DISPLAY_BY_80x24			0x01
#define 	DISPLAY_BY_80x25			0x02

#define STOPB   0x4                 //      Bit2: Number of Stop Bits
#define PAREN   0x8                 //      Bit3: Parity Enable
#define EVENPAR 0x10                //      Bit4: Even Parity Select
#define STICPAR 0x20                //      Bit5: Sticky Parity
#define SERIALDB 0x3                //      Bit0-1: Number of Serial 
                                    //     

#define EFI_WIN_NT_THUNK_PROTOCOL_GUID \
  { 0x58c518b1, 0x76f3, 0x11d4, 0xbc, 0xea, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 }

#define EFI_WIN_NT_BUS_DRIVER_IO_PROTOCOL_GUID \
  { 0x96eb4ad6, 0xa32a, 0x11d4, 0xbc, 0xfd, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 }

#define EFI_WIN_NT_SERIAL_PORT_GUID \
  { 0xc95a93d, 0xa006, 0x11d4, 0xbc, 0xfa, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 }

#define AMI_CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID \
	{ 0xef9a3971, 0xc1a0, 0x4a93, 0xbd, 0x40, 0x5a, 0xa1, 0x65, 0xf2, 0xdc, 0x3a }

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           SerialOverLAN;
  UART_DEVICE_PATH          Uart;
  VENDOR_DEVICE_PATH        TerminalType;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_PCI_SERIAL_OVER_LAN_DEVICE_PATH;

#define gPciRootBridge \
  { \
	ACPI_DEVICE_PATH, \
	ACPI_DP, \
    (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)), \
    (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8), \
    EISA_PNP_ID (0x0A03), 0 \
  }

#define gEndEntire \
  { \
    END_DEVICE_PATH_TYPE,\
    END_ENTIRE_DEVICE_PATH_SUBTYPE,\
    END_DEVICE_PATH_LENGTH,\
    0\
  }
  
VOID
SetSOLCOMEnable(
    IN BOOLEAN         Enabled
);

EFI_STATUS 
AmtWrapperInit(
    IN EFI_HANDLE ImageHandle, 
    IN OUT EFI_SYSTEM_TABLE *SystemTable
);

BOOLEAN
AmtWrapperGet(
    UINTN Index, 
    VOID *pVar
);

BOOLEAN 
AmtWrapperSet(
    UINTN Index, 
    VOID *pVar
);

BOOLEAN
ActiveManagementPauseBoot (
    IN VOID
);

BOOLEAN
ActiveManagementEnterSetup (
    IN VOID
);

BOOLEAN
ActiveManagementEnableSol (
    IN VOID
);

BOOLEAN
ActiveManagementEnableIdeR (
    IN VOID
);

EFI_STATUS
BdsAsfInitialization (
    IN VOID
);

EFI_STATUS
BdsBootViaAsf (
    IN VOID
);

VOID
InitAmtWrapperLib(
	IN VOID
);

BOOLEAN
AmtWrapperEnableKvm(
	IN VOID
);

BOOLEAN
AmtWrapperInitializationKvm(
	IN VOID
);

BOOLEAN
AmtWrapperEnableSol(
	IN VOID
);

BOOLEAN
AmtWrapperEnableIdeR(
	IN VOID
);

BOOLEAN
AmtWrapperPauseBoot(
	IN VOID
);	

BOOLEAN
AmtWrapperEnterSetup(
	IN VOID
);

EFI_STATUS
AmtWrapperBdsBootViaAsf(
	IN VOID
);

EFI_STATUS
AmtWrapperReadyToBoot(
	EFI_EVENT           Event,
    VOID                *ParentImageHandle
);

BOOLEAN
BdsKvmInitialization (
  IN  VOID
);

UINTN IsSOL(
	IN EFI_HANDLE Controller
);

UINTN IsIDER(
	IN EFI_HANDLE Controller
);
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************