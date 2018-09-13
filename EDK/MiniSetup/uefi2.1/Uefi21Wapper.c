//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2013, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Uefi21Wapper.c $
//
// $Author: Premkumara $
//
// $Revision: 85 $
//
// $Date: 8/28/14 11:54a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Uefi21Wapper.c $
// 
// 85    8/28/14 11:54a Premkumara
// [TAG] 			EIP174031
// [Category] 		Improvement
// [Description] 	Removed TODO comments and added proper comments in those
// places
// [Files] 			commonoem.c, commonhelper.c, special.c, submenu.c,
// minisetupext.c, uefi21wapper.c and legacy.c
// 
// 84    8/28/14 9:56a Premkumara
// [TAG] 	           EIP173038
// [Category]           Bug Fix
// [Symptom:]          System hangs on using UefiVarsetnvramforCurrentform
// [Root Cause]       UINT32 gProcessedForms[MAX_FORMS_TO_PROCESS];
// Entries overbound the arrary MAX_FORMS_TO_PROCESS
// [Solution] 	           gProcessedForms formed dynamically
// [Files] 	           Uefi21wapper.c
// 
// 83    7/12/14 12:25p Arunsb
// [TAG]	EIP174938
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	Arrow mark shown when driver health page published
// [Root Cause]	Driver health formset considered as dynamic page so arrow
// shown
// [Solution]	For driverhealth formset DynamicPageCount variable not
// incremented. Returned EFI_ABORTED in parseform for driverhealth formset
// so DynamicPageCount not incremented so arrow will not be shown.
// [Files]	Parse.c and uefi21wapper.c
// 
// 82    5/21/14 6:33p Arunsb
// [TAG]	EIPEIP169096,168632
// [Description]	Changed global variable guid usage for tse debug
// messages. Removed unwanted RT flag in TSE.
// [Files]	commonoem.c, setupdbg.h, print.c and uefi21wapper.c
// 
// 81    5/02/14 5:02a Arunsb
// [TAG]	EIP156958
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	UefiVarsetnvramforCurrentform function not saving the values
// properly for passed page ID
// [Root Cause]	This function calling VarSetNvram to update the NVRAM,
// this function updates the offset value to NVRAM and then got the whole
// buffer from NVRAM again and updates the cache so second controls and
// further modified controls cache values are overwritten by NVRAM value.
// [Solution]	Instead of calling VarSetNvram set the values in
// UefiVarsetnvramforCurrentform fnc itself.
// [Files]	uefi21wapper.c
// 
// 80    2/11/14 8:57p Arunsb
// [TAG]	EIP133728
// [Category]	New Feature
// [Description]	Provide special control support in ESA for driver health
// [Files]	uefi21wapper.c
// 
// 79    10/18/13 4:20p Arunsb
// [TAG]	EIP140268
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	Clicking driver health control crashes
// [Root Cause]	Incremented pointer freed instead of allocated pointer
// [Solution]	Pointer freed properly
// [Files]	uefi21wapper.c
// 
// 78    8/26/13 3:10p Blaines
// [TAG] - EIP 134138 
// [Category] - Defect 
// [Symptom] - Incorrect Driver Health name shown in BIOS (UEFI Mode)
// Setup for SAS Card.
// 
// [Root cause]
// In the function FindDriverHealthDriverName,when querying the
// GetDriverName() routine of Component Name Protocol, the function is
// passing more than one language.
// 
// [Solution]- 
// In the function FindDriverHealthDriverName,when querying the
// GetDriverName() routine of Component Name Protocol, pass only one
// language to the routine.
// 
// [Files] 
//   Uefi21Wapper.c
// 
// 77    7/01/13 10:47a Premkumara
// [TAG]  		EIP126997
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Selecting Save current form Now or Discard Current form and
// Exit now controls causing setup crash
// [RootCause]  	NULL is not handled properly for controls->controlPtr
// [Solution]  	Handled NULL check properly in necessary places
// [Files]  		Uefi21Wapper.c
// 
// 76    5/22/13 11:18a Arunsb
// Name value string not saving properly. Fixed it.
// 
// 75    4/18/13 9:39a Arunsb
// Functions moved to avoid build error in 2.0 build
// 
// 74    4/16/13 9:20a Arunsb
// Build error corrected
// 
// 73    4/16/13 8:01a Arunsb
// [TAG]  		EIP106950
// [Category]  	New Feature
// [Description]  	PasswordEncode hook function
// 
// 72    3/29/13 12:30p Premkumara
// [TAG]  		EIP97611
// [Category]  	New Feature
// [Description]  	PrintScreen Support in TSE
// [Files]  		AMITSE.sdl, CommonHelper.c, HotKeyBin.h, AddBootOption.c,
// Page.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 71    3/25/13 8:31a Premkumara
// [TAG]  		EIP116315
// [Category]  	Improvement
// [Description]  	Display control prompt string for password control.
// (for String on CHAP secret popup)
// [Files]  		- AMITSE.sdl
// - CommonHelper.c
// - FakeToken.c
// - AmiTSEStr.uni
// - TseLite\PopupPassword.c
// - uefi2.1\UefiWapper21.c
// - uefi2.0\HiiCallback.c
// - uefi2.0\hii.h
// - uefi2.0\hii.c 
// 
// 70    2/25/13 10:57a Blaines
// [TAG] - EIP 104273
// [Category] - Action Item
// [Description] -  Provide ability to dump the Hii Pack from the Setup as
// part TSE debug Infrastructure. It should dump the Pack updates on Hii
// notification also.
// So it can be used to debug the issue.
// [Files] - ForBrowser2.c,  Hii.c,  HiiNotificationHandler.c,
// UefiWapper.c,  TseUefiHii.h
// 
// 69    12/05/12 4:51a Premkumara
// [TAG]  		EIP105552
// [Category]  	Improvement
// [Description]  	Adding RefreshID support for OrderList, Password
// controls
// [Files]  		Uefi21Wapper.c
// 
// 68    10/18/12 8:56a Rajashakerg
// [TAG]  		EIP103568 
// [Category]  	Improvement
// [Description]  	Help string support for ordered list
// [Files]  		Uefi21Wapper.c, ordlistbox.c
// 
// 67    10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 24    10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 65    9/18/12 2:15a Rajashakerg
// [TAG]  		EIP88658 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Minisetup crashes after controller reconnection during Hii
// callback
// [RootCause]  	Minisetup crashes after controller reconnection during
// callback. since we have new packs and new handles.
// [Solution]  	Additional checks for invalid ptrs were added
// [Files]  		Hii.c, Parse.c, Uefi21Wapper.c
// 
// 64    9/17/12 6:22a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 62    9/10/12 11:46a Arunsb
// [TAG]  		EIP90372
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Setup browser handling of
// EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD
// [RootCause]  	For discard action current value is saved
// [Solution]  	Introduced a global variable which will set for discard
// action for that current value will not be saved
// [Files]  		HiiCallback.c and Uefi21Wapper.c
// 
// 61    5/29/12 4:46a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 60    5/28/12 12:38p Arunsb
// [TAG]  		EIP86885
// [Category]  	Improvement
// [Description]  	Support added for following callback action requests 
// EFI_BROWSER_ACTION_REQUEST_FORM_SUBMIT_EXIT
// EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD_EXIT
// EFI_BROWSER_ACTION_REQUEST_FORM_APPLY
// EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD
// [Files]  		Uefi21Wapper.c
// 
// 59    4/27/12 1:39a Rajashakerg
// [TAG]  		EIP74964
// [Category]  	Improvement
// [Description]  	UefiGetDateTimeDetails does not initialize the min and
// max values
// [Files]  		Uefi21Wapper.c
// 
// 58    4/05/12 12:49p Arunsb
// [TAG]  		EIP83252
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hangs with onboard SAS Option ROM
// [RootCause]  	ProcessPackNotification not invoked properly
// [Solution]  	gEnableDrvNotification flag handled properly to invoke
// ProcessPackNotification
// [Files]  		uefi2.1\hiicallback.c and uefi2.1\uefi21wapper.c
// 
// 57    2/02/12 5:41p Arunsb
// [TAG]  		EIP81814
// [Category]  	Improvement
// [Description]  	Merging common utility function for page, control and
// variable data.
// [Files]  		Uefi21Wapper.c
// 
// 56    2/02/12 1:19p Premkumara
// [TAG]  		EIP75351,75352,75384
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		String.c, boot.c, TseAdvanced.c,Time.c, PopupEdit.c,
// MessageBox.c, Label.c, Edit.c, Date.c
// 
// 55    2/02/12 3:06a Premkumara
// [TAG]  		EIP75066 
// [Category]  	Improvement
// [Description]  	Support loading defaults for Ordelist controls
// [Files]  		Ordlistbox.c, Uefi21Wapper.c, CtrlCond.c, HiiCallback.c,
// Parse.c, Uefi20Wapper.c, TseUefihiil.h
// 
// 54    1/20/12 5:10a Rajashakerg
// [TAG]  		EIP77875 
// [Category]  	Improvement
// [Description]  	Minisetup: Memory leaks in text browser
// [Files]  		Uefi21Wapper.c, hiistring21.c, variable.c
// 
// 53    1/20/12 12:31a Rajashakerg
// [TAG]  		EIP80426 
// [Category]  	Improvement
// [Description]  	When restoring settings, avoid accessing the varstore
// for text controls
// [Files]  		uefi21wapper.c, Setupdata.h.
// 
// 52    1/13/12 1:41a Arunsb
// [TAG]  		EIP80360
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  		HDDSecurity module - Issue in login with TSE, Master
// password disabled
// [RootCause]  	Cache not updated
// [Solution]  	Cache updated properly
// [Files]  		Tseadvanced.c, special.c and uefi21wapper.c
// 
// 51    1/09/12 1:59a Arunsb
// [TAG]  		EIP79952
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Add driver option displays select boot option as title
// [RootCause]  	Title problem
// [Solution]  	Title changed
// [Files]  		Faketokens.c, amitsestr.uni, addbootoption.c,
// uefi2.0\hiicallback.c and uefi21wapper.c
// 
// 50    12/08/11 5:21p Arunsb
// progress freeing removed
// 
// 49    12/08/11 1:09p Rajashakerg
// [TAG]  		EIP75379 
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Postmgmtext.c, Uefi21Wapper.c
// 
// 48    12/08/11 12:18p Rajashakerg
// [TAG]  		EIP75558 
// [Category]  	Improvement
// [Description]  	Incorrect static strings retrieved in Text Broswer
// [Files]  		Uefi21Wapper.c
// 
// 47    12/07/11 2:48p Arunsb
// [TAG]  		EIP75588
// [Category]  	New Feature
// [Description]  	Support for queuing UpdatePack notifications
// [Files]  		frame.c, page.c, formbrowser2.c, hii.c, hiicallback.c,
// hiinotificationhandler.c, tseuefihii.h and uefi21wapper.c
// 
// 46    12/07/11 2:08p Arunsb
// [TAG]  		EIP77475
// [Category]  	New Feature
// [Description]  	Changed varsetvalue to _vargetsetvalue in
// UefiRefershQuestionValueNvRAM fnc since _vargetsetvalue wont calls the
// SetupConfigModifiedHook
// [Files]  		uefi21wapper.c
// 
// 45    12/07/11 8:56a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Updated the check for date and time flags for NON RTC.
// [Files]  		Uefi21Wapper.c
// 
// 44    12/07/11 8:16a Rajashakerg
// [TAG]  		EIP75118 
// [Category]  	Improvement
// [Description]  	xtractConfig() fail since BrowserCallback() cannot find
// the variable to process
// [Files]  		FormBrowser2.c, FormBrowser2.h, HiiCallback.c,
// Uefi21Wapper.c, PopupSel.c
// 
// 43    12/07/11 7:18a Rajashakerg
// [TAG]  		EIP75558 
// [Category]  	Improvement
// [Description]  	Incorrect static strings retrieved in Text Broswer
// [Files]  		Uefi20Wapper.c
// 
// 42    12/01/11 7:46a Rajashakerg
// [TAG]  		EIP75464 
// [Category]  	Improvement
// [Description]  	Improper handling of action controls
// [Files]  		SubMenu.c, UefiAction.c, HiiCallback.c, Uefi21Wapper.c
// 
// 41    11/28/11 5:16a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 40    11/28/11 2:15a Premkumara
// [TAG]  		EIP75384 
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		UefiWapper.c, Hii.c, Expression.c, CtrlCond.c, PopupSel.c,
// Minisetupext.c, Menu.c, Date.c, Ezport\Stylecommon.c,
// EzportPlus\StyleCommon.c,
// 
// 39    11/23/11 5:20a Rajashakerg
// [TAG]  		EIP75473 
// [Category]  	Improvement
// [Description]  	System Time is not updated every second
// [Files]  		variable.h, variable.c, FormBrowser2.c, TseUefiHii.h,
// Uefi21Wapper.c, hii.h, uefi20Wapper.c
// 
// 38    11/20/11 7:39a Premkumara
// [TAG]  		EIP73226
// [Category]  	New Feature
// [Description]  	Extended support for password prompt
// [Files]  		FakeToken.c, Uefi21Wapper.c, AmiTSEStr.uni, PopupPassword.c,
// 
// 37    11/14/11 2:43p Blaines
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
// 36    11/14/11 12:07a Arunsb
// While checking in EIP70421 & 70422 Support for driver order,
// UefiRefershQuestionValueNvRAM
// function had a wrong fix. So reverting.
// 
// 35    11/13/11 1:13p Arunsb
// [TAG]  		EIP70421
// [Category]  	New Feature
// [Description]  	Support for driver order in TSE
// [Files]  		AMITSE.SDL, CommonHelper.c, setup.ini, uefisetup.ini,
// boot.c,
// minisetup.h, bbs.c, special.c, special.h, tseadvanced.c,
// addbootoption.c,
// callback.c, minisetupext.c, minisetupext.h, popupsel.c, popupsel.h,
// TseLitehelper.c, variable.c, Uefi21Wapper.c, AMIVfr.h, boot.h,
// TseElink.h, variable.h, 
// setup.h, Boot.vfr and Setup.uni
// 
// 34    11/03/11 4:43a Premkumara
// [TAG]  		EIP70966
// [Category]  	Improvement
// [Description]  	Hii orderlist item can't update priority from value in
// Setup menu for both enable and disable TSE_MULTILINE_CONTROLS token
// [Files]  		Ordlistbox.c, ordlistbox.h, TseUefiHii.h, Uefi21Wrapper.c
// 
// 33    10/20/11 12:25p Blaines
// Correct the comments.
// 
// 32    10/20/11 11:48a Blaines
// [TAG]  		EIP 72333
// [Category]  	Sighting
// [Symptom]  	Some SAS controller card HII Screen Titles are displaying
// the wrong information
// [RootCause]  	Menu tab always displays the root page title when
// navigating submenu pages. TSE did not support the display of Formset
// Help. 
// 		
// [Solution]	Display Formset Help for Dynamic page, Display page title of
// submenu pages in the menu tab.
// 
// [Files Changed]
// - AMITSE.sdl, CommonHelper.c, special.c, Menu.c, minisetupext.h,
// TseUefiHii.h, Uefi21Wapper.c
// 
// 31    9/29/11 7:02p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 30    8/26/11 6:22p Blaines
// [TAG]  		EIP68354
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Callback was invoked during periodic update for time and
// date controls without EFI_IFR_REFRESH_OP.
// [Solution]  	Callback is only invoked for interactive controls.
// [Files]  		TseLite: Time.c, Date.c
// Uefi21: Parese.c, Uefi21Wrapper.c
// 
// 29    7/19/11 3:04p Arunsb
// [TAG]        EIP57661
// [Category]   New Feature
// [Description]    Driver health variables are updated in cache too.
// [Files]          notify.c, Uefi21Wapper.c and variable.h
// 
// 28    6/30/11 4:20a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 27    6/23/11 4:01p Rajashakerg
// [TAG]  		EIP55762, 58925, 59971
// [Category]  	New Feature
// [Description]  	Support REF2,REF3 and REF4 in AMITSE
// Support direct form navigation path
// Improper layout of controls in the root page when Dynamic pages are
// added using the Legacy Setup Style	
// 
// [Files]  		setupdata.h, CommonHelper.c, AMITSE.sdl, Legacy\Legacy.c,
// Legacy\style.h, Legacy\style.h, frame.c, minisetupext.c,
// minisetupext.h, numeric.c, page.c Popupstring.c, Hii.c,
// Uefi21Wrapper.c, Parse.c Hii.c
// 
// 26    6/22/11 6:05p Arunsb
// [TAG]       EIP56405
// [Category]      New Feature
// [Description]   Support for EFI_IFR_VARSTORE_NAME_VALUE opcode
// [Files]         Hii.c, parse.c and uefi21wapper.c
// 
// 25    6/20/11 12:28p Rajashakerg
// [TAG]  		EIP60563
// [Category]  	New Feature
// [Description]  	Support for signed decimal value for
// EFI_IFR_NUMERIC_OP. 
// [Files]  		numeric.c, numeric.h, string.c, string.h, Uefi21Wapper.c
// 
// 24    4/29/11 4:46p Arunsb
// For 2.13 public patch release IFR RefX feature is omitted
// 
// 22    3/28/11 11:45p Madhans
// UefiGetKeyField() updated.
// 
// 21    3/28/11 5:06p Rajashakerg
// [TAG]  		EIP56413 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_RESET_BUTTON opcode
// [Files]  		ezport.c, minisetupext.h, ResetButton.c, ResetButton.h,
// Hii.c, TseUefiHii.h, Uefi21Wapper.c, hii.h, Uefi20Wapper.c
// 
// 20    3/21/11 1:02a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 19    3/09/11 7:26p Madhans
// [TAG]  		EIPEIP48615 
// [Category]  	Improvement
// [Description]  	To support UEFI 2.1 RefreshOp. Based in Refersh Rate
// Controls are refershed periodically.
// [Files]  		minisetupext.h
// SubMenu.h
// SubMenu.c
// Memo.c
// Memo.h
// numeric.c
// numeric.h
// time.c
// Date.c
// PopupSel.c
// PopupSel.h
// PopupString.c
// PopupString.h
// ordlistbox.c
// minisetupext.c
// UefiAction.c
// hii.h
// Uefi20wapper.c
// hiicallback.c
// Parse.c
// tseuefihii.h
// Uefi21wapper.c
// 
// 18    2/01/11 7:38p Madhans
// [TAG] - EIP 50737 
// [Category]- Defect
// [Severity]- Mordarate
// [Symptom] - Suppressing the Interactive control does not work
// correctly.
// [RootCause] - The control conditional pointer if not set correctly.
// [Solution]- To fix the Control condition pointer. And identify the
// suppress if related to UEFI action control
// [Files] - UefiAction.c TseLiteHelper.c hii.h uefi20wapper.c
// uefi21wapper.c
// 
// 17    12/28/10 12:31p Madhans
// To update the Tag of EIp 46998. UEFI option ROM menus disappear in
// Setup when certain options are selected. 
// No file changed but Comment updated right
// 
// 16    12/02/10 5:51p Madhans
// [TAG] - EIP 48169    
// [Category]- Improvment.
// [Severity]- Mordarate
// [Symptom]- To do the Workaround for ConfigtoBlock issues and Fix issues
// with Retirive config.
// [Solution]- Fix done formBrowser2.c and uefi21wrapper.c 
// [Files] - formBrowser2.c and uefi21wrapper.c 
// 
// 15    12/02/10 5:34p Madhans
// [TAG] - EIP 49559   
// [Category]- defect
// [Severity]- Mordarate
// [Symptom]- OneOption contols works ok if it stores the values in BYTE
// and Does not contain any suppressif for options.
// But it has issues in supporting UINT16, UINT32 and UINT64 storage.
// [Rootcause] - The Type is not checked for Storeage and issues with
// condition check for options.
// [Solution]- Fix done ctrlcond.c and uefi21wrapper.c 
// [Files] - CtrlCond.h, ctrlcond.c and uefi21wrapper.c 
// 
// 14    12/02/10 5:21p Madhans
// [TAG] - EIP 49557  
// [Category]- defect
// [Severity]- Mordarate
// [Symptom]- UEFIAction controls does not work correctly.
// [Rootcause] - Action controls does not Process the QuestionResp
// correctly. 
// [Solution]- Fix done UEFIAction to check for QuestionResp and call the
// callback 
// [Files] - uefiaction.c and uefi21wapper.c
// 
// 13    11/10/10 7:02p Blaines
// EIP 47037:  Add range checks to properly edit and update date/time.
// 
// 12    10/27/10 4:25p Madhans
// [TAG]    	EIP46998 
// [Category]	Defect
// [Symptom]	Some user action on PCIx with UEFI Hii Pages causes Setup
// screen pages and menu disappers.
// [RootCause] UEFI 2.1 parsing code is not handling the Removepack and
// New pack sequance properly. Normally UpdatePack
// does the removepack and AddPack.
// [Solution]	UEFI 2.1 parsing code fixed to handle above case correctly.
// [Files]		hii.c HiiNotificationHandler.c Parse.c TseUefiHii.h
// uefi21wapper.c
// 
// 11    9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 17    7/07/10 7:45p Madhans
// Changes to Support Adding Conditions to Suppress or Grayout the Special
// controls.
// 
// 16    6/22/10 6:44a Mallikarjunanv
// EIP 39764 - Password Encoding Enabled by default.
// 
// 15    6/21/10 4:19p Blaines
// Added code to support more question types for the function
// UefiGetKeyField.
// 
// 14    6/17/10 2:48p Madhans
// Varsotre NameValue fix.
// 
// 13    6/15/10 12:33p Blaines
// Update function header and properly initialize status variable in
// UefiSetTime and UefiGetTime.
// 
// 12    6/14/10 7:15p Madhans
// Dynamic parsing support
// 
// 11    6/08/10 5:17p Blaines
// Add support for UEFI 2.0/2.1 Date and Time controls
// 
// 10    4/08/10 12:09p Madhans
// To call the Special Callback with proper Key value.
// 
// 9     4/07/10 6:25p Madhans
// For UEFI 2.1 Error Manger variable is EFI variable not an HII Varstore.
// 
// 8     3/11/10 5:44p Madhans
// Coding Standards Update
//
// 7     2/26/10 7:02p Madhans
// To build with EDK support.
//
// 4     12/14/09 4:52p Presannar
// Bug Fix Eip-32732
//
// 3     11/30/09 1:10p Presannar
// Modified ConfigAccessCallback EFI_BROWSER_ACTION from pass by reference
// to pass by value
//
// 2     11/19/09 5:33p Presannar
// Updated TSE include file name to not clash with CORE file
// Updated fn GetControlConditionVarId to search for Control within the
// formset if not found in current form
// Added Fn IsPasswordEncodeEnabled
//
// 1     7/24/09 6:54p Presannar
//
// 6     5/28/09 11:50a Presannar
// Bug Fixes
//
// 5     4/24/09 7:54p Presannar
// TSE 2.0 UEFI 2.1 Code Complete
//
// 4     4/14/09 12:43p Presannar
// Added Fn ProcessActionQuestionConfiguration,
// ProcessBrowserActionRequest and _VerifyResponseString
// Added AMI_IFR_MSGBOX declarations
// Updated Uefi Action control handling
//
// 3     3/31/09 4:15p Madhans
// UEFI Wrapper improvments.
//
// 2     1/29/09 6:10p Presannar
// Added case for EFI_IFR_SUBTITLE_OP
// Added new fn GetControlConditionVariable and HiiRemoveString
//
// 1     1/09/09 2:38p Presannar
// UEFI 2.1 Hii Related Code - Initial Drop
//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name: Uefi21Wapper.c
//
// Description:
//
//<AMI_FHDR_END>
//****************************************************************//

//----------------------------------------------------------------------------

#include "minisetup.h"
#include "TseUefiHii.h"
#include "TseElinks.h" 			//EIP106950
#include EFI_PROTOCOL_DEFINITION(UnicodeCollation)
#if TSE_DEBUG_MESSAGES
#include <Protocol\SimpleFileSystem.h>
#endif 
#include "TseDrvHealth.h"       //Has TSE related driver health structures
//EIP 57661 Driver health support
UINT16 *_DevicePathToStr (EFI_DEVICE_PATH_PROTOCOL *Path);
CHAR16 DriverHealthStatus [6][23] = {
									L"Healthy",
									L"Repair Required",
									L"Configuration Required",
									L"Failed",
									L"Reconnect Required",
									L"Reboot Required"
								};
EFI_HANDLE                  gDrvHandle = NULL;
EFI_DRIVER_HEALTH_PROTOCOL  *gDrvHealthInstance = NULL;
DRV_HEALTH_HNDLS            *gDrvHealthHandlesHead = NULL;
extern BOOLEAN gEnableDrvNotification; //TRUE if allow notification function to process action, FALSE to ignore the notification
extern AMI_POST_MANAGER_PROTOCOL 	*mPostMgr;
extern VOID _GetNextLanguage(CHAR8 **LangCode, CHAR8 *Lang);
//----------------------------------------------------------------------------
#if TSE_DEBUG_MESSAGES
BOOLEAN SetupDebugKeyHandler(UINT16 ItemIndex, UINT16 Unicode, CHAR16	*Value) ;
EFI_STATUS DisplayParseFormSetData(VOID) ;
EFI_STATUS DebugShowAllHiiVariable(UINT32 formID) ;
UINT16 _GetQuestionToken(UINT8 *ifrData);
VOID ProcessPackToFile(EFI_HII_DATABASE_NOTIFY_TYPE NotifyType, EFI_HANDLE Handle);
UINTN HpkFileCount=0;
#endif //End of TSE_DEBUG_MESSAGES

EFI_FILE_PROTOCOL * CreateFile(CHAR16 *filename, UINT32 index);
EFI_GUID  guidSimpleFileSystemProtocol = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

static EFI_IFR_SUBTITLE	_Title = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, 0 };
static EFI_IFR_SUBTITLE	_Help = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, 0 };
static EFI_IFR_SUBTITLE	_SubTitle = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, 0 };
static EFI_IFR_SUBTITLE	_HelpTitle = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, STRING_TOKEN(STR_HELP_TITLE) };
static EFI_IFR_SUBTITLE	_NavStrings = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, 0 };

static STRING_REF CallbackErrToken=0;

AMI_IFR_MSGBOX _PreviousMsgBox = { 0, 0, STRING_TOKEN(STR_LOAD_PREVIOUS), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_LOAD_PREVIOUS_MSG) };
AMI_IFR_MSGBOX _FailsafeMsgBox = { 0, 0, STRING_TOKEN(STR_LOAD_FAILSAFE), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_LOAD_FAILSAFE_MSG) };
AMI_IFR_MSGBOX _OptimalMsgBox = { 0, 0, STRING_TOKEN(STR_LOAD_OPTIMAL), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_LOAD_OPTIMAL_MSG) };
AMI_IFR_MSGBOX _SaveMsgBox = { 0, 0, STRING_TOKEN(STR_SAVE_VALUES), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_SAVE_VALUES_MSG) };
AMI_IFR_MSGBOX _SaveExitMsgBox = { 0, 0, STRING_TOKEN(STR_SAVE_EXIT), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_SAVE_EXIT_MSG) };
AMI_IFR_MSGBOX _ExitMsgBox = { 0, 0, STRING_TOKEN(STR_EXIT), (VOID*)INVALID_HANDLE,  STRING_TOKEN(STR_EXIT_MSG) };
AMI_IFR_MSGBOX _SaveResetMsgBox = { 0, 0, STRING_TOKEN(STR_SAVE_RESET), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_SAVE_RESET_MSG) };
AMI_IFR_MSGBOX _ResetMsgBox = { 0, 0, STRING_TOKEN(STR_RESET), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_RESET_MSG) };
AMI_IFR_MSGBOX _HelpMsgBox = { 0, 0, STRING_TOKEN(STR_GENERAL_HELP), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_GENERAL_HELP_MSG) };
AMI_IFR_MSGBOX _SaveUserMsgBox = { 0, 0, STRING_TOKEN(STR_SAVE_USER_DEFAULTS), (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_SAVE_VALUES_MSG) };
AMI_IFR_MSGBOX _LoadUserMsgBox = { 0, 0, STRING_TOKEN(STR_LOAD_USER_DEFAULTS),  (VOID*)INVALID_HANDLE, STRING_TOKEN(STR_LOAD_USER_MSG) };

AMI_IFR_MSGBOX _InvalidPasswordFailMsgBox	= { 0, 0, STRING_TOKEN(STR_ERROR),(VOID*) INVALID_HANDLE, STRING_TOKEN(STR_ERROR_PSWD) };
AMI_IFR_MSGBOX _ClearPasswordMsgBox 		= { 0, 0, STRING_TOKEN(STR_WARNING),(VOID*) INVALID_HANDLE, STRING_TOKEN(STR_PSWD_CLR) };//EIP:73226 To Clear Old Password message
AMI_IFR_MSGBOX _ClearPasswordLabelMsgBox 	= { 0, 0, STRING_TOKEN(STR_WARNING),(VOID*) INVALID_HANDLE, STRING_TOKEN(STR_PSWD_CLR_LABEL) };//EIP:73226 To Clear Old Password message
AMI_IFR_MSGBOX _BootLaunchFailedMsgBox 		= { 0, 0, STRING_TOKEN(STR_WARNING), INVALID_HANDLE, STRING_TOKEN(STR_WARNING_NOT_FOUND) };
AMI_IFR_MSGBOX _gInvalidRangeFailMsgBox 	= { 0, 0, STRING_TOKEN(STR_ERROR), INVALID_HANDLE, STRING_TOKEN(STR_ERROR_INPUT) };

AMI_IFR_MSGBOX _gDelBootOptionReserved = { 0, 0, STRING_TOKEN(STR_WARNING), INVALID_HANDLE, STRING_TOKEN(STR_DEL_BOOT_OPTION_RESERVED) };
AMI_IFR_MSGBOX _gAddBootOptionReserved = { 0, 0, STRING_TOKEN(STR_WARNING), INVALID_HANDLE, STRING_TOKEN(STR_ADD_BOOT_OPTION_RESERVED) };
AMI_IFR_MSGBOX _gAddBootOptionEmpty = { 0, 0, STRING_TOKEN(STR_WARNING), INVALID_HANDLE, STRING_TOKEN(STR_ADD_BOOT_OPTION_EMPTY) };
AMI_IFR_MSGBOX _gAddDriverOptionEmpty = { 0, 0, STRING_TOKEN(STR_WARNING), INVALID_HANDLE, STRING_TOKEN(STR_ADD_DRIVER_OPTION_EMPTY) };


UINTN gPreviousMsgBox = (UINTN)&_PreviousMsgBox;
UINTN gFailsafeMsgBox = (UINTN)&_FailsafeMsgBox;
UINTN gOptimalMsgBox = (UINTN)&_OptimalMsgBox;
UINTN gSaveMsgBox = (UINTN)&_SaveMsgBox;
UINTN gSaveExitMsgBox = (UINTN)&_SaveExitMsgBox;
UINTN gExitMsgBox = (UINTN)&_ExitMsgBox;
UINTN gSaveResetMsgBox = (UINTN)&_SaveResetMsgBox;
UINTN gResetMsgBox = (UINTN)&_ResetMsgBox;
UINTN gHelpMsgBox = (UINTN)&_HelpMsgBox;
UINTN gSaveUserMsgBox = (UINTN)&_SaveUserMsgBox;
UINTN gLoadUserMsgBox = (UINTN)&_LoadUserMsgBox;

UINTN gBootLaunchFailedMsgBox 		=	(UINTN)&_BootLaunchFailedMsgBox;
UINTN gInvalidPasswordFailMsgBox	=	(UINTN)&_InvalidPasswordFailMsgBox;
UINTN gClearPasswordMsgBox			=	(UINTN)&_ClearPasswordMsgBox;//EIP:73226 To display Clear Old Password message
UINTN gClearLabelPasswordMsgBox		=	(UINTN)&_ClearPasswordLabelMsgBox;
UINTN gInvalidRangeFailMsgBox		=	(UINTN)&_gInvalidRangeFailMsgBox;
UINTN gDelBootOptionReserved 		=	(UINTN)&_gDelBootOptionReserved;
UINTN gAddBootOptionReserved 		=	(UINTN)&_gAddBootOptionReserved;
UINTN gAddBootOptionEmpty 			=	(UINTN)&_gAddBootOptionEmpty;
UINTN gAddDriverOptionEmpty 		=	(UINTN)&_gAddDriverOptionEmpty;

static AMI_IFR_MSGBOX gCallbackErrorMsgBox = { 0, 0, STRING_TOKEN(STR_ERROR), (VOID*)INVALID_HANDLE, 0 };

static BOOLEAN gHiiInitialized = FALSE;

EFI_GUID gEfiHiiConfigRoutingProtocolGuid = EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID;

EFI_HII_CONFIG_ROUTING_PROTOCOL *gHiiConfigRouting;

UINTN	gTitle = (UINTN)&_Title;
UINTN	gHelp = (UINTN)&_Help;
UINTN	gSubTitle = (UINTN)&_SubTitle;
UINTN	gHelpTitle = (UINTN)&_HelpTitle;
UINTN	gNavStrings = (UINTN)&_NavStrings;

VOID _UefiGetValidOptions(CONTROL_INFO *IfrPtr, UINT16 **OptionPtrTokens,
                        UINT64 **ValuePtrTokens, UINT16 *ItemCount,
						UINT8 MaxItems);

EFI_STATUS _VerifyResponseString(EFI_STRING Configuration, BOOLEAN NameValue);
UINT32 FindVarFromITKQuestionId(UINT16 QuestionId);

//EIP81814 Starts
//---------------------------------------------------------------------------
// Defines for Utility Functions
//---------------------------------------------------------------------------
#define MAX_FORMS_TO_PROCESS      50
#define EFI_INCONSISTENT_VALUE      (0x80000000 | 28)
#define EFI_NOSUBMIT_VALUE      (0x80000000 | 29)
#define CHECKBOX_OPTION_COUNT   2
#define OPTION_DEFAULT            0x10
#define OPTION_DEFAULT_MFG        0x20
#define TSE_GET_ONE_OF_WIDTH(a)				(((EFI_IFR_ONE_OF*)(a))->Width)
#define TSE_GET_ONE_OF_OPTION_WIDTH(a) ( \
          ((EFI_IFR_ONE_OF_OPTION*)a)->Type == EFI_IFR_TYPE_NUM_SIZE_8 ? sizeof(UINT8) : (\
          ((EFI_IFR_ONE_OF_OPTION*)a)->Type == EFI_IFR_TYPE_NUM_SIZE_16 ? sizeof(UINT16) : (\
          ((EFI_IFR_ONE_OF_OPTION*)a)->Type == EFI_IFR_TYPE_NUM_SIZE_32 ? sizeof(UINT32) : (\
          ((EFI_IFR_ONE_OF_OPTION*)a)->Type == EFI_IFR_TYPE_NUM_SIZE_64 ? sizeof(UINT64) : (\
          ((EFI_IFR_ONE_OF_OPTION*)a)->Type == EFI_IFR_TYPE_BOOLEAN ? sizeof(BOOLEAN) : (\
          ((EFI_IFR_ONE_OF_OPTION*)a)->Type == EFI_IFR_TYPE_TIME ? sizeof(EFI_HII_TIME) : (\
          ((EFI_IFR_ONE_OF_OPTION*)a)->Type == EFI_IFR_TYPE_DATE ? sizeof(EFI_HII_DATE) : (\
          ((EFI_IFR_ONE_OF_OPTION*)a)->Type == EFI_IFR_TYPE_STRING ? sizeof(EFI_STRING_ID) : (\
          0)))))))))



typedef struct _OPTION_LIST OPTION_LIST;

typedef struct _OPTION_LIST
{
  UINT16  Option;
  UINT64   Value;
  UINT8  Flag;
  OPTION_LIST *Next;
};

static BOOLEAN  LibInitialized = FALSE;
UINT32 *gProcessedForms; //[MAX_FORMS_TO_PROCESS]; //EIP 162180
UINT32 gVarOffset = 0;
UINT32 gProFormOffset = 0;
UINT32 gProFormOffsetAllocCount = 0;
//---------------------------------------------------------------------------
// Prototypes for Utility Functions
//---------------------------------------------------------------------------
BOOLEAN _InconsistenceCheck(PAGE_INFO *PgInfo, UINT16 *ErrStrToken);
BOOLEAN _DestinationFormProcessed(UINT32 FormID);
EFI_STATUS _GetVariableIDList(UINT32 FormID, UINT32 **varIDList);
EFI_STATUS _GetCheckBoxOptions(CONTROL_INFO *CtrlInfo, UINT32 *OptionCount, OPTION_LIST **OptionArray);
EFI_STATUS LoadDefaults(UINT32 FormID, BOOLEAN *ResetVal, BOOLEAN * ValChanged);
BOOLEAN _InconsistenceCheck(PAGE_INFO *PgInfo, UINT16 *ErrStrToken);
BOOLEAN _NoSubmitCheck(CONTROL_INFO *ctrlInfo, UINT16 *ErrStrToken);
EFI_STATUS _GetVariableIDList(UINT32 FormID, UINT32 **VarIDList);
BOOLEAN _DestinationFormProcessed(UINT32 FormID);
BOOLEAN IsNoSubmitOfForms(UINT32 FormID, UINT16* ErrToken);
EFI_STATUS CheckforNosubmitIf(UINT32 FormID, BOOLEAN Recursive, UINT16 *ErrToken);
EFI_STATUS _GetControlFlag(UINT32 PgIndex, UINT32 CtrlIndex, CONTROL_FLAGS **CtrlFlag);
EFI_STATUS GetNumOfPages(UINT32 *NumOfPages);
EFI_STATUS GetPageTitle(UINT32 PgIndex, UINT16 *TitleToken);
EFI_STATUS GetPageSubTitle(UINT32 PgIndex, UINT16 *SubtitleToken);
EFI_STATUS GetPageHandle(UINT32 PgIndex, EFI_HII_HANDLE  *Handle);
EFI_STATUS GetPageIdIndex(UINT32 PgIndex, UINT16 *PgIdIndex);
BOOLEAN IsParentPage(UINT32 PgIndex);
EFI_STATUS GetPageHiiId(UINT32 PgIndex, UINT16 *PageId);
EFI_STATUS GetPageParentId(UINT32 PgIndex, UINT16 *PageParentId);
EFI_STATUS GetCtrlsDestCtrlId(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *DestCtrlId);
EFI_STATUS GetControlType(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlType);
EFI_STATUS GetControlQuestionPrompt(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlPrompt);
EFI_STATUS GetControlHelpStr(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlHelp);
BOOLEAN IsControlCheckBox(UINT32 PgIndex, UINT32 CtrlIndex);
EFI_STATUS GetControlDataWidth(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlWidth);
EFI_STATUS GetControlDestinationPage(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlDestPg);
UINT8 GetControlAccess(UINT32 PgIndex, UINT32 CtrlIndex);
UINT8 GetControlRefresh(UINT32 PgIndex, UINT32 CtrlIndex);
BOOLEAN IsControlVisible(UINT32 PgIndex, UINT32 CtrlIndex);
BOOLEAN IsControlResetRequired(UINT32 PgIndex, UINT32 CtrlIndex);
BOOLEAN IsControlReadOnly(UINT32 PgIndex, UINT32 CtrlIndex);
BOOLEAN IsControlInteractive(UINT32 PgIndex, UINT32 CtrlIndex);
EFI_STATUS EvaluateControlCondition(UINT32 PgIndex, UINT32 CtrlIndex, UINTN *ExpResult);
EFI_STATUS GetQuestionValue(UINT32 PgIndex, UINT32 CtrlIndex, UINT8 **Value, UINTN *ValueSize);
EFI_STATUS SetQuestionValue(UINT32 PgIndex, UINT32 CtrlIndex, UINT8 *Value, UINTN ValueSize, UINT16 *ErrStrToken);
EFI_STATUS SaveQuestionValues(UINT32 FormID);
VOID FreeOptionList(OPTION_LIST *OptionArray);
EFI_STATUS GetControlDisplayFormat(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *Format);
EFI_STATUS GetControlMinMax(UINT32 PgIndex, UINT32 CtrlIndex, UINT64 *Min, UINT64 *Max);
EFI_STATUS GetControlDefault(UINT32 PgIndex, UINT32 CtrlIndex,UINT8 *Def, BOOLEAN Optimal);
EFI_STATUS GetOrderedListMaxEntries(UINT32 PgIndex, UINT32 CtrlIndex, UINT8 *MaxEntry);
EFI_STATUS GetOrderedListOptionDataWidth(CONTROL_INFO *ControlInfo, UINT32 *DataWidth);
EFI_STATUS GetOrderedListDataTypeWidth(UINT32 PgIndex, UINT32 CtrlIndex, UINT32 *DataWidth);
BOOLEAN IsPageRefreshable(UINT32 PgIndex);
BOOLEAN IsPageModal(UINT32 PgIndex);
BOOLEAN IfNoCommitVariable(UINT32 PgIndex, UINT32 CtrlIndex);
BOOLEAN IdentifyFormHasDefault(UINT32 FormID);
BOOLEAN IsFormsetHasDefault(UINT32 FormID);
EFI_STATUS GetPageGuidFromPgIndex(UINT32 PgIndex, EFI_GUID *FormGuid);
void AddEntryIngProcessedForms (UINT32 FormID);
void CleargProcessedForms (void);
//----------------------------------------------------------------------------
//EIP81814 Ends

#define _GET_MINMAXSTEP_DATA(b,c,d)			( \
				((c)==EFI_IFR_NUMERIC_SIZE_1)?((b).u8.d):( 	\
				((c)==EFI_IFR_NUMERIC_SIZE_2)?((b).u16.d):( \
				((c)==EFI_IFR_NUMERIC_SIZE_4)?((b).u32.d): 	\
				((b).u64.d) )))

#define TSE_GET_NUMERIC_MINVALUE(a)			_GET_MINMAXSTEP_DATA((((EFI_IFR_NUMERIC*)(a))->data),(((EFI_IFR_NUMERIC*)(a))->Flags&EFI_IFR_NUMERIC_SIZE),MinValue)
#define TSE_GET_NUMERIC_MAXVALUE(a)			_GET_MINMAXSTEP_DATA((((EFI_IFR_NUMERIC*)(a))->data),(((EFI_IFR_NUMERIC*)(a))->Flags&EFI_IFR_NUMERIC_SIZE),MaxValue)
#define TSE_GET_NUMERIC_STEP(a)				_GET_MINMAXSTEP_DATA((((EFI_IFR_NUMERIC*)(a))->data),(((EFI_IFR_NUMERIC*)(a))->Flags&EFI_IFR_NUMERIC_SIZE),Step)
#define TSE_GET_NUMERIC_BASE(a)				(((((EFI_IFR_NUMERIC*)a)->Flags&EFI_IFR_DISPLAY)==EFI_IFR_DISPLAY_UINT_HEX)?AMI_BASE_HEX:((((EFI_IFR_NUMERIC*)a)->Flags&EFI_IFR_DISPLAY)==EFI_IFR_DISPLAY_INT_DEC) ? AMI_BASE_INT_DEC :AMI_BASE_DEC)

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetHelpField
//
// Description:
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetHelpField(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT16 Token = 0;

  if(IfrPtr == NULL){
	  return Token;
  }
  switch(OpHeader->OpCode)
  {
  case EFI_IFR_REF_OP:
    Token = ((EFI_IFR_REF *)OpHeader)->Question.Header.Help;
    break;
  case EFI_IFR_TEXT_OP:
    Token = ((EFI_IFR_TEXT *)OpHeader)->Statement.Help;
    break;
  case EFI_IFR_ONE_OF_OP:
    Token = ((EFI_IFR_ONE_OF *)OpHeader)->Question.Header.Help;
    break;
  case EFI_IFR_TIME_OP:
    Token = ((EFI_IFR_TIME *)OpHeader)->Question.Header.Help;
    break;
  case EFI_IFR_DATE_OP:
    Token = ((EFI_IFR_DATE *)OpHeader)->Question.Header.Help;
    break;
  case EFI_IFR_NUMERIC_OP:
    Token = ((EFI_IFR_NUMERIC *)OpHeader)->Question.Header.Help;
    break;
  case EFI_IFR_PASSWORD_OP:
    Token = ((EFI_IFR_PASSWORD *)OpHeader)->Question.Header.Help;
    break;
  case EFI_IFR_ACTION_OP:
    Token = ((EFI_IFR_ACTION *)OpHeader)->Question.Header.Help;
    break;
  case EFI_IFR_STRING_OP:
    Token = ((EFI_IFR_STRING *)OpHeader)->Question.Header.Help;
    break;
  case EFI_IFR_RESET_BUTTON_OP:
	 Token = ((EFI_IFR_RESET_BUTTON *)OpHeader)->Statement.Help;//EIP:56413 Updated the Help field for Reset Button
    break;
  case EFI_IFR_ORDERED_LIST_OP:
	 Token = ((EFI_IFR_ORDERED_LIST *)OpHeader)->Question.Header.Help;//EIP:103568  Updated the Help field for order list control.
    break;
  default:
    break;
  }

  return Token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetPromptField
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetPromptField(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT16 Token = 0;

  if(IfrPtr == NULL){
	  return Token;
  }
  switch(OpHeader->OpCode)
  {
  case EFI_IFR_REF_OP:
    Token = ((EFI_IFR_REF *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_NUMERIC_OP:
    Token = ((EFI_IFR_NUMERIC *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_TIME_OP:
    Token = ((EFI_IFR_TIME *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_DATE_OP:
    Token = ((EFI_IFR_DATE *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_ONE_OF_OP:
    Token = ((EFI_IFR_ONE_OF *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_ORDERED_LIST_OP:
    Token = ((EFI_IFR_ORDERED_LIST *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_CHECKBOX_OP:
    Token = ((EFI_IFR_CHECKBOX *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_PASSWORD_OP:
    Token = ((EFI_IFR_PASSWORD *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_ACTION_OP:
    Token = ((EFI_IFR_ACTION *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_STRING_OP:
    Token = ((EFI_IFR_STRING *)OpHeader)->Question.Header.Prompt;
    break;
  case EFI_IFR_RESET_BUTTON_OP:
	 Token = ((EFI_IFR_RESET_BUTTON *)OpHeader)->Statement.Prompt;//EIP:56413  Updated the Prompt field for Reset Button
    break;
  default:
    break;
  }

  return Token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetKeyField
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetKeyField(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT16 Token = 0;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_REF_OP:
    Token = ((EFI_IFR_REF *)IfrPtr)->Question.QuestionId;
    break;
  case EFI_IFR_NUMERIC_OP:
    Token = ((EFI_IFR_NUMERIC *)IfrPtr)->Question.QuestionId;
    break;
  case EFI_IFR_STRING_OP:
    Token = ((EFI_IFR_STRING *)IfrPtr)->Question.QuestionId;
    break;

  case EFI_IFR_PASSWORD_OP:
    Token = ((EFI_IFR_PASSWORD *)IfrPtr)->Question.QuestionId;
    break;
  case EFI_IFR_CHECKBOX_OP:
    Token = ((EFI_IFR_CHECKBOX *)IfrPtr)->Question.QuestionId;
    break;
  case EFI_IFR_ACTION_OP:
    Token = ((EFI_IFR_ACTION *)IfrPtr)->Question.QuestionId;
    break;
  case EFI_IFR_DATE_OP:
    Token = ((EFI_IFR_DATE *)IfrPtr)->Question.QuestionId;
    break;
  case EFI_IFR_ONE_OF_OP:
    Token = ((EFI_IFR_ONE_OF *)IfrPtr)->Question.QuestionId;
    break;
  case EFI_IFR_ORDERED_LIST_OP:
    Token = ((EFI_IFR_ORDERED_LIST *)IfrPtr)->Question.QuestionId;
    break;
  case EFI_IFR_TIME_OP:
    Token = ((EFI_IFR_TIME *)IfrPtr)->Question.QuestionId;
    break;
  default:
    break;
  }

  return Token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetTitleField
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetTitleField(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT16 Token = 0;

// EIP 88658  : Minisetup crashes after controller reconnection during Hii callback
  if(IfrPtr == NULL){
      goto DONE;
  }
  switch(OpHeader->OpCode)
  {
  case EFI_IFR_SUBTITLE_OP:
    Token = ((EFI_IFR_SUBTITLE *)IfrPtr)->Statement.Prompt;
    break;
  case EFI_IFR_FORM_SET_OP:
    Token = ((EFI_IFR_FORM_SET *)IfrPtr)->FormSetTitle;
    break;
  case EFI_IFR_FORM_OP:
    Token = ((EFI_IFR_FORM *)IfrPtr)->FormTitle;
    break;
  default:
    break;
  }

DONE:
  return Token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetFlagsField
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UefiGetFlagsField(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT8 Flag = 0;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_REF_OP:
    Flag = ((EFI_IFR_REF *)IfrPtr)->Question.Flags;
    break;
  case EFI_IFR_TIME_OP:
	Flag = ((EFI_IFR_TIME *)IfrPtr)->Flags;
   	break;
  case EFI_IFR_DATE_OP:
	Flag = ((EFI_IFR_DATE *)IfrPtr)->Flags;
   	break;
  default:
    break;
  }

  return Flag;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiIsInteractive
//
// Description:   
//
// Parameter:	    CONTROL_INFO *ControlData
//
// Return value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN UefiIsInteractive(CONTROL_INFO *ControlData)
{
  return (BOOLEAN)(ControlData->ControlFlags.ControlInteractive);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetControlKey
//
// Description:   
//
// Parameter:	    CONTROL_INFO *ControlData
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetControlKey(CONTROL_INFO *ControlData)
{
  return 	ControlData->ControlKey;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetTextField
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetTextField(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT16 Token = 0;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_TEXT_OP:
    Token = ((EFI_IFR_TEXT*)OpHeader)->Statement.Prompt;
    break;
  default:
    break;
  }

  return Token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetTextTwoField
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetTextTwoField(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT16 Token = 0;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_TEXT_OP:
    Token = ((EFI_IFR_TEXT*)OpHeader)->TextTwo;
    break;
  default:
    break;
  }

  return Token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetSubTitleField
//
// Description:   
//
// Parameter:	    VOID *IfrPtr,UINT16 Token
//
// Return value:  VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetSubTitleField(VOID *IfrPtr,UINT16 Token)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_SUBTITLE_OP:
    ((EFI_IFR_SUBTITLE*)OpHeader)->Statement.Prompt = Token;
    break;
  default:
    break;
  }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetHelpField
//
// Description:
//
// Parameter:	    VOID *IfrPtr,UINT16 Token
//
// Return value:  VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetHelpField(VOID *IfrPtr, UINT16 Token)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  
  switch(OpHeader->OpCode)
  {
  case EFI_IFR_REF_OP:
    ((EFI_IFR_REF *)OpHeader)->Question.Header.Help = Token ;
    break;
  case EFI_IFR_TEXT_OP:
    ((EFI_IFR_TEXT *)OpHeader)->Statement.Help = Token ;
    break;
  case EFI_IFR_ONE_OF_OP:
    ((EFI_IFR_ONE_OF *)OpHeader)->Question.Header.Help = Token ;
    break;
  case EFI_IFR_TIME_OP:
    ((EFI_IFR_TIME *)OpHeader)->Question.Header.Help = Token ;
    break;
  case EFI_IFR_DATE_OP:
    ((EFI_IFR_DATE *)OpHeader)->Question.Header.Help = Token ;
    break;
  case EFI_IFR_NUMERIC_OP:
    ((EFI_IFR_NUMERIC *)OpHeader)->Question.Header.Help = Token ;
    break;
  case EFI_IFR_PASSWORD_OP:
    ((EFI_IFR_PASSWORD *)OpHeader)->Question.Header.Help = Token ;
    break;
  case EFI_IFR_ACTION_OP:
    ((EFI_IFR_ACTION *)OpHeader)->Question.Header.Help = Token ;
    break;
  case EFI_IFR_STRING_OP:
    ((EFI_IFR_STRING *)OpHeader)->Question.Header.Help = Token ;
    break;
  case EFI_IFR_RESET_BUTTON_OP:
	((EFI_IFR_RESET_BUTTON *)OpHeader)->Statement.Help = Token ;
    break;
  default:
    break;
  }
  
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetPromptField
//
// Description:   
//
// Parameter:	    VOID *IfrPtr,UINT16 Token
//
// Return value:  VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetPromptField(VOID *IfrPtr,UINT16 Token)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_REF_OP:
    ((EFI_IFR_REF*)OpHeader)->Question.Header.Prompt = Token;
    break;
  case EFI_IFR_ONE_OF_OP:
  case EFI_IFR_NUMERIC_OP:
  case EFI_IFR_TIME_OP:
  case EFI_IFR_DATE_OP:
  case EFI_IFR_ORDERED_LIST_OP:
  case EFI_IFR_CHECKBOX_OP:
  case EFI_IFR_PASSWORD_OP:
  case EFI_IFR_STRING_OP:
  {
    EFI_IFR_QUESTION_HEADER *Question = (EFI_IFR_QUESTION_HEADER *)((UINT8 *)OpHeader + sizeof(EFI_IFR_OP_HEADER));

    Question->Header.Prompt = Token;
  }
    break;
  default:
    break;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiCreateSubTitleTemplate
//
// Description:   
//
// Parameter:	    UINT16 Token
//
// Return value:  VOID *
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID * UefiCreateSubTitleTemplate(UINT16 Token)
{
  EFI_IFR_OP_HEADER *OpHeader = EfiLibAllocateZeroPool(sizeof(EFI_IFR_SUBTITLE));

  OpHeader->OpCode = EFI_IFR_SUBTITLE_OP ;
  OpHeader->Length = sizeof(EFI_IFR_SUBTITLE) ;
  UefiSetSubTitleField((VOID *)OpHeader,Token);
  return (VOID*)OpHeader;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiCreateStringTemplate
//
// Description:   Function to create uefi string template
//
// Parameter:	    UINT16 Token
//
// Return value:  VOID *
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID * UefiCreateStringTemplate(UINT16 Token)
{
  EFI_IFR_OP_HEADER *OpHeader = EfiLibAllocateZeroPool(sizeof(EFI_IFR_STRING));

  OpHeader->OpCode = EFI_IFR_STRING_OP ;
  OpHeader->Length = sizeof(EFI_IFR_STRING) ;
  UefiSetPromptField((VOID *)OpHeader,Token);
  return (VOID*)OpHeader;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetIfrLength
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UefiGetIfrLength(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

  return OpHeader->Length;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetMinValue
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT64
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT64 UefiGetMinValue(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT64 Min = 0;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_NUMERIC_OP:
    // Should The type be Taken Into Account? //
    //Min =  (UINT64)((EFI_IFR_NUMERIC*)OpHeader)->data.u64.MinValue;
	Min = TSE_GET_NUMERIC_MINVALUE(IfrPtr);
	break;
  case EFI_IFR_PASSWORD_OP:
    Min =  (UINT64)((EFI_IFR_PASSWORD*)OpHeader)->MinSize;
    break;
  case EFI_IFR_STRING_OP:
    Min =  (UINT64)((EFI_IFR_STRING*)OpHeader)->MinSize;
    break;
  default:
    break;
  }
  return Min;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetMaxValue
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT64
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT64 UefiGetMaxValue(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT64 Max = 0;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_NUMERIC_OP:
    // Should The type be Taken Into Account? //
    //Max = (UINT64)((EFI_IFR_NUMERIC*)OpHeader)->data.u64.MaxValue;
	Max = TSE_GET_NUMERIC_MAXVALUE(IfrPtr);
    break;
  case EFI_IFR_PASSWORD_OP:
    Max = (UINT64)((EFI_IFR_PASSWORD*)OpHeader)->MaxSize;
    break;
  case EFI_IFR_STRING_OP:
    Max = (UINT64)((EFI_IFR_STRING*)OpHeader)->MaxSize;
    break;
  default:
    break;
  }
  return Max;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetStepValue
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT64
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT64 UefiGetStepValue(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT64 Step = 0;
  switch(OpHeader->OpCode)
  {
  case EFI_IFR_NUMERIC_OP:
    // Should The type be Taken Into Account? //
    //Step = (UINT64)((EFI_IFR_NUMERIC*)OpHeader)->data.u64.Step;
    Step = TSE_GET_NUMERIC_STEP(IfrPtr);
    break;
  default:
    break;
  }
  return Step;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetBaseValue
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UefiGetBaseValue(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT8 Base = EFI_IFR_DISPLAY_UINT_DEC;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_NUMERIC_OP:
    //Base = (((EFI_IFR_NUMERIC *)OpHeader)->Flags & EFI_IFR_DISPLAY);
	Base = TSE_GET_NUMERIC_BASE(IfrPtr);
    break;
  default:
    break;
  }
  return Base;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetWidth
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetWidth(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT16 Width = 0;

  if (NULL == OpHeader) //EIP-126997 Avoid setup crash
	  return Width;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_NUMERIC_OP:
  case EFI_IFR_ONE_OF_OP:
    Width = (UINT16)(1 << (((EFI_IFR_NUMERIC*)OpHeader)->Flags & EFI_IFR_NUMERIC_SIZE));
    break;
  case EFI_IFR_PASSWORD_OP:
    Width = (UINT16)((EFI_IFR_PASSWORD*)OpHeader)->MaxSize * sizeof(CHAR16);
    break;
  case EFI_IFR_STRING_OP:
    Width = (UINT16)((EFI_IFR_STRING*)OpHeader)->MaxSize * sizeof(CHAR16);
    break;
  case EFI_IFR_CHECKBOX_OP:
    Width = sizeof(UINT8);
    break;
  case EFI_IFR_DATE_OP:
    Width = sizeof(EFI_HII_DATE);
    break;
  case EFI_IFR_TIME_OP:
    Width = sizeof(EFI_HII_TIME);
    break;
  case EFI_IFR_EQ_ID_VAL_OP:
  case EFI_IFR_EQ_ID_LIST_OP:
  case EFI_IFR_EQ_ID_ID_OP:
    ASSERT(1);
    break;
  default:
    break;
  }
  return Width;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetQuestionOffset
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
extern UINT32	gtempCurrentPage;
UINT16 UefiGetQuestionOffset(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  EFI_IFR_QUESTION_HEADER *QHeader = NULL;
  UINT16 VarOffset = 0;
  UINT32 iIndex = 0;
  VARIABLE_INFO *Variable = NULL;

  if (NULL == OpHeader) //EIP-126997 Avoid setup crash
	  return VarOffset;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_CHECKBOX_OP:
  case EFI_IFR_REF_OP:
  case EFI_IFR_RESET_BUTTON_OP:
  case EFI_IFR_ACTION_OP:
  case EFI_IFR_DATE_OP:
  case EFI_IFR_NUMERIC_OP:
  case EFI_IFR_ONE_OF_OP:
  case EFI_IFR_STRING_OP:
  case EFI_IFR_PASSWORD_OP:
  case EFI_IFR_ORDERED_LIST_OP:
  case EFI_IFR_TIME_OP:
    QHeader = (EFI_IFR_QUESTION_HEADER *)((UINT8*)OpHeader + sizeof(EFI_IFR_OP_HEADER));
   for (iIndex = 0; iIndex < gVariables->VariableCount; iIndex++)
   {
      Variable = (VARIABLE_INFO*)((UINT8 *)gVariables + gVariables->VariableList [iIndex]);
      if ((VARIABLE_ATTRIBUTE_NAMEVALUE == (Variable->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE)))
      {
	      UINT32  page = (NULL == gApp ? gtempCurrentPage : gApp->CurrentPage);
	      PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList [page]);
	      
			//Always dont depend on VariableID alone it will be same for different handles, compare handle also
	      if (pageInfo && (pageInfo->PageHandle == Variable->VariableHandle) && (Variable->VariableID == QHeader->VarStoreId))
	      {
		      return 0;
	      }
      }
   }
    VarOffset = QHeader->VarStoreInfo.VarOffset;
    break;
  default:
    break;
  }
  return VarOffset;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetDateTimeDetails
//
// Description:   
//
// Parameter:	    VOID *IfrPtr,UINT8 Type,UINT16 * Help,UINT16 * Min,UINT16 * Max
//
// Return value:  VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiGetDateTimeDetails(VOID *IfrPtr,UINT8 Type,UINT16 * Help,UINT16 * Min,UINT16 * Max)
{
/*
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  EFI_IFR_NUMERIC *NumIfr=NULL;
  switch(OpHeader->OpCode)
  {
  case EFI_IFR_TIME_OP:
    if(Type == AMI_TIME_HOUR)
      NumIfr = &(((EFI_IFR_TIME*)OpHeader)->Hour);
    else if (Type == AMI_TIME_MIN)
      NumIfr = &(((EFI_IFR_TIME*)OpHeader)->Minute);
    else if (Type == AMI_TIME_SEC)
      NumIfr = &(((EFI_IFR_TIME*)OpHeader)->Second);
    break;
  case EFI_IFR_DATE_OP:
    if(Type == AMI_DATE_YEAR)
      NumIfr = &(((EFI_IFR_DATE*)OpHeader)->Year);
    else if (Type == AMI_DATE_MONTH)
      NumIfr = &(((EFI_IFR_DATE*)OpHeader)->Month);
    else if (Type == AMI_DATE_DAY)
      NumIfr = &(((EFI_IFR_DATE*)OpHeader)->Day);
    break;
  default:
    break;
  }
  if(NumIfr)
  {
    *Help = NumIfr->Help;
    *Min = NumIfr->Minimum;
    *Max = NumIfr->Maximum;
  }*/

  *Min = 0;
  *Max = 0xFFFF;//EIP 74964 Initializing the MIN/MAX values for date and time.

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetOneOfOptions
//
// Description:   
//
// Parameter:	    VOID *IfrPtr,VOID **Handle,UINT16  **OptionPtrTokens,
//                UINT64 **ValuePtrTokens, UINT16 *ItemCount,
//                UINT16 *Interactive,UINT16 *CallBackKey
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiGetOneOfOptions(CONTROL_INFO *CtrlInfo, VOID **Handle, UINT16 **OptionPtrTokens,
                               UINT64 **ValuePtrTokens, UINT16 *ItemCount,
                               UINT16 *Interactive,UINT16 *CallBackKey )
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)(CtrlInfo->ControlPtr);
  EFI_IFR_QUESTION_HEADER *QHeader;
  EFI_STATUS Status = EFI_SUCCESS;
  UINT16 Index= 0;
  UINT8 Opcode = OpHeader->OpCode;
  UINT8 MaxItems = 10;

  if(OpHeader->OpCode == EFI_IFR_CHECKBOX_OP)
  {
    MaxItems = 2;
    *Handle = gHiiHandle;
  }

  // Evaluate Interactive and Callback
  QHeader = (EFI_IFR_QUESTION_HEADER *)((UINT8 *)OpHeader + sizeof(EFI_IFR_OP_HEADER));
  if(QHeader->Flags & EFI_IFR_FLAG_CALLBACK)
  {
    if(Interactive)
      *Interactive = TRUE;
    if(CallBackKey)
      *CallBackKey = QHeader->QuestionId;
  }

  // Free Buffers if Allocated and Allocate afresh
  if( OptionPtrTokens != NULL )
  {
    if( *OptionPtrTokens != NULL )
    MemFreePointer((VOID **)OptionPtrTokens);
  }

  if( ValuePtrTokens != NULL )
  {
	if( *ValuePtrTokens != NULL )
		MemFreePointer((VOID **)ValuePtrTokens);
  }

	if( NULL != OptionPtrTokens )//EIP-75379 Static code analysis check for NULL
	{
		*OptionPtrTokens = (UINT16 *)EfiLibAllocateZeroPool(MaxItems * sizeof(UINT16));
	}

	if(ValuePtrTokens)
		*ValuePtrTokens = (UINT64 *)EfiLibAllocateZeroPool(MaxItems * sizeof(UINT64));

	if ( NULL == OptionPtrTokens || NULL == *OptionPtrTokens )//EIP-75379 Static code analysis check for NULL
	{
		Status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

  //Populate Options
  if(Opcode == EFI_IFR_CHECKBOX_OP)
  {
    *ItemCount = MaxItems;
	for(Index = 0; Index < MaxItems; Index++)
	{
		(*OptionPtrTokens)[Index] = gCheckboxTokens[Index];
		if(ValuePtrTokens)
      		(*ValuePtrTokens)[Index] = Index;
	}
  }
  else
  {
    *ItemCount = 0;
    _UefiGetValidOptions(CtrlInfo, OptionPtrTokens, ValuePtrTokens, ItemCount, MaxItems);
  }

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    _UefiGetValidOptions
//
// Description:
//
// Parameter:	    CONTROL_INFO *CtrlInfo, UINT16 **OptionPtrTokens,
//                  UINT64 **ValuePtrTokens, UINT16 *ItemCount,UINT8 MaxItems
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _UefiGetValidOptions(CONTROL_INFO *CtrlInfo, UINT16 **OptionPtrTokens,
                                UINT64 **ValuePtrTokens, UINT16 *ItemCount,UINT8 MaxItems)
{
  EFI_IFR_OP_HEADER *OpHeader = (EFI_IFR_OP_HEADER *)CtrlInfo->ControlPtr;
  UINT32 Offset = 0;
  INT32 InScope = 0;
  UINT16 Max = (UINT16)MaxItems;
  UINT16 Itr = 0;
  UINT8 suppress = FALSE;
  UINT8 condition = COND_NONE;
  INT32 suppressScopeCount = 0;
  UINT8 *conditionPtr = NULL;

  do
  {
    if(OpHeader->Scope)
    {
      InScope++;
      suppressScopeCount = suppressScopeCount? ++suppressScopeCount : 0;
    }
    switch(OpHeader->OpCode)
    {
    case EFI_IFR_SUPPRESS_IF_OP:
        if(suppress == FALSE)
        {
        	conditionPtr = (UINT8 *)OpHeader;
        	suppress = TRUE;
         	suppressScopeCount++;
		}
	  break;
    case EFI_IFR_ONE_OF_OPTION_OP:
		// Evaluate Condition to determine if option is required to be added to list
        condition = suppress && conditionPtr? CheckOneOfOptionSuppressIf(CtrlInfo, conditionPtr, (UINT8*)OpHeader) : COND_NONE;
		if(condition != COND_SUPPRESS)
        {
			// Add Option to Buffer.
			if(Itr == Max)
			{
				*OptionPtrTokens = MemReallocateZeroPool(*OptionPtrTokens, Max * sizeof(UINT16), (Max + 10) * sizeof(UINT16));
				if(ValuePtrTokens)
				{
        			*ValuePtrTokens = MemReallocateZeroPool(*ValuePtrTokens, Max * sizeof(UINT64), (Max + 10) * sizeof(UINT64));
				}
				Max += 10;
			}
			(*OptionPtrTokens)[Itr] = ((EFI_IFR_ONE_OF_OPTION *)OpHeader)->Option;
			if(ValuePtrTokens)
			{
				switch(((EFI_IFR_ONE_OF_OPTION *)OpHeader)->Type)
				{
				case EFI_IFR_TYPE_NUM_SIZE_16:
					(*ValuePtrTokens)[Itr] = ((EFI_IFR_ONE_OF_OPTION *)OpHeader)->Value.u16;
					break;
				case EFI_IFR_TYPE_NUM_SIZE_32:    
					(*ValuePtrTokens)[Itr] = ((EFI_IFR_ONE_OF_OPTION *)OpHeader)->Value.u32;
					break;
				case EFI_IFR_TYPE_NUM_SIZE_64:
					(*ValuePtrTokens)[Itr] = ((EFI_IFR_ONE_OF_OPTION *)OpHeader)->Value.u64;
					break;
				case EFI_IFR_TYPE_NUM_SIZE_8:
				default:
					(*ValuePtrTokens)[Itr] = ((EFI_IFR_ONE_OF_OPTION *)OpHeader)->Value.u8;
					break;
				}
			}
			Itr++;
		}
      break;
    case EFI_IFR_END_OP:
		InScope = InScope > 0? --InScope : 0;
        suppressScopeCount = suppressScopeCount > 0? --suppressScopeCount : 0;
        suppress = suppressScopeCount == 0? FALSE : suppress;
        conditionPtr = suppress == TRUE? conditionPtr : NULL;
    default:
      break;
    }

    // Move to Next Opcode
    Offset += OpHeader->Length;
    OpHeader = (EFI_IFR_OP_HEADER *)((UINT8*)CtrlInfo->ControlPtr + Offset);
  }while(InScope);
  *ItemCount = Itr;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   UefiGetValidOptionType
//
// Description: Assuming all the options in this control has option with
//              same type and length
//
// Input:	CONTROL_INFO *CtrlInfo - Pointer to the control info data
//          UINTN *Type - Returns EFI_IFR_TYPE_NUM_SIZE
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiGetValidOptionType(CONTROL_INFO *CtrlInfo, UINTN *Type, UINT32 *SizeOfData)
{
	EFI_IFR_OP_HEADER *OpHeader = (EFI_IFR_OP_HEADER *)CtrlInfo->ControlPtr;
	UINT32 Offset = 0;
	INT32 InScope = 0;
	UINT8 suppress = FALSE;
	UINT8 condition = COND_NONE;
	INT32 suppressScopeCount = 0;
	UINT8 *conditionPtr = NULL;

	do
	{
		if(OpHeader->Scope)
		{
			InScope++;
			suppressScopeCount = suppressScopeCount? ++suppressScopeCount : 0;
		}
		switch(OpHeader->OpCode)
		{
			case EFI_IFR_SUPPRESS_IF_OP:
				if(suppress == FALSE)
				{
					conditionPtr = (UINT8 *)OpHeader;
					suppress = TRUE;
					suppressScopeCount++;
				}
				break;
			case EFI_IFR_ONE_OF_OPTION_OP:
				// Evaluate Condition to determine if option is required to be added to list
				condition = suppress && conditionPtr? CheckOneOfOptionSuppressIf(CtrlInfo, conditionPtr, (UINT8*)OpHeader) : COND_NONE;
				if(condition != COND_SUPPRESS)
				{
					switch(((EFI_IFR_ONE_OF_OPTION *)OpHeader)->Type)
					{
						case EFI_IFR_TYPE_NUM_SIZE_16:
							*Type = EFI_IFR_TYPE_NUM_SIZE_16;
							*SizeOfData = sizeof(UINT16);
							goto DONE;
						case EFI_IFR_TYPE_NUM_SIZE_32:    
							*Type = EFI_IFR_TYPE_NUM_SIZE_32;
							*SizeOfData = sizeof(UINT32);
							goto DONE;
						case EFI_IFR_TYPE_NUM_SIZE_64:
							*Type = EFI_IFR_TYPE_NUM_SIZE_64;
							*SizeOfData = sizeof(UINT64);
							goto DONE;
						case EFI_IFR_TYPE_NUM_SIZE_8:
						default:
							*Type = EFI_IFR_TYPE_NUM_SIZE_8;
							*SizeOfData = sizeof(UINT8);
							goto DONE;
					}
				}
				break;
			case EFI_IFR_END_OP:
				InScope = InScope > 0? --InScope : 0;
				suppressScopeCount = suppressScopeCount > 0? --suppressScopeCount : 0;
				suppress = suppressScopeCount == 0? FALSE : suppress;
				conditionPtr = suppress == TRUE? conditionPtr : NULL;
				break;
			default:
				break;
		}
		// Move to Next Opcode
		Offset += OpHeader->Length;
		OpHeader = (EFI_IFR_OP_HEADER *)((UINT8*)CtrlInfo->ControlPtr + Offset);
	}while(InScope);

DONE:
	return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetMaxEntries
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UefiGetMaxEntries(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
  UINT8 Value = 0;

  switch(OpHeader->OpCode)
  {
  case EFI_IFR_ORDERED_LIST_OP:
    Value = ((EFI_IFR_ORDERED_LIST*)OpHeader)->MaxContainers;
    break;
  default:
    break;
  }
  return Value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiTseLiteGetBootOverRideIndex
//
// Description:   
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiTseLiteGetBootOverRideIndex(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER * OpHeader = (EFI_IFR_OP_HEADER *)IfrPtr;
  EFI_IFR_EQ_ID_LIST *EqIdList;
  UINT16 Index=0xFFFF;
  UINT8 InScope = 0;

  if ((OpHeader != NULL) && (OpHeader->OpCode == EFI_IFR_SUPPRESS_IF_OP))
  {
    do
    {
      if(OpHeader->Scope)
      {
        InScope++;
      }

      if(OpHeader->OpCode == EFI_IFR_END_OP)
      {
        InScope--;
        if(InScope == 0)
        {
          // EFI_IFR_EQ_ID_LIST_OP opcode not found
          goto DONE;
        }
      }

      OpHeader = (EFI_IFR_OP_HEADER*)((UINT8*)OpHeader + OpHeader->Length);
    }while(OpHeader->OpCode != EFI_IFR_EQ_ID_LIST_OP);

    // FIX ME : Do it better. Check the list length and 
    if(OpHeader->OpCode == EFI_IFR_EQ_ID_LIST_OP)
    {
      EqIdList = (EFI_IFR_EQ_ID_LIST*)OpHeader;
      Index = EqIdList->ListLength - 1;
    }
  }

DONE:
  return Index;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiTseLiteGetAmiCallbackIndex
//
// Description:   
//
// Parameter:	    VOID * Ptr
//
// Return value:  UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiTseLiteGetAmiCallbackIndex(VOID * Ptr, VOID * CtrlPtr)
{
  EFI_IFR_OP_HEADER * OpHeader = (EFI_IFR_OP_HEADER *)Ptr;
  UINT16 Index=0xFFFF;
  UINT8 InScope = 0;
  VOID *SupressIfPtr = NULL;

  if ((OpHeader != NULL) && (OpHeader->OpCode == EFI_IFR_SUPPRESS_IF_OP))
  {
    // Locate the Last supress If till the control Ptr
    do
    {
      if(OpHeader->Scope)
      {
        InScope++;
      }
      if(OpHeader->OpCode == EFI_IFR_END_OP)
      {
        InScope--;
        if(InScope == 0)
        {
          // EFI_IFR_EQ_ID_VAL_OP opcode not found
          goto DONE;
        }
      }
      if(OpHeader->OpCode == EFI_IFR_SUPPRESS_IF_OP)
        SupressIfPtr =  (VOID*)OpHeader;
      OpHeader = (EFI_IFR_OP_HEADER*)((UINT8*)OpHeader + OpHeader->Length);
    }while((UINTN)OpHeader < (UINTN)CtrlPtr);

    OpHeader = (EFI_IFR_OP_HEADER*)SupressIfPtr ;
    do
    {
      if(OpHeader->Scope)
      {
        InScope++;
      }
      if(OpHeader->OpCode == EFI_IFR_END_OP)
      {
        InScope--;
        if(InScope == 0)
        {
          // EFI_IFR_EQ_ID_VAL_OP opcode not found
          goto DONE;
        }
      }
      OpHeader = (EFI_IFR_OP_HEADER*)((UINT8*)OpHeader + OpHeader->Length);
    }while(OpHeader->OpCode != EFI_IFR_EQ_ID_VAL_OP);

    // FIX ME : Do it better. Check the list length and 
    if(OpHeader->OpCode == EFI_IFR_EQ_ID_VAL_OP)
    {
      Index = ((EFI_IFR_EQ_ID_VAL*)OpHeader)->Value;
    }
  }

DONE:
  return Index;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiFormCallbackNVRead
//
// Description:   
//
// Parameter:	    CHAR16 *name, EFI_GUID *guid, UINT32 *attributes,
//                UINTN *size, VOID **buffer
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiFormCallbackNVRead(CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size, VOID **buffer)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiFormCallbackNVWrite
//
// Description:   
//
// Parameter:	    CHAR16 *name, EFI_GUID *guid, UINT32 attributes,
//                VOID *buffer, UINTN size
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiFormCallbackNVWrite(CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size)
{
  EFI_STATUS Status = EFI_UNSUPPORTED;

  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiVarGetNvram
//
// Description:   
//
// Parameter:	    VARIABLE_INFO *VariableInfo, VOID **Buffer, UINTN Offset, 
//					UINTN Size
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NameValueGetHexStringAsBuffer (UINT8 **Buffer, CHAR16 *HexStringBuffer, UINTN Size);
EFI_STATUS UefiVarGetNvram(VARIABLE_INFO *VariableInfo, VOID **Buffer, UINTN Offset, UINTN Size)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_STRING configuration = (EFI_STRING)NULL;
	EFI_STRING result = (EFI_STRING)NULL;
	EFI_STRING stringPtr = (EFI_STRING)NULL;
	UINTN length = 1;
	UINT8 *buffer = NULL;
	EFI_GUID EfiHiiConfigAccessProtocolGuid = EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID;
	EFI_HANDLE DriverHandle;
	EFI_HII_CONFIG_ACCESS_PROTOCOL	*ConfigAccess;
	CHAR16 tmpString = (CHAR16)NULL;
	EFI_STRING progress = &tmpString;
   BOOLEAN PreservegEnableDrvNotification = FALSE;

	configuration = EfiLibAllocateZeroPool(length);
	if(configuration == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

  //
  // Construct the Configuration Header String
  //
  status = GetConfigHeader(VariableInfo, &configuration, &length);
	if(EFI_ERROR(status) || (configuration == NULL))//EIP-75384 Static Analysis
	{
		goto DONE;
	}

	if(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE)
	{
		//Allocate Memory for "&<Name>"
		UINTN len = length + EfiStrLen(L"&") + EfiStrLen(VariableInfo->VariableName) + sizeof(CHAR16);
		
		configuration = MemReallocateZeroPool(configuration, length * sizeof(CHAR16), len * sizeof(CHAR16));
		if(configuration == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		EfiStrCat(configuration, L"&");
		EfiStrCat(configuration, VariableInfo->VariableName);
        length = len;
	}else
	{
        status = GetBlockName(&configuration, &length, Offset, Size);
		if(EFI_ERROR(status))
		{
			goto DONE;
		}
	}

	SetCallBackControlInfo(VariableInfo->VariableHandle, 0); //Set this varaible handle to allow BrowserCallback

	PreservegEnableDrvNotification = gEnableDrvNotification;
	gEnableDrvNotification = TRUE; //EIP75588 Set to enable notification processing

	if (!(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE))		// Invoke Config Routing Route Config
	{
		status = gHiiConfigRouting->ExtractConfig (gHiiConfigRouting, configuration, &progress, &result);
	}
	else
	{
		status = gHiiDatabase->GetPackageListHandle (gHiiDatabase, VariableInfo->VariableHandle, &DriverHandle); //Calling the driver which publishes the name value
		if(!EFI_ERROR(status))
		{
			status = gBS->HandleProtocol (DriverHandle, &EfiHiiConfigAccessProtocolGuid , &ConfigAccess);
			if(!EFI_ERROR(status))
			{
				status = ConfigAccess->ExtractConfig (ConfigAccess, configuration, &progress, &result);
			}
		}
	}
  if (!PreservegEnableDrvNotification) // If gEnableDrvNotification is already True Don't touch it
		gEnableDrvNotification = FALSE; //EIP75588 Reset to disable notification processing
	SetCallBackControlInfo(NULL, 0); //Disable update
    if(EFI_ERROR(status) || (progress == (EFI_STRING)NULL))
	{
		goto DONE;
	}

	if(EFI_ERROR(status = _VerifyResponseString(result, (VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE)? TRUE : FALSE)))
  {
    goto DONE;
  }

	stringPtr = result;
	if(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE)
	{
		for(stringPtr = result; *stringPtr != 0 && EfiStrnCmp(stringPtr, VariableInfo->VariableName, EfiStrLen(VariableInfo->VariableName)) != 0; stringPtr++)
			;
		stringPtr += EfiStrLen(VariableInfo->VariableName);
		stringPtr += EfiStrLen(L"=");
		status = NameValueGetHexStringAsBuffer (&buffer, stringPtr, Size);
	}else
	{
		for(stringPtr = result; *stringPtr != 0 && EfiStrnCmp(stringPtr, L"&VALUE=", EfiStrLen(L"&VALUE=")) != 0; stringPtr++)
			;
		stringPtr += EfiStrLen(L"&VALUE=");
		status = GetHexStringAsBuffer (&buffer, stringPtr);
	}


	if(EFI_ERROR(status))
	{
		goto DONE;
	}

	*Buffer = buffer;

DONE:
  if(configuration)
  {
  MemFreePointer(&configuration);
  }
  if(result)
  {
    MemFreePointer(&result);
  }
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiVarSetNvram
//
// Description:   
//
// Parameter:	    VARIABLE_INFO *VariableInfo, VOID *Buffer, UINTN Offset,
//					UINTN Size
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NameValueBufToHexString (IN OUT CHAR16 **, IN OUT UINTN *,  IN UINT8 *,  IN UINTN );
EFI_STATUS UefiVarSetNvram(VARIABLE_INFO *VariableInfo, VOID *Buffer, UINTN Offset, UINTN Size)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_STRING configuration = NULL;
	EFI_STRING progress = NULL;
	CHAR16 *tempBuffer = NULL;
	UINTN length = 0;
	UINTN finalLen = 0;
	UINTN bufLen = 1;
	BOOLEAN   PreservegEnableDrvNotification = FALSE;

  //
  //Construct the Configuration Header String
  //
  status = GetConfigHeader(VariableInfo, &configuration, &length);
  if(EFI_ERROR(status) || (configuration == NULL))//EIP-75384 Static Analysis
  {
    goto DONE;
  }

	if(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE)
	{
		UINTN len = length + EfiStrLen(L"&") + EfiStrLen(VariableInfo->VariableName) + EfiStrLen(L"=") + sizeof(CHAR16);
		configuration = MemReallocateZeroPool (configuration, length * sizeof(CHAR16), len * sizeof(CHAR16));
		if (configuration == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}
		EfiStrCat(configuration, L"&");
		EfiStrCat(configuration, VariableInfo->VariableName);
        EfiStrCat(configuration, L"=");
        length = EfiStrLen (configuration) * sizeof (CHAR16);
	}else
	{
        status = GetBlockName(&configuration, &length, Offset, Size);
		if(EFI_ERROR(status))
		{
			goto DONE;
		}
	}

  //
  // Get the Buffer as Hex String
  //
	if (!(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE))
	{
		tempBuffer = (UINT16*)EfiLibAllocateZeroPool(bufLen * sizeof(UINT16));
		if(tempBuffer == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}
		status = BufToHexString(tempBuffer, &bufLen, Buffer, Size);
		if(EFI_ERROR(status))
		{
			if(status != EFI_BUFFER_TOO_SMALL)
			{
				goto DONE;
			}
			if(tempBuffer)
			{
				MemFreePointer(&tempBuffer);
			}
			tempBuffer = (UINT16*)EfiLibAllocateZeroPool(bufLen * 2);
			if(tempBuffer == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}
		}
		status = BufToHexString(tempBuffer, &bufLen, Buffer, Size);
	}
	else
	{
		bufLen = 0;
		status = NameValueBufToHexString (&tempBuffer, &bufLen, Buffer, Size);
	}
	if(EFI_ERROR(status))
	{
		goto DONE;
	}

//
  // Calculate the total Configuration string length
  // <Config Hdr>&OFFSET=<HexChar>0&WIDTH=<HexChar>&VALUE=<HexChar><NULL>
  // |                       length                |  7   | bufLen |  1  |
  //
    if (!(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE))
    {
        finalLen = length + (bufLen * 2) + (EfiStrLen(L"&VALUE=") * sizeof(CHAR16));
    }
   else
    {             //<exislen> + <Var val> + <NULL>
        finalLen = length + bufLen + (2 * sizeof (CHAR16));			//Last 2 bytes for appending & and NULL
    }
    configuration = MemReallocateZeroPool(configuration, length, finalLen);
    if(configuration == NULL)
    {
        status = EFI_OUT_OF_RESOURCES;
        goto DONE;
    }
    if (!(VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE))
    {
        EfiStrCat(configuration, L"&VALUE=");
    }
    EfiStrCat(configuration, tempBuffer);
    if (VariableInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE)
    {
        EfiStrCat (configuration, L"&");
    }
    MemFreePointer(&tempBuffer);
    PreservegEnableDrvNotification =  gEnableDrvNotification; 
	 gEnableDrvNotification = TRUE; //EIP75588 Set to enable notification processing
    status = gHiiConfigRouting->RouteConfig (gHiiConfigRouting, configuration, &progress);
	 if(!PreservegEnableDrvNotification) // If gEnableDrvNotification is already True Don't touch it
		gEnableDrvNotification = FALSE; //Reset to disable notification processing
    MemFreePointer (&configuration);
DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    _ConstructConfigHdr
//
// Description:		Construct <ConfigHdr> using routing information GUID/NAME/PATH.
//
// Parameter:	  	IN OUT CHAR16 *ConfigHdr,
//                	IN OUT UINTN  *StrBufferLen,
//                	IN EFI_GUID   *Guid,
//                	IN CHAR16     *Name, OPTIONAL
//                	IN EFI_HANDLE *DriverHandle
//
// Return value:  	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _ConstructConfigHdr (
  IN OUT CHAR16                *ConfigHdr,
  IN OUT UINTN                 *StrBufferLen,
  IN EFI_GUID                  *Guid,
  IN CHAR16                    *Name, OPTIONAL
  IN EFI_HANDLE                *DriverHandle
  )
{
  EFI_STATUS                Status;
  UINTN                     NameStrLen;
  UINTN                     DevicePathSize;
  UINTN                     BufferSize;
  CHAR16                    *StrPtr;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;

  if (Name == NULL)
  {
    //
    // There will be no "NAME" in <ConfigHdr> for  Name/Value storage
    //
    NameStrLen = 0;
  } else
  {
    //
    // For buffer storage
    //
    NameStrLen = EfiStrLen (Name);
  }

  //
  // Retrieve DevicePath Protocol associated with this HiiPackageList
  //
  Status = gBS->HandleProtocol (
                  DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  &DevicePath
                  );
  if (EFI_ERROR (Status))
  {
    return Status;
  }

  DevicePathSize = EfiDevicePathSize (DevicePath);

  //
  // GUID=<HexCh>32&NAME=<Char>NameStrLen&PATH=<HexChar>DevicePathStrLen <NULL>
  // | 5  |   32   |  6  |  NameStrLen*4 |  6  |    DevicePathStrLen    | 1 |
  //
  BufferSize = (5 + 32 + 6 + NameStrLen * 4 + 6 + DevicePathSize * 2 + 1) * sizeof (CHAR16);
  if (*StrBufferLen < BufferSize)
  {
    *StrBufferLen = BufferSize;
    return EFI_BUFFER_TOO_SMALL;
  }

  *StrBufferLen = BufferSize;

  StrPtr = ConfigHdr;

  EfiStrCpy (StrPtr, L"GUID=");
  StrPtr += 5;
  BufferToHexString (StrPtr, (UINT8 *) Guid, sizeof (EFI_GUID));
  StrPtr += 32;

  //
  // Convert name string, e.g. name "ABCD" => "&NAME=0041004200430044"
  //
  EfiStrCpy (StrPtr, L"&NAME=");
  StrPtr += 6;
  if (Name != NULL)
  {
    BufferSize = (NameStrLen * 4 + 1) * sizeof (CHAR16);
    UnicodeToConfigString (StrPtr, &BufferSize, Name);
    StrPtr += (NameStrLen * 4);
  }

  EfiStrCpy (StrPtr, L"&PATH=");
  StrPtr += 6;
  BufferToHexString (StrPtr, (UINT8 *) DevicePath, DevicePathSize);

  return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    GetConfigHeader
//
// Description:
//
// Parameter:	  	VARIABLE_INFO *VariableInfo, EFI_STRING *Configuration, UINTN *Length
//
// Return value:  	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetConfigHeader(VARIABLE_INFO *VariableInfo, EFI_STRING *Configuration, UINTN *Length)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_STRING configuration = NULL;
  EFI_HANDLE driverHandle;
  UINTN length = 50;

  //
  // Initialize Protocols
  //
  status = HiiInitializeProtocol();
	if(EFI_ERROR(status))
	{
		goto DONE;
	}

  //
  // Retrieve the Device Path from Handle
  //
  status = gHiiDatabase->GetPackageListHandle(gHiiDatabase, VariableInfo->VariableHandle, &driverHandle);
	if(EFI_ERROR(status))
	{
		goto DONE;
	}

	// Allocate static memory of 50 Bytes, which will be freed if not used
	configuration = (UINT16*)EfiLibAllocateZeroPool(50);

  // Construct the Configuration Header String
  //
  status = _ConstructConfigHdr(configuration, &length, &VariableInfo->VariableGuid, VariableInfo->VariableName, driverHandle);
  if(EFI_ERROR(status))
  {
    if(status == EFI_BUFFER_TOO_SMALL)
    {
      MemFreePointer(&configuration);
      configuration = (UINT16*)EfiLibAllocateZeroPool(length);
      if(configuration == NULL)
      {
        status = EFI_OUT_OF_RESOURCES;
        goto DONE;
      }

      status = _ConstructConfigHdr(configuration, &length, &VariableInfo->VariableGuid, VariableInfo->VariableName, driverHandle);
    }
  }

	if(EFI_ERROR(status))
	{
		goto DONE;
	}

  if(*Configuration)
  {
    MemFreePointer(Configuration);
  }
  *Configuration = configuration;
  *Length = length;

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    GetBlockName
//
// Description:   
//
// Parameter:	    EFI_STRING *Configuration, UINTN *Length, UINTN Size
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetBlockName(EFI_STRING *Configuration, UINTN *Length, UINTN Offset, UINTN Size)
{
	EFI_STATUS status = EFI_SUCCESS;
  UINTN length = 0;
  UINTN finalLen = 0;
	CHAR16 *tempBuffer = NULL;

  length = (EfiStrLen(L"&OFFSET=") + sizeof(Offset) + EfiStrLen(L"&WIDTH=") + sizeof(Size) + 1) * sizeof(CHAR16);
  tempBuffer = (CHAR16*)EfiLibAllocateZeroPool(length);
  if(tempBuffer == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    goto DONE;
  }

  SPrint(tempBuffer, length, L"&OFFSET=%x&WIDTH=%x", Offset, Size);

  length = EfiStrLen(*Configuration) * sizeof(CHAR16);
  finalLen = (EfiStrLen(*Configuration) + EfiStrLen(tempBuffer) + 1) * sizeof(CHAR16);
  *Configuration = MemReallocateZeroPool(*Configuration, length, finalLen);
  if(*Configuration == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    goto DONE;
  }

  EfiStrCat(*Configuration, tempBuffer);

	MemFreePointer(&tempBuffer);
  *Length = finalLen;

DONE:
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    _VerifyResponseString
//
// Description:   Verifies Correctness of Response String. This is to prevent
//				  crashing if the result pointer is pointing to an invalid location.
//
// Parameter:	    EFI_STRING *Configuration
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _VerifyResponseString(EFI_STRING Configuration, BOOLEAN NameValue)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_STRING config = Configuration;
  CHAR16 *keyWord[] = {L"GUID=", L"&NAME=", L"&PATH=", L"&OFFSET=",L"&WIDTH=", L"&VALUE="};
  UINT32 i = 0;
  UINT32 count = NameValue? 3 : 6; // If Name Value Check only upto &Path else check until &Value.

  if(EfiStrnCmp(config, keyWord[i], EfiStrLen(keyWord[i])) != 0)
  {
    status = EFI_NOT_FOUND;
    goto DONE;
  }

  for(i = 1; i < count; i++)
  {
    for(;EfiStrnCmp(config, keyWord[i], EfiStrLen(keyWord[i])) != 0 && (config != (Configuration + EfiStrLen(Configuration))); config++)
      ;
    if(EfiStrnCmp(config, keyWord[i], EfiStrLen(keyWord[i])) != 0)
    {
      status = EFI_NOT_FOUND;
      goto DONE;
    }
  }

DONE:
  return status;
}

#if !TSE_USE_EDK_LIBRARY
VOID
EfiLibSafeFreePool (
  IN  VOID             *Buffer
  )
{
MemFreePointer(&Buffer);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:		GetHexStringAsBuffer
//
// Description:
//
// Parameter:		CHAR8 *Buffer
//					UINT16 *HexStringBuffer
//					UINTN Size
//
// Return value:	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetHexStringAsBuffer(UINT8 **Buffer, CHAR16 *HexStringBuffer)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN bufLength = 0;
	UINTN convertedStrLen = 0;

	status = HexStringToBuf(*Buffer, &bufLength, HexStringBuffer, &convertedStrLen);
	if(EFI_ERROR(status))
	{
		if(status == EFI_BUFFER_TOO_SMALL)
		{
			if(*Buffer)
			{
				MemFreePointer(Buffer);
			}
			*Buffer = EfiLibAllocateZeroPool(bufLength);
			if(*Buffer == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}
		}else
		{
			goto DONE;
		}
	  status = HexStringToBuf(*Buffer, &bufLength, HexStringBuffer, &convertedStrLen);
	}

DONE:
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:		NameValueGetHexStringAsBuffer
//
// Description:
//
// Parameter:		CHAR8 *Buffer
//					UINT16 *HexStringBuffer
//					UINTN Size
//
// Return value:	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NameValueHexStringToBuf (IN OUT UINT8 *, IN OUT UINTN *Len,IN CHAR16 *, OUT UINTN *);
EFI_STATUS NameValueGetHexStringAsBuffer (UINT8 **Buffer, CHAR16 *HexStringBuffer, UINTN Size)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN bufLength = 0;
	UINTN convertedStrLen = 0;

	if (Size <= sizeof  (UINT64))
	{
		GetHexStringAsBuffer (Buffer, HexStringBuffer);
	}
	else
	{
		status = NameValueHexStringToBuf (*Buffer, &bufLength, HexStringBuffer, &convertedStrLen);
		if(EFI_ERROR(status))
		{
			if(status == EFI_BUFFER_TOO_SMALL)
			{
				if(*Buffer)
				{
					MemFreePointer(Buffer);
				}
				bufLength = (Size > bufLength) ? Size : bufLength;
				*Buffer = EfiLibAllocateZeroPool(bufLength);
				if(*Buffer == NULL)
				{
					status = EFI_OUT_OF_RESOURCES;
					goto DONE;
				}
			}else
			{
				goto DONE;
			}
		  status = NameValueHexStringToBuf (*Buffer, &bufLength, HexStringBuffer, &convertedStrLen);
		}
	}
DONE:
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    HiiExtendedInitializeProtocol
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS
//					EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiExtendedInitializeProtocol()
{
	EFI_STATUS status = EFI_SUCCESS;

	if (gHiiInitialized)
	{
		goto DONE;
	}

	status = gBS->LocateProtocol(&gEfiHiiConfigRoutingProtocolGuid, NULL, &gHiiConfigRouting);
	if(EFI_ERROR(status))
	{
		goto DONE;
	}

	gHiiInitialized = TRUE;

DONE:
	return status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    GetControlConditionVariable
//
// Description:
//
// Parameter:	    CONTROL_INFO *ControlInfo
//
// Return value:  	UINT32
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetControlConditionVariable(CONTROL_INFO *ControlInfo)
{
	EFI_IFR_OP_HEADER *ifrPtr;
	PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[ControlInfo->ControlPageID]);
	UINTN control = 0;
	CONTROL_INFO *CtrlInfo;
	BOOLEAN found = FALSE;
	EFI_QUESTION_ID  QuestionId;
	UINT32 varId = 0;

	if ( ControlInfo == NULL )
		return 0;

	ifrPtr = (EFI_IFR_OP_HEADER *)ControlInfo->ControlConditionalPtr;

	if ( ifrPtr == NULL )
		return 0;
																			
	if ( ( ifrPtr->OpCode != EFI_IFR_SUPPRESS_IF_OP ) && ( ifrPtr->OpCode != EFI_IFR_GRAY_OUT_IF_OP ) )
		return 0;

	ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length);
	// skip NOT if it is present
	if ( ifrPtr->OpCode == EFI_IFR_NOT_OP )
		ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length);

	if ( ifrPtr->OpCode == EFI_IFR_EQ_ID_LIST_OP )
		QuestionId = ((EFI_IFR_EQ_ID_LIST *)ifrPtr)->QuestionId;
	else if ( ifrPtr->OpCode == EFI_IFR_EQ_ID_VAL_OP )
		QuestionId = ((EFI_IFR_EQ_ID_VAL *)ifrPtr)->QuestionId;
	else
		return 0;

	if(pageInfo->PageHandle ==0)
		return 0;

	for ( control= 0; (control < pageInfo->PageControls.ControlCount) && (found == FALSE); control++ )
	{
		CtrlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

		if(QuestionId == CtrlInfo->ControlKey)
		{
			varId = CtrlInfo->ControlVariable;
			found = TRUE;
		}
	}
	if(!found)
		return 0;

	return varId;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    HiiRemoveString
//
// Description:
//
// Parameter:	    EFI_HII_HANDLE Handle, UINT16 Token
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HiiRemoveString(EFI_HII_HANDLE Handle, UINT16 Token)
{
  UINT32 i = 0;
  CHAR16 *nullString = NULL;

	for ( i = 0; i < gLangCount; i++ )
  {
  	HiiChangeStringLanguage( Handle, Token, gLanguages[i].Unicode, nullString );
  }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiIsEfiVariable
//
// Description:
//
// Parameter:	    UINT32 variable, VARIABLE_INFO *varInfo
//
// Return value:  	BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN UefiIsEfiVariable(UINT32 variable, VARIABLE_INFO *varInfo)
{
	if (varInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_EFI_VARSTORE ||
		variable == VARIABLE_ID_LANGUAGE ||
		variable == VARIABLE_ID_DEL_BOOT_OPTION ||
		variable == VARIABLE_ID_ADD_BOOT_OPTION ||
		variable == VARIABLE_ID_BOOT_MANAGER ||
		variable == VARIABLE_ID_BOOT_NOW ||
		variable == VARIABLE_ID_LEGACY_DEV_INFO ||
		variable == VARIABLE_ID_LEGACY_GROUP_INFO ||
    	variable == VARIABLE_ID_BOOT_TIMEOUT ||
		variable == VARIABLE_ID_BOOT_ORDER ||
		variable == VARIABLE_ID_AMI_CALLBACK ||
		variable == VARIABLE_ID_AMITSESETUP ||
		variable == VARIABLE_ID_ERROR_MANAGER ||
		variable == VARIABLE_ID_USER_DEFAULTS ||
		variable == VARIABLE_ID_BBS_ORDER ||
		variable == VARIABLE_ID_DRIVER_MANAGER ||
		variable == VARIABLE_ID_DRIVER_ORDER || 
		variable == VARIABLE_ID_ADD_DRIVER_OPTION ||			//EIP70421 Support for driver order
		variable == VARIABLE_ID_DEL_DRIVER_OPTION ||
		variable == VARIABLE_ID_IDE_SECURITY)	
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

EFI_HII_PACKAGE_LIST_HEADER *
PreparePackageList (
  IN UINTN                    NumberOfPackages,
  IN EFI_GUID                 *GuidId,
  ...
  );

#if APTIO_4_00 != 1 && SETUP_USE_GUIDED_SECTION !=1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    InitMiniSetupStrings
//
// Description:
//
// Parameter:	    VOID
//
// Return value:  	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitMiniSetupStrings( VOID )
{
	EFI_STATUS          Status=EFI_SUCCESS;
	UINT16              Index = 0;
  	EFI_HII_PACKAGE_LIST_HEADER     *PackageList=NULL;
#ifdef STANDALONE_APPLICATION
	EFI_GUID            MiniSetupGuid = ENVIRONMENT_VARIABLE_ID ;
#else
    EFI_GUID            MiniSetupGuid = MINI_SETUP_GUID ;
#endif
	Status = HiiInitializeProtocol();
	if ( EFI_ERROR ( Status ) )
		return Status;

	gHiiHandle = HiiFindHandle( &MiniSetupGuid, &Index );

	if(gHiiHandle != INVALID_HANDLE){ //Remove the previous pack installed with this GUID
		Status = gHiiDatabase->RemovePackageList(gHiiDatabase, gHiiHandle);
		gHiiHandle = INVALID_HANDLE;
	}

	if ( gHiiHandle == INVALID_HANDLE )
	{
	  PackageList = PreparePackageList (
	                  1,
	                  &MiniSetupGuid,
	                  STRING_ARRAY_NAME
	                  );
	  if (PackageList == NULL) {
	    return EFI_OUT_OF_RESOURCES;
	  }
	
	  Status = gHiiDatabase->NewPackageList (
	                          gHiiDatabase,
	                          PackageList,
	                          gImageHandle,
	                          &gHiiHandle
	                          );
	} 

	return Status;
}
#endif


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    HiiGetManufactuingMask
//
// Description:
//
// Parameter:	    VOID
//
// Return value:  	UINTN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN HiiGetManufactuingMask(VOID)
{
	return AMI_FLAG_MANUFACTURING;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    HiiGetDefaultMask
//
// Description:
//
// Parameter:	    VOID
//
// Return value:  	UINTN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN HiiGetDefaultMask(VOID)
{
	return AMI_FLAG_DEFAULT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    GetControlConditionVarId
//
// Description:
//
// Parameter:	    CONTROL_INFO *controlInfo
//
// Return value:  	UINT32
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetControlConditionVarId(CONTROL_INFO *controlInfo)
{
	EFI_IFR_OP_HEADER *ifrPtr;
	PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[controlInfo->ControlPageID]);
	UINTN control = 0;
	CONTROL_INFO *CtrlInfo;
	BOOLEAN found = FALSE;
	EFI_QUESTION_ID  QuestionId;
	UINT32 varId = 0;

	if ( controlInfo == NULL )
		return 0;

	ifrPtr = (EFI_IFR_OP_HEADER *)controlInfo->ControlConditionalPtr;

	if ( ifrPtr == NULL )
		return 0;
																			
	if ( ( ifrPtr->OpCode != EFI_IFR_SUPPRESS_IF_OP ) && ( ifrPtr->OpCode != EFI_IFR_GRAY_OUT_IF_OP ) )
		return 0;

	ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length);
	// skip NOT if it is present
	if ( ifrPtr->OpCode == EFI_IFR_NOT_OP )
		ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length);

	if ( ifrPtr->OpCode == EFI_IFR_EQ_ID_LIST_OP )
		QuestionId = ((EFI_IFR_EQ_ID_LIST *)ifrPtr)->QuestionId;
	else if ( ifrPtr->OpCode == EFI_IFR_EQ_ID_VAL_OP )
		QuestionId = ((EFI_IFR_EQ_ID_VAL *)ifrPtr)->QuestionId;
	else
		return 0;

	if(pageInfo->PageHandle ==0)
		return 0;

	for ( control= 0; (control < pageInfo->PageControls.ControlCount) && (found == FALSE); control++ )
	{
		CtrlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

		if(QuestionId == CtrlInfo->ControlKey)
		{
			varId = CtrlInfo->ControlVariable;
			found = TRUE;
		}
	}
  if(!found)
  {
    // Control Definition not in this Page. Look within the formset
    EFI_HII_HANDLE pgHandle = controlInfo->ControlHandle;
    UINT32 page = 0;

    for(;page < gPages->PageCount && (found == FALSE); page++)
    {
      if(page == controlInfo->ControlPageID)
      {
        continue;
      }
      pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[page]);
      if(pageInfo->PageHandle != pgHandle)
      {
        continue;
      }

      for(control = 0; control < pageInfo->PageControls.ControlCount && (found == FALSE); control++)
      {
        controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

        if(QuestionId == controlInfo->ControlKey)
        {
          varId = controlInfo->ControlVariable;
          found = TRUE;
        }
      }
    }
  }

	if(!found)
		return 0;

	return varId;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure	:	ProcessActionQuestionConfiguration
//
// Description	:	Function to process Action Control Configuration String.
//
// Input		:	CONTROL_INFO *control
//
// Output		:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessActionQuestionConfiguration(CONTROL_INFO *control)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_STRING configuration = NULL;
  EFI_STRING progress = NULL;
  EFI_IFR_ACTION *UefiAction = NULL;
  BOOLEAN PreservegEnableDrvNotification = FALSE;

    if((control == NULL) || (control->ControlPtr == NULL)){ 
	  Status = EFI_UNSUPPORTED;
	  goto DONE;
  	}
  UefiAction = (EFI_IFR_ACTION*)control->ControlPtr;

  if(UefiAction->Header.Length == sizeof(EFI_IFR_ACTION))
  {
    if(UefiAction->QuestionConfig)
    {
      //Process UefiAction QuestionConfig
      configuration = HiiGetString(control->ControlHandle, UefiAction->QuestionConfig);
	  if((configuration != NULL) && EfiStrLen(configuration))
	  {
		  PreservegEnableDrvNotification = gEnableDrvNotification;
        gEnableDrvNotification = TRUE; //EIP75588 Set to enable notification processing
		  Status = gHiiConfigRouting->RouteConfig(gHiiConfigRouting, configuration, &progress);
		  if (!PreservegEnableDrvNotification) // If gEnableDrvNotification is already True Don't touch it
        	gEnableDrvNotification = FALSE; //Reset to disable notification processing
		  MemFreePointer(&configuration);
	  }
    }
  }
DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     ProcessBrowserActionRequest
//
// Description:   
//
// Parameter:     EFI_BROWSER_ACTION_REQUEST actionReq
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiVarsetnvramforCurrentform(UINT32 FormID);
EFI_STATUS UefiLoadPreviousValuesforCurrentform(UINT32 FormID);
VOID HotclickESCaction(VOID);
extern BOOLEAN BrowserActionDiscard;
EFI_STATUS ProcessBrowserActionRequest(EFI_BROWSER_ACTION_REQUEST ActionReq)
{

  switch(ActionReq)
  {
  case EFI_BROWSER_ACTION_REQUEST_RESET:
    // Do nothing. Reset the system.
    gApp->Quit = ResetSys();
    break;
  case EFI_BROWSER_ACTION_REQUEST_SUBMIT:
    //Save values here before exiting.
    gApp->Quit = SaveAndExit();
    break;
  case EFI_BROWSER_ACTION_REQUEST_EXIT:
    //Donot save values. Exit as is.
    gApp->Quit = ExitApplication();
    break;
	//EIP 86885 : START
	//Changes to support new action request form browser
  case EFI_BROWSER_ACTION_REQUEST_FORM_SUBMIT_EXIT:
	UefiVarsetnvramforCurrentform (gApp->CurrentPage) ;
	HotclickESCaction();
	break;
  case EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD_EXIT:
	BrowserActionDiscard = TRUE;
	UefiLoadPreviousValuesforCurrentform (gApp->CurrentPage);
	HotclickESCaction();
	break;
  case EFI_BROWSER_ACTION_REQUEST_FORM_APPLY:
	UefiVarsetnvramforCurrentform (gApp->CurrentPage) ;
	break;
  case EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD:
	BrowserActionDiscard = TRUE;
	UefiLoadPreviousValuesforCurrentform (gApp->CurrentPage);
	break;
	//EIP 86885 : END
  default:
    break;
  }
//  gProFormOffset = 0;				//EIP 86885
  CleargProcessedForms ();
//  MemSet (gProcessedForms, MAX_FORMS_TO_PROCESS, 0);
		
  return EFI_SUCCESS;
}

VOID* UefiGetSpecialEqIDIfrPtr(CONTROL_INFO *ControlInfo, UINT32 *Variable, GUID_INFO **GuidInfo)
{
    VOID *Conditional = ControlInfo->ControlConditionalPtr;
    VOID *ControlPtr = ControlInfo->ControlPtr;
    EFI_IFR_OP_HEADER * OpHeader = (EFI_IFR_OP_HEADER *)Conditional;
    GUID_INFO *specialGuid = NULL;
    VARIABLE_INFO *varInfo = NULL;
    UINT32 i = 0;
    UINT8 InScope = 0;

    if((OpHeader==NULL) || (ControlPtr <= Conditional))
        return NULL;

    if ((OpHeader != NULL) &&
    ((OpHeader->OpCode == EFI_IFR_SUPPRESS_IF_OP) ||
     (OpHeader->OpCode == EFI_IFR_GRAY_OUT_IF_OP)))
    {
        do
        {
            if(OpHeader->Scope)
            {
                InScope++;
            }
            if(OpHeader->OpCode == EFI_IFR_END_OP)
            {
                InScope--;
                if(InScope == 0)
                {
                    // EFI_IFR_EQ_ID_VAL_OP opcode not found
                    OpHeader = NULL;
                    goto DONE;
                }
            }
            OpHeader = (EFI_IFR_OP_HEADER*)((UINT8*)OpHeader + OpHeader->Length);
        }while((OpHeader->OpCode != EFI_IFR_EQ_ID_VAL_OP) &&
            (OpHeader->OpCode != EFI_IFR_EQ_ID_LIST_OP));
    }

	if(NoVarStoreSupport())
	{
	    if(*Variable == VARIABLE_ID_SETUP)
	    {
			*Variable = FindVarFromITKQuestionId(UefiGetEqIDQuestionID(OpHeader));
	    }
	}

  // Retrieve Special Control Information??? Update with proper comment
  varInfo = VarGetVariableInfoIndex( *Variable );
	if( varInfo == NULL )
  {
    OpHeader = NULL;
		goto DONE;
  }

	for ( i = 0; i < gGuidList->GuidCount; i++ )
	{
		GUID_INFO *guidInfo = (GUID_INFO *)((UINTN)gGuidList + gGuidList->GuidList[i]);
		if ( EfiCompareGuid( &varInfo->VariableGuid, &guidInfo->GuidValue ) )
		{
			specialGuid = guidInfo;
			break;
		}
	}

	if ( specialGuid != NULL )
	{
		if ( GuidInfo != NULL )
			*GuidInfo = specialGuid;
	}
	else
	{
		OpHeader = NULL;
	}

    // See if Other condition is Special condition
    if(OpHeader == NULL)
    {
        if(ControlPtr > Conditional)
        {
            UINTN Offset = _SkipExpression(Conditional);
            if(Offset)
            {
                Conditional = (VOID*)((UINTN)Conditional + Offset);
                if(ControlPtr > Conditional)
                {
                     CONTROL_INFO TempCtlInfo;
                     MemCopy(&TempCtlInfo, ControlInfo, sizeof (CONTROL_INFO));
                     TempCtlInfo.ControlConditionalPtr = Conditional;
                     *Variable = (UINT16)GetControlConditionVarId(&TempCtlInfo);
                     OpHeader = UefiGetSpecialEqIDIfrPtr(&TempCtlInfo, Variable, GuidInfo)  ;
                }
            }
        }
    }

DONE:
  return OpHeader;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetSpecialEqIDValue
//
// Description:
//
// Parameter:	    CONTROL_INFO *ControlInfo, GUID_INFO **GuidInfo
//
// Return value:  	UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetSpecialEqIDValue(CONTROL_INFO *ControlInfo, GUID_INFO **GuidInfo)
{
  UINT16 value = (UINT16)-2;
  UINT32 condVarID = 0;
  EFI_IFR_OP_HEADER *ifrPtr = NULL;

  condVarID = (UINT32)GetControlConditionVarId(ControlInfo);
  ifrPtr = (EFI_IFR_OP_HEADER *)UefiGetSpecialEqIDIfrPtr(ControlInfo, &condVarID, GuidInfo);

  if(ifrPtr != NULL)
  {
    switch(ifrPtr->OpCode)
    {
    case EFI_IFR_EQ_ID_LIST_OP:
      value = ((EFI_IFR_EQ_ID_LIST *)ifrPtr)->ValueList[0];
      break;
    case EFI_IFR_EQ_ID_VAL_OP:
      value = ((EFI_IFR_EQ_ID_VAL *)ifrPtr)->Value;
      break;
    default:
      break;
    }
  }

  return value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetEqIDValue
//
// Description:
//
// Parameter:	    VOID *IfrPtr, UINT16 Value
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetEqIDValue(VOID *IfrPtr, UINT16 Value)
{
  EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)IfrPtr;

  switch(opHeader->OpCode)
  {
  case EFI_IFR_EQ_ID_LIST_OP:
    ((EFI_IFR_EQ_ID_LIST *)IfrPtr)->ValueList[0] = Value;
    break;
  case EFI_IFR_EQ_ID_VAL_OP:
    ((EFI_IFR_EQ_ID_VAL *)IfrPtr)->Value = Value;
    break;
  default:
    break;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiIsOneOfControl
//
// Description:
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  	BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN UefiIsOneOfControl(VOID *IfrPtr)
{
  return (((EFI_IFR_OP_HEADER *)IfrPtr)->OpCode == EFI_IFR_ONE_OF_OP)? TRUE : FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiUpdateControlVarOffset
//
// Description:
//
// Parameter:	    VOID *IfrPtr, UINT16 Value
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiUpdateControlVarOffset(VOID *IfrPtr, UINT16 Value)
{
  EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)IfrPtr;

  switch(opHeader->OpCode)
  {
  case EFI_IFR_ONE_OF_OP:
    ((EFI_IFR_ONE_OF *)opHeader)->Question.VarStoreInfo.VarOffset = Value;
    break;
  default:
    break;
  }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiCreateOneOfWithOptionsTemplate
//
// Description:
//
// Parameter:	    UINTN OptionCount, CONTROL_INFO *CtrlInfo
//
// Return value:  	VOID*
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* UefiCreateOneOfWithOptionsTemplate(UINTN OptionCount, CONTROL_INFO *CtrlInfo)
{
  VOID *buffer = NULL;
  UINTN size = 0;
  UINTN length = 0;
  UINTN offset;

  offset = (UINTN)CtrlInfo->ControlPtr - (UINTN)CtrlInfo->ControlConditionalPtr;

  size = offset + sizeof(EFI_IFR_ONE_OF) + sizeof(EFI_IFR_OP_HEADER) +
	 OptionCount * sizeof(EFI_IFR_ONE_OF_OPTION);
  buffer = EfiLibAllocateZeroPool(size);
  if(buffer == NULL)
  {
    goto DONE;
  }
  MemCopy(buffer, CtrlInfo->ControlConditionalPtr, offset);

  length = UefiGetIfrLength(CtrlInfo->ControlPtr);
  CtrlInfo->ControlConditionalPtr = buffer;
  MemCopy( (UINT8 *)buffer + offset, CtrlInfo->ControlPtr, length );
  CtrlInfo->ControlPtr = (UINT8 *)buffer + offset;

DONE:
  return (UINT8 *)buffer + offset;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetOneOfOption
//
// Description:
//
// Parameter:	    VOID *IfrPtr, UINT64 Value, UINT32 Size, UINT8 Flag, UINT16 Option
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetOneOfOption(VOID *IfrPtr, UINT64 Value, UINT32 Size, UINT8 Flag, UINT16 Option)
{
  EFI_IFR_ONE_OF_OPTION *option = (EFI_IFR_ONE_OF_OPTION *)IfrPtr;
  UINT8 flag = 0;

  flag |= ((Flag & AMI_FLAG_DEFAULT) == AMI_FLAG_DEFAULT)? EFI_IFR_OPTION_DEFAULT : 0;
  flag |= ((Flag & AMI_FLAG_MANUFACTURING) == AMI_FLAG_MANUFACTURING)? EFI_IFR_OPTION_DEFAULT_MFG : 0;

  switch(Size)
  {
  case sizeof(UINT8):
    flag |= EFI_IFR_TYPE_NUM_SIZE_8;
    option->Value.u8 = (UINT8)Value;
    break;
  case sizeof(UINT16):
    flag |= EFI_IFR_TYPE_NUM_SIZE_16;
    option->Value.u16 = (UINT16)Value;
    break;
  case sizeof(UINT32):
    flag |= EFI_IFR_TYPE_NUM_SIZE_32;
    option->Value.u32 = (UINT32)Value;
    break;
  case sizeof(UINT64):
    flag |= EFI_IFR_TYPE_NUM_SIZE_64;
    option->Value.u64 = (UINT64)Value;
    break;
  default:
    break;
  }

  option->Flags = flag;
  option->Option = Option;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiAddEndOp
//
// Description:
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiAddEndOp(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *opHeader =  (EFI_IFR_OP_HEADER *)IfrPtr;

  opHeader->OpCode = EFI_IFR_END_OP;
  opHeader->Length = sizeof(EFI_IFR_OP_HEADER);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetQuestionID
//
// Description:
//
// Parameter:	    CONTROL_INFO *Control
//
// Return value:  	UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetQuestionID(CONTROL_INFO *Control)
{
	return 0; //(UINT16)GetControlConditionVarId(Control);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiCreateDynamicControlCondition
//
// Description:
//
// Parameter:	    CONTROL_INFO *control,UINT16 VarId, UINT16 PrevControlQuestionID,UINT16 Value
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiCreateDynamicControlCondition(CONTROL_INFO *control,UINT16 VarId, UINT16 PrevControlQuestionID,UINT16 Value)
{
	//Add condition here for boot and bbs special controls
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetEqIDQuestionID
//
// Description:
//
// Parameter:	    VOID *IfrPtr
//
// Return value:  	UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetEqIDQuestionID(VOID *IfrPtr)
{
  UINT16 questionID = 0;

  return questionID;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetEqIDQuestionID
//
// Description:
//
// Parameter:	    VOID *IfrPtr, UINT16 Value
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetEqIDQuestionID(VOID *IfrPtr, UINT16 Value)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiUpdateControlQuestionID
//
// Description:
//
// Parameter:	    VOID *IfrPtr, UINT16 Value
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiUpdateControlQuestionID(VOID *IfrPtr, UINT16 Value)
{
  EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)IfrPtr;

  switch(opHeader->OpCode)
  {
  case EFI_IFR_ONE_OF_OP:
    ((EFI_IFR_ONE_OF *)opHeader)->Question.QuestionId = Value;
    break;
  default:
    break;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSpecialGuidCallback
//
// Description:
//
// Parameter:	    VOID * HiiHandle, UINT16 Key, EFI_GUID *pGUID
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSpecialGuidCallback(VOID * HiiHandle, UINT16 Key, EFI_GUID *pGUID)
{
	EFI_HANDLE DriverHandle;
	EFI_GUID EfiHiiConfigAccessProtocolGuid = EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID;
	EFI_HII_CONFIG_ACCESS_PROTOCOL	*ConfigAccess;
	EFI_IFR_TYPE_VALUE	Value;
	EFI_BROWSER_ACTION_REQUEST ActionReq;
	EFI_STATUS	Status;
   BOOLEAN PreservegEnableDrvNotification = FALSE;

	Status = gHiiDatabase->GetPackageListHandle(gHiiDatabase,HiiHandle,&DriverHandle);
	if(!EFI_ERROR(Status))
	{
		Status = gBS->HandleProtocol( DriverHandle, &EfiHiiConfigAccessProtocolGuid , &ConfigAccess );
		if(!EFI_ERROR(Status))
		{
			EFI_BROWSER_ACTION action = EFI_BROWSER_ACTION_CHANGED;

			MemSet( &Value, sizeof(Value), 0 );
			Value.u64 = (UINTN)pGUID;
		   PreservegEnableDrvNotification = gEnableDrvNotification;
			gEnableDrvNotification = TRUE; //EIP75588 Set to enable notification processing
			Status = ConfigAccess->Callback(ConfigAccess, action,Key,((sizeof(VOID*)==sizeof(UINT32))?EFI_IFR_TYPE_NUM_SIZE_32:EFI_IFR_TYPE_NUM_SIZE_64),&Value,&ActionReq);
		   if (!PreservegEnableDrvNotification) // If gEnableDrvNotification is already True Don't touch it
			  gEnableDrvNotification = FALSE; //Reset to disable notification processing
            // Clean up PAGE_INFO struct with Handle set to 0xFFFF  
            Status = FixSetupData();
            if(EFI_ERROR(Status))
            {
            }
		}
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetWidth
//
// Description:
//
// Parameter:	    VOID *IfrPtr,UINT8 Width
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetWidth(VOID *IfrPtr,UINT8 Width)
{
  EFI_IFR_OP_HEADER *OpHeader = (EFI_IFR_OP_HEADER*)IfrPtr;

  switch(OpHeader->OpCode)
  {
	case EFI_IFR_NUMERIC_OP:
		break;
	case EFI_IFR_PASSWORD_OP:
		break;
	case EFI_IFR_STRING_OP:
		break;
	case EFI_IFR_ONE_OF_OP:
		break;
	case EFI_IFR_CHECKBOX_OP:
		break;
  default:
    break;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    BBSUpdateControlOffset
//
// Description:
//
// Parameter:	    CONTROL_INFO *control
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID   BBSUpdateControlOffset(CONTROL_INFO *control)
{
    UINT16 offset=  ((EFI_IFR_ONE_OF*)control->ControlPtr)->Question.VarStoreInfo.VarOffset;

    offset = offset +sizeof(UINT32)+sizeof(UINT16);
    offset = (UINT16)(offset + gCurrLegacyBootData->LegacyEntryOffset);

	UefiUpdateControlVarOffset(control->ControlPtr, offset);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		GetControlDataLength
//
// Description:	This function will return width of questions
//
// Parameter:		CONTROL_INFO *
//
// Return value:	UINTN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN GetControlDataLength(CONTROL_INFO *controlInfo)
{
  UINTN width = 0;

  switch(controlInfo->ControlType)
  {
  case CONTROL_TYPE_CHECKBOX:
  case CONTROL_TYPE_POPUPSEL:
  case CONTROL_TYPE_NUMERIC:
  case CONTROL_TYPE_PASSWORD:
  case CONTROL_TYPE_POPUP_STRING:
    width = UefiGetWidth(controlInfo->ControlPtr);
    break;
  case CONTROL_TYPE_ORDERED_LIST:
    width = (((EFI_IFR_ORDERED_LIST*)(controlInfo->ControlPtr))->MaxContainers);
    break;
  case CONTROL_TYPE_TEXT:
    width = sizeof(UINT16);
    break;
  case CONTROL_TYPE_DATE:
    width = sizeof(EFI_HII_DATE);
    break;
  case CONTROL_TYPE_TIME:
    width = sizeof(EFI_HII_TIME);
    break;
  default:
    break;
  }
  return width;
}


//EIP 23354 : Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsPasswordEncodeEnabled
//
// Description:	Function to return Password Encoding Status.
//
// Input:		CONTROL_INFO
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsPasswordEncodeEnabled (CONTROL_INFO *controlInfo)
{
//EIP106950 : Starts
	extern PASSWORD_ENOCDE_LIST_TEMPLATE gPasswordEncodeList [];
	extern UINT32 gEncodeListCount;
	UINT32 iIndex = 0;
	EFI_GUID tFormsetGuid;

	//Get page info
//	PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[controlInfo->ControlPageID]);

	//Get FormsetGuid
	GetPageGuidFromPgIndex (controlInfo->ControlPageID, &tFormsetGuid);
		
	for (iIndex = 0; iIndex < gEncodeListCount; iIndex ++)
	{
		//If given QuestionId and FormsetGuid is same then return Encoding Flag
		if ( (gPasswordEncodeList [iIndex].QuestionID == ((EFI_IFR_PASSWORD *)controlInfo->ControlPtr)->Question.QuestionId) &&
				(EfiCompareGuid(&gPasswordEncodeList [iIndex].FormsetGuid, &tFormsetGuid) )
			)
		{
			return gPasswordEncodeList [iIndex].EncodingFlag;
		}
	}
//EIP106950 : Ends
	
	// IDE Password Encode the password
	if (
      (VARIABLE_ID_IDE_SECURITY == controlInfo->ControlVariable) ||
	   (VARIABLE_ID_AMITSESETUP == controlInfo->ControlVariable)
      )
   {
		return TRUE;
   }
	return FALSE;
}

//EIP 23354 : End
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetTime
//
// Description:     Function to get time
//
// Parameter:	    CONTROL_INFO *control, EFI_TIME *Tm
//
// Return value:    STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiGetTime(CONTROL_INFO *control, EFI_TIME *Tm)
{
  VOID *IfrPtr = NULL ;
  UINT8 Flags ;
  EFI_STATUS Status = EFI_UNSUPPORTED;	


  if((control != NULL) && (control->ControlPtr != NULL))
  {
	IfrPtr = control->ControlPtr; 
  	Flags = UefiGetFlagsField(IfrPtr) ;


  	if( ((Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_TIME)||
	    ((Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_TIME)  )// EIP 77875 : Incorrect logic used to check Time and Date control types
  	{
		Status = gRT->GetTime( Tm, NULL );
 	}
  	else if( ((Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_NORMAL) ||
		 ((Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_NORMAL)   )// EIP 77875 : Incorrect logic used to check Time and Date control types
  	{
		
		if(control->ControlType == CONTROL_TYPE_DATE)
		{	
			EFI_HII_DATE *date = NULL ;	

			date = EfiLibAllocateZeroPool( sizeof(EFI_HII_DATE) );
			
			if ( date != NULL )
			{	
				Status = VarGetValue( control->ControlVariable, UefiGetQuestionOffset(IfrPtr), UefiGetWidth(IfrPtr), date );
				if ( ! EFI_ERROR( Status ) )
				{
					Tm->Month = date->Month ;
					Tm->Day = date->Day ;
					Tm->Year = date->Year ;
				}

				MemFreePointer( (VOID **)&date );
			}
		}else{
			EFI_HII_TIME *time = NULL ;
			
			time = EfiLibAllocateZeroPool( sizeof(EFI_HII_TIME) );

			if ( time != NULL )
			{	
				Status = VarGetValue( control->ControlVariable, UefiGetQuestionOffset(IfrPtr), UefiGetWidth(IfrPtr), time );
				Tm->Hour = time->Hour ;
				Tm->Minute = time->Minute ;
				Tm->Second = time->Second ;
				
				MemFreePointer( (VOID **)&time );
			}
		}
	}
	else if( ((Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_WAKEUP) ||
		 ((Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_WAKEUP) )// EIP 77875 : Incorrect logic used to check Time and Date control types
  	{
		
		BOOLEAN Enabled;
		BOOLEAN Pending;
		Status = gRT->GetWakeupTime( &Enabled, &Pending, Tm );
	}
  }
  else	
	Status = gRT->GetTime( Tm, NULL );

  return Status ;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetTime
//
// Description:	    Function to set time
//
// Parameter:	    CONTROL_INFO *control, EFI_TIME *Tm
//
// Return value:    STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiSetTime(CONTROL_INFO *control, EFI_TIME *Tm)
{
  VOID *IfrPtr = NULL ;
  UINT8 Flags = 0;
  EFI_STATUS Status = EFI_UNSUPPORTED;	  
  	

  if((control != NULL) && (control->ControlPtr != NULL))
  {
	IfrPtr = control->ControlPtr; 
  	Flags = UefiGetFlagsField(IfrPtr) ;

  	if( ((Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_TIME)||
	    ((Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_TIME)  )// EIP 77875 : Incorrect logic used to check Time and Date control types
  	{
		Status = gRT->SetTime( Tm );
 	}
  	else if( ((Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_NORMAL) ||
		 ((Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_NORMAL)   )// EIP 77875 : Incorrect logic used to check Time and Date control types
  	{
		if(control->ControlType == CONTROL_TYPE_DATE)
		{	
			EFI_HII_DATE *date = NULL ;	
			EFI_TIME Tc ;

			date = EfiLibAllocateZeroPool( sizeof(EFI_HII_DATE) );

			if ( date != NULL )
			{
//EIP 47037 : Start
				UefiGetTime(control, &Tc);				
				date->Month = (Tm->Month <= 12)?Tm->Month : ((Tc.Month>12)? 1:Tc.Month) ;
				date->Day = (Tm->Day <= 31)?Tm->Day : ((Tc.Day>31)? 1:Tc.Day) ;
				date->Year = Tm->Year ;	
//EIP 47037 : End		
				Status = VarSetValue( control->ControlVariable, UefiGetQuestionOffset(IfrPtr), UefiGetWidth(IfrPtr), date );

				MemFreePointer( (VOID **)&date );
			}
			
		}else{
			EFI_HII_TIME *time = NULL ;	
			EFI_TIME Tc ;

			time = EfiLibAllocateZeroPool( sizeof(EFI_HII_TIME) );

			if ( time != NULL )
			{
//EIP 47037 : Start
				UefiGetTime(control, &Tc);
				time->Hour = (Tm->Hour <= 23)?Tm->Hour : ((Tc.Hour>23)? 0:Tc.Hour) ;
				time->Minute = (Tm->Minute <= 59)? Tm->Minute : ((Tc.Minute>59)? 0:Tc.Minute) ;
				time->Second = (Tm->Second <= 59)?Tm->Second : ((Tc.Second>59)? 0:Tc.Second);
//EIP 47037 : End
				Status = VarSetValue( control->ControlVariable, UefiGetQuestionOffset(IfrPtr), UefiGetWidth(IfrPtr), time );
				MemFreePointer( (VOID **)&time );
			}
		}
	}
	else if( ((Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_WAKEUP) ||
		 ((Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_WAKEUP) )// EIP 77875 : Incorrect logic used to check Time and Date control types
  	{
		BOOLEAN Enabled = TRUE ;
		Status = gRT->SetWakeupTime( Enabled, Tm );
	}
  }
  else	
	Status = gRT->SetTime( Tm );


  return Status ;	

}
//EIP: 55762 Start
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   UpdateDestiantionQuestion
//
// Description: Finds the destination question ID for the current destination
//
// Input:	UINT32 CurrPageID - Current page ID
//          UINT32 DestQuestionId - Destination question ID to set focus
//          UINT32 *FocusControlIndex - 
//
// Output:	EFI_STATUS status - EFI_SUCCESS is successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UpdateDestiantionQuestion(UINT32 CurrPageID, UINT32 DestQuestionId, UINT32 *FocusControlIndex)
{
	EFI_STATUS status = EFI_NOT_FOUND;
	UINT32 j = 0;

	PAGE_INFO *PageInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[CurrPageID]);

	for ( j = 0; j < PageInfo->PageControls.ControlCount; j++ )
	{
		CONTROL_INFO *ctrlInfo = (CONTROL_INFO*)(((UINTN)gControlInfo) + PageInfo->PageControls.ControlList [j /*PageInfo->PageIdIndex */]);
		if(!ctrlInfo){
			continue;
		}
        

		if(UefiGetKeyField(ctrlInfo->ControlPtr) == DestQuestionId){
			*FocusControlIndex = j;
			status = EFI_SUCCESS;
			goto DONE;
		}
	}

DONE:
	return status;
}
//EIP: 55762 End

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	   UefiRefershQuestionValueNvRAM
//
// Description:	Function to Refresh the questions
//
// Parameter:	   CONTROL_INFO *ControlData
//
// Return value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiRefershQuestionValueNvRAM(CONTROL_INFO *ControlData)
{

	
	UINT8 * CurBuf=NULL;
	UINT8 * NvBuf = NULL;
	UINTN VarSize=0;
	EFI_STATUS Status=EFI_UNSUPPORTED;
	UINT8 Flags = 0;
	UINTN offset = UefiGetQuestionOffset(ControlData->ControlPtr);
//EIP-105552 Starts
	UINT16 Size = 0;// = UefiGetWidth(ControlData->ControlPtr);
	//If the control is Ordered list then we are calculating the actual size
	if( CONTROL_TYPE_ORDERED_LIST != ControlData->ControlType)
	{
		Size = UefiGetWidth(ControlData->ControlPtr);
		VarSize = GetControlDataLength(ControlData);
	}
	else
	{
		UINTN Type=0;
		UINT16 OptionCount = 0;
		UINT16 *OptionList=NULL;
		UINT64 *ValueList=NULL;

		UefiGetOneOfOptions(ControlData,&ControlData->ControlHandle,&OptionList, &ValueList, &OptionCount,NULL,NULL);
		if (OptionList)
			MemFreePointer( (VOID **)&(OptionList));
		if (ValueList)
			MemFreePointer( (VOID **)&(ValueList));

		UefiGetValidOptionType( ControlData, &Type, (UINT32 *)&Size);
		Size = OptionCount * Size;
		VarSize = Size;
		
	}
//EIP-105552 Ends
	NvBuf = VarGetNvramQuestionValue(ControlData->ControlVariable, offset, VarSize); //Read value for specific question
	if(NvBuf == NULL){ // No Variable Assosiated then Just refrsh the page
		return EFI_SUCCESS;
    }

    if((UINTN)(Size) >  VarSize){
        goto DONE;
    }

	CurBuf = EfiLibAllocateZeroPool(Size);

	switch(ControlData->ControlType)
	{

	case CONTROL_TYPE_NUMERIC:
	case CONTROL_TYPE_ORDERED_LIST:
	case CONTROL_TYPE_POPUPSEL:
	case CONTROL_TYPE_POPUP_STRING:
	case CONTROL_TYPE_CHECKBOX:
	case CONTROL_TYPE_PASSWORD:
		VarGetValue( ControlData->ControlVariable, 
					UefiGetQuestionOffset(ControlData->ControlPtr), Size, CurBuf );
		break;
	case CONTROL_TYPE_DATE:
	case CONTROL_TYPE_TIME:
  		Flags = UefiGetFlagsField(ControlData->ControlPtr) ;
  		if( ((Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_NORMAL)  ||
		    ((Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_NORMAL) )
		{
				VarGetValue( ControlData->ControlVariable, 
						UefiGetQuestionOffset(ControlData->ControlPtr), Size, CurBuf );
		}
		else
		{
			// RTC/Wakeup Date/Timecontrol
			Status = EFI_SUCCESS;
			goto DONE;
		}
		break;
	default:
		goto DONE;
	}
	if(MemCmp((UINT8 *)NvBuf, (UINT8 *)CurBuf, Size))
	{
		_VarGetSetValue (VAR_COMMAND_SET_VALUE, gVariableList, ControlData->ControlVariable, UefiGetQuestionOffset (ControlData->ControlPtr), Size, NvBuf);
	}
	else
	{
		if(UefiIsInteractive(ControlData))
			Status = CallFormCallBack(ControlData,UefiGetControlKey(ControlData),0,EFI_BROWSER_ACTION_RETRIEVE);
	}
	
	Status = EFI_SUCCESS;
DONE:
	
	MemFreePointer((VOID**)&CurBuf);		
	MemFreePointer((VOID**)&NvBuf);
	return Status;
}
//EIP:56413: START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetResetButtonDefaultid
//
// Description:	    Funtion get the ResetButton Default Id from the Opcode information
//
// Parameter:	    VOID *IfrPtr
//
// Return value:    UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetResetButtonDefaultid(VOID *IfrPtr)
{
   EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
   UINT16 DefaultId = 0xFFFF;//Initializing the default to handle error case 
	 
	 if(OpHeader->OpCode == EFI_IFR_RESET_BUTTON_OP )
	  {
		    DefaultId = ((EFI_IFR_RESET_BUTTON *)OpHeader)->DefaultId;
			return DefaultId;
	  }
return DefaultId;
}
//EIP:56413: END

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FindDriverHealthDriverName
//
// Description:	Finds the driver name which supports driver health protocol
//
// Input:		UINT16 = Entry for which driver name has to be return
//
// Output:		CHAR16 * = Driver Name
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *FindDriverHealthDriverName (UINT16 DriverEntry)
{
	EFI_STATUS  Status, StatusforGetHealth = EFI_UNSUPPORTED;
//	EFI_GUID 	DriverHealthProtocolGuid = EFI_DRIVER_HEALTH_PROTOCOL_GUID;
	EFI_HANDLE  *DriverHealthHandles;
	UINTN       NumHandles = 0, iIndex = 0;
	UINTN 		Count = 0;
	CHAR16      *DriverName = NULL, *DrvNameWithStatus;
	EFI_GUID 	EfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
	EFI_COMPONENT_NAME2_PROTOCOL	*ComponentName2 = NULL;
	EFI_DRIVER_HEALTH_PROTOCOL		*DrvHealthInstance = NULL;
	EFI_DEVICE_PATH_PROTOCOL		*DevicePath;
	EFI_DRIVER_HEALTH_STATUS		HealthStatus = EfiDriverHealthStatusHealthy;
    EFI_GUID EfiDriverHealthProtocolGuid = EFI_DRIVER_HEALTH_PROTOCOL_GUID;
    
    CHAR8 *LangStrings = (CHAR8 *)NULL;
    CHAR8 *tempLangStrings = (CHAR8 *)NULL;
    CHAR8 Lang[200]; 
    

	Status = gBS->LocateHandleBuffer (
				ByProtocol,
				&EfiDriverHealthProtocolGuid,
				NULL,
				&NumHandles,
				&DriverHealthHandles
				);
	if ((Status != EFI_SUCCESS) || (NumHandles == 0))
	{
		return NULL;
	}
	for (iIndex = 0; iIndex < NumHandles; iIndex ++)
	{
		Status = gBS->HandleProtocol (DriverHealthHandles [iIndex], &EfiDriverHealthProtocolGuid, &DrvHealthInstance);
		if (EFI_ERROR (Status))
		{
			continue;
		}
		if (Count != DriverEntry)
		{
			Count ++;
			continue;
		}
		StatusforGetHealth = DrvHealthInstance->GetHealthStatus (DrvHealthInstance, NULL, NULL, &HealthStatus, NULL, NULL);
		Status = gBS->HandleProtocol (DriverHealthHandles [iIndex], &EfiComponentName2ProtocolGuid, &ComponentName2);
		if (EFI_ERROR (Status))
		{
			break;
		}
		//EIP 134138			
		LangStrings = StrDup8( ComponentName2->SupportedLanguages );
		tempLangStrings = LangStrings;							//Ptr will be incremented in _GetNextLanguage so taking backup for freeing
		_GetNextLanguage (&LangStrings, Lang);
		
		Status = ComponentName2->GetDriverName (
                            ComponentName2,
                            Lang,
                            //ComponentName2->SupportedLanguages,
                            &DriverName
                            );
		
		MemFreePointer( (VOID **)&tempLangStrings );
		
		if ((EFI_ERROR (Status)) || (NULL == DriverName))
		{
			break;
		}
		if (!EFI_ERROR (StatusforGetHealth))
		{
			DrvNameWithStatus = EfiLibAllocateZeroPool ((EfiStrLen (DriverName) + EfiStrLen (DriverHealthStatus [HealthStatus]) + 7) * sizeof (CHAR16));  //7 for spaces and NULL character
			if (NULL != DrvNameWithStatus)
			{
				SPrint (
					DrvNameWithStatus,
					((EfiStrLen (DriverName) + EfiStrLen (DriverHealthStatus [HealthStatus]) + 7) * sizeof (CHAR16)),
					L"%s     %s",
					DriverName,
					DriverHealthStatus [HealthStatus]
					);
					MemFreePointer ((VOID **)&DriverHealthHandles);
					return DrvNameWithStatus;
			}
		}	
		goto DONE;
	}
	if (iIndex == NumHandles)
	{
		goto DONE;
	}
	if (!DriverName)
	{
		Status = gBS->HandleProtocol (DriverHealthHandles [iIndex], &gEfiDevicePathProtocolGuid, (VOID **) &DevicePath);
		if (!EFI_ERROR (Status))
		{
			DriverName = _DevicePathToStr (DevicePath);
			if (!EFI_ERROR (StatusforGetHealth))
			{
				DrvNameWithStatus = EfiLibAllocateZeroPool ((EfiStrLen (DriverName) + EfiStrLen (DriverHealthStatus [HealthStatus]) + 7) * sizeof (CHAR16));  //7 for spaces and NULL character
				if (NULL != DrvNameWithStatus)
				{
					SPrint (
						DrvNameWithStatus,
						((EfiStrLen (DriverName) + EfiStrLen (DriverHealthStatus [HealthStatus]) + 7) * sizeof (CHAR16)),
						L"%s     %s",
						DriverName,
						DriverHealthStatus [HealthStatus]
						);
						MemFreePointer ((VOID **)&DriverHealthHandles);
						return DrvNameWithStatus;
				}
			}
		}
		else
		{
			DriverName = EfiLibAllocateZeroPool (30 * sizeof (CHAR16));			//This case will be helpfull when driver name or device path not present
			SPrint (
				DriverName,
				(30 * sizeof (CHAR16)),
				L"Driver At Handle %x",
				DriverHealthHandles [iIndex]
				);
		}
	}
DONE:
	MemFreePointer ((VOID **)&DriverHealthHandles);
	return DriverName;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------
// Procedure:	CtrlsSupportsHealthProtocol
//
// Description:	Finds the number of controllers supports driver health protocol for the driver entry
//
// Input:		UINT16 = Entry for driver to which total controllers has to be find
//
// Output:		UINT16 = Total number of controllers supports driver health
//
//-----------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 CtrlsSupportsHealthProtocol (UINT16 EntryItem)
{
	EFI_STATUS  Status;
	EFI_HANDLE  *Handles;
	UINTN       NumHandles = 0;
	UINT16		ControllerCnt = 0, Count = 0;
	EFI_HANDLE  *DriverHealthHandles;
	UINTN       DriverHealthIndex;
	UINTN       ControllerIndex = 0;
	UINTN       HandleCount = 0;
	UINTN       ChildIndex = 0;
	EFI_DRIVER_HEALTH_PROTOCOL 	*DriverHealth;
	EFI_DRIVER_HEALTH_STATUS	HealthStatus;
    EFI_GUID EfiDriverHealthProtocolGuid = EFI_DRIVER_HEALTH_PROTOCOL_GUID;

	Status = gBS->LocateHandleBuffer (
				ByProtocol,
				&EfiDriverHealthProtocolGuid,
				NULL,
				&NumHandles,
				&DriverHealthHandles
				);
	if ((EFI_ERROR (Status)) || (NumHandles == 0))
	{
		return ControllerCnt;
	}
	for (DriverHealthIndex = 0; DriverHealthIndex < NumHandles; DriverHealthIndex++)
	{
		if (DriverHealthHandles [DriverHealthIndex] == NULL)
		{
			continue;
		}	
		Status = gBS->HandleProtocol (
			DriverHealthHandles [DriverHealthIndex],
			&EfiDriverHealthProtocolGuid,
			(VOID **)&DriverHealth
		);
		if (EFI_ERROR (Status))
		{
			continue;
		}
		if (EntryItem > Count)
		{
			Count ++;
			continue;
		}
		gDrvHandle = DriverHealthHandles [DriverHealthIndex];
		gDrvHealthInstance = DriverHealth;
		Status = gBS->LocateHandleBuffer (
			AllHandles,
			NULL,
			NULL,
			&HandleCount,
			&Handles
	        );
		if (EFI_ERROR (Status))
        {
			MemFreePointer ((VOID **)&DriverHealthHandles);
			return ControllerCnt;
		}
		for (ControllerIndex = 0; ControllerIndex < HandleCount; ControllerIndex ++)
		{
			if (NULL == Handles [ControllerIndex])
			{
				continue;
      		}
			Status = DriverHealth->GetHealthStatus (DriverHealth, Handles [ControllerIndex], NULL, &HealthStatus, NULL, NULL);
			if (EFI_ERROR (Status))
			{
				continue;
			}
			AddHandleIntoList (Handles [ControllerIndex], NULL, HealthStatus);
			ControllerCnt ++;
			for (ChildIndex = 0; ChildIndex < HandleCount; ChildIndex++)
			{
        		if (Handles [ChildIndex] == NULL)
				{
          			continue;
    	    	}
				Status = DriverHealth->GetHealthStatus (DriverHealth, Handles [ControllerIndex], Handles [ChildIndex], &HealthStatus, NULL, NULL);
				if (EFI_ERROR (Status))
				{
					continue;
				}
				AddHandleIntoList (Handles [ControllerIndex], Handles [ChildIndex], HealthStatus);
				ControllerCnt ++;
			}
		}
		break;
	}
    MemFreePointer ((VOID **)&DriverHealthHandles);
	return ControllerCnt;
}	

//<AMI_PHDR_START>
//----------------------------------------------------------------------------------
// Procedure:	GetCtrlNameAndHealth
//
// Description:	Finds the controller name with its health
//
// Input:		UINT16 = Entry for controller to which name has to be find
//
// Output:		CHAR16 * = Controller name with its health status
//
//-----------------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetCtrlNameAndHealth (UINT16 ControllerEntry)
{
	UINT16  Count = 0;
	CHAR16	*ContrNameAndHlth = NULL;
	DRV_HEALTH_HNDLS *DrvHlthHandles = NULL;


	DrvHlthHandles = gDrvHealthHandlesHead;
	while (Count != ControllerEntry)
	{
		DrvHlthHandles = DrvHlthHandles->Next;
		Count ++;
	}
	ContrNameAndHlth = GetDrvHlthCtrlName (DrvHlthHandles);
	return ContrNameAndHlth;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------------
// Procedure:	GetDrvHlthCtrlName
//
// Description:	Finds the controller name
//
// Input:		DRV_HEALTH_HNDLS * = Details for finding the controller name
//
// Output:		CHAR16 * = Controller name for the controller and child handle
//
//-----------------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetDrvHlthCtrlName (DRV_HEALTH_HNDLS *DrvHlthHandles)// EFI_HANDLE DriverHealth, EFI_HANDLE ControllerHandle, EFI_HANDLE ChildHandle)
{
	EFI_STATUS  Status = EFI_SUCCESS;
	CHAR16		*CtrlName = NULL;
	CHAR16		*ContrNameAndHlth = NULL;
	EFI_GUID 	EfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
	EFI_COMPONENT_NAME2_PROTOCOL	*ComponentName2 = NULL;
	EFI_DRIVER_HEALTH_STATUS 		HealthStatus = EfiDriverHealthStatusHealthy;  //EIP 134138

	Status = gDrvHealthInstance->GetHealthStatus (				//If controllers reconnected status might change so getting the status again
					gDrvHealthInstance,
	  				DrvHlthHandles->ControllerHandle,
		    		DrvHlthHandles->ChildHandle, 
					&HealthStatus,
					NULL,
					NULL
					);
	if (EFI_ERROR (Status))
	{
		return NULL;
	}
	DrvHlthHandles->HealthStatus = HealthStatus;
	Status = gBS->HandleProtocol (
		gDrvHandle,
		&EfiComponentName2ProtocolGuid,
		(VOID **)&ComponentName2
	);
	if (!EFI_ERROR (Status))
 	{
		Status = ComponentName2->GetControllerName (ComponentName2, DrvHlthHandles->ControllerHandle, DrvHlthHandles->ChildHandle, ComponentName2->SupportedLanguages, &CtrlName);
		if (EFI_ERROR (Status))
	 	{
			CtrlName = NULL;
		}
	}
	if (NULL == CtrlName)
	{
		CtrlName = EfiLibAllocateZeroPool (50 * sizeof (CHAR16)); //16+16+"DriverName"
		if (NULL == CtrlName)
		{
			return NULL;
		}
		SPrint (CtrlName, 50 * sizeof (CHAR16), L"Controller %x Child %x", DrvHlthHandles->ControllerHandle, DrvHlthHandles->ChildHandle);
	}
	ContrNameAndHlth = EfiLibAllocateZeroPool ((EfiStrLen (CtrlName) + EfiStrLen (DriverHealthStatus [HealthStatus]) + 7) * sizeof (CHAR16));		//7 for spaces and NULL char.
	if (NULL == ContrNameAndHlth)
	{
		return NULL;
	}
	SPrint (
		ContrNameAndHlth,
		((EfiStrLen (CtrlName) + EfiStrLen (DriverHealthStatus [HealthStatus]) + 7) * sizeof (CHAR16)),
		L"%s     %s",     
		CtrlName,
		DriverHealthStatus [HealthStatus]
		);
	return ContrNameAndHlth;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------
// Procedure:	AddHandleIntoList
//
// Description:	Adds the driver health details to the linked list
//
//	Input:		EFI_HANDLE = Controller handle
//				EFI_HANDLE = Child handle
//				EFI_DRIVER_HEALTH_STATUS = Health status corresponding to controller and child handle
//
// Output:		VOID
//
//------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AddHandleIntoList (EFI_HANDLE ControllerHandle, EFI_HANDLE ChildHandle, EFI_DRIVER_HEALTH_STATUS HealthStatus)
{
	DRV_HEALTH_HNDLS *DrvHealthHandles;
	DRV_HEALTH_HNDLS *tempHealthHandle;

	DrvHealthHandles = EfiLibAllocateZeroPool (sizeof (DRV_HEALTH_HNDLS));
	if (NULL == DrvHealthHandles)
	{
		return;
	}
	DrvHealthHandles->ControllerHandle = ControllerHandle;
	DrvHealthHandles->ChildHandle = ChildHandle;
	DrvHealthHandles->HealthStatus = HealthStatus;
	DrvHealthHandles->Next = NULL;
	if (NULL == gDrvHealthHandlesHead)
	{	
		gDrvHealthHandlesHead = DrvHealthHandles;
		return;
	}
	tempHealthHandle = gDrvHealthHandlesHead;
	while (tempHealthHandle->Next)
	{
		tempHealthHandle = tempHealthHandle->Next;
	}
	tempHealthHandle->Next = DrvHealthHandles;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------------
// Procedure:	FreeControllersList
//
// Description:	Frees the driver health details linked list
//
//	Input:		VOID
//
// Output:		VOID
//
//-----------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FreeControllersList (VOID)
{
	DRV_HEALTH_HNDLS *DrvHealthHandles, *tempDrvHealthHandles;
	
	if (!gDrvHealthHandlesHead)
	{
		return;
	}
	DrvHealthHandles = gDrvHealthHandlesHead;
	while (DrvHealthHandles)
	{
		tempDrvHealthHandles = DrvHealthHandles;
		DrvHealthHandles = DrvHealthHandles->Next;
		MemFreePointer ((VOID **)&tempDrvHealthHandles);
	}
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------
// Procedure:	SetDrvHealthHandleAndCtrlCount
//
// Description:	Finds and sets the number of controllers supports the driver health handle
//
//	Input:		UINT16 = Driver health handle entry
//
// Output:		VOID
//
//--------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetDrvHealthHandleAndCtrlCount (UINT16 ItemEntry)
{
	UINTN 		TotControllers = 0;
	EFI_GUID 	DrvHealthCtrlGuid = AMITSE_DRIVER_HEALTH_CTRL_GUID;
	
	FreeControllersList ();
	gDrvHealthHandlesHead = NULL;

	TotControllers = CtrlsSupportsHealthProtocol (ItemEntry);
	VarSetNvramName (L"DrvHealthCtrlCnt", &DrvHealthCtrlGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &TotControllers, sizeof (UINTN));
}

//EIP57661 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetDriverHealthCount
//
// Description:	Sets the DriverHealthCount and DriverHlthEnable variables
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetDriverHealthCount (VOID)
{
	EFI_STATUS  Status;
	EFI_GUID 	DriverHealthProtocolGuid = EFI_DRIVER_HEALTH_PROTOCOL_GUID;
	EFI_HANDLE  *DriverHealthHandles = NULL;
	UINTN       NumHandles = 0, iIndex = 0, HealthCount = 0;
	EFI_GUID 	DrvHealthGuid = AMITSE_DRIVER_HEALTH_GUID;
	EFI_GUID 	DrvHlthEnableGuid = AMITSE_DRIVER_HEALTH_ENB_GUID;
	EFI_DRIVER_HEALTH_PROTOCOL	*DrvHealthInstance = NULL;

    SETUP_DEBUG_UEFI ( "\n[TSE] Entering SetDriverHealthCount()\n" );
	
	Status = gBS->LocateHandleBuffer (
				ByProtocol,
				&DriverHealthProtocolGuid,
				NULL,
				&NumHandles,
				&DriverHealthHandles
				);
	if (EFI_SUCCESS != Status)
	{
		NumHandles = 0;
	}
	for (iIndex = 0; iIndex < NumHandles; iIndex ++)
	{
		Status = gBS->HandleProtocol (DriverHealthHandles [iIndex], &DriverHealthProtocolGuid, &DrvHealthInstance);
		if (EFI_ERROR (Status))
		{
			continue;
		}
		HealthCount ++;
	}
	if (NumHandles)
	{
		MemFreePointer ((VOID **)&DriverHealthHandles);
	}
	VarSetNvramName (L"DriverHealthCount", &DrvHealthGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &HealthCount, sizeof (UINTN));
    VarUpdateVariable (VARIABLE_ID_DRV_HLTH_COUNT);             //Update NVRAM cache for DriverHealthCount
    HealthCount = HealthCount ? 1 : 0;          //To enable driver health root menu
    VarSetNvramName (L"DriverHlthEnable", &DrvHlthEnableGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &HealthCount, sizeof (UINTN));
    VarUpdateVariable (VARIABLE_ID_DRV_HLTH_ENB);               //Update NVRAM cache for DriverHlthEnable
    SETUP_DEBUG_UEFI ( "\n[TSE] Exiting SetDriverHealthCount()\n" );
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------
// Procedure:	DisplayMsgListMessageBox
//
// Description:	Displays the messages from EFI_DRIVER_HEALTH_HII_MESSAGE
//
//	Input:		EFI_DRIVER_HEALTH_HII_MESSAGE * = Message to show
//
// Output:		VOID
//
//--------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DisplayMsgListMessageBox (EFI_DRIVER_HEALTH_HII_MESSAGE *MessageList)
{
	CHAR16 	*DisplayString = NULL;
	CHAR16	*String = NULL;
	UINT8 	Count = 0;
	UINT8	MsgBoxSel = 0;
	EFI_STATUS	Status = EFI_SUCCESS;

	while (MessageList [Count].HiiHandle)
	{
		String = HiiGetString (MessageList [Count].HiiHandle, MessageList [Count].StringId);
		Count ++;
		if (Count > 15)							//Checking for safe termination, otherwise msgbox fill the full screen
		{
			break;
		}
		if (String)
		{
			if (!DisplayString)
			{
				DisplayString = EfiLibAllocateZeroPool ((EfiStrLen (String) + 2) * sizeof (CHAR16));		//2 for /n and NULL character
			}
			else
			{
				DisplayString = MemReallocateZeroPool (
									DisplayString,
									( (EfiStrLen (DisplayString) + 1) * sizeof (CHAR16) ),
									( ((EfiStrLen (String) + 2) * sizeof (CHAR16)) + ((EfiStrLen (DisplayString) + 1) * sizeof (CHAR16)) )    //2 for /n and NULL character
									);	
			}
			if (NULL == DisplayString)
			{
				MemFreePointer ((VOID **)&String);
				continue;
			}
			if (DisplayString [0])
			{
				EfiStrCat (DisplayString, String);
				EfiStrCat (DisplayString, L"\n");
			}
			else
			{
				EfiStrCpy (DisplayString, String);
				EfiStrCat (DisplayString, L"\n");
			}
		}
	}
	if (DisplayString)
	{
		CHAR16 *text = NULL;
		text = HiiGetString (gHiiHandle, STRING_TOKEN (STR_DRV_HLTH_TITLE));
		Status = mPostMgr->DisplayMsgBox (
					text,
					DisplayString,
					MSGBOX_TYPE_OK, 
					&MsgBoxSel		
				);
		if(EFI_ERROR (Status))
			return;
		
		MemFreePointer ((VOID **)&DisplayString);
		if (text)
		{
			MemFreePointer ((VOID **)&text);
		}	
	}
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------
// Procedure:	DoDriverHealthOperation
//
// Description:	Performs the driver health operations for the corresponding controller entry
//
//	Input:		VOID * = Control Info for the correponding controller entry
//				UINT16 = Controller entry in the page
//
// Output:		VOID
//
//--------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DoDriverHealthOperation (VOID *Tempcontrol, UINT16 ControllerEntry)
{
	UINT16 						Count = 0;
	EFI_STATUS					Status = EFI_SUCCESS;
	DRV_HEALTH_HNDLS 			*DrvHlthHandles = NULL;
	EFI_DRIVER_HEALTH_STATUS  		LocalHealthStatus = EfiDriverHealthStatusHealthy;
	EFI_DRIVER_HEALTH_HII_MESSAGE 	*MessageList = NULL;
	EFI_HII_HANDLE				FormHiiHandle;
	UINT8						MsgBoxSel = 0;
	CONTROL_INFO                    		*control = (CONTROL_INFO *)Tempcontrol;

	if(!mPostMgr)
	{
		//Loacate Post Manager Protocol
		Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL,(void**) &mPostMgr);
		if(Status != EFI_SUCCESS)
			return;
	}
	
	DrvHlthHandles = gDrvHealthHandlesHead;
	while (Count != ControllerEntry)
	{
		DrvHlthHandles = DrvHlthHandles->Next;
		Count ++;
	}
	if (EfiDriverHealthStatusHealthy == DrvHlthHandles->HealthStatus)
	{
		Status = gDrvHealthInstance->GetHealthStatus (
						gDrvHealthInstance,
						DrvHlthHandles->ControllerHandle,
						DrvHlthHandles->ChildHandle, 
						&LocalHealthStatus,
						&MessageList,
						&FormHiiHandle
					);
		if (NULL != MessageList)
		{
		    DisplayMsgListMessageBox (MessageList);
		}
	}
	if (EfiDriverHealthStatusRepairRequired == DrvHlthHandles->HealthStatus)
	{
		Status = gDrvHealthInstance->Repair (
					gDrvHealthInstance,
					DrvHlthHandles->ControllerHandle,
					DrvHlthHandles->ChildHandle,
					NULL
                    	    	    );
		if (!EFI_ERROR (Status))
		{
			Status = gDrvHealthInstance->GetHealthStatus (
						gDrvHealthInstance,
		  				DrvHlthHandles->ControllerHandle,
		  				DrvHlthHandles->ChildHandle, 
						&LocalHealthStatus,
						&MessageList,
						&FormHiiHandle
					);
			if (NULL != MessageList)
			{
				DisplayMsgListMessageBox (MessageList);
			}
		}
	}
	if ((EfiDriverHealthStatusConfigurationRequired == DrvHlthHandles->HealthStatus) || 
		(EfiDriverHealthStatusConfigurationRequired == LocalHealthStatus))
	{
		UINT32 		i=0;
		PAGE_INFO 	*pageInfo;
		if (EfiDriverHealthStatusConfigurationRequired != LocalHealthStatus)
		{
			Status = gDrvHealthInstance->GetHealthStatus (
						gDrvHealthInstance,
						DrvHlthHandles->ControllerHandle,
						DrvHlthHandles->ChildHandle, 
						&LocalHealthStatus,
						&MessageList,
						&FormHiiHandle
					);
		}
		if (!EFI_ERROR (Status) && (FormHiiHandle))
		{
			if (NULL != MessageList)
			{
				DisplayMsgListMessageBox (MessageList);
			}
			for (i = 0; i < gPages->PageCount; i++)
			{
				pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[i]);
				if (pageInfo->PageHandle == FormHiiHandle)
				{
				    PAGE_DATA **page;                   //To display the configuration page in advanced menu itself
				    
				    control->ControlDestPageID = i;				    
				    pageInfo->PageFlags.PageVisible = FALSE;
				    pageInfo->PageParentID = control->ControlPageID;
				    
				    //For ESA gApp will be NULL but for TSE gApp will be not-NULL
				    if(gApp)
				    {
					    page = &gApp->PageList [pageInfo->PageID];
					    gPage.Destroy (*page, FALSE);
					    gPage.Initialize (*page, pageInfo);
						gApp->CurrentPage = i;
				    }
				    break;
				}
			}
		}
	}
	if (EfiDriverHealthStatusFailed == DrvHlthHandles->HealthStatus)
	{
		Status = gDrvHealthInstance->GetHealthStatus (
						gDrvHealthInstance,
						DrvHlthHandles->ControllerHandle,
						DrvHlthHandles->ChildHandle, 
						&LocalHealthStatus,
						&MessageList,
						&FormHiiHandle
					);
		if ((!EFI_ERROR (Status)) && (NULL != MessageList))
		{
			DisplayMsgListMessageBox (MessageList);
		}
	}
	if (EfiDriverHealthStatusReconnectRequired == DrvHlthHandles->HealthStatus)
	{
		CHAR16 *Title = NULL;
		CHAR16 *Message = NULL;

		Title = HiiGetString (gHiiHandle, STRING_TOKEN (STR_DRV_HLTH_TITLE));
		Message = HiiGetString (gHiiHandle, STRING_TOKEN (STR_DRV_HLTH_RECON));
		Status = mPostMgr->DisplayMsgBox (
					Title,
					Message,
					MSGBOX_TYPE_OKCANCEL, 
					&MsgBoxSel		
				);
		if(EFI_ERROR (Status))
			return;
		
		if (0 == MsgBoxSel)			//User pressed OK
		{
			gBS->DisconnectController (DrvHlthHandles->ControllerHandle, NULL, NULL);
			gBS->ConnectController (DrvHlthHandles->ControllerHandle, NULL, NULL, TRUE);
		}
	}
	if (EfiDriverHealthStatusRebootRequired == DrvHlthHandles->HealthStatus)
	{
		CHAR16 *Title = NULL;
		CHAR16 *Message = NULL;

		Title = HiiGetString (gHiiHandle, STRING_TOKEN (STR_DRV_HLTH_TITLE));
		Message = HiiGetString (gHiiHandle, STRING_TOKEN (STR_DRV_HLTH_REBOOT));
		Status = mPostMgr->DisplayMsgBox (
					Title,
					Message,
					MSGBOX_TYPE_OKCANCEL, 
					&MsgBoxSel		
				);
		if(EFI_ERROR (Status))
			return;
		
		if (0 == MsgBoxSel)			//User pressed OK
		{
			DrvHlthHandles = gDrvHealthHandlesHead;
			while (DrvHlthHandles)
			{
				//Proceed with repair for all the controllers in repair state
				if (EfiDriverHealthStatusRepairRequired == DrvHlthHandles->HealthStatus)	
				{
					Status = gDrvHealthInstance->Repair (
								gDrvHealthInstance,
								DrvHlthHandles->ControllerHandle,
								DrvHlthHandles->ChildHandle,
								NULL
					    	    	    );
				}
				DrvHlthHandles = DrvHlthHandles->Next;
			}
			FreeControllersList ();
			gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
		}
	}
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CheckTimeFlags
//
// Description: Function to check the time flags.
//
// Input:	UINT16 ItemCount
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckTimeFlags(UINT8 Flags)
{
	return ((Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_NORMAL) ;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CheckDateFlags
//
// Description: Function to check the date flags.
//
// Input:	UINT16 ItemCount
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckDateFlags(UINT8 Flags)
{
	return ((Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_NORMAL);
}

//EIP75481  Support TSE debug print infrastructure
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CreateFile
//
// Description: Creates a file to output hpk data
//
// Input:	CHAR16 *filenameFormat, 
//			EFI_HII_HANDLE *Handle, 
//			UINTN Index
//			
//
// Output:	EFI_FILE_PROTOCOL*
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_FILE_PROTOCOL * CreateFile(CHAR16 *filename, UINT32 index)
{
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *pSFP;
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_FILE_PROTOCOL *pRoot,*FileHandle;
    EFI_HANDLE *gSmplFileSysHndlBuf = NULL;  
	UINTN Count = 0;
    UINT16 i = 0;

	// Locate all the simple file system devices in the system
    Status = pBS->LocateHandleBuffer(ByProtocol, &guidSimpleFileSystemProtocol, NULL, &Count, &gSmplFileSysHndlBuf);
	
	if(!EFI_ERROR(Status))
    {
	 	Status = gBS->HandleProtocol( gSmplFileSysHndlBuf[index], &guidSimpleFileSystemProtocol, &pSFP );

		if (!EFI_ERROR(Status))
		{
			Status = pSFP->OpenVolume(pSFP,&pRoot);
		
			if (!EFI_ERROR(Status))
			{
				Status = pRoot->Open(pRoot,
				                    &FileHandle,
				                    filename,
				                    EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
				                    0);
				
				pRoot->Close(pRoot);
		
				if (!EFI_ERROR(Status))
	 			{
					return FileHandle;
				}
			}
		}
	}

	if(gSmplFileSysHndlBuf != NULL) 
        pBS->FreePool(gSmplFileSysHndlBuf);
	
	return NULL;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   WriteDataToFile
//
// Description: Writes data to file
//
// Input:	CHAR16 *filename, VOID *Data, UINTN length
//			
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WriteDataToFile(CHAR16 *filename, VOID *Data, UINTN length, UINT32 index)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_FILE_PROTOCOL *FileHandle=NULL;

	UINTN len = length;

	SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] Entering WriteDataToFile \n\n");
	
	if (Data == NULL)
	{
    	goto DONE;
	}	
  	
	FileHandle = CreateFile(filename, index);

	if (FileHandle != NULL)
	{
		FileHandle->SetPosition(FileHandle,0);
		FileHandle->Write(FileHandle,&len, Data);
		FileHandle->Close(FileHandle);
		Status = EFI_SUCCESS ;

		SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] Exporting Filename: %s \n\n", filename);
	}
DONE:
	
	SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] Exiting WriteDataToFile, Status: %x \n\n", Status);

	return Status ;
}

#if TSE_DEBUG_MESSAGES
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   HiiGetPackList
//
// Description: Get HII form package by handle and form ID
//
// Input:	EFI_HII_HANDLE Handle
//          UINT16 form
//          UINTN *Length
//
// Output:	VOID *formPkBuffer - 
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *HiiGetPackList( EFI_HII_HANDLE Handle, UINT16 form, UINTN *Length )
{
	EFI_STATUS status = EFI_SUCCESS;
	VOID *hiiFormPackage=NULL;
	UINTN len=10;

	if(Length == NULL)
		Length = &len;

	hiiFormPackage = EfiLibAllocateZeroPool(*Length);

	status = gHiiDatabase->ExportPackageLists(gHiiDatabase, Handle, Length, hiiFormPackage);
	if(status == EFI_BUFFER_TOO_SMALL)
	{
		MemFreePointer(&hiiFormPackage);
		//
		// Allocate space for retrieval of IFR data
		//
		hiiFormPackage = EfiLibAllocateZeroPool(*Length);

		if (hiiFormPackage == NULL)
		{
			hiiFormPackage = NULL;
			goto DONE;
		}
		//
		// Get all the packages associated with this HiiHandle
		//
		status = gHiiDatabase->ExportPackageLists (gHiiDatabase, Handle, Length, hiiFormPackage);
		if(EFI_ERROR(status))
		{
			MemFreePointer(&hiiFormPackage);
			hiiFormPackage = NULL;
		}
	}
	else if(EFI_ERROR(status))
	{
		hiiFormPackage = NULL;
	}

DONE:
	return hiiFormPackage;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   ProcessPackToFile
//
// Description: Prints the HPK data to file
//
// Input:	EFI_HII_DATABASE_NOTIFY_TYPE NotifyType, EFI_HANDLE Handle
//			
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProcessPackToFile(EFI_HII_DATABASE_NOTIFY_TYPE NotifyType, EFI_HANDLE Handle)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	CHAR16 *filenameFormat = NULL;
	CHAR16 filename[50];
	VOID *formSetData = NULL;
	UINTN length = 0;
	
	SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] Entering ProcessPackToFile \n\n");
	

	if(NotifyType == EFI_HII_DATABASE_NOTIFY_REMOVE_PACK)
		filenameFormat = L"REMOVED_0x%x_%03d.hpk" ;

	else if(NotifyType == EFI_HII_DATABASE_NOTIFY_NEW_PACK)
		filenameFormat = L"NEW_0x%x_%03d.hpk" ;

	else if(NotifyType == EFI_HII_DATABASE_NOTIFY_ADD_PACK)
		filenameFormat = L"UPDATE_0x%x_%03d.hpk" ;

	else
		goto DONE ;


	formSetData = (UINT8*)HiiGetPackList(Handle, 0, &length);

	if (formSetData == NULL)
	{
	   	goto DONE;
 	}

	SPrint(filename, 50, filenameFormat, Handle, HpkFileCount);

	Status = WriteDataToFile(filename, formSetData, length, 0) ;
	
	if (!EFI_ERROR (Status))
	{
		HpkFileCount++ ;
	}

DONE:
	
	SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] Exiting ProcessPackToFile, Status: %x \n\n", Status);
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   WritePackToFile
//
// Description: Writes Hpk data to file
//
// Input:	CHAR16 *filenameFormat, EFI_HANDLE Handle, UINT8 *PackData, UINTN length
//			
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WritePackToFile(CHAR16 *filenameFormat, EFI_HANDLE Handle, UINT8 *PackData, UINTN length)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_FILE_PROTOCOL *FileHandle=NULL;
	UINT8 *formSet = PackData;
	UINTN len = length;
	CHAR16 filename[50];

	SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] Entering WritePackToFile \n\n");
	
	if(formSet == NULL)
  	{
    	formSet = (UINT8*)HiiGetPackList(Handle, 0, &len);
		if (formSet == NULL)
		{
	    	goto DONE;
 		}	
  	}

	SPrint(filename, 50, filenameFormat, Handle, HpkFileCount);

	Status = WriteDataToFile(filename, formSet, length,0) ;	
	
	if (!EFI_ERROR (Status))
	{
		HpkFileCount++ ;
	}
	
DONE:
	
	SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] Exiting WritePackToFile, Status: %x \n\n", Status);

	return Status ;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   DebugShowBufferContent
//
// Description: Prints the buffer, 16 characters max in a line
//
// Input:	UINTN bufSize - Buffer length to print
//			VOID *buffer - Buffer to print
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DebugShowBufferContent(UINTN bufSize, VOID *buffer)
{
    
 //#if TSE_DEBUG_MESSAGES == 2
    
    UINTN index = 0, j = 0;
	UINTN size = bufSize;
	UINT8 *temp = (UINT8 *)buffer;

    for(index = 0; index < size; ){
		SETUP_DEBUG_UEFI_CALLBACK ( "[0x%08x (%04d)]  ", index, index);
        for(j = 0; (j < 16) && (temp != NULL); index++, j++){
			if(index >= size){
				break;
			}
            if(j==8) SETUP_DEBUG_UEFI_CALLBACK ( "- ");
			SETUP_DEBUG_UEFI_CALLBACK ( "%02x ", (UINT8)temp[index]);
		}
		SETUP_DEBUG_UEFI_CALLBACK ("\n");
	}

	
// #endif

}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   DebugLibShowHiiControlState
//
// Description: Prints the AMI Setup Lib control states
//
// Input:	None
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DebugLibShowHiiControlState(UINT32 formID, UINT32 ctrlIndex, VOID *passedCtrlInfo)
{
	EFI_STATUS status = EFI_SUCCESS;
	CONTROL_INFO *ctrlInfo = (CONTROL_INFO *)NULL;
	UINTN ctrlCond = COND_NONE;
	
	ctrlInfo = (CONTROL_INFO *)passedCtrlInfo;
	if(passedCtrlInfo == NULL){
		//status = _GetControlInfo(formID, ctrlIndex, &ctrlInfo);
		//if((ctrlInfo == NULL) || EFI_ERROR(status)){
			SETUP_DEBUG_TSE("Invalid ctrlInfo, formID: 0x%x, ctrlIndex: 0x%x, status: 0x%x", formID, ctrlIndex, status);
			return;
		//}
	}
	ctrlCond = CheckControlCondition(ctrlInfo);
	
	switch(ctrlCond){
		case COND_NONE:
			SETUP_DEBUG_TSE("Control Condition: COND_NONE\n");
			break;
		case COND_SUPPRESS:
			SETUP_DEBUG_TSE("Control Condition: COND_SUPPRESS\n");
			break;
		case COND_HIDDEN:
			SETUP_DEBUG_TSE("Control Condition: COND_HIDDEN\n");
			break;
		case COND_GRAYOUT:
			SETUP_DEBUG_TSE("Control Condition: COND_GRAYOUT\n");
			break;
		case COND_INCONSISTENT:
			SETUP_DEBUG_TSE("Control Condition: COND_INCONSISTENT\n");
			break;
		default:
			break;
	}
	return;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   DebugShowControlInfo
//
// Description: Prints the cache controls information
//
// Input:	UINT32 formID
//			UINTN count
//			VOID *passedCtrlInfo
//          BOOLEAN detailed - If TRUE, prints the control buffers
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DebugShowControlInfo(UINT32 formID, VOID *passedCtrlInfo)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN bufferLen = 0;
	UINT32 i = 0, j = 0;
	UINT8 *temp = (UINT8 *)NULL;
	EFI_IFR_QUESTION_HEADER *questionHdr = NULL;
	UINT8 *questionValue = (UINT8 *)NULL;
	UINTN dataWidth = 0;
	CONTROL_INFO *ctrlInfo = (CONTROL_INFO *)NULL;
	CHAR16 *String = (CHAR16 *)NULL;

	ctrlInfo = (CONTROL_INFO *)passedCtrlInfo;
	
    if(passedCtrlInfo == NULL){
		//status = _GetControlInfo(formID, ctrlIndex, &ctrlInfo);
        goto DONE ;		
	}

	if((ctrlInfo == NULL) || EFI_ERROR(status)){
		SETUP_DEBUG_TSE("Invalid ctrlInfo, formID: 0x%x, status: 0x%x", formID, status);
        goto DONE ;		
	}
    
    SETUP_DEBUG_TSE("\n----- Adding Control -----\n");  

    if(ctrlInfo->ControlHandle != NULL){
		String = HiiGetString(ctrlInfo->ControlHandle, ctrlInfo->QuestionId);
	}
	
    if (String)
    {
	    SETUP_DEBUG_TSE("QuestionId: 0x%x, %s\n", ctrlInfo->QuestionId, String);
    }
	SETUP_DEBUG_TSE("ControlHandle: 0x%x\n", ctrlInfo->ControlHandle);
    SETUP_DEBUG_TSE("ControlType: 0x%x\n", ctrlInfo->ControlType);
	SETUP_DEBUG_TSE("ControlPageID: %d\n", ctrlInfo->ControlPageID);
    SETUP_DEBUG_TSE("ControlDestPageID: %d\n", ctrlInfo->ControlDestPageID);
	SETUP_DEBUG_TSE("ControlIndex: %d\n", ctrlInfo->ControlIndex);
	SETUP_DEBUG_TSE("ControlPtr: 0x%x\n", ctrlInfo->ControlPtr);
    SETUP_DEBUG_TSE("ControlConditionalPtr: 0x%x\n", ctrlInfo->ControlConditionalPtr);
	SETUP_DEBUG_TSE("ControlDataLength: 0x%x\n", ctrlInfo->ControlDataLength);
    SETUP_DEBUG_TSE("ControlDataWidth: 0x%x\n", ctrlInfo->ControlDataWidth);
    SETUP_DEBUG_TSE("ControlKey: %d\n", ctrlInfo->ControlKey);
    SETUP_DEBUG_TSE("DestQuestionID: 0x%x\n", &ctrlInfo->DestQuestionID);
    //DebugLibShowHiiControlState(formID, ctrlInfo->ControlIndex, ctrlInfo);
	//DebugShowControlFlags(formID, ctrlIndex, ctrlInfo, &ctrlInfo->ControlFlags);


DONE:
	MemFreePointer( (VOID **)&String );
	
	return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   DebugShowPageInfo
//
// Description: Shows the Page information
//
// Input:	UINT32 formID - The form 
//			PAGE_INFO *passedPageInfo
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DebugShowPageInfo(UINT32 formID, VOID *passedPageInfo)
{
	EFI_STATUS status = EFI_SUCCESS;
	PAGE_INFO *pageInfo = (PAGE_INFO *)NULL;
	
	pageInfo = (PAGE_INFO *)passedPageInfo;

    if(pageInfo == NULL)
        return ;	
    
	SETUP_DEBUG_TSE("\n+++++ Adding Page +++++\n");
    SETUP_DEBUG_TSE("PageTitle: %s \n", HiiGetString(pageInfo->PageHandle, pageInfo->PageSubTitle )); //Varies	Allows a page to override the main title bar
    //SETUP_DEBUG_TSE("PageSubTitle: %s \n", HiiGetString(pageInfo->PageHandle, pageInfo->PageSubTitle )); //Varies	Token for the subtitle string for this page
	SETUP_DEBUG_TSE("PageHandle: 0x%x\n", pageInfo->PageHandle);
	SETUP_DEBUG_TSE("PageIdIndex: %d\n", pageInfo->PageIdIndex); //varies	Index in to PageIdList triplets
	SETUP_DEBUG_TSE("PageFormID: %d\n", pageInfo->PageFormID); //Varies	Form ID within the formset for this page
	SETUP_DEBUG_TSE("PageID: %d\n", pageInfo->PageID); //Varies	unique ID for this page
	SETUP_DEBUG_TSE("PageParentID: %d\n", pageInfo->PageParentID); //Varies	Identify this page's parent page
	SETUP_DEBUG_TSE("PageFlags: 0x%x\n", pageInfo->PageFlags); //3			Various attributes for a specific page
	SETUP_DEBUG_TSE("PageVariable: 0x%x\n", pageInfo->PageVariable); //Varies	Overrides the variable ID for this page (0 = use default)
    SETUP_DEBUG_TSE("PageDynamic: 0x%x\n", pageInfo->PageFlags.PageDynamic); //Identify this page as dynamic page

}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   DebugShowHiiVariable
//
// Description: Prints the variable information for the given parameter
//
// Input:	UINT32 formID
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DebugShowHiiVariable(UINT32 formID, UINT32 varIndex, UINT32 *passedVarIDList)
{
	EFI_STATUS status = EFI_SUCCESS;
	NVRAM_VARIABLE *nvPtr = (NVRAM_VARIABLE *)NULL;
	UINT32 *varIDList = (UINT32 *)NULL;
    VARIABLE_INFO *varInfo = (VARIABLE_INFO *)NULL ;
    UINTN index = 0, j = 0, size = 0 ;
    UINT8 *temp = (UINT8 *)NULL ;

	nvPtr = gVariableList;
	size = nvPtr[varIndex].Size < 0xFFFF ? nvPtr[varIndex].Size : 0;
	temp = nvPtr[varIndex].Buffer;
    varInfo = VarGetVariableInfoIndex( varIndex );

	if(size){
        SETUP_DEBUG_VAR ("\n----------- DebugShowHiiVariable -----------\n");
		SETUP_DEBUG_VAR ("VariableName: %s, Buffer size: %d, Buffer: 0x%x \n", varInfo->VariableName, size, nvPtr[varIndex].Buffer); 
                
        for(index = 0; index < size; ){
			SETUP_DEBUG_VAR ( "[0x%08x (%04d)]  ", index, index);
            for(j = 0; (j < 16) && (temp != NULL); index++, j++){
				if(index >= size){
					break;
				}
                if(j==8) SETUP_DEBUG_VAR ( "- ");
				SETUP_DEBUG_VAR ( "%02x ", (UINT8)temp[index]);
			}
			SETUP_DEBUG_VAR ("\n");
		}

        SETUP_DEBUG_VAR ("----------- End of DebugShowHiiVariable, status: 0x%x -----------\n\n", status); 
	} else{
        SETUP_DEBUG_VAR ("!!!!!! VariableName: %s, size: %d !!!!!\n", varInfo->VariableName, nvPtr[varIndex].Size); 
    }

	return status;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   DebugShowAllHiiVariable
//
// Description: Prints the variable information in the list
//
// Input:	UINT32 formID
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DebugShowAllHiiVariable(UINT32 formID)
{
	EFI_STATUS status = EFI_SUCCESS;
	NVRAM_VARIABLE *nvPtr = (NVRAM_VARIABLE *)NULL;
	UINT32 i = 0;
	UINT32 *varIDList = (UINT32*)EfiLibAllocateZeroPool(gVariables->VariableCount * sizeof(UINT32));

	SETUP_DEBUG_VAR ("\n----------- DebugShowAllHiiVariable -----------\n");  

	if(varIDList == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		SETUP_DEBUG_VAR ("ERROR-%r: varIDList Memory Allocation Failed\n", status);
		goto DONE;
	}

	nvPtr = gVariableList;

	SETUP_DEBUG_VAR ("++ Total number of variables: %d ++\n\n", gVariables->VariableCount);
	for ( i = 0; i < gVariables->VariableCount; i++){
		DebugShowHiiVariable(formID, i, varIDList);		
	}
	SETUP_DEBUG_VAR ("\n");

DONE:
	
    SETUP_DEBUG_VAR ("--------- End of DebugShowAllHiiVariable, status: 0x%x ---------\n\n", status); 
	return status;
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   DisplayParseFormSetData
//
// Description: Prints the current FormSet data
//
// Input:	UINT32 FormID - Library formID of a FormSet
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DisplayParseFormSetData(VOID)
{
   	
    EFI_STATUS status = EFI_SUCCESS;
	PAGE_INFO *pageInfo = (PAGE_INFO *)NULL;
	EFI_HII_PACKAGE_HEADER *pkgHdr = (EFI_HII_PACKAGE_HEADER *)NULL;
	UINT8 *formSet = (UINT8 *)NULL;
	UINT8 *ifrData = (UINT8 *)NULL;
	EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)NULL;
	UINTN length = 0;
	UINTN i = 0, count = 0;
	CHAR16 *opcodeName = (CHAR16 *)NULL;
	EFI_GUID *tempFormSetGuid = (EFI_GUID *)NULL;
	BOOLEAN validOpCode = TRUE;
	UINTN pScopeCount = 0;
    BOOLEAN CurrentForm = FALSE;
    PAGE_DATA *Page ;
    UINT16 questionId = 0;
    FRAME_DATA *frame = NULL ;
    //UINT16	PageFormID = 0;

    Page = gApp->PageList[gApp->CurrentPage];

    formSet = (UINT8*)HiiGetForm(Page->PageData.PageHandle, 0, &length);
	if(formSet == NULL){
		status = EFI_UNSUPPORTED;
        SETUP_DEBUG_TSE ("ERROR: 0x%x, failed to get FormSet data\n",status);
		goto DONE;
	}

	pkgHdr = (EFI_HII_PACKAGE_HEADER*)formSet;

	if(pkgHdr->Type != EFI_HII_PACKAGE_FORMS)
	{
		status = EFI_UNSUPPORTED;
		SETUP_DEBUG_TSE("ERROR: 0x%x, pkgHdr->Type is not supported, Since it is not EFI_HII_PACKAGE_FORM\n",status);
		goto DONE;
	}


	ifrData = ((UINT8 *)pkgHdr) + sizeof(EFI_HII_PACKAGE_HEADER);

	while(i < pkgHdr->Length)
	{
		opHeader = (EFI_IFR_OP_HEADER*)(ifrData + i);
		tempFormSetGuid = (EFI_GUID *)NULL;

		if(opHeader == NULL){
			break;
		}

		count = pScopeCount;
        questionId = 0;

		switch(opHeader->OpCode)
		{
			case EFI_IFR_FORM_OP: //0x01 - Form
				opcodeName = L"EFI_IFR_FORM_OP";

                if(CurrentForm)
                {
                    SETUP_DEBUG_TSE (  "[TSE] Form OpCode End\n" );
                    goto DONE;
                 }

                if(((EFI_IFR_FORM*)(ifrData + i))->FormId == Page->PageData.PageFormID)
                {
                   SETUP_DEBUG_TSE (  "[TSE] Form OpCode Start\n" );  
                   SETUP_DEBUG_TSE (  "FormTitle: %s\n", HiiGetString(Page->PageData.PageHandle, Page->PageData.PageSubTitle  ));
                   
                   frame = Page->FrameList[StyleFrameIndexOf(MAIN_FRAME)];
                   if(frame != NULL)
                     SETUP_DEBUG_TSE (  "NumberOfControls: %ld\n", frame->ControlCount );
                         
                   CurrentForm = TRUE;
                }

				break;
			case EFI_IFR_SUBTITLE_OP: //0x02 - Subtitle statement
				opcodeName = L"EFI_IFR_SUBTITLE_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_TEXT_OP: //0x03 - Static text/image statement
				opcodeName = L"EFI_IFR_TEXT_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_IMAGE_OP: //0x04 - Static image.
				opcodeName = L"EFI_IFR_IMAGE_OP";
				break;
			case EFI_IFR_ONE_OF_OP: //0x05 - One-of question
				opcodeName = L"EFI_IFR_ONE_OF_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_CHECKBOX_OP: //0x06 - Boolean question
				opcodeName = L"EFI_IFR_CHECKBOX_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_NUMERIC_OP: //0x07 - Numeric question
				opcodeName = L"EFI_IFR_NUMERIC_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_PASSWORD_OP: //0x08 - Password string question
				opcodeName = L"EFI_IFR_PASSWORD_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_ONE_OF_OPTION_OP: //0x09 - Option
				opcodeName = L"EFI_IFR_ONE_OF_OPTION_OP";
                /*
                switch(((EFI_IFR_ONE_OF_OPTION *)opHeader)->Type)
				{
				    case EFI_IFR_TYPE_NUM_SIZE_16:
					    questionId = ((EFI_IFR_ONE_OF_OPTION *)opHeader)->Value.u16;
					    break;
				    case EFI_IFR_TYPE_NUM_SIZE_32:    
					    questionId = ((EFI_IFR_ONE_OF_OPTION *)opHeader)->Value.u32;
					    break;
				    case EFI_IFR_TYPE_NUM_SIZE_64:
					    questionId = (UINT16)((EFI_IFR_ONE_OF_OPTION *)opHeader)->Value.u64;
					    break;
				    case EFI_IFR_TYPE_NUM_SIZE_8:
				    default:
					    questionId = ((EFI_IFR_ONE_OF_OPTION *)opHeader)->Value.u8;
					    break;
				}
                */       
				break;
			case EFI_IFR_SUPPRESS_IF_OP: //0x0A - Suppress if conditional
				opcodeName = L"EFI_IFR_SUPPRESS_IF_OP";
				break;
			case EFI_IFR_LOCKED_OP: //0x0B - Marks statement/question as locked
				opcodeName = L"EFI_IFR_LOCKED_OP";
				break;
			case EFI_IFR_ACTION_OP: //0x0C - Button question
				opcodeName = L"EFI_IFR_ACTION_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_RESET_BUTTON_OP: //0x0D - Reset button statement
				opcodeName = L"EFI_IFR_RESET_BUTTON_OP";
				break;
			case EFI_IFR_FORM_SET_OP: //0x0E - Form set
				opcodeName = L"EFI_IFR_FORM_SET_OP";
				break;
			case EFI_IFR_REF_OP: //0x0F - Cross-reference statement
				opcodeName = L"EFI_IFR_REF_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_NO_SUBMIT_IF_OP: //0x10 - Error checking conditional
				opcodeName = L"EFI_IFR_NO_SUBMIT_IF_OP";
				break;
			case EFI_IFR_INCONSISTENT_IF_OP: //0x11 - Error checking conditional
				opcodeName = L"EFI_IFR_INCONSISTENT_IF_OP";
				break;
			case EFI_IFR_EQ_ID_VAL_OP: //0x12 - Return true if question value equals UINT16
				opcodeName = L"EFI_IFR_EQ_ID_VAL_OP";
				break;
			case EFI_IFR_EQ_ID_ID_OP: //0x13 - Return true if question value equals another question value
				opcodeName = L"EFI_IFR_EQ_ID_ID_OP";
				break;
			case 0x14: //0x14 - Return true if question value is found in list of UINT16s
				opcodeName = L"EFI_IFR_EQ_ID_VAL_LIST_OP";
				break;
			case EFI_IFR_AND_OP: //0x15 - Push true if both sub-expressions returns true.
				opcodeName = L"EFI_IFR_AND_OP";
				break;
			case EFI_IFR_OR_OP: //0x16 - Push true if either sub-expressions returns true.
				opcodeName = L"EFI_IFR_OR_OP";
				break;
			case EFI_IFR_NOT_OP: //0x17 - Push false if sub-expression returns true, otherwise return true.
				opcodeName = L"EFI_IFR_NOT_OP";
				break;
			case EFI_IFR_RULE_OP: //0x18 - Create rule in current form.
				opcodeName = L"EFI_IFR_RULE_OP";
				break;
			case EFI_IFR_GRAY_OUT_IF_OP: //0x19 - Nested statements, questions or options will not be selectable if expression returns true.
				opcodeName = L"EFI_IFR_GRAY_OUT_IF_OP";
				break;
			case EFI_IFR_DATE_OP: //0x1A - Date question.
				opcodeName = L"EFI_IFR_DATE_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);    
				break;
			case EFI_IFR_TIME_OP: //0x1B - Time question.
				opcodeName = L"EFI_IFR_TIME_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_STRING_OP: //0x1C - String question
				opcodeName = L"EFI_IFR_STRING_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_REFRESH_OP: //0x1D - Interval for refreshing a question
				opcodeName = L"EFI_IFR_REFRESH_OP";
				break;
			case EFI_IFR_DISABLE_IF_OP: //0x1E - Nested statements, questions or options will not be processed if expression returns true.
				opcodeName = L"EFI_IFR_DISABLE_IF_OP";
				break;
			case 0x1F: //0x1F - Animation associated with question statement, form or form set.
				opcodeName = L"EFI_IFR_ANIMATION_OP";
				break;
			case EFI_IFR_TO_LOWER_OP: //0x20 - Convert a string on the expression stack to lower case.
				opcodeName = L"EFI_IFR_TO_LOWER_OP";
				break;
			case EFI_IFR_TO_UPPER_OP: //0x21 - Convert a string on the expression stack toupper case.
				opcodeName = L"EFI_IFR_TO_UPPER_OP";
				break;
			case 0x22: //0x22 - Convert one value to another by selecting a match from a list.
				opcodeName = L"EFI_IFR_MAP_OP";
				break;
			case EFI_IFR_ORDERED_LIST_OP: //0x23 - Set question
				opcodeName = L"EFI_IFR_ORDERED_LIST_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_VARSTORE_OP: //0x24 - Define a buffer-style variable storage.
				opcodeName = L"EFI_IFR_VARSTORE_OP";
				break;
			case EFI_IFR_VARSTORE_NAME_VALUE_OP: //0x25 - Define a name/value style variable storage.
				opcodeName = L"EFI_IFR_VARSTORE_NAME_VALUE_OP";
				break;
			case EFI_IFR_VARSTORE_EFI_OP: //0x26 - Define a UEFI variable style variable storage.
				opcodeName = L"EFI_IFR_VARSTORE_EFI_OP";
				break;
			case EFI_IFR_VARSTORE_DEVICE_OP: //0x27 - Specify the device path to use for variable storage.
				opcodeName = L"EFI_IFR_VARSTORE_DEVICE_OP";
				break;
			case EFI_IFR_VERSION_OP: //0x28 - Push the revision level of the UEFI Specification to which this FormsProcessor is compliant.
				opcodeName = L"EFI_IFR_VERSION_OP";
				break;
			case EFI_IFR_END_OP: //0x29 - Marks end of scope.
				opcodeName = L"EFI_IFR_END_OP";
				break;
			case EFI_IFR_MATCH_OP: //0x2A - Push TRUE if string matches a pattern.
				opcodeName = L"EFI_IFR_MATCH_OP";
				break;
			case 0x2B: //0x2B - Return a stored value.
				opcodeName = L"EFI_IFR_GET_OP";
				break;
			case 0x2C: //0x2C - Change a stored value.
				opcodeName = L"EFI_IFR_SET_OP";
				break;
			case 0x2D: //0x2D - Provides a value for the current question or default.
				opcodeName = L"EFI_IFR_READ_OP";
				break;
			case 0x2E: //0x2E - Change a value for the current question.
				opcodeName = L"EFI_IFR_WRITE_OP";
				break;
			case EFI_IFR_EQUAL_OP: //0x2F - Push TRUE if two expressions are equal.
				opcodeName = L"EFI_IFR_EQUAL_OP";
				break;
			case EFI_IFR_NOT_EQUAL_OP: //0x30 - Push TRUE if two expressions are not equal.
				opcodeName = L"EFI_IFR_NOT_EQUAL_OP";
				break;
			case EFI_IFR_GREATER_THAN_OP: //0x31 - Push TRUE if one expression is greater than another expression.
				opcodeName = L"EFI_IFR_GREATER_THAN_OP";
				break;
			case EFI_IFR_GREATER_EQUAL_OP: //0x32 - Push TRUE if one expression is greater than or equal to another expression.
				opcodeName = L"EFI_IFR_GREATER_EQUAL_OP";
				break;
			case EFI_IFR_LESS_THAN_OP: //0x33 - Push TRUE if one expression is less than another expression.
				opcodeName = L"EFI_IFR_LESS_THAN_OP";
				break;
			case EFI_IFR_LESS_EQUAL_OP: //0x34 - Push TRUE if one expression is less than or equal to another expression.
				opcodeName = L"EFI_IFR_LESS_EQUAL_OP";
				break;
			case EFI_IFR_BITWISE_AND_OP: //0x35 - Bitwise-AND two unsigned integers and push the result.
				opcodeName = L"EFI_IFR_BITWISE_AND_OP";
				break;
			case EFI_IFR_BITWISE_OR_OP: //0x36 - Bitwise-OR two unsigned integers and push the result.
				opcodeName = L"EFI_IFR_BITWISE_OR_OP";
				break;
			case EFI_IFR_BITWISE_NOT_OP: //0x37 - Bitwise-NOT an unsigned integer and push the result.
				opcodeName = L"EFI_IFR_BITWISE_NOT_OP";
				break;
			case EFI_IFR_SHIFT_LEFT_OP: //0x38 - Shift an unsigned integer left by a number of bits and push the result.
				opcodeName = L"EFI_IFR_SHIFT_LEFT_OP";
				break;
			case EFI_IFR_SHIFT_RIGHT_OP: //0x39 - Shift an unsigned integer right by a number of bits and push the result.
				opcodeName = L"EFI_IFR_SHIFT_RIGHT_OP";
				break;
			case EFI_IFR_ADD_OP: //0x3A - Add two unsigned integers and push the result.
				opcodeName = L"EFI_IFR_ADD_OP";
				break;
			case EFI_IFR_SUBTRACT_OP: //0x3B - Subtract two unsigned integers and push the result.
				opcodeName = L"EFI_IFR_SUBTRACT_OP";
				break;
			case EFI_IFR_MULTIPLY_OP: //0x3C - Multiply two unsigned integers and push the result.
				opcodeName = L"EFI_IFR_MULTIPLY_OP";
				break;
			case EFI_IFR_DIVIDE_OP: //0x3D - Divide one unsigned integer by another and push the result.
				opcodeName = L"EFI_IFR_DIVIDE_OP";
				break;
			case EFI_IFR_MODULO_OP: //0x3E - Divide one unsigned integer by another and push the remainder.
				opcodeName = L"EFI_IFR_MODULO_OP";
				break;
			case EFI_IFR_RULE_REF_OP: //0x3F //Evaluate a rule
				opcodeName = L"EFI_IFR_RULE_REF_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_QUESTION_REF1_OP: //0x40 - Push a question’s value
				opcodeName = L"EFI_IFR_QUESTION_REF1_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_QUESTION_REF2_OP: //0x41 - Push a question’s value
				opcodeName = L"EFI_IFR_QUESTION_REF2_OP";
                questionId = _GetQuestionToken((UINT8*)opHeader);
				break;
			case EFI_IFR_UINT8_OP: //0x42 - Push an 8-bit unsigned integer
				opcodeName = L"EFI_IFR_UINT8_OP";
				break;
			case EFI_IFR_UINT16_OP: //0x43 - Push a 16-bit unsigned integer.
				opcodeName = L"EFI_IFR_UINT16_OP";
				break;
			case EFI_IFR_UINT32_OP: //0x44 - Push a 32-bit unsigned integer
				opcodeName = L"EFI_IFR_UINT32_OP";
				break;
			case EFI_IFR_UINT64_OP: //0x45 - Push a 64-bit unsigned integer.
				opcodeName = L"EFI_IFR_UINT64_OP";
				break;
			case EFI_IFR_TRUE_OP: //0x46 - Push a boolean TRUE.
				opcodeName = L"EFI_IFR_TRUE_OP";
				break;
			case EFI_IFR_FALSE_OP: //0x47 - Push a boolean FALSE
				opcodeName = L"EFI_IFR_FALSE_OP";
				break;
			case EFI_IFR_TO_UINT_OP: //0x48 - Convert expression to an unsigned integer
				opcodeName = L"EFI_IFR_TO_UINT_OP";
				break;
			case EFI_IFR_TO_STRING_OP: //0x49 - Convert expression to a string
				opcodeName = L"EFI_IFR_TO_STRING_OP";
				break;
			case EFI_IFR_TO_BOOLEAN_OP: //0x4A - Convert expression to a boolean.
				opcodeName = L"EFI_IFR_TO_BOOLEAN_OP";
				break;
			case EFI_IFR_MID_OP: //0x4B - Extract portion of string or buffer
				opcodeName = L"EFI_IFR_MID_OP";
				break;
			case EFI_IFR_FIND_OP: //0x4C - Find a string in a string.
				opcodeName = L"EFI_IFR_FIND_OP";
				break;
			case EFI_IFR_TOKEN_OP: //0x4D - Extract a delimited byte or character string from buffer or string.
				opcodeName = L"EFI_IFR_TOKEN_OP";
				break;
			case EFI_IFR_STRING_REF1_OP: //0x4E - Push a string
				opcodeName = L"EFI_IFR_STRING_REF1_OP";
				break;
			case EFI_IFR_STRING_REF2_OP: //0x4F - Push a string
				opcodeName = L"EFI_IFR_STRING_REF2_OP";
				break;
			case EFI_IFR_CONDITIONAL_OP: //0x50 - Duplicate one of two expressions depending on result of the first expression.
				opcodeName = L"EFI_IFR_CONDITIONAL_OP";
				break;
			case EFI_IFR_QUESTION_REF3_OP: //0x51 - Push a question’s value from a different form.
				opcodeName = L"EFI_IFR_QUESTION_REF3_OP";
				break;
			case EFI_IFR_ZERO_OP: //0x52 - Push a zero
				opcodeName = L"EFI_IFR_ZERO_OP";
				break;
			case EFI_IFR_ONE_OP: //0x53 //Push a one
				opcodeName = L"EFI_IFR_ONE_OP";
				break;
			case EFI_IFR_ONES_OP: //0x54 - Push a 0xFFFFFFFFFFFFFFFF.
				opcodeName = L"EFI_IFR_ONES_OP";
				break;
			case EFI_IFR_UNDEFINED_OP: //0x55 - Push Undefined
				opcodeName = L"EFI_IFR_UNDEFINED_OP";
				break;
			case EFI_IFR_LENGTH_OP: //0x56 - Push length of buffer or string.
				opcodeName = L"EFI_IFR_LENGTH_OP";
				break;
			case EFI_IFR_DUP_OP: //0x57 - Duplicate top of expression stack
				opcodeName = L"EFI_IFR_DUP_OP";
				break;
			case EFI_IFR_THIS_OP: //0x58 - Push the current question’s value
				opcodeName = L"EFI_IFR_THIS_OP";
				break;
			case EFI_IFR_SPAN_OP: //0x59 - Return first matching/non-matching character in a string
				opcodeName = L"EFI_IFR_SPAN_OP";
				break;
			case EFI_IFR_VALUE_OP: //0x5A - Provide a value for a question
				opcodeName = L"EFI_IFR_VALUE_OP";
				break;
			case EFI_IFR_DEFAULT_OP: //0x5B - Provide a default value for a question.
				opcodeName = L"EFI_IFR_DEFAULT_OP";
				break;
			case 0x5C: //0x5C - Define a Default Type Declaration
				opcodeName = L"EFI_IFR_DEFAULTSTORE_OP";
				break;
			case 0x5D: //0x5D - Create a standards-map form.
				opcodeName = L"EFI_IFR_FORM_MAP_OP";
				break;
			case EFI_IFR_CATENATE_OP: //0x5E - Push concatenated buffers or strings.
				opcodeName = L"EFI_IFR_CATENATE_OP";
				break;
			case EFI_IFR_GUID_OP: //0x5F - An extensible GUIDed op-code
				opcodeName = L"EFI_IFR_GUID_OP";
				break;
			case 0x60: //0x60 - Returns whether current user profile contains specified setup access privileges.
				opcodeName = L"EFI_IFR_SECURITY_OP";
				break;
			case 0x61: //0x61 - Specify current form is modal
				opcodeName = L"EFI_IFR_MODAL_TAG_OP";
				break;
			case 0x62: //0x62 - Establish an event group for refreshing a forms-based element.
				opcodeName = L"EFI_IFR_REFRESH_ID_OP";
				break;
			default:
				opcodeName = L"Invalid Opcode";
				validOpCode = FALSE;
				break;
		}

		if(opHeader->OpCode == EFI_IFR_END_OP){
			pScopeCount--;
			count = pScopeCount;
		}
		while(count){
			if(CurrentForm) SETUP_DEBUG_TSE (  "    ");
                    
			count--;
		}

		if(CurrentForm) SETUP_DEBUG_TSE (  "\n\n%s, len: %d\n", opcodeName, opHeader->Length);
        
        if(CurrentForm && questionId) SETUP_DEBUG_TSE (  "questionId: 0x%x  %s \n", questionId, HiiGetString(Page->PageData.PageHandle , questionId  ));    
        
        if(opHeader->Length==0)
        {
            //validOpCode = FALSE ;
            goto DONE;
        }

		
        if(validOpCode){
			UINTN index = 0, j = 0;
			UINTN size = opHeader->Length;
			UINT8 *temp = (UINT8 *)opHeader;
			UINTN sCount = pScopeCount;

			if(size){		
				for(index = 0; index < size; ){
					sCount = pScopeCount;
    				while(sCount){
						sCount--;
					}
                    
                    if(CurrentForm) SETUP_DEBUG_TSE ( "[0x%08x (%04d)]  ", index, index);

					for(j = 0; (j < 16) && (temp != NULL); index++, j++)
                    {
						if(index >= size){
							break;
						}
                        if(CurrentForm && j==8) SETUP_DEBUG_TSE ( "- ");
            			if(CurrentForm) SETUP_DEBUG_TSE ( "%02x ", (UINT8)temp[index]);
					}
					if(CurrentForm)SETUP_DEBUG_TSE ("\n");

				}
			}
		}

		if(opHeader->Scope){
			pScopeCount++;
		}
		
		i += opHeader->Length;
		validOpCode = TRUE;
	}

DONE:
	if(formSet){
		EfiLibSafeFreePool(formSet);
	}

	pScopeCount = 0;

	return status;
}

#endif //End of TSE_DEBUG_MESSAGES
//EIP75481  Support TSE debug print infrastructure
//EIP 80426 : START
#define ASSERT_ERROR_STATUS(assertion)		if(EFI_ERROR(assertion)) goto DONE
#define MAX_PAGES_TO_PROCESS				50
UINT32 gProcessedPages[MAX_PAGES_TO_PROCESS];
UINT32 gProPageOffset = 0;
UINT32 gCurrLoadVarIndex = 0; //Used to track which variable is getting loaded
UINT8 *gCurrLoadVarBuf = (UINT8 *)NULL; //Used to store current variable buffer

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   _GetControlInfo
//
// Description: Returns pointer to the CONTROL_INFO struct of given CtrlIndex
//
// Input:	UINT32 PgIndex - Page index containing the control
//			UINT32 CtrlIndex - HII Control index
//			CONTROL_INFO **CtrlInfo - Pointer to the CONTROL_INFO structure
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetPageInfo(UINT32 PgIndex, PAGE_INFO **PageInfo);
EFI_STATUS _GetControlInfo(UINT32 PgIndex, UINT32 CtrlIndex, CONTROL_INFO **CtrlInfo)
{
  EFI_STATUS status = EFI_SUCCESS;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  if(pageInfo->PageHandle == NULL)
  {
    status = EFI_NOT_FOUND; //If the page handle is invalid, then page may contain incorrect control data. Return error.
  }
  ASSERT_ERROR_STATUS(status);

  if(CtrlIndex > pageInfo->PageControls.ControlCount)
  {
    status = EFI_INVALID_PARAMETER;
    goto DONE;
  }

  *CtrlInfo = (CONTROL_INFO*)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[CtrlIndex]);

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     	GetNumOfControls
//
// Description:   	Get the Number of Control for a Page
//
// Input:     		IN  UINT32 PgIndex
//                	OUT UINT32 *numOfControls
//
// Output:			EFI_STATUS 
//                  EFI_SUCCESS
//                  EFI_NOT_READY
//                  EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetNumOfControls(UINT32 PgIndex, UINT32 *NumOfControls)
{
  EFI_STATUS status = EFI_SUCCESS;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);

  *NumOfControls = pageInfo->PageControls.ControlCount;

DONE:
  return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CleanCurrLoadVarBuffer
//
// Description: Cleans the temporary variables
//
// Input:   None
//
// Output:  VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanCurrLoadVarBuffer()
{
    if(gCurrLoadVarBuf!= NULL) {
        MemFreePointer(&gCurrLoadVarBuf);
    }
    gCurrLoadVarBuf = (UINT8 *)NULL;
    gCurrLoadVarIndex = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		_DestinationPageProcessed
//
// Description:		Checks whether the page is already processed or not.
//
// Input:			UINT32 PageID
//
// Output:			BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _DestinationPageProcessed(UINT32 PageID)
{
  BOOLEAN isProcessed = FALSE;
  UINT32 index = 0;

  for(index = 0; index < gProPageOffset; index++)
  {
    if(PageID == gProcessedPages[index])
    {
      isProcessed = TRUE;
      break;
    }
  }
  return isProcessed;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		_GetDefaultNvramVariableIDList
//
// Description:		To get the default variable names.
//
// Input:			UINT32 FormID
//					BOOLEAN DefaultsFlag
//					BOOLEAN *ResetVal
//					BOOLEAN *ValChanged
//
// Output:			EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetDefaultNvramVariableIDList(UINT32 PageID, BOOLEAN DefaultsFlag, BOOLEAN *ResetVal, BOOLEAN *ValChanged)
{
  EFI_STATUS				status = EFI_SUCCESS;
  UINT16					CtrlDataSize = 0;
  UINT32					count = 0;
  UINT32					index = 0;
  UINTN						CurVarSize = 0;
  CONTROL_INFO				*ctrlInfo;
  NVRAM_VARIABLE			*nvPtr = gVariableList;
  NVRAM_VARIABLE			*defaults = gOptimalDefaults;
  EFI_IFR_QUESTION_HEADER	*questionHdr = (EFI_IFR_QUESTION_HEADER *)NULL;

  gProcessedPages[gProPageOffset++] = PageID;

  status = GetNumOfControls(PageID, &count);
  ASSERT_ERROR_STATUS(status);

  for(index = 0; index < count; index++)
  {
    //Iterating for all controls
    status = _GetControlInfo(PageID , index, &ctrlInfo);
    ASSERT_ERROR_STATUS(status);

    // CONTROL_TYPE_TEXT is a special case here since its value is not
    // in the varstore. If this is a text control, continue.
	if(ctrlInfo->ControlType == CONTROL_TYPE_TEXT){
	  continue;
	}

    if((ctrlInfo->ControlType == CONTROL_TYPE_SUBMENU) || (ctrlInfo->ControlType == CONTROL_TYPE_REF2))
    {
      if(_DestinationPageProcessed(ctrlInfo->ControlDestPageID) == FALSE)
      {
		status = _GetDefaultNvramVariableIDList(ctrlInfo->ControlDestPageID, DefaultsFlag, ResetVal, ValChanged);
        ASSERT_ERROR_STATUS(status);
      }
    }
    if(ctrlInfo->ControlType == CONTROL_TYPE_POPUP_STRING && DefaultsFlag)
    {
      UINT16 defaultToken = 0;
      CHAR16 * defaultValue = NULL;

      // First, check if the control has a default value. During parsing, the
      // Control Data Width is set to zero if there is no default value.
      if (ctrlInfo->ControlDataWidth == 0) {
        continue;       // move to next control if this one has no default. 
      }

      // Get the Default String Id
      defaultToken = *(UINT16*)((UINT8*)ctrlInfo + sizeof(CONTROL_INFO) + ctrlInfo->ControlDataWidth);
      // Get the string corresponding to the StringId
      defaultValue = HiiGetString(ctrlInfo->ControlHandle, defaultToken);
      // Set the default value to nvPtr
      questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8*)ctrlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));
      if(defaultValue)
      {
        if(EfiStrCmp(defaultValue, (CHAR16 *)&nvPtr[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset]) != 0)
        {
          EfiStrCpy((CHAR16 *)&nvPtr[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset], defaultValue);
          *ValChanged = TRUE;

          if(ctrlInfo->ControlFlags.ControlReset)
          {
            //ControlReset reset requested.
            *ResetVal |= ctrlInfo->ControlFlags.ControlReset;
          }
        }
      }
      continue;
    }

    if(ctrlInfo->ControlFlags.ControlEvaluateDefault)
    {
      UINT64 defaults = 0;
      UINT16 size = EvaluateControlDefault(ctrlInfo, &defaults);

      if(DefaultsFlag)
      {
        //Loading Defaults for control
        questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8*)ctrlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));

        if(MemCmp((UINT8*)&nvPtr[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset], (UINT8*)&defaults, size) != 0)
        {
          //defaults and Memory value donot match. Copying defaults to memory value
          MemCopy( &nvPtr[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset], &defaults, size);
          *ValChanged = TRUE;

          if(ctrlInfo->ControlFlags.ControlReset)
          {
            //ControlReset reset requested
            *ResetVal |= ctrlInfo->ControlFlags.ControlReset;
          }
        }
		continue;
      }
    }

	if(DefaultsFlag) { //If loading defaults, use the data size given in CONTROL_INFO. Else get the data size using GetControlDataLength().
		CtrlDataSize = ctrlInfo->ControlDataWidth;
	}
	else {
		CtrlDataSize = (UINT16)GetControlDataLength(ctrlInfo);
	}

    if(CtrlDataSize == 0) {
     //Control Data Width for control %s is 0\n", HiiGetString(ctrlInfo->ControlHandle, ctrlInfo->QuestionId));
      continue;
    }

    if(ctrlInfo->ControlVariable <= gVariables->VariableCount)
    {
      if(DefaultsFlag == TRUE)
      {
        //Loading Defaults for control
        questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8*)ctrlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));

        if(MemCmp((UINT8*)&nvPtr[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset], (UINT8*)&defaults[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset], ctrlInfo->ControlDataWidth) != 0)
        {
         //defaults and Memory value donot match. Copying defaults to memory value
          MemCopy( &nvPtr[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset], &defaults[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset], ctrlInfo->ControlDataWidth);
          *ValChanged = TRUE;

          if(ctrlInfo->ControlFlags.ControlReset)
          {
            //ControlReset reset requested.
            *ResetVal |= ctrlInfo->ControlFlags.ControlReset;
          }
        }
      }
      else
      {
        UINT8 *tempLoadVarBuff = (UINT8 *)NULL;

        if(gCurrLoadVarBuf != NULL)
        {
          if(gCurrLoadVarIndex != ctrlInfo->ControlVariable)
          {
            tempLoadVarBuff = VarGetNvram( ctrlInfo->ControlVariable, &CurVarSize );
            if(tempLoadVarBuff != NULL){
              CleanCurrLoadVarBuffer();
              gCurrLoadVarBuf = tempLoadVarBuff;
              gCurrLoadVarIndex = ctrlInfo->ControlVariable;
            }
          }
        }
        else
        {
          tempLoadVarBuff = VarGetNvram( ctrlInfo->ControlVariable, &CurVarSize );
          if(tempLoadVarBuff != NULL){
            CleanCurrLoadVarBuffer();
            gCurrLoadVarBuf = tempLoadVarBuff;
            gCurrLoadVarIndex = ctrlInfo->ControlVariable;
          }
        }

        if(gCurrLoadVarBuf != NULL)
        {
          if(tempLoadVarBuff != NULL){
            gCurrLoadVarIndex = ctrlInfo->ControlVariable;
          }
          questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8*)ctrlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));
          MemCopy( &nvPtr[ctrlInfo->ControlVariable].Buffer[questionHdr->VarStoreInfo.VarOffset], &gCurrLoadVarBuf[questionHdr->VarStoreInfo.VarOffset], CtrlDataSize);
        }
      }
    }
  }

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		LoadNvram
//
// Description:		Intermediate function to get the nvram variables to restore.
//
// Parameter:		UINT32 PageID
//
// Return Value:	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LoadNvram(UINT32 PageID)
{
    EFI_STATUS status = EFI_SUCCESS;

    gProPageOffset = 0;
    MemSet(gProcessedPages, MAX_PAGES_TO_PROCESS * sizeof(UINT32), 0);
    status = _GetDefaultNvramVariableIDList(PageID, FALSE, NULL, NULL);
    ASSERT_ERROR_STATUS(status);

DONE:
    CleanCurrLoadVarBuffer();
    return status;
}
//EIP 80426 : END

//EIP81814 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     LoadDefaults
//
// Description:   function to load the defaults to the nvram cache
//
// Parameter:     UINT32 FormID - form identifier
//				  BOOLEAN *ResetVal - Reboot flag of the control variable
//				  BOOLEAN * ValChanged - flag to check whether the value changed
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LoadDefaults(UINT32 FormID, BOOLEAN *ResetVal, BOOLEAN * ValChanged)
{
    EFI_STATUS status = EFI_SUCCESS;
    UINT32 *varIDList = (UINT32*)EfiLibAllocateZeroPool(gVariables->VariableCount * sizeof(UINT32));


    if(varIDList == NULL)
    {
        status = EFI_OUT_OF_RESOURCES;

        goto DONE;
    }

    gVarOffset = 0;
//    gProFormOffset = 0;
//    MemSet(gProcessedForms, MAX_FORMS_TO_PROCESS, 0);
    CleargProcessedForms ();

    //inplace of updating all the variables, update only the variables that are modified
    //status = _GetVariableIDList(FormID, &varIDList);
    status = _GetDefaultNvramVariableIDList(FormID, TRUE, ResetVal, ValChanged);
    ASSERT_ERROR_STATUS(status);

DONE:
    if (varIDList) {
        MemFreePointer(&varIDList);
    }
    CleanCurrLoadVarBuffer();


    return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   _InconsistenceCheck
//
// Description: Checks if the controls in a page is inconsistent
//
// Input:	PAGE_INFO *PgInfo - Input page info
//			UINT16 *ErrStrToken - Pointer to the output error code
//
// Output:	BOOLEAN flag - TRUE if inconsistence, else FALSE
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _InconsistenceCheck(PAGE_INFO *PgInfo, UINT16 *ErrStrToken)
{
  CONTROL_INFO *ctrlInfo = NULL;
  EFI_IFR_INCONSISTENT_IF *inconsistentIf = NULL;
  BOOLEAN flag = FALSE;
  UINT32 i = 0;

  //Find out if there is inconsistent value in any of the controls
  for(i=0; i < PgInfo->PageControls.ControlCount; i++)
  {
    
    ctrlInfo = (CONTROL_INFO*)((UINTN)(gControlInfo) + PgInfo->PageControls.ControlList[i]);
    //Check if there is a CONTROL_TYPE_MSGBOX in this page
    if(ctrlInfo->ControlType == CONTROL_TYPE_MSGBOX)
    {
      
      if(CheckControlCondition(ctrlInfo) == COND_INCONSISTENT)
      {
        
        inconsistentIf = (EFI_IFR_INCONSISTENT_IF*)ctrlInfo->ControlConditionalPtr;
        *ErrStrToken = inconsistentIf->Error;
        flag = TRUE;
        goto DONE;
      }
    }
  }

DONE:
  
  return flag;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   _NoSubmitCheck
//
// Description: Checks if the controls in a page has no submit
//
// Input:	CONTROL_INFO *ctrlInfo - Input control info
//			UINT16 *ErrStrToken - Pointer to the output error code
//
// Output:	BOOLEAN flag - TRUE if nosubmit, else FALSE
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _NoSubmitCheck(CONTROL_INFO *ctrlInfo, UINT16 *ErrStrToken)
{
	EFI_IFR_NO_SUBMIT_IF *nosubmitIf = NULL;
	BOOLEAN flag = FALSE;

	

    if(ctrlInfo->ControlType == CONTROL_TYPE_MSGBOX)
    {
		
		if(CheckControlCondition(ctrlInfo) == COND_NOSUBMIT)
		{
			
			nosubmitIf = (EFI_IFR_NO_SUBMIT_IF*)ctrlInfo->ControlConditionalPtr;
			*ErrStrToken = nosubmitIf->Error;
			flag = TRUE;
		}
    }
  
	
	return flag;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     _GetVariableIDList
//
// Description:		function to get the list of all variables that are need to update
//
// Parameter:     UINT32 FormID,
//                UINT32 **VarIDList
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetVariableIDList(UINT32 FormID, UINT32 **VarIDList)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT32 count = 0;
  UINT32 index = 0;
  UINT32 varIndex = 0;
  UINT32 *varPtr = NULL;
  CONTROL_INFO *ctrlInfo;

  
  if(*VarIDList == NULL || VarIDList == NULL)
  {
    status = EFI_INVALID_PARAMETER;
  
    goto DONE;
  }
  AddEntryIngProcessedForms (FormID);
//  gProcessedForms[gProFormOffset++] = FormID;
  status = GetNumOfControls(FormID, &count);
  ASSERT_ERROR_STATUS(status);
  varPtr = *VarIDList;
  for(index = 0; index < count; index++)
  {
  
    status = _GetControlInfo(FormID , index, &ctrlInfo);
    ASSERT_ERROR_STATUS(status);

    if((ctrlInfo->ControlType == CONTROL_TYPE_SUBMENU) || (ctrlInfo->ControlType == CONTROL_TYPE_REF2))
    {

      if(_DestinationFormProcessed(ctrlInfo->ControlDestPageID) == FALSE)
      {

        _GetVariableIDList(ctrlInfo->ControlDestPageID, VarIDList);
      }
    }

    for(varIndex = 0; varIndex < gVariables->VariableCount; varIndex++)
    {

      if(varPtr[varIndex] == ctrlInfo->ControlVariable)
      {

        break;
      }
    }
    if(varIndex == gVariables->VariableCount)
    {

      varPtr[gVarOffset++] = ctrlInfo->ControlVariable;
    }
  }

DONE:

  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		_DestinationFormProcessed 
//
// Description:		Is this form Processed
//
// Parameter:		IN	UINT32 FormID
//					
//				  
// Return Value:	BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN _DestinationFormProcessed(UINT32 FormID)
{
  BOOLEAN isProcessed = FALSE;
  UINT32 index = 0;

  
  for(index = 0; index < gProFormOffset; index++)
  {
    
    if(FormID == gProcessedForms[index])
    {
      
      isProcessed = TRUE;
      break;
    }
  }
  
  return isProcessed;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		IsNoSubmitOfForms 
//
// Description:		Is this formset or form has the no submit if
//
// Parameter:		IN	UINT32 FormID
//					OUT	UINT16* ErrToken
//				  
// Return Value:	BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsNoSubmitOfForms(UINT32 FormID, UINT16* ErrToken)
{
	BOOLEAN flag = FALSE;
	EFI_STATUS status = EFI_SUCCESS;
	UINT32	count = 0;
	UINT32	index = 0;
	CONTROL_INFO	*ctrlInfo;
	
  
//	gProcessedForms[gProFormOffset++] = FormID;
	AddEntryIngProcessedForms (FormID);
	
	status = GetNumOfControls(FormID, &count);
	ASSERT_ERROR_STATUS(status);

	for(index = 0; index < count; index++)
	{
	    
		status = _GetControlInfo(FormID, index, &ctrlInfo);
		ASSERT_ERROR_STATUS(status);

		if((ctrlInfo->ControlType == CONTROL_TYPE_SUBMENU)//If submenu traverse recursively through the sub forms
			|| (ctrlInfo->ControlType == CONTROL_TYPE_REF2))
		{
			
			if(_DestinationFormProcessed(ctrlInfo->ControlDestPageID) == FALSE)//If the form has not be processed already
			{
				flag = IsNoSubmitOfForms(ctrlInfo->ControlDestPageID, ErrToken);
				if(flag)
				{
					break;
				}
			}
		}
		if(_NoSubmitCheck(ctrlInfo, ErrToken) == TRUE)//if the control is no submit if
		{
			flag = TRUE;
			break;
		}
	}//end of for loop of controls

DONE:
	
 	return flag;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     CheckforNosubmitIf 
//
// Description:   Check for no submit if 
//
// Parameter:     UINT32 FormID, BOOLEAN Recursive, UINT16 *ErrToken
//				  
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CheckforNosubmitIf(UINT32 FormID, BOOLEAN Recursive, UINT16 *ErrToken)
{
	EFI_STATUS status = EFI_SUCCESS;
	BOOLEAN flag = FALSE;

	if(Recursive)//To check all the forms in the formset
	{
//		gProFormOffset = 0;
//		MemSet(gProcessedForms, MAX_FORMS_TO_PROCESS, 0);
	   CleargProcessedForms ();
		flag = IsNoSubmitOfForms(FormID,ErrToken);
	}
	else//for single form ID
	{
		PAGE_INFO *PgInfo = NULL;
		EFI_STATUS status = EFI_SUCCESS;
		UINT32 i = 0;
		CONTROL_INFO *ctrlInfo = NULL; 

		status = _GetPageInfo(FormID, &PgInfo);
		ASSERT_ERROR_STATUS(status);

		for(i=0; i < PgInfo->PageControls.ControlCount; i++)
		{
			
			ctrlInfo = (CONTROL_INFO*)((UINTN)(gControlInfo) + PgInfo->PageControls.ControlList[i]);
			if(_NoSubmitCheck(ctrlInfo, ErrToken) == TRUE)
			{
				flag = TRUE;
				break;
			}
		}
	}
  
	if(flag)
	{
		status = EFI_NOSUBMIT_VALUE;
	}

DONE:
	return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   _GetControlFlag
//
// Description: Gets attribute flag for a given CtrlIndex in a page
//
// Input:	UINT32 PgIndex - Page index containing the control
//			UINT32 CtrlIndex - Control index
//			CONTROL_FLAGS **CtrlFlag - Pointer to the flag attribute structure
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetControlFlag(UINT32 PgIndex, UINT32 CtrlIndex, CONTROL_FLAGS **CtrlFlag)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  
  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *CtrlFlag = &ctrlInfo->ControlFlags;

DONE:
  
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetNumOfPages
//
// Description:   Get the Total Number of HII Form Pages to display
//
// Parameter:     OUT UINT32 *numOfPages
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_OUT_OF_RESOURCES
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetNumOfPages(UINT32 *NumOfPages)
{
  EFI_STATUS status = EFI_SUCCESS;

  
  if(LibInitialized == FALSE)
  {
    status = EFI_NOT_READY;
    
    goto DONE;
  }

  *NumOfPages = gPages->PageCount;

DONE:
  
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetPageTitle
//
// Description:   Get the Page Title String Index
//
// Parameter:     IN  UINT32 PgIndex
//                OUT UINT16 *titleToken
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPageTitle(UINT32 PgIndex, UINT16 *TitleToken)
{
  EFI_STATUS status = EFI_SUCCESS;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);

  *TitleToken = pageInfo->PageTitle;

DONE:
  return status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetPageHandle
//
// Description:   Get the Handle for the Page
//
// Parameter:     IN  UINTN           PgIndex
//                OUT EFI_HII_HANDLE  *handle
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPageHandle(UINT32 PgIndex, EFI_HII_HANDLE  *Handle)
{
  EFI_STATUS status = EFI_SUCCESS;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);

  *Handle = pageInfo->PageHandle;
DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetPageIdIndex
//
// Description:   Get the page ID index for the Page
//
// Parameter:     IN  UINTN  PgIndex
//                OUT UINT16 *PgIdIndex
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPageIdIndex(UINT32 PgIndex, UINT16 *PgIdIndex)
{
  EFI_STATUS status = EFI_SUCCESS;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);

  *PgIdIndex = pageInfo->PageIdIndex;

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     IsParentPage
//
// Description:   Is this page a parent page
//
// Parameter:     IN  UINT32 PgIndex
//
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsParentPage(UINT32 PgIndex)
{
  EFI_STATUS status = EFI_SUCCESS;
  BOOLEAN isTrue = FALSE;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);
  isTrue = pageInfo->PageParentID == 0? TRUE : FALSE;

DONE:
  return isTrue;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetPageHiiId
//
// Description:   Get the Page Title String Index
//
// Parameter:     IN  UINT32 PgIndex
//                OUT UINT16 *PageId
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPageHiiId(UINT32 PgIndex, UINT16 *PageId)
{
  EFI_STATUS status = EFI_SUCCESS;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);

  *PageId = pageInfo->PageFormID;

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetPageParentId
//
// Description:   Get the parent page ID from the page index
//
// Parameter:     IN  UINT32 PgIndex - Current page Index/ID
//                OUT UINT16 *PageParentId - Parent page ID
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPageParentId(UINT32 PgIndex, UINT16 *PageParentId)
{
  EFI_STATUS status = EFI_SUCCESS;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);

  *PageParentId = pageInfo->PageParentID;

DONE:
  return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   GetCtrlsDestCtrlId
//
// Description: Returns the QuestionID to select in the destination page
//
// Input:	UINT32 PgIndex - ASL page ID
//          UINT32 CtrlIndex - Control index, Lib control ID
//          UINT16 *DestCtrlId - Destination control index
//
// Output:	EFI_STATUS status
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetCtrlsDestCtrlId(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *DestCtrlId)
{
  EFI_STATUS status = EFI_NOT_FOUND;
  CONTROL_INFO *ctrlInfo = (CONTROL_INFO *)NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *DestCtrlId = ctrlInfo->DestQuestionID;

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlType
//
// Description:   Get the AMI Control Type
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                OUT UINT16 *ctrlType
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetControlType(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlType)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *CtrlType = ctrlInfo->ControlType;

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlQuestionPrompt
//
// Description:   Get the Control Question Prompt's String Id
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                OUT UINT16 *ctrlPrompt
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetControlQuestionPrompt(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlPrompt)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *CtrlPrompt = ctrlInfo->QuestionId;
DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlHelpStr
//
// Description:   Get the Control Help String ID
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                OUT UINT16 *ctrlHelp
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetControlHelpStr(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlHelp)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *CtrlHelp = ctrlInfo->ControlHelp;
DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     _GetCheckBoxOptions
//
// Description:   Get the List of Options for the Checkbox Control
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                OUT UINTN  *optionCount
//                OUT OPTION_LIST *optionArray
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetCheckBoxOptions(CONTROL_INFO *CtrlInfo, UINT32 *OptionCount, OPTION_LIST **OptionArray)
{
  EFI_STATUS status = EFI_SUCCESS;
  OPTION_LIST *optList = NULL;
  OPTION_LIST *temp = NULL;
  EFI_IFR_CHECKBOX *checkBoxOp = (EFI_IFR_CHECKBOX*)(CtrlInfo->ControlPtr);
  UINT32 index = 0;

  *OptionCount = CHECKBOX_OPTION_COUNT;
  for(index = 0; index < *OptionCount; index++)
  {
  
    temp = (OPTION_LIST*)EfiLibAllocateZeroPool(sizeof(OPTION_LIST));
    if(temp == NULL)
    {
      status = EFI_OUT_OF_RESOURCES;
  
      goto DONE;
    }

    if(*OptionArray == NULL)
    {

      *OptionArray = temp;
    }else
    {

      if(optList){
        optList->Next = temp;
	  }
    }
    optList = temp;

    // Option will be set In the Application
    temp->Option = 0;
    temp->Value = index;
    temp->Flag = ((checkBoxOp->Flags & EFI_IFR_CHECKBOX_DEFAULT) == EFI_IFR_CHECKBOX_DEFAULT)? OPTION_DEFAULT : 0;
    temp->Flag = ((checkBoxOp->Flags & EFI_IFR_CHECKBOX_DEFAULT_MFG) == EFI_IFR_CHECKBOX_DEFAULT_MFG)? OPTION_DEFAULT_MFG : 0;
    temp->Next = NULL;
  }


DONE:

  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     IsControlCheckBox
//
// Description:   Check if the control is a check box
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsControlCheckBox(UINT32 PgIndex, UINT32 CtrlIndex)
{
  BOOLEAN isCheckBox = FALSE;
  CONTROL_INFO *ctrlInfo = NULL;
  EFI_IFR_OP_HEADER *opHeader = NULL;

  _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);

  opHeader = (EFI_IFR_OP_HEADER*)ctrlInfo->ControlPtr;
  isCheckBox = (opHeader->OpCode == EFI_IFR_CHECKBOX_OP)? TRUE : FALSE;

  return isCheckBox;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlDataWidth
//
// Description:   Get the Data size
//
// Parameter:     UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *controlWidth
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetControlDataWidth(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlWidth)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *CtrlWidth = (UINT16)GetControlDataLength(ctrlInfo)/*ctrlInfo->ControlDataWidth*/;
DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlDestinationPage
//
// Description:
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                OUT UINT16 *ctrlDestPg
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetControlDestinationPage(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *CtrlDestPg)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *CtrlDestPg = ctrlInfo->ControlDestPageID;
DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlAccess
//
// Description:   Get the Control Access Specifier for a Control
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//
// Return Value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetControlAccess(UINT32 PgIndex, UINT32 CtrlIndex)
{
  CONTROL_FLAGS *flags = NULL;

  _GetControlFlag(PgIndex, CtrlIndex, &flags);
  
  return (UINT8)flags->ControlAccess;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlRefresh
//
// Description:   Get the Control Refresh for a Control
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//
// Return Value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetControlRefresh(UINT32 PgIndex, UINT32 CtrlIndex)
{
  CONTROL_FLAGS *flags = NULL;
  
  _GetControlFlag(PgIndex, CtrlIndex, &flags);
  
  return (UINT8)flags->ControlRefresh;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     IsControlVisible
//
// Description:   Get the Control Visiblity for a Control
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsControlVisible(UINT32 PgIndex, UINT32 CtrlIndex)
{
  CONTROL_FLAGS *flags = NULL;
  
  _GetControlFlag(PgIndex, CtrlIndex, &flags);
  
  return (BOOLEAN)flags->ControlVisible;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     IsControlResetRequired
//
// Description:   Get the Control Reset status for a Control
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsControlResetRequired(UINT32 PgIndex, UINT32 CtrlIndex)
{
  CONTROL_FLAGS *flags = NULL;
  
  _GetControlFlag(PgIndex, CtrlIndex, &flags);
  
  return (BOOLEAN)flags->ControlReset;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     IsControlReadOnly
//
// Description:   Get the Control Readonly Specifier for a Control
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsControlReadOnly(UINT32 PgIndex, UINT32 CtrlIndex)
{
  CONTROL_FLAGS *flags = NULL;
  
  _GetControlFlag(PgIndex, CtrlIndex, &flags);
  
  return (BOOLEAN)flags->ControlReadOnly;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     IsControlInteractive
//
// Description:   Get the Control Interactive Specifier for a Control
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//
// Return Value:  EFI_STATUS
//                    BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsControlInteractive(UINT32 PgIndex, UINT32 CtrlIndex)
{
    CONTROL_FLAGS *flags = (CONTROL_FLAGS *)NULL;
    EFI_STATUS status = EFI_SUCCESS;
    BOOLEAN isInteractive = FALSE;

    status = _GetControlFlag(PgIndex, CtrlIndex, &flags);
    ASSERT_ERROR_STATUS(status);

    if(flags != NULL){
        isInteractive = (BOOLEAN)flags->ControlInteractive;
    }

DONE:
    return isInteractive;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     EvaluateControlCondition
//
// Description:   Evaluate control HII expression and return display Result
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                OUT UINTN *expResult
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EvaluateControlCondition(UINT32 PgIndex, UINT32 CtrlIndex, UINTN *ExpResult)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *ExpResult = CheckControlCondition(ctrlInfo);

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetQuestionValue
//
// Description:   Get the Question Value
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                OUT UINT8  *Value
//                OUT UINTN  *ValueSize
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//                    EFI_OUT_OF_RESOURCES
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetQuestionValue(UINT32 PgIndex, UINT32 CtrlIndex, UINT8 **Value, UINTN *ValueSize)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_IFR_QUESTION_HEADER *questionHdr = NULL;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *ValueSize = GetControlDataLength(ctrlInfo);
  *Value = (UINT8*)EfiLibAllocateZeroPool(*ValueSize);
  if(*Value == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    
    goto DONE;
  }

  if(ctrlInfo->ControlType == CONTROL_TYPE_TEXT)
  {
    UINT16 textTwo = ((EFI_IFR_TEXT*)(ctrlInfo->ControlPtr))->TextTwo;
    
    MemCopy(*Value, &textTwo, *ValueSize);
    goto DONE;
  }

  questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8*)ctrlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));
  status = VarGetValue(ctrlInfo->ControlVariable, questionHdr->VarStoreInfo.VarOffset, *ValueSize, Value);
  ASSERT_ERROR_STATUS(status);

DONE:
  
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     SetQuestionValue
//
// Description:   Set the Value for a Question
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                IN  UINT8  *Value
//                IN  UINTN  ValueSize
//                OUT UINT16 *ErrStrToken
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetQuestionValue(UINT32 PgIndex, UINT32 CtrlIndex, UINT8 *Value, UINTN ValueSize, UINT16 *ErrStrToken)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_IFR_QUESTION_HEADER *questionHdr = NULL;
  CONTROL_INFO *ctrlInfo = NULL;
  PAGE_INFO *pgInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  questionHdr = (EFI_IFR_QUESTION_HEADER*)((UINT8*)ctrlInfo->ControlPtr + sizeof(EFI_IFR_OP_HEADER));
  status = VarSetValue(ctrlInfo->ControlVariable, questionHdr->VarStoreInfo.VarOffset, ValueSize, Value);
  ASSERT_ERROR_STATUS(status);

  status = _GetPageInfo(PgIndex, &pgInfo);
  ASSERT_ERROR_STATUS(status);

  if(_InconsistenceCheck(pgInfo, ErrStrToken) == TRUE)
  {
    
    status = EFI_INCONSISTENT_VALUE;
  }

DONE:  
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     SaveQuestionValues
//
// Description:   Save all the values to the system
//
// Parameter:     VOID
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SaveQuestionValues(UINT32 FormID)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_STATUS tempStatus = EFI_SUCCESS;
  NVRAM_VARIABLE *nvPtr;
  UINT32 i = 0;
  UINT32 *varIDList = (UINT32*)EfiLibAllocateZeroPool(gVariables->VariableCount * sizeof(UINT32));
  
  if(varIDList == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    
    goto DONE;
  }

  nvPtr = gVariableList;
  gVarOffset = 0;
//  gProFormOffset = 0;
//  MemSet(gProcessedForms, MAX_FORMS_TO_PROCESS, 0);
  CleargProcessedForms ();
  status = _GetVariableIDList(FormID, &varIDList);
  ASSERT_ERROR_STATUS(status);
  for ( i = 0; i < gVariables->VariableCount; i++)
  {
   
    if(nvPtr[varIDList[i]].Buffer == NULL)
    {
   
      continue;
    }
    tempStatus = VarSetNvram(varIDList[i], nvPtr[varIDList[i]].Buffer, nvPtr[varIDList[i]].Size);
    if(EFI_ERROR(tempStatus))
    {
      status = tempStatus;
    }
  }

DONE:
  if (varIDList) {
  	MemFreePointer(&varIDList);
  }


  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     FreeOptionList
//
// Description:   
//
// Parameter:     OPTION_LIST *OptionArray
//
// Return Value:  VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FreeOptionList(OPTION_LIST *OptionArray)
{
  OPTION_LIST *optList = OptionArray;

  do
  {
    optList = OptionArray;
    OptionArray = OptionArray->Next;
    if(optList)
    {
      MemFreePointer(&optList);
    }
  }while(OptionArray);
  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlDisplayFormat
//
// Description:   
//
// Parameter:     UINT32 PgIndex
//                UINT32 CtrlIndex
//                UINT16 *Format
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetControlDisplayFormat(UINT32 PgIndex, UINT32 CtrlIndex, UINT16 *Format)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);
  if(ctrlInfo->ControlType == CONTROL_TYPE_NUMERIC)
  {
   
    *Format = ((EFI_IFR_NUMERIC*)ctrlInfo->ControlPtr)->Flags & EFI_IFR_DISPLAY;
  }

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlMinMax
//
// Description:   
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                UINT64 *Min
//                UINT64 *Max
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//                    EFI_OUT_OF_RESOURCES
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetControlMinMax(UINT32 PgIndex, UINT32 CtrlIndex, UINT64 *Min, UINT64 *Max)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  switch(ctrlInfo->ControlType)
  {
    case CONTROL_TYPE_NUMERIC:
    case CONTROL_TYPE_PASSWORD:
    case CONTROL_TYPE_POPUP_STRING:

    *Min = UefiGetMinValue(ctrlInfo->ControlPtr);
    *Max = UefiGetMaxValue(ctrlInfo->ControlPtr);
    break;
  default:

    break;
  }

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetControlDefault
//
// Description:   
//
// Parameter:     IN  UINT32 PgIndex
//                IN  UINT32 CtrlIndex
//                UINT64 *Def
//                BOOLEAN Optimal
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetControlDefault(UINT32 PgIndex, UINT32 CtrlIndex,UINT8 *Def, BOOLEAN Optimal)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  
  if(Def == NULL)
  {
    status = EFI_INVALID_PARAMETER;
  
    goto DONE;
  }
  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  switch(ctrlInfo->ControlDataWidth)
  {
    /*
    * ctrlInfo[sizeof(ctrlInfo)]
    * Used when user selects load Optimal value
    *
    * ctrlInfo[sizeof(ctrlInfo) + valSize]
    * Used when user selects load optimal value
    */
  case 1: // BYTE

    *Def = Optimal? *((UINT8 *) ((UINT8 *)ctrlInfo + sizeof(*ctrlInfo))) :
      *((UINT8 *) ((UINT8 *)ctrlInfo + sizeof(*ctrlInfo) + ctrlInfo->ControlDataWidth));
    break;
  case 2: //WORD

    *((UINT16*)Def) = Optimal? *((UINT16 *) ((UINT8 *)ctrlInfo + sizeof(*ctrlInfo))) :
      *((UINT16 *) ((UINT8 *)ctrlInfo + sizeof(*ctrlInfo) + ctrlInfo->ControlDataWidth));
    break;
  case 4: //DWORD

    *((UINT32*)Def) = Optimal? *((UINT32 *) ((UINT8 *)ctrlInfo + sizeof(*ctrlInfo))) :
      *((UINT32 *) ((UINT8 *)ctrlInfo + sizeof(*ctrlInfo) + ctrlInfo->ControlDataWidth));
    break;
  case 8: //QWORD

    *((UINT64*)Def) = Optimal? *((UINT64 *) ((UINT8 *)ctrlInfo + sizeof(*ctrlInfo))) :
      *((UINT64 *) ((UINT8 *)ctrlInfo + sizeof(*ctrlInfo) + ctrlInfo->ControlDataWidth));
    break;
  default:
    break;
  }

DONE:

  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetOrderedListMaxEntries
//
// Description: Create a Timer Event
//
// Input:       UINT32 PgIndex, UINT32 CtrlIndex, UINT8 *MaxEntry
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetOrderedListMaxEntries(UINT32 PgIndex, UINT32 CtrlIndex, UINT8 *MaxEntry)
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *ctrlInfo = NULL;

  status = _GetControlInfo(PgIndex, CtrlIndex, &ctrlInfo);
  ASSERT_ERROR_STATUS(status);

  *MaxEntry = 0;
  if(ctrlInfo->ControlType == CONTROL_TYPE_ORDERED_LIST)
  {
    *MaxEntry = UefiGetMaxEntries(ctrlInfo->ControlPtr);
  }
DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetOrderedListOptionDataWidth
//
// Description:   Gets OrderedList Data Width
//
// Parameter:     CONTROL_INFO *ControlInfo, UINT32 *DataWidth
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetOrderedListOptionDataWidth(CONTROL_INFO *ControlInfo, UINT32 *DataWidth)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_IFR_OP_HEADER *OpHeader = NULL;
  EFI_IFR_ONE_OF_OPTION *OneOfOptionOp = NULL;

  OpHeader = (EFI_IFR_OP_HEADER*)ControlInfo->ControlPtr;

  if(OpHeader->OpCode != EFI_IFR_ORDERED_LIST_OP)
  {
    Status = EFI_UNSUPPORTED;
    goto DONE;
  }

  do
  {
    OpHeader = (EFI_IFR_OP_HEADER*)((UINT8*)ControlInfo->ControlPtr + OpHeader->Length);
  }while(OpHeader->OpCode != EFI_IFR_ONE_OF_OPTION_OP);

  OneOfOptionOp = (EFI_IFR_ONE_OF_OPTION*)OpHeader;

  switch(OneOfOptionOp->Type)
  {
  case EFI_IFR_TYPE_NUM_SIZE_16:
    *DataWidth = sizeof(UINT16);
    break;
  case EFI_IFR_TYPE_NUM_SIZE_32:
    *DataWidth = sizeof(UINT32);
    break;
  case EFI_IFR_TYPE_NUM_SIZE_64:
    *DataWidth = sizeof(UINT64);
    break;
  case EFI_IFR_TYPE_NUM_SIZE_8:
  default:
    *DataWidth = sizeof(UINT8);
    break;
  }

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetOrderedListDataTypeWidth
//
// Description:   Gets OrderedList DataType Width
//
// Parameter:     UINT32 PgIndex, UINT32 CtrlIndex, UINT32 *DataWidth
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetOrderedListDataTypeWidth(UINT32 PgIndex, UINT32 CtrlIndex, UINT32 *DataWidth)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CONTROL_INFO *CtrlInfo = NULL;

  Status = _GetControlInfo(PgIndex, CtrlIndex, &CtrlInfo);
  if(EFI_ERROR(Status))
  {
    goto DONE;
  }

  Status = GetOrderedListOptionDataWidth(CtrlInfo, DataWidth);

DONE:
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     IsPageRefreshable
//
// Description:   Is this page can be refreshable
//
// Parameter:     IN  UINT32 PgIndex
//
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsPageRefreshable(UINT32 PgIndex)
{
  EFI_STATUS status = EFI_SUCCESS;
  BOOLEAN isTrue = FALSE;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);
  isTrue = pageInfo->PageFlags.PageRefresh ? TRUE : FALSE;

DONE:
  return isTrue;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     IfNoCommitVariable
//
// Description:   Is this a no commit variable 
//
// Parameter:     IN  UINT32 PgIndex
//				  IN  UINT32 CtrlIndex
//
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IfNoCommitVariable(UINT32 PgIndex, UINT32 CtrlIndex)
{
    EFI_STATUS status = EFI_SUCCESS;
    BOOLEAN isTrue = FALSE;
    CONTROL_INFO *CtrlInfo = NULL;
    VARIABLE_INFO *varInfo = NULL;

    status = _GetControlInfo(PgIndex, CtrlIndex, &CtrlInfo);
    ASSERT_ERROR_STATUS(status);
    varInfo = VarGetVariableInfoIndex(CtrlInfo->ControlVariable);
    if((varInfo != NULL) && (varInfo->ExtendedAttibutes /*& AMI_SPECIAL_NO_COMMIT_VARIABLE*/)){ //If the variable is valid and set to NO_COMMIT
        isTrue = TRUE;
    }
DONE:
    return isTrue;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     IdentifyFormHasDefault 
//
// Description:   Is this formset has the default set
//
// Parameter:     IN  UINT32 FormID
//				  
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IdentifyFormHasDefault(UINT32 FormID)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINT32	count = 0;
	UINT32	index = 0;
	CONTROL_INFO	*ctrlInfo;
	BOOLEAN isDefault = FALSE;

//	gProcessedForms[gProFormOffset++] = FormID;
	AddEntryIngProcessedForms (FormID);
	
	status = GetNumOfControls(FormID, &count);
	ASSERT_ERROR_STATUS(status);

	for(index = 0; index < count; index++)
	{

		status = _GetControlInfo(FormID, index, &ctrlInfo);
		ASSERT_ERROR_STATUS(status);

		if((ctrlInfo->ControlType == CONTROL_TYPE_SUBMENU)//If submenu traverse recursively through the sub forms
			|| (ctrlInfo->ControlType == CONTROL_TYPE_REF2))
		{

			if(_DestinationFormProcessed(ctrlInfo->ControlDestPageID) == FALSE)//If the form has not be processed already
			{
				isDefault = IdentifyFormHasDefault(ctrlInfo->ControlDestPageID);
				if(isDefault)
				{
					break;
				}
			}
		}

		if(ctrlInfo->ControlType == CONTROL_TYPE_CHECKBOX || //Check for the control is checkbox 
			ctrlInfo->ControlFlags.ControlEvaluateDefault || //or if the control has the Evaluate default bit set
			ctrlInfo->ControlDataWidth)						 // or if the ControlDataWidth is set to the size of the defaults
		{
			isDefault = TRUE;
			break;
		}
	}//end of for loop of controls

DONE:
	return isDefault;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     IsFormsetHasDefault 
//
// Description:   Is this formset has the default set
//
// Parameter:     IN  UINT32 FormID
//				  
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsFormsetHasDefault(UINT32 FormID)
{
	BOOLEAN isDefault = FALSE;

//	gProFormOffset = 0;
//	MemSet(gProcessedForms, MAX_FORMS_TO_PROCESS, 0);
	CleargProcessedForms ();
	isDefault = IdentifyFormHasDefault(FormID);

	return isDefault;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetPageGuidFromFormId
//
// Description: To get the form GUID from the page index
//
// Input:       UINT32 PgIndex
//				EFI_GUID *FormGuid
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPageGuidFromPgIndex(UINT32 PgIndex, EFI_GUID *FormGuid)
{
	EFI_STATUS status = EFI_INVALID_PARAMETER;
	PAGE_INFO *pgInfo = (PAGE_INFO *)NULL;
	PAGE_ID_INFO *pageIdInfo = (PAGE_ID_INFO*)NULL;

	status = _GetPageInfo(PgIndex, &pgInfo);
	ASSERT_ERROR_STATUS(status);

	if(gPages && gPageIdList && pgInfo)
	{
		pageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[pgInfo->PageIdIndex]);
		if(pageIdInfo)
		{
			MemCopy(FormGuid, &pageIdInfo->PageGuid, sizeof(EFI_GUID));
		}
	}

DONE:
	return status;
}
//EIP81814 Ends

//EIP 86885 Starts
//<AMI_PHDR_START>
//--------------------------------------------------------------------------------------
// Procedure:   UefiVarsetnvramforCurrentform
//
// Description: Save the values for the passed pageID
//				If this function is not called as part of browser action then it is
//				caller responsibility to reset the gProFormOffset and gProcessedForms
//				gProFormOffset = 0;
//				MemSet (gProcessedForms, MAX_FORMS_TO_PROCESS, 0);
//
// Input:       UINT32 - page ID to save the values
//
// Output:      EFI_STATUS - Status of the operation
//--------------------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiVarsetnvramforCurrentform (UINT32 FormID)
{
	EFI_STATUS 	status = EFI_SUCCESS;
	UINT32 		count = 0;
	UINT32 		index = 0;
	CONTROL_INFO *ctrlInfo;
	UINT8 			*tempLoadVarBuff = (UINT8 *)NULL;
	UINT8 			*CurrentValue = NULL;
	UINTN			CurVarSize = 0;
	UINT32 		size = 0;
	UINT32 		offset = 0;
	VARIABLE_INFO 	*varInfo = (VARIABLE_INFO *)NULL;
	
//	gProcessedForms [gProFormOffset++] = FormID;
	AddEntryIngProcessedForms (FormID);
	
	status = GetNumOfControls (FormID, &count);
	ASSERT_ERROR_STATUS (status);
	
	for(index = 0; index < count; index++)
	{
		status = _GetControlInfo(FormID , index, &ctrlInfo);
		ASSERT_ERROR_STATUS(status);

		if (NULL == ctrlInfo->ControlPtr) //EIP-Setup crashes when clicking Discard and Exit goto control in simulator
			continue;
	
		if((ctrlInfo->ControlType == CONTROL_TYPE_SUBMENU) || (ctrlInfo->ControlType == CONTROL_TYPE_REF2))
		{
			if(_DestinationFormProcessed(ctrlInfo->ControlDestPageID) == FALSE)
			{
				UefiVarsetnvramforCurrentform(ctrlInfo->ControlDestPageID);
			}
			continue;
		}
		tempLoadVarBuff = VarGetNvram( ctrlInfo->ControlVariable, &CurVarSize );
		if (NULL == tempLoadVarBuff)
		{
			continue;
		}
		offset = UefiGetQuestionOffset (ctrlInfo->ControlPtr);
		if(CONTROL_TYPE_ORDERED_LIST == ctrlInfo->ControlType)
		{
			UINTN Type = 0;
			UefiGetValidOptionType (ctrlInfo, &Type, &size);
			size = (UefiGetMaxEntries (ctrlInfo->ControlPtr)) * size;
		}
		else
		{
			size = UefiGetWidth(ctrlInfo->ControlPtr);
		}
		if (0 == size)
		{
			continue;
		}
		CurrentValue = EfiLibAllocateZeroPool(size);
		if(CurrentValue == NULL)
		{
			return EFI_OUT_OF_RESOURCES;
		}
		status = VarGetValue(ctrlInfo->ControlVariable, offset, size, CurrentValue );
		if (!EFI_ERROR (status))
		{
			MemCopy ( tempLoadVarBuff+offset, CurrentValue, size );
			
			 varInfo = VarGetVariableInfoIndex (ctrlInfo->ControlVariable);
			 if(varInfo == NULL)
		     {
        		continue;
    		 }
			 
			if((varInfo->ExtendedAttibutes & AMI_SPECIAL_VARIABLE_NO_SET) == AMI_SPECIAL_VARIABLE_NO_SET)
			{
				// Don't save the variable
				continue;
			}
			else
			{
				if(UefiIsEfiVariable(ctrlInfo->ControlVariable, varInfo))
				{
					VarSetNvramName( varInfo->VariableName, &varInfo->VariableGuid, varInfo->VariableAttributes, tempLoadVarBuff, CurVarSize );
				}
				else
				{
					UefiVarSetNvram(varInfo, tempLoadVarBuff, VAR_ZERO_OFFSET, CurVarSize);
				}
			}
		}
		MemFreePointer ((VOID **)&tempLoadVarBuff);
		MemFreePointer ((VOID **)&CurrentValue);
	}
DONE:
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UefiLoadPreviousValuesforCurrentform
//
// Description: Loads previous value for the current form
//
// Input:       FormID - Current page ID
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiLoadPreviousValuesforCurrentform(UINT32 FormID)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINT32 	count = 0;
	UINT32 	index = 0;
	CONTROL_INFO *ctrlInfo;
	UINT8 	*tempLoadVarBuff = (UINT8 *)NULL;
	UINT8 	*CurrentValue = NULL;
	UINTN		CurVarSize = 0;
	UINT32	size = 0;
	UINT32 	offset = 0;
	
//	gProcessedForms [gProFormOffset++] = FormID;
	AddEntryIngProcessedForms (FormID);
	
	status = GetNumOfControls (FormID, &count);
	ASSERT_ERROR_STATUS (status);
	
	for(index = 0; index < count; index++)
	{
		status = _GetControlInfo(FormID , index, &ctrlInfo);
		ASSERT_ERROR_STATUS(status);

		if (NULL == ctrlInfo->ControlPtr) //EIP-126997 Avoid setup crash
			continue;

		if((ctrlInfo->ControlType == CONTROL_TYPE_SUBMENU) || (ctrlInfo->ControlType == CONTROL_TYPE_REF2))
		{
			if(_DestinationFormProcessed(ctrlInfo->ControlDestPageID) == FALSE)
			{
				UefiVarsetnvramforCurrentform(ctrlInfo->ControlDestPageID);
			}
		}
		tempLoadVarBuff = VarGetNvram (ctrlInfo->ControlVariable, &CurVarSize);
		if (NULL == tempLoadVarBuff)
		{
			continue;
		}
		offset = UefiGetQuestionOffset (ctrlInfo->ControlPtr);
		if (CONTROL_TYPE_ORDERED_LIST == ctrlInfo->ControlType)
		{
			UINTN Type = 0;
			UefiGetValidOptionType (ctrlInfo, &Type, &size);
			size = (UefiGetMaxEntries (ctrlInfo->ControlPtr)) * size;
		}
		else
		{
			size = UefiGetWidth (ctrlInfo->ControlPtr);
		}
		CurrentValue = EfiLibAllocateZeroPool(size);
		if(CurrentValue == NULL)
		{
			return EFI_OUT_OF_RESOURCES;
		}
		status = VarGetValue (ctrlInfo->ControlVariable, offset, size, CurrentValue);
		if (!EFI_ERROR (status))
		{
			MemCopy (gVariableList [ctrlInfo->ControlVariable].Buffer + offset, tempLoadVarBuff + offset, size);
		}
		MemFreePointer ((VOID **)&tempLoadVarBuff);
		MemFreePointer ((VOID **)&CurrentValue);
	}
DONE:
	return status;
}
//EIP 86885 Ends

///////////////EIP 162180 Starts//////////////////////////
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CleargProcessedForms
//
// Description: Clears gProcessedForms data
//
// Input:       void
//
// Output:      void
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void CleargProcessedForms (void)
{
	gProFormOffset = 0;
	MemSet(gProcessedForms, (gProFormOffsetAllocCount * sizeof (UINT32)), 0);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AddEntryIngProcessedForms
//
// Description: Adds the formid in gProcessedForms
//
// Input:       UINT32 FormID
//
// Output:      void
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void AddEntryIngProcessedForms (UINT32 FormID)
{
	if (gProFormOffset >= gProFormOffsetAllocCount)													//Check if enough size has been already allocated
	{
		gProcessedForms = MemReallocateZeroPool (gProcessedForms, gProFormOffsetAllocCount * sizeof (UINT32), (gProFormOffsetAllocCount + MAX_FORMS_TO_PROCESS) * sizeof (UINT32));
		if (NULL == gProcessedForms)
		{
			return;
		}
		gProFormOffsetAllocCount += MAX_FORMS_TO_PROCESS;
	}
	gProcessedForms [gProFormOffset++] = FormID;
}
///////////////EIP 162180 Ends//////////////////////////
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************