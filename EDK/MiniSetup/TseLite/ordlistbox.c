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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ordlistbox.c $
//
// $Author: Premkumara $
//
// $Revision: 22 $
//
// $Date: 5/01/14 3:44p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ordlistbox.c $
// 
// 22    5/01/14 3:44p Premkumara
// [TAG]  		EIP123727
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Enabling Multiline and in Boot option priorities, Clicking
// on second or third line of the boot item is not selecting boot options
// menu
// [RootCause]  	Proper Condition was not there to check whether Mouse
// Click
// is within the Width and Height of Control or not.
// [Solution]  	Added Proper Condition to check whether Mouse Click
// is within the Width and Height of Control or not.
// [Files]  		Date.c, time.c, frame.c, SubMenu.c, numeric.c,
// PopupString.c, PopupSel.c, ordlistbox.c, PopupPassword.c, UefiAction.c,
// 
// 21    7/03/13 10:29a Premkumara
// [TAG]  		EIP127000
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	After suppressing any of items in orderlist, the listbox is
// showing blank space. If items are changing using +/- then Empty list
// item appear
// [RootCause]  	Since items are suppressing in listbox and the
// listbox->ItemCount, listbox->Sel, listbox options value and ptrtoken
// value are not updated properly
// [Solution]  	Handling orderedlistbox items and itemcount properly after
// items are suppressed
// [Files]  		OrdListBox.c
//  -$/Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/ordlistbox.c (ver
// 20)
// 
// 20    7/02/13 10:19a Premkumara
// [TAG]  		EIP127000
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	After suppressing any of items in orderlist, the listbox is
// showing blank space. If items are changing using +/- then Empty list
// item appear
// [RootCause]  	Since items are suppressing in listbox and the
// listbox->ItemCount, listbox->Sel, listbox options value and ptrtoken
// value are not updated properly
// [Solution]  	Handling orderedlistbox items and itemcount properly after
// items are suppressed
// [Files]  		OrdListBox.c
// 
// 19    10/18/12 8:58a Rajashakerg
// [TAG]  		EIP103568 
// [Category]  	Improvement
// [Description]  	Help string support for ordered list
// [Files]  		Uefi21Wapper.c, ordlistbox.c
// 
// 18    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 17    5/28/12 12:35p Premkumara
// [TAG]  		EIP67049 & 90224
// [Category]  	New Feature
// [Description]  	Support mouse drag operation in frame and list box
// [Files]  		CommonHelper.c, Frame.c, ListBox.c, Minisetupext
// 
// 16    5/09/12 1:37p Arunsb
// [TAG]  		EIP86885
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	ISCSI attempt order is not changing on setup
// [RootCause]  	Orderlist maxcontainers value and ordered list size not
// handled properly
// [Solution]  	Orderlist maxcontainers value is 0xff, but TSE changed the
// cache value for only the added attempts(dynamic orderlist creation)
// remaining buffer left as is, Now the remaining buffers made as 0.
// [Files]  		HiiCallback.c and ordlistbox.
// 
// 15    2/03/12 4:45a Rajashakerg
// [TAG]  			EIP75066 
// [Category]  	Improvement
// [Description]  	_OrdListGetSelection logic changed to support the
// special controls(Boot Order).
// [Files]  		Ordlistbox.c, Uefi21Wapper.c, CtrlCond.c, HiiCallback.c,
// Parse.c, Uefi20Wapper.c and TseUefihiil.h
// 
// 14    2/02/12 2:50a Premkumara
// [TAG]  		EIP75066 
// [Category]  	Improvement
// [Description]  	Support loading defaults for Ordelist controls
// [Files]  		Ordlistbox.c, Uefi21Wapper.c, CtrlCond.c, HiiCallback.c,
// Parse.c, Uefi20Wapper.c, TseUefihiil.h
// 
// 13    2/01/12 1:49a Arunsb
// [TAG]  		EIP74968
// [Category]  	Improvement
// [Description]  	Support for mouse drag and drop to rearrange the items
// in the Orderlist.
// [Files]  		Ordlistbox.c, commonoem.c and commonoem.h
// 
// 12    12/10/11 4:45a Arunsb
// Header corrected
// 
// 11    12/01/11 7:42a Arunsb
// [TAG]  		EIP70966
// UefiGetValidOptionSize fnc declaration added for avoiding build error
// in 2.0.
// 
// 10    11/28/11 4:59a Rajashakerg
// [TAG]  		EIP73231
// [Category]  	Improvement
// [Description]  	Callback handling :For interactive controls updating
// the currnet vaule in cache even when hii callback returns error status.
// [Files]  		Date.c, SubMenu.c, ordlistbox.c, time.c, UefiAction.c,
// hii.h, uefi20Wapper.c, HiiCallback.c, TseUefiHii.h, Uefi21Wapper.c  
// 
// 9     11/21/11 11:18a Premkumara
// [TAG]  		EIP72610
// [Category]  	Improvement
// [Description]  	Moving TSE_MULTILINE_CONTROLS to Binary
// [Files]  		AMITSE-CommonHelper.c, AMITSE.sdl, 
// TSELITE-UefiAction.c, TseLite.sdl, Time.h, Text.c,
// SubMenu.c, ResetButton.c, PopupString.c, PopupSel.h, PopupSel.c, 
// PopupPassword.c, OrderListBox.c, Numeric.c, Label.c, Frame.c, Edit.c, 
// Date.h, Date.c, 
// LEGACY-Legacy.c,
// BOOTONLY- Minisetup.h
// 
// 8     11/21/11 8:54a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupSel.c, PopupString.c, SubMenu.c, Text.c.
// 
// 7     11/14/11 6:55p Blaines
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
// 6     11/03/11 4:29a Premkumara
// [TAG]  		EIP70966
// [Category]  	Improvement
// [Description]  	Hii orderlist item can't update priority from value in
// Setup menu for both enable and disable TSE_MULTILINE_CONTROLS token
// [Files]  		Ordlistbox.c, ordlistbox.h, TseUefiHii.h, Uefi21Wrapper.c
// 
// 5     3/09/11 7:23p Madhans
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
// 4     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 4     2/17/10 7:03p Madhans
// To suppor readonly control
// 
// 3     6/23/09 6:52p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:05p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:12p Madhans
// TSE Lite Special control support
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		orderlistbox.c
//
// Description:	This file contains code to handle ordered list box controls
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

VOID _PopupSelGetSelection( POPUPSEL_DATA *popupSel );
EFI_STATUS _OrdListMultiLIneDraw(ORD_LISTBOX_DATA *OrdList);
UINT16 gOrderlistcount;
extern BOOLEAN lButtonOnListBoxScroll;//EIP-67049

ORD_LISTBOX_METHODS gOrdListBox =
{
	OrdListBoxCreate,
	OrdListBoxDestroy,
	OrdListBoxInitialize,
	OrdListBoxDraw,
	OrdListBoxHandleAction,
	OrdListBoxSetCallback,
	OrdListBoxSetFocus,
	OrdListBoxSetPosition,
	OrdListBoxSetDimensions,
	OrdListBoxSetAttributes,
    OrdListGetControlHeight
};
VOID UefiGetValidOptionType(CONTROL_INFO *CtrlInfo, UINTN *Type, UINT32 *SizeOfData);
BOOLEAN FirstDownEvent = FALSE;			//EIP74968 Change Order in Orderlist using Mouse drag
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxCreate
//
// Description:	function to Create a Order List Box, which uses the PopupSel Fucntions
//
// Input:	ORD_LISTBOX_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxCreate( ORD_LISTBOX_DATA **object )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(ORD_LISTBOX_DATA) );

		if ( *object == NULL )
			return Status;
	}

	Status = gPopupSel.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gOrdListBox;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxDestroy
//
// Description:	function to Destroy a Order List Box, which uses the PopupSel Fucntions
//
// Input:	ORD_LISTBOX_DATA *listbox, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxDestroy( ORD_LISTBOX_DATA *listbox, BOOLEAN freeMem )
{
	if(NULL == listbox)
	  return EFI_SUCCESS;
	
	gPopupSel.Destroy( listbox, FALSE );

	if( freeMem )
	{
		MemFreePointer( (VOID **)&(listbox->PtrTokens) );
		MemFreePointer( (VOID **)&listbox );
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxDestroy
//
// Description:	function to initialize a Order List Box, which uses the PopupSel Fucntions
//
// Input:	ORD_LISTBOX_DATA *listbox, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxInitialize( ORD_LISTBOX_DATA *listbox, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	Status = gPopupSel.Initialize( listbox, data );
//	_OrdListGetSelection(listbox); // make sure data is correct.
	listbox->ControlData.ControlHelp = UefiGetHelpField(listbox->ControlData.ControlPtr);//EIP:103568  Updated the Help field for order list control.

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxDraw
//
// Description:	function to draw a ordered List Box
//
// Input:	ORD_LISTBOX_DATA *listbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxDraw( ORD_LISTBOX_DATA *listbox )
{
	EFI_STATUS Status = EFI_SUCCESS;

	Status = _OrdListMultiLIneDraw(listbox); //EIP-70966 Draw OrderListBox

	return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   UpdateOrderlistcount
//
// Description: Function to update the orderlist count.
//
// Input:	UINT16 ItemCount
//
// Output:	VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _UpdateOrderlistcount(UINT16 ItemCount)
{
	gOrderlistcount = ItemCount;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoOrdListCallBack
//
// Description:	Call back function of ordered List Box
//
// Input:	ORD_LISTBOX_DATA *listbox
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DoOrdListCallBack(ORD_LISTBOX_DATA *listbox)
{
	UINT8 			i=0;
	VOID 				*Data = (VOID *)NULL; //EIP70966

	if ( listbox->Cookie != NULL )
	{
		VOID *ifrData = listbox->ControlData.ControlPtr;
		CALLBACK_VARIABLE *callbackData = (CALLBACK_VARIABLE *)listbox->Cookie;

		callbackData->Variable = listbox->ControlData.ControlVariable;
		callbackData->Offset = UefiGetQuestionOffset(ifrData);
		callbackData->Length = UefiGetMaxEntries(ifrData);

		if( (listbox->ControlData.ControlVariable == VARIABLE_ID_BOOT_ORDER) || 
			(listbox->ControlData.ControlVariable == VARIABLE_ID_BBS_ORDER) )
		{
			// Special Handling for Boot Order variable change
	        Data = (UINT8*)EfiLibAllocateZeroPool( listbox->ItemCount * sizeof(UINT16) );
			for(i=0;i<listbox->ItemCount;i++)
				((UINT16*)Data)[i] = (UINT16)(listbox->PtrTokens[i].Value);
			callbackData->Length = listbox->ItemCount * sizeof(UINT16);
		}
		else
		{
			//EIP70966_START
			UINT32 sizeOfData = 0;
			UINTN type = 0;
			UINT8 *tempData = (UINT8 *)NULL;

			//To find the Type and Size of OrderList based on EFI_IFR_TYPE
			UefiGetValidOptionType(&listbox->ControlData, &type, &sizeOfData);

			Data = (UINT8*)EfiLibAllocateZeroPool( listbox->ItemCount * sizeOfData);
			tempData = Data;
			
			for(i=0;i<listbox->ItemCount;i++)
			{
				//Data[i] = (UINT8)(listbox->PtrTokens[i].Value);
				//Copy Data based on EFI_IFR_TYPE and Size
				MemCopy(tempData, &listbox->PtrTokens[i].Value, sizeOfData);
				tempData = (UINT8 *)tempData + sizeOfData;
			}
			//Fix the length of Data based on EFI_IFR_TYPE
			callbackData->Length = UefiGetMaxEntries(ifrData) * sizeOfData;
			if (callbackData->Length > (listbox->ItemCount * sizeOfData))			//EIP86885, Filling all the dynamic forming datas with 0's
			{
				Data = MemReallocateZeroPool (Data, (listbox->ItemCount * sizeOfData), callbackData->Length);
			}
			//EIP70966_END 
		}
		
		callbackData->Data = Data; //must send actual array of UINT8 values 
	}
	_UpdateOrderlistcount(listbox->ItemCount);										//Initializing gOrderlistcount
	UefiPreControlUpdate(&(listbox->ControlData));
	listbox->Callback( listbox->Container, listbox, listbox->Cookie );

		//For interactive orderedlist control invoke the callback functions
	if(UefiIsInteractive(&listbox->ControlData)){
		EFI_STATUS Status = EFI_SUCCESS;
		Status = CallFormCallBack(&listbox->ControlData, UefiGetControlKey(&listbox->ControlData), FALSE, AMI_CALLBACK_CONTROL_UPDATE);
	}
	//_OrdListGetSelection(listbox);

	if(Data!=NULL)
		MemFreePointer((VOID **)&Data);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxHandleAction
//
// Description:	Function to handle the ordered List Box actions
//
// Input:	ORD_LISTBOX_DATA *listbox, ACTION_DATA *Data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxHandleAction( ORD_LISTBOX_DATA *listbox, ACTION_DATA *Data)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT8 i=0;
    CONTROL_ACTION Action;


	if ( Data->Input.Type == ACTION_TYPE_TIMER )
	{
		// List box is active don't refresh
		if ( listbox->ListBoxCtrl != NULL )
			return Status;

		if (listbox->Interval == 0)
			return Status;

		if(IsActiveControlPresent(gApp->PageList[gApp->CurrentPage]))
			return Status;
		
		if ( --(listbox->Interval) == 0 )
		{
			// initialize the interval
			listbox->Interval = (UINT8)(listbox->ControlData.ControlFlags.ControlRefresh);
			return UefiRefershQuestionValueNvRAM(&(listbox->ControlData));
		}
		else
			return Status;
	}

    if(listbox->ControlData.ControlFlags.ControlReadOnly)
		return EFI_UNSUPPORTED;

	if(!listbox->ControlFocus)
		return Status;

	if(Data->Input.Type == ACTION_TYPE_MOUSE) //EIP74968 Change Order in Orderlist using Mouse drag
	{
		 if((listbox->Top <= (UINT16)Data->Input.Data.MouseInfo.Top ) &&  
			((listbox->Top + listbox->Height) > (UINT16)Data->Input.Data.MouseInfo.Top )&&
			(listbox->Left <= Data->Input.Data.MouseInfo.Left) &&
			((listbox->Left + listbox->Width) > (UINT16)Data->Input.Data.MouseInfo.Left) )
			Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);
	}

	if(Data->Input.Type == ACTION_TYPE_KEY)
    	Action = MapControlKeysHook(Data->Input.Data.AmiKey);

	if ( listbox->ListBoxCtrl != NULL )
	{
		Status = gListBox.HandleAction(listbox->ListBoxCtrl,Data);
		// special case, we need ot get the Sel from the listbox and put it into ordlistbox
        listbox->Sel = listbox->ListBoxCtrl->Sel;
		if ( listbox->ListBoxEnd )
		{
			gListBox.Destroy(listbox->ListBoxCtrl,TRUE);
			listbox->ListBoxCtrl = NULL;
			listbox->ListBoxEnd = FALSE;
			listbox->ControlActive = FALSE;
			DoOrdListCallBack(listbox);
		}
	}
	else
	{
		if(ControlActionSelect == Action)
        {
			if ( gListBox.Create( &(listbox->ListBoxCtrl) ) == EFI_SUCCESS )
			{
				UINT16 TempLength=0;

				listbox->ControlActive = TRUE; 
				gListBox.Initialize( listbox->ListBoxCtrl, &(listbox->ControlData) );
				//The next for loop should not be necessary after the callback
				//updates NVRAM properly
				//EIP70966 
				//if(TseLiteIsSpecialOptionList((CONTROL_DATA *)listbox) == TRUE) // EIP70966 -
				{
					for( i = 0 ; i < listbox->ItemCount; i++ )
					{
						listbox->ListBoxCtrl->PtrTokens[i] = listbox->PtrTokens[i].Option;
						TempLength = (UINT16)HiiMyGetStringLength( listbox->ListBoxCtrl->ListHandle, listbox->ListBoxCtrl->PtrTokens[i] );
						TempLength+=5; // to included barders
						if ( TempLength > listbox->ListBoxCtrl->Width )
							listbox->ListBoxCtrl->Width = TempLength;

					}
				}
				if ( listbox->Sel > (listbox->ItemCount-1) ) //EIP-127000 If selected item is suppresed then reset the focus to first item
					listbox->ListBoxCtrl->Sel = listbox->Sel = 0;
				else
					listbox->ListBoxCtrl->Sel = listbox->Sel;
				gListBox.SetCallback(listbox->ListBoxCtrl, listbox,  _OrdListBoxCallback, NULL);
				gListBox.Draw( listbox->ListBoxCtrl );
			} 

			Status = EFI_SUCCESS; 
		} 
	}

	if(Data->Input.Type == ACTION_TYPE_MOUSE && !lButtonOnListBoxScroll)//EIP74968 Change Order in Orderlist using Mouse drag && EIP-67049
	{
		if ( listbox->ListBoxCtrl != NULL )
		{
			Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);
		// Check if the Mouse action is on top of list box.
 		    if(
				(Data->Input.Data.MouseInfo.Top >= (UINT32)(listbox->ListBoxCtrl->Top - 1)) &&
				(ControlActionSelect != Action) &&
				(Data->Input.Data.MouseInfo.Top <= (UINT32)(listbox->ListBoxCtrl->Top + listbox->ListBoxCtrl->Height)) &&
				(Data->Input.Data.MouseInfo.Left >= listbox->ListBoxCtrl->Left) &&
				(Data->Input.Data.MouseInfo.Left <= (UINT32)(listbox->ListBoxCtrl->Left + listbox->ListBoxCtrl->Width - 1))
				) 
			{	
				//Note MOUSE_LEFT_DOWN position
				if(Action==ControlMouseActionLeftDown)
				{
					if(FirstDownEvent == FALSE )
					{
						if(Data->Input.Data.MouseInfo.Top == (UINT32)(listbox->ListBoxCtrl->Top + listbox->Sel - listbox->ListBoxCtrl->FirstVisibleSel + 1))	
							FirstDownEvent = TRUE;
					}
					else
					{
						if(Data->Input.Data.MouseInfo.Top > (UINT32)(listbox->ListBoxCtrl->Top + listbox->Sel - listbox->ListBoxCtrl->FirstVisibleSel + 1))	
							Action = ControlActionDecreament;
					
						if(Data->Input.Data.MouseInfo.Top < (UINT32)(listbox->ListBoxCtrl->Top + listbox->Sel - listbox->ListBoxCtrl->FirstVisibleSel + 1))	
							Action = ControlActionIncreament;
					}				
				}
				else
				{
					FirstDownEvent = FALSE;
				}
			}
		}
	}
    switch ( Action )
	{
        case ControlActionDecreament:
			// eip : B12674  Don't allow +/- until it is selected.
			if ( listbox->ListBoxCtrl != NULL ) 
			{
	        	if(!EFI_ERROR(_OrdListBoxShift(listbox, FALSE)))
	        	{
	        		if ( (INTN)(listbox->Sel) < listbox->ItemCount - 1 )
	        			listbox->Sel++;
	        	}
	        	Status = EFI_SUCCESS;
			}
        break;
        
        case ControlActionIncreament:
			// eip : B12674  Don't allow +/- until it is selected.
			if ( listbox->ListBoxCtrl != NULL )
			{
	        	if(!EFI_ERROR(_OrdListBoxShift(listbox, TRUE)))
	        	{
	        		if ( listbox->Sel > 0 )
	        			listbox->Sel--;
	        	}
	        	Status = EFI_SUCCESS;
			}
        break;
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxSetCallback
//
// Description:	Function to set callback for ordered List Box 
//
// Input:	ORD_LISTBOX_DATA *listbox, OBJECT_DATA *container,   OBJECT_CALLBACK callback, VOID *cookie
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxSetCallback( ORD_LISTBOX_DATA *listbox, OBJECT_DATA *container,   OBJECT_CALLBACK callback, VOID *cookie )
{
	return gPopupSel.SetCallback( listbox, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxSetFocus
//
// Description:	Function to set focus for ordered List Box 
//
// Input:	ORD_LISTBOX_DATA *listbox, BOOLEAN focus
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxSetFocus(ORD_LISTBOX_DATA *listbox, BOOLEAN focus)
{
	return gPopupSel.SetFocus(listbox,focus);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxSetPosition
//
// Description:	Function to set position for ordered List Box 
//
// Input:	ORD_LISTBOX_DATA *listbox, UINT16 Left, UINT16 Top
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxSetPosition(ORD_LISTBOX_DATA *listbox, UINT16 Left, UINT16 Top )
{
	return gPopupSel.SetPosition( listbox, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxSetDimensions
//
// Description:	Function to set dimension for ordered List Box 
//
// Input:	ORD_LISTBOX_DATA *listbox, UINT16 Width, UINT16 Height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxSetDimensions(ORD_LISTBOX_DATA *listbox, UINT16 Width, UINT16 Height )
{
	return gPopupSel.SetDimensions( listbox, Width, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListBoxSetAttributes
//
// Description:	Function to set atributes for ordered List Box 
//
// Input:	ORD_LISTBOX_DATA *listbox, UINT8 FGColor, UINT8 BGColor
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListBoxSetAttributes(ORD_LISTBOX_DATA *listbox, UINT8 FGColor, UINT8 BGColor )
{
	return gPopupSel.SetAttributes( listbox, FGColor, BGColor );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_OrdListBoxCallback
//
// Description:	Ordered List Box callback function
//
// Input:	ORD_LISTBOX_DATA *container, CONTROL_DATA *listbox, VOID *cookie
//
// Output:	VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _OrdListBoxCallback( ORD_LISTBOX_DATA *container, CONTROL_DATA *listbox, VOID *cookie )
{
	container->ListBoxEnd = TRUE;
	if ( cookie != NULL )
		container->Sel = *((UINT16*)cookie);
}

/*
	Please note that the following function is non-rotatary or non-circular
	This is an internal function to ordered list control,so we need to:
	   1-add underscore to the name 
	   2-do not put it in control_methods
	This function is not used by any one else outside the control.
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_OrdListBoxShift
//
// Description:	Function used in OrdListBoxHandleAction to handle actions
//
// Input:	ORD_LISTBOX_DATA *listbox, UINT8 bShiftUp
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _OrdListBoxShift(ORD_LISTBOX_DATA *listbox, UINT8 bShiftUp)
{	
	PTRTOKENS  unSwap;
	UINT8 i=0;

	if(TRUE == bShiftUp)
	{
		//move up
		if ( listbox->Sel > 0 )
		{
			unSwap = listbox->PtrTokens[listbox->Sel];
			listbox->PtrTokens[listbox->Sel] = listbox->PtrTokens[listbox->Sel-1];
			listbox->PtrTokens[listbox->Sel-1] = unSwap;
			if( listbox->ListBoxCtrl !=NULL)
			{
				// update string tokens into listbox area
				for( i = 0 ; i < listbox->ItemCount; i++ )
					listbox->ListBoxCtrl->PtrTokens[i] = listbox->PtrTokens[i].Option;
				listbox->ListBoxCtrl->Sel--;
				gPopupSel.Draw(listbox);
		    }
			return EFI_SUCCESS;
		}
	}
	else
	{
		//move dn
		if ( (INTN)(listbox->Sel) < listbox->ItemCount - 1 )
		{
			unSwap = listbox->PtrTokens[listbox->Sel];
			listbox->PtrTokens[listbox->Sel] = listbox->PtrTokens[listbox->Sel+1];
			listbox->PtrTokens[listbox->Sel+1] = unSwap;
			if( listbox->ListBoxCtrl !=NULL)
			{	// update string tokens into listbox area
				for( i = 0 ; i < listbox->ItemCount; i++ )
					listbox->ListBoxCtrl->PtrTokens[i] = listbox->PtrTokens[i].Option;
				listbox->ListBoxCtrl->Sel++;
				gPopupSel.Draw(listbox);
			} 

			return EFI_SUCCESS;
		}
	}

	return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	OrdListGetControlHeight
//
// Description:	Function used get the hight of control
//
// Input:	ORD_LISTBOX_DATA *OrdList, VOID* frame, UINT16 *height
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS OrdListGetControlHeight( ORD_LISTBOX_DATA *OrdList, VOID* frame, UINT16 *height )
{
	//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
	if(IsTSEMultilineControlSupported())
	{
		CHAR16 *newText = NULL,*text=NULL;
		UINT16 Width;
	
		Width = (UINT16)(OrdList->LabelMargin - (((FRAME_DATA*)frame)->FrameData.Left + (UINT8)gLabelLeftMargin));
	
		text = HiiGetString( OrdList->ControlData.ControlHandle, OrdList->Title );
		if ( text == NULL )
			return EFI_OUT_OF_RESOURCES;
	
		newText = StringWrapText( text, Width, height );
	
	    (*height) = (*height) ? (*height):1;
	
	    MemFreePointer( (VOID **)&newText );
		MemFreePointer( (VOID **)&text );

    	*height = (*height < OrdList->ItemCount)? OrdList->ItemCount : *height ;
	}
	else
	{
		*height = 1;
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_OrdListMultiLIneDraw
//
// Description:	Function used to draw teh Ordered list box
//
// Input:	ORD_LISTBOX_DATA *OrdList
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _OrdListMultiLIneDraw(ORD_LISTBOX_DATA *OrdList)
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 ColorNSel = OrdList->NSelFGColor;
	UINT8 ColorLabel = (OrdList->ControlFocus) ? OrdList->LabelFGColor : OrdList->NSelLabelFGColor ;
  	CHAR16 *text1, *text;
	UINTN i=0,Len, oldSize = 0;
	BOOLEAN MultilineSupport = FALSE;
	UINT16 *OptionList=NULL, Index = 0;
	UINT64 *ValueList=NULL;

    //Draw the list box alone if the control is active
	if(  OrdList->ListBoxCtrl != NULL)
	{
		gListBox.Draw( OrdList->ListBoxCtrl );
	}
	else
	{
		// check conditional
        //EIP 75486 Support grayout condition for readonly controls
		//if( OrdList->ControlData.ControlConditionalPtr != 0x0)
		//{
			switch( CheckControlCondition( &OrdList->ControlData ) )
			{
				case COND_NONE:
					break;
				case COND_GRAYOUT:
					Status = EFI_WARN_WRITE_FAILURE;
					ColorNSel =  ColorLabel = CONTROL_GRAYOUT_COLOR;
					break;
				default:
					return EFI_UNSUPPORTED;
					break;
			}
		//}
			if(TseLiteIsSpecialOptionList((CONTROL_DATA *)OrdList) != TRUE) //EIP-127000 Fix options and option count in listbox if any item is suppressed
			{
				oldSize = OrdList->ItemCount;

				Status = UefiGetOneOfOptions(&OrdList->ControlData,&OrdList->PopupSelHandle,
					&OptionList, &ValueList, &OrdList->ItemCount,NULL,NULL);

				if (OrdList->ItemCount!=oldSize)
				{
					OrdList->PtrTokens = MemReallocateZeroPool(OrdList->PtrTokens, oldSize*sizeof(PTRTOKENS), OrdList->ItemCount * sizeof(PTRTOKENS));
					if (NULL == OrdList->PtrTokens)
						return EFI_OUT_OF_RESOURCES;
				}

				if (EFI_ERROR(Status))
					return Status;
				for( Index = 0; Index < OrdList->ItemCount; Index++ )
				{
					OrdList->PtrTokens[Index].Option = OptionList[Index];
					OrdList->PtrTokens[Index].Value = ValueList[Index];
				}
				MemFreePointer( (VOID **)&(OptionList));
				MemFreePointer( (VOID **)&(ValueList));
			}
        _OrdListGetSelection(OrdList); //EIP70966 To handle OrderList Items
		//_PopupSelGetSelection((POPUPSEL_DATA *)OrdList);

        //Draw label in left column
		text1 = HiiGetString( OrdList->ControlData.ControlHandle, OrdList->Title );
		if ( text1 != NULL )
		{
			//EIP-72610 TSE_MULTILINE_CONTROLS moved to binary
			if(OrdList->Height>1 && IsTSEMultilineControlSupported())
			{
				DrawMultiLineStringWithAttribute( OrdList->Left, OrdList->Top, 
						(UINTN)(OrdList->LabelMargin - OrdList->Left),(UINTN) OrdList->Height,
						text1, OrdList->BGColor |  ColorLabel );
			}
			else
			{
	            // boundary overflow  check
				if((TestPrintLength( text1) / (NG_SIZE))> (UINTN)(OrdList->LabelMargin - OrdList->Left  ))
					text1[HiiFindStrPrintBoundary(text1 ,(UINTN)(OrdList->LabelMargin - OrdList->Left  ))] = L'\0';
	
				DrawStringWithAttribute( OrdList->Left , OrdList->Top, (CHAR16*)text1, 
						OrdList->BGColor |  ColorLabel  );
			}	
	
			MemFreePointer( (VOID **)&text1 );
		}
		if(IsTSEMultilineControlSupported()) //TSE_MULTILINE_CONTROLS moved to binary
			MultilineSupport = TRUE;

        do
		{
            text1 = HiiGetString( OrdList->PopupSelHandle, OrdList->PtrTokens[i].Option);

			if(!text1) //EIP-70966 To handle NULL items in orderlistbox
				text1 = EfiLibAllocateZeroPool(2);

            Len = TestPrintLength( text1 ) / (NG_SIZE);
            if ( Len > (UINTN)(OrdList->Width - OrdList->Left - OrdList->LabelMargin -2) )
			    EfiStrCpy(&text1[HiiFindStrPrintBoundary(text1 ,(UINTN)(OrdList->Width - OrdList->Left - OrdList->LabelMargin -4))],L"..." );

            //Enclose the string with [ ]
            text = EfiLibAllocateZeroPool( (Len+3)*2 );
            SPrint( text,(UINTN)( (Len+3)*2 ), L"[%s]", text1 );
            MemFreePointer( (VOID **)&text1 );

            DrawStringWithAttribute(
                        OrdList->Left + OrdList->LabelMargin,
                        OrdList->Top+i,
                        (CHAR16*)text,
                        (UINT8)(OrdList->ControlFocus ? OrdList->SelBGColor|OrdList->SelFGColor : OrdList->BGColor|ColorNSel)
                        );
			i++;
        }while(i<OrdList->ItemCount && MultilineSupport);

  		/*
        i=TestPrintLength(text) / (NG_SIZE);
        MemFreePointer( (VOID **)&text );

        // erase extra spaces if neccessary
		for(;(UINT16)(popupSel->Left + popupSel->LabelMargin + i+2) <= (popupSel->Width-1);i++)
			DrawStringWithAttribute( popupSel->Left + popupSel->LabelMargin +i +2 , popupSel->Top, L" ", 
						 popupSel->BGColor  |  ColorNSel );
        */

		FlushLines( OrdList->Top, OrdList->Top+i-1 );
	}

	return Status;
}

// EIP70966_START
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   _OrdListGetSelection
//
// Description: Function to ordering the option in OrderList
//
// Input:	ORD_LISTBOX_DATA *ordlist
//
// Output:	
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _OrdListGetSelection( ORD_LISTBOX_DATA *ordlist )
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT8 *temp=NULL;
	VOID *ifrData = ordlist->ControlData.ControlPtr;
	int i=0,j=0;
    PTRTOKENS		*OrdPtrTokens=NULL, TempOrdPtrTokens;



	UINT32 sizeOfData = 0;
	UINTN type = 0;
	UINTN dataLen = 0;
	//Find the size of OrderList based on EFI_IFR_TYPE of EFI_IFR_ONE_OF_OPTION
//	UefiGetValidOptionSize(&ordlist->ControlData, &sizeOfData);
//	dataLen = ordlist->ItemCount * sizeOfData;
    
	UefiGetValidOptionType(&ordlist->ControlData, &type, &sizeOfData);
	dataLen = UefiGetMaxEntries(ifrData) * sizeOfData;

	temp = EfiLibAllocateZeroPool( dataLen  );
	if ( temp == NULL )
		return;

    OrdPtrTokens = ordlist->PtrTokens;
    
    Status = VarGetValue( ordlist->ControlData.ControlVariable, UefiGetQuestionOffset(ifrData), dataLen, temp );

    // Check variable data and adjust item order.
	if ( Status == EFI_SUCCESS )
	{
        for (i=0 ; i<ordlist->ItemCount-1 ; i++)
        {
            for (j=i+1 ; j<ordlist->ItemCount ; j++)
            {
                if ( MemCmp( (VOID *)&(OrdPtrTokens[j].Value),(VOID *)(temp + (i * sizeOfData)), sizeOfData ) == 0)
                {
                    TempOrdPtrTokens = OrdPtrTokens[i];
                    OrdPtrTokens[i] = OrdPtrTokens[j];
                    OrdPtrTokens[j] = TempOrdPtrTokens;
                    break;
                }
            }
        }
	}
	MemFreePointer( (VOID **)&temp );

}
// EIP70966_END

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
