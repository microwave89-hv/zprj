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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/frame.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/frame.h $
// 
// 7     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
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
// Name:		frame.h
//
// Description:	Header file for Frame control related functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _FRAME_H_
#define _FRAME_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "object.h"
#include "action.h"
#include "control.h"

#include "submenu.h"
#include "menu.h"
#include "text.h"

#define	MAIN_FRAME	0
#define	TITLE_FRAME	(MAIN_FRAME + 1)
#define	HELP_FRAME	(TITLE_FRAME + 1)
#define	NAV_FRAME	(HELP_FRAME + 1)
#define	SUBTITLE_FRAME	(NAV_FRAME + 1)
#define	HELPTITLE_FRAME	(SUBTITLE_FRAME + 1)
#define	MAINTITLE_FRAME	(HELPTITLE_FRAME + 1)
#define	SCROLLBAR_FRAME	(MAINTITLE_FRAME + 1)

typedef struct _FRAME_INFO
{
	UINT32			FrameType;
	BOOLEAN			Drawable;
	BOOLEAN			Border;
	CHAR16			BorderType;
	UINT8			Width;
	UINT8			Height;
	UINT8			Top;
	UINT8			Left;
	UINT8			FGColor;
	UINT8			BGColor;
	UINT8			ScrlFGColor;
	UINT8			ScrlBGColor;
	UINT8			ScrlUpFGColor; 
	UINT8			ScrlUpBGColor;
	UINT8			ScrlDnFGColor; 
	UINT8			ScrlDnBGColor;

}
FRAME_INFO;

typedef struct _AMITSE_CONTROL_MAP
{
	UINT16			ControlType;
	CONTROL_METHODS *ControlMethods;
	BOOLEAN			CallbackSuppored;
	VOID 			*CallbackFunction;	
	VOID 			*CallbackContext;
}AMITSE_CONTROL_MAP;

typedef struct _POSITION_INFO
{
	UINT16	Top;
	UINT16	Left;
}
POSITION_INFO;

#define FRAME_NONE_FOCUSED 0xFFFFFFFF

#define	FRAME_MEMBER_VARIABLES		\
	FRAME_INFO		FrameData;		\
	UINT32			PageID;			\
	UINT32			ControlCount;	\
	UINT32			NullCount;		\
	UINT32			CurrentControl;	\
	CONTROL_DATA	**ControlList;	\
	CHAR16			*BlankLine;		\
	BOOLEAN			UseScrollbar;  \
	UINT32			FirstVisibleCtrl; \
	UINT32			LastVisibleCtrl;  \
	POSITION_INFO	*OrigPosition;	\
	POSITION_INFO	*CurrPosition;

typedef struct _FRAME_METHODS FRAME_METHODS;

typedef struct _FRAME_DATA
{
	FRAME_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	FRAME_MEMBER_VARIABLES

}
FRAME_DATA;

typedef EFI_STATUS	(*FRAME_METHOD_ADD_CONTROL)		( VOID *object, VOID *data );


#define	FRAME_METHOD_FUNCTIONS				\
	FRAME_METHOD_ADD_CONTROL	AddControl;	

struct _FRAME_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	FRAME_METHOD_FUNCTIONS
};

extern FRAME_METHODS gFrame;
extern AMITSE_CONTROL_MAP gTseControlMap[];
// Object Methods
EFI_STATUS FrameCreate( VOID **object );
EFI_STATUS FrameDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS FrameInitialize( VOID *object, VOID *data );
EFI_STATUS FrameDraw( VOID *object );
EFI_STATUS FrameHandleAction( VOID *object, ACTION_DATA *data );
EFI_STATUS FrameSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Frame Methods
EFI_STATUS FrameAddControl( VOID *object, VOID *data );


VOID _FrameSubmenuCallback( FRAME_DATA *frame, SUBMENU_DATA *submenu, VOID *cookie );
VOID _FrameVariableCallback( FRAME_DATA *frame, CONTROL_DATA *control, VOID *cookie );
VOID _FramePasswordCallback( FRAME_DATA *frame, CONTROL_DATA *control, VOID *cookie );
BOOLEAN _FrameSetControlFocus( FRAME_DATA *frame, UINT32 index );
EFI_STATUS _FrameAddControls( FRAME_DATA *frame, PAGE_INFO *data );
EFI_STATUS _FrameAddTitle( FRAME_DATA *frame, UINT32 frameType, PAGE_INFO *data );

#endif /* _FRAME_H_ */


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
