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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/ps2main.c 22    11/07/12 12:23a Srikantakumarp $
//
// $Revision: 22 $
//
// $Date: 11/07/12 12:23a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/ps2main.c $
// 
// 22    11/07/12 12:23a Srikantakumarp
// [TAG]  		EIP99411
// [Category]  	Improvement
// [Description]  	Add port validation check in the PS2Ctrl module before
// starting the driver.
// [Files]  		kbc.c, kbc.h, mouse.c, ps2main.c, CORE_DXE.sdl, Tokens.c
// 
// 21    2/01/12 2:02a Deepthins
// [TAG]  		EIP63116
// [Category]  	New Feature
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Token.c, Ps2main.c, Ps2kbd.c, Mouse.c, kbc.h, kbc.c,
// CORE_DXE.sdl
// 
// 20    12/15/11 5:42p Artems
// Fixed bug in Supported function
// 
// 19    11/03/11 5:58a Rajeshms
// [TAG]  		EIP73263
// [Category]  	Improvement
// [Description]  	PS2Ctl Driver Follow the UEFI Driver Model as per the
// UEFI Spec.
// [Files]  		ps2main.c, efismplpp.c
// 
// 18    8/02/11 4:43a Rameshr
// [TAG] - EIP 58974
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - Yellow exclamation mark in Windows when PS2 KB/MS are not
// present.
// [RootCause]- ACPI name space variable reports that PS2 device present 
// [Solution] - Updated the SIO device status based on the device present
// after BDS.
// [Files] - Kbc.c, Kbc.h , Ps2main.c
// 
// 17    4/27/11 4:35a Lavanyap
// [TAG] - EIP49407
// [Category] - IMPROVEMENT
// [Description] - Move the Ps2 driver SDL tokens from Core Source to Core
// Bin,So that we don't need to add Core source for changing the Ps2
// driver SDL tokens.
// [Files] - Ps2Ctl.sdl, ps2kbd.c, ps2main.c, ps2ctl.h, kbc.c, mouse.c,
// hotkey.c, CORE_DXE.sdl, Tokens.c
// 
// 16    1/24/11 3:45p Pats
// [TAG] - EIP 18488
// [Category] - Enhancement
// [Severity] - Normal
// [Symptom] - PS2CTL: Need hooks for port swap, Keybaord mouse detect.
// [RootCause] - Support may be needed for kbc controller or SIO with
// different support from AMI KB-5.
// [Solution] - Changes to make AutodetectKbdMousePortsPtr elink
// controlled instead of token controlled.
// [Files] - ps2main.c
// NOTE: Implementation of this change requires changes to CORE_DXE.sdl
// and BdsBoard.c.
// 
// 15    1/05/11 12:43a Rameshr
// [TAG]  		EIPEIP 35306
// [Category]  	Improvement
// [Description]  	Report the Ps2 Controller and Device Error Codes.
// [Files]  		AmiStatuscodes.h, Kbc.c, Kbc.h,Ps2ctl.sdl, ps2kbd.c,
// ps2main.c ,Statuscode.h
// 
// 14    8/28/09 10:03a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 13    7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
// 
// 12    4/16/07 6:28p Pats
// Modified to conform with coding standards. No code changes.
// 
// 11    4/10/07 10:04a Felixp
// LookupHID routine renamed to LookupPs2Hid to avoid linking issue when
// linking with FloppyCtrl module
// 
// 10    3/19/07 2:28p Pats
// Removed test for KBC acrive.
// 
// 9     3/13/07 5:36p Pats
// Fixed problem in last BAT fix.
// 
// 8     3/13/07 2:59p Pats
// Tests for KBC active and skips KBC BAT test if it is. This preserves
// the input key if there is one.
// 
// 7     2/28/07 6:05p Pats
// Made KBC BAT test removable with SDL token, to speed up boot, and to
// keep keep Setup key (F2 or Del) from being absorbed.
// 
// 6     3/13/06 2:38a Felixp
// 
// 5     10/11/05 4:11p Srinin
// KBD and Mouse Start function is called in TPL_NOTIFY state.
// 
// 4     6/03/05 5:35p Felixp
// 
// 2     2/25/05 10:27a Olegi
// 
// 1     2/01/05 1:10a Felixp
// 
// 4     1/31/05 3:12p Felixp
// Driver Binding Installed on a new handle.
// 
// 3     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 2     1/07/05 4:57p Felixp
// Small bug fix in ComponentName Protocol (GetPS2_DP modified)
// 
// 1     10/28/04 10:19a Olegi
// 
// 9     9/30/04 8:13a Olegi
// HotKeys added.
// 
// 8     9/24/04 4:36p Olegi
// 
// 7     9/21/04 5:53p Olegi
// 
// 6     8/27/04 3:17p Olegi
// Header and footer added.
// 
// 5     8/18/04 6:44p Olegi
// Logitech mouse PNPID added.
// 
// 4     8/18/04 6:37p Olegi
// Header and footer added.
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: ps2main.c
//
// Description: PS/2 Controller DXE driver
// This driver supports PS/2 keyboard and/or PS/2 mouse depending on the
// switches in SDL tokens.
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "efi.h"
#include "ps2ctl.h"
#include "kbc.h"
#include <Protocol\ComponentName.h>

//----------------------------------------------------------------------

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
        {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

EFI_GUID    gBdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;

static EFI_GUID gDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
static EFI_GUID gComponentNameProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#else
static EFI_GUID gComponentNameProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
#endif
EFI_GUID gDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
UINT8 gDriverStartCounter;

VOID        *gAllDriverConnectedNotifyRegistration;
EFI_EVENT   gAllDriverConnectedEvent;

extern BOOLEAN Ps2MouseSupport;
extern BOOLEAN Ps2KbdSupport;
extern BOOLEAN KbcBasicAssuranceTest;
extern EFI_COMPONENT_NAME_PROTOCOL  gPS2CtlDriverName;
extern EFI_LEGACY_8259_PROTOCOL     *mLegacy8259;
extern BOOLEAN                      KbRdBeforeInstall; 
extern BOOLEAN                      KbdIrqSupport;
EFI_SYSTEM_TABLE                    *gSysTable = NULL;
extern UINT8                        gKeyboardIrqInstall;
extern  UINT32                      IbFreeTimeoutValue;

  

//==================================================================================
// Function Prototypes for Driver Binding Protocol Interface
//==================================================================================
EFI_STATUS PS2CtlSupported(
        EFI_DRIVER_BINDING_PROTOCOL *This,
        EFI_HANDLE                  Controller,
        EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath);

EFI_STATUS PS2CtlStart(
        EFI_DRIVER_BINDING_PROTOCOL *This,
        EFI_HANDLE                  Controller,
        EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath);

EFI_STATUS PS2CtlStop(
        EFI_DRIVER_BINDING_PROTOCOL *This,
        EFI_HANDLE                  Controller,
        UINTN                       NumberOfChildren,
        EFI_HANDLE                  *ChildHandleBuffer);

//==================================================================================
// Driver binding protocol instance for PS2Ctl Driver
//==================================================================================
EFI_DRIVER_BINDING_PROTOCOL gPS2CtlDriverBinding = {
    PS2CtlSupported,
    PS2CtlStart,
    PS2CtlStop,
    PS2_DRIVER_VER,     // Driver version
    NULL,               // Image Handle
    NULL                // DriverBindingHandle
};

//==================================================================================
// Supported PS2 devices table
//==================================================================================
CHAR16 *gPS2ControllerName = L"PS/2 Controller";

PS2DEV_TABLE    supportedDevices[] = {
    {EISA_PNP_ID(0xF03), 0, DEVICETYPE_MOUSE, StartMouse, StopMouse, L"Microsoft PS/2 Mouse"},
    {EISA_PNP_ID(0xF12), 0, DEVICETYPE_MOUSE, StartMouse, StopMouse, L"Logitech PS/2 Mouse"},
    {EISA_PNP_ID(0xF13), 0, DEVICETYPE_MOUSE, StartMouse, StopMouse, L"Generic PS/2 Mouse"},
    {EISA_PNP_ID(0x303), 1, DEVICETYPE_MOUSE, StartMouse, StopMouse, L"IBM Keyboard, PS/2 Mouse Support"},
    {EISA_PNP_ID(0x303), 0, DEVICETYPE_KEYBOARD, StartKeyboard, StopKeyboard, L"Generic PS/2 Keyboard"},
    {0} // End of table
};


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       PS2CtlEntryPoint
//
// Description:     PS/2 Controller Driver Entry Point
//                  This function is a part of DriverBinfing protocol
//
// Parameters:      EFI_HANDLE ImageHandle - Image handle for this driver
//                                           image
//                  EFI_SYSTEM_TABLE *SystemTable - pointer to the EFI
//                                                  system table
//
// Output:          EFI_STATUS - Status of the operation
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PS2CtlEntryPoint(
    EFI_HANDLE          ImageHandle,
    EFI_SYSTEM_TABLE    *SystemTable )
{
    EFI_STATUS         Status;

    InitAmiLib(ImageHandle,SystemTable);

    gSysTable = SystemTable;
    gPS2CtlDriverBinding.DriverBindingHandle = NULL;
    gPS2CtlDriverBinding.ImageHandle = ImageHandle;

    Status = gSysTable->BootServices->InstallMultipleProtocolInterfaces(
                &gPS2CtlDriverBinding.DriverBindingHandle,
                &gDriverBindingProtocolGuid, &gPS2CtlDriverBinding,
                &gComponentNameProtocolGuid, &gPS2CtlDriverName,
                NULL);

    gDriverStartCounter = 0;

    //
    // Update the SIO variable in the ACPI name space depend on the 
    // Ps2keyboard and Mouse Present state.
    //
    Status = RegisterProtocolCallback(
                    &gBdsAllDriversConnectedProtocolGuid,
                    UpdateSioVariableForKeyboardMouse,
                    NULL,   
                    &gAllDriverConnectedEvent,
                    &gAllDriverConnectedNotifyRegistration
    );
    ASSERT_EFI_ERROR(Status);

    //
    // Initialized Keyboard irq if keys are to be read before starting driver
    // IRQ handler will save the data in temp buffer and once the Keyboard
    // Driver started , the temp buffer data is pushed into Keyboard driver.
    // So that the key's are pressed in post also taken by Ps2 driver
    //
    if(KbRdBeforeInstall){
        if(IoRead8(KBC_CMDSTS_PORT) != 0xFF) { 
            //
            // Enable the Keyboard and Keyboard Interrupt  
            //
            Write8042CommandByte(0x65);
            InitKeyboardIrq();
        }
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       PS2CtlSupported
//
// Description:     PS/2 Controller Driver Supported function
//                  This function is a part of DriverBinfing protocol
//
// Paremeters:      EFI_DRIVER_BINDING_PROTOCOL *This - Pointer to this
//                      instance of the driver binding protocol
//                  EFI_HANDLE Controller - Handle for this controller
//                  EFI_DEVICE_PATH_PROTOCOL - *RemainingDevicePath -
//                      Pointer to last node in device path
//
// Output:          EFI_SUCCESS - Ps2 Controller supported
//                  EFI_UNSUPPORTED -- Ps2 Controller not supported
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PS2CtlSupported(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath)
{
    ACPI_HID_DEVICE_PATH* acpiDP;

    //
    // Checking if KBC is available at all
    //
    if (IoRead8 (KBC_CMDSTS_PORT) == 0xFF){
        return EFI_DEVICE_ERROR;
	}
    //
    // Find the last device node in the device path and return "Supported" 
    // for mouse and/or keyboard depending on the SDL switches.
    //
    if( !EFI_ERROR(GetPS2_DP(This, Controller, &acpiDP, EFI_OPEN_PROTOCOL_BY_DRIVER)) &&
            LookupPs2Hid(supportedDevices, acpiDP->HID, acpiDP->UID, 0)){
        return EFI_SUCCESS;
    } 

    return EFI_UNSUPPORTED;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       PS2CtlStart
//
// Description:     PS/2 Controller Driver Start function
//                  This function is a part of DriverBinfing protocol
//
// Paremeters:      EFI_DRIVER_BINDING_PROTOCOL *This - Pointer to this
//                      instance of the driver binding protocol
//                  EFI_HANDLE Controller - Handle for this controller
//                  EFI_DEVICE_PATH_PROTOCOL - *RemainingDevicePath -
//                      Pointer to last node in device path
//
// Output:          EFI_STATUS - Status of the operation
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PS2CtlStart(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath)
{
    ACPI_HID_DEVICE_PATH    *acpiDP;
    PS2DEV_TABLE            *ps2dev = 0;
    EFI_STATUS              Status;
    EFI_TPL                 OldTpl;

    //
    // The following code performs the basic KBC initialization
    // It has to be executed only once, we use global variable
    // gDriverStartCounter to control this. Also, this code is
    // executed on a higher TPL to prevent re-entrance.
    //
    OldTpl = gSysTable->BootServices->RaiseTPL(TPL_NOTIFY);
    if (OldTpl > TPL_NOTIFY) return EFI_DEVICE_ERROR;
    
    while (!gDriverStartCounter) {
        //
        // Disable the Keyboard IRQ if it's enabled before 
        // Finish all the Keyboard Initilization and Re-enable the IRQ again 
        // 
        if(KbRdBeforeInstall){
            mLegacy8259->DisableIrq( mLegacy8259, SYSTEM_KEYBOARD_IRQ );
            gKeyboardIrqInstall=FALSE;
        }
        // Initialize KBC hardware
        //
        if ( KbcBasicAssuranceTest ) {
            Status = KBCBatTest();      // Perform KBC Basic Assurance Test
            if (EFI_ERROR(Status)) {
                //
                // Report the Error code if the BAT test failed
                //
                ERROR_CODE (DXE_KEYBOARD_STUCK_KEY_ERROR, EFI_ERROR_MAJOR);
                break;
            }

            //
            // Check for stuck keys
            //
            Status = IbFreeTimeout(IbFreeTimeoutValue);
            if (EFI_ERROR(Status)) {
                //
                // Report the Error Code.
                //
                ERROR_CODE (DXE_KEYBOARD_STUCK_KEY_ERROR, EFI_ERROR_MAJOR);
                break;
            }
        }
        // Swap ports if needed
        if (AutodetectKbdMousePortsPtr!=NULL) AutodetectKbdMousePortsPtr();
    
        gDriverStartCounter++;
    }
    
    
    if(!EFI_ERROR(GetPS2_DP(This, Controller, &acpiDP, EFI_OPEN_PROTOCOL_BY_DRIVER)) &&
            LookupPs2Hid(supportedDevices, acpiDP->HID, acpiDP->UID, &ps2dev) ){
             Status = ps2dev->start(This, Controller);

            //
            // End of critical section - restore TPL
            //
            gSysTable->BootServices->RestoreTPL(OldTpl);

            if(EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            }

            return EFI_SUCCESS;
    } 
        
    //
    // End of critical section - restore TPL
    //
    gSysTable->BootServices->RestoreTPL(OldTpl);

    //
    // If control is here then something totally wrong happend:
    // if device is not supported then Start shouldn't be called.
    //
    return EFI_DEVICE_ERROR;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       PS2CtlStop
//
// Description:     PS/2 Controller Driver Stop function
//                  This function is a part of DriverBinfing protocol
//
// Paremeters:      EFI_DRIVER_BINDING_PROTOCOL *This - Pointer to this
//                      instance of the driver binding protocol
//                  EFI_HANDLE Controller - Handle for this controller
//                  UINTN NumberOfChildren - Number of children of this
//                      controller
//                  EFI_HANDLE *ChildHandleBuffer - Pointer to a buffer
//                      for child handles
//
// Output:          EFI_STATUS - Status of the operation
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PS2CtlStop(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *ChildHandleBuffer)
{
    ACPI_HID_DEVICE_PATH        *acpiDP;
    PS2DEV_TABLE                *ps2dev = 0;
    EFI_STATUS                  Status;

    if(!EFI_ERROR(GetPS2_DP(This, Controller, &acpiDP, EFI_OPEN_PROTOCOL_GET_PROTOCOL)) &&
            LookupPs2Hid(supportedDevices, acpiDP->HID, acpiDP->UID, &ps2dev) ){
        Status = ps2dev->stop(This, Controller);
        if(EFI_ERROR(Status)) {
            return EFI_DEVICE_ERROR;
        }
        return EFI_SUCCESS;
    } 

    //
    // If control is here then device path was not found in the lookup table
    //
    return EFI_DEVICE_ERROR;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       LookupPs2Hid
//
// Description:     This fuction searches the PS2 device in table that 
//                  matches given HID and UID
//
// Paremeters:
//  PS2DEV_TABLE *  devTable - Lookup table pointer
//  UINT32          hid - HID to look for
//  UINT32          uid - UID to look for
//  PS2DEV_TABLE**  dev - address of the matched table entry
//
// Output:
//          BOOLEAN - TRUE if match is found, FALSE otherwise
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN LookupPs2Hid(
    PS2DEV_TABLE *  devTable,
    UINT32          hid,
    UINT32          uid,
    PS2DEV_TABLE**  dev)
{
    for( ;devTable->hid;++devTable){
        if( devTable->hid == hid && devTable->uid==uid){
            if ( (devTable->DeviceType == DEVICETYPE_MOUSE && Ps2MouseSupport) ||
                 (devTable->DeviceType == DEVICETYPE_KEYBOARD && Ps2KbdSupport) ) {
                if(dev) *dev = devTable;
                return TRUE;
            }
        } 
    }
    return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetPS2_DP
//
// Description:     This fuction returns the last node in the device 
//                  path for the given controller.
//
// Paremeters:      EFI_DRIVER_BINDING_PROTOCOL *This - Pointer to this
//                      instance of the driver binding protocol
//                  EFI_HANDLE Controller - Handle for this controller
//                  ACPI_HID_DEVICE_PATH** ps2dp - Pointer to ACPI HID
//                      device path
//                  UINT32 Attributes - Attributes passed to driver binding
//                      protocol
//
// Output:
//          EFI_SUCCESS or EFI_UNSUPPORTED
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetPS2_DP(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    ACPI_HID_DEVICE_PATH**      ps2dp,
    UINT32                      Attributes)
{   
    EFI_STATUS Status;
    ACPI_HID_DEVICE_PATH        *acpiDP;
    EFI_DEVICE_PATH_PROTOCOL    * ps2DevPath, *pDP;

    //
    // Get device path from Controller handle.
    //
    Status = gSysTable->BootServices->OpenProtocol (
                Controller,
                &gDevicePathProtocolGuid,
                (VOID**)&pDP,
                This->DriverBindingHandle,
                Controller,   
                Attributes
                );
  
    if (EFI_ERROR(Status)) {
        if( Status != (EFI_ALREADY_STARTED || EFI_ACCESS_DENIED) ) {
            return EFI_UNSUPPORTED;
        } else { 
            return Status;
        }
    }

    //
    // Process ps2DevPath - get the node which is before the EndNode
    //
    ps2DevPath=DPGetLastNode(pDP);

    //
    // ps2DevPath is now the last node
    //
    acpiDP = *ps2dp = (ACPI_HID_DEVICE_PATH*)ps2DevPath;

    Status = (acpiDP->Header.Type == ACPI_DEVICE_PATH && 
        acpiDP->Header.SubType == ACPI_DP)? EFI_SUCCESS : EFI_UNSUPPORTED;

    if (Attributes!=EFI_OPEN_PROTOCOL_GET_PROTOCOL)
        gSysTable->BootServices->CloseProtocol (
            Controller,
            &gDevicePathProtocolGuid,
            This->DriverBindingHandle,
            Controller
            );

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
