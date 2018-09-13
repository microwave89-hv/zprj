//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/string.c $
//
// $Author: Arunsb $
//
// $Revision: 20 $
//
// $Date: 2/11/14 10:10p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/string.c $
// 
// 20    2/11/14 10:10p Arunsb
// [TAG]	EIP149640
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	F1 not displaying help message
// [Root Cause]	If we have \n in string then it replaced with 0x0d(\r) and
// 0xa(\n) so both \r and \n treated as new line so incremented in height
// not displayed the message box.
// ie., height is beyond the max rows
// [Solution]	If we have \n in string we will get 0x0d(\r) and 0xa(\n)
// continuously so removed \r for \n.
// For \r alone case it will replaced with \0
// [Files]	string.c
// 
// 19    2/11/14 8:13p Arunsb
// [TAG]			EIP126746
// [Category]		Improvement
// [Description]	AMITSE - ANSI escape code support for multiline
// [Files]			string.c and commonhelper.c
// 
// 18    12/03/13 1:55p Premkumara
// [TAG]  		EIP130420
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	String is getting truncated
// [RootCause]  	The string for messagebox, Popup controls is getting
// truncated
// [Solution]  	Used temp variable to store original string and modify the
// string temp and used to avoid changing org string.
// [Files]  		String.c
// 
// 17    11/08/13 7:55a Premkumara
// [TAG]  		EIP131481
// [Category]  	Improvement
// [Description]  	TSE support '\r' to do line break
// [Files]  		String.c
// 
// 16    4/18/13 6:17a Arunsb
// [TAG]  		EIP113081 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  		Post message displays twice
// [RootCause]  	Buffer not cleared after displaying post message
// [Solution]  	Buffer cleared properly. Save and restored the post
// graphics screen properly.
// [Files]  		protocol.c, screen.c and string.c
// 
// 15    10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 16    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 14    4/27/12 3:57a Rajashakerg
// [TAG]  		EIP87424
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Mouse pointer is destroyed by TSE when it is on SETUP icon
// during POST
// [RootCause]  	When SOFTKBD_ICON_SUPPORT is enabled the mouse pointer is
// restricted to the ICON location. In the same line we are updating the
// Post Message in which DoRealFlushLines() will stop the mouse while
// updating the string in Post, but immediate Mouse refresh is not present
// in PrintPostMessage() which is causing mouse pointer disappear.
// 
// [Solution]  	Provided mouserefresh after DoRealFlushLines() in
// PrintPostMessage() function.
// [Files]  		BootOnly/string.c
// 
// 13    2/02/12 1:13p Premkumara
// [TAG]  		EIP75351,75352,75384
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		String.c, boot.c, TseAdvanced.c,Time.c, PopupEdit.c,
// MessageBox.c, Label.c, Edit.c, Date.c
// 
// 12    11/30/11 12:17a Premkumara
// [TAG]  		EIP75351
// [Category]  	Improvement
// [Description]  	Static code analysis.Suppress the warnings from static
// code analyzer
// [Files]  		String.c, HiiString21.c, TseAdvanced.c, Special.c,
// UefiAction., Time.c, PopupEdit.c, MessageBox.c, Label.c, Edit.c, Date.c
// 
// 11    10/21/11 2:57a Rajashakerg
// [TAG]  		EIP60563 
// [Category]  	New Feature
// [Description]  	Updating the file with fix for issue : maximum 8 byte
// value shows negative number
// [Files]  		numeric.c, numeric.h, string.c, string.h
// 
// 10    6/20/11 12:25p Rajashakerg
// [TAG]  		EIP60563 
// [Category]  	New Feature
// [Description]  	Support for signed decimal value for
// EFI_IFR_NUMERIC_OP.  
// [Files]  		numeric.c, numeric.h, string.c, string.h, Uefi21Wapper.c
// 
// 9     12/22/10 5:03a Mallikarjunanv
// [TAG]  		EIP41838
// [Category]  	Improvement
// [Description]  	Updated the fix for 41838. Previously for \r is not
// returning the cursor position to the starting column and \n it is not
// moved to the first column of the next line. Now \r and \n functionality
// updated to work properly. 
// [Files]  		string.c
// 
// 8     11/16/10 8:55a Mallikarjunanv
// [TAG] - EIP 41838  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Update AMI Post Manager Protocol witht he following. 2.
// Updating the interface PostManagerDisplayPostMessageEx to handle the
// cursor position properly. 2. Need to add new interface to GetAttribute
// [Rootcause] - 1. Display string is over written by the next string if
// the interface PostManagerDisplayPostMessageEx used simultaneously. 2.
// Need to get the attribute info to use PostManagerDisplayPostMessage
// interfaces effectively
// [Solution]- Fix in string.c to handle cursor and line positions. The
// files Protocol.c, Protocol.h and AmiPostMgr.h have the new interface
// implementaion to get the attribute.
// [Files] - Protocol.c, Protocol.h, AmiPostMgr.h and string.c
// 
// 7     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 6     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 5     2/19/10 8:50p Madhans
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 8     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 7     2/04/10 12:03p Blaines
// EIP-28005
// 
// Added PostManagerSetAttribute to support display of text in color.
// Added support for handling string characters --- \n, \r.
// 
// 6     1/09/10 5:43a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 5     10/05/09 10:36a Madhans
// To allow printing without affecting the previous screen when it is used
// with SetCursorPosition.
// 
// 4     9/25/09 6:37a Sudhirv
// EIP-26893 : when the DisplayPostMessage() function of the AMI Post
// Manager protocol is called multiple times, strings are truncated when
// displayed.
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
// 5     4/28/09 9:49p Madhans
// 
// 4     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:01p Madhans
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
// Name:		string.c
//
// Description:	This file contains code for string functionalities.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

static UINTN StartRow = 0;
static UINTN StartCol = 0;
static UINTN EndRow = STYLE_FULL_MAX_ROWS;
static UINTN EndCol = STYLE_FULL_MAX_COLS;

static UINTN stStartLine= 0 ;
static UINTN stNextLine = 0;
static UINTN stColNum = 0;

static BOOLEAN	stPostScreenActive = FALSE;
VOID ScrollPostScreenLine();


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	SetPostScreenScrollArea
//
// Description:	Sets the PostScreen Scroll Area.
//
// Input:	UINTN TopX, UINTN TopY, UINTN BottomX, UINTN BottomY
//
// Output:	None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetPostScreenScrollArea(UINTN TopRow, UINTN TopCol, UINTN BottomRow, UINTN BottomCol)
{
	if((TopCol<BottomCol) && (BottomCol<=STYLE_FULL_MAX_COLS) && (TopRow<BottomRow) && (BottomRow<=STYLE_FULL_MAX_ROWS) )
	{
		stNextLine = stStartLine = StartRow = TopRow;
		stColNum = StartCol = TopCol;
		EndRow = BottomRow;
		EndCol = BottomCol;
	}
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	atoi
//
// Description:	function to convet a string to integer
//
// Input:	CHAR16 *string, UINT8 base
//
// Output:	integer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN atoi(CHAR16 *string, UINT8 base)
{
	UINTN dval = 0;//EIP:60563 to support signed integers for NUMERIC opcode
	CHAR16 ch;

	if ( base == 10 )
	{
		while ( (ch = *string++ ) != 0x0)
		{
			if ( ch >= L'0' && ch <= L'9' )
				dval = dval * 10 + ch - L'0';
			else
				break;

		}
	}
	else if ( base == 16 )
	{
		while ( (ch = *string++) != 0x0 )
		{
			if ( ch >= L'0' && ch <= L'9' )
				dval = dval * 16 + ch - L'0';
			else if ( ch >= L'a' && ch <= L'f' )
				dval = dval * 16 + ch - L'a' + 10;
			else if ( ch >= L'A' && ch <= L'F' )
				dval = dval * 16 + ch - L'A' + 10;
			else
				break;
		}
	}//EIP:60563 to support signed integers for NUMERIC opcode
	else if( base == 32)
	{
		if(string[0]== L'-')
		{
			string++;
			while ( (ch = *string++ ) != 0x0)
			{
				if ( ch >= L'0' && ch <= L'9' )
				dval = dval * 10 + ch - L'0';
			else
				break;
			}
			dval= (INTN)((0xffffffffffffffff - dval )+ 0x1);
		}
		else
		{
			while ( (ch = *string++ ) != 0x0)
			{
				if ( ch >= L'0' && ch <= L'9' )
				dval = dval * 10 + ch - L'0';
			else
				break;
			}
		}
	}
	return dval;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StrZeroPad
//
// Description:	function to pad with zero
//
// Input:	INT32 Tm, CHAR16 *Str
//
// Output:	String
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *StrZeroPad(INT32 Tm, CHAR16 *Str)
{
	CHAR16 *fmt = L"%d";

	if ( Tm < 10 )
		fmt = L"0%d";

	SPrint( Str, 10, fmt, Tm );
	return Str;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StrDup
//
// Description:	function to dump and return the string
//
// Input:	CHAR16 *String
//
// Output:	String
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *StrDup( CHAR16 *string )
{
	CHAR16 *text;

	if(string == NULL)
		return NULL;
	
	text = EfiLibAllocatePool( (1 + EfiStrLen( string )) * sizeof(CHAR16) );
	if ( text != NULL )
		EfiStrCpy( text, string );

	return text;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawAttribute
//
// Description:	function to write a attribute
//
// Input:	UINTN Col, UINTN Row, UINT8 Attrib, UINTN Length
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawAttribute( UINTN Col, UINTN Row, UINT8 Attrib, UINTN Length )
{
	UINTN Offset = Row * gMaxCols + Col;

	if ( Row >= gMaxRows )
		return;

	DrawAttributeOffset( Offset, Attrib, Length );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawAttributeOffset
//
// Description:	function to write in a peticular offset.
//
// Input:	UINTN Offset, UINT8 Attrib, UINTN Length
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawAttributeOffset( UINTN Offset, UINT8 Attrib, UINTN Length )
{
	if ( Attrib )
		MemSet( &gActiveBuffer->Attribs[Offset], Length, Attrib );
}
UINT8 ForegroundColors[] = {
    30,         //Black
    34,         //Blue
    32,         //Green
    36,         //Cyan
    31,         //Red
    35,         //Magenta
    33,         //Brown (code is for Yellow)
    37,         //Light Gray (code is for White)
};

UINT8 BackgroundColors[] = {
    40, //Black
    44, //Blue
    42, //Green
    46, //Cyan
    41, //Red
    45, //Magenta
    43, //Brown (code is for Yellow)
    47  //Light Gray (code is for White)
};

UINT8 GetEFIFG(UINT8 ANSIColor)
{
	UINT8 i=0;
	for(i=0;i<sizeof(ForegroundColors);i++)
		if(ForegroundColors[i]==ANSIColor)
			return i;
	return 0;
}

UINT8 GetEFIBG(UINT8 ANSIColor)
{
	UINT8 i=0;
	for(i=0;i<sizeof(BackgroundColors);i++)
		if(BackgroundColors[i]==ANSIColor)
			return i;
	return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawMultiLineStringWithAttribute
//
// Description:	function to write a multiline string.
//
// Input:	UINTN Col, UINTN Row,UINTN Width, UINTN Height,
//					CHAR16 *line, UINT8 Attrib
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawMultiLineStringWithAttribute( UINTN Col, UINTN Row,UINTN Width, UINTN Height, CHAR16 *line, UINT8 Attrib )
{
	CHAR16 * text;
	UINTN i;
	CHAR16 * String,*newtext;
	UINT16 height;

	newtext = StringWrapText( line, (UINT16)Width, &height ); 
	//EIP-75351 Suppress the warnings from static code analyzer
	if(NULL == newtext){
		return;		
	}
	if(height < Height)
		Height = height;
	String = newtext;
	for(i=0;i<Height;i++)
	{
		CHAR16 save;

		text = String;
		if ( *String == L'\0' )
			break;

		while ( ( *String != L'\n' ) &&( *String != L'\r' ) && ( *String != L'\0' ) )
			String++;

		save = *String;
		*String = L'\0';
		DrawStringWithAttribute( Col , Row+i, (CHAR16*)text, Attrib);

		if ( ( *String = save ) != L'\0' )
		{
			String++;
			if ( ( *String == L'\r' ) || ( *String == L'\n' ) )
				String++;
		}
	}
	MemFreePointer( (VOID **)&newtext );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawPostStringWithAttribute
//
// Description:	function to write a multiline string in the post screen.
//
// Input:	UINTN Col, UINTN Row,
//					CHAR16 *line, UINT8 Attrib
//
// Output:	UINTN
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN DrawPostStringWithAttribute( UINTN Col, UINTN Row,CHAR16 *line, UINT8 Attrib, BOOLEAN AdvanceLine )
{
	CHAR16 * text;
	UINTN i=0;
	CHAR16 * String=line;
	UINTN Offset;
	UINTN mxCol=gMaxCols;
	while(1)
	{
		CHAR16 save;

		text = String;
		if ( *String == L'\0' )
			break;

		while ( ( *String != L'\n' ) &&( *String != L'\r' ) && ( *String != L'\0' ) )
			String++;

		save = *String;
		*String = L'\0';

		if(AdvanceLine)
		{
			mxCol = EndCol;
		}

		Offset = HiiFindStrPrintBoundary(text,(mxCol - Col));

		if((AdvanceLine) && (Row+i >= gMaxRows))
		{
			ScrollPostScreenLine();
			Row = gMaxRows-1-i;
		}

		if(Offset < EfiStrLen(text))
		{// Printing the string printed next line also
			*String = save;
			save = text[Offset];
			text[Offset] = 0;
			DrawStringWithAttribute( Col , Row+i, (CHAR16*)text, Attrib);
			String = &text[Offset];
		}
		else
			DrawStringWithAttribute( Col , Row+i, (CHAR16*)text, Attrib);

		stColNum = EfiStrLen(text);//EIP-41838: Updating the col position based on present string length.
		if ( ( *String = save ) != L'\0' )
		{
			stColNum = 0; Col=0;//EIP-41838: Updating the col position to zero in case of \n and \r.
			if ( *String == L'\r' )
			{	String++;
				i--;
			}
			if ( *String == L'\n' )
			{
				String++;

				if ( *(String - sizeof(CHAR16)) == L'\r' )
					i++;
			}
		}
		else
			break;
		i++;
		//EIP-41838: Update the col position based on string processed to display.
		if ( (!AdvanceLine) && ( (Col+Offset) >= mxCol) ) {
			Col =0;
		}
	}
	return i;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawStringWithAttribute
//
// Description:	function to write a string with attributes.
//
// Input:	UINTN Col, UINTN Row, CHAR16 *String, UINT8 Attrib
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawStringWithAttribute( UINTN Col, UINTN Row, CHAR16 *String, UINT8 Attrib )
{
	UINTN Length,printLength;
	UINTN Offset = Row * gMaxCols + Col;
	UINTN nIndex = 0;
	UINTN Size;
	UINT8 EscBold,EscFg,EscBg,EscAttrib=Attrib;

	if ( Row >= gMaxRows )
		return;

	Length = EfiStrLen( String );
	printLength = TestPrintLength( String ) / (NG_SIZE);
	if ( Length == 0 )
		return;

	if ( printLength == 0 )
		return;
	DrawAttributeOffset( Offset, Attrib, printLength );
	EscAttrib = Attrib;

	for(nIndex = 0;nIndex < Length;nIndex++)
	{
		if((String[nIndex] == 0xfff0) ||  (String[nIndex] == 0xfff1))
		{
			continue;
		}
		Size=TseGetANSIEscapeCode(&String[nIndex],&EscBold,&EscFg,&EscBg);
		if(Size)
		{
			EscAttrib = Attrib;
			if(EscBg!=0xFF)
				EscAttrib = (EscAttrib & 0x0F) | (GetEFIBG(EscBg)<<4);
			if(EscFg!=0xFF)
				EscAttrib = (EscAttrib & 0xF0) | GetEFIFG(EscFg);
			if(EscBold!=0xFF)
				EscAttrib = (EscAttrib & 0xF7) | (EscBold<<3);
	
			nIndex +=Size;
			continue;
		}
		gActiveBuffer->Chars[Offset] = String[nIndex];
		if(EscAttrib)
			gActiveBuffer->Attribs[Offset] = EscAttrib;
		if(TRUE == IsCharWide(String[nIndex]))
		{
			Offset+=2;
		}
		else
		{
			Offset++;
		}
	}
}

VOID DrawString( UINTN Col, UINTN Row, CHAR16 *String )
{
	DrawStringWithAttribute( Col, Row, String, 0 );
}

VOID DrawStringJustified( UINTN MinCol, UINTN MaxCol, UINTN Row, UINTN Justify, CHAR16 *String )
{
	DrawStringJustifiedWithAttribute( MinCol, MaxCol, Row, Justify, String, 0 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DrawStringJustifiedWithAttribute
//
// Description:	function to write a string with justify and attributes.
//
// Input:	UINTN MinCol, UINTN MaxCol, UINTN Row, UINTN Justify,
//					CHAR16 *String, UINT8 Attrib
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawStringJustifiedWithAttribute( UINTN MinCol, UINTN MaxCol, UINTN Row, UINTN Justify, CHAR16 *String, UINT8 Attrib )
{
	UINTN Col = MinCol;
	CHAR16	*text;
	UINTN		Length = 0;
	
	text = StrDup(String); //EIP-130420
	
	Length = TestPrintLength( text ) / (NG_SIZE);
	if ( Length == 0 )
		return;

	if ( Justify == JUSTIFY_RIGHT )
	{
		if(Length < MaxCol)
			Col = MaxCol - Length;
	}
	else if ( Justify == JUSTIFY_CENTER )
	{
		if(Length < (MaxCol - MinCol))
			Col = MinCol + (((MaxCol - MinCol) - Length) / 2);
		else
			text[MaxCol - MinCol] = '\0';
	}

	if ( Col < MinCol )
		Col = MinCol;

	DrawStringWithAttribute( Col, Row, text, Attrib );
	MemFreePointer( (VOID **)&text );
}

VOID WriteChar( UINTN Row, UINTN Col, CHAR16 Char )
{
	WriteCharWithAttribute( Row, Col, Char, 0 );
}

VOID WriteCharWithAttribute( UINTN Row, UINTN Col, CHAR16 Char, UINT8 Attrib )
{
	UINTN Offset = Row * gMaxCols + Col;

	if ( Row >= gMaxRows )
		return;

	DrawAttributeOffset( Offset, Attrib, 1 );

	gActiveBuffer->Chars[Offset] = Char;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StringWrapText
//
// Description:	function to create a new text by wrapping the given text.
//
// Input:	CHAR16 *OrgText, UINT16 width, UINT16 *height
//
// Output:	text
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void 	FindAnsiEscCode (CHAR16 *ThisLine, CHAR16 **EscCode);
BOOLEAN IsANSIEscapeCodeSupported (VOID);
CHAR16 * StringWrapText( CHAR16 *OrgText, UINT16 width, UINT16 *height )
{
    CHAR16 		*newText, *text;
    UINTN 		TextLen, i, j, newTextLen;
    CHAR16		*ESCCode = (CHAR16 *)NULL;

	if(OrgText == NULL)
		return NULL;

    if (IsANSIEscapeCodeSupported ())
    {
    	ESCCode = EfiLibAllocateZeroPool (12 * sizeof(CHAR16));
    	if (NULL == ESCCode)
    	{
    		return NULL;
    	}
    }
    text = StrDup(OrgText);
    TextLen = EfiStrLen(text);
    //reformat input string by replacing \n and \r with \0
    i=0;
    while(text[i])
    {
        switch(text[i])
        {
        case L'\r':
            //IF we have \n in string we will get 0x0d(\r) and 0xa(\n) continuously so removing \r for \n alone
            j=i;
				if (text[i+1] == L'\n')
				{
	            while(text[j])
	            {
	                text[j]= text[j+1];
	                j++;
	            }
					//Adjust text length
					TextLen--;
					break;
				}
        case L'\n':
            text[i] = L'\0';
            //No break on purpose
        default:
            i++;
        }
    }
    
    //Assuming max no of '\n's that may be added is no of rows
    if (!IsANSIEscapeCodeSupported ())
    {
    	newText = EfiLibAllocateZeroPool( (TextLen + 1 + gMaxRows) * sizeof(CHAR16));
    }
    else
    {
    	newText = EfiLibAllocateZeroPool( (TextLen + 1 + (gMaxRows * 12)) * sizeof(CHAR16));			//If ANSI supported then chances are there to fill
    }																								//ANSI code in all rows so 12 * gMaxRows bytes allocated
    if (NULL == newText)
    {
    	return NULL;
    }
    	
    *height=0;
    newTextLen = 0;
    for(i=0; i<TextLen; (*height)++)
    {
        CHAR16 *ThisLine;

        ThisLine = text+i;
        
        if( width >= (TestPrintLength(ThisLine)/(NG_SIZE)) ) //Can accomodate this line
        {
            if ((IsANSIEscapeCodeSupported ()) && (*ESCCode))
            {
        		if ( (ThisLine [0] == 0x001b) && (ThisLine [1] == L'[') )
        		{
					EfiStrCpy (newText + newTextLen, ThisLine);
        		}
        		else
        		{
        			EfiStrCpy (newText + newTextLen, ESCCode);
        			EfiStrCat (newText + newTextLen, ThisLine);        			
        		}
        		if ( (ThisLine [0] != 0x001b) || (ThisLine [1] != L'[') )
        		{
        			newTextLen += EfiStrLen (ESCCode);
        		}
        		newTextLen += EfiStrLen (ThisLine);
                newText[newTextLen] = L'\n';
                newTextLen++;
            }
            else
            {
                //Found space break the str here
                EfiStrCpy(newText + newTextLen, ThisLine);
                newTextLen+=EfiStrLen(ThisLine);
                newText[newTextLen] = L'\n';
                newTextLen++;
            }
            if (IsANSIEscapeCodeSupported ())
            {
            	FindAnsiEscCode (ThisLine, &ESCCode);
            }
            i+=EfiStrLen(ThisLine);
            i++;
        }
        else //Can not accomodate this line
        {
            //See if we can find a L" "
            j = HiiFindStrPrintBoundary ( ThisLine, width )-1;
            while(j)
            {
                if(ThisLine[j] == L' ')
                {
                    //Found space break the str here
                    ThisLine[j]=L'\0';
                    if ((IsANSIEscapeCodeSupported ()) && (*ESCCode))
                    {
                		if ( (ThisLine [0] == 0x001b) && (ThisLine [1] == L'[') )
                		{
							EfiStrCpy (newText + newTextLen, ThisLine);
                		}
                		else
                		{
                			EfiStrCpy (newText + newTextLen, ESCCode);
                			EfiStrCat (newText + newTextLen, ThisLine);                			
                		}
                		if ( (ThisLine [0] != 0x001b) || (ThisLine [1] != L'[') )
                		{
                			newTextLen += EfiStrLen (ESCCode);
                		}
                		newTextLen += EfiStrLen (ThisLine);
                        newText[newTextLen] = L'\n';
                        newTextLen++;
                    }
                    else
                    {
                        EfiStrCpy(newText + newTextLen, ThisLine);
                        newTextLen+=EfiStrLen(ThisLine);
                        newText[newTextLen] = L'\n';
                        newTextLen++;
                    }
                    if (IsANSIEscapeCodeSupported ())
                    {
                    	FindAnsiEscCode (ThisLine, &ESCCode);
                    }
                    i+=EfiStrLen(ThisLine);
                    i++;
                    break;
                }
                j--;
            }

            if(0==j)
            {
                CHAR16 temp;

                //did not find L' '
                j = HiiFindStrPrintBoundary ( ThisLine, width ) - 1;
                temp = ThisLine[j];
                ThisLine[j] = '\0';
                if ((IsANSIEscapeCodeSupported ()) && (*ESCCode))
                {
            		if ( (ThisLine [0] == 0x001b) && (ThisLine [1] == L'[') )
            		{
            			EfiStrCpy (newText + newTextLen, ThisLine);
            		}
            		else
            		{
            			EfiStrCpy (newText + newTextLen, ESCCode);
            			EfiStrCat (newText + newTextLen, ThisLine);
            		}
            		if ( (ThisLine [0] != 0x001b) || (ThisLine [1] != L'[') )
            		{
            			newTextLen += EfiStrLen (ESCCode);
            		}
            		newTextLen += EfiStrLen (ThisLine);
					newText[newTextLen] = temp;
					newTextLen++;
					newText[newTextLen] = L'\n';
                    newTextLen++;
                }
                else
                {
					EfiStrCpy(newText + newTextLen, ThisLine);
					newTextLen+=EfiStrLen(ThisLine);
					newText[newTextLen] = temp;
					newTextLen++;
					newText[newTextLen] = L'\n';
					newTextLen++;
                }
                if (IsANSIEscapeCodeSupported ())
                {
                	FindAnsiEscCode (ThisLine, &ESCCode);
                }
                i+=EfiStrLen(ThisLine);
                i++;
            }
        }
    }
    newText[newTextLen] = L'\0';
    MemFreePointer((VOID **)&text);
    
    if (IsANSIEscapeCodeSupported ())
    {
    	MemFreePointer((VOID **)&ESCCode);
    }
    return newText;
}

VOID ScrollPostScreenLine()
{
	UINTN i,j;
	UINTN CopyFrom, CopyTo;


	for(i=stStartLine;i<EndRow;i++)
	{
		//Push up and discard extra line on top
		CopyFrom = ((i + 1)*gMaxCols)+StartCol;
		CopyTo = (i * gMaxCols)+StartCol;
		for(j=0;j<(EndCol-StartCol);j++)
		{
			gActiveBuffer->Attribs[CopyTo] = gActiveBuffer->Attribs[CopyFrom];
			gActiveBuffer->Chars[CopyTo] = gActiveBuffer->Chars[CopyFrom];
			if((i+1)==EndRow)
			{
				gActiveBuffer->Chars[CopyFrom] = L' ';
			}
			CopyFrom++;
			CopyTo++;
		}
	}

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PrintPostMessage
//
// Description:	function to Print the post massages
//
// Input:		CHAR16 *message, BOOLEAN bAdvanceLine
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PrintPostMessage( CHAR16 *message, BOOLEAN bAdvanceLine )
{
    UINTN LineCount;

	RUNTIME_DEBUG(L"printpostmsg");

	if(bAdvanceLine && (stNextLine > EndRow))
	{
		ScrollPostScreenLine();
		stNextLine = EndRow;
		stColNum = StartCol;
	}

    LineCount = DrawPostStringWithAttribute(stColNum,stNextLine,message, gPostMgrAttribute,bAdvanceLine);

	if(stPostScreenActive)
	{
		FlushLines(stStartLine,stNextLine+LineCount);
		DoRealFlushLines();
        MouseRefresh();//EIP 87424 : Mouse pointer disappear in POST when SOFTKBD_ICON_SUPPORT is enabled
	}

	if(bAdvanceLine)
    {
		stNextLine += LineCount;
		stColNum = StartCol;
		stNextLine++;
		if(stNextLine > gMaxRows)
			stNextLine = gMaxRows;
    }
	else {
		//EIP-41838: Update the Line number based on the string displayed, to not to overwrite the existing line in case of a big string.
		if(stColNum > gMaxCols)
		{
			stColNum = (stColNum%gMaxCols);
		}
		stNextLine = stNextLine+LineCount;
		if(stNextLine > EndRow)
		{
			ScrollPostScreenLine();
			stNextLine = EndRow;
		}
	}

	return EFI_SUCCESS;
}

//eip:26893-Start
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PreservePostMessages
//
// Description:	function to take care the postmessages when Screen mode changes
//				Only supported if OldMaxCols <= NewMaxCols
//
// Input:	UINTN NewMaxCols, UINTN OldMaxCols
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PreservePostMessages(UINTN NewMaxCols, UINTN OldMaxCols)
{
	UINTN i,CharCount;

	if(OldMaxCols <= NewMaxCols)
		return;
	// Loop to copy each line to newmax cols
	for(i=0;i<stNextLine;i++)
	{
		gBS->CopyMem ((VOID*)&gActiveBuffer->Attribs[i*NewMaxCols], (VOID*)&gActiveBuffer->Attribs[i*OldMaxCols],NewMaxCols);
		gBS->CopyMem ((VOID*)&gActiveBuffer->Chars[i*NewMaxCols], (VOID*)&gActiveBuffer->Chars[i*OldMaxCols],NewMaxCols*sizeof(CHAR16));
	}

	//clear chars after (NewCol * stNextLine) in the buffer
	CharCount = (stNextLine*OldMaxCols) - (stNextLine*NewMaxCols);
	for(i=0;i<CharCount;i++)
		gActiveBuffer->Chars[(stNextLine*NewMaxCols)+i] = L' ';
}
//eip:26893-End

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	DisplayActivePostMsgs
//
// Description:	function to Display active messages
//
// Input:		UINTN LogoHeight
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DisplayActivePostMsgs(UINTN LogoHeight)
{
	UINTN LinesToPush;

	if(!stPostScreenActive)
	{
		//First time showing the messages received. Adjust buffer to Logo height
		//Find out no of extra lines
		if((stNextLine-stStartLine) >= (gMaxRows - LogoHeight))
		{
			//Dicard only extra line that can not be shown
			stStartLine = (stNextLine - stStartLine) - (gMaxRows - LogoHeight);
		}
		//Push lines so that they will be seen below the logo
		LinesToPush = LogoHeight - stStartLine;
		if(LinesToPush)
		{
			UINTN CopyFrom, CopyTo;
	
			//Copy previous line if any
			if(stNextLine > stStartLine)
			{
				CopyTo = (stNextLine + LinesToPush) * gMaxCols;
				CopyFrom = stNextLine * gMaxCols;
	
				//Go to the end char of the previous line
				CopyTo--;
				CopyFrom--;
	
				while(1)
				{
					gActiveBuffer->Attribs[CopyTo] = gActiveBuffer->Attribs[CopyFrom];
					gActiveBuffer->Chars[CopyTo] = gActiveBuffer->Chars[CopyFrom];
					gActiveBuffer->Chars[CopyFrom] = (UINT16)L' ';
					gActiveBuffer->Attribs[CopyFrom] = (UINT8) EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY ;
					
					if(CopyFrom == (stStartLine * gMaxCols)) // Copy till the first char of the start line
						break;
	
					CopyFrom--;
					CopyTo--;
				}
			}
	
			//Modify Start and Next line values to new values
			stStartLine = LogoHeight;
			stNextLine = stNextLine + LinesToPush;
		}

		// make sure EndRow and EndCol is not bigger then ScreenSize
		EndRow = (EndRow>gMaxRows)?gMaxRows:EndRow;
		EndCol = (EndCol>gMaxCols)?gMaxCols:EndCol;
	}


	//Post screen activated
	stPostScreenActive = TRUE;

	//Flush lines if any
	if(stNextLine > stStartLine)
	{
		FlushLines(stStartLine,stNextLine-1);
		DoRealFlushLines();
	}
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	     SetCurPos
//
// Description:  Sets the cursor to the position defined by X and Y.
//
// Input:		UINTN X - Value of the column 
//				UINTN Y - Number of row below the last written line
//
// Output:		EFI_STATUS status - If the function runs correctly, returns
//				EFI_SUCCESS, else other EFI defined error values.
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetCurPos(UINTN X, UINTN Y)
{
    if((X < gMaxCols) && ( Y < gMaxRows))
    {
		stColNum = X;
        stNextLine = Y;
        return EFI_SUCCESS;
    }

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    GetCurPos
//
// Description: Writes cursor position into given X and Y locations.
//
// Input:		UINTN *pX - Pointer to storage for current column value 
//				UINTN *pY - Pointer to storage for current row value
//
// Output:		EFI_STATUS status - EFI_SUCCESS if OK,
//              EFI_INVALID_PARAMETER if NULL pointer
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetCurPos(UINTN * const pX, UINTN * const pY)
{
	EFI_STATUS retcode = EFI_INVALID_PARAMETER;

	if (NULL != pX && NULL != pY)
	{
	    if(stColNum < gMaxCols) {
		*pX = stColNum;
	    }
	    else {	//EIP-41753: If the nextline exceeds the limit, set the value based on gMaxCols value.
		*pX = gMaxCols-1; 
	    }

	    if(stNextLine < gMaxRows) {
		*pY = stNextLine;
	    }
	    else {	//EIP-41753: If the nextline exceeds the limit, set the value based on gMaxRows value.
		*pY = gMaxRows-1;
	    }

		retcode = EFI_SUCCESS;
	}
	return retcode;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    StrDup8
//
// Description: Duplicates a String of type CHAR8
//	
// Input:	CHAR8* string	
//
// Output:	CHAR8 *
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8 *StrDup8( CHAR8 *string )
{
	CHAR8 *text;

	text = EfiLibAllocatePool(1 + StrLen8( string ));
	if ( text != NULL )
		StrCpy8( text, string );

	return text;
}
#pragma warning( disable : 4706 )

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    StrDup8to16
//
// Description: Duplicates a String from CHAR8 to CHAR16
//
// Input:	CHAR8* string	
//
// Output:	CHAR16 *
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *StrDup8to16( CHAR8 *string )
{
	CHAR16  *text;
    UINTN   i;

	text = EfiLibAllocatePool( (1 + StrLen8( string )) * sizeof(CHAR16));
	if ( text != NULL )
    {
        i=0;
		while(text[i] = (CHAR16)string[i])
            i++;
    }

	return text;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    StrLen8
//
// Description: Returns Length of a String of type CHAR8
//
// Input:	CHAR8* string	
//
// Output:	UINTN
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN StrLen8(CHAR8 *string)
{
    UINTN i=0;
    while(string[i])
        i++;

    return i;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    StrCpy8
//
// Description: Copies a CHAR8 String from source to destination
//
// Input:	CHAR8 *dest, CHAR8 *src	
//
// Output:	VOID
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StrCpy8(CHAR8 *dest, CHAR8 *src)
{
    UINTN i=0;
    while(dest[i] = src[i])
        i++;
}


//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    GetTokenCount
//
// Description: 
//
// Input:	CHAR8 *String
//
// Output:	UINTN
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN GetTokenCount(CHAR8 *String)
{
	UINTN count = 0;
	UINTN j = 0;
	BOOLEAN token = FALSE;

	do
	{
		if(String[j] == ';')
		{
			if(token)
				count++;
			token = FALSE;
		}else
		{
			token = TRUE;
		}
	}while(String[j++]);

	return (token? (count + 1) : count);
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    GetTokenString
//
// Description:
//
// Input:	CHAR8 *String, UINTN *pos
//
// Output:	CHAR8 *
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* GetTokenString(CHAR8 *String, UINTN *pos)
{
	CHAR8 *text;
	UINTN i = 0, count = 0, j = 0;

	do
	{
		if(String[i] == ';')
		{
			break;
		}
		count++;
	}while(String[i++]);

	text = EfiLibAllocateZeroPool( (1 + count) * sizeof(CHAR8));
	if(text != NULL)
	{
		i = 0;
		do
		{
			text[j++] = String[i++];
		}while(j < count);
		*pos = i;
	}

	return text;
}

//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    StrDup16to8
//
// Description: Duplicates a String from CHAR16 to CHAR8
//
// Input:	CHAR16 *String
//
// Output:	CHAR8 *
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* StrDup16to8(CHAR16 *String)
{
	CHAR8 *text;
	UINTN len = 0, j = 0;

	while(String[j++])
		len++;
	text = EfiLibAllocateZeroPool( (1 + len) * sizeof(CHAR8));
	if(text != NULL)
	{
		j = 0;
		do
		{
			text[j] = (CHAR8)String[j];
		}while(j++ < len);
	}

	return text;
}

//EIP-126746 Start
//<AMI_PHDR_START>
//--------------------------------------------------------------------------
//
// Name:	    		FindAnsiEscCode
//
// Description:			Fills the EscCode in current line
//
// Input:				CHAR16 *, CHAR16 **
//
// Output:				void
//              
//
//--------------------------------------------------------------------------
//<AMI_PHDR_END>
void FindAnsiEscCode (CHAR16 *ThisLine, CHAR16 **EscCode)
{
	UINTN iIndex = 0, size = 0;

	while (ThisLine [iIndex])
	{
		if ( (ThisLine [iIndex] == 0x001b) && (ThisLine [iIndex+1] == L'[') )
		{
			size = 0;
			MemSet (*EscCode, 12 * sizeof (CHAR16), 0);
			while (ThisLine [iIndex] != L'm')
			{
				(*EscCode)[size] = ThisLine [iIndex];
				size++;
				iIndex++;
			}
			(*EscCode)[size] = L'm';
		}
		iIndex ++;
	}
}
//EIP-126746 END

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

