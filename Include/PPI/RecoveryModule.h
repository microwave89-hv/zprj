//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/PPI/RecoveryModule.h 2     3/13/06 1:16a Felixp $
//
// $Revision: 2 $
//
// $Date: 3/13/06 1:16a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/PPI/RecoveryModule.h $
// 
// 2     3/13/06 1:16a Felixp
// 
// 1     12/01/05 9:48a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	RecoveryModule.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __RECOVERY_MODULE__H__
#define __RECOVERY_MODULE__H__
#ifdef __cplusplus
extern "C" {
#endif
#include<PEI.h>

#define EFI_PEI_RECOVERY_MODULE_PPI_GUID \
	{0xFB6D9542, 0x612D, 0x4f45, 0x87, 0x2F, 0x5C, 0xFF, 0x52, 0xE9, 0x3D, 0xCF}

GUID_VARIABLE_DECLARATION(gPeiRecoveryModulePpiGuid,EFI_PEI_RECOVERY_MODULE_PPI_GUID);

typedef EFI_STATUS (EFIAPI *EFI_PEI_LOAD_RECOVERY_CAPSULE)(
	IN EFI_PEI_SERVICES **PeiServices,
	IN struct _EFI_PEI_RECOVERY_MODULE_PPI *This
);

typedef struct _EFI_PEI_RECOVERY_MODULE_PPI {
	EFI_PEI_LOAD_RECOVERY_CAPSULE LoadRecoveryCapsule;
} EFI_PEI_RECOVERY_MODULE_PPI;
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************