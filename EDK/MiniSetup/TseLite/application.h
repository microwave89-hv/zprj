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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/application.h $
//
// $Author: Arunsb $
//
// $Revision: 7 $
//
// $Date: 10/18/12 6:01a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/application.h $
// 
// 7     10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     6/29/11 12:54p Rajashakerg
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
// 1     4/28/09 11:04p Madhans
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
// Name:		Application.h
//
// Description:	Header file for code to handle Application.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "object.h"
#include "action.h"
#include "page.h"
#include "hotkey.h"
#include "hotclick.h"//EIP:47086 - Right clicking from the Main page is not exiting from BIOS setup.

#define	APPLICATION_MEMBER_VARIABLES	\
	ACTION_DATA			*Action;		\
	UINT32				CurrentPage;	\
	UINT32				PageCount;		\
	PAGE_DATA			**PageList;		\
	UINTN				HotKeyCount;	\
	HOTKEY_DATA			**HotKeyList;	\
	UINTN				HotClickCount;	\
	HOTCLICK_DATA			**HotClickList;\
	BOOLEAN				CompleteRedraw;	\
	BOOLEAN				ClearScreen;	\
	BOOLEAN				Quit;			\
	UINT32				OnRedraw;\
    BOOLEAN             Fixed;

typedef struct _APPLICATION_METHODS APPLICATION_METHODS;

typedef struct _APPLICATION_INFO
{
	UINT32	PageCount;
}
APPLICATION_INFO;

typedef struct _APPLICATION_DATA
{
	APPLICATION_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	APPLICATION_MEMBER_VARIABLES

}
APPLICATION_DATA;

typedef EFI_STATUS		(*APPLICATION_METHOD_ADD_PAGE)	( APPLICATION_DATA *app, VOID *data );

#define APPLICATION_METHOD_FUNCTIONS		\
	APPLICATION_METHOD_ADD_PAGE	AddPage;

struct _APPLICATION_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	APPLICATION_METHOD_FUNCTIONS
};

extern APPLICATION_METHODS gApplication;
extern APPLICATION_DATA *gApp;

// Object Methods
EFI_STATUS ApplicationCreate( VOID **object );
EFI_STATUS ApplicationDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS ApplicationInitialize( VOID *object, VOID *data );
EFI_STATUS ApplicationEmptyMethod( VOID *object );
EFI_STATUS ApplicationHandleAction( VOID *object, ACTION_DATA *Data );
EFI_STATUS ApplicationSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Application Methods
EFI_STATUS ApplicationAddPage( APPLICATION_DATA *app, VOID *data );

#endif /* _APPLICATION_H_ */


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
