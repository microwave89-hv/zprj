//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2013, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/TseElinks.h $
//
// $Author: Premkumara $
//
// $Revision: 6 $
//
// $Date: 3/25/13 8:41a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Inc/TseElinks.h $
// 
// 6     3/25/13 8:41a Premkumara
// [TAG]  		EIP116315
// [Category]  	Improvement
// [Description]  	Display control prompt string for password control.
// (for String on CHAP secret popup)
// [Files]  		- AMITSE.sdl
// - CommonHelper.c
// - FakeToken.c
// - AmiTSEStr.uni
// - TseLite\PopupPassword.c
// - uefi2.1\UefiWapper21.c
// - uefi2.0\UefiWapper20.c
// - uefi2.0\HiiCallback.c
// - uefi2.0\hii.h
// - uefi2.0\hii.c  
// 
// 5     10/18/12 5:31a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 5     10/10/12 12:23p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 4     5/28/12 6:21a Rajashakerg
// [TAG]  		EIP80873
// [Category]  	Improvement
// [Description]  	TSE Load/Save defaults without Messaaagebox.
// [Files]  		TseElinks.h, Tseadvanced.c
// 
// 3     11/13/11 12:22p Arunsb
// [TAG]  		EIP70421
// [Category]  	New Feature
// [Description]  	Support for driver order in TSE
// [Files]  		AMITSE.SDL, CommonHelper.c, setup.ini, uefisetup.ini,
// boot.c,
// minisetup.h, bbs.c, special.c, special.h, tseadvanced.c,
// addbootoption.c,
// callback.c, minisetupext.c, minisetupext.h, popupsel.c, popupsel.h,
// TseLitehelper.c, variable.c, Uefi21Wapper.c, AMIVfr.h, boot.h,
// TseElink.h, variable.h, 
// setup.h, Boot.vfr and Setup.uni
// 
// 2     12/29/10 5:11a Mallikarjunanv
// [TAG]  		EIP41615
// [Category]  	New Feature
// [Description]  	Added the file browser support for the Add boot option
// reated controls
// 
// [Files]  		AmiVfr.h, AmiTse.sdl, AmiTseStr.uni, CommonHelper.c,
// Faketokens.c, TseElinks.h, EdkHelper.h, minisetup.h, TseAdvanced.c,
// AddBootOption.c
// 
// 1     2/19/10 12:58p Madhans
// Uploaded for TSE 2.01. Refer Changelog.log for File change history.
// 
// 2     2/19/10 7:59a Mallikarjunanv
// updated the year in copyright message
// 
// 1     7/30/09 7:32a Mallikarjunanv
// New header file to handle the Elinks related inforamtion
// 
// 1     7/30/09 7:27a Mallikarjunanv
// New file to handle Elink related definitions
// 
// 
//
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		TseElinks.h
//
// Description:	Header file for Elink related customizations
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _TSEELINKS_H_
#define _TSEELINKS_H_

#define END_OF_EXIT_PAGE_OPTION_LIST	0xFF

///Default fucntions to handle Exit page options...
VOID HandleSaveAndExit(VOID);
VOID HandleExitApplication(VOID);
VOID HandleSaveAndReset(VOID);
VOID HandleResetSys(VOID);
VOID HandleSaveWithoutExit(VOID);
VOID HandleLoadPreviousValues(VOID);
VOID HandleLoadOptimalDefaults(VOID);
VOID HandleSaveUserDefaults(VOID);
VOID HandleRestoreUserDefaults(VOID);
VOID HandleBootAddBootOption(VOID);
VOID HandleLaunchFileSystem(VOID);	//EIP_41615 related to file browser support in AddBootOption
VOID HandleLaunchFileSystemDriver (VOID);
VOID HandleDriverAddDriverOption (VOID);
VOID SaveUserDefaultsSilently(VOID);
VOID LoadUserDefaultsSilently(VOID);

typedef	VOID	(*OPTION_CALLBACK)(VOID);

typedef struct _EXIT_PAGE_OPTIONS
{
	UINT8	OptIdx;
	OPTION_CALLBACK		ExitPageCallBack;
}
EXIT_PAGE_OPTIONS;

typedef struct			
{
	EFI_GUID FormsetGuid;
	UINT32	QuestionID;
	BOOLEAN 	EncodingFlag;
}PASSWORD_ENOCDE_LIST_TEMPLATE;

#endif /* _TSEELINKS_H_ */

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**         (C)Copyright 2013, American Megatrends, Inc.             **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093       **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
