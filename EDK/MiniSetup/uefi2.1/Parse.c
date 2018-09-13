//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Parse.c 68    7/12/14 12:23p Arunsb $
//
// $Revision: 68 $
//
// $Date: 7/12/14 12:23p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Parse.c $
// 
// 68    7/12/14 12:23p Arunsb
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
// 67    5/02/14 5:48a Arunsb
// [TAG]  		EIP156258
// [Category]  	Improvement
// [Description]  	Providing ELINK option to suppress the handle
// comparison on dynamic parsing
// [Files]  		AMITSE.mak, AMITSE.sdl, commonoem.c, commonoem.h and Parse.c
// 
// 66    5/02/14 4:42a Premkumara
// [TAG]  		EIP95647
// [Category]  	Improvement
// [Description]  	Dynamic Forms need to hide.
// [Files]  		AMITSE.mak, AMITSE.sdl, CommonOem.c, Parse.c
// 
// 65    5/01/14 10:29p Arunsb
// EIP148837 change reverted, this is specially for Aptio5 customization
// 
// 64    5/01/14 6:40p Premkumara
// Resolved build error
// 
// 63    5/01/14 4:42p Premkumara
// [TAG]  		EIP151552 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	IScsi Configuration option throws exception on pressing it
// after 'Esc' is done to move back to previous page.
// [RootCause]  	When "Save and Exit" in iScsi page is selected to create
// new controls, while parsing PageInfo->PageParentID is not handled
// properly. So while initializing menu title menu menu->CurrEntry is not
// setting properly because of ParentPageID.
// [Solution]  	While parsing PageInfo->PageParentID is not handled
// properly. So while initializing menu title menu menu->CurrEntry is not
// setting properly so that menu will be initialize and draw proper data.
// [Files]  		Parse.c
// 
// 62    5/01/14 4:09p Premkumara
// [TAG]  		EIP148837
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Checkbox Control control is not working in dynamic page.
// [RootCause]  	TSE is treating both the OneOf control and CheckBox
// Control as CONTROL_TYPE_POPUPSEL
// During dynamic parsing TSE is changing the Control type to
// CONTROL_TYPE_POPUPSEL if it is CheckBox.
// That's Why in ESA ComboBox is coming instead of CheckBox.
// [Solution]  	For Dynamic Parsing after creating the Control Info i am
// calling GetCheckBoxStyle() to get the Type as 
// CONTROL_TYPE_CHECKBOX for CheckBox Control.
// [Files]  		Parse.c
// 
// 61    12/04/13 2:56a Premkumara
// [TAG]	EIP139099
// [Category]	New Feature
// [Description]	Supress formset other than
// EFI_HII_PLATFORM_SETUP_FORMSET_GUID and
// EFI_HII_DRIVER_HEALTH_FORMSET_GUID through elink based on token
// [Files]	AMITSE.sdl, AMITSE.mak, CommonOem.c, Hii.c, Parse.c,
// TseUefiHii.h
// 
// 60    6/10/13 12:21p Arunsb
// EIP122907 EFI_IFR_TYPE_OTHER support provided.
// 
// 59    5/22/13 11:11a Arunsb
// Fixed these issues,
// -If control has submit/inconsistent and its form has condition over it
// then it will hang,
// - Read write opcode hang
// 
// 58    5/22/13 10:19a Premkumara
// [TAG]  		EIP120418 
// [Category]  	Improvement
// [Issue Faced]           When any suppressif, grayoutif, disableif over
// the form then HPKTool crashes
// [Root Cause]            The end of suppressif, grayoutif, disableif
// over the form were not handle properly
// [Solution]                  The suppressif,grayoutif,disable are pushed
// and end of suppressif, grayoutif, disableif over the form are popupout
// properly at the end of parsing form
// [Files]  		Parse.c
// 
// 57    5/20/13 3:36a Premkumara
// [TAG]  		EIP124286 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Optimal Defaults are not loading on pressing ResetButton
// [RootCause]  	While filling defaults for DefaultOp2 optimal defaults
// are skipped in __UpdateDefaults() fn
// [Solution]  	If default ID EFI_IFR_DEFAULT_OP is found then fill
// default link for all types of defaults
// [Files]  		Parse.c
// 
// 56    4/17/13 2:29p Arunsb
// [TAG]  		EIP109812, 107774
// [Category]  	Improvement
// [Description]  	Provide support for EFI_IFR_TYPE_REF and EFI_IFR_REF5
// [Files]  		Hii.c, HiiCallback.c, Parse.c and TseUefiHii.h
// 
// 55    4/16/13 9:58a Arunsb
// Missed HII structures added in TSE itself. So Hii structure names
// changed.
// 
// 54    4/02/13 8:21a Arunsb
// [TAG]  		EIP113919, EIP114842
// [Category]  	Improvement
// [Description]  	Provide support for EFI_IFR_WRITE, EFI_IFR_READ,
// EFI_IFR_GET, EFI_IFR_SET and EFI_IFR_MAP_OP.
// [Files]  		Setupdata.h, ctrlcond.c, expression.c, hii.c and parse.c
// 
// 53    3/29/13 8:19a Arunsb
// [TAG]  		EIP111061 
// [Category]  	Improvement
// [Description]  	Provide support for efivarstore opcode
// [Files]  		Parse.c and tseuefihii.h
// 
// 52    3/25/13 8:05a Premkumara
// [TAG]  		EIP105468
// [Category]  	New Feature
// [Description]  	Support for EFI_IFR_REFRESH_ID opcode for Offline
// Parsing
// [Files]  		Parse.c, Hii.c, Setupdata.h
// 
// 51    3/20/13 10:42a Blaines
// [TAG] - EIP 116513 
// [Category]- Defect 
// [Symptom]- System hangs while navigating SAS Card UEFI HII Page, when
// TSE_MULTILINE_CONTROLS is enabled.
// 
// [Root cause]
// The Hii page contained EFI_IFR_ACTION controls with a refresh value
// greater than zero. When DEBUG_MODE is enabled, 
// The increased page draw completion time caused the Action timer to
// expire. The constant page refresh prevented the call
// to function ActionReadKey from the function ActionGetAction.
// 
// [Solution]- Set the refresh value for EFI_IFR_ACTION controls only if
// AMI CALLBACK value is used.
// 
// [Files] 
//   -  Parse.c
// 
// 50    3/20/13 9:29a Premkumara
// [TAG]  		EIP116566
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Fixed Boot Order Issue
// [RootCause]  	Some controls are using checkbox(from runtime pages)
// value to suppress some controls in SuperIO configuration page.
// Dynamic parsing is modifying Checkbox controls optimal and failsafe
// defaults by setting size=1 irrespective of presence of defaults.
// [Solution]  	Setting size =0/1 based on presence of fail safe/Optimal
// defaults for CheckBox controls.
// [Files]  		Parse.c
// 
// 
// 48    3/15/13 2:15a Premkumara
// [TAG]  		EIP85745 & 109814 
// [Category]  	Improvement
// [Description]  	Support for Modal Form Support as per UEFI 2.3.1
// [Files]  		Parse.c, Page.c, Menu.c, Hotclick.c
// 
// 47    12/21/12 8:34p Blaines
// [TAG]  		EIP 108987
// [Category]  	Defect
// [Symptom]  	SAS controller card HII menus hang when selecting and HII
// pack update occurs. 
// [RootCause]  	The Setup maintains a page data cache when hii packs are
// created, and will normally try to reuse the page data when hii packs
// are removed/updated. If the existing page data cannot be reused, the
// function _InvalidateExistingPage is called, but the
// NewPageInfo->PageParentID is updated with the
// OldPageInfo->PageParentID.
// This resulted in circular page reference, causing the function
// MenuInitialize (menu.c) to enter an infinite loop.
//   
// [Solution]	In the function _InvalidateExistingPage, remove the code
// that changes NewPageInfo->PageParentID  with the
// OldPageInfo->PageParentID.
// 		
// [Files Changed]
// - Parse.c
// 
// 
// 46    10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 16    10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 44    9/25/12 8:31a Rajashakerg
// [TAG]  		EIP94424 
// [Category]  	Improvement
// [Description]  	Some form can't normal display when add Hii item will
// in runtime during
// [Files]  		AMITSE.sdl, AMITSE.mak, Parse.c
// 
// 43    9/18/12 2:15a Rajashakerg
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
// 42    2/02/12 3:12a Premkumara
// Updated with CheckBox scope issue.
// 
// 41    2/02/12 3:03a Premkumara
// [TAG]  		EIP75066 
// [Category]  	Improvement
// [Description]  	Support loading defaults for Ordelist controls
// [Files]  		Ordlistbox.c, Uefi21Wapper.c, CtrlCond.c, HiiCallback.c,
// Parse.c, Uefi20Wapper.c, TseUefihiil.h
// 
// 40    1/20/12 1:59a Arunsb
// [TAG]  		EIP80424
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Circular reference is not updated after pack update which
// leads to RSOD
// [RootCause]  	Circular reference is not updated after pack update which
// leads to RSOD
// [Solution]  	Setting NewPageInfo->PageHandle before calling
// _AdvAddPageToList() so that Circular reference is updated properly
// [Files]  		Parse.c
// 
// 39    1/17/12 5:39a Premkumara
// [TAG]  		EIP80422
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Update Defaults for Checkbox controls doesn't support scope
// [RootCause]  	The flaw in this is that this code will never get
// executed as the scope of a Checkbox control is always 1
// [Solution]  	Comment the scope check if(CheckBoxOp->Header.Scope == 0)
// in _UpdateDefaults() function to execute if scope is 0
// [Files]  		Parse.c
// 
// 38    11/30/11 6:34a Premkumara
// [TAG]  		EIP71351
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Setup Crash when iSCSI is loaded
// [RootCause]  	Aptio giving length as 0xe(matches size of
// EFI_IFR_ONE_OF_OPTION) but in latest EDKII driver it is 0x1c.
// [Solution]  	change the length as j += ((EFI_IFR_OP_HEADER*)(buff + i +
// j))->Length;
// [Files]  		Parse.c, Hii.c, Variable.c, Minisetupext.c, 
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
// 36    11/14/11 4:27a Arunsb
// [TAG]  		EIP72540
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Advance page disappear on using 4.6.2_TSE_2_14_1219
// [RootCause]  	Offline pages also considered in dynamic parsing
// [Solution]  	Offline pages are not considered in dynamic parsing
// [Files]  		hii.c and parse.c
// 
// 35    11/10/11 11:47a Premkumara
// [TAG]  		EIP73396 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	On Pressing ESC the token SETUP_GO_TO_EXIT_PAGE_ON_EXIT_KEY
// key doesnt work in UEFI2.1
// [RootCause]  	In AddPageIdToList() function. 
// If PageIdSize = 0 then first pageInfo will not copy into PageIdInfoPtr
// [Solution]  	In Parse.c,
// - removed PageIdSize =0 in AddPageIdToList() function. If PageIdSize =
// 0 then first pageInfo will not copy into PageIdInfoPtr
// [Files]  		Parse.c
// 
// 34    9/29/11 3:24p Madhans
// File Checkin comments corrected.
// 
// 33    8/26/11 6:12p Blaines
// [TAG]  		EIP68354
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	non-refresh date control is gets refreshed
// [RootCause]  	Date controls that don't have IFR_REFRESH_OP are being
// assumed to have it. The Flags are not checked for type
// QF_DATE_STORAGE_TIME.
// [Solution]  	The Flags are checked for type QF_DATE_STORAGE_TIME.
// [Files]  		TseLite: Time.c, Date.c
// Uefi21: Parese.c, Uefi21Wrapper.c
// 
// 31    6/30/11 4:19a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Dynamic parsing changed for driver health config. page
// via sendform.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 30    6/28/11 2:40p Arunsb
// Build error resolved
// 
// 29    6/28/11 9:38a Arunsb
// EIP 56405 . Review comment addressed
// Comment: Uncomment the 2.1 EFI Varstore support part.
// 
// 28    6/24/11 10:16a Premkumara
// [TAG]  		EIP62310, EIP 59743, EIP 62308
// [Category]  	Improvement
// [Description]  	Merge all SupportEFI_IFR_SUPPRESS_IF_OP,
// EFI_IFR_GRAYOUT_IF_OP,
// cases in one case
// [Files]  		Parse.c
// 
// 27    6/23/11 4:02p Rajashakerg
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
// 26    6/22/11 5:17p Arunsb
// [TAG]       EIP56405
// [Category]      New Feature
// [Description]   Support for EFI_IFR_VARSTORE_NAME_VALUE opcode
// [Files]         Hii.c, parse.c and uefi21wapper.c
// 
// 25    6/22/11 9:27a Premkumara
// [TAG]  		EIP 62310, EIP 59743, EIP 62308
// [Description]  	SupportEFI_IFR_SUPPRESS_IF_OP, EFI_IFR_GRAYOUT_IF_OP,
// EFI_IFR_DISABLE_IF_OP Over the Form or Formset
// [Files]  		parse.c
// 
// 24    6/08/11 4:52p Arunsb
// [TAG]  		EIP61650
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Cannot edit time field when using new "time" format
// [RootCause]  	Default refresh interval set to all the time variables
// [Solution]  	Default refresh interval provided only for RTC time
// variable
// [Files]  		uefi2.1\Parse.c
// 
// 23    6/01/11 4:11p Madhans
// [TAG]  		EIP61588
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Advanced -> ISCSI -> Add an attempt-> Mac Address -> Save
// changes causes the system to hang.
// [RootCause]  	Dynamic update for the goto control to same target page
// was not updated correctly.
// [Solution]  	Fixed to update the control destination page correctly.
// [Files]  		parse.c
// special.c
// 
// 22    5/31/11 9:52a Premkumara
// [TAG]  		EIP48930 
// [Description]  	Boot override hangs with exception 0x0d
// [Files]  		Parse.c, hii.c
// 
// 21    4/29/11 4:46p Arunsb
// For 2.13 public patch release IFR RefX feature is omitted
// 
// 20    4/22/11 6:09p Arunsb
// [TAG]  		EIP59002
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Refresh interval not set properly
// [Solution]  	If control has callback then it is handled in
// EFI_IFR_ACTION_OP
// also.
// [Files]  		Parse.c
// 
// 19    4/20/11 5:37p Blaines
// [TAG] - EIP 55762
// [Category]- Action Item
// [Synopsis]- Add support for IFR RefX controls.
// [Files] - setupdata.h, special.c, frame.c, Hii.c, Parse.c,
// Uefi21Wrapper.c
// 
// 18    3/28/11 11:03p Madhans
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 17    3/28/11 9:49p Premkumara
// [TAG]  		EIP52562 
// [Category]  	Improvement
// [Description]  	Need to have the Fixed Limit in AMITSE module for
// Controls, Pages and Variable etc.
// [Files]  		TSEUefiHii.h, Hii.c, Parse.c, hii.c
// 
// 16    3/28/11 5:34p Rajashakerg
// [TAG]  		EIP56896 
// [Category]  	Improvement
// [Description]  	
// TSE: Support for EFI_IFR_LOCKED opcode
// [Files]  		Parse.c
// 
// 15    3/18/11 2:46a Rajashakerg
// [TAG]  		EIP56124
// [Category]  	New Feature
// [Description]  	TSE: Support for EFI_IFR_DEFAULT opcode
// [Files]  		Parse.c, TseUefiHii.h 
// 
// 14    3/09/11 7:26p Madhans
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
// 13    2/10/11 12:32p Blaines
// [TAG] - EIP 53146
// [Category]- New Feature
// [Description] -Add the support to Move the Dynamic IFR Pages under
// subpages. It should be customizable to move around.
// 
// 12    12/28/10 12:31p Madhans
// To update the Tag of EIp 46998. UEFI option ROM menus disappear in
// Setup when certain options are selected. 
// No file changed but Comment updated right
// 
// 11    12/06/10 5:48p Madhans
// [TAG] - EIP 49488  
// [Category]- Defect
// [Severity]- Mordarate
// [Symptom]- ISCSI Pages not working.
// [Rootcause] Variable Entry that is added by offline parsing is left
// untouched and it cause the issue when locating the varible based on
// GUID and Variable Name.
// [Solution]- Fixed when adding Variable to the list to check for NULL
// Variable handle.
// [Files] - Parse.c
// 
// 10    12/02/10 2:39p Madhans
// [TAG] - EIP 48169  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Code Cleanup and Compiler Warning need to resolved.
// [Rootcause] Warnings reported when we build AMI higher Warning level.
// [Solution]- 1. Fix the warnings and do the code cleanup. 
//             2. Introduce proper checks.
//             3. change the popupSel.c to not change the Option/variable
// cache to default or first option
//                when the variable cache is not matching with any of
// option.
// [Files] - commonoem.c bbs.c boot.c hiistring.c resource.c
// popuppassword.c popupsel.c
//           expression.c hii.c parse.c
// 
// 9     10/27/10 4:25p Madhans
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
// 8     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 13    9/15/10 1:53p Madhans
// To fix the Issues Parent page fixing with Dynamic update of Pages. 
// 
// 11    9/07/10 1:43p Blaines
// Support loading defaults for Data&Time in UEFI 2.1
// 
// 10    8/12/10 1:11p Blaines
// EIP-40946 : Fix root page processing to support Award Style setup.
// 
// 9     8/10/10 7:14p Madhans
// EIP 40555 : To avoid Compilation issues with Fareast Windows.
// 
// 8     6/17/10 4:19p Madhans
// To fix the circular Page referance
// 
// 7     6/17/10 2:47p Madhans
// Fix for parsing correctly.
// in Dyncamic parsing Fix the parent pages.
// 
// 6     6/14/10 7:14p Madhans
// Dynamic parsing support
// 
// 5     3/11/10 5:43p Madhans
// Coding Standards Update
//
// 4     2/15/10 10:19p Madhans
// to support EDK nt32 version
//
// 3     11/19/09 5:31p Presannar
// Updated TSE include file name to not clash with CORE file
//
// 2     8/11/09 2:57p Presannar
// Added fn _AdvAddPageToList, _ReplacePageWithNewPage and
// _AdvAddControlToList to handle dynamic updation of IFR data
// Renamed _GetDefaultValue as GetDefaultValue
// Modified _GetQuestionToken to get prompt of Ordered List opcode
// Modified AddControlToList and AddPageToList to do Advanced Parsing
// Added fn _ReplacePageWithNewPage and _InvalidateExistingPage to help in
// handling Adv Page parsing
//
// 1     7/24/09 6:54p Presannar
//
// 5     5/28/09 11:49a Presannar
// Bug fixes and clean up
//
// 3     5/19/09 11:29a Presannar
// Removed check for Handle, while searching for existing Variable Info.
// This is a temporary fix. The issue needs to be analyzed further to
// check Handle also.
//
// 2     5/13/09 10:43a Presannar
// When EFI_IFR_DEFAULT_OP was encountered, its scope got ignored when
// skipping the opcode. Special handling of EFI_IFR_DEFAULT_OP case was
// removed to allow the default case to take care of it.
// Added File Header
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  			Parse.c
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------

#include "Minisetup.h"
#include "TseUefiHii.h"

#define PARSE_START_INDEX    1
//---------------------------------------------------------------------------

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: PageLink
//
// Description:
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// FormID					UINT16
// ParentPageID				UINT16
// PageNum					UINT16
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct PAGELINK
{
  UINT16 FormID;       // number from hpk
  UINT16 ParentPageID; // number from the tool
  UINT16 PageNum;      // number assigned by the tool
}PageLink;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: FormSetLinks
//
// Description:
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// PageCount				UINT16
// PageLink[20]				PageLink
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct FORMSETLINKS
{
  UINT16    PageCount;
  PageLink  PageLink[20];
}FormSetLinks;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: *PVAR_KEY_TABLE, VAR_KEY_TABLE
//
// Description:
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// VarId				UINT16
// Index				PageLink
// Handle				EFI_HII_HANDLE
// *Next				struct _VAR_KEY_TABLE
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _VAR_KEY_TABLE
{
  UINT32 VarId;
  UINT16 Index;
  EFI_HII_HANDLE Handle;
  struct _VAR_KEY_TABLE *Next;
}*PVAR_KEY_TABLE, VAR_KEY_TABLE;
//----------------------------------------------------------------------------
// MACRO DEFINITIONS
//----------------------------------------------------------------------------
#define 	START_EVAL_IF						0x8000
#define 	END_EVAL_IF							0x8001
#define 	DEFAULT_REFRESH_RATE 			0x01
#define 	DEFAULT_DATETIME_REFRESH 		0x05
#define	CONTROL_TYPE_MASK	 				0x0FFF
#define STANDARD_FORM_MAP_GUID { 0x3bd2f4ec, 0xe524, 0x46e4, 0xa9, 0xd8, 0x51, 0x1, 0x17, 0x42, 0x55, 0x62 }

#ifndef 	TSE_FOR_APTIO_4_50
#define 	EFI_HII_PACKAGE_FORMS         EFI_HII_PACKAGE_FORM
#include "tianohii.h"
#endif
//----------------------------------------------------------------------------
// VARIABLE DECLARATIONS
//----------------------------------------------------------------------------
static FormSetLinks	*FSetLinks;

VAR_KEY_TABLE VarKeyTable;

BOOLEAN 				ResetCondVars = TRUE;
BOOLEAN 				ResetVars = TRUE;
BOOLEAN 				Inconsistant = FALSE;
BOOLEAN 				NoSubmitIf = FALSE; // EIP: NO_SUBMIT_IF
BOOLEAN 				IsRecursive = FALSE;
UINT8 				DefaultStoreCount = 0;
UINT32 				CtrlVar = 0;
UINT32 				gnewCtrlVar = 0;
UINT32 				PageOffset;
UINT32 				PageVar = 0;
UINT32 				gRefreshIdCount = 0; //No. of controls with Refresh Id set
UINTN 				gDynamicPageCount=0;
VOID   *gConditionalOverFormPtr = NULL;//EIP-120418 
BOOLEAN updateformcondvars = TRUE;
BOOLEAN 				gConditionOverForm = FALSE;
//BOOLEAN 			IsRefreshIdSet = FALSE;
EFI_GUID 			RefreshEventGroupId;
REFRESH_ID_INFO 	*gRefreshIdInfo = NULL;
EFI_GUID StandardFormGuid = STANDARD_FORM_MAP_GUID;

//---------------------------------------------------------------------------
// EXTERN VARIABLES
//---------------------------------------------------------------------------
extern PAGE_ID_INFO *PageIdInfoPtr;
extern PAGE_ID_LIST *PageIdListPtr;
extern PAGE_INFO 		*FirstPage;
extern PAGE_INFO 		*NewPageInfo;
extern PAGE_INFO 		*PageInfoPtr;
extern PAGE_LIST 		*PageListPtr;
extern VARIABLE_LIST *VariableListPtr;
extern VARIABLE_INFO *VariableInfoPtr;

extern UINT32 			AllocatedFirstPageSize, FirstPageOffset;
extern UINT32 			ControlListSize, ControlListOffset;
extern UINT32 			PageIdInfoSize, PageIdInfoOffset;
extern UINT32 			PageIdListSize, PageIdListOffset;
extern UINT32 			PageInfoSize, PageInfoOffset;
extern UINT32 			PageListSize, PageListOffset;
extern UINT32 			VariableListSize, VariableListOffset;
extern UINT32 			VariableInfoSize, VariableInfoOffset;
extern UINTN 			TotalRootPages;
extern SETUP_LINK 	*gSetupData ;
extern VOID 			**gSfHandles;
extern EFI_GUID 		*gGuidDump;		//EIP64253 offline vfr pages hided
extern UINTN    		gGuidDumpCount;
//---------------------------------------------------------------------------
// EXTERN FUNCTIONS
//---------------------------------------------------------------------------
extern BOOLEAN IsGroupDynamicPages();
extern BOOLEAN IsOrphanPagesAsRootPage();

extern EFI_STATUS DebugShowControlInfo(UINT32 formID, VOID *passedCtrlInfo) ;
extern VOID DebugShowPageInfo(UINT32 formID, VOID *passedPageInfo) ;
extern VOID ResetExpressionStack (  VOID  );
extern EFI_STATUS PushExpression (IN EFI_HII_VALUE  *Value);
extern EFI_STATUS PopExpression (IN EFI_HII_VALUE  *Value);
extern INTN CompareHiiValue (IN  EFI_HII_VALUE   *Value1,IN  EFI_HII_VALUE   *Value2,IN  EFI_HII_HANDLE  HiiHandle OPTIONAL);
extern EFI_STATUS _GetValueFromQuestionId(UINT16 QuestionId, UINT16 PageId, EFI_HII_VALUE **Value);
extern EFI_STATUS VarGetValue( UINT32 variable, UINT32 offset, UINTN size, VOID *buffer );

extern VOID *gFirstPageRef;
extern UINT32 GetUefiSpecVersion (VOID);
extern BOOLEAN ShowClassGuidFormsets (TSE_EFI_IFR_FORM_SET *SetupFormSet );//EIP-139099 
extern BOOLEAN HideDynamicFormsets (EFI_GUID *FormSetGuid );//EIP-95647 
//---------------------------------------------------------------------------
// FUNCTION DECLARATIONS
//---------------------------------------------------------------------------
EFI_STATUS 	_AddVariable(UINT8 *IFRData, EFI_HII_HANDLE Handle);
EFI_STATUS 	_InitFormsetLinks(char *buff, UINTN InitFormNum);
EFI_STATUS 	_AdvAddPageToList(PAGE_INFO *NewPageInfo, UINT32 PageSize);
EFI_STATUS 	_ReplacePageWithNewPage(PAGE_INFO *OldPageInfo, PAGE_INFO *NewPageInfo, UINT32 PageSize);
EFI_STATUS 	_InvalidateExistingPage(PAGE_INFO *OldPageInfo, PAGE_INFO *NewPageInfo);
VOID 			RefreshGroupOnCallBack(EFI_EVENT Event, VOID *Context);
UINT8 		_IsVarGuidPresent(EFI_GUID *VarGuid, int *Index);
UINT16 		_GetPageIdIndex(EFI_GUID *FormGuid, UINT16 FormClass, UINT16 FormSubClass);
UINT16 		_GetPageParent(int PageNum);
UINT32 		_AddFormSetVariable(EFI_GUID *VarGuid);
UINT32 		_AdvAddControlToList(CONTROL_INFO *ControlInfo, UINT32 ControlSize);
UINT32 		_GetVarNumFromVarID(UINT32 ID, EFI_HII_HANDLE Handle, void *);
UINTN 		_AddHpkControls(EFI_HII_HANDLE Handle, UINT8 *buff,UINTN Size, PAGE_INFO **NewPageInfo, UINT32 *AllocatedPageSize, UINT32 *PageOffset);
UINTN 		_GetSubFormCount(UINT8 *buff);
UINT16 		_GetQuestionToken(UINT8 *ifrData) ;
VOID 			_CleanVarKeyTable();
EFI_STATUS 	CreateEventforIFR (CONTROL_INFO *control_Info );//EIP-105468



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _AddFormSetVariable
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 _AddFormSetVariable(EFI_GUID * VarGuid)
{
	VARIABLE_INFO Variable;
	UINT32 i;

	MemSet(&Variable, sizeof(Variable), 0);
    MemCopy((&Variable.VariableGuid),VarGuid,sizeof(EFI_GUID));
    Variable.VariableAttributes = 0x7; // BT+RT+NV
	EfiStrCpy(Variable.VariableName,L"Setup");

	i = VariableListPtr->VariableCount;
	AddVariableToList(&Variable);

	return i;
}

//----------------------------------------------------------------------------
// Procedure:    _DisplayErrorMessage
//
// Description: Function to display Error message when TSE supported limit exceeds
//
//----------------------------------------------------------------------------

EFI_STATUS _DisplayErrorMessage(CHAR16 *Temp)
{
	EFI_EVENT Event;
	EFI_STATUS status = EFI_SUCCESS;;	
	status = PostManagerDisplayInfoBox(L" Unrecoverable Error",Temp,20,&Event);
	if(status)
	{		
		gST->ConOut->OutputString(gST->ConOut,Temp);		
	}
	return status;
}

//----------------------------------------------------------------------------
// Procedure:    _AddVariable
//
// Description:
//----------------------------------------------------------------------------
BOOLEAN VariableHandleSuppressed (EFI_GUID *VariableGuid, CHAR16	*VariableName);
EFI_STATUS _AddVariable(UINT8 *IFRData, EFI_HII_HANDLE Handle)
{
	EFI_GUID *guid=NULL;
	EFI_STATUS status = EFI_SUCCESS;
	VARIABLE_INFO *variable=NULL;
	VARIABLE_INFO newVariable;
	PVAR_KEY_TABLE pVarTable;

	EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER*)IFRData;
	EFI_IFR_VARSTORE *varstore=NULL;
	AMI_EFI_IFR_VARSTORE_EFI *efivarstore;
	EFI_IFR_VARSTORE_NAME_VALUE *nameValuevarstore;

	char *str2;
	CHAR16 *varNamePtr;
	UINT16 i;
	UINT16 varId = 0;
	UINT16 varName[40];
	UINT16 varstoreSize = 0;
	UINT32 attributes = 0;
	UINT32 extAttributes = 0;
	UINTN varfound = 0;
    BOOLEAN bGreaterUEFIVersion = FALSE;

    SETUP_DEBUG_UEFI ( "\n[TSE] Entering _AddVariable()\n" );

	switch(opHeader->OpCode)
	{
	case EFI_IFR_VARSTORE_OP:
		varstore = (EFI_IFR_VARSTORE*)IFRData;
		guid = &(varstore->Guid);
		varId = varstore->VarStoreId;
		varstoreSize = varstore->Size;
		attributes |= 0;
		extAttributes |= VARIABLE_ATTRIBUTE_VARSTORE;
		str2 = (char*)varstore->Name;

		//Convert to unicode string
		MemSet(varName, sizeof(varName), 0);
		i = 0;
		for(varNamePtr = varName; *str2; *varNamePtr = *str2, str2++, varNamePtr++)
			;
		break;
	case EFI_IFR_VARSTORE_EFI_OP:
		efivarstore = (AMI_EFI_IFR_VARSTORE_EFI*)IFRData;
		guid = &(efivarstore->Guid);
		varId = efivarstore->VarStoreId;
		attributes |= efivarstore->Attributes;
		extAttributes |= VARIABLE_ATTRIBUTE_EFI_VARSTORE;
        if ((GetUefiSpecVersion()) > 0x2001E) //If UEFI spec version is greater than 2.3 then store the Name and size from the opcode      
        {
            bGreaterUEFIVersion = TRUE; //set it to True for version great than 2.3
            str2 = (char*)efivarstore->Name; //name of the opcode
		    //Convert to unicode string
		    MemSet(varName, sizeof(varName), 0);
		    i = 0;
		    for(varNamePtr = varName; *str2; *varNamePtr = *str2, str2++, varNamePtr++)
			    ;

            varstoreSize = efivarstore->Size; //size of the varstore
        }
		break;
	case EFI_IFR_VARSTORE_NAME_VALUE_OP:
		nameValuevarstore = (EFI_IFR_VARSTORE_NAME_VALUE*)IFRData;
		guid = &(nameValuevarstore->Guid);
		varId = nameValuevarstore->VarStoreId;
		EfiStrCpy (varName, L"");
		attributes |= 0;
		extAttributes |= VARIABLE_ATTRIBUTE_NAMEVALUE;
		break;
	default:
		break;
	}

	// check that the variable is not already in the list
	for(i=0; i < VariableListPtr->VariableCount; i++)
	{
		variable = (VARIABLE_INFO*)((UINT8 *)VariableInfoPtr + VariableListPtr->VariableList[i]);
		if( EfiCompareGuid(guid, &(variable->VariableGuid)) )//Compare Guid
		{
			switch(opHeader->OpCode)
			{
			case EFI_IFR_VARSTORE_OP:
				if((EfiStrCmp(varName, variable->VariableName) ==0))
				{
					if ((Handle == variable->VariableHandle) || VariableHandleSuppressed (guid, varName))
                    {
						varfound=1;
                        break;
                    }

					// Aptio SETUP Patch. refer EIP 39861
					// In aptio If it Setup Variable all the forms refers same varstore.
                    if((i==0) || UefiIsEfiVariable(i, variable))
                    {
						varfound=1;
                        break;
                    }

                   if(variable->VariableHandle == NULL)
                    {
                        // if Variable Handle is zero, then it added from OFFline parsing and we need use this
                        // Entry if the size also matchs.
                        if(varstore->Size == variable->VariableSize)
                        {
                            variable->VariableHandle = Handle;
                            varfound=1;
                            break;
                        }
                    }

				}
				break;
			case EFI_IFR_VARSTORE_EFI_OP:
        
                if (bGreaterUEFIVersion) //If UEFI spec version is greater than 2.3, then use the name to find the variable
                {
                    if((EfiStrCmp(varName, variable->VariableName) ==0))
				    {
					    if ((Handle == variable->VariableHandle) || VariableHandleSuppressed (guid, varName))
                        {
						    varfound=1;
                            break;
                        }

					    // Aptio SETUP Patch. refer EIP 39861
					    // In aptio If it Setup Variable all the forms refers same varstore.
                        if((i==0) || UefiIsEfiVariable(i, variable))
                        {
						    varfound=1;
                            break;
                        }

                       if(variable->VariableHandle == NULL)
                        {
                            // if Variable Handle is zero, then it added from OFFline parsing and we need use this
                            // Entry if the size also matchs.
                            if(efivarstore->Size == variable->VariableSize)
                            {
                                variable->VariableHandle = Handle;
                                varfound=1;
                                break;
                            }
                        }

				    }
                }
                else
                {
                    if((variable->ExtendedAttibutes & VARIABLE_ATTRIBUTE_EFI_VARSTORE) == VARIABLE_ATTRIBUTE_EFI_VARSTORE &&
					    variable->VariableAttributes == attributes)
				    {
					    varfound = 1;
				    }
                }
				break;
			case EFI_IFR_VARSTORE_NAME_VALUE_OP:
				varfound = 1;
				break;
			}
			if(varfound)
			{
				break;
			}
		}
	}

	if(!varfound)
	{
		MemSet(&newVariable, sizeof(VARIABLE_INFO), 0);
		newVariable.VariableID = varId;
		MemCopy((&newVariable.VariableGuid),guid,sizeof(EFI_GUID));
		newVariable.VariableAttributes = attributes;
		newVariable.ExtendedAttibutes = extAttributes;
		newVariable.VariableHandle = Handle;

	    if(opHeader->OpCode == EFI_IFR_VARSTORE_OP)
	    {
	      EfiStrCpy(newVariable.VariableName, varName);
	      newVariable.VariableSize = varstoreSize;
	    }
        else if ((EFI_IFR_VARSTORE_EFI_OP == opHeader->OpCode) && (bGreaterUEFIVersion)) //Name is available in the opcode only if UEFI spec followed is
	    {                                                                                //greater than 2.3
	      EfiStrCpy(newVariable.VariableName, varName);
	      newVariable.VariableSize = varstoreSize;
	    }

		AddVariableToList(&newVariable);
	}else
	{
		variable->VariableID = varId;
		variable->VariableHandle = Handle;
		variable->ExtendedAttibutes = extAttributes;

	    if(opHeader->OpCode == EFI_IFR_VARSTORE_OP)
	    {
	      variable->VariableSize = varstoreSize;
	    }
		else if (EFI_IFR_VARSTORE_NAME_VALUE_OP == opHeader->OpCode)
		{
			EfiStrCpy (variable->VariableName, varName);
		}
        else if ((EFI_IFR_VARSTORE_EFI_OP == opHeader->OpCode) && (bGreaterUEFIVersion)) //Size is available in the opcode only if UEFI spec followed is
        {                                                                                //greater than 2.3
            variable->VariableSize = varstoreSize;
        }
	}

	pVarTable = &VarKeyTable;

	while(pVarTable->Next)
		pVarTable = pVarTable->Next;

	pVarTable->Next = EfiLibAllocateZeroPool(sizeof(VAR_KEY_TABLE));
	if(pVarTable->Next == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	pVarTable = pVarTable->Next;
	pVarTable->VarId = varId;
	pVarTable->Handle = Handle;
	pVarTable->Index = i;

DONE:
    SETUP_DEBUG_UEFI( "\n[TSE] Exiting _AddVariable(),  status = 0x%x \n" , status );
    
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _CleanVarKeyTable
//
// Description:  Clean VarKey Table
//
// Parameter:    None
//
// Return value: None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _CleanVarKeyTable()
{
	PVAR_KEY_TABLE pVarTable = VarKeyTable.Next;

	while(pVarTable)
	{
		VarKeyTable.Next = pVarTable->Next;
		MemFreePointer(&pVarTable);
		pVarTable = VarKeyTable.Next;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetControlKeyToken
//
// Description:  Get ControlKey Token
//
// Parameter:    None
//
// Return value: None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetControlKeyToken(UINT8 *IFRData)
{
	EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER*)IFRData;
	EFI_IFR_QUESTION_HEADER *question;
	UINT16 questionKey = 0;

	switch(opHeader->OpCode)
	{
	case EFI_IFR_ONE_OF_OP:			      // 0x05
	case EFI_IFR_CHECKBOX_OP:         // 0x06
	case EFI_IFR_NUMERIC_OP:          // 0x07
	case EFI_IFR_PASSWORD_OP:         // 0x08
	case EFI_IFR_ACTION_OP:           // 0x0C
	case EFI_IFR_RESET_BUTTON_OP:     // 0x0D
	case EFI_IFR_REF_OP:              // 0x0F
	case EFI_IFR_DATE_OP:             // 0x1A
	case EFI_IFR_TIME_OP:             // 0x1B
	case EFI_IFR_STRING_OP:           // 0x1C
	case EFI_IFR_ORDERED_LIST_OP:     // 0x23
		question = (EFI_IFR_QUESTION_HEADER*)((UINT8*)IFRData + sizeof(EFI_IFR_OP_HEADER));
		questionKey = question->QuestionId;
		break;
	case EFI_IFR_RULE_OP:             // 0x18
		questionKey = ((EFI_IFR_RULE*)((UINT8*)IFRData))->RuleId;
		break;
	default:
		break;
	}

	return questionKey;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetControlDevicePathId
//
// Description:  Get Control DevicePathId
//
// Parameter:
//
// Return value: UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetControlDevicePathId(UINT8 *IFRData)
{
	EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER*)IFRData;
	UINTN inScope = 0;
	UINTN i = 0;
	UINT16 devicePath = 0;
	BOOLEAN found = FALSE;

	if(opHeader->Scope)
	{
		do
		{
			switch(opHeader->OpCode)
			{
			case EFI_IFR_VARSTORE_DEVICE_OP:
				devicePath = ((EFI_IFR_VARSTORE_DEVICE*)((UINT8*)IFRData + i))->DevicePath;
				found = TRUE;
				break;
			case EFI_IFR_END_OP:
				inScope--;
				break;
			default:
				if(opHeader->Scope)
				{
					inScope++;
				}
			}
			i += opHeader->Length;
			opHeader = (EFI_IFR_OP_HEADER*)(IFRData + i);
		}while(inScope || found);
	}

	return devicePath;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    	GetDefaultValue
//
// Description:  	Get Default Value
//
// Input:			UINT8 Type
//	    			EFI_IFR_TYPE_VALUE *Value
//					UINT16 *Size - [IN/OUT] parameter - IN for the type
//							EFI_IFR_TYPE_BUFFER. For all other types, 
//							as OUT parameter
//					VOID *DefValue
//
// Output:			Void
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetDefaultValue(UINT8 Type, EFI_IFR_TYPE_VALUE *Value, UINT16 *Size, VOID *DefValue, UINT8 *TempData)
{
	UINT8 *Data = TempData;
	switch(Type)
	{
	case EFI_IFR_TYPE_NUM_SIZE_8:
		*Size = (UINT16)sizeof(UINT8);
		*(UINT8*)DefValue = Value->u8;
		break;
	case EFI_IFR_TYPE_NUM_SIZE_16:
    case EFI_IFR_TYPE_STRING:
		*Size = (UINT16)sizeof(UINT16);
		*(UINT16*)DefValue = Value->u16;
		break;
	case EFI_IFR_TYPE_NUM_SIZE_32:
		*Size = (UINT16)sizeof(UINT32);
		*(UINT32*)DefValue = Value->u32;
		break;
	case EFI_IFR_TYPE_NUM_SIZE_64:
		*Size = (UINT16)sizeof(UINT64);
		*(UINT64*)DefValue = Value->u64;
		break;
	case EFI_IFR_TYPE_DATE:
		*Size = sizeof(EFI_HII_DATE);
		MemCopy(DefValue, &(Value->date), sizeof(EFI_HII_DATE));
		break;
	case EFI_IFR_TYPE_TIME:
		*Size = sizeof(EFI_HII_TIME);
		MemCopy(DefValue, &(Value->time), sizeof(EFI_HII_TIME));
		break;
	case EFI_IFR_TYPE_BUFFER:
		// Size will be received as parameter
		MemCopy(DefValue, Value, *Size);
		break;
    case EFI_IFR_TYPE_REF:			//EIP109812, 107774
        // Size will be received as parameter
		MemCopy (DefValue, Value, *Size);
		break;
   case EFI_IFR_TYPE_BOOLEAN:
		*Size = 1;
      MemCopy(DefValue, &(Value->b), *Size);
      break;
	case EFI_IFR_TYPE_OTHER:
      {
         UINTN ScopeCount = 0;
         EFI_IFR_OP_HEADER *OpHeader = (EFI_IFR_OP_HEADER *)Data;
         EFI_IFR_DEFAULT *DefaultOp = NULL;
         *Size = 0;

         if (OpHeader->Scope)
         {
            ScopeCount ++;
            OpHeader = (EFI_IFR_OP_HEADER *)((UINT8 *)OpHeader + OpHeader->Length);
            if (OpHeader->Scope)
            {
               ScopeCount ++;
               if (EFI_IFR_VALUE_OP == OpHeader->OpCode)
               {
                  OpHeader = (EFI_IFR_OP_HEADER *)((UINT8 *)OpHeader + OpHeader->Length);
                  switch (OpHeader->OpCode)
                  {
                     case EFI_IFR_UINT8_OP:
                        *Size = (UINT16)sizeof (UINT8);
		                  *(UINT8 *)DefValue = *(UINT8 *)((UINT8 *)OpHeader + sizeof (EFI_IFR_OP_HEADER));
                        break;
                     case EFI_IFR_UINT16_OP:
                        *Size = (UINT16)sizeof (UINT16);
		                  *(UINT16 *)DefValue = *(UINT16 *)((UINT8 *)OpHeader + sizeof (EFI_IFR_OP_HEADER));
                        break;
                     case EFI_IFR_UINT32_OP:
                        *Size = (UINT16)sizeof (UINT32);
		                  *(UINT32 *)DefValue = *(UINT32 *)((UINT8 *)OpHeader + sizeof (EFI_IFR_OP_HEADER));
		                  break;
                     case EFI_IFR_UINT64_OP:
                        *Size = (UINT16)sizeof (UINT64);
		                  *(UINT64 *)DefValue = *(UINT64 *)((UINT8 *)OpHeader + sizeof (EFI_IFR_OP_HEADER));
		                  break;
                     default:
                        *Size = 0;
								break;
                  }
               }
            }
         }
         while (ScopeCount)
	      {
            OpHeader = (EFI_IFR_OP_HEADER *)((UINT8 *)OpHeader + OpHeader->Length);
            if (EFI_IFR_END_OP == OpHeader->OpCode)
            { 
               ScopeCount --;
            }
	      }
      }
      break;
	default:
		*Size = 0;
		*(UINT8*)DefValue = 0;
		break;
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetHelpToken
//
// Description:  Get Control Question Help Token
//
// Parameter:
//
// Return value: UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetHelpToken(UINT8 *ifrData)
{
	EFI_IFR_OP_HEADER *headerPtr = (EFI_IFR_OP_HEADER*)ifrData;
	UINT16 token = 0;

	switch ( headerPtr->OpCode )
	{
		case EFI_IFR_TEXT_OP:
			{
				EFI_IFR_TEXT *ptr = (EFI_IFR_TEXT*)headerPtr;
				token = ptr->Statement.Help;
			}
			break;
		case EFI_IFR_ORDERED_LIST_OP:
			{
				EFI_IFR_ORDERED_LIST *ptr = (EFI_IFR_ORDERED_LIST*)headerPtr;
				token = ptr->Question.Header.Help;
			}
			break;
		case EFI_IFR_ONE_OF_OP:
			{
				EFI_IFR_ONE_OF *ptr = (EFI_IFR_ONE_OF*)headerPtr;
				token = ptr->Question.Header.Help;
			}
			break;
		case EFI_IFR_CHECKBOX_OP:
			{
				EFI_IFR_CHECKBOX *ptr = (EFI_IFR_CHECKBOX*)headerPtr;
				token = ptr->Question.Header.Help;
			}
			break;
		case EFI_IFR_DATE_OP:
		case EFI_IFR_TIME_OP:
		case EFI_IFR_NUMERIC_OP:
			{
				EFI_IFR_NUMERIC *ptr = (EFI_IFR_NUMERIC*)headerPtr;
				token = ptr->Question.Header.Help;
			}
			break;
		case EFI_IFR_PASSWORD_OP:
			{
				EFI_IFR_PASSWORD *ptr = (EFI_IFR_PASSWORD*)headerPtr;
				token = ptr->Question.Header.Help;
			}
			break;
		case EFI_IFR_ACTION_OP:
			{
				EFI_IFR_ACTION *ptr = (EFI_IFR_ACTION*)headerPtr;
				token = ptr->Question.Header.Help;
			}
			break;
		case EFI_IFR_RESET_BUTTON_OP:
			{
				EFI_IFR_RESET_BUTTON *ptr = (EFI_IFR_RESET_BUTTON*)headerPtr;
#ifdef TSE_FOR_APTIO_4_50
				token = ptr->Statement.Help;
#else
				token = ptr->Question.Header.Help;
#endif
			}
		case EFI_IFR_REF_OP:
			{
				EFI_IFR_REF *ptr = (EFI_IFR_REF*)headerPtr;
				token = ptr->Question.Header.Help;
			}
			break;
		case EFI_IFR_STRING_OP:
			{
				EFI_IFR_STRING *ptr = (EFI_IFR_STRING*)headerPtr;
				token = ptr->Question.Header.Help;
			}
			break;
		default:
			break;
	}

	return token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetPageIdIndex
//
// Description:  Get Page ID index
//
// Parameter:
//
// Return value: UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetPageIdIndex(EFI_GUID * FormGuid, UINT16 FormClass, UINT16 FormSubClass)
{
	UINT16 i;
	PAGE_ID_INFO *pageId;

	if(PageIdListPtr == NULL)
	{
		PageIdListSize = 128;
		PageIdListPtr = (PAGE_ID_LIST *)EfiLibAllocateZeroPool(128);
		PageIdListOffset = sizeof(UINT32); // Points to first Offset of PageIdList
	}

	//search if this combination exists
	for(i = 0; i < PageIdListPtr->PageIdCount ; i++)
	{
		pageId = (PAGE_ID_INFO *) ((UINT8 *)PageIdInfoPtr + PageIdListPtr->PageIdList[i]);
		if( EfiCompareGuid(FormGuid,&(pageId->PageGuid)) )//Compare Guid
		{
			if(FormClass == pageId->PageClass)//Compare class
			{
				if(FormSubClass == pageId->PageSubClass)//Compare SubClass
				{
					break; //found entry
				}
			}
		}
	}

	if(i >= PageIdListPtr->PageIdCount)
	{
		PAGE_ID_INFO NewPageId;

		MemCopy(&(NewPageId.PageGuid),FormGuid,sizeof(EFI_GUID));
		NewPageId.PageClass = FormClass;
		NewPageId.PageSubClass = FormSubClass;

		i = (UINT16)PageIdListPtr->PageIdCount;
		AddPageIdToList(&NewPageId);
	}

	return i;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetPageNumFromFormID
//
// Description:  Get Page Id from Form Id
//
// Parameter:
//
// Return value: UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetPageNumFromFormID(UINTN FormID)
{
	UINTN i=0;

	do{
		if(FSetLinks->PageLink[i].FormID == FormID)
		{
			return (FSetLinks->PageLink[i].PageNum);
			break;
		}
	}while(i++ < FSetLinks->PageCount);

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetPageParent
//
// Description: Get Parent Page PageID
//
// Parameter:
//
// Return value: UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetPageParent(int PageNum)
{
	UINT16 i=0;

	do{
		if(FSetLinks->PageLink[i].PageNum == PageNum  )
		{
			return (FSetLinks->PageLink[i].ParentPageID );
			break;
		}
	}while( i++ < FSetLinks->PageCount  );

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetQuestionToken
//
// Description: Get Control Question Prompt
//
// Parameter:
//
// Return value: UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _GetQuestionToken(UINT8 *ifrData)
{
	EFI_IFR_OP_HEADER *headerPtr = (EFI_IFR_OP_HEADER*)ifrData;
	UINT16 token = 0;

	switch ( headerPtr->OpCode )
	{
		case EFI_IFR_TEXT_OP:
			{
				EFI_IFR_TEXT *ptr = (EFI_IFR_TEXT*)headerPtr;
				token = ptr->Statement.Prompt;
			}
			break;
		case EFI_IFR_ONE_OF_OP:
			{
				EFI_IFR_ONE_OF *ptr = (EFI_IFR_ONE_OF*)headerPtr;
				token = ptr->Question.Header.Prompt;
			}
			break;
		case EFI_IFR_CHECKBOX_OP:
			{
				EFI_IFR_CHECKBOX *ptr = (EFI_IFR_CHECKBOX*)headerPtr;
				token = ptr->Question.Header.Prompt;
			}
			break;
		case EFI_IFR_DATE_OP:
		case EFI_IFR_TIME_OP:
		case EFI_IFR_NUMERIC_OP:
			{
				EFI_IFR_NUMERIC *ptr = (EFI_IFR_NUMERIC*)headerPtr;
				token = ptr->Question.Header.Prompt;
			}
			break;
  		case EFI_IFR_ORDERED_LIST_OP:
		    {
		      EFI_IFR_ORDERED_LIST *ptr = (EFI_IFR_ORDERED_LIST *)headerPtr;
		      token = ptr->Question.Header.Prompt;
		    }
		    break;
		case EFI_IFR_PASSWORD_OP:
			{
				EFI_IFR_PASSWORD *ptr = (EFI_IFR_PASSWORD*)headerPtr;
				token = ptr->Question.Header.Prompt;
			}
			break;
		case EFI_IFR_ACTION_OP:
			{
				EFI_IFR_ACTION *ptr = (EFI_IFR_ACTION*)headerPtr;
				token = ptr->Question.Header.Prompt;
			}
			break;
		case EFI_IFR_RESET_BUTTON_OP:
			{
				EFI_IFR_RESET_BUTTON *ptr = (EFI_IFR_RESET_BUTTON*)headerPtr;
#ifdef TSE_FOR_APTIO_4_50
				token = ptr->Statement.Prompt;
#else
				token = ptr->Question.Header.Prompt;
#endif
			}
			break;
		case EFI_IFR_REF_OP:
			{
				EFI_IFR_REF *ptr = (EFI_IFR_REF*)headerPtr;
				token = ptr->Question.Header.Prompt;
			}
			break;
		case EFI_IFR_STRING_OP:
			{
				EFI_IFR_STRING *ptr = (EFI_IFR_STRING*)headerPtr;
				token = ptr->Question.Header.Prompt;
			}
			break;
		case EFI_IFR_SUBTITLE_OP:
			{
				EFI_IFR_SUBTITLE *ptr = (EFI_IFR_SUBTITLE*)headerPtr;
				token = ptr->Statement.Prompt;
			}
			break;
		default:
			break;
	}

	return token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetSubFormCount
//
// Description:  Count the subform and Ref inside the formset
//
// Parameter:
//
// Return value: UINTN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _GetSubFormCount(UINT8 *buff)
{
	UINTN *tmpFormIDBuf;
	UINTN MaxPagecount=100;
	UINTN PageCount= 0;
	UINTN i=0, j=0, found =0;
    INTN ScopeCount = 0;
	EFI_IFR_OP_HEADER *Header;

	tmpFormIDBuf = (UINTN*)EfiLibAllocateZeroPool(MaxPagecount*sizeof(UINTN));
	//go thru the forms and get the links, creating the lookup table also
	do
	{
		Header = (EFI_IFR_OP_HEADER*)(buff+i);
		switch(Header->OpCode )
		{
    case EFI_IFR_FORM_OP: // find parent in lookup table and then the parent pageNum  to link
				// Add page if is not in lookup table already
				found=0;
				j=0;

				while( (found==0) && ( j < PageCount ) ){
					if(tmpFormIDBuf[j] == ((EFI_IFR_FORM*)Header)->FormId  )
					{
						found =1;
						break;
					}
					j++;
				}

				if(!found)
				{
					// pages in the root(no parent)
					tmpFormIDBuf[PageCount] = ((EFI_IFR_FORM*)Header)->FormId ;
					PageCount++;
				}

		         break;
     case EFI_IFR_FORM_MAP_OP: // find parent in lookup table and then the parent pageNum  to link
				// Add page if is not in lookup table already
                found=0;
				j=0;

				while((found==0) && (j < PageCount))
                {
					if(tmpFormIDBuf[j] == ((AMI_EFI_IFR_FORM_MAP *)Header)->FormId)
					{
						found =1;
					}
					j++;
				}

				if(!found)
				{
					// pages in the root(no parent)
					tmpFormIDBuf[PageCount] = ((AMI_EFI_IFR_FORM_MAP *)Header)->FormId ;
					PageCount++;
				}
		    break;

	  case EFI_IFR_REF_OP: // add to lookup table adding the PageID and ParentPageID
                // Add page if is not in lookup table already
				found=0;
				j=0;

				while((found==0) && (j < PageCount))
        {
					if(tmpFormIDBuf[j] == ((EFI_IFR_REF*)Header)->FormId)
					{
						found =1;
					}
					j++;
				}

				if(!found)
				{
					// pages in the root(no parent)
					tmpFormIDBuf[PageCount] = ((EFI_IFR_REF*)Header)->FormId ;
					PageCount++;
				}
		    break;
    case EFI_IFR_END_OP:
        ScopeCount--;
        break;
		default:
	      break;
		}
    if(Header->Scope)
    {
      ScopeCount++;
    }
		// If the Buffer is not enough the reallocate more
		if(PageCount >= MaxPagecount)
		{
			UINTN *tmpBuf;
			MaxPagecount +=50;
			tmpBuf = (UINTN*)EfiLibAllocateZeroPool(MaxPagecount*sizeof(UINTN));
			MemCopy(tmpBuf,tmpFormIDBuf,sizeof(UINTN)*PageCount);
			MemFreePointer(&tmpFormIDBuf);
			tmpFormIDBuf = tmpBuf;
		}
    i+=Header->Length;
	}while(ScopeCount != 0);

	MemFreePointer(&tmpFormIDBuf);
	return PageCount;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetVarNumFromVarID
//
// Description:  Get Variable Index
//
// Parameter:
//
// Return value: UINT32
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 _GetVarNumFromVarID (UINT32 ID, EFI_HII_HANDLE Handle, void *IfrData)
{
    PVAR_KEY_TABLE		pVarTable = VarKeyTable.Next;
    UINT16				*varString;
    UINT16              Width = 0;
    VARIABLE_INFO		*Variable = NULL;
    VARIABLE_INFO	    newVariable;
    EFI_STATUS		    Status = EFI_SUCCESS;
    EFI_IFR_QUESTION_HEADER *QuestionHeader = NULL;
    
    while(pVarTable)
    {
        if ((pVarTable->VarId == ID) && (pVarTable->Handle == Handle))
        {
        Variable = (VARIABLE_INFO*)((UINT8 *)VariableInfoPtr + VariableListPtr->VariableList [pVarTable->Index]);
            if (Variable)
            {
                if (VARIABLE_ATTRIBUTE_NAMEVALUE == (Variable->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE))
                {
                    QuestionHeader = (EFI_IFR_QUESTION_HEADER *)((UINT8 *)IfrData + sizeof (EFI_IFR_OP_HEADER));
                    varString = HiiGetString (Variable->VariableHandle, QuestionHeader->VarStoreInfo.VarName);
                    Width = UefiGetWidth (IfrData);
                    if (varString)
                    {
                        if (0 == (EfiStrLen (Variable->VariableName)))
                        {
                            Variable->VariableSize = Width;
                            EfiStrCpy (Variable->VariableName, varString);
                        }
                        else
                        {
                            MemSet (&newVariable, sizeof (VARIABLE_INFO), 0);
                            EfiCopyMem (&newVariable, Variable, sizeof (VARIABLE_INFO));
                            newVariable.VariableSize = Width;
                            EfiStrCpy (newVariable.VariableName, varString);
                            Status = AddVariableToList (&newVariable);
                            if (!EFI_ERROR (Status))
                            {
                                return gnewCtrlVar;
                            }		
                        }	
                    }
                }	
                return (pVarTable->Index);
            }
        }
        pVarTable = pVarTable->Next;
    }
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _InitFormsetLinks
//
// Description:  Init Formset Links
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _InitFormsetLinks(char *buff,UINTN InitFormNum)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_IFR_OP_HEADER *Header;

	UINTN j=0, found =0, InitForm = InitFormNum;
	UINTN ScopeCount = 0, count = 0;
	UINT16 RootPageinFormSet=0,RootPageID=0;
    UINT16 *_PageIdList = (UINT16 *)NULL, _PageIdListCount = 0;
	EFI_FORM_ID tempFormID = 0;

    SETUP_DEBUG_UEFI( "\n[TSE] Entering _InitFormsetLinks()\n");
	

	// allocate memory for data
	if(FSetLinks != NULL)
		MemFreePointer(&FSetLinks);

	count = _GetSubFormCount(buff);
	FSetLinks = (FormSetLinks*)EfiLibAllocateZeroPool(sizeof(FormSetLinks) + count * sizeof(PageLink));
	if(FSetLinks == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	//go thru the forms and get the links, creating the lookup table also
	do
	{
		Header = (EFI_IFR_OP_HEADER*)(buff);
		switch(Header->OpCode )
		{
            case EFI_IFR_FORM_OP:
				// find parent in lookup table and then the parent pageNum  to link
				// Add page if is not in lookup table already
				found = 0;
				j = 0;

				while( (found == 0) && ( j < FSetLinks->PageCount ) )
				{
					if(FSetLinks->PageLink[j].FormID == ((EFI_IFR_FORM*)Header)->FormId  )
					{
                        FSetLinks->PageLink[j].PageNum = (UINT16)InitForm++;
						found = 1;
						break;
					}
					j++;
				}

				if(found == 0)
				{
					if(!RootPageinFormSet)
						RootPageinFormSet = ((EFI_IFR_FORM*)Header)->FormId;
					// pages in the root(no parent)
					FSetLinks->PageLink[FSetLinks->PageCount].FormID = ((EFI_IFR_FORM*)Header)->FormId ;

                    if(IsOrphanPagesAsRootPage()) 
                    {
    					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = 0;
                    }
                    else
                    {
                        if(RootPageinFormSet == ((EFI_IFR_FORM*)Header)->FormId)
        					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = 0;
                        else
        					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = FSetLinks->PageLink[0].PageNum;
                    }

					FSetLinks->PageLink[FSetLinks->PageCount].PageNum = (UINT16)InitForm++;
					FSetLinks->PageCount++;
				}

				if(Header->Scope)
				{
					ScopeCount++;
				}

		         break;
            case EFI_IFR_FORM_MAP_OP: 
				// find parent in lookup table and then the parent pageNum  to link
				// Add page if is not in lookup table already
                found = 0;
				j = 0;

				while( (found == 0) && ( j < FSetLinks->PageCount ) )
				{
					if(FSetLinks->PageLink[j].FormID == ((AMI_EFI_IFR_FORM_MAP *)Header)->FormId  )
					{
                        FSetLinks->PageLink[j].PageNum = (UINT16)InitForm++;
                        found = 1;
						break;
					}
					j++;
				}

				if(found == 0)
				{
					if(!RootPageinFormSet)
						RootPageinFormSet = ((AMI_EFI_IFR_FORM_MAP *)Header)->FormId;
					// pages in the root(no parent)
					FSetLinks->PageLink[FSetLinks->PageCount].FormID = ((AMI_EFI_IFR_FORM_MAP *)Header)->FormId ;

                    if(IsOrphanPagesAsRootPage()) 
                    {
    					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = 0;
                    }
                    else
                    {
                        if(RootPageinFormSet == ((AMI_EFI_IFR_FORM_MAP *)Header)->FormId)
        					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = 0;
                        else
        					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = FSetLinks->PageLink[0].PageNum;
                    }

					FSetLinks->PageLink[FSetLinks->PageCount].PageNum = (UINT16)InitForm++;
					FSetLinks->PageCount++;
				}

				if(Header->Scope)
				{
					ScopeCount++;
				}

			case EFI_IFR_REF_OP:
				// add to lookup table adding the PageID and ParentPageID
                // Add page if is not in lookup table already
				found = 0;
				j = 0;

				while( (found == 0) && ( j < FSetLinks->PageCount ) )
				{
					tempFormID = ((EFI_IFR_REF*)Header)->FormId;
					if(tempFormID == 0) //If the EFI_IFR_REFX FormId is invalid
					{
						tempFormID = (UINT16)InitForm; // Set the check FormId to the current FormId
					}

					if(FSetLinks->PageLink[j].FormID == tempFormID)
					{
						if(RootPageinFormSet != FSetLinks->PageLink[j].FormID)
						{
							if(FSetLinks->PageLink[j].PageNum != (UINT16)InitForm-1) // Parent of the Page can't be same page id.
							{
								FSetLinks->PageLink[j].ParentPageID = (UINT16)InitForm-1;
							}
						}
						found = 1;
					}
					j++;
				}

				if(found == 0)
				{
					// sub pages
					if(((EFI_IFR_FORM*)Header)->FormId) //If the the FormId is valid, store it
					{
						FSetLinks->PageLink[FSetLinks->PageCount].FormID = ((EFI_IFR_REF*)Header)->FormId ;
					} else{ //Else store the current FormId
						FSetLinks->PageLink[FSetLinks->PageCount].FormID = (UINT16)InitForm;
					}
					FSetLinks->PageLink[FSetLinks->PageCount].ParentPageID = (UINT16)InitForm-1;
					FSetLinks->PageLink[FSetLinks->PageCount].PageNum = 0;
					FSetLinks->PageCount++;
				}
		       break;
			case EFI_IFR_END_OP:
				ScopeCount--;
				break;
			default:
				if(Header->Scope)
				{
					ScopeCount++;
				}
		      break;

		}
       buff += Header->Length;
	}while(ScopeCount != 0);

	// Fix to find the Circulr Links.
	for(j=0;j<FSetLinks->PageCount;j++)
	{
		if(FSetLinks->PageLink[j].FormID == RootPageinFormSet)
		{
			RootPageID = FSetLinks->PageLink[j].PageNum;
			break;
		}
	}
	
	_PageIdList = EfiLibAllocateZeroPool(FSetLinks->PageCount*sizeof(UINT16));
	for(j=0;j<FSetLinks->PageCount;j++)
	{
		UINT16 k,CurrentPageId,m,n;
		BOOLEAN IsCircular=TRUE; // Default
		
		if(FSetLinks->PageLink[j].ParentPageID == 0)
			continue; // Rootpage.
		
		CurrentPageId = FSetLinks->PageLink[j].PageNum;

		MemSet(_PageIdList, FSetLinks->PageCount*sizeof(UINT16), 0);
		_PageIdListCount = 0;
		
		k=0;
		while(k<FSetLinks->PageCount)
		{
			if(FSetLinks->PageLink[k].PageNum == CurrentPageId)
			{
				_PageIdList[_PageIdListCount++] = CurrentPageId;
				CurrentPageId = FSetLinks->PageLink[k].ParentPageID;
				
				if(CurrentPageId == RootPageID)
					break; // Root found.
				
				// Check if it circular.
				for(m=0;(m<_PageIdListCount)&& IsCircular ;m++)
				{
					if(_PageIdList[m] == CurrentPageId) // Circular pages.. Fix the PageIdList[0]
					{
						for(n=0;n<FSetLinks->PageCount;n++)
						{
							if(FSetLinks->PageLink[n].PageNum == _PageIdList[0])
							{
									FSetLinks->PageLink[n].ParentPageID = RootPageID;
									IsCircular = FALSE;
									break;
							}
						}
					}
				}
				if(!IsCircular)
					break;

				k=0;
				continue;
			}
			k++;
		}

	}
	MemFreePointer(&_PageIdList);

DONE:

    SETUP_DEBUG_UEFI( "\n[TSE] Exiting _InitFormsetLinks(),  status = 0x%x \n" , status );

	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _IsVarGuidPresent
//
// Description:  Check if the Variable Guid is already defined
//
// Parameter:
//
// Return value: UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 _IsVarGuidPresent(EFI_GUID * VarGuid, int * Index)
{
	UINT32 i=0;
	VARIABLE_INFO *Variable;

	for(i=0; i < VariableListPtr->VariableCount; i++)
	{
		Variable = (VARIABLE_INFO *) ((UINT8 *)VariableInfoPtr + VariableListPtr->VariableList[i]);
		if( EfiCompareGuid(VarGuid,&(Variable->VariableGuid)) )//Compare Guid
			if( (EfiStrCmp(L"Setup",Variable->VariableName) ==0)  ||
				(EfiStrCmp(L"setup",Variable->VariableName) ==0 ))
			{
				*Index = i;
				return TRUE;
			}
	}
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _UpdateDefaults
//
// Description:  Get Control Defaults
//
// Parameter:    EFI_HII_HANDLE Handle, 
//               VOID *Data, 
//               UINT16 *size, 
//               VOID *Failsafe, 
//               VOID *Optimal, 
//               DEFAULT_VALUE **defaultValue, 
//               struct _CONTROL_FLAGS *Control_Flags, 
//               VOID *ConditionalPtr
//
// Return value: UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 _UpdateDefaults( EFI_HII_HANDLE Handle, VOID *Data, UINT16 *size, VOID **FailsafeValue, VOID **OptimalValue, DEFAULT_VALUE **defaultValue, struct _CONTROL_FLAGS *Control_Flags, VOID *ConditionalPtr)
{

	EFI_IFR_OP_HEADER *OpHeader;
	EFI_QUESTION_ID QuestionId = 0;

    EFI_IFR_ONE_OF *OneOfOp = (EFI_IFR_ONE_OF *)NULL;
    EFI_IFR_ONE_OF_OPTION *OneOfOption = (EFI_IFR_ONE_OF_OPTION *)NULL;
    EFI_IFR_CHECKBOX *CheckBoxOp = (EFI_IFR_CHECKBOX *)NULL;
    EFI_IFR_NUMERIC *NumericOp = (EFI_IFR_NUMERIC *)NULL;
    EFI_IFR_ORDERED_LIST *OrderedListOp = (EFI_IFR_ORDERED_LIST *)NULL;
    EFI_IFR_PASSWORD *PasswordOp = (EFI_IFR_PASSWORD *)NULL;
    EFI_IFR_ACTION *ActionOp = (EFI_IFR_ACTION *)NULL;
    EFI_IFR_STRING *StringOp = (EFI_IFR_STRING *)NULL;
    EFI_IFR_DEFAULT *DefaultOp = (EFI_IFR_DEFAULT *)NULL;
    EFI_IFR_REF *RefOp = (EFI_IFR_REF *)NULL;
    EFI_IFR_DATE *DateOp = (EFI_IFR_DATE *)NULL;
    EFI_IFR_TIME *TimeOp = (EFI_IFR_TIME *)NULL;
	EFI_STRING_ID varName = 0;
    VARIABLE_INFO *varInfo = (VARIABLE_INFO *)NULL;

	UINT8 Flags=0, questionFlags = 0;
	UINTN ScopeCount = 0;
    UINT16 *varString = (UINT16 *)NULL;
	int i=0;
	UINT8 defaultCount = 0;//EIP: 56124 Declaration to count the defaults of the control 	
    VOID   *Failsafe = NULL;
    VOID   *Optimal = NULL;
    UINT16 RecommandedDefaultSize=0;
    UINT8 DefaultSize = 0;

    SETUP_DEBUG_UEFI( "\n[TSE] Entering _UpdateDefaults()\n");
    //  Assume the default values are 64 bits or less. If the values are larger,
    //  we will re-allocate more space.
    Failsafe = EfiLibAllocateZeroPool (sizeof (UINT64));
	if(NULL == Failsafe)
	{		 
		return 0;
	}
    Optimal = EfiLibAllocateZeroPool (sizeof (UINT64));
	if(NULL == Optimal)
	{		
		MemFreePointer (Failsafe);        
		return 0;
	}

    do
	{
		OpHeader = (EFI_IFR_OP_HEADER*)((UINT8*)Data + i);
		switch(OpHeader->OpCode)
		{
		// ------ text --------------
		case EFI_IFR_TEXT_OP: //(only interactive)
			break;

		// ------ ref --------------
		case EFI_IFR_REF_OP: // uses only interactive , but to signal that a key has to be passed
							 // back to a consumer (this behavior is not defined in TSE as of 5/20/05)
			RefOp = (EFI_IFR_REF*)((UINT8*)Data + i);

			questionFlags = RefOp->Question.Flags;
			break;

		// ------ one of --------------
		case EFI_IFR_ONE_OF_OP:
			OneOfOp = (EFI_IFR_ONE_OF*)((UINT8*)Data + i);

			QuestionId = OneOfOp->Question.VarStoreInfo.VarOffset;
			CtrlVar = _GetVarNumFromVarID(OneOfOp->Question.VarStoreId, Handle, (void *)OneOfOp);
			varName = OneOfOp->Question.VarStoreInfo.VarName;

			questionFlags = OneOfOp->Question.Flags;
			DefaultSize = 1 << (OneOfOp->Flags & 0x0F);			//if 0, the size is 1 so adding with 1
			break;

		// ------ one of option--------------
		case EFI_IFR_ONE_OF_OPTION_OP:
			OneOfOption = (EFI_IFR_ONE_OF_OPTION*)((UINT8*)Data + i);

			Flags =OneOfOption->Flags;
			if((Flags & EFI_IFR_OPTION_DEFAULT) == EFI_IFR_OPTION_DEFAULT)
			{
				GetDefaultValue(OneOfOption->Type, &(OneOfOption->Value), size, Optimal,(UINT8*)Data + i);
			}

			if((Flags & EFI_IFR_OPTION_DEFAULT_MFG) == EFI_IFR_OPTION_DEFAULT_MFG)
			{
				GetDefaultValue(OneOfOption->Type, &(OneOfOption->Value), size, Failsafe,(UINT8*)Data + i);
			}

			break;

		// ------ checkbox --------------
		case EFI_IFR_CHECKBOX_OP:
			CheckBoxOp = (EFI_IFR_CHECKBOX*)Data;

			CtrlVar = _GetVarNumFromVarID(CheckBoxOp->Question.VarStoreId, Handle, (void *)CheckBoxOp);
			QuestionId = CheckBoxOp->Question.VarStoreInfo.VarOffset;
			varName = CheckBoxOp->Question.VarStoreInfo.VarName;
			questionFlags = CheckBoxOp->Question.Flags;
			//if(CheckBoxOp->Header.Scope == 0) EIP-80422 
			//{
			Flags = CheckBoxOp->Flags ;

			//*size = sizeof(UINT8);
			*(UINT8*)Optimal = (Flags & EFI_IFR_CHECKBOX_DEFAULT)? 1 : 0;
			if (*(UINT8*)Optimal)
				*size = sizeof(UINT8);//EIP-116566 Set size if it has default

			*(UINT8*)Failsafe = (Flags & EFI_IFR_CHECKBOX_DEFAULT_MFG)? 1 : 0;
			if (*(UINT8*)Failsafe)
				*size = sizeof(UINT8);//EIP-116566 Set size if it has default

			Control_Flags->ControlRefresh = 0;
			//}
			DefaultSize = 1;
			break;

		// ------ numeric --------------
		case EFI_IFR_NUMERIC_OP:
			NumericOp = (EFI_IFR_NUMERIC*)((UINT8*)Data + i);

			Control_Flags->ControlRefresh = 0;
			questionFlags = NumericOp->Question.Flags;
			QuestionId = NumericOp->Question.VarStoreInfo.VarOffset;
			CtrlVar = _GetVarNumFromVarID(NumericOp->Question.VarStoreId, Handle, (void *)NumericOp);
			varName = NumericOp->Question.VarStoreInfo.VarName;
			DefaultSize = 1 << (NumericOp->Flags & 0x0F);			//if 0, the size is 1 so adding with 1
			break;

		// ------ ordered list --------------
		case EFI_IFR_ORDERED_LIST_OP:
			OrderedListOp = (EFI_IFR_ORDERED_LIST*)((UINT8*)Data + i);

			QuestionId = OrderedListOp->Question.VarStoreInfo.VarOffset;
			CtrlVar = _GetVarNumFromVarID(OrderedListOp->Question.VarStoreId, Handle, (void *)OrderedListOp);
			varName = OrderedListOp->Question.VarStoreInfo.VarName;
			questionFlags =OrderedListOp->Question.Flags;
			DefaultSize = OrderedListOp->MaxContainers;
			break;

		// ------ date --------------
		case EFI_IFR_DATE_OP:
      		DateOp = (EFI_IFR_DATE*)((UINT8*)Data + i);

      		CtrlVar = _GetVarNumFromVarID(DateOp->Question.VarStoreId, Handle, (void *)DateOp);
			varName = DateOp->Question.VarStoreInfo.VarName;
      		questionFlags =DateOp->Question.Flags;
			QuestionId = DateOp->Question.VarStoreInfo.VarOffset;
            if ((DateOp->Flags & EFI_QF_DATE_STORAGE) == QF_DATE_STORAGE_TIME)
            {
                Control_Flags->ControlRefresh = DEFAULT_DATETIME_REFRESH; /**refresh*/
            }
			break;

		// ------ time --------------
		case EFI_IFR_TIME_OP:
      		TimeOp = (EFI_IFR_TIME*)((UINT8*)Data + i);
      		CtrlVar = _GetVarNumFromVarID(TimeOp->Question.VarStoreId, Handle, (void *)TimeOp);
			varName = TimeOp->Question.VarStoreInfo.VarName;
      		questionFlags =TimeOp->Question.Flags;
			QuestionId = TimeOp->Question.VarStoreInfo.VarOffset;
            if ((TimeOp->Flags & QF_TIME_STORAGE) == QF_TIME_STORAGE_TIME)		//EIP 61650 Not able to edit the normal storage time opcode
			{
				Control_Flags->ControlRefresh = DEFAULT_DATETIME_REFRESH;	
			}
             //Control_Flags->ControlRefresh = DEFAULT_DATETIME_REFRESH;
			break;

		// ------ string --------------
		case EFI_IFR_STRING_OP:
			StringOp = (EFI_IFR_STRING*)Data;

			questionFlags = StringOp->Question.Flags;
			QuestionId = StringOp->Question.VarStoreInfo.VarOffset;
			CtrlVar = _GetVarNumFromVarID(StringOp->Question.VarStoreId, Handle, (void *)StringOp);
			varName = StringOp->Question.VarStoreInfo.VarName;
        break;

		// ------ End op --------------
		case EFI_IFR_END_OP:
			if(ScopeCount)
			{
				ScopeCount--;
			}
			break;

		// ------ password--------------
		case EFI_IFR_PASSWORD_OP:
			PasswordOp = (EFI_IFR_PASSWORD*)Data;

			questionFlags = PasswordOp->Question.Flags;
			CtrlVar = _GetVarNumFromVarID(PasswordOp->Question.VarStoreId, Handle, (void *)PasswordOp);
			QuestionId = PasswordOp->Question.VarStoreInfo.VarOffset;
			varName = PasswordOp->Question.VarStoreInfo.VarName;
			break;

    	// ------- Action --------------
	    case EFI_IFR_ACTION_OP:
			ActionOp = (EFI_IFR_ACTION*)Data;

			questionFlags = ActionOp->Question.Flags;
			CtrlVar = _GetVarNumFromVarID(ActionOp->Question.VarStoreId, Handle, (void *)ActionOp);
			QuestionId = ActionOp->Question.VarStoreInfo.VarOffset;
		  //	if ((questionFlags & EFI_IFR_FLAG_CALLBACK) && (Control_Flags->ControlRefresh == 0))
			
			//EIP:116513 Do refresh only if AMI CALLBACK value is used.  
			if(ConditionalPtr != NULL)
	  		{    
	  			if(INTERACTIVE_TEXT_VALUE == UefiTseLiteGetAmiCallbackIndex(ConditionalPtr,ActionOp ))
	  			    Control_Flags->ControlRefresh = DEFAULT_REFRESH_RATE;
	  		}	
			break;

	    // ------- Reset Button --------------
	    case EFI_IFR_RESET_BUTTON_OP:
			break;

		// ------ default --------------
		case EFI_IFR_DEFAULT_OP:
			DefaultOp = (EFI_IFR_DEFAULT*)((UINT8*)Data + i);

			if(DefaultOp->Type == EFI_IFR_TYPE_BUFFER) //Update the size value for the EFI_IFR_TYPE_BUFFER
			{
				//Update size for the array of value stored in VALUE field excluding size for op_header, DefaultId & Type
				*size = ((EFI_IFR_OP_HEADER*)DefaultOp)->Length - sizeof(EFI_IFR_OP_HEADER) - sizeof(UINT16) - sizeof(UINT8);
			}
            else if(DefaultOp->Type == EFI_IFR_TYPE_REF) //ifREf5 Opcode with default value, value is obtained as size of EFI_HII_REF EIP109812, 107774
            {
                //buffer is of size EFI_HII_REF.
                *size = sizeof(AMI_EFI_HII_REF);
            }

			if(DefaultOp->Header.Scope && DefaultOp->Type > EFI_IFR_TYPE_BUFFER)
			{
				// retrieve default value from within scope (evaluate EFI_IFR_VALUE)
				Control_Flags->ControlEvaluateDefault = TRUE;
			}
			else if(DefaultOp->DefaultId == EFI_HII_DEFAULT_CLASS_STANDARD)
			{
					// if Optimal is not large enough to hold the buffer, allocate more space for it.
				if (*size > sizeof (UINT64)) {
					Optimal = MemReallocateZeroPool (Optimal, sizeof (UINT64), (UINTN) *size);
				}
				GetDefaultValue(DefaultOp->Type, &(DefaultOp->Value), size, Optimal,(UINT8*)Data + i);
				if ((0 == *size) && (DefaultOp->Type == EFI_IFR_TYPE_OTHER)) // GetDefaultValue will return 0 if need Evalutaion
					Control_Flags->ControlEvaluateDefault = TRUE;
				else if (DefaultSize) {
					*size = DefaultSize;
				}
			}
			else if(DefaultOp->DefaultId == EFI_IFR_OPTION_DEFAULT_MFG)
			{
				// if Failsafe is not large enough to hold the buffer, allocate more space for it.
				if (*size > sizeof (UINT64)) {
					Failsafe = MemReallocateZeroPool (Failsafe, sizeof (UINT64), (UINTN) *size);
				}
				GetDefaultValue(DefaultOp->Type, &(DefaultOp->Value), size, Failsafe,(UINT8*)Data + i);
				if ((0 == *size) && (DefaultOp->Type == EFI_IFR_TYPE_OTHER))
					Control_Flags->ControlEvaluateDefault = TRUE;
				else if (DefaultSize)	{
					*size = DefaultSize;
				}
			}
			//else //EIP-124286 Commented since it will not fill Standard and above case defaults for default2 when ResetButton is pressed
			{ // EIp : 56124 Defautls are stored as linked list
				DEFAULT_VALUE *defaults = NULL;
				if(*defaultValue == NULL)
				{
					*defaultValue = (DEFAULT_VALUE*)EfiLibAllocateZeroPool(sizeof(DEFAULT_VALUE));
					defaults = *defaultValue;
				}else
				{
					for(defaults = *defaultValue; defaults->Next; defaults = defaults->Next)
						;
					defaults->Next = (DEFAULT_VALUE*)EfiLibAllocateZeroPool(sizeof(DEFAULT_VALUE));
					defaults = defaults->Next;
				}
				defaults->DefaultId = DefaultOp->DefaultId;
				GetDefaultValue(DefaultOp->Type, &(DefaultOp->Value), size, &defaults->Value, (UINT8*)Data + i);
				if((*size == 0 ) && (DefaultOp->Type == EFI_IFR_TYPE_OTHER))
					Control_Flags->ControlEvaluateDefault = TRUE;
				else if (DefaultSize)
					*size = DefaultSize;
				defaultCount++;
			}
//			DefaultSize = 0;			//If defaultstore 2 is present then changing to 0 will mal function so commented.
			break;

		// ------ refresh --------------
		case EFI_IFR_REFRESH_OP:
			Control_Flags->ControlRefresh = ((EFI_IFR_REFRESH*)((UINT8*)Data + i))->RefreshInterval;
			// SetupData's ControlRefresh Granularity is 1/20 Sec (TSE_REFRESH_GRANURALITY) and makesure it does not cross BYTE size
			Control_Flags->ControlRefresh = (UINT8)( ((Control_Flags->ControlRefresh*TSE_REFRESH_GRANURALITY) <= 0xFF)? 
										(Control_Flags->ControlRefresh*TSE_REFRESH_GRANURALITY): 0xFF);
			break;
        
        // ------ refresh id --------------
        case EFI_IFR_REFRESH_ID_OP:
            MemCopy( &RefreshEventGroupId, &(((AMI_EFI_IFR_REFRESH_ID *)((UINT8*)Data + i))->RefreshEventGroupId), sizeof(EFI_GUID) );
            Control_Flags->RefreshID = TRUE;//EIP-105468
            break;

		// ------ inconsistent if --------------
		case EFI_IFR_INCONSISTENT_IF_OP:
			if(IsRecursive == FALSE)
			{
				Inconsistant = TRUE;
			}
			break;
		//----locked-----EIP:56896 
		case EFI_IFR_LOCKED_OP:
			questionFlags |= EFI_IFR_FLAG_READ_ONLY;
			break;
				//EIP : -------------- NO_SUBMIT_IF --------------
		case EFI_IFR_NO_SUBMIT_IF_OP:
			if(IsRecursive == FALSE)
			{
				NoSubmitIf = TRUE;
			}
			break;


		default:
			break;
		}

		if(OpHeader->Scope)
		{
			ScopeCount++;
		}

		i += OpHeader->Length;
	}while(ScopeCount != 0);

	Control_Flags->ControlReset = (questionFlags & EFI_IFR_FLAG_RESET_REQUIRED)? 1 : 0;
	Control_Flags->ControlReadOnly = (questionFlags & EFI_IFR_FLAG_READ_ONLY)? 1 : 0;
	Control_Flags->ControlInteractive = (questionFlags & EFI_IFR_FLAG_CALLBACK)? 1 : 0;

	if(CtrlVar)
	{
		varInfo = (VARIABLE_INFO*)((UINT8 *)VariableInfoPtr + VariableListPtr->VariableList[CtrlVar]);
		if(varInfo->ExtendedAttibutes)
		{
			varInfo->VariableNameId = varName;
			varString = HiiGetString(varInfo->VariableHandle, varName);
			if(varString && (EfiStrLen(varInfo->VariableName) == 0))
			{
				EfiStrCpy(varInfo->VariableName, varString);
			}
		}
	}

	*FailsafeValue = Failsafe;
    *OptimalValue = Optimal;

    SETUP_DEBUG_UEFI( "\n[TSE] Exiting _UpdateDefaults()\n")  ;   
    
	return defaultCount;//EIP:56124 Returning the Default count for the control
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    GetValueFromOpCode
//
// Description:  Gets the value from the opcode
//
// Parameter:    EFI_IFR_OP_HEADER *, 
//               EFI_HII_VALUE *, 
//               INTN 
//
// Return value: VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetValueFromOpCode (EFI_IFR_OP_HEADER *ifrData, EFI_HII_VALUE *Value, INTN Result)
{
  EFI_HII_VALUE           Data1;
  EFI_HII_VALUE           Data2;
  EFI_STATUS              Status = EFI_SUCCESS;
  EfiZeroMem (&Data1, sizeof (EFI_HII_VALUE));
  EfiZeroMem (&Data1, sizeof (EFI_HII_VALUE));
  EfiZeroMem (Value, sizeof (EFI_HII_VALUE));

     switch (ifrData->OpCode) {
        case EFI_IFR_EQUAL_OP:
            Value->Value.b = (Result == 0) ? TRUE : FALSE;
            break;

        case EFI_IFR_NOT_EQUAL_OP:
            Value->Value.b = (Result != 0) ? TRUE : FALSE;
            break;

        case EFI_IFR_GREATER_EQUAL_OP:
            Value->Value.b = (Result >= 0) ? TRUE : FALSE;
            break;

        case EFI_IFR_GREATER_THAN_OP:
            Value->Value.b = (Result > 0) ? TRUE : FALSE;
            break;

        case EFI_IFR_LESS_EQUAL_OP:
            Value->Value.b = (Result <= 0) ? TRUE : FALSE;
            break;

        case EFI_IFR_LESS_THAN_OP:
            Value->Value.b = (Result < 0) ? TRUE : FALSE;
            break;
        case EFI_IFR_UINT8_OP:
            Value->Type = EFI_IFR_TYPE_NUM_SIZE_8;
            Value->Value.u8 = ((EFI_IFR_UINT8*)ifrData)->Value;
           break;
        case EFI_IFR_UINT16_OP:
            Value->Type = EFI_IFR_TYPE_NUM_SIZE_16;
            Value->Value.u16 = ((EFI_IFR_UINT16*)ifrData)->Value;
           break;
        case EFI_IFR_UINT32_OP:
            Value->Type = EFI_IFR_TYPE_NUM_SIZE_32;
            Value->Value.u32 = ((EFI_IFR_UINT32*)ifrData)->Value;
           break;
        case EFI_IFR_UINT64_OP:
            Value->Type = EFI_IFR_TYPE_NUM_SIZE_64;
            Value->Value.u64 = ((EFI_IFR_UINT64*)ifrData)->Value;
           break;
       case EFI_IFR_NOT_OP:
            Status = PopExpression (Value);
            if (EFI_ERROR (Status)) {
               break;
            }
            if (Value->Type != EFI_IFR_TYPE_BOOLEAN) {
                break;
            }
            Value->Value.b = !Value->Value.b;
           break;
       case EFI_IFR_AND_OP:
       case EFI_IFR_OR_OP:
            //
            // Two Boolean operator
            //
            Status = PopExpression (&Data2);
            if (EFI_ERROR (Status)) {
                 break;
            }
            if (Data2.Type != EFI_IFR_TYPE_BOOLEAN) {
                break;
            }

            //
            // Pop another expression from the expression stack
            //
            Status = PopExpression (&Data1);
            if (EFI_ERROR (Status)) {
                break;
            }
            if (Data1.Type != EFI_IFR_TYPE_BOOLEAN) {
                break;
            }

            if (ifrData->OpCode == EFI_IFR_AND_OP) {
                Value->Value.b = Data1.Value.b && Data2.Value.b;
            } else {
                Value->Value.b = Data1.Value.b || Data2.Value.b;
            }
           break;
        //
        // binary-op
        //
        case EFI_IFR_ADD_OP:
        case EFI_IFR_SUBTRACT_OP:
        case EFI_IFR_MULTIPLY_OP:
        case EFI_IFR_DIVIDE_OP:
        case EFI_IFR_MODULO_OP:
        case EFI_IFR_BITWISE_AND_OP:
        case EFI_IFR_BITWISE_OR_OP:
        case EFI_IFR_SHIFT_LEFT_OP:
        case EFI_IFR_SHIFT_RIGHT_OP:
          //
          // Pop an expression from the expression stack
          //
          Status = PopExpression (&Data2);
          if (EFI_ERROR (Status)) {
            break;
          }
          if (Data2.Type > EFI_IFR_TYPE_DATE) {
            Status = EFI_INVALID_PARAMETER;
            break;
          }

          //
          // Pop another expression from the expression stack
          //
          Status = PopExpression (&Data1);
          if (EFI_ERROR (Status)) {
            break;
          }
          if (Data1.Type > EFI_IFR_TYPE_DATE) {
            break;
          }

          Value->Type = EFI_IFR_TYPE_NUM_SIZE_64;

          switch (ifrData->OpCode) {
            case EFI_IFR_ADD_OP:
              Value->Value.u64 = Data1.Value.u64 + Data2.Value.u64;
              break;

            case EFI_IFR_SUBTRACT_OP:
              Value->Value.u64 = Data1.Value.u64 - Data2.Value.u64;
              break;

            case EFI_IFR_MULTIPLY_OP:
              Value->Value.u64 = MultU64x32 (Data1.Value.u64, (UINT32)Data2.Value.u64);
              break;

            case EFI_IFR_DIVIDE_OP:
              Value->Value.u64 = AmiTseDivU64x32 (Data1.Value.u64, (UINT32)Data2.Value.u64,NULL);
              break;

            case EFI_IFR_MODULO_OP:
              Value->Value.u64 = 0;
              AmiTseDivU64x32(Data1.Value.u64, (UINT32)Data2.Value.u64, (UINTN*)Value->Value.u64);
              break;

            case EFI_IFR_BITWISE_AND_OP:
              Value->Value.u64 = Data1.Value.u64 & Data2.Value.u64;
              break;

            case EFI_IFR_BITWISE_OR_OP:
              Value->Value.u64 = Data1.Value.u64 | Data2.Value.u64;
              break;

            case EFI_IFR_SHIFT_LEFT_OP:
              Value->Value.u64 = LShiftU64 (Data1.Value.u64, (UINTN) Data2.Value.u64);
              break;

            case EFI_IFR_SHIFT_RIGHT_OP:
              Value->Value.u64 = RShiftU64 (Data1.Value.u64, (UINTN) Data2.Value.u64);
              break;

            default:
              break;
          }

        default:
            Value->Type = EFI_IFR_TYPE_UNDEFINED;
           break;
      }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    EvaluateReadWrite
//
// Description:  Evaluates read write conditions
//
// Parameter:    UINT8 *, 
//               CONTROL_INFO *, 
//               EFI_HII_VALUE * 
//
// Return value: VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetRWVariableID (UINT16 RWVarStoreId, CONTROL_INFO *ControlInfo, UINT16 *VarStoreId);
VOID EvaluateReadWrite(UINT8 *buf, CONTROL_INFO *ControlInfo, EFI_HII_VALUE *Value1)
{
  EFI_HII_VALUE           *Value=NULL;
  EFI_HII_VALUE	           *questionValue=NULL;
  EFI_IFR_TYPE_VALUE	  questionValue1;
  UINT64                  qValue=0;
  EFI_HII_VALUE           Data1;
  EFI_HII_VALUE           Data2;
  EFI_HII_VALUE           Data3;
  EFI_IFR_OP_HEADER		  *ifrData = NULL;
  EFI_STATUS              Status;
  INTN                    Result;
  UINTN					  i = 0;
  UINTN					  j = 0;
  EFI_QUESTION_ID		  questionId = 0;
  AMI_EFI_IFR_GET *IfrGet =NULL;
  AMI_EFI_IFR_SET *IfrSet =NULL;
  UINTN  dataWidth  = 0;
  UINT16 Size = 0;
  EFI_IFR_QUESTION_HEADER *questionHdr = NULL;
  UINT64 def;
  UINTN ScopeCount = 0;
  
  ResetExpressionStack ();
  questionValue = (EFI_HII_VALUE*)EfiLibAllocateZeroPool(sizeof(EFI_HII_VALUE));
  EfiZeroMem (questionValue, sizeof (EFI_HII_VALUE));
  EfiZeroMem (&Data1, sizeof (EFI_HII_VALUE));
  EfiZeroMem (&Data2, sizeof (EFI_HII_VALUE));
  EfiZeroMem (&Data3, sizeof (EFI_HII_VALUE));
  Value = &Data3;
  Value->Type = EFI_IFR_TYPE_BOOLEAN;

  ifrData = (EFI_IFR_OP_HEADER*)buf;
    
  do
  {
    if(ifrData->Scope)
	{
		ScopeCount++;
    }
      
    switch(ifrData->OpCode)
    {
    
    case EFI_IFR_THIS_OP:
      Status = _GetValueFromQuestionId(ControlInfo->ControlKey, ControlInfo->ControlPageID, &questionValue);
      if(EFI_ERROR(Status))
      {
        goto DONE;
      }
      Value = questionValue;
        break;
    case EFI_IFR_END_OP:
        if(ScopeCount)
		{
		    ScopeCount--;
		}
       
       goto DONE;

    case EFI_IFR_GET_OP:
      {
         UINT16 VarStoreId = 0;
         IfrGet = (AMI_EFI_IFR_GET *)ifrData;
         GetDefaultValue(IfrGet->VarStoreType,&questionValue1, &Size, &def, (UINT8 *)ifrData);
         Status = GetRWVariableID (IfrGet->VarStoreId, ControlInfo, &VarStoreId);
         if(EFI_ERROR(Status))
         {
           goto DONE;
         }
         Status = VarGetValue(VarStoreId, IfrGet->VarStoreInfo.VarOffset, (( Size > sizeof(UINT64))? sizeof(UINT64) : Size ), &qValue);
         if(EFI_ERROR(Status))
         {
           goto DONE;
         }
         Value->Value.u64 = qValue;
        break;
      }
    case EFI_IFR_SET_OP:
    {
        UINT16 VarStoreId = 0;
        IfrSet = (AMI_EFI_IFR_SET *)ifrData;
        GetDefaultValue(IfrSet->VarStoreType,&questionValue1, &Size, &def, (UINT8 *)ifrData);
        Status = GetRWVariableID (IfrSet->VarStoreId, ControlInfo, &VarStoreId);
        if(EFI_ERROR(Status))
        {
          goto DONE;
        }
        Status = PopExpression (&Data1);
        if (EFI_ERROR (Status)) {
          goto DONE;
        }
        qValue = Data1.Value.u64;
        if(Data1.Type != EFI_IFR_TYPE_UNDEFINED){
            Status = VarSetValue(VarStoreId, IfrSet->VarStoreInfo.VarOffset, (( Size > sizeof(UINT64))? sizeof(UINT64) : Size ), &qValue);
        }
        if(EFI_ERROR(Status))
        {
         goto DONE;
        }
        Value->Type = Data1.Type;
        Value->Value.u64 = qValue;
        break;
    }
    case EFI_IFR_MAP_OP:
        Status = PopExpression (&Data1);
        if (EFI_ERROR (Status)) {
          goto DONE;
        }
        i+=ifrData->Length;
        ifrData = (EFI_IFR_OP_HEADER*)(buf + i);
        while (ifrData->OpCode != EFI_IFR_END_OP)
        {
            GetValueFromOpCode(ifrData,Value,Result);          
            Result = CompareHiiValue (&Data1, Value,NULL);
            i+=ifrData->Length;    
            ifrData = (EFI_IFR_OP_HEADER*)(buf + i);		//Skip its pair so incrementing ifrData
            if (0 == Result)
            {
	        GetValueFromOpCode(ifrData,Value,Result);	//Retreiving the value
                while(ifrData->OpCode != EFI_IFR_END_OP)
                {
                    i+=ifrData->Length;
                    ifrData = (EFI_IFR_OP_HEADER*)(buf + i);
                }
            }
            else
            {
		    i+=ifrData->Length;
		    ifrData = (EFI_IFR_OP_HEADER*)(buf + i);
            }
        }
        if ((EFI_IFR_END_OP == ifrData->OpCode) && (ScopeCount))		//Since endopcode validated before itself here we decrementing scope
	{
	    ScopeCount --;
	}
        break;
    case EFI_IFR_CONDITIONAL_OP:
        //
      // Pop third expression from the expression stack
      //
      Status = PopExpression (&Data3);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      //
      // Pop second expression from the expression stack
      //
      Status = PopExpression (&Data2);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }

      //
      // Pop first expression from the expression stack
      //
      Status = PopExpression (&Data1);
      if (EFI_ERROR (Status)) {
        goto DONE;
      }
    
      if (Data1.Value.b) {
        Value = &Data2;
      } else {
        Value = &Data3;
      }
      break;
    case EFI_IFR_EQUAL_OP:
    case EFI_IFR_NOT_EQUAL_OP:
    case EFI_IFR_GREATER_EQUAL_OP:
    case EFI_IFR_GREATER_THAN_OP:
    case EFI_IFR_LESS_EQUAL_OP:
    case EFI_IFR_LESS_THAN_OP:
       //
      // Compare two integer, string, boolean or date/time
      //
      Status = PopExpression (&Data2);
      if (EFI_ERROR (Status)) {
	    goto DONE;
      }
      if (Data2.Type > EFI_IFR_TYPE_BOOLEAN && Data2.Type != EFI_IFR_TYPE_STRING) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }

      //
      // Pop another expression from the expression stack
      //
      Status = PopExpression (&Data1);
      if (EFI_ERROR (Status)) {
	    goto DONE;
      }

      Result = CompareHiiValue (&Data1, &Data2,NULL);
      if (Result == EFI_INVALID_PARAMETER) {
        Status = EFI_INVALID_PARAMETER;
        goto DONE;
      }
      GetValueFromOpCode(ifrData,Value,Result);
      break;
    case EFI_IFR_UINT8_OP:
    case EFI_IFR_UINT16_OP:
    case EFI_IFR_UINT32_OP:
    case EFI_IFR_UINT64_OP:
      GetValueFromOpCode(ifrData,Value,Result);
      break;

    // binary-op
    
    case EFI_IFR_ADD_OP:
    case EFI_IFR_SUBTRACT_OP:
    case EFI_IFR_MULTIPLY_OP:
    case EFI_IFR_DIVIDE_OP:
    case EFI_IFR_MODULO_OP:
    case EFI_IFR_BITWISE_AND_OP:
    case EFI_IFR_BITWISE_OR_OP:
    case EFI_IFR_SHIFT_LEFT_OP:
    case EFI_IFR_SHIFT_RIGHT_OP:
        GetValueFromOpCode(ifrData,Value,Result);
      break;
    case EFI_IFR_UNDEFINED_OP:
	 Value1->Type = EFI_IFR_TYPE_UNDEFINED;
        return;
    default:
       goto DONE;
       break;

    }
    PushExpression(Value);
    DONE:
    i += ((EFI_IFR_OP_HEADER*)(buf + i))->Length;
    ifrData = (EFI_IFR_OP_HEADER*)(buf + i);
  } while(ScopeCount);
  MemFreePointer(&questionValue);
  Status = PopExpression (&Data1);
  if(EFI_ERROR (Status)){
      Data1.Type = EFI_IFR_TYPE_UNDEFINED;
  }
  MemCopy(Value1,&Data1,sizeof(EFI_HII_VALUE));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _AddHpkControls
//
// Description:  Add Control Setup Data
//
// Parameter:
//
// Return value: UINTN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN _AddHpkControls(EFI_HII_HANDLE Handle, UINT8 *buff,UINTN Size, PAGE_INFO **NewPageInfo, UINT32 *AllocatedPageSize, UINT32 *PageOffset)
{
    CONTROL_FLAGS control_Flags;
    CONTROL_INFO *control_Info;
    CONTROL_INFO *NotifyContext = (CONTROL_INFO*)NULL;
    EFI_IFR_OP_HEADER *opHeader= NULL;
    EFI_EVENT RefreshIdEvent = (EFI_EVENT)NULL;
  	 EFI_IFR_OP_HEADER *opHdrPtr= (EFI_IFR_OP_HEADER *)NULL;


    BOOLEAN addControl = TRUE;
    BOOLEAN updatecondvars = TRUE;
    UINT8  opCode = 0;
    UINT16 controlLabel = 0;
    UINT16 controlIndex = 0;
    UINT16 destPageID =0xFFFF;
    UINT16 controlType = 0;
    UINT16 devicePathId = 0;
    UINT16 helpOffset = 0;
    UINT16 questionId = 0;
    UINT16 opcodeNum = 0;
    UINT16 defaults_size=0;
    UINT16 controlKey = 0;
    UINT32 controlSize = 0;
    UINT32 controlOffset = 0;
    INT32  ifCounter = 0;
    VOID   *ctrlFailSafe = NULL;
    VOID   *ctrlOptimal = NULL;
   UINTN  i =0, end=0,j=0,index=0, itr = 0;
    VOID   *conditionalPtr = NULL;
    VOID   *controlPtr = NULL;
    BOOLEAN Formlock = FALSE;//EIP:56896 support for Formlock
    UINT16 refQuestionId = 0;   //EIP: 55762 
	EFI_STATUS Status = EFI_SUCCESS;
   INT32 ScopeCount = 0;


	DEFAULT_VALUE *defaultValue = NULL, *Temp= NULL;//EIP:56214 Declaration for the Default value 

    SETUP_DEBUG_UEFI("\n[TSE] Entering _AddHpkControls\n");

	// for loop for the number of controls of this
	while(i < Size )
 	{
    addControl = TRUE;
		MemSet(&control_Flags, sizeof(CONTROL_FLAGS), 0);
		control_Flags.ControlVisible =0x1;
    controlType = 0;
    CtrlVar = 0;
    destPageID =0xFFFF;

    opHeader = (EFI_IFR_OP_HEADER*)(buff + i);
    if(opHeader->Scope)
    {
     PushScope(opHeader->OpCode);
    }

		// control type
    switch(opHeader->OpCode)
    {
    case EFI_IFR_SUBTITLE_OP:
      controlType = CONTROL_TYPE_MEMO;
      break;
    case EFI_IFR_TEXT_OP:
      controlType = CONTROL_TYPE_TEXT;
      break;
    case EFI_IFR_ONE_OF_OP:
    case EFI_IFR_CHECKBOX_OP:
      controlType = CONTROL_TYPE_POPUPSEL;
      break;
    case EFI_IFR_NUMERIC_OP:
      controlType = CONTROL_TYPE_NUMERIC;
      break;
    case EFI_IFR_PASSWORD_OP:
      controlType = CONTROL_TYPE_PASSWORD;
      break;
    case EFI_IFR_ACTION_OP:
      controlType = CONTROL_TYPE_ACTION;
      break;
    case EFI_IFR_MODAL_TAG_OP: //EIP-85745 Modal Support
      (*NewPageInfo)->PageFlags.PageModal = 1;
      break;	 
    case EFI_IFR_RESET_BUTTON_OP:
      controlType = CONTROL_TYPE_RESET;
      break;
    case EFI_IFR_REF_OP:
      controlType = CONTROL_TYPE_SUBMENU;
      destPageID =  _GetPageNumFromFormID(((EFI_IFR_REF*)((char*)buff +i))->FormId);
//EIP: 55762 Start
      if(opHeader->Length >= sizeof(EFI_IFR_REF2))
      {
        refQuestionId = ((EFI_IFR_REF2*)((char*)buff +i))->QuestionId;
      }
//EIP: 55762 End
      break;
    case EFI_IFR_INCONSISTENT_IF_OP:
      controlType = INCONSISTENT_IF;
      break;
      //EIP : NO_SUBMIT_IF	
	case EFI_IFR_NO_SUBMIT_IF_OP:
      controlType = NO_SUBMIT_IF;
      break;
    case EFI_IFR_RULE_OP:
      controlType = CONTROL_TYPE_RULE;
      conditionalPtr = (VOID *)((UINT8 *)opHeader + sizeof(EFI_IFR_RULE));
      break;
    case EFI_IFR_END_OP:
      PopScope(&opCode);
      switch(opCode)
      {
      case EFI_IFR_FORM_OP:
      case EFI_IFR_FORM_MAP_OP:
        i += opHeader->Length;
        end =1;
        break;
      case EFI_IFR_NO_SUBMIT_IF_OP:
      case EFI_IFR_INCONSISTENT_IF_OP:
      case EFI_IFR_SUPPRESS_IF_OP:
      case EFI_IFR_GRAY_OUT_IF_OP:
      case EFI_IFR_DISABLE_IF_OP:
        controlType = --ifCounter? 0 : END_EVAL_IF;
        break;
      default:
        controlType = 0;
        break;
      }
      addControl = FALSE;
      break;
    case EFI_IFR_DATE_OP:
      controlType = CONTROL_TYPE_DATE;
      break;
    case EFI_IFR_TIME_OP:
      controlType = CONTROL_TYPE_TIME;
      break;
    case EFI_IFR_STRING_OP:
      controlType = CONTROL_TYPE_POPUP_STRING;
      break;
    case EFI_IFR_SUPPRESS_IF_OP:
	//case EFI_IFR_NO_SUBMIT_IF_OP: 
    case EFI_IFR_GRAY_OUT_IF_OP:
    case EFI_IFR_DISABLE_IF_OP:
      controlType = START_EVAL_IF;
      addControl =FALSE;
      break;
    case EFI_IFR_ORDERED_LIST_OP:
      controlType = CONTROL_TYPE_ORDERED_LIST;
      break;
    case EFI_IFR_VARSTORE_OP:
    case EFI_IFR_VARSTORE_NAME_VALUE_OP:
    case EFI_IFR_VARSTORE_EFI_OP:
      _AddVariable((UINT8*)opHeader, Handle);
      addControl =FALSE;
      break;
	  //EIP:56896 Form lock support provided.
	case EFI_IFR_LOCKED_OP:
		Formlock = TRUE;
		break;
    default:
      addControl = FALSE;
      break;
    }

    switch(controlType)
    {
	//EIP : NO_SUBMIT_IF
	case NO_SUBMIT_IF:
    case INCONSISTENT_IF:
    case START_EVAL_IF: // IF for grayout,suppress, no submit and disable
      if(updatecondvars == 1)
      {
        updatecondvars = 0;
		conditionalPtr = (gConditionOverForm == TRUE) ? gConditionalOverFormPtr : (VOID *)opHeader;				
      }
      ifCounter++;
      break;
    case END_EVAL_IF:
      conditionalPtr = NULL;
      updatecondvars = TRUE;
      ifCounter = 0;
      break;
    default:
      break;
    }

		if(end ==1)
			break;

		if(addControl)
		{
	      defaults_size =0;

			controlKey = _GetControlKeyToken((UINT8*)opHeader);
			devicePathId = _GetControlDevicePathId((UINT8*)opHeader);
			helpOffset = _GetHelpToken((UINT8*)opHeader);
			questionId = _GetQuestionToken((UINT8*)opHeader);

			DefaultStoreCount = _UpdateDefaults(Handle, (void *)opHeader, &defaults_size, &ctrlFailSafe, &ctrlOptimal, &defaultValue,&control_Flags, conditionalPtr);
			//EIP:56896 Checking for the Formlock condition
			if(Formlock)
				control_Flags.ControlReadOnly = 1;	
            //EIP:56124 Allocating the control Size depending on the default count of the control
			controlSize = sizeof(CONTROL_INFO) + defaults_size * 2+ DefaultStoreCount*(sizeof(UINT16) + defaults_size);
			control_Info = EfiLibAllocateZeroPool(controlSize);
			if(control_Info == NULL)
			{
				i = Size;
				goto DONE;
			}

			controlPtr = (VOID *)opHeader;

			if(controlType == INCONSISTENT_IF  )
			{
				controlType = CONTROL_TYPE_MSGBOX;
				controlPtr = 0;
			}
			//EIP : NO_SUBMIT_IF
			if(controlType == NO_SUBMIT_IF )
			{
				controlType = NO_SUBMIT_IF;
				controlPtr = 0;
			}

			/* Update Control Info*/
			/*
			 * control_Info->ControlHandle
			 * HII Handle to the formset that contains this control
			 */
			control_Info->ControlHandle =  Handle;
			/*
			 * control_Info->ControlVariable
			 * Overrides the variable ID for this specific control
			 */
			control_Info->ControlVariable = CtrlVar;
			/*
			 * control_Info->ControlConditionalVariable
			 * Conditional variable ID?s for this control
			 * or
			 * For UEFI 2.1 Use the following.
			 * control_Info->ControlKey
			 * control_Info->DefaultStoreCount
			 * control_Info->Reserved
			 */
			control_Info->ControlKey = controlKey;
			control_Info->DevicePathId = devicePathId;
			control_Info->DefaultStoreCount = DefaultStoreCount;
			/*
			 * control_Info->ControlType
			 * Type of the control on the page
			 */
			control_Info->ControlType = controlType & CONTROL_TYPE_MASK;
			/*
			 * control_Info->ControlPageID
			 * Page ID that contains this control
			 */
			control_Info->ControlPageID = PageListPtr ? (UINT16)PageListPtr->PageCount:1;
			/*
			 * control_Info->ControlDestPageID
			 * Dest PageId. Only needed for controls of type CONTROL_TYPE_SUBMENU
			 */
			control_Info->ControlDestPageID = destPageID;
			/*
             * control_Info->DestQuestionID
             * Question Id that will be selected refered page is visited. Only needed for controls of type CONTROL_TYPE_SUBMENU
             */
             control_Info->DestQuestionID = refQuestionId;   //EIP: 55762
             /*
			 * control_Info->ControlFlags
			 * Various attributes for a specific control
			 */
			control_Info->ControlFlags = control_Flags;
			/*
			 * control_Info->ControlHelp
			 * Token for help string for this control
			 */
			control_Info->ControlHelp = helpOffset;
			/*
			 * control_Info->ControlLabel
			 * One-based label number that this control is ?linked to?
			 */
			control_Info->ControlLabel = controlLabel;
			/*
			 * control_Info->ControlIndex
			 * Zero-based opcode number from the last label
			 */
			control_Info->ControlIndex = controlIndex;
			/*
			 * control_Info->ControlLabelCount
			 * Number of opcodes associated with this control's label
			 */
			control_Info->ControlLabelCount = opcodeNum;
			/*
			 * control_Info->ControlPtr
			 * Pointer to control data in HII
			 */
			control_Info->ControlPtr = (VOID *)controlPtr;
			/*
			 * control_Info->ControlConditionalPtr
			 * Pointer to control condition data in HII
			 */
			control_Info->ControlConditionalPtr = (gConditionOverForm == TRUE) ? gConditionalOverFormPtr :(VOID *)conditionalPtr;
			/*
			 * control_Info->ControlDataLength
			 * Length of HII data for control
			 */
			control_Info->ControlDataLength = defaults_size;
			/*
			 * control_Info->ControlDataWidth
			 * Width of data (in bytes) for this control
			 */
			control_Info->ControlDataWidth = defaults_size;
			/*
			 * control_Info->QuestionId
			 * QuestionId of this control
			 */
			control_Info->QuestionId = questionId;

             //READ/WRTIE opcode  opHeader 
            if((*NewPageInfo)->PageFlags.PageStdMap){

                if (opHeader->Scope && controlType && addControl)
		        {
  			     	  UINT32 scopeCount = 0;
			        BOOLEAN scoped = TRUE;

			        if(opHeader->OpCode == EFI_IFR_SUBTITLE_OP)
			        {
				        EFI_IFR_OP_HEADER *nextOpHeader = (EFI_IFR_OP_HEADER *)((UINT8 *)opHeader + opHeader->Length);
				        if(nextOpHeader->OpCode != EFI_IFR_END_OP)
					        scoped = FALSE;
			        }
                 itr = 0; 
			        while(scoped)
                    {
                        opHdrPtr = (EFI_IFR_OP_HEADER*)((UINT8*)controlPtr + itr);
                        switch(opHdrPtr->OpCode)
                        {
                            case EFI_IFR_READ_OP:
                            case EFI_IFR_WRITE_OP:
                            case EFI_IFR_MAP_OP:
                                control_Info->ControlFlags.ControlRWEvaluate = 1;
                                scoped = FALSE;
                                break;
                            case EFI_IFR_END_OP:
                                if(scopeCount)
                                {
                                    scopeCount--;
                                 }
                                 if (!scopeCount)			//Check for sudden scopeCount from previous statement
                                    scoped = FALSE;   
                                break;                           
                        }
                        if(opHdrPtr->Scope)
                        {
                            scopeCount++;
                        }
                        itr += opHdrPtr->Length ;
                    }
                }
            }

			if(defaults_size)
			{
				/*
				 * control_Info[sizeof(CONTROL_INFO)]
				 * Used when user selects load failsafe value
				 */

				/*
				 * control_Info[sizeof(CONTROL_INFO) + valSize]
				 * Used when user selects load optimal value
				 */
	/*		//EIP: 56124 Storing the default information by using Memcopy
					MemCopy((UINT8 *)control_Info + sizeof(CONTROL_INFO), &ctrlFailSafe, defaults_size);
					MemCopy((UINT8 *)control_Info + sizeof(CONTROL_INFO)+ defaults_size, &ctrlOptimal, defaults_size);
					if(DefaultStoreCount)
					{
							index=0;
							while(index < DefaultStoreCount)
							{
								MemCopy((UINT8 *)control_Info+sizeof(CONTROL_INFO) + (defaults_size * 2)+ (index *(sizeof(UINT16) + defaults_size)), &defaultValue->DefaultId, sizeof(UINT16) );
								MemCopy((UINT8 *)control_Info + sizeof(CONTROL_INFO) + (defaults_size * 2) + (index *(sizeof(UINT16) + defaults_size)) + sizeof(UINT16) , &defaultValue->Value, defaults_size );
								defaultValue = defaultValue->Next;
								index++;	
							}
	
					}
				
			*/
				Temp = defaultValue;
				switch(defaults_size)
				{
				case 1: // BYTE
                    *((UINT8 *) ((UINT8 *)control_Info + sizeof(CONTROL_INFO))) = *((UINT8 *) ctrlFailSafe);
                    *((UINT8 *) ((UINT8 *)control_Info + sizeof(CONTROL_INFO) + defaults_size)) = *((UINT8 *)ctrlOptimal);
					if(DefaultStoreCount)
					{//copy the defaults to the location in the control info
						index=0;
						while(index < DefaultStoreCount)
						{
							MemCopy((UINT8 *)control_Info+sizeof(CONTROL_INFO) + (defaults_size * 2)+ (index *(sizeof(UINT16) + defaults_size)), &Temp->DefaultId, sizeof(UINT16) );
							*((UINT8 *) ( (UINT8 *)control_Info + sizeof(CONTROL_INFO)+(defaults_size * 2)+(index *(sizeof(UINT16) + defaults_size))+ sizeof(UINT16) )) =  (UINT8 ) (Temp->Value);
							Temp = Temp->Next;
								index++;	
						}
									
					}
					break;
				case 2: //WORD
                    *((UINT16 *) ((UINT8 *)control_Info + sizeof(CONTROL_INFO))) = *((UINT16 *)ctrlFailSafe);
                    *((UINT16 *) ((UINT8 *)control_Info + sizeof(CONTROL_INFO) + defaults_size)) = *((UINT16 *)ctrlOptimal);
					if(DefaultStoreCount)
					{//copy the defaults to the location in the control info
						index=0;
						while(index < DefaultStoreCount)
						{
							MemCopy((UINT8 *)control_Info+sizeof(CONTROL_INFO) + (defaults_size * 2)+ (index *(sizeof(UINT16) + defaults_size)), &Temp->DefaultId, sizeof(UINT16) );
							*((UINT16 *) ( (UINT8 *)control_Info + sizeof(CONTROL_INFO)+(defaults_size * 2)+(index *(sizeof(UINT16) + defaults_size))+ sizeof(UINT16) ) )=  (UINT16 ) (Temp->Value);
							Temp = Temp->Next;
								index++;	
						}
									
					}
					break;
				case 4: //DWORD
                    *((UINT32 *) ((UINT8 *)control_Info + sizeof(CONTROL_INFO))) = *((UINT32 *)ctrlFailSafe);
                    *((UINT32 *) ((UINT8 *)control_Info + sizeof(CONTROL_INFO) + defaults_size)) = *((UINT32 *)ctrlOptimal);
					if(DefaultStoreCount)
					{//copy the defaults to the location in the control info
						index=0;
						while(index < DefaultStoreCount)
						{
							MemCopy((UINT8 *)control_Info+sizeof(CONTROL_INFO) + (defaults_size * 2)+ (index *(sizeof(UINT16) + defaults_size)), &Temp->DefaultId, sizeof(UINT16) );
							*((UINT32 *) ( (UINT8 *)control_Info + sizeof(CONTROL_INFO)+(defaults_size * 2)+(index *(sizeof(UINT16) + defaults_size))+ sizeof(UINT16) )) =  (UINT32) (Temp->Value);	
							Temp = Temp->Next;
								index++;	
						}
									
					}
					break;
				case 8: //QWORD
                    *((UINT64 *) ((UINT8 *)control_Info + sizeof(CONTROL_INFO))) = *((UINT64 *)ctrlFailSafe);
                    *((UINT64 *) ((UINT8 *)control_Info + sizeof(CONTROL_INFO) + defaults_size)) = *((UINT64 *)ctrlOptimal);
					if(DefaultStoreCount)
					{//copy the defaults to the location in the control info
						index=0;
						while(index < DefaultStoreCount)
						{
							MemCopy((UINT8 *)control_Info+sizeof(CONTROL_INFO) + (defaults_size * 2)+ (index *(sizeof(UINT16) + defaults_size)), &Temp->DefaultId, sizeof(UINT16) );
							*((UINT64 *) ( (UINT8 *)control_Info + sizeof(CONTROL_INFO)+(defaults_size * 2)+(index *(sizeof(UINT16) + defaults_size))+ sizeof(UINT16) )) =  (UINT64) (Temp->Value);	
							Temp = Temp->Next;
								index++;	
						}
									
					}
					break;
				default: // MemCopy the value equivalent to the default buffer size
            		  MemCopy( ((UINT8 *)control_Info + sizeof(CONTROL_INFO)) , (UINT8 *)ctrlFailSafe, defaults_size);
            		  MemCopy( ((UINT8 *)control_Info + sizeof(CONTROL_INFO) + defaults_size) , (UINT8 *)ctrlOptimal, defaults_size);
					break;
				}
			}
        	//Create group event using Refresh Id GUID
			if ( control_Info->ControlFlags.RefreshID )//EIP-105468
			{
				Status = CreateEventforIFR (control_Info);
				if (EFI_ERROR (Status))
				{
					i = Size;
					goto DONE;
				}
			}
			//EIP-148837
            /*if(IsRefreshIdSet) {
                ++gRefreshIdCount; //increament the refresh id control count
                NotifyContext = EfiLibAllocateZeroPool(sizeof(CONTROL_INFO));                
                if(NotifyContext == NULL)
			    {
				    i = Size;
				    goto DONE;
			    }
                MemCopy(NotifyContext, control_Info, sizeof(CONTROL_INFO));
                gBS->CreateEventEx (
                    EFI_EVENT_NOTIFY_SIGNAL,
                    EFI_TPL_CALLBACK,
                    (EFI_EVENT_NOTIFY)RefreshGroupOnCallBack,
                    (void*)NotifyContext,
                    &RefreshEventGroupId,
                    &RefreshIdEvent
                    );
                IsRefreshIdSet = FALSE;
                if(RefreshIdEvent == NULL)
			    {
                    i = Size;
                    goto DONE;
                }

                //store the Event and Context for this control, to be freed on exiting the application.
                gRefreshIdInfo = MemReallocateZeroPool(gRefreshIdInfo, sizeof(REFRESH_ID_INFO)*(gRefreshIdCount-1), sizeof(REFRESH_ID_INFO)*gRefreshIdCount);
                if(gRefreshIdInfo == NULL)
			    {
                    i = Size;
                    goto DONE;
                }
                gRefreshIdInfo[gRefreshIdCount-1].pEvent = RefreshIdEvent;
                gRefreshIdInfo[gRefreshIdCount-1].pNotifyContext = (UINT8*)NotifyContext;
            }*/
			while(defaultValue != NULL)
			{
				Temp=defaultValue;
				defaultValue = defaultValue->Next;
				MemFreePointer(&Temp);
			}

			controlOffset = AddControlToList(control_Info, controlSize);
			CreatePage(NewPageInfo, AllocatedPageSize, PageOffset, &controlOffset, sizeof(UINT32));
			MemFreePointer(&control_Info);

			if (controlType & ~CONTROL_TYPE_MASK)
			{
				controlOffset = 0;
				CreatePage(NewPageInfo, AllocatedPageSize, PageOffset, &controlOffset, sizeof(UINT32));
			}
		}

        MemFreePointer (&ctrlFailSafe);
        MemFreePointer (&ctrlOptimal);
		j= opHeader->Length;
		if (opHeader->Scope && controlType && addControl)
		{
			UINT32 scopeCount = 0;
			BOOLEAN scoped = TRUE;

			if(opHeader->OpCode == EFI_IFR_SUBTITLE_OP)
			{
				EFI_IFR_OP_HEADER *nextOpHeader = (EFI_IFR_OP_HEADER *)((UINT8 *)opHeader + opHeader->Length);
				if(nextOpHeader->OpCode != EFI_IFR_END_OP)
					scoped = FALSE;
			}

			while(scoped)
			{
				switch(((EFI_IFR_OP_HEADER*)(buff + i + j))->OpCode)
				{
				case EFI_IFR_ONE_OF_OPTION_OP:
					//j += sizeof(EFI_IFR_ONE_OF_OPTION);				//EIP71351 
					j += ((EFI_IFR_OP_HEADER*)(buff + i + j))->Length;   //Aptio giving length as 0xe(matches size of EFI_IFR_ONE_OF_OPTION) but in latest EDKII driver it is 0x1c.
					break;
				case EFI_IFR_END_OP:
					if(scopeCount)
					{
						scopeCount--;
						j += ((EFI_IFR_OP_HEADER*)(buff + i + j))->Length;
					}else
					{
						scoped = FALSE;
					}
					break;
				default:
					if(((EFI_IFR_OP_HEADER*)(buff + i + j))->Scope)
					{
						scopeCount++;
					}
					j += ((EFI_IFR_OP_HEADER*)(buff + i + j))->Length;
					break;
				}
				// Increase Control Index to account above control and final EFI_IFR_END_OP
				controlIndex++;
			}
		}

		//
		// Add Inconsistant Control for Control that have INCONSISTANT_IF embedded within
		// their scope. Eg. BOOLEAN | DATE | NUMERIC | ORDERED_LIST | STRING | TIME
		//
		if(Inconsistant)
		{
			BOOLEAN 	BackupgConditionOverForm = FALSE;
			Inconsistant = FALSE;
			IsRecursive = TRUE;
			BackupgConditionOverForm = gConditionOverForm;				//To have the current control as condptr.  If saving condition over form as condptr then it will hang
			gConditionOverForm = FALSE;
			_AddHpkControls(Handle, buff + i + opHeader->Length, j - opHeader->Length,
				NewPageInfo, AllocatedPageSize, PageOffset);
			gConditionOverForm = BackupgConditionOverForm;
			IsRecursive = FALSE;
		}
		//EIP : NO_SUBMIT_IF
		if(NoSubmitIf)
		{
			BOOLEAN 	BackupgConditionOverForm = FALSE;
			NoSubmitIf = FALSE;
			IsRecursive = TRUE;
			BackupgConditionOverForm = gConditionOverForm;		//To have the current control as condptr if has condition over form as condptr then it will hang
			gConditionOverForm = FALSE;
			_AddHpkControls(Handle, buff + i + opHeader->Length, j - opHeader->Length,
				NewPageInfo, AllocatedPageSize, PageOffset);
			gConditionOverForm = BackupgConditionOverForm;
			IsRecursive = FALSE;
		}

	   i= i+ j;
	};	
DONE:
    SETUP_DEBUG_UEFI("\n[TSE] Exiting _AddHpkControls\n");
	return i;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     AddControlToList
//
// Description:
//
// Parameter:     CONTROL_INFO *ControlInfo
//                UINT32 ControlSize
//
// Return value:  EFI_STATUS
//					      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 AddControlToList(CONTROL_INFO *ControlInfo, UINT32 ControlSize)
{
//	EFI_STATUS status = EFI_SUCCESS;
	UINT32 offset = 0;
	UINT32 u32Compensation = 0;

    SETUP_DEBUG_UEFI( "\n[TSE] Entering AddControlToList(), QuestionId: %d \n", ControlInfo->QuestionId );

#if TSE_DEBUG_MESSAGES
    if((gDbgPrint & PRINT_UEFI_PARSE)== PRINT_UEFI_PARSE)
         DebugShowControlInfo( ControlInfo->ControlPageID, ControlInfo) ;
#endif
    
  if(gIFRChangeNotify)
  {
    offset = _AdvAddControlToList(ControlInfo, ControlSize);
    if(offset)
    {
      goto DONE;
    }
  }
	u32Compensation = (sizeof(UINT64) - (ControlSize % sizeof(UINT64))) % sizeof(UINT64);

	if((ControlListOffset + ControlSize + u32Compensation ) >= ControlListSize)
	{
		//Allocate 4k at a time
		gControlInfo = MemReallocateZeroPool( gControlInfo, ControlListSize, ControlListSize + 4096 );
/*
		if(gControlInfo == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			offset = -1;
			goto DONE;
		}
*/
		ControlListSize+=4096;
	}

	MemCopy((UINT8 *)gControlInfo + ControlListOffset, ControlInfo, ControlSize);
	offset = ControlListOffset;
	ControlListOffset += (ControlSize + u32Compensation);

DONE:
    SETUP_DEBUG_UEFI( "\n[TSE] Exiting AddControlToList()\n");
    
	return offset;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    AddPageIdToList
//
// Description:
//
// Parameter:   PAGE_ID_INFO *NewPageIdInfo
//
// Return value: EFI_STATUS -
//					      EFI_SUCCESS -
//					      EFI_OUT_OF_RESOURCES -
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddPageIdToList(PAGE_ID_INFO *NewPageIdInfo)
{
	EFI_STATUS status = EFI_SUCCESS;

	UINT32 offset;
	UINT32 PageIdSize = sizeof(PAGE_ID_INFO);

    SETUP_DEBUG_UEFI( "\n[TSE] Entering AddPageIdToList(), PageClass: 0x%x,  PageSubClass: 0x%x,\n", NewPageIdInfo->PageClass, NewPageIdInfo->PageSubClass);

	 //@VgDebug
	if( PageIdInfoPtr == NULL )
		PageIdInfoOffset = PageIdInfoSize = 0; //EIP-73396 Removed (PageIdSize=0) since size is 0 the first PageInfo will not copy to PageIdInfoPtr

	if(PageIdInfoOffset + PageIdSize >= PageIdInfoSize)
	{
		 //Allocate 4k at a time
		PageIdInfoPtr = MemReallocateZeroPool( PageIdInfoPtr, PageIdInfoSize, PageIdInfoSize + 256 );
		if(PageIdInfoPtr == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		PageIdInfoSize+=256;
	}

	MemCopy((UINT8 *)PageIdInfoPtr + PageIdInfoOffset, NewPageIdInfo, PageIdSize);
	offset = PageIdInfoOffset;
	PageIdInfoOffset += PageIdSize;

	if(!PageIdListPtr)
	{
		PageIdListSize = 128;
		PageIdListPtr = EfiLibAllocateZeroPool(PageIdListSize);
		if(PageIdListPtr == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		PageIdListPtr->PageIdList[PageIdListPtr->PageIdCount] = offset;
		PageIdListPtr->PageIdCount = 1;
		PageIdListOffset = sizeof(PAGE_ID_LIST);
	}
	else
	{
		if(PageIdListOffset + sizeof(UINT32) >= PageIdListSize)
		{
			PageIdListPtr = MemReallocateZeroPool(PageIdListPtr, PageIdListSize, PageIdListSize + 128);
			if(PageIdInfoPtr == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}

			PageIdListSize += 128;
		}
		PageIdListPtr->PageIdList[PageIdListPtr->PageIdCount] = offset;
		PageIdListPtr->PageIdCount++;
		PageIdListOffset += sizeof(UINT32);
	}

DONE:
    SETUP_DEBUG_UEFI( "\n[TSE] Exiting AddPageIdToList(),  status = 0x%x \n" , status );
    
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     AddPageToList
//
// Description:
//
// Parameter:     PAGE_INFO *NewPageInfo
//                UINT32 PageSize
//
// Return value:  EFI_STATUS
//					      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddPageToList(PAGE_INFO *NewPageInfo, UINT32 PageSize)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINT32 offset;
	UINT32 ReallocSize=4096;

    SETUP_DEBUG_UEFI( "\n[TSE] Entering AddPageToList(),  PageFormID: %d \n", NewPageInfo->PageFormID );

#if TSE_DEBUG_MESSAGES
    if((gDbgPrint & PRINT_UEFI_PARSE)== PRINT_UEFI_PARSE)
        DebugShowPageInfo(NewPageInfo->PageFormID, NewPageInfo) ;
#endif 
    

  if(gIFRChangeNotify)
  {
    status = _AdvAddPageToList(NewPageInfo, PageSize);
    if(status == EFI_SUCCESS)
    {
      goto DONE;
    }
    status = EFI_SUCCESS;// EIP 88658  : Minisetup crashes after controller reconnection during Hii callback
  }
	if(PageInfoOffset + PageSize >= PageInfoSize)
	{
		if(ReallocSize < PageSize)
			ReallocSize = (PageSize & 0xFFFFF000) + 4096;
		PageInfoPtr = MemReallocateZeroPool( PageInfoPtr, PageInfoSize, PageInfoSize + ReallocSize ); //Allocate 4k at a time
		if(PageInfoPtr == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		PageInfoSize+=ReallocSize;
	}

	MemCopy((UINT8 *)PageInfoPtr + PageInfoOffset, NewPageInfo, PageSize);
	offset = PageInfoOffset;
	PageInfoOffset += PageSize;

	if(!PageListPtr)
	{
		PageListSize = 512;
		PageListPtr = EfiLibAllocateZeroPool(PageListSize);
		if(PageListPtr == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		/* Leave space for offset of Page 0 */
		PageListPtr->PageCount = 1;
		PageListPtr->PageList[PageListPtr->PageCount] = offset;
		PageListPtr->PageCount++;
		PageListOffset = sizeof(PAGE_LIST)+sizeof(UINT32);
	}
	else
	{
		if(PageListOffset + sizeof(UINT32) >= PageListSize)
		{
			PageListPtr = MemReallocateZeroPool(PageListPtr, PageListSize, PageListSize + 128);
			if(PageListPtr == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}

			PageListSize += 128;
		}
		PageListPtr->PageList[PageListPtr->PageCount] = offset;
		PageListPtr->PageCount++;
		PageListOffset += sizeof(UINT32);
	}

DONE:
    SETUP_DEBUG_UEFI( "\n[TSE] Exiting AddPageToList(),  status = 0x%x \n" , status ) ; 

	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    AddVariableToList
//
// Description:
//
// Parameter:
//
//
// Return value: EFI_STATUS
//					EFI_SUCCESS -
//					EFI_OUT_OF_RESOURCES -
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddVariableToList(VARIABLE_INFO *NewVariableInfo)
{
	EFI_STATUS status = EFI_SUCCESS;

	UINT32 offset;
	UINT32 VariableSize = sizeof(VARIABLE_INFO);

    SETUP_DEBUG_UEFI( "\n[TSE] Entering AddVariableToList(), VariableName:  %s\n", NewVariableInfo->VariableName);

	if(VariableInfoOffset + VariableSize >= VariableInfoSize)
	{
		//Allocate 4k at a time
		VariableInfoPtr = MemReallocateZeroPool( VariableInfoPtr, VariableInfoSize,
												VariableInfoSize + 256 );
		if(VariableInfoPtr == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		VariableInfoSize += 256;
	}

	MemCopy((UINT8 *)VariableInfoPtr + VariableInfoOffset, NewVariableInfo, VariableSize);
	offset = VariableInfoOffset;
	VariableInfoOffset += VariableSize;

	if(!VariableListPtr)
	{
		VariableListSize = 128;
		VariableListPtr = EfiLibAllocateZeroPool(VariableListSize);
		if(VariableListPtr == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		VariableListPtr->VariableList[VariableListPtr->VariableCount] = offset;
		VariableListPtr->VariableCount = 1;
		VariableListOffset = sizeof(VARIABLE_LIST);
	}
	else
	{
		if(VariableListOffset + sizeof(UINT32) >= VariableListSize)
		{
			VariableListPtr = MemReallocateZeroPool(VariableListPtr, VariableListSize,
													VariableListSize + 128);
			if(VariableListPtr == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}

			VariableListSize += 128;
		}
		VariableListPtr->VariableList[VariableListPtr->VariableCount] = offset;
		gnewCtrlVar = VariableListPtr->VariableCount;
		VariableListPtr->VariableCount++;
		// EIP : Display Error message variable exceeds Maximum variable supported in TSE
		if(VariableListPtr->VariableCount >= MAX_VARIABLE)
		{
			CHAR16 *Temp = L"Reached TSE Maximum supported variables";
			_DisplayErrorMessage(Temp);
			ASSERT(0);
		}
		VariableListOffset += sizeof(UINT32);
	}

DONE:
    SETUP_DEBUG_UEFI( "\n[TSE] Exiting AddVariableToList(),  status = 0x%x \n" , status );

	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     CreatePage
//
// Description:
//
// Parameter:     PAGE_INFO **PageInfo
//                UINT32 *AllocatedSize
//                UINT32 *Offset
//                VOID *Buff
//                UINT32 BuffSize
//
// Return value: EFI_STATUS
//					EFI_SUCCESS -
//					EFI_OUT_OF_RESOURCES -
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CreatePage(PAGE_INFO **PageInfo, UINT32 *AllocatedSize,
					   UINT32 *Offset, VOID *Buff, UINT32 BuffSize)
{
	EFI_STATUS status = EFI_SUCCESS;

    SETUP_DEBUG_UEFI( "\n[TSE] Entering CreatePage()\n");

	if(!(*AllocatedSize))
	{
		//creating a new page
		*PageInfo = EfiLibAllocateZeroPool(BuffSize);
		if(PageInfo == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}

		*AllocatedSize = BuffSize;
		MemCopy(*PageInfo, Buff, BuffSize);

		if((*PageInfo)->PageControls.ControlCount)
			*Offset = BuffSize;
		else //We have space to store one more offset
			//*Offset = BuffSize - sizeof((*PageInfo)->PageControls.ControlList[0]);
			*Offset = (UINT32)((UINTN)(&(*PageInfo)->PageControls.ControlList[0]) - (UINTN)(*PageInfo));
	}
	else
	{
		//adding offsets
		if(*Offset + BuffSize >= *AllocatedSize)
		{
			//Allocate 128 bytes at a time
			*PageInfo = MemReallocateZeroPool( *PageInfo, *AllocatedSize, *AllocatedSize + 128 );
			if(PageInfo == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}

			*AllocatedSize+=128;
		}
		MemCopy((UINT8 *)(*PageInfo) + *Offset, Buff, BuffSize);
		*Offset += BuffSize;
		(*PageInfo)->PageControls.ControlCount++;
	}

DONE:
    SETUP_DEBUG_UEFI( "\n[TSE] Exiting CreatePage(),  status = 0x%x \n" , status );
        
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    ParseForm
//
// Description:  Parse the HII Package for the Form Pack and parse the FormPack
//
// Parameter:    IFRPackage - The Header of the Package to parse.
//
// Return value: EFI_STATUS - Return the Status of the Parsing
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ParseForm(SETUP_LINK *Setup_Link)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_HII_PACKAGE_HEADER *pkgHdr;
	EFI_IFR_FORM_SET *formSet = NULL;
	EFI_IFR_FORM *form = (EFI_IFR_FORM *)NULL;
   AMI_EFI_IFR_FORM_MAP_METHOD *formMapMethod = (AMI_EFI_IFR_FORM_MAP_METHOD *) NULL;
   AMI_EFI_IFR_FORM_MAP *formMap = (AMI_EFI_IFR_FORM_MAP *) NULL;
	EFI_IFR_GUID_CLASS *guidClassOp;
	EFI_IFR_GUID_SUBCLASS *guidSubClassOp;
	EFI_IFR_OP_HEADER *opHeader;
    EFI_GUID  DriverHealthHiiGuid = EFI_HII_DRIVER_HEALTH_FORMSET_GUID;
    EFI_GUID  CredentialHiiGuid = EFI_HII_USER_CREDENTIAL_FORMSET_GUID;
    extern EFI_GUID *gFSetGuid;
    UINT16 FormSetTitle = 0 ;
	UINT32 formOffset = 0, ifOverformCounter = 0;
	UINT8 Opcode = 0;
	CONTROL_INFO *control_Info;

  UINT8  opCode = 0;
	UINT16 extendOpCode = 0;
	UINT16 fsClass = 0;
	UINT16 fsSubClass = 0;
	UINT32 controlOffset = 0;
	UINT32 varIndex = 0;
	UINTN  i = 0,formMapLength =0,formType = 0;
	UINTN jIndex = 0;

	PVAR_KEY_TABLE pVarTable;
	UINT32 allocatedPageSize = 0;
	PAGE_INFO *tmpPgInfo;

    UINT8 *ifrData = NULL;

    SETUP_DEBUG_UEFI ( "\n[TSE] Entering ParseForm()\n" );

	pkgHdr = (EFI_HII_PACKAGE_HEADER*)Setup_Link->FormSet;

  if(pkgHdr->Type != EFI_HII_PACKAGE_FORMS)
	{
    status = EFI_UNSUPPORTED;
		goto DONE;
	}
  ifrData = ((UINT8 *)pkgHdr) + sizeof(EFI_HII_PACKAGE_HEADER);

  while(i < pkgHdr->Length)
	{
		opHeader = (EFI_IFR_OP_HEADER*)(ifrData + i);

		switch(opHeader->OpCode)
		{
		case EFI_IFR_SUPPRESS_IF_OP:
		case EFI_IFR_DISABLE_IF_OP:
		case EFI_IFR_GRAY_OUT_IF_OP:
			if(updateformcondvars == 1)//EIP-120418 Support suppressif,grayoutif, DisableIf over form
			{
				updateformcondvars = 0;
				gConditionOverForm = TRUE;
				gConditionalOverFormPtr = (void*)opHeader;
			}
			PushScope(opHeader->OpCode);
			ifOverformCounter++;
			break;
		case EFI_IFR_FORM_SET_OP:
			formSet = (EFI_IFR_FORM_SET*)opHeader;
			
			FormSetTitle = formSet->FormSetTitle;
			
			if ( !ShowClassGuidFormsets( (TSE_EFI_IFR_FORM_SET*)formSet) ) //EIP-139099 If ClassGuid is matches then continue parsing to display formset
			{
				FormSetTitle = 0;//Clear FormSetTitle
				i += (pkgHdr->Length - opHeader->Length); //Change i value to end of Pkg to skip parsing forms,etc,.
				status = EFI_ABORTED;
				gConditionOverForm = FALSE;
				updateformcondvars = 1;
				break;
			}
			
			if ( HideDynamicFormsets(&formSet->Guid) ) //EIP-95647 Suppressing formsets mentioned in elink AMITSE_SUPPRESS_DYNAMIC_FORMSET_LIST
			{
				FormSetTitle = 0;
				i += (pkgHdr->Length - opHeader->Length);
				status = EFI_ABORTED;
				gConditionOverForm = FALSE;
				updateformcondvars = 1;
				break;
			}

			PushScope(opHeader->OpCode);

			if(_IsVarGuidPresent(&formSet->Guid, &varIndex) == FALSE)
			{
				varIndex = _AddFormSetVariable(&formSet->Guid);
			}

			for(pVarTable = &VarKeyTable ; pVarTable->Next; pVarTable= pVarTable->Next)
				;

			pVarTable->Next = EfiLibAllocateZeroPool(sizeof(VAR_KEY_TABLE));
			if(pVarTable->Next == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}

			pVarTable = pVarTable->Next;
			pVarTable->VarId = 0;
			pVarTable->Index = (UINT16)varIndex;

			// create the pages lookup table
			_InitFormsetLinks((char*)ifrData, PageListPtr ? PageListPtr->PageCount:1);

			// add NULL control above submenu in main
			controlOffset = 0;
			CreatePage(&FirstPage, &AllocatedFirstPageSize, &FirstPageOffset,
				&controlOffset, sizeof(UINT32));

			// add second null control for splitting the page in 2 halves
			if (TotalRootPages == 7)
			{
				controlOffset = 0;
				CreatePage(&FirstPage, &AllocatedFirstPageSize, &FirstPageOffset,
					&controlOffset, sizeof(UINT32));
			}

			control_Info = (CONTROL_INFO*)EfiLibAllocateZeroPool(sizeof(CONTROL_INFO));
			if(control_Info == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}

			// add the submenu control to main form  that points to this form.
			control_Info->ControlHandle = Setup_Link->Handle;
			control_Info->ControlType = CONTROL_TYPE_SUBMENU;
			control_Info->ControlDestPageID = PageListPtr ? ((UINT16)PageListPtr->PageCount):1 ;

			control_Info->ControlFlags.ControlVisible = 1;

            if(!IsGroupDynamicPages())  //EIP: 59971 
			    control_Info->ControlPtr = (VOID*)gFirstPageRef;

/*	What is this here for?

			controlInfo->ControlPtr = (UINTN)gSetupData[HiiIndex].FormSet +
				sizeof(EFI_HII_PACK_HEADER) +
				sizeof(EFI_IFR_FORM_SET) +
				TotalRootPages * sizeof(EFI_IFR_REF);
*/

			controlOffset = AddControlToList(control_Info, sizeof(CONTROL_INFO));
			CreatePage(&FirstPage, &AllocatedFirstPageSize, &FirstPageOffset,
				&controlOffset, sizeof(UINT32));
			MemFreePointer(&control_Info);

			TotalRootPages++;
			break;
		case EFI_IFR_FORM_OP:
        case EFI_IFR_FORM_MAP_OP: 
            if(opHeader->OpCode == EFI_IFR_FORM_OP)
                form = (EFI_IFR_FORM*)opHeader;
            else{
                formMap =(AMI_EFI_IFR_FORM_MAP *)opHeader;
                formMapMethod =(AMI_EFI_IFR_FORM_MAP_METHOD *)((UINT8 *)formMap + sizeof(AMI_EFI_IFR_FORM_MAP));
                formMapLength = sizeof(AMI_EFI_IFR_FORM_MAP);
                //
                // FormMap Form must contain at least one Map Method.
                //
                if (opHeader->Length < (formMapLength + sizeof(AMI_EFI_IFR_FORM_MAP_METHOD))) {
                    return EFI_INVALID_PARAMETER;
                }
                //
                // Try to find the standard form map method.
                //
                while (formMapLength < opHeader->Length) {
                    if (EfiCompareGuid((EFI_GUID *) (VOID *) &formMapMethod->MethodIdentifier, &StandardFormGuid)) {
                        formType = 1;
                        break;
                    }
                    formMapMethod ++;
                    formMapLength+= sizeof(AMI_EFI_IFR_FORM_MAP_METHOD);
                }
                if(!formType)
                    formMapMethod =(AMI_EFI_IFR_FORM_MAP_METHOD *)((UINT8 *)formMap + sizeof(AMI_EFI_IFR_FORM_MAP));
            }

			tmpPgInfo = (PAGE_INFO*)EfiLibAllocateZeroPool(sizeof(PAGE_INFO));
			if(tmpPgInfo == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}

			allocatedPageSize = PageOffset = 0;
			NewPageInfo = NULL;

            tmpPgInfo->PageFormID = (opHeader->OpCode == EFI_IFR_FORM_OP) ? form->FormId : formMap->FormId;
			tmpPgInfo->PageID = PageListPtr ? (UINT16) PageListPtr->PageCount : 1;
			tmpPgInfo->PageIdIndex = _GetPageIdIndex(&formSet->Guid, fsClass, fsSubClass);
			tmpPgInfo->PageHandle = Setup_Link->Handle;
			tmpPgInfo->PageParentID = PageListPtr ? _GetPageParent(PageListPtr->PageCount) : 0;
   			tmpPgInfo->PageSubTitle =  (opHeader->OpCode == EFI_IFR_FORM_OP) ?  form->FormTitle :formMapMethod->MethodTitle;
            if(formType &&opHeader->OpCode == EFI_IFR_FORM_MAP_OP ){
                tmpPgInfo->PageFlags.PageStdMap = 1;
            }
            else{
                tmpPgInfo->PageFlags.PageStdMap = 0;
            }
   			//tmpPgInfo->PageSubTitle = form->FormTitle;

			

			for (jIndex = 0; jIndex < gGuidDumpCount; jIndex ++)			//EIP64253 Check for offline vfr's
			{
				if (EfiCompareGuid (&gGuidDump [jIndex], &formSet->Guid))
				{
					break;
				}
			}
			if (jIndex == gGuidDumpCount)				//EIP64253 If offline vfr dont hide it
			{
			//EIP 94424 : Some form can't normal display when add Hii item will in runtime during
				//EIP:68341 Support for displaying FormSet Title
            	if (tmpPgInfo->PageParentID == 0)
            	{
                	tmpPgInfo->PageSubTitle = FormSetTitle ;
            	}
			//Check for Dynamic Page Flag
				if (tmpPgInfo->PageParentID == 0 && IsGroupDynamicPages())			//PageParentID is 0 && SDL token is true
				{
					//then set as dynamic page
	//                if (!EfiCompareGuid (&formSet->Guid, &DriverHealthHiiGuid) || (NULL != gSfHandles))         //EIP 57661 Not to show the form with EFI_HII_DRIVER_HEALTH_FORMSET_GUID
	//                {
	                if ((NULL == gSfHandles) && (!EfiCompareGuid (&formSet->Guid, &DriverHealthHiiGuid)) && (!EfiCompareGuid (&formSet->Guid, &CredentialHiiGuid)) )
	                {
	                    tmpPgInfo->PageFlags.PageDynamic = TRUE ;
	                }
	                if ((NULL == gSfHandles) && (EfiCompareGuid (&formSet->Guid, &DriverHealthHiiGuid)))			//EIP174938 if driverhealth page we have to not consider it as dynamic page so returning aborted
	                {																								//If not returning aborted then arrow will displayed
	                	status = EFI_ABORTED;
	                }
	//                }    
					tmpPgInfo->PageFlags.PageVisible = TRUE;
					if ( tmpPgInfo->PageFlags.PageDynamic)  //EIP-151552 Title is changing to MAIN and causing crashing while navigating from dynamic page to root page
					{
						tmpPgInfo->PageParentID = gDynamicParentPage;
					}
				}
	            if( (tmpPgInfo->PageParentID == 0) && (NULL != gSfHandles))
	            {
	                if ((NULL == gFSetGuid) && (!EfiCompareGuid (&formSet->Guid, &DriverHealthHiiGuid)) && (!EfiCompareGuid (&formSet->Guid, &CredentialHiiGuid)) )
	                {
	                    tmpPgInfo->PageFlags.PageVisible = FALSE;
	                }
	                else if ((NULL != gFSetGuid) && (EfiCompareGuid (&formSet->Guid, gFSetGuid)))
	                {
	                    tmpPgInfo->PageFlags.PageVisible = FALSE;
	                }
	                else
	                    tmpPgInfo->PageFlags.PageVisible = TRUE;
				}
            }
			/*
			 * Add tmpPgInfo to PageInfo and PageList Structures.
			 * Memory for tmpPgInfo->PageControls.ControlList[0]
			 * will be allocated later when adding controls
			 */
			CreatePage(&NewPageInfo, &allocatedPageSize, &PageOffset,
				tmpPgInfo, sizeof(PAGE_INFO));
			MemFreePointer(&tmpPgInfo);

			i += _AddHpkControls(Setup_Link->Handle, (UINT8*)opHeader, pkgHdr->Length - i,
					&NewPageInfo, &allocatedPageSize, &PageOffset);
			AddPageToList(NewPageInfo, PageOffset);
			// EIP: Display Error message when Control count exceeds MAX_CONTROLS supported 
			if(NewPageInfo->PageControls.ControlCount >= MAX_CONTROLS)
			{
				CHAR16 *Temp = L"Reached TSE Maximum supported Controls";
				_DisplayErrorMessage(Temp);
				ASSERT(0);
			}
			MemFreePointer(&NewPageInfo);
			/* The Form Opcode Length is already added */
			continue;

		case EFI_IFR_GUID_OP:
			extendOpCode = (UINT8)*((UINT8*)opHeader + sizeof(EFI_IFR_GUID));
			switch(extendOpCode)
			{
			case EFI_IFR_EXTEND_OP_LABEL:       //0x0
				break;
			case EFI_IFR_EXTEND_OP_BANNER:      //0x1
				break;
			case EFI_IFR_EXTEND_OP_TIMEOUT:     //0x2
				break;
			case EFI_IFR_EXTEND_OP_CLASS:       //0x3
				guidClassOp = (EFI_IFR_GUID_CLASS*)opHeader;
				fsClass = guidClassOp->Class;
				break;
			case EFI_IFR_EXTEND_OP_SUBCLASS:    //0x4
				guidSubClassOp = (EFI_IFR_GUID_SUBCLASS*)opHeader;
				fsSubClass = guidSubClassOp->SubClass;
				break;
			default:
				break;
			}

			break;
    case EFI_IFR_VARSTORE_OP:        // 0x24
    case EFI_IFR_VARSTORE_NAME_VALUE_OP: //0x25
    case EFI_IFR_VARSTORE_EFI_OP:    // 0x26
			_AddVariable((UINT8*)opHeader, Setup_Link->Handle);

			break;
		case EFI_IFR_DEFAULTSTORE_OP:
			break;
		case EFI_IFR_END_OP:
			PopScope(&opCode);
			if(EFI_IFR_SUPPRESS_IF_OP == opCode || EFI_IFR_GRAY_OUT_IF_OP == opCode || EFI_IFR_DISABLE_IF_OP == opCode)
			{
				--ifOverformCounter;//Resetting flags
				gConditionOverForm = FALSE;
				updateformcondvars = 1;
			}

			if(opCode == EFI_IFR_FORM_SET_OP)
			{
				if(FSetLinks !=NULL)
				{
					MemFreePointer(&FSetLinks);
					FSetLinks = NULL;
				}
				i += sizeof(EFI_HII_PACKAGE_HEADER);
			}
			// To match the Scoping. Don't abort the parsing.
			// Suppressif in the Form level need to be supported.
			/*
			else0
			{
				status = EFI_ABORTED;
				goto DONE;
			}
			*/
			break;
		default:
			if(opHeader->Scope)
				PushScope(opHeader->OpCode);
			break;
		}

		i += opHeader->Length;
	}

	_CleanVarKeyTable();
	Setup_Link->Added = 1;

DONE:
    SETUP_DEBUG_UEFI ("\n[TSE] Exiting ParseForm(),   status = 0x%x \n" , status ); 
	return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   _AdvAddControlToList
//
// Description: Add control info the control list
//
// Input:	CONTROL_INFO *ControlInfo - Pointer to the CONTROL_INFO
//          UINT32 ControlSize - Size the control info
//
// Output:	UINT32 offset - Return the control list offset
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 _AdvAddControlToList(CONTROL_INFO *ControlInfo, UINT32 ControlSize)
{
  CONTROL_INFO *ctrlInfo = (CONTROL_INFO*)gControlInfo;
  UINT32 ctrlSize = 0;
	UINT32 offset = 0;
	UINT32 u32Compensation = 0;
  UINT32 ctrlListOffset = 0;

  SETUP_DEBUG_UEFI( "\n[TSE] Entering _AdvAddControlToList()\n");

  do
  {
    if(ctrlInfo == NULL)
    {
      break; //If ctrlInfo is invalid 
    }

    if(ctrlListOffset == ControlListOffset)
    {
      break;
    }

    //ctrlSize = sizeof(CONTROL_INFO) + ctrlInfo->ControlDataWidth * 2;
	ctrlSize = sizeof(CONTROL_INFO) + (2* ctrlInfo->ControlDataWidth) + (ctrlInfo->DefaultStoreCount * (sizeof(UINT16)+ctrlInfo->ControlDataWidth));
    if(ctrlInfo->ControlHandle == NULL && ctrlSize == ControlSize)
    {
      // Add the Control
      MemCopy(ctrlInfo, ControlInfo, ControlSize);
      offset = ctrlListOffset;
      break;
    }


    // Skip to the Next Control in gControl
    u32Compensation = (sizeof(UINT64) - (ctrlSize % sizeof(UINT64))) % sizeof(UINT64);
    ctrlListOffset += (ctrlSize + u32Compensation);
    ctrlInfo = (CONTROL_INFO *)((UINT8 *)ctrlInfo + ctrlSize + u32Compensation);
  }while(TRUE);

    SETUP_DEBUG_UEFI( "\n[TSE] Exiting _AdvAddControlToList()\n");

	return offset;
}

VOID UpdateCtrlDestPageID(VOID * Handle, UINT16 NewPageID)
{
  UINT32 page = PARSE_START_INDEX;
  UINT32 control = 0;

  for(;page < PageListPtr->PageCount; page++)
  {
    PAGE_INFO *pgInfo = (PAGE_INFO *)((UINT8 *)PageInfoPtr + PageListPtr->PageList[page]);

    if(pgInfo->PageHandle == Handle)
    {
      for(control = 0;control < pgInfo->PageControls.ControlCount; control++)
      {
        CONTROL_INFO *controlInfo = NULL;

        controlInfo = (CONTROL_INFO*)((UINT8 *)gControlInfo + pgInfo->PageControls.ControlList[control]);
        if((NewPageID < controlInfo->ControlDestPageID) && (controlInfo->ControlDestPageID != 0xFFFF))
        {
          controlInfo->ControlDestPageID--;
        }
      }
    }
  }

}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   _AdvAddPageToList
//
// Description: Add page into to the page list
//
// Input:	PAGE_INFO *NewPageInfo - Pointer to new page info structure
//          UINT32 PageSize - Page into size
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _AdvAddPageToList(PAGE_INFO *NewPageInfo, UINT32 PageSize)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT32 ii = 0;
  UINT16 pageNo=0;

  SETUP_DEBUG_UEFI( "\n[TSE] Entering _AdvAddPageToList()\n");

  for(ii = PARSE_START_INDEX; ii < PageListPtr->PageCount; ii++)
  {
    PAGE_INFO *pageInfo = (PAGE_INFO *)((UINT8 *)PageInfoPtr + PageListPtr->PageList[ii]);

    if(pageInfo->PageHandle == (VOID *)(UINTN)0xFFFF)
    {
      if(pageInfo->PageFormID == NewPageInfo->PageFormID)
      {
        if(pageInfo->PageControls.ControlCount == NewPageInfo->PageControls.ControlCount)
        {
		  pageNo = NewPageInfo->PageID;
          pageInfo->PageHandle = NewPageInfo->PageHandle;      //EIP-80424
		  // Updated in old page location itself
          status = _ReplacePageWithNewPage(pageInfo, NewPageInfo, PageSize);
        }else
        {
          status = _InvalidateExistingPage(pageInfo, NewPageInfo);
          status = EFI_UNSUPPORTED;
        }
        break;
      }
    }
  }

  if(pageNo)
  {
	// Search in FSetLink for the Page and update PageID and ParentPageID
	for(ii = 0; ii < FSetLinks->PageCount; ii++)
	{
		if(FSetLinks->PageLink[ii].FormID != NewPageInfo->PageFormID)
		{
			if(FSetLinks->PageLink[ii].ParentPageID == pageNo)
			{
	  			FSetLinks->PageLink[ii].ParentPageID = NewPageInfo->PageID;
			}

			if(FSetLinks->PageLink[ii].PageNum > pageNo)
			{
				FSetLinks->PageLink[ii].PageNum--;
			}
		}
		else
		{
			//FSetLinks->PageLink[ii].ParentPageID = NewPageInfo->PageParentID;
			FSetLinks->PageLink[ii].PageNum = NewPageInfo->PageID;
		}

		if(FSetLinks->PageLink[ii].ParentPageID > pageNo)
			FSetLinks->PageLink[ii].ParentPageID--;

	}

	for(ii = PARSE_START_INDEX; ii < PageListPtr->PageCount; ii++)
	{
		PAGE_INFO *pageInfo = (PAGE_INFO *)((UINT8 *)PageInfoPtr + PageListPtr->PageList[ii]);
		if(pageInfo->PageHandle == NewPageInfo->PageHandle)
		{
			if(pageInfo->PageParentID == pageNo)
	  			pageInfo->PageParentID = NewPageInfo->PageID;

			if(pageInfo->PageParentID > pageNo)
				pageInfo->PageParentID--;
		}
	}

	UpdateCtrlDestPageID(NewPageInfo->PageHandle, pageNo);
  }

    SETUP_DEBUG_UEFI( "\n[TSE] Exiting _AdvAddPageToList(),  status = 0x%x \n" , status );

  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _ReplacePageWithNewPage
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _ReplacePageWithNewPage(PAGE_INFO *OldPageInfo, PAGE_INFO *NewPageInfo, UINT32 PageSize)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT32 page = PARSE_START_INDEX;
  UINT32 control = 0;
    
    SETUP_DEBUG_UEFI( "\n[TSE] Entering _ReplacePageWithNewPage()\n");


  // Go thru NewPageInfo CtrlList and update Control PageId
  for(;control < NewPageInfo->PageControls.ControlCount; control++)
  {
    CONTROL_INFO *controlInfo = NULL;

    controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + NewPageInfo->PageControls.ControlList[control]);

    // Update the ControlDestPageID if it pointing to the same page.
    if(controlInfo->ControlDestPageID == controlInfo->ControlPageID)
        controlInfo->ControlDestPageID = OldPageInfo->PageID;

    controlInfo->ControlPageID = OldPageInfo->PageID;
  }

  // Go thru all PageList with the same Handle as NewPageInfo and
  // Go thru their CtrlList and Update any destination PageID that
  // refers this page
  for(;page < PageListPtr->PageCount; page++)
  {
    PAGE_INFO *pgInfo = (PAGE_INFO *)((UINT8 *)PageInfoPtr + PageListPtr->PageList[page]);

    if(pgInfo->PageHandle == NewPageInfo->PageHandle)
    {
      for(control = 0;control < pgInfo->PageControls.ControlCount; control++)
      {
        CONTROL_INFO *controlInfo = NULL;

        controlInfo = (CONTROL_INFO*)((UINT8 *)gControlInfo + pgInfo->PageControls.ControlList[control]);
        if(_GetPageNumFromFormID(NewPageInfo->PageFormID) == controlInfo->ControlDestPageID)
        {
          controlInfo->ControlDestPageID = OldPageInfo->PageID;
        }
      }

	  if(pgInfo->PageParentID == NewPageInfo->PageID)
		  pgInfo->PageParentID = OldPageInfo->PageID;
    }
  }

  // Update NewPageInfo PageId and ParentPageId
  NewPageInfo->PageID = OldPageInfo->PageID;
//  NewPageInfo->PageParentID = OldPageInfo->PageParentID;
  // Copy NewPageInfo to pageInfo
  MemCopy(OldPageInfo, NewPageInfo, PageSize);

    SETUP_DEBUG_UEFI( "\n[TSE] Exiting _ReplacePageWithNewPage(),  status = 0x%x \n" , status );

  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _InvalidateExistingPage
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _InvalidateExistingPage(PAGE_INFO *OldPageInfo, PAGE_INFO *NewPageInfo)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT32 page = 0;

    SETUP_DEBUG_UEFI( "\n[TSE] Entering _InvalidateExistingPage()\n");

  // Search thru gPages for pages with Controls with destination page
  // that refer OldPage and change them to point to NewPage
  for(page = PARSE_START_INDEX; page < PageListPtr->PageCount; page++)
  {
    UINT32 control = 0;
    PAGE_INFO *pgInfo = (PAGE_INFO *)((UINTN)PageInfoPtr + PageListPtr->PageList[page]);

    if(pgInfo->PageHandle == NewPageInfo->PageHandle)
    {
      for(control = 0; control < pgInfo->PageControls.ControlCount; control++)
      {
        CONTROL_INFO *controlInfo = NULL;

        controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pgInfo->PageControls.ControlList[control]);
        if(controlInfo->ControlDestPageID == _GetPageNumFromFormID(NewPageInfo->PageFormID))
        {
          controlInfo->ControlDestPageID = NewPageInfo->PageID;
        }
      }
    }
  }
  //EIP: 108987 May cause circular page reference.
  //NewPageInfo->PageParentID = OldPageInfo->PageParentID;

  SETUP_DEBUG_UEFI( "\n[TSE] Exiting _InvalidateExistingPage(),  status = 0x%x \n" , status )  ;

  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    RefreshGroupOnCallBack
//
// Description: Callback function which refreshes Controls of a Group which are
//				set with refresh Id
//
// Parameter:   EFI_EVENT Event, VOID *Context
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RefreshGroupOnCallBack(EFI_EVENT Event, VOID *Context)
{
	EFI_STATUS 		Status = EFI_SUCCESS;
	CONTROL_INFO 	*control_Info;
	UINT16 			Key;
	
	control_Info = (CONTROL_INFO*)Context;
	Key = UefiGetControlKey (control_Info);
			
	//refresh the control
	Status = UefiRefershQuestionValueNvRAM (control_Info);

	if (UefiIsInteractive (control_Info))
	{
		UefiPreControlUpdate (control_Info);
		Status = CallFormCallBack (control_Info, Key, 0, AMI_CALLBACK_CONTROL_UPDATE);//EIP-53480: Updated the action to AMI_CALLBACK_CONTROL_UPDATE   	 
	}

	//check if the control is in the current page, and redraw only then.
	if((Status == EFI_SUCCESS) && (control_Info->ControlPageID == gApp->CurrentPage))
	{
		gApp->CompleteRedraw = TRUE;
	}
}
//EIP-105468 Starts
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    CreateEventforIFR
//
// Description:	To create Event if any control has RefreshID opcode
//
//
// Parameter:   CONTROL_INFO*
//
// Return value:	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//#define EFI_REFRESH_ID_GUID    { 0x68a6632a, 0x5120, 0x45c3, 0x9b, 0x8e, 0xfc, 0xbf, 0x8c, 0xa0, 0xe7, 0x2e }
EFI_STATUS CreateEventforIFR (CONTROL_INFO *control_Info )
{
	EFI_STATUS Status = EFI_SUCCESS;
   CONTROL_INFO *NotifyContext = (CONTROL_INFO*)NULL;
   EFI_EVENT RefreshIdEvent = (EFI_EVENT)NULL;
	UINTN i = 0;

	//EFI_GUID    RefreshIDGuid = EFI_REFRESH_ID_GUID;	
	//MemCopy( &RefreshEventGroupId, &RefreshIDGuid, sizeof(EFI_GUID) );
//	MemCopy( &RefreshEventGroupId, &(((AMI_EFI_IFR_REFRESH_ID *)control_Info->ControlPtr)->RefreshEventGroupId), sizeof(EFI_GUID) );
	//Create group event using Refresh Id GUID

	++gRefreshIdCount; //increament the refresh id control count
	NotifyContext = EfiLibAllocateZeroPool(sizeof(CONTROL_INFO));                
	if(NotifyContext == NULL)
	{
		Status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
	MemCopy(NotifyContext, control_Info, sizeof(CONTROL_INFO));
	gBS->CreateEventEx (
		EFI_EVENT_NOTIFY_SIGNAL,
		EFI_TPL_CALLBACK,
		(EFI_EVENT_NOTIFY)RefreshGroupOnCallBack,
		(void*)NotifyContext,
		&RefreshEventGroupId,
		&RefreshIdEvent
		);
	if(RefreshIdEvent == NULL)
	{
		Status = EFI_UNSUPPORTED;
      goto DONE;
	}

	//store the Event and Context for this control, to be freed on exiting the application.
	gRefreshIdInfo = MemReallocateZeroPool(gRefreshIdInfo, sizeof(REFRESH_ID_INFO)*(gRefreshIdCount-1), sizeof(REFRESH_ID_INFO)*gRefreshIdCount);
	if(gRefreshIdInfo == NULL)
	{
		Status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
	gRefreshIdInfo[gRefreshIdCount-1].pEvent = RefreshIdEvent;
	gRefreshIdInfo[gRefreshIdCount-1].pNotifyContext = (UINT8*)NotifyContext;
DONE:
	return Status;
}
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
