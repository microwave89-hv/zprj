//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2014, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                     Phone: (770)-246-8600                   **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/CommonHelper.c $
//
// $Author: Premkumara $
//
// $Revision: 158 $
//
// $Date: 9/05/14 2:28p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/CommonHelper.c $
// 
// 158   9/05/14 2:28p Premkumara
// Moved below functions from HiiString21.c to CommonHelper.c
//  - IsSupportDefaultForStringControl()
//  - IsTseBestTextGOPModeSupported()
// 
// 157   9/05/14 6:29a Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 156   8/28/14 10:08a Premkumara
// [TAG] 			EIP174031
// [Category] 		Improvement
// [Description] 	Removed TODO comments and added proper comments in those
// places
// [Files] 			commonoem.c, commonhelper.c, special.c, submenu.c,
// minisetupext.c, uefi21wapper.c and legacy.c
// 
// 155   8/28/14 7:27a Premkumara
// [TAG]		EIP107833, 125388
// [Category]	Improvement
// [Symptom:]	Setting best text and GOP mode while using TSEPostinterfaces
// before TSE or after TSE.
// [Files]		Protocol.c, AMITSE.sdl, CommonHelper.c, MiniSetup.sdl,
// PostMgmtc, PostmgmtExt.c, MessagBox.c
// 
// 154   8/28/14 4:28a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 153   7/12/14 5:44p Arunsb
// 
// 152   5/08/14 9:09p Arunsb
// [TAG]  			EIP162981
// [Category]  	Improvement
// [Description]  	Configuring default Password through SDL token.
// Based on RT_ACCESS_SUPPORT_IN_HPKTOOL, attribute is set for amitsesetup
// variable
// 
// 151   5/08/14 4:26p Arunsb
// [TAG]  			EIP162197
// [Category]  	Improvement
// [Description]  	Password encode feature modify to encode using Hashing
// based on token.
// IsPasswordSupportNonCaseSensitive moved to PasswordEncode module
// 
// 150   5/02/14 9:22p Arunsb
// EIP141986 changes reverted.
// 
// 149   5/02/14 2:43p Premkumara
// Resolve build error for undeclared fn CheckandDeactivateSoftkbd()
// 
// 148   5/02/14 2:09p Premkumara
// [TAG]  		EIP140123 
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	While showing secureboot error msg mouse is not move and
// get hang. Softkbd is displaying
// [RootCause]  	MouseClickEvent is not stopped while boot to any option.
// So clicking outside msg box causes displaying
// softkbd and mouse is not init at this phase.
// [Solution]  	Initialized mouse and deactivating any softkbd activated
// before showing secureboot error msg box.
// [Files]  		CommonHelper.c, CommonOem.c, MessageBox.c
// 
// 147   5/02/14 1:09p Premkumara
// [TAG]	                EIP128526
// [Category]	Improvement
// [Description]	Disable ESC action in BBS popup menu
// [Files]	AMITSE.sdl, CommonHelper.c, TseLite/MinisetupExt.c 
// 
// 146   5/02/14 11:08a Premkumara
// [TAG]  		EIP141986
// [Category]  	New Feature
// [Description]  	Made Grayed controls to focus-able when token
// TSE_SETUP_GRAYOUT_SELECTABLE
//  is enabled and can't edit the values
// [Files]  		AMITSE.sdl,CommonHelper.c,frame.c,Label.c,minisetupext.h,
// numeric.c,PopupPassword.c,PopupSel.c,PopupString.c,SubMenu.c
// 
// 145   5/02/14 8:37a Premkumara
// [TAG]  		EIP162981
// [Category]  	Improvement
// [Description]  	Configuring default Password through SDL token
// [Files]  		AMITSE.sdl, CommonHelper.c, Minisetup.c, TseAdvanced.c
// 
// 144   5/02/14 6:47a Premkumara
// [TAG]  		EIP164232
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When password keyboard is launched and mouse pointer is
// placed on softkbd mouse will flickers continously.
// [RootCause]  	MouseRefresh and MouseStop is calling contiously in loop
// so mouse pointer get flickers
// [Solution]  	When mouse pointer is on softkbd and is static then stop
// calling MouseRefresh and MouseFreeze
// [Files]  		PopupPassword.c, CommonHelper.c, Mouse.c
// 
// 143   5/02/14 6:08a Premkumara
// [TAG]  		EIP123431 
// [Category]  	Improvement
// [Description]  	Need create one override token to TSE.
// [Files]  		CommonHelper.c, AMITSE.sdl
// 
// 142   5/02/14 3:53a Premkumara
// [TAG]  		EIP151966
// [Category]  	Improvement
// [Description]  	Added the implementation for getting the BIOS build
// year dynamically 
// from TimeStamp.h file and updated the Build year in copyright message
// in both Setup and POST.
// [Files]  		style.c,style.c,style.c,notify.c,minisetupext.c,CommonHelper
// .c,
// AmiTSEStr.uni,AMITSE.mak
// 
// 141   5/02/14 3:00a Arunsb
// IsHashingSupported function removed since TSE_HASH_PASSWORD can he
// handled directly. Since implementation is there in binary only.
// 
// 140   5/02/14 2:30a Arunsb
// Reverted 137341 change
// 
// 137   5/02/14 2:13a Arunsb
// [TAG]  		EIP142690
// [Category]  	Improvement
// [Description]  	Create token OVERRIDE_CsmBBSBootOptionName for function
// CsmBBSBootOptionName
// [Files]  		Amitse.sdl and commonhelper.c
// 
// 135   5/02/14 1:19a Arunsb
// [TAG]		EIP137341
// [Category]	Bug Fix
// [Symptom:]	The use of T_ACPI_OEM_ID and T_ACPI_OEM_TBL_ID when
// generating the BGRT does not display blank characters.
// [Root Cause]	The macro CONVERT_TO_STRING() will consume the blank char,
// so there's nothing different between the use of " AMI" and "AMI" when
// showing in the ACPI table.
// [Solution]	The functions GetACPIOEMID and GetACPIOEMTableID should no
// longer use T_ACPI_OEM_ID and T_ACPI_OEM_TBL_ID in token.h 
// But should use the tokens ACPI_OEM_ID_MAK and ACPI_OEM_TBL_ID_MAK from
// AcpiOemElinks.h
// [Files]	CommonHelper.c
// 
// 134   2/11/14 7:03p Arunsb
// Updated in synch with Aptio5.
// For EIPs 129750, 130997, 131969, 131739, 130529, 126746 and 148693
// 
// 133   12/05/13 1:00a Premkumara
// [TAG]	EIP140123
// [Category]	Bug Fix
// [Symptom:]	Not able to close SecureError Msgbox using touch/mouse and
// softkeyboard is displaying while displaying secureerror msgbox 
// [Root Cause]	Mouse is not not initilalized when showing msg box during
// ProceedToBoot and sofkbd is not cleared in this case also.
// [Solution]	CommonHelper.c
// [Files]	CommonHelper.c
// 
// 132   12/04/13 3:40p Premkumara
// [TAG]  		EIP136946
// [Category]  	Improvement
// [Description]  	Made gBootFileName shell boot compatable with x32, x64
// and ARM for aptio4&5
// [Files]  		CommonHelper.c
// 
// 131   12/03/13 1:26p Premkumara
// [TAG]	EIP128526
// [Category]	Improvement
// [Description]	Disable ESC action in BBS popup menu
// [Files]	AMITSE.sdl, CommonHelper.c, TseLite/MinisetupExt.c
// 
// 130   12/03/13 12:52p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 129   11/26/13 10:24a Premkumara
// [TAG]  		EIP123431 
// [Category]  	Improvement
// [Description]  	Need create one override token to TSE.
// [Files]  		CommonHelper.c, AMITSE.sdl
// 
// 128   11/26/13 1:30a Premkumara
// [TAG]  		EIP118342
// [Category]  	Improvement
// [Description]  	Show meaningful error message when HDD is locked after
// reached maximum unlocking attempt.
// [Files]  		TseAdvanced.c, CommonHelper.c
// 
// 127   8/06/13 3:58a Premkumara
// [TAG]  		EIP130529 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	When entered into setup with User mode and On pressing
// "Restore User Defaults" SystemAccess variable is loading and the user
// mode is changes to Admin mode so the controls are editable
// [RootCause]  	LoadUserDefaultsSilently() function is loading defaults
// for all types of variable
// [Solution]  	Skipping loading SystemAccess variable while loading
// defaults for user default variable.
// [Files]  		TseAdvanced.c, AMITSE.sdl, CommonHelper.c 
// 
// 126   4/18/13 9:49a Arunsb
// Wrapper function introduced to avoid build error in 2.0 build
// 
// 125   3/29/13 12:15p Premkumara
// [TAG]  		EIP97611
// [Category]  	New Feature
// [Description]  	PrintScreen Support in TSE
// [Files]  		AMITSE.sdl, CommonHelper.c, HotKeyBin.h, AddBootOption.c,
// Page.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 124   3/25/13 8:46a Premkumara
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
// - uefi2.0\UefiWapper20.c
// - uefi2.0\HiiCallback.c
// - uefi2.0\hii.h
// - uefi2.0\hii.c 
// 
// 123   3/16/13 3:58a Rajashakerg
// [TAG]  		EIP107221 
// [Category]  	Improvement
// [Description]  	Logo disappear after HDD password verified
// [Files]  		CommonHelper.c, notify.c, minisetupext.c
// 
// 122   3/12/13 6:56a Rajashakerg
// [TAG]  		EIP105167 
// [Category]  	Improvement
// [Description]  	Making the specify setup items departing from F2/F3
// effect.
// [Files]  		AMITSE.sdl, CommonHelper.c, callback.c, minisetupext.h,
// PopupPassword.c, SubMenu.c, HiiCallback.c
// 
// 121   2/20/13 11:42p Rajashakerg
// [TAG]  		EIP104521
// [Category]  	Improvement
// [Description]  	Customer needs AMITSE modification to popup boxes so
// highlighted choices can be seen via VT100 console redirection
// [Files]  		AMITSE.sdl, CommonHelper.c, Ezport\stylecommon.c,
// EzportPlus\stylecommon.c, Legacy\stylecommon.c
// 
// 120   2/19/13 4:15a Premkumara
// [TAG]  		EIP103540 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	 	Currently _BootBuildFVDevicePath function using FV
// protocol alone not FV2 protocol. So applications loading from ffs are
// not loading properly.
// [RootCause]  	_BootBuildFVDevicePath() function used
// gEfiFirmwareVolumeProtocolGuid only not gEfiFirmwareVolume2ProtocolGuid
// [Solution]  	Used gEfiFirmwareVolume2ProtocolGuid based on
// PISpecVersion
// [Files]  		CommonHelper.c, Boot.c
// 
// 119   2/11/13 6:10a Premkumara
// [TAG]  		EIP112628
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	(JP000E)SETUP_GO_TO_EXIT_PAGE_ON_EXIT_KEY does not work on
// 4.6.2_TSE_2_15_1234
// [RootCause]  	The Exit FormID value will change if any form is
// generated before Exit page
// [Solution]  	Handled Exit FormID from Binary and handling Exit FormID
// from binary
// [Files]  		Ezport.c, Ezport.sdl, Legacy.c, Legacy.sdl, EzportPlus.c,
// EzportPlus.sdl
// 
// 118   2/10/13 11:51p Rajashakerg
// [TAG]  		EIP104521
// [Category]  	Improvement
// [Description]  	Customer needs AMITSE modification to popup boxes so
// highlighted choices can be seen via VT100 console redirection
// [Files]  		AMITSE.sdl, CommonHelper.c, Ezport\stylecommon.c,
// EzportPlus\stylecommon.c, Legacy\stylecommon.c
// 
// 117   2/06/13 9:07a Arunsb
// Checking in properly. Instead check in Alaska previously made in PBA.
// 
// 117   1/31/13 12:49p Arunsb
// [TAG]  		EIP109382
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Boot Device name incorrect when load default 
// [RootCause]  	Legacy offset in gbootdata corrupted so names displayed
// improperly.
// [Solution]  	Legacy offsets re-calculated properly
// [Files]  		CommonHelper.c, BootOnly\bbs.c and callback.c
// 
// 116   12/05/12 5:29a Rajashakerg
// [TAG]  		EIP103381 
// [Category]  	Improvement
// [Description]  	adopting SDL to control timeout spec
// [Files]  		AMITSE.sdl, CommonHelper.c, protocol.c
// 
// 115   10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 43    10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 113   9/21/12 12:30p Premkumara
// [TAG]  		EIP99022
// [Category]  	Improvement
// [Description]  	Tokenize the feature of flushing keyboard after every
// key read
// [Files]  		AMITSE.sdl, CommonHelper.c, TseAdvanced.c, Action.c
// 
// 112   9/17/12 5:59a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 110   9/12/12 5:21a Rajashakerg
// [TAG]  		EIP94205
// [Category]  	Improvement
// [Description]  	OEM needs Token to assign the display mode of SHELL
// [Files]  		AMITSE.sdl, boot.c, CommonHelper.c
// 
// 109   9/10/12 5:03a Rajashakerg
// [TAG]  		EIP93881 and 93873
// [Category]  	Improvement
// [Description]  	need keep system password after Load default and
// Password saved into NVRAM immediately(not buffer) while it is installed
// in TSE
// [Files]  		frame.c, callback.c, AMITSE.sdl, CommonHelper.c
// 
// 108   9/08/12 1:22p Arunsb
// [TAG]  		EIP100558
// [Category]  	New Feature
// [Description]  	Provide solution to display the small logo in (0,0)
// graphics position
// [Files]  		AMITSE.sdl, commonhelper.c, postmgmt.c and boot.c
// 
// 107   9/08/12 11:44a Arunsb
// [TAG]  		EIP99059
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	_ReInitializeSetupdataPointers function crashes in Hii.C
// when DyanmicPage processed with PageIdListSize =0
// [RootCause]  	Hii pack notification installed for
// SETUP_RUNTIME_IFR_PROCESSING is disabled also
// [Solution]  	Hii pack notification installed only if
// SETUP_RUNTIME_IFR_PROCESSING is enabled
// [Files]  		commonhelper.c and Hii.c
// 
// 106   9/06/12 1:06a Rajashakerg
// [TAG]  		EIP91410 
// [Category]  	Improvement
// [Description]  	TSE_MULTILINE_CONTROLS=1 makes one of option with max
// string looks not good.
// [Files]  		PopupSel.c, COmmonHelper.c, AMITSE.sdl
// 
// 105   9/03/12 3:07a Premkumara
// [TAG]  		EIP 96246
// [Category]  	Improvement
// [Description]  	Improvement of a boots override when firmware has a
// BootNext variable
// [Files]  		AMITSE.sdl, CommonHelper.c, FakeToken.c, AmiTSEStr.uni,
// TseAdvanced.c
// 
// 104   8/29/12 4:09p Arunsb
// [TAG]  		EIP94702
// [Description]  	Support for Native Resolution in POST/BOOT
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c, boot.c, logo.c,
// notify.c, postmgmt.c, ezport/stylecommon.c,
// ezportplus/stylecommon.c,legacy/stylecommon.c
// tselite\minisetupext.c
// 
// 103   8/29/12 12:35p Arunsb
// [TAG]  		EIP93521
// [Category]  	New Feature
// [Description]  	Support of ESRT
// [Files]  		amitse.sdl, bootflow.c, bootflow.h, commonhelper.c and
// dobmpmgr.c
// 
// 102   8/29/12 8:33a Premkumara
// [TAG]  		EIP 91364
// [Category]  	Improvement
// [Description]  	Token to disable the Cursor of TSE Password Dialog
// [Files]  		AMITSE.sdl, CommonHelper.c, Postmgmtext.c, PopupPassword.c,
// PopupString.c
// 
// 101   8/27/12 6:18a Premkumara
// [TAG]  		EIP 94616
// [Category]  	Improvement
// [Description]  	TSE should not wait for key if fast boot is in progress
// [Files]  		AMITSE.sdl, CommonHelper.c, Notify.c, Protocol.c
// 
// 100   8/23/12 6:31p Arunsb
// 
// 99    8/21/12 7:55p Arunsb
// [TAG]  		EIP93521
// [Category]  	New Feature
// [Description]  	Support of ESRT
// [Files]  		amitse.sdl, bootflow.c, bootflow.h, commonhelper.c and
// dobmpmgr.c
// 
// 98    6/28/12 8:19p Arunsb
// [TAG]  		EIP93524
// [Category]  	Improvement
// [Description]  	Invalidate the BGRT table when boot device launched
// from BBS popup or from shell or launched as second boot device
// [Files]  		commonhelper.c, boot.c and minisetup.c
// 
// 97    5/29/12 3:15a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 96    5/28/12 12:30p Premkumara
// [TAG]  		EIP67049 & 90224
// [Category]  	New Feature
// [Description]  	Support mouse drag operation in frame and list box
// [Files]  		CommonHelper.c, Frame.c, ListBox.c, Minisetupext.h
// 
// 95    5/28/12 12:00p Premkumara
// [TAG]  		EIP89272
// [Category]  	Improvement
// [Description]  	Change softkbd layout for numeric control
// [Files]  		CommonHelper.c, Mouse.c, Minisetup.h, C, Numeric.c
// 
// 94    5/28/12 11:24a Premkumara
// [TAG]  		EIP88912
// [Category]  	Improvement
// [Description]  	On password window display the softkbd with only with
// valid key's
// [Files]  		CommonHelper.c, Postmgmtext.c, Mouse.c, PopupPassword.c
// 
// 93    5/28/12 6:08a Rajashakerg
// [TAG]  		EIP89377
// [Category]  	Improvement
// [Description]  	Support to LegacyBootFailHook() in TSE.
// [Files]  		AMITSE.sdl, CommonHelper.c, boot.c
// 
// 92    5/28/12 5:35a Premkumara
// [TAG]  		EIP75236
// [Category]  	Improvement
// [Description]  	Add the support to control the GOP dependency in TSE
// notification.
// [Files]  		AMITSE.sdl, CommonHelper.c, Notify.c, Minisetup.h,
// Minisetup.sdl, protocol.c, FormBrowser.c, FormBrowser2.c
// 
// 91    5/28/12 2:49a Arunsb
// [TAG]  		EIP88447
// [Category]  	New Feature
// [Description]  	Disable UEFI boot option in BIOS setup should not load
// the default image \EFI\BOOT\BOOT{machine type short-name}.EFI
// [Files]  		Amitse.sdl, commonhelper.c and bootflow.c
// 
// 90    5/09/12 6:31p Premkumara
// EIP-83703 Updated CleareNumericShiftstate function
// 
// 89    5/09/12 5:09p Premkumara
// Removed #pragma optimize( "", off ) line
// 
// 88    5/09/12 5:06p Premkumara
// [TAG]  		EIP83703
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	TSE hangs while clicking on the "link training time out"
// value [this is happening while trying the specified steps immediate
// after bios flash
// [RootCause]  	When invalid range input is provided for numeric control
// ESC sequence is not provided if it is handled by the mouse.
// [Solution]  	Provided the proper ESC sequence to the control such that
// it close the Invalid Range Fail MsgBox when handled with the mouse and
// key.
// [Files]  		Numeric.c, CommonHelper.c
// 
// 87    4/27/12 9:23a Arunsb
// [TAG]  		EIP88895 
// [Category]  	Improvement
// [Description]  	Changing GetUefiSpecVersion as board module hook and
// also controlling callback spec version from TSE
// [Files]  		Amitse.sdl, amitse.mak and commonhelper.c
// 
// 86    4/27/12 1:40a Premkumara
// [TAG]  		EIP88527 
// [Category]  	Improvement
// [Description]  	Implement BGRT logo calculation based on Windows-8
// [Files]  		CommonHelper.c, Logo.c
// 
// 85    4/05/12 7:09a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 84    4/04/12 12:24a Rajashakerg
// [TAG]  		EIP86253 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Mouse and SoftKbd does not work after displaying "No option
// to boot to" in POST
// [RootCause]  	Mouse timer cleared once after displaying the "No option
// to boot to" in POST
// [Solution]  	Mouse timer cleared only when its going to boot.
// [Files]  		CommonHelper.c, commonoem.c, minisetupext.c, protocol.c
// 
// 83    2/04/12 9:08a Premkumara
// Moved DrawOEMImage with some modification from binary to source
// 
// 82    2/02/12 12:39a Premkumara
// [TAG]  		EIP75136 
// [Category]  	New Feature
// [Description]  	Generic support for logos in RomHoles
// [Files]  		CommomHelper.c, AMITSE.sdl, AMITSE.mak, LogoLib.h,
// 
// 81    2/01/12 4:55a Rajashakerg
// [TAG]  		EIP77256 
// [Category]  	Improvement
// [Description]  	Provide the Support to override the control Condition
// checking() generically. And provide customization to supress the
// controls with Security GUIDed opcode.
// [Files]  		AMITSE.sdl, CommonHelper.c, CtrlCond.c and CtrlCond.h
// 
// 80    1/31/12 1:17p Premkumara
// [TAG]  		EIP75136 
// [Category]  	New Feature
// [Description]  	Generic support for logos in RomHoles
// [Files]  		CommomHelper.c, AMITSE.sdl, AMITSE.mak, LogoLib.h,
// Postmgmt.c, AMILogo.h
// 
// 79    1/31/12 6:08a Arunsb
// [TAG]  		EIP81830
// [Category]  	Improvement
// [Description]  	Support to uninstall the BGRT on legacy boot.
// [Files]  		Commonhelper.c, postmgmt.c and boot.c
// 
// 78    1/27/12 12:03a Rajashakerg
// [TAG]  		EIP81623 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	IDE security login dialog was not displayed properly and
// observed password dialog label name displayed in text field 
// [RootCause]  	 IDE security module uses _ReportInBox() to draw the
// password text label which draws the text background. 
// [Solution]  	Provided the Gtse background color to the text label
// field. 
// [Files]  		CommonHelper.c
// 
// 77    1/25/12 7:59a Rajashakerg
// [TAG]  		EIP81617 
// [Category]  	Improvement
// [Description]  	Avoiding memory leaks in TSE
// [Files]  		hiistring21.c, CommonHelper.c, notify.c
// 
// 76    1/18/12 7:20a Premkumara
// [TAG]  		EIP79959 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Scree is not cleared properly while showing ""Secure boot
// violation"" warning message
// [RootCause]  	When any boot option fails then screen is not cleared
// properly before display Violatioin MessageBox in UefiBootFailHook()
// [Solution]  	When any boot option fails then clear screen before
// display Violatioin MessageBox to avoid screen corruption in
// UefiBootFailHook()
// [Files]  		CommonHelper.c
// 
// 75    1/18/12 4:54a Rajashakerg
// [TAG]  		EIP79962 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Mouse pointer corruption in GTSE
// [RootCause]  	For GTSE, the cordanites comparison logic went wrong for 
// stopping the mouse pointer when it is present while 
// updating the screen buffer.
// [Solution]  	Corrected the logic to stop the mouse when mouse pointer
//  is present on screen we are updating.
// [Files]  		buffer.c, CommonHelper.c, Mouse.c
// 
// 74    12/28/11 4:12a Arunsb
// [TAG]  		EIP75021 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	[TSE] In Date and Time item Press Shift+Tab key can't move
// previous field.
// [RootCause]  	Shift states not checked properly
// [Solution]  	Shift state bits are cleared for every combinations and
// compared at last
// [Files]  		commonoem.c and commonhelper.c
// 
// 73    12/08/11 9:03p Arunsb
// Wrapper function added for GetFormSetTitleAndHelpWrapper fnc to resolve
// the build error in 2.0
// 
// 72    12/08/11 12:29p Rajashakerg
// Updated the file to overcome build errors when build for x32 mode.
// 
// 71    12/08/11 9:34a Rajashakerg
// [TAG]  		EIP77108
// [Category]  	Improvement
// [Description]  	Updated the file to aviod build errors when build for
// UEFI 20
// 
// 70    12/08/11 12:04a Arunsb
// [TAG]  		EIP75021
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	In Date and Time item Press Shift+Tab key can't move
// previous field
// [RootCause]  	Combination of keys not handled properly
// [Solution]  	Combination of keys handled properly
// [Files]  		commonhelper.c
// 
// 69    12/07/11 9:29a Rajashakerg
// [TAG]  		EIP77108 
// [Category]  	Improvement
// [Description]  	Make ProcessBrowserActionRequest as board module hook
// [Files]  		AMITSE.sdl, CommonHelper.c, HiiCallback.c
// 
// 68    12/01/11 5:34a Rajashakerg
// [TAG]  		EIP74963 
// [Category]  	Improvement
// [Description]  	MAX_MSGBOX_WIDTH cannot be overridden
// [Files]  		AMITSE.sdl, CommonHelper.c, minisetup.h, legacy.c,
// MessageBox.c, MessageBox.h, FormBrowser.c
// 
// 67    11/22/11 1:09a Premkumara
// Updated GetPasswordReportInboxcolor() with missing #endif
// 
// 66    11/22/11 12:08a Premkumara
// [TAG]  		EIP70175
// [Category]  	Improvement
// [Description]  	Color of Password Validation for TSE and  GTSE
// [Files]  		CommonHelper.c, postmgmtext.c
// 
// 65    11/21/11 10:31a Premkumara
// [TAG]  		EIP72610
// [Category]  	Improvement
// [Description]  	Moving TSE_MULTILINE_CONTROLS to Binary
// [Files]  		AMITSE-CommonHelper.c, AMITSE.sdl, 
// TSELITE-UefiAction.c, TseLite.sdl, Time.h, Text.c,
// SubMenu.c, ResetButton.c, PopupString.c, PopupSel.h, PopupSel.c, 
// PopupPassword.c, OrderListBox.c, Numeric.c, Label.c, Frame.c, Edit.c, 
// Date.h, Date.c, 
// LEGACY-Legacy.c,
// BOOTONLY- Minisetup.h
// 
// 64    11/21/11 9:42a Rajashakerg
// [TAG]  		EIP62763 
// [Description]  	For avoiding build errors when softkbd present and
// MINISETUP_MOUSE_SUPPORT is disabled.
// 
// 63    11/21/11 5:44a Rajashakerg
// [TAG]  		EIP74591 
// [Category]  	Improvement
// [Description]  	Make MainSetupLoop as board module hook
// [Files]  		AMITSE.sdl, CommonHelper.c, protocol.c, minisetup.h,
// FormBrowser.c, FormBrowser2.
// 
// 62    11/20/11 8:09a Premkumara
// [TAG]  		EIP70175
// [Category]  	Improvement
// [Description]  	Color of PopupPassword Window to validate password in
// GTSE style
// [Files]  	CommonHelper.c, postmgmtext.c, minisetup.h
// 
// 61    11/20/11 6:48a Rajashakerg
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
// 60    11/19/11 9:22a Premkumara
// [TAG]  		EIP70175
// [Category]  	Improvement
// [Description]  	Color of PopupPassword Window to validate password in
// GTSE style
// [Files]  		CommonHelper.c, postmgmtext.c, minisetup.h
// 
// 59    11/14/11 6:52p Blaines
// [TAG] - EIP 75486 
// [Category]- Function Request
// [Synopsis]- Support grayout condition for readonly controls.
// [Description] - Display readonly controls as grayout, non-selectable.
// [Files]
// AMITSE.sdl, CommonHelper.c, Minisetupext.h, stylecommon.c, Legacy.c,
// date.c, edit.c, label.c, memo.c, menu.c,, numeric.c, ordlistbox.c,
// PopupPassword.c, 
// PopupSel.c, PopupString.c, ResetButton.c, SubMenu.c, Text.c, Time.c,
// UefiAction.c, ctrlcond.c, 
// 
// 58    11/13/11 12:17p Arunsb
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
// 57    11/09/11 9:57a Premkumara
// [TAG]  		EIP74375 
// [Category]  	Improvement
// [Description]  	Control STYLE_HELP_AREA_SCROLLBAR from binary
// [Files]  		CommonHelper.c, AMITSE.sdl, StyleHook.h,
// Legacy\StyleCommon.c, Legacy.sdl, 
// EzportPlus\StyleCommon.c, EzportPlus.sdl, Ezport\StyleCommon.c,
// Ezport.sdl
// 
// 56    11/01/11 4:19a Arunsb
// [Category]  	Improvement
// [Description]  	To change the single click behaviour as like double
// click
// [Files]  		amitse.sdl, commonhelper.c, commonoem.c and listbox.c
// 
// 55    10/20/11 12:23p Blaines
// Correct the comments.
// 
// 54    10/20/11 11:44a Blaines
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
// 53    10/10/11 1:43a Arunsb
// [TAG]  		EIP66976
// [Category]  	Improvement
// [Description]  	Provision to change the Numeric string format
// [Files]  		Amitse.sdl, commonhelper.c and numeric.c
// 
// 52    9/04/11 3:57a Arunsb
// [TAG]  		EIP65320
// [Category]  	Improvement
// [Description]  	Board module hook for LoadImage failure.
// Review comment addressed.
// [Files]  		Commonhelper.c, amitsestr.uni, boot.c and faketokens.c
// 
// 51    7/20/11 3:23p Rajashakerg
// Removed the unwanted function for mouse hot click operation
// 
// 48    7/01/11 4:23a Rajashakerg
// Updated to avoid Build errors when build with binaries alone
// 
// 47    6/30/11 11:52a Arunsb
// EDKVersion_1_05_RetrieveData wrapper function added to return the
// EDK_1_05_RETRIEVE_DATA token value.
// 
// 46    6/30/11 4:00a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Wrapper functions added.
//                 Added board module hook to perform rebooting the
// system.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 45    6/29/11 4:35p Rajashakerg
// Updated for Help frame scroll changes
// 
// 44    6/29/11 2:01p Arunsb
// gHotKeyBootOption declaration added and the same is removed in
// commonoem.c file.
// 
// 43    6/29/11 1:32p Rajashakerg
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
// 42    6/29/11 5:50a Arunsb
// [TAG]           EIP 62631
// [Category]      New Feature
// [Description]   Hot key boot option support in TSE as per UEFI spec.
// section 3.1.6.
//                 CheckAdvShiftState function moved from commonoem.c to
// here.
//                 LaunchHotKeyBootOption function added to launch hot key
// boot device.    
// [Files]         AMITSE.sdl, bootflow.c, bootflow.h, CommonHelper.c,
// commonoem.c, commonoem.h, boot.c,
//                 hiistring20.c, hiistring21.c and notify.c.
// 
// 41    6/23/11 3:39p Rajashakerg
// [TAG]  		EIP55762, 58925, 59971
// [Category]  	New Feature
// [Description]  	Support REF2,REF3 and REF4 in AMITSE
// Support direct form navigation path
// Improper layout of controls in the root page when Dynamic pages are
// added using the Legacy Setup Style	
// [Files]  		setupdata.h, CommonHelper.c, AMITSE.sdl, Legacy\Legacy.c,
// Legacy\style.h, Legacy\style.h, frame.c, minisetupext.c,
// minisetupext.h, numeric.c, page.c Popupstring.c, Hii.c,
// Uefi21Wrapper.c, Parse.c Hii.c
// 
// 40    6/23/11 5:30a Rajashakerg
// [TAG]  		EIP63073  
// [Category]  	New Feature
// [Description]  	Source modules in TSE should get the version details
// from binary in run time not at build time 
// [Files]  		CommonHelper.c, minisetupext.c, notify.c, Ezport\style.c,
// EzportPlus\style.c, Legacy\style.c
// 
// 37    6/20/11 11:41a Rajashakerg
// [TAG]  		EIP59417   
// [Category]  	New Feature
// [Description]  	Spport LOAD_OPTION_HIDDEN option in TSE 
// [Files]  		boot.h, AMITSE.sdl, CommonHelper.c, bbs.c, boot.c,
// minisetup.h, special.c, callback.c 
// 
// 36    6/19/11 4:13p Arunsb
// [TAG]           EIP58712
// [Category]      New Feature
// [Description]   To disable the BIOS Signon Message and TSE copyright
// version in post screen.
// [Files]         amitse.sdl, amitse.mak, commonhelper.c and notify.c
// 
// 35    6/13/11 12:37p Rajashakerg
// [TAG]  		EIP60910 
// [Category]  	New Feature
// [Description]  	PNG image support in TSE.
// [Files]  		 LogoLib.h, AMITSE.sdl, CommonHelper.c, logo.c, png.c,
// png.h, pnguncmp.c, TseAdvanced.cif
// 
// 34    6/04/11 1:54p Arunsb
// [TAG]            EIP58954
// [Category]     New Feature
// [Description] Wrapper function added for InvalidateStatusInBgrt
// function.
// [Files]            Postmgmt.c, boot.c, logo.c commonoem.c and
//                      commonhelper.c
// 
// 33    5/29/11 12:02p Arunsb
// [TAG]           EIP58954
// [Category]      New Feature
// [Description]   Quiet boot logo's only added for BGRT. BGRT status
// field cleared if any changes happened in screen other than displaying
// the image.
// [Files]         Postmgmt.c, boot.c, logo.c commonoem.c and
// commonhelper.c
// 
// 32    5/13/11 12:42p Arunsb
// [TAG]           EIP58954
// [Category]     New Feature
// [Description] Contributing BGRT table to ACPI table. Image blt formed
// with the coordinates drawn onto the screen.
// [Files]            Postmgmt.c, commonoem.c,logo.c and commonhelper.c
// 
// 31    5/04/11 5:03p Arunsb
// [TAG]  		EIP58954
// [Category]  	New Feature
// [Description]  	Contributing BGRT table to ACPI table.
// CONTRIB_BGRT_TABLE_TO_ACPI token added. Wrapper function
// ContribBGRTTableToAcpi added.
// [Files]  		Postmgmt.c, commonoem.c,logo.c and commonhelper.c
// 
// 30    4/29/11 5:03p Arunsb
// For 2.13 public patch release signon message hiding feature is omitted
// 
// 29    4/29/11 4:49p Madhans
// [TAG]  		EIP59177 
// [Category]  	Improvement
// [Description]  	Support for JPEG with RSI markers. Fix to support logo
// size that bigger then Screen resolution.
// [Files]  		Logo.c
// Jpeg6.c
// commonHelper.c
// 
// 28    4/23/11 4:56p Arunsb
// [TAG]  		EIP58712
// [Category]  	New Feature
// [Description]  	To disable the BIOS Signon Message and TSE copyright
// version in post screen.
// [Files]  		amitse.sdl, amitse.mak, commonhelper.c and notify.c
// 
// 27    4/23/11 3:13p Arunsb
// [TAG]  		EIP58954
// [Category]  	New Feature
// [Description]  	Contributing BGRT table to ACPI table.
// CONTRIB_BGRT_TABLE_TO_ACPI token added.
// [Files]  		Postmgmt.c, commonoem.c and commonhelper.c
// 
// 26    4/22/11 5:34p Arunsb
// [TAG]  		EIP58009
// [Category]  	Bug Fix
// [RootCause]  	Certain controls not compatible with UEFI 2.3 version.
// [Solution]  	The UEFI 2.3 features will be added only if core supports
// it.
// [Files]  		Hiicallback.c and commonhelper.c
// 
// 25    4/04/11 10:40a Arunsb
// Small logo cleared properly when it is placed at the top most
// 
// 24    4/04/11 10:31a Arunsb
// Added GetGraphicsBitMapFromFV function.
// 
// 23    3/28/11 11:39p Madhans
// [TAG]  		EIP50878
// [Category]  	Improvement
// [Description]  	Support to move the Control With Boot Order Change.
// [Files]  		AMITSE.sdl
// commonoem.c
// minisetup.h
// popupsel.c
// 
// 22    3/28/11 9:06p Madhans
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
// 21    3/23/11 8:37p Blaines
// [TAG] - EIP 23601
// [Category]- Enhancement
// [Symptom]- Add support for OEM special controls.
// [Files] - AmiTse.sdl, CommonHelper.c, Setup.ini, UefiSetup.ini,
// AmiVfr.h, minisetup.h, minisetup.sdl, variable.c, special.c
// 
// 20    3/15/11 5:12a Rajashakerg
// [TAG]  		EIP51671
// [Category]  	New Feature
// [Description]  	Boot overide menu devices are not disable  
// [Files]  		boot.c, minisetup.h, special.c, minisetupext.c, AMITSE.sdl,
// boot.h, CommonHelper.c
// 
// 19    3/07/11 4:54p Arunsb
// [TAG]  		EIP53106
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Invalid string appears in the boot order for Network
// related devices.
// [RootCause]  	Handle not obtained for network related devices.
// [Solution]  	Disabled option is checked only if
// GROUP_BOOT_OPTIONS_BY_TAG token is enabled.
// [Files]  		bbs.c and commonhelper.c
// 
// 18    2/10/11 12:31p Blaines
// [TAG] - EIP 53146
// [Category]- New Feature
// [Description] -Add the support to Move the Dynamic IFR Pages under
// subpages. It should be customizable to move around.
// 
// 17    12/28/10 6:01p Mallikarjunanv
// [TAG]  		EIP41615
// [Category]  	New Feature
// [Description]  	Added the file browser support for the Add boot option
// reated controls
// [Files]  		AmiVfr.h, AmiTse.sdl, AmiTseStr.uni, CommonHelper.c,
// Faketokens.c, TseElinks.h, EdkHelper.h, minisetup.h, TseAdvanced.c,
// AddBootOption.c
// 
// 16    10/06/10 5:58p Madhans
// [TAG] - EIP 45620 
// [Category]- Enhancment
// [Severity]- Mordarate
// [Symptom]- TSE with TSE_CONTINUE_BOOT_NOW_ON_FAIL ON Not allows to boot
// to USB group of devices with customized BDS.
// [RootCause] - BBSTable does not contain the DeviceType called USB. Only
// in EFI Logical group is created in EFI variables.
// TSE was checking the DeviceType to set the priorities.
// [Solution]- TSE is changed to not check for DeviceType in BBSTable. But
// set the priorities based on LegacyDevOrder.
// [Files] - bbs.c commonhelper.c minisetup.h 
// 
// 15    10/05/10 5:37p Madhans
// [TAG] - EIP 45299 
// [Category]- Enhancment
// [Severity]- Minor
// [Symptom]- TSE by default saves the Disbaled BBS devices device path in
// NVRAM Varaiable "DisabledDevs" Variable. In Next boots it depend on
// this variable to consider the device as disabled inaddtion to
// LegacyDevOrder.
// Some BDS customized projects don't want this.
// [Solution]- TSE_SAVE_DISABLED_BBS_DEVICEPATH SDL token created to
// control this option. Bydefault It is Enabled.
// [Files] - callback.c bbs.c commonhelper.c minisetup.h AMITSE.sdl
// 
// 14    9/20/10 6:46p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 13    9/16/10 8:39p Madhans
// Updated for TSE 2.10. Refer changelog.log for more deatils.
// 
// 35    9/08/10 6:57a Mallikarjunanv
// EIP-42080: TSE updates with respect to Fast Boot Support
// 
// 34    8/27/10 4:54a Mallikarjunanv
// EIP-39334: support to build TSE without the CSM module support
// 
// 33    8/27/10 4:43a Mallikarjunanv
// EIP-39764: Setup password non-case sensitive support and password
// encode support updated
// 
// 32    8/19/10 12:50p Mallikarjunanv
// EIP-42520: Updated to get the BBS group type from the Board module in
// case of a non standard type.
// 
// 31    8/13/10 11:03a Mallikarjunanv
// EIP-39670:  handled the function CheckIsAllowedPasswordChar() with
// override token
// 
// 30    7/28/10 4:47a Mallikarjunanv
// EIP-29951: TSE Device Path Name support updated
// 
// 29    6/08/10 4:59p Blaines
// Add SDL tokens to overrie the following functions:
// 
// TseFramePwdCallbackIdePasswordUpdate
// TsePopupPwdAuthenticateIDEPwd
// TsePopupPwdUpdateIDEPwd
// IDEPasswordGetName
// IDEPasswordAuthenticate
// IDEPasswordUpdate
// IDEPasswordGetDataPtr
// IDEPasswordGetLocked
// IDEPasswordCheck
// IDEPasswordFreezeDevices
// UnlockHDD
// SetHDDPassword
// IDEUpdateConfig
// 
// 28    4/07/10 6:23p Madhans
// Post Screen Scroll Area Support.TSE_POSTSCREEN_SCROLL_AREA Sdl token
// Controls it.
// 
// 27    4/02/10 4:46p Madhans
// To getride of OEM header files from TSE sources..
// 
// 26    3/26/10 6:08p Madhans
// Eip 35562  To create Boot Option variables
// 
// 25    3/23/10 5:03p Blaines
// Preseve the order of disabled BBS boot devices.
// 
// 24    3/19/10 2:39p Madhans
// Support to Load Defaults from NVRAM Defaults.
// 
// 23    2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 22    2/15/10 10:01p Madhans
// Wide Glyph support for uefi 2.1
// 
// 21    2/04/10 11:07p Madhans
// Mouse Support Code optimized
// 
// 20    1/29/10 5:15p Madhans
// To avoid build error of CSM support is off
// 
// 19    1/25/10 1:35a Mallikarjunanv
// eip-24791: changed the function BBSBuildName as a board module hook
// 
// 18    1/09/10 2:32a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 17    1/04/10 9:49a Mallikarjunanv
// Added support for reserved boot option names and added condition not to
// accept empty boot option names
// 
// 16    12/18/09 2:23p Madhans
// To avoid compiler issues.
// 
// 15    10/28/09 5:34p Madhans
// 1. Support to Add the String from other modules to TSE.
// 2. Clean of GIF and Image code Control them with minimal code from TSE
// binary.
// 
// 
// 14    9/24/09 9:42a Sudhirv
// EIP-24971: moved the dependency for TSE_CONTINUE_BOOT_NOW_ON_FAIL to
// Tse Binary
// 
// 13    9/17/09 9:03a Sudhirv
// Remove Load Driver Option from TSE 2.x as it will be handled from Core
// 
// 12    9/16/09 6:14p Madhans
// EIP 25416  : Support have 1/10 sec Timeout
// 
// 11    9/15/09 9:14a Sudhirv
// updated ADD DEL boot opions handling and added empty functions to
// support SETUP_OEM_SPECIAL_CONTROL_SUPPORT
// 
// 10    8/20/09 6:41p Madhans
// Fix for the Mouse Click crash issue.
// 
// 9     8/17/09 9:00a Mallikarjunanv
// Updated with the board module logo and keyhook fucntions to keep the
// empty board module as empty
// 
// 8     8/13/09 12:09p Blaines
// Move Image support to binary module
// 
// 7     8/13/09 7:31a Mallikarjunanv
// eips: 25075, 24971 and hii functions miving from binary to uefi module
// 
// 6     8/03/09 7:54a Mallikarjunanv
// Moved the IDE Security related hook functions from Tse Binary to Tse
// Board Module
// 
// 5     7/20/09 1:05p Mallikarjunanv
// updated the code for PASSWORD_WITH_SPECIAL_CHAR_SUPPORT token
// 
// 4     7/14/09 6:32p Blaines
// For GTSE first Release.,
// 
// 3     6/24/09 6:33p Madhans
// Coding Standards
// 
// 2     6/08/09 5:33p Madhans
// Funtionality to get the Lang/PlatformLang variable name based on SDL
// setting.
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 3     5/07/09 10:31a Madhans
// Changes After Bin module.
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
// Name:		commonhelper.c
//
// Description:	This file is Helper file for Boot only TSE module
// 				This functions may be overridden by Other Advanced TSE module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#pragma warning( disable : 4028 )

#include "TimeStamp.h"
#ifdef TSE_FOR_APTIO_4_50

#include "Token.h"  
#include <Efi.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextOut.h>
#include <Protocol/EfiOemBadging.h>
#include <Protocol/AMIPostMgr.h>
#include "AMITSEStrTokens.h"
#include <Protocol/FirmwareVolume.h>
#include "AmiLib.h"				//Added for using CONVERT_TO_STRING macro
#include "AmiDxeLib.h"
#include "AMITSEElinks.h"
#include "AutoId.h" //EIP-112628
#include "TseElinks.h"			//EIP106950

VOID *
EfiLibAllocateZeroPool (
  IN  UINTN   AllocationSize
  );

#else //#ifdef TSE_FOR_APTIO_4_50

#include "minisetup.h"

#endif //#ifdef TSE_FOR_APTIO_4_50

#include "commonoem.h"
#include "LogoLib.h"
#include "Mem.h"
#include "HiiLib.h"
#include "PwdLib.h"
#include "boot.h"
#include "bootflow.h"
#include "variable.h"
#include "TseCommon.h"
// Build time file generated from AMITSE_OEM_HEADER_LIST elink.
#include "AmiTseOem.h"	
#include "SetupData.h"	
#if SUPPORT_ESRT
#include "amireflashprotocol.h"
#endif




/////////////OEM_SPECIAL_CONTROL////////////////
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
//#include "SetupData.h"

VOID *VarGetVariable( UINT32 variable, UINTN *size );
#define	VARIABLE_ID_OEM_TSE_VAR		17

#endif //SETUP_OEM_SPECIAL_CONTROL_SUPPORT

#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT
UINT16 OEMSpecialGetControlCount(CONTROL_INFO *controlInfo);
VOID OEMSpecialOneOfFixup( CONTROL_INFO *control , UINT16 value );
VOID OEMSpecialGotoFixup(CONTROL_INFO *control, UINT16 value );
#endif //#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT

//#include EFI_PROTOCOL_DEFINITION(LegacyBios)

//EIP:39334 - START
//#if !TSE_APTIO_5_SUPPORT
#if !TSE_CSM_SUPPORT
EFI_GUID gEfiLegacyBiosProtocolGuid = EFI_LEGACY_BIOS_PROTOCOL_GUID;
#endif
//#endif
//EIP:39334 - END

#define VARIABLE_NAME_LENGTH	40
#define _CharIsUpper(c) ((c >= L'A') && (c <= L'Z'))
#define _CharIsLower(c) ((c >= L'a') && (c <= L'z'))
#define _CharIsAlpha(c) (_CharIsUpper(c) || _CharIsLower(c)) 
#define _CharIsNumeric(c) ((c >= L'0') && (c <= L'9'))
#define _CharIsAlphaNumeric(c) (_CharIsAlpha(c) || _CharIsNumeric(c))
#define _CharIsAlphaNumericSpecial(c) ((c >= (CHAR16)0x20) && (c <= (CHAR16)0x7E))
#define Str2No(A)	(A - '0')
#define	TSE_STRUCT_OFFSET(type, field)	(UINTN)&(((type *)0)->field)

//EIP-75236 Starts
#define	NOTIFY_MASK_UGA					(0x00000001)
#define	NOTIFY_MASK_CONSOLE_CONTROL	(0x00000002)
#define	NOTIFY_MASK_CONSOLE_IN			(0x00000004)
#define	NOTIFY_MASK_CONSOLE_OUT			(0x00000008)
#define	NOTIFY_MASK_MOUSE_DRIVER		(0x00000010)

#if SETUP_DELAY_POST_TILL_GOP
	#if SETUP_DELAY_LOGO_TILL_INPUT
		#define	SOMETHING	(NOTIFY_MASK_UGA | NOTIFY_MASK_CONSOLE_CONTROL | NOTIFY_MASK_CONSOLE_IN | NOTIFY_MASK_CONSOLE_OUT /*| NOTIFY_MASK_MOUSE_DRIVER*/)
																															//EIP160126 no need of mouse dependency lets have only if pwd set
	#else
		#define	SOMETHING	(NOTIFY_MASK_UGA | NOTIFY_MASK_CONSOLE_CONTROL | NOTIFY_MASK_CONSOLE_OUT /*| NOTIFY_MASK_MOUSE_DRIVER*/)	
	#endif
#else
	#if SETUP_DELAY_LOGO_TILL_INPUT
		#define	SOMETHING	( NOTIFY_MASK_CONSOLE_CONTROL | NOTIFY_MASK_CONSOLE_IN | NOTIFY_MASK_CONSOLE_OUT /*| NOTIFY_MASK_MOUSE_DRIVER*/)	
	#else
		#define	SOMETHING	( NOTIFY_MASK_CONSOLE_CONTROL | NOTIFY_MASK_CONSOLE_OUT /*| NOTIFY_MASK_MOUSE_DRIVER*/)	
	#endif
#endif
//EIP-75236 Ends

#ifndef SCAN_F12
#define SCAN_F12        EFI_SCAN_F12
#endif

extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE *gST;
extern EFI_RUNTIME_SERVICES *gRT;
extern BOOLEAN gQuietBoot;
VOID *VarGetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size );
VOID GetTseBuildVersion(UINTN *TseMajor, UINTN *TseMinor, UINTN *TseBuild);//EIP 63073 : Source modules in TSE should get the version details from binary in run time not at build time

#if TSE_FOR_64BIT
CHAR16 gBootFileName[]=L"\\EFI\\BOOT\\BOOTX64.EFI";
#else
CHAR16 gBootFileName[]=L"\\EFI\\BOOT\\BOOTIA32.EFI";
#endif //TSE_FOR_64BIT

#if TSE_CAPITAL_BOOT_OPTION
CHAR16 gBootFormarSpecifier[]=L"Boot%04X";
CHAR16 gDriverFormarSpecifier[]=L"Driver%04X";
#else
CHAR16 gBootFormarSpecifier[]=L"Boot%04x";
CHAR16 gDriverFormarSpecifier[]=L"Driver%04x";
#endif

BOOLEAN gPopupMenuShowAllBbsDev = POPUP_MENU_SHOW_ALL_BBS_DEVICES;
BOOLEAN gShowAllBbsDev = SETUP_SHOW_ALL_BBS_DEVICES;
BOOLEAN gIsSaveDisabledBBSDevicePath = TSE_SAVE_DISABLED_BBS_DEVICEPATH;
BOOLEAN gSetupHideDisableBootOptions = SETUP_HIDE_DISABLE_BOOT_OPTIONS;//EIP:51671 Global declerations to access the tokens from Binary
BOOLEAN gPopupMenuHideDisableBootOptions = POPUP_MENU_HIDE_DISABLE_BOOT_OPTIONS;
#ifdef TSE_LOAD_OPTION_HIDDEN
BOOLEAN gLoadOptionHidden = TSE_LOAD_OPTION_HIDDEN;//EIP:59417 -Global declerations to access the tokens from Binary
#else
BOOLEAN gLoadOptionHidden = 0;
#endif

const UINTN TsePasswordLength = SETUP_PASSWORD_LENGTH;




EFI_STATUS GetGifNextFrame( IN OUT VOID **UgaBlt, OUT UINTN	*GifDelay );
extern VOID DrawBltBuffer( EFI_UGA_PIXEL *UgaBlt, CO_ORD_ATTRIBUTE Attribute, UINTN Width,  UINTN Height,
    		INTN DestX, INTN DestY,  UINTN BufferWidth);


extern EFI_STATUS ConvertBmpToUgaBlt (IN VOID *BmpImage, IN UINTN BmpImageSize, IN OUT VOID **UgaBlt,
		IN OUT UINTN  *UgaBltSize, OUT UINTN *PixelHeight, OUT UINTN *PixelWidth );

extern EFI_STATUS ConvertGifToUgaBlt ( IN VOID *GifImage, IN UINTN GifImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINTN *UgaBltSize, OUT UINTN *PixelHeight, OUT UINTN *PixelWidth, OUT UINTN *GifDelay );

extern EFI_STATUS ConvertJPEGToUgaBlt ( IN VOID *JPEGImage, IN UINT32 JPEGImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth, OUT UINT32 *punBufferWidth);

extern EFI_STATUS ConvertPCXToUgaBlt ( IN VOID *PCXImage, IN UINT32 PCXImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth);

extern EFI_STATUS ConvertPNGToUgaBlt ( IN VOID *PCXImage, IN UINT32 PCXImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth);
//Functions
VOID DoAddBootOptionFixup (VOID *ControlInfo);
VOID SpecialFixupDelBootOption( VOID *ControlInfo);
VOID BootAddBootOption();
BOOLEAN DoBootDelBootOption(VOID *popupSel);
void TseUpdateAddDeleteBootVar (void);
VOID DiscardAddDelBootOptions(VOID);
VOID SaveAddDelBootOptions();
UINT16 * TseBootNowinBootOrderInit(VOID);
EFI_STATUS TseVarBuildAMIDefaults(VOID);
VOID TSEMouseInit(VOID);
VOID TSEMouseStop(VOID);
EFI_STATUS TSEGetCoordinates(INT32 *x, INT32 *y, INT32 *z);
BOOLEAN TSEIsMouseClickedonSoftkbd(VOID);
VOID TSEMouseRefresh(VOID);
VOID TSEMouseFreeze(VOID);
VOID TSEMouseStart(VOID);
VOID TSEMouseDestroy(VOID);
INT32 TSEGetactualScreentop(VOID);
VOID TSENumericSoftKbdExit(VOID);
VOID TSENumericSoftKbdInit(VOID);
VOID TSESetPwdKeyboardLayout(VOID);//EIP-88912
VOID TSEResetPwdKeyboardLayout(VOID);//EIP-88912
VOID TSEPrintableKeysSoftKbdInit(VOID);//EIP-89272
VOID TSEPrintableKeysSoftKbdExit(VOID);//EIP-89272
EFI_STATUS TSEMouseReadInfo(VOID *MouseInfo);
EFI_STATUS TSEMouseScrollBarMove(VOID *frame, BOOLEAN bScrollUp, UINT32 Size); //EIP-67049
EFI_STATUS TSEMouseListBoxScrollBarMove(VOID *listbox, BOOLEAN bScrollUp, UINT32 Size); //EIP-67049
EFI_STATUS TSEMouseFrameHandleAction( VOID *frame, VOID *action,VOID *control );
EFI_STATUS TSEMouseSubMenuHandleAction( VOID *submenu, VOID *Data);
EFI_STATUS TSEMouseMsgBoxHandleAction( VOID *msgbox, VOID *Data,BOOLEAN * pRedraw);
EFI_STATUS TSEMousePopupSelHandleAction( VOID *popupSel, VOID *Data);
EFI_STATUS TSEMousePopupEditHandleAction( VOID *PopupEdit, VOID *Data, BOOLEAN * pRedraw );
EFI_STATUS TSEMouseMenuHandleAction( VOID *menu, VOID *Data );
EFI_STATUS TSEMouseListBoxHandleAction( VOID *listbox, VOID *Data);
VOID ClearUserPasswordPolicy(VOID *callbackData,VOID *saveData);
EFI_STATUS TseFramePwdCallbackIdePasswordUpdate ( VOID *control,VOID *saveData);
EFI_STATUS TsePopupPwdAuthenticateIDEPwd(VOID *popuppassword, BOOLEAN *AbortUpdate,VOID *data);
VOID TsePopupPwdUpdateIDEPwd (VOID);
VOID RTIfrProcessExit(VOID);
VOID RTIfrProcessAddVarListAndPageIDList(VOID);
BOOLEAN RTIfrProcessFormIfUpdated(UINT16 link);
VOID RTIfrProcessRunTimeForms(VOID*ref);
LOGO_TYPE GetBmpLogoType(UINT8 *ImageData);
LOGO_TYPE GetGifLogoType(UINT8 *ImageData);
LOGO_TYPE GetJPEGLogoType(UINT8 *ImageData);
LOGO_TYPE GetPCXLogoType(UINT8 *ImageData);
LOGO_TYPE GetOEMLogoType(UINT8 *ImageData);
VOID CleanUpGif(VOID);
VOID DoGifAnimate(CO_ORD_ATTRIBUTE Attribute,INTN CoordinateX,INTN CoordinateY);
UINTN HiiTestPrintLength ( IN CHAR16   *String );
UINTN UefiHiiTestPrintLength ( IN CHAR16   *String );
UINTN EfiTestPrintLength ( IN CHAR16   *String );
VOID BBSSetBootPriorities( BOOT_DATA *pBootData, UINT16 *pOrder, UINTN u16OrderCount);
BOOLEAN IsBBSDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath );
CHAR16 * GetBBSBootOptionName( BOOT_DATA *bootData);
EFI_STATUS BBSSetBootNowPriority( BOOT_DATA *BootData,UINTN uiPrefferedDevice,BOOLEAN ShowAllBbsDev);
VOID BBSGetDeviceList( VOID );
VOID BBSBuildDefaultName( CHAR16 *String, VOID *info, UINTN index, VOID *HDDInfo );
VOID BBSBuildDevicePathName( CHAR16 *String, VOID *info, UINTN index, VOID *HDDInfo );
VOID SaveBBSOrder(VOID*);
VOID BBSSetDisabled(UINT16 Index, VOID **DisDPs, UINTN *DPSize);
VOID RearrangeBBSOrderVariable(VOID *popupSel, UINT8 bIncrease,UINT16 *newOption);
VOID LoadDefaultLegDevOrder(VOID);
VOID BBSUpdateOrder(UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer);
VOID BBSSetBootPriorities_BootOrder(UINT16);
UINTN GetANSIEscapeCode(CHAR16 *String,UINT8 *Bold,UINT8 *Foreground, UINT8 *Background);
CHAR16 *StrDup(CHAR16 *String);
CHAR16 *SkipEscCode(CHAR16 *String);
BOOLEAN CheckShiftState(UINT32 ActionKey, UINT32 HotkeyState);
BOOLEAN SupportPrintScreenEvent();
VOID SupportPrintScreen();
VOID GetBootLanguages( VOID );
VOID GetPlatformBootLanguages( VOID );
VOID RTIfrUpdateVariableInfo( UINT32 ControlVariable, EFI_HANDLE Handle );
void ClearGrphxScreen (void);
VOID ConvertBmpandAddBGRT (
	BOOLEAN GifImagePresence
    );
VOID InvalidateStatusInBgrt (VOID);
UINT32 GetMsgboxWidth(VOID);//EIP74963 : MAX_MSGBOX_WIDTH macro changed as token and handled from binary
INTN  gHotKeyBootOption = -1;
extern UINT32 gBootFlow;
VOID InvalidateStatusInBgrtWrapper (VOID);

//EIP70421 & 70422 Support for driver order starts
VOID SpecialFixupDelDriverOption (VOID *);
BOOLEAN DoDriverDelDriverOption (VOID *);
void TseUpdateAddDeleteDriverVar (VOID );
VOID DiscardAddDelDriverOptions (VOID);
VOID SaveAddDelDriverOptions ();
//EIP70421 & 70422 Support for driver order Ends
VOID UninstallBGRT (VOID);					//EIP81830 Support to uninstall the BGRT on legacy boot
//EIP-75136 ROMHole Support
LOGO_TYPE GetExtendedLogoType(UINT8 *ImageData);
//EIP-75136 End

VOID *SavePostScreen( UINTN *SizeOfX, UINTN *SizeOfY );
VOID RestorePostScreen( VOID *UgaBlt, UINTN SizeOfX, UINTN SizeOfY );

extern BOOT_DATA	*gBootData;						//EIP 88447
extern UINTN		gBootOptionCount;
extern EFI_GUID _gBootFlowGuid;

VOID SetupDebugPrint(IN CONST CHAR8  *Format, ...) ;
#if SUPPRESS_PRINT
    #define SETUP_DEBUG_TSE(format,...)
#else //Else of SUPPRESS_PRINT
    #define SETUP_DEBUG_TSE(format,...) SetupDebugPrint(format, __VA_ARGS__)
#endif

//EIP106950 : Starts
//Controlling from binary
PASSWORD_ENOCDE_LIST_TEMPLATE gPasswordEncodeList [] = {PASSWORD_ENOCDE_LIST {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0, 0}};	//Last structure for avoiding build error.
UINT32 gEncodeListCount = sizeof (gPasswordEncodeList)/ sizeof (PASSWORD_ENOCDE_LIST_TEMPLATE);
//EIP106950 : Ends

//<AMI_PHDR_START>
//--------------------------------------------------------------------------------
// Procedure:	CheckForAddDelBootOption
//
// Description:	Function to return the SETUP_SUPPORT_ADD_BOOT_OPTION token value
//
// Input:		None
//
// Output:		BOOLEAN
//
//--------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckForAddDelBootOption ()
{
#if SETUP_SUPPORT_ADD_BOOT_OPTION
	return 1;
#else
	return 0;
#endif //#if SETUP_SUPPORT_ADD_BOOT_OPTION
}

//EIP70421 & 70422 Support for driver order
//<AMI_PHDR_START>
//--------------------------------------------------------------------------------
// Procedure:	CheckForAddDelDriverOption
//
// Description:	Function to return the SETUP_SUPPORT_ADD_DRIVER_OPTION token value
//
// Input:		None
//
// Output:		BOOLEAN
//
//--------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckForAddDelDriverOption (VOID)
{
#ifdef SETUP_SUPPORT_ADD_DRIVER_OPTION
	return SETUP_SUPPORT_ADD_DRIVER_OPTION;		//Since there is no token dependency for this, returning as such
#else
	return 0;
#endif
}

VOID TseDoAddBootOptionFixup(VOID *ControlInfo )
{
#if SETUP_SUPPORT_ADD_BOOT_OPTION
	DoAddBootOptionFixup(ControlInfo);
#endif //#if SETUP_SUPPORT_ADD_BOOT_OPTION
}


VOID TSESpecialFixupDelBootOption(VOID *ControlInfo)
{
#if SETUP_SUPPORT_ADD_BOOT_OPTION
	SpecialFixupDelBootOption(ControlInfo);
#endif //#if SETUP_SUPPORT_ADD_BOOT_OPTION
}

//EIP70421 & 70422 Support for driver order
VOID TSESpecialFixupDelDriverOption (VOID *ControlInfo)
{
#if SETUP_SUPPORT_ADD_DRIVER_OPTION
	SpecialFixupDelDriverOption (ControlInfo);
#endif
}

VOID TseBootAddBootOption()
{
#if SETUP_SUPPORT_ADD_BOOT_OPTION
	BootAddBootOption();
#endif //#if SETUP_SUPPORT_ADD_BOOT_OPTION
}

//EIP70421 & 70422 Support for driver order
VOID TseDriverAddDriverOption ()
{
#if SETUP_SUPPORT_ADD_DRIVER_OPTION
	DriverAddDriverOption ();
#endif
}

// EIP-41615: Start.
EFI_STATUS FileBrowserLaunchFileSystem (UINT32 Variable);
EFI_STATUS FileBrowserLaunchFilePath (UINT32 Variable);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		TseLaunchFileSystem
//
// Description:		This function to handle launching file system
//
// Input:			UINT32
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TseLaunchFileSystem
EFI_STATUS TseLaunchFileSystem (UINT32 Variable)
{
	EFI_STATUS Status = EFI_SUCCESS;
#if SETUP_SUPPORT_ADD_BOOT_OPTION || SETUP_SUPPORT_ADD_DRIVER_OPTION			//EIP70421 & 70422 Support for driver order
	Status = FileBrowserLaunchFileSystem (Variable);
	if(!EFI_ERROR(Status))
		Status = FileBrowserLaunchFilePath (Variable);
#endif
	return Status;
}
#endif
// EIP-41615: End

BOOLEAN TseDoBootDelBootOption(VOID *popupSel)
{
#if SETUP_SUPPORT_ADD_BOOT_OPTION
	return DoBootDelBootOption(popupSel);
#else
	return 0;
#endif //#if SETUP_SUPPORT_ADD_BOOT_OPTION
}

//EIP70421 & 70422 Support for driver order
BOOLEAN TseDoDriverDelDriverOption (VOID *popupSel)
{
#if SETUP_SUPPORT_ADD_DRIVER_OPTION
	return DoDriverDelDriverOption (popupSel);
#else
	return 0;
#endif
}

void UpdateAddDeleteBootVar(void)
{
#if SETUP_SUPPORT_ADD_BOOT_OPTION
	TseUpdateAddDeleteBootVar();
#endif //#if SETUP_SUPPORT_ADD_BOOT_OPTION
}

//EIP70421 & 70422 Support for driver order
void UpdateAddDeleteDriverVar (void)
{
#if SETUP_SUPPORT_ADD_DRIVER_OPTION
	TseUpdateAddDeleteDriverVar ();
#endif
}

VOID TseDiscardAddDelBootOptions()
{
#if SETUP_SUPPORT_ADD_BOOT_OPTION
	DiscardAddDelBootOptions();
#endif //#if SETUP_SUPPORT_ADD_BOOT_OPTION
}

//EIP70421 & 70422 Support for driver order
VOID TseDiscardAddDelDriverOptions ()
{
#if SETUP_SUPPORT_ADD_DRIVER_OPTION
	DiscardAddDelDriverOptions ();
#endif
}

VOID TseSaveAddDelBootOptions()
{
#if SETUP_SUPPORT_ADD_BOOT_OPTION
	SaveAddDelBootOptions();
#endif //#if SETUP_SUPPORT_ADD_BOOT_OPTION
}

//EIP70421 & 70422 Support for driver order
VOID TseSaveAddDelDriverOptions ()
{
#if SETUP_SUPPORT_ADD_DRIVER_OPTION
	SaveAddDelDriverOptions ();
#endif
}

//EIP# 58925 start
BOOLEAN IsLinkHistorySupport()
{
#if SETUP_LINK_HISTORY_SUPPORT
	return 1;
#else
	return 0;
#endif  
}

//EIP# 58925 End


//EIP# 72333
BOOLEAN IsSubMenuDisplayTitle()
{
#if SETUP_DISPLAY_SUBMENU_PAGETITLE
	return 1;
#else
	return 0;
#endif  
}//EIP# 72333

//EIP 75486 
BOOLEAN IsReadOnlyGrayout()
{
#if SETUP_GRAYOUT_READONLY_CONTROL
	return 1;
#else
	return 0;
#endif  
}//EIP# 75486

BOOLEAN IsGroupDynamicPages()
{
#if SETUP_GROUP_DYNAMIC_PAGES
	return 1;
#else
	return 0;
#endif  
}

BOOLEAN IsOrphanPagesAsRootPage()
{
#if SETUP_ORPHAN_PAGES_AS_ROOT_PAGE
	return 1;
#else
	return 0;
#endif  
}

BOOLEAN IsUpdateBootOrderCursor()
{
#if SETUP_UPDATE_BOOT_ORDER_CURSOR
	return 1;
#else
	return 0;
#endif
}

BOOLEAN IsPreservedDisabledBootOptionOrder()
{
#if TSE_PRESERVE_DISABLED_BBS_DEVICE_ORDER
	return 1;
#else
	return 0;
#endif  
}

BOOLEAN IsReservedBootOptionNamesEnable()
{
#if SETUP_SUPPORT_RES_ADD_DEL_BOOT_OPTION_NAME
	return 1;
#else
	return 0;
#endif  //#if SETUP_SUPPORT_RES_ADD_DEL_BOOT_OPTION_NAME
}

//EIP 103381 - START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsBootTimeOutValueZero
//
// Description:	function to return  TSE_BOOT_TIME_OUT_AS_ZERO value
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsBootTimeOutValueZero()
{
#ifdef TSE_BOOT_TIME_OUT_AS_ZERO
	return TSE_BOOT_TIME_OUT_AS_ZERO;
#else
	return 0;
#endif  //#if TSE_BOOT_TIME_OUT_AS_ZERO
}
//EIP 103381 - END

BOOT_DATA * BootGetBootNowBootData(BOOT_DATA *bootData, UINT16 *BootOrder, UINTN i )
{
#if TSE_BOOT_NOW_IN_BOOT_ORDER
	return BootGetBootData(BootOrder[i]);
#else
	return (bootData + i);
#endif
}


UINT16 * BootNowinBootOrderInit(VOID)
{
#if TSE_BOOT_NOW_IN_BOOT_ORDER
	return TseBootNowinBootOrderInit();
#else
	return NULL;
#endif
}


EFI_STATUS VarBuildAMIDefaults(VOID)
{
#if SETUP_USE_AMI_DEFAULTS
	return TseVarBuildAMIDefaults();
#else
    return EFI_UNSUPPORTED;
#endif // SETUP_USE_AMI_DEFAULTS
}

///
/// Mouse Functions
///

VOID MouseInit(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	TSEMouseInit();	
#endif	
}

BOOLEAN IsMouseSupported(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	return TRUE;
#else
	return FALSE;
#endif	
}

BOOLEAN IsSoftKbdSupported(VOID)
{
#if AMITSE_SOFTKBD_SUPPORT
	return TRUE;
#else
	return FALSE;
#endif	
}


VOID MouseStop(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	TSEMouseStop();	
#endif	
}

VOID GetCoordinates(INT32 *x, INT32 *y, INT32 *z)
{
#if MINISETUP_MOUSE_SUPPORT
	TSEGetCoordinates(x,y,z);	
#endif	
}

VOID MouseRefresh(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	TSEMouseRefresh();	
#endif	
}
BOOLEAN IsMouseClickedonSoftkbd(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	return TSEIsMouseClickedonSoftkbd();	
#endif
return FALSE;	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsMouseOnSoftkbd
//
// Description:    	Function to return whether MousePointer is on softkbd or not
//
// Input:        	None 
//
// Output:        	TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
TSEIsMouseOnSoftkbd(VOID);
BOOLEAN IsMouseOnSoftkbd(VOID)
{
#if (MINISETUP_MOUSE_SUPPORT && AMITSE_SOFTKBD_SUPPORT)
	return TSEIsMouseOnSoftkbd();	
#endif
	return FALSE;	
}

VOID MouseFreeze(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	TSEMouseFreeze();	
#endif	
}

VOID MouseStart(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	TSEMouseStart();	
#endif	
}

VOID NumericSoftKbdInit(VOID)
{
#if (MINISETUP_MOUSE_SUPPORT && AMITSE_SOFTKBD_SUPPORT)
	TSENumericSoftKbdInit();
#endif

}

VOID NumericSoftKbdExit(VOID)
{
#if (MINISETUP_MOUSE_SUPPORT && AMITSE_SOFTKBD_SUPPORT)
	TSENumericSoftKbdExit();
#endif

}
//EIP-88912 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetPwdKeyboardLayout
//
// Description:	function to initialize SetKeyboardLayout
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetPwdKeyboardLayout(VOID)
{
#if (MINISETUP_MOUSE_SUPPORT && AMITSE_SOFTKBD_SUPPORT)
	TSESetPwdKeyboardLayout();
#endif

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ResetPwdKeyboardLayout
//
// Description:	function to exit ResetKeyboardLayout and reset with default keyboard layout
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ResetPwdKeyboardLayout(VOID)
{
#if (MINISETUP_MOUSE_SUPPORT && AMITSE_SOFTKBD_SUPPORT)
	TSEResetPwdKeyboardLayout();
#endif

}
//EIP-88912 Ends

//EIP-89272 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PrintableKeysSoftKbdInit
//
// Description:	function to launch PrintableKeysSoftKbd layout
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PrintableKeysSoftKbdInit(VOID)
{
#if (MINISETUP_MOUSE_SUPPORT && AMITSE_SOFTKBD_SUPPORT)
	TSEPrintableKeysSoftKbdInit();
#endif

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PrintableKeysSoftKbdExit
//
// Description:	function to exit PrintableKeysSoftKbd and reset with default keyboard layout
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PrintableKeysSoftKbdExit(VOID)
{
#if (MINISETUP_MOUSE_SUPPORT && AMITSE_SOFTKBD_SUPPORT)
	TSEPrintableKeysSoftKbdExit();
#endif

}
//EIP-89272 Ends

EFI_STATUS MouseReadInfo(VOID *MouseInfo)
{
#if MINISETUP_MOUSE_SUPPORT
	return TSEMouseReadInfo(MouseInfo);	
#else
    return EFI_UNSUPPORTED;
#endif	
}

VOID MouseDestroy(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	TSEMouseDestroy();	
#endif	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetactualScreentop
//
// Description:	function to get the actual screen top value for mouse
//
// Input:		None
//
// Output:		INT32
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INT32 GetactualScreentop(VOID)
{
#if MINISETUP_MOUSE_SUPPORT
	return TSEGetactualScreentop();//EIP79962 function to return the actual screen top of the setup
#endif	

return 0;
}
EFI_STATUS MouseFrameHandleAction( VOID *frame, VOID *action,VOID *control )
{
#if MINISETUP_MOUSE_SUPPORT
	return TSEMouseFrameHandleAction(frame, action, control);	
#else
    return EFI_UNSUPPORTED;
#endif
}

EFI_STATUS MouseMsgBoxHandleAction( VOID *msgbox, VOID *Data,BOOLEAN * pRedraw)
{
#if MINISETUP_MOUSE_SUPPORT
	return TSEMouseMsgBoxHandleAction(msgbox, Data, pRedraw);	
#else
    return EFI_UNSUPPORTED;
#endif
}

EFI_STATUS MouseMenuHandleAction( VOID *menu, VOID *Data )
{
#if MINISETUP_MOUSE_SUPPORT
	return TSEMouseMenuHandleAction(menu, Data);	
#else
    return EFI_UNSUPPORTED;
#endif	
}


EFI_STATUS MouseListBoxHandleAction( VOID *listbox, VOID *Data)
{
#if MINISETUP_MOUSE_SUPPORT
	return TSEMouseListBoxHandleAction(listbox, Data);	
#else
    return EFI_UNSUPPORTED;
#endif	
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		FramePasswordAdvancedCallback
//
// Description:		This function to handle password callback inside setup
//
// Input:			VOID*, VOID*
//
// Output:			VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_FramePasswordAdvancedCallback 
VOID FramePasswordAdvancedCallback(VOID *callbackData,VOID *saveData)
{
#if TSE_CLEAR_USERPW_WITH_ADMINPW
	ClearUserPasswordPolicy(callbackData,saveData);
#endif //#if TSE_CLEAR_USERPW_WITH_ADMINPW
}
#endif


#if !OVERRIDE_FramePwdCallbackIdePasswordUpdate
EFI_STATUS FramePwdCallbackIdePasswordUpdate ( VOID *control,VOID *saveData)
{
#if SETUP_IDE_SECURITY_SUPPORT
	return TseFramePwdCallbackIdePasswordUpdate ( control,saveData);
#else
    return EFI_UNSUPPORTED;
#endif
}
#endif

#if !OVERRIDE_PopupPwdAuthenticateIDEPwd
EFI_STATUS PopupPwdAuthenticateIDEPwd(VOID *popuppassword, BOOLEAN *AbortUpdate,VOID *data)
{
#if SETUP_IDE_SECURITY_SUPPORT
	return TsePopupPwdAuthenticateIDEPwd(popuppassword, AbortUpdate,data);
#else
    return EFI_UNSUPPORTED;
#endif
}
#endif

#if !OVERRIDE_PopupPwdUpdateIDEPwd
VOID PopupPwdUpdateIDEPwd (VOID)
{
#if SETUP_IDE_SECURITY_SUPPORT
	TsePopupPwdUpdateIDEPwd ();
#endif
}
#endif

LOGO_TYPE GetBmpLogoType(UINT8 *ImageData)
{
#if SETUP_BMP_LOGO_SUPPORT
//	if ( ((BMP_IMAGE_HEADER *)ImageData)->CharB == 'B' && ((BMP_IMAGE_HEADER *)ImageData)->CharM == 'M' ) 
	if ( ImageData[0] == 'B' && ImageData[1] == 'M' ) 
  		return BMP_Logo;
#endif
	return Unsupported_Logo;
}


LOGO_TYPE GetGifLogoType(UINT8 *ImageData)
{
#if SETUP_GIF_LOGO_SUPPORT
	if ( 0 == EfiCompareMem(ImageData, "GIF87a", 6) || 0 == EfiCompareMem(ImageData, "GIF89a", 6) )
		return GIF_Logo;
#endif

	return Unsupported_Logo;
}



LOGO_TYPE GetJPEGLogoType(UINT8 *ImageData)
{

#if SETUP_JPEG_LOGO_SUPPORT
    // Start of Image
    if(0x0D8FF == *((UINT16*)ImageData))
		return JPEG_Logo;
#endif

	return Unsupported_Logo;
}

LOGO_TYPE GetPCXLogoType(UINT8 *ImageData)
{

#if SETUP_PCX_LOGO_SUPPORT
	 if (((*ImageData) == 0x0A) && (*(ImageData+2) == 0x01))
		return PCX_Logo;
#endif

	return Unsupported_Logo;
}

LOGO_TYPE GetPNGLogoType(UINT8 *ImageData)
{

#if SETUP_PNG_LOGO_SUPPORT
	 if ((ImageData[0] == 0x89) && (ImageData[1] == 0x50) && (ImageData[2] == 0x4E ) && (ImageData[3] == 0x47 ) && (ImageData[4] == 0x0D ) && (ImageData[5] == 0x0A ) && (ImageData[6] == 0x1A ) && (ImageData[7] == 0x0A ))
		return PNG_Logo;
#endif

	return Unsupported_Logo;
}

LOGO_TYPE GetOEMLogoType(UINT8 *ImageData)
{

#if SETUP_OEM_FORMAT_LOGO_SUPPORT
	if(IsOEMLogoType(ImageData))
		return OEM_Format_LOGO;
#endif

	return Unsupported_Logo;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertOEMFormatToUgaBltWrapper
//
// Description:	Wrapper function to process ConvertOEMFormatToUgaBlt 
//              functionallity based on SDL token.
//
//
// Input:	OEMImage      - Pointer to GIF file
//					OEMImageSize  	- Number of bytes in BmpImage
//					UgaBlt        	- Buffer containing UGA version of GifImage.
//					UgaBltSize	- Size of UgaBlt in bytes.
//					Height   	- Height of UgaBlt/BmpImage in pixels
//					Width    	- Width of UgaBlt/BmpImage in pixels
//					Animate		-
//
// Output:	EFI_SUCCESS - UgaBlt and UgaBltSize are returned. 
//					EFI_UNSUPPORTED       - GifImage is not a valid *.GIF image
//					EFI_BUFFER_TOO_SMALL  - The passed in UgaBlt buffer is not big enough.
//                          		UgaBltSize will contain the required size.
//					EFI_OUT_OF_RESOURCES  - No enough buffer to allocate
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertOEMFormatToUgaBltWrapper ( IN VOID *OEMImage, IN UINT32 OEMImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *Height, OUT UINT32 *Width, BOOLEAN * Animate)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

#if SETUP_OEM_FORMAT_LOGO_SUPPORT
            Status = ConvertOEMFormatToUgaBlt(
                                ImageData,
            			(UINT32)ImageSize,
            			UgaBlt,
            			(UINT32*)UgaBltSize,
            			(UINT32*)Height,
            			(UINT32*)Width,
				Animate
				);
#endif
	return Status ;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertBmpToUgaBltWrapper
//
// Description:	Wrapper function to process ConvertBmpToUgaBlt 
//              functionallity based on SDL token.
//
// Input:		BmpImage      - Pointer to BMP file
//					BmpImageSize  - Number of bytes in BmpImage
//					UgaBlt        - Buffer containing UGA version of BmpImage.
//					UgaBltSize    - Size of UgaBlt in bytes.
//					PixelHeight   - Height of UgaBlt/BmpImage in pixels
//					PixelWidth    - Width of UgaBlt/BmpImage in pixels
//
// Output:		EFI_SUCCESS           - UgaBlt and UgaBltSize are returned. 
//					EFI_UNSUPPORTED       - BmpImage is not a valid *.BMP image
//					EFI_BUFFER_TOO_SMALL  - The passed in UgaBlt buffer is not big enough.
//                      UgaBltSize will contain the required size.
//					EFI_OUT_OF_RESOURCES  - No enough buffer to allocate
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertBmpToUgaBltWrapper(
  IN  VOID      *BmpImage,
  IN  UINTN     BmpImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *PixelHeight,
  OUT UINTN     *PixelWidth)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

#if SETUP_BMP_LOGO_SUPPORT
	Status = ConvertBmpToUgaBlt(
	        BmpImage,
	        BmpImageSize,
	        UgaBlt,
	        UgaBltSize,
	        PixelHeight,
	        PixelWidth
	        );
#endif
	return Status ;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CleanUpExtendedLogoWrapper
//
// Description:	function to clear the logo
//
// Input:		None
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanUpExtendedLogoWrapper()
{
#if SETUP_GIF_LOGO_SUPPORT
	CleanUpGif();
#endif
#if SETUP_OEM_FORMAT_LOGO_SUPPORT
	CleanUpOEMLogo();
#endif
   ClearGrphxScreen ();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoLogoAnimateWrapper
//
// Description:	function to Handle logo animation
//
// Input:		CO_ORD_ATTRIBUTE Attribute, 
//				INTN CoordinateX,INTN CoordinateY
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DoLogoAnimateWrapper(CO_ORD_ATTRIBUTE Attribute,INTN CoordinateX,INTN CoordinateY)
{

#if SETUP_GIF_LOGO_SUPPORT
	DoGifAnimate(Attribute,CoordinateX,CoordinateY);
#endif

#if SETUP_OEM_FORMAT_LOGO_SUPPORT
	DoOEMLogoAnimate(Attribute,CoordinateX,CoordinateY);
#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertGifToUgaBltWrapper
//
// Description:	Wrapper function to process ConvertGifToUgaBlt 
//              functionallity based on SDL token.
//
//
// Input:	GifImage      - Pointer to GIF file
//					GifImageSize  - Number of bytes in BmpImage
//					UgaBlt        - Buffer containing UGA version of GifImage.
//					UgaBltSize    - Size of UgaBlt in bytes.
//					PixelHeight   - Height of UgaBlt/BmpImage in pixels
//					PixelWidth    - Width of UgaBlt/BmpImage in pixels
//					GifDelay      -
//
// Output:	EFI_SUCCESS - UgaBlt and UgaBltSize are returned. 
//					EFI_UNSUPPORTED       - GifImage is not a valid *.GIF image
//					EFI_BUFFER_TOO_SMALL  - The passed in UgaBlt buffer is not big enough.
//                          UgaBltSize will contain the required size.
//					EFI_OUT_OF_RESOURCES  - No enough buffer to allocate
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ConvertGifToUgaBltWrapper (
  IN  VOID      *GifImage,
  IN  UINTN     GifImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *PixelHeight,
  OUT UINTN     *PixelWidth,
  OUT BOOLEAN 	*Animate
  )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
#if SETUP_GIF_LOGO_SUPPORT 
	UINTN 		GifDelay;	

	GifDelay = 0;
	
	Status = ConvertGifToUgaBlt(
                GifImage,
                GifImageSize,
                UgaBlt,
                UgaBltSize,
                PixelHeight,
                PixelWidth,
                &GifDelay
                );
	//the first frame usually doesn't have valid data so we get the
	//second one and set the timer
	if(!EFI_ERROR(Status) )
	{
	    if(GifDelay)
	    {
			*Animate = TRUE;
	    }
	}

#endif
	return Status ;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertJPEGToUgaBltWrapper
//
// Description:	Wrapper function to process ConvertJPEGToUgaBlt 
//              functionallity based on SDL token.
//
// Input:	IN VOID *JPEGImage - Pointer to the memory that has the 
//										 JPEG Image that need to be decoded.
//					IN UINT32 JPEGImageSize - Size of the JPEG Image
//					IN OUT VOID **UgaBlt - Two cases
//						Case 1: Memory is expected to be allocated by the callee.
//								Address provided as input should be NULL.
//								pointer that will recieve the address of the UGA buffer.
//								The buffer is allocated by callee.
//								This buffer need to be freed by the caller.
//						Case 2: Memory is allocated by the caller
//					IN OUT UINT32 *UgaBltSize - Pointer that stores Size of UgaBlt 
//						in bytes. This will be treated as an input. This should have 
//						value ZERO for Case 2 above.
//					OUT UINT32 *PixelHeight - Height of UgaBlt/JPEG Image in pixels
//					OUT UINT32 *PixelWidth - Width of UgaBlt/JPEG Image in pixels
//					OUT UINT32 *pun32BufferWidth - Width of UgaBlt/JPEG Buffer
//
// Output:	EFI_SUCCESS	- The image was successfully decoded and placed in the buffer
//					EFI_UNSUPPORTED
//					EFI_BUFFER_TOO_SMALL
//					EFI_OUT_OF_RESOURCES
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertJPEGToUgaBltWrapper ( 
	IN VOID *JPEGImage, 
	IN UINT32 JPEGImageSize, 
	IN OUT VOID **UgaBlt, 
	IN OUT UINT32 *UgaBltSize, 
	OUT UINT32 *PixelHeight, 
	OUT UINT32 *PixelWidth, 
	OUT UINT32 *pun32BufferWidth)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

#if SETUP_JPEG_LOGO_SUPPORT
	Status = ConvertJPEGToUgaBlt(
                JPEGImage,
                (UINT32)JPEGImageSize,
                UgaBlt,
                (UINT32*)UgaBltSize,
                (UINT32*)PixelHeight,
                (UINT32*)PixelWidth,
                (UINT32*)pun32BufferWidth
                );
#endif 
	
	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertPCXToUgaBltWrapper
//
// Description:	Wrapper function to process ConvertPCXToUgaBlt 
//              functionallity based on SDL token.
//
// Input:		VOID *PCXImage - Pointer to the memory that has the PCX 
//						Image that need to be decoded.
//					UINT32 PCXImageSize - Size of the PCX Image
//					OUT VOID **UgaBlt - Two cases
//						Case 1: Memory is expected to be allocated by the callee.
//							Address provided as input should be NULL.
//							pointer that will receive the address of the UGA buffer. 
//							The buffer is allocated by callee.	
//							This buffer need to be freed by the caller. 		
//						Case 2: Memory is allocated by the caller
//					OUT UINT32 *UgaBltSize - Pointer that stores Size of UgaBlt in bytes. 
//						This will be treated as an input. This should have value ZERO for Case 2 above.
//					UINT32 *PixelHeight - Height of UgaBlt/PCX Image in pixels
//					UINT32 *PixelWidth - Width of UgaBlt/PCX Image in pixels
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertPCXToUgaBltWrapper ( 
	IN VOID *PCXImage, 
	IN UINT32 PCXImageSize, 
	IN OUT VOID **UgaBlt, 
	IN OUT UINT32 *UgaBltSize, 
	OUT UINT32 *PixelHeight, 
	OUT UINT32 *PixelWidth)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

#if SETUP_PCX_LOGO_SUPPORT
	Status = ConvertPCXToUgaBlt ( 
		PCXImage, 
		PCXImageSize, 
		UgaBlt, 
		UgaBltSize, 
		PixelHeight, 
		PixelWidth);
#endif

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertPNGToUgaBltWrapper
//
// Description:	Wrapper function to process ConvertPNGToUgaBlt 
//              functionallity based on SDL token.
//
// Input:		VOID *PNGImage - Pointer to the memory that has the PNG
//						Image that need to be decoded.
//					UINT32 PNGImageSize - Size of the PNG Image
//					OUT VOID **UgaBlt - Two cases
//						Case 1: Memory is expected to be allocated by the callee.
//							Address provided as input should be NULL.
//							pointer that will receive the address of the UGA buffer. 
//							The buffer is allocated by callee.	
//							This buffer need to be freed by the caller. 		
//						Case 2: Memory is allocated by the caller
//					OUT UINT32 *UgaBltSize - Pointer that stores Size of UgaBlt in bytes. 
//						This will be treated as an input. This should have value ZERO for Case 2 above.
//					UINT32 *PixelHeight - Height of UgaBlt/PNG Image in pixels
//					UINT32 *PixelWidth - Width of UgaBlt/PNG Image in pixels
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertPNGToUgaBltWrapper ( 
	IN VOID *PNGImage, 
	IN UINT32 PNGImageSize, 
	IN OUT VOID **UgaBlt, 
	IN OUT UINT32 *UgaBltSize, 
	OUT UINT32 *PixelHeight, 
	OUT UINT32 *PixelWidth)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

#if SETUP_PNG_LOGO_SUPPORT
	Status = ConvertPNGToUgaBlt ( 
		PNGImage, 
		PNGImageSize, 
		UgaBlt, 
		UgaBltSize, 
		PixelHeight, 
		PixelWidth);
#endif

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrProcessExitWrapper
//
// Description:	Wrapper function to process the RuntimeParsing Exit 
//              functionallity based on SDL token.
//
// Input:		none
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessExitWrapper(VOID)
{
#if SETUP_RUNTIME_IFR_PROCESSING
	RTIfrProcessExit();
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrProcessAddVarListAndPageIDListWrapper
//
// Description:	Wrapper function to add runtime variable and Pages 
//              based on SDL token.
//
// Input:		none
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessAddVarListAndPageIDListWrapper(VOID)
{
#if SETUP_RUNTIME_IFR_PROCESSING
	RTIfrProcessAddVarListAndPageIDList();
#endif
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrProcessFormIfUpdatedWrapper
//
// Description:	Wrapper function to include RTIfrProcessFormIfUpdated
//              based on SDL token.
//
// Input:		Link
//
// Output:		Bool
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN RTIfrProcessFormIfUpdatedWrapper(UINT16 link)
{
#if SETUP_RUNTIME_IFR_PROCESSING
	return RTIfrProcessFormIfUpdated(link);
#else 
	return FALSE;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrUpdateVariableInfoWrapper
//
// Description:	Wrapper function to include RTIfrUpdateVariableInfo
//              based on SDL token.
//
// Input:		ControlVariable, Handle
//
// Output:		Bool
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if UEFI_2_1_SUPPORT
BOOLEAN RTIfrUpdateVariableInfoWrapper(UINT32 ControlVariable, EFI_HANDLE Handle)
{
#if SETUP_RUNTIME_IFR_PROCESSING
	RTIfrUpdateVariableInfo(ControlVariable, Handle);
  return TRUE;
#else 
	return FALSE;
#endif
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrProcessRunTimeFormsWrapper
//
// Description:	Wrapper function to process runtime Ifrs 
//              based on SDL token.
//
// Input:		Link
//
// Output:		Bool
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessRunTimeFormsWrapper(VOID*ref)
{
#if SETUP_RUNTIME_IFR_PROCESSING
	RTIfrProcessRunTimeForms(ref);
#endif
}

EFI_STATUS Uefi20HiiInitializeProtocol( VOID );
EFI_STATUS Uefi21HiiInitializeProtocol(VOID);
EFI_STATUS HiiInitializeProtocol( VOID )
{
#if UEFI_2_1_SUPPORT
	return Uefi21HiiInitializeProtocol();
#else
	return Uefi20HiiInitializeProtocol();
#endif
}

CHAR16 *Uefi20HiiGetStringLanguage( VOID* handle, UINT16 token, CHAR16 *lang );
CHAR16 *Uefi21HiiGetStringLanguage(VOID * handle, UINT16 token, CHAR16 *lang);
CHAR16 *HiiGetStringLanguage( VOID* handle, UINT16 token, CHAR16 *lang )
{
#if UEFI_2_1_SUPPORT
	return Uefi21HiiGetStringLanguage(handle,token,lang);
#else
	return Uefi20HiiGetStringLanguage(handle,token,lang);
#endif
}

UINT16 Uefi20HiiChangeStringLanguage( VOID* handle, UINT16 token, CHAR16 *lang, CHAR16 *string );
UINT16 Uefi21HiiChangeStringLanguage(VOID* handle, UINT16 token, CHAR16 *lang, CHAR16 *string);
UINT16 HiiChangeStringLanguage( VOID* handle, UINT16 token, CHAR16 *lang, CHAR16 *string )
{
#if UEFI_2_1_SUPPORT
	return Uefi21HiiChangeStringLanguage( handle, token, lang, string );
#else
	return Uefi20HiiChangeStringLanguage( handle, token, lang, string);
#endif
}

UINTN Uefi20HiiGetGlyphWidth(VOID);
UINTN Uefi20HiiGetGlyphHeight(VOID);
UINTN Uefi21HiiGetGlyphWidth(VOID);
UINTN Uefi21HiiGetGlyphHeight(VOID);
UINTN HiiGetGlyphWidth(VOID)
{
#if UEFI_2_1_SUPPORT
	return Uefi21HiiGetGlyphWidth();
#else
	return Uefi20HiiGetGlyphWidth();
#endif
}

UINTN HiiGetGlyphHeight(VOID)
{
#if UEFI_2_1_SUPPORT
	return Uefi21HiiGetGlyphHeight();
#else
	return Uefi20HiiGetGlyphHeight();
#endif
}


EFI_STATUS GetUnicodeCollection2Protocol(VOID **Protocol);
EFI_STATUS GetUnicodeCollectionProtocol(VOID **Protocol);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure	:	InitUnicodeCollectionProtocol
//
// Description	:	function to add a string
//
// Input		:	. 
//
// Output		:	status and VOID** UnicodeCollectionProtocol
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitUnicodeCollectionProtocol(VOID **Protocol)
{
#if UEFI_2_1_SUPPORT
	return GetUnicodeCollection2Protocol(Protocol);
#else
	return GetUnicodeCollectionProtocol(Protocol);
#endif 
}

//----------------------------------------------------------------------------
// In Aptio UnicodeCollation2 protocol is supported in the same file as
// UnicodeCollation Protocol depending on EFI_SPECIFICATION_VERSION
//----------------------------------------------------------------------------
#include EFI_PROTOCOL_DEFINITION(UnicodeCollation)
#if UEFI_2_1_SUPPORT 
#ifndef TSE_FOR_APTIO_4_50
#include EFI_PROTOCOL_DEFINITION(UnicodeCollation2)
#endif
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure	:	MetaiMatch
//
// Description	:	Calles MetaiMatch of EFI_UNICODE_COLLATION2_PROTOCOL or EFI_UNICODE_COLLATION_PROTOCOL
//
// Input		:	
//
// Output		:	Boolean
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MetaiMatch(VOID *Protocol,IN CHAR16 *String,IN CHAR16 *Pattern)
{
#if UEFI_2_1_SUPPORT
	return ((EFI_UNICODE_COLLATION2_PROTOCOL*)Protocol)->MetaiMatch((EFI_UNICODE_COLLATION2_PROTOCOL*)Protocol,String,Pattern);
#else
	return ((EFI_UNICODE_COLLATION_PROTOCOL*)Protocol)->MetaiMatch((EFI_UNICODE_COLLATION_PROTOCOL*)Protocol,String,Pattern);
#endif 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure	:	StringColl
//
// Description	:	Calles StriColl of EFI_UNICODE_COLLATION2_PROTOCOL or EFI_UNICODE_COLLATION_PROTOCOL
//
// Input	:	VOID *Protocol,IN CHAR16 *String1,IN CHAR16 *String2
//
// Output	:	INTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
INTN StringColl(VOID *Protocol,IN CHAR16 *String1,IN CHAR16 *String2)
{
#if UEFI_2_1_SUPPORT
	return ((EFI_UNICODE_COLLATION2_PROTOCOL*)Protocol)->StriColl((EFI_UNICODE_COLLATION2_PROTOCOL*)Protocol, String1, String2 );
#else
	return ((EFI_UNICODE_COLLATION_PROTOCOL*)Protocol)->StriColl((EFI_UNICODE_COLLATION_PROTOCOL*)Protocol, String1, String2 );
#endif 
}

UINTN TestPrintLength ( IN CHAR16   *String )
{
#if WIDE_GLYPH_SUPPORT
#if !UEFI_2_1_SUPPORT
	return HiiTestPrintLength ( String );
#else
	return UefiHiiTestPrintLength ( String );			
#endif /* #if !UEFI_2_1_SUPPORT */
#else
	return EfiTestPrintLength ( String );
#endif //WIDE_GLYPH_SUPPORT
}

//#undef TSE_CSM_SUPPORT
//#define TSE_CSM_SUPPORT 0


VOID CsmBBSSetBootPriorities( BOOT_DATA *pBootData, UINT16 *pOrder, UINTN u16OrderCount)
{
#if TSE_CSM_SUPPORT
	BBSSetBootPriorities( pBootData, pOrder, u16OrderCount);
#endif
}

BOOLEAN BBSValidDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath )
{
#if TSE_CSM_SUPPORT
	return IsBBSDevicePath(DevicePath);
#else
	return FALSE;
#endif
}

//----------------------------------------------------------------------------
// Procedure:    CsmBBSBootOptionName
//
// Description: Override function. OEM can override this function to change the 
//				default behaviour of function
//----------------------------------------------------------------------------
#if !OVERRIDE_CsmBBSBootOptionName
CHAR16 * CsmBBSBootOptionName( BOOT_DATA *bootData)
{
#if TSE_CSM_SUPPORT
	return GetBBSBootOptionName( bootData);
#else
	return NULL;
#endif
}
#endif

EFI_STATUS CsmBBSSetBootNowPriority( BOOT_DATA *BootData,UINTN uiPrefferedDevice,BOOLEAN ShowAllBbsDev)
{
#if TSE_CSM_SUPPORT
	return BBSSetBootNowPriority( BootData, uiPrefferedDevice, ShowAllBbsDev);
#else
	return EFI_UNSUPPORTED;
#endif
}


VOID CsmBBSGetDeviceList( VOID )
{
#if TSE_CSM_SUPPORT
	BBSGetDeviceList();
#endif
}
EFI_STATUS BBSLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath );
EFI_STATUS CsmBBSLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevicePath )
{
#if TSE_CSM_SUPPORT
	return BBSLaunchDevicePath( DevicePath);
#else
	return EFI_UNSUPPORTED;
#endif
}


VOID CsmSaveBBSOrder( VOID *nvPtr )
{
#if TSE_CSM_SUPPORT
	SaveBBSOrder(nvPtr);
#endif
}

//EIP109382 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure	:	CsmRearrangeBBSOrder
//
// Description	:	Calls RearrangeBBSOrder function
//
// Input	:	VOID * -> Cache buffer, VOID * -> Default buffer
//
// Output	:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RearrangeBBSOrder (NVRAM_VARIABLE *nvPtr, NVRAM_VARIABLE *DefaultBuffer);
VOID CsmRearrangeBBSOrder (VOID *nvPtr, VOID *DefaultBuffer)
{
#if TSE_CSM_SUPPORT
	RearrangeBBSOrder (nvPtr, DefaultBuffer);
#endif
}
//EIP109382 Ends

VOID CsmBBSSetDisabled(UINT16 Index, VOID **DisDPs, UINTN *DPSize)
{
#if TSE_CSM_SUPPORT
	BBSSetDisabled(Index, DisDPs, DPSize);
#endif
}


VOID CsmRearrangeBBSOrderVariable(VOID *popupSel, UINT8 bIncrease,UINT16 *newOption)
{
#if TSE_CSM_SUPPORT
	RearrangeBBSOrderVariable(popupSel, bIncrease,newOption);
#endif
}

VOID CsmLoadDefaultLegDevOrder(VOID)
{
#if TSE_CSM_SUPPORT
	LoadDefaultLegDevOrder();
#endif
}

EFI_STATUS CsmBBSUpdateOrder(UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer)
{
#if TSE_CSM_SUPPORT
	BBSUpdateOrder(newOption,offset,size, buffer);
	return EFI_SUCCESS;
#else
	return EFI_INVALID_PARAMETER;
#endif
}

// EIP-24971: Start , moving dependency to board module...
VOID TseBBSSetBootPriorities_BootOrder(UINT16 Priority)
{
#if TSE_CONTINUE_BOOT_NOW_ON_FAIL
	BBSSetBootPriorities_BootOrder(Priority);
#endif
}
//EIP-24971: End

VOID GetProgressColor(EFI_UGA_PIXEL * BGColor, EFI_UGA_PIXEL * BDRColor, EFI_UGA_PIXEL * FillColor)
{
	EFI_UGA_PIXEL	backgroundColor = PROGRESSBAR_BACKGROUNDCOLOR;
	EFI_UGA_PIXEL	borderColor = PROGRESSBAR_BORDERCOLOR;
	EFI_UGA_PIXEL	fillColor = PROGRESSBAR_FILLCOLOR;

	MemCopy( BGColor, &backgroundColor, sizeof(EFI_UGA_PIXEL) );
	MemCopy( BDRColor, &borderColor, sizeof(EFI_UGA_PIXEL) );
	MemCopy( FillColor, &fillColor, sizeof(EFI_UGA_PIXEL) );
}

///IDE Password Hooks...
UINTN   gCurrIDESecPage;

#if !OVERRIDE_TSEIDEPasswordGetName
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIDEPasswordGetName
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT  
//
// Input:		UINT16 Index
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 TSEIDEPasswordGetName(UINT16 Index)
{	
#if SETUP_IDE_SECURITY_SUPPORT
	 return IDEPasswordGetName(Index);
#else
	return 0;
#endif
}
#endif

#if !OVERRIDE_TSEIDEPasswordAuthenticate
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIDEPasswordAuthenticate
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		CHAR16 *Password,  VOID*  DataPtr, BOOLEAN bCheckUser
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEIDEPasswordAuthenticate(CHAR16 *Password,  VOID*  DataPtr, BOOLEAN bCheckUser)
{
#if SETUP_IDE_SECURITY_SUPPORT
	 return IDEPasswordAuthenticate(Password, DataPtr, bCheckUser);
#else
	return FALSE;
#endif
}
#endif

#if !OVERRIDE_TSEIDEPasswordUpdate
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIDEPasswordUpdate
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		UINT32 DeviceIndex, CHAR16 *Password, BOOLEAN bCheckUser
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TSEIDEPasswordUpdate( UINT32 DeviceIndex, CHAR16 *Password, BOOLEAN bCheckUser)
{
#if SETUP_IDE_SECURITY_SUPPORT
	 return IDEPasswordUpdate(DeviceIndex, Password, bCheckUser);
#else
	return FALSE;
#endif
}
#endif

#if !OVERRIDE_TSEIDEPasswordGetDataPtr
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIDEPasswordGetDataPtr
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		UINTN Index
//
// Output:		VOID*
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* TSEIDEPasswordGetDataPtr(UINTN Index)
{
#if SETUP_IDE_SECURITY_SUPPORT
	 return IDEPasswordGetDataPtr(Index);
#else
	return NULL;
#endif
}
#endif

#if !OVERRIDE_TSEIDEPasswordGetLocked
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIDEPasswordGetLocked
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		UINTN Index
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TSEIDEPasswordGetLocked(UINTN Index)
{
#if SETUP_IDE_SECURITY_SUPPORT
	 return IDEPasswordGetLocked(Index);
#else
	return FALSE;
#endif
}
#endif

#if !OVERRIDE_TSEIDEPasswordCheck
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIDEPasswordCheck
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEIDEPasswordCheck()
{
	VOID *UgaBlt = NULL;
	UINTN SizeOfX=0, SizeOfY=0;

#if SETUP_IDE_SECURITY_SUPPORT
	 UgaBlt = SavePostScreen(&SizeOfX, &SizeOfY);
	 IDEPasswordCheck();
	 RestorePostScreen( UgaBlt, SizeOfX, SizeOfY);
#endif
}
#endif

#if !OVERRIDE_TSEIDEPasswordFreezeDevices
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIDEPasswordFreezeDevices
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEIDEPasswordFreezeDevices()
{
#if SETUP_IDE_SECURITY_SUPPORT
	 IDEPasswordFreezeDevices();
#endif
}
#endif

#if !OVERRIDE_TSEUnlockHDD
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEUnlockHDD
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEUnlockHDD()
{
#if SETUP_IDE_SECURITY_SUPPORT
	 UnlockHDD();
#endif
}
#endif

#if !OVERRIDE_TSESetHDDPassword
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSESetHDDPassword
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSESetHDDPassword()
{
#if SETUP_IDE_SECURITY_SUPPORT
	 SetHDDPassword();
#endif
}
#endif

#if !OVERRIDE_TSEIDEUpdateConfig
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEIDEUpdateConfig
//
// Description:	Hook function for the IDE Password fuctionality based on
//				the security token SETUP_IDE_SECURITY_SUPPORT 
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TSEIDEUpdateConfig(VOID *ideSecConfig, UINTN value)
{
#if SETUP_IDE_SECURITY_SUPPORT
	 IDEUpdateConfig(ideSecConfig, value);
#endif
}
#endif

UINTN TseGetANSIEscapeCode(CHAR16 *String,UINT8 *Bold,UINT8 *Foreground, UINT8 *Background)
{
#if TSE_ANSI_ESC_CODE_SUPPORT
	return GetANSIEscapeCode(String, Bold, Foreground, Background);
#else
	return 0;
#endif
}

CHAR16 *TseSkipEscCode(CHAR16 *String)
{
#if TSE_ANSI_ESC_CODE_SUPPORT
	return (CHAR16 *)SkipEscCode(String);
#else
	return StrDup(String);
#endif
}

BOOLEAN TseCheckShiftState(AMI_EFI_KEY_DATA ActionKey, UINT32 HotkeyState)
{
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
	return (TSE_CHECK_SHIFTSTATE(ActionKey.KeyState.KeyShiftState, HotkeyState));
#else
	return 1;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		TsePrintScreenSupport
//
// Description:		Function to return print screen support feature
//
// Input:			UINT16 ScanCode
//
// Output:			TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TsePrintScreenEventSupport(UINT16 ScanCode)
{
#if TSE_PRN_SCRN_EVENT_SUPPORT
	if( ScanCode == TSE_PRN_SCRN_KEY_SCAN )
		return 1;
	else 
		return 0;
#else
	return 0;
#endif
}


VOID TseHotkeyPrintScreenSupport()
{
#if TSE_PRN_SCRN_EVENT_SUPPORT
	SupportPrintScreen();
#endif
}

BOOLEAN CheckSystemPasswordPolicy(UINT32 PasswordInstalled)
{
#if SETUP_USER_PASSWORD_POLICY
	return (PasswordInstalled & AMI_PASSWORD_USER)?TRUE:FALSE;
#else
	return (PasswordInstalled & AMI_PASSWORD_ANY)?TRUE:FALSE;
#endif
}



extern VOID EfiStrCpy(IN CHAR16 *Destination, IN CHAR16 *Source);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure	:	GetVariableNameByID
//
// Description	:	function to get Variable Name based on ID
//
// Input		:	UINT32 VariableID
//
// Output		:	CHAR16 *
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetVariableNameByID( UINT32 VariableID )
{
	CHAR16 *varName = (CHAR16 *)EfiLibAllocateZeroPool(VARIABLE_NAME_LENGTH);
	if(varName != NULL)
	{
		switch(VariableID)
		{
			case VARIABLE_ID_LANGUAGE:
#if SETUP_SUPPORT_PLATFORM_LANG_VAR
				EfiStrCpy(varName, L"PlatformLang");
#else
				EfiStrCpy(varName, L"Lang");
#endif
				break;

			default:
				break;
		}
	}	

	return varName;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure	:	GetGUIDNameByID
//
// Description	:	function to get GUID Name based on Variable ID
//
// Input		:	UINT32 VariableID
//
// Output		:	CHAR16 *
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *GetGUIDNameByID( UINT32 VariableID )
{
	CHAR16 *guidName = (CHAR16 *)EfiLibAllocateZeroPool(VARIABLE_NAME_LENGTH);
	if(guidName != NULL)
	{
		switch(VariableID)
		{
			case VARIABLE_ID_LANGUAGE:
#if SETUP_SUPPORT_PLATFORM_LANG_VAR
				EfiStrCpy(guidName, L"PlatformLangCodes");
#else
				EfiStrCpy(guidName, L"LangCodes");
#endif
				break;
			default:
				break;
		}
	}
  return guidName;
}

VOID BootGetLanguages()
{
#if SETUP_SUPPORT_PLATFORM_LANG_VAR
	GetPlatformBootLanguages();
#else
	GetBootLanguages();
#endif
}


///EIP - 24971
BOOLEAN PlatformLangVerSupport()
{
#if SETUP_SUPPORT_PLATFORM_LANG_VAR
	return 1;
#else
	return 0;
#endif
}

BOOLEAN BootNowInBootOrderSupport()
{
#if TSE_BOOT_NOW_IN_BOOT_ORDER
	return 1;
#else
	return 0;
#endif
}

BOOLEAN IsTseLoadPasswordOnDefaults()
{
	return TSE_LOAD_PASSWORD_ON_DEFAULTS;
}

UINT16 GetNoVarStoreBootCountOffset()
{
#if NO_VARSTORE_SUPPORT
	return (UINT16)(TSE_STRUCT_OFFSET(TSE_SETUP_DATA, BootCount));
#else
	return 0;
#endif
}


VOID SetPostScreenScrollArea(UINTN TopRow, UINTN TopCol, UINTN BottomRow, UINTN BottomCol);
VOID ConfigPostScrollArea(VOID)
{
	UINTN X[]= TSE_POSTSCREEN_SCROLL_AREA;
	SetPostScreenScrollArea(X[0],X[1],X[2],X[3]);
}

///EIP - 24971

////////// BOARD MODULE FUNCTIONS /////////////

#if !OVERRIDE_CheckIsAllowedPasswordChar
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckIsAllowedPasswordChar
//
// Description:	Check is the char allowed for password control 
//              based on SDL token.
//
// Input:		Input character
//
// Output:		Bool
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckIsAllowedPasswordChar(CHAR16 Char)
{
#if PASSWORD_WITH_SPECIAL_CHAR_SUPPORT
	return (BOOLEAN)_CharIsAlphaNumericSpecial(Char);
#else
	return (BOOLEAN)_CharIsAlphaNumeric(Char);
#endif
}
#endif

#if !OVERRIDE_PopupPasswordFormCallback
EFI_STATUS PopupPasswordFormCallback(/*CONTROL_INFO*/VOID * pControlData,UINT16 Key,UINT8 Flags)
{
	return EFI_UNSUPPORTED;
}
#endif

#if !OVERRIDE_PopupPwdHandleActionOverRide
EFI_STATUS _PopupPasswordHandleAction( VOID *popuppassword, VOID *Data);
EFI_STATUS 	PopupPwdHandleActionOverRide(VOID *popuppassword, VOID *Data)
{
	return _PopupPasswordHandleAction(popuppassword, Data);
}
#endif

#if !OVERRIDE_PasswordCheckInstalled
UINT32 PasswordCheckInstalledLocal(VOID);
UINT32 PasswordCheckInstalled( VOID )
{
	UINT32	Installed = AMI_PASSWORD_NONE;

	Installed = PasswordCheckInstalledLocal();

	return Installed;
}
#endif

#if !OVERRIDE_PasswordAuthenticate
UINT32 PasswordAuthenticateLocal( CHAR16 *Password );
UINT32 PasswordAuthenticate( CHAR16 *Password )
{
	UINT32 PasswordType = AMI_PASSWORD_NONE;

	PasswordType = PasswordAuthenticateLocal(Password);

	return PasswordType;
}
#endif

#if !OVERRIDE_PasswordUpdate
CHAR16 *PasswordUpdateLocal( CHAR16 *Password, UINTN Size );
CHAR16 *PasswordUpdate( CHAR16 *Password, UINTN Size )
{
	CHAR16 *Buffer = NULL;

	Buffer = PasswordUpdateLocal(Password, Size);

	return Buffer;
}
#endif

#if !OVERRIDE_PasswordCommitChanges
VOID PasswordCommitChanges( BOOLEAN SaveChanges )
{
}
#endif

#if !OVERRIDE_PopupPasswordCheckInstalled
UINT32 PopupPasswordCheckInstalledLocal(VOID *popuppassword);
UINT32 PopupPasswordCheckInstalled(VOID *popuppassword)
{
	return PopupPasswordCheckInstalledLocal(popuppassword);
}
#endif

#if !OVERRIDE_PopupPasswordAuthenticate
BOOLEAN PopupPasswordAuthenticateLocal( VOID *popuppassword, CHAR16 *Password );
BOOLEAN PopupPasswordAuthenticate( VOID *popuppassword, CHAR16 *Password )
{
	return PopupPasswordAuthenticateLocal( popuppassword, Password );
}
#endif

/*
BOOLEAN IsPasswordSupportNonCaseSensitive()
{
#if SETUP_PASSWORD_NON_CASE_SENSITIVE
	return TRUE;
#endif
	return FALSE;
}
*/

#if !OVERRIDE_NoVarStoreSupport
BOOLEAN NoVarStoreSupport(VOID)
{
	return NO_VARSTORE_SUPPORT;
}
#endif

#if !OVERRIDE_NoVarStoreUpdateSystemAccess
VOID NoVarStoreUpdateSystemAccess(UINT8 sysAccessValue)
{
}
#endif

#if !OVERRIDE_ItkSupport
BOOLEAN ItkSupport(VOID)
{
	return SETUP_ITK_COMPATIBILITY;
}
#endif


#if !OVERRIDE_BbsItkBoot
EFI_STATUS BbsItkBoot()
{
	return EFI_UNSUPPORTED;
}
#endif

#if !OVERRIDE_GetAMITSEVariable
VOID GetAMITSEVariableLocal(VOID **mSysConf, UINT8 **setup, UINTN *VarSize);
VOID GetAMITSEVariable(VOID **mSysConf, UINT8 **setup, UINTN *VarSize)
{
	GetAMITSEVariableLocal(mSysConf, setup, VarSize);
}
#endif

#if !OVERRIDE_GetBootTimeOut
UINT16 GetBootTimeOutLocal(UINT16 DefaultValue);
UINT16 GetBootTimeOut(UINT16 DefaultValue)
{
	UINT16 Val;

	Val = GetBootTimeOutLocal(SETUP_DEFAULT_TIMEOUT);

	if(Val == 0xFFFF)
		return Val;
	if(SETUP_TIMEOUT_IN_TENTHOFSEC)
		return Val; //timeout Value Calcualted in 1/0 Sec. Value is already in 1/10 Sec.
	else
	{
		//timeout Value Calcualted in 1/0 Sec. Value is in Sec and Multiply by 10 to make 1/10.
		if((65530/10) > Val) // To avoid overflow
			return Val*10; 
		else
			return 0xFFFE; // return Max timeout possible.
	}

}
#endif

#if !OVERRIDE_VarBuildItkDefaults
VOID VarBuildItkDefaults(VOID)
{
}
#endif

#if !OVERRIDE_SetSystemAccessValueItk
VOID SetSystemAccessValueItk(UINT8 sysAccessValue)
{
}
#endif

#if !OVERRIDE_FindVarFromITKQuestionId
UINT32 FindVarFromITKQuestionId(UINT16 QuestionId)
{
    return 0;
}
#endif

#if !OVERRIDE_IsOEMLogoType
BOOLEAN IsOEMLogoType(UINT8 *ImageData)
{
	// Return TRUE if OEM format.
	return FALSE;
}
#endif

#if !OVERRIDE_ConvertOEMFormatToUgaBlt
EFI_STATUS ConvertOEMFormatToUgaBlt ( IN VOID *OEMImage, IN UINT32 OEMImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *Height, OUT UINT32 *Width, BOOLEAN * Animate)
{
	// Use this override function to convert the oem image to UGABlt.
	return EFI_UNSUPPORTED;
}
#endif

#if !OVERRIDE_CleanUpOEMLogo
VOID CleanUpOEMLogo(VOID)
{
	//Use this override function to free up memory If needed
}
#endif

#if !OVERRIDE_DoOEMLogoAnimate
VOID DoOEMLogoAnimate(CO_ORD_ATTRIBUTE Attribute,INTN CoordinateX,INTN CoordinateY)
{
	//Takecare to init the timer to animate.
}
#endif

#if !OVERRIDE_BBSBuildName
VOID BBSBuildName( CHAR16 *String, VOID *info, UINTN index, VOID *HDDInfo )
{
#if TSE_CSM_SUPPORT
#if TSE_DEVICE_PATH_NAME
	BBSBuildDevicePathName(String, info, index, HDDInfo);
#else
	BBSBuildDefaultName(String, info, index, HDDInfo );
#endif
#endif
}
#endif

VOID StopClickEvent(VOID);
/// EIP74591: START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MainSetupLoopHook
//
// Description:	 Set OVERRIDE_MainSetupLoopHook to 1, if OEM wants to override the MainSetupLoopHook function from Board module.
//
// Input:	VOID
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_MainSetupLoopHook
EFI_STATUS MainSetupLoop( VOID );
EFI_STATUS MainSetupLoopHook( VOID )
{//EIP74591 : Modified MainSetupLoop as board module hook
	StopClickEvent();//EIP 86253 : Mouse and SoftKbd does not work after displaying "No option to boot to" in POST
	return MainSetupLoop();
}
#endif
#if EFI_SPECIFICATION_VERSION>=0x2000A   
//EIP77108 : START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ProcessBrowserActionRequestHook
//
// Description:	 Set OVERRIDE_ProcessBrowserActionRequestHook to 1, if OEM wants to override the ProcessBrowserActionRequestHook function from Board module.
//
// Input:	EFI_BROWSER_ACTION_REQUEST ActionReq
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_ProcessBrowserActionRequestHook
EFI_STATUS ProcessBrowserActionRequest(EFI_BROWSER_ACTION_REQUEST ActionReq);
EFI_STATUS ProcessBrowserActionRequestHook(EFI_BROWSER_ACTION_REQUEST ActionReq)
{//EIP77108 : Modified  ProcessBrowserActionRequest as board module hook
	return ProcessBrowserActionRequest(ActionReq);
}
#endif
#endif
//EIP77108 : END
/// EIP74591: END
/// EIP-42520: START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSGetNonStandardGroupType
//
// Description:	Set OVERRIDE_BBSGetNonStandardGroupType to 1, then add the OEM 
//		specific function to override this function to provide a non standard 
//		group type for the given Device Type.
//
// Input:	BBS Device Type
//
// Output:	String Token
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_BBSGetNonStandardGroupType
UINT16 BBSGetNonStandardGroupType(UINT16 DeviceType)
{
	// By default return the Unknown order
	return STRING_TOKEN(STR_UNKNOWN_ORDER);
}
#endif
/// EIP-42520: END


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseInitHook
//
// Description:	Hook function which is called when Mouse init is done. 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TSEMouseInitHook
VOID TSEMouseInitHook(VOID)
{
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseStopHook
//
// Description:	Hook function which is called when Mouse Stop is done. 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TSEMouseStopHook
VOID TSEMouseStopHook(VOID)
{
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseRefreshHook
//
// Description:	Hook function which is called when Mouse Refresh action is done. 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TSEMouseRefreshHook
VOID TSEMouseRefreshHook(VOID)
{
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseStartHook
//
// Description:	Hook function which is called when Mouse start action is done. 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TSEMouseStartHook
VOID TSEMouseStartHook(VOID)
{
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseDestroyHook
//
// Description:	Hook function which is called when Mouse Destory is done. 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TSEMouseDestoryHook
VOID TSEMouseDestroyHook(VOID)
{
}
#endif


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseIgnoreMouseActionHook
//
// Description:	Hook function which can make TSE to Ignore the mouse action.
//     This function is called whenever TSE read the mouse action 
//     This hook need to be used carefully. It can used in the cases when Mouse 
//     actions consumes by modules like Softkeyboard and not to be used by TSE 
//
// Input:	VOID
//
// Output:	BOOLEAN
//          TRUE - Mouse actions will be ignored by TSE
//          FALSE - Mouse action
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TSEMouseIgnoreMouseActionHook
BOOLEAN TSEMouseIgnoreMouseActionHook(VOID)
{
    return FALSE;    
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEStringReadLoopEntryHook
//
// Description:	Hook function which is called when Strings/Password is going to be read. 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TSEStringReadLoopEntryHook
VOID TSEStringReadLoopEntryHook(VOID)
{
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEStringReadLoopExitHook
//
// Description:	Hook function which is called after Strings/Password read. 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_TSEStringReadLoopExitHook
VOID TSEStringReadLoopExitHook(VOID)
{
}
#endif

EFI_STATUS GetAdvanceDeviceName( CHAR16 *String, VOID *info, UINTN index, VOID *HDDInfo )
{
#if TSE_ADVANCED_BIN_SUPPORT
	BBSBuildDevicePathName(String, info, index, HDDInfo);
	return EFI_SUCCESS;
#endif
	return EFI_UNSUPPORTED;
}

CHAR16 *GetUefiDevPathString(EFI_DEVICE_PATH_PROTOCOL *DevPath);
CHAR16 *TseGetUefiDevPathString(EFI_DEVICE_PATH_PROTOCOL *DevPath)
{
#if TSE_DEVICE_PATH_UEFI_NAME
	return GetUefiDevPathString(DevPath);
#endif
	return NULL;
}

/////////////OEM_SPECIAL_CONTROL////////////////
#if SETUP_OEM_SPECIAL_CONTROL_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OEMSpecialGetControlCount
//
// Description:	OEM Hook Function can allows exploding into multiple controls.
//				Based on the OEM policies it returns number controls need to exploded.
//
//				
// Input:		CONTROL_INFO *controlInfo
//
// Output:		UINT16 Control Count.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_OEMSpecialGetControlCount
UINT16 OEMSpecialGetControlCount(CONTROL_INFO *controlInfo)
{
// SAMPLE CODE: START

// SAMPLE Code : for One of Special control returns 1 and for Other(Submenu) it returns the OemTseVar
/*
	if(controlInfo->ControlType == CONTROL_TYPE_POPUPSEL)
		return 1;
	else
	{
		UINT16 * pValue=NULL,Val;
		UINTN size;

		pValue = VarGetVariable( VARIABLE_ID_OEM_TSE_VAR, &size );
		if(pValue)
		{
			Val = *pValue;
			MemFreePointer((VOID **) &pValue);
			return  Val;
		}
		else
			return 1;
	}
*/
// SAMPLE CODE: END

	//Add the OEM code like above for customization
	
	return 1;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OEMSpecialOneOfFixup
//
// Description:	If the OEM Special control is One of Control the members of the one of control
//				Can be fixed up in this function. If OEM needs multiple control,
//				for each one of it will be called.
//				This function has to create dynamic IFR Oneof Options
//
// Input:		CONTROL_INFO *control - ControlInfo that need to be patched.
//				UINT16 value - Index of the control that need to be pathched.
//
// Output:		NONE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_OEMSpecialOneOfFixup
VOID OEMSpecialOneOfFixup( CONTROL_INFO *control , UINT16 value )
{
// SAMPLE CODE: START

// Sample Code: To create the One of options based in the OemTSEVar count.
/*
	EFI_IFR_ONE_OF *ifrPtr;
	EFI_IFR_ONE_OF_OPTION *templatePtr, *oneOf;

	VOID *tempPtr;
	UINTN i, size;
	CHAR16 Number[]=L"0";
	UINT16 * pValue=NULL,Val=0;

	pValue = VarGetVariable( VARIABLE_ID_OEM_TSE_VAR, &size );
	if(pValue)
	{
		Val = *pValue;
		MemFreePointer((VOID **) &pValue);
	}

    //Create one one_of_option for each OEM option 
	size = sizeof(EFI_IFR_ONE_OF) + sizeof(EFI_IFR_END_ONE_OF) + (Val) * sizeof(EFI_IFR_ONE_OF_OPTION);
	tempPtr = EfiLibAllocateZeroPool( size );
	if ( tempPtr == NULL )
		return;

	ifrPtr = (VOID *)control->ControlPtr;
	MemCopy( tempPtr, ifrPtr, ifrPtr->Header.Length );
	control->ControlPtr = (UINTN)tempPtr;

	templatePtr = (EFI_IFR_ONE_OF_OPTION *)((UINTN)ifrPtr + ifrPtr->Header.Length);
	oneOf = (EFI_IFR_ONE_OF_OPTION *)((UINTN)tempPtr + ifrPtr->Header.Length);
	for ( i = 0; i < Val; i++, oneOf++ )
	{
		MemCopy( oneOf, templatePtr, sizeof(EFI_IFR_ONE_OF_OPTION) );
		oneOf->Value = (UINT16)i+1;
		Number[0]=L'0'+(UINT16)i+1;
		oneOf->Option = HiiAddString( control->ControlHandle, Number );
	}

	oneOf->Header.OpCode = EFI_IFR_END_ONE_OF_OP;
	oneOf->Header.Length = sizeof(EFI_IFR_END_ONE_OF);

	ifrPtr = (EFI_IFR_ONE_OF *)control->ControlPtr;
	control->ControlHelp = ifrPtr->Help;
*/
// SAMPLE CODE: END

	//Add the OEM code like above for customization

	return;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OEMSpecialUpdateOneOf
//
// Description:	Hook to update the OEM Variable based on Selection.
//				TSE updates the varible buffer in the normal way (updates with option value selected)
//				If any OEM Special updatation required OEM may use this function and return EFI_SUCCESS.
//				
//
// Input:		newOption - Option value selected.
//				offset 	- Variable offset
//				Size 	- size of the variable
//				buffer - OutBuffer Allocate and fill this if OEM Updated the buffer. (Return Success)
//
// Output:		EFI_SUCCESS - If OEM Updates the Buffer with OEM policy
//				EFI_ERROR (EFI_INVALID_PARAMETER) - Standard TSE Update is enough. No Updates done for OEM
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_OEMSpecialUpdateOneOf
EFI_STATUS OEMSpecialUpdateOneOf(UINT16 newOption,UINT32 *offset,UINTN *size, VOID OUT **buffer)
{

	return EFI_INVALID_PARAMETER;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OEMSpecialGotoFixup
//
// Description:	If the OEM Special control is Submenu Control. Based on the OEMSpecialGetControlCount
//				The submenus are added with same promt/help. If OEM want to Fix the prompt and help fields
//				of the submenu control. It can be done here.
//				For  each submenu of that OEM special control it is called.
//
// Input:		CONTROL_DATA *ctrlData - Control data.
//				UINT16 value - Index of the control that need to be pathched.
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_OEMSpecialGotoFixup
VOID OEMSpecialGotoFixup(CONTROL_INFO *control, UINT16 value )
{
// SAMPLE CODE: START
	// Sample Code: To Fix the OEM One of controls prompt based on Value.
/*
UINTN
SPrint (
  OUT CHAR16        *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR16  *Format,
  ...
  );

	CHAR16 str[100];
	SPrint(str,200,L"OEM Goto Control %d",value);
	((EFI_IFR_REF *)control->ControlPtr)->Prompt = HiiAddString( control->ControlHandle,str);
*/
// SAMPLE CODE: END

	//Add the OEM code like above for customization

	return;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OEMSpecialGotoSelect
//
// Description:	Hook for OEM Goto control Action Handler.
//				On Selection of the OEM Goto control it is called.
//
// Input:		UINT16 value - Index of the control that is selected
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_OEMSpecialGotoSelect
VOID OEMSpecialGotoSelect(UINT16 value)
{
// SAMPLE CODE: START
/*
	// Sample Code: To display the message box on what is selected.

	CHAR16 str[100];
	UINT8 ShowPostMsgBox(IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8   MsgBoxType);

	SPrint(str,200,L"OEM Goto Control %d Selected",value);
	ShowPostMsgBox(L"OEM Goto Select",str,MSGBOX_TYPE_OK);
*/
// SAMPLE CODE: END

	//Add the OEM code like above for customization

	return;
}
#endif

#endif // SETUP_OEM_SPECIAL_CONTROL_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OemCheckControlCondition
//
// Description:	 Set OVERRIDE_OemCheckControlCondition to 1, if OEM wants to override the OemCheckControlCondition function from Board module.
//
// Input:	UINT8 FinalCond, CONTROL_INFO *controlInfo
//
// Output:	UINT8
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_OEMCheckControlCondition
UINT8 OEMCheckControlCondition(UINT8 FinalCond, CONTROL_INFO *controlInfo)
{
	return FinalCond;
}
#endif

#if !OVERRIDE_FastBootLaunch
EFI_STATUS FastBootLaunch()
{
    return EFI_UNSUPPORTED;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetMessageboxColorHook
//
// Description:	Hook function to set Messagebox Color. 
//
// Input:	UINT8 **Color
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_GetMessageboxColorHook
VOID GetMessageboxColorHook(UINT8 **Color)
{
//	**Color = EFI_BACKGROUND_LIGHTGRAY | EFI_BLUE;	
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GOPScreenResolution
//
// Description:	Hook function to set GOPScreen Resolution. 
//
// Input:	VOID
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_GOPSetScreenResolutionHook
EFI_STATUS GOPSetScreenResolutionHook(UINTN *Width, UINTN *Height, UINT32 Index)
{
	return EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LaunchHotKeyBootOption
//
// Description:	Board module hook for LaunchHotKeyBootOption function
//
// Input:		BOOT_FLOW *
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_LaunchHotKeyBootOption
EFI_STATUS LaunchHotKeyBootOption (BOOT_FLOW *Bflow)
{
    if (-1 != gHotKeyBootOption)
    {
        return (BootLaunchBootOption ((UINT16)gHotKeyBootOption, NULL, 0) );
    }
    return EFI_NOT_FOUND;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DriverHealthSystemReset
//
// Description:	Board module hook for DriverHealthSystemReset function
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_DriverHealthSystemReset
VOID DriverHealthSystemReset (VOID)
{
    CHAR16 *Text = NULL;
    Text = HiiGetString (gHiiHandle, STRING_TOKEN (STR_DRV_HLTH_REBOOT_POST));
    PostManagerDisplayPostMessage (Text);
    gBS->Stall (2000000);
    gRT->ResetSystem (EfiResetWarm, EFI_SUCCESS, 0, NULL);
}
#endif

void SetDesiredTextMode();
//EIP 89377 : START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	LegacyBootFailHook
//
// Description:	Board module hook for LegacyBootFailHook function
//				This function invoked when LoadImage fails
//
// Input:		EFI_STATUS => Status returned from CsmBBSLaunchDevicePath
//
// Output:		VOID 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void CheckandDeactivateSoftkbd();
#if !OVERRIDE_LegacyBootFailHook
VOID LegacyBootFailHook (EFI_STATUS Status)
{
	UINT8 	Sel;
	UINT16 	OptionToken = STR_CTRL_OK;
    CHAR16	*Title = NULL;
    CHAR16	*Message = NULL;
	AMI_POST_MGR_KEY Key;

	if(EFI_SECURITY_VIOLATION == Status)
	{
		MouseInit();
		CheckandDeactivateSoftkbd (); //EIP-140123 disabling any softkbd activated while showing msgbox
		
		SetDesiredTextMode();			//EIP94702
	   Title = HiiGetString (gHiiHandle, STRING_TOKEN (STR_SECBOOT_VIOLATION));
		Message = HiiGetString (gHiiHandle, STRING_TOKEN (STR_SECBOOT_INV_SIGN));
		ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );
		PostManagerDisplayMsgBoxEx (
			Title,
			Message,
			NULL,
			MSGBOX_EX_CATAGORY_ERROR,
			MSGBOX_TYPE_CUSTOM,
			&OptionToken,
			1,
			NULL,
			0,
			&Sel,
			&Key
			);
		MouseDestroy(); //EIP-140123
	} 
}
#endif
////EIP 89377 : END

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiBootFailHook
//
// Description:	Board module hook for UefiBootFailHook function
//				This function invoked when LoadImage fails
//
// Input:		EFI_STATUS => Status returned from LoadImage
//
// Output:		VOID 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_UefiBootFailHook
VOID UefiBootFailHook (EFI_STATUS Status)
{
	UINT8 	Sel;
	UINT16 	OptionToken = STR_CTRL_OK;
    CHAR16	*Title = NULL;
    CHAR16	*Message = NULL;
	AMI_POST_MGR_KEY Key;

	if ((EFI_SECURITY_VIOLATION == Status) || (EFI_ACCESS_DENIED == Status))
	{
		MouseInit();
		CheckandDeactivateSoftkbd (); //EIP-140123 disabling any softkbd activated while showing msgbox

		SetDesiredTextMode();			//EIP94702
		Title = HiiGetString (gHiiHandle, STRING_TOKEN (STR_SECBOOT_VIOLATION));
		Message = HiiGetString (gHiiHandle, STRING_TOKEN (STR_SECBOOT_INV_SIGN));
		ClearScreen( EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY );//EIP-79959 Clear screen before display Violatioin MessageBox to avoid screen corruption
		PostManagerDisplayMsgBoxEx (
			Title,
			Message,
			NULL,
			MSGBOX_EX_CATAGORY_ERROR,
			MSGBOX_TYPE_CUSTOM,
			&OptionToken,
			1,
			NULL,
			0,
			&Sel,
			&Key
			);
		InvalidateStatusInBgrtWrapper ();					//Since mode changed invalidating status field in BGRT table. EIP93524
		MouseDestroy(); //EIP-140123
	} 
}
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------------------
// Procedure:	UpdateNumericDisplayString
//
// Description:	Board module hook for UpdateNumericDisplayString function
//				This function invoked before displaying the numeric control
//				Can use this function to change the display style of numeric control
//
// Input:		CHAR16 ** => Numeric string to be formatted
//				INT64 => Numeric data to be formatted
//				UINT8 => Base of the numeric control, might be AMI_BASE_HEX, AMI_BASE_INT_DEC, AMI_BASE_DEC
//				UINT16 => Width of the numeric control
//				UINT16 => Size of the CHAR16 **Text
//
// Output:		VOID 
//
//----------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_UpdateNumericDisplayString
VOID UpdateNumericDisplayString (CHAR16 **Text, INT64 Num, UINT8 Base, UINT16 ControlDataWidth, UINT16 SizeofText)
{
#if 0			//Replace 0 with 1
	#define AMI_BASE_HEX 16
//Example for showing the numeric hex variables in uppercase and with leading zeroes
	if (AMI_BASE_HEX == Base)
	{
		SPrint (*Text, SizeofText, L"%0*X", (ControlDataWidth * 2), Num);
	}
#endif
}
#endif

//EIP 88895 Starts
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	GetUEFISpecVersion
//
// Description:	Returns the Specification version assigned to TSE_CALLBACK_SPEC_VERSION
//
// Input:	VOID
//
// Output:	UINT32 => Callback Version
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_GetUefiSpecVersion
UINT32 GetUefiSpecVersion (VOID)
{
    return TSE_CALLBACK_SPEC_VERSION;
}
#endif
//EIP 88895 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FBBootFlow
//
// Description:	
//
// Input:		BOOT_FLOW *
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS	FBBootFlow ( BOOT_FLOW * Bflow)
{
	gBootFlow = BOOT_FLOW_CONDITION_FAST_BOOT;
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsBootOptionsGroupingEnabled
//
// Description:	Returns the value for grouping the boot options
//
// Input:		void
//
// Output:		UINT8 - Value for grouping boot options
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8   IsBootOptionsGroupingEnabled (void)
{
#ifdef GROUP_BOOT_OPTIONS_BY_TAG
    return ((UINT8)GROUP_BOOT_OPTIONS_BY_TAG);
#else              
    return 1;        //In older version grouping is defaultly enabled
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsSetupHideBiosSignOnMsg
//
// Description:	Returns the value for hiding the bios signon msg
//
// Input:		void
//
// Output:		UINT8 - Value for hiding bios signon msg
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8   IsSetupHideBiosSignOnMsg (void)
{
#ifdef SETUP_HIDE_BIOS_SIGNON_MESSAGE2
    return ((UINT8)SETUP_HIDE_BIOS_SIGNON_MESSAGE2);
#else              
    return 0;        //In older version no chance for hiding sign on msg
#endif
}
//EIP-75136 ROMHole support Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsOEMPOSTLogoSupport
//
// Description:	To Return OEMLogo Draw Support token value
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsOEMPOSTLogoSupport()
{
#ifdef TSE_OEM_POSTLOGO_SUPPORT
	return TSE_OEM_POSTLOGO_SUPPORT;
#else
	return 0;
#endif
}
//EIP-75136 ROMHole support End

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	GetGraphicsBitMapFromFV.
//				This is Override function. OEM can override the default behaviour
//
// Description:	Return the graphics image file named FileNameGuid into Image
//					and return it's size in ImageSize. All Firmware Volumes (FV)
//					in the system are searched for the file name.
//
// Input:	FileNameGuid  - File Name of graphics file in the FV(s).
//					Image         - Pointer to pointer to return graphics image.
//										If NULL, a buffer will be allocated.
//					ImageSize     - Size of the graphics Image in bytes. Zero if no image found.
//
// Output:	EFI_SUCCESS          - Image and ImageSize are valid.
//					EFI_BUFFER_TOO_SMALL - Image not big enough. ImageSize has required size
//					EFI_NOT_FOUND        - FileNameGuid not found
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_GetGraphicsBitMapFromFV
EFI_STATUS
GetGraphicsBitMapFromFV ( IN EFI_GUID *FileNameGuid, OUT VOID **Image, OUT UINTN *ImageSize )
{
	EFI_STATUS                    Status;
	UINTN                         FvProtocolCount;
	EFI_HANDLE                    *FvHandles;
	UINTN                         Index;
	UINT32                        AuthenticationStatus;

#if (TSE_ROMHOLE_SUPPORT)	//EIP-75136 Start
	EFI_FV_FILE_ATTRIBUTES		Attrib 			= (EFI_FV_FILE_ATTRIBUTES)NULL;
	EFI_FIRMWARE_VOLUME_HEADER  *FvVolume 		= (EFI_FIRMWARE_VOLUME_HEADER  *)NULL;
	EFI_HANDLE					processFvHandle	= NULL;	
	DXE_SERVICES *DXE_Service = NULL;
	EFI_TPL CurrentTpl = 0;
	EFI_GUID DxeServicesTableGuid = DXE_SERVICES_TABLE_GUID;
	EFI_GUID AMIROMHOLEGuid = TSE_ROMHOLE_HEADER_GUID;
#endif //EIP-75136 End

#if (PI_SPECIFICATION_VERSION < 0x00010000)
	EFI_FIRMWARE_VOLUME_PROTOCOL  *Fv;
#else
    EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
#endif

	Status = gBS->LocateHandleBuffer (
                  ByProtocol,
#if (PI_SPECIFICATION_VERSION < 0x00010000)
                  &gEfiFirmwareVolumeProtocolGuid,
#else
                  &gEfiFirmwareVolume2ProtocolGuid,
#endif
                  NULL,
                  &FvProtocolCount,
                  &FvHandles
                  );
	if (EFI_ERROR (Status)) 
		return EFI_NOT_FOUND;

	for (Index = 0; Index < FvProtocolCount; Index++)
	{
		Status = gBS->HandleProtocol (
                   FvHandles[Index],
#if (PI_SPECIFICATION_VERSION < 0x00010000)
                   &gEfiFirmwareVolumeProtocolGuid,
#else
                   &gEfiFirmwareVolume2ProtocolGuid,
#endif
                   (VOID **) &Fv
                   );

		// Assuming Image and ImageSize are correct on input.
		Status = Fv->ReadSection (
		          Fv,
                  FileNameGuid,
                  EFI_SECTION_RAW,
                  0,
                  Image,
                  ImageSize,
                  &AuthenticationStatus
                  );

		if (!EFI_ERROR (Status))
		{
		//81617 : Avoiding memory leaks in TSE
			gBS->FreePool(FvHandles);
			return EFI_SUCCESS;
		}
		else if (Status == EFI_BUFFER_TOO_SMALL) // ImageSize updated to needed size so return
		{
		//81617 : Avoiding memory leaks in TSE
			gBS->FreePool(FvHandles);
            return EFI_BUFFER_TOO_SMALL;
		}
	}
//EIP-75136 Start
#if (TSE_ROMHOLE_SUPPORT)

	for (Index = 0; Index < FvProtocolCount; Index++)
	{
		Status = gBS->HandleProtocol (
                   FvHandles[Index],
#if (PI_SPECIFICATION_VERSION < 0x00010000)
                   &gEfiFirmwareVolumeProtocolGuid,
#else
                   &gEfiFirmwareVolume2ProtocolGuid,
#endif
                   (VOID **) &Fv
                   );
		if (EFI_ERROR (Status)) {
			continue;
		}

		// Get FV buffer and FV_ImageSize from RomHole FV
		Status = Fv->ReadFile (
		          Fv,
                  &AMIROMHOLEGuid,
                  Image,
                  ImageSize,
				  (VOID *)EFI_SECTION_RAW,
				  &Attrib,
                  &AuthenticationStatus
                  );

		if (!EFI_ERROR (Status))//If it found before end of iteration then break the loop
		{
			if (*ImageSize)
				*ImageSize = 0;
			break;
		}

	}

	MemFreePointer ((VOID **)&FvHandles);
	if (EFI_ERROR (Status)){		
		return EFI_NOT_FOUND;
	}

	DXE_Service = (DXE_SERVICES *)GetEfiConfigurationTable(gST,&DxeServicesTableGuid);	
	FvVolume = (EFI_FIRMWARE_VOLUME_HEADER  *)*Image;

	//Raise TPL level to Install FV protocol for ROMHole
	CurrentTpl = gBS->RaiseTPL( TPL_HIGH_LEVEL );
	gBS->RestoreTPL( TPL_APPLICATION);

	//Install new FV protocol for ROMHole
	Status = DXE_Service->ProcessFirmwareVolume (FvVolume, FvVolume->HeaderLength, &processFvHandle);

	//Free Image data after ProcessFirmwareVolume
	MemFreePointer((VOID **)Image);
		
	if (EFI_ERROR(Status)){
		return Status;
	}

	gBS->RaiseTPL( TPL_HIGH_LEVEL );
	gBS->RestoreTPL( CurrentTpl );	

	Status = gBS->LocateHandleBuffer (
                  ByProtocol,
#if (PI_SPECIFICATION_VERSION < 0x00010000)
                  &gEfiFirmwareVolumeProtocolGuid,
#else
                  &gEfiFirmwareVolume2ProtocolGuid,
#endif
                  NULL,
                  &FvProtocolCount,
                  &FvHandles
                  );

	if (EFI_ERROR (Status)){		
		return EFI_NOT_FOUND;
	}

	for (Index = 0; Index < FvProtocolCount; Index++)
	{
		Status = gBS->HandleProtocol (
                   FvHandles[Index],
#if (PI_SPECIFICATION_VERSION < 0x00010000)
                   &gEfiFirmwareVolumeProtocolGuid,
#else
                   &gEfiFirmwareVolume2ProtocolGuid,
#endif
                   (VOID **) &Fv
                   );
				   
		if (EFI_ERROR (Status)) {
			continue;
		}			   

		// Assuming Image and ImageSize are correct on input.
		Status = Fv->ReadSection (
		          Fv,
                  FileNameGuid,
                  EFI_SECTION_RAW,
                  0,
                  Image,
                  ImageSize,
                  &AuthenticationStatus
                  );

		if (!EFI_ERROR (Status))
		{
			MemFreePointer ((VOID **)&FvHandles);
			return EFI_SUCCESS;
		}
		else if (EFI_BUFFER_TOO_SMALL == Status) // ImageSize updated to needed size so return
		{
			MemFreePointer ((VOID **)&FvHandles);
            return EFI_BUFFER_TOO_SMALL;
		}
	}
#endif
//EIP-75136 End

	//81617 : Avoiding memory leaks in TSE
	gBS->FreePool(FvHandles);
	return EFI_NOT_FOUND;
}
#endif
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	GetACPIOEMID
//
// Description:	Returns the ACPI OEM ID
//
// Input:	VOID
//
// Output:	UINT8 * => OEM ID String
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 *GetACPIOEMID (VOID)
{
#ifdef T_ACPI_OEM_ID
    return CONVERT_TO_STRING (T_ACPI_OEM_ID);
#else
    return 0;
#endif
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	GetACPIOEMTableID
//
// Description:	Returns the ACPI OEM Table ID
//
// Input:	VOID
//
// Output:	UINT8 * => OEM Table ID String
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 *GetACPIOEMTableID (VOID)
{
#ifdef T_ACPI_OEM_TBL_ID
    return CONVERT_TO_STRING (T_ACPI_OEM_TBL_ID);
#else
    return 0;
#endif
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	GetACPIOEMRevision
//
// Description:	Returns the ACPI OEM Revision
//
// Input:	VOID
//
// Output:  UINT32 => ACPI OEM Revision	
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetACPIOEMRevision (VOID)
{
#ifdef ACPI_OEM_REV
    return ACPI_OEM_REV;
#else
    return 0;
#endif
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	ContribBGRTTableToAcpi
//
// Description:	Wrapper function to call ConvertBmpandAddBGRT
//
// Input:	    BOOLEAN
//
// Output:      VOID 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ContribBGRTTableToAcpi (
	BOOLEAN	GifImagePresence
    )
{
#if CONTRIB_BGRT_TABLE_TO_ACPI
    ConvertBmpandAddBGRT (GifImagePresence);
#endif
}


//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	InvalidateStatusInBgrtWrapper
//
// Description:	Wrapper function to call InvalidateStatusInBgrt
//
// Input:	    BOOLEAN
//
// Output:      VOID 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InvalidateStatusInBgrtWrapper (
    )
{
#if CONTRIB_BGRT_TABLE_TO_ACPI
    InvalidateStatusInBgrt ();
#endif
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	LoadDefaultsFromDefaultBuffer
//
// Description:	Wrapper function to provide TSE_LOAD_DEFAULTS_FROM_DEFAULTS_BUFFER
//
// Input:	    BOOLEAN
//
// Output:      VOID 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
//EIP 105167 : START
BOOLEAN LoadDefaultsFromDefaultBuffer( VOID )
{

#ifdef TSE_LOAD_DEFAULTS_FROM_DEFAULTS_BUFFER
	return TSE_LOAD_DEFAULTS_FROM_DEFAULTS_BUFFER;
#else 
	return FALSE;
#endif

}
//EIP 105167 : END

//EIP81830 starts - Support to uninstall the BGRT on legacy boot starts
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	UninstallBgrtWrapper
//
// Description:	Wrapper function to call UninstallBgrtWrapper
//
// Input:	    BOOLEAN
//
// Output:      VOID 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UninstallBgrtWrapper (
    )
{
#if CONTRIB_BGRT_TABLE_TO_ACPI
    UninstallBGRT ();
#endif
}
//EIP81830 ends

//EIP 63073 START
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	GetTseBuildVersion
//
// Description:	Function to fill the TSE build information
//
// Input:	    UINTN *TseMajor, UINTN *TseMinor, UINTN *TseBuild
//
// Output:      VOID 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetTseBuildVersion(UINTN *TseMajor, UINTN *TseMinor, UINTN *TseBuild)
{
	*TseMajor = TSE_MAJOR;
	*TseMinor = TSE_MINOR;
	*TseBuild = TSE_BUILD;
}
//EIP 63073 END

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	GetTseBuildYear
//
// Description:	Function to fill the TSE build Year
//
// Input:	    UINT16 *TseBuildYear
//
//
// Output:      VOID 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetTseBuildYear(UINT16 *TseBuildYear)
{
	CHAR8 BuildYear[5]=FOUR_DIGIT_YEAR;
	*TseBuildYear=(Str2No(BuildYear[0])*0x1000+Str2No(BuildYear[1])*0x100+Str2No(BuildYear[2])*0x10+Str2No(BuildYear[3]));
}
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
//<AMI_PHDR_START>
//----------------------------------------------------------------------------------------
// Procedure:	CheckAdvShiftState
//				This is override function. OEM can override default behaviour of this function
//
// Description:	Checks the input shift state with the condition shift state
//
// Input:		UINT32 = Key shift state obtained from console input devices
//              UINT32 = Shift state condition to match with input key shift state
//
// Output:		BOOLEAN = TRUE => When input and condition shift states matches
//                        FALSE => When input and condition shift states not matches  
//
//-----------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_CheckAdvShiftState
BOOLEAN CheckAdvShiftState (UINT32 AmiKeyShiftState, UINT32 CondShiftState)
{
	BOOLEAN 	Result = TRUE;

	AmiKeyShiftState =  AmiKeyShiftState & (~SHIFT_STATE_VALID);
	CondShiftState = CondShiftState & (~SHIFT_STATE_VALID);

	if (AmiKeyShiftState == CondShiftState)		
	{
		goto DONE;
	}
	else
	{
		Result = FALSE;
		//If condition shift state has both the shift key set then checking for any one pressed
		if ((CondShiftState & RIGHT_LEFT_SHIFT_PRESSED) == RIGHT_LEFT_SHIFT_PRESSED)
		{	
			if (!(AmiKeyShiftState & RIGHT_LEFT_SHIFT_PRESSED))
			{
				goto DONE;
			}
			AmiKeyShiftState &= ~RIGHT_LEFT_SHIFT_PRESSED;			//Clearing the left right bits
			CondShiftState &= ~RIGHT_LEFT_SHIFT_PRESSED;
		}
		//If condition shift state has both the Ctrl key set then checking for any one pressed
		if ((CondShiftState & RIGHT_LEFT_CONTROL_PRESSED) == RIGHT_LEFT_CONTROL_PRESSED)
		{
			if (!(AmiKeyShiftState & RIGHT_LEFT_CONTROL_PRESSED))
			{
				goto DONE;
			}
			AmiKeyShiftState &= ~RIGHT_LEFT_CONTROL_PRESSED;
			CondShiftState &= ~RIGHT_LEFT_CONTROL_PRESSED;
		}
		//If condition shift state has both the Alt key set then checking for any one pressed
		if ((CondShiftState & RIGHT_LEFT_ALT_PRESSED) == RIGHT_LEFT_ALT_PRESSED)
		{
			if (!(AmiKeyShiftState & RIGHT_LEFT_ALT_PRESSED))
			{
				goto DONE;
			}
			AmiKeyShiftState &= ~RIGHT_LEFT_ALT_PRESSED;
			CondShiftState &= ~RIGHT_LEFT_ALT_PRESSED;
		}
		//If condition shift state has both the logo key set then checking for any one pressed
		if ((CondShiftState & RIGHT_LEFT_LOGO_PRESSED) == RIGHT_LEFT_LOGO_PRESSED)
		{
			if (!(AmiKeyShiftState & RIGHT_LEFT_LOGO_PRESSED))
			{
				goto DONE;
			}
			AmiKeyShiftState &= ~RIGHT_LEFT_LOGO_PRESSED;
			CondShiftState &= ~RIGHT_LEFT_LOGO_PRESSED;
		}
		if (CondShiftState == AmiKeyShiftState)
		{
			Result = TRUE;
		}					
	}
DONE:
	return Result;
}
#endif
#endif

//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	IsDriverHealthSupported
//
// Description:	Retrurns DRIVER_HEALTH_SUPPORT token value
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN  IsDriverHealthSupported (VOID)
{
#ifdef DRIVER_HEALTH_SUPPORT
    return DRIVER_HEALTH_SUPPORT;
#else
    return 0;					//Defaultly disabled.
#endif
}

//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	AdvancedRepairSupported
//
// Description:	Returns the SHOW_DRV_HEALTH_BOOT_TIME_SENDFORM token value
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN AdvancedRepairSupported (VOID)
{
#ifdef HONOR_DRVHLTH_CONFIGREQD_ON_BOOTFAIL
	return HONOR_DRVHLTH_CONFIGREQD_ON_BOOTFAIL;
#else
	return 0;
#endif
}

//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	EDKVersion_1_05_RetrieveData
//
// Description:	Returns the EDK_1_05_RETRIEVE_DATA token value
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN EDKVersion_1_05_RetrieveData (VOID)
{
#ifdef EDK_1_05_RETRIEVE_DATA
	return EDK_1_05_RETRIEVE_DATA;
#else
	return 1;
#endif
}

//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	SingleClickActivation
//
// Description:	Returns the SINGLE_CLICK_ACTIVATION token value
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SingleClickActivation (VOID)
{
	return SINGLE_CLICK_ACTIVATION;
}
//EIP-74375 
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsHelpAreaScrollBarSupport
//
// Description:	Returns value as enable or disable STYLE_HELP_AREA_SCROLLBAR support
//
// Input:		void
//
// Output:		UINT8 - Value for grouping boot options
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   IsHelpAreaScrollBarSupport (void)
{
#if STYLE_HELP_AREA_SCROLLBAR
    return STYLE_HELP_AREA_SCROLLBAR;
#else
    return 0;
#endif
}
//<--End EIP-74375 Control STYLE_HELP_AREA_SCROLLBAR from binary

//Start_EIP-70175 Set Password Popup Window and PopupTextBox color
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPasswordPopupTextBoxColor
//
// Description:	Function to Get PasswordPopupTextBox Color
//
// Input:		VOID
//
// Output:		
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetPasswordPopupTextBoxColor(VOID)
{
#if TSE_STYLE_GTSE_BIN_SUPPORT
	return (EFI_BACKGROUND_BLACK | EFI_WHITE);//For GTSE
#else
	return (EFI_BACKGROUND_LIGHTGRAY | EFI_BLUE);//For TSE
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPasswordPopupWindowColor
//
// Description:	Function to Get PasswordPopupWindow Color
//
// Input:		VOID
//
// Output:		
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetPasswordPopupWindowColor(VOID)
{
#if TSE_STYLE_GTSE_BIN_SUPPORT
	return (EFI_BACKGROUND_LIGHTGRAY | EFI_WHITE);//For GTSE
#else
	return (EFI_BACKGROUND_BLUE | EFI_WHITE);//For TSE
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPasswordReportInboxcolor
//
// Description:	Function to Get PasswordReportInBox Color
//
// Input:		VOID
//
// Output:		
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetPasswordReportInboxcolor(VOID)
{
#if TSE_STYLE_GTSE_BIN_SUPPORT 
	return (EFI_BACKGROUND_LIGHTGRAY | EFI_WHITE);//EIP 81623 : For GTSE IDE security password dialog label name displayed in text field 
#else
	return (EFI_BACKGROUND_BLUE | EFI_WHITE);//For TSE
#endif	
}
//End_EIP-70175
//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	IsTSEMultilineControlSupported
//
// Description:	Retrurns TSE_MULTILINE_CONTROLS token value
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN  IsTSEMultilineControlSupported (VOID)
{
#ifdef TSE_MULTILINE_CONTROLS
    return TSE_MULTILINE_CONTROLS;
#endif
    return FALSE;					//Defaultly disabled.
}
//EIP74963 : MAX_MSGBOX_WIDTH macro changed as token and handled from binary
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	GetMsgboxWidth
//
// Description:	Returns the message box width 
//
// Input:	VOID
//
// Output:  UINT32 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetMsgboxWidth(VOID)
{
	return MAX_MSGBOX_WIDTH;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetFormSetTitleAndHelp
//
// Description: GetFormSetTitleAndHelp
//
// Parameter:   EFI_HII_HANDLE Handle, EFI_STRING_ID *Title, EFI_STRING_ID *Help
//
// Return value: status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetFormSetTitleAndHelp (EFI_HII_HANDLE Handle, UINT16 *Title, UINT16 *Help);
EFI_STATUS GetFormSetTitleAndHelpWrapper (VOID *Handle, UINT16 *Title, UINT16 *Help)
{
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
	return GetFormSetTitleAndHelp (Handle, Title, Help);
#else
	return EFI_UNSUPPORTED;
#endif	
}
//EIP-88527 Starts
//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	IsBGRTSupported
//
// Description:	Retrurns CONTRIB_BGRT_TABLE_TO_ACPI token value
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN  IsBGRTSupported (VOID)
{
#ifdef CONTRIB_BGRT_TABLE_TO_ACPI
    return CONTRIB_BGRT_TABLE_TO_ACPI;	//Default is ENABLE
#endif
    return FALSE;					
}
//EIP-88527 Ends

//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	ClearNumericShiftState
//
// Description:	
//
// Input:	    VOID*
//
// Output:      
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearNumericShiftState (AMI_EFI_KEY_DATA *Data)
{
#if TSE_USE_AMI_EFI_KEYCODE_PROTOCOL
	 Data->KeyState.KeyShiftState = 0;	 
#endif 
}

//EIP 88447 Starts
//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	FindDevPathTotLength
//
// Description: Find the length of the complete device path	
//
// Input:	    EFI_DEVICE_PATH_PROTOCOL *
//
// Output:      UINTN	
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN FindDevPathTotLength (EFI_DEVICE_PATH_PROTOCOL *DevPath)
{
	EFI_DEVICE_PATH_PROTOCOL *TempDevPath = DevPath;
	UINTN TotalLength = sizeof (EFI_DEVICE_PATH_PROTOCOL);

	while (!isEndNode (TempDevPath))
	{
		TotalLength += NODE_LENGTH (TempDevPath);
		TempDevPath = NEXT_NODE (TempDevPath);
	}
	return TotalLength;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------
// Procedure:		BootDevPathMatchEnabled
//
// Description:	Checks whether the input device path matches exactly with any of the boot options
//						device path. This will be useful for USB, Floppy....
//
// Input:	    	EFI_DEVICE_PATH_PROTOCOL *
//
// Output:      	BOOLEAN - TRUE - Device path matched and the corresponding boot option is enabled
//									 FALSE - Device path matched and the corresponding boot option is disbled
//
//------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BootDevPathMatchEnabled (EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
	UINTN iIndex = 0;
//	UINTN CmpLength = 0; Not used
	EFI_DEVICE_PATH_PROTOCOL *TempDevPath = DevicePath;
	
	while (!isEndNode (TempDevPath))
	{
		if ((MEDIA_DEVICE_PATH == TempDevPath->Type) && (MEDIA_FILEPATH_DP == TempDevPath->SubType))
		{
			for (iIndex = 0; iIndex < gBootOptionCount; iIndex ++)
			{
				if (((UINTN)TempDevPath - (UINTN)DevicePath) <= FindDevPathTotLength (gBootData [iIndex].DevicePath))
				{
					if (!MemCmp (DevicePath, gBootData [iIndex].DevicePath, (UINTN)TempDevPath - (UINTN)DevicePath))
					{
						if (!gBootData [iIndex].Active)
						{
							return FALSE;
						}
					}
				}
			}
			break;
		}
		TempDevPath = NEXT_NODE (TempDevPath);
	}
	return TRUE;					//If nothing matched then boot from that device path
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------
// Procedure:		MediaDevPathMatchEnabled
//
// Description:	Checks whether the input device path matches with any of the boot options
//						media device path. This will be useful for drives with partition.
//
// Input:	    	EFI_DEVICE_PATH_PROTOCOL *
//
// Output:      	BOOLEAN - TRUE - Device path matched and the corresponding boot option is enabled
//									 FALSE - Device path matched and the corresponding boot option is disbled
//
//------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN MediaDevPathMatchEnabled (EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
	UINTN 	iIndex = 0;
	UINTN 	CmpLength = 0;
	EFI_DEVICE_PATH_PROTOCOL *TempDevPath = DevicePath;

	while (!isEndNode (TempDevPath))
	{
		if ((MEDIA_DEVICE_PATH == TempDevPath->Type) && (MEDIA_HARDDRIVE_DP == TempDevPath->SubType))
		{
			CmpLength = NODE_LENGTH (TempDevPath);
			break;
		}
		TempDevPath = NEXT_NODE (TempDevPath);
	}
	if (CmpLength)
	{	
		for (iIndex = 0; iIndex < gBootOptionCount; iIndex ++)
		{
			if (CmpLength <= FindDevPathTotLength (gBootData [iIndex].DevicePath))
			{
				if (!MemCmp (TempDevPath, gBootData [iIndex].DevicePath, CmpLength))
				{
					if (!gBootData [iIndex].Active)
					{
						return FALSE;
					}
				}
			}
		}		
	}	
	return TRUE;			//If nothing matched then boot from that device path
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------
// Procedure:		LaunchSecBootPathFromEnabledDevs
//					This is override function. OEM can override default behaviour of this function
//
// Description:	Launches default image from the path \EFI\BOOT\BOOT{machine type short-name}.EFI
//						from the enabled devices in setup.
//
// Input:	    	CHAR16 *
//
// Output:      	EFI_STATUS - EFI_SUCCESS -> If default image loaded successfully
//									 	!EFI_SUCCESS -> If default image not loaded successfully
//
//------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_DEVICE_PATH_PROTOCOL *_BootBuildFileDevicePath( UINT32 *, CHAR16 *);
EFI_STATUS _BootLaunchDevicePath( EFI_DEVICE_PATH_PROTOCOL *, VOID *, UINTN, BOOLEAN);
#if !OVERRIDE_LaunchSecBootPathFromEnabledDevs
EFI_STATUS LaunchSecBootPathFromEnabledDevs (CHAR16 *FileName)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT32     index = 0;
	
	EFI_DEVICE_PATH_PROTOCOL *devicePath;
	do
	{
		devicePath = _BootBuildFileDevicePath (&index, FileName);
		if (index != (UINT32)-1)
		{
			if ((BootDevPathMatchEnabled (devicePath)) && (MediaDevPathMatchEnabled (devicePath)))
			{
				Status = _BootLaunchDevicePath (devicePath, NULL, 0,FALSE);
			}
		}
		MemFreePointer ((VOID **)&devicePath);
	} while ((EFI_ERROR (Status)) && (index != (UINT32)-1));
	return Status;
}
#endif

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------
// Procedure:		LaunchSecondaryPath
//
// Description:	Launches default image from the path \EFI\BOOT\BOOT{machine type short-name}.EFI
//
// Input:	    	CHAR16 *
//
// Output:      	EFI_STATUS - EFI_SUCCESS -> If default image loaded successfully
//									 	!EFI_SUCCESS -> If default image not loaded successfully
//
//------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_LaunchSecondaryBootPath
EFI_STATUS LaunchSecondaryBootPath (CHAR16 *FileName)
{
#if SECONDARY_BOOT_FROM_ENABLED_DEVICES
	return LaunchSecBootPathFromEnabledDevs (FileName);		//If user need to boot the default image from only enabled devices
#else																			//Default case
	return BootLaunchFilename (FileName);	            		//EIP 57660 loads the default image from any of the file system
#endif
}
#endif
//EIP 88447 Ends

//EIP-75236 Starts
//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	IsDelayLogoTillInputSupported
//
// Description:	Retrurns SETUP_DELAY_LOGO_TILL_INPUT token value
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN  IsDelayLogoTillInputSupported (VOID)
{
#ifdef SETUP_DELAY_LOGO_TILL_INPUT
	return SETUP_DELAY_LOGO_TILL_INPUT;
#else
	return 0;
#endif
}

//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	GetNotifyMaskValue
//
// Description:	Retrurns notify mask vaule
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32  GetNotifyMaskValue (VOID)
{
//#if AMITSE_SOFTKBD_SUPPORT
	return SOMETHING;
/*#else
	return (SOMETHING & (~NOTIFY_MASK_MOUSE_DRIVER));
#endif*/
}
//EIP-75236 Ends

//EIP-67049 Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   MouseScrollBarMove
//
// Description: Function to move scrollbar in Frame using mouse
//
// Parameter:   VOID *, BOOLEAN, UINT32
//
// Return value: status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MouseScrollBarMove(VOID *frame, BOOLEAN bScrollUp, UINT32 Size)
{
#if MINISETUP_MOUSE_SUPPORT
	 return TSEMouseScrollBarMove( frame, bScrollUp, Size );	
#else
    return EFI_UNSUPPORTED;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   MouseListBoxScrollBarMove
//
// Description: Function to move scrollbar in ListBox using mouse
//
// Parameter:   VOID *, BOOLEAN, UINT32
//
// Return value: status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MouseListBoxScrollBarMove(VOID *listbox, BOOLEAN bScrollUp, UINT32 Size)
{
#if MINISETUP_MOUSE_SUPPORT
	 return TSEMouseListBoxScrollBarMove( listbox, bScrollUp, Size );	
#else
    return EFI_UNSUPPORTED;
#endif	
}
//EIP-67049 End

//EIP-94616 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TseIgnoreKeyForFastBoot
//
// Description: Function to return FastBoot is ENABLED or DISABLED
//
// Parameter:   VOID
//
// Return value: BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN TseIgnoreKeyForFastBoot()
{
#if TSE_IGNORE_KEY_FOR_FASTBOOT
	UINT32 *currentBootFlow;
	UINTN size = 0;

	currentBootFlow = VarGetNvramName( L"BootFlow", &_gBootFlowGuid, NULL, &size );	
	if (currentBootFlow != NULL  && *currentBootFlow == BOOT_FLOW_CONDITION_FAST_BOOT)
	{
		MemFreePointer( (VOID **)&currentBootFlow );
		return TRUE;
	}	
	else
	{
		if (currentBootFlow)
		{
			MemFreePointer ((VOID **)&currentBootFlow );
		}
		return FALSE;
	}
#else
 	return FALSE;
#endif	
}
//EIP-94616 Ends

//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	IsTSECursorSupport
//
// Description:	Function to return TSE_CURSOR_SUPPORT token value
//
// Input:	    VOID
//
// Output:      BOOLEAN
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN  IsTSECursorSupport (VOID)
{
#ifdef TSE_CURSOR_SUPPORT
	return TSE_CURSOR_SUPPORT;
#else
	return 0;
#endif
}


//EIP93521 Starts
//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------
// Procedure:		OsUpdateCapsuleWrap
//
// Description:	Dispalys the image obtained form OS Update and calls the capsule to update
//
// Input:	    	BOOT_FLOW *
//
// Output:      	EFI_STATUS - EFI_SUCCESS -> Capsule update is success
//									 	!EFI_SUCCESS -> Fault happenend in capsule update
//
//------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_OsUpdateCapsuleWrap
TSE_POST_STATUS	PostManagerGetPostStatus(VOID);
LOGO_TYPE GetLogoType(UINT8 *ImageData);
EFI_STATUS OsUpdateCapsuleWrap (BOOT_FLOW *bootFlowPtr)
{
	EFI_STATUS  Status = EFI_SUCCESS;
#if SUPPORT_ESRT
	EFI_GUID    ReflashGuid = EFI_REFLASH_PROTOCOL_GUID;
	UINT8 		*ImageData = NULL;
	UINTN 		ImageSize       = 0;
	UINTN 		CoordinateX     = 0;
	UINTN 		CoordinateY     = 0;
	UINTN 		Width           = 0;
	UINTN       Height          = 0;
	UINTN			LogoType        = 0;
	UINTN			UgaBltSize      = 0;
	UINTN			unBufferWidth   = 0;
	EFI_BADGING_DISPLAY_ATTRIBUTE Attribute;
	EFI_UGA_PIXEL	            	*UgaBlt = NULL;
	EFI_REFLASH_PROTOCOL        	*ReFlash = NULL;

   SETUP_DEBUG_TSE ("\nEntering OsUpdateCapsuleWrap");
	Status = gBS->LocateProtocol (&ReflashGuid, NULL, &ReFlash);
	if (!EFI_ERROR (Status))
	{
		Status = ReFlash->GetDisplayImage (ReFlash, &CoordinateX,  &CoordinateY, &ImageData);		//Recovery module have to allocate and send the image data
		SETUP_DEBUG_TSE ("\nGetDisplayImage status is %x", Status);
		if (!EFI_ERROR (Status))																						//TSE wont free the ImageData
		{																														//Recovery module have to provide the X,Y coordinates too
      	Attribute = EfiBadgingDisplayAttributeCustomized;	//and wont free the memory
      	Height = 0;
      	Width = 0;
      	LogoType = GetLogoType (ImageData);
        
      	if (BMP_Logo ==  LogoType)			//Draw only for BMP image
			{
				Status = ConvertBmpToUgaBltWrapper(
					ImageData,
					ImageSize,
					&UgaBlt,
					&UgaBltSize,
					&Height,
					&Width );
				SETUP_DEBUG_TSE ("\nStatus for blt wrap is %x", Status);
				unBufferWidth = Width;
				SETUP_DEBUG_TSE ("\nCoordinateX  is %x CoordinateY is %x", CoordinateX, CoordinateY);
				SETUP_DEBUG_TSE ("\nDrawing the string");
				DrawBltBuffer (UgaBlt, Attribute, Width, Height, CoordinateX, CoordinateY, unBufferWidth);
			}
			SETUP_DEBUG_TSE ("\nCalling CapUpdProgress");
			Status = ReFlash->CapUpdProgress (ReFlash);
      }
	}
#endif
   SETUP_DEBUG_TSE ("\nExiting OsUpdateCapsuleWrap");
	return Status;
}
#endif
//EIP93521 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsBootOverrideBootNextSupport
//
// Description: Function to return BOOT_OVERRIDE_BOOTNEXT_VARIABLE_FEATURE value
//
// Parameter:   VOID
//
// Return value: BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN  IsBootOverrideBootNextSupport (VOID)
{
#if BOOT_OVERRIDE_BOOTNEXT_VARIABLE_FEATURE
	return BOOT_OVERRIDE_BOOTNEXT_VARIABLE_FEATURE;
#else
	return 0;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TseSuppressOneofMultilineSupport
//
// Description: Function to return TSE_SUPPRESS_MULTILINE_FOR_ONEOFLABEL value
//
// Parameter:   VOID
//
// Return value: BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TseSuppressOneofMultilineSupport(VOID)
{

#ifdef TSE_SUPPRESS_MULTILINE_FOR_ONEOFLABEL
	return TSE_SUPPRESS_MULTILINE_FOR_ONEOFLABEL;
#else
	return FALSE;
#endif

}

//EIP99059 starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrRegFormNotificationWrapper
//
// Description:	Wrapper function for RegFormNotification
//
// Input:		VOID
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RegFormNotification (VOID);
EFI_STATUS RTIfrRegFormNotificationWrapper (VOID)
{
#if SETUP_RUNTIME_IFR_PROCESSING
	return RegFormNotification ();
#else
	return EFI_SUCCESS;	
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrUnRegFormNotificationWrapper
//
// Description: Wrapper function for UnRegFormNotification
//
// Input:	VOID	
//
// Output:	VOID	
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UnRegFormNotification (VOID);
VOID RTIfrUnRegFormNotificationWrapper (VOID)
{
#if SETUP_RUNTIME_IFR_PROCESSING
	UnRegFormNotification ();
#endif
}
//EIP99059 ends

//EIP94234 starts
//<AMI_PHDR_START>		
//----------------------------------------------------------------------------
//
// Procedure:   DrawPostLogoAt0Pos
//
// Description: Retrurns DRAW_POST_LOGO_AT_0POS token value
//
// Parameter:   VOID
//
// Return value: BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DrawPostLogoAt0Pos (VOID)
{
#ifdef DRAW_POST_LOGO_AT_0POS
	 return DRAW_POST_LOGO_AT_0POS;	
#else
    return FALSE;
#endif	
}
//EIP94234 ends
//EIP 93881 & 93873 : START
//Save pwd to nvram and not loading empty pwd on loading defaults.
//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	TSEPwdSavetoNvram
//
// Description:	Returns the token value for SETUP_SAVE_PSWD_TO_NVRAM
//
// Input:	VOID
//
// Output:  UINT32 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TSEPwdSavetoNvram(VOID)
{

#ifdef SETUP_SAVE_PSWD_TO_NVRAM
    return SETUP_SAVE_PSWD_TO_NVRAM;
#endif
    return FALSE;					//Defaultly disabled.

}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------------------------------------------
// Procedure:	TSEDonotLoadPasswordOnDefaults
//
// Description:	Returns the token value for TSE_DONOT_LOAD_PASSWORD_ON_DEFAULTS
//
// Input:	VOID
//
// Output:  UINT32 
//
//-------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TSEDonotLoadPasswordOnDefaults(VOID)
{

#ifdef TSE_DONOT_LOAD_PASSWORD_ON_DEFAULTS
    return TSE_DONOT_LOAD_PASSWORD_ON_DEFAULTS;
#endif
    return FALSE;					//Defaultly disabled.

}
//EIP 93881 & 93873 : END
//EIP 94205 START
//<AMI_PHDR_START>
//------------------------------------------------------------------------------
// Procedure:	ShellTextMode
//
// Description:	Returns type of shell text mode
//
// Input:	    VOID
//
// Output:      UINT32
//
//-----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32  ShellTextMode (VOID)
{//EIP 94205 : OEM needs Token to assign the display mode of SHELL.
#ifdef SHELL_TEXT_MODE
	return SHELL_TEXT_MODE;
#else
	return 0xFF;
#endif
}
//EIP 94205 END

//EIP-99022 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FlushKeysAfterRead
//
// Description:	Returns value of disable FLUSH_KEYS_AFTER_READ
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   FlushKeysAfterRead(VOID)
{
#ifdef FLUSH_KEYS_AFTER_READ
	return FLUSH_KEYS_AFTER_READ;
#else
	return 0;
#endif
}
//EIP-99022 Ends

//EIP-112628 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	gotoExitOnEscKey
//
// Description:	Returns value of disable SETUP_GO_TO_EXIT_PAGE_ON_EXIT_KEY
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   gotoExitOnEscKey(EFI_GUID *exitPageGuid, UINT16 *pageClass, UINT16 *pageSubclass, UINT16 *pageFormID)
{
#if SETUP_GO_TO_EXIT_PAGE_ON_EXIT_KEY

	EFI_GUID ExitPageGuid = EXIT_PAGE_GUID;
	MemCopy(exitPageGuid, &ExitPageGuid, sizeof(EFI_GUID));
	*pageClass 		= (UINT16)EXIT_PAGE_CLASS;
	*pageSubclass	= (UINT16)EXIT_PAGE_SUB_CLASS;
	*pageFormID		= (UINT16)EXIT_PAGE_FORM_ID;

	return TRUE;
#else
	return FALSE;
#endif
}
//EIP-112628 ENDS

//EIP-103540 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		PISpecVersion
//
// Description:		Returns PI_SPECIFICATION_VERSION value
//
// Input:			VOID
//
// Output:			UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN   PISpecVersion(VOID)
{
#ifdef PI_SPECIFICATION_VERSION
	return PI_SPECIFICATION_VERSION;
#else
	return 0;
#endif
}
//EIP-103540 Ends

//EIP-116315 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsShowPromptStringAsTitle
//
// Description:	Returns token value TSE_SHOW_PROMPT_STRING_AS_TITLE
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   IsShowPromptStringAsTitle(VOID)
{
#if TSE_SHOW_PROMPT_STRING_AS_TITLE
	return TSE_SHOW_PROMPT_STRING_AS_TITLE;
#else
	return 0;
#endif
}
//EIP-116315 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PrntScrnKeyHandleactionWrapper
//
// Description:	Wrapper function to call PrntScrnKeyHandleaction
//
// Input:		VOID
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS WriteDataToFile(CHAR16 *filename, VOID *Data, UINTN length, UINT32 index);
EFI_STATUS WriteDataToFileWrapper (CHAR16 *filename, VOID *Data, UINTN length, UINT32 index)
{
   EFI_STATUS Status = EFI_SUCCESS;
#if EFI_SPECIFICATION_VERSION>=0x2000A   
   Status = WriteDataToFile (filename, Data, length, index);
#endif
   return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UIUpdateCallbackHook
//
// Description:  Set OVERRIDE_UIUpdateCallbackHook to 1, if OEM wants to override the UIUpdateCallbackHook function from Board module.
//
// Input:   VOID
//
// Output:  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_UIUpdateCallbackHook
VOID UIUpdateCallback( VOID * Handle, UINT32 OldVariableCount );
VOID UIUpdateCallbackHook( VOID * Handle, UINT32 OldVariableCount )
{   //EIP 129750 : Modified UIUpdateCallback as module hook
    UIUpdateCallback((VOID*)Handle, OldVariableCount);
}
#endif


//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Procedure:   FixMergePagesExtraHook
//
// Description:  Set OVERRIDE_FixMergePagesExtraHook to 1, if OEM wants to override the UIUpdateCallbackHook function from Board module.
//
// Input:   VOID
//
// Output:  EFI_STATUS
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_FixMergePagesExtraHook
VOID FixMergePagesExtraHook (VOID *gPages, VOID *tempPages)
{

}
#endif

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Procedure:   PageRemoveHook
//
// Description:  Set OVERRIDE_PageRemoveHook to 1, if OEM wants to override the PageRemoveHook function from Board module.
//
// Input:   VOID
//
// Output:  EFI_STATUS
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_PageRemoveHook
void PageRemoveHook (UINTN PageIndex, void *pageInfo, void *PageHandle, UINT16 PageFormID)
{
	
}
#endif

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Procedure:   ProcessPackNotificationHook
//
// Description:  Set OVERRIDE_ProcessPackNotificationHook to 1, if OEM wants to override the ProcessPackNotificationHook function from Board module.
//
// Input:   VOID
//
// Output:  EFI_STATUS
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_ProcessPackNotificationHook
EFI_STATUS ProcessPackNotification (void);
EFI_STATUS ProcessPackNotificationHook (void)
{
	return ProcessPackNotification ();
}
#endif

//EIP131739 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   MainSetupLoopInitHook
//
// Description:  Set OVERRIDE_MainSetupLoopInitHook to 1, if OEM wants to override the MainSetupLoopInitHook function from Board module.
//
// Input:   VOID
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if !OVERRIDE_MainSetupLoopInitHook
VOID MainSetupLoopInit(VOID);
VOID MainSetupLoopInitHook ( VOID )
{	//EIP131739 : Modified MainSetupLoopInit as module hook for TSE
	MainSetupLoopInit();
}
#endif
//EIP131739 Ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		IsLoadSysteAccessOnUserDefault
//
// Description:	Returns token value TSE_DONOT_LOAD_SYSTEM_ACCESS_FOR_USER_DEFAULT
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   IsLoadSysteAccessOnUserDefault(VOID)
{
#if TSE_DONOT_LOAD_SYSTEM_ACCESS_FOR_USER_DEFAULT
	return TSE_DONOT_LOAD_SYSTEM_ACCESS_FOR_USER_DEFAULT;
#else
	return 0;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		IsANSIEscapeCodeSupported
//
// Description:		Returns token value TSE_ANSI_ESC_CODE_SUPPORT
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   IsANSIEscapeCodeSupported(VOID)
{
#if TSE_ANSI_ESC_CODE_SUPPORT
	return TSE_ANSI_ESC_CODE_SUPPORT;
#else
	return 0;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		TseDebugDisableApplicationDestructor
//
// Description:	Returns token value TSE_DBG_DISABLE_APPDESTRUCTOR
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TseDebugDisableApplicationDestructor (VOID)
{
#ifdef TSE_DBG_DISABLE_APPDESTRUCTOR
	return TSE_DBG_DISABLE_APPDESTRUCTOR;
#else
	return FALSE;
#endif
}

//EIP 162981 Providing defaults through sdl tokens starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		TseDefaultSetupPasswordSupported
//
// Description:		Returns token value TSE_DEFAULT_SETUP_PASSWORD_SUPPORT
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TseDefaultSetupPasswordSupported (void)
{
#ifdef TSE_DEFAULT_SETUP_PASSWORD_SUPPORT
	return TSE_DEFAULT_SETUP_PASSWORD_SUPPORT;
#else
	return FALSE;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		DefaultSetupPwdAtFirstBootOnly
//
// Description:		Returns token value DEFAULT_SETUP_PWD_AT_FIRSTBOOT_ONLY
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DefaultSetupPwdAtFirstBootOnly (void)
{
#ifdef DEFAULT_SETUP_PWD_AT_FIRSTBOOT_ONLY
	return DEFAULT_SETUP_PWD_AT_FIRSTBOOT_ONLY;
#else
	return FALSE;
#endif
}
//EIP 162981 Providing defaults through sdl tokens ends

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		IsDisableESCinBBSMenu
//
// Description:		Returns token DISABLE_ESC_IN_BBS value
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   IsDisableESCinBBSMenu (VOID)
{
#ifdef DISABLE_ESC_IN_BBS
	return DISABLE_ESC_IN_BBS;
#else
	return 0;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		TseRtAccessSupport
//
// Description:		Returns token RT_ACCESS_SUPPORT_IN_HPKTOOL value
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   TseRtAccessSupport (VOID)
{
#ifdef RT_ACCESS_SUPPORT_IN_HPKTOOL
	return RT_ACCESS_SUPPORT_IN_HPKTOOL;
#else
	return 0;
#endif
}


//<AMI_PHDR_START>
// Procedure:		IsGrayoutSelectable
//
// Description:	Returns token value TSE_SETUP_GRAYOUT_SELECTABLE
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsGrayoutSelectable()
{
#if TSE_SETUP_GRAYOUT_SELECTABLE
    return 1;
#else
    return 0;
#endif
}

//EIP-93340 Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		IsSupportDefaultForStringControl
//
// Description:	Returns TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL token value
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   IsSupportDefaultForStringControl (VOID)
{
#if TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL
	return TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL;
#else
	return FALSE;
#endif
}
//EIP-93340 End

//EIP-107833 Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:		IsTseBestTextGOPModeSupported
//
// Description:	Returns token TSE_BEST_TEXT_GOP_MODE value
//
// Input:			VOID
//
// Output:			BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN   IsTseBestTextGOPModeSupported (VOID)
{
#ifdef TSE_BEST_TEXT_GOP_MODE
	return TSE_BEST_TEXT_GOP_MODE;
#else
	return FALSE;
#endif
}
//EIP-197833 End
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
