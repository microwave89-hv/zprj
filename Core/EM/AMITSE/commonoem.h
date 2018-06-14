//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/commonoem.h $
//
// $Author: Arunsb $
//
// $Revision: 18 $
//
// $Date: 5/02/14 5:45a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/commonoem.h $
// 
// 18    5/02/14 5:45a Arunsb
// [TAG]  		EIP156258
// [Category]  	Improvement
// [Description]  	Providing ELINK option to suppress the handle
// comparison on dynamic parsing
// [Files]  		AMITSE.mak, AMITSE.sdl, commonoem.c, commonoem.h and Parse.c
// 
// 17    3/06/13 12:24a Premkumara
// [TAG]  		EIP111415
// [Category]  	Improvement
// [Description]  	Elink function for SETUP_TOGGLE_KEY_UNICODE function
// [Files]  		HookAnchor.h, AMITSE.sdl, commonoem.c, Commonoem.h,
// HookList.c, HookAnchor.c
// 
// 16    10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 13    10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 15    2/01/12 1:53a Arunsb
// [TAG]  		EIP74968
// [Category]  	Improvement
// [Description]  	Support for mouse drag and drop to rearrange the items
// in the Orderlist.
// [Files]  		Ordlistbox.c, commonoem.c and commonoem.h
// 
// 14    11/20/11 6:56a Rajashakerg
// [TAG]  		EIP62763 
// [Category]  	Improvement
// [Description]  	Utilize the Improvements done from mouse driver in
// AMITSE
// [Files]  		HookAnchor.h, TseCommon.h, AMITSE.sdl, CommonHelper.c,
// commonoem.c, commonoem.h, buffer.c, globals.c, HookAnchor.c,
// minisetup.h, notify.c, postmgmt.c, protocol.c, ezport.c, stylecommon.c,
// Mouse.c, Action.c, Date.c, frame.c, MessageBox.c, minisetupext.c,
// minisetupext.h, numeric.c, numeric.h, page.c, PopupEdit.c, PopupEdit.h,
// PopupPassword.c, postmgmtext.c, time.c.
// 
// 13    7/20/11 3:25p Rajashakerg
// Removed the unwanted code for mouse hot click operation
// 
// 11    6/29/11 1:03p Rajashakerg
// [TAG]  		EIP47086
// [Category]  	New Feature
// [Description]  	Right clicking from the Main page is not exiting from
// BIOS setup.
// 
// [Files]  		minisetup.h, Ezport\style.h,Ezport\EzportBin.sdl,
// Ezport\EzportBin.mak, Ezport\ezport.c, Ezport\EzportBin.cif,
// EzportPlus\style.h, EzportPlus\EzportPlusBin.sdl, EzportPlusBin.mak,
// EzportPlus\EzportPlusBin.cif, EzportPlus\ezportplus.c, Legacy\style.h,
// Legacy\EzportPlusBin.sdl, Legacy\LegacyBin.mak, Legacy\LegacyBin.cif,
// Legacy\legacy.c, TseLiteBin.sdl, TseLite.cif, Memo.c, frame.c,
// application.h, application.c, commonoem.h, CommonHelper.c
// 
// 10    6/22/11 7:18a Arunsb
// [TAG]           EIP 62631, 60128 
// [Category]      New Feature
// [Description]   Hot key boot option in TSE as per UEFI spec. section
// 3.1.6.
//                 TSE_CHECK_SHIFTSTATE macro redefined to
// CheckAdvShiftState
// [Files]         AMITSE.sdl, CommonHelper.c, commonoem.c, commonoem.h,
// boot.c, hiistring20.c and hiistring21.c.
// 
// 9     3/28/11 9:06p Madhans
// [TAG]  		EIP41744 
// [Category]  	Improvement
// [Description]  	SoftKeyBoard Support in TSE. and Support to Work with
// new mouse driver(Label 07).
// [Files]  		HookAnchor.h
// AMITSE.sdl
// CommonHelper.c
// commonoem.c
// commonoem.h
// HookList.c
// HookAnchor.c
// Mouse.c
// minisetupext.c
// postmgmtext.c
// minisetupext.h
// PopupPassword.c
// PopupString.c
// TseLiteCommon.c
// 
// 8     9/16/10 8:39p Madhans
// Updated for TSE 2.10. Refer changelog.log for more deatils.
// 
// 11    8/18/10 6:15p Mallikarjunanv
// EIP-38089: Hook after pressing F2 key and before showing setup menu.
// 
// 10    6/08/10 5:06p Blaines
// Created new AMITSE hook (hook33), called when TSE determines that
// console out is available.
// 
// 9     4/13/10 6:01p Madhans
// Eip: 33100 To create new hook for BootNowLaunching. (From bbsPopoup and
// Boot override menu).
// 
// 8     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 7     2/04/10 11:06p Madhans
// Map Control Mouse Action Hook Added.
// 
// 6     1/09/10 2:26a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     9/15/09 9:19a Sudhirv
// added new hook entries for LoadSetupDefaults and PreResetSystem
// 
// 4     7/30/09 4:16p Blaines
// Fix for EIP #23127
// 
// Item #8 : Shift + Tab handling.
// 
// MapControlKeys() does not handle correctly because of
// TSE_CHECK_SHIFTSTATE macro has problem.
// ControlActionNextSelection is always became true so never checks
// ControlActionPrevSelection.
// 
// 3     6/24/09 6:33p Madhans
// Coding Standards
// 
// 2     6/24/09 11:52a Blaines
// Coding standard update
// 
// 1     6/09/09 9:52a Madhans
// TSE 2.00.1201
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 2     4/29/09 9:01p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 10:49p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		commonoem.h
//
// Description:	header of commonoem.h
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _COMMONOEM_H_
#define _COMMONOEM_H_

typedef enum
{
	ControlActionUnknown,
	ControlActionNextLeft,
	ControlActionNextRight,
	ControlActionNextUp,
	ControlActionNextDown,
	ControlActionPageUp,
	ControlActionPageDown,
	ControlActionNextSelection,
	ControlActionPrevSelection,
	ControlActionSelect,
	ControlActionIncreament,
	ControlActionDecreament,
	ControlActionBackSpace,
	ControlActionAbort,
	ControlActionAlpha,
	ControlActionNumeric,
	ControlActionHelpPageUp,
	ControlActionHelpPageDown,

	ControlActionHome,
	ControlActionEnd,
	ControlActionChoose,
	ControlMouseActionLeftDown,
	ControlMouseActionLeftUp
}CONTROL_ACTION;

typedef struct _STYLECOLORS
{
	UINT8 FGColor;
	UINT8 BGColor;
	UINT8 SecFGColor;
	UINT8 SecBGColor;
	UINT8 SelFGColor;
	UINT8 SelBGColor;
	UINT8 NSelFGColor;
	UINT8 NSelBGColor;
	UINT8 LabelBGColor;
	UINT8 LabelFGColor;
	UINT8 NSelLabelFGColor;
	UINT8 EditBGColor;
	UINT8 EditFGColor;
	UINT8 PopupFGColor;
	UINT8 PopupBGColor;
}STYLECOLORS;


//For CLICK Event
#define     TSEMOUSE_NULL_CLICK         0
#define     TSEMOUSE_RIGHT_CLICK        1
#define     TSEMOUSE_LEFT_CLICK         2
//#define     TSEMOUSE_MIDDLE_CLICK       3
#define     TSEMOUSE_LEFT_DCLICK        4
#define     TSEMOUSE_RIGHT_DOWN         5
#define     TSEMOUSE_LEFT_DOWN          6
//#define     TSEMOUSE_MIDDLE_DOWN        7
#define     TSEMOUSE_RIGHT_UP           8
#define     TSEMOUSE_LEFT_UP            9
//#define     TSEMOUSE_MIDDLE_UP         10

//Data Structure for Storing Mouse action
typedef struct _MOUSE_INFO
{
    UINT32	Top;
    UINT32	Left;
    UINT32  ButtonStatus;
}MOUSE_INFO;

#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
#include <Protocol/AmiKeyCode.h>


//Start EIP #23127 Item #8
//EIP 60128 Ctrl+Alt+F6 also working as Ctrl+F6 or Alt+F6
BOOLEAN CheckAdvShiftState (UINT32 AmiKeyShiftState, UINT32 CondShiftState);
#define TSE_CHECK_SHIFTSTATE  CheckAdvShiftState
 
/*( (!(AmiKeyShiftSate &(~SHIFT_STATE_VALID)) && (!CondShiftState)) || \
(((AmiKeyShiftSate &(~SHIFT_STATE_VALID)) & CondShiftState) == (CondShiftState & (~SHIFT_STATE_VALID))) || \
((AmiKeyShiftSate == SHIFT_STATE_VALID) && (CondShiftState == SHIFT_STATE_VALID)) )*/
//End EIP #23127 Item #8

#else
#ifndef _AMI_EFI_KEY_DATA_
#define _AMI_EFI_KEY_DATA_
typedef struct {
  EFI_INPUT_KEY  Key;
} AMI_EFI_KEY_DATA;
#endif
#endif

VOID DrawQuietBootLogo(VOID);
BOOLEAN ProcessConInAvailability(VOID);
VOID ProcessEnterSetup(VOID);
VOID ProcessProceedToBoot(VOID);
VOID MinisetupDriverEntryHook(VOID);
VOID PostManagerHandShakeHook(VOID);
CONTROL_ACTION MapControlKeys(AMI_EFI_KEY_DATA key);
VOID CheckForKey( EFI_EVENT Event, VOID *Context );
VOID CheckForClick( EFI_EVENT Event, VOID *Context );
VOID BeforeLegacyBootLaunch(VOID);
VOID AfterLegacyBootLaunch(VOID);
VOID BeforeEfiBootLaunch(VOID);
VOID AfterEfiBootLaunch(VOID);
VOID SavedConfigChanges(VOID);
VOID LoadedConfigDefaults(VOID);
VOID TimeOutLoopHook(VOID);
VOID PasswordEncode( CHAR16 *Password, UINTN MaxSize);
EFI_STATUS SetControlColors(UINT8 *BGColor, UINT8 *FGColor, UINT8 *SecBGColor, UINT8 *SecFGColor, 
								 UINT8 *SelBGColor, UINT8 *SelFGColor, UINT8 *NSelBGColor, UINT8 *NSelFGColor,
								 UINT8 *LabelBGColor, UINT8 *LabelFGColor,UINT8 *NSelLabelFGColor, UINT8 *EditBGColor, UINT8 *EditFGColor,
								 UINT8 *PopupFGColor, UINT8 *PopupBGColor);

VOID InvalidActionHook(VOID);
VOID LoadedUserDefaults(VOID);
VOID LoadedBuildDefaults(VOID);
VOID LoadedPreviousValues(VOID);
VOID SetupConfigModified(VOID);
VOID LoadSetupDefaults (VOID *defaults, UINTN data );
VOID PreSystemResetHook(VOID);
CONTROL_ACTION MapControlMouseAction(VOID *pMouseInfo);
VOID ProcessProceedToBootNow(VOID);
VOID ProcessConOutAvailable(VOID);
VOID ProcessUIInitHook(VOID);
VOID AfterInitPostScreen(VOID);
VOID SwitchToPostScreen(VOID);//EIP-111415 SwitchToPostScreenHook



#define MODIFIER_DUAL_KEYS 			0x000000FF          //For handling any oTf the two dual(ctrl, alt, shift and logo) keys pressed
#define RIGHT_LEFT_SHIFT_PRESSED	0x00000003
#define RIGHT_LEFT_CONTROL_PRESSED	0x0000000C
#define RIGHT_LEFT_ALT_PRESSED		0x00000030
#define RIGHT_LEFT_LOGO_PRESSED		0x000000C0


#define EFI_MOUSE_DRIVER_PROTOCOL_GUID \
{0xc7a7030c, 0xc3d8, 0x45ee, 0xbe, 0xd9, 0x5d, 0x9e, 0x76, 0x76, 0x29, 0x53}

typedef struct
{
	EFI_GUID			VariableGuid;
	CHAR8				VariableName [50];
}VAR_DYNAMICPARSING_HANDLESUPPRESS;

#endif

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//