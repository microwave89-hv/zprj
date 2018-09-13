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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/pcxc.c $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/pcxc.c $
// 
// 5     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
// 
// 5     8/13/09 12:16p Blaines
// Move Image support to binary module
// 
// 4     8/04/09 10:23a Madhans
// Fix to support big PCX images.(previously it was not supporing 800x600
// images.)
// 
// 3     6/23/09 7:09p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
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
// 3     7/05/06 11:19a Madhans
// 
// 2     7/05/06 11:09a Madhans
// DecodePCX function optimized.
// 
// 1     6/30/06 4:22p Madhans
// PCX image support in C.
// 
// 2     6/26/06 8:41a Shirinmd
// Modifications based on design change suggested by Madhan
// 
// 1     6/16/06 8:15a Shirinmd
// Added PCX Support in C for Minisetup
//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		pcx.c
//
// Description:	This file contains code for pcx image handling
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "pcx.h"


AMI_TRUECOLOR_PIXEL * ScreenBuffer = (AMI_TRUECOLOR_PIXEL *)NULL;

//Functions
BOOL PCX_Init(BYTE * pbyPCXImage, PCX_INFO *pPCX_INFO, DWORD dwPCXImageSize);
BOOL GetPCXDimensions( BYTE * pbyPCXImageData, UINT32 * pn32Width, UINT32 * pn32Height);
BOOL DecodePCX(BYTE * pbyPCXInputData, BYTE * pbyPCXOutputData, DWORD dwPCXImageSize);
void Decode_Line(DWORD *wCountX, PCX_INFO *pPCX_INFO, BYTE *pbOneLineBuffer);
void Output_Line(DWORD wTop, PCX_INFO *pPCX_INFO, BYTE *pbOneLineBuffer);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PCX_Init
//
// Description:	This routine is used to fill the PCX_INFO structure.
//
// Input:	BYTE * pbyPCXImage - Pointer that gives the memory location 
//						where the PCX input data is available.
//					PCX_INFO *pPCX_INFO	- Pointer to PCX_INFO structure
//					DWORD dwPCXImageSize - Size of the PCX Image
//
// Output:	BOOL - TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOL PCX_Init(BYTE * pbyPCXImage, PCX_INFO *pPCX_INFO, DWORD dwPCXImageSize)
{
	PCX_HEADER *pPCX_HEADER = (PCX_HEADER *)pbyPCXImage;

	if(pPCX_HEADER->bVersion != 5 || pPCX_HEADER->bBitsPerPixel == 1 || pPCX_HEADER->bBitsPerPixel == 2 || pPCX_HEADER->bColorPlanes != 1)
		return FALSE;
	
	pPCX_INFO->wImageWidth		= pPCX_HEADER->wXmax - pPCX_HEADER->wXmin + 1;
	pPCX_INFO->wImageHeight		= pPCX_HEADER->wYmax - pPCX_HEADER->wYmin + 1;
	pPCX_INFO->wBytesPerLine	= pPCX_HEADER->wBytesPerLine;
	pPCX_INFO->bBitsPerPixel	= pPCX_HEADER->bBitsPerPixel;	
	pPCX_INFO->dwPCXImageSize	= dwPCXImageSize;
	pPCX_INFO->bpPCXData		= pbyPCXImage + 128;
	if(pPCX_HEADER->bBitsPerPixel == 8)			//256 color image palette at the end
		pPCX_INFO->bpPalette	= pbyPCXImage + dwPCXImageSize - 768;
	else if(pPCX_HEADER->bBitsPerPixel == 4)	//16 color image palette in the header
		pPCX_INFO->bpPalette	= pPCX_HEADER->bPalette;
	return TRUE;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetPCXDimensions
//
// Description:	Get the dimensions (Width and Height of the PCX Image).
//
// Input:	BYTE * pbyPCXImageData - Pointer to the buffer that contains the PCX data
//					UINT32 * pun32Width - Pointer to the UINT32 variable that will 
//						receive the Width of the PCX Image
//					UINT32 * pun32Height - Pointer to the UINT32 variable that 
//						will receive the Height of the PCX Image
//
// Output:	BOOL - TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOL GetPCXDimensions( BYTE * pbyPCXImageData, UINT32 * pun32Width, UINT32 * pun32Height){
	BOOL bReturn = FALSE;
	WORD wWidth = 0;
	WORD wHeight= 0;
	wWidth  = *((WORD*)(pbyPCXImageData+8)) - *((WORD*)(pbyPCXImageData+4)) + 1;
	wHeight = *((WORD*)(pbyPCXImageData+10)) - *((WORD*)(pbyPCXImageData+6)) + 1;
	if( (wWidth > 0) && (wHeight > 0))
	{
		*pun32Width = (UINT32)wWidth;
		*pun32Height = (UINT32)wHeight;
		bReturn = TRUE;
	}
	return bReturn;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	Decode_Line
//
// Description:	This routine will first check whether the PCX image is 16 
//					color or 256 color and then decode the PCX image data one 
//					line at a time and put the decoded data in a One Line Buffer.
//
// Input:	WORD *wCountX - Pointer to the index of the image data after 128 byte header
//					PCX_INFO *pPCX_INFO - Pointer to PCX_INFO structure
//					BYTE *pbOneLineBuffer - Pointer to the buffer that holds one line of decoded data.
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Decode_Line(DWORD *wCountX, PCX_INFO *pPCX_INFO, BYTE *pbOneLineBuffer)
{
	WORD wOffset_of_buffer = 0;
	int nDataCount = 0;
	WORD wLength_of_buffer = 0;
	while(wLength_of_buffer < (pPCX_INFO->wImageWidth))
	{
		if((pPCX_INFO->bpPCXData[*wCountX] & 0xC0) >= 0xC0)
			nDataCount = (pPCX_INFO->bpPCXData[(*wCountX)++] & 0x3f);
		else
			nDataCount = 1;

		while(nDataCount--)
		{
			if(pPCX_INFO->bBitsPerPixel == 8)
			{
				pbOneLineBuffer[wOffset_of_buffer++] = pPCX_INFO->bpPCXData[*wCountX];
				(wLength_of_buffer)++;
			}
			else if(pPCX_INFO->bBitsPerPixel == 4)
			{
				pbOneLineBuffer[wOffset_of_buffer++] = ((pPCX_INFO->bpPCXData[*wCountX]) >> 4);
				pbOneLineBuffer[wOffset_of_buffer++] = ((pPCX_INFO->bpPCXData[*wCountX]) & 0x0f);
				(wLength_of_buffer) = (wLength_of_buffer)+2;
			}
		}
		(*wCountX)++;
	}


	if(pPCX_INFO->bBitsPerPixel == 8)
	{
		if((pPCX_INFO->wImageWidth) != (pPCX_INFO->wBytesPerLine))
			(*wCountX)++;
	}
	else if(pPCX_INFO->bBitsPerPixel == 4)
	{
		if(wLength_of_buffer < ((pPCX_INFO->wBytesPerLine)<<1))
			(*wCountX)++;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	Output_Line
//
// Description:	This routine is used to map the decoded data to the palette 
//					and fill the global Screen Buffer. 
//
// Input:	WORD wTop - This variable gives the position from where a 
//						line should start in the Screen Buffer
//					PCX_INFO *pPCX_INFO - Pointer to PCX_INFO structure
//					BYTE *pbOneLineBuffer - Pointer to the buffer that holds one line of decoded data.
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Output_Line(DWORD wTop, PCX_INFO *pPCX_INFO, BYTE *pbOneLineBuffer)
{
	WORD wCountX;
	int nIndex;
	AMI_TRUECOLOR_PIXEL * pStartofLineInScreenBuffer = (AMI_TRUECOLOR_PIXEL *)ScreenBuffer + (wTop*(pPCX_INFO->wImageWidth));

		for(wCountX = 0; wCountX< pPCX_INFO->wImageWidth; wCountX++)		
		{
			nIndex = (3 * (int)(pbOneLineBuffer[wCountX]));
			pStartofLineInScreenBuffer->Red = pPCX_INFO->bpPalette[nIndex];
			pStartofLineInScreenBuffer->Green = pPCX_INFO->bpPalette[nIndex + 1];
			pStartofLineInScreenBuffer->Blue = pPCX_INFO->bpPalette[nIndex + 2];
			pStartofLineInScreenBuffer++;
		}


}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DecodePCX
//
// Description:	This routine will call functions to decode both 16 and 256 
//					color PCX images of version 5 (with palette information) and 
//					fill the Screen Buffer.
//
// Input:	BYTE * pbyPCXInputData - Pointer that gives the memory location 
//						where the PCX input data is available.
//					BYTE * pbyPCXOutputData - Pointer to the buffer that will 
//						receive the decoded PCX image
//					DWORD dwPCXImageSize - Size of the PCX Image
//
// Output:	BOOL - TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOL DecodePCX(BYTE * pbyPCXInputData, BYTE * pbyPCXOutputData, DWORD dwPCXImageSize)
{
	PCX_INFO pcx_info;
	BYTE  * bOneLineBuffer = NULL;
	DWORD wCountY = 0;
	DWORD wCountX = 0;

	bOneLineBuffer = EfiLibAllocatePool(sizeof(BYTE)*1280);
	if(bOneLineBuffer == NULL)
		return FALSE;

	ScreenBuffer = (AMI_TRUECOLOR_PIXEL *)pbyPCXOutputData;
	if(PCX_Init(pbyPCXInputData, &pcx_info, dwPCXImageSize))
	{
		for(wCountY = 0; wCountY < pcx_info.wImageHeight; wCountY++)
		{
			Decode_Line(&wCountX, &pcx_info, bOneLineBuffer);
			Output_Line(wCountY, &pcx_info, bOneLineBuffer);
		}
		MemFreePointer( (VOID **)&bOneLineBuffer);
		return TRUE;
	}
	else
	{
		MemFreePointer( (VOID **)&bOneLineBuffer);
		return FALSE;
	}
}
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
