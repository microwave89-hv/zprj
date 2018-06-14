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
// $Header: /Alaska/BIN/Core/Include/Protocol/ComponentName.h 6     6/16/11 3:22p Felixp $
//
// $Revision: 6 $
//
// $Date: 6/16/11 3:22p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/ComponentName.h $
// 
// 6     6/16/11 3:22p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 5     5/27/11 5:53p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 4     8/21/09 3:05p Felixp
// Definition of the ComponentName2 protocol is added.
// 
// 1     9/20/04 1:24p Olegi
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	ComponentName.h
//
// Description:	Component Name protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __COMPONENT_NAME_PROTOCOL__H__
#define __COMPONENT_NAME_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

//*********************** Component Name Protocol ******************/
#define EFI_COMPONENT_NAME_PROTOCOL_GUID \
	{0x107a772c,0xd5e1,0x11d4,0x9a,0x46,0x0,0x90,0x27,0x3f,0xc1,0x4d}

GUID_VARIABLE_DECLARATION(gEfiComponentNameProtocolGuid,  EFI_COMPONENT_NAME_PROTOCOL_GUID);

// Forward declaration
typedef	struct _EFI_COMPONENT_NAME_PROTOCOL EFI_COMPONENT_NAME_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_COMPONENT_NAME_GET_DRIVER_NAME) (
	IN EFI_COMPONENT_NAME_PROTOCOL *This,
	IN CHAR8 *Language,
	OUT CHAR16 **DriverName
);

typedef EFI_STATUS (EFIAPI *EFI_COMPONENT_NAME_GET_CONTROLLER_NAME) (
	EFI_COMPONENT_NAME_PROTOCOL *This,
	EFI_HANDLE ControllerHandle,
	EFI_HANDLE ChildHandle OPTIONAL,
	CHAR8 *Language,
	CHAR16 **ControllerName
);

struct _EFI_COMPONENT_NAME_PROTOCOL {
	EFI_COMPONENT_NAME_GET_DRIVER_NAME GetDriverName;
	EFI_COMPONENT_NAME_GET_CONTROLLER_NAME GetControllerName;
	CHAR8 *SupportedLanguages;
};

#if BACKWARD_COMPATIBLE_MODE
#include <Protocol/ComponentName2.h>
#else
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID
#if EFI_SPECIFICATION_VERSION<=0x20000
#define EFI_COMPONENT_NAME2_PROTOCOL_GUID \
	{0x107a772c,0xd5e1,0x11d4,0x9a,0x46,0x0,0x90,0x27,0x3f,0xc1,0x4d}
#else //if EFI_SPECIFICATION_VERSION
#define EFI_COMPONENT_NAME2_PROTOCOL_GUID \
    { 0x6a7a5cff, 0xe8d9, 0x4f70, 0xba, 0xda, 0x75, 0xab, 0x30, 0x25, 0xce, 0x14 }
#endif //if EFI_SPECIFICATION_VERSION
#endif // EFI_COMPONENT_NAME2_PROTOCOL_GUID
#endif //if BACKWARD_COMPATIBLE_MODE

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