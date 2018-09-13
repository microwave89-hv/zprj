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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/AMILogo/AMILogo.h $
//
// $Author: Arunsb $
//
// $Revision: 6 $
//
// $Date: 10/18/12 5:58a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/AMILogo/AMILogo.h $
// 
// 6     10/18/12 5:58a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 8     10/10/12 12:36p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 5     1/31/12 1:22p Premkumara
// [TAG]  		EIP75136 
// [Category]  	New Feature
// [Description]  	Generic support for logos in RomHoles
// [Files]  		CommomHelper.c, AMITSE.sdl, AMITSE.mak, LogoLib.h,
// Postmgmt.c, AMILogo.h
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:14a Mallikarjunanv
// updated year in copyright message
// 
// 4     6/24/09 6:09p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
// 
// 3     6/23/09 6:55p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:11p Madhans
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
// Name:		AMILogo.h
//
// Description:	header file to define logo related stuff.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMI_LOGO_FV_
#define _AMI_LOGO_FV_

#define 	FOUR_GB_LIMIT 	0x100000000
//{63819805-67BB-46ef-AA8D-1524A19A01E4}
#define AMI_EFI_LOGO_GUID \
	{ 0x63819805, 0x67BB, 0x46ef, 0xAA, 0x8D, 0x15, 0x24, 0xA1, 0x9A, 0x01, 0xE4}

extern EFI_GUID gAMIEfiLogoGuid;
#endif //_AMI_LOGO_FV_
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
