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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatchProtocol.c 2     4/25/12 9:35a Victortu $
//
// $Revision: 2 $
//
// $Date: 4/25/12 9:35a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatchProtocol.c $
// 
// 2     4/25/12 9:35a Victortu
// [TAG]         None
// [Category]    Improvement
// [Description] Reprogram SMM ChildDispatcher drivers.
// [Files]       SmiHandlerGeneric.c; SmiHandlerPorting.c;
// SmiHandlerGeneric2.c; SmmChildDispatch2Main.c; SmmChildDispatcher2.mak;
// SmmChildDispatcher2.sdl; SmmChildDispatch.h; SmmChildDispatchMain.c;
// SmmChildDispatchProtocol.c; SmmChildDispatcher.dxs;
// PchSmiDispatcher.sdl
// 
// 1     2/08/12 8:27a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmmChildDispatchProtocol.c
//
// Description: This file contains SMM Child dispatcher Protocols
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include "SmmChildDispatch.h"
#include "SmmChildDispatchProtocol.h"

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

#if INTEL_RC_SMI_DISPATCHER_SUPPORT == 0
SMM_CHILD_DISPATCHER SmmHandler[] = { 
                                // SwSmmHandler 
                                EfiSmmSwSmi,
                                { SmmSwAddHandler,
                                  SmmSwRemoveHandler,
                                  SmmSwVerifyContext,
                                  SmmSwGetContext,
                                  SmmSwDispatchSmi },
                                { 0, NULL, NULL },

                                // SxSmmHandler
                                EfiSmmSxSmi,
                                { SmmSxAddHandler,
                                  SmmSxRemoveHandler,
                                  SmmSxVerifyContext,
                                  SmmSxGetContext,
                                  SmmSxDispatchSmi },
                                { 0, NULL, NULL },

                                // PeriodicTimerSmmHandler
                                EfiSmmPeriodicTimerSmi,
                                { SmmTimerAddHandler,
                                  SmmTimerRemoveHandler,
                                  SmmTimerVerifyContext,
                                  SmmTimerGetContext,
                                  SmmTimerDispatchSmi },
                                { 0, NULL, NULL },

                                // UsbSmmHandler
                                EfiSmmUsbSmi,
                                { SmmUsbAddHandler,
                                  SmmUsbRemoveHandler,
                                  SmmUsbVerifyContext,
                                  SmmUsbGetContext,
                                  SmmUsbDispatchSmi },
                                { 0, NULL, NULL },

                                // GpiSmmHandler
                                EfiSmmGpiSmi,
                                { SmmGpiAddHandler,
                                  SmmGpiRemoveHandler,
                                  SmmGpiVerifyContext,
                                  SmmGpiGetContext,
                                  SmmGpiDispatchSmi },
                                { 0, NULL, NULL },

                                // SButtonSmmHandler
                                EfiSmmStandbyButtonSmi,
                                { SmmSButtonAddHandler,
                                  SmmSButtonRemoveHandler,
                                  SmmSButtonVerifyContext,
                                  SmmSButtonGetContext,
                                  SmmSButtonDispatchSmi },
                                { 0, NULL, NULL },

                                // PButtonSmmHandler
                                EfiSmmPowerButtonSmi,
                                { SmmPButtonAddHandler,
                                  SmmPButtonRemoveHandler,
                                  SmmPButtonVerifyContext,
                                  SmmPButtonGetContext,
                                  SmmPButtonDispatchSmi },
                                { 0, NULL, NULL },

                                // TcoSmmHandler
                                EfiSmmTcoSmi,
                                { SmmTcoAddHandler,
                                  SmmTcoRemoveHandler,
                                  SmmTcoVerifyContext,
                                  SmmTcoGetContext,
                                  SmmTcoDispatchSmi },
                                { 0, NULL, NULL },

                                // IoTrapSmmHandler
                                EfiSmmIoTrapSmi,
                                { SmmIoTrapAddHandler,
                                  SmmIoTrapRemoveHandler,
                                  SmmIoTrapVerifyContext,
                                  SmmIoTrapGetContext,
                                  SmmIoTrapDispatchSmi },
                                { 0, NULL, NULL },

//********************** PUT ADDITIONAL HANDLERS HERE ***********************
//********************** PUT ADDITIONAL HANDLERS HERE ***********************
//********************** PUT ADDITIONAL HANDLERS HERE ***********************

                                        // Terminator record
                                        EfiSmmMaxSmi,
                                        { NULL, NULL, NULL, NULL, NULL },
                                        { 0, NULL, NULL }
};
#else
SMM_CHILD_DISPATCHER SmmHandler[] = { 
                                // SwSmmHandler 
                                (EfiSmmMaxSmi + 1),
                                { NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL },
                                { 0, NULL, NULL },

                                // SxSmmHandler
                                (EfiSmmMaxSmi + 1),
                                { NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL },
                                { 0, NULL, NULL },

                                // PeriodicTimerSmmHandler
                                (EfiSmmMaxSmi + 1),
                                { NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL },
                                { 0, NULL, NULL },

                                // UsbSmmHandler
                                (EfiSmmMaxSmi + 1),
                                { NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL },
                                { 0, NULL, NULL },

                                // GpiSmmHandler
                                (EfiSmmMaxSmi + 1),
                                { NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL },
                                { 0, NULL, NULL },

                                // SButtonSmmHandler
                                EfiSmmStandbyButtonSmi,
                                { SmmSButtonAddHandler,
                                  SmmSButtonRemoveHandler,
                                  SmmSButtonVerifyContext,
                                  SmmSButtonGetContext,
                                  SmmSButtonDispatchSmi },
                                { 0, NULL, NULL },

                                // PButtonSmmHandler
                                (EfiSmmMaxSmi + 1),
                                { NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL },
                                { 0, NULL, NULL },

                                // TcoSmmHandler
                                (EfiSmmMaxSmi + 1),
                                { NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL },
                                { 0, NULL, NULL },

                                // IoTrapSmmHandler
                                (EfiSmmMaxSmi + 1),
                                { NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL },
                                { 0, NULL, NULL },

//********************** PUT ADDITIONAL HANDLERS HERE ***********************
//********************** PUT ADDITIONAL HANDLERS HERE ***********************
//********************** PUT ADDITIONAL HANDLERS HERE ***********************

                                        // Terminator record
                                        EfiSmmMaxSmi,
                                        { NULL, NULL, NULL, NULL, NULL },
                                        { 0, NULL, NULL }
};
#endif

EFI_SMM_SW_DISPATCH_PROTOCOL gEfiSmmSwDispatchProtocol = \
                                                { EfiSmmSwRegister, \
                                                  EfiSmmSwUnregister, \
                                                  MAX_SW_SMI_INPUT_VALUE };

EFI_SMM_SX_DISPATCH_PROTOCOL gEfiSmmSxDispatchProtocol = \
                                    { EfiSmmSxRegister, EfiSmmSxUnregister };

EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL gEfiSmmPeriodicTimerDispatchProtocol=
                                        { EfiSmmTimerRegister, \
                                          EfiSmmTimerUnregister, \
                                          EfiSmmTimerGetNextShorterInterval };

EFI_SMM_USB_DISPATCH_PROTOCOL gEfiSmmUsbDispatchProtocol = \
                                  { EfiSmmUsbRegister, EfiSmmUsbUnregister };

EFI_SMM_GPI_DISPATCH_PROTOCOL gEfiSmmGpiDispatchProtocol = \
                                                    { EfiSmmGpiRegister, \
                                                      EfiSmmGpiUnregister, \
                                                      SUPPORTED_GPIS };

EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL gEfiSmmStandbyButtonDispatchProtocol=
                            { EfiSmmSButtonRegister, EfiSmmSButtonUnregister };

EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL gEfiSmmPowerButonDispatchProtocol = \
                          { EfiSmmPButtonRegister, EfiSmmPButtonUnregister };

EFI_SMM_TCO_DISPATCH_PROTOCOL gEfiSmmTcoDispatchProtocol = \
                                  { EfiSmmTcoRegister, EfiSmmTcoUnregister };

EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL gEfiSmmIoTrapDispatchProtocol = \
                             { EfiSmmIoTrapRegister, EfiSmmIoTrapUnregister };

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

extern UINT64 gSupportedIntervals[];

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSwRegister
//
// Description: EFI_SMM_SW_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_SW_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSwRegister (
    IN EFI_SMM_SW_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_SW_DISPATCH          Function,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                  *Handle )
{
//#### Use Intel RC    return RegisterHandler( EfiSmmSwSmi, \
//#### Use Intel RC                            Function, \
//#### Use Intel RC                            Context, \
//#### Use Intel RC                            sizeof(EFI_SMM_SW_DISPATCH_CONTEXT), \
//#### Use Intel RC                            Handle );
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSwUnregister
//
// Description: EFI_SMM_SW_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_SW_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSwUnregister (
    IN  EFI_SMM_SW_DISPATCH_PROTOCOL        *This,
    IN  EFI_HANDLE                          Handle )
{
//#### Use Intel RC    return UnregisterHandler( EfiSmmSwSmi, Handle );
    return EFI_NOT_FOUND;
}

//---------------------------------------------------------------------------
//                         Sleep SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSxRegister
//
// Description: EFI_SMM_SX_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_SX_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSxRegister (
    IN EFI_SMM_SX_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_SX_DISPATCH          Function,
    IN EFI_SMM_SX_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                  *Handle )
{
//#### Use Intel RC    return RegisterHandler( EfiSmmSxSmi, \
//#### Use Intel RC                            Function, \
//#### Use Intel RC                            Context, \
//#### Use Intel RC                            sizeof(EFI_SMM_SX_DISPATCH_CONTEXT), \
//#### Use Intel RC                            Handle );
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSxUnregister
//
// Description: EFI_SMM_SW_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_SX_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSxUnregister (
    IN EFI_SMM_SX_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                   Handle )
{
//#### Use Intel RC    return UnregisterHandler( EfiSmmSxSmi, Handle );
    return EFI_NOT_FOUND;
}

//---------------------------------------------------------------------------
//                  Periodic timer SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmTimerRegister
//
// Description: EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmTimerRegister (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH          Function,
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                              *Handle )
{
//#### Use Intel RC    return RegisterHandler( EfiSmmPeriodicTimerSmi, \
//#### Use Intel RC                            Function, \
//#### Use Intel RC                            Context, \
//#### Use Intel RC                            sizeof(EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT), \
//#### Use Intel RC                            Handle );
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmTimerUnregister
//
// Description: EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the 
//                       EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmTimerUnregister (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle )
{
//#### Use Intel RC    return UnregisterHandler( EfiSmmPeriodicTimerSmi, Handle );
    return EFI_NOT_FOUND;;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmTimerGetNextShorterInterval
//
// Description: EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL
//              GetNextShorterInterval function. 
//
// Input:       *This             - Pointer to the
//                                  EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL
//              **SmiTickInterval - Pointer to store pointer to next interval
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmTimerGetNextShorterInterval (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN OUT UINT64                               **SmiTickInterval )
{
    UINT64 *Result = *SmiTickInterval;

    if (Result == NULL) {
        Result = gSupportedIntervals;
    } else {
        Result++;
    }
    *SmiTickInterval = (*Result == 0) ? NULL : Result;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmGetPeriodicTimerSourcesStatus
//
// Description: Gets Periodic Timer sources status.
//
// Input:       None
//
// Output:      BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN EfiSmmGetPeriodicTimerSourcesStatus (VOID)
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                 SmmHandler[EfiSmmPeriodicTimerSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *TimerContext;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC            TimerContext = \
//#### Use Intel RC                 (EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC            if (TimerContext->TimerEnabled) return TRUE;

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmPeriodicTimerEnable
//
// Description: Enables Periodic Timer SMI.
//
// Input:       *This  - Pointer to the
//                       EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL
//              Handle - Handle to enable
//
// Output:      EFI_STATUS
//                  EFI_NOT_FOUND - The specific handle is not found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmPeriodicTimerEnable (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle )
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                 SmmHandler[EfiSmmPeriodicTimerSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *TimerContext;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        if (Handler == Handle) {
//#### Use Intel RC            TimerContext = \
//#### Use Intel RC                 (EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC            TimerContext->TimerEnabled = TRUE;
//#### Use Intel RC            TimerSmiClear();
//#### Use Intel RC            TimerSmiEnable();
//#### Use Intel RC            return EFI_SUCCESS;
//#### Use Intel RC        }

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmPeriodicTimerDisable
//
// Description: Disables Periodic Timer SMI.
//
// Input:       *This  - Pointer to the
//                       EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL
//              Handle - Handle to disable
//
// Output:      EFI_STATUS
//                  EFI_NOT_FOUND - The specific handle is not found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmPeriodicTimerDisable (
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle )
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                 SmmHandler[EfiSmmPeriodicTimerSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *TimerContext;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        if (Handler == Handle) {
//#### Use Intel RC            TimerContext = \
//#### Use Intel RC                 (EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC            TimerContext->TimerEnabled = FALSE;
//#### Use Intel RC            if (!EfiSmmGetPeriodicTimerSourcesStatus())
//#### Use Intel RC                TimerSmiDisable();
//#### Use Intel RC            return EFI_SUCCESS;
//#### Use Intel RC        }

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }
    return EFI_NOT_FOUND;
}

//---------------------------------------------------------------------------
//                         USB SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmUsbRegister
//
// Description: EFI_SMM_USB_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_USB_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmUsbRegister (
    IN EFI_SMM_USB_DISPATCH_PROTOCOL    *This,
    IN EFI_SMM_USB_DISPATCH             Function,
    IN EFI_SMM_USB_DISPATCH_CONTEXT     *Context,
    OUT EFI_HANDLE                      *Handle )
{
//#### Use Intel RC    return RegisterHandler( EfiSmmUsbSmi, \
//#### Use Intel RC                            Function, \
//#### Use Intel RC                            Context, \
//#### Use Intel RC                            sizeof(EFI_SMM_USB_DISPATCH_CONTEXT), \
//#### Use Intel RC                            Handle );
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmUsbUnregister
//
// Description: EFI_SMM_USB_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_USB_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmUsbUnregister (
    IN EFI_SMM_USB_DISPATCH_PROTOCOL    *This,
    IN EFI_HANDLE                       Handle )
{
//#### Use Intel RC    return UnregisterHandler( EfiSmmUsbSmi, Handle );
    return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
//                         GPI SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmGpiRegister
//
// Description: EFI_SMM_GPI_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_GPI_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmGpiRegister (
    IN EFI_SMM_GPI_DISPATCH_PROTOCOL    *This,
    IN EFI_SMM_GPI_DISPATCH             Function,
    IN EFI_SMM_GPI_DISPATCH_CONTEXT     *Context,
    OUT EFI_HANDLE                      *Handle )
{
//#### Use Intel RC    return RegisterHandler( EfiSmmGpiSmi, \
//#### Use Intel RC                            Function, \
//#### Use Intel RC                            Context,  \
//#### Use Intel RC                            sizeof(EFI_SMM_GPI_DISPATCH_CONTEXT), \
//#### Use Intel RC                            Handle );
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmGpiUnregister
//
// Description: EFI_SMM_GPI_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_GPI_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmGpiUnregister (
    IN EFI_SMM_GPI_DISPATCH_PROTOCOL    *This,
    IN EFI_HANDLE                       Handle )
{
//#### Use Intel RC    return UnregisterHandler( EfiSmmGpiSmi, Handle );
    return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
//                    Standby button SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSButtonRegister
//
// Description: EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSButtonRegister (
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH          Function,
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                              *Handle )
{
    return RegisterHandler( EfiSmmStandbyButtonSmi, \
                            Function, \
                            Context, \
                            sizeof(EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT), \
                            Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSButtonUnregister
//
// Description: EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the
//                       EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSButtonUnregister (
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle )
{
    return UnregisterHandler( EfiSmmStandbyButtonSmi, Handle );
}

//---------------------------------------------------------------------------
//                    Power button SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmPButtonRegister
//
// Description: EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmPButtonRegister (
    IN EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL   *This,
    IN EFI_SMM_POWER_BUTTON_DISPATCH            Function,
    IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT    *Context,
    OUT EFI_HANDLE                              *Handle )
{
#if INTEL_RC_SMI_DISPATCHER_SUPPORT == 0
    return RegisterHandler( EfiSmmPowerButtonSmi,
                            Function,
                            Context,
                            sizeof(EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT),
                            Handle );
#else
    return EFI_UNSUPPORTED;
#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmPButtonUnregister
//
// Description: EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmPButtonUnregister (
    IN EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                               Handle )
{
#if INTEL_RC_SMI_DISPATCHER_SUPPORT == 0
    return UnregisterHandler( EfiSmmPowerButtonSmi, Handle );
#else
    return EFI_UNSUPPORTED;
#endif
}

//---------------------------------------------------------------------------
//                         TCO SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmTcoRegister
//
// Description: EFI_SMM_TCO_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_TCO_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmTcoRegister (
    IN EFI_SMM_TCO_DISPATCH_PROTOCOL    *This,
    IN EFI_SMM_TCO_DISPATCH             Function,
    IN EFI_SMM_TCO_DISPATCH_CONTEXT     *Context,
    OUT EFI_HANDLE                      *Handle )
{
//#### Use Intel RC    return RegisterHandler( EfiSmmTcoSmi, \
//#### Use Intel RC                            Function, \
//#### Use Intel RC                            Context, \
//#### Use Intel RC                            sizeof(EFI_SMM_TCO_DISPATCH_CONTEXT), \
//#### Use Intel RC                            Handle );
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmTcoUnregister
//
// Description: EFI_SMM_TCO_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_TCO_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmTcoUnregister (
    IN EFI_SMM_TCO_DISPATCH_PROTOCOL    *This,
    IN EFI_HANDLE                       Handle )
{
//#### Use Intel RC    return UnregisterHandler( EfiSmmTcoSmi, Handle );
    return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
//                       I/O Trap SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmIoTrapRegister
//
// Description: EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmIoTrapRegister (
    IN EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL    *This,
    IN EFI_SMM_IO_TRAP_DISPATCH             Function,
    IN EFI_SMM_IO_TRAP_DISPATCH_CONTEXT     *Context,
    OUT EFI_HANDLE                          *Handle )
{
//#### Use Intel RC     return RegisterHandler( EfiSmmIoTrapSmi, \
//#### Use Intel RC                            Function, \
//#### Use Intel RC                            Context, \
//#### Use Intel RC                            sizeof(EFI_SMM_IO_TRAP_DISPATCH_CONTEXT), \
//#### Use Intel RC                            Handle );
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmIoTrapUnregister
//
// Description: EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmIoTrapUnregister (
    IN EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL    *This,
    IN EFI_HANDLE                           Handle )
{
//#### Use Intel RC    return UnregisterHandler( EfiSmmIoTrapSmi, Handle );
    return EFI_SUCCESS;
}

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
