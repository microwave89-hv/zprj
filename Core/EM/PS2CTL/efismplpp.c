//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/efismplpp.c 7     11/03/11 5:56a Rajeshms $
//
// $Revision: 7 $
//
// $Date: 11/03/11 5:56a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/efismplpp.c $
// 
// 7     11/03/11 5:56a Rajeshms
// [TAG]  		EIP73263
// [Category]  	Improvement
// [Description]  	PS2Ctl Driver Follow the UEFI Driver Model as per the
// UEFI Spec.
// [Files]  		ps2main.c, efismplpp.c
// 
// 6     8/23/10 4:26a Rameshr
// Bug Fix : EIP 40838
// Symptoms: KBC.C build failed in DetectPS2Keyboard() if
// DETECT_PS2_KEYBOARD=0 & PS2MOUSE_SUPPORT=0
// Files Modified: Efismplpp.c, Kbc.c, Kbc.h, Mouse.c PS2ctl.cif,
// Ps2ctl.sdl, Ps2Kbd.c, Ps2Mouse.h
// Details: 
// 1) Added Detect_PS2_Mouse sdl token and modified the code.
// 2) INSTALL_KEYBOARD_MOUSE_ALWAYS sdl token added.
//    1 - Install the Keyboard- SimpleTextIn, Mouse - AbsPointer Always, 
//    0 - Install the Keyboard- SimpleTextIn, Mouse - AbsPointer only if
// the device is present at the time of detection.
//    This is for Ps2Keyboard Hot plug support in EFI 
// 3) Code clean up in mouse.c EfiSmplpp.c ,ps2mouse.h
// 4) Unused file automaton.h removed.
// 
// 5     7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
// 
// 4     12/16/08 2:06a Iminglin
// The function value of StopMouse for compliance.
// 
// 3     4/16/07 6:28p Pats
// Modified to conform with coding standards. No code changes.
// 
// 2     3/04/05 1:37p Mandal
// 
// 1     2/01/05 1:11a Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     10/28/04 10:19a Olegi
// 
// 3     10/04/04 7:42p Olegi
// 
// 2     9/21/04 2:29p Andriyn
// 
// 1     9/14/04 2:56p Andriyn
// 
// 4     9/14/04 2:46p Andriyn
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: efismplpp.c
//
// Description: PS/2 mouse implmentation of simple pointer protocol
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "ps2ctl.h"
#include <AmiLib.h>
#include "ps2ctl.h"
#include "kbc.h"
#include "ps2mouse.h"

//----------------------------------------------------------------------


extern MOUSE gMouse;
extern EFI_GUID gDevicePathProtocolGuid;
EFI_GUID gSimplePointerGuid = EFI_SIMPLE_POINTER_PROTOCOL_GUID;

//----------------------------------------------------------------------


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       StartMouse
//
// Description:     This routine is called from Driver Binding Start function.
//                  It starts the mouse support
//
// Parameters:      
//    EFI_DRIVER_BINDING_PROTOCOL *This -  Pointer to this instance of driver
//                                         binding protocol structure
//    EFI_HANDLE Controller - Handle for this driver
//
// Output:          EFI_STATUS - Status of the operation
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS StartMouse (
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller )
{
    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL *pDummyDevPath;
    MOUSE* pmouse = 0;

    if (EFI_ERROR(gSysTable->BootServices->OpenProtocol(
            Controller,
            &gDevicePathProtocolGuid,
            &pDummyDevPath,
            This->DriverBindingHandle,
            Controller,
            EFI_OPEN_PROTOCOL_BY_DRIVER))) {
        return EFI_INVALID_PARAMETER;
    }

    DetectPS2KeyboardAndMouse();

    if ( EFI_ERROR(InitMOUSE( &pmouse ))) {
        gSysTable->BootServices->CloseProtocol(
            Controller,
            &gDevicePathProtocolGuid,
            This->DriverBindingHandle,
            Controller);

        return EFI_DEVICE_ERROR;
    }

    gSysTable->BootServices->CreateEvent(
        EVT_NOTIFY_WAIT,
        TPL_NOTIFY, 
        OnWaitingOnMouse,
        pmouse,
        &pmouse->iSmplPtr.WaitForInput);
    //
    // Install protocol interfaces for the pointer device.
    //
    Status = gSysTable->BootServices->InstallProtocolInterface (
        &Controller, &gSimplePointerGuid, EFI_NATIVE_INTERFACE,
        &pmouse->iSmplPtr);

    if (EFI_ERROR(Status)) {
        gSysTable->BootServices->CloseProtocol(
            Controller,
            &gDevicePathProtocolGuid,
            This->DriverBindingHandle,
            Controller);

        gSysTable->BootServices->CloseEvent(pmouse->iSmplPtr.WaitForInput);
    }

    return Status;  
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       StopMouse
//
// Description:     This routine is called from Driver Binding Start function.
//                  It stops the mouse support
//
// Parameters:      
//    EFI_DRIVER_BINDING_PROTOCOL *This -  Pointer to this instance of driver
//                                         binding protocol structure
//    EFI_HANDLE Controller - Handle for this driver
//
// Output:           EFI_STATUS - Status of the operation
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS StopMouse (
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller )
{
    EFI_STATUS Status;

    //
    // Kill wait event
    //
    Status = gSysTable->BootServices->CloseEvent(gMouse.iSmplPtr.WaitForInput);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Uninstall protocol interfaces from the Mouse device.
    //
    Status = gSysTable->BootServices->UninstallMultipleProtocolInterfaces (
        Controller,
        &gSimplePointerGuid, &gMouse.iSmplPtr,   
        NULL
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Close protocols that is open during Start
    //
    Status = gSysTable->BootServices->CloseProtocol(
        Controller,
        &gEfiDevicePathProtocolGuid,
        This->DriverBindingHandle,
        Controller);

    if (EFI_ERROR(Status)) {
        return Status;
    }

    pBS->FreePool(gMouse.iSmplPtr.Mode);

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
