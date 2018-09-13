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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/buffer.c $
//
// $Author: Arunsb $
//
// $Revision: 10 $
//
// $Date: 3/18/13 2:40a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/buffer.c $
// 
// 10    3/18/13 2:40a Arunsb
// [TAG]  		EIP116669
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Mouse shadow can't  refresh when switch Multi languages
// under BIOS Setup.
// [RootCause]  	Mouse not stopped when mouse pointer is at the top(0 row)
// of the screen.
// [Solution]  	Mouse stopped properly in all the position.
// [Files]  		buffer.c
// 
// 9     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 13    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     1/18/12 4:55a Rajashakerg
// [TAG]  		EIP79962 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Mouse pointer corruption in GTSE
// [RootCause]  	For GTSE, the cordanites comparison logic went wrong for 
// stopping the mouse pointer when it is present while 
// updating the screen buffer.
// [Solution]  	Corrected the logic to stop the mouse when mouse pointer
//  is present on screen we are updating.
// [Files]  		buffer.c, CommonHelper.c, Mouse.c
// 
// 7     11/30/11 11:24a Premkumara
// [TAG]  		EIP67695
// [Category]  	Improvement
// [Description]  	No cursor visible in setup, while editing text input
// box
// [Files]  		Buffer.c, Postmgmtext.c, PopupString.c, PopupPassword.c
// 
// 6     11/20/11 7:02a Rajashakerg
// [TAG]  		EIP62763
// [Category]  	Improvement
// [Description]  	Utilize the Improvements done from mouse driver in
// AMITSE
// [Files]  		HookAnchor.h, TseCommon.h, AMITSE.sdl, CommonHelper.c,
// commonoem.c, commonoem.h, buffer.c, globals.c, HookAnchor.c,
// minisetup.h, notify.c, postmgmt.c, protocol.c, ezport.c, stylecommon.c,
// Mouse.c, Action.c, Date.c, frame.c, MessageBox.c, minisetupext.c,
// minisetupext.h, numeric.c, numeric.h, page.c, PopupEdit.c, PopupEdit.h,
// PopupPassword.c, postmgmtext.c, time.c.
// 
// 5     9/27/10 7:48a Mallikarjunanv
// EIP 40555 : To avoid Compilation issues with Fareast Windows.
// 
// 4     2/19/10 1:01p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 9     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 8     1/29/10 4:37p Madhans
// To not to depend on ConsoleControl and ConOut.
// 
// 7     10/28/09 5:36p Madhans
// To undo the changes.
// 
// 6     9/29/09 5:51p Madhans
// Added more comment.
// 
// 5     9/15/09 9:27a Sudhirv
// added a flag for FlushPause
// 
// 4     8/17/09 4:31a Mallikarjunanv
// EIP:24991 - updated the DoRealFlush lines function with the changes
// suggested by Murase
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
// 2     4/29/09 9:02p Madhans
// Bug Fixes after unit Testing..
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     2/05/09 10:15a Madhans
// Style Module created.
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
// Name:		Buffer.c
//
// Description:	This file contains code to manage buffers
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
VOID GetCoordinates(INT32 *x, INT32 *y, INT32 *z);
INT32 GetactualScreentop(VOID);
BOOLEAN IsMouseSupported(VOID);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitializeScreenBuffer
//
// Description:	function to initialize the screen buffer
//
// Input:		UINT8 attrib
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitializeScreenBuffer( UINT8 attrib )
{
	EFI_STATUS Status = EFI_OUT_OF_RESOURCES;

	MemFreePointer( (VOID **)&gFlushBuffer );
	gFlushBuffer = EfiLibAllocateZeroPool( sizeof(SCREEN_BUFFER) );
	if ( gFlushBuffer == NULL )
		return Status;

	MemFreePointer( (VOID **)&gActiveBuffer );
	gActiveBuffer = EfiLibAllocatePool( sizeof(SCREEN_BUFFER) );
	if ( gActiveBuffer != NULL )
	{
		ClearScreenWithoutFlush( attrib );
		Status = EFI_SUCCESS;
	}

	return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SlowFlushLines
//
// Description:	function to slow flush lines
//
// Input:		UINTN Top, UINTN Bottom
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SlowFlushLines( UINTN Top, UINTN Bottom )
{
	UINTN	Index;
	UINTN	Offset = Top * gMaxCols;
	UINTN	End = (Bottom - Top + 1) * gMaxCols + Offset;
	UINT8	LastAttrib = 0xFF;
	CHAR16	String[2] = { 0, 0 };

	gST->ConOut->SetCursorPosition( gST->ConOut, 0, Top );
	for ( Index = Offset; Index < End; Index++ )
	{
		if ( gActiveBuffer->Attribs[Index] != LastAttrib )
		{
			LastAttrib = gActiveBuffer->Attribs[Index];
			gST->ConOut->SetAttribute( gST->ConOut, LastAttrib );
		}
		*String = gActiveBuffer->Chars[Index];

		gST->ConOut->OutputString( gST->ConOut, String );
	}
}

#define INVALID_FLUSH_LINE 0xFFFF
UINTN	FlushTop=INVALID_FLUSH_LINE;
UINTN	FlushBottom=INVALID_FLUSH_LINE;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	FlushLines
//
// Description:	function to set the positions for flush lines
//
// Input:		UINTN Top, UINTN Bottom
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FlushLines( UINTN Top, UINTN Bottom )
{
	if( FlushTop==INVALID_FLUSH_LINE) 
		FlushTop = Top;

	if(FlushBottom==INVALID_FLUSH_LINE)
		FlushBottom = Bottom;

	if(FlushTop>Top)
		FlushTop = Top;

	if(FlushBottom < Bottom)
		FlushBottom = Bottom;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DoRealFlushLines
//
// Description:	function to flush lines
//
// Input:		NIL
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DoRealFlushLines()
{
	UINTN	Index;
	UINTN	ByteStart, ByteEnd;
	UINTN	Offset = 0;
	UINTN	End = 0;
	UINT8	LastAttrib,LastSetAttrib=0;
	CHAR16	*String;
	UINTN	X=0,Y=0,TempOffSet,PrintLen;
	UINTN	CurrentX=0;
	BOOLEAN	FlushIt;
	UINTN	Top, Bottom;
	UINT32  MousePointerX=0,MousePointerY=0,MousePointerZ=0;//EIP 62763 : Mouse poiner declaration

	if( (FlushTop==INVALID_FLUSH_LINE) || (FlushBottom==INVALID_FLUSH_LINE))
		return;

	if(gST->ConOut == NULL)
		return;
	Top = FlushTop;
	Bottom = FlushBottom;

	if ( Top >= gMaxRows )
		return;

	if ( Top > Bottom )
	{
		UINTN Swap = Bottom;
		Bottom = Top;
		Top = Swap;
	}

	if ( Bottom >= gMaxRows )
		Bottom = gMaxRows - 1;

	ByteStart = Top * gMaxCols;
	ByteEnd = (Bottom - Top + 1) * gMaxCols + ByteStart;

	String = EfiLibAllocateZeroPool( (gMaxCols + 1) * sizeof(CHAR16) );

	if ( String == NULL )
	{
		SlowFlushLines( Top, Bottom );
		return;
	}

	// Flush from Top to Bottom
	// inside the loop 'Top' refers current line
	for ( ; Top <= Bottom; Top++ )
	{
		Offset = Top * gMaxCols;
		End = Offset + gMaxCols;

		// If All the Chars and attributes are equal in current line. Go to next line.
		if ( ( ! EfiCompareMem( &gActiveBuffer->Attribs[Offset], &gFlushBuffer->Attribs[Offset], gMaxCols ) ) &&
				( ! EfiCompareMem( &gActiveBuffer->Chars[Offset], &gFlushBuffer->Chars[Offset], gMaxCols * sizeof(CHAR16) ) ) )
			continue;

		// Don't Print the last char in MaxRow X MaxCol
		// As it will scroll if we print.
		if ( End >= gMaxRows * gMaxCols )
			End = gMaxRows * gMaxCols - 1;

		// Attribute for current print.
		LastAttrib = gActiveBuffer->Attribs[Offset];

		// To improve the flush lines code.
		CurrentX=0;

		// To support Terminal host with hight resolution.(EIP-25288)
		gST->ConOut->EnableCursor(gST->ConOut, FALSE);			//EIP:67695-Make the cursor invisible since the cursor position is changing and visible outside popup box
		gST->ConOut->SetCursorPosition( gST->ConOut, CurrentX, Top );

		PrintLen = 0;
		FlushIt = TRUE; // decides printing

		if(IsMouseSupported())
		GetCoordinates(&MousePointerX, &MousePointerY, &MousePointerZ);

		while ( Offset < End )
		{
			// Collect the string till the Attribute is differnt as it may need setAttribute
			for ( Index = 0, TempOffSet = Offset; (gActiveBuffer->Attribs[Offset] == LastAttrib) && (Offset < End); Offset++, Index++ )
			{
				String[Index] = gActiveBuffer->Chars[Offset];

				if(TRUE == IsCharWide(String[Index]))
					Offset++;

			}
			String[Index] = 0;
//EIP 79962 : Getting the actual Screen top from the binary for stopping the mouse
		  if(
			(IsMouseSupported() && 
         ((0 == Top) || (((MousePointerY/HiiGetGlyphHeight()) >= ((Top + ( GetactualScreentop()/ HiiGetGlyphHeight()))-1)) && ( (MousePointerY/HiiGetGlyphHeight()) <= ((Top + (GetactualScreentop()/ HiiGetGlyphHeight()))+1)))) )
         )		//EIP116669
		  {
		     MouseStop(); 
   		  }

			// We are trying to print the strings with 'LastAttrib'
			// NOW - TempOffSet refers begining of the buffer
			// 		 Offset refers end if the print buffer for currnet print.
			
			// if the String and attribute are equal to flush lines and it is more then 10 then we don't need to Print.
			// The reason for 10 is to avoid sending setposition. IF we skip less then 10 then we will end up calling setposition that takes 9 bytes
			// for serial redirection.
			if(((Offset-TempOffSet)>10)&&
				( ! EfiCompareMem( &gActiveBuffer->Attribs[TempOffSet], &gFlushBuffer->Attribs[TempOffSet], Offset-TempOffSet ) ))
			{
				// If all the charecters are same between active and flush buffer, let not print it
				if ( ( ! EfiCompareMem( &gActiveBuffer->Chars[TempOffSet], &gFlushBuffer->Chars[TempOffSet], (Offset-TempOffSet) * sizeof(CHAR16) ) ) )
					FlushIt = FALSE;
				else
				{
					UINTN i,j=0;
					UINTN FirstDiff, LastDiff;
					FirstDiff = LastDiff = (Offset-TempOffSet); // Fail case default
					
					// loop to find out that is the first and last different offset in the printable string.
					for(i=0,j=0; i<(Offset-TempOffSet);i++,j++)
					{
						if(gActiveBuffer->Chars[TempOffSet+i] != gFlushBuffer->Chars[TempOffSet+i])
						{
							if(FirstDiff>i) // First Diff set
								FirstDiff = i;
							LastDiff = i;
							Index = j;
						}
						if(TRUE == IsCharWide(String[j]))
							i++;
					}

//EIP:24991 - START
                    // Modification to erase wide characters correctly.
                    //  Issue:
                    //   If we write "a" over some wide character, the right half of the wide character is sometimes not erased.
                    //   e.g.)
                    //    When we write "aaaa    " over "aaa?   ", the right half of "?" is not erased.
                    if (!IsCharWide(String[Index]) && IsCharWide(gFlushBuffer->Chars[TempOffSet + LastDiff]) && LastDiff+1<Offset-TempOffSet){
                        LastDiff++;
                        Index++;
                    }else if (IsCharWide(String[Index]) && IsCharWide(gFlushBuffer->Chars[TempOffSet + LastDiff + 1]) && LastDiff+2<Offset-TempOffSet){
                        LastDiff += 2;
                        Index++;
                    }
//EIP:24991 - End
					if(FirstDiff>10) // Is it worth skiping?
					{
						Offset = TempOffSet+FirstDiff;
						String[Index] = 0; // No need. But lets do it anyway
						FlushIt = FALSE;
					}
					else  if(((Offset-TempOffSet)- LastDiff) > 10) // Only print the Different sting up to LastDiff
					{
//EIP:24991 - START
						// Make the offset to point to next char to be printed for next iteration
						Offset = TempOffSet+LastDiff+1;
						if(TRUE == IsCharWide(String[Index]))
							Offset++;
//EIP:24991 - END
						String[Index+1] = 0; 
					}
				}
			}

			if(FlushIt)
			{
				// Set of it is different from previous setatribute.
				if(LastSetAttrib!=LastAttrib)
				{
					gST->ConOut->SetAttribute( gST->ConOut, LastAttrib );
					LastSetAttrib = LastAttrib;
				}
				//do the set position if the cursor is not at expected loc. 
				if(((X+PrintLen) != CurrentX) || (Y != Top) || ((CurrentX == 0) && (Top==0)))
				{
					gST->ConOut->SetCursorPosition( gST->ConOut, CurrentX, Top );
				}

				X=CurrentX;
				Y=Top;

				gST->ConOut->OutputString( gST->ConOut, String );
				PrintLen = Offset-TempOffSet;

				// if we print till end of line then increament the y and make x=0.
				if((X+PrintLen)>=gMaxCols)
				{
					Y++;X=0;
				}
			}

			CurrentX += Offset-TempOffSet;
			FlushIt = TRUE;
			LastAttrib = gActiveBuffer->Attribs[Offset];
		}
	}

	MemCopy( &gFlushBuffer->Attribs[ByteStart], &gActiveBuffer->Attribs[ByteStart], ByteEnd - ByteStart );
	MemCopy( &gFlushBuffer->Chars[ByteStart], &gActiveBuffer->Chars[ByteStart], (ByteEnd - ByteStart) * sizeof(CHAR16) );
	FlushTop=INVALID_FLUSH_LINE;
	FlushBottom=INVALID_FLUSH_LINE;
	MemFreePointer( (VOID **)&String );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetDesiredTextMode
//
// Description:	function to set the test mode
//
// Input:		nil
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void SetDesiredTextMode()
{
	EFI_STATUS Status;

	if(gST->ConOut==NULL)
		return;
    Status = gST->ConOut->Reset( gST->ConOut, FALSE );
	Status = gST->ConOut->SetMode( gST->ConOut, StyleGetTextMode( gMaxRows, gMaxCols ) );

	if ( EFI_ERROR( Status ) )
	{
		gMaxRows = StyleGetStdMaxRows(); 
		gMaxCols = StyleGetStdMaxCols();
		gST->ConOut->SetMode( gST->ConOut, 0 );
	}
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
