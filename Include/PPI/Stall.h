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
// $Header: /Alaska/BIN/Core/Include/PPI/Stall.h 2     3/13/06 1:16a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:16a $
//*****************************************************************************
// Revision	History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/Stall.h $
// 
// 2     3/13/06 1:16a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     2/12/04 5:07p Robert
// 
// 1     1/06/04 2:53p Robert
// 
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	Stall.h
//
// Description:	This file	is an	include	file used	to define	the	PPI	for	the
//		Stall PPI.	For	questions	about	the	specification	refer	to the PEI CIS
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef	_STALL_PPI_H_
#define	_STALL_PPI_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#define	EFI_PEI_STALL_PPI_GUID \
{	0x1f4c6f90, 0xb06b, 0x48d8, 0xa2, 0x01, 0xba, 0xe5, 0xf1, 0xcd, 0x7d, 0x56 }

GUID_VARIABLE_DECLARATION(gPeiStallPpiGuid,EFI_PEI_STALL_PPI_GUID);

typedef	struct	_EFI_PEI_STALL_PPI		EFI_PEI_STALL_PPI;

typedef
EFI_STATUS 
(EFIAPI *EFI_PEI_STALL) (
		IN EFI_PEI_SERVICES **PeiServices,
		IN struct _EFI_PEI_STALL_PPI *This,
		IN UINTN Microseconds
	);


typedef
struct _EFI_PEI_STALL_PPI {
		UINTN Resolution;
		EFI_PEI_STALL Stall;
	} EFI_PEI_STALL_PPI;

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
