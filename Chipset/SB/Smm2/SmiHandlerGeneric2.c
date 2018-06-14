//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmiHandlerGeneric2.c 7     8/17/14 11:55p Mirayang $
//
// $Revision: 7 $
//
// $Date: 8/17/14 11:55p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmiHandlerGeneric2.c $
// 
// 7     8/17/14 11:55p Mirayang
// Fix Build Error when token "PI_0_9_CHILD_DISPATCHER_SUPPORT" = 0
// 
// 6     3/25/13 4:59a Wesleychen
// [TAG]          None
// [Category]     Improvement
// [Description]  Refine GPI SMM2 related routines.
// [Files]        SmiHandlerGeneric2.c; SmiHandlerPorting2.c;
//                SmmChildDispatch2.h
// 
// 5     3/15/13 2:25a Scottyang
// [TAG]          None
// [Category]     Improvement
// [Description]  Support ULT GPISMI.
// [Files]        SmiHandlerGeneric2.c
// 
// 4     1/03/13 7:00a Scottyang
// [TAG]        None
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	GPISMI cannot use.
// [RootCause]  GPISMI2 will clear status before GPISMI.
// [Solution]  	GPISMI2 do not clear status when GPISMI has register.
// [Files]  	SmmChildDispatcher2.sdl; SmiHandlerGeneric2.c
// 
// 3     8/30/12 9:50a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Implement EIP#73211 and EIP#79156 for OA 3.0 function.
// [Files]         SmiHandlerGeneric2.c, SmmChildDispatch2Main.c
// 
// 2     4/25/12 9:32a Victortu
// [TAG]         None
// [Category]    Improvement
// [Description] Reprogram SMM ChildDispatcher drivers.
// [Files]       SmiHandlerGeneric.c; SmiHandlerPorting.c;
// SmiHandlerGeneric2.c; SmmChildDispatch2Main.c; SmmChildDispatcher2.mak;
// SmmChildDispatcher2.sdl; SmmChildDispatch.h; SmmChildDispatchMain.c;
// SmmChildDispatchProtocol.c; SmmChildDispatcher.dxs;
// PchSmiDispatcher.sdl
// 
// 1     2/08/12 8:28a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmiHandlerGeneric2.c
//
// Description: This file contains implementation of generic SMI handler II
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
#include "SmmChildDispatch2.h"
#include <AmiSmm.h>

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

// Protocol Definition(s)

// External Declaration(s)

extern EFI_SMM_SYSTEM_TABLE2 *gSmst2;
extern SMM_CHILD_DISPATCHER2 Smm2Handler[];
extern EFI_SMM_SMI_CONTEXT2  SmiContext;

extern UINT64 gSupportedIntervals[];

// Function Definition(s)

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//                      Software SMI II Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwAddHandler2
//
// Description: This function adds SW SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_SW_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSwAddHandler2 (
    IN VOID             *Context )
{
    if (Smm2Handler[EfiSmmSwSmi2].RegisteredCallbacks.Size == 1) SwSmiEnable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwRemoveHandler2
//
// Description: This function removes SW SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_SW_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSwRemoveHandler2 (
    IN VOID             *Context )
{
#if (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    if (Smm2Handler[EfiSmmSwSmi2].RegisteredCallbacks.Size == 1) SwSmiDisable();
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwVerifyContext2
//
// Description: This function verifies SW SMI II context
//
// Input:       *Context - Pointer to SMI II context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS - Context verified
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSwVerifyContext2 (
    IN VOID             *Context )
{
    HANDLER_LINK2 *Handler = (HANDLER_LINK2 *)\
                            Smm2Handler[EfiSmmSwSmi2].RegisteredCallbacks.pHead;
    EFI_SMM_SW_REGISTER_CONTEXT *SwContext;
    EFI_SMM_SW_REGISTER_CONTEXT *RegisteredSwContext;

    SwContext = (EFI_SMM_SW_REGISTER_CONTEXT *)Context;
    // First check if we already registered handler for this value
    while (Handler != NULL) {
        RegisteredSwContext = (EFI_SMM_SW_REGISTER_CONTEXT *)Handler->Context;
        if(SwContext->SwSmiInputValue == RegisteredSwContext->SwSmiInputValue)
            // Handler with this value already registered 
            return EFI_INVALID_PARAMETER;       

        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

    // Second check if given value is extended SMI value, 
    // check the lowest byte  
    if ((SwContext->SwSmiInputValue & 0xff) == EXTENDED_SMI)
        return EFI_SUCCESS;     // Accept value of UINTN size

    // Third check if given value is in default range
    return (SwContext->SwSmiInputValue > MAX_SW_SMI_INPUT_VALUE) ? \
                                          EFI_INVALID_PARAMETER : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSwGetContext2
//
// Description: This function verifies SW SMI II event and sets SW SMI II
//              context
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - SW SMI occured, context saved
//                  FALSE - There was no SW SMI II
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmSwGetContext2 (VOID)
{
    UINT16      SwSmiNumber;
    BOOLEAN     SwSmiDetected;

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
// Procedure:   SmmSwDispatchSmi2
//
// Description: This function dispatches SW SMI II event based on context
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSwDispatchSmi2 ( VOID )
{
    EFI_STATUS                  Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
    HANDLER_LINK2               *Handler;
    EFI_SMM_SW_REGISTER_CONTEXT *SwRegisterContext;

    EFI_SMM_SW_CONTEXT          SwContext;
    UINTN                       SwContextSize;
    UINT16                      i;
    EFI_GUID                    SwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
    SW_SMI_CPU_TRIGGER          *SwSmiCpuTrigger;
    UINTN                       Cpu = pSmst->CurrentlyExecutingCpu - 1; //default cpu #

    for (i = 0; i < pSmst->NumberOfTableEntries; i++)
    {
        if (guidcmp(&(pSmst->SmmConfigurationTable[i].VendorGuid), &SwSmiCpuTriggerGuid) == 0)
            break;
    }

    //If found table, check for the CPU that caused the software Smi.
    if (i != pSmst->NumberOfTableEntries)
    {
        SwSmiCpuTrigger = pSmst->SmmConfigurationTable[i].VendorTable;
        Cpu = SwSmiCpuTrigger->Cpu;
    }

    SwContext.SwSmiCpuIndex = Cpu;
    SwContext.CommandPort = IoRead8(SW_SMI_IO_ADDRESS);
    SwContext.DataPort = IoRead8(SW_SMI_IO_ADDRESS + 1);
    SwContextSize = sizeof(SwContext);

    Handler = \
            (HANDLER_LINK2 *)Smm2Handler[EfiSmmSwSmi2].RegisteredCallbacks.pHead;
    while (Handler != NULL) {
        SwRegisterContext = (EFI_SMM_SW_REGISTER_CONTEXT *)Handler->Context;
        if(SwRegisterContext->SwSmiInputValue == SmiContext.SwContext.SwSmiInputValue)
            Status = Handler->Callback(Handler, SwRegisterContext, &SwContext, &SwContextSize);

        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

/*#if (CHILD_DISPATCHER_SUPPORT != 0)
    if (!EFI_ERROR(Status))
#endif*/
if (Status != EFI_WARN_INTERRUPT_SOURCE_QUIESCED)
        SwSmiClear();

    return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
}

//---------------------------------------------------------------------------
//                       Sleep SMI II Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxAddHandler2
//
// Description: This function adds Sx SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_SX_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSxAddHandler2 (
    IN VOID             *Context )
{
#if SLP_SMI_ENABLE_ON_REGISTER
    if (Smm2Handler[EfiSmmSxSmi2].RegisteredCallbacks.Size == 1) SxSmiEnable();
#endif
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxRemoveHandler2
//
// Description: This function removes Sx SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_SX_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSxRemoveHandler2 (
    IN VOID             *Context )
{
#if SLP_SMI_ENABLE_ON_REGISTER && (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    if (Smm2Handler[EfiSmmSxSmi2].RegisteredCallbacks.Size == 1) SxSmiDisable();
#endif
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxVerifyContext2
//
// Description: This function verifies Sx SMI II context
//
// Input:       *Context - Pointer to SMI II context
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS           - Context verified
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSxVerifyContext2 (
    IN VOID                 *Context )
{
    EFI_SMM_SX_REGISTER_CONTEXT *SxContext;

    SxContext = (EFI_SMM_SX_REGISTER_CONTEXT *)Context;
    if ((SxContext->Type >= EfiMaximumSleepType) || \
                                        (SxContext->Phase >= EfiMaximumPhase))
        return EFI_INVALID_PARAMETER;

    return ((SxContext->Phase) != SxEntry) ? EFI_UNSUPPORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxGetContext2
//
// Description: This function verifies Sx SMI II event and sets SX SMI II
//              context
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - Sx SMI occured, context saved
//                  FALSE - There was no SX SMI II
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmSxGetContext2 (VOID)
{
    UINT16      SxSleepState;
    BOOLEAN     SxSmiDetected;

    SxSmiDetected = SxSmiDetect( &SxSleepState );

    SmiContext.SxContext.Type = SxSleepState;
    SmiContext.SxContext.Phase = SxEntry;

    return SxSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSxDispatchSmi2
//
// Description: This function dispatches Sx SMI II event based on context
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSxDispatchSmi2 (VOID)
{
    EFI_STATUS                  Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
    HANDLER_LINK2               *Handler;
    EFI_SMM_SX_REGISTER_CONTEXT *SxContext;

    Handler = \
            (HANDLER_LINK2 *)Smm2Handler[EfiSmmSxSmi2].RegisteredCallbacks.pHead;
    while (Handler != NULL) {
        SxContext = (EFI_SMM_SX_REGISTER_CONTEXT *)Handler->Context;

        if ((SxContext->Type == SmiContext.SxContext.Type) && \
                            (SxContext->Phase == SmiContext.SxContext.Phase))
            Status = Handler->Callback(Handler, SxContext, NULL, NULL);

        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

#if (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    SxSmiClear();

    if (SmiContext.SxContext.Type == SxS0) return Status;

    PutToSleep( &(SmiContext.SxContext) );

    // Control returns here on S1.

    SxSmiClear();

    return Status;
#else
    return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
#endif
}

//---------------------------------------------------------------------------
//                    Periodic timer SMI II Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerAddHandler2
//
// Description: This function adds Periodic timer SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTimerAddHandler2 (
    IN VOID                 *Context )
{
    EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *TimerContext;

    TimerContext = (EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *)Context;

    if (Smm2Handler[EfiSmmPeriodicTimerSmi2].RegisteredCallbacks.Size == 1) {
        gCurrentInterval = TimerContext->OrgContext.SmiTickInterval;
        TimerSetInterval2( TimerContext->OrgContext.SmiTickInterval );
        TimerSmiClear2();
        TimerSmiEnable2();
        return EFI_SUCCESS;
    }

    if (gCurrentInterval > TimerContext->OrgContext.SmiTickInterval) {
        gCurrentInterval = TimerContext->OrgContext.SmiTickInterval;
        TimerSetInterval2( TimerContext->OrgContext.SmiTickInterval );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerRemoveHandler2
//
// Description: This function removes Periodic timer SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTimerRemoveHandler2 (
    IN VOID                 *Context )
{
    HANDLER_LINK2 *Handler = (HANDLER_LINK2 *)\
               Smm2Handler[EfiSmmPeriodicTimerSmi2].RegisteredCallbacks.pHead;
    EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *TimerContext;
    EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *CurrentTimerContext;
    UINT64                                  Interval = 0xffffffffffffffff;

    UINT16      CurrentIntervalCounter = 0;
    UINT64      *SupportedIntervals = gSupportedIntervals;

    if (Smm2Handler[EfiSmmPeriodicTimerSmi2].RegisteredCallbacks.Size == 1) {
        gCurrentInterval = 0xffffffffffffffff;
        TimerSmiDisable2();
        return EFI_SUCCESS;
    }

    CurrentTimerContext = \
                      (EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *)Context;
    while (Handler != NULL) {    
        TimerContext = \
             (EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *)Handler->Context;
        if (Interval > TimerContext->OrgContext.SmiTickInterval)
            Interval = TimerContext->OrgContext.SmiTickInterval;
        if (TimerContext->OrgContext.SmiTickInterval == \
                             CurrentTimerContext->OrgContext.SmiTickInterval)
            CurrentIntervalCounter++;
        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

    if ((Interval == CurrentTimerContext->OrgContext.SmiTickInterval) && \
                                              (CurrentIntervalCounter == 1)) {
        Interval = 0xffffffffffffffff;
        while (*SupportedIntervals != 0) {
            if (*SupportedIntervals != \
                             CurrentTimerContext->OrgContext.SmiTickInterval)
                if (*SupportedIntervals < Interval)
                    Interval = *SupportedIntervals;
            SupportedIntervals++;
        }
    }

    // This means lowest rate timer no longer active 
    if (gCurrentInterval < Interval) {
        gCurrentInterval = Interval;
        TimerSetInterval2( Interval );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerVerifyContext2
//
// Description: This function verifies Periodic timer SMI II context
//
// Input:       *Context - Pointer to SMI II context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS           - Context verified
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTimerVerifyContext2 (
    IN VOID                 *Context )
{
    EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *TimerContext;
    UINT64                                  *Interval = gSupportedIntervals;

    TimerContext = (EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *)Context;
    while (*Interval != 0) {
        if (*Interval == TimerContext->OrgContext.SmiTickInterval)
            return EFI_SUCCESS;
        Interval++;
    }

    return EFI_INVALID_PARAMETER;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerGetContext2
//
// Description: This function verifies Periodic timer SMI II event and sets
//              Periodic timer SMI II context 
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

BOOLEAN SmmTimerGetContext2 (VOID)
{
    UINT16      TimerType;
    BOOLEAN     TimerSmiDetected;

    TimerSmiDetected = TimerSmiDetect2( &TimerType );
    SmiContext.TimerContext.OrgContext.SmiTickInterval = gCurrentInterval;

    return TimerSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmTimerDispatchSmi2
//
// Description: This function dispatches Periodic timer SMI event based on
//              context
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmTimerDispatchSmi2 (VOID)
{
    EFI_STATUS    Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
    HANDLER_LINK2 *Handler = (HANDLER_LINK2 *)\
               Smm2Handler[EfiSmmPeriodicTimerSmi2].RegisteredCallbacks.pHead;
    EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *TimerContext;

    while (Handler != NULL) {
        TimerContext = \
                 (EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT *)Handler->Context;

            TimerContext->ElapsedTime += \
                          SmiContext.TimerContext.OrgContext.SmiTickInterval;
            if (TimerContext->ElapsedTime >= TimerContext->OrgContext.Period){
                Status = Handler->Callback(Handler, TimerContext, NULL, NULL);
                TimerContext->ElapsedTime = 0;
            }
        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

#if (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    TimerSmiClear2();
    return Status;
#else
    return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
#endif

}

//---------------------------------------------------------------------------
//                           USB SMI II Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbAddHandler2
//
// Description: This function adds USB SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_USB_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmUsbAddHandler2 (
    IN VOID             *Context
)
{
    EFI_STATUS                   Status;
    EFI_SMM_USB_REGISTER_CONTEXT *UsbContext;
    UINT16                       ControllerType;
    VOID                         *NewDp;
    UINTN                        Length;

    UsbContext = (EFI_SMM_USB_REGISTER_CONTEXT *)Context;

    // Save USB device path protocol into SMM memory
    Length = DPLength( UsbContext->Device );
    Status = gSmst2->SmmAllocatePool( 0, Length, &NewDp );
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
// Procedure:   SmmUsbRemoveHandler2
//
// Description: This function removes USB SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_USB_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmUsbRemoveHandler2 (
    IN VOID             *Context )
{
    HANDLER_LINK2 *Handler = (HANDLER_LINK2 *)\
                         Smm2Handler[EfiSmmUsbSmi2].RegisteredCallbacks.pHead;
    EFI_SMM_USB_REGISTER_CONTEXT *UsbContext;
    UINT16                       ControllerType = 0;

    UsbContext = (EFI_SMM_USB_REGISTER_CONTEXT *)Context;

    gSmst2->SmmFreePool( UsbContext->Device );

    if (Smm2Handler[EfiSmmUsbSmi2].RegisteredCallbacks.Size == 1) {
        gEnabledUsbSmi = 0;
        UsbSmiSet( gEnabledUsbSmi );
        return EFI_SUCCESS;
    }

    while (Handler != NULL) {
        UsbContext = (EFI_SMM_USB_REGISTER_CONTEXT *)Handler->Context;
        ControllerType |= GetControllerType( UsbContext->Device );
        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

    if (ControllerType != gEnabledUsbSmi) {
        gEnabledUsbSmi = ControllerType;
        UsbSmiSet( gEnabledUsbSmi );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbVerifyContext2
//
// Description: This function verifies USB SMI II context
//
// Input:       *Context - Pointer to SMI II context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS           - Context verified
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmUsbVerifyContext2 ( 
    IN VOID                 *Context )
{
    EFI_SMM_USB_REGISTER_CONTEXT    *UsbContext;
    UINT16                          ControllerType;

    UsbContext = (EFI_SMM_USB_REGISTER_CONTEXT *)Context;
    ControllerType = GetControllerType( UsbContext->Device );
    if (((ControllerType & 7) == 0) || (UsbContext->Type > UsbWake))
        return EFI_INVALID_PARAMETER;

    return ((UsbContext->Type) > UsbLegacy) ? EFI_UNSUPPORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbGetContext2
//
// Description: This function verifies USB SMI II event and sets USB SMI II
//              context 
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

BOOLEAN SmmUsbGetContext2 (VOID)
{
    BOOLEAN     UsbSmiDetected;

    UsbSmiDetected = UsbSmiDetect( &gActiveUsbSmi );
    SmiContext.UsbContext.Type = UsbLegacy;

    return UsbSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmUsbDispatchSmi2
//
// Description: This function dispatches USB SMI II event based on context
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmUsbDispatchSmi2 (VOID)
{
    EFI_STATUS    Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
    HANDLER_LINK2 *Handler = (HANDLER_LINK2 *)\
                         Smm2Handler[EfiSmmUsbSmi2].RegisteredCallbacks.pHead;
    EFI_SMM_USB_REGISTER_CONTEXT *UsbContext;
    UINT16                       ControllerType;

    while (Handler != NULL) {
        UsbContext = (EFI_SMM_USB_REGISTER_CONTEXT *)Handler->Context;
        ControllerType = GetControllerType( UsbContext->Device );

        if (((ControllerType & gActiveUsbSmi) != 0) && \
                            (UsbContext->Type == SmiContext.UsbContext.Type))
            Status = Handler->Callback(Handler, UsbContext, NULL, NULL);

        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

#if (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    UsbSmiClear( gActiveUsbSmi );
    gActiveUsbSmi = 0;
    return Status;
#else
    gActiveUsbSmi = 0;
    return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
#endif

}

//---------------------------------------------------------------------------
//                         GPI SMI II Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiAddHandler2
//
// Description: This function adds GPI SMI II handler
//
// Input:       VOID *Context - Pointer to EFI_SMM_GPI_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmGpiAddHandler2 (
    IN VOID             *Context )
{
    EFI_SMM_GPI_REGISTER_CONTEXT    *GpiContext;
    UINT32 GpiBitMap = 0;

    GpiContext = (EFI_SMM_GPI_REGISTER_CONTEXT *)Context;

    GpiBitMap = ConvertGpi (GpiContext->GpiNum);

    if ((GpiBitMap & gEnabledGpiSmi) == 0) {
        gEnabledGpiSmi |= GpiBitMap;
        GpiSmiSet( GpiBitMap );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiRemoveHandler2
//
// Description: This function removes GPI SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_GPI_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmGpiRemoveHandler2 (
    IN VOID             *Context )
{
    EFI_SMM_GPI_REGISTER_CONTEXT    *GpiContext;
    UINT32 GpiBitMap = 0;

    GpiContext = (EFI_SMM_GPI_REGISTER_CONTEXT *)Context;

    GpiBitMap = ConvertGpi (GpiContext->GpiNum);

    gEnabledGpiSmi &= ~(GpiBitMap);

    GpiSmiReset( GpiBitMap );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiVerifyContext2
//
// Description: This function verifies GPI SMI II context
//
// Input:       *Context - Pointer to SMI II context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS - Context verified
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmGpiVerifyContext2 ( 
    IN VOID                 *Context )
{
    EFI_SMM_GPI_REGISTER_CONTEXT *GpiContext;
    UINT32      GpiBitMap = 0;

    GpiContext = (EFI_SMM_GPI_REGISTER_CONTEXT *)Context; 

    GpiBitMap = ConvertGpi (GpiContext->GpiNum);

    if ((GpiBitMap & SUPPORTED_GPIS2) == 0)
        return EFI_INVALID_PARAMETER;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiGetContext2
//
// Description: This function verifies GPI SMI II event and sets GPI SMI II
//              context
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

BOOLEAN SmmGpiGetContext2 (VOID)
{
    BOOLEAN     GpiSmiDetected;
    UINT32      GpiSmiNum;

    GpiSmiDetected = GpiSmiDetect( &GpiSmiNum );
    SmiContext.GpiContext.GpiNum = GpiSmiNum;

    return GpiSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmGpiDispatchSmi2
//
// Description: This function dispatches GPI SMI event based on context
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmGpiDispatchSmi2 (VOID)
{
    EFI_STATUS    Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
    HANDLER_LINK2 *Handler = (HANDLER_LINK2 *)\
                           Smm2Handler[EfiSmmGpiSmi2].RegisteredCallbacks.pHead;
    EFI_SMM_GPI_REGISTER_CONTEXT *GpiContext;
    UINT32 GpiBitMap = 0;
    BOOLEAN GpiSmiServiced = FALSE;

    while (Handler != NULL) {
        GpiContext = (EFI_SMM_GPI_REGISTER_CONTEXT *)Handler->Context;

        GpiBitMap = ConvertGpi (GpiContext->GpiNum);

        GpiSmiServiced = FALSE;
        if ((SmiContext.GpiContext.GpiNum & GpiBitMap) != 0) {
            Status = Handler->Callback( Handler, GpiContext, NULL, NULL );
            GpiSmiServiced = TRUE;
        }

        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

    if (GpiSmiServiced)
      GpiSmiClear( (UINT16)SmiContext.GpiContext.GpiNum );

#if (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    return Status;
#else
    return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
#endif

}

//---------------------------------------------------------------------------
//                   Standby button SMI II Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonAddHandler2
//
// Description: This function adds Standby button SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSButtonAddHandler2 (
    IN VOID                 *Context )
{
    if (Smm2Handler[EfiSmmStandbyButtonSmi2].RegisteredCallbacks.Size == 1)
        SButtonSmiEnable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonRemoveHandler2
//
// Description: This function removes Standby button SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSButtonRemoveHandler2 (
    IN VOID                 *Context )
{
    if (Smm2Handler[EfiSmmStandbyButtonSmi2].RegisteredCallbacks.Size == 1)
        SButtonSmiDisable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonVerifyContext2
//
// Description: This function verifies Standby button SMI II context
//
// Input:       VOID *Context - Pointer to SMI II context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS           - Context verified
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSButtonVerifyContext2 ( 
    IN VOID                     *Context )
{
    EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT *SButtonContext;

    SButtonContext = (EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT *)Context; 
    if (SButtonContext->Phase >= EfiStandbyButtonMax)
        return EFI_INVALID_PARAMETER;

    return (SButtonContext->Phase > EfiStandbyButtonEntry) \
                                            ? EFI_UNSUPPORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonGetContext2
//
// Description: This function verifies Standby button SMI II event and sets 
//              Standby button SMI II context 
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

BOOLEAN SmmSButtonGetContext2 (VOID)
{
    UINT16      Dummy = 0;
    BOOLEAN     SButtonSmiDetected;

    SButtonSmiDetected = SButtonSmiDetect( &Dummy );

    SmiContext.SBtnContext.Phase = EfiStandbyButtonEntry;

    return SButtonSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmSButtonDispatchSmi2
//
// Description: This function dispatches Standby button SMI II event based on
//              context 
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmSButtonDispatchSmi2 (VOID)
{
    EFI_STATUS   Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
    HANDLER_LINK2 *Handler = (HANDLER_LINK2 *)\
               Smm2Handler[EfiSmmStandbyButtonSmi2].RegisteredCallbacks.pHead;
    EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT *SButtonContext;

    while (Handler != NULL) {
        SButtonContext = \
                 (EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT *)Handler->Context;

        if (SButtonContext->Phase == SmiContext.SBtnContext.Phase)
            Status = Handler->Callback( Handler, SButtonContext, NULL, NULL );

        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

#if (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    SButtonSmiClear();

    return Status;
#else
    return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
#endif
}

//---------------------------------------------------------------------------
//                     Power button SMI II Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonAddHandler2
//
// Description: This function adds Power button SMI II handler
//
// Input:       *Context - pointer to EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmPButtonAddHandler2 (
    IN VOID                 *Context )
{
    if (Smm2Handler[EfiSmmPowerButtonSmi2].RegisteredCallbacks.Size == 1)
        PButtonSmiEnable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonRemoveHandler2
//
// Description: This function removes Power button SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS;
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmPButtonRemoveHandler2 (
    IN VOID                     *Context )
{
    if (Smm2Handler[EfiSmmPowerButtonSmi2].RegisteredCallbacks.Size == 1)
        PButtonSmiDisable();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonVerifyContext2
//
// Description: This function verifies Power button SMI II context
//
// Input:       *Context - Pointer to SMI II context
//
// Output:      EFI_STATUS
//                  EFI_INVALID_PARAMETER - Given context is invalid
//                  EFI_SUCCESS           - Context verified
//                  EFI_UNSUPPORTED       - Context is not supported
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmPButtonVerifyContext2 ( 
    IN VOID                     *Context )
{
    EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT *PButtonContext;

    PButtonContext = (EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT *)Context; 
    if (PButtonContext->Phase >= EfiPowerButtonMax)
        return EFI_INVALID_PARAMETER;

    return (PButtonContext->Phase > EfiPowerButtonEntry) ? \
                                               EFI_UNSUPPORTED : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonGetContext2
//
// Description: This function verifies Power button SMI II event and sets
//              Power button SMI II context 
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

BOOLEAN SmmPButtonGetContext2 (VOID)
{
    UINT16      Dummy = 0;
    BOOLEAN     PButtonSmiDetected;

    PButtonSmiDetected = PButtonSmiDetect( &Dummy );

    SmiContext.PBtnContext.Phase = EfiPowerButtonEntry;

    return PButtonSmiDetected;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmPButtonDispatchSmi2
//
// Description: This function dispatches Power button SMI II event based on
//              context 
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmPButtonDispatchSmi2 (VOID)
{
    EFI_STATUS    Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
    HANDLER_LINK2 *Handler = (HANDLER_LINK2 *)\
                  Smm2Handler[EfiSmmPowerButtonSmi2].RegisteredCallbacks.pHead;
    EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT *PButtonContext;

    while (Handler != NULL) {
        PButtonContext = \
                    (EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT *)Handler->Context;

        if (PButtonContext->Phase == SmiContext.PBtnContext.Phase)
            Status = Handler->Callback( Handler, PButtonContext, NULL, NULL );

        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

#if (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    PButtonSmiClear();
    SBLib_Shutdown();

    return Status;
#else
    return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
#endif
}

//---------------------------------------------------------------------------
//                     I/O Trap SMI II Handler functions
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapAddHandler2
//
// Description: This function adds I/O Trap SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_IO_TRAP_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS - The context has been registerd successfully.
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmIoTrapAddHandler2 (
    IN VOID             *Context )
{
    HANDLER_LINK2                        *Handler;
    EFI_SMM_IO_TRAP_REGISTER_CONTEXT    *RegedContext;
    EFI_SMM_IO_TRAP_REGISTER_CONTEXT    *IoTrapContext;
    UINT32                              TrapRegIndex = 0;
    UINT32                              i = 0;

    IoTrapContext = (EFI_SMM_IO_TRAP_REGISTER_CONTEXT *)Context;

    Handler = \
      (HANDLER_LINK2 *)Smm2Handler[EfiSmmIoTrapSmi2].RegisteredCallbacks.pHead;

    while (Handler != NULL) {
        RegedContext = (EFI_SMM_IO_TRAP_REGISTER_CONTEXT *)Handler->Context;
        if ((RegedContext->Address == IoTrapContext->Address) && \
            (RegedContext->Type == IoTrapContext->Type) && \
            (RegedContext->Length == IoTrapContext->Length)) {
            i++;
        }
        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

    if (i > 1) return EFI_SUCCESS;

    IoTrapSmiSet2( IoTrapContext, &TrapRegIndex );

    gEnabledIoTrapSmi |= (UINT32)(1 << TrapRegIndex);

    if (Smm2Handler[EfiSmmIoTrapSmi2].RegisteredCallbacks.Size == 1)
        IoTrapSmiEnable2();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapRemoveHandler2
//
// Description: This function removes I/O Trap SMI II handler
//
// Input:       *Context - Pointer to EFI_SMM_IO_TRAP_REGISTER_CONTEXT
//
// Output:      EFI_SUCCESS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmIoTrapRemoveHandler2 (
    IN VOID             *Context )
{
    HANDLER_LINK2                       *Handler;
    EFI_SMM_IO_TRAP_REGISTER_CONTEXT    *RegedContext;
    EFI_SMM_IO_TRAP_REGISTER_CONTEXT    *RemoveContext;
    UINT32                              i = 0;
    UINT32                              TrapRegIndex = 0;

    RemoveContext = (EFI_SMM_IO_TRAP_REGISTER_CONTEXT *)Context;

    Handler = \
      (HANDLER_LINK2 *)Smm2Handler[EfiSmmIoTrapSmi2].RegisteredCallbacks.pHead;

    while (Handler != NULL) {
        RegedContext = (EFI_SMM_IO_TRAP_REGISTER_CONTEXT *)Handler->Context;
        if ((RegedContext->Address == RemoveContext->Address) && \
            (RegedContext->Type == RemoveContext->Type) && \
            (RegedContext->Length == RemoveContext->Length)) i++;
        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

    if (i > 1) return EFI_SUCCESS;

    IoTrapSmiReset2( Context, &TrapRegIndex );
   
    gEnabledIoTrapSmi &= ~(1 << TrapRegIndex);

    if (gEnabledIoTrapSmi == 0) IoTrapSmiDisable2();

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapVerifyContext2
//
// Description: This function verifies I/O Trap SMI II context
//
// Input:       *Context - Pointer to SMI II context
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

EFI_STATUS SmmIoTrapVerifyContext2 (
    IN VOID                 *Context )
{
    HANDLER_LINK2                       *Handler;
    EFI_SMM_IO_TRAP_REGISTER_CONTEXT    *RegedContext;
    EFI_SMM_IO_TRAP_REGISTER_CONTEXT    *IoTrapContext;

    Handler = \
        (HANDLER_LINK2 *)Smm2Handler[EfiSmmIoTrapSmi2].RegisteredCallbacks.pHead;

    IoTrapContext = (EFI_SMM_IO_TRAP_REGISTER_CONTEXT *)Context;

    while (Handler != NULL) {
        RegedContext = (EFI_SMM_IO_TRAP_REGISTER_CONTEXT *)Handler->Context;
        if ((RegedContext->Address == IoTrapContext->Address) && \
            (RegedContext->Type == IoTrapContext->Type)) {
            if ( IoTrapContext->Length > MAX_SUPPORTED_IOTRAP_LENGTH)
                return EFI_INVALID_PARAMETER;
            return EFI_SUCCESS;
        }
        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }

    if (gEnabledIoTrapSmi >= ((1 << MAX_SUPPORTED_IOTRAP_REGS) - 1))
        return EFI_OUT_OF_RESOURCES;

    if (IoTrapContext->Length > MAX_SUPPORTED_IOTRAP_LENGTH)
        return EFI_INVALID_PARAMETER;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapGetContext2
//
// Description: This function verifies I/O Trap SMI II event and sets 
//              I/O Trap SMI II context.
//
// Input:       None
//
// Output:      BOOLEAN
//                  TRUE  - I/O Trap SMI occured, context saved
//                  FALSE - There was no I/O Trap SMI
//              The global variable gIoTrapWriteData will save the data from
//              I/O write cycle.
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmIoTrapGetContext2 (VOID)
{
    return IoTrapSmiDetect2( &SmiContext.IoTrapContext, &gIoTrapWriteData );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmIoTrapDispatchSmi2
//
// Description: This function dispatches I/O Trap SMI II event based on
//              context.
//
// Input:       None
//
// Output:      EFI_STATUS
//
// Notes:       GENERALLY NO PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmIoTrapDispatchSmi2 (VOID)
{
    EFI_STATUS                   Status = EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
    HANDLER_LINK2                       *Handler;
    EFI_SMM_IO_TRAP_REGISTER_CONTEXT    *IoTrapContext;
    volatile UINT16                     MaxAddress;

    Handler = \
      (HANDLER_LINK2 *)Smm2Handler[EfiSmmIoTrapSmi2].RegisteredCallbacks.pHead;
    while (Handler != NULL) {
        IoTrapContext = (EFI_SMM_IO_TRAP_REGISTER_CONTEXT *)Handler->Context;
        MaxAddress = IoTrapContext->Address + IoTrapContext->Length;
        if ((IoTrapContext->Address <= SmiContext.IoTrapContext.Address) && \
            (MaxAddress > SmiContext.IoTrapContext.Address)) {
            if ((IoTrapContext->Type == ReadWriteTrap) || \
               (IoTrapContext->Type == SmiContext.IoTrapContext.Type)) {
                Status = Handler->Callback( \
                                Handler, \
                                (EFI_SMM_IO_TRAP_CONTEXT*)&gIoTrapWriteData, \
                                NULL, \
                                NULL );
            }
        }
        Handler = (HANDLER_LINK2 *)Handler->Link.pNext;
    }
#if (PI_0_9_CHILD_DISPATCHER_SUPPORT == 0)
    if (Status != EFI_WARN_INTERRUPT_SOURCE_QUIESCED) IoTrapSmiClear2();
    return Status;
#else
    return EFI_WARN_INTERRUPT_SOURCE_QUIESCED;
#endif
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
