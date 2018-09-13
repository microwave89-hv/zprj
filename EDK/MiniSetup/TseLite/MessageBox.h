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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/MessageBox.h $
//
// $Author: Premkumara $
//
// $Revision: 10 $
//
// $Date: 8/28/14 6:05a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/MessageBox.h $
// 
// 10    8/28/14 6:05a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 9     10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     12/01/11 5:42a Rajashakerg
// [TAG]  		EIP74963 
// [Category]  	Improvement
// [Description]  	MAX_MSGBOX_WIDTH cannot be overridden
// [Files]  		AMITSE.sdl, CommonHelper.c, minisetup.h, legacy.c,
// MessageBox.c, MessageBox.h, FormBrowser.c
// 
// 7     4/21/10 12:01p Madhans
// Tse 2.02
// 
// 9     4/20/10 6:22p Blaines
// Define MSGBOX_MAX_OPTIONS
// 
// 8     3/26/10 6:53p Madhans
// Support to Map the do the Control Mapping from gTseControlMap Table. So
// no changes need in Frame.c, With this feature gTseControlMap Can be
// customized to add/customize the TSE controls.
// 
// 7     3/23/10 5:20p Blaines
// Extend Message Box support
//     Adds Custom Type
//     Adds Progress Bar Type
// 
// 6     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 5     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 4     2/04/10 11:17p Madhans
// Mouse support related code optimized
// 
// 3     8/17/09 12:27p Presannar
// Removed References to Tiano.h and replaced it with Efi.h
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

#ifndef _MSGBOX_H_
#define	_MSGBOX_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "popup.h"
#include "Memo.h"  

//EIP74963 : MAX_MSGBOX_WIDTH macro changed as token and handled from binary
//#define MAX_MSGBOX_WIDTH		45
// messagebox constants
#define MSGBOX_TYPE_NULL        0
#define MSGBOX_TYPE_OK			1
#define MSGBOX_TYPE_OKCANCEL	2
#define MSGBOX_TYPE_YESNO		3
#define MSGBOX_TYPE_CUSTOM		4
#define MSGBOX_TYPE_PROGRESS		5  	// internal use only (NOT PUBLISHED)
#define	MSGBOX_TYPE_MASK		0x0F
#define MSGBOX_TYPE_MAXTYPE     MSGBOX_TYPE_MASK
#define	MSGBOX_STYLE_CENTER		(UINT8)(JUSTIFY_CENTER << 4)
#define	MSGBOX_STYLE_RIGHT		(UINT8)(JUSTIFY_RIGHT << 4)
#define	MSGBOX_STYLE_LEFT		(UINT8)(JUSTIFY_LEFT << 4)
#define	MSGBOX_STYLE_MASK		0xF0
#define MSGBOX_OK				0
#define MSGBOX_CANCEL			1
#define MSGBOX_YES				0	
#define MSGBOX_NO				1

#define MSGBOX_MAX_OPTIONS		4
typedef struct _IFR_MSGBOX
{ // this structure is, in some way, following EFI_IFR structures
	UINT8	Opcode, Length;
	UINT16	Title;
	/*EFI_HII_HANDLE*/VOID * 	TextHandle;
	UINT16	Text;
}AMI_IFR_MSGBOX;

#define	MSGBOX_MEMBER_VARIABLES	\
    VOID	*ScreenBuf;			\
	MEMO_DATA *Memo;			\
	UINT8	MsgBoxType;			\
	UINT8	MsgboxSel;			\
	UINT8	Button1Len;			\
	UINT8	Button2Len;			\
	CHAR16	*Legend;			\
	MSGBOX_EX_CATAGORY MsgBoxCatagory;	\
	UINT16  *PtrTokens;			\
	UINT16  OptionCount;			\
	AMI_POST_MGR_KEY  *HotKeyList;		\
	UINT16 	HotKeyListCount; 		\
	AMI_POST_MGR_KEY  *OutKey;		\
	UINTN 	Percent;				// 0 - 100


typedef struct _MSGBOX_METHODS	MSGBOX_METHODS;

typedef struct _MSGBOX_DATA
{
	MSGBOX_METHODS	*Methods;

	OBJECT_MEMBER_VARIABLES
	CONTROL_MEMBER_VARIABLES
	POPUP_MEMBER_VARIABLES
	MSGBOX_MEMBER_VARIABLES
}
MSGBOX_DATA;

typedef	EFI_STATUS	(*MSGBOX_METHOD_SET_TYPE)		( VOID *object, UINT8 Type );

#define	MSGBOX_METHOD_FUNCTIONS \
      MSGBOX_METHOD_SET_TYPE SetType;

struct _MSGBOX_METHODS
{
	OBJECT_METHOD_FUNCTIONS
	CONTROL_METHOD_FUNCTIONS
    MSGBOX_METHOD_FUNCTIONS
};

extern MSGBOX_METHODS gMsgBox;


// Object Methods
EFI_STATUS MsgBoxCreate( VOID **object );
EFI_STATUS MsgBoxDestroy( VOID *object, BOOLEAN freeMem );
EFI_STATUS MsgBoxInitialize( VOID *object, VOID *data );
EFI_STATUS MsgBoxDraw( VOID *object );
EFI_STATUS MsgBoxHandleAction(VOID *object, ACTION_DATA *Data);
EFI_STATUS MsgBoxSetCallback(  VOID *object, VOID *container, OBJECT_CALLBACK callback, VOID *cookie );
EFI_STATUS MsgBoxSetType(VOID *object, UINT8 Type );

// Control Methods
EFI_STATUS MsgBoxSetFocus(VOID *object, BOOLEAN focus);
EFI_STATUS MsgBoxSetPosition(VOID *object, UINT16 Left, UINT16 Top);
EFI_STATUS MsgBoxSetDimensions(VOID *object, UINT16 Width, UINT16 Height);
EFI_STATUS MsgBoxSetAttributes(VOID *object, UINT8 FGColor, UINT8 BGColor);
EFI_STATUS MsgBoxGetControlHight( VOID *object,VOID *frame, UINT16 *height );

#endif /* _MSGBOX_H_ */


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
