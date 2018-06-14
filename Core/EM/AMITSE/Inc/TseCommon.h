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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/TseCommon.h $
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
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/TseCommon.h $
// 
// 6     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 5     11/20/11 6:38a Rajashakerg
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
// 4     9/20/10 6:46p Madhans
// [TAG]    	EIP44542
// [Category]	BUILD ISSUE FIX
// [Symptom]	Build issues with TSE label (INT)4.6.2_TSE_2_10_1207_TEST
// when IdeSecurity and FastBoot modules added to the project
// [RootCause] -
// [Solution]	Build issues resolved
// [Files]		CommonHelper.c, Tsecommon.h, Hiilib.h, Boot.h, minisetup.h,
// bbs.c, special.c, Bds.c TseLitehelp
// 
// 3     9/16/10 8:39p Madhans
// Updated for TSE 2.10. Refer changelog.log for more deatils.
// 
// 2     8/04/10 12:11a Mallikarjunanv
// EIP-29951 : Device Path Name support updates
// 
// 1     2/19/10 12:58p Madhans
// Uploaded for TSE 2.01. Refer Changelog.log for File change history.
// 
// 2     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 1     10/28/09 5:32p Madhans
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		TseCommon.h
//
// Description:	Tse Common Helper header file
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _TSECOMMON_H_
#define _TSECOMMON_H_

#include "HiiLib.h"
#include "Mem.h"
#include "Variable.h"
#include "PwdLib.h"

EFI_STATUS
EfiLibReportStatusCode (
  IN EFI_STATUS_CODE_TYPE     Type,
  IN EFI_STATUS_CODE_VALUE    Value,
  IN UINT32                   Instance,
  IN EFI_GUID                 *CallerId OPTIONAL,
  IN EFI_STATUS_CODE_DATA     *Data     OPTIONAL  
  );

VOID *
EfiLibAllocateZeroPool (
  IN  UINTN   AllocationSize
  );

extern INTN
EfiCompareMem (
  IN VOID     *MemOne,
  IN VOID     *MemTwo,
  IN UINTN    Len
  );

UINTN
SPrint (
  OUT CHAR16        *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR16  *Format,
  ...
  );

EFI_STATUS ShowPostMsgBox(IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8  MsgBoxType, UINT8 *pSelection);

VOID    CheckForKeyHook( EFI_EVENT Event, VOID *Context );
VOID CheckForClickHook( EFI_EVENT Event, VOID *Context );
VOID    ClearScreen( UINT8 Attrib );
VOID    *SaveScreen( VOID );

extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE *gST;
extern EFI_GUID  gEfiDevicePathProtocolGuid;

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2011, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093       **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
