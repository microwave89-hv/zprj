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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/mem.c $
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
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/mem.c $
// 
// 5     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 4     11/10/11 12:52a Arunsb
// [TAG]  		EIP67735
// [Category]  	Improvement
// [Description]  	Zeroing password buffers before freeing
// [Files]  		mem.c, mem.h, popupedit.c, popuppassword.c and tseadvanced.c
// 
// 3     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
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
// 1     4/28/09 11:12p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 3:37p Madhans
// TSE_USE_EDK_LIBRARY
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
// Name:		mem.c
//
// Description:	file contains code to handle the memory operations. 
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemFreePointer
//
// Description:	function to free the pointers
//
// Input:		VOID **ptr
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemFreePointer( VOID **ptr )
{
	if ( ( ptr == NULL ) || ( *ptr == NULL ) )
		return;

	gBS->FreePool( *ptr );
	*ptr = NULL;
}

//<AMI_PHDR_START>
//-----------------------------------------------------------------------------------------------
// Procedure:	StringZeroFreeMemory
//
// Description:	Function to free the string pointers and zeroing its memory, used for strings
//				Care should be taken String Length identification function is used
//
// Input:		VOID **ptr
//
// Output:		void
//
//-------------------------------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StringZeroFreeMemory (VOID **ptr)
{
	if ( (ptr == NULL) || (*ptr == NULL))
		return;

	MemSet (*ptr, (EfiStrLen ((CHAR16 *)*ptr) * sizeof (CHAR16)), 0);
	gBS->FreePool (*ptr);
	*ptr = NULL;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemCopy
//
// Description:	function to copy a memory
//
// Input:		VOID *dest, VOID *src, UINTN size
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemCopy( VOID *dest, VOID *src, UINTN size )
{
	gBS->CopyMem( dest, src, size );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemSet
//
// Description:	function to set the memory with the specified value
//
// Input:		VOID *buffer, UINTN size, UINT8 value
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if TSE_USE_EDK_LIBRARY
VOID MemSet( VOID *buffer, UINTN size, UINT8 value )
{
	gBS->SetMem( buffer, size, value );
}
#endif //#if TSE_USE_EDK_LIBRARY

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemReallocateZeroPool
//
// Description:	function to reuse a allocated buffer
//
// Input:		VOID *oldBuffer, UINTN oldSize, UINTN newSize
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *MemReallocateZeroPool( VOID *oldBuffer, UINTN oldSize, UINTN newSize )
{
	VOID *buffer;

	buffer = EfiLibAllocateZeroPool( newSize );
	if ( buffer == NULL )
		return buffer;

	if ( newSize < oldSize )
		oldSize = newSize;

	if ( oldBuffer != NULL )
		MemCopy( buffer, oldBuffer, oldSize );

	MemFreePointer( (VOID **)&oldBuffer );

	return buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemFillUINT16Buffer
//
// Description:	function to fill a UINT16 Buffer
//
// Input:		VOID *buffer, UINTN bufferSize, UINT16 value
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MemFillUINT16Buffer( VOID *buffer, UINTN bufferSize, UINT16 value )
{
	UINTN	Index;
	UINT16	*bufPtr = (UINT16 *)buffer;

	for ( Index = 0; Index < bufferSize; Index++ )
		*bufPtr++ = value;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MemCmp
//
// Description:	function to compare the memory of two buffers.
//
// Input:		UINT8 *dest, UINT8 *src, UINTN size
//
// Output:		0/1/-1
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if TSE_USE_EDK_LIBRARY
INTN MemCmp( UINT8 *dest, UINT8 *src, UINTN size )
{
	UINTN i;

	for( i=0; i<size; i++)
	{
		if(dest[i] < src[i])
			return -1;
        if(dest[i] > src[i])
            return 1;
	}
	return 0;
}
#endif //#if TSE_USE_EDK_LIBRARY

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
