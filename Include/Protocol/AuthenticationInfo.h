//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/AuthenticationInfo.h 1     4/22/11 6:45p Artems $
//
// $Revision: 1 $
//
// $Date: 4/22/11 6:45p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/AuthenticationInfo.h $
// 
// 1     4/22/11 6:45p Artems
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  AuthenticationInfo.h
//
//  Description:
//  EFI_AUTHENTICATION_INFO_PROTOCOL definition file
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __AUTHENTICATION_INFO_PROTOCOL__H__
#define __AUTHENTICATION_INFO_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>

#define EFI_AUTHENTICATION_INFO_PROTOCOL_GUID \
    { 0x7671d9d0, 0x53db, 0x4173, 0xaa, 0x69, 0x23, 0x27, 0xf2, 0x1f, 0xb, 0xc7 }

GUID_VARIABLE_DECLARATION(gEfiAuthenticationInfoProtocolGuid, EFI_AUTHENTICATION_INFO_PROTOCOL_GUID);


typedef struct _EFI_AUTHENTICATION_INFO_PROTOCOL EFI_AUTHENTICATION_INFO_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_AUTHENTICATION_INFO_PROTOCOL_GET) (
    IN  EFI_AUTHENTICATION_INFO_PROTOCOL *This,
    IN  EFI_HANDLE                       ControllerHandle,
    OUT VOID                             **Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_AUTHENTICATION_INFO_PROTOCOL_SET) (
    IN EFI_AUTHENTICATION_INFO_PROTOCOL *This,
    IN EFI_HANDLE                       ControllerHandle,
    IN VOID                             *Buffer
);

struct _EFI_AUTHENTICATION_INFO_PROTOCOL {
    EFI_AUTHENTICATION_INFO_PROTOCOL_GET Get;
    EFI_AUTHENTICATION_INFO_PROTOCOL_SET Set;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
