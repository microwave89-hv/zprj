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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatchMain.c 2     4/25/12 9:35a Victortu $
//
// $Revision: 2 $
//
// $Date: 4/25/12 9:35a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatchMain.c $
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
// Name:        SmmChildDispatchMain.c
//
// Description: This file contains implementation of module entry point,
//              generic RegisterHandler and UnregisterHandler routines 
//              and main dispatcher loop.
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <AmiCspLib.h>
#include <Smm.h>
#include "SmmChildDispatch.h"
#include "SmmChildDispatchProtocol.h"

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)
#define SMI_HANDLER_SIGNATURE 0x48494d53    //SMIH

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

EFI_SMM_SMI_CONTEXT SmiContext;
SB_ASL_BUFFER       *gSbAslBufPtr = NULL;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

extern EFI_SMM_SYSTEM_TABLE *pSmst;
extern SMM_CHILD_DISPATCHER SmmHandler[];

#if INTEL_RC_SMI_DISPATCHER_SUPPORT == 0
extern EFI_SMM_SW_DISPATCH_PROTOCOL             gEfiSmmSwDispatchProtocol;
extern EFI_SMM_SX_DISPATCH_PROTOCOL             gEfiSmmSxDispatchProtocol;
extern EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL gEfiSmmPeriodicTimerDispatchProtocol;
extern EFI_SMM_USB_DISPATCH_PROTOCOL            gEfiSmmUsbDispatchProtocol;
extern EFI_SMM_GPI_DISPATCH_PROTOCOL            gEfiSmmGpiDispatchProtocol;
#endif
extern EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL gEfiSmmStandbyButtonDispatchProtocol;
#if INTEL_RC_SMI_DISPATCHER_SUPPORT == 0
extern EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL   gEfiSmmPowerButonDispatchProtocol;
extern EFI_SMM_TCO_DISPATCH_PROTOCOL            gEfiSmmTcoDispatchProtocol;
extern EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL        gEfiSmmIoTrapDispatchProtocol;
#endif

// Function Definition(s)

#if (INTEL_RC_SMI_DISPATCHER_SUPPORT == 1) && (PI_0_9_CHILD_DISPATCHER_SUPPORT == 1)
static BOOLEAN PowerBtnSmi = FALSE;

VOID PowerButtonActivated(
    IN EFI_HANDLE                               DispatchHandle,
    IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT    *DispatchContext
    )
{
    PowerBtnSmi = TRUE;
}

VOID AfterChildDispatcher(VOID)
{
    if (PowerBtnSmi)
    {
        PButtonSmiClear();
        SBLib_Shutdown();
        PowerBtnSmi = FALSE;
    }
}

VOID InstallAfterChildDispatcher(VOID)
{
    EFI_STATUS Status;
    EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL *PowerButton;
    EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT DispatchContext = {PowerButtonEntry};
    EFI_HANDLE hPowerButton;

    Status = pBS->LocateProtocol(
                    &gEfiSmmPowerButtonDispatchProtocolGuid,
                    NULL,
                    &PowerButton);
    if (!EFI_ERROR(Status))
    {
        Status = PowerButton->Register(
                        PowerButton,
                        PowerButtonActivated,
                        &DispatchContext,
                        &hPowerButton);
        ASSERT_EFI_ERROR(Status);
    }
}
#endif

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RegisterHandler
//
// Description: This function registers SMI handler and returns registered
//              handle 
//
// Input:       Type        - Type of SMI handler
//              Function    - Pointer to callback function
//              *Context    - Pointer to callback context
//              ContextSize - Callback context size
//              *Handle     - Pointer to store registered handle
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS RegisterHandler (
    IN EFI_SMM_SMI              Type,
    IN VOID                     *Function,
    IN VOID                     *Context,
    IN UINTN                    ContextSize,
    OUT EFI_HANDLE              *Handle )
{
    EFI_STATUS      Status;
    HANDLER_LINK    *HandlerLink;
    Status = SmmHandler[Type].HandlerProtocol.VerifyContext( Context );
    if(EFI_ERROR(Status)) return Status;

    Status = pSmst->SmmAllocatePool( 0,
                                     sizeof(HANDLER_LINK) + ContextSize - 1,
                                     &HandlerLink );
    if(EFI_ERROR(Status)) return Status;

    HandlerLink->Callback = Function;
    HandlerLink->Signature = SMI_HANDLER_SIGNATURE;
    MemCpy( HandlerLink->Context, Context, ContextSize );

    DListAdd(&(SmmHandler[Type].RegisteredCallbacks), (DLINK *)HandlerLink);
    SmmHandler[Type].HandlerProtocol.AddHandler( HandlerLink->Context );
    *Handle = HandlerLink;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   FindHandler
//
// Description: This function find the handle in the Type of SMI hander list.
//
// Input:       Type   - Type of SMI handler
//              Handle - Handle of found handler
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FindHandler(
    IN EFI_SMM_SMI Type,
    IN EFI_HANDLE Handle)
{
    HANDLER_LINK *HandlerLink = (HANDLER_LINK *)Handle;
    HANDLER_LINK *NodeLink = NULL;

    if (HandlerLink->Signature != SMI_HANDLER_SIGNATURE)
        return EFI_INVALID_PARAMETER;

    if (SmmHandler[Type].RegisteredCallbacks.Size <= 0)
        return EFI_UNSUPPORTED;

    NodeLink = (HANDLER_LINK *)SmmHandler[Type].RegisteredCallbacks.pHead;
    for (; NodeLink != NULL; NodeLink = (HANDLER_LINK *)NodeLink->Link.pNext)
    {
        if (NodeLink == HandlerLink)
            return EFI_SUCCESS;
    }

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UnregisterHandler
//
// Description: This function unregisters SMI handler with given handle
//
// Input:       Type   - Type of SMI handler
//              Handle - Handle of registered handler
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UnregisterHandler (
    IN EFI_SMM_SMI          Type,
    IN EFI_HANDLE           Handle )
{
    EFI_STATUS Status;
    HANDLER_LINK *HandlerLink = (HANDLER_LINK *)Handle;

    Status = FindHandler(Type, Handle);
    if (Status == EFI_SUCCESS)
    {
        SmmHandler[Type].HandlerProtocol.RemoveHandler( HandlerLink->Context );
        DListDelete( &(SmmHandler[Type].RegisteredCallbacks), (DLINK *)HandlerLink );
        pSmst->SmmFreePool( HandlerLink );
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ChildDispatcher
//
// Description: This function implements main SMI dispatcher loop
//
// Input:       SmmImageHandle       - SMM Image handle
//              *CommunicationBuffer - Pointer to optional communication
//                                     buffer
//              *SourceSize          - Pointer to size of communication
//                                     buffer
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ChildDispatcher (
    IN EFI_HANDLE       SmmImageHandle,
    IN OUT VOID         *CommunicationBuffer OPTIONAL,
    IN OUT UINTN        *SourceSize OPTIONAL )
{
    UINT32      Index;
    BOOLEAN     HandledSmi;

    do {
        HandledSmi = FALSE;
        for (Index = EfiSmmStandbyButtonSmi; Index < EfiSmmMaxSmi; Index++)
        {
            if (SmmHandler[Index].HandlerProtocol.GetContext != NULL && 
                            SmmHandler[Index].HandlerProtocol.GetContext())
            {
                SmmHandler[Index].HandlerProtocol.DispatchSmi();
                HandledSmi = TRUE;
            }
        }
    } while (HandledSmi);

    SbSmiWorkaround();

#if (INTEL_RC_SMI_DISPATCHER_SUPPORT == 1) && (PI_0_9_CHILD_DISPATCHER_SUPPORT == 1)
    AfterChildDispatcher();
#endif

    return EFI_HANDLER_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: This function initializes Child dispatcher in SMM mode
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction( 
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS      Status;
    EFI_GUID        SbAslBufPtrGuid = SB_ASL_BUFFER_PTR_GUID;
    CHAR16          SbAslBufPtrVar[] = SB_ASL_BUFFER_PTR_VARIABLE;
    EFI_HANDLE      Handle = NULL;
    UINTN           VarSize = sizeof(UINT32);
    UINT32          SbAslBufPtr;

    ClearAllSmi();

    Status = pRS->GetVariable( SbAslBufPtrVar, 
                               &SbAslBufPtrGuid, 
                               NULL, 
                               &VarSize, 
                               &SbAslBufPtr );
    if (!EFI_ERROR(Status)) gSbAslBufPtr = (SB_ASL_BUFFER *)SbAslBufPtr;

    // Install Protocols
    Status = pBS->InstallMultipleProtocolInterfaces(
                                  &Handle, 

#if INTEL_RC_SMI_DISPATCHER_SUPPORT == 0
                                  &gEfiSmmSwDispatchProtocolGuid, 
                                  &gEfiSmmSwDispatchProtocol, 

                                  &gEfiSmmSxDispatchProtocolGuid, 
                                  &gEfiSmmSxDispatchProtocol, 

                                  &gEfiSmmPeriodicTimerDispatchProtocolGuid, 
                                  &gEfiSmmPeriodicTimerDispatchProtocol, 

                                  &gEfiSmmUsbDispatchProtocolGuid, 
                                  &gEfiSmmUsbDispatchProtocol, 

                                  &gEfiSmmGpiDispatchProtocolGuid, 
                                  &gEfiSmmGpiDispatchProtocol, 
#endif

                                  &gEfiSmmStandbyButtonDispatchProtocolGuid, 
                                  &gEfiSmmStandbyButtonDispatchProtocol, 

#if INTEL_RC_SMI_DISPATCHER_SUPPORT == 0
                                  &gEfiSmmPowerButtonDispatchProtocolGuid, 
                                  &gEfiSmmPowerButonDispatchProtocol, 

                                  &gEfiSmmTcoDispatchProtocolGuid, 
                                  &gEfiSmmTcoDispatchProtocol, 

                                  &gEfiSmmIoTrapDispatchProtocolGuid, 
                                  &gEfiSmmIoTrapDispatchProtocol, 

                                  &gEfiSmmBiosWriteDispatchProtocolGuid, 
                                  &gEfiSmmBiosWriteDispatchProtocol, 
#endif

                                  NULL );
    ASSERT_EFI_ERROR(Status);

    Status = pSmmBase->RegisterCallback( pSmmBase, 
                                         ImageHandle, 
                                         ChildDispatcher, 
                                         TRUE, 
                                         FALSE );
    ASSERT_EFI_ERROR(Status);

#if (INTEL_RC_SMI_DISPATCHER_SUPPORT == 1) && (PI_0_9_CHILD_DISPATCHER_SUPPORT == 1)
    InstallAfterChildDispatcher();
#endif

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmChildDispatchEntryPoint
//
// Description: SMM Child Dispatcher module entry point
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmChildDispatchEntryPoint (
    IN EFI_HANDLE               ImageHandle,
    IN EFI_SYSTEM_TABLE         *SystemTable )
{
    InitAmiLib( ImageHandle,SystemTable );

    return InitSmmHandler( ImageHandle, SystemTable, InSmmFunction, NULL );
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
