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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/control.h $
//
// $Author: Arunsb $
//
// $Revision: 8 $
//
// $Date: 10/18/12 6:01a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/control.h $
// 
// 8     10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/26/10 8:54p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 5     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 4     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 3     8/17/09 12:27p Presannar
// Removed References to Tiano.h and replaced it with Efi.h
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:04p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     2/05/09 10:15a Madhans
// Style Module created.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

#ifndef _CONTROL_H_
#define	_CONTROL_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "object.h"
#include "setupdata.h"
#include "action.h"
#if UEFI_SOURCES_SUPPORT
#include "ctrlcond.h"
#endif

#define CONTROL_GRAYOUT_COLOR STYLE_COLOR_GRAYOUT

#define	CONTROL_MEMBER_VARIABLES		\
	CONTROL_INFO	ControlData;		\
	UINT16			Left;				\
	UINT16			Top;				\
	UINT16			Width;				\
	UINT16			Height;				\
	UINT8			FGColor;			\
    UINT8			BGColor;			\
	BOOLEAN			ControlFocus;		\
	BOOLEAN			ControlActive;		\
	UINT32			ParentFrameType;

typedef struct _CONTROL_METHODS	CONTROL_METHODS;

typedef struct _CONTROL_DATA
{
	CONTROL_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES

}
CONTROL_DATA;

typedef	EFI_STATUS	(*CONTROL_METHOD_SET_FOCUS)		( VOID *object, BOOLEAN focus );
typedef	EFI_STATUS	(*CONTROL_METHOD_SET_POSITION)	( VOID *object, UINT16 Left, UINT16 Top );
typedef	EFI_STATUS	(*CONTROL_METHOD_SET_DIMENSIONS)	( VOID *object, UINT16 Width, UINT16 Height );
typedef	EFI_STATUS	(*CONTROL_METHOD_SET_ATTRIBUTES)( VOID *object, UINT8 FGColor, UINT8 BGColor );
typedef	EFI_STATUS	(*CONTROL_METHOD_GET_CONTROL_HIGHT)( VOID *object, VOID *frame, UINT16 *height  );

#define	CONTROL_METHOD_FUNCTIONS					\
	CONTROL_METHOD_SET_FOCUS		SetFocus;		\
	CONTROL_METHOD_SET_POSITION		SetPosition;	\
	CONTROL_METHOD_SET_DIMENSIONS    SetDimensions;	\
	CONTROL_METHOD_SET_ATTRIBUTES	SetAttributes; \
	CONTROL_METHOD_GET_CONTROL_HIGHT GetControlHeight;

struct _CONTROL_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
};

extern CONTROL_METHODS gControl;

// Object Methods
EFI_STATUS ControlCreate( VOID **object );
EFI_STATUS ControlDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS ControlInitialize( VOID *object, VOID *data );
EFI_STATUS ControlEmptyMethod( VOID *object );
EFI_STATUS ControlDraw( VOID *object );
EFI_STATUS ControlHandleAction( VOID *object, ACTION_DATA *Data );
EFI_STATUS ControlSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS ControlSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS ControlSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS ControlSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS ControlSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
CONTROL_DATA * GetUpdatedControlData(CONTROL_DATA * ControlData,UINT16 ControlType,VOID *Handle,UINT16 Key);


#endif /* _CONTROL_H_ */


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
