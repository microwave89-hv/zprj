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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/HookList.c $
//
// $Author: Premkumara $
//
// $Revision: 11 $
//
// $Date: 8/28/14 4:28a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/HookList.c $
// 
// 11    8/28/14 4:28a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 10    3/06/13 12:24a Premkumara
// [TAG]  		EIP111415
// [Category]  	Improvement
// [Description]  	Elink function for SETUP_TOGGLE_KEY_UNICODE function
// [Files]  		HookAnchor.h, AMITSE.sdl, commonoem.c, Commonoem.h,
// HookList.c, HookAnchor.c
// 
// 9     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 8     3/28/11 9:06p Madhans
// [TAG]  		EIP41744 
// [Category]  	Improvement
// [Description]  	SoftKeyBoard Support in TSE. and Support to Work with
// new mouse driver(Label 07).
// [Files]  		HookAnchor.h
// AMITSE.sdl
// CommonHelper.c
// commonoem.c
// commonoem.h
// HookList.c
// HookAnchor.c
// Mouse.c
// minisetupext.c
// postmgmtext.c
// minisetupext.h
// PopupPassword.c
// PopupString.c
// TseLiteCommon.c
// 
// 7     9/16/10 8:39p Madhans
// Updated for TSE 2.10. Refer changelog.log for more deatils.
// 
// 6     6/04/10 12:12p Blaines
// Created new AMITSE hook, hook33
// 
// 5     4/16/10 5:10p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 4     2/19/10 12:58p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 4     1/09/10 2:32a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 3     9/15/09 9:20a Sudhirv
// added entry number 31
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards
// 
// 2     6/24/09 11:52a Blaines
// Coding standard update
// 
// 1     6/09/09 9:52a Madhans
// TSE 2.00.1201
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:49p Madhans
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
// Name:		hooklist.c
//
// Description:	AMITSE Hook definitions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifdef TSE_FOR_APTIO_4_50
#include <Efi.h>
#include "Token.h"
#else
#include "Tiano.h"
#include "tokens.h"
#endif

#include "AMITSEElinks.h"

UINTN gHookBase = TSE_HOOKBASE_VALUE;

typedef VOID TSE_HOOK (VOID);

extern TSE_HOOK HOOK_LIST_FROM_ELINKS;

#define HOOK0	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE)
#define HOOK1	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+1)
#define HOOK2	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+2)
#define HOOK3	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+3)
#define HOOK4	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+4)
#define HOOK5	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+5)
#define HOOK6	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+6)
#define HOOK7	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+7)
#define HOOK8	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+8)
#define HOOK9	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+9)
#define HOOK10	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+10)
#define HOOK11	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+11)
#define HOOK12	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+12)
#define HOOK13	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+13)
#define HOOK14	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+14)
#define HOOK15	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+15)
#define HOOK16	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+16)
#define HOOK17	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+17)
#define HOOK18	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+18)
#define HOOK19	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+19)
#define HOOK20	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+20)
#define HOOK21	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+21)
#define HOOK22	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+22)
#define HOOK23	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+23)
#define HOOK24	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+24)
#define HOOK25	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+25)
#define HOOK26	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+26)
#define HOOK27	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+27)
#define HOOK28	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+28)
#define HOOK29	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+29)
#define HOOK30	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+30)
#define HOOK31	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+31)
#define HOOK32	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+32)
#define HOOK33	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+33)
#define HOOK34	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+34)
#define HOOK35	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+35)
#define HOOK36	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+36)
#define HOOK37	(TSE_HOOK *)((UINTN)TSE_HOOKBASE_VALUE+37)//EIP-111415 SwitchToPostScreenHook

TSE_HOOK * AMITSE_HookList [] = {HOOK_LIST_FROM_ELINKS, NULL};

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
