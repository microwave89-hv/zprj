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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/application.c $
//
// $Author: Arunsb $
//
// $Revision: 12 $
//
// $Date: 5/03/14 4:33p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/application.c $
// 
// 12    5/03/14 4:33p Arunsb
// Build error rectified
// 
// 11    5/03/14 3:38p Arunsb
// [TAG]	EIP154569
// [Category]	Improvement
// [Description]	Handling clicks in application level for 80*25 mode also.
// [Files]	LegacyBin.sdl. EzportBin.sdl, EzportPlusBin.sdl and
// application.c
// 
// 10    9/19/13 8:01a Arunsb
// [TAG]	EIP127375
// [Category]	Bug Fix
// [Severity:]	Critical
// [Symptom:]	Legacy boot doesn't work after UEFI Shell is launched from
// LaunchAppHotkey menu. The system hangs
// [Root Cause]	If ShowPostMsgBoxEx is invoked through postmgr protcol
// then gMsgBoxAction will be NULL initially,
// so this time action is assigned and used. 
// ACTION_DATA *action = gMsgBoxAction; so accessing NULL pointer leads to
// hang.
// [Solution]	gMsgBoxAction is created again inside ShowPostMsgBoxEx, 
// reassign gMsgBoxAction to action.
// [Files]	TseAdvanced.c
// 
// 9     5/22/13 10:40a Arunsb
// [TAG]  		EIP122907
// [Category]  	Improvement
// [Description]  	For getting name value offset preserving page number
// then it will be easy to find handle of the hii which published name
// value.
// 
// 8     10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     6/29/11 6:21p Rajashakerg
// Updated the file for Hotkey and hotclicks to return their exact status
// 
// 6     6/29/11 12:52p Rajashakerg
// [TAG]  		EIP47086
// [Category]  	New Feature
// [Description]  	Right clicking from the Main page is not exiting from
// BIOS setup.
// 
// [Files]  		minisetup.h, Ezport\style.h,Ezport\EzportBin.sdl,
// Ezport\EzportBin.mak, Ezport\ezport.c, Ezport\EzportBin.cif,
// EzportPlus\style.h, EzportPlus\EzportPlusBin.sdl, EzportPlusBin.mak,
// EzportPlus\EzportPlusBin.cif, EzportPlus\ezportplus.c, Legacy\style.h,
// Legacy\EzportPlusBin.sdl, Legacy\LegacyBin.mak, Legacy\LegacyBin.cif,
// Legacy\legacy.c, TseLiteBin.sdl, TseLite.cif, Memo.c, frame.c,
// application.h, application.c, commonoem.h, CommonHelper.c
// 
// 5     3/26/10 5:06p Madhans
// EIP 36704 : Fix for Making sure to make the Variable to NULL after it
// is Freed up.
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 6:25a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     8/19/09 12:58p Madhans
// To handle ToggleStateKeys
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
// 1     4/28/09 11:04p Madhans
// Tse 2.0 Code complete Checkin.
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
// Name:		Application.c
//
// Description:	This file contains code to handle Application.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

APPLICATION_METHODS gApplication =
{
	ApplicationCreate,
	ApplicationDestroy,
	ApplicationInitialize,
	ApplicationEmptyMethod,
	ApplicationHandleAction,
	ApplicationSetCallback,
	ApplicationAddPage
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ApplicationCreate
//
// Description:	Function to create an application, which uses the Object functions.
//
// Input:	APPLICATION_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ApplicationCreate( APPLICATION_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(APPLICATION_DATA) );

		if ( *object == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Status = gObject.Create( object );
	if ( EFI_ERROR( Status ) )
	{
		MemFreePointer( (VOID **)object );
		return Status;
	}

	(*object)->Methods = &gApplication;
	(*object)->CompleteRedraw = TRUE;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ApplicationDestroy
//
// Description:	Function to destroy an application, which uses the Object functions.
//
// Input:	APPLICATION_DATA *app, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ApplicationDestroy( APPLICATION_DATA *app, BOOLEAN freeMem )
{
	UINT32 i;

	if ( app->Action )
		gAction.Destroy( app->Action, TRUE );

	app->Action = NULL;
	gMsgBoxAction = NULL;			//EIP127375, if not made NULL here, then TSE will try to use the freed memory in above step.

	for ( i = 0; i < app->PageCount; i++ )
		if(app->PageList[i] !=NULL)
			gPage.Destroy( app->PageList[i], TRUE );

	if ( app->PageList )
		MemFreePointer( (VOID **)&app->PageList );

	for ( i = 0; i < app->HotKeyCount; i++ )
		gHotKey.Destroy( app->HotKeyList[i], TRUE );
	
//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
	for ( i = 0; i < app->HotClickCount; i++ )
		gHotClick.Destroy( app->HotClickList[i], TRUE );

	if ( app->HotKeyList )
		MemFreePointer( (VOID **)&app->HotKeyList );
	
//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
	if ( app->HotClickList )
		MemFreePointer( (VOID **)&app->HotClickList );
	

	gObject.Destroy( app, FALSE );

	if ( freeMem )
		MemFreePointer( (VOID **)&app );

	return EFI_SUCCESS;
}

EFI_STATUS ApplicationEmptyMethod( APPLICATION_DATA *app )
{
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ApplicationInitialize
//
// Description:	Function to initialize an application, which uses the Object functions.
//
// Input:	APPLICATION_DATA *app, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
extern UINT32	gtempCurrentPage;
EFI_STATUS ApplicationInitialize( APPLICATION_DATA *app, VOID *data )
{
	EFI_STATUS Status;

	UINT32 i;

	Status = gAction.Create( &app->Action );
	if ( EFI_ERROR( Status ) )
		return Status;

	if ( gPages->PageCount == 0 )
		return EFI_OUT_OF_RESOURCES;

	for ( i = 0; i < gPages->PageCount; i++ )
	{
		if (NULL == gApp)
		{
			gtempCurrentPage = i;					//Will be used in UefiGetQuestionOffset. Since gApp will not be filled but we need handle to find name value variable so
		}												//saving current page
		else
		{
			gApp->CurrentPage = i;
		}
		ApplicationAddPage( app, (UINT8 *)data + gPages->PageList[i] );
	}

	app->HotKeyList = EfiLibAllocateZeroPool( sizeof(HOTKEY_DATA *) * gHotKeyCount );
	
//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
	app->HotClickList = EfiLibAllocateZeroPool( sizeof(HOTCLICK_DATA *) * gHotClickCount );

	if ( app->HotKeyList == NULL )
		return Status;
	
//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
	if ( app->HotClickList == NULL )
		return Status;

	app->HotKeyCount = gHotKeyCount;
	
//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
	app->HotClickCount = gHotClickCount;

	for ( i = 0; i < app->HotKeyCount; i++ )
	{
		if ( gHotKey.Create( &app->HotKeyList[i] ) != EFI_SUCCESS )
			continue;

		gHotKey.Initialize( app->HotKeyList[i], &gHotKeyInfo[i] );
		gHotKey.SetCallback( app->HotKeyList[i], app, gHotKeyInfo[i].Callback, NULL );
	}

//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
	for ( i = 0; i < app->HotClickCount; i++ )
	{
		if ( gHotClick.Create( &app->HotClickList[i] ) != EFI_SUCCESS )
			continue;

		gHotClick.Initialize( app->HotClickList[i], &gHotClickInfo[i] );
		gHotClick.SetCallback( app->HotClickList[i], app, gHotClickInfo[i].Callback, NULL );
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ApplicationHandleAction
//
// Description:	Function to handle the application actions.
//
// Input:	APPLICATION_DATA *app, ACTION_DATA *action
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ApplicationHandleAction( APPLICATION_DATA *app, ACTION_DATA *action )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT32 i;

	for ( i = 0; i < app->HotKeyCount; i++ )
	{
		Status = gHotKey.HandleAction( app->HotKeyList[i], action );

		if ( ! EFI_ERROR(Status) )
			goto DONE;
	}
	
//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.
	if ((31 == gMaxRows) && (100 == gMaxCols))
	{
		for ( i = 0; i < app->HotClickCount/2; i++ )
		{
			Status = gHotClick.HandleAction( app->HotClickList[i], action );
	
			if ( ! EFI_ERROR(Status) )
				return Status;
		}
	}
	else if ((24 == gMaxRows) && (80 == gMaxCols))
	{
		for ( i = (UINT32)(app->HotClickCount/2); i < (app->HotClickCount-1); i++ )
		{
			Status = gHotClick.HandleAction( app->HotClickList[i], action );
	
			if ( ! EFI_ERROR(Status) )
				return Status;
		}
	}
DONE:
	if(Status!=EFI_SUCCESS && IsToggleStateKey(action))	
		Status = EFI_SUCCESS;

	return Status;
}

EFI_STATUS ApplicationSetCallback( APPLICATION_DATA *app, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gObject.SetCallback( app, container, callback, cookie );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ApplicationAddPage
//
// Description:	Function to add a page to the application.
//
// Input:	APPLICATION_DATA *app, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ApplicationAddPage( APPLICATION_DATA *app, VOID *data )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;
	PAGE_DATA **page;
	UINT32 count = app->PageCount;

	page = MemReallocateZeroPool( app->PageList, count * sizeof(PAGE_DATA *), (count + 1) * sizeof(PAGE_DATA *) );
	if ( page == NULL )
		return Status;

	app->PageList = page;
	page = &app->PageList[ count ];

	if( ((PAGE_INFO*)data)->PageHandle == 0)
	{
        app->PageCount++;
		//return EFI_SUCCESS , page space left , but no page to create.
		return EFI_SUCCESS;
	}

	Status = gPage.Create( page );
	if ( ! EFI_ERROR( Status ) )
	{
		Status = gPage.Initialize( *page, data );
		if ( ! EFI_ERROR( Status ) )
			app->PageCount++;
		else
		{
			gPage.Destroy( *page, TRUE );
			*page = NULL;
		}
	}

	return Status;
}


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
