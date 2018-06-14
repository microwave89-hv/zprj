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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSEBoard/TseBoard.c $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 10/18/12 6:34a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSEBoard/TseBoard.c $
// 
// 6     10/18/12 6:34a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:25p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 5     2/19/10 12:58p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:04a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 2:49a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     8/13/09 7:27a Mallikarjunanv
// EIP-25075: Updated files to keep the Board module empty
// 
// 3     8/03/09 7:54a Mallikarjunanv
// Moved the IDE Security related hook functions from Tse Binary to Tse
// Board Module
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards
// 
// 2     6/24/09 11:54a Blaines
// Coding standard update
// 
// 1     6/09/09 9:53a Madhans
// TSE 2.00.1201
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 11:03p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:25p Madhans
// Tse 2.0 Code complete Checkin.
// 
//
//*****************************************************************//
//*****************************************************************//

#include "token.h"
#include <EFI.h>
#include <Protocol/AMIPostMgr.h>
#include "PwdLib.h"

// This Module is to implement the OME Functions, which can be override the existing TSE functions.
// For Example, UEFI Callback 
// If Board module handle the Passwordwith Formcallback and return sccuess then 
// TSE will not takecare of Password handling.



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
