//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2009, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDebugSupport/DbgrHelp.c 6     4/04/12 4:57p Sudhirv $
//
// $Revision: 6 $
//
// $Date: 4/04/12 4:57p $
//*****************************************************************
//*****************************************************************
//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDebugSupport/DbgrHelp.c $
// 
// 6     4/04/12 4:57p Sudhirv
// To Avoid Build errors in special cases.
// 
// 5     3/13/12 10:47a Sudhirv
// [TAG]  		EIP60224
// [Category]  	Improvement
// [Description]  Function implement When broken in SMM, show the register
// context for 'outside' SMM.
// 
// [TAG]  		EIP80406
// [Category]  	Improvement
// [Description]  Debugger support for Dynamic pci express base token
// 
// [TAG]  		EIP81423
// [Category]  	Improvement
// [Description]  VeB Debugger - Improve the EFI tab's Handle Display
// feature
// 
// [TAG]  		EIP84201
// [Category]  	Improvement
// [Description]  AMIDebugRx\Debugger Target modules usage of the Port 80
// must be controlable
// 
// 4     5/13/11 4:13p Madhans
// [TAG]  		EIP60365 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	LoadFV not working for PI 1.1 BIOS
// [RootCause]  	The SDK Token values need to come from the building
// project. But it was included with Binary so change SDL value cause the
// feature to break
// [Solution]  	SDL token values are will used be source.
// [Files]  		relocdbg.obj
// relocdbg_PI_1_1.obj
// dbghelp.c
// 
// 3     3/09/11 8:23a Sudhirv
// EIP 53658 - AMIDebugRx\Debugger support for PI 1.1
// 
// 2     7/17/09 7:15p Madhans
// DebugRx 1.30.0022
// 
// 2     7/13/09 2:50p Sudhirv
// Updated with Coding Standards
// 
// 1     7/07/09 4:46p Sudhirv
// Restructure Binaries Created
// 
// 1     5/01/09 7:48p Madhans
// AMIDebug Rx Module. Intial Checkin.
// 
// 1     4/29/09 7:52a Sudhirv
// AMI Debug Rx module created
// 
// 6     3/27/09 8:41a Sudhirv
// Updated Coding Standards.
// 
// 5     6/13/07 3:17p Madhans
// Copyright Year updated.
// 
// 4     1/22/07 11:42a Madhans
// Modification made for Binary Release 1.04.0003.
// 
// 4     1/05/07 6:15p Madhan
// 
// 3     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
// 
//
//*****************************************************************

//*****************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		DbgHelp.c
//
// Description:	File containing the globals for CAR base address & size.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "misc.h"
#include "AMIPeiDebug.h"

#if defined (PI_SPECIFICATION_VERSION) && (PI_SPECIFICATION_VERSION >= 0x00010000)
const UINTN	AMI_PEIDEBUGGER_DS_BASEADDRESS 	= 0;
const UINTN	AMI_PEIDEBUGGER_DS_SIZE			= 0x2048;
#else
const UINTN	AMI_PEIDEBUGGER_DS_BASEADDRESS 	= PEI_DEBUG_DATASECTION_BASEADDRESS;
const UINTN	AMI_PEIDEBUGGER_DS_SIZE			= PEI_DEBUG_DATASECTION_SIZE;
#endif

#ifndef ALASKA_SUPPORT

#define FV_MAIN_BLOCKS	FLASH_REGION_FVMAIN_SIZE_IN_BLOCKS
#define FV_BB_BLOCKS	FLASH_REGION_FV_RECOVERY_SIZE_IN_BLOCKS
#define FV_MAIN_BASE	FLASH_REGION_FVMAIN_BASE

#endif

#ifndef FV_MAIN_BASE
#define FV_MAIN_BASE 0
#endif
#ifndef FV_MAIN_BLOCKS
#define FV_MAIN_BLOCKS 0
#endif
#ifndef FV_BB_BLOCKS
#define FV_BB_BLOCKS 0
#endif
#ifndef FLASH_BLOCK_SIZE
#define FLASH_BLOCK_SIZE 0
#endif
#ifndef DBG_WRITE_IO_80_SUPPORT
#define DBG_WRITE_IO_80_SUPPORT 0
#endif

UINTN gFvMainBase = FV_MAIN_BASE;
UINTN gFvMainBlocks = FV_MAIN_BLOCKS;
UINTN gFvBBBlocks = FV_BB_BLOCKS;
UINTN gBlockSize = FLASH_BLOCK_SIZE;

volatile UINTN gDbgWriteIO80Support = DBG_WRITE_IO_80_SUPPORT;

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2009, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

