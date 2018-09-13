//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/minisetupext.h $
//
// $Author: Premkumara $
//
// $Revision: 30 $
//
// $Date: 8/28/14 3:07p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/minisetupext.h $
// 
// 30    8/28/14 3:07p Premkumara
// [TAG]	EIP141986
// [Category]	Improvement
// [Description]	Make grayedout control focusable and this feature is
// handled by token TSE_SETUP_GRAYOUT_SELECTABLE
// [Files]	AMITSE.sdl, CommonHelper.c, Frame.c, Label.c, Minisetupext.c,
// Numeric.c, PopupPassword.c, PopupSel.c, PopupString. SubMenu.c
// 
// 29    8/28/14 6:06a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 28    5/02/14 9:28p Arunsb
// EIP141986 changes reverted.
// 
// 27    5/02/14 10:59a Premkumara
// [TAG]  		EIP141986
// [Category]  	New Feature
// [Description]  	Made Grayed controls to focus-able when token
// TSE_SETUP_GRAYOUT_SELECTABLE
//  is enabled and can't edit the values
// [Files]  		AMITSE.sdl,CommonHelper.c,frame.c,Label.c,minisetupext.h,
// numeric.c,PopupPassword.c,PopupSel.c,PopupString.c,SubMenu.c
// 
// 26    2/11/14 8:23p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 24    3/12/13 7:02a Rajashakerg
// [TAG]  		EIP105167 
// [Category]  	Improvement
// [Description]  	Making the specify setup items departing from F2/F3
// effect.
// [Files]  		AMITSE.sdl, CommonHelper.c, callback.c, minisetupext.h,
// PopupPassword.c, SubMenu.c, HiiCallback.c
// 
// 23    10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 14    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 22    5/28/12 12:32p Premkumara
// [TAG]  		EIP67049 & 90224
// [Category]  	New Feature
// [Description]  	Support mouse drag operation in frame and list box
// [Files]  		CommonHelper.c, Frame.c, ListBox.c, Minisetupext.h
// 
// 21    5/28/12 11:45a Premkumara
// [TAG]  		EIP89272
// [Category]  	Improvement
// [Description]  	Change softkbd layout for numeric control
// [Files]  		CommonHelper.c, Mouse.c, Minisetup.h, C, Numeric.c
// 
// 20    4/05/12 7:16a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 19    1/24/12 4:40a Arunsb
// [TAG]  		EIP81581
// [Category]  	Improvement
// [Description]  	Default driver order support
// [Files]  		globals.c, addbootoption.c, callback.c, minisetupext.h and
// variable.c
// 
// 18    11/20/11 7:55a Rajashakerg
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
// 17    11/14/11 6:55p Blaines
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
// 16    11/13/11 1:00p Arunsb
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
// 15    10/20/11 12:25p Blaines
// Correct the comments.
// 
// 14    10/20/11 11:48a Blaines
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
// 13    6/23/11 3:55p Rajashakerg
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
// 12    3/28/11 9:24p Madhans
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
// 11    3/28/11 4:58p Rajashakerg
// [TAG]  		EIP56413 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_RESET_BUTTON opcode
// [Files]  		ezport.c, minisetupext.h, ResetButton.c, ResetButton.h,
// Hii.c, TseUefiHii.h, Uefi21Wapper.c, hii.h, Uefi20Wapper.c 
// 
// 10    3/21/11 12:36a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 9     3/09/11 7:23p Madhans
// [TAG]  		EIP48615  
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
// 8     2/10/11 12:32p Blaines
// [TAG] - EIP 53146
// [Category]- New Feature
// [Description] -Add the support to Move the Dynamic IFR Pages under
// subpages. It should be customizable to move around.
// 
// 7     1/06/11 7:44p Madhans
// [TAG] - EIP 51678 
// [Category]- Enhancment
// [Severity]- Mordarate
// [Symptom]-  If OEMs override the style module parts, If new tse adds
// new style hook then 
// if the OEM has different style module, even if they don't need use the
// hook to avoid 
// compilation issue they need touch their style module to add the new
// hook.
// [RootCause] - The Original Style Hooks are part of Style module itself.
// [Solution]- To create Empty style Hook List in TSE core. This will
// allows the OEM not 
// to change their style module to update newer TSE.
// [Files] - StyleHook Module Part under TSE lite sources. StyleHook.lib
// StyleHookx64.lib tselitebin.sdl
// 
// 6     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 10    2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 9     2/15/10 10:14p Madhans
// Uefi 2.1 support
// 
// 8     1/09/10 6:23a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 7     10/28/09 5:38p Madhans
// 
// 6     9/15/09 9:46a Sudhirv
// added new definition VARIABLE_ID_OEM_TSE_VAR
// 
// 5     8/20/09 6:43p Madhans
// Fix for Mouse click crash issue.
// 
// 4     8/19/09 12:58p Madhans
// IsToggleStateKey() function added
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:05p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 5     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     3/31/09 4:11p Madhans
// 
// 3     2/05/09 10:15a Madhans
// Style Module created.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		MINISETUPEXT.h
//
// Description:	Header file for FULL TSE specific minisetup entery and exit	funtionallies
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _MINISETUPEXT_H_
#define	_MINISETUPEXT_H_


#define	MINI_SETUP_HPK_DATA_GUID	\
	{ 0xDCFBBCA4, 0x2498, 0x48DB, 0x91, 0x22, 0xFF, 0x7E, 0x96, 0x4B, 0xC5, 0x69 }
//EIP:53480 Defining the Action requests for the callbacks
#define AMI_CALLBACK_CONTROL_UPDATE 1
#define AMI_CALLBACK_RETRIEVE 2
#define AMI_CALLBACK_FORM_OPEN 3
#define AMI_CALLBACK_FORM_CLOSE 4
#define AMI_CALLBACK_FORM_DEFAULT_STANDARD 		0x1000 //EIP 105167 : Making the specify setup items departing from F2/F3 effect.
#define AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING 0x1001

#include "setupdata.h"
#if EFI_SPECIFICATION_VERSION <= 0x20000
#include "hii.h"
#else
#include "TseUefiHii.h"
#endif /* #if EFI_SPECIFICATION_VERSION <= 0x20000 */
#include "StyleHook\StyleHook.h"
#if TSE_STYLE_SOURCES_SUPPORT
#include "style.h"
#endif
#include "application.h"
#include "action.h"
#include "MessageBox.h" 
#include "hotkey.h"
#include "Date.h" 
#include "Text.h" 
#include "edit.h"
#include "Label.h" 
#include "ListBox.h" 
#include "Memo.h" 
#include "Menu.h"  //
#include "numeric.h"
#include "popup.h"
#include "PopupEdit.h"
#include "PopupPassword.h"
#include "PopupSel.h"
#include "PopupString.h"
#include "SubMenu.h"
#include "Time.h"
#include "password.h"
#include "ordlistbox.h"
#include "UefiAction.h"
#include "ResetButton.h"//EIP:56413 Added reset button header file

/*
#include "special.h"
*/

extern SETUP_PKG					*gSetupPkg;
extern SCREEN_INFO					*gScreen;
extern PAGE_LIST					*gPages;
extern PAGE_LIST					*gToolPages;
extern CONTROL_INFO					*gToolControlInfo;
extern CONTROL_INFO					*gControlInfo;
extern VARIABLE_LIST				*gToolVariables;
extern VARIABLE_LIST				*gVariables;
extern PAGE_ID_LIST					*gPageIdList;
extern PAGE_ID_LIST					*gToolPageIdList;
extern PAGE_ID_INFO					*gPageIdInfo;
extern PAGE_ID_INFO					*gToolPageIdInfo;

extern NVRAM_VARIABLE				*gVariableList;
extern NVRAM_VARIABLE				*gFailsafeDefaults;
extern NVRAM_VARIABLE				*gOptimalDefaults;

extern HPK_INFO						*gHpkInfo;

extern GUID_LIST					*gGuidList;

extern FRAME_DATA					*gActiveFrame;

extern ACTION_DATA                  *gMsgBoxAction;
extern UINT16 gDynamicParentPage;
// callback.c
VOID LoadPreviousValues( BOOLEAN showMsgBox );
VOID LoadOptimalDefaults( VOID );
VOID LoadFailsafeDefaults( VOID );
BOOLEAN SaveAndExit( VOID );
VOID SaveWithoutExit( VOID );
BOOLEAN SaveAndReset( VOID );
BOOLEAN ResetSys( VOID );
BOOLEAN ExitApplication( VOID );
VOID ShowHelpMessageBox( VOID );
UINT8 CallbackShowMessageBox( UINTN data, UINT8 type );
EFI_STATUS CallFormCallBack(CONTROL_INFO * pControlData, UINT16 Key, UINT8 Flags, UINTN Action);
VOID UEFICallSetupFormCallBack(UINTN Action );

// Helper
extern CHAR8						*gPrevLanguage;
extern UINTN						gPrevLangSize;

VARIABLE_INFO *VarGetVariableInfoIndex( UINT32 index );
VARIABLE_INFO *VarGetVariableInfoId( UINT32 varId, UINT32 *index );
// variable.h
extern UINTN gSetupCount;
VOID *BBSReOrderDefultLegacyDevOrder(BBS_ORDER_TABLE *DefaultLegDevOrder,UINTN DefaultLegDevOrderSize);
extern EFI_GUID EfiDefaultLegacyDevOrderGuid;
extern EFI_GUID EfiDefaultBootOrderGuid;
extern EFI_GUID EfiDefaultDriverOrderGuid;		//EIP81581
//#define SETUP_PASSWORD_LENGTH	20
extern const UINTN TsePasswordLength;
VOID InitgProgress( VOID );
VOID SetHDDPassword(VOID);
VOID BBSUpdateOrder(UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer);
VOID BootUpdateOrder (UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer);
VOID DriverUpdateOrder (UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer);	//EIP70421 & 70422 Support for driver order

extern VOID MainSetupLoopInit(VOID) ;
EFI_STATUS DoBbsPopupInit(VOID) ;
EFI_STATUS DrawBbsPopupMenu( VOID );
VOID DrawBootOnlyBbsPopupMenu( VOID ) ;
VOID BbsBoot(VOID) ;

EFI_STATUS VarBuildAMIDefaults(VOID);

// Mouse Functions
VOID NumericSoftKbdExit(VOID);
VOID NumericSoftKbdInit(VOID);
VOID PrintableKeysSoftKbdInit(VOID);
VOID PrintableKeysSoftKbdExit(VOID);
VOID MouseInit(VOID);
VOID MouseStop(VOID);
VOID MouseFreeze(VOID);
VOID MouseRefresh(VOID);
BOOLEAN IsMouseClickedonSoftkbd(VOID);
VOID MouseStart(VOID);
VOID MouseDestroy(VOID);
EFI_STATUS MouseReadInfo(VOID *MouseInfo);
EFI_STATUS MouseScrollBarMove(VOID *frame, BOOLEAN bScrollUp, UINT32 Size); //EIP-67049
EFI_STATUS MouseListBoxScrollBarMove(VOID *listbox, BOOLEAN bScrollUp, UINT32 Size); //EIP-67049
EFI_STATUS MouseFrameHandleAction( VOID *frame, VOID *action, VOID *control );
EFI_STATUS MouseSubMenuHandleAction( VOID *submenu, VOID *Data);
EFI_STATUS MouseMsgBoxHandleAction( VOID *msgbox, VOID *Data,BOOLEAN * pRedraw );
EFI_STATUS MouseListBoxHandleAction( VOID *listbox, VOID *Data);
EFI_STATUS MousePopupSelHandleAction( VOID *popupSel, VOID *Data);
EFI_STATUS MousePopupEditHandleAction( VOID *PopupEdit, VOID *Data,BOOLEAN * pRedraw );
EFI_STATUS MouseMenuHandleAction( VOID *menu, VOID *Data );


VOID ReGroupOptions(UINT16 *optionList,UINT16 *OrgOptionList);
EFI_STATUS PopupEditHandlePassword( VOID *PopupEdit, VOID *Data);
EFI_STATUS ActionReadKey( AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout );
EFI_STATUS AMIReadKeyStroke(EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData);
EFI_STATUS HelperIsPasswordCharValid(EFI_INPUT_KEY *Key,AMI_EFI_KEY_DATA *KeyData,UINTN StrIndex,UINTN PasswordLength, CHAR16 *OutChar);
VOID FramePasswordAdvancedCallback(CALLBACK_PASSWORD *callbackData,CHAR16 *saveData);
EFI_STATUS FramePwdCallbackIdePasswordUpdate ( CONTROL_DATA *control,CHAR16 *saveData);
EFI_STATUS PopupPwdAuthenticateIDEPwd(POPUP_PASSWORD_DATA *popuppassword, BOOLEAN *AbortUpdate,VOID *data);
VOID PopupPwdUpdateIDEPwd (VOID);
EFI_STATUS 	PopupPwdHandleActionOverRide(POPUP_PASSWORD_DATA *popuppassword, ACTION_DATA *Data);
UINT32 PopupPasswordCheckInstalled(POPUP_PASSWORD_DATA *popuppassword);
BOOLEAN PopupPasswordAuthenticate( POPUP_PASSWORD_DATA *popuppassword, CHAR16 *Password );
EFI_STATUS FormBrowserLocateSetupHandles(/*EFI_HII_HANDLE*/VOID*	**handleBuffer,UINT16 *count);
BOOLEAN FormBrowserHandleValid(VOID);
VOID GetAMITSEVariable(AMITSESETUP **mSysConf,UINT8 **setup,UINTN *VarSize);
VOID NoVarStoreUpdateSystemAccess(UINT8 sysAccessValue);
VOID SetSystemAccessValueItk(UINT8 sysAccessValue);
VOID VarBuildItkDefaults(VOID);
VOID SpecialUpdatePageControls(UINT32 CurrentPage);
EFI_STATUS PopupPasswordFormCallback(CONTROL_INFO * pControlData,UINT16 Key,UINT8 Flags);
BOOLEAN CheckSystemPasswordPolicy(UINT32 PasswordInstalled);

extern UINTN                        gHpkInfoLength;
BOOLEAN IsReadOnlyGrayout();
BOOLEAN IsGrayoutSelectable();
BOOLEAN IsGroupDynamicPages();
BOOLEAN IsOrphanPagesAsRootPage();
BOOLEAN IsLinkHistorySupport();
BOOLEAN IsSubMenuDisplayTitle();

VOID CsmSaveBBSOrder( VOID *);
VOID CsmBBSSetDisabled(UINT16 Index, VOID **DisDPs, UINTN *DPSize);
VOID CsmRearrangeBBSOrderVariable(VOID *popupSel, UINT8 bIncrease,UINT16 *newOption);
VOID CsmLoadDefaultLegDevOrder(VOID);
EFI_STATUS CsmBBSUpdateOrder(UINT16 *newOption,UINT32 *offset,UINTN *size, VOID **buffer);

BOOLEAN TseLiteIsSpecialOptionList(CONTROL_DATA *);


///IDE Password Hooks
UINT16 TSEIDEPasswordGetName(UINT16 Index);
EFI_STATUS TSEIDEPasswordAuthenticate(CHAR16 *Password,  VOID*  DataPtr, BOOLEAN bCheckUser);
BOOLEAN TSEIDEPasswordUpdate( UINT32 DeviceIndex, CHAR16 *Password, BOOLEAN bCheckUser);
VOID* TSEIDEPasswordGetDataPtr( UINTN Index);
BOOLEAN TSEIDEPasswordGetLocked(UINTN Index);
VOID TSEIDEPasswordCheck();
VOID TSEIDEPasswordFreezeDevices();
VOID TSEUnlockHDD(VOID);
VOID TSESetHDDPassword(VOID);
VOID TSEIDEUpdateConfig(VOID *ideSecConfig, UINTN value);


UINTN TseGetANSIEscapeCode(CHAR16 *String,UINT8 *Bold,UINT8 *Foreground, UINT8 *Background);
CHAR16 *TseSkipEscCode(CHAR16 *String);

BOOLEAN TseCheckShiftState(AMI_EFI_KEY_DATA ActionKey, UINT32 HotkeyState);

UINT32 _GetControlVariable(CONTROL_INFO *control);

VOID TseHotkeyPrintScreenSupport();
BOOLEAN TsePrintScreenEventSupport(UINT16 ScanCode);
BOOLEAN IsToggleStateKey(ACTION_DATA *Data);
BOOLEAN IsActiveControlPresent(PAGE_DATA *page);
VOID TSEStringReadLoopEntryHook(VOID);
VOID TSEStringReadLoopExitHook(VOID);
BOOLEAN TSEMouseIgnoreMouseActionHook(VOID);
VOID TSENumericSoftKbdExit(VOID);
VOID TSENumericSoftKbdInit(VOID);
#endif /* _MINISETUP_H_ */


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
