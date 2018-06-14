//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/ConSplitter/In.c 5     7/08/15 4:32a Chienhsieh $
//
// $Revision: 5 $
//
// $Date: 7/08/15 4:32a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/ConSplitter/In.c $
// 
// 5     7/08/15 4:32a Chienhsieh
// Update for eip217417.
// 
// 4     8/02/13 4:26a Thomaschen
// Add for EIP109384.
// [Files]  ConSplit.c, ConSplit.h, In.c, CsmSimpleIn.c.
// 
// 3     6/26/13 3:11a Thomaschen
// Remove EIP109384.
// 
// 1     6/04/13 1:52a Thomaschen
// Fixed for EIP118202.
// 
// 32    10/25/12 2:33a Deepthins
// [TAG]  		EIP99475
// [Category]  	Improvement
// [Description]  	Multi language module Support in the console splitter
// 
// [Files]  		ConSplit.c, ConSplit.h , In.c and AmiKeycode.h
// 
// 31    7/20/12 10:38a Artems
// [TAG]  		EIP93929
// [Description]  	Implement support to initialize the Keyboard in first
// call of readkeystoke in fast boot case
// [Files]  		In.c
// 
// 30    4/11/12 5:35p Artems
// [TAG]  		EIPN/A
// [Category]  	Bug Fix
// [Symptom]  	Function SetState was not broadcasted to third party
// drivers
// [RootCause]  	Splitter uses AMI proprietary protocol to broadcast
// SetState function
// which is not installed by third party drivers
// [Solution]  	Modified splitter to broadcast SetState function via
// SimpleTextInEx protocol
// [Files]  		in.c
// 
// 29    3/21/12 12:53p Artems
// EIP 83358: Fixed bug in SimplePointerGetState function, where
// EFI_SUCCESS was lost if ohter device returns DEVICE_ERROR
// 
// 28    9/22/11 6:29a Rameshr
// [TAG]  		EIP63054
// [Category]  	New Feature
// [Description]  	0000790: Add warning to ReadKeyStrokeEx for partial key
// press
// [Files]  		KeyboardCommonDefinitions.h, In.c, Kbc.h, Ps2Kbd.c,
// Efiusbkb.c, efiusbkb.h
// 
// 27    7/21/11 3:41p Aaronp
// // [TAG]  		EIP65187 
// // [Category]  	Bug Fix
// // [Severity]  	Minor
// // [Symptom]  	unicode character was not returned when english selected
// // and alt key pressed
// // [RootCause]  	The EFI_HII_KEYBOARD_LAYOUT table provides the
// AltGraphic
// // and Shifted AltGraphic unicode definitions for key combinations, and
// // there are NULL values for undefined key combinations.  
// // [Solution]  	Changed how the EFI_HII_KEYBOARD_LAYOUT table is
// consumed
// // so that the current unicode character in the AMI_EFI_KEY_DATA
// structure
// // will not be overwritten when the EFI_HII_KEYBOARD_LAYOUT has a NULL
// // value in the matching table entry.
// // [Files]  		In.c
// 
// 25    5/05/11 4:53p Artems
// Removed unnecessary checks
// 
// 24    5/05/11 3:54p Artems
// Added multi-language keyboard support
// 
// 23    8/10/10 2:29p Vyacheslava
// Initialized default value of Status in the
// ConSplitterSimplePointerReset function.
// 
// 22    6/23/10 3:02p Felixp
// SimplePointer splitter support is added.
// 
// 21    1/18/10 3:40a Rameshr
// NumLock,Capslock,Scroll Lock LED's synced properly between Keyboard
// connect and disconnect.
// EIP 27917
// 
// 20    10/09/09 12:15p Felixp
// SetState function is updated to process all the physical devices
// despite the errors returned by some of them.
// 
// 19    8/13/09 3:04p Rameshr
// When item "num-lock status" set off, Num-lock will keep open until in
// DOS.
// EIP:21757
// 
// 18    7/07/09 3:35p Artems
// Added functions headers according to code standard
// 
// 17    4/30/09 5:45p Felixp
// Minor improvements on the pause key implementation.
// 
// 16    3/30/09 10:24a Pats
// Issue: EIP 19547 - Pause key support needed in Aptio
// Solution: Function CsReadEfiKey modified to enter pause loop when pause
// key detected. Requires mod in Ps2Kbd.c and efiusbkb.c.
// 
// 15    1/23/09 9:55a Rameshr
// Symptom:SCT failure in ReadKeystrokeEx function.
// Solution: Validated the Input parameters Keydata for the
// ReadKeystrokeEx Function.
// Eip: 19039
// 
// 14    11/17/08 10:22a Rameshraju
// Problem:SCT failure on RegisterKeyNotify, SetState and
// UnregisterKeyNotify.
// Fix : Validated the input parameters for RegisterKeyNotify, SetState
// and UnregisterKeyNotify.
// EIP:17578
// 
// 13    10/08/08 4:27p Olegi
// Implemented the Register/Unregister key notofocation function in
// SimpletextinEx protocol.
// 
// 12    3/17/08 4:49p Rameshraju
// ReadEfiKey doesnt not return correct key value randomly.
// 
// 11    1/31/08 12:00p Olegi
// Numlock bootup state made setup driven.
// 
// 10    11/16/07 4:05p Olegi
// Modifications in CSReadKeyStroke function.
// 
// 9     10/23/07 4:14p Olegi
// Modifications in CSInSetState that allow the sync between the Input
// Devices' LEDs.
// 
// 8     10/16/07 10:47a Olegi
// Modification in CSReadEfiKey().
// 
// 7     9/17/07 4:04p Olegi
// Added support for AMI_EFIKEYCODE_PROTOCOL and
// EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.
// 
// 6     9/05/07 11:13a Felixp
// SimpleTextInEx support removed. It causes problems. Support will add
// again after Core labeling.
// 
// 3     3/13/06 2:37a Felixp
// 
// 2     11/07/05 10:37a Felixp
// LockStdIn function of ConsoleControl protocol implemented
// 
// 1     1/28/05 1:16p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     1/07/05 11:57a Felixp
// 
// 2     1/03/05 5:47p Robert
// Working beta version of the consplitter
// 
// 1     12/30/04 9:47a Robert
// Initial check in 
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        Out.c
//
// Description: File contains the Simple Text Output functionality for the 
//		        Console Splitter Driver
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------------

#include "ConSplit.h"
#include "token.h"
#include <Protocol/SimplePointer.h>

//----------------------------------------------------------------------------
extern EFI_HII_KEYBOARD_LAYOUT *gKeyDescriptorList;
extern EFI_KEY_TOGGLE_STATE mCSToggleState;
EFI_SIMPLE_POINTER_MODE gSimplePointerMode = {
    0x10000,
    0x10000,
    0x10000,
    FALSE,
    FALSE
};

VOID ConnectInputDevices(
    VOID
);

//----------------------------------------------------------------------------

EFI_SIMPLE_TEXT_INPUT_PROTOCOL mCSSimpleInProtocol = {
	CSInReset,
	CSReadKeyStroke,
	NULL
	} ;

EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL mCSSimpleInExProtocol = 	{
	CSInResetEx,
	CSReadKeyStrokeEx,
	NULL,
    CSInSetState,
    CSInRegisterKeyNotify,
    CSInUnRegisterKeyNotify
	} ;

AMI_EFIKEYCODE_PROTOCOL mCSKeycodeInProtocol = 	{
	CSInResetEx,
	CSReadEfiKey,
	NULL,
    CSInSetState,
    CSInRegisterKeyNotify,
    CSInUnRegisterKeyNotify
	} ;

EFI_SIMPLE_POINTER_PROTOCOL mCSSimplePointerProtocol = {
    ConSplitterSimplePointerReset,
    ConSplitterSimplePointerGetState,
    ConSplitterSimplePointerWaitForInput,
    &gSimplePointerMode
};

//----------------------------------------------------------------------------


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ConSplitterSimplePointerReset
//
// Description: Resets the pointer device hardware.
//
// Input:   
//  *This - pointer to protocol instance.
//  ExtendedVerification - Driver may perform diagnostics on reset.
//
// Output:
//          EFI_SUCCESS - device was reset successfully
//          EFI_ERROR - some of devices returned error
// 
//----------------------------------------------------------------------------
// <AMI_PHDR_END>         

EFI_STATUS ConSplitterSimplePointerReset (
    IN  EFI_SIMPLE_POINTER_PROTOCOL *This,
    IN  BOOLEAN ExtendedVerification )
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_STATUS TestStatus;
    CON_SPLIT_SIMPLE_POINTER *ConSimplePointer = NULL;

    if (StdInLocked) 
        return EFI_ACCESS_DENIED;

    if (ConPointerList.pHead == NULL)
        return EFI_DEVICE_ERROR;

    ConSimplePointer = OUTTER(ConPointerList.pHead, Link, CON_SPLIT_SIMPLE_POINTER);

    // we need to loop through all the registered simple pointer devices
    // and call each of their Reset function
    while (ConSimplePointer != NULL) {
        TestStatus = ConSimplePointer->SimplePointer->Reset(ConSimplePointer->SimplePointer, ExtendedVerification);
        ConSimplePointer = OUTTER( ConSimplePointer->Link.pNext, Link, CON_SPLIT_SIMPLE_POINTER );

        if (EFI_ERROR(TestStatus))
            Status = TestStatus;
    }

    return Status;
}


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ConSplitterSimplePointerGetState
//
// Description: Retrieves the current state of a pointer device.
//  Reads the next keystroke from the input device. The WaitForKey Event can
//  be used to test for existance of a keystroke via WaitForEvent () call.
//  If the ConIn is password locked make it look like no keystroke is availible
//
// Input:   
//    This   - Protocol instance pointer.
//    State  - A pointer to the state information on the pointer device.
//
// Output:
//    EFI_SUCCESS       - The keystroke information was returned.
//    EFI_NOT_READY     - There was no keystroke data availiable.
//    EFI_DEVICE_ERROR  - The keydtroke information was not returned due to
//                        hardware errors.
// 
//----------------------------------------------------------------------------
// <AMI_PHDR_END>         

EFI_STATUS ConSplitterSimplePointerGetState(
    IN  EFI_SIMPLE_POINTER_PROTOCOL *This,
    IN OUT EFI_SIMPLE_POINTER_STATE *State )
{
    EFI_STATUS Status; 
    EFI_SIMPLE_POINTER_STATE  CurrentState;
    CON_SPLIT_SIMPLE_POINTER *ConSimplePointer = NULL;
    BOOLEAN EfiSuccessDetected = FALSE;
    BOOLEAN EfiDeviceErrorDetected = FALSE;
    BOOLEAN EfiNotReadyDetected = FALSE;

    if (StdInLocked) 
        return EFI_ACCESS_DENIED;

    if (ConPointerList.pHead == NULL)
        return EFI_DEVICE_ERROR;

    ConSimplePointer = OUTTER( ConPointerList.pHead, Link, CON_SPLIT_SIMPLE_POINTER );
    
    State->RelativeMovementX  = 0;
    State->RelativeMovementY  = 0;
    State->RelativeMovementZ  = 0;
    State->LeftButton         = FALSE;
    State->RightButton        = FALSE;

    // we need to loop through all the registered simple pointer devices
    while (ConSimplePointer != NULL) {

        Status = ConSimplePointer->SimplePointer->GetState(ConSimplePointer->SimplePointer, &CurrentState);

        if (!EFI_ERROR(Status)) {
        
            EfiSuccessDetected = TRUE;

            if (CurrentState.LeftButton)
                State->LeftButton = TRUE;
     
            if (CurrentState.RightButton)
                State->RightButton = TRUE;
     
            if ( CurrentState.RelativeMovementX != 0 && ConSimplePointer->SimplePointer->Mode->ResolutionX != 0 )
                State->RelativeMovementX += 
                    (CurrentState.RelativeMovementX * (INT32)gSimplePointerMode.ResolutionX) / 
                    (INT32)ConSimplePointer->SimplePointer->Mode->ResolutionX;

            if ( CurrentState.RelativeMovementY != 0 && ConSimplePointer->SimplePointer->Mode->ResolutionY != 0 )
                State->RelativeMovementY += 
                    (CurrentState.RelativeMovementY * (INT32)gSimplePointerMode.ResolutionY) / 
                    (INT32)ConSimplePointer->SimplePointer->Mode->ResolutionY;

            if ( CurrentState.RelativeMovementZ != 0 && ConSimplePointer->SimplePointer->Mode->ResolutionZ != 0 )
                State->RelativeMovementZ += 
                    (CurrentState.RelativeMovementZ * (INT32)gSimplePointerMode.ResolutionZ) / 
                    (INT32)ConSimplePointer->SimplePointer->Mode->ResolutionZ;

        } else if (Status == EFI_DEVICE_ERROR) {
            EfiDeviceErrorDetected = TRUE;
        } else {
            EfiNotReadyDetected = TRUE;
        }

        ConSimplePointer = OUTTER( ConSimplePointer->Link.pNext, Link, CON_SPLIT_SIMPLE_POINTER );
    }

    return (EfiSuccessDetected) ? EFI_SUCCESS : (EfiDeviceErrorDetected) ? EFI_DEVICE_ERROR : EFI_NOT_READY;
}


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ConSplitterSimplePointerWaitForInput
//
// Description: This is callback function for WaitForInputEvent to use with 
//  WaitForEvent() to wait for input from the pointer device.
//
// Input:   
//  Event   - The Event assoicated with callback.
//  Context - Context registered when Event was created.
//
// Output: VOID
// 
//----------------------------------------------------------------------------
// <AMI_PHDR_END>         

VOID ConSplitterSimplePointerWaitForInput(
    IN  EFI_EVENT Event,
    IN  VOID *Context )
{
    EFI_STATUS Status = EFI_SUCCESS; 
    EFI_STATUS TestStatus;
    CON_SPLIT_SIMPLE_POINTER *ConSimplePointer = NULL;

    if (StdInLocked) 
        return;
        
    if (ConPointerList.pHead == NULL) 
        return;

    ConSimplePointer = OUTTER( ConPointerList.pHead, Link, CON_SPLIT_SIMPLE_POINTER );

    // loop through simple pointer events and check their events 
    // if one event has been signaled, signal my event and exit.
    // we need to loop through all the registered simple pointer devices
    while (ConSimplePointer != NULL) {
        TestStatus = pBS->CheckEvent(ConSimplePointer->SimplePointer->WaitForInput);
        ConSimplePointer = OUTTER( ConSimplePointer->Link.pNext, Link, CON_SPLIT_SIMPLE_POINTER );

        if (!EFI_ERROR(TestStatus))
            pBS->SignalEvent(Event);
    }

    return;
}


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSInReset
//
// Description:
//  This function resets the input device hardware. This routine is a part
//  of SimpleTextIn protocol implementation.
//
// Input:   
//  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This - pointer to protocol instance
//  IN BOOLEAN EV - flag if Extended verification has to be performed
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - device was reset successfully
//          EFI_ERROR - some of devices returned error
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
// <AMI_PHDR_END>         

EFI_STATUS CSInReset( 
	IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,	
	IN BOOLEAN                        EV 
)
{
	EFI_STATUS	Status = EFI_SUCCESS, TestStatus;
	CON_SPLIT_IN *SimpleIn;

	if (StdInLocked) return EFI_ACCESS_DENIED;

	if (ConInList.pHead == NULL)
		return EFI_SUCCESS;

    SimpleIn = OUTTER(ConInList.pHead, Link, CON_SPLIT_IN);

	// we need to loop through all the registered simple text out devices
	//	and call each of their Reset function
	while ( SimpleIn != NULL)
	{
		TestStatus = SimpleIn->SimpleIn->Reset(SimpleIn->SimpleIn, EV);
		SimpleIn = OUTTER(SimpleIn->Link.pNext, Link, CON_SPLIT_IN);

		if (EFI_ERROR(TestStatus))
			Status = TestStatus;
	}

	return Status;

}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSReadKeyStroke
//
// Description:
//  This function reads the next keystroke from the input device. This 
//  routine is a part of SimpleTextIn protocol implementation
//
// Input:   
//  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This - pointer to protocol instance
//  OUT EFI_INPUT_KEY *Key - key pressed information
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - Keystroke data successfully retrieved
//          EFI_NOT_READY - There was no keystroke data available
//          EFI_DEVICE_ERROR - The keystroke information was not returned
//                             due to hardware error
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>             

EFI_STATUS CSReadKeyStroke(
	IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	OUT	EFI_INPUT_KEY                  *Key 
)
{
	EFI_STATUS	Status;
    AMI_EFI_KEY_DATA EfiKeyData;

    Status = CSReadEfiKey ( (AMI_EFIKEYCODE_PROTOCOL*) This, &EfiKeyData );
    if (Status == EFI_SUCCESS) {
        //
        // Check for the Partial Key. If found, SimpleTextIn ReadKeyStroke
        // Should not return that Key has bee found.
        //
        if(EfiKeyData.Key.ScanCode == 00 && EfiKeyData.Key.UnicodeChar == 0 &&
             (EfiKeyData.KeyState.KeyToggleState & KEY_STATE_EXPOSED )) {
            return EFI_NOT_READY;
        }
        *Key = EfiKeyData.Key;
        return EFI_SUCCESS;
    }

	return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSWaitForKey
//
// Description:
//  This function is a callback for the EFI_SIMPLE_TEXT_INPUT_PROTOCOL.WaitForKey event
//  Checks whether the new key is available and if so - signals the event
//
// Input:   
//  IN EFI_EVENT Event - event to signal
//  IN VOID *Context - pointer to event specific context
//
// Output:
//      VOID
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>         

VOID CSWaitForKey(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
	EFI_STATUS	Status = EFI_SUCCESS, TestStatus;
	CON_SPLIT_IN *SimpleIn;

	if (StdInLocked) return ;
	if (ConInList.pHead == NULL) return;

// loop through simple in events and check their events 
//	if one event has been signaled, signal my event and exit

    SimpleIn = OUTTER(ConInList.pHead, Link, CON_SPLIT_IN);

	// we need to loop through all the registered simple text out devices
	//	and call each of their Reset function
	while ( SimpleIn != NULL)
	{
		TestStatus = pBS->CheckEvent(SimpleIn->SimpleIn->WaitForKey);
		SimpleIn = OUTTER(SimpleIn->Link.pNext, Link, CON_SPLIT_IN);

		if (!EFI_ERROR(TestStatus))
     		pBS->SignalEvent (Event);
	}

	return;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSInResetEx
//
// Description:
//  This function resets the input device hardware. This routine is a part
//  of SimpleTextInEx protocol implementation
//
// Input:   
//  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This - pointer to protocol instance
//  IN BOOLEAN ExtendedVerification - flag if Extended verification has to be performed
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - device was reset successfully
//          EFI_ERROR - some of devices returned error
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSInResetEx( 
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,  
    IN BOOLEAN                           ExtendedVerification )
{
    return CSInReset(0, ExtendedVerification);
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSReadKeyStrokeEx
//
// Description:
//  This function reads the next keystroke from the input device. This 
//  routine is a part of SimpleTextInEx protocol implementation
//
// Input:   
//  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This - pointer to protocol instance
//  OUT EFI_KEY_DATA *KeyData - key pressed information
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - Keystroke data successfully retrieved
//          EFI_NOT_READY - There was no keystroke data available
//          EFI_DEVICE_ERROR - The keystroke information was not returned
//                             due to hardware error
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSReadKeyStrokeEx (
    IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    OUT EFI_KEY_DATA                      *KeyData
)
{
	EFI_STATUS	Status;
    AMI_EFI_KEY_DATA EfiKeyData;

    if(KeyData == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    Status = CSReadEfiKey ( (AMI_EFIKEYCODE_PROTOCOL*) This, &EfiKeyData );
    if (Status == EFI_SUCCESS) {
        KeyData->Key = EfiKeyData.Key;
        KeyData->KeyState = EfiKeyData.KeyState;
        return EFI_SUCCESS;
    }

	return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSReadEfiKey
//
// Description:
//  This function reads the next keystroke from the input device. This 
//  routine is a part of AmiKeyCode protocol implementation
//
// Input:   
//  IN AMI_EFIKEYCODE_PROTOCOL *This - pointer to protocol instance
//  OUT AMI_EFI_KEY_DATA *KeyData - key pressed information
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - Keystroke data successfully retrieved
//          EFI_NOT_READY - There was no keystroke data available
//          EFI_DEVICE_ERROR - The keystroke information was not returned
//                             due to hardware error
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSReadEfiKey (
    IN  AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA        *KeyData
)
{
	AMI_EFI_KEY_DATA	TempKey;
	EFI_STATUS	Status = EFI_NOT_READY;
	CON_SPLIT_IN *SimpleIn;

	if (StdInLocked) return EFI_ACCESS_DENIED;

    ConnectInputDevices();

	if (ConInList.pHead == NULL) return EFI_NOT_READY;

    SimpleIn = OUTTER(ConInList.pHead, Link, CON_SPLIT_IN);

    pBS->SetMem(KeyData, sizeof(AMI_EFI_KEY_DATA), 0);

	// we need to loop through all the registered EfiKey, SimpleInEx and
    // SimpleIn devices and call each of their ReadKeyStroke function
	while (SimpleIn != NULL)
	{
        if (SimpleIn->KeycodeInEx) {
    		Status = SimpleIn->KeycodeInEx->ReadEfikey(SimpleIn->KeycodeInEx, &TempKey);
        } else if(SimpleIn->SimpleInEx != NULL) {
    		Status = SimpleIn->SimpleInEx->ReadKeyStrokeEx(
                        SimpleIn->SimpleInEx, (EFI_KEY_DATA*)&TempKey);
        } else if(SimpleIn->SimpleIn != NULL) {
            Status = SimpleIn->SimpleIn->ReadKeyStroke(
                        SimpleIn->SimpleIn, (EFI_INPUT_KEY*)&TempKey);
        }

        // Check for the Toggle State change
        if (!EFI_ERROR(Status) && (TempKey.KeyState.KeyToggleState & TOGGLE_STATE_VALID)) {
            if ((TempKey.KeyState.KeyToggleState & ~KEY_STATE_EXPOSED ) != mCSToggleState) {
                mCSToggleState = (TempKey.KeyState.KeyToggleState & ~KEY_STATE_EXPOSED);
                CSInSetState ( (EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*) This,
                                &mCSToggleState );
            }
        }

		if (!EFI_ERROR(Status)) {
			*KeyData = TempKey;
            break;
        }

		SimpleIn = OUTTER(SimpleIn->Link.pNext, Link, CON_SPLIT_IN);
	}
#if PAUSEKEY_SUPPORT
    if (!EFI_ERROR(Status) && TempKey.EfiKey == EfiKeyPause) {
        while(TRUE) {
            Status = CSReadEfiKey ( This, &TempKey );
            if ((!EFI_ERROR(Status)) && (TempKey.EfiKey != EfiKeyPause) && (TempKey.EfiKey != 0x55)) {
                break;
            }
        }
        *KeyData = TempKey;
    }
#endif
	return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSInSetState
//
// Description:
//  This function sets certain state for input device
//
// Input:   
//  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This - pointer to protocol instance
//  IN EFI_KEY_TOGGLE_STATE *KeyToggleState - pointer to state to set
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - Keystroke data successfully retrieved
//          EFI_UNSUPPORTED - Given state not supported
//          EFI_INVALID_PARAMETER - KeyToggleState is NULL
//          EFI_DEVICE_ERROR - input device not found
//          EFI_ACCESS_DENIED - input device is busy
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSInSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE              *KeyToggleState
)
{
	EFI_STATUS	Status = EFI_SUCCESS;
	CON_SPLIT_IN *SimpleIn;

	if (StdInLocked) return EFI_ACCESS_DENIED;

	if (ConInList.pHead == NULL)
		return EFI_UNSUPPORTED;

    if(KeyToggleState == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(*KeyToggleState & TOGGLE_STATE_VALID) || 
        ((*KeyToggleState & (~(TOGGLE_STATE_VALID | KEY_STATE_EXPOSED | 
                            SCROLL_LOCK_ACTIVE | NUM_LOCK_ACTIVE | CAPS_LOCK_ACTIVE)))) ) {
        return EFI_UNSUPPORTED;
    }

    mCSToggleState = *KeyToggleState;  // Update global toggle state

    SimpleIn = OUTTER(ConInList.pHead, Link, CON_SPLIT_IN);

	// we need to loop through all the registered KeycodeInEx devices
	//	and call each of their SetState function
	while ( SimpleIn != NULL )
	{
        if (SimpleIn->SimpleInEx) {
    		SimpleIn->SimpleInEx->SetState(SimpleIn->SimpleInEx, KeyToggleState);
        }
		SimpleIn = OUTTER(SimpleIn->Link.pNext, Link, CON_SPLIT_IN);
	}
	
	return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSInKeyNotificationFunction
//
// Description:
//
// Input:
//
// Output:
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS
CSInKeyNotificationFunction(
    IN EFI_KEY_DATA *KeyData
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    DLINK           *ListPtr;
    UINTN           Index = 0;
    UINTN           Count = 0;
    EFI_KEY_NOTIFY_FUNCTION *NotifyFunctionList = NULL;
    CON_SPLIT_IN_KEY_NOTIFY *CsInKeyNotify = NULL;

    if (StdInLocked) return EFI_ACCESS_DENIED;

    if (ConInKeyNotifyList.pHead == NULL) return EFI_DEVICE_ERROR;

    Status = pBS->AllocatePool(EfiBootServicesData, 
                ConInKeyNotifyList.Size * sizeof(EFI_KEY_NOTIFY_FUNCTION), 
                (VOID**)&NotifyFunctionList);
    if (EFI_ERROR(Status)) {
        return EFI_OUT_OF_RESOURCES;
    }

    for (ListPtr = ConInKeyNotifyList.pHead; ListPtr != NULL; ListPtr = ListPtr->pNext) {
        CsInKeyNotify = OUTTER(ListPtr, Link, CON_SPLIT_IN_KEY_NOTIFY);

        if (!MemCmp(&(CsInKeyNotify->KeyData), KeyData, sizeof(CsInKeyNotify->KeyData))) {
            NotifyFunctionList[Count++] = CsInKeyNotify->KeyNotificationFunction;
        }
    }

    for (Index = 0; Index < Count; Index++) {
        NotifyFunctionList[Index](&(CsInKeyNotify->KeyData));
    }

    pBS->FreePool(NotifyFunctionList);
 
    return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSInRegisterKeyNotify
//
// Description:
//  This function registers a notification function for a particular
//  keystroke of the input device
//
// Input:   
//  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This - pointer to protocol instance
//  IN EFI_KEY_DATA *KeyData - key value
//  IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction - notification function
//  OUT EFI_HANDLE *NotifyHandle - returned registered handle
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - notification function registered successfully
//          EFI_INVALID_PARAMETER - KeyData/KeyNotificationFunction/NotifyHandle is NULL
//          EFI_DEVICE_ERROR - input device not found
//          EFI_ACCESS_DENIED - input device is busy
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSInRegisterKeyNotify(
    IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN  EFI_KEY_DATA                      *KeyData,
    IN  EFI_KEY_NOTIFY_FUNCTION           KeyNotificationFunction,
    OUT EFI_HANDLE                        *NotifyHandle
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    DLINK           *ListPtr = NULL;
    CON_SPLIT_IN    *ConIn = NULL;
    CON_SPLIT_IN_KEY_NOTIFY         *CsInKeyNotify = NULL;
    CON_SPLIT_IN_KEY_NOTIFY_HANDLE  *CsInNotifyHandle = NULL;

    if (StdInLocked) return EFI_ACCESS_DENIED;

    if(KeyData == NULL || KeyNotificationFunction == NULL || NotifyHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    for (ListPtr = ConInKeyNotifyList.pHead; ListPtr != NULL; ListPtr = ListPtr->pNext) {
        CsInKeyNotify = OUTTER(ListPtr, Link, CON_SPLIT_IN_KEY_NOTIFY);

        if ((!MemCmp(&CsInKeyNotify->KeyData, KeyData, sizeof(CsInKeyNotify->KeyData))) &&
            (CsInKeyNotify->KeyNotificationFunction == KeyNotificationFunction)) {
            *NotifyHandle = (EFI_HANDLE)&(CsInKeyNotify->Link);
            return EFI_SUCCESS;
        }

    }

    Status = pBS->AllocatePool(EfiBootServicesData, 
                sizeof(CON_SPLIT_IN_KEY_NOTIFY), &CsInKeyNotify);
    if (EFI_ERROR(Status)) {
        return EFI_OUT_OF_RESOURCES;
    }

    MemCpy(&(CsInKeyNotify->KeyData), KeyData, sizeof(CsInKeyNotify->KeyData));
    CsInKeyNotify->KeyNotificationFunction = KeyNotificationFunction;
    DListAdd(&ConInKeyNotifyList, &(CsInKeyNotify->Link));
    DListInit(&(CsInKeyNotify->NotifyHandleList));
    // we need to loop through all the registered SimpleInEx 
    // and call each of their ReadKeyStroke function
    for (ListPtr = ConInList.pHead; ListPtr != NULL; ListPtr = ListPtr->pNext) {
        ConIn = OUTTER(ListPtr, Link, CON_SPLIT_IN);

        if (ConIn->SimpleInEx == NULL) {
            continue;
        }

        Status = pBS->AllocatePool(EfiBootServicesData, 
                     sizeof(CON_SPLIT_IN_KEY_NOTIFY_HANDLE), &CsInNotifyHandle);
        if (EFI_ERROR(Status)) {
            break;
        }

        CsInNotifyHandle->SimpleInEx = ConIn->SimpleInEx;
        DListAdd(&(CsInKeyNotify->NotifyHandleList), &(CsInNotifyHandle->Link));

        Status = ConIn->SimpleInEx->RegisterKeyNotify(ConIn->SimpleInEx, 
                    KeyData, CSInKeyNotificationFunction, &(CsInNotifyHandle->NotifyHandle));
        if (EFI_ERROR(Status)) {
            break;
        }
    }

    if (EFI_ERROR(Status)) {
        for (ListPtr = CsInKeyNotify->NotifyHandleList.pHead; 
                ListPtr != NULL; ListPtr = ListPtr->pNext) {
            CsInNotifyHandle = OUTTER(ListPtr, Link, CON_SPLIT_IN_KEY_NOTIFY_HANDLE);

            CsInNotifyHandle->SimpleInEx->UnregisterKeyNotify(
                        CsInNotifyHandle->SimpleInEx, CsInNotifyHandle->NotifyHandle);

            DListDelete(&(CsInKeyNotify->NotifyHandleList), ListPtr);
            pBS->FreePool(CsInNotifyHandle);
        }

        pBS->FreePool(CsInKeyNotify);

        return Status;
    }

    *NotifyHandle = (EFI_HANDLE)&(CsInKeyNotify->Link);

    return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSInUnRegisterKeyNotify
//
// Description:
//  This function unregisters a notification function with given handle
//
// Input:   
//  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This - pointer to protocol instance
//  IN EFI_HANDLE NotificationHandle - handle to unregister
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - notification function unregistered successfully
//          EFI_INVALID_PARAMETER - NotificationHandle is NULL
//          EFI_DEVICE_ERROR - input device not found
//          EFI_ACCESS_DENIED - input device is busy
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSInUnRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE                        NotificationHandle
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    DLINK           *ListPtr = NULL;
    DLINK           *HandleLink = NULL;
    CON_SPLIT_IN_KEY_NOTIFY         *CsInKeyNotify = NULL;
    CON_SPLIT_IN_KEY_NOTIFY_HANDLE  *CsInNotifyHandle = NULL;

    if (StdInLocked) return EFI_ACCESS_DENIED;

    if (NotificationHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    for (ListPtr = ConInKeyNotifyList.pHead; ListPtr != NULL; ListPtr = ListPtr->pNext) {
        CsInKeyNotify = OUTTER(ListPtr, Link, CON_SPLIT_IN_KEY_NOTIFY);

        if (NotificationHandle == (EFI_HANDLE)&(CsInKeyNotify->Link)) {
            DListDelete(&ConInKeyNotifyList, ListPtr);
            break;
        }
    }

    if (ListPtr == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    // we need to loop through all the registered SimpleInEx 
    // and call each of their ReadKeyStroke function

    for (HandleLink = CsInKeyNotify->NotifyHandleList.pHead; HandleLink != NULL; 
            HandleLink = HandleLink->pNext) {
        CsInNotifyHandle = OUTTER(HandleLink, Link, CON_SPLIT_IN_KEY_NOTIFY_HANDLE);

        Status = CsInNotifyHandle->SimpleInEx->UnregisterKeyNotify(
                    CsInNotifyHandle->SimpleInEx, CsInNotifyHandle->NotifyHandle);
    
        DListDelete(&(CsInKeyNotify->NotifyHandleList), HandleLink);
        Status = pBS->FreePool(CsInNotifyHandle);
    }

    Status = pBS->FreePool(CsInKeyNotify);

    return Status;
}


#if FAST_BOOT_SUPPORT
#include <Protocol/FastBootProtocol.h>
static AMI_FAST_BOOT_PROTOCOL *AmiFbProtocol = NULL;

VOID ConnectInputDevices(
    VOID
)
{
    EFI_STATUS Status;
    static Executed = FALSE;

    if(Executed)
        return;

    if(AmiFbProtocol == NULL) {
        Status = pBS->LocateProtocol(&AmiFastBootProtocolGuid, NULL, &AmiFbProtocol);
        if(EFI_ERROR(Status)) {
            AmiFbProtocol = NULL;
            return;
        }
    }

    if(AmiFbProtocol->IsRuntime()) {
        AmiFbProtocol->ConnectInputDevices();
        Executed = TRUE;
    }
}

#else //#if FAST_BOOT_SUPPORT
VOID ConnectInputDevices(
    VOID
){return;}
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
