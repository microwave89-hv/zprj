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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/buffer.h $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 5:58a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/buffer.h $
// 
// 4     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 3     2/19/10 1:01p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Buffer.h
//
// Description:	Header file for code to manage buffers
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _BUFFER_H_
#define	_BUFFER_H_

VOID FlushLines( UINTN Top, UINTN Bottom );
VOID DoRealFlushLines();

#endif /* _BUFFER_H_ */

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
