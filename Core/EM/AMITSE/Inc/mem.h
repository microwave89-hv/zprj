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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/mem.h $
//
// $Author: Arunsb $
//
// $Revision: 5 $
//
// $Date: 10/18/12 5:31a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/mem.h $
// 
// 5     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 5     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 4     11/10/11 12:46a Arunsb
// [TAG]  		EIP67735
// [Category]  	Improvement
// [Description]  	Zeroing password buffers before freeing
// [Files]  		mem.c, mem.h, popupedit.c, popuppassword.c and tseadvanced.c
// 
// 3     2/19/10 12:59p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 3     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 2     6/24/09 6:12p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
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
// Name:		mem.h
//
// Description:	memory utility functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _MEM_H_
#define _MEM_H_

VOID MemFreePointer (VOID **ptr);
VOID StringZeroFreeMemory (VOID **ptr);
VOID MemCopy( VOID *dest, VOID *src, UINTN size );
VOID MemSet( VOID *buffer, UINTN size, UINT8 value );
#if !TSE_USE_EDK_LIBRARY
INTN MemCmp( VOID *dest, VOID *src, UINTN size );
#endif
VOID *MemReallocateZeroPool( VOID *oldBuffer, UINTN oldSize, UINTN newSize );
VOID MemFillUINT16Buffer( VOID *buffer, UINTN bufferSize, UINT16 value );

#endif /* _MEM_H_ */

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
