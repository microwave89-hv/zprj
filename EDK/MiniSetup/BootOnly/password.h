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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/password.h $
//
// $Author: Arunsb $
//
// $Revision: 2 $
//
// $Date: 10/18/12 5:59a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/password.h $
// 
// 2     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:37p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 1     12/08/11 4:54a Arunsb
// EIP63190 => Moving password support from TSELite to BootOnly
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
// Name:		password.h
//
// Description:	Header file for code to handle password operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _PASSWORD_H_
#define	_PASSWORD_H_

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

BOOLEAN _PasswordProtocolInit( VOID );
BOOLEAN PasswordBootMode( VOID );
UINT32 PasswordCheckInstalledVarIndex( UINT32 VarIndex );
UINT32 PasswordAuthenticate( CHAR16 *Password );
BOOLEAN PasswordAuthenticateVarIndex( UINT32 VarIndex, CHAR16 *Password );
CHAR16 *PasswordUpdate( CHAR16 *Password, UINTN Size );
VOID PasswordCommitChanges( BOOLEAN SaveChanges );

#endif /* _PASSWORD_H_ */


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
