//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/PPI/ReadOnlyVariable.h 7     6/16/11 3:18p Felixp $
//
// $Revision: 7 $
//
// $Date: 6/16/11 3:18p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/ReadOnlyVariable.h $
// 
// 7     6/16/11 3:18p Felixp
// Surround backward compatibility definitions with #if
// BACKWARD_COMPATIBLE_MODE
// 
// 6     5/27/11 5:52p Felixp
// Headers are updated to improve separation of the Framework and PI
// interfaces.
// The definitions that will be removed in the future versions are marked
// with the comments.
// 
// 5     8/30/07 11:06p Felixp
// EFI_PEI_READ_ONLY_VARIABLE2_PPI added
// 
// 4     3/13/06 1:16a Felixp
// 
// 3     3/22/05 9:23p Felixp
// 
// 2     3/04/05 10:26a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     1/22/04 12:47p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	ReadOnlyVariable.h
//
// Description:	Defines Read Only Variable PPI
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __ReadOnlyVariable__H__
#define __ReadOnlyVariable__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#define EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID \
    {0x3cdc90c6, 0x13fb, 0x4a75, 0x9e, 0x79, 0x59, 0xe9, 0xdd, 0x78, 0xb9, 0xfa}

GUID_VARIABLE_DECLARATION(gPeiReadOnlyVariablePpiGuid,EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID);

typedef EFI_STATUS (EFIAPI *EFI_PEI_GET_VARIABLE)
(
	IN EFI_PEI_SERVICES **PeiServices,
	IN CHAR16 *VariableName,
	IN EFI_GUID *VendorGuid,
	OUT UINT32 *Attributes OPTIONAL,
	IN OUT UINTN *DataSize,
	OUT VOID *Data
);

typedef EFI_STATUS (EFIAPI *EFI_PEI_GET_NEXT_VARIABLE_NAME)
(
	IN EFI_PEI_SERVICES **PeiServices,
	IN OUT UINTN *VariableNameSize,
	IN OUT CHAR16 *VariableName,
	IN OUT EFI_GUID *VendorGuid
);

//PPI Interface Structure
typedef struct _EFI_PEI_READ_ONLY_VARIABLE_PPI {
	EFI_PEI_GET_VARIABLE GetVariable;
	EFI_PEI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
} EFI_PEI_READ_ONLY_VARIABLE_PPI;
//===============================================================================
#if BACKWARD_COMPATIBLE_MODE
#include <Ppi/ReadOnlyVariable2.h>

GUID_VARIABLE_DECLARATION(gPeiReadOnlyVariable2PpiGuid,EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID);
#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
