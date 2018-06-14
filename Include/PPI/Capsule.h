//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Core/Include/PPI/Capsule.h 1     5/24/12 3:15p Artems $
//
// $Revision: 1 $
//
// $Date: 5/24/12 3:15p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/Capsule.h $
// 
// 1     5/24/12 3:15p Artems
// [TAG]  		EIP74625
// [Category]  	New Feature
// [Description]  	added new capsule ppi used by Intel's MRC code
// [Files]  		Capsule.h
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Capsule.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _PEI_CAPSULE_PPI_H_
#define _PEI_CAPSULE_PPI_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Pei.h>

#define PEI_CAPSULE_PPI_GUID \
  { 0x3acf33ee, 0xd892, 0x40f4, 0xa2, 0xfc, 0x38, 0x54, 0xd2, 0xe1, 0x32, 0x3d }

GUID_VARIABLE_DECLARATION(gPeiCapsulePpiGuid, PEI_CAPSULE_PPI_GUID);

typedef struct _PEI_CAPSULE_PPI PEI_CAPSULE_PPI;

typedef EFI_STATUS
(EFIAPI *PEI_CAPSULE_COALESCE)(
    IN EFI_PEI_SERVICES  **PeiServices,
    IN OUT VOID          **MemoryBase,
    IN OUT UINTN         *MemSize
);

typedef EFI_STATUS
(EFIAPI *PEI_CAPSULE_CHECK_CAPSULE_UPDATE)(
    IN EFI_PEI_SERVICES  **PeiServices
);

typedef EFI_STATUS
(EFIAPI *PEI_CAPSULE_CREATE_STATE)(
    IN EFI_PEI_SERVICES  **PeiServices,
    IN VOID              *CapsuleBase,
    IN UINTN             CapsuleSize  
);

struct _PEI_CAPSULE_PPI {
  PEI_CAPSULE_COALESCE              Coalesce;
  PEI_CAPSULE_CHECK_CAPSULE_UPDATE  CheckCapsuleUpdate;
  PEI_CAPSULE_CREATE_STATE          CreateState;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************