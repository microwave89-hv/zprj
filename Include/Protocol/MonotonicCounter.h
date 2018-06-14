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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/MonotonicCounter.h 3     3/13/06 1:45a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:45a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/MonotonicCounter.h $
// 
// 3     3/13/06 1:45a Felixp
// 
// 2     3/04/05 10:42a Mandal
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
// 1     3/30/04 2:24a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	MonotonicCounter.h
//
// Description:	MonotonicCounter Architectural Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __MONOTONIC_COUNTER_ARCH_PROTOCOL_H__
#define __MONOTONIC_COUNTER_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_MONOTONIC_COUNTER_ARCH_PROTOCOL_GUID \
	{0x1da97072,0xbddc,0x4b30,0x99,0xf1,0x72,0xa0,0xb5,0x6f,0xff,0x2a}

GUID_VARIABLE_DECLARATION(gEfiMonotonicCounterArchProtocolGuid, EFI_MONOTONIC_COUNTER_ARCH_PROTOCOL_GUID);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
