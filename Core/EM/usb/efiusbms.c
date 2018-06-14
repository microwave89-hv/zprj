//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbms.c 30    3/02/16 9:43p Wilsonlee $
//
// $Revision: 30 $
//
// $Date: 3/02/16 9:43p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbms.c $
// 
// 30    3/02/16 9:43p Wilsonlee
// [TAG]  		EIP254309
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	GK-FORCE K83 USB KB function abnormal.
// [RootCause]  	This device has an interrupt out endpoint and doesn't
// support "Set Report" request.
// [Solution]  	Use the interrupt out endpoint instead of sending "Set
// Report" request.
// [Files]  		AmiUsbController.h, xhci.c, usbmass.c, usbkbd.h, usbkbd.c,
// usbhub.c, usbhid.c, usbdef.h, usbCCID.c, usb.c, uhci.c, ohci.c, ehci.c,
// amiusb.h, efiusbms,c, amiusbhc.c
// 
// 29    5/28/15 5:01a Wilsonlee
// [TAG]  		EIP218997
// [Category]  	Improvement
// [Description]  	Break the GetQueue loop if UninstallDevice is failed.
// [Files]  		usbbus.c, efiusbkb.c, efiusbmass.c, efiusbms.c,
// efiusbpoint.c, efiusbhid.c
// 
// 28    2/18/14 9:54p Wilsonlee
// Add a #ifndef CR around the definition of the CR MACRO.
// 
// 27    12/30/13 3:48a Wilsonlee
// [TAG]  		EIP148707
// [Category]  	Improvement
// [Description]  	We need to store wheel data before clearing the buffer.
// [Files]  		usbms.c, efiusbms.c
// 
// 26    10/24/13 10:25p Wilsonlee
// [TAG]  		EIP131339
// [Category]  	Improvement
// [Description]  	Synchronize USB\Touch device mouse pointer position.
// [Files]  		efiusbms.c, efiusbpoint.c
// 
// 25    7/24/13 2:35a Roberthsu
// [TAG]           EIP121333
// [Category]      Improvement
// [Description]   Multiple USB mouse support for UEFI USB mouse driver
// [Files]         efiusbhid.c,efiusbkb.h,efiusbms.c
// 
// 24    3/19/13 4:00a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 23    10/27/12 10:26a Ryanchou
// [TAG]  		EIP104380
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	USB mouse button are lost in Wave application
// [RootCause]  	WaitForInput() clears button state, button is incorrect
// when calling GetState().
// [Solution]  	Keep the button state in WaitForInput().
// [Files]  		efiusbms.c
// 
// 22    9/19/11 9:31a Lavanyap
// [TAG]  		EIP66198
// [Category]  	Improvement
// [Description]  	Added Mouse Wheel support in PS2 and USB drivers. 
// [Files]  		usbdef.h, usbms.c, efiusbms.c, ps2mouse.h, mouse.c
// 
// 21    7/12/11 11:40p Ryanchou
// [TAG] EIP63752
// [Bug fix] Left click status lost on USB Mousee.
// [Symptom] First time Getstate will return that Left Click is Pressed.
// On the Second GetState Call it will return that Left click released.
// [Root Cause] We are clearing the Button status once we send the data.
// So next time getstate will return that left click is released.
// [Solution] We should not clear the ButtonStatus.Insteed of OR the data,
// we should have taken directly from the fpBuffer.
// 
// 20    5/03/11 10:48a Ryanchou
// [TAG]  		EIP59272
// [Category]  	Improvement
// [Description]  	According Uefi 2.1 Aptio porting document, changes made
// to install the component name protocol.
// [Files]  		componentname.c, componentname.h, efiusbkb.c, efiusbmass.c,
// efiusbms.c, uhcd.c, uhcd.h, usbbus.c
// 
// 19    3/04/11 1:31p Olegi
// 
// 18    3/04/11 1:25p Olegi
// [TAG]  		EIP55172
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Install EFI_COMPONENT_NAME_PROTOCOL if BIOS is in UEFI
// 2.0 mode and EFI_COMPONENT_NAME2_PROTOCOL if BIOS is in UEFI 2.1 mode.
// [Files]  		uhcd.c
// usbbus.c
// efiusbkb.c
// efiusbmass.c
// efiusbms.c
// componentname.c
// componentname.h
// 
// 17    12/02/10 2:24p Olegi
// [TAG]  		EIP48695
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	SCT Error for USB HC SyncInterruptTransfer API
// [RootCause]  	Checking for endpoint being IN was missing.
// [Solution]  	Corrected EFI USB mouse driver that issues the
// SyncInterruptTransfer with the wrong endpoint address.
// 
// 16    10/30/10 2:40a Ryanchou
// EIP38221: Added the code that properly initializes
// DEV_INFO.bIntEndpoint field; interrupt endpoint polling is using this
// endpoint number.
// 
// 15    9/16/10 12:59p Olegi
// EIP40959:: Modifications in UpdateUsbMouseData. Depending on the
// project settings mouse data is either obtained via polling TD, or using
// direct mouse access.
// 
// 14    5/11/10 9:33a Olegi
// Corrected the mouse data report. EIP37798
// 
// 13    2/23/10 1:36p Olegi
// Work around Klockwork issues. EIP34370
// 
// 12    1/07/09 3:11p Olegi
// EIP#16970:  Fix for the USB mouse right click issue:
// If the right mouse button is pressed, value of variable "RightButton"
// is not updated properly.
// The variable "RightButton" is BOOLEAN. But when right click is done on
// USB mouse, the value of "RightButton" is 0x02, which is not correct.
// The value should be TRUE if right click is done.
// Changed the code to save TRUE in RightButton instead of saving as 0x02.
// Even if we typecast the result of (bData & 0x02) to BOOLEAN and save it
// in a BOOLEAN variable RightButton, it is saved as 0x02. Hence changed
// the code to save TRUE if BIT 1 in variable bData is set else save FALSE
// in variable RightButton.
// 
// 10    9/16/08 2:05p Olegi
// Modifications in UpdateUsbMouseData, EIP#15780.
// 
// 9     7/07/08 4:01p Olegi
// 
// 8     5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
// 
// 7     3/20/07 1:29p Olegi
//
// 5     10/12/06 7:12p Andriyn
// Support unexpected plug-off USB device
//
// 4     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 3     5/19/05 8:06p Olegi
// Aptio changes in driver 8.1 implementation.
//
// 2     5/17/05 7:51p Andriyn
// USB BUS pre-release
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           EFIUSBMS.C
//
//  Description:    EFI USB Mouse Driver
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"
#include "componentname.h"
#include "usbbus.h"

#define USBMS_DRIVER_VERSION 2

#define USB_MOUSE_DEV_SIGNATURE   EFI_SIGNATURE_32('u','m','o','u')

#ifndef CR
#define CR(record, TYPE, field, signature) _CR(record, TYPE, field) 
#endif
#define USB_MOUSE_DEV_FROM_MOUSE_PROTOCOL(a,b) \
    CR(a, USB_MOUSE_DEV, b, USB_MOUSE_DEV_SIGNATURE)

typedef struct
{
    UINTN                           Signature;
    UINT8                           NumberOfButtons;
    INT32                           XLogicMax;
    INT32                           XLogicMin;
    INT32                           YLogicMax;
    INT32                           YLogicMin;
    EFI_SIMPLE_POINTER_PROTOCOL     SimplePointerProtocol;
    EFI_SIMPLE_POINTER_MODE         Mode;
    UINT8                           Endpoint;
    EFI_USB_IO_PROTOCOL             *UsbIo;
} USB_MOUSE_DEV;

static VOID
UsbMouseWaitForInput (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  );

static EFI_STATUS
UpdateUsbMouseData (
    EFI_SIMPLE_POINTER_PROTOCOL  *This, 
	EFI_SIMPLE_POINTER_STATE	*State
  );

//
// Mouse Protocol
//
static EFI_STATUS
GetMouseState(
  IN   EFI_SIMPLE_POINTER_PROTOCOL  *This,
  OUT  EFI_SIMPLE_POINTER_STATE     *MouseState
);

static EFI_STATUS
UsbMouseReset(
  IN EFI_SIMPLE_POINTER_PROTOCOL    *This,
  IN BOOLEAN                        ExtendedVerification
  );

extern USB_GLOBAL_DATA *gUsbData;

BOOLEAN                         StateChanged; 
UINT8                           ButtonsState; 
EFI_SIMPLE_POINTER_STATE        MsState;



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        InitUSBMouse
//
// Description: Initialize USB mouse device and all private data structures.
//
// Input:       None
//
// Output:      EFI_SUCCESS or EFI_ERROR
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitUSBMouse()
{
    EfiZeroMem (&MsState, sizeof(EFI_SIMPLE_POINTER_STATE));
    ButtonsState = 0;
    StateChanged = FALSE; 
    return EFI_SUCCESS;
}  

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        InstallUSBMouse
//
// Description: Installs SimplePointerProtocol interface on a given controller.
//
// Input:       Controller - controller handle to install interface on.
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
InstallUSBMouse(
    EFI_HANDLE Controller,
    EFI_USB_IO_PROTOCOL *UsbIo,
    DEV_INFO *DevInfo
)
{
    USB_MOUSE_DEV       *UsbMouse; 
    EFI_STATUS Status;

    VERIFY_EFI_ERROR(
        Status = gBS->AllocatePool(
        EfiBootServicesData,
        sizeof(USB_MOUSE_DEV),
        &UsbMouse));

    EfiZeroMem(UsbMouse, sizeof(USB_MOUSE_DEV));

    //
    // Initialize UsbMouseDevice
    //
    UsbMouse->Signature = USB_MOUSE_DEV_SIGNATURE;
    UsbMouse->SimplePointerProtocol.GetState = GetMouseState;
    UsbMouse->SimplePointerProtocol.Reset = UsbMouseReset;
    UsbMouse->SimplePointerProtocol.Mode = &UsbMouse->Mode;

    UsbMouse->NumberOfButtons = 2;
    UsbMouse->XLogicMax = UsbMouse->YLogicMax = 127;
    UsbMouse->XLogicMin = UsbMouse->YLogicMin = -127;

    UsbMouse->Mode.LeftButton = TRUE;
    UsbMouse->Mode.RightButton = TRUE;
    UsbMouse->Mode.ResolutionX = 8;
    UsbMouse->Mode.ResolutionY = 8;
    UsbMouse->Mode.ResolutionZ = 1; 

    UsbMouse->UsbIo = UsbIo;
    UsbMouse->Endpoint = DevInfo->IntInEndpoint;

    UsbMouseReset(NULL, FALSE);
 
    VERIFY_EFI_ERROR(
        Status = gBS->CreateEvent (
        EFI_EVENT_NOTIFY_WAIT,
        EFI_TPL_NOTIFY,
        UsbMouseWaitForInput,
        UsbMouse,
        &((UsbMouse->SimplePointerProtocol).WaitForInput)
        ));

    USB_DEBUG(DEBUG_LEVEL_4, "Mouse event is created, status = %r\n", Status);

    //
    // Install protocol interfaces for the USB mouse device
    //
    VERIFY_EFI_ERROR(
        Status = gBS->InstallProtocolInterface(
        &Controller,
        &gEfiSimplePointerProtocolGuid,
        EFI_NATIVE_INTERFACE,
        &UsbMouse->SimplePointerProtocol));

    USB_DEBUG(DEBUG_LEVEL_4, "Mouse protocol is installed, status = %r\n", Status);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UninstallUSBMouse
//
// Description: Stops USB mouse device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UninstallUSBMouse (
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE Controller,
    UINTN NumberOfChildren,
    EFI_HANDLE *Children
)
{
    EFI_STATUS Status;
    EFI_SIMPLE_POINTER_PROTOCOL     *SimplePoint; 
    USB_MOUSE_DEV       *UsbMouse = 0; 
 

    Status = gBS->OpenProtocol(Controller,
                                &gEfiSimplePointerProtocolGuid,
                                (VOID **)&SimplePoint,
                                This->DriverBindingHandle,
                                Controller,
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL); 

    UsbMouse = USB_MOUSE_DEV_FROM_MOUSE_PROTOCOL(SimplePoint,SimplePointerProtocol);
    
    Status = gBS->UninstallProtocolInterface(Controller, &gEfiSimplePointerProtocolGuid,
                        &UsbMouse->SimplePointerProtocol);
    
    if (EFI_ERROR(Status)) {
        return Status;
    }

    VERIFY_EFI_ERROR(gBS->CloseEvent(
            (UsbMouse->SimplePointerProtocol).WaitForInput));

    gBS->FreePool(UsbMouse);
    
    return Status;
} 


/************ SimplePointer Protocol implementation routines*************/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbMouseReset
//
// Description: This routine is a part of SimplePointerProtocol implementation;
//              it resets USB mouse.
//
// Input:       This - A pointer to the EFI_SIMPLE_POINTER_PROTOCOL instance.
//              ExtendedVerification - Indicates that the driver may perform
//              a more exhaustive verification operation of the device during
//              reset.
//
// Output:      EFI_SUCCESS or EFI_DEVICE_ERROR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static EFI_STATUS
UsbMouseReset(
    IN EFI_SIMPLE_POINTER_PROTOCOL    *This,
    IN BOOLEAN                        ExtendedVerification
  )
{
    EfiZeroMem (
        &MsState,
        sizeof(EFI_SIMPLE_POINTER_STATE)
        );
    StateChanged = FALSE;
    
    EfiZeroMem (&gUsbData->MouseData, sizeof(MOUSE_DATA));

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        GetMouseState
//
// Description: This routine is a part of SimplePointerProtocol implementation;
//              it retrieves the current state of a pointer device.
//
// Input:       This - A pointer to the EFI_SIMPLE_POINTER_PROTOCOL instance.
//              MouseState - A pointer to the state information on the pointer
//              device. Type EFI_SIMPLE_POINTER_STATE is defined as follows:
//                typedef struct {
//                    INT32 RelativeMovementX;
//                    INT32 RelativeMovementY;
//                    INT32 RelativeMovementZ;
//                    BOOLEAN LeftButton;
//                    BOOLEAN RightButton;
//                } EFI_SIMPLE_POINTER_STATE;
//
// Output:      EFI_SUCCESS      - The state of the pointer device was returned
//                                 in MouseState.
//              EFI_NOT_READY    - The state of the pointer device has not changed
//                                 since the last call to GetMouseState().
//              EFI_DEVICE_ERROR - A device error occurred while attempting to
//                                 retrieve the pointer device’s current state.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static EFI_STATUS
GetMouseState(
    EFI_SIMPLE_POINTER_PROTOCOL  *This,
    EFI_SIMPLE_POINTER_STATE     *MouseState
)
{
    if (MouseState == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    return UpdateUsbMouseData(This,MouseState);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UpdateUsbMouseData
//
// Description: This routine updates current mouse data.
//
// Input:       Data* - pointer to the data area to be updated.
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static EFI_STATUS
UpdateUsbMouseData (
    EFI_SIMPLE_POINTER_PROTOCOL  *This,
	EFI_SIMPLE_POINTER_STATE	*State
)
{
    BOOLEAN LeftButton, RightButton;
    INT32   rX, rY, rZ;
    UINT8   bData;
    EFI_STATUS  Status;
    UINT8   MouseData[4];
    UINTN   DataLength;
    UINT32  UsbStatus;
    INT32   Coordinates;
    USB_MOUSE_DEV       *UsbMouse = 0; 
 
    if ((gUsbData->dUSBStateFlag & USB_FLAG_EFIMS_DIRECT_ACCESS) && (This != NULL) ){
        UsbMouse = USB_MOUSE_DEV_FROM_MOUSE_PROTOCOL(This,SimplePointerProtocol); 
        // Get the data from mouse
        DataLength = 4;
    
        Status = UsbMouse->UsbIo->UsbSyncInterruptTransfer(
            UsbMouse->UsbIo,
            UsbMouse->Endpoint | 0x80,    // IN
            MouseData,
            &DataLength,
            0,  // Timeout
            &UsbStatus
        );
    
        gUsbData->MouseData.ButtonStatus = MouseData[0];
    
        Coordinates = (INT8)MouseData[1];
        gUsbData->MouseData.MouseX += Coordinates;
        Coordinates = (INT8)MouseData[2];
        gUsbData->MouseData.MouseY += Coordinates;
     }

    bData = gUsbData->MouseData.ButtonStatus & 7;

    //
    // Check mouse Data
    //
	LeftButton=(BOOLEAN)(bData & 0x01)?TRUE:FALSE;
	RightButton=(BOOLEAN)(bData & 0x02)?TRUE:FALSE;

    rX = gUsbData->MouseData.MouseX;
    rY = gUsbData->MouseData.MouseY;
    rZ = - (gUsbData->MouseData.MouseZ);

	if (StateChanged == FALSE) {
		if (rX == 0 && rY == 0 && rZ == 0 && 
			bData == ButtonsState) {
			return EFI_NOT_READY;
		}
        StateChanged = TRUE;
	}

    gUsbData->MouseData.MouseX=0;
    gUsbData->MouseData.MouseY=0;
    gUsbData->MouseData.MouseZ=0;

    ButtonsState = bData;
    MsState.LeftButton = LeftButton;
    MsState.RightButton = RightButton;
    MsState.RelativeMovementX += rX;
    MsState.RelativeMovementY += rY;
    MsState.RelativeMovementZ += rZ; 


	if (State != NULL) {
		EfiCopyMem(State, &MsState, sizeof(EFI_SIMPLE_POINTER_STATE));
	    //
	    // Clear previous move state
	    //
        MsState.RelativeMovementX = 0;
        MsState.RelativeMovementY = 0;
        MsState.RelativeMovementZ = 0;  
        StateChanged = FALSE;
	}

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbMouseWaitForInput
//
// Description: Event notification function for SIMPLE_POINTER.WaitForInput
//              event. Signal the event if there is input from mouse.
//
// Input:       Event - event to signal in case of mouse activity
//              Context - data to pass along with the event.
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static VOID
EFIAPI
UsbMouseWaitForInput (
    EFI_EVENT   Event,
    VOID        *Context
    )
{
	EFI_STATUS Status;
    USB_MOUSE_DEV       *UsbMouse = (USB_MOUSE_DEV*)Context; 

    Status = UpdateUsbMouseData (&UsbMouse->SimplePointerProtocol,NULL);
	if (EFI_ERROR(Status)) {
		return;
	}

    //
    // Someone is waiting on the mouse event, if there's
    // input from mouse, signal the event
    //
    gBS->SignalEvent(Event);

}



//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbMsInit
//
// Description: Initialize USB Mouse driver
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

CHAR16*
UsbMsGetControllerName(
    EFI_HANDLE Controller,
    EFI_HANDLE Child
)
{
    return 0;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
