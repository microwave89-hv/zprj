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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmPi.h 3     6/22/11 2:38p Markw $
//
// $Revision: 3 $
//
// $Date: 6/22/11 2:38p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmPi.h $
// 
// 3     6/22/11 2:38p Markw
// Add exclusions around typedef EFI_AP_PROCEDURE.
// 
// 2     3/04/11 3:33p Markw
// Update headers.
// 
// 1     2/07/11 3:58p Markw
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
//----------------------------------------------------------------------------
//
// Name: SmmPi.h
//
// Description: Smst table definitions.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMMPI__H__
#define __SMMPI__H__

#if PI_SPECIFICATION_VERSION >= 0x0001000A

#include <efi.h>
#include <Protocol\SmmCpuIo2.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SMM_SMST_SIGNATURE 'TSMS'
#define EFI_SMM_SYSTEM_TABLE_REVISION (0<<16) | (0x09)

typedef struct _EFI_SMM_SYSTEM_TABLE2 EFI_SMM_SYSTEM_TABLE2;


typedef EFI_STATUS (EFIAPI *EFI_SMM_INSTALL_CONFIGURATION_TABLE2) (
    IN EFI_SMM_SYSTEM_TABLE2 *SystemTable,
    IN EFI_GUID             *Guid,
    IN VOID                 *Table,
    IN UINTN                TableSize
);

#ifndef EFI_AP_PROCEDURE_TYPE_DEFINED
#define EFI_AP_PROCEDURE_TYPE_DEFINED

typedef VOID (*EFI_AP_PROCEDURE) (
    IN VOID                     *Buffer
);

#endif

typedef EFI_STATUS (EFIAPI *EFI_SMM_STARTUP_THIS_AP) (
    IN EFI_AP_PROCEDURE         Procedure,
    IN UINTN                    CpuNumber,
    IN OUT VOID                 *ProcArguments  OPTIONAL
);

#define EFI_SMM_SYSTEM_TABLE_REVISION2 (1<<16) | (0x0A)


typedef struct _EFI_SMM_ENTRY_CONTEXT {
    EFI_SMM_STARTUP_THIS_AP SmmStartupThisAp;
    UINTN CurrentlyExecutingCpu;
    UINTN NumberOfCpus;
    UINTN *CpuSaveStateSize;
    VOID **CpuSaveState;
} EFI_SMM_ENTRY_CONTEXT;

typedef EFI_STATUS (EFIAPI *EFI_SMM_NOTIFY_FN)(
	IN CONST EFI_GUID *Protocol,
	IN VOID *Interface,
	IN EFI_HANDLE Handle
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_INSTALL_PROTOCOL_INTERFACE) (
		IN OUT EFI_HANDLE *UserHandle, 
		IN EFI_GUID *Protocol,
		IN EFI_INTERFACE_TYPE InterfaceType, 
		IN VOID *Interface
);		

typedef EFI_STATUS (EFIAPI *EFI_SMM_UNINSTALL_PROTOCOL_INTERFACE)(
		IN EFI_HANDLE UserHandle, 
		IN EFI_GUID *Protocol, 
		IN VOID *Interface
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_HANDLE_PROTOCOL)(
		IN EFI_HANDLE Handle, 
		IN EFI_GUID *Protocol,
		OUT VOID **Interface
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_REGISTER_PROTOCOL_NOTIFY)(
		IN CONST EFI_GUID *Protocol, 
		IN EFI_SMM_NOTIFY_FN Function, 
		OUT VOID **Registration
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_LOCATE_HANDLE)(
		IN EFI_LOCATE_SEARCH_TYPE SearchType, 
		IN EFI_GUID *Protocol OPTIONAL, 
		IN VOID *SearchKey OPTIONAL,
		IN OUT UINTN *BufferSize, 
		OUT EFI_HANDLE *Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_LOCATE_PROTOCOL)(
		IN EFI_GUID *Protocol, 
		IN VOID *Registration OPTIONAL,
		OUT VOID **Interface
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_INTERRUPT_MANAGE)(
		IN CONST EFI_GUID *HandlerType,
		IN CONST VOID *Context OPTIONAL,
		IN OUT VOID *CommBuffer OPTIONAL,
		IN OUT UINTN *CommBufferSize OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_HANDLER_ENTRY_POINT2) (
		IN EFI_HANDLE DispatchHandle,
		IN CONST VOID *Context OPTIONAL,
		IN OUT VOID *CommBuffer OPTIONAL,
		IN OUT UINTN *CommBufferSize OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_INTERRUPT_REGISTER) (
		IN EFI_SMM_HANDLER_ENTRY_POINT2 Handler,
		IN CONST EFI_GUID *HandlerType OPTIONAL,
		OUT EFI_HANDLE *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_INTERRUPT_UNREGISTER)(
		IN EFI_HANDLE DispatchHandle
);


typedef struct _EFI_SMM_SYSTEM_TABLE2 {
    EFI_TABLE_HEADER                    Hdr;
    CHAR16                              *SmmFirmwareVendor;
    UINT32                              SmmFirmwareRevision;
    
    EFI_SMM_INSTALL_CONFIGURATION_TABLE2 SmmInstallConfigurationTable;
    
    // I/O Services
    EFI_SMM_CPU_IO2_PROTOCOL             SmmIo;
    
    // Runtime memory service
    EFI_ALLOCATE_POOL                   SmmAllocatePool;
    EFI_FREE_POOL                       SmmFreePool;
    EFI_ALLOCATE_PAGES                  SmmAllocatePages;
    EFI_FREE_PAGES                      SmmFreePages;
    
    // Mp service
    EFI_SMM_STARTUP_THIS_AP             SmmStartupThisAp;

    // CPU information records
    UINTN                               CurrentlyExecutingCpu;
    UINTN                               NumberOfCpus;
    UINTN                               *CpuSaveStateSize;
    VOID                                **CpuSaveState;

    // Extensibility table
    UINTN                               NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE             *SmmConfigurationTable;

    // Protocol services
	EFI_SMM_INSTALL_PROTOCOL_INTERFACE 	SmmInstallProtocolInterface;
	EFI_SMM_UNINSTALL_PROTOCOL_INTERFACE SmmUninstallProtocolInterface;
	EFI_SMM_HANDLE_PROTOCOL 			SmmHandleProtocol;
	EFI_SMM_REGISTER_PROTOCOL_NOTIFY	SmmRegisterProtocolNotify;
	EFI_SMM_LOCATE_HANDLE 				SmmLocateHandle;
	EFI_SMM_LOCATE_PROTOCOL 			SmmLocateProtocol;

	// SMI management functions
	EFI_SMM_INTERRUPT_MANAGE 			SmiManage;
	EFI_SMM_INTERRUPT_REGISTER 			SmiHandlerRegister;
	EFI_SMM_INTERRUPT_UNREGISTER 		SmiHandlerUnRegister;
} EFI_SMM_SYSTEM_TABLE2;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
