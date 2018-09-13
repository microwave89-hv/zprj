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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/FormBrowser.c $
//
// $Author: Arunsb $
//
// $Revision: 12 $
//
// $Date: 10/18/12 6:00a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/FormBrowser.c $
// 
// 12    10/18/12 6:00a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:39p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 11    5/28/12 5:55a Premkumara
// [TAG]  		EIP75236
// [Category]  	Improvement
// [Description]  	Add the support to control the GOP dependency in TSE
// notification.
// [Files]  		AMITSE.sdl, CommonHelper.c, Notify.c, Minisetup.h,
// Minisetup.sdl, protocol.c, FormBrowser.c, FormBrowser2.c
// 
// 10    12/01/11 5:44a Rajashakerg
// [TAG]  		EIP74963 
// [Category]  	Improvement
// [Description]  	MAX_MSGBOX_WIDTH cannot be overridden
// [Files]  		AMITSE.sdl, CommonHelper.c, minisetup.h, legacy.c,
// MessageBox.c, MessageBox.h, FormBrowser.c
// 
// 9     11/21/11 5:53a Rajashakerg
// [TAG]  		EIP74591
// [Category]  	Improvement
// [Description]  	Make MainSetupLoop as board module hook
// [Files]  		AMITSE.sdl, CommonHelper.c, protocol.c, minisetup.h,
// FormBrowser.c, FormBrowser2.c
// 
// 8     11/08/11 4:56a Rajashakerg
// Lowered the TPL to Application level and invoked
// StyleUpdateVersionString() function to update the copy right string in
// the SendForm() function.
// 
// 7     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 9     8/13/10 10:14a Mallikarjunanv
// EIP-40056: Updated with the modified function call GetControlHeight
// 
// 8     2/26/10 6:56p Madhans
// To validate the Hii Handle
// 
// 6     2/19/10 8:20a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/27/10 12:59p Madhans
// // EIP 33804 : Issue iSCSI initiator name is not saved..
// 
// 4     1/09/10 7:31a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
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
// 1     4/28/09 11:08p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     3/31/09 4:14p Madhans
// UEFI Wrapper improvments.
// 
// 1     2/06/09 4:10p Madhans
// FormBorwser protocol support added.
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
// Name:		FormBrowser.c
//
// Description:	This file contains code for form browser
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

#include EFI_PROTOCOL_DEFINITION(Hii)
#include EFI_PROTOCOL_DEFINITION(FormCallback)
extern EFI_HII_PROTOCOL	*gHiiProtocol;

#if SETUP_FORM_BROWSER_SUPPORT
EFI_STATUS
MinisetupSendForm (
  IN EFI_FORM_BROWSER_PROTOCOL        * This,
  IN BOOLEAN                          UseDatabase,
  IN EFI_HII_HANDLE                   * Handle,
  IN UINTN                            HandleCount,
  IN EFI_IFR_PACKET                   * Packet,
  IN EFI_HANDLE                       CallbackHandle,
  IN UINT8                            *NvMapOverride,
  IN SCREEN_DESCRIPTOR                * ScreenDimensions,
  OUT BOOLEAN                         *ResetRequired
  );
  
EFI_STATUS
MinisetupCreatePopup (
  IN  UINTN                           NumberOfLines,
  IN  BOOLEAN                         HotKey,
  IN  UINTN                           MaximumStringSize,
  OUT CHAR16                          *StringBuffer,
  OUT EFI_INPUT_KEY                   * KeyValue,
  IN  CHAR16                          *String,
  ...
  );

EFI_FORM_BROWSER_PROTOCOL	gFormBrowserProtocol =
{
	MinisetupSendForm,
	MinisetupCreatePopup
};

VOID* *gSfHandles;
UINTN gSfHandleCount;
UINT8 *gSfNvMap;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MinisetupSendForm
//
// Description:	Function implements the SendForm interface of Formbrowser 
//					Protocol. UseDatabase=True is only supported. 
//
// Input:	Refer Spec. Packet,CallbackHandle, ScreenDimensions and ResetRequired
//					parameters ignored.
//
//					IN EFI_FORM_BROWSER_PROTOCOL        * This,		
//					IN BOOLEAN                          UseDatabase,
//					IN EFI_HII_HANDLE                   * Handle,
//					IN UINTN                            HandleCount,
//					IN EFI_IFR_PACKET                   * Packet,
//					IN EFI_HANDLE                       CallbackHandle,
//					IN UINT8                            *NvMapOverride,
//					IN SCREEN_DESCRIPTOR                * ScreenDimensions,
//					OUT BOOLEAN                         *ResetRequired
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MinisetupSendForm (
  IN EFI_FORM_BROWSER_PROTOCOL        * This,
  IN BOOLEAN                          UseDatabase,
  IN EFI_HII_HANDLE                   * Handles,
  IN UINTN                            HandleCount,
  IN EFI_IFR_PACKET                   * Packet,
  IN EFI_HANDLE                       CallbackHandle,
  IN UINT8                            *NvMapOverride,
  IN SCREEN_DESCRIPTOR                * ScreenDimensions,
  OUT BOOLEAN                         *ResetRequired
  )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN i;
	if(UseDatabase)
	{
		if( Handles == NULL || HandleCount == 0 )
		{
			return EFI_INVALID_PARAMETER;
		}

#ifndef STANDALONE_APPLICATION
        if ( ! gConsoleControl )
        {
            //All necessary protocols are not available yet.
            //We can still proceed if Uga Draw is the only protocol not available yet.
            ActivateApplication();

				if (!IsDelayLogoTillInputSupported())	//EIP-75236
					ActivateInput();
        }
#endif

		//Initialize send form global variables
		if(HandleCount)
		{
			gSfHandles = EfiLibAllocateZeroPool( HandleCount * sizeof(VOID*));
			gSfHandleCount = 0;
			for(i=0;i<HandleCount;i++)
			{
				UINT8 *FormSet = NULL;
				UINTN Length = 0;
				// Check if the Handle Has Forms to Display
				FormSet = _HiiGetForm( (VOID*)Handles[i], 0, &Length);
				if( FormSet != NULL )
				{
					gSfHandles[gSfHandleCount] = (VOID*)(UINTN)Handles[i];
					MemFreePointer( &FormSet );
					gSfHandleCount++;
				}
			}
			if( gSfHandleCount == 0 )
			{
				MemFreePointer( (VOID**)&gSfHandles );
				return EFI_NOT_FOUND;
			}
		}


		gSfNvMap = NvMapOverride;

        if(!gVariableList)
            VarLoadVariables( (VOID **)&gVariableList, NULL );

		// this *MUST* be run a EFI_TPL_APPLICATION
		gBS->RaiseTPL( EFI_TPL_HIGH_LEVEL );	// guarantees that RestoreTPL won't ASSERT
		gBS->RestoreTPL( EFI_TPL_APPLICATION );
	
		StyleUpdateVersionString();

		//Show forms
		Status = gST->ConIn->Reset( gST->ConIn, FALSE );
		Status = MainSetupLoopHook();//EIP74591 : Modified MainSetupLoop as board module hook

		//Reset send form global variables
		MemFreePointer( (VOID**)&gSfHandles );
		gSfHandles = NULL;

		gSfHandleCount = 0;
		gSfNvMap = NULL;

		return Status;
	}
	else
	{
		return EFI_UNSUPPORTED;
	}
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MinisetupCreatePopup
//
// Description:	Function implements the CreatePopup interface of Formbrowser 
//					Protocol. 
//
// Input:	
//					IN  UINTN                           NumberOfLines,
//					IN  BOOLEAN                         HotKey,
//					IN  UINTN                           MaximumStringSize,
//					OUT CHAR16                          *StringBuffer,
//					OUT EFI_INPUT_KEY                   * KeyValue,
//					IN  CHAR16                          *String,
//
// Output:			Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
MinisetupCreatePopup (
  IN  UINTN                           NumberOfLines,
  IN  BOOLEAN                         HotKey,
  IN  UINTN                           MaximumStringSize,
  OUT CHAR16                          *StringBuffer,
  OUT EFI_INPUT_KEY                   * KeyValue,
  IN  CHAR16                          *String,
  ...
  )
{
    VA_LIST Marker;
    MEMO_DATA **memo;
    POPUP_DATA *popup = NULL;
    CONTROL_INFO dummy;
    AMI_IFR_MSGBOX MsgData;
    VOID	*ScreenBuf;
    UINT16 *textToken;
	UINT16 Height =0 ;
	EFI_IFR_SUBTITLE *buff;
	CONTROL_INFO *MemoCtrlData;
    EFI_STATUS Status;
    UINTN i;
    CONTROL_ACTION MappedAction = ControlActionUnknown;
    UINTN StrIndex = 0;
    EFI_INPUT_KEY Key;
    CHAR16 *EditString;

    if (HotKey)
    {
        if (KeyValue == NULL)
        {
        return EFI_INVALID_PARAMETER;
        }
    }
    else
    {
        if (StringBuffer == NULL)
        {
            return EFI_INVALID_PARAMETER;
        }
    }

    //Put strings in Hii
    VA_START (Marker, String);
    textToken = EfiLibAllocateZeroPool(NumberOfLines*sizeof(UINT16));
    i=0;
    textToken[i] = HiiChangeString(gHiiHandle, textToken[i], String);
    i++;
    for(;i<NumberOfLines; i++)
    {
        textToken[i] = HiiChangeString(gHiiHandle, textToken[i], VA_ARG (Marker, CHAR16 *));
    }

	//Create
    gPopup.Create(&popup);
	
    //Init
    MemSet( &dummy, sizeof(dummy), 0 );
	dummy.ControlHandle = INVALID_HANDLE;

	MsgData.Opcode = 0;
	MsgData.Length = 0;
	MsgData.Title =  0;
	MsgData.TextHandle = INVALID_HANDLE; 
	MsgData.Text = 0;

	dummy.ControlPtr = (VOID*) (&MsgData);
	dummy.ControlFlags.ControlVisible = TRUE;

    Status = gPopup.Initialize( popup, &dummy );
	if (EFI_ERROR(Status))
		return Status;

 // To fix the Color of the popup Box.
	SetControlColorsHook( NULL, NULL, NULL , NULL, NULL , NULL, NULL ,
	                      NULL , NULL,  NULL,NULL ,
						  NULL,NULL ,&(popup->FGColor),&(popup->BGColor)  );

	popup->Container = NULL;
	popup->Border =TRUE;
    popup->Width = GetMsgboxWidth(); //EIP74963 : MAX_MSGBOX_WIDTH macro changed as token and handled from binary
    popup->Height = 4;

    MemoCtrlData = EfiLibAllocateZeroPool(NumberOfLines*sizeof(CONTROL_INFO));
    memo = EfiLibAllocateZeroPool(NumberOfLines*sizeof(MEMO_DATA *));
    for(i=0;i<NumberOfLines;i++)
    {
        gMemo.Create(&(memo[i]));
        buff =  EfiLibAllocateZeroPool(sizeof(EFI_IFR_SUBTITLE));
	    buff->Header.OpCode = EFI_IFR_SUBTITLE_OP ;
	    buff->Header.Length = sizeof(EFI_IFR_SUBTITLE) ;
	    buff->SubTitle= textToken[i];
        MemoCtrlData[i].ControlPtr = (VOID*)buff;
	    MemoCtrlData[i].ControlHandle = INVALID_HANDLE;
	    MemoCtrlData[i].ControlFlags.ControlVisible = TRUE;
	    gMemo.Initialize(memo[i],(VOID *)&(MemoCtrlData[i]));
	    memo[i]->Width = popup->Width - 2;
//EIP:40056 - START
//Updated with the modified function
	    // gMemo.GetTextHeight( memo[i], &Height );
	    gMemo.GetControlHeight( memo[i], NULL, &Height );
//EIP:40056 - END
	    popup->Height = popup->Height + Height;
        gMemo.SetAttributes(memo[i],popup->FGColor ,popup->BGColor);
        gMemo.SetDimensions( memo[i], popup->Width-2 , Height );
        gMemo.SetJustify( memo[i], JUSTIFY_CENTER );
    }
	

    //Draw
    ScreenBuf = SaveScreen();
    Status = gPopup.Draw( popup );
	if(EFI_ERROR(Status))
		return Status;
    Height = popup->Top + 2;
    for(i=0;i<NumberOfLines;i++)
    {
        gMemo.SetPosition( memo[i], popup->Left + 1, Height);
	    gMemo.Draw( memo[i] );
        Height = Height + memo[i]->Height;
    }
    
	FlushLines( popup->Top, popup->Top + popup->Height );
	DoRealFlushLines();

    //Getkeys
    gST->ConIn->Reset( gST->ConIn, FALSE );
    EditString = EfiLibAllocateZeroPool(MaximumStringSize);
    while(
        (MappedAction != ControlActionSelect) &&
        (MappedAction != ControlActionAbort)
        )
    {
        if(EFI_SUCCESS == gST->ConIn->ReadKeyStroke( gST->ConIn, &Key ))
        {
			AMI_EFI_KEY_DATA AmiKey;
			AmiKey.Key = Key;
            MappedAction = MapControlKeysHook(AmiKey);
            
            if(HotKey)
            {
                *KeyValue = Key;
                break;
            }
            else
            {
                if((ControlActionAlpha == MappedAction) || (ControlActionNumeric == MappedAction))
                {
                    if(StrIndex < (MaximumStringSize/2))
                    {
                        EditString[StrIndex] = Key.UnicodeChar;
                        StrIndex++;
                    }
                }
            }
        }
    }

    if(MappedAction == ControlActionSelect && !HotKey)
    {
        MemCopy(StringBuffer, EditString, MaximumStringSize);
    }

    //Destroy
    Status = gPopup.Destroy( popup, TRUE );
	MemFreePointer( (VOID **)&(textToken) );
    for(i=0;i<NumberOfLines;i++)
    {
        MemFreePointer( (VOID **)&(memo[i]->ControlData.ControlPtr) );
	    Status = gMemo.Destroy( memo[i], TRUE );
    }
    MemFreePointer( (VOID **)&(MemoCtrlData) );
    MemFreePointer( (VOID **)&(memo) );
    MemFreePointer( (VOID **)&(EditString) );

  	RestoreScreen( ScreenBuf );

    //Return
	return EFI_SUCCESS;
}
#endif //#if SETUP_FORM_BROWSER_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InstallFormBrowserProtocol
//
// Description:	Installs the Formbrowser Protocol in the given handle if 
//				SETUP_FORM_BROWSER_SUPPORT is on.
//
// Input:		IN  EFI_HANDLE Handle
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 	InstallFormBrowserProtocol(EFI_HANDLE Handle)
{
#if SETUP_FORM_BROWSER_SUPPORT
	EFI_STATUS Status;
	Status = gBS->InstallMultipleProtocolInterfaces(
			&Handle,
			&gEfiFormBrowserProtocolGuid, &gFormBrowserProtocol,
			NULL
			);
	return Status;
#else
	return EFI_SUCCESS;
#endif //#if SETUP_FORM_BROWSER_SUPPORT
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	UnInstallFormBrowserProtocol
//
// Description:	Uninstalls the Formbrowser Protocol in the given handle if 
//					SETUP_FORM_BROWSER_SUPPORT is on.
//
// Input:		IN  EFI_HANDLE Handle
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UnInstallFormBrowserProtocol(EFI_HANDLE Handle)
{
#if SETUP_FORM_BROWSER_SUPPORT
	gBS->UninstallMultipleProtocolInterfaces(
			&Handle,
			&gEfiFormBrowserProtocolGuid, &gFormBrowserProtocol,
			NULL
			);
#endif //#if SETUP_FORM_BROWSER_SUPPORT
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FormBrowserHandleValid
//
// Description:	return True Browser is showing forms from SendForm interface.
//
// Input:		none
//
// Output:		BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN FormBrowserHandleValid(VOID)
{
#if SETUP_FORM_BROWSER_SUPPORT
	if(gSfHandles)
		return TRUE;
#endif
	return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FormBrowserLocateSetupHandles
//
// Description:	return Handles and count that is passed to SendForm interface.
//
// Input:		OUT handleBuffer and count
//
// Output:		Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FormBrowserLocateSetupHandles(VOID*	**handleBuffer,UINT16 *count)
{
#if SETUP_FORM_BROWSER_SUPPORT
	if(gSfHandles)
	{
		*handleBuffer = (VOID**)gSfHandles;
		*count = (UINT16)gSfHandleCount;
		return EFI_SUCCESS;
	}
	else
		return EFI_NOT_FOUND;
#else
	return EFI_UNSUPPORTED;
#endif
}

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
