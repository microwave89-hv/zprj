//**********************************************************************
//**********************************************************************
//**																																	**
//**				(C)Copyright 1985-2004,	American Megatrends, Inc.					**
//**																																	**
//**											 All Rights	Reserved.												**
//**																																	**
//**						 6145-F	Northbelt	Pkwy,	Norcross,	GA 30071						**
//**																																	**
//**											 Phone:	(770)-246-8600											**
//**																																	**
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/PPI/CpuIo.h 4     3/13/06 1:16a Felixp $
//
// $Revision: 4 $
//
// $Date: 3/13/06 1:16a $
//*****************************************************************************
// Revision	History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/CpuIo.h $
// 
// 4     3/13/06 1:16a Felixp
// 
// 3     6/06/05 1:24p Felixp
// 
// 2     6/03/05 3:44p Felixp
// Updated to support changes introduced in PEI CIS 0.91
// 
// 1     1/28/05 12:44p Felixp
// 
// 1     12/23/04 9:41a Felixp
// 
// 7     12/19/03 10:15a Robert
// 
// 6     12/18/03 3:08p Robert
//
// 5		 12/18/03	2:46p	Robert
//
// 4		 12/16/03	4:03p	Robert
//
// 3		 12/15/03	4:21p	Robert
//
// 2		 12/15/03	3:01p	Robert
// Added SmBus SubComponent
//
// 1		 12/11/03	5:35p	Robert
// Initial Check in	of the Cpu I/O PPI
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	CpuIo.h
//
// Description:	This file	is an	include	file used	to define	the	PPI	for	the
//		CPU	I/O	PPI.	For	questions	about	the	specification	refer	to the PEI CIS
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef	_PEI_CPUIO_PPI_H_
#define	_PEI_CPUIO_PPI_H_
#ifdef __cplusplus
extern "C" {
#endif
#include<PEI.h>

// This is an indicator GUID without any data. It represents the fact that a PEIM
// has written the address of the EFI_PEI_CPU_IO_PPI into the EFI_PEI_SERVICES
#define	EFI_PEI_CPU_IO_PPI_INSTALLED_GUID \
	{0xe6af1f7b, 0xfc3f, 0x46da, 0xa8, 0x28, 0xa3, 0xb4, 0x57, 0xa4, 0x42, 0x82}

GUID_VARIABLE_DECLARATION(gPeiCpuIoPpiInServiceTableGuid,EFI_PEI_CPU_IO_PPI_INSTALLED_GUID);
/******	DO NOT WRITE BELOW THIS	LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**																																	**
//**				(C)Copyright 1985-2004,	American Megatrends, Inc.					**
//**																																	**
//**											 All Rights	Reserved.												**
//**																																	**
//**						 6145-F	Northbelt	Pkwy,	Norcross,	GA 30071						**
//**																																	**
//**											 Phone:	(770)-246-8600											**
//**																																	**
//**********************************************************************
//**********************************************************************
