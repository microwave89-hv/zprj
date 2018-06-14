//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Metronome.h 2     3/13/06 1:45a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:45a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Metronome.h $
// 
// 2     3/13/06 1:45a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:42a Felixp
// 
// 1     12/23/04 9:29a Felixp
// 
// 2     3/29/04 2:32a Felixp
// 
// 1     12/31/03 11:05a Robert
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	Metronome.h
//
// Description:	This file is an include file used to define the Architectural
//		Protocol for the Legacy Metronome.  For questions about the specification
//		refer to the DXE CIS
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef __METRONOME_ARCH_PROTOCOL_H__
#define __METRONOME_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

// GUID for the Metronome Architectural Protocol
#define EFI_METRONOME_ARCH_PROTOCOL_GUID \
  { 0x26baccb2, 0x6f42, 0x11d4, 0xbc, 0xe7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 }

GUID_VARIABLE_DECLARATION(gEfiMetronomeArchProtocolGuid, EFI_METRONOME_ARCH_PROTOCOL_GUID);

// Declare forward reference for the Metronome Architectural Protocol
typedef struct _EFI_METRONOME_ARCH_PROTOCOL EFI_METRONOME_ARCH_PROTOCOL;


typedef
EFI_STATUS
(EFIAPI *EFI_METRONOME_WAIT_FOR_TICK) (
   IN struct _EFI_METRONOME_ARCH_PROTOCOL  *This,
   IN UINT32                               TickNumber
  );


// Architectural Protocol structure for Metronome
typedef struct _EFI_METRONOME_ARCH_PROTOCOL {
  EFI_METRONOME_WAIT_FOR_TICK  WaitForTick;
  UINT32                       TickPeriod;
} EFI_METRONOME_ARCH_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
