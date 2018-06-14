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
// $Header: /Alaska/BIN/Core/Modules/Recovery/DeviceRecoveryModule.h 1     12/01/05 9:35a Felixp $
//
// $Revision: 1 $
//
// $Date: 12/01/05 9:35a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/Recovery/DeviceRecoveryModule.h $
// 
// 1     12/01/05 9:35a Felixp
// 
// 3     3/22/05 9:33p Felixp
// 
// 2     3/22/05 8:21p Felixp
// 
// 1     3/22/05 8:04p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	DeviceRecoveryModule.h
//
// Description:	EFI_PEI_DEVICE_RECOVERY_MODULE_PPI PPI definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __DeviceRecoveryModule__H__
#define __DeviceRecoveryModule__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <PEI.h>

#define EFI_PEI_DEVICE_RECOVERY_MODULE_PPI_GUID \
{ 0x0DE2CE25, 0x446A, 0x45a7, 0xBF, 0xC9, 0x37, 0xDA, 0x26, 0x34, 0x4B, 0x37}

typedef struct _EFI_PEI_DEVICE_RECOVERY_MODULE_PPI EFI_PEI_DEVICE_RECOVERY_MODULE_PPI;

typedef EFI_STATUS (EFIAPI *EFI_PEI_DEVICE_GET_NUMBER_RECOVERY_CAPSULE)(
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
	OUT UINTN *NumberRecoveryCapsules
);

typedef EFI_STATUS (EFIAPI *EFI_PEI_DEVICE_GET_RECOVERY_CAPSULE_INFO)(
	IN EFI_PEI_SERVICES **PeiServices,
	IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
	IN UINTN CapsuleInstance, OUT UINTN *Size,
	OUT EFI_GUID *CapsuleType
);

typedef EFI_STATUS (EFIAPI *EFI_PEI_DEVICE_LOAD_RECOVERY_CAPSULE)(
	IN OUT EFI_PEI_SERVICES **PeiServices,
	IN struct _EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
	IN UINTN CapsuleInstance, OUT VOID *Buffer
);

struct _EFI_PEI_DEVICE_RECOVERY_MODULE_PPI {
	EFI_PEI_DEVICE_GET_NUMBER_RECOVERY_CAPSULE GetNumberRecoveryCapsules;
	EFI_PEI_DEVICE_GET_RECOVERY_CAPSULE_INFO GetRecoveryCapsuleInfo;
	EFI_PEI_DEVICE_LOAD_RECOVERY_CAPSULE LoadRecoveryCapsule;
};

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