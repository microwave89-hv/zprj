//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmSxDispatch.h 4     2/07/11 3:38p Markw $
//
// $Revision: 4 $
//
// $Date: 2/07/11 3:38p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmSxDispatch.h $
// 
// 4     2/07/11 3:38p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
// 3     7/08/09 8:02p Markw
// Update headers.
// 
// 2     3/28/07 2:47p Markw
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmSxDispatch.h
//
// Description:	SMM SX Dispatch Protocol Header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_SX_DISPATCH_PROTOCOL_H__
#define __SMM_SX_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_SX_DISPATCH_PROTOCOL_GUID \
	{0x14fc52be, 0x1dc, 0x426c, 0x91, 0xae, 0xa2, 0x3c, 0x3e, 0x22, 0xa, 0xe8}

GUID_VARIABLE_DECLARATION(gEfiSmmSxDispatchProtocolGuid,EFI_SMM_SX_DISPATCH_PROTOCOL_GUID);

typedef struct _EFI_SMM_SX_DISPATCH_PROTOCOL EFI_SMM_SX_DISPATCH_PROTOCOL;

#ifndef SMM_SX_DEF
#define SMM_SX_DEF

//****************************************************
// EFI_SLEEP_TYPE
//****************************************************
typedef enum {
	SxS0, SxS1, SxS2, SxS3, SxS4, SxS5,
	EfiMaximumSleepType
} EFI_SLEEP_TYPE;

//****************************************************
// EFI_SLEEP_PHASE
//****************************************************
typedef enum {
	SxEntry, SxExit,
	EfiMaximumPhase
} EFI_SLEEP_PHASE;

#endif


//****************************************************
// EFI_SMM_SX_DISPATCH_CONTEXT
//****************************************************
typedef struct {
	EFI_SLEEP_TYPE	Type;
	EFI_SLEEP_PHASE	Phase;
} EFI_SMM_SX_DISPATCH_CONTEXT;

//****************************************************
// EFI_SMM_SX_DISPATCH
//****************************************************
typedef VOID (EFIAPI *EFI_SMM_SX_DISPATCH) (
	IN EFI_HANDLE					DispatchHandle,
	IN EFI_SMM_SX_DISPATCH_CONTEXT	*DispatchContext
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_SX_REGISTER) (
	IN EFI_SMM_SX_DISPATCH_PROTOCOL	*This,
	IN EFI_SMM_SX_DISPATCH			DispatchFunction,
	IN EFI_SMM_SX_DISPATCH_CONTEXT	*DispatchContext,
	OUT EFI_HANDLE					*DispatchHandle
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_SX_UNREGISTER) (
	IN EFI_SMM_SX_DISPATCH_PROTOCOL	*This,
	IN EFI_HANDLE					DispatchHandle
);


struct _EFI_SMM_SX_DISPATCH_PROTOCOL {
	EFI_SMM_SX_REGISTER		Register;
	EFI_SMM_SX_UNREGISTER	UnRegister;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
