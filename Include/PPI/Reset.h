//************************************************************************
//************************************************************************
//**																	**
//**		(C)Copyright 1985-2004,	American Megatrends, Inc.			**
//**																	**
//**					 All Rights	Reserved.							**
//**																	**
//**		 6145-F	Northbelt Pkwy, Norcross, GA 30071					**
//**																	**
//**					 Phone:	(770)-246-8600							**
//**																	**
//************************************************************************
//************************************************************************
//************************************************************************
// $Header: /Alaska/BIN/Core/Include/PPI/Reset.h 2     3/13/06 1:16a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:16a $
//*****************************************************************************
// Revision	History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/Reset.h $
// 
// 2     3/13/06 1:16a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     2/16/04 11:48a Robert
// 
// 1     2/13/04 11:15a Robert
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:	Reset.h
//
// Description:	This file is used to define the Reset PPI used to reset the
//		system when the PeiServices ResetSystem function is called
//
//<AMI_FHDR_END>
//*****************************************************************************
#ifndef	_RESET_PPI_H_
#define	_RESET_PPI_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#define	EFI_PEI_RESET_PPI_GUID \
  {0xef398d58, 0x9dfd, 0x4103, 0xbf, 0x94, 0x78, 0xc6, 0xf4, 0xfe, 0x71, 0x2f}

GUID_VARIABLE_DECLARATION(gPeiResetPpiGuid, EFI_PEI_RESET_PPI_GUID);

typedef	struct	_EFI_PEI_RESET_PPI		EFI_RESET_PPI;

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_RESET) (
		IN EFI_PEI_SERVICES **PeiServices
	);


typedef struct _EFI_PEI_RESET_PPI {
	EFI_PEI_RESET ResetSystem;
	} EFI_PEI_RESET_PPI;

/******	DO NOT WRITE BELOW THIS	LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**																  **
//**		(C)Copyright 1985-2004,	American Megatrends, Inc.		  **
//**																  **
//**						 All Rights	Reserved.					  **
//**																  **
//**		 6145-F	Northbelt	Pkwy,	Norcross,	GA 30071		  **
//**																  **
//**						 Phone:	(770)-246-8600					  **
//**																  **
//**********************************************************************
//**********************************************************************
