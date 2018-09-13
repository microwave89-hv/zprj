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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/PasswordEncode/TsePasswordEncode.c $
//
// $Author: Arunsb $
//
// $Revision: 2 $
//
// $Date: 7/16/14 1:40p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/PasswordEncode/TsePasswordEncode.c $
// 
// 2     7/16/14 1:40p Arunsb
// [TAG]	EIP178064
// [Category]	Bug Fix
// [Severity:]	Normal
// [Symptom:]	Password window hangs on post
// [Root Cause]	Memory accessed over the allocated range
// [Solution]	While changing the incoming password to non case sensitivie
// memory accessed only within range.
// [Files]	PasswordEncode\PasswordEncode.c and
// PasswordEncode\TsePasswordEncode.c
// 
// 1     5/08/14 4:37p Arunsb
// [TAG]  		EIP162197
// [Category]  	Improvement
// [Description]  	Password encode feature. Modify to encode using Hashing
// based on token.
// Separate module created for TSE password encoding logic.
// 
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:          CtrlCond.C
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
#include "minisetup.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    TsePasswordEncodeLocal
//
// Description:   	Function to encode the password string
//
// Parameter:	    CHAR16 *Password, UINTN MaxSize
//
// Return value:  	VOID
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsPasswordSupportNonCaseSensitive();
VOID TsePasswordEncodeLocal ( CHAR16 *Password, UINTN MaxSize)
{
	UINTN	ii;
	unsigned int key = 0x935b;

   if (IsPasswordSupportNonCaseSensitive ())
   {
   	for ( ii = 0; ii < MaxSize/2; ii++ )
		   Password[ii] = ((Password[ii]>=L'a')&&(Password[ii]<=L'z'))?(Password[ii]+L'A'-L'a'):Password[ii];
   }
	// Encode the password..
	for ( ii = 1; ii <= MaxSize/2; ii++ )
			Password[ii-1] = (CHAR16)(Password[ii-1] ^ (key*ii));
}

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
