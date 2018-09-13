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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/dobmpmgr.c $
//
// $Author: Arunsb $
//
// $Revision: 13 $
//
// $Date: 10/18/12 5:58a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/dobmpmgr.c $
// 
// 13    10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 11    9/17/12 6:10a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 9     8/29/12 12:38p Arunsb
// [TAG]  		EIP93521
// [Category]  	New Feature
// [Description]  	Support of ESRT
// [Files]  		amitse.sdl, bootflow.c, bootflow.h, commonhelper.c and
// dobmpmgr.c
// 
// 8     8/23/12 6:24p Arunsb
// Reverted back 2.15.1229 for making GTSE, TSELite and BootOnly labels
//
// 7     8/21/12 7:57p Arunsb
// [TAG]  		EIP93521, EIP92901 and EIP92900
// [Category]  	New Feature
// [Description]  	Support of ESRT
// [Files]  		amitse.sdl, bootflow.c, bootflow.h, commonhelper.c and
// dobmpmgr.c
// 
// 6     2/19/10 1:01p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 7     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 6     9/02/09 7:40p Madhans
// To Realy fix the Logo Security issue
// 
// 5     8/13/09 12:14p Blaines
// Move Image support to binary module
// 
// 4     6/24/09 6:09p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
// 
// 3     6/23/09 6:56p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
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
// Name:		DoBMPmgr.c
//
// Description:	file contains code that is  taken from graphics.c 
//				to eliminnate library dependancy
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


//#if SETUP_BMP_LOGO_SUPPORT

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemFreePointer
//
// Description:	Convert a *.BMP graphics image to a UGA blt buffer. 
//					If a NULL UgaBlt buffer is passed in a UgaBlt buffer will 
//					be allocated by this routine. If a UgaBlt buffer is passed 
//					in it will be used if it is big enough.
//
// Input:		BmpImage      - Pointer to BMP file
//					BmpImageSize  - Number of bytes in BmpImage
//					UgaBlt        - Buffer containing UGA version of BmpImage.
//					UgaBltSize    - Size of UgaBlt in bytes.
//					PixelHeight   - Height of UgaBlt/BmpImage in pixels
//					PixelWidth    - Width of UgaBlt/BmpImage in pixels
//
// Output:		EFI_SUCCESS           - UgaBlt and UgaBltSize are returned. 
//					EFI_UNSUPPORTED       - BmpImage is not a valid *.BMP image
//					EFI_BUFFER_TOO_SMALL  - The passed in UgaBlt buffer is not big enough.
//                      UgaBltSize will contain the required size.
//					EFI_OUT_OF_RESOURCES  - No enough buffer to allocate
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ConvertBmpToUgaBlt (
  IN  VOID      *BmpImage,
  IN  UINTN     BmpImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *PixelHeight,
  OUT UINTN     *PixelWidth
  )
{
	UINT8             *Image;
	BMP_IMAGE_HEADER  *BmpHeader;
	BMP_COLOR_MAP     *BmpColorMap;
	EFI_UGA_PIXEL     *BltBuffer;
	EFI_UGA_PIXEL     *Blt;
	UINT64			  BltBufferSize;
	UINTN             Index;
	UINTN             Height;
	UINTN             Width;
	UINTN             ImageIndex;

	BmpHeader = (BMP_IMAGE_HEADER *) BmpImage;
	if (BmpHeader->CharB != 'B' || BmpHeader->CharM != 'M') 
  		return EFI_UNSUPPORTED;
  
	if (BmpHeader->CompressionType != 0) 
		return EFI_UNSUPPORTED;
  
	// Calculate Color Map offset in the image.
	Image       = BmpImage;
	BmpColorMap = (BMP_COLOR_MAP *) (Image + sizeof (BMP_IMAGE_HEADER));

	// Calculate graphics image data address in the image
	Image         = ((UINT8 *) BmpImage) + BmpHeader->ImageOffset;

	// Make sure to do x64 Mul
	BltBufferSize = MultU64x32((UINT64)BmpHeader->PixelWidth ,BmpHeader->PixelHeight);

	/// Check whether the Size exceeds the limit...
	//  4GB/PIXEL_SIZE becoz we need Resolution*PIXEL_SIZE for bltbuffer
	if ( BltBufferSize >= (FOUR_GB_LIMIT/sizeof (EFI_UGA_PIXEL))) {
		// The buffer size extends the limitation
		return EFI_UNSUPPORTED;
	}

	BltBufferSize = MultU64x32( BltBufferSize ,sizeof (EFI_UGA_PIXEL));

	if (*UgaBlt == NULL) 
	{
		*UgaBltSize = (UINTN)BltBufferSize;
		*UgaBlt     = EfiLibAllocatePool (*UgaBltSize);
		if (*UgaBlt == NULL) 
			return EFI_OUT_OF_RESOURCES;
    }
	else 
	{
		if (*UgaBltSize < (UINTN)BltBufferSize) 
		{
			*UgaBltSize = (UINTN)BltBufferSize;
			return EFI_BUFFER_TOO_SMALL;
		}
	}

	*PixelWidth   = BmpHeader->PixelWidth;
	*PixelHeight  = BmpHeader->PixelHeight;

    // Convert image from BMP to Blt buffer format
  
	BltBuffer = *UgaBlt;
	for (Height = 0; Height < BmpHeader->PixelHeight; Height++) 
	{
		Blt = &BltBuffer[(BmpHeader->PixelHeight - Height - 1) * BmpHeader->PixelWidth];
		for (Width = 0; Width < BmpHeader->PixelWidth; Width++, Image++, Blt++) 
		{
			switch (BmpHeader->BitPerPixel) 
			{
				case 1: //the bitmap is monochrome		//EIP93521 and EIP92900
					//for every bit
					for(Index = 8; Index ; Index--)
					{
						if(1<<(Index-1) & *Image)
						{
							Blt->Red    = BmpColorMap[1].Red;
							Blt->Green  = BmpColorMap[1].Green;
							Blt->Blue   = BmpColorMap[1].Blue;
						}
						else
						{
							Blt->Red    = BmpColorMap[0].Red;
							Blt->Green  = BmpColorMap[0].Green;
							Blt->Blue   = BmpColorMap[0].Blue;
						}
						if (Width < (BmpHeader->PixelWidth))
						{
							Blt++;
							Width++;
						}
					}
					Blt--;
					Width--;
				break;

				case 4:   // Convert BMP Palette to 24-bit color
        			Index       = (*Image) >> 4;
					Blt->Red    = BmpColorMap[Index].Red;
					Blt->Green  = BmpColorMap[Index].Green;
					Blt->Blue   = BmpColorMap[Index].Blue;
					if (Width < (BmpHeader->PixelWidth - 1)) 
					{
						Blt++;
						Width++;
						Index       = (*Image) & 0x0f;
						Blt->Red    = BmpColorMap[Index].Red;
						Blt->Green  = BmpColorMap[Index].Green;
						Blt->Blue   = BmpColorMap[Index].Blue;
					}
					break;

				case 8:  // Convert BMP Palette to 24-bit color
					Blt->Red    = BmpColorMap[*Image].Red;
					Blt->Green  = BmpColorMap[*Image].Green;
					Blt->Blue   = BmpColorMap[*Image].Blue;
					break;

				case 24:
					Blt->Blue   = *Image++;
					Blt->Green  = *Image++;
					Blt->Red    = *Image;
					break;
				case 32:					//EIP93521 and EIP92901
				{
					if((BmpHeader->CompressionType)==0)
					{
						Blt->Blue   = *Image++;
						Blt->Green  = *Image++;
						Blt->Red    = *Image++;
					}
					else
					{
						return EFI_UNSUPPORTED;
					}
				}
				break;
				default:
					return EFI_UNSUPPORTED;
					break;
			};
		}
		ImageIndex = (UINTN) (Image - BmpHeader->ImageOffset);
		if ((ImageIndex % 4) != 0) // Bmp Image starts each row on a 32-bit boundary!
			Image = Image + (4 - (ImageIndex % 4));
	}
 	return EFI_SUCCESS;
}

//#endif //SETUP_BMP_LOGO_SUPPORT

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
