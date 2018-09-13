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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/password.c $
//
// $Author: Arunsb $
//
// $Revision: 7 $
//
// $Date: 5/08/14 9:17p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/password.c $
// 
// 7     5/08/14 9:17p Arunsb
// TsePasswordEncodeLocal function moved to PasswordEncode module
// 
// 6     5/02/14 9:27p Arunsb
// TsePasswordEncodeLocal function moved to source
// 
// 5     5/02/14 2:04a Premkumara
// TAG]  		EIP162197
// [Category]  	Improvement
// [Description]  	Password encode feature modify to encode using Hashing
// based on token.
// [Files]  		Password.c, PasswordEncodeBin.cif, AMITSE.cif,
// TSESource.cif, PasswordEncode.c, PasswordEncode.h, AMITSE.sdl,
// CommonHelper.c, PasswordEncodeBin.mak, PasswordEncodeBin.sdl
// 
// 4     5/22/13 10:37a Arunsb
// EIP123047 - 
// 
// 3     10/18/12 5:59a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 2     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 2     12/08/11 12:46p Rajashakerg
// [TAG]    EIP63190 
// [Category]   New Feature
// [Description]   Security operations in BootOnly module instead of
// TSELite. GetAMITSEVariableLocal moved to tselite.
// 
// 1     12/08/11 4:54a Arunsb
// EIP63190 => Moving password support from TSELite to BootOnly
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:18a Mallikarjunanv
// updated year in copyright message
// 
// 5     7/09/09 12:29p Mallikarjunanv
// updated the password encoding fix
// 
// 3     6/23/09 6:52p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:05p Madhans
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
// Name:		password.c
//
// Description:	This file contains code to handle password operations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PasswordCheckInstalledLocal
//
// Description:	function to check the password type
//
// Input:	void
//
// Output:	void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 PasswordCheckInstalledLocal(VOID)
{
	UINT32	Installed = AMI_PASSWORD_NONE;
	UINT8 *setup = NULL;
	AMITSESETUP *mSysConf = NULL;
	UINTN VarSize = 0;
	CHAR16 *TestPassword;
	
	TestPassword = EfiLibAllocateZeroPool((TsePasswordLength + 1)*sizeof(CHAR16));
	
	GetAMITSEVariable(&mSysConf,&setup,&VarSize);

	if ( ( mSysConf != NULL ) && ( VarSize == sizeof(AMITSESETUP) ) )
	{
		MemSet( TestPassword, (TsePasswordLength + 1)*sizeof(CHAR16), 0 );
		if ( ! EfiCompareMem( TestPassword, mSysConf->UserPassword, TsePasswordLength * sizeof(CHAR16) ) )
			Installed |= AMI_PASSWORD_USER;
		if ( ! EfiCompareMem( TestPassword, mSysConf->AdminPassword, TsePasswordLength * sizeof(CHAR16) ) )
			Installed |= AMI_PASSWORD_ADMIN;
		Installed ^= AMI_PASSWORD_ANY;
	}

	if(setup)
		MemFreePointer( (VOID **)&setup );
	else
		MemFreePointer( (VOID **)&mSysConf );

	MemFreePointer( (VOID **)&TestPassword);

	return Installed;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PasswordAuthenticateLocal
//
// Description:	function to check the authentication of the password
//
// Input:	CHAR16 *Password
//
// Output:	password type
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsPasswordSupportNonCaseSensitive ();
UINT32 PasswordAuthenticateLocal( CHAR16 *Password )
{
	UINT32 PasswordType = AMI_PASSWORD_NONE;
	UINT8 *setup = NULL;
	AMITSESETUP *mSysConf = NULL;
	UINTN VarSize = 0;
	CHAR16 *EncPass;
	UINTN	ii;

	GetAMITSEVariable(&mSysConf,&setup,&VarSize);
	
	if ( ( mSysConf == NULL ) || ( VarSize != sizeof(AMITSESETUP) ) )
		return PasswordType;

	EncPass = EfiLibAllocateZeroPool((TsePasswordLength + 1)*sizeof(CHAR16));

	MemSet( EncPass, (TsePasswordLength + 1)*sizeof(CHAR16), 0 );
	EfiStrCpy( EncPass, Password );
	if (IsPasswordSupportNonCaseSensitive ()) //If admin/user passwords are not encoded then case pbm will arose so avoiding that
	{
		for (ii = 0; ii < TsePasswordLength; ii++)
			Password [ii] = ((Password [ii]>=L'a')&&(Password [ii]<=L'z'))?(Password [ii]+L'A'-L'a'):Password [ii];
	}

	PasswordEncodeHook( EncPass, TsePasswordLength*sizeof(CHAR16));

//EIP 23354 : Start
	if ( ( ! EfiCompareMem( Password, mSysConf->UserPassword, TsePasswordLength * sizeof(CHAR16) ) ) ||
		 ( ! EfiCompareMem( EncPass, mSysConf->UserPassword, TsePasswordLength * sizeof(CHAR16) ) ) )
	{
		PasswordType = AMI_PASSWORD_USER;
	}

	if ( ( ! EfiCompareMem( Password, mSysConf->AdminPassword, TsePasswordLength * sizeof(CHAR16) ) ) ||
		 ( ! EfiCompareMem( EncPass, mSysConf->AdminPassword, TsePasswordLength * sizeof(CHAR16) ) ) )
	{
		PasswordType = AMI_PASSWORD_ADMIN;
	}
//EIP 23354 : End

	if(setup)
		MemFreePointer( (VOID **)&setup );
	else
		MemFreePointer( (VOID **)&mSysConf );

	MemFreePointer( (VOID **)&EncPass );

	return PasswordType;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	PasswordUpdateLocal
//
// Description:	function to ubdate the password
//
// Input:	CHAR16 *Password, , UINTN Size
//
// Output:	updated password
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR16 *PasswordUpdateLocal( CHAR16 *Password, UINTN Size )
{
	CHAR16 *Buffer = NULL;

    if ( Password[0] == L'\0' )
        return Password;

	Buffer = EfiLibAllocateZeroPool( Size );
	if ( Buffer == NULL )
		return Buffer;

	MemCopy( Buffer, Password, Size );
	PasswordEncodeHook( Buffer, Size );

	return Buffer;
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
