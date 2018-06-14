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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/HiiLib.h $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 10/18/12 5:31a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/HiiLib.h $
// 
// 6     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 5     9/20/10 6:46p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 4     6/17/10 2:17p Madhans
// Refer Changelog.log.
// 
// 3     2/19/10 12:59p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 7     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 6     1/09/10 2:29a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     10/28/09 5:34p Madhans
// 
// 4     8/13/09 7:33a Mallikarjunanv
// changed after moving the hii ralated function to uefi module from
// binary module
// 
// 3     7/20/09 11:54a Mallikarjunanv
// added external variable gHiiProtocol to use in tse binary
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards.
// 
// 1     6/09/09 9:53a Madhans
// TSE 2.00.1201
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:50p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:24p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		hiilib.h
//
// Description:	Hii related functions 
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _HIILIB_H_
#define _HIILIB_H_

EFI_STATUS HiiInitializeProtocol( VOID );
CHAR16 *HiiGetString( VOID* handle, UINT16 token );
UINT16 HiiAddString( VOID* handle, CHAR16 *string );
UINTN TestPrintLength ( IN CHAR16   *String );

extern VOID * gHiiHandle;

#ifndef INVALID_HANDLE
#define	INVALID_HANDLE	((VOID*)(UINTN)-1)
#endif

#ifndef INVALID_TOKEN
#define	INVALID_TOKEN	((UINT16)-1)
#endif

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2010, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093       **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
