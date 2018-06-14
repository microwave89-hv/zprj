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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/ConSplitter/ConSplit.c 7     8/28/13 10:44p Thomaschen $
//
// $Revision: 7 $
//
// $Date: 8/28/13 10:44p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/ConSplitter/ConSplit.c $
// 
// 7     8/28/13 10:44p Thomaschen
// Fixed for EIP133747.
// 
// 6     8/01/13 2:32a Thomaschen
// Add for EIP109384.
// [Files]  ConSplit.c, ConSplit.h, In.c, CsmSimpleIn.c.
// 
// 5     6/26/13 3:09a Thomaschen
// Remove EIP109384.
// 
// 3     6/04/13 1:55a Thomaschen
// Fixed for EIP118202.
// 
// 2     11/15/12 9:53p Wesleychen
// Update to rev.55 for EIP103887.
// 
// 55    10/29/12 3:44p Artems
// [TAG]  		EIP103887
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Upgrade Serial Redirection to 4.6.3_Terminal_51 with Core
// 4654, system will hang 0x06.
// [RootCause]  	Uninitialized variable was used
// [Solution]  	Initialize DeviceModeNumber variable before using
// [Files]  		ConSplit.c
// 
// 54    10/25/12 2:31a Deepthins
// [TAG]  		EIP99475
// [Category]  	Improvement
// [Description]  	Multi language module Support in the console splitter
// [Files]  		ConSplit.c, ConSplit.h , In.c and AmiKeycode.h
// 
// 53    10/08/12 4:28p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	system boots in wrong text mode
// [RootCause]  	Incorrect restore of graphics mode after legacy OPROM
// execution
// [Solution]  	Added code for correct restoration of system state after
// execution of Consplit.stop function
// [Files]  		Consplit.c
// 
// 52    8/13/12 3:39p Artems
// [TAG]  		EIP95607
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Execute nsh script and redirect output to file, then exit
// from shell, setup screen will crash
// [RootCause]  	Console splitter maintains global pool of supportedmodes.
// It's getting adjusted every time new SimpleTextOut (STO) is installed
// If new STO doesn't support particular mode it is getting marked as
// unsupported in global pool
// However once this STO is uninstalled global pool isn't updated, so mode
// is still marked as unsupported,
// though system can support it
// [Solution]  	Do not connect simpleTextOut driver if it doesn'tsupport
// mode splitter is in
// [Files]  		Consplit.c
// 
// 51    8/02/12 12:13p Artems
// [TAG]  		EIP95607
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Execute nsh script and redirect output to file, then exit
// from shell, setup screen will crash
// [RootCause]  	Console splitter maintains global pool of supported
// modes. 
// It's getting adjusted every time new SimpleTextOut (STO) is installed
// If new STO doesn't support particular mode it is getting marked as
// unsupported in global pool
// However once this STO is uninstalled global pool isn't updated, so mode
// is still marked as unsupported,
// though system can support it
// [Solution]  	Added reinitilization of global pool of supported modes on
// STO uninstall event
// [Files]  		Consplit.h Consplit.c
// 
// 50    7/06/12 11:28a Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Support for monitor native resolution
// [Files]  		GC.c, Consplit.c, Out.c, Core_Dxe.sdl
// 
// 49    12/15/11 12:15p Felixp
// [TAG]  		EIP73410
// [Category]  	Improvement
// [Description]  	InstallSimplePointerDevice function is updated to
// initialize 
// LeftButton and RightButton fields of the 
// EFI_SIMPLE_POINTER_MODE structure exposed by 
// the splitter based on capabilities of the available mouse devices.
// 
// 48    8/12/11 12:19p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 
// 47    7/11/11 10:10a Felixp
// Improvement (EIP 64049):
// REPORT_NO_CON_OUT_ERROR and REPORT_NO_CON_IN_ERROR SDL tokens are added
// to enable/disable reporting of the console errors.
// 
// 46    5/13/11 3:37p Felixp
// Minor improvement in CSStop: the screen is now saved after closing the
// protocol
// 
// 45    5/05/11 3:52p Artems
// Added multi-language keyboard support
// 
// 44    2/25/11 12:33p Artems
// EIP 53767 - disable reporting keyboard absence on fast boot path
// 
// 43    11/15/10 4:59p Felixp
// 
// 41    9/24/10 3:38p Felixp
// Enhancement(EIP 43535):
// The pST->ConOut pointer used to be initialized once all ConOut 
// device are connected. The Console Splitter driver is updated 
// to initialize ConOut-related fields of the systems table 
// early (in the entry point) to workaround bugs in some of the 
// UEFI OpROM drivers that are using pST->ConOut without NULL checking.
// 
// 40    9/24/10 7:39a Felixp
// Additional checks for DXE_NO_CON_OUT and DXE_NO_CON_IN errors are
// added.
// The errors are now reported when no console devices with device path
// available.
// 
// 39    8/10/10 2:31p Vyacheslava
// Simple Pointer Protocol bug fixes. (EIP#41832)
// 
// 38    6/23/10 3:02p Felixp
// SimplePointer splitter support is added.
// 
// 37    2/19/10 9:58a Artems
// Merged previous changes
// 
// 36    2/12/10 6:13p Artems
// EIP 34632 Added modification of MasterMode.MaxMode value if one of 
// children does not support Mode 2 or higher
// 
// 34    8/28/09 9:07a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 33    7/08/09 4:42p Artems
// Added missing functions headers
// 
// 32    7/07/09 3:35p Artems
// Added functions headers according to code standard
// 
// 31    6/16/09 5:50p Artems
// EIP 21415 Fixed error with CursorVisible variable
// 
// 30    1/16/09 5:27p Felixp
// Bug fix.
// Headless systems hanging(EIP 18165).
// Symptoms: Systems with no console output devices were hanging towards 
// the end of the boot process (prior to OS handoff). 
// Details: Some of the global variables used by console splitter
// implementation 
// of TxtOut were only initialized once first physical console output
// device is detected, 
// which was never happenning of a headless system.
// The conosle splitter is updated to properly initialize the globals 
// when no actual console output devices are available. 
// UpdateSystemTableConOut function is updated.
// 
// 29    1/05/09 3:11p Felixp
// Minor update of UpdateSystemTableConOut. 
// Callback event is closed at the end of the function
// (system table needs to be populated only once).
// 
// 28    10/09/08 2:50p Felixp
// StdErr and StandardErrorHandle initialization added
// 
// 27    1/31/08 12:00p Olegi
// Numlock bootup state made setup driven.
// 
// 26    10/23/07 4:07p Olegi
// Added a call to syncronize LEDs of ConIn devices during Start.
// 
// 25    10/23/07 10:12a Felixp
// Bug fix: after boot to Shell big part of the small AMI logo stayed on
// the screen.
// It was only happenning when two conditions were met: serial redirection
// was turned off and plug in card with the option ROM was connected to
// the system.
// 
// 24    9/17/07 4:04p Olegi
// Added support for AMI_EFIKEYCODE_PROTOCOL and
// EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.
// 
// 23    9/05/07 5:43p Felixp
// Report errors when no ConIn and ConOut devices are not available.
// 
// 22    9/05/07 11:13a Felixp
// SimpleTextInEx support removed. It causes problems. Support will add
// again after Core labeling.
// 
// 20    1/05/07 5:32p Artems
// 
// 19    12/29/06 3:01p Felixp
// 1. Support for GraphicsOutput protocol added
// 2. Support for more then one text mode added
// 
// 18    9/27/06 7:42p Felixp
// SetMode funciton of the ConsoleControl protocol is updated to restore
// default UGA mode when switching from grphics to text.
// 
// 17    9/13/06 6:16p Felixp
// pST->ConOut initialization logic changed: it is now initialized 
// immediately after the first ConOut device has been connected
// 
// 16    3/13/06 2:37a Felixp
// 
// 15    12/12/05 8:36p Felixp
// RestoreTheScreen update: Restore Cursor Status
// 
// 14    12/12/05 9:32a Felixp
// Support for synchronization of console devices 
// (now screen is restored after legacy OpROM execution).
// 
// 13    11/07/05 10:37a Felixp
// LockStdIn function of ConsoleControl protocol implemented
// 
// 12    7/15/05 7:17p Felixp
// CONSOLE_DEVICES_STARTED_PROTOCOL_GUID added.
// BDS uses it to notify Splitter that Console Devices have been started.
// Once Splitter receives notification, it will install ConIn and ConOut
// in System Table
// 
// 11    5/27/05 12:16p Felixp
// 
// 10    5/27/05 12:47a Felixp
// Support for ConsoleControl protocol added
// 
// 9     4/08/05 7:40a Felixp
// fix: from now on when new device added, others not cleared
// 
// 8     3/04/05 9:17a Mandal
// 
// 7     2/24/05 5:30p Felixp
// 1. Coded added to Start/Stop functions to open processed handles in
// BY_CHILD_CONTROLLER mode
// 2. GetControllerName implemented
// 
// 6     2/11/05 6:11p Felixp
// Logic to update ConDev variables
// 
// 5     2/02/05 4:20p Felixp
// 
// 3     2/02/05 2:32p Felixp
// Splitter opens TxtIn and TxtOut in BY_DRIVER mode (used to be
// GET_PROTOCOL)
// 
// 2     2/01/05 1:17a Felixp
// 
// 1     1/28/05 1:16p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     1/07/05 11:57a Felixp
// 
// 3     1/04/05 5:15p Robert
// Changed component name to be more consistent with the other drivers
// that have been developed
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
// Name:        ConSplit.c
//
// Description: Console Splitter driver that creates a cetralized input and 
//              output console so that the correct data is going to and coming
//              from the correct devices
//
//<AMI_FHDR_END>
//**********************************************************************

//----------------------------------------------------------------------------

#include "ConSplit.h"
#include <Protocol/DevicePath.h>
#include <Protocol/ConsoleControl.h>
#include <Protocol/HiiDataBase.h>
#include <Setup.h>
#include <Dxe.h>
#include <Hob.h>
#include <Token.h>

//----------------------------------------------------------------------------

EFI_HANDLE		ConSplitHandle = NULL;

DLIST 		ConInList;
DLIST		ConOutList;
DLIST		ConPointerList;
DLIST		ConInKeyNotifyList;

EFI_KEY_TOGGLE_STATE mCSToggleState = TOGGLE_STATE_VALID;
BOOLEAN NumLockSet = FALSE;
static BOOLEAN InitModesTableCalled = FALSE;

static EFI_GUID	gSimpleTextOutGuid  = EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID;
static EFI_GUID	gSimpleInGuid       = EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID;
static EFI_GUID	gSimpleInExGuid     = EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID;
static EFI_GUID gAmiEfiKeycodeGuid  = AMI_EFIKEYCODE_PROTOCOL_GUID;
static EFI_GUID	gSimplePointerGuid  = EFI_SIMPLE_POINTER_PROTOCOL_GUID;
static EFI_GUID	gEfiDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;
static EFI_GUID gAmiMultiLangSupportGuid = AMI_MULTI_LANG_SUPPORT_PROTOCOL_GUID;

extern SIMPLE_TEXT_OUTPUT_MODE	MasterMode;


EFI_STATUS InstallConOutDevice(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *SimpleOut, 
    IN EFI_HANDLE                      Handle
    );

EFI_STATUS InstallConInDevice(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL    *SimpleIn, 
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *SimpleInEx, 
    IN AMI_EFIKEYCODE_PROTOCOL           *KeycodeIn,
    IN EFI_HANDLE                        Handle
    );

EFI_STATUS InstallSimplePointerDevice(
    IN EFI_SIMPLE_POINTER_PROTOCOL       *SimplePointer, 
    IN EFI_HANDLE                        Handle
    );

EFI_STATUS ConOutHandleCheck(
    IN EFI_HANDLE Handle
    );

EFI_STATUS ConInHandleCheck(
    IN EFI_HANDLE Handle
    );

VOID CSSetKbLayoutNotifyFn(
    IN EFI_EVENT Event, 
    IN VOID *Context
);

EFI_HII_DATABASE_PROTOCOL *HiiDatabase      = NULL;
EFI_HII_KEYBOARD_LAYOUT *gKeyDescriptorList = NULL;
UINT16 KeyDescriptorListSize                = 0;
static EFI_GUID SetKeyboardLayoutEventGuid = EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID;

EFI_STATUS ConSimplePointerHandleCheck( IN EFI_HANDLE Handle );

EFI_DRIVER_BINDING_PROTOCOL gConSplitterDriverBindingProtocol = {
	CSSupported,
	CSStart,
	CSStop,
	0x10,
	NULL,
	NULL
	};
AMI_MULTI_LANG_SUPPORT_PROTOCOL     gMultiLangSupportProtocol = {
    KeyboardLayoutMap
};

#ifdef EFI_DEBUG
#ifndef EFI_COMPONENT_NAME2_PROTOCOL_GUID //old Core
#ifndef LANGUAGE_CODE_ENGLISH
#define LANGUAGE_CODE_ENGLISH "eng"
#endif
static BOOLEAN LanguageCodesEqual(
    CONST CHAR8* LangCode1, CONST CHAR8* LangCode2
){
    return    LangCode1[0]==LangCode2[0] 
           && LangCode1[1]==LangCode2[1]
           && LangCode1[2]==LangCode2[2];
}
static EFI_GUID gEfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
#endif
static CHAR16 *gDriverName=L"AMI Console Splitter Driver";
static CHAR16 *gControllerName=L"AMI Console Splitter";

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:  ComponentNameGetControllerName
//
// Description: 
//  EFI_COMPONENT_NAME_PROTOCOL GetControllerName function
//
// Input:       
//  IN EFI_COMPONENT_NAME_PROTOCOL* This - pointer to protocol instance
//  IN EFI_HANDLE Controller - controller handle
//  IN EFI_HANDLE ChildHandle - child handle
//  IN CHAR8* Language - pointer to language description
//  OUT CHAR16** ControllerName - pointer to store pointer to controller name
//
// Output:      
//      EFI_STATUS
//          EFI_SUCCESS - controller name returned
//          EFI_INVALID_PARAMETER - language undefined
//          EFI_UNSUPPORTED - given language not supported
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static EFI_STATUS ComponentNameGetControllerName (
	IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
	IN  EFI_HANDLE                   ControllerHandle,
 	IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
  	IN  CHAR8                        *Language,
  	OUT CHAR16                       **ControllerName 
)
{
	//Supports only English
	if(!Language || !ControllerName) 
        return EFI_INVALID_PARAMETER;

	if (   ChildHandle!=ConSplitHandle 
        || !LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH)
    ) return EFI_UNSUPPORTED;

	*ControllerName=gControllerName;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:   ComponentNameGetDriverName
//
// Description: 
//  EFI_COMPONENT_NAME_PROTOCOL GetDriverName function
//
// Input:       
//  IN EFI_COMPONENT_NAME_PROTOCOL* This - pointer to protocol instance
//  IN CHAR8* Language - pointer to language description
//  OUT CHAR16** DriverName - pointer to store pointer to driver name
//
// Output:      
//  EFI_STATUS
//      EFI_SUCCESS - driver name returned
//      EFI_INVALID_PARAMETER - language undefined
//      EFI_UNSUPPORTED - given language not supported
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

static EFI_STATUS ComponentNameGetDriverName(
    IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
	IN  CHAR8                        *Language,
	OUT CHAR16                       **DriverName
)
{
	//Supports only English 
	if(!Language || !DriverName) 
        return EFI_INVALID_PARAMETER;

	if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH)) 
        return EFI_UNSUPPORTED;
	else 
        *DriverName=gDriverName;
	
	return EFI_SUCCESS;
}

//Component Name Protocol
static EFI_COMPONENT_NAME2_PROTOCOL gComponentName = {
  ComponentNameGetDriverName,
  ComponentNameGetControllerName,
  LANGUAGE_CODE_ENGLISH
};
#endif

EFI_CONSOLE_CONTROL_SCREEN_MODE ScreenMode = EfiConsoleControlScreenText;
BOOLEAN CursorVisible = TRUE;
BOOLEAN StdInLocked   = FALSE;

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: GetMode
//
// Description:
//  This function returns current console mode
//
// Input:   
//  IN EFI_CONSOLE_CONTROL_PROTOCOL *This - pointer to console protocol
//  OUT EFI_CONSOLE_CONTROL_SCREEN_MODE *Mode - placeholder for mode to return
//  OUT OPTIONAL BOOLEAN *UgaExists - if not NULL on return will have current UGA present state
//  OUT OPTIONAL BOOLEAN *StdInLocked - if not NULL on return will have value of STD_IN_LOCKED state
//                                                              
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - function returns correct values
// 
// Modified:
//
// Referrals:
//      ScreenMode
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS GetMode(
	IN  EFI_CONSOLE_CONTROL_PROTOCOL    *This,
	OUT EFI_CONSOLE_CONTROL_SCREEN_MODE *Mode,
	OUT BOOLEAN                         *UgaExists OPTIONAL, 
	OUT BOOLEAN                         *StdInLocked OPTIONAL
)
{
	if (Mode) *Mode = ScreenMode;
	if (UgaExists) *UgaExists = TRUE;
	if (StdInLocked) *StdInLocked = FALSE;
	return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SetMode
//
// Description:
//  This function sets current console mode
//
// Input:   
//  IN  EFI_CONSOLE_CONTROL_PROTOCOL *This - pointer to console protocol
//  IN  EFI_CONSOLE_CONTROL_SCREEN_MODE Mode - mode to set
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - mode set successfully
//          EFI_INVALID_PARAMETER - incorrect mode given
// 
// Modified:
//      ScreenMode
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS SetMode(
	IN EFI_CONSOLE_CONTROL_PROTOCOL    *This,
	IN EFI_CONSOLE_CONTROL_SCREEN_MODE Mode
)
{
	if (ScreenMode != Mode)
	{
		ScreenMode = Mode;
		if (ScreenMode == EfiConsoleControlScreenText)
		{
			//Restore UGA mode when switching from graphics to text
			DLINK			*ListPtr = ConOutList.pHead;
			CON_SPLIT_OUT 	*SimpleOut;
			while ( ListPtr != NULL)
			{
				SimpleOut = OUTTER(ListPtr, Link, CON_SPLIT_OUT);
				RestoreUgaMode(SimpleOut->Handle);
				ListPtr = ListPtr->pNext;
			}

			if (CursorVisible)
				mCSOutProtocol.EnableCursor(&mCSOutProtocol,TRUE);
		}
		else if (ScreenMode == EfiConsoleControlScreenGraphics)
		{
			DLINK			*ListPtr = ConOutList.pHead;
			CON_SPLIT_OUT 	*SimpleOut;
			CursorVisible = MasterMode.CursorVisible;
			if (CursorVisible)
				mCSOutProtocol.EnableCursor(&mCSOutProtocol,FALSE);
			//Save UGA mode when switching from text to graphics
			while ( ListPtr != NULL)
			{
				SimpleOut = OUTTER(ListPtr, Link, CON_SPLIT_OUT);
				SaveUgaMode(SimpleOut->Handle);
				ListPtr = ListPtr->pNext;
			}

		}
		else return EFI_INVALID_PARAMETER;
	}
	return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: LockStdIn
//
// Description:
//  This function toggles STD_IN_LOCKED state
//
// Input:   
//  IN  EFI_CONSOLE_CONTROL_PROTOCOL *This - pointer to console protocol
//  IN  CHAR16 *Password - pointer to password string
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - function executed successfully
// 
// Modified:
//      StdInLocked
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS LockStdIn(
	IN EFI_CONSOLE_CONTROL_PROTOCOL *This, 
    IN CHAR16 *Password
)
{
	//TODO: add support for the password
	StdInLocked = !StdInLocked;
	return EFI_SUCCESS;
};

EFI_GUID gConsoleControlProtocolGuid = EFI_CONSOLE_CONTROL_PROTOCOL_GUID;

EFI_CONSOLE_CONTROL_PROTOCOL gConsoleControlProtocol = { 
	GetMode, 
    SetMode, 
    LockStdIn
};

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: UpdateSystemTableConOut
//
// Description:
//  This function updates system table ConOut pointer
//
// Input:   
//  IN EFI_EVENT Event - signalled event
//  IN VOID *Context - pointer to event context
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

VOID UpdateSystemTableConOut()
{
	UINT32		CRC32 = 0;

    if( ConOutList.Size==0 ){
        //Initialize all the global variables used by 
        //splitter implementation of TxtOut.
        //When physical ConOut devices are available, the initialization is performed
        //within InitModesTable routine.
        VERIFY_EFI_ERROR(ResizeSplitterBuffer(0));
        VERIFY_EFI_ERROR(pBS->AllocatePool(EfiBootServicesData, sizeof(SUPPORT_RES), &SupportedModes));
        SupportedModes[0].Rows =  25;
	    SupportedModes[0].Columns = 80;
	    SupportedModes[0].AllDevices = TRUE;
    }

	pST->ConOut = &mCSOutProtocol;
	pST->ConsoleOutHandle = ConSplitHandle;
    // We want to initialize ConOut-related fields of the systems table early
    // to workaround bugs in some of the UEFI OpROM drivers
    // that are using pST->ConOut without NULL checking.
    // We are not installing the instance of SimpleTextOut on ConSplitHandle though,
    // because it confuses the logic of TSE notification callbacks.
    // The protocol is installed once all ConOut devices are connected
    // in ReportNoConOutError.
    if (pST->StdErr==NULL){
        pST->StdErr = pST->ConOut;
        pST->StandardErrorHandle  = pST->ConsoleOutHandle;
    }

	// Now calculate the CRC32 value
	pST->Hdr.CRC32 = 0;
	pST->BootServices->CalculateCrc32(pST, sizeof(EFI_SYSTEM_TABLE), &CRC32);
	pST->Hdr.CRC32 = CRC32;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ReportNoConOutError
//
// Description:
//  This function checks if physical ConOut devices are available.
//  If not, DXE_NO_CON_OUT error is reported.
//
// Input:   
//  IN EFI_EVENT Event - signalled event
//  IN VOID *Context - pointer to event context
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

VOID ReportNoConOutError(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
#if REPORT_NO_CON_OUT_ERROR
    DLINK       *Link;
    EFI_STATUS Status;

    //Report error if no ConOut devices available or
    // all console devices are fake devices (without device path).
    for(Link = ConOutList.pHead; Link!=NULL; Link=Link->pNext){
        CON_SPLIT_OUT *SimpleOut = OUTTER(Link, Link, CON_SPLIT_OUT);
        VOID *Dp;

        Status = pBS->HandleProtocol(
            SimpleOut->Handle, &gEfiDevicePathProtocolGuid, &Dp
        );
        if (!EFI_ERROR(Status)) break; // Got one device path
    }
    //Report error if no ConOut devices with device path exists
    if( ConOutList.Size==0 || EFI_ERROR(Status) )
        ERROR_CODE(DXE_NO_CON_OUT, EFI_ERROR_MAJOR);
#endif
	pBS->InstallMultipleProtocolInterfaces (
		&ConSplitHandle, &gSimpleTextOutGuid, &mCSOutProtocol,
		&gConsoleControlProtocolGuid, &gConsoleControlProtocol,
		NULL
	);
    pBS->CloseEvent(Event);
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: UpdateSystemTableConIn
//
// Description:
//  This function updates system table ConIn pointer
//
// Input:   
//  IN EFI_EVENT Event - signalled event
//  IN VOID *Context - pointer to event context
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

VOID UpdateSystemTableConIn(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
	UINT32		CRC32 = 0;

#if REPORT_NO_CON_IN_ERROR
    DLINK       *Link;
    EFI_STATUS Status;

    EFI_HOB_HANDOFF_INFO_TABLE *pHit;
    static EFI_GUID guidHob = HOB_LIST_GUID;

    //Report error if no ConIn devices available or
    // all console devices are fake devices (without device path).
    for(Link = ConInList.pHead; Link!=NULL; Link=Link->pNext){
        CON_SPLIT_IN *SimpleIn = OUTTER(Link, Link, CON_SPLIT_IN);
        VOID *Dp;

        Status = pBS->HandleProtocol(
            SimpleIn->Handle, &gEfiDevicePathProtocolGuid, &Dp
        );
        if (!EFI_ERROR(Status)) break; // Got one device path
    }

	pHit = GetEfiConfigurationTable(pST, &guidHob);
    //Report error if no ConIn devices with device path exists
    if( (ConInList.Size == 0 || EFI_ERROR(Status)) && (pHit->BootMode == BOOT_WITH_FULL_CONFIGURATION))
        ERROR_CODE(DXE_NO_CON_IN, EFI_ERROR_MAJOR);
#endif
	pST->ConIn = &mCSSimpleInProtocol;

	pBS->InstallMultipleProtocolInterfaces (
		&ConSplitHandle,
        &gSimpleInGuid, &mCSSimpleInProtocol,
        &gSimpleInExGuid, &mCSSimpleInExProtocol,
        &gAmiEfiKeycodeGuid, &mCSKeycodeInProtocol,
        &gEfiSimplePointerProtocolGuid, &mCSSimplePointerProtocol, 
		NULL
	);
	
	pST->ConsoleInHandle = ConSplitHandle;

	// Now calculate the CRC32 value
	pST->Hdr.CRC32 = 0;
	pST->BootServices->CalculateCrc32(pST, sizeof(EFI_SYSTEM_TABLE), &CRC32);
	pST->Hdr.CRC32 = CRC32;

	pBS->CloseEvent(Event);
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSEntryPoint
//
// Description:
//  This function is Console splitter driver entry point
//
// Input:   
//  IN EFI_HANDLE ImageHandle - image handle of Console splitter driver
//  IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - driver installed successfully
//          EFI_ERROR - error occured during execution
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSEntryPoint(
	IN EFI_HANDLE       ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
	static EFI_GUID guidConInStarted = CONSOLE_IN_DEVICES_STARTED_PROTOCOL_GUID;
	static EFI_GUID guidConOutStarted = CONSOLE_OUT_DEVICES_STARTED_PROTOCOL_GUID;
    // {8FF925F1-8624-4d38-9ED2-F8F5AA94F84A}
    static EFI_GUID gDummyProtocolGuid = 
        { 0x8ff925f1, 0x8624, 0x4d38, { 0x9e, 0xd2, 0xf8, 0xf5, 0xaa, 0x94, 0xf8, 0x4a } };

	EFI_STATUS	Status;
	EFI_EVENT 	Event;
	VOID *pRegistration;
    SETUP_DATA *SetupData = NULL;
    UINTN VariableSize = 0;	
    EFI_GUID SetupGuid = SETUP_GUID;

	// initialize AMI library
	InitAmiLib(ImageHandle, SystemTable);

	// initiaize the ImageHandle and DriverBindingHandle
	gConSplitterDriverBindingProtocol.DriverBindingHandle = NULL;
	gConSplitterDriverBindingProtocol.ImageHandle = ImageHandle;

	// Install driver binding protocol here
	Status = pBS->InstallMultipleProtocolInterfaces (
						&gConSplitterDriverBindingProtocol.DriverBindingHandle,
						&gEfiDriverBindingProtocolGuid, &gConSplitterDriverBindingProtocol,
#ifdef EFI_DEBUG
						&gEfiComponentName2ProtocolGuid, &gComponentName,
#endif
                        &gAmiMultiLangSupportGuid, &gMultiLangSupportProtocol,
						NULL);

	// Create and event for the Simple In Interface
	Status = pBS->CreateEvent (EFI_EVENT_NOTIFY_WAIT, TPL_NOTIFY,
				CSWaitForKey, &mCSSimpleInProtocol,
				&mCSSimpleInProtocol.WaitForKey
				);
	ASSERT_EFI_ERROR (Status);

	// Create and event for the SimpleInEx Interface
	Status = pBS->CreateEvent (EFI_EVENT_NOTIFY_WAIT, TPL_NOTIFY,
				CSWaitForKey, &mCSSimpleInExProtocol,
				&mCSSimpleInExProtocol.WaitForKeyEx
				);
	ASSERT_EFI_ERROR (Status);


	// Create and event for the KeycodeIn Interface
	Status = pBS->CreateEvent (EFI_EVENT_NOTIFY_WAIT, TPL_NOTIFY,
				CSWaitForKey, &mCSKeycodeInProtocol,
				&mCSKeycodeInProtocol.WaitForKeyEx
				);
	ASSERT_EFI_ERROR (Status);

    // Create an event for the SimplePointer Interface
    Status = pBS->CreateEvent(
        EFI_EVENT_NOTIFY_WAIT, 
        TPL_NOTIFY,
        ConSplitterSimplePointerWaitForInput, 
        &mCSSimplePointerProtocol,
        &mCSSimplePointerProtocol.WaitForInput
    );
    ASSERT_EFI_ERROR(Status);

	// Initialize the global lists here 
	DListInit(&ConInList);
	DListInit(&ConOutList);
	DListInit(&ConPointerList);
    DListInit(&ConInKeyNotifyList);

	// Register Protocol Notification to expose 
	// Console Splitter interface only after all consoles initialized
	RegisterProtocolCallback(
		&guidConOutStarted, ReportNoConOutError,
		NULL, &Event,&pRegistration
	);
	RegisterProtocolCallback(
		&guidConInStarted, UpdateSystemTableConIn,
		NULL, &Event,&pRegistration
	);

    //We need a valid handle
    //The only way to create it is to install a protocol
    //Let's install a dummy protocol
	pBS->InstallMultipleProtocolInterfaces (
		&ConSplitHandle,
		&gDummyProtocolGuid, NULL,
		NULL
	);
	
    //install pST->ConOut
    UpdateSystemTableConOut();

//multi keyboard layout support
	Status = pBS->CreateEventEx(
					EVT_NOTIFY_SIGNAL,
					TPL_CALLBACK,
					CSSetKbLayoutNotifyFn,
					NULL,
					&SetKeyboardLayoutEventGuid,
					&Event);
	CSSetKbLayoutNotifyFn(NULL, NULL);

    // Lighten up the keyboard(s) lights
    if(NumLockSet == FALSE) {
        Status = GetEfiVariable(L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData);	
        if (!EFI_ERROR(Status)) {
            if (SetupData->Numlock) {
                mCSToggleState |= NUM_LOCK_ACTIVE;
            }
            pBS->FreePool(SetupData);
        }
        NumLockSet=TRUE;
    }

	return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSSupported
//
// Description:
//  This function is Console splitter driver Supported function for driver
//  binding protocol
//
// Input:   
//  IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to driver binding protocol
//  IN EFI_HANDLE ControllerHandle - controller handle to install driver on
//  IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath - pointer to device path
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - driver supports given controller
//          EFI_UNSUPPORTED - driver doesn't support given controller
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSSupported (
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE                  ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
)
{
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL			*SimpleIn = NULL;
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL		*SimpleInEx = NULL;
	AMI_EFIKEYCODE_PROTOCOL                 *KeycodeIn = NULL;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*SimpleOut = NULL;
    EFI_SIMPLE_POINTER_PROTOCOL *SimplePointer = NULL;
    EFI_STATUS  SimplePointerStatus;
	EFI_STATUS	OutStatus;
	EFI_STATUS	InStatus;
	EFI_STATUS	InExStatus;
	EFI_STATUS	KeycodeInStatus;
    INT32       Dummy;
	
	if (ControllerHandle == ConSplitHandle)
		return EFI_UNSUPPORTED;

	// check to see if this device has a simple text out protocol installed on it
	OutStatus = pBS->OpenProtocol ( ControllerHandle, &gSimpleTextOutGuid,
							&SimpleOut, This->DriverBindingHandle,
							ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER );
    if(!EFI_ERROR(OutStatus)) {
        OutStatus = IsModeSupported(SimpleOut, MasterMode.Mode, &Dummy);
        if(EFI_ERROR(OutStatus)) {
            pBS->CloseProtocol(ControllerHandle, &gSimpleTextOutGuid,
						       This->DriverBindingHandle, ControllerHandle);
        }
    }


	// check to see if this device has a simple input protocol installed on it
	InStatus = pBS->OpenProtocol ( ControllerHandle, &gSimpleInGuid,
							&SimpleIn, This->DriverBindingHandle,
							ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER );
    InExStatus = pBS->OpenProtocol ( ControllerHandle, &gSimpleInExGuid,
							&SimpleInEx, This->DriverBindingHandle,
							ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER );
    KeycodeInStatus = pBS->OpenProtocol ( ControllerHandle, &gAmiEfiKeycodeGuid,
							&KeycodeIn, This->DriverBindingHandle,
							ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER );

    // check if device has simple pointer protocol installed on it
    SimplePointerStatus = pBS->OpenProtocol(
        ControllerHandle, 
        &gEfiSimplePointerProtocolGuid,
        &SimplePointer, 
        This->DriverBindingHandle,
        ControllerHandle, 
        EFI_OPEN_PROTOCOL_BY_DRIVER 
    );
    if (!EFI_ERROR(SimplePointerStatus))
        pBS->CloseProtocol(
            ControllerHandle,
            &gEfiSimplePointerProtocolGuid,
            This->DriverBindingHandle,
            ControllerHandle
        );

	if (!EFI_ERROR(OutStatus))
		pBS->CloseProtocol(ControllerHandle, &gSimpleTextOutGuid,
						   This->DriverBindingHandle, ControllerHandle);

	if (!EFI_ERROR(InStatus))
		pBS->CloseProtocol(ControllerHandle, &gSimpleInGuid,
						   This->DriverBindingHandle, ControllerHandle);

	if (!EFI_ERROR(InExStatus))
		pBS->CloseProtocol(ControllerHandle, &gAmiEfiKeycodeGuid,
						   This->DriverBindingHandle, ControllerHandle);

	if (!EFI_ERROR(KeycodeInStatus))
		pBS->CloseProtocol(ControllerHandle, &gSimpleInExGuid,
						   This->DriverBindingHandle, ControllerHandle);

	if ( EFI_ERROR(SimplePointerStatus) && 
         EFI_ERROR(OutStatus) && 
         EFI_ERROR(InStatus) && 
         EFI_ERROR(InExStatus) && 
         EFI_ERROR(KeycodeInStatus) )
		return EFI_UNSUPPORTED;

	return EFI_SUCCESS;
}


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSStart
//
// Description:
//  This function is Console splitter driver Start function for driver
//  binding protocol
//
// Input:   
//  IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to driver binding protocol
//  IN EFI_HANDLE ControllerHandle - controller handle to install driver on
//  IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath - pointer to device path
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - driver started successfully
//          EFI_UNSUPPORTED - driver didn't start
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSStart(
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE                  ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
)
{
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL			*SimpleIn = NULL;
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL		*SimpleInEx = NULL;
	AMI_EFIKEYCODE_PROTOCOL                 *KeycodeIn = NULL;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*SimpleOut = NULL;
    EFI_SIMPLE_POINTER_PROTOCOL *SimplePointer = NULL;
    EFI_STATUS  Status;
	EFI_STATUS	OutStatus;
	EFI_STATUS	InStatus;
	EFI_STATUS	InExStatus;
	EFI_STATUS	KeycodeInStatus;

	// grab the pointers for the ConIn, ConOut, and StdErr from the System Table
	// install the current handles for these devices.
	
	// if Simple In, add the Con In device to the list and 
	InStatus = pBS->OpenProtocol(ControllerHandle, &gSimpleInGuid,
								&SimpleIn, This->DriverBindingHandle,
								ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER );
	InExStatus = pBS->OpenProtocol(ControllerHandle, &gSimpleInExGuid,
								&SimpleInEx, This->DriverBindingHandle,
								ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER );
    KeycodeInStatus = pBS->OpenProtocol(ControllerHandle, &gAmiEfiKeycodeGuid,
								&KeycodeIn, This->DriverBindingHandle,
								ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER );

	if (!EFI_ERROR(InStatus) || !EFI_ERROR(InExStatus) || !EFI_ERROR(KeycodeInStatus))
	{
		InStatus = InstallConInDevice(SimpleIn, SimpleInEx, KeycodeIn, ControllerHandle);
		if (InStatus == EFI_OUT_OF_RESOURCES)
			return InStatus;

		if (!EFI_ERROR(InStatus))
			pBS->OpenProtocol(ControllerHandle, &gSimpleInGuid,
						      &SimpleIn, This->DriverBindingHandle,
						      ConSplitHandle, EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );
	}			

    Status = pBS->OpenProtocol(
        ControllerHandle, 
        &gEfiSimplePointerProtocolGuid,
        &SimplePointer, 
        This->DriverBindingHandle,
        ControllerHandle, 
        EFI_OPEN_PROTOCOL_BY_DRIVER 
    );
    if (!EFI_ERROR(Status)) {
        Status = InstallSimplePointerDevice( SimplePointer, ControllerHandle );
        if (!EFI_ERROR(Status)) {
            Status = pBS->OpenProtocol(
                ControllerHandle, 
                &gEfiSimplePointerProtocolGuid,
                &SimplePointer, 
                This->DriverBindingHandle,
                ConSplitHandle, 
                EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 
            );
        } else if (Status == EFI_OUT_OF_RESOURCES)
            return Status;
    }

	// if it has a simple text out add the Con Out device to the list and 
	OutStatus = pBS->OpenProtocol(ControllerHandle, &gSimpleTextOutGuid,
								&SimpleOut, This->DriverBindingHandle,
								ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER );
	if (!EFI_ERROR(OutStatus) )
	{
		OutStatus = InstallConOutDevice(SimpleOut, ControllerHandle);
		if (OutStatus == EFI_OUT_OF_RESOURCES)
			return OutStatus;

		if (!EFI_ERROR(OutStatus))
		{
			RestoreTheScreen(ControllerHandle,SimpleOut);
			pBS->OpenProtocol(ControllerHandle, &gSimpleTextOutGuid,
						  	  &SimpleOut, This->DriverBindingHandle,
						      ConSplitHandle, EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );
		}
	}			
	
	// If no devices were installed, then Houston we have a problem
	if ( EFI_ERROR(OutStatus) && EFI_ERROR(InStatus) && EFI_ERROR(Status) )
		return EFI_UNSUPPORTED;

	return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSStop
//
// Description:
//  This function is Console splitter driver Stop function for driver
//  binding protocol
//
// Input:   
//  IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to driver binding protocol
//  IN EFI_HANDLE ControllerHandle - controller handle to install driver on
//  IN UINTN NumberOfChildren - number of childs on this handle
//  IN OPTIONAL EFI_HANDLE *ChildHandleBuffer - pointer to child handles array
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - driver stopped successfully
//          EFI_INVALID_PARAMETER - invalid values passed for NumberOfChildren or
//                                  ChildHandleBuffer
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS CSStop (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE                  ControllerHandle,
    IN UINTN                       NumberOfChildren,
    IN EFI_HANDLE                  *ChildHandleBuffer OPTIONAL
)
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    DLINK *ListPtr;
    CON_SPLIT_IN *SimpleIn;
    CON_SPLIT_OUT *SimpleOut;
    CON_SPLIT_SIMPLE_POINTER *SimplePointer = NULL;
    BOOLEAN Stopped = FALSE;
    DLINK *HandleLink = NULL;
    CON_SPLIT_IN_KEY_NOTIFY *CsInKeyNotify = NULL;
    CON_SPLIT_IN_KEY_NOTIFY_HANDLE  *CsInNotifyHandle = NULL;
    
    if (NumberOfChildren == 0) 
        return EFI_SUCCESS;

    if ( NumberOfChildren != 1 || 
         ChildHandleBuffer == NULL ||
         *ChildHandleBuffer!= ConSplitHandle ) 
        return EFI_INVALID_PARAMETER;

    // remove simple text out, simple in, simple pointer
    ListPtr = ConOutList.pHead;
    while ( ListPtr != NULL)
    {
        SimpleOut = OUTTER(ListPtr, Link, CON_SPLIT_OUT);
        if ( SimpleOut->Handle == ControllerHandle)
        {
            pBS->CloseProtocol(ControllerHandle, &gSimpleTextOutGuid,
                        This->DriverBindingHandle, ControllerHandle);

            pBS->CloseProtocol(ControllerHandle, &gSimpleTextOutGuid,
                        This->DriverBindingHandle, ConSplitHandle);
            DListDelete(&ConOutList, ListPtr);
            Stopped = TRUE;
            SaveTheScreen(ControllerHandle, SimpleOut->SimpleOut);
            Status = pBS->FreePool(SimpleOut);
            break;
        }
        
        ListPtr = ListPtr->pNext;
    }

    //If we already populated pST->ConOut preserve
    //screen buffer and list of supported modes
    //to keep using it when ConOut devices are connected
    if(ConOutList.Size == 0 && !pST->ConOut) //all devices stops
    {
        if(SupportedModes != NULL) 
        { 
            pBS->FreePool(SupportedModes); 
            SupportedModes = NULL; 
        }

        if(ScreenBuffer != NULL) 
        { 
            pBS->FreePool(ScreenBuffer); 
            ScreenBuffer = NULL; 
        }

        if(AttributeBuffer != NULL) 
        { 
            pBS->FreePool(AttributeBuffer); 
            AttributeBuffer = NULL; 
        }

        MasterMode.Mode=0;
    } else {
        if(Stopped && ConOutList.Size > 0) //re-initialize supported modes buffer if at least one child was stopped
            AdjustSupportedModes();
    }

    ListPtr = ConInList.pHead;
    while ( ListPtr != NULL)
    {
        SimpleIn = OUTTER(ListPtr, Link, CON_SPLIT_IN);
        if ( SimpleIn->Handle == ControllerHandle)
        {
            DListDelete(&ConInList, ListPtr);

            pBS->CloseProtocol(ControllerHandle, &gSimpleInGuid,
                        This->DriverBindingHandle, ControllerHandle);

            pBS->CloseProtocol(ControllerHandle, &gSimpleInExGuid,
                        This->DriverBindingHandle, ControllerHandle);

            pBS->CloseProtocol(ControllerHandle, &gAmiEfiKeycodeGuid,
                        This->DriverBindingHandle, ControllerHandle);

            pBS->CloseProtocol(ControllerHandle, &gSimpleInGuid,
                        This->DriverBindingHandle, ConSplitHandle);
            break;
        }
        
        ListPtr = ListPtr->pNext;
    }

    if (ListPtr != NULL && SimpleIn->SimpleInEx != NULL) {
        for (ListPtr = ConInKeyNotifyList.pHead; ListPtr != NULL; ListPtr = ListPtr->pNext) {
            CsInKeyNotify = OUTTER(ListPtr, Link, CON_SPLIT_IN_KEY_NOTIFY);
     
            for (HandleLink = CsInKeyNotify->NotifyHandleList.pHead; HandleLink != NULL; 
                    HandleLink = HandleLink->pNext) {
                CsInNotifyHandle = OUTTER(HandleLink, Link, CON_SPLIT_IN_KEY_NOTIFY_HANDLE);
    	
                if (SimpleIn->SimpleInEx != CsInNotifyHandle->SimpleInEx) {
                    continue;
                }

                Status = SimpleIn->SimpleInEx->UnregisterKeyNotify(
                            SimpleIn->SimpleInEx, CsInNotifyHandle->NotifyHandle);
            
                DListDelete(&(CsInKeyNotify->NotifyHandleList), HandleLink);
                Status = pBS->FreePool(CsInNotifyHandle);
            }
        }
        Status = pBS->FreePool(SimpleIn);
    }

    ListPtr = ConPointerList.pHead;
    while (ListPtr != NULL) {
        SimplePointer = OUTTER(ListPtr, Link, CON_SPLIT_SIMPLE_POINTER);
        if ( SimplePointer->Handle == ControllerHandle ) {
            DListDelete(&ConPointerList, ListPtr);

            pBS->CloseProtocol(
                ControllerHandle, 
                &gEfiSimplePointerProtocolGuid,
                This->DriverBindingHandle, 
                ControllerHandle
            );
            
            pBS->CloseProtocol(
                ControllerHandle, 
                &gEfiSimplePointerProtocolGuid,
                This->DriverBindingHandle, 
                ConSplitHandle
            );
            Status = pBS->FreePool(SimplePointer);
            break;
        }
        ListPtr = ListPtr->pNext;
    }

    return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: UpdateConVar
//
// Description:
//  This function stores device path of given controller in EFI variable with
//  name sVarName
//
// Input:   
//  IN EFI_HANDLE Controller - controller, which device path to store
//  IN CHAR16 *sVarName - name of EFI variable to store device path under
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

VOID UpdateConVar(
    IN EFI_HANDLE Controller, 
    IN CHAR16     *sVarName
)
{
	static EFI_GUID guidDevicePath = EFI_DEVICE_PATH_PROTOCOL_GUID;
	static EFI_GUID guidEfiVar = EFI_GLOBAL_VARIABLE;
	EFI_DEVICE_PATH_PROTOCOL *pDevicePath, *pConDev = NULL;
	EFI_STATUS Status;
	UINTN DataSize=0;
	UINT32 Attributes;

	Status = pBS->HandleProtocol(Controller,&guidDevicePath, &pDevicePath);
	if (EFI_ERROR(Status)) 
        return;
    
	Status = GetEfiVariable(sVarName, &guidEfiVar, &Attributes, &DataSize, &pConDev);
	if (EFI_ERROR(Status))
	{
		if (Status!=EFI_NOT_FOUND) 
            return;

		DataSize = DPLength(pDevicePath);
		pRS->SetVariable(sVarName, &guidEfiVar, 
                        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS, 
                        DataSize, pDevicePath);
		return;
	}

	if (!DPIsOneOf(pConDev, pDevicePath, FALSE))
	{
		EFI_DEVICE_PATH_PROTOCOL *pNewConDev = DPAddInstance(pConDev, pDevicePath);
		DataSize = DPLength(pNewConDev);
		pRS->SetVariable(sVarName, &guidEfiVar, Attributes, DataSize, pNewConDev);
		pBS->FreePool(pNewConDev);
	}

	pBS->FreePool(pConDev);
}


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: InstallSimplePointerDevice
//
// Description:
//  This function adds another ConIn device to splitter
//
// Input:   
//  *SimpleIn - pointer to new protocol
//  *SimpleInEx - pointer to new extended protocol
//  *KeycodeIn - pointer to AMI key code protocol
//  Handle - handle of new device
//
// Output:
//          EFI_SUCCESS - device added successfully
//          EFI_UNSUPPORTED - device not supported
//          EFI_OUT_OF_RESOURCES - not enough resources to perform operation
// 
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS InstallSimplePointerDevice(
    IN EFI_SIMPLE_POINTER_PROTOCOL *SimplePointer, 
    IN EFI_HANDLE Handle ) 
{
    EFI_STATUS Status;
    CON_SPLIT_SIMPLE_POINTER *ConSimplePointer = NULL;

    if (EFI_ERROR(ConSimplePointerHandleCheck(Handle)))
        return EFI_UNSUPPORTED;

    Status = pBS->AllocatePool(
        EfiBootServicesData, 
        sizeof(CON_SPLIT_SIMPLE_POINTER), 
        &ConSimplePointer
    );
    if (EFI_ERROR(Status))
        return EFI_OUT_OF_RESOURCES;

    ConSimplePointer->SimplePointer = SimplePointer;
    ConSimplePointer->Handle = Handle;
    mCSSimplePointerProtocol.Mode->LeftButton |= SimplePointer->Mode->LeftButton;
    mCSSimplePointerProtocol.Mode->RightButton |= SimplePointer->Mode->RightButton;
	DListAdd(&ConPointerList, &ConSimplePointer->Link);	
    return EFI_SUCCESS;
}


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: InstallConOutDevice
//
// Description:
//  This function adds another ConOut device to splitter
//
// Input:   
//  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *SimpleOut - pointer to new protocol
//  IN EFI_HANDLE Handle - handle of new device
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - device added successfully
//          EFI_UNSUPPORTED - device not supported
//          EFI_OUT_OF_RESOURCES - not enough resources to perform operation
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS InstallConOutDevice(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *SimpleOut, 
    IN EFI_HANDLE                      Handle
)
{
	EFI_STATUS		Status;
	CON_SPLIT_OUT	*ConOut;
	INT32	DeviceModeNumber = 0;
    BOOLEAN FirstChild = FALSE;

	if (EFI_ERROR(ConOutHandleCheck(Handle)))
		return EFI_UNSUPPORTED;

	if(MasterMode.Mode != 0) //already in extended mode
		if (EFI_ERROR(IsModeSupported(SimpleOut, MasterMode.Mode, &DeviceModeNumber)))
			return EFI_UNSUPPORTED;	//device doesn't support current mode - do not include into list


    if (ConOutList.Size==0 && !InitModesTableCalled)     //this is first call
	{
        FirstChild = TRUE;
		Status = InitModesTable(SimpleOut, Handle);
		if(EFI_ERROR(Status)) //first device becomes master
			return Status;
	}
	else 
        UpdateModesTable(SimpleOut, Handle); //all next devices

		
	Status = pBS->AllocatePool(EfiBootServicesData, sizeof(CON_SPLIT_OUT), &ConOut);
	if (EFI_ERROR(Status))
		return EFI_OUT_OF_RESOURCES;

	ConOut->SimpleOut = SimpleOut;

	ConOut->Handle = Handle;

	DListAdd(&ConOutList, &(ConOut->Link));	

    if(!FirstChild) {
	// set child display to a current master mode
	    SimpleOut->SetMode(SimpleOut, DeviceModeNumber);
        SimpleOut->EnableCursor(SimpleOut, MasterMode.CursorVisible);
    }
	UpdateConVar(Handle, L"ConOutDev");
	return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: InstallConInDevice
//
// Description:
//  This function adds another ConIn device to splitter
//
// Input:   
//  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *SimpleIn - pointer to new protocol
//  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *SimpleInEx - pointer to new extended
//                                                     protocol
//  IN AMI_EFIKEYCODE_PROTOCOL *KeycodeIn - pointer to AMI key code protocol
//  IN EFI_HANDLE Handle - handle of new device
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - device added successfully
//          EFI_UNSUPPORTED - device not supported
//          EFI_OUT_OF_RESOURCES - not enough resources to perform operation
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS InstallConInDevice(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL    *SimpleIn, 
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *SimpleInEx, 
    IN AMI_EFIKEYCODE_PROTOCOL           *KeycodeIn, 
    IN EFI_HANDLE                        Handle
)
{
	EFI_STATUS	Status;
	CON_SPLIT_IN	*ConIn;
    DLINK           *ListPtr;
	CON_SPLIT_IN_KEY_NOTIFY         *CsInKeyNotify = NULL;
    CON_SPLIT_IN_KEY_NOTIFY_HANDLE  *CsInNotifyHandle = NULL;

	if (EFI_ERROR(ConInHandleCheck(Handle)))
		return EFI_UNSUPPORTED;
	
	Status = pBS->AllocatePool(EfiBootServicesData, sizeof(CON_SPLIT_IN), &ConIn);
	if (EFI_ERROR(Status))
		return EFI_OUT_OF_RESOURCES;
		
	ConIn->SimpleIn = SimpleIn;
	ConIn->SimpleInEx = SimpleInEx;
	ConIn->KeycodeInEx = KeycodeIn;

	ConIn->Handle = Handle;
	
	DListAdd(&ConInList, &(ConIn->Link));	

	UpdateConVar(Handle, L"ConInDev");	

    if (SimpleInEx == NULL) {
        return EFI_SUCCESS;
    }

    SimpleInEx->SetState(SimpleInEx, &mCSToggleState);

    for (ListPtr = ConInKeyNotifyList.pHead; ListPtr != NULL; ListPtr = ListPtr->pNext) {
        CsInKeyNotify = OUTTER(ListPtr, Link, CON_SPLIT_IN_KEY_NOTIFY);

        Status = pBS->AllocatePool(EfiBootServicesData, 
                 sizeof(CON_SPLIT_IN_KEY_NOTIFY_HANDLE), &CsInNotifyHandle);
        if (EFI_ERROR(Status)) {
            return EFI_OUT_OF_RESOURCES;
        }

        CsInNotifyHandle->SimpleInEx = SimpleInEx;

        Status = SimpleInEx->RegisterKeyNotify(SimpleInEx, &CsInKeyNotify->KeyData, 
                    CsInKeyNotify->KeyNotificationFunction, &(CsInNotifyHandle->NotifyHandle));
        if (EFI_ERROR(Status)) {
            Status = pBS->FreePool(CsInNotifyHandle);
            continue;
        }
 
        DListAdd(&(CsInKeyNotify->NotifyHandleList), &(CsInNotifyHandle->Link));
    }

	return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ConOutHandleCheck
//
// Description:
//  This function checks if ConOut device already present in Splitter
//
// Input:   
//  IN EFI_HANDLE Handle - handle of device to check
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - device not present
//          EFI_UNSUPPORTED - device already present
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS ConOutHandleCheck(
    IN EFI_HANDLE Handle
)
{
	CON_SPLIT_OUT *SimpleOut = OUTTER(ConOutList.pHead, Link, CON_SPLIT_OUT);
	
	// if the list is empty return the status that was passed in 
	if (SimpleOut == NULL)
		return EFI_SUCCESS;

	// check for a handle that was already identified
	while ( SimpleOut != NULL)
	{
		// check the handle
		if (SimpleOut->Handle == Handle)
			return EFI_UNSUPPORTED;
		// go to the next element in the list
		SimpleOut = OUTTER(SimpleOut->Link.pNext, Link, CON_SPLIT_OUT);
	}

	// if it is a new handle return the status pass in
	return EFI_SUCCESS;		
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ConInHandleCheck
//
// Description:
//  This function checks if ConIn device already present in Splitter
//
// Input:   
//  IN EFI_HANDLE Handle - handle of device to check
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - device not present
//          EFI_UNSUPPORTED - device already present
// 
// Modified:
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS ConInHandleCheck(
    IN EFI_HANDLE Handle
)
{
	CON_SPLIT_IN *SimpleIn = OUTTER(ConInList.pHead, Link, CON_SPLIT_IN);
	
	// if the list is empty return the status that was passed in 
	if (SimpleIn == NULL)
		return EFI_SUCCESS;

	// check for a handle that was already identified
	while ( SimpleIn != NULL)
	{
		// check the handle
		if (SimpleIn->Handle == Handle)
			return EFI_UNSUPPORTED;
		// go to the next element in the list
		SimpleIn = OUTTER(SimpleIn->Link.pNext, Link, CON_SPLIT_IN);
	}

	// if it is a new handle return the status pass in
	return EFI_SUCCESS;		
}


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ConSimplePointerHandleCheck
//
// Description:
//  This function checks if ConIn device already present in Splitter.
//
// Input:   Handle - handle of device to check
//
// Output:
//          EFI_SUCCESS - device not present
//          EFI_UNSUPPORTED - device already present
// 
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS ConSimplePointerHandleCheck( IN EFI_HANDLE Handle )
{
    CON_SPLIT_SIMPLE_POINTER *SimplePointer;

    SimplePointer = OUTTER(ConPointerList.pHead, Link, CON_SPLIT_SIMPLE_POINTER);

    // if the list is empty return the status that was passed in 
    if (SimplePointer == NULL)
        return EFI_SUCCESS;

    // check for a handle that was already identified
    while ( SimplePointer != NULL) {

        // check the handle
        if (SimplePointer->Handle == Handle)
            return EFI_UNSUPPORTED;

        // go to the next element in the list
        SimplePointer = OUTTER(SimplePointer->Link.pNext, Link, CON_SPLIT_SIMPLE_POINTER);
    }

    // if it is a new handle return the status pass in
    return EFI_SUCCESS;
}


// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: InitModesTable
//
// Description:
//  This function fills the SupportedModes table with modes supported by first 
//  simple text out device
//
// Input:   
//  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to protocol
//  IN EFI_HANDLE Handle - handle of first ConOut device
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - table filled successfully
//          EFI_OUT_OF_RESOURCES - not enough resources to perform operation
// 
// Modified:    SupportedModes, MasterMode
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS InitModesTable(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN EFI_HANDLE                      Handle
)
{
	INT32 MaxMode;
	INT32 CurrentMode;
	UINTN Rows, Columns;
	INT32 i;
	EFI_STATUS Status;

	if(Handle == ConSplitHandle) 
        return EFI_SUCCESS;

    InitModesTableCalled = TRUE;

	MaxMode = This->Mode->MaxMode;
	CurrentMode = This->Mode->Mode;

    //The SupportedModes structure
    //may have already been initialized in UpdateSystemTableConOut.
    //If this is the case, free the memory before reinitialization.
    if (SupportedModes!=NULL){
        //If SupportedModes is not NULL, 
        //ResizeSplitterBuffer(0) has already been called
        pBS->FreePool(SupportedModes);
        SupportedModes = NULL;
    }

	Status = pBS->AllocatePool(EfiBootServicesData, sizeof(SUPPORT_RES)* MaxMode,
				                &SupportedModes);
	if(EFI_ERROR(Status))
	{
		MasterMode.MaxMode = 1;
		return EFI_SUCCESS;
	}

	MasterMode.MaxMode = MaxMode; //modify default value

	for(i = 0; i < MaxMode; i++)
	{
		Status = This->QueryMode(This, i, &Columns, &Rows);
		SupportedModes[i].Rows = (INT32)Rows;
		SupportedModes[i].Columns = (INT32)Columns;
		SupportedModes[i].AllDevices = EFI_ERROR(Status) ? FALSE : TRUE;
	}

//Make sure MasterMode.Mode <> CurrentMode, otherwise ResizeSplitterBuffer won't do anything
    MasterMode.Mode = CurrentMode + 1;
    Status = ResizeSplitterBuffer(CurrentMode);
    MasterMode.Mode = CurrentMode;
	return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: IsModeSupported
//
// Description:
//  This function determines if mode, specified by ModeNum supported by 
//  simple text out device
//
// Input:   
//  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to protocol to check
//  IN UINTN ModeNum - mode to check
//  OUT INT32 *DeviceModeNumber - device mode number correspondent to ModeNum
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - mode supported by device
//          EFI_UNSUPPORTED - mode not supported by device
// 
// Modified:
//
// Referrals:   SupportedModes
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS IsModeSupported(
    IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN  UINTN                           ModeNum, 
	OUT INT32                           *DeviceModeNumber)
{
	INT32 MaxMode;
	UINTN Rows, Columns;
	INT32 i;
	EFI_STATUS Status;

	MaxMode = This->Mode->MaxMode;	
	for(i = 0; i < MaxMode; i++)
	{
		Status = This->QueryMode(This, i , &Columns, &Rows);
		if (!EFI_ERROR(Status) && \
		    SupportedModes[ModeNum].Rows == (INT32)Rows && \
		    SupportedModes[ModeNum].Columns == (INT32)Columns)
		{
			*DeviceModeNumber = i;
			return EFI_SUCCESS;
		}

	}
	return EFI_UNSUPPORTED;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: UpdateModesTable
//
// Description:
//  This function updates supported modes table when new devices started don't 
//  support some of this modes
//
// Input:   
//  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to protocol to check
//  IN EFI_HANDLE Handle - handle of device
//
// Output:
//      VOID
// 
// Modified:    SupportedModes
//
// Referrals:   
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

VOID UpdateModesTable(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN EFI_HANDLE                      Handle
)
{
	INT32 i, ModeNumber;
	EFI_STATUS Status;

	if(Handle == ConSplitHandle) 
        return;

	
	for(i = 0; i < MasterMode.MaxMode; i++)	{
		if(SupportedModes[i].AllDevices == FALSE) continue;
		Status = IsModeSupported(This, i, &ModeNumber);
		SupportedModes[i].AllDevices = EFI_ERROR(Status) ? FALSE : TRUE;
	}

//update MasterMode.MaxMode value based on modes supported by different devices
//lookup for the first mode above 1 not supported by all devices - this will be
//new MaxMode value
    for(i = 2; i < MasterMode.MaxMode; i++) {
        if(SupportedModes[i].AllDevices == FALSE) {
            MasterMode.MaxMode = i;
            break;
        }
    }
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: ResizeSplitterBuffer
//
// Description:
//  This function allocates new buffers when mode changed 
//
// Input:   
//  IN INT32 ModeNum - new mode
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - new buffers allocated
//          EFI_OUT_OF_RESOURCES - not enough resources to perform operation
// 
// Modified:    ScreenBuffer, EndOfTheScreen,AttributeBuffer
//
// Referrals:   SupportedModes, MasterMode
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS ResizeSplitterBuffer(
    IN INT32 ModeNum
)
{
	INT32 Row, Col;
	CHAR16 *NewCharBuffer;
	INT32 *NewAttributeBuffer;
	EFI_STATUS Status;

	if(ModeNum != MasterMode.Mode || SupportedModes == NULL) //check if it is first init
	{

		if(SupportedModes == NULL)
		{
			Row = 25;
			Col = 80;
		}
		else
		{
			Row = SupportedModes[ModeNum].Rows;
			Col = SupportedModes[ModeNum].Columns;
		}

		Status = pBS->AllocatePool(EfiBootServicesData, 
                                    sizeof(CHAR16) * Row * Col, 
                                    &NewCharBuffer);
		if(EFI_ERROR(Status)) 
            return Status;

		Status = pBS->AllocatePool(EfiBootServicesData, 
                                    sizeof(INT32) * Row * Col, 
                                    &NewAttributeBuffer);
		if(EFI_ERROR(Status)) 
		{
			pBS->FreePool(NewCharBuffer);
			return Status;
		}

		if(ScreenBuffer != NULL) 
            pBS->FreePool(ScreenBuffer);
		ScreenBuffer = NewCharBuffer;
		EndOfTheScreen = ScreenBuffer + (Row * Col);

		if(AttributeBuffer != NULL) 
            pBS->FreePool(AttributeBuffer);
		AttributeBuffer = NewAttributeBuffer;
		Columns = Col;
	}
	MemClearScreen();
	return EFI_SUCCESS;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: CSSetKbLayoutNotifyFn
//
// Description:
//  This function stores a pointer to the current keyboard layout
//
// Input:   
//  IN EFI_EVENT Event - event that caused this function to be called
//  IN VOID *Context - context of the event
//
// Output:
//      VOID
// 
// Modified:
//  gKeyDescriptorList - changed to point to the current EFI_HII_KEYBOARD_LAYOUT
// 						  or, NULL if no layout currently set
//  LayoutLength - set to the size of the current keyboard layout
//
// Referrals:
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

VOID CSSetKbLayoutNotifyFn(
    IN EFI_EVENT Event, 
    IN VOID *Context)
{
    EFI_STATUS Status;

    if(HiiDatabase == NULL) {
	    Status = pBS->LocateProtocol(&gEfiHiiDatabaseProtocolGuid, NULL, &HiiDatabase);
        if(EFI_ERROR(Status))
            return;
    }

    Status = HiiDatabase->GetKeyboardLayout(HiiDatabase, NULL, &KeyDescriptorListSize, gKeyDescriptorList);
    if (Status == EFI_BUFFER_TOO_SMALL) {
        if(gKeyDescriptorList != NULL)
            pBS->FreePool(gKeyDescriptorList);

        Status = pBS->AllocatePool(EfiBootServicesData, KeyDescriptorListSize, &gKeyDescriptorList);
        if(EFI_ERROR(Status)) {
            KeyDescriptorListSize = 0;
            gKeyDescriptorList = NULL;
        } else {
            HiiDatabase->GetKeyboardLayout(HiiDatabase, NULL, &KeyDescriptorListSize, gKeyDescriptorList);
        }
    } else if(Status == EFI_NOT_FOUND) {
        if(gKeyDescriptorList != NULL) {
            pBS->FreePool(gKeyDescriptorList);
            KeyDescriptorListSize = 0;
            gKeyDescriptorList = NULL;
        }
    }
}

VOID AdjustSupportedModes(
    VOID
)
{
    DLINK *ListPtr;
    CON_SPLIT_OUT *SimpleOut;
    EFI_STATUS Status;
    INT32 i;
    UINTN Columns;
    UINTN Rows;

    ListPtr = ConOutList.pHead;
    SimpleOut = OUTTER(ListPtr, Link, CON_SPLIT_OUT);

//re-initialize supported modes buffer
    if(MasterMode.MaxMode < SimpleOut->SimpleOut->Mode->MaxMode) {
        if (SupportedModes != NULL)
            pBS->FreePool(SupportedModes);
        Status = pBS->AllocatePool(EfiBootServicesData, SimpleOut->SimpleOut->Mode->MaxMode * sizeof(SUPPORT_RES), &SupportedModes);
        if(EFI_ERROR(Status))
            return;
    }
    MasterMode.MaxMode = SimpleOut->SimpleOut->Mode->MaxMode;
    for(i = 0; i < MasterMode.MaxMode; i++) {
        Status = SimpleOut->SimpleOut->QueryMode(SimpleOut->SimpleOut, i, &Columns, &Rows);
		SupportedModes[i].Rows = (INT32)Rows;
		SupportedModes[i].Columns = (INT32)Columns;
		SupportedModes[i].AllDevices = EFI_ERROR(Status) ? FALSE : TRUE;
	}

//update supported modes buffer
    ListPtr = ListPtr->pNext;
    while(ListPtr != NULL) {
        SimpleOut = OUTTER(ListPtr, Link, CON_SPLIT_OUT);
        UpdateModesTable(SimpleOut->SimpleOut, SimpleOut->Handle);
        ListPtr = ListPtr->pNext;
    }
}
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: KeyboardLayoutMap
//
// Description:
//  This function maps an EFI_KEY to a Unicode character, based on the current
//  keyboard layout
//
// Input:   
//  IN AMI_EFI_KEY_DATA *KeyData - pointer to the key data returned by a device
//
// Output:
//      EFI_STATUS
//          EFI_SUCCESS - key was mapped successfully
//          EFI_NOT_FOUND - the key was not found in the keyboard layout
//			EFI_INVALID_PARAMETER - KeyData is NULL
// 
// Modified:
//  AMI_EFI_KEY_DATA *KeyData - KeyData->Key.UnicodeChar is changed to match
//      the character found in the keyboard layout
//
// Referrals:
//  EFI_HII_KEYBOARD_LAYOUT* gKeyDescriptorList - Pointer to the current
//      keyboard layout
//
// Notes:
//
//-------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS KeyboardLayoutMap(
    IN      AMI_MULTI_LANG_SUPPORT_PROTOCOL *This,
    IN OUT  AMI_EFI_KEY_DATA                *KeyData)
{
    EFI_STATUS Status;
    EFI_KEY_DESCRIPTOR *KeyDescriptor; 

    BOOLEAN AltState = FALSE;
    BOOLEAN ShiftKeyState = FALSE;
    BOOLEAN ShiftState = ShiftKeyState;
    
    static UINT16 ModifierIndex = 0xFFFF;
    static CHAR16 ModifierUnicodeChar = 0x0000;

    UINT16 i = 0;

    if(gKeyDescriptorList== NULL) {
        return EFI_NOT_FOUND;
    }

    KeyDescriptor = (EFI_KEY_DESCRIPTOR*)&(gKeyDescriptorList->Descriptors);
    
    // check alt status (left alt or right alt)
    if( ((KeyData->KeyState.KeyShiftState)&(RIGHT_ALT_PRESSED|LEFT_ALT_PRESSED)) != 0 )
        AltState = TRUE;

    if( ((KeyData->KeyState.KeyShiftState)&(RIGHT_SHIFT_PRESSED|LEFT_SHIFT_PRESSED)) != 0 )
        ShiftKeyState = TRUE;
        
    Status = EFI_NOT_FOUND;
    if ( (ModifierIndex != 0xFFFF) && (KeyDescriptor[ModifierIndex].Modifier == EFI_NS_KEY_MODIFIER) ) {
        // Previous key had a modifier, we need to find out what to do
        // for now, only handle EFI_NS_KEY_MODIFIER
        for (i = ModifierIndex+1; KeyDescriptor[i].Modifier == EFI_NS_KEY_DEPENDENCY_MODIFIER && i < gKeyDescriptorList->DescriptorCount; i++) {
            if(KeyDescriptor[i].Key == KeyData->EfiKey) {
                if ((KeyDescriptor[i].AffectedAttribute&EFI_AFFECTED_BY_STANDARD_SHIFT) != 0)
                    ShiftState = ShiftKeyState;
                else
                    ShiftState = FALSE;
                // account for cAPS lOCK, only applicable if the affected attribute is set
                if (!AltState && ((KeyDescriptor[i].AffectedAttribute&EFI_AFFECTED_BY_CAPS_LOCK) != 0) && ((KeyData->KeyState.KeyToggleState&CAPS_LOCK_ACTIVE) != 0))
                    ShiftState = !ShiftState;
                    
                if (AltState && ShiftState && (KeyDescriptor[i].ShiftedAltGrUnicode != 0x0000)) {
                    KeyData->Key.UnicodeChar = KeyDescriptor[i].ShiftedAltGrUnicode;
                    Status = EFI_SUCCESS;
                }
                else if (AltState && !ShiftState && (KeyDescriptor[i].AltGrUnicode != 0x0000)) {
                    KeyData->Key.UnicodeChar = KeyDescriptor[i].AltGrUnicode;
                    Status = EFI_SUCCESS;
                }
                else if (!AltState && ShiftState && (KeyDescriptor[i].ShiftedUnicode != 0x0000)) {
                    KeyData->Key.UnicodeChar = KeyDescriptor[i].ShiftedUnicode;
                    Status = EFI_SUCCESS;
                }
                else if (!AltState && !ShiftState && (KeyDescriptor[i].Unicode != 0x0000)) {
                    KeyData->Key.UnicodeChar = KeyDescriptor[i].Unicode;
                    Status = EFI_SUCCESS;
                }
                break;
            }
        }

        if (EFI_ERROR(Status))
            // No match found, just return the deadkey's character
            KeyData->Key.UnicodeChar = ModifierUnicodeChar;
        ModifierIndex = 0xFFFF;
        ModifierUnicodeChar = 0x0000;
        return EFI_SUCCESS;
    }

    // Search the KeyDescriptorList for a matching key
    for(i = 0; i < gKeyDescriptorList->DescriptorCount; i++)
    {
        if(KeyDescriptor[i].Key == KeyData->EfiKey || (KeyDescriptor[i].Key == 0xA5A5 && KeyData->PS2ScanCode == 0x73)) {
            if ((KeyDescriptor[i].AffectedAttribute&EFI_AFFECTED_BY_STANDARD_SHIFT) != 0)
                ShiftState = ShiftKeyState;
            else
                ShiftState = FALSE;
            // account for cAPS lOCK, only applicable if the affected attribute is set
            if (!AltState && ((KeyDescriptor[i].AffectedAttribute&EFI_AFFECTED_BY_CAPS_LOCK) != 0) && ((KeyData->KeyState.KeyToggleState&CAPS_LOCK_ACTIVE) != 0))
                ShiftState = !ShiftState;
            
            switch (KeyDescriptor[i].Modifier) {
            case EFI_NULL_MODIFIER:
                Status = EFI_SUCCESS;
                if (AltState && ShiftState) {
                    KeyData->Key.UnicodeChar = KeyDescriptor[i].ShiftedAltGrUnicode;
                }
                else if (AltState && !ShiftState) {
                    KeyData->Key.UnicodeChar = KeyDescriptor[i].AltGrUnicode;
                }
                else if (!AltState && ShiftState) {
                    KeyData->Key.UnicodeChar = KeyDescriptor[i].ShiftedUnicode;
                }
                else if (!AltState && !ShiftState) {
                    KeyData->Key.UnicodeChar = KeyDescriptor[i].Unicode;
                }
                break;
            case EFI_NS_KEY_MODIFIER:
                Status = EFI_SUCCESS;
                if (AltState && ShiftState && (KeyDescriptor[i].ShiftedAltGrUnicode != 0x0000)) {
                    ModifierIndex = i;
                    ModifierUnicodeChar = KeyDescriptor[i].ShiftedAltGrUnicode;
                    KeyData->Key.UnicodeChar = 0x0000;		// don't return a character yet, the next keypress will determine the correct character
                }
                else if (AltState && !ShiftState && (KeyDescriptor[i].AltGrUnicode != 0x0000)) {
                    ModifierIndex = i;
                    ModifierUnicodeChar = KeyDescriptor[i].AltGrUnicode;
                    KeyData->Key.UnicodeChar = 0x0000;		// don't return a character yet, the next keypress will determine the correct character
                }
                else if (!AltState && ShiftState && (KeyDescriptor[i].ShiftedUnicode != 0x0000)) {
                    ModifierIndex = i;
                    ModifierUnicodeChar = KeyDescriptor[i].ShiftedUnicode;
                    KeyData->Key.UnicodeChar = 0x0000;		// don't return a character yet, the next keypress will determine the correct character
                }
                else if (!AltState && !ShiftState && (KeyDescriptor[i].Unicode != 0x0000)) {
                    ModifierIndex = i;
                    ModifierUnicodeChar = KeyDescriptor[i].Unicode;
                    KeyData->Key.UnicodeChar = 0x0000;		// don't return a character yet, the next keypress will determine the correct character
                }
            default:
            case EFI_NS_KEY_DEPENDENCY_MODIFIER:
                // skip deadkey-dependent modifiers and unknown modifiers
                break;
            }			// switch (KeyDescriptor[i].Modifier)
            
            if (!EFI_ERROR(Status) && (KeyData->Key.UnicodeChar != 0x0000 || ModifierUnicodeChar != 0x0000))
                break;	// successfully mapped a key, break for(...) loop
        }
    }
    return Status;
}
	
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
