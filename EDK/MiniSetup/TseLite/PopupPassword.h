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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupPassword.h $
//
// $Author: Premkumara $
//
// $Revision: 10 $
//
// $Date: 8/28/14 6:07a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/PopupPassword.h $
// 
// 10    8/28/14 6:07a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 9     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     5/18/12 6:56a Rajashakerg
// [TAG]  		EIP85220
// [Category]  	Improvement
// [Description]  	TSE - Extend Popup password customization options
// [Files]  		Popuppassword.h
// 
// 7     11/30/11 11:58a Premkumara
// [TAG]  		EIP75521
// [Category]  	Improvement
// [Description]  	Need to support interactive password controls
// [Files]  		PopupPassword.c, PopupPassword.h, TsetAdvanced.c
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 7     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 6:53a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
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
// 1     4/28/09 11:06p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		PopupPassword.h
//
// Description:	Header file for Popup Passwords
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _POPUP_PASSWORD_H_
#define	_POPUP_PASSWORD_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"
#include "action.h"
#include "Label.h"
#include "PopupEdit.h" 


#define POPUP_PASSWORD_MEMBER_VARIABLES \
UINT16 TextMargin; \
UINT16 TextWidth; \
UINT16 TextAreaWidth;


typedef struct _POPUP_PASSWORD_METHODS	POPUP_PASSWORD_METHODS;

typedef struct _POPUP_PASSWORD_DATA
{
	POPUP_PASSWORD_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	LABEL_MEMBER_VARIABLES
	POPUP_PASSWORD_MEMBER_VARIABLES

}
POPUP_PASSWORD_DATA;

#define	POPUP_PASSWORD_METHOD_FUNCTIONS


struct _POPUP_PASSWORD_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	POPUP_PASSWORD_METHOD_FUNCTIONS

};

extern POPUP_PASSWORD_METHODS gPopupPassword;

// Object Methods
EFI_STATUS PopupPasswordCreate( VOID **object );
EFI_STATUS PopupPasswordDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS PopupPasswordInitialize( VOID *object, VOID *data );
EFI_STATUS PopupPasswordDraw( VOID *object );
EFI_STATUS PopupPasswordHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS PopupPasswordSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS PopupPasswordSetFocus( VOID *object, BOOLEAN focus);
EFI_STATUS PopupPasswordSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS PopupPasswordSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS PopupPasswordSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS PopupPasswordGetControlHeight(VOID *object, VOID *frame, UINT16 *height);

EFI_STATUS _DoPopupEdit( POPUP_PASSWORD_DATA *PopupPassword, UINT16 Title, CHAR16 **Text);//EIP-75521 Support Interactive Password control

#endif /* _POPUP_PASSWORD_H_ */


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
