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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmSxDispatch2.h 2     3/04/11 3:36p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmSxDispatch2.h $
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
// Name: SmmSxDispatch2.h
//
// Description:	SMM SX Dispatch Protocol Header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_SX_DISPATCH2_PROTOCOL_H__
#define __SMM_SX_DISPATCH2_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <SmmPi.h>

#define EFI_SMM_SX_DISPATCH2_PROTOCOL_GUID \
    {0x456d2859, 0xa84b, 0x4e47, 0xa2, 0xee, 0x32, 0x76, 0xd8, 0x86, 0x99, 0x7d } 

GUID_VARIABLE_DECLARATION(gEfiSmmSxDispatch2ProtocolGuid,EFI_SMM_SX_DISPATCH2_PROTOCOL_GUID);

typedef struct _EFI_SMM_SX_DISPATCH2_PROTOCOL EFI_SMM_SX_DISPATCH2_PROTOCOL;

#ifndef SMM_SX_DEF
#define SMM_SX_DEF

typedef enum {
    SxS0, SxS1, SxS2, SxS3, SxS4, SxS5,
    EfiMaximumSleepType
} EFI_SLEEP_TYPE;

typedef enum {
    SxEntry, SxExit,
    EfiMaximumPhase
} EFI_SLEEP_PHASE;
#endif


typedef struct {
    EFI_SLEEP_TYPE  Type;
    EFI_SLEEP_PHASE Phase;
} EFI_SMM_SX_REGISTER_CONTEXT;

typedef struct _EFI_SMM_SX_DISPATCH2_PROTOCOL  EFI_SMM_SX_DISPATCH2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_SX_REGISTER2)(
    IN  CONST EFI_SMM_SX_DISPATCH2_PROTOCOL  *This,
    IN        EFI_SMM_HANDLER_ENTRY_POINT2   DispatchFunction,
    IN  CONST EFI_SMM_SX_REGISTER_CONTEXT    *RegisterContext,
    OUT       EFI_HANDLE                     *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_SX_UNREGISTER2)(
    IN CONST EFI_SMM_SX_DISPATCH2_PROTOCOL  *This,
    IN       EFI_HANDLE                     DispatchHandle
);

struct _EFI_SMM_SX_DISPATCH2_PROTOCOL {
    EFI_SMM_SX_REGISTER2    Register;
    EFI_SMM_SX_UNREGISTER2  UnRegister;
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
