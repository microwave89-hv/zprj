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
// $Header: /Alaska/SOURCE/Core/EDK/GUID/EventGroup.h 2     2/05/11 3:35p Artems $
//
// $Revision: 2 $
//
// $Date: 2/05/11 3:35p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/GUID/EventGroup.h $
// 
// 2     2/05/11 3:35p Artems
// Added variable gEfiEventDxeDispatchGuid 
// 
// 1     10/07/06 10:22a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EventGroup.h
//
// Description:	Declaration of even group GUIDs
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_EVENT_GROUP_GUID__H__
#define __EFI_EVENT_GROUP_GUID__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <DXE.h>

GUID_VARIABLE_DECLARATION(gEfiEventExitBootServicesGuid, EFI_EVENT_GROUP_EXIT_BOOT_SERVICES);

GUID_VARIABLE_DECLARATION(gEfiEventVirtualAddressChangeGuid, EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE);

GUID_VARIABLE_DECLARATION(gEfiEventMemoryMapChangeGuid, EFI_EVENT_GROUP_MEMORY_MAP_CHANGE);

GUID_VARIABLE_DECLARATION(gEfiEventReadyToBootGuid, EFI_EVENT_GROUP_READY_TO_BOOT);

GUID_VARIABLE_DECLARATION(gEfiEventDxeDispatchGuid, EFI_EVENT_GROUP_DXE_DISPATCH);
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