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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmControl2.h 2     3/04/11 3:35p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:35p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmControl2.h $
// 
// 2     3/04/11 3:35p Markw
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
//
// Name: SmmControl2.h
//
// Description:	Provides south bridge functions for triggering and clearing SMIs.
//
//<AMI_FHDR_END>
//**********************************************************************

#ifndef __SMM_CONTROL2_PROTOCOL_H__
#define __SMM_CONTROL2_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

//************************************************
// EFI_SMM_PERIOD
//************************************************
typedef UINTN EFI_SMM_PERIOD;

#define EFI_SMM_CONTROL2_PROTOCOL_GUID \
    {0x843dc720,0xab1e,0x42cb,0x93,0x57,0x8a,0x0,0x78,0xf3,0x56,0x1b}

GUID_VARIABLE_DECLARATION(gEfiSmmControl2ProtocolGuid,EFI_SMM_CONTROL2_PROTOCOL_GUID);

typedef struct _EFI_SMM_CONTROL2_PROTOCOL EFI_SMM_CONTROL2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_ACTIVATE2)(
    IN CONST EFI_SMM_CONTROL2_PROTOCOL  *This,
    IN OUT UINT8                        *CommandPort       OPTIONAL,
    IN OUT UINT8                        *DataPort          OPTIONAL,
    IN BOOLEAN                          Periodic           OPTIONAL,
    IN UINTN                            ActivationInterval OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_DEACTIVATE2)(
    IN CONST EFI_SMM_CONTROL2_PROTOCOL  *This,
    IN BOOLEAN                          Periodic OPTIONAL
);

struct _EFI_SMM_CONTROL2_PROTOCOL {
    EFI_SMM_ACTIVATE2    Trigger;
    EFI_SMM_DEACTIVATE2  Clear;
    EFI_SMM_PERIOD      MinimumTriggerPeriod;     /// Minimum interval at which the platform can set the period.
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
