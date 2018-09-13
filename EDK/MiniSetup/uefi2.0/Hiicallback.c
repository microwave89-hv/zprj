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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/Hiicallback.c $
//
// $Author: Premkumara $
//
// $Revision: 11 $
//
// $Date: 3/25/13 8:35a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/Hiicallback.c $
// 
// 11    3/25/13 8:35a Premkumara
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
// 10    10/18/12 6:00a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:39p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 9     1/09/12 1:53a Arunsb
// [TAG]  		EIP79952
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Add driver option displays select boot option as title
// [RootCause]  	Title problem
// [Solution]  	Title changes
// [Files]  		Faketokens.c, amitsestr.uni, addbootoption.c,
// uefi2.0\hiicallback.c and uefi21wapper.c
// 
// 8     12/02/11 1:51a Premkumara
// [TAG]  		EIP73226
// [Category]  	New Feature
// [Description]  	Extended support for password prompt
// [Files]  	FakeToken.c, Uefi21Wapper.c, AmiTSEStr.uni, PopupPassword.c,
// HiiCallback.c, Uefi20Wapper.c
// 
// 7     5/02/11 9:56a Arunsb
// [TAG]  		EIP58126
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System boot into setup page, it will popup "ME Update Info"
// [RootCause]  	Different actions allowed in 2.0 version also
// [Solution]  	Only update action is handled in 2.0 version
// [Files]  		uefi2.0\Hiicallback.c, uefi2.1\Hiicallback.c, Commonhelper.c
// 
// 6     3/21/11 12:52a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 7     2/19/10 8:20a Mallikarjunanv
// updated year in copyright message
// 
// 6     1/09/10 7:27a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     1/04/10 10:40a Mallikarjunanv
// EIPs 27161/29095 - Added support for reserved boot option names and
// added support not to create empty boot option names
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
// 2     5/07/09 10:36a Madhans
// Changes after Bin module
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
// Name:		HiiCallback.c
//
// Description:	This file contains code for Hii callback operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include EFI_PROTOCOL_DEFINITION(Hii)
#include EFI_PROTOCOL_DEFINITION(FormCallback)
extern EFI_HII_PROTOCOL	*gHiiProtocol;


static STRING_REF CallbackErrToken=0;

AMI_IFR_MSGBOX _PreviousMsgBox = { 0, 0, STRING_TOKEN(STR_LOAD_PREVIOUS), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_LOAD_PREVIOUS_MSG) };
AMI_IFR_MSGBOX _FailsafeMsgBox = { 0, 0, STRING_TOKEN(STR_LOAD_FAILSAFE), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_LOAD_FAILSAFE_MSG) };
AMI_IFR_MSGBOX _OptimalMsgBox = { 0, 0, STRING_TOKEN(STR_LOAD_OPTIMAL), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_LOAD_OPTIMAL_MSG) };
AMI_IFR_MSGBOX _SaveMsgBox = { 0, 0, STRING_TOKEN(STR_SAVE_VALUES), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_SAVE_VALUES_MSG) };
AMI_IFR_MSGBOX _SaveExitMsgBox = { 0, 0, STRING_TOKEN(STR_SAVE_EXIT), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_SAVE_EXIT_MSG) };
AMI_IFR_MSGBOX _ExitMsgBox = { 0, 0, STRING_TOKEN(STR_EXIT), (VOID*)(UINTN)INVALID_HANDLE,  STRING_TOKEN(STR_EXIT_MSG) };
AMI_IFR_MSGBOX _SaveResetMsgBox = { 0, 0, STRING_TOKEN(STR_SAVE_RESET), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_SAVE_RESET_MSG) };
AMI_IFR_MSGBOX _ResetMsgBox = { 0, 0, STRING_TOKEN(STR_RESET), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_RESET_MSG) };
AMI_IFR_MSGBOX _HelpMsgBox = { 0, 0, STRING_TOKEN(STR_GENERAL_HELP), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_GENERAL_HELP_MSG) };
AMI_IFR_MSGBOX _SaveUserMsgBox = { 0, 0, STRING_TOKEN(STR_SAVE_USER_DEFAULTS), (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_SAVE_VALUES_MSG) };
AMI_IFR_MSGBOX _LoadUserMsgBox = { 0, 0, STRING_TOKEN(STR_LOAD_USER_DEFAULTS),  (VOID*)(UINTN)INVALID_HANDLE, STRING_TOKEN(STR_LOAD_USER_MSG) };

AMI_IFR_MSGBOX _InvalidPasswordFailMsgBox = { 0, 0, STRING_TOKEN(STR_ERROR),(VOID*)(UINTN) INVALID_HANDLE, STRING_TOKEN(STR_ERROR_PSWD) };
AMI_IFR_MSGBOX _ClearPasswordMsgBox = { 0, 0, STRING_TOKEN(STR_WARNING),(VOID*) INVALID_HANDLE, STRING_TOKEN(STR_PSWD_CLR) };//EIP:73226 To Clear Old Password message
AMI_IFR_MSGBOX _ClearPasswordLabelMsgBox 	= { 0, 0, STRING_TOKEN(STR_WARNING),(VOID*) INVALID_HANDLE, STRING_TOKEN(STR_PSWD_CLR_LABEL) };//EIP:73226 To Clear Old Password message
AMI_IFR_MSGBOX _BootLaunchFailedMsgBox = { 0, 0, STRING_TOKEN(STR_WARNING), INVALID_HANDLE, STRING_TOKEN(STR_WARNING_NOT_FOUND) };

AMI_IFR_MSGBOX _gInvalidRangeFailMsgBox = { 0, 0, STRING_TOKEN(STR_ERROR), INVALID_HANDLE, STRING_TOKEN(STR_ERROR_INPUT) };

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
UINTN gBootLaunchFailedMsgBox = (UINTN)&_BootLaunchFailedMsgBox;
UINTN gInvalidPasswordFailMsgBox=(UINTN)&_InvalidPasswordFailMsgBox;
UINTN gClearPasswordMsgBox=(UINTN)&_ClearPasswordMsgBox;//EIP:73226 To display Clear Old Password message
UINTN gClearLabelPasswordMsgBox	=	(UINTN)&_ClearPasswordLabelMsgBox;
UINTN gInvalidRangeFailMsgBox=(UINTN)&_gInvalidRangeFailMsgBox;
UINTN gDelBootOptionReserved = (UINTN)&_gDelBootOptionReserved;
UINTN gAddBootOptionReserved = (UINTN)&_gAddBootOptionReserved;
UINTN gAddBootOptionEmpty = (UINTN)&_gAddBootOptionEmpty;
UINTN gAddDriverOptionEmpty = (UINTN)&_gAddDriverOptionEmpty;

static AMI_IFR_MSGBOX gCallbackErrorMsgBox = { 0, 0, STRING_TOKEN(STR_ERROR), (VOID*)(UINTN)INVALID_HANDLE, 0 };
EFI_IFR_FORM_SET *HiiGetFormSetFromHandle( /*EFI_HII_HANDLE*/VOID* handle );
EFI_IFR_FORM_SET *HiiGetFormSet( UINTN index );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CallFormCallBack
//
// Description: To call form callback
//
// Input:		CONTROL_INFO * pControlData,
//				UINT16 Key,
//				UINT8 Flags
//				UINTN Action
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CallFormCallBack(CONTROL_INFO * pControlData,UINT16 Key,UINT8 Flags,UINTN Action)//EIP-53480: Implementation of FormBrowser with actions support 
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_FORM_CALLBACK_PROTOCOL *FormCallBack=NULL;
	EFI_IFR_FORM_SET *FormSet = NULL;
	EFI_IFR_DATA_ARRAY * callbackData = NULL;
	EFI_HII_CALLBACK_PACKET *Packet =NULL ;
	UINTN	Size;

    if (AMI_CALLBACK_CONTROL_UPDATE != Action)
    {
        return EFI_UNSUPPORTED;
    }
	FormSet = HiiGetFormSetFromHandle( pControlData->ControlHandle );//HiiGetFormSet( 0 ); 

	callbackData = EfiLibAllocateZeroPool( 0x10000 );
	if(callbackData == NULL)
		return EFI_OUT_OF_RESOURCES;

	callbackData->NvRamMap = gVariableList[ pControlData->ControlVariable ].Buffer;
	

	if ( FormSet != NULL )
	{	
		callbackData->EntryCount = 1;
		((EFI_IFR_OP_HEADER*)&(callbackData->Data[0]))->OpCode = ((EFI_IFR_OP_HEADER *)(pControlData->ControlPtr))->OpCode;
		switch(((EFI_IFR_OP_HEADER*)&(callbackData->Data[0]))->OpCode)
		{	
		case EFI_IFR_STRING_OP:
			Size = ((EFI_IFR_STRING *)(pControlData->ControlPtr))->MaxSize * 2;
			((EFI_IFR_OP_HEADER*)&(callbackData->Data[0]))->Length = (UINT8)Size + 4;
			MemCopy(&(callbackData->Data[0].Data),(UINT8 *)callbackData->NvRamMap+((EFI_IFR_STRING *)(pControlData->ControlPtr))->QuestionId,Size);
			break;
		case EFI_IFR_NUMERIC_OP:
			Size = ((EFI_IFR_NUMERIC *)(pControlData->ControlPtr))->Width;
			((EFI_IFR_OP_HEADER*)&(callbackData->Data[0]))->Length =  (UINT8) Size + 4;
			MemCopy(&(callbackData->Data[0].Data),(UINT8 *)callbackData->NvRamMap+((EFI_IFR_NUMERIC *)(pControlData->ControlPtr))->QuestionId,Size);
			break;
		case EFI_IFR_REF_OP:
			((EFI_IFR_OP_HEADER*)&(callbackData->Data[0]))->Length = 6;
			MemCopy(&(callbackData->Data[0].Data),&((EFI_IFR_REF *)(pControlData->ControlPtr))->FormId,2);
			break;
        case EFI_IFR_ONE_OF_OP:
			Size = ((EFI_IFR_ONE_OF *)(pControlData->ControlPtr))->Width;
			((EFI_IFR_OP_HEADER*)&(callbackData->Data[0]))->Length =  (UINT8) Size + 4;
            MemCopy(&(callbackData->Data[0].Data),(UINT8 *)callbackData->NvRamMap+((EFI_IFR_ONE_OF *)(pControlData->ControlPtr))->QuestionId,Size);
            break;
		//EIP-16541 : for EFIMEBX checkbox call back handle.
	 	case EFI_IFR_CHECKBOX_OP:
			Size = ((EFI_IFR_CHECK_BOX *)(pControlData->ControlPtr))->Width;
			((EFI_IFR_OP_HEADER*)&(callbackData->Data[0]))->Length =  (UINT8) Size + 4;
            MemCopy(&(callbackData->Data[0].Data),(UINT8 *)callbackData->NvRamMap+((EFI_IFR_CHECK_BOX *)(pControlData->ControlPtr))->QuestionId,Size);
			break;
		default:
			callbackData->EntryCount=0;
		}

		Status = gBS->HandleProtocol ( (EFI_HANDLE)((UINTN) FormSet->CallbackHandle), &gEfiFormCallbackProtocolGuid, &FormCallBack);


		if ( ( FormCallBack != NULL ) && ( FormCallBack->Callback != NULL ) )
			Status = FormCallBack->Callback( FormCallBack, Key, callbackData, &Packet );

	
		if(EFI_ERROR(Status))
			if(Packet != NULL)
			{
				if(Packet->String!=NULL)
				{	EFI_STATUS Sts;
					Sts = gHiiProtocol->NewString(gHiiProtocol,NULL,(EFI_HII_HANDLE)(UINTN)gHiiHandle,&CallbackErrToken, Packet->String);
					gCallbackErrorMsgBox.Text=CallbackErrToken;
					if(!EFI_ERROR(Sts))
						CallbackShowMessageBox( (UINTN)&gCallbackErrorMsgBox, MSGBOX_TYPE_OK );
				}
				MemFreePointer( (VOID *)&Packet);
			}
	}
	
	MemFreePointer( (VOID *)&callbackData);
	return Status;
}

#if !TSE_USE_EDK_LIBRARY

#pragma pack(1)
typedef struct {
  UINT8   OpCode;           // Likely a string, numeric, or one-of
  UINT8   Length;           // Length of the EFI_IFR_DATA_ENTRY packet
  UINT16  Flags;            // Flags settings to determine what behavior is desired from the browser after the callback
  VOID    *Data;            // The data in the form based on the op-code type - this is not a pointer to the data, the data follows immediately
  // If the OpCode is a OneOf or Numeric type - Data is a UINT16 value
  // If the OpCode is a String type - Data is a CHAR16[x] type
  // If the OpCode is a Checkbox type - Data is a UINT8 value
  // If the OpCode is a NV Access type - Data is a EFI_IFR_NV_DATA structure
  //
} TSE_EFI_IFR_DATA_ENTRY;

typedef struct {
  VOID                *NvRamMap;  // If the flag of the op-code specified retrieval of a copy of the NVRAM map,
  // this is a pointer to a buffer copy
  //
  UINT32              EntryCount; // How many EFI_IFR_DATA_ENTRY entries
  TSE_EFI_IFR_DATA_ENTRY  Data[1];    // The in-line Data entries.
} TSE_EFI_IFR_DATA_ARRAY;

#pragma pack()
#else
#define TSE_EFI_IFR_DATA_ARRAY	EFI_IFR_DATA_ARRAY
#endif // TSE_USE_EDK_LIBRARY


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CallTextCallBack
//
// Description: Fuction to call text callback
//
// Input:		TEXT_DATA *text, ACTION_DATA *Data
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CallTextCallBack(TEXT_DATA *text, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if ( --(text->Interval) == 0 )
	{
		EFI_FORM_CALLBACK_PROTOCOL *FormCallBack=NULL;
		EFI_IFR_FORM_SET *FormSet = NULL;
		EFI_IFR_TEXT *ifrPtr;
			TSE_EFI_IFR_DATA_ARRAY callbackData;
		UINT16 DataArray[2];
		EFI_HII_CALLBACK_PACKET *Packet =NULL ;

		// initialize the interval
		text->Interval = (UINT8)(text->ControlData.ControlFlags.ControlRefresh);
		if ( text->Callback )
			text->Callback( text->Container, text, text->Cookie );

		MemSet( &callbackData, sizeof(callbackData), 0 );
		ifrPtr = (EFI_IFR_TEXT *)text->ControlData.ControlPtr;
		if ( ifrPtr->Flags & EFI_IFR_FLAG_NV_ACCESS )
			callbackData.NvRamMap = gVariableList[ text->ControlData.ControlVariable ].Buffer;

		callbackData.EntryCount = 1;
		// token number of string to update
		DataArray[0] = (UINT16)(UINTN)text->ControlData.ControlHandle;
		DataArray[1] = ifrPtr->TextTwo;
		callbackData.Data[0].Data = DataArray;

		FormSet = HiiGetFormSetFromHandle( text->ControlData.ControlHandle );//HiiGetFormSet( 0 ); 

		if ( FormSet != NULL )
		{
			Status = gBS->HandleProtocol ( (EFI_HANDLE)((UINTN) FormSet->CallbackHandle), &gEfiFormCallbackProtocolGuid,  &FormCallBack);

			if ( ( FormCallBack != NULL ) && ( FormCallBack->Callback != NULL ) )
					Status = FormCallBack->Callback( FormCallBack, ifrPtr->Key, (EFI_IFR_DATA_ARRAY*)&callbackData, &Packet/*NULL*/ );
				
		}

		return EFI_SUCCESS;
	}
	return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:		SpecialActionCallBack
//
// Description:		Callback for UEFI Action control. This is used only in UEFI 2.1
//
// Input:			CONTROL_INFO * ControlData, UINT16 Key
//
// Output:			EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SpecialActionCallBack(CONTROL_INFO * ControlData, UINT16 Key)
{
  return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:		UEFICallSetupFormCallBack
//
// Description:		Wrapper function for the Implementation of FormBrowser with actions support .This is used only in UEFI 2.1	
//
// Input:			UINTN Action
//
// Output:			VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UEFICallSetupFormCallBack(UINTN Action )
{//EIP-53480: Implementation of FormBrowser with actions support 

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
