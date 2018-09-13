//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/HiiNotificationHandler.c $
//
// $Author: Arunsb $
//
// $Revision: 14 $
//
// $Date: 2/11/14 8:54p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/HiiNotificationHandler.c $
// 
// 14    2/11/14 8:54p Arunsb
// [TAG]	EIP130997
// [Category]	Improvement
// [Description]	New pack support in ESA
// 
// 13    2/25/13 10:57a Blaines
// [TAG] - EIP 104273
// [Category] - Action Item
// [Description] -  Provide ability to dump the Hii Pack from the Setup as
// part TSE debug Infrastructure. It should dump the Pack updates on Hii
// notification also.
// So it can be used to debug the issue.
// [Files] - ForBrowser2.c,  Hii.c,  HiiNotificationHandler.c,
// UefiWapper.c,  TseUefiHii.h
// 
// 12    10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 11    5/26/12 5:20a Arunsb
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
// 10    12/10/11 4:47a Arunsb
// Header corrected
// 
// 9     12/07/11 2:54p Arunsb
// [TAG]  		EIP75588
// [Category]  	New Feature
// [Description]  	Support for queuing UpdatePack notifications
// [Files]  		frame.c, page.c, formbrowser2.c, hii.c, hiicallback.c,
// hiinotificationhandler.c, tseuefihii.h and uefi21wapper.c
// 
// 8     11/14/11 2:43p Blaines
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
// 7     12/28/10 12:31p Madhans
// To update the Tag of EIp 46998. UEFI option ROM menus disappear in
// Setup when certain options are selected. 
// No file changed but Comment updated right
// 
// 6     10/27/10 4:25p Madhans
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
// 5     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 4     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 8:50p Madhans
// 
// 4     2/19/10 8:21a Mallikarjunanv
// updated year in copyright message
// 
// 3     2/15/10 10:19p Madhans
// to support EDK nt32 version
// 
// 2     11/19/09 5:31p Presannar
// Updated TSE include file name to not clash with CORE file
// 
// 1     8/11/09 2:50p Presannar
// HiiNotificationHandler to handle notification of dynamic modification
// of IFR data.
// 
// 2     7/24/09 3:58p Presannar
// Modified IFRChangeNotifyFn to handle New/Add pack notification
// 
// 1     7/09/09 11:24a Presannar
// Initial Draft
// Code to handle Notification arising from Dynamic Form Modification
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:          HiiNotificationHandler.c
//
// Description:  Contains Hii related Functions
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "Minisetup.h"
#include "TseUefiHii.h"

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define BY_ENTRY         0
#define BY_HANDLE        1
#define BY_TYPE          2
#define BY_HANDLE_TYPE   3

//---------------------------------------------------------------------------
// Type definitions
//---------------------------------------------------------------------------
typedef struct _NOTIFICATION_INFO NOTIFICATION_INFO;

typedef struct _NOTIFICATION_INFO
{
  EFI_HII_HANDLE Handle;
  EFI_HII_DATABASE_NOTIFY_TYPE NotifyType;
  UINT8 *PackData;
  UINTN DataLength;
  NOTIFICATION_INFO *prevNotifInfo;
  NOTIFICATION_INFO *nextNotifInfo;
};

typedef struct _NOTIFICATION_QUEUE
{
  UINTN NumOfNotification;
  NOTIFICATION_INFO *headNotifInfo;
  NOTIFICATION_INFO *tailNotifInfo;
} NOTIFICATION_QUEUE;

//---------------------------------------------------------------------------
// Externs
//---------------------------------------------------------------------------
extern EFI_STATUS FindHandleWithInSetupData(EFI_HII_HANDLE Handle);
extern EFI_BROWSER_ACTION gBrowserCallbackAction ;
extern BOOLEAN gBrowserCallbackEnabled;
//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
BOOLEAN gIFRChangeNotify = FALSE;
EFI_HII_HANDLE gRemovedHandle=NULL;
BOOLEAN gEnableDrvNotification = FALSE; //TRUE if allow notification function to process action, FALSE to ignore the notification
BOOLEAN gEnableProcessPack = FALSE; //TRUE if the process pack is allowed, FALSE if to be ignored

static EFI_HANDLE gIFRHandle;
static UINTN gNotifyType;
#ifndef TSE_FOR_APTIO_4_50
#define EFI_HII_PACKAGE_FORMS                EFI_HII_PACKAGE_FORM
#include "tianohii.h"
#endif

NOTIFICATION_QUEUE *gNotificationQueue = (NOTIFICATION_QUEUE *)NULL; //This is a pointer to the notifiaction queue
BOOLEAN gPackUpdatePending = FALSE;

//---------------------------------------------------------------------------
// Function Prototypes
//---------------------------------------------------------------------------
EFI_STATUS AddNotificationToQueue(EFI_HII_HANDLE Handle, EFI_HII_DATABASE_NOTIFY_TYPE Type);
EFI_STATUS ProcessPackNotificationHook (VOID);
//---------------------------------------------------------------------------
// Function Implementation
//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     RegisterFormNotification
//
// Description:   Notification Registering Function
//
// Parameter:     EFI_HII_DATABASE_NOTIFY PackageNotifyFn,
//                EFI_HII_DATABASE_NOTIFY_TYPE NotifyType,
//                EFI_HANDLE *NotifyHandle
//
// Return value:  EFI_STATUS
//					      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RegisterFormNotification(EFI_HII_DATABASE_NOTIFY PackageNotifyFn,
                                    EFI_HII_DATABASE_NOTIFY_TYPE NotifyType,
                                    EFI_HANDLE *NotifyHandle)
{
  //
  // Register notification
  //
  return gHiiDatabase->RegisterPackageNotify (
                           gHiiDatabase,
                           EFI_HII_PACKAGE_FORMS,
                           NULL,
                           PackageNotifyFn,
                           NotifyType,
                           NotifyHandle
                           );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     UnRegisterFormNotification
//
// Description:   Notification UnRegistering Function
//
// Parameter:     EFI_HANDLE *NotifyHandle
//
// Return value:  EFI_STATUS
//					      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UnRegisterFormNotification(EFI_HANDLE NotifyHandle)
{
  //
  // UnRegister notification
  //
  return gHiiDatabase->UnregisterPackageNotify (gHiiDatabase, NotifyHandle);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     IFRChangeNotifyFn
//
// Description:   Function that handles IFR change notification
//
// Parameter:     IN UINT8 PackageType,
//                IN CONST EFI_GUID *PackageGuid,
//                IN CONST EFI_HII_PACKAGE_HEADER *Package,
//                IN EFI_HII_HANDLE Handle,
//                IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType
//
// Return value:  EFI_STATUS
//					      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IFRChangeNotifyFn (
	IN UINT8                              PackageType,
	IN CONST EFI_GUID                     *PackageGuid,
	IN CONST EFI_HII_PACKAGE_HEADER       *Package,
	IN EFI_HII_HANDLE                     Handle,
	IN EFI_HII_DATABASE_NOTIFY_TYPE       NotifyType
	)
{
	EFI_STATUS status = EFI_NOT_FOUND;

	//EIP90895
	if( (gBrowserCallbackEnabled == TRUE) && 
		( (gBrowserCallbackAction == EFI_BROWSER_ACTION_FORM_OPEN) ||		
		 (gBrowserCallbackAction == EFI_BROWSER_ACTION_FORM_CLOSE) ||
		 (gBrowserCallbackAction == EFI_BROWSER_ACTION_RETRIEVE) ) )
	{
		if (TSE_DEBUG_MESSAGES)
		{
			SETUP_DEBUG_TSE ("\n\n[TSE] WARNING: Browser callback is currently in progress");
			SETUP_DEBUG_TSE ("\n[TSE] HII PACK REMOVE/ADD/UPDATE from EFI_BROWSER_ACTION_FORM_OPEN/EFI_BROWSER_ACTION_RETRIEVE/EFI_BROWSER_ACTION_CLOSE");
			SETUP_DEBUG_TSE ("\n[TSE] It is not recommended to proceed with the current action, behavior could be unpredictable.");
			SETUP_DEBUG_TSE ("\n[TSE] It is advisable to work with the card vendor to properly support UEFI 2.3.1, or");
			SETUP_DEBUG_TSE ("\n[TSE] decrease the value of TSE_CALLBACK_SPEC_VERSION to (UEFI 2.1) to change the callback functionality.");
			SETUP_DEBUG_TSE ("\n[TSE] So UEFI 2.3.1 Callbacks will be disabled!\n\n");
		}
		ASSERT (0);
	}

	if (FALSE == gEnableDrvNotification)		//EIP75588
	{
		SETUP_DEBUG_UEFI_NOTIFICATION ("\n\n[TSE] Illegal Notification (Type: NotifyType 0x%x) recieved. \n\n", NotifyType);
	}
	status = AddNotificationToQueue (Handle, NotifyType); //Adding notification to the queue
	if(status != EFI_SUCCESS) //Failed to add notification in the queue, return error
	{
		goto DONE;
	}
	gPackUpdatePending = TRUE;
	
	if(gEnableDrvNotification && !gEnableProcessPack)
	{
		SETUP_DEBUG_UEFI_NOTIFICATION ("\n\n[TSE] IFRChangeNotifyFn() calling ProcessPackNotificationHook() \n\n");
		gEnableProcessPack = TRUE;
		status = ProcessPackNotificationHook (); // Synchronized Notification Call happening because of Callback,ExtractConfig. routeconfig.
		gEnableProcessPack = FALSE;
	}
DONE:
  SETUP_DEBUG_UEFI_NOTIFICATION ("\n\n[TSE] Exiting IFRChangeNotifyFn() status: %x\n\n", status);
  return status;
}

//EIP75588 starts
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   AddNotificationToQueue
//
// Description: Adds new notification to the queue and increments queue size
//
// Input:	EFI_HII_HANDLE Handle, EFI_HII_DATABASE_NOTIFY_TYPE Type
//
// Output:	EFI_STATUS status - EFI_ABORTED, By default
//                              EFI_OUT_OF_RESOURCES, if memory allocation fails
//                              EFI_SUCCESS, if successful
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AddNotificationToQueue (EFI_HII_HANDLE Handle, EFI_HII_DATABASE_NOTIFY_TYPE Type)
{
	EFI_STATUS status = EFI_ABORTED;
	NOTIFICATION_INFO *tempNotifInfo = (NOTIFICATION_INFO *)NULL;
	
	if (gNotificationQueue == NULL)
	{
		gNotificationQueue = EfiLibAllocateZeroPool (sizeof (NOTIFICATION_QUEUE));
		if (NULL == gNotificationQueue)
		{
			status = EFI_OUT_OF_RESOURCES; //Cannot allocate memory for the notification queue
			goto DONE;
		}
	}
	if (NULL == tempNotifInfo)
	{
		tempNotifInfo = EfiLibAllocateZeroPool(sizeof(NOTIFICATION_INFO));
		if (NULL == tempNotifInfo)
		{
			status = EFI_OUT_OF_RESOURCES; //Cannot allocate memory for the notification queue
			goto DONE;
		}
	}
	tempNotifInfo->Handle = Handle;
	tempNotifInfo->NotifyType = Type;
	if((Type == EFI_HII_DATABASE_NOTIFY_NEW_PACK) || (Type == EFI_HII_DATABASE_NOTIFY_ADD_PACK))
	{
		tempNotifInfo->PackData = (UINT8*)HiiGetForm(Handle, 0, &tempNotifInfo->DataLength);
	}
	if((gNotificationQueue->NumOfNotification == 0) || (gNotificationQueue->headNotifInfo == NULL))
	{
		gNotificationQueue->headNotifInfo = tempNotifInfo;
		gNotificationQueue->tailNotifInfo = tempNotifInfo;
	}
	else
	{
		tempNotifInfo->prevNotifInfo = gNotificationQueue->tailNotifInfo;
		gNotificationQueue->tailNotifInfo = tempNotifInfo;
		gNotificationQueue->tailNotifInfo->prevNotifInfo->nextNotifInfo = tempNotifInfo;
	}
	gNotificationQueue->NumOfNotification++;
	status = EFI_SUCCESS;
DONE:
	return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   RemoveFromQueueByEntry
//
// Description: Removes the notification entry from the queue, and returns
//              the pointer to the next notification node
//
// Input:	NOTIFICATION_INFO *matchingNotifInfo
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RemoveFromQueueByEntry(NOTIFICATION_INFO *matchingNotifInfo)
{
	NOTIFICATION_INFO *tempNotifInfo = matchingNotifInfo;
	
	if ((NULL == tempNotifInfo) || (NULL == gNotificationQueue) || (0 == gNotificationQueue->NumOfNotification)){
		goto DONE;
	}
	if(gNotificationQueue->headNotifInfo == tempNotifInfo){
		if (gNotificationQueue->headNotifInfo == gNotificationQueue->tailNotifInfo){
			gNotificationQueue->tailNotifInfo = tempNotifInfo->nextNotifInfo;
		}
		gNotificationQueue->headNotifInfo = tempNotifInfo->nextNotifInfo;
	}else if(gNotificationQueue->tailNotifInfo == tempNotifInfo){
		gNotificationQueue->tailNotifInfo = tempNotifInfo->prevNotifInfo;
	}
	if(tempNotifInfo->prevNotifInfo){
		tempNotifInfo->prevNotifInfo->nextNotifInfo = tempNotifInfo->nextNotifInfo;
	}
	if(tempNotifInfo->nextNotifInfo){
		tempNotifInfo->nextNotifInfo->prevNotifInfo = tempNotifInfo->prevNotifInfo;
	}
	gNotificationQueue->NumOfNotification--; //Decrement the number of notification by 1
	MemFreePointer(&tempNotifInfo); //Free the node
DONE:
	return;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   RemoveNotifFromQueueByHandleType
//
// Description: Removes the all the node with same notification handle and
//              type except the passed the entry from the queue
//
// Input:	EFI_HII_HANDLE Handle
//          EFI_HII_DATABASE_NOTIFY_TYPE Type
//          NOTIFICATION_INFO *matchingNotifInfo
//
// Output:	EFI_STATUS status - EFI_ABORTED, By default ;
//                              EFI_INVALID_PARAMETER, if invalid gNotificationQueue
//                              EFI_SUCCESS, if successful
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RemoveNotifFromQueueByHandleType (UINTN RemoveOption, EFI_HII_HANDLE Handle, EFI_HII_DATABASE_NOTIFY_TYPE Type, NOTIFICATION_INFO *matchingNotifInfo)
{
	EFI_STATUS status = EFI_NOT_FOUND;
	NOTIFICATION_INFO *tempNotifInfo = (NOTIFICATION_INFO *)NULL;
	NOTIFICATION_INFO *currNotifInfo = (NOTIFICATION_INFO *)NULL;
	EFI_HII_HANDLE NotifyHandle = (EFI_HII_HANDLE)NULL;
	EFI_HII_DATABASE_NOTIFY_TYPE NotifyType = 0;
	
	if (NULL == gNotificationQueue){
		status = EFI_INVALID_PARAMETER; //gNotificationQueue invalid
		goto DONE;
	}
	
	if((Handle != NULL) || (Type != 0)){
		NotifyHandle = Handle;
		NotifyType = Type;
	} else{
		NotifyHandle = matchingNotifInfo->Handle;
		NotifyType = matchingNotifInfo->NotifyType;
	}
	tempNotifInfo = gNotificationQueue->headNotifInfo;
	while(tempNotifInfo != NULL)
	{
		currNotifInfo = tempNotifInfo->nextNotifInfo;
		if (BY_ENTRY == RemoveOption){
			if (tempNotifInfo == matchingNotifInfo){
				RemoveFromQueueByEntry(tempNotifInfo);
				status = EFI_SUCCESS;
				break;
			}
		}else if(tempNotifInfo != matchingNotifInfo){	//Match found
			if (BY_HANDLE == RemoveOption){
				if (tempNotifInfo->Handle == NotifyHandle){					
					RemoveFromQueueByEntry(tempNotifInfo);
					status = EFI_SUCCESS;
				}
			} else if(RemoveOption == BY_TYPE){
				if(tempNotifInfo->NotifyType == NotifyType){
					RemoveFromQueueByEntry(tempNotifInfo);
					status = EFI_SUCCESS;
				}
			} else if(RemoveOption == BY_HANDLE_TYPE){	
//If match found process the node and move to the next node
				if((tempNotifInfo->Handle == NotifyHandle) && (tempNotifInfo->NotifyType == NotifyType)){
					RemoveFromQueueByEntry(tempNotifInfo);
					status = EFI_SUCCESS;
				}
			}
		}
		tempNotifInfo = currNotifInfo;
	}
DONE:
	return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   CleanNotificationQueue
//
// Description: Cleans the IFR notification queue
//
// Input:	None
//
// Output:	EFI_STATUS status - EFI_SUCCESS, if successful
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CleanNotificationQueue()
{
	EFI_STATUS status = EFI_ABORTED;
	
	do //Loop to clean up the notification queue
	{
		if((NULL == gNotificationQueue) || (NULL == gNotificationQueue->headNotifInfo))
		{
			status = EFI_SUCCESS; //The is no notification to process
			goto DONE;
		}
		RemoveFromQueueByEntry(gNotificationQueue->headNotifInfo); //Removes this node
	}while (1);
	if (gNotificationQueue)
	{
		MemFreePointer (&gNotificationQueue);
		gNotificationQueue = (NOTIFICATION_QUEUE *)NULL; //Reset the Notification Queue
	}
DONE:
	return status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   RemoveDuplicateIFRNotification
//
// Description: Finds duplicate notification on the same handle and remove
//
// Input:	None
//
// Output:	EFI_STATUS status - EFI_ABORTED, By default ;
//                              EFI_INVALID_PARAMETER, if invalid gNotificationQueue
//                              EFI_SUCCESS, if successful
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RemoveDuplicateIFRNotification()
{
	EFI_STATUS 		status = EFI_ABORTED;
	EFI_HII_HANDLE Handle = (EFI_HII_HANDLE)NULL;
	NOTIFICATION_INFO *tempNotifInfo = (NOTIFICATION_INFO *)NULL;
	EFI_HII_DATABASE_NOTIFY_TYPE NotifyType = 0;
    BOOLEAN packFound = FALSE;	
	
	if((gNotificationQueue == NULL) || (gNotificationQueue->headNotifInfo == NULL))
	{
		status = EFI_SUCCESS; //The is no notification to process
		goto DONE;
	}
	SETUP_DEBUG_UEFI_NOTIFICATION ("\n\n[TSE] Before RemoveDuplicateIFRNotification(), NumOfNotification left: %d\n\n", gNotificationQueue->NumOfNotification);
	
	tempNotifInfo = gNotificationQueue->tailNotifInfo;
	Handle = tempNotifInfo->Handle;
	NotifyType = tempNotifInfo->NotifyType;
	
	while(tempNotifInfo != NULL) //Loop to removed duplicate notifications
	{
    	if((EFI_HII_DATABASE_NOTIFY_REMOVE_PACK == tempNotifInfo->NotifyType) || 
           (EFI_HII_DATABASE_NOTIFY_ADD_PACK == tempNotifInfo->NotifyType)){
			RemoveNotifFromQueueByHandleType (BY_HANDLE_TYPE, 0, 0, tempNotifInfo); //If the handle belongs to the formset, clean up notification queue
		}
		if(tempNotifInfo != NULL){  //If the current node is valid
			tempNotifInfo = tempNotifInfo->prevNotifInfo; //Move current notification node pointer to previous notification node
		}
	}
	tempNotifInfo = gNotificationQueue->tailNotifInfo;
	while(tempNotifInfo != NULL) //Loop to removed duplicate notifications
	{
		status = FindHandleWithInSetupData(tempNotifInfo->Handle);
		if (EFI_SUCCESS == status){
			packFound = TRUE;
		}
	
		if(tempNotifInfo->NotifyType == EFI_HII_DATABASE_NOTIFY_REMOVE_PACK){
			if(packFound){
				BOOLEAN newPackOnThisHandle = FALSE;
				NOTIFICATION_INFO *thisNotifInfo = tempNotifInfo->prevNotifInfo;
				while(thisNotifInfo) //Loop to find if there is a new pack notification in the queue with this handle
				{
					if((thisNotifInfo->Handle == tempNotifInfo->Handle) && (EFI_HII_DATABASE_NOTIFY_NEW_PACK == thisNotifInfo->NotifyType)){
						newPackOnThisHandle = TRUE;
						break;
					}
					thisNotifInfo = thisNotifInfo->prevNotifInfo;
				}
				if(newPackOnThisHandle){	//If a new pack notification was found, no need to process any notification on this handle
					RemoveNotifFromQueueByHandleType(BY_HANDLE, tempNotifInfo->Handle, 0, NULL);
					tempNotifInfo = gNotificationQueue->tailNotifInfo;
					continue;
				} else{		//Removed everything except for the remove pack notification on the handle
					RemoveNotifFromQueueByHandleType(BY_HANDLE, tempNotifInfo->Handle, 0, tempNotifInfo);
				}
			} else{
				RemoveNotifFromQueueByHandleType(BY_ENTRY, NULL, 0, tempNotifInfo); //clean up notification queue, except for this handle
			}
		} else if(tempNotifInfo->NotifyType == EFI_HII_DATABASE_NOTIFY_ADD_PACK) {
			if(packFound){
				if((gIFRChangeNotify == TRUE) && (gRemovedHandle != NULL)){
					RemoveNotifFromQueueByHandleType(BY_HANDLE, gRemovedHandle, 0, tempNotifInfo); //If the previous remove pack is already processed, clean up notification queue with this handle
				} else{
					NOTIFICATION_INFO *thisNotifInfo = tempNotifInfo->prevNotifInfo;
					while (thisNotifInfo) //Loop to find if there is a remove pack notification in the queue with this handle
					{
						if((thisNotifInfo->Handle == tempNotifInfo->Handle) && (thisNotifInfo->NotifyType == EFI_HII_DATABASE_NOTIFY_REMOVE_PACK)){
							tempNotifInfo = thisNotifInfo; //Skip the first remove pack encountered on this handle
							break;
						}
						thisNotifInfo = thisNotifInfo->prevNotifInfo;
					}
				}
			} else{
				RemoveNotifFromQueueByHandleType(BY_ENTRY, NULL, 0, tempNotifInfo); //clean up notification queue, except for this handle
			}
		}
		if (NULL != tempNotifInfo){		//If the current node is valid
			tempNotifInfo = tempNotifInfo->prevNotifInfo; //Move current notification node pointer to previous notification node
		}
		packFound = FALSE;
	}
	SETUP_DEBUG_UEFI_NOTIFICATION ("\n\n[TSE] After RemoveDuplicateIFRNotification(), NumOfNotification left: %d\n\n", gNotificationQueue->NumOfNotification);
DONE:
	return status;
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
	EFI_STATUS 		status = EFI_ABORTED;
	EFI_HII_HANDLE 	Handle = (EFI_HII_HANDLE)NULL;
	EFI_HII_DATABASE_NOTIFY_TYPE NotifyType = 0;
	UINT8 			*PackData = (UINT8 *)NULL;

	SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] Entering IFRChangeNotifyFn() \n\n");
	RemoveDuplicateIFRNotification();

	if((gNotificationQueue == NULL) || (gNotificationQueue->headNotifInfo == NULL))
	{
		status = EFI_NOT_FOUND; //There is no notification to process
		goto DONE;
	}

	do
	{
		if ((NULL == gNotificationQueue) || (NULL == gNotificationQueue->headNotifInfo))
		{
			status = EFI_SUCCESS; //All the notifications are processed
			goto DONE;
		}
		Handle = gNotificationQueue->headNotifInfo->Handle;
		NotifyType = gNotificationQueue->headNotifInfo->NotifyType;
		PackData = gNotificationQueue->headNotifInfo->PackData;

		SETUP_DEBUG_UEFI_NOTIFICATION( "\n\n[TSE] gNotificationQueue->NumOfNotification left: %d \n\n", gNotificationQueue->NumOfNotification);	
	
		switch(NotifyType)
		{
			case EFI_HII_DATABASE_NOTIFY_REMOVE_PACK:
				SETUP_DEBUG_UEFI_NOTIFICATION( "\n[TSE] NotifyType: EFI_HII_DATABASE_NOTIFY_REMOVE_PACK \n\n[TSE] Removing IFR Pack \n");
				if(gIFRChangeNotify)
				{
					if(gRemovedHandle!=NULL)
					{
						FixSetupData(); //Will fix the UI and Setup data.
					}
				}
				status = HandleRemoveIFRPack(Handle);
				gIFRChangeNotify = TRUE;
				gRemovedHandle = Handle;
				break;
			case EFI_HII_DATABASE_NOTIFY_NEW_PACK:
				SETUP_DEBUG_UEFI_NOTIFICATION( "\n[TSE] NotifyType: EFI_HII_DATABASE_NOTIFY_NEW_PACK \n\n[TSE] New IFR Pack \n");
				if(gIFRChangeNotify)
				{
					if(gRemovedHandle!=NULL)
					{
						FixSetupData(); //Will fix the UI and Setup data.
					}
				}
				status = HandleNewIFRPack (Handle, PackData);
				break;
			case EFI_HII_DATABASE_NOTIFY_ADD_PACK:
				SETUP_DEBUG_UEFI_NOTIFICATION( "\n[TSE] NotifyType: EFI_HII_DATABASE_NOTIFY_ADD_PACK \n\n[TSE] Add IFR Pack \n");
				status = HandleAddIFRPack(Handle, PackData);
				gIFRChangeNotify = FALSE;
				FixSetupData();
				break;
			default:
				break;
		}

#if TSE_DEBUG_MESSAGES
	    ProcessPackToFile(NotifyType, Handle) ;
#endif
		RemoveFromQueueByEntry(gNotificationQueue->headNotifInfo); //Remove the processed notification node from the queue
		SETUP_DEBUG_UEFI_NOTIFICATION( "\n[TSE] NumOfNotification left: %d, headNotifInfo: 0x%x \n\n", gNotificationQueue->NumOfNotification, gNotificationQueue->headNotifInfo);
	}while(1);

DONE:
	gPackUpdatePending = FALSE;
	SETUP_DEBUG_UEFI_NOTIFICATION( "\n[TSE] Exiting ProcessPackNotificationHook, status: %x \n\n", status);
	return status;
}
//EIP75588 ends

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
