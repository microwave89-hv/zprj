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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/jpeg.h $
//
// $Author: Arunsb $
//
// $Revision: 5 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/jpeg.h $
// 
// 5     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
// 
// 4     1/09/10 4:44a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:43p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:16p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:27p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     9/26/06 4:03p Madhans
// JpegC Implimentation
// 
// 1     8/01/06 8:03a Shirinmd
// Files for JPEG decoding (C version)
//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		jpeg.h
//
// Description:	Header file for jpeg image format related code
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _JPEG_H_
#define _JPEG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MyDefs.h"
#include "jpeg6.h"

EFI_STATUS ConvertJPEGToUgaBlt ( IN VOID *JPEGImage, IN UINT32 JPEGImageSize, IN OUT VOID **UgaBlt, IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth, OUT UINT32 *pun32BufferWidth);

#ifdef __cplusplus
}
#endif

#endif //#ifndef _JPEG_H_

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
