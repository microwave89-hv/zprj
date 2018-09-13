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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/hii.h $
//
// $Author: Arunsb $
//
// $Revision: 18 $
//
// $Date: 4/18/13 9:33a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/hii.h $
// 
// 18    4/18/13 9:33a Arunsb
// Function declarations added to avoid build error in 2.0
// 
// 17    3/25/13 8:34a Premkumara
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
// 16    10/18/12 6:00a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 16    10/10/12 12:39p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 15    11/28/11 5:05a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 14    11/23/11 5:22a Rajashakerg
// [TAG]  		EIP75473 
// [Category]  	Improvement
// [Description]  	System Time is not updated every second
// [Files]  		variable.h, variable.c, FormBrowser2.c, TseUefiHii.h,
// Uefi21Wapper.c, hii.h, uefi20Wapper.c
// 
// 13    3/28/11 5:01p Rajashakerg
// [TAG]  		EIP56413 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_RESET_BUTTON opcode
// [Files]  		ezport.c, minisetupext.h, ResetButton.c, ResetButton.h,
// Hii.c, TseUefiHii.h, Uefi21Wapper.c, hii.h, Uefi20Wapper.c 
// 
// 12    3/09/11 7:25p Madhans
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
// 11    2/01/11 7:35p Madhans
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
// 10    12/02/10 6:09p Madhans
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
// 9     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 8     6/15/10 12:16p Blaines
// Update functon prototype for UefiSetTime and UefiGetTime
// 
// 7     6/04/10 12:53p Blaines
// Add support for UEFI 2.1 date and time controls
// 
// 6     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 9     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 8     2/19/10 8:20a Mallikarjunanv
// updated year in copyright message
// 
// 7     2/17/10 7:03p Madhans
// 
// 6     1/09/10 7:22a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     8/17/09 12:28p Presannar
// Removed References to Tiano.h and replace it with Efi.h
// 
// 4     7/09/09 12:30p Mallikarjunanv
// updated the password encoding fix
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:08p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:14p Madhans
// UEFI Wrapper improvments.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Hii.h
//
// Description:	Header file for Hii functionallities 
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMIHII_H_	// DO NOT CHANGE THIS TO _HII_H_ !!  That is used by the HII Protocol header
#define	_AMIHII_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

extern /*EFI_HII_HANDLE*/VOID* gHiiHandle;


EFI_STATUS HiiExit( VOID );
EFI_STATUS HiiFixupData( );
UINTN HiiGetStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token );
/*EFI_HII_HANDLE*/VOID* HiiFindHandle( EFI_GUID *guid, UINT16 *index );
UINT16 HiiAddStringLanguage( /*EFI_HII_HANDLE*/VOID* handle, CHAR16 *lang, CHAR16 *string );
UINT16 HiiChangeString( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token, CHAR16 *string );
EFI_STATUS HiiLoadDefaults( VOID **VariableList, UINTN DefaultMask );
VOID HiiRemoveString(VOID* Handle, UINT16 Token);

/*EFI_HII_HANDLE*/VOID* * _HiiGetHandles( UINT16 *bufferSize );
EFI_STATUS _HiiLocateSetupHandles( VOID );
VOID *_HiiGetForm( /*EFI_HII_HANDLE*/VOID* handle, UINT16 form, UINTN *Length );
UINT16 _HiiGetLinkIndex( EFI_GUID *guid, UINT16 class, UINT16 subclass, UINT16 formid );

EFI_STATUS _HiiWrapperFindHandles( UINT16 *bufferSize, /*EFI_HII_HANDLE*/VOID* *buffer );

#if HII_VERSION <= 1
EFI_STATUS _HiiWrapperGetForm( /*EFI_HII_HANDLE*/VOID* handle, UINT16 form, UINT16 *bufferSize, VOID *buffer );
#else
EFI_STATUS _HiiWrapperGetForm( /*EFI_HII_HANDLE*/VOID* handle, UINT16 form, UINTN *bufferSize, VOID *buffer );
#endif
UINTN HiiMyGetStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token );
UINTN HiiMyGetMultiLineStringLength( /*EFI_HII_HANDLE*/VOID* handle, UINT16 token );
UINTN IsCharWide( CHAR16 strWide);


extern UINTN	gTitle;
extern UINTN	gHelp;
extern UINTN	gSubTitle;
extern UINTN	gHelpTitle;
extern UINTN	gNavStrings;

UINT16 UefiGetHelpField(VOID *);
UINT16 UefiGetPromptField(VOID *);
BOOLEAN UefiIsInteractive(CONTROL_INFO *ControlData);
UINT16 UefiGetKeyField(VOID *IfrPtr);
UINT8 UefiGetFlagsField(VOID *IfrPtr);
UINT16 UefiGetControlKey(CONTROL_INFO *ControlData);
UINT16 UefiGetTextField(VOID *IfrPtr);
UINT16 UefiGetTextTwoField(VOID *IfrPtr);
EFI_STATUS CallTextCallBack(TEXT_DATA *text, ACTION_DATA *Data);

UINT16 UefiGetMessageBoxTitle(VOID *ptr);
UINT16 UefiGetMessageBoxText(VOID *ptr);
VOID* UefiGetMessageBoxHandle(VOID *ptr);
VOID UefiSetSubTitleField(VOID *IfrPtr,UINT16 Token);
VOID * UefiCreateSubTitleTemplate(UINT16 Token);
UINT16 UefiGetTitleField(VOID *IfrPtr);
UINT64 UefiGetMinValue(VOID *IfrPtr);
UINT64 UefiGetMaxValue(VOID *IfrPtr);
UINT16 UefiGetWidth(VOID *IfrPtr);
UINT64 UefiGetStepValue(VOID *IfrPtr);
UINT8 UefiGetBaseValue(VOID *IfrPtr);
UINT16 UefiGetQuestionOffset(VOID *IfrPtr);
EFI_STATUS UefiGetTime(CONTROL_INFO *control, EFI_TIME *Tm);
EFI_STATUS UefiSetTime(CONTROL_INFO *control, EFI_TIME *Tm);
#define AMI_TIME_HOUR	1
#define AMI_TIME_MIN	2
#define AMI_TIME_SEC	3
#define AMI_DATE_YEAR	4
#define AMI_DATE_MONTH	5
#define AMI_DATE_DAY	6
VOID UefiGetDateTimeDetails(VOID *IfrPtr,UINT8 Type,UINT16 * Help,UINT16 * Min,UINT16 * Max);
UINT8 UefiGetIfrLength(VOID *IfrPtr);
VOID UefiSetPromptField(VOID *IfrPtr,UINT16 Token);
EFI_STATUS UefiGetOneOfOptions(CONTROL_INFO *IfrPtr,VOID **Handle,UINT16  **OptionPtrTokens, UINT64 **ValuePtrTokens, UINT16 * ItemCount,UINT16 * Interactive,UINT16 * CallBackKey );
UINT8 UefiGetMaxEntries(VOID *IfrPtr);
UINT16 UefiTseLiteGetBootOverRideIndex(VOID *Ptr);
UINT16 UefiTseLiteGetAmiCallbackIndex(VOID * Ptr,VOID * Ptr2 );
EFI_STATUS UefiFormCallbackNVRead(CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size, VOID **buffer);
EFI_STATUS UefiFormCallbackNVWrite(CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size);

BOOLEAN UefiIsEfiVariable(UINT32 variable, VARIABLE_INFO *varInfo);
EFI_STATUS UefiVarGetNvram(VARIABLE_INFO *VariableInfo, VOID **Buffer, UINTN Offset, UINTN Size);
EFI_STATUS UefiVarSetNvram(VARIABLE_INFO *VariableInfo, VOID *Buffer, UINTN Offset, UINTN Size);

UINTN HiiGetManufactuingMask(VOID);
UINTN HiiGetDefaultMask(VOID);

VOID* UefiGetSpecialEqIDIfrPtr(CONTROL_INFO *ControlInfo, UINT32 *Variable, GUID_INFO **GuidInfo);
UINT16 UefiGetSpecialEqIDValue(CONTROL_INFO *ControlInfo, GUID_INFO **GuidInfo);
VOID UefiSpecialGuidCallback(VOID * HiiHandle, UINT16 Key, EFI_GUID *pGUID);
VOID UefiSetEqIDValue(VOID *IfrPtr, UINT16 Value);
BOOLEAN UefiIsOneOfControl(VOID *IfrPtr);
UINT16 UefiGetEqIDQuestionID(VOID *IfrPtr);
VOID UefiSetEqIDQuestionID(VOID *IfrPtr, UINT16 Value);
VOID* UefiCreateOneOfWithOptionsTemplate(UINTN OptionCount, CONTROL_INFO *CtrlInfo);
VOID UefiSetOneOfOption(VOID *IfrPtr, UINT64 Value, UINT32 Size, UINT8 Flag, UINT16 Option);
UINT32 GetControlConditionVarId(CONTROL_INFO *control);
VOID UefiUpdateControlVarOffset(VOID *IfrPtr, UINT16 Value);
VOID UefiSetWidth(VOID *IfrPtr,UINT8 Width);
VOID UefiAddEndOp(VOID *IfrPtr);
VOID   BBSUpdateControlOffset(CONTROL_INFO *control);
UINT16 UefiGetQuestionID(CONTROL_INFO *control);
VOID UefiCreateDynamicControlCondition(CONTROL_INFO *control,UINT16 VarId, UINT16 PrevControlQuestionID,UINT16 Value);
EFI_STATUS SpecialActionCallBack(CONTROL_INFO * ControlData, UINT16 Key);
EFI_STATUS ProcessActionQuestionConfiguration(CONTROL_INFO *control);
//EIP 23354 : Start
BOOLEAN IsPasswordEncodeEnabled(VOID *PwDataPtr);
//EIP 23354 : End
EFI_STATUS UefiIsProceedWithPageChange(EFI_STATUS Status);
VOID UefiPreControlUpdate(CONTROL_INFO *ControlData);
EFI_STATUS UefiRefershQuestionValueNvRAM(CONTROL_INFO *ControlData);
UINT16 UefiGetResetButtonDefaultid(VOID *IfrPtr);//EIP:56413 Function decleration to get the Default ID
//EIP:56413 Function to update the Resetbutton Defaults to the control
EFI_STATUS UefiupdateResetButtonDefault(CONTROL_INFO ControlData, UINT16 DefaultId);
BOOLEAN CheckTimeFlags(UINT8 Flags);
BOOLEAN CheckDateFlags(UINT8 Flags);
UINTN UefiGetActionWapper(UINTN Action);
VOID UefiGetValidOptionType(CONTROL_INFO *CtrlInfo, UINTN *Type, UINT32 *SizeOfData);
#endif /* _AMIHII_H_ */


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
