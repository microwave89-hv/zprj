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

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatch2Protocol.h 1     2/08/12 8:28a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:28a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatch2Protocol.h $
// 
// 1     2/08/12 8:28a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmmChildDispatch2Protocol.h
//
// Description: SMM Child dispatcher II protocols functions definition
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __SMM_CHILD_DISPATCH2_PROTOCOL__H__
#define __SMM_CHILD_DISPATCH2_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Protocol\SmmSwDispatch2.h>
#include <Protocol\SmmSxDispatch2.h>
#include <Protocol\SmmPeriodicTimerDispatch2.h>
#include <Protocol\SmmUsbDispatch2.h>
#include <Protocol\SmmGpiDispatch2.h>
#include <Protocol\SmmStandbyButtonDispatch2.h>
#include <Protocol\SmmPowerButtonDispatch2.h>
#include <Protocol\SmmIoTrapDispatch2.h>

//-------------- Generic register/unregister handler functions --------------

EFI_STATUS RegisterHandler2(
    IN  EFI_SMM_SMI2                            Type,
    IN  SMI_GENERIC_CALLBACK2                   Function,
    IN  CONST VOID                              *Context,
    IN  UINTN                                   ContextSize,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS UnregisterHandler2 (
    IN EFI_SMM_SMI2                             Type,
    IN EFI_HANDLE                               Handle
);

//------------------------ Sw SMI protocol functions ------------------------

EFI_STATUS EfiSmmSwRegister2 (
    IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL      *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2       Function,
    IN CONST EFI_SMM_SW_REGISTER_CONTEXT        *Context,
    OUT      EFI_HANDLE                         *Handle
);

EFI_STATUS EfiSmmSwUnregister2 (
    IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL      *This,
    IN       EFI_HANDLE                         Handle
);

//------------------------ Sx SMI protocol functions ------------------------

EFI_STATUS EfiSmmSxRegister2 (
    IN CONST EFI_SMM_SX_DISPATCH2_PROTOCOL      *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2       Function,
    IN CONST EFI_SMM_SX_REGISTER_CONTEXT        *Context,
    OUT      EFI_HANDLE                         *Handle
);

EFI_STATUS EfiSmmSxUnregister2 (
    IN CONST EFI_SMM_SX_DISPATCH2_PROTOCOL      *This,
    IN EFI_HANDLE                               Handle
);

//------------------ Periodic timer SMI protocol functions ------------------

EFI_STATUS EfiSmmTimerRegister2 (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2              Function,
    IN CONST EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                                *Handle
);

EFI_STATUS EfiSmmTimerUnregister2 (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                                Handle
);

EFI_STATUS EfiSmmTimerGetNextShorterInterval2 (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN OUT   UINT64                                    **SmiTickInterval
);

//----------------------- Usb SMI protocol functions ------------------------

EFI_STATUS EfiSmmUsbRegister2 (
    IN CONST EFI_SMM_USB_DISPATCH2_PROTOCOL     *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2       Function,
    IN CONST EFI_SMM_USB_REGISTER_CONTEXT       *Context,
    OUT      EFI_HANDLE                         *Handle
);

EFI_STATUS EfiSmmUsbUnregister2 (
    IN CONST EFI_SMM_USB_DISPATCH2_PROTOCOL     *This,
    IN       EFI_HANDLE                         Handle
);

//----------------------- Gpi SMI protocol functions ------------------------

EFI_STATUS EfiSmmGpiRegister2 (
    IN CONST EFI_SMM_GPI_DISPATCH2_PROTOCOL     *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2       Function,
    IN CONST EFI_SMM_GPI_REGISTER_CONTEXT       *Context,
    OUT      EFI_HANDLE                         *Handle
);

EFI_STATUS EfiSmmGpiUnregister2 (
    IN CONST EFI_SMM_GPI_DISPATCH2_PROTOCOL     *This,
    IN EFI_HANDLE                               Handle
);

//------------------ Standby button SMI protocol functions ------------------

EFI_STATUS EfiSmmSButtonRegister2 (
    IN CONST EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2              Function,
    IN CONST EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                                *Handle
);

EFI_STATUS EfiSmmSButtonUnregister2 (
    IN CONST EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                                Handle
);

//------------------- Power button SMI protocol functions -------------------

EFI_STATUS EfiSmmPButtonRegister2 (
    IN CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2            Function,
    IN CONST EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmPButtonUnregister2 (
    IN CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                              Handle
);

//--------------------- I/O Trap SMI protocol functions ---------------------

EFI_STATUS EfiSmmIoTrapRegister2 (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2       Function,
    IN OUT   EFI_SMM_IO_TRAP_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                         *Handle
);

EFI_STATUS EfiSmmIoTrapUnregister2 (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                         Handle
);

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
