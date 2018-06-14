//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/GC.c 1     11/21/12 4:07a Wesleychen $
//
// $Revision: 1 $
//
// $Date: 11/21/12 4:07a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/GC.c $
// 
// 1     11/21/12 4:07a Wesleychen
// Update rev.45 for EIP105534.
// 
// 45    11/14/12 5:57p Artems
// [TAG]  		EIP105534
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	system hangs during SCT execution
// [RootCause]  	Incorrect handling of FORM_FEED escape character in
// StringToImage function
// [Solution]  	Graphics console - added flag to ignore line breaks
// HiiFont - fixed multiline drawing logic
// [Files]  		Gc.c HiiFont.c HiiFontEx.c
// 
// 44    7/06/12 11:19a Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Removed unnecessary traces
// [Files]  		Gc.c
// 
// 43    7/06/12 11:11a Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Support for monitor native resolution
// [Files]  		GC.c, ConSplit.c, Out.c, Core_Dxe.sdl
// 
// 42    6/19/12 3:43p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	GC.c file gives build error
// [RootCause]  	incorrect pointer used
// [Solution]  	changed pointer
// [Files]  		gc.c
// 
// 41    6/19/12 10:36a Artems
// [TAG]  		EIP89430
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Cursor position wasn't 0:0 after call to SetMode
// [RootCause]  	When console SetMode involved changing of screen
// resolution
// screen was cleared by graphics driver, however cursol position wasn't
// reset
// [Solution]  	Added code to resent cursor position when changing screen
// resolution
// [Files]  		Gc.c
// 
// 40    5/21/12 10:46a Artems
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Added text mode for full screen in native resolution
// [Files]  		GC.c
// 
// 39    4/30/12 3:55p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Modified GraphicsConsole driver to output whole string
// instead of symbol-by-symbol output
// [Files]  		Gc.c, AmiDxeLib.h, EfiLib.c, UefiHiiUtils.c
// 
// 38    8/12/11 12:22p Artems
// EIP 64107: Added changes for module to be compliant with UEFI
// specification v 2.3.1
// 
// 37    8/12/11 11:54a Artems
// Bug fix: avoid using uninitialized data fields of GC_DATA structure
// 
// 36    4/12/10 3:25p Artems
// Fixed bug of drawing cursor when window position is undefined
// 
// 35    12/17/09 10:22a Artems
// EIP 29311 added automatic discovering of graphics mode for text mode 0
// 
// 34    12/03/09 3:13p Felixp
// TestString is implemented for UEFI 2.1 case.
// 
// 33    10/09/09 6:06p Felixp
// UEFI 2.1 - related changes (suppot Framework and UEFI HII).
// 
// 32    8/28/09 10:25a Felixp
// Component Name protocol implementation is upadted  to support both 
// ComponentName and ComponentName2 protocols
// (based on value of the EFI_SPECIFICATION_VERSION SDL token).
// 
// 31    7/10/09 6:26p Felixp
// 
// 30    7/08/09 5:01p Artems
// Added missing function headers
// 
// 29    5/22/09 7:27p Felixp
// 
// 27    10/19/07 9:19a Felixp
//  - Graphic Console driver is updated to support different graphical
// resolutions (used to be only 800 by 600).
//  - SDL tokens are added in CORE_DXE.sdl to customize list of text
// modes.
//  - SDL tokens are added in CORE_DXE.sdl to customize color values(EIP:
// 9854).
// 
// 26    4/13/07 2:45p Robert
// Updates for Coding Standard
// 
// 25    3/30/07 6:13p Felixp
// 
// 24    3/29/07 10:22a Felixp
// 
// 23    3/28/07 5:39p Artems
// Fixed errors reported by SCT test
// 
// 22    3/13/07 1:48p Artems
// Fixed bug in 100 x 31 mode
// 
// 21    3/13/07 10:42a Artems
// 
// 20    3/09/07 1:40p Artems
// Clear screen function changed to clear only affected part of screen,
// not 
// entire screen
// 
// 19    1/04/07 6:19p Artems
// 
// 18    12/20/06 10:38a Felixp
// Graphics Output Protocol support added
// 
// 17    8/24/06 10:11a Felixp
// x64 support: warning/error fixes
// 
// 16    8/04/06 4:07p Robert
// 
// 15    3/13/06 10:07a Felixp
// 
// 14    9/29/05 2:52p Robert
// Initialization of Global Variables
// 
// 13    7/22/05 11:29a Felixp
// enable cursor in reset function
// 
// 12    7/20/05 6:50p Felixp
// 
// 11    7/20/05 6:24p Robert
// Added check for trying to print a wide character at position 79.  This
// should produce a line feed instead
// 
// 10    7/20/05 5:31p Robert
// Data structure for temporary storage of cursor position was only big
// enough for narrow glyph not for wide glyph
// 
// 7     3/03/05 12:16p Felixp
// HII New protocol is default now
// 
// 6     2/25/05 11:27a Robert
// Cleared current p[osition buffer before clearing the screen and moving
// the cursor
// 
// 5     2/25/05 10:52a Robert
// Clear screen procedure would leave a block on the screen where the
// cursor was.
// We changed the order of the operation so that the cursor moved first
// and the screen was cleared afterward
// 
// 4     2/24/05 5:27p Felixp
// bug fix in DriverBindingStop (Cursor blinking timer was not getting
// stopped)
// 
// 3     2/07/05 4:04p Yakovlevs
// 
// 2     2/04/05 1:47p Felixp
// warning fixed
// 
// 1     1/28/05 12:45p Felixp
// 
// 3     1/06/05 11:22a Robert
// 
// 2     1/06/05 10:09a Robert
// Added Blinking Cursor support
// 
// 1     12/22/04 6:19p Admin
// 
// 1     12/22/04 6:18p Admin
// 
// 9     12/16/04 3:40p Felixp
// 
// 8     12/16/04 2:14p Robert
// Added TempBlt Buffer init for printing of default string.  was
// forgetting to re-init
// buffer pointer when doing a carriage return line feed
// 
// 7     12/16/04 11:39a Robert
// code optimization for color selection
// 
// 6     12/15/04 4:02p Robert
// added checks for memory allocation
// 
// 5     12/14/04 6:02p Robert
// added component name support
// 
// 4     12/14/04 5:28p Robert
// 
// 3     12/14/04 4:28p Robert
//
// 2     11/11/04 5:09p Robert
//
// 1     11/11/04 3:28p Robert
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  GC.h
//
// Description:  Graphics console driver that produces the Simple Text Out
//		interface
//
//<AMI_FHDR_END>
//**********************************************************************

//-----------------------------------------------------------------------------

#include <AmiDxeLib.h>
#include <Protocol/UgaDraw.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/HiiFont.h>
#include <Protocol/SimpleTextOut.h >
#include <Protocol/DevicePath.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/EdidActive.h>
#include <Token.h>

//-----------------------------------------------------------------------------

#define	GLYPH_HEIGHT		19
#define	NARROW_GLYPH_WIDTH	8
#define WIDE_GLYPH_WIDTH	16

#define MODE_ZERO_MIN_HOR_RES NARROW_GLYPH_WIDTH * 80
#define MODE_ZERO_MIN_VER_RES GLYPH_HEIGHT * 25

#define CURSOR_THICKNESS	3
#define CURSOR_OFFSET   	15      //base line of simple narrow font

#define	NULL_CHAR			0x0000
#define	BACKSPACE			0x0008
#define	LINE_FEED			0x000A
#define	FORM_FEED			0x000C
#define	CARRIAGE_RETURN		0x000D

//-----------------------------------------------------------------------------
// Data Structures

#pragma pack(1)

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: TEXT_MODE
//
// Description: 
// This structure represents text mode internal information structure
//
// Fields: Name          Type                    Description
//----------------------------------------------------------------------------
// ModeNum              INT32               Mode number
// Col                  INT32               Max number of columns
// Row                  INT32               Max number of rows
// VideoCol             UINT32              Horizontal screen resolution
// VideoRow             UINT32              Vertical screen resolution
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _TEXT_MODE  {
	INT32	ModeNum;
	INT32	Col;
	INT32	Row;
	UINT32	VideoCol; // horizontal pixels
	UINT32	VideoRow; // vertical pixels
} TEXT_MODE;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: GC_TEXT_MODE
//
// Description: 
// This structure represents text mode extended internal information structure
//
// Fields: Name          Type                    Description
//----------------------------------------------------------------------------
// ModeNum              INT32               Mode number
// Col                  INT32               Max number of columns
// Row                  INT32               Max number of rows
// VideoCol             UINT32              Horizontal screen resolution
// VideoRow             UINT32              Vertical screen resolution
// Supported            BOOLEAN             Flag if this mode supported
// GraphicsMode         UINT32              Correspondent graphics mode
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

typedef struct _GC_TEXT_MODE  {
	INT32	ModeNum;
	INT32	Col;
	INT32	Row;
	UINT32	VideoCol; // horizontal pixels
	UINT32	VideoRow; // vertical pixels
    BOOLEAN Supported;
    UINT32  GraphicsMode;
} GC_TEXT_MODE;

typedef struct _GC_DATA GC_DATA;

typedef VOID (* AGC_UPDATE_BLT_BUFFER ) (
	IN     GC_DATA 			             *This,
	IN     UINT32			             Width,
    IN     UINT32                        Height,
	IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer
	);

typedef VOID (* AGC_CLEAR_SCREEN) (
	IN OUT GC_DATA *This
	);

typedef VOID (* AGC_SCROLL_UP) (
	IN GC_DATA *This
	);

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: GC_DATA
//
// Description: 
// This structure represents internal information structure for Graphics console
// driver
//
// Fields: Name          Type                               Description
//----------------------------------------------------------------------------
// SimpleTextOut        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL     Protocol structure
// Signature            UINT32                              Unique signature
// GraphicsOutput       EFI_GRAPHICS_OUTPUT_PROTOCOL*       Pointer to Gop driver
// Hii                  EFI_HII_PROTOCOL*                   Pointer to HII driver
// SupportedModes       GC_TEXT_MODE*                       Pointer to supported modes array
// MaxRows              UINT32                              Max rows in current mode
// MaxColumns           UINT32                              Max columns in current mode
// DeltaX               UINT32                              Horizontal indent of text window on screen in pixels
// DeltaY               UINT32                              Vertical indent of text window on screen in  pixels
// Cursor               EFI_GRAPHICS_OUTPUT_BLT_PIXEL       Array for saving cursor image
// BlinkVisible         BOOLEAN                             Current state of cursor in blinking mode
// CursorEvent          EFI_EVENT                           Event generated to blink cursor
// OemUpdateBltBuffer   AGC_UPDATE_BLT_BUFFER               Custom porting hook
// OemClearScreen       AGC_CLEAR_SCREEN                    Custom porting hook
// OemScrollUp          AGC_SCROLL_UP                       Custom porting hook
// 
// Notes:  
//
// Referrals:
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>

struct _GC_DATA{
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	SimpleTextOut;
	UINT32				            Signature;			            //signature (must be 0x54445348 ('GRCS') )
    UINT32                          Version;
	EFI_GRAPHICS_OUTPUT_PROTOCOL	*GraphicsOutput;
	EFI_HII_FONT_PROTOCOL		    *HiiFont;
    GC_TEXT_MODE                    *SupportedModes;
    UINT32                          MaxRows;                        //max number of rows in current mode
    UINT32                          MaxColumns;                     //max number of columns in current mode
    UINT32                          DeltaX;                         //horizontal offset in pixels for current text mode
    UINT32                          DeltaY;                         //vertical offset in pixels for current text mode
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL   Cursor[NARROW_GLYPH_WIDTH * 3]; //Save cursor image
	BOOLEAN				            BlinkVisible;                   //if true cursor is visible, otherwise - invisible
	EFI_EVENT			            CursorEvent;
	AGC_UPDATE_BLT_BUFFER		    OemUpdateBltBuffer;		        //pointer to custom hook
	AGC_CLEAR_SCREEN		        OemClearScreen;		            //pointer to custom hook
	AGC_SCROLL_UP			        OemScrollUp;			        //pointer to custom hook
};
#pragma pack()

//-----------------------------------------------------------------------------
// Function Prototypes

EFI_STATUS	DriverBindingSupported ( 
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath);

EFI_STATUS	DriverBindingStart ( 
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath);

EFI_STATUS	DriverBindingStop ( 
	IN EFI_DRIVER_BINDING_PROTOCOL	*This,
	IN EFI_HANDLE			        ControllerHandle,
	IN  UINTN			            NumberOfChildren,
	IN  EFI_HANDLE			        *ChildHandleBuffer);

//******************** Simple Text Output protocol functions prototypes ***********

EFI_STATUS GCReset(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN BOOLEAN ExtendedVerification);

EFI_STATUS GCOutputString(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN CHAR16 *String);

EFI_STATUS GCTestString(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN CHAR16 *String);

EFI_STATUS GCQueryMode(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN UINTN ModeNum, 
    OUT UINTN *Col, 
    OUT UINTN *Row);

EFI_STATUS GCSetMode(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN UINTN ModeNum);

EFI_STATUS GCSetAttribute(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN UINTN Attribute);

EFI_STATUS GCClearScreen(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);

EFI_STATUS GCSetCursorPosition(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN UINTN Column, 
    IN UINTN Row);

EFI_STATUS GCEnableCursor(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, 
    IN BOOLEAN Visible);

//******************** Service functions prototypes ********************************

EFI_STATUS GetColorFromAttribute(
    IN UINT32 Attribute, 
    OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Foreground,
    OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Background);

EFI_STATUS GetGraphicsModeNumber (
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL	*GraphicsOutput, 
    IN UINT32                       HorRes,
    IN UINT32                       VerRes,
	OUT UINT32                      *ModeNum,
    IN  BOOLEAN                     ExactMatch,
    OUT UINT32                      *ActualHorRes OPTIONAL,
    OUT UINT32                      *ActualVerRes OPTIONAL );

EFI_STATUS SetupGraphicsDevice(
    IN GC_DATA *GcData);

VOID EFIAPI BlinkCursorEvent ( IN EFI_EVENT Event, IN VOID *Context );

VOID DrawCursor(
    IN GC_DATA *GcData,
    IN BOOLEAN Visible);

VOID ScrollUp(
    IN GC_DATA *GcData);

VOID SaveCursorImage(
    IN GC_DATA *GcData);

VOID ShiftCursor(
    IN GC_DATA *GcData,
    IN UINT16 Step);

VOID AddChar(
    IN GC_DATA *GcData,
    IN CHAR16 Char,
    IN UINT16 Width
);

VOID FlushString(
    IN GC_DATA *GcData
);

//********************** Hooks prototypes ******************************************

VOID GcUpdateBltBuffer (
	IN     GC_DATA 			             *This,			    //pointer to internal structure
	IN     UINT32			             Width,	            //width of the buffer in pixels
    IN     UINT32                        Height,            //height of the buffer in pixels
	IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer	        //pointer to BLT buffer to update
	);

VOID GcInternalClearScreen (
	IN OUT GC_DATA *This
	);

//-----------------------------------------------------------------------------
// Globals
extern const TEXT_MODE TextModeArray[];
extern const MaxTextMode;
extern const EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorArray[];
static CHAR16 *TextBuffer = NULL;
static UINT32 TextBufferSize;
static UINT32 Position;
static UINT32 StringWidth;
static EFI_HANDLE GopHandle;

//-----------------------------------------------------------------------------
// Protocol implementation
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	mGCProtocol	=
	{
	GCReset,
	GCOutputString,
	GCTestString,
	GCQueryMode,
	GCSetMode,
	GCSetAttribute,
	GCClearScreen,
	GCSetCursorPosition,
	GCEnableCursor,
	NULL
	};


//-----------------------------------------------------------------------------
// Driver Binding Protocol

EFI_DRIVER_BINDING_PROTOCOL gGraphicsConsoleDriverBindingProtocol = {
	DriverBindingSupported,
	DriverBindingStart,
	DriverBindingStop,
	0x10,
	NULL,
	NULL
	};


//-----------------------------------------------------------------------------
// Function Definitions
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
//Driver Name
static UINT16 *gDriverName=L"AMI Graphic Console Driver";

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:  GraphicsConsoleGetControllerName
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

static EFI_STATUS GraphicsConsoleGetControllerName (
		IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
		IN  EFI_HANDLE                   ControllerHandle,
 		IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
  		IN  CHAR8                        *Language,
  		OUT CHAR16                       **ControllerName
)
{
	return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:   GraphicsConsoleGetDriverName
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

static EFI_STATUS GraphicsConsoleGetDriverName(
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
static EFI_COMPONENT_NAME2_PROTOCOL gGraphicsConsole = {
  GraphicsConsoleGetDriverName,
  GraphicsConsoleGetControllerName,
  LANGUAGE_CODE_ENGLISH
};
#endif

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCEntryPoint
//
// Description:	
//  Installs gGraphicsConsoleDriverBindingProtocol protocol
//
// Input:
//	IN EFI_HANDLE ImageHandle - driver image handle
//	IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
// Output:
//	EFI_STATUS
//      EFI_SUCCESS - Driver binding protocol was installed
//
// Modified:
//
// Referrals: InitAmiLib InstallMultipleProtocolInterfaces
//
// Notes:
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS	GCEntryPoint (
	IN EFI_HANDLE           ImageHandle,
	IN EFI_SYSTEM_TABLE     *SystemTable
)
{
	EFI_STATUS	Status;

	InitAmiLib(ImageHandle, SystemTable);

	// initiaize the ImageHandle and DriverBindingHandle
	gGraphicsConsoleDriverBindingProtocol.DriverBindingHandle = NULL;
	gGraphicsConsoleDriverBindingProtocol.ImageHandle = ImageHandle;

	// Install driver binding protocol here
	Status = pBS->InstallMultipleProtocolInterfaces (
						&gGraphicsConsoleDriverBindingProtocol.DriverBindingHandle,
						&gEfiDriverBindingProtocolGuid, &gGraphicsConsoleDriverBindingProtocol,
#ifdef EFI_DEBUG
						&gEfiComponentName2ProtocolGuid, &gGraphicsConsole,
#endif
						NULL);

	return Status;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: DriverBindingSupported
//
// Description: 
//  Checks to see if this driver can be used
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to protocol instance
//	IN EFI_HANDLE Controller - handle of controller to install driver on
//	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath - pointer to device path
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - Driver supports the Device
//      EFI_NOT_SUPPORTED - Driver cannot support the Device 
//
// Notes:
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS	DriverBindingSupported (
	IN EFI_DRIVER_BINDING_PROTOCOL    *This,
	IN EFI_HANDLE                     ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
)
{
	EFI_STATUS                   Status;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput = NULL;
	EFI_HII_FONT_PROTOCOL		 *HiiFont;

	Status = pBS->OpenProtocol(
                        ControllerHandle, 
                        &gEfiGraphicsOutputProtocolGuid,
    	                &GraphicsOutput, 
                        This->DriverBindingHandle,
		                ControllerHandle, 
                        EFI_OPEN_PROTOCOL_BY_DRIVER);
	if (EFI_ERROR(Status))
        return Status;
    else
		pBS->CloseProtocol( 
                        ControllerHandle, 
                        &gEfiGraphicsOutputProtocolGuid,
					    This->DriverBindingHandle, 
                        ControllerHandle);

	Status = pBS->OpenProtocol(
                        ControllerHandle, 
                        &gEfiDevicePathProtocolGuid,
    	                NULL, 
                        This->DriverBindingHandle,
		                ControllerHandle, 
                        EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
	if (EFI_ERROR(Status)) 
        return Status;

	Status = pBS->LocateProtocol ( &gEfiHiiFontProtocolGuid, NULL, &HiiFont);

	return Status;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: DriverBindingStart
//
// Description: 
//  This function grabs needed protocols and initializes the supported text modes
//
// Input:
//	IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to protocol instance
//	IN EFI_HANDLE Controller - handle of controller to install driver on
//	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath - pointer to device path
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - SimpleTextOut Protocol installed
//      EFI_NOT_SUPPORTED - SimpleTextOut Protocol not installed
//
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS	DriverBindingStart (
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE                  ControllerHandle,
	IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
)
{
	EFI_STATUS Status;
    INT32 StartMode;

#if (CURSOR_BLINK_ENABLE != 0)
	EFI_STATUS			EventStatus;
#endif
	GC_DATA				*GcData = NULL;

	// Create private data structure and fill with proper data
	Status = pBS->AllocatePool(EfiBootServicesData, sizeof(GC_DATA), &GcData);
	if (EFI_ERROR(Status))
        return Status;

	pBS->CopyMem( &(GcData->SimpleTextOut), 
                  &mGCProtocol, 
				  sizeof(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL) );

	Status = pBS->AllocatePool(EfiBootServicesData, 
                               sizeof(SIMPLE_TEXT_OUTPUT_MODE), 
                               &(GcData->SimpleTextOut.Mode));
    if(EFI_ERROR(Status))
    {
        pBS->FreePool(GcData);
        return Status;
    }

	Status = pBS->AllocatePool(EfiBootServicesData, 
                               sizeof(GC_TEXT_MODE) * MaxTextMode, 
                               &(GcData->SupportedModes));
    if(EFI_ERROR(Status))
    {
        pBS->FreePool(GcData->SimpleTextOut.Mode);
        pBS->FreePool(GcData);
        return Status;
    }

	Status = pBS->OpenProtocol( 
                            ControllerHandle, 
                            &gEfiGraphicsOutputProtocolGuid,
					        &(GcData->GraphicsOutput), 
                            This->DriverBindingHandle,
					        ControllerHandle, 
                            EFI_OPEN_PROTOCOL_BY_DRIVER );
	if (EFI_ERROR(Status))
    {
        pBS->FreePool(GcData->SupportedModes);
        pBS->FreePool(GcData->SimpleTextOut.Mode);
        pBS->FreePool(GcData);
		return Status;
    }

	// Find the Hii Protocol and attach it to the datastructure
	Status = pBS->LocateProtocol ( &gEfiHiiFontProtocolGuid, NULL, &(GcData->HiiFont));

	if (EFI_ERROR(Status))
	{
		pBS->CloseProtocol( 
                        ControllerHandle, 
                        &gEfiGraphicsOutputProtocolGuid,
					    This->DriverBindingHandle, 
                        ControllerHandle);
        pBS->FreePool(GcData->SupportedModes);
        pBS->FreePool(GcData->SimpleTextOut.Mode);
        pBS->FreePool(GcData);
		return EFI_UNSUPPORTED;
	}

    GopHandle = ControllerHandle;
    Status = SetupGraphicsDevice(GcData);
    if(EFI_ERROR(Status))
	{
		pBS->CloseProtocol( 
                        ControllerHandle, 
                        &gEfiGraphicsOutputProtocolGuid,
					    This->DriverBindingHandle, 
                        ControllerHandle);
        pBS->FreePool(GcData->SupportedModes);
        pBS->FreePool(GcData->SimpleTextOut.Mode);
        pBS->FreePool(GcData);
		return EFI_UNSUPPORTED;
	}	

    //initialize porting hooks and signature
    GcData->Signature = 0x54445348;
    GcData->Version = 1;
    GcData->OemUpdateBltBuffer = GcUpdateBltBuffer;
    GcData->OemClearScreen = GcInternalClearScreen;
    GcData->OemScrollUp = NULL;
    GcData->DeltaX = 0;
    GcData->DeltaY = 0;
    GcData->MaxColumns = 0;
    GcData->MaxRows = 0;

	// Default the cursor blink to the show cursor state
	GcData->BlinkVisible = TRUE;


   (GcData->SimpleTextOut.Mode)->CursorVisible = FALSE;    //since initial position of window is undefined we cannot draw cursor yet
    Status = GCSetAttribute(&(GcData->SimpleTextOut), EFI_BACKGROUND_BLACK | EFI_WHITE);  //set default attributes
    StartMode = ((GcData->SimpleTextOut.Mode)->MaxMode > 3 && START_IN_NATIVE_RESOLUTION) ? 3 : 0;
    Status = GCSetMode(&(GcData->SimpleTextOut), StartMode);
    Status = GCEnableCursor(&(GcData->SimpleTextOut), TRUE);    //enable cursor

	// install the simple text out protocol
	Status = pBS->InstallMultipleProtocolInterfaces ( 
                    &ControllerHandle,            
                    &gEfiSimpleTextOutProtocolGuid, 
                    &GcData->SimpleTextOut,
                    NULL);
	
	if (EFI_ERROR(Status))
	{
		// close protocols and free allocated memory
		pBS->CloseProtocol( 
                        ControllerHandle, 
                        &gEfiGraphicsOutputProtocolGuid,
					    This->DriverBindingHandle, 
                        ControllerHandle);

        pBS->FreePool(GcData->SupportedModes);
        pBS->FreePool(GcData->SimpleTextOut.Mode);
		pBS->FreePool(GcData);
        return EFI_UNSUPPORTED;
    }

#if (CURSOR_BLINK_ENABLE != 0)
	EventStatus = pBS->CreateEvent (
                    EVT_TIMER | EVT_NOTIFY_SIGNAL,
					TPL_NOTIFY,
					BlinkCursorEvent,
					&(GcData->SimpleTextOut),
					&(GcData->CursorEvent)
					);
	if (!EFI_ERROR(EventStatus))
	{
		pBS->SetTimer(GcData->CursorEvent, TimerPeriodic, 5000000);
	}
#endif
	
	return Status;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: DriverBindingStop
//
// Description: 
//  Uninstalls the driver from given ControllerHandle
//
// Input:
//  IN EFI_DRIVER_BINDING_PROTOCOL *This - pointer to protocol instance
//  IN EFI_HANDLE ControllerHandle - controller handle to uninstall driver from
//  IN UINTN NumberOfChildren - number of children supported by this driver
//  IN EFI_HANDLE *ChildHandleBuffer  - pointer to child handles buffer
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS	- driver uninstalled from controller
//      EFI_NOT_STARTED - driver was not started
//		
// Notes:
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS	DriverBindingStop ( 
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
	IN EFI_HANDLE                  ControllerHandle,
	IN UINTN                       NumberOfChildren,
	IN EFI_HANDLE                  *ChildHandleBuffer
)
{
	EFI_STATUS						Status;
	GC_DATA							*GcData = NULL;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*SimpleTextOut = NULL;

	Status = pBS->OpenProtocol (
                            ControllerHandle, 
                            &gEfiSimpleTextOutProtocolGuid, 
					        &SimpleTextOut, 
                            This->DriverBindingHandle, 
					        ControllerHandle, 
                            EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	if (EFI_ERROR (Status))
		return EFI_NOT_STARTED;

	Status = pBS->CloseProtocol (
                            ControllerHandle, 
                            &gEfiSimpleTextOutProtocolGuid, 
					        This->DriverBindingHandle, 
                            ControllerHandle);

	GcData = (GC_DATA *) SimpleTextOut;	

	// uninstall the simple text out protocol
	Status = pBS->UninstallMultipleProtocolInterfaces ( 
                            ControllerHandle,            
                            &gEfiSimpleTextOutProtocolGuid, 
                            &GcData->SimpleTextOut,
                            NULL);
	if (EFI_ERROR (Status))
		return Status;

#if (CURSOR_BLINK_ENABLE != 0)
	pBS->SetTimer(GcData->CursorEvent, TimerCancel, 0);
	pBS->CloseEvent(GcData->CursorEvent);
#endif

	Status = pBS->CloseProtocol( 
                            ControllerHandle, 
                            &gEfiGraphicsOutputProtocolGuid,
						    This->DriverBindingHandle, 
                            ControllerHandle);

    pBS->FreePool(GcData->SupportedModes);
    pBS->FreePool(GcData->SimpleTextOut.Mode);
    pBS->FreePool(GcData);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCReset
//
// Description: 
//  Resets the text output device
//
// Input:
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//	IN BOOLEAN ExtendedVerification - indicates that the driver should preform more
//			exhausted verification of the device during reset
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS	- device reset properly
//	    EFI_DEVICE_ERROR - Device is not functioning properly
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  GCReset(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN                         ExtendedVerification
)
{
	// Set mode clears the screen and sets the cursor back to (0,0) So before 
	//	we do that, set the Attribute colors to default
	This->SetAttribute(This, EFI_BACKGROUND_BLACK | EFI_WHITE);
//    This->SetMode(This, 0);
    This->ClearScreen(This);
	This->EnableCursor(This, TRUE);
	return	EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCOutputString
//
// Description: 
//  Writes a string to the output device and advances the cursor 
//	as necessary.
//
// Input:
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//	IN CHAR16 *String - pointer to string to be displayed to the screen
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS	- device reset properly
//	    EFI_DEVICE_ERROR - Device reported an Error while outputting a string
//	    EFI_UNSUPPORTED - The output device's mode is not currently in a defined state
//	    EFI_WARN_UNKNOWN_GLYPH - This warning code indicates that some of the 
//          characters in the unicode string could not be rendered and were skipped
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GCOutputString(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16                          *String
)
{
	EFI_STATUS		      Status;
	GC_DATA			      *GcData;
    BOOLEAN               UnknownGlyph = FALSE;
    BOOLEAN               CursorVisible;
    EFI_FONT_DISPLAY_INFO FontInfo;
    EFI_IMAGE_OUTPUT      *Glyph = NULL;
    UINT16                GlyphWidth;
	
	// find private data structure	
	GcData = (GC_DATA *) This;	

    CursorVisible = (GcData->SimpleTextOut.Mode)->CursorVisible;
	if (CursorVisible)    
        This->EnableCursor(This, FALSE);
	
	// now loop through the string and display it to the output device
	while (*String != 0)
	{
		switch (*String)
		{
			case CARRIAGE_RETURN:
                FlushString(GcData);
                This->SetCursorPosition(
                                    This, 
                                    0, 
                                    (GcData->SimpleTextOut.Mode)->CursorRow);
				break;

			case LINE_FEED:
			case FORM_FEED:
                FlushString(GcData);
                if((GcData->SimpleTextOut.Mode)->CursorRow == (GcData->MaxRows - 1))
                {
                    ScrollUp(GcData);
                    //cursor position not changed, but image under it does - save new image
                    SaveCursorImage(GcData);
                }
                else
                    This->SetCursorPosition(
                                    This, 
                                    (GcData->SimpleTextOut.Mode)->CursorColumn, 
                                    (GcData->SimpleTextOut.Mode)->CursorRow + 1);
				break;
			
			case BACKSPACE:
                FlushString(GcData);
                if((GcData->SimpleTextOut.Mode)->CursorColumn != 0)
                    This->SetCursorPosition(
                                    This, 
                                    (GcData->SimpleTextOut.Mode)->CursorColumn - 1, 
                                    (GcData->SimpleTextOut.Mode)->CursorRow);
				break;
			
			default:
                Status = HiiLibGetGlyphWidth(*String, &GlyphWidth);
                if(Status == EFI_UNSUPPORTED) {
                    Status = GcData->HiiFont->GetGlyph(
                                                GcData->HiiFont,
                                                *String,
                                                &FontInfo,
                                                &Glyph,
                                                0);
                    if(EFI_ERROR(Status))
                        return Status;
                    GlyphWidth = Glyph->Width;
                }

                if(Status == EFI_WARN_UNKNOWN_GLYPH)
                    UnknownGlyph = TRUE;

                AddChar(GcData, *String, GlyphWidth / 8);

                if(Glyph != NULL) {
                    pBS->FreePool(Glyph->Image.Bitmap);
                    pBS->FreePool(Glyph);
                    Glyph = NULL; 
                }

				break; // end of default case
		}

		String++;
	}
    FlushString(GcData);
	if (CursorVisible)    
        This->EnableCursor(This, TRUE);

	return (UnknownGlyph) ? EFI_WARN_UNKNOWN_GLYPH : EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCTestString
//
// Description: 
//  Tests to see if the String has the glyphs that correspond to
//	each character in the string
//
// Input: 
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//	IN CHAR16 *String - pointer to a string that needs to be tested
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - all characters can be drawn
//	    EFI_UNSUPPORTED - there are characters that cannot be drawn
//		
// Notes:
//	Uses the HII function TestString
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  GCTestString(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16                          *String
)
{
	GC_DATA		*GcData;
    EFI_STATUS  Status;
    EFI_IMAGE_OUTPUT *Glyph = NULL;
	
	// find private data structure	
	GcData = (GC_DATA *) This;	
	
	// now loop through the string and display it to the output device
	while (*String != 0)
	{
		switch (*String)
		{
			case CARRIAGE_RETURN: case LINE_FEED: case BACKSPACE:
				break;
			default:
                Status = GcData->HiiFont->GetGlyph(
                                                GcData->HiiFont,
                                                *String,
                                                NULL,
                                                &Glyph,
                                                0);
                if(EFI_ERROR(Status))
                    return Status;

                pBS->FreePool(Glyph->Image.Bitmap);
                pBS->FreePool(Glyph);
                if(Status == EFI_WARN_UNKNOWN_GLYPH)
                    return EFI_UNSUPPORTED;
                Glyph = NULL; 
				break;
		}
		String++;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCQueryMode
//
// Description: 
//  Returns information for an available text mode that the output
//	device supports
//
// Input: 
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//	IN UINTN ModeNum - The mode to return information on
//	OUT UINTN *Col - the number of columns supported
//	OUT UINTN *Row - the number of rows supported
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS	- device reset properly
//	    EFI_DEVICE_ERROR - Device reported an Error while outputting a string
//	    EFI_UNSUPPORTED - The ModeNumber is not supported
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GCQueryMode(
	IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN  UINTN                           ModeNum,
	OUT UINTN                           *Col,
	OUT UINTN                           *Row
)
{
	GC_DATA		*GcData;
    UINT32      i = 0;
	
	GcData = (GC_DATA *) This;	

    if(ModeNum >= (UINTN)(GcData->SimpleTextOut.Mode)->MaxMode)
        return EFI_UNSUPPORTED;

    while(GcData->SupportedModes[i].ModeNum != ModeNum)
        i++;

    if(!GcData->SupportedModes[i].Supported)
        return EFI_UNSUPPORTED;

	// if the mode is a valid mode, return the data from the array of
	//	for the height and width
	*Col = GcData->SupportedModes[i].Col;
	*Row = GcData->SupportedModes[i].Row;
	
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCSetMode
//
// Description: 
//  Sets the text mode to the requested mode.  It checks to see if
//	it is a valid mode
//
// Input: 
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//	IN UINTN ModeNum - mode number to change to
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - the new mode is valid and has been set
//	    EFI_UNSUPPORTED - the new mode is not valid
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GCSetMode(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           ModeNum
)
{
	EFI_STATUS	Status;
	GC_DATA		*GcData;
    BOOLEAN     CursorVisible;
    UINT32      i = 0;
    UINT32      DeltaX, DeltaY;
    UINT32      SaveX, SaveY;

	GcData = (GC_DATA *) This;	

    if(ModeNum >= (UINTN)(GcData->SimpleTextOut.Mode)->MaxMode)
        return EFI_UNSUPPORTED;

    while(GcData->SupportedModes[i].ModeNum != ModeNum)
        i++;

    if(!GcData->SupportedModes[i].Supported)
        return EFI_UNSUPPORTED;

    SaveX = GcData->DeltaX;
    SaveY = GcData->DeltaY;

    DeltaX = (GcData->SupportedModes[i].VideoCol - 
              GcData->SupportedModes[i].Col * NARROW_GLYPH_WIDTH) / 2;
    DeltaY = (GcData->SupportedModes[i].VideoRow - 
              GcData->SupportedModes[i].Row * GLYPH_HEIGHT) / 2;

    //save cursor status and hide it if nesessary
    CursorVisible = (GcData->SimpleTextOut.Mode)->CursorVisible;
	if (CursorVisible)
		This->EnableCursor(This, FALSE);

    if(GcData->GraphicsOutput->Mode->Mode != GcData->SupportedModes[i].GraphicsMode)
    {
        Status = GcData->GraphicsOutput->SetMode(GcData->GraphicsOutput,
                                                 GcData->SupportedModes[i].GraphicsMode);
        if(EFI_ERROR(Status))
            return Status;

        if(GcData->OemClearScreen != GcInternalClearScreen) { //we have porting hook installed - call it
            This->ClearScreen(This);
        } else {
        /* the screen is cleared by graphics driver when changed graphics mode
           we just need to reset cursor position */
            This->Mode->CursorColumn = 0;
	        This->Mode->CursorRow = 0;
        }
    }
    else
        This->ClearScreen(This);    //call clear screen with old values

    if(GcData->DeltaX == SaveX && GcData->DeltaY == SaveY)
    {                               //initial position was not changed by porting hook inside C
                                    //ClearScreen function
        GcData->DeltaX = DeltaX;
        GcData->DeltaY = DeltaY;
    }

    GcData->MaxColumns = GcData->SupportedModes[i].Col;
    GcData->MaxRows = GcData->SupportedModes[i].Row;
    (GcData->SimpleTextOut.Mode)->Mode = GcData->SupportedModes[i].ModeNum;

	//  restore cursor at new position
	if (CursorVisible)
		This->EnableCursor(This, TRUE);

    if(TextBuffer == NULL || TextBufferSize < GcData->MaxColumns) {
        if(TextBuffer)
            pBS->FreePool(TextBuffer);

        Status = pBS->AllocatePool(EfiBootServicesData, (GcData->MaxColumns + 1) * sizeof(CHAR16), &TextBuffer);
        if(EFI_ERROR(Status))
            return Status;

        TextBufferSize = GcData->MaxColumns + 1;    //additional space for null-terminator
        Position = 0;
        StringWidth = 0;
    }

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCSetAttribute
//
// Description: 
//  Sets the foreground color and background color for the screen
//
// Input: 
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//	IN UINTN Attribute - the attributes to set
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - the attribute was changed successfully
//	    EFI_DEVICE_ERROR - The device had an error
//	    EFI_UNSUPPORTED - The attribute is not supported
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  GCSetAttribute(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           Attribute
)
{
	GC_DATA	*GcData;
	
	GcData = (GC_DATA *) This;
	
	(GcData->SimpleTextOut.Mode)->Attribute = (INT32) Attribute;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCClearScreen
//
// Description: 
//  Clears the text screen
//
// Input: 
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - the screen was cleared
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  GCClearScreen(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
)
{
	GC_DATA			              *GcData;

	GcData = (GC_DATA *) This;

    GcData->OemClearScreen(GcData);

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCSetCursorPosition
//
// Description: 
//  This function sets the position of the cursor
//
// Input: 
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//	IN UINTN Column - the new column
//	IN UINTN Row - The new row
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - the cursor position was changed
//	    EFI_DEVICE_ERROR - The device had an error
//	    EFI_UNSUPPORTED - The device is not in a valid text mode or the 
//	                      cursor position is not valid
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GCSetCursorPosition(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           Column,
	IN UINTN                           Row
)
{
	GC_DATA	*GcData;
    BOOLEAN CursorVisible;
	
	GcData = (GC_DATA *) This;
	
	// check for a valid text mode and check for a valid position 
	//	on the screen
	
	if ( ((UINT32)Column >= GcData->MaxColumns) || 
		 ((UINT32)Row >= GcData->MaxRows) )
		return EFI_UNSUPPORTED;
		
	
    //save cursor status and hide it if nesessary
    CursorVisible = (GcData->SimpleTextOut.Mode)->CursorVisible;
	if (CursorVisible)
		This->EnableCursor(This, FALSE);
	
	(GcData->SimpleTextOut.Mode)->CursorColumn = (INT32)Column;
	(GcData->SimpleTextOut.Mode)->CursorRow = (INT32)Row;

	
	//  restore cursor at new position
	if (CursorVisible)
		This->EnableCursor(This, TRUE);
	
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GCEnableCursor
//
// Description: 
//  Makes cursor invisible or visible
//
// Input: 
//	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This - pointer to the protocol instance
//	IN BOOLEAN Visible - a boolean that if TRUE the cursor will be visible
//	if FALSE the cursor will be invisible
//
// Output:
//  EFI_STATUS
//	    EFI_SUCCESS - the cursor visibility was set correctly
//	    EFI_DEVICE_ERROR - The device had an error
//	    EFI_UNSUPPORTED - The device does not support visibilty control
//	                      for the cursor
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  GCEnableCursor(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN                         Visible
)
{
	GC_DATA	*GcData;
	
	GcData = (GC_DATA *) This;

	// check to see if the we are already set to the same cursor visibility mode
	if (Visible != (GcData->SimpleTextOut.Mode)->CursorVisible)
	{
		(GcData->SimpleTextOut.Mode)->CursorVisible = Visible;
//if we put cursor back we have to update image under it in order it contains older data
        if(Visible)
            SaveCursorImage(GcData);

		DrawCursor(GcData, Visible);
	}
	
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GetColorFromAttribute
//
// Description: 
//  Turns color attributes into Pixel values
//
// Input: 
//	IN  UINT32 Attribute - The color to set
//	OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Foreground - foreground color
//	OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Background - background color
//
// Output:
//  EFI_STATUS
//      EFI_SUCCESS - valid colors returned
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetColorFromAttribute(
    IN  UINT32                         Attribute, 
    OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Foreground, 
    OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Background
)
{
	UINT8 IndexF;
	UINT8 IndexB;

	if ((Attribute & 0x80) != 0)
			return EFI_UNSUPPORTED;

    IndexF = (UINT8)(Attribute & 0x0f);
    IndexB = (UINT8)((Attribute >> 4) & 0x0f);

	*Foreground = ColorArray[IndexF];
	*Background = ColorArray[IndexB];

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: DrawCursor
//
// Description: 
//  This function draws /hides the cursor in the current cursor position
//
// Input: 
//	IN GC_DATA * GcData - Private data structure for SimpleTextOut interface
//  IN BOOLEAN Visible - if TRUE - draws cursor, if FALSE - hides cursor
//
// Output:
//  VOID
//
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DrawCursor(
    IN GC_DATA *GcData, 
    IN BOOLEAN Visible
)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Fill;

    if(Visible)
    {
        Fill = ColorArray[((GcData->SimpleTextOut.Mode)->Attribute & 0x0f)];    //get foreground color
        GcData->GraphicsOutput->Blt(
            GcData->GraphicsOutput,
            &Fill,
            EfiBltVideoFill,
            0,
            0,                   
            GcData->DeltaX + (GcData->SimpleTextOut.Mode)->CursorColumn * NARROW_GLYPH_WIDTH,
            GcData->DeltaY + (GcData->SimpleTextOut.Mode)->CursorRow * GLYPH_HEIGHT + CURSOR_OFFSET,
            NARROW_GLYPH_WIDTH,
            CURSOR_THICKNESS,
            0); 
    }
    else
    {
        GcData->GraphicsOutput->Blt(
            GcData->GraphicsOutput,
            GcData->Cursor,
            EfiBltBufferToVideo,
            0,
            0,                   
            GcData->DeltaX + (GcData->SimpleTextOut.Mode)->CursorColumn * NARROW_GLYPH_WIDTH,
            GcData->DeltaY + (GcData->SimpleTextOut.Mode)->CursorRow * GLYPH_HEIGHT + CURSOR_OFFSET,
            NARROW_GLYPH_WIDTH,
            CURSOR_THICKNESS,
            NARROW_GLYPH_WIDTH * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)); 
    }                                   
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: BlinkCursorEvent
//
// Description: 
//  This is the function that makes the cursor blink. A timer event 
//	is created that will cause this function to be called
//
// Input: 
//	IN EFI_EVENT Event - event that was triggered
//  IN VOID *Context - pointer to the event context
//
// Output:
//  VOID
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID EFIAPI BlinkCursorEvent(
	IN EFI_EVENT Event,
	IN VOID      *Context
)
{
	GC_DATA	*GcData;
	
	GcData = (GC_DATA *) Context;

	if (!(GcData->SimpleTextOut.Mode)->CursorVisible)
		return;

	if (GcData->BlinkVisible)
	{
		// remove the cursor from the screen
		DrawCursor(GcData, FALSE);
        GcData->BlinkVisible = FALSE;
	}
	else		
	{
		// put cursor back
		DrawCursor(GcData, TRUE);
        GcData->BlinkVisible = TRUE;
	}
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: GetGraphicsModeNumber
//
// Description: 
//  This function returns graphics mode number, correspondend with given
//  horizontal and vertical resolution
//
// Input: 
//	IN EFI_GRAPHICS_OUTPUT_PROTOCOL	*GraphicsOutput - pointer to Gop driver
//  IN UINT32 HorRes - required horizontal resolution
//  IN UINT32 VerRes - required vertical resolution
//  OUT UINT32 *ModeNum - returned graphics mode number
//      
// Output: 
//  EFI_STATUS
//      EFI_SUCCESS - correct mode number returned
//      EFI_NOT_FOUND - mode number not found for given resolution
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetGraphicsModeNumber (
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput, 
    IN  UINT32                       HorRes,
    IN  UINT32                       VerRes,
	OUT UINT32                       *ModeNum,
    IN  BOOLEAN                      ExactMatch,
    OUT UINT32                       *ActualHorRes OPTIONAL,
    OUT UINT32                       *ActualVerRes OPTIONAL
)
{
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION	Info;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION	*pInfo = &Info;
	EFI_STATUS				                Status;
	UINTN							        SizeOfInfo;
	UINT32							        i;

	for(i = 0; i < GraphicsOutput->Mode->MaxMode; i++) {
		Status = GraphicsOutput->QueryMode(GraphicsOutput, i, &SizeOfInfo, &pInfo);

		if (!EFI_ERROR(Status)) { 
            if (ExactMatch && pInfo->HorizontalResolution == HorRes && pInfo->VerticalResolution == VerRes ) {
			    *ModeNum = i;
                return Status;
            }
            if(!ExactMatch && pInfo->HorizontalResolution >= HorRes && pInfo->VerticalResolution >= VerRes ) {
                *ModeNum = i;
                *ActualHorRes = pInfo->HorizontalResolution;
                *ActualVerRes = pInfo->VerticalResolution;
                return Status;
            }
		}
	}
    return EFI_NOT_FOUND;
}

EFI_STATUS GetNativeResolution (
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput,
	OUT UINT32                       *ModeNum,
    OUT UINT32                       *ActualHorRes,
    OUT UINT32                       *ActualVerRes
)
{
    EFI_STATUS Status;
    EFI_EDID_ACTIVE_PROTOCOL *EdidActive;
    UINT32 HorRes;
    UINT32 VerRes;

    Status = pBS->HandleProtocol(GopHandle, &gEfiEdidActiveProtocolGuid, &EdidActive);
    if(EFI_ERROR(Status) || EdidActive->SizeOfEdid == 0)
        return EFI_UNSUPPORTED;

    if(!((EdidActive->Edid)[24] & BIT01))
    /* native resolution not supported */
        return EFI_UNSUPPORTED;

    HorRes = ((((EdidActive->Edid)[0x36 + 4]) & 0xF0) << 4) + (EdidActive->Edid)[0x36 + 2];
    VerRes = ((((EdidActive->Edid)[0x36 + 7]) & 0xF0) << 4) + (EdidActive->Edid)[0x36 + 5];

    Status = GetGraphicsModeNumber(GraphicsOutput, HorRes, VerRes, ModeNum, TRUE, NULL, NULL);
    if(!EFI_ERROR(Status)) {
        *ActualHorRes = HorRes;
        *ActualVerRes = VerRes;
    }
    return Status;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: SetupGraphicsDevice
//
// Description: 
//  This function fills array of supported text modes
//
// Input: 
//	IN GC_DATA *Data - pointer to private protocol data structure
//      
// Output: 
//  EFI_STATUS
//      EFI_SUCCESS - function executed successfully
//      EFI_UNSUPPORTED - no supported modes found
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetupGraphicsDevice(
    IN GC_DATA *GcData
)
{
    EFI_STATUS Status;
    INT32 i;
    UINT32 GraphicsModeNumber;
    INT32 MaxSupportedModes = 1;
    BOOLEAN DefaultModeNotSupported = FALSE;
    INT32 ModeZeroIndex;
    UINT32 HorRes;
    UINT32 VerRes;

    for(i = 0; i < MaxTextMode; i++) {
        HorRes = TextModeArray[i].VideoCol;
        VerRes = TextModeArray[i].VideoRow;
        if(HorRes == 0 && VerRes == 0) {
            Status = GetNativeResolution(GcData->GraphicsOutput, &GraphicsModeNumber, &HorRes, &VerRes);
        } else {
        /* get mode number with exact resolution */
            Status = GetGraphicsModeNumber(GcData->GraphicsOutput,
                                            HorRes,
                                            VerRes,
                                            &GraphicsModeNumber,
                                            TRUE, NULL, NULL);
        }

        if(!EFI_ERROR(Status)) {
            GcData->SupportedModes[i].Supported = TRUE;
            GcData->SupportedModes[i].GraphicsMode = GraphicsModeNumber;
            GcData->SupportedModes[i].ModeNum = TextModeArray[i].ModeNum;

            if(TextModeArray[i].Col == 0)
                GcData->SupportedModes[i].Col = HorRes / NARROW_GLYPH_WIDTH;
            else
                GcData->SupportedModes[i].Col = TextModeArray[i].Col;

            if(TextModeArray[i].Row == 0)
                GcData->SupportedModes[i].Row = VerRes / GLYPH_HEIGHT;
            else
                GcData->SupportedModes[i].Row = TextModeArray[i].Row;

            GcData->SupportedModes[i].VideoCol = HorRes;
            GcData->SupportedModes[i].VideoRow = VerRes;

            MaxSupportedModes = (TextModeArray[i].ModeNum >= MaxSupportedModes) ? 
                                 TextModeArray[i].ModeNum + 1 : MaxSupportedModes;
        } else {
            GcData->SupportedModes[i].Supported = FALSE;
            GcData->SupportedModes[i].ModeNum = TextModeArray[i].ModeNum;

            if(TextModeArray[i].ModeNum == 0) {
                ModeZeroIndex = i;
                DefaultModeNotSupported = TRUE;
            }
        }
    }

    if(DefaultModeNotSupported) {
        Status = GetGraphicsModeNumber(GcData->GraphicsOutput,
                                       MODE_ZERO_MIN_HOR_RES,
                                       MODE_ZERO_MIN_VER_RES,
                                       &GraphicsModeNumber,
                                       FALSE,
                                       &(GcData->SupportedModes[ModeZeroIndex].VideoCol),
                                       &(GcData->SupportedModes[ModeZeroIndex].VideoRow));
        if(EFI_ERROR(Status)) {
            (GcData->SimpleTextOut.Mode)->MaxMode = 0;
            return EFI_UNSUPPORTED;
        }

        GcData->SupportedModes[ModeZeroIndex].Supported = TRUE;
        GcData->SupportedModes[ModeZeroIndex].GraphicsMode = GraphicsModeNumber;
        GcData->SupportedModes[ModeZeroIndex].Row = 25;
        GcData->SupportedModes[ModeZeroIndex].Col = 80;
    }

    (GcData->SimpleTextOut.Mode)->MaxMode = MaxSupportedModes;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: ScrollUp
//
// Description: 
//  This function scrolls screen one row up and clears bottom row
//
// Input:       
//  IN GC_DATA *GcData - pointer to private protocol data structure
//      
// Output:      
//  VOID
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ScrollUp(
    IN GC_DATA *GcData
)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Fill;

    GcData->GraphicsOutput->Blt(GcData->GraphicsOutput,
                                &Fill,
                                EfiBltVideoToVideo,
                                GcData->DeltaX,
                                GcData->DeltaY + GLYPH_HEIGHT,                   
                                GcData->DeltaX,
                                GcData->DeltaY,
                                GcData->MaxColumns * NARROW_GLYPH_WIDTH,
                                (GcData->MaxRows - 1) * GLYPH_HEIGHT,
                                0);
//clear bottom line
    Fill = ColorArray[(((GcData->SimpleTextOut.Mode)->Attribute >> 4) & 0xf)];
    GcData->GraphicsOutput->Blt(GcData->GraphicsOutput,
                                &Fill,
                                EfiBltVideoFill,
                                0,
                                0,                   
                                GcData->DeltaX,
                                GcData->DeltaY + (GcData->MaxRows - 1) * GLYPH_HEIGHT,
                                GcData->MaxColumns * NARROW_GLYPH_WIDTH,
                                GLYPH_HEIGHT,
                                0);
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name:    SaveCursorImage
//
// Description: 
//  This function saves image under cursor to restore, when cursor moves
//
// Input:       
//  IN GC_DATA *GcData - pointer to private protocol data structure
//      
// Output:      
//  VOID
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SaveCursorImage(
    IN GC_DATA *GcData
)
{
    GcData->GraphicsOutput->Blt(
            GcData->GraphicsOutput,
            GcData->Cursor,
            EfiBltVideoToBltBuffer,
            GcData->DeltaX + (GcData->SimpleTextOut.Mode)->CursorColumn * NARROW_GLYPH_WIDTH,
            GcData->DeltaY + (GcData->SimpleTextOut.Mode)->CursorRow * GLYPH_HEIGHT + CURSOR_OFFSET,
            0,
            0,                   
            NARROW_GLYPH_WIDTH,
            CURSOR_THICKNESS,
            NARROW_GLYPH_WIDTH * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
}    

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name: ShiftCursor
//
// Description: 
//  This function shifts cursor right to number of columns defined in Step
//  If cursor reaches right edge of the screen it moves one line down, scrolling screen
//  if nesessary
//
// Input: 
//	IN GC_DATA *GcData - pointer to private protocol data structure
//  IN UINT16 Step - number of columns to shift cursor right
//      
// Output: 
//  VOID
//		
// Notes:
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ShiftCursor(
    IN GC_DATA *GcData,
    IN UINT16  Step
)
{
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This = (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *)GcData;

    if(((GcData->SimpleTextOut.Mode)->CursorColumn + Step) >= (INT32)GcData->MaxColumns)
    {
        if((GcData->SimpleTextOut.Mode)->CursorRow == GcData->MaxRows - 1)
        {
            ScrollUp(GcData);
            This->SetCursorPosition(
                              This, 
                              0, 
                              (GcData->SimpleTextOut.Mode)->CursorRow);
        }
        else
        {
            This->SetCursorPosition(
                              This, 
                              0, 
                              (GcData->SimpleTextOut.Mode)->CursorRow + 1);
        }
    }
    else
    {
        This->SetCursorPosition(
                              This, 
                              (GcData->SimpleTextOut.Mode)->CursorColumn + Step, 
                              (GcData->SimpleTextOut.Mode)->CursorRow);
    }
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name:    GcUpdateBltBuffer
//
// Description: 
//  This function is a porting hook to implement specific action on
//  Blt buffer before put it on screen
//
// Input:       
//  IN GC_DATA *GcData - pointer to internal structure
//  IN UINT32 Width - width of passed buffer in pixels
//  IN UINT32 Height - height of passed buffer in pixels
//  IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer - pointer to Blt buffer
//              to perform action upon
//      
// Output:
//  VOID
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID GcUpdateBltBuffer (
	IN     GC_DATA 			             *This,
	IN     UINT32			             Width,
    IN     UINT32                        Height,
	IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer
)
{
    return;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name:    GcInternalClearScreen
//
// Description: 
//  This function is a porting hook to implement specific action when
//  clear screen operation is needed
//
// Input:       
//  IN GC_DATA *This - pointer to private protocol data structure
//      
// Output:      
//  VOID
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID GcInternalClearScreen (
	IN OUT GC_DATA *This
)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Fill;
    EFI_STATUS Status;
    UINT32 StartX;
    UINT32 StartY;
    UINT32 SizeX;
    UINT32 SizeY;

    if(This->MaxColumns == 0 || This->MaxRows == 0) { //this is the first invocation
        StartX = 0;
        StartY = 0;
        SizeX = This->GraphicsOutput->Mode->Info->HorizontalResolution;
        SizeY = This->GraphicsOutput->Mode->Info->VerticalResolution;
    } else {
        StartX = This->DeltaX;
        StartY = This->DeltaY;
        SizeX = This->MaxColumns * NARROW_GLYPH_WIDTH;
        SizeY = This->MaxRows * GLYPH_HEIGHT;
    }

    Fill = ColorArray[(((This->SimpleTextOut.Mode)->Attribute >> 4) & 0xf)];
    This->GraphicsOutput->Blt(This->GraphicsOutput,
                                &Fill,
                                EfiBltVideoFill,
                                0,
                                0,                   
                                StartX,
                                StartY,
                                SizeX,
                                SizeY,
                                0);

	Status = This->SimpleTextOut.SetCursorPosition(&(This->SimpleTextOut), 0, 0);
    if(EFI_ERROR(Status)) { //on first invocation this failed because MaxRows = MaxCols = 0
        (This->SimpleTextOut.Mode)->CursorColumn = 0;
	    (This->SimpleTextOut.Mode)->CursorRow = 0;
    }
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name:    AddChar
//
// Description: 
//  This function adds character to internal buffer of ready-to-print string
//
// Input:       
//  IN GC_DATA *This - pointer to private protocol data structure
//  IN CHAR16 Char - character to add
//  IN UINT16 Width - character width in system font symbols
//      
// Output:      
//  VOID
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AddChar(
    IN GC_DATA *GcData,
    IN CHAR16 Char,
    IN UINT16 Width
)
{
    UINT32 CurrentWidth;

    CurrentWidth = (GcData->SimpleTextOut.Mode)->CursorColumn + StringWidth;
    if((CurrentWidth + Width) > GcData->MaxColumns) {
        FlushString(GcData);

        if(Width == 2)
            ShiftCursor(GcData, 1);
    }

    TextBuffer[Position] = Char;
    Position++;
    StringWidth += Width;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------
// Name:    FlushString
//
// Description: 
//  This function flushes string from internal buffer to screen
//
// Input:       
//  IN GC_DATA *This - pointer to private protocol data structure
//      
// Output:      
//  VOID
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FlushString(
    IN GC_DATA *GcData
)
{
    EFI_STATUS Status;
    EFI_FONT_DISPLAY_INFO FontInfo;
    EFI_IMAGE_OUTPUT      *Image = NULL;

    if(Position == 0)
        return;

//retreive colors
    GetColorFromAttribute(
                        (GcData->SimpleTextOut.Mode)->Attribute,
                        &FontInfo.ForegroundColor,
                        &FontInfo.BackgroundColor);
//use system font
    FontInfo.FontInfoMask =   EFI_FONT_INFO_SYS_FONT 
                            | EFI_FONT_INFO_SYS_SIZE 
                            | EFI_FONT_INFO_SYS_STYLE;

/* put NULL-terminator */
    TextBuffer[Position] = 0;

    Status = GcData->HiiFont->StringToImage(GcData->HiiFont,
                                    EFI_HII_IGNORE_LINE_BREAK,
                                    TextBuffer,
                                    &FontInfo,
                                    &Image,
                                    0, 0, NULL, NULL, NULL);

    GcData->OemUpdateBltBuffer(GcData, Image->Width, Image->Height, Image->Image.Bitmap);

    GcData->GraphicsOutput->Blt(
                    GcData->GraphicsOutput,
                    Image->Image.Bitmap,
                    EfiBltBufferToVideo,
                    0,
                    0,                   
                    GcData->DeltaX + (GcData->SimpleTextOut.Mode)->CursorColumn * NARROW_GLYPH_WIDTH,
                    GcData->DeltaY + (GcData->SimpleTextOut.Mode)->CursorRow * GLYPH_HEIGHT,
                    Image->Width,
                    Image->Height,
                    Image->Width * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));     

    ShiftCursor(GcData, (Image->Width / 8));

    pBS->FreePool(Image->Image.Bitmap);
    pBS->FreePool(Image);

    Position = 0;
    StringWidth = 0;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
