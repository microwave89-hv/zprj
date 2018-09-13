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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/Jpeg6.h $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/Jpeg6.h $
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
// 4     1/09/10 4:43a Mallikarjunanv
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
// Name:		jpeg6.h
//
// Description:	Header file for jpeg6 image format related code
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _JPEG_6_H_
#define _JPEG_6_H_

#include "Mydefs.h" 



#pragma pack(1)

typedef struct _AMI_TRUECOLOR_PIXEL_JPEG{
	UINT8 Red;
	UINT8 Green;
	UINT8 Blue;
	UINT8 Reserved;
}AMI_TRUECOLOR_PIXEL_JPEG, *PAMI_TRUECOLOR_PIXEL_JPEG;

#pragma pack()

#define MKF_JPEG_YUV111_SUPPORT 1
#define c_g_cb	5638	//; 0.34414   * 16384
#define c_g_cr	11700	//; 0.71417   * 16384


#define c1_16		8352	//;0.509795
#define c3_16		9852	//;0.601344
#define c5_16		14745	//;0.899976
#define c7_16		41990	//;2.562915
#define c1_8		8867	//;0.541196
#define c3_8		21407	//;1.306562
#define c1_4		11585	//;0.707196
#define c1_sqrt2	11585	//;0.707106


#endif //#ifndef _JPEG_6_H_

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
