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
// $Header: /Alaska/SOURCE/Core/EDK/Protocol/VariableWrite.h 1     5/19/06 11:28p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/19/06 11:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/Protocol/VariableWrite.h $
// 
// 1     5/19/06 11:28p Felixp
// 
// 1     3/13/06 1:57a Felixp
// 
// 2     3/04/05 10:43a Mandal
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
// Name:	VariableWrite.h
//
// Description:	Variable Architectural Protocol Definitions
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __VARIABLE_WRITE_ARCH_PROTOCOL_H__
#define __VARIABLE_WRITE_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#ifndef EFI_VARIABLE_WRITE_ARCH_PROTOCOL_GUID
#define EFI_VARIABLE_WRITE_ARCH_PROTOCOL_GUID \
	{0x6441f818,0x6362,0x4e44,0xb5,0x70,0x7d,0xba,0x31,0xdd,0x24,0x53}
#endif
GUID_VARIABLE_DECLARATION(gEfiVariableWriteArchProtocolGuid, EFI_VARIABLE_WRITE_ARCH_PROTOCOL_GUID);
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
