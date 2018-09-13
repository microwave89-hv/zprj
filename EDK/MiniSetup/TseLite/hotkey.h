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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/hotkey.h $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 10/18/12 6:02a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/hotkey.h $
// 
// 6     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 5     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
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
// 1     4/28/09 11:05p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/28/09 9:40p Madhans
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
// Name:		hotkey.h
//
// Description:	Header file for hotkey code to handling
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _HOTKEY_H_
#define _HOTKEY_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "object.h"
#include "action.h"

/*
typedef struct _HOTKEY_TEMPLATE
{
	EFI_INPUT_KEY	Key;
	UINT32			KeySftSte;
	OBJECT_CALLBACK	Callback;
	UINT32			BasePage;
}
HOTKEY_TEMPLATE;
*/
typedef struct _HOTKEY_INFO
{
	EFI_INPUT_KEY	Key;
	UINT32			KeySftSte;
}
HOTKEY_INFO;

#define	HOTKEY_MEMBER_VARIABLES	\
	HOTKEY_INFO		HotKeyData;	\
	UINT32			BasePage;

typedef struct _HOTKEY_METHODS HOTKEY_METHODS;

typedef struct _HOTKEY_DATA
{
	HOTKEY_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	HOTKEY_MEMBER_VARIABLES

}
HOTKEY_DATA;

#define	HOTKEY_METHOD_FUNCTIONS

struct _HOTKEY_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	HOTKEY_METHOD_FUNCTIONS
};

extern HOTKEY_METHODS gHotKey;

// Object Methods
EFI_STATUS HotKeyCreate( VOID **object );
EFI_STATUS HotKeyDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS HotKeyInitialize( VOID *object, VOID *data );
EFI_STATUS HotKeyEmptyMethod( VOID *object );
EFI_STATUS HotKeyHandleAction( VOID *object, ACTION_DATA *data );
EFI_STATUS HotKeySetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

#endif /* _HOTKEY_H_ */


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
