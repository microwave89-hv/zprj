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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/RealTimeClock.h 1     3/13/06 1:45a Felixp $
//
// $Revision: 1 $
//
// $Date: 3/13/06 1:45a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/RealTimeClock.h $
// 
// 1     3/13/06 1:45a Felixp
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
// 1     1/15/04 6:19p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	RealTimeClock.h
//
// Description:	The Real Time Clock Architectural Protocol only consists
//              of a GUID. The Protocol is installed with a NULL pointer
//              to the structure after the RTC EFI services are installed.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __REAL_TIME_CLOCK_ARCH_PROTOCOL_H__
#define __REAL_TIME_CLOCK_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_REAL_TIME_CLOCK_ARCH_PROTOCOL_GUID \
    {0x27CFAC87,0x46CC,0x11d4,0x9A,0x38,0x00,0x90,0x27,0x3F,0xC1,0x4D}

GUID_VARIABLE_DECLARATION(gEfiRealTimeClockArchProtocolGuid, EFI_REAL_TIME_CLOCK_ARCH_PROTOCOL_GUID);
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
