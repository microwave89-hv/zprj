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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/pcx.h $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/pcx.h $
// 
// 4     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 6     10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 3     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
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
// 1     6/30/06 4:22p Madhans
// PCX image support in C.
// 
// 1     6/16/06 8:15a Shirinmd
// Added PCX Support in C for Minisetup
//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		pcx.h
//
// Description:	Header file for pcx image format related code
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#ifndef _PCX_H_13_JUNE_2006
#define _PCX_H_13_JUNE_2006

#include "MyDefs.h"

#pragma pack(1)

typedef struct _AMI_TRUECOLOR_PIXEL{
	BYTE Blue;
	BYTE Green;
	BYTE Red;
	BYTE Reserved;
}AMI_TRUECOLOR_PIXEL, *PAMI_TRUECOLOR_PIXEL;

#pragma pack()


//PCX File Header (128 bytes)
typedef struct _PCX_HEADER{
	BYTE bManufacturer;
	BYTE bVersion;
	BYTE bEncoding;
	BYTE bBitsPerPixel;
	WORD wXmin;
	WORD wYmin;
	WORD wXmax;
	WORD wYmax;
	WORD wHres;
	WORD wVres;
	BYTE bPalette[48];
	BYTE bReserved;
	BYTE bColorPlanes;
	WORD wBytesPerLine;
	WORD wPaletteType;
	WORD wHorizontalSize;
	WORD wVerticalSize;
	BYTE bFiller[54];
}PCX_HEADER;

typedef struct _PCX_INFO{
	WORD wImageWidth;
	WORD wImageHeight;
	WORD wBytesPerLine;
	BYTE bBitsPerPixel;
	DWORD dwPCXImageSize;
	BYTE *bpPCXData;
	BYTE *bpPalette;
}PCX_INFO;


#endif //#ifndef _PCX_H_13_JUNE_2006

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
