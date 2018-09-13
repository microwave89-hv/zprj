//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2011, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/Logo.c $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/Logo.c $
// 
// 6     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 5     6/13/11 12:32p Rajashakerg
// [TAG]  		EIP60910
// [Category]  	New Feature
// [Description]  	PNG image support in TSE.
// [Files]  		LogoLib.h, AMITSE.sdl, CommonHelper.c, logo.c, png.c, png.h,
// pnguncmp.c, TseAdvanced.cif
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
// 
// 5     8/17/09 10:46a Presannar
// Use proper tycasting for the parameters of fn ConvertGifToUgaBltWrapper
// to avoid compiler warnings.
// 
// 4     8/13/09 12:16p Blaines
// Move Image support to binary module
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
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		logo.c
//
// Description:	This file contains code for advanced logo support
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

extern LOGO_TYPE GetGifLogoType(UINT8 *ImageData);
extern LOGO_TYPE GetJPEGLogoType(UINT8 *ImageData);
extern LOGO_TYPE GetPCXLogoType(UINT8 *ImageData);
extern LOGO_TYPE GetPNGLogoType(UINT8 *ImageData);
LOGO_TYPE GetOEMLogoType(UINT8 *ImageData);

extern EFI_STATUS ConvertBmpToUgaBltWrapper (IN VOID *BmpImage, IN UINTN BmpImageSize, IN OUT VOID **UgaBlt,
		IN OUT UINTN  *UgaBltSize, OUT UINTN *PixelHeight, OUT UINTN *PixelWidth );

extern EFI_STATUS ConvertGifToUgaBltWrapper ( IN VOID *GifImage, IN UINTN GifImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINTN *UgaBltSize, OUT UINTN *PixelHeight, OUT UINTN *PixelWidth, OUT BOOLEAN *Animate );

extern EFI_STATUS ConvertJPEGToUgaBltWrapper ( IN VOID *JPEGImage, IN UINT32 JPEGImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth, OUT UINT32 *punBufferWidth);

extern EFI_STATUS ConvertPCXToUgaBltWrapper ( IN VOID *PCXImage, IN UINT32 PCXImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth) ;

extern EFI_STATUS ConvertPNGToUgaBltWrapper ( IN VOID *PCXImage, IN UINT32 PCXImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth) ;

extern EFI_STATUS ConvertOEMFormatToUgaBltWrapper ( IN VOID *OEMImage, IN UINT32 OEMImageSize, IN OUT VOID **UgaBlt, 
		IN OUT UINT32 *UgaBltSize, OUT UINT32 *Height, OUT UINT32 *Width, BOOLEAN * Animate);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetExtendedLogoType
//
// Description:	function to get the type of extended logo
//
// Input:		UINT8 *ImageData
//
// Output:		LOGO_TYPE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
LOGO_TYPE GetExtendedLogoType(UINT8 *ImageData)
{
	if ( GIF_Logo == GetGifLogoType(ImageData))
		return GIF_Logo;

	if ( JPEG_Logo == GetJPEGLogoType(ImageData))
		return JPEG_Logo;

	if ( PCX_Logo == GetPCXLogoType(ImageData))
		return PCX_Logo;

	if ( PNG_Logo == GetPNGLogoType(ImageData))
		return PNG_Logo;

	if( OEM_Format_LOGO == GetOEMLogoType(ImageData))
		return OEM_Format_LOGO;

	return Unsupported_Logo;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertAdvancedImageToUgaBlt
//
// Description:	Convert a advanced graphics image to a UGA blt buffer. 
//
// Input:			IN  VOID      *ImageData,
//					IN  UINTN     ImageSize,
//					IN OUT VOID   **UgaBlt,
//					IN OUT UINTN  *UgaBltSize,
//					OUT UINTN     *Height,
//					OUT UINTN     *Width,
//					OUT BOOLEAN *Animate
//
// Output:			EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ConvertAdvancedImageToUgaBlt (
  IN  VOID      *ImageData,
  IN  UINTN     ImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *Height,
  OUT UINTN     *Width,
  OUT BOOLEAN *Animate
)
{
   	UINTN LogoType;
	EFI_STATUS Status = EFI_UNSUPPORTED;


	UINT32 Temp=0;


    LogoType = GetExtendedLogoType(ImageData);
    switch(LogoType)
    {

	case GIF_Logo:
          
		Status = ConvertGifToUgaBltWrapper(
                                ImageData,
            			(UINT32)ImageSize,
            			UgaBlt,
            			(UINTN*)UgaBltSize,
            			(UINTN*)Height,
            			(UINTN*)Width,
                                Animate
                                );

        	break;

        case JPEG_Logo:

            	Status = ConvertJPEGToUgaBltWrapper(
                                ImageData,
                                (UINT32)ImageSize,
                                UgaBlt,
                                (UINT32*)UgaBltSize,
                                (UINT32*)Height,
                                (UINT32*)&Temp,
                                (UINT32*)Width
                                );
	        break;

        case PCX_Logo:

		Status = ConvertPCXToUgaBltWrapper(
                                ImageData,
            			(UINT32)ImageSize,
            			UgaBlt,
            			(UINT32*)UgaBltSize,
            			(UINT32*)Height,
            			(UINT32*)Width
            			);
	        break;
	 case PNG_Logo:

		Status = ConvertPNGToUgaBltWrapper(
                                ImageData,
            			(UINT32)ImageSize,
            			UgaBlt,
            			(UINT32*)UgaBltSize,
            			(UINT32*)Height,
            			(UINT32*)Width
            			);
	        break;

	case OEM_Format_LOGO:
		
		Status = ConvertOEMFormatToUgaBltWrapper(
                                ImageData,
            			(UINT32)ImageSize,
            			UgaBlt,
            			(UINT32*)UgaBltSize,
            			(UINT32*)Height,
            			(UINT32*)Width,
				Animate
				);
        	break;

	default:
		break;
	}
	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoLogoAnimate
//
// Description:	function to Handle logo animation
//
// Input:		CO_ORD_ATTRIBUTE Attribute, 
//				INTN CoordinateX,INTN CoordinateY
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DoLogoAnimate(CO_ORD_ATTRIBUTE Attribute,INTN CoordinateX,INTN CoordinateY)
{
	DoLogoAnimateWrapper(Attribute,CoordinateX,CoordinateY);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
