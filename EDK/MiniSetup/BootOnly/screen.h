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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/screen.h $
//
// $Author: Arunsb $
//
// $Revision: 4 $
//
// $Date: 10/18/12 5:59a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/screen.h $
// 
// 4     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 6     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 3     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 3     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 2     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:13p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

#ifndef _SCREEN_H_
#define	_SCREEN_H_

VOID ClearScreenWithoutFlush( UINT8 Attrib );
VOID ClearLinesWithoutFlush( UINT8 LineStart, UINT8 NumLines, UINT8 Attrib );
VOID ClearScreen( UINT8 Attrib );
VOID *SaveScreen( VOID );
VOID RestoreScreen( VOID *ScreenBuffer );

typedef struct
{
	UINT32	ScreenTag;
	UINT8	Attribs[MAX_DIMENSIONS];
	CHAR16	Chars[MAX_DIMENSIONS];
}
SCREEN_BUFFER;

#define	ACTIVE_SCREEN_TAG	0x54434153	// "SACT"
#define	SAVE_SCREEN_TAG		0x56415353	// "SSAV"

extern SCREEN_BUFFER *gActiveBuffer;

VOID MemFillUINT16Buffer( VOID *buffer, UINTN bufferSize, UINT16 value );

#endif /* _SCREEN_H_ */

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
