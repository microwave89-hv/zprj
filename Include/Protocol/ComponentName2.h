//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/ComponentName2.h 1     5/27/11 5:52p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/27/11 5:52p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/ComponentName2.h $
// 
// 1     5/27/11 5:52p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	ComponentName2.h
//
// Description:	Component Name 2 Protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __COMPONENT_NAME2_PROTOCOL__H__
#define __COMPONENT_NAME2_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID
#if EFI_SPECIFICATION_VERSION<=0x20000
#define EFI_COMPONENT_NAME2_PROTOCOL_GUID \
	{0x107a772c,0xd5e1,0x11d4,0x9a,0x46,0x0,0x90,0x27,0x3f,0xc1,0x4d}
#else //if EFI_SPECIFICATION_VERSION
#define EFI_COMPONENT_NAME2_PROTOCOL_GUID \
    { 0x6a7a5cff, 0xe8d9, 0x4f70, 0xba, 0xda, 0x75, 0xab, 0x30, 0x25, 0xce, 0x14 }
#endif //if EFI_SPECIFICATION_VERSION
#endif // EFI_COMPONENT_NAME2_PROTOCOL_GUID

GUID_VARIABLE_DECLARATION(gEfiComponentName2ProtocolGuid, EFI_COMPONENT_NAME2_PROTOCOL_GUID);

typedef struct _EFI_COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_COMPONENT_NAME2_GET_DRIVER_NAME) (
    IN  EFI_COMPONENT_NAME2_PROTOCOL *This,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **DriverName
);

typedef EFI_STATUS (EFIAPI *EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME) (
    IN  EFI_COMPONENT_NAME2_PROTOCOL *This,
    IN  EFI_HANDLE                   ControllerHandle,
    IN  EFI_HANDLE                   ChildHandle OPTIONAL,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **ControllerName
);

struct _EFI_COMPONENT_NAME2_PROTOCOL {
    EFI_COMPONENT_NAME2_GET_DRIVER_NAME      GetDriverName;
    EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME  GetControllerName;
    CHAR8                                   *SupportedLanguages;
};
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************