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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/box.c $
//
// $Author: Arunsb $
//
// $Revision: 5 $
//
// $Date: 10/18/12 5:58a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/box.c $
// 
// 5     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     2/19/10 1:01p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 4     12/10/09 2:59p Presannar
// Modified DrawBorder fn to  check if Width or Height is zero. This is a
// solution to address EiP - 32242
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

#include "minisetup.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawLineWithAttribute
//
// Description:	function to draw the lines with attributes
//
// Input:		UINTN Col, UINTN Row, UINTN Length, CHAR16 Type, UINT8 Attrib
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawLineWithAttribute( UINTN Col, UINTN Row, UINTN Length, CHAR16 Type, UINT8 Attrib )
{
	UINTN	Index;
	CHAR16	*Line;

	Line = EfiLibAllocatePool( sizeof(CHAR16) * (Length + 1) );
	if ( Line == NULL )
		return;

	for ( Index = 0; Index < Length; Index++ )
		Line[Index] = Type;

	Line[Index] = 0;

	DrawStringWithAttribute( Col, Row, Line, Attrib );

	MemFreePointer( (VOID **)&Line );
}

VOID DrawLine( UINTN Col, UINTN Row, UINTN Length, CHAR16 Type )
{
	DrawLineWithAttribute( Col, Row, Length, Type, 0 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawBorder
//
// Description:	function to draw the border
//
// Input:		UINTN Left, UINTN Top, UINTN Width, UINTN Height
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawBorder( UINTN Left, UINTN Top, UINTN Width, UINTN Height )
{
	UINTN	Index;
	CHAR16	*Line;
	UINTN	Right, Bottom;

	if( Width == 0 || Height == 0 )
		return;

	Line = EfiLibAllocateZeroPool( (Width + 6) * sizeof(CHAR16) );
	if ( Line == NULL )
		return;

	Right = Left + Width - 1;
	Bottom = Top + Height - 1;

	for ( Index = 1; Index < Width - 1; Index++ )
		Line[Index] = BOXDRAW_HORIZONTAL;

	Line[0] = BOXDRAW_DOWN_RIGHT;
	Line[Index] = BOXDRAW_DOWN_LEFT;
	DrawString( Left, Top, Line );
	Line[0] = BOXDRAW_UP_RIGHT;
	Line[Index] = BOXDRAW_UP_LEFT;
	DrawString( Left, Bottom, Line );

	Line[0] = BOXDRAW_VERTICAL;
	Line[1] = 0;

	for ( Index = Top + 1; Index < Bottom; Index++ )
	{
		DrawString( Left, Index, Line );
		DrawString( Right, Index, Line );
	}

	MemFreePointer( (VOID **)&Line );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawWindow
//
// Description:	function to draw a window
//
// Input:		UINTN Left, UINTN Top, UINTN Width, UINTN Height,
//				UINT8 Attrib, BOOLEAN Border, BOOLEAN Shadow
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawWindow( UINTN Left, UINTN Top, UINTN Width, UINTN Height, UINT8 Attrib, BOOLEAN Border, BOOLEAN Shadow )
{
	if ( Shadow )
		DrawBox( Left + 2, Top + 1, Width, Height, 0 );

	DrawBox( Left, Top, Width, Height, Attrib );

	if ( Border )
		DrawBorder( Left, Top, Width, Height );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawBox
//
// Description:	function to draw a box
//
// Input:		UINTN Left, UINTN Top, UINTN Width, UINTN Height, UINT8 Attrib
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawBox( UINTN Left, UINTN Top, UINTN Width, UINTN Height, UINT8 Attrib )
{
	UINTN	Bottom, Right;
	UINTN	Index;
	UINTN	Offset;
	CHAR16	WindowLine[MAX_COLS];
	UINT8	AttribLine[MAX_COLS];

	Bottom = Top + Height;
	if ( Bottom >= gMaxRows )
	{
		Bottom = gMaxRows - 1;
		Height = Bottom - Top;
	}

	Right = Left + Width;
	if ( Right >= gMaxCols )
	{
		Right = gMaxCols - 1;
		Width = Right - Left;
	}

	MemSet( AttribLine, Width, Attrib );
	for ( Index = 0; Index < Width; Index++ )
		WindowLine[Index] = L' ';

	Offset = Top * gMaxCols + Left;
	for ( Index = Top; Index < Bottom; Index++, Offset += gMaxCols )
	{
		// to resolve the wide char corruption when box is drawn
		if((Left) && ( IsCharWide( gFlushBuffer->Chars[Offset-1]) == TRUE ))
				gActiveBuffer->Chars[Offset-1]=L' ';

		MemCopy( &gActiveBuffer->Chars[Offset], WindowLine, sizeof(CHAR16) * Width );
		MemCopy( &gActiveBuffer->Attribs[Offset], AttribLine, Width );
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
