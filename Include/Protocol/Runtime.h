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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Runtime.h 4     10/07/06 10:18a Felixp $
//
// $Revision: 4 $
//
// $Date: 10/07/06 10:18a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/Runtime.h $
// 
// 4     10/07/06 10:18a Felixp
// Updated to a new Runtime protocol defined by DXE CIS 0.91
// 
// 3     3/13/06 1:45a Felixp
// 
// 2     3/04/05 10:44a Mandal
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
// Name:	Runtime.h
//
// Description:	Runtime Architectural Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __RUNTIME_ARCH_PROTOCOL_H__
#define __RUNTIME_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_RUNTIME_ARCH_PROTOCOL_GUID \
    { 0xb7dfb4e1, 0x52f, 0x449f, 0x87, 0xbe, 0x98, 0x18, 0xfc, 0x91, 0xb7, 0x33 }

GUID_VARIABLE_DECLARATION(gEfiRuntimeArchProtocolGuid, EFI_RUNTIME_ARCH_PROTOCOL_GUID);

#ifndef EFI_LIST_ENTRY_DEFINED
#define EFI_LIST_ENTRY_DEFINED
typedef struct _EFI_LIST_ENTRY {
    struct _EFI_LIST_ENTRY *ForwardLink;
    struct _EFI_LIST_ENTRY *BackLink;
} EFI_LIST_ENTRY;
#endif

typedef struct _EFI_RUNTIME_IMAGE_ENTRY {
    VOID *ImageBase;
    UINT64 ImageSize;
    VOID *RelocationData;
    EFI_HANDLE Handle;
    EFI_LIST_ENTRY Link;
} EFI_RUNTIME_IMAGE_ENTRY;

typedef struct _EFI_RUNTIME_EVENT_ENTRY {
    UINT32 Type;
    EFI_TPL NotifyTpl;
    EFI_EVENT_NOTIFY NotifyFunction;
    VOID *NotifyContext;
    EFI_EVENT *Event;
    EFI_LIST_ENTRY Link;
} EFI_RUNTIME_EVENT_ENTRY;

// Interface stucture for the Runtime Architectural Protocol
typedef struct _EFI_RUNTIME_ARCH_PROTOCOL {
    EFI_LIST_ENTRY ImageHead;
    EFI_LIST_ENTRY EventHead;
    UINTN MemoryDescriptorSize;
    UINT32 MemoryDesciptorVersion;
    UINTN MemoryMapSize;
    EFI_MEMORY_DESCRIPTOR *MemoryMapPhysical;
    EFI_MEMORY_DESCRIPTOR *MemoryMapVirtual;
    BOOLEAN VirtualMode;
    BOOLEAN AtRuntime;
} EFI_RUNTIME_ARCH_PROTOCOL;
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
