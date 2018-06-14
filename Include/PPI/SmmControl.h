//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **//
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
// $Header: /Alaska/BIN/Core/Include/PPI/SmmControl.h 2     3/13/06 1:16a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:16a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/SmmControl.h $
// 
// 2     3/13/06 1:16a Felixp
// 
// 1     6/21/05 7:12p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SmmControl.h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _SMM_CONTROL_PPI_H__
#define _SMM_CONTROL_PPI_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#define PEI_SMM_CONTROL_PPI_GUID \
	{0x61c68702,0x4d7e,0x4f43,0x8d,0xef,0xa7,0x43,0x5,0xce,0x74,0xc5}

GUID_VARIABLE_DECLARATION(gPeiSmmControlPpiGuid,PEI_SMM_CONTROL_PPI_GUID);

typedef struct _PEI_SMM_CONTROL_PPI PEI_SMM_CONTROL_PPI;

typedef EFI_STATUS (EFIAPI *PEI_SMM_ACTIVATE) (
	IN EFI_PEI_SERVICES		**PeiServices,
	IN PEI_SMM_CONTROL_PPI	*This,
	IN OUT INT8				*ArgumentBuffer OPTIONAL,
	IN OUT UINTN			*ArgumentBufferSize OPTIONAL,
	IN BOOLEAN				Periodic OPTIONAL,
	IN UINTN				ActivationInterval OPTIONAL
);

typedef EFI_STATUS (EFIAPI *PEI_SMM_DEACTIVATE) (
	IN EFI_PEI_SERVICES		**PeiServices,
	IN PEI_SMM_CONTROL_PPI	*This,
	IN BOOLEAN				Periodic OPTIONAL
);

typedef struct _PEI_SMM_CONTROL_PPI {
	PEI_SMM_ACTIVATE	Trigger;
	PEI_SMM_DEACTIVATE	Clear;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
