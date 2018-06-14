//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2013, American Megatrends, Inc.    **//
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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/FakeTokens.c $
//
// $Author: Arunsb $
//
// $Revision: 25 $
//
// $Date: 2/11/14 7:35p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/FakeTokens.c $
// 
// 25    2/11/14 7:35p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 24    11/26/13 9:49a Premkumara
// [TAG]  		EIP118342
// [Category]  	Improvement
// [Description]  	Show meaningful error message when HDD is locked after
// reached maximum unlocking attempt.
// [Files]  		TseAdvanced.c, CommonHelper.c, FakeToken.c, AmiTseStr.uni
// 
// 23    5/22/13 11:18p Premkumara
// [TAG]  		EIP123432 
// [Category]  	Bug Fix
// [Issue Faced]            Take print screen for save & Exit msg box. OK
// of msg box is consumed by Save & Exit msg box.
// 		- Cursor is missing after taking print screen of popupedit box in
// string control
// 		- Printscreen support is not given for Filebrowser feature
// [RootCause]  	- When msg box for Save&Exit is popped and printscreen
// event is called and displaying msg box over Save&Exit. Then msgbox
// handleaction for printscreen event will change the result value in
// _CallbackMsgbox() function so it will break the while loop in
// _CallbackGetValue() function so destroy the next msg box in
// CallbackShowMessageBox() function.
// 		- DrawCursor variable is not set to TRUE after printscreen event
// [Solution]  	- Returning EFI_UNSUPPORTED for printscreen event handling
// function for messgebox and change the result value to 0xff
// 		- Support given for file browser feature
// [Files]  		Callback.c, MessageBox.c, Minisetupext.c, PopupString.c,
// AddBootOption.c
// 		AmiTSEStr.uni, FakeToken.c 
// 
// 22    4/18/13 1:48a Arunsb
// [TAG]  		EIP81490
// [Category]  	New Feature
// [Description]  	Post message support for BBS popup menu
// [Files]  		AMITSE.sdl, AmiTSEStr.uni, commonoem.c, FakeTokens.c and
// globals.c
// 
// 21    3/25/13 8:42a Premkumara
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
// 20    10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 18    9/17/12 5:59a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 16    9/03/12 3:08a Premkumara
// [TAG]  		EIP 96246
// [Category]  	Improvement
// [Description]  	Improvement of a boots override when firmware has a
// BootNext variable
// [Files]  		AMITSE.sdl, CommonHelper.c, FakeToken.c, AmiTSEStr.uni,
// TseAdvanced.c
// 
// 15    1/09/12 1:38a Arunsb
// [TAG]  		EIP79952
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Add driver option displays select boot option as title
// [RootCause]  	Title problem
// [Solution]  	Title changes
// [Files]  		Faketokens.c, amitsestr.uni, addbootoption.c,
// uefi2.0\hiicallback.c and uefi21wapper.c
// 
// 14    12/16/11 7:16a Arunsb
// Ordered the strings as Bootonly strings then normal strings
// 
// 13    12/16/11 6:05a Premkumara
// [TAG]  		EIP63190
// [Category]  	Improvement
// [Description]  	Changed Order of Strings based on TSE flavors.
// [Files]  		AmiTSEStr.uni, FakeTokens.c
// 
// 12    11/20/11 7:38a Premkumara
// [TAG]  		EIP73226
// [Category]  	New Feature
// [Description]  	Extended support for password prompt
// [Files]  		FakeToken.c, Uefi21Wapper.c, AmiTSEStr.uni, PopupPassword.c,
// 
// 11    11/14/11 2:40p Blaines
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
// 10    9/04/11 3:59a Arunsb
// [TAG]  		EIP65320
// [Category]  	Improvement
// [Description]  	Board module hook for LoadImage failure.
// Review comment addressed.
// [Files]  		Commonhelper.c, amitsestr.uni, boot.c and faketokens.c
// 
// 9     6/30/11 3:57a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Driver health related string tokens added.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 8     3/28/11 11:00p Madhans
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 7     12/28/10 5:59p Mallikarjunanv
// [TAG]  		EIP41615
// [Category]  	New Feature
// [Description]  	Added the file browser support for the Add boot option
// reated controls
// [Files]  		AmiVfr.h, AmiTse.sdl, AmiTseStr.uni, CommonHelper.c,
// Faketokens.c, TseElinks.h, EdkHelper.h, minisetup.h, TseAdvanced.c,
// AddBootOption.c
// 
// 6     9/16/10 8:39p Madhans
// Updated for TSE 2.10. Refer changelog.log for more deatils.
// 
// 5     8/04/10 12:12a Mallikarjunanv
// EIP-29951 : Device Path Name support updates
// 
// 4     4/16/10 5:10p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 12:58p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 3     1/04/10 9:49a Mallikarjunanv
// Added support for reserved boot option names and added condition not to
// accept empty boot option names
// 
// 2     10/28/09 5:34p Madhans
// 1. Support to Add the String from other modules to TSE.
// 2. Clean of GIF and Image code Control them with minimal code from TSE
// binary.
// 
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:49p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
//*****************************************************************//
//*****************************************************************//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		faketokens.c
//
// Description:
// This file does not add any code. It has, all the string tokens that
// are used by Minisetup, to fake the usage to strgather.exe. Add to
// this list, the new string tokens that are defined in
// AmiTSEStrstr.uni and to be used by Minisetup
//
//<AMI_FHDR_END>
//**********************************************************************


//Following code is to force strgatherer to include these strings
#if 0
STRING_TOKEN(STR_MAIN_TITLE)
STRING_TOKEN(STR_MAIN_COPYRIGHT)
STRING_TOKEN(STR_CTRL_CHKBOX_ENABLE)
STRING_TOKEN(STR_CTRL_CHKBOX_DISABLE)
STRING_TOKEN(STR_HELP_TITLE)

STRING_TOKEN(STR_FDD)
STRING_TOKEN(STR_HDD)
STRING_TOKEN(STR_CDROM)
STRING_TOKEN(STR_NETWORK)
STRING_TOKEN(STR_BEV)
STRING_TOKEN(STR_PRI_MAS)
STRING_TOKEN(STR_PRI_SLA)
STRING_TOKEN(STR_SEC_MAS)
STRING_TOKEN(STR_SEC_SLA)
STRING_TOKEN(STR_SATA_X)
STRING_TOKEN(STR_NO_BOOT_OPTIONS)
STRING_TOKEN(STR_PASSWORD_PROMPT)
STRING_TOKEN(STR_ERROR_PSWD)
STRING_TOKEN(STR_DRV_HLTH_REBOOT_POST)
STRING_TOKEN(STR_EVAL_MSG)
STRING_TOKEN(STR_ACK_BBS_POPUP)
STRING_TOKEN(STR_DEL_ENTER_SETUP)
STRING_TOKEN(STR_ACK_ENTER_SETUP)
STRING_TOKEN(STR_GENERAL_HELP)
STRING_TOKEN(STR_GENERAL_HELP_MSG)
STRING_TOKEN(STR_BOOT_MANAGER)
STRING_TOKEN(STR_BOOT_MANAGER_HELP)
STRING_TOKEN(STR_LANGUAGE)
STRING_TOKEN(STR_LANGUAGE_HELP)
STRING_TOKEN(STR_LOAD_PREVIOUS)
STRING_TOKEN(STR_LOAD_PREVIOUS_MSG)
STRING_TOKEN(STR_LOAD_FAILSAFE)
STRING_TOKEN(STR_LOAD_FAILSAFE_HELP)
STRING_TOKEN(STR_LOAD_FAILSAFE_MSG)
STRING_TOKEN(STR_LOAD_OPTIMAL)
STRING_TOKEN(STR_LOAD_OPTIMAL_HELP)
STRING_TOKEN(STR_LOAD_OPTIMAL_MSG)
STRING_TOKEN(STR_SAVE_EXIT)
STRING_TOKEN(STR_SAVE_EXIT_HELP)
STRING_TOKEN(STR_SAVE_EXIT_MSG)
STRING_TOKEN(STR_SAVE_RESET)
STRING_TOKEN(STR_SAVE_RESET_HELP)
STRING_TOKEN(STR_SAVE_RESET_MSG)
STRING_TOKEN(STR_SAVE_VALUES)
STRING_TOKEN(STR_SAVE_VALUES_MSG)
STRING_TOKEN(STR_EXIT)
STRING_TOKEN(STR_EXIT_MSG)
STRING_TOKEN(STR_RESET)
STRING_TOKEN(STR_RESET_MSG)
STRING_TOKEN(STR_SAVE_USER_DEFAULTS)
STRING_TOKEN(STR_LOAD_USER_DEFAULTS)
STRING_TOKEN(STR_LOAD_USER_MSG)
STRING_TOKEN(STR_SUBMENU_OPTION)
STRING_TOKEN(STR_CTRL_OK)
STRING_TOKEN(STR_CTRL_CANCEL)
STRING_TOKEN(STR_CTRL_YES)
STRING_TOKEN(STR_CTRL_NO)
STRING_TOKEN(STR_DAY_SUNDAY)
STRING_TOKEN(STR_DAY_MONDAY)
STRING_TOKEN(STR_DAY_TUESDAY)
STRING_TOKEN(STR_DAY_WEDNESDAY)
STRING_TOKEN(STR_DAY_THURSDAY)
STRING_TOKEN(STR_DAY_FRIDAY)
STRING_TOKEN(STR_DAY_SATURDAY)
STRING_TOKEN(STR_OLD_PSWD)
STRING_TOKEN(STR_NEW_PSWD)
STRING_TOKEN(STR_CONFIRM_NEW_PSWD)
STRING_TOKEN(STR_PSWD_CLR)
STRING_TOKEN(STR_ERROR)
STRING_TOKEN(STR_WARNING)
STRING_TOKEN(STR_WARNING_NOT_FOUND)
STRING_TOKEN(STR_ERROR_INPUT)
STRING_TOKEN(STR_EMPTY_STRING)
STRING_TOKEN(STR_INCONSISTENT_MSG_TITLE)
STRING_TOKEN(STR_NOSUBMITIF_MSG_TITLE)
STRING_TOKEN(STR_BBS_POPUP_TITLE_STRING)
STRING_TOKEN(STR_BBS_POPUP_HELP1_STRING)
STRING_TOKEN(STR_BBS_POPUP_HELP2_STRING)
STRING_TOKEN(STR_BBS_POPUP_HELP3_STRING)
STRING_TOKEN(STR_BBS_POPUP_HELP_STRING)
STRING_TOKEN(STR_POPUPMENU_ENTER_SETUP)
STRING_TOKEN(STR_USB)
STRING_TOKEN(STR_VENDOR)
STRING_TOKEN(STR_FILEPATH)
STRING_TOKEN(STR_PROTOCOL)
STRING_TOKEN(STR_FV_FILEPATH)
STRING_TOKEN(STR_USB_DP)
STRING_TOKEN(STR_SCSI_DP)
STRING_TOKEN(STR_FIBRE_CHANNEL_DP)
STRING_TOKEN(STR_1394_DP)
STRING_TOKEN(STR_I20_DP)
STRING_TOKEN(STR_INFINIBAND_DP)
STRING_TOKEN(STR_VENDOR_DP)
STRING_TOKEN(STR_MAC_DP)
STRING_TOKEN(STR_NETWORK_IPV4_DP)
STRING_TOKEN(STR_NETWORK_IPV6_DP)
STRING_TOKEN(STR_UART_DP)
STRING_TOKEN(STR_USB_CLASS_DP)
STRING_TOKEN(STR_USB_CLASS_PHY_DP)
STRING_TOKEN(STR_USB_CLASS_MASS_DP)
STRING_TOKEN(STR_USB_LOGICAL_DP)
STRING_TOKEN(STR_USB_SATA_DP)
STRING_TOKEN(STR_USB_ISCSI_DP)
STRING_TOKEN(STR_HARD_DISK_ORDER)
STRING_TOKEN(STR_CDROM_ORDER)
STRING_TOKEN(STR_FLOPPY_DISK_ORDER)
STRING_TOKEN(STR_NETWORK_ORDER)
STRING_TOKEN(STR_BEV_ORDER)
STRING_TOKEN(STR_USB_ORDER)
STRING_TOKEN(STR_PCMCIA_ORDER)
STRING_TOKEN(STR_UNKNOWN_ORDER)
STRING_TOKEN(STR_ADD_BOOT_OPTION_RESERVED)
STRING_TOKEN(STR_ADD_BOOT_OPTION_EMPTY)
STRING_TOKEN(STR_ADD_DRIVER_OPTION_EMPTY)
STRING_TOKEN(STR_DEL_BOOT_OPTION_RESERVED)
STRING_TOKEN(STR_MSGBOX_PROGRESS_TITLE)
STRING_TOKEN(STR_MSGBOX_PROGRESS_TEXT)
STRING_TOKEN(STR_FILE_SYSTEM)
STRING_TOKEN(STR_FILE_PATH)
STRING_TOKEN(STR_DRIVER_PATH)
STRING_TOKEN(STR_DRV_HLTH_TITLE)
STRING_TOKEN(STR_DRV_HLTH_RECON)
STRING_TOKEN(STR_DRV_HLTH_REBOOT)
STRING_TOKEN(STR_SECBOOT_VIOLATION)
STRING_TOKEN(STR_SECBOOT_INV_SIGN)
STRING_TOKEN(STR_DBG_PRINT_CHECKED)
STRING_TOKEN(STR_DBG_PRINT_HIIPARSING)
STRING_TOKEN(STR_DBG_PRINT_HIIFUNCTION)
STRING_TOKEN(STR_DBG_PRINT_HIICALLBACK) 
STRING_TOKEN(STR_DBG_PRINT_HIINOTIFICATION)
STRING_TOKEN(STR_DBG_PRINT_IFRFORM)
STRING_TOKEN(STR_DBG_PRINT_VARIABLE_CACHE)
STRING_TOKEN(STR_OVERRIDE_BOOTNEXT_OPTION_1)						
STRING_TOKEN(STR_OVERRIDE_BOOTNEXT_OPTION_2)						
STRING_TOKEN(STR_OVERRIDE_BOOTNEXT_OPTION_3)
STRING_TOKEN(STR_OVERRIDE_OPTION_MENU_TITLE)
STRING_TOKEN(STR_OVERRIDE_OPTION_MENU_LEGEND)
STRING_TOKEN(STR_OLD_PSWD_LABEL)
STRING_TOKEN(STR_NEW_PSWD_LABEL)
STRING_TOKEN(STR_CONFIRM_NEW_PSWD_LABEL)
STRING_TOKEN(STR_PSWD_CLR_LABEL)
STRING_TOKEN(STR_FILE_SYSTEM_TO_SAVE_IMG)
#endif


//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2013, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           5555 Oakbrook Pkwy, Norcross, Georgia 30093       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
