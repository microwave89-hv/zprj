//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/object.c $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 6:01a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/object.c $
// 
// 4     10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 6     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 3     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
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
// Name:		Object.c
//
// Description:	This file contains code to handle Objects
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

OBJECT_METHODS gObject = 
{
	ObjectCreate,
	ObjectDestroy,
	ObjectInitialize,
	ObjectDraw,
	ObjectHandleAction,
	ObjectSetCallback
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectCreate
//
// Description:	function to create an object
//
// Input:	 OBJECT_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ObjectCreate( OBJECT_DATA **object )
{
	if ( *object == NULL )
		*object = EfiLibAllocateZeroPool( sizeof(OBJECT_DATA) );

	if ( *object == NULL )
		return EFI_OUT_OF_RESOURCES;

	(*object)->Methods = &gObject;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectDestroy
//
// Description:	function to Destroy an object
//
// Input:	 OBJECT_DATA **object, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ObjectDestroy( OBJECT_DATA *object, BOOLEAN freeMem )
{
	if ( freeMem )
		MemFreePointer( (VOID **)&object );

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectInitialize
//
// Description:	Function to initialize an object
//
// Input:	 OBJECT_DATA *object, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ObjectInitialize( OBJECT_DATA *object, VOID *data )
{
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectDraw
//
// Description:	Function to draw an object
//
// Input:		OBJECT_DATA *object
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ObjectDraw( OBJECT_DATA *object )
{
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectHandleAction
//
// Description:	Function to handle object action
//
// Input:		OBJECT_DATA *object, ACTION_DATA *Data
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ObjectHandleAction( OBJECT_DATA *object, ACTION_DATA *Data )
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ObjectSetCallback
//
// Description:	Function to set  object callback
//
// Input:		OBJECT_DATA *object, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ObjectSetCallback( OBJECT_DATA *object, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	object->Callback = callback;
	object->Container = container,
	object->Cookie = cookie;

	return EFI_SUCCESS;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
