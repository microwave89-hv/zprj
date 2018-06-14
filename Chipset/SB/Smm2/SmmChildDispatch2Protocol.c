#pragma optimize ("", off)
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatch2Protocol.c 1     2/08/12 8:28a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:28a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatch2Protocol.c $
// 
// 1     2/08/12 8:28a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmmChildDispatch2Protocol.c
//
// Description: This file contains SMM Child dispatcher II Protocols
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include "SmmChildDispatch2.h"
#include "SmmChildDispatch2Protocol.h"

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

SMM_CHILD_DISPATCHER2 Smm2Handler[] = { 
                                        // SwSmmHandler 
                                        EfiSmmSwSmi2,
                                        { SmmSwAddHandler2, \
                                          SmmSwRemoveHandler2, \
                                          SmmSwVerifyContext2, \
                                          SmmSwGetContext2, \
                                          SmmSwDispatchSmi2 },
                                          { 0, NULL, NULL },

                                        // SxSmmHandler
                                        EfiSmmSxSmi2,
                                        { SmmSxAddHandler2, \
                                          SmmSxRemoveHandler2, \
                                          SmmSxVerifyContext2, \
                                          SmmSxGetContext2, \
                                          SmmSxDispatchSmi2 },
                                        { 0, NULL, NULL },

                                        // PeriodicTimerSmmHandler
                                        EfiSmmPeriodicTimerSmi2,
                                        { SmmTimerAddHandler2, \
                                          SmmTimerRemoveHandler2, \
                                          SmmTimerVerifyContext2, \
                                          SmmTimerGetContext2, \
                                          SmmTimerDispatchSmi2 },
                                        { 0, NULL, NULL },

                                        // UsbSmmHandler
                                        EfiSmmUsbSmi2,
                                        { SmmUsbAddHandler2, \
                                          SmmUsbRemoveHandler2, \
                                          SmmUsbVerifyContext2, \
                                          SmmUsbGetContext2, \
                                          SmmUsbDispatchSmi2 },
                                        { 0, NULL, NULL },

                                        // GpiSmmHandler
                                        EfiSmmGpiSmi2,
                                        { SmmGpiAddHandler2, \
                                          SmmGpiRemoveHandler2, \
                                          SmmGpiVerifyContext2, \
                                          SmmGpiGetContext2, \
                                          SmmGpiDispatchSmi2 },
                                        { 0, NULL, NULL },

                                        // SButtonSmmHandler
                                        EfiSmmStandbyButtonSmi2,
                                        { SmmSButtonAddHandler2, \
                                          SmmSButtonRemoveHandler2, \
                                          SmmSButtonVerifyContext2, \
                                          SmmSButtonGetContext2, \
                                          SmmSButtonDispatchSmi2 },
                                        { 0, NULL, NULL },

                                        // PButtonSmmHandler
                                        EfiSmmPowerButtonSmi2,
                                        { SmmPButtonAddHandler2, \
                                          SmmPButtonRemoveHandler2, \
                                          SmmPButtonVerifyContext2, \
                                          SmmPButtonGetContext2, \
                                          SmmPButtonDispatchSmi2 },
                                        { 0, NULL, NULL },

                                        // IoTrapSmmHandler
                                        EfiSmmIoTrapSmi2,
                                        { SmmIoTrapAddHandler2, \
                                          SmmIoTrapRemoveHandler2, \
                                          SmmIoTrapVerifyContext2, \
                                          SmmIoTrapGetContext2, \
                                          SmmIoTrapDispatchSmi2 },
                                        { 0, NULL, NULL },

//********************** PUT ADDITIONAL HANDLERS HERE ***********************
//********************** PUT ADDITIONAL HANDLERS HERE ***********************
//********************** PUT ADDITIONAL HANDLERS HERE ***********************

                                        // Terminator record
                                        EfiSmmMaxSmi2,
                                        { NULL, NULL, NULL, NULL, NULL },
                                        { 0, NULL, NULL }
};

EFI_SMM_SW_DISPATCH2_PROTOCOL gEfiSmmSwDispatch2Protocol = \
                                                { EfiSmmSwRegister2, \
                                                  EfiSmmSwUnregister2, \
                                                  MAX_SW_SMI_INPUT_VALUE };

EFI_SMM_SX_DISPATCH2_PROTOCOL gEfiSmmSxDispatch2Protocol = \
                                  { EfiSmmSxRegister2, EfiSmmSxUnregister2 };

EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL \
                                    gEfiSmmPeriodicTimerDispatch2Protocol = \
                                       { EfiSmmTimerRegister2, \
                                         EfiSmmTimerUnregister2, \
                                         EfiSmmTimerGetNextShorterInterval2 };

EFI_SMM_USB_DISPATCH2_PROTOCOL gEfiSmmUsbDispatch2Protocol = \
                                { EfiSmmUsbRegister2, EfiSmmUsbUnregister2 };

EFI_SMM_GPI_DISPATCH2_PROTOCOL gEfiSmmGpiDispatch2Protocol = \
                                                   { EfiSmmGpiRegister2, \
                                                     EfiSmmGpiUnregister2, \
                                                     SUPPORTED_GPIS };

EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL \
                                    gEfiSmmStandbyButtonDispatch2Protocol = \
                         { EfiSmmSButtonRegister2, EfiSmmSButtonUnregister2 };

EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL gEfiSmmPowerButonDispatch2Protocol = \
                        { EfiSmmPButtonRegister2, EfiSmmPButtonUnregister2 };


EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL gEfiSmmIoTrapDispatch2Protocol = \
                           { EfiSmmIoTrapRegister2, EfiSmmIoTrapUnregister2 };


// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

extern UINT64 gSupportedIntervals[];

// Function Definition(s)

//---------------------------------------------------------------------------
//                          S/W SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSwRegister2
//
// Description: EFI_SMM_SW_DISPATCH2_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_SW_DISPATCH2_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSwRegister2 (
    IN  CONST EFI_SMM_SW_DISPATCH2_PROTOCOL     *This,
    IN        EFI_SMM_HANDLER_ENTRY_POINT2      Function,
    IN  CONST EFI_SMM_SW_REGISTER_CONTEXT       *Context,
    OUT       EFI_HANDLE                        *Handle )
{
    return RegisterHandler2( EfiSmmSwSmi2, \
                             Function, \
                             Context, \
                             sizeof(EFI_SMM_SW_REGISTER_CONTEXT), \
                             Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSwUnregister2
//
// Description: EFI_SMM_SW_DISPATCH2_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_SW_DISPATCH2_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSwUnregister2 (
    IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL      *This,
    IN       EFI_HANDLE                         Handle )
{
    return UnregisterHandler2( EfiSmmSwSmi2, Handle );
}

//---------------------------------------------------------------------------
//                         Sleep SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSxRegister2
//
// Description: EFI_SMM_SX_DISPATCH2_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_SX_DISPATCH2_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSxRegister2 (
    IN  CONST EFI_SMM_SX_DISPATCH2_PROTOCOL     *This,
    IN        EFI_SMM_HANDLER_ENTRY_POINT2      Function,
    IN  CONST EFI_SMM_SX_REGISTER_CONTEXT       *Context,
    OUT       EFI_HANDLE                        *Handle )
{
    return RegisterHandler2( EfiSmmSxSmi2, \
                             Function, \
                             Context, \
                             sizeof(EFI_SMM_SX_REGISTER_CONTEXT), \
                             Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSxUnregister2
//
// Description: EFI_SMM_SW_DISPATCH2_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_SX_DISPATCH2_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSxUnregister2 (
    IN CONST EFI_SMM_SX_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                    Handle )
{
    return UnregisterHandler2( EfiSmmSxSmi2, Handle );
}

//---------------------------------------------------------------------------
//                  Periodic timer SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmTimerRegister2
//
// Description: EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL Register function.
//
// Input:       *This    - Pointer to 
//                         EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmTimerRegister2 (
    IN  CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN        EFI_SMM_HANDLER_ENTRY_POINT2              Function,
    IN  CONST EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT   *Context,
    OUT       EFI_HANDLE                                *Handle )
{
    EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT ExContext;
	TRACE ((TRACE_ALWAYS, "EfiSmmTimerRegister2 \n"));
    ExContext.OrgContext = *Context;
    ExContext.ElapsedTime = 0;

    return RegisterHandler2( EfiSmmPeriodicTimerSmi2, \
                        Function, \
                        &ExContext, \
                        sizeof(EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT), \
                        Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmTimerUnregister2
//
// Description: EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the 
//                       EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmTimerUnregister2 (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                                Handle )
{
	TRACE ((TRACE_ALWAYS, "EfiSmmTimerUnregister2 \n"));
    return UnregisterHandler2( EfiSmmPeriodicTimerSmi2, Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmTimerGetNextShorterInterval2
//
// Description: EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL
//              GetNextShorterInterval function. 
//
// Input:       *This             - Pointer to the
//                                  EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL
//              **SmiTickInterval - Pointer to store pointer to next interval
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmTimerGetNextShorterInterval2 (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN OUT   UINT64                                    **SmiTickInterval )
{
    UINT64 *Result = *SmiTickInterval;
	TRACE ((TRACE_ALWAYS, "EfiSmmTimerGetNextShorterInterval2 \n"));
    if (Result == NULL) {
        Result = gSupportedIntervals;
    } else {
        Result++;
    }
    *SmiTickInterval = (*Result == 0) ? NULL : Result;

    return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
//                         USB SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmUsbRegister2
//
// Description: EFI_SMM_USB_DISPATCH2_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_USB_DISPATCH2_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmUsbRegister2 (
    IN  CONST EFI_SMM_USB_DISPATCH2_PROTOCOL    *This,
    IN        EFI_SMM_HANDLER_ENTRY_POINT2      Function,
    IN  CONST EFI_SMM_USB_REGISTER_CONTEXT      *Context,
    OUT       EFI_HANDLE                        *Handle )
{
    return RegisterHandler2( EfiSmmUsbSmi2, \
                             Function, \
                             Context, \
                             sizeof(EFI_SMM_USB_REGISTER_CONTEXT), \
                             Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmUsbUnregister2
//
// Description: EFI_SMM_USB_DISPATCH2_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_USB_DISPATCH2_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmUsbUnregister2 (
    IN CONST EFI_SMM_USB_DISPATCH2_PROTOCOL  *This,
    IN       EFI_HANDLE                      Handle )
{
    return UnregisterHandler2( EfiSmmUsbSmi2, Handle );
}

//---------------------------------------------------------------------------
//                         GPI SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmGpiRegister2
//
// Description: EFI_SMM_GPI_DISPATCH2_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_GPI_DISPATCH2_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmGpiRegister2 (
    IN CONST EFI_SMM_GPI_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2   Function,
    IN CONST EFI_SMM_GPI_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                     *Handle )
{
    return RegisterHandler2( EfiSmmGpiSmi2, \
                             Function, \
                             Context,  \
                             sizeof(EFI_SMM_GPI_REGISTER_CONTEXT), \
                             Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmGpiUnregister2
//
// Description: EFI_SMM_GPI_DISPATCH2_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_GPI_DISPATCH2_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmGpiUnregister2 (
    IN CONST EFI_SMM_GPI_DISPATCH2_PROTOCOL  *This,
    IN       EFI_HANDLE                      Handle )
{
    return UnregisterHandler2( EfiSmmGpiSmi2, Handle );
}

//---------------------------------------------------------------------------
//                    Standby button SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSButtonRegister2
//
// Description: EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL Register function.
//
// Input:       *This    - Pointer to
//                         EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSButtonRegister2 (
    IN CONST EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2              Function,
    IN CONST EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                                *Handle )
{
    return RegisterHandler2( EfiSmmStandbyButtonSmi2, \
                             Function, \
                             Context, \
                             sizeof(EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT),\
                             Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmSButtonUnregister2
//
// Description: EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the
//                       EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmSButtonUnregister2 (
    IN CONST EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                                Handle )
{
    return UnregisterHandler2( EfiSmmStandbyButtonSmi2, Handle );
}

//---------------------------------------------------------------------------
//                    Power button SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmPButtonRegister2
//
// Description: EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to callback context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmPButtonRegister2 (
    IN CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2            Function,
    IN CONST EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                              *Handle )
{
    return RegisterHandler2( EfiSmmPowerButtonSmi2, \
                             Function, \
                             Context, \
                             sizeof(EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT), \
                             Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmPButtonUnregister2
//
// Description: EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the
//                       EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmPButtonUnregister2 (
    IN CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                              Handle )
{
    return UnregisterHandler2( EfiSmmPowerButtonSmi2, Handle );
}

//---------------------------------------------------------------------------
//                       I/O Trap SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmIoTrapRegister2
//
// Description: EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL Register function.
//
// Input:       *This    - Pointer to EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL
//              Function - Pointer to callback function
//              *Context - Pointer to register context
//              *Handle  - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmIoTrapRegister2 (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2       Function,
    IN OUT   EFI_SMM_IO_TRAP_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                         *Handle)
{
    return RegisterHandler2( EfiSmmIoTrapSmi2, \
                             Function, \
                             Context, \
                             sizeof(EFI_SMM_IO_TRAP_REGISTER_CONTEXT), \
                             Handle );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiSmmIoTrapUnregister2
//
// Description: EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL Unregister function.
//
// Input:       *This  - Pointer to the EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL
//              Handle - Handle to unregister
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EfiSmmIoTrapUnregister2 (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                         Handle )
{
    return UnregisterHandler2( EfiSmmIoTrapSmi2, Handle );
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
