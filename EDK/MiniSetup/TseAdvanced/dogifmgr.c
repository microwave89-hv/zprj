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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/dogifmgr.c $
//
// $Author: Arunsb $
//
// $Revision: 10 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/dogifmgr.c $
// 
// 10    10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 14    10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 9     3/29/11 6:59p Madhans
// To fix the function header
// 
// 8     3/28/11 9:38p Arunsb
// [TAG]  		EIP55548
// [Category]  	Improvement
// [Description]  	Support to display Multiple GIF and display other image
// format when Active animated Gif is displaying.
// [Files]  		dogif.c and dogifmgr.c
// 
// 7     3/21/11 1:19a Rajashakerg
// [TAG]  		EIP53740
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Animation does not continue after the last frame of the
// logo.
// [RootCause]  	Animation is continued upto the last frame of the
// animated image
// [Solution]  	Fixed the issue by handling Gif image data to redraw image
// if all the frames are completed and if boottimeout is present. 	
// [Files]  		minisetup.h, dogif.c, dogifmgr.c
// 
// 6     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 12    2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
// 
// 11    1/09/10 4:46a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 10    12/04/09 7:13a Mallikarjunanv
// Fix for EIP:30263 - Gif Logo Issue
// 
// 9     10/28/09 5:37p Madhans
// To do the clean up.
// 
// 8     9/02/09 7:39p Madhans
// To Realy fix the Logo Security issue
// 
// 7     8/13/09 12:15p Blaines
// Move Image support to binary module
// 
// 6     7/09/09 10:56a Madhans
// To fix the compilation error
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
// 3     6/30/06 4:21p Madhans
// To Integrate the PCX and Jpeg Support. SDL tokens created to support
// different image formats.
// 
// 2     6/16/06 3:40p Madhans
// 64 Bit Support. Set SDL token TSE_FOR_64BIT for 64 bit support.
// 
// 1     1/24/06 3:01a Stefanor
// quiet boot support
// implementation of buffering for POST messages
// gif support
// support for OEM badging protocol
// fixed fallback from 100x31 to 80x25
// cleanup of set graphic/text mode
// ver 1.17.1051
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		dogifmgr.c
//
// Description:	This file contains code for gif image handling
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//#if SETUP_GIF_LOGO_SUPPORT
//static EFI_EVENT	NextFrameEvent;
//static EFI_UGA_PIXEL	*UgaBltForGif = NULL;
//static UINT8		*ImageDataForGif = NULL;
//static CO_ORD_ATTRIBUTE GifAttribute;
//static UINTN            GifWidth, GifHeight, GifX, GifY, GifBufferWidth;
static UINTN 		    gGifDelay, animateDelay;
//#endif

extern unsigned long dofirst( unsigned char *, unsigned long );
extern unsigned long donext( unsigned char * );

UINT64 RShiftU64 (
  	IN UINT64   Operand,
  	IN UINTN    Count
  	);

//EIP: 55548: To display multiple gif
typedef struct                  //Structure to preserve the various gif images data
{
    UINTN           GifWidth;
    UINTN           GifHeight;
    UINTN           GifX;
    UINTN           GifY;
    UINTN           GifBufferWidth;
    EFI_EVENT       GifEvent;
    EFI_UGA_PIXEL   *UgaBltForGif;
    CO_ORD_ATTRIBUTE GifAttribute;
    unsigned char   *GifCurBufLocation;
    unsigned char 	*ImageBuffer;
    UINTN           ImageSize;
    unsigned long 	FistFrameAddress;
} GIF_ANIMATE_DATA;

struct GIF_IMAGE_DATAS          //Structure used to cleanup the logo buffers
{
	GIF_ANIMATE_DATA        *GifAnimateData;
	struct GIF_IMAGE_DATAS	*Next;
};

struct GIF_IMAGE_DATAS  *GifEntries;
GIF_ANIMATE_DATA        *GifAnimateData;
extern unsigned char    *pcurbuf;
extern unsigned long firstframeadd;     //EIP: 53740 preserving first frame address for drawing the gif image until the time out occurs
void SaveCleanUpGifDatas (GIF_ANIMATE_DATA **GifDatas);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetGifNextFrame
//
// Description:	
//
// Input:		VOID **UgaBlt , UINTN *GifDelay
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
GetGifNextFrame(IN OUT VOID **GifImageData, OUT UINTN *GifDelay)
{
	GIF_ANIMATE_DATA    **GifData;
	EFI_TPL 		  OldTpl;

	GifData = (GIF_ANIMATE_DATA    **)GifImageData;

	OldTpl = gBS->RaiseTPL(EFI_TPL_NOTIFY);
	dofirst ((*GifData)->ImageBuffer, (unsigned long)(*GifData)->ImageSize);
	while (pcurbuf != (*GifData)->GifCurBufLocation)
	{
		*GifDelay = donext ((unsigned char *)((*GifData)->UgaBltForGif));
	}
	*GifDelay = donext ((unsigned char *)((*GifData)->UgaBltForGif));
	(*GifData)->GifCurBufLocation = pcurbuf;
	gBS->RestoreTPL (OldTpl);
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NextFrame
//
// Description:	function to get the next frame.
//
// Input:		EFI_EVENT Event, VOID *Context
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NextFrame(IN EFI_EVENT Event, VOID *Context)
{
	EFI_STATUS      Status = EFI_UNSUPPORTED;
    GIF_ANIMATE_DATA      *GifContextData = (GIF_ANIMATE_DATA *)Context;

    if (NULL == GifContextData)
	{                               //Add clean up function
	   return;
    }
	if (gPostStatus > TSE_POST_STATUS_IN_BOOT_TIME_OUT)// if boot timeout is occured then we have to clean the logo and return
	{
		CleanUpLogo ();
		return;
	}
	GetGifNextFrame (&GifContextData, &gGifDelay);
	if (gGifDelay >= 0)
	{
        DrawBltBuffer (GifContextData->UgaBltForGif, GifContextData->GifAttribute, GifContextData->GifWidth, GifContextData->GifHeight, GifContextData->GifX, GifContextData->GifY, GifContextData->GifBufferWidth);
        //DrawBltBuffer(UgaBltForGif, GifAttribute, GifWidth, GifHeight, GifX, GifY, GifBufferWidth);
        Status = gBS->SetTimer (GifContextData->GifEvent, TimerRelative, gGifDelay*10000);
        if (EFI_ERROR (Status))
            TimerStopTimer (GifAnimateData->GifEvent);
	}
	else
	{
		CleanUpLogo ();
	}

	if ((0 == gGifDelay) && (gPostStatus <= TSE_POST_STATUS_IN_BOOT_TIME_OUT))// checking gGifDelay and boot timeout to assing the first frame address to the current buffer pointer
	{
		GifContextData->GifCurBufLocation = (unsigned char *)GifContextData->FistFrameAddress;
	}
	return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoGifAnimate
//
// Description:	function to Handle gif logo animation
//
// Input:		CO_ORD_ATTRIBUTE Attribute, 
//				INTN CoordinateX,INTN CoordinateY
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DoGifAnimate(CO_ORD_ATTRIBUTE Attribute,INTN CoordinateX,INTN CoordinateY)
{
    EFI_STATUS Status = EFI_UNSUPPORTED;

    if (animateDelay)
    {
        GifAnimateData->GifX = CoordinateX;
        GifAnimateData->GifY = CoordinateY;
        GifAnimateData->GifAttribute = Attribute;
        
        Status = gBS -> CreateEvent (
                            EFI_EVENT_TIMER|EFI_EVENT_NOTIFY_SIGNAL,
                            EFI_TPL_NOTIFY,
                            &NextFrame,
                            GifAnimateData,                 //NULL
                            &GifAnimateData->GifEvent);     //NextFrameEvent
        if (gEnterSetup == TRUE && !(EFI_ERROR (Status))) 
        {
            CleanUpLogo();
            return;
        }
        Status = gBS->SetTimer (GifAnimateData->GifEvent, TimerRelative, animateDelay*10000);
        if (EFI_ERROR (Status)) {
            TimerStopTimer (GifAnimateData->GifEvent);
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertGifToUgaBlt
//
// Description:	Convert a *.GIF graphics image to a UGA blt buffer. If a 
//					NULL UgaBlt buffer is passed in a UgaBlt buffer will be 
//					allocated by this routine. If a UgaBlt buffer is passed in 
//					it will be used if it is big enough.
//
// Input:	GifImage      - Pointer to GIF file
//					GifImageSize  - Number of bytes in BmpImage
//					UgaBlt        - Buffer containing UGA version of GifImage.
//					UgaBltSize    - Size of UgaBlt in bytes.
//					PixelHeight   - Height of UgaBlt/BmpImage in pixels
//					PixelWidth    - Width of UgaBlt/BmpImage in pixels
//					GifDelay      -
//
// Output:	EFI_SUCCESS - UgaBlt and UgaBltSize are returned. 
//					EFI_UNSUPPORTED       - GifImage is not a valid *.GIF image
//					EFI_BUFFER_TOO_SMALL  - The passed in UgaBlt buffer is not big enough.
//                          UgaBltSize will contain the required size.
//					EFI_OUT_OF_RESOURCES  - No enough buffer to allocate
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
ConvertGifToUgaBlt (
  IN  VOID      *GifImage,
  IN  UINTN     GifImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *PixelHeight,
  OUT UINTN     *PixelWidth,
  OUT UINTN     *GifDelay
  )
{
	UINT64      BltBufferSize;
	UINTN       Height;
	UINTN       Width;
    EFI_TPL     OldTpl;
    unsigned char   *TempCurBuf = NULL;
    unsigned long 	tempfirstframeadd;

//	unsigned long 	tempstartunreadbuf;

    OldTpl = gBS->RaiseTPL (EFI_TPL_NOTIFY);            // prepare BLT buffer for the GIF image
	BltBufferSize = dofirst (GifImage, (unsigned long)GifImageSize);
	gBS->RestoreTPL (OldTpl);

	Width = (UINTN)RShiftU64(BltBufferSize,16);
	Height = (UINTN)(BltBufferSize & 0xffff);

	// Make sure to do x64 Mul
	BltBufferSize = MultU64x32((UINT64)Width , Height);
  
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
		*UgaBlt = EfiLibAllocatePool (*UgaBltSize);
    		if (*UgaBlt == NULL) return EFI_OUT_OF_RESOURCES;
    } 
	else 
	{
		if (*UgaBltSize < (UINTN)BltBufferSize) 
		{
			*UgaBltSize = (UINTN)BltBufferSize;
				return EFI_BUFFER_TOO_SMALL;
		}    
	}

 	//corrected the assignment.	
 	*PixelWidth   = Width;
	*PixelHeight  = Height;
    OldTpl = gBS->RaiseTPL(EFI_TPL_NOTIFY);
    BltBufferSize = dofirst (GifImage, (unsigned long)GifImageSize);
    tempfirstframeadd = firstframeadd;                                  //Using temp variable because call to allocatepool 
    gGifDelay = *GifDelay = donext ((unsigned char *)(*UgaBlt));        //may lead to trigger the previous gif events so pcurbuf value might change
    TempCurBuf = pcurbuf;
    gBS->RestoreTPL (OldTpl);
    if (*GifDelay)
	{
        GifAnimateData = (GIF_ANIMATE_DATA *)EfiLibAllocateZeroPool (sizeof (GIF_ANIMATE_DATA));
	    if (NULL == GifAnimateData)
	    {
		    return EFI_OUT_OF_RESOURCES;
	    }
        GifAnimateData->ImageBuffer = GifImage;
        GifAnimateData->ImageSize = GifImageSize;
        GifAnimateData->FistFrameAddress = tempfirstframeadd;
        GifAnimateData->GifWidth = Width;
        GifAnimateData->GifHeight = Height;
        GifAnimateData->GifBufferWidth = Width;
        GifAnimateData->UgaBltForGif = *UgaBlt;
        GifAnimateData->GifCurBufLocation = TempCurBuf;
	    GetGifNextFrame ((void **)&GifAnimateData, &gGifDelay);
        animateDelay = gGifDelay;
        SaveCleanUpGifDatas (&GifAnimateData);
	}
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CleanUpGif
//
// Description:	Cleans the gif datas
//
// Input:	void
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CleanUpGif (VOID)
{
    while (NULL != GifEntries)
    {
        gBS->CloseEvent (GifEntries->GifAnimateData->GifEvent);
    	MemFreePointer( (VOID **)&GifEntries->GifAnimateData->UgaBltForGif);
    	MemFreePointer( (VOID **)&GifEntries->GifAnimateData->ImageBuffer);   
        GifEntries = GifEntries->Next;    
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveCleanUpGifDatas
//
// Description:	Saves the structures used for preserving the gif images
//					
//
// Input:	GifDatas - Pointer to a pointer for GIF image structure
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void SaveCleanUpGifDatas (GIF_ANIMATE_DATA **GifDatas)
{
    struct GIF_IMAGE_DATAS *HoldGifData = NULL, *tempGifEntries = NULL;
    
    HoldGifData = (struct GIF_IMAGE_DATAS *)EfiLibAllocateZeroPool (sizeof (struct GIF_IMAGE_DATAS));
    if (NULL == HoldGifData)
    {
        return;
    }
    HoldGifData->GifAnimateData = *GifDatas;
    HoldGifData->Next = NULL;
    tempGifEntries = GifEntries;
    if (NULL == tempGifEntries)
    {
        GifEntries = HoldGifData; 
    }
    else
    {
        while (NULL != tempGifEntries->Next)
        {
            tempGifEntries = tempGifEntries->Next;
        }
        tempGifEntries->Next = HoldGifData;
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
