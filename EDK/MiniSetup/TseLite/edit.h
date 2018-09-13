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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/edit.h $
//
// $Author: Arunsb $
//
// $Revision: 7 $
//
// $Date: 10/18/12 6:02a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/edit.h $
// 
// 7     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 7     3/26/10 6:52p Madhans
// Support to Map the do the Control Mapping from gTseControlMap Table. So
// no changes need in Frame.c, With this feature gTseControlMap Can be
// customized to add/customize the TSE controls.
// 
// 6     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 5     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 4     8/17/09 12:27p Presannar
// Removed References to Tiano.h and replaced it with Efi.h
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
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
// Name:		Edit.h
//
// Description:	Header file for Edit controls
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _EDIT_H_
#define	_EDIT_H_


#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"
#include "action.h"

#define	EDIT_MEMBER_VARIABLES	\
    CHAR16	*Text;			\
	CHAR16	*TempText;		\
	UINT16	TextMargin;		\
    UINT16	MinSize;		\
	UINT16	MaxSize;		\
	UINT16	TextWidth;		\
	UINT16  TextAreaWidth;	\
    UINT8	LabelFGColor;	\
	UINT8	NSelLabelFGColor;		\
	UINT8   LabelMargin;	\
	UINT8	SelFGColor;		\
	UINT8	SelBGColor;		\
	UINT8	EditFGColor;	\
	CHAR16	Chr;			 /* character used to display instead of real chars from keyboard.*/
								 /* mainly used for password entry.*/

typedef struct _EDIT_METHODS	EDIT_METHODS;

typedef struct _EDIT_DATA
{
	EDIT_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	EDIT_MEMBER_VARIABLES

}
EDIT_DATA;

#define	EDIT_METHOD_FUNCTIONS

struct _EDIT_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	EDIT_METHOD_FUNCTIONS

};

extern EDIT_METHODS gEdit;

// Object Methods
EFI_STATUS EditCreate( VOID **object );
EFI_STATUS EditDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS EditInitialize( VOID *object, VOID *data );
EFI_STATUS EditDraw( VOID *object );
EFI_STATUS EditHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS EditSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS EditSetFocus( VOID *object, BOOLEAN focus);
EFI_STATUS EditSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS EditSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS EditSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS EditGetControlHight( VOID *object,VOID *frame, UINT16 *height );

#endif /* _EDIT_H_ */


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
