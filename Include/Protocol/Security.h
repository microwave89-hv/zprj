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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Security.h 1     4/25/07 9:36a Felixp $
//
// $Revision: 1 $
//
// $Date: 4/25/07 9:36a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Security.h $
// 
// 1     4/25/07 9:36a Felixp
// 
// 1     5/19/06 11:28p Felixp
// 
// 1     3/13/06 1:57a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	<This File Name>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __ARCH_PROTOCOL_SECURITY__H__
#define __ARCH_PROTOCOL_SECURITY__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SECURITY_ARCH_PROTOCOL_GUID  \
  { 0xA46423E3, 0x4617, 0x49f1, 0xB9, 0xFF, 0xD1, 0xBF, 0xA9, 0x11, 0x58, 0x39 }

typedef struct _EFI_SECURITY_ARCH_PROTOCOL EFI_SECURITY_ARCH_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SECURITY_FILE_AUTHENTICATION_STATE)(
	IN EFI_SECURITY_ARCH_PROTOCOL *This,
	IN UINT32 AuthenticationStatus,
	IN EFI_DEVICE_PATH_PROTOCOL *File
);

struct _EFI_SECURITY_ARCH_PROTOCOL {
	EFI_SECURITY_FILE_AUTHENTICATION_STATE FileAuthenticationState;
};

GUID_VARIABLE_DECLARATION(gEfiSecurityArchProtocolGuid, EFI_SECURITY_ARCH_PROTOCOL_GUID);
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