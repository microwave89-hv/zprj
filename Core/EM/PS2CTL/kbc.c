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
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/kbc.c 41    11/07/12 12:24a Srikantakumarp $
//
// $Revision: 41 $
//
// $Date: 11/07/12 12:24a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/kbc.c $
// 
// 41    11/07/12 12:24a Srikantakumarp
// [TAG]  		EIP99411
// [Category]  	Improvement
// [Description]  	Add port validation check in the PS2Ctrl module before
// starting the driver.
// [Files]  		kbc.c, kbc.h, mouse.c, ps2main.c, CORE_DXE.sdl, Tokens.c
// 
// 40    10/18/12 8:58a Deepthins
// [TAG]  		EIP70313
// [Category]  	Improvement
// [Description]  	Used CheckIssueLEDCmd in function LEDsOnOff instead of
// OutToKb(Kbd, 0xED)
// [Files]  		kbc.c, ps2kbd.c and kbc.h
// 
// 39    6/05/12 9:30a Lavanyap
// [TAG]  		EIP91313
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Ps2 keyboard does not work with Ps2Ctl label (INT)4.6.5.4
// [RootCause]  	Could not process PS2 keyboard data since there were more
// frequent calls to DISABLE the Keyboard.
// [Solution]  	Disabled and enabled the keyboard only before processing
// the PS2 keyboard data.
// [Files]  		kbc.c
// 
// 38    5/02/12 2:27a Deepthins
// [TAG]  		EIP63116 
// [Category]  	Improvement
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Ps2kbd.c, Mouse.c, kbc.h, kbc.c
// 
// 37    4/30/12 2:21a Rajeshms
// [TAG]  		EIP86986 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Can not detect F8 key on PS2 Keyboard while booting to EFI
// aware OS.
// [RootCause]  	Make code of F8 key (0x42) is taken by int09h and  EFI
// aware OS calls only one ReadKeyStroke() for any key catch, Now PS2
// driver will take Break Code of F8 key(0xC2) and returns EFI_NOT_READY.
// [Solution]  	Multiple Read from PS2 keyboard is implemented and read
// exits if any valid key is detected. Also, the BDA keyboard buffer is
// checked for any missed key in EFI.
// [Files]  		ps2kbd.c, kbc.c, CORE_DXE.sdl
// 
// 36    2/01/12 1:59a Deepthins
// [TAG]  		EIP63116
// [Category]  	New Feature
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Token.c, Ps2main.c, Ps2kbd.c, Mouse.c, kbc.h, kbc.c,
// CORE_DXE.sdl
// 
// 35    8/02/11 4:43a Rameshr
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
// 34    4/27/11 4:36a Lavanyap
// [TAG] - EIP49407
// [Category] - IMPROVEMENT
// [Description] - Move the Ps2 driver SDL tokens from Core Source to Core
// Bin,So that we don't need to add Core source for changing the Ps2
// driver SDL tokens.
// [Files] - Ps2Ctl.sdl, ps2kbd.c, ps2main.c, ps2ctl.h, kbc.c, mouse.c,
// hotkey.c, CORE_DXE.sdl, Tokens.c
// 
// 33    2/05/11 3:57p Artems
// Fixed bug with ellow exclamation mark in Windows, when PS2 keyboard is
// absent
// 
// 32    1/24/11 3:39p Pats
// [TAG] - EIP 18488
// [Category] - Enhancement
// [Severity] - Normal
// [Symptom] - PS2CTL: Need hooks for port swap, Keybaord mouse detect.
// [RootCause] - Support may be needed for kbc controller or SIO with
// different support from AMI KB-5.
// [Solution] - Removed token control of AutodetectKbdMousePortsPtr.
// [Files] - kbc.c
// 
// 31    1/05/11 1:02a Rameshr
// [TAG]  		EIPEIP 35306
// [Category]  	Improvement
// [Description]  	Report the Ps2 Controller and Device Error Codes.
// [Files]  		AmiStatuscodes.h, Kbc.c, Kbc.h,Ps2ctl.sdl, ps2kbd.c,
// ps2main.c ,Statuscode.h
// 
// 30    12/10/10 5:28a Rameshr
// [TAG] - EIP 47011
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - DTM IO Tests fail due to presence of PS/2 devices that are
// not ready - no PS/2 devices attached during test.
// [RootCause]- PS2 device _STA method returns that, device is present .
// [Solution] - Updated the SIO device status based on the device
// presence.
// [Files] - Kbc.c , Kbc.h, Mouse.c
// 
// 29    8/23/10 4:37a Rameshr
// Bug Fix: EIP 41862
// Symptoms: If plug PS/2 KB only, Can`t use hot key enter iSCSI OPROM
// .The CheckIssueLEDCmd routine cause PS2 keyboard not work.
// FilesModified: Kbc.c
// Details: Send Data immediately after sending LED command "ED". 
// 
// 28    8/23/10 4:23a Rameshr
// Bug Fix : EIP 40838
// Symptoms: KBC.C build failed in DetectPS2Keyboard() if
// DETECT_PS2_KEYBOARD=0 & PS2MOUSE_SUPPORT=0
// Files Modified: Efismplpp.c, Kbc.c, Kbc.h, Mouse.c PS2ctl.cif,
// Ps2ctl.sdl, Ps2Kbd.c, Ps2Mouse.c
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
// 27    7/01/10 9:03a Rameshr
// Issue:If PS/2 KBD isn't present, KBC returns oxFE when send 0xED
// command, that makes system to hang for 5 to 10 Sec.
// Solution:If command output is 0xFE (Resent) , tried for 3 times and
// gets out.
// EIP 40515
// 
// 26    8/04/09 4:32p Rameshr
// Symptom: Boot to Shell and Press Ps2 keyboard Key, Reduces the EFI
// available memory.
// RootCause: Progress_code macro allocate the memory for the Data hub and
// when ever key pressed , Disable/enable keyboard gets called. That sends
// the progress code.
// Solution: Removed the Progress code from Disable/Enable keyboard
// functions.
// 
// 25    7/01/09 5:29p Olegi
// Correction: previous file headers changes were done on the older file.
// Now changes are applied to the latest file.
// 
// 24    7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
//
// 23    4/20/09 1:53p Rameshr
// CCB byte programmed once Keyboard controller is avilable.
// EIP 19880-CCB byte not programmed
// 
// 22    4/22/08 4:31p Felixp
// Additional progress codes added
//
// 21    4/09/08 10:19a Olegi
// Changed the key attributes (modifiers and shift state) reporting.
//
// 20    10/23/07 4:05p Olegi
// Removed BDA related data storage.
//
// 19    4/16/07 6:28p Pats
// Modified to conform with coding standards. No code changes.
//
// 18    3/19/07 2:22p Pats
// Removed test for keyboard active. Issues start keyboard command on
// logic of SDL tokens only.
//
// 17    3/13/07 5:35p Pats
// Fixed problem of Lakeport not seeing setup key.
//
// 16    3/13/07 3:01p Pats
// If keyboard detection is disabled, tests for keyboard active and issues
// keyboard enable command only if it is not active. This preserves the
// input key if there is one.
//
// 15    3/13/07 11:11a Pats
// Added line to enable keyboard if keyboard detection is disabled.
// Required for some platforms.
//
// 14    3/01/07 3:20p Pats
// Fixed problem of mouse not working if keyboard detection disabled.
//
// 13    2/28/07 6:05p Pats
// Made PS2 Keyboard detection removable with SDL token, to speed up boot,
// and to keep keep Setup key (F2 or Del) from being absorbed.
//
// 12    4/12/06 9:14a Srinin
// Write to Port 80h removed.
//
// 11    1/09/06 11:38a Felixp
//
// 9     12/22/05 10:23a Srinin
// KBD Enable/Disable call optimized. Cleaned up the code.
//
// 8     10/27/05 1:04p Srinin
// When command to KBD is given, check for Timeout error added.
//
// 7     10/11/05 4:14p Srinin
// KBD and Mouse init done together. Re-entry problem fixed.
//
// 6     8/31/05 6:21p Srinin
// Comments added to "AutodetectKbdMousePorts"
//
// 5     8/31/05 4:45p Srinin
// When KBD not connected, DetectPS2Keyboard
// will returns EFI_SUCCESS in order to support hot plug.
//
// 4     8/30/05 5:23p Srinin
// PortSwap logic changed.
//
// 3     5/03/05 8:51a Olegi
// Delay correction in OutToKb function.
//
// 2     2/25/05 10:34a Olegi
// Removed duplicated code.
//
// 1     2/01/05 1:10a Felixp
//
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
//
// 1     10/28/04 10:19a Olegi
//
// 2     9/17/04 7:02p Olegi
//
// 1     8/27/04 3:18p Olegi
// Initial VSS checkin.
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: kbc.c
//
// Description: PS/2 Controller I/O support fuctions
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include "ps2ctl.h"
#include "kbc.h"
#include "genericSio.h"


//----------------------------------------------------------------------

extern  BOOLEAN MouseResetRequired;
extern  BOOLEAN DetectPs2KeyboardValue;
extern  BOOLEAN InstallKeyboardMouseAlways;
extern  UINT32  IbFreeTimeoutValue;
extern  UINT32  IbFreeMaxTimeoutValue;
BOOLEAN MouseEnableState = FALSE;
BOOLEAN KBDEnableState = TRUE;
BOOLEAN Ps2KbdDetected = FALSE;
BOOLEAN Ps2KbdMouseDetected=FALSE;
extern  BOOLEAN Ps2MouseDetected;
extern  BOOLEAN KbdIrqSupport;
extern  UINT8   gKeyboardIrqInstall;
extern  EFI_LEGACY_8259_PROTOCOL *mLegacy8259;
BOOLEAN InsidePS2DataDispatcher = FALSE;
//----------------------------------------------------------------------
        

VOID F81866ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(F81866_CONFIG_INDEX, Index);
	IoWrite8(F81866_CONFIG_DATA, Data);
}
UINT8 F81866ConfigRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(F81866_CONFIG_INDEX, Index);
	Data8 = IoRead8(F81866_CONFIG_DATA);
	return Data8;
}
VOID F81866LDNSelect(UINT8 Ldn)
{
	IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
	IoWrite8(F81866_CONFIG_DATA, Ldn);
}
VOID F81866EnterConfigMode()
{
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
}
VOID F81866ExitConfigMode()
{
	// Exit config mode
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       KBCDummyGetData
//
// Description:     Reads keyboard data port to clear it
//
// Parameters:      VOID *Context - Pointer to context
//
// Output:          UINT8 - Keyboard data port data
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
KBCDummyGetData (
    VOID *Context )
{
    UINT8   bData;
    bData = IoRead8(KBC_DATA_PORT);
    TRACEKBD((-1,"KD %X ", bData));
    return bData;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       MouseDummyGetData
//
// Description:     Reads keyboard data port to clear it
//
// Parameters:      VOID *Context - Pointer to context
//
// Output:          UINT8 - Keyboard data port data
//
// Modified:        MouseResetRequired
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8
MouseDummyGetData (
    VOID *Context )
{
    UINT8   bData;
    bData = IoRead8(KBC_DATA_PORT);
    TRACEKBD((-1,"MD %X ", bData));
    MouseResetRequired = TRUE;          // Since a orphan mouse data is
                                        // received, mouse packet will be out
                                        // of sync.
    return bData;

}


//----------------------------------------------------------------------
// The following two fuction pointers are initialized with dummy
// routines; they will be updated with the real routine pointers
// in the corresponding device drivers' start functions.
//----------------------------------------------------------------------

STATEMACHINEPROC DrivePS2KbdMachine = KBCDummyGetData;
STATEMACHINEPROC DrivePS2MouseMachine = MouseDummyGetData;

extern KEYBOARD gKbd;


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       KBCBatTest
//
// Description:     Runs Basic Assurance Test on KBC.
//
// Parameters:      None
//
// Output:          EFI_SUCCESS or EFI_DEVICE_ERROR
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS KBCBatTest()
{
    UINT16 wCounter = 0xFFFF;
  PROGRESS_CODE(DXE_KEYBOARD_SELF_TEST);
    //
    // Empty KBC before BAT
    //
    for (; wCounter; wCounter--) {
        IoRead8(KBC_DATA_PORT);
        IoDelay();
        if (!(IoRead8(KBC_CMDSTS_PORT) & (KBC_OBF | KBC_IBF))) {
            break;
        }
    }
    if (!wCounter) {
        return EFI_DEVICE_ERROR;
    }

    //
    // Perform BAT
    //
    if (Read8042(0xAA) != 0x55) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       AutodetectKbdMousePorts
//
// Description:     Auto detection of KB/MS using AMI KB-5.  This code will
//                  allow the connector swap of Keyboard and PS2 Mouse i.e.
//                  keyboard can be connected to PS2 Mouse connector and
//                  vice-versa.
//
// Parameters:      None. AMI KB-5 present in the system, keyboard controller
//                  BAT is complete.
//
// Output:          None
//
//
// Notes:            This code should be used only if the motherboard has
//                  AMI KB-5 which is also available in IO chipsets having KBC
//                  e.g. SMC932, etc.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID AutodetectKbdMousePorts()
{
    UINT8 bData, Index;

//    EFI_STATUS              Status;
{
    UINT8 Data8 ;

    F81866EnterConfigMode() ;
    F81866LDNSelect(0x05) ;
    Data8 = F81866ConfigRegisterRead(0xFE) ;
    F81866ConfigRegisterWrite(0xFE , Data8 & ~BIT4) ;
    F81866ExitConfigMode() ;
}
//    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
//    if (EFI_ERROR(Status)) {
//        return;
//    }
//    WriteKeyboardCommand(0x60);         // Lock KBD
    IoRead8(KBC_DATA_PORT);             // Discard any data

    Write8042CommandByte(0x74);         // KBD and Aux device disabled

//  Check for KBC version
    IoRead8(KBC_DATA_PORT);             // Discard any data
//    WriteKeyboardCommand(0xa1);         //
//    if (!ObFullReadTimeout(&bData, 20, TRUE) && bData == 0x35) {
        WriteKeyboardCommand(0x60);
        WriteKeyboardData(4);

        for (Index = 6; Index; Index--){  // Read max. 6 data
            if (ObFullReadTimeout(&bData, 10, TRUE)) break;
        }

        WriteKeyboardCommand(0xa7);         // Disable Mouse
        WriteKeyboardCommand(0xc8);         //  Select Primary

        WriteKeyboardData(rKeyboardID);     // Read KBD ID

        ObFullReadTimeout(&bData, 1000, TRUE);      // Read ACK

        if (bData == rKeyboardID) goto PortSwap;

//        if (bData == KB_ACK_COM) {
            ObFullReadTimeout(&bData, 100, TRUE);
// When Mouse is connected to KBD port, control goes to PortSwap here
//            if (!bData) goto PortSwap;
            if (bData != 0xAB) goto PortSwap;
            ObFullReadTimeout(&bData, 100, TRUE);
//        }
        bData = IoRead8(KBC_CMDSTS_PORT);
// When KBD is connected to the KBD port, control returns here
        if (!(bData & KBC_TIMEOUT_ERR)) return;

        WriteKeyboardCommand(0xD4);         // Secondary Port
        WriteKeyboardData(rKeyboardID);     // Read KBD ID
        ObFullReadTimeout(&bData, 1000, TRUE);
        if (bData == rKeyboardID) return;
        if (bData == KB_ACK_COM) {
// When Mouse alone is connected to Mouseport, control returns here
            if (!ObFullRead()) return;
            bData = ObFullRead();
        }
        bData = IoRead8(KBC_CMDSTS_PORT);
// When KBD alone is connected to Mouse port, no time out error and control
//  goes to portswap.
        if (bData & KBC_TIMEOUT_ERR) return;

PortSwap:
{
    UINT8 Data8 ;

    F81866EnterConfigMode() ;
    F81866LDNSelect(0x05) ;
    Data8 = F81866ConfigRegisterRead(0xFE) ;
    F81866ConfigRegisterWrite(0xFE , Data8 | BIT4) ;
    F81866ExitConfigMode() ;
}
//        WriteKeyboardCommand(0xC9);
        return;
//    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       AuxDeviceCommand
//
// Description:     This routine issues AuxDevice command, and returns the
//                  from the AUX device
//                  the connector swap of Keyboard and PS2 Mouse i.e. keyboard
//                  can be connected to PS2 Mouse connector and vice-versa.
//
// Parameters:      UINT8 bCmd - AUX device command
//
// Output:          UINT8 Data from AUX device
//
// Notes:            Only AUX commands that expect the response from AUX device
//                  can be executed using this function; otherwise the code will
//                  be stuck waiting for OBF
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 AuxDeviceCommand (
    UINT8   bCmd )
{
    EFI_STATUS              Status;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return (UINT8)Status;
    }
    IoWrite8(KBC_CMDSTS_PORT, 0xD4);

    return IssueCommand(bCmd);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       IssueCommand
//
// Description:     Helper function to read the data after executing AUX
//                  device command.
//
// Parameters:      UINT8 bCmd - AUX device command
//
// Output:          UINT8 Data from AUX device
//
// Notes:           Only AUX commands that expect the response from AUX device
//                  can be executed using this function; otherwise the code will
//                  be stuck waiting for OBF
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 IssueCommand (
    UINT8   bCmd )
{
    EFI_STATUS              Status;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return (UINT8)Status;
    }
    IoWrite8(KBC_DATA_PORT, bCmd);
    IbFree();
    for (;;)
    {
        if (IoRead8(KBC_CMDSTS_PORT) & KBC_OBF) {
            return IoRead8(KBC_DATA_PORT);
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       Read8042
//
// Description:     Sends the given command to KBC, reads and returns the
//                  acknowledgement byte returned from KBC.
//
// Parameters:      UINT8 bCmd - Command to send to KBC
//
// Output:          UINT8 Acknowledgment byte
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 Read8042 (
    UINT8   bCmd )
{

    UINT8 bData = 0xFE;
    WriteKeyboardCommand(bCmd);
    ObFullReadTimeout(&bData, 40, FALSE);
    return bData;

}



//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ReadDevice
//
// Description:     Sends the given command to KBD, reads and returns the
//                  acknowledgement byte returned from KBD.
//
// Parameters:      UINT8 bCmd - Command to send to KBC
//                  UINT8 *Data - Pointer to data buffer
//                  UINT8 Response - Response expected
//
// Output:          EFI_SUCCESS - Data == Response
//                  EFI_DEVICE_ERROR - Data != Response
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReadDevice (
    UINT8   bCmd,
    UINT8   *Data,
    UINT8   Response )
{

    WriteKeyboardData(bCmd);
    if (ObFullReadTimeout(Data, 40, FALSE)) return EFI_DEVICE_ERROR;
    if (*Data == Response) return EFI_SUCCESS;
    return EFI_DEVICE_ERROR;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       WriteKeyboardCommand
//
// Description:     Writes command to KBC.
//
// Parameters:      UINT8 bCmd - Command to send to KBC
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteKeyboardCommand (
    UINT8   bCmd )
{
    EFI_STATUS              Status;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return;
    }
    IoWrite8(KBC_CMDSTS_PORT, bCmd);
    IbFree();
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       WriteKeyboardData
//
// Description:     Writes data to KBC.
//
// Parameters:      UINT8 bCmd - Data to send to KBC
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteKeyboardData (
    UINT8   bCmd )
{
    EFI_STATUS              Status;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return;
    }
    IoWrite8(KBC_DATA_PORT, bCmd);
    IbFree();
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       Write8042CommandByte
//
// Description:     Writes CCB to KBC
//
// Parameters:      UINT8 bCCB - Command byte to send to KBC
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID Write8042CommandByte (
    UINT8   bCCB )
{
    EFI_STATUS              Status;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return;
    }
    WriteKeyboardCommand(0x60);     // CMD to send command byte
    IoWrite8(KBC_DATA_PORT, bCCB);  // Write command byte into KBC
    IbFree();                       // Wait until input buffer is free
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ObFullRead
//
// Description:     Waits for Output Buffer Full and then reads the data port
//
// Parameters:      None
//
// Output:          UINT8 KBC Data port data
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 ObFullRead()
{
    for (;;) {
        if (IoRead8(KBC_CMDSTS_PORT) & KBC_OBF) {
            return IoRead8(KBC_DATA_PORT);
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       IbFree
//
// Description:     Waits for Iutput Buffer to be empty
//
// Parameters:      None
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID IbFree()
{
    for (;;) {
        if (!(IoRead8(KBC_CMDSTS_PORT) & KBC_IBF)) {
            break;
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	    IbFreeTimeout
//
// Description:	    Waits a specified timeout for Iutput Buffer to be empty
//
// Parameters:		UINT32 TimeoutValue
//
// Return value:	EFI_STATUS (EFI_SUCCESS or EFI_TIMEOUT)
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS IbFreeTimeout( UINT32 TimeoutValue)
{
    UINTN   i;

    for (i = 0; i < TimeoutValue; i++) {
        if (!(IoRead8(KBC_CMDSTS_PORT) & KBC_IBF)) {
            return EFI_SUCCESS;
        }
        gSysTable->BootServices->Stall(1000);   // 1 ms
    }
    return EFI_TIMEOUT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       IoDelay
//
// Description:     Performs IO delay by executing IO read.
//
// Parameters:      None
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID IoDelay()
{
    IoRead8(0x61);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ObFullReadTimeout
//
// Description:     This routine checks for the data availbility in output
//                  buffer for a short period of time, if data is available
//                  within this time, it reads and returns the data from
//                  output buffer.
//
// Paremeters:      UINT8* data - Pointer to the byte to be updated
//                  UINT32 msec - Milliseconds timeout
//                  BOOLEAN ONLYOBF - Only waits for OBF if true
//
// Output:          BOOLEAN - Returns FALSE if data is successfully updated
//                  (no timeout), data is updated
//                  Returns TRUE if time-out
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN
ObFullReadTimeout (
    UINT8*      data,
    UINT32      msec,
    BOOLEAN     ONLYOBF )
{

    UINT8       bData;
    UINT32      loopcount = msec << 1;


    for (; loopcount; loopcount--) {

        bData = IoRead8(KBC_CMDSTS_PORT);

        if (ONLYOBF && (bData & KBC_OBF)) {
            *data = IoRead8(KBC_DATA_PORT);
            return FALSE;
        }

        if ((bData & (KBC_OBF|KBC_AUX_OBF)) == KBC_OBF) {
            *data = IoRead8(KBC_DATA_PORT);
            if (bData & 0x40) {
                TRACEKBD((-1, "Status Reg K : %x, %x\n", bData, *data));
                return TRUE;
            }
            else return FALSE;  // No timeout
        }

        if ((bData & (KBC_OBF|KBC_AUX_OBF)) == (KBC_OBF | KBC_AUX_OBF)){
            TRACEKBD((-1, "AUX OBF inside KBD"));
            return TRUE;
        }

        gSysTable->BootServices->Stall(500);        // 0.5msec

    }
    TRACEKBD((-1, "KBD data not available"));
    return TRUE;    // Timeout
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       OutToKb
//
// Description:     Send the given command to KDB during runtime.
//
// Parameters:      KEYBOARD* kbd - Pointer to keyboard buffer
//                  UINT8 bCmd - Command to send to keyboard
//
// Output:          EFI_SUCCESS or EFI_DEVICE_ERROR
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
OutToKb (
    KEYBOARD*   kbd,
    UINT8       bCmd )
{
    UINT8 bCounter1, bData;
    UINT32  Counter;
    EFI_STATUS              Status;

    //
    // If Keyboard irq is supported, device acknowlegement is prossed by IRQ
    // Handler. The acknowledgement data is stored in Kbd->CommandResponded
    //
    if(KbdIrqSupport && gKeyboardIrqInstall){
        if(KBDEnableState) {
            Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
            if (EFI_ERROR(Status)) {
                return Status;
            }
            IoWrite8(KBC_DATA_PORT, bCmd);
            IbFree();
            for (Counter = 1000; Counter > 0; Counter--) {
                if (kbd->CommandResponded == KB_ACK_COM){
                    kbd->CommandResponded =NULL;
                    return EFI_SUCCESS;
                }
                if (kbd->CommandResponded == KB_RSND_COM){
                    kbd->CommandResponded =NULL;
                    break;
                }
                gSysTable->BootServices->Stall(1000);
            }
            return EFI_DEVICE_ERROR;
        } 
    }


    for (bCounter1 = 3; bCounter1 > 0; bCounter1--) {
        IbFree();
        IoWrite8(KBC_DATA_PORT, bCmd);
        IbFree();

        for (Counter = 1000; Counter > 0; Counter--) {
            if (IoRead8(KBC_CMDSTS_PORT) & KBC_OBF) {
                bData = IoRead8(KBC_DATA_PORT);
                if (bData == 0xFA) {
                    return EFI_SUCCESS;
                } else if (bData == 0xFE) {
					break;
				} else {
                    if (IoRead8(KBC_CMDSTS_PORT) & KBC_TIMEOUT_ERR) break;
                    //
                    // Insert the key into the buffer
                    //
                    if (kbd) {
                        HandleKBDData(kbd, bData);
                        if (kbd->KeyIsReady) {
                            ProcessHotKey(kbd->KeyData.PS2ScanCode, kbd->KeyData.KeyState.KeyShiftState);
                            InsertKeyToBuffer(kbd, &kbd->KeyData);
                            kbd->KeyIsReady = FALSE;
                        }
                    }
                }
            }
            gSysTable->BootServices->Stall(1000);           // 1msec
        }
    }

    return EFI_DEVICE_ERROR;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       DisableKeyboard
//
// Description:     Disables KBD interface and reads the data from KBC
//                  data port.
//
// Modified:        KBDEnableState
//
// Referral(s):     KBDEnableState
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DisableKeyboard()
{
    EFI_STATUS  Status;

    if (!KBDEnableState) return;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return;
    }
    IoWrite8(KBC_CMDSTS_PORT, 0xAD);
    IbFree();
    KBDEnableState = FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       EnableKeyboard
//
// Description:     Enables KBD interface.
//
// Paremeters:      None
//
// Output:          Status
//
// Modified:        KBDEnableState
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EnableKeyboard()
{
    EFI_STATUS Status=EFI_SUCCESS;

    if (KBDEnableState) {
        return EFI_SUCCESS;
    }
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    IoWrite8(KBC_CMDSTS_PORT, 0xAE);
    Status = IbFreeTimeout(IbFreeTimeoutValue);
	KBDEnableState = TRUE;
    if (EFI_ERROR(Status)) {
        KBDEnableState = FALSE;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       DisableAuxDevice
//
// Description:     Disables Aux interface.
//
// Paremeters:      None
//
// Output:          None
//
// Modified:        MouseEnableState
//
// Referrals:       MouseEnableState
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DisableAuxDevice()
{
    EFI_STATUS  Status;
    if (!MouseEnableState) return;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return;
    }
    IoWrite8(KBC_CMDSTS_PORT, 0xA7);
    IbFree();
    MouseEnableState = FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       EnableAuxDevice
//
// Description:     Enables Aux interface.
//
// Paremeters:      None
//
// Output:          None
//
// Modified:        MouseEnableState
//
// Referrals:       MouseEnableState
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID EnableAuxDevice()
{
    EFI_STATUS  Status;
    if (MouseEnableState) return;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return;
    }
    IoWrite8(KBC_CMDSTS_PORT, 0xA8);
    IbFree();
    MouseEnableState = TRUE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       DetectPS2KeyboardAndMouse
//
// Description:     Detects the presence of Keyboard and Mouse in KBC port.
//
// Parameters:      None. Keyboard interface is disabled.
//
// Output:          Ps2KbdDetected and Ps2MouseDetected variable set accorinding 
//                  the device presence 
//
// Modified:        Ps2KbdDetected, Ps2MouseDetected
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS DetectPS2KeyboardAndMouse()
{
    UINT16      wCount;
    UINT8       bData;
    BOOLEAN bAck = FALSE;

    if(Ps2KbdMouseDetected) {
        //
        // Ps2Keyboard and Mouse Detected already
        //
        return EFI_SUCCESS;
    }
            
    Ps2KbdMouseDetected=TRUE;

    DetectPs2Mouse();


    if ( DetectPs2KeyboardValue ) {

        PROGRESS_CODE(DXE_KEYBOARD_DETECT);
        Write8042CommandByte (0x6d);
        KBCGetData();                                       // Dummy read

        for (wCount = 0; wCount < 3; wCount++) {
            // Disable Scanning
            if (!ReadDevice(KBD_DISABLE_SCANNING, &bData, KB_ACK_COM)) break;
            if (IoRead8(KBC_CMDSTS_PORT) & 0x40) {              // Time out error
                gSysTable->BootServices->Stall(6000);           // 6 msec
                // After power-up some junk data comes from KBD. If not eaten
                // other command will fail.
                KBCGetData();
            }
        }

        DisableKeyboard();
        KBCGetData();   

        //
        // 3 times retry on keyboard reset
        //
        for (wCount = 0; wCount < 3; wCount++) {
            if (!ReadDevice(KBD_RESET, &bData, KB_ACK_COM)) {   // ACK received
                TRACEKBD((-1,"KBD Reset Response %X ", bData));
                bAck = TRUE;
                break;
            } else {        
                KBCGetData();                       // Dummy read
            }
        }

        if (bAck) {                             //If not not Keyboard
            if (ObFullRead() == 0xAA) {     // Reset successful
                Ps2KbdDetected=TRUE;
            } else if (Read8042(0xAB)) {       // On Success returns 0
                //
                // 0x01 if Clock line stuck low, 0x02 if clock line stuck high, 
                // 0x03 if data line stuck low, and 0x04 if data line stuck high       
                //
                Ps2KbdDetected=FALSE;
            }
	    }									

        //
        // Check for lock key
        //
        if (!(IoRead8(KBC_CMDSTS_PORT) & 0x10)) {
            //
            // Keyboard is locked, we can report it here
            //
            Ps2KbdDetected=FALSE;
        }
    } else { 
        Ps2KbdDetected = TRUE;
        KBDEnableState = TRUE;
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       UpdateSioVariableForKeyboardMouse
//
// Description:     Update the SIO variable in the ACPI name space depend on the 
//                  Ps2keyboard and Mouse Present state.
//
// Parameters:      None
//
// Output:          None
//                  
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateSioVariableForKeyboardMouse(
    EFI_EVENT   Event,
    VOID        *Context
)
{
    static EFI_GUID     SioDevStatusVarGuid = SIO_DEV_STATUS_VAR_GUID;
    UINTN               SioDevStatusVarSize = sizeof(SIO_DEV_STATUS);
    SIO_DEV_STATUS      SioDevStatus;
    UINT32              SioDevStatusVarAttributes = 0;
    EFI_STATUS Status;

    //
    // Get the SIO variable.
    //
    Status = pRS->GetVariable( SIO_DEV_STATUS_VAR_NAME, 
                                &SioDevStatusVarGuid, 
                                &SioDevStatusVarAttributes,
                                &SioDevStatusVarSize, 
                                &SioDevStatus.DEV_STATUS);

    //
    // If variable not found return without updating it.
    //
    if(EFI_ERROR(Status)) {
        SioDevStatus.DEV_STATUS = 0;
		SioDevStatusVarAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS;
        SioDevStatus.Res3 = 1;   // To indicate that PS2 state vas updated
    }

    //
    // Set the flag based on the Ps2 keyboard presence state
    //
    if(Ps2KbdDetected) {
        SioDevStatus.Key60_64 = 1;
    } else {
        SioDevStatus.Key60_64 = 0;
    }


    //
    // Set the Mouse flag based on the Mouse Presence state.
    //
    if(Ps2MouseDetected) {
        SioDevStatus.Ps2Mouse = 1;
    } else {
        SioDevStatus.Ps2Mouse = 0;
    }

    //
    // Set the SIO variable.
    //
    Status = pRS->SetVariable(  SIO_DEV_STATUS_VAR_NAME, 
                                &SioDevStatusVarGuid, 
                                SioDevStatusVarAttributes,
                                SioDevStatusVarSize, 
                                &SioDevStatus);
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       DetectPS2Keyboard
//
// Description:     Detects the presence of Keyboard in KBC port.
//
// Parameters:      None
//
// Output:          EFI_SUCCESS if mouse is detected
//                  EFI_NOT_FOUND if mouse is not detected
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  DetectPS2Keyboard( )
{
    if ( InstallKeyboardMouseAlways ) {
        return EFI_SUCCESS;
    } else {
        return Ps2KbdDetected ? EFI_SUCCESS : EFI_NOT_FOUND;
    }
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       PS2DataDispatcher
//
// Description:     This fuction checks whether data is available in the PS2
//                  controller output buffer. If so, it gives control to the
//                  corresponding state machine executor.
//
// Parameters:      VOID *Context - Pointer to the context for this function
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PS2DataDispatcher (
    VOID    *Context )
{
    UINT8 data;
    KEYBOARD *kbd = &gKbd;
    UINT8  bIndicators;
	
    bIndicators = kbd->KeyData.KeyState.KeyToggleState & 7;    // SCRL/NUM/CPSL 
    if(KbdIrqSupport){
        
        //
        // if keyboard irq supported check status of SCRL/NUM/CPSL keys
        // and send the command to Keyboard to update the LED status
        // 
        UINT8 bIndicators = kbd->KeyData.KeyState.KeyToggleState & 7; 
        if (bIndicators != kbd->Indicators && kbd->LEDCommandState == 0){
            LEDsOnOff(kbd);
        }
        return;
    }

    if (InsidePS2DataDispatcher) return;
    InsidePS2DataDispatcher = TRUE;

    for(data = IoRead8(KBC_CMDSTS_PORT); data & KBC_OBF; data = IoRead8(KBC_CMDSTS_PORT)) {
        if (data & KBC_AUX_OBF) {
            DrivePS2MouseMachine(Context);
        }
        else {
            //
            // Removed the DisableKeyboard() as to read multiple data from port60h,
            // If any valid key is received we break out of the loop. 
            //
            DrivePS2KbdMachine(Context);
            if (CheckKeyinBuffer(kbd) ) {
                break;
            }
        }
    }

    //
    // Check LED state before issuing ED command
    //
    if (bIndicators != kbd->Indicators && kbd->LEDCommandState == 0) {
	    //
		// Disable the keyboard before issuing ED command 
		//
        DisableKeyboard();
        CheckIssueLEDCmd(kbd);
    }

    //
    //Process the led command and data
    //
    ProcessLEDCommandData(kbd);
    EnableKeyboard();
    InsidePS2DataDispatcher = FALSE;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       CheckIssueLEDCmd
//
// Description:     This function check if KBD LED command ED needs to be
//                  issued.
//                  If 'yes', sends ED command. No data is read.
//
// Parameters:      KEYBOARD *kbd - Pointer to keyboard buffer
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CheckIssueLEDCmd (
    KEYBOARD    *Kbd )
{

    UINT8 bIndicators = Kbd->KeyData.KeyState.KeyToggleState & 7;    // SCRL/NUM/CPSL

    if (bIndicators != Kbd->Indicators && Kbd->LEDCommandState == 0) {
        //
        // Don't issue LED command when data is pending
        //
        if (IoRead8(KBC_CMDSTS_PORT) & KBC_OBF) return;
        Kbd->LEDCommandState = ED_COMMAND_ISSUED;
        WriteKeyboardData(0xED);
    }

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ProcessKBDResponse
//
// Description:     If 0xFA is received as data, check for any pending ACK
//                  and take necessary action.
//
// Parameters:      KEYBOARD* kbd - Pointer to keyboard buffer
//                  UINT8 bData - Data received from keyboard
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ProcessKBDResponse (
    KEYBOARD    *Kbd,
    UINT8       Data )
{

    UINT8 bIndicators = Kbd->KeyData.KeyState.KeyToggleState & 7;    // SCRL/NUM/CPSL

    switch (Data) {
        case 0xFA:
            if (Kbd->LEDCommandState == ED_COMMAND_ISSUED) {
                Kbd->LEDCommandState = ED_DATA_ISSUED;
                Kbd->Indicators = bIndicators;
                WriteKeyboardData(bIndicators);
                break;
            }

            if (Kbd->LEDCommandState == ED_DATA_ISSUED) {
                Kbd->LEDCommandState = 0;
                break;
            }


        case 0xFE:
            if (Kbd->LEDCommandState == ED_COMMAND_ISSUED || Kbd->LEDCommandState == ED_DATA_ISSUED) {
//                  Error occured. Clear out the current indicator bits.
//                  Modifiers will have the correct bits that needs to be set.
//                  Next Call to CheckIssueLEDCmd will detect the mismatch
//                  and start the LED sequence.
                    WriteKeyboardData(0xF4);
                    Kbd->LEDCommandState = 0;
                    bIndicators = Kbd->KeyData.KeyState.KeyToggleState & 7;
                    Kbd->KeyData.KeyState.KeyToggleState &=
                        ~(SCROLL_LOCK_ACTIVE | NUM_LOCK_ACTIVE | CAPS_LOCK_ACTIVE);
                    Kbd->Indicators &= 0xf0;
                    break;
            }

        case 0xFF:
                Kbd->LEDCommandState = 0;
                break;
        default:  break;
    }

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       KBCGetData
//
// Description:     Reads and returns byte of data from KBC data port. Also
//                  used as dummy KBC data process routine.
//
// Parameters:      VOID *Context - Pointer to the context of this function
//
// Output:          UINT8 Data read from KBC Data port.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 KBCGetData ()
{
    UINT8   Data;
    Data = IoRead8(KBC_DATA_PORT);

    return Data;
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
