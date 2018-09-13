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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/AMILogo/AMILogo.c $
//
// $Author: Premkumara $
//
// $Revision: 7 $
//
// $Date: 8/28/14 5:29a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/AMILogo/AMILogo.c $
// 
// 7     8/28/14 5:29a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 6     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 5     2/26/10 8:53p Madhans
// For TSE 2.01.1024. refer changelog.log for file checkin history .
// 
// 5     2/26/10 1:30p Madhans
// To avoid build issues with EDK.
// 
// 4     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 3     8/17/09 12:22p Presannar
// Removed References to Tiano.h
// 
// 2     6/23/09 6:55p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		AMILogo.c
//
// Description:	This file contains code to handle logo.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifdef TSE_FOR_APTIO_4_50
#include "Token.h"  
#else
#include "tokens.h"
#endif

#if TSE_USE_EDK_LIBRARY
#include "Tiano.h" 
#else
#include "Efi.h" 
#endif

#include "AMILogo.h"

EFI_GUID gAMIEfiLogoGuid = AMI_EFI_LOGO_GUID;
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
