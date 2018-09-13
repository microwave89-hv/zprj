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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Menu.c $
//
// $Author: Premkumara $
//
// $Revision: 26 $
//
// $Date: 3/14/13 11:47a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/Menu.c $
// 
// 26    3/14/13 11:47a Premkumara
// [TAG]  		EIP85745 & 109814 
// [Category]  	Improvement
// [Description]  	Support for Modal Form Support as per UEFI 2.3.1
// [Files]  		Parse.c, Page.c, Menu.c, Hotclick.c
// 
// 25    10/19/12 5:06a Rajashakerg
// Provided support for menu scroll for only action choose and select.
// 
// 24    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 14    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 22    9/25/12 12:31p Rajashakerg
// [TAG]  		EIP92053 
// [Category]  	Improvement
// [Description]  	Need support define Root page order using elinks
// [Files]  		AMITSE.sdl, Menu.c, AMIVfr.h, AMITSE.mak, commonoem.c
// 
// 21    9/25/12 9:33a Rajashakerg
// [TAG]  		EIP92053 
// [Category]  	Improvement
// [Description]  	Need support define Root page order using elinks
// [Files]  		AMITSE.sdl, Menu.c, AMIVfr.h, AMITSE.mak, commonoem.c
// 
// 20    12/01/11 1:43a Premkumara
// [TAG]  		EIP73236
// [Category]  	Improvement
// [Description]  	Large amounts of allocated memory are not freed
// [Files]  		Expression.c, PopupEdit.c, Popup.c, MessageBox.c, Menu.c,
// Memo.c,
// 
// 19    11/21/11 8:53a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupSel.c, PopupString.c, SubMenu.c, Text.c.
// 
// 18    11/14/11 6:55p Blaines
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
// 17    11/09/11 6:05p Blaines
// [TAG]  		EIP 72333
// [Category]  	Sighting
// [Symptom]  	Some SAS controller card HII Screen Titles are displaying
// the wrong information
// 
// [RootCause]  	Menu tab always displays the root page title when
// navigating submenu pages. TSE did not support the display of Formset
// Help. 
// 
// [Solution]	Display Formset Help for Dynamic page, Display page title of
// submenu pages in the menu tab. Fix the ASSERT seen in Menu.c when
// serial redirection is enabled.
// 
// [Files Changed] - AMITSE.sdl, CommonHelper.c, special.c, Menu.c,
// minisetupext.h,TseUefiHii.h, Uefi21Wapper.c
// 
// 16    10/31/11 2:44a Rajashakerg
// [TAG]  		EIP73377
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Setup page Menu tab gets selected even when the click is
// below the menu separator line
// [RootCause]  	Menu tab selection was not handled properly using mouse.
// [Solution]  	Provided exact menu tab co-ordinates for selection using
// mouse
// [Files]  		Menu.c
// 
// 15    10/21/11 6:26p Blaines
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
// 14    10/20/11 12:03p Madhans
// Checkin comments corrected.
// 
// 12    10/04/11 5:28p Blaines
// [TAG]  		EIP 68920
// [Category]  	Defect
// [Symptom]  	SOME SAS controller card HII menus hang when selecting "Clear
// Configuration" when DEBUG_MODE=0
// [RootCause]  	Menu is not re-initialize from SetupData after dynamic
// page update. MenuInitialize enters an infinite loop on some SAS controller cards.
// 
// 
// PopupSelGetControlHeight() causes an assert if popupSel has an item
// with an invalid string token.  
// 		
// [Solution]	Due to dynamic updates, SetupData (most current data) is
// given priority when re-initializing menu. 
// Check for invalid string token in PopupSelGetControlHeight.		
// 
// [Files Changed]
// - Menu.c, Popupsel.c
// 
// 11    9/19/11 11:50a Blaines
// [TAG]  		EIP 68920
// [Category]  	Defect
// [Symptom]  	SOME SAS controller card menus hang when selecting "Clear
// Configuration" when DEBUG_MODE=0
// [RootCause]  	Menu is not re-initialize from SetupData after dynamic
// page update. 
// PopupSelGetControlHeight() causes an assert if popupSel has an item
// with an invalid string token.  
// 		
// [Solution]	Due to dynamic updates, SetupData (most current data) is
// given priority when re-initializing menu. 
// Check for invalid string token in PopupSelGetControlHeight.		
// 
// [Files Changed]
// - Menu.c, Popupsel.c
// 
// 10    8/26/11 4:10p Blaines
// [TAG] - EIP 68341
// [Category]- Action Item
// [Synopsis]- Dynamic Pages need to List FormSet title instead of Form
// Title..
// [Files] - Parse.c, Menu.c 
// 
// 9     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 8     6/15/10 10:49a Blaines
// Fix for EIP:39570: Adding to length may create additional pages to
// accommodate extra space.
// 
// 7     5/24/10 11:11a Mallikarjunanv
// EIP-38215: Fix for Setup corruption issue with mouse
// 
// 6     5/24/10 11:02a Mallikarjunanv
// EIP-38555 : Spacing issue in Menu display
// 
// 5     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 7     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 6     2/15/10 10:15p Madhans
// To support root page hiding based on page flag
// 
// 5     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 4     1/09/10 6:38a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
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
// 2     5/07/09 10:36a Madhans
// Changes after Bin module
// 
// 1     4/28/09 11:05p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:09p Madhans
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
// Name:		Menu.c
//
// Description:	This file contains code to handle Menu operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
extern BOOLEAN gIsRootPageOrderPresent;

MENU_METHODS gMenu =
{
	MenuCreate,
	MenuDestroy,
	MenuInitialize,
	MenuDraw,
	MenuHandleAction,
	MenuSetCallback,
	MenuSetFocus,
	MenuSetPosition,
	MenuSetDimensions,
	MenuSetAttributes,
	MenuGetControlHight,
	MenuSetWidth
	
};

#define ItemPerPage 6
typedef struct _HII_FORM_ADDRESS
{
	EFI_GUID formsetGuid; // Required
	UINT16		formId;	// Required
	VOID *		Handle;	// Optional
}HII_FORM_ADDRESS;
extern UINT16 gRootPageOrderIndex;
extern HII_FORM_ADDRESS *gRootPageOrder;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuCreate
//
// Description:	Function to create Menu, Which uses the control functions.
//
// Input:	MENU_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuCreate( MENU_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(MENU_DATA) );

		if ( *object == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Status = gControl.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gMenu;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuDestroy
//
// Description:	Function to Destroy Menu, Which uses the control functions.
//
// Input:	MENU_DATA *menu, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuDestroy( MENU_DATA *menu, BOOLEAN freeMem )
{
	if(NULL == menu)
	  return EFI_SUCCESS;

	gControl.Destroy( menu, FALSE );

    if( freeMem ){
        MemFreePointer( (VOID **)&menu->Entries);//EIP-73236
		MemFreePointer( (VOID **)&menu );
    }

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuInitialize
//
// Description:	Function to Initialize Menu, Which uses the control functions.
//
// Input:	MENU_DATA *menu, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuInitialize( MENU_DATA *menu, VOID *data )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
    UINT16 i,j=0,k=0;
	PAGE_INFO *info,*tempPage=NULL;
	UINT32 count = 0 ,PageCount=0;

   // data is NULL when only reinitialization of the menu entries is needed.
   // this assumes the control was initialized before.
   if(data !=NULL)
   {
	Status = gControl.Initialize( menu, data );
	if (EFI_ERROR(Status))
		return Status;
   }
	menu->IsSubMenu = 0;
	// add extra initialization here...
	if(menu->Entries !=NULL)
	{
		gBS->FreePool(menu->Entries);
	    menu->Entries =NULL;
		menu->NumEntries=menu->CurrEntry=0;
	}

	menu->Entries = EfiLibAllocateZeroPool( sizeof(AMI_MENU_ENTRY) *(gPages->PageCount) );
	count = ( gPages->PageCount > gApp->PageCount ) ? gPages->PageCount : gApp->PageCount ;

	if(gIsRootPageOrderPresent)
	{
		//for( k=0 ; (gRootPageOrder[k] != 0); k++ );
		for( j=0 ; j < gRootPageOrderIndex ; j++ )
		{
			for ( i = 0; i < (UINT16)count; i++ )
			{
				if(i > gPages->PageCount )
				{
					if(gApp->PageList[i] == NULL)
						continue;
					info = (PAGE_INFO*)&( gApp->PageList[i]->PageData);
					PageCount = gApp->PageCount;
				}
				else
				{
					info = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[i]);
		            PageCount = gPages->PageCount;	     
				} 
	
				if( (info->PageHandle == NULL ) || (info->PageHandle == (VOID*)(UINTN)0xffff ))
					continue;
				
				if (!( info->PageID  == 0) && (info->PageParentID == 0) &&
						(gRootPageOrder[j].formId == info->PageFormID) )
				{
					PAGE_ID_INFO *pageIdInfo;
					pageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[info->PageIdIndex]);

					if(gRootPageOrder[j].Handle)
						if(gRootPageOrder[j].Handle != info->PageHandle)
							continue;

					if(!EfiCompareGuid(&pageIdInfo->PageGuid, &gRootPageOrder[j].formsetGuid) )//Compare Guid
					{
						continue;
					}

					if(info->PageFlags.PageVisible)
						continue; //To Control the root page not to show.
	
				   menu->Entries[menu->NumEntries].PageHandle = info->PageHandle;
				   menu->Entries[menu->NumEntries].PageID = info->PageID;
			       menu->Entries[menu->NumEntries].StringToken = info->PageSubTitle;
	
				   if( menu->ControlData.ControlPageID == info->PageID )
	                   menu->CurrEntry = menu->NumEntries;
	
				   if(menu->Entries[menu->NumEntries].PageHandle != 0)
	 			   menu->NumEntries++;
				}
					
			
			}
		}
	}

	for ( i = 0; i < (UINT16)count; i++ )
	{
		// EIP 68920: Due to dynamic updates, SetupData (most current data)  
        // is given priority when re-initializing menu. 
        if(i > gPages->PageCount )
		{
			if(gApp->PageList[i] == NULL)
				continue;
			info = (PAGE_INFO*)&( gApp->PageList[i]->PageData);
			PageCount = gApp->PageCount;
		}
		else
		{
			info = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[i]);
            PageCount = gPages->PageCount;	     
		} 

	   if( (info->PageHandle == NULL ) || (info->PageHandle == (VOID*)(UINTN)0xffff ))
			continue;

       if( info->PageID  == 0)
	   {
	   }
	   else
	   {
		   if((info->PageParentID ==0) /*&& (info->PageFlags.PageVisible)*/)
		   {
	   			if(info->PageFlags.PageVisible ||  gIsRootPageOrderPresent)
					continue; //To Control the root page not to show.

			   menu->Entries[menu->NumEntries].PageHandle = info->PageHandle;
			   menu->Entries[menu->NumEntries].PageID = info->PageID;
		       menu->Entries[menu->NumEntries].StringToken = info->PageSubTitle;

			   if( menu->ControlData.ControlPageID == info->PageID )
                   menu->CurrEntry = menu->NumEntries;

			   if(menu->Entries[menu->NumEntries].PageHandle != 0)
 			   menu->NumEntries++;              
		       
		   }
		   else
		   {
			   if( menu->ControlData.ControlPageID == info->PageID )
			   {  
				   tempPage =info;
				   while(tempPage->PageParentID!=0)
				   {
					   for(j=0;j < PageCount;j++)
					   {

                            // EIP 68920: Due to dynamic updates, SetupData (most current data)  
                            // is given priority when re-initializing menu. 
                            if(j < gPages->PageCount)
							{
								if( tempPage->PageParentID == ((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[j]))->PageID) 
								{   
									menu->IsSubMenu = 1;
									tempPage =((PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[j]));
                               			j=0;
									if(tempPage->PageParentID ==0)
										break;
							   
							   }
								
							}
						   else
						   {
                                if(gApp->PageList[j] == NULL)
									continue;								

                                if( tempPage->PageParentID == gApp->PageList[j]->PageData.PageID) 
								{   
									menu->IsSubMenu = 1;
									tempPage =&(gApp->PageList[j]->PageData);
                               			j=0;
									if(tempPage->PageParentID ==0)
										break;
							   
							   }

						   }
					   }
				   }

				   // find the item number for the parent in the menu 
				   for(j=0;j<menu->NumEntries;j++)
				   {
					   if( (tempPage !=NULL) && ( tempPage->PageID == menu->Entries[j].PageID) )
					   {
						   menu->CurrEntry =  j;
						   break;
					   }
				   }
			   }

		   }
	   }
	}
	
	menu->ControlData.ControlHelp = UefiGetHelpField((VOID *)menu->ControlData.ControlPtr);
	menu->ControlFocus = FALSE;

	// initialize default colors
	SetControlColorsHook(NULL, NULL,
						&(menu->SelFGColor),&(menu->SelBGColor),
						NULL, NULL,
			            NULL, NULL,
						NULL,NULL, 
						NULL,
						NULL ,NULL, 
						&(menu->FGColor),&(menu->BGColor));
	
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuDraw
//
// Description:	Function to draw a Menu.
//
// Input:	MENU_DATA *menu
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuDraw( MENU_DATA *menu )
{
	CHAR16 *text=NULL, *tmp=NULL;
	UINTN offset=0,length;
	UINT16 StartItem=0,PageNum=0,ActualPage=0,ItemsInPage=0,ItemFound=0,k=0;
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 ColorMenu = menu->FGColor;
	UINT8 Pos=(UINT8) menu->Left;
	UINT16 i=0,j=0;
    PAGE_DATA *Page ;
    BOOLEAN Overflow = FALSE ;
    
    Page = gApp->PageList[gApp->CurrentPage];
   

	//erase menu line
	for(i=1;i <= /*MAX_COLS*/menu->MenuWidth; i++, Pos++ )
  	   DrawStringWithAttribute( Pos , menu->Top,L" ",menu->BGColor | menu->FGColor );
		
	// check conditional ptr if necessary
    //EIP 75486 Support grayout condition for readonly controls
	//if( menu->ControlData.ControlConditionalPtr != 0x0)
	//{
		switch( CheckControlCondition( &menu->ControlData ) )
		{
			case COND_NONE:
				break;
			case COND_GRAYOUT:
				Status = EFI_WARN_WRITE_FAILURE;
				ColorMenu = CONTROL_GRAYOUT_COLOR;
				break;
			default:
				return EFI_UNSUPPORTED;
				break;
		}
	//}

	tmp = EfiLibAllocateZeroPool( 256 );
	if ( tmp == NULL )
		return EFI_OUT_OF_RESOURCES;

	Pos = (UINT8)menu->Left;

	//loop to find which menu entries to draw
    for( k = 0 ; k < menu->NumEntries ; k++ )
	{
        //get string from hii
		text = HiiGetString(menu->Entries[k].PageHandle , menu->Entries[k].StringToken );
		if ( text == NULL )
			return EFI_OUT_OF_RESOURCES;

        length = (UINT16)((TestPrintLength( text ) / (NG_SIZE)) + 2); // take in account added space on either side of menu below.

        //EIP:68341 Dynamic pages may contain lengthy FormSet Title strings, truncate if necessary.     
		//EIP# 72333, Display page title of submenu pages in the menu tab.
        if(length >(UINTN) (menu->MenuWidth-2) )
        {
				EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(menu->MenuWidth-5))],L"...");
                length = menu->MenuWidth-2 ;
        }

        //EIP:39570 Adding to length may create additional pages to accommodate extra space. 
        if ((offset + length /*+2*/) >= /*MAX_COLS*/(UINTN)(menu->MenuWidth-2))
		{
            PageNum ++;	
	        if(!ItemFound)
			{
                ActualPage++;
                StartItem = k;
			    ItemsInPage=0;
				offset=length+2;
			}
			else
			{
				MemFreePointer( (VOID **)&text );
				break;
			}
	    }
	    else
	      offset += length /*+2*/; 

	    if(k == menu->CurrEntry)
	       ItemFound=1;

	    ItemsInPage++;
	    MemFreePointer( (VOID **)&text );
    }

    menu->StartItem = StartItem;
    menu->ActualPage = ActualPage;
    menu->PageNum = PageNum;
    menu->ItemsInPage = ItemsInPage;

	if(ActualPage > 0 )
	{
       if(!( menu->IsSubMenu ))
	   {
		SPrint( tmp, 6, L"%c ", GEOMETRICSHAPE_LEFT_TRIANGLE );
	    DrawStringWithAttribute( menu->Left, menu->Top ,tmp, menu->BGColor | menu->FGColor );
	   }
		//Pos += 2;
	} 
    Pos += 1;  // always leave space for the arrow even if it is not drawn
    j = (UINT16)StartItem;
    
	for(i=0;(i < ItemsInPage) && ( i+j < menu->NumEntries) ;i++)
	{
		UINTN StrPrntLen=0;	//to fill with the length of the string to draw. 

		//get string from hii

        //EIP# 72333, Display page title of submenu pages in the menu tab.
        if ( i+j == menu->CurrEntry && menu->IsSubMenu && IsSubMenuDisplayTitle())
		{
            text = HiiGetString(Page->PageData.PageHandle, Page->PageData.PageSubTitle );
        }
        else
        {
		    text = HiiGetString(menu->Entries[i+j].PageHandle , menu->Entries[i+j].StringToken );
        }

		if ( text == NULL )
			return EFI_OUT_OF_RESOURCES;

		length = (UINT16)(TestPrintLength( text ) / (NG_SIZE));

        //EIP:68341 Dynamic pages may contain lengthy FormSet Title strings, truncate if necessary.
        //EIP# 72333, Display page title of submenu pages in the menu tab.
        if( (Pos-2+length) >(UINTN) (menu->MenuWidth-2) )
        {
				EfiStrCpy( &text[HiiFindStrPrintBoundary(text,(menu->MenuWidth-5-Pos-2))],L"...");
                length = menu->MenuWidth-2 ;
                Overflow = TRUE ;
        }

		// the size of the string plus additional characters(2 spaces + Null character)
		StrPrntLen = length+3;
		// The Menu title length should be less than Max display size.
		if(length >= gMaxCols) {
			StrPrntLen = gMaxCols-2;
		}

		// print the string for the lenth uptained
		SPrint( tmp, StrPrntLen*sizeof(CHAR16), L" %s ", text );
		if ( i+j == menu->CurrEntry )
		{
			DrawStringWithAttribute( Pos , menu->Top , tmp, menu->SelFGColor | menu->SelBGColor);
			Pos += 2+(UINT8)length;
		}	
		else
		{
			if( !(menu->IsSubMenu))
			   DrawStringWithAttribute( Pos , menu->Top, tmp, menu->BGColor | menu->FGColor );
			Pos += 2+(UINT8)length;
		}
		MemFreePointer( (VOID **)&text );

        if(Overflow)
            break ;
	}

	if( (ActualPage < PageNum) && !(menu->IsSubMenu))
	{
        SPrint( tmp, 6, L"%c",GEOMETRICSHAPE_RIGHT_TRIANGLE );
	    DrawStringWithAttribute( gMaxCols-1, menu->Top ,tmp, menu->BGColor | menu->FGColor );
	}

	MemFreePointer( (VOID **)&tmp );
	FlushLines( menu->Top, menu->Top );

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_MenuCallCallback
//
// Description:	Internal Helper Function to Call the callback
//
// Input:		MENU_DATA *menu, UINT8 MenuEntry
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID _MenuCallCallback(MENU_DATA *menu,UINT16 MenuEntry)
{
    if ( ( menu->Callback != NULL ) && (menu->Cookie != NULL) )
    {
        CALLBACK_MENU *callbackData = (CALLBACK_MENU *)menu->Cookie;
        callbackData->DestPage = menu->Entries[MenuEntry].PageID;
        menu->Callback( menu->Container, menu, menu->Cookie );
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuHandleAction
//
// Description:	Function to handle actions.
//
// Input:		MENU_DATA *menu, ACTION_DATA *Data
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuHandleAction( MENU_DATA *menu, ACTION_DATA *Data)
{
	// control is in separate frame for ezport.
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 TempEntry;
    PAGE_DATA *page = NULL ;
    page = gApp->PageList[gApp->CurrentPage];


	if ( Data->Input.Type == ACTION_TYPE_TIMER )
		return Status;
    if(!page){
          return Status; 
    }
    if(page->PageData.PageFlags.PageModal){
          return Status; 
    }
    if(Data->Input.Type == ACTION_TYPE_MOUSE)
    {
		Status = MouseMenuHandleAction( menu, Data );
    }

	if ( Data->Input.Type == ACTION_TYPE_KEY )
	{
        CONTROL_ACTION Action;

        //Get mapping
        Action = MapControlKeysHook(Data->Input.Data.AmiKey);

        switch(Action)
		{
            case ControlActionNextLeft:
			    if(!(menu->IsSubMenu))
			    {
					if ( menu->CurrEntry > 0 )
						TempEntry = menu->CurrEntry - 1;
					else
    					TempEntry = menu->NumEntries - 1;

					_MenuCallCallback(menu,TempEntry);
			    }
                Status = EFI_SUCCESS;
			break;

			case ControlActionNextRight:
                if(!(menu->IsSubMenu))
                {
				    if ( menu->CurrEntry < menu->NumEntries - 1 )
				        TempEntry = menu->CurrEntry + 1;
					else
					    TempEntry = 0;

					_MenuCallCallback(menu,TempEntry);
                }				
                Status = EFI_SUCCESS;
            break;

			default:
			break;
		} 
	}

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuSetCallback
//
// Description:	Function to set callback.
//
// Input:		MENU_DATA *menu, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuSetCallback( MENU_DATA *menu, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gControl.SetCallback( menu, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuSetFocus
//
// Description:	Function to set focus.
//
// Input:		MENU_DATA *menu, BOOLEAN focus
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuSetFocus(MENU_DATA *menu, BOOLEAN focus)
{

	if( !(menu->ControlFocus && focus) )
		menu->ControlFocus = focus;
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuSetPosition
//
// Description:	Function to set position.
//
// Input:		MENU_DATA *menu, UINT16 Left, UINT16 Top
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuSetPosition(MENU_DATA *menu, UINT16 Left, UINT16 Top )
{
	// Width -> is the container frame width the menu width is that minus 2 spaces.
	// Left and rigth menu spaces will contain arrows in case that there are multiple pages for the menu.
	return gControl.SetPosition( menu, Left, Top );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuSetDimensions
//
// Description:	Function to set dimension.
//
// Input:		MENU_DATA *menu, UINT16 Width, UINT16 Height
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuSetDimensions(MENU_DATA *menu, UINT16 Width, UINT16 Height )
{
	MenuSetWidth(menu, (UINT8)Width);
	return gControl.SetDimensions( menu, Width-2, Height );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuSetAttributes
//
// Description:	Function to set attributes.
//
// Input:		MENU_DATA *menu, UINT8 FGColor, UINT8 BGColor
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuSetAttributes(MENU_DATA *menu, UINT8 FGColor, UINT8 BGColor )
{
	return gControl.SetAttributes( menu, FGColor, BGColor );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuSetWidth
//
// Description:	Function to set width.
//
// Input:		VOID *menu, UINT8 Width
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuSetWidth(VOID *menu, UINT8 Width)
{
	EFI_STATUS Status = EFI_SUCCESS;
  
	// Width -> is the container frame width the menu width is that minus 2 spaces.
	// Left and rigth menu spaces will contain arrows in case that there are multiple pages for the menu. 
	((MENU_DATA*)menu)->MenuWidth = Width-2;
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	TSEMouseMenuHandleAction
//
// Description:	Function to hadnle Menu using mouse
//
// Input:		MENU_DATA *menu,  
//				ACTION_DATA *Data
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TSEMouseMenuHandleAction( MENU_DATA *menu, ACTION_DATA *Data )
{
	// control is in separate frame for ezport.
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT16 TempEntry;
	UINTN i;
	UINTN Pos = menu->Left, StartPos, StrLen;
    CHAR16 *text=NULL;
	CONTROL_ACTION Action;
    //If a sub menu is being displayed no need to handle action
    if(menu->IsSubMenu)
        return EFI_UNSUPPORTED;

	Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);
			

    //Check if left arrow is displayed
    if(menu->ActualPage > 0)
    {
        //Check if left arrow clicked
        if(
            (Data->Input.Data.MouseInfo.Left == menu->Left) &&
            (Data->Input.Data.MouseInfo.Top == menu->Top) &&
				( (Action == ControlActionChoose ) || (Action == ControlActionSelect) )//Performing menu scroll for only action choose and select
          )
        {
            //Handle left arrow click
            if ( menu->CurrEntry > 0 )
                TempEntry = menu->CurrEntry - 1;
            else
                TempEntry = menu->NumEntries - 1;

			_MenuCallCallback(menu,TempEntry);
            Status = EFI_SUCCESS;
        }
    }

    //Check if right arrow is displayed
    if(menu->ActualPage < menu->PageNum)
    {
        //Check if right arrow clicked
        if(
            (Data->Input.Data.MouseInfo.Left == gMaxCols-1) &&
            (Data->Input.Data.MouseInfo.Top == menu->Top) &&
				( (Action == ControlActionChoose ) || (Action == ControlActionSelect) )//Performing menu scroll for only action choose and select
          )
        {
            //Handle right arrow click
            if ( menu->CurrEntry < menu->NumEntries - 1 )
                TempEntry = menu->CurrEntry + 1;
            else
                TempEntry = 0;

			_MenuCallCallback(menu,TempEntry);
            Status = EFI_SUCCESS;
        }
    }

    //Handle individual Page selections
    Pos++;
    for(i = menu->StartItem; i < (UINTN)(menu->StartItem + menu->ItemsInPage); i++)		
    {
        StartPos = Pos;
        text = HiiGetString(menu->Entries[i].PageHandle , menu->Entries[ i ].StringToken );
        StrLen = (TestPrintLength( text ) / (NG_SIZE));
		MemFreePointer( (VOID **)&text );
        Pos = StartPos + StrLen + 2;

        if(
            (Data->Input.Data.MouseInfo.Left >= StartPos) && 
            (Data->Input.Data.MouseInfo.Left < Pos) &&
            (Data->Input.Data.MouseInfo.Top == (UINT32)(menu->Top)) //EIP-73377: Check for the exact menu tab co-ordinates.
          )
        {
            Action = MapControlMouseActionHook(&Data->Input.Data.MouseInfo);
			if( (Action == ControlActionChoose ) || (Action == ControlActionSelect) )
            {
                if(i != menu->CurrEntry)
                {
					_MenuCallCallback(menu,(UINT16)i);
                 }
                 Status=EFI_SUCCESS;
            }
            break;
        }
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MenuGetControlHight
//
// Description:	Function unsupported.
//
// Input:		VOID *object,VOID *frame, UINT16 *height
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS MenuGetControlHight( VOID *object,VOID *frame, UINT16 *height )
{
	return EFI_UNSUPPORTED;
}

//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**       (C)Copyright 1985-2012, American Megatrends, Inc.     **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**    5555 Oakbrook Pkwy, Norcross, Suite 200, Georgia 30093   **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//

