//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Security2.h 1     4/09/12 5:41p Artems $
//
// $Revision: 1 $
//
// $Date: 4/09/12 5:41p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Security2.h $
// 
// 1     4/09/12 5:41p Artems
// Initial check-in
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Security2.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __ARCH_PROTOCOL_SECURITY2__H__
#define __ARCH_PROTOCOL_SECURITY2__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SECURITY2_ARCH_PROTOCOL_GUID  \
  { 0x94ab2f58, 0x1438, 0x4ef1, 0x91, 0x52, 0x18, 0x94, 0x1a, 0x3a, 0xe, 0x68 }

typedef struct _EFI_SECURITY2_ARCH_PROTOCOL EFI_SECURITY2_ARCH_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SECURITY2_FILE_AUTHENTICATION) (
    IN CONST EFI_SECURITY2_ARCH_PROTOCOL *This,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *File,
    IN VOID *FileBuffer,
    IN UINTN FileSize,
    IN BOOLEAN BootPolicy
);

struct _EFI_SECURITY2_ARCH_PROTOCOL {
    EFI_SECURITY2_FILE_AUTHENTICATION FileAuthentication;
};

GUID_VARIABLE_DECLARATION(gEfiSecurity2ArchProtocolGuid, EFI_SECURITY2_ARCH_PROTOCOL_GUID);
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