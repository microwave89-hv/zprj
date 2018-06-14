//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2009, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
// $Header: /Alaska/BIN/Modules/Terminal/TerminalSetupVar.h 14    12/12/11 6:55a Rajeshms $
//
// $Revision: 14 $
//
// $Date: 12/12/11 6:55a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Terminal/TerminalSetupVar.h $
// 
// 14    12/12/11 6:55a Rajeshms
// [TAG]  		EIP71636
// [Category]  	New Feature
// [Description]  	Implement the AMI_SERIAL_PROTOCOL for non-generic PCI
// Serial Device.
// [Files]  		AmiSerial.c, AmiSerial.sdl, AmiSerial.mak, AmiSerial.chm,
// AmiSerial.dxs, AmiSerial.cif, Terminal.c, SerialIo.c, TerminalSetup.c,
// InitTerminalStrings.c, TerminalSetupVar.h, Terminal.cif,
// TerminalAmiSerial.h, LegacySredir_Setup.c
// 
// 13    1/24/11 4:04a Lavanyap
// [TAG] - EIP48183
// [Category] - IMPROVEMENT
// [Description] - Update the Terminal eModule to utilize Setup
// Customization 
// [Files] - Terminal.sd, TerminalSetupVar.h
// 
// 12    5/03/10 12:22a Rameshr
// Issue:VT-UTF8 mode support for Console redirection with Debugger
// Solution: Serial Port attribute Setup questions added for the debugger
// console redirection port.
// EIP 37440
// 
// 11    9/28/09 4:09p Rameshr
// Terminal assumes UID to be started from 0. This assumption removed as
// UID should be unique and not be started from 0.
// EIP 17239
// 
// 10    7/02/09 5:01p Rameshr
// Coding Standard and File header updated.
// 
// 9     6/22/09 12:58p Ambikas
// 
// 8     4/14/08 6:51p Ambikas
// 
// 7     6/12/07 3:55p Ambikas
// 
// 6     6/06/07 7:53p Ambikas
// We no longer save segment and bus number of pci serial device.
// 
// 5     6/05/07 6:16p Ambikas
// 
// 4     6/05/07 11:47a Ambikas
//
// 3     6/4/2007 7:31p
// The setup question related data structures for the serial ports will
// not be defined if TOTAL_SERIAL_PORTS is 0.  
//
// 2     5/24/2007 2:33p Ambikas
//
// 1     5/05/2006 5:33p Ambikas
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: TerminalSetupVar.h
//
// Description: Contains definition of PCI_SERIAL_PORTS_LOCATION_VAR 
//		and of varstore declaration SERIAL_PORTS_ENABLED_VAR.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef _TERMINAL_SETUP_VAR_H
#define _TERMINAL_SETUP_VAR_H
#ifdef __cplusplus
extern "C" {
#endif

#include <token.h>

#define TERMINAL_VAR_GUID \
{0x560bf58a, 0x1e0d, 0x4d7e, 0x95, 0x3f, 0x29, 0x80, 0xa2, 0x61, 0xe0, 0x31}

#define SERIAL_PORTS_ENABLED_VAR_C_NAME         L"SerialPortsEnabledVar"
#define SIO_SERIAL_PORTS_LOCATION_VAR_C_NAME    L"SioSerialPortsLocationVar"
#define PCI_SERIAL_PORTS_LOCATION_VAR_C_NAME    L"PciSerialPortsLocationVar"
#define DEBUGGER_SERIAL_PORTS_ENABLED_VAR_C_NAME         L"DebuggerSerialPortsEnabledVar"

#define DEBUGGER_TERMINAL_VAR_GUID \
{0x97ca1a5b, 0xb760, 0x4d1f, 0xa5, 0x4b, 0xd1, 0x90, 0x92, 0x3, 0x2c, 0x90}

#pragma pack(1)

#ifndef TYPEDEF_DEBUGGER_SERIAL_PORTS_ENABLED_VAR
#define TYPEDEF_DEBUGGER_SERIAL_PORTS_ENABLED_VAR
    typedef struct { 
        UINT8 PortEnabled;
    } DEBUGGER_SERIAL_PORTS_ENABLED_VAR;
#endif

#if (TOTAL_SERIAL_PORTS > 0)
#ifndef TYPEDEF_SERIAL_PORTS_ENABLED_VAR
#define TYPEDEF_SERIAL_PORTS_ENABLED_VAR
    typedef struct { 
        UINT8 PortsEnabled[ TOTAL_SERIAL_PORTS ];
    } SERIAL_PORTS_ENABLED_VAR;
#endif
#endif

#if (TOTAL_SIO_SERIAL_PORTS > 0)
#ifndef TYPEDEF_SIO_SERIAL_PORTS_LOCATION_VAR
#define TYPEDEF_SIO_SERIAL_PORTS_LOCATION_VAR
    typedef struct { 
        UINT8 PortUid[ TOTAL_SIO_SERIAL_PORTS ];
        UINT8 Valid[ TOTAL_SIO_SERIAL_PORTS ];
    } SIO_SERIAL_PORTS_LOCATION_VAR;
#endif
#endif

#if (TOTAL_PCI_SERIAL_PORTS > 0)
#ifndef TYPEDEF_PCI_SERIAL_PORTS_LOCATION_VAR
#define TYPEDEF_PCI_SERIAL_PORTS_LOCATION_VAR
    typedef struct { 
        UINT8 Segment[ TOTAL_PCI_SERIAL_PORTS ]; 
        UINT8 Bus[ TOTAL_PCI_SERIAL_PORTS ]; 
        UINT8 Device[ TOTAL_PCI_SERIAL_PORTS ]; 
        UINT8 Function[ TOTAL_PCI_SERIAL_PORTS ]; 
        UINT8 AmiPciSerialPresent[ TOTAL_PCI_SERIAL_PORTS ];
        UINT8 Port[ TOTAL_PCI_SERIAL_PORTS ]; 
    } PCI_SERIAL_PORTS_LOCATION_VAR;
#endif
#endif

#pragma pack()

#ifdef __cplusplus
}
#endif
#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2009, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
