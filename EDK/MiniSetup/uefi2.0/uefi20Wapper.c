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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/uefi20Wapper.c $
//
// $Author: Arunsb $
//
// $Revision: 34 $
//
// $Date: 5/02/14 10:38p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/uefi20Wapper.c $
// 
// 34    5/02/14 10:38p Arunsb
// gEnableProcessPack variable added to avoid build error
// 
// 33    6/10/13 2:15p Arunsb
// EvaluateControlDefault function added to avoid build error in 2.0
// 
// 32    3/25/13 8:34a Premkumara
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
// 31    10/18/12 6:00a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 18    10/10/12 12:39p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 28    9/25/12 1:45p Premkumara
// EIP - 99059 - Updated for UEFI2.0
// Files - Hii.c, Uefi20Wapper.c
// 
// 27    2/02/12 2:56a Premkumara
// [TAG]  		EIP75066 
// [Category]  	Improvement
// [Description]  	Support loading defaults for Ordelist controls
// [Files]  		Ordlistbox.c, Uefi21Wapper.c, CtrlCond.c, HiiCallback.c,
// Parse.c, Uefi20Wapper.c, TseUefihiil.h
// 
// 26    12/08/11 9:37a Rajashakerg
// [TAG]  		EIP75588
// [Category]  	Improvement
// [Description]  	Updated the file to aviod build errors when build for
// UEFI 20 by providing the dummy functions.
// 
// 25    12/02/11 1:52a Premkumara
// [TAG]  		EIP73226
// [Category]  	New Feature
// [Description]  	Extended support for password prompt
// [Files]  	FakeToken.c, Uefi21Wapper.c, AmiTSEStr.uni, PopupPassword.c,
// HiiCallBack.c, Uefi20Wapper.c
// 
// 24    12/01/11 7:16p Blaines
// Fix build errors in Uefi2.0
// 
// 23    11/28/11 5:06a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 22    11/23/11 5:24a Rajashakerg
// [TAG]  		EIP75473 
// [Category]  	Improvement
// [Description]  	System Time is not updated every second
// [Files]  		variable.h, variable.c, FormBrowser2.c, TseUefiHii.h,
// Uefi21Wapper.c, hii.h, uefi20Wapper.c
// 
// 21    10/18/11 1:50p Blaines
// [TAG] - EIP 66860
// [Category]- Function Request
// [Synopsis]- AmiPostManager interface for text entry.
// [Files] - LogoLib.h, AMIPostMgr.h, protocol.c, protocol.h,
// TseAdvanced.c, TseLitehelper.c, TseUefiHii.h, Uefi21Wapper.c,
// uefi20Wapper.c
// 
// 20    6/30/11 4:15a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Wrapper functions added.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 19    6/28/11 3:44p Arunsb
// [TAG]  		EIP55762
// [Description]  	Dummy  UpdateDestiantionQuestion function added
// 
// 18    4/29/11 4:39p Arunsb
// For 2.13 public patch release IFR RefX feature is omitted
// 
// 16    3/28/11 5:03p Rajashakerg
// [TAG]  		EIP56413 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_RESET_BUTTON opcode
// [Files]  		ezport.c, minisetupext.h, ResetButton.c, ResetButton.h,
// Hii.c, TseUefiHii.h, Uefi21Wapper.c, hii.h, Uefi20Wapper.c 
// 
// 15    3/09/11 7:25p Madhans
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
// 14    2/01/11 7:41p Madhans
// [TAG] - EIP 52032 
// [Category]- Defect
// [Severity]- Mordarate
// [Symptom] - In UEFI2.0 Updating the Interactive One of Control may not
// work correctly.
// [RootCause] - The UefiGetControlKey for Interactive one of control is
// not returned properly.
// [Solution]- fix in UefiGetControlKey control.
// [Files] - uefi20wapper.c
// 
// 13    2/01/11 7:37p Madhans
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
// 12    12/02/10 6:09p Madhans
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
// 11    9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 10    6/15/10 12:16p Blaines
// Update functon prototype for UefiSetTime and UefiGetTime
// 
// 9     6/04/10 12:53p Blaines
// Add support for UEFI 2.1 date and time controls
// 
// 8     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 11    2/19/10 8:20a Mallikarjunanv
// updated year in copyright message
// 
// 10    1/29/10 4:34p Madhans
// To avoid compiler warnings.
// 
// 9     1/27/10 12:59p Madhans
// // EIP 33804 : Issue iSCSI initiator name is not saved..
// 
// 8     1/09/10 7:30a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 7     10/19/09 10:52a Blaines
// EIP #26029 Fix: UefiCreateOneOfWithOptionsTemplate() does not always
// return NULL when EfiLibAllocateZeroPool() returns NULL
// 
// 6     7/09/09 12:30p Mallikarjunanv
// updated the password encoding fix
// 
// 4     6/24/09 6:11p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
// 
// 3     6/23/09 6:51p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:09p Madhans
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
// 
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		uefi20wraper.c
//
// Description:	This file contains code for UEFI2.0 wrapper
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include EFI_PROTOCOL_DEFINITION(Hii)
#include EFI_PROTOCOL_DEFINITION(FormCallback)
extern EFI_HII_PROTOCOL	*gHiiProtocol;
BOOLEAN gPackUpdatePending = FALSE;
BOOLEAN gEnableProcessPack = FALSE; //Added to avoid build error

static EFI_IFR_SUBTITLE	_Title = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, 0 };
static EFI_IFR_SUBTITLE	_Help = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, 0 };
static EFI_IFR_SUBTITLE	_SubTitle = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, 0 };
static EFI_IFR_SUBTITLE	_HelpTitle = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, STRING_TOKEN(STR_HELP_TITLE) };
static EFI_IFR_SUBTITLE	_NavStrings = { { EFI_IFR_SUBTITLE_OP, sizeof(EFI_IFR_SUBTITLE) }, 0 };

UINTN	gTitle = (UINTN)&_Title;
UINTN	gHelp = (UINTN)&_Help;
UINTN	gSubTitle = (UINTN)&_SubTitle;
UINTN	gHelpTitle = (UINTN)&_HelpTitle;
UINTN	gNavStrings = (UINTN)&_NavStrings;

EFI_IFR_FORM_SET *HiiGetFormSetFromHandle( /*EFI_HII_HANDLE*/VOID* handle );
EFI_IFR_FORM_SET *HiiGetFormSet( UINTN index );
VOID *UefiCreateStringTemplate(UINT16 Token);

UINT32 FindVarFromITKQuestionId(UINT16 QuestionId);
UINT32 GetVarNumFromVarID(UINT32 ID);
VOID UefiSetHelpField(VOID *IfrPtr,UINT16 Token);
////For avoiding build error EIP101564
UINT32 gRefreshIdCount = 0; //No. of controls with Refresh Id set	
REFRESH_ID_INFO *gRefreshIdInfo = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetHelpField
//
// Description:	To get the specific help field
//
// Input:		VOID *IfrPtr
//
// Output:		Help Field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetHelpField(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_REF_OP:
		return ((EFI_IFR_REF*)OpHeader)->Help;
		break;
	case EFI_IFR_TEXT_OP:
		return ((EFI_IFR_TEXT*)OpHeader)->Help;
		break;
	case EFI_IFR_ONE_OF_OP:
		return ((EFI_IFR_ONE_OF*)OpHeader)->Help;
		break;
	case EFI_IFR_TIME_OP:
	case EFI_IFR_DATE_OP:
	case EFI_IFR_NUMERIC_OP:
		return ((EFI_IFR_NUMERIC*)OpHeader)->Help; 
		break;
	case EFI_IFR_PASSWORD_OP:
		return ((EFI_IFR_PASSWORD*)OpHeader)->Help; 
		break;
	case EFI_IFR_STRING_OP:
		return ((EFI_IFR_STRING*)OpHeader)->Help; 
		break;
	default:
		break;
	}

	return 0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiSetHelpField
//
// Description:	To Set the specific help field
//
// Input:	VOID *IfrPtr,	UINT16 Token
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetHelpField(VOID *IfrPtr, UINT16 Token)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_REF_OP:
		((EFI_IFR_REF*)OpHeader)->Help = Token ;
		break;
	case EFI_IFR_TEXT_OP:
		((EFI_IFR_TEXT*)OpHeader)->Help = Token ;
		break;
	case EFI_IFR_ONE_OF_OP:
		((EFI_IFR_ONE_OF*)OpHeader)->Help = Token ;
		break;
	case EFI_IFR_TIME_OP:
	case EFI_IFR_DATE_OP:
	case EFI_IFR_NUMERIC_OP:
		((EFI_IFR_NUMERIC*)OpHeader)->Help = Token ;
		break;
	case EFI_IFR_PASSWORD_OP:
		((EFI_IFR_PASSWORD*)OpHeader)->Help = Token ;
		break;
	case EFI_IFR_STRING_OP:
		((EFI_IFR_STRING*)OpHeader)->Help = Token ;
		break;
	default:
		break;
	}
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetPromptField
//
// Description:	To get the prompt field from ifr
//
// Input:		VOID *IfrPtr
//
// Output:		Prompt Field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetPromptField(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_REF_OP:
		return ((EFI_IFR_REF*)OpHeader)->Prompt;
		break;
	case EFI_IFR_NUMERIC_OP:
	case EFI_IFR_TIME_OP:
	case EFI_IFR_DATE_OP:
		return ((EFI_IFR_NUMERIC*)OpHeader)->Prompt;
		break;
	case EFI_IFR_ONE_OF_OP:
		return ((EFI_IFR_ONE_OF*)OpHeader)->Prompt;
		break;
	case EFI_IFR_ORDERED_LIST_OP:
		return ((EFI_IFR_ORDERED_LIST*)OpHeader)->Prompt;
		break;
	case EFI_IFR_CHECKBOX_OP:
		return ((EFI_IFR_CHECK_BOX*)OpHeader)->Prompt;
		break;
	case EFI_IFR_PASSWORD_OP:
		return ((EFI_IFR_PASSWORD*)OpHeader)->Prompt;
		break;
	case EFI_IFR_STRING_OP:
		return ((EFI_IFR_STRING*)OpHeader)->Prompt;
		break;
	default:
		break;
	}

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetKeyField
//
// Description:	To get the Key field from ifr
//
// Input:		VOID *IfrPtr
//
// Output:		Key Field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetKeyField(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_REF_OP:
		return ((EFI_IFR_REF*)OpHeader)->Key;
		break;
	case EFI_IFR_NUMERIC_OP:
		return ((EFI_IFR_NUMERIC*)OpHeader)->Key;
		break;
	case EFI_IFR_PASSWORD_OP:
		return ((EFI_IFR_PASSWORD*)OpHeader)->Key;
		break;
	case EFI_IFR_TEXT_OP:
		return ((EFI_IFR_TEXT*)OpHeader)->Key;
		break;
	case EFI_IFR_CHECKBOX_OP:
		return ((EFI_IFR_CHECK_BOX*)OpHeader)->Key;
		break;
	case EFI_IFR_ONE_OF_OP:
    case EFI_IFR_ORDERED_LIST_OP:
    	if(OpHeader->OpCode == EFI_IFR_ORDERED_LIST_OP)
    		OpHeader = (EFI_IFR_OP_HEADER *)(((UINT8 *)OpHeader) +sizeof(EFI_IFR_ORDERED_LIST) );
    	else
    		OpHeader = (EFI_IFR_OP_HEADER *)(((UINT8 *)OpHeader) +sizeof(EFI_IFR_ONE_OF) );
		return ((EFI_IFR_ONE_OF_OPTION*)OpHeader)->Key;
		break;
	case EFI_IFR_ONE_OF_OPTION_OP:
		return ((EFI_IFR_ONE_OF_OPTION*)OpHeader)->Key;
		break;
	case EFI_IFR_STRING_OP:
		return ((EFI_IFR_STRING*)OpHeader)->Key;
		break;
	default:
		break;
	}

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetTitleField
//
// Description:	To get the Title field from ifr
//
// Input:		VOID *IfrPtr
//
// Output:		Title Field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetTitleField(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_SUBTITLE_OP:
		return ((EFI_IFR_SUBTITLE*)OpHeader)->SubTitle;
		break;
	case EFI_IFR_FORM_OP:
		return ((EFI_IFR_FORM*)OpHeader)->FormTitle;
		break;
	default:
		break;
	}

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetFlagsField
//
// Description:	to get the Flags field from ifr
//
// Input:		VOID *IfrPtr
//
// Output:		Flags Field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UefiGetFlagsField(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_REF_OP:
		return ((EFI_IFR_REF*)OpHeader)->Flags;
		break;
	default:
		break;
	}

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiIsInteractive
//
// Description: To get Uefi Interactive
//
// Input:		CONTROL_INFO *ControlData
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN UefiIsInteractive(CONTROL_INFO *ControlData)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)ControlData->ControlPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_REF_OP:
		return ((((EFI_IFR_REF*)OpHeader)->Flags & EFI_IFR_FLAG_INTERACTIVE)?TRUE:FALSE);
		break;
	case EFI_IFR_NUMERIC_OP:
		return ((((EFI_IFR_NUMERIC*)OpHeader)->Flags & EFI_IFR_FLAG_INTERACTIVE)?TRUE:FALSE);
		break;
	case EFI_IFR_STRING_OP:
		return ((((EFI_IFR_STRING*)OpHeader)->Flags & EFI_IFR_FLAG_INTERACTIVE)?TRUE:FALSE);
		break;
	case EFI_IFR_PASSWORD_OP:
		return ((((EFI_IFR_PASSWORD*)OpHeader)->Flags & EFI_IFR_FLAG_INTERACTIVE)?TRUE:FALSE);
		break;
	default:
		break;
	}

	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetControlKey
//
// Description:	Helper function in obtaining Control Key
//
// Input:		CONTROL_INFO *ControlData
//
// Output:		Key Field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetControlKey(CONTROL_INFO *ControlData)
{
	return UefiGetKeyField((VOID*)ControlData->ControlPtr);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetTextField
//
// Description:	Function to get the Text Field.
//
// Input:		VOID *IfrPtr
//
// Output:		Text Field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetTextField(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_TEXT_OP:
		return ((EFI_IFR_TEXT*)OpHeader)->Text;
		break;
	default:
		break;
	}

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetTextTwoField
//
// Description:	Function to get the Text Field.
//
// Input:		VOID *IfrPtr
//
// Output:		Text Field
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetTextTwoField(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_TEXT_OP:
		return ((EFI_IFR_TEXT*)OpHeader)->TextTwo;
		break;
	default:
		break;
	}

	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiSetSubTitleField
//
// Description:	Function to Set the Sub-Title Field.
//
// Input:		VOID *IfrPtr,	UINT16 Token
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetSubTitleField(VOID *IfrPtr,UINT16 Token)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_SUBTITLE_OP:
		((EFI_IFR_SUBTITLE*)OpHeader)->SubTitle = Token;
		break;
	default:
		break;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiSetPromptField
//
// Description:	Function to set the prompt Field.
//
// Input:	VOID *IfrPtr,	UINT16 Token
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetPromptField(VOID *IfrPtr,UINT16 Token)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_REF_OP:
		((EFI_IFR_REF*)OpHeader)->Prompt = Token;
		break;
	case EFI_IFR_NUMERIC_OP:
	case EFI_IFR_TIME_OP:
	case EFI_IFR_DATE_OP:
		((EFI_IFR_NUMERIC*)OpHeader)->Prompt = Token;
		break;
	case EFI_IFR_ONE_OF_OP:
		((EFI_IFR_ONE_OF*)OpHeader)->Prompt = Token;
		break;
	case EFI_IFR_ORDERED_LIST_OP:
		((EFI_IFR_ORDERED_LIST*)OpHeader)->Prompt = Token;
		break;
	case EFI_IFR_CHECKBOX_OP:
		((EFI_IFR_CHECK_BOX*)OpHeader)->Prompt = Token;
		break;
	case EFI_IFR_PASSWORD_OP:
		((EFI_IFR_PASSWORD*)OpHeader)->Prompt = Token;
		break;
	case EFI_IFR_STRING_OP:
		((EFI_IFR_STRING*)OpHeader)->Prompt = Token;
		break;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiCreateSubTitleTemplate
//
// Description:	Function to prepare the template for sub-title
//
// Input:		UINT16 Token
//
// Output:		VOID
//
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
// Procedure:	UefiGetIfrLength
//
// Description:	Function to get the length of Ifr
//
// Input:		VOID *IfrPtr
//
// Output:		Length
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UefiGetIfrLength(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;
	return OpHeader->Length;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetMinValue
//
// Description: Function to get the minimum value
//
// Input:		VOID *IfrPtr
//
// Output:		UINT64
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT64 UefiGetMinValue(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_NUMERIC_OP:
		return (UINT64)((EFI_IFR_NUMERIC*)OpHeader)->Minimum;
		break;
	case EFI_IFR_PASSWORD_OP:
		return (UINT64)((EFI_IFR_PASSWORD*)OpHeader)->MinSize;
		break;
	case EFI_IFR_STRING_OP:
		return (UINT64)((EFI_IFR_STRING*)OpHeader)->MinSize;
		break;
	default:
		break;
	}
	return (UINT64)0;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetMaxValue
//
// Description:	Function to get the max value
//
// Input:		VOID *IfrPtr
//
// Output:		UINT64
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT64 UefiGetMaxValue(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_NUMERIC_OP:
		return (UINT64)((EFI_IFR_NUMERIC*)OpHeader)->Maximum;
		break;
	case EFI_IFR_PASSWORD_OP:
		return (UINT64)((EFI_IFR_PASSWORD*)OpHeader)->MaxSize;
		break;
	case EFI_IFR_STRING_OP:
		return (UINT64)((EFI_IFR_STRING*)OpHeader)->MaxSize;
		break;
	default:
		break;
	}
	return (UINT64)0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetStepValue
//
// Description:	Function to get the step value
//
// Input:		VOID *IfrPtr
//
// Output:		UINT64
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT64 UefiGetStepValue(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_NUMERIC_OP:
		return (UINT64)((EFI_IFR_NUMERIC*)OpHeader)->Step;
		break;
	default:
		break;
	}
	return (UINT64)0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetBaseValue
//
// Description:	Function to get the base value
//
// Input:		VOID *IfrPtr
//
// Output:		UINT8
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UefiGetBaseValue(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_NUMERIC_OP:
		return AMI_BASE_DEC;
		break;
	default:
		break;
	}
	return AMI_BASE_DEC;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetWidth
//
// Description:	Function to get width
//
// Input:		VOID *IfrPtr
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetWidth(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_NUMERIC_OP:
		return (UINT16)((EFI_IFR_NUMERIC*)OpHeader)->Width;
		break;
	case EFI_IFR_PASSWORD_OP:
		return (UINT16)((EFI_IFR_PASSWORD*)OpHeader)->Width;
		break;
	case EFI_IFR_STRING_OP:
		return (UINT16)((EFI_IFR_STRING*)OpHeader)->Width;
		break;
	case EFI_IFR_ONE_OF_OP:
		return (UINT16)((EFI_IFR_ONE_OF*)OpHeader)->Width;
		break;
	case EFI_IFR_CHECKBOX_OP:
		return (UINT16)((EFI_IFR_CHECK_BOX*)OpHeader)->Width;
		break;
	case EFI_IFR_EQ_ID_VAL_OP:
		return (UINT16)((EFI_IFR_EQ_ID_VAL*)OpHeader)->Width;
		break;
	case EFI_IFR_EQ_ID_LIST_OP:
		return (UINT16)((EFI_IFR_EQ_ID_LIST*)OpHeader)->Width;
		break;
	case EFI_IFR_EQ_ID_ID_OP:
		return (UINT16)((EFI_IFR_EQ_ID_ID*)OpHeader)->Width;
		break;
	default:
		break;
	}
	return (UINT16)0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiSetWidth
//
// Description:	Function to set width
//
// Input:		VOID *IfrPtr
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetWidth(VOID *IfrPtr,UINT8 Width)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_NUMERIC_OP:
		((EFI_IFR_NUMERIC*)OpHeader)->Width = Width;
		break;
	case EFI_IFR_PASSWORD_OP:
		((EFI_IFR_PASSWORD*)OpHeader)->Width = Width ;
		break;
	case EFI_IFR_STRING_OP:
		((EFI_IFR_STRING*)OpHeader)->Width = Width;
		break;
	case EFI_IFR_ONE_OF_OP:
		((EFI_IFR_ONE_OF*)OpHeader)->Width = Width;
		break;
	case EFI_IFR_CHECKBOX_OP:
		((EFI_IFR_CHECK_BOX*)OpHeader)->Width = Width;
		break;
	case EFI_IFR_EQ_ID_VAL_OP:
		((EFI_IFR_EQ_ID_VAL*)OpHeader)->Width = Width;
		break;
	case EFI_IFR_EQ_ID_LIST_OP:
		((EFI_IFR_EQ_ID_LIST*)OpHeader)->Width = Width;
		break;
	case EFI_IFR_EQ_ID_ID_OP:
		((EFI_IFR_EQ_ID_ID*)OpHeader)->Width = Width;
		break;
	default:
		break;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetQuestionOffset
//
// Description:	Function to get question offset
//
// Input:		VOID *IfrPtr
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetQuestionOffset(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	return (UINT16)((EFI_IFR_NV_DATA*)OpHeader)->QuestionId;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetDateTimeDetails
//
// Description:	Function to get the details of data and time
//
// Input:		VOID *IfrPtr,
//				UINT8 Type,
//				UINT16 * Help,
//				UINT16 * Min,
//				UINT16 * Max
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiGetDateTimeDetails(VOID *IfrPtr,UINT8 Type,UINT16 * Help,UINT16 * Min,UINT16 * Max)
{
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
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetOneOfOptions
//
// Description:	Function to get OneOf options
//
// Input:	VOID *IfrPtr,
//					VOID **Handle,
//					UINT16  **OptionPtrTokens,
//					UINT64 **ValuePtrTokens,
//					UINT16 * ItemCount,
//					UINT16 * Interactive,
//					UINT16 * CallBackKey
//
// Output:	Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiGetOneOfOptions(CONTROL_INFO *CtrlInfo,VOID **Handle,UINT16  **OptionPtrTokens, UINT64 **ValuePtrTokens, UINT16 * ItemCount,UINT16 * Interactive,UINT16 * CallBackKey )
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)(CtrlInfo->ControlPtr);
	EFI_IFR_ONE_OF_OPTION *ptrData;
	UINT8 Opcode = OpHeader->OpCode;
	EFI_STATUS Status = EFI_SUCCESS;
	UINT16 Index= 0 ;

	if(Opcode == EFI_IFR_ORDERED_LIST_OP)
		ptrData = (EFI_IFR_ONE_OF_OPTION *)((UINT8 *)(OpHeader) +sizeof(EFI_IFR_ORDERED_LIST) );
	else
		ptrData = (EFI_IFR_ONE_OF_OPTION *)((UINT8 *)(OpHeader) +sizeof(EFI_IFR_ONE_OF) );

	switch ( Opcode )
	{
		case EFI_IFR_ONE_OF_OP:
		case EFI_IFR_ORDERED_LIST_OP: // ordered list option 
			while( ptrData[Index].Header.OpCode != EFI_IFR_END_ONE_OF_OP )
				Index++;
			break;

		case EFI_IFR_CHECKBOX_OP:
			Index = 2;
			*Handle = gHiiHandle;
			break;
	}
	if( *OptionPtrTokens != NULL )
      MemFreePointer( (VOID **)OptionPtrTokens);

	if(ValuePtrTokens)
		if( *ValuePtrTokens != NULL )
			MemFreePointer( (VOID **)ValuePtrTokens);

	
	*OptionPtrTokens = EfiLibAllocatePool( Index * sizeof(UINT16) );

	if(ValuePtrTokens)
		*ValuePtrTokens = EfiLibAllocatePool( Index * sizeof(UINT64) );

	if ( *OptionPtrTokens == NULL )
		Status = EFI_OUT_OF_RESOURCES;
	else
	{
		*ItemCount = Index;

		for ( Index = 0; Index < *ItemCount; Index++ )
		{
			if( ((Opcode == EFI_IFR_ONE_OF_OP)|(Opcode == EFI_IFR_ORDERED_LIST_OP)) && (ptrData->Header.OpCode == EFI_IFR_ONE_OF_OPTION_OP) )
			{
				(*OptionPtrTokens)[Index] = ptrData[Index].Option;
				if(ValuePtrTokens)
					(*ValuePtrTokens)[Index] = ptrData[Index].Value;
				
                if(ptrData[Index].Flags & EFI_IFR_FLAG_INTERACTIVE)
                {
                    if(Interactive) *Interactive = TRUE;
                    if(CallBackKey) *CallBackKey = ptrData[Index].Key;
                }
			}
			else
			{
				(*OptionPtrTokens)[Index] = gCheckboxTokens[Index];
				if(ValuePtrTokens)
					(*ValuePtrTokens)[Index] = Index;
                if(((EFI_IFR_CHECK_BOX *)OpHeader)->Flags & EFI_IFR_FLAG_INTERACTIVE)
                {
                    if(Interactive) *Interactive = TRUE;
                    if(CallBackKey) *CallBackKey = ((EFI_IFR_CHECK_BOX *)OpHeader)->Key;
                }

			}
		}
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetMaxEntries
//
// Description:	Function to get max entries
//
// Input:	VOID *IfrPtr,
//
// Output:	UINT8
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UefiGetMaxEntries(VOID *IfrPtr)
{
	EFI_IFR_OP_HEADER *OpHeader=(EFI_IFR_OP_HEADER *)IfrPtr;

	switch(OpHeader->OpCode)
	{
	case EFI_IFR_ORDERED_LIST_OP:
		return ((EFI_IFR_ORDERED_LIST*)OpHeader)->MaxEntries;
		break;
	default:
		break;
	}
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiTseLiteGetBootOverRideIndex
//
// Description:	Function to get boot override index
//
// Input:	VOID *Ptr,
//
// Output:	UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiTseLiteGetBootOverRideIndex(VOID *Ptr)
{
	UINT16 Index=0xFFFF;
	EFI_IFR_OP_HEADER * OpHeader = (EFI_IFR_OP_HEADER *)Ptr;
	EFI_IFR_EQ_ID_LIST *EqIdList;

	if ((OpHeader != NULL) && (OpHeader->OpCode == EFI_IFR_SUPPRESS_IF_OP))
	{
		while(OpHeader->OpCode != EFI_IFR_EQ_ID_LIST_OP)
		{
			OpHeader = (EFI_IFR_OP_HEADER*)((UINT8*)OpHeader + OpHeader->Length);
			if(OpHeader->OpCode == EFI_IFR_END_IF_OP) // Not found
				return Index;
		}
	
		// FIX ME : Do it better. Check the list length and 
		if(OpHeader->OpCode == EFI_IFR_EQ_ID_LIST_OP)
		{
			EqIdList = (EFI_IFR_EQ_ID_LIST*)OpHeader;
			Index = EqIdList->ListLength - 1;
		}
	}

	return Index;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiTseLiteGetAmiCallbackIndex
//
// Description:	Function to get ami callback index
//
// Input:	VOID *Ptr,
//
// Output:	UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiTseLiteGetAmiCallbackIndex(VOID * Ptr, VOID * Ptr2)
{
	UINT16 Index=0xFFFF;
	EFI_IFR_OP_HEADER * OpHeader = (EFI_IFR_OP_HEADER *)Ptr;

	if ((OpHeader != NULL) && (OpHeader->OpCode == EFI_IFR_SUPPRESS_IF_OP))
	{
		while(OpHeader->OpCode != EFI_IFR_EQ_ID_VAL_OP)
		{
			OpHeader = (EFI_IFR_OP_HEADER*)((UINT8*)OpHeader + OpHeader->Length);
			if(OpHeader->OpCode == EFI_IFR_END_IF_OP) // Not found
				return Index;
		}
	
		// FIX ME : Do it better. Check the list length and 
		if(OpHeader->OpCode == EFI_IFR_EQ_ID_VAL_OP)
		{
			Index = ((EFI_IFR_EQ_ID_VAL*)OpHeader)->Value;
		}
	}

	return Index;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiFormCallbackNVRead
//
// Description:	Function to get callback nvread
//
// Input:		CHAR16 *name,
//					EFI_GUID *guid,
//					UINT32 *attributes,
//					UINTN *size,
//					VOID **buffer
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiFormCallbackNVRead(CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size, VOID **buffer)
{
	EFI_FORM_CALLBACK_PROTOCOL *FormCallBack=NULL;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_IFR_FORM_SET *FmSet=NULL;
	UINTN i=0;

    if(gSetupCount)
    {
        for ( i = 0; i < gSetupCount - 1; i++ )
        {
            FmSet = HiiGetFormSet( i );
            if(!FmSet)
                continue;

            if( EfiCompareGuid(&(FmSet->Guid),guid) && (EFI_HANDLE)((UINTN)FmSet->CallbackHandle) )
            {
                Status = gBS->HandleProtocol(
                                    (EFI_HANDLE)((UINTN)FmSet->CallbackHandle),
                                    &gEfiFormCallbackProtocolGuid,
                                    &FormCallBack );
            }

	        if ( ! EFI_ERROR( Status ) )
	        {
        		if( FormCallBack->NvRead )
		        {
                    Status = FormCallBack->NvRead( FormCallBack, name, guid, attributes, size, *buffer );

        		    if ( Status != EFI_BUFFER_TOO_SMALL )
						break;

        		    *buffer = EfiLibAllocatePool( *size );

        		    if ( *buffer == NULL )
			            return EFI_OUT_OF_RESOURCES;

        		    Status = FormCallBack->NvRead( FormCallBack, name, guid, attributes, size, *buffer );
                    break;
		        }
		        else
			        Status = EFI_UNSUPPORTED;
	        }
        }
    }

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiFormCallbackNVWrite
//
// Description:	Function to get callback nvwrite
//
// Input:		CHAR16 *name,
//				EFI_GUID *guid,
//				UINT32 *attributes,
//				VOID **buffer
//				UINTN *size,
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiFormCallbackNVWrite(CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size)
{
	EFI_FORM_CALLBACK_PROTOCOL *FormCallBack=NULL;
	BOOLEAN Reset=FALSE;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_IFR_FORM_SET * FmSet=NULL;
	UINTN i=0;

    if(gSetupCount)
    {
        for ( i = 0; i < gSetupCount - 1; i++ )
        { 
            FmSet = HiiGetFormSet( i );

            if(!FmSet)
                continue;

            if( EfiCompareGuid(&(FmSet->Guid),guid) && (EFI_HANDLE)((UINTN)FmSet->CallbackHandle) )
            {
        		Status = gBS->HandleProtocol(
                                    (EFI_HANDLE)((UINTN)FmSet->CallbackHandle),
                                    &gEfiFormCallbackProtocolGuid,
                                    &FormCallBack );
            }

	        if ( ! EFI_ERROR(Status ) )
	        {
		        if( FormCallBack->NvWrite )
                {
					Reset = FALSE;
					Status = FormCallBack->NvWrite(
				                        FormCallBack,
				                        name,
				                        guid,
				                        attributes,
				                        size,
				                        buffer,
				                        &Reset
				                        );
			        if ( ( ! EFI_ERROR(Status ) ) && Reset )
						gResetRequired = TRUE;
                    break;
                }
		        else
			        Status = EFI_UNSUPPORTED;
	        }
        }
    }
	return Status;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitMiniSetupStrings
//
// Description:	Function to init minisetup strings
//
// Input:		VOID
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if APTIO_4_00 != 1 && SETUP_USE_GUIDED_SECTION !=1
EFI_STATUS InitMiniSetupStrings( VOID )
{
	EFI_STATUS          Status=EFI_SUCCESS;
	UINT16              Index = 0;

#if HII_VERSION == 0
	EFI_HII_PACK_LIST   PackList;
	EFI_HII_PACK_LIST   *PackageList;
#else
	EFI_HII_PACKAGES	*PackageList = NULL;
#endif
	VOID **Package = NULL;
	EFI_GUID            MiniSetupGuid = MINI_SETUP_GUID;

	Status = HiiInitializeProtocol();
	if ( EFI_ERROR ( Status ) )
		return Status;

	gHiiHandle = HiiFindHandle( &MiniSetupGuid, &Index );

	if ( gHiiHandle == INVALID_HANDLE )
	{
#if HII_VERSION == 0
		PackList.IfrPack      = NULL;
		PackList.StringPack   = (EFI_HII_STRING_PACK *)STRING_ARRAY_NAME;
		PackList.FontPack     = NULL;
		PackList.KeyboardPack = NULL;
		PackList.GuidId       = &MiniSetupGuid;
		PackageList = &PackList;
#else
		PackageList = EfiLibAllocateZeroPool( sizeof(EFI_HII_PACKAGES) + sizeof(VOID *) );
		if ( PackageList == NULL )
			return EFI_OUT_OF_RESOURCES;

		PackageList->GuidId = &MiniSetupGuid;
		PackageList->NumberOfPackages = 1;
		Package = (VOID **) ((UINT8 *)PackageList + sizeof (EFI_HII_PACKAGES));
#ifdef USE_DEPRICATED_INTERFACE
		*Package = (VOID *)STRING_ARRAY_NAME;
#else
		*Package = (VOID *)&STRING_ARRAY_NAME;
#endif
#endif

		Status = gHiiProtocol->NewPack( gHiiProtocol, PackageList, (EFI_HII_HANDLE *)&gHiiHandle );
#if HII_VERSION != 0
		MemFreePointer( (VOID **)&PackageList );
#endif
	} 

	return Status;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiIsEfiVariable
//
// Description:	Function to check efi variable
//
// Input:		UINT32 variable, VARIABLE_INFO *varInfo
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN UefiIsEfiVariable(UINT32 variable, VARIABLE_INFO *varInfo)
{
	return TRUE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiVarGetNvram
//
// Description:	Function to get nvram
//
// Parameter:	    VARIABLE_INFO *VariableInfo, VOID **Buffer, UINTN Offset, 
//					UINTN Size
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiVarGetNvram(VARIABLE_INFO *VariableInfo, VOID **Buffer, UINTN Offset, UINTN Size)
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiVarGetNvram
//
// Description:	Function to set nvram
//
// Parameter:	    VARIABLE_INFO *VariableInfo, VOID *Buffer, UINTN Offset,
//					UINTN Size
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiVarSetNvram(VARIABLE_INFO *VariableInfo, VOID *Buffer, UINTN Offset, UINTN Size)
{
	return EFI_UNSUPPORTED;
}

#define AMI_FLAG_MANUFACTURING	EFI_IFR_FLAG_MANUFACTURING
#define AMI_FLAG_DEFAULT	EFI_IFR_FLAG_DEFAULT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiGetManufactuingMask
//
// Description:	Function to get manufacturing mask
//
// Input:		VOID
//
// Output:		UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN HiiGetManufactuingMask(VOID)
{
	return AMI_FLAG_MANUFACTURING;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiGetDefaultMask
//
// Description:	Function to get default mask
//
// Input:		VOID
//
// Output:		UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN HiiGetDefaultMask(VOID)
{
	return AMI_FLAG_DEFAULT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetControlConditionVarId
//
// Description:	Function to get control variable id
//
// Input:		CONTROL_INFO *control
//
// Output:		UINT32
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 GetControlConditionVarId(CONTROL_INFO *control)
{
	return (control->ControlConditionalVariable[0])?control->ControlConditionalVariable[0]:0xFFFF;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	BBSUpdateControlOffset
//
// Description:	Function to update control offset
//
// Input:		CONTROL_INFO *control
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID   BBSUpdateControlOffset(CONTROL_INFO *control)
{
    UINT16 offset=  ((EFI_IFR_ONE_OF*)control->ControlPtr)->QuestionId;

    offset = offset +sizeof(UINT32)+sizeof(UINT16);
    offset = (UINT16)(offset + gCurrLegacyBootData->LegacyEntryOffset);

    ((EFI_IFR_ONE_OF*)control->ControlPtr)->QuestionId = offset;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetSpecialEqIDIfrPtr
//
// Description:	Function to get special eqID Ifr pointer
//
// Input:		VOID *Conditional, UINT32 Variable, GUID_INFO **GuidInfo
//
// Output:		VOID*
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* UefiGetSpecialEqIDIfrPtr(CONTROL_INFO *ControlInfo, UINT32 *Variable, GUID_INFO **GuidInfo)
{
    VOID *Conditional = ControlInfo->ControlConditionalPtr;
    VOID *ControlPtr = ControlInfo->ControlPtr;
	EFI_IFR_OP_HEADER *ifrPtr;
	VARIABLE_INFO *varInfo;
	UINTN i;
	GUID_INFO *specialGuid = NULL;

	ifrPtr = (EFI_IFR_OP_HEADER *)Conditional;

    if((ifrPtr==NULL) || (ControlPtr <= Conditional))
        return NULL;

	if ( ( ifrPtr->OpCode != EFI_IFR_SUPPRESS_IF_OP ) && ( ifrPtr->OpCode != EFI_IFR_GRAYOUT_IF_OP ) )
		return NULL;

	ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length);
	if ( ( ifrPtr->OpCode == EFI_IFR_VARSTORE_SELECT_OP ) || ( ifrPtr->OpCode == EFI_IFR_VARSTORE_SELECT_PAIR_OP ) )
		ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length);

	// skip NOT if it is present
	if ( ifrPtr->OpCode == EFI_IFR_NOT_OP )
		ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length);

	if(NoVarStoreSupport())
	{
	    if(*Variable == VARIABLE_ID_SETUP)
	    {
			*Variable = FindVarFromITKQuestionId(UefiGetEqIDQuestionID(ifrPtr));
	    }
	}

	varInfo = VarGetVariableInfoIndex( *Variable );
	if ( varInfo == NULL )
		return NULL;

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
    	ifrPtr = NULL;
    }   

    // See if Other condition is Special condition
    if(ifrPtr == NULL)
    {
        if(ControlPtr > Conditional)
        {
            ifrPtr = (EFI_IFR_OP_HEADER *)Conditional;
            ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length); // To skip the SuppressIf or GrayOutIf
            // to skip current expression.
            while( (VOID*)ifrPtr < ControlPtr)
            {
            	if ( (ifrPtr != ControlPtr) && ( ifrPtr->OpCode != EFI_IFR_SUPPRESS_IF_OP ) && ( ifrPtr->OpCode != EFI_IFR_GRAYOUT_IF_OP ) )
                    ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length); // To skip the SuppressIf or GrayOutIf
                else
                    break;
            }

            Conditional = ifrPtr;
            if(ControlPtr > Conditional)
            {
                 CONTROL_INFO TempCtlInfo;
                 MemCopy(&TempCtlInfo, ControlInfo, sizeof (CONTROL_INFO));
                 TempCtlInfo.ControlConditionalPtr = Conditional;
                 ifrPtr = (EFI_IFR_OP_HEADER *)((UINTN)ifrPtr + ifrPtr->Length); // To skip the SuppressIf or GrayOutIf
            	 if ( ( ifrPtr->OpCode == EFI_IFR_VARSTORE_SELECT_OP ) )
                    VarGetVariableInfoId( ((EFI_IFR_VARSTORE_SELECT*)((char*)ifrPtr))->VarId, Variable );
                 ifrPtr = UefiGetSpecialEqIDIfrPtr(&TempCtlInfo, Variable, GuidInfo);
            }
            else
                ifrPtr = NULL;
        }
    }

	return ifrPtr;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetSpecialEqIDValue
//
// Description:	Function to get special eqID value
//
// Input:		CONTROL_INFO *ControlInfo, GUID_INFO **GuidInfo
//
// Output:		UINT16
//
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
// Procedure:	UefiSpecialGuidCallback
//
// Description:	Function to get special guid callback
//
// Input:		VOID * HiiHandle, UINT16 Key, EFI_GUID *pGUID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSpecialGuidCallback(VOID * HiiHandle, UINT16 Key, EFI_GUID *pGUID)
{
	EFI_FORM_CALLBACK_PROTOCOL *FormCallBack=NULL;
	EFI_IFR_FORM_SET *FormSet = NULL;
	EFI_IFR_DATA_ARRAY callbackData;
	EFI_STATUS	Status;

	MemSet( &callbackData, sizeof(callbackData), 0 );

	FormSet = HiiGetFormSetFromHandle( HiiHandle );

	if ( FormSet != NULL )
    {
	    Status = gBS->HandleProtocol ( (EFI_HANDLE)((UINTN) FormSet->CallbackHandle), &gEfiFormCallbackProtocolGuid,  &FormCallBack);

		if(!EFI_ERROR(Status))
		{
			(VOID*)callbackData.NvRamMap = (VOID*)pGUID;
			if ( ( FormCallBack != NULL ) && ( FormCallBack->Callback != NULL ) )
		    	FormCallBack->Callback( FormCallBack, Key, &callbackData, NULL );
		}
	}

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiSetEqIDValue
//
// Description:	Function to set EqID value
//
// Input:		VOID *IfrPtr, UINT16 Value
//
// Output:		VOID
//
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
// Procedure:	UefiIsOneOfControl
//
// Description:	Function to check for OneOf controls
//
// Input:		VOID *IfrPtr
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN UefiIsOneOfControl(VOID *IfrPtr)
{
  return (((EFI_IFR_OP_HEADER *)IfrPtr)->OpCode == EFI_IFR_ONE_OF_OP)? TRUE : FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiGetEqIDQuestionID
//
// Description:	Function to check EqID question ID
//
// Input:		VOID *IfrPtr
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetEqIDQuestionID(VOID *IfrPtr)
{
  EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)IfrPtr;
  UINT16 questionID = 0;

  switch(opHeader->OpCode)
  {
  case EFI_IFR_EQ_ID_ID_OP:
    break;
  case EFI_IFR_EQ_ID_LIST_OP:
    questionID = ((EFI_IFR_EQ_ID_LIST *)opHeader)->QuestionId;
    break;
  case EFI_IFR_EQ_ID_VAL_OP:
    questionID = ((EFI_IFR_EQ_ID_VAL *)opHeader)->QuestionId;
    break;
  default:
    break;
  }

  return questionID;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiSetEqIDQuestionID
//
// Description:	Function to set EqID question ID
//
// Input:		VOID *IfrPtr, UINT16 Value
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetEqIDQuestionID(VOID *IfrPtr, UINT16 Value)
{
  EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)IfrPtr;

  switch(opHeader->OpCode)
  {
  case EFI_IFR_EQ_ID_ID_OP:
    break;
  case EFI_IFR_EQ_ID_LIST_OP:
    ((EFI_IFR_EQ_ID_LIST *)opHeader)->QuestionId = Value;
    break;
  case EFI_IFR_EQ_ID_VAL_OP:
    ((EFI_IFR_EQ_ID_VAL *)opHeader)->QuestionId = Value;
    break;
  default:
    break;
  }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiCreateOneOfWithOptionsTemplate
//
// Description:	Function to create OneOf option template
//
// Input:		UINTN OptionCount, CONTROL_INFO *CtrlInfo
//
// Output:		VOID*
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID* UefiCreateOneOfWithOptionsTemplate(UINTN OptionCount, CONTROL_INFO *CtrlInfo)
{
  VOID *buffer = NULL;
  UINTN length = 0;
  UINTN offset = (UINTN)CtrlInfo->ControlPtr - (UINTN)CtrlInfo->ControlConditionalPtr;
  UINT32 size = (UINT32)((UINT32)offset + sizeof(EFI_IFR_ONE_OF) + sizeof(EFI_IFR_END_ONE_OF) + OptionCount * sizeof(EFI_IFR_ONE_OF_OPTION));

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
  return (buffer == NULL)?NULL:((UINT8*)buffer + offset);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiSetOneOfOption
//
// Description:	Function to set OneOf option
//
// Input:		VOID *IfrPtr, UINT64 Value, UINT32 Size, UINT8 Flag, UINT16 Option
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiSetOneOfOption(VOID *IfrPtr, UINT64 Value, UINT32 Size, UINT8 Flag, UINT16 Option)
{
  EFI_IFR_ONE_OF_OPTION *option = (EFI_IFR_ONE_OF_OPTION *)IfrPtr;
  UINT8 flag = 0;

  flag |= ((Flag & AMI_FLAG_DEFAULT) == AMI_FLAG_DEFAULT)? EFI_IFR_FLAG_DEFAULT : 0;
  flag |= ((Flag & AMI_FLAG_MANUFACTURING) == AMI_FLAG_MANUFACTURING)? EFI_IFR_FLAG_MANUFACTURING : 0;

  option->Value = (UINT16)Value;
  option->Option = Option;
  option->Flags = flag;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiUpdateControlVarOffset
//
// Description:	Function to update control variable offset
//
// Input:		VOID *IfrPtr, UINT16 Value
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiUpdateControlVarOffset(VOID *IfrPtr, UINT16 Value)
{
  EFI_IFR_OP_HEADER *opHeader = (EFI_IFR_OP_HEADER *)IfrPtr;

  switch(opHeader->OpCode)
  {
  case EFI_IFR_ONE_OF_OP:
    ((EFI_IFR_ONE_OF *)opHeader)->QuestionId = Value;
    break;
  default:
    break;
  }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiAddEndOp
//
// Description:	Function to add end op code
//
// Input:		VOID *IfrPtr
//
// Output:		VOID
//
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
// Procedure:	UefiGetQuestionID
//
// Description:	Function to get question ID
//
// Input:		CONTROL_INFO *control
//
// Output:		UINT16
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetQuestionID(CONTROL_INFO *control)
{
	return UefiGetQuestionOffset(control->ControlPtr);
}
#pragma warning( disable : 4204 )
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiCreateDynamicControlCondition
//
// Description:	Function to create dynamic control condition
//
// Input:		CONTROL_INFO *control,UINT16 VarId, UINT16 PrevControlQuestionID,UINT16 Value
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiCreateDynamicControlCondition(CONTROL_INFO *control,UINT16 VarId, UINT16 PrevControlQuestionID,UINT16 Value)
{
	struct SuppressCondition 
	{
		EFI_IFR_SUPPRESS Suppress;
		EFI_IFR_VARSTORE_SELECT	VarStroreSelect;
		EFI_IFR_EQ_ID_VAL	IDEqVal;
		EFI_IFR_END_IF	Endif;
	}Condition= { 	{EFI_IFR_SUPPRESS_IF_OP,sizeof(EFI_IFR_SUPPRESS),0},
					{EFI_IFR_VARSTORE_SELECT_OP,sizeof(EFI_IFR_VARSTORE_SELECT),0},
					{EFI_IFR_EQ_ID_VAL_OP,sizeof(EFI_IFR_EQ_ID_VAL),0,sizeof(UINT16),Value },
					{EFI_IFR_END_IF_OP,sizeof(EFI_IFR_END_IF)}};

	Condition.VarStroreSelect.VarId = VarId;
	Condition.IDEqVal.QuestionId = PrevControlQuestionID;
// Add the New code to update the ControlConditionalPtr
	MemCopy((void*)control->ControlConditionalPtr,(void*)&Condition,sizeof(Condition));
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
// Procedure:	ProcessActionQuestionConfiguration
//
// Description:	Function to process Action Control Configuration String.
//				UEFI Action control is a 2.1 control
//
// Input:		CONTROL_INFO *control
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessActionQuestionConfiguration(CONTROL_INFO *control)
{
  return EFI_SUCCESS;
}

//EIP 23354 : Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsPasswordEncodeEnabled
//
// Description:	Function to Password Encoding Status.
//
// Input:		VOID *PwDataPtr
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsPasswordEncodeEnabled ( CONTROL_INFO * controlInfo )
{
	EFI_IFR_PASSWORD *PwData = ((EFI_IFR_PASSWORD *)controlInfo->ControlPtr);
	return (PwData->Encoding == TRUE)? TRUE:FALSE;
}
//EIP 23354 : End
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetTime
//
// Description:	    Function to get time
//
// Parameter:	    CONTROL_INFO *control, EFI_TIME *Tm
//
// Return value:    STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiGetTime(CONTROL_INFO *control, EFI_TIME *Tm)
{
  return gRT->GetTime( Tm, NULL );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiSetTime
//
// Description:     Function to set time
//
// Parameter:	    CONTROL_INFO *control, EFI_TIME *Tm
//
// Return value:    STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiSetTime(CONTROL_INFO *control, EFI_TIME *Tm)
{
  return gRT->SetTime( Tm );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     UefiIsProceedWithPageChange
//
// Description:   	For UEFI 2.0 Just return EFI_SUCCESS;
//
// Parameter:     EFI_STATUS
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiIsProceedWithPageChange(EFI_STATUS Status)
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     UefiPreControlUpdate
//
// Description:   In UEFI 2.0 this is Dummy function.
//
// Parameter:     CONTROL_INFO * ControlData
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiPreControlUpdate(CONTROL_INFO *ControlData)
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiRefershQuestionValueNvRAM
//
// Description:	    Function Refresh the question
//
// Parameter:	    CONTROL_INFO *control
//
// Return value:    STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiRefershQuestionValueNvRAM(CONTROL_INFO *ControlData)
{
    return EFI_SUCCESS;
}

//EIP:56413 START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UefiupdateResetButtonDefault
//
// Description:	In UEFI 2.0 this is Dummy function.
//
// Input:	CONTROL_INFO ControlData, UINT16 DefaultId
//
// Output:	EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiupdateResetButtonDefault(CONTROL_INFO ControlData, UINT16 DefaultId)
{
	return EFI_SUCCESS;
}

//EIP:56413: START
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UefiGetResetButtonDefaultid
//
// Description:	  In UEFI 2.0 this is Dummy function.
//
// Parameter:	    VOID *IfrPtr
//
// Return value:    UINT16
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 UefiGetResetButtonDefaultid(VOID *IfrPtr)
{
return 0xffff;
}
//EIP:56413 END

//EIP: 55762 Start
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   UpdateDestiantionQuestion
//
// Description: Dummy function for 2.0
//
// Input:	UINT32 CurrPageID - Current page ID
//          UINT32 DestQuestionId - Destination question ID to set focus
//          UINT32 *FocusControlIndex - 
//
// Output:	EFI_STATUS status - EFI_SUCCESS is successful
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UpdateDestiantionQuestion (UINT32 CurrPageID, UINT32 DestQuestionId, UINT32 *FocusControlIndex)
{
	return EFI_UNSUPPORTED;
}
//EIP: 55762 End

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
	return NULL;
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
	return 0;
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
    return NULL;
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
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   UefiGetValidOptionSize
//
// Description: Function to get sizeof option.UEFI2.0 doesn't have EFI_IFR_TYPE support
//
// Input:	CONTROL_INFO *CtrlInfo - Pointer to the control info data
//          UINTN *Type - Returns EFI_IFR_TYPE_NUM_SIZE
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UefiGetValidOptionType(CONTROL_INFO *CtrlInfo, UINTN *Type, UINT32 *SizeOfData)
{
	*SizeOfData = sizeof(UINT8);//UEFI2.0 Supports UINT8 size of data for OrderList Control					
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CheckTimeFlags
//
// Description: Function to check the time flags.
//
// Input:	UINT8 Flags
//
// Output:	BOOLEAN
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckTimeFlags(UINT8 Flags)
{
	return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CheckDateFlags
//
// Description: Function to check the Date flags.
//
// Input:	UINT8 Flags
//
// Output:	BOOLEAN
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckDateFlags(UINT8 Flags)
{
	return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   ProcessPackNotification
//
// Description: Processes the IFR notification queue
//
// Input:	None
//
// Output:	EFI_STATUS status - EFI_ABORTED, By default
//                              EFI_SUCCESS, if successful
//                              EFI_ERROR, otherwise
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ProcessPackNotification (VOID)
{
	return EFI_ABORTED;
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

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    EvaluateControlDefault
//
// Description:
//
// Parameter:	    CONTROL_INFO *CtrlInfo
//
// Return value:  UINT64
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 EvaluateControlDefault (CONTROL_INFO *CtrlInfo, UINT64 *Defaults)
{
   return 0;
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

