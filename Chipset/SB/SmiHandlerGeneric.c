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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmiHandlerGeneric.c 2     4/25/12 9:35a Victortu $
//
// $Revision: 2 $
//
// $Date: 4/25/12 9:35a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmiHandlerGeneric.c $
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
// Name:        SmiHandlerGeneric.c
//
// Description: This file contains implementation of generic SMI handler
//              functions 
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include "SmmChildDispatch.h"
#include <DXE.h>
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

static UINT64 gCurrentInterval  = 0xffffffffffffffff;
static UINT16 gEnabledUsbSmi    = 0;
static UINT16 gActiveUsbSmi     = 0;
static UINT32 gEnabledGpiSmi    = 0;
static UINT32 gEnabledTcoSmi    = 0;
static UINT32 gEnabledIoTrapSmi = 0;
static UINT32 gIoTrapWriteData  = 0;

BOOLEAN     gIsLastState = FALSE;

// GUID Definition(s)
EFI_GUID gDxeGuid = DXE_SERVICES_TABLE_GUID;

// Protocol Definition(s)

// External Declaration(s)

extern EFI_SMM_SYSTEM_TABLE *pSmst;
extern SMM_CHILD_DISPATCHER SmmHandler[];
extern EFI_SMM_SMI_CONTEXT  SmiContext;

extern UINT64 gSupportedIntervals[];

// Function Definition(s)

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//                       Software SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwAddHandler
//
// Description: This function adds SW SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSwAddHandler (
    IN VOID             *Context )
{
//#### Use Intel RC     if (SmmHandler[EfiSmmSwSmi].RegisteredCallbacks.Size == 1) SwSmiEnable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwRemoveHandler
//
// Description: This function removes SW SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSwRemoveHandler (
    IN VOID             *Context )
{
//#### Use Intel RC    if (SmmHandler[EfiSmmSwSmi].RegisteredCallbacks.Size == 1) SwSmiDisable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwVerifyContext
//
// Description: This function verifies SW SMI context
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS - Context verified
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSwVerifyContext (
    IN VOID             *Context )
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                            SmmHandler[EfiSmmSwSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_SW_DISPATCH_CONTEXT *SwContext;
//#### Use Intel RC    EFI_SMM_SW_DISPATCH_CONTEXT *RegisteredSwContext;

//#### Use Intel RC    SwContext = (EFI_SMM_SW_DISPATCH_CONTEXT *)Context;
//#### Use Intel RC    // First check if we already registered handler for this value
//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        RegisteredSwContext = (EFI_SMM_SW_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC        if(SwContext->SwSmiInputValue == RegisteredSwContext->SwSmiInputValue)
//#### Use Intel RC            // Handler with this value already registered 
//#### Use Intel RC            return EFI_INVALID_PARAMETER;       

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    // Second check if given value is extended SMI value, 
//#### Use Intel RC    // check the lowest byte  
//#### Use Intel RC    if ((SwContext->SwSmiInputValue & 0xff) == EXTENDED_SMI)
//#### Use Intel RC        return EFI_SUCCESS;     // Accept value of UINTN size

//#### Use Intel RC    // Third check if given value is in default range
//#### Use Intel RC    return (SwContext->SwSmiInputValue > MAX_SW_SMI_INPUT_VALUE) ? \
//#### Use Intel RC                                          EFI_INVALID_PARAMETER : EFI_SUCCESS;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwGetContext
//
// Description: This function verifies SW SMI event and sets SW SMI context
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - SW SMI occured, context saved
//                  FALSE - There was no SW SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmSwGetContext (VOID)
{
    UINT16      SwSmiNumber;
    BOOLEAN     SwSmiDetected;

    // use intel ref code 
    return FALSE;

    SwSmiDetected = SwSmiDetect( &SwSmiNumber );

    if (SwSmiDetected) {
        if(SwSmiNumber == EXTENDED_SMI) {
            // Get the actual number from EAX register 
            SmiContext.SwContext.SwSmiInputValue = GetEAX();
        } else {
            SmiContext.SwContext.SwSmiInputValue = SwSmiNumber;
        }
    }

    return SwSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwDispatchSmi
//
// Description: This function dispatches SW SMI event based on context
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmSwDispatchSmi (VOID)
{
//#### Use Intel RC    HANDLER_LINK                *Handler;
//#### Use Intel RC    EFI_SMM_SW_DISPATCH_CONTEXT *SwContext;

//#### Use Intel RC    Handler = \
//#### Use Intel RC            (HANDLER_LINK *)SmmHandler[EfiSmmSwSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        SwContext = (EFI_SMM_SW_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC        if(SwContext->SwSmiInputValue == SmiContext.SwContext.SwSmiInputValue)
//#### Use Intel RC            Handler->Callback(Handler, SwContext);

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    SwSmiClear();
}

//---------------------------------------------------------------------------
//                        Sleep SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxAddHandler
//
// Description: This function adds Sx SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSxAddHandler (
    IN VOID             *Context )
{
//#### Use Intel RC#if SLP_SMI_ENABLE_ON_REGISTER
//#### Use Intel RC    if (SmmHandler[EfiSmmSxSmi].RegisteredCallbacks.Size == 1) SxSmiEnable();
//#### Use Intel RC#endif
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxRemoveHandler
//
// Description: This function removes Sx SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSxRemoveHandler (
    IN VOID             *Context )
{
//#### Use Intel RC    if (SmmHandler[EfiSmmSxSmi].RegisteredCallbacks.Size == 1) SxSmiDisable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxVerifyContext
//
// Description: This function verifies Sx SMI context
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - Context verified
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSxVerifyContext (
    IN VOID                 *Context )
{
    EFI_SMM_SX_DISPATCH_CONTEXT *SxContext;

    SxContext = (EFI_SMM_SX_DISPATCH_CONTEXT *)Context;
    if ((SxContext->Type >= EfiMaximumSleepType) || \
                                        (SxContext->Phase >= EfiMaximumPhase))
        return EFI_INVALID_PARAMETER;

    return ((SxContext->Phase) != SxExit) ? EFI_UNSUPPORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxGetContext
//
// Description: This function verifies Sx SMI event and sets SX SMI context
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - Sx SMI occured, context saved
//                  FALSE - There was no SX SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmSxGetContext (VOID)
{
    UINT16      SxSleepState;
    BOOLEAN     SxSmiDetected;
    // use intel ref code 
    return FALSE;

    SxSmiDetected = SxSmiDetect( &SxSleepState );

    SmiContext.SxContext.Type = SxSleepState;
    SmiContext.SxContext.Phase = SxEntry;

    return SxSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxDispatchSmi
//
// Description: This function dispatches Sx SMI event based on context
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmSxDispatchSmi (VOID)
{
//#### Use Intel RC    HANDLER_LINK                *Handler;
//#### Use Intel RC    EFI_SMM_SX_DISPATCH_CONTEXT *SxContext;

//#### Use Intel RC    Handler = \
//#### Use Intel RC            (HANDLER_LINK *)SmmHandler[EfiSmmSxSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        SxContext = (EFI_SMM_SX_DISPATCH_CONTEXT *)Handler->Context;

//#### Use Intel RC        if ((SxContext->Type == SmiContext.SxContext.Type) && \
//#### Use Intel RC                            (SxContext->Phase == SmiContext.SxContext.Phase))
//#### Use Intel RC            Handler->Callback(Handler, SxContext);

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    SxSmiClear();

//#### Use Intel RC    if (SmiContext.SxContext.Type == SxS0) return;

//#### Use Intel RC    PutToSleep( &(SmiContext.SxContext) );

    // Control returns here on S1.

//#### Use Intel RC    SxSmiClear();
}

//---------------------------------------------------------------------------
//                    Periodic timer SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerAddHandler
//
// Description: This function adds Periodic timer SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTimerAddHandler (
    IN VOID                 *Context )
{
//#### Use Intel RC    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *TimerContext;

//#### Use Intel RC    TimerContext = (EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Context;

//#### Use Intel RC    TimerContext->TimerEnabled = TRUE;

//#### Use Intel RC    if (SmmHandler[EfiSmmPeriodicTimerSmi].RegisteredCallbacks.Size == 1) {
//#### Use Intel RC        gCurrentInterval = TimerContext->SmiTickInterval;
//#### Use Intel RC        TimerSetInterval( TimerContext->SmiTickInterval );
//#### Use Intel RC        TimerSmiClear();
//#### Use Intel RC        TimerSmiEnable();
//#### Use Intel RC        return EFI_SUCCESS;
//#### Use Intel RC    }

//#### Use Intel RC    if (gCurrentInterval > TimerContext->SmiTickInterval) {
//#### Use Intel RC        gCurrentInterval = TimerContext->SmiTickInterval;
//#### Use Intel RC        TimerSetInterval( TimerContext->SmiTickInterval );
//#### Use Intel RC    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerRemoveHandler
//
// Description: This function removes Periodic timer SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTimerRemoveHandler (
    IN VOID                 *Context )
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                 SmmHandler[EfiSmmPeriodicTimerSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *TimerContext;
//#### Use Intel RC    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *CurrentTimerContext;
//#### Use Intel RC    UINT64                                  Interval = 0xffffffffffffffff;

//#### Use Intel RC    UINT16      CurrentIntervalCounter = 0;
//#### Use Intel RC    UINT64      *SupportedIntervals = gSupportedIntervals;

//#### Use Intel RC    ((EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Context)->TimerEnabled = \
//#### Use Intel RC                                                                        FALSE;

//#### Use Intel RC    if (SmmHandler[EfiSmmPeriodicTimerSmi].RegisteredCallbacks.Size == 1) {
//#### Use Intel RC        gCurrentInterval = 0xffffffffffffffff;
//#### Use Intel RC        TimerSmiDisable();
//#### Use Intel RC        return EFI_SUCCESS;
//#### Use Intel RC    }

//#### Use Intel RC    CurrentTimerContext = (EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Context;
//#### Use Intel RC    while (Handler != NULL) {    
//#### Use Intel RC        TimerContext = \
//#### Use Intel RC                  (EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC        if (Interval > TimerContext->SmiTickInterval)
//#### Use Intel RC            Interval = TimerContext->SmiTickInterval;
//#### Use Intel RC        if (TimerContext->SmiTickInterval == \
//#### Use Intel RC                                         CurrentTimerContext->SmiTickInterval)
//#### Use Intel RC            CurrentIntervalCounter++;
//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    if ((Interval == CurrentTimerContext->SmiTickInterval) && \
//#### Use Intel RC                                              (CurrentIntervalCounter == 1)) {
//#### Use Intel RC        Interval = 0xffffffffffffffff;
//#### Use Intel RC        while (*SupportedIntervals != 0) {
//#### Use Intel RC            if (*SupportedIntervals != CurrentTimerContext->SmiTickInterval)
//#### Use Intel RC                if (*SupportedIntervals < Interval)
//#### Use Intel RC                    Interval = *SupportedIntervals;
//#### Use Intel RC            SupportedIntervals++;
//#### Use Intel RC        }
//#### Use Intel RC    }

//#### Use Intel RC    // This means lowest rate timer no longer active 
//#### Use Intel RC    if (gCurrentInterval < Interval) {
//#### Use Intel RC        gCurrentInterval = Interval;
//#### Use Intel RC        TimerSetInterval( Interval );
//#### Use Intel RC    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerVerifyContext
//
// Description: This function verifies Periodic timer SMI context
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS           - Context verified
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTimerVerifyContext (
    IN VOID                 *Context )
{
    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *TimerContext;
    UINT64                                  *Interval = gSupportedIntervals;

    TimerContext = (EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Context;
    while (*Interval != 0) {
        if (*Interval == TimerContext->SmiTickInterval) return EFI_SUCCESS;
        Interval++;
    }

    return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerGetContext
//
// Description: This function verifies Periodic timer SMI event and sets
//              Periodic timer SMI context 
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - Periodic timer SMI occured, context saved
//                  FALSE - There was no Periodic timer SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmTimerGetContext (VOID)
{
    UINT16      TimerType;
    BOOLEAN     TimerSmiDetected;

    // use intel ref code 
    return FALSE;

    TimerSmiDetected = TimerSmiDetect( &TimerType );
    SmiContext.TimerContext.SmiTickInterval = gCurrentInterval;

    return TimerSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerDispatchSmi
//
// Description: This function dispatches Periodic timer SMI event based on
//              context
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmTimerDispatchSmi (VOID)
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                 SmmHandler[EfiSmmPeriodicTimerSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *TimerContext;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        TimerContext = \
//#### Use Intel RC                 (EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT *)Handler->Context;

//#### Use Intel RC        if (TimerContext->TimerEnabled) {
//#### Use Intel RC            TimerContext->ElapsedTime += \
//#### Use Intel RC                                     SmiContext.TimerContext.SmiTickInterval;
//#### Use Intel RC            if ((TimerContext->ElapsedTime) >= (TimerContext->Period)) {
//#### Use Intel RC                Handler->Callback(Handler, TimerContext);
//#### Use Intel RC                TimerContext->ElapsedTime = 0;
//#### Use Intel RC            }
//#### Use Intel RC        }
//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    TimerSmiClear();
}

//---------------------------------------------------------------------------
//                            USB SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbAddHandler
//
// Description: This function adds USB SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmUsbAddHandler (
    IN VOID             *Context
)
{
    EFI_STATUS                   Status;
    EFI_SMM_USB_DISPATCH_CONTEXT *UsbContext;
    UINT16                       ControllerType;
    VOID                         *NewDp;
    UINTN                        Length;

    UsbContext = (EFI_SMM_USB_DISPATCH_CONTEXT *)Context;

    // Save USB device path protocol into SMM memory
    Length = DPLength( UsbContext->Device );
    Status = pSmst->SmmAllocatePool( 0, Length, &NewDp );
    if (EFI_ERROR(Status)) return Status;
    MemCpy( NewDp, UsbContext->Device, Length );
    UsbContext->Device = (EFI_DEVICE_PATH_PROTOCOL *)NewDp;

    ControllerType = GetControllerType( UsbContext->Device );
    if((ControllerType & gEnabledUsbSmi) == 0) {
        gEnabledUsbSmi |= ControllerType;
        UsbSmiSet( gEnabledUsbSmi );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbRemoveHandler
//
// Description: This function removes USB SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmUsbRemoveHandler (
    IN VOID             *Context )
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                           SmmHandler[EfiSmmUsbSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_USB_DISPATCH_CONTEXT *UsbContext;
//#### Use Intel RC    UINT16                       ControllerType = 0;

//#### Use Intel RC    UsbContext = (EFI_SMM_USB_DISPATCH_CONTEXT *)Context;

//#### Use Intel RC    pSmst->SmmFreePool( UsbContext->Device );

//#### Use Intel RC    if (SmmHandler[EfiSmmUsbSmi].RegisteredCallbacks.Size == 1) {
//#### Use Intel RC        gEnabledUsbSmi = 0;
//#### Use Intel RC        UsbSmiSet( gEnabledUsbSmi );
//#### Use Intel RC        return EFI_SUCCESS;
//#### Use Intel RC    }

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        UsbContext = (EFI_SMM_USB_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC        ControllerType |= GetControllerType( UsbContext->Device );
//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    if (ControllerType != gEnabledUsbSmi) {
//#### Use Intel RC        gEnabledUsbSmi = ControllerType;
//#### Use Intel RC        UsbSmiSet( gEnabledUsbSmi );
//#### Use Intel RC    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbVerifyContext
//
// Description: This function verifies USB SMI context
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS           - Context verified
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmUsbVerifyContext ( 
    IN VOID                 *Context )
{
    EFI_SMM_USB_DISPATCH_CONTEXT    *UsbContext;
    UINT16                          ControllerType;

    UsbContext = (EFI_SMM_USB_DISPATCH_CONTEXT *)Context;
    ControllerType = GetControllerType( UsbContext->Device );
    if (((ControllerType & 3) == 0) || (UsbContext->Type > UsbWake))
        return EFI_INVALID_PARAMETER;

    return ((UsbContext->Type) > UsbLegacy) ? EFI_UNSUPPORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbGetContext
//
// Description: This function verifies USB SMI event and sets USB SMI context
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - USB SMI occured, context saved
//                  FALSE - There was no USB SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmUsbGetContext (VOID)
{
    BOOLEAN     UsbSmiDetected;
    // use intel ref code 
    return FALSE;

    UsbSmiDetected = UsbSmiDetect( &gActiveUsbSmi );
    SmiContext.UsbContext.Type = UsbLegacy;

    return UsbSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbDispatchSmi
//
// Description: This function dispatches USB SMI event based on context
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmUsbDispatchSmi (VOID)
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                           SmmHandler[EfiSmmUsbSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_USB_DISPATCH_CONTEXT *UsbContext;
//#### Use Intel RC    UINT16                       ControllerType;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        UsbContext = (EFI_SMM_USB_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC        ControllerType = GetControllerType( UsbContext->Device );

//#### Use Intel RC        if (((ControllerType & gActiveUsbSmi) != 0) && \
//#### Use Intel RC                            (UsbContext->Type == SmiContext.UsbContext.Type))
//#### Use Intel RC            Handler->Callback(Handler, UsbContext);

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    UsbSmiClear( gActiveUsbSmi );

//#### Use Intel RC    gActiveUsbSmi = 0;
}

//---------------------------------------------------------------------------
//                          GPI SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiAddHandler
//
// Description: This function adds GPI SMI handler
//
// Input:       VOID *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmGpiAddHandler (
    IN VOID             *Context )
{
    EFI_SMM_GPI_DISPATCH_CONTEXT    *GpiContext;

    GpiContext = (EFI_SMM_GPI_DISPATCH_CONTEXT *)Context;
    if (((UINT32)(GpiContext->GpiNum) & gEnabledGpiSmi) == 0) {
        gEnabledGpiSmi |= (UINT32)(GpiContext->GpiNum);
        GpiSmiSet( (UINT32)(GpiContext->GpiNum) );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiRemoveHandler
//
// Description: This function removes GPI SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmGpiRemoveHandler (
    IN VOID             *Context )
{
    UINTN   RemoveGpiSmi = ((EFI_SMM_GPI_DISPATCH_CONTEXT *)Context)->GpiNum;

    gEnabledGpiSmi &= ~((UINT32)RemoveGpiSmi);

    GpiSmiReset( (UINT32)RemoveGpiSmi );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiVerifyContext
//
// Description: This function verifies GPI SMI context
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS - Context verified
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmGpiVerifyContext ( 
    IN VOID                 *Context )
{
    EFI_SMM_GPI_DISPATCH_CONTEXT *GpiContext;

    GpiContext = (EFI_SMM_GPI_DISPATCH_CONTEXT *)Context; 
    if ((GpiContext->GpiNum & (UINT32)SUPPORTED_GPIS) == 0)
        return EFI_INVALID_PARAMETER;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiGetContext
//
// Description: This function verifies GPI SMI event and sets GPI SMI context
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - GPI SMI occured, context saved
//                  FALSE - There was no GPI SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmGpiGetContext (VOID)
{
//#### Use Intel RC    BOOLEAN     GpiSmiDetected;
//#### Use Intel RC    UINT32      GpiSmiNum;

    // use intel ref code 
//#### Use Intel RC    GpiSmiDetected = GpiSmiDetect( &GpiSmiNum );
//#### Use Intel RC    SmiContext.GpiContext.GpiNum = GpiSmiNum;
//#### Use Intel RC    return GpiSmiDetected;
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiDispatchSmi
//
// Description: This function dispatches GPI SMI event based on context
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmGpiDispatchSmi (VOID)
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                           SmmHandler[EfiSmmGpiSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    EFI_SMM_GPI_DISPATCH_CONTEXT *GpiContext;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        GpiContext = (EFI_SMM_GPI_DISPATCH_CONTEXT *)Handler->Context;

//#### Use Intel RC        if ((SmiContext.GpiContext.GpiNum & GpiContext->GpiNum) != 0)
//#### Use Intel RC            Handler->Callback( Handler, GpiContext );

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    GpiSmiClear( (UINT16)SmiContext.GpiContext.GpiNum );
}

//---------------------------------------------------------------------------
//                    Standby button SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonAddHandler
//
// Description: This function adds Standby button SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSButtonAddHandler (
    IN VOID                 *Context )
{
    if (SmmHandler[EfiSmmStandbyButtonSmi].RegisteredCallbacks.Size == 1)
        SButtonSmiEnable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonRemoveHandler
//
// Description: This function removes Standby button SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSButtonRemoveHandler (
    IN VOID                 *Context )
{
    if (SmmHandler[EfiSmmStandbyButtonSmi].RegisteredCallbacks.Size == 1)
        SButtonSmiDisable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonVerifyContext
//
// Description: This function verifies Standby button SMI context
//
// Input:       VOID *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS           - Context verified
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSButtonVerifyContext ( 
    IN VOID                     *Context )
{
    EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT *SButtonContext;

    SButtonContext = (EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT *)Context; 
    if (SButtonContext->Phase > Exit)
        return EFI_INVALID_PARAMETER;

    return (SButtonContext->Phase > Entry) ? EFI_UNSUPPORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonGetContext
//
// Description: This function verifies Standby button SMI event and sets 
//              Standby button SMI context 
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - Standby button SMI occured, context saved
//                  FALSE - There was no Standby button SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmSButtonGetContext (VOID)
{
    UINT16      Dummy = 0;
    BOOLEAN     SButtonSmiDetected;

    SButtonSmiDetected = SButtonSmiDetect( &Dummy );

    SmiContext.SBtnContext.Phase = Entry;

    return SButtonSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonDispatchSmi
//
// Description: This function dispatches Standby button SMI event based on
//              context 
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmSButtonDispatchSmi (VOID)
{
    HANDLER_LINK *Handler = (HANDLER_LINK *)\
                SmmHandler[EfiSmmStandbyButtonSmi].RegisteredCallbacks.pHead;
    EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT *SButtonContext;

    while (Handler != NULL) {
        SButtonContext = \
                 (EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT *)Handler->Context;

        if (SButtonContext->Phase == SmiContext.SBtnContext.Phase)
            Handler->Callback( Handler, SButtonContext );

        Handler = (HANDLER_LINK *)Handler->Link.pNext;
    }

    SButtonSmiClear();
}

//---------------------------------------------------------------------------
//                      Power button SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonAddHandler
//
// Description: This function adds Power button SMI handler
//
// Input:       *Context - pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmPButtonAddHandler (
    IN VOID                 *Context )
{
#if 0
    if (SmmHandler[EfiSmmPowerButtonSmi].RegisteredCallbacks.Size == 1)
        PButtonSmiEnable();
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonRemoveHandler
//
// Description: This function removes Power button SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS;
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmPButtonRemoveHandler (
    IN VOID                     *Context )
{
#if 0
    if (SmmHandler[EfiSmmPowerButtonSmi].RegisteredCallbacks.Size == 1)
        PButtonSmiDisable();
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonVerifyContext
//
// Description: This function verifies Power button SMI context
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS           - Context verified
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmPButtonVerifyContext ( 
    IN VOID                     *Context )
{
    EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT *PButtonContext;

    PButtonContext = (EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT *)Context; 
    if (PButtonContext->Phase > PowerButtonExit)
        return EFI_INVALID_PARAMETER;

    return (PButtonContext->Phase > PowerButtonEntry) ? \
                                                EFI_UNSUPPORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonGetContext
//
// Description: This function verifies Power button SMI event and sets Power
//              button SMI context 
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE - Power button SMI occured, context saved
//                  FALSE - There was no Power button SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmPButtonGetContext (VOID)
{
    UINT16      Dummy = 0;
    BOOLEAN     PButtonSmiDetected;

    PButtonSmiDetected = PButtonSmiDetect( &Dummy );

    SmiContext.PBtnContext.Phase = PowerButtonEntry;

    return PButtonSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonDispatchSmi
//
// Description: This function dispatches Power button SMI event based on
//              context 
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmPButtonDispatchSmi (VOID)
{
#if 0
    HANDLER_LINK *Handler = (HANDLER_LINK *)\
                   SmmHandler[EfiSmmPowerButtonSmi].RegisteredCallbacks.pHead;
    EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT *PButtonContext;

    while (Handler != NULL) {
        PButtonContext = \
                    (EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT *)Handler->Context;

        if (PButtonContext->Phase == SmiContext.PBtnContext.Phase)
            Handler->Callback( Handler, PButtonContext );

        Handler = (HANDLER_LINK *)Handler->Link.pNext;
    }

    PButtonSmiClear();

    SBLib_Shutdown();
#endif
}
//---------------------------------------------------------------------------
//                        TCO SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTcoAddHandler
//
// Description: This function adds TCO SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTcoAddHandler (
    IN VOID             *Context )
{
//#### Use Intel RC    EFI_SMM_TCO_DISPATCH_CONTEXT    *TcoContext;

//#### Use Intel RC    TcoContext = (EFI_SMM_TCO_DISPATCH_CONTEXT *)Context;

//#### Use Intel RC    gEnabledTcoSmi |= (1 << (UINT32)(TcoContext->TcoBitOffset));
//#### Use Intel RC    TcoSmiSet( (UINT32)(TcoContext->TcoBitOffset) );

//#### Use Intel RC    if (SmmHandler[EfiSmmTcoSmi].RegisteredCallbacks.Size == 1)
//#### Use Intel RC        TcoSmiEnable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTcoRemoveHandler
//
// Description: This function removes TCO SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTcoRemoveHandler (
    IN VOID             *Context )
{
//#### Use Intel RC    UINT32      RemoveTcoSmiOffset = (UINT32) \
//#### Use Intel RC                    (((EFI_SMM_TCO_DISPATCH_CONTEXT *)Context)->TcoBitOffset);

//#### Use Intel RC    TcoSmiReset( RemoveTcoSmiOffset );
   
//#### Use Intel RC    gEnabledTcoSmi &= ~(1 << RemoveTcoSmiOffset);

//#### Use Intel RC    if (gEnabledTcoSmi == 0) TcoSmiDisable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTcoVerifyContext
//
// Description: This function verifies TCO SMI context
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - Context verified
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTcoVerifyContext (
    IN VOID                 *Context )
{
//#### Use Intel RC    EFI_SMM_TCO_DISPATCH_CONTEXT *TcoContext;

//#### Use Intel RC    TcoContext = (EFI_SMM_TCO_DISPATCH_CONTEXT *)Context;

//#### Use Intel RC    if (((1 << TcoContext->TcoBitOffset) & SUPPORTED_TCOS) == 0)
//#### Use Intel RC        return EFI_UNSUPPORTED;

//#### Use Intel RC    if ( TcoContext->TcoBitOffset > 32) return EFI_INVALID_PARAMETER;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTcoGetContext
//
// Description: This function verifies TCO SMI event and sets TCO SMI context
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - TCO SMI occured, context saved
//                  FALSE - There was no TCO SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmTcoGetContext (VOID)
{
//#### Use Intel RC    UINT32      TcoStatus;
//#### Use Intel RC    BOOLEAN     TcoSmiDetected;

//#### Use Intel RC    TcoSmiDetected = TcoSmiDetect( &TcoStatus );
//#### Use Intel RC    SmiContext.TcoContext.TcoBitOffset = (UINTN)(TcoStatus & gEnabledTcoSmi);
//#### Use Intel RC    if (SmiContext.TcoContext.TcoBitOffset == 0) TcoSmiDetected = FALSE;

//#### Use Intel RC    return TcoSmiDetected;
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTcoDispatchSmi
//
// Description: This function dispatches TCO SMI event based on context
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmTcoDispatchSmi (VOID)
{
//#### Use Intel RC    HANDLER_LINK                    *Handler;
//#### Use Intel RC    EFI_SMM_TCO_DISPATCH_CONTEXT    *TcoContext;

//#### Use Intel RC    Handler = \
//#### Use Intel RC           (HANDLER_LINK *)SmmHandler[EfiSmmTcoSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        TcoContext = (EFI_SMM_TCO_DISPATCH_CONTEXT *)Handler->Context;

//#### Use Intel RC        if ((Shl64( 1 , (UINT8)TcoContext->TcoBitOffset)) & \
//#### Use Intel RC                                           SmiContext.TcoContext.TcoBitOffset)
//#### Use Intel RC            Handler->Callback(Handler, TcoContext);

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    TcoSmiClear();
}

//---------------------------------------------------------------------------
//                      I/O Trap SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapAddHandler
//
// Description: This function adds I/O Trap SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmIoTrapAddHandler (
    IN VOID             *Context )
{
//#### Use Intel RC    HANDLER_LINK                        *Handler;
//#### Use Intel RC    EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *RegedContext;
//#### Use Intel RC    EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *IoTrapContext;
//#### Use Intel RC    UINTN                               i = 0;
//#### Use Intel RC    UINT32                              TrapRegIndex = 0;

//#### Use Intel RC    IoTrapContext = (EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *)Context;

//#### Use Intel RC    Handler = \
//#### Use Intel RC        (HANDLER_LINK *)SmmHandler[EfiSmmIoTrapSmi].RegisteredCallbacks.pHead;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        RegedContext = (EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC        if (RegedContext->Address == IoTrapContext->Address) {
//#### Use Intel RC            TrapRegIndex = RegedContext->TrapRegIndex;
//#### Use Intel RC            i++;
//#### Use Intel RC        }
//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    if (i > 1) {
//#### Use Intel RC        IoTrapContext->TrapRegIndex = TrapRegIndex;
//#### Use Intel RC        return EFI_SUCCESS;
//#### Use Intel RC    }

//#### Use Intel RC    IoTrapSmiSet( IoTrapContext );

//#### Use Intel RC    gEnabledIoTrapSmi |= (1 << (UINT32)(IoTrapContext->TrapRegIndex));

//#### Use Intel RC    if (SmmHandler[EfiSmmIoTrapSmi].RegisteredCallbacks.Size == 1)
//#### Use Intel RC        IoTrapSmiEnable();
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapRemoveHandler
//
// Description: This function removes I/O Trap SMI handler
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmIoTrapRemoveHandler (
    IN VOID             *Context )
{
//#### Use Intel RC    HANDLER_LINK                        *Handler;
//#### Use Intel RC    EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *RegedContext;
//#### Use Intel RC    UINTN       i = 0;
//#### Use Intel RC    UINTN       RemoveIoTrapRegIndex = \
//#### Use Intel RC                (((EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *)Context)->TrapRegIndex);

//#### Use Intel RC    Handler = \
//#### Use Intel RC        (HANDLER_LINK *)SmmHandler[EfiSmmIoTrapSmi].RegisteredCallbacks.pHead;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        RegedContext = (EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC        if (RegedContext->TrapRegIndex == RemoveIoTrapRegIndex) i++;
//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    if (i > 1) return EFI_SUCCESS;

//#### Use Intel RC    IoTrapSmiReset( Context );
   
//#### Use Intel RC    gEnabledIoTrapSmi &= ~(1 << RemoveIoTrapRegIndex);

//#### Use Intel RC    if (gEnabledIoTrapSmi == 0) IoTrapSmiDisable();
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapVerifyContext
//
// Description: This function verifies I/O Trap SMI context
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - Context verified
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_UNSUPPORTED       - Context is not supported
//                  EFI_OUT_OF_RESOURCES  - There is no I/O Trap register
//                                          available
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmIoTrapVerifyContext (
    IN VOID                 *Context )
{
//#### Use Intel RC    HANDLER_LINK                        *Handler;
//#### Use Intel RC    EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *RegedContext;
//#### Use Intel RC    EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *IoTrapContext;

//#### Use Intel RC    Handler = \
//#### Use Intel RC        (HANDLER_LINK *)SmmHandler[EfiSmmIoTrapSmi].RegisteredCallbacks.pHead;

//#### Use Intel RC    IoTrapContext = (EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *)Context;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        RegedContext = (EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *)Handler->Context;
//#### Use Intel RC        if (RegedContext->Address == IoTrapContext->Address) {
//#### Use Intel RC            if ( IoTrapContext->Length > MAX_SUPPORTED_IOTRAP_LENGTH)
//#### Use Intel RC                return EFI_INVALID_PARAMETER;
//#### Use Intel RC            return EFI_SUCCESS;
//#### Use Intel RC        }
//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    if (gEnabledIoTrapSmi >= ((1 << MAX_SUPPORTED_IOTRAP_REGS) - 1))
//#### Use Intel RC        return EFI_OUT_OF_RESOURCES;

//#### Use Intel RC    if ( IoTrapContext->Length > MAX_SUPPORTED_IOTRAP_LENGTH)
//#### Use Intel RC        return EFI_INVALID_PARAMETER;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapGetContext
//
// Description: This function verifies I/O Trap SMI event and sets 
//              I/O Trap SMI context.
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - I/O Trap SMI occured, context saved
//                  FALSE - There was no I/O Trap SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmIoTrapGetContext (VOID)
{
    return IoTrapSmiDetect( &SmiContext.IoTrapContext );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapDispatchSmi
//
// Description: This function dispatches I/O Trap SMI event based on context.
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmIoTrapDispatchSmi (VOID)
{
//#### Use Intel RC    HANDLER_LINK                        *Handler;
//#### Use Intel RC    EFI_SMM_IO_TRAP_DISPATCH_CONTEXT    *IoTrapContext;

//#### Use Intel RC    Handler = \
//#### Use Intel RC        (HANDLER_LINK *)SmmHandler[EfiSmmIoTrapSmi].RegisteredCallbacks.pHead;
//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        IoTrapContext = (EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *)Handler->Context;

//#### Use Intel RC        if ( IoTrapContext->TrapRegIndex == \
//#### Use Intel RC                                        SmiContext.IoTrapContext.TrapRegIndex)
//#### Use Intel RC            if ( gEnabledIoTrapSmi & (1 << IoTrapContext->TrapRegIndex))
//#### Use Intel RC                Handler->Callback(Handler, &SmiContext.IoTrapContext);

//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    IoTrapSmiClear();
}

//---------------------------------------------------------------------------
//                      BIOS Write SMI Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmBiosWriteAddHandler
//
// Description: This function adds BIOS Write SMI handler.
//
// Input:       *Context - pointer to SMI context
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmBiosWriteAddHandler (
    IN VOID                 *Context )
{
//#### Use Intel RC    if (SmmHandler[EfiSmmBiosWriteSmi].RegisteredCallbacks.Size == 1)
//#### Use Intel RC        BiosWriteSmiEnable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmBiosWriteRemoveHandler
//
// Description: This function removes BIOS Write SMI handler.
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_SUCCESS;
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmBiosWriteRemoveHandler (
    IN VOID                     *Context )
{
//#### Use Intel RC    if (SmmHandler[EfiSmmBiosWriteSmi].RegisteredCallbacks.Size == 1)
//#### Use Intel RC        BiosWriteSmiDisable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmBiosWriteVerifyContext
//
// Description: This function verifies BIOS Write SMI context.
//
// Input:       *Context - Pointer to SMI context
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS - Context verified
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmBiosWriteVerifyContext ( 
    IN VOID                     *Context )
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmBiosWriteGetContext
//
// Description: This function verifies BIOS Write SMI event.
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE - BIOS Write SMI occured.
//                  FALSE - There was no BIOS Write SMI
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmBiosWriteGetContext (VOID)
{
    return BiosWriteSmiDetect();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmBiosWriteDispatchSmi
//
// Description: This function dispatches BIOW Write SMI event based on
//              context.
//
// Input:       None
//
// Output:      None
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmBiosWriteDispatchSmi (VOID)
{
//#### Use Intel RC    HANDLER_LINK *Handler = (HANDLER_LINK *)\
//#### Use Intel RC                   SmmHandler[EfiSmmBiosWriteSmi].RegisteredCallbacks.pHead;

//#### Use Intel RC    while (Handler != NULL) {
//#### Use Intel RC        Handler->Callback( Handler, NULL );
//#### Use Intel RC        Handler = (HANDLER_LINK *)Handler->Link.pNext;
//#### Use Intel RC    }

//#### Use Intel RC    BiosWriteSmiClear();
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
