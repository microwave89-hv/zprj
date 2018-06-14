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
// $Header: /Alaska/BIN/Core/Include/PPI/ReadOnlyVariable2.h 3     6/16/11 5:30p Felixp $
//
// $Revision: 3 $
//
// $Date: 6/16/11 5:30p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/ReadOnlyVariable2.h $
// 
// 3     6/16/11 5:30p Felixp
// FORWARD_COMPATIBLE_MODE definitions removed (they are not needed in the
// Core version of the header).
// 
// 1     6/16/11 4:56p Felixp
// 
// 2     5/27/11 6:02p Felixp
// 
// 1     5/27/11 5:50p Felixp
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  ReadOnlyVariable2.h
//
// Description:	ReadOnlyVariable2 PPI Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __READ_ONLY_VARIABLE2_PPI__H__
#define __READ_ONLY_VARIABLE2_PPI__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Pei.h>

#define EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID \
    { 0x2ab86ef5, 0xecb5, 0x4134, 0xb5, 0x56, 0x38, 0x54, 0xca, 0x1f, 0xe1, 0xb4 }

GUID_VARIABLE_DECLARATION(gEfiPeiReadOnlyVariable2PpiGuid, EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID);

typedef struct _EFI_PEI_READ_ONLY_VARIABLE2_PPI EFI_PEI_READ_ONLY_VARIABLE2_PPI;

typedef EFI_STATUS (EFIAPI *EFI_PEI_GET_VARIABLE2)
(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN CONST CHAR16 *VariableName,
    IN CONST EFI_GUID *VariableGuid,
    OUT UINT32 *Attributes,
    IN OUT UINTN *DataSize,
    OUT VOID *Data
);

typedef EFI_STATUS (EFIAPI *EFI_PEI_GET_NEXT_VARIABLE_NAME2)
(
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
    IN OUT UINTN *VariableNameSize,
    IN OUT CHAR16 *VariableName,
    IN OUT EFI_GUID *VariableGuid
);

struct _EFI_PEI_READ_ONLY_VARIABLE2_PPI {
    EFI_PEI_GET_VARIABLE2 GetVariable;
    EFI_PEI_GET_NEXT_VARIABLE_NAME2 NextVariableName;
};

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
