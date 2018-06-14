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

/** SmmPiSmst.c - Protocol functions are modified verision from Intel's SMM source.
 
  Copyright (c) 2009, Intel Corporation
  All rights reserved. This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmPiSmst.c 6     3/31/11 6:52p Markw $
//
// $Revision: 6 $
//
// $Date: 3/31/11 6:52p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SMMDispatcher/SmmPiSmst.c $
// 
// 6     3/31/11 6:52p Markw
// Add back revisions 2 to 4.
// 
// 5     3/31/11 6:45p Markw
// [TAG]  		EIP57440
// [Category]  	New Feature
// [Description]  	Add PI 1.1 SMM support for reading/writing floating
// point/smm save state.
// 
// [Files]  		CpuCspLib.h, CpuCspLib.c, SmmPiSmst.c
// 
// 4     3/15/11 2:35p Markw
// Copyright header update.
// 
// 3     3/14/11 3:19p Markw
// Update for EIP 53481.
// Rename gSmmFirmwareVender to gSmmFirmwareVendor.
// For gSmmFirmwareVendor use CONVERT_TO_WSTRING(CORE_VENDOR); instead of
// AMI.
// 
// 2     3/08/11 2:00p Markw
// Update headers and spacing.
// 
// 1     2/07/11 3:28p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name: SmmPiSmst.c
//
// Description:	PI Smst functions.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

//This include should come first.
//#include "SmmPi.h"
#include "SmmPrivateShared.h"
#include <AmiDxeLib.h>
#include <Protocol\SmmCpu.h>
#if SMM_USE_PI
#include "SmmDispatcher.h"
#include <AmiLib.h>
#include <AmiCspLib.h>
#endif

CHAR16 gSmmFirmwareVendor[] = CONVERT_TO_WSTRING(CORE_VENDOR);

extern UINT8 **gSmmBase;

//TODOx64: move it to a library header
VOID CPULib_Pause();

VOID *Allocate(VOID *Base, UINTN Size,UINTN Alignment);

EFI_STATUS AllocateABSegPages(
    IN EFI_ALLOCATE_TYPE        Type,
    IN UINTN                    NumberOfPages,
    IN OUT EFI_PHYSICAL_ADDRESS *Memory
);
EFI_STATUS FreeABSegPages(
    IN EFI_PHYSICAL_ADDRESS Memory,
    IN UINTN                NumberOfPages
);

BOOLEAN Free(VOID *Buffer);
BOOLEAN Free4kPages(VOID *StartAddress,UINTN Pages);

EFI_STATUS InterruptManage(
    IN CONST EFI_GUID *HandlerType,
    IN CONST VOID *Context OPTIONAL,
    IN OUT VOID *CommBuffer OPTIONAL,
    IN OUT UINTN *CommBufferSize OPTIONAL
);

VOID UpdateFrameworkSmmConfigTable(IN EFI_CONFIGURATION_TABLE *SmmConfigurationTable, IN UINTN NumberOfTableEntries);

UINT8* Align2n(UINT8 *Value,UINTN Alignment);

#if SMM_USE_FRAMEWORK
extern EFI_SMM_SYSTEM_TABLE             gSmmSystemTable;
#endif
#if SMM_USE_PI
extern EFI_SMM_SYSTEM_TABLE2            gSmmSystemTable2;
extern EFI_SMM_ENTRY_CONTEXT            gEfiSmmEntryContext;  //For now, hardcode.
#endif
extern SMM_DISPATCHER_PRIVATE_STRUCT   *gDispatcherPrivate;

#if SMM_USE_PI
EFI_STATUS SmmMemRead(
    IN CONST EFI_SMM_CPU_IO2_PROTOCOL *This,
    IN EFI_SMM_IO_WIDTH         Width,
    IN UINT64                   Address,
    IN UINTN                    Count,
    IN OUT VOID                 *Buffer
);

EFI_STATUS SmmMemWrite(
    IN CONST EFI_SMM_CPU_IO2_PROTOCOL *This,
    IN EFI_SMM_IO_WIDTH         Width,
    IN UINT64                   Address,
    IN UINTN                    Count,
    IN OUT VOID                 *Buffer
);

EFI_STATUS SmmIoRead(
    IN CONST EFI_SMM_CPU_IO2_PROTOCOL *This,
    IN EFI_SMM_IO_WIDTH         Width,
    IN UINT64                   Address,
    IN UINTN                    Count,
    IN OUT VOID                 *Buffer
);

EFI_STATUS SmmIoWrite(
    IN CONST EFI_SMM_CPU_IO2_PROTOCOL *This,
    IN EFI_SMM_IO_WIDTH         Width,
    IN UINT64                   Address,
    IN UINTN                    Count,
    IN OUT VOID                 *Buffer
);

EFI_STATUS SmmSmstAllocatePages(
    IN EFI_ALLOCATE_TYPE        Type,
    IN EFI_MEMORY_TYPE          MemoryType,
    IN UINTN                    NumberOfPages,
    IN OUT EFI_PHYSICAL_ADDRESS *Memory
);

EFI_STATUS SmmSmstFreePages(
    IN EFI_PHYSICAL_ADDRESS Memory,
    IN UINTN NumberOfPages
);

EFI_STATUS SmmStartupThisAp(
    IN EFI_AP_PROCEDURE         Procedure,
    IN UINTN                    CpuNumber,
    IN OUT VOID                 *ProcArguments  OPTIONAL
);

#endif

EFI_STATUS SmmSmstAllocatePool(
    IN EFI_MEMORY_TYPE  PoolType,
    IN UINTN            Size,
    OUT VOID            **Buffer
);

EFI_STATUS SmmSmstFreePool(
    IN VOID *Buffer
);

EFI_STATUS CalculateCrc32(
     IN VOID *Data, IN UINTN DataSize, OUT UINT32 *Crc32
);

#if SMM_USE_PI

EFI_STATUS SmmInstallConfigurationTable(
    IN EFI_SMM_SYSTEM_TABLE2 *SystemTable,
    IN EFI_GUID             *Guid,
    IN VOID                 *Table,
    IN UINTN                TableSize
    );

EFI_STATUS ReadSaveState(
    IN CONST EFI_SMM_CPU_PROTOCOL   *This,
    IN UINTN                        Width,
    IN EFI_SMM_SAVE_STATE_REGISTER  Register,
    IN UINTN                        CpuIndex,
    OUT VOID                        *Buffer
)
{
    UINT8 *SmmBase;
#if SMM_USE_FRAMEWORK
    UINT8 *SstSaveState;
#endif

    if (CpuIndex >= gDispatcherPrivate->NumCpus) return EFI_INVALID_PARAMETER;

    SmmBase = gSmmBase[CpuIndex];
#if SMM_USE_FRAMEWORK
    SstSaveState = (UINT8*)&gSmmSystemTable.CpuSaveState[CpuIndex];
#endif

    if (Register >= EFI_SMM_SAVE_STATE_REGISTER_FCW && Register <= EFI_SMM_SAVE_STATE_REGISTER_XMM15) {
        return CpuLib_SmmReadSaveStateFxSave(
                gDispatcherPrivate->SmmXmmSave[CpuIndex],
                (UINT8)Width,
                Register,
                (VOID*)Buffer
                );
    }

    return CPULib_SmmReadSaveState(
        SmmBase, 
#if SMM_USE_FRAMEWORK
        SstSaveState,
        TRUE,
#else
        NULL,
        FALSE,
#endif
        (UINT8)Width,
        Register,
        Buffer
    );
}

EFI_STATUS WriteSaveState(
    IN CONST EFI_SMM_CPU_PROTOCOL   *This,
    IN UINTN                        Width,
    IN EFI_SMM_SAVE_STATE_REGISTER  Register,
    IN UINTN                        CpuIndex,
    IN CONST VOID                   *Buffer
)
{
    UINT8 *SmmBase;
#if SMM_USE_FRAMEWORK
    UINT8 *SstSaveState;
#endif

    if (CpuIndex >= gDispatcherPrivate->NumCpus) return EFI_INVALID_PARAMETER;

    SmmBase = gSmmBase[CpuIndex];
#if SMM_USE_FRAMEWORK
    SstSaveState = (UINT8*)&gSmmSystemTable.CpuSaveState[CpuIndex];
#endif

    if (Register >= EFI_SMM_SAVE_STATE_REGISTER_FCW && Register <= EFI_SMM_SAVE_STATE_REGISTER_XMM15) {
        return CpuLib_SmmWriteSaveStateFxSave(
                gDispatcherPrivate->SmmXmmSave[CpuIndex],
                (UINT8)Width,
                Register,
                (VOID*)Buffer
                );
    }

    return CPULib_SmmWriteSaveState(
        SmmBase, 
#if SMM_USE_FRAMEWORK
        SstSaveState,
        TRUE,
#else
        NULL,
        FALSE,
#endif
        (UINT8)Width,
        Register,
        Buffer
    );
}

EFI_SMM_CPU_PROTOCOL gEfiSmmCpuProtocol = {
    ReadSaveState,
    WriteSaveState
};


static EFI_LIST_ENTRY  SmmProtocolDatabase  = INITIALIZE_LIST_HEAD_VARIABLE (SmmProtocolDatabase);
EFI_LIST_ENTRY  SmmHandleList        = INITIALIZE_LIST_HEAD_VARIABLE (SmmHandleList);
UINTN mEfiLocateHandleRequest = 0; // Added for SmmSmstLocateProtocol

EFI_LIST_ENTRY  mRootSmiHandlerList = INITIALIZE_LIST_HEAD_VARIABLE (mRootSmiHandlerList);
EFI_LIST_ENTRY  mSmiEntryList       = INITIALIZE_LIST_HEAD_VARIABLE (mSmiEntryList);

SMM_IHANDLE *SmmGetNextLocateByRegisterNotify(
    IN OUT SMM_LOCATE_POSITION  *Position,
    OUT    VOID             **Interface
);


SMM_IHANDLE *SmmGetNextLocateByProtocol (
    IN OUT SMM_LOCATE_POSITION  *Position,
    OUT    VOID             **Interface
);

SMM_IHANDLE *SmmGetNextLocateAllHandles (
    IN OUT SMM_LOCATE_POSITION  *Position,
    OUT    VOID             **Interface
);

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmValidateHandle
//
// Description: Check whether a handle is a valid EFI_HANDLE.
//
// Input: 
//  IN  EFI_HANDLE  UserHandle

// Output:
//  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SmmValidateHandle (
        IN EFI_HANDLE  UserHandle
)
{
    SMM_IHANDLE  *Handle;
    Handle = (SMM_IHANDLE *)UserHandle;
    if (Handle == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    if (Handle->Signature != SMM_EFI_HANDLE_SIGNATURE) {
        return EFI_INVALID_PARAMETER;
    }
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmFindProtocolEntry
//
// Description: Finds the protocol entry for the requested protocol.
//
// Input: 
//  IN EFI_GUID   *Protocol
//  IN BOOLEAN    Create
//
// Output:
//  Protocol entry
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
SMM_PROTOCOL_ENTRY  *
SmmFindProtocolEntry (
  IN EFI_GUID   *Protocol,
  IN BOOLEAN    Create
  )
{
    EFI_LIST_ENTRY          *Link;
    SMM_PROTOCOL_ENTRY      *Item;
    SMM_PROTOCOL_ENTRY      *ProtEntry;
    EFI_STATUS Status;
    //
    // Search the database for the matching GUID
    //

    ProtEntry = NULL;
    for (Link = SmmProtocolDatabase.ForwardLink;
        Link != &SmmProtocolDatabase;
        Link = Link->ForwardLink
    ) {
        Item = CR(Link, SMM_PROTOCOL_ENTRY, AllEntries, SMM_PROTOCOL_ENTRY_SIGNATURE);
        if ( !guidcmp (&Item->ProtocolID, Protocol)) {
            //
            // This is the protocol entry
            //
            ProtEntry = Item;
            break;
        }
    }

    //
    // If the protocol entry was not found and Create is TRUE, then
    // allocate a new entry
    //
    if ((ProtEntry == NULL) && Create) {
        Status = SmmSmstAllocatePool(0,sizeof(SMM_PROTOCOL_ENTRY),&ProtEntry); // ********** Probe whether it works? Typecast to VOID** to make it go thro SmmPiAllocatePool.
        if (ProtEntry != NULL) {
            //
            // Initialize new protocol entry structure
            //
            ProtEntry->Signature = SMM_PROTOCOL_ENTRY_SIGNATURE;
            ProtEntry->ProtocolID = *Protocol; // This done as Core Handle.C function implementation.
            InitializeListHead (&ProtEntry->Protocols);
            InitializeListHead (&ProtEntry->Notify);

            //
            // Add it to protocol database
            //
            InsertTailList (&SmmProtocolDatabase, &ProtEntry->AllEntries);
        }
    }
    return ProtEntry;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmFindProtocolInterface
//
// Description:
//  Finds the protocol instance for the requested handle and protocol.
//  Note: This function doesn't do parameters checking, it's caller's responsibility
//  to pass in valid parameters.
//
// Input: 
//  IN SMM_IHANDLE  *Handle,
//  IN EFI_GUID     *Protocol
//  IN VOID         *Interface
//
// Output:
//  Protocol instance (NULL: Not found)
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

SMM_PROTOCOL_INTERFACE * SmmFindProtocolInterface (
    IN SMM_IHANDLE  *Handle,
    IN EFI_GUID     *Protocol,
    IN VOID         *Interface
    )
{
    SMM_PROTOCOL_INTERFACE  *Prot;
    SMM_PROTOCOL_ENTRY      *ProtEntry;
    EFI_LIST_ENTRY          *Link;

    Prot = NULL;

    //
    // Lookup the protocol entry for this protocol ID
    //
    ProtEntry = SmmFindProtocolEntry (Protocol, FALSE);
    if (ProtEntry != NULL) {
        //
        // Look at each protocol interface for any matches
        //
        for (Link = Handle->Protocols.ForwardLink; Link != &Handle->Protocols; Link=Link->ForwardLink) {
            //
            // If this protocol interface matches, remove it
            //
            Prot = CR(Link, SMM_PROTOCOL_INTERFACE, Link, SMM_PROTOCOL_INTERFACE_SIGNATURE);
            if (Prot->Interface == Interface && Prot->Protocol == ProtEntry) {
                break;
            }
            Prot = NULL;
        }
    }
    return Prot;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmNotifyProtocol
//
// Description: Signal event for every protocol in protocol entry.
//
// Input: 
//	IN SMM_PROTOCOL_INTERFACE  *Prot

// Output:
//	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmNotifyProtocol (
  IN SMM_PROTOCOL_INTERFACE  *Prot
  )
{
    SMM_PROTOCOL_ENTRY   *ProtEntry;
    SMM_PROTOCOL_NOTIFY  *ProtNotify;
    EFI_LIST_ENTRY       *Link;

    ProtEntry = Prot->Protocol;
    for (Link=ProtEntry->Notify.ForwardLink; Link != &ProtEntry->Notify; Link=Link->ForwardLink) {
        ProtNotify = CR(Link, SMM_PROTOCOL_NOTIFY, Link, SMM_PROTOCOL_NOTIFY_SIGNATURE);
        ProtNotify->Function (&ProtEntry->ProtocolID, Prot->Interface, Prot->Handle);
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstInstallProtocolInterface
//
//  Description:
//  Wrapper function to SmmInstallProtocolInterfaceNotify.  This is the public API which
//  Calls the private one which contains a BOOLEAN parameter for notifications
//
// Input: 
//  IN OUT EFI_HANDLE       *Handle
//  IN EFI_GUID             *Protocol
//  IN EFI_INTERFACE_TYPE   InterfaceType
//  IN VOID                 Interface
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstInstallProtocolInterface (
    IN OUT EFI_HANDLE       *UserHandle,
    IN EFI_GUID             *Protocol,
    IN EFI_INTERFACE_TYPE   InterfaceType,
    IN VOID                 *Interface
)
{
    return SmmSmstInstallProtocolInterfaceNotify (
           UserHandle,
           Protocol,
           InterfaceType,
           Interface,
           TRUE
           );
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstInstallProtocolInterfaceNotify
//
// Description: Installs a protocol interface into the boot services environment.

// Input: 
//  IN OUT EFI_HANDLE          *UserHandle,
//  IN     EFI_GUID            *Protocol,
//  IN     EFI_INTERFACE_TYPE  InterfaceType,
//  IN     VOID                *Interface,
//  IN     BOOLEAN             Notify
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SmmSmstInstallProtocolInterfaceNotify (
    IN OUT EFI_HANDLE          *UserHandle,
    IN     EFI_GUID            *Protocol,
    IN     EFI_INTERFACE_TYPE  InterfaceType,
    IN     VOID                *Interface,
    IN     BOOLEAN             Notify
)
{
    SMM_PROTOCOL_INTERFACE  *Prot;
    SMM_PROTOCOL_ENTRY      *ProtEntry;
    SMM_IHANDLE             *Handle;
    EFI_STATUS              Status;
    VOID                    *ExistingInterface;

    //
    // returns EFI_INVALID_PARAMETER if InterfaceType is invalid.
    // Also added check for invalid UserHandle and Protocol pointers.
    //

    if (UserHandle == NULL || Protocol == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (InterfaceType != EFI_NATIVE_INTERFACE) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Print debug message
    //
    //DEBUG((DEBUG_LOAD | DEBUG_INFO, "SmmInstallProtocolInterface: %g %p\n", Protocol, Interface));

    Status = EFI_OUT_OF_RESOURCES;

    Prot = NULL;
    Handle = NULL;

    if (*UserHandle != NULL) {
        Status = SmmSmstHandleProtocol(*UserHandle, Protocol, (VOID **)&ExistingInterface);

        if (!EFI_ERROR (Status)) {
            return EFI_INVALID_PARAMETER;
        }
    }

    //
    // Lookup the Protocol Entry for the requested protocol
    //
    ProtEntry = SmmFindProtocolEntry (Protocol, TRUE);

    if (ProtEntry == NULL) {
        goto Done;
    }

    //
    // Allocate a new protocol interface structure
    //
    Status = SmmSmstAllocatePool(0,sizeof(SMM_PROTOCOL_INTERFACE),&Prot);
    MemSet(Prot,(Prot == NULL) ? 0 : sizeof(SMM_PROTOCOL_INTERFACE), 0);

    if (Prot == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Done;
    }

    //
    // If caller didn't supply a handle, allocate a new one
    //
    Handle = (SMM_IHANDLE *)*UserHandle;
    if (Handle == NULL) {
        Status = SmmSmstAllocatePool(0,sizeof(SMM_IHANDLE),&Handle);
        MemSet(Handle,(Handle == NULL) ? 0 : sizeof(SMM_IHANDLE), 0);
        if (Handle == NULL) {
            Status = EFI_OUT_OF_RESOURCES;
            goto Done;
        }

        //
        // Initialize new handler structure
        //
        Handle->Signature = SMM_EFI_HANDLE_SIGNATURE;
        InitializeListHead (&Handle->Protocols);

        //
        // Add this handle to the list global list of all handles
        // in the system
        //
        InsertTailList (&SmmHandleList, &Handle->AllHandles);
    }

    Status = SmmValidateHandle (Handle);

    if (EFI_ERROR (Status)) {
        goto Done;
    }

    //
    // Each interface that is added must be unique
    //
    ASSERT (SmmFindProtocolInterface (Handle, Protocol, Interface) == NULL);

    //
    // Initialize the protocol interface structure
    //
    Prot->Signature = SMM_PROTOCOL_INTERFACE_SIGNATURE;
    Prot->Handle = Handle;
    Prot->Protocol = ProtEntry;
    Prot->Interface = Interface;

    //
    // Add this protocol interface to the head of the supported
    // protocol list for this handle
    //
    InsertHeadList (&Handle->Protocols, &Prot->Link);

    //
    // Add this protocol interface to the tail of the
    // protocol entry
    //
    InsertTailList (&ProtEntry->Protocols, &Prot->ByProtocol);

    //
    // Notify the notification list for this protocol
    //
    if (Notify) {
        SmmNotifyProtocol (Prot);
    }
    Status = EFI_SUCCESS;

Done:
    if (!EFI_ERROR (Status)) {
        //
        // Return the new handle back to the caller
        //
        *UserHandle = Handle;
    } else {
        //
        // There was an error, clean up
        //
        if (Prot != NULL) {
            SmmSmstFreePool (Prot);
        }
    }
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstUninstallProtocolInterface
//
// Description:
//  Uninstalls all instances of a protocol:interfacer from a handle.
//  If the last protocol interface is remove from the handle, the
//  handle is freed.
//
// Input: 
//  IN OUT EFI_HANDLE   UserHandle
//  IN EFI_GUID         *Protocol
//  IN VOID             *Interface
//
//  Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstUninstallProtocolInterface (
    IN OUT EFI_HANDLE   UserHandle,
    IN EFI_GUID         *Protocol,
    IN VOID             *Interface
)
{
    EFI_STATUS              Status;
    SMM_IHANDLE             *Handle;
    SMM_PROTOCOL_INTERFACE  *Prot;

    //
    // Check that Protocol is valid
    //
    if (Protocol == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Check that UserHandle is a valid handle
    //
    Status = SmmValidateHandle (UserHandle);

    if (EFI_ERROR (Status)) {
        return Status;
    }

    //
    // Check that Protocol exists on UserHandle, and Interface matches the interface in the database
    //
    Prot = SmmFindProtocolInterface (UserHandle, Protocol, Interface);

    if (Prot == NULL) {
        return EFI_NOT_FOUND;
    }

    //
    // Remove the protocol interface from the protocol
    //
    Status = EFI_NOT_FOUND;
    Handle = (SMM_IHANDLE *)UserHandle;

    Prot   = SmmRemoveInterfaceFromProtocol (Handle, Protocol, Interface);

    if (Prot != NULL) {
        //
        // Remove the protocol interface from the handle
        //
        RemoveEntryList (&Prot->Link);

        //
        // Free the memory
        //
        Prot->Signature = 0;
        SmmSmstFreePool(Prot);
        Status = EFI_SUCCESS;
    }

    //
    // If there are no more handlers for the handle, free the handle
    //
    if (IsListEmpty (&Handle->Protocols)) {
        Handle->Signature = 0;
        RemoveEntryList (&Handle->AllHandles);
        SmmSmstFreePool (Handle);
    }
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmRemoveInterfaceFromProtocol
//
// Description: Removes Protocol from the protocol list (but not the handle list).
//
// Input: 
//  IN SMM_IHANDLE  *Handle,
//  IN EFI_GUID     *Protocol
//  IN VOID         *Interface
//
// Output: Protocol Entry
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

SMM_PROTOCOL_INTERFACE * SmmRemoveInterfaceFromProtocol (
    IN SMM_IHANDLE  *Handle,
    IN EFI_GUID     *Protocol,
    IN VOID         *Interface
)
{
    SMM_PROTOCOL_INTERFACE  *Prot;
    SMM_PROTOCOL_NOTIFY     *ProtNotify;
    SMM_PROTOCOL_ENTRY      *ProtEntry;
    EFI_LIST_ENTRY          *Link;

    Prot = SmmFindProtocolInterface (Handle, Protocol, Interface);
    if (Prot != NULL) {
        ProtEntry = Prot->Protocol;

        //
        // If there's a protocol notify location pointing to this entry, back it up one
        //
        for(Link = ProtEntry->Notify.ForwardLink; Link != &ProtEntry->Notify; Link=Link->ForwardLink) {
            ProtNotify = CR(Link, SMM_PROTOCOL_NOTIFY, Link, SMM_PROTOCOL_NOTIFY_SIGNATURE);

            if (ProtNotify->Position == &Prot->ByProtocol) {
                ProtNotify->Position = Prot->ByProtocol.BackLink;
            }
        }

        //
        // Remove the protocol interface entry
        //
        RemoveEntryList (&Prot->ByProtocol);
    }

    return Prot;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmGetProtocolInterface
//
// Description: Locate a certain GUID protocol interface in a Handle's protocols.
//
// Input: 
//  IN EFI_HANDLE  UserHandle,
//  IN EFI_GUID    *Protocol
//
// Output:
//	The requested protocol interface for the handle.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

SMM_PROTOCOL_INTERFACE  * SmmGetProtocolInterface (
    IN EFI_HANDLE  UserHandle,
    IN EFI_GUID    *Protocol
)
{
    EFI_STATUS              Status;
    SMM_PROTOCOL_ENTRY      *ProtEntry;
    SMM_PROTOCOL_INTERFACE  *Prot;
    SMM_IHANDLE             *Handle;
    EFI_LIST_ENTRY          *Link;

    Status = SmmValidateHandle (UserHandle);
    if (EFI_ERROR (Status)) {
        return NULL;
    }

    Handle = (SMM_IHANDLE *)UserHandle;

    //
    // Look at each protocol interface for a match
    //
    for (Link = Handle->Protocols.ForwardLink; Link != &Handle->Protocols; Link = Link->ForwardLink) {
        Prot = CR(Link, SMM_PROTOCOL_INTERFACE, Link, SMM_PROTOCOL_INTERFACE_SIGNATURE);
        ProtEntry = Prot->Protocol;
        if (!guidcmp(&ProtEntry->ProtocolID, Protocol)) {
            return Prot;
        }
    }
    return NULL;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstHandleProtocol
//
// Description: Queries a handle to determine if it supports a specified protocol.
//
// Input: 
//  IN OUT EFI_HANDLE  UserHandle
//  IN     EFI_GUID    *Protocol
//  OUT    VOID        **Interface
//
// Output:
//  EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstHandleProtocol (
    IN OUT EFI_HANDLE  UserHandle,
    IN     EFI_GUID    *Protocol,
    OUT    VOID        **Interface
)
{
    EFI_STATUS              Status;
    SMM_PROTOCOL_INTERFACE  *Prot;

    //
    // Check for invalid Protocol
    //
    if (Protocol == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Check for invalid Interface
    //
    if (Interface == NULL) {
        return EFI_INVALID_PARAMETER;
    } else {
        *Interface = NULL;
    }

    //
    // Check for invalid UserHandle
    //
    Status = SmmValidateHandle (UserHandle);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    //
    // Look at each protocol interface for a match
    //
    Prot = SmmGetProtocolInterface (UserHandle, Protocol);
    if (Prot == NULL) {
        return EFI_UNSUPPORTED;
    }

    //
    // This is the protocol interface entry for this protocol
    //
    *Interface = Prot->Interface;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstRegisterProtocolNotify
//
// Description: Add a new protocol notification record for the request protocol.
//
// Input: 
//  IN EFI_GUID                  *Protocol
//  IN EFI_SMM_NOTIFY_FN         Function
//  OUT VOID                     **Registration
//
// Output:
//  EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstRegisterProtocolNotify (
    IN CONST EFI_GUID     *Protocol,
    IN EFI_SMM_NOTIFY_FN  Function,
    OUT VOID              **Registration)
{
    SMM_PROTOCOL_ENTRY    *ProtEntry=NULL;
    SMM_PROTOCOL_NOTIFY   *ProtNotify=NULL;
    EFI_LIST_ENTRY        *Link;
//  EFI_GUID              *protocol=(EFI_GUID*)Protocol;
    EFI_STATUS            Status;

    if ((Protocol == NULL) || (Function == NULL) || (Registration == NULL))  {
        return EFI_INVALID_PARAMETER;
    }

    ProtNotify = NULL;

    //
    // Get the protocol entry to add the notification too
    //
    ProtEntry = SmmFindProtocolEntry ((EFI_GUID *) Protocol, TRUE);
    if (ProtEntry != NULL) {
        //
        // Find whether notification already exist
        //
        for (Link = ProtEntry->Notify.ForwardLink;
            Link != &ProtEntry->Notify;
            Link = Link->ForwardLink) {

            ProtNotify = CR(Link, SMM_PROTOCOL_NOTIFY, Link, SMM_PROTOCOL_NOTIFY_SIGNATURE);
            if ((!guidcmp(&ProtNotify->Protocol->ProtocolID, (EFI_GUID*)Protocol)) &&
                    (ProtNotify->Function == Function)
            ) {

                //
                // Notification already exist
                //
                *Registration = ProtNotify;

                return EFI_SUCCESS;
            }
        }

        //
        // Allocate a new notification record
        //
        Status = SmmSmstAllocatePool(0,sizeof(SMM_PROTOCOL_NOTIFY),&ProtNotify);
        ASSERT_EFI_ERROR(Status);
        if (ProtNotify != NULL) {
            ProtNotify->Signature = SMM_PROTOCOL_NOTIFY_SIGNATURE;
            ProtNotify->Protocol = ProtEntry;
            ProtNotify->Function = Function;
            //
            // Start at the ending
            //
            ProtNotify->Position = ProtEntry->Protocols.BackLink;

            InsertTailList (&ProtEntry->Notify, &ProtNotify->Link);
        }
    }

    //
    // Done.  If we have a protocol notify entry, then return it.
    // Otherwise, we must have run out of resources trying to add one
    //
    Status = EFI_OUT_OF_RESOURCES;
    if (ProtNotify != NULL) {
        *Registration = ProtNotify;
        Status = EFI_SUCCESS;
    }
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstLocateHandle
//
// Description: Locates the requested handle(s) and returns them in Buffer.
//
// Input: 
//  IN EFI_LOCATE_SEARCH_TYPE   SearchType
//  IN EFI_GUID                 *Protocol OPTIONAL
//  IN VOID                     *SearchKey OPTIONAL
//  IN OUT UINTN                *BufferSize
//  OUT EFI_HANDLE              *Buffer
//
// Output:
//  EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmmSmstLocateHandle (
    IN     EFI_LOCATE_SEARCH_TYPE  SearchType,
    IN     EFI_GUID *Protocol      OPTIONAL,
    IN     VOID *SearchKey         OPTIONAL,
    IN OUT UINTN                   *BufferSize,
    OUT    EFI_HANDLE              *Buffer
)

{
    EFI_STATUS          Status;
    SMM_LOCATE_POSITION Position;
    SMM_PROTOCOL_NOTIFY *ProtNotify;
    SMM_CORE_GET_NEXT   GetNext;
    UINTN               ResultSize;
    SMM_IHANDLE         *Handle;
    SMM_IHANDLE         **ResultBuffer;
    VOID                *Interface;

    if (BufferSize == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if ((*BufferSize > 0) && (Buffer == NULL)) {
        return EFI_INVALID_PARAMETER;
    }

    GetNext = NULL;

    //
    // Set initial position
    //
    Position.Protocol  = Protocol;
    Position.SearchKey = SearchKey;
    Position.Position  = &SmmHandleList;

    ResultSize = 0;
    ResultBuffer = (SMM_IHANDLE **) Buffer;
    Status = EFI_SUCCESS;

    //
    // Get the search function based on type
    //
    switch (SearchType) {
    case AllHandles:
        GetNext = SmmGetNextLocateAllHandles;
        break;

    case ByRegisterNotify:
        GetNext = SmmGetNextLocateByRegisterNotify;
        //
        // Must have SearchKey for locate ByRegisterNotify
        //
        if (SearchKey == NULL) {
            Status = EFI_INVALID_PARAMETER;
        }
        break;
    case ByProtocol:
        GetNext = SmmGetNextLocateByProtocol;
        if (Protocol == NULL) {
            Status = EFI_INVALID_PARAMETER;
            break;
        }
        //
        // Look up the protocol entry and set the head pointer
        //
        Position.ProtEntry = SmmFindProtocolEntry (Protocol, FALSE);
        if (Position.ProtEntry == NULL) {
            Status = EFI_NOT_FOUND;
            break;
        }
        Position.Position = &Position.ProtEntry->Protocols;
        break;
    default:
    Status = EFI_INVALID_PARAMETER;
    break;
    }

    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Enumerate out the matching handles
    //
    mEfiLocateHandleRequest += 1;
    for (; ;) {
        //
        // Get the next handle.  If no more handles, stop
        //
        Handle = GetNext (&Position, &Interface);
        if (NULL == Handle) {
            break;
        }

        //
        // Increase the resulting buffer size, and if this handle
        // fits return it
        //
        ResultSize += sizeof(Handle);
        if (ResultSize <= *BufferSize) {
            *ResultBuffer = Handle;
            ResultBuffer += 1;
        }
    }

    //
    // If the result is a zero length buffer, then there were no
    // matching handles
    //
    if (ResultSize == 0) {
        Status = EFI_NOT_FOUND;
    } else {
        //
        // Return the resulting buffer size.  If it's larger than what
        // was passed, then set the error code
        //
        if (ResultSize > *BufferSize) {
            Status = EFI_BUFFER_TOO_SMALL;
        }

        *BufferSize = ResultSize;

        if (SearchType == ByRegisterNotify && !EFI_ERROR(Status)) {
            ASSERT (SearchKey != NULL);
            //
            // If this is a search by register notify and a handle was
            // returned, update the register notification position
            //
            ProtNotify = SearchKey;
            ProtNotify->Position = ProtNotify->Position->ForwardLink;
        }
    }
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmSmstLocateProtocol
//
// Description:
//  Return the first Protocol Interface that matches the Protocol GUID. If
//  Registration is passed in, return a Protocol Instance that was just add
//  to the system. If Registration is NULL return the first Protocol Interface
//  you find.
//
// Input: 
//  IN  EFI_GUID    *Protocol,
//  IN  VOID        *Registration OPTIONAL
//  OUT VOID        **Interface
//
// Output:
//  EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSmstLocateProtocol (
    IN EFI_GUID *Protocol,
    IN VOID     *Registration OPTIONAL,
    OUT VOID    **Interface
)
{
    EFI_STATUS              Status;
    SMM_LOCATE_POSITION     Position;
    SMM_PROTOCOL_NOTIFY     *ProtNotify;
    SMM_IHANDLE             *Handle;

    if (Interface == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (Protocol == NULL) {
        return EFI_NOT_FOUND;
    }

    *Interface = NULL;
    Status = EFI_SUCCESS;
    //
    // Set initial position
    //
    Position.Protocol  = Protocol;
    Position.SearchKey = Registration;
    Position.Position  = &SmmHandleList;

    mEfiLocateHandleRequest += 1;

    if (Registration == NULL) {
        //
        // Look up the protocol entry and set the head pointer
        //
        Position.ProtEntry = SmmFindProtocolEntry (Protocol, FALSE);
        if (Position.ProtEntry == NULL) {
            return EFI_NOT_FOUND;
        }
        Position.Position = &Position.ProtEntry->Protocols;

        Handle = SmmGetNextLocateByProtocol (&Position, Interface);
    } else {
        Handle = SmmGetNextLocateByRegisterNotify (&Position, Interface);
    }

    if (Handle == NULL) {
        Status = EFI_NOT_FOUND;
    } else if (Registration != NULL) {
        //
        // If this is a search by register notify and a handle was
        // returned, update the register notification position
        //
        ProtNotify = Registration;
        ProtNotify->Position = ProtNotify->Position->ForwardLink;
    }

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmGetNextLocateAllHandles
//
// Description:
//  Find next handle.
//
// Input:
//  IN OUT SMM_LOCATE_POSITION  *Position,
//  OUT    VOID                 **Interface
//
// Output:
//  SMM_IHANDLE
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

SMM_IHANDLE *SmmGetNextLocateAllHandles (
    IN OUT SMM_LOCATE_POSITION  *Position,
    OUT    VOID                 **Interface
)
{
    SMM_IHANDLE     *Handle;

    //
    // Next handle
    //
    Position->Position = Position->Position->ForwardLink;

    //
    // If not at the end of the list, get the handle
    //
    Handle      = NULL;
    *Interface  = NULL;
    if (Position->Position != &SmmHandleList) {
        Handle = CR (Position->Position, SMM_IHANDLE, AllHandles, SMM_EFI_HANDLE_SIGNATURE);
    }
    return Handle;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmGetNextLocateByRegisterNotify
//
// Description: Routine to get the next Handle, when you are searching for register protocol
//  notifies.
//
// Input: 
//  IN OUT SMM_LOCATE_POSITION  *Position
//  OUT    VOID                 **Interface
//
// Output:
//  An pointer to SMM_IHANDLE if the next Position is not the end of the list.
//  Otherwise,NULL is returned.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

SMM_IHANDLE *SmmGetNextLocateByRegisterNotify (
    IN OUT SMM_LOCATE_POSITION  *Position,
    OUT    VOID                 **Interface
)
{
    SMM_IHANDLE             *Handle;
    SMM_PROTOCOL_NOTIFY     *ProtNotify;
    SMM_PROTOCOL_INTERFACE  *Prot;
    EFI_LIST_ENTRY          *Link;

    Handle      = NULL;
    *Interface  = NULL;
    ProtNotify = Position->SearchKey;

    //
    // If this is the first request, get the next handle
    //
    if (ProtNotify != NULL) {
        ASSERT(ProtNotify->Signature == SMM_PROTOCOL_NOTIFY_SIGNATURE);
        Position->SearchKey = NULL;

        //
        // If not at the end of the list, get the next handle
        //
        Link = ProtNotify->Position->ForwardLink;
        if (Link != &ProtNotify->Protocol->Protocols) {
            Prot = CR (Link, SMM_PROTOCOL_INTERFACE, ByProtocol, SMM_PROTOCOL_INTERFACE_SIGNATURE);
            Handle = Prot->Handle;
            *Interface = Prot->Interface;
        }
    }
    return Handle;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmGetNextLocateByProtocol
//
// Description: Routine to get the next Handle, when you are searching for a given protocol.
//
// Input: 
//  IN OUT SMM_LOCATE_POSITION  *Position
//  OUT    VOID                 **Interface
//
// Output:
//  An pointer to SMM_IHANDLE if the next Position is not the end of the list.
//  Otherwise,NULL is returned.
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

SMM_IHANDLE *SmmGetNextLocateByProtocol (
    IN OUT SMM_LOCATE_POSITION  *Position,
    OUT    VOID                 **Interface
)
{
    SMM_IHANDLE             *Handle;
    EFI_LIST_ENTRY          *Link;
    SMM_PROTOCOL_INTERFACE  *Prot;

    Handle      = NULL;
    *Interface  = NULL;

    for (; ;) {
        //
        // Next entry
        //
        Link = Position->Position->ForwardLink;
        Position->Position = Link;

        //
        // If not at the end, return the handle
        //
        if (Link == &Position->ProtEntry->Protocols) {
            Handle = NULL;
            break;
        }

        //
        // Get the handle
        //
        Prot = CR(Link, SMM_PROTOCOL_INTERFACE, ByProtocol, SMM_PROTOCOL_INTERFACE_SIGNATURE);
        Handle = Prot->Handle;
        *Interface = Prot->Interface;

        //
        // If this handle has not been returned this request, then
        // return it now
        //
        if (Handle->LocateRequest != mEfiLocateHandleRequest) {
            Handle->LocateRequest = mEfiLocateHandleRequest;
            break;
        }
    }
    return Handle;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmCoreFindSmiEntry
//
// Description: Find Smi Entry
//
// Input:
//  IN EFI_GUID  *HandlerType
//  IN BOOLEAN   Create
//
// Output: SMM_SMI_ENTRY
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

SMM_SMI_ENTRY* SmmCoreFindSmiEntry (
    IN EFI_GUID  *HandlerType,
    IN BOOLEAN   Create
)
{
    EFI_LIST_ENTRY  *Link;
    SMM_SMI_ENTRY   *Item;
    SMM_SMI_ENTRY   *SmiEntry;
    EFI_STATUS   Status;

    //
    // Search the SMI entry list for the matching GUID
    //
    SmiEntry = NULL;
    for (Link = mSmiEntryList.ForwardLink;
        Link != &mSmiEntryList;
        Link = Link->ForwardLink) {

        Item = CR (Link, SMM_SMI_ENTRY, AllEntries, SMI_ENTRY_SIGNATURE);
        if (!guidcmp(&Item->HandlerType, HandlerType)) {
            //
            // This is the SMI entry
            //
            SmiEntry = Item;
            break;
        }
    }

    //
    // If the protocol entry was not found and Create is TRUE, then
    // allocate a new entry
    //
    if ((SmiEntry == NULL) && Create) {
        Status = SmmSmstAllocatePool (0,sizeof(SMM_SMI_ENTRY),&SmiEntry);
        if (EFI_ERROR(Status) || (SmiEntry != NULL)) {
            //
            // Initialize new SMI entry structure
            //
            SmiEntry->Signature = SMI_ENTRY_SIGNATURE;
            MemCpy((VOID *)&SmiEntry->HandlerType, HandlerType, sizeof(EFI_GUID));
            InitializeListHead (&SmiEntry->SmiHandlers);

            // Add it to SMI entry list
            InsertTailList (&mSmiEntryList, &SmiEntry->AllEntries);
        }
    }
    return SmiEntry;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmiHandlerRegister
//
// Description: Register SMI Handle
//
// Input:
//  IN EFI_SMM_HANDLER_ENTRY_POINT2 Handler,
//  IN CONST EFI_GUID               *HandlerType OPTIONAL,
//  OUT EFI_HANDLE                  *DispatchHandle
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmiHandlerRegister(
    IN EFI_SMM_HANDLER_ENTRY_POINT2 Handler,
    IN CONST EFI_GUID *HandlerType OPTIONAL,
    OUT EFI_HANDLE *DispatchHandle
)
{
    HANDLER_LIST	*HandlerInfo, *Link;

    if (gSmmSystemTable2.SmmAllocatePool(0, sizeof(HANDLER_LIST), &HandlerInfo) != EFI_SUCCESS)
        return EFI_OUT_OF_RESOURCES;

    HandlerInfo->IsPi = TRUE;
    HandlerInfo->EntryPoint     = Handler;
    HandlerInfo->SmmImageHandle = HandlerInfo;
    if (HandlerType) {
        MemCpy(&HandlerInfo->HandlerType, (EFI_GUID*)HandlerType, sizeof(EFI_GUID));
        HandlerInfo->IsRoot = FALSE;
    } else HandlerInfo->IsRoot = TRUE;

    HandlerInfo->Link = 0;

    //If very first add.
    if (!gDispatcherPrivate->HandlerListHead) {
        gDispatcherPrivate->HandlerListHead = HandlerInfo;
        return EFI_SUCCESS;
    }
    
    //Add to end of list.
    for (Link = gDispatcherPrivate->HandlerListHead; Link->Link; Link = Link->Link);	//Find end of list
    Link->Link = HandlerInfo;

    return EFI_SUCCESS;
}

EFI_STATUS SmiHandlerUnRegister(IN EFI_HANDLE DispatchHandle)
{
    HANDLER_LIST *Link = gDispatcherPrivate->HandlerListHead;
    HANDLER_LIST *PrevLink;

    while (Link != 0) {
        if (Link->SmmImageHandle == DispatchHandle) {
            if (Link == gDispatcherPrivate->HandlerListHead) {
                gDispatcherPrivate->HandlerListHead = Link->Link;
            } else {
                PrevLink->Link = Link->Link;
            }
            SmmSmstFreePool(Link);
            return EFI_SUCCESS;
        }
        PrevLink = Link;
        Link = Link->Link;
    }
    return EFI_INVALID_PARAMETER;
}

EFI_SMM_SYSTEM_TABLE2 gSmmSystemTable2 =
{
    {                               //Header
    SMM_SMST_SIGNATURE2,            //Signature
    EFI_SMM_SYSTEM_TABLE_REVISION2, //Revison will show 1.1
    sizeof(EFI_SMM_SYSTEM_TABLE2),   //Header size
    0,                              //CRC32
    0                               //Reserved
    },
    gSmmFirmwareVendor,             //Vendor
    0,								//Vendor version

    SmmInstallConfigurationTable,
    {
        {
        SmmMemRead,
        SmmMemWrite
        },
        {
        SmmIoRead,
        SmmIoWrite
        }
    },
    SmmSmstAllocatePool,
    SmmSmstFreePool,
    SmmSmstAllocatePages,
    SmmSmstFreePages,
    SmmStartupThisAp,
    1,                              //Executing CPU
    1,                              //Number of CPUs
    0,                              //CpuSaveStateSize...PI 1.1
    0,                              //Cpu Save State
    0,                              //Number of Table Entries
    0,                              //Table pointer
    SmmSmstInstallProtocolInterface,
    SmmSmstUninstallProtocolInterface,
    SmmSmstHandleProtocol,
    SmmSmstRegisterProtocolNotify,
    SmmSmstLocateHandle,
    SmmSmstLocateProtocol,
    InterruptManage,
    SmiHandlerRegister,
    SmiHandlerUnRegister
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InsertTailList
//
// Description:
//  Insert a Node into the end of a doubly linked list. The list must have
//  been initialized with InitializeListHead () before using this function.
//
//
// Input:
//  IN EFI_LIST_ENTRY  *ListHead
//  IN EFI_LIST_ENTRY  *Entry
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InsertTailList (
    IN EFI_LIST_ENTRY  *ListHead,
    IN EFI_LIST_ENTRY  *Entry
)
{
    EFI_LIST_ENTRY *_ListHead;
    EFI_LIST_ENTRY *_BackLink;
    
    _ListHead              = ListHead;
    _BackLink              = _ListHead->BackLink;
    Entry->ForwardLink     = _ListHead;
    Entry->BackLink        = _BackLink;
    _BackLink->ForwardLink = Entry;
    _ListHead->BackLink    = Entry;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InsertHeadList
//
// Description:
//  Insert a Node into the start of a doubly linked list. The list must have
//  been initialized with InitializeListHead () before using this function.
//
// Input:
//  IN EFI_LIST_ENTRY  *ListHead
//  IN EFI_LIST_ENTRY  *Entry
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InsertHeadList (
    IN EFI_LIST_ENTRY  *ListHead,
    IN EFI_LIST_ENTRY  *Entry
)
{
    EFI_LIST_ENTRY  *_ListHead;
    EFI_LIST_ENTRY  *_ForwardLink;
    
    _ListHead               = ListHead;
    _ForwardLink            = _ListHead->ForwardLink;
    Entry->ForwardLink      = _ForwardLink;
    Entry->BackLink         = _ListHead;
    _ForwardLink->BackLink  = Entry;
    _ListHead->ForwardLink  = Entry;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitializeListHead
//
// Description:
//  Initialize the head of the List.  The caller must allocate the memory
//   for the EFI_LIST. This function must be called before the other linked
//   list macros can be used.
//
// Input:
//  IN EFI_LIST_ENTRY  *List
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitializeListHead (
    IN EFI_LIST_ENTRY  *List
)
{
    List->ForwardLink = List;
    List->BackLink    = List;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: IsListEmpty
//
// Description:
//  Return TRUE is the list contains zero nodes. Otherwise return FALSE.
//    The list must have been initialized with InitializeListHead () before using
//    this function.
//
// Input:
//  IN EFI_LIST_ENTRY  *List
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsListEmpty (
    IN EFI_LIST_ENTRY  *List
)
{
    return (BOOLEAN)(List->ForwardLink == List);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: RemoveEntryList
//
// Description:
//  Remove Node from the doubly linked list. It is the caller's responsibility
//  to free any memory used by the entry if needed. The list must have been
//  initialized with InitializeListHead () before using this function.
//
// Input:
//  IN EFI_LIST_ENTRY  *Entry
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RemoveEntryList (
    EFI_LIST_ENTRY  *Entry
)
{
    EFI_LIST_ENTRY  *_ForwardLink;
    EFI_LIST_ENTRY  *_BackLink;
    
    _ForwardLink           = Entry->ForwardLink;
    _BackLink              = Entry->BackLink;
    _BackLink->ForwardLink = _ForwardLink;
    _ForwardLink->BackLink = _BackLink;

#if EFI_DEBUG
    Entry->ForwardLink = (EFI_LIST_ENTRY *) 0xAFAFAFAF;
    Entry->BackLink    = (EFI_LIST_ENTRY *) 0xAFAFAFAF;
#endif
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitializeSmmPiSystemTable
//
// Description:
//  Initialize SMM PI System Table.
//
// Input: VOID
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitializeSmmPiSystemTable()
{
	UINT32 CRC32;
    UINT32 NumCpus = gDispatcherPrivate->NumCpus;
    UINT32 i;

    gSmmSystemTable2.NumberOfCpus = NumCpus;

    gSmmSystemTable2.CpuSaveStateSize = Allocate(0,sizeof(UINTN) * NumCpus,0);
    for (i = 0; i < NumCpus; ++i) gSmmSystemTable2.CpuSaveStateSize[i] = MAX_SMM_SAVE_STATE_SIZE;

    gSmmSystemTable2.CpuSaveState = Allocate(0,sizeof(VOID*) * NumCpus,0);
    for (i = 0; i < NumCpus; ++i) {
        gSmmSystemTable2.CpuSaveState[i] = (VOID*)(gSmmBase[i] + 0x10000 - MAX_SMM_SAVE_STATE_SIZE);
    }

    CalculateCrc32(&gSmmSystemTable2, sizeof(EFI_SMM_SYSTEM_TABLE2), &CRC32);
    gSmmSystemTable2.Hdr.CRC32 = CRC32;

    gEfiSmmEntryContext.SmmStartupThisAp = gSmmSystemTable2.SmmStartupThisAp;
    gEfiSmmEntryContext.NumberOfCpus = gSmmSystemTable2.NumberOfCpus;
    gEfiSmmEntryContext.CpuSaveStateSize = gSmmSystemTable2.CpuSaveStateSize;
    gEfiSmmEntryContext.CpuSaveState = gSmmSystemTable2.CpuSaveState;
}
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
