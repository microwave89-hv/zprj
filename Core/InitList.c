//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/InitList.c 3     6/16/05 10:42a Felixp $
//
// $Revision: 3 $
//
// $Date: 6/16/05 10:42a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/InitList.c $
// 
// 3     6/16/05 10:42a Felixp
// 1. Tokens.c added. It has variables representing SDL tokens.
// 2. InitList.c extended to support 2 init lists
// 
// 2     3/04/05 12:38p Mandal
// 
// 1     1/28/05 12:43p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     7/12/04 6:31p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	InitList.c
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#include <efi.h>
typedef EFI_STATUS (INIT_FUNCTION)(IN VOID* ImageHandle, IN VOID *SystemTable);
//First init function
#ifdef INIT_LIST
extern INIT_FUNCTION INIT_LIST EndOfInitList;
INIT_FUNCTION* InitList[] = {INIT_LIST NULL};

VOID InitParts(IN VOID* ImageHandle, IN VOID *SystemTable)
{
	UINTN i;
	for(i=0; InitList[i]; i++) InitList[i](ImageHandle,SystemTable);
}
#endif

//Second init function
#ifdef INIT_LIST2
extern INIT_FUNCTION INIT_LIST2 EndOfInitList;
INIT_FUNCTION* InitList2[] = {INIT_LIST2 NULL};

VOID InitParts2(IN VOID* ImageHandle, IN VOID *SystemTable)
{
	UINTN i;
	for(i=0; InitList2[i]; i++) InitList2[i](ImageHandle,SystemTable);
}
#endif
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
