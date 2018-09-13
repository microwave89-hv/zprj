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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/callback.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/callback.h $
// 
// 6     10/18/12 6:01a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 6:30a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     6/24/09 6:10p Madhans
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
// Name:		callback.h
//
// Description:	Header file for code to handle callbacks
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _CALLBACK_H_
#define	_CALLBACK_H_


#include "Minisetup.h"

#define	CALLBACK_TYPE_UNKNOWN		0
#define	CALLBACK_TYPE_SUBMENU		1
#define	CALLBACK_TYPE_VARIABLE		2
#define	CALLBACK_TYPE_MESSAGEBOX	3
#define	CALLBACK_TYPE_NVRAM			4
#define	CALLBACK_TYPE_DEFAULTS		5
#define	CALLBACK_TYPE_LABEL			6
#define	CALLBACK_TYPE_PASSWORD		7
#define	CALLBACK_TYPE_MENU		    8
#define	CALLBACK_TYPE_USER			-1

typedef struct _CALLBACK_HEADER
{
	UINT32	Type;
	UINT32	Length;
}
CALLBACK_HEADER;

typedef struct _CALLBACK_SUBMENU
{
	CALLBACK_HEADER	Header;
	UINT16			DestPage;
}
CALLBACK_SUBMENU;

typedef struct _CALLBACK_MENU
{
	CALLBACK_HEADER	Header;
	UINT16			DestPage;
}
CALLBACK_MENU;

typedef struct _CALLBACK_VARIABLE
{
	CALLBACK_HEADER	Header;
	UINT32			Variable;
	UINT32			Offset;
	UINT32			Length;
	VOID			*Data;
}
CALLBACK_VARIABLE;

typedef struct _CALLBACK_PASSWORD
{
	CALLBACK_HEADER	Header;
	UINT32			Variable;
	UINT32			Offset;
	UINT32			Length;
	VOID			*Data;
	BOOLEAN			Encoded;
}
CALLBACK_PASSWORD;

typedef struct _CALLBACK_MESSAGEBOX
{
	CALLBACK_HEADER	Header;
	UINTN			Result;
}
CALLBACK_MESSAGEBOX;

typedef struct _CALLBACK_NVRAM
{
	CALLBACK_HEADER	Header;
	// I can't remember what this type was for
}
CALLBACK_NVRAM;

#define	DEFAULT_TYPE_UNKNOWN	0
#define	DEFAULT_TYPE_FAILSAFE	1
#define	DEFAULT_TYPE_OPTIMAL	2

typedef struct _CALLBACK_DEFAULTS
{
	CALLBACK_HEADER	Header;
	UINT32			Type;
}
CALLBACK_DEFAULTS;

typedef struct _CALLBACK_LABEL
{
	CALLBACK_HEADER	Header;
	UINT32			Key;
}
CALLBACK_LABEL;

typedef struct _CALLBACK_USER
{
	CALLBACK_HEADER	Header;
	VOID			*UserData;
}
CALLBACK_USER;

#endif /* _CALLBACK_H_ */


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
