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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/control.c $
//
// $Author: Arunsb $
//
// $Revision: 5 $
//
// $Date: 10/18/12 6:01a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/control.c $
// 
// 5     10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 6     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     11/21/11 8:49a Rajashakerg
// [TAG]  		EIP69104 
// [Category]  	Improvement
// [Description]  	Not to destroy the controls if it is NULL
// [Files]  		control.c, edit.c, Label.c, memo.c, menu.c, ordlistbox.c,
// popup.c, PopupSel.c, PopupString.c, SubMenu.c, Text.c.
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
// Name:		contorl.c
//
// Description:	This file contains code to handle controls
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

CONTROL_METHODS gControl =
{
	ControlCreate,
	ControlDestroy,
	ControlInitialize,
	ControlEmptyMethod,
	ControlHandleAction,
	ControlSetCallback,
	ControlSetFocus,
	ControlSetPosition,
	ControlSetDimensions,
	ControlSetAttributes
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlCreate
//
// Description:	Function to create the cotrol options using object functions.
//
// Input:	CONTROL_DATA **object
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlCreate( CONTROL_DATA **object )
{
	EFI_STATUS Status = EFI_SUCCESS;

	if ( *object == NULL )
	{
		*object = EfiLibAllocateZeroPool( sizeof(CONTROL_DATA) );

		if ( *object == NULL )
			return EFI_OUT_OF_RESOURCES;
	}

	Status = gObject.Create( object );
	if ( ! EFI_ERROR(Status) )
		(*object)->Methods = &gControl;

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlDestroy
//
// Description:	Function to destroy the cotrol options using object functions.
//
// Input:	CONTROL_DATA *control, BOOLEAN freeMem
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlDestroy( CONTROL_DATA *control, BOOLEAN freeMem )
{
	if(NULL == control)
		return EFI_SUCCESS;
		
	gObject.Destroy( control, FALSE );

	if ( freeMem )
		MemFreePointer( (VOID **)&control );

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlInitialize
//
// Description:	Function to Initialize the cotrol options using object functions.
//
// Input:	CONTROL_DATA *control, VOID *data
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlInitialize( CONTROL_DATA *control, VOID *data )
{
	EFI_STATUS Status;

	Status = gObject.Initialize( control, data );
	if (EFI_ERROR(Status))
		return Status;

	if ( ((CONTROL_INFO *)data)->ControlPtr == (UINTN)NULL )
		return EFI_UNSUPPORTED;

	if ( ! ((CONTROL_INFO *)data)->ControlFlags.ControlVisible )
		Status = EFI_UNSUPPORTED;
	else
		MemCopy( &control->ControlData, data, sizeof(CONTROL_INFO) );

	return Status;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlInitialize
//
// Description:	Function to draw control.
//
// Input:		CONTROL_DATA *control
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlDraw( CONTROL_DATA *control )
{
	return gObject.Draw( control );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlEmptyMethod
//
// Description:	Empty control method.
//
// Input:		CONTROL_DATA *control
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlEmptyMethod( CONTROL_DATA *control )
{
	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlSetCallback
//
// Description:	Function to set callback.
//
// Input:		CONTROL_DATA *control, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie 
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlSetCallback( CONTROL_DATA *control, OBJECT_DATA *container, OBJECT_CALLBACK callback, VOID *cookie )
{
	return gObject.SetCallback( control, container, callback, cookie );
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlHandleAction
//
// Description:	Function to handle action.
//
// Input:		CONTROL_DATA *control, ACTION_DATA *Data
//
// Output:		STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlHandleAction( CONTROL_DATA *control, ACTION_DATA *Data )
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlSetFocus
//
// Description:	Function to set focus.
//
// Input:		CONTROL_DATA *control, BOOLEAN focus
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlSetFocus( CONTROL_DATA *control, BOOLEAN focus )
{
	return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlSetPosition
//
// Description:	Function to set the position.
//
// Input:		CONTROL_DATA *control, UINT16 Left, UINT16 Top
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlSetPosition( CONTROL_DATA *control, UINT16 Left, UINT16 Top )
{
	control->Left = Left;
	control->Top = Top;

	return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlSetDimensions
//
// Description:	Function to set dimensions.
//
// Input:		 CONTROL_DATA *control, UINT16 Width, UINT16 Height
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlSetDimensions(CONTROL_DATA *control, UINT16 Width, UINT16 Height)
{
	control->Width = Width;
	control->Height = Height;

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ControlSetAttributes
//
// Description:	Function to set the control attributes
//
// Input:	CONTROL_DATA *control, UINT8 FGColor, UINT8 BGColor
//
// Output:	status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ControlSetAttributes( CONTROL_DATA *control, UINT8 FGColor, UINT8 BGColor )
{
	if ( FGColor != 0 )
		control->FGColor = FGColor;

	if ( BGColor != 0 )
		control->BGColor = BGColor;

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
