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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/screen.c $
//
// $Author: Arunsb $
//
// $Revision: 7 $
//
// $Date: 4/18/13 6:16a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/screen.c $
// 
// 7     4/18/13 6:16a Arunsb
// [TAG]  		EIP113081 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  		Post message displays twice
// [RootCause]  	Buffer not cleared after displaying post message
// [Solution]  	Buffer cleared properly. Save and restored the post
// graphics screen properly.
// [Files]  		protocol.c, screen.c and string.c
// 
// 6     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 5     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 7     6/22/10 5:32a Mallikarjunanv
// EIP:39102 - Updated Restore screen to restore complete screen
// 
// 6     4/07/10 6:24p Madhans
// post screen Sroll area support. TSE_POSTSCREEN_SCROLL_AREA SDL
// configures the area.
// 
// 5     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 4     2/04/10 11:22p Madhans
// To remove conout dependance
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
// 1     4/28/09 11:13p Madhans
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
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		screen.c
//
// Description:	This file contains code for screen operations.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

VOID MouseStop(VOID);
VOID MouseRefresh(VOID);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ClearScreenWithoutFlush
//
// Description:	function to clear screen without flushing.
//
// Input:		UINT8 Attrib
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearScreenWithoutFlush( UINT8 Attrib )
{

	gActiveBuffer->ScreenTag = ACTIVE_SCREEN_TAG;
	MemSet( gActiveBuffer->Attribs, sizeof(gActiveBuffer->Attribs), Attrib );

	MemFillUINT16Buffer( gActiveBuffer->Chars, MAX_DIMENSIONS, (UINT16)L' ' );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ClearLinesWithoutFlush
//
// Description:	function to clear lines without flushing.
//
// Input:		UINT8 LineStart, UINT8 NumLines, UINT8 Attrib
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearLinesWithoutFlush( UINT8 LineStart, UINT8 NumLines, UINT8 Attrib )
{

	gActiveBuffer->ScreenTag = ACTIVE_SCREEN_TAG;
	MemSet(&( gActiveBuffer->Attribs[LineStart*gMaxCols]), NumLines*gMaxCols /*sizeof(gActiveBuffer->Attribs)*/, Attrib );

	MemFillUINT16Buffer( &(gActiveBuffer->Chars[LineStart*gMaxCols]), NumLines*gMaxCols/*MAX_ROWS * MAX_COLS*/, (UINT16)L' ' );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ClearScreen
//
// Description:	function to clear the screen.
//
// Input:		UINT8 Attrib
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearScreen( UINT8 Attrib )
{
	ClearScreenWithoutFlush( Attrib );

	if(gST->ConOut!=NULL)
	{
		gST->ConOut->EnableCursor( gST->ConOut, FALSE );
		gST->ConOut->SetAttribute( gST->ConOut, Attrib );
		gST->ConOut->ClearScreen( gST->ConOut);
	}

	FlushLines( 0, gMaxRows - 1 );

}  

EFI_UGA_PIXEL *gPostscreenwithlogo;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveScreen
//
// Description:	function to get the backup of the screen.
//
// Input:		void
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *SaveScreen( VOID )
{
		SCREEN_BUFFER *Buffer;
	
		Buffer = EfiLibAllocatePool( sizeof(SCREEN_BUFFER) );
	
		if ( Buffer != NULL )
		{
			MemCopy( Buffer, gActiveBuffer, sizeof(SCREEN_BUFFER) );
			Buffer->ScreenTag = SAVE_SCREEN_TAG;
		}
	
		return (VOID *)Buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RestoreScreen
//
// Description:	function to restore the screen from the saved screen buffer.
//
// Input:		VOID *ScreenBuffer
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreScreen( VOID *ScreenBuffer )
{
	SCREEN_BUFFER *Buffer = (SCREEN_BUFFER *)ScreenBuffer;

	MouseStop();

	if ( ( Buffer == NULL ) || ( Buffer->ScreenTag != SAVE_SCREEN_TAG ) )
		return;

	///Clear Original data in the buffers before restoring with saved screen buffer.
	MemSet(gActiveBuffer, sizeof(SCREEN_BUFFER), 0);
	MemSet(gFlushBuffer, sizeof(SCREEN_BUFFER), 0);

	MemCopy( gActiveBuffer, Buffer, sizeof(SCREEN_BUFFER) );
	gActiveBuffer->ScreenTag = ACTIVE_SCREEN_TAG;

	FlushLines( 0, gMaxRows - 1 );
	DoRealFlushLines();

	MemFreePointer( (VOID **)&Buffer );

	MouseRefresh();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SaveGraphicsScreen
//
// Description:	Saves post graphics screen
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SaveGraphicsScreen(VOID)
{
	   UINTN HorizontalResolution = 0;
 	   UINTN VerticalResolution = 0;
		
		GetScreenResolution(&HorizontalResolution, &VerticalResolution);
		gPostscreenwithlogo = EfiLibAllocateZeroPool( HorizontalResolution * VerticalResolution * sizeof(EFI_UGA_PIXEL)); 

		if (NULL == gPostscreenwithlogo)
		{
			return;
		}
		 MouseStop();
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
    if ( gGOP)
	    gGOP->Blt (
	        gGOP,
	        gPostscreenwithlogo,
	        EfiBltVideoToBltBuffer,
	       (UINTN)0, (UINTN)0,
			 (UINTN)0, (UINTN)0,
	       HorizontalResolution, VerticalResolution,
	       0
	        );
#else
    if ( gUgaDraw)
	    gUgaDraw->Blt (
	        gUgaDraw,
	        gPostscreenwithlogo,
	        EfiUgaVideoToBltBuffer,
	       (UINTN)0, (UINTN)0,
			 (UINTN)0, (UINTN)0,
	       HorizontalResolution, VerticalResolution,
	       0
	        );
#endif
      MouseRefresh();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	RestoreGraphicsScreen
//
// Description:	Restores the saved post graphics screen
//
// Input:		VOID
//
// Output:		VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreGraphicsScreen (VOID)
{
   
   if( gPostscreenwithlogo != NULL )
   {
      UINTN HorizontalResolution = 0;
      UINTN VerticalResolution = 0;
      
      GetScreenResolution(&HorizontalResolution, &VerticalResolution);
      MouseStop();
#if SETUP_USE_GRAPHICS_OUTPUT_PROTOCOL
      if ( gGOP)
         gGOP->Blt (
         gGOP,
         gPostscreenwithlogo,
         EfiBltBufferToVideo,
         (UINTN)0, (UINTN)0,
         (UINTN)0, (UINTN)0,
         HorizontalResolution, VerticalResolution,
         0
      );
#else
      if ( gUgaDraw)
         gUgaDraw->Blt (
         gUgaDraw,
         gPostscreenwithlogo,
         EfiUgaBltBufferToVideo,
         (UINTN)0, (UINTN)0,
         (UINTN)0, (UINTN)0,
         HorizontalResolution, VerticalResolution,
         0
      );
#endif
      MouseRefresh();
      MemFreePointer( (VOID **)&gPostscreenwithlogo );
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
