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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/special.h $
//
// $Author: Arunsb $
//
// $Revision: 9 $
//
// $Date: 10/18/12 5:53a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/special.h $
// 
// 9     10/18/12 5:53a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:35p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     1/30/12 1:27a Arunsb
// [TAG]  		EIP74676
// [Category]  	Improvement
// [Description]  	Setup.ini and Upfisetup.ini to reserve 3~5 variable and
// 			GUID for porting purpose
// [Files]  		Amivfr.h, special.h, variable.h, Uefisetup.ini and setup.ini
// 
// 7     11/13/11 12:39p Arunsb
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
// 6     6/30/11 4:13a Arunsb
// [TAG]           EIP57661
// [Category]      New Feature
// [Description]   Boot manager algorithm for interaction with Driver
// Health protocol.
//                 Guid key added.
// [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
//                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
// amivfr.h, minisetupbin.mak,
//                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
// special.h, boot.h, minisetup.h,
//                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
// uefi21wapper.c.
// 
// 5     2/10/11 12:32p Blaines
// [TAG] - EIP 53146
// [Category]- New Feature
// [Description] -Add the support to Move the Dynamic IFR Pages under
// subpages. It should be customizable to move around.
// 
// 4     2/19/10 1:02p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:12a Mallikarjunanv
// updated year in copyright message
// 
// 4     9/15/09 9:38a Sudhirv
// added definition GUID_KEY_OEM_CONTROL 
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
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
// 11    10/24/07 11:23a Arunkumars
// - Moved IDE security code to binary
// - Fixed build errors under UGA draw support
// - Added EFI key password support
// - Added modifier hot key support
// - Added popup support in From browser protocol
// 
// 10    1/25/07 11:06a Arunkumars
// Fixed StringWrapText function to consider words longer than width.
// Added code to correct LegacyDevOrder upon entry.
// BootOrder now has all the options and only enabled ones are booted by
// boot manager
// 
// 9     1/09/07 10:15a Arunkumars
// Enable/Disable of boot/bbs option support
// Add/Del of boot option support
// 
// 8     10/03/06 11:26a Natalyak
// IDE Security support
// 
// 7     9/27/05 10:02p Franklynd
// Updates to BBS order capability.
// 
// 6     8/01/05 4:15p Franklynd
// 1-Update boot manager and boot options pages at runtime. with latest
// boot information.
// 
// 2- PopupSel using less space.
// 
// 
// 5     7/19/05 3:44p Jerryp
// Language fixes
// 
// 4     6/27/05 2:59p Jerryp
// Support for dynamic expansion
// 
// 3     6/24/05 7:35p Jerryp
// 
// 2     6/24/05 10:17a Jerryp
// Added ErrorManager handling
// 
// 1     5/27/05 10:24a Jerryp
// Special handling for OEM packs
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		Special.h
//
// Description:	Header file for TSE special controls like AMI callback controls
//				
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#ifndef _SPECIAL_H_
#define	_SPECIAL_H_

#define	GUID_KEY_BOOT_NOW					0x0001
#define	GUID_KEY_AMI_CALLBACK			0x0002
#define	GUID_KEY_ERROR_MANAGER			0x0003
#define	GUID_KEY_LANG_CODES				0x0005
#define 	GUID_KEY_BBS_ORDER				0x0007
#define 	GUID_KEY_IDE_SECURITY			0x0008
#define 	GUID_KEY_ADD_BOOT_OPTION   	0x0009
#define 	GUID_KEY_OEM_CONTROL	    		0x000A
#define 	GUID_KEY_MODAL						0x000B
#define 	GUID_KEY_REFRESH					0x000C
#define	GUID_KEY_NO_COMMIT				0x000D
#define	GUID_KEY_DYNAMIC_PAGE			0x000E
#define	GUID_KEY_DRIVER_HEALTH_ENB		0x000F
#define	GUID_KEY_DRIVER_HEALTH			0x0010
#define	GUID_KEY_DRV_HEALTH_CTRL_COUNT	0x0011
#define	GUID_KEY_DRIVER_OPTION			0x0012		//EIP70421 & 70422  Support for driver order
#define	GUID_KEY_OEMGUID1					0x0013		//EIP74676 guids for porting purpose
#define	GUID_KEY_OEMGUID2					0x0014


UINT16 SpecialGetValue( CONTROL_DATA *control, GUID_INFO **guidInfo );
VOID SpecialAddMultipleControls( CONTROL_INFO *controlInfo, GUID_INFO *guidInfo );
VOID SpecialUpdatePageControls(UINT32 CurrentPage);

#endif /* _SPECIAL_H_ */

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
