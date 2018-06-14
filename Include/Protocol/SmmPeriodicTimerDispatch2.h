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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmPeriodicTimerDispatch2.h 2     3/04/11 3:36p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmPeriodicTimerDispatch2.h $
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
// 3     7/08/09 8:02p Markw
// Update headers.
// 
// 2     3/28/07 2:41p Markw
// 
//**********************************************************************

//----------------------------------------------------------------------------
//<AMI_FHDR_START>
//
// Name: SmmPeriodicTimerDispatch2.h 
//
// Description:	Smm Periodic Timer Dispatch Protocol header.
//
//<AMI_FHDR_END>
//----------------------------------------------------------------------------

#ifndef __SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL_H__
#define __SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>
#include <SmmPi.h>


#define EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL_GUID \
    {0x4cec368e, 0x8e8e, 0x4d71, 0x8b, 0xe1, 0x95, 0x8c, 0x45, 0xfc, 0x8a, 0x53}

GUID_VARIABLE_DECLARATION(gEfiSmmPeriodicTimerDispatch2ProtocolGuid,EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL_GUID);

typedef struct _EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL;

typedef struct {
    UINT64 Period;
    UINT64 SmiTickInterval;
} EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT;

typedef EFI_STATUS (EFIAPI *EFI_SMM_PERIODIC_TIMER_REGISTER2) (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL  *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2               DispatchFunction,
    IN CONST EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT    *RegisterContext,
    OUT      EFI_HANDLE                                 *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_PERIODIC_TIMER_UNREGISTER2) (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                                DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_PERIODIC_TIMER_INTERVAL2) (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN OUT   UINT64                                    **SmiTickInterval
);

typedef struct _EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL {
    EFI_SMM_PERIODIC_TIMER_REGISTER2   Register;
    EFI_SMM_PERIODIC_TIMER_UNREGISTER2 UnRegister;
    EFI_SMM_PERIODIC_TIMER_INTERVAL2   GetNextShorterInterval;
} EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL;

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
