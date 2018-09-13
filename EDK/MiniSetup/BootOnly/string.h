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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/string.h $
//
// $Author: Arunsb $
//
// $Revision: 7 $
//
// $Date: 10/18/12 5:59a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/string.h $
// 
// 7     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     10/21/11 2:58a Rajashakerg
// [TAG]  		EIP60563 
// [Category]  	New Feature
// [Description]  	Updating the file with fix for issue : maximum 8 byte
// value shows negative number
// [Files]  		numeric.c, numeric.h, string.c, string.h
// 
// 5     6/20/11 12:26p Rajashakerg
// [TAG]  		EIP60563
// [Category]  	New Feature
// [Description]  	Support for signed decimal value for
// EFI_IFR_NUMERIC_OP.
// [Files]  		numeric.c, numeric.h, string.c, string.h, Uefi21Wapper.c
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 5:43a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     9/25/09 6:37a Sudhirv
// EIP-26893 : when the DisplayPostMessage() function of the AMI Post
// Manager protocol is called multiple times, strings are truncated when
// displayed.
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:13p Madhans
// Tse 2.0 Code complete Checkin.
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
// Name:		string.h
//
// Description:	Header file for string functionalities.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _STRING_H_
#define	_STRING_H_

#define CharIsUpper(c) ((c >= L'A') && (c <= L'Z'))
#define CharIsLower(c) ((c >= L'a') && (c <= L'z'))
#define CharIsAlpha(c) (CharIsUpper(c) || CharIsLower(c)) 
#define CharIsNumeric(c) ((c >= L'0') && (c <= L'9'))
#define CharIsAlphaNumeric(c) (CharIsAlpha(c) || CharIsNumeric(c))
#define CharIsAlphaNumericSpecial(c) ((c >= (CHAR16)0x20) && (c <= (CHAR16)0x7E))

#define	JUSTIFY_CENTER	(0)
#define	JUSTIFY_LEFT	(1)
#define	JUSTIFY_RIGHT	(2)
#define	JUSTIFY_MAX		JUSTIFY_RIGHT

UINTN atoi(CHAR16 *string, UINT8 base);
CHAR16 *StrZeroPad(INT32 Tm, CHAR16 *Str);
CHAR16 *StrDup(CHAR16 *string);
VOID DrawAttribute( UINTN Col, UINTN Row, UINT8 Attrib, UINTN Length );
VOID DrawAttributeOffset( UINTN Offset, UINT8 Attrib, UINTN Length );
VOID DrawString( UINTN Col, UINTN Row, CHAR16 *String );
VOID DrawStringWithAttribute( UINTN Col, UINTN Row, CHAR16 *String, UINT8 Attrib );
VOID DrawMultiLineStringWithAttribute( UINTN Col, UINTN Row,UINTN Width, UINTN Height, CHAR16 *line, UINT8 Attrib );
VOID DrawStringJustified( UINTN MinCol, UINTN MaxCol, UINTN Row, UINTN Justify, CHAR16 *String );
VOID DrawStringJustifiedWithAttribute( UINTN MinCol, UINTN MaxCol, UINTN Row, UINTN Justify, CHAR16 *String, UINT8 Attrib );
VOID WriteChar( UINTN Row, UINTN Col, CHAR16 Char );
VOID WriteCharWithAttribute( UINTN Row, UINTN Col, CHAR16 Char, UINT8 Attrib );

CHAR16 *StringWrapText( CHAR16 *text, UINT16 width, UINT16 *height );
UINTN StringGetWrapHeight( CHAR16 *text, UINT16 width );
UINTN _StringFindBreak( CHAR16 *string );

EFI_STATUS PrintPostMessage( CHAR16 *message, BOOLEAN bAdvanceLine );
VOID DisplayActivePostMsgs(UINTN LogoHeight);
VOID PreservePostMessages(UINTN NewMaxCols, UINTN OldMaxCols);	//eip:26893

EFI_STATUS SetCurPos(UINTN X, UINTN Y);
EFI_STATUS GetCurPos(UINTN * const pX, UINTN * const pY);
UINTN GetTokenCount(CHAR8 *String);
CHAR8* GetTokenString(CHAR8 *String, UINTN *pos);
CHAR8 *StrDup8( CHAR8 *string );
CHAR16 *StrDup8to16( CHAR8 *string );
UINTN StrLen8(CHAR8 *string);
VOID StrCpy8(CHAR8 *dest, CHAR8 *src);
CHAR8* StrDup16to8(CHAR16 *String);

#endif /* _STRING_H_ */


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
