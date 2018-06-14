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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/PasswordEncode/PasswordEncode.h $
//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		password.h
//
// Description:	Header file for code to handle password operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _PASSWORDENCODE_H_
#define	_PASSWORDENCODE_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "token.h"

#if TSE_HASH_PASSWORD
#include "Protocol\Hash.h"
#include "Protocol\AmiDigitalSignature.h"
#include "Include\CryptLib.h"
#endif

///////////////////////////////////////////////////////
//		EXTERN FUNCTIONS AND VARIABLES
//////////////////////////////////////////////////////
extern BOOLEAN IsPasswordSupportNonCaseSensitive ();
extern BOOLEAN IsHashingSupported (VOID);
extern BOOLEAN EfiCompareGuid (IN EFI_GUID *Guid1,IN EFI_GUID *Guid2);
extern VOID * EfiLibAllocateZeroPool (IN UINTN AllocationSize);
extern VOID MemCopy( VOID *dest, VOID *src, UINTN size );
extern VOID MemSet( VOID *buffer, UINTN size, UINT8 value );

#endif /* _PASSWORDENCODE_H_ */


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
