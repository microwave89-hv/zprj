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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSEBoard/OemkeyHook.c $
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
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSEBoard/OemkeyHook.c $
// 
// 6     10/18/12 6:34a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 5     10/10/12 12:25p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 5     2/19/10 12:58p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:04a Mallikarjunanv
// updated year in copyright message
// 
// 3     8/13/09 7:27a Mallikarjunanv
// EIP-25075: Updated files to keep the Board module empty
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
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		oemkeyhook.c
//
// Description:	contains oemkey hook functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifdef TSE_FOR_APTIO_4_50

#include "token.h"
#include <EFI.h>

#else //#ifdef TSE_FOR_APTIO_4_50

#include "minisetup.h"

#endif //#ifdef TSE_FOR_APTIO_4_50

#include "bootflow.h"

///To implement OEM key customizations


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
