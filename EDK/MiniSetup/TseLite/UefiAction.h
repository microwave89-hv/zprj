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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/UefiAction.h $
//
// $Author: Arunsb $
//
// $Revision: 5 $
//
// $Date: 10/18/12 6:03a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/UefiAction.h $
// 
// 5     10/18/12 6:03a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:19a Mallikarjunanv
// updated year in copyright message
// 
// 4     7/31/09 6:35p Presannar
// Remove Include Tiano.h and instead include Minisetup.h
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		UefiAction.h
//
// Description:	Header file for UefiAction data
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _UEFI_ACTION_H_
#define _UEFI_ACTION_H_

#include "minisetup.h" 

#include "control.h"
#include "action.h"

typedef struct _UEFI_ACTION_METHODS	UEFI_ACTION_METHODS;

#define	UEFI_ACTION_MEMBER_VARIABLES \
  LABEL_MEMBER_VARIABLES \
  UINT8	Interval;

typedef struct _UEFI_ACTION_DATA
{
	UEFI_ACTION_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	UEFI_ACTION_MEMBER_VARIABLES
}
UEFI_ACTION_DATA;

#define UEFI_ACTION_METHOD_FUNCTIONS

struct _UEFI_ACTION_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	LABEL_METHOD_FUNCTIONS
  UEFI_ACTION_METHOD_FUNCTIONS
};

extern UEFI_ACTION_METHODS gUefiAction;

// Object Methods
EFI_STATUS UefiActionCreate( VOID **object );
EFI_STATUS UefiActionInitialize( VOID *object, VOID *data );
EFI_STATUS UefiActionDraw( VOID *object );
EFI_STATUS UefiActionHandleAction(VOID *object, ACTION_DATA *Data);

#endif /*#ifndef _UEFI_ACTION_H_*/

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
