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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/hiistring.c $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/hiistring.c $
// 
// 5     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     12/02/10 2:33p Madhans
// [TAG] - EIP 48169  
// [Category]- Enhancement
// [Severity]- Mordarate
// [Symptom]- Code Cleanup and Compiler Warning need to resolved.
// [Rootcause] Warnings reported when we build AMI higher Warning level.
// [Solution]- 1. Fix the warnings and do the code cleanup. 
//             2. Introduce proper checks.
//             3. change the popupSel.c to not change the Option/variable
// cache to default or first option
//                when the variable cache is not matching with any of
// option.
// [Files] - commonoem.c bbs.c boot.c hiistring.c resource.c
// popuppassword.c popupsel.c
//           expression.c hii.c parse.c
// 
// 3     2/19/10 1:01p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 4     6/23/09 6:56p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 3     6/12/09 7:41p Presannar
// Initial implementation of coding standards
// 
// 2     6/08/09 5:35p Madhans
// Functionality moved to CommonHelper.
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:39p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 3:34p Madhans
// Hii string support for UEFI 2.0 or UEFI 2.1
// 
// 1     12/18/08 7:58p Madhans
// Intial version of TSE Lite sources
// 
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		hiistring.c
//
// Description:	file contains code to handle the hii sting operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

#define VARIABLE_NAME_LENGTH 40

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiFindStrPrintBoundary
//
// Description:	function to check the boundary of the print stirng.
//					Find out the index of the character from where the print boundry will be met
//
// Input:		IN CHAR16   *String, IN UINTN PrintWidth
//
// Output:		count
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN HiiFindStrPrintBoundary ( IN CHAR16   *String, IN UINTN PrintWidth )
{
  UINTN Length = 0;
  UINT16                Count = 0;
  CHAR16				TempString[10];

  while (String[Count]) {
	  TempString[0] = String[Count];
	  TempString[1] = 0;

	  if((Length + TestPrintLength(TempString) / NG_SIZE) > PrintWidth)
		  break;

	  Length += TestPrintLength(TempString) / NG_SIZE;

	  Count++;
  }
  return Count;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	IsCharWide
//
// Description:	function to check the given character is wide
//
// Input:		CHAR16 strWide
//
// Output:		TRUE/FALSE
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN IsCharWide( CHAR16 strWide)
{
  UINTN		Length = 0;
  CHAR16	TempString[10];

  TempString[0] = strWide;
  TempString[1] = 0;
  Length = 0;
  Length = TestPrintLength( TempString ) / (NG_SIZE);
  if(2 == Length)
	  return TRUE;
  else
	  return FALSE;
}

CHAR16 *HiiGetString( VOID* handle, UINT16 token )
{
	if(INVALID_TOKEN != token)
		return HiiGetStringLanguage( handle, token, NULL );
	else
		return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	HiiAddString
//
// Description:	function to add a string
//
// Input:		VOID* handle, CHAR16 *string
//
// Output:		token
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16 HiiAddString( VOID* handle, CHAR16 *string )
{
	UINT16 token = 0;

	if(ItkSupport())
	{
	    token = HiiChangeStringLanguage( handle, 0, gLanguages[0].Unicode, string );
	}
	else
	{
	    UINT16 FirstToken;
		UINTN i, j;

		FirstToken = token = HiiChangeStringLanguage( handle, 0, gLanguages[0].Unicode, string );
	    if ( token == INVALID_TOKEN )
	    	return token;
		for ( j = 0, i = 1; i < gLangCount; i++ )
	    {
	        if ( i != j )
	    		token = HiiChangeStringLanguage( handle, token, gLanguages[i].Unicode, string );
	        if ( token == INVALID_TOKEN )
	        {
			    token = HiiChangeStringLanguage( handle, 0, gLanguages[i].Unicode, string );
	            if ( token == INVALID_TOKEN )
	    	        return FirstToken; //token;
	            j = i;
	            i = 0;
	        }
	    }
	}
   	return token;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EfiTestPrintLength
//
// Description:	function to get the printable lenght of the string
//
// Input:		CHAR16 *string
//
// Output:		Size of string
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN EfiTestPrintLength ( IN CHAR16   *String )
{
	UINTN Size;

	if(String == NULL)
		return 0;

	String = (UINT16* )TseSkipEscCode(String);
	Size = (EfiStrLen(String) * NG_SIZE);
	gBS->FreePool( String );
	return Size;
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

