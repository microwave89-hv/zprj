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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Reset.h 2     3/13/06 1:45a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:45a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Reset.h $
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
// 1     3/25/04 3:02p Robert
// 
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	Reset.h
//
// Description:	This file contains the support values for the Reset 
//		Architectural Protocol
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef __RESET_ARCH_PROTOCOL_H__
#define __RESET_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

// GUID for the Reset Architectural Protocol
#define EFI_RESET_ARCH_PROTOCOL_GUID \
  { 0x27CFAC88, 0x46CC, 0x11D4, 0x9A, 0x38, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }

GUID_VARIABLE_DECLARATION(gEfiResetArchProtocolGuid, EFI_RESET_ARCH_PROTOCOL_GUID);

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
