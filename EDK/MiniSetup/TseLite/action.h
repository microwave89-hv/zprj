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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/action.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/action.h $
// 
// 5     10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     2/04/10 11:17p Madhans
// Mouse support related code optimized
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
// Name:		Action.h
//
// Description:	Header file for code to handle different actions.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _ACTION_H_
#define	_ACTION_H_

#include "Minisetup.h"
#include "commonoem.h"
#define	ACTION_TYPE_NULL	0
#define	ACTION_TYPE_KEY		1
#define	ACTION_TYPE_TIMER	2
#define ACTION_TYPE_MOUSE	3

// In terms of 100ns units
#define	ONE_SEC				10000000

typedef struct _ACTION_INPUT
{
	UINT16			Type;
	union
	{
		AMI_EFI_KEY_DATA	AmiKey;
		UINT32			TimerCount;
        MOUSE_INFO 		MouseInfo;
	}
	Data;
}
ACTION_INPUT;

#define	ACTION_MEMBER_VARIABLES	\
	ACTION_INPUT	Input;		\
	UINT32			TimerCount;	\
	EFI_EVENT		TimerEvent;

typedef struct _ACTION_METHODS ACTION_METHODS;

typedef struct _ACTION_DATA
{
	ACTION_METHODS	*Methods;

	ACTION_MEMBER_VARIABLES

}
ACTION_DATA;

typedef EFI_STATUS	(*ACTION_METHOD_CREATE)			( ACTION_DATA **object );
typedef EFI_STATUS	(*ACTION_METHOD_DESTROY)		( ACTION_DATA *object, BOOLEAN freeMem );
typedef EFI_STATUS	(*ACTION_METHOD_GET_ACTION)		( ACTION_DATA *object );
typedef EFI_STATUS	(*ACTION_METHOD_CLEAR_ACTION)	( ACTION_DATA *object );

#define	ACTION_METHOD_FUNCTIONS					\
	ACTION_METHOD_CREATE		Create;			\
	ACTION_METHOD_DESTROY		Destroy;		\
	ACTION_METHOD_GET_ACTION	GetAction;		\
	ACTION_METHOD_CLEAR_ACTION	ClearAction;

struct _ACTION_METHODS
{
	ACTION_METHOD_FUNCTIONS
};

extern ACTION_METHODS gAction;

// Action Methods
EFI_STATUS ActionCreate( ACTION_DATA **object );
EFI_STATUS ActionDestroy( ACTION_DATA *object, BOOLEAN freeMem );
EFI_STATUS ActionGetAction( ACTION_DATA *object );
EFI_STATUS ActionClearAction( ACTION_DATA *object );

//
// Internal functions
//

EFI_STATUS _ActionReadKey( AMI_EFI_KEY_DATA *pAmiKey, UINT64 Timeout );
VOID _ActionTimer( EFI_EVENT Event, VOID *Context );
VOID _ActionInstallTimer( ACTION_DATA *object, UINT64 TriggerTime );

#endif /* _ACTION_H_ */

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
