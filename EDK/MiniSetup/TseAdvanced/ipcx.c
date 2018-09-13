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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/ipcx.c $
//
// $Author: Arunsb $
//
// $Revision: 7 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/ipcx.c $
// 
// 7     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 10    10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 8     2/19/10 8:11a Mallikarjunanv
// updated year in copyright message
// 
// 7     1/09/10 4:44a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 6     9/02/09 7:39p Madhans
// To Realy fix the Logo Security issue
// 
// 5     8/13/09 12:16p Blaines
// Move Image support to binary module
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
// 2     7/06/06 6:41p Arunkumars
// include minisetup.h
// include tiano.h instead of efi.h
// 
// 1     6/30/06 4:22p Madhans
// PCX image support in C.
// 
// 2     6/26/06 8:41a Shirinmd
// Modifications based on design change suggested by Madhan
// 
// 1     6/16/06 8:15a Shirinmd
// Added PCX Support in C for Minisetup
//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		ipcx.c
//
// Description:	This file contains code related to pcx image handling
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

#include "MyDefs.h"


BOOL DecodePCX(BYTE * pbyPCXInputData, BYTE * pbyPCXOutputData, DWORD dwPCXImageSize); //Function implemented in PCX_ADV.c
BOOL GetPCXDimensions( BYTE * pbyPCXImageData, UINT32 * pun32Width, UINT32 * pun32Height);	//Function implemented in PCX_ADV.c

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	ConvertPCXToUgaBlt
//
// Description:	Decode the PCX Image and store the output in UGA Format
//
// Input:		VOID *PCXImage - Pointer to the memory that has the PCX 
//						Image that need to be decoded.
//					UINT32 PCXImageSize - Size of the PCX Image
//					OUT VOID **UgaBlt - Two cases
//						Case 1: Memory is expected to be allocated by the callee.
//							Address provided as input should be NULL.
//							pointer that will receive the address of the UGA buffer. 
//							The buffer is allocated by callee.	
//							This buffer need to be freed by the caller. 		
//						Case 2: Memory is allocated by the caller
//					OUT UINT32 *UgaBltSize - Pointer that stores Size of UgaBlt in bytes. 
//						This will be treated as an input. This should have value ZERO for Case 2 above.
//					UINT32 *PixelHeight - Height of UgaBlt/PCX Image in pixels
//					UINT32 *PixelWidth - Width of UgaBlt/PCX Image in pixels
//
// Output:		EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConvertPCXToUgaBlt ( IN VOID *PCXImage, IN UINT32 PCXImageSize, IN OUT VOID **UgaBlt, IN OUT UINT32 *UgaBltSize, OUT UINT32 *PixelHeight, OUT UINT32 *PixelWidth){
	BOOL bStatus = FALSE;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	UINT64 unBltBufferSize = 0;
	bStatus = GetPCXDimensions(PCXImage, PixelWidth, PixelHeight);
	if(bStatus)
	{
		// Make sure to do x64 Mul
		unBltBufferSize = MultU64x32((UINT64)(*PixelWidth), (*PixelHeight));

		/// Check whether the Size exceeds the limit...
		//  4GB/PIXEL_SIZE becoz we need Resolution*PIXEL_SIZE for bltbuffer
		if ( unBltBufferSize >= (FOUR_GB_LIMIT/sizeof (EFI_UGA_PIXEL))) {
			// The buffer size extends the limitation
			return EFI_UNSUPPORTED;
		}

		unBltBufferSize = MultU64x32( unBltBufferSize ,sizeof (EFI_UGA_PIXEL));

		if(NULL!=*UgaBlt)
		{
			if(*UgaBltSize<(UINT32)unBltBufferSize)
			{
				*UgaBltSize = (UINT32)unBltBufferSize;
				Status = EFI_BUFFER_TOO_SMALL;
				bStatus = FALSE;
			}
		}
		else
		{
			*UgaBltSize = (UINT32)unBltBufferSize;
			*UgaBlt = EfiLibAllocatePool((UINT32)unBltBufferSize);
			if(NULL == *UgaBlt)
			{
				Status = EFI_OUT_OF_RESOURCES;
				bStatus = FALSE;
			}
		}
		if(bStatus)
		{
			MemSet(*UgaBlt,*UgaBltSize,0);
			bStatus = DecodePCX(PCXImage, *UgaBlt, PCXImageSize);
			if(bStatus)
				Status = EFI_SUCCESS;
		}
	}
	return Status;
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
