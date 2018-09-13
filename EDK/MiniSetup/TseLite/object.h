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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/object.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/object.h $
// 
// 5     10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 4     6/24/09 6:11p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
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
// Name:		Object.h
//
// Description:	Header file for code to handle Objects
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _OBJECT_H_
#define	_OBJECT_H_

//#include "Tiano.h" 
//#include "EfiDriverLib.h"
#include "Minisetup.h"
#include "action.h"
#include "callback.h"

typedef	VOID	(*OBJECT_CALLBACK)	( VOID *container, VOID *object, VOID *cookie );

#define	OBJECT_MEMBER_VARIABLES	\
	OBJECT_CALLBACK	Callback;	\
	VOID			*Container;	\
	VOID			*Cookie;
	
typedef struct _OBJECT_METHODS OBJECT_METHODS;

typedef struct _OBJECT_DATA
{
	OBJECT_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
}
OBJECT_DATA;

typedef EFI_STATUS	(*OBJECT_METHOD_CREATE)			( VOID **object );
typedef EFI_STATUS	(*OBJECT_METHOD_DESTROY)		( VOID *object, BOOLEAN freeMem );
typedef EFI_STATUS	(*OBJECT_METHOD_INITIALIZE)		( VOID *object, VOID *data );
typedef	EFI_STATUS	(*OBJECT_METHOD_DRAW)			( VOID *object );
typedef EFI_STATUS	(*OBJECT_METHOD_HANDLE_ACTION)	( VOID *object, ACTION_DATA *Data );
typedef	EFI_STATUS	(*OBJECT_METHOD_SET_CALLBACK)	( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

#define	OBJECT_METHOD_FUNCTIONS					\
	OBJECT_METHOD_CREATE		Create;			\
	OBJECT_METHOD_DESTROY		Destroy;		\
	OBJECT_METHOD_INITIALIZE	Initialize;		\
	OBJECT_METHOD_DRAW			Draw;			\
	OBJECT_METHOD_HANDLE_ACTION	HandleAction;	\
	OBJECT_METHOD_SET_CALLBACK	SetCallback;

struct _OBJECT_METHODS
{
	OBJECT_METHOD_FUNCTIONS
};

extern OBJECT_METHODS gObject;

EFI_STATUS ObjectCreate( VOID **object );
EFI_STATUS ObjectDestroy( VOID *object, BOOLEAN freeMem );

EFI_STATUS ObjectInitialize( VOID *object, VOID *data );
EFI_STATUS ObjectDraw( VOID *object );
EFI_STATUS ObjectHandleAction( VOID *object, ACTION_DATA *Data );
EFI_STATUS ObjectSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

#endif /* _OBJECT_H_ */


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
