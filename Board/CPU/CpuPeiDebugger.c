//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CpuPeiDebugger.c 1     2/07/12 3:57a Davidhsieh $
//
// $Revision: 1 $
//
// $Date: 2/07/12 3:57a $
//
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Board/CpuPeiDebugger.c $
// 
// 1     2/07/12 3:57a Davidhsieh
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		CpuPeiDebugger.C
//
// Description:
//  This file contains PEI stage board component code for Template CPU module
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <Efi.h>
#include <AmiLib.h>
#include <Token.h>
#include "AmiDebugPort.h"
#include "CpuCspLib.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CPUPEIDBG_Initialize
//
// Description:	
//  This eLink function is used to initialize CPU for PEI debugger support
//
// Input:		DbgXportIfStruc		Debug transport interface structure
//
// Output:		EFI_STATUS
//
// Notes:		PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CPUPEIDBG_Initialize (
	PEI_DBG_PORT_INFO	*DebugPort
)
{
	MemReadWrite32((UINT32*)(UINTN)(LOCAL_APIC_BASE + APIC_SPURIOUS_VECTOR_REGISTER), 1 << 8, 0xffffffff);

	//--------------------------
	//Program Virtual Wire Mode.
	//--------------------------
 
	//Program LINT0 vector as ExtInt
	MemReadWrite32((UINT32*)(UINTN)(LOCAL_APIC_BASE + APIC_LVT_LINT0_REGISTER),
		0x700, 0xfffe00ff
	);
  
	//Program the LINT1 vector entry as NMI
	MemReadWrite32((UINT32*)(UINTN)(LOCAL_APIC_BASE + APIC_LVT_LINT1_REGISTER),
		0x10400, 0xfffe00ff
	);

	return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
