//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Capsule.h 1     10/07/06 10:17a Felixp $
//
// $Revision: 1 $
//
// $Date: 10/07/06 10:17a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Capsule.h $
// 
// 1     10/07/06 10:17a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Capsule.h
//
// Description:	Defines Capsule Architectural Protocol
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __CAPSULE_ARCH_PROTOCOL_H__
#define __CAPSULE_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_CAPSULE_ARCH_PROTOCOL_GUID \
  { 0x5053697e, 0x2cbc, 0x4819, 0x90, 0xd9, 0x5, 0x80, 0xde, 0xee, 0x57, 0x54 }

GUID_VARIABLE_DECLARATION(gEfiCapsuleArchProtocolGuid, EFI_CAPSULE_ARCH_PROTOCOL_GUID);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************