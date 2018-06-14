//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPPIs/CPUPolicy.h 1     2/07/12 3:58a Davidhsieh $
//
// $Revision: 1 $
//
// $Date: 2/07/12 3:58a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPPIs/CPUPolicy.h $
// 
// 1     2/07/12 3:58a Davidhsieh
// 
// 1     5/06/11 6:07a Davidhsieh
// First release
// 
// 2     3/04/09 10:42a Markw
// Add Copyright header.
// 
// 1     11/02/07 1:59p Markw
// 
// 1     11/02/07 1:45p Markw
// 
// 3     3/23/07 9:54a Markw
// Updated headers.
// 
// 2     2/20/07 10:56a Markw
// Update headers.
// 
// 1     4/01/05 12:55p Robert
// Initial Checkin
//
//
//*****************************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	CPUPolicy.h
//
// Description: This forces NB to load after CPU.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef FILE_PEI_CPUINIT_POLICY_PPI_H_
#define FILE_PEI_CPUINIT_POLICY_PPI_H_

// {F824CCBB-D8E0-4522-8AA8-65F04B463DB5}
#define AMI_PEI_CPUINIT_POLICY_PPI_GUID \
	{0xf824ccbb, 0xd8e0, 0x4522, 0x8a, 0xa8, 0x65, 0xf0, 0x4b, 0x46, 0x3d, 0xb5}

//EFI_GUID_STRING(AMI_PEI_CPUINIT_POLICY_PPI_GUID, "AMICPUPeiInitPolicy", "AMI Generic CPU PEI Init Policy");


typedef struct _AMI_PEI_CPUINIT_POLICY_PPI	AMI_PEI_CPUINIT_POLICY_PPI;

typedef struct _AMI_PEI_CPUINIT_POLICY_PPI {
  UINTN                   unFlag;
} AMI_PEI_CPUINIT_POLICY_PPI;


#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
