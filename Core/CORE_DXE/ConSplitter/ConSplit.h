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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/ConSplitter/ConSplit.h 4     8/02/13 4:27a Thomaschen $
//
// $Revision: 4 $
//
// $Date: 8/02/13 4:27a $
//*****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/ConSplitter/ConSplit.h $
// 
// 4     8/02/13 4:27a Thomaschen
// Add for EIP109384.
// [Files]  ConSplit.c, ConSplit.h, In.c, CsmSimpleIn.c.
// 
// 3     6/26/13 3:10a Thomaschen
// Remove EIP109384.
// 
// 1     6/04/13 1:53a Thomaschen
// Fixed for EIP118202.
// 
// 16    10/25/12 2:32a Deepthins
// [TAG]  		EIP99475
// [Category]  	Improvement
// [Description]  	Multi language module Support in the console splitter
// [Files]  		ConSplit.c, ConSplit.h , In.c and AmiKeycode.h
// 
// 15    8/02/12 12:14p Artems
// [TAG]  		EIP95607
// [Category]  	Bug Fix
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
// 14    8/12/11 12:17p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 
// 13    5/05/11 3:52p Artems
// Added multi-language keyboard support
// 
// 12    6/23/10 3:02p Felixp
// SimplePointer splitter support is added.
// 
// 11    7/07/09 3:35p Artems
// Added functions headers according to code standard
// 
// 10    9/17/07 4:04p Olegi
// Added support for AMI_EFIKEYCODE_PROTOCOL and
// EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.
// 
// 9     9/05/07 11:13a Felixp
// SimpleTextInEx support removed. It causes problems. Support will add
// again after Core labeling.
// 
// 8     9/04/07 2:55p Olegi
// Added EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL support.
// 
// 7     1/05/07 4:23p Artems
// 
// 6     12/29/06 3:01p Felixp
// 1. Support for GraphicsOutput protocol added
// 2. Support for more then one text mode added
// 
// 5     9/27/06 7:42p Felixp
// SetMode funciton of the ConsoleControl protocol is updated to restore
// default UGA mode when switching from grphics to text.
// 
// 4     3/13/06 2:37a Felixp
// 
// 3     12/12/05 9:32a Felixp
// Support for synchronization of console devices 
// (now screen is restored after legacy OpROM execution).
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
//
//*****************************************************************************
//<AMI_FHDR_START>
//
// Name:        ConSplit.h
//
// Description:	This file contains the structure and function prototypes needed
//              for the Console Splitter driver
//
//<AMI_FHDR_END>
//*****************************************************************************

#ifndef __CONSOLE_SPLITTER_H__
#define __CONSOLE_SPLITTER_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------------

#include <EFI.h>
#include <Protocol\SimpleTextOut.h >
#include <Protocol\SimpleTextIn.h>
#include <Protocol\SimpleTextInEx.h>
#include <Protocol\amikeycode.h>
#include <Protocol\SimplePointer.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\ComponentName2.h>
#include <AmiDxeLib.h>

//--------------------------------------------------------------------------------

#pragma pack (1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: CON_SPLIT_SIMPLE_POINTER
//
// Description: 
// This structure represents Splitter Simple Pointer devices linked list.
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Link             DLINK                           Linked list pointer
// SimplePointer    EFI_SIMPLE_POINTER_PROTOCOL*    Protocol pointer
// Handle           EFI_HANDLE                      Device handle
// 
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _CON_SPLIT_SIMPLE_POINTER {
    DLINK Link; //MUST BE THE FIRST FIELD
    EFI_SIMPLE_POINTER_PROTOCOL *SimplePointer;
    EFI_HANDLE Handle;
} CON_SPLIT_SIMPLE_POINTER;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: CON_SPLIT_OUT
//
// Description: 
// This structure represents Splitter ConOut devices linked list
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Link             DLINK                               Linked list pointer
// SimpleOut        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*    Protocol pointer
// Handle           EFI_HANDLE                          Device handle
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _CON_SPLIT_OUT
	{
		DLINK                           Link; //MUST BE THE FIRST FIELD
		EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*SimpleOut;
		EFI_HANDLE	                    Handle;
	} CON_SPLIT_OUT;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: CON_SPLIT_IN_KEY_NOTIFY
//
// Description: 
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
	DLINK                             Link; //MUST BE THE FIRST FIELD
	EFI_KEY_DATA                      KeyData;
	EFI_KEY_NOTIFY_FUNCTION           KeyNotificationFunction;
    DLIST		                      NotifyHandleList;
} CON_SPLIT_IN_KEY_NOTIFY;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: CON_SPLIT_IN_KEY_NOTIFY
//
// Description: 
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct {
	DLINK                             Link; //MUST BE THE FIRST FIELD
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *SimpleInEx;
	EFI_HANDLE	                      NotifyHandle;
} CON_SPLIT_IN_KEY_NOTIFY_HANDLE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: CON_SPLIT_IN
//
// Description: 
// This structure represents Splitter ConIn devices linked list
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Link             DLINK                               Linked list pointer
// SimpleIn         EFI_SIMPLE_TEXT_INPUT_PROTOCOL*     Protocol pointer
// SimpleInEx       EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*  Protocol pointer
// KeycodeInEx      AMI_EFIKEYCODE_PROTOCOL*            Protocol pointer
// Handle           EFI_HANDLE                          Device handle
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
	
typedef struct _CON_SPLIT_IN
	{
		DLINK                             Link; //MUST BE THE FIRST FIELD
		EFI_SIMPLE_TEXT_INPUT_PROTOCOL	  *SimpleIn;
		EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *SimpleInEx;
		AMI_EFIKEYCODE_PROTOCOL	          *KeycodeInEx;
		EFI_HANDLE	                      Handle;
	} CON_SPLIT_IN;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: CON_SPLIT
//
// Description: 
// This structure represents Splitter devices structure
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Input             CON_SPLIT_IN               Input devices linked list
// Output            CON_SPLIT_OUT              Output devices linked list
// StdErr            CON_SPLIT_OUT              Error output devices linked list
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
	
typedef struct _CON_SPLIT
	{
		CON_SPLIT_IN	Input;
		CON_SPLIT_OUT	Output;
		CON_SPLIT_OUT	StdErr;
	} CON_SPLIT;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: SUPPORT_RES
//
// Description: 
// This structure represents Splitter supported resolutions database
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Columns              INT32            Max number of text columns
// Rows                 INT32            Max number of text rows
// AllDevices           BOOLEAN          Flag if all devices support given resolution
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
		
typedef struct __SUPPORT_RES
	{
		INT32	Columns;
		INT32	Rows;
		BOOLEAN AllDevices;
	} SUPPORT_RES;

#pragma pack()

//-----------------------------------------------------------------------------------

SUPPORT_RES *SupportedModes;

//virtual splitter output buffer
CHAR16 *ScreenBuffer;
CHAR16 *EndOfTheScreen;
INT32  *AttributeBuffer;
INT32  Columns;

extern SIMPLE_TEXT_OUTPUT_MODE		     MasterMode;
extern EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	 mCSOutProtocol;
extern EFI_SIMPLE_TEXT_INPUT_PROTOCOL 	 mCSSimpleInProtocol;
extern EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL mCSSimpleInExProtocol;
extern AMI_EFIKEYCODE_PROTOCOL 	         mCSKeycodeInProtocol;
extern DLIST 		                     ConInList;
extern DLIST		                     ConOutList;
extern DLIST		                     ConPointerList;
extern DLIST		                     ConInKeyNotifyList;
extern BOOLEAN                           StdInLocked;
extern EFI_SIMPLE_POINTER_PROTOCOL       mCSSimplePointerProtocol;

//-----------------------------------------------------------------------------------

EFI_STATUS ConSplitterSimplePointerReset(
    IN  EFI_SIMPLE_POINTER_PROTOCOL *This,
    IN  BOOLEAN ExtendedVerification );

EFI_STATUS ConSplitterSimplePointerGetState(
    IN  EFI_SIMPLE_POINTER_PROTOCOL *This,
    IN OUT EFI_SIMPLE_POINTER_STATE *State );

VOID ConSplitterSimplePointerWaitForInput(
    IN  EFI_EVENT Event,
    IN  VOID *Context );

EFI_STATUS	CSSupported ( 
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath);

EFI_STATUS	CSStart ( 
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
	);

EFI_STATUS	CSStop ( 
	IN	EFI_DRIVER_BINDING_PROTOCOL	  *This,
	IN	EFI_HANDLE                    ControllerHandle,
	IN  UINTN						  NumberOfChildren,
	IN  EFI_HANDLE					  *ChildHandleBuffer
	);

EFI_STATUS CSReset( 
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN BOOLEAN                         ExtendedVerification
	);

EFI_STATUS CSOutputString( 
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN CHAR16                          *String	
    );

EFI_STATUS CSTestString( 
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN CHAR16                          *String
    );

EFI_STATUS CSQueryMode( 
    IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN  UINTN                           ModeNum,
    OUT UINTN                           *Col, 
    OUT UINTN                           *Row
    );

EFI_STATUS CSSetMode(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN UINTN                           ModeNum
    );

EFI_STATUS CSSetAttribute(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN UINTN                           Attribute
    );

EFI_STATUS CSClearScreen(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
    );

EFI_STATUS CSSetCursorPosition(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This, 
    IN UINTN                            Column, 
    IN UINTN                            Row
    );

EFI_STATUS CSEnableCursor(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This, 
    IN BOOLEAN                          Visible
    );

EFI_STATUS CSInReset( 
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, 
    IN BOOLEAN                        EV 
    );

EFI_STATUS CSReadKeyStroke (
    IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, 
    OUT EFI_INPUT_KEY                  *Key 
    );

VOID CSWaitForKey(
    IN EFI_EVENT Event, 
    IN VOID      *Context
    );

EFI_STATUS CSInResetEx( 
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This, 
    IN BOOLEAN                           EV 
    );

EFI_STATUS CSReadKeyStrokeEx (
    IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This, 
    OUT EFI_KEY_DATA                      *KeyData 
    );

EFI_STATUS
CSReadEfiKey (
    IN  AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA        *KeyData
    );

EFI_STATUS CSInSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE              *KeyToggleState
);

EFI_STATUS CSInRegisterKeyNotify(
    IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN  EFI_KEY_DATA                      *KeyData,
    IN  EFI_KEY_NOTIFY_FUNCTION           KeyNotificationFunction,
    OUT EFI_HANDLE                        *NotifyHandle
);

EFI_STATUS CSInUnRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE                        NotificationHandle
);

VOID RestoreTheScreen(
    IN EFI_HANDLE                       ControllerHandle, 
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *SimpleOut
    );

VOID SaveTheScreen(
    IN EFI_HANDLE                       ControllerHandle, 
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *SimpleOut
    );

EFI_STATUS MemClearScreen(
    VOID
    );

VOID SaveUgaMode(
    IN EFI_HANDLE ControllerHandle
    );

VOID RestoreUgaMode(
    IN EFI_HANDLE ControllerHandle
    );

EFI_STATUS InitModesTable(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN EFI_HANDLE                      Handle
    );

VOID UpdateModesTable(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN EFI_HANDLE                      Handle
    );

EFI_STATUS IsModeSupported(
    IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN  UINTN                           ModeNum, 
	OUT INT32                           *DeviceModeNumber
    );

EFI_STATUS ResizeSplitterBuffer(
    IN INT32 ModeNum
    );

VOID UpdateMasterMode(
    IN SIMPLE_TEXT_OUTPUT_MODE *Mode
    );

EFI_STATUS CSInKeyboardLayoutMap(
    IN OUT AMI_EFI_KEY_DATA *KeyData
    );

VOID AdjustSupportedModes(
    VOID
    );

EFI_STATUS KeyboardLayoutMap(
    IN      AMI_MULTI_LANG_SUPPORT_PROTOCOL *This,
    IN OUT  AMI_EFI_KEY_DATA                *KeyData
	);
#ifdef __cplusplus
}
#endif
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