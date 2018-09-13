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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/HiiCallback.c $
//
// $Author: Arunsb $
//
// $Revision: 41 $
//
// $Date: 7/03/13 11:25a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/HiiCallback.c $
// 
// 41    7/03/13 11:25a Arunsb
// Validated gApplicationData to NULL. In some case gApplicationData is
// NULL then it leading to hang.
// 
// 40    5/22/13 11:02a Arunsb
// [TAG]  		EIP123047
// Password retrieved only for its string not for entire size. So password
// not validated properly, changed upto entire size.
// 
// 39    4/17/13 2:37p Arunsb
// [TAG]  		EIP109812, 107774
// [Category]  	Improvement
// [Description]  	Provide support for EFI_IFR_TYPE_REF and EFI_IFR_REF5
// [Files]  		Hii.c, HiiCallback.c, Parse.c and TseUefiHii.h
// 
// 38    4/16/13 11:44a Arunsb
// EFI_IFR_TYPE_UNDEFINED declaration moved to tseuefihii.h
// 
// 37    3/12/13 11:35p Rajashakerg
// [TAG]  		EIP105167 
// [Category]  	Improvement
// [Description]  	Making the specify setup items departing from F2/F3
// effect.
// [Files]  		AMITSE.sdl, CommonHelper.c, callback.c, minisetupext.h,
// PopupPassword.c, SubMenu.c, HiiCallback.c
// 
// 36    3/12/13 7:05a Rajashakerg
// [TAG]  		EIP105167 
// [Category]  	Improvement
// [Description]  	Making the specify setup items departing from F2/F3
// effect.
// [Files]  		AMITSE.sdl, CommonHelper.c, callback.c, minisetupext.h,
// PopupPassword.c, SubMenu.c, HiiCallback.c
// 
// 35    3/08/13 1:39a Rajashakerg
// [TAG]  		EIP113085
// [Category]  	Improvement
// [Description]  	 Modify callback function behavior to match UEFI SPEC.
// [Files]  		HiiCallback.c, PopupPassword.c, SubMenu.c
// 
// 34    10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 32    9/17/12 6:22a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 30    9/10/12 10:38a Arunsb
// [TAG]  		EIP90372
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Setup browser handling of
// EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD
// [RootCause]  	For discard action current value is saved
// [Solution]  	Introduced a global variable which will set for discard
// action for that current value will not be saved
// [Files]  		HiiCallback.c and Uefi21Wapper.c
// 
// 29    5/29/12 4:46a Arunsb
// [TAG]  		EIP91109
// [Category]  	Improvement
// [Description]  	Sync the Aptio IV source for AptioV
// 
// 28    5/26/12 5:21a Arunsb
// [TAG]  		EIP90895
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Setup hangs when retrieve callback produces
// add/remove/update forms
// [RootCause]  	Callback with retrieve action produces add/remove/update
// form
// [Solution]  	If retrieve callback produces add/remove/update form then
// TSE will print debug messages and assert.
// [Files]  		HiiNotificationHandler.c, HiiCallback.c and FormBrowser2.c
// 
// 27    5/09/12 1:32p Arunsb
// [TAG]  		EIP86885
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	ISCSI attempt order is not changing on setup
// [RootCause]  	Orderlist maxcontainers value and ordered list size not
// handled properly
// [Solution]  	Orderlist maxcontainers value is 0xff, but TSE changed the
// cache value for only the added attempts(dynamic orderlist creation)
// remaining buffer left as is, Now the remaining buffers made as 0.
// [Files]  		HiiCallback.c and ordlistbox.c
// 
// 26    4/19/12 6:09p Blaines
// [TAG] - EIP 88031 
// [Category]- Defect
// [Synopsis]- Hii Callbacks may enter infinite loop on
// BROWSER_ACTION_RETRIEVE
// [Solution] - Only allow EFI_BROWSER_ACTION_RETRIEVE action for all
// Interactive controls from MiniSetupEntry.
// [Files] - Submenu.c, HiiCallback.c,
// 
// 25    4/05/12 12:49p Arunsb
// [TAG]  		EIP83252
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hangs with onboard SAS Option ROM
// [RootCause]  	ProcessPackNotification not invoked properly
// [Solution]  	gEnableDrvNotification flag handled properly to invoke
// ProcessPackNotification
// [Files]  		uefi2.1\hiicallback.c and uefi2.1\uefi21wapper.c
// 
// 24    2/02/12 3:00a Premkumara
// [TAG]  		EIP75066 
// [Category]  	Improvement
// [Description]  	Support loading defaults for Ordelist controls
// [Files]  		Ordlistbox.c, Uefi21Wapper.c, CtrlCond.c, HiiCallback.c,
// Parse.c, Uefi20Wapper.c, TseUefihiil.h
// 
// 23    12/16/11 2:01a Arunsb
// [TAG]  		EIP78100
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	TSE 2.15 can't enter Setup menu
// [RootCause]  	Tried to access the NULL controldata 
// [Solution]  	Controldata validated for NULL
// [Files]  		Hiicallback.c and uefihpktool.exe
// 
// 22    12/08/11 4:33p Arunsb
// [TAG]  		EIP75536
// [Category]  	Improvement
// [Description]  	String handling inside the callbacks in Minisetup
// [Files]  		Hiicallback.c and hiistring21.c
// 
// 21    12/08/11 12:29a Arunsb
// ProcessBrowserActionRequestHook declaration changed
// 
// 20    12/07/11 3:02p Arunsb
// [TAG]  		EIP75588
// [Category]  	New Feature
// [Description]  	Support for queuing UpdatePack notifications
// [Files]  		frame.c, page.c, formbrowser2.c, hii.c, hiicallback.c,
// hiinotificationhandler.c, tseuefihii.h and uefi21wapper.c
// 
// 19    12/07/11 2:22p Rajashakerg
// [TAG]  		EIP75572 
// [Category]  	Improvement
// [Description]  	Callback for Date and Time doesn't pass the new value
// [Files]  		HiiCallback.c
// 
// 18    12/07/11 9:31a Rajashakerg
// [TAG]  		EIP77108 
// [Category]  	Improvement
// [Description]  	Make ProcessBrowserActionRequest as board module hook
// [Files]  		AMITSE.sdl, CommonHelper.c, HiiCallback.c
// 
// 17    12/07/11 8:14a Rajashakerg
// [TAG]  		EIP75118 
// [Category]  	Improvement
// [Description]  	xtractConfig() fail since BrowserCallback() cannot find
// the variable to process
// [Files]  		FormBrowser2.c, FormBrowser2.h, HiiCallback.c,
// Uefi21Wapper.c, PopupSel.c
// 
// 16    12/01/11 12:38p Premkumara
// [TAG]  		EIP75536
// [Category]  	Improvement
// [Description]  	1.String handling inside the callbacks in
// Minisetup.Adding Null termination for String and Password control type.
// 2.Iterate to check the available language and add/change the string
// only for the passed language.
// [Files]  		HiiCallback.c, hiistring21.c
// 
// 15    12/01/11 11:22a Rajashakerg
// UefiGetValidOptionSize() function  declared  to resolve build error.
// 
// 14    12/01/11 7:44a Rajashakerg
// [TAG]  		EIP75464 
// [Category]  	Improvement
// [Description]  	Improper handling of action controls
// [Files]  		SubMenu.c, UefiAction.c, HiiCallback.c, Uefi21Wapper.c
// 
// 13    11/28/11 5:10a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 12    11/14/11 2:43p Blaines
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
// 11    7/19/11 2:33p Arunsb
// Suppressing the callback for AMI_CALLBACK_FORM_OPEN action
// 
// 10    4/22/11 5:31p Arunsb
// [TAG]  		EIP58009
// [Category]  	Bug Fix
// [Severity]  	Normal
// [RootCause]  	Certain controls not compatible with UEFI 2.3 version
// [Solution]  	The UEFI 2.3 features will be added only if core supports
// it
// [Files]  		HiiCallback.c and commonhelper.c
// 
// 9     3/21/11 12:58a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 8     3/09/11 7:26p Madhans
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
// 7     12/02/10 6:09p Madhans
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
// 6     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 5     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 4     2/19/10 8:50p Madhans
// 
// 4     11/30/09 1:10p Presannar
// Modified ConfigAccessCallback EFI_BROWSER_ACTION from pass by reference
// to pass by value
// 
// 3     11/19/09 5:31p Presannar
// Updated TSE include file name to not clash with CORE file
// 
// 2     8/11/09 2:49p Presannar
// Added code to FormCallBack by calling FixSetupData after
// ConfigAccess->Callback to handle dynamic removal of IFR data
// Added code to handle callback for EFI_IFR_REF_OP opcode
// 
// 1     7/24/09 6:54p Presannar
// 
// 5     4/24/09 7:54p Presannar
// TSE 2.0 UEFI 2.1 Code Complete
// 
// 4     4/14/09 12:41p Presannar
// Added Fn SpecialActionCallBack
// Modified fn signature FormCallBack
// 
// 3     3/31/09 4:15p Madhans
// UEFI Wrapper improvments.
//
// 2     1/29/09 6:08p Presannar
// Added Function Header comments
// Modified implementation for fn CallFormCallBack and CallTextCallBack
//
// 1     1/09/09 2:38p Presannar
// UEFI 2.1 Hii Related Code - Initial Drop
//
// 1     12/29/08 4:45p Presannar
// Initial draft Form Callback handler
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:          HiiCallback.c
//
// Description:  Contains Hii related Functions
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
#include "Minisetup.h"
#include "FormBrowser2.h"
#include "TseUefiHii.h"
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
static UINT8 *gPrevControlValue = NULL;
static CHAR16 *gCurPswdString = NULL;
extern UINT16 gOrderlistcount;
extern BOOLEAN gEnableDrvNotification; //TRUE if allow notification function to process action, FALSE to ignore the notification
extern BOOLEAN gBrowserCallbackEnabled; //Allow external drivers to change cache only if it's TRUE; ignore browser callback otherwise
extern EFI_BROWSER_ACTION gBrowserCallbackAction ; //Contains the BrowserCallback action when a callback is in progress.
EFI_STATUS ProcessBrowserActionRequestHook(EFI_BROWSER_ACTION_REQUEST actionReq);//EIP77108 : Modified  ProcessBrowserActionRequest as board module hook
//----------------------------------------------------------------------------

UINT32 GetUefiSpecVersion (VOID);
VOID UefiGetValidOptionSize(CONTROL_INFO *CtrlInfo, UINT32 *SizeOfData);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     FormCallBack
//
// Description:   
//
// Parameter:     EFI_HII_HANDLE Handle, EFI_QUESTION_ID QuestionID,
//		  UINT8 Type, EFI_IFR_TYPE_VALUE *Value
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FormCallBack(EFI_HII_HANDLE Handle, EFI_QUESTION_ID QuestionID, UINT8 Type, EFI_IFR_TYPE_VALUE *Value, EFI_BROWSER_ACTION action)
{
  EFI_HANDLE DriverHandle;
  EFI_GUID EfiHiiConfigAccessProtocolGuid = EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID;
  EFI_HII_CONFIG_ACCESS_PROTOCOL  *ConfigAccess;
  EFI_BROWSER_ACTION_REQUEST actionReq = EFI_BROWSER_ACTION_REQUEST_NONE;
  //EFI_BROWSER_ACTION action = EFI_BROWSER_ACTION_CHANGED; //EFI_BROWSER_ACTION_CHANGING;
  EFI_STATUS status = EFI_SUCCESS;
  BOOLEAN PreservegEnableDrvNotification = FALSE;
	
  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Entering FormCallBack()\n\n" );
  SETUP_DEBUG_UEFI_CALLBACK (  "Handle = 0x%x \nQuestionID = %d \nType = 0x%x \nValue = 0x%x \naction = 0x%x\n\n" , Handle, QuestionID, Type, *Value, action );   

  //
  //  Get Driver Handle that installed this Hii Form
  //
  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Getting Driver Handle\n" );   
  status = gHiiDatabase->GetPackageListHandle(gHiiDatabase, Handle, &DriverHandle);
  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Getting Driver Handle returned, status = 0x%x \n\n", status );   
  if(EFI_ERROR(status))
  {
    goto DONE;
  }

  //
  //  Get ConfigAccess protocol handle
  //
  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Getting ConfigAccess protocol handle\n" );    
  status = gBS->HandleProtocol( DriverHandle, &EfiHiiConfigAccessProtocolGuid , &ConfigAccess );
  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Getting ConfigAccess protocol handle returned,  status = 0x%x \n\n" , status );    
  if(EFI_ERROR(status))
  {
    goto DONE;
  }

  //
  //  Invoke Config Access Protocol
  //
  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] ConfigAccess->Callback()\n\n" );

  PreservegEnableDrvNotification = gEnableDrvNotification;
  gEnableDrvNotification = TRUE; //Set to enable notification processing
  gBrowserCallbackEnabled = TRUE;
  gBrowserCallbackAction = action ; //Save the current BrowserCallback action
  status = ConfigAccess->Callback(ConfigAccess, action, QuestionID, Type, Value, &actionReq);
  gBrowserCallbackAction = 0 ;		//Clear the current BrowserCallback action
  gBrowserCallbackEnabled = FALSE;
  if (!PreservegEnableDrvNotification) // If gEnableDrvNotification is already True Don't touch it
	  gEnableDrvNotification = FALSE; //Reset to disable notification processing

  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] ConfigAccess->Callback returned,   status = 0x%x \n\n" , status );   
  if(EFI_ERROR(status))
  {
    goto DONE;
  }

  // Clean up PAGE_INFO struct with Handle set to 0xFFFF
  status = FixSetupData();
  if(EFI_ERROR(status))
  {
  }

  if(actionReq)
  {
    SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] ProcessBrowserActionRequestHook()\n" );
    status = ProcessBrowserActionRequestHook(actionReq);//EIP77108 : Modified  ProcessBrowserActionRequest as board module hook
    SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] ProcessBrowserActionRequestHook returned,   status = 0x%x \n\n" , status );
  }

DONE:
  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Exiting FormCallBack()\n\n" );
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     CallFormCallBack
//
// Description:   
//
// Parameter:     CONTROL_INFO * ControlData, UINT16 Key , UINT8 Flags, UINTN Action
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN BrowserActionDiscard = FALSE;
EFI_STATUS CallFormCallBack(CONTROL_INFO * ControlData, UINT16 Key ,UINT8 Flags, UINTN Action)//EIP-53480: Implementation of FormBrowser with actions support 
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_IFR_TYPE_VALUE value;
  EFI_IFR_OP_HEADER *OpHeader = (EFI_IFR_OP_HEADER *)ControlData->ControlPtr;
  EFI_BROWSER_ACTION action ;
  EFI_HII_HANDLE hiiHandle;
  UINT16 ControlType = 0;
  UINT8	type = 0;
  UINT16 tok = 0;
  UINTN size = 0;
  UINT32 offset = 0;
  VOID *ctrlValue = NULL, *FullCtrlValue = NULL;
  UINT32 UefiSpecVer = 0;
  UINT32 tempVariable = 0;     
  MemSet( &value, sizeof(value), 0 );

  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Entering CallFormCallBack()\n\n" ); 

  UefiSpecVer = GetUefiSpecVersion ();
  if (UefiSpecVer <= 0x2000A)     //If spec version is 2.0 suppressing other actions
  {
    if (AMI_CALLBACK_CONTROL_UPDATE != Action)
    {
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Exiting CallFormCallBack()\n\n" );
        status = EFI_UNSUPPORTED;
		goto DONE;
    }
  }
  else if (UefiSpecVer >= 0x2001E)   //If spec version is greater than 2.30 then suppressing other actions
  {
    if (
        (AMI_CALLBACK_CONTROL_UPDATE != Action) &&  
        (AMI_CALLBACK_RETRIEVE != Action) &&
        (AMI_CALLBACK_FORM_OPEN != Action) &&
        (AMI_CALLBACK_FORM_CLOSE != Action) &&
        (AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING != Action)&&
  		  (AMI_CALLBACK_FORM_DEFAULT_STANDARD != Action)	)//EIP 105167 : Making the specify setup items departing from F2/F3 effect.
    {
       switch(Action)
	    {
	        case AMI_CALLBACK_FORM_OPEN:
                SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_FORM_OPEN Unsupported\n\n" );         
                break;
            case AMI_CALLBACK_FORM_CLOSE:
                SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_FORM_CLOSE Unsupported\n\n" );
                break;
            case AMI_CALLBACK_RETRIEVE:
                SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_RETRIEVE Unsupported\n\n" );
                break;
            case AMI_CALLBACK_CONTROL_UPDATE:            
                SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_CHANGING Unsupported\n\n" );
                break;
				case AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING : 
					SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING Unsupported\n\n" );
               break;
				case AMI_CALLBACK_FORM_DEFAULT_STANDARD : 
					SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] AMI_CALLBACK_FORM_DEFAULT_STANDARD Unsupported\n\n" );//EIP 105167 : Making the specify setup items departing from F2/F3 effect.
               break;
    	    default:
    	        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Callback Action Unsupported\n\n" ); 
    	    break;
        }
        
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Exiting CallFormCallBack()\n\n" );
        status = EFI_UNSUPPORTED;
		goto DONE;
    }
  }        
  action = UefiGetActionWapper(Action);
    
  if(ControlData->ControlHandle == INVALID_HANDLE)
  {  
	SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] INVALID_HANDLE\n\n" ); 
    SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Exiting CallFormCallBack()\n\n" );
   	goto DONE;
  }  
  
  hiiHandle = ControlData->ControlHandle;
  ControlType = ControlData->ControlType;
  tempVariable = ControlData->ControlVariable;

  if(AMI_CALLBACK_FORM_OPEN != Action)
  {
	  if(OpHeader->OpCode != EFI_IFR_ACTION_OP && OpHeader->OpCode != EFI_IFR_REF_OP)
	  {
	    offset = UefiGetQuestionOffset(ControlData->ControlPtr);
	//If the control is Ordered list then we are calculating the actual size
		if(ControlData->ControlType == CONTROL_TYPE_ORDERED_LIST)
		{
			UINTN Type=0;
			UefiGetValidOptionType( ControlData, &Type, (UINT32 *)&size);
			size = gOrderlistcount * size;
		}
		else
			size = UefiGetWidth(ControlData->ControlPtr);

		if ((EFI_IFR_PASSWORD_OP == OpHeader->OpCode) || (EFI_IFR_STRING_OP == OpHeader->OpCode))
		{
			ctrlValue = EfiLibAllocateZeroPool (size + sizeof (CHAR16));		//If max character reached then the string should have NULL at last
		}
		else
		{
			ctrlValue = EfiLibAllocateZeroPool (size);
		}
	    if(ctrlValue == NULL)
	    {
	      status = EFI_OUT_OF_RESOURCES;
	      goto DONE;
	    }
	
		if((EFI_IFR_PASSWORD_OP == OpHeader->OpCode)&&(NULL != gCurPswdString) )
		{
			MemCopy( ctrlValue, gCurPswdString, size);
		}
		else
	    status = VarGetValue(ControlData->ControlVariable, offset, size, ctrlValue );

	    if(EFI_ERROR(status))
	    {
	      goto DONE;
	    }
		//Checking the Previous value presence and updateing the cache with the previous value
		if(NULL != gPrevControlValue)
			status = VarSetValue(ControlData->ControlVariable, offset, size, gPrevControlValue );
		if(EFI_ERROR(status))
	    {
	      goto DONE;
	    }
	  }
	
	  switch(OpHeader->OpCode)
	  {
	  case EFI_IFR_NUMERIC_OP:
	    type = ((EFI_IFR_NUMERIC *)(ControlData->ControlPtr))->Flags & EFI_IFR_NUMERIC_SIZE;
	    MemCopy(&(value), ctrlValue, size);
	    break;
	  case EFI_IFR_REF_OP:
        //type = EFI_IFR_TYPE_UNDEFINED; //REF_OP uses type EFI_IFR_TYPE_UNDEFINED
		  //EIP109812, 107774
        if ((GetUefiSpecVersion ()) >= 0x2001E)			//If spec version is greater than or equals 2.3 then type will be buffer
        {
            type = EFI_IFR_TYPE_REF;
        }
        else
        {
            type = EFI_IFR_TYPE_UNDEFINED;
        }	
	    break;
	  case EFI_IFR_ONE_OF_OP:
	    type = ((EFI_IFR_ONE_OF *)(ControlData->ControlPtr))->Flags & EFI_IFR_NUMERIC_SIZE;
	    MemCopy(&(value), ctrlValue, size);
	    break;
	  case EFI_IFR_ORDERED_LIST_OP:
		 if ((GetUefiSpecVersion ()) >= 0x2001E)			//If spec version is greater than or equals 2.3 then type will be buffer
		 {
	    	type = EFI_IFR_TYPE_BUFFER;
		 }
		 else
		 {
			type = EFI_IFR_TYPE_OTHER;
		 }		
	    MemCopy(&(value), ctrlValue, size);
	    break;
	  case EFI_IFR_CHECKBOX_OP:
	    type = EFI_IFR_TYPE_BOOLEAN;
	    MemCopy(&(value), ctrlValue, size);
	    break;
	  case EFI_IFR_ACTION_OP:
	    type = EFI_IFR_TYPE_OTHER;
	    tok = ((EFI_IFR_ACTION*)ControlData->ControlPtr)->QuestionConfig;
	    MemCopy(&(value), &tok, sizeof(EFI_STRING_ID));
	    break;
	  case EFI_IFR_STRING_OP:
	  case EFI_IFR_PASSWORD_OP:
	    type = EFI_IFR_TYPE_STRING;
	    tok = HiiAddString(hiiHandle, ctrlValue);
	    MemCopy(&(value), &tok, sizeof(EFI_STRING_ID));
	    break;
	  case EFI_IFR_DATE_OP:
		type = EFI_IFR_TYPE_DATE;
		MemCopy(&(value), ctrlValue, size);
		break;
  	  case EFI_IFR_TIME_OP:
		type = EFI_IFR_TYPE_TIME;
		MemCopy(&(value), ctrlValue, size);
		break;

	  default:
	    goto DONE;
	    break;
	  }
  }
  else
  {
  	type = EFI_IFR_TYPE_UNDEFINED;
  }

 SetCallBackControlInfo(hiiHandle, tempVariable);

  switch(Action)
  {
    case AMI_CALLBACK_FORM_OPEN:
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Sending EFI_BROWSER_ACTION_FORM_OPEN \n\n" );         
        break;
    case AMI_CALLBACK_FORM_CLOSE:
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Sending EFI_BROWSER_ACTION_FORM_CLOSE \n\n" );
        break;
    case AMI_CALLBACK_RETRIEVE:
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Sending EFI_BROWSER_ACTION_RETRIEVE \n\n" );
        break;
    case AMI_CALLBACK_CONTROL_UPDATE:            
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Sending EFI_BROWSER_ACTION_CHANGING \n\n" );
        break;
		case AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING : 
			SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Sending EFI_BROWSER_ACTION_DEFAULT_MANUFACTURING \n\n" );
         break;
		case AMI_CALLBACK_FORM_DEFAULT_STANDARD : 
			SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Sending EFI_BROWSER_ACTION_DEFAULT_STANDARD \\n\n" );//EIP 105167 : Making the specify setup items departing from F2/F3 effect.
         break;
    default:
       
       break;
  }   
  BrowserActionDiscard = FALSE;	
  status = FormCallBack(hiiHandle, Key, type, &value, action);

  switch(Action)
  {
    case AMI_CALLBACK_FORM_OPEN:
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_FORM_OPEN returned,  status = 0x%x \n\n" , status );          
        break;
    case AMI_CALLBACK_FORM_CLOSE:
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_FORM_CLOSE returned,  status = 0x%x \n\n" , status ); 
        break;
    case AMI_CALLBACK_RETRIEVE:
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_RETRIEVE returned,  status = 0x%x \n\n" , status ); 
        break;
    case AMI_CALLBACK_CONTROL_UPDATE:            
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_CHANGING returned,  status = 0x%x \n\n" , status ); 
        break;
		case AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING : 
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING returned,  status = 0x%x \n\n" , status ); 
        break; 
		case AMI_CALLBACK_FORM_DEFAULT_STANDARD : 
        SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] AMI_CALLBACK_FORM_DEFAULT_STANDARD returned,  status = 0x%x \n\n" , status ); //EIP 105167 : Making the specify setup items departing from F2/F3 effect.
        break;
   default:
       
       break;
  }     
    
  SetCallBackControlInfo(NULL, 0);

  if(CONTROL_TYPE_SUBMENU == ControlType) { //Skip rest of the step for REF / Submenu control
    goto DONE;
  }
  //For the action EFI_BROWSER_ACTION_CHANGING update the cache and invoke callback with EFI_BROWSER_ACTION_CHANGED
	if((!EFI_ERROR(status))&&(OpHeader->OpCode != EFI_IFR_ACTION_OP && OpHeader->OpCode != EFI_IFR_REF_OP))
	{
		if (FALSE == BrowserActionDiscard)
	 	{
			if((OpHeader->OpCode == EFI_IFR_STRING_OP)||(OpHeader->OpCode == EFI_IFR_PASSWORD_OP))
			{
				if ( NULL != ctrlValue )
					MemFreePointer( (VOID **)&ctrlValue );
				ctrlValue = HiiGetString( hiiHandle, value.string );
				FullCtrlValue = EfiLibAllocateZeroPool (size);
				if (NULL == FullCtrlValue)
				{
					status = EFI_OUT_OF_RESOURCES;
					goto DONE;
				}
				MemCopy (FullCtrlValue, ctrlValue, EfiStrLen (ctrlValue) * sizeof (CHAR16));	//If not allocated with full size then junk will be store after original string

				if ((EFI_IFR_PASSWORD_OP == OpHeader->OpCode) && IsPasswordEncodeEnabled (ControlData))
				{
					ctrlValue = PasswordUpdate (FullCtrlValue, size);
				}
				VarSetValue (tempVariable, offset, size, FullCtrlValue);//EIP 105167 : Making the specify setup items departing from F2/F3 effect.
				MemFreePointer ((VOID **)&FullCtrlValue);
			}
			else
			{
			 VarSetValue(tempVariable, offset, size, &value );//EIP 105167 : Making the specify setup items departing from F2/F3 effect.
			}
		}
	}
	BrowserActionDiscard = FALSE;
  
 if( (action == EFI_BROWSER_ACTION_CHANGING ) && (/*(status == EFI_UNSUPPORTED) ||*/ (status == EFI_SUCCESS)) )
  {
	switch(OpHeader->OpCode)
	{
	case EFI_IFR_NUMERIC_OP:
	case EFI_IFR_ONE_OF_OP:
	case EFI_IFR_ORDERED_LIST_OP:
	case EFI_IFR_CHECKBOX_OP:
	case EFI_IFR_ACTION_OP:
	case EFI_IFR_STRING_OP:
	case EFI_IFR_PASSWORD_OP:
	case EFI_IFR_DATE_OP:
	case EFI_IFR_TIME_OP:
		if(hiiHandle != NULL)
		{
			SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_CHANGING Success\n\n" ); 
            
            action = EFI_BROWSER_ACTION_CHANGED;
		 	SetCallBackControlInfo(hiiHandle, tempVariable);

            
            SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Sending EFI_BROWSER_ACTION_CHANGED \n\n" ); 

			status = FormCallBack(hiiHandle, Key, type, &value,action);

            SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_CHANGED returned,  status = 0x%x \n\n" , status ); 
            
	  		SetCallBackControlInfo(NULL, 0);
		}
		status = EFI_SUCCESS;
		break;
	default:
		break;
	}
  }
  if(OpHeader->OpCode == EFI_IFR_STRING_OP || OpHeader->OpCode == EFI_IFR_PASSWORD_OP)
  {
    HiiRemoveString(hiiHandle, tok);
  }

DONE:
  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Exiting CallFormCallBack()\n\n" ); 
  if(gPrevControlValue)
	MemFreePointer( (VOID **)&gPrevControlValue );
  if(gCurPswdString)
	MemFreePointer( (VOID **)&gCurPswdString );
  MemFreePointer( (VOID **)&ctrlValue );
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     CallTextCallBack
//
// Description:   
//
// Parameter:     TEXT_DATA *text, ACTION_DATA *Data
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CallTextCallBack(TEXT_DATA *text, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	if (text->Interval == 0)
		return Status;
	if ( --(text->Interval) == 0 )
	{
		// initialize the interval
		text->Interval = (UINT8)(text->ControlData.ControlFlags.ControlRefresh);
		return EFI_SUCCESS;
	}
	else
		return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     SpecialActionCallBack
//
// Description:   
//
// Parameter:     CONTROL_INFO * ControlData, UINT16 Key
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SpecialActionCallBack(CONTROL_INFO * ControlData, UINT16 Key)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_IFR_TYPE_VALUE value;

  UINT16 tok = 0;
  UINT8	type = 0;

  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Entering SpecialActionCallBack()\n\n" );   

  MemSet( &value, sizeof(value), 0 );
  type = EFI_IFR_TYPE_OTHER;
  tok = ((EFI_IFR_ACTION*)ControlData->ControlPtr)->Question.Header.Prompt;
  MemCopy(&(value), &tok, sizeof(EFI_STRING_ID));

  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Sending EFI_BROWSER_ACTION_CHANGING \n\n" ); 

  SetCallBackControlInfo(ControlData->ControlHandle, ControlData->ControlVariable);
  status = FormCallBack(ControlData->ControlHandle, Key, type, &value,EFI_BROWSER_ACTION_CHANGING);
  SetCallBackControlInfo(NULL, 0);

  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] EFI_BROWSER_ACTION_CHANGING returned,  status = 0x%x \n\n" , status );   

  SETUP_DEBUG_UEFI_CALLBACK (  "[TSE] Exiting SpecialActionCallBack()\n\n" );    

  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     UefiPreControlUpdate
//
// Description:   store the Control value before updating and calling the callback.
//
// Parameter:     CONTROL_INFO * ControlData
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UefiPreControlUpdate (CONTROL_INFO *ControlData)
{
	EFI_STATUS status = EFI_SUCCESS;

	if(gPrevControlValue)
		MemFreePointer( (VOID **)&gPrevControlValue );

	if (NULL == ControlData)			//UefiPreControlUpdate will be called with NULL for clearing gPrevControlValue. So returning from here if it is NULL.
	{
		return;
	}	
	if(UefiIsInteractive(ControlData))
	{
		UINT32 size = 0;
		UINT32 offset = 0;
		offset = UefiGetQuestionOffset(ControlData->ControlPtr);
		if(ControlData->ControlType == CONTROL_TYPE_ORDERED_LIST)
		{
			UINTN Type=0;
			UefiGetValidOptionType( ControlData, &Type, &size);
			size = gOrderlistcount * size;
		}
		else
			size = UefiGetWidth(ControlData->ControlPtr);
		gPrevControlValue = EfiLibAllocateZeroPool(size);
		if(gPrevControlValue == NULL)
		{
			//EFI_OUT_OF_RESOURCES;
			return;
		}

		status = VarGetValue(ControlData->ControlVariable, offset, size, gPrevControlValue );
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     SavePswdString
//
// Description:   fucntion to save the password string.
//
// Parameter:     CONTROL_INFO * ControlData, CHAR16 *String
//
// Return Value:  VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SavePswdString (CONTROL_INFO *ControlData, CHAR16 *String)
{
	EFI_STATUS status = EFI_SUCCESS;

	if(gCurPswdString)
		MemFreePointer( (VOID **)&gCurPswdString );

	if (NULL == ControlData)			//UefiPreControlUpdate will be called with NULL for clearing gPrevControlValue. So returning from here if it is NULL.
	{
		return;
	}	
	if(UefiIsInteractive(ControlData))
	{
		UINT32 size = 0;
		size = UefiGetWidth(ControlData->ControlPtr);
		gCurPswdString = EfiLibAllocateZeroPool(size);
		if ( NULL == gCurPswdString )
        	return ;
		MemCopy(gCurPswdString, String, size);
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     UefiIsProceedWithPageChange
//
// Description:   	If the Formcallback returns status is EFI_UNSUPPORTED or EFI_SUCCESS.
//					Change page is allowed. Otherwise changeing of page should not happen
//					For UEFI 2.0 Just return EFI_SUCCESS;
//
// Parameter:     EFI_STATUS
//
// Return Value:  EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UefiIsProceedWithPageChange(EFI_STATUS Status)
{
	// For Submenu if the status is EFI_UNSUPPORTED or EFI_SUCCESS.
	// Change page is allowed.
	if((Status == EFI_UNSUPPORTED) || (Status == EFI_SUCCESS))
	{
		return EFI_SUCCESS;
	}
	else
		return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     UEFICallSetupFormCallBack
//
// Description:	  The Wrapper function function which calls the CallFormCallBack() if the control is Interactive    	
//
// Parameter:     UINTN Action 
//
// Return Value:  VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UEFICallSetupFormCallBack(UINTN Action )
{
//EIP-53480: Implementation of FormBrowser with actions support 
	UINT32	page, control;
	gBrowserCallbackEnabled = TRUE;

	if (NULL != gApplicationData)
	{
		for ( page = 0; page < gPages->PageCount; page++ )
		{
			PAGE_INFO *pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[page]);

			if (NULL != pageInfo && 0 == pageInfo->PageHandle)
				continue;

			for ( control= 0; control < pageInfo->PageControls.ControlCount; control++ )
			{
				CONTROL_INFO *controlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);

				if (UefiIsInteractive(controlInfo))
				{
					// EIP88031 : Allow BROWSER_ACTION_RETRIEVE for all Interactive controls on MiniSetupEntry
					//if((Action == EFI_BROWSER_ACTION_RETRIEVE)&&(controlInfo->ControlType == CONTROL_TYPE_SUBMENU))
					//	continue;
				
					UefiPreControlUpdate(NULL);	//EIP 75464 : Updating the gPrevControlValue buffer to NULLL before invoking CallFormCallBack 
					CallFormCallBack(controlInfo, UefiGetControlKey(controlInfo), FALSE,Action);
				}

			}
		}
	}
	gBrowserCallbackEnabled = FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     UefiGetActionWapper
//
// Description:	  The Wrapper function to get the actual action for the driver   	
//
// Parameter:     UINTN Action 
//
// Return Value:  EFI_BROWSER_ACTION 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_BROWSER_ACTION UefiGetActionWapper(UINTN Action)
{
	if(Action == AMI_CALLBACK_CONTROL_UPDATE)
	  return EFI_BROWSER_ACTION_CHANGING;
	  
	if(Action == AMI_CALLBACK_RETRIEVE)
	  return EFI_BROWSER_ACTION_RETRIEVE;
	  
	if(Action == AMI_CALLBACK_FORM_OPEN)
	  return EFI_BROWSER_ACTION_FORM_OPEN;
	  
	if(Action == AMI_CALLBACK_FORM_CLOSE)
	  return EFI_BROWSER_ACTION_FORM_CLOSE;

	if(Action == AMI_CALLBACK_FORM_DEFAULT_MANUFACTURING)
	  return  EFI_BROWSER_ACTION_DEFAULT_MANUFACTURING;//EIP 105167 : Making the specify setup items departing from F2/F3 effect.

	if(Action == AMI_CALLBACK_FORM_DEFAULT_STANDARD)
	  return  EFI_BROWSER_ACTION_DEFAULT_STANDARD;
	  
	return Action;

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
