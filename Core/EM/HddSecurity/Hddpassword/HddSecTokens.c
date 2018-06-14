//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/HddSecurity/HddPassword/HddSecTokens.c 2     3/25/13 5:16a Rameshr $
//
// $Revision: 2 $
//
// $Date: 3/25/13 5:16a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSecurity/HddPassword/HddSecTokens.c $
// 
// 2     3/25/13 5:16a Rameshr
// [TAG]  		EIP117159
// [Category]  	Improvement
// [Description]  	Proper error message displayed when the Password count
// expired 
// [Files]  		HddPassword.c, HddPassword.uni, HddSecTokens.c
// 
// 1     3/11/10 3:51a Rameshr
// Issue: Same Structure definied in Hddpassword and Amitse.
// Solution: Amitse created tsecommon.h with all the common definition.
// EIP: 27339
// 
// Initial check-in
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:		HddSecTokens.c
//
// Description:
// This file does not add any code. It has, all the string tokens that
// are used by Minisetup, to fake the usage to strgather.exe. Add to
// this list, the new string tokens that are defined in
// AmiTSEStrstr.uni and to be used by Minisetup
//
//<AMI_FHDR_END>
//**********************************************************************


//Following code is to force strgatherer to include these strings
#if 0

STRING_TOKEN(STR_IDE_SECURITY_UNSUPPORTED)
STRING_TOKEN(STR_IDE_SECURITY_LOCKED)
STRING_TOKEN(STR_IDE_ERROR_PSWD)
STRING_TOKEN(STR_IDE_SECURITY_PROMPT)
STRING_TOKEN(STR_IDE_ENTER_USER)
STRING_TOKEN(STR_IDE_ENTER_MASTER)
STRING_TOKEN(STR_IDE_UNLCK_COLD)

#endif

//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2013, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           5555 Oakbrook Pkwy, Norcross, Georgia 30093       **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
