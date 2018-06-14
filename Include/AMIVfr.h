//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2014, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Include/AMIVfr.h $
//
// $Author: Arunsb $
//
// $Revision: 24 $
//
// $Date: 5/08/14 9:11p $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Include/AMIVfr.h $
// 
// 24    5/08/14 9:11p Arunsb
// EIP122164 changes reverted since the EIP is not generic.
// 
// 23    5/02/14 5:10p Premkumara
// [TAG]  			EIP162197
// [Category]  	Improvement
// [Description]  	Password encode feature modify to encode using Hashing
// based on token.
// [[Files]  		Password.c, PasswordEncodeBin.cif, AMITSE.cif,
// TSESource.cif, PasswordEncode.c, PasswordEncode.h, AMITSE.sdl,
// PasswordEncodeBin.mak, PasswordEncodeBin.sdl
// AMIVfr.h, Boot.c
// 
// 22    5/02/14 6:58a Premkumara
// [TAG]  		EIP137373
// [Category]  	Improvement
// [Description]  	Added signal event for BeforeTimeOut and AfterTimeOut
// with guids
// [Files]  		AMIVfr.h,protocol.c
// 
// 21    5/02/14 2:17a Arunsb
// [TAG]  		EIP158989
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	BGRT status bit not cleared with Shell v2.0
// [RootCause]  	Shell v2.0 protocol not registered
// [Solution]  	Shell v2.0 protocol registered and cleared the BGRT status
// bit
// [Files]  		AMIVfr.h and boot.c
// 
// 20    2/11/14 7:31p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 19    1/30/14 3:21a Premkumara
// [TAG]  		EIP122164
// [Category]  	Improvement
// [Description]  	Struct IDE_SECURITY_CONFIG added for IDE security
// module
// [Files]  		AMIVfr.h
// 
// 18    1/22/14 10:53a Premkumara
// [TAG]  		EIP148071
// [Category]  	Improvement
// [Description]  	Changed Path[1] to Path[120] in NEW_BOOT_OPTION struct
// [Files]  		AMIVfr.h
// 
// 17    12/04/13 2:44p Arunsb
// [TAG]	EIP125219
// [Category]	Improvement
// [Description]	Add event at end of BootFlowManageExit() after second
// boot path
// [Files]	bootflow.c, AMIVfr.h
// 
// 16    11/07/13 1:56a Premkumara
// [TAG]	EIP-137373
// [Category]	Improvement
// [Description]	Added signal event for BeforeTimeOut and AfterTimeOut
// with GUID
// [Files]	Protocol.c, AMIVfr.h
// 
// 15    12/01/12 6:48a Premkumara
// [TAG]  		EIP105725 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Setup hangs on BBS Menu having string more than 200
// characters
// [RootCause]  	File path string is not handled properly
// [Solution]  	Handled FilePath strings based on length of string and
// allocate memory based on length dynamically
// [Files]  		AddBootOption.c, AMIVfr.h
// 
// 14    10/18/12 5:44a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:24p Arunsb
// Synched the source for v2.16.1232 backup with Aptio
// 
// 12    9/25/12 12:28p Rajashakerg
// [TAG]  		EIP92053 
// [Category]  	Improvement
// [Description]  	Need support define Root page order using elinks
// [Files]  		AMITSE.sdl, Menu.c, AMIVfr.h, AMITSE.mak, commonoem.c
// 
// 11    9/25/12 9:30a Rajashakerg
// [TAG]  		EIP92053 
// [Category]  	Improvement
// [Description]  	Need support define Root page order using elinks
// [Files]  		AMITSE.sdl, Menu.c, AMIVfr.h, AMITSE.mak, commonoem.c
// 
// 10    1/30/12 3:30a Arunsb
// [TAG]  		EIP74676
// [Category]  	Improvement
// [Description]  	Setup.ini and Upfisetup.ini to reserve 3~5 variable and
// 		GUID for porting purpose
// [Files]  		Amivfr.h, special.h, variable.h, Uefisetup.ini and setup.ini
// 
// 9     1/30/12 1:24a Arunsb
// [TAG]  		EIP74676
// [Category]  	Improvement
// [Description]  	Setup.ini and Upfisetup.ini to reserve 3~5 variable and
// GUID for porting purpose
// [Files]  		Amivfr.h, special.h, variable.h, Uefisetup.ini and setup.ini
// 
// 8     11/13/11 1:14p Arunsb
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
// 7     6/30/11 4:06a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Added driver health structures for vfr.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 6     3/23/11 8:37p Blaines
// [TAG] - EIP 23601
// [Category]- Enhancement
// [Symptom]- Add support for OEM special controls.
// [Files] - AmiTse.sdl, CommonHelper.c, Setup.ini, UefiSetup.ini,
// AmiVfr.h, minisetup.h, minisetup.sdl, variable.c, special.c
// 
// 5     2/11/11 4:43p Madhans
// [TAG]  		EIP53146
// [Category]  	New Feature
// [Description]  	Add the support to Move the Dynamic IFR Pages under
// subpages. It should be customizable to move around.
// 
// [Files]  		AMITSE.sdl, CommonHelper.c, setup.ini, Uefisetup.ini,
// setupdata.h, special.c,
// special.h,minisetupext.c,minisetupext.h,UEFI20\hii.c,UEFI2.1\Hii.c,Pars
// e.c,AMIVfr.h  
// 
// 4     12/28/10 6:05p Mallikarjunanv
// [TAG]  		EIP41615
// [Category]  	New Feature
// [Description]  	Added the file browser support for the Add boot option
// reated controls
// [Files]  		AmiVfr.h, AmiTse.sdl, AmiTseStr.uni, CommonHelper.c,
// Faketokens.c, TseElinks.h, EdkHelper.h, minisetup.h, TseAdvanced.c,
// AddBootOption.c
// 
// 3     2/19/10 12:59p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 4     2/19/10 8:03a Mallikarjunanv
// updated year in copyright message
// 
// 3     1/09/10 2:40a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 2     6/24/09 6:33p Madhans
// Coding Standards.
// 
// 1     6/04/09 7:49p Madhans
// AMI TSE Advanced.
// 
// 1     4/28/09 10:50p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 10:25p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		AMIVfr.h
//
// Description:	VFR related header
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMI_VFR_H_
#define _AMI_VFR_H_

#ifndef EFI_GLOBAL_VARIABLE_GUID
#define	EFI_GLOBAL_VARIABLE_GUID	\
	{ 0x8BE4DF61, 0x93CA, 0x11D2, 0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C }
#endif

#define	SYSTEM_ACCESS_GUID	\
	{ 0xE770BB69, 0xBCB4, 0x4D04, 0x9E, 0x97, 0x23, 0xFF, 0x94, 0x56, 0xFE, 0xAC }

#define	LEGACY_DEV_ORDER_GUID	\
	{ 0xA56074DB, 0x65FE, 0x45F7, 0xBD, 0x21, 0x2D, 0x2B, 0xDD, 0x8E, 0x96, 0x52 }

#define	BOOT_MANAGER_GUID \
	{ 0xB4909CF3, 0x7B93, 0x4751, 0x9B, 0xD8, 0x5B, 0xA8, 0x22, 0x0B, 0x9B, 0xB2 }

#define BOOT_NOW_COUNT_GUID \
	{ 0x052e6eb0, 0xf240, 0x42c5, 0x83, 0x09, 0x45, 0x87, 0x45, 0x45, 0xc6, 0xb4 }

#define	AMI_CALLBACK_GUID	\
	{ 0x9CF0F18E, 0x7C7D, 0x49DE, 0xB5, 0xAA, 0xBB, 0xBA, 0xD6, 0xB2, 0x10, 0x07 }

#define	ERROR_MANAGER_GUID	\
	{ 0xADDEBF82, 0xA560, 0x46B9, 0xA2, 0x80, 0x78, 0xC6, 0xAB, 0x61, 0xAE, 0xDA }

#define	DEL_BOOT_OPTION_GUID \
	{ 0xF6C73719, 0xF34C, 0x479C, 0xB3, 0x2F, 0x27, 0x7F, 0xCB, 0xBC, 0xFE, 0x4F }

#define	ADD_BOOT_OPTION_GUID \
    { 0x19d96d3f, 0x6a6a, 0x47d2, 0xb1, 0x95, 0x7b, 0x24, 0x32, 0xda, 0x3b, 0xe2 }

#define	USER_DEFAULTS_GUID	\
    { 0xC4CC0DE8, 0x0687, 0x4422, 0x99, 0xC1, 0x65, 0x35, 0x1A, 0x5D, 0x5F, 0x95 }

#ifndef EFI_SHELL_FILE_GUID
#define EFI_SHELL_FILE_GUID  \
	{ 0xc57ad6b7, 0x0515, 0x40a8, 0x9d, 0x21, 0x55, 0x16, 0x52, 0x85, 0x4e, 0x37 }
#endif

#ifndef EFI_SHELL2_0_FILE_GUID
#define EFI_SHELL2_0_FILE_GUID  \
	{ 0x6302d008, 0x7f9b, 0x4f30, 0x87, 0xac, 0x60, 0xc9, 0xfe, 0xf5, 0xda, 0x4e }
#endif
#define	AMITSESETUP_GUID	\
	{ 0xc811fa38, 0x42c8, 0x4579, 0xa9, 0xbb, 0x60, 0xe9, 0x4e, 0xdd, 0xfb, 0x34 }

#define IDE_SECURITY_CONFIG_GUID \
	{ 0x3dd0de67, 0x2d7, 0x4129, 0x91, 0x4a, 0x9f, 0x37, 0x7c, 0xc3, 0x4b, 0xd}

// TSE Notifications in single place.
// These #define removed from setup.h and minisetup.h.
#define AMITSE_SETUP_ENTER_GUID \
  { 0x71202EEE, 0x5F53, 0x40d9, 0xAB, 0x3D, 0x9E, 0x0C, 0x26, 0xD9, 0x66, 0x57 }

#define AMITSE_AFTER_FIRST_BOOT_OPTION_GUID \
  { 0xC48D651C, 0x9D0E, 0x4ce7, 0xAD, 0x39, 0xED, 0xD1, 0xAB, 0x83, 0x6B, 0x30 }


// {1CBFC9B6-7F1E-4e9e-801F-FBCE4D92A76D}
#define AMITSE_BEFORE_TIMEOUT_GUID \
	{ 0x1cbfc9b6, 0x7f1e, 0x4e9e, 0x80, 0x1f, 0xfb, 0xce, 0x4d, 0x92, 0xa7, 0x6d }

// {CAD40D6E-C871-4398-910D-2D74EE94711A}
#define AMITSE_AFTER_TIMEOUT_GUID \
	{ 0xcad40d6e, 0xc871, 0x4398, 0x91, 0xd, 0x2d, 0x74, 0xee, 0x94, 0x71, 0x1a }


// {3677770F-EFB2-43b2-B8AE-B302E9604882}
#define AMITSE_EVENT_BEFORE_BOOT_GUID \
  { 0x3677770f, 0xefb2, 0x43b2, 0xb8, 0xae, 0xb3, 0x2, 0xe9, 0x60, 0x48, 0x82 }

// {8c12A959-70BC-4362-B437-bBB80514A1916E}
#define AMITSE_EVENT_AFTER_BOOT_GUID \
  {0x8c12a959, 0x70bc, 0x4362, 0xb4, 0x37, 0xb8, 0x05, 0x14, 0xa1, 0x91, 0x6e}

// {1B6BC809-C986-4937-934F-1EA58622FE50}
#define AMITSE_BOOT_ORDER_CHANGE_GUID \
{ 0x1b6bc809, 0xc986, 0x4937, 0x93, 0x4f, 0x1e, 0xa5, 0x86, 0x22, 0xfe, 0x50 }

// {D84BEFF0-159A-4b60-9AB9-AC5C474BD3B1}
#define AMITSE_NVRAM_UPDATE_GUID \
{ 0xd84beff0, 0x159a, 0x4b60, 0x9a, 0xb9, 0xac, 0x5c, 0x47, 0x4b, 0xd3, 0xb1 }

// {073E7E01-2611-4e85-B896-A3B6767CBA00}
#define AMITSE_PASSWORD_PROMPT_ENTER_GUID \
{ 0x73e7e01, 0x2611, 0x4e85, 0xb8, 0x96, 0xa3, 0xb6, 0x76, 0x7c, 0xba, 0x0 }

// {B9B038B0-E2B6-4aab-9435-4165ECFED032}
#define AMITSE_PASSWORD_PROMPT_EXIT_GUID \
{ 0xb9b038b0, 0xe2b6, 0x4aab, 0x94, 0x35, 0x41, 0x65, 0xec, 0xfe, 0xd0, 0x32 }

// {AB1404CA-4801-4208-98BF-30D521DAD4D3}
#define AMITSE_USER_PASSWORD_VALID_GUID \
{ 0xab1404ca, 0x4801, 0x4208, 0x98, 0xbf, 0x30, 0xd5, 0x21, 0xda, 0xd4, 0xd3 }

// {541D5A75-95EE-43c7-9E5D-2394DC486249}
#define AMITSE_ADMIN_PASSWORD_VALID_GUID \
{ 0x541d5a75, 0x95ee, 0x43c7, 0x9e, 0x5d, 0x23, 0x94, 0xdc, 0x48, 0x62, 0x49 }

// {D69240C0-DD40-4f2d-9863-4848DA6E615F}
#define AMITSE_INVALID_PASSWORD_GUID \
{ 0xd69240c0, 0xdd40, 0x4f2d, 0x98, 0x63, 0x48, 0x48, 0xda, 0x6e, 0x61, 0x5f }

#define	DYNAMIC_PAGE_COUNT_GUID	\
    { 0xb63bf800, 0xf267, 0x4f55, 0x92, 0x17, 0xe9, 0x7f, 0xb3, 0xb6, 0x98, 0x46 }

//EIP 57661 Start
// {0885F288-418C-4be1-A6AF-8BAD61DA08FE}
#define AMITSE_DRIVER_HEALTH_ENB_GUID \
    { 0x885f288, 0x418c, 0x4be1, 0xa6, 0xaf, 0x8b, 0xad, 0x61, 0xda, 0x8, 0xfe }

// {7459A7D4-6533-4480-BBA7-79E25A4443C9}
#define	AMITSE_DRIVER_HEALTH_GUID	\
    { 0x7459a7d4, 0x6533, 0x4480, 0xbb, 0xa7, 0x79, 0xe2, 0x5a, 0x44, 0x43, 0xc9 }

// {58279C2D-FB19-466e-B42E-CD437016DC25}
#define	AMITSE_DRIVER_HEALTH_CTRL_GUID	\
    { 0x58279c2d, 0xfb19, 0x466e, 0xb4, 0x2e, 0xcd, 0x43, 0x70, 0x16, 0xdc, 0x25 }
//EIP 57661 End

//EIP70421 & 70422 Support for Driver Order starts
// {C0B4FB05-15E5-4588-9FE9-B3D39C067715}
#define	DRIVER_MANAGER_GUID  \
	{ 0xc0b4fb05, 0x15e5, 0x4588, 0x9f, 0xe9, 0xb3, 0xd3, 0x9c, 0x6, 0x77, 0x15 }
	
	// {17A3C5DA-F51F-437c-91B6-002B6F262593}
#define	DEL_DRIVER_OPTION_GUID \
	{ 0x17a3c5da, 0xf51f, 0x437c, 0x91, 0xb6, 0x0, 0x2b, 0x6f, 0x26, 0x25, 0x93}

#define	ADD_DRIVER_OPTION_GUID \
    { 0x7df66c0f, 0xd40a, 0x4748, 0xac, 0x5a, 0x6c, 0xb, 0xea, 0x78, 0x6a, 0x1a}
//EIP70421 & 70422 Support for Driver ends

#define	OEM_TSE_VAR_GUID	\
	{ 0xF4B2C007, 0x94A1, 0x4cd5, 0xA7, 0x10, 0xf4, 0x14, 0x1f, 0xce, 0xbc, 0xA0 }

//EIP74676 guids and variables for porting purpose starts
//EDA2B104-7A10-4519-B0A1-EBA5C52ACFCE
#define	OEM_PORT_VARIABEL1 \
	{ 0xEDA2B104, 0x7A10, 0x4519, 0xB0, 0xA1, 0xEB, 0xA5, 0xC5, 0x2A, 0xCF, 0xCE }

//EF402953-B819-4cc2-A44C-4C9B4CFBC889
#define	OEM_PORT_VARIABEL2 \
	{ 0xEF402953, 0xB819, 0x4CC2, 0xA4, 0x4C, 0x4C, 0x9B, 0x4C, 0xFB, 0xC8, 0x89 }

//1D6F853E-0006-40d8-9B4B-79618A5733B0
#define	OEM_PORT_VARIABEL3 \
	{ 0x1D6F853E, 0x0006, 0x40d8, 0x9B, 0x4B, 0x79, 0x61, 0x8A, 0x57, 0x33, 0xB0 }

//47E87E67-FBC0-4c01-9002-4A0A6ECB92FF
#define	OEM_PORT_VARIABEL4 \
	{ 0x47E87E67, 0xFBC0, 0x4c01, 0x90, 0x02, 0x4A, 0x0A, 0x6E, 0xCB, 0x92, 0xFF }

//2799A453-FC10-4334-9E66-D3D6EF09D0EE
#define	OEM_PORT_VARIABEL5 \
	{ 0x2799A453, 0xFC10, 0x4334, 0x9E, 0x66, 0xD3, 0xD6, 0xEF, 0x09, 0xD0, 0xEE }

#define	OEM_PORT_GUID1	\
	{ 0xecfd4bce, 0x4279, 0x40f8, 0xba, 0xf2, 0xdc, 0xb7, 0x96, 0x38, 0xd4, 0x1e }

#define	OEM_PORT_GUID2	\
	{ 0x23f69cd0, 0xff46, 0x4db6, 0xb9, 0x82, 0x63, 0xed, 0xf1, 0xa9, 0x1, 0xff }
//EIP74676 ends

//{06449bc5-4494-4f8c-8773-1d2464c0e7ec}
#define AMITSE_AFTER_LAST_BOOT_OPTION_GUID \
  { 0x06449bc5, 0x4494, 0x4f8c, 0x87, 0x73, 0x1d, 0x24, 0x64, 0xc0, 0xe7, 0xec }

#define	EXIT_KEY_ID				        0xF001
#define	AMI_CALLBACK_KEY_ID		        0xF002
#define	BOOT_MANAGER_KEY_ID		        0xF003
#define	BOOT_OPTIONS_KEY_ID		        0xF004
#define	BOOT_TIMEOUT_KEY_ID		        0xF005
#define	BOOT_ORDER_KEY_ID	            0xF006
#define	LEGACY_DEV_KEY_ID		        0xF007
#define	LEGACY_ORDER_KEY_ID	            0xF008
#define	LANGUAGE_KEY_ID			        0xF009
#define	LANGUAGE_CODES_KEY_ID	        0xF00A
#define	EFI_SHELL_KEY_ID		        0xF00B
#define	ERROR_MANAGER_KEY_ID	        0xF00C
#define	NEW_BOOT_OPTION_KEY_ID	        0xF00D
#define	DEL_BOOT_OPTION_KEY_ID	        0xF00E
#define	USER_DEFAULTS_KEY_ID	        0xF00F
#define SYSTEM_ACCESS_KEY		        0xF010
#define ADMIN_PASSWORD_KEY		        0xF011
#define USER_PASSWORD_KEY		        0xF012
#define AMITSESETUP_KEY		            0xF013
#define BOOT_NOW_COUNT_KEY_ID           0xF014
#define	IDE_SECURITY_HD_1_KEY_ID        0xF015
#define LEGACY_GROUP_KEY_ID             0xF016
#define SETUP_SAVE_STATE_INFO_KEY_ID   	0xF017
#define DYNAMIC_PAGE_COUNT_KEY_ID       0xF018
#define DRIVER_HEALTH_ENB_KEY_ID	    0xF019
#define DRIVER_HEALTH_KEY_ID		    0xF020
#define DRIVER_HEALTH_CTRL_KEY_ID	    0xF021
#define	DRIVER_MANAGER_KEY_ID		    0xF022		//EIP70421 & 70422 Support for Driver Order
#define	DRIVER_ORDER_KEY_ID	            0xF023
#define	NEW_DRIVER_OPTION_KEY_ID	    0xF024
#define	DEL_DRIVER_OPTION_KEY_ID	    0xF025
#define OEM_TSE_VAR_KEY_ID              0xF100

#define	SYSTEM_PASSWORD_ADMIN	0
#define	SYSTEM_PASSWORD_USER	1

#define	SAVE_AND_EXIT_VALUE			1
#define	DISCARD_AND_EXIT_VALUE		2
#define	SAVE_VALUE					3
#define	DISCARD_VALUE				4
#define	RESTORE_DEFAULTS_VALUE		5
#define	SAVE_USER_DEFAULTS_VALUE	6
#define	RESTORE_USER_DEFAULTS_VALUE	7
#define	SAVE_BOOT_OPTION			8
#define	SAVE_AND_RESET_VALUE		9
#define	DISCARD_AND_RESET_VALUE		10
#define INTERACTIVE_TEXT_VALUE    	11
#define LAUNCH_FILE_PATH            12		// EIP-41615: releated to file browser support for add boot option.
#define LAUNCH_FILE_PATH_DRIVER     13
#define SAVE_DRIVER_OPTION			14		//EIP70421 & 70422 Support for Driver Order

#define	ADD_FORM_ID				0x2000
#define	DEL_FORM_ID				0x2001
#define	ADD_DRIVER_FORM_ID		0x2002		//EIP70421 & 70422 Support for Driver Order
#define	DEL_DRIVER_FORM_ID		0x2003

#define	HARD_DISK_ORDER_FORM	0x1000
#define	CDROM_ORDER_FORM		0x1001
#define	FLOPPY_DISK_ORDER_FORM	0x1002
#define	NETWORK_ORDER_FORM		0x1003
#define	BEV_ORDER_FORM			0x1004

typedef struct
{
	UINT16 HardDiskCount;
	UINT16 CDROMCount;
	UINT16 FloppyCount;
	UINT16 NetworkCount;
	UINT16 BevCount;
}
LEGACY_DEV_LIST;

#define	SETUP_RESET_NOT_REQUIRED			0
#define	SETUP_SAVED_AND_RESET_REQUIRED		1

#pragma pack(1)
typedef struct
{
	UINT16 SetupSaveState;
}
SETUP_SAVE_STATE_INFO;


typedef struct
{
	UINT16 GroupCount;
}
LEGACY_DEV_INFO;

typedef struct
{
	UINT16 DeviceCount;
}
LEGACY_GROUP_INFO;

typedef struct _SYSTEM_ACCESS
{
	UINT8	Access;
}
SYSTEM_ACCESS;

typedef struct
{
	UINT16 BootCount;
}
BOOT_MANAGER;

typedef struct{
  UINT16            BootCount;
} BOOT_NOW_COUNT;

typedef struct
{
	UINT16 Option;
}
DEL_BOOT_OPTION;

typedef struct 
{
	UINT16	Value;
}
AMI_CALLBACK;

typedef struct 
{
	UINT16	Value;
}
TIMEOUT;

typedef struct{
  UINT16            Value;
} BOOT_ORDER;

typedef struct{
  UINT16            Value;
} LEGACY_DEV_ORDER;

typedef struct 
{
	UINT16	Value;
}
LANGUAGE;

typedef struct 
{
	UINT16	Value;
}
LANGUAGE_CODES;

typedef struct 
{
	UINT16	Value;
}
EFI_SHELL;

typedef struct{
  UINT16            PageCount;
} DYNAMIC_PAGE_COUNT;

typedef struct
{
	UINT16 Value;

}OEMTSEVAR;

//EIP 57661 Start
typedef struct
{
	UINT16 Enable;
}
DRIVER_HEALTH_ENABLE;

typedef struct
{
	UINT16 DrvHandleCount;
}
DRIVER_HEALTH;

typedef struct			//Number of controllers support driver health handle
{
	UINT16 DrvHealthCtrlCnt;
}
DRIVER_HEALTH_CTRL_COUNT;
//EIP 57661 End

typedef struct
{
	UINT16 DriverCount;
} DRIVER_MANAGER;

typedef struct{
  UINT16            Value;
} DRIVER_ORDER;

typedef struct
{
	UINT16 Option;
}DEL_DRIVER_OPTION;

#define	ERROR_MANAGER_NOP			0x0000
#define	ERROR_MANAGER_ALL_ERRORS	0xFFFF

#define OEM_TSE_VARSTORE\
    varstore OEMTSEVAR, key = OEM_TSE_VAR_KEY_ID,\
        name  = OemTSEVar, guid  = OEM_TSE_VAR_GUID;


#ifndef VFRCOMPILE
typedef struct _ERROR_LIST
{
	VOID*	Handle;
	UINT16	Summary;
	UINT16	DetailInfo;
}
ERROR_LIST ;
#endif

typedef struct _ERROR_MANAGER
{
	UINT16		ErrorCount;
	UINT16		ErrorFunction;
#ifndef VFRCOMPILE
	ERROR_LIST	ErrorList[1];
#endif
}
ERROR_MANAGER;

typedef struct _NEW_BOOT_OPTION
{
    CHAR16	Label[20];
    UINT16  FsCount;
    UINT16  SelFs;
    CHAR16	Path[120];
}
NEW_BOOT_OPTION;

typedef struct _NEW_DRIVER_OPTION
{
    CHAR16	Label[20];
    UINT16  FsCount;
    UINT16  SelFs;
    CHAR16	DriverPath[120];
}
NEW_DRIVER_OPTION;

typedef struct
{
	UINT16	Count;
}
USER_DEFAULTS;

typedef struct _IDE_SECURITY_CONFIG {
	UINT16		Count;
    UINT16      Supported;
    UINT16      Enabled;
	UINT16		Locked;
    UINT16      Frozen; 
    UINT16      UserPasswordStatus; 
    UINT16      MasterPasswordStatus; 
    UINT16      ShowMaster;   
	UINT16      IDEUserPassword[32];
    UINT16      IDEMasterPassword[32];
}IDE_SECURITY_CONFIG;

typedef struct _AMITSESETUP
{
    // Passwords
    UINT16  UserPassword[SETUP_PASSWORD_LENGTH];
    UINT16  AdminPassword[SETUP_PASSWORD_LENGTH];
	// AMI SilentBoot
    UINT8   AMISilentBoot;
}
AMITSESETUP;

#pragma pack()

#endif /* _AMI_VFR_H_ */
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
