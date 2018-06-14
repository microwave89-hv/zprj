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
// $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/DbgrX64Lib/AsmDbgrx64Libs.h 4     3/13/12 10:52a Sudhirv $
//
// $Revision: 4 $
//
// $Date: 3/13/12 10:52a $
//*****************************************************************
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/DbgrX64Lib/AsmDbgrx64Libs.h $
// 
// 4     3/13/12 10:52a Sudhirv
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
// 3     9/22/10 7:09p Sudhirv
// 4.6.2_AMIDebugRx_2.01.0026_Beta Release
// 
// 2     7/17/09 7:15p Madhans
// DebugRx 1.30.0022
// 
// 3     7/16/09 3:07p Madhans
// To fix the Serial Debugger issuel and To do cleanup.
// 
// 2     7/13/09 2:44p Sudhirv
// Updated with Coding Standards
// 
// 1     7/07/09 4:46p Sudhirv
// Restructure Binaries Created
// 
// 1     5/01/09 7:48p Madhans
// AMIDebug Rx Module. Intial Checkin.
// 
// 1     4/29/09 7:51a Sudhirv
// AMI Debug Rx module created
// 
// 3     9/07/07 12:07a Madhans
// 1.07.0008 Eng Release
// 
// 7     6/13/07 3:16p Madhans
// Copyright Year updated.
// 
// 6     2/23/07 5:34p Madhans
// EnableMasterPICIRQ function added
// 
// 5     1/22/07 11:36a Madhans
// Modification made for Binary Release 1.04.0003.
// 
// 2     1/05/07 1:05p Ashrafj
// Latest version 1.04.0001 Beta
// Known issues from previous 1.04.000 Beta release has been fixed.
// 
//**********************************************************************
//*****************************************************************
//*****************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	AsmDbgrx64Libs.h
//
// Description:	File containing the Prototypes for the library functions
//				
//
//<AMI_FHDR_END>
//**********************************************************************

#include "Efi.h"

UINT8
DbgrIoRead8 (
  IN  UINT64    Address
  )
/*++

Routine Description:
  Do a one byte IO read

Arguments:
  Address - IO address to read

Returns: 
  Data read

--*/
;
VOID
DbgrIoWrite8 (
  IN  UINT64    Address,
  IN  UINT8     Data
  )
/*++

Routine Description:
  Do a one byte IO write

Arguments:
  Address - IO address to write
  Data    - Data to write to Address

Returns: 
  NONE

--*/
;
void DbgrDisableInterrupt();
void DbgrRestoreInterrupt();

void DebugWriteChkPort(UINT8 DbgChkPoint);

UINT32 ReadPCIConfigSpace(IN UINT32	PCIAddr);
VOID	WritePCIConfigSpace(UINT32	PCIAddr,UINT32 Data);

void DisableMasterPICIRQ(UINT8 IrqBit);
void EnableMasterPICIRQ(UINT8 IrqBit);

#define DISABLE_INTx64 DbgrDisableInterrupt()
#define RESTORE_INTx64 DbgrRestoreInterrupt()

void	DisableDebugFeature(UINTN *pStoreDr7);
void	EnableDebugFeature(UINTN *pLoadDr7);

VOID	SetHWBreakpointX64_DR2(UINTN	Address);
VOID	DisableIF(VOID);
VOID	EnableIF(VOID);
void 	EnableBreakpointOnIO();
void 	DisableBreakpointOnIO();
VOID	GetIdtr(VOID *addr);

UINT8 	IoReadByte(UINT16 Port);
VOID 	IoWriteByte(UINT16 Port, UINT8 Value);
UINT32 	GetCPUInfo0(VOID);
UINT32 	GetCPUInfo4(VOID);
UINT32 	GetCPUInfo8(VOID);
UINT32 	GetVersion(VOID);
UINT32 	GetFeature(VOID);
UINT8 ReadIoAsm8(UINT16 Port);
VOID WriteIoAsm8 (UINT16 Port,UINT8 Val);
UINT16 	IoReadWord(UINT16 Port);
VOID 	IoWriteWord(UINT16 Port, UINT16 Value);
UINT32	IoReadDword(UINT16 Port);
VOID 	IoWriteDword(UINT16 Port, UINT32 Value);
VOID	SET_SOFTWAREBREAKPOINT();

// For IndirectIO Support
UINT8 	IIoReadByte(UINT16 DataPort, UINT16 IndexPort, UINT16 Port);
VOID 	IIoWriteByte(UINT16 DataPort, UINT16 IndexPort, UINT16 Port, UINT8 Value);
UINT16 	IIoReadWord(UINT16 DataPort, UINT16 IndexPort, UINT16 Port);
VOID 	IIoWriteWord(UINT16 DataPort, UINT16 IndexPort, UINT16 Port, UINT16 Value);
UINT32	IIoReadDword(UINT16 DataPort, UINT16 IndexPort, UINT16 Port);
VOID 	IIoWriteDword(UINT16 DataPort, UINT16 IndexPort, UINT16 Port, UINT32 Value);
UINT64	GetCpuTmr();

//EIP 80406 - Debugger support for Dynamic pci express base token
UINT32 IoRead32(UINT16);
VOID IoWrite32(UINT16 Port, UINT32 Value);
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
