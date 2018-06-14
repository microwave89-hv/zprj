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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmPowerButtonDispatch2.h 2     3/04/11 3:36p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmPowerButtonDispatch2.h $
// 
// 2     3/04/11 3:36p Markw
// Update headers.
// 
// 1     2/07/11 4:03p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		mm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: PowerButtonDispatch2.h
//
// Description:	Power Button Dispatch Protocol Header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_POWER_BUTTON_DISPATCH2_PROTOCOL_H__
#define __SMM_POWER_BUTTON_DISPATCH2_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <Efi.h>
#include <SmmPi.h>


#define EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL_GUID \
    {0x1b1183fa, 0x1823, 0x46a7, 0x88, 0x72, 0x9c, 0x57, 0x87, 0x55, 0x40, 0x9d } 

GUID_VARIABLE_DECLARATION(gEfiSmmPowerButtonDispatch2ProtocolGuid,EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL_GUID);

typedef struct _EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL;

typedef enum {
    EfiPowerButtonEntry,
    EfiPowerButtonExit,
    EfiPowerButtonMax
} EFI_POWER_BUTTON_PHASE;

typedef struct {
    EFI_POWER_BUTTON_PHASE  Phase;
} EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT;


typedef struct _EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_POWER_BUTTON_REGISTER2)(
    IN CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL  *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2             DispatchFunction,
    IN       EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT    *RegisterContext,
    OUT      EFI_HANDLE                               *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_POWER_BUTTON_UNREGISTER2)(
    IN CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL  *This,
    IN       EFI_HANDLE                               DispatchHandle
);

// This protocol provides the parent dispatch service for the power button SMI source generator.
struct _EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL {
    EFI_SMM_POWER_BUTTON_REGISTER2    Register;
    EFI_SMM_POWER_BUTTON_UNREGISTER2  UnRegister;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
