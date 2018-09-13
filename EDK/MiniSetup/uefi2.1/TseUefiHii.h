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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/TseUefiHii.h $
//
// $Author: Arunsb $
//
// $Revision: 39 $
//
// $Date: 2/11/14 8:55p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/TseUefiHii.h $
// 
// 39    2/11/14 8:55p Arunsb
// EFI_IFR_EQ_ID_LIST_OP entry added
// 
// 38    12/04/13 2:57a Premkumara
// [TAG]	EIP139099
// [Category]	New Feature
// [Description]	Supress formset other than
// EFI_HII_PLATFORM_SETUP_FORMSET_GUID and
// EFI_HII_DRIVER_HEALTH_FORMSET_GUID through elink based on token
// [Files]	AMITSE.sdl, AMITSE.mak, CommonOem.c, Hii.c, Parse.c,
// TseUefiHii.h
// 
// 37    6/10/13 12:23p Arunsb
// EIP122907 GetDefaultValue function argument added for
// EFI_IFR_TYPE_OTHER support.
// 
// 36    5/22/13 11:12a Arunsb
// Build error rectified
// 
// 35    4/18/13 9:37a Arunsb
// Opcodes added to avoid build error in 2.0 build.
// 
// 34    4/17/13 2:12p Arunsb
// [TAG]  		EIP109812, 107774
// [Category]  	Improvement
// [Description]  	Provide support for EFI_IFR_TYPE_REF and EFI_IFR_REF5
// [Files]  		Hii.c, HiiCallback.c, Parse.c and TseUefiHii.h
// 
// 33    4/16/13 9:49a Arunsb
// Missed out Hii headers and structures added.
// 
// 32    3/29/13 12:26p Premkumara
// [TAG]  		EIP97611
// [Category]  	New Feature
// [Description]  	PrintScreen Support in TSE
// [Files]  		AMITSE.sdl, CommonHelper.c, HotKeyBin.h, AddBootOption.c,
// Page.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 31    3/29/13 8:21a Arunsb
// [TAG]  			EIP111061 
// [Category]  	Improvement
// [Description]  	Provide support for efivarstore opcode
// [Files]  		Parse.c and tseuefihii.h
// 
// 30    2/25/13 10:57a Blaines
// [TAG] - EIP 104273
// [Category] - Action Item
// [Description] -  Provide ability to dump the Hii Pack from the Setup as
// part TSE debug Infrastructure. It should dump the Pack updates on Hii
// notification also.
// So it can be used to debug the issue.
// [Files] - ForBrowser2.c,  Hii.c,  HiiNotificationHandler.c,
// UefiWapper.c,  TseUefiHii.h
// 
// 29    10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 27    2/02/12 3:05a Premkumara
// [TAG]  		EIP75066 
// [Category]  	Improvement
// [Description]  	Support loading defaults for Ordelist controls
// [Files]  		Ordlistbox.c, Uefi21Wapper.c, CtrlCond.c, HiiCallback.c,
// Parse.c, Uefi20Wapper.c, TseUefihiil.h
// 
// 26    12/07/11 2:50p Arunsb
// [TAG]  		EIP75588
// [Category]  	New Feature
// [Description]  	Support for queuing UpdatePack notifications
// [Files]  		frame.c, page.c, formbrowser2.c, hii.c, hiicallback.c,
// hiinotificationhandler.c, tseuefihii.h and uefi21wapper.c
// 
// 25    12/01/11 7:27a Arunsb
// UefiGetValidOptionSize declaration removed. To resolce build error in
// 2.0
// 
// 24    11/28/11 5:13a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 23    11/23/11 5:17a Rajashakerg
// [TAG]  		EIP75473 
// [Category]  	Improvement
// [Description]  	System Time is not updated every second
// [Files]  		variable.h, variable.c, FormBrowser2.c, TseUefiHii.h,
// Uefi21Wapper.c, hii.h, uefi20Wapper.c
// 
// 22    11/14/11 2:43p Blaines
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
// 21    11/03/11 4:44a Premkumara
// [TAG]  		EIP70966
// [Category]  	Improvement
// [Description]  	Hii orderlist item can't update priority from value in
// Setup menu for both enable and disable TSE_MULTILINE_CONTROLS token
// [Files]  		Ordlistbox.c, ordlistbox.h, TseUefiHii.h, Uefi21Wrapper.c
// 
// 20    10/20/11 12:25p Blaines
// Correct the comments.
// 
// 19    10/20/11 11:48a Blaines
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
// 18    9/29/11 7:02p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c
// 
// 17    6/20/11 12:20p Rajashakerg
// [TAG]  		EIP57402 
// [Category]  	New Feature
// [Description]  	Support for EFI_IFR_DEFAULT_2 opcode.
// [Files]  		Hii.c, TseUefiHii.h
// 
// 16    4/04/11 10:34a Arunsb
// Added macros compatible UEFI 2.3
// 
// 15    3/28/11 9:44p Premkumara
// [TAG]  		EIP52562 
// [Category]  	Improvement
// [Description]  	Need to have the Fixed Limit in AMITSE module for
// Controls, Pages and Variable etc.
// 
// [Files]  		TSEUefiiHii.h, Parse.c, Hii.c, hii.c
// 
// 14    3/28/11 5:10p Rajashakerg
// [TAG]  		EIP56413 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_RESET_BUTTON opcode
// [Files]  		ezport.c, minisetupext.h, ResetButton.c, ResetButton.h,
// Hii.c, TseUefiHii.h, Uefi21Wapper.c, hii.h, Uefi20Wapper.c 
// 
// 13    3/21/11 1:00a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 12    3/18/11 2:52a Rajashakerg
// [TAG]  		EIP56124
// [Category]  	New Feature
// [Description]  	TSE: Support for EFI_IFR_DEFAULT opcode
// [Files]  		Parse.c, TseUefiHii.h 
// 
// 11    3/09/11 7:26p Madhans
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
// 10    2/01/11 7:38p Madhans
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
// 9     12/28/10 12:31p Madhans
// To update the Tag of EIp 46998. UEFI option ROM menus disappear in
// Setup when certain options are selected. 
// No file changed but Comment updated right
// 
// 8     12/02/10 6:09p Madhans
// [TAG] - EIP49562    
// [Category]- Improvment.
// [Severity]- Mordarate
// [Symptom]- Need to support UEFI 2.2 requirements related to Calling
// Formcallback with 
// EFI_BROWSER_ACTION_CHANGING and EFI_BROWSER_ACTION_CHANGED action.
// [Solution]- Implemented the support.
// [Files] - submenu.c, numeric.c, popupsel.c, popupString.c,
// uefi20\hii.h, uefi20\uefi20wrapper.c
// uefi21\hiicalback.c, uefi21\tseuefihii.h
// 
// 7     10/27/10 4:25p Madhans
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
// 6     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 6     7/07/10 7:45p Madhans
// Changes to Support Adding Conditions to Suppress or Grayout the Special
// controls.
// 
// 5     6/14/10 7:14p Madhans
// Dynamic parsing support
// 
// 4     3/11/10 5:44p Madhans
// Coding Standards Update
//
// 3     2/26/10 7:01p Madhans
// To build with EDK
//
// 1     11/19/09 5:26p Presannar
//
// 2     8/11/09 3:00p Presannar
// Added Fn signature FixSetupData, HandleNewIFRPack, HandleRemoveIFRPack,
// HandleAddIFRPack, GetFormByFormID, HiiGetForm, GetDefaultValue,
// IFRChangeHandler, RegisterFormNotification, UnRegisterFormNotification
// and VarUpdateFormSetVariable
//
// 1     7/24/09 6:54p Presannar
//
// 2     4/14/09 12:39p Presannar
// Added Fn prototype FormCallBack, CallFormCallBack and
// SpecialActionCallBack
//
// 1     3/31/09 4:15p Madhans
//
// 2     1/29/09 6:09p Presannar
// Added Function Prototypes for GetControlConditionVariable and
// HiiRemoveString
//
// 1     1/09/09 2:38p Presannar
// UEFI 2.1 Hii Related Code - Initial Drop
//
// 30    9/17/08 7:44p Madhans
// For Boot only Driver file split changes.
//
// 29    3/19/08 5:39p Madhans
// Get Max line length of multiline string support for Message box
//
// 28    10/24/07 11:23a Arunkumars
// - Moved IDE security code to binary
// - Fixed build errors under UGA draw support
// - Added EFI key password support
// - Added modifier hot key support
// - Added popup support in From browser protocol
//
// 27    7/18/07 8:04a Arunkumars
// added hook for password encode and colour
//
// 26    7/09/07 1:27p Arunkumars
// - Added elink hooks for Logo, Password management and Control Keys
// customizations
//
// 25    5/22/07 9:21a Arunkumars
// Added support to dynamically parse forms that have been updated using
// UpdateForm; under SDL token for Run time Hii support
//
// 24    3/12/07 7:25p Arunkumars
// Added support to store EFI_KEYs for password.
//
// 23    8/14/06 12:38p Arunkumars
// Wide glyph support added
//
// 22    7/06/06 6:37p Arunkumars
// Include tiano.h instead of efi.h
//
// 21    6/15/06 9:34a Arunkumars
// Support to show new pages added at runtime
//
// 20    6/06/06 11:19a Madhans
// HII_VERSION Sdl Added. the token should be
// 0 - hii version older then aptio 3 version
// 1 - Aptio 3, 4 and 4.5 and Tiano 8
// 2 - tiano 8.5 and later
//
// 19    5/26/06 12:23p Madhans
// HiiGetLinkIndex modified to check for Class, subclass and guid though
// page variable.
//
// 18    10/04/05 11:29a Stefanor
// add string & language
// started fix for fixup data on mulitple reentry
// started dynamic IFR support
//
// 17    9/02/05 1:24p Jerryp
// Added skeleton for runtime IFR processing
//
// 16    8/10/05 5:10p Franklynd
// Fixing callback protocol issue.
//
// 15    8/10/05 4:01p Franklynd
// Fixes for ading and getting new strings from HII. using a specific
// language instead of all available languages.
//
// 14    8/05/05 4:47p Jerryp
// Added form browser callback when exploding a multiple variable
// Updated to version 1.12.1027
//
// 13    7/22/05 11:02a Jerryp
// Added code to OPTIONALLY use HII->GetDefaultImage instead of BCP
// compatible defaults
//
// 12    7/19/05 3:45p Jerryp
// Added function to change string for all languages or individual
// languages
//
// 11    5/19/05 10:29a Jerryp
// Added new HiiChangeString function
//
// 10    5/01/05 11:23a Jerryp
// Modifed HiiGetFormSet to accept a parameter
//
// 9     4/29/05 1:11p Franklynd
// Adding support for formcallback protocol to update nvram setup
// variables
//
// 8     2/07/05 2:32p Jerryp
// Removed HPK data
//
// 7     2/06/05 11:15a Jerryp
// Full hotkey support
//
// 6     2/04/05 10:30a Jerryp
// Added ability to get strings in ANY language
//
// 5     2/02/05 4:20p Jerryp
// **WORK IN PROGRESS **
// Latest changes for Label/Index.
// Not completely tested
//
// 4     1/31/05 2:32p Jerryp
// Added HiiGetStringLength function
//
// 3     1/14/05 7:09p Jerryp
// First integration code with boot to shell.
// Still a bug in booting to shell from FV
//
// 2     1/10/05 5:16p Jerryp
// Finished sync with HII
//
// 1     1/07/05 4:30p Jerryp
// Initial checkin
// useful debugging functions and HII header
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  			TseUefiHii.h
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
#ifndef _AMI_UEFI_HII_H_	// DO NOT CHANGE THIS TO _HII_H_ !!  That is used by the HII Protocol header
#define	_AMI_UEFI_HII_H_
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Minisetup.h"
#include "FormBrowser2.h"
#include EFI_PROTOCOL_DEFINITION(HiiDatabase)
#include EFI_PROTOCOL_DEFINITION(HiiFont)
#include EFI_PROTOCOL_DEFINITION(HiiString)
#include EFI_PROTOCOL_DEFINITION(HiiConfigRouting)
#include EFI_PROTOCOL_DEFINITION(HiiConfigAccess)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if TSE_USE_EDK_LIBRARY
#include "TianoHii.h"
#else
#include "UefiTianoHii.h"  // Internal file used then EDKsupport is OFF
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#define AMI_TIME_HOUR	1
#define AMI_TIME_MIN	2
#define AMI_TIME_SEC	3
#define AMI_DATE_YEAR	4
#define AMI_DATE_MONTH	5
#define AMI_DATE_DAY	6
//---------------------------------------------------------------------------
#define	TSE_REFRESH_GRANURALITY		5
//---------------------------------------------------------------------------
// Maximum supported page, variables, controls.
#define MAX_PAGE 246
#define MAX_CONTROLS 0xFFFE
#define MAX_VARIABLE 300

#ifndef _EFI_IFR_TYPE_BUFFER
#define EFI_IFR_TYPE_BUFFER            0x0B
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
extern EFI_HII_DATABASE_PROTOCOL *gHiiDatabase;
extern EFI_HII_FONT_PROTOCOL *gHiiFont;
extern EFI_HII_STRING_PROTOCOL *gHiiString;
extern EFI_HII_CONFIG_ROUTING_PROTOCOL *gHiiConfigRouting;

extern /*EFI_HII_HANDLE*/VOID* gHiiHandle;
extern UINTN	gTitle;
extern UINTN	gHelp;
extern UINTN	gSubTitle;
extern UINTN	gHelpTitle;
extern UINTN	gNavStrings;
extern BOOLEAN gIFRChangeNotify;
extern EFI_HII_HANDLE gRemovedHandle;
//---------------------------------------------------------------------------


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: EFI_HII_VALUE
//
// Description:
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Type					UINT8
// Value						EFI_IFR_TYPE_VALUE
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct _EFI_HII_VALUE
{
  UINT8               Type;
  EFI_IFR_TYPE_VALUE  Value;
}EFI_HII_VALUE;


//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name: SETUP_LINK
//
// Description:
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// FormSet					UINT8*
// Handle					VOID*
// ClassID					UINT16
// FormSetLength			UINTN
// Added					UINT8
// SubClassID				UINT16
// ClassGuidCount			UINT16
// ClassGuid				EFI_GUID*
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
typedef struct
{
  UINT8*		FormSet;
  VOID*			Handle;
  UINT16		ClassID;
  UINTN			FormSetLength;
  UINT8			Added;	//To know if this page was present in the tool data
  UINT16		SubClassID;
  UINT16    	ClassGuidCount;
  EFI_GUID*		ClassGuid;
}SETUP_LINK;

//EIP111061
typedef struct AMI_EFI_IFR_VARSTORE_EFI {
  EFI_IFR_OP_HEADER        Header;
  EFI_VARSTORE_ID          VarStoreId;
  EFI_GUID                 Guid;
  UINT32                   Attributes;
  UINT16                   Size;
  UINT8                    Name[1];
} AMI_EFI_IFR_VARSTORE_EFI; //as per UEFI spec 2.3.1

//---------------------------------------------------------------------------
EFI_IFR_FORM_SET *HiiGetFormSetFromHandle( /*EFI_HII_HANDLE*/VOID* handle );
EFI_IFR_FORM_SET *HiiGetFormSet( UINTN index );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
extern VOID RTIfrProcessAddVarListAndPageIDListWrapper(VOID);
extern VOID RTIfrProcessExitWrapper(VOID);
extern VOID RTIfrProcessRunTimeFormsWrapper(EFI_IFR_REF **ref);
extern BOOLEAN RTIfrUpdateVariableInfoWrapper(UINT32 ControlVariable, EFI_HANDLE Handle);
extern BOOLEAN RTIfrProcessFormIfUpdatedWrapper(UINT16 link);
extern INTN EfiStrnCmp(IN CHAR16 *String, IN CHAR16 *String2, IN UINTN Length);
extern EFI_STATUS GetHexStringAsBuffer(UINT8 **Buffer, CHAR16 *HexStringBuffer);
extern EFI_STATUS BufferToHexString(IN OUT CHAR16 *Str, IN UINT8 *Buffer, IN UINTN BufferSize);
extern EFI_STATUS UnicodeToConfigString(IN OUT CHAR16 *ConfigString, IN OUT UINTN *StrBufferLen, IN CHAR16 *UnicodeString);
//---------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Hii.c
// ----------------------------------------------------------------------------
EFI_STATUS HiiExit(VOID);
EFI_STATUS HiiFixupData();
EFI_STATUS HiiLoadDefaults( VOID **varList, UINT32 Mask );
EFI_STATUS FixSetupData();
EFI_STATUS HandleNewIFRPack(EFI_HANDLE Handle, UINT8 *PackData); 	//EIP 75588
EFI_STATUS HandleRemoveIFRPack(EFI_HANDLE Handle);
EFI_STATUS HandleAddIFRPack(EFI_HANDLE Handle, UINT8 *PackData);
VOID* HiiFindHandle( EFI_GUID *guid, UINT16 *index );
UINT16 HiiChangeString(VOID* handle, UINT16 token, CHAR16 *string);

VOID *GetFormByFormID(EFI_HII_PACKAGE_HEADER *IFRData, UINT16 FormID, UINTN *Length);
VOID *HiiGetForm( EFI_HII_HANDLE Handle, UINT16 form, UINTN *Length );

PAGE_ID_INFO *GetPageIdInfoByIndex(PAGE_ID_INFO *PageIdInfo, UINT16 PgIndex);
//EIP:56413 Function to update the Resetbutton Defaults to the control
EFI_STATUS UefiupdateResetButtonDefault(CONTROL_INFO ControlData, UINT16 DefaultId);
 //EIP: 57402 Evaluating the Control Default
UINT16 EvaluateControlDefault(CONTROL_INFO *CtrlInfo, UINT64 *Defaults);

// ----------------------------------------------------------------------------
// Uefi21Wrapper.c
// ----------------------------------------------------------------------------
EFI_STATUS GetConfigHeader(VARIABLE_INFO *VariableInfo, EFI_STRING *Configuration, UINTN *Length);
EFI_STATUS ProcessActionQuestionConfiguration(CONTROL_INFO *control);
EFI_STATUS UefiGetOneOfOptions(CONTROL_INFO *CtrlInfo, VOID **Handle, UINT16 **OptionPtrTokens,
                               UINT64 **ValuePtrTokens, UINT16 *ItemCount,
                               UINT16 *Interactive, UINT16 *CallBackKey);
VOID UefiGetValidOptionType(CONTROL_INFO *CtrlInfo, UINTN *Type, UINT32 *SizeOfData);
EFI_STATUS UefiVarGetNvram(VARIABLE_INFO *VariableInfo, VOID **Buffer, UINTN Offset, UINTN Size);
EFI_STATUS UefiVarSetNvram(VARIABLE_INFO *VariableInfo, VOID *Buffer, UINTN Offset, UINTN Size);

BOOLEAN IsPasswordEncodeEnabled(VOID *PwDataPtr);
BOOLEAN UefiIsEfiVariable(UINT32 variable, VARIABLE_INFO *varInfo);
BOOLEAN UefiIsInteractive(CONTROL_INFO *ControlData);

UINT8 UefiGetBaseValue(VOID *IfrPtr);
UINT8 UefiGetIfrLength(VOID *IfrPtr);
UINT8 UefiGetMaxEntries(VOID *IfrPtr);

UINT16 UefiGetControlKey(CONTROL_INFO *ControlData);
UINT16 UefiGetHelpField(VOID *IfrPtr);
UINT16 UefiGetPromptField(VOID *IfrPtr);
UINT16 UefiGetQuestionOffset(VOID *IfrPtr);
UINT16 UefiGetTextField(VOID *IfrPtr);
UINT16 UefiGetTextTwoField(VOID *IfrPtr);
UINT16 UefiGetTitleField(VOID *IfrPtr);
UINT16 UefiGetWidth(VOID *IfrPtr);
UINT8 UefiGetFlagsField(VOID *IfrPtr);

UINT16 UefiTseLiteGetAmiCallbackIndex(VOID * Ptr,VOID * CtrlPtr);
UINT16 UefiTseLiteGetBootOverRideIndex(VOID *IfrPtr);

UINTN HiiGetDefaultMask(VOID);
UINTN HiiGetManufactuingMask(VOID);
UINTN HiiMyGetMultiLineStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token );
UINTN HiiMyGetStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token );

UINT64 UefiGetMaxValue(VOID *IfrPtr);
UINT64 UefiGetMinValue(VOID *IfrPtr);
UINT64 UefiGetStepValue(VOID *IfrPtr);

VOID EfiLibSafeFreePool(IN VOID *Buffer);
VOID HiiRemoveString(EFI_HII_HANDLE Handle, UINT16 Token);
VOID UefiGetDateTimeDetails(VOID *IfrPtr,UINT8 Type,UINT16 * Help,UINT16 * Min,UINT16 * Max);
VOID UefiSetPromptField(VOID *IfrPtr,UINT16 Token);
VOID UefiSetHelpField(VOID *IfrPtr,UINT16 Token);
VOID UefiSetSubTitleField(VOID *IfrPtr,UINT16 Token);

VOID *UefiCreateSubTitleTemplate(UINT16 Token);
VOID *UefiCreateStringTemplate(UINT16 Token);
EFI_STATUS UefiRefershQuestionValueNvRAM(CONTROL_INFO *ControlData);
UINT16 UefiGetResetButtonDefaultid(VOID *IfrPtr);//EIP:56413 Function decleration to get the Default ID
BOOLEAN CheckTimeFlags(UINT8 Flags);
BOOLEAN CheckDateFlags(UINT8 Flags);

// ----------------------------------------------------------------------------
// TSE Advanced
// ----------------------------------------------------------------------------
VOID UefiAddEndOp(VOID *IfrPtr);
VOID BBSUpdateControlOffset(CONTROL_INFO *control);
VOID UefiCreateDynamicControlCondition(CONTROL_INFO *control,UINT16 VarId, UINT16 PrevControlQuestionID,UINT16 Value);
VOID UefiSetEqIDValue(VOID *IfrPtr, UINT16 Value);
VOID UefiSetEqIDQuestionID(VOID *IfrPtr, UINT16 Value);
VOID UefiSetOneOfOption(VOID *IfrPtr, UINT64 Value, UINT32 Size, UINT8 Flag, UINT16 Option);
VOID UefiSetWidth(VOID *IfrPtr,UINT8 Width);
VOID UefiSpecialGuidCallback(VOID * HiiHandle, UINT16 Key, EFI_GUID *pGUID);
VOID UefiUpdateControlVarOffset(VOID *IfrPtr, UINT16 Value);

VOID* UefiCreateOneOfWithOptionsTemplate(UINTN OptionCount, CONTROL_INFO *CtrlInfo);
VOID* UefiGetSpecialEqIDIfrPtr(CONTROL_INFO *ControlInfo, UINT32 * Variable, GUID_INFO **GuidInfo);

BOOLEAN UefiIsOneOfControl(VOID *IfrPtr);

UINT16 UefiGetEqIDQuestionID(VOID *IfrPtr);
UINT16 UefiGetQuestionID(CONTROL_INFO *Control);
UINT16 UefiGetSpecialEqIDValue(CONTROL_INFO *ControlInfo, GUID_INFO **GuidInfo);

UINT32 GetControlConditionVarId(CONTROL_INFO *controlInfo);
UINTN GetControlDataLength(CONTROL_INFO *controlInfo);

// ----------------------------------------------------------------------------
// Expression.c
// ----------------------------------------------------------------------------
EFI_STATUS EvaluateExpression(IN CONTROL_INFO *ControlInfo,
			      IN OUT EFI_HII_VALUE *ExpressionResult,
			      OUT UINTN *Offset);
VOID ResetScopeStack(VOID);
EFI_STATUS PushScope(IN UINT8 Operand);
EFI_STATUS PopScope(OUT UINT8 *Operand);
BOOLEAN IsScopeStackEmpty();
UINTN _SkipExpression(UINT8 *ControlCondPtr);
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Parse.c
// ----------------------------------------------------------------------------
EFI_STATUS AddPageIdToList(PAGE_ID_INFO *NewPageIdInfo);
EFI_STATUS AddPageToList(PAGE_INFO *NewPageInfo, UINT32 PageSize);
EFI_STATUS AddVariableToList(VARIABLE_INFO *NewVariableInfo);
EFI_STATUS CreatePage(PAGE_INFO **PageInfo, UINT32 *AllocatedSize, UINT32 *Offset, VOID *Buff, UINT32 BuffSize);
EFI_STATUS ParseForm(SETUP_LINK *Setup_Link);
UINT32 AddControlToList(CONTROL_INFO *ControlInfo, UINT32 ControlSize);
VOID GetDefaultValue(UINT8 Type, EFI_IFR_TYPE_VALUE *Value, UINT16 *Size, VOID *DefValue, UINT8 *TempData);
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// HiiCallBack.c
// ----------------------------------------------------------------------------
#if TSE_DEBUG_MESSAGES
#define SETUPDATAFILENAME 	L"SETUPDATA_0x%x_%03d.hpk" 
EFI_STATUS WritePackToFile(CHAR16 *filenameFormat, EFI_HANDLE Handle, UINT8 *PackData, UINTN length);
EFI_STATUS WriteDataToFile(CHAR16 *filename, VOID *Data, UINTN length, UINT32 index);
VOID *HiiGetPackList( EFI_HII_HANDLE Handle, UINT16 form, UINTN *Length );
VOID ProcessPackToFile(EFI_HII_DATABASE_NOTIFY_TYPE NotifyType, EFI_HANDLE Handle);
VOID DebugShowBufferContent(UINTN bufSize, VOID *buffer) ;
#endif //End of TSE_DEBUG_MESSAGES
EFI_STATUS FormCallBack(EFI_HII_HANDLE Handle, EFI_QUESTION_ID QuestionID, UINT8 Type, EFI_IFR_TYPE_VALUE *Value,EFI_BROWSER_ACTION action);
EFI_STATUS CallFormCallBack(CONTROL_INFO * ControlData, UINT16 Key ,UINT8 Flags,UINTN Action);//EIP-53480: Implementation of FormBrowser with actions support 
EFI_STATUS SpecialActionCallBack(CONTROL_INFO * ControlData, UINT16 Key);
EFI_STATUS CallTextCallBack(TEXT_DATA *text, ACTION_DATA *Data);
VOID UefiPreControlUpdate(CONTROL_INFO *ControlData);
EFI_STATUS UefiIsProceedWithPageChange(EFI_STATUS Status);
VOID UEFICallSetupFormCallBack(UINTN Action );//EIP-53480: Decleration of the Wrapper function which calls the CallFormCallBack()
EFI_BROWSER_ACTION UefiGetActionWapper(UINTN Action);//EIP-53480  The Wrapper function to get the actual action for the driver 
// ----------------------------------------------------------------------------

//HiiNotificationHandler.c
// ----------------------------------------------------------------------------
EFI_STATUS
IFRChangeNotifyFn (IN UINT8 PackageType, IN CONST EFI_GUID *PackageGuid,
  IN CONST EFI_HII_PACKAGE_HEADER *Package, IN EFI_HII_HANDLE Handle,
  IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType);
EFI_STATUS RegisterFormNotification(EFI_HII_DATABASE_NOTIFY PackageNotifyFn,
                                    EFI_HII_DATABASE_NOTIFY_TYPE NotifyType,
                                    EFI_HANDLE *NotifyHandle);
EFI_STATUS UnRegisterFormNotification(EFI_HANDLE NotifyHandle);
VOID VarUpdateFormSetVariable();
EFI_STATUS _DisplayErrorMessage(); // EIP : 52562 To display Error message when TSE limits exceeds
// ----------------------------------------------------------------------------

#define AMI_FLAG_MANUFACTURING	EFI_IFR_OPTION_DEFAULT_MFG
#define AMI_FLAG_DEFAULT	EFI_IFR_OPTION_DEFAULT
EFI_STATUS GetBlockName(EFI_STRING *Configuration, UINTN *Length, UINTN Offset, UINTN Size);

// ----------------------------------------------------------------------------
// To Be removed
#define EfiCopyMem(_Destination, _Source, _Length)  gBS->CopyMem ((_Destination), (_Source), (_Length))
#define EfiZeroMem(_Destination, _Length)  gBS->SetMem ((_Destination), (_Length), 0)

//EIP:56124 Defining the Default value linked list 
typedef struct _DEFAULT_VALUE
{
	UINT16 DefaultId;
	UINT64 Value;
	struct _DEFAULT_VALUE *Next;
}DEFAULT_VALUE;
//EIP:56124 END

//Added for UEFI spec. 2.3 compatibility- Start   
#ifndef EFI_BROWSER_ACTION_RETRIEVE
#define EFI_BROWSER_ACTION_RETRIEVE   2
#endif
#ifndef EFI_BROWSER_ACTION_FORM_OPEN
#define EFI_BROWSER_ACTION_FORM_OPEN  3
#endif
#ifndef EFI_BROWSER_ACTION_FORM_CLOSE
#define EFI_BROWSER_ACTION_FORM_CLOSE 4
#endif

#pragma pack (1)
typedef struct _AMI_EFI_IFR_REFRESH_ID {
  EFI_IFR_OP_HEADER Header;
  EFI_GUID          RefreshEventGroupId;
} AMI_EFI_IFR_REFRESH_ID;

#ifndef EFI_IFR_EQ_ID_LIST_OP
#define EFI_IFR_EQ_ID_LIST_OP      0x14
#endif 

#ifndef EFI_IFR_ANIMATION_OP
#define EFI_IFR_ANIMATION_OP           0x1F
#endif

#ifndef EFI_IFR_MAP_OP
#define EFI_IFR_MAP_OP                 0x22
#endif

#ifndef EFI_IFR_GET_OP
#define EFI_IFR_GET_OP                 0x2B
#endif

#ifndef EFI_IFR_SET_OP
#define EFI_IFR_SET_OP                 0x2C
#endif

#ifndef EFI_IFR_READ_OP
#define EFI_IFR_READ_OP                0x2D
#endif

#ifndef EFI_IFR_WRITE_OP
#define EFI_IFR_WRITE_OP               0x2E
#endif

#ifndef EFI_IFR_FORM_MAP_OP
#define EFI_IFR_FORM_MAP_OP            0x5D
#endif

#ifndef EFI_IFR_MODAL_TAG_OP
#define EFI_IFR_MODAL_TAG_OP           0x61
#endif

#ifndef EFI_IFR_REFRESH_ID_OP
#define EFI_IFR_REFRESH_ID_OP          0x62
#endif

#ifndef EFI_IFR_TYPE_UNDEFINED
#define EFI_IFR_TYPE_UNDEFINED         0x09
#endif

#ifndef EFI_IFR_TYPE_ACTION
#define EFI_IFR_TYPE_ACTION            0x0A
#endif

#ifndef EFI_IFR_TYPE_REF
#define EFI_IFR_TYPE_REF               0x0C
#endif

typedef struct _AMI_EFI_IFR_FORM_MAP_METHOD {
  ///
  /// The string identifier which provides the human-readable name of 
  /// the configuration method for this standards map form.
  ///
  EFI_STRING_ID            MethodTitle;
  ///
  /// Identifier which uniquely specifies the configuration methods 
  /// associated with this standards map form.
  ///
  EFI_GUID                 MethodIdentifier;
} AMI_EFI_IFR_FORM_MAP_METHOD;

typedef struct _AMI_EFI_IFR_FORM_MAP {
  ///
  /// The sequence that defines the type of opcode as well as the length 
  /// of the opcode being defined. Header.OpCode = EFI_IFR_FORM_MAP_OP. 
  ///
  EFI_IFR_OP_HEADER        Header;
  ///
  /// The unique identifier for this particular form.
  ///
  EFI_FORM_ID              FormId;
  ///
  /// One or more configuration method's name and unique identifier.
  ///
  // EFI_IFR_FORM_MAP_METHOD  Methods[];
} AMI_EFI_IFR_FORM_MAP;

typedef struct _AMI_EFI_IFR_SET {
  ///
  /// The sequence that defines the type of opcode as well as the length 
  /// of the opcode being defined. Header.OpCode = EFI_IFR_SET_OP. 
  ///
  EFI_IFR_OP_HEADER  Header;
  ///
  /// Specifies the identifier of a previously declared variable store to 
  /// use when storing the question's value. 
  ///
  EFI_VARSTORE_ID    VarStoreId;
  union {
    ///
    /// A 16-bit Buffer Storage offset.
    ///
    EFI_STRING_ID    VarName;
    ///
    /// A Name Value or EFI Variable name (VarName).
    ///
    UINT16           VarOffset;
  }                  VarStoreInfo;
  ///
  /// Specifies the type used for storage. 
  ///
  UINT8              VarStoreType;
} AMI_EFI_IFR_SET;

typedef struct _AMI_EFI_IFR_GET {
  ///
  /// The sequence that defines the type of opcode as well as the length 
  /// of the opcode being defined. Header.OpCode = EFI_IFR_GET_OP. 
  ///
  EFI_IFR_OP_HEADER  Header;
  ///
  /// Specifies the identifier of a previously declared variable store to 
  /// use when retrieving the value. 
  ///
  EFI_VARSTORE_ID    VarStoreId;
  union {
    ///
    /// A 16-bit Buffer Storage offset.
    ///
    EFI_STRING_ID    VarName;
    ///
    /// A Name Value or EFI Variable name (VarName).
    ///
    UINT16           VarOffset;
  }                  VarStoreInfo;
  ///
  /// Specifies the type used for storage. 
  ///
  UINT8              VarStoreType;
} AMI_EFI_IFR_GET;

//EIP109812, 107774
typedef struct _AMI_EFI_HII_REF {
    EFI_QUESTION_ID QuestionId;
    EFI_FORM_ID     FormId;
    EFI_GUID        FormSetGuid;
    EFI_STRING_ID   DevicePath;
} AMI_EFI_HII_REF;

typedef struct _AMI_EFI_IFR_REF5 {
	EFI_IFR_OP_HEADER 			Header;
	EFI_IFR_QUESTION_HEADER 	Question;
} AMI_EFI_IFR_REF5;

/////////////////////////////////////////////////////////////////////////////////
//
//Declaring the struct which are not present in core (UefiHii.h)
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _TSE_EFI_IFR_FORM_SET
#define _TSE_EFI_IFR_FORM_SET
typedef struct _TSE_EFI_IFR_FORM_SET {
  EFI_IFR_OP_HEADER        Header;
  EFI_GUID                 Guid;
  EFI_STRING_ID            FormSetTitle;
  EFI_STRING_ID            Help;
  UINT8                    Flags;
  EFI_GUID                 ClassGuid[1];
} TSE_EFI_IFR_FORM_SET;
#endif
#pragma pack ()

//End for UEFI spec. 2.3 compatibility
#endif /* _AMI_UEFI_HII_H_ */
// ----------------------------------------------------------------------------
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