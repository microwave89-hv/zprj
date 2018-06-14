//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/BootScriptSave.h 12    6/16/11 9:48a Felixp $
//
// $Revision: 12 $
//
// $Date: 6/16/11 9:48a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/BootScriptSave.h $
// 
// 12    6/16/11 9:48a Felixp
// BOOT_SCRIPT_S3_... macros moved to AmiDxeLib.h from BootScripSave.h
// 
// 11    5/13/11 3:29p Oleksiyy
// [TAG]  		EIP56650 
// [Category]  	New Feature
// [Description]  	S3 Save State Protocol and S3 Smm Save State Protocol
// functions added. Support for opcodes introduced in PI 1.2 added.
// [Files]  		BootScriptCommon.h, BootScriptExecuter.c,
// BootScriptPrivate.h, BootScriptSave.c and BootScriptSave.h
// 
// 10    3/09/11 5:43p Artems
// EFI_BOOT_SCRIPT_WIDTH moved to BootScriptCommon.h
// 
// 9     2/05/11 2:29p Artems
// Common definitions for PI 0.91 and PI 1.1 moved to BootScriptCommon.h
// 
// 8     7/17/07 10:44a Markw
// Updated typecasts in macro where UINTN is needed.
// 
// 7     2/12/07 11:20a Felixp
// Clean up
// 
// 6     2/12/07 11:18a Felixp
// Revision field removed from EFI_BOOT_SCRIPT_SAVE_PROTOCOL structure
// to match BootScript spec (it was earlier their for Tiano compliance.
// Tiano header is fixed now).
// 
// 5     12/26/06 2:57p Markw
// Add BootScript Polling.
// 
// 4     3/13/06 1:40a Felixp
// 
// 3     11/07/05 3:42p Sivagarn
// Removed SMBus related definitions.  The Smbus definitions are moved to
// appropriate SMBUS.H file.
// 
// 2     4/04/05 4:37p Markw
// Modified existing and added new macros.
// 
// 1     1/28/05 12:44p Felixp
// 
// 1     12/23/04 9:41a Felixp
// 
// 5     4/22/04 2:32p Felixp
// 
// 4     3/09/04 9:37a Markw
// Fixed Io RW Macro.
// 
// 3     3/08/04 5:25p Markw
// Fixed the BootScriptSave macros.
// 
// 2     3/02/04 4:44p Markw
// Added Boot Script Macros
// 
// 1     2/26/04 2:36p Markw
// 
//**********************************************************************


//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:	BootScriptSave.h
//
// Description: Boot Script Save Protocol header.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __BOOT_SCRIPT_SAVE_PROTOCOL__H__
#define __BOOT_SCRIPT_SAVE_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>
#include <BootScriptCommon.h>

#define EFI_BOOT_SCRIPT_SAVE_GUID \
	{0x470e1529,0xb79e,0x4e32,0xa0,0xfe,0x6a,0x15,0x6d,0x29,0xf9,0xb2}

GUID_VARIABLE_DECLARATION(gEfiBootScriptSaveGuid,EFI_BOOT_SCRIPT_SAVE_GUID);

//*******************************************
// EFI_ACPI_S3_RESUME_SCRIPT_TABLE
//*******************************************
#define EFI_ACPI_S3_RESUME_SCRIPT_TABLE					0x00

//*****************
// Generic macros. 
//*****************

#define BOOT_SCRIPT_IO_WRITE_MACRO(This, TableName, Width, Address, Count, Buffer) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_IO_WRITE_OPCODE,Width,(UINT64)Address,(UINTN)Count,Buffer)

#define BOOT_SCRIPT_IO_READ_WRITE_MACRO(This,TableName,Width,Address,Data,DataMask) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE,Width,(UINT64)Address,Data,DataMask)

#define BOOT_SCRIPT_MEM_WRITE_MACRO(This,TableName,Width,Address,Count,Buffer) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE,Width,(UINT64)Address,(UINTN)Count,Buffer)

#define BOOT_SCRIPT_MEM_READ_WRITE_MACRO(This,TableName,Width,Address,Data,DataMask) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE,Width,(UINT64)Address,Data,DataMask)

#define BOOT_SCRIPT_PCI_CONFIG_WRITE_MACRO(This,TableName,Width,Address,Count,Buffer) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE,Width,(UINT64)Address,(UINTN)Count,Buffer)

#define BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_MACRO(This,TableName,Width,Address,Data,DataMask) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE,Width,(UINT64)Address,Data,DataMask)

#define BOOT_SCRIPT_SMBUS_EXECUTE_MACRO(This,TableName,SlaveAddress,Command,Operation,PecCheck,Length,Buffer) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_SMBUS_EXECUTE_OPCODE,SlaveAddress,Command,Operation,PecCheck,Length,Buffer)

#define BOOT_SCRIPT_STALL_MACRO(This,TableName,Duration) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_STALL_OPCODE,Duration)

#define BOOT_SCRIPT_DISPATCH_MACRO(This,TableName,EntryPoint) \
	This->Write(This,TableName,EFI_BOOT_SCRIPT_DISPATCH_OPCODE,(EFI_PHYSICAL_ADDRESS)EntryPoint)

//OEM

#define BOOT_SCRIPT_IO_POLL_MACRO(This,TableName,Width,Address,Mask,Result) \
    This->Write(This,TableName,EFI_BOOT_SCRIPT_IO_POLL_OPCODE_OEM,Width,(UINT64)Address,Mask,Result)

#define BOOT_SCRIPT_MEM_POLL_MACRO(This,TableName,Width,Address,Mask,Result) \
    This->Write(This,TableName,EFI_BOOT_SCRIPT_MEM_POLL_OPCODE_OEM,Width,(UINT64)Address,Mask,Result)

#define BOOT_SCRIPT_PCI_POLL_MACRO(This,TableName,Width,Address,Mask,Result) \
    This->Write(This,TableName,EFI_BOOT_SCRIPT_PCI_POLL_OPCODE_OEM,Width,(UINT64)Address,Mask,Result)

typedef struct _EFI_BOOT_SCRIPT_SAVE_PROTOCOL EFI_BOOT_SCRIPT_SAVE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_BOOT_SCRIPT_WRITE) (
	IN EFI_BOOT_SCRIPT_SAVE_PROTOCOL	*This,
	IN UINT16							TableName,
	IN UINT16							OpCode,
	...
);

typedef EFI_STATUS (EFIAPI *EFI_BOOT_SCRIPT_CLOSE_TABLE) (
	IN EFI_BOOT_SCRIPT_SAVE_PROTOCOL	*This,
	IN UINT16							TableName,
	OUT EFI_PHYSICAL_ADDRESS			*Address
);

struct _EFI_BOOT_SCRIPT_SAVE_PROTOCOL {
	EFI_BOOT_SCRIPT_WRITE		Write;
	EFI_BOOT_SCRIPT_CLOSE_TABLE	CloseTable;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
