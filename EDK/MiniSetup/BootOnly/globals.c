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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/globals.c $
//
// $Author: Arunsb $
//
// $Revision: 9 $
//
// $Date: 2/11/14 7:54p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/globals.c $
// 
// 9     2/11/14 7:54p Arunsb
// [TAG]	EIP132360
// [Category]	Improvement
// [Description]	Verify ESA will show a form if SendForm interface is
// called by a driver.
// [Files]	globals.c
// EsaBin.c
// FormBrowser2.c
// protocol.c
// minisetup.h
// 
// 8     4/18/13 1:50a Arunsb
// [TAG]  		EIP81490
// [Category]  	New Feature
// [Description]  	Post message support for BBS popup menu
// [Files]  		AMITSE.sdl, AmiTSEStr.uni, commonoem.c, FakeTokens.c and
// globals.c
// 
// 7     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     1/24/12 4:24a Arunsb
// [TAG]  		EIP81581
// [Category]  	Improvement
// [Description]  	Default driver order support
// [Files]  		globals.c, addbootoption.c, callback.c, minisetupext.h and
// variable.c
// 
// 5     11/20/11 7:03a Rajashakerg
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
// 4     11/14/11 2:43p Blaines
// [TAG] - EIP 75481
// [Category]- Function Request
// [Synopsis]- TSE debug print infrastructure.
// [Description]- Add TSE debug print info for basic functions such as
// Hiiparsing, HiiNotifications, HiiCallbacks. Variables, and Ifrforms
// data. 
// [Files]
// AMITSE.sdl, AmiTSEStr.uni,  CommonHelper.c, commonoem.c, FakeTokens.c
// Globals.c, Minisetup.cif, Minisetup.h, print.c, FormBrowser2.c, Hii.c,
// HiiCallback.c, HiiNotificationHandler.c, Parse.c, TseUefiHii.h,
// Uefi21Wrapper.c, setupdbg.h
// 
// 3     2/19/10 1:01p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 3     2/04/10 12:03p Blaines
// EIP-28005
// 
// Added PostManagerSetAttribute to support display of text in color.
// Added support for handling string characters --- \n, \r.
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     3/31/09 3:34p Madhans
// Hii string support for UEFI 2.0 or UEFI 2.1
// 
// 3     2/05/09 5:19p Madhans
// PostMgrStatus interface added.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		globals.c
//
// Description:	file contains code to take care of the globals in boot only
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

PROGRESSBAR_INFO	*gProgress;

#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
EFI_GRAPHICS_OUTPUT_PROTOCOL    *gGOP = NULL;
#else
EFI_UGA_DRAW_PROTOCOL           *gUgaDraw = NULL;
#endif //SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL

#ifndef STANDALONE_APPLICATION
EFI_CONSOLE_CONTROL_PROTOCOL	*gConsoleControl = NULL;
#endif //STANDALONE_APPLICATION

SCREEN_BUFFER	*gActiveBuffer;
SCREEN_BUFFER	*gFlushBuffer;

EFI_HANDLE	gImageHandle;
VOID*		gHiiHandle;

BOOLEAN		gPostMsgProtocolActive = TRUE;
BOOLEAN		gSetupContextActive = FALSE;
UINT8		gPostMgrAttribute = 0;

#if 0
// This adds no code space but allows the StrGather utility to know that these tokens are used
STRING_TOKEN(STR_MAIN_TITLE);
STRING_TOKEN(STR_MAIN_COPYRIGHT);
STRING_TOKEN(STR_HELP_TITLE);
STRING_TOKEN(STR_EVAL_MSG);
#endif // 0

UINT8	*gApplicationData;

#ifdef USE_DEPRICATED_INTERFACE
UINT8	*STRING_ARRAY_NAME;
#endif //USE_DEPRICATED_INTERFACE

NVRAM_VARIABLE	*gVariableList = NULL;
NVRAM_VARIABLE	*gFailsafeDefaults = NULL;
NVRAM_VARIABLE	*gOptimalDefaults = NULL;

BOOLEAN gEnterSetup = FALSE;
BOOLEAN gEnterBoot = FALSE;
EFI_EVENT gKeyTimer = NULL;
EFI_EVENT gClickTimer = NULL;
UINT32 gPasswordType = AMI_PASSWORD_NONE;

UINTN gPostStatus = TSE_POST_STATUS_BEFORE_POST_SCREEN;

UINTN gMaxRows = MAX_ROWS;
UINTN gMaxCols = MAX_COLS;
UINTN gPostManagerHandshakeCallIndex = 0;

#define EFI_DEFAULT_LEGACY_DEV_ORDER_VARIABLE_GUID  \
  { 0x3c4ead08, 0x45ae, 0x4315, 0x8d, 0x15, 0xa6, 0x0e, 0xaa, 0x8c, 0xaf, 0x69 }

#define EFI_DEFAULT_BOOT_ORDER_VARIABLE_GUID  \
  { 0x45cf35f6, 0x0d6e, 0x4d04, 0x85, 0x6a, 0x03, 0x70, 0xa5, 0xb1, 0x6f, 0x53 }

//EIP81581 Default driver order support
#define EFI_DEFAULT_DRIVER_ORDER_VARIABLE_GUID  \
  { 0xde788bed, 0xb6e2, 0x4290, 0xbd, 0xc8, 0x2a, 0xbb, 0x65, 0xd6, 0x21, 0x78 }

EFI_GUID EfiDefaultLegacyDevOrderGuid = EFI_DEFAULT_LEGACY_DEV_ORDER_VARIABLE_GUID;
EFI_GUID EfiDefaultBootOrderGuid = EFI_DEFAULT_BOOT_ORDER_VARIABLE_GUID;
EFI_GUID EfiDefaultDriverOrderGuid = EFI_DEFAULT_DRIVER_ORDER_VARIABLE_GUID;

//Globals for Debug prints
UINT16 gDbgPrint = TSE_DEBUG_MESSAGES;
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************