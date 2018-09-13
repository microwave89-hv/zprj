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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Hii.c $
//
// $Author: Premkumara $
//
// $Revision: 59 $
//
// $Date: 9/05/14 2:40p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Hii.c $
// 
// 59    9/05/14 2:40p Premkumara
// Moved GetSetDefaultsFromControlPtr() function from Uefi2.1\Hii.c to
// TseAdvanced.c
// 
// 58    8/28/14 12:35p Premkumara
// [TAG]  		EIP175492
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Refresh_ID is not working in  for static and dynamic
// controls
// [RootCause]  	RefreshGroupOnCallBack was not getting called after
// signaling the RefreshId Event due to incorrect RefreshEventGroupId
// [Solution]  	Assigning correct RefreshEventGroupId to the RefreshId
// Event so that RefreshGroupOnCallBack will get called after signaling
// the Event
// [Files]  		Hii.c
// 
// 57    8/28/14 6:51a Premkumara
// [TAG]	EIP93340
// [Category]	Improvement
// [Description]	- Defaults can be given to string type controls using tag
// "Default = STRING_TOKEN(STR_DEFAULT_STRING)".
// - New token TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL is introduced for
// this support.
// - Enabling this TSE_SUPPORT_DEFAULT_FOR_STRING_CONTROL token will
// display default string mention in setup.
// - On loading optimal defaults also string will load default mentioned
// in default value tag.
// [Files] AMITSE.sdl, HiiString21.c, TseAdvanced.c, MiniSetupExt.c, Hii.c
// 
// 56    5/02/14 12:44a Arunsb
// [TAG]	EIP150526
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	TSE hangs on disconnecting and connecting the RAID driver
// [Root Cause]	Process pack updated on processing the existing pack
// update
// [Solution]	First we getting remove and new pack. 
// On getting this TSE starts processing the pack(ProcessPackNotification)
// but on processing the pack itself we getting notification again for
// remove and add.
// So again process pack happens inside notification
// itself(IFRChangeNotifyFn), this processing should not happen inside
// notification so enabled flag gEnableProcessPack in PageHandleAction.
// [Files]	hii.c, minisetupext.c and page.c
// 
// 55    2/11/14 8:53p Arunsb
// [TAG]	EIP132359
// [Category]	Bug Fix
// [Root Cause]	The ParentPageID in the destination page of the Ref3
// control is not updated.
// [Solution]	In the function UpdateIFRRefXControls, 
// update the ParentPageID in the destination page of the Ref3 control.
// [Files]	hii.c
// 
// 54    12/04/13 2:54a Premkumara
// [TAG]	EIP139099
// [Category]	New Feature
// [Description]	Supress formset other than
// EFI_HII_PLATFORM_SETUP_FORMSET_GUID and
// EFI_HII_DRIVER_HEALTH_FORMSET_GUID through elink based on token
// [Files]	AMITSE.sdl, AMITSE.mak, CommonOem.c, Hii.c, Parse.c,
// TseUefiHii.h
// 
// 53    6/10/13 12:10p Arunsb
// EIP122907. Refresh opcode event stopped when its pack removed
// 
// 52    5/22/13 10:57a Arunsb
// Read write opcodes variable number retrieved in special way using
// GetRWVariableID function.
// 
// 51    5/21/13 1:31a Arunsb
// [TAG]  		EIP122350
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Setup hangs on first goto after entering from Shell twice
// [RootCause]  	HiiExit not happened for all the cases so offsets behaved
// abruptly
// [Solution]  	HiiExit invoked for all the possible cases
// [Files]  		Hii.c
// 
// 50    4/18/13 5:56a Arunsb
// [TAG]  		EIP105468
// [Category]  	New Feature
// [Description]  	Support for EFI_IFR_REFRESH_ID opcode for Offline
// 
// 49    4/17/13 2:57p Arunsb
// [TAG]  		EIP109812, 107774
// [Category]  	Improvement
// [Description]  	Provide support for EFI_IFR_TYPE_REF and EFI_IFR_REF5
// [Files]  		Hii.c, HiiCallback.c, Parse.c and TseUefiHii.h
// 
// 48    4/16/13 9:40a Arunsb
// Missed HII structures added in TSE itself.
// 
// 47    4/02/13 8:08a Arunsb
// [TAG]  		EIP113919, EIP114842
// [Category]  	Improvement
// [Description]  	Provide support for EFI_IFR_WRITE, EFI_IFR_READ,
// EFI_IFR_GET, EFI_IFR_SET and EFI_IFR_MAP_OP.
// [Files]  		Setupdata.h, ctrlcond.c, expression.c, hii.c and parse.c
// 
// 46    3/25/13 8:06a Premkumara
// [TAG]  		EIP105468
// [Category]  	New Feature
// [Description]  	Support for EFI_IFR_REFRESH_ID opcode for Offline
// Parsing
// [Files]  		Parse.c, Hii.c, Setupdata.h
// 
// 45    2/25/13 10:57a Blaines
// [TAG] - EIP 104273
// [Category] - Action Item
// [Description] -  Provide ability to dump the Hii Pack from the Setup as
// part TSE debug Infrastructure. It should dump the Pack updates on Hii
// notification also.
// So it can be used to debug the issue.
// [Files] - ForBrowser2.c,  Hii.c,  HiiNotificationHandler.c,
// UefiWapper.c,  TseUefiHii.h
// 
// 44    11/09/12 2:33a Arunsb
// EIP 105965 : No. of root pages can be more than hii handle because of
// AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST_SUPPORT
// 
// 43    10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 21    10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 41    9/18/12 2:14a Rajashakerg
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
// 40    9/17/12 6:22a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 38    9/08/12 11:42a Arunsb
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
// 37    5/29/12 4:44a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 36    5/28/12 11:14a Premkumara
// [TAG]  		EIP83080
// [Category]  	Improvement
// [Description]  	Support REF4 type control.
// [Files]  		TseDrvHealth.h, Hii.c
// 
// 35    5/27/12 3:29a Arunsb
// [TAG]  		EIP90809
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Setup hang
// [RootCause]  	gFailsafeDefaults memory corruption between
// _MergeVariableListAndInfo and TseVarBuildAMIDefaults
// [Solution]  	Removed the memory corruption
// [Files]  		Hii.c
// 
// 34    2/03/12 4:49a Rajashakerg
// Defaults not saved for special variables.
// 
// 33    12/07/11 3:11p Arunsb
// [TAG]  		EIP75588
// [Category]  	New Feature
// [Description]  	Support for queuing UpdatePack notifications
// [Files]  		frame.c, page.c, formbrowser2.c, hii.c, hiicallback.c,
// hiinotificationhandler.c, tseuefihii.h and uefi21wapper.c
// 
// 32    12/05/11 5:51a Rajashakerg
// [TAG]  		EIP76381 
// [Category]  	Improvement
// [Description]  	Performance: Improving variable data load and usage
// [Files]  		callback.c, minisetupext.c, variable.c, variable.h,
// minisetup.h, Hii.c, FormBrowser2.c
// 
// 31    11/30/11 1:36p Premkumara
// [TAG]  		EIP75352
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		Boot.c, bbs.c, TseAdvanced.c, Special.c, Variable.c,
// TseLiteHelper.c, PopupSel.c, AddBootOption.c, Hii.c, FormBrowser2.c
// 
// 30    11/30/11 6:36a Premkumara
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
// 29    11/28/11 2:23a Premkumara
// [TAG]  		EIP75384 
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		UefiWapper.c, Hii.c, Expression.c, CtrlCond.c, PopupSel.c,
// Minisetupext.c, Menu.c, Date.c, Ezport\Stylecommon.c,
// EzportPlus\StyleCommon.c,
// 
// 28    11/22/11 1:00p Arunsb
// EIP72540 offline pages not included in run time parsing. Extra
// provision provided to hide particular page. But this needs
// customization.
// 
// 27    11/14/11 2:43p Blaines
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
// 26    11/14/11 4:22a Arunsb
// [TAG]  		EIP72540
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Advance page disappear on using 4.6.2_TSE_2_14_1219
// [RootCause]  	Offline pages also considered in dynamic parsing
// [Solution]  	Offline pages are not considered in dynamic parsing
// [Files]  		hii.c and parse.c.
// 
// 25    7/19/11 10:50a Blaines
// [TAG] - EIP 63262
// [Category]- Defect
// [Symptom]- Setup page display problem on rose city.
// When SETUP_GROUP_DYNAMIC_PAGES is enabled and Network Stack is enabled,
// the "iSCSI" menu is listed as a dynamic page in advanced menu but only
// 3 of 4 "Port Configuration" pages shows up. The TSE dynamic page count
// is incorrect.
// 
// [Solution]- In the functions (RTIfrProcessRunTimeForms,
// HandleNewIFRPack, HandleRemoveIFRPack, HandleAddIFRPack), make sure the
// nvram cache is updated by calling
// VarUpdateVariable(VARIABLE_ID_DYNAMIC_PAGE_COUNT) when updating
// "DynamicPageCount" variable name. 
// .
// [Files] -  Hii.c, Minisetup.h, Variable.h
// 
// 24    7/01/11 3:27a Arunsb
// Removed unwanted header for chm file creation.
// 
// 23    6/30/11 4:17a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Sets the driver health support variable.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 22    6/28/11 8:26a Arunsb
// EIP56405: Commented the build time parsing code.
// Name value not supported by current vfr compiler.
// Uncomment the codes once vfr compiler supports it.
// 
// 21    6/23/11 4:03p Rajashakerg
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
// 20    6/22/11 4:47p Arunsb
// [TAG]  		EIP56405
// [Category]  	New Feature
// [Description]  	Support for EFI_IFR_VARSTORE_NAME_VALUE opcode
// [Files]  		Hii.c, parse.c and uefi21wapper.c
// 
// 19    6/20/11 10:39a Rajashakerg
// [TAG]  		EIP57402 
// [Category]  	New Feature
// [Description]  	Support for EFI_IFR_DEFAULT_2 opcode.
// [Files]  		Hii.c
// 
// 18    6/01/11 5:22p Blaines
// [TAG]  		61122
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	If SETUP_ORPHAN_PAGES_AS_ROOT_PAGE=1, HiiExit() will cause
// an ASSERT in pool.c if debug_mode is enabled.
// [RootCause]  	HiiExit() exit attempts to free gSetupData elements
// associated with orphaned forms..
// [Solution]  	Only free gSetupData[i].FormSet if
// gSetupData[i].FormSetLength is non-zero.
// [Files]  		Hii.c
// 
// 17    4/29/11 4:41p Arunsb
// For 2.13 public patch release IFR RefX feature is omitted.
// 
// 14    3/28/11 5:08p Rajashakerg
// [TAG]  		EIP56413
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_RESET_BUTTON opcode
// [Files]  		ezport.c, minisetupext.h, ResetButton.c, ResetButton.h,
// Hii.c, TseUefiHii.h, Uefi21Wapper.c, hii.h, Uefi20Wapper.c
// 
// 13    2/10/11 1:44p Blaines
// [TAG] - EIP 53146
// [Category]- New Feature
// [Modification] - Update DynamicPageCount variable on HandleNewIFRPack,
// HandleRemoveIFRPack, and HandleAddIFRPack notifications.
// 
// 12    2/10/11 12:32p Blaines
// [TAG] - EIP 53146
// [Category]- New Feature
// [Description] -Add the support to Move the Dynamic IFR Pages under
// subpages. It should be customizable to move around.
// 
// 11    12/28/10 12:31p Madhans
// To update the Tag of EIp 46998. UEFI option ROM menus disappear in
// Setup when certain options are selected. 
// No file changed but Comment updated right
// 
// 10    12/02/10 2:38p Madhans
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
// 18    8/12/10 1:11p Blaines
// EIP-40946 : Fix root page processing to support Award Style setup.
// 
// 17    7/07/10 7:47p Madhans
// To fix the Variables when new forms dynamically added.
// 
// 16    7/07/10 7:45p Madhans
// Changes to Support Adding Conditions to Suppress or Grayout the Special
// controls.
// 
// 15    6/17/10 2:46p Madhans
// Fix in Classcode/Subclass finding function.
// 
// 14    6/14/10 7:14p Madhans
// Dynamic parsing support
// 
// 13    6/14/10 7:04p Blaines
// Fix to correctly check if FormSet length has changed and if so Parse
// it. This fixes the issue with duplicate ClassID and SubClassID.
// 
// 12    3/11/10 5:42p Madhans
// Coding Standards Update
//
// 11    2/19/10 8:39p Madhans
//
// 10    2/19/10 8:35p Madhans
// Function header fix
//
// 7     1/12/10 11:12a Presannar
// Modified code to update Handle for the Variable Info referenced.
//
// 6     1/11/10 11:14a Presannar
// Get The Variable Info referenced by Control Variable
// BugFix - Remove code to set Extended Attributes
//
// 5     11/19/09 5:31p Presannar
// Updated TSE include file name to not clash with CORE file
// Added code to support Dynamic Notification
// Commented fn. HiiGetEfiKey
//
// 4     8/24/09 12:13p Madhans
// EIP 25092 : Fix to Use the HiiChangeString() to Add the string for
// morethen one langs. with the same token.
//
// 3     8/12/09 8:08a Mallikarjunanv
// moved the Hii function 'HiiGetEfiKey' from commonoem.c to hii.c
//
// 2     8/11/09 2:46p Presannar
// Renamed _HiiGetForm to HiiGetForm
// Modified HiiGetForm by moving retrieving form by ID to another function
// GetFormByFormID
// Added new fns HandleNewIFRPack, HandleRemoveIFRPack, HandleAddIFRPack
// and _FxiupNotificationData for dynamic parsing of IFR data
// Added new fn GetFormByFormID, GetNextForm for form manipulation
// Added Fns _ReInitializeSetupdataPointers to reinitialize setupdata
// pointers.
//
// 1     7/24/09 6:54p Presannar
//
// 4     4/24/09 7:53p Presannar
// Bug fixes
//
// 3     4/14/09 12:39p Presannar
// Added fn implementation for GetFormSetTitleAndHelp
//
// 2     3/31/09 4:15p Madhans
// UEFI Wrapper improvments.
//
// 1     1/09/09 2:38p Presannar
// UEFI 2.1 Hii Related Code - Initial Drop
//
// 8     10/08/08 6:42p Presannar
// Removed function PreparePackageList
// removed call to get UEFI 2.1 HII ImageProtocol
//
// 7     8/22/08 4:56p Madhans
// To skip the Formsets, thier subclass type is not
// EFI_SETUP_APPLICATION_SUBCLASS.
// fix resolve parentpageid for nested sub page that is out of order. (To
// consider case where form are refered after it is defined in the VFR).
//
// 6     8/20/08 4:51p Presannar
// Code Snippet Added to Check if a Form Pack indeed contains a Formset.
//
// 5     8/05/08 3:44p Presannar
// Updated code snippets for functions _AddVariable, HiiFixupData,
// _ParseForm, _UpdeateDefaults, _AddHpkControls.
// Added new code snippets functions _CheckAndAddVariable,
// _GetControlKeytoken, _GetControlDevicePathId,
// _UpdateVariableDevicePathId.
//
// 4     7/23/08 6:09p Presannar
// Fixed infinite loop Bug for function _IsFormFound
//
// 3     7/21/08 2:08p Madhans
// Fix to add the condition control for the first control
//
// 2     7/17/08 11:48a Madhans
// To fix the issue of the last control it is supposed.
//
// 1     6/12/08 6:40p Madhans
// Minisetup Standalone Application for UEFI 2.1
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:          Hii.c
//
// Description:  Contains Hii related Functions
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
#include "minisetup.h"
#include "TseDrvHealth.h" //EIP-83080 
#include "TseUefiHii.h"
#ifndef TSE_FOR_APTIO_4_50
#define EFI_HII_PACKAGE_FORMS                EFI_HII_PACKAGE_FORM
#include "tianohii.h"
#endif
//----------------------------------------------------------------------------
// MACRO DEFINITIONS
//----------------------------------------------------------------------------
#define MAX_DEV_PATH_STR_LEN    100	//EIP: 55762 

//----------------------------------------------------------------------------
// EXTERN VARIABLES
//----------------------------------------------------------------------------
extern UINTN gLangCount;
extern UINTN gDynamicPageCount;
extern UINT32 gRefreshIdCount;
extern REFRESH_ID_INFO 	*gRefreshIdInfo;

//----------------------------------------------------------------------------
// VARIABLE DECLARATIONS
//----------------------------------------------------------------------------
static SETUP_LINK 		*gSetupData = NULL;
static EFI_HII_HANDLE 	*gSetupHandles;
static EFI_HANDLE 		gNotifyHandle[3];
EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *gDevPathToTextProtocol = (EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *)NULL;//EIP-83080 starts
EFI_GUID 			gDevPathToTextGuid 							= EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID;//EIP-83080 Ends
VOID 					*gFirstPageRef;
PAGE_ID_INFO 		*PageIdInfoPtr;
PAGE_ID_LIST 		*PageIdListPtr;
PAGE_INFO 			*PageInfoPtr;
PAGE_INFO 			*FirstPage;
PAGE_INFO 			*NewPageInfo;
PAGE_LIST 			*PageListPtr;
VARIABLE_LIST 		*VariableListPtr;
VARIABLE_INFO 		*VariableInfoPtr;
BOOLEAN 				gHiiInitialized = FALSE;
UINT32 				AllocatedFirstPageSize, FirstPageOffset;
UINT32 				ControlListSize, ControlListOffset;
UINT32 				PageIdListSize, PageIdListOffset;
UINT32 				PageIdInfoSize, PageIdInfoOffset;
UINT32 				PageListSize, PageListOffset;
UINT32 				PageInfoSize, PageInfoOffset;
UINT32 				VariableListSize, VariableListOffset;
UINT32 				VariableInfoSize, VariableInfoOffset;
UINTN 				TotalRootPages;
UINTN 				gSetupCount = 0;
EFI_GUID 			*gGuidDump=NULL;		//EIP64253 offline vfr pages hided
UINTN    			gGuidDumpCount=0;

//----------------------------------------------------------------------------
// FUNCCTION DECLARATIONS
//----------------------------------------------------------------------------
EFI_HII_HANDLE 		*_HiiGetHandles (UINT16 *NumberOfHiiHandles);
EFI_IFR_FORM_SET 		*_HiiGetFormSet (UINTN index);


EFI_STATUS 				_HiiLocateSetupHandles (VOID);
EFI_STATUS 				_MergePageIdListAndInfo (VOID);
EFI_STATUS 				_MergePageListAndInfo (VOID);
EFI_STATUS 				_MergeVariableListAndInfo (VOID);
EFI_STATUS 				_GetClassSubClassID (SETUP_LINK *SetupData);
EFI_STATUS 				GetAcknowledgementKey ();
EFI_STATUS 				_ReInitializeSetupdataPointers ();

UINT16 					_IsFormFound (EFI_IFR_FORM_SET *formSet, UINT16 formid);
UINT16 					_HiiGetLinkIndex (EFI_GUID *guid, UINT16 class, UINT16 subclass, UINT16 formid);
VOID 						UIUpdateCallback (VOID * Handle, UINT32 OldVariableCount);
EFI_STATUS _FxiupNotificationData(SETUP_LINK *Setup_Link);

EFI_STATUS 				UpdateIFRRefXControls (PAGE_INFO *PageInfo, CONTROL_INFO * CtrlInfo);//EIP: 55762 Start
EFI_STATUS				GetPageIdFromGuid (EFI_GUID *FormGuid, UINT16 PageFormID, UINT16 *PageID);//EIP: 55762 End
VOID 						SetDriverHealthCount (VOID);//EIP57661 Starts Driver health support
BOOLEAN  				IsDriverHealthSupported (VOID);//EIP57661 Ends
EFI_STATUS 				CreateEventforIFR (CONTROL_INFO *control_Info );//EIP-105468



VOID 				FixMergePagesExtraHook (VOID *gPages, VOID *tempPages);
VOID 				PageRemoveHook (UINTN PageIndex, void *pageInfo, 	void *PageHandle, UINT16	PageFormID);

////////////////////////////////////
//	Externing Functions
///////////////////////////////////
extern BOOLEAN   IsSupportDefaultForStringControl (VOID);

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   HiiGetForm
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
VOID *HiiGetForm( EFI_HII_HANDLE Handle, UINT16 form, UINTN *Length )
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_HII_PACKAGE_HEADER *pkgHdr;
	EFI_IFR_OP_HEADER *opHeader = NULL;

	VOID *hiiFormPackage=NULL;
	UINT8 *formPkBuffer = NULL;
	UINT8 *pkgOffset;
//	UINT8 *msgBoxSel = NULL;
	UINT8 end = 0;
	UINT32 offset = 0;
	UINTN len=10;
	SETUP_LINK DummySetupLink;

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
			goto DONE;
		}
	}else if(EFI_ERROR(status))
	{
		hiiFormPackage = NULL;
		goto DONE;
	}

	offset = sizeof(EFI_HII_PACKAGE_LIST_HEADER);

	while(offset < ((EFI_HII_PACKAGE_LIST_HEADER*)hiiFormPackage)->PackageLength)
	{
		pkgOffset = ((UINT8*)hiiFormPackage) + offset;
		pkgHdr = (EFI_HII_PACKAGE_HEADER*)pkgOffset;
		switch(pkgHdr->Type)
		{
			case EFI_HII_PACKAGE_FORMS:
				formPkBuffer = (UINT8*)EfiLibAllocateZeroPool(pkgHdr->Length);
				if(formPkBuffer == NULL)
				{
					goto DONE;
				}
				MemCopy(formPkBuffer, pkgHdr, pkgHdr->Length);
				opHeader = (EFI_IFR_OP_HEADER*)((UINT8*)formPkBuffer + sizeof(EFI_HII_PACKAGE_HEADER));
				if(opHeader->OpCode != EFI_IFR_FORM_SET_OP)
				{
#ifdef STANDALONE_APPLICATION
					CHAR16 *Temp = L"ERROR! Form Package contains No FormSet. Skipping Package Processing.\x0a\x0dPress a Key to Continue :\x0a\x0d";
					gST->ConOut->OutputString(gST->ConOut,Temp);
					status = GetAcknowledgementKey();
					if(EFI_ERROR(status))
					{
						gST->ConOut->OutputString(gST->ConOut, L"GetAcknowledgementKey returned ERROR!");
					}
#endif
					MemFreePointer(&formPkBuffer);
					formPkBuffer = NULL;
					*Length = 0;
					goto DONE;
				}
				// to check is the formset is EFI_SETUP_APPLICATION_SUBCLASS.
				MemSet(&DummySetupLink,sizeof(DummySetupLink),0);
				DummySetupLink.FormSet = formPkBuffer;
				if(_GetClassSubClassID(&DummySetupLink) == EFI_UNSUPPORTED)
				{
					MemFreePointer(&formPkBuffer);
					formPkBuffer = NULL;
					*Length = 0;
					goto DONE;
				}
				end = 1;
				break;
			case EFI_HII_PACKAGE_END:
				end = 1;
				break;
			default:
				break;
		}
		if (end)
		{
			break;
		}
		offset += pkgHdr->Length;
	}
	MemFreePointer(&hiiFormPackage);
	if(form && (NULL != formPkBuffer))//EIP-75384 Static code
	{
	    UINT8 *tempForm = NULL;
		tempForm = GetFormByFormID((EFI_HII_PACKAGE_HEADER *)formPkBuffer, form, Length);
		MemFreePointer(&formPkBuffer);
		formPkBuffer = tempForm;
	}

DONE:
	return formPkBuffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _GetClassSubClassID
//
// Description:
//
// Parameter:    VOID *DefValue
//
// Return value: EFI_STATUS - The status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS _GetClassSubClassID(SETUP_LINK *SetupData)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)NULL;
  BOOLEAN flag = TRUE;
  INTN inScope = 0;

  if(SetupData->FormSet == NULL)
  {
    return EFI_UNSUPPORTED;
  }

  SetupData->ClassID = 0;
  SetupData->SubClassID = 0;
  opHeader = (EFI_IFR_OP_HEADER*)(SetupData->FormSet + sizeof(EFI_HII_PACKAGE_HEADER));
  do
  {
    switch(opHeader->OpCode)
    {
    case EFI_IFR_GUID_OP:
      {
        UINT8 extOpcode = (UINT8)*((UINT8*)opHeader + sizeof(EFI_IFR_GUID));
        switch(extOpcode)
        {
        case EFI_IFR_EXTEND_OP_CLASS:
          {
            EFI_IFR_GUID_CLASS *guidClass = (EFI_IFR_GUID_CLASS*)opHeader;
            SetupData->ClassID = guidClass->Class;
          }
          break;
        case EFI_IFR_EXTEND_OP_SUBCLASS:
          {
            EFI_IFR_GUID_SUBCLASS *guidSubClass = (EFI_IFR_GUID_SUBCLASS*)opHeader;
            SetupData->SubClassID = guidSubClass->SubClass;
            flag = FALSE;
          }
          break;
        }
      }
	  break;
	case EFI_IFR_END_OP:
		if(inScope)
		{
		  inScope--;
		}
    default:
      break;
    }

	if(opHeader->Scope)
	{
	  inScope++;
	}
	opHeader = (EFI_IFR_OP_HEADER*)((UINT8*)opHeader + opHeader->Length);
  } while(flag && inScope > 0);

  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _MergePageIdListAndInfo
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _MergePageIdListAndInfo()
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN i;

	if((PageIdListOffset + PageIdInfoOffset) == 0)
	{
		gPageIdList = NULL;
		gPageIdInfo = NULL;
		return status; // NO Formset to show.
	}

	gPageIdList = (PAGE_ID_LIST*)EfiLibAllocateZeroPool(PageIdListOffset + PageIdInfoOffset);
	if(gPageIdList == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	MemCopy(gPageIdList,PageIdListPtr,PageIdListOffset);
	MemCopy(((UINT8 *)gPageIdList)+ PageIdListOffset,PageIdInfoPtr,PageIdInfoOffset);

	for(i=0; i<gPageIdList->PageIdCount; i++)
	{
		gPageIdList->PageIdList[i] += PageIdListOffset;
	}

	gPageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[0]);

	//Free Temp Memory
	MemFreePointer(&PageIdInfoPtr);
	MemFreePointer(&PageIdListPtr);

DONE:
	return status;
}
//EIP: 55762 Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    SpecialControlsFixup
//
// Description:  Fixes control information for special control in the varstore
//
// Parameter:    None
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SpecialControlsFixup()
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN i,j;
	VARIABLE_INFO *varInfo = NULL;

	for(i = 0; i < gPages->PageCount; i++)
	{
		PAGE_INFO *PageInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[i]);
		if(!PageInfo){
			continue;
		}
		for ( j = 0; j < PageInfo->PageControls.ControlCount; j++ )
		{
			CONTROL_INFO *ctrlInfo = (CONTROL_INFO*)(((UINTN)gControlInfo) + PageInfo->PageControls.ControlList[j]);
			if(!ctrlInfo){
				continue;
			}

			UpdateIFRRefXControls(PageInfo, ctrlInfo); //Update the CONTROL_INFO with REFX information

			
		}
	}
	for ( i = 0; i < gVariables->VariableCount; i++)
	{
		varInfo = (VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[i]);
		if(!varInfo){
			continue;
		}
		for(j = 0; j < gGuidList->GuidCount; j++)
        {
			GUID_INFO *GuidInfo = (GUID_INFO *)((UINTN)gGuidList + gGuidList->GuidList[j]);
			if(GuidInfo && EfiCompareGuid(&varInfo->VariableGuid, &GuidInfo->GuidValue))
			{
				switch(GuidInfo->GuidKey)  
				{
					//case GUID_KEY_NO_COMMIT:
					//	varInfo->ExtendedAttibutes = AMI_SPECIAL_NO_COMMIT_VARIABLE;
					//	break;
					default:
						break;
				}
			}
		}
	}

	return status;
}
//EIP: 55762 End
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _MergePageListAndInfo
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS
//					EFI_SUCCESS
//					EFI_OUT_OF_RESOURCES
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _MergePageListAndInfo()
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN i;

    SETUP_DEBUG_UEFI ( "\n[TSE] Entering _MergePageListAndInfo()\n" );

	gApplicationData = (UINT8*)EfiLibAllocateZeroPool(PageListOffset + FirstPageOffset + PageInfoOffset);
	if(gApplicationData == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	gPages = (PAGE_LIST *) gApplicationData;
	MemCopy(gApplicationData, PageListPtr, PageListOffset);
	MemCopy(gApplicationData + PageListOffset, FirstPage, FirstPageOffset);
	MemCopy(gApplicationData + PageListOffset + FirstPageOffset, PageInfoPtr, PageInfoOffset);

	//Fix Offsets
	i=0;
	gPages->PageList[i] = PageListOffset;
	i++;

	for(; i < gPages->PageCount; i++)
	{
		gPages->PageList[i] += (FirstPageOffset + PageListOffset);
	}

	//Free Temp Memory
	MemFreePointer(&FirstPage);
	MemFreePointer(&PageInfoPtr);
	MemFreePointer(&PageListPtr);
//EIP: 55762 Start
	SpecialControlsFixup(); //Fixes control information for special control in the varstore
//EIP: 55762 End
DONE:
    SETUP_DEBUG_UEFI ( "\n[TSE] Exitingg _MergePageListAndInfo(),  status = 0x%x \n" , status );

	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _MergeVariableListAndInfo
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _MergeVariableListAndInfo()
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN i;

	//EIP-71351 Try to reallocate the existing Variable Cache.
	if (gVariables->VariableCount != VariableListPtr->VariableCount)		//EIP 90809 Reallocating only when counts varies
	{
		if(gVariableList != NULL)
			gVariableList = MemReallocateZeroPool( gVariableList, sizeof(NVRAM_VARIABLE) * gVariables->VariableCount, VariableListPtr->VariableCount * sizeof(NVRAM_VARIABLE));
		
		if(gOptimalDefaults != NULL)
			gOptimalDefaults = MemReallocateZeroPool( gOptimalDefaults, sizeof(NVRAM_VARIABLE) * gVariables->VariableCount, VariableListPtr->VariableCount * sizeof(NVRAM_VARIABLE));
		
		if(gFailsafeDefaults != NULL)
			gFailsafeDefaults = MemReallocateZeroPool( gFailsafeDefaults, sizeof(NVRAM_VARIABLE) * gVariables->VariableCount, VariableListPtr->VariableCount * sizeof(NVRAM_VARIABLE));
	}

	gVariables = (VARIABLE_LIST*)EfiLibAllocateZeroPool(VariableListOffset + VariableInfoOffset);
	if(gVariables == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	MemCopy(gVariables,VariableListPtr,VariableListOffset);
	MemCopy(((UINT8 *)gVariables)+ VariableListOffset,VariableInfoPtr,VariableInfoOffset);

	for(i=0; i<gVariables->VariableCount; i++)
	{
		gVariables->VariableList[i] += VariableListOffset;
	}

	//Free Temp Memory
	MemFreePointer(&VariableInfoPtr);
	MemFreePointer(&VariableListPtr);

DONE:
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    HiiExit
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS - Return the Status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrUnRegFormNotificationWrapper (VOID);
EFI_STATUS HiiExit()
{
	UINTN i;

	//Remove gSetupHandles
	MemFreePointer((VOID**)&gSetupHandles);

	// Remove memory held by gSetupData
	for ( i = 0; i < gSetupCount; i++ )
    {
		//EIP:61122, Free memory only if gSetupData[i].FormSetLength is non-zero.
        if(gSetupData[i].FormSetLength)
            MemFreePointer(&(gSetupData[i].FormSet));
    }
	MemFreePointer(&gSetupData);
	gSetupCount = 0;

	MemFreePointer(&gControlInfo);
	ControlListSize = ControlListOffset = 0;

	MemFreePointer(&gApplicationData);
	gPages = gToolPages;
	PageListPtr = NULL;
	PageInfoPtr = NULL;
	FirstPage = NULL;
	AllocatedFirstPageSize = FirstPageOffset = PageListSize = PageListOffset = PageInfoSize = PageInfoOffset = 0;

//#if SETUP_RUNTIME_IFR_PROCESSING
	RTIfrProcessExitWrapper();
//#endif

	gVariables = gToolVariables;
	gPageIdList = gToolPageIdList;
	gPageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[0]);

	RTIfrUnRegFormNotificationWrapper ();	//EIP99059
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    UnRegFormNotification
//
// Description:	Unregisters the form notification
//
// Parameter:	VOID
//
// Return value: VOID	
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UnRegFormNotification (VOID)
{
	UnRegisterFormNotification (gNotifyHandle[0]);
	UnRegisterFormNotification (gNotifyHandle[1]);
	UnRegisterFormNotification (gNotifyHandle[2]);
}

VOID FixupPage0ControlInfo( UINTN FormSet, UINTN ControlPtr, EFI_HII_HANDLE Handle)
{
	PAGE_INFO *pageInfo = (PAGE_INFO *)(((UINT8 *)gSetupPkg) + gToolPages->PageList[0]);
	CONTROL_INFO *controlInfo = NULL;
	UINT32 j;

	if(pageInfo->PageControls.ControlCount)
	{
		for ( j = 0; j < pageInfo->PageControls.ControlCount; j++ )
		{
			controlInfo = (CONTROL_INFO*)((UINTN)gToolControlInfo + pageInfo->PageControls.ControlList[j]);
			if( (ControlPtr-FormSet) == (UINTN)controlInfo->ControlPtr )
			{
				controlInfo->ControlHandle = Handle;
				controlInfo->ControlPtr = (VOID*)ControlPtr;
			}else{
				if(controlInfo->ControlType == CONTROL_TYPE_NULL)
					controlInfo->ControlHandle = Handle;
			}
		}
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    RegFormNotification
//
// Description:  Registers the hii pack notification
//
// Parameter: VOID
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RegFormNotification (VOID)
{
	EFI_STATUS status = EFI_SUCCESS;

	status = RegisterFormNotification(IFRChangeNotifyFn, EFI_HII_DATABASE_NOTIFY_NEW_PACK, &gNotifyHandle[0]);
	if (EFI_ERROR(status))
	{
		return status;
	}
	status = RegisterFormNotification(IFRChangeNotifyFn, EFI_HII_DATABASE_NOTIFY_REMOVE_PACK, &gNotifyHandle[1]);
	if (EFI_ERROR(status))
	{
		return status;
	}
	status = RegisterFormNotification(IFRChangeNotifyFn, EFI_HII_DATABASE_NOTIFY_ADD_PACK, &gNotifyHandle[2]);
	if (EFI_ERROR(status))
	{
		return status;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    HiiFixupData
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS - Return the Status
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RTIfrRegFormNotificationWrapper (VOID);
extern EFI_GUID 	RefreshEventGroupId;
EFI_STATUS HiiFixupData()
{
	EFI_STATUS status = EFI_SUCCESS;

	PAGE_INFO	*pageInfo = NULL;
	EFI_IFR_FORM_SET *formSet;
	EFI_IFR_REF *ref = NULL;
    //UINT16      *varString;
    //UINT16      StringToken = 0;
	UINT16      link;
	UINT32      i=0;
	UINT32      j=0;

   SETUP_DEBUG_UEFI ( "\n[TSE] Entering HiiFixupData()\n" );
   if (PageListOffset || FirstPageOffset || PageInfoOffset)          //EIP122350 If handofftse invoked second time then offsets incrementing from current so exiting and reforming.
   {
      HiiExit();
   }
	status = RTIfrRegFormNotificationWrapper ();			//EIP99059
	if (EFI_ERROR (status))
		goto DONE;
	status = _HiiLocateSetupHandles();
	if (EFI_ERROR(status))
	{
		goto DONE;
	}
	gSetupData = EfiLibAllocateZeroPool(sizeof(SETUP_LINK) * gSetupCount);
	if(gSetupData == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	for(i = 0; i < gSetupCount - 1; i++)
	{
		gSetupData[i].FormSet = HiiGetForm(gSetupHandles[i], 0, &(gSetupData[i].FormSetLength));
		if(gSetupData[i].FormSet == NULL)
		{
			// make sure the handle is also zero
			gSetupData[i].Handle = 0 ;
			continue;
		}
		gSetupData[i].Handle = gSetupHandles[i];
		formSet = (EFI_IFR_FORM_SET*)_HiiGetFormSet(i);

		_GetClassSubClassID(&gSetupData[i]);

#if TSE_DEBUG_MESSAGES
	    WritePackToFile(SETUPDATAFILENAME, 
				gSetupData[i].Handle, 
				NULL,
				gSetupData[i].FormSetLength) ;
#endif
	}


	// need to allocate one more dynamic IFR for the root page, this is NOT a 100% valid
	// formset as there is no form defined
	gSetupData[i].FormSet = EfiLibAllocateZeroPool(sizeof(EFI_HII_PACKAGE_HEADER) +
			sizeof(EFI_IFR_FORM_SET) + /*i*/ gToolPages->PageCount * sizeof(EFI_IFR_REF)); //EIP 105965 : No. of root pages can be more then hii handle because of AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST_SUPPORT
	if(gSetupData[i].FormSet == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	formSet = (EFI_IFR_FORM_SET*)_HiiGetFormSet(i);
	MemCopy(&(formSet->Guid),&(gSetupPkg->PackageGuid),sizeof(EFI_GUID));

	TotalRootPages = 0;
	if ( gSetupData[i].FormSet != NULL )
	{
		ref = (EFI_IFR_REF *)(gSetupData[i].FormSet + sizeof(EFI_HII_PACKAGE_HEADER) + sizeof(EFI_IFR_FORM_SET));
		for ( j = 1; j <= gToolPages->PageCount; j++ )
		{
			pageInfo = (PAGE_INFO *)(((UINT8 *)gSetupPkg) + gToolPages->PageList[j]);
			if ( pageInfo->PageParentID != 0 ) //if ( pageInfo->PageFormID != 1 ) 
			{
				continue;
			}

			TotalRootPages++;

			link = _HiiGetLinkIndex(&(gToolPageIdInfo[pageInfo->PageIdIndex].PageGuid),
						gToolPageIdInfo[pageInfo->PageIdIndex].PageClass,
						gToolPageIdInfo[pageInfo->PageIdIndex].PageSubClass,
						pageInfo->PageFormID);

			if ( link == (gSetupCount - 1) )
			{
				continue;
			}

			formSet = (EFI_IFR_FORM_SET*)_HiiGetFormSet(link);
			//EIP-75352 Suppress the warnings from static code analyzer
			if(NULL == formSet){
				continue;
			}
			ref->Header.OpCode = EFI_IFR_REF_OP;
			ref->Header.Length = sizeof(EFI_IFR_REF);
			ref->Question.Header.Prompt = formSet->FormSetTitle;
			ref->Question.Header.Help = formSet->Help;
			FixupPage0ControlInfo( (UINTN)gSetupData[i].FormSet, (UINTN)ref, gSetupData[link].Handle);
			ref++;
		}
		gSetupData[i].Handle = gSetupData[0].Handle;
	}
//#if SETUP_RUNTIME_IFR_PROCESSING
	RTIfrProcessAddVarListAndPageIDListWrapper();
//#endif //SETUP_RUNTIME_IFR_PROCESSING
//EIP64253 offline vfr pages hided starts
	i = 0;
    if(gGuidDump == NULL)
    {
        gGuidDumpCount = gToolPages->PageCount;
    	gGuidDump = EfiLibAllocateZeroPool (sizeof (EFI_GUID) * gGuidDumpCount);
        j = 0;
    }
    else
    {
        j = (UINT32) gGuidDumpCount;
		gGuidDump = MemReallocateZeroPool (gGuidDump, gGuidDumpCount * sizeof (EFI_GUID), (gGuidDumpCount+gToolPages->PageCount) * sizeof (EFI_GUID));
        gGuidDumpCount += gToolPages->PageCount;
    }

	if (NULL != gGuidDump)
	{
		for (i = 0; i < gToolPages->PageCount; i++)
		{
			PAGE_INFO	*ParsepageInfo = NULL;
			ParsepageInfo = (PAGE_INFO *)(((UINT8 *)gSetupPkg) + gToolPages->PageList [i]);

			EfiCopyMem (&gGuidDump [i+j], &gToolPageIdInfo [ParsepageInfo->PageIdIndex].PageGuid, sizeof (EFI_GUID));
		}	
	}
//EIP64253 offline vfr pages hided ends
	// update the control (IFR) pointers and HII handles
	for ( i = 0; i< gToolPages->PageCount; i++ )
	{
//		PAGE_INFO *NewPageInfo;
		UINT32 PageSize;
		UINT32 ControlSize;
		CONTROL_INFO *NewControlInfo;
		UINTN NoOfControlSpace;

		pageInfo = (PAGE_INFO *)(((UINT8 *)gSetupPkg) + gToolPages->PageList[i]);

		if(i == 0)
		{
			link = (UINT16)(gSetupCount - 1);
		}
		else
		{
			link = _HiiGetLinkIndex( &(gToolPageIdInfo[pageInfo->PageIdIndex].PageGuid),
					gToolPageIdInfo[pageInfo->PageIdIndex].PageClass,
					gToolPageIdInfo[pageInfo->PageIdIndex].PageSubClass,
					pageInfo->PageFormID);
		}

		NoOfControlSpace = pageInfo->PageControls.ControlCount ? pageInfo->PageControls.ControlCount - 1 : pageInfo->PageControls.ControlCount;
        PageSize = (UINT32)(sizeof(PAGE_INFO) + sizeof(pageInfo->PageControls.ControlList) * NoOfControlSpace);
		NewPageInfo = EfiLibAllocateZeroPool(PageSize);
		if (NewPageInfo == NULL)
		{
			status = EFI_OUT_OF_RESOURCES;
			goto DONE;
		}
		MemCopy(NewPageInfo,pageInfo,PageSize);

		if ( link == (gSetupCount - 1) )
		{
			NewPageInfo->PageHandle = 0;// This page has been removed in runtime!!!
		}
		else
		{
//#if SETUP_RUNTIME_IFR_PROCESSING
			if(RTIfrProcessFormIfUpdatedWrapper(link) == TRUE)
				continue;
//#endif //SETUP_RUNTIME_IFR_PROCESSING

        	NewPageInfo->PageHandle = gSetupData[link].Handle;
		}

		//Fixup and add the controls in this page to gContolInfo and update offsets in page info

		if(NewPageInfo->PageControls.ControlCount)
		{
		for ( j = 0; j < NewPageInfo->PageControls.ControlCount; j++ )
		{
			VARIABLE_INFO *varInfo = NULL;
			CONTROL_INFO *controlInfo = (CONTROL_INFO*)((UINTN)gToolControlInfo + NewPageInfo->PageControls.ControlList[j]);
			//EIP:56413 Updated the contol size to copy the Default information for the control
		    ControlSize = sizeof(CONTROL_INFO) + controlInfo->ControlDataWidth * 2 + controlInfo->DefaultStoreCount * (sizeof(UINT16) + controlInfo->ControlDataWidth) ;

			NewControlInfo = EfiLibAllocateZeroPool(ControlSize);
			if (NewControlInfo == NULL)
			{
				status = EFI_OUT_OF_RESOURCES;
				goto DONE;
			}
			MemCopy(NewControlInfo, controlInfo, ControlSize);

			if(NewPageInfo->PageHandle != 0)
			{
				NewControlInfo->ControlHandle = gSetupData[link].Handle;

				if ( NewControlInfo->ControlPtr != 0 )
				{
					NewControlInfo->ControlPtr = (VOID *)((UINTN)NewControlInfo->ControlPtr + (UINTN)gSetupData[link].FormSet);
					
					if ( NewControlInfo->ControlFlags.RefreshID )//EIP-105468 & 175492 
					{
						UINT32	index=0;
						UINT8   *pOpcodeHeader=(UINT8 *)NewControlInfo->ControlPtr;
						//search for the EFI_IFR_REFRESH_ID_OP.if Found then only type cast and assign RefreshEventGroupId and create event for IFR.
						while(pOpcodeHeader)//EIP-175492  
						{
							if(EFI_IFR_REFRESH_ID_OP == ((EFI_IFR_OP_HEADER *)(pOpcodeHeader))->OpCode)
							{
								MemCopy (&RefreshEventGroupId, &(((AMI_EFI_IFR_REFRESH_ID *)(pOpcodeHeader))->RefreshEventGroupId), sizeof (EFI_GUID));
								CreateEventforIFR (NewControlInfo);
								break;
							}
							if((((EFI_IFR_OP_HEADER *)(pOpcodeHeader))->Scope))//if OpcodeHeader has scope then, Increment index
								index++;
							if(EFI_IFR_END_OP == ((EFI_IFR_OP_HEADER *)(pOpcodeHeader))->OpCode)//if EFI_IFR_END_OP found then,decrement index
								index--;
							if(!index)
								break;
							pOpcodeHeader+=((EFI_IFR_OP_HEADER *)(pOpcodeHeader))->Length;//point to next opcode header depending upon the Length
						} 
					}

					if ( NewControlInfo->ControlConditionalPtr != 0 )
					{
						NewControlInfo->ControlConditionalPtr = (VOID *)((UINTN)NewControlInfo->ControlConditionalPtr + (UINTN)NewControlInfo->ControlPtr);
					}
				}
				else if ( NewControlInfo ->ControlConditionalPtr != 0 )
				{
					NewControlInfo ->ControlConditionalPtr = (VOID *)((UINTN)NewControlInfo ->ControlConditionalPtr + (UINTN)gSetupData[link].FormSet);
				}
				// Get The Variable Info referenced by Control Variable
                if (RTIfrUpdateVariableInfoWrapper (NewControlInfo->ControlVariable, gSetupData[link].Handle) == FALSE)
                {
                    varInfo = VarGetVariableInfoIndex (NewControlInfo->ControlVariable);
                    if(varInfo->VariableHandle == NULL)
                    {
                        varInfo->VariableHandle = gSetupData[link].Handle;
                    }
                    //EIP56405: Commented for suppressing build time parsing. Name value not supported by current vfr compiler. Uncomment it once vfr compiler supports it.
                    /*if (VARIABLE_ATTRIBUTE_NAMEVALUE == (varInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE))
                    {
                        if (0 == (EfiStrLen (varInfo->VariableName)))
                        {
                            StringToken = (UINT16)((UINT16)(varInfo->NameValueToken [1] << 8) + (UINT8)(varInfo->NameValueToken [0]));
                            varString = HiiGetString (varInfo->VariableHandle, StringToken);
                            EfiStrCpy (varInfo->VariableName, varString);
                        }
                    }*/
                 }
            }
   			NewPageInfo->PageControls.ControlList[j] = AddControlToList(NewControlInfo,ControlSize); //Update new offset in gControlInfo
   			MemFreePointer(&NewControlInfo);
			}
		}
		else
		{
			// Add the Empty Control to control List even if NewPageInfo->PageControls.ControlCount = 0
			CONTROL_INFO *controlInfo = (CONTROL_INFO*)((UINTN)gToolControlInfo + 0);
			ControlSize = sizeof(CONTROL_INFO) + controlInfo->ControlDataWidth * 2;
			NewControlInfo = EfiLibAllocateZeroPool(ControlSize);
			MemCopy(NewControlInfo, controlInfo, ControlSize);
			AddControlToList(NewControlInfo,ControlSize); //Update new offset in gControlInfo
			MemFreePointer(&NewControlInfo);
		}

		if(i==0)
		{
			status = CreatePage(&FirstPage, &AllocatedFirstPageSize, &FirstPageOffset, NewPageInfo, PageSize);
		}
		else
		{
			status = AddPageToList(NewPageInfo,PageSize);
		}
		if(EFI_ERROR(status))
		{
			goto DONE;
		}
		MemFreePointer(&NewPageInfo);
	}

//#if SETUP_RUNTIME_IFR_PROCESSING
	RTIfrProcessRunTimeFormsWrapper(&ref);
//#endif //SETUP_RUNTIME_IFR_PROCESSING

	status = _MergePageListAndInfo();
//EIP57661 Starts
	if (IsDriverHealthSupported ())
	{
		SetDriverHealthCount ();
	} 
//EIP57661 Ends
DONE:
    SETUP_DEBUG_UEFI ( "\n[TSE] Exiting HiiFixupData(),  status = 0x%x \n" , status );
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _HiiLocateSetupHandles
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _HiiLocateSetupHandles()
{
    EFI_STATUS status;
	UINT16 i = 0;
	UINT16 count;
	EFI_HII_HANDLE	*handleBuffer;
	UINT8 *buffer;
	UINT16 found = 0;

	status = HiiInitializeProtocol();
	if (EFI_ERROR(status))
	{
		goto DONE;
	}

	if(FormBrowserLocateSetupHandles(&handleBuffer,&count)!= EFI_SUCCESS)
	{
		handleBuffer = _HiiGetHandles( &count );
	}

	if ( handleBuffer == NULL )
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	gSetupHandles = (EFI_HII_HANDLE*)EfiLibAllocatePool((count + 1) * sizeof(EFI_HII_HANDLE));
	if ( gSetupHandles == NULL )
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}

	for ( i = found = 0; i < count; i++ )
	{
		buffer = HiiGetForm( handleBuffer[i], 0, NULL );
		if ( buffer == NULL )
		{
			continue;
		}

		gSetupHandles[found] = handleBuffer[i];
		found++;
		MemFreePointer( &buffer );
	}

	gSetupCount = found + 1;

	// at this point we have all the setup specific HII handles into our buffer
DONE:

	if(!FormBrowserHandleValid())
		MemFreePointer((VOID**)&handleBuffer);

	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _HiiGetLinkIndex
//
// Description:
//
// Parameter:
//
// Return value: UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _HiiGetLinkIndex(EFI_GUID *guid, UINT16 class, UINT16 subclass, UINT16 formid)
{
	UINT16	i;
	EFI_IFR_FORM_SET *formSet;
	EFI_HII_PACKAGE_HEADER *pack;

	for ( i = 0; i < gSetupCount - 1; i++ )
	{
		pack = (EFI_HII_PACKAGE_HEADER *)gSetupData[i].FormSet;

		if ( sizeof(EFI_HII_PACKAGE_HEADER) == pack->Length )
		{
			continue;
		}

		formSet = (EFI_IFR_FORM_SET *)((UINT8 *)pack + sizeof(EFI_HII_PACKAGE_HEADER));

		if(EfiCompareGuid( guid , (VOID *)&(formSet->Guid) ))
		{
			if( gSetupData[i].ClassID == class )
			{
				if( gSetupData[i].SubClassID == subclass )
				{
					if(_IsFormFound(formSet, formid))
					{
						break;
					}
				}
			}
		}
	}

	return i;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _HiiGetFormSet
//
// Description:
//
// Parameter:
//
// Return value: EFI_IFR_FORM_SET
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_IFR_FORM_SET *_HiiGetFormSet(UINTN index)
{
		EFI_IFR_FORM_SET *formSet = NULL;

	if ( (index >= gSetupCount) || (gSetupData == NULL))
	{
		return formSet;
	}

	formSet = (EFI_IFR_FORM_SET*)(gSetupData[index].FormSet + sizeof(EFI_HII_PACKAGE_HEADER));

	return formSet;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: _HiiGetHandles
//
// Description: gets all the HII handles
//
// Parameter: No of handles
//
// Return value: EFI_HII_HANDLE *
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_HII_HANDLE *_HiiGetHandles(UINT16 *NumberOfHiiHandles)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_HII_HANDLE *hiiHandleBuffer = NULL;

	UINTN handleBufferLength = 0;

//	gBS->AllocatePool(EfiBootServicesData, handleBufferLength,
//				(VOID **)&hiiHandleBuffer);
	hiiHandleBuffer = EfiLibAllocatePool(handleBufferLength);

	status = gHiiDatabase->ListPackageLists (gHiiDatabase, EFI_HII_PACKAGE_TYPE_ALL, NULL,
					&handleBufferLength, hiiHandleBuffer);
	if (status == EFI_BUFFER_TOO_SMALL)
	{
		//
		// Free the old pool
		//
		MemFreePointer ((VOID**)&hiiHandleBuffer);
		//
		// Allocate new pool with correct value
		//
//		gBS->AllocatePool (EfiBootServicesData, handleBufferLength,
//				(VOID **)&hiiHandleBuffer);
		hiiHandleBuffer = EfiLibAllocatePool(handleBufferLength);

		//
		// Get the Handles of the packages that were registered with Hii
		//
		gBS->SetMem(hiiHandleBuffer,handleBufferLength,0);
		status = gHiiDatabase->ListPackageLists (gHiiDatabase, EFI_HII_PACKAGE_TYPE_ALL,
					  NULL, &handleBufferLength, hiiHandleBuffer);

		if (EFI_ERROR (status))
		{
			MemFreePointer((VOID**)&hiiHandleBuffer);
			hiiHandleBuffer = NULL;
			goto DONE;
		}
	}else if(EFI_ERROR(status))
	{
		MemFreePointer((VOID**)&hiiHandleBuffer);
		hiiHandleBuffer = NULL;
		goto DONE;
	}

	*NumberOfHiiHandles = (UINT16)(handleBufferLength / sizeof(EFI_HII_HANDLE));

DONE:
	return hiiHandleBuffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    _IsFormFound
//
// Description:
//
// Parameter:
//
// Return value: UINT16 -
//					1 Form Found
//					0 Form Not Found
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 _IsFormFound(EFI_IFR_FORM_SET *formSet,UINT16 formid )
{
	EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER*)formSet;
	BOOLEAN flag = TRUE;
	UINT16 found = 0;
	UINTN offset = 0;
	UINTN ScopeCount = 0;

	while(flag)
	{
		switch(opHeader->OpCode)
		{
		case EFI_IFR_FORM_OP:
			{
				EFI_IFR_FORM *formOp = (EFI_IFR_FORM*)opHeader;
				if(formOp->FormId == formid)
				{
					found = 1;
					flag = FALSE;
				}
			}
			break;
        case EFI_IFR_FORM_MAP_OP: 
			{
				AMI_EFI_IFR_FORM_MAP *formMapOp = (AMI_EFI_IFR_FORM_MAP *)opHeader;
				if(formMapOp->FormId == formid)
				{
					found = 1;
					flag = FALSE;
				}
			}
			break;
		case EFI_IFR_END_OP:
			flag = (--ScopeCount)? TRUE:FALSE;
			break;
		default:
			break;
		}
		if(opHeader->Scope)
		{
			ScopeCount++;
		}
		offset += opHeader->Length;
		opHeader = (EFI_IFR_OP_HEADER*)((UINT8*)formSet + offset);
	}

	return found;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: HiiFindHandle
//
// Description: HiiFindHandle
//
// Parameter: EFI_GUID *guid, UINT16 *index
//
// Return value: EFI_HII_HANDLE
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_HII_HANDLE HiiFindHandle( EFI_GUID *guid, UINT16 *index )
{
	EFI_HII_HANDLE	*handleBuffer = NULL;
	EFI_HII_HANDLE	handle = INVALID_HANDLE;
	UINT16 found = 0;
	UINT16 i, count;
	UINTN len=10;
	EFI_HII_PACKAGE_LIST_HEADER *hiiPackageList;
	EFI_STATUS          status=EFI_SUCCESS;

	handleBuffer = _HiiGetHandles( &count );
	if ( handleBuffer == NULL )
		return handle;

	for ( i = found = 0; i < count; i++ )
	{
		hiiPackageList = EfiLibAllocateZeroPool(len);

		status = gHiiDatabase->ExportPackageLists(gHiiDatabase, handleBuffer[i], &len, hiiPackageList);
		if(status == EFI_BUFFER_TOO_SMALL)
		{
			MemFreePointer(&hiiPackageList);
			//
			// Allocate space for retrieval of IFR data
			//
			hiiPackageList = EfiLibAllocateZeroPool(len);

			if (hiiPackageList == NULL)
			{
				hiiPackageList = NULL;
				goto DONE;
			}
			//
			// Get all the packages associated with this HiiHandle
			//
			status = gHiiDatabase->ExportPackageLists(gHiiDatabase, handleBuffer[i], &len, hiiPackageList);
			if(EFI_ERROR(status))
			{
				MemFreePointer(&hiiPackageList);
				hiiPackageList = NULL;
				goto DONE;
			}
		}
		if ( EfiCompareGuid( guid, &hiiPackageList->PackageListGuid ) )
		{
			if ( *index == found )
			{
				handle = handleBuffer[i];
				(*index)++;
				break;
			}
			found++;
		}

		MemFreePointer( &hiiPackageList );
	}

DONE:
	MemFreePointer( (VOID **)&handleBuffer );
	return handle;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: RTIfrProcessExit
//
// Description: RTIfrProcessExit
//
// Parameter: none
//
// Return value: none
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessExit(VOID)
{
	MemFreePointer(&gVariables);
	VariableListPtr = NULL;
	VariableInfoPtr = NULL;
	VariableListOffset = VariableListSize = VariableInfoOffset = VariableInfoSize = 0;

	MemFreePointer(&gPageIdList);
	PageIdListPtr = NULL;
	PageIdInfoPtr =  NULL;
	PageIdListOffset = PageIdListSize = PageIdInfoOffset = PageIdInfoSize = 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    RTIfrProcessAddVarListAndPageIDList
//
// Description:
//
// Parameter:    None
//
// Return value: None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessAddVarListAndPageIDList(VOID)
{
	UINT32	i;

    SETUP_DEBUG_UEFI ( "\n[TSE] Entering RTIfrProcessAddVarListAndPageIDList()\n" );

	//Create Variable List
	for(i=0; i < gToolVariables->VariableCount ; i++)
	{
		VARIABLE_INFO *VariableInfo;

		VariableInfo = (VARIABLE_INFO*)((UINT8*)gToolVariables + gToolVariables->VariableList[i]);
		AddVariableToList(VariableInfo);
	}

	//Create Page ID list
	for(i=0; i < gToolPageIdList->PageIdCount ; i++)
	{
		PAGE_ID_INFO *PageIdInfo;

		PageIdInfo = (PAGE_ID_INFO*)((UINT8*)gToolPageIdList + gToolPageIdList->PageIdList[i]);
		AddPageIdToList(PageIdInfo);
	}

    SETUP_DEBUG_UEFI ( "\n[TSE] Exiting RTIfrProcessAddVarListAndPageIDList()\n" );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    RTIfrProcessFormIfUpdated
//
// Description:
//
// Parameter:
//
// Return value: BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN RTIfrProcessFormIfUpdated(UINT16 link)
{
	UINT32 j;

    SETUP_DEBUG_UEFI ( "\n[TSE] Entering RTIfrProcessFormIfUpdated()\n" );

	//Fix to correctly check if FormSet length has changed and if so Parse it. This fixes the issue with duplicate ClassID and SubClassID.
	
	for(j=1; j < gToolPageIdList->PageIdCount; j++) // PAGE_ID_INFO[0] contains reference to the NULL page
	{
		//Check if the page has changed during run time
		EFI_HII_PACKAGE_HEADER *pack;
		PAGE_ID_INFO *pageIdList = (PAGE_ID_INFO *)((UINT8 *)gToolPageIdList + gToolPageIdList->PageIdList[j]);
		EFI_IFR_FORM_SET *formSet = (EFI_IFR_FORM_SET*)((UINT8 *)gSetupData[link].FormSet + sizeof(EFI_HII_PACKAGE_HEADER));

		// Compare if the FormSet triplet is already available
		if((pageIdList->PageClass == gSetupData[link].ClassID) &&
		   (pageIdList->PageSubClass == gSetupData[link].SubClassID) &&
		   (EfiCompareGuid(&pageIdList->PageGuid, (VOID *)&formSet->Guid)))
		{
			pack = (EFI_HII_PACKAGE_HEADER *)gSetupData[link].FormSet;

			if ( gHpkInfo[j-1].Length != pack->Length )
			{
   	 			break;
			}
		}
	}

	if(j < gToolPageIdList->PageIdCount)
	{
	        //This page changed during run time parse again
	        if(!gSetupData[link].Added)
		{
			ParseForm(&gSetupData[link]);
		}
		return TRUE;
	}


	gSetupData[link].Added = 1;

    SETUP_DEBUG_UEFI ( "\n[TSE] Exiting RTIfrProcessFormIfUpdated()\n" );

	return FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    RTIfrProcessRunTimeForms
//
// Description:
//
// Parameter:
//
// Return value: None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrProcessRunTimeForms(EFI_IFR_REF **ref)
{
	UINT32 i;
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_IFR_FORM_SET *formSet;
	EFI_GUID 	DynamicPageGuid = DYNAMIC_PAGE_COUNT_GUID;
	UINTN count = 0;

    SETUP_DEBUG_UEFI ( "\n[TSE] Entering RTIfrProcessRunTimeForms()\n" );

    if(!IsGroupDynamicPages())   //EIP: 59971 
        gFirstPageRef = (VOID*)(*ref);

	for(i = 0; i < gSetupCount - 1; i++)
	{
		if(!(gSetupData[i].Added))
		{
			Status = ParseForm(&gSetupData[i]);
			if((gSetupData[i].Added))
			{
				formSet = _HiiGetFormSet( i );
				//EIP-75352 Suppress the warnings from static code analyzer
				if(NULL == formSet){
					continue;
				}
				
                if(!IsGroupDynamicPages())   //EIP: 59971 
                {
                    (*ref)->Header.OpCode = EFI_IFR_REF_OP;
    				(*ref)->Header.Length = sizeof(EFI_IFR_REF);
    				(*ref)->Question.Header.Prompt = formSet->FormSetTitle;
    				(*ref)->Question.Header.Help = formSet->Help;
    				(*ref)++;
    				gFirstPageRef = (VOID*)(*ref);
                }
                
			}
			if (EFI_SUCCESS == Status) //To avoid increment count incase parsing is aborted and avoid showing sub-link under advanced page
				count++ ; 
		}
	}

	gDynamicPageCount = count ;

	//Set Dynamic page count variable
    VarSetNvramName( L"DynamicPageCount", &DynamicPageGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &count, sizeof(count) );
    VarUpdateVariable(VARIABLE_ID_DYNAMIC_PAGE_COUNT);  //EIP_63262: Update nvram cache for DynamicPageCount

	_MergePageIdListAndInfo();
	_MergeVariableListAndInfo();

    SETUP_DEBUG_UEFI ( "\n[TSE] Exiting RTIfrProcessRunTimeForms()\n" );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    HiiLoadDefaults
//
// Description:
//
// Parameter:
//
// Return value: EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HiiLoadDefaults( VOID **varList, UINT32 Mask )
{
  // This function needs to be revisited once Aptio supports GetAltCfg
  EFI_STATUS status = EFI_SUCCESS;
  UINT32 index = 0;

  status = GetNvramVariableList((NVRAM_VARIABLE **)varList); // EIP  76381 : Performance Improving of variable data load and usage
    if(EFI_ERROR(status)){
        goto DONE;
    }

  // Get the Controls in each Page
  for ( index = 0; index < gPages->PageCount; index++ )
  {
    PAGE_INFO *pageInfo = (PAGE_INFO*)((UINT8 *)gPages + gPages->PageList[index]);
    UINTN control = 0;

    if(pageInfo->PageHandle == NULL)
    {
      continue;
    }
    // Get the Default values for each control and update DefaultStore
    for(control = 0; control < pageInfo->PageControls.ControlCount; control++)
    {
      CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

      if(controlInfo->ControlDataWidth > 0)
      {
        UINT32 offset = 0;
        UINTN width = 0;
        UINT8 *defaultValue = NULL;

		if( UefiIsEfiVariable(controlInfo->ControlVariable,VarGetVariableInfoIndex( controlInfo->ControlVariable ) ) )
			continue;

        offset = UefiGetQuestionOffset(controlInfo->ControlPtr);
        width = UefiGetWidth(controlInfo->ControlPtr);

        defaultValue = (Mask & AMI_FLAG_MANUFACTURING)? ((UINT8*)controlInfo + sizeof(CONTROL_INFO)) :
            ((UINT8*)controlInfo + sizeof(CONTROL_INFO) + controlInfo->ControlDataWidth);
        _VarGetSetValue( VAR_COMMAND_SET_VALUE, *varList, controlInfo->ControlVariable, offset, width, defaultValue );
      }
    }
  }

DONE:
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    HiiMyGetStringLength
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN HiiMyGetStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token )
{
	CHAR16 *string;
	UINTN length = 0;

	string = HiiGetString( handle, token );
	if ( string == NULL )
		return length;

	length = TestPrintLength( string ) / (NG_SIZE);
	MemFreePointer( (VOID **)&string );

	return length;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiMyGetMultiLineStringLength
//
// Description:	returns Max length of the in the paragraph
//
// Input:		Handle and token
//
// Output:		Length
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN HiiMyGetMultiLineStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token )
{
	CHAR16 *string;
	UINTN length = 0,MaxLength=0;
	UINTN i,j;

	string = HiiGetString( handle, token );
	if ( string == NULL )
		return length;

	i=j=0;
	while(string[i])
	{
		// is Newline
		if((string[i]==0x0d)&& (string[i+1]==0x0a))
		{
			string[i]=0x0;
			length = TestPrintLength( &string[j] ) / (NG_SIZE);
			if(length>MaxLength)
				MaxLength = length;
			i+=2;
			j=i;
		}
		else
			i++;
	}
	length = TestPrintLength( &string[j] ) / (NG_SIZE);
	MemFreePointer( (VOID **)&string );

	if(length>MaxLength)
		MaxLength = length;

	return MaxLength;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:		GetAcknowledgementKey
//
// Description:		Waits for a Key Press
//
// Parameter:		VOID
//
// Return value:	EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetAcknowledgementKey()
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN Index;
    EFI_INPUT_KEY Key;

	//Flush Key Stroke
	while(gST->ConIn->ReadKeyStroke( gST->ConIn, &Key ) == EFI_SUCCESS)
		;

	status = gBS->WaitForEvent( 1, &gST->ConIn->WaitForKey, &Index );
	if(EFI_ERROR(status))
	{
		goto DONE;
	}

	status = gST->ConIn->ReadKeyStroke( gST->ConIn, &Key );

DONE:
	return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure  : HiiChangeString
//
// Description  : to change a existing string
//
// Input    : VOID* handle, UINT16 token, CHAR16 *string
//
// Output   : Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 HiiChangeString( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token, CHAR16 *string )
{
/*  return HiiChangeStringLanguage( handle, token, L"   ", string );*/
  UINTN i;
  UINT16 returntoken;
  UINT16 status = token;

  for ( i = 0; i < gLangCount; i++ )
    {
      returntoken = HiiChangeStringLanguage( handle, token, gLanguages[i].Unicode, string );
        if (( token != returntoken ) && ( INVALID_TOKEN != returntoken ))
		{
			//EIP 25092 : Fix to Use the HiiChangeString() to Add the string for morethen one langs.
			//with the same token.
   	        token = status = returntoken;
		}

    }
  return status;
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
EFI_STATUS GetFormSetTitleAndHelp(EFI_HII_HANDLE Handle, EFI_STRING_ID *Title, EFI_STRING_ID *Help)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_IFR_FORM_SET *formSet = NULL;
  UINT32 index = 0;
  UINT8 *pkgHdr = NULL;


  for(index = 0; index < gSetupCount; index++)
  {
    if(gSetupData[index].Handle == Handle)
    {
      pkgHdr = (UINT8*)gSetupData[index].FormSet;
      formSet = (EFI_IFR_FORM_SET*)(pkgHdr + sizeof(EFI_HII_PACKAGE_HEADER));
      *Title = formSet->FormSetTitle;
      *Help = formSet->Help;
      break;
    }
  }

  if(index == gSetupCount)
  {
    status = EFI_INVALID_PARAMETER;
  }

  return status;
}

/*
VOID HiiTestFormBrowser(EFI_HANDLE Handle )
{
		EFI_HII_HANDLE	hHandle[3];
		EFI_FORM_BROWSER2_PROTOCOL * pfb;

		_HiiLocateSetupHandles();
		hHandle[0] = gSetupHandles[1];
		hHandle[1] = gSetupHandles[3];
		hHandle[2] = gSetupHandles[4];

		gBS->HandleProtocol(Handle,&gEfiFormBrowser2ProtocolGuid,&pfb);
		pfb->SendForm(pfb,(EFI_HII_HANDLE *)&hHandle,3,NULL,0,NULL,NULL);
}
*/

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   HandleNewIFRPack
//
// Description: Added a new IFR pack data in gSetupData
//
// Input:	EFI_HANDLE Handle - Formset handle
//          UINT8 *PackData - New pack data to add
//
// Output:	EFI_STATUS status - EFI_OUT_OF_RESOURCES if memory allocation fails
//								EFI_SUCCESS if successful
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HandleNewIFRPack(EFI_HANDLE Handle, UINT8 *PackData)
{
  EFI_STATUS 	status = EFI_SUCCESS;
  UINTN 		length = 0;
  UINTN 		oldSetupCount = 0, size = 0; 
  UINT8 		*formSet = PackData;
  UINT32 		OldVariableCount = gVariables->VariableCount;
  UINTN 		count = gDynamicPageCount;
  EFI_GUID 		DynamicPageGuid = DYNAMIC_PAGE_COUNT_GUID;   

  SETUP_DEBUG_UEFI_NOTIFICATION ( "\n\n[TSE] Entering HandleNewIFRPack()\n\n" );     

  if(gSetupCount == 0)
  {
    goto DONE;
  }

  // Check if Handle contains an IFR formset
  //formSet = (UINT8*)HiiGetForm(Handle, 0, &length);
  if(NULL == formSet)
  {
    formSet = (UINT8*)HiiGetForm(Handle, 0, &length);
	if (NULL == formSet)
	{
	    goto DONE;
 	}	
  }

  oldSetupCount = gSetupCount++;

  // Reallocate gSetupHandles
  gSetupHandles = MemReallocateZeroPool(gSetupHandles, oldSetupCount * sizeof (EFI_HII_HANDLE), gSetupCount * sizeof (EFI_HII_HANDLE));
  if(gSetupHandles == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    goto DONE;
  }

  gSetupHandles[oldSetupCount] = Handle;

  // Reallocate and set gSetupData
  gSetupData = MemReallocateZeroPool(gSetupData, oldSetupCount * sizeof(SETUP_LINK), gSetupCount * sizeof(SETUP_LINK));
  if(gSetupData == NULL)
  {
    status = EFI_OUT_OF_RESOURCES;
    goto DONE;
  }
  MemCopy(&gSetupData[gSetupCount -1], &gSetupData[oldSetupCount -1], sizeof(SETUP_LINK));
  gSetupData[gSetupCount -1].FormSet = formSet;
  gSetupData[gSetupCount -1].Handle = Handle;
  _GetClassSubClassID(&gSetupData[gSetupCount -1]);
  status = _FxiupNotificationData(&gSetupData[gSetupCount -1]);
  UIUpdateCallbackHook((VOID*)Handle, OldVariableCount); // EIP 129750  : Modified UIUpdateCallback as module hook

  if (EFI_SUCCESS == status)//To avoid increment count incase parsing is aborted and avoid showing sub-link under advanced page
   count++ ;
   gDynamicPageCount = count ;   
   //Set Dynamic page count variable
   VarSetNvramName( L"DynamicPageCount", &DynamicPageGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &count, sizeof(count) );
   VarUpdateVariable(VARIABLE_ID_DYNAMIC_PAGE_COUNT);   //EIP_63262: Update nvram cache for DynamicPageCount

DONE:
    SETUP_DEBUG_UEFI_NOTIFICATION ( "\n\n[TSE] Exiting HandleNewIFRPack:   status = 0x%x \n\n" , status );    
  return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   HandleRemoveIFRPack
//
// Description: Removes a IFR pack data from gSetupData
//
// Input:	EFI_HANDLE Handle - Formset handle
//
// Output:	EFI_STATUS status - EFI_OUT_OF_RESOURCES if memory allocation fails
//								EFI_SUCCESS if successful
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StopRefreshOpEvent (CONTROL_INFO *controlInfo);
EFI_STATUS HandleRemoveIFRPack(EFI_HANDLE Handle)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN ii = 0, size = 0;
  UINTN count = gDynamicPageCount;
  EFI_GUID 	DynamicPageGuid = DYNAMIC_PAGE_COUNT_GUID; 

  SETUP_DEBUG_UEFI_NOTIFICATION ( "\n\n[TSE] Entering HandleRemoveIFRPack()\n\n" );     

  if(gSetupCount == 0)
  {
    goto DONE;
  }

  for(ii = 0; ii < gPages->PageCount; ii++)
  {
    UINTN control = 0;
    PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[ii]);

    if(pageInfo->PageHandle != Handle)
    {
      continue;
    }
    for(control= 0; (control < pageInfo->PageControls.ControlCount); control++)
    {
      CONTROL_INFO *controlInfo = NULL;

      controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);
      if (controlInfo->ControlFlags.RefreshID)
      {
	      StopRefreshOpEvent (controlInfo);
      }
      controlInfo->ControlHandle = (VOID *)NULL;
    }
    PageRemoveHook (ii, (VOID *)pageInfo, pageInfo->PageHandle, pageInfo->PageFormID);
    pageInfo->PageHandle = (VOID *)(UINTN)0xFFFF;
  }

  if(count)
  {
    count-- ;
    gDynamicPageCount = count ;   
     //Set Dynamic page count variable
     VarSetNvramName( L"DynamicPageCount", &DynamicPageGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &count, sizeof(count) );
     VarUpdateVariable(VARIABLE_ID_DYNAMIC_PAGE_COUNT);     //EIP_63262: Update nvram cache for DynamicPageCount

  }  

  // Find gSetupData and free memory
  for(ii = 0; ii < gSetupCount - 1; ii++)
	{
		if(gSetupData[ii].Handle != Handle)
    {
      continue;
    }
    gSetupData[ii].ClassID = 0;
    gSetupData[ii].FormSetLength = 0;
    gSetupData[ii].Added = 0;
    gSetupData[ii].SubClassID = 0;
    MemFreePointer(&gSetupData[ii].FormSet);
    break;
	}
DONE:
    SETUP_DEBUG_UEFI_NOTIFICATION ( "\n\n[TSE] Exiting HandleRemoveIFRPack:   status = 0x%x \n\n" , status );  
  return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   HandleAddIFRPack
//
// Description: Adds a IFR pack data from gSetupData
//
// Input:	EFI_HANDLE Handle - Formset handle
//          UINT8 *PackData - Update pack data to add
//
// Output:	EFI_STATUS status - EFI_OUT_OF_RESOURCES if memory allocation fails
//								EFI_SUCCESS if successful
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS HandleAddIFRPack(EFI_HANDLE Handle, UINT8 *PackData)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN 	length = 0;
  UINTN 	ii = 0, size = 0 ;
  UINT32 	OldVariableCount = gVariables->VariableCount;
  UINTN 	count = gDynamicPageCount; 
  EFI_GUID 	DynamicPageGuid = DYNAMIC_PAGE_COUNT_GUID;
  UINT8 	*formSetData = PackData;   


  SETUP_DEBUG_UEFI_NOTIFICATION ( "\n\n[TSE] Entering HandleAddIFRPack()\n" );     

  if(gSetupCount == 0)
  {
    goto DONE;
  }

  // Find gSetupData
	for(ii = 0; ii < gSetupCount - 1; ii++)
	{
		if(gSetupHandles[ii] == Handle)
		{
			break;
		}
	}
	
	if(NULL == formSetData)
	{
		formSetData = (UINT8*)HiiGetForm(Handle, 0, &length);
		if(NULL == formSetData)
		{
			goto DONE;
		}
	}

  // If iterator ii = gSetupCount - 1 (Should not be the case)
  if(ii == gSetupCount - 1)
  {
	status = HandleNewIFRPack(Handle, formSetData);
    goto DONE;
  }

  // Replace in gSetupData
  gSetupData[ii].FormSet = formSetData;
	_GetClassSubClassID(&gSetupData[ii]);
  status = _FxiupNotificationData(&gSetupData[ii]);
  
  UIUpdateCallbackHook((VOID*)Handle, OldVariableCount); // EIP 129750  : Modified UIUpdateCallback as module hook
   
  if (EFI_SUCCESS == status)//To avoid increment count incase parsing is aborted and avoid showing sub-link under advanced page
    count++ ;
    gDynamicPageCount = count ;   
   //Set Dynamic page count variable
   VarSetNvramName( L"DynamicPageCount", &DynamicPageGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, &count, sizeof(count) );
   VarUpdateVariable(VARIABLE_ID_DYNAMIC_PAGE_COUNT);   //EIP_63262: Update nvram cache for DynamicPageCount

DONE:
  SETUP_DEBUG_UEFI_NOTIFICATION ( "\n[TSE] Exiting HandleAddIFRPack:   status = 0x%x \n\n" , status );      
  return status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: GetFormByFormID
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID *GetFormByFormID(EFI_HII_PACKAGE_HEADER *IFRData, UINT16 FormID, UINTN *Length)
{
  EFI_IFR_OP_HEADER *opHeader = NULL;
  UINTN formLength = 0;
  UINTN offset = 0;
  UINT8 *form = NULL;
  UINT8 *formBegin = NULL;
  BOOLEAN flag = TRUE;

  offset = sizeof(EFI_HII_PACKAGE_HEADER);

  ResetScopeStack();
	do
	{
    EFI_IFR_FORM *formOp = NULL;
    AMI_EFI_IFR_FORM_MAP *formMapOp = NULL;
		UINT8 scope = 0;

    opHeader = (EFI_IFR_OP_HEADER*)((UINT8*)IFRData + offset);
		switch(opHeader->OpCode)
		{
		case EFI_IFR_FORM_OP:
			formOp = (EFI_IFR_FORM*)opHeader;
			if(formOp->FormId == FormID)
			{
				formBegin = (UINT8*)opHeader;
			}
			break;
        case EFI_IFR_FORM_MAP_OP: 
			formMapOp = (AMI_EFI_IFR_FORM_MAP *)opHeader;
			if(formMapOp->FormId == FormID)
			{
				formBegin = (UINT8*)opHeader;
			}
			break;
		case EFI_IFR_END_OP:
      PopScope(&scope);
			switch(scope)
			{
			case EFI_IFR_FORM_SET_OP:
        flag = FALSE;
				break;
			case EFI_IFR_FORM_OP:
            case EFI_IFR_FORM_MAP_OP: 
				if(formBegin)
				{
					flag = FALSE;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		if(opHeader->Scope)
		{
			PushScope(opHeader->OpCode);
		}
		if(formBegin)
		{
			formLength += opHeader->Length;
		}
		offset += opHeader->Length;
	}while(flag);

	if(formLength)
	{
		form = EfiLibAllocateZeroPool(formLength);
		if (form == NULL)
		{
      goto DONE;
		}
		MemCopy(form, formBegin, formLength);
		*Length = formLength;
	}

DONE:
  ResetScopeStack();
  return form;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: GetNextForm
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *GetNextForm(EFI_HII_PACKAGE_HEADER *Package, UINT8 **IFRDataPtr, UINTN *Length)
{
  UINT8 *form = NULL;
  UINT8 *formBegin = NULL;
  UINTN offset = 0;
  UINTN formLen = 0;
  UINTN formScope = 0;
  BOOLEAN endForm = FALSE;

  static UINTN scopeCount = 0;

  if(Package == NULL)
  {
    goto DONE;
  }
  if(*IFRDataPtr == NULL)
  {
    *IFRDataPtr = (UINT8 *)Package + sizeof(EFI_HII_PACKAGE_HEADER);
    scopeCount = 0;
  }

  do
  {
    EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)(*IFRDataPtr + offset);
    switch(opHeader->OpCode)
    {
    case EFI_IFR_FORM_OP:
    case EFI_IFR_FORM_MAP_OP:
      formBegin = (UINT8 *)opHeader;
      break;
    case EFI_IFR_END_OP:
      scopeCount -= scopeCount? 1 : 0;
      formScope -= formScope? 1 : 0;
      endForm = formScope? FALSE : TRUE;
      break;
    default:
      break;
    }
    if(opHeader->Scope)
    {
      scopeCount++;
      formScope += formBegin? 1 : 0;
    }
    formLen += formBegin? opHeader->Length : 0;
    offset+=opHeader->Length;
  }while(endForm == FALSE);

  if(formBegin)
  {
    form = EfiLibAllocateZeroPool(formLen);
    if(form == NULL)
    {
      *Length = 0;
      goto DONE;
    }
    MemCopy(form, formBegin, formLen);
    *Length = formLen;
    formBegin += formLen;
    *IFRDataPtr += offset;
  }

DONE:
  return form;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: FixSetupData
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FixSetupData()
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN ii = 0;

  SETUP_DEBUG_UEFI ( "\n[TSE] Entering FixSetupData()\n" );    

  if(gIFRChangeNotify)
  {
    if(gRemovedHandle!=NULL)
    {
      UIUpdateCallbackHook((VOID*)gRemovedHandle, gVariables->VariableCount); // EIP 129750  : Modified UIUpdateCallback as module hook
      gRemovedHandle = NULL;
      gIFRChangeNotify = FALSE;
    }
  }
//EIP 88658 : Minisetup crashes after controller reconnection during Hii callback
  if((gApplicationData == NULL) || (gSetupCount == 0))
  {
    status = EFI_UNSUPPORTED;
    goto DONE;
  }

  for(ii = 0; ii < gPages->PageCount; ii++)
  {
    PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[ii]);

    if(pageInfo->PageHandle != (VOID *)(UINTN)0xFFFF)
    {
      continue;
    }
    pageInfo->PageHandle = NULL;
  }

  SETUP_DEBUG_UEFI ( "\n[TSE] Exiting FixSetupData(),  status = 0x%x \n" , status );

DONE:  
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: _FxiupNotificationData
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _FxiupNotificationData(SETUP_LINK *Setup_Link)
{
	EFI_STATUS Status = EFI_SUCCESS;
  PAGE_ID_LIST  *tempPageIdList = gPageIdList;
  PAGE_LIST     *tempPages = gPages;
  VARIABLE_LIST *tempVariables = gVariables;

  //ReInitialize Setupdata Pointers
  _ReInitializeSetupdataPointers();
  //Parse Form
  Status = ParseForm(Setup_Link);
  // Merge ListPtr and InfoPtr
	_MergePageIdListAndInfo();
	_MergeVariableListAndInfo();
	_MergePageListAndInfo();

	FixMergePagesExtraHook ((VOID *)gPages, (VOID *)tempPages );
	
  // Free memory used by temp Ptrs
  MemFreePointer((VOID**)&tempPageIdList);
  MemFreePointer((VOID**)&tempPages);
  MemFreePointer((VOID**)&tempVariables);
  
  return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: _ReInitializeSetupdataPointers
//
// Description:
//
// Parameter:
//
// Return value:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _ReInitializeSetupdataPointers()
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT32 i = 0;

  // Reinitialize PageIdListPtr and PageIdInfoPtr
  PageIdListPtr = (PAGE_ID_LIST *)EfiLibAllocateZeroPool(PageIdListSize);
	if(PageIdListPtr == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
  MemCopy(PageIdListPtr, gPageIdList, PageIdListOffset);

	//Fix Offsets
	for(i=0; i < PageIdListPtr->PageIdCount; i++)
	{
		PageIdListPtr->PageIdList[i] -= PageIdListOffset;
	}

  PageIdInfoPtr = (PAGE_ID_INFO *)EfiLibAllocateZeroPool(PageIdInfoSize);
	if(PageIdInfoPtr == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
  MemCopy(PageIdInfoPtr, (UINT8 *)gPageIdList + PageIdListOffset, PageIdInfoOffset);

  // Reinitialize PageListPtr, FirstPage and PageInfoPtr
  PageListPtr = (PAGE_LIST *)EfiLibAllocateZeroPool(PageListSize);
	if(PageIdListPtr == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
  MemCopy(PageListPtr, gPages, PageListOffset);
	//Fix Offsets
	for(i = 0; i < PageListPtr->PageCount; i++)
	{
    PageListPtr->PageList[i] -= (i == 0)? PageListOffset : (FirstPageOffset + PageListOffset);
	}

  FirstPage = (PAGE_INFO *)EfiLibAllocateZeroPool(AllocatedFirstPageSize);
	if(FirstPage == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
  MemCopy(FirstPage, (UINT8 *)gPages + PageListOffset, FirstPageOffset);

  PageInfoPtr = (PAGE_INFO *)EfiLibAllocateZeroPool(PageInfoSize);
	if(PageInfoPtr == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
  MemCopy(PageInfoPtr, (UINT8 *)gPages + PageListOffset + FirstPageOffset, PageInfoOffset);

  // Reinitialize VariableInfoPtr and VariableListPtr
  VariableListPtr = (VARIABLE_LIST *)EfiLibAllocateZeroPool(VariableListSize);
	if(VariableListPtr == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
  MemCopy(VariableListPtr, gVariables, VariableListOffset);

	//Fix Offsets
	for(i=0; i < VariableListPtr->VariableCount; i++)
	{
		VariableListPtr->VariableList[i] -= VariableListOffset;
	}

  VariableInfoPtr = (VARIABLE_INFO *)EfiLibAllocateZeroPool(VariableInfoSize);
	if(VariableInfoPtr == NULL)
	{
		status = EFI_OUT_OF_RESOURCES;
		goto DONE;
	}
  MemCopy(VariableInfoPtr, (UINT8 *)gVariables + VariableListOffset, VariableInfoOffset);

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RTIfrUpdateVariableInfo
//
// Description:	Wrapper function to include RTIfrUpdateVariableInfo
//              based on SDL token.
//
// Input:		ControlVariable
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RTIfrUpdateVariableInfo( UINT32 ControlVariable, EFI_HANDLE Handle )
{
	VARIABLE_INFO  *varInfo = NULL;
//    UINT16		*varString;
//    UINT16        StringToken = 0;


   if (ControlVariable < VariableListPtr->VariableCount)
   {
      varInfo = (VARIABLE_INFO*)((UINT8*)VariableInfoPtr + VariableListPtr->VariableList[ControlVariable]);
      if(varInfo->VariableHandle == NULL)
      {
   	   varInfo->VariableHandle = Handle;
      }
      //EIP56405: Commented for suppressing build time parsing. Name value not supported by current vfr compiler. Uncomment it once vfr compiler supports it.
      /*if (VARIABLE_ATTRIBUTE_NAMEVALUE == (varInfo->ExtendedAttibutes & VARIABLE_ATTRIBUTE_NAMEVALUE))
      {
         if (0 == (EfiStrLen (varInfo->VariableName)))
         {
            StringToken = (UINT16)((UINT16)(varInfo->NameValueToken [1] << 8) + (UINT8)(varInfo->NameValueToken [0]));
            varString = HiiGetString (varInfo->VariableHandle, StringToken);
            EfiStrCpy (varInfo->VariableName, varString);
         }
      }*/
   }else
   {
      // ERROR. This case should not Occur.If it Does then DOOM!!!
   }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiGetEfiKey
//
// Description:	Function to Encode the password key
//
// Input:	CHAR16 *PwKey
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID HiiGetEfiKey(CHAR16 *PwKey)
{
// Need to fix this for UEFI 2.1
/*
  EFI_HII_KEYBOARD_LAYOUT *Key
    EFI_KEY_DESCRIPTOR *pEfiKD = NULL;	//, *pRetEfiKD = NULL;
    UINT16  Count = 0,i;
    EFI_STATUS Status;

    if(EFI_SUCCESS != HiiInitializeProtocol())
        return;

    //Get Count (No Of Key board Desc)
    Status= gHiiDatabase->GetKeyboardLayout(gHiiDatabase, NULL, &Count, pEfiKD);

    if(EFI_BUFFER_TOO_SMALL != Status)
        return;

    if(Count)
    {
        //Allocate space for Count number of EFI_KEY_DESCRIPTOR
        pEfiKD = EfiLibAllocateZeroPool(sizeof(EFI_KEY_DESCRIPTOR)*Count);

        Status= gHiiDatabase->GetKeyboardLayout(gHiiDatabase, &Count, pEfiKD);

        if(EFI_SUCCESS == Status)
        {
            for(i=0;i<Count;i++)
            {
                if((pEfiKD[i].Unicode == *PwKey) ||
                    (pEfiKD[i].ShiftedUnicode == *PwKey) ||
                    (pEfiKD[i].AltGrUnicode == *PwKey) ||
                    (pEfiKD[i].ShiftedAltGrUnicode == *PwKey)
                    )
                {
//                  pRetEfiKD = EfiLibAllocateZeroPool(sizeof(EFI_KEY_DESCRIPTOR));
//                  MemCopy(pRetEfiKD, pEfiKD+i,sizeof(EFI_KEY_DESCRIPTOR));
                    *PwKey = (CHAR16)(pEfiKD+i)->Key;
                    break;
                }
            }
        }
        MemFreePointer((VOID **)&pEfiKD);
    }
*/
}
//EIP:56413 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiupdateResetButtonDefault
//
// Description:	Function to update defaults depending on the Default Id on Selecting the Reset Button
//
// Input:	CONTROL_INFO ControlData, UINT16 DefaultId
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiupdateResetButtonDefault(CONTROL_INFO ControlData, UINT16 DefaultId)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINT32 control, offset = 0;
	UINTN index=0, size = 0;
	UINT8 *Defaultaddress = 0;

   //Getting the current page info	
	PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[ControlData.ControlPageID]);
	
	if (NULL != pageInfo && 0 == pageInfo->PageHandle)
			return EFI_UNSUPPORTED;

	for ( control= 0; control < pageInfo->PageControls.ControlCount; control++ )
	{
		CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);
		index=0;
		//checking for the Default count of the control
		while(index  <  controlInfo->DefaultStoreCount)
		{
			Defaultaddress = (UINT8 *)controlInfo + sizeof(CONTROL_INFO)+(controlInfo->ControlDataWidth * 2)+(index *(sizeof(UINT16) + controlInfo->ControlDataWidth));
				//checking for the default Id of the Resetbutton
				if(DefaultId == (UINT16)*Defaultaddress)
				{
						offset = UefiGetQuestionOffset(controlInfo->ControlPtr);
	 					size = UefiGetWidth(controlInfo->ControlPtr);
						status = VarSetValue(controlInfo->ControlVariable, offset, size, Defaultaddress+sizeof(UINT16) );
				}
				index++;
		}
		//EIP:57402  Checking for the ControlEvaluateDefault Flag and the Default Id equal tp Manufacturing Id 
		 if(controlInfo->ControlFlags.ControlEvaluateDefault)
		 {
			 UINT64 Defaults = 0 ;
			 UINT16 size = 0;
			 offset = UefiGetQuestionOffset(controlInfo->ControlPtr);
			 
			 //EIP: 57402 Evaluating the Control Default
				size = EvaluateControlDefault(controlInfo,&Defaults);
				status = VarSetValue(controlInfo->ControlVariable, offset, size, &Defaults );
				// EIP: 57402 Setiing the Evaluated value to the gOptimalDefaults
				if(DefaultId == EFI_HII_DEFAULT_CLASS_MANUFACTURING)
				_VarGetSetValue( VAR_COMMAND_SET_VALUE, gOptimalDefaults, controlInfo->ControlVariable, offset, size, &Defaults );
		 }
	}

	return status;

}
//EIP:56413 END

//EIP-83080 Start
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   GetDevPathFromHandle
//
// Description: Get the device path for the the given handle
//
// Input:	EFI_HII_HANDLE HiiHandle - Input handle
//          EFI_DEVICE_PATH_PROTOCOL **DevicePath - Corresponding device path
//                                     if successful.
//
// Output:	EFI_STATUS Status - EFI_SUCCESS, if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetDevPathFromHandle(EFI_HII_HANDLE HiiHandle, EFI_DEVICE_PATH_PROTOCOL **DevicePath)
{
  EFI_STATUS Status = EFI_INVALID_PARAMETER;
  EFI_HANDLE DriverHandle = (EFI_HANDLE)NULL;
  EFI_DEVICE_PATH_PROTOCOL *TempDevPath = (EFI_DEVICE_PATH_PROTOCOL *)NULL;

  *DevicePath = TempDevPath;

  Status = gHiiDatabase->GetPackageListHandle (gHiiDatabase, HiiHandle, &DriverHandle);
  if(EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->HandleProtocol (DriverHandle, &gEfiDevicePathProtocolGuid, &TempDevPath);
  if(Status == EFI_SUCCESS){
    *DevicePath = TempDevPath;
  }

  return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   GetStringFromDevPath
//
// Description: Gets the string presentation of the given DevicePath
//
// Input:	EFI_DEVICE_PATH_PROTOCOL *DevPath - Given device path
//          CHAR16 **DevPathStr - Return pointer to the string presentation
//
// Output:	EFI_STATUS status - EFI_SUCCESS, if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetStringFromDevPath(EFI_DEVICE_PATH_PROTOCOL *DevPath, CHAR16 **DevPathStr)
{
  EFI_STATUS status = EFI_ABORTED;
  
  if(gDevPathToTextProtocol == NULL)
  {
    status = gBS->LocateProtocol(&gDevPathToTextGuid, NULL, &gDevPathToTextProtocol);
  }
  if(gDevPathToTextProtocol != NULL)
  {
    *DevPathStr = gDevPathToTextProtocol->ConvertDevicePathToText(DevPath, FALSE, FALSE);
    status = EFI_SUCCESS;
  }
  return status;
}
//EIP: 83080 End


//EIP: 132359 Start
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   FixIFRRefXControl
//
// Description: Updates the parent pageID for the EFI_IFR_REFX
//              control
//
// Input:	CONTROL_INFO * CtrlInfo - Control Info in the library
//          PAGE_INFO *PageInfo - Page Info in the library
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FixIFRRefXControl(PAGE_INFO *PageInfo, CONTROL_INFO * CtrlInfo)
{
  EFI_STATUS status = EFI_NOT_FOUND;
  UINT32 		i=0;
  PAGE_INFO 	*pageInfo;
  
  for (i = 0; i < gPages->PageCount; i++)
  {
	pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[i]);
	if (pageInfo->PageID == CtrlInfo->ControlDestPageID)
	{
		pageInfo->PageParentID = PageInfo->PageID ; //CtrlInfo->ControlPageID;
		status = EFI_SUCCESS;
		break;
	}
  }
    
  return status;
}
//EIP: 55762 Start
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   UpdateIFRRefXControls
//
// Description: Updates the reference link information in for the EFI_IFR_REFX
//              controls
//
// Input:	CONTROL_INFO * CtrlInfo - Control Info in the library
//          BOOLEAN *PgHasRefXCtrl - Return TRUE if REF4 control found
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UpdateIFRRefXControls(PAGE_INFO *PageInfo, CONTROL_INFO * CtrlInfo)
{
    EFI_STATUS status = EFI_SUCCESS;
    EFI_DEVICE_PATH_PROTOCOL *tempDevPath = (EFI_DEVICE_PATH_PROTOCOL *)NULL;
    BOOLEAN IsQuestionIdValid = FALSE;
    BOOLEAN IsFormSetIdValid = FALSE;
    BOOLEAN IsDevicePathFound = FALSE;
    EFI_GUID formSetGuid = {0}, zeroFormSetGuid = {0};
    UINT16 ControlDestPageID = 0xFFFF;
    UINT16 ControlDestQuestionID = 0xFFFF;
    UINTN count = 0;
    UINTN control = 0;
    PAGE_INFO *pageInfo = (PAGE_INFO*)NULL;
    PAGE_ID_INFO *pageIdInfo = (PAGE_ID_INFO*)NULL;
  
    CHAR16 *devPathStr = (CHAR16 *)NULL, *tempDevPathStr = (CHAR16 *)NULL;

    if((CtrlInfo == NULL) || (CtrlInfo->ControlPtr == NULL))
    {
        status = EFI_INVALID_PARAMETER;
        goto DONE;
    }

    if(CtrlInfo->ControlHandle == NULL)
    {
        status = EFI_INVALID_PARAMETER;
        goto DONE;
    }   

    if(((EFI_IFR_OP_HEADER*)CtrlInfo->ControlPtr)->OpCode != EFI_IFR_REF_OP)
    {
        status = EFI_INVALID_PARAMETER;
        goto DONE;
    }

    //EIP109812, 107774
    if(((EFI_IFR_OP_HEADER *)CtrlInfo->ControlPtr)->Length == sizeof(AMI_EFI_IFR_REF5)) //If AMI_EFI_IFR_REF5
    {
        if(CtrlInfo->ControlDataLength == sizeof(AMI_EFI_HII_REF)) //if default value is of size AMI_EFI_HII_REF, retrieve its value
        {        
            AMI_EFI_HII_REF *Ref = NULL ;
            Ref = (AMI_EFI_HII_REF*)((UINT8*)CtrlInfo + sizeof(CONTROL_INFO) + CtrlInfo->ControlDataLength); //take the default value
            if(Ref) 
            {
                //fetch the destination questionId
                ControlDestQuestionID = Ref->QuestionId; //Set the destination question ID to set focus
                if(Ref->DevicePath) //if device path is provided
                {
                    devPathStr = HiiGetString(CtrlInfo->ControlHandle, Ref->DevicePath); //get the text representation of device path
                    if(devPathStr == NULL) //If the device path string is invalid, remain the same
                    {
                        CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page
                        CtrlInfo->DestQuestionID = CtrlInfo->QuestionId; //set the current control's question Id as the destination question Id.
                        goto DONE;
                    } 
                    else 
                    { //If the device path string is not NULL
                        CHAR16 *zeroDevPathStr = (CHAR16 *)EfiLibAllocateZeroPool(MAX_DEV_PATH_STR_LEN * sizeof(CHAR16));
                        if(zeroDevPathStr)
                        {
                            //MemSet(&zeroDevPathStr[0], MAX_DEV_PATH_STR_LEN * sizeof(CHAR16), L'0');
                            MemSet(&zeroDevPathStr[0], MAX_DEV_PATH_STR_LEN * sizeof(CHAR16), 0);
                            if(EfiStrCmp(devPathStr, zeroDevPathStr) == 0) //If the DevicePath string contains all zeros, remain the same page.
                            {
                                CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page
                                CtrlInfo->DestQuestionID = CtrlInfo->QuestionId; //set the current control's question Id as the destination question Id.
                                goto DONE;
                            }
                        }
                    }
                    //Device Path is not zero. check whether the provided device path is found.
                    for(count = 0; count < gPages->PageCount; count++)
                    {
                        PAGE_INFO *tempPageInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[count]);
                        if(tempPageInfo == NULL)
                        {
                            continue;
                        }
                        status = GetDevPathFromHandle(tempPageInfo->PageHandle, &tempDevPath);
                        if((status == EFI_SUCCESS) && (tempDevPath != NULL))
                        {
                            GetStringFromDevPath(tempDevPath, &tempDevPathStr);
                            if(EfiStrCmp(devPathStr, tempDevPathStr) == 0) //if the provided device path is found
                            {
                                CtrlInfo->ControlDestPageID = tempPageInfo->PageID; //set that page ID
                                ControlDestPageID = tempPageInfo->PageID;
                                IsDevicePathFound = TRUE;
                                break;
                            }
                        }
                    }
                    if(!IsDevicePathFound) //if provided device path is not found, remain the same
                    {
                        CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page;
                        CtrlInfo->DestQuestionID = CtrlInfo->QuestionId; //set the current control's page ID itself as destination page Id.
                        goto DONE;
                    }
                }
                else //if device path is not provided
                {
                    //get formset GUID
                    MemCopy(&formSetGuid, &(Ref->FormSetGuid), sizeof (EFI_GUID));
		            if(EfiCompareGuid(&formSetGuid, &zeroFormSetGuid) == FALSE) //If it is not all zeroes
		            {
			            GetPageIdFromGuid(&formSetGuid, Ref->FormId, &ControlDestPageID);
			            if(ControlDestPageID != 0xFFFF) //If the destination page ID is valid
			            {
			                CtrlInfo->ControlDestPageID = ControlDestPageID; //Assign it to CONTROL_INFO->ControlDestPageID
			                IsFormSetIdValid = TRUE;
			            }
		            }
                    if(!IsFormSetIdValid) //if formset Id is invalid, remain the same
                    {
                        CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page;
                        CtrlInfo->DestQuestionID = CtrlInfo->QuestionId; //set the current control's page ID itself as destination page Id.
                        goto DONE;
                    }
                }
                //at this point either through device path or formset ID the destination page ID will be obtained.
                //check whether the provided Dest. Question ID exist in that destination page
                pageInfo = (PAGE_INFO*)((UINT8 *)gPages + gPages->PageList[ControlDestPageID]);                
                if(pageInfo->PageHandle == NULL)
                {
                    CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page;
                    CtrlInfo->DestQuestionID = CtrlInfo->QuestionId; //set the current control's page ID itself as destination page Id.
                    goto DONE;
                }
                for(control = 0; control < pageInfo->PageControls.ControlCount; control++) //check if the destination Question ID is exists in any of
                { //the availble controls of the page.
                    CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);
                    if(ControlDestQuestionID == controlInfo->ControlKey)
                    {
                        IsQuestionIdValid = TRUE;
                        CtrlInfo->ControlDestPageID = ControlDestPageID; //Assign it to CONTROL_INFO->ControlDestPageID
                        CtrlInfo->DestQuestionID = ControlDestQuestionID;
                        break;
                    }                    
                }
                if(!IsQuestionIdValid) //if the provided Question ID is invalid, remain the same
                {
                    CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page;
                    CtrlInfo->DestQuestionID = CtrlInfo->QuestionId; //set the current control's page ID itself as destination page Id.
                }
            }
        }
    }

    else if(((EFI_IFR_OP_HEADER *)CtrlInfo->ControlPtr)->Length >= sizeof(EFI_IFR_REF2)) //If EFI_IFR_REFX
    {
	    CtrlInfo->DestQuestionID = ((EFI_IFR_REF2 *)CtrlInfo->ControlPtr)->QuestionId; //Set the destination question ID to set focus

	    if(((EFI_IFR_OP_HEADER *)CtrlInfo->ControlPtr)->Length >= sizeof(EFI_IFR_REF3)) //If EFI_IFR_REF3/EFI_IFR_REF4
	    {

		    MemCopy(&formSetGuid, &((EFI_IFR_REF3 *)CtrlInfo->ControlPtr)->FormSetId, sizeof (EFI_GUID));

		    if(EfiCompareGuid(&formSetGuid, &zeroFormSetGuid) == FALSE) //If it is not all zeroes
		    {
			    GetPageIdFromGuid(&formSetGuid, ((EFI_IFR_REF3 *)CtrlInfo->ControlPtr)->FormId, &ControlDestPageID);
			    if(ControlDestPageID != 0xFFFF) //If the destination page ID is valid
			    {
			     CtrlInfo->ControlDestPageID = ControlDestPageID; //Assign it to CONTROL_INFO->ControlDestPageID
			     IsFormSetIdValid = TRUE;
			     FixIFRRefXControl(PageInfo, CtrlInfo);
			    }
		    }

		    if(((EFI_IFR_OP_HEADER *)CtrlInfo->ControlPtr)->Length >= sizeof(EFI_IFR_REF4)) //If EFI_IFR_REF4
		    {
    			

				devPathStr = HiiGetString(CtrlInfo->ControlHandle, ((EFI_IFR_REF4 *)CtrlInfo->ControlPtr)->DevicePath);
				if(devPathStr == NULL) //If the device path string is invalid
				{
					CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page
					goto DONE;
				} 
				else 
				{ //If the device path string is valid
					CHAR16 *zeroDevPathStr = (CHAR16 *)EfiLibAllocateZeroPool(MAX_DEV_PATH_STR_LEN * sizeof(CHAR16));
					if(zeroDevPathStr)
					{
						MemSet(&zeroDevPathStr[0], MAX_DEV_PATH_STR_LEN * sizeof(CHAR16), L'0');
						if(EfiStrCmp(devPathStr, zeroDevPathStr) == 0) //If the DevicePath string contains all zeros
						{
							CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page
							goto DONE;
						}
					}
				}

			    for(count = 0; count < gPages->PageCount; count++)
			    {
				    PAGE_INFO *tempPageInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[count]);
				    if(tempPageInfo == NULL)
				    {
					    continue;
				    }
				    status = GetDevPathFromHandle(tempPageInfo->PageHandle, &tempDevPath);
				    if((status == EFI_SUCCESS) && (tempDevPath != NULL))
				    {
					    GetStringFromDevPath(tempDevPath, &tempDevPathStr);
					    if(EfiStrCmp(devPathStr, tempDevPathStr) == 0)
					    {
						    CtrlInfo->ControlDestPageID = tempPageInfo->PageID;
                      IsDevicePathFound = TRUE;
						    break;
					    }
				    }
			    }
                if(!IsDevicePathFound) //the provided device path is not found, hence remain in the same page.
                {
                    CtrlInfo->ControlDestPageID = PageInfo->PageID; //The link refers to the current page
                    goto DONE;
                }
		    } 
		    else
		    { //If the Device path is not present
			    if(IsFormSetIdValid == FALSE) //If the FormSetId is invalid
			    {
				    PAGE_ID_INFO *pageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[PageInfo->PageIdIndex]);
				    if(pageIdInfo)
				    {
					    ControlDestPageID = 0xFFFF;
					    GetPageIdFromGuid(&(pageIdInfo->PageGuid), ((EFI_IFR_REF3 *)CtrlInfo->ControlPtr)->FormId, &ControlDestPageID);
					    if(ControlDestPageID != 0xFFFF) //If the destination page ID is valid, assign it to CONTROL_INFO->ControlDestPageID
					    {
					      CtrlInfo->ControlDestPageID = ControlDestPageID;
					    }
				    }
			    }
		    }
	    }
    }

DONE:	
  return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   GetPageIdFromGuid
//
// Description: Finds the page ID with matching Guid from the page list
//
// Input:	EFI_GUID *FormGuid
//          UINT16 *PageID
//
// Output:	EFI_STATUS status - EFI_SUCCESS, if successful,
//                              EFI_INVALID_PARAMETER, if invalid values found
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPageIdFromGuid(EFI_GUID *FormGuid, UINT16 PageFormID, UINT16 *PageID)
{
  EFI_STATUS status = EFI_INVALID_PARAMETER;
  UINT32 pgIndex = 0;
  PAGE_INFO *pgInfo = (PAGE_INFO *)NULL;
  PAGE_ID_INFO *pageIdInfo = (PAGE_ID_INFO*)NULL;

  if(gPages && gApplicationData && gPageIdList)
  {
    for(pgIndex = 0; pgIndex < gPages->PageCount; pgIndex++)
    {
      pgInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[pgIndex]);
      if ((NULL != pgInfo) && (NULL == pgInfo->PageHandle))		//EIP133981 if relash module formsetguid passed then it will return the pageid
          continue;															//so this should not happen when the resource not published so added the condition
      if(pgInfo->PageFormID == PageFormID)
      {
        pageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[pgInfo->PageIdIndex]);
        if(pageIdInfo && (EfiCompareGuid(FormGuid, &(pageIdInfo->PageGuid)) == TRUE))//Compare Guid
        {
          *PageID  = pgInfo->PageID;
          status = EFI_SUCCESS;
		  goto DONE;
        }
      }
    }
  }

DONE:
  return status;
}
//EIP: 55762 End

//EIP75588 starts
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   FindHandleWithInSetupData
//
// Description: Checks if the given handle is avaiable in the scope of the
//              current formset.
//
// Input:	EFI_HII_HANDLE Handle
//
// Output:	EFI_STATUS Status - EFI_NOT_FOUND, if not found, else EFI_SUCCESS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FindHandleWithInSetupData (EFI_HII_HANDLE Handle)
{
  EFI_STATUS 	Status = EFI_NOT_FOUND;
  UINTN 			i = 0;

  if (gSetupData) //Check if the notification is within out formset's scope
  {
    for (i = 0; i < gSetupCount; i++)
    {
      if (gSetupData[i].Handle == Handle)
      {
        Status = EFI_SUCCESS;
        break;
      }
    }
  }
  return Status;
}
//EIP75588 ends

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:     GetRWVariableID
//
// Description:   Returns the variable ID for read write operation
//
// Input:	      UINT16, CONTROL_INFO *, UINT16 *
//
// Output:	      EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetRWVariableID (UINT16 RWVarStoreId, CONTROL_INFO *ControlInfo, UINT16 *VarStoreId)
{
   VARIABLE_INFO 	*varInfo = NULL;
   UINT32         		index = 0;

   for (index = 0; index < gVariables->VariableCount; index++)
   {
      varInfo = (VARIABLE_INFO *)VarGetVariableInfoIndex(index);
      //EIP-75352 Suppress the warnings from static code analyzer
      if(NULL == varInfo)
      {
         continue;
      }
      if ((ControlInfo->ControlHandle == varInfo->VariableHandle) && (varInfo->VariableID == RWVarStoreId))
      {
            *VarStoreId = index;
            return EFI_SUCCESS;
      }
   }
   return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:     StopRefreshOpEvent
//
// Description:   Stops the refresh event
//
// Input:	      CONTROL_INFO *
//
// Output:	      VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StopRefreshOpEvent (CONTROL_INFO *controlInfo)
{
	CONTROL_INFO 	*RefreshEventcontrolInfo = (CONTROL_INFO *)NULL;
	UINTN 				index;
	EFI_STATUS 		Status = EFI_UNSUPPORTED;
	
	if (gRefreshIdInfo)
	{
		for(index = 0; index < gRefreshIdCount; index++) 
		{
			if(gRefreshIdInfo[index].pEvent) //Close the event
			{
				RefreshEventcontrolInfo = (CONTROL_INFO *)gRefreshIdInfo[index].pNotifyContext;
				if (
					(controlInfo->ControlHandle == RefreshEventcontrolInfo->ControlHandle) && 
					(controlInfo->ControlConditionalPtr == RefreshEventcontrolInfo->ControlConditionalPtr) &&
					(controlInfo->ControlPtr == RefreshEventcontrolInfo->ControlPtr)
					)
				{
					Status = gBS->CloseEvent (gRefreshIdInfo[index].pEvent);
					if(Status == EFI_SUCCESS)
					{
						gRefreshIdInfo[index].pEvent = NULL;
					}								//Dont free the pNotifyContext might be using in formcallback, so freeing here will crash in formcallback. Free in MiniSetupUIExit
					break;
				}
			}
		}
	}
}

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