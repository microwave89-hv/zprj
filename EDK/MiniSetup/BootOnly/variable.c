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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/variable.c $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/variable.c $
// 
// 7     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     9/28/11 10:48p Arunsb
// [TAG]  		EIP66369
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	English strings appears intermediately when Chinese is a
// current language
// [RootCause]  	Some cases lang variable is not NULL terminated
// [Solution]  	Lang variable made as NULL terminated.
// [Files]  		BootOnly\Variable.c
// 
// 5     6/17/10 2:59p Madhans
// Dynamic parsing support in TSE.
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 5     2/18/10 8:26p Madhans
// To take care NOGET and NOSET Attribs from Exetendedflags of
// VariableInfo
// 
// 4     1/09/10 5:44a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
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
// Name:		variable.c
//
// Description:	This file contains code to handle bootonly lever variables operations.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

extern UINTN gSetupCount;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarGetNvramName
//
// Description:	function to get the NvRam Variable Name
//
// Input:		CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size
//
// Output:		Name String
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *VarGetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size )
{
	VOID *buffer = NULL;
	UINT32 attrib = 0;
	EFI_STATUS Status = EFI_UNSUPPORTED;

	// NO GET Functionality is taken care by VarGetNvram()

	if ( attributes != NULL )
    {
        attrib = *attributes;
    }

	Status = UefiFormCallbackNVRead(name, guid, &attrib, size, &buffer);

	if(EFI_ERROR(Status))
	{
	    Status = gRT->GetVariable(
			name,
			guid,
			&attrib,
			size,
			buffer
			);

	    if ( Status != EFI_BUFFER_TOO_SMALL )
		    return buffer;

	    buffer = EfiLibAllocateZeroPool ( *size + 1);
	    if ( buffer == NULL )
		   return buffer;

	    Status = gRT->GetVariable(
			name,
			guid,
			&attrib,
			size,
			buffer
			);
	}
	    
	if ( EFI_ERROR( Status ) )
	    MemFreePointer( (VOID *)&buffer );

	if ( attributes != NULL )
		*attributes = attrib;

	return buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	VarSetNvramName
//
// Description:	function to Set the NvRam Variable Name
//
// Input:		CHAR16 *name, EFI_GUID *guid, UINT32 *attributes,
//					VOID *buffer, UINTN *size
//
// Output:		status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS VarSetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size )
{
	EFI_STATUS Status = EFI_UNSUPPORTED;

	// NO SET Functionality is taken care by VarSetNvram()

	Status = UefiFormCallbackNVWrite(name, guid, attributes, buffer, size);

	if(EFI_ERROR(Status ) )
		Status = gRT->SetVariable(
			name,
			guid,
			attributes,
			size,
			buffer
			);

	return(Status);
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
