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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/iJpeg.c $
//
// $Author: Arunsb $
//
// $Revision: 8 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/iJpeg.c $
// 
// 8     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 11    10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     5/10/11 10:43a Madhans
// [TAG]  		EIP59139 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Jpeg image with the resolution 1366x768 is not displayed in
// Screen resolution 1366x768.
// [RootCause]  	Jepg Algorithem does the decoding in 16 pixel boudary. As
// 1366 is not in 16 bit boundary the image width is returned as 1376 to
// make 16bit boundary.
// [Solution]  	Once decoded the Blt buffer is formed with orginal
// resolution from the image.
// [Files]  		ijpeg.c
// 
// 6     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 9     2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
// 
// 8     1/09/10 4:43a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 7     9/02/09 7:39p Madhans
// To fix the Logo Security issue correctly.
// 
// 6     8/13/09 12:15p Blaines
// Move Image support to binary module
// 
// 5     7/08/09 3:34p Madhans
// Coding Standards.
// 
// 4     6/24/09 6:10p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
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
// 1     9/26/06 4:03p Madhans
// JpegC Implimentation
// 
// 2     9/15/06 9:57a Shirinmd
// Initialized UgaBlt buffer to 0
// 
// 1     8/01/06 8:03a Shirinmd
// Files for JPEG decoding (C version)
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		iJpeg.c
//
// Description:	Adds jpeg Support.
//
//<AMI_FHDR_END>
//*****************************************************************//
#include "jpeg.h"

BOOL GetJPEGDimensions(BYTE * pbyJPEGInputData, UINT32 * pun32Width, UINT32 * pun32Height);
BOOL DecodeJPEG(WORD wXPos, WORD wYPos, BYTE * pbyJPEGInputData, BYTE * pbyJPEGOutputData, UINT32 un32BufferWidth, UINT32 un32BufferHeight);


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertJPEGToUgaBlt
//
// Description:	Decode the JPEG and store the output in UGA format. The 
//					JPEG images are stored in 16X16 blocks. Hence Buffer will 
//					require width and hieght that are equal to or more than 
//					the actual width and hieght. Buffer Width and Height will 
//					be the lowest multipe of 16 that is equal to or greater than 
//					the actual width and height.
//					Eg: For decoding an image with Actual sizes being 17X33 will 
//						require a buffer of 32X48.
//
// Input:	IN VOID *JPEGImage - Pointer to the memory that has the 
//										 JPEG Image that need to be decoded.
//					IN UINT32 JPEGImageSize - Size of the JPEG Image
//					IN OUT VOID **UgaBlt - Two cases
//						Case 1: Memory is expected to be allocated by the callee.
//								Address provided as input should be NULL.
//								pointer that will recieve the address of the UGA buffer.
//								The buffer is allocated by callee.
//								This buffer need to be freed by the caller.
//						Case 2: Memory is allocated by the caller
//					IN OUT UINT32 *UgaBltSize - Pointer that stores Size of UgaBlt 
//						in bytes. This will be treated as an input. This should have 
//						value ZERO for Case 2 above.
//					OUT UINT32 *PixelHeight - Height of UgaBlt/JPEG Image in pixels
//					OUT UINT32 *PixelWidth - Width of UgaBlt/JPEG Image in pixels
//					OUT UINT32 *pun32BufferWidth - Width of UgaBlt/JPEG Buffer
//
// Output:	EFI_SUCCESS	- The image was successfully decoded and placed in the buffer
//					EFI_UNSUPPORTED
//					EFI_BUFFER_TOO_SMALL
//					EFI_OUT_OF_RESOURCES
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertJPEGToUgaBlt ( IN VOID *JPEGImage, IN UINT32 JPEGImageSize, IN OUT VOID **UgaBlt, IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth, OUT UINT32 *pun32BufferWidth)
{
	BOOL bStatus=FALSE;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT64    BltBufferSize =0; 
	UINT32 un32PadWidth= 0, un32PadHeight=0;
	
	bStatus = GetJPEGDimensions(JPEGImage, PixelWidth, PixelHeight);

	if(bStatus){
//We need to add a little memory to deal cases when the Width or height is not a
//multiple of 16 or else we need to add a fix with in output_8x8_image function
		un32PadWidth = 16 - (*PixelWidth)%16;
		if(un32PadWidth==16){
			un32PadWidth = 0;
		}
		un32PadHeight = 16 - (*PixelHeight)%16;
		if(un32PadHeight==16){
			un32PadHeight = 0;
		}
		*pun32BufferWidth = *PixelWidth + un32PadWidth;
	
		// Make sure to do x64 Mul
		BltBufferSize = MultU64x32((UINT64)(*pun32BufferWidth) ,(*PixelHeight + un32PadHeight));

		/// Check whether the Size exceeds the limit...
		//  4GB/PIXEL_SIZE becoz we need Resolution*PIXEL_SIZE for bltbuffer
		if ( BltBufferSize >= (FOUR_GB_LIMIT/sizeof (EFI_UGA_PIXEL))) {
			// The buffer size extends the limitation
			return EFI_UNSUPPORTED;
		}

		BltBufferSize = MultU64x32( BltBufferSize ,sizeof (EFI_UGA_PIXEL));

		if(NULL!=*UgaBlt)
		{
			if (*UgaBltSize < (UINT32)BltBufferSize)
					{
						*UgaBltSize = (UINT32)BltBufferSize;
						bStatus = FALSE;
						Status = EFI_BUFFER_TOO_SMALL;
					}	
		}
		else
		{
			*UgaBltSize = (UINT32)BltBufferSize;
			*UgaBlt = EfiLibAllocatePool((UINT32)BltBufferSize);
			if(*UgaBlt == NULL) 
			{
				Status = EFI_OUT_OF_RESOURCES;
				bStatus = FALSE;
			}

		}
		if(TRUE==bStatus)
		{	
			memset(*UgaBlt, (UINT32)BltBufferSize, 0 );
			bStatus = DecodeJPEG(0,0, JPEGImage, *UgaBlt, *pun32BufferWidth , (*PixelHeight + un32PadHeight));
			if(bStatus){
				Status = EFI_SUCCESS;
                if(un32PadWidth) 
                {
                    // Padding Done. Need to discard the Extra Width and Height.
                    EFI_UGA_PIXEL *BltBuf = NULL;
                    UINT32 i;

                    // Recalculate the actual Buffer
                    BltBufferSize = MultU64x32((UINT64)(*PixelWidth) ,*PixelHeight);
            		BltBufferSize = MultU64x32( BltBufferSize ,sizeof (EFI_UGA_PIXEL));
        			BltBuf = EfiLibAllocatePool((UINT32)BltBufferSize);

                    if(BltBuf == NULL) 
        			{   // Out of resources.
                        MemFreePointer( (VOID **)UgaBlt);
        				Status = EFI_OUT_OF_RESOURCES;
        				bStatus = FALSE;
        			}
                    // Copy the bltbuf for *PixelWidth in each line.
                    for(i=0;i<*PixelHeight;i++)
                    {
                        gBS->CopyMem((VOID*)&(BltBuf[(*PixelWidth * i)]),(VOID*)&(((EFI_UGA_PIXEL*)(*UgaBlt))[(*pun32BufferWidth * i)]),sizeof(EFI_UGA_PIXEL) * *PixelWidth);
                    }
                    *pun32BufferWidth = *PixelWidth; // Unpadded Width.
                    MemFreePointer( (VOID **)UgaBlt); // Free the Orgianl Blt. 
                    *UgaBlt = (VOID*)BltBuf;    // New blt
        			*UgaBltSize = (UINT32)BltBufferSize; // New size
                }
			}
		}		
	}
	
	return Status;
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
