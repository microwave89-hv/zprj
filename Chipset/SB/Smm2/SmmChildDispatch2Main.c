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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatch2Main.c 4     10/19/12 2:52a Scottyang $
//
// $Revision: 4 $
//
// $Date: 10/19/12 2:52a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatch2Main.c $
// 
// 4     10/19/12 2:52a Scottyang
// [TAG]       EIP93461
// [Category]  Bug Fix
// [Severity]  Normal
// [Symptom]   System halt when AFUDOS is running with /N /ME command.
// [RootCause] An unexpected BIOSWR_STS is set, it causes BIOS stuck
//             at SMM dispatcher.
// [Solution]  Clear BIOSWR_STS if BIOS Lock Enable is not set.
// [Files]     SmiHandlerPorting2.c; SmmChildDispatch2Main.c
//             SmmChildDispatcher2.sdl; SmmChildDispatch2.h
//             SB\SBGeneric.c
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
// Name:        SmmChildDispatch2Main.c
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
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmCpu.h>
#include "SmmChildDispatch2.h"
#include "SmmChildDispatch2Protocol.h"

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

EFI_SMM_SMI_CONTEXT2    SmiContext;
EFI_SMM_BASE2_PROTOCOL  *gSmmBase2;
EFI_SMM_SYSTEM_TABLE2   *gSmst2;
EFI_SMM_CPU_PROTOCOL    *gEfiSmmCpuProtocol;

// GUID Definition(s)

EFI_GUID gEfiSmmChildDispatcher2Guid = SMM_CHILD_DISPATCHER2_GUID;

// Protocol Definition(s)

// External Declaration(s)

extern SMM_CHILD_DISPATCHER2 Smm2Handler[];

extern EFI_SMM_SW_DISPATCH2_PROTOCOL gEfiSmmSwDispatch2Protocol;
extern EFI_SMM_SX_DISPATCH2_PROTOCOL gEfiSmmSxDispatch2Protocol;
extern EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL gEfiSmmPeriodicTimerDispatch2Protocol;
extern EFI_SMM_USB_DISPATCH2_PROTOCOL gEfiSmmUsbDispatch2Protocol;
extern EFI_SMM_GPI_DISPATCH2_PROTOCOL gEfiSmmGpiDispatch2Protocol;
extern EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL gEfiSmmStandbyButtonDispatch2Protocol;
extern EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL gEfiSmmPowerButonDispatch2Protocol;
extern EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL gEfiSmmIoTrapDispatch2Protocol;

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RegisterHandler2
//
// Description: This function registers SMI II handler and returns registered
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

EFI_STATUS RegisterHandler2 (
    IN EFI_SMM_SMI2                 Type,
    IN SMI_GENERIC_CALLBACK2        Function,
    IN VOID                         *Context,
    IN UINTN                        ContextSize,
    OUT EFI_HANDLE                  *Handle )
{
    EFI_STATUS      Status;
    HANDLER_LINK2   *HandlerLink;

    Status = Smm2Handler[Type].HandlerProtocol.VerifyContext( Context );
    if(EFI_ERROR(Status)) return Status;

    Status = gSmst2->SmmAllocatePool( 0,
                                     sizeof(HANDLER_LINK2) + ContextSize - 1,
                                     &HandlerLink );
    if(EFI_ERROR(Status)) return Status;

    HandlerLink->Callback = Function;
    HandlerLink->Signature = SMI_HANDLER_SIGNATURE;
    MemCpy( HandlerLink->Context, Context, ContextSize );

    DListAdd(&(Smm2Handler[Type].RegisteredCallbacks), (DLINK *)HandlerLink);

    Smm2Handler[Type].HandlerProtocol.AddHandler( HandlerLink->Context );
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
    IN EFI_SMM_SMI2 Type,
    IN EFI_HANDLE Handle)
{
    HANDLER_LINK2 *HandlerLink = (HANDLER_LINK2 *)Handle;
    HANDLER_LINK2 *NodeLink = NULL;

    if (HandlerLink->Signature != SMI_HANDLER_SIGNATURE)
        return EFI_INVALID_PARAMETER;

    if (Smm2Handler[Type].RegisteredCallbacks.Size <= 0)
        return EFI_UNSUPPORTED;

    NodeLink = (HANDLER_LINK2 *)Smm2Handler[Type].RegisteredCallbacks.pHead;
    for (; NodeLink != NULL; NodeLink = (HANDLER_LINK2 *)NodeLink->Link.pNext)
    {
        if (NodeLink == HandlerLink)
            return EFI_SUCCESS;
    }

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UnregisterHandler2
//
// Description: This function unregisters SMI II handler with given handle
//
// Input:       Type   - Type of SMI handler
//              Handle - Handle of registered handler
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UnregisterHandler2 (
    IN EFI_SMM_SMI2         Type,
    IN EFI_HANDLE           Handle )
{
    EFI_STATUS Status;
    HANDLER_LINK2 *HandlerLink = (HANDLER_LINK2 *)Handle;

    Status = FindHandler(Type, Handle);
    if (Status == EFI_SUCCESS)
    {
        Smm2Handler[Type].HandlerProtocol.RemoveHandler( HandlerLink->Context );
        DListDelete( &(Smm2Handler[Type].RegisteredCallbacks), (DLINK *)HandlerLink );
        gSmst2->SmmFreePool( HandlerLink );
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   ChildDispatcher2
//
// Description: This function implements main SMI II dispatcher.
//
// Input:       DispatchHandle  - SMM dispatch handle
//              *Context        - Pointer to the dispatched context
//              CommBuffer      - Pointer to a collection of data in memory
//                                that will be conveyed from a non-SMM 
//                                environment into an SMM environment.
//              CommBufferSize  - Pointer to the size of the CommBuffer
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ChildDispatcher2 (
    IN EFI_HANDLE           DispatchHandle,
    IN CONST VOID           *Context OPTIONAL,
    IN OUT VOID             *CommBuffer OPTIONAL,
    IN OUT UINTN            *CommBufferSize OPTIONAL )
{
    EFI_STATUS  Status = EFI_UNSUPPORTED;
    UINT32      Index;
    BOOLEAN     HandledSmi;

    do
    {
        HandledSmi = FALSE;
        for (Index = EfiSmmSwSmi2; Index < EfiSmmMaxSmi2; Index++)
        {
            if (Smm2Handler[Index].HandlerProtocol.GetContext != 0 && 
                Smm2Handler[Index].HandlerProtocol.GetContext())
            {
                Status = Smm2Handler[Index].HandlerProtocol.DispatchSmi();
                if (Status != EFI_WARN_INTERRUPT_SOURCE_QUIESCED)
                {
                    HandledSmi = TRUE;
                }
            }
        }
    } while (HandledSmi);
                                        // [EIP93461]>
    SbSmiWorkaround2();
                                        // <[EIP93461]
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

EFI_STATUS InSmmFunction ( 
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS      Status;
    EFI_HANDLE      Handle = NULL;
    EFI_HANDLE      BsHandle = NULL;
    EFI_HANDLE      RootHandle;

#if (CHILD_DISPATCHER_SUPPORT == 0)
    ClearAllSmi();
#endif

    // Locate SMM CPU Protocols
    Status = gSmst2->SmmLocateProtocol( &gEfiCpuProtocolGuid,
                                        NULL,
                                        &gEfiSmmCpuProtocol);

    // Install Protocols
    Status = gSmst2->SmmInstallProtocolInterface(
                                    &Handle,
                                    &gEfiSmmSwDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gEfiSmmSwDispatch2Protocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(
                                    &BsHandle,
                                    &gEfiSmmSwDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);

    Status = gSmst2->SmmInstallProtocolInterface(
                                    &Handle,
                                    &gEfiSmmSxDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gEfiSmmSxDispatch2Protocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(
                                    &BsHandle,
                                    &gEfiSmmSxDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);

    Status = gSmst2->SmmInstallProtocolInterface(
                                    &Handle,
                                    &gEfiSmmPeriodicTimerDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gEfiSmmPeriodicTimerDispatch2Protocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(
                                    &BsHandle,
                                    &gEfiSmmPeriodicTimerDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);

    Status = gSmst2->SmmInstallProtocolInterface(
                                    &Handle,
                                    &gEfiSmmUsbDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gEfiSmmUsbDispatch2Protocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(
                                    &BsHandle,
                                    &gEfiSmmUsbDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);

    Status = gSmst2->SmmInstallProtocolInterface(
                                    &Handle,
                                    &gEfiSmmGpiDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gEfiSmmGpiDispatch2Protocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(
                                    &BsHandle,
                                    &gEfiSmmGpiDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);

    Status = gSmst2->SmmInstallProtocolInterface(
                                    &Handle,
                                    &gEfiSmmStandbyButtonDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gEfiSmmStandbyButtonDispatch2Protocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(
                                    &BsHandle,
                                    &gEfiSmmStandbyButtonDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);

    Status = gSmst2->SmmInstallProtocolInterface(
                                    &Handle,
                                    &gEfiSmmPowerButtonDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gEfiSmmPowerButonDispatch2Protocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(
                                    &BsHandle,
                                    &gEfiSmmPowerButtonDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);

    Status = gSmst2->SmmInstallProtocolInterface(
                                    &Handle,
                                    &gEfiSmmIoTrapDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gEfiSmmIoTrapDispatch2Protocol);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->InstallProtocolInterface(
                                    &BsHandle,
                                    &gEfiSmmIoTrapDispatch2ProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);

    Status = gSmst2->SmiHandlerRegister(ChildDispatcher2, NULL, &RootHandle);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SmmChildDispatch2EntryPoint
//
// Description: SMM Child Dispatcher II module entry point
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmChildDispatch2EntryPoint (
    IN EFI_HANDLE               ImageHandle,
    IN EFI_SYSTEM_TABLE         *SystemTable )
{
    EFI_STATUS Status;
    BOOLEAN InSmram = FALSE;

    InitAmiLib( ImageHandle, SystemTable );

    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
    if (!EFI_ERROR(Status))
    {
        Status = gSmmBase2->InSmm(gSmmBase2, &InSmram);
        if ((!EFI_ERROR(Status)) &&
            (InSmram))
        {
            Status = InitAmiSmmLib( ImageHandle, SystemTable );
            if (EFI_ERROR(Status))
                return Status;

            Status = gSmmBase2->GetSmstLocation(gSmmBase2, &gSmst2);
            if (!EFI_ERROR(Status))
            {
                Status = InSmmFunction(ImageHandle, SystemTable);
                return Status;
            }
            else
            {
                gSmst2 = NULL;
            }
        }
        else
        {
            // DXE initialize.
        }
    }

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
