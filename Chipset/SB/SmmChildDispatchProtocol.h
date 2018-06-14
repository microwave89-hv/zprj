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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatchProtocol.h 1     2/08/12 8:27a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:27a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatchProtocol.h $
// 
// 1     2/08/12 8:27a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmmChildDispatchProtocol.h
//
// Description: SMM Child dispatcher protocols functions definition
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __SMM_CHILD_DISPATCH_PROTOCOL__H__
#define __SMM_CHILD_DISPATCH_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmSxDispatch.h>
#include <Protocol\SmmPeriodicTimerDispatch.h>
#include <Protocol\SmmUsbDispatch.h>
#include <Protocol\SmmGpiDispatch.h>
#include <Protocol\SmmStandbyButtonDispatch.h>
#include <Protocol\SmmPowerButtonDispatch.h>
#include <Protocol\SmmTcoDispatch.h>
#include <Protocol\SmmIoTrapDispatch.h>
#if defined PI_SPECIFICATION_VERSION && (PI_SPECIFICATION_VERSION >= 0x0001000A)
#include <Protocol\SmmIoTrapDispatch2.h>
#else
#include <Protocol\SmmPchIoTrapDispatch2.h>
#endif

#include <Protocol\SmmBiosWriteDispatch.h>
#include <Token.h>
//-------------- Generic register/unregister handler functions --------------

EFI_STATUS RegisterHandler(
    IN  EFI_SMM_SMI                             Type,
    IN  VOID                                    *Function,
    IN  VOID                                    *Context,
    IN  UINTN                                   ContextSize,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS UnregisterHandler (
    IN EFI_SMM_SMI                              Type,
    IN EFI_HANDLE                               Handle
);

//------------------------ Sw SMI protocol functions ------------------------

EFI_STATUS EfiSmmSwRegister (
    IN EFI_SMM_SW_DISPATCH_PROTOCOL             *This,
    IN EFI_SMM_SW_DISPATCH                      Function,
    IN EFI_SMM_SW_DISPATCH_CONTEXT              *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmSwUnregister (
    IN EFI_SMM_SW_DISPATCH_PROTOCOL             *This,
    IN EFI_HANDLE                               Handle
);

//------------------------ Sx SMI protocol functions ------------------------

EFI_STATUS EfiSmmSxRegister (
    IN EFI_SMM_SX_DISPATCH_PROTOCOL             *This,
    IN EFI_SMM_SX_DISPATCH                      Function,
    IN EFI_SMM_SX_DISPATCH_CONTEXT              *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmSxUnregister (
    IN EFI_SMM_SX_DISPATCH_PROTOCOL             *This,
    IN EFI_HANDLE                               Handle
);

//------------------ Periodic timer SMI protocol functions ------------------

EFI_STATUS EfiSmmTimerRegister (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH          Function,
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmTimerUnregister (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle
);

EFI_STATUS EfiSmmTimerGetNextShorterInterval (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN OUT UINT64                               **SmiTickInterval
);

EFI_STATUS EfiSmmPeriodicTimerEnable (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle  
);

EFI_STATUS EfiSmmPeriodicTimerDisable (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle  
);

//----------------------- Usb SMI protocol functions ------------------------

EFI_STATUS EfiSmmUsbRegister (
    IN EFI_SMM_USB_DISPATCH_PROTOCOL            *This,
    IN EFI_SMM_USB_DISPATCH                     Function,
    IN EFI_SMM_USB_DISPATCH_CONTEXT             *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmUsbUnregister (
    IN EFI_SMM_USB_DISPATCH_PROTOCOL            *This,
    IN EFI_HANDLE                               Handle
);

//----------------------- Gpi SMI protocol functions ------------------------

EFI_STATUS EfiSmmGpiRegister (
    IN EFI_SMM_GPI_DISPATCH_PROTOCOL            *This,
    IN EFI_SMM_GPI_DISPATCH                     Function,
    IN EFI_SMM_GPI_DISPATCH_CONTEXT             *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmGpiUnregister (
    IN EFI_SMM_GPI_DISPATCH_PROTOCOL            *This,
    IN EFI_HANDLE                               Handle
);

//------------------ Standby button SMI protocol functions ------------------

EFI_STATUS EfiSmmSButtonRegister (
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH          Function,
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmSButtonUnregister (
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle
);

//------------------- Power button SMI protocol functions -------------------

EFI_STATUS EfiSmmPButtonRegister (
    IN EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL   *This,
    IN EFI_SMM_POWER_BUTTON_DISPATCH            Function,
    IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT    *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmPButtonUnregister (
    IN EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                               Handle
);

//----------- Total Cost of Ownership (TCO) SMI protocol functions ----------

EFI_STATUS EfiSmmTcoRegister (
    IN EFI_SMM_TCO_DISPATCH_PROTOCOL            *This,
    IN EFI_SMM_TCO_DISPATCH                     Function,
    IN EFI_SMM_TCO_DISPATCH_CONTEXT             *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmTcoUnregister (
    IN EFI_SMM_TCO_DISPATCH_PROTOCOL            *This,
    IN EFI_HANDLE                               Handle
);

//--------------------- I/O Trap SMI protocol functions ---------------------

EFI_STATUS EfiSmmIoTrapRegister (
    IN EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL        *This,
    IN EFI_SMM_IO_TRAP_DISPATCH                 Function,
    IN EFI_SMM_IO_TRAP_DISPATCH_CONTEXT         *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmIoTrapUnregister (
    IN EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL        *This,
    IN EFI_HANDLE                               Handle
);

//------------------- I/O Trap #2 SMI protocol functions -------------------

#if defined PI_SPECIFICATION_VERSION && (PI_SPECIFICATION_VERSION >= 0x0001000A)
EFI_STATUS EfiSmmIoTrap2Register (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL   *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2         Function,
    IN       EFI_SMM_IO_TRAP_REGISTER_CONTEXT     *Context,
    OUT      EFI_HANDLE                           *Handle
);
#else
EFI_STATUS EfiSmmIoTrap2Register (
    IN EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL   *This,
    IN EFI_SMM_IO_TRAP_DISPATCH2            Function,
    IN EFI_SMM_IO_TRAP_REGISTER_CONTEXT     *Context,
    OUT EFI_HANDLE                          *Handle 
);
#endif

#if defined PI_SPECIFICATION_VERSION && (PI_SPECIFICATION_VERSION >= 0x0001000A)
EFI_STATUS EfiSmmIoTrap2Unregister (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL   *This,
    IN       EFI_HANDLE                           Handle 
);
#else
EFI_STATUS EfiSmmIoTrap2Unregister (
    IN EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL   *This,
    IN EFI_HANDLE                           Handle 
);
#endif

//-------------------- BIOS Write SMI protocol functions --------------------

EFI_STATUS EfiSmmBiosWriteRegister (
    IN EFI_SMM_BIOS_WRITE_DISPATCH_PROTOCOL     *This,
    IN EFI_SMM_BIOS_WRITE_DISPATCH              Function,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmBiosWriteUnregister (
    IN EFI_SMM_BIOS_WRITE_DISPATCH_PROTOCOL     *This,
    IN EFI_HANDLE                               Handle
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
