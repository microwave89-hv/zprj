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
// $Header: /Alaska/BIN/Core/Include/BootScriptCommon.h 5     6/24/11 1:47p Felixp $
//
// $Revision: 5 $
//
// $Date: 6/24/11 1:47p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/BootScriptCommon.h $
// 
// 5     6/24/11 1:47p Felixp
// Improved compatibility with the Framework drivers in PI mode.
// 
// 4     6/16/11 10:01a Felixp
// Enhancements: 
// 1. SAVE_STATE_... macros are removed (used BOOT_SCRIPT_S3_... from
// AmiDxeLib.h instead) 
// 2. OEM OpCodes moved into the Framework section of the header (no OEM
// OpCodes in PEI)
// 
// 3     5/13/11 3:28p Oleksiyy
// [TAG]  		EIP56650 
// [Category]  	New Feature
// [Description]  	S3 Save State Protocol and S3 Smm Save State Protocol
// functions added. Support for opcodes introduced in PI 1.2 added.
// [Files]  		BootScriptCommon.h, BootScriptExecuter.c,
// BootScriptPrivate.h, BootScriptSave.c and BootScriptSave.h
// 
// 2     3/11/11 7:02p Artems
// 
// 1     3/09/11 5:33p Artems
// 
// 1     2/03/11 4:45p Oleksiyy
// 
// 1     2/03/11 4:09p Oleksiyy
// [TAG]  		EIP53402 
// [Category]  	Improvement
// [Description]  	Create new label of ACPI with separate S3 Functionality
// [Files]  		S3Common.cif
// ..\..\..\Include\BootScriptCommon.h
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
// Name:	BootScriptCommon.h
//
// Description: Boot Script Common definitions header.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __BOOT_SCRIPT_COMMON__H__
#define __BOOT_SCRIPT_COMMON__H__
#ifdef __cplusplus
extern "C" {
#endif

//*******************************************
// EFI Save State Script Opcode definitions (Common)
//*******************************************
#define EFI_BOOT_SCRIPT_IO_WRITE_OPCODE                 0x00
#define EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE            0x01
#define EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE                0x02
#define EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE           0x03
#define EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE         0x04
#define EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE    0x05
#define EFI_BOOT_SCRIPT_SMBUS_EXECUTE_OPCODE            0x06
#define EFI_BOOT_SCRIPT_STALL_OPCODE                    0x07
#define EFI_BOOT_SCRIPT_DISPATCH_OPCODE                 0x08

#if PI_SPECIFICATION_VERSION>=0x0001000A
//*******************************************
// EFI Save State Script Opcode definitions (PI)
//*******************************************
#define EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE               0x09
#define EFI_BOOT_SCRIPT_INFORMATION_OPCODE              0x0A
#define EFI_BOOT_SCRIPT_PCI_CONFIG2_WRITE_OPCODE        0x0B
#define EFI_BOOT_SCRIPT_PCI_CONFIG2_READ_WRITE_OPCODE   0x0C
#define EFI_BOOT_SCRIPT_IO_POLL_OPCODE                  0x0D
#define EFI_BOOT_SCRIPT_MEM_POLL_OPCODE                 0x0E
#define EFI_BOOT_SCRIPT_PCI_CONFIG_POLL_OPCODE          0x0F
#define EFI_BOOT_SCRIPT_PCI_CONFIG2_POLL_OPCODE         0x10
#define EFI_BOOT_SCRIPT_LABEL_OPCODE_OEM                0x83
#endif

#if BACKWARD_COMPATIBLE_MODE || PI_SPECIFICATION_VERSION < 0x0001000A
//*******************************************
// EFI Boot Script Opcode definitions (Framework)
//*******************************************

// Extensions to boot script definitions
//OEM
#ifndef EFI_BOOT_SCRIPT_IO_POLL_OPCODE_OEM
#define EFI_BOOT_SCRIPT_IO_POLL_OPCODE_OEM                  0x80
#endif

#ifndef EFI_BOOT_SCRIPT_MEM_POLL_OPCODE_OEM
#define EFI_BOOT_SCRIPT_MEM_POLL_OPCODE_OEM                 0x81
#endif

#ifndef EFI_BOOT_SCRIPT_PCI_POLL_OPCODE_OEM
#define EFI_BOOT_SCRIPT_PCI_POLL_OPCODE_OEM                 0x82
#endif

#endif

#define EFI_BOOT_SCRIPT_TABLE_OPCODE                  0xAA
#define EFI_BOOT_SCRIPT_TERMINATE_OPCODE              0xFF

//*******************************************
// EFI_BOOT_SCRIPT_WIDTH
//*******************************************
typedef enum {
	EfiBootScriptWidthUint8,
	EfiBootScriptWidthUint16,
	EfiBootScriptWidthUint32,
	EfiBootScriptWidthUint64,
	EfiBootScriptWidthFifoUint8,
	EfiBootScriptWidthFifoUint16,
	EfiBootScriptWidthFifoUint32,
	EfiBootScriptWidthFifoUint64,
	EfiBootScriptWidthFillUint8,
	EfiBootScriptWidthFillUint16,
	EfiBootScriptWidthFillUint32,
	EfiBootScriptWidthFillUint64,
	EfiBootScriptWidthMaximum
} EFI_BOOT_SCRIPT_WIDTH;

//////////////////////////////////////////////////////////////////////////////////

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
