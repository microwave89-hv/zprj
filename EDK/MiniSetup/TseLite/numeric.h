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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/numeric.h $
//
// $Author: Arunsb $
//
// $Revision: 12 $
//
// $Date: 10/18/12 6:02a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/numeric.h $
// 
// 12    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 11    4/05/12 7:18a Rajashakerg
// [TAG]  		EIP87122,85508,86449
// [Category]  	Improvement
// [Description]  	Numeric in old style, softkbd issues
// [Files]  		CommonHelper.c, Mouse.c, Date.c, edit.c, frame.c,
// minisetupext.h, numeric.c, numeric.h, PopupEdit.c, PopupEdit.h, time.c
// 
// 10    11/20/11 8:03a Rajashakerg
// [TAG]  		EIP62763
// [Category]  	Improvement
// [Description]  	Utilize the Improvements done from mouse driver in
// AMITSE
// [Files]  		HookAnchor.h, TseCommon.h, AMITSE.sdl, CommonHelper.c,
// commonoem.c, commonoem.h, buffer.c, globals.c, HookAnchor.c,
// minisetup.h, notify.c, postmgmt.c, protocol.c, ezport.c, stylecommon.c,
// Mouse.c, Action.c, Date.c, frame.c, MessageBox.c, minisetupext.c,
// minisetupext.h, numeric.c, numeric.h, page.c, PopupEdit.c, PopupEdit.h,
// PopupPassword.c, postmgmtext.c, time.c.
// 
// 9     10/21/11 2:55a Rajashakerg
// [TAG]  		EIP60563 
// [Category]  	New Feature
// [Description]  	Updating the file with fix for issue : maximum 8 byte
// value shows negative number
// [Files]  		numeric.c, numeric.h, string.c, string.h
// 
// 8     6/20/11 12:23p Rajashakerg
// [TAG]  		EIP60563 
// [Category]  	New Feature
// [Description]  	Support for signed decimal value for
// EFI_IFR_NUMERIC_OP.
// [Files]  		numeric.c, numeric.h, string.c, string.h, Uefi21Wapper.c
// 
// 7     3/09/11 7:23p Madhans
// [TAG]  		EIP48615  
// [Category]  	Improvement
// [Description]  	To support UEFI 2.1 RefreshOp. Based in Refersh Rate
// Controls are refershed periodically.
// [Files]  		minisetupext.h
// SubMenu.h
// SubMenu.c
// Memo.c
// Memo.h
// numeric.c
// numeric.h
// time.c
// Date.c
// PopupSel.c
// PopupSel.h
// PopupString.c
// PopupString.h
// ordlistbox.c
// minisetupext.c
// UefiAction.c
// hii.h
// Uefi20wapper.c
// hiicallback.c
// Parse.c
// tseuefihii.h
// Uefi21wapper.c
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
// Name:		numeric.h
//
// Description:	Header file for numeric control
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _NUMERIC_H_
#define	_NUMERIC_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "control.h"
#include "action.h"
#include "MessageBox.h"

#define AMI_BASE_BIN 2
#define AMI_BASE_OCT 8
#define AMI_BASE_DEC 10
#define AMI_BASE_HEX 16
#define AMI_BASE_INT_DEC 32

#define NUMERIC_MIN_MAX_BASE	UINT64 //EIP:60563 to support signed integers for NUMERIC opcode
#define NUMERIC_VALUE_BASE		UINT64
#define	NUMERIC_MEMBER_VARIABLES	\
     UINT8	Base;					\
     NUMERIC_MIN_MAX_BASE MinValue;				\
	 NUMERIC_MIN_MAX_BASE MaxValue;				\
	 NUMERIC_VALUE_BASE	Value;					\
     NUMERIC_MIN_MAX_BASE Step;					\
 	 UINT8   Interval;


typedef struct _NUMERIC_METHODS	NUMERIC_METHODS;

typedef struct _NUMERIC_DATA
{
	NUMERIC_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	EDIT_MEMBER_VARIABLES
	NUMERIC_MEMBER_VARIABLES
}
NUMERIC_DATA;
#define	NUMERIC_METHOD_FUNCTIONS


struct _NUMERIC_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
	EDIT_METHOD_FUNCTIONS
	NUMERIC_METHOD_FUNCTIONS
};

extern NUMERIC_METHODS gNumeric;

// Object Methods
EFI_STATUS NumericCreate( VOID **object );
EFI_STATUS NumericDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS NumericInitialize( VOID *object, VOID *data );
EFI_STATUS NumericDraw( VOID *object );
EFI_STATUS NumericHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS NumericSetCallback( VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );

// Control Methods
EFI_STATUS NumericSetFocus( VOID *object, BOOLEAN focus);
EFI_STATUS NumericSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS NumericSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS NumericSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS NumericGetControlHeight(VOID *object, VOID *frame, UINT16 *height);
#endif /* _NUMERIC_H_ */


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
