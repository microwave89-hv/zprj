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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/page.h $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 10/18/12 6:01a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/page.h $
// 
// 6     10/18/12 6:01a Arunsb
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
// 
// 7     7/06/06 6:37p Arunkumars
// Include tiano.h instead of efi.h
// 
// 6     2/06/05 11:15a Jerryp
// Full hotkey support
// 
// 5     1/14/05 7:09p Jerryp
// First integration code with boot to shell.
// Still a bug in booting to shell from FV
// 
// 4     1/13/05 7:14p Jerryp
// Added new method to Control class
// Added RUNTIME_DEBUG_SUPPORT option
// Fixed flushing error with memo
// Added update to help of date control
// Removed all fake HII stuff
// 
// 3     1/13/05 10:37a Jerryp
// Latest updated
// Added ifdef for fake HII info
// 
// 2     1/06/05 11:31a Jerryp
// Moved callback from Control to Object
// Better class heirarchy definitions through #define
// 
// 1     12/30/04 5:35p Jerryp
// Initial checkin
// ** Still some debugging code in place
// ** Not all object/controls work as expected
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		page.h
//
// Description:	Header file for code to handle page level operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _PAGE_H_
#define _PAGE_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "object.h"
#include "action.h"
#include "frame.h"
#include "hotkey.h"

#define	PAGE_MEMBER_VARIABLES	\
	PAGE_INFO	PageData;		\
	UINT32		CurrentFrame;	\
	UINT32		FrameCount;		\
	FRAME_DATA	**FrameList;	\
	UINT32		HotKeyCount;	\
	HOTKEY_DATA	**HotKeyList;

typedef struct _PAGE_METHODS PAGE_METHODS;

typedef struct _PAGE_DATA
{
	PAGE_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	PAGE_MEMBER_VARIABLES

}
PAGE_DATA;

#define	PAGE_METHOD_FUNCTIONS

struct _PAGE_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	PAGE_METHOD_FUNCTIONS
};

extern PAGE_METHODS gPage;

// Object Methods
EFI_STATUS PageCreate( VOID **object );
EFI_STATUS PageDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS PageInitialize( VOID *object, VOID *data );
EFI_STATUS PageDraw( VOID *object );
EFI_STATUS PageHandleAction( VOID *object, ACTION_DATA *data );
EFI_STATUS PageSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

VOID _PageUpdateMemo( PAGE_DATA *page, UINT32 frameType, /*EFI_HII_HANDLE*/VOID * handle, UINT16 token );

VOID _PageUpdateHelp( PAGE_DATA *page );
VOID _PageUpdateSubtitle( PAGE_DATA *page );
VOID _PageUpdateTitle( PAGE_DATA *page );
VOID _PageUpdateNavStrings( PAGE_DATA *page );
VOID _PageUpdateFrameStrings( PAGE_DATA *page );

#endif /* _PAGE_H_ */


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
