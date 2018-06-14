//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/CsmSimpleIn.c 9     10/18/13 10:18a Olegi $
//
// $Revision: 9 $
//
// $Date: 10/18/13 10:18a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Core/CsmSimpleIn.c $
// 
// 9     10/18/13 10:18a Olegi
// [TAG]  		EIP140252
// [Category]  	Improvement
// [Description]  	Connect CsmSimpleIn on ConInStarted installation
// 
// 8     5/27/13 7:20a Rameshr
// [TAG]  		EIP122428
// [Category]  	Improvement
// [Description]  	Clear the LED's status before setting it.
// [Files]  		CsmSimpleIn.c
// 
// 7     2/21/13 12:53p Olegi
// [TAG]  		EIP115727
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	CsmSimpleIn->RegisterKeyNotify problem
// [RootCause]  	If someone uses RegisterKeyNotify() to register
// notification more than one time, then UnRegisterKeyNotify() will free
// wrong pointer when unregistering it.
// [Solution]  	Remove global KEY_WAITING_RECORD variable, add a code to
// manage multiple instances of KEY_WAITING_RECORD
// [Files]  		CsmSimpleIn.c
// 
// 6     9/06/12 8:15a Olegi
// 
// 4     5/14/10 11:13a Olegi
// Modified RegisterKeyNotify/UnregisterKeyNotify functions to pass SCT.
//
// 3     5/07/10 10:23a Olegi
// Added input validation in CsmSimpleInInputReadKeyEx.
//
// 2     1/12/10 11:46a Olegi
// Copyright message updated.
//
// 1     11/10/09 8:16a Olegi
//
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    CsmSimpleIn.c
//
// Description: Implements the SimpleTextIn protocol for the Csm.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <efi.h>
#include <AmiDxeLib.h>
#include <Protocol\SimpleTextIn.h>
#include <Protocol\SimpleTextInEx.h>
#include <Protocol\AmiKeycode.h>
#include <Protocol\SimpleTextOut.h >
#include <Protocol\ConsoleControl.h>


typedef struct _CSMSIMPLEIN_DEV {
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL      SimpleTextInput;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  SimpleTextInputEx;
    AMI_EFIKEYCODE_PROTOCOL             EfiKeycodeInput;
} CSMSIMPLEIN_DEV;

UINT8   CurrentKeyState=0;

typedef struct _KEY_WAITING_RECORD{
  DLINK                                         Link;
  EFI_KEY_DATA                                  Context;
  EFI_KEY_NOTIFY_FUNCTION                       Callback;
} KEY_WAITING_RECORD;

DLIST                               mCsmKeyboardData;

//Simple Input:

EFI_STATUS CsmSimpleInInputReset(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    IN BOOLEAN                          ExtendedVerification
);

EFI_STATUS CsmSimpleInInputReadKey(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    OUT EFI_INPUT_KEY                   *Key
);

//Simple Input Ex:

EFI_STATUS CsmSimpleInInputResetEx(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN BOOLEAN                              ExtendedVerification
);

EFI_STATUS CsmSimpleInInputReadKeyEx(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    OUT EFI_KEY_DATA                        *KeyData
);

EFI_STATUS CsmSimpleInInputSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_KEY_TOGGLE_STATE                 *KeyToggleState
);

EFI_STATUS CsmSimpleInInputRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_KEY_DATA                         *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION              KeyNotificationFunction,
    OUT EFI_HANDLE                          *NotifyHandle
);

EFI_STATUS CsmSimpleInInputUnRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_HANDLE                           NotificationHandle
);

// AMI KeyCode:

EFI_STATUS
CsmSimpleInInputReadEfiKey(
    IN AMI_EFIKEYCODE_PROTOCOL              *This,
    OUT AMI_EFI_KEY_DATA                    *KeyData
);

VOID ConnectCsmSimpleIn(
    IN EFI_EVENT Event, 
    IN VOID *Context
);

EFI_HANDLE          gCsmSimpleInHandle=NULL;


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:  InitCsmSimpleIn
//
// Description: CSM SimpleIn driver entry point,
//
// Input:       Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT
//
// Output:      The status of CSM board initalization
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitCsmSimpleIn (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{

    EFI_STATUS          Status;
    CSMSIMPLEIN_DEV     *CsmSimpleInDev = NULL;
	static EFI_GUID     GuidConInStarted = CONSOLE_IN_DEVICES_STARTED_PROTOCOL_GUID;
	EFI_EVENT 	        Event;
	VOID                *pRegistration;


    Status = pBS->AllocatePool(
                    EfiBootServicesData,
                    sizeof(CSMSIMPLEIN_DEV),
                    &CsmSimpleInDev);

    if (EFI_ERROR(Status)) {
        return Status;
    }

    pBS->SetMem(CsmSimpleInDev, sizeof(CSMSIMPLEIN_DEV), 0);

    CsmSimpleInDev->SimpleTextInput.Reset = CsmSimpleInInputReset;
    CsmSimpleInDev->SimpleTextInput.ReadKeyStroke = CsmSimpleInInputReadKey;
    CsmSimpleInDev->SimpleTextInput.WaitForKey = NULL;

    CsmSimpleInDev->SimpleTextInputEx.Reset = CsmSimpleInInputResetEx;
    CsmSimpleInDev->SimpleTextInputEx.ReadKeyStrokeEx = CsmSimpleInInputReadKeyEx;
    CsmSimpleInDev->SimpleTextInputEx.SetState = CsmSimpleInInputSetState;
    CsmSimpleInDev->SimpleTextInputEx.RegisterKeyNotify = CsmSimpleInInputRegisterKeyNotify;
    CsmSimpleInDev->SimpleTextInputEx.UnregisterKeyNotify = CsmSimpleInInputUnRegisterKeyNotify;
    CsmSimpleInDev->SimpleTextInputEx.WaitForKeyEx = NULL;

    CsmSimpleInDev->EfiKeycodeInput.Reset = CsmSimpleInInputResetEx;
    CsmSimpleInDev->EfiKeycodeInput.ReadEfikey = CsmSimpleInInputReadEfiKey;
    CsmSimpleInDev->EfiKeycodeInput.SetState = CsmSimpleInInputSetState;
    CsmSimpleInDev->EfiKeycodeInput.RegisterKeyNotify = CsmSimpleInInputRegisterKeyNotify;
    CsmSimpleInDev->EfiKeycodeInput.UnregisterKeyNotify = CsmSimpleInInputUnRegisterKeyNotify;
    CsmSimpleInDev->EfiKeycodeInput.WaitForKeyEx = NULL;

    Status = pBS->InstallMultipleProtocolInterfaces(
            &gCsmSimpleInHandle,
            &gEfiSimpleTextInProtocolGuid, &CsmSimpleInDev->SimpleTextInput,
            &gEfiSimpleTextInExProtocolGuid, &CsmSimpleInDev->SimpleTextInputEx,
            &gAmiEfiKeycodeProtocolGuid, &CsmSimpleInDev->EfiKeycodeInput,
            NULL
            );

	RegisterProtocolCallback(
		    &GuidConInStarted, ConnectCsmSimpleIn,
		    NULL, &Event,&pRegistration
	        );


    return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ConnectCsmSimpleIn
//
// Description:
//      This function Connect the CsmSimpleIn handle 
//
// Input:   
//  IN EFI_EVENT Event - signalled event
//  IN VOID *Context - pointer to event context
//
// Output:
//      VOID
// 
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

VOID ConnectCsmSimpleIn(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    // Connect the CsmSimpleIn, So that Consplitter gets notified 
    pBS->ConnectController(gCsmSimpleInHandle, NULL, NULL, TRUE);
    // Kill the Event
    pBS->CloseEvent(Event); 

    return;        
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: CsmSimpleInInputReset
//
// Description: In our implementation, this function does nothing.
//
// Input:
//  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL    *This
//  IN BOOLEAN                  ExtendedVerification
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS CsmSimpleInInputReset(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    IN BOOLEAN                          ExtendedVerification
)
{
    return EFI_SUCCESS;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: CsmSimpleInInputResetEx
//
// Description: In our implementation, this function does nothing.
//
// Input:
//  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This
//  IN BOOLEAN                  ExtendedVerification
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS CsmSimpleInInputResetEx(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN BOOLEAN                              ExtendedVerification
)
{
    return EFI_SUCCESS;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: CsmSimpleInInputReadKey
//
// Description: Returns a EFI_INPUT_KEY Key if possible.
//
// Input:
//  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This
//  OUT EFI_INPUT_KEY                   *Key
//
// Output:
//  EFI_STATUS
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS CsmSimpleInInputReadKey(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    OUT EFI_INPUT_KEY                   *Key
)
{
    return EFI_NOT_READY;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CsmSimpleInToggleState
//
// Description:     Get the Key Toggle State from the BDA
//
// Paremeters:
//                  KeyToggleState - Pointer to the EFI_KEY_TOGGLE_STATE to
//                          set the state for the input device.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CsmSimpleInToggleState(
    OUT EFI_KEY_TOGGLE_STATE *KeyToggleState
)
{
    UINT8   KeyState;

    KeyState = *(UINT8*)(UINTN)0x417;
    if(KeyState != CurrentKeyState) {
        if(KeyState & 0x10) {
            *KeyToggleState |= SCROLL_LOCK_ACTIVE;
        }
        if(KeyState & 0x20) {
            *KeyToggleState |= NUM_LOCK_ACTIVE;
        }
        if(KeyState & 0x40) {
            *KeyToggleState |= CAPS_LOCK_ACTIVE;
        }
        *KeyToggleState |= TOGGLE_STATE_VALID;
        CurrentKeyState=*(UINT8*)(UINTN)0x417;
        return EFI_SUCCESS;
    }
    return EFI_NOT_READY;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CsmSimpleInInputReadKeyEx
//
// Description:     Reads the next keystroke from the input device and
//                  returns data in the form of EFI_KEY_DATA structure.
//                  This routine is a part of SimpleTextInEx protocol
//                  implementation.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmSimpleInInputReadKeyEx(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    OUT EFI_KEY_DATA *KeyData
)
{
    EFI_STATUS  Status;

    if(KeyData == NULL)
        return EFI_INVALID_PARAMETER;

    pBS->SetMem (KeyData, sizeof(EFI_KEY_DATA) , 0);
    Status=CsmSimpleInToggleState(&(KeyData->KeyState.KeyToggleState));
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CsmSimpleInInputSetState
//
// Description:     Set certain state for the input device.
//
// Paremeters:      This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
//                          instance.
//                  KeyToggleState - Pointer to the EFI_KEY_TOGGLE_STATE to
//                          set the state for the input device.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmSimpleInInputSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState
)
{
    if(KeyToggleState == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(*KeyToggleState & TOGGLE_STATE_VALID) ||
        ((*KeyToggleState & (~(TOGGLE_STATE_VALID | KEY_STATE_EXPOSED | SCROLL_LOCK_ACTIVE | NUM_LOCK_ACTIVE | CAPS_LOCK_ACTIVE)))) ) {
        return EFI_UNSUPPORTED;
    }

    CurrentKeyState = *(UINT8*)(UINTN)0x417;

    // Clear NumLock, CapsLock, Scroll Lock status
    CurrentKeyState &= 0x8F;

    if (*KeyToggleState & SCROLL_LOCK_ACTIVE) {
        CurrentKeyState |= 0x10;
    }

    if (*KeyToggleState & NUM_LOCK_ACTIVE) {
        CurrentKeyState |= 0x20;
    }

    if (*KeyToggleState & CAPS_LOCK_ACTIVE) {
        CurrentKeyState |= 0x40;
    }

    *(UINT8*)(UINTN)0x417 = CurrentKeyState;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CsmSimpleInInputRegisterKeyNotify
//
// Description:     Register a notification function for a particular
//                  keystroke for the input device.
//
// Input:           This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
//                          instance.
//                  KeyData - Key value
//                  KeyNotificationFunction- Pointer to the Notification Function
//                  NotificationHandle - Handle to be unregisterd
//
// Output           None
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmSimpleInInputRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT EFI_HANDLE *NotifyHandle
)
{

    EFI_STATUS          Status;
    KEY_WAITING_RECORD  *CsmKeyIn;

    if(KeyData == NULL || KeyNotificationFunction == NULL || NotifyHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }


    //
    // Create database record and add to database
    //
    Status = pBS->AllocatePool (
                      EfiRuntimeServicesData,
                      sizeof (KEY_WAITING_RECORD),
                      &CsmKeyIn
                      );

    if(EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Gather information about the registration request
    //

    CsmKeyIn->Context   = *KeyData;
    CsmKeyIn->Callback  = KeyNotificationFunction;

    DListAdd (&mCsmKeyboardData, &(CsmKeyIn->Link));

    //
    // Child's handle will be the address linked list link in the record
    //
    *NotifyHandle = (EFI_HANDLE) (&CsmKeyIn->Link);

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CsmSimpleInInputUnRegisterKeyNotify
//
// Description:     Removes the notification which was previously
//                  registered by CsmSimpleInInputRegisterKeyNotify.
//
// Input:          This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
//                          instance.
//                  NotificationHandle - Handle to be unregisterd
//
// Output           None
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmSimpleInInputUnRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
)
{
    DLINK               *ListPtr;
    KEY_WAITING_RECORD  *CsmKeyIn;

    if(NotificationHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    ListPtr = mCsmKeyboardData.pHead;
    while ( ListPtr != NULL)
    {
        CsmKeyIn = OUTTER(ListPtr, Link, KEY_WAITING_RECORD);
        if ( (&CsmKeyIn->Link) == NotificationHandle)
        {
            DListDelete(&mCsmKeyboardData, ListPtr);
            pBS->FreePool(CsmKeyIn);
            return EFI_SUCCESS;
        }

        ListPtr = ListPtr->pNext;
    }

    return EFI_INVALID_PARAMETER;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CsmSimpleInInputReadEfiKey
//
// Description:     Reads the next keystroke from the input device and
//                  returns data in the form of AMI_EFI_KEY_DATA structure.
//                  This routine is a part of AmiEfiKeycode protocol
//                  implementation.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CsmSimpleInInputReadEfiKey(
    IN AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA *KeyData
)
{
    EFI_STATUS  Status;
    pBS->SetMem (KeyData, sizeof(AMI_EFI_KEY_DATA) , 0);
    Status=CsmSimpleInToggleState(&(KeyData->KeyState.KeyToggleState));
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
